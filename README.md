Embarcatech

Tarefa da aula síncrona do dia 29/01/2025 - **ATIVIDADE 1**

Aluno: **Fábio Rocha Gomes Jardim**

Matrícula: **TIC370100723**

# Sequência de Desligamento de LEDs com Raspberry Pi Pico W

Este projeto implementa uma funcionalidade em que, após o acionamento de um botão, três LEDs (azul, vermelho e verde) são ligados simultaneamente e, em seguida, desligados em sequência a cada 3 segundos. A sequência inicia com o LED azul, passa para o vermelho e finaliza com o verde. Enquanto a sequência de desligamento ocorre, o sistema impede novos acionamentos, garantindo que o processo seja executado de forma ordenada. O código utiliza a biblioteca padrão do Raspberry Pi Pico SDK para controle dos GPIOs e o agendamento de alarmes.

## Simulação no Wokwi

O projeto **integra o Wokwi ao VS Code** para fazer a simulação do circuito, e todos os arquivos necessários estão incluídos.

Caso queira ver a simulação através do Wokwi web: [simulação no Wokwi web](https://wokwi.com/projects/421922658945214465)

![Simulação no VS Code](https://github.com/fabiorgj/Tarefa_aula_sinc_29_01_Atividade_2/blob/main/SIMULA%C3%87%C3%83O%20WOKWI.gif)   

O código rodando na BitdogLab:    

![codigo na bitdoglab](https://github.com/fabiorgj/Tarefa_aula_sinc_29_01_Atividade_2/blob/main/bitdoglab-atv2.gif)   

## Descrição

O código realiza o seguinte:
- **Botão:** Ao ser pressionado, aciona o sistema.
- **LEDs:** São ligados simultaneamente (LED azul, LED vermelho e LED verde).
- **Sequência de Desligamento:** 
  - Após 3 segundos, o LED azul é desligado.
  - Após mais 3 segundos, o LED vermelho é desligado.
  - Após mais 3 segundos, o LED verde é desligado, liberando o sistema para um novo acionamento.

Essa lógica é gerenciada através de uma função de callback do alarme, que realiza o desligamento dos LEDs em sequência.

## Explicação do Código

### Definições e Variáveis
- **Pinos dos LEDs e Botão:**
  - `LED_AZUL` (GPIO 11)
  - `LED_VERMELHO` (GPIO 12)
  - `LED_VERDE` (GPIO 13)
  - `BOTAO` (GPIO 5)
- **Variáveis Globais:**
  - `contador`: Controla a ordem de desligamento dos LEDs (0 para azul, 1 para vermelho e 2 para verde).
  - `em_processo`: Flag que impede novos acionamentos enquanto o temporizador está ativo.

### Função `turn_off_callback`
Esta função é chamada a cada 3 segundos e realiza:
1. **Quando `contador == 0`:** Desliga o LED azul e agenda o próximo alarme.
2. **Quando `contador == 1`:** Desliga o LED vermelho e agenda o próximo alarme.
3. **Quando `contador == 2`:** Desliga o LED verde e libera o sistema para novos acionamentos.

### Função `main`
1. Inicializa a biblioteca padrão e configura os pinos dos LEDs e do botão.
2. Configura o botão com resistor de pull-up.
3. No loop principal, aguarda o acionamento do botão. Quando pressionado, liga todos os LEDs, inicia a contagem e agenda o primeiro alarme para iniciar a sequência de desligamento.
4. Aguarda o botão ser solto para evitar acionamentos repetidos.

## Componentes Necessários
- Raspberry Pi Pico W
- 1 LED Azul (GPIO 11)
- 1 LED Vermelho (GPIO 12)
- 1 LED Verde (GPIO 13)
- 1 Botão (GPIO 5)
- 3 Resistores de 330Ω (um para cada LED)

![Diagrama do Circuito no Wokwi](https://github.com/fabiorgj/Tarefa_aula_sinc_29_01_Atividade_2/blob/main/diagrama%20wokwi.png)

