import math
import pandas as pd

def distancia(latUser, lonUser, latCompany, lonCompany):
  # Radio de la Tierra en kilómetros
  radio_tierra = 6371.795477598
  # Convertir las latitudes y longitudes a radianes
  latUser, lonUser, latCompany, lonCompany = map(math.radians, [latUser, lonUser, latCompany, lonCompany])

  # Calcular las diferencias de latitud y longitud
  d_lat = latCompany- latUser
  d_lon = lonCompany - lonUser

  # Aplicar la fórmula de Haversine
  a = math.sin(d_lat / 2)**2 + math.cos(latUser) * math.cos(latCompany) * math.sin(d_lon / 2)**2
  c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
  
  distancia = radio_tierra * c

  return distancia

def mostrarInfo(lista):
    #Funcion para mostrar la info, recibe una lista con las filas convertidas en diccionarios
    cont = 0
    for datos in lista:
        name = datos['Name']
        empleados = datos['Employees']
        sector = datos['Sector']
        distancia = datos['Distance']
        print(f'{cont+1}. {name} - {empleados} empleados - {sector} - {round(distancia,1)} km')
        cont+=1

    print('------------------------------------------------------------------------------------')

#Codigo general
datos = pd.read_csv("companies.csv")

print('------------------------------------------------------------------------------------')
#Se solicitan los daots necesario
latitud,longitud = input("Por favor, ingrese su ubicación actual en términos de latitud y longitud: ").split(',')
#Se convierte a numero decimal
latitud = float(latitud)
longitud = float(longitud)

Radio = float(input('Por favor indique el radio de busqueda: '))

print('Si lo desea, puede filtrar las empresas por sector y/o número mínimo de empleados.')
tipo = input('Por favor, ingrese el sector por el que desea filtrar, o presione Enter para omitir este filtro: ')
numeroEmpleados = input('Por favor, ingrese el número mínimo de empleados que desea que tenga cada empresa, o presione Enter para omitir este filtro: ')
#Solo si se ingreso un numero minimo de empleados se convierte a entero la variable, ya que si esta vacia daria un error
if numeroEmpleados:
    numeroEmpleados = int(numeroEmpleados)
print('------------------------------------------------------------------------------------')

lista = []
#Ciclo que recorre el data frame comprobando las distancias de cada empresa al puntodado
for i in range(len(datos)):
    fila = datos.iloc[i]
    LatitudE = float(fila['Latitude'])
    LongitudE = float(fila['Longitude'])
    distancia = distancia(latitud,longitud,LatitudE,LongitudE)
    
    #Se convierte la fila en diccionario
    filasecundaria = fila.to_dict()

    #Si la distancia es menor o igual al radio dado por el usuario y la empresa las condiciones (si es que las hay) se agrega
    #a la lista de diccionarios
    if distancia <= Radio:    
        if tipo:
            if tipo == fila['Sector']:
                if numeroEmpleados:
                    if numeroEmpleados <= fila['Employees']:
                        filasecundaria['Distance'] = distancia
                        lista.append(filasecundaria)
                else:
                    filasecundaria['Distance'] = distancia
                    lista.append(filasecundaria)
        else:
            filasecundaria['Distance'] = distancia
            lista.append(filasecundaria)

#Se llama a la funcion mostrar info no sin antes organizar de menor a mayor por las distancias de las empresas al putno de interes
mostrarInfo(sorted(lista, key=lambda p: p["Distance"]))