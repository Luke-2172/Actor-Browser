#pragma once
// Fixed allowlist shared with the generated game bridge; no console evaluation.
struct ActorValueChoice { const char* label; const char* token; double low,high; };
static const ActorValueChoice actorValues[]={
 {"Health","Health",1,100000},{"Action points","ActionPoints",0,10000},
 {"Carry weight","CarryWeight",0,100000},{"Movement speed (%)","SpeedMult",10,500},
 {"Damage threshold","DamageThreshold",0,1000},{"Damage resistance","DamageResist",0,100},
 {"Strength","Strength",1,10},{"Perception","Perception",1,10},
 {"Endurance","Endurance",1,10},{"Charisma","Charisma",1,10},
 {"Intelligence","Intelligence",1,10},{"Agility","Agility",1,10},{"Luck","Luck",1,10},
 {"Barter","Barter",0,100},{"Energy weapons","EnergyWeapons",0,100},
 {"Explosives","Explosives",0,100},{"Guns","Guns",0,100},
 {"Lockpick","Lockpick",0,100},{"Medicine","Medicine",0,100},
 {"Melee weapons","MeleeWeapons",0,100},{"Repair","Repair",0,100},
 {"Science","Science",0,100},{"Sneak","Sneak",0,100},{"Speech","Speech",0,100},
 {"Survival","Survival",0,100},{"Unarmed","Unarmed",0,100},
 {"Aggression","Aggression",0,3},{"Confidence","Confidence",0,4},
 {"Radiation resistance","RadResist",0,100},{"Poison resistance","PoisonResist",0,100}
};
static constexpr int ActorValueCount=sizeof(actorValues)/sizeof(actorValues[0]);
static bool actorValueNumber(const std::string& input,double& value) {
 if(input.empty()||input.size()>12)return false;
 char* end=nullptr;value=strtod(input.c_str(),&end);
 return end!=input.c_str()&&!*end&&std::isfinite(value);
}

