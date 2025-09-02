# 题目信息

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1
```

### 输出

```
1 2 3 0 3 
```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1
```

### 输出

```
2 2 2 1 1 0 4 3 4 4 
```

# AI分析结果



---

## 算法分类  
**贪心算法**

---

## 题解思路与核心难点  

### 核心思路  
所有题解均采用贪心策略：**优先处理考试时间最早的考试**，在其公布时间到考试前的区间内尽可能安排复习天数。若某考试无法安排足够复习天数，直接判定无解。

### 算法要点  
1. **结构体排序**：按考试时间 `d_i` 升序排序，确保先处理截止时间更紧迫的考试。  
2. **时间分配**：对每个考试，从公布日 `s_i` 到考试前日 `d_i-1` 顺序遍历，优先填充空闲天数。  
3. **冲突解决**：若多个考试区间重叠，优先满足更早截止的考试，剩余天数留给后续考试。  
4. **终止条件**：若某考试复习天数不足，立即返回 `-1`，避免无效计算。  

### 解决难点  
- **时间窗口重叠**：通过排序保证最早截止的考试优先占用时间，避免后续考试被挤占。  
- **非连续复习**：允许间断复习，只需总天数满足即可。  

---

## 题解评分（≥4星）  

### 1. 作者：fls233666（★★★★☆）  
- **亮点**：代码简洁，结构清晰，直接按 `d_i` 排序后顺序处理，无冗余操作。  
- **代码片段**：  
  ```cpp  
  sort(e+1,e+1+m,cmp);  
  for(rgt i=1;i<=m;i++){  
    for(rgt j=e[i].si;j<e[i].di;j++){  
      if(!plan[j]){  
        plan[j]=e[i].id;  
        e[i].ci--;  
        if(!e[i].ci) break;  
      }  
    }  
    if(e[i].ci) return printf("-1"),0;  
  }  
  ```  

### 2. 作者：风中の菜鸡（★★★★☆）  
- **亮点**：详细注释与代码可读性，推荐同类练习题加深理解。  
- **代码片段**：  
  ```cpp  
  sort(exam+1,exam+m+1,cmp);  
  for(int i=1;i<=m;i++){  
    num=0;  
    for(int j=exam[i].promulgate;j<exam[i].start;j++){  
      if(num==exam[i].review) break;  
      if(jh[j]==-1) jh[j]=exam[i].place, num++;  
    }  
    if(num<exam[i].review) return cout<<"-1",0;  
  }  
  ```  

### 3. 作者：kimidonatsu（★★★★☆）  
- **亮点**：结构体设计合理，代码模块化，适合教学演示。  
- **代码片段**：  
  ```cpp  
  stable_sort(exams +1, exams +m +1, cmp);  
  for(re int i=1;i<=m;i++){  
    int tot=0;  
    for(re int j=exams[i].s; j<=exams[i].d && tot<exams[i].c; j++)  
      if(!ans[j]) ans[j]=exams[i].id, tot++;  
    if(tot<exams[i].c) exit(0);  
  }  
  ```  

---

## 最优思路提炼  

### 关键步骤  
1. **排序策略**：按考试时间 `d_i` 升序排序。  
2. **时间填充**：从 `s_i` 开始顺序填充空闲天数，直到满足 `c_i`。  
3. **即时终止**：若某考试无法满足需求，立即判定无解。  

### 技巧与优化  
- **结构体记录原始位置**：排序后仍能正确输出考试编号。  
- **贪心正确性证明**：若无法满足更早考试，后续考试必然无法满足。  

---

## 类似题目推荐  
1. **P1230 智力大冲浪**：类似的时间窗口贪心，优先处理截止早的任务。  
2. **P1803 活动安排**：区间调度问题，选择不冲突的最多活动。  
3. **P2949 工作调度**：利用优先队列动态选择最优任务。  

---

## 可视化与算法演示  

### 动画设计  
- **网格表示天数**：用不同颜色标记考试日（红色）、复习（绿色）、休息（灰色）。  
- **高亮当前操作**：正在处理的考试区间用闪烁边框提示，填充复习天数时显示进度条。  
- **音效反馈**：成功填充复习天数为“滴”声，考试失败为“哔”声。  

### 复古像素风格  
- **8位调色板**：红色（#FF0000）、绿色（#00FF00）、灰色（#808080）。  
- **Canvas绘制**：每天用 32x32 像素方块表示，考试日显示“E”，复习日显示编号。  
- **自动演示模式**：按排序顺序处理考试，每步延迟 500ms，可暂停或调速。  

### 关键代码片段（伪代码）  
```javascript  
// 初始化 Canvas 和音效  
const grid = new PixelGrid(n, 32, 32);  
grid.initColors({ exam: '#FF0000', study: '#00FF00', rest: '#808080' });  

// 自动演示逻辑  
let currentExam = 0;  
function autoStep() {  
  if (currentExam >= m) return;  
  const exam = sortedExams[currentExam];  
  for (let day = exam.s; day < exam.d; day++) {  
    if (grid.getDay(day) === 'rest') {  
      grid.setDay(day, 'study', exam.id);  
      playSound('beep');  
      exam.c--;  
      if (exam.c === 0) break;  
    }  
  }  
  if (exam.c > 0) playSound('fail');  
  currentExam++;  
}  
```  

---

## 个人心得  
- **贪心排序是关键**：最初尝试按 `s_i` 排序导致逻辑混乱，后调整为 `d_i` 后迎刃而解。  
- **边界条件易错**：需确保考试当天不可复习，且 `s_i < d_i`。  

--- 

通过上述分析与可视化设计，可清晰理解贪心策略如何高效解决时间窗口冲突问题。

---
处理用时：87.90秒