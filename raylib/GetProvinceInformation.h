struct provinceInformation {
	char terrainName[255];
	char regionName[255];
	char cityName[255];
};

void GetProvinceInformation(int sessionID, int coordinateX, int coordinateY, struct provinceInformation* info);