USE [Project]

GO

INSERT INTO [Project].dbo.[Map]([Name], [Width], [Height], [StartingDate]) VALUES
	('Map 1', 25, 25, '1000-01-01')

INSERT INTO [Project].dbo.[Province]([CoordinateX], [CoordinateY], [MapID], [DefaultRegionID], [TerrainID]) VALUES
	(0, 0, 1, NULL, 8),
	(1, 0, 1, NULL, 8),
	(2, 0, 1, NULL, 8),
	(3, 0, 1, NULL, 8),
	(4, 0, 1, NULL, 8),
	(5, 0, 1, NULL, 8),
	(6, 0, 1, NULL, 8),
	(7, 0, 1, NULL, 8),
	(8, 0, 1, NULL, 8),
	(9, 0, 1, NULL, 8),
	(10, 0, 1, NULL, 8),
	(11, 0, 1, NULL, 8),
	(12, 0, 1, NULL, 8),
	(13, 0, 1, NULL, 8),
	(14, 0, 1, NULL, 8),
	(15, 0, 1, NULL, 8),
	(16, 0, 1, NULL, 2),
	(17, 0, 1, NULL, 2),
	(18, 0, 1, NULL, 2),
	(19, 0, 1, NULL, 2),
	(20, 0, 1, NULL, 2),
	(21, 0, 1, NULL, 2),
	(22, 0, 1, NULL, 2),
	(23, 0, 1, NULL, 2),
	(24, 0, 1, NULL, 2),
	(0, 1, 1, NULL, 8),
	(1, 1, 1, NULL, 8),
	(2, 1, 1, NULL, 8),
	(3, 1, 1, NULL, 8),
	(4, 1, 1, NULL, 8),
	(5, 1, 1, NULL, 4),
	(6, 1, 1, NULL, 4),
	(7, 1, 1, NULL, 2),
	(8, 1, 1, NULL, 2),
	(9, 1, 1, NULL, 4),
	(10, 1, 1, NULL, 6),
	(11, 1, 1, NULL, 4),
	(12, 1, 1, NULL, 6),
	(13, 1, 1, NULL, 6),
	(14, 1, 1, NULL, 4),
	(15, 1, 1, NULL, 4),
	(16, 1, 1, NULL, 6),
	(17, 1, 1, NULL, 6),
	(18, 1, 1, NULL, 2),
	(19, 1, 1, NULL, 4),
	(20, 1, 1, NULL, 2),
	(21, 1, 1, NULL, 2),
	(22, 1, 1, NULL, 2),
	(23, 1, 1, NULL, 8),
	(24, 1, 1, NULL, 8),
	(0, 2, 1, NULL, 8),
	(1, 2, 1, NULL, 8),
	(2, 2, 1, NULL, 8),
	(3, 2, 1, NULL, 8),
	(4, 2, 1, NULL, 8),
	(5, 2, 1, NULL, 2),
	(6, 2, 1, NULL, 4),
	(7, 2, 1, NULL, 2),
	(8, 2, 1, NULL, 2),
	(9, 2, 1, NULL, 4),
	(10, 2, 1, NULL, 4),
	(11, 2, 1, NULL, 4),
	(12, 2, 1, NULL, 4),
	(13, 2, 1, NULL, 2),
	(14, 2, 1, NULL, 2),
	(15, 2, 1, NULL, 2),
	(16, 2, 1, NULL, 4),
	(17, 2, 1, NULL, 4),
	(18, 2, 1, NULL, 4),
	(19, 2, 1, NULL, 6),
	(20, 2, 1, NULL, 4),
	(21, 2, 1, NULL, 6),
	(22, 2, 1, NULL, 4),
	(23, 2, 1, NULL, 8),
	(24, 2, 1, NULL, 8),
	(0, 3, 1, NULL, 8),
	(1, 3, 1, NULL, 8),
	(2, 3, 1, NULL, 8),
	(3, 3, 1, NULL, 8),
	(4, 3, 1, NULL, 8),
	(5, 3, 1, NULL, 2),
	(6, 3, 1, NULL, 6),
	(7, 3, 1, NULL, 2),
	(8, 3, 1, NULL, 4),
	(9, 3, 1, NULL, 4),
	(10, 3, 1, NULL, 2),
	(11, 3, 1, NULL, 2),
	(12, 3, 1, NULL, 4),
	(13, 3, 1, NULL, 4),
	(14, 3, 1, NULL, 6),
	(15, 3, 1, NULL, 2),
	(16, 3, 1, NULL, 2),
	(17, 3, 1, NULL, 4),
	(18, 3, 1, NULL, 2),
	(19, 3, 1, NULL, 4),
	(20, 3, 1, NULL, 4),
	(21, 3, 1, NULL, 4),
	(22, 3, 1, NULL, 2),
	(23, 3, 1, NULL, 8),
	(24, 3, 1, NULL, 8),
	(0, 4, 1, NULL, 8),
	(1, 4, 1, NULL, 8),
	(2, 4, 1, NULL, 8),
	(3, 4, 1, NULL, 8),
	(4, 4, 1, NULL, 8),
	(5, 4, 1, NULL, 8),
	(6, 4, 1, NULL, 4),
	(7, 4, 1, NULL, 2),
	(8, 4, 1, NULL, 4),
	(9, 4, 1, NULL, 2),
	(10, 4, 1, NULL, 2),
	(11, 4, 1, NULL, 4),
	(12, 4, 1, NULL, 2),
	(13, 4, 1, NULL, 2),
	(14, 4, 1, NULL, 2),
	(15, 4, 1, NULL, 2),
	(16, 4, 1, NULL, 2),
	(17, 4, 1, NULL, 2),
	(18, 4, 1, NULL, 4),
	(19, 4, 1, NULL, 2),
	(20, 4, 1, NULL, 4),
	(21, 4, 1, NULL, 2),
	(22, 4, 1, NULL, 8),
	(23, 4, 1, NULL, 8),
	(24, 4, 1, NULL, 8),
	(0, 5, 1, NULL, 8),
	(1, 5, 1, NULL, 8),
	(2, 5, 1, NULL, 8),
	(3, 5, 1, NULL, 8),
	(4, 5, 1, NULL, 8),
	(5, 5, 1, NULL, 4),
	(6, 5, 1, NULL, 4),
	(7, 5, 1, NULL, 4),
	(8, 5, 1, NULL, 2),
	(9, 5, 1, NULL, 2),
	(10, 5, 1, NULL, 2),
	(11, 5, 1, NULL, 4),
	(12, 5, 1, NULL, 4),
	(13, 5, 1, NULL, 4),
	(14, 5, 1, NULL, 2),
	(15, 5, 1, NULL, 2),
	(16, 5, 1, NULL, 2),
	(17, 5, 1, NULL, 2),
	(18, 5, 1, NULL, 4),
	(19, 5, 1, NULL, 2),
	(20, 5, 1, NULL, 8),
	(21, 5, 1, NULL, 8),
	(22, 5, 1, NULL, 8),
	(23, 5, 1, NULL, 8),
	(24, 5, 1, NULL, 8),
	(0, 6, 1, NULL, 8),
	(1, 6, 1, NULL, 8),
	(2, 6, 1, NULL, 8),
	(3, 6, 1, NULL, 8),
	(4, 6, 1, NULL, 8),
	(5, 6, 1, NULL, 8),
	(6, 6, 1, NULL, 4),
	(7, 6, 1, NULL, 4),
	(8, 6, 1, NULL, 2),
	(9, 6, 1, NULL, 2),
	(10, 6, 1, NULL, 6),
	(11, 6, 1, NULL, 2),
	(12, 6, 1, NULL, 4),
	(13, 6, 1, NULL, 6),
	(14, 6, 1, NULL, 2),
	(15, 6, 1, NULL, 2),
	(16, 6, 1, NULL, 4),
	(17, 6, 1, NULL, 2),
	(18, 6, 1, NULL, 4),
	(19, 6, 1, NULL, 2),
	(20, 6, 1, NULL, 8),
	(21, 6, 1, NULL, 8),
	(22, 6, 1, NULL, 8),
	(23, 6, 1, NULL, 8),
	(24, 6, 1, NULL, 8),
	(0, 7, 1, NULL, 8),
	(1, 7, 1, NULL, 8),
	(2, 7, 1, NULL, 8),
	(3, 7, 1, NULL, 8),
	(4, 7, 1, NULL, 8),
	(5, 7, 1, NULL, 2),
	(6, 7, 1, NULL, 2),
	(7, 7, 1, NULL, 4),
	(8, 7, 1, NULL, 2),
	(9, 7, 1, NULL, 6),
	(10, 7, 1, NULL, 4),
	(11, 7, 1, NULL, 2),
	(12, 7, 1, NULL, 2),
	(13, 7, 1, NULL, 2),
	(14, 7, 1, NULL, 4),
	(15, 7, 1, NULL, 4),
	(16, 7, 1, NULL, 2),
	(17, 7, 1, NULL, 4),
	(18, 7, 1, NULL, 8),
	(19, 7, 1, NULL, 8),
	(20, 7, 1, NULL, 8),
	(21, 7, 1, NULL, 8),
	(22, 7, 1, NULL, 8),
	(23, 7, 1, NULL, 8),
	(24, 7, 1, NULL, 8),
	(0, 8, 1, NULL, 8),
	(1, 8, 1, NULL, 8),
	(2, 8, 1, NULL, 8),
	(3, 8, 1, NULL, 8),
	(4, 8, 1, NULL, 8),
	(5, 8, 1, NULL, 8),
	(6, 8, 1, NULL, 4),
	(7, 8, 1, NULL, 2),
	(8, 8, 1, NULL, 4),
	(9, 8, 1, NULL, 2),
	(10, 8, 1, NULL, 2),
	(11, 8, 1, NULL, 2),
	(12, 8, 1, NULL, 2),
	(13, 8, 1, NULL, 2),
	(14, 8, 1, NULL, 2),
	(15, 8, 1, NULL, 2),
	(16, 8, 1, NULL, 2),
	(17, 8, 1, NULL, 4),
	(18, 8, 1, NULL, 8),
	(19, 8, 1, NULL, 8),
	(20, 8, 1, NULL, 8),
	(21, 8, 1, NULL, 8),
	(22, 8, 1, NULL, 4),
	(23, 8, 1, NULL, 4),
	(24, 8, 1, NULL, 8),
	(0, 9, 1, NULL, 8),
	(1, 9, 1, NULL, 8),
	(2, 9, 1, NULL, 8),
	(3, 9, 1, NULL, 8),
	(4, 9, 1, NULL, 8),
	(5, 9, 1, NULL, 2),
	(6, 9, 1, NULL, 4),
	(7, 9, 1, NULL, 2),
	(8, 9, 1, NULL, 2),
	(9, 9, 1, NULL, 2),
	(10, 9, 1, NULL, 2),
	(11, 9, 1, NULL, 4),
	(12, 9, 1, NULL, 2),
	(13, 9, 1, NULL, 2),
	(14, 9, 1, NULL, 2),
	(15, 9, 1, NULL, 2),
	(16, 9, 1, NULL, 2),
	(17, 9, 1, NULL, 2),
	(18, 9, 1, NULL, 8),
	(19, 9, 1, NULL, 8),
	(20, 9, 1, NULL, 4),
	(21, 9, 1, NULL, 8),
	(22, 9, 1, NULL, 8),
	(23, 9, 1, NULL, 8),
	(24, 9, 1, NULL, 8),
	(0, 10, 1, NULL, 8),
	(1, 10, 1, NULL, 8),
	(2, 10, 1, NULL, 8),
	(3, 10, 1, NULL, 8),
	(4, 10, 1, NULL, 8),
	(5, 10, 1, NULL, 4),
	(6, 10, 1, NULL, 4),
	(7, 10, 1, NULL, 2),
	(8, 10, 1, NULL, 2),
	(9, 10, 1, NULL, 2),
	(10, 10, 1, NULL, 2),
	(11, 10, 1, NULL, 2),
	(12, 10, 1, NULL, 4),
	(13, 10, 1, NULL, 4),
	(14, 10, 1, NULL, 2),
	(15, 10, 1, NULL, 4),
	(16, 10, 1, NULL, 2),
	(17, 10, 1, NULL, 2),
	(18, 10, 1, NULL, 4),
	(19, 10, 1, NULL, 8),
	(20, 10, 1, NULL, 8),
	(21, 10, 1, NULL, 8),
	(22, 10, 1, NULL, 8),
	(23, 10, 1, NULL, 8),
	(24, 10, 1, NULL, 8),
	(0, 11, 1, NULL, 8),
	(1, 11, 1, NULL, 8),
	(2, 11, 1, NULL, 8),
	(3, 11, 1, NULL, 8),
	(4, 11, 1, NULL, 2),
	(5, 11, 1, NULL, 2),
	(6, 11, 1, NULL, 2),
	(7, 11, 1, NULL, 2),
	(8, 11, 1, NULL, 2),
	(9, 11, 1, NULL, 4),
	(10, 11, 1, NULL, 2),
	(11, 11, 1, NULL, 2),
	(12, 11, 1, NULL, 2),
	(13, 11, 1, NULL, 4),
	(14, 11, 1, NULL, 2),
	(15, 11, 1, NULL, 4),
	(16, 11, 1, NULL, 2),
	(17, 11, 1, NULL, 8),
	(18, 11, 1, NULL, 8),
	(19, 11, 1, NULL, 8),
	(20, 11, 1, NULL, 8),
	(21, 11, 1, NULL, 8),
	(22, 11, 1, NULL, 8),
	(23, 11, 1, NULL, 8),
	(24, 11, 1, NULL, 8),
	(0, 12, 1, NULL, 8),
	(1, 12, 1, NULL, 8),
	(2, 12, 1, NULL, 8),
	(3, 12, 1, NULL, 8),
	(4, 12, 1, NULL, 8),
	(5, 12, 1, NULL, 2),
	(6, 12, 1, NULL, 4),
	(7, 12, 1, NULL, 4),
	(8, 12, 1, NULL, 2),
	(9, 12, 1, NULL, 2),
	(10, 12, 1, NULL, 4),
	(11, 12, 1, NULL, 2),
	(12, 12, 1, NULL, 4),
	(13, 12, 1, NULL, 4),
	(14, 12, 1, NULL, 4),
	(15, 12, 1, NULL, 2),
	(16, 12, 1, NULL, 2),
	(17, 12, 1, NULL, 2),
	(18, 12, 1, NULL, 8),
	(19, 12, 1, NULL, 8),
	(20, 12, 1, NULL, 8),
	(21, 12, 1, NULL, 8),
	(22, 12, 1, NULL, 8),
	(23, 12, 1, NULL, 8),
	(24, 12, 1, NULL, 8),
	(0, 13, 1, NULL, 8),
	(1, 13, 1, NULL, 8),
	(2, 13, 1, NULL, 8),
	(3, 13, 1, NULL, 8),
	(4, 13, 1, NULL, 8),
	(5, 13, 1, NULL, 4),
	(6, 13, 1, NULL, 4),
	(7, 13, 1, NULL, 2),
	(8, 13, 1, NULL, 1),
	(9, 13, 1, NULL, 2),
	(10, 13, 1, NULL, 4),
	(11, 13, 1, NULL, 4),
	(12, 13, 1, NULL, 4),
	(13, 13, 1, NULL, 4),
	(14, 13, 1, NULL, 2),
	(15, 13, 1, NULL, 8),
	(16, 13, 1, NULL, 8),
	(17, 13, 1, NULL, 8),
	(18, 13, 1, NULL, 8),
	(19, 13, 1, NULL, 8),
	(20, 13, 1, NULL, 8),
	(21, 13, 1, NULL, 8),
	(22, 13, 1, NULL, 8),
	(23, 13, 1, NULL, 8),
	(24, 13, 1, NULL, 8),
	(0, 14, 1, NULL, 8),
	(1, 14, 1, NULL, 8),
	(2, 14, 1, NULL, 8),
	(3, 14, 1, NULL, 8),
	(4, 14, 1, NULL, 8),
	(5, 14, 1, NULL, 8),
	(6, 14, 1, NULL, 8),
	(7, 14, 1, NULL, 8),
	(8, 14, 1, NULL, 8),
	(9, 14, 1, NULL, 1),
	(10, 14, 1, NULL, 4),
	(11, 14, 1, NULL, 6),
	(12, 14, 1, NULL, 8),
	(13, 14, 1, NULL, 8),
	(14, 14, 1, NULL, 8),
	(15, 14, 1, NULL, 8),
	(16, 14, 1, NULL, 8),
	(17, 14, 1, NULL, 8),
	(18, 14, 1, NULL, 8),
	(19, 14, 1, NULL, 8),
	(20, 14, 1, NULL, 8),
	(21, 14, 1, NULL, 8),
	(22, 14, 1, NULL, 8),
	(23, 14, 1, NULL, 8),
	(24, 14, 1, NULL, 4),
	(0, 15, 1, NULL, 8),
	(1, 15, 1, NULL, 8),
	(2, 15, 1, NULL, 8),
	(3, 15, 1, NULL, 8),
	(4, 15, 1, NULL, 8),
	(5, 15, 1, NULL, 8),
	(6, 15, 1, NULL, 8),
	(7, 15, 1, NULL, 8),
	(8, 15, 1, NULL, 8),
	(9, 15, 1, NULL, 8),
	(10, 15, 1, NULL, 8),
	(11, 15, 1, NULL, 8),
	(12, 15, 1, NULL, 8),
	(13, 15, 1, NULL, 8),
	(14, 15, 1, NULL, 8),
	(15, 15, 1, NULL, 8),
	(16, 15, 1, NULL, 8),
	(17, 15, 1, NULL, 8),
	(18, 15, 1, NULL, 8),
	(19, 15, 1, NULL, 4),
	(20, 15, 1, NULL, 4),
	(21, 15, 1, NULL, 4),
	(22, 15, 1, NULL, 6),
	(23, 15, 1, NULL, 4),
	(24, 15, 1, NULL, 6),
	(0, 16, 1, NULL, 8),
	(1, 16, 1, NULL, 8),
	(2, 16, 1, NULL, 8),
	(3, 16, 1, NULL, 8),
	(4, 16, 1, NULL, 8),
	(5, 16, 1, NULL, 8),
	(6, 16, 1, NULL, 8),
	(7, 16, 1, NULL, 8),
	(8, 16, 1, NULL, 8),
	(9, 16, 1, NULL, 8),
	(10, 16, 1, NULL, 4),
	(11, 16, 1, NULL, 8),
	(12, 16, 1, NULL, 8),
	(13, 16, 1, NULL, 8),
	(14, 16, 1, NULL, 8),
	(15, 16, 1, NULL, 8),
	(16, 16, 1, NULL, 8),
	(17, 16, 1, NULL, 2),
	(18, 16, 1, NULL, 2),
	(19, 16, 1, NULL, 4),
	(20, 16, 1, NULL, 2),
	(21, 16, 1, NULL, 2),
	(22, 16, 1, NULL, 1),
	(23, 16, 1, NULL, 4),
	(24, 16, 1, NULL, 1),
	(0, 17, 1, NULL, 8),
	(1, 17, 1, NULL, 8),
	(2, 17, 1, NULL, 8),
	(3, 17, 1, NULL, 8),
	(4, 17, 1, NULL, 8),
	(5, 17, 1, NULL, 8),
	(6, 17, 1, NULL, 8),
	(7, 17, 1, NULL, 8),
	(8, 17, 1, NULL, 8),
	(9, 17, 1, NULL, 2),
	(10, 17, 1, NULL, 4),
	(11, 17, 1, NULL, 4),
	(12, 17, 1, NULL, 2),
	(13, 17, 1, NULL, 2),
	(14, 17, 1, NULL, 8),
	(15, 17, 1, NULL, 8),
	(16, 17, 1, NULL, 4),
	(17, 17, 1, NULL, 4),
	(18, 17, 1, NULL, 2),
	(19, 17, 1, NULL, 2),
	(20, 17, 1, NULL, 1),
	(21, 17, 1, NULL, 1),
	(22, 17, 1, NULL, 1),
	(23, 17, 1, NULL, 4),
	(24, 17, 1, NULL, 1),
	(0, 18, 1, NULL, 8),
	(1, 18, 1, NULL, 8),
	(2, 18, 1, NULL, 8),
	(3, 18, 1, NULL, 8),
	(4, 18, 1, NULL, 8),
	(5, 18, 1, NULL, 8),
	(6, 18, 1, NULL, 8),
	(7, 18, 1, NULL, 8),
	(8, 18, 1, NULL, 8),
	(9, 18, 1, NULL, 2),
	(10, 18, 1, NULL, 2),
	(11, 18, 1, NULL, 2),
	(12, 18, 1, NULL, 4),
	(13, 18, 1, NULL, 4),
	(14, 18, 1, NULL, 1),
	(15, 18, 1, NULL, 6),
	(16, 18, 1, NULL, 4),
	(17, 18, 1, NULL, 2),
	(18, 18, 1, NULL, 2),
	(19, 18, 1, NULL, 2),
	(20, 18, 1, NULL, 1),
	(21, 18, 1, NULL, 4),
	(22, 18, 1, NULL, 4),
	(23, 18, 1, NULL, 4),
	(24, 18, 1, NULL, 1),
	(0, 19, 1, NULL, 8),
	(1, 19, 1, NULL, 8),
	(2, 19, 1, NULL, 8),
	(3, 19, 1, NULL, 8),
	(4, 19, 1, NULL, 8),
	(5, 19, 1, NULL, 8),
	(6, 19, 1, NULL, 8),
	(7, 19, 1, NULL, 8),
	(8, 19, 1, NULL, 2),
	(9, 19, 1, NULL, 4),
	(10, 19, 1, NULL, 4),
	(11, 19, 1, NULL, 4),
	(12, 19, 1, NULL, 4),
	(13, 19, 1, NULL, 6),
	(14, 19, 1, NULL, 4),
	(15, 19, 1, NULL, 1),
	(16, 19, 1, NULL, 1),
	(17, 19, 1, NULL, 1),
	(18, 19, 1, NULL, 1),
	(19, 19, 1, NULL, 4),
	(20, 19, 1, NULL, 1),
	(21, 19, 1, NULL, 1),
	(22, 19, 1, NULL, 1),
	(23, 19, 1, NULL, 1),
	(24, 19, 1, NULL, 1),
	(0, 20, 1, NULL, 8),
	(1, 20, 1, NULL, 8),
	(2, 20, 1, NULL, 8),
	(3, 20, 1, NULL, 8),
	(4, 20, 1, NULL, 8),
	(5, 20, 1, NULL, 8),
	(6, 20, 1, NULL, 8),
	(7, 20, 1, NULL, 2),
	(8, 20, 1, NULL, 2),
	(9, 20, 1, NULL, 2),
	(10, 20, 1, NULL, 4),
	(11, 20, 1, NULL, 2),
	(12, 20, 1, NULL, 4),
	(13, 20, 1, NULL, 1),
	(14, 20, 1, NULL, 4),
	(15, 20, 1, NULL, 1),
	(16, 20, 1, NULL, 1),
	(17, 20, 1, NULL, 1),
	(18, 20, 1, NULL, 1),
	(19, 20, 1, NULL, 1),
	(20, 20, 1, NULL, 1),
	(21, 20, 1, NULL, 1),
	(22, 20, 1, NULL, 1),
	(23, 20, 1, NULL, 1),
	(24, 20, 1, NULL, 1),
	(0, 21, 1, NULL, 8),
	(1, 21, 1, NULL, 8),
	(2, 21, 1, NULL, 8),
	(3, 21, 1, NULL, 8),
	(4, 21, 1, NULL, 8),
	(5, 21, 1, NULL, 2),
	(6, 21, 1, NULL, 2),
	(7, 21, 1, NULL, 4),
	(8, 21, 1, NULL, 2),
	(9, 21, 1, NULL, 4),
	(10, 21, 1, NULL, 2),
	(11, 21, 1, NULL, 4),
	(12, 21, 1, NULL, 4),
	(13, 21, 1, NULL, 1),
	(14, 21, 1, NULL, 1),
	(15, 21, 1, NULL, 1),
	(16, 21, 1, NULL, 1),
	(17, 21, 1, NULL, 1),
	(18, 21, 1, NULL, 4),
	(19, 21, 1, NULL, 1),
	(20, 21, 1, NULL, 1),
	(21, 21, 1, NULL, 1),
	(22, 21, 1, NULL, 1),
	(23, 21, 1, NULL, 1),
	(24, 21, 1, NULL, 1),
	(0, 22, 1, NULL, 8),
	(1, 22, 1, NULL, 8),
	(2, 22, 1, NULL, 8),
	(3, 22, 1, NULL, 8),
	(4, 22, 1, NULL, 8),
	(5, 22, 1, NULL, 1),
	(6, 22, 1, NULL, 2),
	(7, 22, 1, NULL, 1),
	(8, 22, 1, NULL, 2),
	(9, 22, 1, NULL, 4),
	(10, 22, 1, NULL, 4),
	(11, 22, 1, NULL, 2),
	(12, 22, 1, NULL, 1),
	(13, 22, 1, NULL, 6),
	(14, 22, 1, NULL, 6),
	(15, 22, 1, NULL, 1),
	(16, 22, 1, NULL, 1),
	(17, 22, 1, NULL, 1),
	(18, 22, 1, NULL, 4),
	(19, 22, 1, NULL, 1),
	(20, 22, 1, NULL, 1),
	(21, 22, 1, NULL, 1),
	(22, 22, 1, NULL, 1),
	(23, 22, 1, NULL, 1),
	(24, 22, 1, NULL, 1),
	(0, 23, 1, NULL, 8),
	(1, 23, 1, NULL, 8),
	(2, 23, 1, NULL, 8),
	(3, 23, 1, NULL, 8),
	(4, 23, 1, NULL, 4),
	(5, 23, 1, NULL, 1),
	(6, 23, 1, NULL, 4),
	(7, 23, 1, NULL, 1),
	(8, 23, 1, NULL, 4),
	(9, 23, 1, NULL, 4),
	(10, 23, 1, NULL, 4),
	(11, 23, 1, NULL, 6),
	(12, 23, 1, NULL, 1),
	(13, 23, 1, NULL, 1),
	(14, 23, 1, NULL, 1),
	(15, 23, 1, NULL, 1),
	(16, 23, 1, NULL, 1),
	(17, 23, 1, NULL, 1),
	(18, 23, 1, NULL, 1),
	(19, 23, 1, NULL, 1),
	(20, 23, 1, NULL, 1),
	(21, 23, 1, NULL, 1),
	(22, 23, 1, NULL, 1),
	(23, 23, 1, NULL, 1),
	(24, 23, 1, NULL, 1),
	(0, 24, 1, NULL, 8),
	(1, 24, 1, NULL, 8),
	(2, 24, 1, NULL, 8),
	(3, 24, 1, NULL, 8),
	(4, 24, 1, NULL, 4),
	(5, 24, 1, NULL, 4),
	(6, 24, 1, NULL, 4),
	(7, 24, 1, NULL, 4),
	(8, 24, 1, NULL, 4),
	(9, 24, 1, NULL, 4),
	(10, 24, 1, NULL, 1),
	(11, 24, 1, NULL, 1),
	(12, 24, 1, NULL, 1),
	(13, 24, 1, NULL, 1),
	(14, 24, 1, NULL, 1),
	(15, 24, 1, NULL, 1),
	(16, 24, 1, NULL, 1),
	(17, 24, 1, NULL, 1),
	(18, 24, 1, NULL, 1),
	(19, 24, 1, NULL, 1),
	(20, 24, 1, NULL, 1),
	(21, 24, 1, NULL, 1),
	(22, 24, 1, NULL, 1),
	(23, 24, 1, NULL, 1),
	(24, 24, 1, NULL, 1)

GO

EXECUTE dbo.[CreateDefaultCity] 1, 16, 0, 'Orlean'
EXECUTE dbo.[CreateDefaultCity] 1, 20, 0, 'Lyon'
EXECUTE dbo.[CreateDefaultCity] 1, 23, 0, 'Pary'
EXECUTE dbo.[CreateDefaultCity] 1, 9, 1, 'Sewilla'
EXECUTE dbo.[CreateDefaultCity] 1, 6, 2, 'Barcelona'
EXECUTE dbo.[CreateDefaultCity] 1, 15, 2, 'Berlin'
EXECUTE dbo.[CreateDefaultCity] 1, 18, 3, 'Kraków'
EXECUTE dbo.[CreateDefaultCity] 1, 6, 4, 'Lizbona'
EXECUTE dbo.[CreateDefaultCity] 1, 12, 4, 'Madryt'
EXECUTE dbo.[CreateDefaultCity] 1, 16, 4, 'Lodz'
EXECUTE dbo.[CreateDefaultCity] 1, 21, 4, 'Warszawa'
EXECUTE dbo.[CreateDefaultCity] 1, 9, 5, 'Kordoba'
EXECUTE dbo.[CreateDefaultCity] 1, 12, 6, 'Toledo'
EXECUTE dbo.[CreateDefaultCity] 1, 14, 6, 'Wroclaw'
EXECUTE dbo.[CreateDefaultCity] 1, 18, 6, 'Poznan'
EXECUTE dbo.[CreateDefaultCity] 1, 5, 7, 'Porta'
EXECUTE dbo.[CreateDefaultCity] 1, 12, 8, 'Khurasan'
EXECUTE dbo.[CreateDefaultCity] 1, 22, 8, 'Gdansk'
EXECUTE dbo.[CreateDefaultCity] 1, 8, 9, 'Futstat'
EXECUTE dbo.[CreateDefaultCity] 1, 17, 9, 'Basra'
EXECUTE dbo.[CreateDefaultCity] 1, 5, 10, 'Kufah'
EXECUTE dbo.[CreateDefaultCity] 1, 10, 11, 'Nad ran'
EXECUTE dbo.[CreateDefaultCity] 1, 7, 13, 'Anjar'
EXECUTE dbo.[CreateDefaultCity] 1, 13, 13, 'Bagdad'
EXECUTE dbo.[CreateDefaultCity] 1, 23, 15, 'Casablanca'
EXECUTE dbo.[CreateDefaultCity] 1, 18, 16, 'Marrakesz'
EXECUTE dbo.[CreateDefaultCity] 1, 9, 17, 'Mekka'
EXECUTE dbo.[CreateDefaultCity] 1, 22, 19, 'Fez'
EXECUTE dbo.[CreateDefaultCity] 1, 7, 20, 'Medyna'
EXECUTE dbo.[CreateDefaultCity] 1, 19, 21, 'Rabat'
EXECUTE dbo.[CreateDefaultCity] 1, 12, 22, 'Damaszek'

INSERT INTO [Project].dbo.[Building]([CityID], [BuildingTypeID]) VALUES
	(1, 1),
	(2, 2),
	(3, 3),
	(4, 4),
	(5, 5),
	(6, 6),
	(7, 7),
	(8, 8),
	(9, 1),
	(10, 2),
	(11, 3),
	(12, 4),
	(13, 5),
	(14, 6),
	(15, 7),
	(16, 8),
	(17, 1),
	(18, 2),
	(19, 3),
	(20, 4),
	(21, 5),
	(22, 6),
	(23, 7),
	(24, 8),
	(25, 1),
	(26, 2),
	(27, 3),
	(28, 4),
	(29, 5),
	(30, 6),
	(31, 7),
	(1, 8),
	(2, 1),
	(3, 2),
	(4, 3),
	(5, 4),
	(6, 5),
	(7, 6),
	(8, 7),
	(9, 8),
	(10, 1),
	(11, 2),
	(12, 3),
	(13, 4),
	(14, 5),
	(15, 6),
	(16, 7),
	(17, 8),
	(18, 1),
	(19, 2),
	(20, 3),
	(21, 4),
	(22, 5),
	(23, 6),
	(24, 7),
	(25, 8),
	(26, 1),
	(27, 2),
	(28, 3),
	(29, 4),
	(30, 5),
	(31, 6),
	(1, 7),
	(2, 8),
	(3, 1),
	(4, 2),
	(5, 3),
	(6, 4),
	(7, 5),
	(8, 6),
	(9, 7),
	(10, 8),
	(11, 1),
	(12, 2),
	(13, 3),
	(14, 4),
	(15, 5),
	(16, 6),
	(17, 7),
	(18, 8),
	(19, 1),
	(20, 2),
	(21, 3),
	(22, 4),
	(23, 5),
	(24, 6),
	(25, 7),
	(26, 8),
	(27, 1),
	(28, 2),
	(29, 3),
	(30, 4),
	(31, 5)

GO

EXECUTE dbo.[CreateCivilization] 1, 20, 0, 'Zaby', 0x8870F890
EXECUTE dbo.[CreateCivilization] 1, 9, 1, 'Rabusie', 0x4E844C90
EXECUTE dbo.[CreateCivilization] 1, 15, 2, 'Niemcy', 0x07309790
EXECUTE dbo.[CreateCivilization] 1, 6, 4, 'Pawie', 0x976B2390
EXECUTE dbo.[CreateCivilization] 1, 21, 4, 'Polska', 0xEFA5E590
EXECUTE dbo.[CreateCivilization] 1, 10, 11, 'Wielki Islam', 0xD0D3B590
EXECUTE dbo.[CreateCivilization] 1, 22, 19, 'Ktos', 0x57AB5190

EXECUTE dbo.[AddProvinceToRegion] 1, 16, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 0, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 1, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 1, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 1, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 1, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 1, 'Zaby'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 2, 'Zaby'

EXECUTE dbo.[AddProvinceToRegion] 1,  5, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 1, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 2, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 3, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 3, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 3, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 3, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 3, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 4, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 4, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 4, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 4, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 5, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 5, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 5, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 5, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 5, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 6, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 6, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 6, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 6, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 6, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 7, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 7, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 7, 'Rabusie'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 7, 'Rabusie'

EXECUTE dbo.[AddProvinceToRegion] 1, 14, 1, 'Niemcy'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 1, 'Niemcy'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 1, 'Niemcy'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 2, 'Niemcy'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 2, 'Niemcy'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 3, 'Niemcy'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 3, 'Niemcy'

EXECUTE dbo.[AddProvinceToRegion] 1, 5, 3, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 6, 3, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 7, 3, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 7, 4, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 8, 4, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 5, 5, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 6, 5, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 7, 5, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 6, 6, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 7, 6, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 5, 7, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 6, 7, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 7, 7, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 6, 8, 'Pawie'
EXECUTE dbo.[AddProvinceToRegion] 1, 7, 8, 'Pawie'

EXECUTE dbo.[AddProvinceToRegion] 1, 17, 1, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 2, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 2, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 2, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 2, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 2, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 3, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 4, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 5, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 6, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 7, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 7, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 7, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 7, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 7, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 7, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 8, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 8, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 8, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 8, 'Polska'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 9, 'Polska'

EXECUTE dbo.[AddProvinceToRegion] 1,  8,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 17,  8, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 17,  9, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 10, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  4, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 11, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 12, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 13, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 14, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 14, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 14, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 16, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 17, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 17, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 17, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 17, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 17, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 18, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 18, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 18, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 18, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 18, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 18, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 19, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 20, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 21, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 22, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  4, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 23, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  4, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  5, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  6, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  7, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  8, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1,  9, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 10, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 11, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 12, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 13, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 14, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 24, 'Wielki Islam'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 24, 'Wielki Islam'

EXECUTE dbo.[AddProvinceToRegion] 1, 24, 14, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 15, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 15, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 15, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 15, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 15, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 15, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 16, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 17, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 18, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 15, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 19, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 20, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 21, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 22, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 16, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 23, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 17, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 18, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 19, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 20, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 21, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 22, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 23, 24, 'Ktos'
EXECUTE dbo.[AddProvinceToRegion] 1, 24, 24, 'Ktos'

GO

USE [master]