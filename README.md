ROMSniffer watches when a game starts on the output signals for MAME, DemulShooter, and other programs. It looks for "mame_start" and "game =" in the output signals. When a new game is detected, it will start a new program with the arguments supplied. The game or ROM name can be used in the arguments, using the %r% which will get replaced by the game or ROM name. When the program starts, it will be hidden, by hiding the command prompt that it runs in. When using the debug mode, it doesn't hide the command prompt. The user can also use the "-noHide" option, where the command prompt will not be hidden, but minimized instead. This program will run all the time, until the user closes it in the command prompt, if it is not hidden. If it is hidden, then the uses must use task manager or a different way.    

The program first needs the program that will be run when a new game has been found. Then after the program name, it is the arguments for the program, if needed. The game's name can be used in the arguments, by using %r%, which gets replaced by the game's name. 

There are 3 options that can be used with the program. The first is "-h" which will bring up the help information and not run the program. The 2nd option is "-ddd" which is the debug option. It will not hid the command prompt, so that the debug info can be seen. The last option is "-noHide" which doesn't hide the command prompt, but minimizes it. 


Run the program and get help info.

ROMSniffer.exe -h

ROMSniffer.exe


Run the program example.

ROMSniffer ProgramX.exe -%r%.txt

When a game is found, it will run the ProgramX.exe program, with the game's name with .txt. Let say "digdug" was started in MAME. It will run the program below. The command prompt will be hidden. 

ProgramX.exe -digdug.txt



Run the program in debug mode example.

ROMSniffer ProgramY.exe -%r%.json -ddd

The command prompt will not be hidden, and debug info will be displayed. When a game is found, it will run the ProgramY.exe program, with the game's name with .json. This will also be displayed in the command prompt. Let say "pacman" was started in MAME. It will run the program below.

ProgramY.exe -pacman.json




Run the program with "-noHide" example.

ROMSniffer "Program Zed.exe" %r%.hor -noHide

The command prompt will be minimized, and not hidden. When a game is found, it will run the ProgramZ.exe program, with the game's name with .hor. Let say "HOTD4" was started in TeknoParrot with DemulShooter. It will run the program below.

Program Zed.exe HOTD4.hor
