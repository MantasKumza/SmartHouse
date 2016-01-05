using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for Zone
/// </summary>
public class Zone
{
    public ZoneConf Config=new ZoneConf();
    public string Name
    {
        get;
        private set;
    }
    public bool IsLightOn { get; set; }
	public Zone(string name)
	{
        Name = name;
	}
}
public class ZoneConf
{
	public bool IsManualMode = false;
    public bool OffByTime = false;
    public int OffHour = 0;
    public int OffMin = 0;
    public long TimeOut = 7;
};