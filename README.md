🖨️ PROJETO IMPRESSORA-ELGIN – Integração em C com a DLL Oficial

📘 Descrição do Projeto

Este projeto demonstra como integrar aplicações em linguagem C com a impressora Elgin i9, utilizando a DLL oficial de comunicação fornecida pela própria Elgin.
O objetivo é testar e executar as principais funcionalidades da impressora, como:

✔️ Abertura e fechamento de conexão

✔️ Impressão de texto

✔️ Impressão de QR Code

✔️ Impressão de código de barras

✔️ Impressão de XML SAT e XML de cancelamento

✔️ Abertura de gaveta

✔️ Emissão de sinal sonoro

O trabalho foi desenvolvido para fins educativos, como parte da disciplina de Programação.

🧰 Pré-Requisitos

Para compilar e executar o projeto, você precisará de:

🔹 Compilador C (Dev-C++, Visual Studio, etc.)

🔹 DLL oficial da Elgin

IntegracaoImpressora.dll (ou nome equivalente fornecido pela Elgin)

Deve estar no mesmo diretório do executável

🔹 Sistema Operacional Windows (necessário para uso da DLL)

🗂️ Funções do Sistema

A seguir você encontrará um resumo claro de cada função implementada no programa em C.

📌 1. exibirMenu()

Exibe todas as opções disponíveis para o usuário, como:

Abrir conexao

Fechar conexao

Imprimir texto

Imprimir QR Code

Imprimir código de barras

Imprimir XML SAT

Imprimir XML Cancelamento

Abrir gaveta (Elgin)

Abrir gaveta 

Emitir sinal sonoro

📌 Apenas exibe o menu. Não executa nenhuma ação.

📌 2. configurarConexao()

Permite ao usuário definir os parâmetros necessários para se conectar à impressora:

Tipo de conexão (USB, Serial, TCP/IP etc.)

Modelo (ex.: i9)

Tipo de comunicação

Parâmetro específico (porta, baudrate ou IP)

As respostas são armazenadas em variáveis globais usadas posteriormente por abrirConexao().

Usa também flush_entrada() para evitar problemas com buffer do teclado.

📌 3. abrirConexao()

Abre de fato a conexão com a impressora usando a função da DLL:

AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);


retorno 0 → conexão aberta

outros valores → erro

Atualiza a variável global g_conectada.

📌 4. fecharConexao()

Encerra a conexão com a impressora, chamando:

FechaConexaoImpressora();


Só executa se houver uma conexão ativa.

📌 5. imprimirTexto()

Permite ao usuário digitar um texto e imprime usando:

ImpressaoTexto(texto, 1, 4, 0);


Onde:

Alinhamento: centro

Tamanho da fonte: padrão

Estilo: normal

Finaliza com:

AvancaPapel(2);
Corte(2);

📌 6. imprimirQrCode()

Lê um texto digitado pelo usuário e imprime um QR Code via:

ImpressaoQRCode(conteudo, 6, 4);


6 = tamanho

4 = nível de correção (30%)

📌 7. imprimirCodigoBarras()

Imprime um código de barras pré-definido:

ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);


8 = CODE128

Altura = 100

Largura = 2

Posição = 3

Finaliza com avanço e corte.

📌 8. imprimirXMLSAT()

Imprime um XML de venda do SAT:

char caminho[] = "path=XMLSAT.xml";
ImprimeXMLSAT(caminho, 0);

Finaliza com:

AvancaPapel(4);
Corte(2);

📌 9. imprimirXMLCancelamentoSAT()

Imprime o XML de cancelamento do SAT com assinatura digital:

ImprimeXMLCancelamentoSAT(caminho, assinatura, 0);


Também avança e corta o papel.

📌 10. abrirGavetaElginOpc()

Aciona gavetas compatíveis com Elgin usando:

AbreGavetaElgin(1, 50, 50);

📌 11. abrirGavetaOpc()

Abertura de gaveta:

AbreGaveta(1, 5, 10);

📌 12. emitirSinalSonoro()

Emite um sinal sonoro na impressora:

SinalSonoro(4, 50, 5);


👥 Autores

Ana Luisa Costa da Silva

Beatriz Gonçalves de Souza

Julia Souza Costa

Thiago Pinheiro Lima
