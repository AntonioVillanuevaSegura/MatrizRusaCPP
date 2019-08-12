/*Matriz Rusa en wxWidgets Antonio Villanueva
https://www.wxwidgets.org/downloads/
https://drive.google.com/open?id=1-w3Vt29wkp3xScl0bCmWbAc2Kl3G6-lR
https://wiki.wxwidgets.org/Installing_and_configuring_under_Ubuntu
sudo apt-cache search libwxgt*
sudo apt-get install wx2.8-headers libwxgtk2.8-0 libwxgtk2.8-dev
cd /usr/include
ls | grep wx
sudo ln -sv wx-2.8/wx wx
When you compile your files to include the wxWidgets libraries, add this to the end of your gcc command:

'wx-config --cxxflags' 'wx-config --libs'
 
Compilacion
g++ -std=c++11  -o ejecutable *.cpp `wx-config --libs`

*/
#include <iostream>
#include <random> //n aleatorios
#include <ctime>
#include "wx/wx.h"
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/sizer.h> //Layouts Sizers

#define TAM_PANTALLA 350
#define TAM_BOTON 50

using namespace std;
//Declaraciones 
//----------------------------------------------------------------------
//Cada aplicacion wxWidget define una clase derivada de wxApp
class MiApp:public wxApp
{
  public:
  //Llamado al inicio startup, es como el main en c
  virtual bool OnInit();//main wxWidgets , mas abajo se implementa 
};

//Declaracion de la clase frame principal

//----------------------------------------------------------------------

class MiFrame:public wxFrame
{
  public:
  //Constructor de la clase
  MiFrame(const wxString& titulo);
  void OnButton(wxCommandEvent& event);//Manipula los botones
  int aleatorio (int minimo=1, int maximo=10);//Genera numeros aleatorio
  
  private:

  wxPanel* ventana;
  
  wxStaticText* label;
  wxStaticText* datos;

  /*Macro para informar a wxWidgets de la gestion de eventos
  *Declara la tabla de eventos en esta clase ,mas abajo
  * la implemento entre BEGIN_ y END_EVENT_TABLE
  */
  
  //Declaracion dinamica eventos no utilizo el macro 
  //Trabajaremos desde OnInit para eventos dinamicos
  DECLARE_EVENT_TABLE()
};
//----------------------------------------------------------------------
//----------------------------------------------------------------------

/*Implementacion , MiApp 
*Cuando se crea el objeto MiApp se asigna a la variable global wxTheApp
* pero mejor que hacer un CAST emplear el MACRO  DECLARE_APP despues de 
* la declaracion de la clase , wxGetApp retorna una ref. al objeto MiApp
*/
DECLARE_APP(MiApp)

//Macro que Proporciona a wxWidgets los medios de crear el objeto MiApp
IMPLEMENT_APP(MiApp)

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//Implementacion OnInit,Inicializa la aplicacion 

bool MiApp::OnInit()
{
  //Crea la ventana principal , una instancia de nuestra clase MiFrame
  //El titulo lo pasamos al constructor envuelto en el macro wxT
  //macro de conversion de strings y char al tipo apropiado
  MiFrame *frame=new MiFrame(wxT("Matriz Rusa A.Villanueva"));
  
  frame->SetSize(wxDefaultCoord,wxDefaultCoord,TAM_PANTALLA,TAM_PANTALLA);
  
  //Mostrar la ventana
  frame->Show(true);
  
  //Arranca el bucle de eventos
  return true ;//Si false limpia sus estructuras y sale 
}

//----------------------------------------------------------------------


const wxWindowIDRef BOTON = wxWindow::NewControlId();

//Tabla de eventos para MiFrame DECLARE_EVENT_TABLE() en MiFrame

BEGIN_EVENT_TABLE (  MiFrame,wxFrame)
  //EVT_BUTTON(BOTON, MiFrame::OnButton)//Evento un boton pulsado 
  EVT_BUTTON(wxID_ANY, MiFrame::OnButton)//Evento un boton pulsado   
  
END_EVENT_TABLE()
//----------------------------------------------------------------------
int MiFrame::aleatorio(int minimo,int maximo){
	return  minimo + std::rand()/((RAND_MAX + 1u)/maximo);
}
//----------------------------------------------------------------------
//wxID_ANY le dice a Widgets de generar un identificador por su cuenta
MiFrame::MiFrame(const wxString& titulo):wxFrame(NULL,wxID_ANY,wxT("5x5 A.Villanueva"))
{
	ventana=new wxPanel(this,wxID_ANY);
	//std::srand(std::time(nullptr)); //usa la hora actual para numeros aleatorios
	
	wxButton* matrizBotones[5][5];
	bool matrizSuma[5][5];

	int EtiquetaSuperior [5];//Valores de suma de las etiquetas
	int EtiquetaInferior [5];
	
	//CREA BOTONES
      wxPoint posicion(0,0); //wxPoint (const wxRealPoint &pt)
      wxSize TAMANO(TAM_BOTON,TAM_BOTON); //Tamano de un boton
      //Crea botones
      for (int x=1;x<=5;x++){
		for (int y=1 ;y<=5;y++){
        posicion= wxPoint(x*TAM_BOTON,y*TAM_BOTON);
        //wxButton* boton1=new wxButton(ventana,BOTON,wxT("x"),posicion,TAMANO);
       //new wxButton( ventana,wxID_ANY,(to_string (x+y)),posicion,TAMANO);
		//new wxButton( ventana,wxID_ANY,(to_string (aleatorio(1,9))),posicion,TAMANO);  
		matrizBotones[x-1][y-1]=new wxButton( ventana,wxID_ANY,(to_string (aleatorio(1,9))),posicion,TAMANO);  
		matrizSuma[x-1][y-1]=
      }
    }
   
  //CREA ETIQUETAS 
  
  int offset=25;
  
  for (int x=1;x<=5;x++){// etiquetas HORIZONTALES X
    int y=0;
      posicion= wxPoint(x*TAM_BOTON+offset,TAM_BOTON/2);
      wxStaticText* etiqueta=new wxStaticText( ventana,wxID_ANY,(to_string (x+y)),posicion,TAMANO);
      etiqueta->SetForegroundColour( wxColor(*wxRED));
        
      posicion= wxPoint(x*TAM_BOTON+offset,TAM_BOTON*6 +TAM_BOTON/4);       
      etiqueta=new wxStaticText( ventana,wxID_ANY,(to_string (x+y)),posicion,TAMANO); 
      etiqueta->SetForegroundColour( wxColor(*wxRED));
    }

  for (int y=1;y<=5;y++){//etiquetas VERTICALES Y
    int x=0;
      posicion= wxPoint(TAM_BOTON/3,y*TAM_BOTON+offset);
      wxStaticText* etiqueta=new wxStaticText( ventana,wxID_ANY,(to_string (x+y)),posicion,TAMANO);
      etiqueta->SetForegroundColour( wxColor(*wxRED));
      
      posicion= wxPoint(TAM_BOTON*6 +TAM_BOTON/2,y*TAM_BOTON+offset);     
      etiqueta=new wxStaticText( ventana,wxID_ANY,(to_string (x+y)),posicion,TAMANO);
      etiqueta->SetForegroundColour( wxColor(*wxRED));            
    }
  
}    

//Boton
void MiFrame::OnButton(wxCommandEvent& event)//Botones
{
	wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);	
	//cout <<" ETIQUETA = "<< string (button->GetLabel ())<<endl;
	if (button->GetBackgroundColour()!=*wxRED ){
		button->SetBackgroundColour(*wxRED);
	}else{
		button->SetBackgroundColour(*wxYELLOW);
	}
	
	
	
	
	/*
	cout <<"Boton = "<<event.GetId()<<endl;
	cout<<"Evento ="<<event.GetEventObject()<<endl;
	*/
	
	/*
	wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);	
	cout <<" ETIQUETA = "<< string (button->GetLabel ())<<endl;

	//button->SetForegroundColour(*wxRED);//COLOR LETRAS
	button->SetBackgroundColour(*wxYELLOW);

	wxColour color=button->GetBackgroundColour();
	
	if (color==wxColour(255, 255, 0)){
		cout <<"Red"<<endl;
	}
	//button->ClearBackground();
	*/
}
 
