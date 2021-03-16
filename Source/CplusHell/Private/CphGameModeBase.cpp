// C plus Hell Learning Game, All Right Reserved.


#include "CphGameModeBase.h"


#include "EngineUtils.h"
#include "Components/CphRespawnComponent.h"
#include "Player/CphBaseCharacter.h"
#include "Player/CphPlayerController.h"
#include "Player/CphPlayerState.h"
#include "UI/CphGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogCphGameModeBase, All, All)

ACphGameModeBase::ACphGameModeBase()
{
    // Set defaults
    DefaultPawnClass = ACphBaseCharacter::StaticClass();
    PlayerControllerClass = ACphPlayerController::StaticClass();
    HUDClass = ACphGameHUD::StaticClass();
    PlayerStateClass = ACphPlayerState::StaticClass();
}

void ACphGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    StartRound();
}

UClass* ACphGameModeBase::GetDefaultPawnClassForController_Implementation(
    AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ACphGameModeBase::Killed(AController* SlayerController,
                              AController* VictimController) const
{
    ACphPlayerState* SlayerPlayerState = SlayerController
                                             ? Cast<ACphPlayerState>(
                                                 SlayerController->PlayerState)
                                             : nullptr;
    ACphPlayerState* VictimPlayerState = VictimController
                                             ? Cast<ACphPlayerState>(
                                                 VictimController->PlayerState)
                                             : nullptr;

    if (SlayerPlayerState)
    {
        SlayerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ACphGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

void ACphGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayerNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride =
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AAIController* CphAIController = GetWorld()->
            SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(CphAIController);
    }
}

void ACphGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundDuration;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this,
                                    &ACphGameModeBase::GameTimerUpdate, 1.0f,
                                    true);
}

void ACphGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogCphGameModeBase, Display, TEXT("Round %i time remaining %i"),
           CurrentRoundNum,
           RoundCountDown)

    // GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
    // I am sure timer reduces every second and is RoundCountDown integer

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (++CurrentRoundNum <= GameData.RoundsNum)
        {
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ACphGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It;
         ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ACphGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ACphGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It;
         ++It)
    {
        AController* Controller = It->Get();
        if (!Controller) continue;

        ACphPlayerState* PlayerState = Cast<ACphPlayerState>(
            Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ACphGameModeBase::DetermineColorByTeamID(const int32 TeamID)
{
    const int32 Index = TeamID - 1;
    if (Index < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[Index];
    }

    UE_LOG(LogCphGameModeBase, Warning,
           TEXT("There is no color for Team ID = %i. Set to default %s"),
           TeamID, *GameData.DefaultTeamColor.ToString())
    return GameData.DefaultTeamColor;
}

void ACphGameModeBase::SetPlayerColor(AController* PlayerController) const
{
    if (!PlayerController) return;

    ACphBaseCharacter* Character = Cast<ACphBaseCharacter>(
        PlayerController->GetPawn());
    if (!Character) return;

    ACphPlayerState* PlayerState = Cast<ACphPlayerState>(
        Character->GetPlayerState());
    if (!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ACphGameModeBase::LogPlayerInfo() const
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();
        if (!Controller) continue;

        ACphPlayerState* PlayerState = Cast<ACphPlayerState>(
            Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

// Calls respawn component than starts respawn timer
void ACphGameModeBase::StartRespawn(AController* Controller) const
{
    // Check if respawn timer should not start
    const bool RespawnAvailable = RoundCountDown > GameData.RespawnTime;
    if (!RespawnAvailable) return;

    UActorComponent* RespawnComponentCandidate = Controller->
        FindComponentByClass(UCphRespawnComponent::StaticClass());
    UCphRespawnComponent* RespawnComponent = Cast<UCphRespawnComponent>(
        RespawnComponentCandidate);
    if (!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

//
void ACphGameModeBase::GameOver()
{
    UE_LOG(LogCphGameModeBase, Display, TEXT("Game Over"))
    LogPlayerInfo();

    for (APawn* Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            // Pawn->TurnOff();
            // Pawn->DisableInput(nullptr);
            UE_LOG(LogCphGameModeBase, Display, TEXT("Turn off pawn: %s"),
                   *Pawn->GetName())
        }
    }
}
