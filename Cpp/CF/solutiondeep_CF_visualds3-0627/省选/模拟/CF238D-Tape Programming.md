# 题目信息

# Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7```

### 输出

```
0 1 0 1 0 0 0 0 0 0
2 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
2 3 2 1 0 0 0 0 0 0
```

# AI分析结果



---

### **1. 算法分类**  
**链表与并查集 + 预处理前缀和**

---

### **2. 题解思路与核心难点**  
#### **核心问题**  
直接模拟每个查询会超时，需设计高效预处理方法。关键在于利用指针移动的连续性，将动态删除的链表操作与方向切换的预处理结合，快速计算区间输出结果。  

#### **题解对比与算法要点**  
1. **作者 __gcd 的解法**  
   - **核心数据结构**：双向链表维护字符序列的动态删除，并查集处理向左移动时的区间赋值。  
   - **预处理数组**：  
     - `f[1][i][j]`：第一次向右到达 `i` 时数字 `j` 的输出次数。  
     - `f[0][i][j]`：第一次从 `i` 向左移动时数字 `j` 的输出次数。  
   - **关键优化**：  
     - 在指针移动过程中，动态删除字符并维护链表。  
     - 使用并查集跳过已处理的左移区间，避免重复计算。  

2. **作者 LinkyChristian 的解法**  
   - **核心思路**：预处理整个指针移动序列，记录左右方向的前缀和。  
   - **动态维护**：通过链表快速处理字符删除，记录 `left` 和 `right` 数组表示左右方向退出的输出次数。  

#### **解决难点**  
- **动态删除与移动同步**：链表实时更新字符序列，保证指针移动的合法性。  
- **区间快速查询**：通过预处理的前缀和数组，将区间查询转化为差值计算。  

---

### **3. 题解评分**  
- **作者 __gcd（★★★★☆）**  
  - **思路清晰度**：通过并查集巧妙处理左移赋值，逻辑严密。  
  - **代码可读性**：链表与并查集实现较复杂，但注释可提升可读性。  
  - **优化程度**：时间复杂度接近线性，适合大规模数据。  
- **作者 LinkyChristian（★★★☆☆）**  
  - **思路描述较模糊**，未提供完整代码，实践细节需自行推导。  

---

### **4. 最优思路与技巧提炼**  
#### **关键技巧**  
1. **链表维护动态序列**：用 `l[i]` 和 `r[i]` 数组表示前驱和后继，支持快速删除。  
2. **并查集跳过已处理区间**：向左移动时，通过并查集合并已赋值的节点，避免重复遍历。  
3. **方向敏感的前缀和**：分方向记录输出次数，解决区间方向切换的复杂性问题。  

#### **代码片段（核心逻辑）**  
```cpp  
void move(int &p, int &dir) {  
    int nxt;  
    if (isdigit(s[p])) {  
        // 输出数字并更新计数  
        b[s[p] - '0']++;  
        if (s[p] == '0') del(p);  
        else s[p]--;  
        nxt = (dir == 0) ? l[p] : r[p];  
    } else {  
        // 切换方向并删除多余符号  
        dir = (s[p] == '<') ? 0 : 1;  
        nxt = (dir == 0) ? l[p] : r[p];  
        if (!isdigit(s[nxt])) del(p);  
    }  
    // 更新预处理数组  
    if (dir == 1 && !vis[1][nxt]) {  
        for (int i = 0; i < 10; i++) f[1][nxt][i] = b[i];  
        vis[1][nxt] = 1;  
    }  
    if (dir == 0) {  
        // 并查集合并已处理节点  
        int j = find(nxt) + 1;  
        while (j <= p) {  
            vis[0][j] = 1;  
            for (int i = 0; i < 10; i++) f[0][j][i] = b[i];  
            unionn(j, j - 1);  
            j = find(j) + 1;  
        }  
    }  
    p = nxt;  
}  
```

---

### **5. 同类型题与算法套路**  
- **动态链表 + 并查集**：适用于需要高效处理动态删除与区间合并的场景。  
- **方向敏感的前缀和**：适用于路径依赖的模拟问题（如光线反射、机器人移动）。  

#### **推荐题目**  
1. **洛谷 P1540 [NOIP2010 提高组] 机器翻译**（链表维护缓存淘汰）。  
2. **洛谷 P2058 [NOIP2016 提高组] 海港**（滑动窗口与计数结合）。  
3. **洛谷 P2827 [NOIP2016 提高组] 蚯蚓**（链表模拟动态切割与合并）。  

---

### **6. 可视化设计**  
#### **动画方案**  
- **像素风格界面**：  
  - **网格布局**：用 8-bit 像素块表示字符序列，不同颜色区分 `<`、`>` 和数字。  
  - **指针高亮**：红色方块表示当前 CP，蓝色箭头表示 DP 方向。  
- **动态删除效果**：被删除的字符变为灰色并消失，链表连线实时更新。  
- **并查集合并演示**：向左移动时，已处理的区间用绿色覆盖，并查集路径用连线显示。  

#### **交互功能**  
- **步进控制**：支持暂停/继续、单步执行，观察每一步链表和并查集的变化。  
- **音效反馈**：  
  - 移动时播放“滴”声，删除时播放“咔嚓”声。  
  - 方向切换时播放不同音调。  

---

### **7. 总结**  
本题通过链表与并查集的高效结合，解决了动态删除和方向切换的复杂性问题。预处理方向敏感的前缀和数组，使得查询时间复杂度降至常数级。核心在于将路径依赖的模拟转化为静态数据的高效查询，这一思路在类似问题中具有广泛适用性。

---
处理用时：75.01秒