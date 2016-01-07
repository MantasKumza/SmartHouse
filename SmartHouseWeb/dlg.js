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

