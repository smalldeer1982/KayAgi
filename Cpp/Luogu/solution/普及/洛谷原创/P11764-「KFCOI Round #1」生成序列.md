# 「KFCOI Round #1」生成序列

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/w0cqwhal.png)

## 题目描述

你需要生成一个长度为 $n$ 的非负整数序列 $a$。

$a$ 满足 $m$ 条限制，第 $i$ 条限制形如：

* 若将 $a_{x_i}$ 修改为 $y_i$，则序列中恰好有 $k_i$ 个区间满足修改前后，其区间和的变化量不超过 $p_i$。

各个限制间独立，即修改操作没有真的执行。

为了防止序列中的数过大，如果存在 $a_i>2\times 10^9$，则认为序列 $a$ 不满足限制。

若有多个满足条件的序列，输出任意一个即可。若无解，输出 `-1`。

## 说明/提示

### 样例解释

对于第一组数据：

$a_1=6$，$a_2=20$，$a_3=18$，$a_4=4$。

若将 $a_4$ 改为 $1$，则有 $6$ 个区间的区间和变化量不超过 $1$，分别为：

`[1,1],[1,2],[1,3],[2,2],[2,3],[3,3]`。

若将 $a_3$ 改为 $20$，则所有区间的区间和变化量均不超过 $12$。

若将 $a_2$ 改为 $3$，则有 $4$ 个区间的区间和变化量不超过 $4$，分别为：

`[1,1],[3,3],[3,4],[4,4]`。

若将 $a_4$ 改为 $9$，则所有区间的区间和变化量均不超过 $10$。

可能存在其他解，输出任意一个即可。

对于第二组数据，可以证明没有符合条件的序列满足限制。

---

### 数据范围

**本题采用捆绑测试**。


- Subtask 1（10 points）：$1 \le n \le 10$，$1 \le m \le 10$，$1 \le y_i \le 10$，$1 \le p_i\le 10$。
- Subtask 2（10 points）：$m=1$。
- Subtask 3（10 points）：$k_i=\frac{n(n+1)}{2}$。
- Subtask 4（20 points）：$1 \le n \le 10 ^ 4$，$1 \le m \le 10 ^ 4$，$1 \le y_i \le 10 ^4$，$1 \le p_i\le 10^4$。
- Subtask 5（50 points）：无特殊限制。


对于所有测试数据，$1 \le n\le 10^5$，$1\le m\le 10^5$，$1 \le T\le 10$，$1\le x_i\le n$，$1 \le k_i\le \frac{n(n+1)}{2}$，$1 \le y_i \le 10 ^ 9$，$0 \le p_i\le 10^9$。

## 样例 #1

### 输入

```
2
4 4
4 1 6 1
3 20 10 12
2 3 4 4
4 9 10 10
3 2
1 2 6 0
1 3 6 0```

### 输出

```
6 20 18 4
-1```

# 题解

## 作者：_lmh_ (赞：3)

所有操作独立，所以只需要考虑一个数 $a_x$。

显然合法的 $k$ 只有两种取值：要么所有区间都合法，此时 $a_x\in [y-p,y+p]$；要么不包含 $x$ 的区间合法，此时 $a_x\notin [y-p,y+p]$。

首先考虑第一类限制，它可以把 $a_x$ 的范围缩小到一个区间 $[L,R]$；然后按照左端点从小到大考虑第二类限制 $[l,r]$，如果 $L<l$ 则 $L$ 合法，否则 $L\leftarrow \max\{L,r+1\}$，如果 $L>R$ 则无解。

---

## 作者：gesic (赞：0)

容易发现，对于任意的 $ x_i,y_i,p_i $，满足条件的 $ k_i $ 只有以下两种情况，否则无解。

1. $ |a_{x_i} - y_i| \leq p_i \Rightarrow k_i = \frac{n (n + 1)}{2} $，即每个区间改变量都不超过 $ p_i $。
2. $ |a_{x_i} - y_i| > p_i \Rightarrow k_i = \frac{x_i (x_i - 1)}{2} + \frac{(n - x_i) (n - x_i + 1)}{2} $，即不包含 $ x_i $ 的区间改变量不超过 $ p_i $。

因此可以确定 $ a_i $ 的取值区间。若是情况 $ 1 $，则 $ a_{x_i} \in [y_i - p_i , y_i + p_i] $；否则为情况 $ 2 $ ，$ a_{x_i} \in [0 , y_i - p_i)  \cup ( y_i + p_i, 2 \times 10^9] $。

实现用 `set` 维护每个 $ a_i $ 的取值区间即可，若 `set` 为空，则无解。

时间 $ O( T m \log_2 m ) $。

code：

```cpp
#include<bits/extc++.h>
#define ll long long
#define gc getchar_unlocked
#define pc putchar_unlocked
#define sc scanf
#define pr printf
#define fu(v,s,e) for(int v=s;v<=(e);v++)
#define fd(v,s,e) for(int v=s;v>=(e);v--)
#define ciallo cerr<<"Ciallo~\n"
#define fuck cerr<<"Fuck you\n"
#define ___ cerr<<"----------------\n"
#define ___2 cerr<<"================\n"
#define mem(a,x) memset(a,x,sizeof(a))
#define itn int
#ifdef DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
using namespace std;
#ifdef INFO
struct __info{~__info(){cerr<<'\n';___;cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms.\n";FILE* mem=fopen("/proc/self/status","r");char str[128];while(fgets(str,128,mem)!=NULL) if(strncmp(str,"VmRSS:",6)==0){cerr<<"Memory: "<<atoi(str+6)/1024.0<<" MB.\n";break;}}}_info_tmp;
#endif
#ifdef PAI
struct __pai{~__pai(){cerr<<" ( "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms , ";FILE* mem=fopen("/proc/self/status","r");char str[128];while(fgets(str,128,mem)!=NULL) if(strncmp(str,"VmRSS:",6)==0){cerr<<atoi(str+6)/1024.0<<" MB )\n";break;}}}_pai_tmp;
#endif
inline ll in(){char c=gc();ll x=0,f=1;while((c<'0'||c>'9')&&c!='-') c=gc();if(c=='-') f=-1,c=gc();while(c>='0'&&c<='9') x=x*10+c-'0',c=gc();return x*f;}
int _t;
int n,m;
#define A_L 0
#define A_R 2000000000
struct node{
    int l,r;
};
inline bool operator<(const node &p,const node &q){
    if(p.l^q.l) return p.l<q.l;
    return p.r<q.r;
}
set<node> st[100005];
// 更新a[i]取值范围
inline void insert(set<node> &a,int l,int r,int tp){
    set<node> b;
    if(tp){  // [0,l)∩(r,2e9]
        for(const node& x:a){
            if(x.l<=l) b.emplace(node{x.l,min(l,x.r)});
            if(x.r>=r) b.emplace(node{max(r,x.l),x.r});
        }
    }else for(const node& x:a) if(x.r>=l&&x.l<=r) b.emplace(node{max(l,x.l),min(r,x.r)});  // [l,r]
    swap(a,b);
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    _t=in();
    while(_t--){
        n=in(),m=in();
        fu(i,1,n) st[i].clear(),st[i].emplace(node{A_L,A_R});
        int fg=0;
        while(m--){
            itn x=in(),y=in();
            ll k=in();
            int p=in();
            if(fg) continue;
            if(k==1ll*n*(n+1)/2) insert(st[x],y-p,y+p,0);
            else if(k==1ll*x*(x-1)/2+1ll*(n-x)*(n-x+1)/2) insert(st[x],y-p-1,y+p+1,1);
            else fg=1;  // k不符合要求
            if(st[x].empty()) fg=1;  // 取值区间为空
        }
        if(fg){
            pr("-1\n");
            continue;
        }
        fu(i,1,n) pr("%d ",st[i].begin()->l);
        pc('\n');
    }
    return 0;
}
```

---

## 作者：E_M_T (赞：0)

# Sub1

暴力。

# Sub2


因为每次只修改一个位置，区间和的变化量就两种：

* 区间包含 $x$，变化量 $|a_x-y|$。
* 区间不包含 $x$，变化量 $0$。

于是合法的 $k$ 一共只有两种取值：

* 若 $|a_x-y|\le q$，则所有区间均满足，即 $k=\frac{n(n+1)}{2}$。
* 若 $|a_x-y|> q$，则不包含 $x$ 的区间满足，即 $k=\frac{n(n+1)}{2}-x(n-x+1)$。

现在已知 $k$，一共三种情况：

* $k=\frac{n(n+1)}{2}$，则 $a_x\in [y-q,y+q]$。
* $k=\frac{n(n+1)}{2}-x(n-x+1)$，则 $a_x\not \in [y-q,y+q]$。
* 其他情况，无解。

称第一种情况带来的限制为“合法区间”，第二种情况带来的限制为“不合法区间”。

Sub 2 只有一个限制，特判即可。


# Sub3

只有合法区间。

若 $a_x$ 有两个合法区间，则 $a_x$ 的取值必须在两个合法区间的交集内。

对每个数维护其合法区间的交集，若某个数的交集为空则无解，否则输出交集内的任意一个数即可。

显然，一堆区间的交集必定是一个连续的区间，维护交集的左右端点即可。


# Sub4

上文提到合法区间的合并是取交集，而类似的，不合法区间的合并是取并集。

对每个数分别维护交集和并集，最后看合法区间的交集是否被不合法区间的并集包含即可。

最简单的解法是对每个数开 $2$ 个大小为 $V$ 的 bitset 分别维护交并。

复杂度 $O(\frac{nV}{w})$。

# Sub5

由于交集一定是一段区间，考虑用这个区间对比并集里所有区间，判断是否有包含。

本题存在另解，比如将限制离线使用权值线段树维护。

$O(n\log n)$ 可过，可能存在线性但我没管。

---

