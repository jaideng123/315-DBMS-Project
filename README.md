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

##Token_Type  -  Symbol
```
TABLE - "TABLE"
OPEN  - "OPEN"
CLOSE - "CLOSE
WRITE - "WRITE"
CREATE- "CREATE"
INSERT- "INSERT"
SHOW  - "SHOW"
UPDATE- "UPDATE"
DELETE- "DELETE"
SELECT- "SELECT"
UNION - "+"
DIFF  - "-"
PRODUCT-"*"
PROJECT-"project"
RENAME- "rename"
LEFTPAREN-"("
RIGHTPAREN-")"
PRIMARY - "PRIMARY"
KEY   - "KEY"
INTO  - "INTO"
VALUES- "VALUES"
FROM  - "FROM"
LEFTARROW-"<-"
EQUALSIGN-"="
EQ    - "=="
LT    - "<"
LEQ   - "<="
GT    - ">"
GEQ   - ">="
NEQ   - "!="
AND   - "&&"
OR    - "||"
WHERE - "WHERE"
COMMA - ","
SEMICOLON - ";"
NUMBER -  "NUMBER"
VARCHAR-  "VARCHAR"
INTEGER-  "INTEGER"
RELATION- "RELATION"
EXIT  - "EXIT"
IDENTIFIER  - everything that isnt a key word
```
