// Automatically created struct from database.
/*
  DO NOT MODIFY!
*/

struct ListTest
{
	int ID;
	List<Test> TestList;

	ListTest(DataManager& dataManager, int ID)
	{
		dataManager.GetData(ID);
	}
	~ListTest();
};
