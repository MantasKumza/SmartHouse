using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for SDCard
/// </summary>
public class SDCard
{
    string _rootDir;
	public SDCard(string rootDir)
	{
        _rootDir = rootDir;
	}
    public bool exists(string fileName)
    {
        return File.Exists(Path.Combine(_rootDir, fileName));
    }
    public string readAllFile(string fileName)
    {
        return File.ReadAllText(Path.Combine(_rootDir, fileName));
    }
}