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

	private: System::Windows::Forms::RadioButton^ moveLight_RB;
	private: System::Windows::Forms::RadioButton^ colorByPosition_RB;
	private: System::Windows::Forms::RadioButton^ cubesToSphere_RB;

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
			this->moveLight_RB = (gcnew System::Windows::Forms::RadioButton());
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
			this->colorByPosition_RB = (gcnew System::Windows::Forms::RadioButton());
			this->cubesToSphere_RB = (gcnew System::Windows::Forms::RadioButton());
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
			// moveLight_RB
			// 
			this->moveLight_RB->AutoSize = true;
			this->moveLight_RB->Location = System::Drawing::Point(24, 24);
			this->moveLight_RB->Name = L"moveLight_RB";
			this->moveLight_RB->Size = System::Drawing::Size(80, 17);
			this->moveLight_RB->TabIndex = 0;
			this->moveLight_RB->TabStop = true;
			this->moveLight_RB->Text = L"MoveLights";
			this->moveLight_RB->UseVisualStyleBackColor = true;
			this->moveLight_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton1_CheckedChanged);
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
			// colorByPosition_RB
			// 
			this->colorByPosition_RB->AutoSize = true;
			this->colorByPosition_RB->Location = System::Drawing::Point(24, 313);
			this->colorByPosition_RB->Name = L"colorByPosition_RB";
			this->colorByPosition_RB->Size = System::Drawing::Size(103, 17);
			this->colorByPosition_RB->TabIndex = 16;
			this->colorByPosition_RB->TabStop = true;
			this->colorByPosition_RB->Text = L"Color by Position";
			this->colorByPosition_RB->UseVisualStyleBackColor = true;
			this->colorByPosition_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton2_CheckedChanged);
			// 
			// cubesToSphere_RB
			// 
			this->cubesToSphere_RB->AutoSize = true;
			this->cubesToSphere_RB->Location = System::Drawing::Point(24, 391);
			this->cubesToSphere_RB->Name = L"cubesToSphere_RB";
			this->cubesToSphere_RB->Size = System::Drawing::Size(136, 17);
			this->cubesToSphere_RB->TabIndex = 17;
			this->cubesToSphere_RB->TabStop = true;
			this->cubesToSphere_RB->Text = L"Move Cubes by Sphere";
			this->cubesToSphere_RB->UseVisualStyleBackColor = true;
			this->cubesToSphere_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton3_CheckedChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(42, 347);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(131, 23);
			this->button2->TabIndex = 18;
			this->button2->Text = L"Reset Teapot Position";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &ToolWindow::button2_Click);
			// 
			// r_Out_Label
			// 
			this->r_Out_Label->AutoSize = true;
			this->r_Out_Label->Location = System::Drawing::Point(430, 172);
			this->r_Out_Label->Name = L"r_Out_Label";
			this->r_Out_Label->Size = System::Drawing::Size(13, 13);
			this->r_Out_Label->TabIndex = 19;
			this->r_Out_Label->Text = L"1";
			// 
			// g_Out_Label
			// 
			this->g_Out_Label->AutoSize = true;
			this->g_Out_Label->Location = System::Drawing::Point(430, 222);
			this->g_Out_Label->Name = L"g_Out_Label";
			this->g_Out_Label->Size = System::Drawing::Size(13, 13);
			this->g_Out_Label->TabIndex = 20;
			this->g_Out_Label->Text = L"1";
			// 
			// b_Out_Label
			// 
			this->b_Out_Label->AutoSize = true;
			this->b_Out_Label->Location = System::Drawing::Point(430, 270);
			this->b_Out_Label->Name = L"b_Out_Label";
			this->b_Out_Label->Size = System::Drawing::Size(13, 13);
			this->b_Out_Label->TabIndex = 21;
			this->b_Out_Label->Text = L"1";
			// 
			// specularStrength_Out_Label
			// 
			this->specularStrength_Out_Label->AutoSize = true;
			this->specularStrength_Out_Label->Location = System::Drawing::Point(387, 96);
			this->specularStrength_Out_Label->Name = L"specularStrength_Out_Label";
			this->specularStrength_Out_Label->Size = System::Drawing::Size(13, 13);
			this->specularStrength_Out_Label->TabIndex = 22;
			this->specularStrength_Out_Label->Text = L"4";
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
			this->Controls->Add(this->cubesToSphere_RB);
			this->Controls->Add(this->colorByPosition_RB);
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
			this->Controls->Add(this->moveLight_RB);
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
	enum class  Mode : char {
		SceneOne,
		SceneTwo,
		SceneThree,
	};
	static float specularStrength = 4;
	static float color_R = 1;
	static float color_G = 1;
	static float color_B = 1;
	static Mode  game_mode = Mode::SceneOne;
	static bool ResetLight = false;
	static bool ResetTeapot = false;


private:
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
			ResetLight = true;
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			ResetTeapot = true;
		}
		System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (moveLight_RB->Checked)
			{
				game_mode = Mode::SceneOne;
			}

		}
		System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (colorByPosition_RB->Checked)
			{
				game_mode = Mode::SceneTwo;
			}
		}

		System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (cubesToSphere_RB->Checked)
			{
				game_mode = Mode::SceneThree;
			}
		}
};
}	
 