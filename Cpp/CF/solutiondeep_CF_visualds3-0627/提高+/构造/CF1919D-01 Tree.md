# 题目信息

# 01 Tree

## 题目描述

There is an edge-weighted complete binary tree with $ n $ leaves. A complete binary tree is defined as a tree where every non-leaf vertex has exactly 2 children. For each non-leaf vertex, we label one of its children as the left child and the other as the right child.

The binary tree has a very strange property. For every non-leaf vertex, one of the edges to its children has weight $ 0 $ while the other edge has weight $ 1 $ . Note that the edge with weight $ 0 $ can be connected to either its left or right child.

You forgot what the tree looks like, but luckily, you still remember some information about the leaves in the form of an array $ a $ of size $ n $ . For each $ i $ from $ 1 $ to $ n $ , $ a_i $ represents the distance $ ^\dagger $ from the root to the $ i $ -th leaf in dfs order $ ^\ddagger $ . Determine whether there exists a complete binary tree which satisfies array $ a $ . Note that you do not need to reconstruct the tree.

 $ ^\dagger $ The distance from vertex $ u $ to vertex $ v $ is defined as the sum of weights of the edges on the path from vertex $ u $ to vertex $ v $ .

 $ ^\ddagger $ The dfs order of the leaves is found by calling the following $ \texttt{dfs} $ function on the root of the binary tree.

```
<pre class="verbatim"><br></br>dfs_order = []<br></br><br></br>function dfs(v):<br></br>    if v is leaf:<br></br>        append v to the back of dfs_order<br></br>    else:<br></br>        dfs(left child of v)<br></br>        dfs(right child of v)<br></br><br></br>dfs(root)<br></br>
```

## 说明/提示

In the first test case, the following tree satisfies the array.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1919D/2af3796cd4a2a9733f8a3c061e8120f70b3cbf6a.png)

In the second test case, it can be proven that there is no complete binary tree that satisfies the array.

## 样例 #1

### 输入

```
2
5
2 1 0 1 1
5
1 0 2 1 3```

### 输出

```
YES
NO```

# AI分析结果



1. **唯一算法分类**  
   - 无算法分类

2. **综合分析与结论**  
   本题核心在于通过结构分析验证两个条件：  
   - **存在且仅有一个0**  
   - **每个非0元素必须存在相邻元素为其值减1**  

   各题解主要分为两类思路：  
   - **单调栈预处理**：通过左右单调栈快速找到每个元素左右第一个更小的值，验证是否满足差值为1的条件（如题解MaxBlazeResFire）。  
   - **贪心合并模拟**：从最大值开始，用链表维护元素，动态删除满足条件的节点（如题解FFTotoro、Luzhuoyuan）。  

   **可视化设计思路**：  
   - **动画流程**：  
     1. 初始数组以像素风格呈现，元素按DFS序排列。  
     2. 遍历每个元素时，高亮当前元素并标记其左右相邻元素。  
     3. 若左右存在差值为1的元素，触发绿色高亮并播放成功音效；否则触发红色闪烁并播放失败音效。  
     4. 对于贪心合并法，动态展示链表删除过程，用像素方块模拟节点合并。  
   - **复古交互**：  
     - 使用8-bit风格颜色（如深蓝背景、亮黄高亮）。  
     - 音效：合并时播放"哔"声，失败时播放"嘟嘟"声，背景音乐为循环芯片音乐。  
     - 控制面板支持步进/暂停，展示当前检查的值域层级（如"Processing Value: 3"）。  

3. **题解清单 (≥4星)**  
   - **MaxBlazeResFire（5星）**：思路清晰，利用单调栈预处理左右边界，代码简洁高效。  
   - **FFTotoro（4星）**：链表+BFS优化，直观展示动态删除过程，可读性良好。  
   - **Luzhuoyuan（4星）**：详细注释+链表队列实现，附带调试心得（如未打标记的坑）。  

4. **最优思路提炼**  
   **关键条件验证法**（MaxBlazeResFire）：  
   ```cpp
   // 预处理左右第一个更小的值
   for (int i=1; i<=n; i++) {
       while (top && a[i] < a[st[top]]) R[st[top--]] = i;
       st[++top] = i;
   }
   // 检查每个元素是否满足条件
   for (int i=1; i<=n; i++) {
       if (!a[i]) continue;
       if (!(左存在a[i]-1 || 右存在a[i]-1)) return NO;
   }
   ```

5. **同类型题拓展**  
   - **CF1350D**：数组相邻元素合并条件验证  
   - **LeetCode 768**：验证数组是否可分割为满足条件的子数组  

6. **洛谷推荐题目**  
   - P1886（滑动窗口单调栈应用）  
   - P5788（单调栈模板题）  
   - P1972（链表维护区间特性）  

7. **核心代码片段**  
   ```cpp
   // MaxBlazeResFire的关键代码
   void solve() {
       // 统计0的个数
       if (cnt0 != 1) { puts("NO"); return; }
       // 单调栈求右侧第一个更小的值
       for (int i=1; i<=n; i++) {
           while (top && a[i] < a[st[top]]) R[st[top--]] = i;
           st[++top] = i;
       }
       // 同理求左侧
       // 验证每个元素
       for (int i=1; i<=n; i++) {
           if (!a[i]) continue;
           if (!(左或右存在a[i]-1)) return NO;
       }
       puts("YES");
   }
   ```

8. **可视化实现要点**  
   ```javascript
   // 伪代码：像素动画核心逻辑
   class Visualizer {
       constructor(arr) {
           this.canvas = initCanvas(); // 8-bit风格画布
           this.sound = new ChipTune(); // 音效库
           this.highlightIndex = -1;
       }
       step() {
           // 高亮当前元素，检查左右
           if (checkCondition()) {
               this.sound.play('success');
               drawMergeEffect();
           } else {
               this.sound.play('fail');
               flashRed();
           }
       }
   }
   ```

---
处理用时：88.44秒