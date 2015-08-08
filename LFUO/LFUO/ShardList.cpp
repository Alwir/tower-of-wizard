#include "ShardList.h"

using namespace System::IO;

ShardList::ShardList() {
	this->allShard = gcnew array<Shard^>(MAXSHARDS);
}

void ShardList::Load() {
	String^ fileName = FILENAME;
	StreamReader^ stream;
	while (true) {
		try {
			stream = File::OpenText(fileName);
			break;
		}
		catch (Exception^ e) {
			if (dynamic_cast<FileNotFoundException^>(e)) {
				StreamWriter^ streamWrite = File::CreateText(fileName);
				streamWrite->Close();
			}
		}
	}

	Char str;
	String^ str1;

	int cout = 0;
	UInt16 cout1 = 0;
	if (stream->Peek() >= 0) {
		this->allShard[0] = gcnew Shard();
	}

	while (stream->Peek() >= 0) {
		str = (Char)stream->Read();
		if (str == ';') {
			AddProperty(cout, cout1, str1);
		}
		else if (str == '\n' && stream->Peek() >= 0) {
			this->allShard[++cout] = gcnew Shard();
		}
		else {
			str1 += str;
		}
	}

	stream->Close();
}

void ShardList::Save() {
	String^ fileName = FILENAME;
	StreamWriter^ stream = File::CreateText(fileName);

	for (int i = 0; i<allShard->Length; i++) {
		if (allShard[i] == nullptr) {
			break;
		}
		stream->WriteLine(allShard[i]->name + ";" + allShard[i]->client + ";" + allShard[i]->url + ";" + allShard[i]->port + ";");
		stream->Flush();
	}
	stream->Close();
}

int ShardList::GetLenght() {
	return this->allShard->Length;
}

void ShardList::Delete(int ind) {
	int q = 0;
	for (int i = 0; i<this->allShard->Length; i++, q++) {
		if (ind == i) {
			delete allShard[i];
			q++;
		}
		if (allShard[q] == allShard[i]) {
			continue;
		}
		allShard[i] = allShard[q];
		if (allShard[i] == nullptr) {
			break;
		}
	}
}

int ShardList::Add(String^ newName, String^ newClient, String^ newUrl, String^ newPort) {
	for (int i = 0; i<this->allShard->Length; i++) {
		if (allShard[i] == nullptr) {
			allShard[i] = gcnew Shard();
			allShard[i]->name = newName;
			allShard[i]->client = newClient;
			allShard[i]->url = newUrl;
			allShard[i]->port = newPort;
			return i;
		}
	}
	return -1;
}

ShardList::Shard^ ShardList::operator[](int ind)
{
	return this->allShard[ind];
}

void ShardList::AddProperty(int cout, unsigned short& cout1, String ^& str1)
{
	switch (cout1) {
	case Pole::NAME:
		this->allShard[cout]->name = str1;
		cout1++;
		break;
	case Pole::CLIENT:
		this->allShard[cout]->client = str1;
		cout1++;
		break;
	case Pole::URL:
		this->allShard[cout]->url = str1;
		cout1++;
		break;
	case Pole::PORT:
		this->allShard[cout]->port = str1;
		cout1 = 0;
		break;
	}
	str1 = "";
}
