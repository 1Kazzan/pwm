<h1 align="center">Embarcatech | Atividade PWM </h1>

Nome: Kauan Carneiro Almeida 

Link de Demonstração: https://youtube.com/shorts/cGRDk4f0v2E?si=ebOo9AdC3Z6WEpqx

Requisito 6:

#include <stdio.h>
#include "pico/stdlib.h" // biblioteca padrão para trabalhar com a raspberry pi pico
#include "hardware/pwm.h" // biblioteca para gerenciamento de temporizadores de hardware.

#define led_blue 12  // pino GPIO para o led azul

// Função para definir o brilho do ledazul
void ligar_led(uint slice, uint duty_cicle) {
    uint level = (duty_cicle * 24999) / 20000; // Calcula o nível de pwm(24999 é o WRAP e 2000 refere-se ao período total do ciclo)
    pwm_set_gpio_level(led_blue, duty_cicle); // Define o nível de PWM para o led azul
}

int main() {
    stdio_init_all(); // permite uso de printf
  
    gpio_set_function(led_blue, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(led_blue); // Obtém o slice de PWM para o led azul

    pwm_set_clkdiv(slice, 100.0); // Define o divisor de clock do PWM (ajusta a frequência do PWM)

    pwm_set_wrap(slice, 24999); // Define o valor de wrap 

    pwm_set_enabled(slice, true); // Habilita o PWM para o led azul

    while (true) {
        // Acende o led azul em brilho máximo
        ligar_led(NUM_PWM_SLICES, 2400); // 100% brilho
        sleep_ms(5000);

        // Acende o led azul com brilho médio
        ligar_led(slice, 1470); 
        sleep_ms(5000); 

        // Acende o led azul com brilho mínimo
        ligar_led(slice, 500); 
        sleep_ms(5000); 

        // vai do ponto de brilho mais fraco até o ponto máximo 
        for (int duty_cicle = 500; duty_cicle <= 2400; duty_cicle += 5){ // incia no ponto mínimo, e tem um aumento de 5 µs, movendo-se suavemente até o ponto máximo
            ligar_led(slice, duty_cicle); 
            sleep_ms(10); 
        }
        // Faz a operação contrária, sai do ponto máximo e vai para o mínimo
        for (int duty_cicle = 2400; duty_cicle >= 500; duty_cicle -= 5){ // incia no ponto máximo, e tem um decremento de 5 µs, movendo-se suavemente até o ponto mínimo
            ligar_led(slice, duty_cicle);
            sleep_ms(10); 
        }
        sleep_ms(2000); 
    }
}

 

