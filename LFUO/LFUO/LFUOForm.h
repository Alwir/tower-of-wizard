#pragma once
#include <Windows.h>
#include "ShardList.h"


namespace LFUO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Resources;
	using namespace System::Reflection;

	enum Command {
		EMPTY,
		ADD,
		EDIT
	};


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class LFUOForm : public System::Windows::Forms::Form {
	public:
		LFUOForm(void) {
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LFUOForm() {
			if (components)
			{
				delete components;
			}
		}

	private:
		ShardList shardList;
		int selectIndex;
		int command;

		System::Windows::Forms::Button^  StartShard;
		System::Windows::Forms::Button^  AddShard;
		System::Windows::Forms::Button^  EditShard;
		System::Windows::Forms::Button^  DeleteShard;
		System::Windows::Forms::ListBox^  ListShard;
		System::Windows::Forms::Label^  LabelName;
		System::Windows::Forms::Label^  LabelUrl;
		System::Windows::Forms::Label^  LabelPort;
		System::Windows::Forms::Label^  LabelClient;
		System::Windows::Forms::TextBox^  InputName;
		System::Windows::Forms::TextBox^  InputUrl;
		System::Windows::Forms::TextBox^  InputPort;
		System::Windows::Forms::TextBox^  InputClient;

		System::Windows::Forms::GroupBox^  groupBox1;
		System::Windows::Forms::Label^  LabelAlwir;
		System::Windows::Forms::Label^  LabelHandler;
		System::Windows::Forms::Button^  butOk;
		System::Windows::Forms::Button^  butCancel;
		System::Windows::Forms::ToolTip^  toolTip1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		System::ComponentModel::IContainer^  components;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			this->StartShard = (gcnew System::Windows::Forms::Button());
			this->AddShard = (gcnew System::Windows::Forms::Button());
			this->EditShard = (gcnew System::Windows::Forms::Button());
			this->DeleteShard = (gcnew System::Windows::Forms::Button());
			this->ListShard = (gcnew System::Windows::Forms::ListBox());
			this->LabelName = (gcnew System::Windows::Forms::Label());
			this->LabelUrl = (gcnew System::Windows::Forms::Label());
			this->LabelPort = (gcnew System::Windows::Forms::Label());
			this->LabelClient = (gcnew System::Windows::Forms::Label());
			this->InputName = (gcnew System::Windows::Forms::TextBox());
			this->InputUrl = (gcnew System::Windows::Forms::TextBox());
			this->InputPort = (gcnew System::Windows::Forms::TextBox());
			this->InputClient = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->LabelAlwir = (gcnew System::Windows::Forms::Label());
			this->LabelHandler = (gcnew System::Windows::Forms::Label());
			this->butOk = (gcnew System::Windows::Forms::Button());
			this->butCancel = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// StartShard
			// 
			this->StartShard->Location = System::Drawing::Point(165, 221);
			this->StartShard->Name = L"StartShard";
			this->StartShard->Size = System::Drawing::Size(137, 127);
			this->StartShard->TabIndex = 0;
			this->StartShard->Text = L"button1";
			this->toolTip1->SetToolTip(this->StartShard, L"Запустить игру");
			this->StartShard->UseVisualStyleBackColor = true;
			this->StartShard->Click += gcnew System::EventHandler(this, &LFUOForm::StartShard_Click);
			// 
			// AddShard
			// 
			this->AddShard->Location = System::Drawing::Point(165, 45);
			this->AddShard->Name = L"AddShard";
			this->AddShard->Size = System::Drawing::Size(137, 41);
			this->AddShard->TabIndex = 1;
			this->AddShard->Text = L"button2";
			this->toolTip1->SetToolTip(this->AddShard, L"Добавить новый шард");
			this->AddShard->UseVisualStyleBackColor = true;
			this->AddShard->Click += gcnew System::EventHandler(this, &LFUOForm::AddShard_Click);
			// 
			// EditShard
			// 
			this->EditShard->Location = System::Drawing::Point(165, 102);
			this->EditShard->Name = L"EditShard";
			this->EditShard->Size = System::Drawing::Size(137, 41);
			this->EditShard->TabIndex = 2;
			this->EditShard->Text = L"button3";
			this->toolTip1->SetToolTip(this->EditShard, L"Редактировать шард");
			this->EditShard->UseVisualStyleBackColor = true;
			this->EditShard->Click += gcnew System::EventHandler(this, &LFUOForm::EditShard_Click);
			// 
			// DeleteShard
			// 
			this->DeleteShard->Location = System::Drawing::Point(165, 162);
			this->DeleteShard->Name = L"DeleteShard";
			this->DeleteShard->Size = System::Drawing::Size(137, 41);
			this->DeleteShard->TabIndex = 3;
			this->DeleteShard->Text = L"button4";
			this->toolTip1->SetToolTip(this->DeleteShard, L"Удалить шард");
			this->DeleteShard->UseVisualStyleBackColor = true;
			this->DeleteShard->Click += gcnew System::EventHandler(this, &LFUOForm::DeleteShard_Click);
			// 
			// ListShard
			// 
			this->ListShard->FormattingEnabled = true;
			this->ListShard->Location = System::Drawing::Point(10, 45);
			this->ListShard->Name = L"ListShard";
			this->ListShard->Size = System::Drawing::Size(133, 303);
			this->ListShard->TabIndex = 4;
			this->toolTip1->SetToolTip(this->ListShard, L"Список шардов");
			this->ListShard->SelectedIndexChanged += gcnew System::EventHandler(this, &LFUOForm::ListShard_SelectedIndexChanged);
			this->ListShard->DoubleClick += gcnew System::EventHandler(this, &LFUOForm::StartShard_Click);
			// 
			// LabelName
			// 
			this->LabelName->AutoSize = true;
			this->LabelName->Location = System::Drawing::Point(327, 45);
			this->LabelName->Name = L"LabelName";
			this->LabelName->Size = System::Drawing::Size(35, 13);
			this->LabelName->TabIndex = 5;
			this->LabelName->Text = L"label1";
			// 
			// LabelUrl
			// 
			this->LabelUrl->AutoSize = true;
			this->LabelUrl->Location = System::Drawing::Point(327, 102);
			this->LabelUrl->Name = L"LabelUrl";
			this->LabelUrl->Size = System::Drawing::Size(35, 13);
			this->LabelUrl->TabIndex = 6;
			this->LabelUrl->Text = L"label1";
			// 
			// LabelPort
			// 
			this->LabelPort->AutoSize = true;
			this->LabelPort->Location = System::Drawing::Point(327, 162);
			this->LabelPort->Name = L"LabelPort";
			this->LabelPort->Size = System::Drawing::Size(35, 13);
			this->LabelPort->TabIndex = 7;
			this->LabelPort->Text = L"label1";
			// 
			// LabelClient
			// 
			this->LabelClient->AutoSize = true;
			this->LabelClient->Location = System::Drawing::Point(327, 221);
			this->LabelClient->Name = L"LabelClient";
			this->LabelClient->Size = System::Drawing::Size(35, 13);
			this->LabelClient->TabIndex = 8;
			this->LabelClient->Text = L"label1";
			// 
			// InputName
			// 
			this->InputName->Location = System::Drawing::Point(330, 61);
			this->InputName->Name = L"InputName";
			this->InputName->Size = System::Drawing::Size(142, 20);
			this->InputName->TabIndex = 9;
			this->toolTip1->SetToolTip(this->InputName, L"Название шарда\r\nот 3 до 7 букв или цифр");
			this->InputName->TextChanged += gcnew System::EventHandler(this, &LFUOForm::InputName_TextChanged);
			// 
			// InputUrl
			// 
			this->InputUrl->Location = System::Drawing::Point(330, 118);
			this->InputUrl->Name = L"InputUrl";
			this->InputUrl->Size = System::Drawing::Size(142, 20);
			this->InputUrl->TabIndex = 10;
			this->toolTip1->SetToolTip(this->InputUrl, L"Адрес шарда\r\nот 3 букв или цифр");
			this->InputUrl->TextChanged += gcnew System::EventHandler(this, &LFUOForm::InputUrl_TextChanged);
			// 
			// InputPort
			// 
			this->InputPort->Location = System::Drawing::Point(330, 178);
			this->InputPort->Name = L"InputPort";
			this->InputPort->Size = System::Drawing::Size(142, 20);
			this->InputPort->TabIndex = 11;
			this->toolTip1->SetToolTip(this->InputPort, L"Порт шарда\r\nот 0 до 65536");
			this->InputPort->TextChanged += gcnew System::EventHandler(this, &LFUOForm::InputPort_TextChanged);
			// 
			// InputClient
			// 
			this->InputClient->Location = System::Drawing::Point(330, 237);
			this->InputClient->Name = L"InputClient";
			this->InputClient->Size = System::Drawing::Size(142, 20);
			this->InputClient->TabIndex = 12;
			this->toolTip1->SetToolTip(this->InputClient, L"Файл для запуска\r\n\"client.exe\"");
			this->InputClient->TextChanged += gcnew System::EventHandler(this, &LFUOForm::InputClient_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->LabelAlwir);
			this->groupBox1->Controls->Add(this->LabelHandler);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Location = System::Drawing::Point(0, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(310, 39);
			this->groupBox1->TabIndex = 15;
			this->groupBox1->TabStop = false;
			// 
			// LabelAlwir
			// 
			this->LabelAlwir->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->LabelAlwir->AutoSize = true;
			this->LabelAlwir->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->LabelAlwir->Location = System::Drawing::Point(252, 27);
			this->LabelAlwir->Name = L"LabelAlwir";
			this->LabelAlwir->Size = System::Drawing::Size(31, 9);
			this->LabelAlwir->TabIndex = 1;
			this->LabelAlwir->Text = L"label4";
			// 
			// LabelHandler
			// 
			this->LabelHandler->Dock = System::Windows::Forms::DockStyle::Top;
			this->LabelHandler->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->LabelHandler->Location = System::Drawing::Point(3, 16);
			this->LabelHandler->Name = L"LabelHandler";
			this->LabelHandler->Size = System::Drawing::Size(304, 20);
			this->LabelHandler->TabIndex = 0;
			this->LabelHandler->Text = L"label3";
			this->LabelHandler->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// butOk
			// 
			this->butOk->Location = System::Drawing::Point(330, 273);
			this->butOk->Name = L"butOk";
			this->butOk->Size = System::Drawing::Size(62, 75);
			this->butOk->TabIndex = 16;
			this->butOk->Text = L"button1";
			this->toolTip1->SetToolTip(this->butOk, L"Сохранить изменения");
			this->butOk->UseVisualStyleBackColor = true;
			this->butOk->Click += gcnew System::EventHandler(this, &LFUOForm::butOk_Click);
			// 
			// butCancel
			// 
			this->butCancel->Location = System::Drawing::Point(410, 273);
			this->butCancel->Name = L"butCancel";
			this->butCancel->Size = System::Drawing::Size(62, 75);
			this->butCancel->TabIndex = 17;
			this->butCancel->Text = L"button2";
			this->toolTip1->SetToolTip(this->butCancel, L"Отказаться от изменений");
			this->butCancel->UseVisualStyleBackColor = true;
			this->butCancel->Click += gcnew System::EventHandler(this, &LFUOForm::butCancel_Click);
			// 
			// MyForm
			// 
			this->ClientSize = System::Drawing::Size(310, 353);
			this->Controls->Add(this->butCancel);
			this->Controls->Add(this->butOk);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->InputClient);
			this->Controls->Add(this->InputPort);
			this->Controls->Add(this->InputUrl);
			this->Controls->Add(this->InputName);
			this->Controls->Add(this->LabelClient);
			this->Controls->Add(this->LabelPort);
			this->Controls->Add(this->LabelUrl);
			this->Controls->Add(this->LabelName);
			this->Controls->Add(this->ListShard);
			this->Controls->Add(this->DeleteShard);
			this->Controls->Add(this->EditShard);
			this->Controls->Add(this->AddShard);
			this->Controls->Add(this->StartShard);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &LFUOForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void StartShard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ListShard_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void AddShard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void DeleteShard_Click(System::Object^  sender, System::EventArgs^  e);

		void Messages(String^ name);
		bool isSelectItem();
		void RefreshList();
		System::Void EditShard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void butCancel_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void butOk_Click(System::Object^  sender, System::EventArgs^  e);
		void Cancel();
		System::Void InputName_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void InputUrl_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void InputPort_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void InputClient_TextChanged(System::Object^  sender, System::EventArgs^  e);
	};
}
