# 「VUSC」Math Game

## 题目背景

**upd 2023.1.22**：新增一组 Hack 数据 by @[MCRS_lizi](https://www.luogu.com.cn/user/585805)。

远在哞利坚的 Bessie 也要在新春之际走亲访友！为了打发时间，她常和 Farmer John 玩一个有趣的数字游戏。

## 题目描述

Farmer John 有一个集合 $S$，集合初始为 $\{2,3,4,...,N\}$。

对于两个**在集合 $S$ 内的**正整数 $p,q$，我们称它们为「一对好数」当且仅当 $p^k=q(k\ge 2\land k\in\N)$。

我们将每个 $S$ 中的数看成一张**无向图**中的节点，对于每一对「好数」，我们在这两个数间连一条无向边。

Farmer John 会进行 $Q$ 次操作，操作有以下两种：

1. 给出 $x$，询问结点 $x$ 所在的连通块大小。
2. 给出 $x$，从 $S$ 中移除 $x$。**与此同时，无向图中的结点 $x$ 也被移除。**

由于 Bessie 的速度太慢了，她想要你来帮忙。

## 说明/提示

#### 【样例解释】

这是原始无向图（上面一排都是孤点）：
![](https://cdn.luogu.com.cn/upload/image_hosting/utsz04dt.png)

这是进行第一次操作 $2$ 后的无向图（删除了结点 $9$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/wmexc9ks.png)

这是进行第二次操作 $2$ 后的无向图（删除了结点 $2$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9mi0l18p.png)

---

#### 【数据范围】

全部数据满足：
- $2\le N \le 10^{18}$
- $1\le Q \le 10^6$
- $x_i\in S$
- $op_i \in \{1,2\}$

测试点 $1\sim2$ 另外满足 $2\le N \le 10^5$，$1\le Q \le 10^4$。

测试点 $3\sim4$ 另外满足所有 $x_i=m^{p_i}$，其中 $m$ 为一满足 $m\ge 2 \land m\in \N$ 的**常数**。

测试点 $5\sim10$ 没有额外限制。


## 样例 #1

### 输入

```
30 6
1 6
1 4
2 9
1 3
2 2
1 16```

### 输出

```
1
4
2
2```

# 题解

## 作者：enucai (赞：3)

upd 2023.1.25 修改了一处代码错误。

## Analysis

令 $f(x)$ 表示最小的满足 $y^k=x$ 的 $y$ 值。

考虑在没有任何删点操作时，所有 $f(x)$ 值相同的 $x$ 在同一个连通块内。

考虑如果删点后，在询问一个值 $x$ 时，我们可以先找到一个最小的还存在的满足 $y^k=x$ 的 $y$，那么答案就是还存在的 $y^k$ 的数的个数。

如果我们能快速找到 $y$，那么这样的个数是可以暴力统计的，因为所有这样的数只有 $\log n$ 个，我们可以枚举所有这样的数，并对被删除的数用 `set` 记录，每个数在 `set` 查询是否存在即可，单次复杂度是 $O(\log n\log q)$。

考虑如何找这个 $y$。不难发现 $y$ 一定是 $f^k(x)$，所以只要知道 $f(x)$，那么这个 $y$ 也是能快速找到的。

于是考虑如何快速 $f(x)$。设 $f^k(x)=x$，对 $k$ 的大小分类讨论。

- 对于 $k=2$，可以在计算时直接 check $x$ 是否是完全平方数。

- 对于 $k=3$，一种方法是直接计算 $x^{1/3}$，但是这样误差会很大。所以直接预处理出 $[1,10^6]$ 所有数的三次方，然后每次询问 `lower_bound`。

- 对所有 $\ge4$ 的 $k$，由于这样的 $(f(x),x)$ 数对非常少，个数大约是 $\sum\limits_{i\ge 4}\lfloor n^{1/i}\rfloor$，我们可以枚举 $f(x)$，然后用 `map` 记录对于每个 $x$ 的最小的值。

总之，单次求 $f(x)$ 容易做到 $O(\log n)$，且常数很小。

综上，我们在 $O(q\log n\log q)$ 的复杂度内在线完成了这道题，常数很小。注意查询要特判 $x=1$ 的情况。

本题还有离线的并查集解法，此处不再赘述。

## Code

```cpp
const int N = 1000010;
const int V = 1000000;

ll n, val[N];
int q;
set<ll> s;
map<ll, ll> mp;

ll check(ll x) {
  int pos = lower_bound(val + 1, val + V + 1, x) - val;
  if (val[pos] == x) return pos;
  else return -1;
}

ll find(ll x) {
  if (mp.find(x) != mp.end()) return mp[x];
  else if (check(x) != -1) return check(x);
  else if ((ll)sqrtl(x) * (ll)sqrtl(x) == x) return sqrtl(x);
  else return x;
}

int calc(ll x, ll y) {
  int res = 0;
  while (x != 1) res++, x /= y;
  return res;
}

int main() {
  n = read<ll>(), q = read();
  rep (i, 1, V) val[i] = 1ll * i * i * i;
  rep (i, 2, 32000) {
    ll val = i;
    while (val <= n) {
      if (!mp.count(val)) mp[val] = i;
      if (n / val < i) break;
      val *= i;
    }
  }
  rep (i, 1, q) {
    int op = read();
    ll x = read<ll>();
    if (op == 1) {
      if (x == 1) {
        write(1), pc(10);
        continue;
      }
      map<ll, int> mp;
      ll y = find(x);
      int k = calc(x, y);
      ll tmp = 1;
      rep (i, 1, k) {
        tmp *= y;
        if (k % i == 0 && s.find(tmp) == s.end()) mp[tmp] = 1;
      }
      ll z = x, cur = 1;
      rep (i, 1, k) {
        cur *= y;
        if (k % i == 0 && s.find(cur) == s.end())
          z = min(z, cur);
      }
      y = z;
      while (y <= n) {
        if (s.find(y) == s.end()) mp[y] = 1;
        if (n / y < z) break;
        y *= z;
      }
      write(SZ(mp)), pc(10);
    } else {
      s.insert(x);
    }
  }
}
```

---

## 作者：STUDENT00 (赞：2)

昨日闲志恰遇斯，手飞盘上力成之。只惜小儿才能鄙，无分悲涕见正解。恍然之明如红日，故欲撰文告众人。

所阅题解讲得有些不明，故写一篇详细的造福后人。

# 1.前置芝士

并查集

# 2.发掘思路

初看题目时，相信大家都会想到利用并查集维护连通图。但是马上诧异地看到了两个问题：

一、$N \le 10^{18}$，$O(N)$ 的空间复杂度明显超限。

二、对于删点操作，更新其连通块需要 $O(siz)$ 的复杂度，其中 $siz$ 表示连通块的大小，时间复杂度明显超限。

对于一，或许大家会想到使用 STL map。但是，map 的时间复杂度是 $O(logn)$ 级的，又带有极大的常数 $C$，所以会严重超时！这时，我们的离散化就出场了，具体做法如下：

首先，我们将这 $Q$ 次询问的每个数字 $x$ 表示成 $p^q$ 的形式（ $p,q$ 为正整数，且 $p$ 尽量小），然后对于这 $Q$ 个 $p$，进行离散化处理，使得每个 $p$ 都对应一个编号 $id$ 。接着，我们使用一个二维数组 $fa_{i,j}$ 代替原本的 一维数组 $fa_i$。 $fa_{i,j}$ 中的 $i=id,j=q$，完美地规避了时间、空间双重问题。

对于二，我们可以使用“时间倒流”的方式更新。即预处理出经过 $Q$ 次操作后的图，然后将每次移除节点 $x$ 操作，转化为加入点 $x$ 操作。加点的具体做法如下：

设我们如今要连一条 $p^x-p^y$ 的边，那么 $y$ 可分为两类：一是 $y<x$，二是 $y>x$；经过简单分析，我们发现这二类的 $y$ 分别需且仅需满足以下要求：一需 $y|x$，二需 $x|y$。

目前为止，我们已经基本掌握了解题要点。接下来，是进一步的细节与深入。

# 3.总结与细节

总结：对于本题，我们首先需要想到 BIGSTAR 并查集。在解决数据范围问题上，不能将自己死锁在 STL map 的范围内，而应灵活运用离散化，既解决了空间问题，又不造成时间上的浪费；在解决删点问题上，不能将自己的思维死锁在正向解决范围内，而应灵活运用预处理+逆向解题，使得时间复杂度得到巨大的提升。

好了，接下来让我们一起查看几个代码中较易出错或难理解的地方：

一、变量名

```cpp
ll n,x[N],num[N];
int q,op[N],ans[N],tot,tott;
set<ll> del; 
map<ll,pair<ll,int> > indx; 
vector<int> fa[N],siz[N];
```

$num$ 是离散化数组，$ans$ 是暂存答案的（因为时间是倒流的），$tot$ 是离散化后的 $id$ 个数，$tott$ 是答案的个数，$del$ 存储被删点（在时间倒流的过程中，元素个数逐渐减少），$indx_i$ 所对应的 $value$ 值二元组 $(p,q)$，详见“发掘思路”中问题一的具体解决方案，$fa,siz$ 亦详见之。

二、预处理 $x=p^q$

这是“发掘思路”中问题一离散化的基础，但是具体如何实现？显然，枚举每个 $x$，然后枚举 $q$，使用 $p=x^{\frac{1}{q}}$ 并判断 $p$ 是否为整数会超时。再细思，$q>1$ 的 $p$ 有 $10^9$ 个，无法做预处理。但更进一步地， $q>2$ 的 $p$ 只有 $10^6$ 个，预处理的时间复杂度完全够。那么对于 $q=2$ 者，可针对 $x$ 进行比 `sqrt` 精度更高的 `sqrtl` 处理，具体代码实现如下：

```cpp
for(int i=2;(ll)i*i*i<=n;i++){
	lll tmp=i;
	for(int j=1;tmp<=n;j++){
		if(indx.find(tmp)!=indx.end()&&indx[tmp].first==tmp) indx[tmp]=make_pair(i,j);
		tmp*=i;
	}
}
for(auto i:indx){
	if((lll)i.first*i.first*i.first<=n) continue;
	ll x=sqrtl(i.first);
	if(x*x==i.first) i.second=make_pair(x,2);
}
```

三、预处理并查集

或许有人会想当然，对于任意 $id$，将所有 $del$ 中所不含之数具皆为一集。但这是错误的，因为 $p$ 可能也被 $del$ 包含，这样所有 $p^q$ 的数之根基 $p$ 就断了。故需枚举每个 $p^q$ （不被 $del$ 包含者）为“根基”，利用 unnion 操作预处理，具体代码实现如下：

```cpp
for(int i=1;i<=tot;i++){
	int cnt=logl(n)/logl(num[i]);
	fa[i].resize(cnt+1);siz[i].resize(cnt+1);
	for(int j=1;j<=cnt;j++) fa[i][j]=j,siz[i][j]=1;
	ll tmp=1;
	for(int j=1;j<=cnt/2;j++){
		tmp*=num[i];
		if(del.count(tmp)) continue;
		ll cur=tmp;
		for(int k=2;k<=cnt/j;k++){
			cur*=tmp;
			if(del.count(cur)) continue;
			unnion(i,j,j*k);
		}
	}
}
```

讲了这么多，相信各位都甚为明了了。最后的代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
typedef __int128 lll;
ll n,x[N],num[N];
int q,op[N],ans[N],tot,tott;
set<ll> del; 
map<ll,pair<ll,int> > indx; 
vector<int> fa[N],siz[N];
int find(int id,int x){
	if(fa[id][x]==x) return x;
	return fa[id][x]=find(id,fa[id][x]);
}
void unnion(int id,int x,int y){
	x=find(id,x);y=find(id,y);
	if(x==y) return;
	fa[id][y]=x;siz[id][x]+=siz[id][y];
}
//并查集的查找祖宗与合并操作 
void init(){
	for(int i=2;(ll)i*i*i<=n;i++){
		lll tmp=i;
		for(int j=1;tmp<=n;j++){
			if(indx.find(tmp)!=indx.end()&&indx[tmp].first==tmp) indx[tmp]=make_pair(i,j);
			tmp*=i;
		}
	}
	for(auto i:indx){
		if((lll)i.first*i.first*i.first<=n) continue;
		ll x=sqrtl(i.first);
		if(x*x==i.first) i.second=make_pair(x,2);
	}
	//预处理出每个数的p^q形式（p,q为整数），p最小
	for(auto i:indx) num[++tot]=i.second.first;
	sort(num+1,num+tot+1);
	tot=unique(num+1,num+tot+1)-num-1;
	for(int i=1;i<=tot;i++){
		int cnt=logl(n)/logl(num[i]);
		fa[i].resize(cnt+1);siz[i].resize(cnt+1);
		for(int j=1;j<=cnt;j++) fa[i][j]=j,siz[i][j]=1;
		ll tmp=1;
		for(int j=1;j<=cnt/2;j++){
			tmp*=num[i];
			if(del.count(tmp)) continue;
			ll cur=tmp;
			for(int k=2;k<=cnt/j;k++){
				cur*=tmp;
				if(del.count(cur)) continue;
				unnion(i,j,j*k);
			}
		}
	}
	//预处理并查集 
}
void calc(){
	for(int i=q;i>=1;i--){
		ll base=indx[x[i]].first;
        int power=indx[x[i]].second,id=lower_bound(num+1,num+tot+1,base)-num;
		if(op[i]==1){ans[++tott]=siz[id][find(id,power)];continue;} //查询操作
		del.erase(x[i]);
		int cnt=logl(n)/logl(base);
		ll tmp=1;
		for(int j=1;j<=cnt/power;j++){
			tmp*=x[i];
			if(del.count(tmp)) continue;
			unnion(id,power,power*j);
		}
        //倍数
		tmp=1;
		for(int j=1;j<=power;j++){
			tmp*=base;
			if(del.count(tmp)) continue;
			if(power%j==0) unnion(id,j,power);
		}
        //因数
	}
}
int main(){
	scanf("%lld%d",&n,&q);
	for(int i=1;i<=q;i++){
		scanf("%d%lld",&op[i],&x[i]);
		if(op[i]==2) del.insert(x[i]);
		indx[x[i]]=make_pair(x[i],1);
	}
	init();
	calc();
	for(int i=tott;i>=1;i--) printf("%d\n",ans[i]);
	return 0;
}
```

P.S. 对于运算速度有：`int`<`long long`<`int128`，`array`<`vector`<`set`<`map` （ `array` 指普通数组）。故在解题过程中，也应按此规则行事，避免时间上的浪费。

P.S.S. 鄙人虽已尽了最大的努力减小时间复杂度，但终归还是要开 O2 方过。

At the last，欢迎各位大佬对鄙人的题解进行质疑与吐槽！



---

## 作者：Moeebius (赞：1)

## Preface
来一发出题人题解！
## Analysis
首先，令 $f(x)$ 为满足 $y^p=x\ (\text{其中}\ p\in \mathbb{N} )$ 的**最小**的 $y$。

显然地，我们可以用 $f(x)$ 来离散化 $O(N)$ 的巨大值域。

由于操作次数不超过 $10^6$，涉及到的 $f(x)$ 也不超过 $10^6$ 个。对于每个涉及到的 $f(x)$，我们维护一个并查集，并且使用「时间倒流」的方法维护删边（倒序加边）。

怎么快捷地求出 $f(x)$ 呢？

- 对于 $p=2$ 的情况，我们直接开根号，~~也许~~需要 ```sqrtl``` 来避免精度误差，也可以通过 $\pm1$ 来微调。

- 对于 $p>2$ 的情况，我们离线所有询问，并且在 $[2,10^6]$ 的值域中暴力查询+预处理。

初始时，我们将所有未被删除的点之间连边。

每次遇到一个删除（即倒序插入）操作，我们连以下两类边：

- $x\leftrightarrow f(x)^q\ (\text{其中}\ q\mid p \land q\ge 2)$
- $x\leftrightarrow f(x)^q\ (\text{其中}\ p\mid q \land f(x)^q\le 10^{18})$

遇到询问操作即查询并查集的 ```sz```。

实现细节有点多，尤其是使用 ```vector``` 造成的 0-index 和 1-index 之间的转换。

复杂度约为 $O(Q \log N+Q\log^2 N)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define il inline
#define mkp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define lll __int128
#define ll long long
#define For(i,j,k) for(int i=(j); i<=(k); ++i)
#define ForDown(i,j,k) for(int i=(j); i>=(k); --i)
#define pb push_back
#define FileIO(filename) freopen(filename ".in" ,"r",stdin);freopen(filename ".out" ,"w",stdout)
template<typename T> 
il void read(T &x){ x=0;int f=1;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}while(isdigit(c)){x=x*10+c-'0';c=getchar();}x*=f;}
template<typename T, typename ... Args>
il void read(T &x, Args &... y){ read(x);read(y...); }
// File head end

const int MAXN=1e6;
const lll MAXV=1e18;
ll n,q;
vector<int> f[MAXN+5],sz[MAXN+5];
vector<ll> num,ans;
vector<pair<int,ll>> oper;
map<ll,pair<ll,ll>> pool;
map<ll,bool> vis;

il int find(int id, int x) // 并查集查询父亲
{
    return f[id][x]==x ? f[id][x] : f[id][x]=find(id,f[id][x]);
}
il void uni(int id, int x, int y) // 合并集合
{
    int u=find(id,x),v=find(id,y);
    if(u==v) return;
    f[id][u]=v; sz[id][v]+=sz[id][u]; 
}
il void prework()
{
    For(i,2,min(MAXN,(int)sqrt(n))) // 预处理三次方以上
    {
        lll tmp=i;
        For(j,2,64)
        {
            tmp*=i;
            if(tmp>n) break;
            if(pool.find(tmp)!=pool.end() && pool[tmp].first==tmp) pool[tmp]=mkp(i,j);
        }
    }
    for(auto i: pool) // 预处理二次方
    {
        if(i.second.first==-1)
        {
            ll tmp=sqrtl(i.first);
            For(j,-1,1)
            {
                if((tmp+j)*(tmp+j)==i.first)
                {
                    i.second=mkp(tmp+j,2);
                }
            }
        }
    }
    for(auto i: pool) num.pb(i.second.first);
    sort(num.begin(),num.end());
    num.erase(unique(num.begin(),num.end()),num.end()); // 离散化
    int len=num.size();
    For(i,0,len-1)
    {
        int cnt=logl(n)/logl(num[i]);
        f[i+1].resize(cnt+1),sz[i+1].resize(cnt+1); // 预处理并查集
        For(j,1,cnt) f[i+1][j]=j,sz[i+1][j]=1;
        lll tmp=1;
        For(j,1,cnt/2) // 暴力连没有被删点的边
        {
            tmp*=num[i];
            if(vis[tmp]) continue;
            lll cur=tmp;
            For(k,2,cnt/j)
            {
                cur*=tmp;
                if(vis[cur]) continue;
                uni(i+1,j,j*k);
            }
        }
    }
}

il void calc()
{
    int len=oper.size();
    ForDown(i,len-1,0) // 时间倒流
    {
        auto cur=oper[i];
        int id=lower_bound(num.begin(),num.end(),pool[cur.second].first)-num.begin()+1,power=pool[cur.second].second; // 查询离散化后的编号
        if(cur.first==1)
        {
            // p = 1
            ans.pb(sz[id][find(id,power)]);
        }
        else
        {
            int cnt=logl(n)/logl(cur.second);
            lll qwq=cur.second; vis[qwq]=0;
            For(j,2,cnt/power) // 往后连边
            {
                qwq*=cur.second;
                if(vis[qwq]) continue;
                uni(id,power,power*j);
            }
            qwq=1;
            For(j,1,power) // 往前连边
            {
                qwq*=num[id-1];
                if(power%j==0 && !vis[qwq]) uni(id,j,power);
            }
        }
    }
    reverse(ans.begin(),ans.end());
}

signed main()
{
    read(n,q);
    For(i,1,q) // 离线询问
    {
        ll op,x;
        read(op,x);
        oper.pb(mkp(op,x));
        pool[x]=mkp(x,1);
        if(op==2) vis[x]=1; // 标记删点
    }
    prework(); // 预处理
    calc(); // 计算
    for(ll x: ans) printf("%lld\n",x);
	return 0;
}
```

---

## 作者：xieziheng (赞：1)

感觉这题也就黄。

首先发现不考虑删除时，只有 $\{a^b | a \geq 2,b \geq 1\}$ 会形成一个连通块。将形如 $a^k$ 的数称为 $k$ 次方数。若 $x$ 是一个 $k$ 次方数，设 $x=a^k$，则对于 $b|k$，显然与 $x$ 直接相连的点都直接与 $a^b$ 相连。即，$x$ 所能到达的点为所有未被删除的 $a^{b_i}(i\in [1,n])$ 所能到达的未被删除点的并集（$b_i | k,i\in [1,n]$）。否则，$x$ 所能到达的点即为所有未被删除的 $x^i(i\in [1,n],x^n \leq 10^{18},x^{n+1}>10^{18}$)。

怎么判断 $x$ 是否是一个 $k$ 次方数呢？直接令 $y=x^{\frac 1 k}$，看 $y^k$ 是否等于 $x$。为了避免误差,可以判断 $y-1,y,y+1$ 的 $k$ 次方是否是 $x$。

于是做法就很简单了：开两个 map，一个记录一个数是否被删除，另一个存能到达的点。枚举 $k \in [2, \log(n)]$ ，若 $x$ 是 $k$ 次方数且 $x$ 开 $k$ 次方没被删除，就记录下来。若 $x$ 不是 $k$ 次方数，就直接枚举其指数即可。

代码：

```cpp
#include <bits/stdc++.h>
#define il inline
#define B __int128
using namespace std;
typedef long long ll;
il int read() {
	int x=0,c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x;
}
il B read1() {
	B x=0,c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*B(10)+c-B(48),c=getchar();
	return x;
}
void write(int x) {
	if(x>9) write(x/10);
	putchar(x%10+48);
}
il void print(int x,char c) {
	write(x),putchar(c);
}
const B inf=1e18;
B n;
int q;
map<B,bool> mp,tmp;
il int getlg(B x) {
	B a=1;
	int s=0;
	while(a<=x) a<<=1,++s;
	return s;
}
il B pw(B a,int b) {
	B base=a,ans=1ll;
	while(b) {
		if(b&1) ans=ans*base;
		base=base*base;
		b>>=1;
		if(ans>n) return -1;
	}
	return ans>n?-1:ans;
}
il B sqr(B x,int k) {
	B y=B(pow(x*1.0,1.0/k));
	for(B i=y-1; i<=y+1; ++i) if(pw(i,k)==x && !mp.count(i)) return i;
	return 0;
}
int ans,k;
int opt;
B x,y,z,a;
int main() {
	n=read1(),q=read();
	while(q--) {
		opt=read(),x=read1();
		if(opt==1) {
			ans=0,k=getlg(x),tmp.clear();
			y=z=x;
			while(z<=n) {
				if(!mp.count(z) && z>0) tmp[z]=1;
				z*=y;
			}
			for(int i=2; i<=k; ++i) {
				a=sqr(x,i);
				if(a>0) {
					y=z=a;
					while(z<=n) {
						if(!mp.count(z) && z>0) tmp[z]=1;
						z*=y;
					}
				}
			}
			print(tmp.size(),'\n');
		} else mp[x]=1;
	}
	return 0;
}
```

---

## 作者：MCRS_lizi (赞：1)

**upd：更改代码并修改相关描述，源代码无法通过自己造的 hack 数据。**

难得比赛可以 A 掉这种级别的题目，当然要冲一发题解啦。

## 题目大意
初始有一个为 $[2,3,4\cdots N]$ 的数列，任意两个数 $p,q$ 之间会连接一条边当且仅当存在一个大于等于 $2$ 的正整数 $k$，满足 $p^k=q$ 或者 $q^k=p$。现在会形成一张无向图，现在要求维护以下 $Q$ 次操作：

1. 删除一个结点；
2. 询问一个结点所在连通块大小。

数据范围：$N\le 10^{18},Q\le 10^6$。

## 思路简述
暴力建边肯定不可取的，这种级别的数据范围只能考虑 $\log$ 级别的做法。当然时间限制也比较充裕，毕竟这题我的做法不优化的话，吸氧要跑 4s 多。

首先考虑初始没有删除任何点的状态，询问 $x$ 所在连通块大小的话，无非就这三种情况：

1. 存在一个在 $[2,N]$ 以内的正整数 $a$，使得 $x^{k_1}=a$，那么 $a$ 在连通块中；
2. 存在一个在 $[2,N]$ 以内的正整数 $b$，使得 $b^{k_2}=x$，那么 $b$ 在连通块中；
3. 存在一个在 $[2,N]$ 以内的正整数 $c$，使得对于情况 $2$ 中的 $b$，$b^{k_3}=c$，那么 $c$ 在连通块中。

不难发现，我们无需讨论情况 $1$，因为针对情况 $2$ 中的 $b^{k_2}=x$，那么我们可推出 ${b^{k_2}}^{k_1}=a$，这样的话这种情况可以直接归入情况 $3$ 中。

并且，我们如果令情况 $2$ 中的 $b$ 足够小，那么其他情况都可以归入情况 $3$ 中，举个例子，我们在找 $16$ 的连通块时，一定是先找到最小的 $2$，然后其他部分都可以用 $2^k$ 来进行表示。

那么我们就有思路了，只需要将一个数开方开到最小，然后在向上乘看看最多可以乘到几次就行。

接下来再考虑删过点的情况，如果那个最小的 $b$ 已经被删了就往上找找到**每一个**没被删除的并且满足与原数连边的，执行相同操作即可。这里注意，每一个值虽然比较麻烦，但对时间复杂度不会产生过多影响，可以优化但不优化也可以过，就是比较慢。

注意一下向上找的时候遇到删掉的直接跳过即可。

## 代码实现

我们核心无非是实现开方的操作，开方其实很简单，配合快速幂进行二分就行了，详情见注释，不多赘述。

删点可以用 $\text{map}$ 标记，也很简单。

向上跳的时候细节要稍稍注意一下，为了时间快一点会提前预处理 $10^6$ 范围内开方的最小值。

时间复杂度 $O(Q\log^2N)$，有点大，但是时限也大加上吸氧卡卡常单侧试点跑进 3s 还是没问题的，毕竟这个值也跑不满。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long//反正全是 long long 那就直接快点吧
//#define __int128 long long
using namespace std;
map<int,int> used,can;//标记是否删除
const int N=1000020;
int n,q,low[N],lq[N];//low[i] 表示数 i 最小可以开方开到 low[i]
inline void init()
{
    register int m=N-10;
    for(register int i=2;i<=m;i++)//用类似筛法的方式进行预处理
    {
        register int x=i;
        while(x<=m)
        {
            if(!low[x])
            {
                low[x]=i;//处理 low 数组
            }
            x*=i;
        }
    }
}
inline __int128 power(register int x,register int y)//快速幂，使用 __int128 是怕二分的时候炸掉，但好像不会
{
    register int res=1;
    while(y)
    {
        if(y&1)
        {
            res=res*x;
        }
        x=x*x;
        y>>=1;
    }
    return res;
}
inline int query(register int x,register int k)//求出 x 开 k 次方向下取整的结果
{
    __int128 l=1,r=pow(n,1.0/k)+10,mid;//压一下上边界，节约时间且防止炸 __int128 
    register int res;
    if(k==1)
    {
        return x;
    }
    while(l<=r)//二分查找这个开方后的值
    {
        mid=(l+r)>>1;
        if(power(mid,k)<=x)
        {
            l=mid+1;
            res=mid;
        }
        else
        {
            r=mid-1;
        }
    }
    return res;
}
inline bool check(register int x,register int y)//检查是否存在正整数 k 使得 x 的 k 次方等于 y
{
    if(x==1)
    {
        return y==1;
    }
    __int128 l=x;//这里不用 __int128 容易出事故
    while(l<y)
    {
        l*=x;
    }
    return l==y;
}
inline void write(register int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline int read()
{
    char ch;
    register int s=0,x=1;
    ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')x=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
   {
        s=(s<<3)+(s<<1)+(ch^48);
        ch=getchar();
    }
    return s*x;
}//搬来的快读快写板子
signed main()
{
    n=read(),q=read();
    init();
    int m=N-10;
    while(q--)
    {
        register int op,x,e=1,f=0,ans=0;
        op=read(),x=read();
        if(op==1)
        {
            register int num=x;
            register int l=x;
            if(x>m)
            {//这里执行双向查找是为了省时间
                for(register int i=2;i<=50;i++)//先从开方结果进行枚举
                {
                    if(check(i,num))
                    {
                        l=x=i;
                        break;
                    }
                }
                if(x==num)//没有结果的话枚举开方次数
                {
                    for(register int i=12;i;i--)
                    {
                        int res=query(num,i);
                        if(power(res,i)==num)
                        {
                            l=x=res;
                            break;
                        }
                    }
                }
       //    l=x=low[x];
            }
            else
            {
                l=x=low[x];//直接取预处理结果
            }
            if(used[l])
            {
                while(1)//被删了就向上跳
                {
                    l*=x;
                    if(!used[l]&&check(l,num))//找到满足的了
                    {
                        lq[++f]=l;
                    }
                    if(l>=num)
                    {
                    	break;
					}
                }
            }
            else
            {
            	lq[++f]=l;
			}
			while(e<=f)
			{
				l=lq[e++];
	            register __int128 y=l;//防止乘的时候炸掉
	            while(y<=n)//向上查找
	            {
	                if(!used[(int)y]&&!can[y])//没删掉
	                {
	                    ans++;
	                    can[y]=1;
	                }
	                y*=l;
	            }
	        }
	        write(ans);
	        putchar('\n');
	        e=1;
	        while(e<=f)
			{
				l=lq[e++];
	            register __int128 y=l;//防止乘的时候炸掉
	            while(y<=n)//向上查找
	            {
	                if(!used[(int)y])//没删掉
	                {
	                    can[y]=0;
	                }
	                y*=l;
	            }
	        }
        }
        else
        {
            used[x]=1;//直接打标记表示删除了，不用过多处理
        }
    }
    return 0;
}//应该没人会去复制我这个蒟蒻的题解ba
```



---

