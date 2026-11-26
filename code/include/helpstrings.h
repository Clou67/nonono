#ifndef HELPSTRINGS_H
#define HELPSTRINGS_H

// Text ids used by the help and message system; the comment is the English text.
enum HELP_STRING_IDS {
    HELP_STR_0x4E34 = 0x00004E34,  /* "#" */
    HELP_STR_THE_CIRCLE_BUTTON = 0x00004E35,  /* "the circle button" */
    HELP_STR_THE_SQUARE_BUTTON = 0x00004E36,  /* "the square button" */
    HELP_STR_THE_X_BUTTON = 0x00004E37,  /* "the X button" */
    HELP_STR_THE_TRIANGLE_BUTTON = 0x00004E38,  /* "the triangle button" */
    HELP_STR_THE_R1_BUTTON = 0x00004E39,  /* "the R1 button" */
    HELP_STR_THE_R2_BUTTON = 0x00004E3A,  /* "the R2 button" */
    HELP_STR_THE_L1_BUTTON = 0x00004E3B,  /* "the L1 button" */
    HELP_STR_THE_L2_BUTTON = 0x00004E3C,  /* "the L2 button" */
    HELP_STR_THE_SELECT_BUTTON = 0x00004E3D,  /* "the SELECT button" */
    HELP_STR_THE_START_BUTTON = 0x00004E3E,  /* "the START button" */
    HELP_STR_THE_RIGHT_ANALOG_STICK = 0x00004E3F,  /* "the right analog stick" */
    HELP_STR_THE_LEFT_ANALOG_STICK = 0x00004E40,  /* "the left analog stick" */
    HELP_STR_X_UNITS = 0x00004E41,  /* "[x units]" */
    HELP_STR_DRONE_DEVICE = 0x00004E42,  /* "Drone Device" */
    HELP_STR_MINE_GLOVE = 0x00004E43,  /* "Mine Glove" */
    HELP_STR_MORPH_O_RAY = 0x00004E44,  /* "Morph-o-ray" */
    HELP_STR_WALLOPER = 0x00004E45,  /* "Walloper" */
    HELP_STR_OMNIWRENCH = 0x00004E46,  /* "OmniWrench" */
    HELP_STR_BLASTER = 0x00004E47,  /* "Blaster" */
    HELP_STR_BOMB_GLOVE = 0x00004E48,  /* "Bomb Glove" */
    HELP_STR_PYROCITOR = 0x00004E49,  /* "Pyrocitor" */
    HELP_STR_SUCK_CANNON = 0x00004E4A,  /* "Suck Cannon" */
    HELP_STR_TESLA_CLAW = 0x00004E4B,  /* "Tesla Claw" */
    HELP_STR_GLOVE_OF_DOOM = 0x00004E4C,  /* "Glove of Doom" */
    HELP_STR_DEVASTATOR = 0x00004E4D,  /* "Devastator" */
    HELP_STR_RYNO = 0x00004E4E,  /* "R.Y.N.O." */
    HELP_STR_VISIBOMB = 0x00004E4F,  /* "Visibomb" */
    HELP_STR_VISIBOMB_GUN = 0x00004E50,  /* "Visibomb Gun" */
    HELP_STR_TAUNTER = 0x00004E51,  /* "Taunter" */
    HELP_STR_DECOY_GLOVE = 0x00004E52,  /* "Decoy Glove" */
    HELP_STR_DRONE_DEVICE_2 = 0x00004E53,  /* "Drone Device" */
    HELP_STR_MINE_GLOVE_2 = 0x00004E54,  /* "Mine Glove" */
    HELP_STR_MORPH_O_RAY_2 = 0x00004E55,  /* "Morph-o-ray" */
    HELP_STR_BOMB_GLOVE_2 = 0x00004E56,  /* "Bomb Glove" */
    HELP_STR_SUCK_CANNON_2 = 0x00004E57,  /* "Suck Cannon" */
    HELP_STR_TESLA_CLAW_2 = 0x00004E58,  /* "Tesla Claw" */
    HELP_STR_DECOY_GLOVE_2 = 0x00004E59,  /* "Decoy Glove" */
    HELP_STR_VISIBOMB_GUN_2 = 0x00004E5A,  /* "Visibomb Gun" */
    HELP_STR_GLOVE_OF_DOOM_2 = 0x00004E5B,  /* "Glove of Doom" */
    HELP_STR_HYDRODISPLACER = 0x00004E5C,  /* "Hydrodisplacer" */
    HELP_STR_HOLOGUISE = 0x00004E5D,  /* "Hologuise" */
    HELP_STR_METAL_DETECTOR = 0x00004E5E,  /* "Metal Detector" */
    HELP_STR_GADGETRON_PDA = 0x00004E5F,  /* "Gadgetron PDA" */
    HELP_STR_GADGETRON_PERSONAL_DELIVERY_ASSISTANT = 0x00004E60,  /* "Gadgetron Personal Delivery Assistant" */
    HELP_STR_SWINGSHOT = 0x00004E61,  /* "Swingshot" */
    HELP_STR_HYDRODISPLACER_2 = 0x00004E62,  /* "Hydrodisplacer" */
    HELP_STR_TRESPASSER = 0x00004E63,  /* "Trespasser" */
    HELP_STR_HOLOGUISE_2 = 0x00004E64,  /* "Hologuise" */
    HELP_STR_METAL_DETECTOR_2 = 0x00004E65,  /* "Metal Detector" */
    HELP_STR_GADGETRON_PDA_2 = 0x00004E66,  /* "Gadgetron PDA" */
    HELP_STR_MAGNEBOOTS = 0x00004E67,  /* "Magneboots" */
    HELP_STR_GRINDBOOTS = 0x00004E68,  /* "Grindboots" */
    HELP_STR_HOVERBOARD = 0x00004E69,  /* "Hoverboard" */
    HELP_STR_SONIC_SUMMONER = 0x00004E6A,  /* "Sonic Summoner" */
    HELP_STR_O2_MASK = 0x00004E6B,  /* "O2 Mask" */
    HELP_STR_PILOTS_HELMET = 0x00004E6C,  /* "Pilot's Helmet" */
    HELP_STR_THRUSTER_PACK = 0x00004E6D,  /* "Thruster-Pack" */
    HELP_STR_HELI_PACK = 0x00004E6E,  /* "Heli-Pack" */
    HELP_STR_HYDRO_PACK = 0x00004E6F,  /* "Hydro-Pack" */
    HELP_STR_MAP_O_MATIC = 0x00004E70,  /* "Map-o-matic" */
    HELP_STR_PREMIUM_NANOTECH = 0x00004E71,  /* "Premium Nanotech" */
    HELP_STR_ULTRA_NANOTECH = 0x00004E72,  /* "Ultra Nanotech" */
    HELP_STR_PERSUADER = 0x00004E73,  /* "Persuader" */
    HELP_STR_ZOOMERATOR = 0x00004E74,  /* "Zoomerator" */
    HELP_STR_RARITANIUM = 0x00004E75,  /* "Raritanium" */
    HELP_STR_CODEBOTS = 0x00004E76,  /* "CodeBots" */
    HELP_STR_CODEBOT = 0x00004E77,  /* "CodeBot" */
    HELP_STR_BOLT_GRABBER = 0x00004E78,  /* "Bolt Grabber" */
    HELP_STR_INFOBOTS = 0x00004E79,  /* "Infobots" */
    HELP_STR_HELPDESK = 0x00004E7A,  /* "HelpDesk" */
    HELP_STR_INFOBOT = 0x00004E7C,  /* "Infobot" */
    HELP_STR_INVINCO_LOCKS = 0x00004E7D,  /* "Invinco-Locks" */
    HELP_STR_INVINCO_LOCK = 0x00004E7E,  /* "Invinco-Lock" */
    HELP_STR_INSTA_DRAINS = 0x00004E7F,  /* "Insta-Drains" */
    HELP_STR_INSTA_FAUCETS = 0x00004E80,  /* "Insta-Faucets" */
    HELP_STR_VERSA_TARGETS = 0x00004E81,  /* "Versa-Targets" */
    HELP_STR_GRIND_RAILS = 0x00004E82,  /* "Grind Rails" */
    HELP_STR_MAGNE_STRIPS = 0x00004E83,  /* "Magne-Strips" */
    HELP_STR_JET_FIGHTER = 0x00004E84,  /* "Jet Fighter" */
    HELP_STR_HYPER_STRIKE = 0x00004E85,  /* "Hyper-Strike" */
    HELP_STR_BOOST_JUMP = 0x00004E86,  /* "Boost Jump" */
    HELP_STR_GLIDE = 0x00004E87,  /* "Glide" */
    HELP_STR_COMET_STRIKE = 0x00004E88,  /* "Comet-Strike" */
    HELP_STR_GADGE_BOTS = 0x00004E89,  /* "Gadge-Bots" */
    HELP_STR_BOT_PORTS = 0x00004E8A,  /* "Bot Ports" */
    HELP_STR_BOT_DEVICE = 0x00004E8B,  /* "Bot Device" */
    HELP_STR_MULTI_STRIKE = 0x00004E8C,  /* "Multi-Strike" */
    HELP_STR_STRETCH_JUMP = 0x00004E8D,  /* "Stretch Jump" */
    HELP_STR_POWER_SLAM = 0x00004E8E,  /* "Power Slam" */
    HELP_STR_INVINCO_VAULTS = 0x00004E8F,  /* "Invinco-Vaults" */
    HELP_STR_TRI_RINGS = 0x00004E90,  /* "Tri-Rings" */
    HELP_STR_GOLD_BOMB_GLOVE = 0x00004E91,  /* "Gold Bomb Glove" */
    HELP_STR_GOLD_PYROCITOR = 0x00004E92,  /* "Gold Pyrocitor" */
    HELP_STR_GOLD_BLASTER = 0x00004E93,  /* "Gold Blaster" */
    HELP_STR_GOLD_GLOVE_OF_DOOM = 0x00004E94,  /* "Gold Glove of Doom" */
    HELP_STR_GOLD_MINE_GLOVE = 0x00004E95,  /* "Gold Mine Glove" */
    HELP_STR_GOLD_DEVASTATOR = 0x00004E96,  /* "Gold Devastator" */
    HELP_STR_GOLD_DECOY_GLOVE = 0x00004E97,  /* "Gold Decoy Glove" */
    HELP_STR_GOLD_TESLA_CLAW = 0x00004E98,  /* "Gold Tesla Claw" */
    HELP_STR_GOLD_SUCK_CANNON = 0x00004E99,  /* "Gold Suck Cannon" */
    HELP_STR_GOLD_MORP_O_RAY = 0x00004E9A,  /* "Gold Morp-o-ray" */
    HELP_STR_SKILL_POINTS = 0x00004E9B,  /* "Skill Points" */
    HELP_STR_SKILL_POINT = 0x00004E9C,  /* "Skill Point" */
    HELP_STR_QUICKSELECT = 0x00004E9D,  /* "QuickSelect" */
    HELP_STR_GOLD_BOLTS = 0x00004E9E,  /* "Gold Bolts" */
    HELP_STR_GOLD_BOLT = 0x00004E9F,  /* "Gold Bolt" */
    HELP_STR_THANKS_TO_YOUR_STELLAR_0x531D = 0x0000531D,  /* "Thanks to your stellar piloting, you're stranded without a ship. Complicating matters is the fact that Tobruk Crater is being invaded by Drek's robot army. Yet with all of that military hardware, there's got to be a ship around somewhere... " */
    HELP_STR_THESE_WATERWORKS_ARE_ONE_0x531E = 0x0000531E,  /* "These waterworks are one of the things Drek plans to steal from this planet. You should search them thoroughly before they're ripped from the planet." */
    HELP_STR_GOOD_JOB_FINDING_THE_0x531F = 0x0000531F,  /* "Good job finding the mechanic. You should seriously consider buying the Infobot he has for sale. It will provide coordinates for a new planet." */
    HELP_STR_FIND_A_NEW_SHIP = 0x00005320,  /* "Find a new ship" */
    HELP_STR_EXPLORE_THE_WATERWORKS = 0x00005321,  /* "Explore the waterworks" */
    HELP_STR_BUY_INFOBOT_FROM_MECHANIC = 0x00005322,  /* "Buy Infobot from mechanic" */
    HELP_STR_THAT_DISTRESS_SIGNAL_INDICATED_0x5323 = 0x00005323,  /* "That distress signal indicated that Skid Mc Marx ejected from his doomed ship. If he's still alive, it would be probably be worth finding him. Maybe you could get an autograph�" */
    HELP_STR_DESTROY_ALL_OF_THE_0x5324 = 0x00005324,  /* "Destroy all of the sandsharks and sandshark nests in the canyon leading to Skid's ship. You may want to pick up a Pyrocitor for this - those sandsharks are nasty. Don't forget, there's a Hoverboard in it for you." */
    HELP_STR_THAT_CHATTY_GUY_IN_0x5325 = 0x00005325,  /* "That chatty guy in the Infobot must have been Skid's agent. If he landed safely, you should track him down - agents always have useful information." */
    HELP_STR_THE_AGENT_MENTIONED_THAT_0x5326 = 0x00005326,  /* "The agent mentioned that Hoverboard races are being held on Planet Rilgar. If you win the grand prize, you should bring it back to him as proof of your prowess. Perhaps he'll give you something useful in return. Better make sure you have a Hoverboard before you enter the race." */
    HELP_STR_THE_WEST_SIDE_OF_0x5327 = 0x00005327,  /* "The west side of the factory has Swingshot Versa-Targets everywhere. You should explore but you'll need a Swingshot first." */
    HELP_STR_THE_WEST_SIDE_OF_0x5328 = 0x00005328,  /* "The west side of the factory has swingshot targets everywhere.  You'll need that swingshot of yours to explore." */
    HELP_STR_LOCATE_SKID_MCMARX = 0x00005329,  /* "Locate Skid McMarx" */
    HELP_STR_HELP_SKID_GET_TO_0x532A = 0x0000532A,  /* "Help Skid get to his ship" */
    HELP_STR_FIND_SKIDS_AGENT = 0x0000532B,  /* "Find Skid's agent" */
    HELP_STR_BRING_PRIZE_TO_AGENT = 0x0000532C,  /* "Bring prize to agent" */
    HELP_STR_USE_YOUR_SWINGSHOT = 0x0000532D,  /* "Use your Swingshot" */
    HELP_STR_CAPTAIN_QWARK_STARRED_IN_0x532E = 0x0000532E,  /* "Captain Qwark starred in the commercial for Al's Roboshack.  Maybe Al knows where he is." */
    HELP_STR_AL_WILL_SELL_YOU_0x532F = 0x0000532F,  /* "Al will sell you a Heli-Pack upgrade, which should improve Clank's abilities." */
    HELP_STR_IN_A_CITY_THIS_0x5330 = 0x00005330,  /* "In a city this big, there must be something interesting you can find!" */
    HELP_STR_ITS_RUMORED_THAT_CAPTAIN_0x5331 = 0x00005331,  /* "It's rumored that Captain Qwark has sponsored a fitness park on the west side of town. You should look for a Qwark-bot to find out more." */
    HELP_STR_ALS_GOT_A_STORAGE_0x5332 = 0x00005332,  /* "Al's got a storage area behind his shop. Perhaps it leads to another section of the city�" */
    HELP_STR_THE_TRAIN_USED_TO_0x5333 = 0x00005333,  /* "The train used to provide scenic tours of Metropolis but after the Blarg invaded, things changed. It's still worth taking a ride�" */
    HELP_STR_FINISH_CAPTAIN_QWARKS_FITNESS_0x5334 = 0x00005334,  /* "Finish Captain Qwark's fitness challenge and you may get a prize" */
    HELP_STR_THE_TRAINER_IS_DEMANDING_0x5335 = 0x00005335,  /* "The trainer is demanding money for the Swingshot.  Buy it, you're sure to need it later." */
    HELP_STR_VISIT_ALS_ROBOSHACK = 0x00005336,  /* "Visit Al's Roboshack" */
    HELP_STR_BUY_HELI_PACK_FROM_AL = 0x00005337,  /* "Buy Heli-Pack from Al" */
    HELP_STR_EXPLORE_THE_REST_OF_0x5338 = 0x00005338,  /* "Explore the rest of the city" */
    HELP_STR_RIDE_THE_ROBOT_TRAIN = 0x00005339,  /* "Ride the Robot Train" */
    HELP_STR_COMPLETE_FITNESS_COURSE = 0x0000533A,  /* "Complete fitness course" */
    HELP_STR_BUY_SWINGSHOT_FROM_TRAINER = 0x0000533B,  /* "Buy Swingshot from trainer" */
    HELP_STR_TRACK_DOWN_DREKS_RIGHT_HAND_0x533C = 0x0000533C,  /* "Track down Drek's right-hand robot. He's got to have some useful information." */
    HELP_STR_WITH_ALL_OF_THESE_0x533D = 0x0000533D,  /* "With all of these robots running around, there's probably some good hardware available�" */
    HELP_STR_CONFRONT_ROBOT_LIEUTENANT = 0x0000533E,  /* "Confront robot lieutenant" */
    HELP_STR_EXPLORE_THE_MILLS = 0x0000533F,  /* "Explore the mills" */
    HELP_STR_CAPTAIN_QWARK_IS_PRESENTING_0x5340 = 0x00005340,  /* "Captain Qwark is presenting the grand prize for the race. If you win the race, you've got proof that you're a pro!" */
    HELP_STR_SINCE_CAPTAIN_QWARK_IS_0x5341 = 0x00005341,  /* "Since Captain Qwark is here for the races, it would be a good idea to track him down and ask for his help." */
    HELP_STR_THE_BODYGUARD_WONT_LET_0x5342 = 0x00005342,  /* "The bodyguard won't let you in unless you grease his palm with some bolts" */
    HELP_STR_HERE_IT_IS_THE_0x5343 = 0x00005343,  /* "Here it is, the ultimate weapon.  At the ultimate price." */
    HELP_STR_WIN_THE_HOVERBOARD_RACE = 0x00005344,  /* "Win the hoverboard race" */
    HELP_STR_LOCATE_CAPTAIN_QWARK = 0x00005345,  /* "Locate Captain Qwark" */
    HELP_STR_BRIBE_THE_BODYGUARD = 0x00005346,  /* "Bribe the bodyguard" */
    HELP_STR_PURCHASE_THE_RYNO = 0x00005347,  /* "Purchase the RYNO" */
    HELP_STR_THE_INFOBOT_FOR_THIS_0x5348 = 0x00005348,  /* "The Infobot for this station showed a lot of new hardware being created. Perhaps if you look hard enough you'll find some." */
    HELP_STR_THIS_IS_DEFINITELY_A_0x5349 = 0x00005349,  /* "This is definitely a worthwhile purchase. Grindboots are rare but very useful." */
    HELP_STR_THE_BLARG_SHUT_DOWN_0x534A = 0x0000534A,  /* "The Blarg shut down this warship after it was overrun with mutants from the labs.  It's still fairly new so maybe they left something behind." */
    HELP_STR_STRIKE_A_BLOW_AGAINST_0x534B = 0x0000534B,  /* "Strike a blow against Drek and activate the ship's self-destruct sequence." */
    HELP_STR_THERES_NO_AIR_OUTSIDE_0x534C = 0x0000534C,  /* "There's no air outside the space station, so Clank's got to explore by himself." */
    HELP_STR_EXPLORE_THE_SPACE_STATION = 0x0000534D,  /* "Explore the space station" */
    HELP_STR_BUY_GRINDBOOTS = 0x0000534E,  /* "Buy Grindboots" */
    HELP_STR_EXPLORE_THE_BLARG_WARSHIP = 0x0000534F,  /* "Explore the Blarg warship" */
    HELP_STR_DESTROY_THE_WARSHIP = 0x00005350,  /* "Destroy the warship" */
    HELP_STR_JOURNEY_OUTSIDE_THE_AIRLOCK = 0x00005351,  /* "Journey outside the airlock" */
    HELP_STR_QWARK_MAY_HELP_YOU_0x5352 = 0x00005352,  /* "Qwark may help you if you can get to the inner chambers of his fortress." */
    HELP_STR_QWARK_HAS_BETRAYED_YOU_0x5353 = 0x00005353,  /* "Qwark has betrayed you! The only way you're going to be able to track him down is to get past his pet Snagglebeast." */
    HELP_STR_NOW_YOU_NEED_TO_0x5354 = 0x00005354,  /* "Now you need to find a way off of this planet.  Maybe Qwark has an extra ship in the garage attached to this cave�" */
    HELP_STR_SURVIVE_QWARKS_GAUNTLET = 0x00005355,  /* "Survive Qwark's gauntlet" */
    HELP_STR_DESTROY_THE_SNAGGLEBEAST = 0x00005356,  /* "Destroy the Snagglebeast" */
    HELP_STR_FIND_A_NEW_SHIP_2 = 0x00005357,  /* "Find a new ship" */
    HELP_STR_IF_YOU_CAN_BREAK_0x5358 = 0x00005358,  /* "If you can break away from the battles, it would be a good idea to explore the quieter areas of this world." */
    HELP_STR_THESE_TRANSPORT_RAILS_LOOK_0x5359 = 0x00005359,  /* "These transport rails look like a great place to try out a pair of Grindboots." */
    HELP_STR_EVEN_THOUGH_THIS_GUY_0x535A = 0x0000535A,  /* "Even though this guy is a coward, the Infobot he has could be crucial to tracking down Drek." */
    HELP_STR_THE_COMMANDO_FROM_THE_0x535B = 0x0000535B,  /* "The Commando from the Infobot needs your help" */
    HELP_STR_THE_COMMANDO_NEEDS_YOUR_0x535C = 0x0000535C,  /* "The Commando needs your help. Meet him at the platform before the city." */
    HELP_STR_TO_GET_TO_THE_0x535D = 0x0000535D,  /* "To get to the walled city, you'll have to climb the ventilation shaft using a pair of Magneboots" */
    HELP_STR_THESE_GUYS_NEED_SOMEONE_0x535E = 0x0000535E,  /* "These guys need someone with good aim to operate the turret outside the city. Shoot well and you may be able to help stop the invasion. Talk to the Waterworker on the bluff outside of the city." */
    HELP_STR_SCOUT_THE_AREA = 0x0000535F,  /* "Scout the area" */
    HELP_STR_RIDE_THE_GRIND_RAIL = 0x00005360,  /* "Ride the grind rail" */
    HELP_STR_BUY_DESERTERS_INFOBOT = 0x00005361,  /* "Buy Deserter's Infobot" */
    HELP_STR_TALK_TO_THE_COMMANDO = 0x00005362,  /* "Talk to the Commando" */
    HELP_STR_MEET_THE_COMMANDO_AT_0x5363 = 0x00005363,  /* "Meet the Commando at city" */
    HELP_STR_EXPLORE_THE_WALLED_CITY = 0x00005364,  /* "Explore the walled city" */
    HELP_STR_DESTROY_THE_BOMBERS = 0x00005365,  /* "Destroy the bombers" */
    HELP_STR_THAT_TESTING_AREA_YOU_0x5366 = 0x00005366,  /* "That testing area you saw in the Infobot must be somewhere on this base�" */
    HELP_STR_THE_BLARG_WARSHIPS_ARE_0x5367 = 0x00005367,  /* "The Blarg warships are docked for refueling. Take them out any way you can." */
    HELP_STR_FIND_THE_PILOTS_HELMET = 0x00005368,  /* "Find the Pilot's Helmet" */
    HELP_STR_DESTROY_THE_BLARG_FLEET = 0x00005369,  /* "Destroy the Blarg fleet" */
    HELP_STR_CLANK_WILL_HAVE_TO_0x536A = 0x0000536A,  /* "Clank will have to take care of this one. The deserted Blarg laboratories are in the caves and probably contain some useful items." */
    HELP_STR_BEYOND_THE_LABORATORIES_LIES_0x536B = 0x0000536B,  /* "Beyond the laboratories lies a hostile environment where Clank will need his Gadge-Bot buddies to survive." */
    HELP_STR_THERE_ARE_SOME_BLARG_0x536C = 0x0000536C,  /* "There are some Blarg troopers stationed in the factory along with the mutated wildlife. If you can get through the hordes, you could find some useful tech that the Blarg left behind. Ratchet needs the O2 Mask for this." */
    HELP_STR_CATCH_THIS_INFOBOT_BUT_0x536D = 0x0000536D,  /* "Catch this Infobot.  But watch out, it's fast!" */
    HELP_STR_PREMIUM_NANOTECH_WILL_BOOST_0x536E = 0x0000536E,  /* "Premium Nanotech will boost your overall health. It's definitely a worthwhile purchase." */
    HELP_STR_THIS_IS_THE_MOST_0x536F = 0x0000536F,  /* "This is the most powerful Nanotech available. It's expensive but will give you a HUGE permanent health boost." */
    HELP_STR_SEARCH_THE_LABORATORIES = 0x00005370,  /* "Search the laboratories" */
    HELP_STR_TRAVERSE_THE_WILDERNESS = 0x00005371,  /* "Traverse the wilderness" */
    HELP_STR_CATCH_THE_INFOBOT = 0x00005372,  /* "Catch the Infobot" */
    HELP_STR_EXPLORE_AS_RATCHET = 0x00005373,  /* "Explore as Ratchet" */
    HELP_STR_BUY_THE_PREMIUM_NANOTECH = 0x00005374,  /* "Buy the Premium Nanotech" */
    HELP_STR_BUY_THE_ULTRA_NANOTECH = 0x00005375,  /* "Buy the Ultra Nanotech" */
    HELP_STR_LOOKS_LIKE_THE_INFOBOT_0x5376 = 0x00005376,  /* "Looks like the Infobot for this planet was a little misleading. The Blarg ships dumping toxic waste have turned the seas into mutant breeding grounds. Since all of the tourists have been scared away, this would be a good time to do some exploring." */
    HELP_STR_THE_RESORT_OWNER_NEEDS_0x5377 = 0x00005377,  /* "The resort owner needs your help to get to his escape jet. Clear out the enemies along the path." */
    HELP_STR_IF_YOURE_GOING_TO_0x5378 = 0x00005378,  /* "If you're going to open the jet fighter garage, you should stop by Bob's Roboshack. Bob may have something to help you out." */
    HELP_STR_NOW_THAT_YOUVE_GOT_0x5379 = 0x00005379,  /* "Now that you've got the Thruster-Pack, you can open the Jet Plane garage and blow those Blarg out of the sky! And don't forget, if you succeed, you'll get an O2 Mask!" */
    HELP_STR_WELCOME_TO_THE_JOWAI_0x537A = 0x0000537A,  /* "Welcome to the Jowai Resort sewer system!  It's certainly one of the cleaner systems on this planet. Maybe there's something down here that Ratchet can use." */
    HELP_STR_THE_INVENTOR_NEEDS_SOME_0x537B = 0x0000537B,  /* "The Inventor needs some Raritanium.  Maybe you can find some on another world." */
    HELP_STR_CHECK_OUT_THE_RESORT = 0x0000537C,  /* "Check out the resort" */
    HELP_STR_HELP_THE_RESORT_OWNER = 0x0000537D,  /* "Help the resort owner" */
    HELP_STR_BUY_THRUSTERPACK_FROM_BOB = 0x0000537E,  /* "Buy Thrusterpack from Bob" */
    HELP_STR_DESTROY_THE_BLARG_SHIPS = 0x0000537F,  /* "Destroy the Blarg ships" */
    HELP_STR_NAVIGATE_THE_SEWERS = 0x00005380,  /* "Navigate the sewers" */
    HELP_STR_BRING_RARITANIUM_TO_INVENTOR = 0x00005381,  /* "Bring Raritanium to Inventor" */
    HELP_STR_DREKS_PLANETBUSTER_BOMB_IS_0x5382 = 0x00005382,  /* "Drek's planetbuster bomb is about to be lifted off-planet. You've got to stop it or some unfortunate planet's gonna be blown to bits." */
    HELP_STR_BEFORE_DREKS_COMMANDOS_ARRIVED_0x5383 = 0x00005383,  /* "Before Drek's commandos arrived, the factories in this level were well-known for refining Raritanium. There must still be plenty of high-tech equipment around worth finding�" */
    HELP_STR_WITH_THIS_HYDRO_PACK_RATCHET_0x5384 = 0x00005384,  /* "With this Hydro-Pack, Ratchet can travel more quickly underwater.  Get it, you'll need it." */
    HELP_STR_DESTROY_THE_PLANETBUSTER = 0x00005385,  /* "Destroy the Planetbuster" */
    HELP_STR_EXPLORE_THE_ICY_WASTES = 0x00005386,  /* "Explore the Icy Wastes" */
    HELP_STR_BUY_HYDRO_PACK_FROM_ED = 0x00005387,  /* "Buy Hydro-Pack from Ed" */
    HELP_STR_EVEN_THOUGH_YOU_MISSED_0x5388 = 0x00005388,  /* "Even though you missed Drek, this base may have a ship fast enough to catch up with him. You should look around." */
    HELP_STR_THIS_IS_YOUR_BIG_0x5389 = 0x00005389,  /* "This is your big chance to exact revenge for what Qwark did to you. Find a ship and shoot him down!" */
    HELP_STR_EXPLORE_BASE = 0x0000538A,  /* "Explore base" */
    HELP_STR_SHOOT_DOWN_CAPTAIN_QWARK = 0x0000538B,  /* "Shoot down Captain Qwark" */
    HELP_STR_EVEN_THOUGH_MOST_OF_0x538C = 0x0000538C,  /* "Even though most of the city's residents have fled the Blarg attack on the planet, there are probably a few still left. They might have some information to help you stop Drek." */
    HELP_STR_THIS_INFOBOT_MAY_CONTAIN_0x538D = 0x0000538D,  /* "This Infobot may contain valuable information to help you stop Drek. And at half-price, how could you pass it up?" */
    HELP_STR_IT_WOULD_BE_WORTHWHILE_0x538E = 0x0000538E,  /* "It would be worthwhile to take a look around here. There may be some useful equipment left behind in the remains of the city." */
    HELP_STR_THE_GADGETRON_PDA_WILL_0x538F = 0x0000538F,  /* "The Gadgetron PDA will let you purchase ammunition at any time. This would definitely be a big help when away from a Gadgetron vendor." */
    HELP_STR_FIND_SURVIVORS_OF_THE_0x5390 = 0x00005390,  /* "Find survivors of the Blarg attack" */
    HELP_STR_BUY_INFOBOT_FROM_SCRAP_0x5391 = 0x00005391,  /* "Buy Infobot from scrap merchant" */
    HELP_STR_SEARCH_THE_DESTROYED_CITY = 0x00005392,  /* "Search the destroyed city" */
    HELP_STR_PURCHASE_GADGETRON_PDA_FROM_0x5393 = 0x00005393,  /* "Purchase Gadgetron PDA from 'Steve'" */
    HELP_STR_THE_ULTRA_MECH_LOOKS_LIKE_0x5394 = 0x00005394,  /* "The Ultra-Mech looks like a powerful piece of weaponry. There must be someone around who knows more about it." */
    HELP_STR_DESTROYING_THESE_ULTRA_MECHS_WOULD_0x5395 = 0x00005395,  /* "Destroying these Ultra-Mechs would throw a wrench into Drek's plans. They're too big for Ratchet, but Giant Clank could take them out." */
    HELP_STR_GIANT_CLANK_WONT_BE_0x5396 = 0x00005396,  /* "Giant Clank won't be able to make it across that gap. The engineer should be able to return Clank to his original size." */
    HELP_STR_THE_FACTORYS_COOLANT_SYSTEMS_0x5397 = 0x00005397,  /* "The factory's coolant systems are the very latest in Blarg technology. It would be a good idea to look around and see if they've left anything interesting in there." */
    HELP_STR_CLANK_ESCAPED_FROM_THE_0x5398 = 0x00005398,  /* "Clank escaped from the secure inner areas of this factory! If you could somehow sneak in, you could find out more information about Drek's whereabouts." */
    HELP_STR_IF_YOU_CAN_GET_0x5399 = 0x00005399,  /* "If you can get past the robot patrols, you might find some decent loot." */
    HELP_STR_IF_THE_BLARG_ARE_0x539A = 0x0000539A,  /* "If the Blarg are taking pre-orders for their Ultra-Mechs, you can bet they've got plenty of bolts stashed in this vault. You'll need a Codebot to deactivate the lock." */
    HELP_STR_FIND_OUT_MORE_ABOUT_0x539B = 0x0000539B,  /* "Find out more about the Ultra-Mech" */
    HELP_STR_DESTROY_THE_ULTRA_MECHS = 0x0000539C,  /* "Destroy the Ultra-Mechs" */
    HELP_STR_RETURN_TO_THE_ENGINEER = 0x0000539D,  /* "Return to the engineer" */
    HELP_STR_EXPLORE_THE_COOLANT_SYSTEM = 0x0000539E,  /* "Explore the coolant system" */
    HELP_STR_INFILTRATE_THE_SECURE_AREA = 0x0000539F,  /* "Infiltrate the secure area" */
    HELP_STR_EXPLORE_THE_FACTORY = 0x000053A0,  /* "Explore the factory" */
    HELP_STR_OPEN_THE_VAULT = 0x000053A1,  /* "Open the vault" */
    HELP_STR_THERES_GOT_TO_BE_0x53A2 = 0x000053A2,  /* "There's got to be all sorts of great equipment at Gadgetron Headquarters. That Hologuise you saw in the Infobot movie could be really useful. Someone at Gadgetron Headquarters must have one�" */
    HELP_STR_THERES_GOT_TO_BE_0x53A3 = 0x000053A3,  /* "There's got to be all sorts of great equipment at Gadgetron Headquarters. Now that you've got the Hologuise maybe there are other new Gadgetron items here." */
    HELP_STR_DREK_HAS_SENT_HIS_0x53A4 = 0x000053A4,  /* "Drek has sent his commandos after you. They've triggered the Gadgetron automated defenses and things have gone haywire. Find someone in charge to warn about the Blarg!" */
    HELP_STR_WIN_THE_HOVERBOARD_RACE_0x53A5 = 0x000053A5,  /* "Win the Hoverboard race and Ratchet could be Gadgetron's newest star. You might even get some Gadgetron equipment as a bonus." */
    HELP_STR_YOU_CAN_USE_YOUR_0x53A6 = 0x000053A6,  /* "You can use your Grind Boots to speed along Gadgetron's transportation system. But watch out for moving cars!" */
    HELP_STR_FIND_NEW_EQUIPMENT = 0x000053A7,  /* "Find new equipment" */
    HELP_STR_GET_PAST_THE_BLARG = 0x000053A8,  /* "Get past the Blarg" */
    HELP_STR_WIN_THE_HOVERBOARD_RACE_2 = 0x000053A9,  /* "Win the Hoverboard race" */
    HELP_STR_RIDE_THE_GRIND_RAIL_2 = 0x000053AA,  /* "Ride the Grind Rail" */
    HELP_STR_THE_LOCATION_OF_THE_0x53AB = 0x000053AB,  /* "The location of the laser to destroy Ratchet's planet should be listed somewhere on Drek's ship. Get to the command ship and find out where it is so you can stop him in time." */
    HELP_STR_THIS_HUGE_TANKER_IS_0x53AC = 0x000053AC,  /* "This huge tanker is hauling water for Drek's new planet. There may be interesting technology inside, but you'll need to use your Hydro-Pack to get through something this big." */
    HELP_STR_FIND_THE_COORDINATES_FOR_0x53AD = 0x000053AD,  /* "Find the coordinates for Drek's laser" */
    HELP_STR_SWIM_THROUGH_THE_WATER_0x53AE = 0x000053AE,  /* "Swim through the water tanker" */
    HELP_STR_DREKS_LASER_IS_SET_0x53AF = 0x000053AF,  /* "Drek's laser is set up to destroy Ratchet's home planet! Destroy the laser and foil Drek's plans." */
    HELP_STR_SAVE_RATCHETS_PLANET = 0x000053B0,  /* "Save Ratchet's planet" */
    HELP_STR_THAT_SHIP_LOOKED_LIKE_0x53B1 = 0x000053B1,  /* "That ship looked like it crashed near here! Find the site where it landed, and perhaps you can learn more about what happened." */
    HELP_STR_INVESTIGATE_CRASH_SITE = 0x000053B2,  /* "Investigate crash site" */
    HELP_STR_BUY_INFOBOT_FOR_500_0x4EA0 = 0x00004EA0,  /* "Buy Infobot for 500 bolts" */
    HELP_STR_ELIMINATE_SANDSHARKS_FOR_HOVERBOARD = 0x00004EA1,  /* "Eliminate sandsharks for Hoverboard" */
    HELP_STR_TALK_TO_AGENT_AFTER_0x4EA2 = 0x00004EA2,  /* "Talk to agent after winning race" */
    HELP_STR_BUY_HELI_PACK_FOR_1000_0x4EA3 = 0x00004EA3,  /* "Buy Heli-Pack for 1,000 bolts" */
    HELP_STR_BUY_SWINGSHOT_FOR_1000_0x4EA4 = 0x00004EA4,  /* "Buy Swingshot for 1,000 bolts" */
    HELP_STR_RACE_FOR_ZOOMERATOR = 0x00004EA5,  /* "Race for Zoomerator" */
    HELP_STR_BRIBE_BODYGUARD_WITH_4000_0x4EA6 = 0x00004EA6,  /* "Bribe Bodyguard with 4,000 bolts" */
    HELP_STR_BUY_RYNO_FOR_150000_0x4EA7 = 0x00004EA7,  /* "Buy R.Y.N.O. for 150,000 bolts" */
    HELP_STR_BUY_GRINDBOOTS_FOR_2000_0x4EA8 = 0x00004EA8,  /* "Buy Grindboots for 2,000 bolts" */
    HELP_STR_DESTROY_THE_WARSHIP_2 = 0x00004EA9,  /* "Destroy the warship" */
    HELP_STR_EXTERMINATE_THE_SNAGGLEBEAST = 0x00004EAA,  /* "Exterminate the Snagglebeast" */
    HELP_STR_BUY_INFOBOT_FOR_2000_0x4EAB = 0x00004EAB,  /* "Buy Infobot for 2,000 bolts" */
    HELP_STR_DESTROY_THE_BOMBERS_2 = 0x00004EAC,  /* "Destroy the bombers" */
    HELP_STR_BUY_PREMIUM_NANOTECH_FOR_0x4EAD = 0x00004EAD,  /* "Buy Premium Nanotech for 4,000 bolts" */
    HELP_STR_BUY_ULTRA_NANOTECH_FOR_0x4EAE = 0x00004EAE,  /* "Buy Ultra Nanotech for 30,000 bolts" */
    HELP_STR_HELP_OWNER_FOR_O2_0x4EAF = 0x00004EAF,  /* "Help owner for O2 mask" */
    HELP_STR_DESTROY_BLARG_SHIPS_FOR_0x4EB0 = 0x00004EB0,  /* "Destroy Blarg ships for O2 Mask" */
    HELP_STR_BUY_THRUSTER_PACK_FOR_2000_0x4EB1 = 0x00004EB1,  /* "Buy Thruster-Pack for 2,000 bolts" */
    HELP_STR_TRADE_RARITANIUM_FOR_PERSUADER = 0x00004EB2,  /* "Trade Raritanium for Persuader" */
    HELP_STR_BUY_HYDRO_PACK_FOR_2000_0x4EB3 = 0x00004EB3,  /* "Buy Hydro-Pack for 2,000 bolts" */
    HELP_STR_BUY_INFOBOT_FOR_2000_0x4EB4 = 0x00004EB4,  /* "Buy Infobot for 2,000 bolts" */
    HELP_STR_BUY_GADGETRON_PDA_FOR_0x4EB5 = 0x00004EB5,  /* "Buy Gadgetron PDA for 1,000 bolts" */
    HELP_STR_DESTROY_THE_ULTRA_MECHS_2 = 0x00004EB6,  /* "Destroy the Ultra-Mechs" */
    HELP_STR_USE_CODEBOT_TO_OPEN_0x4EB7 = 0x00004EB7,  /* "Use Codebot to open vault" */
    HELP_STR_RACE_FOR_HOLOGUISE = 0x00004EB8,  /* "Race for Hologuise" */
    HELP_STR_KYZIL_PLATEAU = 0x00004EB9,  /* "Kyzil Plateau" */
    HELP_STR_TOBRUK_CRATER = 0x00004EBA,  /* "Tobruk Crater" */
    HELP_STR_OUTPOST_X11 = 0x00004EBB,  /* "Outpost X11" */
    HELP_STR_METROPOLIS = 0x00004EBC,  /* "Metropolis" */
    HELP_STR_LOGGING_SITE = 0x00004EBD,  /* "Logging Site" */
    HELP_STR_BLACKWATER_CITY = 0x00004EBE,  /* "Blackwater City" */
    HELP_STR_BLARG_STATION = 0x00004EBF,  /* "Blarg Station" */
    HELP_STR_QWARKS_HQ = 0x00004EC0,  /* "Qwark's HQ" */
    HELP_STR_FORT_KRONTOS = 0x00004EC1,  /* "Fort Krontos" */
    HELP_STR_BLARG_DEPOT = 0x00004EC2,  /* "Blarg Depot" */
    HELP_STR_KOGOR_REFINERY = 0x00004EC3,  /* "Kogor Refinery" */
    HELP_STR_JOWAI_RESORT = 0x00004EC4,  /* "Jowai Resort" */
    HELP_STR_BOMB_FACTORY = 0x00004EC5,  /* "Bomb Factory" */
    HELP_STR_GEMLIK_BASE = 0x00004EC6,  /* "Gemlik Base" */
    HELP_STR_GORDA_CITY_RUINS = 0x00004EC7,  /* "Gorda City Ruins" */
    HELP_STR_ROBOT_PLANT = 0x00004EC8,  /* "Robot Plant" */
    HELP_STR_GADGETRON_SITE = 0x00004EC9,  /* "Gadgetron Site" */
    HELP_STR_DREKS_FLEET = 0x00004ECA,  /* "Drek's Fleet" */
    HELP_STR_KYZIL_PLATEAU_2 = 0x00004ECB,  /* "Kyzil Plateau" */
    HELP_STR_PLANET = 0x00004ECC,  /* "Planet" */
    HELP_STR_NOVALIS = 0x00004ECD,  /* "Novalis" */
    HELP_STR_ARIDIA = 0x00004ECE,  /* "Aridia" */
    HELP_STR_KERWAN = 0x00004ECF,  /* "Kerwan" */
    HELP_STR_EUDORA = 0x00004ED0,  /* "Eudora" */
    HELP_STR_RILGAR = 0x00004ED1,  /* "Rilgar" */
    HELP_STR_NEBULA_G34 = 0x00004ED2,  /* "Nebula G34" */
    HELP_STR_UMBRIS = 0x00004ED3,  /* "Umbris" */
    HELP_STR_BATALIA = 0x00004ED4,  /* "Batalia" */
    HELP_STR_GASPAR = 0x00004ED5,  /* "Gaspar" */
    HELP_STR_ORXON = 0x00004ED6,  /* "Orxon" */
    HELP_STR_POKITARU = 0x00004ED7,  /* "Pokitaru" */
    HELP_STR_HOVEN = 0x00004ED8,  /* "Hoven" */
    HELP_STR_OLTANIS_ORBIT = 0x00004ED9,  /* "Oltanis Orbit" */
    HELP_STR_OLTANIS = 0x00004EDA,  /* "Oltanis" */
    HELP_STR_QUARTU = 0x00004EDB,  /* "Quartu" */
    HELP_STR_KALEBO_III = 0x00004EDC,  /* "Kalebo III" */
    HELP_STR_VELDIN_ORBIT = 0x00004EDD,  /* "Veldin Orbit" */
    HELP_STR_VELDIN = 0x00004EDE,  /* "Veldin" */
    HELP_STR_TOGGLE = 0x00004EDF,  /* " Toggle" */
    HELP_STR_EXIT = 0x00004EE0,  /* " Exit" */
    HELP_STR_SKILL_POINTS_2 = 0x00004EE1,  /* "Skill Points" */
    HELP_STR_WEAPONS = 0x00004EE2,  /* "Weapons" */
    HELP_STR_GADGETS = 0x00004EE3,  /* "Gadgets" */
    HELP_STR_QUICK_SELECT = 0x00004EE4,  /* "Quick Select" */
    HELP_STR_ITEMS = 0x00004EE5,  /* "Items" */
    HELP_STR_HELP = 0x00004EE6,  /* "Help" */
    HELP_STR_OPTIONS = 0x00004EE7,  /* "Options" */
    HELP_STR_HAND_ITEMS = 0x00004EE8,  /* "Hand Items" */
    HELP_STR_BACK_PACKS = 0x00004EE9,  /* "Back Packs" */
    HELP_STR_HEAD_ITEMS = 0x00004EEA,  /* "Head Items" */
    HELP_STR_FOOT_ITEMS = 0x00004EEB,  /* "Foot Items" */
    HELP_STR_EQUIP = 0x00004EEC,  /* " Equip" */
    HELP_STR_PRESS__FOR_HELP = 0x00004EED,  /* "Press  for help" */
    HELP_STR_VIEW_MISSIONS = 0x00004EEE,  /* " View Missions" */
    HELP_STR_PLAY_INFOBOT = 0x00004EEF,  /* " Play Infobot" */
    HELP_STR_GALACTIC_MAP = 0x00004EF0,  /* "Galactic Map" */
    HELP_STR_CONTROLS = 0x00004EF1,  /* "Controls" */
    HELP_STR_MOVES = 0x00004EF2,  /* "Moves" */
    HELP_STR_PURCHASING = 0x00004EF3,  /* "Purchasing" */
    HELP_STR_SWITCHES = 0x00004EF4,  /* "Switches" */
    HELP_STR_MAP = 0x00004EF5,  /* "Map" */
    HELP_STR_ENEMIES = 0x00004EF6,  /* "Enemies" */
    HELP_STR_HINTS = 0x00004EF7,  /* "Hints" */
    HELP_STR_PLANETS = 0x00004EF8,  /* "Planets" */
    HELP_STR_GADGETRN_MAINTAINS_DETAILED_RECORDS_0x4EF9 = 0x00004EF9,  /* "Gadgetr�n maintains detailed records of all inhabited worlds.  To consult our database, select this option." */
    HELP_STR_PREVIOUS_MAP = 0x00004EFA,  /* " Previous Map" */
    HELP_STR_NEXT_MAP = 0x00004EFB,  /* " Next Map" */
    HELP_STR_TRACK_ZOOM = 0x00004EFC,  /* "  Track/Zoom" */
    HELP_STR_WE_AT_GADGETRON_ARE_0x4EFD = 0x00004EFD,  /* "We at Gadgetron are here to help you. Selecting this option will show you which buttons do what. " */
    HELP_STR_YOUVE_GOT_AN_EXTENSIVE_0x4EFE = 0x00004EFE,  /* "You've got an extensive array of acrobatic moves.  Find out how to do things like wall jump, swim, and throw your wrench." */
    HELP_STR_GOT_A_QUESTION_ABOUT_0x4EFF = 0x00004EFF,  /* "Got a question about a weapon? Gadgetron's got answers. Look here to learn about weapons operation and strategies." */
    HELP_STR_WEVE_GOT_INFORMATION_ON_0x4F00 = 0x00004F00,  /* "We've got information on all Gadgetron and non-Gadgetron devices. We can help you learn more about your equipment's capabilities!" */
    HELP_STR_IF_YOU_WANT_MORE_0x4F01 = 0x00004F01,  /* "If you want more information about Bolt-Cranks, Frequency-Jammers and other special switches, choose this menu item." */
    HELP_STR_GADGETRONS_PATENTED_QUICKSELECT_SYSTEM_0x4F02 = 0x00004F02,  /* "Gadgetron's patented QuickSelect System makes equipping your gadgets and weapons a breeze. Let us show you how use it!" */
    HELP_STR_GADGETRON_KEEPS_A_RECORD_0x4F03 = 0x00004F03,  /* "Gadgetron keeps a record of all enemies you've encountered in your travels. If you want to find out more about any enemy you've fought, select this option." */
    HELP_STR_STILL_STUCK_TRY_OUR_0x4F04 = 0x00004F04,  /* "Still stuck? Try our special hints section for some choice words of advice." */
    HELP_STR_SELECT = 0x00004F05,  /* " Select" */
    HELP_STR_WALL_JUMP = 0x00004F06,  /* "Wall jump" */
    HELP_STR_CROUCH_TURN = 0x00004F07,  /* "Crouch turn" */
    HELP_STR_SWIM = 0x00004F08,  /* "Swim" */
    HELP_STR_SIDE_FLIP = 0x00004F09,  /* "Side flip" */
    HELP_STR_BACK_FLIP = 0x00004F0A,  /* "Back flip" */
    HELP_STR_LEDGE_GRAB = 0x00004F0B,  /* "Ledge grab" */
    HELP_STR_LEDGE_TRAVERSAL = 0x00004F0C,  /* "Ledge traversal" */
    HELP_STR_YOUR_OMNIWRENCH_8000_HAS_0x4F0D = 0x00004F0D,  /* "Your OmniWrench 8000 has a fast combo attack performed by simply pressing  three times in succession." */
    HELP_STR_THE_HYPER_STRIKE_DOES_MORE_0x4F0E = 0x00004F0E,  /* "The Hyper-Strike does more damage than your regular wrench attack. Jump with  and then hit  for a powerful downward strike." */
    HELP_STR_THE_COMET_STRIKE_IS_ONE_0x4F0F = 0x00004F0F,  /* "The Comet-Strike is one of the more useful features of the OmniWrench 8000. Crouch with  and then hit . You can also pick up distant bolts with this move!" */
    HELP_STR_LOOK_FOR_JUMP_SLOTS_0x4F10 = 0x00004F10,  /* "Look for 'jump slots' with textures like the picture above.  Jump toward one wall using  and then hit  again just as you hit the wall.  Jump back and forth between the walls to get to the top of the slot." */
    HELP_STR_CROUCH_WITH__AND_0x4F11 = 0x00004F11,  /* "Crouch with  and use  to turn in place. Using this technique, you can turn in place and fire weapons." */
    HELP_STR_WHEN_YOURE_IN_WATER_0x4F12 = 0x00004F12,  /* "When you're in water, press  to dive and  to rise. Push  harder to rise more quickly. Watch your air gauge! If the bubbles run out, you'll drown." */
    HELP_STR_TRY_A_SIDE_FLIP_0x4F13 = 0x00004F13,  /* "Try a side flip! Hold  to crouch and snap  right or left while pressing . Go for style by firing your weapons while flipping!" */
    HELP_STR_THIS_MOVE_IS_EFFECTIVE_0x4F14 = 0x00004F14,  /* "This move is effective when backing away from enemies. Hold  to crouch and snap  back while pressing . Try lobbing bombs while doing back flips!" */
    HELP_STR_RATCHET_WILL_AUTOMATICALLY_GRAB_0x4F15 = 0x00004F15,  /* "Ratchet will automatically grab ledges if you jump up to them.  To pull yourself up, hit .  To drop down hit  or ." */
    HELP_STR_WHEN_HANGING_FROM_A_0x4F16 = 0x00004F16,  /* "When hanging from a ledge you can traverse it by moving  left or right." */
    HELP_STR_NOW_THAT_YOU_HAVE_0x4F17 = 0x00004F17,  /* "Now that you have the Gagdetron Heli-Pack upgrade, you can use its Glide feature! Jump using  then hit  again to glide. You can also perform the Glide with the Thruster-Pack." */
    HELP_STR_TO_DO_A_STRETCH_0x4F18 = 0x00004F18,  /* "To do a Stretch Jump, get a running start then press and hold  and  together. For maximum distance when jumping across gaps, jump from the very edge of the gap." */
    HELP_STR_THE_BOOST_JUMP_IS_0x4F19 = 0x00004F19,  /* "The Boost Jump is another helpful feature included in your Heli-Pack and Thruster-Pack upgrades. Hold  to crouch and press  to jump. You can do a Glide out of a Boost Jump by pressing  again." */
    HELP_STR_TO_DO_A_GLIDE_0x4F1A = 0x00004F1A,  /* "To do a Glide, you first have to acquire a special upgrade for Clank." */
    HELP_STR_TO_DO_A_STRETCH_0x4F1B = 0x00004F1B,  /* "To do a Stretch Jump, you first have to acquire a special upgrade for Clank." */
    HELP_STR_TO_DO_A_BOOST_0x4F1C = 0x00004F1C,  /* "To do a Boost Jump, you first have to acquire a special upgrade for Clank." */
    HELP_STR_OPTIONS_2 = 0x00004F1D,  /* "Options" */
    HELP_STR_HELPDESK_2 = 0x00004F1E,  /* "HelpDesk" */
    HELP_STR_SAVE = 0x00004F1F,  /* "Save" */
    HELP_STR_LOAD = 0x00004F20,  /* "Load" */
    HELP_STR_VIDEO = 0x00004F21,  /* "Video" */
    HELP_STR_SOUND = 0x00004F22,  /* "Sound" */
    HELP_STR_CAMERA = 0x00004F23,  /* "Camera" */
    HELP_STR_SUBTITLES = 0x00004F24,  /* "Subtitles" */
    HELP_STR_VIBRATION = 0x00004F25,  /* "Vibration" */
    HELP_STR_QUIT_GAME = 0x00004F26,  /* "Quit Game" */
    HELP_STR_SELECT_FILE = 0x00004F27,  /* " Select file" */
    HELP_STR_LOAD_GAME = 0x00004F28,  /* "Load Game" */
    HELP_STR_SAVE_GAME = 0x00004F29,  /* "Save Game" */
    HELP_STR_NEW_GAME = 0x00004F2A,  /* "New Game" */
    HELP_STR_LANGUAGE = 0x00004F2B,  /* "Language" */
    HELP_STR_ENGLISH = 0x00004F2C,  /* "English" */
    HELP_STR_FRENCH = 0x00004F2D,  /* "French" */
    HELP_STR_SPANISH = 0x00004F2E,  /* "Spanish" */
    HELP_STR_GERMAN = 0x00004F2F,  /* "German" */
    HELP_STR_ITALIAN = 0x00004F30,  /* "Italian" */
    HELP_STR_TOGGLE_HELPDESK_MESSAGES_ON_0x4F31 = 0x00004F31,  /* "Toggle HelpDesk messages on and off" */
    HELP_STR_SAVE_YOUR_PROGRESS = 0x00004F32,  /* "Save your progress" */
    HELP_STR_LOAD_A_SAVED_GAME = 0x00004F33,  /* "Load a saved game" */
    HELP_STR_ADJUST_VIDEO_SETTINGS = 0x00004F34,  /* "Adjust video settings" */
    HELP_STR_ADJUST_SOUND_SETTINGS = 0x00004F35,  /* "Adjust sound settings" */
    HELP_STR_ADJUST_CAMERA_CONTROL_SETTINGS = 0x00004F36,  /* "Adjust camera control settings" */
    HELP_STR_TOGGLE_SUBTITLES_ON_AND_0x4F37 = 0x00004F37,  /* "Toggle subtitles on and off" */
    HELP_STR_TOGGLE_CONTROLLER_VIBRATION_ON_0x4F38 = 0x00004F38,  /* "Toggle controller vibration on and off" */
    HELP_STR_QUIT_YOUR_CURRENT_GAME_0x4F39 = 0x00004F39,  /* "Quit your current game and return to starting menu" */
    HELP_STR_VIDEO_OPTIONS = 0x00004F3A,  /* "Video Options" */
    HELP_STR_VIDEO_MODE_50HZ_OR_0x4F3B = 0x00004F3B,  /* "Video mode (50Hz or 60Hz)" */
    HELP_STR_HZ = 0x00004F3C,  /* "50Hz" */
    HELP_STR_HZ_2 = 0x00004F3D,  /* "60Hz" */
    HELP_STR_SPECIAL = 0x00004F3E,  /* "Special" */
    HELP_STR_QUIT_GAME_2 = 0x00004F3F,  /* "Quit Game?" */
    HELP_STR_HELPDESK_OPTIONS = 0x00004F40,  /* "HelpDesk Options" */
    HELP_STR_RESTART_LEVEL = 0x00004F41,  /* "Restart level?" */
    HELP_STR_CAMERA_OPTIONS = 0x00004F42,  /* "Camera Options" */
    HELP_STR_SOUND_OPTIONS = 0x00004F43,  /* "Sound Options" */
    HELP_STR_YOURE_LOOKING_AT_A_0x4F44 = 0x00004F44,  /* "You're looking at a Z3000 Deluxe Hoverboard manufactured by Gadgetron. You can use it in races held throughout the galaxy. The hoverboard automatically equips as soon as you step onto an Official Gadgetron HoverTrack. When racing, use  to jump. You can perform tricks by jumping and pressing combinations of , ,  and . Try using  to spin while in the air as well. Find a Zoomerator and convert those tricks to turbo!" */
    HELP_STR_THE_PERSUADER_IS_A_0x4F45 = 0x00004F45,  /* "The Persuader is a black market device outlawed on most planets and for good reason. It uses illegal technology to warp minds. We at Gadgetron do not support this device since our Vendors are vulnerable to its power. Once you find this device, it is equipped permanently. The Persuader is powered by Raritanium." */
    HELP_STR_THE_BOLT_GRABBER_IS_0x4F46 = 0x00004F46,  /* "The Bolt Grabber is one of Gadgetron's most popular gadgets. Once you own one, it is permanently attached and will attract bolts over much greater distances." */
    HELP_STR_DEVELOPED_BY_THE_BLARG_0x4F47 = 0x00004F47,  /* "Developed by the Blarg scientists, Premium Nanotech increases your maximum health by one nanotech sphere." */
    HELP_STR_ULTRA_NANOTECH_REPRESENTS_THE_0x4F48 = 0x00004F48,  /* "Ultra Nanotech represents the pinnacle of Blarg engineering. This incredible boost increases your maximum health by three nanotech spheres." */
    HELP_STR_THE_MAP_O_MATIC_IS_A_0x4F49 = 0x00004F49,  /* "The Map-o-matic is a result of Gadgetron's ongoing efforts to map every square inch of the entire galaxy. By simply possessing it, you can see areas on your map which were previously uncharted." */
    HELP_STR_THE_ZOOMERATOR_IS_AN_0x4F4A = 0x00004F4A,  /* "The Zoomerator is an attachment for the Gadgetron Z3000 Deluxe Hoverboard which, through special quantum technology, converts tricks into turbo boost. Possessing the Zoomerator is crucial to winning some of the more difficult hoverboard races held in this galaxy. And if you need to convince anyone of your racing prowess, just show 'em the Zoomerator." */
    HELP_STR_AS_ITS_NAME_IMPLIES_0x4F4B = 0x00004F4B,  /* "As its name implies, Raritanium is... rare. It's used by the Blarg for manufacturing ultra-destructive devices and can also be found in some black market devices. Gadgetron does not support such devices." */
    HELP_STR_GADGETRON_CODEBOTS_ARE_NECESSARY_0x4F4C = 0x00004F4C,  /* "Gadgetron CodeBots are necessary for opening Invinco- Vaults. There is always one CodeBot for each vault and therefore a CodeBot can only be used once." */
    HELP_STR_USES_NO_AMMO = 0x00004F4D,  /* "Uses no ammo" */
    HELP_STR_GOLD_BOLTS_2 = 0x00004F4E,  /* "Gold Bolts" */
    HELP_STR_FOUND = 0x00004F4F,  /* "Found:" */
    HELP_STR_USED = 0x00004F50,  /* "Used:" */
    HELP_STR_REMAIN = 0x00004F51,  /* "Remain:" */
    HELP_STR_NO_AMMO = 0x00004F52,  /* "(no ammo)" */
    HELP_STR_OF = 0x00004F53,  /* "of" */
    HELP_STR_0x4F54 = 0x00004F54,  /* "????" */
    HELP_STR_TO_VIEW_OTHER_0x4F55 = 0x00004F55,  /* "/ to view other planets" */
    HELP_STR_ZOOMS = 0x00004F56,  /* " zooms" */
    HELP_STR_TRACKS = 0x00004F57,  /* " tracks" */
    HELP_STR_TO_VIEW_MISSIONS = 0x00004F58,  /* " to view missions" */
    HELP_STR_MISSIONS = 0x00004F59,  /* "Missions" */
    HELP_STR_ON = 0x00004F5A,  /* "on" */
    HELP_STR_OFF = 0x00004F5B,  /* "off" */
    HELP_STR_CANCEL = 0x00004F5C,  /* "cancel" */
    HELP_STR_AMMO = 0x00004F5D,  /* "Ammo" */
    HELP_STR_HELP_MENU = 0x00004F5E,  /* "Help Menu" */
    HELP_STR_THANK_YOU = 0x00004F5F,  /* "THANK YOU" */
    HELP_STR_YOU_CANT_AFFORD_THAT = 0x00004F60,  /* "You can't afford that" */
    HELP_STR_HEY_YOU_YEAH_YOU_0x4F61 = 0x00004F61,  /* "HEY YOU!  YEAH, YOU WITH THE ROBOT STRAPPED TO YOUR BACK!  COME OVER HERE AND LOOK AT ALL THIS COOL STUFF I'VE GOT FOR SALE." */
    HELP_STR_VISIT_GADGETRON_VIEW_THE_0x4F62 = 0x00004F62,  /* "VISIT GADGETRON!  VIEW THE LATEST IN ENEMY-SMITING TECHNOLOGY!" */
    HELP_STR_STOP_BY_ONE_OF_0x4F63 = 0x00004F63,  /* "STOP BY ONE OF OUR SHOWROOMS TODAY FOR A TEST-DRIVE!" */
    HELP_STR_EAT_AT_JOES = 0x00004F64,  /* "EAT AT JOE'S                         " */
    HELP_STR_GADGETRON_IS_YOUR_ONE_STOP_0x4F65 = 0x00004F65,  /* "GADGETRON IS YOUR ONE-STOP SHOP FOR ALL YOUR GADGET AND AMMUNITION NEEDS." */
    HELP_STR_GADGETRON_HAS_SHOWROOMS_CONVENIENTLY_0x4F66 = 0x00004F66,  /* "GADGETRON HAS SHOWROOMS CONVENIENTLY LOCATED ON ALL INHABITED WORLDS, AND ALSO IN THE ENTIRELY UNINHABITED BOGS OF TRACHEA FIVE.  WE DON'T REALLY KNOW HOW THAT ONE GOT THERE.  ENGINEERING BLAMES MARKETING, MARKETING BLAMES LEGAL, AND LEGAL HAS BEEN AT A ''CONFERENCE'' ON THE TROPICAL PLANET OF BAHAMIA FOR THE LAST SIX MONTHS AND THEY DON'T RETURN OUR CALLS." */
    HELP_STR_VISIT_OUR_HEADQUARTERS_ON_0x4F67 = 0x00004F67,  /* "VISIT OUR HEADQUARTERS ON KALEBO III!  MARVEL AT THE EFFICIENCY OF OUR SECURITY BOTS!  ADMIRE THE LUSH SCENERY!  EVADE THE MOBS OF RAMPAGING CLEANERBOTS!" */
    HELP_STR_CHECK_OUT_OUR_ALL_NEW_0x4F68 = 0x00004F68,  /* "CHECK OUT OUR ALL-NEW LINE OF MEDIUM- AND LONG-RANGE GADGETS!" */
    HELP_STR_HELP_IM_STUCK_IN_0x4F69 = 0x00004F69,  /* "HELP!  I'M STUCK IN THIS BOX!" */
    HELP_STR_GADGETRON_IS_THE_QUADRANTS_0x4F6A = 0x00004F6A,  /* "GADGETRON IS THE QUADRANT'S LEADING RETAILER OF STATE-OF-THE-ART GADGET TECHNOLOGY!" */
    HELP_STR_ASK_ABOUT_OUR_SELECTION_0x4F6B = 0x00004F6B,  /* "ASK ABOUT OUR SELECTION OF HIGH-QUALITY AMMUNITION!" */
    HELP_STR_GADGETRON_WHERE_YOU_ALWAYS_0x4F6C = 0x00004F6C,  /* "GADGETRON!  WHERE YOU ALWAYS SAVE MORE!" */
    HELP_STR_ARE_YOU_SURE_YOU_0x4F6D = 0x00004F6D,  /* "Are you sure you want to quit your current game?" */
    HELP_STR_QUIT_RACE = 0x00004F6E,  /* "Quit Race?" */
    HELP_STR_SUBTITLES_OPTIONS = 0x00004F6F,  /* "Subtitles Options" */
    HELP_STR_LOCAL_MAP = 0x00004F70,  /* " Local Map" */
    HELP_STR_BLAST_OFF = 0x00004F71,  /* " Blast Off" */
    HELP_STR_THE_BOMB_GLOVE_IS_0x4F72 = 0x00004F72,  /* "The Bomb Glove is an affordable, entry-level weapon.  In fact, it's FREE! We believe in this product so strongly that we're willing to give it away to first-time customers!Effective at close or medium-range, this device can be especially handy against clusters of enemies.  Hold down  for precision aiming.  Makes a great gift!" */
    HELP_STR_HAVING_PROBLEMS_WITH_SWARMS_0x4F73 = 0x00004F73,  /* "Having problems with swarms of small creatures? The Gadgetron Pyrocitor is the answer! This flamethrower device will toast 'em fast! User Tip: Hold down  for a constant stream of fire." */
    HELP_STR_THE_BLASTER_IS_A_0x4F74 = 0x00004F74,  /* "The Blaster is a great all-purpose weapon. Even though its range is limited, its high rate of fire makes it ideal for taking on tough enemies at close and medium ranges. Hold down  to use its sniper capabilities. This gun chews up ammo fast so be sure to pick up as much Blaster ammo as you can carry" */
    HELP_STR_WANT_SOME_EXPLOSIVE_NEW_0x4F75 = 0x00004F75,  /* "Want some explosive new friends? Try the Glove of Doom! This handy device lets you throw Gadgetron's DoomEggs which hatch into four Agents of Doom. These tenacious little robots will track down and destroy any nearby threats! Up to 8 Agents can be activated at once!" */
    HELP_STR_THE_MINE_GLOVE_DROPS_0x4F76 = 0x00004F76,  /* "The Mine Glove drops floating mines which will activate when any enemies walk into range. Use mines to set traps for your foes! Or try them in combination with Gadgetron's Taunter! Use  for precision placement of the mines." */
    HELP_STR_WHILE_THE_TAUNTER_DOESNT_0x4F77 = 0x00004F77,  /* "While the Taunter doesn't have offensive capabilities, it's great for luring enemies into mines, forcefields or simply into range of your other weapons. The Taunter will also activate any mines you've placed in the environment, increasing their effective range. When used together, Gadgetron's Mine Glove and Taunter are a deadly combination!" */
    HELP_STR_THE_DEVASTATOR_IS_THE_0x4F78 = 0x00004F78,  /* "The Devastator is the perfect combination of long range effectiveness and economy. Less expensive than some of Gadgetron's other long range weapons, the Devastator can bring down flying enemies with ease. Try the Devastator's new Auto-Lockon feature!  Hold down , and the Lockon reticule will turn green when a target is acquired.  Once locked on, the Devastator missiles will automatically seek moving targets." */
    HELP_STR_GADGETRONS_MOST_POPULAR_SHORT_0x4F79 = 0x00004F79,  /* "Gadgetron's most popular short range weapon, the Walloper really packs a punch! This 'punching glove' is the perfect device for close range combat, when projectile weapons just won't do the job." */
    HELP_STR_THE_VISIBOMB_GUN_IS_0x4F7A = 0x00004F7A,  /* "The Visibomb Gun is the most effective long range weapon made by Gadgetron!  Just launch a remote-controlled Visibomb and deliver a massive payload with pinpoint accuracy! Caution: always fire the gun from a safe place, since damage to the user will terminate the missile's flight." */
    HELP_STR_EVER_WANT_TO_DISTRACT_0x4F7B = 0x00004F7B,  /* "Ever want to distract your foes while you sneak past unscathed? The Decoy Glove creates customized, inflatable dummies in your own likeness!  Your enemies will attack the dummy, while you sneak past them (or attack them from behind!)" */
    HELP_STR_WHENEVER_THIS_DEVICE_IS_0x4F7C = 0x00004F7C,  /* "Whenever this device is selected from the QuickSelect menu or Weapons menu, it will automatically deploy protective Defense Drones. These drones will absorb damage from incoming attacks, leaving your hands free to use other weapons. If any drones are destroyed, simply select the device again to replenish your orbiting friends." */
    HELP_STR_USING_STATE_OF_THE_ART_ELECTROSTATIC_TECHNOLOGY_0x4F7D = 0x00004F7D,  /* "Using state-of-the-art electrostatic technology, the Tesla Claw is the pinnacle of Gadgetron weapons technology. The Tesla Claw sends a powerful stream of charged particles to your nearest foe, destroying it with deadly efficiency. The Tesla Claw will automatically seek a new target whenever its current target is obliterated. " */
    HELP_STR_THE_SUCK_CANNON_IS_0x4F7E = 0x00004F7E,  /* "The Suck Cannon is a prototype weapon under development by the Blarg. What we know about this device is that it uses new quantum technology to suck up small enemies, then convert them to explosive projectiles. Simply hold down  to suck enemies into the gun. Then, tap  again to fire an enemy back out!  Keep  held down for rapid fire!" */
    HELP_STR_WHILE_IT_ORIGINATED_AS_0x4F7F = 0x00004F7F,  /* "While it originated as a failed attempt to create a disintegration ray, the Morph-o-ray has now become one of Gadgetron's most popular devices.  Just shine the Morph-o-ray beam at your foes and watch them turn into harmless chickens! Hold the beam on an enemy for a short period of time to convert it. Caution: larger enemies may take longer to convert." */
    HELP_STR_ORIGINALLY_MANUFACTURED_BY_GADGETRON_0x4F80 = 0x00004F80,  /* "Originally manufactured by Gadgetron as the ultimate in tactical offensive weaponry, the R.Y.N.O. ('Rip You a New One') is now only available from black market vendors. Featuring high-capacity, rapid-fire, auto-tracking missiles, this weapon was simply deemed too dangerous for civilian use." */
    HELP_STR_WHEN_EQUIPPED_THE_GADGETRON_0x4F81 = 0x00004F81,  /* "When equipped, the Gadgetron Swingshot enables users to use Versa-Targets to reach new areas. Versa-Targets come in two varieties: green targets are for grappling and pulling, while yellow targets are used for swinging back and forth. Caution: to prevent injury, do not release  until you are in range of your destination." */
    HELP_STR_USING_QUANTUM_COMPRESSION_TECHNOLOGY_0x4F82 = 0x00004F82,  /* "Using quantum compression technology, the Hydrodisplacer can hold up to 50,000 liters of water. This device is invaluable for draining and filling large pools. To fill the Hydrodisplacer, simply find a Gadgetron Hydro-Faucet, step on the activation pad and press . When you use a Hydro-Faucet, it will automatically convert to a Hydro-Drain. You can deposit the Hydrodisplacer's contents at any Hydro-Drain." */
    HELP_STR_GADGETRONS_TRESPASSER_IS_THE_0x4F83 = 0x00004F83,  /* "Gadgetron's Trespasser is the perfect device for getting past Invinco-Locks Simply stand on the activation pad for an Invinco-Lock and press  to bring up the Invinco-Lock interface. Lasers are mounted on each ring of the Invinco-Lock. Push  up and down to select which ring is active; push left and right to rotate the ring. Aim the lasers at the receptors on the outside ring to turn them green. All receptors must be green before the  Invinco-Lock will open. " */
    HELP_STR_THE_GADGETRON_HOLOGUISE_IS_0x4F84 = 0x00004F84,  /* "The Gadgetron Hologuise is the perfect infiltration device for all our non-robot customers! Simply equip the device and hit . You will instantly be disguised as a robot, preventing detection by most robotic security systems. Press  again to wave at fellow robots who can deactivate force-fields for you.Caution: Use of any weapon while disguised will deactivate the Hologuise!" */
    HELP_STR_WHILE_THIS_METAL_DETECTOR_0x4F85 = 0x00004F85,  /* "While this Metal Detector is not manufactured by Gadgetron, we do have extensive records on its use. Whether or not the device is equipped, a bolt icon will show up on screen whenever you are near a buried stash of bolts. Once the Metal Detector is equipped, it will give you signals to indicate the proximity to buried bolts.  As you get closer, the rings will become redder and the beeping will become faster. The detector plate will indicate the direction to the buried bolts." */
    HELP_STR_THE_GADGETRON_PERSONAL_DELIVERY_0x4F86 = 0x00004F86,  /* "The Gadgetron Personal Delivery Assistant can be deployed anywhere for instant ammo delivery! Simply equip the device and press . Gadgetron will be at your service immediately!" */
    HELP_STR_THE_MAGNEBOOTS_ARE_STILL_0x4F87 = 0x00004F87,  /* "The Magneboots are still under development at Gadgetron, and are not currently for sale.  A few prototype versions of the device have been circulated for beta testing. The boots are designed to adhere firmly to specially ionized Magne-Strips, thus allowing users to walk up walls and even upside down!  Exercise caution, however, as the Magneboots will not prevent you from falling if you should step off the Magne-Strips!" */
    HELP_STR_RUMORS_CIRCULATED_FOR_A_0x4F88 = 0x00004F88,  /* "Rumors circulated for a brief time that someone had invented a device called 'Grindboots' that would somehow allow users to slide along thin narrow rails at high speeds.  After further investigation, we do not believe any such device ever existed." */
    HELP_STR_THE_SONIC_SUMMONER_ALLOWS_0x4F89 = 0x00004F89,  /* "The Sonic Summoner allows you to interact with the mysterious and intelligent Sand Mice species. Despite their innocent appearance, Sand Mice are very effective and aggressive hunters.Simply equip the Sonic Summoner when you are near a Sand Mouse House, and a mouse will emerge to greet you. If the mouse likes you, it may offer a bit of high-caliber tactical assistance." */
    HELP_STR_WANT_TO_BREATHE_UNDERWATER_0x4F8A = 0x00004F8A,  /* "Want to breathe underwater? How about taking a space walk? You can even survive in poisonous atmospheres with the O2 Mask from Gadgetron! This mask autoequips whenever it senses that you need extra oxygen! Or, if you prefer, you can equip it any time and wear it for its stylish looks." */
    HELP_STR_DEVELOPED_BY_THE_BLARG_0x4F8B = 0x00004F8B,  /* "Developed by the Blarg, the Pilot's Helmet is a direct neural interface that allows you to pilot Blarg fighters. The control scheme is simple enough for even a Blarg to use: : fire machine guns. : launch missiles. :  engage afterburners." */
    HELP_STR_THE_THRUSTER_PACK_UPGRADE_HAS_0x4F8C = 0x00004F8C,  /* "The Thruster-Pack upgrade has Boost Jump, Stretch Jump and Glide features just like the Heli-Pack. In addition the Thruster-Pack provides a special maneuver called the Power Slam.  Press  during a jump to activate the Power Slam. The Power Slam can open special locks and break objects in the environment." */
    HELP_STR_WITH_THE_HELI_PACK_UPGRADE_0x4F8D = 0x00004F8D,  /* "With the Heli-Pack upgrade, you can perform a Boost Jump by jumping from a crouched position. You can also perform a Stretch Jump by pressing  while running, then immediately pressing . To glide, simply press and hold  while in the air. Visit your local Robo-Shack dealer to equip this upgrade!" */
    HELP_STR_THE_HYDRO_PACK_UPGRADE_IS_0x4F8E = 0x00004F8E,  /* "The Hydro-Pack upgrade is a black market offering not endorsed by Gadgetron. This upgrade significantly increases swim speed and will even let you swim against currents" */
    HELP_STR_THE_GOLD_BOMB_GLOVE_0x4F8F = 0x00004F8F,  /* "The Gold Bomb Glove replaces your original Bomb Glove and provides more power and bigger explosions for your bombs!  The Gold Bomb Glove also offers longer range when in aiming mode! A real bargain for only a few Gold Bolts!" */
    HELP_STR_THE_GOLD_PYROCITOR_IS_0x4F90 = 0x00004F90,  /* "The Gold Pyrocitor is Gadgetron's deluxe version of its popular flamethrower. This weapon does more damage and does it faster than the original. It also has a greater range and a soothing green flame." */
    HELP_STR_WHY_SETTLE_FOR_A_0x4F91 = 0x00004F91,  /* "Why settle for a regular Blaster when you can have a Gold Blaster? Greater range, firing rate and power is yours with this gold plated beauty. And as an added bonus, your projectiles will richochet off any object - increasing the damage you can do!" */
    HELP_STR_WHILE_THE_REGULAR_GLOVE_0x4F92 = 0x00004F92,  /* "While the regular Glove of Doom has become a favorite among galactic adventurers, the Gold Glove of Doom brings new functionality to this classic.  The Gold version now offers you larger, faster and more powerful Agents! And with their new gloss black exterior, your Agents will fit in nicely at any social function!" */
    HELP_STR_THE_GOLD_MINE_GLOVE_0x4F93 = 0x00004F93,  /* "The Gold Mine Glove is a simple yet effective improvement to the original. Your mines will do more damage, activate at a larger range, and can even be thrown farther when in aiming mode.  A solid addition to any adventurer's arsenal!" */
    HELP_STR_WHEN_WE_AT_GADGETRON_0x4F94 = 0x00004F94,  /* "When we at Gadgetron set out to create a Gold Devastator, we were at a temporary loss. How does one improve on perfection?  And then our engineering staff developed a new targeting technology which enables each missile to hit multiple targets and do even MORE damage! Go ahead... fire a few shots and enjoy the show!" */
    HELP_STR_THE_DECOY_GLOVE_HAS_0x4F95 = 0x00004F95,  /* "The Decoy Glove has always been one of Gadgetron's more entertaining weapons, and the Gold Decoy Glove is sure to earn a permanent place in your armory. Not only does it have a brand new look, but it now will automatically damage any enemy who attacks it!" */
    HELP_STR_THE_GOLD_TESLA_CLAW_0x4F96 = 0x00004F96,  /* "The Gold Tesla Claw is a more powerful version of one of Gadgetron's most effective weapons. Fry your enemies even faster with this dynamo!" */
    HELP_STR_EVEN_THOUGH_THE_SUCK_0x4F97 = 0x00004F97,  /* "Even though the Suck Cannon was never released as a production weapon, we've decided to release a Gold version thanks to the prototype's popularity. The Gold Suck Cannon has an increased capacity and its projectiles will now do more damage." */
    HELP_STR_WHEN_WE_REALIZED_HOW_0x4F98 = 0x00004F98,  /* "When we realized how popular the Morpharay had become, we couldn't wait to make a Gold Morpharay. Yes, this is the perfect weapon for chicken-lovers everywhere.  Now featuring even faster morphing technology! And, due to popular demand, we've even super-sized the chickens.  BIG CHICKENS!  Could anyone ask for more?" */
    HELP_STR_WEAPONS_HELP = 0x00004F99,  /* "Weapons Help" */
    HELP_STR_GADGETS_HELP = 0x00004F9A,  /* "Gadgets Help" */
    HELP_STR_CONGRATULATIONS_NOW_THAT_CHAIRMAN_0x4F9B = 0x00004F9B,  /* "Congratulations! Now that Chairman Drek's account has been closed, you're Gadgetron's most valued customer!We've got new items available for you! Just check the new Goodies menu on your pause screen." */
    HELP_STR_IF_YOUD_LIKE_YOU_0x4F9C = 0x00004F9C,  /* "If you'd like, you can start a new game with all of your current weapons and bolts. You can also go back to your last save. Go ahead and pick one!" */
    HELP_STR_IM_VERY_IMPRESSED_YOU_0x4F9D = 0x00004F9D,  /* "I'm very impressed! You beat Drek again! If you choose to start another new game, I will create another new save game for you!" */
    HELP_STR_CONGRATULATIONS_NOW_THAT_CHAIRMAN_0x4F9E = 0x00004F9E,  /* "Congratulations! Now that Chairman Drek's account has been closed, you're Gadgetron's most valued customer!We've got new items available for you! Just check the new Goodies menu on your pause screen.If you'd like, you can start a new game with all of your current weapons and bolts. You can also go back to your last save. Go ahead and pick one!" */
    HELP_STR_VOICE = 0x00004F9F,  /* "Voice" */
    HELP_STR_TEXT = 0x00004FA0,  /* "Text" */
    HELP_STR_CONTROLLER_VIBRATION = 0x00004FA1,  /* "Controller vibration" */
    HELP_STR_LEFT_RIGHT_MOVEMENT = 0x00004FA2,  /* "Left/Right movement" */
    HELP_STR_UP_DOWN_MOVEMENT = 0x00004FA3,  /* "Up/Down movement" */
    HELP_STR_NORMAL = 0x00004FA4,  /* "Normal" */
    HELP_STR_REVERSED = 0x00004FA5,  /* "Reversed" */
    HELP_STR_MEMORY_CARD_PS2_IN_0x4FA6 = 0x00004FA6,  /* "Memory Card (PS2) in MEMORY CARD slot 1 was removed.Auto-save has been disabled.Use the save game option to manually save your game and re-enable auto-save." */
    HELP_STR_PLEASE_INSERT_A_MEMORY_0x4FA7 = 0x00004FA7,  /* "Please insert a Memory Card (PS2) in MEMORY CARD slot 1 that contains Ratchet and Clank game data." */
    HELP_STR_GO_BACK = 0x00004FA8,  /* " Go back?" */
    HELP_STR_INSUFFICIENT_SPACE_ON_MEMORY_0x4FA9 = 0x00004FA9,  /* "Insufficient space on Memory Card (PS2) inserted in MEMORY CARD slot 1.Ratchet and Clank requires 350 KB to save.Please insert a Memory Card (PS2) containing sufficient space or you will not be able to save game data." */
    HELP_STR_CONTINUE_ANYWAY = 0x00004FAA,  /* "Continue anyway?" */
    HELP_STR_NO_MEMORY_CARD_PS2_0x4FAB = 0x00004FAB,  /* "No Memory Card (PS2) inserted.Ratchet and Clank requires 350 KB of free space.Please insert a Memory Card (PS2) containing sufficient space or you will not be able to save game data.Continue anyway?" */
    HELP_STR_NO_MEMORY_CARD_PS2_0x4FAC = 0x00004FAC,  /* "No Memory Card (PS2) inserted.Ratchet and Clank requires 350 KB of free space.Please insert a Memory Card (PS2) containing sufficient space or you will not be able to save game data." */
    HELP_STR_NO_RATCHET_AND_CLANK_0x4FAD = 0x00004FAD,  /* "No Ratchet and Clank save data on the Memory Card (PS2) inserted in MEMORY CARD slot 1.Would you like to create a Ratchet and Clank save file?" */
    HELP_STR_NO_RATCHET_AND_CLANK_0x4FAE = 0x00004FAE,  /* "No Ratchet and Clank save data on the Memory Card (PS2) inserted in MEMORY CARD slot 1.If you do not create a save file then you will not be able to save game data." */
    HELP_STR_MEMORY_CARD_PS2_IN_0x4FAF = 0x00004FAF,  /* "Memory Card (PS2) in MEMORY CARD slot 1 is unformatted.If you do not format it then you will not be able to save game data.Format?" */
    HELP_STR_MEMORY_CARD_PS2_IN_0x4FB0 = 0x00004FB0,  /* "Memory Card (PS2) in MEMORY CARD slot 1 is unformatted." */
    HELP_STR_MEMORY_CARD_PS2_IN_0x4FB1 = 0x00004FB1,  /* "Memory Card (PS2) in MEMORY CARD slot 1 is unformatted.If you do not format it then you will not be able to save game data.Continue anyway?" */
    HELP_STR_A_RATCHET_AND_CLANK_0x4FB2 = 0x00004FB2,  /* "A Ratchet and Clank save game already exists on the Memory Card (PS2) inserted in MEMORY CARD slot 1.Do you wish to overwrite this?" */
    HELP_STR_A_RATCHET_AND_CLANK_0x4FB3 = 0x00004FB3,  /* "A Ratchet and Clank save game already exists in the save file you have selected.Do you wish to overwrite this?" */
    HELP_STR_AUTO_SAVE_FAILEDDIFFERENT_MEMORY_CARD_0x4FB4 = 0x00004FB4,  /* "Auto-save failed.Different Memory Card (PS2) inserted into slot 1." */
    HELP_STR_SAVING_DATAPLEASE_DO_NOT_0x4FB5 = 0x00004FB5,  /* "Saving Data.Please do not remove the Memory Card (PS2) in MEMORY CARD slot 1 or turn off your console." */
    HELP_STR_LOADING_DATAPLEASE_DO_NOT_0x4FB6 = 0x00004FB6,  /* "Loading Data.Please do not remove the Memory Card (PS2) in MEMORY CARD slot 1 or turn off your console." */
    HELP_STR_FORMATTINGPLEASE_DO_NOT_REMOVE_0x4FB7 = 0x00004FB7,  /* "FormattingPlease do not remove the Memory Card (PS2) in MEMORY CARD slot 1 or turn off your console." */
    HELP_STR_CREATING_SAVE_GAME_FILEPLEASE_0x4FB8 = 0x00004FB8,  /* "Creating Save Game FilePlease do not remove the Memory Card (PS2) in MEMORY CARD slot 1 or turn off your console." */
    HELP_STR_CHECKING_MEMORY_CARD_PS2PLEASE_0x4FB9 = 0x00004FB9,  /* "Checking Memory Card (PS2)Please do not remove the Memory Card (PS2) in MEMORY CARD slot 1 or turn off your console." */
    HELP_STR_FORMAT_FAILED_PLEASE_CHECK_0x4FBA = 0x00004FBA,  /* "Format failed! Please check Memory Card (PS2) and try again." */
    HELP_STR_LOAD_FAILED_PLEASE_CHECK_0x4FBB = 0x00004FBB,  /* "Load failed!  Please check Memory Card (PS2) and try again." */
    HELP_STR_SAVE_FAILED_PLEASE_CHECK_0x4FBC = 0x00004FBC,  /* "Save failed!  Please check Memory Card (PS2) and try again." */
    HELP_STR_SAVE_FAILED_PLEASE_CHECK_0x4FBD = 0x00004FBD,  /* "Save failed!  Please check Memory Card (PS2) and try again.Auto-save has been disabled.Use the save game option to manually save your game and re-enable auto-save." */
    HELP_STR_CHEAT_ENABLED = 0x00004FBE,  /* "Cheat Enabled" */
    HELP_STR_CHEAT_DISABLED = 0x00004FBF,  /* "Cheat Disabled" */
    HELP_STR_NO_CHEATS_ACTIVATED = 0x00004FC0,  /* "No Cheats Activated" */
    HELP_STR_READING_MEMORY_CARD_PS2 = 0x00004FC1,  /* "Reading Memory Card (PS2)" */
    HELP_STR_GOODIES = 0x00004FC2,  /* "Goodies" */
    HELP_STR_GOODIES_MENU = 0x00004FC3,  /* "Goodies Menu" */
    HELP_STR_SKILL_POINTS_3 = 0x00004FC4,  /* "Skill Points" */
    HELP_STR_CREDITS = 0x00004FC5,  /* "Credits" */
    HELP_STR_CHEATS = 0x00004FC6,  /* "Cheats" */
    HELP_STR_CINEMATICS = 0x00004FC7,  /* "Cinematics" */
    HELP_STR_IN_LEVEL_MOVIES = 0x00004FC8,  /* "In-Level Movies" */
    HELP_STR_SKETCHBOOK = 0x00004FC9,  /* "Sketchbook" */
    HELP_STR_EPILOGUE = 0x00004FCA,  /* "Epilogue" */
    HELP_STR_MAKING_OF_VIDEO = 0x00004FCB,  /* "'Making Of' Video" */
    HELP_STR_COMMERCIALS = 0x00004FCC,  /* "Commercials" */
    HELP_STR_0x4FCD = 0x00004FCD,  /* "????" */
    HELP_STR_SKILL_POINTS_ARE_SPECIAL_0x4FCE = 0x00004FCE,  /* "Skill Points are special tasks that you can complete to unlock features!" */
    HELP_STR_SEE_WHO_IS_RESPONSIBLE_0x4FCF = 0x00004FCF,  /* "See who is responsible for making this game!" */
    HELP_STR_IF_YOUVE_SUCCESSFULLY_ENTERED_0x4FD0 = 0x00004FD0,  /* "If you've successfully entered a cheat, you can toggle it on and off here." */
    HELP_STR_WATCH_SOME_OF_THE_0x4FD1 = 0x00004FD1,  /* "Watch some of the between-worlds movies from the game." */
    HELP_STR_WATCH_MOVIES_FOR_THE_0x4FD2 = 0x00004FD2,  /* "Watch movies for the world you're in." */
    HELP_STR_LOOK_AT_SOME_OF_0x4FD3 = 0x00004FD3,  /* "Look at some of the art that went into making the game!" */
    HELP_STR_SEE_WHAT_HAPPENED_AFTER_0x4FD4 = 0x00004FD4,  /* "See what happened after Drek's defeat!" */
    HELP_STR_HELP_LOG = 0x00004FD5,  /* "Help Log" */
    HELP_STR_REVIEW_HELPFUL_MESSAGES_FROM_0x4FD6 = 0x00004FD6,  /* "Review helpful messages from Gadgetron." */
    HELP_STR_CHECK_OUT_THIS_SPECIAL_0x4FD7 = 0x00004FD7,  /* "Check out this special behind-the-scenes video with Insomniac Games!" */
    HELP_STR_WATCH_THE_HILARIOUS_TELEVISION_0x4FD8 = 0x00004FD8,  /* "Watch the hilarious television commercials for Ratchet and Clank!" */
    HELP_STR_YOU_HAVE_TO_COMPLETE_0x4FD9 = 0x00004FD9,  /* "You have to complete any 15 Skill Points to unlock this feature�" */
    HELP_STR_YOU_HAVE_TO_COMPLETE_0x4FDA = 0x00004FDA,  /* "You have to complete all Skill Points to unlock this feature�" */
    HELP_STR_YOU_HAVE_TO_BUY_0x4FDB = 0x00004FDB,  /* "You have to buy all Gold Weapons to unlock this feature�" */
    HELP_STR_TAKE_AIM = 0x00004FDC,  /* "Take Aim" */
    HELP_STR_SWING_IT = 0x00004FDD,  /* "Swing It!" */
    HELP_STR_TRANSPORTED = 0x00004FDE,  /* "Transported" */
    HELP_STR_STRIKE_A_POSE = 0x00004FDF,  /* "Strike a Pose" */
    HELP_STR_BLIMPY = 0x00004FE0,  /* "Blimpy" */
    HELP_STR_QWARKTASTIC = 0x00004FE1,  /* "Qwarktastic" */
    HELP_STR_ANY_TEN = 0x00004FE2,  /* "Any Ten" */
    HELP_STR_TRICKY = 0x00004FE3,  /* "Tricky" */
    HELP_STR_CLUCK_CLUCK = 0x00004FE4,  /* "Cluck, Cluck" */
    HELP_STR_SPEEDY = 0x00004FE5,  /* "Speedy" */
    HELP_STR_GIRL_TROUBLE = 0x00004FE6,  /* "Girl Trouble" */
    HELP_STR_JUMPER = 0x00004FE7,  /* "Jumper" */
    HELP_STR_ACCURACY_COUNTS = 0x00004FE8,  /* "Accuracy Counts" */
    HELP_STR_EAT_LEAD = 0x00004FE9,  /* "Eat Lead" */
    HELP_STR_DESTROYED = 0x00004FEA,  /* "Destroyed" */
    HELP_STR_GUNNER = 0x00004FEB,  /* "Gunner" */
    HELP_STR_SNIPER = 0x00004FEC,  /* "Sniper" */
    HELP_STR_HEY_OVER_HERE = 0x00004FED,  /* "Hey, Over Here!" */
    HELP_STR_ALIEN_INVASION = 0x00004FEE,  /* "Alien Invasion" */
    HELP_STR_BURIED_TREASURE = 0x00004FEF,  /* "Buried Treasure" */
    HELP_STR_PEST_CONTROL = 0x00004FF0,  /* "Pest Control" */
    HELP_STR_WHIRLYBIRDS = 0x00004FF1,  /* "Whirlybirds" */
    HELP_STR_SITTING_DUCKS = 0x00004FF2,  /* "Sitting Ducks" */
    HELP_STR_SHATTERED_GLASS = 0x00004FF3,  /* "Shattered Glass" */
    HELP_STR_BLAST_EM = 0x00004FF4,  /* "Blast 'Em!" */
    HELP_STR_HEAVY_TRAFFIC = 0x00004FF5,  /* "Heavy Traffic" */
    HELP_STR_MAGICIAN = 0x00004FF6,  /* "Magician" */
    HELP_STR_SNEAKY = 0x00004FF7,  /* "Sneaky" */
    HELP_STR_CAREFUL_CRUISE = 0x00004FF8,  /* "Careful Cruise" */
    HELP_STR_GOING_COMMANDO = 0x00004FF9,  /* "Going Commando" */
    HELP_STR_DESTROY_A_FIGHTER_OR_0x4FFA = 0x00004FFA,  /* "Destroy a fighter or a bomber" */
    HELP_STR_TRAVERSE_FINAL_SIX_SWINGSHOT_0x4FFB = 0x00004FFB,  /* "Traverse final six swingshot targets in factory without touching the ground" */
    HELP_STR_DESTROY_THREE_FLYING_TRANSPORTS = 0x00004FFC,  /* "Destroy three flying transports" */
    HELP_STR_STAND_BETWEEN_THE_LEGS_0x4FFD = 0x00004FFD,  /* "Stand between the legs of the Al's Roboshack statue" */
    HELP_STR_TAKE_OUT_A_BLIMP_0x4FFE = 0x00004FFE,  /* "Take out a blimp, any blimp" */
    HELP_STR_DESTROY_THE_QWARKBOT_STATUE = 0x00004FFF,  /* "Destroy the Qwarkbot statue" */
    HELP_STR_BLOW_UP_TEN_VEHICLES = 0x00005000,  /* "Blow up ten vehicles" */
    HELP_STR_DO_A_TWISTY_MCMARX_0x5001 = 0x00005001,  /* "Do a Twisty McMarx in a hoverboard race" */
    HELP_STR_TURN_A_TANK_INTO_0x5002 = 0x00005002,  /* "Turn a tank into a chicken" */
    HELP_STR_BEAT_HOVERBOARD_CHALLENGE_IN_0x5003 = 0x00005003,  /* "Beat hoverboard challenge in 1:35 or less" */
    HELP_STR_BEAT_HOVERBOARD_CHALLENGE_IN_0x5004 = 0x00005004,  /* "Beat hoverboard challenge in 1:36 or less" */
    HELP_STR_BEAT_THE_ALIEN_QUEEN_0x5005 = 0x00005005,  /* "Beat the Alien Queen using your wrench only!" */
    HELP_STR_GET_THROUGH_THE_GRINDRAIL_0x5006 = 0x00005006,  /* "Get through the Grindrail without losing a hit point" */
    HELP_STR_DESTROY_A_SMALL_FIGHTER_0x5007 = 0x00005007,  /* "Destroy a small fighter with the turret" */
    HELP_STR_USE_A_SAND_MOUSE_0x5008 = 0x00005008,  /* "Use a Sand Mouse to take out all tanks" */
    HELP_STR_BLOW_UP_ALL_OF_0x5009 = 0x00005009,  /* "Blow up all of the blarg destroyers" */
    HELP_STR_DOWN_FIVE_SHIPS_WITH_0x500A = 0x0000500A,  /* "Down five ships with a turret" */
    HELP_STR_SHOOT_A_SCREAMER_THROUGH_0x500B = 0x0000500B,  /* "Shoot a Screamer through sniper hole" */
    HELP_STR_LURE_ANY_ENEMY_INTO_0x500C = 0x0000500C,  /* "Lure any enemy into a forcefield" */
    HELP_STR_SHOOT_DOWN_THREE_BLARG_0x500D = 0x0000500D,  /* "Shoot down three Blarg saucers with visibombs" */
    HELP_STR_FIND_AND_DESTROY_ALL_0x500E = 0x0000500E,  /* "Find and destroy all crates in the ocean." */
    HELP_STR_KILL_ALL_ANKLEBITERS_IN_0x500F = 0x0000500F,  /* "Kill all anklebiters in forested section" */
    HELP_STR_DESTROY_FIVE_HELICOPTERS_WITH_0x5010 = 0x00005010,  /* "Destroy five helicopters with any weapon other than the turret" */
    HELP_STR_DESTROY_ALL_CARGO_SHIPS_0x5011 = 0x00005011,  /* "Destroy all cargo ships in the base" */
    HELP_STR_BLAST_ALL_OF_THE_0x5012 = 0x00005012,  /* "Blast all of the streetlights in the city" */
    HELP_STR_DESTROY_THREE_MARAUDING_BLARG_0x5013 = 0x00005013,  /* "Destroy three marauding Blarg ships" */
    HELP_STR_TRAVERSE_THE_LONG_GRINDRAIL_0x5014 = 0x00005014,  /* "Traverse the long Grindrail without hitting any mines or cars" */
    HELP_STR_ATTAIN_A_TRICKS_SCORE_0x5015 = 0x00005015,  /* "Attain a tricks score of 4500 or better on hoverboard race" */
    HELP_STR_KILL_ALL_ENEMIES_IN_0x5016 = 0x00005016,  /* "Kill all enemies in Hologuise traversal" */
    HELP_STR_COMPLETE_WATER_TRAVERSAL_WITHOUT_0x5017 = 0x00005017,  /* "Complete water traversal without losing any hit points" */
    HELP_STR_KILL_TEN_ELITE_GUARDS_0x5018 = 0x00005018,  /* "Kill ten elite guards on Kyzil Plateau with your wrench only" */
    HELP_STR_ALL_LEVELS = 0x00005019,  /* "All Levels" */
    HELP_STR_RATCHET_HAS_A_BIG_0x501A = 0x0000501A,  /* "Ratchet has a big head" */
    HELP_STR_CLANK_HAS_A_LARGE_0x501B = 0x0000501B,  /* "Clank has a large noggin" */
    HELP_STR_ACTORS_HAVE_OVERSIZED_CRANIUMS = 0x0000501C,  /* "Actors have oversized craniums" */
    HELP_STR_ENEMIES_HAVE_MASSIVE_DOMES = 0x0000501D,  /* "Enemies have massive domes" */
    HELP_STR_LEVELS_ARE_MIRRORED = 0x0000501E,  /* "Levels are mirrored" */
    HELP_STR_LEFT_HANDED_RATCHET = 0x0000501F,  /* "Left-handed Ratchet" */
    HELP_STR_HEALTH_GIVES_INVINCIBILITY_AT_0x5020 = 0x00005020,  /* "Health gives invincibility at max" */
    HELP_STR_TRIPPY_CONTRAILS = 0x00005021,  /* "Trippy contrails" */
    HELP_STR_CLANK_CRASHES = 0x00005022,  /* "Clank crashes" */
    HELP_STR_YOURE_QUITE_HANDY_WITH_0x5023 = 0x00005023,  /* "You're quite handy with your wrench�" */
    HELP_STR_THE_PEOPLE_ON_THOSE_0x5024 = 0x00005024,  /* "The people on those planets are hosed!" */
    HELP_STR_SORRY_ABOUT_THAT = 0x00005025,  /* "Sorry about that." */
    HELP_STR_WHAT_ARE_YOU_MERCENARIES_0x5026 = 0x00005026,  /* "What are you? Mercenaries? Torturers?" */
    HELP_STR_CAPTAIN_QWARK_HAS_REALLY_0x5027 = 0x00005027,  /* "Captain Qwark has really sold out." */
    HELP_STR_LOOK___PLUMBERS_CRACK = 0x00005028,  /* "Look - plumber's crack!" */
    HELP_STR_GERONIMO = 0x00005029,  /* "Geronimo!" */
    HELP_STR_DID_YOU_SEE_THAT_0x502A = 0x0000502A,  /* "Did you see that guy on the left?" */
    HELP_STR_ITS_HIM_SKID_MCMARX = 0x0000502B,  /* "It's him! Skid McMarx!" */
    HELP_STR_HERE_CATCH = 0x0000502C,  /* "Here, catch!" */
    HELP_STR_NO_SIGNAL_WHATSOEVER = 0x0000502D,  /* "No signal whatsoever!" */
    HELP_STR_GREAT_WORK_KID = 0x0000502E,  /* "Great work kid!" */
    HELP_STR_HEY_YOURE_THAT_ROBOT_0x502F = 0x0000502F,  /* "Hey, you're that robot guy, right?" */
    HELP_STR_OKAY_THIS_WONT_HURT_0x5030 = 0x00005030,  /* "Okay, this won't hurt a bit." */
    HELP_STR_LISTEN_UP_YOU_LARDBALLS = 0x00005031,  /* "Listen up you lardballs!" */
    HELP_STR_THE_TWO_OF_YOU_0x5032 = 0x00005032,  /* "The two of you make me sick." */
    HELP_STR_THAT_LIEUTENANT_DOESNT_SEEM_0x5033 = 0x00005033,  /* "That lieutenant doesn't seem so tough." */
    HELP_STR_WELCOME = 0x00005034,  /* "Welcome!" */
    HELP_STR_EXCUSE_ME_CAPTAIN = 0x00005035,  /* "Excuse me Captain�" */
    HELP_STR_YOU_SURE_SHOWED_HIM = 0x00005036,  /* "You sure showed him." */
    HELP_STR_NOW_WERE_TALKIN = 0x00005037,  /* "Now we're talkin'!" */
    HELP_STR_WELCOME_2 = 0x00005038,  /* "Welcome!" */
    HELP_STR_HI_FOLKS_CAPTAIN_QWARK_0x5039 = 0x00005039,  /* "Hi folks, Captain Qwark here." */
    HELP_STR_HEY_HEY_HEY_PRESS_0x503A = 0x0000503A,  /* "Hey, hey, hey! Press conference is over!" */
    HELP_STR_CAPTAINQWARK = 0x0000503B,  /* "Captain�Qwark?" */
    HELP_STR_MEET_ME_ATUH = 0x0000503C,  /* "Meet me at�uh..." */
    HELP_STR_WHEW_I_THOUGHT_I_0x503D = 0x0000503D,  /* "Whew, I thought I was a goner..." */
    HELP_STR_WELL_THANKS = 0x0000503E,  /* "Well, thanks!" */
    HELP_STR_WELCOME_TO_MY_CHALLENGE_0x503F = 0x0000503F,  /* "Welcome to my challenge course." */
    HELP_STR_STEP_INTO_THE_RING_0x5040 = 0x00005040,  /* "Step into the Ring of Heroes�" */
    HELP_STR_GET_OFFA_ME_YOU_0x5041 = 0x00005041,  /* "Get offa me you idiot!" */
    HELP_STR_THATS_IT_IM_OUTTA_0x5042 = 0x00005042,  /* "That's it! I'm outta here!" */
    HELP_STR_AT_ATTENTION_YOU_DESERTING_0x5043 = 0x00005043,  /* "At attention you deserting maggots!" */
    HELP_STR_BLASTED_THING_IT_WONT_0x5044 = 0x00005044,  /* "Blasted thing. It won't budge!" */
    HELP_STR_I_GOT_BIGGER_FISH_0x5045 = 0x00005045,  /* "I got bigger fish to fry." */
    HELP_STR_HALT_WHO_ARE_YOU = 0x00005046,  /* "Halt! Who are you?" */
    HELP_STR_I_HAVE_GOT_TO_0x5047 = 0x00005047,  /* "I have GOT to get me one!" */
    HELP_STR_HEY_I_KNOW_YOU_0x5048 = 0x00005048,  /* "Hey, I know you two." */
    HELP_STR_WELL_WELL_WELL = 0x00005049,  /* "Well, well, well." */
    HELP_STR_RATCHET_GETS_PREMIUM_NANOTECH = 0x0000504A,  /* "Ratchet gets Premium Nanotech" */
    HELP_STR_RATCHET_GETS_ULTRA_NANOTECH = 0x0000504B,  /* "Ratchet gets Ultra Nanotech" */
    HELP_STR_YOU_ARE_FRIENDLY_ARENT_0x504C = 0x0000504C,  /* "You ARE friendly, aren't you?" */
    HELP_STR_WHERES_THAT_FIGHTER = 0x0000504D,  /* "�where's that fighter?" */
    HELP_STR_WHADDA_WE_GOT_HERE = 0x0000504E,  /* "Whadda we got here?" */
    HELP_STR_I_AM_DA_MAN = 0x0000504F,  /* "I AM da man!" */
    HELP_STR_HEY_WHAT_ARE_YOU_0x5050 = 0x00005050,  /* "Hey, what are you doing here?" */
    HELP_STR_THIS_IS_PRECISELY_WHAT_0x5051 = 0x00005051,  /* "This is precisely what I need" */
    HELP_STR_WE_MUST_GET_TO_0x5052 = 0x00005052,  /* "We must get to the base!" */
    HELP_STR_AWW_HECK = 0x00005053,  /* "Aww heck!" */
    HELP_STR_HEY_BUDDY_WHATS_SHAKIN = 0x00005054,  /* "Hey buddy, what's shakin'?" */
    HELP_STR_THERE_YA_GO_SWEETIE = 0x00005055,  /* "There ya go sweetie!" */
    HELP_STR_I_DID_NOT_SEE_0x5056 = 0x00005056,  /* "I did not see Drek's ship." */
    HELP_STR_HELLO_CAPTAIN_RATCHET = 0x00005057,  /* "Hello Captain Ratchet!" */
    HELP_STR_YES_QWARK_IS_HISTORY = 0x00005058,  /* "Yes! Qwark is history!" */
    HELP_STR_LOOK_MAYBE_YOU_WERE_0x5059 = 0x00005059,  /* "Look, maybe you were right." */
    HELP_STR_CMON_WAKE_UP = 0x0000505A,  /* "C'mon! Wake up!" */
    HELP_STR_CAPTAIN_QWARK = 0x0000505B,  /* "Captain Qwark!" */
    HELP_STR_THANK_YOU_2 = 0x0000505C,  /* "Thank you!" */
    HELP_STR_HEY_WELCOME_TO_MY_0x505D = 0x0000505D,  /* "Hey! Welcome to my shop!" */
    HELP_STR_THATS_ABOUT_IT_FOR_0x505E = 0x0000505E,  /* "That's about it for me." */
    HELP_STR_HMMWAS_IT_PI_OVER_0x505F = 0x0000505F,  /* "Hmm�was it pi over infinity or�?" */
    HELP_STR_WELL_DONE = 0x00005060,  /* "Well done." */
    HELP_STR_ROBOTS_ARE_NOT_SO_0x5061 = 0x00005061,  /* "Robots are not so easily fooled." */
    HELP_STR_MOM = 0x00005062,  /* "Mom?" */
    HELP_STR_ARE_YOUALRIGHT = 0x00005063,  /* "Are you�alright?" */
    HELP_STR_YOU_EVER_BEEN_ON_0x5064 = 0x00005064,  /* "You ever been on a hoverboard?" */
    HELP_STR_THAT_WAS_TERRIFIC = 0x00005065,  /* "That was terrific!" */
    HELP_STR_I_HOPE_SHES_CUTE = 0x00005066,  /* "I hope she's cute." */
    HELP_STR_HEY_WHAT_THE = 0x00005067,  /* "Hey, what the�?" */
    HELP_STR_SO_IT_HAS_COME_0x5068 = 0x00005068,  /* "So it has come to this." */
    HELP_STR_I_AM_THINKING_WHAT_0x5069 = 0x00005069,  /* "I AM thinking what you're thinking!" */
    HELP_STR_THIS_CANT_BE_GOOD = 0x0000506A,  /* "This can't be good." */
    HELP_STR_FINALE = 0x0000506B,  /* "Finale" */
    HELP_STR_RATCHET_WORKS_ON_HIS_0x506C = 0x0000506C,  /* "Ratchet works on his ship" */
    HELP_STR_CLANK_ESCAPES_FROM_FACTORY = 0x0000506D,  /* "Clank escapes from factory" */
    HELP_STR_INFOBOT___DREKS_PLAN = 0x0000506E,  /* "Infobot - Drek's plan" */
    HELP_STR_THIS_COULD_BE_A_0x506F = 0x0000506F,  /* "''This could be a problem''" */
    HELP_STR_I_WILL_NOT_STAND_0x5070 = 0x00005070,  /* "''I will not stand for this!''" */
    HELP_STR_WHOA_THIS_IS_GREAT = 0x00005071,  /* "''Whoa! This is great!''" */
    HELP_STR_INFOBOT___DISTRESS_CALL_0x5072 = 0x00005072,  /* "Infobot - Distress call from Skid" */
    HELP_STR_INFOBOT___AD_FOR_0x5073 = 0x00005073,  /* "Infobot - Ad for Al's Roboshack" */
    HELP_STR_INFOBOT___DREK_ORDERS_0x5074 = 0x00005074,  /* "Infobot - Drek orders deforestation" */
    HELP_STR_YES_QUITE_LOVELY = 0x00005075,  /* "''Yes, quite lovely.''" */
    HELP_STR_INFOBOT___RECRUITING_ADVERTISEMENT = 0x00005076,  /* "Infobot - Recruiting advertisement" */
    HELP_STR_INFOBOT___NEWSCAST_FROM_0x5077 = 0x00005077,  /* "Infobot - Newscast from Rilgar" */
    HELP_STR_INFOBOT___INFOMERCIAL_FOR_0x5078 = 0x00005078,  /* "Infobot - Infomercial for Qwark's HQ" */
    HELP_STR_INFOBOT___SOS_FROM_0x5079 = 0x00005079,  /* "Infobot - SOS from Batalia" */
    HELP_STR_BACK_SO_SOON = 0x0000507A,  /* "''Back so soon?''" */
    HELP_STR_INFOBOT___PILOTS_HELMET_0x507B = 0x0000507B,  /* "Infobot - Pilot's Helmet demo" */
    HELP_STR_INFOBOT___ORXON_HISTORY = 0x0000507C,  /* "Infobot - Orxon history" */
    HELP_STR_INFOBOT___JOWAI_RESORT_0x507D = 0x0000507D,  /* "Infobot - Jowai Resort ad" */
    HELP_STR_INFOBOT___PLANETBUSTER_PLANS = 0x0000507E,  /* "Infobot - Planetbuster plans" */
    HELP_STR_YOU_REALLY_ARE_AN_0x507F = 0x0000507F,  /* "You really are an idiot." */
    HELP_STR_INFOBOT___ATTACK_GORDA_0x5080 = 0x00005080,  /* "Infobot - Attack Gorda City" */
    HELP_STR_INFOBOT___NEWSCAST_FROM_0x5081 = 0x00005081,  /* "Infobot - Newscast from Oltanis" */
    HELP_STR_HOW_OBSERVANT_OF_YOU = 0x00005082,  /* "''How observant of you.''" */
    HELP_STR_INFOBOT___COMMERCIAL_FOR_0x5083 = 0x00005083,  /* "Infobot - Commercial for mech" */
    HELP_STR_INFOBOT___HOLOGUISE_PROMOTION = 0x00005084,  /* "Infobot - Hologuise promotion" */
    HELP_STR_THIS_IS_STARTING_TO_0x5085 = 0x00005085,  /* "''This is starting to become annoying.''" */
    HELP_STR_INFOBOT___DREK_ANNOUNCES_0x5086 = 0x00005086,  /* "Infobot - Drek announces Deplanetizer" */
    HELP_STR_INFOBOT___DEPLANETIZER_DEMONSTRATION = 0x00005087,  /* "Infobot - Deplanetizer demonstration" */
    HELP_STR_PERSONAL_HYGIENATOR_ADVERTISEMENT = 0x00005088,  /* "Personal Hygienator advertisement" */
    HELP_STR_PLAY_MOVIE = 0x00005089,  /* " Play Movie" */
    HELP_STR_NEXT = 0x0000508A,  /* " Next" */
    HELP_STR_PREVIOUS = 0x0000508B,  /* " Previous" */
    HELP_STR_TELEVISION_COMMERCIALS = 0x0000508C,  /* "Television Commercials" */
    HELP_STR_DECOY_GLOVE_AD = 0x0000508D,  /* "Decoy Glove ad" */
    HELP_STR_DEVASTATOR_AD = 0x0000508E,  /* "Devastator ad" */
    HELP_STR_MORPHARAY_AD = 0x0000508F,  /* "Morpharay ad" */
    HELP_STR_EUROPEAN_AD = 0x00005090,  /* "European ad" */
    HELP_STR_PLAY_AD = 0x00005091,  /* " Play Ad" */
    HELP_STR_CALL_ME_SALLY = 0x00005092,  /* "Call Me Sally" */
    HELP_STR_PLUMBERS_CRACK = 0x00005093,  /* "Plumber's Crack" */
    HELP_STR_SAND_SHARK = 0x00005094,  /* "Sand Shark" */
    HELP_STR_BLARG_AIR = 0x00005095,  /* "Blarg Air" */
    HELP_STR_THE_COMMANDO = 0x00005096,  /* "The Commando" */
    HELP_STR_DOUBLE_DARLA = 0x00005097,  /* "Double Darla" */
    HELP_STR_SNAGGLEBEAST = 0x00005098,  /* "Snagglebeast" */
    HELP_STR_CRACKER_JAK = 0x00005099,  /* "Cracker Jak" */
    HELP_STR_DO_THE_ROBOT = 0x0000509A,  /* "Do the Robot" */
    HELP_STR_REVOLVERATOR = 0x0000509B,  /* "Revolverator" */
    HELP_STR_CHOMPER = 0x0000509C,  /* "Chomper" */
    HELP_STR_BIG_AL = 0x0000509D,  /* "Big Al" */
    HELP_STR_DREKS_REVENGE = 0x0000509E,  /* "Drek's Revenge" */
    HELP_STR_QWARKTASTIC_2 = 0x0000509F,  /* "Qwarktastic" */
    HELP_STR_TWISTY_MCMARX = 0x000050A0,  /* "Twisty McMarx" */
    HELP_STR_TRY_AGAIN = 0x000050A1,  /* "Try Again" */
    HELP_STR_NO_NEW_TIME = 0x000050A2,  /* "No New Time" */
    HELP_STR_NEW_BEST_TIME = 0x000050A3,  /* "New Best Time!" */
    HELP_STR_NO_NEW_SCORE = 0x000050A4,  /* "No New Score" */
    HELP_STR_NEW_HIGH_SCORE = 0x000050A5,  /* "New High Score!" */
    HELP_STR_SCORE = 0x000050A6,  /* "Score" */
    HELP_STR_FLIP = 0x000050A7,  /* "flip" */
    HELP_STR_FLIPS = 0x000050A8,  /* "flips" */
    HELP_STR_CREATED_AND_DEVELOPED_BYINSOMNIAC_0x50A9 = 0x000050A9,  /* "Created and Developed byInsomniac Games" */
    HELP_STR_JI_AHN = 0x000050AA,  /* "Ji Ahn" */
    HELP_STR_BRIAN_ALLGEIER = 0x000050AB,  /* "Brian Allgeier" */
    HELP_STR_GREG_BALDWIN = 0x000050AC,  /* "Greg Baldwin" */
    HELP_STR_TOM_BARLOW = 0x000050AD,  /* "Tom Barlow" */
    HELP_STR_TJ_BORDELON = 0x000050AE,  /* "T.J. Bordelon" */
    HELP_STR_SUNNY_CHEN = 0x000050AF,  /* "Sunny Chen" */
    HELP_STR_RYAN_DENNISTON = 0x000050B0,  /* "Ryan Denniston" */
    HELP_STR_CHAD_DEZERN = 0x000050B1,  /* "Chad Dezern" */
    HELP_STR_GAVIN_DODD = 0x000050B2,  /* "Gavin Dodd" */
    HELP_STR_STEPHANIE_DUKE = 0x000050B3,  /* "Stephanie Duke" */
    HELP_STR_JACKIE_EVANOCHICK = 0x000050B4,  /* "Jackie Evanochick" */
    HELP_STR_JOHN_FIORITO = 0x000050B5,  /* "John Fiorito" */
    HELP_STR_TONY_GARCIA = 0x000050B6,  /* "Tony Garcia" */
    HELP_STR_CRAIG_GOODMAN = 0x000050B7,  /* "Craig Goodman" */
    HELP_STR_DAVE_GUERTIN = 0x000050B8,  /* "Dave Guertin" */
    HELP_STR_DAVE_HANCOCK = 0x000050B9,  /* "Dave Hancock" */
    HELP_STR_JARED_HARDY = 0x000050BA,  /* "Jared Hardy" */
    HELP_STR_ALEX_HASTINGS = 0x000050BB,  /* "Alex Hastings" */
    HELP_STR_BRIAN_HASTINGS = 0x000050BC,  /* "Brian Hastings" */
    HELP_STR_PETER_HASTINGS = 0x000050BD,  /* "Peter Hastings" */
    HELP_STR_MOSES_HOOD = 0x000050BE,  /* "Moses Hood" */
    HELP_STR_DAN_JOHNSON = 0x000050BF,  /* "Dan Johnson" */
    HELP_STR_JAMES_JUSTIN = 0x000050C0,  /* "James Justin" */
    HELP_STR_JOHN_LALLY = 0x000050C1,  /* "John Lally" */
    HELP_STR_JAY_KOOTTARAPPALLIL = 0x000050C2,  /* "Jay Koottarappallil" */
    HELP_STR_STEVE_MARTIN = 0x000050C3,  /* "Steve Martin" */
    HELP_STR_LESLEY_MATHIESON = 0x000050C4,  /* "Lesley Mathieson" */
    HELP_STR_ROLF_MOHR = 0x000050C5,  /* "Rolf Mohr" */
    HELP_STR_COLIN_MUNSON = 0x000050C6,  /* "Colin Munson" */
    HELP_STR_LLOYD_MURPHY = 0x000050C7,  /* "Lloyd Murphy" */
    HELP_STR_TED_PRICE = 0x000050C8,  /* "Ted Price" */
    HELP_STR_MARK_REIS = 0x000050C9,  /* "Mark Reis" */
    HELP_STR_ROBERTO_RODRIGUEZ = 0x000050CA,  /* "Roberto Rodriguez" */
    HELP_STR_JASON_SKILES = 0x000050CB,  /* "Jason Skiles" */
    HELP_STR_CRAIG_STITT = 0x000050CC,  /* "Craig Stitt" */
    HELP_STR_MIKE_STOUT = 0x000050CD,  /* "Mike Stout" */
    HELP_STR_CHUCK_SUONG = 0x000050CE,  /* "Chuck Suong" */
    HELP_STR_TIM_TRZEPACZ = 0x000050CF,  /* "Tim Trzepacz" */
    HELP_STR_OLIVER_WADE = 0x000050D0,  /* "Oliver Wade" */
    HELP_STR_BILL_WRIGHT = 0x000050D1,  /* "Bill Wright" */
    HELP_STR_JOHN_WU = 0x000050D2,  /* "John Wu" */
    HELP_STR_MIKE_YAZIJIAN = 0x000050D3,  /* "Mike Yazijian" */
    HELP_STR_CERNY_GAMES = 0x000050D4,  /* "Cerny Games" */
    HELP_STR_MARK_CERNYDESIGN_CONSULTANT = 0x000050D5,  /* "Mark CernyDesign Consultant" */
    HELP_STR_PUBLISHED_BYSONY_COMPUTER_ENTERTAINMENT_0x50D6 = 0x000050D6,  /* "Published bySony Computer Entertainment America" */
    HELP_STR_PRODUCERGRADY_HUNT = 0x000050D7,  /* "ProducerGrady Hunt" */
    HELP_STR_ASSOCIATE_PRODUCERSAM_THOMPSON = 0x000050D8,  /* "Associate ProducerSam Thompson" */
    HELP_STR_ASSISTANT_PRODUCERGREG_SUPERGREG_PHILLIPS = 0x000050D9,  /* "Assistant ProducerGreg 'Supergreg' Phillips" */
    HELP_STR_DIRECTOR_OF_PRODUCT_DEVELOPMENTCONNIE_0x50DA = 0x000050DA,  /* "Director of Product DevelopmentConnie Booth" */
    HELP_STR_VICE_PRESIDENT_OF_PRODUCT_0x50DB = 0x000050DB,  /* "Vice President of Product DevelopmentShuhei Yoshida" */
    HELP_STR_DIRECTOR_OF_MARKETINGAMI_BLAIRE = 0x000050DC,  /* "Director of MarketingAmi Blaire" */
    HELP_STR_ASSOCIATE_PRODUCT_MANAGERSHELLEY_ASHITOMI = 0x000050DD,  /* "Associate Product ManagerShelley Ashitomi" */
    HELP_STR_DIRECTOR_OF_PUBLIC_RELATIONSMOLLY_0x50DE = 0x000050DE,  /* "Director of Public RelationsMolly Smith" */
    HELP_STR_PUBLIC_RELATIONS_MANAGERCHARLOTTE_PANTHER = 0x000050DF,  /* "Public Relations ManagerCharlotte Panther" */
    HELP_STR_PRODUCT_MARKETING_SPECIALISTSTINA_CASALINOALYSSA_0x50E0 = 0x000050E0,  /* "Product Marketing SpecialistsTina CasalinoAlyssa Casella" */
    HELP_STR_DIRECTOR_OF_QAMICHAEL_BLACKLEDGE = 0x000050E1,  /* "Director of QAMichael Blackledge" */
    HELP_STR_SENIOR_MANAGER_OF_QARITCHARD_0x50E2 = 0x000050E2,  /* "Senior Manager of QARitchard Markelz" */
    HELP_STR_CORE_MANAGER_OF_QASAM_0x50E3 = 0x000050E3,  /* "Core Manager of QASam Bradley" */
    HELP_STR_PROJECT_COORDINATORERIC_IPPOLITO = 0x000050E4,  /* "Project CoordinatorEric Ippolito" */
    HELP_STR_TECHNOLOGY_MANAGERKEVIN_SIMMONS = 0x000050E5,  /* "Technology ManagerKevin Simmons" */
    HELP_STR_LAB_TECHNICIANARA_DEMIRJIAN = 0x000050E6,  /* "Lab TechnicianAra Demirjian" */
    HELP_STR_LEAD_QA_ANALYSTIAN_MCGUINNESSANDREW_0x50E7 = 0x000050E7,  /* "Lead QA AnalystIan McGuinnessAndrew Woodworth" */
    HELP_STR_ASSISTANT_LEAD_QA_ANALYSTJONATHAN_0x50E8 = 0x000050E8,  /* "Assistant Lead QA AnalystJonathan Quilo" */
    HELP_STR_QA_ANALYSTS = 0x000050E9,  /* "QA Analysts" */
    HELP_STR_ANTHONY_AMOS = 0x000050EA,  /* "Anthony Amos" */
    HELP_STR_DAVID_ONG = 0x000050EB,  /* "David Ong" */
    HELP_STR_EDGAR_GONZALEZ = 0x000050EC,  /* "Edgar Gonzalez" */
    HELP_STR_EDWARD_TOOMEY = 0x000050ED,  /* "Edward Toomey" */
    HELP_STR_ERNIE_TOTTEN = 0x000050EE,  /* "Ernie Totten" */
    HELP_STR_FRED_ACEBO = 0x000050EF,  /* "Fred Acebo" */
    HELP_STR_JACOB_FERNANDEZ = 0x000050F0,  /* "Jacob Fernandez" */
    HELP_STR_JAMES_DE_LA_O = 0x000050F1,  /* "James De La O" */
    HELP_STR_JOHN_MACINTOSH_IV = 0x000050F2,  /* "John MacIntosh IV" */
    HELP_STR_JONATHON_HARDY = 0x000050F3,  /* "Jonathon Hardy" */
    HELP_STR_MAEOLL_KIM = 0x000050F4,  /* "Maeoll Kim" */
    HELP_STR_MARCOS_RAMIREZ = 0x000050F5,  /* "Marcos Ramirez" */
    HELP_STR_MICHAEL_WANG = 0x000050F6,  /* "Michael Wang" */
    HELP_STR_PHIL_GUREVICH = 0x000050F7,  /* "Phil Gurevich" */
    HELP_STR_RICARDO_BEDOYA = 0x000050F8,  /* "Ricardo Bedoya" */
    HELP_STR_RICHARD_GATMAITAN = 0x000050F9,  /* "Richard Gatmaitan" */
    HELP_STR_RICKY_CHU = 0x000050FA,  /* "Ricky Chu" */
    HELP_STR_ROLANDO_RAMIS = 0x000050FB,  /* "Rolando Ramis" */
    HELP_STR_RONALD_JONES_II = 0x000050FC,  /* "Ronald Jones II" */
    HELP_STR_SETH_NIELSEN = 0x000050FD,  /* "Seth Nielsen" */
    HELP_STR_WILL_MEDINA_JR = 0x000050FE,  /* "Will Medina Jr." */
    HELP_STR_BRIAN_GILMORE = 0x000050FF,  /* "Brian Gilmore" */
    HELP_STR_COBALT_DENA = 0x00005100,  /* "Cobalt Dena" */
    HELP_STR_CHRIS_REWAK = 0x00005101,  /* "Chris Rewak" */
    HELP_STR_WILLIAM_HUGHES = 0x00005102,  /* "William Hughes" */
    HELP_STR_MICHAEL_WILSON = 0x00005103,  /* "Michael Wilson" */
    HELP_STR_KEVIN_CROALL = 0x00005104,  /* "Kevin Croall" */
    HELP_STR_LENNY_GORDON = 0x00005105,  /* "Lenny Gordon" */
    HELP_STR_PUBLISHED_BYSONY_COMPUTER_ENTERTAINMENT_0x5106 = 0x00005106,  /* "Published bySony Computer Entertainment Europe" */
    HELP_STR_PRODUCERDANIEL_BROOKE = 0x00005107,  /* "ProducerDaniel Brooke" */
    HELP_STR_EUROPEAN_SOFTWARE_MANAGERISABELLE_TOMATIS = 0x00005108,  /* "European Software ManagerIsabelle Tomatis" */
    HELP_STR_EUROPEAN_PR_MANAGERIMOGEN_BAKER = 0x00005109,  /* "European PR ManagerImogen Baker" */
    HELP_STR_QA_MANAGERGEOFF_RENS = 0x0000510A,  /* "QA ManagerGeoff Rens" */
    HELP_STR_INTERNAL_QA_MANAGERDAVE_PARKINSON = 0x0000510B,  /* "Internal QA ManagerDave Parkinson" */
    HELP_STR_INTERNAL_QA_SUPERVISORJIM_MCCABE = 0x0000510C,  /* "Internal QA SupervisorJim McCabe" */
    HELP_STR_TEAM_LEADERPHIL_GREEN = 0x0000510D,  /* "Team LeaderPhil Green" */
    HELP_STR_TESTERS = 0x0000510E,  /* "Testers:" */
    HELP_STR_IAN_CUNLIFFE = 0x0000510F,  /* "Ian Cunliffe" */
    HELP_STR_BARRIE_MITCHELL = 0x00005110,  /* "Barrie Mitchell" */
    HELP_STR_VINCENT_TSE = 0x00005111,  /* "Vincent Tse" */
    HELP_STR_DARREN_PERKINS = 0x00005112,  /* "Darren Perkins" */
    HELP_STR_MATTHEW_NUTTALL = 0x00005113,  /* "Matthew Nuttall" */
    HELP_STR_IAN_MCEVOY = 0x00005114,  /* "Ian McEvoy" */
    HELP_STR_TERRI_HARRISON = 0x00005115,  /* "Terri Harrison" */
    HELP_STR_CARL_SEDDON = 0x00005116,  /* "Carl Seddon" */
    HELP_STR_MARK_COONEY = 0x00005117,  /* "Mark Cooney" */
    HELP_STR_LEAD_TRC_AUDITORPAUL_FRENCH = 0x00005118,  /* "Lead TRC AuditorPaul French" */
    HELP_STR_TRC_AUDITORSJOHN_HALEMICHAEL_KENNEDY = 0x00005119,  /* "TRC AuditorsJohn HaleMichael Kennedy" */
    HELP_STR_QA_SUBMISSIONS_MANAGERSDAVE_BENNETTMARK_0x511A = 0x0000511A,  /* "QA Submissions ManagersDave BennettMark Pittam" */
    HELP_STR_MANUAL_AND_PACKAGING_TEXTRUSSELL_0x511B = 0x0000511B,  /* "Manual and Packaging TextRussell Coburn" */
    HELP_STR_MANUAL_AND_PACKAGING_DESIGNRICHARD_0x511C = 0x0000511C,  /* "Manual and Packaging DesignRichard Turner" */
    HELP_STR_QA_MANUAL_APPROVALSTEPHEN_GRIFFITHSKEITH_0x511D = 0x0000511D,  /* "QA Manual ApprovalStephen GriffithsKeith Derby" */
    HELP_STR_PLANNING_AND_LOCALISATION_MANAGERVANESSA_0x511E = 0x0000511E,  /* "Planning and Localisation ManagerVanessa Wood" */
    HELP_STR_SOFTWARE_OPERATIONS_COORDINATORMARY_GORST = 0x0000511F,  /* "Software Operations CoordinatorMary Gorst" */
    HELP_STR_LOCALISATION_COORDINATORGAELLE_LEYSOUR = 0x00005120,  /* "Localisation CoordinatorGaelle Leysour" */
    HELP_STR_LOCALISATION_LEAD_TESTERNADEGE_JOSA = 0x00005121,  /* "Localisation Lead TesterNadege Josa" */
    HELP_STR_LOCALISATION_TESTERS_FRENCHYANNICK_PAULETGAELLE_0x5122 = 0x00005122,  /* "Localisation Testers FrenchYannick PauletGaelle Grenapin" */
    HELP_STR_LOCALISATION_TESTERS_ITALIANSACHA_FELLICAGIANCINTO_0x5123 = 0x00005123,  /* "Localisation Testers ItalianSacha FellicaGiancinto Attanasio" */
    HELP_STR_LOCALISATION_TESTERS_GERMANNADINE_MARTINKATHARINE_0x5124 = 0x00005124,  /* "Localisation Testers GermanNadine MartinKatharine TropfDeniz Ulu" */
    HELP_STR_LOCALISATION_TESTERS_SPANISHYOLANDA_AKILMONICA_0x5125 = 0x00005125,  /* "Localisation Testers SpanishYolanda AkilMonica BelloJose Flores" */
    HELP_STR_SPECIAL_THANKS_FROM_SCEETO = 0x00005126,  /* "Special Thanks from SCEEto" */
    HELP_STR_NICK_MADDEN = 0x00005127,  /* "Nick Madden" */
    HELP_STR_EVERYONE_AT_SUBMISSIONS_QA = 0x00005128,  /* "Everyone at Submissions QA" */
    HELP_STR_EVERYONE_AT_THE_LOCALISATION_0x5129 = 0x00005129,  /* "Everyone at the Localisation Houses" */
    HELP_STR_MUSIC_COMPOSED_AND_PERFORMEDBY = 0x00005136,  /* "Music Composed and Performedby" */
    HELP_STR_DAVID_BERGEAUD = 0x00005137,  /* "David Bergeaud" */
    HELP_STR_VOICE_ACTORS = 0x00005138,  /* "Voice Actors" */
    HELP_STR_MIKEY_KELLEYASRATCHET = 0x00005139,  /* "Mikey KelleyasRatchet" */
    HELP_STR_DAVID_KAYEASCLANKSCRAP_MERCHANTBOBBLARG_SCIENTIST = 0x0000513A,  /* "David KayeasClankScrap MerchantBobBlarg Scientist" */
    HELP_STR_JIM_WARDASCAPTAIN_QWARKDESERTERGADGETRON_CEO = 0x0000513B,  /* "Jim WardasCaptain QwarkDeserterGadgetron CEO" */
    HELP_STR_KEVIN_MICHAEL_RICHARDSONASDREKCOMMANDOANNOUNCERBOUNCER = 0x0000513C,  /* "Kevin Michael RichardsonasDrekCommandoAnnouncerBouncer" */
    HELP_STR_MONA_MARSHALASHELPDESK_GIRLEDWINAQWARKS_FITNESS_0x513D = 0x0000513D,  /* "Mona MarshalasHelpdesk GirlEd(wina)Qwark's Fitness Trainer" */
    HELP_STR_NEIL_FLYNNASWATERWORKERSKID_MCMARXROBOT_LIEUTENANTINVENTORFOREMAN = 0x0000513E,  /* "Neil FlynnasWaterWorkerSkid McMarxRobot LieutenantInventorForeman" */
    HELP_STR_CHAD_EINBINDERASRESORT_OWNER_RYNO_0x513F = 0x0000513F,  /* "Chad EinbinderasResort OwnerR.Y.N.O. Salesman" */
    HELP_STR_JACK_ANGELASMAYOR = 0x00005140,  /* "Jack AngelasMayor" */
    HELP_STR_SYLVIA_AMERITOASDARLA_GRATCHMELISSA_DISNEYAS_0x5141 = 0x00005141,  /* "Sylvia AmeritoasDarla GratchMelissa DisneyasHoverboard Girl" */
    HELP_STR_CHRIS_HATFIELDASBIG_AL = 0x00005142,  /* "Chris HatfieldasBig Al" */
    HELP_STR_THE_RATCHET_AND_CLANK_0x5143 = 0x00005143,  /* "The Ratchet and Clank background enginewas developed using proprietary techniquesand code created by Naughty Dog, Inc." */
    HELP_STR_SPECIAL_THANKS_FROM_INSOMNIACTO = 0x00005144,  /* "Special Thanks from Insomniacto" */
    HELP_STR_AKIRA_SATO = 0x00005145,  /* "Akira Sato" */
    HELP_STR_KAZ_HIRAI = 0x00005146,  /* "Kaz Hirai" */
    HELP_STR_JACK_TRETTON = 0x00005147,  /* "Jack Tretton" */
    HELP_STR_ANDREW_HOUSE = 0x00005148,  /* "Andrew House" */
    HELP_STR_PHIL_HARRISON = 0x00005149,  /* "Phil Harrison" */
    HELP_STR_SHAWN_LAYDEN = 0x0000514A,  /* "Shawn Layden" */
    HELP_STR_ALL_OF_THE_NAUGHTY_0x514B = 0x0000514B,  /* "All of the Naughty Dogs" */
    HELP_STR_BUZZ_BURROWES = 0x0000514C,  /* "Buzz Burrowes" */
    HELP_STR_GARY_BARTH = 0x0000514D,  /* "Gary Barth" */
    HELP_STR_RYAN_SCHNEIDER = 0x0000514E,  /* "Ryan Schneider" */
    HELP_STR_ELIZABETH_ROSENBERG = 0x0000514F,  /* "Elizabeth Rosenberg" */
    HELP_STR_MIKE_GOLLUMAND_THE_SOUND_0x5150 = 0x00005150,  /* "Mike Gollumand the sound production crew at Warner Bros." */
    HELP_STR_CAROLINE_TRUJILLO = 0x00005151,  /* "Caroline Trujillo" */
    HELP_STR_STEVEN_BATISTE = 0x00005152,  /* "Steven Batiste" */
    HELP_STR_KATHIE_BLACK = 0x00005153,  /* "Kathie Black" */
    HELP_STR_OUR_PATIENT_SPOUSES_CHILDREN_0x5154 = 0x00005154,  /* "Our patient spouses, children, parents, girlfriends, boyfriends and pets" */
    HELP_STR_WE_WOULD_LIKE_TO_0x515E = 0x0000515E,  /* "We would like to thank eachindividual at Sony Computer Entertainment Americafor their contributions, support anddedication to the success ofRatchet and Clank with specialrecognition to the ExecutiveManagement team including:" */
    HELP_STR_KAZ_HIRAI_2 = 0x0000515F,  /* "Kaz Hirai" */
    HELP_STR_JIM_BASS = 0x00005160,  /* "Jim Bass" */
    HELP_STR_MASAYUKI_CHATANI = 0x00005161,  /* "Masayuki Chatani" */
    HELP_STR_ANDREW_HOUSE_2 = 0x00005162,  /* "Andrew House" */
    HELP_STR_STEVE_ROSS = 0x00005163,  /* "Steve Ross" */
    HELP_STR_RILEY_RUSSELL = 0x00005164,  /* "Riley Russell" */
    HELP_STR_JACK_TRETTON_2 = 0x00005165,  /* "Jack Tretton" */
    HELP_STR_AND_MARILYN_WEYANT = 0x00005166,  /* "and Marilyn Weyant" */
    HELP_STR_WE_WOULD_ALSO_LIKE_0x5167 = 0x00005167,  /* "We would also like to extend a special thanks to:" */
    HELP_STR_AKIRA_SATO_2 = 0x00005168,  /* "Akira Sato" */
    HELP_STR_PHIL_HARRISON_2 = 0x00005169,  /* "Phil Harrison" */
    HELP_STR_SHAWN_LAYDEN_2 = 0x0000516A,  /* "Shawn Layden" */
    HELP_STR_ALL_OF_THE_NAUGHTY_0x516B = 0x0000516B,  /* "All of the Naughty Dogs" */
    HELP_STR_BUZZ_BURROWES_2 = 0x0000516C,  /* "Buzz Burrowes" */
    HELP_STR_GARY_BARTH_2 = 0x0000516D,  /* "Gary Barth" */
    HELP_STR_RYAN_SCHNEIDER_2 = 0x0000516E,  /* "Ryan Schneider" */
    HELP_STR_ELIZABETH_ROSENBERG_2 = 0x0000516F,  /* "Elizabeth Rosenberg" */
    HELP_STR_MIKE_GOLLUMAND_THE_SOUND_0x5170 = 0x00005170,  /* "Mike Gollumand the sound production crew at Warner Bros." */
    HELP_STR_CAROLINE_TRUJILLO_2 = 0x00005171,  /* "Caroline Trujillo" */
    HELP_STR_STEVEN_BATISTE_2 = 0x00005172,  /* "Steven Batiste" */
    HELP_STR_KATHIE_BLACK_2 = 0x00005173,  /* "Kathie Black" */
    HELP_STR_AND_OF_COURSEOUR_PATIENT_0x5174 = 0x00005174,  /* "And of courseour patient spouses, children, parentsgirlfriends, boyfriends and pets" */
    HELP_STR_NO_CHICKENS_WERE_HARMED_0x5175 = 0x00005175,  /* "No chickens were harmed in the making of this game" */
    HELP_STR_TRICK_SCORE = 0x00005176,  /* "Trick Score" */
    HELP_STR_POSE = 0x00005177,  /* "Pose" */
    HELP_STR_POSES = 0x00005178,  /* "Poses" */
    HELP_STR_COURSE_RECORD = 0x00005179,  /* "Course Record" */
    HELP_STR_NEW_COURSE_RECORD = 0x0000517A,  /* "New Course Record!" */
    HELP_STR_NEW_HIGH_TRICKS_SCORE = 0x0000517B,  /* "New High Tricks Score!" */
    HELP_STR_GET_YOUR_PRIZE = 0x0000517C,  /* " Get Your Prize" */
    HELP_STR_RACE_AGAIN = 0x0000517D,  /* "Race Again" */
    HELP_STR_GONZO = 0x0000517E,  /* "Gonzo" */
    HELP_STR_SCRATCHER = 0x0000517F,  /* "Scratcher" */
    HELP_STR_TIP_TWEAK = 0x00005180,  /* "Tip Tweak" */
    HELP_STR_CRUNCHY = 0x00005181,  /* "Crunchy" */
    HELP_STR_USE_GOLD_BOLTS_TO_0x5182 = 0x00005182,  /* "Use Gold Bolts to buy Gold Weapons!" */
    HELP_STR_OBTAIN_ALL_GOLD_WEAPONS_0x5183 = 0x00005183,  /* "Obtain all Gold Weapons and Skill Points to unlock more goodies!" */
    HELP_STR_START_NEW_GAME_0x5184 = 0x00005184,  /* " Start new game with current weapons and bolts" */
    HELP_STR_TIMEWARP_TO_BEFORE_0x5185 = 0x00005185,  /* " Timewarp to before you defeated Drek." */
    HELP_STR_CHECK_THE_GOODIES_MENU_0x5186 = 0x00005186,  /* "Check the goodies menu for cool features!" */
    HELP_STR_THESE_ARE_SOME_OF_0x5187 = 0x00005187,  /* "These are some of the concept sketches for Ratchet. We decided early on that he would be a bipedal alien creature with fur. And if anyone asks you, Ratchet is a Lombax. " */
    HELP_STR_CLANK_TOO_WENT_THROUGH_0x5188 = 0x00005188,  /* "Clank too went through many forms. He was originally even younger looking with a bigger head and smaller body. In fact, at first Clank was three much smaller robots but in the end we decided to use just one so that we could develop his personality more easily." */
    HELP_STR_AND_HERE_WE_HAVE_0x5189 = 0x00005189,  /* "And here we have the final sketch for our two main characters. Ratchet came into existence on paper for the first time within two weeks of the initial idea for the game. This final sketch was done about three months later." */
    HELP_STR_FORT_KRONTOS_ON_BATALIA_0x518A = 0x0000518A,  /* "Fort Krontos on Batalia came from the top sketch. We wanted to create forested islands under aerial attack. Then we turned it into more of tropical fort. Kind of the way development goes sometimes.The bottom sketch was one of the many from which we stole pieces for various levels..." */
    HELP_STR_THESE_CLIFF_HUGGING_STRUCTURES_EVOLVED_0x518B = 0x0000518B,  /* "These cliff-hugging structures evolved into the cliffside machinery you can see in parts of the Logging Site on Planet Eudora. They were originally part of a populated city but we decided to make this a robot-only area." */
    HELP_STR_THIS_IS_AN_ELEMENT_0x518C = 0x0000518C,  /* "This is an element from the robot factory exterior on Planet Quartu. The factory on this planet is where Clank is made at the beginning of the game." */
    HELP_STR_THE_TOP_SKETCH_IS_0x518D = 0x0000518D,  /* "The top sketch is an early drawing of Blarg Depot on Planet Gaspar. The bottom is the production design for Blackwater City on Planet Rilgar." */
    HELP_STR_THE_BOMB_FACTORY_ON_0x518E = 0x0000518E,  /* "The Bomb Factory on Planet Hoven was derived from these sketches. Our original idea was that the inhabitants were mining ice and shipping it offworld.But then we decided that the Blarg should invade and convert all the processing plants to munitions factories. Blarg equals bad news. " */
    HELP_STR_A_HANGING_POWER_SOURCE_0x518F = 0x0000518F,  /* "A hanging power source for one of our factories. Can you guess which one?" */
    HELP_STR_THE_TOP_DRAWING_SHOWS_0x5190 = 0x00005190,  /* "The top drawing shows off early concepts for the Logging Site on Planet Eudora. This was one of our first worlds and our initial goal was to create a forest-city. It changed drastically during productionThe bottom sketch shows off peaceful structures from the Bomb Factory on Planet Hoven." */
    HELP_STR_GENERATOR_CONCEPTS_FOR_GORDA_0x5191 = 0x00005191,  /* "Generator concepts for Gorda City on Planet Oltanis. Because the city is plagued by lightning storms, the inhabitants use the generators to attract the lightning and convert it into useful energy.Unfortunately Drek wants the generators for his new planets and the citizens don't stand a chance." */
    HELP_STR_ONE_OF_THE_VERY_0x5192 = 0x00005192,  /* "One of the very first levels we prototyped was Metropolis on Planet Kerwan. We wanted lots of greenery built into the retro sci-fi buildings to create a unique contrast. We ended up removing most of the bronze caps though because they began to clash with the rest of the city.This world was one of the first big ones we built and almost started a war between the designers and the artists." */
    HELP_STR_THIS_IS_THE_FIRST_0x5193 = 0x00005193,  /* "This is the first concept for Qwark's HQ on Planet Umbris. We removed the lightning rods after we realized that it made the central structure look too small.The general idea for Qwark's HQ was that it should be very reminiscent of a WWII battlefield replete with bunkers, machine guns and barbed wire." */
    HELP_STR_HERES_A_BUILDING_STUDY_0x5194 = 0x00005194,  /* "Here's a building study for one of the structures near Qwark's trailer in Blackwater City. We ended up modifying it significantly though and the final result is a bit different�" */
    HELP_STR_THIS_IS_A_GOOD_0x5195 = 0x00005195,  /* "This is a good example of the palette studies we create for every world. This one was for Fort Krontos on Planet Batalia.We ended up changing the weather from a sunny day to a rainstorm but the color palette didn't vary much from this painting." */
    HELP_STR_TWO_EXAMPLES_OF_THE_0x5196 = 0x00005196,  /* "Two examples of the character sheets we use to model the enemies in the game. The top is a Blarg Trooper while the Blarg Commander is on the bottom." */
    HELP_STR_WE_LOVE_OUR_ROBOTS_0x5197 = 0x00005197,  /* "We love our robots! These are some of the many head designs we created for the robot troops who fight Ratchet. And if you look closely you can pick out our Animation Director and our Lead Character Designer. " */
    HELP_STR_HERES_RATCHETS_FIRST_SHIP_0x5198 = 0x00005198,  /* "Here's Ratchet's first ship. Too bad he wrecks it so early in the game. We wanted it to be a real homemade job - held together by chewing gum and wire. We still can't agree on exactly why he crashed it on Planet Novalis�" */
    HELP_STR_FINISHED_SKETCHES_FOR_QWARKS_0x5199 = 0x00005199,  /* "Finished sketches for Qwark's ship and the Courier ship that Ratchet and Clank acquire. The idea was that the Courier ship would be a slow, clunky, durable vehicle - kind of like a mail truck.Qwark's ship on the other hand was designed as a luxury craft - not too fast either but stylish and comfortable." */
    HELP_STR_THIS_IS_THE_ORIGINAL_0x519A = 0x0000519A,  /* "This is the original sketch for the Blarg Fighter that Ratchet and Clank pick up on Gemlik Base. We were going for sleek but deadly�" */
    HELP_STR_MANY_OF_THE_ENEMIES_0x519B = 0x0000519B,  /* "Many of the enemies in the game pilot vehicles. This one turned into a helicopter piloted by a Blarg Commander in Metropolis. He's a nasty one." */
    HELP_STR_THE_GRINDBOOTS_MINE_GLOVE_0x519C = 0x0000519C,  /* "The Grindboots, Mine Glove and what originally was the Defense Drone Glove. We changed the way Defense Drones work midway through the project so we no longer needed that glove." */
    HELP_STR_HERES_ONE_OF_OUR_0x519D = 0x0000519D,  /* "Here's one of our concepts for Giant Clank. Unfortunately the huge shoulder-mounted guns didn't make it in because they just weren't practical. But we did manage to keep Ratchet on Clank's back." */
    HELP_STR_SOME_FUN_ENEMY_DESIGNS_0x519E = 0x0000519E,  /* "Some fun enemy designs. One made it into to the game, four didn't. Can you pick the winner?" */
    HELP_STR_THE_MANY_FACES_OF_0x519F = 0x0000519F,  /* "The many faces of Big Al. This was the first NPC (non player character) we put into the game. He's probably what most people think game developers look like�" */
    HELP_STR_ONE_OF_THE_WEAPONS_0x51A0 = 0x000051A0,  /* "One of the weapons that went through many iterations on paper was Ratchet's wrench. We didn't want something too generic plus it had to function as a tool and a weapon at the same time.It's mistakenly called an 'axe' by many but the label is appropriate in some respects since you probably wouldn't want to get whacked with it." */
    HELP_STR_DESIGNS_FOR_THE_VISIBOMB_0x51A1 = 0x000051A1,  /* "Designs for the Visibomb Gun (top) and the Suck Cannon (bottom). The Suck Cannon was one of the first weapons we designed and one of the few where the name stayed the same throughout the development process. It just had such a nice ring to it�" */
    HELP_STR_THE_TOP_TWO_DESIGNS_0x51A2 = 0x000051A2,  /* "The top two designs are final versions of the Hydro-Pack. The bottom sketches are the designs for the Glove of Doom and Bomb Glove.The Glove of Doom is an office favorite�" */
    HELP_STR_ANOTHER_EARLY_VERSION_OF_0x51A3 = 0x000051A3,  /* "Another early version of Ratchet. Notice the different proportions, lack of eyebrows and stripes. This was also an early box cover concept�" */
    HELP_STR_THIS_ONE_SHOULD_LOOK_0x51A4 = 0x000051A4,  /* "This one should look familiar - the cover for the U.S. game box was derived from it. But more importantly, it was the first image of Ratchet unveiled to the world in March, 2002." */
    HELP_STR_NO_MOVIES = 0x000051A5,  /* "No movies." */
    HELP_STR_BATALIA_CHRONICLES = 0x000051A6,  /* "BATALIA CHRONICLES" */
    HELP_STR_LONE_COMMANDO_WINS_WAR = 0x000051A7,  /* "LONE COMMANDO WINS WAR�" */
    HELP_STR_OR_SO_HE_SAYS = 0x000051A8,  /* "�or so he says" */
    HELP_STR_REINFORCEMENTS_HAVE_ARRIVED = 0x000051A9,  /* "REINFORCEMENTS HAVE ARRIVED!" */
    HELP_STR_WHAT_TOOK_THEM_SO_0x51AA = 0x000051AA,  /* "WHAT TOOK THEM SO LONG?" */
    HELP_STR_OUTPOST_X11_UPDATES = 0x000051AB,  /* "OUTPOST X11 UPDATES" */
    HELP_STR_READER_DIGESTED = 0x000051AC,  /* "Reader Digested" */
    HELP_STR_HOW_LONG_IS_YOUR_0x51AD = 0x000051AD,  /* "How Long Is Your Wrench?" */
    HELP_STR_WHICH_NANOTECH_DO_YOU_0x51AE = 0x000051AE,  /* "Which Nanotech Do You Really Need?" */
    HELP_STR_AN_AMOEBOID_ATE_HER_0x51AF = 0x000051AF,  /* "An Amoeboid Ate Her And Now She's IN LOVE" */
    HELP_STR_THE_MOTION_PICTURE = 0x000051B0,  /* "The Motion Picture" */
    HELP_STR_PRIME = 0x000051B1,  /* "PRIME" */
    HELP_STR_ROBOT_OF_THE_YEAR = 0x000051B2,  /* "Robot of the Year!" */
    HELP_STR_AN_EXCLUSIVE_LOOK_AT_0x51B3 = 0x000051B3,  /* "An exclusive look at how Clank saved us all" */
    HELP_STR_POPULAR_PLUMBERS = 0x000051B4,  /* "Popular Plumbers" */
    HELP_STR_WAYS_TO_CLEAN_0x51B5 = 0x000051B5,  /* "101 WAYS TO CLEAN YOUR PIPES" */
    HELP_STR_WILL_PLUMBING_EVER_BE_0x51B6 = 0x000051B6,  /* "Will plumbing ever be the same?" */
    HELP_STR_THE_WATERWORKER_ASKS_THE_0x51B7 = 0x000051B7,  /* "The WaterWorker asks the same question every day" */
    HELP_STR_A_TRUE_STORY = 0x000051B8,  /* "A TRUE STORY" */
    HELP_STR_I_SAVED_THE_GALAXY_0x51B9 = 0x000051B9,  /* "I SAVED THE GALAXY FROM AN EVIL MUTATED STRAIN OF DRY ROT" */
    HELP_STR_I_KID_YOU_NOT = 0x000051BA,  /* "I KID YOU NOT" */
    HELP_STR_TIPS_TO_FIXING_DERELICT_0x51BB = 0x000051BB,  /* "TIPS TO FIXING DERELICT TURRETS" */
    HELP_STR_HYGEINATOR = 0x000051BC,  /* "Hygeinator" */
    HELP_STR_ZOOMERATOR_2 = 0x000051BD,  /* "Zoomerator" */
    HELP_STR_HOTBOTS = 0x000051BE,  /* "HOTBOTS" */
    HELP_STR_ENTERTAINMENT_FOR_ROBOTS = 0x000051BF,  /* "ENTERTAINMENT FOR ROBOTS" */
    HELP_STR_OIL_AND_GEARS = 0x000051C0,  /* "OIL AND GEARS" */
    HELP_STR_THE_BEST_LUBRICATION_FOR_0x51C1 = 0x000051C1,  /* "THE BEST LUBRICATION FOR YOUR SENSITIVE PARTS" */
    HELP_STR_TOP_50 = 0x000051C2,  /* "TOP 50" */
    HELP_STR_ROBOT_ACTORS = 0x000051C3,  /* "ROBOT ACTORS" */
    HELP_STR_TURBO_TWINS = 0x000051C4,  /* "TURBO TWINS" */
    HELP_STR_HELGAS_WORKOUT_PLAN = 0x000051C5,  /* "HELGA'S WORKOUT PLAN" */
    HELP_STR_CPU_OVERCLOCKS = 0x000051C6,  /* "CPU OVERCLOCKS" */
    HELP_STR_IMPROVES_PERFOMANCE_AND_SATISFACTION = 0x000051C7,  /* "IMPROVES PERFOMANCE AND SATISFACTION" */
    HELP_STR_HELPGIRL = 0x000051C8,  /* "HELPGIRL" */
    HELP_STR_SHOWS_OFF_HER = 0x000051C9,  /* "SHOWS OFF HER" */
    HELP_STR_SERVOS = 0x000051CA,  /* "SERVOS" */
    HELP_STR_INTERVIEW = 0x000051CB,  /* "INTERVIEW" */
    HELP_STR_XVB8 = 0x000051CC,  /* "XVB8" */
    HELP_STR_MODELS = 0x000051CD,  /* "MODELS" */
    HELP_STR_PARTY = 0x000051CE,  /* "PARTY" */
    HELP_STR_AT_THE = 0x000051CF,  /* "AT THE" */
    HELP_STR_HOTBOT = 0x000051D0,  /* "HOTBOT" */
    HELP_STR_MANSION = 0x000051D1,  /* "MANSION" */
    HELP_STR_TOOLS_EXPRESS = 0x000051D2,  /* "TOOLS EXPRESS" */
    HELP_STR_EXTEND_THE_LIFE_OF_0x51D3 = 0x000051D3,  /* "EXTEND THE LIFE OF YOUR WRENCH" */
    HELP_STR_THE_INTERSTELLAR = 0x000051D4,  /* "THE INTERSTELLAR" */
    HELP_STR_NOSEY_NEWS = 0x000051D5,  /* "NOSEY NEWS" */
    HELP_STR_WASHED_UP = 0x000051D6,  /* "WASHED UP" */
    HELP_STR_ILL_DO_ANYTHING_FOR_0x51D7 = 0x000051D7,  /* """I'll do anything for a few bolts"" - Qwark" */
    HELP_STR_CANDID_PHOTOS_INSIDE = 0x000051D8,  /* "CANDID PHOTOS INSIDE" */
    HELP_STR_ROBOT_CAUGHT_IN_THE_0x51D9 = 0x000051D9,  /* "Robot caught in the act" */
    HELP_STR_RATCHETS_LOVE_INTEREST = 0x000051DA,  /* "Ratchet's love interest" */
    HELP_STR_SHOCKING_NEWS_ABOUT_DREK = 0x000051DB,  /* "Shocking news about DREK" */
    HELP_STR_THE_RACE_WAS_FIXED = 0x000051DC,  /* "The race was fixed" */
    HELP_STR_FITNESS_TIPS_FROM_QWARKS_0x51DD = 0x000051DD,  /* "Fitness tips from Qwark's trainer" */
    HELP_STR_BLARG_TROOPS_AT_EACH_0x51DE = 0x000051DE,  /* "Blarg Troops at each others' throats" */
    HELP_STR_THE_TRUTH = 0x000051DF,  /* "THE TRUTH" */
    HELP_STR_IS_SKID_HOOKED_ON_0x51E0 = 0x000051E0,  /* "IS SKID HOOKED ON NANO?" */
    HELP_STR_THE_RILGAR_TIMES = 0x000051E1,  /* "The Rilgar Times" */
    HELP_STR_RYNO_SALESMAN_PLEADS_NOT_0x51E2 = 0x000051E2,  /* "R.Y.N.O. salesman pleads not guilty!" */
    HELP_STR_NOVALIS_NATIVE_CLAIMS_HIS_0x51E3 = 0x000051E3,  /* "Novalis native claims his brother turned into a chicken!" */
    HELP_STR_AMOEBOID_ATTACK = 0x000051E4,  /* "Amoeboid Attack" */
    HELP_STR_HOVER_BOARDER = 0x000051E5,  /* "HOVER BOARDER" */
    HELP_STR_THE_BEST_WAY_TO_0x51E6 = 0x000051E6,  /* """THE BEST WAY TO A MAN'S HEART IS THROUGH HIS RIBCAGE!""" */
    HELP_STR_Z400_SNEAK_PEEK = 0x000051E7,  /* "Z400 SNEAK PEEK" */
    HELP_STR_KILLER_COMBOS = 0x000051E8,  /* "KILLER COMBOS" */
    HELP_STR_BACK_BREAKING_MOVES = 0x000051E9,  /* "BACK BREAKING MOVES" */
    HELP_STR_ZOOMERATOR_GIVEAWAY = 0x000051EA,  /* "ZOOMERATOR GIVEAWAY" */
    HELP_STR_FREE_STUFF = 0x000051EB,  /* "FREE STUFF" */
    HELP_STR_FOR_ONLY_299 = 0x000051EC,  /* "for only 2.99" */
    HELP_STR_HOW_SKID_GETS_HIS_0x51ED = 0x000051ED,  /* "HOW SKID GETS HIS EXTRA ""ALTITUDE""" */
    HELP_STR_WIN = 0x000051EE,  /* "WIN!" */
    HELP_STR_HEAVY_ARTILLERY = 0x000051EF,  /* "HEAVY ARTILLERY" */
    HELP_STR_MORPHARAY_ENDS_GALACTIC_HUNGER = 0x000051F0,  /* "Morpharay ends galactic hunger" */
    HELP_STR_GADGETS_OF_TOMORROW = 0x000051F1,  /* "Gadgets of tomorrow" */
    HELP_STR_LATEST_INNOVATIONS = 0x000051F2,  /* "Latest innovations" */
    HELP_STR_VISIBOMB_REVIEW = 0x000051F3,  /* "Visibomb review" */
    HELP_STR_TOP_10_WEAPONS = 0x000051F4,  /* "Top 10 weapons" */
    HELP_STR_GADGETRONCON = 0x000051F5,  /* "GadgetronCon" */
    HELP_STR_THINK_YOU_COULD_HANDLE_0x51F6 = 0x000051F6,  /* "Think you could handle the R.Y.N.O.?" */
    HELP_STR_INTERVIEW_2 = 0x000051F7,  /* "INTERVIEW" */
    HELP_STR_VICTIMS_OF_THE_RYNO = 0x000051F8,  /* "Victims of the R.Y.N.O." */
    HELP_STR_UPGRADES = 0x000051F9,  /* "UPGRADES" */
    HELP_STR_LEARN_HOW_TO_GET_0x51FA = 0x000051FA,  /* "Learn how to get after market parts at an affordable price" */
    HELP_STR_D_TAILS = 0x000051FB,  /* "D-tails" */
    HELP_STR_THE_FURRY_MECHANIC_WHO_0x51FC = 0x000051FC,  /* "THE FURRY MECHANIC WHO CREATED A PANIC" */
    HELP_STR_DEADLY_GADGETS = 0x000051FD,  /* "DEADLY GADGETS" */
    HELP_STR_TOP_10_GIFT_IDEAS_0x51FE = 0x000051FE,  /* "TOP 10 GIFT IDEAS FOR THIS HOLIDAY SEASON" */
    HELP_STR_I_WAS_IN_REVERSE = 0x000051FF,  /* "I WAS IN REVERSE" */
    HELP_STR_RACETRACK_TRAGEDY_CLAIMS_FIVE_0x5200 = 0x00005200,  /* "RACETRACK TRAGEDY CLAIMS FIVE ROBOTS" */
    HELP_STR_HOMES__BUNKERS = 0x00005201,  /* "HOMES & BUNKERS" */
    HELP_STR_THE_1_OFFICIAL_GUIDE_0x5202 = 0x00005202,  /* "The 1 Official Guide to the Umbris System" */
    HELP_STR_BANK_SEIZES = 0x00005203,  /* "BANK SEIZES" */
    HELP_STR_QWARK_ESTATE = 0x00005204,  /* "QWARK ESTATE" */
    HELP_STR_AUCTION_BEGINS = 0x00005205,  /* "AUCTION BEGINS" */
    HELP_STR_NOW = 0x00005206,  /* "NOW!" */
    HELP_STR_NEW_SECTORS = 0x00005207,  /* "NEW SECTORS" */
    HELP_STR_EAST_UMBRIS = 0x00005208,  /* "East Umbris" */
    HELP_STR_CENTRAL_UMBRIS = 0x00005209,  /* "Central Umbris" */
    HELP_STR_WEENIEVILLE = 0x0000520A,  /* "Weenieville" */
    HELP_STR_SOUTH_X6B = 0x0000520B,  /* "South X6B" */
    HELP_STR_BLARG_TOWN = 0x0000520C,  /* "Blarg Town" */
    HELP_STR_RD_MOON = 0x0000520D,  /* "3rd Moon" */
    HELP_STR_UMBRIS_STATION = 0x0000520E,  /* "Umbris Station" */
    HELP_STR_QWARK_DISTRICT = 0x0000520F,  /* "Qwark District" */
    HELP_STR_FREE = 0x00005210,  /* "FREE" */
    HELP_STR_QWARKS_850_970_00099_0x5211 = 0x00005211,  /* "Qwark's 850 970 000.99 Estate" */
    HELP_STR_SOUND_EFFECTS_VOLUME = 0x00005212,  /* "Sound effects volume" */
    HELP_STR_MUSIC_VOLUME = 0x00005213,  /* "Music volume" */
    HELP_STR_TOGGLE_STEREO_MONO = 0x00005214,  /* "Toggle stereo/mono" */
    HELP_STR_MONO = 0x00005215,  /* "MONO" */
    HELP_STR_STEREO = 0x00005216,  /* "STEREO" */
    HELP_STR_EMPTY = 0x00005217,  /* "EMPTY" */
    HELP_STR_FAST = 0x00005218,  /* "Fast" */
    HELP_STR_MEDIUM = 0x00005219,  /* "Medium" */
    HELP_STR_SLOW = 0x0000521A,  /* "Slow" */
    HELP_STR_CHANGE_CAMERA_ROTATION_SPEED = 0x0000521B,  /* "Change camera rotation speed" */
    HELP_STR_WAIT = 0x0000521C,  /* "Wait" */
    HELP_STR_FOLLOW = 0x0000521D,  /* "Follow" */
    HELP_STR_ENTER = 0x0000521E,  /* "Enter" */
    HELP_STR_ATTACK = 0x0000521F,  /* "Attack" */
    HELP_STR_CREATED_AND_DEVELOPED_BY = 0x00005220,  /* "Created and Developed by" */
    HELP_STR_RATCHET_AND_CLANK_IS_0x5221 = 0x00005221,  /* "Ratchet and Clank is a trademark of Sony Computer Entertainment America, Inc." */
    HELP_STR_PRESS_START = 0x00005222,  /* "Press Start" */
    HELP_STR_SONY_COMPUTER_ENTERTAINMENT_EUROPE_0x5223 = 0x00005223,  /* "Sony Computer Entertainment Europe presents" */
    HELP_STR_ST = 0x00005224,  /* "1st" */
    HELP_STR_ND = 0x00005225,  /* "2nd" */
    HELP_STR_RD = 0x00005226,  /* "3rd" */
    HELP_STR_TH = 0x00005227,  /* "4th" */
    HELP_STR_TH_2 = 0x00005228,  /* "5th" */
    HELP_STR_QUIT = 0x00005229,  /* "Quit?" */
    HELP_STR_THE_SCREEN_WILL_NOW_0x522A = 0x0000522A,  /* "The screen will now change to 60Hz mode.  If the image is displayed incorrectly then your television does not support this mode.  If so, please wait 10 seconds and the screen will change back." */
    HELP_STR_THE_DISPLAY_IS_NOW_0x522B = 0x0000522B,  /* "The display is now in 60Hz mode.  Would you like to keep this mode?" */
    HELP_STR_THE_DISPLAY_HAS_BEEN_0x522C = 0x0000522C,  /* "The display has been restored to 50Hz mode." */
    HELP_STR_PRESS_ANY_BUTTON_TO_0x522D = 0x0000522D,  /* "Press any button to continue�" */
    HELP_STR_YOUVE_GOT = 0x0000522E,  /* "You've got:" */
    HELP_STR_D_OF_D_GOLD_0x522F = 0x0000522F,  /* "%d of %d Gold Bolts" */
    HELP_STR_D_OF_D_GOLD_0x5230 = 0x00005230,  /* "%d of %d Gold Weapons" */
    HELP_STR_D_OF_D_SKILL_0x5231 = 0x00005231,  /* "%d of %d Skill Points" */
    HELP_STR_CONTINUE_WITHOUT_SAVING = 0x00005232,  /* " Continue without saving" */
    HELP_STR_INFOBOT_FOR_PLANET_NOVALIS_0x0006 = 0x00000006,  /* "Infobot for Planet Novalis acquired" */
    HELP_STR_INFOBOT_FOR_PLANET_ARIDIA_0x03F1 = 0x000003F1,  /* "Infobot for Planet Aridia acquired" */
    HELP_STR_INFOBOT_FOR_PLANET_KERWAN_0x03F2 = 0x000003F2,  /* "Infobot for Planet Kerwan acquired" */
    HELP_STR_YOU_FOUND_THE_TRESPASSER = 0x000007DF,  /* "You found the Trespasser!" */
    HELP_STR_YOU_GOT_THE_SONIC_0x07E0 = 0x000007E0,  /* "You got the Sonic Summoner!" */
    HELP_STR_YOU_GOT_THE_HOVERBOARD = 0x000007E1,  /* "You got the Hoverboard!" */
    HELP_STR_INFOBOT_FOR_PLANET_EUDORA_0x0BC6 = 0x00000BC6,  /* "Infobot for Planet Eudora acquired" */
    HELP_STR_YOU_GOT_THE_HELI_PACK_0x0BC7 = 0x00000BC7,  /* "You got the Heli-Pack upgrade!" */
    HELP_STR_YOUVE_PURCHASED_A_SWINGSHOT = 0x00000BC8,  /* "You've purchased a Swingshot!" */
    HELP_STR_GOT_INFOBOT_FOR_BLARG_0x0FA6 = 0x00000FA6,  /* "Got Infobot for Blarg Tactical Station" */
    HELP_STR_YOU_FOUND_THE_SUCK_0x0FA7 = 0x00000FA7,  /* "You found the Suck Cannon!" */
    HELP_STR_INFOBOT_FOR_PLANET_UMBRIS_0x1394 = 0x00001394,  /* "Infobot for Planet Umbris acquired" */
    HELP_STR_YOU_WON_A_PLATINUM_0x1395 = 0x00001395,  /* "You won a Platinum Zoomerator!" */
    HELP_STR_YOU_JUST_PURCHASED_THE_0x1396 = 0x00001396,  /* "You just purchased the R.Y.N.O.!" */
    HELP_STR_YOU_JUST_SET_A_0x1397 = 0x00001397,  /* "You just set a new course record!" */
    HELP_STR_INFOBOT_FOR_PLANET_RILGAR_0x177B = 0x0000177B,  /* "Infobot for Planet Rilgar acquired" */
    HELP_STR_YOUVE_FOUND_THE_HYDRODISPLACER = 0x0000177C,  /* "You've found the Hydrodisplacer!" */
    HELP_STR_YOU_BOUGHT_THE_GRINDBOOTS = 0x0000177D,  /* "You bought the Grindboots!" */
    HELP_STR_INFOBOT_FOR_PLANET_BATALIA_0x1B58 = 0x00001B58,  /* "Infobot for Planet Batalia acquired" */
    HELP_STR_INFOBOT_FOR_PLANET_GASPAR_0x1F47 = 0x00001F47,  /* "Infobot for Planet Gaspar acquired" */
    HELP_STR_INFOBOT_FOR_PLANET_ORXON_0x1F48 = 0x00001F48,  /* "Infobot for Planet Orxon acquired" */
    HELP_STR_YOU_OBTAINED_THE_METAL_0x1F49 = 0x00001F49,  /* "You obtained the Metal Detector!" */
    HELP_STR_YOU_FOUND_THE_PILOTS_0x232A = 0x0000232A,  /* "You found the Pilot's Helmet!" */
    HELP_STR_INFOBOT_FOR_PLANET_POKITARU_0x2719 = 0x00002719,  /* "Infobot for Planet Pokitaru acquired" */
    HELP_STR_INFOBOT_FOR_PLANET_HOVEN_0x271A = 0x0000271A,  /* "Infobot for Planet Hoven acquired" */
    HELP_STR_YOU_FOUND_THE_MAGNEBOOTS = 0x0000271B,  /* "You found the Magneboots!" */
    HELP_STR_YOU_GOT_THE_PREMIUM_0x271C = 0x0000271C,  /* "You got the Premium Nanotech!" */
    HELP_STR_YOU_GOT_THE_ULTRA_0x271D = 0x0000271D,  /* "You got the Ultra Nanotech!" */
    HELP_STR_YOU_GOT_THE_THRUSTER_PACK_0x2B04 = 0x00002B04,  /* "You got the Thruster-Pack upgrade!" */
    HELP_STR_YOUVE_RECEIVED_THE_O2_0x2B05 = 0x00002B05,  /* "You've received the O2 Mask!" */
    HELP_STR_YOU_GOT_THE_PERSUADER = 0x00002B06,  /* "You got the Persuader!" */
    HELP_STR_GOT_INFOBOT_FOR_GEMLIK_0x2EE5 = 0x00002EE5,  /* "Got Infobot for Gemlik Moonbase" */
    HELP_STR_YOUVE_JUST_BOUGHT_THE_0x2EE6 = 0x00002EE6,  /* "You've just bought the Hydro-Pack!" */
    HELP_STR_YOUVE_OBTAINED_SOME_RARITANIUM = 0x00002EE7,  /* "You've obtained some Raritanium!" */
    HELP_STR_INFOBOT_FOR_PLANET_OLTANIS_0x32C9 = 0x000032C9,  /* "Infobot for Planet Oltanis acquired" */
    HELP_STR_INFOBOT_FOR_PLANET_QUARTU_0x36B1 = 0x000036B1,  /* "Infobot for Planet Quartu acquired" */
    HELP_STR_YOU_FOUND_THE_MORPH_O_RAY = 0x000036B2,  /* "You found the Morph-o-ray!" */
    HELP_STR_YOU_BOUGHT_THE_GADGETRON_0x36B3 = 0x000036B3,  /* "You bought the Gadgetron PDA!" */
    HELP_STR_INFOBOT_FOR_PLANET_KALEBO_0x3AA1 = 0x00003AA1,  /* "Infobot for Planet Kalebo III acquired" */
    HELP_STR_INFOBOT_FOR_DREKS_FLEET_0x3AA2 = 0x00003AA2,  /* "Infobot for Drek's Fleet acquired" */
    HELP_STR_YOU_FOUND_THE_BOLT_0x3AA3 = 0x00003AA3,  /* "You found the Bolt Grabber!" */
    HELP_STR_YOU_GOT_THE_MAP_O_MATIC = 0x00003E85,  /* "You got the Map-o-matic!" */
    HELP_STR_YOUVE_ACQUIRED_THE_HOLOGUISE = 0x00003E86,  /* "You've acquired the Hologuise!" */
    HELP_STR_INFOBOT_FOR_PLANET_VELDIN_0x4269 = 0x00004269,  /* "Infobot for Planet Veldin acquired" */
    HELP_STR_YOU_PICKED_UP_A_0x426A = 0x0000426A,  /* "You picked up a CodeBot!" */
    HELP_STR_GOLD_BOLT_ACQUIRED = 0x000053B3,  /* "Gold Bolt acquired" */
    HELP_STR_PICKED_UP_AMMO = 0x000053B4,  /* "Picked up ammo" */
    HELP_STR_GOT_D_BOMB_GLOVE_0x53B5 = 0x000053B5,  /* "Got %d Bomb Glove ammo" */
    HELP_STR_GOT_D_BOMB_GLOVE_0x53B6 = 0x000053B6,  /* "Got %d Bomb Glove ammo" */
    HELP_STR_GOT_D_DEVASTATOR_AMMO = 0x000053B7,  /* "Got %d Devastator ammo" */
    HELP_STR_GOT_D_DEVASTATOR_AMMO_2 = 0x000053B8,  /* "Got %d Devastator ammo" */
    HELP_STR_GOT_D_VISIBOMB_AMMO = 0x000053B9,  /* "Got %d Visibomb ammo" */
    HELP_STR_GOT_D_VISIBOMB_AMMO_2 = 0x000053BA,  /* "Got %d Visibomb ammo" */
    HELP_STR_GOT_D_BLASTER_AMMO = 0x000053BB,  /* "Got %d Blaster ammo" */
    HELP_STR_GOT_D_BLASTER_AMMO_2 = 0x000053BC,  /* "Got %d Blaster ammo" */
    HELP_STR_GOT_D_PYROCITOR_AMMO = 0x000053BD,  /* "Got %d Pyrocitor ammo" */
    HELP_STR_GOT_D_PYROCITOR_AMMO_2 = 0x000053BE,  /* "Got %d Pyrocitor ammo" */
    HELP_STR_GOT_D_MINE_GLOVE_0x53BF = 0x000053BF,  /* "Got %d Mine Glove ammo" */
    HELP_STR_GOT_D_MINE_GLOVE_0x53C0 = 0x000053C0,  /* "Got %d Mine Glove ammo" */
    HELP_STR_GOT_D_TESLA_CLAW_0x53C1 = 0x000053C1,  /* "Got %d Tesla claw ammo" */
    HELP_STR_GOT_D_TESLA_CLAW_0x53C2 = 0x000053C2,  /* "Got %d Tesla claw ammo" */
    HELP_STR_GOT_D_GLOVE_OF_0x53C3 = 0x000053C3,  /* "Got %d Glove of Doom ammo" */
    HELP_STR_GOT_D_GLOVE_OF_0x53C4 = 0x000053C4,  /* "Got %d Glove of Doom ammo" */
    HELP_STR_GOT_D_RYNO_AMMO = 0x000053C5,  /* "Got %d R.Y.N.O. ammo" */
    HELP_STR_GOT_D_RYNO_AMMO_2 = 0x000053C6,  /* "Got %d R.Y.N.O. ammo" */
    HELP_STR_GOT_D_DRONE_GLOVE_0x53C7 = 0x000053C7,  /* "Got %d Drone Glove ammo" */
    HELP_STR_GOT_D_DRONE_GLOVE_0x53C8 = 0x000053C8,  /* "Got %d Drone Glove ammo" */
    HELP_STR_GOT_D_DECOY_GLOVE_0x53C9 = 0x000053C9,  /* "Got %d Decoy Glove ammo" */
    HELP_STR_GOT_D_DECOY_GLOVE_0x53CA = 0x000053CA,  /* "Got %d Decoy Glove ammo" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53CB = 0x000053CB,  /* "You got the Gold Bomb Glove!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53CC = 0x000053CC,  /* "You got the Gold Pyrocitor!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53CD = 0x000053CD,  /* "You got the Gold Blaster!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53CE = 0x000053CE,  /* "You got the Gold Glove of Doom!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53CF = 0x000053CF,  /* "You got the Gold Mine Glove!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53D0 = 0x000053D0,  /* "You got the Gold Devastator!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53D1 = 0x000053D1,  /* "You got the Gold Decoy Glove!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53D2 = 0x000053D2,  /* "You got the Gold Tesla Claw!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53D3 = 0x000053D3,  /* "You got the Gold Suck Cannon!" */
    HELP_STR_YOU_GOT_THE_GOLD_0x53D4 = 0x000053D4,  /* "You got the Gold Morph-o-ray!" */
    HELP_STR_YOU_OPENED_THE_VAULT_0x53D5 = 0x000053D5,  /* "You opened the vault with the Codebot!" */
    HELP_STR_YOU_JUST_EARNED_A_0x53D6 = 0x000053D6,  /* "You just earned a Skill Point!" */
    HELP_STR_CONGRATULATIONS_YOUVE_NOW_COMPLETED_0x53D7 = 0x000053D7,  /* "Congratulations! You've now completed 15 Skill Points!Check the Goodies menu for a new option!" */
    HELP_STR_CONGRATULATIONS_YOUVE_COMPLETED_ALL_0x53D8 = 0x000053D8,  /* "Congratulations! You've completed all Skill Points!Check the Goodies menu for a new option!" */
    HELP_STR_CONGRATULATIONS_YOUVE_COLLECTED_ALL_0x53D9 = 0x000053D9,  /* "Congratulations! You've collected all Gold Bolts!Use them to buy Gold Weapons!" */
    HELP_STR_CONGRATULATIONS_YOUVE_OBTAINED_ALL_0x53DA = 0x000053DA,  /* "Congratulations! You've obtained all Gold Weapons!Check the Goodies menu for a new option!" */
    HELP_STR_YOU_GOT_THE_BOLT_0x53DB = 0x000053DB,  /* "You got the Bolt Grabber�again!" */
    HELP_STR_YOU_GOT_THE_MAP_O_MATICAGAIN = 0x000053DC,  /* "You got the Map-o-matic�again!" */
    HELP_STR_YOU_GOT_THE_GADGETRON_0x53DD = 0x000053DD,  /* "You got the Gadgetron PDA�again!" */
    HELP_STR_YOU_GOT_THE_PERSUADERAGAIN = 0x000053DE,  /* "You got the Persuader�again!" */
    HELP_STR_YOU_GOT_THE_SUCK_0x53DF = 0x000053DF,  /* "You got the Suck Cannon�again!" */
    HELP_STR_YOU_GOT_THE_MORPH_O_RAYAGAIN = 0x000053E0,  /* "You got the Morph-o-Ray�again!" */
    HELP_STR_YOU_GOT_THE_RARITANIUMAGAIN = 0x000053E1,  /* "You got the Raritanium�again!" */
    HELP_STR_YOU_GOT_THE_RYNO_0x53E2 = 0x000053E2,  /* "You got the R.Y.N.O. �again!" */
    HELP_STR_BUY_INFOBOT_FOR_0x03F3 = 0x000003F3,  /* " Buy Infobot for 500 bolts" */
    HELP_STR_YOU_NEED_500_BOLTS_0x03F4 = 0x000003F4,  /* "You need 500 bolts to buy the Infobot" */
    HELP_STR_BRING_THE_PRIZE_FROM_0x07E2 = 0x000007E2,  /* "Bring the prize from the hoverboard races" */
    HELP_STR_DESTROY_THE_SAND_SHARKS = 0x000007E3,  /* "Destroy the sand sharks" */
    HELP_STR_RETURN_TO_YOUR_0x0BC9 = 0x00000BC9,  /* " Return to your ship" */
    HELP_STR_TAKE_A_TAXI_0x0BCA = 0x00000BCA,  /* " Take a taxi ride" */
    HELP_STR_GO_TO_THE_0x0BCB = 0x00000BCB,  /* " Go to the start of the fitness course" */
    HELP_STR_TAKE_A_TAXI_0x0BCC = 0x00000BCC,  /* " Take a taxi ride" */
    HELP_STR_GO_TO_THE_0x0BCD = 0x00000BCD,  /* " Go to the end of the fitness course" */
    HELP_STR_RETURN_TO_THE_0x0BCE = 0x00000BCE,  /* " Return to the vendor" */
    HELP_STR_VISIT_BIG_ALS_0x0BCF = 0x00000BCF,  /* " Visit Big Al's Robot Shack" */
    HELP_STR_BUY_HELI_PACK_FOR_0x0BD0 = 0x00000BD0,  /* " Buy Heli-Pack for 1,000 bolts" */
    HELP_STR_BUY_SWINGSHOT_FOR_0x0BD1 = 0x00000BD1,  /* " Buy Swingshot for 1,000 bolts" */
    HELP_STR_YOU_NEED_1000_BOLTS_0x0BD2 = 0x00000BD2,  /* "You need 1,000 bolts for the Heli-Pack" */
    HELP_STR_YOU_NEED_1000_BOLTS_0x0BD3 = 0x00000BD3,  /* "You need 1,000 bolts for the Swingshot" */
    HELP_STR_HEAD_DOWNTOWN = 0x00001398,  /* " Head downtown" */
    HELP_STR_DROP_BY_RACEWAY_0x1399 = 0x00001399,  /* " Drop by Raceway Plaza" */
    HELP_STR_GO_TO_YOUR_0x139A = 0x0000139A,  /* " Go to your ship" */
    HELP_STR_TAKE_A_TAXI_0x139B = 0x0000139B,  /* " Take a taxi ride" */
    HELP_STR_VISIT_CAPTAIN_QWARKS_0x139C = 0x0000139C,  /* " Visit Captain Qwark's trailer" */
    HELP_STR_BRIBE_BOUNCER_WITH_0x139D = 0x0000139D,  /* " Bribe Bouncer with 4,000 bolts" */
    HELP_STR_BUY_RYNO_FOR_0x139E = 0x0000139E,  /* " Buy R.Y.N.O. for 150,000 bolts" */
    HELP_STR_YOU_NEED_A_HOVERBOARD_0x139F = 0x0000139F,  /* "You need a Hoverboard to race" */
    HELP_STR_YOU_NEED_4000_BOLTS_0x13A0 = 0x000013A0,  /* "You need 4,000 bolts to see Captain Qwark" */
    HELP_STR_YOU_NEED_150000_BOLTS_0x13A1 = 0x000013A1,  /* "You need 150,000 bolts for the R.Y.N.O." */
    HELP_STR_ENTER_RACE = 0x000013A2,  /* " Enter race" */
    HELP_STR_GO_FOR_COURSE_0x13A3 = 0x000013A3,  /* " Go for course record" */
    HELP_STR_SEND_CLANK_TO_0x177E = 0x0000177E,  /* " Send Clank to explore outside the station" */
    HELP_STR_GOING_DOWN = 0x0000177F,  /* " Going Down?" */
    HELP_STR_GOING_UP = 0x00001780,  /* " Going Up?" */
    HELP_STR_RETURN_TO_RATCHET = 0x00001781,  /* " Return to Ratchet" */
    HELP_STR_BOARD_WARSHIP = 0x00001782,  /* " Board warship" */
    HELP_STR_PRESS_THE_BIG_0x1783 = 0x00001783,  /* " Press the big red shiny button?" */
    HELP_STR_FLY_TO_INVENTORS_0x1784 = 0x00001784,  /* " Fly to inventor's hiding place" */
    HELP_STR_RETURN_TO_DOCKING_0x1785 = 0x00001785,  /* " Return to docking bay" */
    HELP_STR_ESCAPE_THE_SHIP = 0x00001786,  /* "Escape the ship" */
    HELP_STR_BUY_GRINDBOOTS_FOR_0x1787 = 0x00001787,  /* " Buy Grindboots for 2,000 bolts" */
    HELP_STR_YOU_NEED_2000_BOLTS_0x1788 = 0x00001788,  /* "You need 2,000 bolts for the Grindboots" */
    HELP_STR_EXPLORE_OUTSIDE = 0x00001789,  /* " Explore outside?" */
    HELP_STR_BUY_INFOBOT_FOR_0x1F4A = 0x00001F4A,  /* " Buy Infobot for 2,000 bolts" */
    HELP_STR_YOU_NEED_2000_BOLTS_0x1F4B = 0x00001F4B,  /* "You need 2,000 bolts for the Infobot" */
    HELP_STR_ENTER_TURRET_AND_0x1F4C = 0x00001F4C,  /* " Enter turret and blast ships" */
    HELP_STR_BUY_PREMIUM_NANOTECH_0x271E = 0x0000271E,  /* " Buy Premium Nanotech for 4,000 bolts" */
    HELP_STR_BUY_ULTRA_NANOTECH_0x271F = 0x0000271F,  /* " Buy Ultra Nanotech for 30,000 bolts" */
    HELP_STR_YOU_NEED_4000_BOLTS_0x2720 = 0x00002720,  /* "You need 4,000 bolts for Premium Nanotech" */
    HELP_STR_YOU_NEED_30000_BOLTS_0x2721 = 0x00002721,  /* "You need 30,000 bolts for Ultra Nanotech" */
    HELP_STR_PAY_2000_BOLTS_0x2B07 = 0x00002B07,  /* " Pay 2,000 Bolts for the Thruster-Pack" */
    HELP_STR_YOU_NEED_2000_BOLTS_0x2B08 = 0x00002B08,  /* "You need 2,000 Bolts for the Thruster-Pack" */
    HELP_STR_FLY_THE_JET_0x2B09 = 0x00002B09,  /* " Fly the Jet Plane" */
    HELP_STR_YOU_NEED_THE_PILOTS_0x2B0A = 0x00002B0A,  /* "You need the Pilot's Helmet to fly this plane" */
    HELP_STR_GO_TO_BOBS_0x2B0B = 0x00002B0B,  /* " Go to Bob's Roboshack" */
    HELP_STR_RETURN_TO_YOUR_0x2B0C = 0x00002B0C,  /* " Return to your ship" */
    HELP_STR_VISIT_THE_SCENIC_0x2B0D = 0x00002B0D,  /* " Visit the scenic Jowai Resort sewers" */
    HELP_STR_YOU_NEED_RARITANIUM = 0x00002B0E,  /* "You need Raritanium" */
    HELP_STR_TRADE_RARITANIUM_FOR_0x2B0F = 0x00002B0F,  /* " Trade Raritanium for Persuader" */
    HELP_STR_PAY_2000_BOLTS_0x2EE8 = 0x00002EE8,  /* " Pay 2,000 Bolts for the Hydro-Pack" */
    HELP_STR_YOU_NEED_2000_BOLTS_0x2EE9 = 0x00002EE9,  /* "You need 2,000 Bolts for the Hydro-Pack" */
    HELP_STR_ACTIVATE_GADGETRON_VENDOR = 0x000053E3,  /* " Activate Gadgetron Vendor" */
    HELP_STR_ENTER_SHIP = 0x000053E4,  /* " Enter ship" */
    HELP_STR_TALK = 0x000053E5,  /* " Talk" */
    HELP_STR_BLAST_OFF_TO_0x13A4 = 0x000013A4,  /* " Blast off to Metropolis" */
    HELP_STR_BLAST_OFF_TO_0x0BD4 = 0x00000BD4,  /* " Blast off to Blackwater City" */
    HELP_STR_BLAST_OFF_TO_0x53E6 = 0x000053E6,  /* " Blast off to Tobruk Crater" */
    HELP_STR_BLAST_OFF_TO_0x53E7 = 0x000053E7,  /* " Blast off to Outpost X11" */
    HELP_STR_RETURN_TO_LAUNCH_0x426B = 0x0000426B,  /* " Return to launch bay" */
    HELP_STR_BUY_INFOBOT_FOR_0x53E8 = 0x000053E8,  /* " Buy Infobot for 2,000 bolts" */
    HELP_STR_YOU_NEED_2000_BOLTS_0x53E9 = 0x000053E9,  /* "You need 2,000 bolts for the Infobot" */
    HELP_STR_BUY_GADGETRON_PDA_0x53EA = 0x000053EA,  /* " Buy Gadgetron PDA for 1,000 bolts" */
    HELP_STR_YOU_NEED_1000_BOLTS_0x53EB = 0x000053EB,  /* "You need 1,000 bolts for the Gadgetron PDA" */
    HELP_STR_YOU_NEED_A_CODEBOT_0x53EC = 0x000053EC,  /* "You need a Codebot to open this vault" */
    HELP_STR_TAKE_TAXI_TO_0x53ED = 0x000053ED,  /* " Take taxi to upper city" */
    HELP_STR_TAKE_TAXI_TO_0x53EE = 0x000053EE,  /* " Take taxi to your ship" */
    HELP_STR_ENTER_RACE_2 = 0x00003E87,  /* " Enter race" */
    HELP_STR_YOU_NEED_A_HOVERBOARD_0x3E88 = 0x00003E88,  /* "You need a Hoverboard to race" */
    HELP_STR_VISIT_GADGETRON_HELPDESK_0x3E89 = 0x00003E89,  /* " Visit Gadgetron Helpdesk offices" */
    HELP_STR_RETURN_TO_GADGETRON_0x3E8A = 0x00003E8A,  /* " Return to Gadgetron Lobby" */
    HELP_STR_GO_TO_THIS_0x426C = 0x0000426C,  /* " Go to this ship's observation deck" */
    HELP_STR_YOU_MUST_OWN_THE_0x03F5 = 0x000003F5,  /* "You must own the Tesla Clawbefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03F6 = 0x000003F6,  /* "You must own the Bomb Glovebefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03F7 = 0x000003F7,  /* "You must own the Devastatorbefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03F8 = 0x000003F8,  /* "You must own the Pyrocitorbefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03F9 = 0x000003F9,  /* "You must own the Mine Glovebefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03FA = 0x000003FA,  /* "You must own the Blasterbefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03FB = 0x000003FB,  /* "You must own theMorph-o-ray before obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03FC = 0x000003FC,  /* "You must own the Glove of Doombefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03FD = 0x000003FD,  /* "You must own the Decoy Glovebefore obtaining the gold version" */
    HELP_STR_YOU_MUST_OWN_THE_0x03FE = 0x000003FE,  /* "You must own the Suck Cannonbefore obtaining the gold version" */
    HELP_STR_YOU_NEED_4_GOLD_0x03FF = 0x000003FF,  /* "You need 4 Gold Bolts" */
    HELP_STR_YOU_NEED_D_BOLTS = 0x00000400,  /* "You need %d bolts" */
    HELP_STR_BUY_THE_GOLD_0x0401 = 0x00000401,  /* " Buy the Gold Tesla Claw for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0402 = 0x00000402,  /* " Buy the Gold Bomb Glovefor %d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0403 = 0x00000403,  /* " Buy the Gold Devastator for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0404 = 0x00000404,  /* " Buy the Gold Pyrocitor for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0405 = 0x00000405,  /* " Buy the Gold Mine Glovefor %d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0406 = 0x00000406,  /* " Buy the Gold Blaster for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0407 = 0x00000407,  /* " Buy the Gold Morph-o-ray for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0408 = 0x00000408,  /* " Buy the Gold Glove of Doom for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x0409 = 0x00000409,  /* " Buy the Gold Decoy Glove for%d bolts and 4 Gold Bolts" */
    HELP_STR_BUY_THE_GOLD_0x040A = 0x0000040A,  /* " Buy the Gold Suck Cannon for%d bolts and 4 Gold Bolts" */
    HELP_STR_GO_TO_SPACE_0x32CA = 0x000032CA,  /* " Go to space fighter hangar" */
    HELP_STR_RETURN_TO_YOUR_0x32CB = 0x000032CB,  /* " Return to your ship" */
    HELP_STR_RETURN_TO_THE_0x13A5 = 0x000013A5,  /* " Return to the city docks" */
    HELP_STR_TELEPORT_TO_GOLD_0x040B = 0x0000040B,  /* " Teleport to Gold Weapons room" */
    HELP_STR_BACK_TO_OVERLOOK = 0x0000040C,  /* " Back to overlook" */
    HELP_STR_RETURN_TO_YOUR_0x1F4D = 0x00001F4D,  /* " Return to your ship" */
    HELP_STR_GO_TO_TURRET = 0x00001F4E,  /* " Go to turret" */
    HELP_STR_GO_TO_DESERTER = 0x00001F4F,  /* " Go to Deserter" */
    HELP_STR_GO_TO_CITY_0x1F50 = 0x00001F50,  /* " Go to city entrance" */
    HELP_STR_TRANSFORM_INTO_GIANT_0x3AA4 = 0x00003AA4,  /* " Transform into Giant Clank" */
    HELP_STR_BECOME_SMALL_AGAIN = 0x00003AA5,  /* " Become small again" */
    HELP_STR_GO_TO_DREKS_0x426D = 0x0000426D,  /* " Go to Drek's Flagship" */
    HELP_STR_GO_TO_MISSILE_0x426E = 0x0000426E,  /* " Go to Missile Cruiser" */
    HELP_STR_GO_TO_DREADNOUGHT = 0x0000426F,  /* " Go to Dreadnought" */
    HELP_STR_GO_TO_LIGHT_0x4270 = 0x00004270,  /* " Go to Light Cruiser" */
    HELP_STR_RETURN_TO_YOUR_0x1B59 = 0x00001B59,  /* " Return to your ship" */
    HELP_STR_GO_TO_SNAGGLEBEAST_0x1B5A = 0x00001B5A,  /* " Go to Snagglebeast pit" */
    HELP_STR_GET_A_NANOTECH_0x2722 = 0x00002722,  /* " Get a nanotech recharge" */
    HELP_STR_TO_GET_GADGETRON_0x36B4 = 0x000036B4,  /* " To get Gadgetron PDA" */
    HELP_STR_TALK_TO_INVENTOR_0x2B10 = 0x00002B10,  /* " Talk to inventor some more�" */
    HELP_STR_RETURN_TO_YOUR_0x4653 = 0x00004653,  /* " Return to your ship" */
    HELP_STR_GO_TO_REFLECTOR_0x4654 = 0x00004654,  /* " Go to reflector dish" */
    HELP_STR_VISIT_THE_GADGETRON_0x53EF = 0x000053EF,  /* " Visit the Gadgetron Employee Breakroom" */
    HELP_STR_RETURN_TO_GADGETRON_0x53F0 = 0x000053F0,  /* " Return to Gadgetron Helpdesk Office" */
    HELP_STR_GO_TO_EDWINAS_0x2EEA = 0x00002EEA,  /* " Go to Edwina's shack" */
    HELP_STR_RETURN_TO_CAVE_0x2EEB = 0x00002EEB,  /* " Return to cave entrance" */
    HELP_STR_WARNING_O2_MASK_REQUIRED_0x53F1 = 0x000053F1,  /* "WARNING: O2 Mask required for organic life forms." */
    HELP_STR_YOU_NEED_60000_BOLTS_0x53F2 = 0x000053F2,  /* "You need 60,000 bolts and 4 Gold Boltsfor the Gold Tesla Claw" */
    HELP_STR_YOU_NEED_20000_BOLTS_0x53F3 = 0x000053F3,  /* "You need 20,000 bolts and 4 Gold Boltsfor the Gold Bomb Glove" */
    HELP_STR_YOU_NEED_60000_BOLTS_0x53F4 = 0x000053F4,  /* "You need 60,000 bolts and 4 Gold Boltsfor the Gold Devastator" */
    HELP_STR_YOU_NEED_30000_BOLTS_0x53F5 = 0x000053F5,  /* "You need 30,000 bolts and 4 Gold Boltsfor the Gold Pyrocitor" */
    HELP_STR_YOU_NEED_10000_BOLTS_0x53F6 = 0x000053F6,  /* "You need 10,000 bolts and 4 Gold Boltsfor the Gold Mine Glove" */
    HELP_STR_YOU_NEED_20000_BOLTS_0x53F7 = 0x000053F7,  /* "You need 20,000 bolts and 4 Gold Boltsfor the Gold Blaster" */
    HELP_STR_YOU_NEED_20000_BOLTS_0x53F8 = 0x000053F8,  /* "You need 20,000 bolts and 4 Gold Boltsfor the Gold Morph-o-ray" */
    HELP_STR_YOU_NEED_10000_BOLTS_0x53F9 = 0x000053F9,  /* "You need 10,000 bolts and 4 Gold Boltsfor the Gold Glove of Doom" */
    HELP_STR_YOU_NEED_10000_BOLTS_0x53FA = 0x000053FA,  /* "You need 10,000 bolts and 4 Gold Boltsfor the Gold Decoy Glove" */
    HELP_STR_YOU_NEED_10000_BOLTS_0x53FB = 0x000053FB,  /* "You need 10,000 bolts and 4 Gold Boltsfor the Gold Suck Cannon" */
    HELP_STR_TO_GET_RYNO_0x53FC = 0x000053FC,  /* " To get R.Y.N.O. again" */
    HELP_STR_TO_USE_YOUR_BOMB_0x0000 = 0x00000000,  /* "To use your Bomb Glove, press  to equip it and  again to fire it. You can also use it in first-person by holding down ." */
    HELP_STR_YOU_JUST_PICKED_UP_0x0001 = 0x00000001,  /* "You just picked up Nanotech! Whenever you sustain injury, let Gadgetron's patented Nanotech system rebuild your body from the inside out!" */
    HELP_STR_THATS_NANOTECH_WHENEVER_YOU_0x0002 = 0x00000002,  /* "That's Nanotech! Whenever you sustain injury, let Gadgetron's patented Nanotech system rebuild your body from the inside out!" */
    HELP_STR_WELCOME_TO_THE_GADGETRON_0x0003 = 0x00000003,  /* "Welcome to the Gadgetron HelpDesk!  We're here to offer you advice during your interplanetary travels. The HelpDesk is a free service provided by Gadgetron Corporation." */
    HELP_STR_GADGETRON_INFOBOTS_GIVE_YOU_0x03E8 = 0x000003E8,  /* "Gadgetron Infobots give you coordinates for new planets. You should press the SELECT button to bring up the map and go to your ship. It's marked with a star." */
    HELP_STR_GADGETRON_INFOBOTS_GIVE_YOU_0x03E9 = 0x000003E9,  /* "Gadgetron Infobots give you coordinates for new planets. Now that you have the Infobot for Planet Aridia you'll need to find a ship to get there." */
    HELP_STR_NOW_THAT_YOU_HAVE_0x03EA = 0x000003EA,  /* "Now that you have coordinates to two new planets, you can use your ship. Press the SELECT button to bring up the map - your ship is marked with a star." */
    HELP_STR_RUN_THEN_JUMP_AT_0x03EB = 0x000003EB,  /* "Run, then jump at the last instant for longer jumps." */
    HELP_STR_TO_PERFORM_A_POWERFUL_0x0004 = 0x00000004,  /* "To perform a powerful Hyper-Strike with your Gadgetron OmniWrench 8000, press  while jumping." */
    HELP_STR_GADGETRONS_OMNIWRENCH_8000_INCLUDES_0x0005 = 0x00000005,  /* "Gadgetron's OmniWrench 8000 includes a new Comet-Strike feature! To activate it, use  to crouch and then press ." */
    HELP_STR_YOUVE_JUST_ACQUIRED_A_0x07D0 = 0x000007D0,  /* "You've just acquired a Gadgetron Z3000 Hoverboard! Use your new Hoverboard at the racetrack in Blackwater City on Planet Rilgar." */
    HELP_STR_THE_GADGETRON_VENDOR_NEAR_0x07D1 = 0x000007D1,  /* "The Gadgetron Vendor near your landing site will sell you more ammo. Looks like you need it!" */
    HELP_STR_HAVING_TROUBLE_WITH_THE_0x07D2 = 0x000007D2,  /* "Having trouble with the local wildlife? Give the Gadgetron Pyrocitor a try! This weapon is perfect for use against creatures like these sandsharks!" */
    HELP_STR_HAVING_TROUBLE_WITH_THE_0x07D3 = 0x000007D3,  /* "Having trouble with the local wildlife? Give the Gadgetron Pyrocitor a try! You can pick one up at any Gadgetron Vendor." */
    HELP_STR_IF_YOU_WANT_TO_0x07D4 = 0x000007D4,  /* "If you want to impress this Agent, you'll have to win a Hoverboard race.  The nearest Hoverboard race is in Blackwater City on Planet Rilgar." */
    HELP_STR_YOU_ARE_NOW_THE_0x07D5 = 0x000007D5,  /* "You are now the proud owner of Gadgetron's Sonic Summoner. Simply equip this handy device whenever you are near a sand mouse residence." */
    HELP_STR_TO_SWING_FARTHER_PRESS_0x07D6 = 0x000007D6,  /* "To swing farther, press  in the direction you are swinging." */
    HELP_STR_YOU_WILL_NEED_A_0x07D7 = 0x000007D7,  /* "You will need a Gadgetron Swingshot to traverse this area. Our records indicate that the Swingshot is not available on this planet." */
    HELP_STR_THE_AREA_AHEAD_OF_0x07D8 = 0x000007D8,  /* "The area ahead of you contains standard Gadgetron Versa-Targets.  Use your Swingshot gadget to traverse the gaps." */
    HELP_STR_USING_THE_LATEST_IN_0x07D9 = 0x000007D9,  /* "Using the latest in precision laser technology, the Gadgetron Trespasser is guaranteed to work on Gadgetron's line of Invinco-Lock security doors." */
    HELP_STR_TRY_USING_THE_GLIDE_0x0BB8 = 0x00000BB8,  /* "Try using the Glide feature of your new Heli-Pack. Jump and then press and hold the  X button in mid-air to glide. " */
    HELP_STR_TRY_USING_THE_HELI_PACKS_0x0BB9 = 0x00000BB9,  /* "Try using the Heli-Pack's Boost Jump feature to climb these boxes. Press  to crouch, then jump." */
    HELP_STR_THIS_IS_A_JUMP_0x0BBA = 0x00000BBA,  /* "This is a jump slot.  Jump then jump again to kick off the walls in midair, until you reach the top." */
    HELP_STR_YOULL_NEED_YOUR_NEW_0x0BBB = 0x00000BBB,  /* "You'll need your new Heli-Pack's Stretch Jump feature to cross this gap. While you're running, crouch using  and then jump." */
    HELP_STR_DID_YOU_KNOW_THAT_0x0BBC = 0x00000BBC,  /* "Did you know that you have a map available to you at all times?  Just press the SELECT button to view a map of this planet." */
    HELP_STR_CONGRATULATIONS_ON_YOUR_NEW_0x0BBD = 0x00000BBD,  /* "Congratulations on your new Gadgetron Swingshot!  Use it on standard Versa-Targets like the ones nearby.  If the target is out of view, use  to aim." */
    HELP_STR_WHEN_USING_THE_SWINGSHOT_0x0BBE = 0x00000BBE,  /* "When using the Swingshot, hold down  until you've safely reached your destination. Premature button release can cause injuries!" */
    HELP_STR_YOU_CAN_USE_THE_0x0BBF = 0x00000BBF,  /* "You can use the zipline if you stand under the wire and jump." */
    HELP_STR_MAY_I_SUGGEST_YOU_0x0FA0 = 0x00000FA0,  /* "May I suggest you use your Glove of Doom in this area? Just sit back and relax while Gadgetron's robotic Agents of Doom do your dirty work!" */
    HELP_STR_WHY_NOT_TRY_GADGETRONS_0x0FA1 = 0x00000FA1,  /* "Why not try Gadgetron's Glove of Doom? This life-saving gadget lets you attack your enemies from a safe distance with tiny killer robots! Grab one now at a Gadgetron Vendor!" */
    HELP_STR_THE_SUCK_CANNON_CAN_0x0FA2 = 0x00000FA2,  /* "The Suck Cannon can vacuum up multiple enemies, then fire them out as high-caliber missiles!  Caution: enemies must be small enough to fit inside the barrel." */
    HELP_STR_YOULL_NEED_A_GADGETRON_0x0FA3 = 0x00000FA3,  /* "You'll need a Gadgetron Trespasser to get past this security door. Unfortunately our scans do not show a Trespasser available on this planet." */
    HELP_STR_USE_YOUR_GADGETRON_TRESPASSER_0x0FA4 = 0x00000FA4,  /* "Use your Gadgetron Trespasser to unlock this security door." */
    HELP_STR_LETS_RACE_USE__0x1388 = 0x00001388,  /* "Let's race! Use  to steer and  to jump." */
    HELP_STR_SINCE_YOU_NOW_HAVE_0x1389 = 0x00001389,  /* "Since you now have a Zoomerator, you can convert tricks to turbo! Press  to use turbo." */
    HELP_STR_TO_PROGRESS_ANY_FURTHER_0x138A = 0x0000138A,  /* "To progress any further in this area, you must have a Gadgetron Hydrodisplacer. Our sales records indicate that you'll find it on another planet." */
    HELP_STR_IF_YOU_EQUIP_THE_0x138B = 0x0000138B,  /* "If you equip the Hydrodisplacer, you'll be able to use the Insta-Faucets in this area." */
    HELP_STR_OUR_SCANNERS_SHOW_THAT_0x138C = 0x0000138C,  /* "Our scanners show that you're low on ammo. Try taking the nearby taxi to the Gadgetron Vendor." */
    HELP_STR_NEED_SOMETHING_MORE_POWERFUL_0x138D = 0x0000138D,  /* "Need something more powerful than your wrench? Get the latest high-tech weaponry from any Gadgetron Vendor and turn your foes into cosmic sludge!" */
    HELP_STR_GADGE_BOTS_CANT_CLIMB_BUT_0x1770 = 0x00001770,  /* "Gadge-Bots can't climb but you can use your ENTER command to send them into the Bot-Ports." */
    HELP_STR_USE_THE_ENTER_COMMAND_0x1771 = 0x00001771,  /* "Use the ENTER command to make the Gadge-Bots activate the Bot-Device.  The Bot-Device will activate when the correct number of Bots have entered it." */
    HELP_STR_YOU_HAVE_JUST_ACTIVATED_0x1772 = 0x00001772,  /* "You have just activated a Gadge-Bot. To command a Gadge-Bot hold down  and select WAIT, FOLLOW, ATTACK or ENTER." */
    HELP_STR_JUMP_THEN_PRESS_AND_0x1773 = 0x00001773,  /* "Jump, then press and hold  again while in the air to glide." */
    HELP_STR_YOU_CAN_TURN_OFF_0x1774 = 0x00001774,  /* "You can turn off this forcefield by breaking its forcefield generator." */
    HELP_STR_YOUVE_GOT_THE_GRINDBOOTS_0x1775 = 0x00001775,  /* "You've got the Grindboots! Grindboots let you travel on rails like this. Just jump onto the rail and grind!" */
    HELP_STR_THE_GADGETRON_HYDRODISPLACER_USES_0x1776 = 0x00001776,  /* "The Gadgetron Hydrodisplacer uses Insta-Faucets and Insta-Drains. Using it you can drain and fill pools. Our sensors do not detect any on this space station." */
    HELP_STR_NEED_A_LITTLE_HELP_0x1777 = 0x00001777,  /* "Need a little help with these enemies?   Try your Taunter!" */
    HELP_STR_NEED_A_LITTLE_HELP_0x1778 = 0x00001778,  /* "Need a little help with these enemies? Try a Gadgetron Taunter - available at any Gadgetron Vendor." */
    HELP_STR_THERE_IS_NOTHING_YOU_0x1F40 = 0x00001F40,  /* "There is nothing you can do here without a pair of Grindboots. Our sensors do not detect Grindboots available on this planet." */
    HELP_STR_YOU_CAN_USE_YOUR_0x1F41 = 0x00001F41,  /* "You can use your Grindboots here. Just jump onto the rail to activate them." */
    HELP_STR_YOU_WILL_NEED_A_0x1F42 = 0x00001F42,  /* "You will need a pair of Gadgetron Magneboots to traverse this ventilation shaft. Unfortunately, our scanners do not detect any Magneboots on this planet." */
    HELP_STR_YOU_NOW_HAVE_A_0x1F43 = 0x00001F43,  /* "You now have a Metal Detector! Whenever you are near a buried stash of bolts, a bolt icon will appear on your screen. Equip the Metal Detector, and hold  to track them down." */
    HELP_STR_YOU_HAVE_ACQUIRED_A_0x2328 = 0x00002328,  /* "You have acquired a Pilot's Helmet, manufactured by the Blarg.  It will allow you to fly jet fighters via neural induction." */
    HELP_STR_YOU_CAN_TIPTOE_TO_0x2710 = 0x00002710,  /* "You can tiptoe to sneak past sleeping enemies - just hold down  when you walk." */
    HELP_STR_THESE_MAGNEBOOTS_ARE_A_0x2711 = 0x00002711,  /* "These Magneboots are a device designed for climbing special metal surfaces.  However, your feet appear to be too small to equip them." */
    HELP_STR_THIS_IS_A_PREMIUM_0x2712 = 0x00002712,  /* "This is a Premium Nanotech dispenser. You can purchase a can to increase your maximum health." */
    HELP_STR_THIS_DISPENSER_ALSO_CARRIES_0x2713 = 0x00002713,  /* "This dispenser also carries Ultra Nanotech, the very latest in Gadgetron technology!  Ultra Nanotech is three times more potent than Premium Nanotech." */
    HELP_STR_THE_ATMOSPHERE_ON_ORXON_0x2714 = 0x00002714,  /* "The atmosphere on Orxon is poisonous. You will need an O2 Mask to survive outside your ship.  If you must explore the planet, we advise using a robot or other expendable device." */
    HELP_STR_THE_O2_MASK_ALLOWS_0x2AF8 = 0x00002AF8,  /* "The O2 Mask allows you to breathe underwater, in poisonous atmospheres, or even in outer space. It will auto-equip when you need it." */
    HELP_STR_THE_PERSUADER_IS_AN_0x2AF9 = 0x00002AF9,  /* "The Persuader is an illegal black market device that tricks Gadgetron Vendors into giving big discounts on all items.  We at Gadgetron trust you not to take advantage of this unsupported product." */
    HELP_STR_YOU_WILL_NEED_A_0x2AFA = 0x00002AFA,  /* "You will need a Blargian Pilot's Helmet to operate this jet fighter. Our scanners do not indicate such a device on this planet." */
    HELP_STR_YOUR_THRUSTER_PACK_INCLUDES_THE_0x2AFB = 0x00002AFB,  /* "Your Thruster-Pack includes the new Power Slam feature!  Just press  during a jump to enjoy your new destructive capabilities." */
    HELP_STR_YOUR_HYDRO_PACK_WILL_AUTOMATICALLY_0x2EE0 = 0x00002EE0,  /* "Your Hydro-Pack will automatically equip when you are swimming. The Hydro-Pack lets you swim against currents." */
    HELP_STR_RARITANIUM_IS_A_PRECIOUS_0x2EE1 = 0x00002EE1,  /* "Raritanium is a precious mineral used to power many of Gagdetron's devices. If used for destructive purposes, even small quantities can be extremely dangerous. ((THIS MESSAGE HAS BEEN CUT))" */
    HELP_STR_TO_ENTER_LOOK_AROUND_MODE_0x03EC = 0x000003EC,  /* "To enter look-around mode, press and hold ." */
    HELP_STR_YOU_CAN_ALSO_USE_0x03ED = 0x000003ED,  /* "You can also use your weapons and your wrench in this mode." */
    HELP_STR_TO_USE_THE_BOLT_0x03EE = 0x000003EE,  /* "To use the bolt crank, press  to attach your wrench, then walk around the platform." */
    HELP_STR_YOU_CAN_VIEW_A_0x03EF = 0x000003EF,  /* "You can view a map of the world by pressing the SELECT button or the R3 button." */
    HELP_STR_PRESS__TO_DIVE_0x03F0 = 0x000003F0,  /* "Press  to dive and  to rise. Push  harder to rise more quickly." */
    HELP_STR_OUR_TRANSLATORS_INDICATE_THIS_0x07DA = 0x000007DA,  /* "Our translators indicate this sand mouse needs help finding his other house." */
    HELP_STR_LASERS_ARE_MOUNTED_ON_0x07DB = 0x000007DB,  /* "Lasers are mounted on each ring of the Invinco-Lock. Aim the lasers at the receptors on the outside ring to turn them green. All receptors must be green before the  Invinco-Lock will open." */
    HELP_STR_USE__TO_CONTROL_0x07DC = 0x000007DC,  /* "Use  to control the Trespasser. Push up and down to select which ring is active; push left and right to rotate the ring." */
    HELP_STR_PRESS_THE_SELECT_BUTTON_0x07DD = 0x000007DD,  /* "Press the SELECT button or the R3 button to bring up the map.  This may help you locate where you are." */
    HELP_STR_YOU_CAN_KICK_OFF_0x0FA5 = 0x00000FA5,  /* "You can kick off the wall by jumping just as you reach it." */
    HELP_STR_YOU_CAN_ACCURATELY_AIM_0x4E20 = 0x00004E20,  /* "You can accurately aim the Blaster if you hold down ." */
    HELP_STR_YOURE_LOADED_WITH_BOLTS_0x4E21 = 0x00004E21,  /* "You're loaded with bolts. How about going to the Gadgetron Vendor and spending some?" */
    HELP_STR_YOU_CAN_USE__0x4E22 = 0x00004E22,  /* "You can use  to control the camera." */
    HELP_STR_HAVING_TROUBLE_GETTING_HEIGHT_0x4E23 = 0x00004E23,  /* "Having trouble getting height with your Boost Jump? Try to avoid pressing  until you've reached the apex of your jump." */
    HELP_STR_TO_USE_THE_PYROCITOR_0x4E24 = 0x00004E24,  /* "To use the Pyrocitor, hold down ." */
    HELP_STR_TRY_THE_GADGETRON_QUICKSELECT_0x4E25 = 0x00004E25,  /* "Try the Gadgetron QuickSelect system to activate weapons or gadgets! Hold  and then select an icon with your left analog stick." */
    HELP_STR_DID_YOU_KNOW_YOU_0x4E26 = 0x00004E26,  /* "Did you know you can place any gadget or weapon on your QuickSelect? Just pause and choose QuickSelect from the menu." */
    HELP_STR_WHEN_YOURE_UNDERWATER_PUSH_0x4E27 = 0x00004E27,  /* "When you're underwater, push  harder to rise more quickly." */
    HELP_STR_UNFORTUNATELY_YOU_CANT_VENTURE_0x1779 = 0x00001779,  /* "Unfortunately, you can't venture beyond this door without a Gadgetron O2 Mask." */
    HELP_STR_THIS_SHUTTLE_HAS_AN_0x177A = 0x0000177A,  /* "This shuttle has an autopilot which will take you to a decommissioned Blarg warship. Our scanners indicate that there may be useful technology on board." */
    HELP_STR_THESE_MOVING_WALLS_ALSO_0x0BC0 = 0x00000BC0,  /* "These moving walls also function as jump slots.  Jump, and jump again to kick off the walls in midair, until you reach the top." */
    HELP_STR_PRESS__TO_FIRE_0x2AFC = 0x00002AFC,  /* "Press  to fire the machine guns and press  to fire homing missiles. To go faster, hold down ." */
    HELP_STR_POSITION_THE_TARGETING_RETICULE_0x2AFD = 0x00002AFD,  /* "Position the targeting reticule over the enemy. When the target stops flashing and is red, fire your homing missiles by pressing ." */
    HELP_STR_SHOOT_DOWN_THOSE_SMALL_0x2AFE = 0x00002AFE,  /* "Shoot down those small enemy ships to get more missiles." */
    HELP_STR_SHOOT_DOWN_THOSE_SMALL_0x2AFF = 0x00002AFF,  /* "Shoot down those small enemy ships to get more health." */
    HELP_STR_TO_GO_FASTER_HOLD_0x2B00 = 0x00002B00,  /* "To go faster, hold down the  square button." */
    HELP_STR_THE_DEVASTATOR_IS_A_0x1F44 = 0x00001F44,  /* "The Devastator is a great weapon against tough enemies. You can purchase one from the Gadgetron Vendor on this world." */
    HELP_STR_THE_GADGETRON_DEVASTATOR_IS_0x2329 = 0x00002329,  /* "The Gadgetron Devastator is very effective against Blarg Paratroopers. You can pick one up at any Gadgetron Vendor." */
    HELP_STR_THE_DEVASTATOR_MANUFACTURED_EXCLUSIVELY_0x2715 = 0x00002715,  /* "The Devastator, manufactured exclusively by Gadgetron, provides the kind of muscle you need to take out Blarg saucers!" */
    HELP_STR_YOU_NEED_A_DEVASTATOR_0x2EE2 = 0x00002EE2,  /* "You need a Devastator to take out that helicopter! " */
    HELP_STR_YOULL_NEED_THE_STRETCH_0x138E = 0x0000138E,  /* "You'll need the Stretch Jump to cross this gap.   While you're running, crouch using  and then jump." */
    HELP_STR_TO_PERFORM_TRICKS_HOLD_0x138F = 0x0000138F,  /* "To perform tricks, hold down , , , or  while in the air." */
    HELP_STR_THIS_IS_A_GADGETRON_0x0BC1 = 0x00000BC1,  /* "This is a Gadgetron HelpDesk message. You can turn off the HelpDesk by going to the help menu. You can interrupt these messages by pressing ." */
    HELP_STR_TO_USE_YOUR_HELI_PACK_0x1390 = 0x00001390,  /* "To use your Heli-Pack, crouch with , jump, and glide by pressing  again to cross this gap." */
    HELP_STR_TRY_PRESSING__TO_0x0BC2 = 0x00000BC2,  /* "Try pressing  to equip your Blaster. Press  again to fire it." */
    HELP_STR_YOULL_NEED_YOUR_SWINGSHOT_0x0BC3 = 0x00000BC3,  /* "You'll need your Swingshot to get to the next barge. Hold down  to equip it in the QuickSelect screen, then hold  to fire it at the yellow target." */
    HELP_STR_WHEN_USING_THE_SWINGSHOT_0x1391 = 0x00001391,  /* "When using the Swingshot, hold down  until you've safely reached your destination. Premature button release can cause injuries!" */
    HELP_STR_TRY_THE_GADGETRON_QUICKSELECT_0x0BC4 = 0x00000BC4,  /* "Try the Gadgetron QuickSelect system to activate weapons or gadgets! Hold  and then select an icon with your left analog stick." */
    HELP_STR_TO_ENTER_LOOK_AROUND_MODE_0x1392 = 0x00001392,  /* "To enter look-around mode, press and hold " */
    HELP_STR_DID_YOU_KNOW_THAT_0x1393 = 0x00001393,  /* "Did you know that you have a map available to you at all times?  Just press the SELECT button to view a map of this planet." */
    HELP_STR_CONGRATULATIONS_YOUVE_COMPLETED_ALL_0x0BC5 = 0x00000BC5,  /* "Congratulations! You've completed all missions for this world! You can collect more bolts to purchase weapons or go to your ship and blast off to the other world in this demo." */
    HELP_STR_YOU_SHOULD_CONSIDER_PURCHASING_0x2716 = 0x00002716,  /* "You should consider purchasing a Gadgetron Devastator. It would be very useful against the enemies in this world." */
    HELP_STR_GADGE_BOTS_CANT_CLIMB_BUT_0x2717 = 0x00002717,  /* "Gadge-Bots can't climb but you can use your ENTER command to send them into the Bot-Ports." */
    HELP_STR_USE_THE_ENTER_COMMAND_0x2718 = 0x00002718,  /* "Use the ENTER command to make the Gadge-Bots activate the Bot-Device.  The Bot-Device will activate when the correct number of Bots have entered it." */
    HELP_STR_WITH_THE_THRUSTER_PACK_YOU_0x2B01 = 0x00002B01,  /* "With the Thruster-Pack, you can Power Slam switches like these by jumping and then pressing ." */
    HELP_STR_YOUR_THRUSTER_PACK_UPGRADE_GIVES_0x2EE3 = 0x00002EE3,  /* "Your Thruster-Pack upgrade gives you the ability to hover and strafe. Double-tap  to activate hover and hold  or  to strafe from side to side." */
    HELP_STR_TRY_USING__OR_0x2EE4 = 0x00002EE4,  /* "Try using  or  with  to strafe while hovering." */
    HELP_STR_THOSE_PULSING_TOWERS_CONTROL_0x32C8 = 0x000032C8,  /* "Those pulsing towers control the force fields.  In order to knock them all out, you're going to need the Gadgetron Devastator or the Visibomb Gun." */
    HELP_STR_YOU_CAN_USE_YOUR_0x1F45 = 0x00001F45,  /* "You can use your Magneboots to traverse the ventilation shaft." */
    HELP_STR_YOULL_NEED_TO_USE_0x2B02 = 0x00002B02,  /* "You'll need to use the special features of a Gadgetron Thruster-Pack to activate this switch.  You can find one at Bob's Roboshack, just around the corner." */
    HELP_STR_WHEN_YOURE_UNDERWATER_DONT_0x4E28 = 0x00004E28,  /* "When you're underwater, don't tap ; push and hold  to rise." */
    HELP_STR_CONGRATULATIONS_YOUVE_SUCCESSFULLY_COMPLETED_0x4E29 = 0x00004E29,  /* "Congratulations! You've successfully completed all known missions on this world! There may be other secrets to find though�" */
    HELP_STR_YOU_CAN_INTERRUPT_HELPDESK_0x4E2A = 0x00004E2A,  /* "You can interrupt HelpDesk messages by pressing . To disable HelpDesk messages, please select Options from your pause menu." */
    HELP_STR_WHEN_THE_GAME_SHOWS_0x4E2B = 0x00004E2B,  /* "When the game shows "Saving" in the bottom-right corner of the screen, your progress is being saved. While this this text is on screen, do not turn off the power." */
    HELP_STR_IF_YOUD_LIKE_YOU_0x4E2C = 0x00004E2C,  /* "If you'd like, you can reverse your camera controls.  Just select Camera from the Options menu." */
    HELP_STR_BY_DOUBLE_TAPPING__YOU_0x4E2D = 0x00004E2D,  /* "By double-tapping , you can quickly switch between your two most recently used weapons or hand gadgets." */
    HELP_STR_NOW_THAT_YOU_HAVE_0x4E2E = 0x00004E2E,  /* "Now that you have the Hydro-Pack you can activate its turbojets by holding down ." */
    HELP_STR_TO_QUICKLY_CENTER_THE_0x4E2F = 0x00004E2F,  /* "To quickly center the camera, just tap ." */
    HELP_STR_CONGRATULATIONS_YOU_JUST_FOUND_0x36B0 = 0x000036B0,  /* "Congratulations, you just found a Gadgetron Morph-o-ray! Hold down  and keep the beam focused on an enemy. When the meter is full, the enemy will transform!" */
    HELP_STR_YOULL_NEED_THE_GADGETRON_0x3A98 = 0x00003A98,  /* "You'll need the Gadgetron Hologuise to explore the factory. Unfortunately, our scanners do not detect a Hologuise on this planet." */
    HELP_STR_TIME_TO_USE_THE_0x3A99 = 0x00003A99,  /* "Time to use the Hologuise! While wearing the Hologuise, press  to wave to the Sentry-bot and he will deactivate the force fields." */
    HELP_STR_WHILE_WEARING_THE_HOLOGUISE_0x3A9A = 0x00003A9A,  /* "While wearing the Hologuise, press  to wave to the Sentry-bot and he will deactivate the forcefield." */
    HELP_STR_THE_HOLOGUISE_IS_A_0x3E80 = 0x00003E80,  /* "The Hologuise is a holographic disguise that  fools Sentry-bots and allows you to gain access to specially guarded areas. Our records do not indicate the existence of Sentry-bots on this planet." */
    HELP_STR_GIANT_CLANK_HAS_HIS_0x3A9B = 0x00003A9B,  /* "Giant Clank has his own set of super attacks. Press  for a mega punch attack and press  to fire homing missiles. Jump to create a powerful shockwave that will wipe out those tiny enemies." */
    HELP_STR_WHEN_YOUR_ENERGY_BAR_0x3A9C = 0x00003A9C,  /* "When your energy bar is full, press  to unleash an atomic energy blast." */
    HELP_STR_TO_USE_THE_TESLA_0x4E30 = 0x00004E30,  /* "To use the Tesla Claw, keep  held down." */
    HELP_STR_YOU_WILL_NEED_A_0x3A9D = 0x00003A9D,  /* "You will need a  Hydro-Pack upgrade to swim through those Tri-Rings and open the door. Unfortunately, our scanners do not detect a Hydro-Pack upgrade service on this planet." */
    HELP_STR_TO_FIRE_A_ROCKET_0x3E81 = 0x00003E81,  /* "To fire a rocket, press ." */
    HELP_STR_THE_GADGETRON_MAP_O_MATIC_CAN_0x3E82 = 0x00003E82,  /* "The Gadgetron Map-o-matic can be used to find secret areas. Just go to your map screen and all secrets areas will be highlighted on the map." */
    HELP_STR_POWER_SLAM_THAT_BUTTON_0x4650 = 0x00004650,  /* "Power Slam that button to terminate the countdown! To Power Slam, jump and press ." */
    HELP_STR_OUR_LONG_RANGE_SENSORS_DO_0x2B03 = 0x00002B03,  /* "Our long-range sensors do not detect Raritanium on this planet. Our database indicates that the best place to locate this mineral  is on Planet Hoven. " */
    HELP_STR_IF_YOU_WANT_TO_0x3E83 = 0x00003E83,  /* "If you want to enter this race, you need a hoverboard. Our sensors indicate that one exists on Planet Aridia." */
    HELP_STR_YOU_WILL_HAVE_TO_0x3A9E = 0x00003A9E,  /* "You will have to destroy those Sentry-bots. Make sure they do not press that alarm button!" */
    HELP_STR_IF_A_SENTRY_BOT_PRESSES_0x3A9F = 0x00003A9F,  /* "If a Sentry-bot presses an alarm button, you will be eliminated by the factory's automated defense system." */
    HELP_STR_THE_GLOWING_ANTENNAE_ON_0x3AA0 = 0x00003AA0,  /* "The glowing antennae on your Hologuise will change colors to let you know if you are in danger. Green means you're safe, and red means you've been caught!" */
    HELP_STR_THE_GUNFIRE_FROM_THOSE_0x4268 = 0x00004268,  /* "The gunfire from those turrets is deadly. You will have to find a detour." */
    HELP_STR_POWER_SLAM_THAT_RESET_0x4651 = 0x00004651,  /* "Power Slam that reset button before the time runs out! To Power Slam, jump and press ." */
    HELP_STR_POWER_SLAM_THAT_RESET_0x4652 = 0x00004652,  /* "Power Slam that reset button before the time runs out!" */
    HELP_STR_SINCE_YOU_NOW_OWN_0x1F46 = 0x00001F46,  /* "Since you now own the Metal Detector a bolt icon will show up on screen whenever you are near a buried stash of bolts.When equipped, the Metal Detector will give you signals to indicate your proximity to the buried bolts.  The detector plate will always indicate the direction to the bolts. Hold down  to activate the device. As you move closer to the bolts, the rings will become redder and the beeping will become faster. Continue holding down  and once you are directly over the bolts, the metal detector will suck them out of the ground!" */
    HELP_STR_THE_GADGETRON_HOLOGUISE_IS_0x3E84 = 0x00003E84,  /* "The Gadgetron Hologuise is the perfect infiltration device for all our non-robot customers! Simply equip the device and press . You will instantly be disguised as a Sentry-bot, preventing detection by all Sentry-bot security systems. Press  again to wave at fellow Sentry-bots who will then deactivate force-fields for you.Caution: Use of any weapon while disguised will deactivate the Hologuise!" */
    HELP_STR_THE_SONIC_SUMMONER_ALLOWS_0x07DE = 0x000007DE,  /* "The Sonic Summoner allows you to interact with the mysterious and intelligent Sand Mice species. Despite their innocent appearance, Sand Mice are very effective and aggressive hunters.Simply equip the Sonic Summoner when you are near a Sand Mouse House, and a mouse will emerge to greet you. If the mouse likes you, it may offer a bit of high-caliber tactical assistance." */
    HELP_STR_SKILL_POINTS_ARE_USED_0x4E31 = 0x00004E31,  /* "Skill points are used for a special reward." */
    HELP_STR_YOU_CAN_EXCHANGE_YOUR_0x4E32 = 0x00004E32,  /* "You can exchange your Gold Bolts for Gold Weapons at the Gemlik Base in Nebula G34." */
    HELP_STR_YOU_CAN_EXCHANGE_YOUR_0x4E33 = 0x00004E33,  /* "You can exchange your Gold Bolts for Gold Weapons here on Planet Novalis or at the Gemlik Base in Nebula G34." */
    HELP_STR_BACK = 0x00005233,  /* " Back" */
    HELP_STR_BUY = 0x00005234,  /* " Buy" */
    HELP_STR_YES = 0x00005235,  /* "YES" */
    HELP_STR_YOURE_MAXED_OUT = 0x00005236,  /* "You're maxed out!" */
    HELP_STR_HOW_MANY = 0x00005237,  /* "How many?" */
    HELP_STR_YOU_CANT_AFFORD_IT = 0x00005238,  /* "You can't afford it!" */
    HELP_STR_PURCHASE = 0x00005239,  /* "Purchase?" */
    HELP_STR_DEMO_OBJECTIVES = 0x0000523B,  /* "Demo Objectives:" */
    HELP_STR_TO_CONTINUE = 0x0000523C,  /* " to continue" */
    HELP_STR_ALL_MISSIONS_COMPLETE = 0x0000523D,  /* "All Missions Complete" */
    HELP_STR_MISSION_COMPLETED = 0x0000523E,  /* "Mission Completed." */
    HELP_STR_LAP = 0x0000523F,  /* "Lap" */
    HELP_STR_PLACE = 0x00005240,  /* "Place" */
    HELP_STR_TIME = 0x00005241,  /* "Time" */
    HELP_STR_TARGET = 0x00005242,  /* "Target" */
    HELP_STR_BEST = 0x00005243,  /* "Best" */
    HELP_STR_PLAY_METROPOLIS = 0x00005244,  /* "Play Metropolis" */
    HELP_STR_PLAY_BLACKWATER_CITY = 0x00005245,  /* "Play Blackwater City" */
    HELP_STR_WATCH_MOVIE = 0x00005246,  /* "Watch Movie" */
    HELP_STR_EXIT_2 = 0x00005247,  /* "Exit" */
    HELP_STR_QUIT_2 = 0x00005248,  /* " Quit" */
    HELP_STR_CONTINUE = 0x00005249,  /* " Continue" */
    HELP_STR_CONTINUE_2 = 0x0000524A,  /* " Continue" */
    HELP_STR_NO = 0x0000524B,  /* " No" */
    HELP_STR_NO_2 = 0x0000524C,  /* " No" */
    HELP_STR_NO_3 = 0x0000524D,  /* " No" */
    HELP_STR_YES_2 = 0x0000524E,  /* " Yes" */
    HELP_STR_YES_3 = 0x0000524F,  /* " Yes" */
    HELP_STR_FIRST_PERSON_TARGETING = 0x00005250,  /* "First person targeting" */
    HELP_STR_SWING_WRENCH = 0x00005251,  /* "Swing wrench" */
    HELP_STR_MENU = 0x00005252,  /* "Menu" */
    HELP_STR_CROUCH = 0x00005253,  /* "Crouch" */
    HELP_STR_QUICK_SELECT_2 = 0x00005254,  /* "Quick Select" */
    HELP_STR_FIRE_WEAPON___USE_0x5255 = 0x00005255,  /* "Fire weapon / Use gadget" */
    HELP_STR_LOOK_AROUND = 0x00005256,  /* "Look around" */
    HELP_STR_WALK_RUN = 0x00005257,  /* "Walk/Run" */
    HELP_STR_JUMP = 0x00005258,  /* "Jump" */
    HELP_STR_UP = 0x00005259,  /* " Up" */
    HELP_STR_DOWN = 0x0000525A,  /* " Down" */
    HELP_STR_BOMB_GLOVE_THROW_BOMBS_0x525B = 0x0000525B,  /* "BOMB GLOVE!   THROW BOMBS AT YOUR ENEMIES!  bBbObObMb!" */
    HELP_STR_DEVASTATOR_LAUNCH_GUIDED_BMBIBSBSBIBLBEBS_0x525C = 0x0000525C,  /* "DEVASTATOR!  LAUNCH GUIDED bMbIbSbSbIbLbEbS AT THE BAD GUYS." */
    HELP_STR_VISIBOMB_STEER_YOUR_MISSILES_0x525D = 0x0000525D,  /* "VISIBOMB!  STEER YOUR MISSILES WITH DEADLY ACCURACY USING THE ON-BOARD VIDEO RELAY!" */
    HELP_STR_TAUNTER_ANNOY_YOUR_ENEMIES_0x525E = 0x0000525E,  /* "TAUNTER!  ANNOY YOUR ENEMIES AND LURE THEM INTO TRAPS AND AMBUSHES WITH THIS OBNOXIOUS NOISE-MAKER!" */
    HELP_STR_BLASTER_POINT_IT_MORE_0x525F = 0x0000525F,  /* "BLASTER!  POINT IT MORE OR LESS AT THE BAD GUYS AND MOW 'EM DOWN!" */
    HELP_STR_PYROCITOR_THIS_FEARSOME_WEAPON_0x5260 = 0x00005260,  /* "PYROCITOR!  THIS FEARSOME WEAPON REALLY SHINES AT CLOSE RANGE.  GREAT FOR TAKING OUT THOSE PESKY SMALL ENEMIES." */
    HELP_STR_MINE_GLOVE_BE_SNEAKY_0x5261 = 0x00005261,  /* "MINE GLOVE!   BE SNEAKY AND SET bEbXbPbLbObDbIbNbG TRAPS FOR YOUR ENEMIES!" */
    HELP_STR_WALLOPER_PUNCH_PEOPLE_HARD = 0x00005262,  /* "WALLOPER!  PUNCH PEOPLE HARD." */
    HELP_STR_TESLA_CLAW_BLAST_THE_0x5263 = 0x00005263,  /* "TESLA CLAW!  BLAST THE BAD GUYS WITH BOLTS OF ELECTRICITY!" */
    HELP_STR_GLOVE_OF_DOOM_LAUNCH_0x5264 = 0x00005264,  /* "GLOVE OF DOOM!  LAUNCH A HORDE OF EXPLODING bBbUbDbDbIbEbS TO CHASE DOWN YOUR FOES!" */
    HELP_STR_RYNO_DESTROYS_EVERYTHING_YOU_0x5265 = 0x00005265,  /* "R.Y.N.O!  DESTROYS EVERYTHING YOU CAN SEE AND PROBABLY A FAIR BIT THAT YOU CANT." */
    HELP_STR_DEFENSE_DRONE_GLOVE_SURROUND_0x5266 = 0x00005266,  /* "DEFENSE DRONE GLOVE!  SURROUND YOURSELF WITH A SCREEN OF POINT DEFENSE BOTS." */
    HELP_STR_DECOY_GLOVE_FOOL_YOUR_0x5267 = 0x00005267,  /* "DECOY GLOVE!  FOOL YOUR ENEMIES WITH THIS EERILY LIFELIKE bDbEbCbObYb." */
    HELP_STR_DEMO = 0x00005268,  /* "Demo" */
    HELP_STR_WARNING_SHIP_NEEDS_REPAIR = 0x00005269,  /* "WARNING: SHIP NEEDS REPAIR!" */
    HELP_STR_SON_ = 0x0000526A,  /* "Son_" */
    HELP_STR_YOU_HAVE_DONE_WELL_ = 0x0000526B,  /* "You have done well_" */
    HELP_STR_THERE_IS_STILL_MORE_0x526C = 0x0000526C,  /* "There is still more to do_" */
    HELP_STR_THIS_WILL_AID_YOU_0x526D = 0x0000526D,  /* "This will aid you on your journey." */
    HELP_STR_YOU_ALREADY_HAVE_ = 0x0000526E,  /* "You already have_" */
    HELP_STR_BOMB_GLOVE_USE = 0x0000526F,  /* "Bomb Glove use" */
    HELP_STR_WHATS_NANOTECH = 0x00005270,  /* "What's Nanotech?" */
    HELP_STR_THIS_IS_NANOTECH = 0x00005271,  /* "This is Nanotech" */
    HELP_STR_WELCOME_3 = 0x00005272,  /* "Welcome!" */
    HELP_STR_WHAT_ARE_INFOBOTS = 0x00005273,  /* "What are Infobots?" */
    HELP_STR_INFOBOT_HINT = 0x00005274,  /* "Infobot hint" */
    HELP_STR_SHIP_REMINDER = 0x00005275,  /* "Ship reminder" */
    HELP_STR_LONGER_JUMPS = 0x00005276,  /* "Longer jumps" */
    HELP_STR_HYPER_STRIKE_HELP = 0x00005277,  /* "Hyper-Strike help" */
    HELP_STR_COMET_STRIKE_EXPLAINED = 0x00005278,  /* "Comet-Strike explained" */
    HELP_STR_WHERE_TO_USE_HOVERBOARD = 0x00005279,  /* "Where to use Hoverboard" */
    HELP_STR_NEED_AMMO = 0x0000527A,  /* "Need ammo?" */
    HELP_STR_SANDSHARK_HINT = 0x0000527B,  /* "Sandshark hint" */
    HELP_STR_TRY_THE_PYROCITOR = 0x0000527C,  /* "Try the Pyrocitor" */
    HELP_STR_IMPRESS_THE_AGENT = 0x0000527D,  /* "Impress the Agent" */
    HELP_STR_SONIC_SUMMONER_HELP = 0x0000527E,  /* "Sonic Summoner help" */
    HELP_STR_SWINGIN_WITH_THE_SWINGSHOT = 0x0000527F,  /* "Swingin' with the Swingshot" */
    HELP_STR_NEED_THE_SWINGSHOT = 0x00005280,  /* "Need the Swingshot" */
    HELP_STR_SWINGSHOT_REMINDER = 0x00005281,  /* "Swingshot reminder" */
    HELP_STR_TRESPASSER_DESCRIPTION = 0x00005282,  /* "Trespasser description" */
    HELP_STR_HOW_TO_GLIDE = 0x00005283,  /* "How to Glide" */
    HELP_STR_HOW_TO_BOOST_JUMP = 0x00005284,  /* "How to Boost Jump" */
    HELP_STR_WALL_JUMP_HINT = 0x00005285,  /* "Wall jump hint" */
    HELP_STR_HOW_TO_STRETCH_JUMP = 0x00005286,  /* "How to Stretch Jump" */
    HELP_STR_USE_THE_MAP = 0x00005287,  /* "Use the map" */
    HELP_STR_SWINGSHOT_INSTRUCTIONS = 0x00005288,  /* "Swingshot instructions" */
    HELP_STR_SWINGSHOT_CAUTION = 0x00005289,  /* "Swingshot caution" */
    HELP_STR_ZIPLINE_HINT = 0x0000528A,  /* "Zipline hint" */
    HELP_STR_GLOVE_OF_DOOM_REMINDER = 0x0000528B,  /* "Glove of Doom reminder" */
    HELP_STR_GLOVE_OF_DOOM_EXPLANATION = 0x0000528C,  /* "Glove of Doom explanation" */
    HELP_STR_SUCK_CANNON_DESCRIPTION = 0x0000528D,  /* "Suck Cannon description" */
    HELP_STR_SECURITY_DOOR = 0x0000528E,  /* "Security door" */
    HELP_STR_SECURITY_DOOR_2 = 0x0000528F,  /* "Security door" */
    HELP_STR_BASIC_RACING = 0x00005290,  /* "Basic racing" */
    HELP_STR_USING_TURBO = 0x00005291,  /* "Using turbo" */
    HELP_STR_HYDRODISPLACER_HINT = 0x00005292,  /* "Hydrodisplacer hint" */
    HELP_STR_HYDRODISPLACER_SUGGESTION = 0x00005293,  /* "Hydrodisplacer suggestion" */
    HELP_STR_AMMO_REMINDER = 0x00005294,  /* "Ammo reminder" */
    HELP_STR_BUY_SOME_WEAPONS = 0x00005295,  /* "Buy some weapons!" */
    HELP_STR_GADGE_BOT_USAGE = 0x00005296,  /* "Gadge-Bot usage" */
    HELP_STR_WHAT_IS_A_BOT_DEVICE = 0x00005297,  /* "What is a Bot-Device?" */
    HELP_STR_GADGE_BOT_ACTIONS = 0x00005298,  /* "Gadge-Bot actions" */
    HELP_STR_GLIDE_REMINDER = 0x00005299,  /* "Glide reminder" */
    HELP_STR_FORCEFIELD_HINT = 0x0000529A,  /* "Forcefield hint" */
    HELP_STR_GRINDBOOTS_DESCRIPTION = 0x0000529B,  /* "Grindboots description" */
    HELP_STR_HYDRODISPLACER_DESCRIPTION = 0x0000529C,  /* "Hydrodisplacer description" */
    HELP_STR_STRATEGY_AGAINST_BLARG = 0x0000529D,  /* "Strategy against Blarg" */
    HELP_STR_BATTLE_SUGGESTION = 0x0000529E,  /* "Battle suggestion" */
    HELP_STR_YOU_NEED_GRINDBOOTS = 0x0000529F,  /* "You need Grindboots" */
    HELP_STR_HOW_TO_USE_GRINDBOOTS = 0x000052A0,  /* "How to use Grindboots" */
    HELP_STR_YOU_NEED_MAGNEBOOTS = 0x000052A1,  /* "You need Magneboots" */
    HELP_STR_METAL_DETECTOR_DESCRIPTION = 0x000052A2,  /* "Metal Detector description" */
    HELP_STR_PILOTS_HELMET_DESCRIPTION = 0x000052A3,  /* "Pilot's Helmet description" */
    HELP_STR_TIPTOE_HELP = 0x000052A4,  /* "Tiptoe help" */
    HELP_STR_CLANK_AND_MAGNEBOOTS = 0x000052A5,  /* "Clank and Magneboots" */
    HELP_STR_PREMIUM_NANOTECH_INFO = 0x000052A6,  /* "Premium Nanotech info" */
    HELP_STR_ULTRA_NANOTECH_INFO = 0x000052A7,  /* "Ultra Nanotech info" */
    HELP_STR_ORXON_EXPLORATION = 0x000052A8,  /* "Orxon exploration" */
    HELP_STR_O2_MASK_DESCRIPTION = 0x000052A9,  /* "O2 Mask description" */
    HELP_STR_PERSUADER_DESCRIPTION = 0x000052AA,  /* "Persuader description" */
    HELP_STR_NEED_PILOTS_HELMET = 0x000052AB,  /* "Need Pilot's Helmet" */
    HELP_STR_POWER_SLAM_EXPLAINED = 0x000052AC,  /* "Power Slam explained" */
    HELP_STR_HYDRO_PACK_DESCRIPTION = 0x000052AD,  /* "Hydro-Pack description" */
    HELP_STR_RARITANIUM_DESCRIPTION = 0x000052AE,  /* "Raritanium description" */
    HELP_STR_LOOK_AROUND_MODE = 0x000052AF,  /* "Look-around mode" */
    HELP_STR_FIRST_PERSON_AND_WEAPONS = 0x000052B0,  /* "First-person and weapons" */
    HELP_STR_BOLT_CRANK_EXPLANATION = 0x000052B1,  /* "Bolt crank explanation" */
    HELP_STR_ACTIVATING_MAP = 0x000052B2,  /* "Activating map" */
    HELP_STR_SWIMMING_HELP = 0x000052B3,  /* "Swimming help" */
    HELP_STR_MOUSE_HELP = 0x000052B4,  /* "Mouse help" */
    HELP_STR_INVINCO_LOCK_DIRECTIONS = 0x000052B5,  /* "Invinco-Lock directions" */
    HELP_STR_INVINCO_LOCK_HELP = 0x000052B6,  /* "Invinco-Lock help" */
    HELP_STR_HOW_TO_ACTIVATE_MAP = 0x000052B7,  /* "How to activate map" */
    HELP_STR_WALL_JUMP_REMINDER = 0x000052B8,  /* "Wall jump reminder" */
    HELP_STR_AIMING_THE_BLASTER = 0x000052B9,  /* "Aiming the Blaster" */
    HELP_STR_SPEND_YOUR_BOLTS = 0x000052BA,  /* "Spend your bolts!" */
    HELP_STR_CAMERA_CONTROL = 0x000052BB,  /* "Camera control" */
    HELP_STR_BOOST_JUMP_HELP = 0x000052BC,  /* "Boost Jump help" */
    HELP_STR_CONSTANT_FLAME = 0x000052BD,  /* "Constant flame" */
    HELP_STR_QUICKSELECT_HELP = 0x000052BE,  /* "QuickSelect help" */
    HELP_STR_QUICKSELECT_INTRODUCTION = 0x000052BF,  /* "QuickSelect introduction" */
    HELP_STR_RISE_WHILE_SWIMMING = 0x000052C0,  /* "Rise while swimming" */
    HELP_STR_NEED_O2_MASK = 0x000052C1,  /* "Need O2 mask" */
    HELP_STR_SHUTTLE_EXPLANATION = 0x000052C2,  /* "Shuttle explanation" */
    HELP_STR_JUMP_SLOTS = 0x000052C3,  /* "Jump slots" */
    HELP_STR_JET_FIGHTER_INSTRUCTIONS = 0x000052C4,  /* "Jet fighter instructions" */
    HELP_STR_LOCK_ON_MISSILES = 0x000052C5,  /* "Lock-on missiles" */
    HELP_STR_GET_MISSILES = 0x000052C6,  /* "Get missiles" */
    HELP_STR_GET_HEALTH = 0x000052C7,  /* "Get health" */
    HELP_STR_JET_TURBO = 0x000052C8,  /* "Jet turbo" */
    HELP_STR_BUY_THE_DEVASTATOR = 0x000052C9,  /* "Buy the Devastator!" */
    HELP_STR_PARATROOPER_STRATEGY = 0x000052CA,  /* "Paratrooper strategy" */
    HELP_STR_BLARG_SAUCER_STRATEGY = 0x000052CB,  /* "Blarg saucer strategy" */
    HELP_STR_HELICOPTER_STRATEGY = 0x000052CC,  /* "Helicopter strategy" */
    HELP_STR_ACROSS_THE_GAP = 0x000052CD,  /* "Across the gap" */
    HELP_STR_HOVERBOARD_TRICKS = 0x000052CE,  /* "Hoverboard tricks" */
    HELP_STR_TURN_OFF_HELPDESK = 0x000052CF,  /* "Turn off HelpDesk" */
    HELP_STR_HELI_PACK_HINTS = 0x000052D0,  /* "Heli-Pack hints" */
    HELP_STR_EQUIP_THE_BLASTER = 0x000052D1,  /* "Equip the Blaster" */
    HELP_STR_USE_THE_SWINGSHOT = 0x000052D2,  /* "Use the Swingshot" */
    HELP_STR_SWINGSHOT_CAUTION_2 = 0x000052D3,  /* "Swingshot caution" */
    HELP_STR_QUICKSELECT_INSTRUCTIONS = 0x000052D4,  /* "QuickSelect instructions" */
    HELP_STR_LOOK_AROUND_2 = 0x000052D5,  /* "Look around" */
    HELP_STR_MAP_GUIDANCE = 0x000052D6,  /* "Map guidance" */
    HELP_STR_CONGRATULATIONS = 0x000052D7,  /* "Congratulations" */
    HELP_STR_NEED_DEVASTATOR = 0x000052D8,  /* "Need Devastator" */
    HELP_STR_BOT_PORTS_2 = 0x000052D9,  /* "Bot-Ports" */
    HELP_STR_BOT_DEVICE_2 = 0x000052DA,  /* "Bot-Device" */
    HELP_STR_POWER_SLAM_EXPLAINED_2 = 0x000052DB,  /* "Power Slam explained" */
    HELP_STR_HOW_TO_STRAFE = 0x000052DC,  /* "How to strafe" */
    HELP_STR_STRAFE_LEFT_AND_RIGHT = 0x000052DD,  /* "Strafe left and right" */
    HELP_STR_DESTROY_THE_TOWERS = 0x000052DE,  /* "Destroy the towers" */
    HELP_STR_USE_THE_MAGNEBOOTS = 0x000052DF,  /* "Use the Magneboots" */
    HELP_STR_SLAM_SWITCH = 0x000052E0,  /* "Slam switch" */
    HELP_STR_SWIMMING_SURVIVAL = 0x000052E1,  /* "Swimming survival" */
    HELP_STR_MISSIONS_FINISHED = 0x000052E2,  /* "Missions finished" */
    HELP_STR_INTERRUPT_HELPDESK = 0x000052E3,  /* "Interrupt HelpDesk" */
    HELP_STR_SAVE_ICON = 0x000052E4,  /* "Save icon" */
    HELP_STR_REVERSE_CAMERA = 0x000052E5,  /* "Reverse camera" */
    HELP_STR_DOUBLE_TAP_TRIANGLE = 0x000052E6,  /* "Double-tap triangle" */
    HELP_STR_HYRDO_PACK_TURBOJETS = 0x000052E7,  /* "Hyrdo-Pack turbojets" */
    HELP_STR_CENTER_CAMERA = 0x000052E8,  /* "Center camera" */
    HELP_STR_MORPH_O_RAY_INTRODUCTION = 0x000052E9,  /* "Morph-o-ray introduction" */
    HELP_STR_NEED_HOLOGUISE = 0x000052EA,  /* "Need Hologuise" */
    HELP_STR_USE_THE_HOLOGUISE = 0x000052EB,  /* "Use the Hologuise" */
    HELP_STR_WAVING = 0x000052EC,  /* "Waving" */
    HELP_STR_HOLOGUISE_DESCRIPTION = 0x000052ED,  /* "Hologuise description" */
    HELP_STR_GIANT_CLANK_INSTRUCTIONS = 0x000052EE,  /* "Giant Clank instructions" */
    HELP_STR_ATOMIC_BLAST = 0x000052EF,  /* "Atomic blast" */
    HELP_STR_TESLA_CLAW_USE = 0x000052F0,  /* "Tesla Claw use" */
    HELP_STR_NEED_HYDRO_PACK = 0x000052F1,  /* "Need Hydro-Pack" */
    HELP_STR_RACE_ROCKETS = 0x000052F2,  /* "Race rockets" */
    HELP_STR_MAP_O_MATIC_INSTRUCTIONS = 0x000052F3,  /* "Map-o-matic instructions" */
    HELP_STR_STOP_THE_COUNTDOWN = 0x000052F4,  /* "Stop the countdown!" */
    HELP_STR_LOCATING_RARITANIUM = 0x000052F5,  /* "Locating Raritanium" */
    HELP_STR_NEED_HOVERBOARD = 0x000052F6,  /* "Need hoverboard" */
    HELP_STR_SENTRY_BOT_WARNING = 0x000052F7,  /* "Sentry-bot warning" */
    HELP_STR_INSTANT_DEATH = 0x000052F8,  /* "Instant death" */
    HELP_STR_HOLOGUISE_COLORS = 0x000052F9,  /* "Hologuise colors" */
    HELP_STR_FIND_ANOTHER_WAY = 0x000052FA,  /* "Find another way" */
    HELP_STR_RESET_TIMER = 0x000052FB,  /* "Reset timer" */
    HELP_STR_TIME_IS_SHORT = 0x000052FC,  /* "Time is short" */
    HELP_STR_METAL_DETECTOR_HELP = 0x000052FD,  /* "Metal Detector help" */
    HELP_STR_HOLOGUISE_HELP = 0x000052FE,  /* "Hologuise help" */
    HELP_STR_SONIC_SUMMONER_HELP_2 = 0x000052FF,  /* "Sonic Summoner help" */
    HELP_STR_SKILL_POINTS_4 = 0x00005300,  /* "Skill points" */
    HELP_STR_GOLD_WEAPON_PURCHASE = 0x00005301,  /* "Gold Weapon purchase" */
    HELP_STR_GOLD_WEAPON_PURCHASE_2 = 0x00005302,  /* "Gold Weapon purchase" */
    HELP_STR_KYZIL_PLATEAU_PLANET_VELDIN = 0x00005303,  /* "Kyzil Plateau, Planet Veldin" */
    HELP_STR_AM_LOCAL_TIME = 0x00005304,  /* "(11:13am local time) " */
    HELP_STR_MEANWHILE_IN_A_FACTORY_0x5305 = 0x00005305,  /* "Meanwhile, in a factory on a nearby planet�" */
    HELP_STR_APPROACHING_PLANET_VELDIN = 0x00005306,  /* "Approaching Planet Veldin�" */
    HELP_STR_AM_LOCAL_TIME_2 = 0x00005307,  /* "(11:47am local time) " */
    HELP_STR_CHAIRMAN_DREKS_FLAGSHIP = 0x00005308,  /* "Chairman Drek's flagship" */
    HELP_STR_VELDIN_ORBIT_2 = 0x00005309,  /* "Veldin Orbit " */
    HELP_STR_BACK_ON_CHAIRMAN_DREKS_0x530A = 0x0000530A,  /* "Back on Chairman Drek's flagship" */
    HELP_STR_ENTERING_ATMOSPHERE_OF_PLANET_0x530B = 0x0000530B,  /* "Entering atmosphere of Planet Novalis" */
    HELP_STR_MEANWHILE_ABOARD_EXECUTIVE_CHAIRMAN_0x530C = 0x0000530C,  /* "Meanwhile aboard Executive Chairman Drek's flagship� " */
    HELP_STR_EUDORA_ORBIT = 0x0000530D,  /* "Eudora Orbit " */
    HELP_STR_ELSEWHERE_ABOARD_SUPREME_EXECUTIVE_0x530E = 0x0000530E,  /* "Elsewhere, aboard Supreme Executive Chairman Drek's flagship�" */
    HELP_STR_SUPREME_EXECUTIVE_CHAIRMAN_DREKS_0x530F = 0x0000530F,  /* "Supreme Executive Chairman Drek's flagship" */
    HELP_STR_OLTANIS_ORBIT_2 = 0x00005310,  /* "Oltanis Orbit " */
    HELP_STR_ULTIMATE_SUPREME_EXECUTIVE_CHAIRMAN_0x5311 = 0x00005311,  /* "Ultimate Supreme Executive Chairman Drek's flagship�" */
    HELP_STR_ULTIMATE_SUPREME_EXECUTIVE_CHAIRMAN_0x5312 = 0x00005312,  /* "Ultimate Supreme Executive Chairman Drek's flagship�" */
    HELP_STR_KALEBO_III_ORBIT = 0x00005313,  /* "Kalebo III orbit " */
    HELP_STR_GADGETRON_VENDOR = 0x00005314,  /* "Gadgetron Vendor" */
    HELP_STR_BOLT_ICON = 0x00005315,  /* "Bolt Icon" */
    HELP_STR_SECURITYBOTS = 0x00005316,  /* "SecurityBots" */
    HELP_STR_MOUSE_HOUSE = 0x00005317,  /* "Mouse House" */
    HELP_STR_BLARG_FIGHER = 0x00005318,  /* "Blarg Figher" */
    HELP_STR_GRINDRAIL = 0x00005319,  /* "Grindrail" */
    HELP_STR_WRONG_WAY_ = 0x0000531A,  /* "Wrong Way !" */
    HELP_STR_BEST_TIME = 0x0000531B,  /* "Best Time" */
    HELP_STR_BEST_SCORE = 0x0000531C,  /* "Best Score" */
    HELP_STR_JAPANESE = -0x4D2,  /* "Japanese" */
    HELP_STR_D_LEVEL = 0x0000EA60  /* "3D Level" */
};

#endif
