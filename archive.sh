if [ -z $1 ]; then
	echo "Usage example: archive lab1"
	exit 1
fi

rm */*.idea
cd $1
zip -r $1.zip logs report/*.tex
cd report
zip -u ../$1.zip $1.pdf
