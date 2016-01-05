using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for Command
/// </summary>
public class Command
{
    public string Name;
    string _params;
    public Command()
    {

    }
    public bool parse(string line)
    {
        int index = line.IndexOf("Command");
        if (index >= 0)
        {
            _params = line;
            Name = get("Command");
            return true;
        }
        else
        {
            return false;
        }
    }
    public String get(String key)
    {

        String value = string.Empty;
        key += "=";
        int index = _params.IndexOf(key);

        if (index > -1)
        {
            int indexStart = index + key.Length;

            int indexEnd = _params.IndexOf("&", indexStart);
            if (indexEnd < 0)
                indexEnd = _params.IndexOf(" ", indexStart);
            if (indexEnd < 0)
                indexEnd = _params.Length;
            if (indexEnd == -1)
                indexEnd = _params.Length;
            value = _params.Substring(indexStart, indexEnd - indexStart);
        }

        return value;
    }
    public int getInt(String key)
    {
        try
        {
            return Convert.ToInt32(get(key));
        }
        catch
        {
            return 0;
        }
    }
    public long getLong(String key)
    {
        try
        {
            return Convert.ToInt64(get(key));
        }
        catch
        {
            return 0;
        }
    }
    public bool getBool(string key)
    {
        return get(key) == "true";
    }
    public void free()
    {
        Name = string.Empty;
        _params = string.Empty;
    }
}