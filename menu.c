#include <stdio.h>
#include "funciones.c"
#include <time.h>

int main(){
	int e;
	do {
		system("cls");
		printf("\t\t\t|-----------------------------------------------------------|\n");
		printf ("\t\t\t|-----------------BIENVENIDO A SEM POSADAS------------------|\n");
		printf("\t\t\t|-----------------------------------------------------------|\n");
		printf(" Le recordamos: \n-USE TAPABOCAS: Pongase el tapabocas justo antes de salir.\n");
		printf("-INTENTE NO PAGAR EN EFECTIVO: En caso de hacerlo,desinfecta tus manos.\n");
		printf("-NO TOQUES NADA: Hasta que no te hayas desinfectado las manos.\n");
		printf("-LAVATE LAS MANOS: Despues de tocar cualquier objeto o superficie.\n");
		printf("-EVITA EL CONTACTO: Siempre que sea posible evita el contacto fisico con otras personas.\n");
		printf("-MANTENE DISTANCIA: Siempre mantene una distancia de al menos dos metros.\n");
		printf("\n");
		printf("#MECUIDOTECUIDO\n");
		printf("\t\t MINISTERIO DE PROGRAMACION KE-GB \n \t\t\tDCC Company 2020\n");
		horasem();
		printf("\n \n-----------------------------------------------------------------------------------------------------------------------");
		printf("\t\t\t\t\t        |  MENU PRINCIPAL  |\n");
		printf("\t\t\t\t\t|  1-Usuarios      |\n\t\t\t\t\t|  2-Recargas      |\n\t\t\t\t\t|  3-Movimientos   |\n\t\t\t\t\t|  4-Inspectores   |\n\t\t\t\t\t|  5-Listado       |\nElegir una opcion: ");
		scanf("%d",&e);
		switch (e){
			case 1:e=U();break;
			case 2:e=R();break;
			case 3:e=M();break;;
			case 4:e=I();break;
			case 5:e=L();break;
			case 6: break;
			default: printf ("La opcion ingresada no es correcta.\n Opcion:");
			}
	}while (e!=6);
	printf ("\n");
	system ("pause");	
	return 0;
}
		
int U(){
	int e,i=0;
	do{
		system("cls");
		printf("\t\t\t\t\t\t*******Menu Usuarios*******\n1-Registrar Usuario\n2-Listado Usuarios\n3-Pagar multa\n4-Volver atras\n5-Salir\n ");
		scanf("%d",&e);
		switch(e){
			case 1:registro();break;
			case 2:mostrarusuarios();break;
			case 3: pagaracta();break;
			case 4:break;
			case 5:i=5;break;
			default: printf ("La opcion ingresada no es correcta.\n");
		}
	}while (e!=4 && e!=5);
	return (i);
}

int R(){
	int e,i=0;
	do{
		system("cls");
		printf("\t*****Menu recarga*****\n1-Realizar recarga\n2-Volver atras\n3-Salir\n");
		scanf("%d",&e);
		switch(e){
			case 1:recargas ();break;
			case 2:break;
			case 3:i=6;break;
			default: printf ("La opcion ingresada no es correcta.\n");
		}
	}while (e!=2 && e!=3);
	return (i);
}

int M(){
	int e,i=0;
	do{
		system("cls");
		printf("\t*****Menu movimientos*****\n1-Iniciar SEM\n2-Finalizar SEM\n3-Volver atras\n4-Salir\n");
		scanf("%d",&e);
		switch(e){
			case 1:iniciarsem();break;
			case 2:finalizarsem();break;
			case 3:break;
			case 4:i=6;break;
			default: printf ("La opcion ingresada no es correcta.\n");
		}
	}while (e!=3 && e!=4);
	return (i);
}


int I(){
	int e,i=0;
	do{
		system("cls");
		printf("\t\t\t\t");   inspectormayoract();
		printf("\n");
		printf("****Menu inspectores****\n1-Registrar inspector\n2-Listado Inspectores\n3-Estado SEM\n4-Listado SEM\n5-Lista de infracciones\n6-Volver atras\n7-Salir\n");
		scanf("%d",&e);
		switch(e){
			case 1:inspectorcarga(); break;
			case 2:inspectoreslecturas();break;
			case 3:estadodesem(); break;
			case 4: listasem();break;
			case 5:listainfracciones();break; 
			case 6:break;
			case 7:i=7;break;
			default: printf ("La opcion ingresada no es correcta.\n");
		}
	}while (e!=6 && e!=7);
	return (i);
}

int L(){
	int e,i=0;
	do{
		system("cls");
		printf("\t/////Menu listado/consultas/////\n 1-Listar Usuarios con SEM activos\n 2-Movimiento de un usuario \n 3-Listar recargas efectuadas por un usuario \n 4-Usuarios con infracciones \n 5-Movimientos por un usuario entre 2 fechas\n 6-Inspector/es con mayor actas labradas\n 7-Usuarios sin infracciones\n 8-Todos los movimientos entre 2 fechas\n 9-Volver atras\n 10-Salir\n Opcion: ");
		scanf("%d",&e);
		switch(e){
			case 1:listarUA();break;
			case 2:Buscarusu50();break;
			case 3:listarecarga();break;
			case 4:usuariosconinfracciones();break;
			case 5:Buscarusu2();break;
			case 6:inspectormayoract();break;
			case 7:usuariossininfracciones();break;
			case 8:Buscarentre2fecha();break;
			case 9:break;
			case 10:i=9;break;
			default: printf ("La opcion ingresada no es correcta.\n");
		}
	}while (e!=9 && e!=10);
	return (i);
	
}
	
	



