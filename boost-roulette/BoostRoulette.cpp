#include "BoostRoulette.h"
#include <stdio.h>

BAKKESMOD_PLUGIN(BoostRoulette, "Boost Roulette", "0.1", 0)
void BoostRoulette::onLoad() {
	this->cvarManager->log("BoostRoulette::onLoad() was invoked!");

	// Default Values
	bool enabled = false;
	float bigBoostDemoChance = 1.0f / NUM_BIG_BOOSTS;
	float padDemoChance = 1.0f / NUM_PADS;

	this->enabled = std::make_shared<CVarWrapper>(
		this->cvarManager->registerCvar(
			"boost_roulette_is_enabled",
			std::to_string(enabled),
			"Enables/disables Boost Roulette plugin.",
			true,
			true,
			0.0,
			true,
			0.0,
			false
		)
	);

	this->bigBoostDemoChance = std::make_shared<CVarWrapper>(
		this->cvarManager->registerCvar(
			"boost_roulette_big_boost_chance",
			std::to_string(bigBoostDemoChance),
			"The probability a big boost demos on pickup.",
			true,
			true,
			0.0,
			true,
			1.0,
			false
		)
	);

	this->padDemoChance = std::make_shared<CVarWrapper>(
		this->cvarManager->registerCvar(
			"boost_roulette_pad_chance",
			std::to_string(padDemoChance),
			"The probability a boost pad demos on pickup.",
			true,
			true,
			0.0,
			true,
			1.0,
			false
		)
	);


	(*this->enabled).addOnValueChanged(std::bind(&BoostRoulette::onEnabledChanged, this, std::placeholders::_1, std::placeholders::_2));
	(*this->bigBoostDemoChance).addOnValueChanged(std::bind(&BoostRoulette::onBoostDemoChanceChanged, this, std::placeholders::_1, std::placeholders::_2));
	(*this->padDemoChance).addOnValueChanged(std::bind(&BoostRoulette::onBoostDemoChanceChanged, this, std::placeholders::_1, std::placeholders::_2));
}

void BoostRoulette::onUnload() {
	this->cvarManager->log("Boost Roulette is being unloaded...");
}

void BoostRoulette::onEnabledChanged(std::string oldValue, CVarWrapper cvar) {
	if (cvar.getBoolValue()) {
		this->cvarManager->log("Boost Roulette enabled!");
	}
	else {
		this->cvarManager->log("Boost Roulette disabled!");
	}
}

void BoostRoulette::onBoostDemoChanceChanged(std::string oldValue, CVarWrapper cvar) {
	const int MSG_SIZE = 50;
	char msg[MSG_SIZE];
	
	int chars = snprintf(msg, MSG_SIZE, "%s => %.2f", cvar.getCVarName().c_str(), cvar.getFloatValue());
	this->cvarManager->log(msg);
}
