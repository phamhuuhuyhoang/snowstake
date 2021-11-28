
// Root webpage to enable people to change API data
static const char rootHtml[] PROGMEM = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF=8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <style type="text/css">
      input[type=text],
      select {
          width: 100%;
          padding: 12px 20px;
          margin: 8px 0;
          display: inline-block;
          border: 1px solid #ccc;
          border-radius: 4px;
          box-sizing: border-box;
      }

      input[type=submit] {
          width: 100%;
          background-color: #4CAF50;
          color: white;
          padding: 14px 20px;
          margin: 8px 0;
          border: none;
          border-radius: 4px;
          cursor: pointer;
      }
 
      input[type=submit]:hover {
          background-color: #45a049;
      }
 
      input[type=refresh] {
          background-color: #ffffff;
          float: right;
          clear: both;
          text-align: center;
          color: rgb(42, 48, 133);
          padding: 14px 20px;
          margin: 8px 0;
          border: none;
          border-radius: 4px;
          cursor: pointer;
      }
      
      input[type=refresh]:hover {
          background-color: #e7dfdf;
          color: rgb(26, 39, 226);
      }
    
      input:required {
          border-color: #800000;
          border-width: 3px;
      }
      
      input:required:invalid {
          border-color: #c00000;
      }
      
      div {
          border-radius: 5px;
          background-color: #f2f2f2;
          padding: 20px;
      }
    </style>
    <body>
        <h2>Snowstake API Settings</h2>
        <p>
            Please make sure you have gone to Weather Unlocked and setup you API Settings. Please use the Developer URL here: <a href="https://developer.weatherunlocked.com/" target="_blank"> WeatherUnlocked.com</a>. Fill in the fields below and submit to
            enable Snowstake. You may have to hit <b>REFRESH</b> to see changes.
        </p>
        </br>
        <div>
            <form action="/">
                <input type="refresh" class="button" value="Refresh" onClick="window.location.reload();"><br>
                <label for="apid">Developer Application ID: Required</label>
                <input type="text" id="apid" name="applicationid" placeholder="ABC12345" value="{{APPID}}" required>
                <label for="apkey">Application Key: Required</label>
                <input type="text" id="apkey" name="applicationkey" placeholder="619b9d50..." value="{{APPKEY}}" required>
                <label for="rsid">Resort ID: Required</label>
                <input type="text" id="rsid" name="resortid" placeholder="206004" value="{{RESORTID}}" required>
                <input type="submit" class="button" value="Submit" onClick="window.location.reload();">
                {{WRITESETTINGS}}
        </div>
    </body>
    </html>
)" ;
