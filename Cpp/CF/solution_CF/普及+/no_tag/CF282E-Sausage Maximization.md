# Sausage Maximization

## 题目描述

The Bitlandians are quite weird people. They have their own problems and their own solutions. They have their own thoughts and their own beliefs, they have their own values and their own merits. They have their own dishes and their own sausages!

In Bitland a sausage is an array of integers! A sausage's deliciousness is equal to the bitwise excluding OR (the $ xor $ operation) of all integers in that sausage.

One day, when Mr. Bitkoch (the local cook) was going to close his BitRestaurant, BitHaval and BitAryo, the most famous citizens of Bitland, entered the restaurant and each ordered a sausage.

But Mr. Bitkoch had only one sausage left. So he decided to cut a prefix (several, may be zero, first array elements) of the sausage and give it to BitHaval and a postfix (several, may be zero, last array elements) of the sausage and give it to BitAryo. Note that one or both pieces of the sausage can be empty. Of course, the cut pieces mustn't intersect (no array element can occur in both pieces).

The pleasure of BitHaval and BitAryo is equal to the bitwise XOR of their sausages' deliciousness. An empty sausage's deliciousness equals zero.

Find a way to cut a piece of sausage for BitHaval and BitAryo that maximizes the pleasure of these worthy citizens.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
1000 1000
```

### 输出

```
1000
```

# 题解

## 作者：Zvelig1205 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF282E)

## Solution 1

此题的 $O(n^3)$ 暴力应该是很好想的。

直接暴力枚举区间所有前缀与后缀的位置，然后循环求解前缀异或和、后缀异或和，最后取 max 即可。

CodeForces 上第 33 个点 TLE 了。

```cpp
const int inf=1e5+7;
int n,ans,a[inf];
signed main()
{
	n=re();
	for(int i=1;i<=n;i++)
		a[i]=re();
	for(int i=0;i<=n;i++)
	{
		for(int j=1;j<=n+1;j++)
		{
			int pre=0,nex=0;
			for(int k=0;k<=i;k++)pre^=a[k];
			for(int k=j;k<=n+1;k++)nex^=a[k];
			ans=max(ans,pre^nex);
		}
	}
	wr(ans);
	return 0;
}
```

## Solution 2

既然都有前后缀了，前缀和优化应该很容易想到。

先 $O(n)$ 分别预处理出 $1\sim i$ 的前缀异或和以及 $i\sim n$ 的后缀异或和，这样在枚举前缀和后缀的位置的时候就不用再通过循环去求解了。

时间复杂度 $O(n^2)$，但同样在第 33 个点上 TLE 了。

~~CodeForces 上的数据居然不保证存在梯度~~

```cpp
const int inf=1e5+7;
int n,ans,a[inf];
int pre[inf],nex[inf];
signed main()
{
	n=re();
	for(int i=1;i<=n;i++)
		a[i]=re();
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]^a[i];
	for(int i=n;i>0;i--)
		nex[i]=nex[i+1]^a[i];
	for(int i=0;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			ans=max(ans,pre[i]^nex[j]);
	wr(ans);
	return 0;
}
```

## Solution 3

~~讲正解的时候到了。~~

通过观察上边的 $O(n^2)$ 暴力，发现复杂度瓶颈在于枚举端点。

那能不能不枚举，而是直接找最大值？

首先，我们需要了解什么是异或（如果你是大佬可以直接跳过）：

最简单的运算方式：

$$0\oplus 0=0,1\oplus 1=0,0\oplus 1=1,1\oplus 0=1,$$

有两种理解方式：

1. 相同得 $0$，不同得 $1$。

	显然。

1. 不进位加法。

	就是说，二进制表示下，$(1)_ 2+(1)_ 2=(10)_ 2$。如果我们把这个进位的 $1$ 去掉，那么就是这样：$(1)_ 2\oplus(1)_ 2=(0)_ 2$，然后就变成了“最简单的运算方式”中第二个的样子。

	至于其他三个，都没有发生进位现象。

所以要使异或和最大，应该满足什么样的条件？

尽可能在 **高位** 上 **多** 出现 $0\oplus1$ 或 $1\oplus0$ 这两种情况。

这里我们贪心的在高位上优先选择 $1$，显然这样贪心是对的，因为 $11\underset{k\text{个}0}{\underbrace{0\cdots0}}>10\underset{k\text{个}1}{\underbrace{1\cdots1}}$。

至于怎么决定选择的是 $1$ 而不是 $0$，这里要用到 [01Trie](https://oi-wiki.org/string/trie/)。

01Trie 中，左儿子代表 $0$，右儿子代表 $1$。

对于前缀异或和、后缀异或和，我们建两个 01Trie。

数据范围是 $10^{12}$，大概是 $2^{40}$ 左右，也就是 Trie 的最大深度。

```cpp
void insert(int &now,int k,int dep)
{//插入到字典树中
	if(now==0)now=++cnt;
	if(dep==41)
	{//插入结束
		T[now].end_=1;
		return;
	}
	if(k&1)insert(T[now].rc,k>>1,dep+1);//向右儿子插入
	else insert(T[now].lc,k>>1,dep+1);//向左儿子插入
}
void chuli(int &i,int k)
{//将原来要插入的数进行翻转处理，便于查询时在高位贪心
	int s=0,cnt=-1;
	while(k)
	{
		if(k&1)s=(s<<1|1);
		else s=(s<<1);
		k>>=1,cnt++;
	}
	while(cnt<40)cnt++,s<<=1;
	insert(i,s,0);
}
//可以为空，先插入两个 0
insert(rot1,0,0);insert(rot2,0,0);
for(int i=1;i<=n;i++)
{//前缀异或和
	pre[i]=pre[i-1]^a[i];
	chuli(rot1,pre[i]);
}
for(int i=n;i>0;i--)
{//后缀异或和
	nex[i]=nex[i+1]^a[i];
	chuli(rot2,nex[i]);
}
```

然后在查询时 **尽可能的** 一个向左走（找 $0$），一个向右走（找 $1$）。

```cpp
void ask(int x,int y,int dep)
{
	if(dep==41)return;
	if(T[x].lc&&T[y].rc)
		ans=ans<<1|1,ask(T[x].lc,T[y].rc,dep+1);
	else if(T[x].rc&&T[y].lc)
		ans=ans<<1|1,ask(T[x].rc,T[y].lc,dep+1);
	else if(T[x].lc&&T[y].lc)
		ans=ans<<1,ask(T[x].lc,T[y].lc,dep+1);
	else ans=ans<<1,ask(T[x].rc,T[y].rc,dep+1);
}
```

显然啊，这样查询是错的，hack：

```text
59
4 3 22 1 7 6 3 1 10 3 11 6 1 5 2 1 1 15 6 34 39 3 6 1 254 16 2 1 3 69 2 3 1 6 26 22 1 76 3 2 167 1 6 5 1 5 8 2 2 1 20 4 186 1 71 1 6 7 2
```

稍微思考了一下，在前缀后缀两棵 Trie 的左右儿子都存在的情况下，我们并不好确定哪一个更优，因此两边都跑一下，取 max 即可。

```cpp
void ask(int x,int y,int sum,int dep)
{
	if(dep==41)
	{
		ans=max(ans,sum);
		return;
	}
	bool pd=1;//一个最优性剪枝
	//当前两种情况成立的时候，后两种无论如何拿不到最优解，直接不需要搜
	if(T[x].lc&&T[y].rc)
		pd=0,ask(T[x].lc,T[y].rc,sum<<1|1,dep+1);
	if(T[x].rc&&T[y].lc)
		pd=0,ask(T[x].rc,T[y].lc,sum<<1|1,dep+1);
	if(pd&&T[x].lc&&T[y].lc)
		ask(T[x].lc,T[y].lc,sum<<1,dep+1);
	if(pd&&T[x].rc&&T[y].rc)
		ask(T[x].rc,T[y].rc,sum<<1,dep+1);
}
```

最坏的时间复杂度为 $O(n\log w)$，但实际上远不达这个上限。

~~空间复杂度不会算~~

采用动态开点，应该也是 $O(n\log w)$。

CodeForces 上给出的数据：

Time:342 ms,Memory:158800 KB.

最后，AC Code 奉上：

```cpp
const int inf=1e5+7;
int n,ans,a[inf];
int pre[inf],nex[inf];
struct Trie_01{
	int lc,rc;
}T[inf*100];
int rot1,rot2,cnt;
void insert(int &now,int k,int dep)
{
	if(now==0)now=++cnt;
	if(dep==41)return;
	if(k&1)insert(T[now].rc,k>>1,dep+1);
	else insert(T[now].lc,k>>1,dep+1);
}
void chuli(int &i,int k)
{
	int s=0,cnt=-1;
	while(k)
	{
		if(k&1)s=(s<<1|1);
		else s=(s<<1);
		k>>=1,cnt++;
	}
	while(cnt<40)cnt++,s<<=1;
	insert(i,s,0);
}
void ask(int x,int y,int sum,int dep)
{
	if(dep==41)
	{
		ans=max(ans,sum);
		return;
	}
	bool pd=1;
	if(T[x].lc&&T[y].rc)
		pd=0,ask(T[x].lc,T[y].rc,sum<<1|1,dep+1);
	if(T[x].rc&&T[y].lc)
		pd=0,ask(T[x].rc,T[y].lc,sum<<1|1,dep+1);
	if(pd&&T[x].lc&&T[y].lc)
		ask(T[x].lc,T[y].lc,sum<<1,dep+1);
	if(pd&&T[x].rc&&T[y].rc)
		ask(T[x].rc,T[y].rc,sum<<1,dep+1);
}
signed main()
{
	n=re();
	for(int i=1;i<=n;i++)
		a[i]=re();
	insert(rot1,0,0);insert(rot2,0,0);
	for(int i=1;i<=n;i++)
	{
		pre[i]=pre[i-1]^a[i];
		chuli(rot1,pre[i]);
	}
	for(int i=n;i>0;i--)
	{
		nex[i]=nex[i+1]^a[i];
		chuli(rot2,nex[i]);
	}
	ask(rot1,rot2,0,0);
	wr(ans);
	return 0;
}
```


---

## 作者：☯☯枫☯☯ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF282E)

~~既然没人发题解那就毫不客气地收下啦！~~

Update 2021.4.24：修复了时间复杂度错误。。

**题意简述：**

> 给你一个 $n$ 个整数的数组，你可以把它分成三段 ( 任意一段可以为空，满足 $l+mid+r=n$ 就行 )，求一种划分方法，使得 $l$,$r$ 内的所有值异或和最大。

**算法分析：Trie 树**

我们知道 Trie 树（又称字典树）善于解决字符串统计问题。但实际上，Trie 树同样可以用来解决部分二进制运算的问题，尤其是异或（不知道的同学请移步经典题：[Hdu4825 Xor Sum](http://acm.hdu.edu.cn/showproblem.php?pid=4825)）。我们可以把一个数的二进制看做一个01串，**从高位开始**插入字典树中，来解决相关问题。

对于本题，题目中要求最大的异或和。我们知道异或又叫“按位异或”，需要对每一个二进制位进行操作。那不就是对每一个字符进行操作了吗？用字典树呀！~~（但作为一道 CF 的题并不会这么水）~~

我们注意到题中要同时求前缀和后缀，相当于多组不同的询问。我们不可能对于每一种可能都重建字典树。枚举至少是 $\mathcal{O}(n^2)$ 级别的，更何况还要建字典树，那还不如直接暴力呢！怎么办呢？我们要对字典树进行**删除操作。**（删除操作可以参考 [CF706D Vasiliy's Multiset](https://www.luogu.com.cn/problem/CF706D)）具体的，由于二进制数存储的时候统一记录相同的位数，所以它们的结尾是可以确定的，即最大位数，所以我们无需额外记录结尾，转而用一个 $rec$ 数组记录每个节点被几个二进制数使用过。在删除某个数时，直接对这个数对应的每一个节点的 $rec-1$ 就可以了。

```cpp
inline void del(ll x) {//删除操作 
	int p=1;//根节点 
	for(reg int i=62; i>=0; i--){//从高位开始 
		bool k=(x&(1ll<<i));
		if(!rec[p] or !trie[p][k])return;
		p=trie[p][k];
		rec[p]--;//删除 
	}
}
```

那么，对于本题，具体应该怎么做呢？我们可以先计算并插入所有的后缀异或和 $bk_i$，然后从前往后扫，记录当前的前缀异或和 $cur$ ，删除后缀异或和，然后在字典树中查找和 $cur$ 对应的异或最大值（其实这一步就和 [CF706D Vasiliy's Multiset](https://www.luogu.com.cn/problem/CF706D)
一样了），同时更新 $ans$ 即可。

**记得把数组开到够大！**

下面是~~喜闻乐见的~~代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);i++)
inline ll read();
using namespace std;
const int N=1e5+10;
int n,trie[N*64][2],cnt=1,rec[N*64];
ll bk[N],a[N],ans;
inline void insert(ll x) {//插入 
	int p=1;//根节点 
	for(reg int i=62; i>=0; i--) {
		bool k=(x&(1ll<<i));
		if(!trie[p][k])trie[p][k]=++cnt;
		p=trie[p][k];
		rec[p]++;
	}
}
inline void del(ll x) {//删除操作 
	int p=1;//根节点 
	for(reg int i=62; i>=0; i--){//从高位开始 
		bool k=(x&(1ll<<i));
		if(!rec[p] or !trie[p][k])return;
		p=trie[p][k];
		rec[p]--;//删除 
	}
}
inline ll search(ll x){//模板不解释 
	int p=1;
	ll s=0;
	for(reg int i=62;i>=0;i--){
		bool k=(x&(1ll<<i));
		s<<=1ll;
		int &to=trie[p][k^1];
		if(!to or !rec[to]){
			if(rec[trie[p][k]] and trie[p][k])p=trie[p][k];
			else break;
		}
		else p=to,s|=1ll;
	}
	return s;
}
int main() {
	n=read();
	F(i,1,n)a[i]=read();
	for(reg int i=n; i>=1; i--)bk[i]=bk[i+1]^a[i],insert(bk[i]);
	//计算后缀异或和 bk ，并插入字典树 
	ll cur=0;
	ans=search(cur);//相当于查询 bk 的最大值 
	F(i,1,n){
		cur^=a[i];//维护前缀异或和 
		del(bk[i]);//删除后缀异或和 
		ans=max(ans,search(cur));//更新答案 
	}
	printf("%lld",ans);
	return 0;
}
inline ll read() {
	reg ll x=0;
	reg char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<3ll)+(x<<1ll)+(c^48),c=getchar();
	return x;
}
```

[AC](https://www.luogu.com.cn/record/48687234)

欢迎交流讨论，请点个赞哦~

---

## 作者：happybob (赞：2)

考虑 01-trie。

把每个前缀异或和变成二进制插入 01-trie，然后贪心地对后缀异或和搜索 01-trie。$10^{12} \approx 2^{40}$，注意空间复杂度。

显然 $2^p > \sum \limits_{i=0}^{p-1} 2^i$，所以每一个数从最高位开始往后判断是否可以使这一位为 $1$，如果可以那就取 $1$，一定最优。

时间 $O(n \log v)$，空间 $O(n \log v)$。

---

## 作者：Leap_Frog (赞：2)

### P.S.
看到题后感觉挺简单的，结果发现是 2200，然后吓傻了。  
然后一写，WA 了几发后就 A 了，感觉难度完全没有 2200 啊 ![](//xn--9zr.tk/xia)  

### Description.
求最长的前后缀使得它们没交集且 $\oplus$ 和最大。  

### Solution.
首先，不重合这个条件其实没用。  
考虑 $\oplus$ 的性质之一是 $x\oplus x=0$，所以中间重合部分对答案无贡献。  
相当于重合情况至少对应于一种不重合情况，所以是否重合和答案无关。  
然后，我们对这个序列做一个前后缀和，前缀和插入 trie 树，后缀和直接在 trie 上查询即可。  
然后就做完了，注意有空串情况。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
int n,ch[4000005][2],tt,rt;ll a[100005],s[100005],t[100005];
inline void ins(int &x,ll vl,int d=40)
{
	x?x:x=++tt;if(d<0) return;
	ins(ch[x][(vl>>d)&1],vl,d-1);
}
inline ll qry(int x,ll vl,int d=40)
{
	int nw;if(d<0) return 0;else nw=(vl>>d)&1;
	if(ch[x][!nw]) return qry(ch[x][!nw],vl,d-1)+(1ll<<d);
	else return qry(ch[x][nw],vl,d-1);
}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
	for(int i=n;i>=1;i--) t[i]=t[i+1]^a[i];
	for(int i=0;i<=n;i++) ins(rt,s[i]);
	ll rs=0;for(int i=1;i<=n+1;i++) rs=max(rs,qry(rt,t[i]));
	return printf("%lld\n",rs),0;
}
```

---

## 作者：Loser_Syx (赞：1)

膜拜一下 [huta0](https://www.luogu.com.cn/user/749665) 大佬 %%%

套路题。

不难想到预处理前后缀异或和，那么可以考虑枚举某一个缀，快速求出其对应异或和最大的另一个缀。

本篇题解枚举的是后缀，相对于当前的 $i$，我们需要找到一个前缀 $0 \leq j < i$ 使得异或和最大。

如果我们将当前的 $nxt_i$ 分解为二进制形式，那么我们一定要找出一个 $0 \leq j < i$ 的 $pre_j$ 使得它和 $nxt_i$ 能在最早的位上出现二进制位不同的情况（这样可以使异或和尽可能大，在此基础上继续选最早不同的，由于二进制使得当前 $2^k$ 一定大于 $\sum_{s=0}^{k-1} 2^s$ 的）。

考虑什么数据结构能快速找出呢？显然可以有 Trie 树，建字典树跑一下就好了。

```cpp
long long pre[101010], nxt[101010], a[101010], ans;
int t[6400010][2], len, er[101], q[101];
void insert() {
	int p = 0;
	for (int i = 0; i < 64; ++i) {
		if (!t[p][er[i]]) t[p][er[i]] = ++len;
		p = t[p][er[i]];
	}
}
long long find() {
	int p = 0; long long now = 0;
	for (int i = 0; i < 64; ++i) {
		if (!t[p][q[i] ^ 1]) now = now * 2 + q[i], p = t[p][q[i]];
		else now = now * 2 + (q[i] ^ 1), p = t[p][q[i] ^ 1];
	} return now;
}
signed main() {
	int n = read();
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		pre[i] = pre[i-1] ^ a[i];
		smax(ans, pre[i]);
	}
	for (int i = n; i; --i) {
		nxt[i] = nxt[i+1] ^ a[i];
		smax(ans, nxt[i]);
	}
	insert();
	for (int i = 1; i <= n; ++i) {
		int t = 64; long long no = nxt[i]; for (int j = 0; j < t; ++j) q[j]  = 0;
		while (no) {
			q[--t] = no % 2;
			no /= 2;
		} smax(ans, nxt[i] ^ find()); // if (i == 5) cout << find() << '\n';
		int s = 64; long long co = pre[i]; for (int j = 0; j < s; ++j) er[j] = 0;
		while (co) {
			er[--s] = co % 2;
			co /= 2;
		}
		insert();
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：黑影洞人 (赞：1)

# 01Trie 裸题

但是我还是 WA 了很多次。

错解 1：线性基

我一开还是认为既然是前缀，那么都可以取到，就全部扔进线性基里然后找一下最大值。

然而这种做法是错误的，因为线性基很可能不满足前缀连续性，于是很遗憾 #9 WA 了。

错解 2：模拟退火

我死活不想打正解，于是想到了模拟退火，就是处理完前缀和，随机找两个点然后查询。很遗憾，只能过掉小数据，和暴力的分一样。

正解 ：01Trie

我们只需要把前缀全部插入 01Trie 里，然后对于每个后缀查询一下在 01Trie 上的所有数字中，可以与给定值异或得到的最大值。

插入操作：

获取到每一位的情况后，依次往下找，如果那个点被选过了，那么往下走，否则就新开一个节点，每个节点用计数器统计一下覆盖的次数，方便后面的删除操作。（然而这题不用删除）

如果完全插入了，那么就在最后的节点标记一下值，避免反复查找。

查询操作：

按位向下找，如果能取反就取反，否则才取正。
```cpp
struct trie{
	int ch[N*M][2],num[N*M],val[N*M],cnt=1;
	void insert(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			if(!ch[u][v])ch[u][v]=++cnt;
			u=ch[u][v];
			num[u]++;
		}
		val[u]=x;
	}
	int query(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			if(ch[u][v^1]&&num[ch[u][v^1]])u=ch[u][v^1];
			else u=ch[u][v];
		}
		return x^val[u];
	}
}st;
```
还有要注意，如果只有一个数，那么我们要特判一下。

否则答案会输出 $0$。

上代码：

```cpp
#include<cstdio>
#include<algorithm>
#define N 114514
#define M 63
#define int long long
using namespace std;
int n,a[N],s[N],t[N],ans;
struct trie{
	int ch[N*M][2],num[N*M],val[N*M],cnt=1;
	void insert(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			if(!ch[u][v])ch[u][v]=++cnt;
			u=ch[u][v];
			num[u]++;
		}
		val[u]=x;
	}
	int query(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			if(ch[u][v^1]&&num[ch[u][v^1]])u=ch[u][v^1];
			else u=ch[u][v];
		}
		return x^val[u];
	}
}st;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	ans=max(ans,a[1]);
	ans=max(ans,a[n]);
	for(int i=1;i<=n;i++)s[i]=s[i-1]^a[i],st.insert(s[i]);
	for(int i=n;i>=1;i--)t[i]=t[i+1]^a[i],ans=max(ans,st.query(t[i]));
	printf("%lld",ans);
	return 0;
}



```


---

## 作者：Uuuuuur_ (赞：1)

这道题是一道 01Trie 的模版题，知识点不懂可以自行百度，就是字典树模版。

把所有前缀插入 01Trie，对每个后缀做一次最大值的查询。有人会问这样不会重叠吗？没事，由于异或性质，$A\oplus B\oplus B=A$，重叠部分会抵消掉。

别忘记前缀后缀是可以为空的。

时间复杂度 $O(n \log a_{max})$。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5;
const ll H = 45;
ll n;
ll pre[N], suf[N];
ll exi[N * (H + 5)][2];
ll cnt = 1;
ll a[N];
ll ans;
void insert(ll x) {
    ll p = 1;
    for (ll i = H; i >= 0; i--) {
        bool bx = (x >> i) & 1;
        if (!exi[p][bx]) exi[p][bx] = ++cnt;
       
        p = exi[p][bx];
    }
}
void query(ll x) {
    ll p = 1;
    ll sum = 0;
    for (ll i = H; i >= 0; i--) {
        bool bx = (x >> i) & 1;
        if (exi[p][!bx]) {
            sum += (1ll << i);
            p = exi[p][!bx];
        } else {
            p = exi[p][bx];
        }
    }
    ans = max(ans, sum);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    insert(0);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] ^ a[i];
        insert(pre[i]);
    }
    for (ll i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] ^ a[i];
    }
    for (ll i = 0; i <= n; i++) {
        query(suf[i]);
    }
    cout << ans;
    return 0;
}
```


---

## 作者：roger_yrj (赞：0)

先想想 $O(N^2)$ 做法。

统计一遍前缀和与后缀和，然后枚举即可。

那如何优化呢？

遇到这种异或的题，应该猜测是线性基或者 01Trie。这里我用的是 01Trie。

考虑枚举前缀，在前缀固定的情况下找到最优的后缀。我们只需要把所有不相交的后缀全部扔到一个 01Trie 上，然后每次尽量走异侧（也就是高位尽量为 $1$）。

时间复杂度 $O(N\log V)$。

---

## 作者：mango2011 (赞：0)

十分简单的字典树应用题。

我们可以预处理出前（后）缀异或和（$p$ 与 $s$），然后枚举前缀的位置 $i$，然后相当于我们要找一个 $s_j(j\ge i)$，使得 $s_j\bigoplus p_i$ 最大。直接寻找总复杂度是 $O(n^2)$ 的，考虑优化：

倒序枚举 $i$，把每一个后缀异或和都插入到字典树当中，对于一个查询的数 $x$，最高位到低位依次贪心，看看能不能取到 $1$ 并继续往下走即可（具体实现可以参考代码）。由于我们按照二进制对数进行了拆分，所以复杂度得到了明显的优化，变成 $O(n\log V)$，其中 $V$ 代表值域，本题中最大为 $10^{12}$。

注意不取前缀（后缀）的情况。

[评测记录](https://codeforces.com/contest/282/submission/271451340)

---

## 作者：_yi_ (赞：0)

# 题意简述

题目要求从一个给定的整数序列中，选择一个前缀和一个不相交的后缀，使得这两个子序列的异或和的最大值。即最大化前缀异或和与后缀异或和的异或结果。需要输出这个最大值。

# 解题思路

显然，出现了前后缀异或和这些区间问题，可以用前缀异或和来记录。记 $s[i]$ 为 $[1,i]$ 的异或和，那么 $[l,r]$ 上的异或和为 $s[r]\oplus s[l-1]$，这样可以 $O(1)$ 求得区间异或和。

考虑最朴素的做法，枚举 $i$ 为前缀长度，$j$ 为后缀长度。（$i,j\geq0,i+j\le n$）直接统计即可。

考虑只枚举 $i$，找到当前缀长度为 $i$ 时的最大贡献。如果我们把满足后缀长度为 $0\le j\le n-i$ 的后缀异或和放入一个 $\text{Trie}$ 树中，便可贪心地从高位到低位钦定答案。

此时复杂度瓶颈在于建 $\text{Trie}$ 树。不难发现，对于 $i+1$ 时建的 $\text{Trie}$ 树，$i$ 时的 $\text{Trie}$ 树仅仅是多了一个插入了一个 $s[i]\oplus s[n]$，显然这是 $O(\log A)$ 的。从 $i$ 大到小统计一遍最大贡献即可。总时间复杂度 $O(n\log A)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5;
ll a[N+2],s[N+2];
int tot;
int t[40*N+2][2];
void insert(ll x){
    for(int i=39,p=0;i>=0;i--){
        int temp=(x>>i)&1;
        if(!t[p][temp]){
            t[p][temp]=++tot;
        }
        p=t[p][temp];
    }
}
ll query(ll x){
    ll ans=0;
    for(int i=39,p=0;i>=0;i--){
        int temp=(x>>i)&1;
        if(t[p][temp^1]){
            p=t[p][temp^1];
            ans+=(1ll<<i);
        }
        else{
            p=t[p][temp];
        }
    }
    return ans;
}
int main(){
    // freopen("data.in","r",stdin);
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]^a[i];
    }
    ll ans=0;
    for(int i=n;i>=0;i--){
        ll t=s[n]^s[i];
        insert(t);
        ans=max(ans,query(s[i]));
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

简单题。

考虑从后往前考虑每个前缀。

显然后缀的决策集合只增不减。

那么就变成了一个加入数和维护最大异或值的问题，考虑从高位到低位丢 Trie 树上贪心即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+114;
struct Trie{
    int ls,rs;
    Trie(){
        ls=rs=0;
    }
}tr[maxn*50];
int tot;
void insert(int &cur,int w,int x){
    if(cur==0) cur=++tot;
    if(w==0) return ;
    if(w&x) insert(tr[cur].rs,w>>1,x);
    else insert(tr[cur].ls,w>>1,x);
}
int query(int cur,int w,int x){
    if(w==0) return 0;
    if(w&x){
        if(tr[cur].ls!=0) return query(tr[cur].ls,w>>1,x)+w;
        else return query(tr[cur].rs,w>>1,x);
    }
    else{
        if(tr[cur].rs!=0) return query(tr[cur].rs,w>>1,x)+w;
        else return query(tr[cur].ls,w>>1,x);
    }
}
int pre[maxn],suf[maxn],a[maxn],n,rt;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pre[i]=pre[i-1]^a[i];
    }
    for(int i=n;i>=1;i--) suf[i]=suf[i+1]^a[i];
    int ans=0;
    tot++;
    rt=1;
    for(int i=n;i>=0;i--){
        insert(rt,(1ll<<40),suf[i+1]);
        ans=max(ans,query(1,(1ll<<40),pre[i]));
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

