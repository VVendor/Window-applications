C++ Matrix DLL
Description
There is simple example of creating DLL and writing Unit tests for it.

Requiremets
Visual Studio 2015 IDE
How to get it
Download/Clone this repository
Open solution file .sln
Build the solution
How to create your own DLL and Unit tests for it
Open Visual Studio 2015 IDE

Start project wizard

 File->New->Project
Select Visual C++ Console Application

 Visual C++->Win32->Win32 Console Application
and set the checkpoint on Create directory for solution

In wizard's Application Settings tab choose

 Appliction type: DLL
 Additional options: Export symbols; Precompiled header; Security Development Lifecycle (SDL) checks
Add new project in solution

 Solution->Add->New Project
Select Unit test

 Visual C++->Test->Native Unit Test Project
Go to solution properties

 Solution->Properties
Select Project Dependencies tab

Select Unit test project and set checkbox on DLL project

Go to Unit test project properties

Go to C/C++->General tab

Add path to DLL project ../ConsoleApplication into Additional Include Directories

Go to Linker->General tab

Add ..\$(Configuration) into Additional Library Directories

Go to Linker->Input tab

Add lib name ConsoleApplication.lib into Additional Dependencies

Build solution and run with tests

Test->Run->All tests
