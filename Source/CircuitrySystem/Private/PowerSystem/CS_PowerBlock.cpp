// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "PowerSystem/CS_PowerBlock.h"

#include "Components/CS_AttachPoint.h"

ACS_PowerBlock::ACS_PowerBlock()
{	
	AttachPoint_1 = CreateDefaultSubobject<UCS_AttachPoint>("AttachPoint_1");
	AttachPoint_1->SetupAttachment(BaseMesh);

	AttachPoint_2 = CreateDefaultSubobject<UCS_AttachPoint>("AttachPoint_2");
	AttachPoint_2->SetupAttachment(BaseMesh);

	AttachPoint_3 = CreateDefaultSubobject<UCS_AttachPoint>("AttachPoint_3");
	AttachPoint_3->SetupAttachment(BaseMesh);

	AttachPoint_4 = CreateDefaultSubobject<UCS_AttachPoint>("AttachPoint_4");
	AttachPoint_4->SetupAttachment(BaseMesh);
}

void ACS_PowerBlock::BeginPlay()
{
	Super::BeginPlay();

}
