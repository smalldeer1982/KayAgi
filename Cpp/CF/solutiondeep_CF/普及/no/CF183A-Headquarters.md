# 题目信息

# Headquarters

## 题目描述

Sensation, sensation in the two-dimensional kingdom! The police have caught a highly dangerous outlaw, member of the notorious "Pihters" gang. The law department states that the outlaw was driving from the gang's headquarters in his car when he crashed into an ice cream stall. The stall, the car, and the headquarters each occupies exactly one point on the two-dimensional kingdom.

The outlaw's car was equipped with a GPS transmitter. The transmitter showed that the car made exactly $ n $ movements on its way from the headquarters to the stall. A movement can move the car from point $ (x,y) $ to one of these four points: to point $ (x-1,y) $ which we will mark by letter "L", to point $ (x+1,y) $ — "R", to point $ (x,y-1) $ — "D", to point $ (x,y+1) $ — "U".

The GPS transmitter is very inaccurate and it doesn't preserve the exact sequence of the car's movements. Instead, it keeps records of the car's possible movements. Each record is a string of one of these types: "UL", "UR", "DL", "DR" or "ULDR". Each such string means that the car made a single movement corresponding to one of the characters of the string. For example, string "UL" means that the car moved either "U", or "L".

You've received the journal with the outlaw's possible movements from the headquarters to the stall. The journal records are given in a chronological order. Given that the ice-cream stall is located at point $ (0,0) $ , your task is to print the number of different points that can contain the gang headquarters (that is, the number of different possible locations of the car's origin).

## 说明/提示

The figure below shows the nine possible positions of the gang headquarters from the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183A/5eedd58060bd35a7ed9fa57f2be7f5f0bfad5425.png)For example, the following movements can get the car from point $ (1,0) $ to point $ (0,0) $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183A/a0545c148a057862574d8aad0a7d3d66cb719bc3.png)

## 样例 #1

### 输入

```
3
UR
UL
ULDR
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2
DR
DL
```

### 输出

```
4
```

# AI分析结果



### 中文重写题目
**总部**

#### 题目描述
二维王国发生重大事件！警方抓获了一个高危逃犯，该逃犯是臭名昭著的“Pihters”团伙成员。据法律部门称，逃犯驾车从团伙总部出发时撞上了一个冰淇淋摊。摊点、汽车和总部在二维平面上各占据一个点。

逃犯的汽车装有GPS发射器，显示汽车从总部到摊点恰好进行了 $n$ 次移动。每次移动可将汽车从点 $(x,y)$ 移动到四个相邻点之一：$(x-1,y)$（标记为"L"）、$(x+1,y)$（标记为"R"）、$(x,y-1)$（标记为"D"）、$(x,y+1)$（标记为"U"）。

GPS记录不保存移动的确切顺序，而是记录可能的移动字符串。每个记录是"UL"、"UR"、"DL"、"DR"或"ULDR"中的一个，表示该次移动选择了字符串中的某个字符对应的方向。例如，"UL"表示汽车移动了"U"或"L"。

已知摊点位于 $(0,0)$，请计算可能的团伙总部位置数目（即汽车出发点的不同可能坐标数）。

---

### 算法分类
**数学（组合计数与乘法原理）**

---

### 题解分析与结论
所有题解的核心思路均基于**坐标变化独立性与乘法原理**：
1. **方向分类**：将移动类型分为两组：
   - **UL/DR/ULDR** 影响对角线方向，决定横向与纵向的可能范围。
   - **UR/DL/ULDR** 影响另一对角线方向，决定另一维度的可能范围。
2. **乘法原理**：总可能位置数为两个方向的可能扩展数的乘积。

关键难点在于识别移动类型对坐标的独立影响，并将ULDR视为可贡献到两个方向的通配符。所有题解均正确应用这一模型，仅实现方式略有差异。

---

### 精选题解（评分≥4星）

#### 1. 作者：sun_qy（★★★★☆）
**关键亮点**：
- 使用`map`清晰统计各移动类型出现次数。
- 明确公式推导过程，解释组合意义。
**核心代码**：
```cpp
map <string, int> mov;
// 统计各移动类型次数后计算
long long ans = 1ll * (mov["UL"] + mov["ULDR"] + mov["DR"] + 1) * (mov["UR"] + mov["DL"] + mov["ULDR"] + 1);
```

#### 2. 作者：_int123_（★★★★☆）
**关键亮点**：
- 代码简洁，直接使用`map`存储，公式表达清晰。
- 明确提示数据溢出问题，强调`long long`转换。
**核心代码**：
```cpp
cout << (a["UL"]+a["DR"]+a["ULDR"]+1) * (a["UR"]+a["DL"]+a["ULDR"]+1);
```

#### 3. 作者：nightwatch.ryan（★★★★☆）
**关键亮点**：
- 代码极简，直接输出计算式。
- 注释强调`1ll`防溢出的细节。
**核心代码**：
```cpp
std::cout << 1ll*(mps["UL"]+mps["DR"]+mps["ULDR"]+1)*(mps["UR"]+mps["DL"]+mps["ULDR"]+1);
```

---

### 关键思路总结
1. **独立维度分析**：将二维坐标分解为两个独立方向的变化，分别计算最大扩展范围。
2. **组合计数技巧**：利用`map`统计各移动类型次数，ULDR同时贡献到两个方向。
3. **防溢出处理**：使用`1ll`或`long long`确保乘法结果不溢出。

---

### 拓展与相似题目
1. **P1002 [NOIP2002 普及组] 过河卒**（路径计数，动态规划）
2. **P1144 最短路计数**（BFS与路径数统计）
3. **P2822 [NOIP2016 提高组] 组合数问题**（组合数预处理与模运算）

---

### 个人心得摘录
- **数据类型**：多个题解强调使用`long long`避免溢出（如："相乘会爆int，要乘1ll"）。
- **方向等价性**：将ULDR视为可扩展两个方向的通配符是解题关键（如："ULDR可以理解为两种情况都可以取到"）。

---
处理用时：56.28秒