#include <iostream>
#include <stdio.h>  
#include <ctime>
#include <ctime>
#include <vector>
#include <string.h> 
#include <conio.h>
#include <fstream>
#include <conio.h>

using namespace std;
const char *factura_archivo = "../Base de Datos/factura.txt";
const char *cliente_archivo = "../Base de Datos/cliente.txt";

int indice=0,pos=0,cod=0;

struct Factura{
	int no_factura; 
	int nit_info;
	char nombre_info[50];
	char direccion_info[50];
	char date_string[100];
};

struct Cliente{
	int nit_cliente;
	char nombre_cliente[50], direccion_cliente[50];
};

void ingresar_clientes_factura(int code){
	FILE* archivo_cliente = fopen(cliente_archivo, "ab"); 
	
	Cliente cliente;
		 string nit, nombre, direccion;
	
			fflush(stdin);

		cliente.nit_cliente=code;
        cin.ignore();

    	cout<<"Nombre del cliente: ";
		getline(cin,nombre);
    	strcpy(cliente.nombre_cliente, nombre.c_str()); 
        
		cout<<"Direccion del cliente: ";
		getline(cin,direccion);
    	strcpy(cliente.direccion_cliente, direccion.c_str()); 
			
		fwrite( &cliente, sizeof(Cliente), 1, archivo_cliente );
	
	fclose(archivo_cliente);
}

void buscar_codigo(int codo){
FILE* archivo_cliente = fopen(cliente_archivo, "rb");
	bool encontrado=false;
	
	Cliente cliente;
	fread(&cliente, sizeof(Cliente), 1, archivo_cliente);
		
		while (feof( archivo_cliente ) == 0){
			
			if (cliente.nit_cliente == codo){
				encontrado=true;
			pos = indice;
			}
	
		fread(&cliente, sizeof(Cliente), 1, archivo_cliente);
		indice += 1;
		} 
		 	if(encontrado==true){
		 
	fseek ( archivo_cliente,pos * sizeof(Cliente), SEEK_SET );

    fread(&cliente, sizeof(Cliente), 1, archivo_cliente);

        cout << "Nombre del cliente: " <<cliente.nombre_cliente<<endl;
        cout << "Direccion del cliente: " << cliente.direccion_cliente <<endl;
    }
    if(encontrado==false){
	
cout<<"El cliente no se encuentra resitrado, presione enter para hacerlo ";	
    	ingresar_clientes_factura(codo);
}
	
	fclose(archivo_cliente);
}

void fecha(){
	char continuar;
	char finalizar;
	FILE* archivo = fopen(factura_archivo, "ab");
	Factura fac;
	Cliente cliente;
	fac.no_factura=0;
	do{
	time_t curr_time;
	tm * curr_tm;
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
	strftime(fac.date_string, 50, "%d/%m/%y-%X", curr_tm);
		printf("Fecha: %s", fac.date_string);
		fac.no_factura+=1;
		
		cout<<"\t\tNo. de factura: "<<fac.no_factura<<endl;
		
		cout<<"-----------------------------Info del cliente--------------------------"<<endl;
			cout<<"NIT: ";
			cin>>fac.nit_info;
		buscar_codigo(fac.nit_info);
		fwrite(&fac, sizeof(Factura), 1,archivo);
		cout<<"\nDesea agregar otra factura s/n : ";
		cin>>continuar;
	}while((continuar=='s') || (continuar=='S') );
	fclose(archivo);
}


void ver_datos_factura(){
	FILE* archivo = fopen(factura_archivo, "rb");
	if(!archivo) {
		archivo = fopen(factura_archivo, "w+b");
	}
	Factura fac;
	fread(&fac, sizeof(Factura), 1,archivo);
	do{
		cout<<"\n";
		cout<<"No. factura: "<<fac.no_factura<<endl;
		cout<<"Fecha de emision: "<<fac.date_string<<endl;
		cout<<"NIT: "<<fac.nit_info<<endl;
		printf("\n");
	fread(&fac, sizeof(Factura), 1,archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
	
}
/*
void clientes_data(){
	FILE* archivo = fopen(cliente_archivo, "rb");
	if(!archivo) {
		archivo = fopen(cliente_archivo, "w+b");
	}
	Cliente cliente;
	fread(&cliente, sizeof(Cliente), 1,archivo);
	do{
		cout<<"\n";
        cout << "Nombre del cliente: " <<cliente.nombre_cliente<<endl;
        cout << "Direccion del cliente: " << cliente.direccion_cliente <<endl;
        cout << "NIT del cliente: " << cliente.nit_cliente <<endl;
		printf("\n");
	fread(&cliente, sizeof(Cliente), 1,archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
}*/

main(){
	//clientes_data();
	fecha();
	ver_datos_factura();
}
