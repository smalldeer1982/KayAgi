# 题目信息

# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1
```

### 输出

```
3
1
4
```

# AI分析结果



【题目中文翻译】

# 浇灌花园

## 题目描述

正值寒冬，Max决定是时候浇灌他的花园了。

花园可以看作由 $n$ 个连续的花坛组成，编号从 $1$ 到 $n$。其中有 $k$ 个花坛装有水龙头（第 $i$ 个水龙头位于花坛 $x_i$ 处），当打开时，水会逐渐浸润相邻花坛。若打开位于 $x_i$ 的水龙头，经过 1 秒后，$x_i$ 所在的花坛会被浸润；经过 2 秒后，区间 $[x_i-1, x_i+1]$ 的花坛会被浸润（若存在）；经过 $j$ 秒后，区间 $[x_i-(j-1), x_i+(j-1)]$ 的花坛会被浸润（若存在）。时间变化是离散的，例如 2.5 秒时不会浸润，只有在 3 秒时才会扩展到 $[x_i-2, x_i+2]$。

Max想要同时打开所有水龙头，请计算从打开水龙头到整个花园都被浸润所需的最短时间。

## 样例与说明

输入样例包含多组测试数据，输出对应每组的最短时间。例如当水龙头位于中间位置时，需要3秒才能覆盖整个花园；当每个花坛都有水龙头时只需1秒。

---

【题解对比与结论】

### 最优思路提炼
核心观察点在于相邻水龙头覆盖区域的交汇时间计算：
1. **首尾特殊处理**：第一个水龙头到左端的时间为 $x_1$，最后一个到右端的时间为 $n - x_k$
2. **中间区域计算**：相邻水龙头间距为 $d$ 时，中间区域被完全覆盖的时间为 $\lceil d/2 \rceil = (d//2) + 1$
3. 最终答案为这三类情况的最大值

该思路通过数学推导实现 O(k) 时间复杂度，显著优于 BFS 的 O(n) 复杂度，且代码简洁。

---

### 高分题解推荐

#### 1. 作者：nenugdi（5星）
**亮点**：
- 数学建模准确，直接推导关键时间点
- 代码简洁高效（仅需排序后单次遍历）
- 处理首尾与中间区域逻辑清晰

**核心代码**：
```cpp
sort(x, x + k);
int max_time = max(x[0], n - x[k-1]);
for(int i=1; i<k; i++){
    int gap = x[i] - x[i-1];
    max_time = max(max_time, gap/2 + 1);
}
cout << max_time << endl;
```

#### 2. 作者：Great_Influence（5星）
**亮点**：
- 公式表达直击问题本质
- 代码模板化，适合竞赛快速实现
- 变量命名与排序预处理规范

**核心公式**：
```cpp
ans = max({x[0], n - x.back(), (x[i]-x[i-1])/2 + 1});
```

#### 3. 作者：codesonic（4星）
**亮点**：
- BFS标准实现，适合理解扩散过程
- 队列记录时间戳，直观展示浸润过程

**核心片段**：
```cpp
queue<node> q;
for(水龙头位置入队并标记时间1秒);
while(!q.empty()){
    扩散左右未访问节点，更新时间最大值;
}
```

---

### 关键技巧总结
1. **贪心思想**：相邻水龙头中间区域的覆盖时间由间距决定，无需逐秒模拟
2. **边界处理**：首尾水龙头的覆盖时间是独立计算的单边扩展
3. **预处理排序**：水龙头位置必须排序后才能正确计算间距

---

### 相似题目推荐
1. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220) - 区间覆盖与时间计算
2. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514) - 覆盖区域的最优解
3. [P1661 扩散](https://www.luogu.com.cn/problem/P1661) - 多点扩散时间计算

---

### 题解中的个人心得
- **排序陷阱**：多个题解强调水龙头位置必须排序后才能计算间距（如 `Great_Influence` 的代码）
- **队列清空**：BFS实现中需在每组测试前清空队列（`LordLaffey` 的题解特别提醒）
- **初始化问题**：暴力解法需注意数组初始化为极大值（`cyrxdzj` 的思考题答案）

---
处理用时：56.16秒