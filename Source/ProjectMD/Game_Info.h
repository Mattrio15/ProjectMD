#pragma once

#include "Engine.h"
#include "EngineMinimal.h"
#include "GameplayTagContainer.h"

#define Test(Text, ...) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT(Text), ##__VA_ARGS__))
#define Log(Text, ...) UE_LOG(LogTemp, Warning, TEXT(Text), ##__VA_ARGS__)
#define CHECK(Text) UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__ Text))

#define MyObject(Class, Name) CreateDefaultSubobject<Class>(TEXT(Name))
#define ObjectFinder(Class, Name, Path) static ConstructorHelpers::FObjectFinder<Class>Name(TEXT(Path))
#define ClassFinder(Class, Name, Path) static ContstructorHelpers::FClassFinder<Class>Name(TEXT(Path))