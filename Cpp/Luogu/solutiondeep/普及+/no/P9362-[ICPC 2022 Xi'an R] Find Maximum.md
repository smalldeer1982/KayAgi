# 题目信息

# [ICPC 2022 Xi'an R] Find Maximum

## 题目描述

定义在所有非负整数 $x$ 上的函数 $f(x)$ 如下：

$$
f(x) =
\begin{cases}
1 & (x = 0) \\
f(\frac{x}{3}) + 1 & (x > 0\land x\bmod3 = 0) \\
f(x - 1) + 1  & (x > 0\land x\bmod 3\neq 0)
\end{cases}
$$

计算 $\max_{x = l} ^ r f(x)$。

共有 $T$ 组数据。

$1\leq T\leq 10 ^ 4$，$1\leq l\leq r\leq 10 ^ {18}$。

## 样例 #1

### 输入

```
10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
```

### 输出

```
3
3
4
5
3
4
5
4
5
5
```

# AI分析结果

### 算法分类
**进制**

### 综合分析与结论
题目要求计算函数 $f(x)$ 在区间 $[l, r]$ 内的最大值，其中 $f(x)$ 的定义与三进制密切相关。通过分析，可以发现 $f(x)$ 的值等于 $x$ 的三进制表示中的位数与数码和之和。因此，问题转化为在三进制下寻找区间 $[l, r]$ 内位数与数码和之和的最大值。

### 所选题解
1. **作者：InoueTakina (赞：3)**
   - **星级：4**
   - **关键亮点：**
     - 通过三进制分析，将问题转化为贪心策略。
     - 动态维护最大值，代码简洁高效。
     - 使用预处理的三进制位数组，优化了计算过程。
   - **核心代码：**
     ```cpp
     void solve(){
         cin >> l >> r; now = sum = flag = ans = 0;
         for(int i = Li - 1; ~i; i --){
             L[i] = l % B[i + 1] / B[i];
             R[i] = r % B[i + 1] / B[i];
         }
         for(int i = Li - 1; ~i; i --){
             if(R[i]) flag = 1;
             if(! flag) continue;
             if(R[i] and now + 1ll * R[i] * B[i] - 1 >= l){
                 if(R[i] > 1 or sum) ans = max(ans, sum + R[i] + 1ll * 3 * i);
                 else ans = max(ans, sum + 1ll * 3 * i);
             }
             sum = sum + R[i] + 1; now = now + 1ll * R[i] * B[i];
         } return cout << max(ans, sum) << "\n", void();
     }
     ```

2. **作者：0x282e202e2029 (赞：3)**
   - **星级：4**
   - **关键亮点：**
     - 通过打表找规律，发现三进制与 $f(x)$ 的关系。
     - 分类讨论不同情况，逻辑清晰。
     - 使用三进制转换函数，代码结构清晰。
   - **核心代码：**
     ```cpp
     vector<int> getTernary(long long k){
         vector<int> v;
         if(!k) v.push_back(0);
         while(k){
             v.push_back(k % 3);
             k /= 3;
         }
         reverse(v.begin(), v.end());
         return v;
     }
     ```

3. **作者：chenzhixing_ (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 详细解释了 $f(x)$ 与三进制的关系，思路清晰。
     - 使用数位 DP 进行优化，适合大规模数据。
     - 代码实现细节丰富，适合深入学习。
   - **核心代码：**
     ```cpp
     int dfs(int len, int op, bool zero, bool lower, bool upper){
         if (st[len][op] == tot && !lower && !upper && !zero) return f[len][op];
         if (!len) return zero ? 1 : op;
         int l = lower ? a[len] : 0, r = upper ? b[len] : 2, ans = 0;
         for (int i = l; i <= r; ++i)
             ans = max(ans, dfs(len - 1, op + (!zero || i) + i, zero && !i, lower && i == l, upper && i == r));
         if (!zero && !upper && !lower) return st[len][op] = tot, f[len][op] = ans;
         return ans;
     }
     ```

### 最优关键思路或技巧
- **三进制分析**：将问题转化为三进制下的位数与数码和之和，简化了问题。
- **贪心策略**：通过动态维护最大值，优化了计算过程。
- **数位 DP**：适用于大规模数据的优化方法，适合深入学习。

### 可拓展之处
- **类似算法套路**：数位 DP 可以应用于其他进制相关的题目，如二进制、十进制等。
- **同类型题**：可以尝试解决其他与进制转换相关的题目，如二进制下的最大值问题。

### 推荐题目
1. [P2602 [ZJOI2010] 数字计数](https://www.luogu.com.cn/problem/P2602)
2. [P2657 [SCOI2009] windy 数](https://www.luogu.com.cn/problem/P2657)
3. [P4124 [CQOI2016] 手机号码](https://www.luogu.com.cn/problem/P4124)

---
处理用时：24.52秒