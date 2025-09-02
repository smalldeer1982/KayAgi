# 题目信息

# 「DTOI-5」进行一个排的重 (Minimum Version)

## 题目背景

**本题与 Maximum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个 pair $(p_i, q_i)$。

为了让 $a$ 看起来规整一些，他钦定 $p, q$ 分别均为长为 $n$ 的排列。

为了对 $a$ 的规整程度进行量化计算，他给出了一个权值函数 $f(a) = \displaystyle\sum_{i = 1}^n ([p_i > \max_{j = 1}^{i - 1} p_j] + [q_i > \max_{j = 1}^{i - 1} q_j])$。**注意 $i = 1$ 时两个方括号都能取到值，因为我们认为 $\displaystyle\max_{j = 1}^0 p_j = \displaystyle\max_{j = 1}^0 q_j = -\infty$。**

为了让 $a$ 看起来更加规整，他决定分别以某种方式重排 $a$ 得到 $a'$ 使得 $f(a')$ 最小。**注意重排时必须将 $a'_i = (p'_i, q'_i)$ 视为整体。**

他希望你求出 $f(a')_{\min}$ 的值，以及分别有多少个 $a'$ 可以取到 $f(a')_{\min}$。

由于方案数可能很大，你只需要求出结果对 $998244353$ 取模的值。

## 说明/提示

**【数据范围】**

$$
\def\or{\operatorname{or}}
%\def\arrayscretch{1.5}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask}&n\le &\textbf{Points}\cr\hline
\sf1&10&10 \operatorname{pts}\cr\hline
\sf2&500&20 \operatorname{pts}\cr\hline
\sf3&5\times10^3&20 \operatorname{pts}\cr\hline
\sf4&10^5&20 \operatorname{pts}\cr\hline
\sf5&5\times10^5&30 \operatorname{pts}\cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$1 \leq p_i, q_i \leq n$，保证 $p, q$ 均为**排列**。

## 样例 #1

### 输入

```
5
1 5 2 4 3
1 4 2 5 3```

### 输出

```
3 48```

# AI分析结果

### 综合分析与结论
这几道题解均围绕对给定序列重排使权值函数最小的问题展开，核心思路是分类讨论。主要分两种情况：存在 $p_i = q_i = n$ 与不存在 $p_i = q_i = n$。算法要点在于根据不同情况计算最小权值及对应方案数，难点是在不存在 $p_i = q_i = n$ 时，分析如何排列能使权值最小并准确计算方案数。
各题解质量相近，思路清晰，代码实现基本相同，但在代码可读性和优化程度上略有差异。

### 所选题解
- **作者：FFTotoro（5星）**
    - **关键亮点**：思路清晰简洁，分类讨论明确，代码实现简洁高效，利用乘法逆元处理除法取模，逻辑清晰，无冗余代码。
    ```cpp
    int f(int n){
      int s=1;
      for(int i=2;i<=n;i++)
        (s*=i)%=mod;
      return s;
    }
    int qpow(int a,int b){
      int r=1;
      while(b){
        if(b&1)r=r%mod*a%mod;
        a=a%mod*a%mod; b>>=1;
      }
      return r;
    }
    int inv(int x){return qpow(x,mod-2);}
    main(){
      ios::sync_with_stdio(false);
      int n,x,y; cin>>n;
      vector<pii> a(n);
      for(auto &i:a)cin>>i.first;
      for(auto &i:a)cin>>i.second;
      for(auto [p,q]:a){
        if(p==n)x=q; if(q==n)y=p;
      } 
      if(x==n)cout<<"2 "<<f(n-1)<<endl; 
      else cout<<"3 "<<f(n-1)*((inv(n-x)+inv(n-y))%mod)%mod<<endl; 
      return 0;
    }
    ```
    - **核心代码思想**：`f` 函数计算阶乘，`qpow` 函数实现快速幂，`inv` 函数利用快速幂求逆元。主函数中读入数据，根据情况分类计算最小权值和方案数并输出。
- **作者：DengDuck（4星）**
    - **关键亮点**：对每种情况的分析详细，通过组合数公式推导方案数，代码结构清晰，变量命名易懂。
    ```cpp
    LL ksm(LL x,LL y)
    {
        LL ans=1;
        while(y)
        {
            if(y&1)ans=ans*x%mod;
            x=x*x%mod,y>>=1;
        }
        return ans;
    }
    int main()
    {
        cin>>n;
        for(int i=1;i<=n-1;i++)F=F*i%mod;
        for(int i=1;i<=n;i++)cin>>a[i].p;
        for(int i=1;i<=n;i++)cin>>a[i].q;
        for(int i=1;i<=n;i++)
        {
            if(a[i].p==n)x=a[i].q;
            if(a[i].q==n)y=a[i].p;
        }
        if(x==n)
        {
            cout<<2<<' '<<F<<endl;
        }
        else 
        {
            cout<<3<<' '<<F*(ksm(n-x,mod-2)+ksm(n-y,mod-2))%mod<<endl;
        }
    }
    ```
    - **核心代码思想**：`ksm` 函数实现快速幂，主函数读入数据，预处理阶乘，根据不同情况计算并输出最小权值和方案数。
- **作者：Leasier（4星）**
    - **关键亮点**：先证明最优解的一些性质，逻辑严谨，在计算方案数时通过排列组合公式详细推导，代码注释详细。
    ```cpp
    inline ll arrange(int n, int m){
        if (n < 0 || m < 0 || n < m) return 0;
        return fac[n] * inv_fac[n - m] % mod;
    }
    int main(){
        int n = read(), pos1, pos2;
        init(n);
        for (register int i = 1; i <= n; i++){
            p[i] = read();
            if (p[i] == n) pos1 = i;
        }
        for (register int i = 1; i <= n; i++){
            q[i] = read();
            if (q[i] == n) pos2 = i;
        }
        if (pos1 == pos2){
            printf("2 %lld", fac[n - 1]);
        } else {
            ll ans = 0;
            for (register int i = 0; i < q[pos1]; i++){
                ans = (ans + fac[n - i - 2] * arrange(q[pos1] - 1, i) % mod) % mod;
            }
            for (register int i = 0; i < p[pos2]; i++){
                ans = (ans + fac[n - i - 2] * arrange(p[pos2] - 1, i) % mod) % mod;
            }
            printf("3 %lld", ans);
        }
        return 0;
    }
    ```
    - **核心代码思想**：`arrange` 函数计算排列数，主函数读入数据，初始化阶乘和逆元，根据情况计算最小权值和方案数并输出。

### 最优关键思路或技巧
- **分类讨论**：清晰地将问题分为两种情况，分别分析计算，简化问题复杂度。
- **利用排列组合性质**：在计算方案数时，通过分析排列的限制条件，利用组合数、排列数公式及阶乘性质进行计算。
- **乘法逆元处理取模除法**：在涉及除法取模运算时，使用乘法逆元将除法转化为乘法，保证结果的正确性。

### 可拓展思路
此类题目属于排列组合与优化问题结合的类型，类似套路是先分析最优解的特征，再通过分类讨论计算不同情况下的结果。可拓展到其他带有特殊权值函数的排列优化问题，关键在于找到权值与排列顺序的关系。

### 相似知识点洛谷题目
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：考察组合数与数论知识结合。
- [P1850 换教室](https://www.luogu.com.cn/problem/P1850)：涉及概率与动态规划，与本题分析最优情况思路类似。
- [P3195 [HNOI2008] 玩具装箱](https://www.luogu.com.cn/problem/P3195)：通过分析最优决策点，利用斜率优化动态规划，与本题分析最优排列思路有相通之处。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：54.29秒