/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#line 2 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"

#include "StdH.h"
extern INDEX ent_bReportBrokenChains;

#include <Trigger.h>
#include <Trigger_tables.h>
void CTrigger::SetDefaultProperties(void) {
	m_strName = "Trigger";
	m_bRaidObject = FALSE ;
	m_RaidEventType = 0;
	m_penTarget1 = NULL;
	m_penTarget2 = NULL;
	m_penTarget3 = NULL;
	m_penTarget4 = NULL;
	m_penTarget5 = NULL;
	m_penTarget6 = NULL;
	m_penTarget7 = NULL;
	m_penTarget8 = NULL;
	m_penTarget9 = NULL;
	m_penTarget10 = NULL;
	m_eetEvent1 = EET_TRIGGER ;
	m_eetEvent2 = EET_TRIGGER ;
	m_eetEvent3 = EET_TRIGGER ;
	m_eetEvent4 = EET_TRIGGER ;
	m_eetEvent5 = EET_TRIGGER ;
	m_eetEvent6 = EET_TRIGGER ;
	m_eetEvent7 = EET_TRIGGER ;
	m_eetEvent8 = EET_TRIGGER ;
	m_eetEvent9 = EET_TRIGGER ;
	m_eetEvent10 = EET_TRIGGER ;
	m_strMessage = "";
	m_fMessageTime = 3.0f;
	m_mssMessageSound = MSS_NONE ;
	m_fWaitTime = 0.0f;
	m_bAutoStart = FALSE ;
	m_iCount = 1;
	m_bUseCount = FALSE ;
	m_bReuseCount = FALSE ;
	m_bTellCount = FALSE ;
	m_bActive = TRUE ;
	m_fSendRange = 1.0f;
	m_eetRange = EET_IGNORE ;
	m_iCountTmp = 0;
	m_penCaused = NULL;
	m_ctMaxTrigs = -1;
	CRationalEntity::SetDefaultProperties();
}

#line 67 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
CEntity * CTrigger::GetTarget(void)const 
#line 68 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
{
#line 69 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return m_penTarget1 ;
#line 70 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}

#line 74 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SLONG CTrigger::GetUsedMemory(void) 
#line 75 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
{
#line 77 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SLONG  slUsedMemory  = sizeof  (CTrigger ) - sizeof  (CRationalEntity ) + CRationalEntity  :: GetUsedMemory  ();
#line 79 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
slUsedMemory  += m_strMessage  . Length  ();
#line 80 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
slUsedMemory  += m_strName  . Length  ();
#line 81 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
slUsedMemory  += 1 * sizeof  (CSoundObject);
#line 82 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return slUsedMemory ;
#line 83 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
BOOL CTrigger::
#line 88 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Main(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CTrigger_Main
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CTrigger::Main expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 89 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
InitAsEditorModel  ();
#line 90 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetPhysicsFlags  (EPF_MODEL_IMMATERIAL );
#line 91 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetCollisionFlags  (ECF_IMMATERIAL );
#line 93 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetFlagOff  (ENF_PROPSCHANGED );
#line 94 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetFlagOn  (ENF_NONETCONNECT );
#line 95 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetFlagOn  (ENF_MARKDESTROY );
#line 98 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetModel  (MODEL_MARKER );
#line 99 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetModelMainTexture  (TEXTURE_MARKER );
#line 101 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_fSendRange  = ClampDn  (m_fSendRange  , 0.01f);
#line 104 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetTimerAfter(0.1f);
Jump(STATE_CURRENT, 0x00cd0000, FALSE, EBegin());return TRUE;}BOOL CTrigger::H0x00cd0000_Main_01(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0000
switch(__eeInput.ee_slEvent) {case EVENTCODE_EBegin: return TRUE;case EVENTCODE_ETimer: Jump(STATE_CURRENT,0x00cd0001, FALSE, EInternal()); return TRUE;default: return FALSE; }}BOOL CTrigger::H0x00cd0001_Main_02(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0001
;
#line 107 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_bActive ){
#line 108 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Jump(STATE_CURRENT, STATE_CTrigger_Active, TRUE, EVoid());return TRUE;
#line 109 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}else {
#line 110 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Jump(STATE_CURRENT, STATE_CTrigger_Inactive, TRUE, EVoid());return TRUE;
#line 111 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 114 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Destroy  ();
#line 116 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Return(STATE_CURRENT,EVoid());
#line 116 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return TRUE; ASSERT(FALSE); return TRUE;};BOOL CTrigger::
#line 119 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendEventToTargets(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CTrigger_SendEventToTargets
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CTrigger::SendEventToTargets expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 121 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(!(m_fWaitTime  > 0.0f)){ Jump(STATE_CURRENT,0x00cd0005, FALSE, EInternal());return TRUE;}
#line 122 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetTimerAfter(m_fWaitTime );
Jump(STATE_CURRENT, 0x00cd0003, FALSE, EBegin());return TRUE;}BOOL CTrigger::H0x00cd0003_SendEventToTargets_01(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0003
switch(__eeInput.ee_slEvent){case(EVENTCODE_EBegin):{const EBegin&e= (EBegin&)__eeInput;
return TRUE;}ASSERT(FALSE);break;case(EVENTCODE_ETimer):{const ETimer&e= (ETimer&)__eeInput;
UnsetTimer();Jump(STATE_CURRENT,0x00cd0004, FALSE, EInternal());return TRUE;}ASSERT(FALSE);break;case(EVENTCODE_EDeactivate):{const EDeactivate&e= (EDeactivate&)__eeInput;
return FALSE;}ASSERT(FALSE);break;default:{return TRUE;}ASSERT(FALSE);break;
#line 127 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}return TRUE;}BOOL CTrigger::H0x00cd0004_SendEventToTargets_02(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0004
Jump(STATE_CURRENT,0x00cd0005, FALSE, EInternal());return TRUE;}BOOL CTrigger::H0x00cd0005_SendEventToTargets_03(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0005

#line 131 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget1  , m_eetEvent1  , m_penCaused );
#line 132 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget2  , m_eetEvent2  , m_penCaused );
#line 133 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget3  , m_eetEvent3  , m_penCaused );
#line 134 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget4  , m_eetEvent4  , m_penCaused );
#line 135 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget5  , m_eetEvent5  , m_penCaused );
#line 136 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget6  , m_eetEvent6  , m_penCaused );
#line 137 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget7  , m_eetEvent7  , m_penCaused );
#line 138 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget8  , m_eetEvent8  , m_penCaused );
#line 139 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget9  , m_eetEvent9  , m_penCaused );
#line 140 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (m_penTarget10  , m_eetEvent10  , m_penCaused );
#line 143 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_eetRange  != EET_IGNORE ){
#line 145 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendInRange  (this  , m_eetRange  , FLOATaabbox3D (GetPlacement  () . pl_PositionVector  , m_fSendRange ));
#line 146 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 175 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_ctMaxTrigs  > 0)
#line 176 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
{
#line 177 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetFlagOff  (ENF_PROPSCHANGED );
#line 179 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_ctMaxTrigs  -= 1;
#line 181 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_ctMaxTrigs  <= 0)
#line 182 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
{
#line 184 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Destroy  ();
#line 185 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 186 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 187 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Return(STATE_CURRENT,EVoid());
#line 187 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return TRUE; ASSERT(FALSE); return TRUE;};BOOL CTrigger::
#line 190 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Active(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CTrigger_Active
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CTrigger::Active expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 191 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
ASSERT  (m_bActive );
#line 193 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_iCountTmp  = m_iCount ;
#line 196 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetTimerAt(THINKTIME_NEVER);
Jump(STATE_CURRENT, 0x00cd0007, FALSE, EBegin());return TRUE;}BOOL CTrigger::H0x00cd0007_Active_01(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0007
switch(__eeInput.ee_slEvent){case(EVENTCODE_EBegin):{const EBegin&e= (EBegin&)__eeInput;

#line 199 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_bAutoStart ){
#line 200 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Call(STATE_CURRENT, STATE_CTrigger_SendEventToTargets, TRUE, EVoid());return TRUE;
#line 201 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 202 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return TRUE;
#line 203 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}ASSERT(FALSE);break;case(EVENTCODE_EStart):{const EStart&eStart= (EStart&)__eeInput;

#line 206 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SendToTarget  (this  , EET_TRIGGER  , eStart  . penCaused );
#line 207 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return TRUE;
#line 208 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}ASSERT(FALSE);break;case(EVENTCODE_ETrigger):{const ETrigger&eTrigger= (ETrigger&)__eeInput;

#line 211 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetFlagOff  (ENF_PROPSCHANGED );
#line 212 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_penCaused  = eTrigger  . penCaused ;
#line 214 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_bUseCount ){
#line 216 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_iCountTmp  > 0){
#line 218 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_iCountTmp  --;
#line 220 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_iCountTmp  < 1){
#line 221 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
if(m_bReuseCount ){
#line 222 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_iCountTmp  = m_iCount ;
#line 223 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}else {
#line 224 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_iCountTmp  = 0;
#line 225 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 226 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Call(STATE_CURRENT, STATE_CTrigger_SendEventToTargets, TRUE, EVoid());return TRUE;
#line 227 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}else if(m_bTellCount ){
#line 231 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 232 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 234 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}else {
#line 235 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Call(STATE_CURRENT, STATE_CTrigger_SendEventToTargets, TRUE, EVoid());return TRUE;
#line 236 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}
#line 237 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return TRUE;
#line 238 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}ASSERT(FALSE);break;case(EVENTCODE_EDeactivate):{const EDeactivate&e= (EDeactivate&)__eeInput;

#line 242 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_bActive  = FALSE ;
#line 243 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Jump(STATE_CURRENT, STATE_CTrigger_Inactive, TRUE, EVoid());return TRUE;
#line 244 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}ASSERT(FALSE);break;default: return FALSE; break;
#line 245 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}return TRUE;}BOOL CTrigger::H0x00cd0008_Active_02(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd0008
 ASSERT(FALSE); return TRUE;};BOOL CTrigger::
#line 247 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Inactive(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CTrigger_Inactive
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CTrigger::Inactive expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 248 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
ASSERT  (! m_bActive );
#line 249 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Jump(STATE_CURRENT,0x00cd000e, FALSE, EInternal());return TRUE;}BOOL CTrigger::H0x00cd000e_Inactive_05(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd000e
if(!(TRUE )){ Jump(STATE_CURRENT,0x00cd000f, FALSE, EInternal());return TRUE;}
#line 251 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetTimerAt(THINKTIME_NEVER);
Jump(STATE_CURRENT, 0x00cd000a, FALSE, EBegin());return TRUE;}BOOL CTrigger::H0x00cd000a_Inactive_01(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd000a
switch(__eeInput.ee_slEvent){case(EVENTCODE_EActivate):{const EActivate&e= (EActivate&)__eeInput;

#line 255 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
m_bActive  = TRUE ;
#line 256 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
Jump(STATE_CURRENT, STATE_CTrigger_Active, TRUE, EVoid());return TRUE;
#line 257 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}ASSERT(FALSE);break;default:{
#line 259 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
return TRUE;
#line 260 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}ASSERT(FALSE);break;
#line 261 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}return TRUE;}BOOL CTrigger::H0x00cd000b_Inactive_02(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd000b
;
#line 264 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
SetTimerAfter(0.1f);
Jump(STATE_CURRENT, 0x00cd000c, FALSE, EBegin());return TRUE;}BOOL CTrigger::H0x00cd000c_Inactive_03(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd000c
switch(__eeInput.ee_slEvent) {case EVENTCODE_EBegin: return TRUE;case EVENTCODE_ETimer: Jump(STATE_CURRENT,0x00cd000d, FALSE, EInternal()); return TRUE;default: return FALSE; }}BOOL CTrigger::H0x00cd000d_Inactive_04(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd000d
;Jump(STATE_CURRENT,0x00cd000e, FALSE, EInternal());return TRUE;
#line 265 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Trigger.es"
}BOOL CTrigger::H0x00cd000f_Inactive_06(const CEntityEvent &__eeInput) {
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00cd000f
 ASSERT(FALSE); return TRUE;};