#!/bin/sh
base=${PWD}
builddir=${PWD}/build/
install_dir="/Users/diederickhuijbers/c++/of/addons_diederick/ofxGLM/src/"
if [ "$1" = "download"  ] ; then
	if [ ! -d ${base}/glm ] ; then 
		mkdir ${base}/glm
	fi
	curl http://www.roxlu.com/assets/downloads/ofxGLM/glm-0.3.1.tar.gz -o ${base}/glm/glm.tgz

	if [ ! -d ${base}/jpeg ] ; then 
		mkdir ${base}/jpeg
	fi
	curl http://www.roxlu.com/assets/downloads/ofxGLM/jpegsr8c.gz -o ${base}/jpeg/jpeg.tgz

	#if [ ! -d ${base}/devil ] ; then
	#	mkdir ${base}/devil
	#fi
	#curl http://www.roxlu.com/assets/downloads/ofxGLM/DevIL-1.7.8.tar.gz -o ${base}/devil/devil.tgz

	#if [ ! -d ${base}/jasper ] ; then
	#	mkdir ${base}/jasper
	#fi
	#curl http://www.roxlu.com/assets/downloads/ofxGLM/jasper-1.900.1.zip -o ${base}/jasper/jasper.zip

	if [ ! -d ${base}/lcms ] ; then
		mkdir ${base}/lcms
	fi
	curl http://www.roxlu.com/assets/downloads/ofxGLM/lcms2-2.1.tar.gz -o ${base}/lcms/lcms.tgz

	if [ ! -d ${base}/mng ] ; then
		mkdir ${base}/mng
	fi
	curl http://www.roxlu.com/assets/downloads/ofxGLM/libmng-1.0.10.tar.gz -o ${base}/mng/mng.tgz

	if [ ! -d ${base}/png ] ; then
		mkdir ${base}/png
	fi
	curl http://www.roxlu.com/assets/downloads/ofxGLM/libpng-1.4.3.tar.gz -o ${base}/png/png.tgz

	if [ ! -d ${base}/tiff ] ; then
		mkdir ${base}/tiff 
	fi 
	curl http://www.roxlu.com/assets/downloads/ofxGLM/tiff-3.9.4.tar.gz -o ${base}/tiff/tiff.tgz

	if [ ! -d ${base}/zlib ] ; then
		mkdir ${base}/zlib
	fi
	curl http://www.roxlu.com/assets/downloads/ofxGLM/zlib-1.2.5.tar.gz -o ${base}/zlib/zlib.tgz

	if [ ! -d ${base}/simage ] ; then
		mkdir ${base}/simage
	fi

	curl http://www.roxlu.com/assets/downloads/ofxGLM/simage-1.7.0.tar.gz -o ${base}/simage/simage.tgz
fi

if [ "$1" = "extract" ] ; then
	cd ${base}/glm/
	tar -zxvf glm.tgz
	mv glm-0.3.1/* .
	rm -r glm-0.3.1

	cd ${base}/jpeg/
	tar -zxvf jpeg.tgz
	mv jpeg-8c/* .
	rm -r jpeg-8c

	cd ${base}/devil
	tar -zxvf devil.tgz
	mv devil-1.7.8/* .
	rm -r devil-1.7.8

	#cd ${base}/jasper
	#unzip jasper.zip
	#mv jasper-1.900.1/* .
	#rm -r jasper-1.900.1

	cd ${base}/lcms
	tar -zxvf lcms.tgz
	mv lcms2-2.1/* .
	rm -r lcms2-2.1

	cd ${base}/mng
	tar -zxvf mng.tgz
	mv libmng-1.0.10/* .
	rm -r libmng-1.0.10

	cd ${base}/png
	tar -zxvf png.tgz
	mv libpng-* libpng
	mv libpng/* .
	rm -r libpng

	cd ${base}/tiff
	tar -zxvf tiff.tgz
	mv tiff-3.9.4/* .
	rm -r tiff-3.9.4 

	cd ${base}/zlib
	tar -zxvf zlib.tgz
	mv zlib-* zlib
	mv zlib/* .
	rm -r zlib
	
	cd ${base}/simage
	tar -zxvf simage.tgz
	mv simage-* simage
	mv simage/* .
	rm -r simage

fi


export LDFLAGS="-arch i386 "
export CFLAGS="-Os -arch i386 "
export CC="gcc-4.0 "

if [ "$1" = "jpg" ] ; then
	cd ${base}/jpeg
	make clean
	./configure --enable-static=yes --prefix=${builddir} --disable-dependency-tracking
	make
	make install
fi

if [ "$1" = "png" ] ; then
	cd ${base}/png
	./configure --enable-static --prefix=${builddir} --disable-dependency-tracking
	make 
	make install
fi

if [ "$1" = "zlib" ] ; then
	cd ${base}/zlib
	./configure  --prefix=${builddir} --static 
	make 
	make install
fi

if [ "$1" = "tiff" ] ; then
	cd ${base}/tiff
	./configure --prefix=${builddir} --enable-static=yes --enable-shared=no --disable-dependency-tracking \
	 	CFLAGS="-I${builddir}/include/ -L${builddir}/lib/ -arch i386 " \
	        LDFLAGS="-L${builddir}/lib/ -arch i386 " \
		CPPFLAGS="-I${builddir}/include/ -arch i386 "
	make
	make install
fi

if [ "$1" = "mng" ] ; then
	cd ${base}/mng
	if [ ! -f ./configure ] ; then
		cp unmaintained/autogen.sh .
		./autogen.sh	
	fi	
	./configure --prefix=${builddir} --enable-static=yes --disable-dependency-tracking \
		CFLAGS="-I${builddir}/include/ -L${builddir}/lib/ -arch i386 " \
                LDFLAGS="-L${builddir}/lib/ -arch i386 " \
                CPPFLAGS="-I${builddir}/include/ -arch i386 "
	make 
	make install
fi

if [ "$1" = "lcms" ] ; then
	cd ${base}/lcms
	 ./configure --prefix=${builddir} --enable-static=yes --disable-dependency-tracking \
                CFLAGS="-I${builddir}/include/ -L${builddir}/lib/ -arch i386 " \
                LDFLAGS="-L${builddir}/lib/ -arch i386 " \
                CPPFLAGS="-I${builddir}/include/ -arch i386 "
        make
        make install	
fi

if [ "$1" = "jasper" ] ; then
	cd ${base}/jasper
	 ./configure --prefix=${builddir} --enable-static=yes --disable-dependency-tracking \
                CFLAGS="-I${builddir}/include/ -L${builddir}/lib/ -arch i386 " \
                LDFLAGS="-L${builddir}/lib/ -arch i386 " \
                CPPFLAGS="-I${builddir}/include/ -arch i386 "
        make
        make install
fi

if [ "$1" = "devil" ] ; then
	cd ${base}/devil
	 ./configure --prefix=${builddir} --enable-static=yes  --disable-dependency-tracking \
	 	--enable-png=no \
		CFLAGS="-I${builddir}include/ -L${builddir}lib/ -arch i386 " \
                LDFLAGS="-L${builddir}lib/ -arch i386 " \
                CPPFLAGS="-I${builddir}include/ -arch i386 "
        make
        make install
fi

if [ "$1" = "simage" ] ; then
        cd ${base}/simage
         ./configure --prefix=${builddir} --enable-static=yes  --disable-dependency-tracking \
                CFLAGS="-I${builddir}include/ -L${builddir}lib/ -arch i386 " \
                LDFLAGS="-L${builddir}lib/ -arch i386 " \
                CPPFLAGS="-I${builddir}include/ -arch i386 " 
        make
        make install
fi

if [ "$1" = "glm" ] ; then
	# necessary for libtool bugs
	if [ ! "$2" = "fast" ] ; then
		cd ${base}/glm/
		tar -zxvf glm.tgz
		mv glm-0.3.1/* .
		rm -r glm-0.3.1
	fi

	cd ${base}/glm
	if [ ! "$2" = "fast" ] ; then
		make clean
	fi
	set -x	
	
	if [ ! -f ./configure ] ; then
		./autogen.sh
	fi
	
 	#export  CFLAGS="-I${builddir}include/ -L${builddir}lib/ -arch i386" 
	#export  LDFLAGS="-L${builddir}lib/ -arch i386" 
    #export  CPPFLAGS="-L${builddir}lib/ -I${builddir}include/ -arch i386"
	echo "---------------------------"
	echo "---------------------------"
	echo "---------------------------"

	if [ ! "$2" = "fast" ]  ; then
		./configure --enable-static=yes  \
			--prefix=${builddir} \
			--disable-dependency-tracking \
			--with-devil \
			--with-simage \
			CFLAGS="-I${builddir}include/ -L${builddir}lib/ -arch i386  -DSINGLE_STRING_GROUP_NAMES" \
			LDFLAGS="-L${builddir}lib/ -arch i386  -DSINGLE_STRING_GROUP_NAMES" \
			CPPFLAGS="-L${builddir}lib/ -I${builddir}include/ -arch i386  -DSINGLE_STRING_GROUP_NAMES" 
	fi

	make
	make clean
	make install
fi

if [ "$1" = "install" ] ; then 
	if [ -d ${install_dir} ]  ; then 
		cp ${builddir}/lib/libglm.a ${install_dir}/lib/osx/
		cp ${builddir}/lib/libsimage.a ${install_dir}/lib/osx/
		cp ${builddir}/include/glm.h ${install_dir}/include/
	else
		echo "install dir not found!"
	fi
fi
