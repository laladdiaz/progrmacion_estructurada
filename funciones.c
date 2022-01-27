#include <stdio.h>
#include <time.h>
#include "estructuras.c"
#include <string.h>
#include <stdlib.h>
void registro(){
	system("cls");
	int registrar,band;
	struct usuarios usu;
	FILE *arch;
	printf("Desea registrarse en el sistema? Presione 1) SI  2) NO \n");
	printf("OPCION:");
	scanf("%d",&registrar);
	while(registrar==1){
	arch=fopen("usuarios.b","ab");
	if(arch!=NULL){
		printf("Ingrese su numero de celular como numero de cuenta: \n");
		getchar();
		gets(usu.nrocuenta);
		band=usuariorepe(usu.nrocuenta);/*si retorna 0 el usuario no existe , 1 si ya existe*/
		if(band==0){
		printf("Ingrese su nombre: \n");
		gets(usu.usuario);
		strupr(usu.usuario);
		printf("Ingrese la patente de su vehiculo. SIN GUIONES NI ESPACIOS :  \n");
		gets(usu.patente);
		strupr(usu.patente);
		printf("Su saldo inicial es de $0. Debe recargar en la opcion de RECARGA\n");
		usu.saldo=0;
		usu.infracciones=0;
		fwrite(&usu,sizeof(usu),1,arch);
	}else {
		printf("El usuario ya existe\n");
	}
		fclose(arch);
	}else {
		printf("error de apertura de archivo \n");
	}
			printf("Registrado con exito!\n");
		printf("Quiere Registrar otro usuario? 1)SI 2)NO \n");
		scanf("%d",&registrar);
}
system ("pause");
}

int usuariorepe(char*nro, char*pat){
	FILE*arch;
	struct usuarios u;
	int existe=0;
	strupr(pat);
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
		fread(&u,sizeof(u),1,arch);
		while(!feof(arch)){
			if(strcmp(nro,u.nrocuenta)==0){
				
				existe=1;
			}
		
			fread(&u,sizeof(u),1,arch);
		}
		fclose(arch);
	}else {
		printf("ERROR DE ARCHIVO");
	}
	return(existe);
}



int  crearnro(){
	FILE *arch;
	struct recargas r;
	int nro=0;
	
	arch= fopen ("recargas.b","rb");
	if (arch!=NULL){
			fread (&r,sizeof(r),1,arch);
			while (!feof(arch)){
 				nro=r.nrocontrol;
 				fread (&r,sizeof(r),1,arch);
			}
			nro++;
			printf ("El numero de control de la recarga es :%d\n",nro);
			fclose (arch);
	}
	return (nro);
}

 int buscarusuario( char *n){
	FILE*arch;
	struct usuarios u;
	int nrocuenta=0;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
		fread(&u,sizeof(u),1,arch);
		while(!feof(arch)){
			if(strcmp(n,u.nrocuenta)==0){
				nrocuenta=1;
			}
			fread(&u,sizeof(u),1,arch);
		}
		fclose(arch);
	}else{
	printf("ERROR DE ARCHIVO");
	}
	return(nrocuenta);
}

float buscarsaldo(char *num){
	FILE*arch;
	struct usuarios u;
	float saldoprev;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
		fread(&u,sizeof(u),1,arch);
		while(!feof(arch)){
			if(strcmp(num,u.nrocuenta)==0){
				saldoprev=u.saldo;
			}
			fread(&u,sizeof(u),1,arch);
		}
		fclose(arch);
	}else{
	printf("ERROR DE ARCHIVO");
}
	return(saldoprev);
}

void actualizarsaldo(char *nro ,float monto,float anterior){
	FILE*arch;
	int aux=(-1);
	struct usuarios u;
	float actualizado=(anterior+monto);
	arch=fopen("usuarios.b","r+b");
	if(arch!=NULL){
			fread (&u,sizeof(u),1,arch);
			while(!feof(arch)){
				if(strcmp(nro,u.nrocuenta)==0){
						u.saldo=actualizado;
						fseek (arch,sizeof (u)*aux,SEEK_CUR);
						fwrite(&u,sizeof(u),1,arch);
						fseek (arch,sizeof(u),SEEK_END);
						printf("SALDO CON LA RECARGA: %.2f \n",u.saldo);
				}
			
					fread (&u,sizeof(u),1,arch);
				//	fseek (arch,sizeof(u),SEEK_END);
				
			}

	fclose(arch);
}else 
printf("Error de apertura\n");
}


void recargas (){
	system("cls");
	struct recargas reca;
	time_t tiempoahora;
	time(&tiempoahora);
	struct tm *mitiempo=localtime(&tiempoahora);
	int nro,usu;
	char celu[15];
	float saldop,monto;
	FILE *arch;
	int op;
	printf("Desea realizar una recarga? 1)SI 2)NO \n");
	scanf("%d",&op);
	while(op==1){
		arch=fopen("recargas.b","ab");
		if(arch!=NULL){  
	printf("Ingrese su numero de cuenta (nro de celular) \n");
	getchar();
	gets(reca.nrocuenta);
	usu=buscarusuario(reca.nrocuenta);/*1 si encuentra ,0 sino*/
	if(usu==1){
		nro=crearnro();
		reca.nrocontrol=nro;
		saldop=buscarsaldo(reca.nrocuenta);
		reca.saldoprevio=saldop;
		printf("Su saldo anterior es de:%.2f\n",saldop);
		printf("Ingrese el monto a recargar\n");
		scanf("%f",&reca.monto);
		monto=reca.monto;
		if(reca.monto>=100){
			actualizarsaldo(reca.nrocuenta,monto,saldop);
		
			printf("Fecha \n");
			reca.fech.dia=mitiempo->tm_mday;
		
				if(mitiempo->tm_mon==0 ||mitiempo->tm_mon==10){
					reca.fech.mes=mitiempo->tm_mon+1;
					}else
					{reca.fech.mes=mitiempo->tm_mon;}
		reca.fech.anio=(mitiempo->tm_year+1900);
		printf("%d/%d/%d",reca.fech.dia,reca.fech.mes,reca.fech.anio);
			printf("\nLa hora es:\n");
			reca.hora.hora=mitiempo->tm_hour;
			reca.hora.minuto=mitiempo->tm_min;
			printf("%d:%d",reca.hora.hora, reca.hora.minuto);
			
		
		
			fwrite(&reca,sizeof(reca),1,arch);
			printf("Se realizo la recarga con exito!\n");
		}else{
			printf("EL MONTO MINIMO ES DE $100\n");
		}
	}else {
		printf("Usted no se encuentra registrado en el sistema. Debe registrarse para recargar\n");
		printf("Desea registrarse? 1)SI 2)NO \n");
		int reg;
		scanf("%d",&reg);
		if(reg==1){
			registro();
		}
	}
	fclose(arch);
}
		
	printf("Desea realizar otra recarga? 1)SI 2)NO \n");
	scanf("%d",&op);
	}
system ("pause");	
}

void mostrarusuarios(){
	system("cls");
	FILE*arch;
	struct usuarios u;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
		fread(&u,sizeof(u),1,arch);
		while(!feof(arch)){
			if(u.nrocuenta>0){
			printf("Nrocuenta: %s \n",u.nrocuenta);
			printf("Nombre del usuario: %s\n",u.usuario);
			printf("Patente: %s\n",u.patente);
			printf("Saldo: %.2f \n",u.saldo);
			if(u.infracciones==0){
				printf("No posee infracciones\n\n");
			}if(u.infracciones==1){
				printf(" Posee infracciones \n\n\n");
			}
		
		}
		fread(&u,sizeof(u),1,arch);
		}
		fclose(arch);
	}else {
		printf("No se abrio");
	}
	system ("pause");

}

int verificacion(char* pat){
	FILE*arch;
	int band=0;
	struct movimientos m;
	arch=fopen("movimientos.b","rb");
	if(arch!=NULL){
		fread(&m,sizeof(m),1,arch);
		while(!feof(arch)){
			if(strcmp(pat,m.patente)==0){
			//	if((dia==m.fech.dia)&&(mes==m.fech.mes)&&(anio==m.fech.anio)){
				if((m.horafin.hora==0)&&(m.horafin.minuto==0)){
					band=1;
				}	
				//}
			}
				fread(&m,sizeof(m),1,arch);
		}
		fclose(arch);
	}else{
		printf("Error de apertura\n");
	}
	return (band);
}

int verificacionagente(char*legajo){
		FILE*arch;
	int band=0;
	struct inspectores i;
	arch=fopen("inspectores.b","rb");
	if(arch!=NULL){
		fread(&i,sizeof(i),1,arch);
		while(!feof(arch)){
			if(strcmp(legajo,i.legajo)==0){
					band=1;
			}
				fread(&i,sizeof(i),1,arch);
		}
		fclose(arch);
	}else{
		printf("Error de apertura\n");
	}
	return (band);
}

int numacta(){
	FILE *arch;
	struct infracciones in;
	int nro=0;
	
	arch= fopen ("infracciones.b","rb");
	if (arch!=NULL){
			fread (&in,sizeof(in),1,arch);
			while (!feof(arch)){
 				nro=in.numacta;
 				fread (&in,sizeof(in),1,arch);
			}
			nro++;
			printf ("El numero de acta es :%d\n",nro);
			fclose (arch);
	}
	return (nro);
}

void actuinfraccionusu(char *pat){
	FILE*arch;
	int aux=(-1);
	struct usuarios u;
	arch=fopen("usuarios.b","r+b");
	if(arch!=NULL){
			fread (&u,sizeof(u),1,arch);
			while(!feof(arch)){
				if(strcmp(pat,u.patente)==0){
						u.infracciones=1;
						fseek (arch,sizeof (u)*aux,SEEK_CUR);
						fwrite(&u,sizeof(u),1,arch);
						fseek (arch,sizeof(u),SEEK_END);
				}
					fread (&u,sizeof(u),1,arch);	
			}

	fclose(arch);
}else 
printf("Error de apertura\n");
}

void continspector(char *agen){
	FILE*arch;
	struct inspectores ins;
	int cont,x=-1;
	arch=fopen("inspectores.b","r+b");
	if(arch!=NULL){
	fread(&ins,sizeof(ins),1,arch);
	while(!feof(arch)){
		if(strcmp(agen,ins.legajo)==0){
			cont=ins.contact;
			cont++;
			ins.contact=cont;
			fseek(arch,sizeof(ins)*x,SEEK_CUR);
			fwrite(&ins,sizeof(ins),1,arch);
			fseek(arch,sizeof(ins),SEEK_END);
		}
		fread(&ins,sizeof(ins),1,arch);
	}
	fclose(arch);
}else
printf("error de apertura\n");
}

void estadodesem(){
	system("cls");
	int op,x=0,z=0;
	struct infracciones i;
	
	time_t tiempoahora;
	time(&tiempoahora);
	struct tm *mitiempo=localtime(&tiempoahora);


char vacio[40],vacio2[7],vacio3[10]="ACTA";
	FILE*arch;
	FILE*acta;

	printf("Desea verificar el estado del SEM? 1)SI 2)NO \n");
	scanf("%d",&op);
	while(op==1){
		arch=fopen("infracciones.b","ab");
		printf("Ingrese la patente del vehiculo: \n");
		getchar();
		gets(i.patente);
		strupr(i.patente);
		
		printf("La fecha es:\n");
		i.fech.dia=mitiempo->tm_mday;
		
			if(mitiempo->tm_mon==0 ||mitiempo->tm_mon==10){
				i.fech.mes=mitiempo->tm_mon+1;
			}else
				{i.fech.mes=mitiempo->tm_mon;}
		i.fech.anio=(mitiempo->tm_year+1900);
		printf("%d/%d/%d",i.fech.dia,i.fech.mes,i.fech.anio);
		
		printf("\nLa hora es:\n");
		i.hor.hora=mitiempo->tm_hour;
		i.hor.minuto=mitiempo->tm_min;
		printf("%d:%d",i.hor.hora, i.hor.minuto);
				
		x=verificacion(i.patente);
		if(x==0){
			if(i.hor.hora>=7 && i.hor.hora<=13 || i.hor.hora>=16 && i.hor.hora<=21){
			printf("La patente no se encuentra con el SEM activo\n");
			printf("Ingrese su legajo: \n");
	//		getchar();
			gets(i.legajoagente);
			z=verificacionagente(i.legajoagente);
			if(z==1){	
				if(arch!=NULL){
				printf("Ingrese su nombre: \n");
			//	getchar();
				gets(i.nombreagente);
				i.numacta=numacta();
				printf("Ingrese la marca del vehiculo: \n");
				gets(i.marca);
				printf("Ingrese el modelo del vehiculo: \n");
				gets(i.modelo);
				printf("Ingrese el tipo de vehiculo : Camion,auto ,moto, omnibus, acoplado, trailer, otro \n");
				gets(i.tipovehiculo);
				printf("Ingrese el tipo de insfraccion: \n");
				gets(i.tipodeinsfraccion);
				printf("Observaciones: \n");
				gets(i.observacion);
				i.pagado=0;
				continspector(i.legajoagente);
				actuinfraccionusu(i.patente);
				sprintf(vacio,"ACTA %d ",i.numacta);
						strcpy(vacio,i.patente);
						sprintf(vacio2,"%d", i.numacta);
						strcat(vacio,vacio3);
						strcat(vacio,vacio2);
						strcat(vacio,".txt");
						acta=fopen(vacio,"w");
								if (acta!=NULL){
									fprintf(acta,"----------------------------------------------DIRECCION GENERAL DE TRANSITO----------------------------------------------\n");
									fprintf(acta,"\t\t\t\t\t\t\t\t\t\t\t\t\tNº de acta: %d \n",i.numacta);
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
-									fprintf(acta,"-------------------------------------------------------CONDUCTOR---------------------------------------------------------\n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\n");
									fprintf(acta,"-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\n");
									fprintf(acta,"-\t  %d  \t        -\t  %d  \t        -\t  %d  \t-\t  %d  \t        -\t  %d  \t        -\n",i.fech.dia,i.fech.mes,i.fech.anio,i.hor.hora,i.hor.minuto);
									fprintf(acta,"-\t DIA        \t-\t  MES          \t-\t  AÑO    \t-\t  HORA        \t-\t  MIN        \t-\t             \t  -\n");
									fprintf(acta,"-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\n");
									fprintf(acta,"-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\t\t\t-\n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"----------------------------------------------------------VEHICULO-------------------------------------------------------\n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"-T\t\t\tM\t\t\tM\n");
									fprintf(acta,"-I    %s\t        A      %s\t        O\t    %s                                                                           -\n",i.tipovehiculo,i.marca,i.modelo);
									fprintf(acta,"-P\t\t\tR\t\t\tD\n");
									fprintf(acta,"-O\t\t\tC\t\t\tE\tDOMINIO:\n");
									fprintf(acta,"-\t\t\tA \t\t\tL\t%s \n",i.patente);
									fprintf(acta,"-\t\t\t -\t\t\tO\t           \n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"-Incumplimiento del pago del sistema de estacionamiento medido(Ordenanza XVI N 17 Art.7). SI___ || NO___-----------------\n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"- Debera presentarse en la oficina de SEM Posadas, sito en Buenos Aires 1521 de Lunes Viernes de 6 a 13 y 15 a 20 o------\n");
									fprintf(acta,"- Sabado de 8 a 12,dentro del plano perentorio de 72 hs de labrada la presente a los del pago opcional Transcurrido------\n");
									fprintf(acta,"- dicho plazo, sin haberse efectuado el pago opcional , la presnete acta se transformara en defitiva conforme las--------\n");
									fprintf(acta,"- previsiones de la ordenanza XVI N 83 y sera para su intervencion a la autoridad de jusgamiento con domicilio San-------\n");
									fprintf(acta,"- Martin 1555, donde podra ofrecer descargo y ejercer su derecho de defensa en los terminos de los Art.67,70 y 71 de la--\n");
									fprintf(acta,"- ley 24.449.------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"----------------------------------OBSERVACION/DESCRPCION/MEDIDAS PRECAUTORIAS /TESTIGOS----------------------------------\n");
									fprintf(acta,"-------------------------------------------------------------------------------------------------------------------------\n");
									fprintf(acta,"- %s \n",i.observacion);
									fprintf(acta,"-Tipo infraccion: %s \n",i.tipodeinsfraccion);
									fprintf(acta,"-Nombre agente: %s \t\t\t-Legajo es: %s \n",i.nombreagente,i.legajoagente); 
									fprintf(acta,"--------------------------------------------------------------------------------------------------------------------------\n");
									
								fclose(acta);
				
				}else { printf("ERROR ARCHIVO ACTA");}
				printf("El acta se realizo con exito! \n");
				fwrite(&i,sizeof(i),1,arch);
				fclose(arch);	
				}else {
					printf("ERROR DE ARCHIVO\n ");
				}
			}else {
				printf("El agente no se encuentra registrado\n");
			}
		}else { printf ("NO ES HORA DE HACER MULTA -.- %d:%d\n",i.hor.hora,i.hor.minuto);
		}
		if(x==1){
			printf("La patente se encuentra con el SEM activo  \n");		
		}
	
}
	printf("Desea verificar otro SEM? 1)SI 2)SALIR\n");
		scanf("%d",&op);
	}

	system ("pause");
}



void listainfracciones(){
	system("cls");
	FILE*arch;
	struct infracciones in;
	int band=0;
	arch=fopen("infracciones.b","rb");
		if(arch!=NULL){
			fread(&in,sizeof(in),1,arch);
			while(!feof(arch)){
				if(in.numacta>0){
					printf("NRO DE ACTA: %d \n",in.numacta);
					printf("FECHA DE ACTA: %d/%d/%d \n",in.fech.dia,in.fech.mes,in.fech.anio);
					printf("HORA : %d:%d \n",in.hor.hora,in.hor.minuto);
					printf("PATENTE DEL VEHICULO: %s \n",in.patente);
					printf("MARCA: %s \n",in.marca);
					printf("MODELO: %d \n",in.modelo);
					printf("TIPO DE VEHICULO: %s \n",in.tipovehiculo);
					printf("TIPO DE INFRACCION: %s \n",in.tipodeinsfraccion);
					printf("OBSERVACION: %s\n",in.observacion);
					printf("NOMBRE Y LEGAJO DEL AGENTE QUE LABRO EL ACTA: %s %s \n",in.nombreagente,in.legajoagente);
					if(in.pagado==0){
						printf("NO PAGADA \n\n\n");
					}
					if(in.pagado==1){
						printf("PAGADO \n\n\n");
					}
					band=1;
				}
				fread(&in,sizeof(in),1,arch);
			}
			if(band==0){
				printf("NO SE ENCONTRARON ACTAS \n");
			}
			fclose(arch);
		}else
		printf("ERROR DE ARCHIVO\n");
	system ("pause");
}


int movimientoverificacion(char*cel , char*paten){
	int x=0;
	struct usuarios usu;
	FILE*arch;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
		fread(&usu,sizeof(usu),1,arch);
		while(!feof(arch)){
			if(strcmp(cel,usu.nrocuenta)==0){
				if(strcmp(paten,usu.patente)==0){
				x=1;
			}
			}
			fread(&usu,sizeof(usu),1,arch);
		}
		fclose(arch);
	}else{
	printf("ERROR DE ARCHIVO");
	}
	return(x);
}

int nrocontrolsem(){
	FILE *arch;
	struct movimientos mov;
	int nro=0;
	arch= fopen ("movimientos.b","rb");
	if (arch!=NULL){
			fread (&mov,sizeof(mov),1,arch);
			while (!feof(arch)){
 				nro=mov.nrocontrol;
 				fread (&mov,sizeof(mov),1,arch);
			}
			nro++;
			printf ("El numero de control del movimiento :%d\n",nro);
			fclose (arch);
	}
	return (nro);
}
float buscarsaldoparasem(char*cel,char*pat){
	FILE*arch;
	struct usuarios u;
	float saldoprev=0;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
		fread(&u,sizeof(u),1,arch);
		while(!feof(arch)){
			if(strcmp(cel,u.nrocuenta)==0){
				saldoprev=u.saldo;
			}
			fread(&u,sizeof(u),1,arch);
		}
		fclose(arch);
	}else{
	printf("ERROR DE ARCHIVO");
}
	return(saldoprev);
}
int v (char *num){
	FILE *arch;
	int rta=0;
	struct movimientos m;
	arch= fopen("movimientos.b", "r+b");
	if(arch != NULL){
	fread(&m, sizeof(m),1,arch);
	while ( ! feof (arch)) {
	if(strcmp(num,m.nrocuenta)==0){
	if(m.horafin.hora==0 && m.horafin.minuto==0){
		rta=1;
	}
	}
	fread(&m, sizeof(m),1,arch);
	}
	fclose(arch);
} else{
	printf("Error de apertura de archivo");
}
return(rta);	
}
void iniciarsem(){
	system("cls");
	time_t tiempoahora;
	time(&tiempoahora);
	struct tm *mitiempo=localtime(&tiempoahora);
	
	FILE*arch;
	int band=0,nrocon,op,ver=0;
	float saldop;
	struct usuarios u;
	struct movimientos m;
	printf("Desea iniciar el SEM ? 1) SI 2) NO \n");
	scanf("%d",&op);
	printf("\n");
	printf("TARIFAS: \n -1/2 hora $9,00\n -1 hora $18,00 -2 horas $24,00\n -Despues de 3 horas $30 por hora\n");
	while(op==1){
		
	printf("Ingrese su numero de celular: \n");
	getchar();
	gets(m.nrocuenta);
	printf("Ingrese su Patente \n");
	gets(m.patente);
	strupr(m.patente);
	band=movimientoverificacion(m.nrocuenta,m.patente);
	ver=v(m.nrocuenta);
	if(band==1){
		arch=fopen("movimientos.b","ab");
		if(arch!=NULL){
			if(ver==0){
			
		nrocon=nrocontrolsem();
		m.nrocontrol=nrocon;
		saldop=buscarsaldoparasem(m.nrocuenta,m.patente);
		if(saldop>0){ 
		m.saldoprevio=saldop;
	
		printf("La fecha es:\n");
		m.fech.dia=mitiempo->tm_mday;
		
			if(mitiempo->tm_mon==0 ||mitiempo->tm_mon==10){
				m.fech.mes=mitiempo->tm_mon+1;
				}else
					{m.fech.mes=mitiempo->tm_mon;
					}
		m.fech.anio=(mitiempo->tm_year+1900);
		printf("\n%d/%d/%d",m.fech.dia,m.fech.mes,m.fech.anio);
		
			printf("\nHorario de la maniana: 07:00 a 13:00 \n Horario de la tarde: 16:00 a 21:00 \n");
			printf("\nHora:\n");
			m.horain.hora=mitiempo->tm_hour;
			m.horain.minuto=mitiempo->tm_min;//////////////////////////////////////////////////////////////////////////////
			printf("%d:%d\n",m.horain.hora, m.horain.minuto);
			
			if((m.horain.hora<7 || m.horain.hora>=13 && m.horain.hora<16) ||(m.horain.hora>=21)){
				printf("\nSEM NO ESTA EN FUNCIONAMIENTO EN ESTE HORARIO %d:%d \n",m.horain.hora, m.horain.minuto);
			}else {
			m.horafin.hora=0;
			m.horafin.minuto=0;
			m.monto=0;
			fwrite(&m,sizeof(m),1,arch);
			fclose(arch);
			}
				
		}else{
		printf("Su saldo es insuficiente \n");
		printf("Desea recargar? 1) SI 2)NO\n");
		int rec;
		scanf("%d",&rec);
		if(rec==1){
			recargas();
		}
			}

		}else{printf("TIENE UNA PATENTE CON SEM ACTIVADO\n");
		}
		
		
		}else{
			printf("Error de archivo");
		}
	
	}
	if(band==0){
		printf("El usuario o la  patente no se encuentran registrados\n");
		printf("\nDesea registrarse? 1) SI 2) NO \n");
		int reg;
		scanf("%d",&reg);
		if(reg==1){
			registro();
		}
	}
	printf("Desea iniciar otro SEM? 1) SI 2) NO \n");
	scanf("%d",&op);
}
system ("pause");
}





void listasem(){
	system("cls");
	FILE*movi;
	struct movimientos mo;
	movi=fopen("movimientos.b","rb");
	if(movi!=NULL){
		fread(&mo,sizeof(mo),1,movi);
			while(!feof(movi)){
				printf("Nro de control: %d \n",mo.nrocontrol);
				printf("Nro de cuenta: %s \n",mo.nrocuenta);
				printf("Patente: %s \n",mo.patente);
				printf("Saldo previo: %.2f \n",mo.saldoprevio);
				printf("Fecha Inicio: %d /%d /%d \n",mo.fech.dia,mo.fech.mes,mo.fech.anio);
				printf("Hora inicio: %d:%d \n ",mo.horain,mo.horain.minuto);
				if((mo.horafin.hora==0) && (mo.horafin.minuto ==0)&& (mo.monto==0)){
					printf("El SEM se encuentra activo \n\n\n");
				}
					if((mo.horafin.hora>0)  && (mo.monto>0)){
					printf("Hora fin: %d:%d \n Monto:%.2f \n\n\n",mo.horafin.hora,mo.horafin.minuto,mo.monto);
				}
				fread(&mo,sizeof(mo),1,movi);	
			}
		}else{
			printf("error de archivo\n");
		}
		system ("pause");
	}



void inspectorcarga(){
	system("cls");
	struct inspectores ins;
	int band,op;
	FILE *arch;
	printf("Desea registrarse en el sistema? 1)SI 2) NO\n");
	scanf("%d",&op);
	while(op==1){
	arch=fopen("inspectores.b","ab");
	if(arch!=NULL){	
		printf("Ingrese su numero de DNI como numero de legajo\n");
		getchar();
		gets(ins.legajo);
		band=inspectorepe(ins.legajo);/*si retorna 0 el usuario no existe , 1 si ya existe*/
		if(band==0){
		printf("Ingrese su nombre:\n");
		gets(ins.nombreagente);
		strupr(ins.nombreagente);
		ins.contact=0;
		
	}else {
		printf("El inspector ya existe\n");
	}
		fwrite(&ins,sizeof(ins),1,arch);
		printf("Registrado con exito!\n");
		fclose(arch);
	}else {
		printf("error de apertura de archivo \n");
	}
		printf("Desea registrar otro usuario? 1)SI 2) NO\n");
		scanf("%d",&op);
}
	system ("pause");
}


void inspectoreslecturas(){
	system("cls");
	struct  inspectores ins;
	FILE*arch;
	arch=fopen("inspectores.b","rb");
	if(arch!=NULL){
		fread(&ins,sizeof(ins),1,arch);
		while(!feof(arch)){
	printf("El nombre del usuario es:%s \n", ins.nombreagente);
	printf("El legajo del inspector es:%s \n", ins.legajo);
	printf("Numero de insfracciones labradas:%d \n \n ",ins.contact);
		fread(&ins,sizeof(ins),1,arch);
		}
		fclose(arch);
	}else{
	printf("ERROR DE ARCHIVO");
	}
	system ("pause");
}
int inspectorepe(char*legaj){
	FILE*arch;
	struct  inspectores ins;
	int existe=0;
	arch=fopen("inspectores.b","rb");
	if(arch!=NULL){
		fread(&ins,sizeof(ins),1,arch);
		while(!feof(arch)){
			if(strcmp(legaj,ins.legajo)==0){
				existe=1;
			}
			fread(&ins,sizeof(ins),1,arch);
		}
		fclose(arch);
	}else {
		printf("ERROR DE ARCHIVO");
	}
	return(existe);
}

void usuariossininfracciones(){
//	system("cls");
	FILE*a;
	struct usuarios usu;
	a=fopen("usuarios.b","rb");
	if(a!=NULL){
		fread(&usu,sizeof(usu),1,a);
		while(!feof(a)){
			if(usu.infracciones==0){
				printf("NRO DE CUENTA: %s \n",usu.nrocuenta);
				printf("NOMBRE DE USUARIO: %s\n",usu.usuario);
				printf("PATENTE: %s\n",usu.patente);
				printf("SALDO: %.2f \n\n",usu.saldo);
				
			}
				fread(&usu,sizeof(usu),1,a);
		}
		fclose(a);
	}else
	printf("ERROR DE ARCHIVO");
	system ("pause");
}


void usuariosconinfracciones(){
//	system("cls");
	FILE*a;
	struct usuarios usu;
	a=fopen("usuarios.b","rb");
	if(a!=NULL){
		fread(&usu,sizeof(usu),1,a);
		while(!feof(a)){
			if(usu.infracciones==1){
				printf("NRO DE CUENTA: %s \n",usu.nrocuenta);
				printf("NOMBRE DE USUARIO: %s\n",usu.usuario);
				printf("PATENTE: %s\n",usu.patente);
				printf("SALDO: %.2f \n\n",usu.saldo);
				
			}
				fread(&usu,sizeof(usu),1,a);
		}
		fclose(a);
	}else
	printf("ERROR DE ARCHIVO");
	system ("pause");
}

void inspectormayoract(){
	system("cls");
	struct  inspectores ins;
	int cont=0;
	FILE*arch;
	arch=fopen("inspectores.b","rb");
	if(arch!=NULL){
		fread(&ins,sizeof(ins),1,arch);
		while(!feof(arch)){
			if(ins.contact>cont){
			cont=ins.contact;	
			}
		fread(&ins,sizeof(ins),1,arch);
		}	
			fclose(arch);
		}else{
	printf("ERROR DE ARCHIVO");
	}
	arch=fopen("inspectores.b","rb");
	if(arch!=NULL){
		fread(&ins,sizeof(ins),1,arch);
		printf("\t\t\t///////INSPECTOR/ES CON MAYOR ACTAS LABRADAS/////\n");
		if(cont==0){
			printf("\t\t\t     No hay inspectores con actas labradas\n");
		}
		while(!feof(arch)){
			if(cont>0){
			if(ins.contact==cont){
					printf("El nombre del inspector es: %s \n", ins.nombreagente);
			printf("El legajo del inspector es: %s \n", ins.legajo);
			printf("Numero de insfracciones labradas: %d \n \n ",ins.contact);
			}
		}
		fread(&ins,sizeof(ins),1,arch);
		}	
			fclose(arch);
		}else{
	printf("ERROR DE ARCHIVO");
	}
//	system ("pause");
	
}


// LISTAR RECARGAS EFECTUADAS
void listarecarga(){
	system("cls");
	struct recargas re;
	FILE*arch;
	int m=0;
char num[50];
	printf("Ingrese el usuario a buscar (nro de celular)\n");
	getchar();
	gets(num);
		arch=fopen("recargas.b","rb");
		if(arch!=NULL){
			fread(&re,sizeof(re),1,arch);
			while(!feof(arch)){
				if(strcmp(re.nrocuenta,num)==0){
				printf("\nFecha: %d/%d/%d\n",re.fech.dia,re.fech.mes,re.fech.anio );
				printf("Recarga de :%.2f\n",re.monto);
			m=1;
		}
		fread(&re,sizeof(re),1,arch);			
	}
	if(m==0){
		printf("No se encontro recargas\n");
	}
	fclose(arch);
} else {printf ("ERROR ARCHIVO");
}
system ("pause");
} 



////USUARIOS ESTACIONAMIENTO ACTIVO	
void listarUA(){
	system("cls");
	struct movimientos mo;
	FILE *arch;
	int band=0;
	arch=fopen("movimientos.b","rb");
	printf("USUARIOS SEM ACTIVO\n");
	if(arch!=NULL){
		fread(&mo,sizeof(mo),1,arch);
		while(!feof(arch)){
			if(mo.horafin.hora==0 && mo.horafin.minuto==0){
			printf("\nUsuario: %s \t",mo.nrocuenta);
			printf("Patente: %s",mo.patente);
			band=1;
		}
		fread(&mo,sizeof(mo),1,arch);
	}
	if(band==0){
		printf("NO HAY USUARIOS CON SEM ACTIVO\n");
	}
	fclose(arch);
}else printf("ERROR ARCHIVO");
system ("pause");
	
}

void cambiarsaldo(char* paten,char *nro ,float monto,float anterior){
	FILE*arch;
	int aux=(-1);
	struct usuarios u;
	float actualizado=(anterior-monto);
	arch=fopen("usuarios.b","r+b");
	if(arch!=NULL){
			fread (&u,sizeof(u),1,arch);
			while(!feof(arch)){
				if(strcmp(nro,u.nrocuenta)==0 && strcmp(paten,u.patente)==0){
						u.saldo=actualizado;
						fseek (arch,sizeof (u)*aux,SEEK_CUR);
						fwrite(&u,sizeof(u),1,arch);
						printf("SALDO DESPUES DE FINALIZAR SEM: %.2f \n",u.saldo);
						fseek (arch,sizeof(u),SEEK_END);
				}
					fread (&u,sizeof(u),1,arch);	
			}

	fclose(arch);
}else 
printf("Error de apertura\n");
}


void cambiarsaldofinalizadoautomat(char* paten,char *nro ,float monto,float anterior){
	FILE*arch;
	int aux=(-1);
	struct usuarios u;
	float actualizado=(anterior-monto);
	arch=fopen("usuarios.b","r+b");
	if(arch!=NULL){
			fread (&u,sizeof(u),1,arch);
			while(!feof(arch)){
				if(strcmp(nro,u.nrocuenta)==0 && strcmp(paten,u.patente)==0){
						u.saldo=actualizado;
						fseek (arch,sizeof (u)*aux,SEEK_CUR);
						fwrite(&u,sizeof(u),1,arch);
						fseek (arch,sizeof(u),SEEK_END);
				}
					fread (&u,sizeof(u),1,arch);	
			}

	fclose(arch);
}else 
printf("Error de apertura\n");
}


void finalizarsem(){
	system("cls");
	FILE*arch;
	time_t tiempoahora;
	time(&tiempoahora);
	struct tm *mitiempo=localtime(&tiempoahora);
	
	int op,x=-1,band=0;
	float total=0,horainicial=0,horafinal=0;
	int total1,total2;
	float monto;
	struct movimientos m;
	char paten[20],nrocuen[15];
	printf("Desea finalizar un SEM? 1) SI 2)NO \n");
	scanf("%d",&op);
	printf("TARIFAS: \n -1/2 hora $9,00\n -1 hora $18,00 -2 horas $24,00\n -Despues de 3 horas $30 por hora\n");
	while(op==1){
	arch=fopen("movimientos.b","r+b");
	if(arch!=NULL){
		printf("Ingrese su patente: \n");
		getchar();
		gets(paten);
		strupr(paten);
		printf("Ingrese su numero de cuenta (nro celular): \n");
		gets(nrocuen);
		fread(&m,sizeof(m),1,arch);
		while(!feof(arch)){
			if(strcmp(paten,m.patente)==0 && strcmp(nrocuen,m.nrocuenta)==0 && (m.horafin.hora==0)&& (m.horafin.minuto==0)){
				printf("Hora: Minuto\n");
				m.horafin.hora=mitiempo->tm_hour;
				m.horafin.minuto=mitiempo->tm_min;
				printf("%d:%d\n",m.horafin.hora, m.horafin.minuto);
				while((m.horafin.hora<=6 )||( m.horafin.hora>=13 )&& (m.horafin.hora<=16) ||(m.horafin.hora>=21)){//hora menor arreglar
				printf("Hora sin servicio sem\n");
				scanf("%d",&m.horafin.hora);
		}
		printf("\nHora inicio: %d:%d\n",m.horain.hora,m.horain.minuto);
			//horafinal=(m.horafin.hora-m.horain.hora);
			/*if(horafinal>0){
						total=horafinal*70;
			}
			if(horafinal==0){
				total=20;
			}
			*/
	total1= (m.horafin.hora)-(m.horain.hora);
	total2 =((m.horafin.minuto)-(m.horain.minuto));
	if(total2<0){
		total2=(total2)+(60);
		total1=(total1)-(1);
	}
	printf("La hora total es %d:%d \n ", total1, total2);
	if(total1==0 && total2>=1 && total2<=30){
		monto=9;
		printf("El monto del estacionamiento es $%.2f\n", monto);
	}if ((total1==0) && (total2>30 && total2<59)){ 
			monto=18;
		printf("El monto del estacionamiento es $%.2f\n", monto);
	} 
	if(total1==1 && total2==00){
		monto=18;
		printf("El monto del estacionamiento es $.2f\n", monto);
}
	if ((total1==1)&&(total2>0 && total2<=59)){
			monto=24;
		printf("El monto del estacionamiento es $%.2f\n", monto);
	}
	if((total1==2)&& (total2==00)){
		monto=24;
		printf("El monto del estacionamiento es $%.2f\n", monto);
	}
	if ((total1==2)&&(total2>0 && total2<=59)){
			monto=72;
		printf("El monto es  $%.2f\n", monto);}
	if ((total1>2)&& total2==0){
			monto=(((total1-2)*30)+42);
		printf("El monto del estacionamiento es $%.2f\n", monto);}
	if ((total1>2) && (total2>=1 && total2<=59)){
		total1=total1+1;
		monto=(((total1-2)*30)+42);
		printf("El monto del estacionamiento es $%.2f \n", monto);			
	}	
	/*printf("El saldo previo es %f \n",m.saldoprevio);
	m.monto = m.saldoprevio-monto;
	printf("Su saldo es: %f \n", m.monto);*/
	if((m.saldoprevio-monto)<0){
	printf("Su saldo es negativo, por favor recargue primero. (Opcion 3)\n");exit(1);
}
			m.monto=monto;
			printf("Su saldo previo: %.2f\n",m.saldoprevio);
			//printf("El monto final es : %.2f \n",m.monto);
			cambiarsaldo(paten,nrocuen,monto,m.saldoprevio);
			fseek (arch,sizeof (m)*x,SEEK_CUR);
			fwrite(&m,sizeof(m),1,arch);
			fseek (arch,sizeof(m),SEEK_END);
			band=1;
			}
			fread(&m,sizeof(m),1,arch);
		}
		if(band==0){
				printf("La patente no se encuentra en movimientos \n");	
		}
		band=0;
		fclose(arch);
	}
	printf("Desea finalizar otro SEM? 1)SI 2)NO \n");
	scanf("%d",&op);
}
system ("pause");
}


//////actualizado
void horasem(){
	time_t tiempoahora;
	time(&tiempoahora);
	struct tm *mitiempo=localtime(&tiempoahora);	
	int total1,total2;
	struct movimientos m;
	float monto;
	FILE*arch;
	int dife,x=-1;	
	printf("HORA ACTUAL : %d:%d \n",mitiempo->tm_hour,mitiempo->tm_min);
	arch=fopen("movimientos.b","r+b");
	if(arch!=NULL){
	fread(&m,sizeof(m),1,arch);
	while(!feof(arch)){
	if((mitiempo->tm_hour>=13) && (mitiempo->tm_hour<=16)){
		if((m.horafin.hora==0)&& (m.horain.hora<13)){
			m.horafin.hora=13;
			m.horafin.minuto=00;	
				total1= (m.horafin.hora)-(m.horain.hora);
	total2 =((m.horafin.minuto)-(m.horain.minuto));
	if(total2<0){
		total2=(total2)+(60);
		total1=(total1)-(1);
	}
	if(total1==0 && total2>=1 && total2<=30){
		monto=9;
	}if ((total1==0) && (total2>30 && total2<59)){ 
			monto=18;
	
	} 
	if(total1==1 && total2==00){
		monto=18;
	
}
	if ((total1==1)&&(total2>0 && total2<=59)){
			monto=24;
	
	}
	if((total1==2)&& (total2==00)){
		monto=24;
		
	}
	if ((total1==2)&&(total2>0 && total2<=59)){
			monto=72;
		}
	if ((total1>2)&& total2==0){
			monto=(((total1-2)*30)+42);
	
		}
	if ((total1>2) && (total2>=1 && total2<=59)){
		total1=total1+1;
		monto=(((total1-2)*30)+42);			
	}		
			m.monto=monto;
			cambiarsaldofinalizadoautomat(m.patente,m.nrocuenta,monto,m.saldoprevio);
			fseek (arch,sizeof (m)*x,SEEK_CUR);
			fwrite(&m,sizeof(m),1,arch);
			fseek (arch,sizeof(m),SEEK_SET);	
		}	
		}
			if((mitiempo->tm_hour>=21)){
		if((m.horafin.hora==0)&& (m.horain.hora<mitiempo->tm_hour)){
				m.horafin.hora=21;
			m.horafin.minuto=00;
			total1= (m.horafin.hora)-(m.horain.hora);
				total2 =((m.horafin.minuto)-(m.horain.minuto));
				if(total2<0){
		total2=(total2)+(60);
		total1=(total1)-(1);
	}
	if(total1==0 && total2>=1 && total2<=30){
		monto=9;
	}if ((total1==0) && (total2>30 && total2<59)){ 
			monto=18;
	} 
	if(total1==1 && total2==00){
		monto=18;
}
	if ((total1==1)&&(total2>0 && total2<=59)){
			monto=24;
	}
	if((total1==2)&& (total2==00)){
		monto=24;
	}
	if ((total1==2)&&(total2>0 && total2<=59)){
			monto=72;
}
	if ((total1>2)&& total2==0){
			monto=(((total1-2)*30)+42);
		}
	if ((total1>2) && (total2>=1 && total2<=59)){
		total1=total1+1;
		monto=(((total1-2)*30)+42);		
	}		
			
			m.monto=monto;
			cambiarsaldofinalizadoautomat(m.patente,m.nrocuenta,monto,m.saldoprevio);
			fseek (arch,sizeof (m)*x,SEEK_CUR);
			fwrite(&m,sizeof(m),1,arch);
			fseek (arch,sizeof(m),SEEK_SET);
				
		}	
		}
			fread(&m,sizeof(m),1,arch);
	}
	fclose(arch);
}
system ("pause");
}

int buscarusuario50(char *nom){
	FILE *arch;
	int rta;
	struct usuarios u;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
	fread(&u, sizeof(u),1,arch);
		while(! feof(arch)){
			if(strcmp(nom,u.usuario)==0){
			rta=1;
			}
			fread(&u, sizeof(u),1,arch);
		}
		fclose(arch);
			}else{
		printf("Error en la apertura de archivo");
	}
	return(rta);
}
void Buscarusu50(){
	FILE *arch;
	int rta;
	struct movimientos m;
	char num[30], nombre[50];
	int pos;
		printf("Ingrese su numero de telefono:\n");
		getchar();
		gets(num);
		printf("Ingrese su nombre\n");
		gets(nombre);
		strupr(nombre);
		rta=buscarusuario50(nombre);
		arch=fopen("movimientos.b", "rb");
		if(arch!=NULL){
		 fread(&m,sizeof(m),1,arch);
		 while(!feof(arch)){
		 	if((strcmp(num,m.nrocuenta)==0) && (rta==1)){
		 	printf("\nFecha: %d %d %d \n", m.fech.dia,m.fech.mes,m.fech.anio);
			printf("Patente: %s\n", m.patente);			
			printf("Monto: $%.2f \n", m.monto);
			printf("Hora inicio: %d\n", m.horain.hora);
			if(m.horafin.hora == 0){
				printf("El SEM se encuentra activo\n");
			}else{
			printf("horario de salida %d %d\n", m.horafin.hora, m.horafin.minuto);}
		 	pos=1;
		 }
 	fread(&m,sizeof(m),1,arch);

}
if(pos==0 || rta==0){
	printf("No se encontro el usuario\n");
}
		fclose(arch);
	}else {
		printf("ERROR DE ARCHIVO");
	}
	system ("pause");
}


int verificarpatente20(char *num){
struct usuarios u;
FILE *arch;
int rta=0;
arch=fopen("usuarios.b","rb");
if(arch != NULL){
fread(&u, sizeof(u),1,arch);	
while (!feof (arch)){
	if(strcmp(num,u.patente)==0 &&(u.infracciones==1)){
			rta=1;
		}
fread(&u, sizeof(u),1,arch);	
}
fclose(arch);
} else{
	printf("Error de apertura de archivo");
}

return(rta);
}

void actualizarpagado(char *num){
	struct infracciones i;
	FILE *arch;
	int aux=-1;
	arch=fopen("infracciones.b","r+b");
	if(arch!= NULL){
	fread(&i,sizeof(i),1,arch);
		while(!feof (arch)){
	if(strcmp(num,i.patente)==0){
				i.pagado=1;
		fseek(arch,sizeof(i)*aux, SEEK_CUR);
		fwrite(&i,sizeof(i),1,arch);
		fseek(arch,sizeof(i)*aux,SEEK_END);
		
	}
	fread(&i, sizeof(i),1,arch);
}
fclose(arch);
}else{ printf("Error de apertura de archivo");
}

}

void *pruebaa(char *num){
	struct usuarios u;
	FILE *arch;
	int aux=-1;
	arch=fopen("usuarios.b","r+b");
	if(arch!= NULL){
	fread(&u,sizeof(u),1,arch);
		while(!feof (arch)){
	if(strcmp(num,u.patente)==0){
				u.infracciones=0;
		fseek(arch,sizeof(u)*aux, SEEK_CUR);
		fwrite(&u,sizeof(u),1,arch);
		fseek(arch,sizeof(u)*aux,SEEK_END);
		
	}
	fread(&u, sizeof(u),1,arch);
}
fclose(arch);
}else{ printf("Error de apertura de archivo");
}

}





void pagaracta (){
	FILE *arch;
	FILE *acta1;
	char vacio[7]="Tarjeta";
	char patente[20],nomtarj[20],numtar[20],dni[30];
	int op2,op,mestarj,cuotas,numdorso, anotarj,mes,anio,dia,rta,rta2;
	time_t tiempoahora;
	time(&tiempoahora);
	struct infracciones i; 
	struct tm *mitiempo=localtime(&tiempoahora);
	arch=fopen("infracciones.b","rb");
	dia=mitiempo->tm_mday;
		
			if(mitiempo->tm_mon==0 ||mitiempo->tm_mon==10){
				mes=mitiempo->tm_mon+1;
				}else
					{mes=mitiempo->tm_mon;
					}
		anio=(mitiempo->tm_year+1900);
	printf("Desea pagar su multa 1) SI 2)NO\n");
	scanf("%d",&op);
	while(op==1){
		arch=fopen("infracciones.b","rb");
		if (arch!= NULL){
				
		printf("Ingrese la patenten\n");
		getchar();
		gets(i.patente);
		strupr(i.patente);
		rta=verificarpatente20(i.patente);
		//printf("%d",rta);
		if(rta==1){
		
		printf("Como desea abonar 1)tarjeta 2)efectivo 3)Mercado pago\n");
		scanf("%d",&op2);
		
	
		if(op2==1){
		printf("Ingrese su numero de tarjeta\n");
		getchar();
		gets(numtar);
		printf("Ingrese su nombre (En mayuscula como aparece en su tarjeta)\n");
		getchar();
		gets(nomtarj);
		printf("Ingrese la fecha de vencimiento\n");
		printf("Mes: \n");
		scanf("%d",&mestarj);
		printf("Año: \n");
		scanf("%d",&anotarj);
		printf("Ingrese su los tres digitos(En el dorso de su tarjeta)\n");
		scanf("%d",&numdorso);
		printf("Ingrese su numero de DNI\n");
		getchar();
		gets(dni);
						strcat(vacio,i.patente);
						strcat(vacio,".txt");
						acta1=fopen(vacio,"w");
						if(acta1!= NULL){
							fprintf(acta1,"--------------------------------------VISA--------------------------------------");
							fprintf(acta1,"\n%d/%d/%d														",dia,mes,anio);
							fprintf(acta1,"SEM\n");
							fprintf(acta1,"COMPRA\n");
							fprintf(acta1,"Total: $1000\n");
							fprintf(acta1,"---------------------------------MUCHAS GRACIAS----------------------------------\n");	
							fprintf(acta1,"---------------------------------TICKET CLIENTE----------------------------------\n");
						
							fclose(acta1);
						}else { printf("ERROR ARCHIVO ACTA");}
				printf("El ticket se realizo con exito! \n");
						
	
	} if(op2==2){
			int op3;
		printf ("El pago en efectivo es a travez de pago facil\n Desea abonarlo 1) SI 2)NO\n");
		scanf("%d",&op3);
		if(op3==1){
			printf("--------------------------LISTO, AHORA VE A UN PAGO FACIL Y PAGA $1000,00-----------------------------\n");
			printf("\t\t\t Dictale estos numeros al cajero \t\t\t\n");
			printf("\t\t\t\t 	3515893453	 \t\t\t\t\n");
			printf("------------------------------------------------------------------------------------------------------\n");
			printf("Si lo abres desde tu telefono va a ser mas facil dictarle al cajero o saca una captura de pantalla.\n");
			printf("\t\t\tEl pago se acreditara al instante\t\t\t\n");
		}
	}
	if(op2==3){
		printf("----------------------------Copie y pegue el siguiente link en una pagina web--------------------------\n");
		printf("\t\t\t\tSe le redireccionara a la pagina de Mercado Pago\t\t\t\t\n");
		printf("MULTA SEM. $ 1.000,00. Pagalos con este link de Mercado Pago: \n");
		printf("\t\thttps://mpago.la/2bkoxUj\t\t\n");
		printf("------------------------------------------------------------------------------------------------------\n");
	}
pruebaa(i.patente);	
actualizarpagado(i.patente);

}else{
	printf("Su patente no se encuentra registrado o usted no posee multas\n");
}

	fread(&i, sizeof(i),1,arch);	
	fclose(arch);		
	}
else {printf("Error de archivo");
}

}
printf("Desea pagar otra multa? 1)SI 2)SALIR\n");
scanf("%d",&op);
system ("pause");

}
int buscarusuario60(char*nom){
	FILE *arch;
	int rta;
	struct usuarios u;
	arch=fopen("usuarios.b","rb");
	if(arch!=NULL){
	fread(&u, sizeof(u),1,arch);
		while(! feof(arch)){
			if(strcmp(nom,u.usuario)==0){
			rta=1;
			}
			fread(&u, sizeof(u),1,arch);
		}
		fclose(arch);
			}else{
		printf("Error en la apertura de archivo");
	}
	return(rta);
}
void Buscarusu2(){
	system("cls");
	FILE *arch;
	struct movimientos m;
	char num[30];
	int d1,d2,m1,m2,a1,a2,a=0,rta,n;
	int pos=0;
		printf("Ingrese numero de telefono:\n");
		getchar();
		gets(num);
		arch=fopen("movimientos.b","rb");
		n=bn(num);
		printf("%d",n);
		if(arch!=NULL){
			fread(&m,sizeof(m),1,arch);
				 			if(n==1){
								a=1;
								printf("Ingrese la primer fecha (DD/MM/AAAA)\n");
									printf("dia\n");
									scanf("%d",&d1);
									scanf("%d",&m1);
									if(d1>=1&&d1<=31&&m1>=1&&m1<=12){
									scanf("%d",&a1);
									printf("dia2\n");
									scanf("%d",&d2);
									scanf("%d",&m2);
									scanf("%d",&a2);
						}else {printf("Fecha mal ingresado intente luego\n");
						}
						if(d1>=1&&d1<=31&&m1>=1&&m1<=12&&d2>=1&&d2<=31&&m2>=1&&m2<=12 ){
				 					 
					
				while(!feof(arch)){
					if(strcmp(num,m.nrocuenta)==0){
				if(m.fech.dia>=d1 && m.fech.mes>=m1 && m.fech.anio>=a1 && m.fech.dia<=d2 && m.fech.mes<=m2 && m.fech.anio<=a2){
			printf("\n");		
			printf("\nFecha: %d %d %d \n", m.fech.dia,m.fech.mes,m.fech.anio);
		 	printf("Nº de cuenta: %s\n", m.nrocuenta);	
			printf("Patente: %s\n", m.patente);			
			printf("Monto: %.1f $\n", m.monto);
			printf("horario de entrada %d %d\n", m.horain.hora, m.horain.minuto);
			if(m.horafin.hora == 0){
				printf("El SEM se encuentra activo\n");
			}else{
				printf("horario de salida %d %d\n", m.horafin.hora, m.horafin.minuto);}
	}
		 }
		 fread(&m,sizeof(m),1,arch);
		 } 
		
	}


}
fclose(arch);
}	
if(a==0){
	printf("El Usuario no esta registrado\n");
}
system ("pause");
}
void Buscarentre2fecha(){
	FILE *arch;
	struct movimientos m;
	char num[30];
	int d1,d2,m1,m2,a1,a2;
	int pos=0;

			printf("Ingrese la primer fecha (DD/MM/AAAA)\n");
						printf("Dia: ");
						scanf("%d",&d1);
						while (d1<1 || d1>31){
							printf("Dia invalido. Ingrese nuevamente: ");
							scanf("%d",&d1);
						}
						printf("Mes: ");
						scanf("%d",&m1);
						while (m1<1 || m1>12){
							printf("Mes invalido. Ingrese nuevamente: ");
							scanf("%d",&m1);
						}
						printf("Año (AAAA): ");
						scanf("%d",&a1);
						printf("Ingrese la segunda fecha (DD/MM/AAAA) \n");
						printf("Dia: ");
						scanf("%d",&d2);
						while (d2<1 || d2>31){
							printf("Dia invalido. Ingrese nuevamente: ");
							scanf("%d",&d2);
						}
						printf("Mes: ");
						scanf("%d",&m2);
						while (m2<1 || m2>12){
							printf("Mes invalido. Ingrese nuevamente: ");
							scanf("%d",&m2);
						}
						printf("Año: (AAAA)");
						scanf("%d",&a2);
						if((m1==m2 && a1==a2 && d1>=d2)|| (m2<m1 && a1==a2)){
							printf("Fecha invalida.");
							exit(1);
						}
		arch=fopen("movimientos.b", "rb");
		if(arch!=NULL){
				 fread(&m,sizeof(m),1,arch);
				 		while(!feof(arch)){
				if(m.fech.dia>=d1 && m.fech.mes>=m1 && m.fech.anio>=a1 && m.fech.dia<=d2 && m.fech.mes<=m2 && m.fech.anio<=a2){
					printf("\n");
			printf("Usuario: %s",m.nrocuenta);	
			printf("\nFecha: %d %d %d \n", m.fech.dia,m.fech.mes,m.fech.anio);
		 	printf("Nº de cuenta: %s\n", m.nrocuenta);	
			printf("Patente: %s\n", m.patente);			
			printf("Monto: %.1f $\n", m.monto);
			printf("horario de entrada %d %d\n", m.horain.hora, m.horain.minuto);
			if(m.horafin.hora == 0){
				printf("El SEM se encuentra activo\n");
			}else{
			printf("horario de salida %d %d\n", m.horafin.hora, m.horafin.minuto);}
		
		 }
		 fread(&m,sizeof(m),1,arch);
		 }
		 fread(&m,sizeof(m),1,arch);
	}
	else{printf("Error de apertura de archivo");
	}

fclose(arch);
system ("pause");
}	
int bn(char *num){
	FILE *arch;
	int rta=0;
	struct movimientos m;
	arch=fopen("movimientos.b","rb");
	if(arch!=NULL){
	fread(&m,sizeof(m),1,arch);
		while(! feof(arch)){
			if(strcmp(num,m.nrocuenta)==0){
			rta=1;
			}
			fread(&m, sizeof(m),1,arch);
		}
		fclose(arch);
			}else{
		printf("Error en la apertura de archivo");
	}
		return(rta);
}
