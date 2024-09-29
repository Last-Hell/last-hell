/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#ifndef _DestroyableArchitecture_INCLUDED
#define _DestroyableArchitecture_INCLUDED 1
#include <EntitiesMP/Debris.h>
#include <EntitiesMP\GradientMarker.h>
#define EVENTCODE_EArchitectureDeath 0x006b0000
class DECL_DLL EArchitectureDeath : public CEntityEvent {
public:
	EArchitectureDeath();
	CEntityEvent *MakeCopy(void);
	BOOL CheckIDs(void);
	SLONG GetSizeOf(void);
};
DECL_DLL inline void ClearToDefault(EArchitectureDeath &e) { e = EArchitectureDeath(); } ;
extern "C" DECL_DLL CDLLEntityClass CDestroyableArchitecture_DLLClass;
class CDestroyableArchitecture : public CMovableBrushEntity {
public:
virtual const CTString &GetName(void) const { return m_strName; };
virtual BOOL IsTargetable(void) const { return TRUE; };
	DECL_DLL virtual void SetDefaultProperties(void);
	CTString m_strName;
	FLOAT m_fHealth;
	enum EffectorEffectType m_etType;
	FLOAT3D m_vDamageDir;
	FLOAT m_fStretch;
	CEntityPointer m_penGradient;
	COLOR m_colDebrises;
	INDEX m_ctDebrises;
	FLOAT m_fCandyEffect;
	FLOAT m_fCubeFactor;
	BOOL m_bBlowupByDamager;
	FLOAT m_fDustStretch;
   
#line 105 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
BOOL HandleEvent(const CEntityEvent & ee);
   
#line 118 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
void Precache(void);
   
#line 156 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
BOOL IsTargetValid(SLONG slPropertyOffset,CEntity * penTarget);
   
#line 172 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
const CTString & GetGradientName(INDEX iGradient);
   
#line 188 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
void UncacheShadowsForGradient(class CGradientMarker * penDiscard);
   
#line 198 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
BOOL GetGradient(INDEX iGradient,class CGradientParameters & fpGradient);
   
#line 211 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
void ReceiveDamage(CEntity * penInflictor,enum DamageType dmtType,
#line 212 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
FLOAT fDamageAmmount,const FLOAT3D & vHitPoint,const FLOAT3D & vDirection);
   
#line 240 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
void DestroyObelisk();
   
#line 307 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
void DestroyPylon();
   
#line 372 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
SLONG GetUsedMemory(void);
#define  STATE_CDestroyableArchitecture_Main 1
	BOOL 
#line 386 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/DestroyableArchitecture.es"
Main(const CEntityEvent &__eeInput);
	BOOL H0x006b0001_Main_01(const CEntityEvent &__eeInput);
	BOOL H0x006b0002_Main_02(const CEntityEvent &__eeInput);
};
#endif // _DestroyableArchitecture_INCLUDED