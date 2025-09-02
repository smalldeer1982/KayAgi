# 题目信息

# [WFOI - 01] 猜数（guess）

## 题目背景

**这是一道交互题。交互库自适应。请注意特殊的时间限制。**

**每次输出后请记得清空缓存**

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/xx7sa8go)。

## 题目描述

你需要猜一个正整数 $q$，保证 $q\in [1,n]$；

你每次可以用诸如 `? x y` 的询问，交互库会在 $[x,y]$ 中指定选择一个数 $z$；

然后交互库会输出形如 `u v` 的回答，表示指定的数是 $u$，其与 $q$ 的关系为 $v$；

具体地，
- 当交互库返回的 $v=0$ 时，表示 $u<q$；
- 当交互库返回的 $v=1$ 时，表示 $u=q$；
- 当交互库返回的 $v=2$ 时，表示 $u>q$。

而一次询问的代价是 $\dfrac{1}{y-x+1}$；

你可以通过 `! x` 输出你认为正确的答案。

现在你要求出 $q$。

------------

设你的代价为 $x$，你每个测试点获得的分数和你的总代价有如下关系（每个测试点满分 $10$ 分）：


- 若 $x\le 1.9813035$，则你可以得到 $\text{10 pts}$；
- 若 $1.9813035 < x \le 12$，则你可以得到 $\lfloor(12-x)\times0.7 \div 1.00186965\rfloor  \text{ pts}$。
- 若 $x\ge12$，则你可以得到 $\text{0 pts}$。


需要注意的是，在每一次操作后，需要调用以下函数刷新缓存：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

### 交互格式

一开始交互库会给你 $n$，

然后你可以按题目描述中的方式进行询问或回答答案；

在回答后请立即退出程序。

## 说明/提示

- **样例 $1$ 解释：**
	
    询问后发现 $1<x\le2$，所以 $x=2$；
    
- **样例 $2$ 解释：** 

    第一次询问后发现 $1<x\le3$；
    
    第二次询问后发现 $1<x<3$，所以 $x=2$；

**【数据规模与约定】**

| 测试点编号 | $n \le$ | 测试点编号 | $n\le$ |
| :-: | :-: | :-: | :-: |
| $\texttt{1}$ | $1$ | $\texttt{6}$ | $2\times 10^3$ |
| $\texttt{2}$ | $7$ | $\texttt{7}$ | $10^4$ |
| $\texttt{3}$ | $20$ | $\texttt{8}$ | $5\times 10^4$ |
| $\texttt{4}$ | $80$ | $\texttt{9}$ | $10^5$ |
| $\texttt{5}$ | $300$ | $\texttt{10}$ | $10^5$ |

对于 $100\%$ 的数据，$1\le n\le10^5$，$1\le q,\forall u\le n$，$\forall v\in\{0,1,2\}$。

保证每询问一次交互库时间是 $\mathcal O(1)$ 的。

## 样例 #1

### 输入

```
2

1 0
 ```

### 输出

```

? 1 2

! 2```

## 样例 #2

### 输入

```
3

1 0

3 2
 ```

### 输出

```

? 1 3

? 3 3

! 2```

# AI分析结果



# 题目翻译

## [WFOI - 01] 猜数（guess）

### 题目背景

**这是一道交互题。交互库自适应。请注意特殊的时间限制。**

**每次输出后请记得清空缓存**

### 题目描述

你需要猜一个正整数 $q$，保证 $q\in [1,n]$；

每次可以用 `? x y` 询问，交互库会在 $[x,y]$ 中选择一个数 $z$，返回其值 $u$ 及与 $q$ 的关系 $v$：
- $v=0$ 表示 $u<q$
- $v=1$ 表示 $u=q$
- $v=2$ 表示 $u>q$

代价为 $\dfrac{1}{y-x+1}$，要求总代价不超过 1.9813035 以获得满分。

---

## 算法分类：线性DP

## 综合分析与结论

### 核心思路
采用动态规划预计算每个区间长度的最优询问策略，通过打表或决策单调性优化将复杂度从 $O(n^2)$ 降至可接受范围。关键点在于设计状态转移方程：
$$
dp[i] = \min_{j} \left( \frac{1}{j} + dp[\max(\text{剩余区间长度})] \right)
$$
其中 $j$ 是询问区间长度，剩余区间由交互库的最坏选择决定。

### 可视化设计要点
1. **DP矩阵更新动画**：用网格展示不同区间长度对应的最优询问长度，高亮当前决策点
2. **像素风格**：8-bit 风格颜色区分：
   - 红色：当前更新的 dp[i]
   - 绿色：候选的 j 值
   - 蓝色：依赖的前置状态
3. **音效触发**：
   - 清脆音效：完成一次状态转移
   - 低音提示：找到更优解
4. **自动演示模式**：按区间长度递增自动播放，展示决策点选择与代价累积

---

## 题解清单（≥4星）

### 题解1（yzy1）★★★★★
- **亮点**：打表法分段拟合最优决策点，通过观察 DP 结果的线性特征建立分段函数
- **关键代码**：
```cpp
int F(int x) {  // 分段函数决策
    if(x <= 10000) return biao[x];
    else if(x <=13383) return 4938; // 后续分段省略...
}
```

### 题解3（Purslane）★★★★☆
- **亮点**：利用决策单调性优化 DP，$O(n\log n)$ 复杂度，无需打表
- **核心转移**：
```cpp
long double f(int x,int v) { // 决策函数
    return dp[x] + 1.0/(2*x+2-v); 
}
```

### 题解4（int08）★★★★
- **亮点**：预计算转移点邻域，局部枚举优化，代码简洁
- **创新点**：
```cpp
for(j=l[i]+(i&1); j<=min(r[i],i); j+=2) // 奇偶性剪枝
```

---

## 核心代码实现

### 决策点预计算（yzy1）
```cpp
// 预处理dp数组和转移决策点
rep(i, 2, 1e5) {
    dp2[i] = INFINITY;
    int mid = (1 + i) / 2;
    re(j, i) { // 枚举询问区间长度
        int l = mid - (j - 1)/2; 
        int r = l + j - 1;
        int res = max({l-1, i-l, r-1, i-r});
        if(dp2[res] + 1.0/j < dp2[i])
            dp2[i] = dp2[res] + 1.0/j, dp1[i] = j;
    }
}
```

### 交互过程（Purslane）
```cpp
void solve(int l, int r) {
    if(l == r) Ans(l);
    int len = r-l+1, res = F(len);
    int L = mid - (res-1)/2, R = L + res-1;
    auto [u,v] = Ask(L, R); // 交互查询
    if(v == 0) solve(u+1, r); // 递归处理剩余区间
    else if(v == 2) solve(l, u-1);
}
```

---

## 相似题目推荐
1. P1255 数楼梯（线性DP）
2. P1048 采药（0-1背包决策优化）
3. P1489 区间问题（区间DP策略）

---

## 可视化代码片段（伪代码）

```javascript
// Canvas绘制DP矩阵
function drawDP() {
    ctx.fillStyle = '#8B00FF'; // 紫色背景
    ctx.fillRect(0,0,canvas.width,canvas.height);
    
    for(let i=1; i<=n; i++) {
        const y = Math.floor((i-1)/gridWidth)*cellSize;
        const x = ((i-1)%gridWidth)*cellSize;
        
        // 高亮当前处理的区间长度
        if(i == currentProcess) 
            ctx.fillStyle = '#FF1493'; // 深粉色
        else
            ctx.fillStyle = hsl(360*i/n, 70%, 80%);
        
        ctx.fillRect(x, y, cellSize-2, cellSize-2);
    }
}

// 播放音效
function playSound(type) {
    const osc = audioCtx.createOscillator();
    osc.frequency.value = type === 'update' ? 880 : 440;
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(0.1);
}
```

---

## 总结
本题突破点在于将交互过程转化为最坏情况下的动态规划问题，通过预计算和优化策略将理论算法落地。关键启示：对于自适应交互题，应建立数学决策模型而非依赖随机策略。

---
处理用时：82.28秒