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
		Info info = Testing();

		System::String^ varName = msclr::interop::marshal_as<System::String^>(info.name); // имя переменной
		int varValue = info.value; // значение переменной
		System::IntPtr ptr(info.address);
		System::String^ hexAddress = "0x" + ptr.ToInt64().ToString("X");

		System::Windows::Forms::Label^ dynamicLabel = gcnew System::Windows::Forms::Label();

		System::String^ valuesText = "";

		System::String^ typeText;

		if (info.type == InfoType::Array) // если массив
		{
			typeText = "Массив: " + info.size + " элементов";
			valuesText = "[";
			for (size_t i = 0; i < info.size; i++) {
				valuesText += info.arrayPtr[i].ToString();
				if (i < info.size - 1) valuesText += ", ";
			}
			valuesText += "]";
		} else if (info.type == InfoType::Variable) { // если обычная переменная
			typeText = "Переменная";
			valuesText = info.value.ToString();
			System::Windows::Forms::TextBox^ varBox = gcnew System::Windows::Forms::TextBox();
			varBox->Text = valuesText;
			varBox->Location = System::Drawing::Point(100, 200);
			this->Controls->Add(varBox);

		}
		else if (info.type == InfoType::Function) { // если функция
			typeText = "Функия";
			System::String^ retType = info.returnType.empty() ? "void" : ToManaged(info.returnType);

			valuesText = retType + ", параметров: " + info.paramCount;

			System::String^ signature = BuildFunctionSignature(info);
			valuesText += "\nСигнатура: " + signature;

			if (info.paramCount > 0) {
				valuesText += "\nТипы параметров: ";
				for (int i = 0; i < info.paramCount; ++i) {
					if (i > 0) valuesText += ", ";
					valuesText += ToManaged(info.paramTypes[i]);
				}
			}
		}

		// координаты и авторазмер текста
		dynamicLabel->Location = System::Drawing::Point(50, 100);
		dynamicLabel->AutoSize = true;
		dynamicLabel->ForeColor = System::Drawing::Color::Black;

		dynamicLabel->Text = "Имя: " + varName + "\n" +
			"Тип: " + typeText + "\n" +
			"Значение: " + valuesText + "\n" +
			"Адрес: " + hexAddress;

		this->Controls->Add(dynamicLabel);
	}
	};
}
