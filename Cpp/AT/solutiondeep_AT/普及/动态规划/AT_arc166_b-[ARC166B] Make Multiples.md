# 题目信息

# [ARC166B] Make Multiples

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc166/tasks/arc166_b

整数列 $ A=(A_1,\ldots,A_N) $ および，正整数 $ a,b,c $ が与えられます．

あなたはこの数列に対して，以下の操作を（$ 0 $ 回を含め）何回でも行うことができます．

- $ 1\leq\ i\leq\ N $ となる整数 $ i $ をひとつ選ぶ．$ A_i $ を $ A_i+1 $ で置き換える．
 
あなたの目的は，数列 $ A $ の中に，$ a $ の倍数，$ b $ の倍数，$ c $ の倍数がいずれもひとつ以上存在するようにすることです． 目的を達成するために必要な操作回数の最小値を求めてください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ a,\ b,\ c\ \leq\ 10^6 $
- $ 1\leq\ A_i\leq\ 10^{18} $
 
### Sample Explanation 1

操作を $ 2 $ 回行い $ A\ =\ (8,10,12) $ とすることで目的を達成できます．

### Sample Explanation 2

操作を $ 1 $ 回行い $ A\ =\ (14,11,60) $ とすることで目的を達成できます．

### Sample Explanation 3

操作を $ 3 $ 回行い $ A\ =\ (8,17,5,30,40,13) $ とすることで目的を達成できます．

### Sample Explanation 4

操作を $ 876537210887543205 $ 回行い $ A\ =\ (999994000010999994) $ とすることで目的を達成できます．

## 样例 #1

### 输入

```
3 3 4 5

8 9 11```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3 4 5

14 11 59```

### 输出

```
1```

## 样例 #3

### 输入

```
6 10 20 30

8 17 5 28 39 13```

### 输出

```
3```

## 样例 #4

### 输入

```
1 999997 999998 999999

123456789123456789```

### 输出

```
876537210887543205```

# AI分析结果

### 题目内容重写

【题目描述】

给定一个整数序列 \( A=(A_1,\ldots,A_N) \) 以及正整数 \( a, b, c \)。

你可以对该序列进行以下操作任意次数（包括零次）：

- 选择一个整数 \( i \)（\( 1\leq i\leq N \)），并将 \( A_i \) 替换为 \( A_i+1 \)。

你的目标是使序列 \( A \) 中包含至少一个 \( a \) 的倍数、至少一个 \( b \) 的倍数、以及至少一个 \( c \) 的倍数。求达成目标所需的最少操作次数。

### 题解分析与结论

本题的核心在于如何通过最少的操作次数，使得序列中的某些元素分别成为 \( a, b, c \) 的倍数。题解中主要采用了以下几种思路：

1. **动态规划（DP）**：通过状态压缩，记录前 \( i \) 个数是否已经满足 \( a, b, c \) 的倍数条件，并逐步更新最小操作次数。
2. **贪心与枚举**：通过枚举某些元素成为 \( a, b, c \) 的倍数，并计算所需的最小操作次数，最终取最小值。
3. **前缀后缀优化**：通过预处理每个数成为 \( a, b, c \) 的倍数所需的最小操作次数，并利用前缀后缀的最小值来优化计算。

### 精选题解

#### 题解1：作者：DerrickLo (赞：7)
- **星级**：★★★★★
- **关键亮点**：使用动态规划（DP）进行状态压缩，记录前 \( i \) 个数是否已经满足 \( a, b, c \) 的倍数条件，并逐步更新最小操作次数。代码清晰，思路明确，时间复杂度较低。
- **核心代码**：
```cpp
int n,a,b,c,x[200005],f[200005][2][2][2],A[200005],B[200005],C[200005],AB[200005],BC[200005],AC[200005],ABC[200005]; 
signed main(){
    cin>>n>>a>>b>>c;
    for(int i=1;i<=n;i++){
        cin>>x[i];
        A[i]=a-(x[i]-1)%a-1;
        B[i]=b-(x[i]-1)%b-1;
        C[i]=c-(x[i]-1)%c-1;
        AB[i]=lcm(a,b)-(x[i]-1)%lcm(a,b)-1;
        BC[i]=lcm(c,b)-(x[i]-1)%lcm(c,b)-1;
        AC[i]=lcm(a,c)-(x[i]-1)%lcm(a,c)-1;
        ABC[i]=lcm(lcm(a,b),c)-(x[i]-1)%lcm(lcm(a,b),c)-1;
    }
    memset(f,0x3f,sizeof f);
    f[0][0][0][0]=0;
    for(int i=1;i<=n;i++){
        f[i][0][0][0]=f[i-1][0][0][0];
        f[i][0][0][1]=min(f[i-1][0][0][1],f[i-1][0][0][0]+C[i]);
        f[i][0][1][0]=min(f[i-1][0][1][0],f[i-1][0][0][0]+B[i]);
        f[i][1][0][0]=min(f[i-1][1][0][0],f[i-1][0][0][0]+A[i]);
        f[i][0][1][1]=min({f[i-1][0][1][1],f[i-1][0][0][1]+B[i],f[i-1][0][1][0]+C[i],f[i-1][0][0][0]+BC[i]});
        f[i][1][0][1]=min({f[i-1][1][0][1],f[i-1][0][0][1]+A[i],f[i-1][1][0][0]+C[i],f[i-1][0][0][0]+AC[i]});
        f[i][1][1][0]=min({f[i-1][1][1][0],f[i-1][1][0][0]+B[i],f[i-1][0][1][0]+A[i],f[i-1][0][0][0]+AB[i]});
        f[i][1][1][1]=min({f[i-1][1][1][1],f[i-1][1][1][0]+C[i],f[i-1][1][0][1]+B[i],f[i-1][0][1][1]+A[i],f[i-1][0][0][1]+AB[i],f[i-1][0][1][0]+AC[i],f[i-1][1][0][0]+BC[i],f[i-1][0][0][0]+ABC[i]}); 
    }
    cout<<f[n][1][1][1];
    return 0;
}
```

#### 题解2：作者：樱雪喵 (赞：3)
- **星级**：★★★★
- **关键亮点**：通过枚举某些元素成为 \( a, b, c \) 的倍数，并计算所需的最小操作次数，最终取最小值。代码简洁，思路清晰，适合小规模数据。
- **核心代码**：
```cpp
#define int long long
const int N=2e5+5;
int n,a[N],vis[N];
struct node{int id,x;} c[N];
int b[3],L[N];
vector<int> d;
il bool cmp(node x,node y) {return x.x<y.x;}
il int lcm(int a,int b) {return a*b/__gcd(a,b);} 
signed main()
{
    n=read(); 
    for(int i=0;i<3;i++) b[i]=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int s=1;s<8;s++)
    {
        int lc=1;
        for(int i=0;i<3;i++) if((s>>i)&1) lc=lcm(lc,b[i]);
        for(int i=1;i<=n;i++) c[i].id=i,c[i].x=a[i]%lc?lc-a[i]%lc:0;
        sort(c+1,c+n+1,cmp);
        for(int i=1;i<=min(n,3ll);i++) 
            if(!vis[c[i].id]) vis[c[i].id]=1,d.push_back(a[c[i].id]);
    }
    int ans=3e18;
    for(int i=0;i<d.size();i++)
    {
        for(int j=0;j<d.size();j++)
        {
            for(int k=0;k<d.size();k++)
            {
                int res=0;
                for(int l=0;l<d.size();l++) L[l]=1;
                L[i]=lcm(L[i],b[0]),L[j]=lcm(L[j],b[1]),L[k]=lcm(L[k],b[2]);
                for(int l=0;l<d.size();l++) res+=d[l]%L[l]?L[l]-d[l]%L[l]:0;
                ans=min(ans,res);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

#### 题解3：作者：Fislett (赞：3)
- **星级**：★★★★
- **关键亮点**：使用状压 DP，记录前 \( i \) 个数是否已经满足 \( a, b, c \) 的倍数条件，并逐步更新最小操作次数。代码简洁，思路清晰，适合大规模数据。
- **核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
#define rint register int 
inline int read()
{
    int x = 0, flag = 1; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') flag = -1; else x = (c ^ 48); c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return flag * x;
}
inline void print(rint x, rint flag = 1)
{
    if (x < 0) putchar('-'), x = ~(x - 1);
    if (x > 9) print(x / 10, 0);
    putchar(x % 10 + 48);
    if (flag) putchar(flag & 1 ? ' ' : '\n');
}
int n, a, x, y, z, dp[200005][8], tmp[8], w[8];
inline int gcd(rint x, rint y) {return y ? gcd(y, x % y) : x;}
inline int lcm(rint x, rint y) {return x / gcd(x, y) * y;}
signed main()
{
    n = read(), x = read(), y = read(), z = read();
    w[1] = x, w[2] = y, w[4] = z, w[3] = lcm(x, y), w[5] = lcm(x, z), w[6] = lcm(y, z), w[7] = lcm(x, lcm(y, z));
    memset(dp, 0x7f, sizeof(dp)); dp[0][0] = 0;
    for (rint i = 1; i <= n; ++ i)
    {
        rint x = read();
        for (rint j = 1; j < 8; ++ j) tmp[j] = (x + w[j] - 1) / w[j] * w[j] - x;
        dp[i][0] = 0;
        for (rint j = 1; j < 8; ++ j)
        {
            dp[i][j] = dp[i - 1][j];
            for (rint k = j; k; k = (k - 1) & j)
                dp[i][j] = min(dp[i][j], dp[i - 1][j ^ k] + tmp[k]);
        }
    }
    print(dp[n][7]);
    return 0;
}
```

### 最优关键思路与技巧

1. **状态压缩动态规划**：通过二进制状态记录前 \( i \) 个数是否已经满足 \( a, b, c \) 的倍数条件，逐步更新最小操作次数。
2. **预处理与优化**：通过预处理每个数成为 \( a, b, c \) 的倍数所需的最小操作次数，并利用前缀后缀的最小值来优化计算。
3. **贪心与枚举**：通过枚举某些元素成为 \( a, b, c \) 的倍数，并计算所需的最小操作次数，最终取最小值。

### 可拓展之处

- **多条件优化**：可以扩展到更多条件的情况，如需要满足多个数的倍数条件。
- **前缀后缀优化**：在处理类似问题时，可以通过前缀后缀的最小值来优化计算。

### 推荐题目

1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：102.72秒