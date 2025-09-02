# 题目信息

# Two Permutations (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions is that you do not have to minimize the number of operations in this version. You can make hacks only if both versions of the problem are solved.

You have two permutations $ ^{\dagger} $ $ p_{1}, p_{2}, \ldots, p_{n} $ (of integers $ 1 $ to $ n $ ) and $ q_{1}, q_{2}, \ldots, q_{m} $ (of integers $ 1 $ to $ m $ ). Initially $ p_{i}=a_{i} $ for $ i=1, 2, \ldots, n $ , and $ q_{j} = b_{j} $ for $ j = 1, 2, \ldots, m $ . You can apply the following operation on the permutations several (possibly, zero) times.

In one operation, $ p $ and $ q $ will change according to the following three steps:

- You choose integers $ i $ , $ j $ which satisfy $ 1 \le i \le n $ and $ 1 \le j \le m $ .
- Permutation $ p $ is partitioned into three parts using $ p_i $ as a pivot: the left part is formed by elements $ p_1, p_2, \ldots, p_{i-1} $ (this part may be empty), the middle part is the single element $ p_i $ , and the right part is $ p_{i+1}, p_{i+2}, \ldots, p_n $ (this part may be empty). To proceed, swap the left and the right parts of this partition. Formally, after this step, $ p $ will become $ p_{i+1}, p_{i+2}, \ldots, p_{n}, p_{i}, p_{1}, p_{2}, \ldots, p_{i-1} $ . The elements of the newly formed $ p $ will be reindexed starting from $ 1 $ .
- Perform the same transformation on $ q $ with index $ j $ . Formally, after this step, $ q $ will become $ q_{j+1}, q_{j+2}, \ldots, q_{m}, q_{j}, q_{1}, q_{2}, \ldots, q_{j-1} $ . The elements of the newly formed $ q $ will be reindexed starting from $ 1 $ .

Your goal is to simultaneously make $ p_{i}=i $ for $ i=1, 2, \ldots, n $ , and $ q_{j} = j $ for $ j = 1, 2, \ldots, m $ .

Find any valid way to achieve the goal using at most $ 10\,000 $ operations, or say that none exists. Please note that you do not have to minimize the number of operations.

It can be proved that if it is possible to achieve the goal, then there exists a way to do so using at most $ 10\,000 $ operations.

 $ ^{\dagger} $ A permutation of length $ k $ is an array consisting of $ k $ distinct integers from $ 1 $ to $ k $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ k=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first example, we can achieve the goal within $ 2 $ operations:

1. In the first operation, choose $ i = 3 $ , $ j = 4 $ . After this, $ p $ becomes $ [3, 2, 1] $ and $ q $ becomes $ [3, 4, 5, 2, 1] $ .
2. In the second operation, choose $ i = 2 $ , $ j = 4 $ . After this, $ p $ becomes $ [1, 2, 3] $ and $ q $ becomes $ [1, 2, 3, 4, 5] $ .

In the third example, it is impossible to achieve the goal.

## 样例 #1

### 输入

```
3 5
2 1 3
5 2 1 4 3```

### 输出

```
2
3 4
2 4```

## 样例 #2

### 输入

```
4 4
3 4 2 1
2 4 1 3```

### 输出

```
5
4 2
3 3
1 4
3 2
4 1```

## 样例 #3

### 输入

```
2 2
1 2
2 1```

### 输出

```
-1```

# AI分析结果

---
# 💡 Kay的C++算法解析：Two Permutations (Easy Version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Two Permutations (Easy Version)”这道构造性C++编程题。这道题的关键在于通过特定操作将两个排列同时变为有序，难点在于构造操作序列并处理奇偶性问题。本指南将帮你理清思路，掌握核心技巧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（构造性算法）`

🗣️ **初步分析**：
解决这道题的核心在于构造操作序列，通过特定操作将两个排列同时排序。构造性算法的核心思想是“设计步骤”——就像拼拼图时，先确定关键块的位置，再逐步调整其他部分。本题中，我们需要：
1. 对单个排列设计操作序列使其有序；
2. 调整两个操作序列的长度，使其次数相同；
3. 处理奇偶性差异，确保存在可行解。

**核心思路对比**：多数题解采用“三次操作交换两元素”的方法（如xkcdjerry），通过类似冒泡排序的方式将排列排序。部分题解（如Milmon）则用“环分解”模型，但Easy版本更适合前一种方法。所有题解均强调调整操作次数的奇偶性，利用逆序对奇偶性证明无解情况（当n、m均为偶数且操作次数奇偶性不同时）。

**可视化设计思路**：设计一个8位像素动画，用不同颜色块表示排列元素。每次操作时，展示数组左右交换的过程（如左边块滑到右边，右边块滑到左边），操作位置用闪烁箭头标记。操作序列调整时，用“添加冗余操作”的动画（如重复添加(1,n)操作），并通过音效（“叮”声）提示关键步骤。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和实践价值，以下题解值得重点学习：
</eval_intro>

**题解一：xkcdjerry（赞：12）**
* **点评**：此题解思路清晰，首先通过“三次操作交换两元素”的方法排序单个排列（最多3(n-1)次操作），再通过添加冗余操作调整两序列长度，最后处理奇偶性差异。代码虽有重复（复制粘贴处理p和q），但变量命名直观（如s1、s2存储操作序列），边界处理严谨（如检查n、m奇偶性）。亮点在于“三次交换”的构造方法和奇偶性调整策略，是构造性算法的典型应用。

**题解二：nullqtr_pwp（赞：1）**
* **点评**：此题解提供了具体的交换函数（swapa、swapb），并详细处理了操作序列的调整。代码结构模块化（虽然未完全封装函数，但逻辑清晰），通过维护位置数组（p、q）快速定位元素，提升了效率。亮点在于“交换两元素”的具体实现和奇偶性调整的条件判断（如n为奇数时添加n次操作）。

**题解三：spdarkle（赞：0）**
* **点评**：此题解补充了逆序对奇偶性的证明，解释了“n、m均为偶数且操作次数奇偶性不同时无解”的原因。虽未提供完整代码，但理论分析增强了题解的严谨性，帮助理解构造的底层逻辑。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于构造操作序列和处理奇偶性。以下是关键步骤和应对策略：
</difficulty_intro>

1.  **关键点1：如何将单个排列排序？**
    * **分析**：通过“三次操作交换两元素”的方法。例如，对于元素i和j（i<j），选择i-1、j-i-1、n-j位置操作，可交换i和j的位置（类似AxByC→ByCxA→CxAyB→AyBxC）。重复此过程，将每个元素归位。
    * 💡 **学习笔记**：构造交换操作是排序的基础，三次操作可实现两元素交换，总次数不超过3(n-1)。

2.  **关键点2：如何调整两操作序列的长度？**
    * **分析**：若两序列长度不同，短的一方可添加冗余操作（如重复(1,n)操作，每次操作后排列不变）。例如，对有序排列执行(1,n)操作两次，排列恢复原状，因此可通过添加偶数次操作调整长度。
    * 💡 **学习笔记**：冗余操作是调整长度的关键，需确保添加的操作不影响排列的有序性。

3.  **关键点3：如何处理奇偶性差异？**
    * **分析**：若两序列长度奇偶性不同，需利用n或m的奇偶性。若n为奇数，可在p的操作序列中添加n次(1)操作（n次操作后p不变，但长度奇偶性改变）；同理m为奇数时处理q。若n、m均为偶数，则无解（逆序对奇偶性矛盾）。
    * 💡 **学习笔记**：奇偶性调整依赖排列长度的奇偶性，需结合逆序对理论判断是否存在解。

### ✨ 解题技巧总结
- **问题分解**：先解决单个排列的排序，再处理两序列的同步问题。
- **冗余操作**：利用不影响排列的操作调整序列长度（如(1,n)操作两次）。
- **奇偶性判断**：通过逆序对奇偶性理论快速判断无解情况（n、m均为偶数且操作次数奇偶性不同）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解的通用核心实现，结合了排序和调整步骤：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了xkcdjerry和nullqtr_pwp的思路，实现了单个排列的排序、操作序列调整和奇偶性处理。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 3005;

    void sort_perm(int* a, int n, vector<int>& ops) {
        for (int i = 1; i <= n; ++i) {
            if (a[i] == i) continue;
            int j = i;
            while (a[j] != i) j++; // 找到i的位置
            // 三次操作交换i和j
            int l1 = i - 1, l2 = j - i - 1, l3 = n - j;
            ops.push_back(l1 + 1); // 第一次操作位置
            ops.push_back(l2 + 1); // 第二次操作位置
            ops.push_back(l3 + 1); // 第三次操作位置
            swap(a[i], a[j]); // 模拟交换后数组状态
        }
    }

    int main() {
        int n, m, a[MAXN], b[MAXN];
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= m; ++i) cin >> b[i];

        vector<int> ops_p, ops_q;
        sort_perm(a, n, ops_p); // 排序p
        sort_perm(b, m, ops_q); // 排序q

        // 调整奇偶性
        if ((ops_p.size() / 3) % 2 != (ops_q.size() / 3) % 2) {
            if (n % 2) for (int i = 0; i < n; ++i) ops_p.push_back(1);
            else if (m % 2) for (int i = 0; i < m; ++i) ops_q.push_back(1);
            else { cout << -1 << endl; return 0; }
        }

        // 调整长度相等
        while (ops_p.size() < ops_q.size()) {
            ops_p.push_back(1); ops_p.push_back(n);
        }
        while (ops_q.size() < ops_p.size()) {
            ops_q.push_back(1); ops_q.push_back(m);
        }

        // 输出结果
        cout << ops_p.size() / 3 << endl;
        for (size_t i = 0; i < ops_p.size(); i += 3) {
            cout << ops_p[i] << " " << ops_q[i] << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先通过`sort_perm`函数对单个排列排序（三次操作交换两元素），然后调整两操作序列的奇偶性和长度，最后输出结果。关键函数`sort_perm`通过循环找到目标元素位置，构造三次操作交换，确保排列有序。

---
<code_intro_selected>
以下是优质题解的核心片段赏析：
</code_intro_selected>

**题解一：xkcdjerry**
* **亮点**：三次操作交换两元素的构造方法，代码直接模拟交换过程。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++) {
        if(a[i]==i) continue;
        for(int j=i;j<=n;j++) if(a[j]==i) {
            int l1=i-1,l2=j-i-1,l3=n-j;
            s1[t1++]=l1+1;
            s1[t1++]=l2+1;
            s1[t1++]=l3+1;
            swap(a[i],a[j]);
            break;
        }
    }
    ```
* **代码解读**：外层循环遍历每个位置i，若a[i]已为i则跳过。内层循环找到i的当前位置j，计算三个操作位置（l1+1、l2+1、l3+1），将这三个位置存入操作序列s1，并交换a[i]和a[j]（模拟操作后的数组状态）。这一步是“三次交换两元素”的具体实现。
* 💡 **学习笔记**：通过三次操作交换两元素是排序的核心，需注意操作位置的计算（基于左、中、右三段的长度）。

**题解二：nullqtr_pwp**
* **亮点**：维护位置数组快速定位元素，提升效率。
* **核心代码片段**：
    ```cpp
    F(i,1,n) {
        F(j,1,n) p[a[j]]=j; // 维护位置数组p
        if(i==p[i]) continue;
        swapa(i,p[i]); // 交换i和p[i]
    }
    ```
* **代码解读**：通过双重循环维护位置数组p（p[x]表示值x的当前位置），快速找到i的位置p[i]，调用swapa函数交换i和p[i]。位置数组的维护避免了每次遍历查找，提升了效率。
* 💡 **学习笔记**：维护辅助数组（如位置数组）是优化查找的常用技巧，可避免重复遍历。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解操作对排列的影响，我们设计一个“像素交换小能手”8位风格动画，展示操作过程和序列调整！
</visualization_intro>

  * **动画演示主题**：`像素排列大冒险`
  * **核心演示内容**：展示单个排列的排序过程（三次操作交换两元素），以及操作序列的调整（添加冗余操作、奇偶性调整）。
  * **设计思路简述**：采用FC红白机风格，用不同颜色的像素块表示排列元素（如红色块代表未归位元素，绿色块代表已归位）。操作时，选中位置用闪烁箭头标记，左右交换过程用像素块滑动动画展示，冗余操作添加时用“+”图标提示。音效方面，每次操作播放“叮”声，完成排序时播放“胜利”音效。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：屏幕分为左右两部分，分别显示排列p和q的像素块（如3x3网格），操作序列显示在下方（白色像素文字）。控制面板包含“单步”、“自动播放”按钮和速度滑块。
    2. **排序过程**：
        - 单步执行时，选中元素i（红色闪烁），找到其当前位置j（蓝色闪烁），三次操作依次执行：
          - 第一次操作：左边块（p[1..i-1]）滑到右边，中间块（p[i]）和右边块（p[i+1..n]）滑到左边，伴随“叮”声。
          - 第二、三次操作类似，最终i和j交换位置（变为绿色）。
    3. **调整操作序列**：
        - 若两序列长度不同，短的一方添加(1,n)操作：像素块滑动两次后恢复原状（绿色闪烁），操作序列末尾添加“(1,n)”（黄色文字）。
        - 奇偶性调整时，若n为奇数，p的操作序列添加n次(1)操作：像素块循环滑动n次后恢复，操作序列长度增加（红色文字提示奇偶性改变）。
    4. **完成状态**：两排列均变为全绿，操作序列长度相同，播放“胜利”音效，显示“成功！”像素文字。

  * **旁白提示**：
    - “看！红色块是还没归位的元素，我们需要用三次操作交换它们～”
    - “现在添加(1,n)操作，排列不会改变，但操作序列长度增加啦！”
    - “当n是奇数时，添加n次(1)操作可以改变奇偶性哦！”

<visualization_conclusion>
通过这个像素动画，我们能直观看到操作如何改变排列，以及调整操作序列的过程，轻松掌握构造性算法的核心！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
构造性算法的核心是“设计步骤”，以下是相关拓展练习：
</similar_problems_intro>

  * **通用思路迁移**：本题的构造方法（交换两元素、添加冗余操作）可用于其他排列操作问题，例如：
    - 循环移位排列的排序；
    - 多排列同步操作的构造；
    - 带限制的排列变换问题（如每次操作类型固定）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1115 最大子段和**  
       🗣️ **推荐理由**：虽然是动态规划题，但构造“子段”的思路与本题构造操作序列类似，需设计步骤逐步求解。
    2.  **洛谷 P1097 统计数字**  
       🗣️ **推荐理由**：考察对数据的排序和调整，与本题的排列排序思路相关。
    3.  **洛谷 P1908 逆序对**  
       🗣️ **推荐理由**：涉及逆序对的计算，与本题的逆序对奇偶性理论密切相关，可加深对构造条件的理解。

---

## 7\. 学习心得与经验分享

<insights_intro>
题解中多位作者提到调试时的经验，例如：
</insights_intro>

> **参考经验 (来自 nullqtr_pwp)**：“原代码被同机房大佬 hack，此版代码无锅。”  
> **点评**：这提醒我们，构造性算法的代码需严格测试边界条件（如i=j时不交换），并通过样例验证。调试时可打印中间数组状态，快速定位错误。

---

<conclusion>
本次关于“Two Permutations (Easy Version)”的分析就到这里。构造性算法的关键在于“设计步骤”，通过交换、调整等操作达到目标。希望大家通过练习，掌握这类问题的构造技巧！下次见～💪
</conclusion>

---

---
处理用时：123.51秒