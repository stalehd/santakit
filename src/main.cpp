#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IRRemote.hpp>

#include <arduino_homekit_server.h>

#include "tree.h"

#define IR_SEND_LED 14
#define IR_ADDRESS 0
#define IR_ON 0x45
#define IR_OFF 0x47
#define IR_COMBO 0x44
#define IR_WAVES 0x43
#define IR_SEQUENTIAL 0x7
#define IR_SLOGLO 0x9
#define IR_CHASING 0x16
#define IR_SLOFADE 0xd
#define IR_EPILEPTIC 0xc
#define IR_STEADY 0x5e
#define IR_REPEATS 1

#ifndef WIFI_SSID
#define WIFI_SSID ""
#endif

#ifndef WIFI_PASS
#define WIFI_PASS ""
#endif

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

#define SIMPLE_INFO(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);


//==============================
// Homekit setup and loop
//==============================
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_steady;
extern "C" homekit_characteristic_t cha_waves;
extern "C" homekit_characteristic_t cha_sequential;
extern "C" homekit_characteristic_t cha_sloglo;
extern "C" homekit_characteristic_t cha_chasing;
extern "C" homekit_characteristic_t cha_slofade;
extern "C" homekit_characteristic_t cha_epileptic;

//Called when the switch value is changed by iOS Home APP
void cha_steady_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_steady.value.bool_value = on;	//sync the value	
	setTreeState(on ? ON_STEADY : OFF);
}
void cha_waves_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_waves.value.bool_value = on;	//sync the value
	setTreeState(on ? ON_WAVES : OFF);
}
void cha_sequential_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_sequential.value.bool_value = on;	//sync the value
	setTreeState(on ? ON_SEQUENTIAL : OFF);
}

void cha_sloglo_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_sloglo.value.bool_value = on;	//sync the value
	setTreeState(on ? ON_SLOGLO : OFF);
}

void cha_chasing_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_chasing.value.bool_value = on;	//sync the value
	setTreeState(on ? ON_CHASING : OFF);
}

void cha_slofade_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_slofade.value.bool_value = on;	//sync the value
	setTreeState(on ? ON_SLOFADE : OFF);
}

void cha_epileptic_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_epileptic.value.bool_value = on;	//sync the value
	setTreeState(on ? ON_EPILEPTIC : OFF);
}


void homekit_setup() {

	cha_steady.setter = cha_steady_setter;
	cha_waves.setter = cha_waves_setter;
	cha_sequential.setter = cha_sequential_setter;
	cha_sloglo.setter = cha_sloglo_setter;
	cha_chasing.setter = cha_chasing_setter;
	cha_slofade.setter = cha_slofade_setter;
	cha_epileptic.setter = cha_epileptic_setter;

	arduino_homekit_setup(&config);

	//report the switch value to HomeKit if it is changed (e.g. by a physical button)
	//bool switch_is_on = true/false;
	//cha_switch_on.value.bool_value = switch_is_on;
	//homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
}

void homekit_loop() {
	arduino_homekit_loop();
	static uint32_t next_heap_millis = 0;
	uint32_t time = millis();
	if (time > next_heap_millis) {
		SIMPLE_INFO("heap: %d, sockets: %d",
				ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
		next_heap_millis = time + 5000;
	}

}

void setup() {
	Serial.begin(115200);
	Serial.setRxBufferSize(32);
	Serial.setDebugOutput(false);


	WiFi.mode(WIFI_STA);
	WiFi.persistent(false);
	WiFi.disconnect(false);
	WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, password);

	// Set up IR
	IrSender.begin(IR_SEND_LED, false, 0); 

	SIMPLE_INFO("");
	SIMPLE_INFO("SketchSize: %d", ESP.getSketchSize());
	SIMPLE_INFO("FreeSketchSpace: %d", ESP.getFreeSketchSpace());
	SIMPLE_INFO("FlashChipSize: %d", ESP.getFlashChipSize());
	SIMPLE_INFO("FlashChipRealSize: %d", ESP.getFlashChipRealSize());
	SIMPLE_INFO("FlashChipSpeed: %d", ESP.getFlashChipSpeed());
	SIMPLE_INFO("SdkVersion: %s", ESP.getSdkVersion());
	SIMPLE_INFO("FullVersion: %s", ESP.getFullVersion().c_str());
	SIMPLE_INFO("CpuFreq: %dMHz", ESP.getCpuFreqMHz());
	SIMPLE_INFO("FreeHeap: %d", ESP.getFreeHeap());
	SIMPLE_INFO("ResetInfo: %s", ESP.getResetInfo().c_str());
	SIMPLE_INFO("ResetReason: %s", ESP.getResetReason().c_str());
	INFO_HEAP();

	homekit_setup();

	INFO_HEAP();
}

void sendCommands(int lastState, int newState) {
	if (newState == OFF) {
		// Send off
		printf("Turn off tree\n");
		IrSender.sendNEC(IR_ADDRESS, IR_OFF, IR_REPEATS);
		return;
	}
	if (lastState == OFF) {
		// Send on before sending mode
		printf("Turn on tree\n");
		IrSender.sendNEC(IR_ADDRESS, IR_ON, IR_REPEATS);
	}
	switch (newState) {
	case ON_WAVES:
		printf("Tree: Waves\n");
		IrSender.sendNEC(IR_ADDRESS, IR_WAVES, IR_REPEATS);
		break;
	case ON_SEQUENTIAL:
		printf("Tree: Sequential\n");
		IrSender.sendNEC(IR_ADDRESS, IR_SEQUENTIAL, IR_REPEATS);
		break;
	case ON_SLOGLO:
		printf("Tree: Sloglo\n");
		IrSender.sendNEC(IR_ADDRESS, IR_SLOGLO, IR_REPEATS);
		break;
	case ON_CHASING:
		printf("Tree: Chasing\n");
		IrSender.sendNEC(IR_ADDRESS, IR_CHASING, IR_REPEATS);
		break;
	case ON_SLOFADE:
		printf("Tree: Slofade\n");
		IrSender.sendNEC(IR_ADDRESS, IR_SLOFADE, IR_REPEATS);
		break;
	case ON_EPILEPTIC:
		printf("Tree: Epileptic\n");
		IrSender.sendNEC(IR_ADDRESS, IR_EPILEPTIC, IR_REPEATS);
		break;
	default:
		printf("Tree: Steady\n");
		IrSender.sendNEC(IR_ADDRESS, IR_STEADY, IR_REPEATS);
		break;
	}
}

int lastState = OFF;
void loop() {
	if (getTreeState() != lastState) {
		// State has changed. Send notification for off value
		switch (lastState) {
			case ON_STEADY:
				cha_steady.value.bool_value = false;
				homekit_characteristic_notify(&cha_steady, cha_steady.value);				
				break;
			case ON_WAVES:
				cha_waves.value.bool_value = false;
				homekit_characteristic_notify(&cha_waves, cha_waves.value);
				break;
			case ON_SEQUENTIAL:
				cha_sequential.value.bool_value = false;
				homekit_characteristic_notify(&cha_sequential, cha_sequential.value);
				break;
			case ON_SLOGLO:
				cha_sloglo.value.bool_value = false;
				homekit_characteristic_notify(&cha_sloglo, cha_sloglo.value);
				break;
			case ON_CHASING:
				cha_chasing.value.bool_value = false;
				homekit_characteristic_notify(&cha_chasing, cha_chasing.value);
				break;
			case ON_SLOFADE:
				cha_slofade.value.bool_value = false;
				homekit_characteristic_notify(&cha_slofade, cha_slofade.value);
				break;
			case ON_EPILEPTIC:
				cha_epileptic.value.bool_value = false;			
				homekit_characteristic_notify(&cha_epileptic, cha_epileptic.value);
				break;
		}
		// Send IR commands to tree
		sendCommands(lastState, getTreeState());
		lastState = getTreeState();		
	}
	homekit_loop();
}

