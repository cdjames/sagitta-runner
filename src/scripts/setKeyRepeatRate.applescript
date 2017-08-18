(*
https://stackoverflow.com/questions/16711861/use-applescript-to-change-system-preferences-without-being-visible
https://stackoverflow.com/questions/6160095/how-to-use-applescript-to-change-preference-pane-slider-value
http://macscripter.net/viewtopic.php?id=24773
https://stackoverflow.com/questions/171326/how-can-i-increase-the-key-repeat-rate-beyond-the-oss-limit#11056655
*)

tell application "System Preferences"
	reveal anchor "keyboardTab" of pane "com.apple.preference.keyboard"
end tell

tell application "System Events" to tell application process "System Preferences"
	tell tab group 1 of window "Keyboard"
		set value of slider 1 to 6
		set value of slider 2 to 7
	end tell
end tell
quit application "System Preferences"