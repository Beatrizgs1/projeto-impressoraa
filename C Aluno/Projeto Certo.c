#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ======================= Config DLL ======================= */
static HMODULE g_hDll = NULL;

#ifndef CALLCONV
#  define CALLCONV WINAPI
#endif

/* ======================= Assinaturas da DLL ======================= */
typedef int (CALLCONV *AbreConexaoImpressora_t)(int, const char *, const char *, int);
typedef int (CALLCONV *FechaConexaoImpressora_t)(void);
typedef int (CALLCONV *ImpressaoTexto_t)(const char *, int, int, int);
typedef int (CALLCONV *Corte_t)(int);
typedef int (CALLCONV *ImpressaoQRCode_t)(const char *, int, int);
typedef int (CALLCONV *ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
typedef int (CALLCONV *AvancaPapel_t)(int);
typedef int (CALLCONV *AbreGavetaElgin_t)(int, int, int);
typedef int (CALLCONV *AbreGaveta_t)(int, int, int);
typedef int (CALLCONV *SinalSonoro_t)(int, int, int);
typedef int (CALLCONV *ImprimeXMLSAT_t)(const char *, int);
typedef int (CALLCONV *ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
typedef int (CALLCONV *InicializaImpressora_t)(void);

/* ======================= Ponteiros ======================= */
static AbreConexaoImpressora_t AbreConexaoImpressora = NULL;
static FechaConexaoImpressora_t FechaConexaoImpressora = NULL;
static ImpressaoTexto_t ImpressaoTexto = NULL;
static Corte_t Corte = NULL;
static ImpressaoQRCode_t ImpressaoQRCode = NULL;
static ImpressaoCodigoBarras_t ImpressaoCodigoBarras = NULL;
static AvancaPapel_t AvancaPapel = NULL;
static AbreGavetaElgin_t AbreGavetaElgin = NULL;
static AbreGaveta_t AbreGaveta = NULL;
static SinalSonoro_t SinalSonoro = NULL;
static ImprimeXMLSAT_t ImprimeXMLSAT = NULL;
static ImprimeXMLCancelamentoSAT_t ImprimeXMLCancelamentoSAT = NULL;
static InicializaImpressora_t InicializaImpressora = NULL;

/* ======================= Configuração ======================= */
static int   g_tipo      = 1;
static char  g_modelo[64] = "i9";
static char  g_conexao[128] = "USB";
static int   g_parametro = 0;
static int   g_conectada = 0;

/* ======================= Utilidades ======================= */
#define LOAD_FN(h, name)                                                         \
    do {                                                                         \
        name = (name##_t)GetProcAddress((HMODULE)(h), #name);                    \
        if (!(name)) {                                                           \
            fprintf(stderr, "Falha ao resolver símbolo %s (erro=%lu)\n",         \
                    #name, GetLastError());                                      \
            return 0;                                                            \
        }                                                                        \
    } while (0)

static void flush_entrada(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* ======================= Funções para manipular a DLL ======================= */
static int carregarFuncoes(void)
{
    g_hDll = LoadLibraryA("E1_Impressora01.dll");
    if (!g_hDll) {
        fprintf(stderr, "Erro ao carregar E1_Impressora01.dll (erro=%lu)\n", GetLastError());
        return 0;
    }

    LOAD_FN(g_hDll, AbreConexaoImpressora);
    LOAD_FN(g_hDll, FechaConexaoImpressora);
    LOAD_FN(g_hDll, ImpressaoTexto);
    LOAD_FN(g_hDll, Corte);
    LOAD_FN(g_hDll, ImpressaoQRCode);
    LOAD_FN(g_hDll, ImpressaoCodigoBarras);
    LOAD_FN(g_hDll, AvancaPapel);
    LOAD_FN(g_hDll, AbreGavetaElgin);
    LOAD_FN(g_hDll, AbreGaveta);
    LOAD_FN(g_hDll, SinalSonoro);
    LOAD_FN(g_hDll, ImprimeXMLSAT);
    LOAD_FN(g_hDll, ImprimeXMLCancelamentoSAT);
    LOAD_FN(g_hDll, InicializaImpressora);

    return 1;
}

/* ======================= Funções a serem implementadas pelos alunos ======================= */

static void exibirMenu(void)
{
    printf("\n=========== MENU ==============\n");
    printf("1 - Configurar Conexao\n");
    printf("2 - Abrir Conexao\n");
    printf("3 - Impressao Texto\n");
    printf("4 - Impressao QRCode\n");
    printf("5 - Impressao Cod Barras\n");
    printf("6 - Impressao XML SAT\n");
    printf("7 - Impressao XML Canc SAT\n");
    printf("8 - Abrir Gaveta Elgin\n");
    printf("9 - Abrir Gaveta\n");
    printf("10 -Sinal Sonoro\n");
    printf("0 - Fechar Conexao e Sair\n");
    printf("\n");
}


static void configurarConexao(void)
{
    printf("Digite o tipo:\n"); 
	scanf("%d", &g_tipo); 
	flush_entrada();
	
    printf("Digite o modelo:\n"); 
	scanf("%s", &g_modelo); 
	flush_entrada();
	
    printf("Digite a conexao:\n"); 
	scanf("%s", &g_conexao); 
	flush_entrada();
	
    printf("Digite o parametro:\n"); 
	scanf("%d", &g_parametro); 
	flush_entrada();
	
	printf("\n");
    printf("Configuracao feita com sucesso!!!");
    printf("\n");
}

static void abrirConexao(void)
{
    if (g_conectada) {
        printf("\n");
        printf(" Ja tem uma Impressora Conectada!\n");
        return;
    }

    int ret = AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);

    if (ret == 0) {
        printf("\n");
        printf("Conexao aberta com sucesso!\n");
        g_conectada = 1;
    } else {
        printf("\n");
        printf("Erro ao abrir conexao: %d\n", ret);
    }
}

static void fecharConexao(void)
{
    if (!g_conectada){
        return;
    }

    int ret = FechaConexaoImpressora();

    if (ret == 0) {
        printf("Conexao fechada!\n");
        g_conectada = 0;
    } else {
        printf("Erro em fechar a conexao: %d\n", ret);
    }
}

static void imprimirTexto(void)
{
    char texto[100];
    printf("Digite um texto para imprimir: ");
    fgets(texto, sizeof(texto), stdin);

    texto[strcspn(texto, "\n")] = 0;

    ImpressaoTexto(texto, 1, 4, 0);
    AvancaPapel(2);
    Corte(2);
}

static void imprimirQRCode(void)
{
    char conteudo[100];
    printf("Digite o texto do QR Code: ");
    fgets(conteudo, sizeof(conteudo), stdin);
    conteudo[strcspn(conteudo, "\n")] = 0;

    ImpressaoQRCode(conteudo, 6, 4);
    AvancaPapel(2);
    Corte(2);
}

static void imprimirCodigoBarras(void)
{
    ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);
    AvancaPapel(2);
    Corte(2);
}

static void imprimirXMLSAT(void)
{
    char caminho[] = "path=XMLSAT.xml";

    int ret = ImprimeXMLSAT(caminho, 0);

    printf("Retorno: %d\n", ret);

    AvancaPapel(4);
    Corte(2);
}

static void imprimirXMLCancelamentoSAT(void)
{
    char caminho[] = "path=CANC_SAT.xml";
    

    const char *assinatura =
        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";

    int ret = ImprimeXMLCancelamentoSAT(caminho, assinatura, 0);

    printf("Retorno: %d\n", ret);

    AvancaPapel(4);
    Corte(2);
}

static void abrirGavetaElginOpc(void)
{
    AbreGavetaElgin(1, 50, 50);
}

static void abrirGavetaOpc(void)
{
    AbreGaveta(1, 5, 10);
}

static void emitirSinalSonoro(void)
{
    SinalSonoro(4, 50, 5);
}



/* ======================= Função principal ======================= */
int main(void)
{
    if (!carregarFuncoes())
        return 1;

    int opcao = 0;

    while (1) {
        exibirMenu();
        printf("Escolha a opcao: ");
        scanf("%d", &opcao);
        flush_entrada();

        switch (opcao) {
            case 1: 
			    configurarConexao(); 
				break;
				
            case 2: 
			    abrirConexao(); 
				break;
				
            case 3: 
			    imprimirTexto(); 
				break;
				
            case 4: 
			    imprimirQRCode(); 
				break;
				
            case 5: 
			    imprimirCodigoBarras(); 
				break;
				
            case 6: 
			    imprimirXMLSAT(); 
				break;
				
            case 7: 
			    imprimirXMLCancelamentoSAT(); 
				break;
				
            case 8: 
			    abrirGavetaElginOpc(); 
				break;
				
            case 9: 
			    abrirGavetaOpc(); 
			    break;
			
            case 10: 
			    emitirSinalSonoro(); 
				break;

            case 0:
                fecharConexao();
                printf("Conexao fechada\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}

