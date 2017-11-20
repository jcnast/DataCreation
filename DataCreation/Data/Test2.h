// Automatically created struct from database.
/*
  DO NOT MODIFY!
*/

struct Test2
{
	int ID;
	string Name;
	Test TestReference;

	Test2(DataManager& dataManager, int ID)
	{
		dataManager.GetData(ID);
	}
	~Test2();
};
