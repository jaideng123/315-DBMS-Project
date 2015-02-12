## Basic work flow:
  
  First time set up
  
    $  git clone https://github.com/jaideng123/315-DBMS-Project.git
    
  Before you start working on anything
  
    write what you are working on in the development log
     $  git pull
    
  Once you've finished working on something
  
    write that you finished it in the development log
    $  git add .
    $  git commit -m "title of commit goes here"
    $  git push
    
  To scrap what you've got and restart from the latest commit
  
    $  git checkout .

## Coding Style guidelines:
```
  int example_function(int arg2, int arg1){
    if(true == true)
      //1 line code here
    if(true == false){
      //2+ line code here
      //2+ line code here
    }
  }
```
* use underscores for names
* follow bracing in example
* minimize use of c++11/14 functions

##Directory for .db files
  The directory for the .db files will be named Databases
