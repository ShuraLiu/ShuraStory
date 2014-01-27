python remove_hd_suffix.py game_1-hd.plist -hd ''

#game_1
if ! mv game_1-hd.plist resources-iphonehd/game_1.plist ; then
	echo "mv game_1-hd.plist error!"
fi
if ! mv game_1-hd.pvr.ccz resources-iphonehd/game_1.pvr.ccz ; then
    echo "mv game_1-hd.pvr.ccz error!"
fi
if ! mv game_1.plist resources-iphone/ ; then
	echo "mv game_1.plist error!"
fi
if ! mv game_1.pvr.ccz resources-iphone/ ; then
    echo "mv game_1.pvr.ccz error!"
fi

echo "done!"