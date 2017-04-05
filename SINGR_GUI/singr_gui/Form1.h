#pragma once
//#include <StdAfx.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <fstream>
#include "clientExample.h"
#include "captureWaveform.h"
#include "changeAxesPopUp.h"
#include "setCutsPopUp.h"

namespace singr_gui {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace std;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//findPorts();
			//
			//TODO: Add the constructor code here
			//
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  diagnosticWindowToolStripMenuItem;





	private: System::Windows::Forms::ToolStripMenuItem^  captureWaveformsToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_FOM;
	private: System::Windows::Forms::ToolStripMenuItem^  pSDOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeAxesToolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  clearChartToolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  spectrumOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeAxesToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  clearChartToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  changeBinWidthToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addCutsOnPSDToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fOMOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeAxesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearChartToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addCutsOnEnergyToolStripMenuItem;
	private: System::Windows::Forms::CheckBox^  chk_stf;
	private: System::Windows::Forms::CheckBox^  chk_atf;
	private: System::Windows::Forms::TextBox^  tb_baseline;
	private: System::Windows::Forms::TextBox^  tb_short;
	private: System::Windows::Forms::TextBox^  tb_long;
	private: System::Windows::Forms::TextBox^  tb_full;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  b_SetIntegrationTimes;
	private: System::Windows::Forms::Button^  b_setTriggerThreshold;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  tb_threshold;

	private: System::Windows::Forms::Label^  label7;
	public: 
		// try and declare public variables here
		static bool continueLooping = true;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  b_CapturePSD;
	protected: 

		

	protected: 







	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::TextBox^  tb_updates;



	private: System::Windows::Forms::TextBox^  tb_savefilename;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  b_saveFile;


	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_PSD;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_ESpectrum;







	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->b_CapturePSD = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->tb_updates = (gcnew System::Windows::Forms::TextBox());
			this->tb_savefilename = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->b_saveFile = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->ch_PSD = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->ch_ESpectrum = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->diagnosticWindowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->captureWaveformsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pSDOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->spectrumOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeBinWidthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addCutsOnPSDToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fOMOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addCutsOnEnergyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ch_FOM = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chk_stf = (gcnew System::Windows::Forms::CheckBox());
			this->chk_atf = (gcnew System::Windows::Forms::CheckBox());
			this->tb_baseline = (gcnew System::Windows::Forms::TextBox());
			this->tb_short = (gcnew System::Windows::Forms::TextBox());
			this->tb_long = (gcnew System::Windows::Forms::TextBox());
			this->tb_full = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->b_SetIntegrationTimes = (gcnew System::Windows::Forms::Button());
			this->b_setTriggerThreshold = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tb_threshold = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_PSD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_ESpectrum))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_FOM))->BeginInit();
			this->SuspendLayout();
			// 
			// b_CapturePSD
			// 
			this->b_CapturePSD->Location = System::Drawing::Point(1023, 418);
			this->b_CapturePSD->Name = L"b_CapturePSD";
			this->b_CapturePSD->Size = System::Drawing::Size(125, 42);
			this->b_CapturePSD->TabIndex = 4;
			this->b_CapturePSD->Text = L"Capture PSD";
			this->b_CapturePSD->UseVisualStyleBackColor = true;
			this->b_CapturePSD->Click += gcnew System::EventHandler(this, &Form1::b_CapturePSD_Click);
			// 
			// tb_updates
			// 
			this->tb_updates->Location = System::Drawing::Point(913, 392);
			this->tb_updates->Name = L"tb_updates";
			this->tb_updates->ReadOnly = true;
			this->tb_updates->Size = System::Drawing::Size(235, 20);
			this->tb_updates->TabIndex = 7;
			// 
			// tb_savefilename
			// 
			this->tb_savefilename->Location = System::Drawing::Point(746, 665);
			this->tb_savefilename->Name = L"tb_savefilename";
			this->tb_savefilename->ReadOnly = true;
			this->tb_savefilename->Size = System::Drawing::Size(402, 20);
			this->tb_savefilename->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(743, 646);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Save File Location:";
			// 
			// b_saveFile
			// 
			this->b_saveFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_saveFile->Location = System::Drawing::Point(936, 617);
			this->b_saveFile->Name = L"b_saveFile";
			this->b_saveFile->Size = System::Drawing::Size(112, 42);
			this->b_saveFile->TabIndex = 11;
			this->b_saveFile->Text = L"Choose Save File...";
			this->b_saveFile->UseVisualStyleBackColor = true;
			this->b_saveFile->Click += gcnew System::EventHandler(this, &Form1::b_saveFile_Click);
			// 
			// ch_PSD
			// 
			this->ch_PSD->BorderlineColor = System::Drawing::Color::Black;
			this->ch_PSD->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->Maximum = 200000;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"Energy (keV)";
			chartArea1->AxisY->Maximum = 2;
			chartArea1->AxisY->Minimum = 0;
			chartArea1->AxisY->Title = L"PSD Ratio";
			chartArea1->Name = L"ChartArea1";
			this->ch_PSD->ChartAreas->Add(chartArea1);
			this->ch_PSD->Location = System::Drawing::Point(12, 27);
			this->ch_PSD->Name = L"ch_PSD";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series1->Name = L"Series1";
			series2->BorderWidth = 4;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series2->MarkerSize = 100;
			series2->Name = L"series_EnergyCutRight";
			series3->BorderWidth = 4;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series3->MarkerSize = 100;
			series3->Name = L"series_EnergyCutLeft";
			series4->BorderWidth = 4;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Blue;
			series4->Name = L"series_psdRatioCutUpper";
			series5->BorderWidth = 4;
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Color = System::Drawing::Color::Blue;
			series5->Name = L"series_psdRatioCutLower";
			this->ch_PSD->Series->Add(series1);
			this->ch_PSD->Series->Add(series2);
			this->ch_PSD->Series->Add(series3);
			this->ch_PSD->Series->Add(series4);
			this->ch_PSD->Series->Add(series5);
			this->ch_PSD->Size = System::Drawing::Size(709, 336);
			this->ch_PSD->TabIndex = 12;
			this->ch_PSD->Text = L"chart1";
			// 
			// ch_ESpectrum
			// 
			this->ch_ESpectrum->BorderlineColor = System::Drawing::Color::Black;
			this->ch_ESpectrum->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea2->AxisX->IsStartedFromZero = false;
			chartArea2->AxisX->Maximum = 200000;
			chartArea2->AxisX->Minimum = 0;
			chartArea2->AxisX->Title = L"Energy (keV)";
			chartArea2->AxisY->IsStartedFromZero = false;
			chartArea2->AxisY->Maximum = 500;
			chartArea2->AxisY->Minimum = 0;
			chartArea2->AxisY->Title = L"Counts";
			chartArea2->Name = L"ChartArea1";
			this->ch_ESpectrum->ChartAreas->Add(chartArea2);
			this->ch_ESpectrum->Location = System::Drawing::Point(12, 369);
			this->ch_ESpectrum->Name = L"ch_ESpectrum";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
			series6->Name = L"Series1";
			this->ch_ESpectrum->Series->Add(series6);
			this->ch_ESpectrum->Size = System::Drawing::Size(709, 318);
			this->ch_ESpectrum->TabIndex = 13;
			this->ch_ESpectrum->Text = L"chart2";
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->fileToolStripMenuItem, 
				this->diagnosticWindowToolStripMenuItem, this->pSDOptionsToolStripMenuItem, this->spectrumOptionsToolStripMenuItem, this->fOMOptionsToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1160, 24);
			this->menuStrip1->TabIndex = 16;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openToolStripMenuItem, 
				this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->openToolStripMenuItem->Text = L"Restart";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// diagnosticWindowToolStripMenuItem
			// 
			this->diagnosticWindowToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			this->diagnosticWindowToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->captureWaveformsToolStripMenuItem});
			this->diagnosticWindowToolStripMenuItem->Name = L"diagnosticWindowToolStripMenuItem";
			this->diagnosticWindowToolStripMenuItem->Size = System::Drawing::Size(122, 20);
			this->diagnosticWindowToolStripMenuItem->Text = L"D&iagnostic Window";
			// 
			// captureWaveformsToolStripMenuItem
			// 
			this->captureWaveformsToolStripMenuItem->Name = L"captureWaveformsToolStripMenuItem";
			this->captureWaveformsToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->captureWaveformsToolStripMenuItem->Text = L"Capture Waveforms";
			this->captureWaveformsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::captureWaveformsToolStripMenuItem_Click);
			// 
			// pSDOptionsToolStripMenuItem
			// 
			this->pSDOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->changeAxesToolStripMenuItem2, 
				this->clearChartToolStripMenuItem2});
			this->pSDOptionsToolStripMenuItem->Name = L"pSDOptionsToolStripMenuItem";
			this->pSDOptionsToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->pSDOptionsToolStripMenuItem->Text = L"PSD Options";
			// 
			// changeAxesToolStripMenuItem2
			// 
			this->changeAxesToolStripMenuItem2->Name = L"changeAxesToolStripMenuItem2";
			this->changeAxesToolStripMenuItem2->Size = System::Drawing::Size(142, 22);
			this->changeAxesToolStripMenuItem2->Text = L"Change Axes";
			this->changeAxesToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::changeAxesToolStripMenuItem2_Click);
			// 
			// clearChartToolStripMenuItem2
			// 
			this->clearChartToolStripMenuItem2->Name = L"clearChartToolStripMenuItem2";
			this->clearChartToolStripMenuItem2->Size = System::Drawing::Size(142, 22);
			this->clearChartToolStripMenuItem2->Text = L"Clear Chart";
			this->clearChartToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::clearChartToolStripMenuItem2_Click);
			// 
			// spectrumOptionsToolStripMenuItem
			// 
			this->spectrumOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->changeAxesToolStripMenuItem1, 
				this->clearChartToolStripMenuItem1, this->changeBinWidthToolStripMenuItem, this->addCutsOnPSDToolStripMenuItem});
			this->spectrumOptionsToolStripMenuItem->Name = L"spectrumOptionsToolStripMenuItem";
			this->spectrumOptionsToolStripMenuItem->Size = System::Drawing::Size(115, 20);
			this->spectrumOptionsToolStripMenuItem->Text = L"Spectrum Options";
			// 
			// changeAxesToolStripMenuItem1
			// 
			this->changeAxesToolStripMenuItem1->Name = L"changeAxesToolStripMenuItem1";
			this->changeAxesToolStripMenuItem1->Size = System::Drawing::Size(173, 22);
			this->changeAxesToolStripMenuItem1->Text = L"Change Axes";
			this->changeAxesToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::changeAxesToolStripMenuItem1_Click);
			// 
			// clearChartToolStripMenuItem1
			// 
			this->clearChartToolStripMenuItem1->Name = L"clearChartToolStripMenuItem1";
			this->clearChartToolStripMenuItem1->Size = System::Drawing::Size(173, 22);
			this->clearChartToolStripMenuItem1->Text = L"Clear Chart";
			this->clearChartToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::clearChartToolStripMenuItem1_Click);
			// 
			// changeBinWidthToolStripMenuItem
			// 
			this->changeBinWidthToolStripMenuItem->Name = L"changeBinWidthToolStripMenuItem";
			this->changeBinWidthToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->changeBinWidthToolStripMenuItem->Text = L"Change Bin Width";
			// 
			// addCutsOnPSDToolStripMenuItem
			// 
			this->addCutsOnPSDToolStripMenuItem->Name = L"addCutsOnPSDToolStripMenuItem";
			this->addCutsOnPSDToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->addCutsOnPSDToolStripMenuItem->Text = L"Add Cuts on PSD...";
			this->addCutsOnPSDToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::addCutsOnPSDToolStripMenuItem_Click);
			// 
			// fOMOptionsToolStripMenuItem
			// 
			this->fOMOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->changeAxesToolStripMenuItem, 
				this->clearChartToolStripMenuItem, this->addCutsOnEnergyToolStripMenuItem});
			this->fOMOptionsToolStripMenuItem->Name = L"fOMOptionsToolStripMenuItem";
			this->fOMOptionsToolStripMenuItem->Size = System::Drawing::Size(90, 20);
			this->fOMOptionsToolStripMenuItem->Text = L"FOM Options";
			// 
			// changeAxesToolStripMenuItem
			// 
			this->changeAxesToolStripMenuItem->Name = L"changeAxesToolStripMenuItem";
			this->changeAxesToolStripMenuItem->Size = System::Drawing::Size(188, 22);
			this->changeAxesToolStripMenuItem->Text = L"Change Axes";
			this->changeAxesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changeAxesToolStripMenuItem_Click);
			// 
			// clearChartToolStripMenuItem
			// 
			this->clearChartToolStripMenuItem->Name = L"clearChartToolStripMenuItem";
			this->clearChartToolStripMenuItem->Size = System::Drawing::Size(188, 22);
			this->clearChartToolStripMenuItem->Text = L"Clear Chart";
			this->clearChartToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::clearChartToolStripMenuItem_Click);
			// 
			// addCutsOnEnergyToolStripMenuItem
			// 
			this->addCutsOnEnergyToolStripMenuItem->Name = L"addCutsOnEnergyToolStripMenuItem";
			this->addCutsOnEnergyToolStripMenuItem->Size = System::Drawing::Size(188, 22);
			this->addCutsOnEnergyToolStripMenuItem->Text = L"Add Cuts on Energy...";
			this->addCutsOnEnergyToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::addCutsOnEnergyToolStripMenuItem_Click);
			// 
			// ch_FOM
			// 
			this->ch_FOM->BorderlineColor = System::Drawing::Color::Black;
			this->ch_FOM->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea3->AxisX->IsStartedFromZero = false;
			chartArea3->AxisX->Maximum = 2;
			chartArea3->AxisX->Minimum = 0;
			chartArea3->AxisX->Title = L"PSD Ratio";
			chartArea3->AxisY->IsStartedFromZero = false;
			chartArea3->AxisY->Maximum = 500;
			chartArea3->AxisY->Minimum = 0;
			chartArea3->AxisY->Title = L"Counts";
			chartArea3->Name = L"ChartArea1";
			this->ch_FOM->ChartAreas->Add(chartArea3);
			this->ch_FOM->Location = System::Drawing::Point(727, 27);
			this->ch_FOM->Name = L"ch_FOM";
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Bar;
			series7->Name = L"Series1";
			this->ch_FOM->Series->Add(series7);
			this->ch_FOM->Size = System::Drawing::Size(421, 336);
			this->ch_FOM->TabIndex = 17;
			this->ch_FOM->Text = L"chart3";
			// 
			// chk_stf
			// 
			this->chk_stf->AutoSize = true;
			this->chk_stf->Location = System::Drawing::Point(1054, 617);
			this->chk_stf->Name = L"chk_stf";
			this->chk_stf->Size = System::Drawing::Size(107, 17);
			this->chk_stf->TabIndex = 18;
			this->chk_stf->Text = L"Save to New File";
			this->chk_stf->UseVisualStyleBackColor = true;
			// 
			// chk_atf
			// 
			this->chk_atf->AutoSize = true;
			this->chk_atf->Location = System::Drawing::Point(1054, 642);
			this->chk_atf->Name = L"chk_atf";
			this->chk_atf->Size = System::Drawing::Size(94, 17);
			this->chk_atf->TabIndex = 19;
			this->chk_atf->Text = L"Append to File";
			this->chk_atf->UseVisualStyleBackColor = true;
			// 
			// tb_baseline
			// 
			this->tb_baseline->Location = System::Drawing::Point(784, 369);
			this->tb_baseline->Name = L"tb_baseline";
			this->tb_baseline->Size = System::Drawing::Size(100, 20);
			this->tb_baseline->TabIndex = 20;
			// 
			// tb_short
			// 
			this->tb_short->Location = System::Drawing::Point(784, 396);
			this->tb_short->Name = L"tb_short";
			this->tb_short->Size = System::Drawing::Size(100, 20);
			this->tb_short->TabIndex = 21;
			// 
			// tb_long
			// 
			this->tb_long->Location = System::Drawing::Point(784, 423);
			this->tb_long->Name = L"tb_long";
			this->tb_long->Size = System::Drawing::Size(100, 20);
			this->tb_long->TabIndex = 22;
			// 
			// tb_full
			// 
			this->tb_full->Location = System::Drawing::Point(784, 450);
			this->tb_full->Name = L"tb_full";
			this->tb_full->Size = System::Drawing::Size(100, 20);
			this->tb_full->TabIndex = 23;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(728, 372);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 13);
			this->label1->TabIndex = 24;
			this->label1->Text = L"Baseline:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(728, 399);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 25;
			this->label3->Text = L"Short Int:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(728, 426);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 13);
			this->label4->TabIndex = 26;
			this->label4->Text = L"Long Int:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(728, 453);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(41, 13);
			this->label5->TabIndex = 27;
			this->label5->Text = L"Full Int:";
			// 
			// b_SetIntegrationTimes
			// 
			this->b_SetIntegrationTimes->Location = System::Drawing::Point(759, 476);
			this->b_SetIntegrationTimes->Name = L"b_SetIntegrationTimes";
			this->b_SetIntegrationTimes->Size = System::Drawing::Size(125, 42);
			this->b_SetIntegrationTimes->TabIndex = 28;
			this->b_SetIntegrationTimes->Text = L"Set Integration Times";
			this->b_SetIntegrationTimes->UseVisualStyleBackColor = true;
			this->b_SetIntegrationTimes->Click += gcnew System::EventHandler(this, &Form1::b_SetIntegrationTimes_Click);
			// 
			// b_setTriggerThreshold
			// 
			this->b_setTriggerThreshold->Location = System::Drawing::Point(759, 570);
			this->b_setTriggerThreshold->Name = L"b_setTriggerThreshold";
			this->b_setTriggerThreshold->Size = System::Drawing::Size(125, 42);
			this->b_setTriggerThreshold->TabIndex = 29;
			this->b_setTriggerThreshold->Text = L"Set Trigger Threshold";
			this->b_setTriggerThreshold->UseVisualStyleBackColor = true;
			this->b_setTriggerThreshold->Click += gcnew System::EventHandler(this, &Form1::b_setTriggerThreshold_Click);
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(724, 534);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(54, 33);
			this->label6->TabIndex = 30;
			this->label6->Text = L"Trigger Threshold:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tb_threshold
			// 
			this->tb_threshold->Location = System::Drawing::Point(784, 541);
			this->tb_threshold->Name = L"tb_threshold";
			this->tb_threshold->Size = System::Drawing::Size(100, 20);
			this->tb_threshold->TabIndex = 31;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(910, 376);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(50, 13);
			this->label7->TabIndex = 32;
			this->label7->Text = L"Updates:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ClientSize = System::Drawing::Size(1160, 698);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tb_threshold);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->b_setTriggerThreshold);
			this->Controls->Add(this->b_SetIntegrationTimes);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tb_full);
			this->Controls->Add(this->tb_long);
			this->Controls->Add(this->tb_short);
			this->Controls->Add(this->tb_baseline);
			this->Controls->Add(this->chk_atf);
			this->Controls->Add(this->chk_stf);
			this->Controls->Add(this->ch_FOM);
			this->Controls->Add(this->ch_ESpectrum);
			this->Controls->Add(this->ch_PSD);
			this->Controls->Add(this->b_saveFile);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tb_savefilename);
			this->Controls->Add(this->tb_updates);
			this->Controls->Add(this->b_CapturePSD);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"SINGR Project uZed Board Interface";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_PSD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_ESpectrum))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_FOM))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: // Declare class-wide variables here
	static double m_energyLowerCut = 0;
	static double m_energyUpperCut = 0;
	static double m_fomLeftCut = 0;
	static double m_fomRightCut = 0;

private: System::Void b_CapturePSD_Click(System::Object^  sender, System::EventArgs^  e) {
			// This section controls what happens when a user clicks b_CapturePSD "Run Selection"
			// Sam's code for connecting to the board using ethernet will go here
			// as will code for connecting to the comm port.				 	
				std::string msg;
				std::string msgstop;
				continueLooping = true;
				Client client("172.30.0.10");

				if ( !client.Start()) {				
					this->tb_updates->Text = "Client start failed";				
					return;
				} 
				 
				int iBaselineSamples(0);
				int iblvalue(0);
				int iShortSamples(0);
				int ishortvalue(0);
				int iLongSamples(0);
				int ilongvalue(0);
				int iFullSamples(0);
				int ifullvalue(0);
				double dPSDxmin(0.0);
				double dPSDxmax(0.0);
				double dPSDymin(0.0);
				double dPSDymax(0.0);
				double dESpectrumDomain(0.0);
				double dESpectrumBinSize(0.0);
				double dESpectrumBin(0.0);
				double dFOMRange(0.0);
				double dFOMBinSize(0.0);
				double dFOMBin(0.0);
				
				int check(0);
				int placeInArray(0);
				int runCounter(0);
				bool doPSD(true);
				int iESpectrumArray[1000] = {};
				//int * iESpectrumArray = new int[1000] = {};
				int iESpectrumArrayIndex(0);
				int iFOMArray[100] = {};
				//int * iFOMArray = new int[100] = {};
				int iFOMArrayIndex(0);

				/* Determine the number of samples, based on what is in textboxes */
				if(this->tb_baseline->Text == String::Empty)
				{
					iBaselineSamples = ((200 - 8) / 4) + 1;
					iShortSamples = ((200 + 232) / 4) + 1;
					iLongSamples = ((200 + 616) / 4) + 1;
					iFullSamples = ((200 + 8008) / 4) + 1;

					this->tb_baseline->Text = (iBaselineSamples * 4) - 52 + " ";
					this->tb_short->Text = (iShortSamples * 4) - 52 + " ";
					this->tb_long->Text = (iLongSamples * 4) - 52 + " ";
					this->tb_full->Text = (iFullSamples * 4) - 52 + " ";
				}
				else
				{
					Int32::TryParse(this->tb_baseline->Text, iblvalue);
					Int32::TryParse(this->tb_short->Text, ishortvalue);
					Int32::TryParse(this->tb_long->Text, ilongvalue);
					Int32::TryParse(this->tb_full->Text, ifullvalue);
					
					iBaselineSamples = ((200 + iblvalue) / 4) + 1;
					iShortSamples = ((200 + ishortvalue) / 4) + 1;
					iLongSamples = ((200 + ilongvalue) / 4) + 1;
					iFullSamples = ((200 + ifullvalue) / 4) + 1;
				}

				/* Determine the domain and set axes for the Energy Spectrum chart */
				dPSDxmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
				dPSDxmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
				this->ch_ESpectrum->ChartAreas[0]->AxisX->Minimum = dPSDxmin;
				this->ch_ESpectrum->ChartAreas[0]->AxisX->Maximum = dPSDxmax;
				dESpectrumDomain = dPSDxmax - dPSDxmin;
				dESpectrumBinSize = dESpectrumDomain / 1000.0;	// 1,000 bins

				/* Determine the domain and set axes for the Energy Spectrum chart */
				dPSDymin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
				dPSDymax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
				this->ch_FOM->ChartAreas[0]->AxisY->Minimum = dPSDymin;
				this->ch_FOM->ChartAreas[0]->AxisY->Maximum = dPSDymax;
				dFOMRange = dPSDymax - dPSDymin;
				dFOMBinSize = dFOMRange / 100.0;	// 100 bins
				 
				int * msgInt(nullptr);		//declare a pointer and initialize it to null
				msgInt = new int[12300];	//dynamically allocate the array of integers
				//memset(&msgInt, 0, sizeof(msgInt));	//initialize all the values

				while(placeInArray < 12291)	// Fill the buffer before proceeding
				{
					msg = "a";	
					client.Send(msg.c_str());	// Send a message to the server
					this->tb_updates->Text = "Filling the array = " + placeInArray;
					Sleep(2000);

					placeInArray = client.Recv(msgInt, placeInArray);			// Fills msgInt, then sorts into array of ints, returns how full array is
				}

				if ( placeInArray == 12291 )	// Buffer is full, process and save it
				{									
					this->tb_updates->Text = "Sorting and saving the array. ";
					check = client.SortPrint(msgInt);	// Sort and save array to file
					if ( check != 0 )
					{
						if ( check = 2 ){
							this->tb_updates->Text = "j or k ran away";
							client.Stop();
							Application::DoEvents();
							return;
						}
						this->tb_updates->Text = "Could not open file.";
						client.Stop();
						return;				
					}					
					placeInArray = 0;					 				

					/* compute the value of PSD for the data set and put it into chart 1 */
					int arrayval(0);
					int ii(0);
					double bl1(0.0);
					double bl2(0.0);
					double bl3(0.0);
					double bl4(0.0);
					double bl_avg(0.0);
					double si(0.0);
					double fi(0.0);
					double li(0.0);
					double psd(0.0);
					double energy(0.0);

					/* This while loops calculates the PSD and energy values, then plots them on ch_PSD */
					while(doPSD == true)
					{						
						if(ii >= 12291){doPSD = false; continue;}
						arrayval = msgInt[ii];							
						switch (arrayval)
						{
						case 111111:	// grab the si, li, fi data to calculate psd and energy							
							bl4 = bl3;
							bl3 = bl2;
							bl2 = bl1;
							bl1 = static_cast<double>(msgInt[ii+4]) / (16 * iBaselineSamples);	//  running baseline calculation
							if(bl4 == 0)
								bl_avg = (msgInt[ii+4] / ( 16 * iBaselineSamples )); //until we have 4 baselines saved, use the regular calculation
							else							
								bl_avg = (bl1+bl2+bl3+bl4) / 4.0;

							si = static_cast<double>(msgInt[ii+5]) / 16.0 - (bl_avg * iShortSamples);
							li = static_cast<double>(msgInt[ii+6]) / 16.0 - (bl_avg * iLongSamples);
							fi = static_cast<double>(msgInt[ii+7]) / 16.0 - (bl_avg * iFullSamples);
							psd = si / (li - si);
							energy = 1.0 * li + 0.0;
							
							/* Add data to the PSD chart */
							if ((psd < 2 && psd > 0) && (energy < 200000 && energy > 0))
							{
								this->ch_PSD->Series["Series1"]->Points->AddXY(fi, psd);
							}
							/* Add data to the Energy Spectrum chart */
							iESpectrumArrayIndex = static_cast<int>(energy / dESpectrumBinSize);
							if(iESpectrumArrayIndex > 999 || iESpectrumArrayIndex < 0)
							{
								//do nothing with the event, it's outside the bins we have
							}
							else
							{
								++iESpectrumArray[iESpectrumArrayIndex];
							}
							/* Add data to the PSD chart */
							iFOMArrayIndex = static_cast<int>(psd / dFOMBinSize);
							if(iFOMArrayIndex > 99 || iFOMArrayIndex < 0)
							{
								//again, do nothing
							}
							else
							{
								++iFOMArray[iFOMArrayIndex];
							}

							this->ch_ESpectrum->Series["Series1"]->Points->Clear();
							for(int i = 0; i < 999; i++)
							{
								dESpectrumBin = dESpectrumBinSize * (i + 0.5);	// shift the marker so it sits over the bin correctly
								this->ch_ESpectrum->Series["Series1"]->Points->AddXY(dESpectrumBin, iESpectrumArray[i]);
							}
							this->ch_FOM->Series["Series1"]->Points->Clear();
							for(int j = 0; j < 999; j++)
							{
								dFOMBin = dFOMBinSize * (j + 0.5);	// shift the marker so it sits over the bin correctly
								this->ch_FOM->Series["Series1"]->Points->AddXY(dFOMBin, iFOMArray[j]);
							}

							ii += 8;					// align the with the next identifier
							//Application::DoEvents();
							break;
						case 121212: case 131313:	// gone too far, stop reading 							
							doPSD = false;
							break;
						default:	// keep iterating to find an identifier							
							++ii;
							break;				
						}
				
					}	// End of while(doPSD)			
				}	// End of if(placeinarray)

				/* Check if the user has clicked the 'stop' button */			
				if ( continueLooping == false )
				{
					this->tb_updates->Text = "Stopped. ";
					client.Stop();
					delete [] msgInt;
					msgInt = nullptr;
					return;
				}
				++runCounter;
				Application::DoEvents();
				 
				/* The user hit stop or pressed exit in file menu, clean up what we were doing */
				client.Stop();
				this->tb_updates->Text = "Complete.";
				delete [] msgInt;
				msgInt = nullptr;
				return;
}	// End of Run button click

private: System::Void b_saveFile_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::DialogResult result = folderBrowserDialog1->ShowDialog();
			 
			 if (result == System::Windows::Forms::DialogResult::OK)
			 {
					this->tb_savefilename->Text = folderBrowserDialog1->SelectedPath;
			 }
			 if (result == System::Windows::Forms::DialogResult::Cancel)
			 {
				 return;
			 }
		 }	// End of choose folder button click

private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 // Close open files
			 Application::Exit();
		 }	//End of file->exit click

private: System::Void captureWaveformsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 captureWaveform ^ captureWF = gcnew captureWaveform();
			 captureWF->Show();
			 
		 }

private: System::Void b_setTriggerThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Declare variables */
			 std::string retMessage = "";
			 std::string chooseMode = "3";
			 const char * strThreshold = "";

			 marshal_context^ context = gcnew marshal_context();
			 String^ threshold = this->tb_threshold->Text;
			 strThreshold = context->marshal_as<const char*>( threshold );

			 /* Open a client class connection to be able to send data over ethernet */
			 Client setThreshold("172.30.0.10");
			 if ( !setThreshold.Start() ) {
				 delete context;
				 this->tb_updates->Text = "Client start failed.";
				 Application::DoEvents();
				 return;
			 }
			 /* Send commands over the ethernet connection to the uZ 
			  * In this case, that means change the trigger threshold
			  * by sending a '3' then the new threshold */
			 setThreshold.Send((char*)chooseMode.c_str());
			 Sleep(1000);
			 setThreshold.Send(strThreshold);
			 Sleep(1500);

			 /* Close the client class ethernet connection */
			 delete context;
			 setThreshold.Stop();
			 this->tb_updates->Text = "Threshold changed.";
			 Application::DoEvents();		
			 return;
		 }//eosettriggerthreshold

private: System::Void b_SetIntegrationTimes_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Declare variables */
			 std::string chooseMode = "4";
			 const char * strBaseline = "";
			 const char * strShort = "";
			 const char * strLong = "";
			 const char * strFull = "";
			 String^ baselineInt = this->tb_baseline->Text;
			 String^ shortInt = this->tb_short->Text;
			 String^ longInt = this->tb_long->Text;
 			 String^ fullInt = this->tb_full->Text;

			 marshal_context^ context = gcnew marshal_context();
			 strBaseline = context->marshal_as<const char*>( baselineInt );
			 strShort = context->marshal_as<const char*>( shortInt );
			 strLong = context->marshal_as<const char*>( longInt );
			 strFull = context->marshal_as<const char*>( fullInt );

			 /* Open a client class connection to be able to send data over ethernet */
			 Client setInts("172.30.0.10");
			 if ( !setInts.Start() ) {
				 delete context;
				 this->tb_updates->Text = "Client start failed.";
				 Application::DoEvents();
				 return;
			 }
			 
			 /* Send the mode selection, then the integration times over ethernet */
			 setInts.Send((char*)chooseMode.c_str());	//Calls setIntegrationTimes(0) in the devkit
			 Sleep(1000);
			 setInts.Send(strBaseline);
			 Sleep(500);
			 setInts.Send(strShort);
			 Sleep(500);
			 setInts.Send(strLong);
			 Sleep(500);
			 setInts.Send(strFull);

			 /* Cleanup */
			 delete context;
			 setInts.Stop();
			 this->tb_updates->Text = "Integration times set.";
			 Application::DoEvents();
			 return;
		 }//eosetintegrationtimes

private: System::Void clearChartToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->ch_PSD->Series["Series1"]->Points->Clear();
			 this->tb_updates->Text = "PSD chart cleared.";
			 Application::DoEvents();
		 }

private: System::Void clearChartToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->ch_ESpectrum->Series["Series1"]->Points->Clear();
			 this->tb_updates->Text = "Energy spectrum chart cleared.";
			 Application::DoEvents();
		 }

private: System::Void clearChartToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->ch_FOM->Series["Series1"]->Points->Clear();
			 this->tb_updates->Text = "FOM chart cleared.";
			 Application::DoEvents();
		 }

private: System::Void changeAxesToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Open small pop-up window which takes in values for axes and passes them back to adjust axis size */
			 double xMin;
			 double xMax;
			 double yMin;
			 double yMax;

			 xMin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
			 xMax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
			 yMin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
			 yMax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
		 
			 /* Show the pop-up window */
			 changeAxesPopUp ^ changePSDAxes = gcnew changeAxesPopUp( xMin, xMax, yMin, yMax);
			 changePSDAxes->ShowDialog();

			 this->ch_PSD->ChartAreas[0]->AxisX->Minimum = changePSDAxes->getxMin();
			 this->ch_PSD->ChartAreas[0]->AxisX->Maximum = changePSDAxes->getxMax();
			 this->ch_PSD->ChartAreas[0]->AxisY->Minimum = changePSDAxes->getyMin();
			 this->ch_PSD->ChartAreas[0]->AxisY->Maximum = changePSDAxes->getyMax();
		 }//end of changePSDAxes

private: System::Void changeAxesToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			/* Pop-up window to change Energy Spectrum Chart */
			 double xMin;
			 double xMax;
			 double yMin;
			 double yMax;

			 xMin = this->ch_ESpectrum->ChartAreas[0]->AxisX->Minimum;
			 xMax = this->ch_ESpectrum->ChartAreas[0]->AxisX->Maximum;
			 yMin = this->ch_ESpectrum->ChartAreas[0]->AxisY->Minimum;
			 yMax = this->ch_ESpectrum->ChartAreas[0]->AxisY->Maximum;
		 
			 /* Show the pop-up window */
			 changeAxesPopUp ^ changeSpectrumAxes = gcnew changeAxesPopUp( xMin, xMax, yMin, yMax);
			 changeSpectrumAxes->ShowDialog();

			 this->ch_ESpectrum->ChartAreas[0]->AxisX->Minimum = changeSpectrumAxes->getxMin();
			 this->ch_ESpectrum->ChartAreas[0]->AxisX->Maximum = changeSpectrumAxes->getxMax();
			 this->ch_ESpectrum->ChartAreas[0]->AxisY->Minimum = changeSpectrumAxes->getyMin();
			 this->ch_ESpectrum->ChartAreas[0]->AxisY->Maximum = changeSpectrumAxes->getyMax();
		 }//end of changeSpectrumAxes

private: System::Void changeAxesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Pop-up window to change Figure of Merit Chart */
			 double xMin;
			 double xMax;
			 double yMin;
			 double yMax;

			 xMin = this->ch_FOM->ChartAreas[0]->AxisX->Minimum;
			 xMax = this->ch_FOM->ChartAreas[0]->AxisX->Maximum;
			 yMin = this->ch_FOM->ChartAreas[0]->AxisY->Minimum;
			 yMax = this->ch_FOM->ChartAreas[0]->AxisY->Maximum;
		 
			 /* Show the pop-up window */
			 changeAxesPopUp ^ changeFOMAxes = gcnew changeAxesPopUp( xMin, xMax, yMin, yMax);
			 changeFOMAxes->ShowDialog();

			 this->ch_FOM->ChartAreas[0]->AxisX->Minimum = changeFOMAxes->getxMin();
			 this->ch_FOM->ChartAreas[0]->AxisX->Maximum = changeFOMAxes->getxMax();
			 this->ch_FOM->ChartAreas[0]->AxisY->Minimum = changeFOMAxes->getyMin();
			 this->ch_FOM->ChartAreas[0]->AxisY->Maximum = changeFOMAxes->getyMax();
		 }//end of changeFOMAxes


private: System::Void addCutsOnEnergyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Plots vertical lines on the PSD chart */
			 double psdXmin(0);
			 double psdXmax(0);
			 double psdYmin(0);
			 double psdYmax(0);

			 psdXmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
			 psdXmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
			 psdYmin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
			 psdYmax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
		
			 /* Show a pop-up that lets user specify where the cuts will be */
			 setCutsPopUp ^ setEnergyCuts = gcnew setCutsPopUp(psdXmin, psdXmax);	//Energy refers to the axis variable, not ch_ESpectrum
			 setEnergyCuts->ShowDialog();

			 /* Retrieve the cuts the user entered */
			 m_fomLeftCut = setEnergyCuts->getCutLower();
			 m_fomRightCut = setEnergyCuts->getCutUpper();

			 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->Clear();
			 this->ch_PSD->Series["series_EnergyCutRight"]->Points->Clear();

			 if(m_fomLeftCut == 0 && m_fomRightCut == 0)	// No cuts
			 {
				 m_fomLeftCut = 0.0;
				 m_fomRightCut = 0.0;
				 this->tb_updates->Text = "Nocuts chose.";
				 return;
			 }

			 if(m_fomLeftCut > 0 && m_fomRightCut > 0)	// Both cuts
			 {
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmax);
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_fomRightCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_fomRightCut, psdYmax);
			 }

			 if(m_fomLeftCut == 0 && m_fomRightCut > 0)	// Only Upper cut
			 {
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_fomRightCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_fomRightCut, psdYmax);
			 }

			 if(m_fomLeftCut > 0 && m_fomRightCut == 0)	// Only lower cut
			 {
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmax);
			 }

		 }//end of cuts on Energy (vertical)


private: System::Void addCutsOnPSDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Plots horizontal lines on the PSD chart */
			 double psdXmin(0);
			 double psdXmax(0);
			 double psdYmin(0);
			 double psdYmax(0);

			 psdXmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
			 psdXmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
			 psdYmin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
			 psdYmax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
		
			 /* Show a pop-up that lets user specify where the cuts will be */
			 setCutsPopUp ^ setpsdRatioCuts = gcnew setCutsPopUp(psdYmin, psdYmax);	//Energy refers to the axis variable, not ch_ESpectrum
			 setpsdRatioCuts->ShowDialog();

			 /* Retrieve the cuts the user entered */
			 m_energyLowerCut = setpsdRatioCuts->getCutLower();
			 m_energyUpperCut = setpsdRatioCuts->getCutUpper();

			 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->Clear();
			 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->Clear();

			 if(m_energyLowerCut == 0 && m_energyUpperCut == 0)	// No cuts
			 {
				 m_energyLowerCut = 0.0;
				 m_energyUpperCut = 0.0;
				 this->tb_updates->Text = "Nocuts chose.";
				 return;
			 }

			 if(m_energyLowerCut > 0 && m_energyUpperCut > 0)	// Both cuts
			 {
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmin, m_energyLowerCut);
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmax, m_energyLowerCut);
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmin, m_energyUpperCut);
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmax, m_energyUpperCut);
			 }

			 if(m_energyLowerCut == 0 && m_energyUpperCut > 0)	// Only Upper cut
			 {
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmin, m_energyUpperCut);
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmax, m_energyUpperCut);
			 }

			 if(m_energyLowerCut > 0 && m_energyUpperCut == 0)	// Only lower cut
			 {
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmin, m_energyLowerCut);
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmax, m_energyLowerCut);
			 }
		 }//end of set cuts on psd ratio (horizontal lines) 

};	// leave semi-colon, closes public ref class Form1, line 25
}	// eof, closes namespace singr_gui, line 10

