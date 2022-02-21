@echo off

set project="zeldasprite"
if exist %project%\main.gb del %project%\main.gb
if exist %project%\main.o del %project%\main.o
if exist %project%\main.lst del %project%\main.lst
if exist %project%\main.map del %project%\main.map
if exist %project%\main.sym del %project%\main.sym

:begin
echo assembling...
	c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o %project%\main.o %project%\main.c
	if errorlevel 1 goto end
echo linking...
	c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o %project%\main.gb %project%\main.o
	if errorlevel 1 goto end
:end
