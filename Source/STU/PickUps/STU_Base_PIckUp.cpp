#include "STU_Base_PIckUp.h"
#include "Components/SphereComponent.h"

ASTU_Base_PIckUp::ASTU_Base_PIckUp()
{
	Sphere_Collision = CreateDefaultSubobject<USphereComponent>("Sphere_Collision");
	Sphere_Collision->SetSphereRadius(68.0f);
	RootComponent = Sphere_Collision;
}

bool ASTU_Base_PIckUp::CouldBeTaken() const
{
	return Sphere_Collision->GetCollisionEnabled() != ECollisionEnabled::NoCollision;
}
