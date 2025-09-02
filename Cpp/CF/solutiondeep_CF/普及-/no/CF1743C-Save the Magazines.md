# 题目信息

# Save the Magazines

## 题目描述

Monocarp has been collecting rare magazines for quite a while, and now he has decided to sell them. He distributed the magazines between $ n $ boxes, arranged in a row. The $ i $ -th box contains $ a_i $ magazines. Some of the boxes are covered with lids, others are not.

Suddenly it started to rain, and now Monocarp has to save as many magazines from the rain as possible. To do this, he can move the lids between boxes as follows: if the $ i $ -th box was covered with a lid initially, he can either move the lid from the $ i $ -th box to the box $ (i-1) $ (if it exists), or keep the lid on the $ i $ -th box. You may assume that Monocarp can move the lids instantly at the same moment, and no lid can be moved more than once. If a box will be covered with a lid after Monocarp moves the lids, the magazines in it will be safe from the rain; otherwise they will soak.

You have to calculate the maximum number of magazines Monocarp can save from the rain.

## 说明/提示

In the first testcase of the example, Monocarp can move the lid from the second box to the first box, so the boxes $ 1 $ , $ 3 $ and $ 4 $ are covered, and $ 10 + 8 + 9 = 27 $ magazines are saved.

In the second testcase, Monocarp can move the lid from the second box to the first box, then from the third box to the second box, then from the fifth box to the fourth box, and then from the sixth box to the fifth box. The boxes $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ will be covered, so $ 20 + 10 + 30 + 20 = 80 $ magazines can be saved.

There are no lids in the third testcase, so it's impossible to save even a single magazine.

## 样例 #1

### 输入

```
4
5
01110
10 5 8 9 6
6
011011
20 10 9 30 20 19
4
0000
100 100 100 100
4
0111
5 4 5 1```

### 输出

```
27
80
0
14```

# AI分析结果

### 题目内容
# 拯救杂志

## 题目描述
莫诺卡普收集稀有杂志已经有一段时间了，现在他决定卖掉它们。他把杂志分放在 $n$ 个排成一排的盒子里。第 $i$ 个盒子里有 $a_i$ 本杂志。有些盒子盖着盖子，有些则没有。

突然开始下雨了，现在莫诺卡普必须尽可能多地拯救杂志不被雨淋。为此，他可以按如下方式在盒子之间移动盖子：如果第 $i$ 个盒子最初盖着盖子，他可以将盖子从第 $i$ 个盒子移动到第 $(i - 1)$ 个盒子（如果存在），或者让盖子留在第 $i$ 个盒子上。你可以假设莫诺卡普能在同一时刻瞬间移动盖子，并且任何盖子都只能移动一次。如果在莫诺卡普移动盖子后，一个盒子被盖子盖住，那么里面的杂志就不会被雨淋；否则就会被淋湿。

你必须计算出莫诺卡普最多能拯救多少本杂志不被雨淋。

## 说明/提示
在示例的第一个测试用例中，莫诺卡普可以将第二个盒子的盖子移动到第一个盒子，这样第1、3和4个盒子就被盖住了，$10 + 8 + 9 = 27$ 本杂志得以拯救。

在第二个测试用例中，莫诺卡普可以将第二个盒子的盖子移动到第一个盒子，然后将第三个盒子的盖子移动到第二个盒子，接着将第五个盒子的盖子移动到第四个盒子，最后将第六个盒子的盖子移动到第五个盒子。这样第1、2、4和5个盒子就被盖住了，所以 $20 + 10 + 30 + 20 = 80$ 本杂志可以被拯救。

在第三个测试用例中没有盖子，所以连一本杂志都救不了。

## 样例 #1
### 输入
```
4
5
01110
10 5 8 9 6
6
011011
20 10 9 30 20 19
4
0000
100 100 100 100
4
0111
5 4 5 1
```
### 输出
```
27
80
0
14
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要分为模拟、动态规划（DP）和贪心三种思路。
 - **模拟思路**：通过设置标记数组，遍历盒子，尝试将后一个盒子的盖子移动到前一个无盖子的盒子上，并根据杂志数量决定是否移动，过程较为直观，但代码实现相对复杂，时间复杂度较高。
 - **动态规划思路**：通过定义状态 $f_{i,0/1}$ 表示考虑到第 $i$ 个箱子时，当前箱子盖子往前传或留在原地时的最大保护价值，根据当前箱子是否有盖子进行状态转移，时间复杂度为 $O(n)$，相对高效且代码简洁。
 - **贪心思路**：从后往前递推，以没盖盖板的位置为节点，用总和减去每段的最小值得到答案，但贪心的正确性较难证明。

整体来看，动态规划思路在代码实现和时间复杂度上表现更优。

### 所选的题解
 - **作者：SalomeJLQ（5星）**
    - **关键亮点**：思路简洁清晰，直接定义状态转移方程，代码简洁明了。
    - **状态转移方程**：
当 $i$ 处原本有盖子时：
$f_{i,0}=\max(f_{i - 1,1}, f_{i - 1,0}+a_{i - 1})$，
$f_{i,1}=\max(f_{i - 1,0}, f_{i - 1,1})+a_i$；
否则 $f_{i,0}=f_{i,1}=\max(f_{i - 1,0}, f_{i - 1,1})$。
 - **作者：Cappuccino_mjj（4星）**
    - **关键亮点**：与SalomeJLQ思路类似，但对状态转移方程解释更详细，便于理解。
    - **状态转移方程代码**：
```cpp
if(vis[i]=='1')//判断是否有盖板
{
    dp[i][0]=dp[i-1][0]+a[i-1];//将盖板移到上一个箱子
    dp[i][1]=max(dp[i-1][0],dp[i-1][1])+a[i];//将盖板保留给自己
}
else dp[i][0]=max(dp[i-1][0],dp[i-1][1]);//没有盖板
```
 - **作者：CENRUIYANG（4星）**
    - **关键亮点**：对动态规划的初始化和转移条件分析细致，逻辑严谨。
    - **状态转移方程**：
当 $s_i = 1$ 时，$f_{i,0}=f_{i - 1,0}+a_{i - 1}$，$f_{i,1}=\max(f_{i - 1,0}, f_{i - 1,1})+a_i$；
当 $s_i = 0$ 时，$f_{i,0}=\max(f_{i - 1,0}, f_{i - 1,1})$。

### 最优关键思路或技巧
动态规划中，通过合理定义状态 $f_{i,0/1}$ 来表示第 $i$ 个箱子不同盖子状态下的最大保护价值，利用状态转移方程高效求解，避免了模拟的复杂操作和贪心难以证明正确性的问题。

### 可拓展之处
此类问题属于动态规划中的线性DP，类似套路是根据问题的阶段和状态，合理定义状态转移方程。同类型题通常涉及决策过程，且当前决策依赖于之前的状态。

### 洛谷相似题目
 - [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)
 - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
 - [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)

### 个人心得摘录
 - **作者：YYHISBOY**：考试时写这道题花了1小时，认为自己太菜。总结：遇到类似题目，应多思考优化方法，避免复杂模拟，可尝试动态规划等高效算法。 

---
处理用时：43.65秒