#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

// Definição dos pinos
#define LED_AZUL        11
#define LED_VERMELHO    12
#define LED_VERDE       13
#define BOTAO           5

// Variáveis globais de controle
volatile int contador = 0;    // Controla a ordem de desligamento dos LEDs
volatile bool em_processo = false;  // Impede novos acionamentos enquanto o temporizador está ativo

//Função de callback do alarme.
//A cada 3 segundos, apaga um LED na sequência: azul -> vermelho -> verde.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    if (contador == 0) {
        gpio_put(LED_AZUL, false);
        contador++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Próximo alarme
    } else if (contador == 1) {
        gpio_put(LED_VERMELHO, false);
        contador++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else if (contador == 2) {
        gpio_put(LED_VERDE, false);
        em_processo = false; // Libera para novo acionamento
    }
    return 0;
}

int main(void) {
    // Inicializa a biblioteca padrão e configura os GPIOs
    stdio_init_all();

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, false);

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, false);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, false);

    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    while (true) {
        if (!em_processo && gpio_get(BOTAO) == 0) {
            sleep_ms(50); // Debounce
            if (gpio_get(BOTAO) == 0) {
                gpio_put(LED_AZUL, true);
                gpio_put(LED_VERMELHO, true);
                gpio_put(LED_VERDE, true);

                contador = 0;
                em_processo = true;

                add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Inicia sequência

                while (gpio_get(BOTAO) == 0) { sleep_ms(10); } // Aguarda soltar botão
            }
        }
        sleep_ms(10);
    }
    return 0;
}
