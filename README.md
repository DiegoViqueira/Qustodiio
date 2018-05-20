# Qustodio
	Test for Qustodio
	
	client-server OOP application in C++. The client is in charge of analyzing router logs and sending questionable 
	activities to the server. 
	The server application will receive those reports from many clients simultaneouslyand store them in memory to 
	process them later. 

### Prerequisites
  - GCC > 5 
  - Makefile 

### Filesystem Structure

```
  + -- /boost ( Boost Framework Utils. )
  |
  + -- /common ( Common Headears. )
  |
  + -- /src ( Sources Files. )
  :
  + -- /obj ( Temporary repository for builded Objects. )
  :
  + -- /build ( Build Directory for Executables.  )
```  

## Deployment 

+ Clone repository localy
+ Download Boost C++ Framework (https://www.boost.org/users/download/) in Git project repository.

## Build Boost

* uncompress bost_[Version].zip into /boost 

```
cd boost
bootstrap.bat gcc
b2 --build-dir=MYBOOST
```


## Build

Makefile Fixes:
Edit Makefile in Project root dir and replace this 3 libraries for the right builded in boost/stage/lib
  - boost_filesystem-mgw73-mt-x64-1_67 
  - boost_system-mgw73-mt-x64-1_67 
  - boost_thread-mgw73-mt-x64-1_67

Compile Proyect:
```
make dirs
make all
```

Clean Proyect:
```
make clean
```



## Running the tests

cd build 

Run Server
```
QustodioServer.exe
```
Run Client
```
QustodioCient.exe -f prueba.dat
```
## Authors

* **Diego Viqueira** - *Initial work* 

## Built With

* [boost] Version: 1.67.0 - (https://www.boost.org/) - Boost Framework.


## License

This project is licensed under the GNU General Public License V.3 - see the [LICENSE.md](LICENSE.md) file for details
