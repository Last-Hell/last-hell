/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#line 2 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"

#include "StdH.h"

#include <AreaMarker.h>
#include <AreaMarker_tables.h>
void CAreaMarker::SetDefaultProperties(void) {
	m_strName = "AreaMarker";
	m_strDescription = "";
	m_boxArea = FLOATaabbox3D(FLOAT3D (0 , 0 , 0) , FLOAT3D (10 , 10 , 10));
	CEntity::SetDefaultProperties();
}

#line 22 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
void CAreaMarker::GetAreaBox(FLOATaabbox3D & box) {
#line 23 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
box  = m_boxArea ;
#line 24 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
box  += GetPlacement  () . pl_PositionVector ;
#line 25 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
return ;
#line 26 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
}
BOOL CAreaMarker::
#line 29 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
Main(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CAreaMarker_Main
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CAreaMarker::Main expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 31 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
InitAsEditorModel  ();
#line 32 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
SetPhysicsFlags  (EPF_MODEL_IMMATERIAL );
#line 33 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
SetCollisionFlags  (ECF_IMMATERIAL );
#line 36 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
SetModel  (MODEL_AREAMARKER );
#line 37 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
SetModelMainTexture  (TEXTURE_AREAMARKER );
#line 39 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
Return(STATE_CURRENT,EVoid());
#line 39 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/AreaMarker.es"
return TRUE; ASSERT(FALSE); return TRUE;};