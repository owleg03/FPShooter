#pragma once

#include "Teams.h"
#include "GenericTeamAgentInterface.h"
#include "EnemyTeamId.generated.h"

USTRUCT()
struct FEnemyTeamId : public FGenericTeamId
{
	GENERATED_USTRUCT_BODY()

	FEnemyTeamId() : FGenericTeamId(EnemysTeam) {}
};
