// Automatically created struct from database.
/*
  DO NOT MODIFY!
*/

struct PrimaryForeignKeyTest
{
	Test2 Key;
	string Name;

	PrimaryForeignKeyTest(DataManager& dataManager, Test2 Key)
	{
		dataManager.GetData(Key);
	}
	~PrimaryForeignKeyTest();
};
