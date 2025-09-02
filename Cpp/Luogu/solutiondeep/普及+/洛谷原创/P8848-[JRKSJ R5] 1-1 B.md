# 题目信息

# [JRKSJ R5] 1-1 B

## 题目背景

本题是 1-1 的较难版本，较易版本为 [1-1 A](https://www.luogu.com.cn/problem/P8847)。

## 题目描述

给出一个序列 $a$，$\forall i\in [1,n],a_i\in \{1,-1\}$。

询问有多少个将 $a$ 重排后的序列使得该序列的最大子段和最小化。

称两个序列不同，当且仅当这两个序列有任意一个位置上的数不同。

## 说明/提示

最大子段和的定义：序列中一段区间的和的最大值。即 $\max_{1\le l\le r\le n} \sum_{i=l}^r a_i$。

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $20$ |
| $2$ | $100$ | $20$ |
| $3$ | $500$ | $20$ |
| $4$ | $10^4$ | $40$ |

对于 $100\%$ 的数据，$1\le n\le 10^4$，$a_i\in \{1,-1\}$。

## 样例 #1

### 输入

```
4
1 -1 1 -1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 1 1 -1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10
1 1 1 1 1 1 1 -1 -1 -1```

### 输出

```
40```

# AI分析结果

### 综合分析与结论
这些题解主要思路为根据序列中1和 - 1的数量关系分类讨论。当1的数量$a$小于等于 - 1的数量$b$时，最小最大子段和为1，通过插板法计算方案数为$\binom{b + 1}{a}$；当$a > b$时，最小最大子段和为$a - b$，通过动态规划求解方案数。难点在于证明$a > b$时满足最小最大子段和的序列前缀和范围在$[0, a - b]$。各题解在思路清晰度、代码可读性和优化程度上有所差异。

### 所选的题解
- **作者：critnos (5星)**
    - **关键亮点**：思路清晰，简洁明了地分类讨论并给出每种情况的答案，对$a > b$时答案下界的构造及充要条件证明严谨。
    - **重点代码**：无代码，核心实现思想为根据1和 - 1数量关系，利用组合数公式及充要条件分析求解。
- **作者：__K2FeO4 (4星)**
    - **关键亮点**：分类讨论清晰，结合图形解释$a > b$时的DP思路，代码给出滚动数组优化实现。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10086;
const int mod=998244353;
typedef long long ll;
int n,cp=0,cq=0;
vector<int> a[N];
signed main(){
    int x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&x),x==1?cp++:cq++;
    int m=cp-cq;
    if(m>0){
        for(int i=0;i<=cq;i++)
            for(int j=0;j<=m;j++){
                int s=0;
                if(i&&j!=m)s+=a[i-1][j+1];
                if(j)s+=a[i][j-1];
                a[i].push_back(i||j?s%mod:1);
            }
        printf("%d",a[cq][m]);
    }
    else{
        for(int i=0;i<=1-m;i++)
            for(int j=0;j<=cp;j++){
                int s=0;
                if(i)s+=a[i-1][j];
                if(j)s+=a[i][j-1];
                a[i].push_back(i||j?s%mod:1);
            }
        printf("%d",a[1-m][cp]);
    }
    return 0;
}
```
    - **核心实现思想**：先统计1和 - 1的数量，根据数量差$m$判断情况。$m > 0$时，通过状态转移方程$f_{i,j}=f_{i - 1,j + 1}+f_{i,j - 1}$进行DP计算；$m \leq 0$时类似计算，最后输出结果。
- **作者：do_while_true (4星)**
    - **关键亮点**：对两种情况的分析详细，证明严谨，代码实现中利用反射容斥可优化到更快复杂度。
    - **重点代码**：
```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
    r=0;bool w=0;char ch=getchar();
    while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
    while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
    return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2&...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s=1ll*s*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return s;
}
mt19937 rnd(time(NULL)^(ull)(new char));
inline int rd(int a,int b){
    return a+rnd()%(b-a+1);
}
#define Win do{puts("Yes");return ;}while(0)
#define Lose do{puts("No");return ;}while(0)
#define Alice do{puts("Alice");return ;}while(0)
#define Bob do{puts("Bob");return ;}while(0)
#define Fuyi do{puts("-1");return ;}while(0)
#define Line cerr << "----------\n"

const int N=1000010;

int n;
int fac[2*N],inv[2*N];
int C(int x,int y){
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int f,z;
int go(int a,int b,int c,int d){
    return C(c-a,(c-a+d-b)/2);
}
int go0(int a,int b,int k1,int k2);
int go1(int a,int b,int k1,int k2);
int go0(int a,int b,int k1,int k2){
    if(a<-b||a<b)return 0;
    return del(del(go(0,0,a,b),go(0,0,a,2*k2-b)),go1(a,b,k1,k2));
}
int go1(int a,int b,int k1,int k2){
    if(a<-b||a<b)return 0;
    if(a<2*k1-b||a<b-2*k1)return 0;
    return add(go0(a,2*k1-b,2*k1-k2,k2),go1(a,b,2*k1-k2,k2));
}
signed main(){
    #ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
    #endif
    read(n);
    fac[0]=1;for(int i=1;i<=3*n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[3*n]=qpow(fac[3*n],mod-2);
    for(int i=3*n-1;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1,x;i<=n;i++){
        read(x);
        if(x==1)++z;
        else ++f;
    }
    if(f>=z)cout << C(f+1,z) << '\n';
    else cout << go0(n,z-f,-1,z-f+1) << '\n';
    #ifdef do_while_true
        cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
    #endif
    return 0;
}
```
    - **核心实现思想**：统计1和 - 1数量，$f \geq z$时用组合数公式计算；$f < z$时，通过函数`go0`和`go1`利用反射容斥原理计算满足条件的路径方案数。

### 最优关键思路或技巧
1. **分类讨论**：根据1和 - 1的数量关系进行分类，简化问题求解。
2. **插板法**：在$a \leq b$时，巧妙运用插板法计算方案数。
3. **动态规划**：$a > b$时，通过定义合适的状态和状态转移方程求解，部分题解利用滚动数组优化空间。
4. **反射容斥**：如`do_while_true`的题解，将问题抽象为格路计数，利用反射容斥优化计算满足条件的路径方案数。

### 可拓展之处
同类型题常涉及序列重排后求特定指标（如最大子段和、最长上升子序列等）的最值及方案数。类似算法套路包括根据序列元素特征分类讨论，利用组合数学、动态规划等方法求解。

### 相似知识点洛谷题目
1. [P1192 台阶问题](https://www.luogu.com.cn/problem/P1192)：涉及动态规划，与本题$a > b$时的DP思路类似，通过状态转移方程求解方案数。
2. [P2602 数字计数](https://www.luogu.com.cn/problem/P2602)：结合分类讨论和组合数学知识，与本题分类讨论的思维方式相似。
3. [P1251 餐巾计划问题](https://www.luogu.com.cn/problem/P1251)：综合运用动态规划和费用流等知识，可锻炼分类讨论及复杂问题分析能力。

### 个人心得摘录与总结
无。 

---
处理用时：92.59秒