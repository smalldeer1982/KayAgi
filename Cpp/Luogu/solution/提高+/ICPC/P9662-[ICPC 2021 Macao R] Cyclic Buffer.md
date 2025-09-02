# [ICPC 2021 Macao R] Cyclic Buffer

## 题目描述

有一个大小为 $n$ 的循环缓冲区，读入流从第 $1$ 个位置到第 $k$ 个位置（两者都包含在内）。设 $a_i$ ($1 \le i \le n$) 是缓冲区初始时第 $i$ 个位置上的整数。此外，$a_1, a_2, \cdots, a_n$ 形成 $n$ 的一个排列。

我们将以递增顺序访问从 $1$ 到 $n$ 的所有整数（两者都包含在内）。只有当整数位于具有读入流的位置（即位于前 $k$ 个位置）时，才能访问整数。如果某个整数无法访问，则可以将整个缓冲区向任意方向移动任意次数。

- 如果我们向左移动缓冲区一次，则位于第 $i$ 个位置的整数将移动到第 $(i - 1)$ 个位置（如果 $i > 1$），并且位于第 $1$ 个位置的整数将移动到第 $n$ 个位置。
- 如果我们向右移动缓冲区一次，则位于第 $i$ 个位置的整数将移动到第 $(i + 1)$ 个位置（如果 $i < n$），并且位于第 $n$ 个位置的整数将移动到第 $1$ 个位置。

我们需要移动缓冲区的最小次数，以便以递增顺序访问所有整数。

## 样例 #1

### 输入

```
2
5 3
2 4 3 5 1
1 1
1```

### 输出

```
3
0```

# 题解

## 作者：xieziheng (赞：2)

这道题细节真多。

首先容易得到一个简单的 dp，设 $dp_{i,j}$ 表示前 $i$ 个数已经做完，此时 $i$ 在 $j$ 位置的最小值。但是发现这个 dp 有很多位置是没有意义的。所以可以优化为设 $dp_{i,0/1}$ 表示前 $i$ 个数已经做完，此时 $i$ 在 $1/m$ 位置的最小值。转移即：找到此时不在前 $m$ 个数中的第一个比 $i$ 大的数 $j$，转移到 $dp_{j,0/1}$ 上。

但是这样是 $O(n^2)$ 的，瓶颈在于找到 $j$。发现这个可以提前预处理。具体而言，首先断环成链，把数组倍长，然后从小到大扫所有的长度为 $k$ 的区间，每次加一个，删一个，然后找到比第一个比区间左或右端点大的值。这个玩意做法挺多的。可以用树状数组维护。树状数组倍增：将区间内的数对应的位置记为 $0$，区间外的数对应的位置记为 $1$。开始为全 $1$，加进来一个就改成 $0$，删一个改成 $1$。查询就先查个当前位置前缀和，然后倍增找到第一个前缀和比这个严格大的位置，就行了。

$code:$

```cpp
//#pragma GCC optimize("O2,O3,Ofast,inline,unroll-loops")
//#pragma GCC target("avx2,sse4")
#include <bits/stdc++.h>
#define il inline
#define RET {puts("0");continue;}
using namespace std;
typedef long long ll;
il int read(){
    int x=0,c=getchar();
    while(c<'0' || c>'9') c=getchar();
    while(c>='0' && c<='9') x=x*10+c-48,c=getchar();
    return x;
}
il int ab(int x){return x>0?x:-x;}
il void cmin(ll &x,ll y){x=x>y?y:x;}
const ll inf=1e18;
const int N=2e6+5;
int T,n,m,a[N],p[N],to[N][2];ll ans,dp[N][2];
il ll dis(int x,int y){return min(ab(x-y),n-ab(x-y));}
int tree[N];
il void add(int x,int v){while(x<=n) tree[x]+=v,x+=(x&-x);}
il int get(int x){
    int ret=0;
    while(x) ret+=tree[x],x-=(x&-x);
    return ret;
}
il int jump(int v){
    int x=0;
    for(int i=19;i>=0;--i) if(x+(1<<i)<=n && tree[x+(1<<i)]<=v) x+=(1<<i),v-=tree[x];
    return x+1;
}
il int f(int x){
    if(x<=0) return x+n;
    if(x>n) return x-n;
    return x;
}
int x,y,z;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);ans=inf,x=0;
        for(int i=1;i<=n;++i) dp[i][0]=dp[i][1]=inf,tree[i]=0;
        for(int i=1;i<=n;++i) a[i]=read(),p[a[i]]=i,a[i+n]=a[i],add(i,1);
        for(int i=1;i<n+m;++i){
            add(a[i],-1);
            if(i>m) add(a[i-m],1);
            if(i>=m) to[a[i-m+1]][0]=jump(get(a[i-m+1])),to[a[i]][1]=jump(get(a[i]));
            if(i==m) x=jump(0);
        }
        if(x>n) RET
        dp[x][0]=dis(1,p[x]),dp[x][1]=dis(m,p[x]);
        for(int i=1;i<=n;++i){
            x=to[i][0],y=p[i],z=p[x];
            if(x>n) cmin(ans,dp[i][0]);
            else cmin(dp[x][0],dp[i][0]+dis(y,z)),cmin(dp[x][1],dp[i][0]+dis(f(y+m-1),z));
            x=to[i][1],y=p[i],z=p[x];
            if(x>n) cmin(ans,dp[i][1]);
            else cmin(dp[x][0],dp[i][1]+dis(f(y-m+1),z)),cmin(dp[x][1],dp[i][1]+dis(y,z));
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

