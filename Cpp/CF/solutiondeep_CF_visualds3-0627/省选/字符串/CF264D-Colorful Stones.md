# 题目信息

# Colorful Stones

## 题目描述

There are two sequences of colorful stones. The color of each stone is one of red, green, or blue. You are given two strings $ s $ and $ t $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone of the first sequence. Similarly, the $ i $ -th (1-based) character of $ t $ represents the color of the $ i $ -th stone of the second sequence. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone of the first sequence and Cat Vasya is standing on the first stone of the second sequence. You can perform the following instructions zero or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , the animals standing on stones whose colors are $ c $ will move one stone forward. For example, if you perform an instruction «RED», the animals standing on red stones will move one stone forward. You are not allowed to perform instructions that lead some animals out of the sequences. In other words, if some animals are standing on the last stones, you can't perform the instructions of the colors of those stones.

A pair of positions (position of Liss, position of Vasya) is called a state. A state is called reachable if the state is reachable by performing instructions zero or more times from the initial state (1, 1). Calculate the number of distinct reachable states.

## 说明/提示

In the first example, there are five reachable states: (1, 1), (2, 2), (2, 3), (3, 2), and (3, 3). For example, the state (3, 3) is reachable because if you perform instructions "RED", "GREEN", and "BLUE" in this order from the initial state, the state will be (3, 3). The following picture shows how the instructions work in this case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264D/ff8e8d184349ca742f85291d5c556a28aebdf7a7.png)

## 样例 #1

### 输入

```
RBR
RGG
```

### 输出

```
5
```

## 样例 #2

### 输入

```
RGBB
BRRBRR
```

### 输出

```
19
```

## 样例 #3

### 输入

```
RRRRRRRRRR
RRRRRRRR
```

### 输出

```
8
```

# AI分析结果



**唯一算法分类**  
双指针与前缀和

---

### **综合分析与结论**

**核心思路**  
本题的核心在于通过双指针维护在第二个序列（t）中的可行区间，并结合预处理的前缀和数组快速排除特定不可达状态。关键点包括：
1. **双指针维护区间**：对每个位置i在第一个序列（s）中，确定第二个序列（t）中对应的最小（l）和最大（r）可达位置。
2. **不可达状态排除**：当s和t中相邻字符顺序相反（如s出现"RG"，t出现"GR"时），对应的状态不可达，需从总数中减去。
3. **前缀和优化**：预处理s中所有相邻字符对的出现次数，快速查询区间内需排除的状态数。

**算法流程**  
1. **预处理前缀和数组**：统计s中每对相邻字符的出现次数。
2. **双指针遍历**：维护t的可行区间[l, r]，每次遍历根据当前字符调整区间。
3. **统计并排除不可达状态**：对每个区间[l, r]，计算总长度并减去因顺序相反导致的不可达状态数。

**可视化设计思路**  
- **网格图模型**：将s和t的字符序列绘制为网格，可达状态在特定区间内，不可达状态用红色标记。
- **双指针动态更新**：高亮当前处理的s字符位置i，动态显示l和r的移动过程。
- **颜色标记**：绿色表示可达状态，红色表示不可达（AB-BA情况）。
- **复古像素动画**：采用8位风格网格，每次指令执行时播放音效，自动步进展示区间变化。

---

### **题解清单 (≥4星)**

1. **Cry_For_theMoon的解法（⭐️⭐️⭐️⭐️⭐️）**  
   - **亮点**：代码简洁高效，利用双指针维护区间，前缀和数组快速统计排除项。
   - **关键代码**：预处理相邻字符对，遍历时动态调整区间并减去不可达状态。

2. **王鲲鹏的解法（⭐️⭐️⭐️⭐️）**  
   - **亮点**：通过三维数组预处理t中的字符对，结合区间维护实现高效计算。
   - **关键优化**：动态维护l和r，避免重复计算。

3. **FlashHu的解法（⭐️⭐️⭐️⭐️）**  
   - **亮点**：网格图模型直观展示可达状态，数学证明排除不可达情况。
   - **个人心得**：通过反证法证明仅AB-BA情况不可达，减少冗余判断。

---

### **最优思路提炼**

1. **双指针维护区间**  
   - 初始化`l=1, r=1`，遍历s字符时动态调整t的可行区间。
   - 若当前字符匹配，扩展`r`至最远位置；若`l`匹配，逐步收缩左边界。

2. **前缀和预处理**  
   ```cpp
   int sum[3][3][MAXN]; // sum[x][y][i]表示s前i位中x后跟y的次数
   for (int i=2; i<=n; i++) {
       sum[x][y][i] = sum[x][y][i-1];
       if (s[i-1]==x && s[i]==y) sum[x][y][i]++;
   }
   ```

3. **排除不可达状态**  
   ```cpp
   if (i>1 && t[i]!=t[i-1]) {
       ans -= sum[t[i]][t[i-1]][r] - sum[t[i]][t[i-1]][l-1];
   }
   ```

---

### **同类型题推荐**

1. **最长公共子序列（洛谷P1439）**  
   - 动态规划与网格图模型，需处理字符匹配与状态转移。

2. **编辑距离（洛谷P2758）**  
   - 双指针与动态规划结合，维护状态矩阵。

3. **字符串的匹配（洛谷P3375）**  
   - KMP算法中的前缀函数与双指针优化。

---

### **代码片段**

**Cry_For_theMoon的核心实现**  
```cpp
for(int i=1, l=1, r=1; i<=m; i++){
    while(r+1 <=n && a[r]!=b[i]) r++;
    ans += r-l+1;
    if(i>1 && b[i]!=b[i-1]){
        ans -= qry(sum[b[i]*3 +b[i-1]], l, r);
    }
    if(a[l]==b[i] && l<=n) l++;
    if(r<n) r++;
}
```

---

### **可视化与复古动画**

1. **网格绘制**  
   - **Canvas绘制**：横向为s字符序列，纵向为t，每个单元格表示状态`(i,j)`。
   - **像素风格**：使用16色调色板，可达单元格为绿色，不可达为红色。

2. **动画流程**  
   - **步进执行**：按s字符顺序逐步扩展区间`[l, r]`，高亮当前处理的字符。
   - **音效触发**：移动指针时播放“滴”声，排除不可达状态时播放“嘟”声。

3. **交互设计**  
   - **控制面板**：支持暂停/继续、调节速度、重置。
   - **自动模式**：AI自动执行，模拟双指针移动与状态更新。

---
处理用时：138.52秒