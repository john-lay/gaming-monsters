@echo off

set project="lesson15"
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


REM set project="lesson15"
REM if exist %project%\main.gb del %project%\main.gb
REM if exist %project%\main.sav del %project%\main.sav
REM if exist %project%\main.map del %project%\main.map

REM if exist %project%\main.o del %project%\main.o
REM if exist %project%\main.lst del %project%\main.lst
REM if exist %project%\main.sym del %project%\main.sym

REM if exist %project%\saveState.o del %project%\saveState.o
REM if exist %project%\saveState.lst del %project%\saveState.lst
REM if exist %project%\saveState.sym del %project%\saveState.sym

REM :begin
REM echo assembling...
REM 	c:\gbdk\bin\lcc -Wa-l -Wf-ba0 -c -o %project%\saveState.o %project%\saveState.c
REM 	c:\gbdk\bin\lcc -Wa-l -c -o %project%\main.o %project%\main.c
REM 	if errorlevel 1 goto end
REM echo linking...
REM 	c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo4 -Wl-ya4 -o %project%\main.gb %project%\main.o %project%\savestate.o
REM 	if errorlevel 1 goto end
REM :end

REM set project="lesson15"
REM if exist %project%\2020.gb del %project%\2020.gb
REM if exist %project%\2020.o del %project%\2020.o
REM if exist %project%\2020.lst del %project%\2020.lst
REM if exist %project%\2020.map del %project%\2020.map
REM if exist %project%\2020.sym del %project%\2020.sym

REM :begin
REM echo assembling...
REM 	c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o %project%\2020.o %project%\2020.c
REM 	if errorlevel 1 goto end
REM echo linking...
REM 	c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o %project%\2020.gb %project%\2020.o
REM 	if errorlevel 1 goto end
REM :end

