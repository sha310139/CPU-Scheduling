# CPU-Scheduling
模擬CPU排程演算法，包括FCFS(先進先出)、NSJF(不可奪取最短工作優先)、PSJF(可奪取最短工作優先)、RR(知更鳥式循環)、PP(優先等級)。

## 開發平台
Win10
<br>
<br>

## 使用開發環境
Dev C++
<br>
<br>

## 使用方式
將input檔放至當前目錄<br>
編譯

    OS_project2.cpp  
或

    OS_project2_v2.cpp

之後執行<br>
輸入input檔名後<br>
程式會產出結果於 input檔名_output.txt 檔案中<br>
<br> 
<br>


## input檔格式

第一行第一個integer為method,範圍1~6<br>
<br>
第一行第二個integer為time slice,範圍不定<br>
<br>
第二擺放的資料為<br>
ID CPU Burst Arrival Time Priority<br>
<br>
第三行開始每行依序為<br>
[ProcessID] [CPUBurst] [arrival time] [Priority]<br>
皆為integer，不會有浮點數<br>

各method定義如下

    1. FCFS (First Come First Serve)
    2. RR (Round Robin)
    3. PSJF (Preemptive Shortest Job First)
    4. NSJF (Non-preemptive Shortest Job First)
    5. PP (Preemptive Priority)
    6. ALL

<br> 
<br>

## output檔格式

output分三個區段<br>
第一個區段為Gantt chart<br>
<br>
第二個區段顯示各個process id 在各個method(可能數個)的Waiting Time<br>
<br>
第三個區段顯示各個process id 在各個method(可能數個)的Turn around Time<br>
<br>
<br>

## v1及v2版本介紹

v1實作FCFS、NSJF、PSJF、RR、PP<br>

v2中的FCFS及PP則有所更動<br>

(1)將FIFO改成LIFO，後進先出可搶奪若Arrival Time相同，則依ProcessID由大至小依序處理。(A-output.txt)<br>
(2)Priority排程改成不可搶奪。若Priority及Arrival Time均相同，則依ProcessID由大至小依序處理。(B-output.txt)<br>
<br>
<br>

## 規則細節說明

就處理程序三態角度來看，本專案沒有因為輸出/輸入而進行環境切換的情況，<br>
因此「只有在process到達、或是time out、或是process執行結束才要比大小，並不是時時刻刻都在比大小」<br>


1. FCFS
  * 依arrival time先後次序處理
  * 若arrival time相同時, 則依ProcessID由小至大依序處理。

2. RR
  * 先依arrival time先後次序處理, 時候未到的Process不能Run。
  * 若arrival time相同時, 則依ProcessID由小至大依序處理。
  * Time out時, 若有新來的Process, 則讓新來的Process排在前面。
  * 某個ProcessTime slice未用完就結束時, 必須讓下一個Process執行。

3. PSJF
  * 由剩餘CPU Burst最小的Process先處理。
  * 若剩餘的CPU Burst相同, 讓沒有用過CPU的先使用, 無法分別時則依arrival time小的先處理。
  * 若剩餘CPU Burst相同且arrival time相同,則依ProcessID由小至大依序處理。
  * 但當CPU裡process的CPU Burst等於備妥佇列裡第一個process的CPU Burst,
  且備妥佇列裡第一個process尚未被使用,不會發生搶奪
  
4. NSJF之處理
  * 由CPU Burst最小的Process先處理
  * 若CPU Burst最少的Process不只一個, 則依arrival time小的先處理
  * 若CPU Burst及arrival time相同, 則依ProcessID由小至大依序處理。
  
5. PP之處理
  * Priority number小的代表Priority大
  * 依Priority由大致小依序處理
  * 若Priority相同,讓沒有用過CPU的先使用,無法分別時則依arrival time小的先處理
  * 若Priority及arrival time均相同, 則依ProcessID由小至大依序處理
  * 但當CPU裡process的Priority等於備妥佇列裡第一個process的Priority, 
  且備妥佇列裡第一個process尚未被使用,不會發生搶奪
  
