#pragma once

#include "Teams.h"
#include "GenericTeamAgentInterface.h"
#include "EnemyTeamId.generated.h"

USTRUCT()
struct FProjectileTeam : public FGenericTeamId
{
	GENERATED_USTRUCT_BODY()

	FProjectileTeam() : FGenericTeamId(ProjectilesTeam) {}
};
