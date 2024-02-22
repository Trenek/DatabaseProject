USE [Project]

GO

INSERT INTO [Project].dbo.[User] ([Login], [Password], [Email]) VALUES 
	('admin', 'ImpossiblePassword123', 'admin@gmail.com'),
	('Trenek', 'VeryHardPassword123', 'Trenek@gmail.com'),
	('pudzian', 'VeryHardPassword123', 'pudzian@pudzian.com'),
	('Czarodziej', 'CzaryMary123', 'Placki@lubie.com')

GO

USE [master]