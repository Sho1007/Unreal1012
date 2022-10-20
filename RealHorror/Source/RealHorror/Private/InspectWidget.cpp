// Fill out your copyright notice in the Description page of Project Settings.


#include "InspectWidget.h"

void UInspectWidget::SetItemName(FText ItemName)
{
	TB_ItemName->SetText(ItemName);
}

void UInspectWidget::SetItemDiscription(FText ItemDiscription)
{
	TB_ItemDiscription->SetText(ItemDiscription);
}

void UInspectWidget::ScrollUp()
{
	if (ScrollOffset > 0.0f)
	{
		ScrollOffset -= 1.0f;
		if (ScrollOffset < 0.0f) ScrollOffset = 0.0f;
		SB_ItemDiscription->SetScrollOffset(ScrollOffset);
	}
}

void UInspectWidget::ScrollDown()
{
	if (ScrollOffset < SB_ItemDiscription->GetScrollOffsetOfEnd())
	{
		ScrollOffset += 1.0f;
		if (ScrollOffset > SB_ItemDiscription->GetScrollOffsetOfEnd()) ScrollOffset = SB_ItemDiscription->GetScrollOffsetOfEnd();
		SB_ItemDiscription->SetScrollOffset(ScrollOffset);
	}
}
