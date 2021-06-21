# Boost Roulette

Russian roulette, but with boost. Everyone loves RNG in their competitive games.  

![Rocket League 2021 03 30 - 11 25 28 06 DVR](https://user-images.githubusercontent.com/8890971/113019258-65b90400-914f-11eb-9869-f81bb457c564.gif)

## **[Go here to install with Bakkesmod.](https://bakkesplugins.com/plugins/view/207)**
  
## What is this?

Boost Roulette is a [BakkesMod](https://www.bakkesmod.com/) plugin for Rocket League on PC.
The plugin changes the way boost works sometimes.
Whenever someone picks up boost, there is a chance they will be demolished.  

By default, the demo chance depends on the type of boost:  

- Big boost: 1 / 6 = ~16.7%
- Small pads: 1 / 28 = ~3.6%

You can easily change the probabilities in the plugin window.

## Is it safe to use?

Yes, it is safe, but that doesn't mean much coming from the developer. The plugin was rewritten in C++ for better overall support and user quality of life. You don't have to trust me, though. I have provided the source code to site staff at bakkesplugins.com. Staff members will verify the plugin is safe to use!

## How to Use

The Boost Roulette plugin is disabled by default. To enable it:

1. Open up the BakkesMod window (F2)
2. Go to the ```Plugins``` tab
3. Click on ```Boost Roulette Plugin```
4. Click the checkbox under ```Enable Boost Roulette Plugin```

Now, it should work!  

You can move the sliders to change the probability of demo per type of boost.

**If you are having any issues, I've listed solutions to common problems below.**

## Help Desk

### Help: The checkbox and probability sliders are not showing up in the plugin window

Most likely, the plugin loaded without refreshing the setting files.  

1. Close the BakkesMod window and open up the BakkesMod console (F6).
2. Make sure the plugin is loaded by entering ```plugin load boostrouletteplugin```
3. Refresh the settings files by entering ```cl_settings_refreshplugins```.
4. The checkbox and sliders should appear now!

---

### Help: The ```Install with BakkesMod``` button isn't working

You will have to install the plugin manually. Don't worry. I made a quick video to show you how!  
[Click here](https://youtu.be/EgsTUwlTjbM)

---

### Help: How do I play with friends?

You will have to host your own lobby to use the plugin with friends. I recommend using [RocketPlugin](https://bakkesplugins.com/plugins/view/26). You have to do this because private matches are hosted on Psyonix's servers, so plugins will not work on their servers.

Only the host needs to have Boost Roulette installed, but to keep it accessible for everyone, I recommend everyone installs RocketPlugin.
