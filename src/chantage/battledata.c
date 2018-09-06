#include <chantage/impl.h>

#define UNIT_COUNT = 16
#defene battleDataArrayAddress = 0x85a3530

static struct {
    u8 newByteCount;
    ExtendedBattleData* extraBattleDataBytes;
} newBattleDataBytes;

static struct {
    NewBattleData* battleDataArray;
} BattleDataRegistry;

void InitNewFlags(void){
    newBattelDataBytes.newByteCount = 2;
    newUnitFlagArraySize = malloc(UNIT_COUNT*(sizeof(ExtendedBattleData)));
    newBattlelDataBytes.extraBattleDataBytes = malloc(newUnitFlagArraySize);

    DataPointerStructSize = malloc(UNIT_COUNT*(sizeof(NewBattleData)))
    for (int i = 0; i <= UNIT_COUNT, i++){
        NewBattleData.battleDataArray[i] = buildMergedData(i)
    }

}

NewBattleData buildMergedData(unit_offset){

    NewBattleData mergedData;
    mergedData.battleData = (BattleData*)battleDataArrayAddress + unit_offset;
    mergedData.extendedBattleData = newBattelDataBytes.extraBattleDataBytes + unit_offset;

    return NewBattleData
}

NewBattleData* getMergedData(unit_offset){
    base = BattleDataRegistry.battleDataArray;
    return base + unit_offset
}
