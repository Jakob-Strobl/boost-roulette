#include "BoostRoulette.h"
#include <stdio.h>

BAKKESMOD_PLUGIN(BoostRoulette, "Boost Roulette", "0.1", 0)
void BoostRoulette::onLoad() {
	this->cvarManager->log("BoostRoulette::onLoad() was invoked!");

	// Default Values
	this->enabled = std::make_shared<bool>(false);
	float bigBoostDemoChance = 1.0f / NUM_BIG_BOOSTS;
	float padBoostDemoChance = 1.0f / NUM_PADS;

	// Seed pRNG
	srand((unsigned)time(NULL));

	auto cvar_enabled = this->cvarManager->registerCvar(
		"boost_roulette_is_enabled",
		std::to_string(*this->enabled),
		"Enables/disables Boost Roulette plugin.",
		true,
		true,
		0.0,
		true,
		0.0,
		false
	);

	auto cvar_bigBoostDemoChance = this->cvarManager->registerCvar(
		"boost_roulette_big_boost_chance",
		std::to_string(bigBoostDemoChance),
		"The probability a big boost demos on pickup.",
		true,
		true,
		0.0,
		true,
		1.0,
		false
	);

	auto cvar_padBoostDemoChance = this->cvarManager->registerCvar(
		"boost_roulette_pad_boost_chance",
		std::to_string(padBoostDemoChance),
		"The probability a boost pad demos on pickup.",
		true,
		true,
		0.0,
		true,
		1.0,
		false
	);

	cvar_enabled.addOnValueChanged(std::bind(&BoostRoulette::onEnabledChanged, this, std::placeholders::_1, std::placeholders::_2));
	cvar_bigBoostDemoChance.addOnValueChanged(std::bind(&BoostRoulette::onBoostDemoChanceChanged, this, std::placeholders::_1, std::placeholders::_2));
	cvar_padBoostDemoChance.addOnValueChanged(std::bind(&BoostRoulette::onBoostDemoChanceChanged, this, std::placeholders::_1, std::placeholders::_2));
}

void BoostRoulette::onUnload() {}

void BoostRoulette::onEnabledChanged(std::string oldValue, CVarWrapper cvar) {
	if (cvar.getBoolValue()) {
		this->cvarManager->log("Boost Roulette enabled!");
		this->gameWrapper->HookEventWithCaller<BoostPickupWrapper>("Function TAGame.VehiclePickup_Boost_TA.Pickup", std::bind(&BoostRoulette::onBoostPickup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	else {
		this->cvarManager->log("Boost Roulette disabled!");
		this->gameWrapper->UnhookEvent("Function TAGame.VehiclePickup_Boost_TA.Pickup");
	}
}

void BoostRoulette::onBoostDemoChanceChanged(std::string oldValue, CVarWrapper cvar) {
	const int MSG_SIZE = 50;
	char msg[MSG_SIZE];

	int chars = snprintf(msg, MSG_SIZE, "%s => %.2f", cvar.getCVarName().c_str(), cvar.getFloatValue());
	this->cvarManager->log(msg);
}

void BoostRoulette::onBoostPickup(BoostPickupWrapper boost, void* rawParams, std::string eventName) {
	// params in this case (maybe all cases?) is actually a double pointer (I think?)
	// the params is a void pointer that points to a pointer to the CarWrapper that picked up the boost
	struct onBoostPickupParams {
		uintptr_t car_address;
	} params;
	params = *(onBoostPickupParams*)rawParams;
	CarWrapper car = CarWrapper::CarWrapper(params.car_address);

	// Null checks
	if (boost.IsNull() || car.IsNull()) {
		return;
	}


	BoostType boostType = parseBoostType(boost.GetBoostType());
	bool isUnlucky = false;

	switch (boostType) {
		case BoostType::BIG:
			//this->cvarManager->log("Big boost picked up!");
			isUnlucky = this->rollBigBoost();
			break;
		case BoostType::PAD:
			//this->cvarManager->log("Boost pad picked up!");
			isUnlucky = this->rollPadBoost();
			break;
		default:
			this->cvarManager->log("Inavlid boost type");
	}

	if (isUnlucky) {
		car.Demolish2(RBActorWrapper(car.memory_address));
	}
}

bool BoostRoulette::rollBigBoost() {
	auto chance = this->cvarManager->getCvar("boost_roulette_big_boost_chance");
	if (chance.IsNull()) {
		return false;
	}

	double roll = (float) rand() / RAND_MAX;
	return roll < chance.getFloatValue();
}

bool BoostRoulette::rollPadBoost() {
	auto chance = this->cvarManager->getCvar("boost_roulette_pad_boost_chance");
	if (chance.IsNull()) {
		return false;
	}

	double roll = (float)rand() / RAND_MAX;
	return roll < chance.getFloatValue();
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