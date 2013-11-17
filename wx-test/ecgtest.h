#ifndef _glpane_
#define _glpane_
 
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "dsp/dsp.h"
 
class MyEventHandler; 
 
class ECGGLPane : public wxGLCanvas
{
    wxGLContext*	m_context;
	int act_cursor;
	float measurement;
	void drawGrid();
	void text(GLfloat x, GLfloat y, char *text);
	void putChannel(const std::vector<EcgSample>&, int ch, float x, float y);
	MyEventHandler& handler;
public:
	EcgSampleBuffer ecg_buffer;
	BaselineFilterBuffer blf_buffer;
	
	ECGGLPane(wxFrame* parent, int* args, MyEventHandler& handler);
	virtual ~ECGGLPane();
    
	void resized(wxSizeEvent& evt);
    
	int getWidth();
	int getHeight();
    
	void render();
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
    
	// events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
    void doPaint( wxPaintEvent& evt ) ;

	void incCursor();

	DECLARE_EVENT_TABLE()
};
#endif 