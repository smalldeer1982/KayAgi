# [入门赛 #9] 大碗宽面 (Hard Version)

## 题目背景


**本题与 Easy Version 题意完全相同，仅有 $n$ 的数据范围和空间限制不同**。

扶苏和她的朋友们在 Impart 酒店开派对。

## 题目描述

算上扶苏，本次派对共有 $n$ 个人。但是，并不是任何两个人都互相认识，并且互相认识的人关系也未必好。

具体而言，任意两个人可能是如下三种关系之一：
1. 敌人
2. 朋友
3. 陌生人

派对的一大重要活动是相互握手。对任意两个人 $u,v$，他们之间的握手情况遵循下面的规则：
1. 如果 $u$ 和 $v$ 是朋友关系，那么他们一定握手一次。
2. 如果 $u$ 和 $v$ 是敌人关系，那么他们一定**不**握手。
3. 如果 $u$ 和 $v$ 是陌生人关系，且存在一个人 $w$，使得 $w$ 是 $u$ 和 $v$ 之一的朋友，同时是 $u,v$ 中另一人的敌人，则 $u$ 和 $v$ **不会**握手，否则 $u$ 和 $v$ 一定握手一次。

对第三条规则，简单的说法是：一对陌生人之间，如果某一方的朋友是另一方的敌人，则不握手，否则握手。

已知共有 $p$ 对人是朋友关系，$q$ 对人是敌人关系。除了这 $p + q$ 对人，其他每对人均为陌生人关系。

请你求出本次派对一共握手了多少次。

## 说明/提示

### 样例 1 解释

共有 $(1,2), (1,3), (1,4), (2,3), (2,4), (3,4)$ $6$ 对人。
- $(1,2)$ 是朋友，握手。
- $(1,3)$ 是敌人，不握手。
- $(1,4)$ 是敌人，不握手。
- $(2,3)$ 是朋友，握手。
- $(2,4)$ 是陌生人，但是 $1$ 是 $2$ 的朋友，也是 $4$ 的敌人，所以不握手。
- $(3,4)$ 是陌生人，但是不存在任何一个人既是 $3$ 和 $4$ 之一的敌人也是另一个人的朋友，故握手。

综上，一共握手 $3$ 次。

### 数据规模与约定

以下设 $m = p + q$，即 $m$ 是朋友和敌人关系条数之和。

- 对 $100\%$ 的数据，保证 $2 \leq n \leq 10^6$，$1 \leq u, v \leq n$，$0 \leq p,q \leq m \leq 10^3$，$u \neq v$。同一对敌人或朋友关系不会出现两次，不会有一对人同时是敌人或朋友关系。

By 一扶苏一

## 样例 #1

### 输入

```
4 2 2
1 2
2 3
1 4
1 3```

### 输出

```
3```

# 题解

## 作者：一扶苏一 (赞：5)

# 【枚举】【P9008】大碗宽面

## Description

给定一张 $n$ 个点的图，两点之间要么有一条灰边（陌生人），要么连一条黑边（敌人），要么连一条白边（朋友）。黑边和白边共 $m$ 条。

如果一个点对：
1. 被一条白边连接
2. 被一条灰边连接，且这个点对不属于任何三条边颜色均不同的三元环

则对答案造成 $1$ 的贡献。求答案。

$1 \leq n \leq 10^6$，$1 \leq m \leq 10^3$。

## Analysis

题目名不是我起的，但是题面是我写的。比赛时感觉创飞了不少人，倒开的选手也直接把这个题跳了。难道大家不喜欢 impart？

因为 $n$ 很大，直接枚举所有点对的梦想破灭了。考虑正难则反，尝试把没有贡献的点对数算出来，拿总的点对数 $n(n-1)/2$ 减一下即可。

首先黑边连接的点对没有贡献，然后被灰边连接的点对如果属于一个三色三元环也没有贡献。前者可以直接算，考虑后者怎么算。

灰边有 $O(n^2)$ 条，直接枚举是不行的，但是考虑黑边和白边数量很少。可以枚举每一条黑边 $(u,v)$，然后分别枚举连接 $v$ 和 $u$ 的白边。以枚举连接 $v$ 的白边 $(v,w)$ 为例，如果 $u$ 和 $w$ 之间是灰边，那么就可以把边 $(u,w)$ 的贡献减掉。因为一条边可能被算多次，所以减掉贡献一共要用一个 map 之类的容器随便记一下以后不要再扣这条边的贡献了。

考虑复杂度：枚举了 $O(m)$ 条黑边，对每条黑边枚举它两个端点连接的白边，至多 $O(m)$ 条，所以枚举量最坏 $O(m^2)$。每次需要去 map 里查一下，所以总复杂度是 $O(m^2 \log n)$。

## Code

```cpp
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

const int maxn = 1000005;

int n, p, q;
std::map<std::pair<int, int>, bool> calced;
std::vector<int> enemy[maxn], frnds[maxn];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> p >> q;
  long long ans = 1ll * n * (n - 1) / 2;
  for (int i = 1, u, v; i <= p; ++i) {
    std::cin >> u >> v;
    frnds[u].push_back(v);
    frnds[v].push_back(u);
    calced[{u,v}] = calced[{v,u}] = true;
  }
  for (int i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v;
    enemy[u].push_back(v);
    enemy[v].push_back(u);
    --ans;
    calced[{u,v}] = calced[{v,u}] = true;
  }
  for (int u = 1; u <= n; ++u) {
    for (auto v : enemy[u]) {
      for (auto w : frnds[u]) if (!calced[{w, v}]) {
        calced[{w,v}] = calced[{v,w}] = true;
        --ans;
      }
      for (auto w : frnds[v]) if (!calced[{w, u}]) {
        calced[{w,u}] = calced[{u,w}] = true;
        --ans;
      }
    }
  }
  std::cout << ans << std::endl;
}
```

---

## 作者：_•́へ•́╬_ (赞：5)

## 思路

这个 1000000 就是防 `memset` 的。其实只有 2000 个点连到了边。

所以我们直接暴力，从一个点出发，访问他敌人和朋友的敌人和敌人的朋友，这些是不握手的。

最后拿总的减去不握手的就是握手的。

## code

```cpp
#include<stdio.h>
#define int long long
#define N 1000009
#define M 2222
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,p,q,h1[N],e1[M],nxt1[M],h2[N],e2[M],nxt2[M],ans;bool a[N];
main()
{
	read(n);read(p);read(q);ans=n*(n-1);
	for(int i=1,u,v;i<=p;++i)
		read(u),read(v),--u,--v,
		e1[i]=v,nxt1[i]=h1[u],h1[u]=i,
		e1[i+p]=u,nxt1[i+p]=h1[v],h1[v]=i+p;
	for(int i=1,u,v;i<=q;++i)
		read(u),read(v),--u,--v,
		e2[i]=v,nxt2[i]=h2[u],h2[u]=i,
		e2[i+q]=u,nxt2[i+q]=h2[v],h2[v]=i+q;
	for(int i=0;i<n;++i)
	{
		for(int j=h1[i];j;j=nxt1[j])a[e1[j]]=1;//双方是直接的朋友
		for(int j=h1[i];j;j=nxt1[j])for(int k=h2[e1[j]];k;k=nxt2[k])
			ans-=!a[e2[k]],a[e2[k]]=1;
		for(int j=h2[i];j;j=nxt2[j])
		{
			ans-=!a[e2[j]],a[e2[j]]=1;//双方是直接的敌人
			for(int k=h1[e2[j]];k;k=nxt1[k])
				ans-=!a[e1[k]],a[e1[k]]=1;
		}//统计不握手的情况

		for(int j=h1[i];j;j=nxt1[j])a[e1[j]]=0;//清空数组
		for(int j=h1[i];j;j=nxt1[j])for(int k=h2[e1[j]];k;k=nxt2[k])
			a[e2[k]]=0;
		for(int j=h2[i];j;j=nxt2[j])
		{
			a[e2[j]]=0;
			for(int k=h1[e2[j]];k;k=nxt1[k])a[e1[k]]=0;
		}
	}
	printf("%lld",ans>>1);
}
```



---

## 作者：__Kyw666__ (赞：3)

## 题意解释
有 $n$ 个人，其中有 $p$ 对朋友与 $q$ 对敌人，你要来计算有几对人将会握手。  
很显然，两个朋友会握手，但两个敌人是不会握手的。那如果两个人既不是朋友也不是敌人，就要找与他们有关系的第三个人，如果三人中有一对朋友与一对敌人，那么这两个人也就不会握手。  
~~俗话说得好：朋友的朋友是朋友，敌人的敌人也是朋友。~~

## 思路分析
求要握手的人并不容易，那我们就来求不握手的人。  
先求 $n$ 个人中有多少对人，公式很容易推导：
$$\frac{n \times (n-1)}{2} $$
接下来，再求有多少对敌人，然后用总对数减去敌人的对数就行了。

## 代码实现
先来看看我的错误代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,p,q;
int x,y,ans=0;
int vis[1005][1005]={0};

bool check(int i,int j)
{
	for(int k=1;k<=n&&k!=i&&k!=j;k++)
	{
		if(vis[i][k]+vis[j][k]==3)
			return 0;
	}
	return 1;
}

int main()
{
	cin>>n>>p>>q; 
	for(int i=1;i<=p;i++)
	{
		cin>>x>>y;
		vis[x][y]=1;
		vis[y][x]=1;
	}
	for(int i=1;i<=q;i++)
	{
		cin>>x>>y;
		vis[x][y]=2;
		vis[y][x]=2;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(vis[i][j]==1) {ans++;continue;}
			if(vis[i][j]==2) continue;			
			if(check(i,j)==1) ans++;
		}
	}
	cout<<ans;
	return 0;
 } 
```
[结果](https://www.luogu.com.cn/record/179405799)很惨烈。  
错误很明显：二维数组存不下题目要求的范围。  

紧接着我调整思路，用 ``map`` 数组与 ``vector`` 数组来存。  
详见代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,p,q,sum=0;
vector <int> a[1000005],b[1000005];    
map <pair <int,int>, int> v;  
signed main()
{
	cin>>n>>p>>q;
	for(int i=1;i<=p;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
		v[{x,y}]++;
		v[{y,x}]++;  
	}
	for(int i=1;i<=q;i++)
	{
		int x,y;
		cin>>x>>y;
		b[x].push_back(y);
		b[y].push_back(x);
		v[{x,y}]++;
		v[{y,x}]++;   
	}
	for(int i=1;i<=n;i++) 
		for(int j=0;j<a[i].size();j++) 
			for(int k=0;k<b[a[i][j]].size();k++)  
				if(v[{i,b[a[i][j]][k]}]==0)
				{   
					v[{i,b[a[i][j]][k]}]++;
					v[{b[a[i][j]][k],i}]++;   
					sum++;  
				}	
	cout<<n*(n-1)/2-q-sum;
	return 0;
}
```

结束！

---

## 作者：Ray1 (赞：3)

若不考虑陌生人关系，则总握手次数为 $\frac{n(n-1)}2-q$。

为了防止重复统计，我们先把所有是朋友或敌人关系的二元组 $(u,v)$ 标记，表示 $u,v$ 是否握手已经确定。注意这里的 $(u,v)$ **不区分先后顺序**。

然后暴力枚举所有陌生人关系。第一层循环枚举每一个人 $u$，第二层循环枚举点 $u$ 的朋友 $mid$，第三层循环枚举 $mid$ 的敌人 $v$。若 $(u,v)$ 未被标记，则标记 $(u,v)$ 并将总握手次数减去一次。

用 `map` 标记二元组 $(u,v)$ 当然是最方便的，但会使时间复杂度多一个 $\log$。我这份代码的时间复杂度是 $O(n+pq\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,q,u,v,s;
map<pair<int,int>,bool>m;
vector<int>P[1000001],Q[1000001];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>p>>q;
	for(int i=1;i<=p;i++)cin>>u>>v,P[u].push_back(v),P[v].push_back(u),m[{u,v}]=m[{v,u}]=1;
	for(int i=1;i<=q;i++)cin>>u>>v,Q[u].push_back(v),Q[v].push_back(u),m[{u,v}]=m[{v,u}]=1;
	for(int u=1;u<=n;u++)for(int mid:P[u])for(int v:Q[mid])if(!m[{u,v}])s++,m[{u,v}]=m[{v,u}]=1;
	cout<<(long long)n*(n-1)/2-q-s;
}
```

---

## 作者：ask_silently (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P9008)

## 题目简述
有 $n$ 个人，他们有 $p+q$ 对人是认识的，但其中 $q$ 对人是敌人。握手的规则是朋友之间肯定握手；敌人之间肯定不握手；朋友的敌人不握手；其余都握手。最后求出总共有多少对握手的人。

## 思路
- 首先，我们求握手的人肯定不好求，所以我们反其道而行之，求不握手的人。先求没有陌生人握手的对数，第一个人可以和其余 $n-1$ 个人握手，第二个人可以和其余 $n-2$ 个人握手，以此类推。所以总共可以握手的人就是： $(1+n-1) \times (n-1) \div 2$ ，化简可得： $n \times (n-1) \div 2$ 。然后减去是敌人的对数 $q$ ，就可以得到除去陌生人之外握手的对数了。

- 那陌生人不握手的对数怎么求呢？咱们可以设两个动态数组，存每个人的敌人和朋友，然后枚举每个人的朋友 $x$ ，再枚举 $x$ 的敌人 $y$ ，让枚举的这个人和 $y$ 不握手，这样就可以求出陌生人不握手的对数了。

- 总体来说，这个程序是三层循环，一层枚举 $n$ 个人，二层枚举每个人的朋友 $x$ ，三层枚举 $x$ 的敌人 $y$ ，这样就可以求出不握手的对数，最后输出 $n \times (n-1) \div 2-q-s$ ，这就是握手的对数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,p,q,bu;
vector<int> pengyou[1000005],diren[1000005];     //动态数组，记录每个人的朋友和敌人 
map <pair<int,int>,int> mp;    //map数组，记录每一对人是否被记录过 
int main(){
	scanf("%d%d%d",&n,&p,&q);
	for(int i=1;i<=p;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		pengyou[x].push_back(y);
		pengyou[y].push_back(x);
		mp[{x,y}]++,mp[{y,x}]++;    //记录上xy，他们不是不握手的人 
	}
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		diren[x].push_back(y);
		diren[y].push_back(x);
		mp[{x,y}]++,mp[{y,x}]++;    //记录上xy，最后我们会减去q，不用再次记录他们 
	}
	for(int i=1;i<=n;i++){    //枚举每个人 
		for(int j=0;j<pengyou[i].size();j++){    //枚举每个人的朋友 
			int you=pengyou[i][j];
			for(int k=0;k<diren[you].size();k++){    //枚举朋友的敌人 
				int x=i,y=diren[you][k];
				if(!mp[{x,y}]){    //判断是否被记录过 
					mp[{x,y}]++,mp[{y,x}]++;    //记录 
					bu++;    //不握手的对数加1 
				}
			}
		}
	}
	printf("%lld",(long long)n*(n-1)/2-q-bu);    //输出最后结果 
	return 0;
}
```


---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
做题要先看数据范围，虽然 $n$ 很大，但是 $m$ 非常小，我们可以考虑建图来跑暴力。
## 2. 题目做法
这题处理朋友和敌人关系非常简单，关键是如何处理陌生人关系。  
我们可以用一个变量 $s$ 记录有多少对人握手，初始时，我们可以假设所有人都可以互相握手，那么 $s$ 的初始值就为 $n \times (n-1) \div 2$。  
我们可以用一个 STL 容器来存储一条边是否被访问过，以免后面重复计算。  
对于朋友关系，我们对两点进行连边，将 $s$ 减一，并将每条边存进容器中，避免后面去掉不握手情况时把这些边算进去。  
对于敌人关系，我们将此边存进容器中，但不连边，防重复计算。然后我们将此两点的朋友关系遍历一遍，若另外一点与这点朋友的边未被访问过，将 $s$ 减一，并将此边存进容器。  
这样我们便能完成此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010,M=2010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int head[N],ne[M],e[M],idx;
inline void add(int x,int y)
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y; 
}
int n,p,q;
int x,y;
long long v=1000000,t,s;
unordered_map<long long,bool>m;
int main()
{
	n=read(),p=read(),q=read();
	s=1ll*n*(n-1)/2;
	while(p--)
	{
		x=read(),y=read();
		add(x,y),add(y,x);
		m[v*x+y]=1;//这样存边能防止重复存储 
		m[v*y+x]=1;
	}
	while(q--)
	{
		x=read(),y=read();
		t=v*x+y;
		if(!m[t])
		{
			m[t]=1;
			m[v*y+x]=1;
			s--;
		}
		for(int i=head[x];i;i=ne[i])
		{
			int c=e[i];
			t=v*y+c;
			if(!m[t])
			{
				m[t]=1;
				m[v*c+y]=1;
				s--;
			}
		}
		for(int i=head[y];i;i=ne[i])
		{
			int c=e[i];
			t=v*x+c;
			if(!m[t])
			{
				m[t]=1;
				m[v*c+x]=1;
				s--;
			}
		}
	}
	printf("%lld",s);
	return 0;
}
```

---

## 作者：block_in_mc (赞：1)

## 题意简述

$n$ 个人中，有 $p$ 对朋友，$q$ 对敌人。其他人都互相是陌生人。两个人 $a,\ b$ 不握手当且仅当出现以下三种情况的一个：

* $a,\ b$ 是敌人；
* $a$ 的朋友之一是 $b$ 的敌人；
* $b$ 的朋友之一是 $a$ 的敌人。

求握手次数。

## 思路

直接求握手次数不好求。考虑用所有可能的握手次数减去不会握手的人的对数。

所有可能的握手次数很好求：$\dfrac{n(n-1)}{2}$，对于 $n$ 个人，每个人都能跟其他 $n-1$ 个人握手。但是这样 $a\rightarrow b$ 和 $b \rightarrow a$ 都被算进去了，答案要除以 $2$。

现在来看不会握手的人的对数。首先，敌人都不会握手，因此答案要减去 $p$；对于后两种情况，用一个变量记录不会握手的人的对数，这样操作：

* 枚举每一个人；
* 对于每一个人 $i$，枚举 $i$ 的朋友；
* 对于每一个朋友 $f$，枚举 $f$ 的敌人；
* 对于每一个敌人 $j$，$(i,\ j)$ 不会握手。

但是这样可能会一组重复考虑多次，比如 $1$ 和 $2,\ 3$ 是朋友，$2,\ 3$ 和 $4$ 是敌人，$(1,\ 4)$ 就被枚举了两次。

考虑使用 `map<pair<int, int>, int>` 来存储 $i$ 是否已经确定会不会与 $j$ 握手。枚举时，如果不确定，不会握手的数量加一，并设为确定。特别地，输入朋友与敌人时这两个人是否会握手就确定了。

要注意的是，$i$ 与 $j$ 会握手，$j$ 与 $i$ 也会握手。反之同理。

**记得开 `long long`！**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node { vector<int> f, e; } pe[1001000];
map<pair<int, int>, int> m;
int n, p, q, cnt, tmp1, tmp2;
int main() {
    scanf("%d%d%d", &n, &p, &q);
    for (int i = 1; i <= p && scanf("%d%d", &tmp1, &tmp2); i++) pe[tmp1].f.push_back(tmp2), pe[tmp2].f.push_back(tmp1), m[{tmp1, tmp2}]++, m[{tmp2, tmp1}]++;
    for (int i = 1; i <= q && scanf("%d%d", &tmp1, &tmp2); i++) pe[tmp1].e.push_back(tmp2), pe[tmp2].e.push_back(tmp1), m[{tmp1, tmp2}]++, m[{tmp2, tmp1}]++;
    for (int i = 1; i <= n; i++) for (int j : pe[i].f) for (int k : pe[j].e) if (!m[{i, k}]) cnt++, m[{i, k}]++, m[{i, j}]++;
    printf("%lld\n", (long long) n * (n-1) / 2 - q - cnt);
    return 0;
}
```

---

