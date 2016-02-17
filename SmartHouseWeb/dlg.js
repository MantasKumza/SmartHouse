var cfgDialog = document.getElementById("configDialog");
var elOffByTime = document.getElementById("offByTime");
var elTimeOut = document.getElementById("timeOut");
var elOffHour = document.getElementById("offHour");
var eloffMin = document.getElementById("offMin");
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


