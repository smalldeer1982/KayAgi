# [COTS 2021] 赛狗游戏 Tiket

## 题目背景

Rebirth.

译自 [Izborne Pripreme 2021 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2021/) D2T3。$\texttt{1s,0.5G}$。


## 题目描述

有三个人在观看赛狗游戏。

三个人都猜测了狗冲过终点的顺序，即 $P_i$ 表示第 $i$ 只冲过终点的狗的编号。我们假设没有平局。

有 $N$ 条狗，因此 $P_i$ 构成一个 $1\sim N$ 的排列。不妨记第 $j$ 个人猜测的排列为 $P(j)$。

此外，最终狗冲过终点的顺序构成排列 $T$。

计算满足以下条件的数对 $(a,b)$ 的数量：

- 在 $T$ 中，$a$ 在 $b$ 前面；
- $\forall 1\le j\le 3$，要么 $a$ 在所有的 $P(j)$ 中都在 $b$ 前面，要么 $b$ 在所有的 $P(j)$ 中都在 $a$ 前面。


## 说明/提示


#### 样例解释

样例 $1$ 解释：只有 $(2,3)$ 满足条件。


#### 数据范围


对于 $100\%$ 的数据，保证：

- $2\le N\le 5\times 10^5$；
- $\forall 1\le j\le 3$，$P(j)$ 构成一个 $1\sim N$ 的排列。
- $T$ 构成一个 $1\sim N$ 的排列。


| 子任务编号 | $N\le $ |  特殊性质   | 得分 |  
| :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 5\, 000 $    |  无  | $ 7 $   |  
| $ 2 $    | $ 5\times 10^5 $   |  有 | $ 8 $   |  
| $ 3 $    | $ 5\times 10^4$ | 无  | $ 29 $   |  
| $ 4 $    | $ 5\times 10^5 $  |  无 | $ 56 $   |  

特殊性质：$P(1)=P(2)$。也就是说前两个人猜的排列是一样的。

## 样例 #1

### 输入

```
3
2 3 1
1 2 3
1 2 3
2 3 1```

### 输出

```
1```

## 样例 #2

### 输入

```
4
3 1 2 4
4 3 2 1
1 2 3 4
1 2 4 3```

### 输出

```
0```

## 样例 #3

### 输入

```
5
1 3 2 4 5
4 3 5 2 1
4 3 1 2 5
1 2 4 3 5```

### 输出

```
3```

# 题解

## 作者：fzitb7912 (赞：14)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

[参考文献](https://www.cnblogs.com/YunQianQwQ/p/16364951.html)，云浅老师好强。 /bx/bx/bx

## 分析

发现条件 $1$ 没有什么用。令 $a_i$ 为 $i$ 在 $P(1)$ 中的位置；$b_i$ 为 $i$ 在 $P(2)$ 中的位置；$c_i$ 为 $i$ 在 $P(3)$ 中的位置。若满足 $a_i < a_j \land b_i < b_j \land c_i <c_j $，且 $T$ 中 $i$ 在 $j$ 前面，则满足条件。若此时 $T$ 中 $i$ 在 $j$ 后面，那么就可以把 $i,j$ 交换一下，也满足条件。

所以原题就是求满足：$a_i <a_j\land b_i < b_j\land c_i<c_j$ 的二元组 $(i,j)$ 的数量。这是一个三位偏序的板子，使用 CDQ 分治可以做到 $O(n \log^2 n)$。需要细微卡常，但是能过。

在这里介绍一下时间复杂度为 $O(n\log n)$ 的算法。该算法带了一个 $3$ 倍的常数，不过不影响。我们考虑把一个三维偏序问题转化为 $3$ 个二维偏序问题的交。令 $S_1=\{(i,j)|a_i<a_j\},S_2=\{(i,j)|b_i<b_j\},S_3=\{(i,j)|c_i<c_j\}$。那么有答案集合 $S=S_1\cap S_2\cap S_3$，则 $(i,j)$ 的数量为 $|S_1\cap S_2\cap S_3|$。根据容斥有：$|S_1\cap S_2\cap S_3|=\frac{|S_1\cap S_2|+|S_2\cap S_3|+|S_3\cap S_1|-|S_1\cup S_2\cup S_3|}{2}$。其中 $S_1,S_2,S_3$ 分别能够算出来，难点在于维护 $|S_1\cup S_2\cup S_3|$。这里需要一点注意力。

对于一对 $(i,j)$，我们会发现若它们满足一维偏序，则 $(j,i)$ 满足二维偏序；若它们满足二维偏序，则 $(j,i)$ 满足一维偏序；若它们满足三维偏序，则 $(j,i)$ 不满足任何偏序。而 $S_1,S_2,S_3$ 中任何一对 $(i,j)$ 至少满足二维偏序。所以 $|S_1\cup S_2\cup S_3|$ 刚好是无序二元组 $(i,j)$ 的数量，即 $\frac{n\times (n-1)}{2}$。

所以原式子可以写成：$|S_1\cap S_2\cap S_3|=\frac{|S_1\cap S_2|+|S_2\cap S_3|+|S_3\cap S_1|-\frac{n\times(n-1)}{2}}{2}$。所以只需要算出来 $|S_1\cap S_2|,|S_2\cap S_3|,|S_3\cap S_1|$ 就能求解三维偏序问题了。时间复杂度 $O(n\log n)$。

## 代码

```cpp
il void solve(){
	n=rd;int ans=0;
	for(re int i=1;i<=n;++i) rd;
	for(re int i=1;i<=n;++i) a[rd]=i;
	for(re int i=1;i<=n;++i) b[rd]=i;
	for(re int i=1;i<=n;++i) c[rd]=i;
	
	for(re int i=1;i<=n;++i) d[a[i]]=b[i];
	for(re int i=1;i<=n;++i) ans+=query(d[i]),add(d[i],1);
	for(re int i=1;i<=n;++i) tr[i]=0;

	for(re int i=1;i<=n;++i) d[b[i]]=c[i];
	for(re int i=1;i<=n;++i) ans+=query(d[i]),add(d[i],1);
	for(re int i=1;i<=n;++i) tr[i]=0;

	for(re int i=1;i<=n;++i) d[c[i]]=a[i];
	for(re int i=1;i<=n;++i) ans+=query(d[i]),add(d[i],1);
	for(re int i=1;i<=n;++i) tr[i]=0;
	
	printf("%lld\n",(ans-n*(n-1)/2)/2);	
	return ;
}
```

---

## 作者：飞雨烟雁 (赞：8)

提供一个 $\Theta(n\log n)$ 的方法。

**题意如下**：

给定排列 $T,P(1),P(2),P(3)$，计算满足以下条件的数对 $(a,b)$ 的数量：

1. 在 $T$ 中，$a$ 在 $b$ 前面；

2. $\forall 1\le j\le 3$，要么 $a$ 在所有的 $P(j)$ 中都在 $b$ 前面，要么 $b$ 在所有的 $P(j)$ 中都在 $a$ 前面。

---

本题的关键是：**排列 $T$ 长什么样对答案没有影响**。这是因为如果数对 $(a,b)$ 满足条件 2，那么 $(b,a)$ 也满足条件 2。并且 $(a,b)$ 和 $(b,a)$ 中恰有一者满足条件 1，故 $(a,b),(b,a)$ 恰有一者满足题意。因此，答案等于满足条件 2 的数对 $(a,b)$ 的数量的一半。

那么我们只需计算有多少个数对 $(a,b)$ 满足 $\forall 1\le j\le 3$，$a$ 在所有 $P(j)$ 中排在 $b$ 前面即可。这是三维偏序，可以利用[此处的方法](https://www.cnblogs.com/YunQianQwQ/p/16364951.html)做到 $\Theta(n\log n)$ 求解。

代码如下：


```cpp
#include <cstdio>
#define ll long long
#define lowbit(x) ((x) & (-(x)))
const int Mx = 5e5 + 5;

int Tr[Mx], n;
void Add(int x){ while(x <= n) ++Tr[x], x += lowbit(x);}
int Query(int x){
	int res = 0;
	while(x) res += Tr[x], x -= lowbit(x);
	return res;
}

int TP[Mx];
ll TwoPartial(int A[], int B[], int n){
	for(int i = 0; i <= n; ++i) Tr[i] = 0;
	for(int i = 1; i <= n; ++i) TP[B[i]] = A[i];
	ll res = 0;
	for(int i = 1; i <= n; ++i) res += Query(TP[i]), Add(TP[i]);
	return res;
}

ll ThreePartial(int A[], int B[], int C[], int n){
	ll res = TwoPartial(A, B, n) + TwoPartial(A, C, n) + TwoPartial(B, C, n);
	return (res - 1ll * n * (n - 1) / 2) / 2;
}

int A[Mx], B[Mx], C[Mx];
int main(){
	scanf("%d", &n);
	for(int i = 1, j; i <= n; ++i) scanf("%d", &j);
	for(int i = 1, j; i <= n; ++i) scanf("%d", &j), A[j] = i;
	for(int i = 1, j; i <= n; ++i) scanf("%d", &j), B[j] = i;
	for(int i = 1, j; i <= n; ++i) scanf("%d", &j), C[j] = i;
	printf("%lld", ThreePartial(A, B, C, n));
	return 0;
} 
```

---

## 作者：ivyjiao (赞：3)

大家都在说本题，其实本题挺像三位偏序板子的，我就重点说一说算法吧。

---

前置知识：

- [P10815 【模板】快速读入](https://www.luogu.com.cn/problem/P10815)（没错，这题特别特别卡常）
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---

三维偏序是 CDQ 分治的一个分支，也是一个重要应用。CDQ 分治的其他应用包括 CDQ 分治优化 DP、ex 斜率优化 DP 等。

想必大家都听过分治这个思想吧（类似线段树），CDQ 分治也是如此，通过把序列分成左右两端最后合并答案，能够把时间复杂度降到 $O(n\log n)$ 级别。

首先把序列按 $a_i$ 从小到大排序。

假如我们现在已经写好了 `CDQ(l,r)`，并且已经求出了 `CDQ(l,mid)` 和 `CDQ(mid+1,r)`，那么我们要求的就是在 $1\leq p\leq mid,mid+1\leq q\leq r$ 中，有多少数对 $(p,q)$ 满足 $a_p<a_q,b_p<b_q,c_p<c_q$。

由于此时 $a$ 有序，条件转化为 $p<q$，一定满足，所以我们只看后两个条件。我们把 $[l,mid],(mid,r]$ 两段按 $b_i$ 排序，然后使用双指针，枚举每个 $q$ 时把所有 $b_p<b_q$ 的 $c_p$ 插入树状数组，然后查找 $<c_q$ 的 $c_p$ 有多少个，统计答案。

三维偏序的一个经典通用优化就是把 $a_i,b_i,c_i$ 均相同的点合并成一个点，答案的权重也为合并的数量。

时间复杂度就是分治的 $O(\log n)$ 加上统计答案双指针的 $O(n)$ 和树状数组的 $O(\log n)$ 等于 $O(n\log^2 n)$。

代码（注意，本题特别卡常）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+1;
int n,k,l1,l2,b[N];
long long ans;
struct node{
    int a,b,c,cnt,ans;
}a[N],c[N];
inline bool chkdiff(node x,node y){
    return (x.a!=y.a)||(x.b!=y.b)||(x.c!=y.c);
}
inline bool cmp(node x,node y){
    if(x.a!=y.a) return x.a<y.a;
    if(x.b!=y.b) return x.b<y.b;
    return x.c<y.c;
}
inline bool cmp1(node x,node y){
    if(x.b!=y.b) return x.b<y.b;
    return x.c<y.c;
}
inline void add(int x,int k){
    for(;x<=n;x+=x&-x) b[x]+=k;
}
inline int qsum(int x){
    int ans=0;
    for(;x;x-=x&-x) ans+=b[x];
    return ans;
}
inline void CDQ(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    CDQ(l,mid);
    CDQ(mid+1,r);
    sort(c+l,c+mid+1,cmp1);
    sort(c+mid+1,c+r+1,cmp1);
    int p=l,q=mid+1;
    while(q<=r){
        while(p<=mid&&c[p].b<=c[q].b){
            add(c[p].c,c[p].cnt);
            ++p;
        }
        c[q].ans+=qsum(c[q].c);
        ++q;
    }
    for(int i=l;i<p;++i) add(c[i].c,-c[i].cnt);
}
inline char get(){
    static char buf[1000010],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int x=0;
    char ch=get();
    while(ch<'0'||ch>'9') ch=get();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=get();
    return x;
}
int main(){
    n=read();
    for(int i=1;i<=n;++i) read();
    for(int i=1;i<=n;++i) a[read()].a=i;
    for(int i=1;i<=n;++i) a[read()].b=i;
    for(int i=1;i<=n;++i) a[read()].c=i;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;++i){
        ++l1;
        if(chkdiff(a[i],a[i+1])){
            c[++l2]={a[i].a,a[i].b,a[i].c,l1};
            l1=0;
        }
    }
    CDQ(1,l2);
    for(int i=1;i<=l2;++i) ans+=c[i].ans;
    printf("%lld",ans);
}
```

---

## 作者：_zuoqingyuan (赞：1)

# 思路分析

分别令 $a_i,b_i,c_i$ 表示 $i$ 在 $P_1,P_2,P_3$ 中的排名

首先，对于所有满足条件的 $(i,j)$，可分为以下几种情况。

- $i<j,a_i<a_j,b_i<b_j,c_i<c_j$。

- $i<j,a_i>a_j,b_i>b_j,c_i>c_j$。

事实上，我们可以将 $T,P_1,P_2,P_3$ 都反转，把第二类二元组转化为：

- $i>j,a_i<a_j,b_i<b_j,c_i<c_j$。

和第一类二元组相结合，可以把第一维的限制去掉，这就是一个三维偏序的模板了。

观察数据范围，发现 $n\le 5\times 10^5$，通常解决三维偏序的算法时间复杂度为 $O(n\log^2n),O(n\sqrt n)$，都不能在正确的时间内通过本题。

其实三维偏序还存在一个 $O(n\log n)$ 的容斥做法。

我们记 $S(a,b)$ 为存在多少 $(i,j)$ 满足 $a_i<a_j,b_i<b_j$。然后计算 $ans=S(a,b)+S(b,c)+S(a,c)$。

这个答案并不是三维偏序的对数，对于每一个三维偏序，我们都将其统计了 $3$ 次（$S(a,b),S(b,c),S(a,c)$ 各有一次贡献）。

对于**仅仅**只有二维偏序的对数，我们将其统计了 $1$ 次（例如：对于 $(i,j)$，如果满足 $b_i<b_j,c_i<c_j,a_i>a_j$，那么它会在 $S(b,c)$ 中贡献为 $1$，在 $S(a,b),S(a,c)$ 中贡献为 $0$）。我们要想办法消掉这一部分。

有这么一个结论，**三维偏序的对数和仅仅满足二维偏序的对数的和为总对数的一半**。

证明：对于任意 $(i,j)$，如果 $(i,j)$ 是三维偏序，那么 $(j,i)$ 是零维偏序，如果 $(i,j)$ 是二维偏序，那么 $(j,i)$ 是一维偏序。可以自己写几个数手模一下，对于 $(i,j)$ 为零维偏序和一维偏序同样可以证明。

所以对于任意 $(i,j)$，如果它是三维或二维偏序，那么 $(j,i)$ 一定不是；如果 $(i,j)$ 不是三维或二维偏序，那么 $(j,i)$ 一定是。显然，结论成立。


我们令 $ans$ 减去 $\frac{n(n-1)}{2}$，此时 $ans$ 中只将每个三维偏序算了两遍，直接取一半输出就可以。

时间复杂度为 $O(n\log n)$。

# Code:


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int c[N],res,n;
struct node{int a,b,c;}q[N];
bool cmp_a(node a,node b){return a.a<b.a;}
bool cmp_b(node a,node b){return a.b<b.b;}
inline void read(int &a){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return a=x,void();
}
inline void add(int x,int t){
	for(;x<=n;x+=(x&-x))c[x]+=t;
	return;
}
inline int ask(int x){
	int cnt=0;
	for(;x>0;x-=(x&-x))cnt+=c[x];
	return cnt;
}
signed main(){
	read(n);
	for(int i=1,x;i<=n;i++)read(x);
	for(int i=1,x;i<=n;i++)read(x),q[x].a=i;
	for(int i=1,x;i<=n;i++)read(x),q[x].b=i;
	for(int i=1,x;i<=n;i++)read(x),q[x].c=i;
	sort(q+1,q+1+n,cmp_a);
	for(int i=1;i<=n;i++){
		res+=ask(q[i].b);
		add(q[i].b,1);
	}
	for(int i=1;i<=n;i++)add(q[i].b,-1);
	for(int i=1;i<=n;i++){
		res+=ask(q[i].c);
		add(q[i].c,1);
	}
	for(int i=1;i<=n;i++)add(q[i].c,-1);
	sort(q+1,q+1+n,cmp_b);
	for(int i=1;i<=n;i++){
		res+=ask(q[i].c);
		add(q[i].c,1);
	}
	res=(res-(n*(n-1)/2))/2;
	printf("%lld\n",res);
	return 0;
}  
```

参考：[在 $O(n\log n)$ 的时间复杂度内计算三维偏序。](https://www.cnblogs.com/YunQianQwQ/p/16364951.html)

如有错误，请指出。

---

## 作者：Bobi2014 (赞：0)

这是一道~~可癌~~的~~毒瘤、卡常~~题。

### 前置知识

- [【模板】快速读入](https://www.luogu.com.cn/problem/P10815)
- [【模板】三维偏序（陌上花开）](https://www.luogu.com.cn/problem/P3810)

### 思路

其实条件 $1$ 并没有用，因为 $a$ 在所有的 $P(j)$ 中都在 $b$ 前面或 $b$ 在所有的 $P(j)$ 中都在 $a$ 前面中，$a$ 在 $T$ 中要么比 $b$ 后，要么前，也就是满足条件 $2$ 的 $(a,b)$ 与 $(b,a)$，其中有且只有 $1$ 组满足条件。

转化后就变成三位偏序的模板了，记得用快速读入。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
struct node{
    int a,b,c;
} e[N],t[N];
int n,ans;
namespace Bit{
    int cnt[N];
    void add(int x,int v){
        for(;x <= n;x += x & -x){
            cnt[x] += v;
        }
    }
    int query(int x){
        int res = 0;
        for(;x > 0;x -= x & -x){
            res += cnt[x];
        }
        return res;
    }
}
char get(){
    static char buf[1 << 20],*p1 = buf,*p2 = buf;
    if(p1 == p2){
        p2 = (p1 = buf) + fread(buf,1,1 << 20,stdin);
        if(p1 == p2){
            return EOF;
        }
    }
    return *p1 ++;
}
int read(){
    int x = 0,f = 1;
    char ch = get();
    while(ch < '0' or ch > '9'){
        if(ch == '-'){
            f = -1;
        }
        ch = get();
    }
    while(ch >= '0' and ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = get();
    }
    return x * f;
}
void write(int x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9){
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
void cdq(int l,int r){
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l,mid);
    cdq(mid + 1,r);
    int p = l,q = mid + 1,cnt = 0;
    while(p <= mid and q <= r){
        if(e[p].b <= e[q].b){
            Bit::add(e[p].c,1);
            t[++cnt] = e[p ++];
        }else{
            t[++cnt] = e[q ++];
            ans += (Bit::query(e[q - 1].c));
        }
    }
    while(p <= mid){
        Bit::add(e[p].c,1);
        t[++cnt] = e[p ++];
    }
    while(q <= r){
        t[++cnt] = e[q ++];
        ans += (Bit::query(e[q - 1].c));
    }
    for(int i = l;i <= mid;i ++){
        Bit::add(e[i].c,-1);
    }
    for(int i = l;i <= r;i ++){
        e[i] = t[i - l + 1];
    }
}
signed main(){
    n = read();
    for(int i = 1;i <= n;i ++){
        read();
    }
    for(int i = 1;i <= n;i ++){
        e[read()].a = i;
    }
    for(int i = 1;i <= n;i ++){
        e[read()].b = i;
    }
    for(int i = 1;i <= n;i ++){
        e[read()].c = i;
    }
    sort(e + 1,e + n + 1,[](node x,node y){
        return x.a < y.a;
    });
    cdq(1,n);
    write(ans);
    return 0;
}
```

---

