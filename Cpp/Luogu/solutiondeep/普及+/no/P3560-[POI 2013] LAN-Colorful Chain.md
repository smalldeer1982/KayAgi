# 题目信息

# [POI 2013] LAN-Colorful Chain

## 题目描述

Little Bytie loves to play with colorful chains.

He already has quite an impressive collection, and some of them he likes    more than the others.

Each chain consists of a certain number of colorful links.

Byteasar has noticed that Bytie's sense of aesthetics is very precise.

It turns out that Bytie finds a contiguous fragment of a chain nice if    it contains exactly    ![](http://main.edu.pl/images/OI20/lan-en-tex.1.png) links of color ![](http://main.edu.pl/images/OI20/lan-en-tex.2.png) links of color ![](http://main.edu.pl/images/OI20/lan-en-tex.3.png) links of color ![](http://main.edu.pl/images/OI20/lan-en-tex.4.png),    and moreover it contains no links of other colors.

A chain's appeal is its number of (contiguous) fragments that are nice.

By trial and error, Byteasar has determined the values ![](http://main.edu.pl/images/OI20/lan-en-tex.5.png) and ![](http://main.edu.pl/images/OI20/lan-en-tex.6.png).

Now he would like to buy a new chain, and therefore asks you to write a program to aid him in shopping.

给定一个长度为 $n$ 的序列 $a$ 和 $m$ 个条件（每个条件中包含键 $c_i$ 和值 $l_i$），要求找出满足下列条件的子串的数量并输出：

 + 条件中存在键 $c_i$ 的，要求子串中 $c_i$ 恰好出现 $l_i$ 次。

 + 条件中不存在键 $c_i$ 的，要求子串中不出现 $c_i$。

先输入 $n$ 和 $m$，再输入 $m$ 个条件的 $l_i$，然后输入 $m$ 个条件的 $c_i$，最后输入 $a_i$。

## 说明/提示



### 数据范围：

对于 $100\%$ 的数据，$1\leq m\leq n \leq 10^6$，$1\leq a_i,b_i,c_i\leq n$。

## 样例 #1

### 输入

```
7 3
2 1 1
1 2 3
4 2 1 3 1 2 5
```

### 输出

```
2
```

# AI分析结果



**算法分类**: 滑动窗口/哈希

**综合分析**  
本题要求找出满足特定颜色出现次数且不含其他颜色的所有连续子串。题解主要分为哈希法和滑动窗口计数法两类：
1. **哈希法**：将颜色映射为哈希值，计算目标哈希（各颜色哈希乘对应次数之和），滑动窗口遍历检查哈希匹配。
2. **滑动窗口计数法**：维护窗口内颜色出现次数，通过计数器判断是否满足条件，同时处理非需求颜色的干扰。

**关键思路与优化**  
最优解法为滑动窗口结合计数器：
- **窗口长度固定**：子串长度必为 $\sum l_i$，窗口滑动时动态维护颜色计数。
- **双重条件校验**：需求颜色次数严格匹配且非需求颜色未出现，通过 `duo` 变量记录超限次数，确保窗口合法性。
- **时间复杂度**：严格 $O(n)$，每个元素进出窗口各一次。

**精选题解与评分**  

1. **xixisuper 的题解（5星）**  
   **亮点**：  
   - 维护 `duo` 变量跟踪超限颜色，高效处理非需求颜色出现情况。  
   - 代码简洁，逻辑清晰，通过双指针实现滑动窗口。  
   **核心代码**：  
   ```cpp
   int duo = 0, ans = 0, len = sum(l_i);
   for (int r = 1; r <= n; r++) {
       if (++cnt[a[r]] > ned[a[r]]) duo++;
       if (r - l + 1 > len) {
           if (--cnt[a[l]] >= ned[a[l]] && cnt[a[l]] == ned[a[l]]) duo--;
           l++;
       }
       ans += (duo == 0 && r - l + 1 == len);
   }
   ```

2. **huangrenheluogu 的题解（4星）**  
   **亮点**：  
   - 利用 `cnt` 变量统计满足条件的颜色数，直接判断是否全部匹配。  
   - 代码简洁，但需注意非需求颜色的隐式处理。  
   **核心代码**：  
   ```cpp
   void add(int x) {
       if (++cnt[a[x]] == ned[a[x]]) now++;
       if (cnt[a[x]] == ned[a[x]] + 1) now--;
   }
   void del(int x) {
       if (--cnt[a[x]] == ned[a[x]] - 1) now--;
       if (cnt[a[x]] == ned[a[x]]) now++;
   }
   ```

**同类题目推荐**  
1. [P3405 [USACO16OPEN] Cities and States S](https://www.luogu.com.cn/problem/P3405)（哈希映射）  
2. [P3661 [USACO17FEB] Why Did the Cow Cross the Road I S](https://www.luogu.com.cn/problem/P3661)（滑动窗口计数）  
3. [P2706 巧克力](https://www.luogu.com.cn/problem/P2706)（多维滑动窗口优化）

---
处理用时：90.52秒