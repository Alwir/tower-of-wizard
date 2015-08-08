#include "LFUOForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Text::RegularExpressions;
using namespace System::IO;
using namespace System::Diagnostics;

System::Void LFUO::LFUOForm::MyForm_Load(System::Object ^ sender, System::EventArgs ^ e) {
	ResourceManager^ res = gcnew ResourceManager("LFUO.Resource", Reflection::Assembly::GetExecutingAssembly());

	this->selectIndex = -1;
	String^ locText = "";

	if (GetUserDefaultUILanguage() != LANG_RUSSIAN + 1024) {
		locText = "En";
	}

	this->StartShard->Text = res->GetString("Start" + locText);
	this->AddShard->Text = res->GetString("Add" + locText);
	this->EditShard->Text = res->GetString("Edit" + locText);
	this->DeleteShard->Text = res->GetString("Delete" + locText);
	this->LabelName->Text = res->GetString("LabName" + locText);
	this->LabelUrl->Text = res->GetString("LabUrl" + locText);
	this->LabelPort->Text = res->GetString("LabPort" + locText);
	this->LabelClient->Text = res->GetString("LabClient" + locText);
	this->Text = res->GetString("AppName" + locText);
	this->LabelHandler->Text = res->GetString("LabHandler" + locText);
	this->LabelAlwir->Text = res->GetString("LabAlwir" + locText);
	this->butOk->Text = res->GetString("ButOk" + locText);
	this->butCancel->Text = res->GetString("ButCancel" + locText);

	this->toolTip1->SetToolTip(this->StartShard, res->GetString("TTStart" + locText));//L"Запустить игру");
	this->toolTip1->SetToolTip(this->AddShard, res->GetString("TTAdd" + locText));//L"Добавить новый шард");
	this->toolTip1->SetToolTip(this->EditShard, res->GetString("TTEdit" + locText));//L"Редактировать шард");
	this->toolTip1->SetToolTip(this->DeleteShard, res->GetString("TTDelete" + locText));//L"Удалить шард");
	this->toolTip1->SetToolTip(this->ListShard, res->GetString("TTList" + locText));//L"Список шардов");
	this->toolTip1->SetToolTip(this->InputName, res->GetString("TTName" + locText));//L"Название шарда\r\nот 3 до 7 букв или цифр");
	this->toolTip1->SetToolTip(this->InputUrl, res->GetString("TTUrl" + locText));//L"Адрес шарда\r\nот 3 букв или цифр");
	this->toolTip1->SetToolTip(this->InputPort, res->GetString("TTPort" + locText));//L"Порт шарда\r\nот 0 до 65536");
	this->toolTip1->SetToolTip(this->InputClient, res->GetString("TTClient" + locText));//L"Файл для запуска\r\n\"client.exe\"");
	this->toolTip1->SetToolTip(this->butOk, res->GetString("TTOk" + locText));//L"Сохранить изменения");
	this->toolTip1->SetToolTip(this->butCancel, res->GetString("TTCancel" + locText));//L"Отказаться от изменений");


	this->shardList.Load();

	RefreshList();

	return System::Void();
}

System::Void LFUO::LFUOForm::StartShard_Click(System::Object ^ sender, System::EventArgs ^ e) {
	if (!isSelectItem()) {
		return System::Void();
	}

	String^ fileName = "login.cfg";
	StreamWriter^ stream = File::CreateText(fileName);

	stream->WriteLine("LoginServer=" + shardList[this->selectIndex]->url + ", " + shardList[this->selectIndex]->port);
	stream->Flush();
	stream->Close();

	try {
		Process^ myProcess = gcnew Process();
		myProcess->StartInfo->FileName = shardList[this->selectIndex]->client;
		myProcess->Start();
	}
	catch (Exception^ e) {
		Messages("MessNoClient");
		return System::Void();
	}

	this->Close();
	return System::Void();
}

System::Void LFUO::LFUOForm::ListShard_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e) {
	this->selectIndex = ListShard->SelectedIndex;
}

System::Void LFUO::LFUOForm::AddShard_Click(System::Object ^ sender, System::EventArgs ^ e) {
	this->ClientSize = System::Drawing::Size(483, 353);
	this->command = Command::ADD;

	return System::Void();
}

System::Void LFUO::LFUOForm::DeleteShard_Click(System::Object ^ sender, System::EventArgs ^ e) {
	if (!isSelectItem()) {
		return System::Void();
	}
	this->shardList.Delete(this->selectIndex);
	this->selectIndex--;
	RefreshList();
	Cancel();

	this->shardList.Save();

	return System::Void();
}

System::Void LFUO::LFUOForm::EditShard_Click(System::Object ^ sender, System::EventArgs ^ e) {
	if (!isSelectItem()) {
		return System::Void();
	}
	this->ClientSize = System::Drawing::Size(483, 353);
	this->command = Command::EDIT;

	this->InputName->Text = shardList[this->selectIndex]->name;
	this->InputClient->Text = shardList[this->selectIndex]->client;
	this->InputUrl->Text = shardList[this->selectIndex]->url;
	this->InputPort->Text = shardList[this->selectIndex]->port;

	return System::Void();
}

System::Void LFUO::LFUOForm::butCancel_Click(System::Object ^ sender, System::EventArgs ^ e) {
	Cancel();
	return System::Void();
}

System::Void LFUO::LFUOForm::butOk_Click(System::Object ^ sender, System::EventArgs ^ e) {
	if (this->InputName->ForeColor == ForeColor.Red || this->InputClient->ForeColor == ForeColor.Red ||
		this->InputUrl->ForeColor == ForeColor.Red || this->InputPort->ForeColor == ForeColor.Red) {
		Messages("MessNoValid");
		return;
	}

	if (this->InputName->Text == "" || this->InputClient->Text == "" ||
		this->InputUrl->Text == "" || this->InputPort->Text == "") {
		Messages("MessEmptyField");
		return;
	}

	switch (this->command) {
	case Command::EMPTY:
		break;
	case Command::EDIT:
		shardList[this->selectIndex]->name = this->InputName->Text;
		shardList[this->selectIndex]->client = this->InputClient->Text;
		shardList[this->selectIndex]->url = this->InputUrl->Text;
		shardList[this->selectIndex]->port = this->InputPort->Text;
		break;
	case Command::ADD:
		this->selectIndex = shardList.Add(this->InputName->Text, this->InputClient->Text, this->InputUrl->Text, this->InputPort->Text);
		break;
	}
	Cancel();
	RefreshList();
	this->shardList.Save();

	return System::Void();
}


System::Void LFUO::LFUOForm::InputName_TextChanged(System::Object ^ sender, System::EventArgs ^ e) {
	String^ regStr = "^[A-Za-zА-Яа-я0-9]{3,7}$"; //from 3 to 7 letters or digits

	if (Regex::IsMatch(this->InputName->Text, regStr)) {
		this->InputName->ForeColor = ForeColor.Green;
	}
	else {
		this->InputName->ForeColor = ForeColor.Red;
	}

	return System::Void();
}

System::Void LFUO::LFUOForm::InputUrl_TextChanged(System::Object ^ sender, System::EventArgs ^ e) {
	String^ regStr = "^[A-Za-z0-9.]{3,}$";

	if (Regex::IsMatch(this->InputUrl->Text, regStr)) {
		this->InputUrl->ForeColor = ForeColor.Green;
	}
	else {
		this->InputUrl->ForeColor = ForeColor.Red;
	}

	return System::Void();
}

System::Void LFUO::LFUOForm::InputPort_TextChanged(System::Object ^ sender, System::EventArgs ^ e) {
	int provInt = -10;
	bool parsed = Int32::TryParse(this->InputPort->Text, provInt);

	if (parsed && provInt>0 && provInt<65356) {
		this->InputPort->ForeColor = ForeColor.Green;
	}
	else {
		this->InputPort->ForeColor = ForeColor.Red;
	}
	return System::Void();
}

System::Void LFUO::LFUOForm::InputClient_TextChanged(System::Object ^ sender, System::EventArgs ^ e) {
	String^ regStr = "^[A-Za-zА-Яа-я0-9]{3,}$";
	String^ regStrFull = "^[A-Za-zА-Яа-я0-9]{3,}.exe$";

	if (Regex::IsMatch(this->InputClient->Text, regStr)) {
		this->InputClient->ForeColor = ForeColor.Green;
		this->InputClient->Text += ".exe";
	}
	else if (Regex::IsMatch(this->InputClient->Text, regStrFull)) {
		this->InputClient->ForeColor = ForeColor.Green;
	}
	else {
		this->InputClient->ForeColor = ForeColor.Red;
	}
	return System::Void();
}

void LFUO::LFUOForm::Cancel() {
	this->ClientSize = System::Drawing::Size(310, 353);
	this->InputName->Text = "";
	this->InputClient->Text = "";
	this->InputUrl->Text = "";
	this->InputPort->Text = "";
	this->command = Command::EMPTY;
}

void LFUO::LFUOForm::Messages(String ^ name) {

	ResourceManager^ res = gcnew ResourceManager("LFUO.Resource", Reflection::Assembly::GetExecutingAssembly());
	String^ locText = "";
	if (GetUserDefaultUILanguage() != LANG_RUSSIAN + 1024) {
		locText = "En";
	}
	MessageBox::Show(res->GetString(name + locText), res->GetString("MessError" + locText), MessageBoxButtons::OK, MessageBoxIcon::Warning);
}

bool LFUO::LFUOForm::isSelectItem() {
	if (this->selectIndex<0) {
		Messages("MessNoSelected");
		return false;
	}
	return true;
}

void LFUO::LFUOForm::RefreshList() {
	ListShard->Items->Clear();

	for (int i = 0; i<this->shardList.GetLenght(); i++) {
		if (shardList[i] == nullptr) {
			break;
		}
		ListShard->Items->Add(shardList[i]->name);
	}
	ListShard->SelectedIndex = this->selectIndex;
}
