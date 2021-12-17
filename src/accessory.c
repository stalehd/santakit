/*
 * accessory.c - set up the accessory definition for the TreeKit
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void tree_identify(homekit_value_t _value) {
	printf("SantaKit Tree Control (tm)\n");
}

homekit_characteristic_t cha_steady = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_steady_name = HOMEKIT_CHARACTERISTIC_(NAME, "Oh God Make The Blinking Stop");

homekit_characteristic_t cha_waves = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_waves_name = HOMEKIT_CHARACTERISTIC_(NAME, "In Waves");

homekit_characteristic_t cha_sequential = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_sequential_name = HOMEKIT_CHARACTERISTIC_(NAME, "Sequential");

homekit_characteristic_t cha_sloglo = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_sloglo_name = HOMEKIT_CHARACTERISTIC_(NAME, "Slo-Glo");


homekit_characteristic_t cha_chasing = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_chasing_name = HOMEKIT_CHARACTERISTIC_(NAME, "Chasing/Flash");

homekit_characteristic_t cha_slofade = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_slofade_name = HOMEKIT_CHARACTERISTIC_(NAME, "Slo-Fade");

homekit_characteristic_t cha_epileptic = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_epileptic_name = HOMEKIT_CHARACTERISTIC_(NAME, "Epileptic Seizure");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Christmas Tree"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "SantaKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "47114711"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, tree_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){ // mode 8 - old school
			&cha_steady_name,
            &cha_steady,			
			NULL
		}),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){ // mode 2 - waves
			&cha_waves_name,
            &cha_waves,			
			NULL
		}),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){ // mode 3 - waves
			&cha_sequential_name,
            &cha_sequential,			
			NULL
		}),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){ // mode 4 - slo-glo
			&cha_sloglo_name,
            &cha_sloglo,			
			NULL
		}),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){ // mode 5 - chasing/flash
			&cha_chasing_name,
            &cha_chasing,			
			NULL
		}),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){ // mode 6 - slow fade
			&cha_slofade_name,
            &cha_slofade,			
			NULL
		}),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){ // mode 7 - epileptic
			&cha_epileptic_name,
            &cha_epileptic,			
			NULL
		}),
        NULL
    }),
    NULL
};


homekit_server_config_t config = {
		.accessories = accessories,
		.password = "666-66-666"
};
