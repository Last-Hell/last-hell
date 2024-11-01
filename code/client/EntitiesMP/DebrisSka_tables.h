/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

CEntityEvent *ESpawnDebrisSka_New(void) { return new ESpawnDebrisSka; };
CDLLEntityEvent DLLEvent_ESpawnDebrisSka = {
	0x02690000, &ESpawnDebrisSka_New
};
CDLLEntityEvent *CDebrisSka_events[] = {
	&DLLEvent_ESpawnDebrisSka,
};
#define CDebrisSka_eventsct ARRAYCOUNT(CDebrisSka_events)
#define ENTITYCLASS CDebrisSka

CEntityProperty CDebrisSka_properties[] = {
 CEntityProperty(CEntityProperty::EPT_ENUM, &DebrisParticlesType_enum, (0x00000269<<8)+1, offsetof(CDebrisSka, m_dptParticles), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000269<<8)+2, offsetof(CDebrisSka, m_iBodyType), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000269<<8)+3, offsetof(CDebrisSka, m_bFade), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000269<<8)+4, offsetof(CDebrisSka, m_fFadeStartTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000269<<8)+5, offsetof(CDebrisSka, m_fFadeTime), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT3D, NULL, (0x00000269<<8)+6, offsetof(CDebrisSka, m_fLastStainHitPoint), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_ENUM, &BasicEffectType_enum, (0x00000269<<8)+7, offsetof(CDebrisSka, m_betStain), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x00000269<<8)+8, offsetof(CDebrisSka, m_ctLeftStains), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000269<<8)+9, offsetof(CDebrisSka, m_tmStarted), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000269<<8)+10, offsetof(CDebrisSka, m_fStretch), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_ANGLE3D, NULL, (0x00000269<<8)+11, offsetof(CDebrisSka, m_aShadingDirection), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000269<<8)+12, offsetof(CDebrisSka, m_bCustomShading), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_COLOR, NULL, (0x00000269<<8)+13, offsetof(CDebrisSka, m_colCustomAmbient), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_COLOR, NULL, (0x00000269<<8)+14, offsetof(CDebrisSka, m_colCustomDiffuse), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000269<<8)+15, offsetof(CDebrisSka, m_bImmaterialASAP), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_FLOAT, NULL, (0x00000269<<8)+16, offsetof(CDebrisSka, m_fDustStretch), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_BOOL, NULL, (0x00000269<<8)+17, offsetof(CDebrisSka, m_bTouchedGround), "", 0, 0, 0),
 CEntityProperty(CEntityProperty::EPT_ENTITYPTR, NULL, (0x00000269<<8)+18, offsetof(CDebrisSka, m_penFallFXPapa), "", 0, 0, 0),
};
#define CDebrisSka_propertiesct ARRAYCOUNT(CDebrisSka_properties)

CEntityComponent CDebrisSka_components[] = {
#define CLASS_BASIC_EFFECT ((0x00000269<<8)+1)
 CEntityComponent(ECT_CLASS, CLASS_BASIC_EFFECT, 0, "EFNM" "Classes\\BasicEffect.ecl"),
};
#define CDebrisSka_componentsct ARRAYCOUNT(CDebrisSka_components)

CEventHandlerEntry CDebrisSka_handlers[] = {
 {1, -1, CEntity::pEventHandler(&CDebrisSka::
#line 212 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DebrisSka.es"
Main),DEBUGSTRING("CDebrisSka::Main")},
 {0x02690001, -1, CEntity::pEventHandler(&CDebrisSka::H0x02690001_Main_01), DEBUGSTRING("CDebrisSka::H0x02690001_Main_01")},
 {0x02690002, -1, CEntity::pEventHandler(&CDebrisSka::H0x02690002_Main_02), DEBUGSTRING("CDebrisSka::H0x02690002_Main_02")},
 {0x02690003, -1, CEntity::pEventHandler(&CDebrisSka::H0x02690003_Main_03), DEBUGSTRING("CDebrisSka::H0x02690003_Main_03")},
 {0x02690004, -1, CEntity::pEventHandler(&CDebrisSka::H0x02690004_Main_04), DEBUGSTRING("CDebrisSka::H0x02690004_Main_04")},
};
#define CDebrisSka_handlersct ARRAYCOUNT(CDebrisSka_handlers)

CEntity *CDebrisSka_New(void) { return new CDebrisSka; };
void CDebrisSka_OnInitClass(void) {};
void CDebrisSka_OnEndClass(void) {};
void CDebrisSka_OnPrecache(CDLLEntityClass *pdec, INDEX iUser) {};
void CDebrisSka_OnWorldEnd(CWorld *pwo) {};
void CDebrisSka_OnWorldInit(CWorld *pwo) {};
void CDebrisSka_OnWorldTick(CWorld *pwo) {};
void CDebrisSka_OnWorldRender(CWorld *pwo) {};
ENTITY_CLASSDEFINITION(CDebrisSka, CMovableModelEntity, "Debris", "", 0x00000269);
DECLARE_CTFILENAME(_fnmCDebrisSka_tbn, "");
