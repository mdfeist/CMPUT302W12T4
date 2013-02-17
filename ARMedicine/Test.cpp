#include "cube.hh"

class Test: public wxApp{
       virtual bool OnInit();
};

IMPLEMENT_APP(Test)

bool Test::OnInit()
{
   wxString title("Title", wxConvUTF8);
   wxFrame *frame = new wxFrame(NULL,-1,title,wxPoint(50,50),wxSize(800,600));

   TestGLCanvas *canvas;
   canvas=new TestGLCanvas(frame,wxNewId(),wxPoint(0,0));

   frame->Show(true);
}
