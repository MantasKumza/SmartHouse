function ShowConfigDialog(zoneName) {
    el = document.getElementById("configDialog");
    document.getElementById("cofigZoneNameTitle").innerText = zoneName + ' configuration';
    document.getElementById("cofigZoneName").value = zoneName;
    jQuery.get('/?Command=GetZoneConfig&ZoneName=' + zoneName,
        function (data, status, xhr) {
        document.getElementById("timeOut").value = data.TimeOut;
        document.getElementById("offByTime").checked = data.OffByTime;
        if (data.TurnOffByTime) {
            document.getElementById("offHour").value = data.TurnOffHour;
            document.getElementById("offMin").value = data.TurnOffMin;
        }
        turnOffByTimeChange();
    });
    el.style.visibility = "visible";
}

function SaveConfig() {
    jQuery.get('/?Command=SaveZoneConfig' +
        '&ZoneName='+document.getElementById("cofigZoneName").value+
        '&TimeOut='+document.getElementById("timeOut").value+
        '&OffByTime=' + document.getElementById("offByTime").checked +
        '&OffHour='+document.getElementById("offHour").value+
        '&OffMin=' + document.getElementById("offMin").value
    );
    CloseConfigDialog();
}
function CloseConfigDialog() {
    document.getElementById("configDialog").style.visibility = "hidden";
}
function turnOffByTimeChange() {
    var turnOffByTime = document.getElementById("offByTime").checked
    if (!turnOffByTime) {
        document.getElementById("offHour").value = null;
        document.getElementById("offMin").value = null;
    }
    document.getElementById("offHour").disabled = !turnOffByTime;
    document.getElementById("offMin").disabled = !turnOffByTime;
}
function LoadDialogHtml()
{
    clearInterval(loadDialogHtmlInterval);
    jQuery.get('/cfgzone.htm', function (data, status, xhr)
    {
        document.getElementById("configDialog").innerHTML = data;
    });
}
var loadDialogHtmlInterval = setInterval(LoadDialogHtml, 1000);
