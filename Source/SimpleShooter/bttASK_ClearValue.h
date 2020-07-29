// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "bttASK_ClearValue.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UbttASK_ClearValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UbttASK_ClearValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

};
