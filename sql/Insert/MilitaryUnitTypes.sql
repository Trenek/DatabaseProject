USE [Project]

GO

INSERT INTO [Project].dbo.[Military_Unit_type]([MilitaryUnitTypeID], [TypeName], [Health], [Damage], [ProductionCost], [PurchasePrice], [AttackType]) VALUES
	(1, 'Slinger', 80, 15, 35, 140, 'Ranged'),
	(2, 'Archer', 100, 25, 60, 240, 'Ranged'),
	(3, 'Crossbowmen', 150, 40, 180, 720, 'Ranged'),
	(4, 'Warrior', 120, 20, 40, 160, 'Melee'),
	(5, 'Swordsmen', 245, 35, 90, 360, 'Melee'),
	(6, 'Men-at-Arm', 340, 45, 160, 640, 'Melee'),
	(7, 'Horsemen', 250, 36, 80, 320, 'Light Cavalry'),
	(8, 'Cossack', 500, 67, 340, 1360, 'Light Cavalry'),
	(9, 'Catapult', 150, 35, 120, 480, 'Siege'),
	(10, 'Pikemen', 200, 25, 65, 260, 'Anti-Cavalry');

GO

USE [master]