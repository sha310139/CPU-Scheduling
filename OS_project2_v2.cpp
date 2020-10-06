
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
# include <fstream> 		// open, is_open, close, ignore

# define NOT !
# define AND &&
# define OR ||


using namespace std;


typedef struct processT {
	int PID;
	int CPU_BURST;
	int arrival_time;
	int priority;
	
	int remainTime;
	
	int waiting_Time;
	int turnaround_Time;
	bool done;
} processType ;


typedef struct resultT {
	string gantt_chart;
	vector<processT> processBuffer;
} resultType ;


bool Compare_CPU_BURST( const processType &p1, const processType &p2 );
bool Compare_arrival_time( const processType &p1, const processType &p2 );
bool Compare_priority( const processType &p1, const processType &p2 );
bool Compare_N_priority( const processType &p1, const processType &p2 );
bool Compare_arrival_timeL( const processType &p1, const processType &p2 );
bool Compare_arrival_time_PID( const processType &p1, const processType &p2 );


bool Compare_CPU_BURST( const processType &p1, const processType &p2 ){

	if ( p1.remainTime == p2.remainTime ) {
		if ( p1.done == p2.done ) {
			if ( p1.arrival_time == p2.arrival_time ) {
				return p1.PID < p2.PID;
			} // if
			else {
				return p1.arrival_time < p2.arrival_time;
			} // else
		} // if
		else {
			return p2.done;
		} // else
	} // if
	else {
		return p1.remainTime < p2.remainTime;
	} // else
	
} // Compare_CPU_BURST()

bool Compare_arrival_time( const processType &p1, const processType &p2 ){
	
	if ( p1.arrival_time == p2.arrival_time ) {
		return p1.PID < p2.PID;
	} // if
	else {
		return p1.arrival_time < p2.arrival_time;
	} // else
	
} // Compare_arrival_time()

bool Compare_arrival_time_PID( const processType &p1, const processType &p2 ){
	
	if ( p1.arrival_time == p2.arrival_time ) {
		return p1.PID > p2.PID;
	} // if
	else {
		return p1.arrival_time < p2.arrival_time;
	} // else
	
} // Compare_arrival_time_PID()

bool Compare_arrival_timeL( const processType &p1, const processType &p2 ){
	
	if ( p1.arrival_time == p2.arrival_time ) {
		return p1.PID > p2.PID;
	} // if
	else {
		return p1.arrival_time > p2.arrival_time;
	} // else
	
} // Compare_arrival_timeL()

bool Compare_priority( const processType &p1, const processType &p2 ){

	if ( p1.priority == p2.priority ) {
		if ( p1.done == p2.done ) {
			if ( p1.arrival_time == p2.arrival_time ) {
				return p1.PID < p2.PID;
			} // if
			else {
				return p1.arrival_time < p2.arrival_time;
			} // else
		} // if
		else {
			return p2.done;
		} // else
	} // if
	else {
		return p1.priority < p2.priority;
	} // else
	
} // Compare_priority()


bool Compare_N_priority( const processType &p1, const processType &p2 ) {

	if ( p1.priority == p2.priority ) {
		if ( p1.done == p2.done ) {
			if ( p1.arrival_time == p2.arrival_time ) {
				return p1.PID > p2.PID;
			} // if
			else {
				return p1.arrival_time < p2.arrival_time;
			} // else
		} // if
		else {
			return p2.done;
		} // else
	} // if
	else {
		return p1.priority < p2.priority;
	} // else
	
} // Compare_N_priority()

class Scheduling {

public:
	
	void Init();
	void DoMethod();
	bool ReadFile();
	void OutputFile();
	
private:
	string fileName = "";
	int method = 0, timeSlice = 0;
	vector<processType> buffer;
	resultType FCFS_result;
	resultType RR_result;
	resultType PSJF_result;
	resultType NSJF_result;
	resultType priority_result;

	void FCFS();
	void LCFS();
	void RR();
	void PSJF();
	void NSJF();
	void Priority();
	void NPriority();
	
	string DecToChar( int num );
	bool IsPreemptive( int arrivalTime, int curPriority, vector<processType> ready_queue, int & position, string type ) ;
	void UpdateReadyQ_priority( vector<processType> & ready_queue, processType curProcess ) ;
	void UpdateReadyQ_FCFS( int arrivalTime, vector<processType> & ready_queue, processType curProcess ) ;
	int GetNextProcess( int arrivalTime, vector<processType> ready_queue, string type ) ;
	void UpdateResult( processType curProcess, resultType & result ) ;
	
} ; // class Scheduling


void Scheduling::Init() {
	fileName = "";
	method = 0, timeSlice = 0;
	buffer.clear();
	FCFS_result.gantt_chart = "";
	FCFS_result.processBuffer.clear();
	RR_result.gantt_chart = "";
	RR_result.processBuffer.clear();
	PSJF_result.gantt_chart = "";
	PSJF_result.processBuffer.clear();
	NSJF_result.gantt_chart = "";
	NSJF_result.processBuffer.clear();
	priority_result.gantt_chart = "";
	priority_result.processBuffer.clear();
} // Scheduling::Init()

string Scheduling::DecToChar( int num ) {
	string eng = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
	string str = "";
	str = str + eng[num];
	return str;
} // Scheduling::DecToChar()

bool Scheduling::ReadFile() {
	
	fstream fp;
	processType newProcess;
	
	char ch = '\0';
	string temp = ""; 
	
	
	while ( 1 ) {
		cout << "\nPlease enter file name(quit : 0) : ";
		cin >> fileName;
		if ( fileName == "0" )  return false;
		fp.open((fileName + ".txt").c_str(), fstream::in);
		if ( fp.is_open() ) {
			fp >> method >> timeSlice >> ch;
			cout << "\nChoose method : " << method << "\n";
			cout << "Set time slice : " << timeSlice << "\n\n";
			getline( fp, temp, '\n' );  // 讀掉文字的部分
	
			while ( fp >> newProcess.PID >> newProcess.CPU_BURST
					   >> newProcess.arrival_time >> newProcess.priority ) {
	
				newProcess.done = false; 
				newProcess.remainTime = newProcess.CPU_BURST;
				buffer.push_back( newProcess );
			} // while
			
			fp.close();
			break;
		} // if
		else {
			cout << "Please enter file name again !\n";
		} // else
	} // while
	
	return true;
	
} // Scheduling::ReadFile()

void Scheduling::OutputFile() {
	
	fstream fp;
	fp.open((fileName + "_output.txt").c_str(), fstream::out);
	
	if ( !fp.is_open() ) return;
	
	if ( method == 1 OR method == 6 )  fp << "==    FCFS==\n" << FCFS_result.gantt_chart << "\n";
	if ( method == 2 OR method == 6 )  fp << "==      RR==\n" << RR_result.gantt_chart << "\n";
	if ( method == 3 OR method == 6 )  fp << "==    PSJF==\n" << PSJF_result.gantt_chart << "\n";
	if ( method == 4 OR method == 6 )  fp << "==Non-PSJF==\n" << NSJF_result.gantt_chart << "\n";
	if ( method == 5 OR method == 6 )  fp << "== Priority==\n" << priority_result.gantt_chart << "\n";
	
	fp << "===========================================================\n";
	fp << "                                                                                \n";
	fp << "Waiting Time\n";
	
	fp << "ID";
	if ( method == 1 OR method == 6 )  fp << "      FCFS";
	if ( method == 2 OR method == 6 )  fp << "    RR";
	if ( method == 3 OR method == 6 )  fp << "      PSJF";
	if ( method == 4 OR method == 6 )  fp << "    NPSJF";
	if ( method == 5 OR method == 6 )  fp << "   Priority";
	
	fp << "\n===========================================================\n";
	for ( int i = 0 ; i < FCFS_result.processBuffer.size() ; i++ ) {
		
		if ( method == 1 ) {
			fp << FCFS_result.processBuffer[i].PID << "\t";
			fp << FCFS_result.processBuffer[i].waiting_Time << "\n";  
		} // if
		else if ( method == 2 ) {
			fp << RR_result.processBuffer[i].PID << "\t";
			fp << RR_result.processBuffer[i].waiting_Time << "\n";  
		} // else if
		else if ( method == 3 ) {
			fp << PSJF_result.processBuffer[i].PID << "\t";
			fp << PSJF_result.processBuffer[i].waiting_Time << "\n";  
		} // else if
		else if ( method == 4 ) {
			fp << NSJF_result.processBuffer[i].PID << "\t";
			fp << NSJF_result.processBuffer[i].waiting_Time << "\n";  
		} // else if
		else if ( method == 5 ) {
			fp << priority_result.processBuffer[i].PID << "\t";
			fp << priority_result.processBuffer[i].waiting_Time << "\n";     
		} // else if
		else if ( method == 6 ) {
			fp << FCFS_result.processBuffer[i].PID << "\t";
			fp << FCFS_result.processBuffer[i].waiting_Time << "\t";  
			fp << RR_result.processBuffer[i].waiting_Time << "\t";  
			fp << PSJF_result.processBuffer[i].waiting_Time << "\t";  
			fp << NSJF_result.processBuffer[i].waiting_Time << "\t";  
			fp << priority_result.processBuffer[i].waiting_Time << "\n";     
		} // else if
    	
		    
	} // for
	
	fp << "===========================================================\n";
	fp << "\n";
	fp << "Turnaround Time\n";
	fp << "ID";
	if ( method == 1 OR method == 6 )  fp << "      FCFS";
	if ( method == 2 OR method == 6 )  fp << "    RR";
	if ( method == 3 OR method == 6 )  fp << "      PSJF";
	if ( method == 4 OR method == 6 )  fp << "    NPSJF";
	if ( method == 5 OR method == 6 )  fp << "   Priority";
	fp << "\n===========================================================\n";
	
	for ( int i = 0 ; i < FCFS_result.processBuffer.size() ; i++ ) {
		if ( method == 1 ) {
			fp << FCFS_result.processBuffer[i].PID << "\t";
			fp << FCFS_result.processBuffer[i].turnaround_Time << "\n";  
		} // if
		else if ( method == 2 ) {
			fp << RR_result.processBuffer[i].PID << "\t";
			fp << RR_result.processBuffer[i].turnaround_Time << "\n";  
		} // else if
		else if ( method == 3 ) {
			fp << PSJF_result.processBuffer[i].PID << "\t";
			fp << PSJF_result.processBuffer[i].turnaround_Time << "\n";  
		} // else if
		else if ( method == 4 ) {
			fp << NSJF_result.processBuffer[i].PID << "\t";
			fp << NSJF_result.processBuffer[i].turnaround_Time << "\n";  
		} // else if
		else if ( method == 5 ) {
			fp << priority_result.processBuffer[i].PID << "\t";
			fp << priority_result.processBuffer[i].turnaround_Time << "\n";     
		} // else if
		else if ( method == 6 ) {
			fp << FCFS_result.processBuffer[i].PID << "\t";
			fp << FCFS_result.processBuffer[i].turnaround_Time << "\t";  
			fp << RR_result.processBuffer[i].turnaround_Time << "\t";  
			fp << PSJF_result.processBuffer[i].turnaround_Time << "\t";  
			fp << NSJF_result.processBuffer[i].turnaround_Time << "\t";  
			fp << priority_result.processBuffer[i].turnaround_Time << "\n";     
		} // else if
	} // for
	
	fp << "===========================================================\n";
	
	cout << "Successfully write result to " <<  fileName  <<  "_output.txt\n";
	
	fp.close();
	
} // Scheduling::OutputFile()


void Scheduling::DoMethod() {
	
	if ( method == 1 ) {
		FCFS();
		//LCFS();
	} // if
	else if ( method == 2 ) {
		RR();
	} // else if
	else if ( method == 3 ) {
		PSJF();
	} // else if
	else if ( method == 4 ) {
		NSJF();
	} // else if
	else if ( method == 5 ) {
		//Priority();
		NPriority();
	} // else if
	else if ( method == 6 ) {
		//FCFS();
		LCFS();
		RR();
		PSJF();
		NSJF();
		//Priority();
		NPriority();
	} // else if
	else {
		cout << "Method number wrong !\n";
	} // else
	
} // Scheduling::DoMethod()

void Scheduling::FCFS() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	string gantt_chart = "";
	
	processType curProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, FCFS_result ) ;
			curPID = ""; // 把curPID歸零 
		} // if
		
		if ( curCPU_BURST == 0 AND !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) { 
			// 已有process到達 且 現在沒有process在執行 

			// 設定現在要執行的process 
			curProcess = ready_queue[0];
			curPID = DecToChar( ready_queue[0].PID ) ;
			curCPU_BURST = ready_queue[0].CPU_BURST ;
				
			// 設定完就從buffer刪掉
			ready_queue.erase( ready_queue.begin() ) ;
			
		} // if
	
		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			curProcess.remainTime = curCPU_BURST;
			// 因為要拿去比較, 隨時都要更新 
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, FCFS_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	FCFS_result.gantt_chart = gantt_chart;
	
} // Scheduling::FCFS()

void Scheduling::LCFS() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	int position = 0;
	string gantt_chart = "";
	
	processType curProcess;
	processType lastProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time_PID );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, FCFS_result ) ;
			curPID = ""; // 把curPID歸零 
		} // if
		
		if ( !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) { 
			// 已有process到達 且 現在沒有process在執行 
			
			if ( curCPU_BURST == 0 ) {  // 現在沒有process在進行
				// 直接找到下一個要執行的process 
				position = GetNextProcess( i, ready_queue, "LCFS" ) ;
				// 設定現在要執行的process 
				curProcess = ready_queue[position];
				curPID = DecToChar( ready_queue[position].PID ) ;
				curCPU_BURST = ready_queue[position].remainTime ;
				
				// 設定完就從buffer刪掉
				ready_queue.erase( ready_queue.begin() + position ) ;
				
			} // if
			
			else {  // 現在有process正在執行
				position = 0;
				// 檢查是否可搶奪 
				if ( IsPreemptive( i, curProcess.arrival_time, ready_queue, position, "LCFS" ) ) {
					lastProcess = curProcess;
					lastProcess.remainTime = curCPU_BURST;  // 把剩下的時間存起來
					lastProcess.done = true; 
					
					// 設定搶奪的process
					curProcess= ready_queue[position];
					curPID = DecToChar( ready_queue[position].PID ) ;
					curCPU_BURST = ready_queue[position].remainTime ;
				
					// 設定完就從buffer刪掉
					ready_queue.erase( ready_queue.begin() + position ) ;
					
					UpdateReadyQ_FCFS( i, ready_queue, lastProcess );  // 把剛剛的process放回readyQueue
				} // if
			} // else
			
			
			
		} // if
	
		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			curProcess.remainTime = curCPU_BURST;
			// 因為要拿去比較, 隨時都要更新 
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, FCFS_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	FCFS_result.gantt_chart = gantt_chart;
	
} // Scheduling::LCFS()

void Scheduling::RR() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	string gantt_chart = "";
	
	processType curProcess;
	processType lastProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0;
	int max_position = 0;
	int position = 0;
	int useTime = 0 ;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, RR_result ) ;
			curPID = ""; // 把curPID歸零 
			useTime = 0;
		} // if
		
		
		if ( !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) {  // 已有process到達 
			
			// 分成現在沒有process在進行, 跟有process在進行  
			
			if ( curCPU_BURST == 0 ) {  // 現在沒有process在進行
				// 直接找到下一個要執行的process 
				position = 0;
				
				// 設定現在要執行的process 
				curProcess= ready_queue[position];
				curPID = DecToChar( ready_queue[position].PID ) ;
				curCPU_BURST = ready_queue[position].remainTime ;
				
				// 設定完就從buffer刪掉
				ready_queue.erase( ready_queue.begin() + position ) ;
				
			} // if
			
			else {  // 現在有process正在執行
				max_position = 0;
				// 檢查是否timeout
				if ( useTime != 0 AND useTime == timeSlice ) {
					lastProcess = curProcess;
					lastProcess.remainTime = curCPU_BURST;  // 把剩下的時間存起來
					lastProcess.done = true; 
					useTime = 0;
					
					// 直接找到下一個要執行的process 
					// max_position = GetNextProcess( i, ready_queue, "RR" );
					max_position = 0;
					
					// 設定下一個process
					curProcess= ready_queue[max_position];
					curPID = DecToChar( ready_queue[max_position].PID ) ;
					curCPU_BURST = ready_queue[max_position].remainTime ;
				
					// 設定完就從buffer刪掉
					ready_queue.erase( ready_queue.begin() + max_position ) ;
					
					UpdateReadyQ_FCFS( i, ready_queue, lastProcess );  // 把剛剛的process放回readyQueue
				} // if
			} // else
			
		} // if
		
		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			useTime++;
			curProcess.remainTime = curCPU_BURST;
			// 因為要拿去比較, 隨時都要更新 
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, RR_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	RR_result.gantt_chart = gantt_chart;
	
} // Scheduling::RR()
	
void Scheduling::PSJF() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	string gantt_chart = "";
	
	processType curProcess;
	processType lastProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0;
	int max_position = 0;
	int position = 0;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, PSJF_result ) ;
			curPID = ""; // 把curPID歸零 
		} // if
		
		
		if ( !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) {  // 已有process到達 
			
			// 分成現在沒有process在進行, 跟有process在進行  
			
			if ( curCPU_BURST == 0 ) {  // 現在沒有process在進行
				// 直接找到下一個要執行的process 
				position = GetNextProcess( i, ready_queue, "PSJF" );
				
				// 設定現在要執行的process 
				curProcess= ready_queue[position];
				curPID = DecToChar( ready_queue[position].PID ) ;
				curCPU_BURST = ready_queue[position].remainTime ;
				
				// 設定完就從buffer刪掉
				ready_queue.erase( ready_queue.begin() + position ) ;
				
			} // if
			
			else {  // 現在有process正在執行
				max_position = 0;
				// 檢查是否可搶奪 
				if ( IsPreemptive( i, curProcess.remainTime, ready_queue, max_position, "PSJF" ) ) {
					lastProcess = curProcess;
					lastProcess.remainTime = curCPU_BURST;  // 把剩下的時間存起來
					lastProcess.done = true; 
					
					// 設定搶奪的process
					curProcess= ready_queue[max_position];
					curPID = DecToChar( ready_queue[max_position].PID ) ;
					curCPU_BURST = ready_queue[max_position].remainTime ;
				
					// 設定完就從buffer刪掉
					ready_queue.erase( ready_queue.begin() + max_position ) ;
					
					UpdateReadyQ_priority( ready_queue, lastProcess );  // 把剛剛的process放回readyQueue
				} // if
			} // else
			
		} // if
		
		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			curProcess.remainTime = curCPU_BURST;
			// 因為要拿去比較, 隨時都要更新 
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, PSJF_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	PSJF_result.gantt_chart = gantt_chart;
	
} // Scheduling::PSJF()

void Scheduling::NSJF() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	string gantt_chart = "";
	
	processType curProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0, min_CPU_BURST = 0, min_position = 0;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, NSJF_result ) ;
			curPID = ""; // 把curPID歸零 
		} // if
		
		
		if ( curCPU_BURST == 0 AND !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) {  // 已有process到達 
			
			min_CPU_BURST = ready_queue[0].CPU_BURST;
			min_position = 0;
			// 找到已經到達的process中, CPU_BURST最小的 
			for ( int k = 0 ; k < ready_queue.size() ; k++ ) {
				if ( i >= ready_queue[k].arrival_time AND
				     ready_queue[k].CPU_BURST < min_CPU_BURST ) {
					min_CPU_BURST = ready_queue[k].CPU_BURST;
					min_position = k;
				} // if
			} // for
				
			// 設定現在要執行的process
				
			curProcess = ready_queue[min_position] ;
			curPID = DecToChar( ready_queue[min_position].PID ) ;
			curCPU_BURST = ready_queue[min_position].CPU_BURST ;
				
			// 設定完就從buffer刪掉
			ready_queue.erase( ready_queue.begin() + min_position ) ;
				
		} // if

		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			curProcess.remainTime = curCPU_BURST;
			// 因為要拿去比較, 隨時都要更新 
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, NSJF_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	NSJF_result.gantt_chart = gantt_chart;
	
} // Scheduling::NSJF()

void Scheduling::Priority() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	string gantt_chart = "";
	
	processType curProcess;
	processType lastProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0;
	int max_position = 0;
	int position = 0;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, priority_result ) ;
			curPID = ""; // 把curPID歸零 
		} // if
		
		
		if ( !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) {  // 已有process到達 
			
			// 分成現在沒有process在進行, 跟有process在進行  
			
			if ( curCPU_BURST == 0 ) {  // 現在沒有process在進行
				// 直接找到下一個要執行的process 
				position = GetNextProcess( i, ready_queue, "priority" );
				
				// 設定現在要執行的process 
				curProcess= ready_queue[position];
				curPID = DecToChar( ready_queue[position].PID ) ;
				curCPU_BURST = ready_queue[position].remainTime ;
				
				// 設定完就從buffer刪掉
				ready_queue.erase( ready_queue.begin() + position ) ;
				
			} // if
			
			else {  // 現在有process正在執行
				max_position = 0;
				// 檢查是否可搶奪 
				if ( IsPreemptive( i, curProcess.priority, ready_queue, max_position, "priority" ) ) {
					lastProcess = curProcess;
					lastProcess.remainTime = curCPU_BURST;  // 把剩下的時間存起來
					lastProcess.done = true; 
					
					// 設定搶奪的process
					curProcess= ready_queue[max_position];
					curPID = DecToChar( ready_queue[max_position].PID ) ;
					curCPU_BURST = ready_queue[max_position].remainTime ;
				
					// 設定完就從buffer刪掉
					ready_queue.erase( ready_queue.begin() + max_position ) ;
					
					UpdateReadyQ_priority( ready_queue, lastProcess );  // 把剛剛的process放回readyQueue
				} // if
			} // else
			
		} // if
		
		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			curProcess.remainTime = curCPU_BURST;
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, priority_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	priority_result.gantt_chart = gantt_chart;
	
} // Scheduling::Priority()


void Scheduling::NPriority() {
	vector<processType> ready_queue;
	ready_queue = buffer;
	
	int i = 0;
	string gantt_chart = "";
	
	processType curProcess;
	sort( ready_queue.begin(), ready_queue.end(), Compare_arrival_time );
	// comparefunction不可以是member 
	
	string curPID = "" ;
	int curCPU_BURST = 0, min_priority = 0, position = 0;
	
	for ( i = 0 ; !ready_queue.empty() OR curCPU_BURST != 0 ; i++ ) {
		
		// 先看現在有沒有剛做完process 
		if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
			// 把資訊存起來 
			curProcess.turnaround_Time = i - curProcess.arrival_time;
			curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
			UpdateResult( curProcess, priority_result ) ;
			curPID = ""; // 把curPID歸零 
		} // if
		
		
		if ( curCPU_BURST == 0 AND !ready_queue.empty() AND i >= ready_queue[0].arrival_time ) {  // 已有process到達 
			
			position = 0;
			position = GetNextProcess( i, ready_queue, "Npriority" );
				
			// 設定現在要執行的process
				
			curProcess = ready_queue[position] ;
			curPID = DecToChar( ready_queue[position].PID ) ;
			curCPU_BURST = ready_queue[position].remainTime ;
				
			// 設定完就從buffer刪掉
			ready_queue.erase( ready_queue.begin() + position ) ;
				
		} // if

		if ( curPID != "" ) {  // 有process在進行 
			gantt_chart = gantt_chart + curPID;
			curCPU_BURST--;
			curProcess.remainTime = curCPU_BURST;
			// 因為要拿去比較, 隨時都要更新 
		} // else
		else {
			gantt_chart = gantt_chart + "-";
		} // else
		
	} // for
	
	if ( curCPU_BURST == 0 AND curPID != "" ) {  // process剛進行完 
		// 把資訊存起來 
		curProcess.turnaround_Time = i - curProcess.arrival_time;
		curProcess.waiting_Time = curProcess.turnaround_Time - curProcess.CPU_BURST;
		UpdateResult( curProcess, priority_result ) ;
		curPID = ""; // 把curPID歸零 
	} // if
	
	priority_result.gantt_chart = gantt_chart;
	
} // Scheduling::NPriority()

bool Scheduling::IsPreemptive( int arrivalTime, int curPriority, vector<processType> ready_queue, int & position, string type ) {
	
	int min = curPriority;
	bool preemptive = false;
	for ( int i = 0 ; i < ready_queue.size() ; i++ ) {
		if ( arrivalTime >= ready_queue[i].arrival_time ) {
			if ( type == "priority" AND min > ready_queue[i].priority ) {
				min = ready_queue[i].priority;
				position = i;
				preemptive = true;
			} // if
			else if ( type == "PSJF" AND min > ready_queue[i].remainTime ) {
				min = ready_queue[i].remainTime;
				position = i;
				preemptive = true;
			} // else if
			else if ( type == "LCFS" AND min < ready_queue[i].arrival_time ) {
				min = ready_queue[i].arrival_time;
				position = i;
				preemptive = true;
			} // else if
		} // if
	} // for
	
	return preemptive;

} // Scheduling::IsPreemptive()

void Scheduling::UpdateReadyQ_priority( vector<processType> & ready_queue, processType curProcess ) {
	
	for ( int i = 0 ; i < ready_queue.size() ; i++ ) {
		if ( Compare_arrival_time( curProcess, ready_queue[i] ) ) {
			ready_queue.insert( ready_queue.begin() + i, curProcess );
			return;
		} // if
	} // for
	
	ready_queue.push_back( curProcess );

} // Scheduling::UpdateReadyQ_priority()

void Scheduling::UpdateReadyQ_FCFS( int arrivalTime, vector<processType> & ready_queue, processType curProcess ) {
	
	for ( int i = 0 ; i < ready_queue.size() ; i++ ) {
		if ( arrivalTime < ready_queue[i].arrival_time ) {
			// 排在所有已到達的process最後面 
			ready_queue.insert( ready_queue.begin() + i, curProcess );
			return;
		} // if
	} // for
	
	ready_queue.push_back( curProcess );

} // Scheduling::UpdateReadyQ_FCFS()

int Scheduling::GetNextProcess( int arrivalTime, vector<processType> ready_queue, string type ) {
	processType curProcess = ready_queue[0];
	int position = 0;
	// 找到已經到達的process中, priority最高的(越小越高) 

	for ( int i = 0 ; i < ready_queue.size() ; i++ ) {
		if ( arrivalTime >= ready_queue[i].arrival_time ) {
			if ( type == "priority" AND Compare_priority( ready_queue[i], curProcess ) ) {
				position = i;
				curProcess = ready_queue[i];
			} // if
			else if ( type == "Npriority" AND Compare_N_priority( ready_queue[i], curProcess ) ) {
				position = i;
				curProcess = ready_queue[i];
			} // else if
			else if ( type == "PSJF" AND Compare_CPU_BURST( ready_queue[i], curProcess ) ) {
				position = i;
				curProcess = ready_queue[i];
			} // else if
			else if ( type == "LCFS" AND Compare_arrival_timeL( ready_queue[i], curProcess ) ) {
				position = i;
				curProcess = ready_queue[i];
			} // else if
		} // if
	} // for
	
	return position;
} // Scheduling::GetNextProcess()


void Scheduling::UpdateResult( processType curProcess, resultType & result ) {
	for ( int i = 0 ; i < result.processBuffer.size() ; i++ ) {
		if ( curProcess.PID < result.processBuffer[i].PID ) {
			result.processBuffer.insert( result.processBuffer.begin()+i, curProcess ) ;
			return;
		} // if
	} // for
	
	result.processBuffer.push_back( curProcess ) ;
} // Scheduling::UpdateResult()

int main() {
	
	Scheduling scheduling;
	scheduling.Init();
	
	while ( scheduling.ReadFile() ) {
		scheduling.DoMethod();
		scheduling.OutputFile();
		scheduling.Init();
	} // while
	
} // main
