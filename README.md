# SteamToolMaster
A solution which provides various tools for items on steam built entirely on c++, current features listed below
### TradePrice
> Quickly calculate the total cost of multiple items denoted in keys and metal

# Installation Guide
### Step 1
> Download the ZIP file from the [main branch](https://github.com/MasterVint/SteamToolMaster)
### Step 2
> Extract the ZIP to a desired folder
### Step 3
> Open and build the solution in visual studio
### Step 4
> Copy and paste the built .exe into a new empty folder and rename it to SteamToolMaster.exe
### Step 5
> In the same folder from step 4, create a .bat file called stmtool.bat with the following contents:
```
@echo off
cd /d "%~dp0"
SteamToolMaster.exe %*
```
### Final Step
> On windows go unto "Environment Variables", find "System Variables" and find "PATH" and click "Edit" then "New" and enter your new folder's path and click "OK" on all windows.
### Enjoy!
> You have now added SteamToolMaster to your computer! Type stmtool from any command prompt on your pc to use!
```
>stmtool
usage: stmtool [ tradeprice | trade | trp]

See "stmtool [command] help" for specific command help
```
### Configuration
> Notice that we could rename our .bat file to e.g "sigma.bat" and we'd be able to call SteamToolMaster like how we did with stmtool.
```
>sigma
usage: sigma [ tradeprice | trade | trp]

See "sigma [command] help" for specific command help
```
