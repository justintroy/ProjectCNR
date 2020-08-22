#include <YSI_Coding\y_hooks>

static carvid;

hook OnGameModeInit()
{
    new tmpobjid;

    carvid = CreateVehicle(411,-1723.502,391.392,6.911,223.482,2,0,-1,0);

    AddVehicleComponent(carvid, 1010);
    AddVehicleComponent(carvid, 1078);
    tmpobjid = CreateDynamicObject(18648,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid, carvid, 0.949, 0.000, -0.649, 0.000, 0.000, 0.000);
    tmpobjid = CreateDynamicObject(18648,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid, carvid, -0.910, 0.000, -0.600, 0.000, 0.000, 0.000);
    tmpobjid = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid, carvid, -0.007, 1.895, 0.031, -8.700, -179.399, 0.000);
    tmpobjid = CreateDynamicObject(11704,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid, carvid, -0.002, 2.959, -0.189, 0.000, 0.000, 179.300);
    return 1;
}

hook OnGameModeExit()
{
    DestroyVehicle(carvid);
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    if(vehicleid == carvid)
    { 
        AddVehicleComponent(carvid, 1010);
        AddVehicleComponent(carvid, 1078);
    } 
    return 1;
}