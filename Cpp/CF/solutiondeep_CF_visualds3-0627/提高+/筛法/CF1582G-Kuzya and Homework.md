# 题目信息

# Kuzya and Homework

## 题目描述

Kuzya started going to school. He was given math homework in which he was given an array $ a $ of length $ n $ and an array of symbols $ b $ of length $ n $ , consisting of symbols '\*' and '/'.

Let's denote a path of calculations for a segment $ [l; r] $ ( $ 1 \le l \le r \le n $ ) in the following way:

- Let $ x=1 $ initially. For every $ i $ from $ l $ to $ r $ we will consequently do the following: if $ b_i= $ '\*', $ x=x*a_i $ , and if $ b_i= $ '/', then $ x=\frac{x}{a_i} $ . Let's call a path of calculations for the segment $ [l; r] $ a list of all $ x $ that we got during the calculations (the number of them is exactly $ r - l + 1 $ ).

For example, let $ a=[7, $ $ 12, $ $ 3, $ $ 5, $ $ 4, $ $ 10, $ $ 9] $ , $ b=[/, $ $ *, $ $ /, $ $ /, $ $ /, $ $ *, $ $ *] $ , $ l=2 $ , $ r=6 $ , then the path of calculations for that segment is $ [12, $ $ 4, $ $ 0.8, $ $ 0.2, $ $ 2] $ .

Let's call a segment $ [l;r] $ simple if the path of calculations for it contains only integer numbers.

Kuzya needs to find the number of simple segments $ [l;r] $ ( $ 1 \le l \le r \le n $ ). Since he obviously has no time and no interest to do the calculations for each option, he asked you to write a program to get to find that number!

## 样例 #1

### 输入

```
3
1 2 3
*/*```

### 输出

```
2```

## 样例 #2

### 输入

```
7
6 4 10 1 2 15 1
*/*/*//```

### 输出

```
8```

# AI分析结果



## 【算法分类】
**质因数分解 + 单调栈**

---

## **题解思路、算法要点与解决难点**

### **核心思路**
1. **质因数分解**：将每个数的质因数独立处理，乘操作视为增加质因数指数（左括号），除操作视为减少（右括号）。
2. **括号匹配**：对每个质因数，维护一个栈记录乘操作的位置。遇到除操作时，弹出栈顶元素，确定合法区间的左端点。
3. **区间统计**：用单调栈维护每个右端点对应的最小左端点，快速统计合法区间数。

### **解决难点**
- **质因数独立性**：每个质因数的合法性独立，需分别处理并取最严格的左端点约束。
- **高效维护栈结构**：分解质因数后，每个质因数的栈需动态维护，避免复杂度爆炸。
- **单调栈优化**：通过单调栈合并区间，统计合法区间的总数。

---

## **题解评分**
### **5星题解**
1. **Alex_Wei**  
   - **亮点**：代码简洁，直接维护质因数栈和单调栈，逻辑清晰。  
   - **关键代码**：  
     ```cpp
     for (int i = n; i; i--) {
         int nw = 1;
         while (top && pre[i] <= stc[top]) nw += w[top], top--;
         stc[++top] = pre[i], w[top] = nw;
         if (pre[i] == i) ans += nw;
     }
     ```
2. **泥土笨笨**  
   - **亮点**：详细注释和质因数分解预处理，适合理解实现细节。  
   - **关键代码**：  
     ```cpp
     void add(int x, int pos) {
         l[pos] = pos;
         while (x > 1) {
             pp[fac[x]].push_back(pos);
             x /= fac[x];
         }
     }
     ```

### **4星题解**
1. **Laoshan_PLUS**  
   - **亮点**：使用线性筛优化质因数分解，代码结构紧凑。  
   - **关键代码**：  
     ```cpp
     for (int i = n; i; i--) {
         long long res = 1;
         while (top && l[stk[top].first] >= l[i]) res += stk[top--].second;
         if (l[i] == i) ans += res;
         stk[++top] = {i, res};
     }
     ```

---

## **最优思路或技巧提炼**
1. **质因数独立处理**：将复杂问题拆解为多个独立子问题，降低复杂度。
2. **栈模拟括号匹配**：用栈记录质因数的乘操作位置，遇到除操作时弹出匹配。
3. **单调栈统计答案**：从右向左维护单调递增栈，合并区间并快速累加合法区间数。

---

## **同类型题或类似算法套路**
- **括号匹配问题**：如统计合法括号子串数目（LeetCode 32）。
- **区间最值维护**：如滑动窗口最大值（LeetCode 239）。
- **质因数分解应用**：如区间乘积的因子数统计（洛谷 P5282）。

---

## **推荐题目**
1. **洛谷 P1491**：区间乘积的质因数分解统计。
2. **LeetCode 76**：最小覆盖子串（类似滑动窗口优化）。
3. **Codeforces 1327E**：统计特定模式的子序列数目。

---

## **可视化与算法演示**
### **动画设计**
1. **质因数分解视图**：  
   - 每个质因数用不同颜色方块表示，乘操作时方块压入对应列，除操作时弹出。
   - **高亮**：当前操作的质因数栈变化，如弹出时显示红色闪烁。

2. **单调栈合并过程**：  
   - **步进显示**：从右向左扫描，动态合并区间并更新答案。
   - **颜色标记**：合法区间用绿色填充，合并时显示黄色边框。

3. **复古像素风格**：  
   - **8位音效**：栈压入/弹出时播放经典“哔”声，合法区间统计时播放胜利音效。
   - **Canvas 网格**：用像素块表示质因数的栈和单调栈状态。

### **交互控制**
- **速度调节**：滑块控制动画速度（0.5x~5x）。
- **单步执行**：按空格键逐帧观察质因数栈和单调栈变化。

---

## **代码实现（核心片段）**
```cpp
// 分解质因数并维护栈
void process(int i) {
    if (s[i] == '*') {
        int x = a[i];
        while (x > 1) {
            int p = fac[x];
            pp[p].push_back(i);
            x /= p;
        }
        l[i] = i;
    } else {
        int x = a[i];
        l[i] = i;
        while (x > 1) {
            int p = fac[x];
            if (pp[p].empty()) {
                l[i] = 0; break;
            }
            l[i] = min(l[i], pp[p].back());
            pp[p].pop_back();
            x /= p;
        }
    }
}

// 单调栈统计答案
long long ans = 0;
stack<Node> stk;
for (int i = n; i >= 1; i--) {
    long long cnt = 1;
    while (!stk.empty() && stk.top().min_l >= l[i]) {
        cnt += stk.top().cnt;
        stk.pop();
    }
    stk.push({l[i], cnt});
    if (l[i] == i) ans += cnt;
}
```

---
处理用时：75.37秒