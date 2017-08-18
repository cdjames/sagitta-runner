REM sample C script: https://stackoverflow.com/questions/171326/how-can-i-increase-the-key-repeat-rate-beyond-the-oss-limit#11056655
REM documentation: https://msdn.microsoft.com/en-us/library/windows/desktop/ms724947(v=vs.85).aspx
REM see also SPI_SETKEYBOARDSPEED in above link
REM reg query "HKEY_CURRENT_USER\Control Panel\Accessibility\Keyboard Response"
REM check user's current settings
reg query "HKEY_CURRENT_USER\Control Panel\Keyboard"
REM save user's current settings (must have admin rights)
reg save "HKEY_CURRENT_USER\Control Panel\Keyboard" keybdSetBak.hiv