var srcOff = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/off.png';
var srcOn = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/on.png';
var srcCfg = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/conf.png';
var srcMnl = 'https://raw.githubusercontent.com/kum63304/SmartHouse/master/SmartHouseWeb/mnl.png';

var isStateWaiting = false;

var zones = ["Terrace", "Summerhouse", "Fireplace", "DriveWay"];

function drawZones() {
    for (var i = 0; i < zones.length; i++) {
        drawRow(zones[i]);
    }
    var getZonesStateInterval = setInterval(GetZonesState, 1000);
}

function drawRow(rowData) {
    var row = jQuery("<tr />");
    jQuery("#zones").append(row);
    row.append(jQuery("<td><div class='padding20'>" + rowData + "<div></td>"));
    row.append(jQuery("<td><div id='Light-" + rowData + "' class='noBtn' onclick=\"SwitchLight('" + rowData + "')\">" +
        "<img  id='imgLight-" + rowData + "'' src='" + srcOff + "'></img><div></td>"));
    row.append(jQuery("<td><div class='btn' onclick=\"SwitchManualMode('" + rowData + "')\" ><img src='" + srcMnl + "'/></div></td>"));
    row.append(jQuery("<td><div class='btn' onclick=\"ShowConfigDialog('" + rowData + "')\" ><img  src='" + srcCfg + "'/></div></td>"));
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
        lightEl.src = srcOn;
    }
    else {
        lightEl.src = srcOff;
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
var cfgDialog = document.getElementById("configDialog");
var elOffByTime;
var elTimeOut;
var elOffHour;
var eloffMin;
function ShowConfigDialog(zoneName) {
    document.getElementById("cfgTitle").innerText = zoneName + ' configuration';
    document.getElementById("cofigZoneName").value = zoneName;
    jQuery.get('/?Command=GetZoneConfig&ZoneName=' + zoneName,
        function (data, status, xhr) {
            elTimeOut.value = data.TimeOut;
            elOffByTime.checked = data.OffByTime;
            if (data.OffByTime) {
                elOffHour.value = data.TurnOffHour;
                eloffMin.value = data.TurnOffMin;
            }
            turnOffByTimeChange();
        });
    cfgDialog.style.visibility = "visible";
}

function SaveConfig() {
    jQuery.get('/?Command=SaveZoneConfig' +
        '&ZoneName=' + document.getElementById("cofigZoneName").value +
        '&TimeOut=' + elTimeOut.value +
        '&OffByTime=' + elOffByTime.checked +
        '&OffHour=' + elOffHour.value +
        '&OffMin=' + eloffMin.value
    );
    CloseConfigDialog();
}
function CloseConfigDialog() {
    cfgDialog.style.visibility = "hidden";
}
function turnOffByTimeChange() {
    var turnOffByTime = elOffByTime.checked
    if (!turnOffByTime) {
        elOffHour.value = null;
        eloffMin.value = null;
    }
    else {
        elOffHour.value = 22;
        eloffMin.value = 0;
    }
    elOffHour.disabled = !turnOffByTime;
    eloffMin.disabled = !turnOffByTime;
}
function LoadDialogHtml() {
    clearInterval(loadDialogHtmlInterval);
    jQuery.get('/cfgzone.htm', function (data, status, xhr) {
        cfgDialog.innerHTML = data;
        elOffByTime = document.getElementById("offByTime");
        elTimeOut = document.getElementById("timeOut");
        elOffHour = document.getElementById("offHour");
        eloffMin = document.getElementById("offMin");
    });
}
var loadDialogHtmlInterval = setInterval(LoadDialogHtml, 1000);
