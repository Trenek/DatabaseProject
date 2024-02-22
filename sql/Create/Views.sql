USE [Project]

GO

CREATE VIEW dbo.[DefaultCivilizationAndProvince] AS
SELECT 
	[Civilization].[CivilizationID] AS [CivilizationID], 
	[Civilization].[RGBA] AS [RGBA],
	[Civilization].[Name] AS [CivilizationName],
	[Province].[DefaultCityID] AS [DefaultCityID], 
	[Province].[ProvinceID] AS [ProvinceID], 
	[Province].[MapID] AS [MapID]
FROM [Project].dbo.[Civilization]
LEFT JOIN [Project].dbo.[City] ON [Civilization].[CapitalCityID] = [City].[CityID]
LEFT JOIN [Project].dbo.[Province] ON [City].[CityID] = [Province].[DefaultCityID]

GO

USE [master]