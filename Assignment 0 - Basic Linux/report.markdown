# Marios Aspris

# Assignment 0 - Report

## First I create the folder plasma_local with the command mkdir.  mkdir is a command used to create new directories.

mkdir plasma_local

## To get the installer file from the link I use the wget command. wget is a command to retrieve files using HTTP, HTTPS and FTP.

wget http://icl.cs.utk.edu/projectsfiles/plasma/pubs/plasma-installer.tar.gz

## To extract the contents from it I use tar -xvf. Since the file downloaded is a tar file, -xvf command is used to extract the files.   

tar -xvf plasma-installer.tar.gz

## Using BLAS and LAPack that are installed on ozzy.
## Fisrt I find the libraries with find.

find /usr/lib/ -iname *blas*
find /usr/lib/ -iname *LAPack*


## Then I install the libraries in the folder created in the begining.

./plasma-installer_2.8.0/setup.py --cc=gcc --blaslib="/usr/lib/libblas/libblas.so.3.6.0" --lapacklib="/usr/lib/lapack/liblapack.so.3.6.0" --notesting --build="/home/hpc32/plasma_local/" 

## The program asks to download the netlib LAPACK and install tmg library. I type d.

d

## Then the program asks for downloading the LAPACK C interface and I type d.

d

## Now the PLASMA installer started and it is installed. The Plasma testing programs are in: /home/hpc32/plasma_local/testing


## Testing. running the PLASMA tests.

### Change the directory to the one:

cd ~/plasma_local/plasma_2.8.0/testing

## In this directory there is a file called plasma_testing.py. Running this:

./plasma_tetsing.py

## Will run all the tests for the program. 
## In the testing folder the makefile Makefile.src exists where I can open it with nano editor:

nano Makefile

## Opening the Makefile, I can see it contains source files for testing. 



