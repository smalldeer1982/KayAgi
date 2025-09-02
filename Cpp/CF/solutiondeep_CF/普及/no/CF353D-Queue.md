# 题目信息

# Queue

## 题目描述

There are $ n $ schoolchildren, boys and girls, lined up in the school canteen in front of the bun stall. The buns aren't ready yet and the line is undergoing some changes.

Each second all boys that stand right in front of girls, simultaneously swap places with the girls (so that the girls could go closer to the beginning of the line). In other words, if at some time the $ i $ -th position has a boy and the $ (i+1) $ -th position has a girl, then in a second, the $ i $ -th position will have a girl and the $ (i+1) $ -th one will have a boy.

Let's take an example of a line of four people: a boy, a boy, a girl, a girl (from the beginning to the end of the line). Next second the line will look like that: a boy, a girl, a boy, a girl. Next second it will be a girl, a boy, a girl, a boy. Next second it will be a girl, a girl, a boy, a boy. The line won't change any more.

Your task is: given the arrangement of the children in the line to determine the time needed to move all girls in front of boys (in the example above it takes 3 seconds). Baking buns takes a lot of time, so no one leaves the line until the line stops changing.

## 说明/提示

In the first test case the sequence of changes looks as follows: MFM $ → $ FMM.

The second test sample corresponds to the sample from the statement. The sequence of changes is: MMFF $ → $ MFMF $ → $ FMFM $ → $ FFMM.

## 样例 #1

### 输入

```
MFM
```

### 输出

```
1
```

## 样例 #2

### 输入

```
MMFF
```

### 输出

```
3
```

## 样例 #3

### 输入

```
FFMMM
```

### 输出

```
0
```

# AI分析结果



### 题目重写  
**队列**  

#### 题目描述  
有 $n$ 个小学生在食堂包子窗口前排成一列，包含男生和女生。包子还没熟，队伍会经历若干次变化。  

每秒所有站在女生正前方的男生会同时与女生交换位置（让女生更靠近队首）。即若某时刻第 $i$ 位是男生且第 $i+1$ 位是女生，下一秒这两个位置将互换。  

例如初始序列为"男男女女"（MMFF），后续变化为：  
1秒后 → MFMF  
2秒后 → FMFM  
3秒后 → FFMM（此时不再变化）  

给定初始队列，求所有女生移动到男生左边所需的时间。  

#### 输入输出样例  
**样例1**  
输入：MFM  
输出：1  

**样例2**  
输入：MMFF  
输出：3  

**样例3**  
输入：FFMMM  
输出：0  

---

### 算法分类  
**递推/贪心**  

---

### 题解分析与结论  
**核心思路**：  
每个女生所需时间 = max(其前男生的数量，前一个女生时间+1)。所有女生时间的最大值即为答案。  

**关键推导**：  
- 每个女生至少需要移动其前面所有男生的次数  
- 连续女生会形成"等待链"，后续女生需比前一个多等1秒  
- 最终时间为所有女生移动时间的最大值  

**算法复杂度**：$O(n)$  

---

### 高星题解精选  
#### 1. decoqwq（5星）  
**核心亮点**：  
- 最早提出递推公式 `ans = max(ans+1, cnt)`  
- 代码简洁高效，逻辑清晰  

**代码片段**：  
```cpp  
int ans=0, m=0;  
for(int i=0; i<len; i++){  
    if(s[i]=='M') m++;  
    if(s[i]=='F' && m>0)  
        ans = max(ans+1, m);  
}  
```  

#### 2. 郑朝曦zzx（4星）  
**核心亮点**：  
- 数学形式化表达递推关系  
- 明确给出转移方程 $ans = \max(ans+1, cnt)$  

**代码片段**：  
```cpp  
for(int i=0; i<s.length(); ++i){  
    if(s[i] == 'M') ++cnt;  
    if(s[i] == 'F' && cnt)  
        ans = max(ans+1, cnt);  
}  
```  

#### 3. Fr0sTy（4星）  
**核心亮点**：  
- 对比模拟与递推方法的优劣  
- 强调"所有女生同时移动"的特性  

**代码片段**：  
```cpp  
for(int i=0; i<str.size(); i++){  
    if(str[i]=='M') cnt++;  
    if(str[i]=='F' && cnt>0)  
        times = max(times+1, cnt);  
}  
```  

---

### 关键实现技巧  
1. **单次遍历**：维护当前已遇到的男生数 `cnt`  
2. **动态更新最大值**：遇到女生时更新 `ans = max(ans+1, cnt)`  
3. **连续女生的处理**：通过 `ans+1` 体现等待关系  

---

### 拓展与心得  
**同类问题**：  
- 字符串中的模式递推（如括号匹配问题）  
- 多因素最值问题（如股票买卖时机）  

**个人心得**：  
> "当发现模拟超时后，意识到必须寻找数学规律。连续女生的等待关系类似流水线阻塞，需要递推处理。" —— Fr0sTy  

---

### 推荐练习题  
1. P1090 [合并果子]（贪心+优先队列）  
2. P1106 删数问题（递推找最优解）  
3. P2878 [保护花朵]（贪心排序策略）

---
处理用时：60.72秒