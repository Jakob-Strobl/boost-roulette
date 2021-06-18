#include "BoostRoulette.h"

BAKKESMOD_PLUGIN(BoostRoulette, "Boost Roulette", "0.1", 0)
void BoostRoulette::onLoad() {
	this->cvarManager->log("BoostRoulette::onLoad() was invoked!");


}

void BoostRoulette::onUnload() {
	this->cvarManager->log("Boost Roulette is being unloaded...");
}