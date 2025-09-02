# 题目信息

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# AI分析结果



# **Multicolored Markers 题解分析**

---

## **唯一算法分类**
**数论**

---

## **题解思路、算法要点与解决难点**

### **核心思路**
- **问题转化**：将总块数 $a+b$ 分解为矩形 $i \times j$，并检查是否至少存在一个颜色（a或b）的块数能分解为子矩形嵌入其中。
- **数学优化**：利用因数分解与贪心策略，从 $\sqrt{a+b}$ 向下枚举大矩形短边 $i$，确保快速找到最小周长的合法解。

### **关键公式与推导**
- **周长公式**：$2(i + \frac{a+b}{i})$，当 $i$ 接近 $\sqrt{a+b}$ 时周长最小。
- **因数约束**：对于颜色块数 $x$（x为a或b），若存在因数对 $(p,q)$ 满足 $p \leq i$ 且 $q \leq \frac{a+b}{i}$，则合法。

### **解决难点**
1. **高效枚举**：直接遍历所有因数会超时，需预处理颜色的因数并优化查找过程。
2. **剪枝策略**：预处理a的因数后，用指针从大到小移动，避免重复检查。
3. **复杂度控制**：Siyuan题解的时间复杂度为 $O(\sqrt{a} + \sqrt{a+b})$，显著优于暴力枚举。

---

## **题解评分 (≥4星)**

### **Siyuan (★★★★★)**
- **思路清晰**：明确枚举大矩形短边，预处理因数后用指针高效验证。
- **代码高效**：预处理因数后仅需单次遍历，时间复杂度最优。
- **优化显著**：指针移动剪枝避免重复计算。

### **Bring (★★★★☆)**
- **代码简洁**：直接维护最大因数，无需预处理。
- **实时剪枝**：在枚举过程中动态调整因数，减少无效检查。

### **guanyf (★★★★☆)**
- **动态优化**：通过指针记录当前最大因数，逐步缩小搜索范围。
- **代码可读**：逻辑清晰，适合快速理解核心思路。

---

## **最优思路或技巧提炼**
- **预处理+指针剪枝**：预处理颜色块数的因数列表，枚举大矩形时用指针从后向前查找最大合法因数。
- **降序贪心枚举**：从 $\sqrt{a+b}$ 向下枚举大矩形短边，确保首次合法解即为最优。
- **数学性质利用**：利用「因数对乘积固定时，差越小和越小」的性质，快速锁定最小周长。

---

## **同类型题及算法套路**
- **常见套路**：因数分解 + 贪心枚举，广泛用于面积/周长优化问题。
- **类似题目**：
  1. **洛谷 P1072**（Hankson的趣味题，因数分解与约束条件）
  2. **洛谷 P1361**（最小矩形覆盖，几何+因数分解）
  3. **洛谷 P1463**（反素数，因数性质与枚举优化）

---

## **推荐洛谷题目**
1. **P1072**：考察因数分解与约束条件验证。
2. **P1516**：同余方程与数论优化。
3. **P1463**：因数性质与贪心枚举的结合。

---

## **个人心得摘录**
- **调试教训**：初始暴力枚举会TLE，必须预处理因数（如Xiao_mo题解的预处理数组）。
- **思维突破**：意识到大矩形的短边只需枚举到 $\sqrt{a+b}$，避免无效长边计算。

---

## **可视化与算法演示**
### **动画设计**
1. **像素风格界面**：  
   - **Canvas 绘制**：大矩形用蓝色边框，子矩形用红色/绿色填充。  
   - **当前枚举步骤**：高亮大矩形的短边 $i$，并显示当前周长值。
2. **音效交互**：  
   - **成功音效**：当找到合法解时播放8-bit胜利音效。  
   - **步进音效**：每枚举一个 $i$ 时触发短促“滴”声。
3. **自动推导模式**：  
   - 模拟AI从 $\sqrt{a+b}$ 逐步向下检查，动态显示因数指针移动过程。

### **代码片段（关键逻辑）**
```cpp
// Siyuan 题解核心代码
vector<int> f;
for(int i=1; i*i <= a; ++i) if(a%i == 0) f.push_back(i);
int p = f.size() - 1;
for(int i = sqrt(tot); i >=1; --i) {
    if(tot % i) continue;
    while(f[p] > i) --p; // 指针剪枝
    if(a/f[p] <= tot/i) return 2*(i + tot/i);
}
```

---

## **总结**
本题核心在于将几何问题转化为数论中的因数分解，通过预处理与贪心策略高效求解。最优解法通过降序枚举与指针剪枝，显著优化时间复杂度至 $O(\sqrt{a})$。可视化设计可结合像素动画与音效，直观展示枚举与验证过程。

---
处理用时：78.26秒