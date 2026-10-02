#pragma once
#include "testing.h"
#include <msclr/marshal_cppstd.h>

inline System::String^ ToManaged(const std::string& s) {
	return msclr::interop::marshal_as<System::String^>(s);
}

System::String^ BuildFunctionSignature(Info% info) {
	System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

	// возвращаемый тип
	if (!info.returnType.empty())
		sb->Append(ToManaged(info.returnType))->Append(" ");
	else
		sb->Append("void ");

	// имя функции
	sb->Append(ToManaged(info.name))->Append("(");

	// параметры
	if (info.paramCount == 0) {
		sb->Append("void");
	}
	else {
		for (int i = 0; i < info.paramCount; ++i) {
			if (i > 0) sb->Append(", ");
			sb->Append(ToManaged(info.paramTypes[i]));
			sb->Append(" arg")->Append(i + 1);
		}
	}

	sb->Append(")");
	return sb->ToString();
}

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
			delete info;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		Info* info = nullptr;
		System::Windows::Forms::TextBox^ varBox = nullptr;
		System::Windows::Forms::Label^ dynamicLabel = nullptr;

		void ShowInfo() {
			if (info == nullptr) return;

			System::IntPtr ptr(info->address);
			System::String^ hexAddress = "0x" + ptr.ToInt64().ToString("X");
			System::String^ valuesText = "";
			System::String^ typeText = "";

			if (info->type == InfoType::Array) {
				typeText = "Массив: " + info->size + " элементов";
				valuesText = "[";
				for (size_t i = 0; i < info->size; i++) {
					valuesText += info->arrayPtr[i].ToString();
					if (i < info->size - 1) valuesText += ", ";
				}
				valuesText += "]";
			}
			else if (info->type == InfoType::Variable) {
				typeText = "Переменная (" + ToManaged(info->typeName) + ")";
				valuesText = ToManaged(info->getValue());
			}
			else if (info->type == InfoType::Function) {
				typeText = "Функция";
				System::String^ retType = info->returnType.empty() ? "void" : ToManaged(info->returnType);
				valuesText = retType + ", параметров: " + info->paramCount;
				valuesText += "\nСигнатура: " + BuildFunctionSignature(*info);
			}

			dynamicLabel->Text = "Имя: " + ToManaged(info->name) + "\n" +
				"Тип: " + typeText + "\n" +
				"Значение: " + valuesText + "\n" +
				"Адрес: " + hexAddress;
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(515, 720);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(259, 67);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Начать контроль";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &App::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1147, 720);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(254, 67);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Обновить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &App::button2_Click);
			// 
			// App
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1939, 893);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"App";
			this->Text = L"App";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dynamicLabel != nullptr) { this->Controls->Remove(dynamicLabel); dynamicLabel = nullptr; }
		if (varBox != nullptr) { this->Controls->Remove(varBox);       varBox = nullptr; }
		delete info;
		info = new Info(Testing());

		dynamicLabel = gcnew System::Windows::Forms::Label();
		dynamicLabel->Location = System::Drawing::Point(50, 100);
		dynamicLabel->AutoSize = true;
		dynamicLabel->ForeColor = System::Drawing::Color::Black;
		this->Controls->Add(dynamicLabel);

		if (info->type == InfoType::Variable && info->getValue) {
			varBox = gcnew System::Windows::Forms::TextBox();
			varBox->Location = System::Drawing::Point(100, 250);
			varBox->Text = ToManaged(info->getValue());
			this->Controls->Add(varBox);
		}

		ShowInfo();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (info == nullptr) return;

		if (info->type == InfoType::Variable && varBox != nullptr && info->setValue) {
			std::string s = msclr::interop::marshal_as<std::string>(varBox->Text);
			info->setValue(s);                                  
			varBox->Text = ToManaged(info->getValue());        
		}
		ShowInfo();
	}
};
}
