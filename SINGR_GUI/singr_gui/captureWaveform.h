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

		
	private: System::Windows::Forms::Form^ Form1;

	private: System::Windows::Forms::Button^  bExit;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartCapWF;

	private: System::Windows::Forms::Button^  bCapWF;
	private: System::Windows::Forms::TextBox^  tbCapWF;
	private: System::Windows::Forms::GroupBox^  gb_WFType;


	private: System::Windows::Forms::RadioButton^  rb_DFFWF;
	private: System::Windows::Forms::RadioButton^  rb_LPFWF;
	private: System::Windows::Forms::RadioButton^  rb_AAWF;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  tb_SetThreshold;
	private: System::Windows::Forms::Button^  b_setThreshold;










	private: System::Windows::Forms::CheckBox^  chk_stf;
	private: System::Windows::Forms::CheckBox^  chk_atf;
	private: System::Windows::Forms::Button^  b_SaveFile;
	private: System::Windows::Forms::TextBox^  tb_SaveFileLocation;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;



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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->bExit = (gcnew System::Windows::Forms::Button());
			this->chartCapWF = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->bCapWF = (gcnew System::Windows::Forms::Button());
			this->tbCapWF = (gcnew System::Windows::Forms::TextBox());
			this->gb_WFType = (gcnew System::Windows::Forms::GroupBox());
			this->rb_DFFWF = (gcnew System::Windows::Forms::RadioButton());
			this->rb_LPFWF = (gcnew System::Windows::Forms::RadioButton());
			this->rb_AAWF = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tb_SetThreshold = (gcnew System::Windows::Forms::TextBox());
			this->b_setThreshold = (gcnew System::Windows::Forms::Button());
			this->chk_stf = (gcnew System::Windows::Forms::CheckBox());
			this->chk_atf = (gcnew System::Windows::Forms::CheckBox());
			this->b_SaveFile = (gcnew System::Windows::Forms::Button());
			this->tb_SaveFileLocation = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartCapWF))->BeginInit();
			this->gb_WFType->SuspendLayout();
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
			chartArea2->AxisX->IsStartedFromZero = false;
			chartArea2->AxisX->Maximum = 4;
			chartArea2->AxisX->Minimum = 0;
			chartArea2->AxisX->Title = L"Time (us)";
			chartArea2->AxisY->IsStartedFromZero = false;
			chartArea2->AxisY->Maximum = 2800;
			chartArea2->AxisY->Minimum = 1900;
			chartArea2->AxisY->Title = L"ADC Counts";
			chartArea2->Name = L"ChartArea1";
			this->chartCapWF->ChartAreas->Add(chartArea2);
			this->chartCapWF->Location = System::Drawing::Point(12, 12);
			this->chartCapWF->Name = L"chartCapWF";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Name = L"Series1";
			this->chartCapWF->Series->Add(series2);
			this->chartCapWF->Size = System::Drawing::Size(795, 480);
			this->chartCapWF->TabIndex = 1;
			this->chartCapWF->Text = L"chartCapWF";
			// 
			// bCapWF
			// 
			this->bCapWF->Location = System::Drawing::Point(813, 244);
			this->bCapWF->Name = L"bCapWF";
			this->bCapWF->Size = System::Drawing::Size(177, 34);
			this->bCapWF->TabIndex = 2;
			this->bCapWF->Text = L"Capture Waveform";
			this->bCapWF->UseVisualStyleBackColor = true;
			this->bCapWF->Click += gcnew System::EventHandler(this, &captureWaveform::bCapWF_Click);
			// 
			// tbCapWF
			// 
			this->tbCapWF->Location = System::Drawing::Point(813, 218);
			this->tbCapWF->Name = L"tbCapWF";
			this->tbCapWF->Size = System::Drawing::Size(179, 20);
			this->tbCapWF->TabIndex = 3;
			// 
			// gb_WFType
			// 
			this->gb_WFType->Controls->Add(this->rb_DFFWF);
			this->gb_WFType->Controls->Add(this->rb_LPFWF);
			this->gb_WFType->Controls->Add(this->rb_AAWF);
			this->gb_WFType->Location = System::Drawing::Point(813, 37);
			this->gb_WFType->Name = L"gb_WFType";
			this->gb_WFType->Size = System::Drawing::Size(119, 87);
			this->gb_WFType->TabIndex = 4;
			this->gb_WFType->TabStop = false;
			// 
			// rb_DFFWF
			// 
			this->rb_DFFWF->AutoSize = true;
			this->rb_DFFWF->Location = System::Drawing::Point(7, 58);
			this->rb_DFFWF->Name = L"rb_DFFWF";
			this->rb_DFFWF->Size = System::Drawing::Size(102, 17);
			this->rb_DFFWF->TabIndex = 2;
			this->rb_DFFWF->TabStop = true;
			this->rb_DFFWF->Text = L"DFF Waveforms";
			this->rb_DFFWF->UseVisualStyleBackColor = true;
			// 
			// rb_LPFWF
			// 
			this->rb_LPFWF->AutoSize = true;
			this->rb_LPFWF->Location = System::Drawing::Point(7, 34);
			this->rb_LPFWF->Name = L"rb_LPFWF";
			this->rb_LPFWF->Size = System::Drawing::Size(101, 17);
			this->rb_LPFWF->TabIndex = 1;
			this->rb_LPFWF->TabStop = true;
			this->rb_LPFWF->Text = L"LPF Waveforms";
			this->rb_LPFWF->UseVisualStyleBackColor = true;
			// 
			// rb_AAWF
			// 
			this->rb_AAWF->AutoSize = true;
			this->rb_AAWF->Location = System::Drawing::Point(7, 10);
			this->rb_AAWF->Name = L"rb_AAWF";
			this->rb_AAWF->Size = System::Drawing::Size(96, 17);
			this->rb_AAWF->TabIndex = 0;
			this->rb_AAWF->TabStop = true;
			this->rb_AAWF->Text = L"AA Waveforms";
			this->rb_AAWF->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(814, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(178, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Choose which waveforms to display:";
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
			this->b_setThreshold->Size = System::Drawing::Size(177, 38);
			this->b_setThreshold->TabIndex = 7;
			this->b_setThreshold->Text = L"Set Trigger Threshold";
			this->b_setThreshold->UseVisualStyleBackColor = true;
			this->b_setThreshold->Click += gcnew System::EventHandler(this, &captureWaveform::b_setThreshold_Click);
			// 
			// chk_stf
			// 
			this->chk_stf->AutoSize = true;
			this->chk_stf->Location = System::Drawing::Point(813, 428);
			this->chk_stf->Name = L"chk_stf";
			this->chk_stf->Size = System::Drawing::Size(107, 17);
			this->chk_stf->TabIndex = 17;
			this->chk_stf->Text = L"Save to New File";
			this->chk_stf->UseVisualStyleBackColor = true;
			// 
			// chk_atf
			// 
			this->chk_atf->AutoSize = true;
			this->chk_atf->Location = System::Drawing::Point(813, 451);
			this->chk_atf->Name = L"chk_atf";
			this->chk_atf->Size = System::Drawing::Size(94, 17);
			this->chk_atf->TabIndex = 18;
			this->chk_atf->Text = L"Append to File";
			this->chk_atf->UseVisualStyleBackColor = true;
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
			// captureWaveform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(999, 528);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->tb_SaveFileLocation);
			this->Controls->Add(this->b_SaveFile);
			this->Controls->Add(this->chk_atf);
			this->Controls->Add(this->chk_stf);
			this->Controls->Add(this->b_setThreshold);
			this->Controls->Add(this->tb_SetThreshold);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->gb_WFType);
			this->Controls->Add(this->tbCapWF);
			this->Controls->Add(this->bCapWF);
			this->Controls->Add(this->chartCapWF);
			this->Controls->Add(this->bExit);
			this->Name = L"captureWaveform";
			this->Text = L"captureWaveform";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartCapWF))->EndInit();
			this->gb_WFType->ResumeLayout(false);
			this->gb_WFType->PerformLayout();
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

			 /* Variables */
			 int retVal(0);
			 int numBytes(0);
			 int stopVal(0);

			 double * wfTime(nullptr);
			 wfTime = new double[12300]();
			 int * wfBuff(nullptr);
			 wfBuff = new int[12300]();

			 Client getWaveForm("172.30.0.10");

			 if ( !getWaveForm.Start()) {
				 this->tbCapWF->Text = "client start failed";
				 Application::DoEvents();
				 return;
			 }

			 /* get the filename from the textbox */
			 if(this->tb_SaveFileLocation->Text == String::Empty)	//if there is no filename in the textbox
			 {
				 this->tbCapWF->Text = "Please select a save file location.";	//alert the user they need one
				 //psdCapRun = !psdCapRun;
				 return;
			 }
			 String^ saveFileName = this->tb_SaveFileLocation->Text;	//this is a managed string
			 marshal_context^ context = gcnew marshal_context();
			 const char * fileName = context->marshal_as<const char*>(saveFileName);
			 

			 /* Set up the transaction */
			 const char * chooseMode = "0";
			 const char * enableSystem = "1";
			 const char * beginTransfer = "9";

			 getWaveForm.Send(chooseMode);
			 Sleep(1000);
			 getWaveForm.Send(chooseMode);	//get the type of wf that we want to display //for now just assume we want AA waveforms
			 Sleep(1000);
			 getWaveForm.Send(enableSystem);
			 Sleep(1000);
			 getWaveForm.Send(beginTransfer);
			 Sleep(2000);

			 while(true)	//not sure when to break out yet
			 {
				 /* Clear the chart to show new points */
				 this->chartCapWF->Series["Series1"]->Points->Clear();
				 //Application::DoEvents();

				 /* Send a char to the board to receive a buffer of data */
				 const char * sendByte = "a";
				 getWaveForm.Send(sendByte);
				 Sleep(2000);

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
					 this->chartCapWF->Series["Series1"]->Points->AddXY(wfTime[jj], (wfBuff[jj] / 16));
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
				 break;
			 }	//End of plot wf while loop

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

//private: System::Void b_SetIntegrals_Click(System::Object^  sender, System::EventArgs^  e) {	//We don't need to change the integrals for capturing WFs
//			 /* Declare variables */
//			 std::string chooseMode = "4";
//			 const char * strBaseline = "";
//			 const char * strShort = "";
//			 const char * strLong = "";
//			 const char * strFull = "";
//			 String^ baselineInt = this->tb_BaselineInt->Text;
//			 String^ shortInt = this->tb_ShortInt->Text;
//			 String^ longInt = this->tb_LongInt->Text;
// 			 String^ fullInt = this->tb_FullInt->Text;
//
//			 marshal_context^ context = gcnew marshal_context();
//			 strBaseline = context->marshal_as<const char*>( baselineInt );
//			 strShort = context->marshal_as<const char*>( shortInt );
//			 strLong = context->marshal_as<const char*>( longInt );
//			 strFull = context->marshal_as<const char*>( fullInt );
//
//			 /* Open a client class connection to be able to send data over ethernet */
//			 Client setInts("172.30.0.10");
//			 if ( !setInts.Start() ) {
//				 delete context;
//				 this->tbCapWF->Text = "Client start failed.";
//				 Application::DoEvents();
//				 return;
//			 }
//			 
//			 /* Send the mode selection, then the integration times over ethernet */
//			 setInts.Send((char*)chooseMode.c_str());	//Calls setIntegrationTimes(0) in the devkit
//			 Sleep(1000);
//			 setInts.Send(strBaseline);
//			 Sleep(500);
//			 setInts.Send(strShort);
//			 Sleep(500);
//			 setInts.Send(strLong);
//			 Sleep(500);
//			 setInts.Send(strFull);
//
//			 /* Cleanup */
//			 delete context;
//			 setInts.Stop();
//			 this->tbCapWF->Text = "Integration times set.";
//			 Application::DoEvents();
//			 return;
//		 }

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
};//public ref class
}//namespace
