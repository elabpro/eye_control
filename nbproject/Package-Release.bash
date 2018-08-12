#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=GNU-Linux
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build
CND_DLIB_EXT=so
NBTMPDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eyecontrol-1.3
OUTPUT_BASENAME=eyecontrol-1.3
PACKAGE_TOP_DIR=/usr/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${NBTMPDIR}
mkdir -p ${NBTMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin/data"
copyFileToTmpDir "data/alfavit_eng.png" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/data/alfavit_eng.png" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin/data"
copyFileToTmpDir "data/lbpcascade_frontalface.xml" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/data/lbpcascade_frontalface.xml" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin/data"
copyFileToTmpDir "data/alfavit_rus.png" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/data/alfavit_rus.png" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin/data"
copyFileToTmpDir "data/settings.dat" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/data/settings.dat" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin/data"
copyFileToTmpDir "data/mousepanel.png" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/data/mousepanel.png" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin/data"
copyFileToTmpDir "data/haarcascade_eye_tree_eyeglasses.xml" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/data/haarcascade_eye_tree_eyeglasses.xml" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/bin"
copyFileToTmpDir "${OUTPUT_PATH}" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755


# Create control file
cd "${TOP}"
CONTROL_FILE=${NBTMPDIR}/DEBIAN/control
rm -f ${CONTROL_FILE}
mkdir -p ${NBTMPDIR}/DEBIAN

cd "${TOP}"
echo 'Package: eyecontrol-1.3' >> ${CONTROL_FILE}
echo 'Version: 1.0' >> ${CONTROL_FILE}
echo 'Architecture: amd64' >> ${CONTROL_FILE}
echo 'Maintainer: eugine' >> ${CONTROL_FILE}
echo 'Description: ...' >> ${CONTROL_FILE}

# Create Debian Package
cd "${TOP}"
cd "${NBTMPDIR}/.."
dpkg-deb  --build ${TMPDIRNAME}
checkReturnCode
cd "${TOP}"
mkdir -p  ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
mv ${NBTMPDIR}.deb ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/eyecontrol-1.3.deb
checkReturnCode
echo Debian: ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/eyecontrol-1.3.deb

# Cleanup
cd "${TOP}"
rm -rf ${NBTMPDIR}
