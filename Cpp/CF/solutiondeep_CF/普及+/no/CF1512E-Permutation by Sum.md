# 题目信息

# Permutation by Sum

## 题目描述

A permutation is a sequence of $ n $ integers from $ 1 $ to $ n $ , in which all the numbers occur exactly once. For example, $ [1] $ , $ [3, 5, 2, 1, 4] $ , $ [1, 3, 2] $ are permutations, and $ [2, 3, 2] $ , $ [4, 3, 1] $ , $ [0] $ are not.

Polycarp was given four integers $ n $ , $ l $ , $ r $ ( $ 1 \le l \le r \le n) $ and $ s $ ( $ 1 \le s \le \frac{n (n+1)}{2} $ ) and asked to find a permutation $ p $ of numbers from $ 1 $ to $ n $ that satisfies the following condition:

- $ s = p_l + p_{l+1} + \ldots + p_r $ .

For example, for $ n=5 $ , $ l=3 $ , $ r=5 $ , and $ s=8 $ , the following permutations are suitable (not all options are listed):

- $ p = [3, 4, 5, 2, 1] $ ;
- $ p = [5, 2, 4, 3, 1] $ ;
- $ p = [5, 2, 1, 3, 4] $ .

 But, for example, there is no permutation suitable for the condition above for $ n=4 $ , $ l=1 $ , $ r=1 $ , and $ s=5 $ .Help Polycarp, for the given $ n $ , $ l $ , $ r $ , and $ s $ , find a permutation of numbers from $ 1 $ to $ n $ that fits the condition above. If there are several suitable permutations, print any of them.

## 样例 #1

### 输入

```
5
5 2 3 5
5 3 4 1
3 1 2 4
2 2 2 2
2 1 1 3```

### 输出

```
1 2 3 4 5 
-1
1 3 2 
1 2 
-1```

# AI分析结果

### 题目翻译
# 按和排列

## 题目描述
一个排列是一个由 1 到 n 的整数组成的序列，其中所有数字恰好出现一次。例如，[1]、[3, 5, 2, 1, 4]、[1, 3, 2] 是排列，而 [2, 3, 2]、[4, 3, 1]、[0] 不是。

给了 Polycarp 四个整数 n、l、r（1 ≤ l ≤ r ≤ n）和 s（1 ≤ s ≤ n(n + 1) / 2），并要求他找到一个 1 到 n 的数字的排列 p，使其满足以下条件：
- s = p[l] + p[l + 1] + ... + p[r]。

例如，对于 n = 5、l = 3、r = 5 和 s = 8，以下排列是合适的（并非列出了所有选项）：
- p = [3, 4, 5, 2, 1]；
- p = [5, 2, 4, 3, 1]；
- p = [5, 2, 1, 3, 4]。

但是，例如对于 n = 4、l = 1、r = 1 和 s = 5，不存在满足上述条件的排列。请帮助 Polycarp，对于给定的 n、l、r 和 s，找到一个满足上述条件的 1 到 n 的数字的排列。如果有多个合适的排列，打印其中任意一个。

## 样例 #1
### 输入
```
5
5 2 3 5
5 3 4 1
3 1 2 4
2 2 2 2
2 1 1 3
```
### 输出
```
1 2 3 4 5 
-1
1 3 2 
1 2 
-1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断是否有解，再构造出满足条件的排列。不同题解的构造方法有所不同，主要有贪心构造和动态规划构造两种。
- **思路对比**：
    - gi_A 和 wheneveright、Milthm 的题解采用贪心策略，通过逐步调整数字来构造排列。
    - haokee 的题解使用动态规划，通过 01 背包的思想来选择数字。
- **算法要点**：
    - 贪心解法的要点在于判断和的范围以及逐步调整数字。
    - 动态规划解法的要点在于状态定义和状态转移。
- **解决难点**：
    - 难点在于判断无解的情况和如何构造出满足条件的排列。

### 所选题解
- **gi_A（5星）**：
    - **关键亮点**：思路清晰，先证明了选取 k 个不重复数字和的值域为一段区间，然后利用该结论快速判断 s 是否合法，最后通过枚举数字构造排列，代码实现简洁。
- **wheneveright（4星）**：
    - **关键亮点**：采用贪心思想，先构造初始序列，再通过贪心调整使和等于 s，代码中对不可能满足的情况进行了判断。
- **Milthm（4星）**：
    - **关键亮点**：先判断无解情况，然后通过逐步加 1 的方式构造排列，逻辑清晰。

### 重点代码
#### gi_A 的题解
```cpp
int main()
{
    int T=read();
    while(T--){
        int n=read();
        int l=read();
        int r=read();
        int s=read();
        int len=r-l+1,L=l;
        mn[0]=mx[0]=0;
        for(int i=1;i<=n;i++){
            mn[i]=(i+1)*i/2;
            mx[i]=(n+n-i+1)*i/2;
        }
        for(int i=1;i<=n;i++)v[i]=0;
        for(int i=1;i<=n;i++)
            if(s-i>=mn[len-1]&&s-i<=mx[len-1]){
                a[l++]=i;len--;s-=i;v[i]=1;
            }
        if(l!=r+1){cout<<-1<<"\n";continue;}
        tot=0;
        for(int i=1;i<=n;i++)
            if(!v[i]){if(tot==L-1)tot=r;a[++tot]=i;}
        for(int i=1;i<=n;i++)cout<<a[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
```
**核心实现思想**：先计算在 n 中选 i 个数之和的最小和最大值，然后枚举数字，判断是否可以选择，若可以则更新相关变量，最后将未选的数字依次填入排列中。

#### wheneveright 的题解
```cpp
int main () {
    cin >> T;
    while (T--) {
        cin >> N >> L >> R >> S;
        memset (vis, 0, sizeof vis);
        for (register int i = L; i <= R; i++)
            A[i] = i - L + 1, vis[A[i]] = true, S -= A[i];
        if (S < 0) {printf ("-1\n"); continue;}
        for (register int i = R; i >= L; i--) {
            if (S >= N - R + L - 1) {
                S -= N - R + L - 1;
                vis[A[i]] = false;
                A[i] += N - R + L - 1;
                vis[A[i]] = true;
                continue;
            }
            vis[A[i]] = false;
            A[i] += S; S = 0;
            vis[A[i]] = true;
            break;
        }
        now = 0;
        if (S != 0) {printf ("-1\n"); continue;}
        for (register int i = 1; i <= N; i++) {
            if (L <= i && i <= R) continue;
            while (vis[++now]); A[i] = now;
        }
        for (register int i = 1; i <= N; i++) printf ("%d%c", A[i], i == N ? '\n' : ' ');
    }
    return 0;
}
```
**核心实现思想**：先构造初始序列，计算剩余和 S，若 S 小于 0 则无解，然后从后往前调整序列，使和等于 s，最后构造其他位置的数字。

#### Milthm 的题解
```cpp
int main(){
    cin>>t;
    while(t--){
        sum=0;
        cin>>n>>l>>r>>s;
        int len=r-l+1;
        if(s>(n-len+1+n)*len/2||s<(1+len)*len/2){
            cout<<"-1\n";
        }
        else{
            for(int i=1;i<=len;++i){
                q[i]=1;
                sum+=i;
            }
            quo=n;
            for(int i=len;sum!=s;--i,--quo){
                int syx=i;
                while(sum!=s&&syx<quo){
                    q[syx]=0;
                    q[++syx]=1;
                    sum++;
                }
            }
            quo=0;
            if(l==1)goto R;
            for(int i=1;i<=n;++i){
                if(q[i]==0){
                    quo++;
                    cout<<i<<" ";
                    q[i]=2; 
                    if(quo==l-1)break;
                }
            }
            R:;
            for(int i=1;i<=n;++i){
                if(q[i]==1){
                    cout<<i<<" ";
                    q[i]=2;
                }
            }
            for(int i=1;i<=n;++i){
                if(q[i]==0)cout<<i<<" ";
                q[i]=0;
            }
            cout<<endl;
        }
    }
    return 0;
}
```
**核心实现思想**：先判断无解情况，然后构造初始序列并计算和，通过逐步加 1 的方式调整序列使和等于 s，最后按顺序输出排列。

### 最优关键思路或技巧
- 先判断无解情况，通过计算选取 k 个不重复数字和的最小和最大值来判断 s 是否合法。
- 贪心构造时，从最小的数字开始选择，逐步调整数字使和等于 s。

### 拓展思路
同类型题或类似算法套路：其他构造排列或组合满足特定条件的题目，可参考贪心构造和动态规划构造的思路。

### 洛谷题目推荐
- P1036 选数（组合数学）
- P1216 [USACO1.5][IOI1994] 数字三角形 Number Triangles（动态规划）
- P1002 [NOIP2002 普及组] 过河卒（动态规划）

---
处理用时：60.70秒