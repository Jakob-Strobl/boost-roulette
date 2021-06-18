#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod\plugin\bakkesmodplugin.h"

class BoostRoulette : public BakkesMod::Plugin::BakkesModPlugin {
	private:
		// TODO remove these Wrappers. Documentation says we should grab when needed, which I guess makes sense. 
		std::shared_ptr<CVarWrapper> enabled;
		std::shared_ptr<CVarWrapper> bigBoostDemoChance;
		std::shared_ptr<CVarWrapper> padDemoChance;

	public:
		virtual void onLoad();
		virtual void onUnload();

		void onEnabledChanged(std::string oldValue, CVarWrapper cvar);
		// This is called when both big boost and boost pad chances are changed
		void onBoostDemoChanceChanged(std::string oldValue, CVarWrapper cvar);

		void onBoostPickup(BoostPickupWrapper caller, void* params, std::string eventName);
};

enum class BoostType {
	UNKNOWN = 0,
	BIG = 1,
	PAD = 2,
};

BoostType parseBoostType(unsigned char type);

const int NUM_BIG_BOOSTS = 6;
const int NUM_PADS = 28;

// Thank you Martinn from BakkesMod discord. I didn't even think of this. 
template <typename T, typename std::enable_if<std::is_base_of<ObjectWrapper, T>::value>::type*>
void GameWrapper::HookEventWithCaller(std::string eventName, std::function<void(T caller, void* params, std::string eventName)> callback)
{
	auto wrapped_callback = [callback](ActorWrapper caller, void* params, std::string eventName)
	{
		callback(T(caller.memory_address), params, eventName);
	};
	HookEventWithCaller<ActorWrapper>(eventName, wrapped_callback);
}