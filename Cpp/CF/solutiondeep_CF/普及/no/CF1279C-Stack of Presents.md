# 题目信息

# Stack of Presents

## 题目描述

Santa has to send presents to the kids. He has a large stack of $ n $ presents, numbered from $ 1 $ to $ n $ ; the topmost present has number $ a_1 $ , the next present is $ a_2 $ , and so on; the bottom present has number $ a_n $ . All numbers are distinct.

Santa has a list of $ m $ distinct presents he has to send: $ b_1 $ , $ b_2 $ , ..., $ b_m $ . He will send them in the order they appear in the list.

To send a present, Santa has to find it in the stack by removing all presents above it, taking this present and returning all removed presents on top of the stack. So, if there are $ k $ presents above the present Santa wants to send, it takes him $ 2k + 1 $ seconds to do it. Fortunately, Santa can speed the whole process up — when he returns the presents to the stack, he may reorder them as he wishes (only those which were above the present he wanted to take; the presents below cannot be affected in any way).

What is the minimum time required to send all of the presents, provided that Santa knows the whole list of presents he has to send and reorders the presents optimally? Santa cannot change the order of presents or interact with the stack of presents in any other way.

Your program has to answer $ t $ different test cases.

## 样例 #1

### 输入

```
2
3 3
3 1 2
3 2 1
7 2
2 1 7 3 4 5 6
3 1
```

### 输出

```
5
8
```

# AI分析结果

### 题目内容重写
#### 题目描述
圣诞老人需要给孩子们送礼物。他有一个大堆的礼物，编号从 $1$ 到 $n$，堆顶的礼物编号为 $a_1$，下一个礼物是 $a_2$，依此类推，堆底的礼物编号为 $a_n$。所有编号都是唯一的。

圣诞老人有一个需要送出的礼物列表，包含 $m$ 个不同的礼物：$b_1$, $b_2$, ..., $b_m$。他将按照列表中的顺序送出这些礼物。

要送出一个礼物，圣诞老人需要在堆中找到它，移除所有在它上面的礼物，取出这个礼物，然后将所有移除的礼物重新放回堆顶。因此，如果堆中有 $k$ 个礼物在目标礼物之上，那么送出这个礼物需要 $2k + 1$ 秒的时间。幸运的是，圣诞老人可以加速整个过程——当他将礼物重新放回堆顶时，可以任意重新排列这些礼物的顺序（只限于那些被移除的礼物；堆中目标礼物下面的礼物不能被改变）。

给定圣诞老人需要送出的礼物列表，并且他可以最优地重新排列礼物的顺序，求送出所有礼物的最小时间。圣诞老人不能改变礼物的顺序或以其他方式与堆互动。

你的程序需要回答 $t$ 个不同的测试用例。

#### 样例 #1
##### 输入
```
2
3 3
3 1 2
3 2 1
7 2
2 1 7 3 4 5 6
3 1
```

##### 输出
```
5
8
```

### 算法分类
贪心

### 题解分析与结论
#### 综合分析
该题的核心在于如何最小化圣诞老人送出礼物的时间。由于圣诞老人可以重新排列被移除的礼物，因此可以利用贪心策略，尽可能减少每次送出礼物时需要移除的礼物数量。

#### 关键思路
1. **记录礼物位置**：首先记录每个礼物在堆中的初始位置。
2. **维护当前最低位置**：通过维护一个变量 `curpos`，记录当前已经处理到堆中的哪个位置。如果下一个要送出的礼物在当前最低位置之上，则可以直接取出，时间加1；否则需要移除所有在它上面的礼物，时间增加 $2k + 1$，并更新 `curpos`。
3. **优化时间计算**：通过上述策略，可以确保每次送出礼物的时间最小化。

#### 评分较高的题解
1. **作者：Goodrage (5星)**
   - **关键亮点**：思路清晰，代码简洁，通过维护 `curpos` 来优化时间计算，且考虑了边界情况（取等与否）。
   - **个人心得**：作者提到在洛谷和 CF 上取等和不取等都可以 AC，但线下数据 hack 了不取等的情况，因此建议取等。

2. **作者：zhangqiuyanAFOon2024 (4星)**
   - **关键亮点**：通过打标记的方式简化了时间计算，思路较为直观。
   - **个人心得**：作者通过标记 `maxx` 来记录当前最低位置，简化了时间计算。

3. **作者：czh___ (4星)**
   - **关键亮点**：通过二分查找礼物的位置，优化了时间计算，代码较为高效。
   - **个人心得**：作者通过二分查找礼物的位置，进一步优化了时间计算。

#### 最优关键思路
- **维护当前最低位置**：通过维护 `curpos` 或 `maxx`，可以快速判断下一个礼物是否在当前最低位置之上，从而优化时间计算。
- **贪心策略**：每次尽可能减少需要移除的礼物数量，确保时间最小化。

#### 可拓展之处
- **类似问题**：类似的问题可以出现在需要多次访问和修改堆结构的场景中，如任务调度、资源分配等。
- **算法套路**：贪心策略在优化问题中非常常见，尤其是在需要最小化或最大化某些指标的场景中。

#### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

### 核心代码片段
```cpp
// Goodrage 的代码片段
int curpos = 0; // 最低位置，要清零
int ans = 0; // 需要步数，要清零
for (int i = 1; i <= m; i++) {
    if (curpos <= pos[b[i]]) { // 之前没动过，需要下去找
        ans += (2 * (pos[b[i]] - i) + 1); // 找，添加步数
        curpos = pos[b[i]]; // 摸的更低了，更新最低位置
    } else {
        ans++; // 已经动过了，在栈顶直接拿出就行
    }
}
```

### 结论
通过维护当前最低位置，结合贪心策略，可以有效地最小化圣诞老人送出礼物的时间。Goodrage 的题解思路清晰，代码简洁，是解决该问题的最佳方案。

---
处理用时：38.87秒