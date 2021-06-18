#pragma once
#pragma comment(lib, "bakkesmod.lib")
#include "bakkesmod\plugin\bakkesmodplugin.h"

class BoostRoulette : public BakkesMod::Plugin::BakkesModPlugin {
	private:
		std::shared_ptr<CVarWrapper> enabled;
		std::shared_ptr<CVarWrapper> bigBoostDemoChance;
		std::shared_ptr<CVarWrapper> padDemoChance;

	public:
		virtual void onLoad();
		virtual void onUnload();

		void onEnabledChanged(std::string oldValue, CVarWrapper cvar);
		void onBoostDemoChanceChanged(std::string oldValue, CVarWrapper cvar);


};

enum BoostType {
	BIG = 1,
	PAD = 2,
};

const int NUM_BIG_BOOSTS = 6;
const int NUM_PADS = 28;