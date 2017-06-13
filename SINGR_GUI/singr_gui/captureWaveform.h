#pragma once

#include "clientExample.h"
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "changeAxesPopUp.h"

namespace singr_gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;
	using namespace System::IO::Ports;
	using namespace std;
	
	/// <summary>
	/// Summary for captureWaveform
	/// </summary>
	public ref class captureWaveform : public System::Windows::Forms::Form
	{
	public:
		captureWaveform(void)
		{
			InitializeComponent();
			wfCapRun = false;
			backgroundWorker1->RunWorkerAsync();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~captureWaveform()
		{
			if (components)
			{
				delete components;
			}
		}

	private: bool wfCapRun;
	private: System::Windows::Forms::Form^ Form1;

	private: System::Windows::Forms::Button^  bExit;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartCapWF;

	private: System::Windows::Forms::Button^  bCapWF;
	private: System::Windows::Forms::TextBox^  tbCapWF;







	private: System::Windows::Forms::TextBox^  tb_SetThreshold;
	private: System::Windows::Forms::Button^  b_setThreshold;












	private: System::Windows::Forms::Button^  b_SaveFile;
	private: System::Windows::Forms::TextBox^  tb_SaveFileLocation;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ComboBox^  cb_WFType;
	private: System::Windows::Forms::Button^  button1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::TextBox^  tb_counterBox;





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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->bExit = (gcnew System::Windows::Forms::Button());
			this->chartCapWF = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->bCapWF = (gcnew System::Windows::Forms::Button());
			this->tbCapWF = (gcnew System::Windows::Forms::TextBox());
			this->tb_SetThreshold = (gcnew System::Windows::Forms::TextBox());
			this->b_setThreshold = (gcnew System::Windows::Forms::Button());
			this->b_SaveFile = (gcnew System::Windows::Forms::Button());
			this->tb_SaveFileLocation = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->cb_WFType = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tb_counterBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartCapWF))->BeginInit();
			this->SuspendLayout();
			// 
			// bExit
			// 
			this->bExit->Location = System::Drawing::Point(899, 496);
			this->bExit->Name = L"bExit";
			this->bExit->Size = System::Drawing::Size(92, 23);
			this->bExit->TabIndex = 0;
			this->bExit->Text = L"Return to Tool";
			this->bExit->UseVisualStyleBackColor = true;
			this->bExit->Click += gcnew System::EventHandler(this, &captureWaveform::bExit_Click);
			// 
			// chartCapWF
			// 
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->Maximum = 4;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"Time (us)";
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->Maximum = 2800;
			chartArea1->AxisY->Minimum = 1900;
			chartArea1->AxisY->Title = L"ADC Counts";
			chartArea1->Name = L"ChartArea1";
			this->chartCapWF->ChartAreas->Add(chartArea1);
			this->chartCapWF->Location = System::Drawing::Point(12, 12);
			this->chartCapWF->Name = L"chartCapWF";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Name = L"Series1";
			this->chartCapWF->Series->Add(series1);
			this->chartCapWF->Size = System::Drawing::Size(795, 480);
			this->chartCapWF->TabIndex = 1;
			this->chartCapWF->Text = L"chartCapWF";
			// 
			// bCapWF
			// 
			this->bCapWF->Location = System::Drawing::Point(813, 244);
			this->bCapWF->Name = L"bCapWF";
			this->bCapWF->Size = System::Drawing::Size(178, 34);
			this->bCapWF->TabIndex = 2;
			this->bCapWF->Text = L"Capture Waveform";
			this->bCapWF->UseVisualStyleBackColor = true;
			this->bCapWF->Click += gcnew System::EventHandler(this, &captureWaveform::bCapWF_Click);
			// 
			// tbCapWF
			// 
			this->tbCapWF->Location = System::Drawing::Point(813, 218);
			this->tbCapWF->Name = L"tbCapWF";
			this->tbCapWF->Size = System::Drawing::Size(177, 20);
			this->tbCapWF->TabIndex = 3;
			// 
			// tb_SetThreshold
			// 
			this->tb_SetThreshold->Location = System::Drawing::Point(813, 133);
			this->tb_SetThreshold->Name = L"tb_SetThreshold";
			this->tb_SetThreshold->Size = System::Drawing::Size(178, 20);
			this->tb_SetThreshold->TabIndex = 6;
			// 
			// b_setThreshold
			// 
			this->b_setThreshold->Location = System::Drawing::Point(813, 159);
			this->b_setThreshold->Name = L"b_setThreshold";
			this->b_setThreshold->Size = System::Drawing::Size(178, 38);
			this->b_setThreshold->TabIndex = 7;
			this->b_setThreshold->Text = L"Set Trigger Threshold";
			this->b_setThreshold->UseVisualStyleBackColor = true;
			this->b_setThreshold->Click += gcnew System::EventHandler(this, &captureWaveform::b_setThreshold_Click);
			// 
			// b_SaveFile
			// 
			this->b_SaveFile->Location = System::Drawing::Point(813, 381);
			this->b_SaveFile->Name = L"b_SaveFile";
			this->b_SaveFile->Size = System::Drawing::Size(177, 41);
			this->b_SaveFile->TabIndex = 19;
			this->b_SaveFile->Text = L"Choose Save File...";
			this->b_SaveFile->UseVisualStyleBackColor = true;
			this->b_SaveFile->Click += gcnew System::EventHandler(this, &captureWaveform::b_SaveFile_Click);
			// 
			// tb_SaveFileLocation
			// 
			this->tb_SaveFileLocation->Location = System::Drawing::Point(137, 498);
			this->tb_SaveFileLocation->Name = L"tb_SaveFileLocation";
			this->tb_SaveFileLocation->ReadOnly = true;
			this->tb_SaveFileLocation->Size = System::Drawing::Size(670, 20);
			this->tb_SaveFileLocation->TabIndex = 20;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 501);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(98, 13);
			this->label6->TabIndex = 21;
			this->label6->Text = L"Save File Location:";
			// 
			// cb_WFType
			// 
			this->cb_WFType->FormattingEnabled = true;
			this->cb_WFType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Adjacent Average", L"Low-Pass Filter", L"Differential Filter", 
				L"Trigger"});
			this->cb_WFType->Location = System::Drawing::Point(813, 41);
			this->cb_WFType->Name = L"cb_WFType";
			this->cb_WFType->Size = System::Drawing::Size(177, 21);
			this->cb_WFType->TabIndex = 22;
			this->cb_WFType->Text = L"Waveform Type";
			this->cb_WFType->SelectedIndexChanged += gcnew System::EventHandler(this, &captureWaveform::cb_WFType_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(813, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(177, 23);
			this->button1->TabIndex = 23;
			this->button1->Text = L"Change Axes";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &captureWaveform::button1_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &captureWaveform::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &captureWaveform::backgroundWorker1_ProgressChanged);
			// 
			// tb_counterBox
			// 
			this->tb_counterBox->Location = System::Drawing::Point(969, 284);
			this->tb_counterBox->Name = L"tb_counterBox";
			this->tb_counterBox->ReadOnly = true;
			this->tb_counterBox->Size = System::Drawing::Size(21, 20);
			this->tb_counterBox->TabIndex = 24;
			// 
			// captureWaveform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(999, 528);
			this->Controls->Add(this->tb_counterBox);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->cb_WFType);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->tb_SaveFileLocation);
			this->Controls->Add(this->b_SaveFile);
			this->Controls->Add(this->b_setThreshold);
			this->Controls->Add(this->tb_SetThreshold);
			this->Controls->Add(this->tbCapWF);
			this->Controls->Add(this->bCapWF);
			this->Controls->Add(this->chartCapWF);
			this->Controls->Add(this->bExit);
			this->Name = L"captureWaveform";
			this->Text = L"captureWaveform";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartCapWF))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void bExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Hide();
				 //Form1->Show();
			 }
private: System::Void bCapWF_Click(System::Object^  sender, System::EventArgs^  e) {
			  /* Send commands to the uZ board to send waveforms according to settings displayed */
			 /* Run Variable */
			 wfCapRun = !wfCapRun;
			 if(wfCapRun == false)
			 {
				 /* need this to send a "quit" command to the devkit...when that is an option */
				 this->tbCapWF->Text = "Stopping WF collection.";
				 return;
			 }

			 /* Variables */
			 int retVal(0);
			 int numBytes(0);
			 int stopVal(0);

			 double * wfTime(nullptr);
			 wfTime = new double[12300]();
			 int * wfBuff(nullptr);
			 wfBuff = new int[12300]();

			 /* Get the waveform type from the combobox */
			 const char * modeType = "";
			 int selectedIndex = cb_WFType->SelectedIndex;	//AA = 0, LPF = 1, DFF = 2, TRG = 3
			 switch(selectedIndex)
			 {
			 case 0:
				 modeType = "0";
				 break;
			 case 1:
				 modeType = "1";
				 break;
			 case 2:
				 modeType = "2";
				 break;
			 case 3:
				 modeType = "3";
				 break;
			 default:
				 this->tbCapWF->Text = "Please choose a WF type.";
				 wfCapRun = !wfCapRun;
				 return;
			 }

			  /* get the filename from the textbox */
			 if(this->tb_SaveFileLocation->Text == String::Empty)	//if there is no filename in the textbox
			 {
				 this->tbCapWF->Text = "Please select a save file location.";	//alert the user they need one
				 wfCapRun = !wfCapRun;
				 return;
			 }
			 String^ saveFileName = this->tb_SaveFileLocation->Text;	//this is a managed string
			 marshal_context^ context = gcnew marshal_context();
			 const char * fileName = context->marshal_as<const char*>(saveFileName);

			 Client getWaveForm("172.30.0.10");

			 if ( !getWaveForm.Start()) {
				 this->tbCapWF->Text = "Client start failed";
				 Application::DoEvents();
				 wfCapRun = !wfCapRun;
				 return;
			 }

			 /* Set up the transaction */
			 const char * chooseMode = "0";
			 const char * enableSystem = "1";
			 const char * beginTransfer = "9";

			 getWaveForm.Send(chooseMode);		//send "0"
			 Sleep(1000);
			 getWaveForm.Send(modeType);		//send "x" where x = waveform type or processed data
			 Sleep(1000);
			 getWaveForm.Send(enableSystem);
			 Sleep(1000);
			 getWaveForm.Send(beginTransfer);
			 Sleep(2000);

			 while(wfCapRun)	//while(true)
			 {
				 /* Clear the chart to show new points */
				 this->chartCapWF->Series["Series1"]->Points->Clear();

				 /* Send a char to the board to receive a buffer of data */
				 const char * sendByte = "a";
				 getWaveForm.Send(sendByte);

				 /* Pass in a pointer to a buffer and an int to get back the number of bytes written to the buffer */
				 retVal = getWaveForm.Recv(wfBuff);	// retVal gives the number of ints that were written to the buffer
				 this->tbCapWF->Text = retVal + " bytes received.";
				 if ( retVal < 10 ) 
				 {
					 this->tbCapWF->Text = "No wf data received.";

					 if(stopVal >=10)
					 {
						 this->tbCapWF->Text = "No wf data after 10 attempts to receive.";
						 return;
					 }
					 ++stopVal;
					 continue;	//if no data received, start over and send another char
				 }
				 stopVal = 0;	//If we get past the 'no data' check, reset stop value
			
				 /* Create a set of times at 4 ns spacing to plot the wf values against */
				 for( int ii(0.0); ii < retVal; ++ii) {
					 wfTime[ii] = (double)ii * (4.0 / 1000.0);	// Each wf data point is 4 ns apart
				 }

				 /* Plot the points in the chart */
				 for (int jj(1); jj < retVal - 2; ++jj)
				 {
					 this->chartCapWF->Series["Series1"]->Points->AddXY(wfTime[jj], (wfBuff[jj]));
				 }

				 ofstream output_file_wf;
				 output_file_wf.open(fileName,ios::app);
				 if ( !output_file_wf.is_open() )
				 {
					 this->tbCapWF->Text = "One waveform displayed, no file saved.";
				 }

 				 output_file_wf << "ffffff" << endl;

				 //write all our data to the file above
				 for(int i = 0; i < retVal - 2; i++)
				 {
					 output_file_wf << wfBuff[i] << endl;
				 }

				 Application::DoEvents();
				 //break;
			 }	//End of plot wf while loop

			 /* Tell the system to quit */
			 const char * quit = "q";
			 getWaveForm.Send(quit);		//send "q"

			 /* Disconnect from the client class and clean up our work */
			 getWaveForm.Stop();
			 //this->tbCapWF->Text = "One waveform displayed.";
			 delete [] wfTime;
			 wfTime = nullptr;
			 delete [] wfBuff;
			 wfBuff = nullptr;
			 return; 		 
		 }	// end of bCapWF click

private: System::Void b_setThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Declare variables */
			 std::string retMessage = "";
			 std::string chooseMode = "3";
			 const char * strThreshold = "";

			 marshal_context^ context = gcnew marshal_context();
			 String^ threshold = this->tb_SetThreshold->Text;
			 strThreshold = context->marshal_as<const char*>( threshold );

			 /* Open a client class connection to be able to send data over ethernet */
			 Client setThreshold("172.30.0.10");
			 if ( !setThreshold.Start() ) {
				 delete context;
				 this->tbCapWF->Text = "Client start failed.";
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
			 this->tbCapWF->Text = "Threshold changed.";
			 Application::DoEvents();		
			 return;
		 }

private: System::Void b_SaveFile_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::DialogResult result = saveFileDialog1->ShowDialog();
			 
			 if (result == System::Windows::Forms::DialogResult::OK)
			 {
					this->tb_SaveFileLocation->Text = saveFileDialog1->FileName;
			 }
			 if (result == System::Windows::Forms::DialogResult::Cancel)
			 {
				 return;
			 }
		 }
private: System::Void cb_WFType_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 //when the user chooses one of the options in the drop down menu, this function will trigger and resize the chart 
			 this->chartCapWF->Series["Series1"]->Points->Clear();

			 /* Get the waveform type from the combobox */
			 const char * modeType = "";
			 int selectedIndex = cb_WFType->SelectedIndex;	//AA = 0, LPF = 1, DFF = 2, TRG = 3

			 //now we know what the user has chosen, use that information to change the axes for the chart
			 
			 switch(selectedIndex)
			 {
			 case 0:	//AA waveforms
				 this->chartCapWF->ChartAreas[0]->AxisX->Minimum = 0;
				 this->chartCapWF->ChartAreas[0]->AxisX->Maximum = 4;
				 this->chartCapWF->ChartAreas[0]->AxisY->Minimum = 1900;
				 this->chartCapWF->ChartAreas[0]->AxisY->Maximum = 2800;
				 break;
			 case 1:	//LPF waveforms
				 this->chartCapWF->ChartAreas[0]->AxisX->Minimum = 0;
				 this->chartCapWF->ChartAreas[0]->AxisX->Maximum = 4;
				 this->chartCapWF->ChartAreas[0]->AxisY->Minimum = 1400;
				 this->chartCapWF->ChartAreas[0]->AxisY->Maximum = 2000;
				 break;
			 case 2:	//DFF waveforms
				 this->chartCapWF->ChartAreas[0]->AxisX->Minimum = 0;
				 this->chartCapWF->ChartAreas[0]->AxisX->Maximum = 4;
				 this->chartCapWF->ChartAreas[0]->AxisY->Minimum = 8000;
				 this->chartCapWF->ChartAreas[0]->AxisY->Maximum = 9000;
				 break;
			 case 3:	//TRG waveforms
				 this->chartCapWF->ChartAreas[0]->AxisX->Minimum = 0;
				 this->chartCapWF->ChartAreas[0]->AxisX->Maximum = 4;
				 this->chartCapWF->ChartAreas[0]->AxisY->Minimum = 8000;
				 this->chartCapWF->ChartAreas[0]->AxisY->Maximum = 9000;
				 break;
			 default:
				 this->tbCapWF->Text = "Error setting axes defaults.";
				 return;
			 }
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* Open small pop-up window which takes in values for axes and passes them back to adjust axis size */
			 double xMin;
			 double xMax;
			 double yMin;
			 double yMax;

			 xMin = this->chartCapWF->ChartAreas[0]->AxisX->Minimum;
			 xMax = this->chartCapWF->ChartAreas[0]->AxisX->Maximum;
			 yMin = this->chartCapWF->ChartAreas[0]->AxisY->Minimum;
			 yMax = this->chartCapWF->ChartAreas[0]->AxisY->Maximum;
		 
			 /* Show the pop-up window */
			 changeAxesPopUp ^ changeWFAxes = gcnew changeAxesPopUp( xMin, xMax, yMin, yMax);
			 changeWFAxes->ShowDialog();

			 this->chartCapWF->ChartAreas[0]->AxisX->Minimum = changeWFAxes->getxMin();
			 this->chartCapWF->ChartAreas[0]->AxisX->Maximum = changeWFAxes->getxMax();
			 this->chartCapWF->ChartAreas[0]->AxisY->Minimum = changeWFAxes->getyMin();
			 this->chartCapWF->ChartAreas[0]->AxisY->Maximum = changeWFAxes->getyMax();
		 }
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
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
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
			 this->tb_counterBox->Text = e->ProgressPercentage + " ";
		 }
};//public ref class
}//namespace
