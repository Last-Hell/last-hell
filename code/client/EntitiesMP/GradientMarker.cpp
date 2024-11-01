/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#line 2 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"

#include "StdH.h"

#include <GradientMarker.h>
#include <GradientMarker_tables.h>
void CGradientMarker::SetDefaultProperties(void) {
	m_fHeight = -10.0f;
	m_bDarkLight = TRUE ;
	m_colColor0 = (C_GRAY  | CT_OPAQUE );
	m_colColor1 = (C_WHITE  | CT_OPAQUE );
	CMarker::SetDefaultProperties();
}

#line 27 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
const CTString & CGradientMarker::GetGradientName(void) 
#line 28 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
{
#line 29 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
return m_strName ;
#line 30 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}

#line 32 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
BOOL CGradientMarker::GetGradient(INDEX iGradient,class CGradientParameters & gpGradient) 
#line 33 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
{
#line 34 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
const FLOATmatrix3D & m  = GetRotationMatrix  ();
#line 35 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_vGradientDir  (1) = m  (1 , 2);
#line 36 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_vGradientDir  (2) = m  (2 , 2);
#line 37 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_vGradientDir  (3) = m  (3 , 2);
#line 38 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
FLOAT fPos  = gpGradient  . gp_vGradientDir  % GetPlacement  () . pl_PositionVector ;
#line 39 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_bDark  = m_bDarkLight ;
#line 40 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
if(m_fHeight  >= 0 && m_fHeight  < + 0.001f){m_fHeight  = + 0.001f;}
#line 41 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
if(m_fHeight  <= 0 && m_fHeight  > - 0.001f){m_fHeight  = - 0.001f;}
#line 42 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_fH0  = fPos ;
#line 43 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_fH1  = fPos  + m_fHeight ;
#line 44 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_col0  = m_colColor0 ;
#line 45 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
gpGradient  . gp_col1  = m_colColor1 ;
#line 46 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
return TRUE ;
#line 47 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}

#line 49 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
void CGradientMarker::UncacheShadowsForGradient(void) 
#line 50 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
{
#line 52 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
FOREACHINDYNAMICCONTAINER  (GetWorld  () -> wo_cenEntities  , CEntity  , iten ){
#line 54 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
if(IsOfClass  (& * iten  , & CWorldBase_DLLClass )){
#line 56 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
((CWorldBase  *) & * iten ) -> UncacheShadowsForGradient  (this );
#line 57 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}
#line 58 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}
#line 59 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}

#line 61 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
void CGradientMarker::SetPlacement_special(const CPlacement3D & plNew,const FLOATmatrix3D & mRotation,ULONG ulFlags) 
#line 62 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
{
#line 63 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
CEntity  :: SetPlacement_special  (plNew  , mRotation  , ulFlags );
#line 64 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
UncacheShadowsForGradient  ();
#line 65 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}

#line 67 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
void CGradientMarker::OnEnd(void) 
#line 68 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
{
#line 69 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
UncacheShadowsForGradient  ();
#line 70 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
CEntity  :: OnEnd  ();
#line 71 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}
BOOL CGradientMarker::
#line 75 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
Main(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CGradientMarker_Main
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CGradientMarker::Main expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 77 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
InitAsEditorModel  ();
#line 78 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
SetPhysicsFlags  (EPF_MODEL_IMMATERIAL );
#line 79 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
SetCollisionFlags  (ECF_IMMATERIAL );
#line 82 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
SetModel  (MODEL_MARKER );
#line 83 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
SetModelMainTexture  (TEXTURE_MARKER );
#line 86 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
if(m_strName  == "Marker"){
#line 87 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
m_strName  = "Gradient marker";
#line 88 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
}
#line 90 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
UncacheShadowsForGradient  ();
#line 91 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
Return(STATE_CURRENT,EVoid());
#line 91 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/GradientMarker.es"
return TRUE; ASSERT(FALSE); return TRUE;};