# 题目信息

# [ABC362E] Count Arithmetic Subsequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_e

長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。各 $ k=1,2,\dots,N $ について、$ A $ の長さ $ k $ の（連続するとは限らない）部分列であって等差数列であるようなものの個数を $ 998244353 $ で割ったあまりを求めてください。ただし、$ 2 $ つの部分列が列として同じでも、取り出す位置が異なるならば区別するものとします。

部分列とは数列 $ A $ の部分列とは、$ A $ の要素を $ 0 $ 個以上選んで削除し、残った要素を元の順序を保って並べた数列のことを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 80 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

\- 長さ $ 1 $ の部分列は全部で $ 5 $ 個あり、これらはすべて長さ $ 1 $ の等差数列です。 - 長さ $ 2 $ の部分列は全部で $ 10 $ 個あり、これらはすべて長さ $ 2 $ の等差数列です。 - 長さ $ 3 $ の部分列であって等差数列であるものは、$ (A_1,A_2,A_3),(A_1,A_2,A_5),(A_1,A_4,A_5) $ の $ 3 $ つです。 - 長さ $ 4 $ 以上の部分列であって等差数列であるものは存在しません。

## 样例 #1

### 输入

```
5
1 2 3 2 3```

### 输出

```
5 10 3 0 0```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
4 6 2 1```

## 样例 #3

### 输入

```
1
100```

### 输出

```
1```

# AI分析结果



# ABC362E 计数等差子序列

## 题目重写

**题目描述**  
给定一个长度为 $N$ 的数列 $A=(A_1,A_2,\dots,A_N)$。对于每个 $k=1,2,\dots,N$，求 $A$ 中长度为 $k$ 的（不一定连续的）子序列中满足等差数列条件的数量，结果对 $998244353$ 取模。两个子序列若选取元素的位置不同则视为不同。

**输入格式**  
第一行输入整数 $N$  
第二行输入 $N$ 个整数 $A_1,A_2,\dots,A_N$

**输出格式**  
输出 $N$ 个空格分隔的数，第 $k$ 个表示长度为 $k$ 的答案

**样例1输入**  
```
5
1 2 3 2 3
```

**样例1输出**  
```
5 10 3 0 0
```

**样例解释**  
- 长度为 1 的子序列（5 个）都是等差数列  
- 长度为 2 的子序列（10 个）都是等差数列  
- 长度为 3 的有效子序列有 3 个  
- 长度为 4/5 的无解

---

## 算法分类  
**线性DP**

---

## 核心分析与结论

### 动态规划关键设计
各题解共性：**以子序列末项为核心设计状态**  
1. **状态定义**  
   - 主流方案：`f[i][j][k]` 表示长度为 i 的子序列，以第 j 和 k 项为最后两个元素  
   - 离散化方案：`dp[pos][len][d]` 表示以 pos 结尾、长度 len、公差 d 的方案数  

2. **转移方程**  
   ```math
   f[i][j][k] = \sum_{l<j} [A_k-A_j == A_j-A_l] \cdot f[i-1][l][j]
   ```
   离散化版本：  
   ```math
   dp[k][len][d] += dp[j][len-1][d] \quad \text{if } A_k-A_j = d
   ```

### 解决难点
1. **公差范围巨大**：通过预处理所有可能的公差进行离散化  
2. **三重循环优化**：  
   - 枚举子序列最后两个元素的位置 j,k  
   - 通过离散化将查找公差的时间优化为 O(1)  
   - 滚动数组优化空间复杂度

### 可视化设计
**像素风格 DP 矩阵**  
1. **Canvas 网格**：  
   - 每个单元格表示一个 `dp[len][j][d]` 状态  
   - 颜色深浅表示状态值的大小  
2. **动画效果**：  
   - 红色高亮：当前处理的 j,k 元素对  
   - 绿色流动：状态转移过程（从旧状态流向新状态）  
3. **音效提示**：  
   - 短促 "滴" 声：每次状态更新  
   - 和弦音：完成一个 len 的计算

---

## 优质题解推荐 (≥4★)

1. **MightZero（5★）**  
   - **亮点**：离散化公差降低复杂度，滚动数组优化空间  
   - **代码段**：  
     ```cpp
     loop(i,1,n)loop(len,2,i)loop(j,1,i-1) {
         ll dpos = lower_bound(d.begin(),d.end(),a[i]-a[j]) - d.begin();
         (dp[i][len][dpos] += dp[j][len-1][dpos]) %= MOD;
     }
     ```

2. **aCssen（4★）**  
   - **亮点**：二维 DP 枚举前两项，适合小规模数据  
   - **代码段**：  
     ```cpp
     for(int p1=1;p1<=n;p1++) {
         for(int p2=p1+1;p2<=n;p2++) {
             memset(f,0,sizeof(f));
             f[p2][2] = 1;
             // ...转移部分...
         }
     }
     ```

3. **xiaofu15191（4★）**  
   - **亮点**：直接使用 map 处理公差，代码简洁  
   - **代码段**：  
     ```cpp
     map<long long,long long> mp;
     //...
     if(!mp.count(a[j]-a[i])) mp[a[j]-a[i]] = ++cnt;
     ```

---

## 关键代码实现

**MightZero 题解核心**  
```cpp
// 预处理所有公差
vector<ll> d;
loop(i,1,n) loop(j,1,i-1) 
    d.push_back(a[i]-a[j]);
sort(d.begin(),d.end());
d.erase(unique(d.begin(),d.end()),d.end());

// DP转移
loop(i,1,n) loop(len,2,i) loop(j,1,i-1) {
    ll delta = a[i]-a[j];
    ll dpos = lower_bound(d.begin(),d.end(),delta) - d.begin();
    dp[i][len][dpos] = (dp[i][len][dpos] + dp[j][len-1][dpos]) % MOD;
}
```

---

## 同类题目推荐
1. **LeetCode 413. 等差数列划分**  
2. **Atcoder DP Contest M - Candies**  
3. **洛谷 P5858 「SWTR-03」Golden Sword**  

---

## 可视化代码片段
```javascript
// Canvas绘制DP矩阵
function drawDPGrid() {
    ctx.clearRect(0,0,canvas.width,canvas.height);
    for(let len=1; len<=n; len++) {
        for(let i=1; i<=n; i++) {
            const val = dp[len][i].reduce((a,b)=>a+b,0);
            const color = `hsl(${200*(1-val/maxVal)},70%,60%)`;
            ctx.fillStyle = color;
            ctx.fillRect((i-1)*cellSize, (len-1)*cellSize, cellSize-1, cellSize-1);
        }
    }
}
// 音效触发
function playUpdateSound() {
    const osc = audioCtx.createOscillator();
    osc.frequency.value = 800 + Math.random()*200;
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(audioCtx.currentTime + 0.05);
}
```

---

## 心得总结
- **离散化技巧**：当数值范围过大时，预处理可能的取值是关键  
- **状态压缩**：发现等差数列的连续性特征，只需记录最后两个元素  
- **逆向思维**：从末项向前推导比从首项开始更易处理公差关系

---
处理用时：83.40秒