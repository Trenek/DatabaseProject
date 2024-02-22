USE [Project]

GO

CREATE OR ALTER TRIGGER dbo.[CreateMutableProvinces] ON [Project].dbo.[Game Session]
AFTER INSERT
AS
	UPDATE [Project].dbo.[Game Session]
	SET [CurrentDate] = [Map].[StartingDate]
	FROM [Project].dbo.[Game Session]
	LEFT JOIN [Project].dbo.[Map] ON [Game Session].[MapID] = [Map].[MapID]

	INSERT INTO [Project].dbo.[Player]([UserID], [SessionID], [CivilizationID])
	SELECT [CreatorID], [SessionID], NULL
	FROM INSERTED

	INSERT INTO [Project].dbo.[MutableProvinces]([ProvinceID], [RegionID], [GameSessionID], [CityID])
	SELECT 
		[Province].[ProvinceID],
		[Province].[DefaultRegionID],
		inserted.[SessionID],
		[Province].[DefaultCityID]
	FROM inserted
	LEFT JOIN [Project].dbo.[Province] ON inserted.[MapID] = [Province].[MapID]
GO

CREATE OR ALTER TRIGGER dbo.[RecreateRegionAndCivilization] ON [Project].dbo.[MutableProvinces]
AFTER INSERT
AS
	DECLARE @City TABLE (
		[CityID] INT,
		[CityName] VARCHAR(255)
	)

	DECLARE @MyTable TABLE (
		[RegionID] INT,
		[RegionName] VARCHAR(255),
		[CivilizationID] INT
	)

	DECLARE @SecondTable TABLE (
		[CivilizationID] INT,
		[CivilizationName] VARCHAR(255)
	)

	-- Creating New Cities
	INSERT INTO [Project].dbo.[City]([Name], [Population], [Water], [FarmAmount], [MaxPopulation], [IsCapital])
	OUTPUT inserted.[CityID], inserted.[Name] INTO @City
	SELECT [Name], [Population], [Water], [FarmAmount], [MaxPopulation], [IsCapital]
	FROM [Project].dbo.[City]
	WHERE EXISTS (
		SELECT *
		FROM inserted
		WHERE inserted.[CityID] = [City].[CityID]
	)

	-- Create New Buildings
	INSERT INTO [Project].dbo.[Building]([CityID], [BuildingTypeID], [Level])
	SELECT [NewCity].[CityID], [Building].[BuildingTypeID], [Building].[Level]
	FROM [Project].dbo.[Building]
	LEFT JOIN [Project].dbo.[City] ON [Building].[CityID] = [City].CityID
	LEFT JOIN @City AS [NewCity] ON [City].[Name] = [NewCity].[CityName]
	WHERE EXISTS (
		SELECT *
		FROM inserted
		WHERE inserted.[CityID] = [City].[CityID]
	)

	-- Updating New Provinces with new cities
	UPDATE [Project].dbo.[MutableProvinces]
	SET [CityID] = [NewCity].[CityID]
	FROM inserted
	LEFT JOIN [Project].dbo.[MutableProvinces] ON inserted.[ID] = [MutableProvinces].[ID]
	LEFT JOIN [Project].dbo.[City] ON [MutableProvinces].[CityID] = [City].[CityID]
	LEFT JOIN @City AS [NewCity] ON [NewCity].[CityName] = [City].[Name]

	-- Creating new Civilizations
	INSERT INTO [Project].dbo.[Civilization]([CapitalCityID], [Name], [RGBA])
	OUTPUT inserted.[CivilizationID], inserted.[Name] INTO @SecondTable
	SELECT [NewCity].[CityID], [Civilization].[Name], [RGBA]
	FROM [Project].dbo.[Civilization]
	LEFT JOIN [Project].dbo.[City] ON [Civilization].[CapitalCityID] = [City].[CityID]
	LEFT JOIN @City AS [NewCity] ON [NewCity].[CityName] = [City].[Name]
	WHERE EXISTS (
		SELECT *
		FROM inserted
		LEFT JOIN [Project].dbo.[Region] ON inserted.[RegionID] = [Region].[RegionID]
		WHERE [Region].[CivilizationID] = [Civilization].[CivilizationID]
	)

	-- Creating New Regions
	INSERT INTO [Project].dbo.[Region]([Name], [MainCityID], [CivilizationID], [RGBA])
	OUTPUT inserted.[RegionID], inserted.[Name], inserted.[CivilizationID] INTO @MyTable
	SELECT [Region].[Name], [NewCity].[CityID], [NewCivilizations].[CivilizationID], [Region].[RGBA]
	FROM [Project].dbo.[Region]
	LEFT JOIN [Project].dbo.[City] ON [Region].[MainCityID] = [City].[CityID]
	LEFT JOIN @City AS [NewCity] ON [NewCity].[CityName] = [City].[Name]
	LEFT JOIN [Project].dbo.[Civilization] ON [Civilization].[CivilizationID] = [Region].[CivilizationID]
	LEFT JOIN @SecondTable AS [NewCivilizations] ON [Civilization].[Name] = [NewCivilizations].[CivilizationName]
	WHERE EXISTS (
		SELECT *
		FROM inserted
		WHERE inserted.[RegionID] = [Region].[RegionID]
	)

	-- Updating New Regions
	UPDATE [Project].dbo.[MutableProvinces]
	SET [RegionID] = [Created].[RegionID]
	FROM inserted
	LEFT JOIN [Project].dbo.[MutableProvinces] ON inserted.[ID] = [MutableProvinces].[ID]
	LEFT JOIN [Project].dbo.[Region] ON [Region].[RegionID] = [MutableProvinces].[RegionID]
	LEFT JOIN @MyTable AS [Created] ON [Created].[RegionName] = [Region].[Name]
GO

CREATE OR ALTER TRIGGER dbo.[SetDiplomaticStates] ON [Project].dbo.[Civilization]
AFTER INSERT
AS
	INSERT INTO [Project].dbo.[Diplomacy]([Civilization1ID], [Civilization2ID], [DiplomaticStateID])
	SELECT 
		[Civilization].[CivilizationID],
		inserted.[CivilizationID],
		1
	FROM inserted, [Project].dbo.[Civilization]
	LEFT JOIN [Project].dbo.[Province] ON [Civilization].[CapitalCityID] = [Province].[DefaultCityID]
	WHERE [Province].[MapID] IN (
		SELECT [MapID]
		FROM inserted
		LEFT JOIN [Project].dbo.[Province] AS [One] ON inserted.[CapitalCityID] = [One].[DefaultCityID]
		WHERE [One].[MapID] IS NOT NULL
	) AND [Civilization].[CivilizationID] <> inserted.[CivilizationID]

	INSERT INTO [Project].dbo.[Diplomacy]([Civilization1ID], [Civilization2ID], [DiplomaticStateID])
	SELECT 
		[Civilization].[CivilizationID],
		inserted.[CivilizationID],
		1
	FROM inserted, [Project].dbo.[Civilization]
	LEFT JOIN [Project].dbo.[MutableProvinces] ON [Civilization].[CapitalCityID] = [MutableProvinces].[CityID]
	WHERE [MutableProvinces].[GameSessionID] IN (
		SELECT [GameSessionID]
		FROM inserted
		LEFT JOIN [Project].dbo.[MutableProvinces] AS [One] ON inserted.[CapitalCityID] = [One].[CityID]
		WHERE [One].[GameSessionID] IS NOT NULL
	) AND [Civilization].[CivilizationID] <> inserted.[CivilizationID]
GO

CREATE OR ALTER TRIGGER dbo.[CreateSpecialBuildingTables] ON [Project].dbo.[Building]
AFTER INSERT
AS
	INSERT INTO [Project].dbo.[Barrack]([BuildingID])
	SELECT [BuildingID]
	FROM inserted
	WHERE [BuildingTypeID] = 2

	INSERT INTO [Project].dbo.[Storage]([BuildingID])
	SELECT [BuildingID]
	FROM inserted
	WHERE [BuildingTypeID] = 5

	INSERT INTO [Project].dbo.[Market]([BuildingID])
	SELECT [BuildingID]
	FROM inserted
	WHERE [BuildingTypeID] = 6

	INSERT INTO [Project].dbo.[Theatre_Square]([BuildingID])
	SELECT [BuildingID]
	FROM inserted
	WHERE [BuildingTypeID] = 7
GO

CREATE OR ALTER TRIGGER dbo.[GetMonthlyTaxes] ON [Project].dbo.[Game Session]
AFTER UPDATE
AS
	IF EXISTS (
		SELECT * 
		FROM inserted
		LEFT JOIN deleted ON inserted.SessionID = deleted.SessionID
		WHERE (DATEDIFF(DAY, deleted.[CurrentDate], inserted.[CurrentDate]) = 1) AND (DATEPART(DAY, inserted.[CurrentDate]) = 1)
	) BEGIN
		UPDATE [Project].dbo.[Civilization]
		SET [Money] += (
			SELECT SUM([CitySum].[Sum])
			FROM [Project].dbo.[MutableProvinces]
			LEFT JOIN [Project].dbo.[Region] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
			LEFT JOIN (
				SELECT
					[City].[CityID] AS [CityID],
					SUM(
					--([Population] / 10000) *
					[Level] * ([BasicTax])) AS [Sum]
				FROM [Project].dbo.[City]
				LEFT JOIN [Project].dbo.[Building] ON [City].[CityID] = [Building].[CityID]
				LEFT JOIN [Project].dbo.[BuildingType] ON [Building].[BuildingTypeID] = [BuildingType].[BuildingTypeID]
				WHERE [Building].[BuildingID] IS NOT NULL
				GROUP BY [City].[CityID]
			) AS [CitySum] ON [CitySum].[CityID] = [MutableProvinces].[CityID]
			WHERE [Source].[CivilizationID] = [Region].[CivilizationID] AND [CitySum].[CityID] IS NOT NULL
		)
		FROM [Project].dbo.[Civilization] AS [Source]
		WHERE EXISTS (
			SELECT * 
			FROM [Project].dbo.[MutableProvinces]
			WHERE [MutableProvinces].[CityID] = [Source].[CapitalCityID] AND [MutableProvinces].[GameSessionID] IN (
				SELECT [GameSessionID]
				FROM inserted
			)
		)
	END

	DELETE 
	FROM [Project].dbo.[ConstructCity]
	WHERE [CompletionDate] IN (
		SELECT [CurrentDate]
		FROM inserted
	)
GO

CREATE OR ALTER TRIGGER dbo.[CreateCity] ON [Project].dbo.[ConstructCity]
AFTER DELETE
AS
	DECLARE @ID TABLE (
		[ID] INT,
		[Name] VARCHAR(255)
	)

	INSERT INTO [Project].dbo.[City]([Name])
	OUTPUT inserted.[CityID], inserted.[Name] INTO @ID
	SELECT deleted.[Name]
	FROM deleted
	LEFT JOIN [Project].dbo.[MutableProvinces] ON [MutableProvinces].[ID] = deleted.[MutableProvinceID]
	LEFT JOIN [Project].dbo.[Game Session] ON [Game Session].[SessionID] = [MutableProvinces].[GameSessionID]
	WHERE deleted.[CompletionDate] = [Game Session].[CurrentDate]

	UPDATE [Project].dbo.[MutableProvinces]
	SET [CityID] = [InsertedCity].[ID]
	FROM [Project].dbo.[MutableProvinces]
	RIGHT JOIN deleted ON deleted.[MutableProvinceID] = [MutableProvinces].[ID]
	LEFT JOIN @ID AS [InsertedCity] ON [InsertedCity].[Name] = deleted.[Name] 
	LEFT JOIN [Project].dbo.[Game Session] ON [Game Session].[SessionID] = [MutableProvinces].[GameSessionID]
	WHERE deleted.[CompletionDate] = [Game Session].[CurrentDate]
GO

USE [master]