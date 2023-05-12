#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

//Definimos la estructura del producto

struct Producto{
    string codigo;
    string nombre;
    string fechaCompra;
    float valorCompra;
    float valorVenta;
    float descuento;
};

//Esta funcion agrega los espacios faltantes para que la tabla de utilidades tenga bonita forma( se puede eliminar e imprimir todo en linea
string espacios(int num,int espacios){

	stringstream ss;
	ss << num; //Usamos una libreria para convertir el numero a string y agregar los espacios faltantes
	string str=ss.str(); 
	
	int faltantes = espacios - str.size();
	
	for(int i = 0; i <faltantes ; i++ ){
		str = str + " "; // agregamos un espacio en blanco n veces
	}	
	
	return str;
};


//Si falta algun 0 en la fecha se lo agregamos para poder comparar bien las fechas (Pueden eliminar esta funcion)
string formatearFecha(string fecha){
	string fechaFinal;
	vector<string> componentes;
    
    //Usamos un ciclo para separar los dias y los meses y los años
    for(int i = 0; i<2; i++){
    	int pos = fecha.find("/");
    	componentes.push_back(fecha.substr(0,pos));
    	fecha.erase(0,pos+1);
	}
	
	componentes.push_back(fecha);
	//Comprobamos que los dias tengan dos caracteres y sino agregamos un 0 adelante
	if(componentes[0].size() ==1){
		componentes[0] = "0"+componentes[0];
	}
	//Comprobamos que los meses tengan dos caracteres y sino agregamos un 0 adelante
	if(componentes[1].size() ==1){
		componentes[1] = "0"+componentes[1];
	}
    
    //unimos de nuevo la fecha
    fechaFinal = componentes[0]+"/"+componentes[1]+"/"+componentes[2] ;
    
    return fechaFinal; 
};


// Funcion para imprimir el ultimo registro de venta
void imprimirRegistro(Producto producto){
	
	cout << "------------------------------------\n";
	cout << " Codigo producto  | " << producto.codigo << "\n";
	cout << "------------------------------------\n";
	cout << " Nombre producto  | " << producto.nombre << "\n";
	cout << "------------------------------------\n";
	cout << " Fecha producto   | " << producto.fechaCompra << "\n";
	cout << "------------------------------------\n";
	cout << " Valor de Compra  | $" << producto.valorCompra << "\n";
	cout << "------------------------------------\n";
	cout << " Valor de Venta   | $" << producto.valorVenta << "\n";
	cout << "------------------------------------\n";
	cout << " Descuento        | $" << producto.descuento <<"\n";
	cout << "------------------------------------\n";
	
};

// Funcion para comprobar que no haya otro registro con la misma fecha
bool comprobarFecha(map<string, vector<Producto> >& Dic ,string fecha, string codigo){
	if(Dic.find(codigo) != Dic.end()){
		for(int i = 0 ; i < Dic[codigo].size(); i++ ){
			if(Dic[codigo][i].fechaCompra == fecha){
				return true;	
			}
		}
	}
	
	return false;	
};

//Funcion que calcula la utilidad de un registro de venta
float calcularUtilidad(Producto& producto){
	float utilidad = ((producto.valorVenta-producto.descuento)-producto.valorCompra)/producto.valorCompra ;
	
	return utilidad*100;

};
	
//Codigo principal
int main(){
	//Definimos el diccionario que contiene una lista con los registros de un producto
	map<string, vector<Producto> > mapProductos;
    int numRegistros = 0;
    char continuar = 'S';
	
	//Recolectamos los datos hasta un maximo de 20
    while(numRegistros <20 && continuar == 'S'){

    	cout << "Ingrese los datos del producto #" << numRegistros + 1 << ":" << endl;
    	
		//Definimos un nuevo producto
		Producto producto;
		
		//Solicitamos el codigo del producto
		cout << "Ingresa el codigo del producto: ";
		cin >> producto.codigo;
		
		//Solicitamos el nombre del producto
		cout << "Ingresa el nombre del producto: ";
		cin >> producto.nombre;
		
		string fechaprueba;
		
		//Solicitamos la fecha de venta
		cout << "Ingresa el la fecha de la venta del producto : ";
		cin >> fechaprueba;
		
		producto.fechaCompra = formatearFecha(fechaprueba);
			
		if(comprobarFecha(mapProductos, producto.fechaCompra, producto.codigo)){
			cout << "------------------------------------\n";
			cout << "Este producto tiene otro registro con la misma fecha de compra. Ingrese una fecha valida." << endl;
			cout << "------------------------------------\n";	
			continue;
		}
			
		//Solicitamos el valor de compra del producto
		cout << "Valor de compra del producto: $";
		cin >> producto.valorCompra;
		
		//Solicitamos el valor de venta del producto
		cout << "Valor de venta del producto: $";
		cin >> producto.valorVenta;
		
		//Solicitamos el valor del descuento 
		cout << "Ingresa el valor del descuento (0 si no hubo): $";
		cin >> producto.descuento;
		
		cout << "------------------------------------\n";
				
		mapProductos[	producto.codigo].push_back(producto);
		numRegistros++;
		
		
		imprimirRegistro(producto);
		
		cout << "Desea ingresar otro registro? (S/N): ";
        cin >> continuar;
        
        cout << "------------------------------------\n";
        
	}
    
    continuar = 'S';
    string codigo;
    
    //Ciclo para sacar balances de utilidad
    while(continuar == 'S'){
    	cout << "Desea ver el balance general de algun registro? (S/N): ";
        cin >> continuar;
        cout << "------------------------------------\n"; 
        
        if(continuar == 'S'){
        	while(true){
				cout << "Ingrese el codigo del producto: ";
        		cin >> codigo;
        		cout << "------------------------------------\n";
				//Comprobamos que el codigo exista, sino pedimos un codigo valido
				if(mapProductos.find(codigo) != mapProductos.end()){
					break;
				}
				else{
					cout << "Ingrese un codigo valido";
					cout << "------------------------------------\n"; 
				}
			}	
		}	
		else{
			break;
		}
		
		//imprimos la informacion general de la tabla de balance
		cout << "Codigo Producto " << codigo << endl;
		cout << "Nombre Producto " << mapProductos[codigo][0].nombre << endl;
		cout << "-----------------------------------------------------------------------\n";
		cout << "Fecha de Compra | Valor Compra | Valor Venta | Descuento | % Utilidad  \n";
		cout << "-----------------------------------------------------------------------\n";
		
		int sumaPrecioVenta = 0;
		
		// Iteramos los registros de un mismo producto y los estilizamos
		for(int i = 0; i < mapProductos[codigo].size();i++){
			cout  << " " << mapProductos[codigo][i].fechaCompra << "     | " << espacios(mapProductos[codigo][i].valorCompra,13)<< "| " <<	 espacios(mapProductos[codigo][i].valorVenta,12)<< "| "<< espacios(mapProductos[codigo][i].descuento,10) << "| " << setprecision(1) << fixed << calcularUtilidad(mapProductos[codigo][i]) << "%" << endl; 
			cout << "-----------------------------------------------------------------------\n";
			sumaPrecioVenta = sumaPrecioVenta + mapProductos[codigo][i].valorVenta;
		}
		cout << "------------------------------------\n"; 
		cout << "Promedio Precio venta: " << sumaPrecioVenta/mapProductos[codigo].size() << endl; //Calculamos el promedio de precio de venta
		cout << "------------------------------------\n"; 
	}
    
    return 0;
}
