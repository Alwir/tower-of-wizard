#pragma once

#define MAXSHARDS 100
#define FILENAME "lfuo.ini"

enum Pole {
	NAME,
	CLIENT,
	URL,
	PORT
};

using namespace System;

ref class ShardList
{
public:
	ref struct Shard {
		String^ name;
		String^ client;
		String^ url;
		String^ port;
	};

	ShardList();
	void Load();
	void Save();
	int GetLenght();

	void Delete(int ind);
	int Add(String^ newName, String^ newClient, String^ newUrl, String^ newPort);

	Shard^ operator[](int ind);

private:
	array<Shard^> ^allShard;

	void AddProperty(int cout, unsigned short& cout1, String^& str1);
};