#include <iostream>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Factura{
	int no_factura; 
	int nit_info;
	char nombre_info[50];
	char direccion_info[50];
	char date_string[100];
};

void menu();
void opcionSeleccionada(int);
void IngresarDet();
void mostrar();
void mostrarFactura();
void mostrarProducto();
bool ExistePro(string);
bool ExisteFac(string);
float retornarTotal(string);
//la direccion del archivo para almacenar y hacer cambios
const char *nombre_archivo="../Base de Datos/factura_detalle.txt";
const char *nombre_archivomar="../Base de Datos/Marcas.txt";
const char *nombre_archivopro="../Base de Datos/Productos.txt";
const char *nombre_archivofac="../Base de Datos/factura.txt";
 
const int conteo=0;
bool esNumerico(string); 
bool VeririficarRepetido(string);
void ingresar_DetArchivo(string,string,string,float,float);
void valoresIniciales();


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

int main() 
{	
//	Creamos una funcion llamada valoresIniciales que es el menu y las opciones
	valoresIniciales();
	return 0;
} 
void valoresIniciales(){
	system("cls");
	int opcion;
	menu();
	cin>>opcion;
	opcionSeleccionada(opcion);
}
void opcionSeleccionada(int op){
	switch(op){
		case 1:
			 IngresarDet();
		break;
		default:
			cout<<"Opcion no valida";
		break;
	}
}
void menu(){
	cout<<"Bienvenido a mi Programa"<<endl;
	cout<<"Seleccione entre las siguientes opciones"<<endl;
	cout<<"1.Ingresar detalle factura"<<endl;

}
void IngresarDet(){
	system("cls");
	mostrarFactura();
	cout<<endl;
	mostrarProducto();
	string codig, marc;
	string codipro, desc, nfac;
	float precioc, total,preciov;
	char time[100];
	int cont=0;
	cout<<" "<<endl;
	cout<<"No. Factura"<<endl;
	cin>>nfac;
	cout<<"Ingrese el codigo de producto"<<endl;
	cin>>codipro;
	ifstream archivo;
	 archivo.open(nombre_archivopro,ios::in);
	 //archivo>>codig>>desc>>marc>>precioc>>preciov>>time;
	if(archivo.fail()){
		cout<<"Error de archivo"<<endl;
		exit(1);
	}else{
		while(archivo.eof()==false){
		archivo>>codig>>desc>>marc>>precioc>>preciov>>time;
			if(codipro==codig){
				//cont=1;
				float total=retornarTotal(nfac);
				cout<<"Nombre del producto"<<endl;
				cout<<desc<<endl;
				cout<<"Precio"<<endl;
				cout<<precioc<<endl;
				cout<<"Total"<<endl;
				total=precioc+total;
				cout<<total<<endl;
				system("pause");
				
				if(esNumerico(codipro)){
					if(nfac == "n"){
						cout<<"Error-- Ya ha utilizado esta factura"<<endl;
						system("pause");
						valoresIniciales();
					}else{	
						if(ExisteFac(nfac)){
							if(ExistePro(codipro)){
								//cout<<s;
								ingresar_DetArchivo(nfac,codipro,desc,precioc,total);
							}else{
								cout<<"Error-- No existe ese producto"<<endl;	
								IngresarDet();
							} 
						}else{
							cout<<"Error-- No existe esa factura"<<endl;	
							//IngresarDet();	
						}
					}
				}else{
					cout<<"Error-- el codigo debe ser numerico"<<endl;
					system("pause");
					IngresarDet();
				}
			}
		}
		//archivo.close();
	}
	
}

float retornarTotal(string codfact){
	float conteo=0;
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
			    if(contenido=="" || contenido==" " || contenido=="****************************************"){
				}else{
				vector<string> TempBuff(0);
				//creo un array para almacenar todos los string
			    int TotalVector;
				//TotalVector almacena la cantidad de palabras almacenadas
				split(contenido, *" ",  TempBuff, TotalVector);
				//Funcion split particiona un string y los agrega al array
				if(TempBuff[0]==codfact){
				//Verificamos si la primera palabra es igual al codigo
					float recolector;
					if(istringstream(TempBuff[3])>>recolector){
					conteo = conteo+recolector;	
					}
					
					 
					//si es asi creamos un contador
				}
				}			
		}
		}
return conteo;
}
bool operator==(const string str, int number) {
    stringstream ss(str);
    int strAsInt;
    ss>>strAsInt;
    return (strAsInt == number);
}

bool operator==(int number, const string str) {
    return (str == number);
}


bool ExisteFac(string codi){
	int conteo;
	ifstream archivo;
	string contenido;
	Factura f;
	archivo.open(nombre_archivofac,ios::in);
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
				if(TempBuff[0]==(codi == f.no_factura)){
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

bool ExistePro(string codi){
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

void ingresar_DetArchivo(string nfac, string codipro, string desc, float precioc, float total){
	ofstream archivo;
	char continuar;
	archivo.open(nombre_archivo,ios::app);
	
	if(archivo.fail()){
	cout<<"Error de archivo";
	}else{
	
	fflush(stdin);
	system("cls");
	archivo<<endl<<nfac<<" "<<codipro<<" "<<desc<<" "<<precioc<<" "<<total<<endl;
	cout<<"Registro Guardado exitosamente"<<endl;
	cout<<"¿Continuar s/n?"<<endl;
	cin>>continuar;
		if(continuar=='s'||continuar=='S'){
			IngresarDet();		
		}else{
			archivo<<"****************************************"<<endl;
			valoresIniciales();
		}
			archivo.close();
	}
}

bool VeririficarRepetido(string codi){
	if(codi == "n"){
		valoresIniciales();
	}else{
		
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

void mostrarFactura(){
	FILE* archivo = fopen(nombre_archivofac, "rb");
	if(!archivo) {
		archivo = fopen(nombre_archivofac, "w+b");
	}
	Factura fac;
	fread(&fac, sizeof(Factura), 1,archivo);
	do{
		cout<<"\n";
		cout<<"No. factura: "<<fac.no_factura<<" ";
		cout<<"Fecha de emision: "<<fac.date_string<<" ";
		cout<<"NIT: "<<fac.nit_info;
		printf("\n");
	fread(&fac, sizeof(Factura), 1,archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
	
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

void mostrar(){
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
