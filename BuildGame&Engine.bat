@echo off
cls
set ENGINE=.\Engine\ElHorno\Exes

cd ./DondeEstaLaPutaLeche/Engine
call ElHorno.bat
cd ../..

cd ./DondeEstaLaPutaLeche
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Debug
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Release

XCOPY /y /s .\Exes\ElHornoGame.dll %ENGINE%
XCOPY /y /s .\Exes\ElHornoGame_d.dll %ENGINE%
pause