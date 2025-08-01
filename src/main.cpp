#include <Geode/Geode.hpp>
#include <Windows.h>
#include <stdio.h>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/DailyLevelPage.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;
// DailyLevelNode::onExit
HWND hwnd = FindWindow(NULL, "Geometry Dash");
bool ChangeGameWindowTitle(std::string param) {
	if (param == "") param = "Geometry Dash";
	else param += " - Geometry Dash";

	LPCSTR lpcstr = param.c_str();

	if (hwnd == NULL) return false;
	else {
		SetWindowText(hwnd, lpcstr);
		return true;
	}
}

/*
	Layers
*/
/*
class $modify(MenuLayer) {
	bool init() {
		if (!init()) return false;
		ChangeGameWindowTitle("Main Menu");
		return true;
	};
};


//	I got this links from the Discord Rich Presence mod, bcause i got some inspiration from TechStudent10's mod.


class $modify(CreatorLayer) {

	bool init() {
		if (!init()) return false;
		ChangeGameWindowTitle("Creator Tab");
		return true;
	}

	void onLeaderboards(CCObject* p0) {
		ChangeGameWindowTitle("Leaderboards");
		return CreatorLayer::onLeaderboards(p0);
	}

	void onMyLevels(CCObject* p0) {
		ChangeGameWindowTitle("Created Levels");
		return CreatorLayer::onMyLevels(p0);
	}

	void onSavedLevels(CCObject* p0) {
		ChangeGameWindowTitle("Saved Levels");
		return CreatorLayer::onSavedLevels(p0);
	}

	void onMapPacks(CCObject* p0) {
		ChangeGameWindowTitle("Map Packs");
		return CreatorLayer::onMapPacks(p0);
	}

	void onDailyLevel(CCObject* p0) {
		ChangeGameWindowTitle("Daily");
		return CreatorLayer::onDailyLevel(p0);
	}

	void onWeeklyLevel(CCObject* p0) {
		ChangeGameWindowTitle("Weekly");
		return CreatorLayer::onWeeklyLevel(p0);
	}

	void onFeaturedLevels(CCObject* p0) {
		ChangeGameWindowTitle("Featured Tab");
		return CreatorLayer::onFeaturedLevels(p0);
	}

	void onGauntlets(CCObject* p0) {
		ChangeGameWindowTitle("Gauntlets");
		return CreatorLayer::onGauntlets(p0);
	}

	void onAdventureMap(CCObject* p0) {
		ChangeGameWindowTitle("The Map");
		return CreatorLayer::onAdventureMap(p0);
	}

	void onEventLevel(CCObject* p0) {
		ChangeGameWindowTitle("Event Level");
		return CreatorLayer::onEventLevel(p0);
	}

	void onMultiplayer(CCObject* p0) {
		ChangeGameWindowTitle("Versus Mode");
		return CreatorLayer::onMultiplayer(p0);
	}
	
	void onPaths(CCObject* p0) {
		ChangeGameWindowTitle("The Paths");
		return CreatorLayer::onPaths(p0);
	}

	void onSecretVault(CCObject* p0) {
		ChangeGameWindowTitle("Vault of Secrets");
		return CreatorLayer::onSecretVault(p0);
	}

	void onTopLists(CCObject* p0) {
		ChangeGameWindowTitle("Lists");
		return CreatorLayer::onTopLists(p0);
	}

	void onTreasureRoom(CCObject* p0) {
		ChangeGameWindowTitle("Treasure Room");
		return CreatorLayer::onTreasureRoom(p0);
	}

	void onChallenge(CCObject* p0) {
		ChangeGameWindowTitle("Quests"); 
		return CreatorLayer::onChallenge(p0);
	}
};

class $modify(LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;
		ChangeGameWindowTitle("Search Tab");
		return true;
	}

	void onBack(CCObject* sender) {
		LevelSearchLayer::onBack(sender);
		ChangeGameWindowTitle("Creator Tab");
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level, bool p1) {
		if (!LevelInfoLayer::init(level, p1)) return false;

		std::string newTitle = std::string(level->m_levelName) + " by " + std::string(level->m_creatorName);
		ChangeGameWindowTitle(newTitle);
		return true;
	}
};

class $modify(DailyLevelPage) {
	void onClose(CCObject* sender) {
		DailyLevelPage::onClose(sender);
		ChangeGameWindowTitle("Creator Tab");
	}
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* p0) {
		if (!LevelBrowserLayer::init(p0)) return false;
		log::info("Exited LevelBrowserLayer. Sender: {}", sender);
		return true;
	}

	void onBack(CCObject* sender) {
		log::info("Exited LevelBrowserLayer. Sender: {}", sender);
		LevelBrowserLayer::onBack(sender);
	}
};
*/
class $modify(PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		std::string newWindowTitle = (level->m_levelName) + " by " + (level->m_creatorName);
		ChangeGameWindowTitle(newWindowTitle);
		return true;
	}

	void postUpdate(float p0) {
		std::string name = "";
		if (m_level->m_creatorName == "") name = "RobTop";
		else name = (m_level->m_creatorName);

		std::string newWindowTitle = (m_level->m_levelName) + " by " + name + " (" + (std::to_string(getCurrentPercentInt())) + "%)";
		ChangeGameWindowTitle(newWindowTitle);

		PlayLayer::postUpdate(p0);
	}

	void pauseGame(bool p0) {
		std::string name = "";
		if (m_level->m_creatorName == "") name = "RobTop";
		else name = m_level->m_creatorName;

		std::string newWindowTitle = (m_level->m_levelName) + " by " + name + " (" + (std::to_string(getCurrentPercentInt())) + "% - Paused)";
		ChangeGameWindowTitle(newWindowTitle);

		PlayLayer::pauseGame(p0);
	}

	void onQuit() {
		ChangeGameWindowTitle("");
		PlayLayer::onQuit();
	}
};