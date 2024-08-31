#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//registros dos pacientes
typedef struct pac{
    char nome[30];
    int cpf;
    char nivel[15];
    struct pac *prox;
}Paciente;

//filas dos pacientes
typedef struct {
    Paciente *emergencia;
    Paciente *urgencia;
    Paciente *eletivo;
}Filas;

//inicializando  as filas para chamar apenas por função
Filas *inicializarFilas(){
    Filas *filas = (Filas*) malloc(sizeof(Filas));
    filas->emergencia = NULL;
    filas->urgencia = NULL;
    filas->eletivo = NULL;
    
    return filas;
}

void lerDados(Paciente *paciente){
    printf("\n\tNome: ");
    scanf("%30[^\n]s", &paciente->nome);
    printf("\tCPF: ");
    scanf("%d", &paciente->cpf);
}


void imprimirPacientes(Paciente *paciente){
    printf("\n\tNome: %s", paciente->nome);
    printf("\n\tCPF: %d", paciente->cpf);
    printf("\n\tNível: %s\n", paciente->nivel);
}

void imprimirFilas(Paciente *fila, char *nomeFila){
    printf("\n\t%s", nomeFila);
    printf("\n\t------------------------\n");

    //percorre as listas imprindo os pacientes
    while (fila != NULL){
        imprimirPacientes(fila);
        fila = fila->prox;
    }
    printf("\n\t------------------------\n");
}

//criando o registro da minha struct
Paciente *registroPaciente(){
    Paciente *novo = (Paciente*) malloc(sizeof(Paciente));

    lerDados(novo);

    novo->prox = NULL; // inicialmente ele sempre apontará para NULL (evitar erros)

    return novo;
}

//recebe a fila e um registro de paciente
void inserirNaFila(Paciente **fila, Paciente *paciente){
    //se fila vazia
    if(*fila == NULL){
        *fila = paciente;
    } else {
        Paciente *aux = *fila;
        //percorrendo a lista
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = paciente; // inserindo o paciente no final da fila
    }
}

void menuCadastro(Filas *filas){
    Paciente *novo;
    int opc = 0;

    do{
        system("cls");
        printf("\n\tINFORME O NÍVEL:\n");
        printf("\n\t1 - Emergência");
        printf("\n\t2 - Urgência");
        printf("\n\t3 - Eletivo");
        printf("\n\t0 - Sair");
        
        printf("\n\n\tDigite a opção: ");
        scanf("%d", &opc);
        getchar();
        system("cls");
        switch (opc){
        case 1:
            novo = registroPaciente();
            //copiando o nível para a variavel Nivel de cada paciente
            strcpy(novo->nivel, "EMERGÊNCIA");
            inserirNaFila(&(filas)->emergencia, novo);

            printf("\n\tCadastrado com sucesso!\n");
            system("pause");
            return;
        case 2:
            novo = registroPaciente();
            //copiando o nível para a variavel Nivel de cada paciente
            strcpy(novo->nivel, "URGÊNCIA");
            inserirNaFila(&(filas)->urgencia, novo);

            printf("\n\tCadastrado com sucesso\n");
            system("pause");
            return;
        case 3:
            novo = registroPaciente();
            //copiando o nível para a variavel Nivel de cada paciente
            strcpy(novo->nivel,"ELETIVO");
            inserirNaFila(&(filas)->eletivo, novo);

            printf("\n\tCadastrado com sucesso\n");
            system("pause");
            return;
        case 0:
            printf("\n\n\tSaindo...");
            system("pause");
            break;
        
        default:
            printf("\n\tOpção inválida!\n");
            break;
        }
    } while (opc != 0);
    
}

Paciente *removerDaFila (Paciente **fila){
    Paciente *remover = *fila;

    *fila = remover->prox;
    remover->prox = NULL;

    return remover;
}

Paciente *next (Filas *filas){

    //vai incrementando sempre que a função é executada
    static int cont = 0;

    //1 - prioridade
    if (cont == 0 && filas->emergencia != NULL){ //se não tiver ninguem na fila de emergencia
        cont++;
        return removerDaFila(&(filas)->emergencia);
    }
    //2 - prioridade
    if(cont == 1 && filas->urgencia != NULL){ //tem que ser difente de 3 e tem que ter alguém na fila
        cont++;
        return removerDaFila(&(filas)->urgencia);
    }
    //3 - prioridade
    if(cont == 2 && filas->eletivo != NULL){
        cont = 0; //contador volta a ser 0
        return removerDaFila(&(filas)->eletivo);
    }
}

int buscar_cpf(Filas *filas, int *cpf){

    Paciente *emergencia = filas->emergencia;
    Paciente *urgencia = filas->urgencia;
    Paciente *eletivo = filas->eletivo;

    int contEmergencia = -1;
    int contUrgencia = 0;
    int contEletivo = 0;

    //1 - prioridade - enquanto tiver pacientes na emergencia
    while(emergencia != NULL){

        contEmergencia++;
        
        if(emergencia->cpf == *cpf){
            return contEmergencia;
        }

        emergencia = emergencia->prox;
    }
    //2 - prioridade - enquanto tiver pacientes nas duas filas
    while(urgencia != NULL || eletivo != NULL){

        while(contUrgencia != 3 && urgencia != NULL){

            contEmergencia++;
            contUrgencia++;
            contEletivo = 0;

            if(urgencia->cpf == *cpf){
                return contEmergencia;
            }

            urgencia = urgencia->prox;

            if(eletivo == NULL){
                contUrgencia = 0;
            }
        }
        //3 - prioridade
        while(contEletivo != 1 && eletivo != NULL){

            contEmergencia++;
            contEletivo++;
            contUrgencia = 0; //zerar para voltar a se repetir o mesmo esquema de prioridade

            if(eletivo->cpf == *cpf){
                return contEmergencia;
            }

            eletivo = eletivo->prox;

            if(urgencia == NULL){
                contEletivo = 0;
            }
        }
    }
    return -1;
}

void pacientesAtendidos(Paciente *paciente, int *qtdEmerg, int *qtdUrg, int *qtdElet){
    //se forem iguais
    if(strcmp(paciente->nivel, "EMERGÊNCIA") == 0){
        *qtdEmerg += 1;
        return;
    }

    if(strcmp(paciente->nivel, "URGÊNCIA") == 0){
        *qtdEmerg += 1;
        return;
    }

    if(strcmp(paciente->nivel, "ELETIVO") == 0){
        *qtdEmerg += 1;
        return;
    }
}

int main(void){
    Filas *fila = inicializarFilas();
    Paciente *pacienteAtendido;
    int opc = 0, cpf = 0, qtdEmerg = 0, qtdUrg = 0, qtdElet = 0, qtdPacientes = 0;

    do{
        system("cls");
        printf("\t\tMENU\n");
        printf("\t1 - Cadastrar paciente\n\t2 - Visualizar pacientes na fila\n\t3 - Atender primeiro paciente da fila\n\t4 - Quantidade de pacientes na frente\n\t5 - Quantidade de pacientes atendidos\n\t0 - Sair\n\n");
        printf("\tDigite a opção: ");
        scanf("%d", &opc);
        system("cls");
        switch (opc){
        case 1:
            menuCadastro(fila);
            break;
        case 2:
            imprimirFilas(fila->emergencia, "EMERGÊNCIA");
            imprimirFilas(fila->urgencia, "URGÊNCIA");
            imprimirFilas(fila->eletivo, "ELETIVO");
            printf("\n");
            system("pause");
            break;
        case 3:
            if (fila->emergencia != NULL || fila->urgencia != NULL || fila->eletivo != NULL){
                pacienteAtendido = next(fila);

                printf("\n\tPaciente atendido: %s", pacienteAtendido->nome);
                printf("\n\tNível: %s\n\n", pacienteAtendido->nivel);

                pacientesAtendidos(pacienteAtendido, &qtdEmerg, &qtdUrg, &qtdElet);

                free(pacienteAtendido);

                system("pause");
            } else {
                printf("\n\tNenhum paciente na fila\n");
            }
            break;
        case 4:
            printf("\n\tInforme o CPF: ");
            scanf("%d", &cpf);

            qtdPacientes = buscar_cpf(fila, &cpf);

            if(qtdPacientes != -1){
                printf("\n\tQuantidade de pacientes na frente: %d\n", qtdPacientes);

                system("pause");
            }
            break;
        case 5:
            printf("\n\tPACIENTES ATENDIDOS:\n");
            printf("\n\tEmergência: %d\n", qtdEmerg);
            printf("\n\tUrgência: %d\n", qtdUrg);
            printf("\n\tEletivo: %d\n\n", qtdElet);

            system("pause");
            break;
        case 0:
            printf("\n\n\tFinalizando...");
            exit(0);
            break;
        default:
            printf("\n\n\tOpção inválida!\n");
            exit(0);
            break;
        }
    } while (opc != 0);

    return 0;
}