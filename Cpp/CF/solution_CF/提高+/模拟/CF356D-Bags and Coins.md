# Bags and Coins

## 题目描述

When you were a child you must have been told a puzzle of bags and coins. Anyway, here's one of its versions:

A horse has three bags. The first bag has one coin, the second bag has one coin and the third bag has three coins. In total, the horse has three coins in the bags. How is that possible?

The answer is quite simple. The third bag contains a coin and two other bags.

This problem is a generalization of the childhood puzzle. You have $ n $ bags. You know that the first bag contains $ a_{1} $ coins, the second bag contains $ a_{2} $ coins, ..., the $ n $ -th bag contains $ a_{n} $ coins. In total, there are $ s $ coins. Find the way to arrange the bags and coins so that they match the described scenario or else state that it is impossible to do.

## 说明/提示

The pictures below show two possible ways to solve one test case from the statement. The left picture corresponds to the first test case, the right picture corresponds to the second one.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF356D/1307eb982020a5ba55b375c0d5ee7ef3aa5a111f.png)

## 样例 #1

### 输入

```
3 3
1 3 1
```

### 输出

```
1 0
1 2 3 1
1 0
```

## 样例 #2

### 输入

```
3 3
1 3 1
```

### 输出

```
1 0
2 1 3
0 1 1
```

## 样例 #3

### 输入

```
1 2
1
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
8 10
2 7 3 4 1 3 1 2
```

### 输出

```
2 0
1 2 1 4
0 2 7 8
0 2 5 6
1 0
3 0
1 0
2 0
```

# 题解

## 作者：IGA_Indigo (赞：5)

## 题意分析
题目翻译概括的其实很到位，管他英文上一些什么马啊袋子硬币的，其实就是告诉你有 $n$ 个点，让你构造一个森林，满足每个点的点权为 $a[i]$，总点权为 $s$，让你自己构造点的连接方式和各自点权。
## 大体思路
题目告诉我们只需要输出一个可能性，所以我们只需要找到一个比较好实现的特例，可以处理的草率一点。

#### 处理
首先如果有其中一个点需要的点权超过了总点权，那他肯定不行，直接输出 $-1$ 然后结束。

然后 dp 处理一下。
### 状态设置
$f[i][j]$ 表示前 $i$ 个数和为 $j$ 是否可能。

很明显我们可以滚动优化到 $f[j]$ 表示和为 $j$ 是否可能。
### 状态转移
很显然我们可以得到 $f[j]|=f[j-a[i]]$ 的转移方程，但是在这里会 TLE ，所以我们使用 bitset 优化一下。得到 $f|=f<<a[i]$，用另一个 bitset $bh$ 记录一下当前状态是由那个数字转移过来的，后面要用。
#### 处理
最后判断下如果总点权达不到（$f[s]==0$），直接输出 $-1$ 结束。
### 构造
我们把所有点都变成一棵只有根节点的树，做成一片森林，然后从大到小依次添加这些点到最后答案里，并将他们的权值变成他们需要的权值。
```cpp
while(s>0){//把每个点都弄成一棵只有根的树，然后把权值变成他的要求（因为只需要构造一个，找个特例就行）
	vis[nxt[s]]=1;
	a[nxt[s]].wei=a[nxt[s]].s;
	s-=a[nxt[s]].wei;
}//从大到小处理一定能构成一个符合条件的森林
```
然后把没有访问的节点全都放在权值最大的点后面，构成一条链。更新他们的权值为自己的权值减去儿子节点的权值。
```cpp
for(int i=2;i<=n;i++){
	if(!vis[i]){
		q.push(a[i].b);
	}
}//因为大的可以套小的，所以我们把没访问到的点全都放在最大的点后面，构成一条链（还是因为只需要构造一个可能）
while(q.size()>1){
	int fa=q.front();
	q.pop();
	int x=q.front();
	a[fa].wei=a[fa].s-a[x].s;
	a[fa].son=x;//记录一下子结点
}//如果到q的最后一个元素，pop之后x访问会超界，所以我们在循环外处理
a[q.front()].wei=a[q.front()].s;
```
最后按照要求输出答案即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int s,b;//存点，s是需要的权值，b代表原下标
	int wei;//实际权值
	int son;
}a[70005];
queue<int> q;
bool cmp1(node aa,node bb){
	return aa.s>bb.s;
}
bool cmp2(node aa,node bb){
	return aa.b<bb.b;
}
bitset<70005> f;
bitset<70005> bh;
int nxt[70005];
bool vis[70005]; 
int main(){
	int n,s;
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i].s;
		a[i].b=i;
	}
	sort(a+1,a+1+n,cmp1);
	s-=a[1].s;//首先必须有最大的那个数
	q.push(a[1].b);//先放在队列里 
	if(s<0){//如果最大的那个点比s还大就输出-1
		cout<<-1;
		return 0;
	}
	f[0]=1;
	for(int i=2;i<=n;i++){//第一个已经取了，从第二个开始
		bh=f;
		f|=f<<a[i].s;//bitset优化
		bh^=f;//bh是变化量
		for(int j=bh._Find_first();j<70005;j=bh._Find_next(j)){
			nxt[j]=i;
		}//用这两个bitset带的函数遍历所有1的位置 
	}
	if(f[s]==0){//证明无解 
		cout<<-1;
		return 0;
	}
	//输出答案
	while(s>0){//把每个点都弄成一棵只有根的树，然后把权值变成他的要求（因为只需要构造一个，找个特例就行）
		vis[nxt[s]]=1;
		a[nxt[s]].wei=a[nxt[s]].s;
		s-=a[nxt[s]].wei;
	}
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			q.push(a[i].b);
		}
	}//因为大的可以套小的，所以我们把没访问到的点全都放在最大的点后面，构成一条链（还是因为只需要构造一个可能） 
	sort(a+1,a+1+n,cmp2);//恢复成下标排序
	while(q.size()>1){
		int fa=q.front();
		q.pop();
		int x=q.front();
		a[fa].wei=a[fa].s-a[x].s;
		a[fa].son=x;//记录一下子结点
	}//如果到q的最后一个元素，pop之后x访问会超界，所以我们在循环外处理
	a[q.front()].wei=a[q.front()].s;
	for(int i=1;i<=n;i++){
		cout<<a[i].wei<<" ";
		if(a[i].son){
			cout<<1<<" "<<a[i].son<<endl;//因为我们找的特例一个节点顶多有一个儿子，所以儿子数直接是1就行 
		}
		else{
			cout<<0<<endl; 
		}
	}
	return 0;
} 
```

---

## 作者：selcouth (赞：3)

# CF356D Bags and Coins

***Tag：背包 dp，构造，bitset 优化***

给定长 $n$ 的数组 $a$ 和一个数 $s$，构造一个森林，每个点 $i$ 有非负点权 $c_i$，要求点 $i$ 的子树中点权之和恰好为 $a_i$，并且所有点权的和为 $s$。

输出答案时，对于每个 $i$，先输出 $c_i$，再输出 $k_i$ 表示 $i$ 的儿子数量，然后依次输出 $i$ 的儿子们。无解输出 $-1$。

## 解题思路：

### 1. 初步思路

由于这是一个构造题，我们可以考虑任何情况下有没有一种特殊的构造能够满足题目要求：

- 首先，既然这要求是一个森林，我们可以搞一堆点（即一棵树只有一个节点），使他们满足和为 $s$。
- 其次，如果有一些点并没有被使用，我们只需要将其放在 $a$ 的值最大的节点之下即可，大的套小的构成一条链。

因此，$a$ 的值在转移的时候应该先从大到小排序，并且最大的那个点一定是链的根节点。

但是如果最大的点比 $s$ 都大，那么直接输出 $-1$ 即可。

### 2. dp 设计

于是我们可以设计出状态：

- $dp_{i, j}$ 表示考虑前 $i$ 数，是否存在和为 $j$ 的方案。
- **状态转移**：$dp_{i, j} = dp_{i-1, j}\space |\space dp_{i-1, j-a_i}$。

朴素的方法如下：

```cpp
dp[0] = 1;
for(int i = 1; i<=n; i++)
    for(int j = n; j>=1; j++)
        dp[j] |= dp[j-a[i].val];
```

但是这样时间会爆炸，由于这是 `bool` 类型的 dp 数组，我们可以采用 `bitset` 优化掉第二层循环。

然后我们需要记录某个状态是从哪个元素转移而来的，定义一个 `dfn` 数组，通过更新后的 `dp` 数组和更新前的进行异或即可查找到本次更新的状态。

以下是 dp 的代码，注意要先将最大的 $a$ 排除出去。

```cpp
sort(a+1, a+1+n, Node::compare);
s -= a[1].val;

dp[0] = 1;
for(int i = 2; i<=n; i++)
{
    upd = dp;
    dp |= dp << a[i].val;
    upd ^= dp;
    for(int j = upd._Find_first(); j < maxn; j=upd._Find_next(j))
        dfn[j] = i; // 记录该状态是由哪个数字转移而来的
}
```

*`__Find_first`：从右到左查找第一个 $1$ 所在的位置。*

*`__Find_next`：从 $j$ 开始从右到左查找第一个 $1$ 所在的位置。*

如此，若不可能有和为 `s` 的情况，即 $dp_s$ 为假，则直接输出 $-1$。

### 3. 构造森林

如果有一堆点满足和为 $s$，那么我们直接依次查找 `dfn[s-a[i]]`，由于这些数只有一个点，所以我们要将将第 $i$ 个元素的权值设置成它的容量。

注意此时 $s$ 已经减去了最大的点了：

```cpp
while(s != 0)
{
    vis[dfn[s]] = true;
    a[dfn[s]].w = a[dfn[s]].val;
    s -= a[dfn[s]].val;
}
```

没有被访问过的点那自然是要塞到最大的根节点下面组成一条链的，这里我们通过一个队列从大到小更新前面的子节点和权值。

如果其父节点的 $a$ 值为 $a_i$，其子节点的值为 $a_j$，那么父节点的权值 $c_i = a_i-a_j$。

```cpp
// 对于单个节点不能独立成树的情况，把他们塞到最大的节点下方。
// 队列中的第一个元素一定是最大的。
for(int i = 1; i<=n; i++)
    if(!vis[i]) q.push(a[i].id);

sort(a+1, a+1+n, [](Node a, Node b) -> bool
{
    return a.id < b.id;
});

while(q.size() > 1)
{
    int cur = q.front();
    q.pop();

    a[cur].w = a[cur].val - a[q.front()].val;
    a[cur].nxt = q.front();
}

a[q.front()].w = a[q.front()].val;
```

最后输出整个问题就解决了！完结撒花。*★,°*:.☆(￣▽￣)/$:*.°★* 

## 源代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
int n, s, dfn[maxn];
bool vis[maxn];
struct Node
{
    int id, val, w, nxt;
    static bool compare(Node a, Node b)
    {
        return a.val > b.val;
    }

    static bool restore(Node a, Node b)
    {
        return a.id < b.id;
    }
} a[maxn];

queue<int> q;
bitset<maxn> dp, upd;
// dp[i][j] 表示前 i 个节点中是否存在若干节点使和为 j
// 压成 1 维的之后使用 bitset 优化

int main()
{
    cin >> n >> s;
    for(int i = 1; i<=n; i++)
    {
        cin >> a[i].val, a[i].id = i;
        if(a[i].val > s)
        {
            cout << -1;
            return 0;
        }
    }

    sort(a+1, a+1+n, Node::compare);
    s -= a[1].val;

    dp[0] = 1;
    for(int i = 2; i<=n; i++)
    {
        upd = dp;
        dp |= dp << a[i].val;
        upd ^= dp;
        for(int j = upd._Find_first(); j < maxn; j=upd._Find_next(j))
            dfn[j] = i; // 记录该状态是由哪个数字转移而来的
    }
    
    if(dp[s] == false) // 不可能出现和为 s 的情况
    {
        cout << -1;
        return 0;
    }

    while(s != 0)
    {
        vis[dfn[s]] = true;
        a[dfn[s]].w = a[dfn[s]].val;
        s -= a[dfn[s]].val;
    }
    
    // 对于单个节点不能独立成树的情况，把他们塞到最大的节点下方。
    // 队列中的第一个元素一定是最大的。
    for(int i = 1; i<=n; i++)
        if(!vis[i]) q.push(a[i].id);
    
    sort(a+1, a+1+n, Node::restore);

    while(q.size() > 1)
    {
        int cur = q.front();
        q.pop();

        a[cur].w = a[cur].val - a[q.front()].val;
        a[cur].nxt = q.front();
    }
    a[q.front()].w = a[q.front()].val;

    for(int i = 1; i<=n; i++)
    {
        if(a[i].nxt != 0) cout << a[i].w << ' ' << 1 << ' ' << a[i].nxt << '\n';
        else cout << a[i].w << ' ' << 0 << '\n';
    }

    return 0;
}
```

---

## 作者：hytmnt (赞：2)

注意到子树最大的结点必为根。

对剩下的结点考虑 $s^2$ 背包dp，设 $dp[i][j]$ 表示前 $i$ 个结点中是否存在若干结点使其和为 $j$，这些结点作为森林的根。

可以压掉 $i$ 这一维，并记录是从哪里转移的，就可以获得方案。

考虑构造方案，把非根结点按子树大小从大到小塞到子树最大的结点为根的树里形成一条链。

用bitset优化一下就能过了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int BUF_SIZ(1<<20);
char ibuf[BUF_SIZ],*ip1(ibuf),*ip2(ibuf);
#define getchar() (ip1==ip2&&(ip2=(ip1=ibuf)+fread(ibuf,1,BUF_SIZ,stdin),ip1==ip2)?EOF:*ip1++)
void read(int& x)
{
	static char c;
	register int f=1;
	while(!isdigit(c=getchar()))if(c=='-')f=-1;
	x=c&15;
	while(isdigit(c=getchar()))x*=10,x+=c&15;
	x*=f;
}
void read(ll& x)
{
	static char c;
	register ll f=1;
	while(!isdigit(c=getchar()))if(c=='-')f=-1;
	x=c&15;
	while(isdigit(c=getchar()))x*=10,x+=c&15;
	x*=f;
}
void write(ll x)
{
	if(x<0)return putchar('-'),write(-x);
	if(x>9)write(x/10);
	putchar(x%10|'0');
}
int n,s;
pair<int,int> l[100001];
bitset<100001>b,t;
int la[100001];
int maxx;
bool hv[100001];
vector<int>to[100001],fr[100001];
int in[100001];
int ans[100001];

int main()
{
	read(n),read(s);
	b[0]=1;
	for(int i=1;i<=n;i++)read(l[i].first),l[i].second=i;
	sort(l+1,l+n+1);
	for(int i=1;i<n;i++)
	{
		t=b;
		b|=(b<<l[i].first);
		t^=b;
		for(int j=t._Find_first();j<=s-l[n].first;j=t._Find_next(j))la[j]=l[i].second;
	}
	if(s-l[n].first<0)
	{
		puts("-1");
		return 0;
	}
	if(b[s-l[n].first])
	{
		int ad=l[n].second;
		la[s]=l[n].second;
		for(int i=1;i<=n;i++)swap(l[i].first,l[i].second);
		sort(l+1,l+n+1);
		int t=s;
		while(t)
		{
			hv[la[t]]=1;
			t-=l[la[t]].second;
		}
		for(int i=1;i<=n;i++)swap(l[i].first,l[i].second);
		sort(l+1,l+n+1);
		for(int i=n;i>0;i--)
		{
			if(hv[l[i].second])continue;
			to[l[i].second].push_back(ad);
			fr[ad].push_back(l[i].second);
			in[ad]++;
			ad=l[i].second;
		}
		for(int i=1;i<=n;i++)swap(l[i].first,l[i].second);
		sort(l+1,l+n+1);
		queue<int>que;
		for(int i=1;i<=n;i++)
		{
			ans[i]=l[i].second;
			if(!in[i])
			{
				que.push(i);
			}
		}
		while(!que.empty())
		{
			int x=que.front();
			que.pop();
			int len=to[x].size();
			for(int i=0;i<len;i++)
			{
				ans[to[x][i]]-=l[x].second;
				in[to[x][i]]--;
				if(!in[to[x][i]])que.push(to[x][i]);
			}
		}
		for(int i=1;i<=n;i++)
		{
			int len=fr[i].size();
			write(ans[i]),putchar(' ');
			write(len),putchar(' ');
			for(int j=0;j<len;j++)
			{
				write(fr[i][j]),putchar(' ');
			}
			putchar('\n');
		}
	}
	else
	{
		puts("-1");
		return 0;
	}
	return 0;
}
```


---

## 作者：白依尘_轩子墨 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF356D)

分析：

对于某个节点 $u$，设他的子节点为 $v$，则 $c_{u}=a_{u}-a_{v}$。

特例：

$\exists 1 \leq i \leq n$,$a_{i} \geq S$

发现如果 $a_{i} > S$ 则无解，$a_{i} = S$ 时 $i$ 作为树的根节点。

所以我们对 $a_{i}$ 升序排序，然后 $x+1$ 向 $x$ 连边即可。

正解：

所有的 $i$ 构成一个森林。

每个节点向它的父亲节点连边即可。

显然，对于森林中的每棵树，都能用**特例**的方法重构成合法方案。

注意到 $a$ 最大的 $i$ 不会被作为叶子节点（记它的编号为 $p$），所以其他节点的权值之和为 $S-a_{p}$。

所以我们只要在其它没被连为子节点的节点中选出子集 $T$ 满足 $\sum_{i\in T} a_{i} =S-a_{p}$，这是一个经典的背包问题。

设 $dp_{i,j}$ 表示考虑到第 $i$ 个节点，$a_{i}$ 的和为 $j$ 时是否有解，直接跑01背包时间复杂度 $O(nS)$。

然而对于题目的 $1 \leq n,S \leq 70000$ 显然会TLE。

优化：

背包转移用 ```bitset``` 优化，可以做到 $O(\frac{nS}{\omega})$ 的复杂度。

至于方案的构造，考虑一个转移 $f_{i,j}\leftarrow f_{i-1,j-a_{i}}$，若之前都没有和为 $j$ 的方案，我们记 $nxt_j=i$，表示 $i$ 提供了第一条向 $j$ 的转移边，之后可以通过将 $s$（初值为 $S-a_{p}$ ）不断减去 $a_{nxt_{s}}$ 直到 ```0``` 来找出集合 $T$。

这样，复杂度瓶颈便变为如何快速找出每次更新了哪些位置（异或相邻的状态即可）。可以手写 ```bitset```，也可以使用 ```bitset``` 内置的 ```_Find_first``` 和 ```_Find_next``` 函数（NOI Linux 下可用）。

遍历方法（记 $t$ 是一个长度 $len$ 的 ```bitset``` ）：

```cpp
for (int i=t._Find_first();i<len;i=t._Find_next(i)){ 
	// 遍历 t 中所有为 1 的位置 
}
```
记 $t$ 中有 $c$ 个 ```1```，则时间复杂度为 $O(c+\frac{len}{\omega})$。

由于每个位置只会在第一次到达时被更新，时间复杂度 $O(n+S+\frac{nS}{\omega})$，空间复杂度 $O(n+S)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e5+10;
const int mod=1e9+7;
typedef long long ll;
namespace io{
	const int _SIZE=(1<<21)+1;
	char ibuf[_SIZE],*iS,*iT,c,stk[40];int tot;
#define gc()(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,_SIZE,stdin),(iS==iT ?EOF:*iS++)):*iS++)
	template<class I>
	inline void read(I &_x){
		I fl=1;
		for(c=gc();c<'0'||c>'9';c=gc()) if(c=='-') fl=-1;
		for(_x=0;c>='0'&&c<='9';c=gc()) _x=(_x<<3)+(_x<<1)+(c&15);
		_x*=fl;
	}
	template<class I>
	inline void prt(I _x,char ch='\0'){
		tot=0;
		if(_x<0) putchar('-'),_x*=-1;
		do{
			stk[tot++]=_x%10|48;_x/=10;
		}while(_x);
		do{
			putchar(stk[--tot]);
		}while(tot);
		if(ch)putchar(ch);
	}
}
using io::read;
using io::prt;
int n,s;
struct node{
	int l,id;
}a[Maxn];
bool cmp1(node x,node y){return x.l>y.l;}
bool cmp2(node x,node y){return x.id<y.id;}
int link[Maxn],nxt[Maxn],cnt,son[Maxn],c[Maxn],l[Maxn],idx[Maxn];
bitset<Maxn>dp,t;
bool done[Maxn];
int main(){
	read(n),read(s);
	for(int i=1;i<=n;i++){
		read(a[i].l),a[i].id=i;
		if(a[i].l>s){
			puts("-1");
			return 0;
		}
	}
	sort(a+1,a+1+n,cmp1);
	s-=a[1].l;
	dp[0]=1;
	for(int i=2;i<=n;i++){
		t=dp;
		dp|=dp<<a[i].l;
		t^=dp;
		for(int j=t._Find_first();j<Maxn;j=t._Find_next(j)) nxt[j]=i;
	}
	if(dp[s]==false){
		puts("-1");
		return 0;
	}
	int pos=s;
	while(pos){
		done[nxt[pos]]=true;
		c[a[nxt[pos]].id]=a[nxt[pos]].l;
		pos-=a[nxt[pos]].l;
	}
	for(int i=1;i<=n;i++) if(!done[i]) link[++cnt]=a[i].id;
	sort(a+1,a+1+n,cmp2);	
	for(int i=2;i<=cnt;i++){
		c[link[i-1]]=a[link[i-1]].l-a[link[i]].l;
		son[link[i-1]]=link[i];
	}
	c[link[cnt]]=a[link[cnt]].l;	
	for(int i=1;i<=n;i++){
		prt(c[i],' ');
		if(son[i]) prt(1,' '),prt(son[i],'\n');
		else puts("0");
	}
	return 0;
}

```


---

## 作者：_ZHONGZIJIE0608_ (赞：0)

一开始看题目，什么马啊，袋子啊，金币啊，还袋子套袋子，什么玩意儿这是。然后看到了翻译写的形式化题面，顿觉豁然开朗。想了一整天，终于搞出来了。

正如翻译所说，我们需要构造一个带点权的森林，使得每个点子树点权和为 $a_i$，所有点的点权和为 $s$。

先考虑我们需要建一个什么样的森林。想了一上午才发现，我们可以不考虑奇怪的树形结构，直接建一些链，每个链的根节点（下文称之为“链头”）的 $a_i$ 是链里面最大的。显而易见，$a_i$ 最大的点 $p$ 一定是链头。我们先把 $s$ 减掉 $a_p$，这样点权总和为 $s$ 的问题就解决了——就是在剩余的 $n-1$ 个点中选取一些点使得这些点的点权和为减掉第一个点的值之后的 $s$。这不就是个背包？但是 $O(n^2)$ 的复杂度一定会超时，考虑到这里只维护可行性（$dp_j$ 表示和为 $j$ 是否可行），我们上 bitset 就能优化复杂度到 $O(\frac{n^2}{w})$，时间限制足够了。注意在 DP 时要记录变化的量，也就是每个点是从哪里转移过来的。

然后我们就得到了所有的链头。发现有一些点还没有使用，可以用一种很好的方案构造：只有点 $p$ 下面链接没有使用的点，剩下的链长度全部是 $1$。

接着就把未使用的点全部用队列存下来（此时这些节点按照 $a_i$ 降序排列，这样先出现的就是父亲），每次弹出 $2$ 个点，先弹出的作为父亲，维护其点权和儿子即可。

当然，如果未选择的点个数是奇数会剩下一个点。所以我们判断能否操作的条件是是否有 $2$ 个点。对于链尾 $t$ 我们直接以它的 $a_t$ 作为权值，没有儿子。

最后输出权值和儿子情况即可。

---

## 作者：lfxxx (赞：0)

首先最大值必选，因为其必是一个连通块的根。

然后考虑我们可以任意挑选出一些点作为连通块根，并将其的子树大小算入全局点权和，所以问题变为一个背包问题，考虑 bitset 优化可以做到 $O(\frac{n^2}{w})$，转移过程中在某个背包可以凑出来的大小第一次被凑出来时记录其方案即可构造出选连通块根的方案，然后按照子树大小排序构造若干条链即可。

---

