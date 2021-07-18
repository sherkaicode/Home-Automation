char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>


<head>
<meta charset="utf-8">
    <script>
        var connection = new WebSocket('ws://' + location.hostname + ':81/');
        var button_1_status = 0;
        var button_2_status = 0;
        var temp_data = 0;
        var hum_data = 0;
        var gas_data = 0;
        var pir_data = 0;
        var tempF_data = 0;

        connection.onmessage = function (event) {
            var full_data = event.data;
            console.log(full_data);
            var data = JSON.parse(full_data);

            temp_data = data.temp;
            hum_data = data.hum;
            gas_data = data.gas;
            pir_data = data.pir;
            tempF_data = data.far;


            if (data.pir == 1) {
                button_1_on();
                document.getElementById("pir_value").innerHTML = "Motion Detected";
                var x = document.getElementById("pir_color");
                x.style.backgroundColor = "red";
    
            } else {
                button_1_off();
                document.getElementById("pir_value").innerHTML = "No Motion";
                var x = document.getElementById("pir_color");
                x.style.backgroundColor = "blue";
      
            }
            if (data.gas > 900) {
                button_2_on();
            } else {
                button_2_off();
            }
            var Cel = String(temp_data).concat("°C");
            var Far = String(tempF_data).concat("°F");
            var Gas = String(gas_data).concat("ppm");
            var Hum = String(hum_data).concat("RH");

            document.getElementById("temp_meter").value = temp_data;
            document.getElementById("temp_value").innerHTML = Cel;  
            document.getElementById("hum_meter").value = hum_data;
            document.getElementById("hum_value").innerHTML = Hum;
            document.getElementById("gas_value").innerHTML = Gas;
            document.getElementById("tempF_value").innerHTML = Far;
        }
        
        function button_1_on() {
            button_1_status = 1;
            console.log("LED 1 is ON");
            send_data();
        }
        function button_1_off() {
            button_1_status = 0;
            console.log("LED 1 is OFF");
            send_data();
        }
        function button_2_on() {
            button_2_status = 1;
            console.log("LED 2 is ON");
            send_data();
        }
        function button_2_off() {
            button_2_status = 0;
            console.log("LED 2 is OFF");
            send_data();
        }
        function send_data() {
            var full_data = '{"LED1" :' + button_1_status + ',"BUZ":' + button_2_status + '}';
            connection.send(full_data);
        }
    </script>
    <style>
        table,
        th,
        td {
            border: 1px solid black;
        }
    </style>
</head>

<body>
    <font size="100%" face="Courier New">
        <table style="width:100%" style="height: 100%">
            <tr>
                <th colspan="3" style="width: auto;"> User Interface</th>
            </tr>
            <tr>
                <td style="width:33.33%;" id="t">Temperature </td>
                <td style="width:33.33%;" id="temp_value" style="display: inline-table;" align="center"> NaN </td> 
                <td style="width:auto;" id="tempF_value" style="display: inline-block;" align="center"> NaN </td>
               
            </tr>
            <tr>
                <th colspan="3"> <meter style="width: 100%;" value="2" min="0" max="100" id="temp_meter"> NaN </meter></th>
            </tr>
            <tr>
                <td style="width: auto;"> Humidity</td>
                <td colspan="2" align="center" style="width: auto;" id="hum_value"> NaN </td>
            </tr>
            <tr>
                <th colspan="3"> <meter style="width: 100%;" value="2" min="0" max="100" id="hum_meter"> </meter></th>
            </tr>
            <tr>
                <td> Air Quality</td>
                <td colspan="2" align="center" id="gas_value"> NaN  </td>
            </tr>
            <tr id="pir_color">
                <th colspan="3" id="pir_value"> Motion Sensor </th>
            </tr>
        </table>
    </font>
   

</body>

</html>
)=====";
