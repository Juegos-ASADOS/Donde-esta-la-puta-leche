@echo off
cls
set EXES=.\Engine\ElHorno\Exes

cd ./DondeEstaLaPutaLeche/Engine
call ElHorno.bat
cd ../..

cd ./DondeEstaLaPutaLeche
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Debug
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Release

XCOPY /y /s .\Exes\ElHornoGame.dll %EXES%
XCOPY /y /s .\Exes\ElHornoGame_d.dll %EXES%
pause