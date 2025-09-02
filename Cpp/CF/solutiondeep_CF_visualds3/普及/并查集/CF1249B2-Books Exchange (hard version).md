# 题目信息

# Books Exchange (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

There are $ n $ kids, each of them is reading a unique book. At the end of any day, the $ i $ -th kid will give his book to the $ p_i $ -th kid (in case of $ i = p_i $ the kid will give his book to himself). It is guaranteed that all values of $ p_i $ are distinct integers from $ 1 $ to $ n $ (i.e. $ p $ is a permutation). The sequence $ p $ doesn't change from day to day, it is fixed.

For example, if $ n=6 $ and $ p=[4, 6, 1, 3, 5, 2] $ then at the end of the first day the book of the $ 1 $ -st kid will belong to the $ 4 $ -th kid, the $ 2 $ -nd kid will belong to the $ 6 $ -th kid and so on. At the end of the second day the book of the $ 1 $ -st kid will belong to the $ 3 $ -th kid, the $ 2 $ -nd kid will belong to the $ 2 $ -th kid and so on.

Your task is to determine the number of the day the book of the $ i $ -th child is returned back to him for the first time for every $ i $ from $ 1 $ to $ n $ .

Consider the following example: $ p = [5, 1, 2, 4, 3] $ . The book of the $ 1 $ -st kid will be passed to the following kids:

- after the $ 1 $ -st day it will belong to the $ 5 $ -th kid,
- after the $ 2 $ -nd day it will belong to the $ 3 $ -rd kid,
- after the $ 3 $ -rd day it will belong to the $ 2 $ -nd kid,
- after the $ 4 $ -th day it will belong to the $ 1 $ -st kid.

So after the fourth day, the book of the first kid will return to its owner. The book of the fourth kid will return to him for the first time after exactly one day.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
3
2 3 1
6
4 6 2 1 5 3
1
1
4
3 4 1 2
5
5 1 2 4 3
```

### 输出

```
1 1 1 1 1 
3 3 3 
2 3 3 2 1 3 
1 
2 2 2 2 
4 4 4 1 4 
```

# AI分析结果


### 💡 Kay的C++算法解析：Books Exchange (hard version) 深入学习指南 💡

**引言**  
今天我们分析CF1249B2题，考察排列中的环检测。本指南将帮助你掌握核心算法，并通过像素动画直观理解执行过程。

---

### 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`环检测与遍历`  

🗣️ **初步分析**  
> 本题如同孩子们传递书本的"环形接力赛"，每个孩子将书传给固定对象形成闭环。解题关键在于识别每个孩子所属的环，其长度即为书本首次返回所需天数。  
> - **核心思路**：排列特性形成多个不相交环，只需计算每个环长度并赋给环中所有节点  
> - **算法流程**：遍历未访问节点→沿指针走完整环→记录环长→标记环中节点  
> - **可视化设计**：采用8位像素风格，节点显示编号，箭头表示传递路径。当前路径用蓝色高亮，成环时变绿色并播放胜利音效，关键操作配"叮"声提示  

---

### 2. 精选优质题解参考  
**题解一（lzy120406）**  
* **亮点**：  
  - 思路清晰：直接模拟传递路径，逻辑直白易懂  
  - 代码规范：使用vector存储路径节点，变量名`cyc`/`vis`含义明确  
  - 算法高效：O(n)时间复杂度完美处理2e5数据规模  
  - 实践价值：无递归栈溢出风险，可直接用于竞赛  

**题解二（JWRuixi）**  
* **亮点**：  
  - 代码简洁：仅用单层循环实现环检测  
  - 空间优化：复用标记数组，内存效率高  
  - 边界处理：显式重置标记数组，避免多测干扰  
  - 可读性强：`while (p[x] != i)` 直观表达环终止条件  

---

### 3. 核心难点辨析与解题策略  
1. **高效环检测**  
   * **分析**：需确保每个节点只被访问一次。优质解法用`vis`数组标记，遍历时跳过已访问节点  
   * 💡 **学习笔记**：标记访问状态是避免重复计算的关键  

2. **环长记录与分配**  
   * **分析**：需在检测环时同步记录路径。解法一用`vector`存储节点，检测后统一赋值；解法二在循环中直接计数  
   * 💡 **学习笔记**：容器临时存储路径节点是实现批量赋值的高效方式  

3. **多组数据处理**  
   * **分析**：需重置全局状态防止数据污染。解法二显式重置`vis`数组，解法一通过局部变量自动清理  
   * 💡 **学习笔记**：多测试用例必须彻底重置状态数组  

### ✨ 解题技巧总结  
- **技巧1（状态标记法）**：用布尔数组记录访问状态，以空间换时间  
- **技巧2（路径容器化）**：使用vector动态存储路径节点，实现批量赋值  
- **技巧3（循环代替递归）**：避免深递归栈溢出，提高代码健壮性  

---

### 4. C++核心代码实现赏析  
**通用核心C++实现**  
```cpp
#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> p(n+1), ans(n+1);
    vector<bool> vis(n+1, false);
    
    for(int i=1; i<=n; i++) cin >> p[i];
    
    for(int i=1; i<=n; i++) {
        if(vis[i]) continue;
        vector<int> path;
        int cur = i;
        
        while(!vis[cur]) {
            vis[cur] = true;
            path.push_back(cur);
            cur = p[cur];
        }
        
        for(int node : path) 
            ans[node] = path.size();
    }
    
    for(int i=1; i<=n; i++) 
        cout << ans[i] << " ";
    cout << endl;
}
```
* **代码解读概要**：  
  > 1. 初始化标记数组`vis`和结果数组`ans`  
  > 2. 遍历每个未访问节点，沿`p`指针走完整环  
  > 3. 用`vector`存储环上所有节点  
  > 4. 将环长度赋给环中每个节点  

**题解一核心片段**  
```cpp
vector<int> cyc;
int cur = i;
while(!vis[cur]) {
    vis[cur] = true;
    cyc.push_back(cur);
    cur = p[cur];
}
for(int k : cyc) 
    ans[k] = cyc.size();
```
* **代码解读**：  
  > `cyc`作为容器存储当前环路径节点，`cur`跟踪当前孩子。当遇到已访问节点时循环终止，此时`cyc.size()`即为环长  
  > **关键点**：`vis[cur]=true`确保每个节点只进入一个环，`p[cur]`实现指针跳转  
* 💡 **学习笔记**：容器存储路径+批量赋值是环检测的黄金范式  

**题解二核心片段**  
```cpp
while(p[x] != i) {
    vis[x] = 1;
    len++;
    x = p[x];
}
ans[x] = len + 1;
```
* **代码解读**：  
  > 直接通过`p[x]!=i`判断环是否闭合。`len`动态计数，循环终止时`len+1`即为环长（包含起始节点）  
  > **优化点**：省去容器存储，内存效率更高  
* 💡 **学习笔记**：小环场景可直接计数，避免容器开销  

---

### 5. 算法可视化：像素动画演示  
**主题**：`像素书童环游记`  
**核心演示**：环检测过程可视化，包含路径追踪与成环提示  

**设计思路**：  
> 采用FC红白机像素风格，增强学习趣味性。节点用16x16像素方块表示，编号显示其中。路径追踪时同步高亮代码行，强化逻辑关联  

**动画流程**：  
1. **初始化**：灰色像素网格展示所有节点（图1）  
   ![](https://via.placeholder.com/300x150/222/fff?text=初始网格)  
   *控制面板*：开始/暂停/单步/速度滑块/重置  

2. **环检测启动**：  
   - 选中未访问节点（蓝色闪烁）  
   - 播放"叮"音效，显示提示："开始检测环#1"  

3. **路径追踪**：  
   - 当前节点变蓝，指针移动时绘制黄色箭头（图2）  
   ![](https://via.placeholder.com/300x150/2255aa/fff?text=路径追踪)  
   - 同步高亮代码：`cur = p[cur]`  
   - 步进音效：每次移动播放"嘀"声  

4. **成环判定**：  
   - 回到起点时所有环节点变绿（图3）  
   ![](https://via.placeholder.com/300x150/22aa55/fff?text=成环提示)  
   - 显示环长，播放胜利音效  
   - 弹幕提示："环#1完成！长度=4"  

5. **AI演示模式**：  
   - 自动播放时节点按0.5秒/步移动  
   - 完成所有环后显示总结面板  

**技术实现**：  
- 颜色方案：未访问(#888888) 路径中(#2255FF) 已确认环(#22CC55)  
- 关键帧控制：用Canvas逐帧绘制路径和状态  
- 音效触发：路径移动(`new Audio('move.wav')`)，成环(`victory.wav`)  

---

### 6. 拓展练习与相似问题  
**通用技巧迁移**  
环检测技术还可用于：  
1. 排列循环分解（如洗牌算法）  
2. 图论中最小环查找  
3. 并查集路径压缩优化  

**洛谷推荐**  
1. **P2661 信息传递**  
   🗣️ 基础环检测应用，巩固标记法技巧  
2. **P2921 [USACO] 派对**  
   🗣️ 复杂环检测变式，训练多指针处理能力  
3. **P5020 [NOIP] 货币系统**  
   🗣️ 环思维在数学问题中的转化应用  

---

### 7. 学习心得与经验分享  
> **经验摘录**：  
> "最初未重置访问数组导致WA，后增加`vis.fill(false)`解决" —— lzy120406  
>   
> **Kay点评**：  
> 多测试用例必须彻底重置状态！建议封装初始化函数。测试时先用小环验证，再逐步扩大数据规模  

---

### 结语  
通过本次学习，我们掌握了排列环检测的核心思想与实现技巧。记住：好算法=正确标记+路径追踪+批量赋值。接下来尝试用可视化工具模拟不同环场景，加深理解！💪  

> 可视化体验建议：访问[算法可视化沙盒]()动手调整参数观察环检测过程

---
处理用时：129.40秒