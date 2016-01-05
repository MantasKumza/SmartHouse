var srcOff = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/off.png';
var srcOn = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/on.png';
var srcCfg = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/conf.png';
var srcMnl = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/mnl.png';

var isStateWaiting = false;
var zones = ["Terrace", "Summerhouse", "Fireplace", "DriveWay"];

jQuery(document).ready(function () {
    for (var i = 0; i < zones.length; i++) {
        drawRow(zones[i]);
    }
    var getZonesStateInterval = setInterval(GetZonesState, 1000);
});

function drawRow(rowData) {
    var row = jQuery("<tr />");
    jQuery("#zones").append(row);
    row.append(jQuery("<td><div class='padding20'>" + rowData + "<div></td>"));
    row.append(jQuery("<td><div id='Light-" + rowData + "' class='noBtn' onclick=\"SwitchLight('" + rowData + "')\">" +
        "<img async id='imgLight-" + rowData + "'' src='" + srcOn + "'></img><div></td>"));
    row.append(jQuery("<td><div class='btn' onclick=\"ShowConfigDialog('" + rowData + "')\" ><img async src='\conf.png'/></div></td>"));
    row.append(jQuery("<td><div class='btn' onclick=\"SwitchManualMode('" + rowData + "')\" ><img async src='\mnl.png'/></div></td>"));
}
function GetZonesState() {
    if (!isStateWaiting) {
        isStateWaiting = true;
        jQuery.get('/?Command=GetZonesState', null,
            function (data, status, xhr) {
                isStateWaiting = false;
                for (var i = 0; i < data.length; i++) {
                    LightCallBack(data[i]);
                }

            }
        );
    }
}

function SwitchLight(zoneName) {
    jQuery.get('/?Command=SwitchLight&ZoneName=' + zoneName, LightCallBack);
}
function LightCallBack(data) {
    var lightEl = document.getElementById("imgLight-" + data.ZoneName);
    if (data.IsLightOn) {
        lightEl.src = '\on.png';
    }
    else {
        lightEl.src = '\off.png';
    }
}

function SwitchManualMode(zoneName) {
    jQuery.get('/?Command=SwitchManualMode&ZoneName=' + zoneName, ManualModeCallBack);
}
function ManualModeCallBack(data) {
    var zoneEl = document.getElementById("Light-" + data.ZoneName);
    if (data.IsManualMode) {
        zoneEl.className = 'btnNofill';
    }
    else {
        zoneEl.className = 'noBtn';
    }
}

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
        '&ZoneName=' + document.getElementById("cofigZoneName").value +
        '&TimeOut=' + document.getElementById("timeOut").value +
        '&OffByTime=' + document.getElementById("offByTime").checked +
        '&OffHour=' + document.getElementById("offHour").value +
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
function LoadDialogHtml() {
    clearInterval(loadDialogHtmlInterval);
    jQuery.get('/cfgzone.htm', function (data, status, xhr) {
        document.getElementById("configDialog").innerHTML = data;
    });
}
var loadDialogHtmlInterval = setInterval(LoadDialogHtml, 1000);
