#include <stdio.h>
#include <time.h>

struct horas{
	int hora;
	int minuto;
};

struct fecha{
	int dia;
	int mes;
	int anio;
};


struct usuarios{
	char nrocuenta[15];
	char usuario[50];
	char patente[20];
	float saldo;
	int infracciones; //0 si no tiene infracciones. 1 si tiene infraccion//
};


struct movimientos{
	int nrocontrol;
	char nrocuenta[15];
	char patente[7];
	char usuario[50];
	float saldoprevio;
	struct fecha fech;
	struct horas horain;
	struct horas horafin;
	float monto;
};

struct recargas{
	int nrocontrol;
	char nrocuenta[15];
	float monto;
	float saldoprevio;
	struct fecha fech;
	struct horas hora;
};

struct inspectores{
	char nombreagente[50];
	 char legajo[20];
	int contact;
};

struct infracciones{
	int numacta;
	struct fecha fech;
	struct horas hor;
	char patente[20];
	char marca[50];
	char modelo[40];
	char tipovehiculo[50];
	char tipodeinsfraccion[50];
	char observacion[1000];
	int pagado; /*0 no pago, 1 pago*/
	char nombreagente[50];
	char legajoagente[15];
};
