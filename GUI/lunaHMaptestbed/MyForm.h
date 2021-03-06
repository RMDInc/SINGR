#pragma once

//TESTING ethernet includes //this compiles 4/24 @ 17:17
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
//END TESTING ethernet includes

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>					//for marshalling
#include <msclr/marshal_cppstd.h>	//for marshalling
#include "captureWaveformsPopup.h"
#include "changeAxesPopUp.h"
#include "setEnergyCutsPopUp.h"

#include <vcclr.h>	//TEST

//This tells the linker to add the following libraries to the list of library dependencies with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//If we get rid of the following lines, the libraries must be added into the project properties at Linker->Input->Additional dependencies
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DATABUFFER_SIZE			12288
#define DATA_BUFLEN				49152
#define DEFAULT_PORT			"7"
#define INPUT_BUFFER_SIZE	512	//coming from the FPGA
#define OUTPUT_BUFFER_SIZE	36	//going to the GUI
#define EVENTS_PER_BUFFER	8
#define EVENT_SIZE			32
#define INTS_PER_EVENT		8
#define INTEG_START_TIME	200
#define NS_TO_SAMPLES		4

value struct dataProductEvent
{
	int aaTotalEvents;	// AA stands for adjacent average
	int aaEventNumber;	// should be matched across all integrators
	double aaBaselineInt;
	double aaShortInt;
	double aaLongInt;
	double aaFullInt;
	int aaEight;		// placeholder
	int lpfEventNumber;	// LPF stands for Low Pass Filter
	int lpfTTLSignal;	// PNG signal in
	double lpfBaselineInt;
	double lpfShortInt;
	double lpfFullInt;
	int lpfSeven;		// placeholder
	int lpfEight;		// placeholder
	double dffTimeSmall;	// DFF stands for Differential filter	//timesmall+timebig = time in seconds
	double dffTimeBig;		//small * 128e-9 + big * 549.7558139 = time (s)
	int dffEventNumber;
	double dffBaselineInt;
	double dffShortInt;
	int dffSeven;		// placeholder
	int dffEight;		// placeholder
};

namespace lunaHMaptestbed {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for MyForm
	/// When we start the GUI this is the constructor for the entire GUI
	/// To run functions, utilities when it is started/created, write the code below, then call them here
	/// FindPorts() is an example of this, as well as runWorkerAsync() which starts a worker thread when the
	///  GUI starts.
	/// This is also a good place to set global variables; they can/should be declared above/below here.
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			findPorts();
			psdCap_run = false;
			connected_to_server = false;
			backgroundWorker2->RunWorkerAsync();

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













	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::ComboBox^  comboBox1;












	private: System::Windows::Forms::Label^  label6;

	//"global" variables declared here
	private: bool psdCap_run;
	private: bool connected_to_server;
	private: array<unsigned int>^ g_dataBuffer;
	private: array<unsigned char>^ g_binaryDataBuffer;
	private: ref struct dataForBkgdWorker {
		String^ mstrFileName;
		String^ portName;
		String^ bufferDisplayFrequency;
	};
	private: static array<Int32>^ g_iESpectrumArray = gcnew array<Int32>(1000) {};
	private: static array<Int32>^ g_iFOMArray = gcnew array<Int32>(100) {};
	private: double dSpectrumBinSize;
	private: double dFOMBinSize;
	private: int iNumberSpectrumBins;
	private: int iFOMBins;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  restartToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  diagnosticsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  captureWaveformsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  option1ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  option2ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cOMPortToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closeCOMToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  restartCOMToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_PSD;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_Spectrum;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_FOM;
	private: System::Windows::Forms::Button^  b_SetIntegrationTimes;

	private: System::Windows::Forms::TextBox^  tb_baseline;
	private: System::Windows::Forms::TextBox^  tb_short;
	private: System::Windows::Forms::TextBox^  tb_long;
	private: System::Windows::Forms::TextBox^  tb_full;




	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  tb_trigger;
	private: System::Windows::Forms::Button^  b_SetThreshold;
	private: System::Windows::Forms::TextBox^  tb_updates;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  b_capturePSD;
	private: System::Windows::Forms::Button^  b_saveFile;
	private: System::Windows::Forms::CheckBox^  chk_stf;
	private: System::Windows::Forms::CheckBox^  chk_atf;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::TextBox^  tb_savefilename;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ToolStripMenuItem^  pSDOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeAxesPSDToolStripMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  clearChartPSDToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  spectrumOptionsToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  changeAxesSpectrumToolStripMenuItem1;
private: System::Windows::Forms::ToolStripMenuItem^  clearChartSpectrumToolStripMenuItem1;


	private: System::Windows::Forms::ToolStripMenuItem^  changeBinWidthToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fOMOptionsToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  changeAxesFOMToolStripMenuItem2;
private: System::Windows::Forms::ToolStripMenuItem^  clearChartFOMToolStripMenuItem2;
private: System::Windows::Forms::ToolStripMenuItem^  addEnergyCutsToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  addFOMCutsToolStripMenuItem;
private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
private: System::Windows::Forms::TextBox^  tb_counterbox;

private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
private: System::Windows::Forms::Timer^  timer1;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::CheckBox^  checkBox3;
private: System::Windows::Forms::CheckBox^  checkBox4;
private: System::Windows::Forms::CheckBox^  checkBox2;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::TextBox^  tb_startTime;
private: System::Windows::Forms::Button^  b_transferDataFile;
private: System::Windows::Forms::Button^  b_deleteDataFile;
private: System::Windows::Forms::SaveFileDialog^  saveFileDialog_TXFile;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::TextBox^  tb_TXFileLocation;


private: System::Windows::Forms::Label^  label11;

private: System::Windows::Forms::ToolStripMenuItem^  recoverMMToolStripMenuItem;
private: System::Windows::Forms::Button^  b_etherConnect;
private: System::Windows::Forms::TextBox^  tb_buff_disp_freq;

private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::TextBox^  tb_TX_progress;
private: System::Windows::Forms::ToolStripMenuItem^  closeEthernetConnectionToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  endDAQToolStripMenuItem;
private: System::Windows::Forms::Button^  b_InvertSignal;
private: System::Windows::Forms::Button^  b_UnInvertSignal;






















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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series13 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea6 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series14 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->restartToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->diagnosticsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->captureWaveformsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->recoverMMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeEthernetConnectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->endDAQToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cOMPortToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeCOMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->restartCOMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pSDOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesPSDToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartPSDToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->spectrumOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesSpectrumToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartSpectrumToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeBinWidthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addEnergyCutsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fOMOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesFOMToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartFOMToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addFOMCutsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ch_PSD = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->ch_Spectrum = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->ch_FOM = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->b_SetIntegrationTimes = (gcnew System::Windows::Forms::Button());
			this->tb_baseline = (gcnew System::Windows::Forms::TextBox());
			this->tb_short = (gcnew System::Windows::Forms::TextBox());
			this->tb_long = (gcnew System::Windows::Forms::TextBox());
			this->tb_full = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tb_trigger = (gcnew System::Windows::Forms::TextBox());
			this->b_SetThreshold = (gcnew System::Windows::Forms::Button());
			this->tb_updates = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->b_capturePSD = (gcnew System::Windows::Forms::Button());
			this->b_saveFile = (gcnew System::Windows::Forms::Button());
			this->chk_stf = (gcnew System::Windows::Forms::CheckBox());
			this->chk_atf = (gcnew System::Windows::Forms::CheckBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tb_savefilename = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tb_counterbox = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tb_startTime = (gcnew System::Windows::Forms::TextBox());
			this->b_transferDataFile = (gcnew System::Windows::Forms::Button());
			this->b_deleteDataFile = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog_TXFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tb_TXFileLocation = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->b_etherConnect = (gcnew System::Windows::Forms::Button());
			this->tb_buff_disp_freq = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->tb_TX_progress = (gcnew System::Windows::Forms::TextBox());
			this->b_InvertSignal = (gcnew System::Windows::Forms::Button());
			this->b_UnInvertSignal = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_PSD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_Spectrum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_FOM))->BeginInit();
			this->SuspendLayout();
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 921600;
			this->serialPort1->ReadTimeout = 3;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(784, 377);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(97, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(725, 381);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(53, 13);
			this->label6->TabIndex = 27;
			this->label6->Text = L"COM Port";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->fileToolStripMenuItem,
					this->diagnosticsToolStripMenuItem, this->cOMPortToolStripMenuItem, this->pSDOptionsToolStripMenuItem, this->spectrumOptionsToolStripMenuItem,
					this->fOMOptionsToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1269, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->restartToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// restartToolStripMenuItem
			// 
			this->restartToolStripMenuItem->Name = L"restartToolStripMenuItem";
			this->restartToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->restartToolStripMenuItem->Text = L"&Restart";
			this->restartToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::restartToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
			// 
			// diagnosticsToolStripMenuItem
			// 
			this->diagnosticsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->captureWaveformsToolStripMenuItem,
					this->recoverMMToolStripMenuItem, this->closeEthernetConnectionToolStripMenuItem, this->endDAQToolStripMenuItem
			});
			this->diagnosticsToolStripMenuItem->Name = L"diagnosticsToolStripMenuItem";
			this->diagnosticsToolStripMenuItem->Size = System::Drawing::Size(80, 20);
			this->diagnosticsToolStripMenuItem->Text = L"&Diagnostics";
			// 
			// captureWaveformsToolStripMenuItem
			// 
			this->captureWaveformsToolStripMenuItem->Name = L"captureWaveformsToolStripMenuItem";
			this->captureWaveformsToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->captureWaveformsToolStripMenuItem->Text = L"&Capture Waveforms";
			this->captureWaveformsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::captureWaveformsToolStripMenuItem_Click);
			// 
			// recoverMMToolStripMenuItem
			// 
			this->recoverMMToolStripMenuItem->Name = L"recoverMMToolStripMenuItem";
			this->recoverMMToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->recoverMMToolStripMenuItem->Text = L"Recover MM";
			this->recoverMMToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::recoverMMToolStripMenuItem_Click);
			// 
			// closeEthernetConnectionToolStripMenuItem
			// 
			this->closeEthernetConnectionToolStripMenuItem->Name = L"closeEthernetConnectionToolStripMenuItem";
			this->closeEthernetConnectionToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->closeEthernetConnectionToolStripMenuItem->Text = L"Close Ethernet Connection";
			this->closeEthernetConnectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closeEthernetConnectionToolStripMenuItem_Click);
			// 
			// endDAQToolStripMenuItem
			// 
			this->endDAQToolStripMenuItem->Name = L"endDAQToolStripMenuItem";
			this->endDAQToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->endDAQToolStripMenuItem->Text = L"End DAQ";
			this->endDAQToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::endDAQToolStripMenuItem_Click);
			// 
			// cOMPortToolStripMenuItem
			// 
			this->cOMPortToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->closeCOMToolStripMenuItem,
					this->restartCOMToolStripMenuItem
			});
			this->cOMPortToolStripMenuItem->Name = L"cOMPortToolStripMenuItem";
			this->cOMPortToolStripMenuItem->Size = System::Drawing::Size(72, 20);
			this->cOMPortToolStripMenuItem->Text = L"&COM Port";
			// 
			// closeCOMToolStripMenuItem
			// 
			this->closeCOMToolStripMenuItem->Name = L"closeCOMToolStripMenuItem";
			this->closeCOMToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->closeCOMToolStripMenuItem->Text = L"Close COM";
			this->closeCOMToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closeCOMToolStripMenuItem_Click);
			// 
			// restartCOMToolStripMenuItem
			// 
			this->restartCOMToolStripMenuItem->Name = L"restartCOMToolStripMenuItem";
			this->restartCOMToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->restartCOMToolStripMenuItem->Text = L"Restart COM";
			this->restartCOMToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::restartCOMToolStripMenuItem_Click);
			// 
			// pSDOptionsToolStripMenuItem
			// 
			this->pSDOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->changeAxesPSDToolStripMenuItem,
					this->clearChartPSDToolStripMenuItem
			});
			this->pSDOptionsToolStripMenuItem->Name = L"pSDOptionsToolStripMenuItem";
			this->pSDOptionsToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->pSDOptionsToolStripMenuItem->Text = L"&PSD Options";
			// 
			// changeAxesPSDToolStripMenuItem
			// 
			this->changeAxesPSDToolStripMenuItem->Name = L"changeAxesPSDToolStripMenuItem";
			this->changeAxesPSDToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->changeAxesPSDToolStripMenuItem->Text = L"Change &Axes";
			this->changeAxesPSDToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::changeAxesPSDToolStripMenuItem_Click);
			// 
			// clearChartPSDToolStripMenuItem
			// 
			this->clearChartPSDToolStripMenuItem->Name = L"clearChartPSDToolStripMenuItem";
			this->clearChartPSDToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->clearChartPSDToolStripMenuItem->Text = L"Clear Chart";
			this->clearChartPSDToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearChartPSDToolStripMenuItem_Click);
			// 
			// spectrumOptionsToolStripMenuItem
			// 
			this->spectrumOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->changeAxesSpectrumToolStripMenuItem1,
					this->clearChartSpectrumToolStripMenuItem1, this->changeBinWidthToolStripMenuItem, this->addEnergyCutsToolStripMenuItem
			});
			this->spectrumOptionsToolStripMenuItem->Name = L"spectrumOptionsToolStripMenuItem";
			this->spectrumOptionsToolStripMenuItem->Size = System::Drawing::Size(115, 20);
			this->spectrumOptionsToolStripMenuItem->Text = L"&Spectrum Options";
			// 
			// changeAxesSpectrumToolStripMenuItem1
			// 
			this->changeAxesSpectrumToolStripMenuItem1->Name = L"changeAxesSpectrumToolStripMenuItem1";
			this->changeAxesSpectrumToolStripMenuItem1->Size = System::Drawing::Size(173, 22);
			this->changeAxesSpectrumToolStripMenuItem1->Text = L"Change Axes";
			this->changeAxesSpectrumToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::changeAxesSpectrumToolStripMenuItem1_Click);
			// 
			// clearChartSpectrumToolStripMenuItem1
			// 
			this->clearChartSpectrumToolStripMenuItem1->Name = L"clearChartSpectrumToolStripMenuItem1";
			this->clearChartSpectrumToolStripMenuItem1->Size = System::Drawing::Size(173, 22);
			this->clearChartSpectrumToolStripMenuItem1->Text = L"Clear Chart";
			this->clearChartSpectrumToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::clearChartSpectrumToolStripMenuItem1_Click);
			// 
			// changeBinWidthToolStripMenuItem
			// 
			this->changeBinWidthToolStripMenuItem->Name = L"changeBinWidthToolStripMenuItem";
			this->changeBinWidthToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->changeBinWidthToolStripMenuItem->Text = L"Change Bin Width";
			// 
			// addEnergyCutsToolStripMenuItem
			// 
			this->addEnergyCutsToolStripMenuItem->Name = L"addEnergyCutsToolStripMenuItem";
			this->addEnergyCutsToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->addEnergyCutsToolStripMenuItem->Text = L"Add Cuts on PSD...";
			this->addEnergyCutsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::addEnergyCutsToolStripMenuItem_Click);
			// 
			// fOMOptionsToolStripMenuItem
			// 
			this->fOMOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->changeAxesFOMToolStripMenuItem2,
					this->clearChartFOMToolStripMenuItem2, this->addFOMCutsToolStripMenuItem
			});
			this->fOMOptionsToolStripMenuItem->Name = L"fOMOptionsToolStripMenuItem";
			this->fOMOptionsToolStripMenuItem->Size = System::Drawing::Size(90, 20);
			this->fOMOptionsToolStripMenuItem->Text = L"&FOM Options";
			// 
			// changeAxesFOMToolStripMenuItem2
			// 
			this->changeAxesFOMToolStripMenuItem2->Name = L"changeAxesFOMToolStripMenuItem2";
			this->changeAxesFOMToolStripMenuItem2->Size = System::Drawing::Size(188, 22);
			this->changeAxesFOMToolStripMenuItem2->Text = L"Change Axes";
			this->changeAxesFOMToolStripMenuItem2->Click += gcnew System::EventHandler(this, &MyForm::changeAxesFOMToolStripMenuItem2_Click);
			// 
			// clearChartFOMToolStripMenuItem2
			// 
			this->clearChartFOMToolStripMenuItem2->Name = L"clearChartFOMToolStripMenuItem2";
			this->clearChartFOMToolStripMenuItem2->Size = System::Drawing::Size(188, 22);
			this->clearChartFOMToolStripMenuItem2->Text = L"Clear Chart";
			this->clearChartFOMToolStripMenuItem2->Click += gcnew System::EventHandler(this, &MyForm::clearChartFOMToolStripMenuItem2_Click);
			// 
			// addFOMCutsToolStripMenuItem
			// 
			this->addFOMCutsToolStripMenuItem->Name = L"addFOMCutsToolStripMenuItem";
			this->addFOMCutsToolStripMenuItem->Size = System::Drawing::Size(188, 22);
			this->addFOMCutsToolStripMenuItem->Text = L"Add Cuts on Energy...";
			this->addFOMCutsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::addFOMCutsToolStripMenuItem_Click);
			// 
			// ch_PSD
			// 
			this->ch_PSD->AntiAliasing = System::Windows::Forms::DataVisualization::Charting::AntiAliasingStyles::None;
			chartArea4->AxisX->IsStartedFromZero = false;
			chartArea4->AxisX->Maximum = 600000;
			chartArea4->AxisX->Minimum = 0;
			chartArea4->AxisY->Maximum = 2;
			chartArea4->AxisY->Minimum = 0;
			chartArea4->Name = L"ChartArea1";
			this->ch_PSD->ChartAreas->Add(chartArea4);
			this->ch_PSD->Location = System::Drawing::Point(13, 28);
			this->ch_PSD->Name = L"ch_PSD";
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series8->MarkerSize = 2;
			series8->Name = L"Series1";
			series9->BorderWidth = 4;
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->Color = System::Drawing::Color::Blue;
			series9->Name = L"series_ECutLower";
			series10->BorderWidth = 4;
			series10->ChartArea = L"ChartArea1";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series10->Color = System::Drawing::Color::Blue;
			series10->Name = L"series_ECutUpper";
			series11->BorderWidth = 4;
			series11->ChartArea = L"ChartArea1";
			series11->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series11->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series11->Name = L"series_FOMCutLeft";
			series11->YValuesPerPoint = 2;
			series12->BorderWidth = 4;
			series12->ChartArea = L"ChartArea1";
			series12->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series12->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series12->MarkerSize = 100;
			series12->Name = L"series_FOMCutRight";
			series12->YValuesPerPoint = 2;
			this->ch_PSD->Series->Add(series8);
			this->ch_PSD->Series->Add(series9);
			this->ch_PSD->Series->Add(series10);
			this->ch_PSD->Series->Add(series11);
			this->ch_PSD->Series->Add(series12);
			this->ch_PSD->Size = System::Drawing::Size(706, 343);
			this->ch_PSD->TabIndex = 29;
			this->ch_PSD->Text = L"chart1";
			this->ch_PSD->TextAntiAliasingQuality = System::Windows::Forms::DataVisualization::Charting::TextAntiAliasingQuality::Normal;
			// 
			// ch_Spectrum
			// 
			this->ch_Spectrum->AntiAliasing = System::Windows::Forms::DataVisualization::Charting::AntiAliasingStyles::None;
			chartArea5->AxisX->IsStartedFromZero = false;
			chartArea5->AxisX->Maximum = 600000;
			chartArea5->AxisX->Minimum = 0;
			chartArea5->AxisY->Maximum = 200;
			chartArea5->AxisY->Minimum = 0;
			chartArea5->Name = L"ChartArea1";
			this->ch_Spectrum->ChartAreas->Add(chartArea5);
			this->ch_Spectrum->IsSoftShadows = false;
			this->ch_Spectrum->Location = System::Drawing::Point(13, 377);
			this->ch_Spectrum->Name = L"ch_Spectrum";
			series13->ChartArea = L"ChartArea1";
			series13->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
			series13->MarkerSize = 2;
			series13->Name = L"Series1";
			this->ch_Spectrum->Series->Add(series13);
			this->ch_Spectrum->Size = System::Drawing::Size(706, 309);
			this->ch_Spectrum->TabIndex = 30;
			this->ch_Spectrum->Text = L"chart1";
			this->ch_Spectrum->TextAntiAliasingQuality = System::Windows::Forms::DataVisualization::Charting::TextAntiAliasingQuality::Normal;
			// 
			// ch_FOM
			// 
			chartArea6->AxisX->Maximum = 2;
			chartArea6->AxisX->Minimum = 0;
			chartArea6->AxisY->IsStartedFromZero = false;
			chartArea6->AxisY->Maximum = 1000;
			chartArea6->AxisY->Minimum = 0;
			chartArea6->Name = L"ChartArea1";
			this->ch_FOM->ChartAreas->Add(chartArea6);
			this->ch_FOM->Location = System::Drawing::Point(726, 28);
			this->ch_FOM->Name = L"ch_FOM";
			series14->ChartArea = L"ChartArea1";
			series14->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Bar;
			series14->CustomProperties = L"PointWidth=0.01";
			series14->Name = L"Series1";
			this->ch_FOM->Series->Add(series14);
			this->ch_FOM->Size = System::Drawing::Size(531, 343);
			this->ch_FOM->TabIndex = 31;
			this->ch_FOM->Text = L"chart1";
			// 
			// b_SetIntegrationTimes
			// 
			this->b_SetIntegrationTimes->Location = System::Drawing::Point(900, 470);
			this->b_SetIntegrationTimes->Name = L"b_SetIntegrationTimes";
			this->b_SetIntegrationTimes->Size = System::Drawing::Size(150, 41);
			this->b_SetIntegrationTimes->TabIndex = 8;
			this->b_SetIntegrationTimes->Text = L"Set Integration Times";
			this->b_SetIntegrationTimes->UseVisualStyleBackColor = true;
			this->b_SetIntegrationTimes->Click += gcnew System::EventHandler(this, &MyForm::b_SetIntegrationTimes_Click);
			// 
			// tb_baseline
			// 
			this->tb_baseline->Location = System::Drawing::Point(961, 378);
			this->tb_baseline->Name = L"tb_baseline";
			this->tb_baseline->Size = System::Drawing::Size(94, 20);
			this->tb_baseline->TabIndex = 4;
			this->tb_baseline->Text = L"-52";
			// 
			// tb_short
			// 
			this->tb_short->Location = System::Drawing::Point(961, 401);
			this->tb_short->Name = L"tb_short";
			this->tb_short->Size = System::Drawing::Size(94, 20);
			this->tb_short->TabIndex = 5;
			this->tb_short->Text = L"88";
			// 
			// tb_long
			// 
			this->tb_long->Location = System::Drawing::Point(962, 422);
			this->tb_long->Name = L"tb_long";
			this->tb_long->Size = System::Drawing::Size(93, 20);
			this->tb_long->TabIndex = 6;
			this->tb_long->Text = L"472";
			// 
			// tb_full
			// 
			this->tb_full->Location = System::Drawing::Point(961, 445);
			this->tb_full->Name = L"tb_full";
			this->tb_full->Size = System::Drawing::Size(94, 20);
			this->tb_full->TabIndex = 7;
			this->tb_full->Text = L"6000";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(900, 384);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 37;
			this->label1->Text = L"Baseline";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(900, 404);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(47, 13);
			this->label2->TabIndex = 38;
			this->label2->Text = L"Short Int";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(900, 425);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 13);
			this->label3->TabIndex = 39;
			this->label3->Text = L"Long Int";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(900, 448);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 13);
			this->label4->TabIndex = 40;
			this->label4->Text = L"Full Int";
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(726, 437);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(63, 31);
			this->label5->TabIndex = 41;
			this->label5->Text = L"Trigger Threshold";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tb_trigger
			// 
			this->tb_trigger->Location = System::Drawing::Point(788, 443);
			this->tb_trigger->Name = L"tb_trigger";
			this->tb_trigger->Size = System::Drawing::Size(94, 20);
			this->tb_trigger->TabIndex = 2;
			this->tb_trigger->Text = L"8700";
			// 
			// b_SetThreshold
			// 
			this->b_SetThreshold->Location = System::Drawing::Point(729, 471);
			this->b_SetThreshold->Name = L"b_SetThreshold";
			this->b_SetThreshold->Size = System::Drawing::Size(153, 41);
			this->b_SetThreshold->TabIndex = 3;
			this->b_SetThreshold->Text = L"Set Trigger Threshold";
			this->b_SetThreshold->UseVisualStyleBackColor = true;
			this->b_SetThreshold->Click += gcnew System::EventHandler(this, &MyForm::b_SetThreshold_Click);
			// 
			// tb_updates
			// 
			this->tb_updates->Location = System::Drawing::Point(919, 638);
			this->tb_updates->Name = L"tb_updates";
			this->tb_updates->ReadOnly = true;
			this->tb_updates->Size = System::Drawing::Size(338, 20);
			this->tb_updates->TabIndex = 44;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(860, 641);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(50, 13);
			this->label7->TabIndex = 45;
			this->label7->Text = L"Updates:";
			// 
			// b_capturePSD
			// 
			this->b_capturePSD->Enabled = false;
			this->b_capturePSD->Location = System::Drawing::Point(900, 564);
			this->b_capturePSD->Name = L"b_capturePSD";
			this->b_capturePSD->Size = System::Drawing::Size(150, 41);
			this->b_capturePSD->TabIndex = 10;
			this->b_capturePSD->Text = L"Capture PSD";
			this->b_capturePSD->UseVisualStyleBackColor = true;
			this->b_capturePSD->Click += gcnew System::EventHandler(this, &MyForm::b_capturePSD_Click);
			// 
			// b_saveFile
			// 
			this->b_saveFile->Location = System::Drawing::Point(733, 596);
			this->b_saveFile->Name = L"b_saveFile";
			this->b_saveFile->Size = System::Drawing::Size(107, 41);
			this->b_saveFile->TabIndex = 9;
			this->b_saveFile->Text = L"Choose Save File...";
			this->b_saveFile->UseVisualStyleBackColor = true;
			this->b_saveFile->Click += gcnew System::EventHandler(this, &MyForm::b_saveFile_Click);
			// 
			// chk_stf
			// 
			this->chk_stf->AutoSize = true;
			this->chk_stf->Location = System::Drawing::Point(733, 562);
			this->chk_stf->Name = L"chk_stf";
			this->chk_stf->Size = System::Drawing::Size(107, 17);
			this->chk_stf->TabIndex = 48;
			this->chk_stf->Text = L"Save to New File";
			this->chk_stf->UseVisualStyleBackColor = true;
			// 
			// chk_atf
			// 
			this->chk_atf->AutoSize = true;
			this->chk_atf->Checked = true;
			this->chk_atf->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chk_atf->Location = System::Drawing::Point(733, 578);
			this->chk_atf->Name = L"chk_atf";
			this->chk_atf->Size = System::Drawing::Size(94, 17);
			this->chk_atf->TabIndex = 49;
			this->chk_atf->Text = L"Append to File";
			this->chk_atf->UseVisualStyleBackColor = true;
			// 
			// tb_savefilename
			// 
			this->tb_savefilename->Location = System::Drawing::Point(725, 664);
			this->tb_savefilename->Name = L"tb_savefilename";
			this->tb_savefilename->ReadOnly = true;
			this->tb_savefilename->Size = System::Drawing::Size(532, 20);
			this->tb_savefilename->TabIndex = 50;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(726, 646);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(98, 13);
			this->label8->TabIndex = 51;
			this->label8->Text = L"Save File Location:";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// tb_counterbox
			// 
			this->tb_counterbox->Location = System::Drawing::Point(1060, 576);
			this->tb_counterbox->Name = L"tb_counterbox";
			this->tb_counterbox->ReadOnly = true;
			this->tb_counterbox->Size = System::Drawing::Size(20, 20);
			this->tb_counterbox->TabIndex = 52;
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->WorkerReportsProgress = true;
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker2_DoWork);
			this->backgroundWorker2->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker2_ProgressChanged);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(1086, 573);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(83, 17);
			this->checkBox1->TabIndex = 53;
			this->checkBox1->Text = L"Data Sorted";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(1174, 573);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(61, 17);
			this->checkBox3->TabIndex = 55;
			this->checkBox3->Text = L"Plotting";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(1174, 589);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(83, 17);
			this->checkBox4->TabIndex = 56;
			this->checkBox4->Text = L"Buffer Done";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(1086, 589);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(78, 17);
			this->checkBox2->TabIndex = 54;
			this->checkBox2->Text = L"Processing";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(855, 615);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(58, 13);
			this->label9->TabIndex = 58;
			this->label9->Text = L"Start Time:";
			// 
			// tb_startTime
			// 
			this->tb_startTime->Location = System::Drawing::Point(919, 612);
			this->tb_startTime->Name = L"tb_startTime";
			this->tb_startTime->ReadOnly = true;
			this->tb_startTime->Size = System::Drawing::Size(338, 20);
			this->tb_startTime->TabIndex = 57;
			// 
			// b_transferDataFile
			// 
			this->b_transferDataFile->Enabled = false;
			this->b_transferDataFile->Location = System::Drawing::Point(1083, 378);
			this->b_transferDataFile->Name = L"b_transferDataFile";
			this->b_transferDataFile->Size = System::Drawing::Size(152, 41);
			this->b_transferDataFile->TabIndex = 11;
			this->b_transferDataFile->Text = L"Transfer SD Data File";
			this->b_transferDataFile->UseVisualStyleBackColor = true;
			this->b_transferDataFile->Click += gcnew System::EventHandler(this, &MyForm::b_transferDataFile_Click);
			// 
			// b_deleteDataFile
			// 
			this->b_deleteDataFile->Enabled = false;
			this->b_deleteDataFile->Location = System::Drawing::Point(1083, 489);
			this->b_deleteDataFile->Name = L"b_deleteDataFile";
			this->b_deleteDataFile->Size = System::Drawing::Size(152, 23);
			this->b_deleteDataFile->TabIndex = 12;
			this->b_deleteDataFile->Text = L"Delete SD Data File";
			this->b_deleteDataFile->UseVisualStyleBackColor = true;
			this->b_deleteDataFile->Click += gcnew System::EventHandler(this, &MyForm::b_deleteDataFile_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(1083, 422);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(112, 13);
			this->label10->TabIndex = 61;
			this->label10->Text = L"Transfer File Location:";
			// 
			// tb_TXFileLocation
			// 
			this->tb_TXFileLocation->BackColor = System::Drawing::SystemColors::Control;
			this->tb_TXFileLocation->Location = System::Drawing::Point(1061, 437);
			this->tb_TXFileLocation->Name = L"tb_TXFileLocation";
			this->tb_TXFileLocation->ReadOnly = true;
			this->tb_TXFileLocation->Size = System::Drawing::Size(196, 20);
			this->tb_TXFileLocation->TabIndex = 62;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(1057, 465);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(102, 13);
			this->label11->TabIndex = 64;
			this->label11->Text = L"TX Progress (bytes):";
			// 
			// b_etherConnect
			// 
			this->b_etherConnect->Location = System::Drawing::Point(729, 404);
			this->b_etherConnect->Name = L"b_etherConnect";
			this->b_etherConnect->Size = System::Drawing::Size(153, 33);
			this->b_etherConnect->TabIndex = 66;
			this->b_etherConnect->Text = L"Connect to Ethernet";
			this->b_etherConnect->UseVisualStyleBackColor = true;
			this->b_etherConnect->Click += gcnew System::EventHandler(this, &MyForm::b_etherConnect_Click);
			// 
			// tb_buff_disp_freq
			// 
			this->tb_buff_disp_freq->Location = System::Drawing::Point(858, 518);
			this->tb_buff_disp_freq->Name = L"tb_buff_disp_freq";
			this->tb_buff_disp_freq->Size = System::Drawing::Size(23, 20);
			this->tb_buff_disp_freq->TabIndex = 67;
			this->tb_buff_disp_freq->Text = L"10";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(732, 520);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(125, 13);
			this->label12->TabIndex = 68;
			this->label12->Text = L"Buffer Display Frequency";
			// 
			// tb_TX_progress
			// 
			this->tb_TX_progress->BackColor = System::Drawing::SystemColors::Control;
			this->tb_TX_progress->Location = System::Drawing::Point(1157, 462);
			this->tb_TX_progress->Name = L"tb_TX_progress";
			this->tb_TX_progress->Size = System::Drawing::Size(100, 20);
			this->tb_TX_progress->TabIndex = 69;
			// 
			// b_InvertSignal
			// 
			this->b_InvertSignal->Location = System::Drawing::Point(900, 517);
			this->b_InvertSignal->Name = L"b_InvertSignal";
			this->b_InvertSignal->Size = System::Drawing::Size(70, 41);
			this->b_InvertSignal->TabIndex = 70;
			this->b_InvertSignal->Text = L"Invert";
			this->b_InvertSignal->UseVisualStyleBackColor = true;
			this->b_InvertSignal->Click += gcnew System::EventHandler(this, &MyForm::b_InvertSignal_Click);
			// 
			// b_UnInvertSignal
			// 
			this->b_UnInvertSignal->Location = System::Drawing::Point(980, 517);
			this->b_UnInvertSignal->Name = L"b_UnInvertSignal";
			this->b_UnInvertSignal->Size = System::Drawing::Size(70, 41);
			this->b_UnInvertSignal->TabIndex = 71;
			this->b_UnInvertSignal->Text = L"Un-invert";
			this->b_UnInvertSignal->UseVisualStyleBackColor = true;
			this->b_UnInvertSignal->Click += gcnew System::EventHandler(this, &MyForm::b_UnInvertSignal_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1269, 698);
			this->Controls->Add(this->b_UnInvertSignal);
			this->Controls->Add(this->b_InvertSignal);
			this->Controls->Add(this->tb_TX_progress);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->tb_buff_disp_freq);
			this->Controls->Add(this->b_etherConnect);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->tb_TXFileLocation);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->b_deleteDataFile);
			this->Controls->Add(this->b_transferDataFile);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->tb_startTime);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->tb_counterbox);
			this->Controls->Add(this->chk_atf);
			this->Controls->Add(this->chk_stf);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->tb_savefilename);
			this->Controls->Add(this->b_saveFile);
			this->Controls->Add(this->b_capturePSD);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tb_updates);
			this->Controls->Add(this->b_SetThreshold);
			this->Controls->Add(this->tb_trigger);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tb_full);
			this->Controls->Add(this->tb_long);
			this->Controls->Add(this->tb_short);
			this->Controls->Add(this->tb_baseline);
			this->Controls->Add(this->b_SetIntegrationTimes);
			this->Controls->Add(this->ch_FOM);
			this->Controls->Add(this->ch_Spectrum);
			this->Controls->Add(this->ch_PSD);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Luna H Map GUI";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_PSD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_Spectrum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_FOM))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
private:	//declare class-wide variables here
	double m_energyLowerCut{ 0.0 };
	double m_energyUpperCut{ 0.0 };
	double m_fomLeftCut{ 0.0 };
	double m_fomRightCut{ 0.0 };
	SOCKET ConnectSocket = INVALID_SOCKET;
	INT64 g_RECV_file_size;

private: void findPorts(void)
{
	array<Object^>^ objectArray = SerialPort::GetPortNames();
	this->comboBox1->Items->AddRange(objectArray);		
}

private: System::Void captureWaveformsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/* When moving between screens, need to close open ports*/
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->Close();
	}
	
	/*show the capture waveforms pop up */
	captureWaveformsPopup ^ captureWFs = gcnew captureWaveformsPopup();
	captureWFs->Show();
}//eocapturewaveformsshow

private: System::Void b_SetIntegrationTimes_Click(System::Object^  sender, System::EventArgs^  e) {
	int baselineInt = 0;
	int shortInt = 0;
	int longInt = 0;
	int fullInt = 0;
	String^ baselineMessage = this->tb_baseline->Text;
	String^ shortMessage = this->tb_short->Text;
	String^ longMessage = this->tb_long->Text;
	String^ fullMessage = this->tb_full->Text;

	/* Open the serial port */
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen) {
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
			this->b_SetIntegrationTimes->Enabled = false;
		}
		else
			this->b_SetIntegrationTimes->Enabled = false;
	}

	this->serialPort1->WriteLine("4");	//change integrals at the main menu
	Sleep(500);							//retMessage = this->serialPort1->ReadLine();	//"enter each integral..."
	this->serialPort1->WriteLine(baselineMessage);
	Sleep(500);
	this->serialPort1->WriteLine(shortMessage);
	Sleep(500);
	this->serialPort1->WriteLine(longMessage);
	Sleep(500);
	this->serialPort1->WriteLine(fullMessage);
	Sleep(500);

	this->serialPort1->DiscardInBuffer();

	this->tb_updates->Text = "Integral times have been set.";
	this->b_SetIntegrationTimes->Enabled = true;
}//eoSetIntegrationTimes

private: System::Void b_SetThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
	/* This button click will allow the user to change the trigger threshold of the system over the serial port */
	String^ thresholdMessage = this->tb_trigger->Text;

	/* Open the serial port */
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen) {
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
			this->b_SetThreshold->Enabled = false;
		}
		else {
			this->tb_updates->Text = (this->comboBox1->Text) + " is already open.";
			this->b_SetThreshold->Enabled = false;
			Application::DoEvents();
		}
	}

	/* Send commands to the uZ over the serial connection */
	this->serialPort1->WriteLine("3");				//choose change threshold from main menu
	Sleep(500);
	this->serialPort1->WriteLine(thresholdMessage);	//write the threshold specified by the user
	Sleep(1200);

	this->serialPort1->DiscardInBuffer();

	///* Clean up */
	this->tb_updates->Text = "Trigger threshold has been set.";
	this->b_SetThreshold->Enabled = true;

}//eoSetThreshold

private: System::Void b_capturePSD_Click(System::Object^  sender, System::EventArgs^  e) {

	//background worker stuff
	psdCap_run = !psdCap_run;		//init'd as false
	if (psdCap_run)
	{
		this->b_capturePSD->Text = "Stop Capture";
	}
	if (!psdCap_run)	//stop capturing data
	{
		this->b_capturePSD->Text = "Capture PSD";
		this->tb_updates->Text = "Stop button pressed; background worker being cancelled.";
		//send the message to stop DAQ on the board
		this->serialPort1->WriteLine("q");
		Sleep(500);
		//cancel the worker thread
		backgroundWorker1->CancelAsync();
		return;	//returns out of this function call to the still running call of this function
	}
	//String^ s_fileName;
	dataForBkgdWorker^ s_variables = gcnew dataForBkgdWorker;	//lets you name the fileName and portName

	if (this->comboBox1->Text == String::Empty) 
	{
		this->tb_updates->Text = "Select a port above.";
		this->b_capturePSD->Text = "Capture PSD";
		psdCap_run = !psdCap_run;
		return;
	}
	else 
	{
		if (!this->serialPort1->IsOpen) 
		{
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
		}
		else
			this->tb_updates->Text = (this->comboBox1->Text) + " is open.";
	}
		
	//put the serial port number into the data for background worker struct so we can pass it in
	s_variables->portName = this->comboBox1->Text;
	if (this->tb_buff_disp_freq->Text == String::Empty)
		s_variables->bufferDisplayFrequency = "10";
	else
		s_variables->bufferDisplayFrequency = this->tb_buff_disp_freq->Text;
	
	if (psdCap_run && chk_atf->Checked)	//if we are running and one of the check buttons is checked, get the file name to pass
	{
		if (this->tb_savefilename->Text == String::Empty)		//if checked, but no file name, return
		{
			this->tb_updates->Text = "Please choose a file save location.";
			this->b_capturePSD->Text = "Capture PSD";
			psdCap_run = !psdCap_run;
			return;
		}

		// Get the filename
		s_variables->mstrFileName = this->saveFileDialog1->FileName;
	}

	this->serialPort1->WriteLine("0");	//choose change mode from main menu
	Sleep(500);
	this->serialPort1->WriteLine("4");	//choose processed data mode
	Sleep(500);

	/* Determine domain and range for the FOM, Energy Spectrum charts here */
	double dPSDXmin = 0.0;
	double dPSDXmax = 0.0;
	double dSpectrumDomain = 0.0;
	double dPSDYmin = 0.0;
	double dPSDYmax = 0.0;
	double dFOMRange = 0.0;
	iNumberSpectrumBins = 1000;
	iFOMBins = 100;				
	dSpectrumBinSize = 0.0;		
	dFOMBinSize = 0.0;			

	// Determine the domain and set axes for the spectrum graph
	dPSDXmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;			//get the min and max of the PSD chart
	dPSDXmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
	this->ch_Spectrum->ChartAreas[0]->AxisX->Minimum = dPSDXmin;	//set the min and max of the spectrum chart to match
	this->ch_Spectrum->ChartAreas[0]->AxisX->Maximum = dPSDXmax;
	dSpectrumDomain = dPSDXmax - dPSDXmin;							//determine that domain of values
	dSpectrumBinSize = dSpectrumDomain / iNumberSpectrumBins;		//set the bin size accordingly //currently 1000 bins

	//Determine the range, set axes, and calculate the bin size for the FOM graph
	dPSDYmin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
	dPSDYmax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
	this->ch_FOM->ChartAreas[0]->AxisX->Minimum = dPSDYmin;
	this->ch_FOM->ChartAreas[0]->AxisX->Maximum = dPSDYmax;
	dFOMRange = dPSDYmax - dPSDYmin;
	dFOMBinSize = dFOMRange / iFOMBins;

	//initialize the global arrays here
	for (int i = 0; i < 1000; i++)
	{
		g_iESpectrumArray[i] = 0;
		if (i < 100)
			g_iFOMArray[i] = 0;
	}

	//Start the background worker and pass in s_variables which is a filename and port number
	backgroundWorker1->RunWorkerAsync(s_variables);
	g_RECV_file_size = 0;	//reset the file size
	return;
}//eoCapturePSDclick

private: System::Void b_saveFile_Click(System::Object^  sender, System::EventArgs^  e) {
	/* create instance of a save file dialog */
	saveFileDialog1->ShowDialog();
	tb_savefilename->Text = saveFileDialog1->FileName;
}//eosavefileclick

private: System::Void changeAxesPSDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/* Open small pop-up which takes in values for axes and passes them back here */
	double xMin;
	double xMax;
	double yMin;
	double yMax;

	xMin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
	xMax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
	yMin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
	yMax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;
	
	/* Show the change axes pop up */
	changeAxesPopUp ^ changePSDAxes = gcnew changeAxesPopUp( xMin, xMax, yMin, yMax);
	//Application::Run(changePSDAxes);
	changePSDAxes->ShowDialog();

	this->ch_PSD->ChartAreas[0]->AxisX->Minimum = changePSDAxes->getxMin();
	this->ch_PSD->ChartAreas[0]->AxisX->Maximum = changePSDAxes->getxMax();
	this->ch_PSD->ChartAreas[0]->AxisY->Minimum = changePSDAxes->getyMin();
	this->ch_PSD->ChartAreas[0]->AxisY->Maximum = changePSDAxes->getyMax();

	/* also change the spectrum chart because we need the two to be linked */
	this->ch_Spectrum->ChartAreas[0]->AxisX->Minimum = changePSDAxes->getxMin();
	this->ch_Spectrum->ChartAreas[0]->AxisX->Maximum = changePSDAxes->getxMax();
	this->ch_FOM->ChartAreas[0]->AxisY->Minimum = changePSDAxes->getyMin();
	this->ch_FOM->ChartAreas[0]->AxisY->Maximum = changePSDAxes->getyMax();

}//eochangepsdaxes

private: System::Void changeAxesSpectrumToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	double xMin;
	double xMax;
	double yMin;
	double yMax;

	xMin = this->ch_Spectrum->ChartAreas[0]->AxisX->Minimum;
	xMax = this->ch_Spectrum->ChartAreas[0]->AxisX->Maximum;
	yMin = this->ch_Spectrum->ChartAreas[0]->AxisY->Minimum;
	yMax = this->ch_Spectrum->ChartAreas[0]->AxisY->Maximum;

	/* Show the change axes pop up */
	changeAxesPopUp ^ changeSpectrumAxes = gcnew changeAxesPopUp(xMin, xMax, yMin, yMax);
	//Application::Run(changePSDAxes);
	changeSpectrumAxes->ShowDialog();

	this->ch_Spectrum->ChartAreas[0]->AxisX->Minimum = changeSpectrumAxes->getxMin();
	this->ch_Spectrum->ChartAreas[0]->AxisX->Maximum = changeSpectrumAxes->getxMax();
	this->ch_Spectrum->ChartAreas[0]->AxisY->Minimum = changeSpectrumAxes->getyMin();
	this->ch_Spectrum->ChartAreas[0]->AxisY->Maximum = changeSpectrumAxes->getyMax();
}//eochangespectrumaxes

private: System::Void changeAxesFOMToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
	double xMin;
	double xMax;
	double yMin;
	double yMax;

	xMin = this->ch_FOM->ChartAreas[0]->AxisX->Minimum;
	xMax = this->ch_FOM->ChartAreas[0]->AxisX->Maximum;
	yMin = this->ch_FOM->ChartAreas[0]->AxisY->Minimum;
	yMax = this->ch_FOM->ChartAreas[0]->AxisY->Maximum;

	/* Show the change axes pop up */
	changeAxesPopUp ^ changeFOMAxes = gcnew changeAxesPopUp(xMin, xMax, yMin, yMax);
	//Application::Run(changePSDAxes);
	changeFOMAxes->ShowDialog();

	this->ch_FOM->ChartAreas[0]->AxisX->Minimum = changeFOMAxes->getxMin();
	this->ch_FOM->ChartAreas[0]->AxisX->Maximum = changeFOMAxes->getxMax();
	this->ch_FOM->ChartAreas[0]->AxisY->Minimum = changeFOMAxes->getyMin();
	this->ch_FOM->ChartAreas[0]->AxisY->Maximum = changeFOMAxes->getyMax();
}//eochangefomaxes

private: System::Void clearChartPSDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->ch_PSD->Series["Series1"]->Points->Clear();
	this->tb_updates->Text = "PSD Chart cleared.";
	Application::DoEvents();
}

private: System::Void clearChartSpectrumToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	this->ch_Spectrum->Series["Series1"]->Points->Clear();
	this->tb_updates->Text = "Energy spectrum chart cleared.";
	Application::DoEvents();
}

private: System::Void clearChartFOMToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
	this->ch_FOM->Series["Series1"]->Points->Clear();
	this->tb_updates->Text = "FOM chart cleared.";
	Application::DoEvents();
}

private: System::Void closeCOMToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
	if (!this->serialPort1->IsOpen)
	{
		this->tb_updates->Text = (this->comboBox1->Text) + " is already closed.";
		return;
	}
		
	this->serialPort1->Close();
	this->tb_updates->Text = (this->comboBox1->Text) + " has been closed.";
	return;
}

private: System::Void restartCOMToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/* scan for com ports again, fill the combobox */
	this->tb_updates->Text = "Closing any open ports...";
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->Close();
		this->tb_updates->Text = "Port closed.";
	}

	this->comboBox1->Items->Clear();
	findPorts();
	
	this->tb_updates->Text = "Please re-select a port.";
	return;
}
private: System::Void restartToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->Close();
	}

	/* shut down this instance of the application and start a new one */
	Application::Restart();
}//eorestart

private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->Close();
	}

	/* exit the application */
	Application::Exit();
}//eoexit

private: System::Void addEnergyCutsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/* This function plots lines horizontally across the PSD chart to indicate an Energy cut */
	/* This further allows the user to specify what energy range to look at and plot on the energy spectrum chart */
	double psdXmin{ 0.0 };
	double psdXmax{ 0.0 };
	double psdYmin{ 0.0 };
	double psdYmax{ 0.0 };

	psdXmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
	psdXmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
	psdYmin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
	psdYmax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;

	/* Show the set E cuts pop up */
	 setCutsPopUp ^ setECuts = gcnew setCutsPopUp(psdYmin, psdYmax);
	setECuts->ShowDialog();

	/* Retrieve the cuts the user entered and add them to the chart */
	m_energyLowerCut = setECuts->getCutLower();
	m_energyUpperCut = setECuts->getCutUpper();

	this->ch_PSD->Series["series_ECutLower"]->Points->Clear();
	this->ch_PSD->Series["series_ECutUpper"]->Points->Clear();

	if (m_energyLowerCut == 0 && m_energyUpperCut == 0)	//no cuts
	{
		m_energyLowerCut = 0.0;
		m_energyUpperCut = 0.0;
		this->tb_updates->Text = "No cuts chosen.";
		return;
	}

	if (m_energyLowerCut > 0 && m_energyUpperCut > 0)	//both cuts were chosen
	{
		this->ch_PSD->Series["series_ECutLower"]->Points->AddXY(psdXmin, m_energyLowerCut);
		this->ch_PSD->Series["series_ECutLower"]->Points->AddXY(psdXmax, m_energyLowerCut);
		this->ch_PSD->Series["series_ECutUpper"]->Points->AddXY(psdXmin, m_energyUpperCut);
		this->ch_PSD->Series["series_ECutUpper"]->Points->AddXY(psdXmax, m_energyUpperCut);
	}	

	if (m_energyLowerCut == 0 && m_energyUpperCut > 0)	//Just an upper cut
	{
		this->ch_PSD->Series["series_ECutUpper"]->Points->AddXY(psdXmin, m_energyUpperCut);
		this->ch_PSD->Series["series_ECutUpper"]->Points->AddXY(psdXmax, m_energyUpperCut);
	}
		
	if (m_energyLowerCut > 0 && m_energyUpperCut == 0)	//Just a lower cut
	{
		this->ch_PSD->Series["series_ECutLower"]->Points->AddXY(psdXmin, m_energyLowerCut);
		this->ch_PSD->Series["series_ECutLower"]->Points->AddXY(psdXmax, m_energyLowerCut);
	}
}

private: System::Void addFOMCutsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/* allows user to plot two vertical lines on ch_PSD, indicating cuts which are plotted by FOM chart */
	double psdXmin{ 0.0 };
	double psdXmax{ 0.0 };
	double psdYmin{ 0.0 };
	double psdYmax{ 0.0 };

	psdXmin = this->ch_PSD->ChartAreas[0]->AxisX->Minimum;
	psdXmax = this->ch_PSD->ChartAreas[0]->AxisX->Maximum;
	psdYmin = this->ch_PSD->ChartAreas[0]->AxisY->Minimum;
	psdYmax = this->ch_PSD->ChartAreas[0]->AxisY->Maximum;

	/* Show the set E cuts pop up */
	setCutsPopUp ^ setFOMCuts = gcnew setCutsPopUp(psdXmin, psdXmax);
	setFOMCuts->ShowDialog();

	/* Retrieve the cuts the user entered and add them to the chart */
	m_fomLeftCut = setFOMCuts->getCutLower();
	m_fomRightCut = setFOMCuts->getCutUpper();

	this->ch_PSD->Series["series_FOMCutLeft"]->Points->Clear();	
	this->ch_PSD->Series["series_FOMCutRight"]->Points->Clear();

	if (m_fomLeftCut == 0 && m_fomRightCut == 0)	//no cuts
	{
		m_fomLeftCut = 0.0;
		m_fomRightCut = 0.0;

		this->tb_updates->Text = "No cuts chosen.";
		return;
	}

	if (m_fomLeftCut > 0 && m_fomRightCut > 0)	//both cuts were chosen
	{
		this->ch_PSD->Series["series_FOMCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmin);
		this->ch_PSD->Series["series_FOMCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmax);
		this->ch_PSD->Series["series_FOMCutRight"]->Points->AddXY(m_fomRightCut, psdYmin);
		this->ch_PSD->Series["series_FOMCutRight"]->Points->AddXY(m_fomRightCut, psdYmax);
	}

	if (m_fomLeftCut == 0 && m_fomRightCut > 0)	//Just an upper cut
	{
		this->ch_PSD->Series["series_FOMCutRight"]->Points->AddXY(m_fomRightCut, psdYmin);
		this->ch_PSD->Series["series_FOMCutRight"]->Points->AddXY(m_fomRightCut, psdYmax);
	}

	if (m_fomLeftCut > 0 && m_fomRightCut == 0)	//Just a lower cut
	{
		this->ch_PSD->Series["series_FOMCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmin);
		this->ch_PSD->Series["series_FOMCutLeft"]->Points->AddXY(m_fomLeftCut, psdYmax);
	}
}

/*	This function handles the ethernet connection and data collection from the board.
	This function passes an array of data to the backgroundWorker1_progressChanged function
	 where it will be processed and displayed. 
	
	NOTE: This function cannot access the "this->" pointer which means it cannot modify 
			anything on the [Design] page. To do this you must call ReportProgress() from
			this function.

	This function is started in a separate thread from the main GUI when runWorkerAsync() is called. 

*/
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

	String^ portname = safe_cast<dataForBkgdWorker^>(e->Argument)->portName;
	String^ buffDispFreq = safe_cast<dataForBkgdWorker^>(e->Argument)->bufferDisplayFrequency;
	String^ filename = safe_cast<dataForBkgdWorker^>(e->Argument)->mstrFileName;

	int m_buffDispFreq = int::Parse(buffDispFreq);
	if (m_buffDispFreq <= 0 || m_buffDispFreq > 1000)
		m_buffDispFreq = 10;
	std::string str_fileName = msclr::interop::marshal_as<std::string>(filename);
	std::ofstream outputFile;
	outputFile.open(str_fileName, std::ios::app);
	if (!outputFile)
		worker->ReportProgress(-1);	//tell the user we couldn't open the file

	//if the serial port isn't open, start serial connection
	if (!serialPort1->IsOpen) {
		serialPort1->PortName = portname;
		serialPort1->Open();
	}

	worker->ReportProgress(-11);	//tell the user that the port is open

	//Start DAQ
	if (serialPort1->IsOpen)
	{
		serialPort1->WriteLine("2");
		Sleep(500);
		worker->ReportProgress(-12);	//tell the user we started DAQ
	}

	//local variables
	int index{ 0 };
	g_dataBuffer = gcnew array<unsigned int>(DATABUFFER_SIZE) {};	//this buffer gets passed to the Progress changed function for processing //holds all 3 arrays (AA, LPF, DFF)
	
	char buffer[20] = "1";
	char *sendbuf = buffer;
	unsigned char recvbuf[DATA_BUFLEN]{};
	int recvbuflen = DATA_BUFLEN;	//length in bytes
	int iResult;
	int iIter = 0;
	int event_counter = 0;
	int m_bytes_received = 0;
	int m_packets_recvd = 0;

	int wsaResult = 0;

	while (worker->CancellationPending == false)//loop 2
	{
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			worker->ReportProgress(-18, WSAGetLastError());	//tell the user we failed a send
			wsaResult = WSAGetLastError();
			closesocket(ConnectSocket);
			WSACleanup();
			break;
		}

		//each packet from the board is 35*36=1260 bytes long and has 35*9 integers //there will be 13 packets total per full buffer 
		iResult = recv(ConnectSocket, (char *)recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			iIter = 0;
			event_counter = 0;
			while (event_counter < EVENT_SIZE * EVENTS_PER_BUFFER)
			{
				g_dataBuffer[index] = (recvbuf[iIter + 3] << 24) | (recvbuf[iIter + 2] << 16) | (recvbuf[iIter + 1] << 8) | recvbuf[iIter];
				outputFile << g_dataBuffer[index] << std::endl;

				iIter += 4;
				event_counter++;
				index++;
			}

			//we have received a full buffer, send it to ProgressChanged to be processed and displayed
			//We can place a switch here that will send only every Nth full buffer to ProgressChanged
			// This is in case processing the buffers causes too much of a hit to the system and we can't keep up at high event rates
			// ---i'm implementing the switch to send only one out of every ten buffers to the display
			// using the variable m_packets_recvd to keep track
			//Currently we send every buffer to be processed and displayed
			g_RECV_file_size += iResult;	//the total file size for this DAQ run //used to TX files and utilize the progress bar
			m_bytes_received += iResult;	iResult = 0;
			if (m_bytes_received >= DATA_BUFLEN)
			{
				m_packets_recvd++;
				if (m_packets_recvd == 0 || m_packets_recvd == m_buffDispFreq)
				{
					//pass the data to the report buffer for processing and display
					worker->ReportProgress(414141, g_dataBuffer);
					m_packets_recvd = 0;
				}
				m_bytes_received = 0;
				index = 0;
			}
		}
		else
		{
			if (WSAGetLastError() != 10060)	//time out error is 10060, we'll ignore that //we only care about other errors
				worker->ReportProgress(-19, WSAGetLastError());
		}
	}//end of loop 2

	outputFile.close();
	//worker->ReportProgress(-30);	//tell the user we have stopped DAQ
}
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	//update the main thread
	if (e->ProgressPercentage == -1)
	{
		this->tb_updates->Text = "Error opening local data file.";
		return;
	}
	else if (e->ProgressPercentage == -11)
	{
		this->tb_updates->Text = "Connected to the serial port.";
		return;
	}
	else if (e->ProgressPercentage == -12)
	{
		this->tb_updates->Text = "Data acquisition started.";
		return;
	}
	else if (e->ProgressPercentage == -13)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "Error initializing Winsock with code " + retVal;
		return;
	}
	else if (e->ProgressPercentage == -14)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "getaddrinfo failed with error " + retVal;
		return;
	}
	else if (e->ProgressPercentage == -15)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "Socket creation failed with error " + retVal;
		return;
	}
	else if (e->ProgressPercentage == -16)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "Connect failed with error " + retVal;
		return;
	}
	else if (e->ProgressPercentage == -17)
	{
		this->tb_updates->Text = "Socket connected at port: " + DEFAULT_PORT;
		return;
	}
	else if (e->ProgressPercentage == -18)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "DAQ Failed to send with " + retVal + ". Restarting connection.";
		return;
	}
	else if (e->ProgressPercentage == -19)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "Recv failed with " + retVal + ". Restarting connection.";
		return;
	}
	else if (e->ProgressPercentage == -20)
	{
		 int^ retVal = safe_cast< int^>(e->UserState);
		this->tb_updates->Text = "Received full buffer, updating display.";
		return;
	}
	else if (e->ProgressPercentage == -30)
	{
		this->tb_updates->Text = "Data acquisition thread stopped.";
		return;
	}
	else if (e->ProgressPercentage == 414141)	//the only else if where we stay in this function to parse out data and print to the charts
		this->tb_updates->Text = "Buffer received for processing.";
	else
	{
		this->tb_updates->Text = "Reporting progress for " + e->ProgressPercentage;
		return;
	}
	
	this->checkBox1->Checked = false;
	this->checkBox2->Checked = false;
	this->checkBox3->Checked = false;
	this->checkBox4->Checked = false;

	//Variables for processing
	int index(0);
	int eventIndex(0);

	array<unsigned int>^ dataBufferPassed = safe_cast<array<unsigned int>^>(e->UserState);	//this will be an unsigned int array[4095]
	array<dataProductEvent>^ eventsSorted = gcnew array<dataProductEvent>(INPUT_BUFFER_SIZE);

	//consume the first 111111 from databufferpassed
	while (1)
	{
		if (dataBufferPassed[index] == 111111)
		{
			if (dataBufferPassed[index + 1] == 111111)
				index++;	//increment by 1 (the next value is the real ID)
			break;								
		}
		else
			index++;	//if no, keep searching

		if (index >= DATABUFFER_SIZE - INTS_PER_EVENT)
		{
			this->tb_updates->Text = "No data found. Please check settings.";
			return;	//don't want to waste time trying to save this...
		}
	}


	while (index < DATABUFFER_SIZE - INTS_PER_EVENT)
	{
		switch (dataBufferPassed[index])
		{
		case 111111:
			//process the AA integrator data
			eventsSorted[eventIndex].aaTotalEvents = dataBufferPassed[index + 1];
			eventsSorted[eventIndex].aaEventNumber = dataBufferPassed[index + 2];
			eventsSorted[eventIndex].aaBaselineInt = dataBufferPassed[index + 3];
			eventsSorted[eventIndex].aaShortInt = dataBufferPassed[index + 4];
			eventsSorted[eventIndex].aaLongInt = dataBufferPassed[index + 5];
			eventsSorted[eventIndex].aaFullInt = dataBufferPassed[index + 6];
			eventsSorted[eventIndex].aaEight = dataBufferPassed[index + 7];
			index += 8;
			eventIndex++;	//move to the next event in the struct
			break;
		case 121212:
			//process the LPF data
			eventsSorted[eventIndex].lpfEventNumber = dataBufferPassed[index + 1];
			eventsSorted[eventIndex].lpfTTLSignal = dataBufferPassed[index + 2];
			eventsSorted[eventIndex].lpfBaselineInt = dataBufferPassed[index + 3];
			eventsSorted[eventIndex].lpfShortInt = dataBufferPassed[index + 4];
			eventsSorted[eventIndex].lpfFullInt = dataBufferPassed[index + 5];
			eventsSorted[eventIndex].lpfSeven = dataBufferPassed[index + 6];
			eventsSorted[eventIndex].lpfEight = dataBufferPassed[index + 7];
			index += 8;
			eventIndex++;
			break;
		case 131313:
			//process the LPF data
			eventsSorted[eventIndex].dffTimeSmall = dataBufferPassed[index + 1];
			eventsSorted[eventIndex].dffTimeBig = dataBufferPassed[index + 2];
			eventsSorted[eventIndex].dffEventNumber = dataBufferPassed[index + 3];
			eventsSorted[eventIndex].dffBaselineInt = dataBufferPassed[index + 4];
			eventsSorted[eventIndex].dffShortInt = dataBufferPassed[index + 5];
			eventsSorted[eventIndex].dffSeven = dataBufferPassed[index + 6];
			eventsSorted[eventIndex].dffEight = dataBufferPassed[index + 7];
			index += 8;
			eventIndex++;
			break;
		default:
			//if we hit this, we didn't find an identifier or the array is finished
			index++;	//check the next entry
			break;
		}
		
		if (eventIndex > INPUT_BUFFER_SIZE - 1)	//if we are at the bottom, reset for the next parts of the struct
		{
			//index++;
			eventIndex = 0;
		}
		if (index > DATABUFFER_SIZE - INTS_PER_EVENT)	//if we are near the top, in the last event, jump out (it's garbage)
			break;
	}

	//inform the user of the start time and event
	if (this->tb_startTime->Text == String::Empty)
	{
		DateTime tstart = System::DateTime::Now;
		int tevent = eventsSorted[0].aaEventNumber;
		this->tb_startTime->Text = "T = " + tstart + ", event: " + tevent;
	}

	//this->tb_updates->Text = "Data sorted.";
	this->checkBox1->Checked = true;
	//Now that data is sorted, sift through and plot it
	array<double>^ aablavgArray = gcnew array<double>(INPUT_BUFFER_SIZE);
	double bl1(0);	double bl2(0); double bl3(0); double bl4(0); double bl_avg(0);
	double si(0); double li(0); double fi(0);
	double psd(0);
	double energy(0);

	double dESpectrumBin(0.0);
	double dFOMBin(0.0);
	//double dFOMBinSize = (0.0);
	int iESpectrumArrayIndex(0);
	int iFOMArrayIndex(0);
	int ii(0); int jj(0);

	//get the ints from the textboxes //OLD
	//int i_short = int::Parse(this->tb_short->Text);
	//int i_long = int::Parse(this->tb_long->Text);
	//int i_full = int::Parse(this->tb_full->Text);

	//hard code this for now
	//get the ints from the textboxes //NEW
	double d_blSamples = ((INTEG_START_TIME + int::Parse(this->tb_baseline->Text)) / NS_TO_SAMPLES) + 1;
	double d_siSamples = ((INTEG_START_TIME + int::Parse(this->tb_short->Text)) / NS_TO_SAMPLES) + 1;
	double d_liSamples = ((INTEG_START_TIME + int::Parse(this->tb_long->Text)) / NS_TO_SAMPLES) + 1;
	double d_fiSamples = ((INTEG_START_TIME + int::Parse(this->tb_full->Text)) / NS_TO_SAMPLES) + 1;

	//this->tb_updates->Text = "Processing.";
	this->checkBox2->Checked = true;

	eventIndex = 0;	//reset this value
	while (eventIndex < INPUT_BUFFER_SIZE)	//plots the charts for each event
	{
		si = 0;	li = 0;	fi = 0;	psd = 0; energy = 0;

		bl4 = bl3; bl3 = bl2; bl2 = bl1;
		bl1 = eventsSorted[eventIndex].aaBaselineInt / (16.0 * d_blSamples);
		if (bl4 == 0.0)
			bl_avg = bl1;
		else
			bl_avg = (bl4 + bl3 + bl2 + bl1) / 4.0;
		aablavgArray[eventIndex] = bl_avg;

		//si = eventsSorted[eventIndex].aaShortInt / 16.0 - (bl_avg * (((i_short + 52) / 4) + 38));
		//li = eventsSorted[eventIndex].aaLongInt / 16.0 - (bl_avg * (((i_long + 52) / 4) + 38));
		//fi = eventsSorted[eventIndex].aaFullInt / 16.0 - (bl_avg * (((i_full + 52) / 4) + 38));
		si = (double)eventsSorted[eventIndex].aaShortInt / 16.0 - (bl_avg * d_siSamples);
		li = (double)eventsSorted[eventIndex].aaLongInt / 16.0 - (bl_avg * d_liSamples);
		fi = (double)eventsSorted[eventIndex].aaFullInt / 16.0 - (bl_avg * d_fiSamples);
		if (si > 0 && li > 0)
			if (si == li)	//handle the situation where the integrals are the same
				psd = 3.0;
			else
				psd = si / (li - si);
		energy = 1.0 * fi + 0.0;

		//plot code for PSD
		if ((psd > 0 && psd < 2) && (energy > 0 && energy < 600000))
		{
			this->ch_PSD->Series["Series1"]->Points->AddXY(fi, psd);

			//plot code for FOM and Energy Spectrum
			iESpectrumArrayIndex = Convert::ToInt32(energy / 600);	//check data is within the spectrum bins
			iFOMArrayIndex = Convert::ToInt32(psd / 0.02);
		}
		else
		{
			iESpectrumArrayIndex = 0;
			iFOMArrayIndex = 0;
		}
		if ((iESpectrumArrayIndex > 0 && iESpectrumArrayIndex < 1000) && (iFOMArrayIndex > 0 && iFOMArrayIndex < 99))	//if the point is within the array (on the chart)
		{
			++g_iESpectrumArray[iESpectrumArrayIndex];
			++g_iFOMArray[iFOMArrayIndex];
		
			/* clear charts and plot the arrays */
			this->ch_Spectrum->Series["Series1"]->Points->Clear();
			this->ch_FOM->Series["Series1"]->Points->Clear();

			for (jj = 0; jj < (iNumberSpectrumBins - 1); jj++)
			{
				dESpectrumBin = dSpectrumBinSize * (jj + 0.5);
				this->ch_Spectrum->Series["Series1"]->Points->AddXY(dESpectrumBin, g_iESpectrumArray[jj]);
			}
			for (ii = 0; ii < (iFOMBins - 1); ii++)
			{
				dFOMBin = dFOMBinSize * (ii + 0.5);
				this->ch_FOM->Series["Series1"]->Points->AddXY(dFOMBin, g_iFOMArray[ii]);
			}
		}
		this->tb_updates->Text = "evt proc: " + eventIndex;
		eventIndex++;
	}

	this->tb_updates->Text = "Done plotting.";
	this->checkBox3->Checked = true;

	//save Erik's file here
	/*
	std::ofstream outputFile_raw;
	outputFile_raw.open("runData_tabsep.txt", std::ios::app);
	for (index = 0; index < INPUT_BUFFER_SIZE - 1; index++)
	{
		outputFile_raw << std::setw(12) << eventsSorted[index].aaEventNumber << '\t'
			<< std::setw(12) << eventsSorted[index].aaTotalEvents << '\t'
			<< std::setw(11) << eventsSorted[index].lpfTTLSignal << '\t'
			<< std::setw(16) << ((eventsSorted[index].dffTimeSmall * 128.0e-9) + (eventsSorted[index].dffTimeBig * 549.7558139)) << '\t'
			<< std::setw(11) << (eventsSorted[index].aaBaselineInt) << '\t'
			<< std::setw(11) << (eventsSorted[index].aaShortInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].aaLongInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].aaFullInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].lpfBaselineInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].lpfShortInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].lpfFullInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].dffBaselineInt / 16.0) << '\t'
			<< std::setw(11) << (eventsSorted[index].dffShortInt / 16.0) << '\t'
			<< std::endl;
	}
	outputFile_raw.close();
	*/
	this->checkBox4->Checked = true;
}
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	//what to do on cancel or completion
	if (e->Cancelled)
		this->tb_updates->Text = "DAQ worker thread cancel success.";
	else if (e->Error != nullptr)
		MessageBox::Show(e->Error->Message);
	else if (e->Cancelled == FALSE)
	{
		this->tb_updates->Text = "Stopping the DAQ run. Please wait...CancelAsync";
	}
}
private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	BackgroundWorker^ counterWorker = dynamic_cast<BackgroundWorker^>(sender);
	int counter(0);

	while (1)
	{
		Sleep(500);
		counterWorker->ReportProgress(counter);
		counter++;
		if (counter > 9)	//if the counter goes to 10, reset it to 0
			counter = 0;	//ie. we loop 0 - 9 -> 0 - 9
	}
}
private: System::Void backgroundWorker2_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	this->tb_counterbox->Text = e->ProgressPercentage + " ";
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	
}
		 //Transfer the SD card file
		 //Start the ethernet connection
		 //Open a serial port and call the function
		 //Begin pinging the board to get the packets, they're the same size packets as data packets from DAQ
private: System::Void b_transferDataFile_Click(System::Object^  sender, System::EventArgs^  e) {
	this->b_transferDataFile->Text = "Transferring...";
	//use the same procedure as we use in DAQ to connect and accept packets
	const System::Windows::Forms::DialogResult idYES = (System::Windows::Forms::DialogResult)IDYES;
	const System::Windows::Forms::DialogResult idNO = (System::Windows::Forms::DialogResult)IDNO;
	const System::Windows::Forms::DialogResult idCANCEL = (System::Windows::Forms::DialogResult)IDCANCEL;
	//Messagebox("Main window message first", );
	switch (MessageBox::Show("Choose a new transfer save file location?\n\nNo will append the current file shown in the Transfer File Location box.\nCancel will abort the transfer.", "Transfer File Save Location", MessageBoxButtons::YesNoCancel))
	{
	case idYES:
		this->tb_updates->Text = "Choose a new transfer file save location.";
		saveFileDialog_TXFile->ShowDialog();
		tb_TXFileLocation->Text = saveFileDialog_TXFile->FileName;
		if (this->tb_TXFileLocation->Text == String::Empty)
		{
			this->tb_updates->Text = "No transfer file location is selected, please choose a new file location.";
			this->b_transferDataFile->Text = "Transfer SD Data File";
			return;
		}
		else
			this->tb_updates->Text = "Selected a new transfer file save location.";
		break;
	case idNO:
		this->tb_updates->Text = "Using the currently selected file save location.";
		if (this->tb_TXFileLocation->Text == String::Empty)
		{
			this->tb_updates->Text = "No transfer file location is selected, please choose a new file location.";
			this->b_transferDataFile->Text = "Transfer SD Data File";
			return;
		}
		break;
	case idCANCEL:	//both pressing the cancel button and closing the window with the 'X' come here
		this->tb_updates->Text = "Aborted the transfer.";
		this->b_transferDataFile->Text = "Transfer SD Data File";
		return;
		break;
	}
	this->tb_TX_progress->Text = "0 bytes";
	this->tb_updates->Text = "Transferring the file...";
	Application::DoEvents();

	//now we know there is a file we can save to, open the file to transfer into it
	std::ofstream tx_file;
	std::string tx_filename = msclr::interop::marshal_as<std::string>(tb_TXFileLocation->Text);
	tx_file.open(tx_filename, std::ios::app);

	char buffer[20] = "1";
	char *sendbuf = buffer;
	unsigned char recvbuf[DATA_BUFLEN]{};
	int recvbuflen = DATA_BUFLEN;	//length in bytes
	int iResult;
	int iIter = 0;
	int event_counter = 0;
	int m_timed_out = 0;
	INT64 m_bytes_received = 0;
	INT64 m_TX_file_size = 0;
	INT64 m_TX_steps = 1;
	INT64 m_TX_step_size = DATA_BUFLEN;
	INT64 m_TX_steps_to_take = 0;

	bool m_running = TRUE;

//check/open the serial connection to call the TX function
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		this->b_transferDataFile->Text = "Transfer SD Data File";
		tx_file.close();
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen)
		{
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
		}
	}

	serialPort1->WriteLine("10");
	Sleep(500);

	DWORD sockTO = 10;
	//SO_RCVTIMEO specifies the timout, in ms, for blocking recv calls
	setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&sockTO, sizeof(DWORD));

	//begin packet send/receive loop
	while (m_running)
	{
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			this->tb_updates->Text = "TX Failed to send with " + WSAGetLastError() + ". Reconnect to the board again.";
			this->b_etherConnect->Enabled = TRUE;
			closesocket(ConnectSocket);
			WSACleanup();
			tx_file.close();
			break;
		}

		iResult = recv(ConnectSocket, (char *)recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			m_timed_out = 0;	//reset this each time we get a packet
			//take in the packet and reassemble the ints from each buffer
			iIter = 0;
			event_counter = 0;
			//loop over the packet we received and reassemble the ints in each event
			while (event_counter < EVENT_SIZE * EVENTS_PER_BUFFER)
			{
				tx_file << ((recvbuf[iIter + 3] << 24) | (recvbuf[iIter + 2] << 16) | (recvbuf[iIter + 1] << 8) | recvbuf[iIter]) << std::endl;

				iIter += 4;
				event_counter++;
			}

			//updates a bar every 1% and breaks out when we're done transferring
			m_bytes_received += iResult;	iResult = 0;
			if (m_bytes_received >= m_TX_step_size * m_TX_steps)
			{
				m_TX_steps++;
				this->tb_TX_progress->Text = m_bytes_received + " bytes";
				Application::DoEvents();
			}
		}
		else
		{
			if (WSAGetLastError() != 10060)	//time out error is 10060, we'll ignore that //we only care about other errors
			{
				this->tb_updates->Text = "Receive failed with error " + WSAGetLastError() + ". Reconnect to the board again.";
				this->b_etherConnect->Enabled = TRUE; 
				closesocket(ConnectSocket);
				WSACleanup();
				tx_file.close();
				break;
			}
			else if (WSAGetLastError() == 10060)
				m_timed_out++;
			if (m_timed_out > 10)
			{
				//if we have not gotten a packet in 2s, then we will stop
				this->tb_updates->Text = "Finished receiving packets. " + m_bytes_received + " bytes received.";
				break;
			}
		}
	}//end of send/recv loop

	//quit from the loop, this way we always end up back at the main menu
	serialPort1->WriteLine("q");
	Sleep(500);

	this->b_transferDataFile->Text = "Transfer SD Data File";
	tx_file.close();
	return; 
}

//This function deletes the SD card file on the board
private: System::Void b_deleteDataFile_Click(System::Object^  sender, System::EventArgs^  e) {

	this->tb_updates->Text = "Deleteing the file...";
	//check/open the serial connection to call the TX function
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen)
		{
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
		}
	}

	System::String^ m_str_delete_ret;
	INT64 m_delete_ret = 0;

	//make sure we don't get garbage
	if (this->serialPort1->BytesToRead > 0)
		this->serialPort1->ReadExisting();
	//call the TX function on the board
	serialPort1->WriteLine("11");
	Sleep(500);
	if (this->serialPort1->BytesToRead > 0)
	{
		m_str_delete_ret = serialPort1->ReadLine();	//gets the file size, tells us how many bytes we should expect to read
		//if this throws an exception, just restart the connection
		m_delete_ret = System::Convert::ToInt64(m_str_delete_ret);
	}

	if (m_delete_ret == -21)
	{
		this->tb_updates->Text = "Error deleting the file.";
		return;
	}
	else
		this->tb_updates->Text = "Successfully deleted the SD card file.";

	return;
}

		 //connect to the serial port and send a couple of 'q's so that the board leaves DAQ?
private: System::Void recoverMMToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->tb_updates->Text = "Recovering to the main menu...";
	//check/open the serial connection to call the TX function
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen)
		{
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
		}
	}

	this->tb_updates->Text = "Commanding the board...";
	//make sure we don't get garbage
	if (this->serialPort1->BytesToRead > 0)
		this->serialPort1->ReadExisting();
	//quit to the main menu
	serialPort1->WriteLine("q");
	Sleep(1000);
	this->tb_updates->Text = "Commanding the board 1...";
	Application::DoEvents();
	serialPort1->WriteLine("q");
	Sleep(2000);
	this->tb_updates->Text = "Commanding the board 2...";
	Application::DoEvents();
	serialPort1->WriteLine("q");
	Sleep(3000);
	this->tb_updates->Text = "Board may be recovered.";

}

private: System::Void b_etherConnect_Click(System::Object^  sender, System::EventArgs^  e) {
	this->tb_updates->Text = "Connecting to the board...";
	//ethernet variables
	WSADATA wsaData;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char buffer[20] = "Hi there!";
	char *sendbuf = buffer;

	//other variables
	unsigned char recvbuf[DATA_BUFLEN]{};
	int recvbuflen = DATA_BUFLEN;	//length in bytes
	int iResult;
	int iIter = 0;
	int event_counter = 0;
	unsigned int reassemble_val = 0;
	int m_bytes_received = 0;
	int m_packets_recvd = 0;

	bool m_running = TRUE;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;			//chose AF_INET over AF_UNSPEC //try unspec
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	std::string m_ip_addr = "192.168.250.2";	//define the ip address for the server that we wish to connect to

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		this->tb_updates->Text = "Error initializing Winsock with code " + iResult;
		return;
	}

	// Resolve the server address and port
	this->tb_updates->Text = "Resolving the address and port information...";
	iResult = getaddrinfo(m_ip_addr.c_str(), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		this->tb_updates->Text = "getaddrinfo failed with error " + iResult;
		WSACleanup();
		return;
	}

	// Attempt to connect to an address until one succeeds
	this->tb_updates->Text = "Creating the socket...";
	ConnectSocket = socket(result->ai_family, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		this->tb_updates->Text = "socket failed with error: " + WSAGetLastError();
		WSACleanup();
		return;
	}

	//pass the created socket to the connect function
	this->tb_updates->Text = "Attempting to connect to the socket...";
	iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		this->tb_updates->Text = "socket failed with error: " + WSAGetLastError();
		WSACleanup();
		return;
	}

	//set a timeout for the socket that we are using, this will make it jump out of receive if
	// we haven't gotten anything in 100 ms
	DWORD sockTO = 10;
	//SO_RCVTIMEO specifies the timout, in ms, for blocking recv calls
	iResult = setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&sockTO, sizeof(DWORD));
	if (iResult != 0)
	{
		this->tb_updates->Text = "Set socket options failed with error: " + WSAGetLastError();
		Application::DoEvents();
		return;
	}

	this->tb_updates->Text = "Successfully connected. DAQ and transfer are now available.";
	this->b_capturePSD->Enabled = TRUE;
	this->b_deleteDataFile->Enabled = TRUE;
	this->b_transferDataFile->Enabled = TRUE;
	this->b_etherConnect->Enabled = FALSE;
	Application::DoEvents();
}
private: System::Void closeEthernetConnectionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->tb_updates->Text = "Closing the ethernet connection to the board. Please reconnect.";
	this->b_capturePSD->Enabled = FALSE;
	this->b_deleteDataFile->Enabled = FALSE;
	this->b_transferDataFile->Enabled = FALSE;
	this->b_etherConnect->Enabled = TRUE;
	Application::DoEvents();

	//run the disconnect code to clean up
	closesocket(ConnectSocket);
	ConnectSocket = INVALID_SOCKET;
	WSACleanup();

	return;
}
private: System::Void endDAQToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->tb_updates->Text = "Transferring the file...";
	Application::DoEvents();

	char buffer[20] = "1";
	char *sendbuf = buffer;
	unsigned char recvbuf[DATA_BUFLEN]{};
	int recvbuflen = DATA_BUFLEN;	//length in bytes
	int iResult;
	int iIter = 0;
	int event_counter = 0;
	int m_timed_out = 0;
	INT64 m_bytes_received = 0;
	INT64 m_TX_file_size = 0;
	INT64 m_TX_steps = 1;
	INT64 m_TX_step_size = DATA_BUFLEN;
	INT64 m_TX_steps_to_take = 0;

	bool m_running = TRUE;

	DWORD sockTO = 10;
	//SO_RCVTIMEO specifies the timout, in ms, for blocking recv calls
	setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&sockTO, sizeof(DWORD));


	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen)
		{
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
		}
	}

	//quit from the loop, this way we always end up back at the main menu
	serialPort1->WriteLine("q");
	Sleep(500);

	//begin packet send/receive loop
	while (m_running)
	{
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			this->tb_updates->Text = "TX Failed to send with " + WSAGetLastError() + ". Reconnect to the board again.";
			this->b_etherConnect->Enabled = TRUE;
			closesocket(ConnectSocket);
			WSACleanup();
			break;
		}

		iResult = recv(ConnectSocket, (char *)recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			m_timed_out = 0;	//reset this each time we get a packet
			//take in the packet and reassemble the ints from each buffer
			iIter = 0;
			event_counter = 0;
			//loop over the packet we received and reassemble the ints in each event
			while (event_counter < EVENT_SIZE * EVENTS_PER_BUFFER)
			{
				iIter += 4;
				event_counter++;
			}

			m_bytes_received += iResult;	iResult = 0;
			if (m_bytes_received >= m_TX_step_size * m_TX_steps)
			{
				m_TX_steps++;
				this->tb_TX_progress->Text = m_bytes_received + " bytes";
				Application::DoEvents();
			}
		}
		else
		{
			if (WSAGetLastError() != 10060)	//time out error is 10060, we'll ignore that //we only care about other errors
			{
				this->tb_updates->Text = "Receive failed with error " + WSAGetLastError() + ". Reconnect to the board again.";
				this->b_etherConnect->Enabled = TRUE;
				closesocket(ConnectSocket);
				WSACleanup();
				break;
			}
			else if (WSAGetLastError() == 10060)
				m_timed_out++;
			if (m_timed_out > 10)
			{
				//if we have not gotten a packet in 2s, then we will stop
				this->tb_updates->Text = "Finished receiving packets. " + m_bytes_received + " bytes received.";
				break;
			}
		}
	}//end of send/recv loop

	this->b_transferDataFile->Text = "Transfer SD Data File";
	return;
}

// TESTING 06-05-2019
// Send a serial command to the board to invert the output phase
private: System::Void b_InvertSignal_Click(System::Object^  sender, System::EventArgs^  e) {
	/* Open the serial port */
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen) {
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
			this->tb_updates->Text = "Writing to port " + (this->comboBox1->Text);
			this->b_InvertSignal->Enabled = false;
		}
		else {
			this->tb_updates->Text = "Writing to port " + (this->comboBox1->Text);
			this->b_InvertSignal->Enabled = false;
			Application::DoEvents();
		}
	}

	/* Send commands to the uZ over the serial connection */
	this->serialPort1->WriteLine("12");	//choose Invert Output Phase from main menu
	Sleep(1000);						//wait 1 second

	this->serialPort1->DiscardInBuffer();

	///* Clean up */
	this->tb_updates->Text = "The signal has been inverted.";
	this->b_InvertSignal->Enabled = true;
}

// TESTING 06-05-2019
// Send a serial command to the board to UN-invert the output phase
private: System::Void b_UnInvertSignal_Click(System::Object^  sender, System::EventArgs^  e) {
	/* Open the serial port */
	if (this->comboBox1->Text == String::Empty) {
		this->tb_updates->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen) {
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
			this->tb_updates->Text = "Writing to port " + (this->comboBox1->Text);
			this->b_UnInvertSignal->Enabled = false;
		}
		else {
			this->tb_updates->Text = "Writing to port " + (this->comboBox1->Text);
			this->b_UnInvertSignal->Enabled = false;
			Application::DoEvents();
		}
	}

	/* Send commands to the uZ over the serial connection */
	this->serialPort1->WriteLine("13");	//choose Invert Output Phase from main menu
	Sleep(1000);						//wait 1 second

	this->serialPort1->DiscardInBuffer();

	///* Clean up */
	this->tb_updates->Text = "The signal has been un-inverted.";
	this->b_UnInvertSignal->Enabled = true;
}
};
}
