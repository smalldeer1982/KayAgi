# Ant colony

## 题目描述

Mole is hungry again. He found one ant colony, consisting of $ n $ ants, ordered in a row. Each ant $ i $ ( $ 1<=i<=n $ ) has a strength $ s_{i} $ .

In order to make his dinner more interesting, Mole organizes a version of «Hunger Games» for the ants. He chooses two numbers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) and each pair of ants with indices between $ l $ and $ r $ (inclusively) will fight. When two ants $ i $ and $ j $ fight, ant $ i $ gets one battle point only if $ s_{i} $ divides $ s_{j} $ (also, ant $ j $ gets one battle point only if $ s_{j} $ divides $ s_{i} $ ).

After all fights have been finished, Mole makes the ranking. An ant $ i $ , with $ v_{i} $ battle points obtained, is going to be freed only if $ v_{i}=r-l $ , or in other words only if it took a point in every fight it participated. After that, Mole eats the rest of the ants. Note that there can be many ants freed or even none.

In order to choose the best sequence, Mole gives you $ t $ segments $ [l_{i},r_{i}] $ and asks for each of them how many ants is he going to eat if those ants fight.

## 说明/提示

In the first test battle points for each ant are $v = [4, 0, 2, 0, 2]$, so ant number $1$ is freed. Mole eats the ants $2, 3, 4, 5$.

In the second test case battle points are $v = [0, 2, 0, 2]$, so no ant is freed and all of them are eaten by Mole.

In the third test case battle points are $v = [2, 0, 2]$, so ants number $3$ and $5$ are freed. Mole eats only the ant $4$.

In the fourth test case battle points are $v = [0, 1]$, so ant number $5$ is freed. Mole eats the ant $4$.

## 样例 #1

### 输入

```
5
1 3 2 4 2
4
1 5
2 5
3 5
4 5
```

### 输出

```
4
4
1
1
```

# 题解

## 作者：培淇2021 (赞：16)

题解区线段树刷屏/fad

所以我要写的是使用 st+二分，萌新都能轻松看懂的题解/kel

- 前置知识

st 表，stl 库函数

- 题目分析

首先看到题目，我们发现得到满分等价于同时是所有数的因子。

题解区都说显然是当且仅当这个数是区间 $\gcd$ 才得到满分/fad

对于我这种 MnZn 很不友好，所以我要稍微证一下

如果我们把区间划分成两部分：

一部分是我们验证是否为满分的这个数；

另外一部分是其他所有数。

我们设其他数的 $\gcd$ 为 $u$，这个数为 $v$，假设 $v$ 是区间 $\gcd$。

因为 $\gcd$ 有结合律，当且仅当 $\gcd(u,v)=v$ 时 $v$ 是满分，此时区间 $\gcd$ 为 $\gcd(u,v)$，此时 $v$ 是 $u$ 的因子。

但是，如果我们把**此时的** $v$ 调成**刚才的**区间 $\gcd$ 的因子，那么区间的 $\gcd$ 也会跟着变为 $v$，此时依然成立：$v$ 是区间 $\gcd$。

所以，我们得出，一个数得到满分等价于它是区间 $\gcd$。

这道题就等价于：给定一个数列，多次询问区间内有多少个数**不是**区间 $\gcd$。

而区间 $\gcd$，由于它的可覆盖性，可以直接用 st 表维护。

我们正难则反，加强问题，就得到了新的题目：

给定一个数列，多次询问区间内有多少个数与给定数相同。

而我们知道，区间的 $\gcd$ 有一个特点：它小于等于区间的任何一个数。

所以问题又又又转化为区间最小值出现的次数。

接下来，就是另一道题了。

- 细节解析

我们输入后，除了做区间 $\gcd$ 的 st 表，我们要再用另一个各个元素与原来的数组元素相同的数组，排序去重后我们用一个 `vector` 数组和一个 `map`。

下面把第一个数组叫做旧数组，第二个数组叫做新数组。

`vector` 是从新数组推到旧数组，用来**顺序**存储每一个在新数组的指定**位置**对应的旧数组的所有元素下标，而 `map` 是由旧数组推到新数组，用来存储每一个旧数组的**元素值**对应的新数组的元素下标。

对每一组询问，先求出这个区间的 $\gcd$，然后通过 `map` 求出下标。

由于 `vector` 数组是新数组下标推向旧数组下标，所以对这个下标，我们放到对应的 `vector` 里，接下来我们求的，是这个数组中范围在 `l~r` 的数的个数。

通过前缀和的思想，只要求 `1~r` 的数的个数减去 `1~l-1` 的数的个数即可。

而这两个值我们都可以用 `vector` 中的 `upper_bound` 来实现。

到此，我们终于，做完了本题。

- 详解代码

变量定义：

```cpp
int n,t,l,r/*输入*/,a[100005]/*新数组*/,f[100005][32]/*st 表的数组*/;
vector<int> e[100005];//vector 数组
map<int,int> b;//map
```

预处理：

```cpp
cin>>n;
for(int i=1;i<=n;i++)
{
    cin>>f[i][0];//这里直接输入成 st 表了（旧数组）
    a[i]=f[i][0];//这是新数组
}
sort(a+1,a+n+1);//排序
int l=unique(a+1,a+n+1)-a-1;//去重
for(int i=1;i<=n;i++)
{
	int poi=lower_bound(a+1,a+1+l,f[i][0])-a;//找对应位置
	e[poi].push_back(i),//这个是顺序排的，下面才能二分
   b[f[i][0]]=poi;//设置位置
}
//下面是 st 表
for(int j=1;(1<<j)<=n;j++)
    for(int i=1;i+(1<<j)-1<=n;j++)
        f[i][j]=__gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
```

对于每一组询问：

```cpp
cin>>l>>r;
int len=r-l+1,//区间的长度
k=(int)log2(len);
int poi=b[__gcd(f[l][k],f[r-(1<<k)+1][k])];//区间 gcd 对应的原数组位置
int lef=upper_bound(e[poi].begin(),e[poi].end(),l-1)-e[poi].begin();//左端点
int rig=upper_bound(e[poi].begin(),e[poi].end(),r)-e[poi].begin();//右端点
int cnt=rig-lef;//区间内都是
cout<<len-cnt;
```

加了两个不影响代码原意的小彩蛋/cy

写题解很慢，球球点个赞/kel

---

## 作者：lzyqwq (赞：8)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17367131.html)**

# $\texttt{Description}$

**[CF474F](https://codeforces.com/problemset/problem/474/F "CF474F")**

**[洛谷 CF474F](https://www.luogu.com.cn/problem/CF474F "洛谷 CF474F")**

> - 给定 $a_1\sim a_n$ 和 $q$ 组询问，每次询问 $a_l\sim a_r$ 之间，不能整除区间内所有数的数的个数。
>
> - $n,q\le 10^5$，$a_i\le 10^9$。

# $\texttt{Solution}$

首先补集转化为**能整除区间内所有数的数的个数**。考虑怎样的数满足性质。

如果一个数 $x$ **不在区间内**并且能整除区间内的所有数，说明 $x|\gcd\limits_{i=l}^ra_i$。现在这个数在区间内，说明它既是 $\gcd$ 的倍数，又是 $\gcd$ 的约数，显然 $x=\gcd\limits_{i=l}^ra_i$。问题转化为求区间内 $\gcd$ 的个数。用 **ST 表**维护 $\gcd$，用**树状数组套 `unordered_map`** 维护区间内某个数的个数。

时间复杂度为 $\mathcal{O}(n\log^2n)$，空间复杂度为 $\mathcal{O}(n\log n)$，可以接受。

# $\texttt{Code}$

**[Submission](https://codeforces.com/contest/474/submission/204122778 "Submission")**


```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,g[20][N],lg[N];
unordered_map<int,int>bit[N];
int gcd(int l,int r){
	int k=lg[r-l+1];
	return __gcd(g[k][l],g[k][r-(1<<k)+1]);
}
void modify(int x,int k){
	for(int i=x;i<=n;i+=i&(-i)){
		++bit[i][k];
	}
}
int query(int x,int k){
	int ret=0;
	for(int i=x;i;i-=i&(-i)){
		if(bit[i].find(k)!=bit[i].end()){
			ret+=bit[i][k];
		}
	}
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		lg[i]=log2(i);
		scanf("%d",&g[0][i]);
		modify(i,g[0][i]);
	}
	for(int i=1;i<=lg[n];++i){
		for(int j=1;j+(1<<i)-1<=n;++j){
			g[i][j]=__gcd(g[i-1][j],g[i-1][j+(1<<(i-1))]);
		}
	}
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;++i){
		scanf("%d%d",&l,&r);
		printf("%d\n",r-l+1-(query(r,gcd(l,r))-query(l-1,gcd(l,r))));
	}
}
```

---

## 作者：YCS_GG (赞：6)

### 题意

给出一个数组$s_i$，有$q$个询问，每个询问给出一个区间$[l,r]$，问$[l,r]$里有多少个数能整除其他数

### Solution

显然题目问的就是$[l,r]$内$gcd(s_{l},s_{l+1},\cdots,s_{r})$的个数。

而在$[l,r]$内,$gcd(s_{l},s_{l+1},\cdots,s_{r})=gcd(gcd(s_{l},s_{l+1},\cdots,s_k),gcd(s_{k+1},s_{k+2},\cdots,s_r))$
可以看出是满足区间加法的,于是我们考虑用线段树搞

区间$gcd$的个数直接记录在区间内，合并也直接合并，套上线段树板子即可

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;//
int n,m;
int val[200002*4],l[200002*4],r[200002*4],num[200002*4],a[200002];
int gcd(int a,int b){
	return __gcd(a,b);
}
void build(int left,int right,int rt){
	l[rt]=left;
	r[rt]=right;
	if(left==right){
		val[rt]=a[left];
		num[rt]=1;
		return ;
	}
	build(left,(left+right)/2,rt*2);
	build((left+right)/2+1,right,rt*2+1);
	val[rt]=gcd(val[rt*2],val[rt*2+1]);
	num[rt]=(val[rt]==val[rt*2]?num[rt*2]:0)+(val[rt]==val[rt*2+1]?num[rt*2+1]:0);
}
int getGcd(int rt,int left,int right){
	if(l[rt]>=left&&r[rt]<=right)
		return val[rt];
	if(right<=(l[rt]+r[rt])/2)
		return getGcd(rt*2,left,right);
	else if(left>(l[rt]+r[rt])/2)
		return getGcd(rt*2+1,left,right);
	else
		return gcd(getGcd(rt*2,left,right),getGcd(rt*2+1,left,right));
}
int query(int rt,int left,int right,int t){
	if(l[rt]>=left&&r[rt]<=right)
		return val[rt]==t?num[rt]:0;
	if(right<=(l[rt]+r[rt])/2)
		return query(rt*2,left,right,t);
	else if(left>(l[rt]+r[rt])/2)
		return query(rt*2+1,left,right,t);
	else
		return query(rt*2,left,right,t)+query(rt*2+1,left,right,t);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,n,1);
	cin>>m;
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		cout<<r-l-query(1,l,r,getGcd(1,l,r))+1<<endl;
	}
}
```

---

## 作者：Leap_Frog (赞：6)

### P.S.
@[serverkiller](https://www.luogu.com.cn/user/68030 "口胡带师") 提出了一个序列分块套值域分块的做法，详情请询问本人。  
这篇题解主要做法是线段树，与其他题解思路略有不同。  

### Description.
给定一个序列，支持多次区间询问。  
对于区间中的两个数 $a,b$，若存在 $b\ |\ a$，则给 $b$ 加一分。  
每次询问 $[L,R]$ 中有多少个得了 $R-L+1$ 分。（满分  

### Solution.
我们对每个区间中满分的数，观察一下它的性质。  
因为它满分了，所以它肯定是区间内每个数的公约数。  
根据最大公约数的性质可得，公约数肯定是最大公约数的因数。  
所以对于每次询问，其中所有满分的数肯定是所有数的最大公约数的因数。  
因为满分的数是属于这个区间的，而且 $\gcd(a,b)\le a$。  
所以我们能发现所有满分的数肯定满足它等于区间 $\gcd$，同时它还是区间最小值。  
所以我们直接用一个线段树维护区间 $gcd$，以及区间等于最小数的数的个数。  
具体见代码。  

### Code.
```cpp
//嗯，那样的话，你就再努力一次试试吧！别在这种地方畏畏缩缩的！别对自己说谎！再努力一次吧。
//我说过了，若是有想要拯救之物，就果断地出手全力去守护!
//拜托了，请把力量借给软弱的我，给我从这里再度起身迈步的力量！
#include<bits/stdc++.h>
using namespace std;
struct node{int min,mnn,gcd;}t[400005];//线段树
int n,q,a[100005];//min是区间最小值，mnn是区间等于最小值的数的个数，gcd是区间gcd
inline int gcd(int a,int b) {return b?gcd(b,a%b):a;}//gcd
inline node up(node a,node b)
{//up函数，简单易懂了吧（
	node r;r.min=min(a.min,b.min),r.gcd=gcd(a.gcd,b.gcd);
	r.mnn=(a.min==r.min?a.mnn:0)+(b.min==r.min?b.mnn:0);return r;
}
inline void build(int x,int l,int r)
{//线段树模板，build函数
	if(l==r) t[x].gcd=t[x].min=a[l],t[x].mnn=1;
	else build(x<<1,l,(l+r)>>1),build(x<<1|1,((l+r)>>1)+1,r),t[x]=up(t[x<<1],t[x<<1|1]);
}
inline node query(int x,int l,int r,int dl,int dr)
{//线段树区间查询，模板
	if(l>dr||dl>r) return (node){(int)1e9,0,0};else if(dl<=l&&r<=dr) return t[x];
	return up(query(x<<1,l,(l+r)>>1,dl,dr),query(x<<1|1,((l+r)>>1)+1,r,dl,dr));
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(build(1,1,n),scanf("%d",&q);q--;)
	{
		int l,r;scanf("%d%d",&l,&r);
		node t=query(1,1,n,l,r);//查询结果记录，防止常数爆炸
		// printf("%d , %d : %d\n",t.gcd,t.min,t.mnn);
		printf("%d\n",r-l+1-(t.gcd==t.min?t.mnn:0));//如果区间最小值=区间gcd，那么就减去最小值的数量
	}
	return 0;
}
```
完结撒花。

---

## 作者：xfrvq (赞：5)

[$\tt Link$](/problem/CF474F "CF474F Ant colony")。

我们考虑什么样的数才能满足条件。

首先它得是这个区间所有数的因数，即 $a_i\mid\gcd(a_l,\cdots,a_r)$。

但是我们知道两个数的 $\gcd$ 一定小于等于这两个数，所以 $\gcd(a_l,\cdots,a_r)\le\min(a_l,\cdots,a_r)\le a_i$。

所以 $a_i=\gcd(a_l,\cdots,a_r)$。

然后就是区间一个数的出现次数。

可以值域 `vector` 存每个数的所有出现位置，然后在这个数的 `vector` 里面二分算（这个 $\tt trick$ 来自 [P5048](/problem/P5048 "P5048 [Ynoi2019 模拟赛] Yuno loves sqrt technology III")）。

```cpp
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define range(_) begin(_),end(_)

const int N = 1e5 + 5;

int n,m,a[N],b[N],cnt,st[20][N],lg2[N];
unordered_map<int,int> M;
vector<int> P[N];

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",a + i),st[0][i] = a[i];
	rep(i,1,n) if(!M[a[i]]) M[a[i]] = ++cnt;
	rep(i,1,n) P[M[a[i]]].push_back(i);
	rep(i,2,n) lg2[i] = lg2[i >> 1] + 1;
	rep(j,1,19) rep(i,1,n - (1 << j) + 1)
		st[j][i] = __gcd(st[j - 1][i],st[j - 1][i + (1 << j - 1)]);
	scanf("%d",&m);
	for(int l,r,i;m--;){
		scanf("%d%d",&l,&r),i = lg2[r - l + 1];
		int v = M[__gcd(st[i][l],st[i][r - (1 << i) + 1])];
		printf("%d\n",(r - l + 1) - (upper_bound(range(P[v]),r) - lower_bound(range(P[v]),l)));
	}
	return 0;
}
```

---

## 作者：EternalEpic (赞：3)

简化一下题意：询问一个区间中所有数的最大公约数是否等于区间最小值，如果是则答案为区间长度减去最小值的个数，否则即为区间长度。

那么这就变成一道数据结构题了。

最小值及个数只需要在线段树上维护，在 $query$ 和 $pushup$ 时注意判断，如果儿子最小值与总区间最小值相同，就加儿子的贡献。

至于 $querygcd(l, r)$ 只要用 $st$ 表维护，因为不带修改，否则还要用差分的线段树做，较为麻烦。

这样我们就得到了一个预处理两只 $log$ ，单次查询一个 $log$ 的做法了，写起来还是很方便的。

```cpp
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
const int Maxn = 1e5 + 5, INF = 1e9;
int n, q, lg[Maxn], st[Maxn][19];
struct SegmentTree {
	int tsm[Maxn << 2], tmn[Maxn << 2];
	inline void pushup(int pos) {
		tmn[pos] = min(tmn[pos << 1], tmn[pos << 1 | 1]);
		if (tmn[pos] == tmn[pos << 1]) tsm[pos] += tsm[pos << 1];
		if (tmn[pos] == tmn[pos << 1 | 1]) tsm[pos] += tsm[pos << 1 | 1];
	}
	
	inline void build(int pos, int l, int r) {
		if (l == r) { tsm[pos] = 1; tmn[pos] = st[l][0]; return; }
		int mid = l + r >> 1;
		build(pos << 1, l, mid),
		build(pos << 1 | 1, mid + 1, r);
		pushup(pos);
	}
	
	inline pair <int, int> query(int pos, int l, int r, int L, int R) {
		if (L <= l && R >= r) return Mp(tmn[pos], tsm[pos]);
		int mid = l + r >> 1; pair <int, int> ret, retl, retr;
		ret = retl = retr = Mp(INF, 0);
		if (L <= mid) retl = query(pos << 1, l, mid, L, R);
		if (R > mid) retr = query(pos << 1 | 1, mid + 1, r, L, R);
		ret.first = min(retl.first, retr.first);
		if (ret.first == retl.first) ret.second += retl.second;
		if (ret.first == retr.first) ret.second += retr.second;
		return ret;
	}
} T;

inline int querygcd(int l, int r) {
	int k = lg[r - l + 1];
	return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

signed main(void) {
	read(n); lg[0] = -1;
	for (int i = 1; i <= n; i++)
		read(st[i][0]), lg[i] = lg[i >> 1] + 1;
	T.build(1, 1, n);
	for (int j = 1; j <= 18; j++)
	for (int i = 1; i + (1 << j) - 1 <= n; i++)
		st[i][j] = gcd(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	for (read(q); q; q--) {
		int l, r, d;
		read(l), read(r);
		d = querygcd(l, r);
		pair <int, int> ret = T.query(1, 1, n, l, r);
		if (ret.first == d) writeln(r - l + 1 - ret.second);
		else writeln(r - l + 1);
	}
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```


---

## 作者：c1ampy (赞：2)

## 题意简述

给定长度为 $ n $ 的序列，对于每次询问，求区间 $ [l, r] $ 内**不符合**以下条件的元素的个数：

- 该元素可以整除区间内所有元素。

## 重要结论

在单次询问内，设
$$
cnt = \sum_{i = l}^{r} [a_i = \gcd(a_l, a_{l + 1}, \dots, a_r)]
$$
即 $ cnt $ 为区间内与区间最大公因数相同的元素的个数。

则本次询问的答案为
$$
ans = r - l + 1 - cnt
$$

## 证明

对于一个可以整除区间内所有元素的元素 $ a_i $，必有 
$$
a_i \mid \gcd(a_l, a_{l + 1}, \dots, a_r)
$$
否则其不能整除区间内所有元素。

由最大公约数的定义，又有
$$
\gcd(a_l, a_{l + 1}, \dots, a_r) \mid a_i
$$

故有
$$
a_i = \gcd(a_l, a_{l + 1}, \dots, a_r)
$$

故当区间内某一元素 $ a_i^\prime \neq \gcd(a_l, a_{l + 1}, \dots, a_r) $ 时，则 $ a_i^\prime $ 不能整除区间内所有元素。

则 $ \sum_{i = l}^{r} [a_i \neq \gcd(a_l, a_{l + 1}, \dots, a_r)] $ 即为所求。

显然，上式与重要结论部分中 $ r - l + 1 - cnt $ 相等。

证毕。

## 代码实现

根据以上分析，可知本题需要维护以下两个信息：

- 区间最大公约数
- 区间内与区间最大公约数相等的元素个数

最大公约数有以下性质：
$$
\gcd(a_1, \dots, a_{n - 1}, a_n, a_{n + 1}, \dots, a_{m - 1}, a_m) = \gcd(\gcd(a_1, \dots, a_{n - 1}, a_n), \gcd(a_{n + 1}, \dots, a_{m - 1}, a_m))
$$

这很好地满足了线段树可维护信息的区间可加性，故我们考虑使用线段树维护以上信息。

具体实现详见代码：

```cpp
#include <iostream>
using namespace std;

const int max_n = 1e5 + 10;

struct Node {

    int l, r;
    int gcd;
    int cnt;
    
    Node(const int l = 0, const int r = 0, const int gcd = 0, const int cnt = 0);
    friend Node operator + (const Node & l, const Node & r);
};

struct SegmentTree {

    Node node[max_n << 2];

    void push_up(const int cur);
    void build(const int l, const int r, const int cur = 1);
    Node query(const int l, const int r, const int cur = 1);
};

int a[max_n];
SegmentTree segment_tree;

int get_gcd(const int a, const int b);

int main() {

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    segment_tree.build(1, n);
    
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", r - l + 1 - segment_tree.query(l, r).cnt);
    }

    return 0;
}

int get_gcd(const int a, const int b) {
    return b ? get_gcd(b, a % b) : a;
}

Node::Node(const int l, const int r, const int gcd, const int cnt) {
    this->l = l;
    this->r = r;
    this->gcd = gcd;
    this->cnt = cnt;
}

Node operator + (const Node & l, const Node & r) {
    int gcd = get_gcd(l.gcd, r.gcd);
    int cnt = 0;
    if (gcd == l.gcd) {
        cnt += l.cnt;
    }
    if (gcd == r.gcd) {
        cnt += r.cnt;
    }
    return Node(l.l, r.r, gcd, cnt);
}

void SegmentTree::push_up(const int cur) {
    node[cur] = node[cur << 1] + node[cur << 1 | 1];
}

void SegmentTree::build(const int l, const int r, const int cur) {
    node[cur].l = l;
    node[cur].r = r;
    if (l == r) {
        node[cur].gcd = a[l];
        node[cur].cnt = 1;
        return;
    }

    int mid = l + r >> 1;
    build(l, mid, cur << 1);
    build(mid + 1, r, cur << 1 | 1);
    push_up(cur);
}

Node SegmentTree::query(const int l, const int r, const int cur) {
    if (l == node[cur].l && node[cur].r == r) {
        return node[cur];
    }

    int mid = node[cur].l + node[cur].r >> 1;
    if (mid < l) {
        return query(l, r, cur << 1 | 1);
    }
    else if (mid >= r) {
        return query(l, r, cur << 1);
    }
    else {
        return query(l, mid, cur << 1) + query(mid + 1, r, cur << 1 | 1);
    }
}
```


---

## 作者：az__eg (赞：2)

首先我们发现一个数满分的条件就是他是区间的最大公约数。

同时我们发现最大公约数小于等于区间最小数。

然后我们开两个 st 表，维护区间最小值，和区间最大公约数。

然后再上一个莫队，离散化一下，统计一下每个询问区间的每个不同值的数量。

不想莫队的可以主席树，但是莫队好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N];
int q;
int n;
int f[21][N];
int gcd[21][N];
int bl;
int sv[N];
int b[N];
struct node
{
	int l,r,id;
	bool operator < (const node &qq)const
	{
		if(l/bl==qq.l/bl)return r<qq.r;
		else return l<qq.l;
	}
}query[N];
int ans[N];
int log_2(int x)
{
	int rt=0;
	while((1<<(rt+1))<=x)
	{
		rt+=1;
	}
	return rt;
}
int querymn(int l,int r)
{
	int len=r-l+1;
	return min(f[log_2(len)][l],f[log_2(len)][r-(1<<log_2(len))+1]);
}
int querygcd(int l,int r)
{
	int len=r-l+1;
	return __gcd(gcd[log_2(len)][l],gcd[log_2(len)][r-(1<<log_2(len))+1]);
}
int main()
{
	int i,j;
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	bl=sqrt(n);
	for(i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+1+n);
	int cnt=unique(b+1,b+1+n)-b-1;
	for(i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
	cin>>q;
	for(i=1;i<=n;i++)f[0][i]=a[i],gcd[0][i]=b[a[i]];
	for(i=1;i<=20;i++)for(j=1;j+(1<<i)-1<=n;j++)f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	for(i=1;i<=20;i++)for(j=1;j+(1<<i)-1<=n;j++)gcd[i][j]=__gcd(gcd[i-1][j],gcd[i-1][j+(1<<(i-1))]);
	for(i=1;i<=q;i++)
	{
		cin>>query[i].l>>query[i].r;
		query[i].id=i;
	}
	sort(query+1,query+1+q);
	int l=query[1].l,r=query[1].l-1;
	for(i=1;i<=q;i++)
	{
		int L=query[i].l,R=query[i].r;
		while(l<L)
		{
			sv[a[l]]--;
			l++;
		}
		while(l>L)
		{
			l--;
			sv[a[l]]++;
		}
		while(r<R)
		{
			r++;
			sv[a[r]]++;
		}
		while(r>R)
		{
			sv[a[r]]--;
			r--;
		}
		int mn=querymn(L,R);
		int GcD=querygcd(L,R);
		if(b[mn]!=GcD)
		{
			ans[query[i].id]=(R-L+1);
		}
		else
		{
			ans[query[i].id]=(R-L+1-sv[mn]);
		}
	}
	for(i=1;i<=q;i++)cout<<ans[i]<<"\n";
}
```


---

## 作者：听取MLE声一片 (赞：2)

简单题。

显然可以转化为查询区间内有多少个数整除区间所有数。

如果 $A$ 整除 $B$，那么 $A$ 一定不大于 $B$，所以区间所有数的最大公因数一定不大于区间最小值，只有区间最小值可能会产生贡献。

如果一个数能整除区间所有数，令 $C$ 是区间所有数的最大公因数，那么这个数必定是 $C$ 的一个因数，其中 $C$ 不大于区间最小值。

对于 $C$ 的因数中小于 $C$ 的数，一定不可能出现在序列中，那么只有 $C$ 本身可能会产生贡献。

所以只需要判断 $C$ 是否等于区间最小值即可，如果是会产生最小值出现次数的贡献。

使用线段树进行维护，需要维护的信息有区间最小值，区间最小值出现次数和区间最大公因数。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n,q,a[N];
struct point{
	int minn,sum,g;
}T[N<<2];
point pushup(point x,point y){
	point ret;
	ret.g=__gcd(x.g,y.g);
	if(x.minn<y.minn){
		ret.minn=x.minn;
		ret.sum=x.sum;
		return ret;
	}
	if(x.minn>y.minn){
		ret.minn=y.minn;
		ret.sum=y.sum;
		return ret;
	}
	ret.minn=x.minn;
	ret.sum=x.sum+y.sum;
	return ret;
}
void build(int p,int l,int r){
	if(l==r){
		T[p].g=a[l];
		T[p].minn=a[l];
		T[p].sum=1;
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	T[p]=pushup(T[ls],T[rs]);
}
point query(int L,int R,int p,int l,int r){
	if(L<=l&&r<=R)
		return T[p];
	if(L<=mid&&R<=mid)
		return query(L,R,ls,l,mid);
	if(L>mid&&R>mid)
		return query(L,R,rs,mid+1,r);
	return pushup(query(L,R,ls,l,mid),query(L,R,rs,mid+1,r));
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	build(1,1,n);
	q=read();
	while(q--){
		int l=read(),r=read(),ans=r-l+1;
		point ret=query(l,r,1,1,n);
		if(ret.minn==ret.g)
			ans-=ret.sum;
		printf("%d",ans);
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：Buried_Dream (赞：2)

## Solution

如果一个数要得到满分，说明区间内的所有数都是他的倍数。

那这个数一定是区间的最小公约数。

又因为他一定是区间的最小值。

用反证法来证明一下：

如果他不是最小值，那一定存在一个更小的数，而更小的数一定不可能是他的倍数。

所以我们用线段树来维护区间的最小值，最小公约数，最小值的个数。

为了方便，这是采用的是重载运算符的线段树。

在一些题目中，妙用重载运算符能节省太多的码量。


```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.7.27
**/
#include<cmath>
#include<queue>
#include<cstdio>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar 
using namespace std;
typedef long long ll;
//#define int long long
const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
const ll inf = 0x3f3f3f3f3f3f3f3f;
inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline int ksm(int a, int b) {int base = a % mod, res = 1; while(b){if(b & 1) res = (res * base) % mod; base = (base * base) % mod, b >>= 1;}return res % mod;}
inline int mul(int a, int b) {int base = a % mod, res = 0; while(b){if(b & 1) res = (res + base) % mod; base = (base + base) % mod, b >>= 1;}return res % mod;}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

namespace Seg {
	#define lson rt << 1
	#define rson rt << 1 | 1
	struct Node {
		int l, r, min, num, gcd; 
	} tree[N << 2];
	Node operator + (const Node &a, const Node &b)  {
		Node res; 
		res.min = std::min(a.min, b.min);
		res.gcd = gcd(a.gcd, b.gcd);
		if(a.min == b.min) res.num = a.num + b.num;
		else if(a.min < b.min) res.num = a.num;
		else if(b.min < a.min) res.num = b.num;
		return res;
	}
	void pushup(int rt) {
		tree[rt].min = std::min(tree[lson].min, tree[rson].min);
		tree[rt].gcd = gcd(tree[lson].gcd, tree[rson].gcd);
		if(tree[lson].min == tree[rson].min) tree[rt].num = tree[lson].num + tree[rson].num;
		else if(tree[lson].min > tree[rson].min) tree[rt].num = tree[rson].num;
		else if(tree[rson].min > tree[lson].min) tree[rt].num = tree[lson].num;
	}
	void build(int rt, int l, int r) {
		tree[rt].l = l, tree[rt].r = r;
		if(l == r) {
			tree[rt].min = read();
			tree[rt].gcd = tree[rt].min;		
			tree[rt].num = 1; return;
		} int mid = (l + r) >> 1;
		build(lson, l, mid), build(rson, mid + 1, r);
		pushup(rt);
	}
	Node Query(int rt, int l, int r) {
		if(tree[rt].l > r || tree[rt].r < l) return tree[0];
		if(tree[rt].l >= l && tree[rt].r <= r) return tree[rt];
		return Query(lson, l, r) + Query(rson, l, r);
	}
}
using namespace Seg;

signed main() 
{
	int n = read();
	tree[0].min = INF, tree[0].gcd = 0;
	build(1, 1, n);
	int Q = read();
	for(int i = 1; i <= Q; i++) {
		int l = read(), r = read();
		Node ans = Query(1, l, r);
		int num = 0;
		if(ans.min == ans.gcd) num = ans.num;
		printf("%d\n", r - l + 1 - num);
	}
	return 0;
}
```

---

## 作者：XeniaF (赞：1)

提供一种比较无脑的做法。

可以发现如果一个数满分，说明这个数是这个区间内每个数的公约数，但由于它同时要是自己的公约数，于是它一定是这个区间的最大公约数。

问题变成了给定区间 $[l,r]$ ，区间内有多少个数不等于 $\gcd(a_l,a_{l+1},...,a_r)$ 。

区间最大公约数可以通过 ST 表 $\mathcal{O}(n\log^2 n)$ 预处理 $\mathcal{O}(\log n)$ 查询来维护，区间内一个数的个数可以通过主席数维护。由于 $1\leqslant s_i \leqslant 10^9$ ，需要离散化。

同时需要特判如果区间内不存在 $\gcd(a_l,a_{l+1},...,a_r)$ ，说明 $\min(a_l,...,a_r)\neq\gcd(a_l,...,a_r)$ ，再开个 ST 表维护区间最小值即可。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define maxn 100001
using namespace std;

ll n;
ll s[maxn];
ll q;
ll f[maxn][25];
ll g[maxn][25];

inline ll read(){
    ll x=0,f=0;char c=getchar();
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?-x:x;
}

inline ll Gcd(ll x,ll y){return !y?x:Gcd(y,x%y);}

ll rt[maxn];
ll b[maxn];
ll ln;

struct T_Tree{
    ll sm[maxn*40];
    ll lc[maxn*40];
    ll rc[maxn*40];
    ll cnt=0;

    T_Tree(){cnt=0;}

    inline void build(ll &id,ll l,ll r){
        id=++cnt;
        sm[id]=lc[id]=rc[id]=0;
        if(l==r) return;
        ll mid=(l+r)>>1;
        build(lc[id],l,mid),build(rc[id],mid+1,r);
    }

    inline void ins(ll &id,ll o,ll l,ll r,ll vl){
        id=++cnt;
        lc[id]=lc[o],rc[id]=rc[o],sm[id]=sm[o]+1;
        if(l==r) return;
        ll mid=(l+r)>>1;
        if(vl<=mid) ins(lc[id],lc[o],l,mid,vl);
        else ins(rc[id],rc[o],mid+1,r,vl);
    }

    inline ll qry(ll id,ll o,ll l,ll r,ll vl){
        if(l==r) return abs(sm[o]-sm[id]);
        ll mid=(l+r)>>1;
        if(vl<=mid) return qry(lc[id],lc[o],l,mid,vl);
        else return qry(rc[id],rc[o],mid+1,r,vl);
    }
}tr;

inline ll qy(ll l,ll r){
    ll lg=log2(r-l+1);
    return Gcd(f[l][lg],f[r-(1<<lg)+1][lg]);
}

inline ll qym(ll l,ll r){
    ll lg=log2(r-l+1);
    return min(g[l][lg],g[r-(1<<lg)+1][lg]);
}

int main(){
    n=read();
    for(register int i=1;i<=n;++i) s[i]=f[i][0]=g[i][0]=read(),b[++ln]=s[i];
    sort(b+1,b+ln+1),ln=unique(b+1,b+ln+1)-b-1;
    for(register ll i=1;i<=25;++i)
        for(register ll j=1;j+(1<<i)-1<=n;++j)
            f[j][i]=Gcd(f[j][i-1],f[j+(1<<(i-1))][i-1]);
    for(register ll i=1;i<=25;++i)
        for(register ll j=1;j+(1<<i)-1<=n;++j)
            g[j][i]=min(g[j][i-1],g[j+(1<<(i-1))][i-1]);
    q=read();
    tr.build(rt[0],1,ln);
    for(register int i=1;i<=n;++i){
        ll ap=lower_bound(b+1,b+ln+1,s[i])-b;
        tr.ins(rt[i],rt[i-1],1,ln,ap);
    }
    for(register int i=1;i<=q;++i){
        ll L,R;
        L=read(),R=read();
        ll gd=qy(L,R);
        ll mn=qym(L,R);
        if(gd!=mn) {printf("%lld\n",R-L+1);continue;}
        gd=lower_bound(b+1,b+ln+1,gd)-b;
        printf("%lld\n",R-L+1-tr.qry(rt[L-1],rt[R],1,ln,gd));
    }
    return 0;
}
```



---

## 作者：happybob (赞：1)

## 简略题意

给定一个 $n$ 个元素的序列 $a$，并且给定 $m$ 次询问，每次询问给定区间 $[l,r]$，设 $g = \gcd(a_l,a_{l+1}, a_{l+2}, \cdots, a_r)$，询问 $\sum_{i=l}^r \begin{cases} 1 & a_i \neq g \\ 0 & \text{otherwise} \end{cases} $，即求 $(r-l+1) - (\sum_{i=l}^r \begin{cases} 1 & a_i=g \\ 0 & \text{otherwise} \end{cases})$。

## 解法

给一个离线解法。

第一步，$a_i \le 10^9$，考虑先离散化。

首先考虑 $\gcd(a_l,a_{l+1}, a_{l+2}, \cdots, a_r)$，明显可以线段树维护，维护的复杂度 $O(n \cdot (\log n + \log v))$，因为计算 $\gcd$ 的复杂度是 $\log n$ 的，$v$ 是值域。

维护完之后明显要求 $\gcd(a_l,a_{l+1}, a_{l+2}, \cdots, a_r)$ 在 $[l,r]$ 中出现的次数，大家都是什么 ST 表或者其他解法，但是出现次数这个问题可以莫队解决。

总结起来，我们对每次询问计算 $\gcd$，然后莫队维护区间 $[l,r]$ 中这个 $\gcd$ 出现次数。

接着分析复杂度：

线段树维护的复杂度是 $O(n \cdot (\log n + \log v))$，而莫队复杂度 $O(n \sqrt{n})$，所以总复杂度 $O(n \cdot (\log n + \log v) + n \sqrt{n})$（应该没错吧，因为 $n,m \le 10^5$，所以我们算复杂度时假设 $n,m$ 同阶，因为不知道 $n \cdot (\log n + \log v)$ 和 $n \sqrt{n}$ 谁大，所以我们相加。如果有错请指出）。

复杂度好像很大，但是最慢的点也就三百多毫秒，轻松通过。

不得不说有紫题的难度。

代码：

```cpp
#pragma GCC optimize(2) 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <utility>
#include <unordered_map>
using namespace std;

const int N = 1e5 + 5;

inline int gcd(int a, int b)
{
	return (b == 0 ? a : gcd(b, a % b));
}

int ans[N], a[N], b[N], n, m, len, cntk[N], real[N];
unordered_map<int, bool> mp;

struct Node
{
	int l, r, gcdn;
}tree[N << 2];

inline void push_up(int u)
{
	tree[u].gcdn = gcd(tree[u << 1].gcdn, tree[u << 1 | 1].gcdn);
}

inline void build(int u, int l, int r)
{
	tree[u] = { l, r };
	if (l == r) tree[u].gcdn = real[a[r]];
	else
	{
		int mid = (l + r) >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		push_up(u);
	}
}

inline int query(int u, int l, int r)
{
	if (tree[u].l >= l && tree[u].r <= r) return tree[u].gcdn;
	int mid = (tree[u].l + tree[u].r) >> 1;
	int k = 0;
	if (l <= mid)
	{
		k = query(u << 1, l, r);
	}
	if (r > mid)
	{
		k = gcd(k, query(u << 1 | 1, l, r));
	}
	return k;
}

struct Nodeq
{
	int rid, l, r, gcdn;
	bool operator<(const Nodeq& g) const
	{
		int i = l / len, j = g.l / len;
		return (i ^ j ? i < j : i & 1 ? r < g.r : r > g.r);
	}
}q[N];

inline void add(int x)
{
	++cntk[a[x]];
}

inline void del(int x)
{
	--cntk[a[x]];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
		mp[a[i]] = true;
	}
	sort(b + 1, b + n + 1);
	int place = unique(b + 1, b + n + 1) - b - 1;
	for (register int i = 1; i <= n; ++i)
	{
		int k = a[i];
		a[i] = lower_bound(b + 1, b + place + 1, a[i]) - b + 1;
		real[a[i]] = k;
	}
	build(1, 1, n);
	scanf("%d", &m);
	for (register int i = 1; i <= m; ++i)
	{
		register int l, r;
		scanf("%d %d", &l, &r);
		int qp = query(1, l, r);
		q[i] = { i, l, r, qp };
	}
	len = sqrt(m);
	sort(q + 1, q + m + 1);
	register int nl = 1, nr = 0;
	for (register int i = 1; i <= m; ++i)
	{
		int l = q[i].l, r = q[i].r;
		while (nl < l) del(nl++);
		while (nl > l) add(--nl);
		while (nr < r) add(++nr);
		while (nr > r) del(nr--);
		if (!mp[q[i].gcdn]) ans[q[i].rid] = r - l + 1;
		else ans[q[i].rid] = (r - l + 1) - cntk[lower_bound(b + 1, b + place + 1, q[i].gcdn) - b + 1];
	}
	for (register int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
```




---

## 作者：_Life_ (赞：1)

### 题意
给出长度为 $n$ 的序列，每次询问区间 $[L,R]$ 中，有多少数不能整除区间 $[L,R]$。
### 题解
不难发现，如果一个数整除 $[L,R]$，这个数必然是 $[L,R]$ 的最大公约数。若 $[L,R]$ 中有 $num$ 个 $\gcd_{[L,R]}$，则 $ans=R-L+1-num$。

因为 $\gcd$ 满足结合律与交换律，所以可以用线段树来快速计算区间 $\gcd$，并且可以在计算区间 $\gcd$ 的同时记录答案。

考虑如何合并两个区间的结果：区间 $[L,k],[k+1,R]$ 的 $\gcd$ 与 $num$ 已知 ，求区间 $[L,R]$ 的 $\gcd$ 与 $num$ ？

显然 $\gcd_{[L,R]}=\gcd(\gcd_{[L,k]},\gcd_{[k+1,R]})$，若 $\gcd_{[L,R]}$ 与一个小区间的 $\gcd$ 相等，那就加上该小区间的 $num$。

时间复杂度 $O(n\log n)-O(\log^2n)$

### 代码
```cpp
#include<cstdio>
#include<algorithm>
#define ls(pos) (pos<<1)
#define rs(pos) (pos<<1|1)
#define mid ((l+r)>>1)
using namespace std;
int n,m,a[100005],seg[100005<<2],sum[100005<<2];
void build(int pos=1,int l=1,int r=n)
{
	if(l==r)
	{
		seg[pos]=a[l];
		sum[pos]=1;
		return;
	}
	build(ls(pos),l,mid);
	build(rs(pos),mid+1,r);
	seg[pos]=__gcd(seg[ls(pos)],seg[rs(pos)]);
	if(seg[pos]==seg[ls(pos)])sum[pos]+=sum[ls(pos)];
	if(seg[pos]==seg[rs(pos)])sum[pos]+=sum[rs(pos)];
}
struct node
{
	int a,b;
	node(){a=b=0;}
	node(int x,int y){a=x,b=y;}
	node operator +(node x)
	{
		node ans;
		ans.a=__gcd(a,x.a);
		if(ans.a==a)ans.b+=b;
		if(ans.a==x.a)ans.b+=x.b;
		return ans;
	}
};
node query(int lx,int rx,int pos=1,int l=1,int r=n)
{
	if(lx<=l&&r<=rx)
		return (node){seg[pos],sum[pos]};
	node ans;
	if(lx<=mid)
		ans=ans+query(lx,rx,ls(pos),l,mid);
	if(rx>mid)
		ans=ans+query(lx,rx,rs(pos),mid+1,r);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build();
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++)
	{
		scanf("%d %d",&l,&r);
		printf("%d\n",r-l+1-query(l,r).b);
	}
}
```

---

## 作者：first_fan (赞：1)

在开始之前，有一些$define$需要了解(不然看不懂)

```cpp
#define ri register int
#define ll long long
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define leaf (l==r)
```

虽然题目已经简化，还是来翻译下题意吧：

>给你一个区间，每次问这个区间内的数字`不等于`区间 $gcd$ 的有多少个。

怎样？有思路了？一个裸的线段树维护$gcd$

显然，$gcd$和题目所求的数的个数都满足区间可加性，所以说线段树搞定。

每次维护的时候，$gcd$直接加，而个数$sum$如果判断出父子区间结点的$gcd$相同，我们就把子节点的个数加入到父节点的个数里。

因为如果一个区间的$gcd$同其父结点的区间$gcd$相同，那么满足等于区间$gcd$的数的个数一定可上传。

先把维护写好：

```cpp
void pushup(ll nd)
{
	seg[nd].gcd=__gcd(seg[ls(nd)].gcd,seg[rs(nd)].gcd);
   	//一句话维护gcd
	seg[nd].sum=0;//个数归零
	if(seg[nd].gcd==seg[ls(nd)].gcd)
	{
		seg[nd].sum+=seg[ls(nd)].sum;
	}
	if(seg[nd].gcd==seg[rs(nd)].gcd)
	{
		seg[nd].sum+=seg[rs(nd)].sum;
	}//分别加
}
```

建树过程过于简单，此处不详讲。`（提问请私信我）`


```cpp
void build(ll nd,ll l,ll r)
{
	seg[nd].l=l;
	seg[nd].r=r;
	if(leaf)
	{
		seg[nd].gcd=read();
		seg[nd].sum=1;
        	//等于区间gcd的个数，叶子结点即其本身
		return ;
	}//边读边建
	ll mid=(l+r)>>1;
	build(ls(nd),l,mid);
	build(rs(nd),mid+1,r);//递归
	pushup(nd);
}
```

下面是线段树找区间$gcd$模板：

```cpp
ll interval_gcd(ll nd,ll l,ll r)
{
	if(seg[nd].l==l&&seg[nd].r==r)
	{
		return seg[nd].gcd;
	}//恰好塞下
	ll mid=(seg[nd].l+seg[nd].r)>>1;
	if(l>mid)
	{
		return interval_gcd(rs(nd),l,r);
	}//区间在右边
	else if(r<=mid)
	{
		return interval_gcd(ls(nd),l,r);
	}//区间在左边
	else
	{
		return __gcd(interval_gcd(ls(nd),l,mid),interval_gcd(rs(nd),mid+1,r));//拆分区间（区间跨越mid时）
	}
}
```

那么接下来就是询问环节了，几乎是裸的`线段树1`模板，只不过维护对象变成$gcd$而已。

```cpp
ll query(ll nd,ll l,ll r)
{
	if(seg[nd].l==l&&seg[nd].r==r)
	{
		return gcd==seg[nd].gcd?seg[nd].sum:0;
	}//恰
	ll mid=(seg[nd].l+seg[nd].r)>>1;
	if(l>mid)
	{
		return query(rs(nd),l,r);
	}//→
	else if(r<=mid)
	{
		return query(ls(nd),l,r);
	}//←
	else
	{
		return query(ls(nd),l,mid)+query(rs(nd),mid+1,r);
	}//跨
}
```

那么理下思路，我们先递归建树顺便维护，再对于询问的每个区间查询区间$gcd$并更新$sum$，返回输出$sum$即可。

`不得不提的一点是`我们求出来的恰好是题目所求数的补集，题目问的是非$gcd$，所以我们要用区间长减去所得$sum$

下面是整份无注代码，欢迎各位优化：

```cpp
#include <bits/stdc++.h>
#define ri register ll
#define ll long long
using namespace std;
#define leaf (l==r)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

ll read()
{
	ll num=0;
	ll flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}
struct segment_tree
{
	ll l,r;
	ll gcd;
	ll sum;
}seg[2003125];

ll n,m,gcd;

void pushup(ll nd)
{
	seg[nd].gcd=__gcd(seg[ls(nd)].gcd,seg[rs(nd)].gcd);
	seg[nd].sum=0;
	if(seg[nd].gcd==seg[ls(nd)].gcd)
	{
		seg[nd].sum+=seg[ls(nd)].sum;
	}
	if(seg[nd].gcd==seg[rs(nd)].gcd)
	{
		seg[nd].sum+=seg[rs(nd)].sum;
	}
}

void build(ll nd,ll l,ll r)
{
	seg[nd].l=l;
	seg[nd].r=r;
	if(leaf)
	{
		seg[nd].gcd=read();
		seg[nd].sum=1;
		return ;
	}
	ll mid=(l+r)>>1;
	build(ls(nd),l,mid);
	build(rs(nd),mid+1,r);
	pushup(nd);
}

ll interval_gcd(ll nd,ll l,ll r)
{
	if(seg[nd].l==l&&seg[nd].r==r)
	{
		return seg[nd].gcd;
	}
	ll mid=(seg[nd].l+seg[nd].r)>>1;
	if(l>mid)
	{
		return interval_gcd(rs(nd),l,r);
	}
	else if(r<=mid)
	{
		return interval_gcd(ls(nd),l,r);
	}
	else
	{
		return __gcd(interval_gcd(ls(nd),l,mid),interval_gcd(rs(nd),mid+1,r));
	}
}

ll query(ll nd,ll l,ll r)
{
	if(seg[nd].l==l&&seg[nd].r==r)
	{
		return gcd==seg[nd].gcd?seg[nd].sum:0;
	}
	ll mid=(seg[nd].l+seg[nd].r)>>1;
	if(l>mid)
	{
		return query(rs(nd),l,r);
	}
	else if(r<=mid)
	{
		return query(ls(nd),l,r);
	}
	else
	{
		return query(ls(nd),l,mid)+query(rs(nd),mid+1,r);
	}
}

int main()
{
	n=read();
	build(1,1,n);
	m=read();
	while(m--)
	{
		ll l=read();
		ll r=read();
		gcd=interval_gcd(1,l,r);
		printf("%lld\n",r+1-l-query(1,l,r));
	}
}
```

* 关于线段树区间$gcd$

* 模板：[LuoGu1890 gcd区间](https://www.luogu.org/problemnew/show/P1890)

* $hdu5726$也可以自己试试，类模板

* 挑战：[LuoGu2086 [NOI2012]魔幻棋盘](https://www.luogu.org/problemnew/show/P2086)

$\tiny\text{这是个二维线段树区间gcd的题，可以花些时间想想。}$

---

## 作者：moye到碗里来 (赞：1)

那份题解太巨了蒟蒻看不懂。。。
我的做法是区间gcd用线段树维护，然后vector记录每个数字出现的位置的集合，二分一下即可找到区间内的数的个数。。
~~注意范围最大是ll，不离散化过不了~~
```

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200020;
#define ll long long 
struct node{
    int gcd;
    node *ls,*rs;
}pool[MAXN * 2];
node *NewNode(){
    static int cnt = 0;
    pool[cnt].gcd = 0,pool[cnt].ls = pool[cnt].rs = NULL;
    return &pool[cnt++];
}
vector<int> v[MAXN];
map<ll,int>f;
int gcd(int x,int y){return y == 0 ? x : gcd(y, x % y);}
int n,m;
ll a[MAXN],b[MAXN];
node *build(int l,int r){
    if(l > r)return NULL;
    node *rt = NewNode();
    if(l == r){
        rt->gcd = a[l];
        return rt;
    }
    int mid = l + r >> 1;
    rt->ls = build(l,mid);
    rt->rs = build(mid + 1,r);
    rt->gcd = gcd(rt->ls->gcd,rt->rs->gcd);  
    return rt;
}
int query(node *rt,int l,int r,int L,int R){
     if(l > R || r < L || l > r)return 0;
     if(L <= l && r <= R){
         return rt->gcd;
     }
    int ans = 0;
    int mid = l + r >> 1;
    ans = gcd(ans,query(rt->ls,l,mid,L,R));
    ans = gcd(ans,query(rt->rs,mid + 1,r,L,R));
    return ans;
}
inline void solve(int x,int l,int r){
    x = f[x];
    int ans = upper_bound(v[x].begin(),v[x].end(),r) - upper_bound(v[x].begin(),v[x].end(),l - 1);
    printf("%d\n",r - l + 1 - ans);
    return ;
}
int main()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; ++i){
        scanf("%lld",&a[i]);
        b[i] = a[i];
    }
    sort(b + 1,b + 1 + n);
    int siz = unique(b + 1,b + 1 + n) - (b + 1);
    for(int i = 1; i <= n; ++i){
        int x = lower_bound(b + 1,b + 1 + siz,a[i]) - b;
        f[a[i]] = x;
        v[x].push_back(i); 
    }
    node *rt = build(1,n);
    scanf("%d",&m);
    for(int i = 1; i <= m; ++i){
        int l,r;
        scanf("%d %d",&l,&r);
        int g = query(rt,1,n,l,r);
        solve(g,l,r);
    }
    return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：1)

## 题目简述

- 给一个长度为 $n$ 的数列 $a_i$。
- 给出 $q$ 次询问每次给出 $l,r$，问有多少个 $i\in [l,r],\exists j\in[l,r]$ 使得 $a_i\not | a_j$。
- $n,q\leq 10^5$。

## 解题思路

首先反面考虑，如果 $\exists i\in[l,r],\forall j\in[l,r],a_i|a_j$ 那么显然 $a_i$ 是 $i\in[l,r]$ 当中最小的。并且还有 $\gcd_l^r=a_i$。

考虑用 ST 表完成，维护一个 $2^i$ 区间的最小值，最小值的个数，区间 gcd。这都是可以用 ST 表实现。

时间复杂度 $\mathcal{O}(q\log n)$。完结撒花。

## 参考代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1e5+5;
struct node{
	int minn,cnt,gcd;
}f[20][MAXN];
int n,m;
int a[MAXN];
int l,r;
int gcd(int x,int y){
	return (x%y==0)?y:gcd(y,x%y);
}
node add(node x,node y){
	if(x.minn<y.minn) return node{x.minn,x.cnt,gcd(x.gcd,y.gcd)};
	if(x.minn==y.minn) return node{x.minn,y.cnt+x.cnt,gcd(x.gcd,y.gcd)};
	return node{y.minn,y.cnt,gcd(x.gcd,y.gcd)};
}
void init(){
	for(int i=1;i<=n;i++)
		f[0][i]=node{a[i],1,a[i]};
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;(1<<i)+j-1<=n;j++)
			f[i][j]=add(f[i-1][j],f[i-1][j+(1<<i-1)]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	init(); 
	cin>>m;
	while(m--){
		node x=node{0,0,0};
		cin>>l>>r;
		int L=l;
		for(int i=19;i>=0;i--)
			if(l+(1<<i)<=r+1){
				if(x.gcd==0)
					x=f[i][l];
				else
					x=add(x,f[i][l]);
				l+=(1<<i);
			}
		if(x.gcd==x.minn) cout<<r-L+1-x.cnt<<endl;
		else cout<<r-L+1<<endl;
	}
	return 0;
}
```


---

## 作者：LengthCheng (赞：0)

# **蒟蒻的第二篇题解**

## [>> CF474F Ant colony](https://www.luogu.com.cn/problem/CF474F)

## **题意解释**

对于一个长度为 $ n $ 的序列，给出 $ q $ 个询问，对于每个询问，给出一个区间 $ [l,r] $，输出这个区间内**不能**整除除自身以外的所有数的数的个数。

## **题目分析**

读完题目，我们不难发现，一个区间内能整除区间内所有数的数即为这个区间的 $ \gcd $（可能不在这个区间内），那么我们只需要统计区间内区间 $ \gcd $ 的个数，设这个值为 $ cnt $，则答案即为 $ r - l + 1 - cnt $。

## **代码实现**

由于区间 $ \gcd $ 是满足区间加法的：

$$ \gcd( a_1,a_2,\dots,a_{n-1},a_n ) = \gcd( \gcd( a_1,a_2,\dots,a_{j-1},a_j ),\gcd( a_{j+1},a_{j+2},\dots,a_{n-1},a_n ) ) $$

所以可以考虑用线段树维护两个信息：

1. 区间 $ \gcd $。
2. 区间中区间 $ \gcd $ 的个数。

对于建树部分，每遍历到一个叶子节点，显然一个数的 $ \gcd $ 就是它本身，此时区间 $ \gcd $ 的个数为一。

接下来考虑区间合并，对于一个区间 $ A $ 以及它的左子区间 $ L $ 和右子区间 $ R $，由上式有 $ \gcd_A = \gcd( \gcd_L,\gcd_R ) $，则可直接计算区间 $ \gcd $。而对于区间 $ \gcd $ 的个数，可以分两种情况讨论：

1. 当 $ \gcd_A = \min( \gcd_L,\gcd_R ) $ 时。

2. 当 $ \gcd_A \neq \min( \gcd_L,\gcd_R ) $ 时。

显然，一个区间的 $ \gcd $ 一定小于等于区间内的每个元素，则对于第一种情况，区间 $ \gcd $ 较大的那个子区间中的所有元素一定大于等于另一个子区间的 $ \gcd $，此时也存在两种情况：

1. 当 $ \gcd_L = \gcd_R $ 时，$ cnt_A = cnt_L + cnt_R $。

2. 当 $ \gcd_L \neq \gcd_R $ 时，$ cnt_A $ 的值等于区间 $ \gcd $ 较小的那个子区间的 $ cnt $。

对于第二种情况，由于 $ \gcd_A $ 小于区间内任一元素，则 $ \gcd_A $ 一定不在这个区间内，此时区间 $ \gcd $ 的个数为 $ 0 $。

最后直接查询区间 $ [l,r] $ 的 $ cnt $,输出答案为 $ r - l + 1 -cnt $。

### **code**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
struct Seg{
	int l,r;
	int gcd;
	int sum;
};
Seg tree[N*4];
int gcd(int a,int b)
{
	if(a%b==0)
	{
		return b;
	}
	gcd(b,a%b);
}
void push_up(int p)
{
	int maxn=max(tree[p*2].gcd,tree[p*2+1].gcd);
	int minn=min(tree[p*2].gcd,tree[p*2+1].gcd);
	if(maxn%minn)
	{
		tree[p].gcd=gcd(maxn,minn);
		tree[p].sum=0;
		return;
	}
	tree[p].gcd=minn;
	if(tree[p*2].gcd<tree[p*2+1].gcd)
    {
	    tree[p].sum=tree[p*2].sum;
	}
    else if(tree[p*2].gcd>tree[p*2+1].gcd)
    {
	    tree[p].sum=tree[p*2+1].sum;
    }
    else
    {
    	tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
	}
	return;
}
void build(int p,int l,int r)
{
	tree[p].l=l,tree[p].r=r;
	if(l==r)
	{
		tree[p].gcd=a[l];
		tree[p].sum=1;
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	push_up(p);
}
Seg ask(int p,int l,int r)
{
	if(l==tree[p].l && tree[p].r==r)
	{
		return tree[p];
	}
	int mid=(tree[p].l+tree[p].r)/2;
	if(l>mid)
	{
		return ask(p*2+1,l,r);
	}
	else if(r<=mid)
	{
		return ask(p*2,l,r);
	}
	else
	{
		Seg ans,L=ask(p*2,l,mid),R=ask(p*2+1,mid+1,r);
		int maxn=max(L.gcd,R.gcd);
		int minn=min(L.gcd,R.gcd);
		if(maxn%minn)
		{
		    ans.gcd=gcd(maxn,minn);
			ans.sum=0;
			return ans;
		}
		ans.gcd=minn;
		if(L.gcd<R.gcd)
    	{
	        ans.sum=L.sum;
		}
		else if(L.gcd>R.gcd)
    	{
	        ans.sum=R.sum;
   		}
    	else
    	{
    	    ans.sum=L.sum+R.sum;
		}
		return ans;
	}
}
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)
    {
    	scanf("%d",&a[i]);
	}
	build(1,1,n);
	int q;
	cin>>q;
	for(int i=1;i<=q;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
	    printf("%d\n",r-l+1-ask(1,l,r).sum);
	}
	return 0;
}

```

---

## 作者：5k_sync_closer (赞：0)

线段树。

若 $i$ 得到满分，则 $\forall j\in[l,r],s_i|s_j$，即 $s_i=\gcd\limits_{j=l}^r s_j$。

即求区间 $\gcd$ 出现次数，可以类比区间 $\min$ 出现次数写。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, g[100050 << 2], v[100050 << 2];
void B(int s, int t, int p)
{
	if(s == t) return (void)(scanf("%d", g + p), v[p] = 1);
	int m = s + t >> 1;B(s, m, p << 1);B(m + 1, t, p << 1 | 1);
	g[p] = __gcd(g[p << 1], g[p << 1 | 1]);
	if(g[p] == g[p << 1]) v[p] += v[p << 1];
	if(g[p] == g[p << 1 | 1]) v[p] += v[p << 1 | 1];
}
int G(int l, int r, int s, int t, int p)
{
	if(l <= s && t <= r) return g[p];int m = s + t >> 1;
	if(l <= m && r > m) return __gcd(G(l, r, s, m, p << 1), G(l, r, m + 1, t, p << 1 | 1));
	if(l <= m) return G(l, r, s, m, p << 1);if(r > m) return G(l, r, m + 1, t, p << 1 | 1);
}
int Q(int l, int r, int k, int s, int t, int p)
{
	if(l <= s && t <= r) return v[p] * (g[p] == k);int m = s + t >> 1, q = 0;
	if(l <= m) q += Q(l, r, k, s, m, p << 1);if(r > m) q += Q(l, r, k, m + 1, t, p << 1 | 1);return q;
}
int main()
{
	scanf("%d", &n);B(1, n, 1);scanf("%d", &m);
	for(int i = 0, x, y;i < m;++i)
		scanf("%d%d", &x, &y), printf("%d\n", y - x + 1 - Q(x, y, G(x, y, 1, n, 1), 1, n, 1));
	return 0;
}
```


---

## 作者：Arghariza (赞：0)

如果一个数得到了满分，那么这个数一定是所有数的公因数，于是这个数一定是所有数的最小值，因此这个数一定是所有数的**最大公因数**。

于是我们把询问转化为区间 $\gcd$ 的个数。

于是可以使用 `st` 表计算区间 $\gcd$，然后就变成了询问区间某种数的个数。

这东西可以离散化后建桶，然后再桶内存储每个这个数出现的下标，查询的时候二分即可。

但你会发现这样做太麻烦了，于是可以主席树。

复杂度 $O(n\log n\log w+q(\log w+\log n))$，瓶颈在于 `st` 表预处理，如果换成线段树的话可以达到单 $\log$，但不想写。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
const int maxs = 25;
struct hjtree { int lc, rc, sum; } tr[maxn << 7];
int n, m, tot, a[maxn], rt[maxn], f[maxn][maxs];

#define ls tr[x].lc
#define rs tr[x].rc
#define mid ((l + r) >> 1)
void update(int l, int r, int p, int rt, int &x) {
	x = ++tot, tr[x] = tr[rt], tr[x].sum++;
	if (l == r) return;
	if (p <= mid) update(l, mid, p, tr[rt].lc, ls);
	else update(mid + 1, r, p, tr[rt].rc, rs);
}

int query(int l, int r, int p, int x) {
	if (!x) return 0;
	if (l == r) return tr[x].sum;
	if (p <= mid) return query(l, mid, p, ls);
	else return query(mid + 1, r, p, rs);
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int gcds(int l, int r) {
	int len = log2(r - l + 1);
	return gcd(f[l][len], f[r - (1 << len) + 1][len]);
}

signed main() {
	n = read();
	for (int i = 1; i <= n; i++) f[i][0] = a[i] = read(), update(1, 1e9, a[i], rt[i - 1], rt[i]);
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
	m = read();
	for (int i = 1, l, r; i <= m; i++) {
		l = read(), r = read();
		int g = gcds(l, r);
		write(r - l + 1 - query(1, 1e9, g, rt[r]) + query(1, 1e9, g, rt[l - 1]));
		puts("");
	}
	return 0;
}

```

---

## 作者：hank0402 (赞：0)

### 题目大意：

有一个长度为 $n$ 的整数序列，有 $q$ 次询问，每次询问给出一个区间 $[l,r]$ 求出所有**不能**被区间所有数整除的数量。

### 题解：

考虑询问区间中**能**被区间所有数的数量。

首先这类数一定是询问区间中最小的数，且必定为这段区间最大公因数的因数，但又因为这类数是区间最小值，且区间 $\gcd$ 必定小于等于区间最小值，故这类数一定为区间 $\gcd$。

所以我们可以用线段树统计出区间最小值，区间最小值个数，以及区间 $\gcd$.

在每次询问统计答案时，若区间最小值为区间 $\gcd$，则答案累加区间最小值最小值的个数即可。

线段树每次查询以及建树都是 $O(\log n)$ 的，所以总复杂度为 $O(q \log n)$.

### 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0; char ch = getchar();
	while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if(ch == '-') f = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
const int N = 1e5 + 10;
struct Segment {
	int g, cnt, minn;
}t[N << 2]; 
int n, q, a[N];
void pushup(int p) { //更新节点的值
	t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
	t[p].g = __gcd(t[p << 1].g, t[p << 1 | 1].g);
	if(t[p << 1].minn == t[p << 1 | 1].minn) t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
	else if(t[p << 1].minn < t[p << 1 | 1].minn) t[p].cnt = t[p << 1].cnt;
	else if(t[p << 1 | 1].minn < t[p << 1].minn) t[p].cnt = t[p << 1 | 1].cnt; 
}
void build(int p, int l, int r) { //建树
	int mid = l + r >> 1;
	if(l == r) {
		t[p].cnt = 1;
		t[p].g = a[l];
		t[p].minn = a[l]; 
	}
	else {
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		pushup(p);	
	}
}
Segment query(int p, int l, int r, int x, int y) { // 查询
	if(l > y || r < x) return (Segment){0, 0, 1000000000};
	if(x <= l && r <= y) return t[p];
	int mid = l + r >> 1;
	Segment lc = query(p << 1, l, mid, x, y);
	Segment rc = query(p << 1 | 1, mid + 1, r, x, y);
	Segment tmp;
	tmp.minn = min(lc.minn, rc.minn);
	tmp.g = __gcd(lc.g, rc.g);
	if(lc.minn == rc.minn) tmp.cnt = lc.cnt + rc.cnt;
	else if(lc.minn < rc.minn) tmp.cnt = lc.cnt;
	else if(rc.minn < lc.minn) tmp.cnt = rc.cnt; 
	return tmp;
}
int main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n);
	q = read();
	while(q --) {
		int l, r;
		l = read(), r = read();
		Segment answer = query(1, 1, n, l, r);
		int ans = 0;
		if(answer.minn == answer.g) ans = answer.cnt; //处理答案
		cout << r - l + 1 - ans << endl;
	}
	return 0;
}

```

---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF474F) & [Problem](//www.luogu.com.cn/problem/CF474F)

## 题目大意

- 给定长度为 $n$ 的序列 $s$。
- 有 $t$ 次询问，每次询问给定 $l,\ r$，求出对于 $l\leq i\leq r$，存在一个 $l\leq k\leq r$，使得 $s_i\nmid s_k$ 的 $i$ 的个数。
- $1\leq n,\ t\leq 10^5$，$1\leq s_i\leq 10^9$

## 解题思路

考虑求出取 $l\leq i\leq r$，对于任意的 $l\leq k\leq r$，都满足 $s_i\mid s_k$ 的 $i$ 的个数，再用 $r-l+1$ 减去求出的数量即可。

根据条件，$s_i\mid s_l,\ s_i\mid s_{l+1},\ \cdots,\ s_i\mid s_r$，则 $s_i\mid\gcd_{k=l}^rs_k$，又因为 $s_i$ 也在 $\{s_l,\ s_{l+1},\ \cdots,\ s_r\}$ 中，则 $s_i=\gcd_{k=l}^rs_k=\min_{k=l}^rs_k$。

使用线段树维护区间最大公因数，以及区间中等于最小值的数的个数，故还需要维护区间最小值。每次询问，判断区间最小值是否等于区间最大公因数，如果等于，设 $t$ 为区间中等于最小值的数的个数，则答案为 $r-l+1-t$，否则，区间中不存在既为最小值又为最大公因数的数，答案为 $r-l+1$。

时间复杂度 $\Theta(t\log n)$。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;
inline int Gcd(int x,int y){
    if(y==0)return x;
    else return Gcd(y,x%y);
}
int n,s[100001];
struct node{
    int gcd,minval,mintot;
    inline node operator+(node x)const{
        // 合并两段数的信息 
        node tmp; tmp.mintot=0;
        // 求出区间最大公因数和最小值
        tmp.gcd=Gcd(gcd,x.gcd);
        tmp.minval=min(minval,x.minval);
        // 若区间最小值等于最终最小值，就把数量加入总区间最小值个数
        if(tmp.minval==minval)tmp.mintot+=mintot;
        if(tmp.minval==x.minval)tmp.mintot+=x.mintot;
        return tmp;
    }
}tree[400001];
void work(int id,int l,int r){
    if(l==r){
        tree[id]={s[l],s[l],1};
        return;
    }
    int mid=l+r>>1;
    work(id<<1,l,mid); work((id<<1)+1,mid+1,r);
    // 合并区间
    tree[id]=tree[id<<1]+tree[(id<<1)+1];
}
node query(int id,int L,int R,int l,int r){
    if(l==L&&r==R)return tree[id];
    int mid=L+R>>1;
    if(l<=mid&&r<=mid)return query(id<<1,L,mid,l,r);
    if(l>mid&&r>mid)return query((id<<1)+1,mid+1,R,l,r);
    return query(id<<1,L,mid,l,mid)+query((id<<1)+1,mid+1,R,mid+1,r);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",s+i);
    work(1,1,n);
    int t; scanf("%d",&t);
    while(t--){
        int l,r; scanf("%d%d",&l,&r);
        node tmp=query(1,1,n,l,r);
        if(tmp.gcd!=tmp.minval)printf("%d\n",r-l+1);
        else printf("%d\n",r-l+1-tmp.mintot);
    }
    return 0;
}
```

---

## 作者：DPair (赞：0)

提供一种好懂但不优的解法。

## 【思路】
首先分析查询的本质。

其实可转化为问 **要求问一个区间内有多少个数是其他所有数的因数** 。

显然这个数是区间 $gcd$ ，这个可以用线段树维护。

那么我们现在就需要知道 **一个区间中出现某个数的次数** 。

本蒟蒻表示不会。

那我们看一看这个数有什么性质：

显然 $gcd(x,y)\le x,y$ 。

因此一个区间的 $gcd$ 若存在于该区间内，必为该区间的最小值。

最小值出现次数，这个好统计，也用线段树就可以了。

那么对于每一次询问，查询其区间最小值及其出现次数，与区间 $gcd$ 即可。

判断区间 $gcd$ 是否与最小值相同，若不同，这说明区间 $gcd$ 不存在于该区间中，输出 $r-l+1$ ，否则有要减去一个等于 **最小值即gcd出现次数的** 的值。

然后就做完了，而且没有修改只有询问，很好实现。

## 【代码】
（~~不要问我为什么变量名是 bruh 和 dude~~）
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}

template <typename T>
inline T mn(T x, T y) {return x < y ? x : y;}
template <typename T>
inline T mx(T x, T y) {return x > y ? x : y;}
template <typename T>
inline void chmin(T &x, T y) {(x > y) && (x = y);}
template <typename T>
inline void chmax(T &x, T y) {(x < y) && (x = y);}

LL gcd(LL x, LL y){return !y ? x : gcd(y, x % y);}
inline LL lcm(LL x, LL y){return x / gcd(x, y) * y;}
typedef pair <LL, int> pi;
int n;
LL a[100005];
struct SegTree{//线段树
    pi num[400005];
    LL sig[400005];
    inline void pushup(int rt){
        sig[rt] = gcd(sig[rt << 1], sig[rt << 1 | 1]);
        if(num[rt << 1].first == num[rt << 1 | 1].first) num[rt] = make_pair(num[rt << 1].first, num[rt << 1].second + num[rt << 1 | 1].second);
        else{
            if(num[rt << 1].first < num[rt << 1 | 1].first) num[rt] = num[rt << 1];
            else num[rt] = num[rt << 1 | 1];
        }
    }
    #define LSON rt << 1, l, mid
    #define RSON rt << 1 | 1, mid + 1, r
    void build(int rt, int l, int r){
        if(l == r){
            num[rt] = make_pair(a[l], 1);
            sig[rt] = a[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(LSON);build(RSON);
        pushup(rt);
    }
    pi query_mn(int rt, int l, int r, int x, int y){
        if(x <= l && r <= y) return num[rt];
        int mid = (l + r) >> 1;
        if(x <= mid && y > mid){
            pi q1 = query_mn(LSON, x, y), q2 = query_mn(RSON, x, y);
            if(q1.first == q2.first) return make_pair(q1.first, q1.second + q2.second);
            else {
                if(q1.first < q2.first) return q1;
                else return q2;
            }
        }
        if(x <= mid) return query_mn(LSON, x, y);
        if(y > mid) return query_mn(RSON, x, y);
        return make_pair(0ll, 0);
    }
    LL query_sig(int rt, int l, int r, int x, int y){
        if(x <= l && r <= y) return sig[rt];
        int mid = (l + r) >> 1;LL ret = 0;
        if(x <= mid) ret = gcd(ret, query_sig(LSON, x, y));
        if(y > mid) ret = gcd(ret, query_sig(RSON, x, y));
        return ret;
    }
}t;

int main(){
    read(n);
    for (register int i = 1;i <= n;i ++) read(a[i]);
    t.build(1, 1, n);
    int Q;read(Q);
    while(Q --){
        int l, r;read(l);read(r);
        LL bruh = t.query_sig(1, 1, n, l, r);
        pi dude = t.query_mn(1, 1, n, l, r);
        if(bruh ^ dude.first) fprint(r - l + 1, 10);
        else fprint(r - l + 1 - dude.second, 10);
    }
}
```

---

## 作者：封禁用户 (赞：0)

小蒟蒻来水一发题解 QωQ

# 题意
给出区间，有多少个数是其他所有数的约数？

显然自己是自己的约数，所以也可以改成

$$\sum_{i=l}^{r}[a_i=\gcd]$$

# 思路
$\gcd$ 我就干脆直接用了 $\tt st$ 表维护。预处理就是 $\mathcal O(n\log^2n)$ 了，真糟糕……但是 $\gcd$ 的 $\mathcal O(\log n)$ 复杂度蛮粗略的，所以应该实际上不是很大。

接下来查询数量呢？我有个不太自然的想法，将树上倍增 $\tt lca$ 的思想拿过来用一用。我把大区间拆成 $\mathcal O(\log n)$ 个小区间行不行？

我们用 $\gcd[l_0,r_0]=\gcd[l,r]$ 作为唯一判断依据，如果为真，则累加 $[l_0,r_0]$ 中与 $\gcd[l_0,r_0]$ 相等的数字的数量。因为 $\gcd[l_0,r_0]>\gcd[l,r]$ 时一定是一个都没有的。由于 $[l_0,r_0]$ 是 $[l,r]$ 的子区间，不可能 $\gcd[l_0,r_0]<\gcd[l,r]$ 滴。

所以，我们再搞一个 $\text{cnt}$ 与 $\tt st$ 表配合，存储一下该区间内，有多少个数等于 $\tt gcd$ 。显然跟 $\tt gcd$ 预处理时间相比微不足道。

总复杂度 $\mathcal O(n\log^2n+q\log n)$ ，常数极小，本人靠它暂时混了一个最优解。现在是 $\tt 2020/08/13$ 下午 $4:50$ ，留作纪念。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long int_;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(int x){
	if(x > 9) writeint(x/10);
	putchar((x%10)^48);
}
inline int __gcd(int a,int b){
	while(b) a %= b, swap(a,b); return a;
}

const int MaxN = 100005, infty = (1<<30)-1;
int st[20][MaxN], cnt[20][MaxN], lg2[MaxN];

int main(){
	int n = readint(); lg2[0] = -1;
	for(int i=1; i<=n; ++i){
		st[0][i] = readint();
		cnt[0][i] = 1; // itself
		lg2[i] = lg2[i>>1]+1;
	}
	for(int j=0; (2<<j)<=n; ++j)
	for(int i=1; i+(2<<j)-1<=n; ++i){
		st[j+1][i] = __gcd(st[j][i],st[j][i+(1<<j)]);
		if(st[j][i] == st[j+1][i])
			cnt[j+1][i] += cnt[j][i];
		if(st[j][i+(1<<j)] == st[j+1][i])
			cnt[j+1][i] += cnt[j][i+(1<<j)];
	}
	int q = readint();
	while(q --){
		int l = readint(), r = readint();
		int g = lg2[r-l+1], ans = 0;
		g = __gcd(st[g][l],st[g][r-(1<<g)+1]);
		for(int j,i=l; i<=r; ){
			j = (r+1-i)&(i-r-1); // lowbit
			j = lg2[j]; // log 数组派上用场！
			if(st[j][i] == g)
				ans += cnt[j][i];
			i += (1<<j);
		}
		writeint(r-l+1-ans), putchar('\n');
	}
	return 0;
}
```

---

## 作者：Genius_Z (赞：0)

[$\Large\color{violet}{Bl}\color{pink}{og}$](http://geiz-revive.github.io/)

这题的题意是要求出不能整除区间内所有数的个数，正难则反一下就变成了区间长度减去能整除区间内所有数的个数，显然这个数就是区间的$gcd$（窝太菜了一开始还以为可以是$gcd$的约数，后来发现是窝傻了），然后就可以发现这个$sum$跟$gcd$是具有可加性的，之后就大力上线段树就完事了。

目前是本题最优解，欢迎超越。

维护部分的代码：

```cpp
node operator +(node a, node b) {
	node c;
	c.gcd = gcd(a.gcd, b.gcd);
	c.sum = (a.gcd == c.gcd)*a.sum + (b.gcd == c.gcd)*b.sum;
	return c;
}
```

$\large Code:$

```cpp
#pragma region revive
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#define inl inline
#define re register int
#define fa(x) t[x].fa
#define son(x,y) t[x].child[y]
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define ll long long
const int inf = 0x3f3f3f3f;
#define lowbit(x) ((x) & (-x))
using namespace std;
#ifndef _DEBUG
#define getchar() (*(IOB.in.p++))
#define putchar(c) (*(IOB.out.p++)=(c))
#define io_eof() (IOB.in.p>=IOB.in.pend)
struct IOBUF { struct { char buff[1 << 26], *p, *pend; }in; struct { char buff[1 << 26], *p; }out; IOBUF() { in.p = in.buff; out.p = out.buff; in.pend = in.buff + fread(in.buff, 1, 1 << 26, stdin); }~IOBUF() { fwrite(out.buff, 1, out.p - out.buff, stdout); } }IOB;
#endif
template<typename IO>
inl void write(IO x) {
	if (x == 0) return (void)putchar('0');
	if (x < 0)putchar('-'), x = -x;
	static char buf[30];
	char* p = buf;
	while (x) {
		*(p++) = x % 10 + '0';
		x /= 10;
	}
	while (p > buf)putchar(*(--p));
}
inl void writestr(const char *s) { while (*s != 0)putchar(*(s++)); }
template<typename IO>inl void writeln(IO x) { write(x), putchar('\n'); }
template<typename IO>inl void writesp(IO x) { write(x), putchar(' '); }
inl int readstr(char *s) {
	char *begin = s, c = getchar();
	while (c < 33 || c>127) {
		c = getchar();
	}
	while (c >= 33 && c <= 127) {
		*(s++) = c;
		c = getchar();
	}
	*s = 0;
	return s - begin;
}
template<typename IO>
inl IO read() {
	IO x = 0;
	register bool w = 0;
	register char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') w = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return w ? -x : x;
}
#pragma endregion
inl int gcd(int x, int y) { if (x < y)swap(x, y); return y ? gcd(y, x%y) : x; }
struct node {
	int gcd, sum;
}t[500001];
node operator +(node a, node b) {
	node c;
	c.gcd = gcd(a.gcd, b.gcd);
	c.sum = (a.gcd == c.gcd)*a.sum + (b.gcd == c.gcd)*b.sum;
	return c;
}
int a[100001];
inl void maintain(int x) { t[x] = t[x << 1] + t[x << 1 | 1]; }
inl void build(int k, int l, int r) {
	if (l == r) { return (void)(t[k].gcd = a[l], t[k].sum = 1); }
	re mid = l + r >> 1;
	build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r);
	maintain(k);
}
inl node query(int k, int l, int r, int x, int y) {
	if (l >= x && r <= y)return t[k];
	re mid = l + r >> 1;
	node ans = { 0,0 };
	if (x <= mid)ans = ans + query(k << 1, l, mid, x, y);
	if (y > mid)ans = ans + query(k << 1 | 1, mid + 1, r, x, y);
	return ans;
}
signed main() {
	re n = read<int>(), m;
	for (re i = 1; i <= n; i++)a[i] = read<int>();
	build(1, 1, n);
	m = read<int>();
	while (m--) {
		re x = read<int>(), y = read<int>();
		writeln(y - x + 1 - query(1, 1, n, x, y).sum);
	}
}
```



---

## 作者：__Hacheylight__ (赞：0)

发现全网竟没有一篇分块题解。。。

看数据范围，有没有修改，感觉分块应该能过。。。

显然答案就是区间长度减去这个区间内值为 $\gcd$ 的数的个数

根据 $\mathsf{BZOJ~2821}$ 的经验，我们很快能够想到一种解决方案：

首先预处理每一个块的 $\gcd$，查询时每个块 $\gcd$ 后再和不完整块合并即可得到区间 $\gcd$

接下来就是查询区间内有多少个数等于某个确定的数了。

可以对每个数离散化，然后令 $f[i][j]$ 表示前 $i$ 个块中离散后的 $j$ 出现了几次

这样就完事了

不算 $map$ 和求 $\gcd$ 的话时间复杂度是 $O(q\sqrt n)$，亲测能过

```cpp
#include <bits/stdc++.h>
using namespace std ;
//#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(s, v, it) for (s::iterator it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (int i = head[x]; i; i = e[i].nxt)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pq priority_queue
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define iv inline void
#define enter cout << endl
#define siz(x) ((int)x.size())
#define file(x) freopen(#x".in", "r", stdin),freopen(#x".out", "w", stdout)
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int M = 320 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
const double eps = 1e-7 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int n, nn, q, len, num ;
int tmp[N], a[N], bl[N], l[M], r[M], f[M][N], g[M][M] ;
// f[i][j] 表示前i个块j出现的次数（离散），g[i][j] 表示块i到j的gcd为多少
mii m, mm ;

void lsh() {
	rep(i, 1, n) tmp[i] = a[i] ;
	sort(tmp + 1, tmp + n + 1) ;
	nn = unique(tmp + 1, tmp + n + 1) - (tmp + 1) ;
	rep(i, 1, n) m[a[i]] = lb(tmp + 1, tmp + nn + 1, a[i]) - tmp, mm[m[a[i]]] = a[i] ;
}

void build() {
	len = sqrt(n), num = (n - 1) / len + 1 ;
	rep(i, 1, n) bl[i] = (i - 1) / len + 1 ;
	rep(i, 1, num) l[i] = (i - 1) * len + 1, r[i] = i * len ; r[num] = n ;
	lsh() ;
	rep(i, 1, num) {
        rep(j, 1, nn) f[i][j] = f[i - 1][j] ;
        rep(j, l[i], r[i]) f[i][m[a[j]]]++ ;
	}
	rep(i, 1, num) {
		g[i][i] = a[l[i]] ;
		rep(j, l[i] + 1, r[i]) g[i][i] = __gcd(g[i][i], a[j]) ;
	}
	rep(i, 1, num) {
		rep(j, i + 1, num) g[i][j] = __gcd(g[i][j - 1], g[j][j]) ;
	}
}

int query(int x, int y) {
	int ans = 0, gc ;
    if (bl[x] == bl[y]) {
		gc = a[x] ;
		rep(i, x + 1, y) gc = __gcd(gc, a[i]) ;
		rep(i, x, y) ans += (a[i] == gc) ;
	} else {
		gc = g[bl[x] + 1][bl[y] - 1] ;
		rep(i, x, r[bl[x]]) gc = __gcd(gc, a[i]) ;
		rep(i, l[bl[y]], y) gc = __gcd(gc, a[i]) ;
		ans = f[bl[y] - 1][m[gc]] - f[bl[x]][m[gc]] ;
		rep(i, x, r[bl[x]]) ans += (a[i] == gc) ;
		rep(i, l[bl[y]], y) ans += (a[i] == gc) ;
	}
	return (y - x + 1) - ans ;
}

signed main(){
	scanf("%d", &n) ;
	rep(i, 1, n) scanf("%d", &a[i]) ;
	build() ;
	scanf("%d", &q) ;
	while (q--) {
		int l, r ; scanf("%d%d", &l, &r) ;
		printf("%d\n", query(l, r)) ;
	}
	return 0 ;
}


```

---

## 作者：piuke (赞：0)

看了看题解区没有ST表的，我来写一个。

### 题意
没什么好说的，注意文中 $|$ 符号指的是整除。

## 题解
显然，题意可以转化为求 $[l, r]$ 内有几个数为 $\gcd(a_l, a_{l+1},\dots,a_r)$ 。

考虑可以维护$\gcd$的数据结构，因为 $\gcd(a, b, c)=\gcd(\gcd(a,b),\gcd(b,c))$ ，所以可以使用ST表维护，不会的请右转[P3865 【模板】ST表](https://www.luogu.com.cn/problem/P3865)。也可以在[P1890 gcd区间](https://www.luogu.com.cn/problem/P1890)验证一下算法正确性。

这样可以很快的在 $O(n\log n\log a+q)$ 的复杂度中求得区间最大公约数，所以问题就在于求定区间内一个数的出现次数。

这里使用的是用 `lower_bound` 和 `upper_bound` 来求。先将原数组按照大小排序，第二关键字为下标大小，就能在 $O(2\times\log n)$ 中找到原数组中值为某数的范围。再在这个范围内找下标在 $[l,r]$ 区间内的，最坏仍为 $O(2\times\log n)$ 。

这里用到了加了 cmp 比较函数的二分查找，不了解的可以百度一下。

时间复杂度 $O(n\log n\log a+q\log n)$ 。

### 代码
~~不要在意`__gcd`啦~~

~~自动C++11~~
```cpp
#define MAXN 100005
int n;
int a[MAXN];
int st[MAXN][20];
int lg2[MAXN];
inline int query(int l, int r) {
    int k = lg2[r - l + 1];
    return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
}
struct node {
    int val, id;
    inline bool operator < (const node& rhs) const { return val == rhs.val ? id < rhs.id : val < rhs.val; }
    inline node() { }
    inline node(int val, int id) : val(val), id(id) { }
} s[MAXN];
signed main() {
    read(n);
    int q;
    for(int i = 1; i <= n; i++) {
        read(s[i].val), s[i].id = i;
        st[i][0] = s[i].val;
    }
    for(int j = 1; (1 << j) <= n; j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    for(int i = 1, x = 0, p2 = 1; i <= n; i++) {
        if((p2 << 1) == i) x++, p2 <<= 1;
        lg2[i] = x;
    }
    sort(s + 1, s + n + 1);
    read(q);
    while(q--) {
        int l, r; read(l, r);
        int d = query(l, r);
        int le = lower_bound(s + 1, s + n + 1, node(d, 0), [](node a, node b) { return a.val < b.val; } ) - s;
        int ri = upper_bound(s + 1, s + n + 1, node(d, 0), [](node a, node b) { return a.val < b.val; } ) - s;
        int idr = upper_bound(s + le, s + ri, node(d, r), [](node a, node b) { return a.id < b.id; } ) - s;
        int idl = lower_bound(s + le, s + ri, node(d, l), [](node a, node b) { return a.id < b.id; } ) - s;
        write(r - l + 1 - (idr - idl), '\n');
    }
}
```

---

