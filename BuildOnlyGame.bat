@echo off
cls

cd ./DondeEstaLaPutaLeche
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Debug
msbuild DondeEstaLaPutaLeche.sln /p:configuration=Release
