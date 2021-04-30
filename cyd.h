#ifndef CYD_H
#define CYD_H
#include <iostream>
#include <fstream>//Libreria para manejo de documentos
using namespace std;

/*Con estas funciones el usuario no tendra ningun tipo de interaccion por consola ya que la informacion suministrada
 en el menu de entrada en suficiente para hacer el proceso.
 La funcion codificacion toma los datos dados por el usuario, luego abre el archivo y guarda la informacion de este en
 una variable, luego, se identifica cada letra contenida y se le asigna su valor binario correspondiente, despues se
 hacen los cambios en los bits por un determinado numero de grupos y dependiendo del metodo elegido, por ultimo se escribe
 la cadena de bits completa en un archivo(de salida)
 La funcion codificacion funciona casi igual que la anterior pero haciendo un proceso reversivo, al ya tener la cadena
 de bits devolviendo el proceso que se hizo en la codificacion, agrupamos de a 8 bits para hacer una conversion de binario
 a decimales e irlos sumando a una varible string para que al escribir en el archivo de salida automaticamente se escriban
 las letras correspondientes a los decimales en la tabla ascii
 */

//Funciones
void codificacion(int s, int m, string fileE, string fileS){//variable s(semilla), m(metodo), fileE(file entrada), fileS(file salida)

    ifstream fl;//variable file lectura(fl), para leer archivos
    ofstream fe;//variable file escritura(fe), para escribir sobre un documento
    fileE="../Metodosdecodificacion/BD/"+fileE+".txt";//variable que incluye la ruta relativa y el nombre del archivo a leer
    fileS="../Metodosdecodificacion/BD/"+fileS+".txt";//variable con ruta relativa y nombre del archivo de salida
    int large,num,cont0,cont1;
    string datos,cb,def;
    //variable letrasM con los numeros ascii correspondientes a las letras mayusculas y letrasm con las minusculas
    string letrasM={65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90},letrasm={97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
    string binario={"01"};
    //variable binarM contiene los numeros binarios correspondientes de la A-Z(mayusculas) y binam con las minusculas
    string binarM={"0100000101000010010000110100010001000101010001100100011101001000010010010100101001001011010011000100110101001110010011110101000001010001010100100101001101010100010101010101011001010111010110000101100101011010"};
    string binarm={"0110000101100010011000110110010001100101011001100110011101101000011010010110101001101011011011000110110101101110011011110111000001110001011100100111001101110100011101010111011001110111011110000111100101111010"};

    fl.open(fileE);//abrimos el archivo de entrada
    if (!fl.is_open()){//verificamos si se pudo abrir
        cout<<"Error al abrir el archivo..."<<endl;
        exit(1);
    }
    cout<<"Leyendo el archivo..."<<endl;
    fl>>datos;//guarda los datos del archivo en la variable datos
    fl.close();//cerramos el archivo
    large=datos.length();//guardamos en la variable large la cantidad de elementos de la variable datos
    for (int i=0; i<large;i++){
         for (int l=0; l<26; l++){
             if(datos[i]==letrasM[l]){//evaluamos si la letra contenida en la posicion i de la variable datos es igual a alguna de las letras mayusculas
                 num=8*l;//la variable num cumple la funcion de coger solo 8 bits de la variable letrasM segun sea la posicion de tal letra
                 for(int b=num; b<num+8;b++){
                         cb+=binarM[b];//se van añadiendo los 8 bits correspondientes a cada letra
                    }
                }
             else if(datos[i]==letrasm[l]){//Se evalua si la letra contenida en la posicion i de la variable datos es una letra minuscula
                 //Se hacen los mismos pasos que en el condicional anterior pero con binarm
                  num=8*l;
                  for(int b=num; b<num+8;b++){
                          cb+=binarm[b];
                    }
                }
            }
        }
    large=cb.length();//se le da un nuevo valor a large con el numero de elementos de cb(cadena binarios)
    datos="";
    if (m==1){//se evalua si el metodo escogido fue el primero
       num=s-1;//num toma el valor de s-1(para avanzar num posiciones)
       for (int i=0;i<large;i++){
       //mientras en el elemento de la posicion i+num de cb no se encuentre ningun valor restaremos num hasta que encuentre un valor en esa posicion
               while(cb[i+num]==datos[0]){
                num-=1;
                }
               if(i==0){//condicional para que solo se entre en la primera recorrida(solo haga el proceso con el primer grupo de bits)
                   for (int j=i;j<s;j++){
                       if(cb[j]==binario[0]){//evaluamos si el elemento j de cb es un 0
                           def+="1";//se cambia el 0 por un 1 y se añade a la variable def(definitiva), que contendra la cadena de binarios final
                       }
                       else{
                           def+="0";//se cambia el 1 por un 0
                       }
                     }
                   }
               else{      //para el resto de los grupos de bits
                   cont0=0;//contador que lleva la cuenta de 0s en el grupos de bits
                   cont1=0;//contador que lleva la cuenta de 1s
                   for (int j=i-s;j<i;j++){//a j se le asigna el valor de i(posicion actual) menos s(para regresar al primer bit del grupo anterior)
                       if(cb[j]==binario[0]){//se evalua si el elemento en esa posicion es 0
                           cont0++;//se suma 1 cada vez que hay un 0
                       }
                       else if(cb[j]==binario[1]){//para identificar si el elemento es un 1
                           cont1++;//se suma 1 cada vez que hay un 1 en el grupo
                       }
                   }
                   if(cont0==cont1){//se evalua si hay igual cantidad de 0s y 1s en el grupo anterior
                       for (int j=i;j<i+s;j++){
                           if(cb[j]==binario[0]){//identificamos si el elmento es un 0
                               def+="1";//se agregan 1s en def por cada 0 en cb
                           }
                           else if(cb[j]==binario[1]){
                               def+="0";//se agregan 0s en def por cada 1 en cb
                           }
                         }
                   }
                   else if (cont0>cont1){//si hay mas 0s que 1s
                       for (int j=i;j<i+s;j++){
                           def+=cb[j];//agregamos el elemento j antes de hacer los cambios en la siguiente posicion
                           j++;//se le suma 1 mas a j para posicionarme en el siguiente elemento
                           if(j!=i+s){//antes de avanzar en posicion nos aseguramos que j no sea igual a i+s
                               if(cb[j]==binario[0]){//si el elemento es igual a 0
                                   def+="1";//se hace cambio de 0 a 1
                               }
                               else if(cb[j]==binario[1]){//si el elemento es igual a 1
                                   def+="0";//cambio de 1 a 0
                           }
                           }
                         }
                   }
                   else{     //si hay mas 1s que 0s
                       for (int j=i;j<i+s;j++){
                           def+=cb[j];//se agrega el elemento j
                           j++;//se avanza de posicion
                           if(j!=i+s){//nos aseguramos que j no sea igual a i+s
                               def+=cb[j];//agregamos en elemento que va antes de la posicion donde se haran los cambios
                               j++;//avanzamos una posicion mas
                               if(j!=i+s){//al entrar al condicional hacemos los cambios
                                   if(cb[j]==binario[0]){//si es igual a 0
                                       def+="1";//se hace el cambio de 0 a 1
                                   }
                                   else if(cb[j]==binario[1]){   //si es igual a 1
                                       def+="0";//se cambia el 1 por 0
                                   }
                              }
                           }
                         }
                   }
               }
               for(int j=0; j<s-1;j++){//ciclo for para sumarle a i el numero de posiciones que debe avanzar(avanza cada s bits)
                i++;
               }
            }
         }
    else if(m==2){   //si el usuario elige el segundo metodo
        num=s-1;
        for (int i=0;i<large;i++){
               while(cb[i+num]==datos[0]){
                   num-=1;
               }
               def+=cb[i+num];//se agrega como primer elemento de def el ultimo bit del grupo cb
               for (int j=i;j<i+num;j++){
                   def+=cb[j];//se va añadiendo el primer elemento de cb hasta llegar a su penultimo elemento(en el grupo)
                 }
               for(int j=0; j<s-1;j++){//se le suma a i s-1 posiciones para avanzar de posicion
                i++;
               }
            }
     }
    fe.open(fileS);//creamos el archivo con el nombre del file de salida
    fe<<def<<endl;//escribimos en el archivo la informacion contenida en def(cadena de bits definitiva o final) ya codificada
    fe.close();//cerramos el archivo
    cout<<"Archivo codificado... "<<endl;
}

void decodificacion(int s, int m, string fileE, string fileS){

    ifstream fl;
    ofstream fe;
    //rutas relativas
    fileE="../Metodosdecodificacion/BD/"+fileE+".txt";
    fileS="../Metodosdecodificacion/BD/"+fileS+".txt";
    int large,num,cont0=0,cont1=0,mul;
    string datos,cb,def;
    string binario={"01"},letras={};

    fl.open(fileE);
    if (!fl.is_open()){//verificamos si se pudo abrir
        cout<<"Error al abrir el archivo..."<<endl;
        exit(1);
    }
    cout<<"Leyendo el archivo..."<<endl;
    fl>>datos;
    fl.close();//cerramos el archivo
    def="";
    large=datos.length();
    if(m==1){
        num=s-1;
        for(int i=0; i<large; i++){
            while(datos[i+num]==def[0]){
                num-=1;
            }
            if(i==0){
                 for (int j=i;j<s;j++){
                     if(datos[j]==binario[0]){//evaluamos si el elemento i de datos es un 0
                          cb+="1";//se cambia el 0 por un 1 y se añade a la variable cb(cadena bits), que contendra la cadena de binarios
                          cont1++;//se suma cada vez que se hace un cambio a 1
                       }
                     else{
                          cb+="0";//se cambia el 1 por un 0
                          cont0++;//se suma cada vez que se hace un cambio a 0
                        }
                     }
                }
            else{
               if(cont0==cont1){
                   //se les asigna 0 a los contadores para eliminar las cuentas hechas en los grupos anteriores
                   cont0=0;
                   cont1=0;
                   for (int j=i;j<i+s;j++){
                          if(datos[j]==binario[0]){//evaluamos si el elemento i de datos es un 0
                                 cb+="1";//se cambia el 0 por un 1
                                 cont1++;//se hace cuenta de los 1s del grupo ya cambiado(para hacer el cambio en los siguientes)
                              }
                          else if(datos[j]==binario[1]){ //el elemento es igual a 1
                                 cb+="0";//se cambia el 1 por un 0
                                 cont0++;//se lleva cuenta de los 0s
                               }
                             }
                        }
               else if(cont0>cont1){
                        //se le asigna a cont0 y cont1 un 0
                        cont0=0;
                        cont1=0;
                        for (int j=i;j<i+s;j++){
                            cb+=datos[j];//agregamos el elemento j de la variable datos
                            if(datos[j]==binario[0]){
                                cont0++;//si el elemento es un cero lo sumamos a cont0
                             }
                            else if (datos[j]==binario[1]){
                                cont1++;//si es un 1 lo sumamos a cont1
                               }
                            j++;
                            if(j!=i+s){
                                if(datos[j]==binario[0]){//si el elemento es igual a 0
                                    cb+="1";//se hace cambio de 0 a 1
                                    cont1++;
                                }
                                else if(datos[j]==binario[1]){//el elemento es igual a 1
                                    cb+="0";//cambio de 1 a 0
                                    cont0++;
                                }
                             }
                        }
                   }
               else{     //si hay mas 1s que 0s
                   //inicializacion de contadores
                   cont0=0;
                   cont1=0;
                   for (int j=i;j<i+s;j++){
                         cb+=datos[j];
                         if(datos[j]==binario[0]){
                             cont0++;//sumamos si el elemento es 0
                          }
                         else if (datos[j]==binario[1]){
                             cont1++;//sumamos si datos[j] es un 1
                            }
                         //se le suma a j 1 para avanzar de posicion
                         j++;
                         if(j!=i+s){
                              cb+=datos[j];
                              if(datos[j]==binario[0]){
                                  cont0++;
                               }
                              else if (datos[j]==binario[1]){
                                  cont1++;
                                 }
                              j++;
                              if(j!=i+s){
                                if(datos[j]==binario[0]){//si es igual a 0
                                    cb+="1";//se hace el cambio de 0 a 1
                                    cont1++;
                                    }
                                else if(datos[j]==binario[1]){//si es igual a 1
                                     cb+="0";//se cambia el 1 por 0
                                     cont0++;
                                    }
                                  }
                                }
                              }
                           }
                        }
            for (int j=0; j<s-1; j++){//ciclo que permite avanzar posiciones en i
               i++;
             }
           }
    }
    else if(m==2){
        num=s-1;
        for (int i=0;i<large;i++){
           while(datos[i+num]==def[0]){
               num-=1;
           }
           for (int j=i+1;j<i+s;j++){
               if(datos[j]!=def[0]){
                 cb+=datos[j];//se va añadiendo a cb desde el segundo bit del grupo hasta el ultimo(para hacer corrimiento hacia la derecha)
                 }
               }
           cb+=datos[i];//se añade de ultimo al primer bit del grupo
           for (int j=0; j<s-1; j++){//se avanzan posiciones en i
               i++;
           }
         }
      }
    fe.open(fileS);//creamos el archivo con el nombre del file de salida
    large=cb.length();
    num=1;
    s=8;
    for (int i=0; i<large;i++){
        mul=s*num;//para hacer una separacion de 8 bits
        cont0=0;
        cont1=0;
        for(int j=i; j<mul;j++){//ciclo en donde se hace la conversion de numero binario a decimal
            cont0++;
            if(cont0==1 and cb[j]==binario[1]){
                cont1+=128;
            }
            else if(cont0==2 and cb[j]==binario[1]){
                cont1+=64;
            }
            else if(cont0==3 and cb[j]==binario[1]){
                cont1+=32;
            }
            else if(cont0==4 and cb[j]==binario[1]){
                cont1+=16;
            }
            else if(cont0==5 and cb[j]==binario[1]){
                cont1+=8;
            }
            else if(cont0==6 and cb[j]==binario[1]){
                cont1+=4;
            }
            else if(cont0==7 and cb[j]==binario[1]){
                cont1+=2;
            }
            else if(cont0==8 and cb[j]==binario[1]){
                cont1+=1;
            }
        }
       letras[num-1]=cont1;//se va sumando en la posicion actual el valor decimal a la variable letras
       fe<<letras[num-1];//vamos escribiendo cada posicion de letras en el archivo
       num++;
       for(int j=0; j<7;j++){//para avanzar posiciones en i
           i++;
       }
     }
    fe.close();//se cierra el archivo en el que escribimos informacion
    cout<<"Archivo decodificado... "<<endl;
}

#endif // CYD_H
