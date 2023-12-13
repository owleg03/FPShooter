#pragma once

#include "Teams.h"
#include "GenericTeamAgentInterface.h"
#include "ProjectileTeamId.generated.h"

USTRUCT()
struct FProjectileTeamId : public FGenericTeamId
{
	GENERATED_USTRUCT_BODY()

	FProjectileTeamId() : FGenericTeamId(ProjectilesTeam) {}
};
