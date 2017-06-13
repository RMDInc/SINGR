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
			psdCapRun = false;
			backgroundWorker2->RunWorkerAsync();
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
	private: System::Windows::Forms::ToolStripMenuItem^  neutronDieAwayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
	private: System::Windows::Forms::TextBox^  tb_counterBox;

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
	private: bool psdCapRun;
	private: ref struct dataForBkgdWorker{
				 String^ mstrFileName;
			 };
	private: array<Int32>^ g_iESpectrumArray;
	private: array<Int32>^ g_iFOMArray;
	private: double dSpectrumBinSize;
	private: double dFOMBinSize;
	private: int iNumberSpectrumBins;
	private: int iFOMBins;
	protected: 

		

	protected: 







	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::TextBox^  tb_updates;



	private: System::Windows::Forms::TextBox^  tb_savefilename;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  b_saveFile;



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
			this->neutronDieAwayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ch_FOM = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
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
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tb_counterBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_PSD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_ESpectrum))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ch_FOM))->BeginInit();
			this->SuspendLayout();
			// 
			// b_CapturePSD
			// 
			this->b_CapturePSD->Location = System::Drawing::Point(1023, 404);
			this->b_CapturePSD->Name = L"b_CapturePSD";
			this->b_CapturePSD->Size = System::Drawing::Size(125, 42);
			this->b_CapturePSD->TabIndex = 4;
			this->b_CapturePSD->Text = L"Capture PSD";
			this->b_CapturePSD->UseVisualStyleBackColor = true;
			this->b_CapturePSD->Click += gcnew System::EventHandler(this, &Form1::b_CapturePSD_Click);
			// 
			// tb_updates
			// 
			this->tb_updates->Location = System::Drawing::Point(913, 378);
			this->tb_updates->Name = L"tb_updates";
			this->tb_updates->ReadOnly = true;
			this->tb_updates->Size = System::Drawing::Size(235, 20);
			this->tb_updates->TabIndex = 7;
			// 
			// tb_savefilename
			// 
			this->tb_savefilename->Location = System::Drawing::Point(746, 651);
			this->tb_savefilename->Name = L"tb_savefilename";
			this->tb_savefilename->ReadOnly = true;
			this->tb_savefilename->Size = System::Drawing::Size(402, 20);
			this->tb_savefilename->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(743, 632);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Save File Location:";
			// 
			// b_saveFile
			// 
			this->b_saveFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_saveFile->Location = System::Drawing::Point(1023, 603);
			this->b_saveFile->Name = L"b_saveFile";
			this->b_saveFile->Size = System::Drawing::Size(124, 42);
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
			this->ch_PSD->Size = System::Drawing::Size(709, 319);
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
			this->ch_ESpectrum->Location = System::Drawing::Point(12, 355);
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
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->fileToolStripMenuItem, 
				this->diagnosticWindowToolStripMenuItem, this->pSDOptionsToolStripMenuItem, this->spectrumOptionsToolStripMenuItem, this->fOMOptionsToolStripMenuItem, 
				this->neutronDieAwayToolStripMenuItem});
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
			// neutronDieAwayToolStripMenuItem
			// 
			this->neutronDieAwayToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->openToolStripMenuItem1});
			this->neutronDieAwayToolStripMenuItem->Name = L"neutronDieAwayToolStripMenuItem";
			this->neutronDieAwayToolStripMenuItem->Size = System::Drawing::Size(117, 20);
			this->neutronDieAwayToolStripMenuItem->Text = L"Neutron Die-Away";
			// 
			// openToolStripMenuItem1
			// 
			this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
			this->openToolStripMenuItem1->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem1->Text = L"Open";
			this->openToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem1_Click);
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
			this->ch_FOM->Size = System::Drawing::Size(421, 319);
			this->ch_FOM->TabIndex = 17;
			this->ch_FOM->Text = L"chart3";
			// 
			// tb_baseline
			// 
			this->tb_baseline->Location = System::Drawing::Point(784, 355);
			this->tb_baseline->Name = L"tb_baseline";
			this->tb_baseline->Size = System::Drawing::Size(100, 20);
			this->tb_baseline->TabIndex = 20;
			// 
			// tb_short
			// 
			this->tb_short->Location = System::Drawing::Point(784, 382);
			this->tb_short->Name = L"tb_short";
			this->tb_short->Size = System::Drawing::Size(100, 20);
			this->tb_short->TabIndex = 21;
			// 
			// tb_long
			// 
			this->tb_long->Location = System::Drawing::Point(784, 409);
			this->tb_long->Name = L"tb_long";
			this->tb_long->Size = System::Drawing::Size(100, 20);
			this->tb_long->TabIndex = 22;
			// 
			// tb_full
			// 
			this->tb_full->Location = System::Drawing::Point(784, 436);
			this->tb_full->Name = L"tb_full";
			this->tb_full->Size = System::Drawing::Size(100, 20);
			this->tb_full->TabIndex = 23;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(728, 358);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 13);
			this->label1->TabIndex = 24;
			this->label1->Text = L"Baseline:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(728, 385);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 25;
			this->label3->Text = L"Short Int:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(728, 412);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 13);
			this->label4->TabIndex = 26;
			this->label4->Text = L"Long Int:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(728, 439);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(41, 13);
			this->label5->TabIndex = 27;
			this->label5->Text = L"Full Int:";
			// 
			// b_SetIntegrationTimes
			// 
			this->b_SetIntegrationTimes->Location = System::Drawing::Point(759, 462);
			this->b_SetIntegrationTimes->Name = L"b_SetIntegrationTimes";
			this->b_SetIntegrationTimes->Size = System::Drawing::Size(125, 42);
			this->b_SetIntegrationTimes->TabIndex = 28;
			this->b_SetIntegrationTimes->Text = L"Set Integration Times";
			this->b_SetIntegrationTimes->UseVisualStyleBackColor = true;
			this->b_SetIntegrationTimes->Click += gcnew System::EventHandler(this, &Form1::b_SetIntegrationTimes_Click);
			// 
			// b_setTriggerThreshold
			// 
			this->b_setTriggerThreshold->Location = System::Drawing::Point(759, 556);
			this->b_setTriggerThreshold->Name = L"b_setTriggerThreshold";
			this->b_setTriggerThreshold->Size = System::Drawing::Size(125, 42);
			this->b_setTriggerThreshold->TabIndex = 29;
			this->b_setTriggerThreshold->Text = L"Set Trigger Threshold";
			this->b_setTriggerThreshold->UseVisualStyleBackColor = true;
			this->b_setTriggerThreshold->Click += gcnew System::EventHandler(this, &Form1::b_setTriggerThreshold_Click);
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(724, 520);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(54, 33);
			this->label6->TabIndex = 30;
			this->label6->Text = L"Trigger Threshold:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tb_threshold
			// 
			this->tb_threshold->Location = System::Drawing::Point(784, 527);
			this->tb_threshold->Name = L"tb_threshold";
			this->tb_threshold->Size = System::Drawing::Size(100, 20);
			this->tb_threshold->TabIndex = 31;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(910, 362);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(50, 13);
			this->label7->TabIndex = 32;
			this->label7->Text = L"Updates:";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker1_RunWorkerCompleted);
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->WorkerReportsProgress = true;
			this->backgroundWorker2->WorkerSupportsCancellation = true;
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker2_DoWork);
			this->backgroundWorker2->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::backgroundWorker2_ProgressChanged);
			// 
			// tb_counterBox
			// 
			this->tb_counterBox->Location = System::Drawing::Point(1128, 453);
			this->tb_counterBox->Name = L"tb_counterBox";
			this->tb_counterBox->ReadOnly = true;
			this->tb_counterBox->Size = System::Drawing::Size(19, 20);
			this->tb_counterBox->TabIndex = 33;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ClientSize = System::Drawing::Size(1160, 681);
			this->Controls->Add(this->tb_counterBox);
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
	static double m_lowerCut = 0;
	static double m_upperCut = 0;
	static double m_leftCut = 0;
	static double m_rightCut = 0;

private: System::Void b_CapturePSD_Click(System::Object^  sender, System::EventArgs^  e) {
			// This section controls what happens when a user clicks b_CapturePSD "Run Selection"
			psdCapRun = !psdCapRun;	//flip the boolean value each time the button is clicked	//is init'd as false
			if(psdCapRun == false)
			{
				/* need this to send a "quit" command to the devkit...when that is an option */
				backgroundWorker1->CancelAsync();
				this->tb_updates->Text = "Cancelled worker thread.";
				return;
			}

			if(this->tb_savefilename->Text == String::Empty)	//if there is no filename in the textbox
			{
				this->tb_updates->Text = "Please select a save file location.";	//alert the user they need one
				psdCapRun = !psdCapRun;
				return;
			}
			String^ saveFileName = this->tb_savefilename->Text;	//this is a managed string
			//marshal_context^ context = gcnew marshal_context();
			//const char * strFileName = context->marshal_as<const char*>(saveFileName);	//convert the filename into something we may pack up and pass to the worker
			
			/* Create the arrays for the Energy Spectrum and FOM charts */
			g_iESpectrumArray = gcnew array<Int32>(1000){};
			g_iFOMArray = gcnew array<Int32>(1000){};

			/* Determine domain and range for the FOM, Energy Spectrum charts here */ //just declaring the variable here doesn't work for other functions
			/* Determine the domain and set axes for the spectrum graph */
			double dPSDXmin = 0.0;
			double dPSDXmax = 0.0;
			double dSpectrumDomain = 0.0;
			double dPSDYmin = 0.0;
			double dPSDYmax = 0.0;
			double dFOMRange = 0.0;
			int iNumberSpectrumBins = 1000.0;
			int iFOMBins = 100.0;
			double dSpectrumBinSize = 0.0;
			double dFOMBinSize = 0.0;

			dPSDXmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;			//get the min and max of the PSD chart
			dPSDXmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
			this->ch_ESpectrum->ChartAreas[0]->AxisX->Minimum = dPSDXmin;	//set the min and max of the spectrum chart to match
			this->ch_ESpectrum->ChartAreas[0]->AxisX->Maximum = dPSDXmax;
			dSpectrumDomain = dPSDXmax - dPSDXmin;							//determine that domain of values
			dSpectrumBinSize = dSpectrumDomain / iNumberSpectrumBins;					//set the bin size accordingly //currently 1000 bins

			/* Determine the range, set axes, and calculate the bin size for the FOM graph */
			dPSDYmin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
			dPSDYmax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
			this->ch_FOM->ChartAreas[0]->AxisX->Minimum = dPSDYmin;
			this->ch_FOM->ChartAreas[0]->AxisX->Maximum = dPSDYmax;
			dFOMRange = dPSDYmax - dPSDYmin;
			dFOMBinSize = dFOMRange / iFOMBins;

			/* Pack up the filename to pass to the background worker */
			dataForBkgdWorker^ s_variables = gcnew dataForBkgdWorker;
			s_variables->mstrFileName = saveFileName;
			
			/* call the background worker with argument being a package of data (just a filename, for now) that it needs */
			backgroundWorker1->RunWorkerAsync(s_variables);

			this->tb_updates->Text = "Waiting to report received data.";

			return;
}	// End of Run button click

private: System::Void b_saveFile_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::DialogResult result = saveFileDialog1->ShowDialog();
			 
			 if (result == System::Windows::Forms::DialogResult::OK)
			 {
					this->tb_savefilename->Text = saveFileDialog1->FileName;
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
			 /* Check that the user has entered a value */
			 // alert the user that they need to enter a value first

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
			 /* Check for values entered...if none, don't finish this process */
			 //if the user has not entered any values, this could mess up the input process

			 /* Declare variables */
			 std::string chooseMode = "4";
			 const char * strBaseline = "";
			 const char * strShort = "";
			 const char * strLong = "";
			 const char * strFull = "";
			 String^ baselineInt = this->tb_baseline->Text;	// read in the values in the textboxes
			 String^ shortInt = this->tb_short->Text;
			 String^ longInt = this->tb_long->Text;
 			 String^ fullInt = this->tb_full->Text;

			 marshal_context^ context = gcnew marshal_context();			// convert the values into unmanaged types so we may work with them
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
			 setInts.Send(strBaseline);					// Pass the values to the devkit
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
			 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->Clear();
			 this->ch_PSD->Series["series_EnergyCutRight"]->Points->Clear();
			 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->Clear();
			 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->Clear();
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
			 m_leftCut = setEnergyCuts->getCutLower();
			 m_rightCut = setEnergyCuts->getCutUpper();

			 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->Clear();
			 this->ch_PSD->Series["series_EnergyCutRight"]->Points->Clear();

			 if(m_leftCut == 0 && m_rightCut == 0)	// No cuts
			 {
				 m_leftCut = 0.0;
				 m_rightCut = 0.0;
				 this->tb_updates->Text = "Nocuts chose.";
				 return;
			 }

			 if(m_leftCut > 0 && m_rightCut > 0)	// Both cuts
			 {
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_leftCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_leftCut, psdYmax);
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_rightCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_rightCut, psdYmax);
			 }

			 if(m_leftCut == 0 && m_rightCut > 0)	// Only Upper cut
			 {
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_rightCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutRight"]->Points->AddXY(m_rightCut, psdYmax);
			 }

			 if(m_leftCut > 0 && m_rightCut == 0)	// Only lower cut
			 {
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_leftCut, psdYmin);
				 this->ch_PSD->Series["series_EnergyCutLeft"]->Points->AddXY(m_leftCut, psdYmax);
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
			 m_lowerCut = setpsdRatioCuts->getCutLower();
			 m_upperCut = setpsdRatioCuts->getCutUpper();

			 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->Clear();
			 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->Clear();

			 if(m_lowerCut == 0 && m_upperCut == 0)	// No cuts
			 {
				 m_lowerCut = 0.0;
				 m_upperCut = 0.0;
				 this->tb_updates->Text = "Nocuts chose.";
				 return;
			 }

			 if(m_lowerCut > 0 && m_upperCut > 0)	// Both cuts
			 {
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmin, m_lowerCut);
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmax, m_lowerCut);
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmin, m_upperCut);
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmax, m_upperCut);
			 }

			 if(m_lowerCut == 0 && m_upperCut > 0)	// Only Upper cut
			 {
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmin, m_upperCut);
				 this->ch_PSD->Series["series_psdRatioCutUpper"]->Points->AddXY(psdXmax, m_upperCut);
			 }

			 if(m_lowerCut > 0 && m_upperCut == 0)	// Only lower cut
			 {
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmin, m_lowerCut);
				 this->ch_PSD->Series["series_psdRatioCutLower"]->Points->AddXY(psdXmax, m_lowerCut);
			 }
		 }//end of set cuts on psd ratio (horizontal lines) 

private: System::Void openToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //This will open a window to the neutron die-away curve utility
		 }

private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

			String^ filename = safe_cast<dataForBkgdWorker^>(e->Argument)->mstrFileName;	//get the data from the packaged arguments
			marshal_context^ context = gcnew marshal_context();								//convert the filename to an unmanaged string type
			const char * strFileName = context->marshal_as<const char*>(filename);
			
			Client client("172.30.0.10");
			if ( !client.Start()) {				
				this->tb_updates->Text = "Client start failed";				
				return;
			} 
				 				
			/* Variables and Arrays */
			std::string msg = "a";
			std::string msgQuit = "q";
			std::string msgbBuff = "b";
			std::string strMode = "0";			//choose mode menu
			std::string enableSystem = "1";		//enable the system
			std::string strProcessedData = "4";	//choose processed data mode
			std::string strEther = "9";			//begin
			int holder(0);
			int * recvBuffer(nullptr);
			recvBuffer = new int[16384]();

			/* Setup the uZ and begin data transfer */
			client.Send((char *)strMode.c_str());
			worker->ReportProgress(-11);	//report mode change
			Sleep(2000);
			client.Send((char *)strProcessedData.c_str());
			worker->ReportProgress(-12);	//report choosing processed data mode
			Sleep(2000);
			client.Send((char *)enableSystem.c_str());
			worker->ReportProgress(-13);	//report system enabled
			Sleep(2000);
			client.Send((char *)strEther.c_str());
			worker->ReportProgress(-14);	//report begin data downlink
			Sleep(2000);

			while(worker->CancellationPending == false)//until the user hits the capture button twice this will loop
			{
				client.Send(msg.c_str());

				int iDataReceived = client.Recv((int *)recvBuffer);	// iDataReceived gives an int which is the number of ints read into recvBuffer
				if(iDataReceived == 1)	//we got no data or an error
				{
					worker->ReportProgress(-1);
					break;
				}
				if(recvBuffer[iDataReceived-2] != 141414)	//we received data, but we have more to receive before passing the array to be sorted and saved
				{
					int testnum = recvBuffer[iDataReceived];
					int testnum2 = recvBuffer[iDataReceived-1];
					int testnum3 = recvBuffer[iDataReceived-2];
					worker->ReportProgress(-15);
					client.Send(msgbBuff.c_str());			// send a "b"
					holder = client.Recv((int *)(recvBuffer + iDataReceived));	//move the pointer to the receive buffer by the amount of data we already received
					iDataReceived += holder;				// add holder back in
				}
				if(holder == 1 || holder == -1)	//we got no data or an error
				{
					worker->ReportProgress(-1);
					break;
				}

				/*need to box up the array into an object */
				array<int>^ recvBufferToPass = gcnew array<int>(iDataReceived);
				for(int ii = 0; ii < (iDataReceived - 1); ++ii)
				{
					recvBufferToPass[ii] = *(recvBuffer + ii);
				}

				worker->ReportProgress((iDataReceived - 1), recvBufferToPass);

				int iSortPrintReturn = client.SortPrint(strFileName, (int *)recvBuffer, (iDataReceived - 1));
				if(iSortPrintReturn == 414141)
					worker->ReportProgress(iSortPrintReturn);
				else
					worker->ReportProgress(-1);
			}

			client.Send((char *)msgQuit.c_str());
			Sleep(2000);
			delete[] recvBuffer; recvBuffer = nullptr;

		 }
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 		 
		 {
			 if(e->ProgressPercentage == 414141)
			 {
				 this->tb_updates->Text = "Data saved.";
				 return;
			 }
			 else if(e->ProgressPercentage == -1)
			 {
				 this->tb_updates->Text = "Error.";
				 return;
			 }
			 else if(e->ProgressPercentage == -11)
			 {
				 this->tb_updates->Text = "Changing mode...";
				 return;
			 }
			 else if(e->ProgressPercentage == -12)
			 {
				 this->tb_updates->Text = "Choosing processed data mode.";
				 return;
			 }
			 else if(e->ProgressPercentage == -13)
			 {
				 this->tb_updates->Text = "System enabled.";
				 return;
			 }
			 else if(e->ProgressPercentage == -14)
			 {
				 this->tb_updates->Text = "Beginning data downlink.";
				 return;
			 }
			 else if(e->ProgressPercentage == -15)
			 {
				 this->tb_updates->Text = "Sending 'b' to get the rest of the data.";
				 return;
			 }
			 else
				 this->tb_updates->Text = e->ProgressPercentage + " bytes received.";

			 /* Variables */
			 int ii(0);
			 double bl1(0);	double bl2(0); double bl3(0); double bl4(0); double bl_avg(0);
			 double si(0); double li(0); double fi(0);
			 double psd(0);
			 double energy(0);

			 /* unpack the values from the array so we may plot them */
			 array<int>^ recvBufferPassed = safe_cast<array<int>^>(e->UserState);

			 while(ii < ((e->ProgressPercentage) / 8))
			 {
				 switch(recvBufferPassed[ii])
				 {
				 case 111111:
					 bl4 = bl3;
					 bl3 = bl2;
					 bl2 = bl1;
					 bl1 = static_cast<double>(recvBufferPassed[ii+3]) / (16.0 * 38.0);	//change this to the real baseline textbox values
					 if(bl4 == 0.0)
						 bl_avg = bl1;
					 else
						 bl_avg = (bl4 + bl3 + bl2 + bl1) / 4.0;
					 si = static_cast<double>(recvBufferPassed[ii+4]) / 16.0 - (bl_avg * 73.0);
					 li = static_cast<double>(recvBufferPassed[ii+5]) / 16.0 - (bl_avg * 169.0);
					 fi = static_cast<double>(recvBufferPassed[ii+6]) / 16.0 - (bl_avg * 1551.0);
					 psd = si / (li - si);
					 energy = 1.0 * fi + 0.0;
					 
					 /* add this data to the psd chart */
					 if((psd > 0 && psd < 2) && (energy > 0 && energy < 200000))
						 this->ch_PSD->Series["Series1"]->Points->AddXY(fi, psd);
					 ii += 8;
					 break;
				 default:
					 ++ii;
					 break;
				 }	//end of switch

				 /* sort energy into Energy Spectrum bins */
				 //double dESpectrumBinSize = (200000 - 0) / 1000; //psdXmax - psdXmin / numbins
				 double dESpectrumBin(0.0);
				 double dFOMBin(0.0);
				 double dFOMBinSize = (0.0);
				 int iESpectrumArrayIndex(0);
				 int iFOMArrayIndex(0);

				 iESpectrumArrayIndex = static_cast<int>(energy / dSpectrumBinSize);	//check data is within the spectrum bins
				 iFOMArrayIndex = static_cast<int>(psd / dFOMBinSize);
				 if((iESpectrumArrayIndex >= 0 && iESpectrumArrayIndex < 1000) && (iFOMArrayIndex >= 0 && iFOMArrayIndex < 99))	//if the point is within the array (on the chart)
				 {
					 if(m_lowerCut > 0 || m_upperCut > 0 || m_leftCut > 0 || m_rightCut > 0)	//see if the user made cuts
					 {
						 //the user has made cuts
						 //now we require the point (energy, psd) to be inside those cuts
						 if((m_upperCut > 0) && (m_rightCut > 0))		//we have an upper and right cut
						 {
							 if((energy >= m_leftCut && energy <= m_rightCut) && (psd >= m_lowerCut && psd <= m_upperCut))
							 {
								 ++g_iESpectrumArray[iESpectrumArrayIndex];
								 ++g_iFOMArray[iFOMArrayIndex];
							 }
						 }
						 else if((m_upperCut > 0) && (m_rightCut == 0))	//we have an upper and no right cut
						 {
 							 if((energy >= m_leftCut) && (psd >= m_lowerCut && psd <= m_upperCut))		//any energy above cut left will do, psd below/within cuts
							 {
								 ++g_iESpectrumArray[iESpectrumArrayIndex];
								 ++g_iFOMArray[iFOMArrayIndex];
							 }
						 }
						 else if((m_upperCut == 0) && (m_rightCut > 0))	//we have a right cut and no upper cut
						 {
 							 if((energy >= m_leftCut && energy <= m_rightCut) && (psd >= m_lowerCut))	//any psd above lower cut will do, energy below/within cuts
							 {
								 ++g_iESpectrumArray[iESpectrumArrayIndex];
								 ++g_iFOMArray[iFOMArrayIndex];
							 }
						 }
						 else										//only lower/left cuts
						 {
							 if((energy >= m_leftCut) && (psd >= m_lowerCut))		//any psd and energy above minimums
							 {
								 ++g_iESpectrumArray[iESpectrumArrayIndex];
								 ++g_iFOMArray[iFOMArrayIndex];
							 }
						 }
					 }
					 else	//if the user did not make cuts, but the point is within the bins
					 {
						 ++g_iESpectrumArray[iESpectrumArrayIndex];
						 ++g_iFOMArray[iFOMArrayIndex];		
					 }
				 }

				 /* clear charts and plot the arrays */
				 this->ch_ESpectrum->Series["Series1"]->Points->Clear();   
				 this->ch_FOM->Series["Series1"]->Points->Clear();

				 for(int jj = 0; jj < (iNumberSpectrumBins - 1); jj++)
				 {
					 dESpectrumBin = dSpectrumBinSize * (jj + 0.5);
					 this->ch_ESpectrum->Series["Series1"]->Points->AddXY(dESpectrumBin, g_iESpectrumArray[jj]);
				 }
				 for(int ii = 0; ii < (iFOMBins - 1); ii++)
				 {
					 dFOMBin = dFOMBinSize * (ii + 0.5);
					 this->ch_FOM->Series["Series1"]->Points->AddXY(dFOMBin, g_iFOMArray[ii]);
				 }
			 }

		 }
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

			 if(e->Cancelled)
				 this->tb_updates->Text = "Worker successfully cancelled.";
			 else if(e->Error != nullptr)
				 MessageBox::Show(e->Error->Message);			 
		 }
private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 BackgroundWorker^ counterWorker = dynamic_cast<BackgroundWorker^>(sender);
			 int counter(0);

			 while(1)
			 {
				 Sleep(500);
				 counterWorker->ReportProgress(counter);
				 counter++;
				 if(counter > 9)	//if the counter goes to 10, reset it to 0
					 counter = 0;	//ie. we loop 0 - 9 -> 0 - 9
			 }

		 }
private: System::Void backgroundWorker2_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
			 this->tb_counterBox->Text = e->ProgressPercentage + " ";
		 }
};	// leave semi-colon, closes public ref class Form1, line 25
}	// eof, closes namespace singr_gui, line 10

