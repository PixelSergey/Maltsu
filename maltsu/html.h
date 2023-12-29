#include <Arduino.h>

const char html_index[] PROGMEM = R"=(
<!DOCTYPE html>
<html>

<body>
    <h1>Colour picker</h1>
    <form action="/colour" onsubmit="javascript:convertColour()">
        <input type="color" value="#c900ab" id="colourpicker">
        <input type="number" value="0" id="colour" name="colour" hidden>
        <input type="submit" value="Set colour">
    </form>
    <script>
        function convertColour(){
            let val = document.getElementById("colourpicker").value;
            document.getElementById("colour").value = parseInt(val.slice(1), 16);
        }
    </script>
</body>

</html>
)=";