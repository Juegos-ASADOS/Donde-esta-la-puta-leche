@echo off
cls
set ENGINE=%cd%\DondeEstaLaPutaLeche\Engine\ElHorno\Exes
set GAME= %cd%\DondeEstaLaPutaLeche\Exes

cd ./DondeEstaLaPutaLeche/Engine
call BuildEngine.bat
cd ../..

copy "%ENGINE%\*.exe" .\Exes 
copy "%ENGINE%\*.dll" .\Exes 

msbuild DondeEstaLaPutaLeche.sln /p:configuration=Debug
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Release