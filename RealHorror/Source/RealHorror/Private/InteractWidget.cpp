// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

void UInteractWidget::SetIsFocused(bool value)
{
	if (value)
	{
		I_Interact->SetOpacity(0.0f);
		TB_Interact->SetOpacity(1.0f);
	}
	else
	{
		I_Interact->SetOpacity(1.0f);
		TB_Interact->SetOpacity(0.0f);
	}
}
