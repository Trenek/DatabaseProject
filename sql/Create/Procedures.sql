USE [Project]

GO

CREATE OR ALTER PROCEDURE dbo.[AddNewUser]
    @login VARCHAR(255),
    @password VARCHAR(255),
    @email VARCHAR(255)
AS
	DECLARE @retVal INT

	-- Check for unique login
    IF EXISTS (SELECT * FROM [User] WHERE [Login] = @login)
    BEGIN
        RAISERROR ('Error: Login already exists.', 16, 1);
        RETURN;
    END

    -- Check for unique email
    IF EXISTS (SELECT * FROM [User] WHERE [Email] = @email)
    BEGIN
        RAISERROR ('Error: Email already exists.', 16, 1);
        RETURN;
    END

    -- Check for email constraints
    IF dbo.[CheckIfStringIsEmail](@email) = 0
    BEGIN
        RAISERROR ('Error: Email is not valid.', 16, 1);
        RETURN;
    END

	SET @retVal = dbo.[CheckPasswordRequirements](@password)

	IF (@retVal = 0) BEGIN
		INSERT INTO [Project].dbo.[User] ([Login], [Password], [Email])
		VALUES (@login, @password, @email);
	END
	ELSE IF (@retVal = 1) BEGIN
		RAISERROR ('Error: Password does not have lower letters.', 16, 1);
	END
	ELSE IF (@retVal = 2) BEGIN
	    RAISERROR ('Error: Password does not have upper letters.', 16, 1);
	END
	ELSE IF (@retVal = 3) BEGIN
		RAISERROR ('Error: Password does not have numbers.', 16, 1);
	END
	ELSE IF (@retVal = 4) BEGIN
		RAISERROR ('Error: Password is too short.', 16, 1);
	END
GO

CREATE OR ALTER PROCEDURE dbo.[Login]
	@login VARCHAR(255),
	@password VARCHAR(255)
AS
	IF @login NOT IN (SELECT [Login] FROM [User] WHERE [Login] = @login) BEGIN
		RAISERROR ('Error: Login doesn''t exist.', 16, 1);
		RETURN
	END

	IF @login NOT IN (SELECT [Login] FROM [User] WHERE [Login] = @login AND [Password] = @password) BEGIN
		RAISERROR ('Error: Wrong Password.', 16, 1);
		RETURN
	END

	SELECT [UserID]
	FROM [Project].dbo.[User]
	WHERE [Login] = @login AND [Password] = @password
GO

CREATE OR ALTER PROCEDURE dbo.[ShowUsers]
	@page INT
AS
	SELECT [Number], [Login]
	FROM (
		SELECT 
			ROW_NUMBER() OVER(ORDER BY [UserID] ASC) AS [Number], 
			[Login]
		FROM [Project].dbo.[User] 
	) AS [List]
	WHERE [Number] BETWEEN ((10 * @page) - 9) AND (10 * @page)
	ORDER BY [Number] ASC
GO

CREATE OR ALTER PROCEDURE dbo.[DeleteUserById]
    @user_id INT
AS
    DELETE FROM [Project].dbo.[User] WHERE [UserID] = @user_id;
GO

CREATE OR ALTER PROCEDURE dbo.[CreateGameSession]
	@saveName VARCHAR(128),
	@creatorID INT,
	@mapID INT
AS
	IF EXISTS (SELECT * FROM [Project].dbo.[Game Session] WHERE [SaveName] = @saveName)
    BEGIN
		RAISERROR ('Error: Name already taken.', 16, 1);
    END
	ELSE BEGIN
		DECLARE @ID TABLE (
			[ID] INT
		)

		INSERT INTO [Project].dbo.[Game Session]([SaveName], [CreatorID], [MapID]) 
		OUTPUT inserted.[SessionID] INTO @ID
		VALUES (@saveName, @creatorID, @mapID)

		SELECT [ID]
		FROM @ID
	END
GO

CREATE OR ALTER PROCEDURE dbo.[GetGameSessionID]
	@saveName VARCHAR(128),
	@creatorID INT
AS
	SELECT [SessionID]
	FROM [Project].dbo.[Game Session]
	WHERE [SaveName] = @saveName AND [CreatorID] = @creatorID
GO

CREATE OR ALTER PROCEDURE dbo.[ShowGameSessions]
	@page INT,
	@ownerID INT
AS
	SELECT [Number], [SaveName], [SessionID]
	FROM (
		SELECT
			ROW_NUMBER() OVER(ORDER BY [SessionID] ASC) AS [Number], 
			[SaveName],
			[SessionID]
		FROM [Project].dbo.[Game Session]
		WHERE [CreatorID] = @ownerID 
	) AS [List]
	WHERE [Number] BETWEEN ((10 * @page) - 9) AND (10 * @page)
	ORDER BY [Number] ASC
GO

CREATE OR ALTER PROCEDURE dbo.[GetTerrainCount]
AS
	SELECT COUNT(*)
	FROM [Project].dbo.[Terrain]
GO

CREATE OR ALTER PROCEDURE dbo.[GetTerrain]
AS
	SELECT [TerrainID], [Name]
	FROM [Project].dbo.[Terrain]
GO

CREATE OR ALTER PROCEDURE dbo.[GetProvinces]
	@mapID INT
AS
	SELECT 
		[CoordinateX], 
		[CoordinateY],
		[TerrainID],
		ISNULL([DefaultCityID], 0)
	FROM [Project].dbo.[Province]
	WHERE [MapID] = @mapID
GO

CREATE OR ALTER PROCEDURE dbo.[GetSessionProvinces]
	@sessionID INT
AS
	SELECT 
		[Province].[CoordinateX], 
		[Province].[CoordinateY],
		[Province].[TerrainID],
		ISNULL([MutableProvinces].[CityID], 0)
	FROM [Project].dbo.[MutableProvinces]
	LEFT JOIN [Project].dbo.[Province] ON [MutableProvinces].[ProvinceID] = [Province].[ProvinceID]
	WHERE [MutableProvinces].[GameSessionID] = @sessionID
GO

CREATE OR ALTER PROCEDURE dbo.[CreateDefaultCity]
	@mapID INT,
	@coordinateX INT,
	@coordinateY INT,
	@name VARCHAR(255)
AS
	DECLARE @MyTableVar TABLE (
		id INT
	)

	INSERT INTO [Project].dbo.[City]([Name])
	OUTPUT inserted.[CityID] INTO @MyTableVar
	VALUES (@name)

	UPDATE [Project].dbo.[Province]
	SET [DefaultCityID] = (
		SELECT [id]
		FROM @MyTableVar
	)
	WHERE [CoordinateX] = @coordinateX AND [CoordinateY] = @coordinateY AND [MapID] = @mapID
GO

CREATE OR ALTER PROCEDURE dbo.[CreateCivilization]
	@mapID INT,
	@coordinateX INT = 0, -- capital
	@coordinateY INT = 0, -- capital
	@name VARCHAR(255),
	@RGBA INT,
	@cityID INT = 0
AS
	DECLARE @inserted TABLE (
		 [CivilizationID] INT, 
		 [Name] VARCHAR(255), 
		 [CapitalCityID] INT,
		 [RGBA] INT
	)

	IF (@cityID = 0) BEGIN
		SET @cityID = (
			SELECT [CityID]
			FROM [Project].dbo.[City]
			LEFT JOIN [Project].dbo.[Province] ON [City].[CityID] = [Province].[DefaultCityID]
			WHERE [Province].[CoordinateX] = @coordinateX AND [Province].[CoordinateY] = @coordinateY AND [Province].[MapID] = @mapID
		)
	END

	INSERT INTO [Project].dbo.[Civilization]([Name], [CapitalCityID], [RGBA])
	OUTPUT inserted.[CivilizationID], inserted.[Name], inserted.[CapitalCityID], inserted.[RGBA] INTO @inserted
	VALUES (@name, @cityID, @RGBA)

	INSERT INTO [Project].dbo.[Region]([CivilizationID], [Name], [MainCityID], [RGBA])
	SELECT [CivilizationID], [Name], [CapitalCityID], [RGBA]
	FROM @inserted

	UPDATE [Project].dbo.[City]
	SET [IsCapital] = 1
	WHERE EXISTS (
		SELECT *
		FROM [Project].dbo.[Civilization]
		WHERE EXISTS (
			SELECT *
			FROM @inserted AS [A]
			WHERE [Civilization].[CivilizationID] = [A].[CivilizationID]
		)
	)

	UPDATE [Project].dbo.[Province]
	SET [DefaultRegionID] = (
		SELECT [RegionID]
		FROM [Project].dbo.[Region]
		WHERE [MainCityID] = @cityID
	)
	WHERE [DefaultCityID] = @cityID
GO

CREATE OR ALTER PROCEDURE dbo.[AddProvinceToRegion]
	@mapID INT,
	@coordinateX INT = 0,
	@coordinateY INT = 0,
	@regionName VARCHAR(255),
	@regionID INT = 0
AS
	IF (@regionID = 0) BEGIN
		SET @regionID = (
			SELECT [Region].[RegionID]
			FROM [Project].dbo.[Region]
			LEFT JOIN [Project].dbo.[City] ON [Region].[MainCityID] = [City].[CityID]
			LEFT JOIN [Project].dbo.[Province] ON [Province].[DefaultCityID] = [City].[CityID]
			WHERE [Region].[Name] = @regionName AND [Province].[MapID] = @mapID
		)
	END

	UPDATE [Project].dbo.[Province]
	SET [DefaultRegionID] = @regionID
	WHERE [CoordinateX] = @coordinateX AND [CoordinateY] = @coordinateY AND [MapID] = @mapID
GO

CREATE OR ALTER PROCEDURE dbo.[CountCivilizations]
	@mapID INT
AS
	SELECT COUNT(DISTINCT [Region].[CivilizationID])
	FROM [Project].dbo.[Province]
	LEFT JOIN [Project].dbo.[Region] ON [Province].[DefaultRegionID] = [Region].[RegionID]
	WHERE [Province].[MapID] = @mapID AND [Region].[CivilizationID] IS NOT NULL

GO

CREATE OR ALTER PROCEDURE dbo.[GetCivilizations]
	@mapID INT
AS
	SELECT
		ROW_NUMBER() OVER(ORDER BY [CivilizationID] ASC) - 1 AS [ID], 
		[CivilizationID],
		[RGBA],
		[Name]
	FROM [Project].dbo.[Civilization]
	WHERE [CivilizationID] IN (
		SELECT DISTINCT [CivilizationID]
		FROM [Project].dbo.[Province]
		LEFT JOIN [Project].dbo.[Region] ON [Province].[DefaultRegionID] = [Region].[RegionID]
		WHERE ([Province].[MapID] = @mapID) AND ([Region].[CivilizationID] IS NOT NULL)
	)
GO

CREATE OR ALTER PROCEDURE dbo.[CountSessionCivilizations]
	@gameSessionID INT
AS
	SELECT COUNT(DISTINCT [Region].[CivilizationID])
	FROM [Project].dbo.[MutableProvinces]
	LEFT JOIN [Project].dbo.[Region] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
	WHERE [MutableProvinces].[GameSessionID] = @gameSessionID AND [Region].[CivilizationID] IS NOT NULL
GO

CREATE OR ALTER PROCEDURE dbo.[GetSessionCivilizations]
	@gameSessionID INT
AS
	SELECT
		ROW_NUMBER() OVER(ORDER BY [CivilizationID] ASC) - 1 AS [ID], 
		[CivilizationID],
		[RGBA],
		[Name]
	FROM [Project].dbo.[Civilization]
	WHERE [CivilizationID] IN (
		SELECT DISTINCT [CivilizationID]
		FROM [Project].dbo.[MutableProvinces]
		LEFT JOIN [Project].dbo.[Region] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
		WHERE ([MutableProvinces].[GameSessionID] = @gameSessionID) AND ([Region].[CivilizationID] IS NOT NULL)
	)
GO

CREATE OR ALTER PROCEDURE dbo.[GetPoliticalDivision]
	@mapID INT
AS
	SELECT 
		[CoordinateX], 
		[CoordinateY],
		ISNULL([DefaultRegionID], 0),
		ISNULL([Region].[CivilizationID], 0),
		ISNULL([Ranking].[Rank], -1),
		IIF([Province].[DefaultCityID] IS NOT NULL AND [Civilization].[CapitalCityID] = [Province].[DefaultCityID], 1, 0)
	FROM [Project].dbo.[Province]
	LEFT JOIN [Project].dbo.[Region] ON [Province].[DefaultRegionID] = [Region].[RegionID]
	LEFT JOIN (
		SELECT 
			[CivilizationID],
			DENSE_RANK() OVER(ORDER BY [CivilizationID] ASC) - 1 AS [Rank]
		FROM dbo.[DefaultCivilizationAndProvince]
		WHERE [MapID] = @mapID
	) AS [Ranking] ON [Ranking].[CivilizationID] = [Region].[CivilizationID]
	LEFT JOIN [Project].dbo.[Civilization] ON [Region].[CivilizationID] = [Civilization].[CivilizationID]
	WHERE [MapID] = @mapID
GO

CREATE OR ALTER PROCEDURE dbo.[GetSessionPoliticalDivision]
	@gameSession INT
AS
	SELECT 
		[Province].[CoordinateX] AS [CoordinateX],
		[Province].[CoordinateY] AS [CoordinateY],
		ISNULL([MutableProvinces].[RegionID], 0) AS [RegionID],
		ISNULL([NumberedCivilization].[CivilizationID], 0) AS [CivilizationID],
		ISNULL([NumberedCivilization].[Position], -1) AS [Position],
		IIF([MutableProvinces].[CityID] IS NOT NULL AND [NumberedCivilization].[CapitalCityID] = [MutableProvinces].[CityID], 1, 0) AS [IsCapital]
	FROM [Project].dbo.[MutableProvinces]
	LEFT JOIN [Project].dbo.[Province] ON [MutableProvinces].[ProvinceID] = [Province].[ProvinceID]
	LEFT JOIN [Project].dbo.[Region] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
	LEFT JOIN (
		SELECT DISTINCT
			[Civilization].[CivilizationID] AS [CivilizationID],
			[Civilization].[CapitalCityID] AS [CapitalCityID],
			DENSE_RANK() OVER(ORDER BY [Civilization].[CivilizationID] ASC) - 1 AS [Position]
		FROM [Project].dbo.[Civilization]
		LEFT JOIN [Project].dbo.[Region] ON [Region].[CivilizationID] = [Civilization].[CivilizationID]
		LEFT JOIN [Project].dbo.[MutableProvinces] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
		WHERE [MutableProvinces].[GameSessionID] = @gameSession
	) AS [NumberedCivilization] ON [Region].[CivilizationID] = [NumberedCivilization].[CivilizationID]
	WHERE [MutableProvinces].[GameSessionID] = @gameSession
GO

CREATE OR ALTER PROCEDURE dbo.[GetMaps]
	@page INT
AS
	SELECT [Number], [Name], [MapID]
	FROM (
		SELECT
			ROW_NUMBER() OVER(ORDER BY [MapID] ASC) AS [Number], 
			[Name],
			[MapID]
		FROM [Project].dbo.[Map]
	) AS [List]
	WHERE [Number] BETWEEN ((10 * @page) - 9) AND (10 * @page)
	ORDER BY [Number] ASC
GO

CREATE OR ALTER PROCEDURE dbo.[ShowPlayer]
	@gameSession INT,
	@position INT
AS
	SELECT [Number], [Name], [CivilizationName], [PlayerID], [CivID], [Money]
	FROM (
		SELECT
			ROW_NUMBER() OVER(ORDER BY [Player].[PlayerID] ASC) AS [Number],
			[User].[Login] AS [Name],
			[Civilization].[Name] AS [CivilizationName],
			[Player].[PlayerID] AS [PlayerID],
			[Player].[CivilizationID] AS [CivID],
			[Civilization].[Money] AS [Money]
		FROM [Project].dbo.[Player]
		LEFT JOIN [Project].dbo.[User] ON [Player].[UserID] = [User].[UserID]
		LEFT JOIN [Project].dbo.[Civilization] ON [Player].[CivilizationID] = [Civilization].[CivilizationID]
		WHERE [Player].[SessionID] = @gameSession
	) AS [List]
	WHERE [Number] = @position
GO

CREATE OR ALTER PROCEDURE dbo.[AddPlayer]
	@gameSession INT,
	@userID INT
AS
	IF EXISTS (SELECT * FROM [Project].dbo.[Player] WHERE [SessionID] = @gameSession AND [UserID] = @userID) BEGIN
		RAISERROR ('Error: User is already a player in this game!', 16, 1);
	END
	ELSE BEGIN
		INSERT INTO [Project].dbo.[Player]([UserID], [SessionID], [CivilizationID]) VALUES 
			(@userID, @gameSession, NULL)
	END
GO

CREATE OR ALTER PROCEDURE dbo.[AssignCivilization]
	@playerID INT,
	@civilizationID INT,
	@gameSession INT
AS
	IF EXISTS (SELECT * FROM [Project].dbo.[Player] WHERE [CivilizationID] = @civilizationID AND [SessionID] = @gameSession) BEGIN
		RAISERROR ('Error: Civilization is already taken!', 16, 1);
	END
	ELSE BEGIN
		UPDATE [Project].dbo.[Player]
		SET [CivilizationID] = @civilizationID
		WHERE [PlayerID] = @playerID
	END
GO

/*
CREATE OR ALTER PROCEDURE dbo.[AddNewUnit]
    @type VARCHAR(255),
    @city_id INT,
    @civilization_id INT,
    @barrack_id INT,
    @level INT
AS
	DECLARE @production_cost INT
	DECLARE @purchase_price INT
	DECLARE @typeID INT

    IF NOT EXISTS (SELECT * FROM [Project].dbo.[City] WHERE [CityID] = @city_id AND [Water] = 1) BEGIN
		RAISERROR ('Error: The city does not have water and cannot produce units.', 16, 1);
        RETURN;
    END

    SELECT 
		@production_cost = [ProductionCost], 
		@purchase_price = [PurchasePrice],
		@typeID = [MilitaryUnitTypeID]
    FROM [Project].dbo.[Military_Unit_type]
    WHERE [TypeName] = @type

    UPDATE [Project].dbo.[Market]
    SET [Gold] = [Gold] - @purchase_price
    WHERE [CityID] = @city_id AND [Gold] >= @purchase_price

	IF (@@ROWCOUNT = 0) BEGIN
		RAISERROR ('Error: Insufficient gold in the market to purchase the unit.', 16, 1);
    END
	ELSE BEGIN
		INSERT INTO [Project].dbo.[Military_Unit] ([CivilizationID], [BarrackID], [Level], [Wait], [MilitaryUnitTypeID]) VALUES 
			(@civilization_id, @barrack_id, @level, @production_cost, @typeID)
	END
GO

CREATE OR ALTER PROCEDURE dbo.[ReplaceUnit]
    @old_unit_type VARCHAR(255),
    @new_unit_type VARCHAR(255),
    @city_id INT,
    @civilization_id INT,
    @barrack_id INT,
    @level INT
AS
	DELETE FROM [Project].dbo.[Military_Unit]
    WHERE [MilitaryUnitID] IN (
        SELECT TOP 1 [Unit].[MilitaryUnitID]
        FROM [Project].dbo.[Military_Unit] AS [Unit]
        INNER JOIN [Project].dbo.[Military_Unit_type] AS [Type] ON [Unit].[MilitaryUnitTypeID] = [Type].[MilitaryUnitTypeID]
        WHERE [Type].[TypeName] = @old_unit_type AND [Unit].[BarrackID] = @barrack_id
    );

	IF (@@ROWCOUNT = 0) BEGIN
		RAISERROR ('Error: The specified old unit type does not exist in the given barracks.', 16, 1);
	END
	ELSE BEGIN
		UPDATE [Project].dbo.[Market]
		SET [Gold] += [PurchasePrice] / 2
		FROM [Project].dbo.[Market]
		LEFT JOIN [Project].dbo.[Military_Unit_type] ON [Military_Unit_type].[TypeName] = @old_unit_type
		WHERE [CityID] = @city_id;

		EXEC [Project].dbo.[AddNewUnit] @new_unit_type, @city_id, @civilization_id, @barrack_id, @level;
	END
GO
*/

CREATE OR ALTER PROCEDURE dbo.[GetSessionDimensions]
	@sessionID INT
AS
	SELECT
		[Width], 
		[Height]
	FROM [Project].dbo.[Game Session]
	LEFT JOIN [Project].dbo.[Map] ON [Game Session].[MapID] = [Map].[MapID]
	WHERE [Game Session].[SessionID] = @sessionID
GO

CREATE OR ALTER PROCEDURE dbo.[GetMapDimensions]
	@mapID INT
AS
	SELECT
		[Width], 
		[Height]
	FROM [Project].dbo.[Map]
	WHERE [Map].[MapID] = @mapID
GO

CREATE OR ALTER PROCEDURE dbo.[CheckIfEveryoneIsReady]
	@sessionID INT
AS
	SELECT *
	FROM [Project].dbo.[Player]
	WHERE [SessionID] = @sessionID AND [CivilizationID] IS NULL
GO

CREATE OR ALTER PROCEDURE dbo.[RemovePlayer]
	@playerID INT
AS
	DELETE
	FROM [Project].dbo.[Player]
	WHERE [PlayerID] = @playerID
GO

CREATE OR ALTER PROCEDURE dbo.[GetProvinceInformation]
	@sessionID INT,
	@coordinateX INT,
	@coordinateY INT
AS
	SELECT
		[Terrain].[Name],
		[Region].[Name],
		[City].[Name]
	FROM [Project].dbo.[MutableProvinces]
	LEFT JOIN [Project].dbo.[Province] ON [MutableProvinces].[ProvinceID] = [Province].[ProvinceID]
	LEFT JOIN [Project].dbo.[Terrain] ON [Terrain].[TerrainID] = [Province].[TerrainID]
	LEFT JOIN [Project].dbo.[Region] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
	LEFT JOIN [Project].dbo.[City] ON [MutableProvinces].[CityID] = [City].[CityID]
	WHERE [MutableProvinces].[GameSessionID] = @sessionID AND [Province].[CoordinateX] = @coordinateX AND [Province].[CoordinateY] = @coordinateY
GO

CREATE OR ALTER PROCEDURE dbo.[GetCurrentDate]
	@SessionID INT
AS
	SELECT 
		[Game Session].[CurrentDate],
		IIF(DATEPART(DAY, [CurrentDate]) = 1, 1, 0)
	FROM [Project].dbo.[Game Session]
	WHERE [SessionID] = @SessionID
GO

CREATE OR ALTER PROCEDURE dbo.[UpdateCurrentDate]
	@SessionID INT
AS
	UPDATE [Project].dbo.[Game Session]
	SET [CurrentDate] = DATEADD(DAY, 1, [CurrentDate])
	WHERE [SessionID] = @SessionID
GO

CREATE OR ALTER PROCEDURE dbo.[BuildCity]
	@SessionID INT,
	@coordinateX INT,
	@coordinateY INT,
	@name VARCHAR(255)
AS
	IF @name = '' BEGIN
		RAISERROR ('Error: name cannot be empty', 16, 1);
	END

	IF EXISTS (
		SELECT *
		FROM [Project].dbo.[City]
		WHERE [Name] = @name
	) BEGIN
		RAISERROR ('Error: City is already built!', 16, 1);
		RETURN
	END

	IF EXISTS (
		SELECT *
		FROM [Project].dbo.[ConstructCity]
		WHERE [Name] = @name
	) BEGIN
		RAISERROR ('Error: City is being built!', 16, 1);
		RETURN
	END

	UPDATE [Project].dbo.[Civilization]
	SET [Money] -= 500
	FROM [Project].dbo.[Civilization]
	WHERE EXISTS (
		SELECT DISTINCT [Region].[CivilizationID]
		FROM [Project].dbo.[MutableProvinces]
		LEFT JOIN [Project].dbo.[Province] ON [MutableProvinces].[ProvinceID] = [Province].[ProvinceID]
		LEFT JOIN [Project].dbo.[Region] ON [MutableProvinces].[RegionID] = [Region].[RegionID]
		WHERE	[MutableProvinces].[GameSessionID] = @SessionID AND 
				[Province].[CoordinateX] = @coordinateX AND 
				[Province].[CoordinateY] = @coordinateY AND
				[Region].[CivilizationID] = [Civilization].[CivilizationID]
	) AND ([Money] >= 500)

	IF (@@ROWCOUNT = 0) BEGIN
		RAISERROR ('Error: Not enought Money!', 16, 1);
		RETURN
	END

	INSERT INTO [Project].dbo.[ConstructCity]([MutableProvinceID], [CompletionDate], [Name])
	SELECT [MutableProvinces].[ID], DATEADD(day, 100, [Game Session].[CurrentDate]), @name
	FROM [Project].dbo.[MutableProvinces]
	LEFT JOIN [Project].dbo.[Province] ON [MutableProvinces].[ProvinceID] = [Province].[ProvinceID]
	LEFT JOIN [Project].dbo.[Game Session] ON [Game Session].[SessionID] = [MutableProvinces].[GameSessionID]
	WHERE [GameSessionID] = @SessionID AND [CoordinateX] = @coordinateX AND [CoordinateY] = @coordinateY
GO

CREATE OR ALTER PROCEDURE dbo.[GetCityConstructionDate]
	@SessionID INT,
	@coordinateX INT,
	@coordinateY INT
AS
	SELECT [CompletionDate]
	FROM [Project].dbo.[ConstructCity]
	LEFT JOIN [Project].dbo.[MutableProvinces] ON [MutableProvinces].[ID] = [ConstructCity].[MutableProvinceID]
	LEFT JOIN [Project].dbo.[Province] ON [Province].[ProvinceID] = [MutableProvinces].[ProvinceID]
	WHERE [GameSessionID] = @SessionID AND [CoordinateX] = @coordinateX AND [CoordinateY] = @coordinateY
GO

CREATE OR ALTER PROCEDURE dbo.[GetBuildingsInformation]
	@CityID INT
AS
	SELECT 
		[Building].[BuildingID] AS [BuildingID],
		[BuildingType].[TypeName] AS [BuildingType],
		[Building].[Level] AS [Level]
	FROM [Project].dbo.[Building]
	LEFT JOIN [Project].dbo.[BuildingType] ON [Building].[BuildingTypeID] = [BuildingType].[BuildingTypeID]
	WHERE [Building].CityID = @CityID
GO

CREATE OR ALTER PROCEDURE dbo.[GetBuildingType]
	@CityID INT,
	@TypeID INT
AS
	IF EXISTS (
		SELECT *
		FROM [Project].dbo.[BuildingType]
		LEFT JOIN [Project].dbo.[Building] ON [Building].[BuildingTypeID] = [BuildingType].[BuildingTypeID]
		WHERE [Building].[CityID] = @CityID AND [Building].[BuildingTypeID] = @TypeID
	) BEGIN
		SELECT 
			IIF([BuildingID] IS NOT NULL, ROW_NUMBER() OVER(ORDER BY [BuildingID] ASC), 1) AS [Number],
			ISNULL([Building].[Level], 0) AS [Level],
			[BuildingType].[MaxLevel] AS [MaxLevel],
			[BuildingType].[BasicTax] AS [Tax],
			[BuildingType].[BasicLevies] AS [Levies],
			[BuildingType].[Price] * (ISNULL([Building].[Level], 0) + 1) AS [Price],
			[BuildingType].[TypeName] AS [Name]
		FROM [Project].dbo.[BuildingType]
		LEFT JOIN [Project].dbo.[Building] ON [Building].[BuildingTypeID] = [BuildingType].[BuildingTypeID]
		WHERE [Building].[CityID] = @CityID AND [Building].[BuildingTypeID] = @TypeID
	END
	ELSE BEGIN
		SELECT 
			0,
			[BuildingType].[MaxLevel] AS [MaxLevel],
			[BuildingType].[BasicTax] AS [Tax],
			[BuildingType].[BasicLevies] AS [Levies],
			[BuildingType].[Price] AS [Price],
			[BuildingType].[TypeName] AS [Name]
		FROM [Project].dbo.BuildingType
		WHERE [BuildingTypeID] = @TypeID
	END
GO

CREATE OR ALTER PROCEDURE dbo.[GetCivilizationInformations]
	@CivilizationID INT,
	@CurrentCivilizationID INT
AS
	SELECT
		[Civilization].[Name],
		[Civilization].[Money],
		[DiplomaticStates].[Name]
	FROM [Project].dbo.[Diplomacy]
	LEFT JOIN [Project].dbo.[Civilization] ON [Diplomacy].[Civilization1ID] = [Civilization].[CivilizationID]
	LEFT JOIN [Project].dbo.[DiplomaticStates] ON [Diplomacy].[DiplomaticStateID] = [DiplomaticStates].[DiplomaticStateID]
	WHERE [Diplomacy].[Civilization1ID] = @CivilizationID AND [Diplomacy].[Civilization2ID] = @CurrentCivilizationID
GO

USE [master]