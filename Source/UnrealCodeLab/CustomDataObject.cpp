#include "CustomDataObject.h"

UWorld* UCustomDataObject::GetWorld() const
{
	// If this is a CDO, then return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld()
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return nullptr;
	}

	UObject* outer = GetOuter();

	// Follow the outer chain to find a valid World
	while (outer)
	{
		UWorld* world = outer->GetWorld();

		if (world)
		{
			return world;
		}

		outer = outer->GetOuter();
	}

	UE_LOG(LogTemp, Warning, TEXT("Cannot find a valid World for %s"), *GetName());
	return nullptr;
}
