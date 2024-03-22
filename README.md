First of all you need SQL Server 2022 instance on your computer.
It should listen on default port 1433
Next you should create login "ProjectApplication" with password "HardPassword"
Open sql/BuildAndTest.sql
Change ScriptPath variable to a path to BuildAndTest.sql file on your device
Next execute this file in SQLCMD mode
Alternatively you can execute files that are refered to in BuildAndTest.sql file one by one
Now, If everything is set up correctly you can use this application
