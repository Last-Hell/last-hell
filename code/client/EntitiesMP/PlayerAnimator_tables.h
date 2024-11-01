/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

CEntityEvent *EAnimatorInit_New(void) { return new EAnimatorInit; };
CDLLEntityEvent DLLEvent_EAnimatorInit = {
	0x01960000, &EAnimatorInit_New
};
CDLLEntityEvent *CPlayerAnimator_events[] = {
	&DLLEvent_EAnimatorInit,
};
#define CPlayerAnimator_eventsct ARRAYCOUNT(CPlayerAnimator_events)
#define ENTITYCLASS CPlayerAnimator

CEntityProperty CPlayerAnimator_properties[] = {
 CEntityProperty(CEntityProperty::EPT_ENTITYPTR, NULL, (0x00000196<<8)+1, offsetof(CPlayerAnimator, m_penPlayer), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+5, offsetof(CPlayerAnimator, m_bReference), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+6, offsetof(CPlayerAnimator, m_fLastActionTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000196<<8)+7, offsetof(CPlayerAnimator, m_iContent), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+8, offsetof(CPlayerAnimator, m_bWaitJumpAnim), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+9, offsetof(CPlayerAnimator, m_bCrouch), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+10, offsetof(CPlayerAnimator, m_iCrouchDownWait), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+11, offsetof(CPlayerAnimator, m_iRiseUpWait), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+12, offsetof(CPlayerAnimator, m_bChangeWeapon), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+13, offsetof(CPlayerAnimator, m_bSwim), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000196<<8)+14, offsetof(CPlayerAnimator, m_iFlare), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000196<<8)+15, offsetof(CPlayerAnimator, m_iSecondFlare), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+16, offsetof(CPlayerAnimator, m_bAttacking), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+19, offsetof(CPlayerAnimator, m_tmAttackingDue), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+17, offsetof(CPlayerAnimator, m_tmFlareAdded), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+18, offsetof(CPlayerAnimator, m_bDisableAnimating), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT3D, NULL, (0x00000196<<8)+20, offsetof(CPlayerAnimator, m_vLastPlayerPosition), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+21, offsetof(CPlayerAnimator, m_fEyesYLastOffset), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+22, offsetof(CPlayerAnimator, m_fEyesYOffset), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+23, offsetof(CPlayerAnimator, m_fEyesYSpeed), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+24, offsetof(CPlayerAnimator, m_bMdl), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+27, offsetof(CPlayerAnimator, m_fWeaponYLastOffset), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+28, offsetof(CPlayerAnimator, m_fWeaponYOffset), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+29, offsetof(CPlayerAnimator, m_fWeaponYSpeed), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+30, offsetof(CPlayerAnimator, m_bMoving), "", 0, 0, EPROPF_NETSEND ),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+31, offsetof(CPlayerAnimator, m_fMoveLastBanking), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+32, offsetof(CPlayerAnimator, m_fMoveBanking), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+33, offsetof(CPlayerAnimator, m_iMovingSide), "", 0, 0, EPROPF_NETSEND ),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+34, offsetof(CPlayerAnimator, m_bSidestepBankingLeft), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000196<<8)+35, offsetof(CPlayerAnimator, m_bSidestepBankingRight), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+36, offsetof(CPlayerAnimator, m_fSidestepLastBanking), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+37, offsetof(CPlayerAnimator, m_fSidestepBanking), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000196<<8)+38, offsetof(CPlayerAnimator, m_iWeaponLast), "", 0, 0, EPROPF_NETSEND ),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+39, offsetof(CPlayerAnimator, m_fBodyAnimTime), "", 0, 0, EPROPF_NETSEND ),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000196<<8)+40, offsetof(CPlayerAnimator, m_iPlayerID), "", 0, 0, EPROPF_NETSEND ),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+41, offsetof(CPlayerAnimator, m_fAttack1AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+42, offsetof(CPlayerAnimator, m_fAttack2AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+43, offsetof(CPlayerAnimator, m_fSkill1AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+44, offsetof(CPlayerAnimator, m_fSkill2AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+45, offsetof(CPlayerAnimator, m_fAttack3AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+46, offsetof(CPlayerAnimator, m_fAttack4AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+47, offsetof(CPlayerAnimator, m_fExtAttack1AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+48, offsetof(CPlayerAnimator, m_fExtAttack2AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+49, offsetof(CPlayerAnimator, m_fExtAttack3AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000196<<8)+50, offsetof(CPlayerAnimator, m_fExtAttack4AnimTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_ENTITYPTR, NULL, (0x00000196<<8)+255, offsetof(CPlayerAnimator, m_penPrediction), "", 0, 0, 0),
};
#define CPlayerAnimator_propertiesct ARRAYCOUNT(CPlayerAnimator_properties)

CEntityComponent CPlayerAnimator_components[] = {
#define CLASS_REMINDER ((0x00000196<<8)+1)
 CEntityComponent(ECT_CLASS, CLASS_REMINDER, 0, "EFNM" "Classes\\Reminder.ecl"),
#define TEX_REFL_BWRIPLES01 ((0x00000196<<8)+200)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_BWRIPLES01, 0, "EFNM" "Data\\Models\\ReflectionTextures\\BWRiples01.tex"),
#define TEX_REFL_BWRIPLES02 ((0x00000196<<8)+201)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_BWRIPLES02, 0, "EFNM" "Data\\Models\\ReflectionTextures\\BWRiples02.tex"),
#define TEX_REFL_LIGHTMETAL01 ((0x00000196<<8)+202)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_LIGHTMETAL01, 0, "EFNM" "Data\\Models\\ReflectionTextures\\LightMetal01.tex"),
#define TEX_REFL_LIGHTBLUEMETAL01 ((0x00000196<<8)+203)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_LIGHTBLUEMETAL01, 0, "EFNM" "Data\\Models\\ReflectionTextures\\LightBlueMetal01.tex"),
#define TEX_REFL_DARKMETAL ((0x00000196<<8)+204)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_DARKMETAL, 0, "EFNM" "Data\\Models\\ReflectionTextures\\DarkMetal.tex"),
#define TEX_REFL_PURPLE01 ((0x00000196<<8)+205)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_PURPLE01, 0, "EFNM" "Data\\Models\\ReflectionTextures\\Purple01.tex"),
#define TEX_REFL_GOLD01 ((0x00000196<<8)+206)
 CEntityComponent(ECT_TEXTURE, TEX_REFL_GOLD01, 0, "EFNM" "Data\\Models\\ReflectionTextures\\Gold01.tex"),
#define TEX_SPEC_WEAK ((0x00000196<<8)+210)
 CEntityComponent(ECT_TEXTURE, TEX_SPEC_WEAK, 0, "EFNM" "Data\\Models\\SpecularTextures\\Weak.tex"),
#define TEX_SPEC_MEDIUM ((0x00000196<<8)+211)
 CEntityComponent(ECT_TEXTURE, TEX_SPEC_MEDIUM, 0, "EFNM" "Data\\Models\\SpecularTextures\\Medium.tex"),
#define TEX_SPEC_STRONG ((0x00000196<<8)+212)
 CEntityComponent(ECT_TEXTURE, TEX_SPEC_STRONG, 0, "EFNM" "Data\\Models\\SpecularTextures\\Strong.tex"),
#define MODEL_FLARE02 ((0x00000196<<8)+250)
 CEntityComponent(ECT_MODEL, MODEL_FLARE02, 0, "EFNM" "Data\\Models\\Effects\\Weapons\\Flare02\\Flare.mdl"),
#define TEXTURE_FLARE02 ((0x00000196<<8)+251)
 CEntityComponent(ECT_TEXTURE, TEXTURE_FLARE02, 0, "EFNM" "Data\\Models\\Effects\\Weapons\\Flare02\\Flare.tex"),
};
#define CPlayerAnimator_componentsct ARRAYCOUNT(CPlayerAnimator_components)

CEventHandlerEntry CPlayerAnimator_handlers[] = {
 {1, -1, CEntity::pEventHandler(&CPlayerAnimator::
#line 2591 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/PlayerAnimator.es"
Main),DEBUGSTRING("CPlayerAnimator::Main")},
 {0x01960001, -1, CEntity::pEventHandler(&CPlayerAnimator::H0x01960001_Main_01), DEBUGSTRING("CPlayerAnimator::H0x01960001_Main_01")},
 {0x01960002, -1, CEntity::pEventHandler(&CPlayerAnimator::H0x01960002_Main_02), DEBUGSTRING("CPlayerAnimator::H0x01960002_Main_02")},
 {0x01960003, -1, CEntity::pEventHandler(&CPlayerAnimator::
#line 2618 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/PlayerAnimator.es"
ReminderAction),DEBUGSTRING("CPlayerAnimator::ReminderAction")},
};
#define CPlayerAnimator_handlersct ARRAYCOUNT(CPlayerAnimator_handlers)

CEntity *CPlayerAnimator_New(void) { return new CPlayerAnimator; };
void CPlayerAnimator_OnInitClass(void) {};
void CPlayerAnimator_OnEndClass(void) {};
void CPlayerAnimator_OnPrecache(CDLLEntityClass *pdec, INDEX iUser) {};
void CPlayerAnimator_OnWorldEnd(CWorld *pwo) {};
void CPlayerAnimator_OnWorldInit(CWorld *pwo) {};
void CPlayerAnimator_OnWorldTick(CWorld *pwo) {};
void CPlayerAnimator_OnWorldRender(CWorld *pwo) {};
ENTITY_CLASSDEFINITION(CPlayerAnimator, CRationalEntity, "Player Animator", "", 0x00000196);
DECLARE_CTFILENAME(_fnmCPlayerAnimator_tbn, "");
