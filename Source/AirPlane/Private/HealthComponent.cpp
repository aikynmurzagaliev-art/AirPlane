// Kleith's Game

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	if(GetOwner()){
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeDamage);
	}
}


void UHealthComponent::HandleTakeDamage(
	AActor* DamagedActor, 
	float Damage, 
	const UDamageType* DamageType, 
	AController* Instigator, 
	AActor* DamageCauser)
{
	if(DamageSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetOwner()->GetActorLocation());
	}
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0.f) DamagedActor->Destroy();
}

void UHealthComponent::TickComponent(
	float DeltaTime, 
	ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

