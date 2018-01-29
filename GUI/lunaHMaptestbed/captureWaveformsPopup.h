#pragma once

#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>					//for marshalling
#include <msclr/marshal_cppstd.h>	//for marshalling
#include "changeAxesPopUp.h"

namespace lunaHMaptestbed {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for captureWaveformsPopup
	/// </summary>
	public ref class captureWaveformsPopup : public System::Windows::Forms::Form
	{
	public:
		captureWaveformsPopup(void)	//constructor: pass variables from myform to here by replacing void
		{
			InitializeComponent();
			findPorts();
			wfCap_run = false;
			this->comboBox2->SelectedIndex = 0;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~captureWaveformsPopup()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:








	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ch_DisplayWaveforms;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;




	private: System::Windows::Forms::TextBox^  tb_trigger_threshold;





	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  bChangeThreshold;

	private: System::Windows::Forms::Button^  bCaptureWFs;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  b_closeWFwindow;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::CheckBox^  chk_stf;


	private: System::Windows::Forms::Button^  tb_saveFile;
	private: System::Windows::Forms::TextBox^  tb_SaveFileLocation;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeAxesWFToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearChartWFToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  resetCOMPortWFToolStripMenuItem;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBox2;

	private: bool wfCap_run;

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
			this->ch_DisplayWaveforms = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tb_trigger_threshold = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->bChangeThreshold = (gcnew System::Windows::Forms::Button());
			this->bCaptureWFs = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->b_closeWFwindow = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->chk_stf = (gcnew System::Windows::Forms::CheckBox());
			this->tb_saveFile = (gcnew System::Windows::Forms::Button());
			this->tb_SaveFileLocation = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAxesWFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearChartWFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetCOMPortWFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_DisplayWaveforms))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// ch_DisplayWaveforms
			// 
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->MajorTickMark->IntervalOffset = 0;
			chartArea1->AxisX->Maximum = 10;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"Time (us)";
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->Maximum = 2500;
			chartArea1->AxisY->Minimum = 1900;
			chartArea1->AxisY->Title = L"ADC Counts";
			chartArea1->Name = L"ChartArea1";
			this->ch_DisplayWaveforms->ChartAreas->Add(chartArea1);
			this->ch_DisplayWaveforms->Location = System::Drawing::Point(12, 39);
			this->ch_DisplayWaveforms->Name = L"ch_DisplayWaveforms";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series1->MarkerSize = 3;
			series1->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series1->Name = L"Series1";
			this->ch_DisplayWaveforms->Series->Add(series1);
			this->ch_DisplayWaveforms->Size = System::Drawing::Size(719, 513);
			this->ch_DisplayWaveforms->TabIndex = 1;
			this->ch_DisplayWaveforms->Text = L"chart1";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(737, 39);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(53, 13);
			this->label6->TabIndex = 44;
			this->label6->Text = L"COM Port";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(737, 275);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(90, 13);
			this->label5->TabIndex = 43;
			this->label5->Text = L"Trigger Threshold";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tb_trigger_threshold
			// 
			this->tb_trigger_threshold->Location = System::Drawing::Point(833, 272);
			this->tb_trigger_threshold->Name = L"tb_trigger_threshold";
			this->tb_trigger_threshold->Size = System::Drawing::Size(110, 20);
			this->tb_trigger_threshold->TabIndex = 38;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(743, 382);
			this->textBox6->Name = L"textBox6";
			this->textBox6->ReadOnly = true;
			this->textBox6->Size = System::Drawing::Size(200, 20);
			this->textBox6->TabIndex = 32;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(805, 36);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(139, 21);
			this->comboBox1->TabIndex = 31;
			// 
			// bChangeThreshold
			// 
			this->bChangeThreshold->Location = System::Drawing::Point(743, 298);
			this->bChangeThreshold->Name = L"bChangeThreshold";
			this->bChangeThreshold->Size = System::Drawing::Size(200, 49);
			this->bChangeThreshold->TabIndex = 30;
			this->bChangeThreshold->Text = L"Change Trigger Threshold";
			this->bChangeThreshold->UseVisualStyleBackColor = true;
			this->bChangeThreshold->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::bChangeThreshold_Click);
			// 
			// bCaptureWFs
			// 
			this->bCaptureWFs->Location = System::Drawing::Point(743, 408);
			this->bCaptureWFs->Name = L"bCaptureWFs";
			this->bCaptureWFs->Size = System::Drawing::Size(200, 49);
			this->bCaptureWFs->TabIndex = 28;
			this->bCaptureWFs->Text = L"Capture Waveforms";
			this->bCaptureWFs->UseVisualStyleBackColor = true;
			this->bCaptureWFs->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::bCaptureWFs_Click);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 115200;
			// 
			// b_closeWFwindow
			// 
			this->b_closeWFwindow->Location = System::Drawing::Point(740, 503);
			this->b_closeWFwindow->Name = L"b_closeWFwindow";
			this->b_closeWFwindow->Size = System::Drawing::Size(204, 49);
			this->b_closeWFwindow->TabIndex = 45;
			this->b_closeWFwindow->Text = L"Close Window";
			this->b_closeWFwindow->UseVisualStyleBackColor = true;
			this->b_closeWFwindow->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::b_closeWFwindow_Click);
			// 
			// label7
			// 
			this->label7->Location = System::Drawing::Point(737, 470);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(206, 30);
			this->label7->TabIndex = 46;
			this->label7->Text = L"Stop capturing data before closing this window.";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// chk_stf
			// 
			this->chk_stf->AutoSize = true;
			this->chk_stf->Location = System::Drawing::Point(781, 359);
			this->chk_stf->Name = L"chk_stf";
			this->chk_stf->Size = System::Drawing::Size(106, 17);
			this->chk_stf->TabIndex = 47;
			this->chk_stf->Text = L"Save WF To File";
			this->chk_stf->UseVisualStyleBackColor = true;
			// 
			// tb_saveFile
			// 
			this->tb_saveFile->Location = System::Drawing::Point(12, 559);
			this->tb_saveFile->Name = L"tb_saveFile";
			this->tb_saveFile->Size = System::Drawing::Size(107, 41);
			this->tb_saveFile->TabIndex = 49;
			this->tb_saveFile->Text = L"Choose Save File...";
			this->tb_saveFile->UseVisualStyleBackColor = true;
			this->tb_saveFile->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::tb_saveFile_Click);
			// 
			// tb_SaveFileLocation
			// 
			this->tb_SaveFileLocation->Location = System::Drawing::Point(125, 575);
			this->tb_SaveFileLocation->Name = L"tb_SaveFileLocation";
			this->tb_SaveFileLocation->ReadOnly = true;
			this->tb_SaveFileLocation->Size = System::Drawing::Size(611, 20);
			this->tb_SaveFileLocation->TabIndex = 50;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(125, 559);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(98, 13);
			this->label8->TabIndex = 51;
			this->label8->Text = L"Save File Location:";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(956, 24);
			this->menuStrip1->TabIndex = 52;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->changeAxesWFToolStripMenuItem,
					this->clearChartWFToolStripMenuItem, this->resetCOMPortWFToolStripMenuItem
			});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// changeAxesWFToolStripMenuItem
			// 
			this->changeAxesWFToolStripMenuItem->Name = L"changeAxesWFToolStripMenuItem";
			this->changeAxesWFToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->changeAxesWFToolStripMenuItem->Text = L"Change Axes";
			this->changeAxesWFToolStripMenuItem->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::changeAxesWFToolStripMenuItem_Click);
			// 
			// clearChartWFToolStripMenuItem
			// 
			this->clearChartWFToolStripMenuItem->Name = L"clearChartWFToolStripMenuItem";
			this->clearChartWFToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->clearChartWFToolStripMenuItem->Text = L"Clear Chart";
			this->clearChartWFToolStripMenuItem->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::clearChartWFToolStripMenuItem_Click);
			// 
			// resetCOMPortWFToolStripMenuItem
			// 
			this->resetCOMPortWFToolStripMenuItem->Name = L"resetCOMPortWFToolStripMenuItem";
			this->resetCOMPortWFToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->resetCOMPortWFToolStripMenuItem->Text = L"Reset COM Port";
			this->resetCOMPortWFToolStripMenuItem->Click += gcnew System::EventHandler(this, &captureWaveformsPopup::resetCOMPortWFToolStripMenuItem_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(740, 93);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 53;
			this->label1->Text = L"Select a WF type:";
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Adjacent Average", L"Low Pass Filter", L"Differential Filter",
					L"Trigger"
			});
			this->comboBox2->Location = System::Drawing::Point(805, 110);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(138, 21);
			this->comboBox2->TabIndex = 54;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &captureWaveformsPopup::comboBox2_SelectedIndexChanged);
			// 
			// captureWaveformsPopup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(956, 612);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->tb_SaveFileLocation);
			this->Controls->Add(this->tb_saveFile);
			this->Controls->Add(this->chk_stf);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->b_closeWFwindow);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tb_trigger_threshold);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->bChangeThreshold);
			this->Controls->Add(this->bCaptureWFs);
			this->Controls->Add(this->ch_DisplayWaveforms);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"captureWaveformsPopup";
			this->Text = L"Capture Waveform Data";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ch_DisplayWaveforms))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		
private: void findPorts(void)
{
	array<Object^>^ objectArray = SerialPort::GetPortNames();
	this->comboBox1->Items->AddRange(objectArray);
}

private: System::Void bChangeThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
	/* This button click will allow the user to change the trigger threshold of the system over the serial port */
	String^ retMessage = "";	//allows for testing
	String^ thresholdMessage = this->tb_trigger_threshold->Text;

	/* Open the serial port then */
	if (this->comboBox1->Text == String::Empty) {
		this->textBox6->Text = "Select a port above.";
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen) {
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
			this->bChangeThreshold->Enabled = false;
		}
		else {
			this->textBox6->Text = (this->comboBox1->Text) + " is already open.";
			this->bChangeThreshold->Enabled = false;
			Application::DoEvents();
		}
	}

	/* Send commands to the uZ over the serial connection */
	this->serialPort1->WriteLine("3");				//choose change threshold from main menu
	Sleep(500);		//read the line that ask for the new threshold
	this->serialPort1->WriteLine(thresholdMessage);	//write the threshold specified by the user
	Sleep(1200);

	this->serialPort1->DiscardInBuffer();

	/* Clean up */
	this->textBox6->Text = "Trigger threshold has been set.";
	this->bChangeThreshold->Enabled = true;
}//eochangeThreshold

private: System::Void bCaptureWFs_Click(System::Object^  sender, System::EventArgs^  e) {
	/* This button click will send commands, over the serial port, to the uZ board and the devkit code running on the FPGA
	* to choose waveform data, enable the system, and send the data */
	String^ retMessage = "";


	wfCap_run = !wfCap_run;		//init'd as false
	if (wfCap_run)
	{
		this->bCaptureWFs->Text = "Stop Capture";
	}
	if (!wfCap_run)	//stop capturing data
	{
		this->bCaptureWFs->Text = "Capture Waveforms";
		this->textBox6->Text = "Stop button pressed.";
		backgroundWorker1->CancelAsync();
		Application::DoEvents();
		return;
	}

	//Need to handle initializing a serial port
	if (this->comboBox1->Text == String::Empty)
	{
		this->textBox6->Text = "Select a port above.";
		this->bCaptureWFs->Text = "Capture Waveforms";
		wfCap_run = !wfCap_run;
		return;
	}
	else
	{
		if (!this->serialPort1->IsOpen)	//If the port is not open, open it
		{
			this->serialPort1->PortName = this->comboBox1->Text;
			this->serialPort1->Open();
		}
		else //if the port is open, 
		{
			this->textBox6->Text = (this->comboBox1->Text) + " connected.";
			Application::DoEvents();
		}
	}

	// Make sure the user has selected a type of WF
	// This tells us what mode to select in the uZ
	// Just make the default be AA WFs
	if (this->comboBox2->SelectedIndex < 0)
		this->comboBox2->SelectedIndex = 0;

	std::ofstream outputFileWF;
	if (wfCap_run && chk_stf->Checked)
	{
		if (this->tb_SaveFileLocation->Text == String::Empty)
		{
			this->textBox6->Text = "Please choose a file save location.";
			this->bCaptureWFs->Text = "Capture Waveforms";
			wfCap_run = !wfCap_run;
			return;
		}

		/* get the filename */
		std::string str_fileNamewf;
		String^ s_fileNamewf = this->saveFileDialog1->FileName;
		str_fileNamewf = msclr::interop::marshal_as<std::string>(s_fileNamewf);

		outputFileWF.open(str_fileNamewf, std::ios::app);

		if (!outputFileWF)	//if we can't open the file
		{
			this->textBox6->Text = "Could not access the specified file.";
			this->bCaptureWFs->Text = "Capture Waveforms";
			wfCap_run = !wfCap_run;
			return;
		}

	}

	//Next, need to send commands over the port to the uZ board
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->WriteLine("0");	//change mode at the main menu
		Sleep(1000);
		
		switch (this->comboBox2->SelectedIndex)
		{
		case 0:
			this->serialPort1->WriteLine("0");
			break;
		case 1:
			this->serialPort1->WriteLine("1");
			break;
		case 2:
			this->serialPort1->WriteLine("2");
			break;
		case 3:
			this->serialPort1->WriteLine("3");
			break;
		default:
			this->serialPort1->WriteLine("0");
			this->textBox6->Text = "Automatically chose AA WFs.";
			break;
		}
		Sleep(1000);
		this->serialPort1->WriteLine("6");	//select case 6 from main menu
	}
	else
	{
		this->textBox6->Text = "Port is not open.";
		this->bCaptureWFs->Text = "Capture Waveforms";
		wfCap_run = !wfCap_run;
		Application::DoEvents();
		return;
	}

	//set variables
	int loops = 0;
	int index = 0;
	double wfTimeBins = 0.0;
	const int wfBins = 4096;	
	int wfArray[wfBins]{  };	//Just guess 4096 wf ints will be sent; init array to 0's
	int numWaveforms = 0;

	//Set up the chart
	this->ch_DisplayWaveforms->Series["Series1"]->Points->Clear();

	while (wfCap_run)
	{
		/* Try and read in the data from the serial port */
		try
		{
			Int32::TryParse(this->serialPort1->ReadLine(), wfArray[index]);
			index++;
			wfTimeBins += 4.0 / 1000.0;
		}
		/* If it times out, catch that and close the connection */
		catch (const TimeoutException^)
		{
			this->serialPort1->Close();
			this->textBox6->Text = "Connection closed due to timeout.";
			this->bCaptureWFs->Text = "Capture Waveforms";
			wfCap_run = !wfCap_run;
			return;
		}

		/* If we have data, plot it on the chart */
		if (index <= 2500)
		{
			this->ch_DisplayWaveforms->Series["Series1"]->Points->AddXY(wfTimeBins, (wfArray[index] / 16));
			if (index % 100 == 0)
				Application::DoEvents();
		}

		if (index > wfBins-1)	//reset variables to allow us to re-use our array
		{
			index = 0;
			wfTimeBins = 0.0;
			this->ch_DisplayWaveforms->Series["Series1"]->Points->Clear();
			++numWaveforms;
			this->textBox6->Text = numWaveforms + " waveforms plotted.";
			
			//save the WF in the file specified by the user, if they want one
			for (index = 0; index < wfBins; index++){
				outputFileWF << wfArray[index] / 16 << std::endl;
			}
			outputFileWF << "000" << std::endl;
			index = 0;
		}
	}

	this->serialPort1->WriteLine("q\r");	//quit the data stream
	Sleep(1000);

	this->serialPort1->DiscardInBuffer();	//just get rid of the buffer because we can't keep up and don't want it
	if (outputFileWF.is_open())
	{
		outputFileWF.close();
	}

	this->textBox6->Text = "Capture finished. Chart not erased.";
	return;
}//eocaptureWF_click

private: System::Void b_closeWFwindow_Click(System::Object^  sender, System::EventArgs^  e) {
	/* To move between screens, need to close ports */
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->Close();
	}
	this->Hide();
}

private: System::Void tb_saveFile_Click(System::Object^  sender, System::EventArgs^  e) {
	/* create instance of a save file dialog */
	saveFileDialog1->ShowDialog();
	tb_SaveFileLocation->Text = saveFileDialog1->FileName;
}//eosavefileclick

private: System::Void changeAxesWFToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	double xMin;
	double xMax;
	double yMin;
	double yMax;

	xMin = this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Minimum;
	xMax = this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Maximum;
	yMin = this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Minimum;
	yMax = this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Maximum;

	/* Show the change axes pop up */
	changeAxesPopUp ^ changeWFAxes = gcnew changeAxesPopUp(xMin, xMax, yMin, yMax);
	//Application::Run(changePSDAxes);
	changeWFAxes->ShowDialog();

	this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Minimum = changeWFAxes->getxMin();
	this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Maximum = changeWFAxes->getxMax();
	this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Minimum = changeWFAxes->getyMin();
	this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Maximum = changeWFAxes->getyMax();

}
private: System::Void clearChartWFToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->ch_DisplayWaveforms->Series["Series1"]->Points->Clear();
	this->textBox6->Text = "Waveform chart cleared.";
	Application::DoEvents();
}

private: System::Void resetCOMPortWFToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/* scan for com ports again, fill the combobox */
	this->textBox6->Text = "Closing any open ports...";
	if (this->serialPort1->IsOpen)
	{
		this->serialPort1->Close();
		this->textBox6->Text = "Port closed.";
	}

	this->comboBox1->Items->Clear();
	findPorts();

	this->textBox6->Text = "Please re-select a port.";
	return;
}
private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	//change the axes depending on what index is selected in the combo box
	//Indices:
	//
	//1: AA - x: 0-10, y: 1900-2300
	//2: LPF- x: 0-10, y: 50 - 200 ???
	//3: DFF- x: 0-10, y: 400 - 1000
	//4: Trg- x: 0-10, y: 400 - 1000

	if (this->comboBox2->SelectedIndex == 0)	//AA Waveforms
	{
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Minimum = 0;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Maximum = 10;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Minimum = 1900;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Maximum = 2300;
	}
	else if (this->comboBox2->SelectedIndex == 1)	//LPF Waveforms
	{
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Minimum = 0;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Maximum = 10;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Minimum = 50;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Maximum = 200;
	}
	else if (this->comboBox2->SelectedIndex == 2)	//DFF Waveforms
	{
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Minimum = 0;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Maximum = 10;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Minimum = 400;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Maximum = 1000;
	}
	else if (this->comboBox2->SelectedIndex == 3)	//Trigger Waveforms
	{
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Minimum = 0;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisX->Maximum = 10;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Minimum = 400;
		this->ch_DisplayWaveforms->ChartAreas[0]->AxisY->Maximum = 1000;
	}
	else
	{
		this->comboBox2->SelectedIndex = 0;
	}
}

};
}
