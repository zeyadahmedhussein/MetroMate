

#pragma once

namespace MetroMate {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	public: System::Windows::Forms::TextBox^ Password;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ EmailLabel;

	public: System::Windows::Forms::TextBox^ Email;

	private: System::Windows::Forms::Label^ terms;
	public: System::Windows::Forms::Button^ ConfirmBtn;
	public: System::Windows::Forms::Button^ ExitBtn;


	private: System::Windows::Forms::Label^ SignUp;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Password = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->EmailLabel = (gcnew System::Windows::Forms::Label());
			this->Email = (gcnew System::Windows::Forms::TextBox());
			this->terms = (gcnew System::Windows::Forms::Label());
			this->ConfirmBtn = (gcnew System::Windows::Forms::Button());
			this->ExitBtn = (gcnew System::Windows::Forms::Button());
			this->SignUp = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::White;
			this->label6->Font = (gcnew System::Drawing::Font(L"Satoshi", 28, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(47, 126);
			this->label6->Name = L"label6";
			this->label6->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->label6->Size = System::Drawing::Size(206, 70);
			this->label6->TabIndex = 21;
			this->label6->Text = L"Sign in";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Black;
			this->label3->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label3->Location = System::Drawing::Point(63, 374);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(300, 2);
			this->label3->TabIndex = 20;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(76, 339);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 20);
			this->label4->TabIndex = 19;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::White;
			this->label5->Font = (gcnew System::Drawing::Font(L"Satoshi Medium", 7.999999F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(60, 330);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(83, 20);
			this->label5->TabIndex = 18;
			this->label5->Text = L"Password";
			// 
			// Password
			// 
			this->Password->BackColor = System::Drawing::Color::White;
			this->Password->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->Password->Font = (gcnew System::Drawing::Font(L"Satoshi", 10));
			this->Password->Location = System::Drawing::Point(64, 356);
			this->Password->Name = L"Password";
			this->Password->PasswordChar = '*';
			this->Password->Size = System::Drawing::Size(329, 27);
			this->Password->TabIndex = 17;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label2->Location = System::Drawing::Point(64, 290);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(299, 2);
			this->label2->TabIndex = 16;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(76, 250);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 20);
			this->label1->TabIndex = 15;
			// 
			// EmailLabel
			// 
			this->EmailLabel->AutoSize = true;
			this->EmailLabel->BackColor = System::Drawing::Color::White;
			this->EmailLabel->Font = (gcnew System::Drawing::Font(L"Satoshi Medium", 7.999999F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EmailLabel->Location = System::Drawing::Point(60, 245);
			this->EmailLabel->Name = L"EmailLabel";
			this->EmailLabel->Size = System::Drawing::Size(50, 20);
			this->EmailLabel->TabIndex = 14;
			this->EmailLabel->Text = L"Email";
			// 
			// Email
			// 
			this->Email->BackColor = System::Drawing::Color::White;
			this->Email->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->Email->Font = (gcnew System::Drawing::Font(L"Satoshi", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Email->Location = System::Drawing::Point(64, 269);
			this->Email->Name = L"Email";
			this->Email->Size = System::Drawing::Size(329, 27);
			this->Email->TabIndex = 13;
			// 
			// terms
			// 
			this->terms->AutoSize = true;
			this->terms->BackColor = System::Drawing::Color::White;
			this->terms->Font = (gcnew System::Drawing::Font(L"Satoshi", 7.999999F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->terms->ForeColor = System::Drawing::Color::Black;
			this->terms->Location = System::Drawing::Point(60, 511);
			this->terms->Margin = System::Windows::Forms::Padding(0);
			this->terms->Name = L"terms";
			this->terms->Size = System::Drawing::Size(184, 20);
			this->terms->TabIndex = 24;
			this->terms->Text = L"Don\'t have an account\?";
			// 
			// ConfirmBtn
			// 
			this->ConfirmBtn->BackColor = System::Drawing::Color::Blue;
			this->ConfirmBtn->FlatAppearance->BorderSize = 0;
			this->ConfirmBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ConfirmBtn->Font = (gcnew System::Drawing::Font(L"Satoshi", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ConfirmBtn->ForeColor = System::Drawing::Color::White;
			this->ConfirmBtn->Location = System::Drawing::Point(64, 418);
			this->ConfirmBtn->Margin = System::Windows::Forms::Padding(0);
			this->ConfirmBtn->Name = L"ConfirmBtn";
			this->ConfirmBtn->Size = System::Drawing::Size(133, 49);
			this->ConfirmBtn->TabIndex = 25;
			this->ConfirmBtn->Text = L"Confirm";
			this->ConfirmBtn->UseVisualStyleBackColor = false;
			this->ConfirmBtn->Click += gcnew System::EventHandler(this, &MyForm::ConfirmBtn_Click);
			// 
			// ExitBtn
			// 
			this->ExitBtn->BackColor = System::Drawing::Color::White;
			this->ExitBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ExitBtn->Font = (gcnew System::Drawing::Font(L"Satoshi", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ExitBtn->ForeColor = System::Drawing::Color::Black;
			this->ExitBtn->Location = System::Drawing::Point(230, 418);
			this->ExitBtn->Margin = System::Windows::Forms::Padding(0);
			this->ExitBtn->Name = L"ExitBtn";
			this->ExitBtn->Size = System::Drawing::Size(133, 49);
			this->ExitBtn->TabIndex = 26;
			this->ExitBtn->Text = L"Exit";
			this->ExitBtn->UseVisualStyleBackColor = false;
			this->ExitBtn->Click += gcnew System::EventHandler(this, &MyForm::ExitBtn_Click);
			// 
			// SignUp
			// 
			this->SignUp->AutoSize = true;
			this->SignUp->BackColor = System::Drawing::Color::White;
			this->SignUp->Font = (gcnew System::Drawing::Font(L"Satoshi", 7.999999F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SignUp->ForeColor = System::Drawing::Color::Blue;
			this->SignUp->Location = System::Drawing::Point(190, 511);
			this->SignUp->Margin = System::Windows::Forms::Padding(0);
			this->SignUp->Name = L"SignUp";
			this->SignUp->Size = System::Drawing::Size(67, 20);
			this->SignUp->TabIndex = 27;
			this->SignUp->Text = L"Sign Up";
			this->SignUp->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(1056, 628);
			this->Controls->Add(this->SignUp);
			this->Controls->Add(this->ExitBtn);
			this->Controls->Add(this->ConfirmBtn);
			this->Controls->Add(this->terms);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->Password);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->EmailLabel);
			this->Controls->Add(this->Email);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
#pragma endregion
	









public: System::Void ConfirmBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ ReadEmail;
	String^ ReadPassword;
	
		ReadEmail = this->Email->Text;
		ReadPassword = this->Password->Text;

	if (ReadEmail-> Length ==0||ReadPassword->Length ==0) {
		MessageBox::Show("Please enter the Email and Password");
	}
}
public: System::Void ExitBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
};
}
