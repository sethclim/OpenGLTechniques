#pragma once

#include <functional>
#include <iostream>
#include "GameController.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace OpenGLTechniques {

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
	private: System::Windows::Forms::RadioButton^ transform_RB;
	private: System::Windows::Forms::RadioButton^ water_RB;
	private: System::Windows::Forms::RadioButton^ space_RB;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ r_Out_Label;
	private: System::Windows::Forms::Label^ g_Out_Label;
	private: System::Windows::Forms::Label^ b_Out_Label;
	private: System::Windows::Forms::Label^ specularStrength_Out_Label;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::CheckBox^ checkBox5;

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
			this->transform_RB = (gcnew System::Windows::Forms::RadioButton());
			this->water_RB = (gcnew System::Windows::Forms::RadioButton());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->r_Out_Label = (gcnew System::Windows::Forms::Label());
			this->g_Out_Label = (gcnew System::Windows::Forms::Label());
			this->b_Out_Label = (gcnew System::Windows::Forms::Label());
			this->specularStrength_Out_Label = (gcnew System::Windows::Forms::Label());
			this->space_RB = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->specularStrength_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r_TB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			this->SuspendLayout();
			// 
			// moveLight_RB
			// 
			this->moveLight_RB->AutoSize = true;
			this->moveLight_RB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->moveLight_RB->Location = System::Drawing::Point(24, 24);
			this->moveLight_RB->Name = L"moveLight_RB";
			this->moveLight_RB->Size = System::Drawing::Size(84, 17);
			this->moveLight_RB->TabIndex = 0;
			this->moveLight_RB->TabStop = true;
			this->moveLight_RB->Text = L"MoveLight";
			this->moveLight_RB->UseVisualStyleBackColor = true;
			this->moveLight_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::moveLight_RB_CheckedChanged);
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
			this->specularStrength_TB->Location = System::Drawing::Point(179, 86);
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
			this->b_TB->Location = System::Drawing::Point(167, 239);
			this->b_TB->Maximum = 300;
			this->b_TB->Name = L"b_TB";
			this->b_TB->Size = System::Drawing::Size(255, 45);
			this->b_TB->TabIndex = 3;
			this->b_TB->Value = 100;
			this->b_TB->Scroll += gcnew System::EventHandler(this, &ToolWindow::B_TB_Callback);
			// 
			// g_TB
			// 
			this->g_TB->Location = System::Drawing::Point(167, 188);
			this->g_TB->Maximum = 300;
			this->g_TB->Name = L"g_TB";
			this->g_TB->Size = System::Drawing::Size(255, 45);
			this->g_TB->TabIndex = 4;
			this->g_TB->Value = 100;
			this->g_TB->Scroll += gcnew System::EventHandler(this, &ToolWindow::G_TB_Callback);
			// 
			// r_TB
			// 
			this->r_TB->Location = System::Drawing::Point(167, 137);
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
			this->label1->Location = System::Drawing::Point(12, 96);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Specular Strength";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 145);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Specular Color";
			this->label2->Click += gcnew System::EventHandler(this, &ToolWindow::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(125, 144);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"R";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(125, 188);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"G";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(125, 239);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 15;
			this->label5->Text = L"B";
			// 
			// colorByPosition_RB
			// 
			this->transform_RB->AutoSize = true;
			this->transform_RB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->transform_RB->Location = System::Drawing::Point(15, 280);
			this->transform_RB->Name = L"colorByPosition_RB";
			this->transform_RB->Size = System::Drawing::Size(81, 17);
			this->transform_RB->TabIndex = 16;
			this->transform_RB->TabStop = true;
			this->transform_RB->Text = L"Transform";
			this->transform_RB->UseVisualStyleBackColor = true;
			this->transform_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::transform_RB_CheckedChanged);
			// 
			// cubesToSphere_RB
			// 
			this->water_RB->AutoSize = true;
			this->water_RB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->water_RB->Location = System::Drawing::Point(16, 432);
			this->water_RB->Name = L"cubesToSphere_RB";
			this->water_RB->Size = System::Drawing::Size(99, 17);
			this->water_RB->TabIndex = 17;
			this->water_RB->TabStop = true;
			this->water_RB->Text = L"Water Scene";
			this->water_RB->UseVisualStyleBackColor = true;
			this->water_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::water_RB_CheckedChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(33, 303);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(131, 23);
			this->button2->TabIndex = 18;
			this->button2->Text = L"Reset Transform";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &ToolWindow::button2_Click);
			// 
			// r_Out_Label
			// 
			this->r_Out_Label->AutoSize = true;
			this->r_Out_Label->Location = System::Drawing::Point(421, 154);
			this->r_Out_Label->Name = L"r_Out_Label";
			this->r_Out_Label->Size = System::Drawing::Size(13, 13);
			this->r_Out_Label->TabIndex = 19;
			this->r_Out_Label->Text = L"1";
			// 
			// g_Out_Label
			// 
			this->g_Out_Label->AutoSize = true;
			this->g_Out_Label->Location = System::Drawing::Point(421, 204);
			this->g_Out_Label->Name = L"g_Out_Label";
			this->g_Out_Label->Size = System::Drawing::Size(13, 13);
			this->g_Out_Label->TabIndex = 20;
			this->g_Out_Label->Text = L"1";
			// 
			// b_Out_Label
			// 
			this->b_Out_Label->AutoSize = true;
			this->b_Out_Label->Location = System::Drawing::Point(421, 252);
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
			// radioButton1
			// 
			this->space_RB->AutoSize = true;
			this->space_RB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->space_RB->Location = System::Drawing::Point(16, 586);
			this->space_RB->Name = L"radioButton1";
			this->space_RB->Size = System::Drawing::Size(101, 17);
			this->space_RB->TabIndex = 23;
			this->space_RB->TabStop = true;
			this->space_RB->Text = L"Space Scene";
			this->space_RB->UseVisualStyleBackColor = true;
			this->space_RB->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::space_RB_CheckedChanged_1);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(32, 332);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(70, 17);
			this->checkBox1->TabIndex = 24;
			this->checkBox1->Text = L"Translate";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(32, 366);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(58, 17);
			this->checkBox2->TabIndex = 25;
			this->checkBox2->Text = L"Rotate";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(32, 398);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(53, 17);
			this->checkBox3->TabIndex = 26;
			this->checkBox3->Text = L"Scale";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(148, 452);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(274, 45);
			this->trackBar1->TabIndex = 27;
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(148, 503);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(274, 45);
			this->trackBar2->TabIndex = 28;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(85, 462);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(57, 13);
			this->label6->TabIndex = 29;
			this->label6->Text = L"Frequency";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(85, 503);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(53, 13);
			this->label7->TabIndex = 30;
			this->label7->Text = L"Amplitude";
			this->label7->Click += gcnew System::EventHandler(this, &ToolWindow::label7_Click);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(33, 530);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(107, 17);
			this->checkBox4->TabIndex = 31;
			this->checkBox4->Text = L"Wireframe render";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBox4_CheckedChanged);
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(33, 548);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(68, 17);
			this->checkBox5->TabIndex = 32;
			this->checkBox5->Text = L"Tint Blue";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(532, 615);
			this->Controls->Add(this->checkBox5);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->space_RB);
			this->Controls->Add(this->specularStrength_Out_Label);
			this->Controls->Add(this->b_Out_Label);
			this->Controls->Add(this->g_Out_Label);
			this->Controls->Add(this->r_Out_Label);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->water_RB);
			this->Controls->Add(this->transform_RB);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

public:
	enum class  Mode : char {
		SceneOne,
		SceneTwo,
		SceneThree,
		SceneFour
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

		System::Void moveLight_RB_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (moveLight_RB->Checked)
			{
				game_mode = Mode::SceneOne;
			}

		}
		System::Void transform_RB_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (transform_RB->Checked)
			{
				game_mode = Mode::SceneTwo;
			}
		}

		System::Void water_RB_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (water_RB->Checked)
			{
				game_mode = Mode::SceneThree;
			}
		}

		System::Void space_RB_CheckedChanged_1(System::Object^ sender, System::EventArgs^ e) {
			if (space_RB->Checked)
			{
				game_mode = Mode::SceneFour;
			}
		}

private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}	
 