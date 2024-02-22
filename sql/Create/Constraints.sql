USE [Project]

GO

ALTER TABLE [Project].dbo.[Game Session] ADD
	CONSTRAINT [GameSession_UQ_Name_Creator] UNIQUE([SaveName], [CreatorID])

ALTER TABLE [Project].dbo.[User] ADD
	CONSTRAINT [User_UQ_Login] UNIQUE([Login]),
	CONSTRAINT [User_UQ_Email] UNIQUE([Email]),

	CONSTRAINT [User_CK_Email] CHECK (dbo.[CheckIfStringIsEmail]([Email]) = 1),
	CONSTRAINT [User_CK_Password] CHECK (dbo.[CheckPasswordRequirements]([Password]) = 0)

ALTER TABLE [Project].dbo.[Player] ADD
	CONSTRAINT [Player_UQ_User_Game] UNIQUE([UserID], [SessionID]),
	CONSTRAINT [Player_UQ_Civilization] CHECK (dbo.[CheckCivilizationUnique]() <= 1)

ALTER TABLE [Project].dbo.[Civilization] ADD
	CONSTRAINT [Civilization_UQ_City] UNIQUE([CapitalCityID]),
	CONSTRAINT [Civilization_UQ_NameInSession] CHECK(dbo.[UniqueSessionCivilizationName]() <= 1),
	CONSTRAINT [Civilization_UQ_NameOnMap] CHECK(dbo.[UniqueMapCivilizationName]() <= 1)

ALTER TABLE [Project].dbo.[DiplomaticStates] ADD
	CONSTRAINT [DiplomaticStates_UQ_Name] UNIQUE([Name])

ALTER TABLE [Project].dbo.[Diplomacy] ADD
	CONSTRAINT [Diplomacy_UQ_One_Two] UNIQUE([Civilization1ID], [Civilization2ID])

ALTER TABLE [Project].dbo.[Province] ADD
	CONSTRAINT [Province_UQ_Map_X_Y] UNIQUE([MapID], [CoordinateX], [CoordinateY]),
	CONSTRAINT [Province_UQ_City] CHECK(dbo.[CheckDefaultCity]() <= 1)

ALTER TABLE [Project].dbo.[Region] ADD
	CONSTRAINT [Region_UQ_City] UNIQUE([MainCityID]),
	CONSTRAINT [Region_UQ_NameInSession] CHECK(dbo.[UniqueSessionRegionName]() <= 1),
	CONSTRAINT [Region_UQ_NameOnMap] CHECK (dbo.[UniqueMapRegionName]() <= 1)

ALTER TABLE [Project].dbo.[MutableProvinces] ADD
	CONSTRAINT [MutableProvinces_UQ_Province_Region] CHECK(dbo.[CheckProvinceRegionUQ]() <= 1),
	CONSTRAINT [MutableProvinces_UQ_Province_GameSession] UNIQUE([ProvinceID], [GameSessionID]),
	CONSTRAINT [MutableProvinces_UQ_City] CHECK(dbo.[CheckCity]() <= 1)

ALTER TABLE [Project].dbo.[Map] ADD
	CONSTRAINT [Map_UQ_Name] UNIQUE([Name])

ALTER TABLE [Project].dbo.[Terrain] ADD
	CONSTRAINT [Terrain_UQ_Name] UNIQUE([Name])

ALTER TABLE [Project].dbo.[River] ADD
	CONSTRAINT [River_UQ_Province_From_To] UNIQUE([ProvinceID], [FromID], [ToID])

ALTER TABLE [Project].dbo.[City] ADD
	CONSTRAINT [City_UQ_NameOnMap] CHECK(dbo.[UniqueMapCityName]() <= 1),
	CONSTRAINT [City_UQ_NameInSession] CHECK(dbo.[UniqueSessionCityName]() <= 1)

ALTER TABLE [Project].dbo.[ConstructCity] ADD
	CONSTRAINT [ConstructCity_UQ_MutableProvinceID] UNIQUE([MutableProvinceID])

ALTER TABLE [Project].dbo.[Road] ADD
	CONSTRAINT [Road_UQ_City1_City2] UNIQUE([City1ID], [City2ID])

--Barrack

ALTER TABLE [Project].dbo.[Barrack] ADD
	CONSTRAINT [Barrack_UQ_Building] UNIQUE([BuildingID]),
	CONSTRAINT [Barrack_CK_BuildingType] CHECK(dbo.[CheckCorrectType]([BuildingID], 2) = 1)

--Military_Unit_type

--Military_Unit

ALTER TABLE [Project].dbo.[BuildingType] ADD
	CONSTRAINT [BuildingType_UQ_Name] UNIQUE([TypeName]),

	CONSTRAINT [BuildingType_CK_Price] CHECK([Price] > 0),
	CONSTRAINT [BuildingType_CK_MaxLevel] CHECK([MaxLevel] > 0)
	
ALTER TABLE [Project].dbo.[Building] ADD
	CONSTRAINT [Building_UQ_Type_City] UNIQUE([BuildingTypeID], [CityID])
	
ALTER TABLE [Project].dbo.[ConstructionTime] ADD
	CONSTRAINT [ConstructionTime_UQ_BuildingType] UNIQUE([BuildingTypeID])

ALTER TABLE [Project].dbo.[Construction] ADD
	CONSTRAINT [Construction_UQ_City_BuildingType] UNIQUE([CityID], [BuildingTypeID])

--Resource

ALTER TABLE [Project].dbo.[Resource] ADD
	CONSTRAINT [Resource_UQ_Name] UNIQUE([Name])

-- StorageItem

ALTER TABLE [Project].dbo.[Storage] ADD
	CONSTRAINT [Storage_UQ_Building_Resource] UNIQUE([BuildingID]),

	CONSTRAINT [Storage_CK_BuildingType] CHECK(dbo.[CheckCorrectType]([BuildingID], 5) = 1),
	CONSTRAINT [Storage_CK_Capacity] CHECK([Capacity] > 0)

ALTER TABLE [Project].dbo.[Market] ADD
	CONSTRAINT [Market_UQ_Building] UNIQUE([BuildingID]),
	CONSTRAINT [Market_CK_BuildingType] CHECK(dbo.[CheckCorrectType]([BuildingID], 6) = 1)

--Trader ??

--Cultural Unit ?

ALTER TABLE [Project].dbo.[Theatre_Square] ADD
	CONSTRAINT [Theatre_Square_CK_BuildingType] CHECK(dbo.[CheckCorrectType]([BuildingID], 7) = 1)

--Masterpiece?

GO

USE [master]