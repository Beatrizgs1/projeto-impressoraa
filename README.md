# projeto-impressoraa
Impressora Elgin i9



1.Função exibirMenu()

A função basicamente é responsável por printar na tela para o usuários todas as opções disponíveis e funcionalidades da impressora que ela pode executar como: 
abrir conexão, fecharconexão imprimir texto, imprimir QrCode, imprimir código de barras, imprimir XMLSAT, imprimir XMLCancelamentoSAT, abrir GavetaElginOpc, abrir GavetaOpc, emitir SinalSonoro.

-Ela não executa nenhuma ação, apenas apresenta o menu sempre que o programa precisa que o usuário escolha uma opção, por isso ela não tem nenhum retorno.



2. Função configurarConexao()
   
Ela vai permitir que o usuário defina os parâmetros necessários para se conectar à impressora Elgin i9.

Quando ela é chamada, o programa pergunta quatro informações:

- Tipo de conexão (por exemplo: 1 para USB, 2 para RS232, 3 para TCP/IP, 4	para Bluetooth e 5 para Impressoras acopladas (Android));
  
-Modelo da impressora (no nosso caso “i9” mas existem outros valores como i7, i8 entre outras);

-Tipo de conexão(USB, RS232, TCP, Bluetooth);

-Parametro(baudrate ou porta de comunicação TCP/IP.)

-O valor digitado para cada campo é armazenado nas variáveis globais (g_tipo, g_modelo, g_conexao, g_parametro) que já vieram configuradas no código dado e apenas chamamos elas, e que depois são usadas pela função que abre a conexão.

Utilizamos a função flush_entrada() que foi usada para limpar o buffer de entrada do teclado, pois quando usamos scanf para ler um número ou uma palavra, o usuário aperta ENTER, e esse ENTER fica “sobrando” no teclado, e ai acababa causando erro na proxima linha.




3.Função abrirConexao()

A função  é responsável por realmente iniciar a conexão com a impressora. Depois disso, ela verifica se já existe uma conexão aberta.

Se não existir, ela chama a função da DLL:

AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);

Se o retorno for 0, significa que a conexão foi aberta com sucesso.
 > Mostramos a mensagem “Conexao aberta com sucesso!”
Atualizamos a variável g_conectada = 1

Se o retorno for diferente de 0, significa erro ao abrir conexão.
Então exibimos na tela o código de erro, printando a variável ret de retorno.




4.Função fecharConexao()
   
Essa função serve para encerrar a conexão com a impressora antes de sair do programa.

Primeiro, ela verifica se existe uma conexão ativa usando a variável g_conectada, se a impressora estiver conectada, chamamos a função FechaConexaoImpressora() da DLL.

Quando a conexão é fechada com sucesso, atualizamos g_conectada para 0, indicando que agora não existe mais nenhuma conexão ativa, esta função é basicamente o contrário da função abrir conexão, além disso, antes de tentar fechar a conexão, o programa verifica se realmente existe uma conexão ativa, para isso, ele usa if (!g_conectada), que significa “se não estiver conectada”, caso não exista conexão, a função simplesmente retorna, evitando chamadas desnecessários, até porque não faz sentido nenhum fechar uma conexão que nem existe.




5.Função imprimirTexto()
   
Essa função é responsável por imprimir um texto simples na impressora. Primeiro, ela pede para o usuário digitar um texto, e essa frase é lida usando fgets().
Em seguida, removemos o “ENTER” que fica no final da string para evitar que seja impresso.

Após isso, chamamos ImpressaoTexto() da DLL da Elgin usando os parâmetros definidos pelo professor (1, 4, 0), que controlam a posição (centro), o tamanho da fonte  e o estilo do texto(normal).

Depois da impressão, avançamos o papel com AvancaPapel(2) que avança duas linhas e cortamos com Corte(2) para finalizar o processo e deixar o texto organizado.





6.Função imprimirQrCode()
Esta função é responsável por gerar e imprimir um QR Code usando a impressora i9.

Primeiro, o programa pede para o usuário digitar o conteúdo que será transformado no QR Code.

Depois disso, removemos o ENTER (\n) do final da string usando o fgets para evitar que ele faça parte do QR Code.

Depois, chamamos a função ImpressaoQRCode() da DLL da Elgin, usando exatamente os parâmetros definidos pelo professor:
ImpressaoQRCode(conteudo, 6, 4);

conteudo - texto digitado pelo usuário;
  
6 - tamanho do QR Code (maior);
  
4 - nível de correção (30%);




7. FuncãoimprimirCodigoBarras()
     
Esta função é responsável por imprimir um código de barras padrão na impressora. Diferente das outras funções, ela não pede para o usuário digitar nada pois  o código de barras já está definido diretamente no código, exatamente como o professor pediu.

Dentro da função, chamamos:

ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);

 8 - tipo do modelo do  código de barras (CODE 128);
 "{A012345678912" → conteúdo do código de barras; 
 
 100 - altura do código de barras;
 
 2 - largura da barra;
 
 3- posição de impressão do código de barra;

Depois de imprimir o código de barras, também chamamos como na outra funçaõ:

AvancaPapel(2);

Corte(2);




8. Função ImprimirXMLSAT()
   
Esta função imprimirXMLSAT() é responsável por enviar um arquivo XML de venda do SAT para a impressora. Esse tipo de impressão é usado quando queremos imprimir um cupom fiscal já gerado pelo SAT.
Dentro da função, definimos o caminho do arquivo XML:
char caminho[] = "path=XMLSAT.xml";

A DLL da Elgin exige que o caminho comece com “path=”, por isso seguimos exatamente a documentação.
Depois disso, chamamos:

int ret = ImprimeXMLSAT(caminho, 0);

caminho - é o arquivo XML que será impresso;

0 - significa que será feita a impressão completa (modo padrão);
     
O retorno da função é guardado em ret, como como nas outras funções da DLL:
0 significa que deu tudo certo e qualquer outro número indica erro
Depois da impressão do cupom do SAT, usamos novamente:
     
 AvancaPapel(4);
 
 Corte(2);




9.Função imprimirXMLCancelamentoSAT()
     
 Esta é responsável por imprimir o XML de cancelamento do SAT. Esse XML é o documento gerado quando uma venda SAT é cancelada, e ele possui uma assinatura digital obrigatória para validar o cancelamento.

Dentro da função, definimos o caminho do XML:

char caminho[] = "path=CANC_SAT.xml";

Depois disso, definimos a assinatura digital do cancelamento, que já foi fornecida pelo professor no documento:
  const char *assinatura = "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==" ; 

 Essa assinatura é necessária porque o XML de cancelamento precisa dessa validação para ser impresso corretamente.

 Depois chamamos:
 
 int ret = ImprimeXMLCancelamentoSAT(caminho, assinatura, 0);
 
 caminho - XML do cancelamento
     
0 - indica que estamos usando o modo padrão de impressão (nenhuma opção extra)

Assim como nas outras funções da DLL, verificamos o retorno:
0 -  impressão bem-sucedida

valor diferente de 0 - erro
     
Como nas outras funções, avançamos o papel e cortamos:
AvancaPapel(4);

Corte(2);




10.Função abrirGavetaElginOpc()
    
Essa função usa parâmetros padrões para abertura de gavetas Elgin.

Chamamos a  função da DLL:
AbreGavetaElgin(1, 50, 50);

1 - indicação do pino a ser acionado;

50 - tempo de inicialização do pulso;

50 -  tempo de desativação do pulso;

Esses valores foram definidos pelo professor, então usamos exatamente como ele pediu. Essa função não imprime nada e não corta papel , ela apenas aciona o mecanismo da gaveta.




11.Função abrirGavetaOpc()
    
Esta função serve apenas para abrir a gaveta.

Chamamos a função DLL:

AbreGaveta(1, 5, 10);
     
 1 - qual saída da impressora vai mandar o sinal
 
 5 - quanto tempo o sinal vai durar
 
 10 - pequena pausa depois do sinal




12.Função emitirSinalSonoro()
    
Emite sinal sonoro na impressora;

Os parametros usados foram:

SinalSonoro(4, 50, 5);
     
4 - quantidade de sinais emitidos;

50 - duração do sinal sonoro;

5  -intervalo entre os sinais sonoros;


