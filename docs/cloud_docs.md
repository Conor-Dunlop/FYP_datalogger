# Documentation for cloud software

### Webserver/API
Webserver code can be found in `software/dataloggerAPI`, uses C# .net as this has the best documentation

This runs as a web app/app service on Azure which can be accessed at https://dataloggerapi.azurewebsites.net (this won't actually load an html page but can post/get to that address). 

I used visual studio with the web development toolkit to develop the API, instructions on how to setup a project can be found here: https://learn.microsoft.com/en-us/azure/app-service/quickstart-dotnetcore?tabs=net80&pivots=development-environment-vs

To see data formats and do testing can go to https://dataloggerapi.azurewebsites.net/swagger/index.html, formats can also be found in `software/data_formats`

### Database
The database runs as a T-SQL microsoft server on Azure, accessed at https://ucdatalogger.database.windows.net, 1433

I used vscode's [MSSQL extensions](https://marketplace.visualstudio.com/items?itemName=MEngRBatinov.mssql-extensions-starter-pack) to access the database and run queries but should be able to use any sql software, or just use Azure's query editor.

The database schema can be found in `software/data_formats`, haven't yet updated to future schema as didn't want to break anything before inspection and handover.

### Emulator

An emulator to communicate with the webserver can be found in `software/emulator`, simply run `client.py`, feel free to change which tests are run in `main()` (test_logans doesn't work).

### Grafana/visualisation

https://ucdatalogger.grafana.net/

Can only have 3 users on free tier so supervisor (Barry Wu) will need to kick people out to allow new users.

Simply edit a dashboard's queries to change what data is shown. Automatically queries the Azure database.

Sending data back to the server isn't very well done, currently just using buttons with query setup in it's settings, should be possible to change to html input fields and send http request to webAPI rather than directly to database.

### Future work

Doesn't yet send data back to datalogger automatically (datalogger currently needs to request), should be able to do this through the webAPI or by performing a function on update to the database.

Implement future formats, should be able to use queries in `software/data_formats` (haven't been fully tested) but will need to update webAPI, visualiser and datalogger code to work with new format.