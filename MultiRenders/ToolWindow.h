#pragma once

#include <functional>
#include <iostream>
#include "GameController.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace MultiRenders {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		ToolWindow(void)
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
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TrackBar^ specularStrength_TB;
	private: System::Windows::Forms::TrackBar^ b_TB;
	private: System::Windows::Forms::TrackBar^ g_TB;
	private: System::Windows::Forms::TrackBar^ r_TB;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ r_Out_Label;
	private: System::Windows::Forms::Label^ g_Out_Label;
	private: System::Windows::Forms::Label^ b_Out_Label;
	private: System::Windows::Forms::Label^ specularStrength_Out_Label;

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
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->specularStrength_TB = (gcnew System::Windows::Forms::TrackBar());
			this->b_TB = (gcnew System::Windows::Forms::TrackBar());
			this->g_TB = (gcnew System::Windows::Forms::TrackBar());
			this->r_TB = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->r_Out_Label = (gcnew System::Windows::Forms::Label());
			this->g_Out_Label = (gcnew System::Windows::Forms::Label());
			this->b_Out_Label = (gcnew System::Windows::Forms::Label());
			this->specularStrength_Out_Label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->specularStrength_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r_TB))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(24, 24);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(80, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"MoveLights";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton1_CheckedChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(42, 47);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(153, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Reset Light Position";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ToolWindow::button1_Click);
			// 
			// specularStrength_TB
			// 
			this->specularStrength_TB->Location = System::Drawing::Point(134, 88);
			this->specularStrength_TB->Maximum = 128;
			this->specularStrength_TB->Minimum = 1;
			this->specularStrength_TB->Name = L"specularStrength_TB";
			this->specularStrength_TB->Size = System::Drawing::Size(255, 45);
			this->specularStrength_TB->TabIndex = 2;
			this->specularStrength_TB->Value = 4;
			this->specularStrength_TB->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularStrength_TB_Callback);
			// 
			// b_TB
			// 
			this->b_TB->Location = System::Drawing::Point(176, 257);
			this->b_TB->Maximum = 300;
			this->b_TB->Name = L"b_TB";
			this->b_TB->Size = System::Drawing::Size(255, 45);
			this->b_TB->TabIndex = 3;
			this->b_TB->Value = 100;
			this->b_TB->Scroll += gcnew System::EventHandler(this, &ToolWindow::B_TB_Callback);
			// 
			// g_TB
			// 
			this->g_TB->Location = System::Drawing::Point(176, 206);
			this->g_TB->Maximum = 300;
			this->g_TB->Name = L"g_TB";
			this->g_TB->Size = System::Drawing::Size(255, 45);
			this->g_TB->TabIndex = 4;
			this->g_TB->Value = 100;
			this->g_TB->Scroll += gcnew System::EventHandler(this, &ToolWindow::G_TB_Callback);
			// 
			// r_TB
			// 
			this->r_TB->Location = System::Drawing::Point(176, 155);
			this->r_TB->Maximum = 300;
			this->r_TB->Name = L"r_TB";
			this->r_TB->Size = System::Drawing::Size(247, 45);
			this->r_TB->TabIndex = 5;
			this->r_TB->Value = 100;
			this->r_TB->Scroll += gcnew System::EventHandler(this, &ToolWindow::R_TB_Callback);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 97);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Specular Strength";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 163);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Specular Color";
			this->label2->Click += gcnew System::EventHandler(this, &ToolWindow::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(134, 162);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"R";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(134, 206);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"G";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(134, 257);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 15;
			this->label5->Text = L"B";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(24, 313);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(103, 17);
			this->radioButton2->TabIndex = 16;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Color by Position";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(24, 391);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(136, 17);
			this->radioButton3->TabIndex = 17;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Move Cubes by Sphere";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(42, 347);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(131, 23);
			this->button2->TabIndex = 18;
			this->button2->Text = L"Reset Teapot Position";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// r_Out_Label
			// 
			this->r_Out_Label->AutoSize = true;
			this->r_Out_Label->Location = System::Drawing::Point(430, 172);
			this->r_Out_Label->Name = L"r_Out_Label";
			this->r_Out_Label->Size = System::Drawing::Size(38, 13);
			this->r_Out_Label->TabIndex = 19;
			this->r_Out_Label->Text = L"R_Out";
			// 
			// g_Out_Label
			// 
			this->g_Out_Label->AutoSize = true;
			this->g_Out_Label->Location = System::Drawing::Point(430, 222);
			this->g_Out_Label->Name = L"g_Out_Label";
			this->g_Out_Label->Size = System::Drawing::Size(38, 13);
			this->g_Out_Label->TabIndex = 20;
			this->g_Out_Label->Text = L"G_Out";
			// 
			// b_Out_Label
			// 
			this->b_Out_Label->AutoSize = true;
			this->b_Out_Label->Location = System::Drawing::Point(430, 270);
			this->b_Out_Label->Name = L"b_Out_Label";
			this->b_Out_Label->Size = System::Drawing::Size(37, 13);
			this->b_Out_Label->TabIndex = 21;
			this->b_Out_Label->Text = L"B_Out";
			// 
			// specularStrength_Out_Label
			// 
			this->specularStrength_Out_Label->AutoSize = true;
			this->specularStrength_Out_Label->Location = System::Drawing::Point(387, 96);
			this->specularStrength_Out_Label->Name = L"specularStrength_Out_Label";
			this->specularStrength_Out_Label->Size = System::Drawing::Size(35, 13);
			this->specularStrength_Out_Label->TabIndex = 22;
			this->specularStrength_Out_Label->Text = L"label6";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(532, 422);
			this->Controls->Add(this->specularStrength_Out_Label);
			this->Controls->Add(this->b_Out_Label);
			this->Controls->Add(this->g_Out_Label);
			this->Controls->Add(this->r_Out_Label);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->r_TB);
			this->Controls->Add(this->g_TB);
			this->Controls->Add(this->b_TB);
			this->Controls->Add(this->specularStrength_TB);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->radioButton1);
			this->Name = L"ToolWindow";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->specularStrength_TB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b_TB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g_TB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r_TB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

public:
	static float specularStrength = 0;
	static float color_R = 0;
	static float color_G = 0;
	static float color_B = 0;


private:
		System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
		}

		//Slider Callbacks
		System::Void SpecularStrength_TB_Callback(System::Object^ sender, System::EventArgs^ e)
		{
			specularStrength = specularStrength_TB->Value;
			specularStrength_Out_Label->Text = specularStrength.ToString();
		}

		System::Void R_TB_Callback(System::Object^ sender, System::EventArgs^ e)
		{
			color_R = RemapSlider(r_TB->Value);
			r_Out_Label->Text = color_R.ToString();
		}

		System::Void G_TB_Callback(System::Object^ sender, System::EventArgs^ e)
		{
			color_G = RemapSlider(g_TB->Value);
			g_Out_Label->Text = color_G.ToString();
		}

		System::Void B_TB_Callback(System::Object^ sender, System::EventArgs^ e) 
		{
			color_B = RemapSlider(b_TB->Value);
			b_Out_Label->Text = color_B.ToString();
		}

		float RemapSlider(int value)
		{
			return (float)value / 100;
		}

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
		{


		}
};
}	
 