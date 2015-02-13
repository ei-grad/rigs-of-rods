/*
	This source file is part of Rigs of Rods
	Copyright 2005-2012 Pierre-Michel Ricordel
	Copyright 2007-2012 Thomas Fischer
	Copyright 2013-2014 Petr Ohlidal

	For more information, see http://www.rigsofrods.com/

	Rigs of Rods is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License version 3, as
	published by the Free Software Foundation.

	Rigs of Rods is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

/** 
	@file   GUI_GameAbout.cpp
	@author Moncef Ben Slimane
	@date   11/2014
*/

#include "GUI_GameAbout.h"

#include "RoRPrerequisites.h"
#include "Utils.h"
#include "RoRVersion.h"
#include "rornet.h"
#include "Language.h"
#include "GUIManager.h"
#include "Application.h"

#include <MyGUI.h>


using namespace RoR;
using namespace GUI;

#define CLASS        GameAbout
#define MAIN_WIDGET  ((MyGUI::Window*)mMainWidget)

CLASS::CLASS()
{
	MyGUI::WindowPtr win = dynamic_cast<MyGUI::WindowPtr>(mMainWidget);
	win->eventWindowButtonPressed += MyGUI::newDelegate(this, &CLASS::notifyWindowButtonPressed); //The "X" button thing
	
	m_backbtn->eventMouseButtonClick      += MyGUI::newDelegate(this, &CLASS::eventMouseButtonClickBackButton);
	m_ror_version->setCaption(Ogre::String(ROR_VERSION_STRING));
	m_net_version->setCaption(Ogre::String(RORNET_VERSION));
	m_build_time->setCaption(Ogre::String(__DATE__) + ", " + Ogre::String(__TIME__));
  
    initMisc();
	CenterToScreen();
	
	Hide();
}

CLASS::~CLASS()
{

}

void CLASS::Show()
{
	MAIN_WIDGET->setVisibleSmooth(true);
}

void CLASS::Hide()
{
	MAIN_WIDGET->setVisibleSmooth(false);
	Application::GetGuiManager()->ShowMainMenu(true);
}

void CLASS::CenterToScreen()
{
	MyGUI::IntSize windowSize = MAIN_WIDGET->getSize();
	MyGUI::IntSize parentSize = MAIN_WIDGET->getParentSize();

	MAIN_WIDGET->setPosition((parentSize.width - windowSize.width) / 2, (parentSize.height - windowSize.height) / 2);
}

bool CLASS::IsVisible()
{
	return MAIN_WIDGET->isVisible();
}

void CLASS::initMisc()
{
	Ogre::UTFString AuthorsText = "";
	Ogre::UTFString orange      = U("#FF7D02"); // colour key shortcut
	Ogre::UTFString white       = U("#FFFFFF"); // colour key shortcut
	Ogre::UTFString color1      = U("#66FF33"); // colour key shortcut
	Ogre::UTFString newline     = U("\n");

	//Authors:
	AuthorsText = orange + "Authors:" + newline;
	AuthorsText = AuthorsText + color1 + "Pierre-Michel Ricordel (pricorde):" + white + " Physics Genius, Original Author, Core Developer, retired" + newline;
	AuthorsText = AuthorsText + color1 + "Thomas Fischer (tdev):" + white + " Core Developer, inactive" + newline;	
	
	//Current Project devs:
	AuthorsText = AuthorsText + newline;
	AuthorsText = AuthorsText + orange + "Current Developers:" + newline;
	AuthorsText = AuthorsText + color1 + "only_a_ptr:" + white + " Core Developer, active" + newline;
	AuthorsText = AuthorsText + color1 + "Hiradur:" + white + " Linux fixes, few tweaks, active" + newline;
	AuthorsText = AuthorsText + color1 + "max98:" + white + " Few fixes, Few improvements, GUI Overhaul, active" + newline;

	
	//Code Contributors:
	AuthorsText = AuthorsText + newline;
	AuthorsText = AuthorsText + orange + "Code Contributors:" + newline;
	AuthorsText = AuthorsText + color1 + "Estama:" + white + " Physics Core Optimizations, Collision/Friction code, Support Beams" + newline;
	AuthorsText = AuthorsText + color1 + "Lifter:" + white + " Triggers, Animators, Animated Props, Shocks2" + newline;
	AuthorsText = AuthorsText + color1 + "Aperion:" + white + " Slidenodes, Axles, Improved Engine code, Rigidifiers, Networking code" + newline;
	AuthorsText = AuthorsText + color1 + "FlyPiper:" + white + " Inertia Code, minor patches" + newline; 
	AuthorsText = AuthorsText + color1 + "knied:" + white + " MacOSX Patches" + newline;
	AuthorsText = AuthorsText + color1 + "altren:" + white + " Coded some MyGUI windows" + newline;
	AuthorsText = AuthorsText + color1 + "petern:" + white + " Repair on spot, Linux patches" + newline;
	AuthorsText = AuthorsText + color1 + "imrenagy:" + white + " Moving chair hardware support, several fixes" + newline;
	AuthorsText = AuthorsText + color1 + "priotr:" + white + " Several Linux fixes" + newline;
	AuthorsText = AuthorsText + color1 + "neorej16:" + white + " AngelScript improvements" + newline;
	AuthorsText = AuthorsText + color1 + "cptf:" + white + " Several Linux gcc fixes" + newline;
	AuthorsText = AuthorsText + color1 + "88Toyota:" + white + " Clutch force patches" + newline;
	AuthorsText = AuthorsText + color1 + "synthead:" + white + " Minor Linux fixes" + newline;
	AuthorsText = AuthorsText + color1 + "ulteq:" + white + " sound engine, lots of fixes" + newline;
	AuthorsText = AuthorsText + color1 + "theshark:" + white + " various fixes" + newline;
	AuthorsText = AuthorsText + color1 + "Clockwork (a.k.a VeyronEB):" + white + " GUI Designer and tweaker" + newline;
	AuthorsText = AuthorsText + color1 + "Klink:" + white + " Terrains conversion, few fixes and tweaks, dashboard designer" + newline;
	AuthorsText = AuthorsText + color1 + "hagdervriese:" + white + " Linux fixes" + newline;

	//Core Content Contributors
	AuthorsText = AuthorsText + newline;
	AuthorsText = AuthorsText + orange + "Core Content Contributors:" + newline;
	AuthorsText = AuthorsText + color1 + "donoteat:" + white + " Improved spawner models, terrain work" + newline;
	AuthorsText = AuthorsText + color1 + "kevinmce:" + white + " old Character" + newline;
	AuthorsText = AuthorsText + color1 + "09Challenger:" + white + " new character animations" + newline;

	//Mod Contributors
	AuthorsText = AuthorsText + newline;
	AuthorsText = AuthorsText + orange + "Mod Contributors:" + newline;
	AuthorsText = AuthorsText + color1 + "The Rigs of Rods community:" + white + " Provides us with lots of mods to play with" + newline;

	//Testers
	AuthorsText = AuthorsText + newline;
	AuthorsText = AuthorsText + orange + "Testers:" + newline;
	AuthorsText = AuthorsText + color1 + "Invited core team:" + white + " The invited members helped us a lot along the way at various corners" + newline;
	AuthorsText = AuthorsText + color1 + "Project 'NextStable' testers:" + white + " Testing and reporting bugs" + newline;

	//Used Libs 
	AuthorsText = AuthorsText + newline;
	AuthorsText = AuthorsText + orange + "Used Libs:" + newline;
	AuthorsText = AuthorsText + color1 + "Ogre3D:" + white + " 3D rendering engine" + newline;
	AuthorsText = AuthorsText + color1 + "Caelum:" + white + " Atmospheric effects" + newline;
	AuthorsText = AuthorsText + color1 + "Hydrax:" + white + " Water rendering" + newline;
	AuthorsText = AuthorsText + color1 + "AngelScript:" + white + " Scripting Backend" + newline;
#ifdef USE_OPENAL
	AuthorsText = AuthorsText + color1 + "OpenAL Soft:" + white + " Sound engine" + newline;
#endif
	AuthorsText = AuthorsText + color1 + "MyGUI:" + white + " GUI System" + newline;
	AuthorsText = AuthorsText + color1 + "CrashRpt:" + white + " Crash Reporting system" + newline;
	AuthorsText = AuthorsText + color1 + "mofilereader:" + white + " Used for Internationalization" + newline;
	AuthorsText = AuthorsText + color1 + "OIS:" + white + " Used as Input System" + newline;
	AuthorsText = AuthorsText + color1 + "pagedGeometry:" + white + " Used for foliage (grass, trees, etc)" + newline;
	AuthorsText = AuthorsText + color1 + "pthreads:" + white + " Used for threading" + newline;
	AuthorsText = AuthorsText + color1 + "curl:" + white + " Used for www-server communication" + newline;
	AuthorsText = AuthorsText + color1 + "SocketW:" + white + " Used as cross-platform socket abstraction" + newline;
	AuthorsText = AuthorsText + color1 + "boost:" + white + " Used as glue in between the components" + newline;
	AuthorsText = AuthorsText + color1 + "wxWidgets:" + white + " Used as cross platform user interface toolkit" + newline;


	m_authors->setCaption(Ogre::String(AuthorsText));
	m_authors->setVScrollPosition(0);
}

void CLASS::eventMouseButtonClickBackButton(MyGUI::WidgetPtr _sender)
{
	Hide();
}

void CLASS::notifyWindowButtonPressed(MyGUI::WidgetPtr _sender, const std::string& _name)
{
	if (_name == "close")
		Hide();
}