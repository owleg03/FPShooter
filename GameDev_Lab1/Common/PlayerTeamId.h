#pragma once

#include "Teams.h"
#include "GenericTeamAgentInterface.h"
#include "PlayerTeamId.generated.h"

USTRUCT()
struct FPlayerTeamId : public FGenericTeamId
{
	GENERATED_USTRUCT_BODY()

	FPlayerTeamId() : FGenericTeamId(PlayersTeam) {}
};
