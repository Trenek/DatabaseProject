USE [Project]

GO

ALTER TABLE [Project].dbo.[Game Session] ADD
	CONSTRAINT [FK_Game_Session_User] FOREIGN KEY ([CreatorID]) REFERENCES [Project].dbo.[User]([UserID]),
	CONSTRAINT [FK_Game_Session_Map] FOREIGN KEY ([MapID]) REFERENCES [Project].dbo.[Map]([MapID])

--User

ALTER TABLE [Project].dbo.[Player] ADD
	CONSTRAINT [FK_Player_User] FOREIGN KEY ([UserID]) REFERENCES [Project].dbo.[User]([UserID]),
	CONSTRAINT [FK_Player_GameSession] FOREIGN KEY ([SessionID]) REFERENCES [Project].dbo.[Game Session]([SessionID]),
	CONSTRAINT [FK_Player_Civilization] FOREIGN KEY ([CivilizationID]) REFERENCES [Project].dbo.[Civilization]([CivilizationID])

ALTER TABLE [Project].dbo.[Civilization] ADD
	CONSTRAINT [FK_Civilization_City] FOREIGN KEY ([CapitalCityID]) REFERENCES [Project].dbo.[City]([CityID])

--DiplomaticStates

ALTER TABLE [Project].dbo.[Diplomacy] ADD
	CONSTRAINT [FK_Diplomacy_DiplomaticStates] FOREIGN KEY ([DiplomaticStateID]) REFERENCES [Project].dbo.[DiplomaticStates]([DiplomaticStateID]),
	CONSTRAINT [FK_Diplomacy_Civilization1] FOREIGN KEY ([Civilization1ID]) REFERENCES [Project].dbo.[Civilization]([CivilizationID]),
	CONSTRAINT [FK_Diplomacy_Civilization2] FOREIGN KEY ([Civilization2ID]) REFERENCES [Project].dbo.[Civilization]([CivilizationID])

ALTER TABLE [Project].dbo.[Province] ADD
	CONSTRAINT [FK_Province_DefaultRegion] FOREIGN KEY ([DefaultRegionID]) REFERENCES [Project].dbo.[Region]([RegionID]),
	CONSTRAINT [FK_Province_Terrain] FOREIGN KEY ([TerrainID]) REFERENCES [Project].dbo.[Terrain]([TerrainID]),
	CONSTRAINT [FK_Province_Map] FOREIGN KEY ([MapID]) REFERENCES [Project].dbo.[Map]([MapID]),
	CONSTRAINT [FK_Provinces_City] FOREIGN KEY ([DefaultCityID]) REFERENCES [Project].dbo.[City]([CityID])

ALTER TABLE [Project].dbo.[Region] ADD
	CONSTRAINT [FK_Region_Civilization] FOREIGN KEY ([CivilizationID]) REFERENCES [Project].dbo.[Civilization]([CivilizationID]),
	CONSTRAINT [FK_Region_City] FOREIGN KEY ([MainCityID]) REFERENCES [Project].dbo.[City]([CityID])

ALTER TABLE [Project].dbo.[MutableProvinces] ADD
	CONSTRAINT [FK_MutableProvinces_Province] FOREIGN KEY ([ProvinceID]) REFERENCES [Project].dbo.[Province]([ProvinceID]),
	CONSTRAINT [FK_MutableProvinces_Region] FOREIGN KEY ([RegionID]) REFERENCES [Project].dbo.[Region]([RegionID]),
	CONSTRAINT [FK_MutableProvinces_GameSession] FOREIGN KEY ([GameSessionID]) REFERENCES [Project].dbo.[Game Session]([SessionID]),
	CONSTRAINT [FK_MutableProvinces_City] FOREIGN KEY ([CityID]) REFERENCES [Project].dbo.[City]([CityID])

-- Map

--Terrain

ALTER TABLE [Project].dbo.[River] ADD
	CONSTRAINT [FK_River_Province1] FOREIGN KEY ([ProvinceID]) REFERENCES [Project].dbo.[Province]([ProvinceID]),
	CONSTRAINT [FK_River_Province2] FOREIGN KEY ([FromID]) REFERENCES [Project].dbo.[Province]([ProvinceID]),
	CONSTRAINT [FK_River_Province3] FOREIGN KEY ([ToID]) REFERENCES [Project].dbo.[Province]([ProvinceID])

--City

ALTER TABLE [Project].dbo.[ConstructCity] ADD
	CONSTRAINT [FK_ConstructCity_MutableProvince] FOREIGN KEY ([MutableProvinceID]) REFERENCES [Project].dbo.[MutableProvinces]([ID])

ALTER TABLE [Project].dbo.[Road] ADD
	CONSTRAINT [FK_Road_City1] FOREIGN KEY ([City1ID]) REFERENCES [Project].dbo.[City]([CityID]),
	CONSTRAINT [FK_Road_City2] FOREIGN KEY ([City2ID]) REFERENCES [Project].dbo.[City]([CityID])

ALTER TABLE [Project].dbo.[Barrack] ADD
	CONSTRAINT [FK_Barrack_Building] FOREIGN KEY ([BuildingID]) REFERENCES [Project].dbo.[Building]([BuildingID])

--MilitaryUnitType

ALTER TABLE [Project].dbo.[Military_Unit] ADD
	CONSTRAINT [FK_Military_Unit_Civilization] FOREIGN KEY ([CivilizationID]) REFERENCES [Project].dbo.[Civilization]([CivilizationID]),
	CONSTRAINT [FK_Military_Unit_Barrack] FOREIGN KEY ([BarrackID]) REFERENCES [Project].dbo.[Barrack]([BarrackID]),
	CONSTRAINT [FK_Military_Unit_Military_Unit_Type] FOREIGN KEY ([MilitaryUnitTypeID]) REFERENCES [Project].dbo.[Military_Unit_type]([MilitaryUnitTypeID]);

ALTER TABLE [Project].dbo.[Building] ADD
	CONSTRAINT [FK_Building_City] FOREIGN KEY ([CityID]) REFERENCES [Project].dbo.[City]([CityID]),
	CONSTRAINT [FK_Building_BuildingType] FOREIGN KEY ([BuildingTypeID]) REFERENCES [Project].dbo.[BuildingType]([BuildingTypeID])

ALTER TABLE [Project].dbo.[ConstructionTime] ADD
	CONSTRAINT [FK_ConstructionTime_BuildingType] FOREIGN KEY ([BuildingTypeID]) REFERENCES [Project].dbo.[BuildingType]([BuildingTypeID])

ALTER TABLE [Project].dbo.[Construction] ADD
	CONSTRAINT [FK_Construction_City] FOREIGN KEY ([CityID]) REFERENCES [Project].dbo.[City]([CityID]),
	CONSTRAINT [FK_Construction_BuildingType] FOREIGN KEY ([BuildingTypeID]) REFERENCES [Project].dbo.[BuildingType]([BuildingTypeID])

--Resource

ALTER TABLE [Project].dbo.[StorageItem] ADD
	CONSTRAINT [FK_StorageItem_Resource] FOREIGN KEY ([ResourceID]) REFERENCES [Project].dbo.[Resource]([ResourceID]),
	CONSTRAINT [FK_StorageItem_Storage] FOREIGN KEY ([StorageID]) REFERENCES [Project].dbo.[Storage]([StorageID])

ALTER TABLE [Project].dbo.[Storage] ADD
	CONSTRAINT [FK_Storage_Building] FOREIGN KEY ([BuildingID]) REFERENCES [Project].dbo.[Building]([BuildingID])

ALTER TABLE [Project].dbo.[Market] ADD
	CONSTRAINT [FK_Market_Building] FOREIGN KEY ([BuildingID]) REFERENCES [Project].dbo.[Building]([BuildingID])

ALTER TABLE [Project].dbo.[Trader] ADD
	CONSTRAINT [FK_Trader_Market1] FOREIGN KEY ([Market1ID]) REFERENCES [Project].dbo.[Market]([MarketID]),
	CONSTRAINT [FK_Trader_Market2] FOREIGN KEY ([Market2ID]) REFERENCES [Project].dbo.[Market]([MarketID]),
	CONSTRAINT [FK_Trader_Resource] FOREIGN KEY ([ResourceID]) REFERENCES [Project].dbo.[Resource]([ResourceID])

ALTER TABLE [Project].dbo.[Cultural_Unit] ADD
	CONSTRAINT [FK_Cultural_Unit] FOREIGN KEY ([CivilizationID]) REFERENCES [Project].dbo.[Civilization]([CivilizationID])

ALTER TABLE [Project].dbo.[Theatre_Square] ADD
	CONSTRAINT [FK_Theatre_Square_Building] FOREIGN KEY ([BuildingID]) REFERENCES [Project].dbo.[Building]([BuildingID])

ALTER TABLE [Project].dbo.[Masterpiece] ADD
	CONSTRAINT [FK_Masterpiece_Cultural_Unit] FOREIGN KEY ([CulturalUnitID]) REFERENCES [Project].dbo.[Cultural_Unit]([CulturalUnitID]),
	CONSTRAINT [FK_Masterpiece_Theatre_Square] FOREIGN KEY ([TheatreID]) REFERENCES [Project].dbo.[Theatre_Square]([TheatreID])

GO

USE [master]