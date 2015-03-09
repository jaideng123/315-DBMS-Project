#include "Database.h"

/* ===================== Constructor/Destructor ============================ */

Database::Database(){
	this->initialize();
}

Database::~Database(){

}

void Database::initialize(){
	//loads in the relations that are already on disk in database
	vector<string> fileNames = getAllFilesInFolder("Relations.db");
	for (int i = 0; i < fileNames.size(); ++i){
		this->relationsOnDisk.push_back(fileNames[i].substr(0, fileNames[i].find_first_of(".")));
	}
}

/* ========================================================================= */

/* ====================== Miscellaneous Functions ========================== */

bool Database::relationExists(string rName){
	//Checks if the relation is in memory
	//returns true if it is in memory false otherwise
	for (int i = 0; i < relations.size(); ++i){
		if (rName == relations[i].getName()){
			return true;
		}
	}
	return false;
}

bool Database::isOnDisk(string rName){
	//Checks if the relation is already on the disk
	//returns true if it is already on disk false otherwise
	for (int i = 0; i < relationsOnDisk.size(); ++i){
		if (relationsOnDisk[i] == rName){
			return true;
		}
	}
	return false;
}

void Database::removeRelation(string rName){
	//removes a relation from memory
	for (int i = 0; i < relations.size(); ++i){
		if (relations[i].getName() == rName){
			relations.erase(relations.begin() + i);
			return;
		}
	}
	cout << "Error in removeRelation() :: Relation not in Memory." << endl;
}

void Database::removeRelationFromDisk(string rName){
	//removes relation from disk but not memory
	if (this->isOnDisk(rName)){
		remove((rName + ".db").c_str()); //remove file name
		for (int i = 0; i < relationsOnDisk.size(); ++i){
			if (relationsOnDisk[i] == rName){
				relationsOnDisk.erase(relationsOnDisk.begin() + i);
			}
		}
	}
	else{
		cout << "Error in removeRelationFromDisk() :: " <<
						rName << " is not on the Disk." << endl;
	}
}

void Database::cleanUp(vector<string> rNames){
	for (int i = 0; i < rNames.size(); ++i){
		for (int k = 0; k < relations.size(); ++k){
			if (rNames[i] == relations[k].getName()){
				this->removeRelation(rNames[i]);
			}
		}
	}
}

Relation& Database::getRelation(string rName){
	//returns the relation given its name
	for (int i = 0; i < relations.size(); ++i){
		if (relations[i].getName() == rName){
			return relations[i];
		}
	}
	cout << "Error in getRelation() :: Relation " << rName << " is not in Memory." << endl;
	exit(1);
}

void Database::setDifferenceLoop(string nameSetDif, Relation rd1, Relation rd2){
	int counter = 0;
	vector<string> row;
	
	for(int x=0; x < rd1.getAttribute(0).getNumEntries(); ++x){
		for(int y=0; y < rd2.getAttribute(0).getNumEntries(); ++y){
			for(int z=0; z < rd1.getNumAttributes(); ++z){
				if( y == 0 ){
					row.push_back(rd1.getAttribute(z).getEntry(x).getData());
				}
				if(y<x && y==(rd2.getAttribute(0).getNumEntries()-1)){
					break;
				}
				if ( rd1.getAttribute(z).getEntry(x).getData() == rd2.getAttribute(z).getEntry(y).getData() ){
					counter++;
				}
			}
			if ( counter == rd1.getNumAttributes() ){
				break;
			}
			else {counter = 0;}
		}
		if(counter != rd1.getNumAttributes()){
			for(int j=0; j < rd1.getNumAttributes(); ++j){ //at this point rd1.getNumAttributes() should be equal to row.size()
				string attName = this->getRelation(nameSetDif).getAttribute(j).getName();
				this->getRelation(nameSetDif).getAttribute(attName).addEntry(row[j]);
			}
		}
		row.clear();
		counter = 0;
	}
}

/* ========================================================================= */

/* ======================= Command Functions =============================== */

void Database::openRelation(string rName){
	//Brings a file into memory if it is on the disk
	if (this->isOnDisk(rName)){
		handleInput(rName + ".db");
	}
	else{
		cout << "Error in openRelation() :: Relation isnt on Disk." << endl;
	}
}

void Database::closeRelation(string rName){
	//removes relation from memory
	this->removeRelation(rName);
}

void Database::writeRelation(string rName){
	//writes a relation to its rName.db file and 
	//the name of the relation to the Relations.db file
	ofstream outputFile;
	string fileName = "Relations.db";
	if (!(this->isOnDisk(rName)) && this->relationExists(rName)){
		relationsOnDisk.push_back(rName);
		outputFile.open(fileName.c_str(), ios::out | ios::app); //append to file not overwrite it
		if (outputFile.is_open()){
			outputFile << rName << ".db" << endl;
			outputFile.close();
		}
		else{
			cout << "Error in writeRelation() :: No file to open.\n";
		}
	}
	if (this->relationExists(rName)){
		relationToFile(rName);
	}
	else{
		cout << "Error in writeRelation() :: Relation is not in memory." << endl;
	}
}

void Database::showRelation(string rName){
	//prints the relation to the screen if it exists in memory
	if (this->relationExists(rName)){
		cout << this->getRelation(rName);
	}
	else{
		cout << "Error in showRelation() :: Relation is not in memory." << endl;
	}
}

void Database::createRelation(string rName, vector<string> keys){
	//Creates relation in memory
	if (!(this->isOnDisk(rName))){
		relations.push_back(Relation(rName, keys));
		//relationNames.push_back(rName);
	}
	else{
		cout << "Error in createRelation() :: Relation already exists." << endl;
		return;
	}
}

void Database::createRelation(string rName){
	//Creates relation in memory
	if (!(this->isOnDisk(rName))){
		relations.push_back(Relation(rName));
		//relationNames.push_back(rName);
	}
	else{
		cout << "Error in createRelation() :: Relation already exists." << endl;
	}
}

void Database::insertInto(string rName, string attName, string type){
	// adding an attribute to a relation
	stringstream ss;
	int typeResult;
	ss << type;
	ss >> typeResult;
	this->getRelation(rName).addAttribute(attName, typeResult);
}

void Database::insertInto(string rName, vector<string> entries){
	//adding entries to an attribute in a relation
	if (entries.size() != this->getRelation(rName).getNumAttributes()){
		cout << "Error in insertInto(string, vector) :: Num Entries != Attributes" << endl;
		return;
	}

	for (int i = 0; i < entries.size(); ++i){
		this->getRelation(rName).getAttribute(i).addEntry(entries[i]);
	}
}

void Database::insertInto(string rName, vector<Entry> entries){
	if (entries.size() != this->getRelation(rName).getNumAttributes()){
		cout << "Error in insertInto(string, vector) :: Num Entries != Attributes" << endl;
		return;
	}

	for (int i = 0; i < entries.size(); ++i){
		this->getRelation(rName).getAttribute(i).addEntry(entries[i]);
	}
}

void Database::updateRelation(string rName, string condRelName, vector<string> updates){
	Relation& r1 = getRelation(rName);
	Relation& r2 = getRelation(condRelName);
	
	for (int i = 0; i < updates.size(); i += 2){
		for (int k = 0; k < r1.getNumAttributes(); ++k){
			for (int l = 0; l < r2.getAttribute(k).getNumEntries(); ++l){
				for (int j = 0; j < r1.getAttribute(k).getNumEntries(); ++j){
					if (r2.getAttribute(updates[i]).getEntry(l) == r1.getAttribute(updates[i]).getEntry(j)){
						r1.getAttribute(updates[i]).getEntry(j).setData(updates[i + 1]);
					}
				}
			}
		}
	}
}

void Database::deleteTuplesFromRelation(string rName, string condrName){
	vector<int> spotsToDelete;
	vector<Entry> entries;
	int spotOfAttribute = 0;
	
	for (int i = 0; i < this->getRelation(condrName).getAttribute(0).getNumEntries(); ++i){
		//set entries to delete from relation
		entries.push_back(this->getRelation(condrName).getAttribute(0).getEntry(i));
	}
	entries.erase(unique(entries.begin(), entries.end()), entries.end());
	for (int i = 0; i < this->getRelation(rName).getAttributes().size(); ++i){
		if (this->getRelation(rName).getAttribute(i).getName() ==
			this->getRelation(condrName).getAttribute(0).getName()){
			spotOfAttribute = i;
		}
	}
	for (int i = 0; i < this->getRelation(rName).getAttribute(spotOfAttribute).getNumEntries(); ++i){
		for (int k = 0; k < entries.size(); ++k){
			if (this->getRelation(rName).getAttribute(spotOfAttribute).getEntry(i) == entries[k]){
				spotsToDelete.push_back(i);
			}
		}
	}
	for (int i = 0; i < this->getRelation(rName).getAttributes().size(); ++i){
		for (int k = spotsToDelete.size() - 1; k >= 0; --k){
			this->getRelation(rName).getAttribute(i).removeEntry(spotsToDelete[k]);
		}
	}
}

void Database::deleteAttsFromRelation(string rName, string condrName){
	for (int i = 0; i < this->getRelation(rName).getAttributes().size(); ++i){
		for (int k = 0; k < this->getRelation(condrName).getAttributes().size(); ++k){
			if (this->getRelation(rName).getAttribute(i) ==
				this->getRelation(condrName).getAttribute(k)){
				this->getRelation(rName).removeAttribute(this->getRelation(rName).getAttribute(i).getName());
			}
		}
	}
}

/* ========================================================================= */

/* ===================== Input/Output Functions ============================ */

void Database::handleInput(string fileName){
	ifstream currentFile(fileName);
	string line;
	if (currentFile.is_open()){
		getline(currentFile, line);//gets first line in file which is the relation name
		string curRel = line;
		this->relations.push_back(Relation(curRel));
		getline(currentFile, line);
		inputKeys(line, curRel);
		while (getline(currentFile, line)){
			parseFileInput(line, curRel); //handles attributes and their entries
		}
		currentFile.close();
	}
	else{
		cout << "Error in handleInput() :: No file to open." << endl;
	}
}

void Database::inputKeys(string fileLine, string rName){
	string token = "";
	string curKey;
	while (fileLine != token && fileLine != ""){
		token = fileLine.substr(0, fileLine.find_first_of(","));
		fileLine = fileLine.substr(fileLine.find_first_of(",") + 1);
		curKey = token;
		this->getRelation(rName).addKey(curKey);
	}
}

void Database::parseFileInput(string fileLine, string rName){
	string token = "";
	string curAtt;
	stringstream ss;
	int attType = -2;//invalid attType
	int spot = 0;
	
	while (fileLine != token && fileLine != ""){
		token = fileLine.substr(0, fileLine.find_first_of(","));
		fileLine = fileLine.substr(fileLine.find_first_of(",") + 1);
		if (spot < 2){
			if (spot == 0){
				curAtt = token;
			}
			else if (spot == 1){
				ss << token;
				ss >> attType;
				this->getRelation(rName).addAttribute(curAtt, attType);
			}
			spot += 1;
		}
		else{
			this->getRelation(rName).getAttribute(curAtt).addEntry(token);
		}
	}
}

void Database::relationToFile(string rName){
	//This function prints the relation and its contents
	//to the file in readable format for openRelation() function
	ofstream outputFile(rName + ".db");
	Relation currentRelation = this->getRelation(rName);
	int numAttributes = currentRelation.getNumAttributes();
	if (outputFile.is_open()){
		outputFile << rName << endl;
		for (int j = 0; j < currentRelation.getNumKeys(); ++j){
			outputFile << currentRelation.getKey(j) << ",";
		}
		outputFile << endl;
		for (int i = 0; i < numAttributes; ++i){
			int numEntries = currentRelation.getAttribute(i).getNumEntries();
			outputFile << currentRelation.getAttribute(i).getName() << "," <<
				currentRelation.getAttribute(i).getMaxLength() << ",";
			for (int k = 0; k < numEntries; ++k){
				outputFile << currentRelation.getAttribute(i).getEntry(k).getData();
				if (k != (numEntries)){
					outputFile << ",";
				}
			}
			outputFile << endl;
		}
		outputFile.close();
	}
	else{
		cout << "Error in relationToFile() :: No file to open." << endl;
	}
}

/* ========================================================================= */

/* ===================== Relation Algebra Functions ======================== */

void Database::renameAttribute(string relName, vector<string> attributes){
	//Renames the attributes in the relation
	if (attributes.size() != this->getRelation(relName).getNumAttributes()){
		cout << "Error in renameAttribute() :: Num Entries != Attributes" << endl;
		return;
	}

	for (int i = 0; i < attributes.size(); ++i){
		if (attributes[i] != "!"){ //Parser will insert '!' for attributes that aren't being changed
			this->getRelation(relName).getAttribute(i).setName(attributes[i]);
		}
	}
}

string Database::crossProduct(string rOneName, string rTwoName){
	//computes the cross product of two relations
	int numEntOne = this->getRelation(rOneName).getAttribute(0).getNumEntries(); //# rows in first relation
	int numEntTwo = this->getRelation(rTwoName).getAttribute(0).getNumEntries(); //# rows in second relation
	int numAttOne = this->getRelation(rOneName).getNumAttributes(); //# columns in first relation
	int numAttTwo = this->getRelation(rTwoName).getNumAttributes(); //# columns in second relation

	string nameOfCrossP = "CrossProduct";
	
	Relation rOne = this->getRelation(rOneName);
	Relation rTwo = this->getRelation(rTwoName);

	this->createRelation(nameOfCrossP);

	for (int i = 0; i < numAttOne; ++i){
		this->getRelation(nameOfCrossP).addAttribute(rOne.getAttribute(i).getName(), -1);
	}

	for (int i = 0; i < numAttTwo; ++i){
		this->getRelation(nameOfCrossP).addAttribute(rTwo.getAttribute(i).getName(), -1);
	}

	int numtotalAtt = this->getRelation(nameOfCrossP).getNumAttributes();
	int numtotalEnt = numEntOne * numEntTwo;
	int count1 = 0;
	int count2 = 0;

	vector<vector<string> > rows;
	vector<string> row;
	
	for (int i = 1; i < (numtotalEnt + 1); ++i){
		for (int k = 0; k < numtotalAtt; ++k){
			if (k < numAttOne){
				row.push_back(rOne.getAttribute(k).getEntry(count1).getData());
			}
			else{
				row.push_back(rTwo.getAttribute(k - numAttOne).getEntry(count2).getData());
			}
		}
		++count2;
		rows.push_back(row);
		row.clear();
		if ((i >= numEntTwo) && (i % numEntTwo == 0)){
			count2 = 0;
			++count1;
		}
	}

	for (int i = 0; i < rows.size(); ++i){
		this->insertInto(nameOfCrossP, rows[i]);
	}
	
	return nameOfCrossP;
}

vector<vector<Entry> > Database::selection(string rName, string entryValue, char condition, string attName){
	//return only the tuples that have the given entry value
	return this->getRelation(rName).selection(entryValue, condition, attName);
}

vector<Attribute> Database::projection(string rName, vector<string> attrProj){
	//return a subset of the attributes
	return this->getRelation(rName).projection(attrProj);
}

string Database::setUnion(string rName1, string rName2){
    string error1 = "Error :: Union only possible with two DIFFERENT relations.\n";
    string error2 = "Error :: Relations do not have the same number of attributes.\n";
    string error3 = "Error :: Attributes don't match.\n";
    if (rName1 == rName2){
        return error1;
    }
    Relation ru1 = this -> getRelation(rName1);
    Relation ru2 = this -> getRelation(rName2);

    int ru1att = ru1.getNumAttributes(); //# attributes in first relation
    int ru2att = ru2.getNumAttributes(); //# attributes in second relation
    int ru1ent = ru1.getAttribute(0).getNumEntries();//# of entries per attribute in relation 1
    int ru2ent = ru2.getAttribute(0).getNumEntries(); //# of entries per attribute in relation 2
    int ruent = ru1ent + ru2ent; // max number of entries per attribute in new relation
    int ru1key = ru1.getNumKeys();
    int ru2key = ru2.getNumKeys();

    string resultUnion = "SetUnion";
    this -> createRelation(resultUnion);
    

    if (ru1key == ru2key){
        for (int h = 0; h < ru1key; h++){
            this -> getRelation(resultUnion).addKey(ru1.getKey(h));
        }
    }
    if ((ru1att == ru2att)){ // if same number of attributes
        for (int x = 0; x < ru1att; ++x){ // ru1att used since the two are equal
            this->getRelation(resultUnion).addAttribute(ru1.getAttribute(x).getName(), -1);
            //This should iitialize the space for the relation created from the union

        }
    }
    else {return error2;}

    int ruatt = this -> getRelation(resultUnion).getNumAttributes(); //variable for number of attributes in ru

    for(int i = 0; i < ruatt; i++){
        ru1ent = ru1.getAttribute(i).getNumEntries();//should reset for every increment of i
        ru2ent = ru2.getAttribute(i).getNumEntries();//same as above
        ruent = ru1ent + ru2ent; //combo of two entry sizes

        int countdown = ruent;
        if ((ru1.getAttribute(i).getName()) == (ru2.getAttribute(i).getName())){
            //this checks that the attributes are the same
            //The attributes also need to be ordered the same way
            //i.e. kind == kind, name == name, etc.
            cout << this -> getRelation(resultUnion).getAttribute(i).getName() << endl;
            int k = 0;
            while(0 < countdown) { //increment for pushing entry to the attribute
                //also used as index for ru attributes
                if ((ru2.getAttribute(i).getEntry(k).getData()) ==
                    (ru1.getAttribute(i).getEntry(k).getData())){ //check for unique entry
                    this -> getRelation(resultUnion).getAttribute(i).addEntry(ru1.getAttribute(i).getEntry(k));

                    k++;
                    countdown = countdown - 2;

                }
                else if ((ru2.getAttribute(i).getEntry(k).getData()) !=
                         (ru1.getAttribute(i).getEntry(k).getData())){//if unique entry

                    this->getRelation(resultUnion).getAttribute(i).addEntry(ru1.getAttribute(i).getEntry(k));
                    countdown = countdown - 1;
                    this->getRelation(resultUnion).getAttribute(i).addEntry(ru2.getAttribute(i).getEntry(k));
                    k++;
                    countdown = countdown - 1;
                }
            }
        }
        else if((ru1.getAttribute(i)) != (ru2.getAttribute(i))){
            return error3;
        }

    }

    this->showRelation(resultUnion);
    return resultUnion;
}

string Database::setDiff(string rName1, string rName2){ //Changes made here By Adelaido Reyes
	Relation rd1 = this->getRelation(rName1);
    	Relation rd2 = this->getRelation(rName2);
    	string resultDiff = "SetDifference";

    	this->createRelation(resultDiff);

	int numAttOne = rd1.getNumAttributes(); //# columns in first relation
	int numAttTwo = rd2.getNumAttributes(); //# columns in second relation
	int numKeys = rd1.getNumKeys();
	int numKeys2 = rd2.getNumKeys();

	if( numAttOne != numAttTwo ){
		cout << "Error in setDiff(RelationName1, RelationName2) :: Num AttributesRelation1 != Num AttributesRelation2" << endl;
		exit(0);
	}

	for (int i = 0; i < numAttOne; ++i){
		if ( rd1.getAttribute(i).getName() != rd2.getAttribute(i).getName() ){
			cout << "Error in setDiff(RelationName1, RelationName2) :: Rel1Attribute" << i << " != Rel2Attribute" << i << endl;
			exit(0);
		}
	}

	if( numKeys > numKeys2 ){
		for (int h = 0; h < numKeys; ++h){
			this->getRelation(resultDiff).addKey(rd2.getKey(h));
		}
	}
	else{
		for (int h = 0; h < numKeys; ++h){
			this->getRelation(resultDiff).addKey(rd1.getKey(h));
		}
	}

	for (int i = 0; i < numAttOne; ++i){
		this->getRelation(resultDiff).addAttribute(rd1.getAttribute(i).getName(), -1);
	}
	
	setDifferenceLoop(resultDiff, rd1, rd2);
	
	this->showRelation(resultDiff); //this can be deleted
	
    	return resultDiff;
}//Changes made here

/* ========================================================================= */

/* ========================= Operator Overloads ============================ */

ostream& operator<<(ostream& os, Database& obj){
	for (int i = 0; i < obj.relations.size(); ++i){
		os << obj.relations[i];
	}
	return os;
}

/* ========================================================================= */

/* ==================== Functions Outside DB Class ========================= */

vector<string> getAllFilesInFolder(string fileName){
	//returns all the names of the files of relations on the disk
	vector<string> files;
	string relationName;
	ifstream relationFile(fileName);
	if (relationFile.is_open()){
		while (getline(relationFile, relationName)){
			files.push_back(relationName);
		}
		relationFile.close();
	}
	else{
		//cout << "Error in getAllFilesInFolder() :: \"Relations.db\" is not in the current folder." << endl;
		//cout << "You may Create relations but there are no relations to read." << endl;
	}

	return files;
}

/* ========================================================================= */
