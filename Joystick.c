#include <stdio.h> // Biblioteca padrão da linguagem C
#include "pico/stdlib.h" // Subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define GREEN 11 // Pino conectado ao LED verde
#define BLUE 12 // Pino conectado ao LED azul
#define RED 13 // Pino conectado ao LED vermelho
#define JOY_BUTTON 22 // Pino conectado ao botão do joystick
#define WRAP 65519 // Valor máximo do contador sendo 65520
#define DIVIDER 16.0 // Divisor do clock para o PWM
uint slice_red, slice_blue; // Declaração dos slices dos canais PWM
uint16_t level_x = 0, level_y = 0; // Declaração das variáveis de níveis iniciais do PWM

void pwm_setup(uint led, uint *slice, uint16_t level) { 
    gpio_set_function(led, GPIO_FUNC_PWM); // Habilitar o pino do LED como PWM
    *slice = pwm_gpio_to_slice_num(led); // Obtem o canal PWM da GPIO
    pwm_set_clkdiv(*slice, DIVIDER); // Define o divisor de clock do PWM
    pwm_set_wrap(*slice, WRAP); // Define o valor de wrap
    pwm_set_gpio_level(led, level); // Define o ciclo de trabalho ativo do pwm para 2400 μs
    pwm_set_enabled(*slice, true); //habilita o pwm no slice correspondente
}

int main() {
    stdio_init_all(); // Inicializa o sistema padrão de I/O

    pwm_setup(RED, &slice_red, level_x); // Configura o LED vermelho como PWM
    pwm_setup(BLUE, &slice_blue, level_y); // Configura o LED azul como PWM

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
