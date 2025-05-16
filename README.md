# SteamToolMaster
A solution which provides various tools for items on steam built entirely on c++, current features listed below
Refer to the [Wiki](https://github.com/MasterVint/SteamToolMaster/wiki) for more in depth help. Currently only supports Windows
### TradePrice
> Calculate the total cost of multiple items denoted in keys and metal
### KitMaker
> Calculate the price of turning a Professional/Specialized killstreak fabricator into a kit

# Build it yourself
### Step 1
> Download the ZIP file from the [main branch](https://github.com/MasterVint/SteamToolMaster) and extract it to a desired folder
### Step 2
> Open and build the solution in visual studio as release
### Step 3
> Copy and paste the built .exe into a new empty folder and rename it to SteamToolMaster.exe
### Step 4
> In the same folder from step 3, create a .bat file called stmtool.bat with the following contents:
```
@echo off
cd /d "%~dp0"
SteamToolMaster.exe %*
```
### Step 5
> On windows go unto "Environment Variables", find "System Variables" and find "PATH" and click "Edit" then "New" and enter your new folder's path and click "OK" on all windows. This will allow windows to find your program from anywhere on your computer.
### Enjoy!
> You have now added SteamToolMaster to your computer! Type stmtool from any command prompt on your pc to use!
```
>stmtool
usage: stmtool [ tradeprice | trade | trp]
```
### Configuration
> Notice that we could rename our .bat file to e.g "sigma.bat" and we'd be able to call SteamToolMaster like how we did with stmtool.
```
>sigma
usage: sigma [ tradeprice | trade | trp]
```
Note: does not change to sigma
