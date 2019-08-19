@echo off ?
echo ---------------------------------------------------- ?
echo By Kaidy
echo Press any key to delete all files with ending: ?
echo ?*.aps *.idb *.ncp *.obj *.pch *.tmp *.sbr ?
echo ?*.tmp *.pdb *.bsc *.ilk *.res *.ncb *.opt ??
echo ?*.suo *.manifest ?*.dep ? ..
echo There are Visual C++ and Visual Studio junk ?
echo ---------------------------------------------------- ?
pause ?
del /F /S /Q *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res *.ncb *.opt *.suo *.manifest *.dep *.lastbuildstate *.tlog?

del Buildlog.htm /s
del *Build_log.htm /s
del *.obj /s
del *.pch /s
del *.idb /s
del *.pdb /s
del *.res /s
del *.dep /s
del *.manifest /s
del *.bsc /s
del *.ilk /s
del *.SBR /s
del *.lst /s
del *.ncb /s
del *.sdf /s
del *.tlog /s
del *.exp /s


del /s *.obj
del /s *.ilk
del /s *.pdb
del /s *.tlog
del /s *.lastbuildstate
del /s *.idb
del /s *.log
del /s *.sdf
del /s *.suo
del /s *.bsc
del /s *.psess
del /s *.pch
del /s *.ipch
del /s *.sbr
del /s *.suo
del /s *.db
del /s *.svn-base

Pause ?