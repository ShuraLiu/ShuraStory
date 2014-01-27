WBTMXTool=./WBTMXTool

if [ "${ACTION}" = "clean" ]
then
	echo "cleaning..."
else

	echo "*** Convert HD TMX files to SD ones..."
    
	for file in resources-iphonehd/*.tmx
	do
		#echo "input HD TMX File: $file"
		echo "File: $file"
		filebasename=`basename $file`
		echo "file base name: $filebasename"
        infile="resources-iphonehd/$filebasename"
        outfile="resources-iphone/$filebasename"
        echo "Input HD TMX File: $infile"
        echo "Output SD TMX File: $outfile"
		${WBTMXTool} -in $infile -out $outfile -scale 0.5
	done
fi
exit 0