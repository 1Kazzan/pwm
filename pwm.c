#include <stdio.h>
#include "pico/stdlib.h" // biblioteca padrão para trabalhar com a raspberry pi pico
#include "hardware/pwm.h" //biblioteca para gerenciamento de temporizadores de hardware.

#define servomotor 22 // pino GPIO conectado ao servomotor

// função para mover o servo para uma posição específica
void mover(uint slice, uint duty_cicle) {
    uint level = (duty_cicle * 24999) / 20000; // Calcula o nível de pwm(24999 é o WRAP e 2000 refere-se ao período total do ciclo)
    pwm_set_gpio_level(servomotor, level); //// define o nível de PWM no pino GPIO
}

int main (){

    stdio_init_all(); // permite uso de printf
  
    gpio_set_function(servomotor, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(servomotor); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, 100.0); //define o divisor de clock do PWM
    pwm_set_wrap(slice, 24999); //define o valor de wrap

    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente

    while (true) {
        mover(slice, 2400);// 180°
        sleep_ms(5000);

        mover(slice, 1470);//90 °
        sleep_ms(5000);

        mover(slice, 500); //0°
        sleep_ms(5000);

       
         // movimentação de 0° para 180°
         for (int duty_cicle = 500; duty_cicle <= 2400; duty_cicle += 5){ // incia na posição de 0°, e tem um aumento de 5 µs, movendo-se suavemente até 180°
            mover(slice, duty_cicle); 
            sleep_ms(10); 
        }
        // movimentação de 180° para 0°
        for (int duty_cicle = 2400; duty_cicle >= 500; duty_cicle -= 5){ // incia na posição de 180°, e tem um decremento de 5 µs, movendo-se suavemente até 0°
            mover(slice, duty_cicle);
            sleep_ms(10); 
        }
    }
}
    







