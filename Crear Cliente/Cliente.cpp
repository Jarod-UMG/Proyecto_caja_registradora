#include <iostream>
#include <stdio.h>  
#include <string.h> 

using namespace std;
const char *cliente_archivo = "cliente.dat";

struct Cliente{
	int nit_cliente;
	char nombre_cliente[50], direccion_cliente[50];
};

void ingresar_clientes();
void abrir_clientes();


int main (){
	//ingresar_clientes();
	abrir_clientes();
	
	return 0;	
}


void abrir_clientes(){
	system("cls");
	FILE* archivo_cliente = fopen(cliente_archivo, "rb");
	if(!archivo_cliente) {
		archivo_cliente = fopen(cliente_archivo, "w+b");
	}
	Cliente cliente;
	int n_factura=0;
	fread ( &cliente, sizeof(Cliente), 1, archivo_cliente );
	cout<<"____________________________________________________________________"<<endl;
	cout << "id" <<"|"<< "CODIGO" <<"|"<< "NOMBRE"<<" "<<endl;	
		do{
		cout<<"____________________________________________________________________"<<endl;
		cout << n_factura <<" |  "<< cliente.nit_cliente <<" | "<< cliente.nombre_cliente<<" | "<<cliente.direccion_cliente<<" "<<endl;
        
        
		fread ( &cliente, sizeof(Cliente), 1, archivo_cliente );
		n_factura += 1;	
		} while (feof( archivo_cliente ) == 0);
		
    cout<<endl;
    
		fclose(archivo_cliente);
}

void ingresar_clientes(){
	
	char continuar;
	FILE* archivo_cliente = fopen(cliente_archivo, "ab"); // ab
	
	
	Cliente cliente;
		 string nit, nombre, direccion;
		do{
			fflush(stdin);
			
			
			cout<<"Ingrese le nit del cliente: ";
		cin>>cliente.nit_cliente;
        cin.ignore();
        
		//cout<<"Ingrese el nit: ";
		//getline(cin,nit);
    	//strcpy(cliente.nit_cliente, nit.c_str()); 
    	
    	cout<<"Ingrese el Nombre: ";
		getline(cin,nombre);
    	strcpy(cliente.nombre_cliente, nombre.c_str()); 
        
		cout<<"Ingrese la direccion: ";
		getline(cin,direccion);
    	strcpy(cliente.direccion_cliente, direccion.c_str()); 
			
		
		
		fwrite( &cliente, sizeof(Cliente), 1, archivo_cliente );
		
		cout<<"Desea Agregar otro s/n : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );
		
	
	fclose(archivo_cliente);
	abrir_clientes();
		
}
