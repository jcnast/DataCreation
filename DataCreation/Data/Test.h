// Automatically created struct from database.
/*
  DO NOT MODIFY!
*/

struct Test
{
	int ID;
	string Name;

	Test(DataManager& dataManager, int ID)
	{
		dataManager.GetData(ID);
	}
	~Test();
};
