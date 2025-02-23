#include "storm-engine\layers.h"
#include "storm-engine\events.h"

#include "_mod_on_off.h"
#include "globals.c"
#include "animals.c"
#include "NumberUtilities.c" // Warship 26.07.09. Работа с числами
#include "sea_ai\sea.c"
#include "ships\ships.c"
#include "Encounters\Encounters.c"
#include "worldmap\worldmap.c"
#include "locations\locations.c"
#include "Loc_ai\LAi_init.c"
#include "store\goods.h"
#include "cannons\cannons.c"
#include "nations\nations.c"
#include "particles.c"
#include "characters\characters.c"
#include "interface\interface.h"
#include "store\storeutilite.c"
#include "dialog.c"
#include "quests\quests.c"
#include "islands\islands.c"
#include "colonies\colonies.c"
#include "reload.c"
#include "battle_interface\loginterface.c"
#include "calendar.c"
#include "teleport.c"
#include "utils.c"
#include "weather\WhrWeather.c"
#include "controls\controls.c"
#include "ITEMS\items.h"
#include "ITEMS\itemLogic.c"
#include "ITEMS\items_utilite.c"
#include "store\store.h"
#include "interface\interface.c"
#include "OnLoadReinit.c"
// Addon things -->
#include "Addons\utils.c"
// Addon things <--
#include "Controls\hotkey_travel.c"
//// {*} BUHO-CIC - ADDED CODE - CIC vars and routines.
#include "BUHO_CIC.c"
//// {*} BUHO END ADDITION

extern void ShipsInit(); //Boyer add
extern void InitBaseCannons();
extern void InitCharacters();
extern void InitBaseInterfaces();

extern void wdmInitWorldMap();
extern void InitGoods();
extern void InitStores();
extern int InitItems();
extern void InitCharactersTables();
extern void InitCharactersNames();
extern void InitPiratesNames();
extern void InitGeneratorNames();
extern void CreateCharacters();

extern void ActiveF4Control(); // boal debuger
extern void ActiveF5Control(); // boal debuger
extern void ActiveF7Control(); // boal debuger
extern void ActiveF10Control(); // boal debuger
extern void ActiveF12Control(); // boal debuger
extern void ActiveINSERTControl(); // boal debuger

native float Bring2RangeNoCheck(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Bring2Range(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Degree2Radian(float fDegree);
native float Clampf(float fValue);
native int RDTSC_B();
native int RDTSC_E(int iRDTSC);

native int SetTexturePath(int iLevel, string sPath);
native int SetGlowParams(float fBlurBrushSize, int Intensivity, int BlurPasses);
native int RPrint(int x, int y, string sPrint);
native int GetTexture(string name);
native void ReleaseTexture(int texId);

#libriary "script_libriary_test"
#libriary "dx9render_script_libriary"

#event_handler(NEW_GAME_EVENT,"NewGame");
#event_handler(GAME_OVER_EVENT,"GameOverE");
#event_handler("Control Activation","ProcessControls");
#event_handler("MainMenuKey","ProcessMainMenuKey");
#event_handler("InterfaceKey","ProcessInterfaceKey");
#event_handler("CameraPosAng","ProcessCameraPosAng");
#event_handler("Cheat","ProcessCheat");
#event_handler("SeaDogs_ClearSaveData", "ClearLocationsSaveData");
#event_handler("StopQuestCheckProcessFreeze","ProcessStopQuestCheckProcessFreeze"); // boal 240804
//#20171009-03
#event_handler("ResetDevice", "ResetDevice");

float fHighPrecisionDeltaTime;

#define CONFIRMMODE_PROFILE_DELETE	1
#define CONFIRMMODE_SAVE_DELETE		2
#define CONFIRMMODE_SAVE_OVERWRITE	3
#define CONFIRMMODE_LOAD_GAME		4

int g_nConfirmMode;
string g_sConfirmReturnWindow;
int g_nInterfaceFileID = -1;

void DoConfirm( int nConfirmMode )
{
	g_sConfirmReturnWindow = "MAIN_WINDOW";
	if( XI_IsWindowEnable("PROFILE_WINDOW") ) {
		g_sConfirmReturnWindow = "PROFILE_WINDOW";
	}
	XI_WindowDisable( g_sConfirmReturnWindow, true );
	// enable confirm window
	XI_WindowDisable( "CONFIRM_WINDOW", false );
	XI_WindowShow( "CONFIRM_WINDOW", true );
	SetCurrentNode( "CONFIRM_YES" );

	g_nConfirmMode = nConfirmMode;
	switch( nConfirmMode )
	{
	case CONFIRMMODE_PROFILE_DELETE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete profile confirm") );
		break;
	case CONFIRMMODE_SAVE_DELETE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete savefile confirm") );
		break;
	case CONFIRMMODE_SAVE_OVERWRITE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Overwrite savefile confirm") );
		break;
	case CONFIRMMODE_LOAD_GAME:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Load game confirm") );
		break;
	}
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONFIRM_TEXT", 5 ); // центрируем по вертикали
}

void ProcessStopQuestCheckProcessFreeze() // boal 240804
{
    bQuestCheckProcessFreeze = false;
    wdmLockReload            = false;
    QuestsCheck(); // выполнить отложенные

    if (rand(20) == 10) // 16.01.06 не помню уже зачем разлочивал ГГ, но на деле мешает до квестам, но если где повиснет, то спасет ф2
    {
    	DoQuestCheckDelay("pchar_back_to_player", 0.5); // если в диалоге залочило, вернем управление
    }
}

void ProcessVersionCheck() // boal 271004
{
    ref mc = GetMainCharacter();

    if (CheckAttribute(mc, "HeroParam")) // признак, что есть герой
    {
        if (!CheckAttribute(mc, "VersionNumber"))
    	{
            Log_Info("Загружена старая сохраненная запись.");
            Log_Info("Возможна нестабильная работа программы.");
    	}
        else
        {
            if (sti(mc.VersionNumberCompatibility) < VERSION_NUM_PRE && mc.VersionNumber != GetVerNum())
            {
                Log_Info("Загружена сохраненная запись версии " + mc.VersionNumber +".");
                Log_Info("Возможна нестабильная работа программы.");
            }
        }
    }
}

void ProcessCheat()
{
	string sCheatName;
	ref mc;
	sCheatName = GetEventData();
	mc = GetMainCharacter();

	switch(sCheatName)
	{
		case "Immortal":
			if(LAi_IsImmortal(GetMainCharacter()))
			{
				LAi_SetImmortal(GetMainCharacter(), false);
				Log_SetStringToLog("God mode OFF");
			}else{

				LAi_SetImmortal(GetMainCharacter(), true);
				Log_SetStringToLog("God mode ON");
			}
		break;
		case "ShotGun":
			if(globalSGMode != false)
			{
				globalSGMode = false;
				Log_SetStringToLog("Shotgun mode OFF");
			}else{
				globalSGMode = true;
				Log_SetStringToLog("Shotgun mode ON");
			}
		break;
		case "Gold":
			mc.money = sti(mc.money) + 100000;
			Log_SetStringToLog(" + 100000 G");
		break;
		case "Skill":
			mc.skill.freeskill = 1;

			mc.skill.freeskill = sti(mc.skill.freeskill) + 50;
			Log_SetStringToLog(" + 50 SP");
		break;
		case "Reputation":
			mc.reputation = REPUTATION_NEUTRAL;
			Log_SetStringToLog("Reputation Set to NEUTRAL");
		break;
		case "Morale":

		break;
		case "Encounters":
			if(CheckAttribute(mc,"worldmapencountersoff") == 0)
			{
				mc.worldmapencountersoff = "1";
				Log_SetStringToLog("Worldmap encounters OFF");
			}
			else
			{
				if(mc.worldmapencountersoff == "1")
				{
					mc.worldmapencountersoff = "0";
					Log_SetStringToLog("Worldmap encounters ON");
				}
				else
				{
					mc.worldmapencountersoff = "1";
					Log_SetStringToLog("Worldmap encounters OFF");
				}
			}
		break;
		case "MainCharacter":
			mc.model	= "Danielle";
			mc.sex = "woman";
			mc.FaceId = 30;
			mc.model.animation = "woman";
			mc.model.height = 1.75;
		break;
		case "soundoff":
			SendMessage(&Sound,"ll",MSG_SOUND_SET_ENABLED,0);
			Log_SetStringToLog("Sound OFF");
		break;
	}
}

object Camera;

void ProcessCameraPosAng()
{
	Camera.Pos.x = GetEventData();
	Camera.Pos.y = GetEventData();
	Camera.Pos.z = GetEventData();

	Camera.Ang.x = GetEventData();
	Camera.Ang.y = GetEventData();
	Camera.Ang.z = GetEventData();
}

void proc_break_video()
{
	PictureAsVideoBreak();
	if (sti(InterfaceStates.videoIdx) != 1)
	{
	}
}

void Main()
{
	if (!CheckAttribute(InterfaceStates,"VISUAL_CIRASS")) InterfaceStates.VISUAL_CIRASS = 0;
	screenscaling = BI_COMPARE_HEIGHT;
    //LayerCreate(REALIZE, 1);
	//LayerCreate(SEA_REALIZE, 1);
	//LayerCreate("net_realize", 1);
	//LayerCreate(INTERFACE_REALIZE, 1);
	//LayerCreate("fader_realize", 1);
	//LayerCreate("inf_realize", 1);

	ReloadProgressStart();

	ControlsInit(GetTargetPlatform(),true, 0);
	nTeleportLocation = 1;

	NationsInit();
	ReloadProgressUpdate();

	EncountersInit();
	ReloadProgressUpdate();

	CannonsInit();
	ReloadProgressUpdate();

	ShipsInit();
	ReloadProgressUpdate();

	IslandsInit();
	ReloadProgressUpdate();

	WeatherInit();
	ReloadProgressUpdate();

	InitPerks();
	ReloadProgressUpdate();

	// Init network, clear massives and load favorite list
	ReloadProgressUpdate();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	SetEventHandler("Control Activation","proc_break_video",0);
	InterfaceStates.Launched = false;
	SetEventHandler(EVENT_END_VIDEO,"Main_LogoVideo",0);
	InterfaceStates.videoIdx = 1;
	Event(EVENT_END_VIDEO);
	ReloadProgressEnd();

	SetGlowParams(1.0, 50, 2);
}

void Main_InitGame()
{
    //LayerCreate(REALIZE, 1);
	//LayerCreate(SEA_REALIZE, 1);
	//LayerCreate("net_realize", 1);
	//LayerCreate(INTERFACE_REALIZE, 1);
	//LayerCreate("fader_realize", 1);
	//LayerCreate("inf_realize", 1);

	nTeleportLocation      = 1;
    bDisableLandEncounters = false;
	bDisableCharacterMenu  = false;
	bWorldAlivePause       = true;
	bPauseContrabandMetro  = false;
	bMonstersGen           = false;
	bLandEncountersGen     = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	bDisableMapEnter           = false;
	bDisableSailTo             = false;
	bEnableIslandSailTo        = false;
	bReloadCanBe               = false;
	bMapEnter                  = false;
	bQuestDisableMapEnter      = false;
    bAbordageStarted           = false;
    bCabinStarted              = false;
	bDeckBoatStarted           = false;
	LAi_IsCapturedLocation     = false;
	LAi_IsBoarding             = false;
	LAi_restoreStates          = false;
	LAi_boarding_process       = false;
	boarding_location          = -1;

	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();
	// Init network, clear massives and load favorite list
	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
}
void Main_LogoVideo()
{
	int i = sti(InterfaceStates.videoIdx);
	switch(i)
	{
	case 1:
		InterfaceStates.videoIdx = 4;
		StartPostVideo("Title",1);
	break;

	default:
		DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
		DeleteClass(&aviVideoObj);
		Event("DoInfoShower","sl","game prepare",true);
		SetEventHandler("frame","Main_Start",1);
	break;
	}

}

void Main_Start()
{
	ReloadProgressStart();

	DelEventHandler("Control Activation","proc_break_video");
	DelEventHandler("frame","Main_Start");

	if( GetTargetPlatform()=="pc" )	ControlsInit(GetTargetPlatform(),false, 0);

	ReloadProgressUpdate();
	InitGame();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;


	InterfaceStates.Buttons.Load.enable = true;

	Event("DoInfoShower","sl","game prepare",false);

	StartLanguageSetting(LanguageGetLanguage());
 	LoadPlayerProfileDefault(); // boal
	LaunchMainMenu();
	//LaunchNetTopListScreen();

	CharacterIsDead(GetMainCharacter());

	ReloadProgressEnd();
}

void SaveGame()
{
	string saveName = GetEventData();
	string saveData = GetEventData();
	DelEventHandler("evntSave","SaveGame");

	aref arTmp;
	if( !GetEntity(arTmp,"fader") )
	{
		//implement interface
		//LaunchQuickSaveMenu();
		pchar.version_number = 104;
		SaveEngineState(saveName);
		ISetSaveData(saveName,saveData);
	}

	//hide interface
	PostEvent("DoInfoShower",1,"sl","save game",false);
	DeleteEntitiesByType("scrshoter");
	HideQuickSaveMenu();
}

void LoadGame()
{
    PauseParticles(true); //fix вылета у форта
    // не помогло DeleteFortEnvironment();  //fix

	PauseAllSounds(); // boal fix
    ResetSound();  // fix
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	string saveName = GetEventData();
	DelEventHandler("evntLoad","LoadGame");

	string retStr="";
	SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&retStr);
	if( retStr=="" ) {return;}

	DeleteEntities();
	ClearEvents();
	ClearPostEvents();
	SetTimeScale(1.0);
	TimeScaleCounter = 0;

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls",FADER_PICTURE0, "loading\jonny_load\load\load_03.tga");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	ReloadProgressStart();
	pchar.savegamename = saveName;
	SetEventHandler("frame","LoadGame_continue",1);
	iCalculateSaveLoadCount("Load");
}

void LoadGame_continue()
{
	DelEventHandler("frame","LoadGame_continue");
	FreezeGroupControls(curKeyGroupName,true);
	LoadEngineState(pchar.savegamename);
}

void InterfaceDoExit()
{
	DelEventHandler("frame","InterfaceDoExit");
	InterfaceStates.Launched=false;
	if(sti(InterfaceStates.doUnFreeze)==true)
	{
		SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
		if(!IsEntity(&aviVideoObj))
		{
			if( bSeaActive && !bAbordageStarted )
			{
				LayerFreeze(SEA_REALIZE,false);
				LayerFreeze(SEA_EXECUTE,false);
			}
			else
			{
				LayerFreeze(REALIZE,false);
				LayerFreeze(EXECUTE,false);
			}
		}
		DeleteAttribute(&GameInterface,"");
	}
	switch(interfaceResultCommand)
	{
		case RC_INTERFACE_FORTCAPTURE_EXIT:
			ReloadAfterFortCapture();
			break;

		case RC_INTERFACE_DO_NOTHING:
			break;
		case RC_INTERFACE_MAIN_MENU_EXIT:
			break;
		case RC_INTERFACE_DO_NEW_GAME:
			InterfaceStates.doUnFreeze = false;
			DeleteEntities();
			ResetSound();  // fix
			ClearEvents();
			ClearPostEvents();

            if (CheckAttribute(pchar, "HeroParam")) // признак, что есть герой
            {
				trace("Main_InitGame");
				Main_InitGame(); // boal вынес все в одинметод, новая игра из страой глючит
			}
			else
			{
				if(LoadSegment("Interface\BaseInterface.c"))
				{
					InitBaseInterfaces_main();
					InitBaseInterfaces();
					UnloadSegment("Interface\BaseInterface.c");
				}
			}
			DeleteEntities();
			ClearEvents();
			SetEventHandler("frame","NewGame",1);
			InterfaceStates.doUnFreeze = false;
		break;
		case RC_INTERFACE_DO_LOAD_GAME:
			if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
			{
				LaunchLoadGame(false);
			}
			else
			{
				LaunchLoadGame(true);
			}
			break;
		case RC_INTERFACE_DO_SAVE_GAME:
			LaunchSaveGame();
			break;
		case RC_INTERFACE_DO_OPTIONS:
			LaunchOptionScreen();
			break;

		case RC_INTERFACE_LOCKPICK: //New Abilities - взлом сундука
			LaunchLockPicking();
		break;

		case RC_INTERFACE_DO_CREDITS:
		    LaunchAboutScreen();
		break;
		case RC_INTERFACE_DO_RESUME_GAME:
		break;
		case RC_INTERFACE_RANSACK_MAIN_EXIT:
			Return2SeaAfterAbordage();
			break;
		case RC_INTERFACE_CHARACTER_SELECT_EXIT:
			DoQuestFunctionDelay("WayBeginning", 1.0);
		break;
		case RC_INTERFACE_SPEAK_EXIT_AND_CAPTURE:
			string sTargetChr = pchar.speakchr;
			pchar.abordage = 1;
			Sea_AbordageStartNow(SHIP_ABORDAGE, GetCharacterIndex(sTargetChr), true, true);
			SetTimeScale(1.0);
			TimeScaleCounter = 0;
			DelPerkFromActiveList("TimeSpeed"); //boal
			pchar.speakchr = 0;
			pchar.whospeak = 0;
		break;
		case RC_INTERFACE_SPEAK_EXIT_AND_TRADE:
			LaunchStore(SHIP_STORE);
		break;
		case RC_INTERFACE_TO_CHAR:
			pchar = GetMainCharacter();
			LaunchCharacter(pchar);
		break;
		case RC_INTERFACE_TO_SHIP:
			LaunchShipState();
		break;
		case RC_INTERFACE_TO_LOGBOOK:
			LaunchQuestBook();
		break;
		case RC_INTERFACE_TO_ITEMS:
			LaunchItems(); // to_do
		break;
		case RC_INTERFACE_LAUNCH_GAMEMENU:
			LaunchGameMenuScreen();
			break;
		// boal -->
  		case RC_INTERFACE_DO_BOAL_BETA:
		     LaunchBoalBetaScreen();
        break;
		// boal <--

		// Warship -->
		case RC_INTERFACE_BEST_MAP:
			LaunchBestMapScreen(); // Смотрим отличную карту
			break;
		// <-- Warship

		case RC_INTERFACE_MAPVIEW:
			LaunchMapViewScreen(); // Смотрим атлас карт
			break;
		case RC_INTERFACE_POINTS_EX:
			LaunchPointsEX();
			break;
		// Крафт
		case RC_INTERFACE_CRAFT_ALL:
			LaunchCraftAll();
		break;
	}
}
void EngineLayersOffOn(bool on)
{
	on = !on;
	if( on ) {
		LayerFreeze(REALIZE,on);
		LayerFreeze(EXECUTE,on);
		LayerFreeze(SEA_REALIZE,on);
		LayerFreeze(SEA_EXECUTE,on);
	} else {
		if(bSeaActive && !bAbordageStarted) {
			LayerFreeze(SEA_REALIZE,on);
			LayerFreeze(SEA_EXECUTE,on);
		} else {
			LayerFreeze(REALIZE,on);
			LayerFreeze(EXECUTE,on);
		}
	}
}

string seadogs_saveFrom = "";

void OnSave()
{
	seadogs_saveFrom = "";
	if(IsEntity(&worldMap) != 0)
	{
		seadogs_saveFrom = "world map";
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			Sea_Save();
			seadogs_saveFrom = "sea";
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				seadogs_saveFrom = "location";
				SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
				LAi_SaveInfo();
				PostEvent("SeaDogs_ClearSaveData", 400, "a", &Locations[ldLoc]);
			}
			else
			{
				Trace("OnSave() -> unknown character location");
			}
		}
	}
	iCalculateSaveLoadCount("Save");
}

//#20180226-01
bool CanSave()
{
    bool bReturn = false;
    if(IsEntity(&worldMap) != 0)
	{
		bReturn = true;
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			bReturn = true;
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				bReturn = true;
			}
		}
	}
	return bReturn;
}

void ClearLocationsSaveData()
{
	aref loc = GetEventData();
	SendMessage(loc, "l", MSG_LOCATION_CLRCHRPOSITIONS);
}

int actLoadFlag = 0;

void OnLoad()
{
	actLoadFlag = 1;

	if(screenscaling < 50) screenscaling = BI_COMPARE_HEIGHT;

	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");

	//Boyer add
	//onLoadReInit();
	SpecOfficersCirass();
	//Boyer change #20170418-01
	//restoreQuestItems(); не нужно в отсутствие реинитов - Gregg
	//End Boyer add
	DeleteAttribute( pchar, "abordage_active_count" );
	FreezeGroupControls(curKeyGroupName,false);

	if( CharacterIsDead(pchar) ) {
		pchar.chr_ai.hp = 1.0;
	}

	Nation_InitAfterLoading();
	ResetSound();

	//CreateClass("dummy");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		//InitBaseInterfaces_main();
		InitBaseInterfaces();
		InitInterfaceTables();
		UnloadSegment("Interface\BaseInterface.c");
	}

	ReloadProgressUpdate();

	DialogsInit();
	//IslandsInit();
	//LocationInit();

	ReloadProgressUpdate();

	//Boyer add to fix missing ship init
	ShipsInit();

	InitCharacterEvents();
	ReloadProgressUpdate();

	QuestsInit();
	ReloadProgressUpdate();

	InitTeleport();
	ReloadProgressUpdate();

	InitParticles();
	ReloadProgressUpdate();
	//ImportFuncTest();

	WeatherInit();
	ReloadProgressUpdate();

	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	//#20190327-01
	if(!CheckAttribute(pchar, "camEye"))
        pchar.camEye = 0;

	SM_PusherOnLoad();

	if(seadogs_saveFrom == "location")
	{
		ref mainchar;
		mainchar = GetMainCharacter();
		// boal: лажа это!!  есть actLoadFlag  //mainchar.isload = 1;
		LoadMainCharacterInFirstLocation(mainchar.location,"", mainchar.location.from_sea);
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0)
		{
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_TLPCHRPOSITIONS);
		}
	}
	else
	{
		if (seadogs_saveFrom == "sea")
		{
			Sea_Load();
 		}
		else
		{
			if(seadogs_saveFrom == "world map")
			{
				wdmLoadSavedMap();
			}
			else
			{
				Trace("Unknown seadogs_saveFrom == " + seadogs_saveFrom);
			}
		}
	}

	//ReloadEndFade();
	EngineLayersOffOn(true);
	//NewGame();
	DialogRun = false;
	InterfaceStates.Launched = false;

	ReloadProgressUpdate();

	PerkLoad();

	ReloadProgressUpdate();

	LoadGameOptions();

	ReloadProgressEnd();
    //#20200519-02
    BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
    BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	if( CheckAttribute(&InterfaceStates,"WorldSituationUpdateStep") &&
		sti(InterfaceStates.WorldSituationUpdateStep) < 10 )
	{
		Event("EvSituationsUpdate", "l", sti(InterfaceStates.WorldSituationUpdateStep));
	}

	actLoadFlag = 0;
	////
	ProcessVersionCheck();
	//#20181015-02
	if(bSeaActive && !bMapEnter)
        Sound_OnSeaAlarm555(seaAlarmed, true);

	iCalculateSaveLoadCount("Load");
}

void NewGame()
{
	DeleteEntities();
	DelEventHandler("frame","NewGame");

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls",FADER_PICTURE0, "loading\jonny_load\load\load_03.tga");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");

	SetEventHandler("frame","NewGame_continue",1);
}

void NewGame_continue()
{
	DeleteAttribute( pchar, "abordage_active_count" );  // это тут не рабоатет :)  Но и не мешает Boal

	ReloadProgressStart();

	DelEventHandler("frame","NewGame_continue");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InitGame();

	ReloadProgressUpdate();

	CreateColonyCommanders();

	ReloadProgressUpdate();

	SetNames();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0; //boal
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.WorldSituationUpdateStep = 100;
	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	pchar = GetMainCharacter(); //fix
	//#20190327-01
    pchar.camEye = 0;
	setNewMainCharacter(pchar, 1);
	ReloadProgressUpdate();

    RumourInit();  //homo 23/06/06
	ReloadProgressUpdate();

	ActivateTimeEvents();

	ReloadProgressUpdate();

	SetDamnedDestinyVariable();
	ReloadProgressUpdate();

	pchar.questTemp.sbormoney = -1;

	//LoadMainCharacterInFirstLocation(sTeleportLocName, sTeleportLocator, sTeleportLocName);
	startGameWeather = true;
	//if (startHeroType > 6)
	//{//Стандартное начало
		InterfaceStates.startGameWeather = FindWeather("11 Hour");
		LoadMainCharacterInFirstLocationGroup("SelectMainCharacter_Cabine", "reload", "reload1");
		pchar.quest.SelectMainCharacterInCabine.win_condition.l1          = "location";
		pchar.quest.SelectMainCharacterInCabine.win_condition.l1.location = "SelectMainCharacter_Cabine";
		pchar.quest.SelectMainCharacterInCabine.function                  = "SelectMainCharacterInCabine";
	ReloadProgressUpdate();

	//InitTowns();
	UpdateCrewInColonies(); // пересчет наемников в городах
	ReloadProgressUpdate();

	//SetQuestForMenInTavernWhoGiveUsInfo(); // to_do
    //#20190909-01
    pchar.fix20190909 = true;
	ReloadProgressUpdate();
	ReloadProgressEnd();
}

void InitGame()
{
	//LayerCreate(REALIZE, 1);
	//LayerCreate(SEA_REALIZE, 1);
	//LayerCreate(INTERFACE_REALIZE, 1);
	//LayerCreate("fader_realize", 1);
	//LayerCreate("inf_realize", 1);

	InitSound();

	ReloadProgressUpdate();

	DeleteSeaEnvironment();
	//CharactersInit();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}
    InitPerks();
    ReloadProgressUpdate();

	IslandsInit();
	ReloadProgressUpdate();

	LocationInit();
	ReloadProgressUpdate();

	DialogsInit();
	ReloadProgressUpdate();

	InitTeleport();
	ReloadProgressUpdate();

	InitParticles();
	ReloadProgressUpdate();

    if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}
	ReloadProgressUpdate();
	//Boyer change #20170301-6...CharactersInit assigns RealShips, and after a bunch of 'New' games in a
	//session, RealShips array overflows, so call new function to reset
	ResetRealShipArray();
	ReloadProgressUpdate();

	CharactersInit();
	ReloadProgressUpdate();

	ColoniesInit();
	ReloadProgressUpdate();

	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}

	QuestsInit();
	ReloadProgressUpdate();


	SeaAIGroupsInit();
	ReloadProgressUpdate();

	InitQuestMapEncounters();
	ReloadProgressUpdate();

	ResetQuestMovie();
	ReloadProgressUpdate();

	LoadGameOptions();

	ReloadProgressUpdate();
	InfoShowSetting();

}

int counter = 0;
void ProcessControls()
{
	string ControlName;
	ControlName = GetEventData();
	// boal -->
 	aref  arItm;
    int   itmIdx;
	String itemID;
	bool bOk, bOk1;

    if (ControlName == "QuickSave") { MakeQuickSave(); return; }
    if (ControlName == "QuickLoad") { MakeQuickLoad(); return; }

    if (dialogRun) return;
	if (ControlName == "SaveDelete" && CurrentInterface == INTERFACE_SAVELOAD)
	{
		if (XI_IsWindowEnable("PROFILE_WINDOW")){DoConfirm(1); return;}
		else {DoConfirm(2); return;}
	}
	if (sti(InterfaceStates.Launched)==true) return;

	if (ControlName == "WhrPrevWeather")	{ Whr_LoadNextWeather(-1); return; }
	if (ControlName == "WhrNextWeather")	{ Whr_LoadNextWeather(1); return; }
	if (ControlName == "WhrUpdateWeather")	{ Whr_UpdateWeather(); return; }

	//if (ControlName == "Help") RunHelpChooser();

	if(bSeaActive && !bAbordageStarted)
	{
		switch(ControlName)
		{
		    case "Ship_Fire": Ship_DoFire(); return; break;
		    case "Interface": ProcessInterfaceKey(); return; break;
			case "MainMenu": ProcessMainMenuKey();	return; break;
			case "MainMenuDouble": ProcessMainMenuKey(); return; break;
			case "Sea_CameraSwitch": SeaCameras_Switch(); return; break;
			case "Ship_Fire": Ship_DoFire(); break;
			case "Tele": Sea_ReloadStart(); return; break;
			 //// {*} BUHO-CIC - ADDED CODE - Key event response.
            //#20180226-02
            case "CIC_LoadBalls" :
                Log_SetStringToLog("Эскадра, зарядить ядра!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadGrapes" :
                Log_SetStringToLog("Эскадра, зарядить картечь!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadChain" :
                Log_SetStringToLog("Эскадра, зарядить книпели!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadBombs" :
                Log_SetStringToLog("Эскадра, зарядить бомбы!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadAtWill" :
                Log_SetStringToLog("Эскадра, зарядка по усмотрению!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\SignalCompanion.wav");
                return;
            break;
            case "CIC_SailAway" :
                Log_SetStringToLog("Эскадра, уплыть!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\SignalCompanion.wav");
                return;
            break;
            case "CIC_LowerSails" :
                Log_SetStringToLog("Эскадра, спустить паруса!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\_strike_down.wav");
                return;
            break;
            case "CIC_ProtFlagship" :
                Log_SetStringToLog("Эскадра, защищать флагман!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\SignalCompanion.wav");
                return;
            break;
            //// {*} BUHO END ADDITION
		}
	}
	else
	{
		switch(ControlName)
		{
			case "ChrBlock":
			if (findsubstr(pchar.model.animation, "mushketer" , 0) != -1)
			{
				if (stf(pchar.chr_ai.charge) != 1.0)
				{
					pchar.chr_ai.charge = stf(pchar.chr_ai.charge) + 0.01;
				}
			}
			break;
/*		    // boal -->
            case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
                if (bLandInterfaceStart && LAi_IsFightMode(pchar))
                {
                    pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
                    if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
                }
            return;
            break;
            case "ChrStrafeLeft":
                if (bLandInterfaceStart && LAi_IsFightMode(pchar))
                {
                    pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
                    if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
                }
            return;
            break;
            case "ChrStrafeRight":
                if (bLandInterfaceStart && LAi_IsFightMode(pchar))
                {
                    pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
                    if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
                }	
            return;
            break; */
            case "BOAL_UsePotion": // boal KEY_X
                if (bLandInterfaceStart)
				{
					bool bEnablePotion1 = true;
					if(CheckAttribute(PChar, "AcademyLand"))
					{
						if(PChar.AcademyLand == "Start")
						{
							bEnablePotion1 = sti(PChar.AcademyLand.Temp.EnablePotion);
						}
					}

					if(!bEnablePotion1)
					{
						Log_SetStringToLog("В данный момент запрещено использовать эликсиры.");
					}
					else
					{
						/*itmIdx = FindPotionFromChr(pchar, &arItm, 0);
						while(itmIdx>=0)
						{
						  if( EnablePotionUsing(pchar, arItm) )
						  {
							 DoCharacterUsedItem(pchar, arItm.id);
							 int idLngFile = LanguageOpenFile("save_load.txt");
							 Log_SetStringToLog(LanguageConvertString(idLngFile, "Potion"));
							 break;
						  }
						  itmIdx = FindPotionFromChr(pchar, &arItm, itmIdx+1);
						}*/
						if(LAi_IsPoison(pchar))
						{
							if (UseBestPotion(pchar, true) == 0)
							{
								if (UseBestPotion(pchar, false) == 0)
								{
									Log_SetStringToLog("Не найдено никаких лечебных средств.");
								}
							}
						}
						else
						{
							if (UseBestPotion(pchar, false) == 0)
							{
								if (UseBestPotion(pchar, true) == 0)
								{
									Log_SetStringToLog("Не найдено никаких лечебных средств.");
								}
							}
						}
					}
				}
            return;
            break;
			case "csmRunLootCollector":
				csmLootCollector();
			break;
            case "BOAL_ActivateRush":  // boal KEY_F
				if (bLandInterfaceStart)
				{
					if (GetCharacterPerkUsing(pchar, "Rush") && LAi_IsFightMode(pchar) && PChar.location != "FencingTown_Arena" && PChar.location != "FencingTown_ExitTown")
					{
						ActivateCharacterPerk(pchar, "Rush");
						PlayVoice(GetSexPhrase("interface\Bers_"+rand(5)+".wav","interface\Bersf_"+rand(4)+".wav"));
						pchar.chr_ai.energy    = pchar.chr_ai.energyMax;
					}
					else
                    {
                        PlaySound("knock");
                    }
                }
				return;
            break;

			case "AltModificatorOff":
				if (!IsEntity(&ILogAndActions)) return;
				if(loadedLocation.type == "Underwater") return;
				bAltInfo = false;
				ModifyTextInfo();
			break;

			case "AltModificator":
				if (!IsEntity(&ILogAndActions)) return;
				if(loadedLocation.type == "Underwater") return;
				bAltInfo = true;
				SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
				ModifyTextInfo();
			break;

			case "Fast_port":
				if(bAltInfo)  HKT_Button(ControlName);
			break;

			case "Fast_store":
				if(bAltInfo) HKT_Button(ControlName);

			break;

			case "Fast_Shipyard":
				 if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_tavern":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_townhall":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_bank":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_church":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_Brothel":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_PortOffice":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_prison":
				if(bAltInfo) HKT_Button(ControlName);
			break;

            case "OfficersCharge":
                pchar.OfficerAttRange = 35.0;
                OfficersFollow();
                Log_SetStringToLog("Офицеры, в атаку!");
                return;
            break;
            case "OfficersFree":
                pchar.OfficerAttRange = 35.0;
                OfficersFree();
                Log_SetStringToLog("Офицеры, вольно!");
                return;
            break;
            case "OfficersFollow":
                pchar.OfficerAttRange = 7.0;
                OfficersFollow();
                Log_SetStringToLog("Офицеры, за мной!");
                return;
            break;
            case "OfficersHold":
                pchar.OfficerAttRange = 7.0;
                OfficersHold();
                Log_SetStringToLog("Офицеры, стоять!");
                return;
            break;
			case "MainMenu": ProcessMainMenuKey();	return; break;
			case "MainMenuDouble": ProcessMainMenuKey(); return; break;
			case "Interface": ProcessInterfaceKey();return; break;
			case "Tele":
				StartQuickTeleport();
			return;
            break;
			case "TeleBack": Teleport(-1); return; break;
			case "Action":
			return;
            break;
		}
	}

    // boal 27.11.03 time -->
  	if (ControlName=="TimeScaleFaster" || ControlName == "TimeScaleSlower" ||
		ControlName=="TimeScaleFasterBA" || ControlName=="TimeScaleSlowerBA")
  	{
        //Boyer change #20170318-38
        // if (CheckAttribute(&loadedLocation, "type") && loadedLocation.type == "underwater") return; //запрет ускорения под водой.
		//if (bAltBalance && !bSeaActive && ControlName == "TimeScaleSlower" && TimeScaleCounter == 0)
		if (bAltBalance && TimeScaleCounter == 0)
		{
			if (ControlName == "TimeScaleSlower" || ControlName == "TimeScaleSlowerBA")
			{
				Log_SetStringToLog("Замедление времени заблокировано.");
				return;
			}

		}
		if (PChar.location == "FencingTown_Arena" || PChar.location == "FencingTown_ExitTown")
		{
			if (InterfaceStates.Buttons.Save.enable == false)
			{
				Log_SetStringToLog("В данный момент запрещены манипуляции временным потоком.");
				return;
			}
		}

		DeleteAttribute(pchar, "pause");
		if (ControlName == "TimeScaleFaster" || ControlName == "TimeScaleFasterBA")
     	{
			if (TimeScaleCounter >= 12)
			{
			    TimeScaleCounter += 4;
			}
			else
			{
                if (TimeScaleCounter >= 4)
				{
				    TimeScaleCounter += 2;
				}
				else
				{
					TimeScaleCounter++;
				}
			}
		}
     	else
     	{
            if (TimeScaleCounter >= 16)
			{
			    TimeScaleCounter -= 4;
			}
			else
			{
                if (TimeScaleCounter >= 6)
				{
				    TimeScaleCounter -= 2;
				}
				else
				{
					TimeScaleCounter--;
				}
			}
		}
		if (true) // MOD_SKILL_ENEMY_RATE > 1) // запрет 0.25 скорости
        {
		   if (!bBettaTestMode && TimeScaleCounter < -2) TimeScaleCounter = -2;
		}
        if (bDisableMapEnter)
        {
            if (TimeScaleCounter > 28) TimeScaleCounter = 28;
        }
        else
        {   // без боя
            if (bSeaActive && !bAbordageStarted )
            {
            	if (TimeScaleCounter > 28) TimeScaleCounter = 28; // море
            }
            else
            {
            	if (TimeScaleCounter > 28) TimeScaleCounter = 28; // суша
            }
        }
        if (IsEntity(worldMap))
        {
            if (TimeScaleCounter > 28) TimeScaleCounter = 28;
        }
     	float newTimeScale = 1 + (TimeScaleCounter)*0.25; // GetSeaTimeScale()
     	if (newTimeScale < 0) //don't wanna crash the game
     	{
        		TimeScaleCounter = -4;
        		newTimeScale = 0;
     	}

     	Log_SetStringToLog("x" + newTimeScale);
     	if (TimeScaleCounter == 0) //back to normal
     	{
			if(IsPerkIntoList("TimeSpeed"))
        	{
        		SetTimeScale(1.0);
        		DelPerkFromActiveList("TimeSpeed");
        	}
     	}
     	else
     	{
        	SetTimeScale(newTimeScale);
        	//if perk not in list
        	if(!IsPerkIntoList("TimeSpeed"))
        	{
				AddPerkToActiveList("TimeSpeed");
			}
     	}
        return;
	}
	// boal <--
	switch(ControlName)
	{
        case "TimeScale":
            DeleteAttribute(pchar, "pause");
            //Boyer change #20170318-38
            /* if (CheckAttribute(&loadedLocation, "type") && loadedLocation.type == "Underwater") {
				return; //запрет ускорения под водой.
			} */
			if (PChar.location == "FencingTown_Arena" || PChar.location == "FencingTown_ExitTown")
			{
				if (InterfaceStates.Buttons.Save.enable == false)
				{
					Log_SetStringToLog("В данный момент запрещены манипуляции временным потоком.");
					return;
				}
			}
			if(IsPerkIntoList("TimeSpeed"))
			{
				SetTimeScale(1.0);
				TimeScaleCounter = 0;
                Log_SetStringToLog("Time x1");
				DelPerkFromActiveList("TimeSpeed");
			}
			else
			{
				SetTimeScale(GetSeaTimeScale());
				TimeScaleCounter = 4;
                Log_SetStringToLog("Time x2");
				AddPerkToActiveList("TimeSpeed");
			}
		break;

		case "VK_PAUSETimePause":
			if (PChar.location == "FencingTown_Arena" && PChar.location == "FencingTown_ExitTown")
			{
				if (InterfaceStates.Buttons.Save.enable == false)
				{
					Log_SetStringToLog("В данный момент запрещены манипуляции временным потоком.");
					return;
				}
			}
			if (!CheckAttribute(pchar, "pause"))
			{
				pchar.pause = true;
				SetTimeScale(0.0);
			    TimeScaleCounter = -3;
			    AddPerkToActiveList("TimeSpeed");
			}
			else
			{
                DeleteAttribute(pchar, "pause");
				SetTimeScale(1.0);
				DelPerkFromActiveList("TimeSpeed");
				TimeScaleCounter = 0;
			}
		break;
		case "WMapCancel":
			if(IsEntity(&worldMap))
			{
				pchar.space_press = 1;
				DeleteAttribute(pchar, "SkipEshipIndex");// boal
			}
		break;

		case "MushketHotkey":
			if (!CheckAttribute(pchar,"mushket")) break;
			if (!CheckCharacterItem(pchar, pchar.mushket)) break;
			if(LAi_CheckFightMode(pchar))
			{
				if (!CheckAttribute(pchar,"mushket.timer")) pchar.mushket.timer = false;
				if (pchar.mushket.timer) break;
				pchar.mushket.timer = true;
				LAi_SetFightMode(pchar, false);
				LAi_SetActorType(pchar);
				if(pchar.model.animation == "man_fast" || pchar.model.animation == "YokoDias_fast" || pchar.model.animation == "Milenace_fast")
				{
					PostEvent("Event_SwapWeapon", 1400);
					DoQuestFunctionDelay("ReloadMyGun", 1.5);
				}
				if(pchar.model.animation == "man" || pchar.model.animation == "YokoDias" || pchar.model.animation == "Milenace")
				{
					PostEvent("Event_SwapWeapon", 1800);
					DoQuestFunctionDelay("ReloadMyGun", 1.9);
				}
				if(findsubstr(pchar.model.animation, "mushketer" , 0) != -1)
				{
					PostEvent("Event_SwapWeapon3", 800);
					DoQuestFunctionDelay("ReloadMyGun", 0.9);
				}
			}
		break;

		case "PusherHotkey":
			if (!CheckCharacterPerk(pchar, "Buldozer")) break;

			if (!CheckAttribute(pchar,"CSM.CrowdPusher"))
			{
				Log_Info("''Громила'' активирован.");
				SM_PusherEnable();
			}
			else
			{
				Log_Info("''Громила'' деактивирован.");
				SM_PusherDisable();
			}
		break;

		case "Map_Best":
			// if (bBettaTestMode) LaunchPaperMapScreen();
			if(CheckCharacterItem(PChar, "Map_Best") || bBettaTestMode) LaunchBestMapScreen();
		break;

		// --> ugeen
		case "MapView":
			bOk = bSeaActive && !bAbordageStarted;
			bOk1 = bLandInterfaceStart && !LAi_IsFightMode(pchar);
			if(bOk || bOk1)
			{ // изврат - но по другому никак :(
				if(CheckCharacterItem(PChar, "MapsAtlas") && pchar.MapsAtlasCount > 0) LaunchMapViewScreen();
			}
		break;
		// <-- ugeen
	/*	// boal -->
		case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;

		case "ChrStrafeLeft":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;

		case "ChrStrafeRight":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
*/
		case "BOAL_UsePotion": // boal KEY_C
            if (bLandInterfaceStart)
            {
				bool bEnablePotion = true;
				if(CheckAttribute(PChar, "AcademyLand"))
				{
					if(PChar.AcademyLand == "Start")
					{
						bEnablePotion = sti(PChar.AcademyLand.Temp.EnablePotion);
					}
				}

				if(!bEnablePotion)
				{
					Log_SetStringToLog("В данный момент запрещено использовать эликсиры.");
				}
				else
				{
					if(LAi_IsPoison(pchar))
					{
						if (UseBestPotion(pchar, true) == 0)
						{
							if (UseBestPotion(pchar, false) == 0)
							{
								Log_SetStringToLog("No Potion Found!");
							}
						}
					}
					else
					{
						if (UseBestPotion(pchar, false) == 0)
						{
							if (UseBestPotion(pchar, true) == 0)
							{
								Log_SetStringToLog("No Potion Found!");
							}
						}
					}
				}
	        }
		break;

		// Warship 13.06.09 Выпить противоядие KEY_V
		case "UseAntidote":
			if(bLandInterfaceStart)
            {
				if(FindCharacterAntidote(PChar, &itemID)) // В itemID запишется ID предмета, который можно использовать
				{
					DoCharacterUsedItem(PChar, itemID);
					Log_Info("Use antidote");
				}
			}
		break;
		case "PaperMap":
			LaunchPaperMapScreen();
		break;

        case "BOAL_ActivateRush":  // boal KEY_F
			if (bLandInterfaceStart)
            {
				if (GetCharacterPerkUsing(pchar, "Rush") && LAi_IsFightMode(pchar))
				{
					ActivateCharacterPerk(pchar, "Rush");
					PlayVoice(GetSexPhrase("interface\Bers_"+rand(5)+".wav","interface\Bersf_"+rand(4)+".wav"));
					pchar.chr_ai.energy    = pchar.chr_ai.energyMax;
				}
				else
                {
                    PlaySound("interface\knock.wav");
                }
            }
	    break;

//JA 16/8/09 -->
		case "BOAL_ActivateTurn180":
		if (!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar, "Turn180"))
		{
			ActivateCharacterPerk(pchar,"Turn180");
			Ship_Turn180(pchar);
		}
		else
		{
			Log_Info("Навык не доступен!");
			PlaySound("interface\knock.wav");
		}
		break;

		case "BOAL_ActivateImmediateReload":
		if(bSeaActive == true)
		{
			if (!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar, "ImmediateReload"))
			{
				ActivateCharacterPerk(pchar,"ImmediateReload");
			}
			else
			{
				Log_Info("Навык не доступен!");
				PlaySound("interface\knock.wav");
			}
		}
		break;

		case "BOAL_ActivateLightRepair":
		if(bSeaActive == true)
		{
			if (!CheckOfficersPerk(pchar, "LightRepair") && GetOfficersPerkUsing(pchar,"LightRepair"))
			{
				ActivateCharacterPerk(pchar,"LightRepair");
				ActivateSpecRepair(pchar,0);
			}
			else
			{
				Log_Info("Навык не доступен!");
				PlaySound("interface\knock.wav");
			}
		}
		break;

		case "BOAL_ActivateInstantRepair":
		if(bSeaActive == true)
		{
			if (CheckInstantRepairCondition (pchar))
			{
				ActivateCharacterPerk(pchar,"InstantRepair");
				ActivateSpecRepair(pchar,1);
			}
			else
			{
				Log_Info("Навык не доступен!");
				PlaySound("interface\knock.wav");
			}
		}
		break;
	    case "BOAL_DeadSearch":  // boal KEY_1
			if (bLandInterfaceStart && !bAltInfo)
            {
                itmIdx = Dead_FindCloseBody();
			    if (itmIdx != -1)
			    {
					Dead_OpenBoxProcedure();
				}
				else
				{
                    Log_Info("Некого обыскивать");
				}
		    }
	    break;
//<--JA
		case "BOAL_SetCamera":
		    // по F10
		    //CameraHoldPos();
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF10Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
			else LaunchPsHeroScreen();
		break;
        case "BOAL_Control":
		    // по F11 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test")
		    {
		       LaunchDebuderMenu();
		    }
		break;
		case "BOAL_Control3":
		    // по F9 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On")
		    {
		       //LaunchBoalDebugScreenSecond();
		    }
		break;
		case "Person_Say": // KEY_T
			// Интерфейс отдыха
			/*if(bLandInterfaceStart) // В "Мыслях вслух"
				LaunchTavernWaitScreen();*/
		break;

		case "Say": // KEY_Y
			// Интерфейс автозакупки товаров
			if(bLandInterfaceStart && IsPCharHaveTreasurer()) // Если есть казначей и ГГ находится на суше
				LaunchTransferGoodsScreen();
		break;
        case "TeleportActive":
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF4Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
		break;
		case "BOAL_ControF5":
            if (MOD_BETTATESTMODE == "On")
            {
                if(LoadSegment("Debuger.c"))
                {
                    ActiveF5Control();
                    UnloadSegment("Debuger.c");
                }
                Statistic_AddValue(PChar, "Cheats.F5", 1);
            }
        break;
        case "BOAL_ControF7":
            // по F7 вызывает окно отладчика
            if (MOD_BETTATESTMODE == "On")
            {
                if(LoadSegment("Debuger.c"))
                {
                    ActiveF7Control();
                    UnloadSegment("Debuger.c");
                }
                Statistic_AddValue(PChar, "Cheats.F7", 1);
            }
        break;
        case "BOAL_Control2": // F12
            //Найти ближайшего видимого персонажа в заданном радиусе
            if(LoadSegment("Debuger.c"))
        	{
                ActiveF12Control(); // можно меять пряв в рабочей игре
        		UnloadSegment("Debuger.c");
        	}
        break;
        case "BOAL_ControlDebug": // VK_INSERT
            if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveINSERTControl();
            		UnloadSegment("Debuger.c");
            	}
        	}
        break;
		case "UseFood":
			if (bLandInterfaceStart)
			{
				bool bEnableFood = true;
				if(CheckAttribute(PChar, "AcademyLand"))
				{
					if(PChar.AcademyLand == "Start")
					{
						bEnableFood = sti(PChar.AcademyLand.Temp.EnableFood);
					}
				}

				if(!bEnableFood)
				{
					Log_SetStringToLog("В данный момент запрещено использовать еду.");
				}
				else
				{
					pchar.pressedFoodButton = true;
					EatSomeFood();
				}
			}
		break;
        // boal <--
		case "CreateNotice":
			LaunchCreateNotice();
		break;
		case "InterfaceDisabler":
			ChangeShowIntarface();
		break;
	}
}

void Teleport(int step)
{
	nTeleportLocation = nTeleportLocation + step;
	if(nTeleportLocation >=	nLocationsNum) nTeleportLocation = 1;
	if(nTeleportLocation <=	0) nTeleportLocation = nLocationsNum - 1;

	sTeleportLocName = Locations[nTeleportLocation].id;
	Trace("Teleport to '" + sTeleportLocName + "'");

    ReleaseSound(0);
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();
	SetEventHandler("frame","NewGame",1);
}

void ProcessMainMenuKey()
{
	if (interfacestates.buttons.resume.enable == "1")
	{
		//LaunchMainMenu();
		LaunchGameMenuScreen();
	}
}
// вызов меню по Ф2
void ProcessInterfaceKey()
{
	if( CharacterIsDead(GetMainCharacter()) ) {return;}
	if(bSeaActive && !bAbordageStarted)
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			{return;}
	}
	else
	{
		if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") != 0 )
			{return;}
		if( CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0 )
			{return;}
	}
	if (bDisableCharacterMenu) // boal
	{
		Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return;
	}
	if (bAbordageStarted && !bCabinStarted && !bDeckBoatStarted)
	{
		Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return;
	}
	LaunchSelectMenu();
}

void GameOverE()
{
	// вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	GameOver("sea");
	DeleteSeaEnvironment();
}

void GameOver(string sName)
{
	ref mc;
	int nSelect;
	string sFileName;
	//ResetSoundScheme();
	PauseAllSounds();
	ResetSound();
	EngineLayersOffOn(false);

	mc = GetMainCharacter();

	ClearEvents();
	ClearPostEvents();
	DeleteEntities();

	if(sti(InterfaceStates.Launched)) {
		UnloadSegment(Interfaces[CurrentInterface].SectionName);
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	InterfaceStates.showGameMenuOnExit = false;
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;

	InitSound();
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu_afterVideo",0);
	SetEventHandler("Control Activation","proc_break_video",0);
	FadeOutMusic(3);
	// PlayStereoOGG("music_ship_dead");
	switch(sName)
	{
		case "sea":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_sea_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_ship_dead");
		break;
		case "boarding":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_sea_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_ship_dead");
		break;
		case "land":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
		case "mutiny":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
		case "town":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
		case "blood":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
	}
}

string its(int iNumber)
{
	string sText = iNumber;
	return sText;
}

// тяжкая игра - сайв токо в церкви 17.03.05 boal
bool QuickSaveGameEnabledHardcore()
{
    bool TmpBool = false;
    ref mchref = GetMainCharacter();

	if (bHardcoreGame)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if( idxLoadLoc!=-1 )
	    {
	        if (CheckAttribute(&Locations[idxLoadLoc], "type"))
	        {
	            if (Locations[idxLoadLoc].type == "church" || Locations[idxLoadLoc].id == "GloriaChurch")
	            {
	                TmpBool = true;
	            }
	        }
	    }
    }
    else
    {
        TmpBool = true;
    }

    return TmpBool;
}

bool CheckBattleSeaSaveEnabled()
{
	string sSaveEnable = GetConvertStr("SeaBattleMode_SaveEnable", KVL_MODS_FILE);
	string sSmallRegStr = GetStrSmallRegister(sSaveEnable);
	if(sSmallRegStr == "on" || sSmallRegStr == "да")
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CheckSaveGameEnabled()
{
    bool TmpBool = true;
    ref mchref = GetMainCharacter();

    if (CheckAttribute(&InterfaceStates, "Buttons.Save.enable"))
	{
		if(InterfaceStates.Buttons.Save.enable != 1)
		{
			TmpBool = false;
		}
	}
	else
	{
		TmpBool = false;
	}

	if (bAbordageStarted) {TmpBool = false;}

	if(LAi_IsBoardingProcess()) {TmpBool = false;}

	if( CharacterIsDead(mchref) ) {TmpBool = false;}

	// LEO: Слишком жётско даже для хардкора. Если будет ваще пздц, выпилим нахер.
	/* if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) {TmpBool = false;}

	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled()) {TmpBool = false;}  */

	if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) TmpBool = false;

	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled()) TmpBool = false;

	// if (bAltBalance && LAi_group_IsActivePlayerAlarm()) TmpBool = false;
	if (TmpBool)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if (idxLoadLoc != -1 )
	    {
	        if (Locations[idxLoadLoc].id == "Ship_deck" || Locations[idxLoadLoc].id == "Deck_Near_Ship" ) // сайв на палубе глюкавый
	        {
	            TmpBool = false;
	        }
			if (CheckAttribute(Locations[idxLoadLoc],"fastreload"))
			{
				if (Pchar.questTemp.CapBloodLine == false)
				{
					string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
					if (sNation != "none" && sNation != "4")
					{
						int i = sti(sNation);
						bool bTmpBool = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
						if (HasSubStr(Locations[idxLoadLoc].id, "_Town") && bTmpBool) TmpBool = false;
					}
				}
			}
	    }

	}
    return TmpBool;
}

//Boyer change #20170418-01
void restoreQuestItems()
{
    ref		rItemRef;
    if(CheckAttribute(pchar, "restoreLSCKeymasterKey")){
        //From reaction_functions.c
        rItemRef =  ItemsFromID(pchar.restoreLSCKeymasterKey);
        rItemRef.shown = true;
        //From initItems.c
        rItemRef.startLocation = "Villemstad_houseSp5";
        rItemRef.startLocator = "item2";
    }
    if(CheckAttribute(pchar, "restoreLSCTrustLetter")){
        //From RelationAgent_dialog.c
        ChangeItemName(pchar.restoreLSCTrustLetter, "itmname_letter_LSC_1");
        ChangeItemDescribe(pchar.restoreLSCTrustLetter, "itmdescr_letter_LSC_1");
    }
	if(CheckAttribute(pchar, "HugtorpQuestStart") && !CheckAttribute(pchar, "HugtorpQuestFinish"))
	{
		ref itm = ItemsFromID("DOjeronRing");
		itm.picIndex = 15;
		itm.picTexture = "ITEMS_13";
		ChangeItemName("DOjeronRing", "itmname_HugtorpRing");
		ChangeItemDescribe("DOjeronRing", "itmdescr_HugtorpRing");
    }
}

//Boyer change #20170418-01
void removeQuestItemAttribute(string itemID)
{
    switch(itemID)
    {
        case "keyQuestLSC":
            if(CheckAttribute(pchar, "restoreLSCKeymasterKey"))
                DeleteAttribute(pchar, "restoreLSCKeymasterKey");
        break;
        case "letter_LSC":
            if(CheckAttribute(pchar, "restoreLSCTrustLetter"))
                DeleteAttribute(pchar, "restoreLSCTrustLetter");
        break;
    }
}

extern void SetCurrentProfile( string profileName );
//#20171009-03
void ResetDevice()
{
	if(InterfaceStates.Launched == true) {
        if(CurrentInterface == INTERFACE_SAVELOAD) {
            SetCurrentProfile( PlayerProfile.name );
        }
	}
	else {
        //Call twice to remove/replace
        ChangeShowIntarface();
        ChangeShowIntarface();
	}
}
int iCalculateSaveLoadCount(string _SaveLoad)
{
	int iCount;
	ref MChref = GetMainCharacter();
	string sAttrName = _SaveLoad + "Count";
	iCount = sti(MChref.SystemInfo.(sAttrName));
	iCount++;
	MChref.SystemInfo.(sAttrName) = iCount;
	return iCount;
}

void SpecOfficersCirass()
{
    if(CheckAttribute(pchar, "fix20210121")) return;

    pchar.fix20210121 = true;

    if(GetCharacterIndex("Daniel") != -1)
	{
    	sld = characterFromID("Daniel");
		// Прописка всех моделей для кирас. -->
    	sld.HeroModel = "PGG_YokoDias_0,PGG_YokoDias_1,PGG_YokoDias_2,PGG_YokoDias_3,PGG_YokoDias_4,PGG_YokoDias_5,PGG_YokoDias_6,PGG_YokoDias_7,PGG_YokoDias_8";
    	// Прописка всех моделей для кирас. <--
	}

	if(GetCharacterIndex("OffMushketer") != -1)
	{
    	sld = characterFromID("OffMushketer");
		// Прописка всех моделей для кирас. -->
        sld.HeroModel = "MusketeerEnglish_2,MusketeerEnglish_2_1,MusketeerEnglish_2_2,MusketeerEnglish_2_3,MusketeerEnglish_2_4,MusketeerEnglish_2_5,MusketeerEnglish_2,MusketeerEnglish_2,MusketeerEnglish_2";
	    // Прописка всех моделей для кирас. <--
	}

	if(GetCharacterIndex("OfMush1") != -1)
	{
    	sld = characterFromID("OfMush1");
        // Прописка всех моделей для кирас. -->
	    sld.HeroModel = "quest_mush_2,quest_mush_2_1,quest_mush_2_2,quest_mush_2_3,quest_mush_2_4,quest_mush_2_5,quest_mush_2,quest_mush_2,quest_mush_2";
	    // Прописка всех моделей для кирас. <--
	}

	if(GetCharacterIndex("OfMush2") != -1)
	{
    	sld = characterFromID("OfMush2");
	    // Прописка всех моделей для кирас. -->
	    sld.HeroModel = "quest_mush_1,quest_mush_1_1,quest_mush_1_2,quest_mush_1_3,quest_mush_1_4,quest_mush_1_5,quest_mush_1,quest_mush_1,quest_mush_1";
	    // Прописка всех моделей для кирас. <--
    }
	SetNewModelToChar(sld);
}
