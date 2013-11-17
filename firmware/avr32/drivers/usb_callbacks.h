
 #ifndef _MAIN_H_
 #define _MAIN_H_

 bool main_generic_enable(void);

 void main_generic_disable(void);

 void main_vbus_action(bool b_high);

 void main_sof_action(void);

 void main_suspend_action(void);

 void main_resume_action(void);

 void main_remotewakeup_enable(void);

 void main_remotewakeup_disable(void);

 void main_hid_set_feature(uint8_t* report);

 #endif // _MAIN_H_
