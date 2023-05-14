#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

struct Producto{  //Se crea la estructura del producto
	int CodigoUnico;
	string Nombre;
	string FechaDeCompra;
	float PrecioDeCompra;
	float PrecioDeVenta;
	float Descuento;
};

bool ComprobarFechaRepetida(vector<Producto> ListaDeProductos, string fecha, int codigo){ //Funcion para comprobar registros de un mismo producto en la misma fecha
	
	for(int i = 0; i < ListaDeProductos.size(); i++ ){
		if(ListaDeProductos[i].FechaDeCompra == fecha && ListaDeProductos[i].CodigoUnico == codigo){
			return true;
		}
	}
	
	return false;
}

Producto SolicitarInformacion(vector<Producto> ListaDeProductos){ //Funcion que solicita la informacion del nuevo producto
	
	Producto ProductoAuxiliar;
	while(true){
	
		cout << "Ingresa el codigo del producto: ";
		cin >> ProductoAuxiliar.CodigoUnico;
		
		cout <<"Ingresa el nombre del producto: ";
		cin >> ProductoAuxiliar.Nombre;
		
		while(true){ //Ciclo que comprueba el correcto formato de la fecha
		
			cout << "Por favor ingresa la fecha en formato DD/MM/AAAA." << endl;
			cout << "Ingresa la fecha: ";
			cin >> ProductoAuxiliar.FechaDeCompra;
			
			if(ProductoAuxiliar.FechaDeCompra.size() == 10){
				break;
			}
			else{
				cout << "===========================================================================" << endl;
				cout << "¡Fecha invalida! Recuerda agregar un 0 antes de los dias o los meses de ser necesario.";
				cout << "===========================================================================" << endl;
			}
		}
		
		if(ComprobarFechaRepetida(ListaDeProductos, ProductoAuxiliar.FechaDeCompra, ProductoAuxiliar.CodigoUnico)){ //Se llama a la funcion para comprobar fecha repetida
			cout << "============================================" << endl;
			cout << "Esta Fecha ya ha sido registrada para este producto, vuelve a hacer el registro" << endl;
			cout << "============================================" << endl;
			continue;
		}
		
		cout << "Ingresa el valor de compra del producto: ";
		cin >> ProductoAuxiliar.PrecioDeCompra;
		
		cout << "Ingresa el valor de venta del producto: ";
		cin >> ProductoAuxiliar.PrecioDeVenta;
		
		cout << "Ingresa el valor del descuento (Si no hay ingresa 0): ";
		cin >> ProductoAuxiliar.Descuento;
	
		break;
	
	}
	return ProductoAuxiliar; //Se retorna un producto para agregar a la lista de registros
}

bool ComprobarExistenciaCodigo(vector<Producto> ListaDeProductos, int codigo){ //Funcion para comprobar si un codigo existe en la lista de productos
	
	for(int i = 0; i < ListaDeProductos.size(); i++ ){
		if(ListaDeProductos[i].CodigoUnico == codigo){
			return true;
		}
	}
	
	return false;
}

void imprimirInfo(char tipo, Producto productoAuxiliar){ //Funcion que imprime la informacion dependiendo de si es el balance de utilidad o un registro
	
	if(tipo == 'U'){
		
		double utilidad = ((productoAuxiliar.PrecioDeVenta-productoAuxiliar.Descuento)-productoAuxiliar.PrecioDeCompra)/productoAuxiliar.PrecioDeCompra;
		
		utilidad = round(utilidad*1000)/10;
		
		cout << setw(15) << productoAuxiliar.FechaDeCompra << setw(2) << "|" << setw(14) << productoAuxiliar.PrecioDeCompra << setw(2) << "|"
		<< setw(13) << productoAuxiliar.PrecioDeVenta << setw(2) << "|" << setw(11) << productoAuxiliar.Descuento<< setw(2) << "|" << 
		setw(12) << utilidad << setw(2) << endl;
	}
	else{
		cout << "============================================" << endl;
		cout << setw(20) << "Codigo de Producto" << setw(2) << "|" << setw(20) << productoAuxiliar.CodigoUnico << endl;
		cout << "============================================" << endl;
		cout << setw(20) << "Nombre de Producto" << setw(2) << "|" << setw(20) << productoAuxiliar.Nombre << endl;
		cout << "============================================" << endl;
		cout << setw(20) << "Fecha de Compra" << setw(2) << "|" << setw(20) << productoAuxiliar.FechaDeCompra << endl;	
		cout << "============================================" << endl;
		cout << setw(20) << "Valor de Compra" << setw(2) << "|" << setw(20) << productoAuxiliar.PrecioDeCompra << endl;
		cout << "============================================" << endl;
		cout << setw(20) << "Valor de Venta" << setw(2) << "|" << setw(20) << productoAuxiliar.PrecioDeVenta << endl;
		cout << "============================================" << endl;
		cout << setw(20) << "Valor del Descuento" << setw(2) << "|" << setw(20) << productoAuxiliar.Descuento << endl;
		cout << "============================================" << endl;
	}
}

//Funcion principal
int main(){ 
	vector<Producto> ListaDeProductos;
	char seguir;
	
	for(int i = 0; i < 20  ; i++){ //Ciclo que agrega los nuevos productos hasta un maximo de 20
		
		ListaDeProductos.push_back(SolicitarInformacion(ListaDeProductos));	
		
		imprimirInfo('R', ListaDeProductos[i]);
		
		cout << "Deseas continuar ingresando datos(S/N): " ;
		cin >> seguir;
		
		if(seguir == 'N'){
			cout << "============================================" << endl;
			break;
		}
		
		cout << "============================================" << endl;
		
	}
	
	int codigo;
	string Nombre;
	
	while(true){            // Ciclo que da la opcion de ver un balace de utilidad de un producto en particular
		cout << "Desea ver el balance general de algun registro? (S/N): ";
        cin >> seguir;
        cout << "===========================================================================" << endl;
        if(seguir == 'S'){ //Ciclo que pide el codigo y comprueba si existe
        	while(true){
				cout << "Ingrese el codigo del producto: ";
        		cin >> codigo;
        		cout << "============================================" << endl;
			
				if(ComprobarExistenciaCodigo(ListaDeProductos,codigo)){
					break;
				}
				else{
					cout << "Ingrese un codigo valido" << endl;
					cout << "============================================" << endl;
				}
			}	
		}	
		else{
			break;
		}
		
		for(int i=0; i <= ListaDeProductos.size(); i++){ //Ciclo para encontrar el nombre del producto
			if(ListaDeProductos[i].CodigoUnico == codigo){
				Nombre = ListaDeProductos[i].Nombre;
			}
		}
		
		double valorPromedio;
		int cont;
		
		cout << "Codigo Producto " << codigo << endl;
		cout << "Nombre Producto " << Nombre << endl;
		cout << "===========================================================================" << endl;
		cout << setw(14) << "Fecha de Compra" << setw(2) << "|" << setw(14) << "Valor Compra" << setw(2) << "|"
		<< setw(13) << " Valor Venta" << setw(2) << "|" << setw(11) << "Descuento" << setw(2) << "|"<<setw(12) << "% Utilidad" << setw(2) << endl;
		cout << "===========================================================================" << endl;
		
		for(int i=0; i <= ListaDeProductos.size(); i++){ //Ciclo que encuentra en la lista de productos los registros con el codigo solicitado
			if(ListaDeProductos[i].CodigoUnico == codigo){
				imprimirInfo('U',ListaDeProductos[i]);
				cout << "===========================================================================" << endl;
				valorPromedio = valorPromedio+ListaDeProductos[i].PrecioDeVenta;
				cont = cont+1;
			}
			
		}
		
		cout << "El valor promedio de venta es: " << round(valorPromedio/cont*10)/10 << endl;  //Se imprime el valor promedio de venta
		cout << "===========================================================================" << endl;
	}
	
}	
