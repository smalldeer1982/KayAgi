# [ABC396F] Rotated Inversions

## 题目描述

给定整数 $N, M$ 和一个长度为 $N$ 的非负整数序列 $A=(A_1, A_2, \ldots, A_N)$。

对于每个 $k=0,1,\ldots,M-1$，请解决以下问题：

> 定义整数序列 $B=(B_1, B_2, \ldots, B_N)$，其中 $B_i = (A_i + k) \bmod M$。求序列 $B$ 的逆序对数。

关于逆序对数的定义：  
序列 $(A_1, A_2, \ldots, A_N)$ 的逆序对数是指满足 $1 \leq i < j \leq N$ 且 $A_i > A_j$ 的整数对 $(i, j)$ 的个数。


## 说明/提示

### 约束条件

- $1 \leq N, M \leq 2 \times 10^5$
- $0 \leq A_i < M$
- 输入中的所有值均为整数

### 样例解释 1

- 当 $k=0$ 时：$B=(2, 1, 0)$，逆序对数为 $3$（所有 $(i,j)$ 对均满足条件）。
- 当 $k=1$ 时：$B=(0, 2, 1)$，逆序对数为 $1$（仅 $(2,3)$ 满足）。
- 当 $k=2$ 时：$B=(1, 0, 2)$，逆序对数为 $1$（仅 $(1,2)$ 满足）。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 3
2 1 0```

### 输出

```
3
1
1```

## 样例 #2

### 输入

```
5 6
5 3 5 0 1```

### 输出

```
7
3
3
1
1
5```

## 样例 #3

### 输入

```
7 7
0 1 2 3 4 5 6```

### 输出

```
0
6
10
12
12
10
6```

# 题解

## 作者：xxgirlxx (赞：7)

## 题外话

> 这个题一看就非常适合 AI 做啊。——by @[lcrh](https://www.luogu.com.cn/user/13127)

## 题目大意

给出长度为 $n$ 的序列 $a$，保证 $0\le a_i<m$，接下来进行 $m$ 轮操作，每轮将 $a_i$ 变为 $(a_i+1)\operatorname{mod}m$，求每轮操作前序列 $a$ 的逆序对数量。

## 题目思路

考虑将每个数的贡献挂到它的值将要从 $m-1$ 变成 $0$ 的时候，然后多枚举几种情况就会发现这个时候后面的数只要不等于它就会减少逆序对，前面的数只要不等于它就会增加逆序对，然后将值的变动存起来差分后加上最初的逆序对数量即可。

## Code

[赛时的丑陋代码（~~赛后换了个号重交的~~）](https://atcoder.jp/contests/abc396/submissions/63698980)

[赛后的清晰（~~应该是更清晰了的吧~~）代码](https://atcoder.jp/contests/abc396/submissions/63699306)

---

## 作者：cwd2023 (赞：3)

## AT_abc396_f 题解
### by cwd2023


---

### 思路：
首先，我们化繁为简，先正常求一遍逆序对数量，再枚举 $k$，想办法快速转移。

由于 $A$ 数组中的值每次会对 $m$ 取模，所以其中的元素是周期性的，当元素 $a_i+k$ 过大以至于大于等于 $m$，就会发生一些很神奇的变化了。

对于它前面的元素，原本不与它构成逆序对且不与它相等的元素便会与它构成逆序对。

对于它后面的元素，原本与它构成逆序对的元素不会再与它构成逆序对。

最后，第一步中求逆序对我用的是树状数组，第二部中要用到一个 $g$ 数组，$g_i$ 中存储所有 $a$ 数组中值为 $i$ 的元素位置。这样，两种情况都可以快速转移。具体看代码吧。


---


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,ans,cur;
ll a[200010],t[200010];
vector<ll>g[200010];
struct N{
	ll val,pos;
	friend bool operator<(N a,N b){return a.val==b.val?a.pos>b.pos:a.val>b.val;}
};
vector<N>v;
inline void add(ll p,ll k){for(;p<=n;p+=(p&(-p)))t[p]+=k;}
inline ll ask(ll p){
	ll res=0;
	for(;p>=1;p-=(p&(-p)))res+=t[p];
	return res;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		v.push_back({a[i],i});
		g[a[i]].push_back(i);
	}
	sort(v.begin(),v.end());
	for(auto k:v){
		ll pos=k.pos;
		ans+=ask(pos),add(pos,1);
	}//正常求逆序对
	cout<<ans<<"\n";//别忘了先输出一个
	for(ll i=m-1;i>=1;i--){
		for(ll j=0;j<(ll)g[i].size();j++){
			ans+=g[i][j]-(j+1);
//对于前面的，一共 (g[i][j]) 个元素，相同的有 (j+1) 个。
			ans-=(n-g[i][j])-(g[i].size()-j-1);
//对于后面的，一共 (n-g[i][j]) 个元素，相同的有 (g[i].size()-j-1) 个。
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

最后，希望本篇题解对你有所帮助，感谢观看。

**望管理员通过！**

---

## 作者：Ray_yi (赞：3)

### 思路：

通过题目可知，在每一次改变后，只有等于 $M$ 的数才会变成 $0$，也就是最小数，其他的数只会在原本的基础上加 $1$，自己想想就能发现，在每一轮变化时，其他的数的贡献不会变。

而贡献唯一会变化的，是在下一轮要变成 $0$ 的数，也就是下一轮要变成 $M$ 的数。

- 在这个数前面的数都比它大或相等，这个时候，我们就需要加上少算的逆序对个数，也就是在这个数前面的且不等于它本身的数的个数。
- 在这个数后面的数也一定大于或等于这个数，这时，我们需要减去在上一轮中多算的逆序对个数，也就是在这个数后面的且不等于它本身的数的个数。

知道这两点后，我们就可以先算出初始数列的逆序对个数，再遍历 $k$，在每一轮中找出下一轮将要变为 $0$ 的数，再变化答案就可以了。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) x&-x
using namespace std;
ll n,m,s,tree[200005],ans;
vector<int> pos[200005];
void update(int x){
	while(x<=m){
		tree[x]++;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while(x){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
		cin>>s;
		pos[s].push_back(i);
		update(s+1);//这里必须加1，树状数组下标不能为0
		ans+=sum(m)-sum(s+1);
	}//树状数组求逆序对，不会的可以去找求逆序对的例题，这里就不详讲了
	cout<<ans<<'\n';//初始数列中逆序对的个数 
	for(int k=1;k<m;k++){//枚举k 
		for(int i=0;i<pos[m-k].size();i++){
            //下面两行可以自己根据上面的两条推出来
			ans+=pos[m-k][i]-i;//加上在它前面的不等于本身的个数
			ans-=n-pos[m-k][i]-pos[m-k].size()+i;//撤销多算的数
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：2)

这是一篇视频题解。

![](bilibili:BV1xBRsYxE6S?t=679)

[代码链接](https://atcoder.jp/contests/abc396/submissions/63557693)

---

## 作者：littlebug (赞：2)

F<<<<<E。

## Solution

首先可以把 $k = 0,1,2,\dots,m-1$ 拆成每次整体 $+1$ 的操作。

注意到一次操作时变化的数只有操作后刚好 $=m$ 的数，因为其它的数相对位置不会改变，于是逆序对数就不会改变。

于是设这个要变化的数为 $a_i$，则有：

- $a_i$ 和它后面的每个 $\ne a_i$ 的数都形成了逆序对，且这些逆序对在操作后消失。  
注：因为 $a_i$ 显然是最大的了，所以 $<a_i$ 相当于 $\ne a_i$
- $a_i$ 和它前面的每个 $\ne a_i$ 的数都没有形成逆序对，不过在操作后会形成。

于是，答案的变化量就可以这样算出来了，先对于每个 $a_i$ 预处理出 $a_i$ 前后 $\ne a_i$ 的数的个数，在操作的时候均摊 $O(n)$。

当然最开始要先把原数组逆序对算出来。

时间复杂度 $O(n)$。

## Code

```cpp
int n,m,a[MAXN];
vector <int> c[MAXN];
pii d[MAXN];

namespace nxd // 求一个数组的逆序对数
{
    class __BIT
    {
    private:
        int v[MAXN];
    public:
        il void upd(int pos,int k) {for(int i=pos;i<=n;v[i]+=k,i+=(i&-i));}
        il int q(int pos) {int res=0; for(int i=pos;i;res+=v[i],i-=(i&-i)); return res;}
        il void clear() {memset(v,0,sizeof(v));}
    } tr;

    pii a[MAXN];
    int b[MAXN];

    il int calc(int *_a)
    {
        rep(i,1,n) a[i].st=_a[i],a[i].nd=i;
        sort(a+1,a+n+1);
        rep(i,1,n) b[a[i].nd]=i;
        int ans=0; rep(i,1,n) tr.upd(b[i],1),ans+=i-tr.q(b[i]);
        return ans;
    }
}

signed main()
{
    read(n,m),_::r(a,n);

    rep(i,1,n) c[a[i]].pb(i);
    rep(i,1,n) d[i].st=(i-1)-(lower_bound(all(c[a[i]]),i)-c[a[i]].begin()), // 当然这里可以 O(n) 来做，维护后缀个数即可，但是赛时为了方便没这么写。
               d[i].nd=(n-i)-(c[a[i]].end()-lower_bound(all(c[a[i]]),i)-1);

    int ans=nxd::calc(a);
    
    rpe(i,m-1,0)
    {
        write(ans,'\n');
        for(auto j:c[i]) ans+=d[j].st,ans-=d[j].nd;
    }

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：liangbob (赞：1)

## ABC396F 题解

[题目链接](https://atcoder.jp/contests/abc396/tasks/abc396_f)。

[或许更好的阅读体验](https://www.cnblogs.com/sslbj/p/18771061)。

### 定义

定义 $k=p$ 时：

- $[x+1,n]$ 中 $b$ 等于 $m-1$ 的数的个数为 $f(p,x)$。
- $[1,x-1]$ 中 $b$ 等于 $m-1$ 的数的个数为 $g(p,x)$。
- $b_x$ 的值为 $b^k_x$。
- $b_x=y$ 的 $x$ 的个数为 $c^k_y$​。

### 问题分析：从简单入手

我们先来考虑 $k=0$ 和 $k=1$ 这两种简单情况。

当 $k=0$ 时，树状数组求逆序对解决之。

当 $k=1$ 时，本质上变化的只有 $b^0_x=m-1$ 的那些数。考虑其中一个数 $b^0_x$。

- 考虑它原本贡献的逆序对数，为 $n-x-f(0,x)$。这个要减去。
- 考虑它变成 $0$ 之后贡献的逆序对数，为 $x-1-g(0,x)$。这个要加上。
- 最终 $k=0$ 到 $k=1$ 答案的变化量为：

$$
x-1-g(0,x) - (n-x-f(0,x))=2x-1-n+(f(0,x)-g(0,x))
$$

### 推广结论

当 $k=q$ 时，类似地，我们有 $k=q-1$ 到 $k=q$ 的答案变化量为：
$$
x-1-g(q-1,x) - (n-x-f(q-1,x))=2x-1-n+(f(q-1,x)-g(q-1,x))
$$

原因显然，我们在分析 $k=1$ 时的过程中没有用到其独有的特殊性质。因此这个式子同样适用于 $k=q$ 的过程。

### 转化条件

我们考虑转化当 $k=p$ 时，$a^k_x=m-1$ 这个条件。

当 $k=p$ 时，$a^k_x=m-1$ 等价于 $(a^0_x+p)\bmod m=m-1$。

即，$a^0_x+p=m-1$ 或 $a^0_x+p=rm-1$，其中 $r \ge 2$。

考虑后者是否可行，由于 $0\le p \le m-1$，于是有 $a^0_x=rm-1-p\ge (r-1)m \ge m$，矛盾。

所以可以得出结论：当 $k=p$ 时，$a^k_x=m-1$ 等价于 $a_x^0=m-1-p$​。

### 问题缩小：$f$ 和 $g$ 怎么求？

现在关键问题是如何计算对于每个 $x$ 算出 $f(p,x)$ 和 $g(p,x)$。

根据上面的转化，$g(p,x)$ 等价于求出 $y \in [1,x-1]$ 中 $a^0_y$ 等于 $m-1-p$ 的数有多少个。

观察到每次我们都只是在计算形如 $g(q-1,x)$ 的这么一个式子。发现里面的 $x$ 都保证 $a^{q-1}_x=m-1$（我们本身枚举的就是这些 $x$），即 $a^0_x=m-q$。我们要找到 $y\in [1,x-1]$ 中 $a^0_y=m-q$ 的数的个数。

即，本质上，我们对于每个 $a^0_x$ 都要找到 $[1,x-1]$ 中等于 $a^0_x$ 的数的个数。写一个树状数组，预处理即可。

而对于 $f(p,x)$，显然 $x$ 一定满足在 $k=p$ 时，$a^k_x=m-1$ 条件（理由同上），于是 $f(p,x)=c^p_{m-1}-1-g(p,x)$​。

### 复杂度分析

由于每个数最多变成一次 $m-1$，因此对于每个 $k$ 直接枚举 $k-1$ 时哪些数为 $m-1$，这么做不会不会超时，总时间复杂度为 $O(m)$​。

前面我们需要使用树状数组预处理出 $g$ 的值，复杂度为 $O(n \log n)$。

因此综上所述，该算法的复杂度为 $O(n \log n)$，可以通过本题。

### [代码](https://atcoder.jp/contests/abc396/submissions/63710522)

---

## 作者：StayAlone (赞：1)

非常简单的题，但是具有诈骗性质！

被骗了十几分钟。

### 题意

给定一个值域 $[0, M)$ 的序列，对于 $k=0\sim M-1$，求将 $a_i$ 变为 $a_i+k\bmod M$ 后，逆序对数量。

### 思路

先树状数组求出 $k=0$ 时的答案，考虑 $k\gets k+1$ 时答案的变化量。

发现减少的逆序对就是数对 $(M-1, x)$ 的数量，其中 $x\ne M-1$；增加的同理，是数对 $(x, M-1)$ 的数量。

由于在 $k$ 增加的过程中，每个数只会当一次 $M-1$，在它的对应时刻累计贡献就好了。于是可以写出我赛时的愚蠢代码，预处理 $s_i$ 表示 $1\sim i$ 中，$a_i$ 的出现次数，后缀同理，就可以计算了。

```cpp
int n, m, a[MAXN], cnt[MAXN], s1[MAXN], s2[MAXN];
vector <int> pos[MAXN];

struct BIT {
    int sum[MAXN];

    il void add(int x) {
        ++x;
        while (x <= m) ++sum[x], x += lowbit(x);
    }

    il int query(int x) {
        int ans = 0; ++x;
        while (x) ans += sum[x], x -= lowbit(x);
        return ans;
    }
} T;

int main() {
    read(n, m); rer(i, 1, n, a), pos[a[i]].eb(i);
    rep1(i, 1, n) s1[i] = ++cnt[a[i]];
    memset(cnt, 0, sizeof cnt);
    rep2(i, n, 1) s2[i] = ++cnt[a[i]];
    ll ans = 0;
    rep2(i, n, 1) ans += T.query(a[i] - 1), T.add(a[i]);
    rep1(i, 0, m - 1) {
        printf("%lld\n", ans);
        for (auto v : pos[m - 1 - i]) ans -= (n - v + 1) - s2[v], ans += v - s1[v];
    }
    return 0;
}
```

更好的方式是考虑补集转化。先不考虑 $x\ne M-1$ 的限制，贡献非常好算；再减去 $M-1$ 内部两两匹配的数对。此时可以发现，$(x, M-1)$ 与 $(M-1,x)$ 的多余贡献部分恰好抵消，于是直接不管 $x=M-1$ 就可以了。

也没有存 pos 的必要，读入的时候做就行了。

```cpp
int n, m; ll ans, delt[MAXN];

struct BIT {
    int sum[MAXN];

    il void add(int x) {
        ++x;
        while (x) ++sum[x], x -= lowbit(x);
    }

    il int query(int x) {
        int ans = 0; ++x;
        while (x <= m) ans += sum[x], x += lowbit(x);
        return ans;
    }
} T;

int main() {
    read(n, m); 
    rep1(i, 1, n) {
        int x = read(); ans += T.query(x + 1), T.add(x);
        delt[m - x] += (i - 1) - (n - i);
    }
    rep1(i, 0, m - 1) printf("%lld\n", ans += delt[i]);
    return 0;
}
```

---

## 作者：lfxxx_ (赞：1)

我们发现，一个数变成 $0$ 的次数最多只有一次，而只有变成 $0$ 才会对逆序对数量有影响，所以我们考虑暴力修改，这样最多修改 $N$ 次。

我们先考虑原数列 $A$ 的逆序对数量，可以用树状数组 $O(N \log N)$ 快速求出。

接下来，我们考虑开一颗线段树，对所有的 $i$ 维护满足 $i<j\le N$ 并且 $A_i>A_j$ 的 $j$ 的数量，记为 $cnt_i$。

当 $A_i$ 变成 $0$ 的时候，$cnt_i$ 显然也需要变成 $0$，而因为他之前是 $M-1$，是最大的，所以对于所有 $1 \le j <i$ 的 $cnt_j$ 都要加 $1$。

注意修改要从后往前。

查询就是 $\sum_{i=1}^ncnt_i$。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
int a[N];
vector<int>p[N];
int tr[N<<2],tag[N<<2];
void pushup(int p){tr[p]=tr[p<<1]+tr[p<<1|1];}
void addtag(int p,int pl,int pr,int d)
{
    tr[p]+=(pr-pl+1)*d;
    tag[p]+=d;
}
void pushdown(int p,int pl,int pr)
{
    if(tag[p])
    {
        int mid=(pl+pr)>>1;
        addtag(p<<1,pl,mid,tag[p]);
        addtag(p<<1|1,mid+1,pr,tag[p]);
        tag[p]=0;
    }
}
void modify(int p,int pl,int pr,int x,int d)
{ 
    if(pl==pr)
    {
        tr[p]=d;
        return ;
    }
    int mid=(pl+pr)>>1;
    pushdown(p,pl,pr);
    if(x<=mid)modify(p<<1,pl,mid,x,d);
    else modify(p<<1|1,mid+1,pr,x,d);
    pushup(p);
}
void update(int p,int pl,int pr,int L,int R,int d)
{
    if(R<pl||pr<L)
        return ;
    if(L<=pl&&pr<=R)
    {
        addtag(p,pl,pr,d);
        return ;
    }
    pushdown(p,pl,pr);
    int mid=(pl+pr)>>1;
    update(p<<1,pl,mid,L,R,d);
    update(p<<1|1,mid+1,pr,L,R,d);
    pushup(p);
}
int query(int p,int pl,int pr,int L,int R)
{
    if(R<pl||pr<L)
        return 0;
    if(L<=pl&&pr<=R)
        return tr[p];
    pushdown(p,pl,pr);
    int mid=(pl+pr)>>1;
    return query(p<<1,pl,mid,L,R)+query(p<<1|1,mid+1,pr,L,R);
}
int t[N];
void add(int x,int d)
{
    for(;x<=m+1;x+=x&-x)
        t[x]+=d;
}
int sum(int x)
{
    int ans=0;
    for(;x;x-=x&-x)
        ans+=t[x];
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=n;i;--i)
    {
        p[a[i]].emplace_back(i);
        if(a[i]>0)modify(1,1,n,i,sum(a[i]));
        else modify(1,1,n,i,0);
        add(a[i]+1,1);
    }
    cout<<query(1,1,n,1,n)<<'\n';
    for(int i=m-1;i;--i)
    {
        for(auto &x:p[i])
        {
            modify(1,1,n,x,0);
            if(x>1)update(1,1,n,1,x-1,1);
        }
        cout<<query(1,1,n,1,n)<<'\n';
    }
}
```

---

## 作者：MrPython (赞：0)

这个绝对比 E 简单。

对于 $k=0$，是经典的逆序对板子，直接做。

然后考虑 $k$ 增加 $1$ 后如何更新答案。在所有数的相对关系中，只有最大的数变成了最小的，其他的都没有变化。因此，将最大的数删除掉，并作为最小的数重新插入回去即可。

线段树可以维护这个过程。使用 `vector` 套 `vector` 以数字大小为键记录其位置。使用线段树求逆序对的过程中，我们每插入一个数时会计数其后面有多少个比他小的数。删除过程类似，先将所有待删除数的标记取消，然后对与每个数，数一下它后面有多少个比它小的数，从答案中减掉就可以。

增加则是反过来，先数出每个数前有多少个比它大的，然后再把标记恢复。

```cpp
#include <mrpython/typical_segment_tree.hpp>  // https://github.com/Mr-Python-in-China/mp-oi-library
#include <cstddef>
#include <iostream>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n, m;
  fin >> n >> m;
  vector<vector<size_t>> d(m);
  for (size_t i = 0; i < n; ++i) {
    ui x;
    fin >> x;
    d[x].emplace_back(i);
  }
  uli v = 0;
  mrpython::typical_segment_tree_add<ui> tree(n, 0);
  auto get = [&](size_t l, size_t r) { return l == r ? 0 : tree.get(l, r); };
  for (size_t i = m - 1; i < m; --i) {
    for (size_t j : d[i]) v += get(0, j);
    for (size_t j : d[i]) tree.set(j, mrpython::const_function(1));
  }
  fout << v << '\n';
  for (size_t i = m - 1; i > 0; --i) {
    for (size_t j : d[i]) tree.set(j, mrpython::const_function(0));
    for (size_t j : d[i]) v -= get(j + 1, n);
    for (size_t j : d[i]) v += get(0, j);
    for (size_t j : d[i]) tree.set(j, mrpython::const_function(1));
    fout << v << '\n';
  }
  return 0;
}
```

---

## 作者：UniGravity (赞：0)

### 题意

给定长为 $n$ 值域在 $[0,M)$ 范围内的序列 $A$，分别对 $k\in[0,M)$ 求解使得 $B_i=(A_i+k)\bmod M$ 的长度为 $n$ 的序列 $B$ 的逆序对数量。

### 题解

考虑从 $k=i-1$ 的答案推出 $k=i$ 的答案。发现其实就是找出 $A_i=M-k$ 的数并且将它们赋值为 $-k$，因为逆序对只依赖于相对大小关系。

考虑把一个最大数变成最小数会发生什么，首先逆序对会减去这个数往后所有小于它的数，然后再加上往前所有大于它修改后的值的数。发现除了等于它的数（即也在这回合修改）外其它的数必定全部选到。直接找出前后有哪些等于其的数即可。

一开始求逆序对使用树状数组即可。时间复杂度 $O(n\log m)$。

### 代码
```cpp
const int N=200005;
int n,m,a[N];
vector<int>v[N];
struct BIT{
    int c[N];
    il void add(int i,int v){for(;i<=m;i+=(i&-i))c[i]+=v;}
    il int qry(int i){int a=0;for(;i;i-=(i&-i))a+=c[i];return a;}
}ds;

signed main(){
    n=read(),m=read();
    ll ans=0;
    forto(i,1,n){
        a[i]=read(),v[a[i]].eb(i);
        ds.add(a[i]+1,1),ans+=ds.qry(m)-ds.qry(a[i]+1);
    }
    forbk(i,m-1,0){
        printf("%lld\n",ans);
        forv(j,v[i].size()){
            ans-=n-v[i][j]-((int)v[i].size()-j-1);
            ans+=v[i][j]-1-j;
        }
    }
    return 0;
}
```

---

## 作者：xukehg (赞：0)

称进位就是 $m - 1$ 变成 $0$。

先将条件转化为每次都加 $1$。考虑如果一次没有进位，逆序对数显然保持不变。如果有了进位，逆序对的变化也只跟变化的位置的数有关。

加 $0$ 即是原序列逆序对总数，用树状数组可以简单求出。对于一个进位的位置 $x$，$x$ 之前非 $0$ 的数都会与 $x$ 形成一个逆序对，由于 $a_x$ 之前是 $m - 1$，因此 $x$ 后面且现在非 $0$ 的数都会少一个逆序对。总的来说，记第 $i$ 此操作进了位的数有 $cnt_i$ 个，下标和为 $sum_i$，单次贡献为 $2 \times sum_i - cnt_i \times n - cnt_i$，模拟即可。

[记录。](https://atcoder.jp/contests/abc396/submissions/63537608)

---

## 作者：JCT_addyi (赞：0)

### 题目大意：
给你 $n$ 个数，循环 $m$ 轮，每轮每个数加 $k$ 再取余 $m$ 变成一个新数，那 $k$ 第一轮等于 $0$，之后每一轮加一，这 $n$ 个数中会有逆序对，问每一轮共有多少个逆序对。 

### 思路：
我们发现当数等于 $M$ 时它被取余后为 $0$，其他数的大小只会在原基础上加一，那么它们的大小关系不变，但是变为 $0$ 的那些数就会有影响，会产生新的逆序对，这些数就有贡献。

那么我们就需要查找这些有贡献的数，暴力肯定会超时，我们可以用前缀和的思路，树状数组就能做，要注意题目可以为 $0$ 但树状数组下标不能为 $0$ 所以要加一。

我们用动态数组存数的下标，相当于一个桶，后面可以用来去重，然后用树状数组套模板求逆序对。

- 我们先求出第一轮每个数都不变的逆序对。
- 然后还剩 $m$ 减 $1$ 轮，每轮的逆序对就是加上前面的逆序对数量和减去后面的逆序对数量，因为我们找的是有贡献的数，那么后面的大小就会改变。

### 代码：
详细看代码。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) (x&-x)
using namespace std;
ll n,m,s,tree[200005],ans;
vector<int> pos[200005];//动态2维数组 列是静态的 行只有200005 下表从0开始 
//void updata(int x){for( ;x<=m;x+=lowbit(x))tree[x]++;}//单点修改 
void updata(int x){//单点修改 
	while(x<=m){//不能超出范围，因为只有N个数 
		tree[x]++;//更改当前所在位置的值(+1)
		x+=lowbit(x);//需要把每个与该数有关的数都加上1
	}
}
//int sum(int x){return (x?sum(x-lowbit(x))+tree[x]:0);}//区间查询 1？ 2：3三目运算符 ； if 1为真运行2；else 运行3 ； 
int sum(int x){
	int re=0;
	while(x>0){//不能超出范围，因为下面没有数啦 
		re+=tree[x];//加上当前值 
		x-=lowbit(x);//从后往前的与该数有关的下标 
	}
	return re;//返回结果 
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=0;i<n;i++){
		cin>>s;
		pos[s].push_back(i);//存下标 
		updata(s+1);//题目可以为0 但树状数组下标不能为0 因为lowbit会一直为0 
		ans+=sum(m)-sum(s+1);//求逆序对 
	}
	cout<<ans<<'\n';//输出一开始的逆序对 
	for(int i=m-1;i;i--){//m-1是因为已经循环了一次了 
		for(int j=0;j<pos[i].size();j++){//找有贡献 
			ans+=pos[i][j]-j;//加上前面的贡献 
			ans-=n-pos[i][j]-pos[i].size()+j;//减去后面的贡献
            //化简前：ans-=(n-pos[i][j]-1)-(pos[i]size()-j-1); 
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

谢谢大家！

---

## 作者：MutU (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc396_f)

求出原序列逆序对数量，开 $m$ 个 vector 存每个值的出现位置。

把 $k$ 增加的过程看做把原序列每个数加一再模 $m$ 的过程。考虑求出每次改变增加或减少的逆序对数。

每次 $k$ 增加，可能有一些点从 $m-1$ 变成 $0$，只有这些点会影响逆序对数量。

通过 vector 求出这些点位置。由于这些点原本是序列中最大值，操作后变为序列中最小值，所以它们右边原本全都比它们小，左边操作后全都比它们大。减去右边数量加上左边的就做完了。

当然值一样的点永远不会产生逆序对，需要判断一下。

---

## 作者：Down_syndrome (赞：0)

## 前置知识

$O(n\log n)$ 求逆序对，怎么求都行。

## 题意

给定一个长度为 $n$ 的数组 $a$ 以及一个整数 $m$，对于 $\forall k\in[0,m)$，求出对应数组 $b_i=(a_i+k)\bmod m$ 的逆序对。

$1\le n\le 2\times 10^5,0\le a_i<m$。

## 思路

先求一遍初始的逆序对，然后递推得到答案。

容易发现，只有 $a_i=m-k$ 时，它和其它数的相对大小才会发生改变，因此只需要减去这些数原先的贡献，再加上后来的贡献即可。

可以想到，原来这些数都是 $m-1$，也就是之中最大的数，因此对于数 $a_i$ 的贡献即为 $n-i-\sum\limits_{j=i+1}[a_i=a_j]$。

因此我们可以开 $m$ 个 vector，存下每个数对应的位置，然后遍历一遍对应 vector，就能够简单的知道在它后面等于它的数的个数。

加上后来的贡献也是同理。

于是这道题成了一个【模板】逆序对了。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&-x)
using namespace std;
const int N=2e5+5;
int n,m,ans,a[N],t[N];
vector<int> g[N];
void modify(int k){
	k++;
	for(int i=k;i<=m;i+=lowbit(i)) t[i]++;
}
int query(int k){
	k++;
	int s=0;
	for(int i=k;i>=1;i-=lowbit(i)) s+=t[i];
	return s;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		g[a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		ans+=i-1-query(a[i]);
		modify(a[i]);
	}
	printf("%lld\n",ans);
	for(int i=1;i<m;i++){
		for(int j=0;j<g[m-i].size();j++) ans+=(g[m-i][j]-1-j)-(n-g[m-i][j]-(g[m-i].size()-j-1));
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Statax (赞：0)

## 前言

蒟蒻第一次不看题解切掉 ABCDEF，写几篇题解庆祝。

## 思路

我们先 $O(n \log n)$ 求出原序列逆序对个数 $c$，这个过程归并排序、树状数组都可以写。

一个很明显的性质：**当且仅当**一个数模 $M$ 为 $0$ 时，$c$ 才可能发生变化。

然后当一个数 $a_x$ 变为 $0$ 时：

对于他前面的数来说，只要原序列中和 $a_x$ 不相等都可以构成逆序对，所以要加上。

对于他后面的数来说，当 $a_x$ 变为 $0$ 时，后面本来算了关于 $a_x$ 的逆序对，就要减回来，这之中实际上包括两两本来就是逆序对的以及中途成为逆序对的。

## 注意事项

1. 十年 OI 一场空，不开 `ll` 见祖宗。

## 代码

时间复杂度 $O (n \log n)$，瓶颈在求逆序对和排序。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

#define x first
#define y second
#define db double
#define pb push_back
#define ll long long
#define i128 __int128
#define ull unsigned ll
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int MAXN = 1e6 + 5;
const int inf = 2147483627;
const int mod = 998244353;
const db eps = 1e-9;

template <typename T> inline void read (T &x) {
	x = 0; T f = 1; char ch = getchar ();
	while (!isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar ();
	x *= f;
}

template <typename T, typename... Arp> inline void read (T &x, Arp &...arp) {
	read(x), read(arp...);
}

ll res;
int n, m, to[MAXN];
struct Node { int pre, nxt, val; } a[MAXN], b[MAXN];
bool comp (const Node & a, const Node & b) { return a.val > b.val; }

void solve (int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
    int i = l, j = mid + 1, k = l;
    solve (l, mid), solve (mid + 1, r);
    while (i <= mid && j <= r) {
        if (a[i].val <= a[j].val) b[k++] = a[i++];
        else b[k++] = a[j++], res += mid - i + 1;
    } while (i <= mid) b[k++] = a[i++];
      while (j <= r) b[k++] = a[j++];
    for (int t = l; t <= r; ++t) a[t] = b[t];
}

signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
    read (n, m);
    for (int i = 1; i <= n; ++i) read (a[i].val);
    for (int i = 1; i <= n; ++i) a[i].pre = i - 1 - to[a[i].val], ++to[a[i].val];
    memset (to, 0, sizeof to);
    for (int i = n; i >= 1; --i) a[i].nxt = n - i - to[a[i].val], ++to[a[i].val];
    
    solve (1, n), sort (a + 1, a + n + 1, comp);
    for (int i = 0, j = 1; i < m; ++i) {
        while (m - a[j].val <= i) 
            res += a[j].pre, res -= a[j++].nxt;
        printf ("%lld\n", res);
    }
	return 0;
}
```

---

## 作者：ln001 (赞：0)

## 题意
给出长度为 $n$ 的序列 $a_i^0$，你需要对所有 $k \in [0, m)$ 计算序列 $a_i^k$ 的逆序对个数。

其中 $a^k_i = (a_i^0 + k) \bmod m$，$n, m \in [1, 2 \times 10^5]$，$a_i^0 \in [0, m)$。

## 做法
利用树状数组可以计算 $a_i^0$ 的答案，考虑如何利用 $a_i^{t - 1}$ 的答案计算 $a_i^t$ 的答案。

求解逆序对只需关注序列中元素的**相对大小**，不妨先设 $t = 1$，此时序列 $a_i^0$ 的变化等价为值 $m - 1$ 被全部替换为 $\min_{i = 1}^na_i^0 - 1$，$a_i^0$ 中所有涉及值 $m - 1$ 的逆序对被删除，$a_i^1$ 中涉及值 $\min_{i = 1}^na_i^1$ 的逆序对被增加。推广一下，对于 $t$ 的其他取值，容易发现他们答案的变化也满足上述过程。

将上面一步转化一下，$t$ 从 $t - 1$ 变到 $t$ 增加的逆序对为序列 $c$ 的逆序对，减少的逆序对为序列 $d$ 的逆序对。其中 $c_i = [a_i^0 \neq m - t], d_i = [a_i^0 = m - t]$。

提前统计出每个值对应的下标集合就能计算 $c_i, d_i$ 逆序对个数了。

---

## 作者：FinderHT (赞：0)

写在开头，赛时因纸张错误没过，赛后不到十分钟改了一个地方过了，来水一下题解。

### 题意

给定 $n,m$ 和序列 $a$，当 $k={0,1,\dots,m-1}$ 时，定义序列 $b$ 满足 $b_i=(a_i+k)\bmod m$，求 $b$ 的逆序对个数。

### 思路

$k=0$ 就是板子，难点是当 $k$ 增加时，逆序对个数会发生怎样的变化。

定义 $b'_{i,j}$ 为 $k=i$ 时，序列 $b$ 中第 $j$ 个元素的值，当 $k$ 由 $k$ 变 $k+1$ 时，每个 $a_i+k$ 中值都会增加 $1$，$b'_{k+1,i}=(a_i+k+1)\bmod m$。如果 $(a_i+k)\bmod m<m-1$， $b'_{k+1,i}=b'_{k,i}+1$，称为更新一；如果 $(a_i+k)\bmod m =m-1$，$b'_{k+1,i}=0$，称为更新二。


容易发现只有更新一的更新是不会影响 $b$ 序列逆序对个数的，因为值该大的还是大、该小的还是小，因此推出如果位置 $i$ 进行了更新一，这个位置不会对答案产生贡献。因为 $0\le a_i,k\le m-1$，所以 $0\le a_i+k \le 2m-2$，由此惊人地发现更新二的条件 $a_i+k\bmod m=m-1 \Leftrightarrow a_i+k=m-1 \Leftrightarrow a_i=m-1-k$，如果 $b$ 中一个位置 $i$ 发生了更新二，实质上会从一个正整数变成 $0$，显然会使逆序对个数发生变化。

我们思考更新二贡献的答案，只考虑一个位置 $b_i$ 从序列最大值 $m-1$ 变为序列最小值 $0$ 会怎样：

- 原来所有 $i>j$ 的 $j$，都有 $b_i>b_j$，而现在这些顺序对将全部变为逆序对，数量为 $i-1$，对答案的贡献为 $i-1$。

- 原来所有 $i<j$ 的 $j$，都有 $b_i>b_j$，而现在这些逆序对将全部变为顺序对，数量为 $n-i$，对答案的贡献即为 $-(n-i)=i-n$。

因此，一个位置 $i$ 发生更新二时对答案的贡献为 $i-1+i-n=2i-1-n$。

接下来就好办了，我们直接拿 $k=0$ 时初始的逆序对去每次做更新即可（根据上面推导的东西，枚举的应是更新前的 $k$，范围是 $[0,m-2]$），由于只有 $a_i=m-k-1$ 时会发生更新二，所以每次更新加上所有 $a_i=m-k-1$ 的总贡献，即 $\sum_{i:a_i=m-k-1}2i-1-n$，这个东西可以直接预处理。

### 代码

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define int long long
#define ull unsigned long long
#define fst first
#define snd second
#define L(x) x<<1
#define R(x) x<<1|1
#define lowbit(x) x&(-x)
using namespace std;
typedef pair<int,int> pii;
const double eps=1e-6;
inline bool pts(char ch){return ch>=48&&ch<=57;}
inline int read(){
	bool f=0;int x=0;char ch;
	ch=gt();
	while(!pts(ch)&&ch!=EOF){if(ch=='-')f=1;ch=gt();}
	while(pts(ch)){x*=10;x+=(ch-48);ch=gt();}
	if(f)return -x;
	else return x;
}
template<class T>
inline void print(T x){
	char s[114];
	int top=0;
	if(x<0)pt('-');
	do{
		top++;
		if(x>=0)s[top]=(x%10)+48;
		else s[top]=(-(x%10)+48);
		x/=10;
	}while(x);
	while(top){pt(s[top]);top--;}
    pt('\n');
}
const int MAXN=5e5+10;
int n,q,m;
int bit[MAXN];
int a[MAXN],b[MAXN];
int sum[MAXN];
int merge_sort(int l,int r){
	int ans=0;
	if(l==r)return 0;
	int m=(l+r)/2;
	ans+=merge_sort(l,m);
	ans+=merge_sort(m+1,r);
	int pl=l;
	int pr=m+1; 
	for(int i=l;i<=r;i++){
		if(pl>m)b[i]=a[pr],pr++;	
		else if(pr>r)b[i]=a[pl],pl++;
		else if(a[pl]<=a[pr])b[i]=a[pl],pl++;
		else b[i]=a[pr],pr++,ans+=m-pl+1; 
	} 
	for(int i=l;i<=r;i++)a[i]=b[i];
	return ans;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        sum[a[i]]+=(2*i-n-1);
    }
    int tmp=merge_sort(1,n);//k=0时，0<=a_i+k<m，b_i=a_i，直接拿a去算逆序对
    print(tmp);
    for(int k=0;k<m-1;k++){//枚举的一定要是更新前的k
        tmp+=sum[m-1-k];
        print(tmp);
    }
    return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [[ABC396F] Rotated Inversions](https://atcoder.jp/contests/abc396/tasks/abc396_f)

## 题意

给出一个非负整数序列 $A=(A_1,A_2,\cdots,A_n) \pod {0\le A_i\le m}$，对于 $k=0,1,\cdots,m-1$，定义 $B_i=(A_i+k)\bmod m$，求 $(B_1,B_2,\cdots,B_n)$ 的逆序对数。

## 思路

若忽视取模限制，因为每个数的相对大小关系不变，则逆序对数不变，因此我们对于每个 $k$ 只需考虑在加上 $k$ 后变为 $0$ 的 $B_i$ 对逆序对数产生的影响。

我们将 $k=0,1,\cdots,m-1$ 看作 $m-1$ 次操作，每次操作将 $A$ 序列整体加 $1$ 并对 $m$ 取模。

考虑那些在操作前等于 $m-1$ 的 $A_i$。因为 $m-1$ 为 $A$ 的最大值，所以这些数可以跟它们后面所有不等于 $m-1$ 的 $A_j$ 构成逆序对，同时不能跟前面任何一个 $A_j$ 构成逆序对。

但是操作后这些 $A_i$ 都变成了 $0$，因为 $0$ 为 $A$ 的最小值，所以这些数可以跟前面所有不等于 $0$ 的 $A_j$ 构成逆序对，同时不能跟后面任何一个 $A_j$ 构成了逆序对。

于是对于这些 $A_i$，它们的操作会使得整个序列的逆序对数减去原来的贡献并加上现在的贡献。最初的逆序对数可以使用树状数组维护，操作产生的贡献可以动态维护，时间复杂度 $O(n\log n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> b[200005];
int n,m,a[200005],c[200005],ans;
void add(int x,int v){
	x++;
	while(x<=m+1) c[x]+=v,x+=(x&-x);
}
int qu(int x){
	x++;
	int res=0;
	while(x) res+=c[x],x-=(x&-x);
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[a[i]].push_back(i);
	for(int i=n;i>=1;i--)
		add(a[i],1),ans+=qu(a[i]-1);
	for(int i=m;i>=1;i--){
		for(int j=b[i].size()-1;j>=0;j--)
			ans-=n-b[i][j]-((int)(b[i].size())-1-j);
		for(int j=0;j<b[i].size();j++)
			ans+=b[i][j]-1-j;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：

首先求出原序列的逆序对数，然后我们进行如下思考：

对于一个数 $x$，当它进行 $m-x$ 次操作后，它会变为 $0$，此时对于它前面的数，都会产生一个逆序对。

对于它后面的数，显然在 $x$ 增加到 $m-1$ 时，都和 $x$ 组成逆序对，而当它又变为 $0$ 后，对它后面的数而言，它就不与它们构成逆序对了。

同时，由于全局加一，所以本来的逆序对数还会保留，所以我们只需要对于每个数，在它到达 $m$ 时对逆序对答案进行修改即可。

对于相等的数，我们不难发现它们的贡献会相互抵消，所以不用进行特判。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[1000005];
int b[1000005];
int d[1000005];


int ans[1000005];

inline void merge_sort(int l,int r){
	if (l==r){
		return;
	}
	int mid=(l+r)/2;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int i=l;
	int j=mid+1;
	for (int k=l;k<=r;k++){
		if (a[i]<=a[j] && i<=mid || j>r){
			b[k]=a[i];
			i++;
		}
		else{
			ans[0]+=(mid-i+1);
			b[k]=a[j];
			j++;
		}
	}
	for (int i=l;i<=r;i++){
		a[i]=b[i];
	}
}



signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		d[i]=a[i];
	}	
	merge_sort(1,n);
	for (int i=1;i<=n;i++){
		int p=m-d[i];
		ans[p]+=i-1;
		ans[p]-=n-i;
	}
	for (int i=0;i<m;i++){
		cout<<ans[i]<<'\n';
		ans[i+1]+=ans[i];
	}
	
	return 0;
}
```

---

