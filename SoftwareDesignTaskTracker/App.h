#pragma once
#include "testing.h"
#include <msclr/marshal_cppstd.h>

namespace SoftwareDesignTaskTracker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for App
	/// </summary>
	public ref class App : public System::Windows::Forms::Form
	{
	public:
		App(void)
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
		~App()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(866, 732);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(259, 67);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Начать контроль";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &App::button1_Click);
			// 
			// App
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1939, 893);
			this->Controls->Add(this->button1);
			this->Name = L"App";
			this->Text = L"App";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		VarInfo info = runTesting();

		System::String^ varName = msclr::interop::marshal_as<System::String^>(info.name);
		int varValue = info.value;

		System::Windows::Forms::MessageBox::Show(varName + " = " + varValue);
	}
	};
}
