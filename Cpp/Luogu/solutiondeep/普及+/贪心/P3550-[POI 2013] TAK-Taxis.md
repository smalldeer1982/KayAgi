# 题目信息

# [POI 2013] TAK-Taxis

## 题目描述

Byteasar wants to take a taxi from the town Bytehole to the town Bytepit,    which is $m$ kilometres away from Bytehole.

Exactly $d$ kilometres along the way from Bytehole to Bytepit, there is    a base of $n$ taxis, numbered from $1$ to $n$.

The taxi no. $i$ has enough fuel to drive exactly $x_i$ kilometres.

Byteasar can change taxis at any point.

All the taxis start at their base but need not return there.

Your task is to determine whether Byteasar can be driven from Bytehole to    Bytepit, and if so, what it the minimum number of taxis required for such    a journey.

Translation 1:

一条线段有三个点，0为初始位置，d为出租车总部位置，m为家的位置，人要叫车，有n辆车可以提供，每辆车有一个路程上限，并且都从车站出发，叫的车行驶之后不必须回到车站，问最少叫几辆车

.Translation 2:

Byteasar想坐出租车从Bytehole镇到Bytepit镇,恰好有d千米从Bytehole镇到Bytepit镇,这有n个出租车,编号从1到n.第i个出租车有足够的燃料行驶xi千米.Byteasar可以在任意点改变出租车.所有的出租车从他们的总部出发但没必要返回总部.你的任务是判断Byteasar是否能从Bytehole镇到Bytepit镇,如果可以,求出路途需要出租车的最小数量.


## 说明/提示

提示:此题需开long long


## 样例 #1

### 输入

```
42 23 6
20 25 14 27 30 7
```

### 输出

```
4
```

# AI分析结果



### 综合分析与结论  
各题解均采用贪心策略，核心思路是：保留一辆能从基地直达终点的出租车，其余车辆按里程降序使用以尽快接近基地。难点在于正确预留车辆及处理移动过程中的临界条件。最优策略是预处理保留车辆后贪心计算最小用车数。

---

### 精选题解推荐  

#### 1. 作者：karma (⭐⭐⭐⭐⭐)  
**关键亮点**：  
- 注释详尽，变量命名清晰（如`now`表示当前位置，`last`表示保留车索引）  
- 逻辑分段明确，重点解释了预留车辆的必要性和贪心终止条件  
- 代码可读性高，附带关键注释解释数学推导（如总行驶距离计算）  

**个人心得**：  
> "贪心之前需要留一辆能从总部到终点的车，否则可能因提前耗尽大车而失败。"

#### 2. 作者：远航之曲 (⭐⭐⭐⭐)  
**关键亮点**：  
- 通过反例分析指出纯贪心的缺陷  
- 代码简洁，使用`res`变量明确表示预留车辆索引  
- 引入`cut()`函数统一处理失败情况，增强代码复用性  

**个人心得**：  
> "必须预留一辆车应对后半程，这是贪心策略成立的前提条件。"

#### 3. 作者：Yizhixiaoyun (⭐⭐⭐⭐)  
**关键亮点**：  
- 代码结构紧凑，快速排序与循环处理逻辑清晰  
- 使用`tot2`动态记录移动距离，直观反映贪心过程  
- 边界条件处理完善（如提前到达终点时`ans--`）  

---

### 核心代码实现  

#### 贪心主逻辑（karma版）  
```cpp  
sort(a+1,a+1+num,cmp);  
for(int i=1;i<=num;++i) 
    if(a[i]<N-M) {last=i; break;}  
last--;  
// ... 预留车辆处理  

for(int i=1;i<=num;++i) {  
    if(i==last) continue;  
    if(now>=M || N-now+M-now<=a[last]) break;  
    if(a[i]<=M-now) exit(0);  
    ans++;  
    now += a[i] - (M - now);  
    if(now>=N) { ans--; break; }  
}  
```  
**实现思想**：  
1. 排序后找到第一个无法直达终点的车辆，其前一辆作为预留车。  
2. 遍历其他车辆，每次计算该车能推进的最远距离更新`now`。  
3. 若中途到达终点或满足预留车条件则提前终止。  

---

### 拓展与举一反三  
**相似题目推荐**：  
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)（贪心排序策略）  
2. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)（贪心模拟覆盖区间）  
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针贪心配对）  

**关键思维模式**：  
- **预留最优解**：在贪心过程中保留关键资源应对后续需求。  
- **动态更新状态**：通过变量（如`now`）实时跟踪当前进度，动态调整策略。

---
处理用时：61.71秒