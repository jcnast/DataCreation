#pragma once

#include "Data/SQL/Headers/SQLInstance.h"

namespace Data
{
	namespace SQL
	{
		SQLInstance::SQLInstance()
		{}

		SQLInstance::SQLInstance(FilePath dbPath)
		{
			SetDB(dbPath);
		}

		void SQLInstance::SetDB(FilePath dbPath)
		{
			DBPath = dbPath;
		}

		bool SQLInstance::Open()
		{
			int rc = sqlite3_open(DBPath.GetFullPath().c_str(), &DB);

			if (!rc)
			{
				LatestError = "Unable to open DB <" + DBPath.GetFullPath() + ">";
				State = DBState::Errored;
				return false;
			}
			
			State = DBState::Open;
			return true;
		}

		void SQLInstance::Close()
		{
			sqlite3_close(DB);

			State = DBState::Closed;
		}

		bool SQLInstance::Query(String sqlCall, Function<bool, Ptr<void>, List<String>, List<String>> rowOperation, Ptr<void> forwardedInfo)
		{
			if (State != DBState::Open)
			{
				LatestError = "Tried to query when DB was not in open state.";
				return false;
			}

			// need to wrap the callback, and the user-desired forwarded info so lambda can be called
			// (lambdas cannot be cast to function pointers if they capture objects - since they are _essentially_ structs if they capture)
			struct WrappedInfo
			{
				Ptr<void> ForwardedInfo;
				Function<bool, Ptr<void>, List<String>, List<String>>& RowOperation;

				WrappedInfo(Ptr<void> forwardedInfo, Function<bool, Ptr<void>, List<String>, List<String>>& rowOperation)
					: ForwardedInfo(forwardedInfo), RowOperation(rowOperation)
				{}
			};
			UniquePtr<WrappedInfo> wrappedInfoObj = MakeUnique<WrappedInfo>(forwardedInfo, rowOperation);

			auto intermediateCallback = [](Ptr<void> wrappedInfo, int columnCount, Ptr<Ptr<char>> columnValues, Ptr<Ptr<char>> columnNames) -> int
			{
				Ptr<WrappedInfo> wrappedInfoObj = static_cast<Ptr<WrappedInfo>>(wrappedInfo);

				List<String> columnValueStrings;
				List<String> columnNameStrings;

				for (int i = 0; i < columnCount; i++)
				{
					Push(columnValueStrings, String(columnValues[i]));
					Push(columnNameStrings, String(columnNames[i]));
				}

				return wrappedInfoObj->RowOperation(wrappedInfoObj->ForwardedInfo, columnValueStrings, columnNameStrings);
			};

			Ptr<Ptr<char>> errorMessage = nullptr;

			int callResult = sqlite3_exec(DB, sqlCall.c_str(), intermediateCallback, wrappedInfoObj.get(), errorMessage);

			if (callResult != SQLITE_OK)
			{
				Free(*errorMessage);
				return false;
			}

			return true;
		}

		bool SQLInstance::Query(List<String> sqlCalls, Function<bool, Ptr<void>, List<String>, List<String>> rowOperation, Ptr<void> forwardedInfo)
		{
			for (auto& sqlCall : sqlCalls)
			{
				if (!Query(sqlCall, rowOperation, forwardedInfo))
				{
					return false;
				}
			}

			return true;
		}

		String SQLInstance::GetError()
		{
			return LatestError;
		}

		void SQLInstance::Free(char* errorHolder)
		{
			LatestError = errorHolder;
			sqlite3_free(errorHolder);
		}
	}
}