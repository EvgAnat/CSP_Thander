
native string LanguageGetLanguage();
native int LanguageOpenFile(string sFileName);
native void LanguageCloseFile(int idLngFile);
native string LanguageConvertString(int userLngFileID, string inStr);
native void LanguageSetLanguage(string sLanguageName);
native string XI_ConvertString(string inStr);
native int GlobalLngFileID();
native string LanguageGetFaderPic(string faderPicName);
native string DialogAssembleStr(string idStr, string paramStr);
native string DialogAddParamToStr(string oldParamStr, string paramID, string paramValue);

//native int NFFindFiles(ref rObject, string sDirectory, string sMask, bool bRecursive);

native void XI_SetColorCorrection(float fContrast, float fGamma, float fBrightness);
native void XI_SetMouseSensitivity( float fMouseXSens, float fMouseYSens );
native void XI_ControlMakeInvert(string sControlName, int bInvertState);
native void XI_MakeNode(string sIniFileName, string sNodeType, string sNodeName, int nPriority);
native void XI_DeleteNode(string sNodeName);
native bool XI_IsWindowEnable(string sWindowName);
native void XI_WindowShow(string sWindowName, int bShowStatus);
native void XI_WindowDisable(string sWindowName, int bDisableStatus);
native void XI_WindowAddNode(string sWindowName, string sNodeName);
native bool XI_CreateFolder(string sFolderName);
native bool XI_CheckFolder(string sFolderName);
native bool XI_DeleteFolder(string sFolderName);
native bool XI_FindFolders(string sFindTemplate,aref arFoldersList);
native int XI_StoreNodeLocksWithOff();
native void XI_RestoreNodeLocks(int nStoreCode);
native bool XI_IsKeyPressed(string key_name); // key_name = {"shift","control","alt"}
native void XI_RegistryExitKey(string key_name);
native void XI_IsVirtualKeyPressed(string key_name);

#libriary "script_interface_functions"

void CreateImage(string AttrName,string imgListName,string imgName,int left,int top,int right,int bottom)
{
	GameInterface.pictures.(AttrName).tex = imgListName;
    GameInterface.pictures.(AttrName).pic = imgName;
    SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_PLACE_IMAGE,AttrName,true,left,top,right,bottom);
}

void CreateAbsoluteImage(string AttrName,string imgListName,string imgName,int left,int top,int right,int bottom)
{
	GameInterface.pictures.(AttrName).tex = imgListName;
    GameInterface.pictures.(AttrName).pic = imgName;
    SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_PLACE_IMAGE,AttrName,false,left,top,right,bottom);
}

void SetPictureBlind(string picName,bool blindFlag,int minCol,int maxCol)
{
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_SET_BLIND,picName,blindFlag,minCol,maxCol);
}

void CreateString(int enable,string strName, string strData, string fontName, int color, int x, int y, int alignment, float scale)
{
    GameInterface.strings.(strName) = strData;
    SendMessage(&GameInterface,"lssllllf",MSG_INTERFACE_CREATE_STRING, strName, fontName, color, x,y,alignment,scale);
    if(enable==FALSE)
    {
        SendMessage(&GameInterface,"ls", MSG_INTERFACE_DISABLE_STRING, strName);
    }
}

void DisableString(string strName)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_DISABLE_STRING, strName);
}

void EnableString(string strName)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_ENABLE_STRING, strName);
}

void ChangeStringColor(string strName, int newCol)
{
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_CHANGE_STR_COLOR,strName,newCol);
}

void SetNodeUsing(string nodeName,int bUsing)
{
    SendMessage(&GameInterface,"lsl", MSG_INTERFACE_SET_NODE_USING, nodeName, bUsing);
}

void SetCurrentNode(string nodeName)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_NEW_CURRENT_NODE,nodeName);
}
string GetCurrentNode()
{
	string retVal;
	SendMessage(&GameInterface,"le", MSG_INTERFACE_GET_CURRENT_NODE,&retVal);
	return retVal;
}

void ShowHelpString(string helpString)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_SETHELPSTRING, helpString);
}

string MakeMoneyShow(int moneyQuantity,string sign,string deliver)
{
	string moneyStr;
	int i,j;
	moneyStr="";
	while(moneyQuantity>999)
	{
		i = moneyQuantity/1000;
		j = moneyQuantity-i*1000;
		if(j>99)
		{
			moneyStr = deliver + j + moneyStr;
		}
		else
		{
			if(j>9)
			{
				moneyStr = deliver+"0" + j + moneyStr;
			}
			else
			{
				moneyStr = deliver+"00" + j + moneyStr;
			}
		}
		moneyQuantity = i;
	}
	moneyStr = sign+moneyQuantity+moneyStr;
	return moneyStr;
}

void SetNewPicture(string _NodeName,string _NewPictureFileName)
{
	SendMessage(&GameInterface,"lslls", MSG_INTERFACE_MSG_TO_NODE,_NodeName,2, false, _NewPictureFileName);
}

void SetNewGroupPicture(string sNodeName,string sGroup, string sName)
{
	SendMessage(&GameInterface,"lslss", MSG_INTERFACE_MSG_TO_NODE, sNodeName ,6, sGroup, sName);
}

void SetNewVideoPicture(string _NodeName,string _NewVideoPicFileName)
{
	SendMessage(&GameInterface,"lslls", MSG_INTERFACE_MSG_TO_NODE,_NodeName,2, true, _NewVideoPicFileName);
}

void SetSelectable(string _NodeName,int _Selectable)
{
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_SET_SELECTABLE, _NodeName, _Selectable);
}
int GetSelectable(string _NodeName)
{
	return SendMessage(&GameInterface,"ls", MSG_INTERFACE_GET_SELECTABLE, _NodeName);
}

void SetClickable(string _NodeName, bool ClickStatus)
{
	SendMessage(&GameInterface,"lslll", MSG_INTERFACE_MSG_TO_NODE,_NodeName,-1,1, ClickStatus);
}
bool GetClickable(string _NodeName)
{
	return SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE,_NodeName,-1,2);
}

void DelFromScroll(string nodeName,int pnum)
{
	int qn = sti(GameInterface.(nodeName).ListSize)-1;
	aref inar,outar;
	string attrName;
	for(int i=pnum; i<qn; i++)
	{
		attrName = "pic"+(i+1);
		makearef(inar,GameInterface.(nodeName).(attrName));
		attrName = "pic"+(i+2);
		makearef(outar,GameInterface.(nodeName).(attrName));
		CopyAttributes(inar,outar);
	}
	attrName = "pic"+(i+1);
	DeleteAttribute(&GameInterface,nodeName+"."+attrName);
	if(qn>=0) GameInterface.(nodeName).ListSize = qn;
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_DEL_SCROLLIMAGE, nodeName, pnum);
}

void AddToScroll(string nodeName,int pnum)
{
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_ADD_SCROLLIMAGE, nodeName, pnum);
}

void XI_SetQuestTitles(string nodName,aref questInfo,int topNum)
{
	SendMessage(&GameInterface,"lsal",MSG_INTERFACE_SET_TITLE_STRINGS,nodName,questInfo,topNum);
}

int GetShipTexture(string shipType)
{
	if(shipType=="Not Used") return -1;
	if(shipType=="Galeoth1") return 1;
	if(shipType=="Galeoth2") return 1;
	if(shipType=="Fearless") return 1;
	if(shipType=="GhostShip") return 1;
	return 0;
}

string GetShipTextureName(string shipType)
{
	if(shipType=="Not Used") return "";
	if(shipType=="Galeoth1") return "SHIPS1";
	if(shipType=="Galeoth2") return "SHIPS1";
	if(shipType=="Fearless") return "SHIPS1";
	if(shipType=="GhostShip") return "SHIPS1";
	return "SHIPS16";
}

string GetFaceGroupName(int charIdx)
{
	if(charIdx<0) {return "EMPTYFACE";}
	return "FACE128_"+Characters[charIdx].FaceID;
}

string GetMinifiedFaceGroupName(int charIdx)
{
    if(charIdx<0) {return "EMPTYFACE";}
    return "%_"+Characters[charIdx].FaceID;
}

string PrepareMinifiedFaceString(string facestr)
{
    string preparedFacestr = facestr;

    while(HasSubStr(preparedFacestr, "%")) {
        preparedFacestr = strreplace(preparedFacestr, "%", "FACE128");
    }

    return preparedFacestr;
}

string GetFacePictureName(int charIdx)
{
	if(charIdx<0) return "emptyface";
	return "face";
}
//-------------------------------------------------------------------------------------------------------------
// FormatedText
//-------------------------------------------------------------------------------------------------------------
void SetFormatedText(string sNodeName, string sText)
{
	SendMessage(&GameInterface,"lss",MSG_INTERFACE_SET_FORMATEDTEXT,sNodeName,sText);
}
//-------------------------------------------------------------------------------------------------------------
void AddLineToFormatedText(string sNodeName, string sText)
{
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, &sText);
}
//-------------------------------------------------------------------------------------------------------------
void SelectLineInFormatedText(string sNodeName, int line)
{
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNodeName, 1, line);
}
//-------------------------------------------------------------------------------------------------------------
int SelectedLineInFormatedText(string sNodeName)
{
	return SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNodeName, 11);
}

int SetVAligmentFormatedText(string sNodeName)  // boal нарыл в ядре, что можно
{
	return SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNodeName, 5);
}
//-------------------------------------------------------------------------------------------------------------
// Warship -->
void SetFormattedTextLastLineColor(string _sNodeName, int _iColor)
{
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _sNodeName, 8, -1, _iColor); // -1 = последняя лини, как я понял
}
// <--
//-------------------------------------------------------------------------------------------------------------

string FloatToString(float fl,int nDigAfterPoint)
{
	//float fmul = pow(10.0,nDigAfterPoint);
	//fl = fl + 0.5/fmul;
	//int p1 = makeint(fl);
	//int p2 = makeint((fl-p1)*fmul);
	//return p1+"."+p2;

	fl= fl + 0.5/pow(10.0,nDigAfterPoint); // округление
	int p1 = makeint(fl); // целая часть
	string str = p1 + "."; // строка
	for(int n=0; n<nDigAfterPoint; n++)
	{
		fl = (fl - p1)*10.0;
		p1 = makeint(fl);
		str = str + p1;
	}
	return str;
}
int GetStringWidth(string str, string fontID, float fScale)
{
	return SendMessage(&GameInterface, "lssf", MSG_INTERFACE_GET_STRWIDTH, str, fontID, fScale);
}

string GetItemPictureName(string itemName)
{
	aref arItm;
	if( Items_FindItem(itemName,&arItm)>=0 )
	{
		if( CheckAttribute(arItm,"picIndex") )
		{
			return	"itm"+sti(arItm.picIndex);
		}
	}
	return "cannon back";
}

string GetItemTextureName(string itemName)
{
	aref arItm;
	if( Items_FindItem(itemName,&arItm)>=0 )
	{
		if( CheckAttribute(arItm,"picTexture") )
		{
			return	arItm.picTexture;
		}
	}
	return "ICONS";
}

int GetItemPictureTexture(string accessString, string itemName)
{
	aref arItm,arGroup;
	makearef(arGroup,GameInterface.(accessString));
	string sTexName = "ICONS";

	if( Items_FindItem(itemName,&arItm)>=0 )
	{	if( CheckAttribute(arItm,"picTexture") )
		{	sTexName = arItm.picTexture;
		}
	}
	int q = GetAttributesNum(arGroup);
	for(int i=0; i<q; i++)
	{	if( GetAttributeValue(GetAttributeN(arGroup,i)) == sTexName )
		{	return i;
		}
	}
	return -1;
}

void FillImagesGroupForItems(aref arImgGrp)
{
	int i,n,q;
	string stmp;
	object objtmp;
	for(i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute( &Items[i], "picTexture" ) && Items[i].picTexture!="" )
		{
			stmp = Items[i].picTexture;
			objtmp.(stmp) = true;
		}
	}
	q = GetAttributesNum(&objtmp);
	n = GetAttributesNum(arImgGrp);
	for(i=0; i<q; i++)
	{
		stmp = "t"+n;
		arImgGrp.(stmp) = GetAttributeName(GetAttributeN(&objtmp,i));
		n++;
	}
}

string GetFacePicName(ref chref)
{
	return "face";
}


void FillFaceList(string strAccess, ref chref, int fillCode)
{
	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int n, cn, q;

	AddFaceGroup(strAccess,"FACE128_"+chref.faceID);

	if(fillCode==0) // officers
	{
		//officers
		if (chref.Fellows.Passengers.navigator == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_NAVIGATOR");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.navigator)].faceID);
		}

		if (chref.Fellows.Passengers.boatswain == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_BOATSWAIN");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.boatswain)].faceID);
		}

		if (chref.Fellows.Passengers.cannoner == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_cannoner");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.cannoner)].faceID);
		}

		if (chref.Fellows.Passengers.doctor == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_doctor");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.doctor)].faceID);
		}

		if (chref.Fellows.Passengers.treasurer == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_treasurer");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.treasurer)].faceID);
		}

		if (chref.Fellows.Passengers.carpenter == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_carpenter");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.carpenter)].faceID);
		}

		//fighters
		for(n=1; n<=MAX_NUM_FIGHTERS; n++)
		{
			cn = GetOfficersIndex(chref,n);
			if( cn>=0 ) {
				AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
			}
			else
			{
				AddFaceGroup(strAccess,"FACE128_fighter");
			}
		}
	}

	if(fillCode==1) // companions
	{
		for(n=1; n<COMPANION_MAX; n++)
		{
			cn = GetCompanionIndex(chref,n);
			if( cn>=0 ) {
				AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
			}
		}
	}

	if(fillCode==2) // passengers
	{
		q = GetPassengersQuantity(chref);
		for(n=0; n<q; n++)
		{
			cn = GetPassenger(chref,n);
			if( cn>=0)
			{
				AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
			}
		}
	}

	if(fillCode==3) // officer for hire
	{

	}
	if(fillCode==4) // free passengers
	{
		q = GetPassengersQuantity(chref);
		for(n=0; n<q; n++)
		{
			cn = GetPassenger(chref,n);
			if( cn>=0)
			{
				if (!CheckAttribute(&characters[cn], "prisoned") || sti(characters[cn].prisoned) != true)
				{
					if(!CheckAttribute(&characters[cn], "isfree"))
					{
						if(!CheckAttribute(&characters[cn], "isquest")) // to_do
						{
							AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
						}
					}
				}
			}
		}
	}
}

void FillShipList(string strAccess, ref chref)
{
	/*
	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int n, cn, q;
	int iShipType;
	string sShip;

	for(n=0; n<COMPANION_MAX; n++)
	{
		cn = GetCompanionIndex(chref, n);
		if(cn != -1)
		{
			iShipType = GetCharacterShipType(/*&*//*characters[cn]);
			iShipType = sti(RealShips[iShipType].basetype);
			sShip = ShipsTypes[iShipType].name;
			AddFaceGroup(strAccess,"SHIPS_"+sShip);
		}
	}
	*/

	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int n;
	string sShip;

	for(n= 0; n< SHIP_TYPES_QUANTITY; n++)
	{
		if(CheckAttribute(ShipsTypes[n], "name"))
			sShip = ShipsTypes[n].name;
		else
			sShip = "";
		AddFaceGroup(strAccess,"SHIPS_"+sShip);
	}
}

void FillItemsPicturesList(string strAccess, ref chref)  // to_do del
{
	AddFaceGroup(strAccess, "WEAPONS");
	/*
	AddFaceGroup(strAccess, "ITEMS_1");
	AddFaceGroup(strAccess, "ITEMS_2");
	AddFaceGroup(strAccess, "ITEMS_3");
	AddFaceGroup(strAccess, "ITEMS_4");
	*/
	return;
}
void FillUpgradesList(string strAccess, string smode, int iCannonMaterial)  // to_do del
{
	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int iMax;
	if(smode == "cannons")
	{
		iMax = CANNON_TYPES_QUANTITY + 1;
	}
	else
	{
		iMax = 4;
	}
	if(smode == "cannons")
	{
		AddFaceGroup(strAccess,smode + "_UPGRADE_"+iCannonMaterial);
	}
	else
	{
		for(int i = 1; i < iMax; i++)
		{
			AddFaceGroup(strAccess,smode + "_UPGRADE_"+i);
		}
	}
}


void AddFaceGroup(string strAccess, string groupName)
{
	if( FindFaceGroupNum(strAccess,groupName)<0 )
	{
		aref ar;
		makearef(ar, GameInterface.(strAccess));
		string attrName = "t"+GetAttributesNum(ar);
		ar.(attrName) = groupName;
	}
}

int FindFaceGroupNum(string strAccess, string groupName)
{
	int n, q;
	aref aRoot, aCur;
	makearef(aRoot, GameInterface.(strAccess));

	q = GetAttributesNum(aRoot);
	for(n=0; n<q; n++)
	{
		aCur = GetAttributeN(aRoot,n);
		if( GetAttributeValue(aCur) == groupName ) return n;
	}

	return -1;
}

string GlobalStringConvert(string strID)
{
	return LanguageConvertString( GlobalLngFileID(), strID );
}

void EnumerateIcons(string sDirectory, string sFileMask, string sControlName, int iAddListSize)
{
	object fileFinder;
	fileFinder.dir = sDirectory;
	fileFinder.mask = sFileMask;
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	aref arFileList;
	makearef(arFileList, fileFinder.filelist);
	int iNumFiles = GetAttributesNum(arFileList);
	for (int i = 0; i < iNumFiles; i++)
	{
		string sFile = "id" + i;
		string attrName = "pic" + (i + 1);

		GameInterface.(sControlName).(attrName).name1 = sDirectory + "\" + arFileList.(sFile);
		GameInterface.(sControlName).(attrName).FileName = arFileList.(sFile);
	}
	GameInterface.(sControlName).ListSize = iNumFiles + iAddListSize;
}

void CreateTooltip(string header, string text1, int color1, string text2, int color2, string text3, int color3, string text4, int color4, string picTexture, string picGroup, string picImage, int nPicWidth, int nPicHeight)
{
	// сохранить состояния окон и элементов
	int nSaveNodeState = -1;
	nSaveNodeState = XI_StoreNodeLocksWithOff();
	InterfaceStates.tooltip.savestate = nSaveNodeState;
	InterfaceStates.tooltip.oldcurrentnode = GetCurrentNode();
	// создать элементы тултипа:
	XI_MakeNode( "", "TOOLTIP_FADER", "tooltip_fader", 30000 ); // fader
	XI_MakeNode( "", "TOOLTIP_FRAME", "tooltip_frame", 30000 ); // окно
	XI_MakeNode( "", "TOOLTIP_TITLERECT", "tooltip_titlerect", 30001 ); // заголовок
	XI_MakeNode( "", "TOOLTIP_PICTURE", "tooltip_picture", 30001 ); // картинка
	XI_MakeNode( "", "TOOLTIP_TEXTRECT", "tooltip_textborder2", 30001 ); // окно для техт2
	XI_MakeNode( "", "TOOLTIP_TEXTRECT", "tooltip_textborder4", 30001 ); // окно для техт4
	XI_MakeNode( "", "TOOLTIP_TITLE", "tooltip_titile", 30002 ); // заголовок
	XI_MakeNode( "", "TOOLTIP_TEXT1", "tooltip_text1", 30002 ); //
	XI_MakeNode( "", "TOOLTIP_TEXT2", "tooltip_text2", 30002 ); //
	XI_MakeNode( "", "TOOLTIP_TEXT3", "tooltip_text3", 30002 ); //
	XI_MakeNode( "", "TOOLTIP_TEXT4", "tooltip_text4", 30002 ); //
	SendMessage(&GameInterface,"lsslslslslsssll",MSG_INTERFACE_SET_TOOLTIP, header, text1,color1, text2,color2, text3,color3, text4,color4, picTexture, picGroup, picImage, nPicWidth, nPicHeight );
}

void CloseTooltip()
{
	// удалить элементы тултипа:
	XI_DeleteNode( "tooltip_fader" ); // окно
	XI_DeleteNode( "tooltip_frame" ); // окно
	XI_DeleteNode( "tooltip_titlerect" ); // заголовок
	XI_DeleteNode( "tooltip_picture" ); // картинка
	XI_DeleteNode( "tooltip_textborder2" ); // окно
	XI_DeleteNode( "tooltip_textborder4" ); // окно
	XI_DeleteNode( "tooltip_titile" ); // заголовок
	XI_DeleteNode( "tooltip_text1" ); //
	XI_DeleteNode( "tooltip_text2" ); //
	XI_DeleteNode( "tooltip_text3" ); //
	XI_DeleteNode( "tooltip_text4" ); //
	// воccтановить состояния окон и элементов
	if( CheckAttribute(&InterfaceStates,"tooltip.oldcurrentnode") ) {
		SetCurrentNode(InterfaceStates.tooltip.oldcurrentnode);
	}
	int nSaveNodeState = -1;
	if( CheckAttribute(&InterfaceStates,"tooltip.savestate") ) {
		nSaveNodeState = sti(InterfaceStates.tooltip.savestate);
	}
	if( nSaveNodeState!=-1 ) {
		XI_RestoreNodeLocks(nSaveNodeState);
		InterfaceStates.tooltip.savestate = -1;
	}
}

/* string GetMoralePicture(float fMoraleValue)
{
	if( fMoraleValue >= 75.0 ) {return "interfaces\flags\flag_1_64.tga.tx";}
	if( fMoraleValue >= 50.0 ) {return "interfaces\flags\flag_2_64.tga.tx";}
	if( fMoraleValue >= 25.0 ) {return "interfaces\flags\flag_3_64.tga.tx";}
	return "interfaces\flags\flag_4_64.tga.tx";
}

string GetExperiencePicture(float fExpValue)
{
	if( fExpValue >= 75.0 ) {return "interfaces\stars\Yellow_star1.tga.tx";}
	if( fExpValue >= 50.0 ) {return "interfaces\stars\Yellow_star2.tga.tx";}
	if( fExpValue >= 25.0 ) {return "interfaces\stars\Yellow_star3.tga.tx";}
	return "interfaces\stars\Yellow_star4.tga.tx";
} */

string GetMoraleGroupPicture(float fMoraleValue)
{
	if( fMoraleValue >= 75.0 ) {return "high morale";}
	if( fMoraleValue >= 40.0 ) {return "medium morale";}
	return "low morale";
}

bool XI_FindFoldersWithoutNetsave(string sFindTemplate,aref arFoldersList)
{
		bool bRetVal = XI_FindFolders(sFindTemplate,arFoldersList);

	int num = GetAttributesNum(arFoldersList);
	int i = 0;
	for(i=0; i<num; i++) {
		if( "NetSaves" == GetAttributeValue(GetAttributeN(arFoldersList,i)) )
		{
			DeleteAttribute( arFoldersList, GetAttributeName(GetAttributeN(arFoldersList,i)) );
			return bRetVal;
		}
	}

	return bRetVal;
}
// boal -->
void ReadSavedOptionsEx(ref gopt)
{
	string sFileName = "options";
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, sFileName, gopt);
}

void SaveSavedOptionsEx(ref gopt)
{
	string sFileName = "options";
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, sFileName, gopt);
}

void SaveStartGameParam()
{
    object gopt;

	ReadSavedOptionsEx(&gopt);

	ref optref = &gopt;

    optref.StartGameParam.PlayerProfile    = GameInterface.PROFILE_NAME.str;//PlayerProfile.name;
    optref.StartGameParam.MOD_SKILL_ENEMY_RATE   = MOD_SKILL_ENEMY_RATE;
	optref.StartGameParam.MOD_DEAD_CLEAR_TIME   = MOD_DEAD_CLEAR_TIME;
	optref.StartGameParam.MainChAnim   = MainChAnim;
    optref.StartGameParam.bHardcoreGame          = bHardcoreGame;
	optref.StartGameParam.bPartitionSet          = bPartitionSet;
	optref.StartGameParam.bSailorsWeight         = bSailorsWeight;
	optref.StartGameParam.bNewSails         	 = bNewSails;
	optref.StartGameParam.bHardAnimations  		 = bHardAnimations;
	optref.StartGameParam.bHardBoss  		 	 = bHardBoss;
	optref.StartGameParam.bHigherShipRate  		 = bHigherShipRate;
	optref.StartGameParam.bHigherSelfRate  		 = bHigherSelfRate;
	optref.StartGameParam.bHalfImmortalPGG  	 = bHalfImmortalPGG;
	optref.StartGameParam.bPortPermission  		 = bPortPermission;
	optref.StartGameParam.bBribeSoldiers  		 = bBribeSoldiers;
	optref.StartGameParam.bNoBonusSkillOff  	 = bNoBonusSkillOff;
    optref.StartGameParam.bRechargePistolOnLine  = bRechargePistolOnLine;
    optref.StartGameParam.iEncountersRate        = iEncountersRate;
	optref.StartGameParam.iEncountersCountRate   = iEncountersCountRate;
	optref.StartGameParam.iArcadeSails           = iArcadeSails;
	optref.StartGameParam.bAltBalance          	 = bAltBalance;
	optref.StartGameParam.bFillEncyShips         = bFillEncyShips;
	optref.StartGameParam.bDifficultyWeight      = bDifficultyWeight;
    // иначе сброс галки может быть optref.StartGameParam.bWorldAlivePause       = bWorldAlivePause;

    optref.StartGameParam.HeroType         = NullCharacter.HeroParam.HeroType;
    optref.StartGameParam.Nation           = NullCharacter.HeroParam.Nation;
    optref.StartGameParam.CurHeroNum       = startHeroType;

	SaveSavedOptionsEx(&gopt);
}
void LoadStartGameParam()
{
    object gopt;

	ReadSavedOptionsEx(&gopt);

	ref optref = &gopt;

	if (CheckAttribute(optref, "StartGameParam.PlayerProfile"))
	{
    	GameInterface.PROFILE_NAME.str = optref.StartGameParam.PlayerProfile;
    }

    if (CheckAttribute(optref, "StartGameParam.MOD_SKILL_ENEMY_RATE"))
	{
    	MOD_SKILL_ENEMY_RATE = sti(optref.StartGameParam.MOD_SKILL_ENEMY_RATE);
    }
	if (CheckAttribute(optref, "StartGameParam.MOD_DEAD_CLEAR_TIME"))
	{
    	MOD_DEAD_CLEAR_TIME = sti(optref.StartGameParam.MOD_DEAD_CLEAR_TIME);
    }
	if (CheckAttribute(optref, "StartGameParam.MainChAnim"))
	{
    	MainChAnim = sti(optref.StartGameParam.MainChAnim);
    }
    if (CheckAttribute(optref, "StartGameParam.bHardcoreGame"))
	{
    	bHardcoreGame = sti(optref.StartGameParam.bHardcoreGame);
    }
	if (CheckAttribute(optref, "StartGameParam.bPartitionSet"))
	{
    	bPartitionSet = sti(optref.StartGameParam.bPartitionSet);
    }
	if (CheckAttribute(optref, "StartGameParam.bSailorsWeight"))
	{
    	bSailorsWeight = sti(optref.StartGameParam.bSailorsWeight);
    }
	if (CheckAttribute(optref, "StartGameParam.bNewSails"))
	{
    	bNewSails = sti(optref.StartGameParam.bNewSails);
    }
	if (CheckAttribute(optref, "StartGameParam.bHardAnimations"))
	{
    	bHardAnimations = sti(optref.StartGameParam.bHardAnimations);
    }
	if (CheckAttribute(optref, "StartGameParam.bHardBoss"))
	{
    	bHardBoss = sti(optref.StartGameParam.bHardBoss);
    }
	if (CheckAttribute(optref, "StartGameParam.bHigherShipRate"))
	{
    	bHigherShipRate = sti(optref.StartGameParam.bHigherShipRate);
    }
	if (CheckAttribute(optref, "StartGameParam.bHigherSelfRate"))
	{
    	bHigherSelfRate = sti(optref.StartGameParam.bHigherSelfRate);
    }
	if (CheckAttribute(optref, "StartGameParam.bHalfImmortalPGG"))
	{
    	bHalfImmortalPGG = sti(optref.StartGameParam.bHalfImmortalPGG);
    }
	if (CheckAttribute(optref, "StartGameParam.bNoBonusSkillOff"))
	{
    	bNoBonusSkillOff = sti(optref.StartGameParam.bNoBonusSkillOff);
    }
	if (CheckAttribute(optref, "StartGameParam.bPortPermission"))
	{
    	bPortPermission = sti(optref.StartGameParam.bPortPermission);
    }
	if (CheckAttribute(optref, "StartGameParam.bBribeSoldiers"))
	{
    	bBribeSoldiers = sti(optref.StartGameParam.bBribeSoldiers);
    }
    if (CheckAttribute(optref, "StartGameParam.bRechargePistolOnLine"))
	{
    	bRechargePistolOnLine = sti(optref.StartGameParam.bRechargePistolOnLine);
    }
    if (CheckAttribute(optref, "StartGameParam.iEncountersRate"))
	{
    	iEncountersRate = sti(optref.StartGameParam.iEncountersRate);
    }
	if (CheckAttribute(optref, "StartGameParam.iEncountersCountRate"))
	{
    	iEncountersCountRate = sti(optref.StartGameParam.iEncountersCountRate);
    }
    if (CheckAttribute(optref, "StartGameParam.iArcadeSails"))
	{
    	iArcadeSails = sti(optref.StartGameParam.iArcadeSails);
    }
    if (CheckAttribute(optref, "StartGameParam.bWorldAlivePause"))
	{
    	//bWorldAlivePause = sti(optref.StartGameParam.bWorldAlivePause);
    }
    //////
    if (CheckAttribute(optref, "StartGameParam.HeroType"))
	{
    	NullCharacter.HeroParam.HeroType = optref.StartGameParam.HeroType;
    }
    if (CheckAttribute(optref, "StartGameParam.Nation"))
	{
    	NullCharacter.HeroParam.Nation = optref.StartGameParam.Nation;
    }
    if (CheckAttribute(optref, "StartGameParam.CurHeroNum"))
	{
		startHeroType = sti(optref.StartGameParam.CurHeroNum);
	}
	if (CheckAttribute(optref, "StartGameParam.bAltBalance"))
	{
    	bAltBalance = sti(optref.StartGameParam.bAltBalance);
    }
	if (CheckAttribute(optref, "StartGameParam.bDifficultyWeight"))
	{
    	bDifficultyWeight = sti(optref.StartGameParam.bDifficultyWeight);
    }
}
void LoadPlayerProfileDefault()
{
    object gopt;

	ReadSavedOptionsEx(&gopt);

	ref optref = &gopt;

	if (CheckAttribute(optref, "StartGameParam.PlayerProfile"))
	{
    	PlayerProfile.name = optref.StartGameParam.PlayerProfile;
    }
}

// boal сложность -->
string GetLevelComplexity(int _Level_Complexity)
{
	switch (_Level_Complexity)
	{
	    case 1 :
            return XI_ConvertString("m_Complexity_1"); //Матрос "Халява";
            break;
        case 2 :
            return XI_ConvertString("m_Complexity_2"); // Боцман "Юнга";
            break;
        case 3 :
            return XI_ConvertString("m_Complexity_3");//Шкипер "Матрос";
            break;
        case 4 :
            return XI_ConvertString("m_Complexity_4");//Лейтенант "Боцман";
            break;
        case 5 :
            return XI_ConvertString("m_Complexity_5");
            break;
        case 6 :
            return XI_ConvertString("m_Complexity_6");
            break;
        case 7 :
            return XI_ConvertString("m_Complexity_7");//Командор "Пират";
            break;
        case 8 :
            return XI_ConvertString("m_Complexity_8");
            break;
        case 9 :
            return XI_ConvertString("m_Complexity_9");
            break;
        case 10 :
            return XI_ConvertString("m_Complexity_10");
            break;
    }
}

string GetAchievementName(string ach_name, int level) // Получим имя достижения (Rasteador) (ver 0.3.0)
{
	int lngFileID = LanguageOpenFile("AchievementsDescr.txt");
	string describeStr = "";

	describeStr = LanguageConvertString(lngFileID, ach_name + "_" + level);
	LanguageCloseFile(lngFileID);

	return describeStr;
}

string GetAchievementDescrible(string ach_name, int level) // Получим описание достижения (Rasteador) (ver 0.3.0)
{
	int lngFileID = LanguageOpenFile("AchievementsDescr.txt");
	string describeStr = "";

	describeStr = LanguageConvertString(lngFileID, ach_name + "_" + level + "_descr");
	LanguageCloseFile(lngFileID);

	return describeStr;
}

string GetAchievementIcon(string ach_name) // Получим описание достижения (Rasteador) (ver 0.3.0)
{
	int lngFileID = LanguageOpenFile("AchievementsDescr.txt");
	string describeStr = "";

	describeStr = LanguageConvertString(lngFileID, ach_name + "_icon");
	Log_TestInfo(describeStr);
	LanguageCloseFile(lngFileID);

	return describeStr;
}

string GetItemDescribe(string sItemID)
{
	int iGoodIndex = Items_FindItemIdx(sItemID);
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
    string describeStr = "";
	string ammotype = "";

	if (CheckAttribute(arItm, "groupID"))
	{
		//aw013 -->
		/*if(arItm.groupID == CIRASS_ITEM_TYPE)
		{
			float fItmShield = stf(arItm.CirassLevel) * 100.0;
			describeStr += "Защита " + FloatToString(fItmShield, 2) + " проц." + newStr();
		}*/
		//aw013 <--

		if(arItm.groupID == GUN_ITEM_TYPE)
		{
			if(CheckAttribute(arItm,"type.t1") && !CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
			{
				ammotype = LanguageConvertString(lngFileID, "itmname_"+arItm.type.t1.bullet) + ".";
				describeStr += GetAssembledString(
				LanguageConvertString(lngFileID,"weapon gun parameters"),
				arItm) + "."  + NewStr() + "При стрельбе используется " + ammotype + newStr();
			}
			if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
			{
				ammotype = LanguageConvertString(lngFileID, "itmname_"+arItm.type.t1.bullet) + "/" + LanguageConvertString(lngFileID, "itmname_"+arItm.type.t2.bullet) + ".";
				int dmg21m = arItm.type.t1.DmgMin_NC;
				int dmg21ma = arItm.type.t1.DmgMax_NC;
				int dmg21a = arItm.type.t1.Accuracy;
				int dmg21c = arItm.type.t1.ChargeSpeed;
				int dmg22m = arItm.type.t2.DmgMin_NC;
				int dmg22ma = arItm.type.t2.DmgMax_NC;
				int dmg22a = arItm.type.t2.Accuracy;
				int dmg22c = arItm.type.t2.ChargeSpeed;
				string sTemp;
				if (dmg21a != dmg22a) sTemp =  dmg21a+"%/"+dmg22a+"%";
				else sTemp = dmg21a+"%";
				string sTemp1;
				if(dmg21m == dmg22m || dmg21ma == dmg22ma ) sTemp1 = "урон мин/макс " + dmg21m+"/"+dmg21ma;
				else sTemp1 = "урон мин "+dmg21m+"/"+dmg22m + " макс " + dmg21ma+"/"+dmg22ma;
				string sTemp2;
				if (dmg21c == dmg22c) sTemp2 = dmg21c;
				else sTemp2 = dmg21c+"/"+dmg22c;
				describeStr += "Оружие: " + sTemp1 +  NewStr()+"Время перезарядки "+ sTemp2 +" сек., точность "+ sTemp  + NewStr() + "При стрельбе используются: " + ammotype + NewStr();
			}
			if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && CheckAttribute(arItm,"type.t3"))
			{
				ammotype = LanguageConvertString(lngFileID, "itmname_"+arItm.type.t1.bullet) + "/" + LanguageConvertString(lngFileID, "itmname_"+arItm.type.t2.bullet) + "/" + LanguageConvertString(lngFileID, "itmname_"+arItm.type.t3.bullet) + ".";
				int dmg31m = arItm.type.t1.DmgMin_NC;
				int dmg31ma = arItm.type.t1.DmgMax_NC;
				int dmg31a = arItm.type.t1.Accuracy;
				int dmg31c = arItm.type.t1.ChargeSpeed;
				int dmg32m = arItm.type.t2.DmgMin_NC;
				int dmg32ma = arItm.type.t2.DmgMax_NC;
				int dmg32a = arItm.type.t2.Accuracy;
				int dmg32c = arItm.type.t2.ChargeSpeed;
				int dmg33m = arItm.type.t3.DmgMin_NC;
				int dmg33ma = arItm.type.t3.DmgMax_NC;
				int dmg33a = arItm.type.t3.Accuracy;
				int dmg33c = arItm.type.t3.ChargeSpeed;
				if (dmg31a == dmg32a && dmg32a == dmg33a) sTemp = dmg31a+"%";
				else  sTemp =  dmg31a+"%/"+dmg32a+"%/"+dmg33a+"%";
				if(dmg31m == dmg32m && dmg33m == dmg32m) sTemp1 = "урон мин/макс " + dmg31m+"/"+dmg31ma;
				else sTemp1 = "урон мин "+dmg31m+"/"+dmg32m+"/"+dmg33m+" макс "+dmg31ma+"/"+dmg32ma+"/"+dmg33ma;
				if (dmg31c == dmg32c && dmg32c == dmg33c) sTemp2 = dmg31c;
				else sTemp2 = dmg31c+"/"+dmg32c+"/"+dmg33c;
				describeStr += "Оружие: "+sTemp1+","+ NewStr()+"Время перезарядки "+sTemp2+" сек., точность "+sTemp + NewStr() + "При стрельбе используются: " + ammotype + NewStr();
			}
			if (CheckAttribute(arItm,"ReqPerk"))
			{
				if (arItm.ReqPerk == "Gunman") describeStr += "Для использования требуется навык 'Стрелок'."+ NewStr();
				if (arItm.ReqPerk == "GunProfessional") describeStr += "Для использования требуется навык 'Мушкетер'."+ NewStr();
			}
			else describeStr += "Не требует специальных навыков."+ NewStr();
		}
		if(arItm.groupID == BACKPACK_ITEM_TYPE)
		{
			float fBackPackWeight = stf(arItm.BackPackWeight);
			string sBackPackWeight = FloatToString(fBackPackWeight, 1);
			describeStr += GetAssembledString(LanguageConvertString(lngFileID,"BackPackWeight"), arItm) + newStr();
		}
		if(arItm.groupID==BLADE_ITEM_TYPE)
		{
			float dmg_min, dmg_max, weight;
			GetBladeParams(sItemID, &dmg_min, &dmg_max, &weight);
			int price = CalculateBladePrice(arItm.FencingType, dmg_min, dmg_max, weight);

			// Собираем фейковый айтем, так как генерируемые параметры не содержатся в изначальном айтеме
			object tempObj;
			aref arTemp;
			makearef(arTemp, tempObj);
			CopyAttributes(arTemp, arItm);
			tempObj.dmg_min = dmg_min;
			tempObj.dmg_max = dmg_max;
			tempObj.weight = weight;
			tempObj.price = price;

			describeStr += GetAssembledString(
				LanguageConvertString(lngFileID,"weapon blade parameters"),
				arTemp) + newStr();

			if (CheckAttribute(arItm, "FencingType"))
			{
    			arItm.FencingTypeName = XI_ConvertString(arItm.FencingType);
    			describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon blade type"), arItm) + newStr();
			}
			else
			{
                describeStr += "ERROR" + newStr();
			}
		}
	}

	describeStr = describeStr + GetAssembledString(LanguageConvertString(lngFileID, Items[iGoodIndex].describe), &Items[iGoodIndex]);
	if (CheckAttribute(arItm, "potion"))
	{
		if (CheckAttribute(arItm, "potion.health"))
		{
			describeStr += NewStr() + LanguageConvertString(lngFileID, "Potion parameters")+": ";
			describeStr += "HP";
			if (stf(arItm.potion.health) >= 0)
			{
				describeStr += " + " + sti(arItm.potion.health) + "\n";
			}
			else
			{
				describeStr += "" + sti(arItm.potion.health) + "\n";
			}
		}
	}
	if (CheckAttribute(arItm, "Food"))
	{
		if (CheckAttribute(arItm, "Food.energy"))
		{
			describeStr += NewStr() + LanguageConvertString(lngFileID, "Energy parameters")+":";
			if (stf(arItm.Food.energy) >= 0)
			{
				describeStr += " + " + sti(arItm.Food.energy) +"\n";
			}
			else
			{
				describeStr += " " + sti(arItm.Food.energy) +"\n";
			}
		}
	}
	describeStr += "\nЦена " + GetItemPrice(sItemID) + " / Вес " + FloatToString(GetItemWeight(sItemID), 2) + newStr();
	if (CheckAttribute(arItm, "groupID"))//Книги, процент прочитанности - Gregg
	{
		if(arItm.groupID == BOOK_ITEM_TYPE)
		{
			if (CheckAttribute(pchar,"booktype") && pchar.bookname == arItm.name)//сейчас читаем книгу
			{
				float value = ((sti(pchar.booktime)*100)/sti(pchar.booktime.full)-100)*(-1.0);
				string text = FloatToString(value,1);
				describeStr += "Прочитано примерно "+text+"%.";
			}
			string sBookname = arItm.name;
			if (checkattribute(pchar,"halfreadbook."+sBookname))//книга, которую сняли недочитав
			{
				float value1 = ((sti(pchar.halfreadbook.(sBookname).booktime)*100)/sti(pchar.halfreadbook.(sBookname).booktime.full)-100)*(-1.0);
				string text1 = FloatToString(value1,1);
				describeStr += "Прочитано примерно "+text1+"%.";
			}
		}
	}
	//aw013 <--

	LanguageCloseFile(lngFileID);

	return describeStr;
}

string GetGunDamage(ref arItm)
{
	if (arItm.groupID != GUN_ITEM_TYPE) return "-------";
	if(CheckAttribute(arItm,"type.t1") && !CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		int dmg11m = arItm.type.t1.DmgMin_NC;
		int dmg11ma = arItm.type.t1.DmgMax_NC;
		return "мин "+dmg11m+"\n"+"макс "+dmg11ma;
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		int dmg21m = arItm.type.t1.DmgMin_NC;
		int dmg21ma = arItm.type.t1.DmgMax_NC;
		int dmg22m = arItm.type.t2.DmgMin_NC;
		int dmg22ma = arItm.type.t2.DmgMax_NC;
		string sTemp2;
		if(dmg21m == dmg22m || dmg21ma == dmg22ma ) sTemp2 =  "мин "+dmg21m+"\nмакс "+dmg21ma;
		else sTemp2 = "мин "+dmg21m+"/"+dmg22m + "\nмакс " + dmg21ma+"/"+dmg22ma;
		return sTemp2;
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && CheckAttribute(arItm,"type.t3"))
	{
		int dmg31m = arItm.type.t1.DmgMin_NC;
		int dmg31ma = arItm.type.t1.DmgMax_NC;
		int dmg32m = arItm.type.t2.DmgMin_NC;
		int dmg32ma = arItm.type.t2.DmgMax_NC;
		int dmg33m = arItm.type.t3.DmgMin_NC;
		int dmg33ma = arItm.type.t3.DmgMax_NC;
		string sTemp3;
		if(dmg31m == dmg32m && dmg33m == dmg32m) sTemp3 = "мин "+dmg31m+"\nмакс "+dmg31ma;
		else sTemp3 = "мин "+dmg31m+"/"+dmg32m+"/"+dmg33m+"\nмакс "+dmg31ma+"/"+dmg32ma+"/"+dmg33ma;
		return sTemp3;
	}
}

string GetAmmoTypes(ref arItm)
{
	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	if (arItm.groupID != GUN_ITEM_TYPE) return "-------";
	if(CheckAttribute(arItm,"type.t1") && !CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		return LanguageConvertString(lngFileID, "itmname_"+arItm.type.t1.bullet);
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		return LanguageConvertString(lngFileID, "itmname_"+arItm.type.t1.bullet) + "/" + LanguageConvertString(lngFileID, "itmname_"+arItm.type.t2.bullet);
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && CheckAttribute(arItm,"type.t3"))
	{
		return LanguageConvertString(lngFileID, "itmname_"+arItm.type.t1.bullet) + "/" + LanguageConvertString(lngFileID, "itmname_"+arItm.type.t2.bullet) + "/" + LanguageConvertString(lngFileID, "itmname_"+arItm.type.t3.bullet);
	}
	LanguageCloseFile(lngFileID);
}

string GetAccuracy(ref arItm)
{
	if (arItm.groupID != GUN_ITEM_TYPE) return "-------";
	if(CheckAttribute(arItm,"type.t1") && !CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		return arItm.type.t1.Accuracy+"%";
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		int dmg21a = arItm.type.t1.Accuracy;
		int dmg22a = arItm.type.t2.Accuracy;
		if (dmg21a != dmg22a) return dmg21a+"%/"+dmg22a+"%";
		else return dmg21a+"%";
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && CheckAttribute(arItm,"type.t3"))
	{
		int dmg31a = arItm.type.t1.Accuracy;
		int dmg32a = arItm.type.t2.Accuracy;
		int dmg33a = arItm.type.t3.Accuracy;
		if (dmg31a == dmg32a && dmg32a == dmg33a) return dmg31a+"%";
		else  return dmg31a+"%/"+dmg32a+"%/"+dmg33a+"%";
	}
}

string GetRecharge(ref arItm)
{
	if (arItm.groupID != GUN_ITEM_TYPE) return "-------";
	if(CheckAttribute(arItm,"type.t1") && !CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		return arItm.type.t1.ChargeSpeed;
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && !CheckAttribute(arItm,"type.t3"))
	{
		int dmg21a = arItm.type.t1.ChargeSpeed;
		int dmg22a = arItm.type.t2.ChargeSpeed;
		if (dmg21a != dmg22a) return dmg21a+"/"+dmg22a;
		else return its(dmg21a);
	}
	if(CheckAttribute(arItm,"type.t1") && CheckAttribute(arItm,"type.t2") && CheckAttribute(arItm,"type.t3"))
	{
		int dmg31a = arItm.type.t1.ChargeSpeed;
		int dmg32a = arItm.type.t2.ChargeSpeed;
		int dmg33a = arItm.type.t3.ChargeSpeed;
		if (dmg31a == dmg32a && dmg32a == dmg33a) return its(dmg31a);
		else return dmg31a+"/"+dmg32a+"/"+dmg33a;
	}
}

string MsgIS(string _str)
{
	return GetConvertStr(_str, "interface_strings.txt");
}

void Table_UpdateWindow(string sTableControl)
{
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, sTableControl, 0);
}

void Table_Clear(string sTableControl, bool bClearHeader, bool bClearContent, bool bUpdateWindow)
{
	if (bClearHeader)
	{
	}

	if (bClearContent)
	{
		for (int i=1; i<2000; i++)
		{
			string sA = sTableControl + "." + "tr" + i;
			if (!CheckAttribute(&GameInterface, sA)) { break; }
			DeleteAttribute(&GameInterface, sA);
		}
	}

	if (bUpdateWindow)
	{
		Table_UpdateWindow(sTableControl);
	}
}
void Button_SetText(string sButtonControl, string sText)
{
	SendMessage( &GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sButtonControl, 0, sText);
}

void Button_SetEnable(string sButtonControl, bool bEnable)
{
	SetSelectable(sButtonControl, bEnable);
}

void CheckButton_SetDisable(string sControl, int iControlIndex, bool bDisableState)
{
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, sControl, 5, iControlIndex, bDisableState);
}

int CheckButton_GetState(string sControl, int iControlIndex)
{
	return SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sControl, 3, iControlIndex);
}

void CheckButton_SetState(string sControl, int iControlIndex, bool bState)
{
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, sControl, 2, iControlIndex, bState);
}

void StringCollection_SetText(string sControl, int iControlIndex, string sText)
{
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, sControl, 1, iControlIndex, sText);
}

void StringCollection_SetTextValue(string sControl, int iControlIndex, int iValue)
{
	string sValue = "#" + iValue;
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, sControl, 1, iControlIndex, sValue);
}

void ImageCollection_ChangeTextureGroup(string sControl, string sNewTextureGroup)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sControl, 1, sNewTextureGroup);
}

void ImageCollection_SetColor(string sControl, int iCIndex, int Color)
{
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, sControl, 3, iCIndex, Color);
}

void ScrollImage_SetPosition(string sControl, int iPosition)
{
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sControl, 1, iPosition);
}

// boal <--
