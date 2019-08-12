/*Matriz Rusa en wxWidgets Antonio Villanueva
instalar wxWidgets 
Compilacion
g++ -std=c++11  -o ejecutable *.cpp `wx-config --libs`

*/
#include <iostream>
#include <random> //n aleatorios
#include <ctime>
#include <string>
#include "wx/wx.h"
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/sizer.h> //Layouts Sizers

#define TAM_PANTALLA 375
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
  
  int valorFila(int x,bool validacion=true);//Suma una fila 
  int valorColumna(int y,bool validacion=true);//Suma una columna
  void valorEtiquetas();//Crea valores de suma para las etiquetas
  void creaBotones();//Creacion de botones 
  void creaEtiquetas();//Creacion de etiquetas perifericas
  
  private:

	wxPanel* ventana;

	wxStaticText* label;
	wxStaticText* datos;

	wxButton* matrizBotones[5][5];//Guarda los botones 
	wxStaticText* matrizEtiquetas[4][5];//Guarda las etiquetas sup,inf,izq,der
	
	bool matrizSuma[5][5];//valores booleanos aceptados en la suma

	int EtiquetasColumna [5];//Suma de valores aceptados en columna
	int EtiquetasLinea [5]; //Suma de valores aceptadis en Linea 
	


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
int MiFrame::valorFila(int x,bool validacion){//Suma una fila 
	int suma(0);
	for (int y=0;y<5;y++){
		if ( validacion){//Emplea el array de validacion
			
			if (matrizSuma[x][y] ){//Si esta validada para la suma
				suma+=std::stoi (string (matrizBotones[x][y]->GetLabel()));	
			}
			
		}else{//Validacion por boton
			if (matrizBotones[y][x]->GetBackgroundColour()!=*wxRED ){//Si no es rojo suma
				suma+=std::stoi (string (matrizBotones[y][x]->GetLabel()));
			}
		}	
	}
	return suma;
}
//----------------------------------------------------------------------  
int MiFrame::valorColumna(int y,bool validacion){//Suma una columna
	int suma(0);
	for (int x=0;x<5;x++){
		if ( validacion){//Emplea el array de validacion
			
			if (matrizSuma[y][x]){//Si esta validada para la suma				
				suma+=std::stoi (string (matrizBotones[y][x]->GetLabel()));	
			}
		}else{//validacion por boton
			if (matrizBotones[y][x]->GetBackgroundColour()!=*wxRED ){//Si no es rojo suma			
				suma+=std::stoi (string (matrizBotones[y][x]->GetLabel()));
			}
		}	
	}
	return suma;
}
//----------------------------------------------------------------------    
void MiFrame::valorEtiquetas(){//Crea valores de suma para las etiquetas 
	//Emplea los botones y el array de validacion
	
	for (int x=0;x<5;x++){//Recorre lineas , crea suma de  linea		
		EtiquetasLinea [x] =valorFila(x,true);
	}
	
	for (int y=0;y<5;y++){//Recorre columnas,crea suma de columna		
		EtiquetasColumna [y] =valorColumna(y,true);
	}	
	
	//Debug de la matriz suma ,valores validados ,booleanos
	for (int x=0;x<5;x++){
		for (int y=0;y<5;y++){
			cout <<matrizSuma[x][y]<<" ";
		}
		cout <<endl;
	}
	
	
		
}
//----------------------------------------------------------------------
void MiFrame::creaBotones(){//Creacion de botones y la matrizSuma
	//CREA BOTONES
      wxPoint posicion(0,0); //wxPoint (const wxRealPoint &pt)
      wxSize TAMANO(TAM_BOTON,TAM_BOTON); //Tamano de un boton
      //Crea botones
      for (int y=1;y<=5;y++){
		for (int x=1 ;x<=5;x++){
        posicion= wxPoint(x*TAM_BOTON,y*TAM_BOTON);
        //wxButton* boton1=new wxButton(ventana,BOTON,wxT("x"),posicion,TAMANO);
       //new wxButton( ventana,wxID_ANY,(to_string (x+y)),posicion,TAMANO);
		//new wxButton( ventana,wxID_ANY,(to_string (aleatorio(1,9))),posicion,TAMANO);  
		matrizBotones[x-1][y-1]=new wxButton( ventana,wxID_ANY,(to_string (aleatorio(1,9))),posicion,TAMANO);  
		matrizSuma[x-1][y-1]=aleatorio(0,2) ==1 ? true :false;//Crea la casillas validadas
      }
    }
    
    //Debug valor botones
	for (int y=0;y<5;y++){
		for (int x=0;x<5;x++){
			cout <<matrizBotones[x][y]->GetLabel ()<<"  ";
		}
		cout <<endl;
	}	
    
    	
}
//----------------------------------------------------------------------
void MiFrame::creaEtiquetas(){//Creacion de etiquetas perifericas
	wxPoint posicion(0,0); //wxPoint (const wxRealPoint &pt)
    wxSize TAMANO(TAM_BOTON,TAM_BOTON); //Tamano de un boton	
	
	int offset=25;
  
  for (int x=1;x<=5;x++){// etiquetas HORIZONTALES X
      posicion= wxPoint(x*TAM_BOTON+offset,TAM_BOTON/2);
      matrizEtiquetas[x-1][0]=new wxStaticText( ventana,wxID_ANY,(to_string (EtiquetasLinea[x-1])),posicion,TAMANO);
      //etiqueta->SetForegroundColour( wxColor(*wxRED));
        
      posicion= wxPoint(x*TAM_BOTON+offset,TAM_BOTON*6 +TAM_BOTON/4);       
      matrizEtiquetas[x-1][1]=new wxStaticText( ventana,wxID_ANY,(to_string (EtiquetasLinea[x-1])),posicion,TAMANO); 
      //etiqueta->SetForegroundColour( wxColor(*wxRED));
    }

  for (int y=1;y<=5;y++){//etiquetas VERTICALES Y

      posicion= wxPoint(TAM_BOTON/3,y*TAM_BOTON+offset);
      matrizEtiquetas[y-1][2]=new wxStaticText( ventana,wxID_ANY,(to_string (EtiquetasColumna [y-1])),posicion,TAMANO);
      //etiqueta->SetForegroundColour( wxColor(*wxRED));
      
      posicion= wxPoint(TAM_BOTON*6 +TAM_BOTON/2,y*TAM_BOTON+offset);     
      matrizEtiquetas[y-1][3]==new wxStaticText( ventana,wxID_ANY,(to_string (EtiquetasColumna[y-1])),posicion,TAMANO);
      //etiqueta->SetForegroundColour( wxColor(*wxRED));            
    }	
}

//----------------------------------------------------------------------
//wxID_ANY le dice a Widgets de generar un identificador por su cuenta
MiFrame::MiFrame(const wxString& titulo):wxFrame(NULL,wxID_ANY,wxT("5x5 A.Villanueva"))
{
	ventana=new wxPanel(this,wxID_ANY);
	std::srand(std::time(nullptr)); //usa la hora actual para numeros aleatorios

	//CREA BOTONES
	creaBotones();
	valorEtiquetas();//Crea los valores de la suma en las etiquetas perifericas
	creaEtiquetas();//Crea las etiquetas perifericas con el valor suma
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
	
	//Analisis de sumas en la linea ,fila
	

	for (int x=0;x<5;x++){//Lineas
		if (valorFila(x,false)==EtiquetasLinea[x] ){
			cout <<"ok" <<endl;
			matrizEtiquetas[2][x]->SetForegroundColour( wxColor(*wxRED));
			//matrizEtiquetas[3][x]->SetForegroundColour( wxColor(*wxRED));		

		}
	}
	
	/*
	for (int x=0;x<5;x++){//Columnas
		if (valorColumna(x,false)==EtiquetasColumna[x] ){
			cout <<"ok" <<endl;
			matrizEtiquetas[0][x]->SetForegroundColour( wxColor(*wxRED));
			matrizEtiquetas[1][x]->SetForegroundColour( wxColor(*wxRED));;		

		}
	}	
	*/
	
	
	
	
	
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
