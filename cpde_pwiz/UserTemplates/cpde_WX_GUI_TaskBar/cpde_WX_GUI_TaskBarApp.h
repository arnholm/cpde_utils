/***************************************************************
 * Name:      %%%project_name_lowercase%%%App.h
 * Purpose:   Defines Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2013-08-31
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#ifndef %%%project_name_lowercase%%%APP_H
#define %%%project_name_lowercase%%%APP_H

#include <wx/app.h>
class %%%project_name_lowercase%%%Icon;
class %%%project_name_lowercase%%%Dialog;

class %%%project_name_lowercase%%%App : public wxApp {
public:
  virtual bool OnInit();

  // either show or hide the dialog, as requested
  void ShowDialog(bool show);

  // toggle show/hide of dialog, depending on current state
  void ToggleDialog();

  // exit the application
  void Exit();
private:
  %%%project_name_lowercase%%%Dialog* m_dlg;
  %%%project_name_lowercase%%%Icon*   m_taskBarIcon;
};

DECLARE_APP(%%%project_name_lowercase%%%App)

#endif // %%%project_name_lowercase%%%APP_H
