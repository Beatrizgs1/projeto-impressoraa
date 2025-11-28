# 🖨️ Integração Java com Impressora Elgin i9
### *PROJETO IMPRESSORA-ELGIN*
---

## 📘 Sobre o Projeto

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


---

## 🧰 Tecnologias Utilizadas

- Linguagem C

- GCC / MinGW (Windows)

- DLL oficial E1_Impressora01.dll (Elgin)

- Dev C++ 

- Driver da impressora Elgin i9
---


## ⚙️ Instalação e Execução

### 🔽 1. Baixar o Projeto do GitHub
1. Acesse o **repositorio**.
2. Clique no botão **Code**, botão verde.
3. Selecione **Baixar ZIP**.
4. Aguarde o download.

### 📦 2. Extrair o Arquivo ZIP
1. Vá até o local onde o arquivo foi salvo.
2. Clique com o botão direito → **Extrair tudo**.
3. Será criada uma nova pasta com os arquivos extraido de forma certa.

### 🧭 3. Importar no Dev C++
1. Abra o **Dev C++**.
2. Clique em **File**.
3. Depois **Open**.
4. Selecione o **arquivo extraído**.
5. Depois abra o arquivo e espere o carregamento do código.


---

## 🧪 Testes

📄 1. Teste de Impressão de Texto

**ImpressaoTexto(texto, 1, 4, 0)**;



🔳 2. Teste de QR Code

**ImpressaoQRCode(conteudo, 6, 4)**;


Tamanho 6

Correção nível 4 (30%)

🏷️ 3. Teste de Código de Barras

**ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3)**;

Padrão Code128

Altura 100

Largura 2

HRI posição 3

🧾 4. Teste XML SAT

**ImprimeXMLSAT("path=XMLSAT.xml", 0)**;

❌ 5. Teste XML Cancelamento SAT

**ImprimeXMLCancelamentoSAT("path=CANC_SAT.xml", assinatura, 0)**;

Envio do XML + assinatura digital completa fornecida pelo professor

🔔 6. Teste de Sinal Sonoro

**SinalSonoro(4, 50, 5)**;

4 sinais

50ms por sinal

Intervalo de 5ms

📬 7. Teste de Abertura de Gaveta

**AbreGavetaElgin(1, 50, 50)**;

---

## 📚 Documentação Adicional

-Plataforma de Comunicação Elgin

---

## 👥 Autores  
*(em ordem alfabética)*

- Ana Luisa Costa
- Beatriz Gonçalves
- Julia Ferraz
- Thiago Lima

