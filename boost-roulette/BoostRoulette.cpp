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
		this->gameWrapper->HookEventWithCaller<BoostPickupWrapper>("Function TAGame.VehiclePickup_Boost_TA.Pickup", std::bind(&BoostRoulette::onBoostPickup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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

void BoostRoulette::onBoostPickup(BoostPickupWrapper boost, void* params, std::string eventName) {
	this->cvarManager->log("Boost:");
	this->cvarManager->log(std::to_string((uintptr_t) &boost));

	this->cvarManager->log("Boost type:");
	this->cvarManager->log(std::to_string(boost.GetBoostType()));

	/*
	BoostType boostType = parseBoostType(boost->GetBoostType());

	switch (boostType) {
		case BoostType::BIG:
			this->cvarManager->log("Big boost picked up!");
			break;
		case BoostType::PAD:
			this->cvarManager->log("Boost pad picked up!");
			break;
		default:
			this->cvarManager->log("Inavlid boost type");
	}

	*/
}

BoostType parseBoostType(unsigned char type)
{
	switch (type) {
	case 1:
		return BoostType::BIG;
	case 2:
		return BoostType::PAD;
	default:
		return BoostType::UNKNOWN;
	}
}