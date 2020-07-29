// Fill out your copyright notice in the Description page of Project Settings.


#include "bttASK_ClearValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UbttASK_ClearValue::UbttASK_ClearValue() 
{
    NodeName = TEXT("Clear Blackboard Value");
}
EBTNodeResult::Type UbttASK_ClearValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
