/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#line 2 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"

#include "StdH.h"
#include "EntitiesMP/Player.h"
#include <Engine/Interface/UIManager.h>
#include <Engine/Contents/function/SummonUI.h>
#include <Engine/SlaveInfo.h>
#include <Engine/Info/MyInfo.h>

#include <Teleport.h>
#include <Teleport_tables.h>
CEntityEvent *ETeleportActivate::MakeCopy(void) { 	CEntityEvent *peeCopy = new ETeleportActivate(*this); 	return peeCopy;}
SLONG ETeleportActivate::GetSizeOf(void) { 	return sizeof(*this);}
ETeleportActivate::ETeleportActivate() : CEntityEvent(EVENTCODE_ETeleportActivate) {
}
BOOL ETeleportActivate::CheckIDs(void) {	return TRUE ; }

CEntityEvent *ETeleportDeactivate::MakeCopy(void) { 	CEntityEvent *peeCopy = new ETeleportDeactivate(*this); 	return peeCopy;}
SLONG ETeleportDeactivate::GetSizeOf(void) { 	return sizeof(*this);}
ETeleportDeactivate::ETeleportDeactivate() : CEntityEvent(EVENTCODE_ETeleportDeactivate) {
}
BOOL ETeleportDeactivate::CheckIDs(void) {	return TRUE ; }

void CTeleport::SetDefaultProperties(void) {
	m_strName = "Teleport";
	m_strDescription = "";
	m_penTarget = NULL;
	m_fWidth = 2.0f;
	m_fHeight = 3.0f;
	m_bActive = TRUE ;
	m_bPlayersOnly = TRUE ;
	m_bForceStop = FALSE ;
	m_eTeleportType = TELEPORT_DEFAULT ;
	m_iTeleportIndex = -1;
	m_iTeleportExtIndex = 0;
	m_tmGoZoneSendedTime = 0.0f;
	m_penParticle = NULL;
	CRationalEntity::SetDefaultProperties();
}

#line 56 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
const CTString & CTeleport::GetDescription(void)const {
#line 57 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
((CTString &) m_strDescription ) . PrintF  ("-><none>");
#line 58 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_penTarget  != NULL ){
#line 59 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
((CTString &) m_strDescription ) . PrintF  ("->%s" , m_penTarget  -> GetName  ());
#line 60 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 61 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return m_strDescription ;
#line 62 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}

#line 64 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
void CTeleport::TeleportEntity(CEntity * pen,const CPlacement3D & pl) 
#line 65 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 67 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pen  -> Teleport  (pl );
#line 70 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ESpawnEffect  ese ;
#line 71 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ese  . colMuliplier  = C_WHITE  | CT_OPAQUE ;
#line 72 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ese  . betType  = BET_TELEPORT ;
#line 73 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ese  . vNormal  = FLOAT3D (0 , 1 , 0);
#line 74 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
FLOATaabbox3D box ;
#line 75 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pen  -> GetBoundingBox  (box );
#line 76 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
FLOAT fEntitySize  = box  . Size  () . MaxNorm  () * 2;
#line 77 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ese  . vStretch  = FLOAT3D (fEntitySize  , fEntitySize  , fEntitySize );
#line 78 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
CEntityPointer penEffect  = CreateEntity  (pl  , CLASS_BASIC_EFFECT );
#line 79 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
penEffect  -> Initialize  (ese );
#line 82 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
for(int  i  = UI_SUMMON_START ;i  <= UI_SUMMON_END ;++ i )
#line 83 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 84 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
CSummonUI  * pUISummon  = (CSummonUI  *) SE_Get_UIManagerPtr  () -> GetUI  (i );
#line 85 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(pUISummon  -> GetSummonEntity  ())
#line 86 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 87 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pUISummon  -> SetCommand  (CSlaveInfo  :: COMMAND_HOLD );
#line 88 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pUISummon  -> GetSummonEntity  () -> SetPlacement  (m_penTarget  -> GetPlacement  ());
#line 89 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pUISummon  -> GetSummonEntity  () -> FallDownToFloor  ();
#line 90 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 91 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 93 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ObjInfo  * pInfo  = ObjInfo  :: getSingleton  ();
#line 94 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
CPetTargetInfom  * pPetInfo  = pInfo  -> GetMyPetInfo  ();
#line 97 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(pPetInfo  -> bIsActive  && pPetInfo  -> pen_pEntity )
#line 98 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 99 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pPetInfo  -> pen_pEntity  -> SetPlacement  (m_penTarget  -> GetPlacement  ());
#line 100 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pPetInfo  -> pen_pEntity  -> FallDownToFloor  ();
#line 101 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 102 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}

#line 106 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SLONG CTeleport::GetUsedMemory(void) 
#line 107 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 109 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SLONG  slUsedMemory  = sizeof  (CTeleport ) - sizeof  (CRationalEntity ) + CRationalEntity  :: GetUsedMemory  ();
#line 111 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
slUsedMemory  += m_strName  . Length  ();
#line 112 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
slUsedMemory  += m_strDescription  . Length  ();
#line 113 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return slUsedMemory ;
#line 114 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
BOOL CTeleport::
#line 120 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
Main(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CTeleport_Main
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CTeleport::Main expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 122 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
InitAsEditorModel  ();
#line 123 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetPhysicsFlags  (EPF_MODEL_IMMATERIAL );
#line 124 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetCollisionFlags  (ECF_TOUCHMODEL );
#line 125 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetFlagOff  (ENF_PROPSCHANGED );
#line 126 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetFlagOn  (ENF_NONETCONNECT );
#line 127 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetFlagOn  (ENF_MARKDESTROY );
#line 130 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_fHeight  < m_fWidth )
#line 131 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 132 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_fHeight  = m_fWidth ;
#line 133 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 136 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
GetModelObject  () -> StretchModel  (FLOAT3D (m_fWidth  , m_fHeight  , m_fWidth ));
#line 137 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetModel  (MODEL_TELEPORT );
#line 138 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ModelChangeNotify  ();
#line 139 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetModelMainTexture  (TEXTURE_TELEPORT );
#line 141 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
Jump(STATE_CURRENT,0x00db0006, FALSE, EInternal());return TRUE;}BOOL CTeleport::H0x00db0006_Main_05(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00db0006
if(!(TRUE )){ Jump(STATE_CURRENT,0x00db0007, FALSE, EInternal());return TRUE;}
#line 143 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetTimerAt(THINKTIME_NEVER);
Jump(STATE_CURRENT, 0x00db0002, FALSE, EBegin());return TRUE;}BOOL CTeleport::H0x00db0002_Main_01(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00db0002
switch(__eeInput.ee_slEvent){case(EVENTCODE_EPass):
#line 145 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{const EPass&ePass= (EPass&)__eeInput;

#line 146 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_eTeleportType  == TELEPORT_DEFAULT )
#line 147 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 148 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_penTarget  != NULL  && m_bActive )
#line 149 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 150 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_bPlayersOnly  && ! IsOfClass  (ePass  . penOther  , & CPlayer_DLLClass )){
#line 151 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 152 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 153 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
TeleportEntity  (ePass  . penOther  , m_penTarget  -> GetPlacement  ());
#line 154 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_bForceStop  && (ePass  . penOther  -> GetPhysicsFlags  () & EPF_MOVABLE ))
#line 155 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 156 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
((CMovableEntity  *) & * ePass  . penOther ) -> ForceFullStop  ();
#line 157 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 158 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
UnsetTimer();Jump(STATE_CURRENT,0x00db0003, FALSE, EInternal());return TRUE;
#line 159 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 160 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 161 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 162 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
else 
#line 163 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_eTeleportType  == TELEPORT_NETWORK )
#line 164 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 165 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_bActive )
#line 166 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 171 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(! IsOfClass  (ePass  . penOther  , & CPlayer_DLLClass ))
#line 172 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 173 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 174 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 175 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ASSERT  (m_iTeleportIndex  != - 1 && "Invalid Teleport Index!");
#line 177 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
CPlayer  * pPlayer  = (CPlayer  *) CEntity  :: GetPlayerEntity  (0);
#line 178 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(pPlayer )
#line 179 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 180 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pPlayer  -> m_bRcvAtMsg  = FALSE ;
#line 181 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pPlayer  -> m_bLockMove  = TRUE ;
#line 182 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pPlayer  -> m_bReserveMove  = FALSE ;
#line 183 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
pPlayer  -> StopMove  ();
#line 184 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 186 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
FLOAT tmCurTime  = _pTimer  -> GetHighPrecisionTimer  () . GetMilliseconds  ();
#line 187 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(tmCurTime  - m_tmGoZoneSendedTime  > 1000)
#line 188 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 189 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_tmGoZoneSendedTime  = tmCurTime ;
#line 190 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
_pNetwork  -> SendWarpTeleport  (m_iTeleportIndex );
#line 191 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 192 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
UnsetTimer();Jump(STATE_CURRENT,0x00db0003, FALSE, EInternal());return TRUE;
#line 193 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 194 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 195 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 196 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
else 
#line 197 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 198 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_bActive )
#line 199 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 200 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(! IsOfClass  (ePass  . penOther  , & CPlayer_DLLClass ))
#line 201 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 202 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 203 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 204 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
ASSERT  (m_iTeleportIndex  != - 1 && "Invalid Teleport Index!");
#line 205 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
const int  iWorldNum  = m_iTeleportIndex ;
#line 206 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
const int  iExtraNum  = m_iTeleportExtIndex ;
#line 209 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
FLOAT tmCurTime  = _pTimer  -> GetHighPrecisionTimer  () . GetMilliseconds  ();
#line 210 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(tmCurTime  - m_tmGoZoneSendedTime  > 1000)
#line 211 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 212 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_tmGoZoneSendedTime  = tmCurTime ;
#line 213 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
_pNetwork  -> GoZone  (iWorldNum  , iExtraNum );
#line 214 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 215 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
UnsetTimer();Jump(STATE_CURRENT,0x00db0003, FALSE, EInternal());return TRUE;
#line 216 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 217 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 218 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 219 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}ASSERT(FALSE);break;case(EVENTCODE_EActivate):{const EActivate&e= (EActivate&)__eeInput;

#line 221 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetFlagOn  (ENF_PROPSCHANGED );
#line 222 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(_pNetwork  -> IsServer  ()){
#line 223 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SendEvent  (ETeleportActivate  () , TRUE );
#line 224 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 225 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 226 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}ASSERT(FALSE);break;case(EVENTCODE_ETeleportActivate):{const ETeleportActivate&e= (ETeleportActivate&)__eeInput;

#line 228 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_bActive  = TRUE ;
#line 230 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_penParticle  != NULL )
#line 231 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 232 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_penParticle  -> SendEvent  (EActivate  ());
#line 233 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 234 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 235 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}ASSERT(FALSE);break;case(EVENTCODE_EDeactivate):{const EDeactivate&e= (EDeactivate&)__eeInput;

#line 237 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetFlagOn  (ENF_PROPSCHANGED );
#line 238 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(_pNetwork  -> IsServer  ()){
#line 239 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SendEvent  (ETeleportDeactivate  () , TRUE );
#line 240 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 241 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 242 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}ASSERT(FALSE);break;case(EVENTCODE_ETeleportDeactivate):{const ETeleportDeactivate&e= (ETeleportDeactivate&)__eeInput;

#line 244 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_bActive  = FALSE ;
#line 246 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
if(m_penParticle  != NULL )
#line 247 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
{
#line 248 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
m_penParticle  -> SendEvent  (EDeactivate  ());
#line 249 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}
#line 250 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 251 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}ASSERT(FALSE);break;default:{
#line 253 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
return TRUE;
#line 254 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}ASSERT(FALSE);break;
#line 255 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}return TRUE;}BOOL CTeleport::H0x00db0003_Main_02(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00db0003
;
#line 258 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
SetTimerAfter(0.1f);
Jump(STATE_CURRENT, 0x00db0004, FALSE, EBegin());return TRUE;}BOOL CTeleport::H0x00db0004_Main_03(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x00db0004
switch(__eeInput.ee_slEvent) {case EVENTCODE_EBegin: return TRUE;case EVENTCODE_ETimer: Jump(STATE_CURRENT,0x00db0005, FALSE, EInternal()); return TRUE;default: return FALSE; }}BOOL CTeleport::H0x00db0005_Main_04(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00db0005
;Jump(STATE_CURRENT,0x00db0006, FALSE, EInternal());return TRUE;
#line 259 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/Teleport.es"
}BOOL CTeleport::H0x00db0007_Main_06(const CEntityEvent &__eeInput) {
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x00db0007
 ASSERT(FALSE); return TRUE;};