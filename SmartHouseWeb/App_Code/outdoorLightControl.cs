using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for outdoorLightControl
/// </summary>
public static class outdoorLightControl
{
    static Zone[] _zones;
    static int _zonesCount;
    static outdoorLightControl()
    {
        _zones = new Zone[4];
        _zones[0] = new Zone("Terrace");
        _zones[1] = new Zone("Summerhouse");
        _zones[2] = new Zone("Fireplace");
        _zones[3] = new Zone("DriveWay");
        _zonesCount = _zones.Length;
    }
    public static string toString(bool value)
    {
        if (value)
            return "true";
        else
            return "false";
    }
    public static string toString(int value)
    {
       return value.ToString();
    }
    public static string toString(long value)
    {
        return value.ToString();
    }
    static Zone getZoneByName(String zoneName)
    {
        for (int i = 0; i < _zonesCount; i++)
        {
            if (_zones[i].Name == zoneName)
            {
                return _zones[i];
            }
        }
        return null;
    }
    public static bool processCommand(Command command, ref string response)
    {
        if (command.Name == "GetZoneConfig")
        {
            Zone zone = getZoneByName(command.get("ZoneName"));
            response = "{";
            response += "\"ZoneName\":\"" + zone.Name + "\",";
            response += "\"TimeOut\":\"" + toString(zone.Config.TimeOut) + "\",";
            response += "\"OffHour\":\"" + toString(zone.Config.OffHour) + "\",";
            response += "\"OffMin\":\"" + toString(zone.Config.OffMin) + "\",";
            response += "\"OffByTime\":" + toString(zone.Config.OffByTime);
            response += "}";
            return true;
        }
        else if (command.Name == "SaveZoneConfig")
        {
            Zone zone = getZoneByName(command.get("ZoneName"));
            zone.Config.OffByTime = command.getBool("OffByTime");
            zone.Config.OffHour = command.getInt("OffHour");
            zone.Config.OffMin = command.getInt("OffMin");
            zone.Config.TimeOut = command.getLong("TimeOut");
            return true;
        }
        else if (command.Name == "GetZonesState")
        {
            response = "[";
            for (int i = 0; i < _zonesCount; i++)
            {
                response += "{";
                response += "\"ZoneName\":\"" + _zones[i].Name + "\",";
                response += "\"IsLightOn\":" + toString(_zones[i].IsLightOn) + ",";
                response += "\"IsManualMode\":" + toString(_zones[i].Config.IsManualMode);
                response += "}";
                if (i != _zonesCount - 1)
                    response += ",";
            }
            response += "]";
            return true;
        }
        else if (command.Name == "SwitchManualMode")
        {

            Zone zone = getZoneByName(command.get("ZoneName"));
            zone.Config.IsManualMode = !zone.Config.IsManualMode;
            response = "{";
            response += "\"ZoneName\":\"" + zone.Name + "\",";
            response += "\"IsManualMode\":" + toString(zone.Config.IsManualMode);
            response += "}";
            return true;
        }
        else if (command.Name == "SwitchLight")
        {
            Zone zone = getZoneByName(command.get("ZoneName"));
            if (zone.Config.IsManualMode)
                zone.IsLightOn = !zone.IsLightOn;
            response = "{";
            response += "\"ZoneName\":\"" + zone.Name + "\",";
            response += "\"IsLightOn\":" + toString(zone.IsLightOn);
            response += "}";
            return true;
        }
        return false;
    }

}