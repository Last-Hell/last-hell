/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

CDLLEntityEvent *CMessageHolder_events[] = {NULL};
#define CMessageHolder_eventsct 0
#define ENTITYCLASS CMessageHolder

CEntityProperty CMessageHolder_properties[] = {
 CEntityProperty(CEntityProperty::EPT_STRING, NULL, (0x000000e2<<8)+1, offsetof(CMessageHolder, m_strName), "Name", 'N', 0x7F0000FFUL, 0),
 CEntityProperty(CEntityProperty::EPT_INDEX, NULL, (0x000000e2<<8)+2, offsetof(CMessageHolder, m_iStringIndex), "String Index", 0, 0x7F0000FFUL, 0),
 CEntityProperty(CEntityProperty::EPT_STRING, NULL, (0x000000e2<<8)+3, offsetof(CMessageHolder, m_strRealString), "Real String", 0, 0x7F0000FFUL, 0),
};
#define CMessageHolder_propertiesct ARRAYCOUNT(CMessageHolder_properties)

CEntityComponent CMessageHolder_components[] = {
#define MODEL_MARKER ((0x000000e2<<8)+1)
 CEntityComponent(ECT_MODEL, MODEL_MARKER, 2, "EFNM" "Data\\Models\\Editor\\MessageHolder.mdl"),
#define TEXTURE_MARKER ((0x000000e2<<8)+2)
 CEntityComponent(ECT_TEXTURE, TEXTURE_MARKER, 2, "EFNM" "Data\\Models\\Editor\\MessageHolder.tex"),
};
#define CMessageHolder_componentsct ARRAYCOUNT(CMessageHolder_components)

CEventHandlerEntry CMessageHolder_handlers[] = {
 {1, -1, CEntity::pEventHandler(&CMessageHolder::
#line 46 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/MessageHolder.es"
Main),DEBUGSTRING("CMessageHolder::Main")},
 {0x00e20000, -1, CEntity::pEventHandler(&CMessageHolder::H0x00e20000_Main_01), DEBUGSTRING("CMessageHolder::H0x00e20000_Main_01")},
 {0x00e20001, -1, CEntity::pEventHandler(&CMessageHolder::H0x00e20001_Main_02), DEBUGSTRING("CMessageHolder::H0x00e20001_Main_02")},
 {0x00e20002, -1, CEntity::pEventHandler(&CMessageHolder::
#line 113 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/MessageHolder.es"
MainMessageType),DEBUGSTRING("CMessageHolder::MainMessageType")},
 {0x00e20003, -1, CEntity::pEventHandler(&CMessageHolder::H0x00e20003_MainMessageType_01), DEBUGSTRING("CMessageHolder::H0x00e20003_MainMessageType_01")},
 {0x00e20004, -1, CEntity::pEventHandler(&CMessageHolder::H0x00e20004_MainMessageType_02), DEBUGSTRING("CMessageHolder::H0x00e20004_MainMessageType_02")},
 {0x00e20005, -1, CEntity::pEventHandler(&CMessageHolder::H0x00e20005_MainMessageType_03), DEBUGSTRING("CMessageHolder::H0x00e20005_MainMessageType_03")},
 {0x00e20006, -1, CEntity::pEventHandler(&CMessageHolder::H0x00e20006_MainMessageType_04), DEBUGSTRING("CMessageHolder::H0x00e20006_MainMessageType_04")},
};
#define CMessageHolder_handlersct ARRAYCOUNT(CMessageHolder_handlers)

CEntity *CMessageHolder_New(void) { return new CMessageHolder; };
void CMessageHolder_OnInitClass(void) {};
void CMessageHolder_OnEndClass(void) {};
void CMessageHolder_OnPrecache(CDLLEntityClass *pdec, INDEX iUser) {};
void CMessageHolder_OnWorldEnd(CWorld *pwo) {};
void CMessageHolder_OnWorldInit(CWorld *pwo) {};
void CMessageHolder_OnWorldTick(CWorld *pwo) {};
void CMessageHolder_OnWorldRender(CWorld *pwo) {};
ENTITY_CLASSDEFINITION(CMessageHolder, CRationalEntity, "MessageHolder", "Thumbnails\\MessageHolder.tbn", 0x000000e2);
DECLARE_CTFILENAME(_fnmCMessageHolder_tbn, "Thumbnails\\MessageHolder.tbn");
