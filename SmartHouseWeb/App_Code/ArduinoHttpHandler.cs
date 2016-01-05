using System;
using System.Collections.Generic;
using System.Web;

/// <summary>
/// Summary description for ArduinoHttpHandler
/// </summary>
public class ArduinoHttpHandler : IHttpHandler
{
    Command command = new Command();
    SDCard SD;
    public ArduinoHttpHandler()
    {
        SD = new SDCard(@"c:\Users\DELL\Documents\Arduino\SmartHouse\SmartHouseWeb\");
    }

    public bool IsReusable
    {
        get { return false; }
    }

    public void ProcessRequest(HttpContext context)
    {

        string _readString = context.Request.RawUrl;
        if (command.parse(_readString))
        {
            String response=string.Empty;
            if (outdoorLightControl.processCommand(command,ref response))
            {
                sendResponseAsJson(context.Response, response);
            }
            else if (timerContoler.processCommand(command,ref response))
            {
                sendResponseAsJson(context.Response, response);
            }
            command.free();
            command.free();
        }
        else
        {
            String fileName = isRequestedFile(_readString);
            if (SD.exists(fileName))
            {
                sendFile(context.Response, fileName);
            }
        }

    }
    private void sendFile(HttpResponse response, string fileName)
    {
        /*
         * client.println("HTTP/1.1 200 OK");
			client.println("Content-Type: text/html");
			client.println("Connection: close");  // the connection will be closed after completion of the response
			client.println();
         */
        response.Clear();
        response.BufferOutput = true;
        response.StatusCode = 200; // HttpStatusCode.OK;
        response.Write(SD.readAllFile(fileName));
        response.ContentType = "text/html";
        response.End();
    }
    private void sendResponseAsJson(HttpResponse response, string responseString)
    {
        response.Clear();
        response.BufferOutput = true;
        response.StatusCode = 200; // HttpStatusCode.OK;
        response.Write(responseString);
        response.ContentType = "application/json; charset=utf-8";
        response.End();
    }
    
    private string isRequestedFile(string line)
    {
        string fileName = string.Empty;
        if (line == "/")
        {
            return "index.htm";
        }
        else
        {
            int indexEnd = line.IndexOf("?");
            if (indexEnd == -1)
                fileName = line;
            else
                fileName = line.Substring(0, indexEnd);
        }
        fileName = fileName.Trim('/');
        return fileName;
    }
}