#include <stdio.h>
#include <curses.h> //Libreria adicional para manejo de ventanas.
#include <stdlib.h>
#include <time.h> 
#include <string.h>

//Variables globales.
int h, w, ym, xm, yc, xc, yct, xct, option = 0, y, x, k, i, l;

//Estructura de usuario.
struct usuario{

  char nombreUsuario[10];
  char contrasenia[24];

};

//Prototipo o firma de la función cursor.
void cursor();

//Prototipo o firma de la función ventana.
void ventana();

//Prototipo o firma de la función help.
void help();

//Prototipo o firma de la función escribir.
void escribir();

//Prototipo o firma de la función leer.
void leer();

//Prototipo o firma de la función menuPrincipal.
void menuPrincipal();

/*Función main, en ella se encuentra el primer menú del programa, el cual
permite registrarte e iniciar sesión.*/
int main(){
  
  //Variables locales para registro e inicio de sesión.
  char usuario[10];
  char contraseniaI[24];
  char salir;
  FILE * servidor;//apuntador hacia un archivo.
  struct usuario l;// llama a la estructura usuario.
  srand(time(0));//inicia el generador aleatorio de número en función del tiempo de ejecución transcurrido.

  initscr(); //inicia una nueva ventana dentro de la terminal.

  //Atributos para color de texto de terminal.
    start_color();//Permite el uso de atributos que permiten cambiar el color de texto.
    init_pair(1, COLOR_GREEN, COLOR_BLACK);//Pareja de colores que tiene como color de texto verde y color de fondo negro.
    init_pair(2, COLOR_RED, COLOR_BLACK);//Pareja de colores que tiene como color de texto rojo y color de fono negro.
    init_pair(3, COLOR_CYAN, COLOR_BLACK);//Pareja de colores que tiene como color de texto cyan y color de fondo negro.

      do{

	option = 0; //Se inicia la variable option en cero para la selección de una opción.
	cursor(); //Llama a la función cursor para obtener su posición y colocarlo en el lugar correcto.
	clear(); //Limpia lo que esté en pantalla.
	ventana(); //Llama a la función ventana para obtener su posición, fijar tamaño y colocarlo en el lugar correcto.
	noecho(); //No se mostrará en pantalla la entrada del usuario.
	curs_set(0); //No se mostrará en pantalla el cursor.

	/*NOTA: la función mvprintw permite mostrar en la ventana creada el contenido y
	 * posicionarlo donde se indique, a través de las coordenadas yc, xc.
	 * La función scanw permite mostrar la entrada del usuario en ventana(en este)
	 * caso no se podrá observar por la función noecho.*/

	//Cambia el color del texto de la terminal a verde.
	attron(COLOR_PAIR(1));
	  mvprintw(yc-12,xc-6,"MSGCRYPT ver. 1.0");
	attroff(COLOR_PAIR(1));
	
	mvprintw(yc-6,xc-6,"1. Iniciar sesión");
	mvprintw(yc-4,xc-6,"2. Registrarse");
	mvprintw(yc-2,xc-6,"3. Salir");
	scanw("%d",&option);

	//Menú de selección.
	switch(option){

	  case 1:

	    servidor=fopen("servidor.txt","r"); //Abre un archivo llamado servidor.txt en modo lectura.
	    clear(); //Se limpia lo que esté en pantalla.
	    ventana(); //Se llama a la función ventana.

	    //Cambia el color del texto de la terminal a verde.
	    attron(COLOR_PAIR(1));
	      mvprintw(yc-12,xc-6,"MSGCRYPT ver. 1.0");
	    attroff(COLOR_PAIR(1));

	    echo(); //Muestra la entrada escrita por el usuario en pantalla.
	    curs_set(1); //Muestra el cursor en la pantalla.
	    mvprintw(yc-6,xc-16,"Usuario: ");
	    mvscanw(yc-6,xc-7,"%s",&usuario);

	    mvprintw(yc-4,xc-16,"Contraseña: ");
	    mvscanw(yc-4,xc-3,"%s",&contraseniaI);

	    //Se compara el valor ingresado con el contenido en las variables de la estructura usuario.
	    while(fread(&l,sizeof(l),1,servidor)){

	      //Se podrá acceder al menú principal si y sólo si el usuario y la contraseña son correctas.
	      if(strcmp(usuario,l.nombreUsuario)==0 && strcmp(contraseniaI,l.contrasenia)==0)
		menuPrincipal(); //Llama a la función principal.

	      else{

		curs_set(0);//No muestra el cursor en pantalla.

		//Mensaje de error de inicio de sesión en color rojo.
		attron(COLOR_PAIR(2));
		  mvprintw(yc,xc-17,"ERROR: Usuario o contraseña incorrectas");
		attroff(COLOR_PAIR(2));
		mvprintw(yc+2,xc-17,"Presione cualquier tecla para continuar");
		getch(); //Espera que el ususario ingrese una tecla para continuar la ejecución del programa.

	      }

	    }

	    fclose(servidor); //cierra la conexión con el archivo servidor.

	  break;

	  case 2:

	    servidor=fopen("servidor.txt","w"); //Abre el archivo servidor en modo lectura.
	    clear(); //Limpia la pantalla.
	    ventana(); //Llama a la función ventana.
	    echo(); //Muestra la entrada del usuario en pantalla.
	    curs_set(1); //Muestra el cursor en pantalla

	    //Cambia el texto de la terminal a color verde
	    attron(COLOR_PAIR(1));
	      mvprintw(yc-12,xc-6,"MSGCRYPT ver. 1.0");
	    attroff(COLOR_PAIR(1));

	    mvprintw(yc-8,xc-16,"Elije un nombre de usuario:");
	    mvscanw(yc-7,xc-16,"%s",l.nombreUsuario); //Se almacena la entrada en la estructura usuario.
	    mvprintw(yc-5,xc-16,"Elija una contraseña");
	    mvscanw(yc-4,xc-16,"%s",l.contrasenia); //Se almacena la entrada en la estructura usuario.
	    fwrite(&l,sizeof(l),1,servidor); //Imprime los datos contendos en la variable l de estrucura usuario
					     //en el archivo servidor.
	    fclose(servidor); //Se cierra la conexión con el archivo servidor.
	    curs_set(0); //No muestra el cursor en pantalla.

	    //Cambia el color del texto de la terminal a cyan
	    attron(COLOR_PAIR(3));
	      mvprintw(yc+2,xc-6,"Registro exitoso");
	      mvprintw(yc+3,xc-11,"Ahora puedes iniciar sesión");
	    attroff(COLOR_PAIR(3));
	    mvprintw(yc+4,xc-17,"Presione cualquier tecla para continuar");
	    getch(); //Espera a que el usuario presione alguna tecla

	  break;

	  case 3:

	    mvprintw(yc+4,xc-16,"¿Estás seguro que deseas salir? [s/n]");

	    while(salir!='n' || salir!='s'){ //Evita que algún otro caracter interactue con el programa.

	      scanw("%c",&salir);

	      if (salir=='s') //Si el carácter ingresado es s el ciclo termina y sale

		break;

	      else {

		if (salir=='n') //Si el caŕacter ingresado es n el ciclo termina y evalua la última condición

		  break;

	      }
	      
	    }
	      

	  break;

	  default:

	  //Muestra un error cuando se ingresa un número mayor a 3 o menor que cero.
	    attron(COLOR_PAIR(2));
	      mvprintw(yc+3,xc-14, "ERROR: Opción ingresada no válida");
	    attroff(COLOR_PAIR(2));

	    mvprintw(yc+4,xc-17,"Presione cualquier tecla para continuar");
	    getch(); //Espera a que el usuario presione una tecla para continuar con el código

	  break;

	}

      }while(salir!='s');

  endwin(); //cierra la ventana abierta en la terminal.

  return 0;

}

//Función que ayuda a obtener los valores de posición del cursor en la consola.
void cursor(){

  getmaxyx(stdscr,y,x); //valores auxiliares para determinar posición.
  getyx(stdscr,yc,xc); //valores de posición del cursor y lo almacena en yc, xc.
  yc = y/2; //posiciona en la mitad del eje y en la terminal.
  xc = x/2; //posiciona en la mitad del eje x en la terminal.

}

//Función utilizada para generar la misma ventana en los diferentes menús y submenús.
void ventana(){

  getmaxyx(stdscr,ym,xm);//obtiene los valores tamaño de la terminal y lo almacena en ym, xm
  h = 20;	//fija la altura
  w = 41;	//fija el ancho
  WINDOW * ventana = newwin (h,w,(ym/2)-12,(xm/2)-18); 	//Apuntador de venta, crea una nueva ventana.
  refresh(); //Refresca la terminal.
  box(ventana,0,0); //fija los bordes de la ventana con guiones.
  wrefresh(ventana); //refresca la ventana creada dentro de la función.

}

//Función que da información relacionada al objetivo, futuro y estado del proyecto.
void help(){

  //Variable local de la función help
  char ret;

  do{

    getmaxyx(stdscr,yct,xct);//Obtiene el tamaño de la terminal y lo almacena en las variables yct, xct.
    clear(); //función que limpia la pantalla.
    ventana(); //llamado a la función ventana.
    WINDOW * cajaTexto = newwin (17,39,(yct/2)-10,(xct/2)-17); //Crea una nueva ventana.
    refresh();//Refresca la terminal.
    wrefresh(cajaTexto);//Refresca la ventana creada.
    noecho(); //No muestra la entrada del usuario en pantalla.
    curs_set(0); //No muestra el cursor en pantalla.

    //Cambia color de texto a cyan.
    attron(COLOR_PAIR(3));
      mvprintw(yc-12,xc-5,"¿Qué es MSGCRYPT?");
    attroff(COLOR_PAIR(3));

    /*La función mvwprintw, imprimirá el contenido dentro de la ventana cajaTexto y solo dentro de ella.*/
    mvwprintw(cajaTexto,0,0,"MSGCRYPT tiene pensado ser un servicio de correo electrónico encriptado para sistemas operativos Linux, el cual se ejecutará desde la terminal.\n\nSe pretende brindar una privacidad personalizada acorde con cada usuario, el cual podrá tener acceso al código fuente y editarlo con el obejtivo de crear sus propios algoritmos de encriptación y distribuirlos exclusivamente con los usuarios de su conveniencia, así como colocarlo en servidores propios o de terceros.\n\nActualmente el proyecto se encuentra en desarrollo.");
    wrefresh(cajaTexto); //Refrescar caja de texto para mostrar información.
    scanw("%c",&ret);

  }while(ret!='r');

}

//Función que permite escribir y encriptar un mensaje.
void escribir(){

  //Variables locales de la función escribir.
  char ret;
  char mensaje[250];
  FILE * archivo;//apuntador de archivo.
  archivo = fopen ("mensaje.txt","w");//abre un archivo llamado mensaje.txt en modo escritura.

  do{

    getmaxyx(stdscr,yct,xct); //Obtiene el tamaño de la terminal y lo almacena en las variables yct, xct.
    clear(); //Limpia la pantalla.
    ventana(); //Llama a la función ventana.

    //Cambia el color de la terminal a cyan.
    attron(COLOR_PAIR(3));
      mvprintw(yc-12,xc-6,"Ingresa tu mensaje");
    attroff(COLOR_PAIR(3));
    WINDOW * cajaTexto = newwin (17,39,(yct/2)-10,(xct/2)-17); //Crea una ventana llamada cajaTexto.
    refresh(); //Refresca la terminal.
    wrefresh(cajaTexto); //Refresca la ventana cajaTexto.
    cursor(); //Llama a la función cursor para posicionarlo.
    echo(); //Muestra la entrada del usuario en pantalla.
    curs_set(1); //Muestra el cursor en pantalla.
    k = rand(); //asigna a la variable k, un número aleatorio que depende del timepo de ejecución.

    /*La función mvwscanw coloca la entrada del usuario sobre la ventana cajaTexto y solo ahí*/
    mvwscanw(cajaTexto,0,0,"%[^\n]",mensaje);//Lee cadena con espacios.

    for(i=0;(i<250 && mensaje[i]!='\0');i++)

      mensaje[i]=mensaje[i] + k; //Método de encriptación Caesar Cypher.

    fprintf(archivo, "%s",mensaje);// se imprime en el archivo abierto la nueva cadena generada en la línea anterior.
    noecho(); //No muestra la salida del usuario en pantalla.
    curs_set(0); //No muestra el cursor en pantalla.
    scanw("%c",&ret);

  }while(ret!=0x1B); //0x1B corresponde a la telca Esc.

  fclose(archivo);//Cierra el archivo.

}

//Función que permite desencriptar y leer un mensaje.
void leer(){

  //Variables locales de la función leer.
  char ret;
  char mensaje[250];
  FILE * archivo;
  archivo = fopen("mensaje.txt","r"); //Abre el archivo mensaje.txt en modo lectura.

  do{

    l = k; //asigna el valor de k a l, es decir la llave de encriptación.
    getmaxyx(stdscr,yct,xct); //Obtiene el tamaño de la terminal.
    clear(); //Limpia la terminal.
    ventana(); //Llama a la función ventana.
    echo(); //Muestra la entrada del usuario en pantalla.

    //Color del texto de la terminal cyan.
    attron(COLOR_PAIR(3));
      mvprintw(yc-12,xc-5,"Mensaje recibido");
    attroff(COLOR_PAIR(3));
    WINDOW * cajaTexto = newwin (17,39,(yct/2)-10,(xct/2)-17); //Crea una nueva ventana.
    refresh(); //Refresca la terminal.
    wrefresh(cajaTexto); //Refresca la ventana cajaTexto.

    while(!feof(archivo)){ 

      fgets(mensaje,250,archivo); //obtendrá el contenido del archivo y lo almacenará mensaje.

      for(i = 0; (i<250 && mensaje[i]!='\0'); i++) //La condición se ejecutará hasta que una de las
						  //dos condiciones sea falsa o las dos lo sean.

	mensaje[i]=mensaje[i]-l; //Descifra el mensaje restando el valor de la llave.

      mvwprintw(cajaTexto,0,0,"%s",mensaje); //Muestra el mensaje en la ventana cajaTexto y solo en ella.
      wrefresh(cajaTexto); //Refresca la ventana cajaTexto para que el mensaje sea visible.

    }

    noecho(); //No muestra la entrada del usuario.
    scanw("%c",&ret);

  }while(ret!=0x1B);

  fclose(archivo); //Cierra la conexión con el archivo.

}



//Función que muestra el segundo menú del programa
void menuPrincipal(){

  //Variable local de la función menuPrincipal
  char sesion;

  do{

    option = 0;
    cursor(); //Llama a la función cursor para posicionarlo en diferentes puntos.
    clear(); //Limpia la terminal
    ventana(); //Llama a la función ventana.
    noecho(); //No muestra la entrada del usuario en pantalla.
    curs_set(0); //No muestra el cursor en la pantalla.

    //Cambia de color a verde el texto de la terminal.
    attron(COLOR_PAIR(1));
      mvprintw(yc-12,xc-12,"Bienvenido a MSGCRYPT ver. 1.0");
    attroff(COLOR_PAIR(1));
    mvprintw(yc-6,xc-8,"1. ¿Qué es MSGCRYPT?");
    mvprintw(yc-4,xc-8,"2. Escribir un mensaje");
    mvprintw(yc-2,xc-8,"3. Leer un mensaje");
    mvprintw(yc,xc-8,"4. Cerrar sesión");
    scanw("%d",&option);

    switch(option){

      case 1:

	help(); //Llama a la función help

      break;

      case 2:

	escribir(); //Llama a la función escribir

      break;

      case 3:

	leer(); //Llama a la función leer

      break;

      case 4:

	 mvprintw(yc+4,xc-16,"¿Estás seguro que deseas salir? [s/n]");

	    while(sesion!='n' || sesion!='s'){ //Limita que solo los carácteres s y n tienen una función.

	      scanw("%c",&sesion);

	      if (sesion=='s') //si el caracter seleccionado es s, el proceso termina.

		break;

	      else {

		if (sesion=='n') //si el caracter seleccionado es n, sale del ciclo y evalua condición.

		  break;

	      }
	      
	    }

      break;

      default:

      //Muestra mensaje de error en color rojo.
	attron(COLOR_PAIR(2));
	  mvprintw(yc+3,xc-14, "ERROR: Opción ingresada no válida");
	attroff(COLOR_PAIR(2));

	mvprintw(yc+4,xc-17,"Presione cualquier tecla para continuar");
	getch(); //Espera que el usuario presione alguna tecla para continuar.

      break;

    }

  }while(sesion!='s');

}
