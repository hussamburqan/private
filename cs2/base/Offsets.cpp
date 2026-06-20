#include "Offsets.h"
#include "../utils/XorStr.h"

#include "rapidjson/document.h"
#include <iostream>
#include <iomanip>

using namespace rapidjson;

bool Offset::UpdateOffsets(std::string offsetdata, std::string clientdata)
{
	Document offsets, client;
	offsets.Parse(offsetdata.c_str());
	client.Parse(clientdata.c_str());

	offsetdata.clear(); clientdata.clear();

	// Decrypt key strings once
	std::string sDll = XS("client.dll");
	std::string sMatchDll = XS("matchmaking.dll");
	std::string sCBaseEntity = XS("C_BaseEntity");
	std::string sCCSPlayerCtrl = XS("CCSPlayerController");
	std::string sCBasePlayerCtrl = XS("CBasePlayerController");
	std::string sCBasePlayerPawn = XS("C_BasePlayerPawn");
	std::string sCCSPlayerPawn = XS("C_CSPlayerPawn");
	std::string sCCSPlayerPawnBase = XS("C_CSPlayerPawnBase");
	std::string sCSkeletonInst = XS("CSkeletonInstance");
	std::string sEntSpotState = XS("EntitySpottedState_t");
	std::string sCCSCamSvc = XS("CCSPlayerBase_CameraServices");
	std::string sClasses = XS("classes");
	std::string sFields = XS("fields");

	Offset::EntityList = offsets[sDll.c_str()][XS("dwEntityList").c_str()].GetUint64();
	Offset::Matrix = offsets[sDll.c_str()][XS("dwViewMatrix").c_str()].GetUint64();
	Offset::ViewAngle = offsets[sDll.c_str()][XS("dwViewAngles").c_str()].GetUint64();
	Offset::LocalPlayerController = offsets[sDll.c_str()][XS("dwLocalPlayerController").c_str()].GetUint64();
	Offset::LocalPlayerPawn = offsets[sDll.c_str()][XS("dwLocalPlayerPawn").c_str()].GetUint64();
	Offset::GlobalVars = offsets[sDll.c_str()][XS("dwGlobalVars").c_str()].GetUint64();
	Offset::Health = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_iHealth").c_str()].GetUint64();
	Offset::TeamID = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_iTeamNum").c_str()].GetUint64();
	Offset::Armor = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerCtrl.c_str()][sFields.c_str()][XS("m_iPawnArmor").c_str()].GetUint64();
	Offset::IsAlive = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerCtrl.c_str()][sFields.c_str()][XS("m_bPawnIsAlive").c_str()].GetUint64();
	Offset::MoneyService = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerCtrl.c_str()][sFields.c_str()][XS("m_pInGameMoneyServices").c_str()].GetUint64();
	Offset::PlayerPawn = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerCtrl.c_str()][sFields.c_str()][XS("m_hPlayerPawn").c_str()].GetUint64();
	Offset::iszPlayerName = client[sDll.c_str()][sClasses.c_str()][sCBasePlayerCtrl.c_str()][sFields.c_str()][XS("m_iszPlayerName").c_str()].GetUint64();
	Offset::Pos = client[sDll.c_str()][sClasses.c_str()][sCBasePlayerPawn.c_str()][sFields.c_str()][XS("m_vOldOrigin").c_str()].GetUint64();
	Offset::MaxHealth = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_iMaxHealth").c_str()].GetUint64();
	Offset::CurrentHealth = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_iHealth").c_str()].GetUint64();
	Offset::GameSceneNode = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_pGameSceneNode").c_str()].GetUint64();
	Offset::BoneArray = client[sDll.c_str()][sClasses.c_str()][sCSkeletonInst.c_str()][sFields.c_str()][XS("m_modelState").c_str()].GetUint64() + 0x80;
	Offset::MapName = offsets[sMatchDll.c_str()][XS("dwGameTypes_mapName").c_str()].GetUint64();
	Offset::angEyeAngles = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_angEyeAngles").c_str()].GetUint64();
	Offset::vecLastClipCameraPos = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_vecLastClipCameraPos").c_str()].GetUint64();
	Offset::pClippingWeapon = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_pClippingWeapon").c_str()].GetUint64();
	Offset::iShotsFired = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_iShotsFired").c_str()].GetUint64();
	Offset::flFlashDuration = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawnBase.c_str()][sFields.c_str()][XS("m_flFlashDuration").c_str()].GetUint64();
	Offset::aimPunchAngle = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_aimPunchAngle").c_str()].GetUint64();
	Offset::aimPunchCache = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_aimPunchCache").c_str()].GetUint64();
	Offset::iIDEntIndex = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_iIDEntIndex").c_str()].GetUint64();
	Offset::iTeamNum = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_iTeamNum").c_str()].GetUint64();
	Offset::CameraServices = client[sDll.c_str()][sClasses.c_str()][sCBasePlayerPawn.c_str()][sFields.c_str()][XS("m_pCameraServices").c_str()].GetUint64();
	Offset::iFovStart = client[sDll.c_str()][sClasses.c_str()][sCCSCamSvc.c_str()][sFields.c_str()][XS("m_iFOVStart").c_str()].GetUint64();
	Offset::fFlags = client[sDll.c_str()][sClasses.c_str()][sCBaseEntity.c_str()][sFields.c_str()][XS("m_fFlags").c_str()].GetUint64();

	int m_entitySpottedState = client[sDll.c_str()][sClasses.c_str()][sCCSPlayerPawn.c_str()][sFields.c_str()][XS("m_entitySpottedState").c_str()].GetUint64();
	int m_bSpottedByMask = client[sDll.c_str()][sClasses.c_str()][sEntSpotState.c_str()][sFields.c_str()][XS("m_bSpottedByMask").c_str()].GetUint64();
	Offset::bSpottedByMask = m_entitySpottedState + m_bSpottedByMask;

	return true;
}