# 题目信息

# Cards

## 题目描述

Catherine has a deck of $ n $ cards, each of which is either red, green, or blue. As long as there are at least two cards left, she can do one of two actions:

- take any two (not necessarily adjacent) cards with different colors and exchange them for a new card of the third color;
- take any two (not necessarily adjacent) cards with the same color and exchange them for a new card with that color.

She repeats this process until there is only one card left. What are the possible colors for the final card?

## 说明/提示

In the first sample, Catherine has one red card and one blue card, which she must exchange for a green card.

In the second sample, Catherine has two green cards and one red card. She has two options: she can exchange the two green cards for a green card, then exchange the new green card and the red card for a blue card. Alternatively, she can exchange a green and a red card for a blue card, then exchange the blue card and remaining green card for a red card.

In the third sample, Catherine only has blue cards, so she can only exchange them for more blue cards.

## 样例 #1

### 输入

```
2
RB
```

### 输出

```
G
```

## 样例 #2

### 输入

```
3
GRG
```

### 输出

```
BR
```

## 样例 #3

### 输入

```
5
BBBBB
```

### 输出

```
B
```

# AI分析结果



【题目翻译】

# 卡片

## 题目描述

凯瑟琳有一叠 $n$ 张卡片，每张卡片为红、绿、蓝三种颜色之一。只要剩下至少两张卡片，她可以进行以下两种操作之一：

- 任取两张不同颜色的卡片（无需相邻），将其替换为第三种颜色的卡片；
- 任取两张同色的卡片，将其替换为一张该颜色的卡片。

重复这个过程直到只剩一张卡片。问最后可能剩下什么颜色？

## 说明/提示

样例一：两张红蓝卡片必须替换为绿色。

样例二：通过不同操作顺序可以得到蓝或红。

样例三：全蓝卡片只能得到蓝色。

---

**算法分类**：数学/组合数学

---

**题解分析与结论**

所有题解均基于颜色数量的数学特性推导，核心思路为：

1. **全同色**：只能得到该颜色
2. **存在两种其他颜色**：通过交替操作可转换为目标色
3. **单种颜色数量≥2且另一颜色缺失**：通过同色消除和异色转换得到目标色

**最优思路**：对每个颜色检查以下条件（以蓝色为例）：
- 全蓝
- 红绿均存在
- （红≥2且绿=0且有蓝）或（绿≥2且红=0且有蓝）

---

**推荐题解**

1. **作者：L_zaa_L（5星）**
   **亮点**：条件归纳完整，代码简洁高效
   ```c
   // 核心判断逻辑（蓝色）
   if((g>0&&r>0)||(g==0&&r>1&&b>0)||(r==0&&g>1&&b>0)||b==n)
       printf("B");
   ```

2. **作者：如履薄冰（4星）**
   **亮点**：操作组合策略清晰
   ```cpp
   // 条件判断逻辑
   if((gr > 0 && re > 0) || (bl == n) || (re > 1 && gr == 0 && bl) || (gr > 1 && re == 0 && bl))
       cout << 'B';
   ```

3. **作者：封禁用户（4星）**
   **亮点**：条件表达规范易读
   ```cpp
   if ((G > 0 && R > 0) || (B == n) || (R > 1 && G == 0 && B) || (G > 1 && R == 0 && B)) 
       cout << 'B';
   ```

---

**关键代码实现**

统计颜色数量后，按顺序（B→G→R）进行条件判断：
```cpp
int r=0, g=0, b=0;
for(/*遍历卡片*/){/*统计数量*/}

if((g&&r) || (g==0&&r>1&&b) || (r==0&&g>1&&b) || b==n) cout<<"B";
if((b&&r) || (b==0&&r>1&&g) || (r==0&&b>1&&g) || g==n) cout<<"G";
if((b&&g) || (b==0&&g>1&&r) || (g==0&&b>1&&r) || r==n) cout<<"R";
```

---

**拓展题型**

1. **CF1155B**（博弈+奇偶分析）
2. **P2581**（状态转换与数学推导）
3. **P7914**（操作策略与数学归纳）

---

**心得摘录**

- "判断顺序必须按BGR，否则可能WA"（__UrFnr__）
- "当两种颜色存在时，通过操作一可逐步转换"（如履薄冰）
- "同色消除本质是数量奇偶性控制"（L_zaa_L）

---
处理用时：94.41秒