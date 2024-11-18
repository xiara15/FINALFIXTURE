#ifndef FUNCION_H_INCLUDED
#define FUNCION_H_INCLUDED
#include <stdio.h>     // Incluir librería para printf y scanf
#include <stdlib.h>    // Incluir librería para system y exit
#include <string.h>

// Declaración de archivos globales
FILE *archivoEquipos;
FILE *archivoGrupo;

// Estructura para guardar los nombres de los equipos
struct equipos {
    char nombreEquipo[50];
};

// Estructura para guardar los grupos de los equipos
struct grupos {
    struct equipos equipo[4];
};

// Estructura para guardar las estadísticas de los partidos
struct estadisticas {
    int partidoGanado;
    int partidoPerdido;
    int partidoEmpatado;
    int partidoJugado;
    int golesFavor;
    int golesContra;
    int diferenciaGol;
    int puntos;
};
//Estructura para guardar el nombre de la competencia y los equipos
struct competencia {
    char nombreCompetencia[50];
    struct grupos grupo [4];

};

// Prototipos de funciones
void CrearMenu();
void crearFixture() ;


// Función para el menú principal
void CrearMenu() {
    int opcion;
    do {
        printf("\n========== Menu Principal =========");
        printf("\n|        1.Crear Fixture          |");
        printf("\n|        2.Menu Fixture           |");
        printf("\n|        3.Salir                  |");
        printf("\n===================================");
        printf("\nIngrese la opcion que desee ver: ");
        fflush(stdin);
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 1:
                system("cls");
                crearFixture();

                break;
            case 2:
                system("cls");
                menuFixture ();

                // Aquí puedes llamar a la función verFixture cuando esté definida
                break;
            case 3:
                exit(0);
                break;
            default:
                system("cls");
                printf("La opcion es incorrecta, volve a intentar de nuevo.\n");
                break;
        }
    } while (opcion != 3);
}

// Definición de la función crearFixture

void crearFixture() {
    char nombreCompetencia[50];
    struct grupos grupo;

    // Solicitar nombre de la competencia
    printf("Ingrese el nombre de la competencia que se va a jugar: ");
    fflush(stdin);
    fgets(nombreCompetencia, 50, stdin);
    nombreCompetencia[strcspn(nombreCompetencia, "\n")] = 0;  // Eliminar salto de línea //strspn copiar cadena de caracter y pegar en el archivo

    // Solicitar los nombres de los equipos
    for (int i = 0; i < 4; i++) {
        printf("Ingrese el nombre del equipo %d: ", i + 1);
        fflush(stdin);
        fgets(grupo.equipo[i].nombreEquipo, 50, stdin);
        grupo.equipo[i].nombreEquipo[strcspn(grupo.equipo[i].nombreEquipo, "\n")] = 0;  // Eliminar salto de línea
    }

    // Guardar la competencia y equipos en el archivo
    archivoEquipos = fopen("miarchivo.txt", "w");
    if (archivoEquipos == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(archivoEquipos, "Competencia: %s\n", nombreCompetencia); //guardar en el archivo fprintf
    for (int i = 0; i < 4; i++) {
        fprintf(archivoEquipos, "Equipo %d: %s\n", i + 1, grupo.equipo[i].nombreEquipo);
    }

    fclose(archivoEquipos); //funcion para cerrar el archivo
    printf("Competencia y equipos guardados correctamente\n");
}





// aqui comienza las funciones del menuFixture

// Función para ver fixture completo

void verFixtureCompleto() {
    archivoEquipos = fopen("miarchivo.txt", "r");
    if (archivoEquipos == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[100];
    printf("Fixture completo:\n");
    while (fgets(linea, sizeof(linea), archivoEquipos)) {
        printf("%s", linea);
    }

    fclose(archivoEquipos);
}

// Función para ver un grupo específico

  void verGrupo()
  {

    archivoEquipos = fopen("miarchivo.txt", "r");
    if (archivoEquipos == NULL) {
        printf("Error: El archivo no existe o no se puede abrir.\n");
        return;
    }

    int grupoNum;
    printf("Ingrese el numero del grupo (1-4): ");
    scanf("%d", &grupoNum);

    if (grupoNum < 1 || grupoNum > 4) {
        printf("Error: Numero de grupo invalido.\n");
        fclose(archivoEquipos);
        return;
    }

    char linea[100];
    int equipoInicio = (grupoNum - 1) * 4 + 1; // Cálculo del índice inicial del grupo
    int equipoFin = equipoInicio + 3;         // Cálculo del índice final del grupo
    int equipoActual = 1;

    printf("\nGrupo %d:\n", grupoNum);
    while (fgets(linea, sizeof(linea), archivoEquipos)) {
        if (equipoActual >= equipoInicio && equipoActual <= equipoFin) {
            printf("%s", linea);
        }
        if (strstr(linea, "Equipo")) {
            equipoActual++;
        }
    }

    fclose(archivoEquipos);


}



// Función para cargar estadísticas de un equipo
void cargarEstadisticas() {
    struct estadisticas stats;
    printf("Ingrese los partidos ganados: ");
    scanf("%d", &stats.partidoGanado);
    printf("Ingrese los partidos perdidos: ");
    scanf("%d", &stats.partidoPerdido);
    printf("Ingrese los partidos empatados: ");
    scanf("%d", &stats.partidoEmpatado);
    stats.partidoJugado = stats.partidoGanado + stats.partidoPerdido + stats.partidoEmpatado;
    printf("Ingrese los goles a favor: ");
    scanf("%d", &stats.golesFavor);
    printf("Ingrese los goles en contra: ");
    scanf("%d", &stats.golesContra);
    stats.diferenciaGol = stats.golesFavor - stats.golesContra;
    stats.puntos = (stats.partidoGanado * 3) + stats.partidoEmpatado;

    archivoEquipos = fopen("estadisticas.txt", "a");
    if (archivoEquipos == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivoEquipos, "PG:%d, PP:%d, PE:%d, PJ:%d, GF:%d, GC:%d, DG:%d, Pts:%d\n",
            stats.partidoGanado, stats.partidoPerdido, stats.partidoEmpatado, stats.partidoJugado,
            stats.golesFavor, stats.golesContra, stats.diferenciaGol, stats.puntos);

    fclose(archivoEquipos);
    printf("Estadisticas guardadas correctamente.\n");
}

// Función para modificar un dato
void modificarDato() {
   char nombreArchivo[] = "miarchivo.txt";
    char linea[100];
    char busqueda[50];
    char reemplazo[100];
    int encontrado = 0;

 printf("Ingrese el dato que desea modificar/n: ");
    fflush(stdin);
    fgets(busqueda, sizeof(busqueda), stdin);
    busqueda[strcspn(busqueda, "\n")] = 0; // Eliminar salto de línea

   // Pedir el texto de reemplazo
    printf("Ingrese el nuevo dato: ");
    fflush(stdin);
    fgets(reemplazo, sizeof(reemplazo), stdin);
    reemplazo[strcspn(reemplazo, "\n")] = 0; // Eliminar salto de línea






}




void menuFixture(){
    int opcion;
    do{
        printf("\n========== MENU FIXTURE ====================");
        printf("\n||        1.Ver Fixture Completo          ||");
        printf("\n||        2.Ver un Grupo                  ||");
        printf("\n||        3.Cargar Resultados             ||");
        printf("\n||        4.Modificar un dato             ||");
        printf("\n||        5.Volver al menu principal      ||");
        printf("\n============================================");
        printf("\nIngrese su opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);
        fflush(stdin);

        switch(opcion){
            case 1://funcion para ver el fixture completo

               printf("Elegiste ver el Fixture Completo.\n");
               verFixtureCompleto();
            break;

            case 2://funcion para ver un solo grupo


                verGrupo();

                break;

            case 3://funcion para cargar las estadisticas

                cargarEstadisticas();

                break;

            case 4://funcion para modificar un dato

            modificarDato();

                break;
            default:
                system("cls");
                printf("La opcion es incorrecta, volve a intentar de nuevo.\n");
                break;
}

} while(opcion!=5);


}

#endif // FUNCION_H_INCLUDED
