# 题目信息

# Queen

## 题目描述

You are given a rooted tree with vertices numerated from $ 1 $ to $ n $ . A tree is a connected graph without cycles. A rooted tree has a special vertex named root.

Ancestors of the vertex $ i $ are all vertices on the path from the root to the vertex $ i $ , except the vertex $ i $ itself. The parent of the vertex $ i $ is the nearest to the vertex $ i $ ancestor of $ i $ . Each vertex is a child of its parent. In the given tree the parent of the vertex $ i $ is the vertex $ p_i $ . For the root, the value $ p_i $ is $ -1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/767631fbfbd5e834691c335a1beebc4c83722771.png)An example of a tree with $ n=8 $ , the root is vertex $ 5 $ . The parent of the vertex $ 2 $ is vertex $ 3 $ , the parent of the vertex $ 1 $ is vertex $ 5 $ . The ancestors of the vertex $ 6 $ are vertices $ 4 $ and $ 5 $ , the ancestors of the vertex $ 7 $ are vertices $ 8 $ , $ 3 $ and $ 5 $ You noticed that some vertices do not respect others. In particular, if $ c_i = 1 $ , then the vertex $ i $ does not respect any of its ancestors, and if $ c_i = 0 $ , it respects all of them.

You decided to delete vertices from the tree one by one. On each step you select such a non-root vertex that it does not respect its parent and none of its children respects it. If there are several such vertices, you select the one with the smallest number. When you delete this vertex $ v $ , all children of $ v $ become connected with the parent of $ v $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/fa2af41e1e599c9e51ca9e3edafbee94d578e807.png)An example of deletion of the vertex $ 7 $ .Once there are no vertices matching the criteria for deletion, you stop the process. Print the order in which you will delete the vertices. Note that this order is unique.

## 说明/提示

The deletion process in the first example is as follows (see the picture below, the vertices with $ c_i=1 $ are in yellow):

- first you will delete the vertex $ 1 $ , because it does not respect ancestors and all its children (the vertex $ 2 $ ) do not respect it, and $ 1 $ is the smallest index among such vertices;
- the vertex $ 2 $ will be connected with the vertex $ 3 $ after deletion;
- then you will delete the vertex $ 2 $ , because it does not respect ancestors and all its children (the only vertex $ 4 $ ) do not respect it;
- the vertex $ 4 $ will be connected with the vertex $ 3 $ ;
- then you will delete the vertex $ 4 $ , because it does not respect ancestors and all its children (there are none) do not respect it ([vacuous truth](https://en.wikipedia.org/wiki/Vacuous_truth));
- you will just delete the vertex $ 4 $ ;
- there are no more vertices to delete.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/ebd0eb4e79b93258618d042cf4204608334ae632.png)In the second example you don't need to delete any vertex:

- vertices $ 2 $ and $ 3 $ have children that respect them;
- vertices $ 4 $ and $ 5 $ respect ancestors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/301d90419aa6803a28893c2a81f56219871e0793.png)In the third example the tree will change this way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/7676abdd5b6383c016cad416ee32ca622873b718.png)

## 样例 #1

### 输入

```
5
3 1
1 1
-1 0
2 1
3 0
```

### 输出

```
1 2 4 
```

## 样例 #2

### 输入

```
5
-1 0
1 1
1 1
2 0
3 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8
2 1
-1 0
1 0
1 1
1 1
4 0
5 1
7 0
```

### 输出

```
5 
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Queen 深入学习指南 💡

<introduction>
今天我们来一起分析“Queen”这道C++编程题。这道题涉及树结构的条件判断与节点删除规则，通过本指南，你将理解题目核心逻辑，掌握关键解题技巧，并通过可视化动画直观感受算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（侧重树结构的条件判断与预处理）

🗣️ **初步分析**：
解决“Queen”问题的关键在于理解节点删除的两个核心条件：节点本身不尊重父节点（`c_i=1`），且其所有子节点都不尊重它（即子节点的`c_j`全为1）。这类问题不需要复杂的搜索或动态规划，而是通过预处理和条件判断直接筛选符合条件的节点。

- **题解思路**：所有优质题解均采用“预处理+条件判断”的思路：用数组记录每个节点的`c_i`（是否不尊重父节点），并用另一个数组记录其所有子节点的`c_j`是否全为1（通过与运算或统计子节点`c_j`的和）。最后遍历所有节点，筛选出满足两个条件的节点，按编号从小到大输出。
- **核心难点**：如何高效判断“所有子节点都不尊重当前节点”。优质题解通过预处理（如与运算）避免了重复遍历子节点。
- **可视化设计思路**：用像素网格表示树结构，每个节点用方块表示，颜色区分`c_i`（红色为1，绿色为0）。动画中高亮满足条件的节点，并用箭头展示子节点与父节点的连接关系。关键步骤（如与运算判断子节点是否全为1）用文字气泡解释。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下题解（评分≥4星）值得重点学习：
</eval_intro>

**题解一：作者Zq_water**
* **点评**：此题解思路简洁直接，通过两个数组`a`和`b`分别记录“子节点是否全不尊重当前节点”和“当前节点是否不尊重父节点”。代码中`a[x]&=y`巧妙利用与运算特性（全1则1，否则0），高效完成子节点条件判断。变量命名清晰（如`a`表示子节点条件，`b`表示自身条件），边界处理严谨（`x!=-1`防止数组越界）。实践价值高，可直接用于竞赛。

**题解二：作者bigclever**
* **点评**：此题解与Zq_water思路一致，但代码更简洁。初始化`a[i]=1`（与运算初始值正确），输入时同步更新`a`和`b`数组，最后遍历输出。代码逻辑直白，无冗余操作，非常适合初学者理解核心逻辑。

**题解三：作者songhongyi**
* **点评**：此题解明确将问题抽象为两个布尔条件，用`a`数组记录子节点是否全不尊重（逻辑与），`b`数组记录自身是否不尊重父节点。代码注释清晰，时间复杂度为O(n)，是高效的典型实现。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决本题时，以下三个关键点需要特别注意：
</difficulty_intro>

1.  **关键点1：如何判断“所有子节点都不尊重当前节点”？**
    * **分析**：对于每个节点`x`，需要检查其所有子节点的`c_j`是否全为1。直接遍历子节点会增加时间复杂度，优质题解通过“与运算”优化：初始化`a[x]=1`，每读入一个子节点`i`（父节点为`x`），执行`a[x] &= c[i]`（若存在子节点`c[i]=0`，则`a[x]`变为0）。最终`a[x]=1`表示所有子节点都不尊重`x`。
    * 💡 **学习笔记**：与运算（`&=`）是处理“全满足”条件的高效技巧，初始值设为1可确保未处理子节点时条件成立。

2.  **关键点2：如何处理根节点？**
    * **分析**：根节点的父节点为-1，题目规定根节点不会被删除（因为其没有父节点，无法满足“不尊重父节点”的条件）。代码中通过`x!=-1`跳过根节点的子节点条件更新。
    * 💡 **学习笔记**：根节点的特殊属性需在代码中显式处理，避免数组越界或逻辑错误。

3.  **关键点3：如何确保输出顺序正确？**
    * **分析**：题目要求按编号从小到大输出可删除节点。优质题解直接按`i=1`到`n`遍历，自然保证了顺序，无需额外排序。
    * 💡 **学习笔记**：当条件满足“编号最小优先”时，顺序遍历是最简洁的实现方式。

### ✨ 解题技巧总结
<summary_best_practices>
- **预处理替代遍历**：用与运算预处理子节点条件，避免多次遍历子节点，降低时间复杂度。
- **边界条件显式处理**：根节点的父节点为-1，需在输入时跳过其更新，防止数组越界。
- **初始化保证逻辑正确**：与运算的初始值设为1，确保未处理子节点时条件成立（无子节点时默认满足“全不尊重”）。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，结合了代码简洁性和逻辑清晰性：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Zq_water、bigclever等题解的思路，通过预处理子节点条件和自身条件，高效筛选可删除节点。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    using namespace std;

    const int MAXN = 1e5 + 5;
    bool a[MAXN]; // a[x]表示x的所有子节点是否都不尊重x（全为1）
    bool b[MAXN]; // b[i]表示节点i是否不尊重父节点（c_i=1）

    int main() {
        int n;
        cin >> n;
        memset(a, 1, sizeof(a)); // 初始化为1，与运算的初始值

        for (int i = 1; i <= n; ++i) {
            int p_i, c_i;
            cin >> p_i >> c_i;
            b[i] = c_i; // 记录节点i是否不尊重父节点
            if (p_i != -1) { // 非根节点，更新其父节点的子节点条件
                a[p_i] &= c_i; // 父节点p_i的子节点i的c_i=1时，a[p_i]保持1；否则变为0
            }
        }

        bool has_ans = false;
        for (int i = 1; i <= n; ++i) {
            if (b[i] && a[i]) { // 满足两个条件
                cout << i << " ";
                has_ans = true;
            }
        }

        if (!has_ans) {
            cout << "-1";
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先初始化`a`数组为1（所有节点初始假设子节点全为1），然后读取每个节点的父节点和`c_i`值，更新`b`数组（记录自身是否不尊重父节点）和`a`数组（记录父节点的子节点是否全为1）。最后遍历所有节点，输出满足`b[i]&&a[i]`的节点，若没有则输出-1。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者Zq_water**
* **亮点**：用`a[x]&=y`高效处理子节点全为1的条件，代码简洁。
* **核心代码片段**：
    ```cpp
    for(ll i=1,x,y;i<=n;i++){
        scanf("%lld %lld",&x,&y);
        if(x!=-1) a[x]&=y,b[i]=y;
    }
    ```
* **代码解读**：
    > 输入时，若当前节点的父节点`x`不是-1（非根节点），则执行`a[x]&=y`：`y`是当前节点的`c_i`值（1或0）。与运算的特性是，只要有一个`y=0`，`a[x]`就会变为0（表示存在子节点尊重父节点`x`）。`b[i]=y`记录当前节点是否不尊重父节点。
* 💡 **学习笔记**：与运算在“全满足”条件判断中非常高效，避免了遍历子节点的开销。

**题解二：作者songhongyi**
* **亮点**：明确将问题抽象为两个布尔条件，代码逻辑清晰。
* **核心代码片段**：
    ```cpp
    memset( a, 1, sizeof( a ) );
    for ( int i = 1; i <= n; i++ ) {
        int x, y;
        cin >> x >> y;
        if ( x != -1 ) {
            a[ x ] &= y;
            b[ i ] = y;
        }
    }
    ```
* **代码解读**：
    > `memset(a,1,sizeof(a))`初始化`a`数组为1（所有节点初始假设子节点全为1）。输入时，若父节点`x`有效（非根），则用`a[x]&=y`更新子节点条件，`b[i]=y`记录自身条件。这一步是核心预处理。
* 💡 **学习笔记**：初始化是预处理的关键，正确的初始值能保证后续运算的逻辑正确。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“子节点全为1”和“自身不尊重父节点”的判断过程，我们设计一个8位像素风格的动画，名为“树精灵的删除游戏”。
</visualization_intro>

  * **动画演示主题**：树精灵的删除游戏（8位像素风格）

  * **核心演示内容**：展示每个节点的`c_i`值（红色表示1，绿色表示0），通过与运算判断子节点是否全为1，高亮满足条件的节点并按顺序删除。

  * **设计思路简述**：8位像素风格（如FC游戏画面）降低学习压力，颜色标记（红/绿）直观区分`c_i`值。关键操作（与运算、条件判断）用音效和文字气泡提示，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧为树结构（像素方块表示节点，根节点在顶部，子节点向下延伸），右侧为控制面板（开始/暂停、单步、重置按钮，速度滑块）。
          * 节点颜色：红色（`c_i=1`）、绿色（`c_i=0`）。

    2.  **预处理阶段**：
          * 输入每个节点的父节点和`c_i`值，用像素箭头从子节点指向父节点，同时更新父节点的`a`数组值（显示为父节点旁的数字1或0）。

    3.  **条件判断阶段**：
          * 遍历节点`i=1`到`n`，当前节点用黄色边框高亮。
          * 检查`b[i]`（自身颜色是否为红）和`a[i]`（父节点旁数字是否为1）。若都满足，节点变为金色，加入删除队列。

    4.  **删除动画**：
          * 按顺序删除金色节点（编号从小到大），子节点像素方块“跳跃”到父节点下方，用虚线表示原连接。
          * 每删除一个节点，播放“叮”的音效（8位合成音）。

    5.  **结果展示**：
          * 所有删除节点显示在屏幕底部，若没有则显示“-1”，并播放“呜”的提示音效。

  * **旁白提示**：
      * “看！红色节点表示不尊重父节点哦~”
      * “父节点旁的数字是1，说明它的子节点都不尊重它！”
      * “金色节点满足条件，要被删除啦~”

<visualization_conclusion>
通过这个动画，你可以直观看到每个节点的`c_i`值如何影响父节点的`a`数组，以及条件判断的具体过程，轻松理解核心逻辑！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的关键是树结构的条件预处理与判断，类似的思路可迁移到其他树结构问题中：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 树结构的条件统计（如统计子节点的某种属性是否全满足）。
      * 预处理替代多次遍历（如用与运算、求和等统计子节点属性）。
      * 按编号顺序处理节点（保证结果顺序正确）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1364 医院设置**：考察树结构的距离统计，需要预处理子节点数量和距离总和。
    2.  **洛谷 P1270 “访问”美术馆**：树结构的动态规划，需处理子节点的时间限制。
    3.  **洛谷 P2015 二叉苹果树**：树结构的背包问题，需统计子节点的苹果数量。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到调试时的教训，例如忘记处理“无节点可删除”的情况（输出-1）。以下是典型经验：
</insights_intro>

> **参考经验 (来自作者ys_kylin__)**：“我第一次提交时忘记处理无节点的情况，导致五连WA。一定要记得最后检查是否有符合条件的节点，没有则输出-1！”

**点评**：这个经验非常实用！在编程中，边界条件（如空输入、无结果）的处理往往是易错点。建议在代码中显式设置标志变量（如`has_ans`），最后根据标志输出结果，避免遗漏。

---

<conclusion>
本次关于“Queen”的C++解题分析就到这里。通过理解条件判断的核心逻辑、学习优质题解的预处理技巧，以及观看像素动画，相信你已掌握此类问题的解决方法。记得多练习类似题目，巩固所学知识！下次见~ 💪
</conclusion>

---
处理用时：188.76秒