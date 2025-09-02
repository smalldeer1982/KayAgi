# 题目信息

# KUSAC - Kusac

## 题目描述

Mirko has given up on the difficult coach job and switched to food tasting instead. Having skipped 

breakfast like a professional connoisseur, he is visiting a Croatian cured meat festival. The most 

renowned cook at the festival, Marijan Bajs, has prepared N equal sausages which need to be 

distributed to M tasters such that each taster gets a precisely equal amount. He will use his trusted knife 

to cut them into pieces. 

In order to elegantly divide the sausages, the number of cuts splitting individual sausages must be as 

small as possible. For instance, if there are two sausages and six tasters (the first test case below), it is 

sufficient to split each sausage into three equal parts, making a total of four cuts. On the other hand, if 

there are three sausages and four tasters (the second test case below), one possibility is cutting off three 

quarters of each sausage. Those larger parts will each go to one of the tasrers, while the fourth taster 

will get the three smaller pieces (quarters) left over. 

Mirko wants to try the famous sausages, so he volunteered to help Bajs. Help them calculate the 

minimum total number of cuts needed to carry out the desired division. 

## 样例 #1

### 输入

```
2 6```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
3
```

# AI分析结果



**唯一算法分类**  
数论（最大公约数应用）

---

### 题解思路与算法要点  
1. **核心公式推导**  
   将香肠连成一根长链，总共有 `m` 份，原本需要切 `m-1` 刀。  
   但香肠原有断口与切点重合时，可省去一刀。重合次数为 `gcd(n,m)-1`。  
   最终公式：`总刀数 = m - gcd(n,m)`  

2. **解决难点**  
   - 理解香肠断口与切点的重合关系  
   - 通过最大公约数计算重合次数  

3. **算法实现**  
   直接计算 `m - gcd(n,m)`，时间复杂度为 `O(log min(n,m))`。

---

### 题解评分（≥4星）  
1. **Miller2019（5星）**  
   - 思路清晰，直接推导公式  
   - 代码简洁（仅需调用gcd函数）  
   - 时间复杂度最优  

2. **做对算我输（5星）**  
   - 图示辅助理解  
   - 代码极简，突出核心公式  

3. **Kevin_Zhen（5星）**  
   - 清晰解释公式推导过程  
   - 代码规范，包含必要头文件  

---

### 最优思路提炼  
**关键技巧**：将物理切割问题转化为数学公约数问题  
- **核心观察**：香肠断口与切点重合次数等于 `gcd(n,m)`  
- **公式优化**：直接使用 `m - gcd(n,m)` 避免遍历或递归  

---

### 同类型题推荐  
1. **P4549 裴蜀定理**（公约数应用）  
2. **P1072 Hankson的趣味题**（公约数与公倍数综合）  
3. **P4057 晨跑**（多数最大公约数）  

---

### 可视化算法演示  
**动画设计**：  
1. **香肠连成长链**：用像素方块拼接表示 `n` 根香肠。  
2. **切点标记**：用红色虚线标出 `m` 等分切点。  
3. **断口重合检测**：绿色高亮与香肠断口重合的切点（数量为 `gcd(n,m)`）。  
4. **刀数计算**：显示总刀数公式 `m - gcd(n,m)`。  

**复古游戏化效果**：  
- **像素风格**：香肠用棕色方块，切点用红色/绿色闪烁像素。  
- **音效**：切刀时播放“咔嚓”声，重合时触发“叮”声。  
- **自动演示**：点击按钮后，自动播放连香肠、标切点、计算结果的全过程。  

---

### 核心代码实现  
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    cout << m - __gcd(n, m);
    return 0;
}
```

---

### 总结  
本题通过数学建模将切割问题转化为公约数计算，代码仅需一行公式。关键点在于发现断口与切点的重合关系，用最大公约数快速统计重合次数。数学思维在此类问题中往往能大幅简化逻辑。

---
处理用时：72.74秒