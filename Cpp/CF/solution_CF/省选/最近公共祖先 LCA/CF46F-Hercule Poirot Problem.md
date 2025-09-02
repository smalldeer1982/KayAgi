# Hercule Poirot Problem

## 题目描述

Today you are to solve the problem even the famous Hercule Poirot can't cope with! That's why this crime has not yet been solved and this story was never included in Agatha Christie's detective story books.

You are not informed on what crime was committed, when and where the corpse was found and other details. We only know that the crime was committed in a house that has $ n $ rooms and $ m $ doors between the pairs of rooms. The house residents are very suspicious, that's why all the doors can be locked with keys and all the keys are different. According to the provided evidence on Thursday night all the doors in the house were locked, and it is known in what rooms were the residents, and what kind of keys had any one of them. The same is known for the Friday night, when all the doors were also locked. On Friday it was raining heavily, that's why nobody left the house and nobody entered it. During the day the house residents could

- open and close doors to the neighboring rooms using the keys at their disposal (every door can be opened and closed from each side);
- move freely from a room to a room if a corresponding door is open;
- give keys to one another, being in one room.

"Little grey matter" of Hercule Poirot are not capable of coping with such amount of information. Find out if the positions of people and keys on the Thursday night could result in the positions on Friday night, otherwise somebody among the witnesses is surely lying.

## 样例 #1

### 输入

```
2 1 2
1 2
Dmitry 1 1 1
Natalia 2 0
Natalia 1 1 1
Dmitry 2 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 4 3
1 3
1 2
2 3
3 4
Artem 1 1 4
Dmitry 1 1 2
Edvard 4 2 1 3
Artem 2 0
Dmitry 1 0
Edvard 4 4 1 2 3 4
```

### 输出

```
NO
```

# 题解

## 作者：封禁用户 (赞：3)

~~一看就是道搜索题，然而本蒟蒻并不会搜索~~

如果直接搜索，要记录的状态很多，要记录人的位置，钥匙的位置，每扇门的状态......而且代码也很难打

因此，我们可以换一种搜索方法：

显然，题目中给的操作都是可逆的，我们可以定义一种中间状态：能开的门都开了，能在一起的人都聚在一起。如果开始和结果都能转移到中间状态，就是YES，否则就是NO。

以为n<=1000所以可以写n^2的代码

用我们可爱的并查集来处理连通块。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int parent[N],rnk[N];
struct UnionFind
{
	UnionFind(int n)
	{
		for(int i=0;i<n;i++)
		{
			parent[i]=i;
			rnk[i]=1;
		}
	}
	int root(int x)
	{
		if(parent[x]!=x)
			parent[x]=root(parent[x]);
		return parent[x];
	}
	void connect(int x,int y)
	{
		int rx=root(x),ry=root(y);
		if(rx==ry)
			return;
		if(rx>ry)
		{
			parent[ry]=rx;
			rnk[rx]+=rnk[ry];	
		} 
		if(rx<=ry)
		{
			parent[rx]=ry;
			rnk[ry]+=rnk[rx];
		}
	}
};
map<string,int>mp;
int n,m,k;
int key[2][N],people[2][N];
bool connected[2][N][N];
int s[N],t[N];
char buf[100];
void func(int id)
{
	UnionFind uf(n);
	for(int iter=0;iter<n+10;iter++)
	{
		for(int i=0;i<m;i++)
		{
			int room=uf.root(key[id][i]);
			if(uf.root(s[i])==room||uf.root(t[i])==room)
				uf.connect(s[i],t[i]);
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			connected[id][i][j]=(uf.root(i)==uf.root(j));
}
bool can()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(connected[0][i][j]!=connected[1][i][j])
				return false;
	for(int i=0;i<m;i++)
		if(!connected[0][key[0][i]][key[1][i]])
			return false;
	for(int i=0;i<k;i++)
		if(!connected[0][people[0][i]][people[1][i]])
			return false;
	return true;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&s[i],&t[i]);
		s[i]--;
		t[i]--;
	}
	for(int i=0;i<k;i++)
	{
		scanf("%s",buf);
		string str=buf;
		mp[str]=i;
		int room;
		scanf("%d",&room);
		room--;
		people[0][i]=room;
		int c;
		scanf("%d",&c);
		for(int j=0;j<c;j++)
		{
			int e;
			scanf("%d",&e);
			e--;
			key[0][e]=room;
		}
	} 
	for(int i=0;i<k;i++)
	{
		scanf("%s",buf);
		string str=buf;
		int p=mp[buf];
		int room;
		scanf("%d",&room);
		room--;
		people[1][p]=room;
		int c;
		scanf("%d",&c);
		for(int j=0;j<c;j++)
		{
			int e;
			scanf("%d",&e);
			e--;
			key[1][e]=room;
		}
	}
	func(0);
	func(1);
	bool ans=can();
	cout<<(ans?"YES":"NO")<<endl;
	return 0;
}

```

---

## 作者：Yuby (赞：2)

upd 2022.05.17：删掉了一张无用的图

[题面](https://www.luogu.com.cn/problem/CF46F)

点数：2300

##### 分析：

$n \leq 1000$ 所以说这题复杂度直接肯定 $O(n^2)$ 左右。

很明显这题非常图论(因为其他算法做不了啊)，门就是边，但能不能走某一条边是有条件的，就是钥匙的问题。

按照这个思路能走到的地方就是一个连通块。

注意到题目中给出了起始和结束的房间和钥匙，于是我们可以双向的搜一下。

这是我们加入并查集维护连通块，这样拿到另一把钥匙就是合并连通块。

跑一遍合并一下能合并的。

最后验证一下所有的人的起始房间和结束房间、还有钥匙的起始房间和结束房间，是不是都在同一个连通块内就行了。

总复杂度：$O(nm)$

完整代码：


```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
#define fast_iostream ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;
const ld EPS=1e-8;
const ll INF=ll(1e9+7);
const ll LLINF=ll(1e18+7);
const ld LDEPS=1e-18;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline ld dmax(ld x,ld y){return x>y?x:y;}
inline ld dmin(ld x,ld y){return x<y?x:y;}
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(ll a,ll b){return a*b/gcd(a,b);}
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline ld dread(){ld x=0,d=0.1;char f=0,ch=getchar();while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch)) x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))x+=d*(ch^48),d*=0.1,ch=getchar();}return f?-x:x;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const ll MAXN=2007;
ll n,m,k;
struct node
{
	ll u,v;
}a[MAXN];
ll in[2][MAXN],key[2][MAXN];
bool con[2][MAXN][MAXN];
ll fa[MAXN],siz[MAXN];
map<string,ll>mp;
void initset(ll fa_size)
{
	for(ll i=0;i<fa_size;i++)fa[i]=i,siz[i]=1;
}
ll find(ll x)
{
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
void us(ll x,ll y)
{
	ll xx=find(x),yy=find(y);
	if(xx==yy)return ;
	if(xx>yy)
	{
		fa[yy]=xx;
		siz[xx]+=siz[yy];
	}
	else
	{
		fa[xx]=yy;
		siz[yy]+=siz[xx];
	}
}
string str;
void solve(ll id)
{
	initset(n+1);
	for(ll t=1;t<=n+1;t++)
	{
		for(ll i=1;i<=m;i++)
		{
			ll root=find(key[id][i]);
			if(find(a[i].u)==root||find(a[i].v)==root)us(a[i].u,a[i].v);
		}
	}
	for(ll i=1;i<=n;i++)
	{
		for(ll j=1;j<=n;j++)
		{
			con[id][i][j]=(find(i)==find(j));
		}
	}
}
bool check()
{
	for(ll i=1;i<=n;i++)
	{
		for(ll j=1;j<=n;j++)
		{
			if(con[0][i][j]!=con[1][i][j])return 0;
		}
	}
	for(ll i=1;i<=m;i++)
	{
		if(!con[0][key[0][i]][key[1][i]])return 0;
	}
	for(ll i=1;i<=k;i++)
	{
		if(!con[0][in[0][i]][in[1][i]])return 0;
	}
	return 1;
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	n=read(),m=read(),k=read();
	for(ll i=1;i<=m;i++)
	{
		a[i].u=read(),a[i].v=read();
	}
	for(ll i=1;i<=k;i++)
	{
		cin>>str;
		mp[str]=i;
		in[0][i]=read();
		ll num=read();
		for(ll j=1;j<=num;j++)
		{
			key[0][read()]=in[0][i];
		}
	}
	for(ll i=1;i<=k;i++)
	{
		cin>>str;
		ll pos=mp[str];
		in[1][i]=read();
		ll num=read();
		for(ll j=1;j<=num;j++)
		{
			key[1][read()]=in[1][i];
		}
	}
	solve(0),solve(1);
	if(check())puts("YES");
	else puts("NO");
	return 0;
}
```



---

