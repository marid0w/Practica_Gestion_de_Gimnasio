/***********************************************************************
Asignatura: Metodologia de Programacion
Tarea que realiza el programa: Gestion de cursos y socios de un gimnasio.
Alumno 1: <Irene Barragan> Alumno 2: <Maria Miguelsanz>
Grupo de laboratorio: 2L
Fecha: 04/03/2024
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_C_MATRICULADOS 3
#define MAX_SOCIOS 100
#define MAX_CURSOS 15
#define MAX_NOMBRE 100
#define MAX_CODIGO_SOCIO 11
#define CUOTA1 70
#define CUOTA2 50
#define CUOTA3 30

typedef struct {
    int dia;
    int mes;
    int anio;
} FechaBaja;

typedef struct {
    char nombre_socio[MAX_NOMBRE];
    char apellido_1[MAX_NOMBRE];
    char apellido_2[MAX_NOMBRE];
    char DNI[11];
    int tipo;
    char codigoSocio[11];
    char curso[MAX_C_MATRICULADOS][6];
    int num_cursos_inscritos;
    FechaBaja fechaBaja;
} tReg_Socio;


typedef struct {
    char nombre_curso[MAX_NOMBRE];
    int plazas_totales;
    int plazas_disponibles;
    float precio;
    char clave[6];
    int apuntados;
} tReg_Curso;

// Declaración de las funciones
void mensajeBienvenida();

void mensajeDespedida();

void sociosGuardDat(tReg_Socio socios[MAX_SOCIOS], int cont_socios);

void sociosCargDat(tReg_Socio socios[MAX_SOCIOS]);

void cursosGuardDat(tReg_Curso cursos[MAX_CURSOS], int cont_cursos);

void cursosCargDat(tReg_Curso cursos[MAX_CURSOS]);

void contGuardDat(int cont_socios, int cont_cursos);

void contCargDat(int *cont_socios, int *cont_cursos);

void totalSociosGuardDat(int totalSocios);

void totalSociosCargDat(int *totalSocios);

//SOCIOS

void gestionSocios(tReg_Socio socios[MAX_SOCIOS], tReg_Curso cursos[MAX_CURSOS], int *totalSocios, int *cont_socios, int *cont_cursos);

void altaSocios(tReg_Socio socios[MAX_SOCIOS], int *totalSocios, int *cont_socios);

void bajaSocios(tReg_Socio socios[MAX_SOCIOS], int *cont_socios);

void modificacionDatosSocio(tReg_Socio socios[MAX_SOCIOS], int cont_socios);

void consultaDatosSocio(tReg_Socio socios[MAX_SOCIOS], int cont_socios);

int validarDNI(char *DNI);

void generarRecibo(tReg_Socio socios[MAX_SOCIOS], int cont_socios, tReg_Curso cursos[MAX_CURSOS], int cont_cursos);

void listadoGeneralSocios(tReg_Socio socios[MAX_SOCIOS], int cont_socios);

void listadoSociosPorCategoria(tReg_Socio socios[MAX_SOCIOS], int cont_socios);

void listadoSociosDadosBajaMesAnioDeterminado();

//CURSOS

void gestionCursos(tReg_Socio socios[MAX_SOCIOS], int totalSocios, int *cont_socios, tReg_Curso cursos[MAX_CURSOS], int *cont_cursos);

void altaCursos(tReg_Curso cursos[MAX_CURSOS], int *cont_cursos);

void bajaCursos(tReg_Curso cursos[MAX_CURSOS], int *cont_cursos);

void modificacionDatosCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos);

void consultaDatosCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos);

void listadoGeneralCursos(tReg_Curso cursos[MAX_CURSOS], int cont_cursos);

void inscribirSocio(tReg_Curso cursos[MAX_CURSOS], tReg_Socio socios[MAX_SOCIOS], int cont_cursos, int cont_socios);

void listadoSociosApuntadosCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos, tReg_Socio socios[MAX_SOCIOS], int cont_socios);

void importeMedioMensualCursosDadosBaja();

//INFORMES ECONOMICOS
void informesEconomicos(tReg_Socio socios[MAX_SOCIOS], int *cont_socios, tReg_Curso curso[MAX_CURSOS], int *cont_cursos);

void informeMensualCuotasBasicas(tReg_Socio socios[MAX_SOCIOS], int cont_socios);

void informeMensualCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos);

void informeMensualTodosCursos(tReg_Socio socios[MAX_SOCIOS], int cont_socios, tReg_Curso cursos[MAX_CURSOS], int cont_cursos);


void importarCursos(tReg_Curso cursos[MAX_CURSOS], int *cont_cursos);

//OTROS
int buscarSocio(tReg_Socio socios[MAX_SOCIOS], int cont_socios, char dniSub[10]);

int buscarCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos, char claveSub[6]);

void mostrarSocio(tReg_Socio socios[], int indiceS);

void mostrarCurso(tReg_Curso cursos[], int indiceC);

char *generarCodigo(tReg_Socio *socio, int totalSocios);


int main()
{
    // Declaración
    tReg_Socio socios[MAX_SOCIOS];
    tReg_Curso cursos[MAX_CURSOS];
    int opcion;
    int totalSocios = 0;
    int cont_socios = 0;
    int cont_cursos = 0;

    // Cargar ficheros
    contCargDat(&cont_socios, &cont_cursos);
    totalSociosCargDat(&totalSocios);
    sociosCargDat(socios);
    cursosCargDat(cursos);

    // Cambio el idioma
    setlocale(LC_ALL, "spanish");
    system("chcp 1252 >> null");

    mensajeBienvenida();

    // MENÚ PRINCIPAL
     do{
        system("cls");
        printf("\n\tMENÚ PRINCIPAL");
        printf("\n\t==============\t");
        printf("\n\t1. Gestión de Socios");
        printf("\n\t2. Gestión de Cursos");
        printf("\n\t3. Informes económicos");
        printf("\n\t4. Importar Cursos");
        printf("\n\t0. Salir");
        printf("\n\n\tElija opción: ");
        scanf("%d", &opcion);
        printf("\n\n\t");
        system("pause");

        switch (opcion)
        {

        case 1:
            gestionSocios(socios, cursos, &totalSocios, &cont_socios, &cont_cursos);
            break;

        case 2:
            gestionCursos(socios, totalSocios, &cont_socios, cursos, &cont_cursos);
            break;

        case 3:
            informesEconomicos(socios, &cont_socios, cursos, &cont_cursos);
            break;

        case 4:
            importarCursos(cursos, &cont_cursos);
            break;

        case 0:
            sociosGuardDat(socios, cont_socios);
            cursosGuardDat(cursos, cont_cursos);
            contGuardDat(cont_socios, cont_cursos);
            totalSociosGuardDat(totalSocios);
            mensajeDespedida();
            break;

        default:
            printf("\n\n\t\tElija una opción válida.");
        }

    }while(opcion != 0);

    return 0;
}


/***********************************************************************************
Subprograma: gestionSocios()

Tipo: void

Parametros de entrada:
    - socios: arreglo de estructuras tReg_Socio que contendrá los datos de los socios
    - totalSocios: puntero a entero que contendrá el total de socios registrados
    - cont_socios: puntero a entero que contendrá el valor del contador de socios
    - cont_cursos: puntero a entero que contendrá el valor del contador de cursos

Parametros de salida: -------

Prerrequisitos: Declaración de la estructura tReg_Socio y las funciones altaSocios(),
                bajaSocios(), modificacionDatosSocio(), consultaDatosSocio(), generarRecibo(),
                listadoGeneralSocios(), listadoSociosPorCategoria()
                y listadoSociosDadosBajaMesAnioDeterminado().

Objetivo: Presentar un menú de opciones para gestionar los socios,
          permitiendo realizar altas, bajas, modificaciones, consultas
          y generación de recibos, así como listados generales y específicos de socios.
**************************************************************************************/

void gestionSocios(tReg_Socio socios[MAX_SOCIOS], tReg_Curso cursos[MAX_CURSOS], int *totalSocios, int *cont_socios, int *cont_cursos){
    int opcion;
    do{
        system("cls");
        printf("\n\tSUBMENU GESTION DE SOCIOS");
        printf("\n\t=========================\t");
        printf("\n\t1. Alta");
        printf("\n\t2. Baja");
        printf("\n\t3. Modificación de datos de un socio");
        printf("\n\t4. Consulta de datos de un socio");
        printf("\n\t5. Generar un recibo");
        printf("\n\t6. Listado general de socios");
        printf("\n\t7. Listado de socios por categoría");
        printf("\n\t8. Listado de socios que han sido dados de baja un mes y año determinado");
        printf("\n\n\t0. Volver al menú principal");
        printf("\n\n\tElija opción: ");
        fflush(stdin);
        scanf("%d", &opcion);
        printf("\n\n\t");
        system("pause");

        switch(opcion){

        case 1:
            altaSocios(socios, totalSocios, cont_socios);
            break;

        case 2:
            bajaSocios(socios, cont_socios); //fichero
            break;

        case 3:
            modificacionDatosSocio(socios, *cont_socios);
            break;

        case 4:
            consultaDatosSocio(socios, *cont_socios);
            break;

        case 5:
            generarRecibo(socios, *cont_socios, cursos, *cont_cursos);
            break;

        case 6:
            listadoGeneralSocios(socios, *cont_socios);
            break;

        case 7:
            listadoSociosPorCategoria(socios, *cont_socios);
            break;

        case 8:
            listadoSociosDadosBajaMesAnioDeterminado();//fichero
            break;

        case 0:
            break;

        default:
            printf("\n\n\t\tElija una opción válida.");

        }

    }while(opcion != 0);
}

/************************************************************************************
Subprograma: altaSocios()

Tipo: void

Parametros de entrada:
    - socios: arreglo de estructuras tReg_Socio que contendrá los datos de los socios
    - totalSocios: puntero a entero que contendrá el total de socios registrados
    - cont_socios: puntero a entero que contendrá el valor del contador de socios

Parametros de salida: --------

Prerrequisitos: Declaración de la estructura tReg_Socio y la función generarCodigo()

Objetivo: Realizar el alta de un nuevo socio en el sistema, solicitando y
          almacenando sus datos, así como generando su código de socio.
**************************************************************************************/
void altaSocios(tReg_Socio socios[MAX_SOCIOS], int *totalSocios, int *cont_socios) {
    int opcion;

    do {
        system("cls");
        printf("\tALTA DE SOCIOS\n");
        printf("\t==============\n\n");
        printf("\tIntroduzca los datos del nuevo socio:\n");
        printf("\t=====================================\n\n");

        printf("\tIntroduzca su nombre: ");
        fflush(stdin);
        fgets(socios[*cont_socios].nombre_socio, sizeof(socios[*cont_socios].nombre_socio), stdin);
        socios[*cont_socios].nombre_socio[strcspn(socios[*cont_socios].nombre_socio, "\n")] = '\0';

        printf("\tIntroduzca el primer apellido: ");
        fflush(stdin);
        fgets(socios[*cont_socios].apellido_1, sizeof(socios[*cont_socios].apellido_1), stdin);
        socios[*cont_socios].apellido_1[strcspn(socios[*cont_socios].apellido_1, "\n")] = '\0';

        printf("\tIntroduzca el segundo apellido: ");
        fflush(stdin);
        fgets(socios[*cont_socios].apellido_2, sizeof(socios[*cont_socios].apellido_2), stdin);
        socios[*cont_socios].apellido_2[strcspn(socios[*cont_socios].apellido_2, "\n")] = '\0';

        do {
            printf("\tIntroduzca el DNI: ");
            fflush(stdin);
            fgets(socios[*cont_socios].DNI, sizeof(socios[*cont_socios].DNI), stdin);
            socios[*cont_socios].DNI[strcspn(socios[*cont_socios].DNI, "\n")] = '\0';

            if (!validarDNI(socios[*cont_socios].DNI)) {
                printf("\n\t\tDNI no válido. Por favor, inténtelo de nuevo.\n\n");
            }
        } while (!validarDNI(socios[*cont_socios].DNI));

        do {
            printf("\tTipo de socio (1: Normal | 2: Jubilado | 3: Infantil): ");
            fflush(stdin);
            scanf("%d", &socios[*cont_socios].tipo);

            if (socios[*cont_socios].tipo != 1 && socios[*cont_socios].tipo != 2 && socios[*cont_socios].tipo != 3) {
                printf("\t\tTipo no válido.\n");
            }
            else {
                printf("\t\tTipo válido.\n");
            }
        } while (socios[*cont_socios].tipo != 1 && socios[*cont_socios].tipo != 2 && socios[*cont_socios].tipo != 3);

        strcpy(socios[*cont_socios].codigoSocio, generarCodigo(&socios[*cont_socios], *totalSocios));
        printf("\tEl código de socio es: %s\n", socios[*cont_socios].codigoSocio);

        printf("\n\n\t¿Desea registrar otro socio? (Sí = 1; No = 2): ");
        fflush(stdin);
        scanf("%d", &opcion);

        (*cont_socios)++;
        (*totalSocios)++;

        if (*cont_socios >= MAX_SOCIOS) {
            printf("\n\tSe ha alcanzado el número máximo de socios permitidos.\n");
            break;
        }

        printf("\n\n\t");
        system("pause");


    } while ((opcion == 1) && (*cont_socios < (MAX_SOCIOS - 1)));
}

/************************************************************************************
Subprograma: validarDNI()

Tipo: int

Parametros de entrada:
    - char* DNI

Parametros de salida: ----

Prerrequisitos: Introducción del DNI

Objetivo: Validar si un DNI es correctamente formado o no.
**************************************************************************************/
int validarDNI(char *DNI) {
    int i;

    if (strlen(DNI) != 9) {
        return 0;
    }

    for (i = 0; i < 8; i++) {
        if (!isdigit(DNI[i])) {
            return 0;
        }
    }

    if (!isalpha(DNI[8])) {
        return 0;
    }

    return 1;
}

/************************************************************************************
Subprograma: generarCodigo()

Tipo: char*

Parametros de entrada:
    - socios: arreglo de estructuras tReg_Socio que contiene los datos de los socios
    - totalSocios: puntero a entero que indica el total de socios registrados

Parametros de salida: Puntero a caracter que representa el código generado para un
                      nuevo socio

Prerrequisitos: Declaración de la estructura tReg_Socio

Objetivo: Generar un código único para un nuevo socio basado en sus datos personales
          y el número total de socios registrados
**************************************************************************************/

char *generarCodigo(tReg_Socio *socio, int totalSocios) {
    char a[11];
    sprintf(a, "%2.2s%1.1s%1.1s-%05d", socio->nombre_socio, socio->apellido_1, socio->apellido_2, totalSocios + 1);
    strupr(a);
    char *codigo = strdup(a);
    return codigo;
}

/***********************************************************************
Subprograma: bajaSocios()

Tipo: void

Parametros de entrada:
    - socios: arreglo de estructuras tReg_Socio que contiene los datos
              de los socios
    - cont_socios: puntero al contador de socios

Parametros de salida: ------

Prerrequisitos: Declaración de la estructura tReg_Socio

Objetivo: Realizar la baja de un socio del sistema
***********************************************************************/
void bajaSocios(tReg_Socio socios[MAX_SOCIOS], int *cont_socios) {
    char dniSub[10];
    int i, opcion;

    FILE *fichero = fopen("bajaHcoSocios.txt", "a");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return;
    }

    do {
        system("cls");
        printf("\n\tBAJA DE SOCIOS\n");
        printf("\t==============");
        printf("\n\n\tIntroduzca el DNI del socio a dar de baja: ");
        fflush(stdin);
        fgets(dniSub, 10, stdin);
        dniSub[strcspn(dniSub, "\n")] = '\0';

        i = buscarSocio(socios, *cont_socios, dniSub);

        if (i != -1) {
            mostrarSocio(socios, i);

            printf("\n\n\t¿Desea dar de baja a este socio? (Sí = 1; No = 2): ");
            fflush(stdin);
            scanf("%i", &opcion);

            if (opcion == 1) {
                time_t t = time(NULL);
                struct tm *tm_info = localtime(&t);

                socios[i].fechaBaja.dia = tm_info->tm_mday;
                socios[i].fechaBaja.mes = tm_info->tm_mon + 1;
                socios[i].fechaBaja.anio = tm_info->tm_year + 1900;

                fprintf(fichero, "%s;%s;%s;%s;%d;%d;%d\n",
                        dniSub, socios[i].nombre_socio, socios[i].apellido_1, socios[i].apellido_2,
                        socios[i].fechaBaja.dia, socios[i].fechaBaja.mes, socios[i].fechaBaja.anio);

                for (int j = i; j < *cont_socios - 1; j++) {
                    socios[j] = socios[j + 1];
                }
                (*cont_socios)--;

                printf("\n\tEl socio ha sido dado de baja correctamente.\n");
            }
        } else {
            printf("\n\tNo se ha encontrado un socio con el DNI proporcionado.\n");
        }

        printf("\n\n\t¿Desea dar de baja a otro socio? (Sí = 1; No = 2): ");
        fflush(stdin);
        scanf("%i", &opcion);

    } while (opcion == 1);

    fclose(fichero);
}


/***********************************************************************
Subprograma: modificacionDatosSocio()

Tipo: void

Parametros de entrada:
            - socios: tReg_Socio que contiene los datos de los socios
            - cont_socios: puntero al contador de socios

Parametros de salida: ------

Prerrequisitos: El struct de socios debe contener los datos de los socios.

Objetivo: Permitir la modificación de datos de un socio dado su DNI.
*****************************************************************************/
void modificacionDatosSocio(tReg_Socio socios[MAX_SOCIOS], int cont_socios) {
    char dniSub[10];
    int i, opcion;

    system("cls");

    do {
        printf("\n\tMODIFICACION DE UN SOCIO");
        printf("\n\t========================");
        printf("\n\n\tIntroduzca el DNI del socio que quiere modificar: ");
        fflush(stdin);
        fgets(dniSub, 10, stdin);

        i = buscarSocio(socios, cont_socios, dniSub);

        if (i != -1) {
            mostrarSocio(socios, i);
            do {
                printf("\n\n\t******************************************");
                printf("\n\n\t\t¿Qué información desea modificar?");
                printf("\n\n\t\t\t1.- DNI");
                printf("\n\t\t\t2.- Nombre");
                printf("\n\t\t\t3.- Tipo de socio");
                printf("\n\n\t\t\t0.- Salir de las modificaciones");
                printf("\n\n\t\t\tElija opción: ");
                scanf("%d", &opcion);

                switch (opcion) {
                    case 1:
                        printf("\n\tDNI actual: %s", socios[i].DNI);
                        printf("\n\tIngrese el nuevo DNI: ");
                        fflush(stdin);
                        scanf("%s", socios[i].DNI);
                        break;

                    case 2:
                        printf("\n\tNombre actual: %s %s %s", socios[i].nombre_socio, socios[i].apellido_1, socios[i].apellido_2);
                        printf("\n\tIngrese el nuevo nombre: ");
                        fflush(stdin);
                        scanf("%s %s %s", socios[i].nombre_socio, socios[i].apellido_1, socios[i].apellido_2);
                        break;

                    case 3:
                        printf("\n\tTipo actual: %i", socios[i].tipo);
                        printf("\n\tTipo de socio (1: Normal | 2: Jubilado | 3: Infantil): ");
                        fflush(stdin);
                        scanf("%d", &socios[i].tipo);
                        break;

                    case 0:
                        break;

                    default:
                        printf("\n\n\t\tElija una opción válida.");
                }
            } while (opcion != 0);
        } else {
            printf("\n\tERROR: Este DNI no figura en nuestro registro de datos.\n");
        }

        printf("\n\n\t¿Desea modificar otro socio? (Sí = 1; No = 2): ");
        fflush(stdin);
        scanf("%i", &opcion);

    } while (opcion == 1);

    printf("\n\n\t");
    system("pause");
}


/*****************************************************************************************
Subprograma: consultaDatosSocio()

Tipo: void

Parametros de entrada:
        - socios:  tReg_Socio que contiene los datos de los socios
        - cont_socios: puntero al contador de socios

Parametros de salida: -------

Prerrequisitos: La función asume que se ha inicializado correctamente el
                tReg_Socio y que el puntero cont_socios apunta al contador actual de socios.

Objetivo: Mostrar los datos de un socio dado su DNI.
********************************************************************************************/
void consultaDatosSocio(tReg_Socio socios[MAX_SOCIOS], int cont_socios){
    char dniSub[10];
    int opcion, i;

    system("cls");

    do{
        printf("\n\tCONSULTA DATOS SOCIOS");
        printf("\n\t=====================");
        printf("\n\n\tIntroduzca el DNI del socio que quiere consultar: ");
        fflush(stdin);
        fgets(dniSub, 10, stdin);

        i = buscarSocio(socios, cont_socios, dniSub);

        if (i != -1) {
            mostrarSocio(socios, i);
        } else {
            printf("\n\t");
            printf("ERROR: Este DNI no figura en nuestro registro de datos.\n\n\t");
            system("pause");
        }

        printf("\n\n\t¿Desea consultar los datos de otro socio? (Sí = 1; No = 2): ");
        scanf("%i", &opcion);
        printf("\n\n\t");
        system("pause");
        system("cls");

    } while(opcion == 1);
}


/***********************************************************************
Subprograma: generarRecibo()

Tipo: void

Parametros de entrada:
        - socios: tReg_Socio que contiene los datos de los socios
        - cont_socios : puntero al contador de socios

Parametros de salida: ------

Prerrequisitos: El arreglo de estructuras socios debe contener los
                datos de los socios.

Objetivo: Generar un recibo para un socio dado su DNI.
***********************************************************************/
void generarRecibo(tReg_Socio socios[MAX_SOCIOS], int cont_socios, tReg_Curso cursos[MAX_CURSOS], int cont_cursos){
    char dniSub[10];
    int opcion, i, j, k;
    int precio_total_cursos = 0;

    system("cls");

    do{
        printf("\n\tGENERAR RECIBO");
        printf("\n\t==============");
        printf("\n\tIntroduzca el DNI del socio para generar el recibo: ");
        fflush(stdin);
        fgets(dniSub, 10, stdin);

        i = buscarSocio(socios, cont_socios, dniSub);

        printf("\n\n\t");
        system("pause");
        system("cls");

        if (i != -1){
            printf("\n\tRecibo generado correctamente para el socio con DNI %s.\n", socios[i].DNI);
            printf("\n\t\t\tGIMNASIO 'NewGym'");
            mostrarSocio(socios, i);
            printf("\tCursos inscritos: %s", "");
            for(j = 0; j < MAX_C_MATRICULADOS; j++){
                if(socios[i].curso[i][0] != -1){
                    k = buscarCurso(cursos, cont_cursos, socios[i].curso[j]);
                    if (k != -1){
                        printf("%s ", cursos[k].nombre_curso);
                        precio_total_cursos += cursos[k].precio;
                    }
                }
            }

            printf("\n---------------------------------------------------------------------------------------------------------");
            printf("\n\tIMPORTE:");
            if(socios[i].tipo == 1){
                printf("\n\t\tCuota: %-18.2d", CUOTA1);
                printf("\n\t\tPor Cursos: %-18.2d", precio_total_cursos);
                 printf("\n\t\tDescuento aplicado por cursos (0%%): %-18.2d", 0);
                printf("\n---------------------------------------------------------------------------------------------------------");
                printf("\n\t\tImporte Total a abonar = %-18.2d", CUOTA1 + precio_total_cursos);
            }
            else if(socios[i].tipo == 2){
                printf("\n\t\tCuota: %-18.2d", CUOTA2);
                printf("\n\t\tPor Cursos: %-18.2d", precio_total_cursos);
                printf("\n\t\tDescuento aplicado por cursos (25%%): %-18.2f", precio_total_cursos * 0.25);
                printf("\n---------------------------------------------------------------------------------------------------------");
                printf("\n\t\tImporte Total a abonar = %-18.2f", CUOTA2 + precio_total_cursos - (precio_total_cursos * 0.25));
            }
            else if(socios[i].tipo == 3){
                printf("\n\t\tCuota: %-18.2d", CUOTA3);
                printf("\n\t\tPor Cursos: %-18.2d", precio_total_cursos);
                printf("\n\t\tDescuento aplicado por cursos (50%%): %-18.2f", precio_total_cursos * 0.50);
                printf("\n---------------------------------------------------------------------------------------------------------");
                printf("\n\t\tImporte Total a abonar = %-18.2f", CUOTA3 + precio_total_cursos - (precio_total_cursos * 0.50));
            }
        } else {
            printf("ERROR: Este DNI no figura en nuestro registro de datos.\n");
        }

        printf("\n\n\t¿Desea generar otro recibo? (Sí = 1; No = 2): ");
        scanf("%i", &opcion);
        printf("\n\n\t");
        system("pause");
        system("cls");

    } while(opcion == 1);
}


/******************************************************************************************
Subprograma: listadoGeneralSocios()

Tipo: void

Parametros de entrada:
            - socios: tReg_Socio que contiene los datos de los socios
            - cont_socios: puntero al contador de socios

Parametros de salida: ------

Prerrequisitos: El struct de socios debe contener los datos de los socios.

Objetivo: Mostrar un listado general de todos los socios registrados en el sistema.
*******************************************************************************************/
void listadoGeneralSocios(tReg_Socio socios[MAX_SOCIOS], int cont_socios){
    char tipo_socio[10];

    system("cls");
    printf("\n\t======================");
    printf("\n\tLISTADO GENERAL SOCIOS");
    printf("\n\t======================");
    printf("\n\n\t%-12s %-20s %-20s %-20s %-10s %-10s", "Código", "Nombre", "Apellido 1", "Apellido 2", "DNI", "Categoría");
    printf("\n\t================================================================================================\n");

    for (int i = 0; i < cont_socios; i++) {
        if (socios[i].tipo == 1) {
            strcpy(tipo_socio, "Normal");
        } else if (socios[i].tipo == 2) {
            strcpy(tipo_socio, "Jubilado");
        } else if (socios[i].tipo == 3) {
            strcpy(tipo_socio, "Infantil");
        }
        printf("\t%-12s %-20s %-20s %-20s %-10s %-10s\n", socios[i].codigoSocio, socios[i].nombre_socio, socios[i].apellido_1, socios[i].apellido_2, socios[i].DNI, tipo_socio);
    }
    printf("\n\n\t");
    system("pause");
}


/***********************************************************************
Subprograma: listadoSociosPorCategoria()
Tipo:
Parametros de entrada:
Parametros de salida:
Prerrequisitos:
Objetivo:
***********************************************************************/
void listadoSociosPorCategoria(tReg_Socio socios[MAX_SOCIOS], int cont_socios) {
    int categoria;
    char respuesta;

    do {
        system("cls");
        printf("\n\tLISTADO DE SOCIOS POR CATEGORIA");
        printf("\n\t================================\n\n");
        printf("\tSeleccione una categoría (1: Normal | 2: Jubilado | 3: Infantil): ");
        scanf("%i", &categoria);

        printf("\n\tLISTADO DE SOCIOS - Categoría %i", categoria);
        printf("\n\t============================================");

        printf("\n\n\t%-15s \t\t\t\t%-10s", "Nombre", "DNI");
    printf("\n\t==========================================================\n");

        for (int i = 0; i < cont_socios; i++) {
            if (socios[i].tipo == categoria) {
                printf("\n\t%-15s %-15s %-15s %-10s", socios[i].nombre_socio, socios[i].apellido_1, socios[i].apellido_2, socios[i].DNI);
            }
        }

        printf("\n\n\t¿Desea ver la información de otra categoría? (s/n): ");
        scanf(" %c", &respuesta);
    } while (respuesta == 's' || respuesta == 'S');

    printf("\n\n\t");
    system("pause");
}


/********************************************************************************
Subprograma:listadoSociosDadosBajaMesAnioDeterminado()

Tipo: void

Parametros de entrada:
                - socios: tReg_Socio que contiene los datos de los socios
                - cont_socios: puntero al contador de socios

Parametros de salida: ------

Prerrequisitos: El struct de socios debe contener los datos de los socios.

Objetivo: Mostrar un listado de socios filtrado por categoría.
*********************************************************************************/
void listadoSociosDadosBajaMesAnioDeterminado() {
    int mes, anio;
    char dni[10], nombre[MAX_NOMBRE], apellido1[MAX_NOMBRE], apellido2[MAX_NOMBRE];
    int dia_baja, mes_baja, anio_baja;
    int num_campos;
    int total_socios = 0;

    FILE *fichero = fopen("bajaHcoSocios.txt", "r");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return;
    }

    system("cls");
    printf("\n\tListado de Socios Dados de Baja\n");
    printf("\t===============================\n");
     printf("\n\tIntroduzca el mes (1-12): ");
    scanf("%d", &mes);
    printf("\tIntroduzca el año: ");
    scanf("%d", &anio);

    printf("\n\t-------------------------------------------------------------------------\n");
    printf("\tLISTADO DE SOCIOS DADOS DE BAJA EN %02d/%d\n", mes, anio);
    printf("\t-------------------------------------------------------------------------\n");
    printf("\t%-25s %-20s %-10s\n", "Nombre y Apellidos", "DNI", "Fecha");
    printf("\t-------------------------------------------------------------------------\n");

    while ((num_campos = fscanf(fichero, "%9[^;];%99[^;];%99[^;];%99[^;];%d;%d;%d\n", dni, nombre, apellido1, apellido2, &dia_baja, &mes_baja, &anio_baja)) == 7) {
        if (mes == mes_baja && anio == anio_baja) {
            printf("\t%-25s %-20s %02d/%02d/%d\n", strcat(strcat(strcpy(nombre, nombre), " "), strcat(strcat(apellido1, " "), apellido2)), dni, dia_baja, mes_baja, anio_baja);
            total_socios++;
        }
    }

    fclose(fichero);

    printf("\t-------------------------------------------------------------------------\n");
    printf("\t** TOTAL: %d socios fueron dados de baja **\n", total_socios);
    printf("\t-------------------------------------------------------------------------\n\n\t");
    system("pause");
}


/***********************************************************************
Subprograma: gestionCursos()

Tipo: void

Parametros de entrada:
                - socios: tReg_Socio que contiene los datos de los socios
                - totalSocios: número total de socios
                - cont_socios: puntero al contador de socios
                - cursos: tReg_Curso que contiene los datos de los cursos
                - cont_cursos: puntero al contador de cursos

Parametros de salida: ------

Prerrequisitos: El struct de cursos debe contener los datos de los cursos.

Objetivo: Mostrar un menú para gestionar los cursos disponibles.
***********************************************************************/
void gestionCursos(tReg_Socio socios[MAX_SOCIOS], int totalSocios, int *cont_socios, tReg_Curso cursos[MAX_CURSOS], int *cont_cursos){
    int opcion;
    do{
        system("cls");
        printf("\n\tSUBMENU GESTION DE CURSOS");
        printf("\n\t=========================\t");
        printf("\n\t1. Alta");
        printf("\n\t2. Baja");
        printf("\n\t3. Modificacion de datos de un curso");
        printf("\n\t4. Consulta de datos de un curso");
        printf("\n\t5. Listado general de cursos");
        printf("\n\t6. Inscripcion de socios a un curso");
        printf("\n\t7. Listado de socios que estan apuntados a un curso");
        printf("\n\t8. Importe medio mensual de los cursos que han sido dados de baja");
        printf("\n\n\t0. Volver al menu principal");
        printf("\n\n\tElija opción: ");
        scanf("%d", &opcion);
        printf("\n\n\t");
        system("pause");

        switch(opcion){

        case 1:
            altaCursos(cursos, cont_cursos);
            break;

        case 2:
            bajaCursos(cursos, cont_cursos); //fichero
            break;

        case 3:
            modificacionDatosCurso(cursos, *cont_cursos);
            break;

        case 4:
            consultaDatosCurso(cursos, *cont_cursos);
            break;

        case 5:
            listadoGeneralCursos(cursos, *cont_cursos);
            break;

        case 6:
            inscribirSocio(cursos, socios, *cont_cursos, *cont_socios);
            break;

        case 7:
            listadoSociosApuntadosCurso(cursos, *cont_cursos, socios, *cont_socios);
            break;

        case 8:
            importeMedioMensualCursosDadosBaja();//fichero
            break;

        case 0:
            break;

        default:
            printf("\n\n\t\tElija una opción válida.");

        }

    }while(opcion != 0);
}

/***********************************************************************
Subprograma: altaCursos()

Tipo: void

Parametros de entrada:
            - cursos: tReg_Curso que contiene los datos de los cursos

Parametros de salida: cont_cursos - puntero al contador de cursos

Prerrequisitos: ------

Objetivo: Registrar un nuevo curso en el sistema.
***********************************************************************/
void altaCursos(tReg_Curso cursos[MAX_CURSOS], int *cont_cursos) {
    char tresLetras[4];
    int opcion;

    do{
        system("cls");
        printf("\tALTA DE CURSOS\n");
        printf("\t==============\n\n");
        printf("\tIntroduzca los datos del nuevo curso:\n");
        printf("\t=====================================\n\n");

        printf("\tIntroduzca el nombre del curso: ");
        fflush(stdin);
        fgets(cursos[*cont_cursos].nombre_curso, sizeof(cursos[*cont_cursos].nombre_curso), stdin);
        cursos[*cont_cursos].nombre_curso[strcspn(cursos[*cont_cursos].nombre_curso, "\n")] = '\0';

        printf("\tIntroduzca el número de plazas: ");
        fflush(stdin);
        scanf("%d", &cursos[*cont_cursos].plazas_totales);
        cursos[*cont_cursos].plazas_disponibles = cursos[*cont_cursos].plazas_totales;

        printf("\tIntroduzca el importe mensual que cada usuario deberá pagar: ");
        fflush(stdin);
        scanf("%f", &cursos[*cont_cursos].precio);

        for(int i = 0; i < 3 && cursos[*cont_cursos].nombre_curso[i] != '\0'; i++) {
            tresLetras[i] = toupper(cursos[*cont_cursos].nombre_curso[i]);
        }
        tresLetras[3] = '\0';
        sprintf(cursos[*cont_cursos].clave, "%s%02d", tresLetras, cursos[*cont_cursos].plazas_totales);

        printf("\n\tCurso dado de alta correctamente. Clave del curso: %s\n", cursos[*cont_cursos].clave);

        printf("\n\n\t¿Desea registrar otro curso? (Sí = 1; No = 2): ");
        fflush(stdin);
        scanf("%d", &opcion);

        (*cont_cursos)++;

        if (*cont_cursos >= MAX_CURSOS) {
                printf("\n\tSe ha alcanzado el número máximo de cursos permitidos.\n");
                break;
            }

    } while ((opcion == 1) && (*cont_cursos < (MAX_CURSOS - 1)));

    printf("\n\n\t");
    system("pause");
}

/***********************************************************************
Subprograma: bajaCursos()

Tipo: void

Parametros de entrada:
            - cursos: tReg_Curso que contiene los datos de los cursos

Parametros de salida:
            - cont_cursos: puntero al contador de cursos

Prerrequisitos: ------

Objetivo: Dar de baja un curso del sistema.
***********************************************************************/
void bajaCursos(tReg_Curso cursos[MAX_CURSOS], int *cont_cursos) {
    char claveCurso[6];
    int i, opcion;

    do {
        system("cls");
        printf("\n\tBAJA DE CURSOS");
        printf("\n\t==============");
        printf("\n\n\tIntroduzca la clave del curso a dar de baja: ");
        fflush(stdin);
        fgets(claveCurso, sizeof(claveCurso), stdin);
        claveCurso[strcspn(claveCurso, "\n")] = '\0';

        i = buscarCurso(cursos, *cont_cursos, claveCurso);

        if (i != -1) {
            mostrarCurso(cursos, i);

            printf("\n\n\t¿Desea dar de baja a este curso? (Sí = 1; No = 2): ");
            fflush(stdin);
            scanf("%i", &opcion);

            if (opcion == 1) {
                if (cursos[i].apuntados != 0) {
                    printf("\n\tBaja de curso cancelada, hay socios inscritos\n");
                } else {
                    FILE *fp = fopen("bajaHcoCursos.dat", "ab");
                    if (fp == NULL) {
                        printf("\n\tError al abrir el archivo bajaHcoCursos.dat para escritura.\n");
                    } else {
                        fprintf(fp, "%s;%s;%.2f;%d;%d\n", cursos[i].clave, cursos[i].nombre_curso, cursos[i].precio, cursos[i].plazas_totales, cursos[i].plazas_disponibles);
                        fclose(fp);

                        for (int j = i; j < (*cont_cursos) - 1; j++) {
                            cursos[j] = cursos[j + 1];
                        }
                        (*cont_cursos)--;
                        printf("\n\tCurso dado de baja correctamente.\n");
                    }
                }
            } else {
                printf("\n\tBaja de curso cancelada.\n");
            }
        } else {
            printf("\n\tCurso no encontrado.\n");
        }

        printf("\n\n\t¿Desea dar de baja otro curso? (Sí = 1; No = 2): ");
        fflush(stdin);
        scanf("%i", &opcion);

    } while (opcion == 1);

    printf("\n\n\t");
    system("pause");
}

/********************   ***************************************************
Subprograma: modificacionDatosCurso()

Tipo: void

Parametros de entrada:
            - cursos: tReg_Curso que contiene los datos de los cursos
            - cont_cursos - número total de cursos

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Modificar los datos de un curso en el sistema.
***********************************************************************/
void modificacionDatosCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos) {
    char claveSub[6];
    char tresLetras[4];
    int opcion, i;
    char continuar;

    do {
        system("cls");
        printf("\n\tMODIFICACION DE UN CURSO");
        printf("\n\t========================");
        printf("\n\n\tIntroduzca la clave del curso que quiere modificar: ");
        scanf("%s", claveSub);

        int j = 0;
        while (claveSub[j]) {
            claveSub[j] = toupper(claveSub[j]);
            j++;
        }
        while (getchar() != '\n');

        i = buscarCurso(cursos, cont_cursos, claveSub);

        if (i != -1) {
            printf("\n");
            mostrarCurso(cursos, i);
            do {
                printf("\n\n\t******************************************");
                printf("\n\n\t\t¿Qué información desea modificar?");
                printf("\n\t\t\t1.- Nombre");
                printf("\n\t\t\t2.- Precio");
                printf("\n\n\t\t\t0.- Salir de las modificaciones");
                printf("\n\n\t\t\tElija opción: ");
                scanf("%i", &opcion);

                switch (opcion) {
                    case 1:
                        printf("\n\tNombre actual: %s", cursos[i].nombre_curso);
                        printf("\n\tIngrese el nuevo nombre: ");
                        scanf("%s", cursos[i].nombre_curso);
                        for(int j = 0; j < 3 && cursos[i].nombre_curso[j] != '\0'; i++) {
                            tresLetras[j] = toupper(cursos[i].nombre_curso[j]);
                        }
                        tresLetras[3] = '\0';
                        sprintf(cursos[i].clave, "%s%02d", tresLetras, cursos[i].plazas_totales);
                        break;

                    case 2:
                        printf("\n\tPrecio actual: %f", cursos[i].precio);
                        printf("\n\tIngrese el nuevo precio: ");
                        scanf("%f", &cursos[i].precio);
                        break;

                    case 0:
                        break;

                    default:
                        printf("\n\n\t\tElija una opción válida.");
                }
            } while (opcion != 0);
        } else {
            printf("\n\n\t\tERROR: Este curso no figura en nuestro registro.\n");
        }

        printf("\n\n\t¿Desea modificar los datos de otro curso? (s/n): ");
        fflush(stdin);
        scanf(" %c", &continuar);
    } while (toupper(continuar) == 'S');

    printf("\n\n\t");
    system("pause");
}

/***********************************************************************
Subprograma: consultaDatosCurso()

Tipo: void

Parametros de entrada:
            - cursos: tReg_Curso que contiene los datos de los cursos
            - cont_cursos - puntero al número total de cursos

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Consultar los datos de un curso dado su clave.
***********************************************************************/
void consultaDatosCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos){
    char claveSub[6], respuesta;
    int i;

    do{
        system("cls");
        printf("\n\t\tCONSULTA DATOS DE UN CURSO");
        printf("\n\t\t==========================");
        printf("\n\n\tIntroduzca la clave del curso a consultar: ");
        scanf("%s", claveSub);

        int j = 0;
        while (claveSub[j]) {
            claveSub[j] = toupper(claveSub[j]);
            j++;
        }
        while (getchar() != '\n');

        i = buscarCurso(cursos, cont_cursos, claveSub);

        if (i != -1){
            mostrarCurso(cursos, i);
        }
        else{
            printf("\n\n\tEl curso con clave %s no se encuentra registrado.\n", claveSub);
        }

        printf("\n\n\t¿Desea ver los datos de otro curso? (S/N): ");
        scanf(" %c", &respuesta);
    }while (respuesta == 's' || respuesta == 'S');

    printf("\n\n\t");
    system("pause");
}


/***********************************************************************
Subprograma: listadoGeneralCursos()

Tipo: void

Parametros de entrada:
            - cursos: tReg_Curso que contiene los datos de los cursos
            - cont_cursos: cantidad total de cursos

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Mostrar un listado general de todos los cursos registrados.
***********************************************************************/
void listadoGeneralCursos(tReg_Curso cursos[MAX_CURSOS], int cont_cursos){
    int i;

    system("cls");
    printf("\n\t\t\tLISTADO GENERAL DE CURSOS");
    printf("\n\t\t\t=========================");
    printf("\n\n\t%-12s %-12s %-15s %-25s %-20s %-24s", "Clave", "Nombre", "Plazas Totales", "Nº de inscritos al curso", "Plazas disponibles", "Precio mensual (euros)");
    printf("\n\t==============================================================================================================");

    for (i = 0; i < cont_cursos; i++) {
        printf("\n\t%-12s %-12s %-15i %-25i %-20i %-24.2f", cursos[i].clave, cursos[i].nombre_curso, cursos[i].plazas_totales, cursos[i].apuntados, cursos[i].plazas_disponibles, cursos[i].precio);
    }

    printf("\n\n\t");
    system("pause");
}

/*****************************************************************************
Subprograma: inscribirSocio()

Tipo: void

Parametros de entrada:
                - cursos: tReg_Curso que contiene los datos de los cursos
                - socios: tReg_Socio que contiene los datos de los socios
                - cont_cursos - cantidad total de cursos
                - cont_socios - cantidad total de socios

Parametros de salida: ------

Prerrequisitos: ------

 Objetivo: Inscribir a un socio en un curso dado su DNI y la clave del curso.
******************************************************************************/
void inscribirSocio(tReg_Curso cursos[MAX_CURSOS], tReg_Socio socios[MAX_SOCIOS], int cont_cursos, int cont_socios) {
    char claveSub[6], dniSub[10];
    int indCurso, indSocio, opcion, continuar;
    int esAlfanumerico = 1;

    do {
        system("cls");
        printf("\n\tINSCRIPCIÓN DE SOCIO EN UN CURSO");
        printf("\n\t=================================\n");

        printf("\n\tIntroduzca la clave del curso al que quiere inscribir al socio: ");
        fflush(stdin);
        fgets(claveSub, sizeof(claveSub), stdin);
        claveSub[strcspn(claveSub, "\n")] = 0;

        for (int t = 0; claveSub[t]; t++) {
            claveSub[t] = toupper(claveSub[t]);
        }

        indCurso = buscarCurso(cursos, cont_cursos, claveSub);
        mostrarCurso(cursos, indCurso);

        if (indCurso != -1) {
            do {
                do {
                    printf("\n\tIntroduzca el DNI del socio para inscribirse al curso: ");
                    fflush(stdin);
                    fgets(dniSub, sizeof(dniSub), stdin);
                    dniSub[strcspn(dniSub, "\n")] = 0;

                    if (strlen(dniSub) != 9) {
                        printf("\n\tERROR: El DNI debe tener 9 caracteres.\n");
                        continue;
                    }

                    for (int i = 0; dniSub[i] != '\0'; i++) {
                        if (!isalnum(dniSub[i])) {
                            esAlfanumerico = 0;
                            break;
                        }
                    }

                    if (!esAlfanumerico) {
                        printf("\n\tERROR: El DNI debe ser alfanumérico.\n");
                    }

                } while (strlen(dniSub) != 9 || !esAlfanumerico);

                indSocio = buscarSocio(socios, cont_socios, dniSub);

                if (indSocio != -1) {
                    int yaInscrito = 0;
                    for (int i = 0; i < socios[indSocio].num_cursos_inscritos; i++) {
                        if (strcmp(socios[indSocio].curso[i], claveSub) == 0) {
                            yaInscrito = 1;
                            break;
                        }
                    }

                    if (yaInscrito) {
                        printf("\n\tERROR: Este socio ya está inscrito en este curso.\n");
                    } else {
                        if (socios[indSocio].num_cursos_inscritos < MAX_C_MATRICULADOS) {
                            strcpy(socios[indSocio].curso[socios[indSocio].num_cursos_inscritos], claveSub);
                            socios[indSocio].num_cursos_inscritos++;
                            cursos[indCurso].apuntados++;
                            cursos[indCurso].plazas_disponibles--;
                            printf("\n\tSocio inscrito correctamente en el curso.\n");
                        } else {
                            printf("\n\tERROR: Este socio ya está inscrito en el máximo de cursos permitidos.\n");
                        }
                    }
                } else {
                    printf("\n\tERROR: Este socio no está registrado en nuestro sistema.\n");
                }
                printf("\n\t¿Desea inscribir a otro socio en este curso? (Sí = 1; No = 2): ");
                scanf("%d", &opcion);
                while(getchar() != '\n');

            } while (opcion == 1);
        } else {
            printf("\n\tERROR: Curso no encontrado.\n");
        }

        printf("\n\t¿Desea inscribir socios en otro curso o salir al menú? (Inscribir en otro curso = 1; Salir al menú = 2): ");
        scanf("%d", &continuar);
        while(getchar() != '\n');
    } while (continuar == 1);

    printf("\n\n\t");
    system("pause");
}

/***********************************************************************
Subprograma: listadoSociosApuntadosCurso()
Tipo: void
Parametros de entrada: cursos - arreglo de estructuras tReg_Curso que contiene los datos de los cursos
                       cont_cursos - cantidad total de cursos
                       socios - arreglo de estructuras tReg_Socio que contiene los datos de los socios
                       cont_socios - cantidad total de socios
Parametros de salida: ------
Prerrequisitos: ------
Objetivo: Mostrar un listado de socios que están apuntados a un curso dado su clave.
***********************************************************************/
void listadoSociosApuntadosCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos, tReg_Socio socios[MAX_SOCIOS], int cont_socios) {
    int i, j, k, opcion;
    char claveSub[6];

    do {
        system("cls");
        printf("\n\tLISTADO DE SOCIOS APUNTADOS A UN CURSO");
        printf("\n\t=======================================");
        printf("\n\n\tIntroduzca la clave del curso: ");
        scanf("%s", claveSub);

        j = 0;
        while (claveSub[j]) {
            claveSub[j] = toupper(claveSub[j]);
            j++;
        }
        while (getchar() != '\n');

        i = buscarCurso(cursos, cont_cursos, claveSub);

        if (i == -1) {
            printf("\n\tERROR: Este curso no está registrado en nuestro sistema.\n");
        } else {
            system("cls");

            printf("\n\tLISTADO DE SOCIOS APUNTADOS AL CURSO :  %s", cursos[i].nombre_curso);
            printf("\n\t==================================================\n");

            int encontrado = 0;
            int cont_socios_insCursos = 0;
            for (j = 0; j < cont_socios; j++) {
                for (k = 0; k < socios[j].num_cursos_inscritos; k++) {
                    if (strcmp(socios[j].curso[k], claveSub) == 0) {
                        encontrado = 1;
                        cont_socios_insCursos ++;
                        printf("\n\t %d -> %s %s %s", cont_socios_insCursos, socios[j].nombre_socio, socios[j].apellido_1, socios[j].apellido_2);
                        break;
                    }
                }
            }

            if (!encontrado) {
                printf("\n\tNo hay socios inscritos en este curso.\n");
            }
        }

        printf("\n\n\n\t¿Desea ver el listado de otro curso? (Sí = 1; No = 2): ");
        scanf("%d", &opcion);

    } while (opcion == 1);
}

/***********************************************************************
Subprograma: importeMedioMensualCursosDadosBaja() FICHERO: bajaHcoCursos.dat
Tipo:
Parametros de entrada:
Parametros de salida:
Prerrequisitos:
Objetivo:
***********************************************************************/
void importeMedioMensualCursosDadosBaja() {
    system("cls");

    FILE *fp = fopen("bajaHcoCursos.dat", "rb");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo bajaHcoCursos.dat\n");
        system("pause");
        return;
    }

    printf("\n\tIMPORTE DE LOS CURSOS DADOS DE BAJA");
    printf("\n\t====================================\n\n");

    char linea[100];
    float suma_precios = 0.0;
    int contador_cursos = 0;

    printf("\tListado de cursos dados de baja:\n\n");
    printf("\tClave\tNombre\t\tPrecio\tPlazas Totales\tPlazas Disponibles\n");
    printf("\t-------------------------------------------------------------------\n");

    while (fgets(linea, sizeof(linea), fp)) {
        char clave[6];
        char nombre[30];
        float precio;
        int plazasTotales, plazasDisponibles;

        sscanf(linea, "%[^;];%[^;];%f;%d;%d", clave, nombre, &precio, &plazasTotales, &plazasDisponibles);

        printf("\t%-6s\t%-15s\t%.2f\t%d\t\t%d\n", clave, nombre, precio, plazasTotales, plazasDisponibles);

        suma_precios += precio;
        contador_cursos++;
    }

    fclose(fp);

    if (contador_cursos > 0) {
        float importe_medio = suma_precios / contador_cursos;
        printf("\n\n\t** TOTAL DE CURSOS DADOS DE BAJA: %d **", contador_cursos);
        printf("\n\t** IMPORTE MEDIO MENSUAL DE LOS CURSOS DADOS DE BAJA: %.2f **", importe_medio);
    } else {
        printf("\n\n\tNo hay cursos dados de baja en el archivo.");
    }

    printf("\n\n\t");
    system("pause");
}
/***********************************************************************
Subprograma: informesEconomicos()

Tipo: void

Parametros de entrada:
    - socios: arreglo de estructuras tReg_Socio que contiene los datos de los socios
    - cont_socios: cantidad total de socios
    - cursos: arreglo de estructuras tReg_Curso que contiene los datos de los cursos
    - cont_cursos: cantidad total de cursos

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Mostrar un menú de opciones para generar informes económicos.
***********************************************************************/
void informesEconomicos(tReg_Socio socios[MAX_SOCIOS], int *cont_socios, tReg_Curso cursos[MAX_CURSOS], int *cont_cursos){
    int opcion;
    do{
        system("cls");
        printf("\n\tSUBMENU INFORMES ECONOMICOS");
        printf("\n\t===========================");
        printf("\n\t1. Informe mensual (por cuotas básicas)");
        printf("\n\t2. Informe mensual (de un curso)");
        printf("\n\t3. Informe mensual (todos los cursos)");
        printf("\n\n\t0. Volver al menu principal");
        printf("\n\n\tElija opción: ");
        scanf("%d", &opcion);
        printf("\n\n\t");
        system("pause");

        switch(opcion){

        case 1:
            informeMensualCuotasBasicas(socios, *cont_socios);
            break;

        case 2:
            informeMensualCurso(cursos, *cont_cursos);
            break;

        case 3:
            informeMensualTodosCursos(socios, *cont_socios, cursos, *cont_cursos);
            break;

        case 0:
            break;

        default:
            printf("\n\n\t\tElija una opción válida.");

        }

    }while(opcion != 0);
}

/*********************************************************************************
Subprograma: informeMensualCuotasBasicas()

Tipo: void

Parametros de entrada:
    - socios: tReg_Socio que contiene los datos de los socios
    - cont_socios: cantidad total de socios

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Generar un informe mensual de las cuotas básicas pagadas por los socios.
***********************************************************************************/
void informeMensualCuotasBasicas(tReg_Socio socios[MAX_SOCIOS], int cont_socios) {
    int num_normales = 0, num_jubilados = 0, num_infantiles = 0, i;
    float cuota_normal = 0, cuota_jubilados = 0, cuota_infantil = 0, total = 0;

    system("cls");
    printf("\n\tINFORME MENSUAL (Por cuotas basicas)");
    printf("\n\t====================================");

    for (i = 0; i < cont_socios; i++) {
        if (socios[i].tipo == 1) {
            num_normales++;
            cuota_normal += CUOTA1;
        } else if (socios[i].tipo == 2) {
            num_jubilados++;
            cuota_jubilados += CUOTA2;
        } else if (socios[i].tipo == 3) {
            num_infantiles++;
            cuota_infantil += CUOTA3;
        }
    }

    total = cuota_normal + cuota_jubilados + cuota_infantil;

    printf("\n\t**Numero de socios:");
    printf("\n\t-------------------");
    printf("\n\tSocios Normales: %-12i", num_normales);
    printf("\n\tSocios Jubilados: %-12i", num_jubilados);
    printf("\n\tSocios Infantiles: %-12i", num_infantiles);
    printf("\n\t----------------------------");
    printf("\n\tNº Total de Socios: %-12i", cont_socios);
    printf("\n\n\t**Importes Registrados (Por cuotas basicas):");
    printf("\n\t--------------------------------------------");
    printf("\n\tSocios Normales: %i x %.2f = %.2f", num_normales, (float)CUOTA1, num_normales * (float)CUOTA1);
    printf("\n\tSocios Jubilados: %i x %.2f = %.2f", num_jubilados, (float)CUOTA2, num_jubilados * (float)CUOTA2);
    printf("\n\tSocios Infantiles: %i x %.2f = %.2f", num_infantiles, (float)CUOTA3, num_infantiles * (float)CUOTA3);
    printf("\n\t-------------------------------------------");
    printf("\n\t\t\tImporte Total = %.2f\n\n\n\t", total);

    system("pause");
}
/***********************************************************************
Subprograma: informeMensualCurso()

Tipo: void

Parametros de entrada:
    - socios: tReg_Socio que contiene los datos de los socios
    - cont_socios: cantidad total de socios
    - cursos: tReg_Curso que contiene los datos de los cursos
    - cont_cursos: cantidad total de cursos

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Generar un informe mensual del curso seleccionado.
***********************************************************************/
void informeMensualCurso(tReg_Curso cursos[MAX_CURSOS], int cont_cursos){
    int opcion, i = 0;

    do {
        system("cls");
        printf("\n\t\tCURSOS ACTUALES");
        printf("\n\t=======================================================\n");

        for(i = 0; i < cont_cursos; i++){
            printf("\t\t%d .- %s\n", i+1, cursos[i].nombre_curso);
        }

        printf("\n\t\t¿Qué curso desea consultar?: ");
        scanf("%d", &opcion);
        printf("\n\n\t");
        system("pause");
        system("cls");

        printf("\n\t=======================================================================\n");
        printf("\t\tINFORME MENSUAL (Curso %s - %s)\n", cursos[opcion-1].nombre_curso, cursos[opcion-1].clave);
        printf("\t=======================================================================\n");
        printf("\t\tCuota mensual: \t\t%.2f euros\n", cursos[opcion-1].precio);
        printf("\t\tPlazas totales:\t\t%d\n", cursos[opcion-1].plazas_totales);
        printf("\t\tSocios inscritos:\t%d\n", cursos[opcion-1].apuntados);
        printf("\t\tPlazas disponibles:\t%d\n", cursos[opcion-1].plazas_disponibles);
        printf("\t-----------------------------------------------------------------------------------------------------\n");
        printf("\t\tImporte mensual registrado (sin aplicar descuentos): %d x %.2f = %.2f euros\n", cursos[opcion-1].apuntados, cursos[opcion-1].precio, cursos[opcion-1].precio * cursos[opcion-1].apuntados);

        printf("\n\n\t");
        printf("¿Desea consultar otro curso? (Sí = 1; No = 2): ");
        scanf("%d", &opcion);
    } while (opcion == 1);

    printf("\n\n\t");
    system("pause");
}

/***********************************************************************
Subprograma: informeMensualTodosCursos()
Tipo:
Parametros de entrada:
Parametros de salida:
Prerrequisitos:
Objetivo:
***********************************************************************/
void informeMensualTodosCursos(tReg_Socio socios[MAX_SOCIOS], int cont_socios, tReg_Curso cursos[MAX_CURSOS], int cont_cursos){

    float importe_total = 0.0;
    int total_participantes = 0;

    system("cls");

    printf("\n\tINFORME MENSUAL (Todos los cursos)\n");
    printf("\t----------------------------------------------------\n");
    printf("\t%-10s %-17s %-20s %-24s %-22s\n", "Curso", "Socios Inscritos", "Plazas Disponibles", "Importe Mensual (euros)", "Importe Total (euros) (sin descuentos)");
    printf("\t-------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cont_cursos; i++) {
        printf("\t%-10s %-17d %-20d %-24.2f %-22.2f\n", cursos[i].nombre_curso, cursos[i].apuntados, cursos[i].plazas_disponibles, cursos[i].precio, cursos[i].precio * cursos[i].apuntados);
        total_participantes += cursos[i].apuntados;
        importe_total += cursos[i].precio * cursos[i].apuntados;
    }

    printf("\t-------------------------------------------------------------------------------------------------------------\n");
    printf("\tNúmero total de participantes en los cursos:  %d\n", total_participantes);
    printf("\tImporte total registrado al mes por cursos => %.2f euros\n", importe_total);
    printf("\t-------------------------------------------------------------------------------------------------------------\n\n\t");
    system("pause");
}

/***********************************************************************
Subprograma: importarCursos()

Tipo: void

Parametros de entrada:
    - cursos: tReg_Curso donde se almacenarán los cursos importados
    - cont_cursos: puntero a entero que lleva el control del número de cursos en el arreglo
    - socios: tReg_Socio con los datos de los socios (no se utiliza en esta función)
    - cont_socios: puntero a entero con el número de socios (no se utiliza en esta función)

Parametros de salida: ------

Prerrequisitos: El archivo "cursos.txt" debe existir y tener un formato válido.

Objetivo: Importar los cursos desde un archivo de texto y almacenarlos en el arreglo de cursos.
***********************************************************************/
void importarCursos(tReg_Curso cursos[MAX_CURSOS], int *cont_cursos) {
    char linea[200];
    char nombre_curso[MAX_NOMBRE];
    int plazas_totales;
    float precio;
    char clave[6];
    int existe, opcion;
    int cursos_importados = 0;


    system("cls");
    printf("\n\t================");
    printf("\n\tIMPORTAR CURSOS");
    printf("\n\t================\n\n\t");

    do{
        printf("¿Desea importar los cursos? (Sí = 1; No = 2): ");
        scanf("%d", &opcion);
    }while (opcion != 1 && opcion != 2);


    if (opcion == 1){
        FILE *fichero = fopen("cursos.txt", "r");
        if (fichero == NULL) {
            fichero = fopen ("cursos.txt", "w");
            if (fichero == NULL) {
                printf("No se pudo abrir el archivo cursos.txt\n");
                return;
            }
        }

        printf("\n\tCURSOS IMPORTADOS:\n\n");
        printf("\tClave\tNombre\t\tPlazas\tPrecio\n");
        printf("\t-----------------------------------------------------\n");

        while (fgets(linea, sizeof(linea), fichero) != NULL) {
            sscanf(linea, "%[^#]#%d#%f", nombre_curso, &plazas_totales, &precio);

            snprintf(clave, sizeof(clave), "%.3s%02d", nombre_curso, plazas_totales);
            for (int i = 0; clave[i]; i++) {
                clave[i] = toupper(clave[i]);
            }

            existe = 0;
            for (int i = 0; i < *cont_cursos; i++) {
                if (strcmp(cursos[i].clave, clave) == 0) {
                    existe = 1;
                    break;
                }
            }

            if (!existe && *cont_cursos < MAX_CURSOS) {
                strcpy(cursos[*cont_cursos].nombre_curso, nombre_curso);
                cursos[*cont_cursos].plazas_totales = plazas_totales;
                cursos[*cont_cursos].plazas_disponibles = plazas_totales;
                cursos[*cont_cursos].precio = precio;
                strcpy(cursos[*cont_cursos].clave, clave);
                cursos[*cont_cursos].apuntados = 0;
                (*cont_cursos)++;
                cursos_importados++;
                // Imprimir el curso importado
                printf("\t%s\t%-15s\t%d\t%.2f\n", clave, nombre_curso, plazas_totales, precio);
            }
        }

        fclose(fichero);
        if (cursos_importados == 0) {
            printf("\n\tNo se importaron nuevos cursos.\n");
        } else {
            printf("\t-----------------------------------------------------\n");
            printf("\t%d curso(s) importado(s) exitosamente.\n", cursos_importados);
    }
    }

    printf("\n\n\n\t");
    system("pause");
}

/***********************************************************************
Subprograma: buscarSocio()

Tipo: int

Parametros de entrada:
    - socios: arreglo de estructuras tReg_Socio
    - cont_socios: entero que indica el número de socios
    - DNI: cadena de caracteres que representa el DNI del socio a buscar

Parametros de salida: int

Prerrequisitos: La estructura tReg_Socio debe estar definida.

Objetivo: Buscar un socio en el arreglo de socios y devolver la posición que ocupa en el arreglo, o -1 si no se encuentra.
***********************************************************************/
int buscarSocio(tReg_Socio socios[MAX_SOCIOS], int cont_socios, char dniSub[10]) {
    int i;
    for (i = 0; i < cont_socios; i++) {
        if (strcmp(socios[i].DNI, dniSub) == 0) {
            return i;
        }
    }
    return -1;
}

/***********************************************************************
Subprograma: buscarCurso()

Tipo: int

Parametros de entrada:
    - cursos: arreglo de estructuras tReg_Curso
    - cont_cursos: entero que indica el número de cursos
    - clave: cadena de caracteres que representa la clave del curso a buscar

Parametros de salida: int

Prerrequisitos: La estructura tReg_Curso debe estar definida.

Objetivo: Buscar un curso en el arreglo de cursos y devolver la posición que ocupa en el arreglo, o -1 si no se encuentra.
***********************************************************************/
int buscarCurso(tReg_Curso cursos[], int cont_cursos, char claveSub[6]) {
    for (int i = 0; i < cont_cursos; i++) {
        if (strcmp(cursos[i].clave, claveSub) == 0) {
            return i;
        }
    }
    return -1;
}
/*****************************************************************************
Subprograma: mostrarSocio()

Tipo: void

Parametros de entrada:
            - socios: tReg_Socio que contiene los datos de los socios
            - cont_socios: número entero que representa la cantidad
                        de socios almacenados en el struct

Parametros de salida: -----

Prerrequisitos: Se asume que los socios almacenados en el arreglo "socios"
                contienen datos válidos y que "cont_socios" es la cantidad
                correcta de socios almacenados.

Objetivo: Mostrar los datos de un socio específico seleccionado por el usuario.
********************************************************************************/
void mostrarSocio(tReg_Socio socios[MAX_SOCIOS], int index) {
    printf("\n\tNombre: %s", socios[index].nombre_socio);
    printf("\n\tApellido 1: %s", socios[index].apellido_1);
    printf("\n\tApellido 2: %s", socios[index].apellido_2);
    printf("\n\tDNI: %s", socios[index].DNI);
    printf("\n\tTipo: %d", socios[index].tipo);
    printf("\n\tCódigo de Socio: %s", socios[index].codigoSocio);
}

/***********************************************************************
Subprograma: mostrarCurso()

Tipo: void

Parametros de entrada:
            - cursos: tReg_Curso que contiene los datos de los cursos
            - cont_cursos: número entero que representa la cantidad de
                           cursos almacenados en el struct

Parametros de salida: -------

Prerrequisitos: Se asume que los cursos almacenados en el arreglo "cursos"
                contienen datos válidos y que "cont_cursos" es la cantidad
                correcta de cursos almacenados.

Objetivo: Mostrar los datos de un curso específico seleccionado por el usuario.
********************************************************************************/
void mostrarCurso(tReg_Curso cursos[], int indiceC){
    cursos[indiceC].plazas_disponibles = cursos[indiceC].plazas_totales - cursos[indiceC].apuntados;

    printf("\n\tDATOS DEL CURSO");
    printf("\n\t================\n\n\t");
    printf("Nombre del curso:       %s\n\t", cursos[indiceC].nombre_curso);
    printf("Clave del curso:        %s\n\t", cursos[indiceC].clave);
    printf("Plazas disponibles:     %d\n\t", cursos[indiceC].plazas_disponibles);
    printf("Plazas totales:         %d\n\t", cursos[indiceC].plazas_totales);
    printf("Importe mensual:        %.2f\n\t", cursos[indiceC].precio);
    printf("Socios inscritos:       %d\n\t", cursos[indiceC].apuntados);

}
/***********************************************************************
Subprograma: mensajeBienvenida()
Tipo: void
Parametros de entrada:------
Parametros de salida: ------
Prerrequisitos:------
Objetivo: Imprimir en pantalla un mensjae que de la bienvenida a la
          aplicacion al usuario.
***********************************************************************/
void mensajeBienvenida(){

    printf("\n\n\t***************************************");
    printf("\n\t* Bienvenido a la aplicación GEST-GYM *");
    printf("\n\t***************************************\n\n\n\t");

    system("pause");
    system("cls");
}

/***********************************************************************
Subprograma: mensajeDespedida()

Tipo: void

Parametros de entrada: ------

Parametros de salida: ------

Prerrequisitos: ------

Objetivo: Mostrar un mensaje de despedida y limpiar la pantalla.
***********************************************************************/
void mensajeDespedida(){
    system("cls");

    printf("\n\n\t*************************************************");
    printf("\n\t* Gracias por utilizar la aplicación \"GEST-GYM\" *");
    printf("\n\t*************************************************\n\n\n\t");

    system("pause");
    system("cls");
}

/************************************************************************************
Subprograma: sociosCargDat()

Tipo: void

Parametros de entrada:
    - socios: registro de socios

Parametros de salida: ---

Prerrequisitos:-----

Objetivo: cargar los datos del fihero binario "socios.dat"
**************************************************************************************/
void sociosCargDat(tReg_Socio socios[MAX_SOCIOS]) {
    FILE *f;
    f = fopen("socios.dat","rb");
    int i = 0;

    if(f == NULL){
        f = fopen("socios.dat", "wb");
        if (f == NULL) {
            printf("Error al crear el fichero socios.dat.\n");
            exit(1);
        }
    }else{
        fread(&socios[i], sizeof(tReg_Socio), 1, f);
        while(!feof(f)){
            i++;
            fread(&socios[i], sizeof(tReg_Socio), 1, f);
        }
    }
    fclose(f);
}

/************************************************************************************
Subprograma: cursosCargDat()

Tipo: void

Parametros de entrada:
    - cursos: registro de cursos

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "cursos.dat"
**************************************************************************************/
void cursosCargDat(tReg_Curso cursos[MAX_CURSOS]) {
    FILE *f;

    f = fopen("cursos.dat","rb");
    int i = 0;

    if(f == NULL){
        f = fopen("cursos.dat", "wb");
        if (f == NULL) {
            printf("Error al crear el fichero cursos.dat.\n");
            exit(1);
        }
    }else{
        fread(&cursos[i], sizeof(tReg_Curso), 1, f);
        while(!feof(f)){
            i++;
            fread(&cursos[i], sizeof(tReg_Curso), 1, f);
        }
    }
    fclose(f);
}

/************************************************************************************
Subprograma: contCargDat()

Tipo: void

Parametros de entrada:
    - contadores de socios y cursos.

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "contadores.dat"
**************************************************************************************/
void contCargDat(int *cont_socios, int *cont_cursos) {
     FILE *f = fopen("contadores.dat", "rb");
     if (f == NULL) {
        f = fopen("contadores.dat", "wb");
        if (f == NULL) {
            printf("Error al crear el fichero contadores.dat.\n");
            exit(1);
        }
     }

    fread(cont_socios, sizeof(int), 1, f);
    fread(cont_cursos, sizeof(int), 1, f);
    fclose(f);
}

/************************************************************************************
Subprograma: totalSociosCargDat()

Tipo: void

Parametros de entrada:
    - contador global de socios.

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "totalGlobalSocios.dat"
**************************************************************************************/
void totalSociosCargDat(int *totalSocios){
    FILE *f = fopen("totalGlobalSocios.dat", "rb");
     if (f == NULL) {
        f = fopen("totalGlobalSocios.dat", "wb");
        if (f == NULL) {
            printf("Error al crear el fichero totalGlobalSocios.dat\n");
            exit(1);
        }
    }

    fread(totalSocios, sizeof(int), 1, f);
    fclose(f);
}

/************************************************************************************
Subprograma: sociosGuardDat()

Tipo: void

Parametros de entrada:
    - socios : registro de socios
    - contador de socios

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "socios.dat"
**************************************************************************************/
void sociosGuardDat(tReg_Socio socios[MAX_SOCIOS], int cont_socios) {
    FILE *f = fopen("socios.dat", "wb");
    if (f == NULL) {
        printf("Error al abrir el fichero socios.dat para escritura.\n");
        exit(1);
    }

    for (int i = 0; i < cont_socios; i++) {
        fwrite(&socios[i], sizeof(tReg_Socio), 1, f);
    }

    fclose(f);
}

/************************************************************************************
Subprograma: cursosGuardDat()

Tipo: void

Parametros de entrada:
    - cursos : registro de cursos
    - contador de cursos

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "cursos.dat"
**************************************************************************************/
void cursosGuardDat(tReg_Curso cursos[MAX_CURSOS], int cont_cursos) {
    FILE *f = fopen("cursos.dat", "wb");
    if (f == NULL) {
        printf("Error al abrir el fichero cursos.dat para escritura.\n");
        exit(1);
    }

    for (int i = 0; i < cont_cursos; i++) {
        fwrite(&cursos[i], sizeof(tReg_Curso), 1, f);
    }

    fclose(f);
}

/************************************************************************************
Subprograma: contGuardDat()

Tipo: void

Parametros de entrada:
    - contador de socios
    - contador de cursos

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "contadores.dat"
**************************************************************************************/
void contGuardDat(int cont_socios, int cont_cursos) {
    FILE *f = fopen("contadores.dat", "wb");
    if (f == NULL) {
        printf("Error al abrir el fichero contadores.dat para escritura.\n");
        exit(1);
    }

    fwrite(&cont_socios, sizeof(int), 1, f);
    fwrite(&cont_cursos, sizeof(int), 1, f);
    fclose(f);
}

/************************************************************************************
Subprograma: totalSociosGuardDat()

Tipo: void

Parametros de entrada:
    - contador global de socios

Parametros de salida: ----

Prerrequisitos:----

Objetivo: cargar el fichero "totalGlobalSocios.dat"
**************************************************************************************/
void totalSociosGuardDat(int totalSocios){
    FILE *f = fopen("totalGlobalSocios.dat","wb");
    if (f == NULL) {
        printf("Error al abrir el fichero totalGlobalSocios.dat para escritura.\n");
        exit(1);
    }

    fwrite(&totalSocios, sizeof(int), 1, f);
    fclose(f);
}
