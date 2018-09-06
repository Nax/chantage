#include <chantage/impl.h>

#define ABILITY_AI_DATA_OFFSET  0x08A754C0
#define ABILITY_DATA_OFFSET  0x08A75813
#define OLD_ABILITES_COUNT = 512

static struct {
    ExtraAbilityData* extraAbilityFields;
} newAbilityFields

static struct {
    size_t extraAbilityCapacity;
    size_t extraAbilityCount;
    AbilityData* extraAbilities;
    AbilityAIData* extraAbilitiesAI;

} newAbilityRegistry

void InitAbilities(void)
{
    extraAbilityCapacity = 8;
    totalAbilities = newAbilityRegistry.extraAbilityCount + 512;
    newAbilityFields.extraAbilityFields = malloc(sizeof(ExtraAbilityData)*totalAbilities);
    newAbilityRegistry.extraAbilities = malloc(sizeof(AbilityData) * newAbilityRegistry.extraAbilityCount);
    newAbilityRegistry.extraAbilitiesAI = malloc(sizeof(AbilityAIData) * newAbilityRegistry.extraAbilityCount);
}


AbilityData* GetAbilityData(u16 offset)
{
    if (offset < OLD_ABILITES_COUNT)
    {
        base = (AbilityData*)ABILITY_DATA_OFFSET;
    }
    else
    {
        base = newAbilityRegistry.extraAbilities;
    }
    return base + offset;
}


AbilityAIData* GetAbilityAIData(u16 offset)
{
    if (offset < OLD_ABILITES_COUNT)
    {
        base = (AbilityAIData*)ABILITY_AI_DATA_OFFSET;
    }
    else
    {
        base = newAbilityRegistry.extraAbilitiesAI;
    }
    return base + offset;
}

ExtraAbilityData* GetExtraAbilityData(u16 offset)
{
    base = newAbilityFields.extraAbilityFields;
    return base + offset
}

u16 CreateAbility(void)
{

    size_t newCapacity;
    AbilityData* newAbilityData;
    AbilityAIData* newAbilityAIData;
    ExtraAbilityData* newExtendedFields;
    u16 AbilityOffset;

    if (newAbilityRegistry.extraAbilityCapacity == newAbilityRegistry.extraAbilityCount)
    {
        newCapacity = newAbilityRegistry.extraAbilityCapacity;
        newCapacity += newCapacity / 2;

        newAbilityData = malloc(newCapacity * sizeof(AbilityData));
        memcpy(
            newAbilityData,
            newAbilityRegistry.extraAbilities,
            newAbilityRegistry.extraAbilityCount * sizeof(AbilityData));
        free(newAbilityRegistry.extraAbilities);

        newAbilityAIData = malloc(newCapacity * sizeof(AbilityAIData));
        memcpy(
            newAbilityAIData,
            newAbilityRegistry.extraAbilitiesAI,
            newAbilityRegistry.extraAbilityCount * sizeof(AbilityDataAI));
        free(newAbilityRegistry.extraAbilitiesAI);

        newExtendedFields = malloc((OLD_ABILITES_COUNT + newCapacity)*sizeof(ExtraAbilityData));
        memcpy(
            newExtendedFields,
            newAbilityFields.extraAbilityFields,
            (OLD_ABILITES_COUNT + newAbilityRegistry.extraAbilityCount)*sizeof(AbilityDataAI));
        free(newAbilityFields.extraAbilityFields);

        newAbilityRegistry.extraAbilities = newAbilityData;
        newAbilityRegistry.extraAbilitiesAI = newAbilityAIData;
        newAbilityFields.extraAbilityFields = newExtendedFields;
        newAbilityRegistry.extraAbilityCapacity = newCapacity;
    }
    memset(
        newAbilityRegistry.extraAbilities + newAbilityRegistry.extraAbilityCount,
        0,
        sizeof(AbilityData));
    memset(
        newAbilityRegistry.extraAbilitiesAI + newAbilityRegistry.extraAbilityCount,
        0,
        sizeof(AbilityDataAI));

    AbilityOffset = OLD_ABILITES_COUNT+ newAbilityRegistry.extraAbilityCount;
    newAbilityRegistry.extraAbilityCount++;

    return AbilityOffset;
}
