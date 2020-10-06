# CPU-Scheduling
模擬CPU排程演算法，包括FCFS(先進先出)、NSJF(不可奪取最短工作優先)、PSJF(可奪取最短工作優先)、RR(知更鳥式循環)、PP(優先等級)。

    1. FCFS (First Come First Serve)
    2. RR (Round Robin)
    3. PSJF (Preemptive Shortest Job First)
    4. NSJF (Non-preemptive Shortest Job First)
    5. PP (Preemptive Priority)
    6. ALL

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
  
4. NSJF之處理
  * 由CPU Burst最小的Process先處理
  * 若CPU Burst最少的Process不只一個, 則依arrival time小的先處理
  * 若CPU Burst及arrival time相同, 則依ProcessID由小至大依序處理。
  
5. PP之處理
  * Priority number小的代表Priority大
  * 依Priority由大致小依序處理
  * 若Priority相同,讓沒有用過CPU的先使用,無法分別時則依arrival time小的先處理
  * 若Priority及arrival time均相同, 則依ProcessID由小至大依序處理
  
