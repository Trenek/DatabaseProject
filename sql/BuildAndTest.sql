USE [master]

GO

DROP DATABASE [Project]

GO

CREATE DATABASE [Project]

GO

USE [Project]

SET NOCOUNT ON

:setvar ScriptPath "C:\Users\Laptopi Pan\Documents\GitHub\Projekt-Bazy-Danych\Projekt\"

:r $(ScriptPath)"Create\Tables.sql"
:r $(ScriptPath)"Create\ForeignKeys.sql"
:r $(ScriptPath)"Create\Functions.sql"
:r $(ScriptPath)"Create\Constraints.sql"
:r $(ScriptPath)"Create\Views.sql"
:r $(ScriptPath)"Create\Procedures.sql"
:r $(ScriptPath)"Create\Triggers.sql"

:r $(ScriptPath)"Insert\BuildingTypes.sql"
:r $(ScriptPath)"Insert\Users.sql"
:r $(ScriptPath)"Insert\Terrain.sql"
:r $(ScriptPath)"Insert\DiplomacyState.sql"
:r $(ScriptPath)"Insert\Map.sql"
:r $(ScriptPath)"Insert\MilitaryUnitTypes.sql"