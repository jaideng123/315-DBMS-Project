#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"



class Database
{
private:
	vector<Relation> relations; //Contains the names of the relations in memory
	vector<string> relationsOnDisk; //Contains names of relations on disk
	vector<Relation> conditionRelations;//holds the relations for the parser
	
	void initialize();
	
public:
	Database();
	~Database();
	
	/* =================     COMMANDS    ===================== */

	void openRelation(string rName);
	void closeRelation(string rName);
	void writeRelation(string rName);
	void showRelation(string rName);
	void createRelation(string rName);
	void createRelation(string rName, vector<string> keys);
	void insertInto(string rName, string attName, string type);
	void insertInto(string rName, vector<string> entries);
	void insertInto(string rName, vector<Entry> entries);
	void updateRelation(string rName, string condRelName, vector<string> updates);
	void deleteTuplesFromRelation(string rName, string condrName);
	void deleteAttsFromRelation(string rName, string condrName);

	/* ======================================================= */

	/* ============   Input/Output functions  ================ */

	void handleInput(string fileName);
	void inputKeys(string fileLine, string rName);
	void parseFileInput(string fileLine, string rName);
	void relationToFile(string rName);

	/* ======================================================= */

	/* ===============  RELATIONAL ALGEBRA  ================== */

	void renameAttribute(string relName, vector<string> attributes);

	string crossProduct(string rOneName, string rTwoName);

	vector<vector<Entry> > selection(string rName, string entryValue, char condition, string attName);
	vector<Attribute> projection(string rName, vector<string> attrProj);

	string setUnion(string rName1, string rName2);
	string setDiff(string rName1, string rName2);

	/* ======================================================= */
	
	/* ==================  MISCELLANEOUS  ==================== */

	

	bool relationExists(string rName);
	bool isOnDisk(string rName);

	void removeRelation(string rName);
	void removeRelationFromDisk(string rName);
	void addRelation(Relation r){ conditionRelations.push_back(r); }
	void cleanUp(vector<string> rNames);
	void setDifferenceLoop(string nameSetDif, Relation rd1, Relation rd2);

	Relation& getRelation(string rName);

	/* ======================================================= */
	
	/* ================  OPERATOR OVERLOADS  ================= */

	friend ostream& operator<<(ostream& os, Database& obj);

	/* ======================================================= */
};

vector<string> getAllFilesInFolder(string fileName);

#endif /* DATABASE_H */
