USE [Project]

GO

INSERT INTO [Project].dbo.[BuildingType]([TypeName], [MaxLevel], [BasicTax], [BasicLevies], [Price]) VALUES 
	('Military Academy',	10,		-10,	500,	100),
	('Barrack',				8,		-10,	100,	50), -- Tabelka 2
	('Marketplace',			7,		10,		0,		100),
	('Farm',				6,		40,		-100,	10),
	('Magazine',			10,		-10,	0,		100), -- Tabelka 5
	('Market',				10,		20,		0,		1000), -- Tabelka 6
	('Theatre',				10,		-20,	-100,	1000), --Tabelka 7
	('Houses',				100,	20,		10,		10)

GO

USE [master]