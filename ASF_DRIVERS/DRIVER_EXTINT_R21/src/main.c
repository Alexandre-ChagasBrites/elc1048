#include <asf.h>

void configure_extint_channel(void);

int main(void)
{
	system_init();
	configure_extint_channel();

	while (true) {
		if (extint_chan_is_detected(BUTTON_0_EIC_LINE)) {
			bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
			port_pin_set_output_level(LED_0_PIN, button_pin_state);
			extint_chan_clear_detected(BUTTON_0_EIC_LINE);
		}
	}
}

void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	
	config_extint_chan.gpio_pin           = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux       = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
}
