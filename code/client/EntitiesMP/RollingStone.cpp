/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#line 2 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"

#include "StdH.h"

#include <RollingStone.h>
#include <RollingStone_tables.h>
void CRollingStone::SetDefaultProperties(void) {
	m_fBounce = 0.5f;
	m_fHealth = 400.0f;
	m_fDamage = 1000.0f;
	m_bFixedDamage = FALSE ;
	m_fStretch = 1.0f;
	m_fDeceleration = 0.9f;
	m_fStartSpeed = 50.0f;
	m_vStartDir = ANGLE3D(0 , 0 , 0);
	m_penDeathTarget = NULL;
	m_soBounce0.SetOwner(this);
	m_soBounce0.Stop(FALSE);
	m_soBounce1.SetOwner(this);
	m_soBounce1.Stop(FALSE);
	m_soBounce2.SetOwner(this);
	m_soBounce2.Stop(FALSE);
	m_soBounce3.SetOwner(this);
	m_soBounce3.Stop(FALSE);
	m_soBounce4.SetOwner(this);
	m_soBounce4.Stop(FALSE);
	m_iNextChannel = 0;
	m_soRoll.SetOwner(this);
	m_soRoll.Stop(FALSE);
	m_bRollPlaying = FALSE ;
	m_qA = FLOATquat3D(0 , 1 , 0 , 0);
	m_qALast = FLOATquat3D(0 , 1 , 0 , 0);
	m_fASpeed = 0.0f;
	m_vR = FLOAT3D(0 , 0 , 1);
	CMovableModelEntity::SetDefaultProperties();
}

#line 53 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::Precache(void) 
#line 54 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 55 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PrecacheClass  (CLASS_DEBRIS );
#line 56 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PrecacheModel  (MODEL_STONE );
#line 57 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PrecacheTexture  (TEXTURE_STONE );
#line 58 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PrecacheSound  (SOUND_BOUNCE );
#line 59 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PrecacheSound  (SOUND_ROLL );
#line 60 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}

#line 61 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::PostMoving() {
#line 62 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
CMovableModelEntity  :: PostMoving  ();
#line 65 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(en_penReference  != NULL ){
#line 67 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AdjustSpeeds  (en_vReferencePlane );
#line 69 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}else {
#line 71 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 74 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_qALast  = m_qA ;
#line 76 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATquat3D qRot ;
#line 77 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
qRot  . FromAxisAngle  (m_vR  , m_fASpeed  * _pTimer  -> TickQuantum  * PI  / 180);
#line 78 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATmatrix3D mRot ;
#line 79 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
qRot  . ToMatrix  (mRot );
#line 80 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_qA  = qRot  * m_qA ;
#line 81 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(en_ulFlags  & ENF_INRENDERING ){
#line 82 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_qALast  = m_qA ;
#line 83 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 84 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}

#line 87 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::AdjustMipFactor(FLOAT & fMipFactor) 
#line 88 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 89 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
fMipFactor  = 0;
#line 91 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATquat3D qA ;
#line 92 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
qA  = Slerp  (_pTimer  -> GetLerpFactor  () , m_qALast  , m_qA );
#line 94 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATmatrix3D mA ;
#line 95 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
qA  . ToMatrix  (mA );
#line 96 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
ANGLE3D vA ;
#line 97 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
DecomposeRotationMatrixNoSnap  (vA  , mA );
#line 99 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
CAttachmentModelObject  * amo  = GetModelObject  () -> GetAttachmentModel  (0);
#line 100 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
amo  -> amo_plRelative  . pl_OrientationAngle  = vA ;
#line 101 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}

#line 103 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::AdjustSpeedOnOneAxis(FLOAT & fTraNow,FLOAT & aRotNow,BOOL bRolling) 
#line 104 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 111 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fR  = 4.0f * m_fStretch ;
#line 113 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fTraNew  = (2 * aRotNow  * fR  + 5 * fTraNow ) / 7;
#line 114 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT aRotNew  = fTraNew  / fR ;
#line 116 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
fTraNow  = fTraNew ;
#line 117 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
aRotNow  = aRotNew ;
#line 118 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}

#line 121 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::AdjustSpeeds(const FLOAT3D & vPlane) 
#line 122 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 124 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(en_vCurrentTranslationAbsolute  . Length  () < 1.0f && m_fASpeed  < 1.0f){
#line 126 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_vCurrentTranslationAbsolute  = FLOAT3D (0 , 0 , 0);
#line 127 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_fASpeed  = 0.0f;
#line 128 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
RollSound  (0.0f);
#line 129 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
return ;
#line 130 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 133 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vTranslationNormal ;
#line 134 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vTranslationParallel ;
#line 135 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
GetParallelAndNormalComponents  (en_vCurrentTranslationAbsolute  , vPlane  , vTranslationNormal  , vTranslationParallel );
#line 138 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
BOOL bRolling  = vTranslationNormal  . Length  () < 0.1f;
#line 140 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(bRolling ){
#line 142 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fSpeedTra  = vTranslationParallel  . Length  ();
#line 146 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
RollSound  (fSpeedTra );
#line 147 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}else {
#line 148 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
RollSound  (0);
#line 149 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 155 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vRotFromRot  = m_vR ;
#line 156 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vTraFromRot  = vPlane  * vRotFromRot ;
#line 157 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
vTraFromRot  . Normalize  ();
#line 159 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fTraFromRot  = 0;
#line 160 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fRotFromRot  = m_fASpeed  * PI  / 180.0f;
#line 163 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vTraFromTra  = vTranslationParallel ;
#line 164 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fTraFromTra  = vTraFromTra  . Length  ();
#line 165 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vRotFromTra  = FLOAT3D (1 , 0 , 0);
#line 166 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fRotFromTra  = 0;
#line 167 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(fTraFromTra  > 0.001f){
#line 168 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
vTraFromTra  /= fTraFromTra ;
#line 169 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
vRotFromTra  = vTraFromTra  * vPlane ;
#line 170 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
vRotFromTra  . Normalize  ();
#line 171 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 174 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(Abs  (fRotFromRot ) > 0.01f){
#line 176 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AdjustSpeedOnOneAxis  (fTraFromRot  , fRotFromRot  , bRolling );
#line 177 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 179 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(Abs  (fTraFromTra ) > 0.01f){
#line 181 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AdjustSpeedOnOneAxis  (fTraFromTra  , fRotFromTra  , bRolling );
#line 182 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 185 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATquat3D qTra ;
#line 186 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
qTra  . FromAxisAngle  (vRotFromTra  , fRotFromTra );
#line 187 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATquat3D qRot ;
#line 188 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
qRot  . FromAxisAngle  (vRotFromRot  , fRotFromRot );
#line 189 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATquat3D q  = qRot  * qTra ;
#line 190 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D vSpeed  = vTraFromTra  * fTraFromTra  + vTraFromRot  * fTraFromRot ;
#line 193 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_vCurrentTranslationAbsolute  = vTranslationNormal  + vSpeed ;
#line 194 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
q  . ToAxisAngle  (m_vR  , m_fASpeed );
#line 195 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_fASpeed  *= 180 / PI ;
#line 196 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}

#line 201 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::BounceSound(FLOAT fSpeed) {
#line 202 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fHitStrength  = fSpeed  * fSpeed ;
#line 204 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fVolume  = fHitStrength  / 20.0f;
#line 205 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
fVolume  = Clamp  (fVolume  , 0.0f , 1.0f);
#line 206 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fPitch  = Lerp  (0.2f , 1.0f , Clamp  (fHitStrength  / 100 , 0.0f , 1.0f));
#line 207 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(fVolume  < 0.1f){
#line 208 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
return ;
#line 209 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 210 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
CSoundObject & so  = (& m_soBounce0 ) [ m_iNextChannel  ];
#line 211 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_iNextChannel  = (m_iNextChannel  + 1) % 5;
#line 212 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
so  . Set3DParameters  (200.0f * m_fStretch  , 100.0f * m_fStretch  , fVolume  , fPitch );
#line 213 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PlaySound  (so  , SOUND_BOUNCE  , SOF_3D );
#line 214 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}

#line 216 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
void CRollingStone::RollSound(FLOAT fSpeed) 
#line 217 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 218 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fHitStrength  = fSpeed  * fSpeed  * m_fStretch  * m_fStretch  * m_fStretch ;
#line 220 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fVolume  = fHitStrength  / 20.0f;
#line 221 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
fVolume  = Clamp  (fVolume  , 0.0f , 1.0f);
#line 222 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fPitch  = Lerp  (0.2f , 1.0f , Clamp  (fHitStrength  / 100 , 0.0f , 1.0f));
#line 223 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(fVolume  < 0.1f){
#line 224 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(m_bRollPlaying ){
#line 225 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_soRoll  . Stop  ();
#line 226 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_bRollPlaying  = FALSE ;
#line 227 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 228 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
return ;
#line 229 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 230 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_soRoll  . Set3DParameters  (200.0f * m_fStretch  , 100.0f * m_fStretch  , fVolume  , fPitch );
#line 232 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(! m_bRollPlaying ){
#line 233 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
PlaySound  (m_soRoll  , SOUND_ROLL  , SOF_3D  | SOF_LOOP );
#line 234 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_bRollPlaying  = TRUE ;
#line 235 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 236 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
BOOL CRollingStone::
#line 240 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
Main(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CRollingStone_Main
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CRollingStone::Main expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 243 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
InitAsModel  ();
#line 244 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetPhysicsFlags  (EPF_ONBLOCK_BOUNCE  | EPF_PUSHABLE  | EPF_MOVABLE  | EPF_TRANSLATEDBYGRAVITY );
#line 245 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetCollisionFlags  (ECF_MODEL );
#line 246 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetModel  (MODEL_ROLLINGSTONE );
#line 247 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetModelMainTexture  (TEXTURE_ROLLINGSTONE );
#line 248 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AddAttachmentToModel  (this  , * GetModelObject  () , 0 , MODEL_STONESPHERE  , TEXTURE_ROLLINGSTONE  , 0 , 0 , TEXTURE_DETAIL );
#line 250 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
GetModelObject  () -> StretchModel  (FLOAT3D (m_fStretch  , m_fStretch  , m_fStretch ));
#line 251 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
ModelChangeNotify  ();
#line 253 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_fBounceDampNormal  = m_fBounce ;
#line 254 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_fBounceDampParallel  = m_fBounce ;
#line 255 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_fAcceleration  = en_fDeceleration  = m_fDeceleration ;
#line 256 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_fCollisionSpeedLimit  = 45.0f;
#line 257 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
en_fCollisionDamageFactor  = 10.0f;
#line 259 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetPlacement  (CPlacement3D (GetPlacement  () . pl_PositionVector  , ANGLE3D (0 , 0 , 0)));
#line 260 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_qA  = FLOATquat3D (0 , 1 , 0 , 0);
#line 261 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
m_qALast  = FLOATquat3D (0 , 1 , 0 , 0);
#line 263 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetTimerAfter(0.1f);
Jump(STATE_CURRENT, 0x025c0000, FALSE, EBegin());return TRUE;}BOOL CRollingStone::H0x025c0000_Main_01(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x025c0000
switch(__eeInput.ee_slEvent) {case EVENTCODE_EBegin: return TRUE;case EVENTCODE_ETimer: Jump(STATE_CURRENT,0x025c0001, FALSE, EInternal()); return TRUE;default: return FALSE; }}BOOL CRollingStone::H0x025c0001_Main_02(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x025c0001
;
#line 265 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetHealth  (m_fHealth );
#line 266 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AddToMovers  ();
#line 268 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SetTimerAt(THINKTIME_NEVER);
Jump(STATE_CURRENT, 0x025c0002, FALSE, EBegin());return TRUE;}BOOL CRollingStone::H0x025c0002_Main_03(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT 0x025c0002
switch(__eeInput.ee_slEvent){case(EVENTCODE_ETrigger):{const ETrigger&e= (ETrigger&)__eeInput;

#line 270 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D v ;
#line 271 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AnglesToDirectionVector  (m_vStartDir  , v );
#line 272 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
GiveImpulseTranslationAbsolute  (v  * m_fStartSpeed );
#line 274 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
return TRUE;
#line 275 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}ASSERT(FALSE);break;case(EVENTCODE_ETouch):
#line 277 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{const ETouch&eTouch= (ETouch&)__eeInput;

#line 281 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(! m_bFixedDamage )
#line 282 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 283 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fDamageFactor  = en_vCurrentTranslationAbsolute  . Length  () / 10.0f;
#line 284 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fAppliedDamage  = fDamageFactor  * m_fDamage ;
#line 286 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
InflictDirectDamage  (eTouch  . penOther  , this  , DMT_BOMB  , fAppliedDamage  , 
#line 287 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
eTouch  . penOther  -> GetPlacement  () . pl_PositionVector  , eTouch  . plCollision );
#line 288 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 289 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
else 
#line 290 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 291 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(en_vCurrentTranslationAbsolute  . Length  () != 0.0f)
#line 292 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 294 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
InflictDirectDamage  (eTouch  . penOther  , this  , DMT_BOMB  , m_fDamage  , 
#line 295 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
eTouch  . penOther  -> GetPlacement  () . pl_PositionVector  , eTouch  . plCollision );
#line 296 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 297 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 300 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
AdjustSpeeds  (eTouch  . plCollision );
#line 303 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(eTouch  . penOther  -> GetRenderType  () & RT_BRUSH )
#line 304 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 305 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
BounceSound  (((FLOAT3D &) eTouch  . plCollision ) % en_vCurrentTranslationAbsolute );
#line 307 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fImpactSpeed  = en_vCurrentTranslationAbsolute  % (- (FLOAT3D &) eTouch  . plCollision );
#line 310 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
if(fImpactSpeed  > 1000)
#line 311 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
{
#line 313 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
ReceiveDamage  (eTouch  . penOther  , DMT_IMPACT  , m_fHealth  * 2.0f , 
#line 314 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D (0 , 0 , 0) , FLOAT3D (0 , 0 , 0));
#line 315 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 316 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 317 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
return TRUE;
#line 318 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}ASSERT(FALSE);break;case(EVENTCODE_EDeath):{const EDeath&eDeath= (EDeath&)__eeInput;

#line 320 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
SendToTarget  (m_penDeathTarget  , EET_TRIGGER  , eDeath  . eLastDamage  . penInflictor );
#line 322 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOATaabbox3D box ;
#line 323 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
GetBoundingBox  (box );
#line 324 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT fEntitySize  = box  . Size  () . MaxNorm  ();
#line 326 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
Debris_Begin  (EIBT_ROCK  , DPT_NONE  , BET_NONE  , fEntitySize  , FLOAT3D (1.0f , 2.0f , 3.0f) , FLOAT3D (0 , 0 , 0) , 1.0f , 0.0f);
#line 327 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
for(INDEX iDebris  = 0;iDebris  < 12;iDebris  ++){
#line 328 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
Debris_Spawn  (this  , this  , MODEL_STONE  , TEXTURE_STONE  , 0 , 0 , 0 , IRnd  () % 4 , 0.15f , 
#line 329 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
FLOAT3D (FRnd  () * 0.8f + 0.1f , FRnd  () * 0.8f + 0.1f , FRnd  () * 0.8f + 0.1f));
#line 330 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}
#line 331 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
Destroy  ();
#line 332 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
UnsetTimer();Jump(STATE_CURRENT,0x025c0003, FALSE, EInternal());return TRUE;
#line 333 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}ASSERT(FALSE);break;default: return FALSE; break;
#line 334 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
}return TRUE;}BOOL CRollingStone::H0x025c0003_Main_04(const CEntityEvent &__eeInput){
ASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);
#undef STATE_CURRENT
#define STATE_CURRENT 0x025c0003

#line 337 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
Destroy  ();
#line 339 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
Return(STATE_CURRENT,EVoid());
#line 339 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/RollingStone.es"
return TRUE; ASSERT(FALSE); return TRUE;};