import pandas as pd
import math

#Funcion para calcular la distancia entre dos puntos en una esfera
def calcularDistancia(latitudUsuario,longitudUsuario,latitudEmpresa,longitudEmpresa):
    #Convertimos todas las longitudes y latitudes de grados a radianes
    latitudUsuario = math.radians(latitudUsuario)
    longitudUsuario = math.radians(longitudUsuario)
    latitudEmpresa = math.radians(float(latitudEmpresa))
    longitudEmpresa = math.radians(float(longitudEmpresa))

    r = 6371 #El radio equivolumen de la tierra en kilometros

    #usamos la formula de Haversine

    #Calculamos el diferencial de las latitudes y las longitudes
    dlat = latitudUsuario-latitudEmpresa
    dlon = longitudUsuario-longitudEmpresa

    #Calculamos las constantes a y c
    a = math.sin(dlat/2)**2+ math.cos(latitudEmpresa)*math.cos(latitudUsuario)* math.sin(dlon/2)**2
    c = 2*math.asin(math.sqrt(a))

    return r*c

#Codigo general
datos = pd.read_csv("companies.csv")

#Solicitamos informacion al usuario

latitud,longitud = input("Por favor, ingrese su ubicación actual en términos de latitud y longitud: ").split(',')
latitud = float(latitud)
longitud = float(longitud)

Radio = float(input('Por favor indique el radio de busqueda: '))

print('Si lo desea, puede filtrar las empresas por sector y/o número mínimo de empleados.')
tipo = input('Por favor, ingrese el sector por el que desea filtrar, o presione Enter para omitir este filtro: ')
numeroEmpleados = input('Por favor, ingrese el número mínimo de empleados que desea que tenga cada empresa, o presione Enter para omitir este filtro: ')
if numeroEmpleados:
    numeroEmpleados = int(numeroEmpleados)
print('------------------------------------------------------------------------------------')

listaColumna = []

for i in range(len(datos)):
    fila = datos.iloc[i]
    LatitudE = float(fila['Latitude'])
    LongitudE = float(fila['Latitude'])

    distancia = calcularDistancia(latitud,longitud,LatitudE,LongitudE)

    print(distancia)
