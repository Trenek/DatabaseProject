cmake_minimum_required(VERSION 3.26)

project(DatabaseProject C)

find_package(ODBC REQUIRED)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(
    "${CMAKE_SOURCE_DIR}/source"
    "${CMAKE_SOURCE_DIR}/source/additions"
    "${CMAKE_SOURCE_DIR}/source/additions/drawMenuElement"
    "${CMAKE_SOURCE_DIR}/source/additions/inputBox"
    "${CMAKE_SOURCE_DIR}/source/additions/LoadingScreen"
    "${CMAKE_SOURCE_DIR}/source/additions/modifyBackgroundColor"
    "${CMAKE_SOURCE_DIR}/source/additions/ProvinceTextures"
    "${CMAKE_SOURCE_DIR}/source/GridTile"
    "${CMAKE_SOURCE_DIR}/source/query"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session"
    "${CMAKE_SOURCE_DIR}/source/query/Map/GetDimensions"
    "${CMAKE_SOURCE_DIR}/source/query/Map/GetMaps"
    "${CMAKE_SOURCE_DIR}/source/query/Player"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/GetCivilizations"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/GetPoliticalDivision"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/Province"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/Province/GetProvinceInformation"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/Province/GetProvinces"
    "${CMAKE_SOURCE_DIR}/source/query/Terrain"
    "${CMAKE_SOURCE_DIR}/source/query/User"
    "${CMAKE_SOURCE_DIR}/source/state/play"
)

add_executable(DatabaseProject
    "${CMAKE_SOURCE_DIR}/source/main.c"
    "${CMAKE_SOURCE_DIR}/source/mapDebug.c"
    "${CMAKE_SOURCE_DIR}/source/additions/drawMenuElement/drawMenuElement.c"
    "${CMAKE_SOURCE_DIR}/source/additions/inputBox/inputBox.c"
    "${CMAKE_SOURCE_DIR}/source/additions/LoadingScreen/LoadingScreen.c"
    "${CMAKE_SOURCE_DIR}/source/additions/modifyBackgroundColor/modifyBackgroundColor.c"
    "${CMAKE_SOURCE_DIR}/source/additions/ProvinceTextures/ProvinceTextures.c"
    "${CMAKE_SOURCE_DIR}/source/GridTile/GridTileDef.c"
    "${CMAKE_SOURCE_DIR}/source/query/query.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/BuildCity.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/CheckIfReady.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/createGameSession.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/GetBuildingType.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/GetCityConstructionDate.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/GetCurrentDate.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/getGameSessions.c"
    "${CMAKE_SOURCE_DIR}/source/query/Game Session/UpdateCurrentDate.c"
    "${CMAKE_SOURCE_DIR}/source/query/Map/GetDimensions/getDimensions.c"
    "${CMAKE_SOURCE_DIR}/source/query/Map/GetMaps/GetMaps.c"
    "${CMAKE_SOURCE_DIR}/source/query/Player/AddPlayer.c"
    "${CMAKE_SOURCE_DIR}/source/query/Player/AssignCivilization.c"
    "${CMAKE_SOURCE_DIR}/source/query/Player/RemovePlayer.c"
    "${CMAKE_SOURCE_DIR}/source/query/Player/ShowPlayer.c"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/GetCivilizations/GetCivilizations.c"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/GetPoliticalDivision/GetPoliticalDivision.c"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/Province/GetProvinceInformation/GetProvinceInformation.c"
    "${CMAKE_SOURCE_DIR}/source/query/SessionOrMap/Province/GetProvinces/GetProvinces.c"
    "${CMAKE_SOURCE_DIR}/source/query/Terrain/GetTerrain.c"
    "${CMAKE_SOURCE_DIR}/source/query/User/AddUser.c"
    "${CMAKE_SOURCE_DIR}/source/query/User/GetUsers.c"
    "${CMAKE_SOURCE_DIR}/source/query/User/logInQuery.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/buildingBox.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/cityBox.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/countryBox.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/drawTopLayer.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/errorLayer.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/map.c"
    "${CMAKE_SOURCE_DIR}/source/state/play/provinceBox.c"
    "${CMAKE_SOURCE_DIR}/source/state/createGame.c"
    "${CMAKE_SOURCE_DIR}/source/state/cube.c"
    "${CMAKE_SOURCE_DIR}/source/state/gameSetup.c"
    "${CMAKE_SOURCE_DIR}/source/state/loadGame.c"
    "${CMAKE_SOURCE_DIR}/source/state/login.c"
    "${CMAKE_SOURCE_DIR}/source/state/menu.c"
    "${CMAKE_SOURCE_DIR}/source/state/pause.c"
    "${CMAKE_SOURCE_DIR}/source/state/play.c"
    "${CMAKE_SOURCE_DIR}/source/state/playerList.c"
    "${CMAKE_SOURCE_DIR}/source/state/register.c"
)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -Wshadow -O2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=c23")

target_include_directories(DatabaseProject PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/include"
    "${ODBC_INCLUDE_DIRS}"
)

target_link_libraries(DatabaseProject PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/lib/libraylib.a"
    "${ODBC_LIBRARIES}"
    winmm
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)