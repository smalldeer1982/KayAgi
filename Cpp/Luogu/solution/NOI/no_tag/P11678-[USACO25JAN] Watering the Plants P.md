# [USACO25JAN] Watering the Plants P

## 题目描述

Bessie 的花园中有 $N$ 株植物，从左到右编号为 $1$ 到 $N$（$2\leq N\leq 5\cdot 10^5$）。Bessie 知道植物 $i$ 至少需要 $w_i$（$0\leq w_i \leq 10^6$）单位的水。

Bessie 有一个十分古怪的灌溉系统，包含 $N-1$ 条水渠，编号为 $1$ 到 $N-1$。每条水渠 $i$ 有一个相关的单位费用 $c_i$（$1\le c_i\le 10^6$），Bessie 可以支付费用 $c_i k$ 来为植物 $i$ 和 $i+1$ 各提供 $k$ 单位的水，其中 $k$ 是一个非负整数。

Bessie 很忙，可能没有时间使用所有的水渠。对于每一个 $2\leq i \leq N$，计算仅使用前 $i-1$ 条水渠灌溉植物 $1$ 到 $i$ 所需要的最小费用。

## 说明/提示

样例 1 解释：

使用第一条水渠灌溉前 $2$ 株植物的最小费用是通过使用第一条水渠 $69$ 次，支付 $30 \cdot 69 = 2070$。

灌溉前 $3$ 株植物的最小费用是通过使用第一条水渠 $39$ 次，第二条水渠 $33$ 次，支付 $39 \cdot 30 + 29 \cdot 33 = 2127$。

- 测试点 $4$：$N \leq 200$，并且所有 $w_i \leq 200$。
- 测试点 $5\sim 6$：所有 $w_i \leq 200$。
- 测试点 $7\sim 10$：$N \leq 5000$。
- 测试点 $11\sim 14$：所有 $w_i$ 和 $c_i$ 独立地均匀随机生成。
- 测试点 $15\sim 19$：没有额外限制。

## 样例 #1

### 输入

```
3
39 69 33
30 29```

### 输出

```
2070
2127```

## 样例 #2

### 输入

```
3
33 82 36
19 1```

### 输出

```
1558
676```

## 样例 #3

### 输入

```
8
35 89 44 1 35 3 62 50
7 86 94 62 63 9 49```

### 输出

```
623
4099
4114
6269
6272
6827
8827```

# 题解

## 作者：lsj2009 (赞：8)

### Preface

赛后 20min 调出，，，

### Description

定义 $f(a_{1\sim m},b_{1\sim m-1})$ 的值为：
- 对于所有满足如下不等式组的 **非负整数** 序列 $x_{1\sim n-1}$：
  $$
  \begin{cases}
  x_1 \ge a_1\\
  x_1+x_2 \ge a_2\\
  \cdots\\
  x_{n-2}+x_{n-1}\ge a_{n-1}\\
  x_{n-1}\ge a_n
  \end{cases}
  $$
  中 $\sum\limits_{i=1}^{n-1} b_ix_i$ 的最小值。

给定 $a_{1\sim n}$ 和 $b_{1\sim n-1}$，对于任意 $2\le i\le n$ 求出 $f(a_{1\sim i},b_{1\sim i-1})$ 的值。

$1\le n\le 5\times 10^5$，$0\le a_i\le 10^6$。

### Solution

记 $V=\max{a_i}$。

考虑一个暴力是从左往右 dp，记 $f_{i,j}$ 表示 $x_{1\sim i-1}$ 的取值已经确定、前 $i-1$ 个不等式的限制已经满足且 $x_{i-1}=j$ 的 $\sum\limits_{j<i} b_jx_j$ 的最小值。

则 $f(a_{1\sim i},b_{1\sim i-1})$ 的值就是 $\min\limits_{j\ge a_i} f_{i,j}$。

简单粗暴地可以得到转移方程：

$$f_{i,j}\gets \left(\min\limits_{k\ge a_{i-1}-j} f_{i-1,k}\right)+j\cdot b_{i-1}$$

可以做到 $\mathcal{O}(nV^2)$ 或 $\mathcal{O}(nV)$。

考虑优化，然后就一拍脑袋说：**我猜他是凸的**！看看能不能上个 **slope trick**！

当然有点 corner case：$i\le 2$ 时有些 $f_{i,j}$ 是不合法的，也就是更严谨的是：
- 我们断言：**当 $i\ge 3$ 时 $f_{i,*}$ 是下凸的**。

套路地考虑 **归纳证明**：
- 当 $i=3$ 时，不妨对初始的 corner case 暴力讨论一下：
  - 当 $i=1$ 时只有 $f_{1,0}=0$，其余值均可以视作 $\infty$。
  - 当 $i=2$ 时那就是 $j\ge a_1$ 部分是一条从 $(a_1,a_1b_1)$ 开始斜率为 $b_1$ 的射线。其余部分为 $\infty$。
  - 当 $i=3$ 时：
    - 若 $a_2\le a_1$ 则全局范围内为一条从 $(0,a_1b_1)$ 开始斜率为 $b_2$ 的射线。
    - 若 $a_2>a_1$ 则全局范围内为一条 $(0,a_2b_1)-(a_2-a_1,a_1b_1+(a_2-a_1)b_2)$ 斜率为 $b_2-b_1$ 的线段和一条从 $(a_2-a_1,a_1b_1+(a_2-a_1)b_2)$ 开始的斜率为 $b_2$ 的射线。
  - 则当 $i=3$ 时 $f$ 已在 **全局范围** 内构成了一个 **下凸壳**。
- 当 $i>3$ 时且我们已经说明 $f_{i-1,*}$ 是下凸的：
  - 找到 $f_{i-1,*}$ 中 **最小值的（第一个）取值点** $p$，则考察 $f_{i-1,*}$ 的差分序列 $\mathrm{d}f_{i-1,j}=f_{i-1,j}-f_{i-1,j-1}$ 有：
    - 对于任意 $1\le k\le p$ 有 $\mathrm{d}f_{i-1,k}<0$。
    - 对于任意 $k> p$ 有 $\mathrm{d}f_{i-1,k}\ge 0$。
  - 若 $p\ge a_{i-1}$，则此时 **全局斜率变为零**，随后 **全局斜率增加 $b_{i-1}$**。
    - 则此时退化为一条射线，显然仍然为凸的。 
  - 若 $p<a_{i-1}$，则此时我们 **截取出凸壳在 $[p,a_{i-1}]$ 的部分**，将其 **翻转**（对应到差分序列上为 **左开右闭区间翻转再取反**），然后 **放置在最前面**，其余部分斜率推平成 $0$，随后 **全局斜率增加 $b_{i-1}$**。
    - 全局增加斜率并不影响凸性；考察做此操作之前的凸性：由于对于任意 $k> p$ 有 $\mathrm{d}f_{i-1,k}\ge 0$ 且递增，则 **翻转并取反** 后仍然递增且不大于 $0$，再接上剩余为 $0$ 的部分仍然符合条件。

对于 $i\le 3$ 的我们可以直接 $\mathcal{O}(V)$ 暴力做；对于 $i>3$ 的部分，根据上面的证明发现我们要支持：
1. 区间翻转。
2. 区间位移（即把三个区间 $x,y,z$ 的顺序变为 $y,x,z$）。
3. 区间取反（即把区间中所有值为 $x$ 的数变为 $-x$）。
4. 区间推平为 $0$。
5. 全局加。

使用 **FHQ-Treap** 容易维护。具体实现上：
- 注意到 $1,3$ 操作其实操作的区间一致，所以只需要打一个 tag。所以最终需要三个 tag。
- 然后还需要额外 **手动维护 $f_{i,0}$ 的值**。

视实现最终复杂度是 $\mathcal{O}(n\log{V}+V)$ 或者 $\mathcal{O}(V\log{V})$。

可以参考代码，5.4kb，倒也不算长。


### Code

```cpp
#include<bits/stdc++.h>
#define int long long
// #pragma GCC optimize(3,"Ofast","inline")
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ll long long
#define bint __int128
#define ull unsigned long long
#define uint unsigned int
#define ld double
#define PII pair<int,int>
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
#define pcnt(x) __builtin_popcount(x)
#define lg(x) (31-__builtin_clz(x))
using namespace std;
void file_IO() {
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
}
bool M1;
const int INF=0x3f3f3f3f;
const ll INFLL=0x3f3f3f3f3f3f3f3f;
const ld eps=1e-9;
mt19937 rd(time(0));
struct FHQ_Treap {
    static const int N=1e6+5;
    struct node {
        int lson,rson,siz,val,sum,x,tag1,tag2,tag3;
        node() {
            lson=rson=siz=val=sum=tag1=tag2=tag3=0;
        }
        node(int a,int b,int c,int d,int e,int f,int g,int h,int i) {
            lson=a; rson=b;
            siz=c;
            val=d; sum=e;
            x=f;
            tag1=g; tag2=h; tag3=i;
        }
    }; node tree[N];
    #define ls(k) tree[k].lson
    #define rs(k) tree[k].rson
    void push_up(int k) {
        tree[k].siz=tree[ls(k)].siz+tree[rs(k)].siz+1;
        tree[k].sum=tree[ls(k)].sum+tree[rs(k)].sum+tree[k].val;
    }
    int p;
    int new_node(int val) {
        tree[++p]=node(0,0,1,val,val,(int)rd(),0,0,0);
        return p;
    }
    void upd(int k,int t1,int t2,int t3) {
        if(!k)
            return;
        if(t3) {
            tree[k].val=tree[k].sum=0;
            tree[k].tag1=tree[k].tag2=0;
            tree[k].tag3=1;
        }
        if(t1) {
            swap(ls(k),rs(k));
            tree[k].tag1^=1;
            tree[k].val=-tree[k].val;
            tree[k].sum=-tree[k].sum;         
            tree[k].tag2=-tree[k].tag2;   
        }
        tree[k].val+=t2;
        tree[k].sum+=t2*tree[k].siz;
        tree[k].tag2+=t2;
    }
    void push_down(int k) {
        int &t1=tree[k].tag1,&t2=tree[k].tag2,&t3=tree[k].tag3;
        if(t1||t2||t3) {
            upd(ls(k),t1,t2,t3);
            upd(rs(k),t1,t2,t3);
            t1=t2=t3=0;  
        }
    }
    int merge(int u,int v) {
        if(!u||!v)
            return u|v;
        if(tree[u].x<tree[v].x) {
            push_down(u);
            rs(u)=merge(rs(u),v);
            push_up(u);
            return u;
        } else {
            push_down(v);
            ls(v)=merge(u,ls(v));
            push_up(v);
            return v;
        }
    }
    void split(int k,int val,int &u,int &v) {
        if(!k) {
            u=v=0;
            return;
        }
        push_down(k);
        if(tree[k].val<val)
            u=k,split(rs(k),val,rs(k),v);
        else
            v=k,split(ls(k),val,u,ls(k));
        push_up(k);
    }
    void split_siz(int k,int val,int &u,int &v) {
        if(!k) {
            u=v=0;
            return;
        }
        push_down(k);
        if(tree[ls(k)].siz<val)
            u=k,split_siz(rs(k),val-tree[ls(u)].siz-1,rs(k),v);
        else
            v=k,split_siz(ls(k),val,u,ls(k));
        push_up(k);
    }
}; FHQ_Treap T;
const int N=5e5+5,M=1e6+5,m=1e6;
int a[N],b[N],f[2][M],suf[M];
int query(int &rt,int p) {
    int u=0,v=0;
    T.split(rt,0,u,v);
    int mnpos=T.tree[u].siz;
    if(mnpos>=p) {
        int val=T.tree[u].sum;
        rt=T.merge(u,v);
        return val;
    } else {
        rt=T.merge(u,v);
        u=v=0;
        T.split_siz(rt,p,u,v);
        int val=T.tree[u].sum;
        rt=T.merge(u,v);
        return val;
    }
}
void solve() {
    int n;
    scanf("%lld",&n);
    rep(i,1,n)
        scanf("%lld",&a[i]);
    rep(i,1,n-1)
        scanf("%lld",&b[i]);
    cl(f,0x3f);
    int p=1;
    f[1][0]=0;
    rep(i,2,3) {
        p^=1;
        rep(j,0,m)
            f[p][j]=INFLL;
        suf[m+1]=INFLL;
        per(j,m,0)
            suf[j]=min(suf[j+1],f[p^1][j]);
        rep(k,0,m) {
            f[p][k]=INFLL;
            chkmin(f[p][k],suf[max(a[i-1]-k,0ll)]+b[i-1]*k);
        }
        int mn=INFLL;
        rep(j,a[i],m)
            chkmin(mn,f[p][j]);
        printf("%lld\n",mn);
    }
    int x=f[p][0],rt=0;
    rep(i,1,m)
        rt=T.merge(rt,T.new_node(f[p][i]-f[p][i-1]));
    rep(i,4,n) {
        int u=0,v=0;
        T.split(rt,0,u,v);
        int mnpos=T.tree[u].siz;
        if(mnpos<a[i-1]) {
            rt=T.merge(u,v);
            x+=query(rt,a[i-1]);
            int w=0;
            u=v=0;
            T.split_siz(rt,mnpos,u,v);
            int t=v; v=0;
            T.split_siz(t,a[i-1]-mnpos,v,w);
            T.upd(v,1,0,0);
            T.upd(u,0,0,1);
            T.upd(w,0,0,1);
            rt=T.merge(v,T.merge(u,w));
        } else {
            x+=T.tree[u].sum;
            rt=T.merge(u,v);
            T.upd(rt,0,0,1);
        }
        T.upd(rt,0,b[i-1],0);
        printf("%lld\n",x+query(rt,a[i]));
    }
}
bool M2;
// g++ C.cpp -std=c++14 -Wall -O2 -o C
signed main() {
    // file_IO();
    int testcase=1;
    // scanf("%d",&testcase);
    while(testcase--)
        solve();
    debug("used time = %dms\n",(signed)(1000*clock()/CLOCKS_PER_SEC));
    debug("used memory = %dMB\n",(signed)((&M1-&M2)/1024/1024));
    return 0;
}
```

---

## 作者：Purslane (赞：5)

# Solution

赛时写了 $O(n)$ 做法，但是没调出来。。。

考虑 DP。设 $dp_{i,j}$ 为，考虑了 $1$ 到 $i-1$ 之间的**管道**，使得 $i$ 号植物还需要 $j$ 单位水。显然我们需要求 $dp_{i,0}$。

暴力转移是简单的，显然有

$$
dp_{i,j} = \min_{k\le w_i-j} c_{i-1}(w_i-j) + dp_{i-1,k}
$$

特别地，可以通过 $dp_{i,j} \leftarrow \min\{dp_{i,j},dp_{i,j-1}\}$ 来转移，所以可以直接改写为：

$$
dp_{i,j} = c_{i-1} (w_i-j) + dp_{i-1,w_i-j}
$$

对于 $j > w_i$ 的部分，直接由 $dp_{i,j}$ 得到。

从 $i$ 到 $i+1$，考虑发生了什么。

1. 加上一个一次函数，$dp_{i,j} \leftarrow dp_{i,j} + jc_i$；
2. 删除 $w_{i}+1$ 之后的部分（或者设为 $+\infty$），并且将剩余部分翻转；
3. 取前缀 $\min$。

发现 $dp$ 数组是凸的（没证），因此 $3$ 操作可以看做将末端斜率 $>0$ 的部分推平。

考虑维护差分数组。发现只有——整体加（操作 $1$）、区间翻转和区间取相反数（操作 $2$）、后缀推平（操作 $3$）。

很容易使用双端队列维护——维护一个增加量 $tag$，以及方向标记 $dir$ 记录序列的方向。如果序列是顺序的，最终值为 $x+tag$，否则为 $-x-tag$。

细节很多，复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4e6+10;
int n,w[MAXN],c[MAXN],a=1000000,hval,tval,dir,tag,hd=2000000,tl=hd-1;
struct SEG {int k,len;}s[MAXN];
signed main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    ffor(i,1,n) cin>>w[i];
    ffor(i,1,n-1) cin>>c[i];
    cout<<c[1]*max(w[1],w[2])<<'\n';
    if(w[1]>=w[2]) hval=tval=c[1]*w[1],s[++tl]={0,a};
    else hval=c[1]*w[2],tval=c[1]*w[1],s[++tl]={-c[1],w[2]-w[1]},s[++tl]={0,a-w[2]+w[1]};
    ffor(i,3,n) {
        tval=min(tval,hval);
        if(!dir) tval+=a*c[i-1],tag+=c[i-1];
        else tval+=a*c[i-1],tag-=c[i-1];
        if(!dir) {
            int ad=0,len=a,mn=0;
            while(len>w[i]) {
                if(len-s[tl].len>=w[i]) mn+=s[tl].len*(s[tl].k+tag),ad+=s[tl].len*(s[tl].k+tag),len-=s[tl].len,tl--;
                else s[tl].len-=len-w[i],mn+=(len-w[i])*(s[tl].k+tag),ad+=(len-w[i])*(s[tl].k+tag),len=w[i];
                if(mn>=0) mn=0;
            }
            while(hd<=tl&&s[tl].len==0) tl--;
            tval=tval-ad+mn;
			if(hd>tl) hval=tval,tag=0,s[++tl]={0,a};
            else s[tl].len--,++tl,s[tl]={s[tl-1].k+mn,1},dir=1,s[--hd]={-tag,a-w[i]},swap(hval,tval);
        }
        else {
            int ad=0,len=a,mn=0;
            while(len>w[i]) {
                if(len-s[hd].len>=w[i]) mn+=s[hd].len*(-s[hd].k-tag),ad+=s[hd].len*(-s[hd].k-tag),len-=s[hd].len,hd++;
                else s[hd].len-=len-w[i],mn+=(len-w[i])*(-s[hd].k-tag),ad+=(len-w[i])*(-s[hd].k-tag),len=w[i];
                if(mn>=0) mn=0;
            }
            while(hd<=tl&&s[hd].len==0) hd++;
			tval=tval-ad+mn;
            if(hd>tl) hval=tval,tag=0,s[++tl]={0,a};
            else s[hd].len--,--hd,s[hd]={s[hd+1].k-mn,1},dir=0,s[++tl]={-tag,a-w[i]},swap(hval,tval);
        }
       	cout<<hval<<'\n';
        if(!dir) {
            int del=0;
            while(hd<=tl)
				if(s[tl].k+tag>=0) tval-=(s[tl].k+tag)*s[tl].len,del+=s[tl].len,tl--;
                else break ;
            if(del) s[++tl]={-tag,del};
        }
        else {
            int del=0;
            while(hd<=tl)
                if(-s[hd].k-tag>=0) tval-=(-s[hd].k-tag)*s[hd].len,del+=s[hd].len,hd++;
                else break ;
            if(del) s[--hd]={-tag,del};
        }
    }
    return 0;
}
```

---

## 作者：AC_Lover (赞：3)

[P11678 [USACO25JAN] Watering the Plants P](https://www.luogu.com.cn/problem/P11678)

此处定义 $c_i$ 表示第 $i$ 株植物需要的水量，$w_i$ 表示连接 $i,i+1$ 的水渠的单位代价。

一个显然的 $\mathrm{DP}$：

定义 $f_{i,j}$ 表示前 $i$ 株植物已经搞定并且给第 $i+1$ 株植物额外贡献了 $j$ 的水量时的最小代价，转移是简单的，枚举第 $i-1$ 个水渠用了 $k$ 的水，于是
$$
f_{i,j}=\min_{k+j\ge c_i}\set{f_{i-1,k}+j\times w_i} \\
=\min_{k\ge \max(0,c_i-j)}\set{f_{i-1,k}}+j\times w_i
$$
使用后缀 $\min$ 优化一下：
$$
g_{i,j}=\min_{k\ge j}\set{f_{i,k}} \\
f_{i,j}=g_{i-1,\max(0,c_i-j)}+j\times w_i
$$
显然对于 $i$ 答案就是 $g_{i-1,c_i}$。

然后就有 $O(nV)$ 的暴力，可以获得 $\texttt{30pts}$。

开始分析性质，我们将 $j$ 分类：

- $j\le c_i$

  此时原式子：$f_{i,j}=g_{i-1,c_i-j}+j\times w_i$

- $j>c_i$

  此时原式子：$f_{i,j}=g_{i-1,0}+j\times w_i$

可以发现 $f_i$ 是凸的，这是一个很好的性质，这表明我们可以考虑**Slope Trick**。

还是分开来看：

- $j\le c_i$

  此时 $f$ 相当于把原来的前 $c_i$ 个翻转一下，然后再加上一个斜率为 $w_i$ 的一次函数

- $j>c_i$

  此时 $f$ 相当于全部推平后后加上一个斜率为 $w_i$ 的一次函数

做完之后，全部推成后缀 $\min$，后缀 $\min$ 一定是一个平台加上一个单调上升。

可以结合图像看一下：

![convex-hull.png](https://s2.loli.net/2025/04/17/BqeghVidn1wSzIb.png)

我们考虑维护点到点斜率，那么假设我们可以知道 $g_{i-1,0}$，那么从前往后加上斜率加到 $c_i$ 就可以推出 $g_{i-1,c_i}$。

观察转移式，可以发现 $f_{i,0}=g_{i-1,c_i}$，这样在 $f$ 计算后取后缀 $\min$ 推平时，将前面斜率小于 $0$ 的贡献上就可以计算出 $g_{i,0}$，如此往复，可以不断推得答案。

维护斜率可以用平衡树，操作有【区间翻转】、【区间取反（翻转后斜率都取反）】、【覆盖成 $0$】、【加上 $w_i$】的操作，可以变成【区间翻转】、【区间乘】、【区间加】，用平衡树维护，并且要在平衡树上二分找到拐点推平，然后要计算前缀和，所以再维护一个前缀和。

然后就可以了，时间复杂度 $O(n\log V)$。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

typedef long long ll;
const int N=500010,M=1000010;
const ll INF=1e18;
int n;
int c[N],w[N];
int mx;

void Min(ll &x,ll y) { x=min(x,y); }

namespace FHQ
{
	mt19937 rnd(time(0));

	ll val[M],sum[M],add[M];
	int pri[M],ch[M][2],sz[M],rev[M],mul[M],idx,root;
	
	inline int new_node(int v)
	{
		int u=++idx;
		val[u]=sum[u]=v;
		pri[u]=rnd();
		sz[u]=1;
		mul[u]=1;
		return u;
	}
	
	inline void pushup(int u) 
	{
		sz[u]=sz[ch[u][0]]+sz[ch[u][1]]+1;
		sum[u]=sum[ch[u][0]]+sum[ch[u][1]]+val[u];
	}
	
	inline void Rev(int u)
	{
		if (!u) return;
		rev[u]^=1;
		swap(ch[u][0],ch[u][1]);
	}
	
	inline void Mul(int u,int x)
	{
		if (!u) return;
		mul[u]*=x;
		add[u]*=x;
		
		val[u]*=x;
		sum[u]*=x;
	}
	
	inline void Add(int u,int d)
	{
		if (!u) return;
		add[u]+=d;
		
		val[u]+=d;
		sum[u]+=(ll)d*sz[u];
	}
	
	inline void pushdown(int u)
	{
		if (rev[u])
		{
			Rev(ch[u][0]);
			Rev(ch[u][1]);
			rev[u]=0;
		}
		if (mul[u]!=1)
		{
			Mul(ch[u][0],mul[u]);
			Mul(ch[u][1],mul[u]);
			mul[u]=1;
		}
		if (add[u])
		{
			Add(ch[u][0],add[u]);
			Add(ch[u][1],add[u]);
			add[u]=0;
		}
	}
	
	void split(int rt,int k,int &rt1,int &rt2)
	{
		if (!rt) 
		{
			rt1=rt2=0;
			return;
		}
		pushdown(rt);
		if (sz[ch[rt][0]]+1<=k) 
		{
			rt1=rt;
			split(ch[rt][1],k-sz[ch[rt][0]]-1,ch[rt][1],rt2);
		}
		else
		{
			rt2=rt;
			split(ch[rt][0],k,rt1,ch[rt][0]);
		}
		pushup(rt);
	}
	
	int merge(int rt1,int rt2)
	{
		if (!rt1 || !rt2) return rt1^rt2;
		if (pri[rt1]<pri[rt2])
		{
			pushdown(rt1);
			ch[rt1][1]=merge(ch[rt1][1],rt2);
			pushup(rt1);
			return rt1;
		}
		else
		{
			pushdown(rt2);
			ch[rt2][0]=merge(rt1,ch[rt2][0]);
			pushup(rt2);
			return rt2;
		}
	}
	
	inline void Insert(int v) { root=merge(root,new_node(v)); }
	
	ll qrys(int u,int k)
	{
		if (!u) return 0;
		pushdown(u);
		if (sz[ch[u][0]]+1<=k) return sum[ch[u][0]]+val[u]+qrys(ch[u][1],k-sz[ch[u][0]]-1);
		else return qrys(ch[u][0],k);
	}
	
	ll mdf(int u)
	{
		if (!u) return 0;
		pushdown(u);
		if (val[u]<0) 
		{
			ll res=sum[ch[u][0]]+val[u]+mdf(ch[u][1]);
			Mul(ch[u][0],0),val[u]=0;
			pushup(u);
			return res;
		}
		else 
		{
			ll res=mdf(ch[u][0]);
			pushup(u);
			return res;
		}
	}
	
	void adj(int rt=root)
	{
		pushdown(rt);
		if (ch[rt][0]) adj(ch[rt][0]);
		if (ch[rt][1]) adj(ch[rt][1]);
		pushup(rt);
	}
	
	void print(int rt=root)
	{
		if (ch[rt][0]) print(ch[rt][0]);
		cout << val[rt] << " ";
		if (ch[rt][1]) print(ch[rt][1]);
	}
	
	void prt(int rt=root) { adj(rt);print(rt);cout << "\n---\n"; }
}
using namespace FHQ;

ll f0;
ll st;

inline ll calc(int k)
{
	ll res=st+f0+qrys(root,k);
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin >> n;
	for (int i=1;i<=n;i++) 
	{
		cin >> c[i];
		mx=max(mx,c[i]);
	}
	for (int i=1;i<n;i++) cin >> w[i];
	
	for (int i=1;i<=c[1];i++) Insert(0);
	for (int i=c[1]+1;i<=mx;i++) Insert(w[1]);
	f0=(ll)c[1]*w[1];
	
	for (int i=2;i<=n;i++)
	{
		st=mdf(root);
		
		f0=calc(c[i]);
		cout << f0 << "\n";
		
		int x,y;
		split(root,c[i],x,y);
		Rev(x);Mul(x,-1);Mul(y,0);
		root=merge(x,y);
		Add(root,w[i]);
	}
	
	return 0;
}
```

---

## 作者：lovely_nst (赞：2)

# P11678 Watering the Plants P

## 前言

这道题我做了四天，是一道很有难度的题。~~标记打错+少判情况~~

## 题意

有 $n$ 个水池，每次可以花费 $w_i$ 的代价让第 $i$ 和第 $i + 1$ 个水池的水量加 $1$。求最小代价使第 $i$ 个水池中至少有 $a_i$ 的水量。

## 思路

因为 $i$ 只能花 $w_{i-1}$ 或 $w_i$ 的贡献加水量，所以 $w_{i-1}$ 和 $w_i$ 的使用次数和不能小于 $a_i$。

设 $f_{i,j}$ 为前 $i-1$ 个水池已经锁定且满足条件，第 $i$ 个水池目前有 $j$ 水量的最小代价。可得转移方程：

$$
f_{i,j}=\min_{k\ge a_{i-1}-j}f_{i-1,k} + j \times w_{i-1}
$$

现在如何从 $f_{i-1}(x)$ 快速转移到 $f_i(x)$ 就是要解决的问题了。

考虑 slope trick。

- 可以发现，若 $f_{i-1}(x)$ 是下凸的，$f_i(x)$ 也是下凸的。

-  证明：观察转移方程可以发现其实就是求了个后缀 $\min$，然后再加上一个一次函数。也就是把 $f_{i-1}(x)$ 每一对相邻点的斜率加上 $w_{i-1}$，因此还是下凸。

由于边界原因，$i < 3$ 时，$f_i(x)$ 不满足下凸性质（具体的可以看楼顶的题解）。那么就可以先预处理出 $f_{i,j}(i<3)$，然后再继续做。

接下来，设 $L$ 为 $f_{i-1}(x)$ 的最小值的位置，然后分两种情况讨论：

- $L\le a_{i-1}$ 时，因为 $L$ 之后的斜率单调不下降，因此 $f_i(j)=f_{i-1}(a_{i-1}-j)+j\times w_{i-1}(j\le a_{i-1}-L)$；当 $j>a_{i-1}-L$ 时，$f_i(j)=f_{i-1}(L)+j\times w_{i-1}$。

- $L> a_{i-1}$ 时，因为 $L$ 之前的斜率单调下降，因此 $f_{i-1}(L)$ 为后缀的最小值，得 $f_i(j)=f_{i-1}(L)+j\times w_{i-1}$。

第一种情况可以看成把 $f_{i-1}(x)$ 中的 $[L,a_{i-1}]$ 这一段提取出来翻转后拼到 $f_i(x)$ 的前缀上，后面的推平成斜率为零 $0$ 的直线。最后全局斜率加上 $w_{i-1}$。

第二种情况可以看成全局重置为一条斜率为 $w_{i-1}$ 的直线，即全局推平然后全局斜率加上 $w_{i-1}$。

那如何维护斜率呢？考虑使用**平衡树（FHQ Treap）**。

维护三个操作：

1. 区间翻转并区间取反（因为反转后斜率 $k$ 会变成 $-k$）。

2. 区间推平为 $0$。

3. 全局加 $w$。

操作 $1$ 可以参考**文艺平衡树**，在平衡树树上打标记，操作时下传标记。这个标记记为 $tag1$，表示翻转并取反该子树。

操作 $2$，标记 $tag2$ 表示子树内的值全部清零。注意若打上了该标记，其他的 $tag$，该位的值以及子树和都要清 $0$。

操作 $3$ 只需在根节点打上加的标记 $tag3$，之后是一样的。

注意先下传顺序是操作 $2$，操作 $3$，操作 $1$。原因是 $tag2$ 标记时会把其他清零，若先下传另外两个会出问题；操作 $3$ 是最后做的，只有下一次的下传可以影响，因此要在最后下传。

具体见代码。

## AC Code
[记录](https://www.luogu.com.cn/record/214419446)

[代码](https://www.luogu.com.cn/paste/2t0mlv4o)

---

## 作者：rlc202204 (赞：1)

# [P11678 [USACO25JAN] Watering the Plants P](https://www.luogu.com.cn/problem/P11678)

**题意：**

有 $n$ 个植物和 $n-1$ 个水管，第 $i$ 个水管可以给 $i,i+1$ 两个植物一起提供任意单位的水，每单位水的花费是 $c_i$。第 $i$ 个植物至少需要 $w_i$ 单位的水。

对于每个 $1 \le i < n$ 求只考虑前 $i$ 个水管，满足前 $i+1$ 个植物的最小花费。

$n \le 5 \times 10^5,c_i,w_i \le 10^6$。

**思路：**

注意到这个问题很想网络流，但是至少 $w_i$ 单位的水不太好做，考虑对偶一下：

原来的限制为：

$$
1 \le i < n,x_i + x_{i+1} \ge w_i\\
\text{minimize} \sum_{i=1}^{n-1}c_ix_i
$$

对偶之后变成：

$$
1 \le i < n, y_i + y_{i+1} \le c_i\\
\text{maximize}\sum_{i=1}^n w_iy_i
$$

这样我们就可以考虑费用流模型，和种树那题很想，大致如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/v2be87ck.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但是显然数据范围不支持我们真的去跑费用流。所以我们只能贪心或者 dp 凸优化。这里我们考虑 dp 凸优化。

设 $f_i(j)$ 表示前 $i$ 个，满足 $y_i = j$ 的最大的 $\sum w_iy_i$。我们发现随着 $j$ 的增大 $f_i(j)$ 是凸函数。

这相当于不断给最后一条边加 $1$ 的流量，由于是费用流，所以增广路不会增大，所以是凸的。

转移如下：

$$
f_i(j) = j \times w_i + \max_{k \le c_i - j}f_{i-1}(k)
$$

假设我们维护了 $f_{i-1}$ 的凸函数，那么这相当于以下三件事：

- 将凸函数范围改成 $[0,c_i]$。

- 反转凸函数。

- 整体取前缀 $\max$。

- 加上直线 $y=w_ix$。

我们可以用 FHQ_Treap 来维护，一个节点储存差分相等的区间的长度，同时还要储存差分是多少，以及差分乘上区间长度的值。

我们要支持全局加法，全局反转，打两个 tag 就行。

当然这里其实可以用官方解法那样用双端队列就行，考场上没想那么多。时间复杂度 $O(n \log n)$，可以通过。


```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <ctime>
#include <random>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
const int A = 1e6 + 5;
typedef long long ll;
#define debug(x) cout << #x << "=" << x << endl 

int n;
int w[N] = {0}, c[N] = {0};

struct LazyTag {
	int rev;
	ll add;//翻转后加上 add
	LazyTag (int _rev = 0, ll _add = 0ll) :
		rev(_rev), add(_add) {}
};
LazyTag operator+(LazyTag x, LazyTag y) {
	return LazyTag((x.rev ^ y.rev), y.add + (y.rev ? -x.add : x.add));
}
struct Node {
	int ch[2], pri, sz;
	ll d, p;
	ll sd, sp, sum;//d之和, p 之和, p * d之和 
	LazyTag tag;  
	Node () {
		ch[0] = ch[1] = sz = 0, pri = -1;
		d = p = sd = sp = sum = 0ll;
		tag = LazyTag();
	}
	Node (ll _d, ll _p) {
		sd = d = _d, sp = p = _p, sum = p * d;
		ch[0] = ch[1] = 0, sz = 1, pri = rand();
		tag = LazyTag();
	}
} a[N];

#define ls(x) a[x].ch[0]
#define rs(x) a[x].ch[1]

void upd(Node &x, Node &y, Node &z) {
	x.sd = y.sd + z.sd + x.d;
	x.sp = y.sp + z.sp + x.p;
	x.sum = y.sum + z.sum + x.d * x.p;
	x.sz = y.sz + z.sz + 1;
}
void pushup(int x) {
	upd(a[x], a[ls(x)], a[rs(x)]);
}
void mdf(Node &x, LazyTag v) {
	if (v.rev) {
		x.d = -x.d;
		x.sd = -x.sd;
		x.sum = -x.sum;
		swap(x.ch[0], x.ch[1]);
	}
	x.d += v.add;
	x.sd += v.add * x.sz;
	x.sum += v.add * x.sp;
	x.tag = x.tag + v;
}
void pushtag(int x, LazyTag v) {
	mdf(a[x], v);
}
void pushdown(int x) {
	pushtag(ls(x), a[x].tag);
	pushtag(rs(x), a[x].tag);
	a[x].tag = LazyTag();
}
void spt_sp(int x, ll v, int &L, int &R) {
	if (x == 0) {
		L = R = 0;
		return;
	}
	pushdown(x);
	if (a[ls(x)].sp + a[x].p <= v)
		L = x, spt_sp(rs(x), v - a[ls(x)].sp - a[x].p, rs(x), R);
	else
		R = x, spt_sp(ls(x), v, L, ls(x));
	pushup(x);
}
void spt_d(int x, ll v, int &L, int &R) {
	if (x == 0) {
		L = R = 0;
		return;
	}
	pushdown(x);
	if (a[x].d > v)
		L = x, spt_d(rs(x), v, rs(x), R);
	else
		R = x, spt_d(ls(x), v, L, ls(x));
	pushup(x); 
}
void spt_sz(int x, int k, int &L, int &R) {
	if (x == 0) {
		L = R = 0;
		return;
	}
	pushdown(x);
	if (a[ls(x)].sz + 1 <= k)
		L = x, spt_sz(rs(x), k - a[ls(x)].sz - 1, rs(x), R);
	else	
		R = x, spt_sz(ls(x), k, L, ls(x));
	pushup(x); 
}
int mrg(int L, int R) {
	if (L == 0 || R == 0)	
		return L + R;
	if (a[L].pri > a[R].pri) {
		pushdown(L);
		rs(L) = mrg(rs(L), R);
		pushup(L);
		return L; 
	}
	else {
		pushdown(R);
		ls(R) = mrg(L, ls(R));
		pushup(R);
		return R;
	}
}

int rt;//当前的根
ll res;//初始截距
int tot = 0;//节点个数 

void show(int x) {
	if (x == 0)
		return;
	pushdown(x);
	show(ls(x));
	printf("(%lld, %lld) ", a[x].p, a[x].d);
	show(rs(x));
}

void upd_lim(ll k) {//只保留 <= k 的部分 
	int L, M, R;
	spt_sp(rt, k, L, R);
//	debug(k);
//	show(L);cout << endl; show(R);cout << endl;
	if (!R) {//表示当前不够了 
//	cout << a[L].sp << endl;
		a[++tot] = Node(0ll, k - a[L].sp);
		rt = mrg(L, tot);
//		show(rt);cout << endl;
		return;
	}
	spt_sz(R, 1, M, R);
	a[M] = Node(a[M].d, k - a[L].sp);
	rt = mrg(L, M);
} 
void upd_rev(ll v) {//整体翻转然后所有数加上 v 
	res += a[rt].sum;//截距变化 
//	show(rt);cout << endl;
//	debug(rt);
	pushtag(rt, LazyTag(1, v));
//	debug(v);
//	show(rt);cout << endl;
}
void upd_min() {//取前缀 max，只保留 d > 0 的所有部分
	int L, R;
//	show(rt);cout << endl;
	spt_d(rt, 0ll, L, R);
	rt = L; 
}


#undef ls
#undef rs 

int main() {
//	freopen("a.in", "r", stdin);
//	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1; i < n; i++)
		scanf("%d", &c[i]);
	res = 0ll;
	rt = ++tot;
	a[rt] = Node(w[1], 1000000ll);
	for (int i = 2; i <= n; i++) {
//		if (i == 9)
//			cout << "\n\n\n\n";
		upd_lim(c[i - 1]);
		upd_rev(w[i]);
		upd_min();
	//	show(rt);
	//	printf("res: %lld\n", res);
		printf("%lld\n", res + a[rt].sum);
	//	cout << "nxt \n\n" << endl;
	//	if (i == 9)
	//		break;
	}
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：1)

可以看出一个很显然的 DP，设 $f_{i,j}$ 表示 $1,\ldots,i$ 的水渠，浇灌 $1,\ldots,i$ 的植物需要的代价。那么 $f_{i,j}=\min_{k=a_i-j}^{V}f_{i-1,j}+c_ij$。

我们动态地维护 $f_{i,*}$。

把每一次转移拆成五类操作：

- 把 $f$ 以 $\frac{a_i}2$ 为轴对称。
- 加上一次函数 $c_ij$。
- 把每个位置变成前缀最小值。
- 修改定义域为 $[0,a_{i+1}]$（也即扔掉多余的点值，注意在进行第二次操作前要对定义域扩充）。
- 查询 $f_{a_{i+1}}$。

只要维护一个数据结构支持这五种操作就可以。

区间翻转可以用 treap 维护，但是注意到翻转是全局的，所以有更加简单的线性做法。

注意到 $f$ 始终是凸的（可以通过归纳得到）。

拿一个 deque $Q$，维护 $f$ 的连续的折线段（记录 $l,r$，以及 $k,b$）。

- 对于第一类操作，可以打上翻转标记。
- 对于第二类操作，可以打上斜率加标记。
- 对于第三类操作，相当于删掉前面的斜率小于 $0$ 的段，并替换为一个水平的段。复杂度可以均摊。
- 对于第四类操作，删掉后面多余的部分即可，复杂度同样可以摊。
- 对于第五类操作查询队尾就可以。

实际上队首和队尾是相对的，对于翻转后的序列，要把队首看作队尾，把队尾看作队首。所以需要更多的讨论（也可封装）。~~（不过也就是码量 $\times 2$ 罢了）~~ 

时间复杂度是优秀的 $O(n)$，值域无关。

具体思想就是这样，写起来还有一坨。我的实现非常劣，是场上写了 2h 用了总共 $4$ 个标记 $7$ 个函数的石山代码（貌似其实可以只维护斜率 $\Delta$ 而非具体斜率，会大大简化操作），仅供参考。

```cpp
#include<bits/stdc++.h>
bool Mbg;
using namespace std;
#define vec vector
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define eb emplace_back
#define siz(vec) ((int)(vec).size())
#define all(vec) (vec).begin(),(vec).end()
template<class T>
void operator +=(vec<T> &a,T b){a.push_back(b);}
template<class T>
void operator --(vec<T> &a){a.pop_back();}
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
#define exc(exp) if(exp)continue;
#define stop(exp) if(exp)break;
#define ret(exp) if(exp)return;
#define deb(var) cerr<<#var<<'='<<(var)<<"; "
#define debl(var) cerr<<#var<<'='<<(var)<<";\n"
#define ins insert
#define era erase
#define lb lower_bound
#define ub upper_bound
#define int long long
#define inf (long long)(1e18)
template<class T>
bool Min(T &x,T y){return x>y?x=y,1:0;}
template<class T>
bool Max(T &x,T y){return x<y?x=y,1:0;}
const int mod=998244353;
void Add(int &x,int y){x=x+y<mod?x+y:x+y-mod;}
void Dec(int &x,int y){x=x>=y?x-y:x-y+mod;}
int fpm(int x,int y){
    int ans=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)ans=1ll*x*ans%mod;return ans;
}


const int W=2e6;

int n,a[500010],c[500010];

int tagk=1,tagb,addk,addb;

// x -> tagkx+tagb
struct segm{
    int l,r,k,b;
    // k -> k+addk
    int f(int x){
        return (k+addk)*((x-tagb)/tagk)+b+addb;
    }
};
deque<segm> Q;


int L(segm x){
    return tagk==1?x.l+tagb:-x.r+tagb;
}
int R(segm x){
    return tagk==1?x.r+tagb:-x.l+tagb;
}

void setR(segm &x,int r){
    if(tagk==1){
        x.r=r-tagb;
    }else{
        x.l=-r+tagb;
    }
    assert(R(x)==r);
}
void setL(segm &x,int l){
    if(tagk==1){
        x.l=l-tagb;
    }else{
        x.r=-l+tagb;
    }
    assert(L(x)==l);
}

void REDUCE(int r){
    if(tagk==1){
        while(L(Q.back())>r){
            Q.pop_back();
        }
        if(R(Q.back())>r){
            auto x=Q.back();
            Q.pop_back();
            setR(x,r);
            Q.push_back(x);
        }
    }else{
        while(L(Q.front())>r){
            Q.pop_front();
        }
        if(R(Q.front())>r){
            auto x=Q.front();
            Q.pop_front();
            setR(x,r);
            Q.push_front(x);
        }
    }
}

void DELETE(){
    if(tagk==1){
        int v=2*inf,x=-1;
        while(!Q.empty()&&Q.front().k+addk<=0&&Q.front().f(x+1)<=v){
            v=Q.front().f(x=R(Q.front()));
            Q.pop_front();
        }
        if(!Q.empty()){
            Min(v,Q.front().f(x+1));
        }
        if(x!=-1){
            segm s;
            s.k=-addk;
            s.b=v-addb;
            setL(s,0);
            setR(s,x);

            Q.push_front(s);
        }

    }else{
        int v=2*inf,x=-1;
        while(!Q.empty()&&Q.back().k+addk>=0&&Q.back().f(L(Q.back()))<=v){
            v=Q.back().f(x=R(Q.back()));
            Q.pop_back();
        }
        if(!Q.empty()){
            Min(v,Q.back().f(x+1));
        }
        if(x!=-1){
            segm s;
            s.k=-addk;
            s.b=v-addb;
            setL(s,0);
            setR(s,x);

            Q.push_back(s);
        }
    }
}

int QUERY(int x){
    return tagk==1?Q.back().f(x):Q.front().f(x);
}


void work(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<n;i++)cin>>c[i];


    Q.push_back({0,0,0,0});
    Q.push_back({1,a[1],W+5,0});

    for(int i=1;i<n;i++){
        // x -> (a[i]-x)
        tagk*=-1;
        tagb=-tagb+a[i];

        if(tagk==1){
            segm x;
            x.k=-addk;
            x.b=Q.back().f(a[i])-addb;
            setL(x,a[i]+1);
            setR(x,W);
            Q.push_back(x);
        }else{
            segm x;
            x.k=-addk;
            x.b=Q.front().f(a[i])-addb;
            setL(x,a[i]+1);
            setR(x,W);
            Q.push_front(x);
        }

        addk+=c[i]*tagk;
        addb+=c[i]*tagb;

        DELETE();

        REDUCE(a[i+1]);
        
        cout<<QUERY(a[i+1])<<'\n';
    }
}
bool Med;
signed main(){
    ios::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int T=1;while(T--)work();
    // cerr<<"Time: "<<clock()<<" ms;\n";
    // cerr<<"Memory: "<<abs(&Med-&Mbg)/1024.0/1024.0<<" MiB.\n";
}
```

---

## 作者：Petit_Souris (赞：0)

好像有点难，主要是因为我写不明白代码。就当 NOI 前复习一下不常考的 slope trick 吧。

首先考虑暴力 dp。设 $dp_{i, j}$ 表示目前决策完 $[1, i  - 1]$ 的水渠，第 $i - 1$ 条水渠用了 $j$ 次，其中规定 $j \in [0, w_i]$，初始时有 $dp_{1, 0} = 0$。

考虑转移，相当于 $dp_{i, j} = \min \limits_{j + k \ge w_i} dp_{i - 1, k} + jc_{i - 1}$。直接看不明显，考虑 $dp_{i - 1, *} \to dp_{i, *}$ 发生的变化。

- 初始 $dp_{i} = dp_{i - 1}$；

- Step 1：$dp_{i, w_i}\leftarrow \min(dp_{i, w_i}, dp_{i, j}), dp_{i, j} \leftarrow +\infty (j > w_i)$；

- Step 2： 将 $dp_{i}[0, w_i]$ 翻转。此时 $dp_{i, 0}$ 即为前缀 $[1, i]$ 的答案；

- Step 3：对于 $dp_{i}$，取前缀 $\min$；

- Step 4：$dp_{i, j} \leftarrow dp_{i, j} + jc_{i - 1}$。

猜测 dp 数组有凸性。在第三轮之后容易用归纳法证明，而前两轮可能会出现问题，直接暴力模拟掉即可。

凸的 dp 可以考虑维护差分数组，这里差分数组一定是单调不降的。记 $V$ 为值域，我们维护 $[0, V]$ 的差分。那么我们对差分数组 $d$ 的修改就是：

- Step 1：对于 $d[w_i + 1, V]$，如果一个 $d_j < 0$，那么会在取 min 时产生贡献，也就是说 $d_{w_i} \leftarrow d_{w_i} + \sum\limits_{j > w_i} [d_j < 0] d_j$。这里 $j$ 是一段前缀。接着将 $d[w_i + 1, V]$ 清零。

- Step 2：翻转 $d[0, w_i]$ 并取相反数；

- Step 3：将 $d$ 中所有元素与 $0$ 取 $\min$。

- Step 4：对 $d$ 数组全局加 $c_{i - 1}$。

显然可以用平衡树解决。对于每个节点，维护子树大小、权值和，以及翻转、取相反数、覆盖为 $0$、加法标记。

- Step 1：分裂出有效的 $j$ 对应的子树，求和，再将 $[w_i + 1, V]$ 清零；

- Step 2：对前缀打翻转和取相反数的 tag；

- Step 3：此时除了 $d_1$ 以外，剩下的 $[2, w_i]$ 的元素是单调递增的。因此可以分别处理；

- Step 4：直接全局打加法 tag。

时间复杂度 $\mathcal O(n\log V)$，常数较大。

代码细节好多...

```cpp
#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using namespace std;
#pragma GCC target("avx512f")
template <class T>
using Ve = vector<T>;
#define ALL(v) (v).begin(), (v).end()
#define pii pair<ll, ll>
#define rep(i, a, b) for(ll i = (a); i <= (b); ++i)
#define per(i, a, b) for(ll i = (a); i >= (b); --i)
#define pb push_back
bool Mbe;
ll read() {
    ll x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
void write(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const ll N = 1e6 + 9, V = 1e6 + 1, INF = 1e18;
ll n, a[N], b[N], dp0, totn, rt, f[N];
mt19937 rnd(time(0));
struct Node {
    int ls, rs, sz;
    ll val, sum, rd, tag;
    bool rev, neg, cov;
} tr[N];
int New(ll v) {
    int x = ++totn;
    tr[x].val = v, tr[x].sum = v, tr[x].rd = rnd(), tr[x].sz = 1;
    return x;
}
void Pushup(int x) {
    tr[x].sum = tr[tr[x].ls].sum + tr[x].val + tr[tr[x].rs].sum;
    tr[x].sz = tr[tr[x].ls].sz + 1 + tr[tr[x].rs].sz;
}
void Pushtag(int x, ll k) {
    tr[x].val += k, tr[x].sum += k * tr[x].sz;
    tr[x].tag += k;
}
void Pushneg(int x) {
    tr[x].val = -tr[x].val, tr[x].sum = -tr[x].sum, tr[x].tag = -tr[x].tag;
    tr[x].neg ^= 1;
}
void Pushcov(int x) {
    tr[x].val = tr[x].sum = tr[x].tag = 0;
    tr[x].neg = 0, tr[x].cov = 1;
}
void Pushrev(int x) {
    swap(tr[x].ls, tr[x].rs);
    tr[x].rev ^= 1;
}
void Pushdown(int x) {
    if(tr[x].cov) {
        if(tr[x].ls) Pushcov(tr[x].ls);
        if(tr[x].rs) Pushcov(tr[x].rs);
        tr[x].cov = 0;
    }
    if(tr[x].rev) {
        if(tr[x].ls) Pushrev(tr[x].ls);
        if(tr[x].rs) Pushrev(tr[x].rs);
        tr[x].rev = 0;
    }
    if(tr[x].neg) {
        if(tr[x].ls) Pushneg(tr[x].ls);
        if(tr[x].rs) Pushneg(tr[x].rs);
        tr[x].neg = 0;
    }
    if(tr[x].tag) {
        if(tr[x].ls) Pushtag(tr[x].ls, tr[x].tag);
        if(tr[x].rs) Pushtag(tr[x].rs, tr[x].tag);
        tr[x].tag = 0;
    }
}
int Merge(int x, int y) {
    if(!x || !y) return x | y;
    Pushdown(x), Pushdown(y);
    if(tr[x].rd < tr[y].rd) {
        tr[x].rs = Merge(tr[x].rs, y);
        return Pushup(x), x;
    }
    tr[y].ls = Merge(x, tr[y].ls);
    return Pushup(y), y;
}
void Split(int x, int v, int &L, int &R) {
    if(!x) return L = R = 0, void();
    Pushdown(x);
    if(tr[tr[x].ls].sz < v) L = x, Split(tr[x].rs, v - tr[tr[x].ls].sz - 1, tr[x].rs, R);
    else R = x, Split(tr[x].ls, v, L, tr[x].ls);
    Pushup(x);
}
void Splitval(int x, ll v, int &L, int &R) {
    if(!x) return L = R = 0, void();
    Pushdown(x);
    if(tr[x].val <= v) L = x, Splitval(tr[x].rs, v, tr[x].rs, R);
    else R = x, Splitval(tr[x].ls, v, L, tr[x].ls);
    Pushup(x);
}
bool Med;
int main() {
    cerr << fabs(&Med - &Mbe) / 1048576.0 << "MB\n";
    n = read();
    rep(i, 1, n) a[i] = read();
    rep(i, 1, n - 1) b[i] = read();
    rep(i, 0, V) f[i] = INF;
    f[0] = 0;
    reverse(f, f + a[1] + 1);
    rep(i, 1, V) f[i] = min(f[i - 1], f[i]);
    rep(i, 0, V) f[i] += b[1] * i;
    rep(i, a[2] + 1, V) f[a[2]] = min(f[a[2]], f[i]), f[i] = INF;
    reverse(f, f + a[2] + 1);
    write(f[0]), putchar('\n');
    rep(i, 1, V) f[i] = min(f[i - 1], f[i]);
    rep(i, 0, V) f[i] += b[2] * i;
    rep(i, a[3] + 1, V) f[a[3]] = min(f[a[3]], f[i]), f[i] = INF;
    reverse(f, f + a[3] + 1);
    write(f[0]), putchar('\n');
    rep(i, 1, V) f[i] = min(f[i - 1], f[i]);
    rep(i, 0, V) f[i] += b[3] * i;
    rep(i, 1, V) rt = Merge(rt, New(f[i] - f[i - 1]));
    dp0 = f[0];
    rep(i, 4, n) {
        int L = 0, R = 0;
        Split(rt, a[i], L, R);
        int u1 = 0, u2 = 0;
        Splitval(R, 0, u1, u2);
        ll S = tr[u1].sum;
        if(a[i]) {
            int x = 0;
            Split(L, a[i] - 1, L, x);
            Pushtag(x, S);
            L = Merge(L, x);
        }
        else dp0 += S;
        R = Merge(u1, u2);
        Pushcov(R);
        if(L) {
            ll ndp0 = dp0 + tr[L].sum;
            Pushrev(L), Pushneg(L);
            dp0 = ndp0;
        }
        write(dp0), putchar('\n');
        int x = 0;
        Split(L, 1, x, L);
        if(tr[x].val > 0) Pushcov(x);
        u1 = u2 = 0;
        Splitval(L, 0, u1, u2);
        Pushcov(u2);
        L = Merge(x, Merge(u1, u2));
        rt = Merge(L, R);
        Pushtag(rt, b[i]);
    }
    cerr << "\n" << clock() * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n";
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P11678)

**题目大意**

> 给定 $n$ 个盒子，第 $i$ 个机器可以花 $w_i$ 的代价往第 $i,i+1$ 个盒子中各放一个球，要求第 $i$ 个盒子里有 $\ge a_i$ 个球，对于每个 $1<k\le n$，求出用 $1\sim k-1$ 号机器满足 $1\sim k$ 号盒子要求的最小代价。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

容易设计出一个朴素的 dp，即 $f_{i,j}$ 表示第 $i$ 个机器使用了 $j$ 次的最小总代价。

记 $V=\max a_i$，即 $j$ 的上界，则从 $f_{i-1}\to f_i$ 的转移步骤如下：

- $f_{a_i}$ 变成 $\min_{k\ge a_i} f_{k}$，$f_{a_i+1}\sim f_{V}$ 设为 $\infty$，然后翻转 $f_0\sim f_{a_i}$。

  此时 $f_j$ 表示还剩 $j$ 个球没放的最小代价，答案就是此时的 $f_0$。

- $f_j\gets \min_{k\le j} f_k$，然后 $f_j\gets f_j+j\times w_i$。

那么感性理解 $f$ 是具有凸性的，观察序列的差分数组，我们首先要弹出若干末尾元素，然后翻转序列并把符号取反，再把元素和 $0$ 取 $\min$ 后全局 $+w_i$。

容易发现差分数组始终单调递增。

那么尝试直接维护差分数组和首项，每次维护首项，相当于维护 $\min_{k\ge a_i} f_k$，从末项开始减去所有 $>0$ 的差分值即可。

那么剩下的就是动态维护这个数组，可以发现弹出位置 $>a_i$ 的差分值和值 $>0$ 的差分值一定删掉了一个后缀，而这个后缀最终的差分值都会变成 $w_i$。

所以我们的操作相当于后缀推平，可以颜色段均摊，用一个栈暴力维护所有极长相等的差分值，每次操作末尾。

但我们还需要进行序列翻转、符号取反、全局加三种操作。

后两种容易用懒标记实现，第一种用双端队列代替栈即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e5+5;
const ll inf=1e18;
int n,a[MAXN],w[MAXN];
struct info {
	int len; ll val;
};
deque <info> dp;
bool rev=0;
ll mul=1,add=0;
info qry() {
	auto it=rev?dp.front():dp.back();
	return {it.len,it.val*mul+add};
}
void pop() { rev?dp.pop_front():dp.pop_back(); }
void push(info it) {
	if(it.len>0) {
		it.val=(it.val-add)/mul;
		rev?dp.push_front(it):dp.push_back(it);
	}
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<n;++i) cin>>w[i];
	int mx=*max_element(a+1,a+n+1);
	ll Z=1ll*max(a[1],a[2])*w[1],sm=0;
	if(a[2]<=a[1]) {
		sm=1ll*mx*w[2];
		push({mx,w[2]});
	} else {
		push({a[2]-a[1],w[2]-w[1]});
		push({mx-(a[2]-a[1]),w[2]});
		sm=1ll*(a[2]-a[1])*(w[2]-w[1])+1ll*w[2]*(mx-(a[2]-a[1]));
	}
	cout<<Z<<"\n";
	for(int i=3;i<=n;++i) {
		ll nw=Z+sm;
		for(int t=mx-a[i];t;) {
			auto it=qry();
			if(it.len<=t) {
				sm-=it.len*it.val,nw-=it.len*max(0ll,it.val);
				t-=it.len,pop();
			} else {
				sm-=t*it.val,nw-=t*max(0ll,it.val);
				if(rev) dp.front().len-=t;
				else dp.back().len-=t;
				t=0;
			}
		}
		rev^=1,mul*=-1,add*=-1,sm*=-1,Z=nw,cout<<Z<<"\n";
		if(i==n) break;
		int dl=mx-a[i];
		while(dp.size()&&qry().val>0) {
			auto it=qry();
			sm-=it.val*it.len,dl+=it.len,pop();
		}
		push({dl,0}),add+=w[i],sm+=1ll*mx*w[i];
	}
	return 0;
}
```

---

