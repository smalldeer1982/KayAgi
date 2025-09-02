# The Strongest Build

## 题目描述

Ivan正在玩另一个类似Rogue的电脑游戏。他控制着游戏里面的一个英雄，这个英雄有 $n$ 个装备槽，对于每个槽 $i$ 而言有 $c_i$ 个物品可以选择，第 $j$ 个物品会增加英雄 $a_{i,j}$ 的力量值。每个槽所对应的物品两两不同并按照可以增加的力量值升序排序，即： $a_{i,1}<a_{i,2}<\dots<a_{i,c_i}$ 

对于每个装备槽，Ivan只能在它所对应的物品列表中至多选一个物品。选择的序列称作一个组合。

一个组合的力量值是组合中所包含的物品提升的力量值之和，然而有 $m$ 个两两不同的组合被游戏禁掉了，保证有至少一个组合没有被禁。

询问满足要求（不被禁）的组合的最大力量值为多少？如果有多个组合有相同的最大值，输出它们之中的任意一个即可。

## 样例 #1

### 输入

```
3
3 1 2 3
2 1 5
3 2 4 6
2
3 2 3
3 2 2```

### 输出

```
2 2 3```

## 样例 #2

### 输入

```
3
3 1 2 3
2 1 5
3 2 4 6
2
3 2 3
2 2 3```

### 输出

```
1 2 3```

## 样例 #3

### 输入

```
3
3 1 2 3
2 1 5
3 2 4 6
2
3 2 3
2 2 3```

### 输出

```
3 2 2```

## 样例 #4

### 输入

```
4
1 10
1 4
1 7
1 3
0```

### 输出

```
1 1 1 1```

# 题解

## 作者：Presentation_Emitter (赞：18)

~~菜鸡 Atziluth 连爆搜都不会了。。。~~

考虑堆优化 BFS，对于一个状态 $(sum,\{t_1,t_2,...,t_n\})$，其中 $sum$ 为 $\sum\limits_{i=1}^{n}a_{i,t_i}$，对于 $\forall\ 1 \le i \le n \land t_i \gt 1$，它能转移到：

$$(sum-a_{i,t_i}+a_{i,t_i-1},\{t_1,...,t_{i-1},t_i-1,t_{i+1},...,t_n\})$$

一个状态的优先级即为 $sum$。检验一个状态是否被禁止仅需检测哈希值即可。

Code:

```cpp
#define prpr make_pair
#define ll long long
#define HgSAKIOI 1
#define il inline
ll n,c[11],m;vector<ll>v[11];
il ll hash1(vector<ll>f)
{
	ll h=0;
	for(int i=0;i<n;++i)h=(h*1333331+f[i])%998244353;
	ret h;
}
il ll hash2(vector<ll>f)
{
	ll h=0;
	for(int i=0;i<n;++i)h=(h*1333331+f[i])%1000000007;
	ret h;
}
il ll hash0(vector<ll>f){ret hash1(f)*1000000007+hash2(f);}
struct node{ll id,v,d[11];il bool opr<(cst node&_)cst{ret v<_.v;}};
multiset<ll>s,vs;priority_queue<pair<ll,vector<ll> > >q;
int main()
{
	n=rd();ll sum=0;
	for(int i=1;i<=n;++i)
	{
		sum+=c[i]=rd();v[i].emplace_back(0);
		for(int j=1;j<=c[i];++j)v[i].emplace_back(rd());
	}
	m=rd();
	for(int i=1;i<=m;++i){vector<ll>tmp;for(int j=1;j<=n;++j)tmp.emplace_back(rd());s.insert(hash0(tmp));}
	vector<ll>tmp;for(int i=1;i<=n;++i)tmp.emplace_back(c[i]);
	q.push(prpr(sum,tmp));
	while(HgSAKIOI)
	{
		auto p=q.top();q.pop();
		ll h=hash0(p.second);if(vs.count(h))continue;
		vs.insert(h);
		if(s.count(h))
		{
			for(int i=1;i<=n;++i)
			{
				--p.second[i-1];
				if(p.second[i-1])q.push(prpr(p.first-v[i][p.second[i-1]+1]+v[i][p.second[i-1]],p.second));
				++p.second[i-1];
			}
		}
		else
		{
			for(int i=0;i<n;++i)prt(p.second[i]," \n"[i==n-1]);
			break;
		}
	}
	ret 0;
}
```

---

## 作者：Lynkcat (赞：6)

发一种阴间做法。

建立 trie 树，把题目中的限制插入进去，然后就相当于 trie 树上的 $m$ 条链不能选。

那么我们可以建立这样一个递归过程 $dfs(k,dep)$ 表示当前在节点 $k$，深度为 $dep$。有若干种选择，如果你往儿子走相当于按照限制走，否则相当于后面的选择没有限制了。

如果你直接这样写，复杂度是错的，因为这样子理论上复杂度是 $O(nm\times 10)$。

如果我们只向不存在的儿子中最大的走，显然正确性可以保证，并且复杂度降到了 $O(m\times 10)$。

然后就通过了本题。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 2000005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
//#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,a[15];
vector<int>W[N];
int m,x[15];
int tot;
unordered_map<int,int>son[N];
struct node
{
	int val,p[11];
	void init() {val=0,memset(p,0,sizeof(p));}
};
inline void insert()
{
	re int now=1;
	for (int i=1;i<=n;i++)
	{
		if (son[now].count(x[i]))
		{
			now=son[now][x[i]];
		} else
			son[now][x[i]]=++tot,
			now=son[now][x[i]];
	}
}
inline node checkmx(node x,node y)
{
	if (x.val<y.val) return y;
	return x;
}
node dfs(int k,int dep,int V)
{
	if (!k)
	{
		re node g;g.init();
		for (int i=dep+1;i<=n;i++) g.p[i]=a[i],g.val+=W[i][a[i]-1];
		g.p[dep]=V;
		g.val+=W[dep][V-1];
		return g;
	}
	if (dep==n) 
	{
		re node g;g.init();
		return g;
	}
	re node g;g.init();
	for (int i=a[dep+1];i>=1;i--)
		if (son[k].count(i))
		{
			g=checkmx(g,dfs(son[k][i],dep+1,i));
		}
		else 
		{
			g=checkmx(g,dfs(0,dep+1,i));
			break;
		}
	if (k==1) return g;
	if (g.val==0) return g;
	g.p[dep]=V;
	g.val+=W[dep][V-1];
	return g;
}
signed main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		for (int j=1;j<=a[i];j++) W[i].push_back(read());
	}
	m=read();
	tot=1;
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)	
		{
			x[j]=read();
		}
		insert();
	}
	node ans=dfs(1,0,0);
	for (int i=1;i<=n;i++) writesp(ans.p[i]);
}
/*
*/
```

---

## 作者：huayucaiji (赞：5)

## 解题思路

这个题有两种做法，这里只详解一种。

首先考虑暴力。

我们找出所有的组合，哈希一下，按大小排个序，从大到小一个一个查这个组合是否被 ban 了。一旦查到一个组合合法，就输出这个组合。这一定是最优的。

很明显时间复杂度爆炸了，这样复杂度是指数级别的。

我们考虑优化。优化的核心思想就是减少参与排序的组合。

根据贪心，我们知道如果说选择每个序列的最后一个值，一定是最大的。如果这个组合没有被 ban，那么就输出。

我们考虑被 ban 了怎么办。

容易发现，答案的形式一定是某一个被 ban 的组合，调整一个取值所得到的组合，且这个组合没有被 ban。这里的调整是将一个取值替换为其前一个数。

为什么？为什么答案是这个形式呢？

如果说我们最终的答案于是某一个组合调整两次所得到的，那么少做一次调整，所得到的的答案会更大。矛盾，证毕。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define pipii pair<int,pair<int,int> >
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=2e5+10,b1=1e5+1,b2=3e5+3,m1=20060527,m2=21071179;

int n,m,cnt=1,num;
int tmp[11],a[11][MAXN],c[MAXN],ban[MAXN>>1][11];
map<pair<int,int>,bool> mp;

struct build {
	int ans,p[11];
	pair<int,int> hsh; 
}b[MAXN*5];

void inw() {
	int sum=0,h1=0,h2=0;
	num++;
	for(int i=1;i<=n;i++) {
		sum+=a[i][tmp[i]];
		b[num].p[i]=tmp[i];
		h1=(h1*b1%m1+tmp[i])%m1;
		h2=(h2*b2%m2+tmp[i])%m2;
	}
	b[num].ans=sum;
	b[num].hsh=make_pair(h1,h2);
}

bool cmp(build a,build b) {
	return a.ans>b.ans;
}

signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		tmp[i]=c[i]=read();
		
		for(int j=1;j<=c[i];j++) {
			a[i][j]=read();
		}
	}
	
	inw();
	
	cin>>m;
	for(int i=1;i<=m;i++) {
		int h1=0,h2=0;
		for(int j=1;j<=n;j++) {
			ban[i][j]=tmp[j]=read();
			h1=(h1*b1%m1+tmp[j])%m1;
			h2=(h2*b2%m2+tmp[j])%m2;
		}
		mp[make_pair(h1,h2)]=1;
	}
	
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=n;j++) {
			tmp[j]=ban[i][j];
		}
		for(int j=1;j<=n;j++) {
			if(ban[i][j]==1) {
				continue;
			}
			tmp[j]--;
			inw();
			tmp[j]++;
		}
	}
	
	sort(b+1,b+num+1,cmp);
	
	for(int i=1;i<=num;i++) {
		if(!mp[b[i].hsh]) {
			for(int j=1;j<=n;j++) {
				cout<<b[i].p[j]<<" ";
			}
			puts("");
			return 0;
		}
	}
	return 0;
}


```

---

## 作者：AmamiyaYuuko (赞：4)

提供一种完全不用动脑子的做法。

如果被 ban 的序列不包括 $\{a_{1, c_1}, a_{2, c_2}, \cdots, a_{n, c_n}\}$，那直接输出这个序列，不然的话继续下面的操作。

考虑此时最优解的可能情况，不难发现必然是被 ban 掉的序列中将某一个元素往前取一个得到的。

枚举每个被 ban 的序列 $\{b_i\}$，然后再枚举每个元素 $1 \le i \le n$，判断序列 $\{b_1, b_2, \cdots, b_i - 1, \cdots, b_n\}$ 是否被 ban，如果没有被 ban 就更新答案。

至于怎么维护某一个序列有没有被 ban，可以用 `std::map` 来实现。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

template <class T>
inline void read(T &x) {
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return ;
}

typedef unsigned long long uLL;
typedef long long LL;

std::vector<int> a[20], b[100010], ans, arr;
std::map<std::vector<int>, bool> mp;
int s[100010];
int n, tot, max, m;

int main() {
    read(n);
    for (int i = 1, x; i <= n; ++i) {
        read(x);
        a[i].push_back(x);
        for (int j = 1; j <= a[i][0]; ++j)    read(x), a[i].push_back(x);
    }
    read(m);
    if (!m) {
        for (int i = 1; i <= n; ++i)    printf("%d ", a[i][0]);
        puts("");
        return 0;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1, x; j <= n; ++j)    read(x), s[i] += a[j][x], b[i].push_back(x);
        mp[b[i]] = true;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            arr = b[i];
            if (arr[j] != 1) {
                --arr[j];
                if (mp.find(arr) == mp.end()) {
                    if (s[i] - a[j + 1][arr[j] + 1] + a[j + 1][arr[j]] > max) {
                        max = s[i] - a[j + 1][arr[j] + 1] + a[j + 1][arr[j]];
                        ans = arr;
                    }
                }   
            }
        }
    }
    for (int i = 1; i <= n; ++i)    arr[i - 1] = a[i][0];
    if (mp.find(arr) == mp.end())    ans = arr;
    for (int i = 0; i < n; ++i)    printf("%d ", ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：henrytb (赞：1)

如果没有限制的话那肯定所有数组都选最大的就行了，但是这里有限制。

那么我们可以从最大的开始往下减，搜一遍，每次都判断一下当前状态是否合法。如果合法的话就和答案取一下 $\max$。这里判断合法我用了一个 `set` 存了一个重载了 $<$ 的结构体表示状态，不知道有没有比我更好的方法。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
struct tp{
    int t[11];
    tp(){}
    tp(int t1,int t2,int t3,int t4,int t5,int t6,int t7,int t8,int t9,int t10) {
        t[1]=t1;
        t[2]=t2;
        t[3]=t3;
        t[4]=t4;
        t[5]=t5;
        t[6]=t6;
        t[7]=t7;
        t[8]=t8;
        t[9]=t9;
        t[10]=t10;
    }
    bool operator < (const tp& rhs) const {
        if(t[1]<rhs.t[1]) return 1;
        if(t[1]>rhs.t[1]) return 0;
        if(t[2]<rhs.t[2]) return 1;
        if(t[2]>rhs.t[2]) return 0;
        if(t[3]<rhs.t[3]) return 1;
        if(t[3]>rhs.t[3]) return 0;
        if(t[4]<rhs.t[4]) return 1;
        if(t[4]>rhs.t[4]) return 0;
        if(t[5]<rhs.t[5]) return 1;
        if(t[5]>rhs.t[5]) return 0;
        if(t[6]<rhs.t[6]) return 1;
        if(t[6]>rhs.t[6]) return 0;
        if(t[7]<rhs.t[7]) return 1;
        if(t[7]>rhs.t[7]) return 0;
        if(t[8]<rhs.t[8]) return 1;
        if(t[8]>rhs.t[8]) return 0;
        if(t[9]<rhs.t[9]) return 1;
        if(t[9]>rhs.t[9]) return 0;
        if(t[10]<rhs.t[10]) return 1;
        if(t[10]>rhs.t[10]) return 0;
        return 0;
    }
};
int n,m;
int c[11];
int a[11][200005];
set<tp> s;
int ans=0x3f3f3f3f;
tp anss;
set<tp> vis;
void dfs(tp u,int dee) {
    if(vis.count(u)) return;
    vis.insert(u);
    if(!s.count(u)) {
        if(dee<ans) {
            ans=dee;
            anss=u;
        }
        return ;
    }
    rep(i,1,n) {
        if(u.t[i]>1) {
            --u.t[i];
            dfs(u,dee+a[i][u.t[i]+1]-a[i][u.t[i]]);
            ++u.t[i];
        }
    }
}
int main() {
    scanf("%d",&n);
    rep(i,1,n) {
        scanf("%d",&c[i]);
        rep(j,1,c[i]) scanf("%d",&a[i][j]);
    }
    scanf("%d",&m);
    tp b(0,0,0,0,0,0,0,0,0,0);
    rep(i,1,m) {
        rep(j,1,n) {
            scanf("%d",&b.t[j]);
        }
        s.insert(b);
    }
    tp now(0,0,0,0,0,0,0,0,0,0);
    rep(i,1,n) {
        now.t[i]=c[i];
    }
    dfs(now,0);
    rep(i,1,n) printf("%d ",anss.t[i]);
    return 0;
}
```

---

## 作者：SSL_wj (赞：0)

# CF1574D 题解
## 写在前面
没有更好的体验了 /kk

这场 CF 的 D 题意外的简单，但依旧是 WA 了两遍才 A 掉。

这 building 翻译过来当作方案实属离谱。

~~话说赛后我还去吐槽了一下，说这题只有 *1300。~~
## 思路
看完题发现方案中的每个值肯定都越大越好，那么**全部选满**肯定是最好的。

但是 Ban 机制打破了我们的梦想，容易发现 $O(nm\log nm)$ 的做法都是跑得过去的，于是考虑用一个堆维护状态，每一次选出当前最优进行扩展（即**尝试减小每一个位置以得到一个新方案**），那么就像一道 **$n$ 维堆优 dij** 一样，正确性显然。

接下来只有一个问题：如何判断一个状态是否访问过？这就需要一个优秀的结构体，我采用的是标记了一个 now，代表上一次修改到了哪个位置（没有则为1），每次**只修改 now 及之后的位置**，容易发现这样就有唯一表示法了。~~其实这一段是我写的时候随手写的优化。~~

接下来是判断是否 Ban 掉了这个方案，我选择给结构体重载运算符，具体而言是先比较这个方案的价值，接下来比较方案的字典序，相同则返回 false，这样子就可以判断是否相等，也符合 map 的使用方法，因此直接将 Ban 掉的方案扔进一个 map，每次直接查就行。

时间复杂度：堆里最多有 $nm$ 个位置（每个不合法方案扩展出 $n$ 个方案），因此维护堆的复杂度不超过 $O(nm\log nm)$，当然严重跑不满。
## 代码
因为不想有人抄所以去掉了头文件。
```cpp
#define int long long
using namespace std;
inline bool idigit(register char x){return (x<'0'||x>'9')?0:1;}
inline int read()
{
	register int num=0,f=1;
	register char c;
	while(!idigit(c=getchar()))if(c=='-')f=-1;
	while(idigit(c))num=(num<<1)+(num<<3)+(c&15),c=getchar();
	return num*f;
}
//快读
int n,m,len[12];
vector<int>a[12];
struct pa{int a[12],val,now;}o2,o3;
inline bool operator<(const pa x,const pa y)
{
	if(x.val!=y.val)return x.val>y.val;
	for(register int i=1;i<=n;++i)if(x.a[i]!=y.a[i])return x.a[i]>y.a[i];
	return 0;
	//因为小于不成立，所以必须返回0
}
//重载运算符，同时给优先队列和map用，大幅减小码量
priority_queue<pa>que;
map<pa,bool>e;
signed main()
{
	n=read();
	for(register int i=1;i<=n;++i)
	{
		a[i].resize((len[i]=read())+10);
		for(register int j=1;j<=len[i];++j)a[i][j]=read();
	}
	m=read(),o2.now=1;
	while(m--)
	{
		for(register int i=1;i<=n;++i)o2.val+=a[i][len[i]]-a[i][o2.a[i]=read()];
		e[o2]=1,o2.val=0;
	}
	for(register int i=1;i<=n;++i)o2.a[i]=len[i];
	que.push(o2);
	while(que.size())
	{
		o2=que.top(),que.pop();
		if(e.find(o2)==e.end())
		{
			for(register int i=1;i<=n;++i)printf("%lld ",o2.a[i]);
			return 0;
		}
		for(register int i=o2.now;i<=n;++i)if(o2.a[i]>1)
		{
			for(register int j=1;j<=n;++j)o3.a[j]=o2.a[j];
			o3.now=i,o3.val=o2.val+a[i][o2.a[i]]-a[i][--o3.a[i]],que.push(o3);
			//对i位置进行减小操作
		}
	}
	return 1;
}
```
~~别看代码挺长，其实删掉 register 就好；别看代码挺丑，其实我[原本写的](https://codeforces.com/contest/1574/submission/129402396)更丑！~~

---

