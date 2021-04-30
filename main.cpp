#include <iostream>
#include "cyd.h"
using namespace std;

/*Programa que codifica y decodifica archivos por 2 metodos, el usuario al ejecutar el programa debera digitar
 el numero respectivo a las opciones que elija, 1 o 2 para codificar o decodificar y asi mismo para la eleccion
 de los metodos. Cuando se pide el numero entero, el usuario digitara un numero teniendo en cuenta que este cumple
 la funcion de separar los grupos de bits en esa cantidad que digito.Por ultimo al pedirle los nombres de los archivos
 simplemente escribira el nombre del archivo de entrada(el nombre debera ser igual a como aparece en el escritorio del
 usuario, cabe aclarar que el archivo debe estar en la carpeta BD) y el nombre del archivo de salida que sera de su
 preferencia(el archivo luego aparecera en la carpeta BD)
 */

int main()
{
    //Variables necesarias para las funciones codificacion y decodificacion
    int semilla, metodo, op;
    string file1, file2;
    cout<<"En este programa podra codificar y decodificar archivos "<<endl;
    cout<<"Digite 1 para codificar archivos de texto "<<endl;//Se aclara que para codificar solo debe seleccionar archivos de texto
    cout<<"Digite 2 para decodificar archivos con numeros binarios "<<endl;//Solo para archivos con numeros binarios
    cin>>op;
    system("CLS");//Limpiar pantalla
    cout << "Ingresa un numero entero para iniciar(para separar los grupos en n bits): " << endl;//La semilla para hacer la separacion de grupos de bits
    cin>>semilla;
    system("CLS");
    //Se le da al usuario la opcion de elegir el metodo
    cout << "Digite 1 para elegir el primer metodo de codificacion/decodificacion" << endl;
    cout << "Digite 2 para elegir el segundo metodo " << endl;
    cin>>metodo;
    system("CLS");
    cout << "Escriba el nombre del archivo a codificar/decodificar: " << endl;//El usuario escribe el nombre del archivo de entrada
    cin>>file1;
    system("CLS");
    cout<<"Escriba el nombre que le pondra al archivo generado ya codificado/decodificado: "<<endl;//Escribe el nombre que recibira el archivo de salida
    cin>>file2;
    system("CLS");
    //Para codificar y decodificar se llama a la funcion y se agregan los parametros necesarios con la informacion que dio el usuario
    if (op==1){//Si el usuario elige codificar archivos
        codificacion(semilla, metodo, file1, file2);
    }
    else if(op==2){//Si elige decodificar archivos
        decodificacion(semilla, metodo, file1, file2);
    }
    return 0;
}
