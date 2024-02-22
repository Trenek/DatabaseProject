USE [Project]

GO

CREATE OR ALTER FUNCTION dbo.[CheckCivilizationUnique]()
	RETURNS INT
AS 
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1 
		@retVal = COUNT([CivilizationID])
	FROM [Project].dbo.[Player]
	WHERE [CivilizationID] IS NOT NULL
	GROUP BY [CivilizationID]
	ORDER BY COUNT([CivilizationID]) DESC

	RETURN @retVal
END 
GO

CREATE OR ALTER FUNCTION dbo.[CheckIfStringIsEmail](
	@email VARCHAR(255)
) RETURNS BIT
AS 
BEGIN
	DECLARE @retVal BIT = 0

	IF @email LIKE '%_@__%.__%'
	BEGIN 
		SET @retVal = 1
	END

	RETURN @retVal
END 
GO

CREATE OR ALTER FUNCTION dbo.[CheckPasswordRequirements](
	@password VARCHAR(255)
) RETURNS INT
AS
BEGIN
	DECLARE @retVal INT = 0

	IF @password NOT LIKE '%[a-z]%' BEGIN
		SET @retVal = 1
	END
	ELSE IF @password NOT LIKE '%[A-Z]%' BEGIN
		SET @retVal = 2
	END
	ELSE IF @password NOT LIKE '%[0-9]%' BEGIN
		SET @retVal = 3
	END
	ELSE IF LEN(@password) < 8 BEGIN
		SET @retVal = 4
	END

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[CheckDefaultCity]()
	RETURNS INT
AS 
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1 
		@retVal = COUNT([DefaultCityID])
	FROM [Project].dbo.[Province]
	WHERE [DefaultCityID] IS NOT NULL
	GROUP BY [DefaultCityID]
	ORDER BY COUNT([DefaultCityID]) DESC

	RETURN @retVal
END 
GO

CREATE OR ALTER FUNCTION dbo.[CheckCity]()
	RETURNS INT
AS 
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1 
		@retVal = COUNT([CityID])
	FROM [Project].dbo.[MutableProvinces]
	WHERE [CityID] IS NOT NULL
	GROUP BY [CityID]
	ORDER BY COUNT([CityID]) DESC

	RETURN @retVal
END 
GO

CREATE OR ALTER FUNCTION dbo.[CheckProvinceRegionUQ]()
	RETURNS INT
AS 
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1 
		@retVal = COUNT([RegionID])
	FROM [Project].dbo.[MutableProvinces]
	WHERE [RegionID] IS NOT NULL
	GROUP BY [ProvinceID], [RegionID]
	ORDER BY COUNT([RegionID]) DESC

	RETURN @retVal
END 
GO

CREATE OR ALTER FUNCTION dbo.[UniqueSessionCityName]()
	RETURNS INT
AS
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1
		@retVal = COUNT([City].[Name])
	FROM [Project].dbo.[MutableProvinces]
	LEFT JOIN [Project].dbo.[City] ON [MutableProvinces].[CityID] = [City].[CityID]
	WHERE [MutableProvinces].[CityID] IS NOT NULL
	GROUP BY [GameSessionID], [City].[Name]
	ORDER BY COUNT([City].[Name]) DESC

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[UniqueMapCityName]()
	RETURNS INT
AS
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1
		@retVal = COUNT([City].[Name])
	FROM [Project].dbo.[Province]
	LEFT JOIN [Project].dbo.[City] ON [Province].[DefaultCityID] = [City].[CityID]
	WHERE [Province].[DefaultCityID] IS NOT NULL
	GROUP BY [MapID], [City].[Name]
	ORDER BY COUNT([City].[Name]) DESC

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[UniqueSessionRegionName]()
	RETURNS INT
AS
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1
		@retVal = COUNT([Region].[Name])
	FROM [Project].dbo.[Region]
	LEFT JOIN [Project].dbo.[City] ON [Region].[MainCityID] = [City].[CityID]
	LEFT JOIN [Project].dbo.[MutableProvinces] ON [MutableProvinces].[CityID] = [City].[CityID]
	WHERE [MutableProvinces].[CityID] IS NOT NULL
	GROUP BY [GameSessionID], [Region].[Name]
	ORDER BY COUNT([Region].[Name]) DESC

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[UniqueMapRegionName]()
	RETURNS INT
AS
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1
		@retVal = COUNT([Region].[Name])
	FROM [Project].dbo.[Region]
	LEFT JOIN [Project].dbo.[City] ON [Region].[MainCityID] = [City].[CityID]
	LEFT JOIN [Project].dbo.[Province] ON [Province].[DefaultCityID] = [City].[CityID]
	WHERE [Province].[DefaultCityID] IS NOT NULL
	GROUP BY [MapID], [Region].[Name]
	ORDER BY COUNT([Region].[Name]) DESC

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[UniqueSessionCivilizationName]()
	RETURNS INT
AS
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1
		@retVal = COUNT([Civilization].[Name])
	FROM [Project].dbo.[Civilization]
	LEFT JOIN [Project].dbo.[City] ON [Civilization].[CapitalCityID] = [City].[CityID]
	LEFT JOIN [Project].dbo.[MutableProvinces] ON [MutableProvinces].[CityID] = [City].[CityID]
	WHERE [MutableProvinces].[CityID] IS NOT NULL
	GROUP BY [GameSessionID], [Civilization].[Name]
	ORDER BY COUNT([Civilization].[Name]) DESC

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[UniqueMapCivilizationName]()
	RETURNS INT
AS
BEGIN
	DECLARE @retVal INT

	SELECT TOP 1
		@retVal = COUNT([Civilization].[Name])
	FROM [Project].dbo.[Civilization]
	LEFT JOIN [Project].dbo.[City] ON [Civilization].[CapitalCityID] = [City].[CityID]
	LEFT JOIN [Project].dbo.[Province] ON [Province].[DefaultCityID] = [City].[CityID]
	WHERE [Province].[DefaultCityID] IS NOT NULL
	GROUP BY [MapID], [Civilization].[Name]
	ORDER BY COUNT([Civilization].[Name]) DESC

	RETURN @retVal
END
GO

CREATE OR ALTER FUNCTION dbo.[CheckCorrectType](
	@buildingID INT,
	@correctTypeID INT
) RETURNS BIT
AS
BEGIN
	DECLARE @retVal BIT = 0

	IF EXISTS (
		SELECT *
		FROM [Project].dbo.[Building]
		WHERE [BuildingID] = BuildingID AND [BuildingTypeID] = @correctTypeID
	) BEGIN
		SET @retVal = 1
	END

	RETURN @retVal
END
GO

USE [master]