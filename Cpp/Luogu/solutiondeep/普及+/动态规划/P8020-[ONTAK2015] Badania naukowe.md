# 题目信息

# [ONTAK2015] Badania naukowe

## 题目描述

给定三个数字串 $A, B, C$，请找到一个 $A, B$ 的最长公共子序列，满足 $C$ 是该子序列的子串。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n,m \leq 3 \times 10^3$，$0 \leq k \leq 3 \times 10^3$。

## 样例 #1

### 输入

```
7
1 2 2 3 1 1 2
6
1 2 1 3 1 2
2
3 2```

### 输出

```
4```

# AI分析结果



### 综合分析与结论
本题解核心思路为拆分问题为三个部分：前缀LCS、C子串、后缀LCS。通过预处理正序/逆序LCS及匹配位置，组合求解。以下题解均采用此框架，差异主要在于预处理细节与代码实现。

---

### 高星题解推荐

#### 1. 作者：Coros_Trusds（★★★★☆）
**核心亮点**  
- 清晰的预处理逻辑，分离正序/逆序LCS计算  
- 使用显式标记数组（ta/tb）记录匹配位置，直观易懂  
- 处理了k=0的特殊情况，鲁棒性强  

**代码核心实现**  
```cpp
// 预处理正序LCS
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        dp1[i][j] = (a[i]==b[j]) ? dp1[i-1][j-1]+1 : max(dp1[i-1][j], dp1[i][j-1]);

// 预处理逆序LCS
for(int i=n;i>=1;i--)
    for(int j=m;j>=1;j--)
        dp2[i][j] = (a[i]==b[j]) ? dp2[i+1][j+1]+1 : max(dp2[i+1][j], dp2[i][j+1]);

// 枚举所有合法起点计算答案
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if(ta[i] && tb[j])
            ans = max(ans, dp1[i-1][j-1] + k + dp2[ta[i]+1][tb[j]+1]);
    }
}
```

---

#### 2. 作者：forever_nope（★★★★☆）
**核心亮点**  
- 函数化封装匹配预处理（init_matching），提高代码复用性  
- 使用更紧凑的数组命名（F/G代替dp1/dp2）  
- 显式处理无效状态的跳过逻辑  

**代码核心实现**  
```cpp
void init_matching(int n, int *A, int k, int *C, int *P) {
    for(int i=1; i<=n; i++) {
        int p=i, q=1;
        while(p<=n && q<=k) q += (A[p++]==C[q]);
        P[i] = (q>k) ? p-1 : 0;
    }
}

// 主答案计算逻辑
for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
        if(P[i] && Q[j])
            ans = max(ans, F[i-1][j-1] + G[P[i]+1][Q[j]+1] + k);
```

---

### 关键思路总结
1. **分阶段处理**：将问题分解为前缀LCS、C子串、后缀LCS三部分，分别预处理。
2. **正逆序LCS**：通过两次动态规划预处理正序（前→后）和逆序（后→前）的LCS。
3. **子串匹配预处理**：对每个起点尝试匹配C，记录最早完整匹配的终点。
4. **组合答案**：枚举所有可能的匹配起点，组合前后缀LCS与C的长度求最大值。

---

### 拓展与相似题目
1. **预处理思想**：类似分阶段预处理可应用于[CF1105E（分段状态压缩）](https://www.luogu.com.cn/problem/CF1105E)
2. **多条件LCS**：[SPOJ LCS2（多序列LCS）](https://www.luogu.com.cn/problem/SP1812)
3. **子串约束LCS**：[HDU 4681（带子串约束的LCS扩展）](https://vjudge.net/problem/HDU-4681)

**推荐题目**  
1. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)  
2. [P2516 [HAOI2010] 最长公共子序列](https://www.luogu.com.cn/problem/P2516)  
3. [P4303 [AHOI2006] 基因匹配](https://www.luogu.com.cn/problem/P4303)

---
处理用时：73.54秒