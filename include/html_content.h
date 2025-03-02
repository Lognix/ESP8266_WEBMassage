#ifndef HTML_CONTENT_H
#define HTML_CONTENT_H

const char* configPage = R"=====(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>WiFi SETUP</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                background-color: #222;
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
                margin: 0;
            }
            form {
                background-color: #fff;
                padding: 20px;
                border-radius: 8px;
                box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
                width: 300px;
                box-sizing: border-box;
            }
            h2 {
                text-align: center;
                color: #333;
                margin-bottom: 20px;
            }
            form input[type="text"],
            form input[type="password"] {
                width: 100%;
                padding: 10px;
                margin-bottom: 15px;
                border: 1px solid #ccc;
                border-radius: 4px;
                font-size: 16px;
                box-sizing: border-box;
            }
            form input[type="text"]::placeholder,
            form input[type="password"]::placeholder {
                color: #999;
            }
            form input[type="submit"] {
                width: 100%;
                padding: 10px;
                background-color:rgb(135, 76, 175);
                color: white;
                border: none;
                border-radius: 4px;
                font-size: 16px;
                cursor: pointer;
            }
            form input[type="submit"]:hover {
                background-color: rgb(122, 34, 180);
            }
        </style>
    </head>
    <body>
        <form action="/save" method="POST">
            <h2>Setup WiFi Connection</h2>
            <input type="text" id="ssid" name="ssid" placeholder="SSID" required>
            <input type="password" id="pass" name="password" placeholder="Password" required>
            <input type="submit" value="Save">
        </form>
    </body>
    </html>
    )=====";
    
    
    const char* mainPage = R"======(
        <!DOCTYPE html>
    <html lang="ru">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Массажное кресло</title>
        <style>
            body {
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
                background-color: #222;
                margin: 0;
            }
            .chair-container {
                position: relative;
                width: 300px;
            }
            .chair-image {
                width: 100%;
                display: block;
            }
            .button {
                position: absolute;
                background-color: rgba(255, 0, 0, 0.7);
                border: none;
                color: white;
                padding: 8px;
                border-radius: 50%;
                cursor: pointer;
                transition: 0.3s;
            }
            .active { background-color: rgb(135, 76, 175); } 
            .back-oben { top: 23.5%; left: 38%; transform: translate(-50%, -50%); }
            .seat { top: 59%; left: 51%; transform: translate(-50%, -50%); }
            .back-unter { top: 41%; left: 35%; }
             </style>
    </head>
    <body>
    
        <div class="chair-container">
            <img src="https://raw.githubusercontent.com/Lognix/ESP8266_WEBMassage/main/Presets/stuhl.png" alt="Кресло" class="chair-image">
            <button class="button back-oben" onclick="sendPostRequest('/btn1', this)">⬤</button>
            <button class="button seat horisontal" onclick="sendPostRequest('/btn2', this)">⬤</button>
            <button class="button back-unter" onclick="sendPostRequest('/btn3', this)">⬤</button>
        </div>
        <script>
        function sendPostRequest(endpoint, button) {
          fetch(endpoint, { method: 'POST' })
            .then(response => response.text())
            .then(data => {
              if (data === '1') {
                button.classList.add('active');
              } else if (data === '0') {
                button.classList.remove('active');
              }
            });
        }
      </script>
    </body>
    </html>
      )======";

#endif