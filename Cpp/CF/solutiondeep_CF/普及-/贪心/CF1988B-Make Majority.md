# 题目信息

# Make Majority

## 题目描述

You are given a sequence $ [a_1,\ldots,a_n] $ where each element $ a_i $ is either $ 0 $ or $ 1 $ . You can apply several (possibly zero) operations to the sequence. In each operation, you select two integers $ 1\le l\le r\le |a| $ (where $ |a| $ is the current length of $ a $ ) and replace $ [a_l,\ldots,a_r] $ with a single element $ x $ , where $ x $ is the majority of $ [a_l,\ldots,a_r] $ .

Here, the majority of a sequence consisting of $ 0 $ and $ 1 $ is defined as follows: suppose there are $ c_0 $ zeros and $ c_1 $ ones in the sequence, respectively.

- If $ c_0\ge c_1 $ , the majority is $ 0 $ .
- If $ c_0<c_1 $ , the majority is $ 1 $ .

For example, suppose $ a=[1,0,0,0,1,1] $ . If we select $ l=1,r=2 $ , the resulting sequence will be $ [0,0,0,1,1] $ . If we select $ l=4,r=6 $ , the resulting sequence will be $ [1,0,0,1] $ .

Determine if you can make $ a=[1] $ with a finite number of operations.

## 说明/提示

In the fourth testcase of the example, initially $ a=[1,0,0,0,0,0,0,0,1] $ . A valid sequence of operations is:

1. Select $ l=2,r=8 $ and apply the operation. $ a $ becomes $ [1,0,1] $ .
2. Select $ l=1,r=3 $ and apply the operation. $ a $ becomes $ [1] $ .

## 样例 #1

### 输入

```
5
1
0
1
1
2
01
9
100000001
9
000011000```

### 输出

```
No
Yes
No
Yes
No```

# AI分析结果



### 中文题目重写

#### 题目描述
给定一个由0和1组成的序列 $[a_1,\ldots,a_n]$，你可以进行若干次（可能为零次）操作。每次操作选择区间 $[l,r]$，将该区间替换为区间内的多数元素（若0和1数量相等则替换为0）。判断能否通过有限次操作使序列变为 $[1]$。

#### 输入格式
多组测试数据，每组给出长度 $n$ 和对应的01字符串。

#### 输出格式
对每组数据输出能否达成目标（Yes/No）。

---

### 题解分析与结论

#### 核心思路
所有题解均围绕以下关键观察展开：
1. **合并连续0更优**：将连续多个0合并为单个0不会改变其贡献，同时减少总操作次数。
2. **统计有效0块**：合并后的0块数（记为c0）和1的总数（记为c1）决定结果。当c1 > c0时可通过整体合并得到1。

#### 最优题解（评分≥4星）

1. **作者：shiziyu111（4星）**
   - **亮点**：代码简洁高效，直接统计合并后的0块数和1的总数，逻辑清晰。
   - **关键代码**：
     ```cpp
     for(int i=0;i<n;i++) {
         if(a[i]=='1') c1++;
         else if(a[i-1]!='0' || i==0) c0++;
     }
     if(c1 > c0) cout<<"Yes";
     ```

2. **作者：Z3k7223（4星）**
   - **亮点**：通过数学推导证明操作不影响相对数量差，强化结论可信度。
   - **要点**：无论中间如何操作，最终只需比较c0和c1的初始合并状态。

3. **作者：Little_Cabbage（4星）**
   - **亮点**：详细模拟合并过程，通过重构字符串演示操作效果。
   - **代码片段**：
     ```cpp
     while(now < n) {
         if(s[now]=='1') t+='1', now++;
         else { t+='0'; while(now <n && s[now]=='0') now++; }
     }
     ```

---

### 关键思路总结
1. **贪心压缩0块**：将连续0视为单个0，最大化1的利用率。
2. **最终条件判断**：只需满足 `c1 > c0` 即可通过一次整体合并达成目标。
3. **无需复杂操作**：所有中间操作不影响最终判断条件，直接统计合并后状态即可。

---

### 推荐相似题目
1. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220) - 区间操作与贪心策略
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心合并策略
3. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019) - 区间覆盖与贪心统计

---

### 题解代码核心实现
以最高效的统计方法为例：
```cpp
int c0=0, c1=0;
for(int i=0; i<n; i++){
    if(s[i]=='1') c1++;
    else if(i==0 || s[i-1]!='0') c0++;
}
cout << (c1 > c0 ? "Yes" : "No");
```

---

### 拓展思考
同类问题中，若需构造具体操作步骤，可结合区间DP思想，记录合并路径。本题的特殊性在于只需判断可行性，无需构造操作序列，因此贪心统计即可高效解决。

---
处理用时：52.47秒