# 题目信息

# ⎌ Nurture ⎌

## 题目背景

![Nurture](https://mivik.gitee.io/image/nurture_wallpaper.jpg)

> "I realized I shouldn't write music with the expectation that the productivity or achievement will fix my problems, but instead with the hope that my honest expression will move people the way music moves me."
>
> — Robinson in a letter to his fans

## 题目描述

Mivik 正在听 Nurture，但这时教练走了进来，Mivik 便假装自己在做这道题。

你有一个长度为 $n$ 的序列 $v$，你每次可以 **取出** 两个数 $a,b$，并把 $a-b$ 添加到序列中。重复操作直到序列中只剩下一个数，你需要求出这个数的最大值。

~~（结果教练一眼秒了这水题，Mivik 因没事刷水题被批判了一番）~~

## 说明/提示

### 样例解释

样例一：第一步取出 $1,2$，并把 $1-2=-1$ 添加到序列中，此时序列为 $[3,-1]$；然后取出 $3,-1$，将 $3-(-1)=4$ 添加到序列中，此时序列只剩下一个数 $4$。可以证明不存在使剩下的数更大的操作方式。

### 数据范围

对于全部数据，有 $1\le n\le 3\cdot 10^5$，$|v_i|\le 10^9$。

Subtask 1 (15 pts)：保证 $n\le 3$。

Subtask 2 (30 pts)：保证 $v_i\ge0$。

Subtask 3 (55 pts)：无特殊限制。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
4
-4 5 -2 -3```

### 输出

```
14```

## 样例 #3

### 输入

```
8
2 0 2 1 0 4 2 3```

### 输出

```
14```

# AI分析结果



### 算法分类
贪心

### 题解分析与结论
题目核心是通过构造减法操作使得最终结果最大化。关键结论为：
- 当存在正负数混合时，答案为所有数绝对值之和
- 全正/全负时，答案需减去2倍最小值/加上2倍最大值
- 最优解通过一次遍历计算极值和绝对值总和即可得出

### 高星题解推荐
1. **Argon_Cube（5星）**
   - **关键亮点**：线性时间复杂度，无需排序，直接计算极值和绝对值总和
   - **核心代码**：
     ```cpp
     sum += abs(tmp);          // 计算绝对值总和
     minn = min(minn, tmp);    // 维护最小值
     maxn = max(maxn, tmp);    // 维护最大值
     // 结果计算
     sum - abs(minn) - abs(maxn) + (maxn - minn)
     ```
   - **实现思想**：通过一次遍历维护极值，利用绝对值总和减去极值的绝对偏差

2. **Mivik（4星）**
   - **关键亮点**：数学归纳严谨，分情况讨论清晰
   - **核心思路**：构造方案使结果为最大(n-k)个数和减最小k个数和，需排序后分类处理

3. **闲人（4星）**
   - **关键亮点**：分正负情况处理，代码简洁
   - **代码技巧**：使用标志位判断是否全正/全负，直接输出对应调整后的绝对值总和

### 关键思路总结
1. **极值维护**：遍历时记录全局最大/最小值
2. **绝对值总和**：所有数贡献绝对值，最后通过极值调整符号
3. **分类处理**：全正/全负需减去两倍极值，混合情况直接取绝对值总和

### 拓展与相似题
- **同类型题**：CF1038D（Slime，相同贪心策略）
- **类似套路**：极值处理+绝对值求和（洛谷P1982、P2647）
- **思维训练**：考虑极值符号对最终结果的影响

### 代码片段（Argon_Cube核心）
```cpp
long long sum = 0, minn = INF, maxn = -INF;
while (cnt--) {
    cin >> tmp;
    sum += abs(tmp);        // 计算绝对值总和
    minn = min(minn, tmp);  // 维护最小值
    maxn = max(maxn, tmp);  // 维护最大值
}
cout << sum - abs(minn) - abs(maxn) + (maxn - minn);
```

### 个人心得摘录
- **特判陷阱**：`n=1`时直接输出原数（多题解强调）
- **数据类型**：必须使用`long long`避免溢出（如样例2结果达14）
- **极值初始化**：正确设置初始值（如`minn=0x7fffffff`）

---

### 推荐练习题
1. [CF1038D Slime](https://codeforces.com/problemset/problem/1038/D)
2. [洛谷P1982 小朋友的数字](https://www.luogu.com.cn/problem/P1982)
3. [洛谷P2647 最大收益](https://www.luogu.com.cn/problem/P2647)

---
处理用时：59.03秒