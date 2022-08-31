#include <iostream>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

const char *nombre_archivo="../Base de Datos/Marcas.txt";
const char *nombre_auxiliar="../Base de Datos/MarcasAux.txt";

const char *nombre_archivopro="../Base de Datos/Productos.txt";
const char *nombre_auxiliarpro="../Base de Datos/ProductosAux.txt";

void mostrar();
void valoresIniciales();
void menu();
void opcionSeleccionada(int);
void Ingresar();
void IngresarDb();
void Modificar();
void Eliminar();

bool esNumerico(string); 
bool VeririficarRepetido(string);
bool Existe(string);
void mostrarMarca();
void mostrarProducto();

void IngresarDb(string,string,string,float,float,char const*);
void mod(string,string,string,float,float,char const*);
void eli(string);
int Cuenta(string s, const char Separadorr, int &TotalChars) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] == Separadorr) TotalChars++;
	}

	void split(string Linea, char Separador, vector<string> &TempBuff, int &TotalVector) {
    TempBuff.resize(0);
    TotalVector = 0;
    int Nums = -1;
    int NumPos = -1;
    int ValorNum = 0;
    int TotalChars = 0;
    int TotalEspacios = Linea.length();
    string Valor;
    Cuenta(Linea, Separador, TotalChars);
    if (TotalChars != 0) {
        while (Nums < TotalChars) {
            Nums++;
            ValorNum = Linea.find(Separador, NumPos + 1);
            Valor = Linea.substr(NumPos + 1,ValorNum);
            Valor = Valor.substr(0, Valor.find_first_of(Separador));
            TempBuff.push_back(Valor);
            NumPos = ValorNum;
            TotalEspacios++;
        }
        TotalVector = TempBuff.size();
    }
    else {
        //TempBuff.push_back(Linea.substr(0, Linea.find_first_of(Separador)));
        TotalVector = 0;
    }
}

int main(){
	valoresIniciales();
	return 0;
}
void valoresIniciales()
{
	system("cls");
	int opcion;
	menu();
	cin>>opcion;
	opcionSeleccionada(opcion);
}
void opcionSeleccionada(int op)
{
	switch(op){
		case 1:
			 Ingresar();
		break;
		case 2:
			 Modificar();
		break;
		case 3:
			 Eliminar();
		break;
		default:
			cout<<"Opcion no valida";
		break;
	}
}
void menu()
{
	cout<<"Bienvenido a mi Programa"<<endl;
	cout<<"Seleccione entre las siguientes opciones"<<endl;
	cout<<"1.Ingresar Producto"<<endl;
	cout<<"2.Modificar Producto"<<endl;
	cout<<"3.Eliminar Producto"<<endl;
}

void Ingresar()
{
	system("cls");
	mostrarMarca();
	string codig,desc,idmarca,r;
	float precioc,preciov;
	
	time_t curr_time;
	tm * curr_tm;
	char date_string[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
	strftime(date_string, 50, "%d/%m/%y-%X", curr_tm);	
	
	cout<<"Ingrese el codigo del producto"<<endl;
	cin>>codig;
	cout<<"Ingrese el nombre del producto"<<endl;
	cin>>desc;
	cout<<"Ingrese el codigo de la marca"<<endl;
	cin>>idmarca;
	cout<<"Ingrese el precio de compra"<<endl<<"Q";
	cin>>precioc;
	cout<<"Ingrese el precio de venta"<<endl<<"Q";
	cin>>preciov;
	//Funcion que verifica si es numero
	
	if(esNumerico(codig)){
		if(VeririficarRepetido(codig)){
			cout<<"Error-- Ya ha utilizado este codigo"<<endl;
			system("pause");
			Ingresar();
		}else{	
		if(Existe(idmarca)){
		//cout<<s;
		IngresarDb(codig,desc,idmarca,precioc,preciov,date_string);
		}else{
			cout<<"Error-- No existe la marca"<<endl;	
			//Ingresar();
		} 
		}
	}
	else{
		cout<<"Error-- el codigo debe ser numerico"<<endl;
		system("pause");
		Ingresar();
	}
}
void IngresarDb(string cod, string des,string idm,float prec, float prev,char const * time){
ofstream archivo;
	char continuar;
	archivo.open(nombre_archivopro,ios::app);
	
	if(archivo.fail()){
	cout<<"Error de archivo";
	}else
	{
	fflush(stdin);
	system("cls");
	archivo<<endl<<cod<<" "<<des<<" "<<idm<<" "<<prec<<" "<<prev<<" "<<time;
	cout<<"Registro Guardado exitosamente"<<endl;
	mostrarProducto();
	cout<<"¿Continuar s/n?"<<endl;
	cin>>continuar;
	archivo.close();
		if(continuar=='s'||continuar=='S'){
			Ingresar();		
		}else{
			valoresIniciales();
		}
	}	
}

void Eliminar(){ 
	system("cls");
 	string codig,desc,idmarca,r;
	float precioc,preciov;
	
 	mostrarProducto();
 	cout<<"Ingrese el codigo que desea modificar"<<endl;
	cin>>codig;
 	
	
 if(Existe(codig)){
 	if(VeririficarRepetido(idmarca)){
 		eli(codig);
	 }
	 else{
	 	cout<<"ERROR-- La marca no existe";
	 	system("pause");
		Eliminar();
	 }
 }else{
 	cout<<"Error-- El codigo no existe"<<endl;
 	system("pause");
	Eliminar();
 } 
}
void eli(string cod){
	ofstream aux;
	ifstream archivo;
	char Salir;
	string contenido;
	bool encontrado = false;
	
	archivo.open(nombre_archivopro,ios::in);
	aux.open(nombre_auxiliarpro,ios::out);
	
	if(archivo.fail()){
		cout<<"Archivo no encontrado"<<endl;
		exit(1);
	}else{		
		system("cls");
		do{
			getline(archivo,contenido);
			if(contenido.find(cod) != std::string::npos)
			{
			aux<<"";
			}
			else{
				aux<<contenido<<endl;
			}
			
		}while(archivo.eof()==false);
		archivo.close();
		aux.close();
		remove(nombre_archivopro);
		rename(nombre_auxiliarpro,nombre_archivopro);
		cout<<"Registro Eliminado de forma exitosa"<<endl<<endl<<endl;
		system("pause");
		mostrarProducto();
		valoresIniciales();
}
}
bool esNumerico(string linea) 
{
   bool b = true;
   int longitud = linea.size();
 
   if (longitud == 0) { // Cuando el usuario pulsa ENTER
      b = false;
   } else if (longitud == 1 && !isdigit(linea[0])) {
      b = false;
   } else {
      int i;
      if (linea[0] == '+' || linea[0] == '-')
         i = 1;
      else
         i = 0;
 
      while (i < longitud) {
         if (!isdigit(linea[i])) {
            b = false;
            break;
         }
         i++;
      }
   }
   return b;
}
bool VeririficarRepetido(string codi){
	int conteo;
	ifstream archivo;
	string contenido;
	archivo.open(nombre_archivopro,ios::in);
	if(archivo.fail()){
		cout<<"Error de archivo"<<endl;
		exit(1);
	}else{
		while(archivo.eof()==false){
		//obtengo la fila del archivo y la almaceno en la variable
			//contenido
				getline(archivo,contenido);
			    if(contenido=="" || contenido==" "){
				}else{
				vector<string> TempBuff(0);
				//creo un array para almacenar todos los string
			    int TotalVector;
				//TotalVector almacena la cantidad de palabras almacenadas
				split(contenido, *" ",  TempBuff, TotalVector);
				//Funcion split particiona un string y los agrega al array
				if(TempBuff[0]==codi){
				//Verificamos si la primera palabra es igual al codigo
					conteo++;
					//si es asi creamos un contador
				}
				}
					
		}
		//va a hacer en todas las filas del archivo
		
	}
	archivo.close();
	//Cierra el archivo
	if (conteo>0){
		//Si el contador es mayor a 0 retorna true
		return true;
	}else{
		//Si el contador es igual a 0 retorna false
		return false;
	}
}
void Modificar(){
 system("cls");
 string codig,desc,idmarca,r;
	float precioc,preciov;
	
	time_t curr_time;
	tm * curr_tm;
	char date_string[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
	strftime(date_string, 50, "%d/%m/%y-%X", curr_tm);
 mostrarProducto();
 	cout<<"Ingrese el codigo que desea modificar"<<endl;
	cin>>codig;
 	cout<<"Ingrese el nuevo nombre"<<endl;
 	cin>>desc;
 	cout<<"Ingrese el codigo de la marca"<<endl;
	cin>>idmarca;
	cout<<"Ingrese el precio de compra"<<endl<<"Q";
	cin>>precioc;
	cout<<"Ingrese el precio de venta"<<endl<<"Q";
	cin>>preciov;
	
 if(Existe(codig)){
 	if(VeririficarRepetido(idmarca)){
 		mod(codig,desc,idmarca,precioc,preciov,date_string);
	 }
	 else{
	 	cout<<"ERROR-- La marca no existe";
	 }
 }else{
 	cout<<"Error-- El codigo no existe"<<endl;
 	system("pause");
	Modificar();
 } 
}
bool Existe(string codi){
	int conteo;
	ifstream archivo;
	string contenido;
	archivo.open(nombre_archivo,ios::in);
	if(archivo.fail()){
		cout<<"Error de archivo"<<endl;
		exit(1);
	}else{
		while(archivo.eof()==false){
		//obtengo la fila del archivo y la almaceno en la variable
			//contenido
				getline(archivo,contenido);
			    if(contenido=="" || contenido==" "){
				}else{
				vector<string> TempBuff(0);
				//creo un array para almacenar todos los string
			    int TotalVector;
				//TotalVector almacena la cantidad de palabras almacenadas
				split(contenido, *" ",  TempBuff, TotalVector);
				//Funcion split particiona un string y los agrega al array
				if(TempBuff[0]==codi){
				//Verificamos si la primera palabra es igual al codigo
					conteo++;
					//si es asi creamos un contador
				}
				}
					
		}
		//va a hacer en todas las filas del archivo
		
	}
	archivo.close();
	//Cierra el archivo
	if (conteo>0){
		//Si el contador es mayor a 0 retorna true
		return true;
	}else{
		//Si el contador es igual a 0 retorna false
		return false;
	}
}
void mostrarMarca(){
	int conteo;
	ifstream archivo;
	string contenido;
	archivo.open(nombre_archivo,ios::in);
	if(archivo.fail()){
		cout<<"Error de archivo"<<endl;
		exit(1);
	}else{
		while(archivo.eof()==false){
		//obtengo la fila del archivo y la almaceno en la variable
			//contenido
				getline(archivo,contenido);
			    if(contenido=="" || contenido==" "){
				}else{
				cout<<contenido<<endl;
				}
				}
		}
		//va a hacer en todas las filas del archivo
}
void mostrarProducto(){
	int conteo;
	ifstream archivo;
	string contenido;
	archivo.open(nombre_archivopro,ios::in);
	if(archivo.fail()){
		cout<<"Error de archivo"<<endl;
		exit(1);
	}else{
		while(archivo.eof()==false){
		//obtengo la fila del archivo y la almaceno en la variable
			//contenido
				getline(archivo,contenido);
			    if(contenido=="" || contenido==" "){
				}else{
				cout<<contenido<<endl;
				}
				}
		}
		//va a hacer en todas las filas del archivo
}

void mod(string cod, string des,string idm,float prec, float prev,char const * time){
	ofstream aux;
	ifstream archivo;
	char Salir;
	string contenido;
	archivo.open(nombre_archivopro,ios::in);
	aux.open(nombre_auxiliarpro,ios::out);
	
	if(archivo.fail()){
		cout<<"Archivo no encontrado"<<endl;
		exit(1);
	}else{		
		system("cls");
		do{
			getline(archivo,contenido);
			if(contenido.find(cod) != std::string::npos)
			{
			aux<<cod<<" "<<des<<" "<<idm<<" "<<prec<<" "<<prev<<" "<<time<<endl;
			}
			else{
				aux<<contenido<<endl;
			}
			
		}while(archivo.eof()==false);
		archivo.close();
		aux.close();
		remove(nombre_archivopro);
		rename(nombre_auxiliarpro,nombre_archivopro);
		cout<<"Registro Modificado de forma exitosa"<<endl<<endl<<endl;
		mostrarProducto();	
		system("pause");
		valoresIniciales();
	}
}
