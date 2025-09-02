# 题目信息

# Rollbacks (Easy Version)

## 题目描述

This is an easy version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?```

### 输出

```
2
0```

# AI分析结果


### 💡 Kay的C++算法解析：Rollbacks (Easy Version) 深入学习指南 💡

<introduction>
今天我们来分析"Rollbacks (Easy Version)"这道有趣的C++题目。本指南将帮助你理解如何高效处理动态数组操作，特别是支持撤销操作时的不同数字统计问题。让我们一起探索操作树和倍增算法的精妙之处！
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`操作树构建` + `倍增法` + `离线处理`

🗣️ **初步分析**：
> 解决这道题的关键在于**将操作序列转化为树形结构**（操作树）。想象你在玩一个像素冒险游戏：每个操作就像游戏中的存档点，添加操作(+x)是创建新存档，删除操作(-k)是读档到之前的存档，撤销操作(!)是返回上一个存档。查询操作(?)则是查看当前存档的成就（不同数字个数）。
   - 核心思路：构建操作树，其中节点代表数组状态，边代表操作。添加操作创建新节点，删除操作通过倍增法快速跳转祖先节点，撤销操作通过栈实现状态回退。
   - 可视化设计：我们将用像素方块表示操作树节点，添加操作时延伸绿色路径（伴随"叮"音效），删除操作时红色箭头跳转祖先（"嗖"音效），查询时节点闪烁金色（"胜利"音效）。
   - 游戏化元素：采用8-bit像素风格，操作树作为游戏地图，每完成一个查询视为通关小关卡，获得像素星星奖励。

---

## 2. 精选优质题解参考

<eval_intro>
以下是综合思路清晰度、代码规范性和算法效率筛选出的优质题解：

### 题解一（作者：Hisaishi_Kanade）
* **点评**：
  该题解构建操作树的思路非常清晰：添加操作创建新节点并更新倍增数组，删除操作通过二进制分解跳转祖先，撤销操作用栈维护状态变化。代码中`f[cq][k]`表示节点的倍增祖先，`v[cq]`存储节点值，命名规范易理解。亮点在于DFS遍历时动态维护数字计数：进入节点时计数增加，离开时回溯计数，完美匹配树形结构。空间复杂度O(n log n)，可直接用于竞赛。

### 题解二（作者：Xy_top）
* **点评**：
  解法同样采用操作树+倍增，但DFS实现更简洁。亮点在于直接使用`vector<int> G[]`存储树结构，`val[]`存储节点值，`res`变量实时维护不同数字个数。删除操作时通过`foR`循环实现二进制跳转，代码仅30行却完整覆盖所有操作，体现高效编程思维。边界处理严谨，实践参考价值高。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题需突破以下三个关键难点：

1.  **操作树的动态构建**
    * **分析**：如何将线性操作序列转化为树形结构？添加操作(+x)需创建新节点作为当前节点的子节点；删除操作(-k)需跳转k级祖先，这要求我们动态维护父子关系。优质题解通过`f[i][0]`存储父节点，`f[i][j]`存储2^j级祖先。
    * 💡 **学习笔记**：操作树是处理离线操作序列的利器，节点=状态，边=操作。

2.  **高效实现删除跳转**
    * **分析**：直接存储每个节点的所有祖先会超空间。题解采用**倍增法**——预处理每个节点的2^j级祖先，跳转时按k的二进制位分解（如k=5=101₂则跳2^0+2^2级），将复杂度优化至O(log k)。
    * 💡 **学习笔记**：倍增法通过指数级跳转将线性操作降为对数级。

3.  **维护不同数字计数**
    * **分析**：DFS遍历操作树时，需要在进入/离开节点时更新计数。关键技巧：进入节点时若该数字首次出现则计数+1，离开时若该数字消失则计数-1，类似莫队算法的add/del操作。
    * 💡 **学习笔记**：DFS的回溯特性天然支持状态回退。

### ✨ 解题技巧总结
<summary_best_practices>
1. **离线转树形**：将操作序列转化为树结构处理历史状态
2. **倍增降复杂度**：用2^j级祖先实现O(log k)跳转
3. **DFS动态维护**：遍历时更新状态，回溯时自动撤销
4. **栈管理操作链**：后进先出特性完美匹配撤销操作
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
### 本题通用核心C++实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5, K = 20;

int n, cnt = 0, distinct = 0, cur = 0;
int f[N][K], val[N], ans[N], freq[N];
vector<int> tree[N];
stack<int> history;

void dfs(int u) {
    if (u) { // 非根节点：更新计数
        if (freq[val[u]]++ == 0) distinct++;
    }
    ans[u] = distinct; // 记录当前节点答案
    for (int child : tree[u]) dfs(child); // 遍历子节点
    if (u) { // 回溯：恢复计数
        if (--freq[val[u]] == 0) distinct--;
    }
}

int main() {
    cin >> n;
    history.push(0); // 初始状态
    for (int i = 1; i <= n; i++) {
        char op; cin >> op;
        if (op == '+') {
            int x; cin >> x;
            f[++cnt][0] = cur;       // 父节点=当前节点
            val[cnt] = x;             // 存储节点值
            for (int j = 1; j < K; j++) // 构建倍增数组
                f[cnt][j] = f[f[cnt][j-1]][j-1];
            cur = cnt;                // 更新当前节点
            history.push(i);          // 记录操作
        } 
        else if (op == '-') {
            int k; cin >> k;
            for (int j = 0; j < K; j++) // 按位跳转祖先
                if (k & (1 << j)) 
                    cur = f[cur][j];
            history.push(i);
        } 
        else if (op == '!') {
            history.pop();          // 弹出当前操作
            cur = history.top();     // 恢复前一个状态
        }
        if (op == '?') 
            cout << ans[cur] << endl;
    }

    // 构建操作树
    for (int i = 1; i <= cnt; i++)
        tree[f[i][0]].push_back(i);
    
    dfs(0); // 从根节点遍历
    return 0;
}
```
* **代码解读概要**：
  1. **初始化**：`f[i][j]`存储i节点的2^j级祖先
  2. **操作处理**：
     - `+`：创建新节点，更新倍增数组
     - `-`：二进制分解k，跳转祖先
     - `!`：用栈回退状态
  3. **离线处理**：所有操作后构建树结构，DFS计算答案
  4. **计数维护**：DFS时动态更新不同数字计数

---

<code_intro_selected>
### 题解片段赏析
**题解一（Hisaishi_Kanade）关键代码**
```cpp
// 倍增跳转祖先（删除操作）
rep(k, 0, 21) 
    if(x[i]&(1<<k)) 
        jmp = f[jmp][k];

// DFS计数更新
if(id) add(v[id]); // 进入节点：计数+
ans[id] = ret;     // 记录答案
for(auto nxt : e[id]) dfs(nxt); 
if(id) del(v[id]); // 离开节点：计数-
```
* **亮点**：用二进制分解实现O(log k)跳转
* **学习笔记**：DFS遍历时进入/离开节点的对称操作完美匹配状态维护

**题解二（Xy_top）核心结构**
```cpp
// 操作树构建
For (i, 1, cnt) 
    G[f[i][0]].push_back(i); 

// DFS维护计数
if (u) add(val[u]);  // 进入节点
ans[u] = res;
for (int v : G[u]) dfs(v); 
if (u) rem(val[u]);  // 离开节点
```
* **亮点**：用`vector`简洁存储树结构
* **学习笔记**：DFS回溯时状态自动恢复是离线算法的核心优势

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
**主题**：像素冒险家在操作树迷宫中探索不同数字宝藏  
**设计思路**：采用FC红白机像素风格，操作树作为游戏地图，每个节点显示当前数组状态。通过颜色和音效强化操作感知。

### 动画流程
1. **场景初始化**：
   - 8-bit风格网格地图，根节点在中心（蓝色像素块）
   - 控制面板：开始/暂停/单步/重置按钮 + 速度滑块
   - 背景播放复古芯片音乐（循环）

2. **添加操作（+）**：
   - 当前节点延伸绿色路径到新节点
   - 新节点显示添加的数字（像素字体）
   - 伴随"叮"的音效，节点闪烁绿色

3. **删除操作（-）**：
   - 红色箭头从当前节点跳回祖先节点
   - 路径上显示跳转步数k（像素数字）
   - 伴随"嗖"的音效，路径红色高亮

4. **查询操作（?）**：
   - 当前节点闪烁金色
   - 头顶显示气泡："Distinct: X"
   - 播放"胜利"音效，获得像素星星+1

5. **撤销操作（!）**：
   - 蓝色箭头沿原路径返回
   - 伴随"倒带"音效，路径变为半透明

6. **自动演示模式**：
   - AI控制角色遍历操作树
   - 进入节点时方块变亮，数字计数显示在右侧面板
   - 离开节点时方块恢复，计数同步更新

### 技术实现
- **数据结构可视化**：数组状态用一行像素方块表示，不同数字用不同颜色
- **关键帧逻辑**：
  ```js
  function addNode(x) {
    playSound("add"); // 播放添加音效
    createNode(current, x); // 创建新节点
    drawPath(current, newNode, GREEN); // 画绿色路径
    current = newNode; // 更新当前节点
  }
  ```
- **交互控制**：通过Canvas API实现单步/自动播放，速度可调

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握操作树和倍增法后，可解决更多历史状态维护问题：

1. **洛谷 P1972 [SDOI2009] HH的项链**  
   → 离线查询区间不同数字个数，练习莫队/树状数组  
   → *推荐理由：巩固不同数字统计技巧，理解在线与离线差异*

2. **洛谷 P3834 可持久化线段树**  
   → 学习经典可持久化数据结构  
   → *推荐理由：操作树的进阶，处理更复杂的历史版本查询*

3. **洛谷 P3391 文艺平衡树**  
   → 实现支持区间翻转的平衡树  
   → *推荐理由：理解数据结构如何维护操作历史*

---

## 7. 学习心得与经验分享

<insights_intro>
> 作者Hisaishi_Kanade提到：*"倍增法预处理祖先数组是处理删除操作的关键"*  
> **Kay点评**：这提醒我们，面对跳转类问题时，预先计算指数级信息可大幅提升效率。类似游戏中的快速旅行点，合理规划路径能节省大量时间。

---

<conclusion>
通过本次分析，我们掌握了操作树构建、倍增法优化和DFS离线处理的核心技巧。记住：将操作序列转化为树结构是处理历史状态问题的通用思路。继续用"像素冒险家"的精神探索算法世界吧！下次见！🚀
</conclusion>
```

---
处理用时：201.43秒