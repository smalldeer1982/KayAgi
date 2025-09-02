# 题目信息

# Rusty String

## 题目描述

Grigory loves strings. Recently he found a metal strip on a loft. The strip had length $ n $ and consisted of letters "V" and "K". Unfortunately, rust has eaten some of the letters so that it's now impossible to understand which letter was written.

Grigory couldn't understand for a long time what these letters remind him of, so he became interested in the following question: if we put a letter "V" or "K" on each unreadable position, which values can the period of the resulting string be equal to?

A period of a string is such an integer $ d $ from $ 1 $ to the length of the string that if we put the string shifted by $ d $ positions to the right on itself, then all overlapping letters coincide. For example, $ 3 $ and $ 5 $ are periods of "VKKVK".

## 说明/提示

In the first test case from example we can obtain, for example, "VKKVK", which has periods $ 3 $ and $ 5 $ .

In the second test case we can obtain "VVVVVV" which has all periods from $ 1 $ to $ 6 $ .

In the third test case string "KVKV" has periods $ 2 $ and $ 4 $ , and string "KVKK" has periods $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
 
5
V??VK
 
6
??????
 
4
?VK?
```

### 输出

```
2
3 5
6
1 2 3 4 5 6
3
2 3 4
```

# AI分析结果



## **算法分类**  
快速傅里叶变换（FFT）/ 数论变换（NTT）

---

## **核心思路与难点分析**  

### 核心算法流程  
1. **FFT/NTT加速匹配检测**  
   - 将字符串视为多项式，通过三次卷积计算匹配度（V-K、K-V、V/K的平方差异）  
   - 公式：$P(x)=\sum (t_i s_j^3 + t_i^3 s_j - 2t_i^2 s_j^2)$  
   - 若卷积结果为0，则初步认为该位移可能是周期  
   
2. **假周期排除**  
   - 若某周期$d$合法，则其所有倍数必须也合法  
   - 遍历每个候选周期$d$，检查其所有倍数是否都被标记为合法  

### 解决难点  
- **问号冲突**：FFT计算结果为0时可能存在问号同时需要匹配不同字符的矛盾  
- **数学性质应用**：利用周期倍数的数学性质（若$d$不合法，则存在其倍数也不合法）进行剪枝  

---

## **题解评分（≥4星）**  

### 1. tzc_wk（⭐⭐⭐⭐⭐）  
- **亮点**：完整推导三次卷积公式，给出数学性质证明，处理假周期逻辑清晰  
- **代码**：实现三次多项式乘法，显式处理反向字符串  

### 2. shadowice1984（⭐⭐⭐⭐）  
- **亮点**：代码简洁，优化NTT实现，直接枚举倍数剪枝  
- **独特技巧**：将字符拆分为V/K两套独立匹配系统  

### 3. 辰星凌（⭐⭐⭐⭐）  
- **亮点**：详细注释，强调输入总长处理，代码可读性高  
- **关键注释**：`for(Re j=2*i;j<=n;j+=i)` 的倍数剪枝逻辑  

---

## **最优技巧提炼**  

### 核心技巧  
1. **三次卷积替代通配符匹配**  
   用 $V^3K + KV^3 - 2V^2K^2$ 代替通配符匹配，消除问号的动态性影响  
2. **倍数剪枝定理**  
   若存在 $d$ 的倍数不合法，则 $d$ 必然不合法（数学性质保证剪枝正确性）  

### 代码实现要点  
```cpp  
// 检查倍数剪枝（以shadowice1984代码为例）  
for(int i=1;i<=n;i++)  
    for(int j=2*i;j<=n;j+=i)  
        if(f3[j]) f3[i] = -1;  
```

---

## **同类题目推荐**  
1. [P4173] 残缺的字符串（带通配符的字符串匹配）  
2. [CF528D] Fuzzy Search（多字符通配符匹配）  
3. [P3338] ZJOI2014 力（FFT优化卷积计算）  

---

## **可视化设计要点**  

### 动画演示方案  
1. **像素化字符串滑动**  
   - 以8-bit风格显示字符串，右移时播放像素移动动画  
   - **高亮**当前匹配位置，红色标记冲突字符对  

2. **FFT卷积可视化**  
   - 展示三次卷积的波形叠加过程，用不同颜色区分 $V^3K$、$KV^3$、$-2V^2K^2$  
   - 动态绘制卷积结果曲线，零点用绿色标记  

3. **倍数检查演示**  
   - 遍历候选周期时，自动高亮其所有倍数，若发现红色标记则触发音效  

### 复古游戏化设计  
- **音效设计**：  
  - 匹配成功：短促的8-bit上升音阶  
  - 冲突发现：类似《超级玛丽》踩乌龟的“咚”声  
- **积分系统**：  
  - 每正确排除一个假周期+10分，最终剩余合法周期数作为额外奖励  

---

## **关键代码片段**  

### FFT三次卷积核心逻辑  
```cpp  
// tzc_wk的卷积实现  
void match() {  
    for(int i=0; i<len; i++) a[i]=comp(pt1[i]*pt1[i]*pt1[i],0);  
    FFT(a,1); FFT(b,1);  
    for(int i=0; i<len; i++) p[i] = a[i]*b[i];  
    // ...类似处理其他两项  
    FFT(p,-1);  
}  
```

### 倍数剪枝实现  
```cpp  
// 辰星凌的剪枝逻辑  
for(Re i=1; i<=n; i++) {  
    bool flag = true;  
    for(Re j=i; j<=n; j+=i)  
        if(!PA[j]) { flag=false; break; }  
    if(flag) ans.push_back(i);  
}  
```

---

## **总结**  
通过FFT/NTT加速卷积计算候选周期，结合数学性质的倍数剪枝排除假周期，是解决此类含不定字符周期问题的通用范式。关键是将字符串匹配转化为多项式运算，并利用数论性质优化验证过程。

---
处理用时：73.78秒