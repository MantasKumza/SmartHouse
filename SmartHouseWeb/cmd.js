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

function SwitchLight(zoneName) 
{
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


var getZonesStateInterval = setInterval(GetZonesState, 1000);