#include <stdio.h> // Biblioteca padrão da linguagem C
#include "pico/stdlib.h" // Subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" // Biblioteca para controle do PWM
#include "hardware/adc.h" // Biblioteca para controle da conversão ADC
#include "hardware/i2c.h" // Biblioteca para controle da comunicação I2C
#include "include/ssd1306.h" // Biblioteca para controle do display OLED
#include "pico/bootrom.h" // Biblioteca para controle do bootrom

#define GREEN 11 // Pino conectado ao LED verde
#define BLUE 12 // Pino conectado ao LED azul
#define RED 13 // Pino conectado ao LED vermelho
#define A_BUTTON 5 // Pino conectado ao botão A
#define B_BUTTON 6 // Pino conectado ao botão B
#define JOY_BUTTON 22 // Pino conectado ao botão do joystick
#define DIVIDER 19.0 // Divisor do clock para o PWM
#define WRAP 65519 // Valor máximo do contador sendo 65520
uint slice_red, slice_blue; // Declaração dos slices dos canais PWM
uint16_t adc_value_x, adc_value_y;
uint16_t x = 60, y = 28; // Variáveis para armazenar as coordenadas do quadrado
uint16_t level_x = 0, level_y = 0; // Declaração das variáveis de níveis iniciais do PWM
volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
bool pwm_on = true; // Variável para armazenar o estado do PWM dos LEDs
bool borda = false; // Variável para armazenar o estado do botão do Joystick

// Definições da comunicação I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define address 0x3C
ssd1306_t ssd; // Inicializa a estrutura do display para todas as funções

void pwm_setup(uint led, uint *slice, uint16_t level) { 
    gpio_set_function(led, GPIO_FUNC_PWM); // Habilitar o pino do LED como PWM
    *slice = pwm_gpio_to_slice_num(led); // Obtem o canal PWM da GPIO
    pwm_set_clkdiv(*slice, DIVIDER); // Define o divisor de clock do PWM
    pwm_set_wrap(*slice, WRAP); // Define o valor de wrap
    pwm_set_gpio_level(led, level); // Define o ciclo de trabalho ativo do pwm para 2400 μs
    pwm_set_enabled(*slice, true); //habilita o pwm no slice correspondente
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time > 200000) { //Apenas ativa as funções quando o intervalo entre acionamentos é superior a 0.2 segundos
      last_time = current_time; //Atualiza o tempo do último evento
      if (gpio == A_BUTTON) {
        pwm_on = !pwm_on; // Inverte o estado do PWM
        pwm_set_enabled(slice_blue, !pwm_on); // Muda o estado de ativação do PWM do LED azul
        pwm_set_enabled(slice_red, !pwm_on); // Muda o estado de ativação do PWM do LED vermelho
      } else if (gpio == B_BUTTON) {
          reset_usb_boot(0,0); //Habilita o modo de gravação do microcontrolador
        } else if (gpio == JOY_BUTTON) {
          gpio_put(GREEN, !gpio_get(GREEN)); // Inverte o estado do LED verde
          borda = !borda; // Inverte o estilo da borda do Display
      }
    }  
  }

int main() {
    
    stdio_init_all(); // Inicializa o sistema padrão de I/O
    
    gpio_init(GREEN); // Inicializa o pino do LED verde
    gpio_set_dir(GREEN, GPIO_OUT); // Configura o pino do LED verde como saída
    gpio_init(BLUE); // Inicializa o pino do LED azul
    gpio_set_dir(BLUE, GPIO_OUT); // Configura o pino do LED azul como saída
    gpio_init(RED); // Inicializa o pino do LED vermelho
    gpio_set_dir(RED, GPIO_OUT); // Configura o pino do LED vermelho como saída

    gpio_init(A_BUTTON); // Inicializa o pino do botão A
    gpio_set_dir(A_BUTTON, GPIO_IN); // Configura o pino do botão A como entrada
    gpio_pull_up(A_BUTTON); // Habilita o pull-up do botão A
    gpio_init(B_BUTTON); // Inicializa o pino do botão B
    gpio_set_dir(B_BUTTON, GPIO_IN); // Configura o pino do botão B como entrada
    gpio_pull_up(B_BUTTON); // Habilita o pull-up do botão B
    gpio_init(JOY_BUTTON); // Inicializa o pino do botão do Joystick
    gpio_set_dir(JOY_BUTTON, GPIO_IN); // Configura o pino do botão do Joystick como entrada
    gpio_pull_up(JOY_BUTTON); // Habilita o pull-up do botão do Joystick

    // Inicialização de interrupções dos botões
    gpio_set_irq_enabled_with_callback(A_BUTTON, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção do botão A
    gpio_set_irq_enabled_with_callback(B_BUTTON, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção do botão B
    gpio_set_irq_enabled_with_callback(JOY_BUTTON, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção do botão do Joystick

    // Inicialização da comunicação I2C. Utilizando a frequência de 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);  // Configura o pino para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Configura o pino para I2C
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, address, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display
    
    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    
    // Configuração das saídas PWM
    pwm_setup(RED, &slice_red, level_x); // Configura o LED vermelho como PWM
    pwm_setup(BLUE, &slice_blue, level_y); // Configura o LED azul como PWM

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
