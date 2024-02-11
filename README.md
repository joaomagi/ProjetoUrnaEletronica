"# ProjetoUrnaEletronica"

Este código é um programa para uma urna eletrônica simulada usando um Arduino Mega. Ele utiliza várias bibliotecas, incluindo SPI, SD, Keypad e LiquidCrystal, para controlar diferentes componentes, como teclado de membrana, display LCD, botões, buzzer e um módulo de cartão microSD.

Aqui está uma descrição do código:

### Bibliotecas utilizadas:
- `SPI.h`: Biblioteca para a comunicação SPI (Serial Peripheral Interface).
- `SD.h`: Biblioteca para interação com cartões microSD.
- `Keypad.h`: Biblioteca para leitura de teclado de membrana.
- `LiquidCrystal.h`: Biblioteca para controlar displays LCD.

### Componentes conectados ao Arduino Mega:
- **Teclado de membrana 3x4**: Conectado aos pinos definidos em `rowPins` e `colPins`.
- **Display LCD 16x2**: Conectado aos pinos 12, 11, 5, 4, 3, 2 do Arduino.
- **Botões de confirmação, voto nulo e cancelamento**: Conectados aos pinos definidos como `confirmButtonPin`, `nullButtonPin` e `cancelButtonPin`, respectivamente.
- **Buzzer ativo 5V**: Conectado ao pino 10 do Arduino.
- **Módulo de micro cartão SD**: Conectado ao pino 53 do Arduino.

### Variáveis e funções importantes:
- `sequence`: Variável que armazena a sequência de números digitados pelo usuário.
- `Musica()`: Função que reproduz uma melodia de confirmação.
- `Musica2()`: Função que reproduz uma melodia de cancelamento.
- `TelaIni()`: Função para exibir a tela inicial da urna eletrônica no display LCD.
- `Mensagem(msg)`: Função para exibir uma mensagem personalizada no display LCD.

O código principal está dentro do loop `void loop()`, onde ele aguarda a entrada do teclado e ações dos botões. Dependendo dos inputs, ele executa a lógica para confirmar o voto, votar nulo ou cancelar o voto, exibindo mensagens no LCD e armazenando os votos no cartão microSD.

Esse código simula o processo de uma urna eletrônica básica e é uma implementação didática. Note que, em ambientes reais, requisitos de segurança mais rigorosos seriam necessários.

