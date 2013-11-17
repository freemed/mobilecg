#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/glcanvas.h"
#include "wx/sound.h"
#include "ecgtest.h"
#include "stdio.h"
#include "stdlib.h"

// include OpenGL
#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#include "GLUT/glut.h"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#endif
 
#include "driver/ecg_driver.hpp"
#include "driver/i_ecg_event_handler.hpp"
#include "driver/usb_packets.hpp"

const int grid_size = 45;
const double sampling_freq = 542.5347222;
const double pixel_per_sample = grid_size*2.5/sampling_freq;
const int num_samples = (int)(450/pixel_per_sample);

uint32_t swap_endianness(uint32_t num)
{
	return ((num>>24)&0xff) |
		((num<<8)&0xff0000) |
		((num>>8)&0xff00) |
		((num<<24)&0xff000000);
}
 
class MyEventHandler: public IEcgEventHandler
{
public:
	MyEventHandler():
		last_time_stamp_(0)
	{
		file_ = 0;
	}

	virtual void onConnected()
	{
		printf("Connected.\n");
		last_time_stamp_ = -1;
	}
	
	virtual void onDisconnected(bool error)
	{
		printf("Disconnected.\n");
	}
	
	virtual void onReceiveData(const DataPacketIn& packet)
	{
		int ts = swap_endianness(packet.time_stamp);
		//printf("DATA %d.\n", ts);
		if(last_time_stamp_+1 != ts)
			printf("ERROR: Missing packet(s) between %d and %d.\n", last_time_stamp_, ts);
		last_time_stamp_ = ts;
		
		EcgSample s1, s2;
		packet_to_sample.processPacket(packet, &s1, &s2);
		if(NULL != ecg_gl_pane_)
		{
			ecg_gl_pane_->ecg_buffer.putSample(s1);
			ecg_gl_pane_->ecg_buffer.putSample(s2);
			ecg_gl_pane_->blf_buffer.putSample(s1);
			ecg_gl_pane_->blf_buffer.putSample(s2);
			ecg_gl_pane_->incCursor();
			if(ts % 5 == 0)
				ecg_gl_pane_->render();		
		}
		if(file_ != 0)
		{
			for(int ch = 0; ch < 12; ch++)
				fprintf(file_, "%d ", (int)packet.channel_data[0][ch]);
			fprintf(file_, "\n");	
			for(int ch = 0; ch < 12; ch++)
				fprintf(file_, "%d ", (int)packet.channel_data[1][ch]);
			fprintf(file_, "\n");
		}
	}
	
	virtual void onReceiveDebugMessage(char *message)
	{
		printf("*** DEBUG: %s\n", message);
	}
	
	virtual void onReceiveStatus(const StatusPacketIn& status)
	{
		printf("# hw version %d.%d, recording: %d, error: %d\n",
			(int)status.hw_version,
			(int)status.fw_version,
			status.is_recording,
			status.internal_error
		);
	}
	
	virtual ~MyEventHandler()
	{
		if(file_)
			fclose(file_);
	}
	
	void setBuffer(ECGGLPane* value)
	{
		ecg_gl_pane_ = value;
	}
	
	void openFile(const char* fn)
	{
		file_ = fopen(fn, "w");
	}
	
	void closeFile()
	{
		fclose(file_);
		file_ = 0;
	}
	
private:
	int last_time_stamp_;
	PacketToSample packet_to_sample;
	ECGGLPane* ecg_gl_pane_;
	FILE* file_;
};

 
class MyApp: public wxApp
{
public:
	MyApp():
		driver_(handler_)
	{}

private:
    virtual bool OnInit();
    virtual int OnExit();
    
    wxFrame *frame;
    ECGGLPane * glPane;
         
    MyEventHandler handler_;
	EcgDriver driver_;
};
 
IMPLEMENT_APP(MyApp)
 
 
bool MyApp::OnInit()
{
	srand (time(NULL));
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("mobilECG test app"), wxPoint(50,50), wxSize(1000,750));
	
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    
    glPane = new ECGGLPane( (wxFrame*) frame, args, handler_);
    handler_.setBuffer(glPane);
    sizer->Add(glPane, 1, wxEXPAND);
	
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
	
    frame->Show();
    
	driver_.connect();
	if(!driver_.isConnected())
	{
		printf("Could not connect.\n");
		return true;
	}
	driver_.requestStatus();
	driver_.startRecording();
    return true;
} 
 
int MyApp::OnExit()
{
	driver_.stopRecording();
	driver_.disconnect();
	wxApp::OnExit();
    return 0;
}  
 
BEGIN_EVENT_TABLE(ECGGLPane, wxGLCanvas)
EVT_MOTION(ECGGLPane::mouseMoved)
EVT_LEFT_DOWN(ECGGLPane::mouseDown)
EVT_LEFT_UP(ECGGLPane::mouseReleased)
EVT_RIGHT_DOWN(ECGGLPane::rightClick)
EVT_LEAVE_WINDOW(ECGGLPane::mouseLeftWindow)
EVT_SIZE(ECGGLPane::resized)
EVT_KEY_DOWN(ECGGLPane::keyPressed)
EVT_KEY_UP(ECGGLPane::keyReleased)
EVT_MOUSEWHEEL(ECGGLPane::mouseWheelMoved)
EVT_PAINT(ECGGLPane::doPaint)
END_EVENT_TABLE()
 
 
// some useful events to use
void ECGGLPane::mouseMoved(wxMouseEvent& event) {}
void ECGGLPane::mouseDown(wxMouseEvent& event) {}
void ECGGLPane::mouseWheelMoved(wxMouseEvent& event) {}
void ECGGLPane::mouseReleased(wxMouseEvent& event) {}
void ECGGLPane::rightClick(wxMouseEvent& event) {}
void ECGGLPane::mouseLeftWindow(wxMouseEvent& event) {}
void ECGGLPane::keyPressed(wxKeyEvent& event) {
	wxSound(wxT("start.wav"), false).Play(wxSOUND_ASYNC);
	char buf[32];
	char id[16];
	for(int i = 0; i < 10; i++)
		id[i]='0'+(rand()%10);
	id[10]=0;
	sprintf(buf, "record_%s.ecg", id);
	handler.openFile(buf);
	measurement = 18;
}
void ECGGLPane::keyReleased(wxKeyEvent& event) {}
 
ECGGLPane::ECGGLPane(wxFrame* parent, int* args, MyEventHandler& handler) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
    handler(handler)
{
	m_context = new wxGLContext(this);
 	act_cursor = 0;
 	measurement = 0;
    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}
 
ECGGLPane::~ECGGLPane()
{
	delete m_context;
}
 
void ECGGLPane::resized(wxSizeEvent& evt)
{
//	wxGLCanvas::OnSize(evt);
	
    Refresh();
}
  
/** Inits the OpenGL viewport for drawing in 2D. */
void ECGGLPane::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); 
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}
 
int ECGGLPane::getWidth()
{
    return GetSize().x;
}
 
int ECGGLPane::getHeight()
{
    return GetSize().y;
}
 
void ECGGLPane::doPaint( wxPaintEvent& evt ) 
{
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
	render();
}

void ECGGLPane::incCursor()
{
	if(measurement > 0)
	{
		measurement -= 2.0/sampling_freq;
		if(measurement <= 0)
		{
			wxSound(wxT("success.wav"), false).Play(wxSOUND_ASYNC);	
			handler.closeFile();
		}
	}
	act_cursor += 2;
	if(act_cursor >= num_samples)
		act_cursor -= num_samples;
}

void ECGGLPane::drawGrid()
{
    for(float x = 0; x < 1000; x += grid_size/2.0/5.0)
    {
    	glColor4f(1, 0.8, 0.8, 1);
		glBegin(GL_LINE_STRIP);
    	glVertex3f(x, 0, 0);
    	glVertex3f(x, 750, 0);
		glEnd();
    }
    for(float y = 0; y < 750; y += grid_size/2.0/5.0)
    {
    	glColor4f(1, 0.8, 0.8, 1);
		glBegin(GL_LINE_STRIP);
    	glVertex3f(0, y, 0);
    	glVertex3f(1000, y, 0);
		glEnd();
    }
    for(float x = 0; x < 1000; x += grid_size/2.0)
    {
    	glColor4f(1, 0.7, 0.7, 1);
		glBegin(GL_LINE_STRIP);
    	glVertex3f(x, 0, 0);
    	glVertex3f(x, 750, 0);
		glEnd();
    }
    for(float y = 0; y < 750; y += grid_size/2.0)
    {
    	glColor4f(1, 0.7, 0.7, 1);
		glBegin(GL_LINE_STRIP);
    	glVertex3f(0, y, 0);
    	glVertex3f(1000, y, 0);
		glEnd();
    }
}


void ECGGLPane::text(GLfloat x, GLfloat y, char *text)
{
    char *p;
    
    glPushMatrix();
//   glTranslatef(x, y, 0);
//    glScalef(0.15,-0.15,1);
    glRasterPos2f(x, y);
    for (p = text; *p; p++)
    	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
        //glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
}

void ECGGLPane::putChannel(const std::vector<EcgSample>& samples, int ch, float x, float y) 
{
	const char* ctext = "ECG";
	switch(ch) {
		case CHANNEL_AVR:
			ctext = "aVR";
			break;
		case CHANNEL_AVL:
			ctext = "aVL";
			break;
		case CHANNEL_AVF:
			ctext = "aVF";
			break;
		case CHANNEL_I:
			ctext = "I";
			break;
		case CHANNEL_II:
			ctext = "II";
			break;
		case CHANNEL_III:
			ctext = "III";
			break;
		case CHANNEL_V1:
			ctext = "V1";
			break;
		case CHANNEL_V2:
			ctext = "V2";
			break;
		case CHANNEL_V3:
			ctext = "V3";
			break;
		case CHANNEL_V4:
			ctext = "V4";
			break;
		case CHANNEL_V5:
			ctext = "V5";
			break;
		case CHANNEL_V6:
			ctext = "V6";
			break;
	}
    glColor4f(0, 0, 0, 1);	
    text(x-14,y-25,const_cast<char*>(ctext));
    glColor4f(0, 0, 0, 1);
	glBegin(GL_LINE_STRIP);
	int cursor = num_samples - act_cursor;
    for(int i = samples.size()-num_samples; i+30 < samples.size(); i++)
    {
    	glVertex3f(x + 450 - cursor*pixel_per_sample, y - samples[i].data[ch] * grid_size, 0);
    	cursor++;
    	if(cursor >= num_samples) {
    		cursor = 0;
			glEnd();
			glBegin(GL_LINE_STRIP);
    	}
    }
	glEnd();
}

void ECGGLPane::render()
{
    if(!IsShown()) return;
    
    wxGLCanvas::SetCurrent(*m_context);
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // ------------- draw some 2D ----------------
    prepare2DViewport(0,0,getWidth(), getHeight());
    glLoadIdentity();
    
	std::vector<EcgSample> samples;
	blf_buffer.reset();
	const int plus = (int)(100/pixel_per_sample);
	for(int i = 0; i < num_samples+plus; i++)    
	{
		EcgSample s;
		if(!blf_buffer.getNextSample(&s))
			break;
		samples.push_back(s);
	}
	//printf("%d\n", samples.size());

    char *p;


   	drawGrid();

    glColor4f(1, 0.6, 0.6, 1);
    glPushMatrix();
    glRotatef(-30, 0,0,1);
    glTranslatef(-170, 580, 0);
    glScalef(1,-1,1);
    for (p = "DEVELOPMENT"; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30, 0,0,1);
    glTranslatef(-20, 750, 0);
    glScalef(1,-1,1);
    for (p = "VERSION"; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();



    float spacing = 120;
    float start = 65;
	putChannel(samples, CHANNEL_I,   40, start+0*spacing);
	putChannel(samples, CHANNEL_II,  40, start+1*spacing);
	putChannel(samples, CHANNEL_III, 40, start+2*spacing);
	putChannel(samples, CHANNEL_AVR, 40, start+3*spacing);
	putChannel(samples, CHANNEL_AVL, 40, start+4*spacing);
   	putChannel(samples, CHANNEL_AVF, 40, start+5*spacing);

	putChannel(samples, CHANNEL_V1, 525, start+0*spacing);
	putChannel(samples, CHANNEL_V2, 525, start+1*spacing);
	putChannel(samples, CHANNEL_V3, 525, start+2*spacing);
	putChannel(samples, CHANNEL_V4, 525, start+3*spacing);
	putChannel(samples, CHANNEL_V5, 525, start+4*spacing);
   	putChannel(samples, CHANNEL_V6, 525, start+5*spacing);
 
 	if(measurement > 0)
 	{
 		int sec = measurement;
 		char buf[32];
 		if(sec>15)
 			sprintf(buf, "starting measurement");
 		else
 			sprintf(buf, "%ds remaining", sec);
 		glColor4f(0, 0, 0.5, 1);
 		text(20,710,buf);
 	}
 
 	glColor4f(0.3, 0.3, 0.3, 1);
	float x = 450 - (num_samples-act_cursor)*pixel_per_sample;
	glBegin(GL_LINE_STRIP);
    glVertex3f(40+x, 0, 0);
    glVertex3f(40+x, 750, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
    glVertex3f(525+x, 0, 0);
    glVertex3f(525+x, 750, 0);
	glEnd();

 
    glFlush();
    SwapBuffers();
}