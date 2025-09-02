# Forming Teams

## 题目描述

One day $ n $ students come to the stadium. They want to play football, and for that they need to split into teams, the teams must have an equal number of people.

We know that this group of people has archenemies. Each student has at most two archenemies. Besides, if student $ A $ is an archenemy to student $ B $ , then student $ B $ is an archenemy to student $ A $ .

The students want to split so as no two archenemies were in one team. If splitting in the required manner is impossible, some students will have to sit on the bench.

Determine the minimum number of students you will have to send to the bench in order to form the two teams in the described manner and begin the game at last.

## 样例 #1

### 输入

```
5 4
1 2
2 4
5 3
1 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
6 2
1 4
3 4
```

### 输出

```
0```

## 样例 #3

### 输入

```
6 6
1 2
2 3
3 1
4 5
5 6
6 4
```

### 输出

```
2```

# 题解

## 作者：_Chesed_ (赞：4)

# [CF216B Forming Teams](https://www.luogu.com.cn/problem/CF216B)
## 题意
给出 $n$ 个人，$m$ 个关系，有 $m$ 个人互相仇视，要求将人分成**人数相同的**两组，互相仇视的点不在同一组。

## 分析
处理关系问题考虑转化为图论问题，人抽象成点，关系抽象成边，由于每个人至多仇视 2 个人，因此每个点的度数至多为 2，那么整张图一定是由**独立的点，链和环构成的**。题意要求分成两组人数相同的，因此将上述三种情况拆成两半就可以产生贡献。

点和链可以合并讨论，因为当孤点的个数与链的长度皆为奇数时可以将链断成一条奇数的链与一条偶数的链，将孤点插入奇数长度链来凑成一条偶数长度的链。

考虑使用并查集来维护点之间的关系，一个连通块的 $size$，特判环，链和点。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct dsu{
	int fa,sz;
}dsu[1000005];
int n,m,ans;
void Init(){//初始化并查集
	for(int i=1;i<=n;i++){
		dsu[i].fa=i;
		dsu[i].sz=1;
	}
}
int Belong(int x){//查找集合的根
	if(dsu[x].fa!=x)
		dsu[x].fa=Belong(dsu[x].fa);
	return dsu[x].fa;
}
void Union(int x,int y){
	int rt_x,rt_y;
	rt_x=Belong(x);
	rt_y=Belong(y);
	if(rt_x!=rt_y){//处理合并
		dsu[rt_y].fa=rt_x;
		dsu[rt_x].sz+=dsu[rt_y].sz;
	}
	else if(dsu[rt_x].sz%2==1) ans++;//特判环
}
int main(){
	scanf("%d%d",&n,&m);
	Init(); 
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		Union(u,v);
	}
	if((n-ans)%2==1) ans++;//特判链和边
	printf("%d",ans);
}
```


---

## 作者：CaiXY06 (赞：4)

# Solution

看到神犇们都用 **dfs** ，那我就写一篇并查集的题解吧。

我们将互相仇视的人连边。

由于每个学生最多仇视两个人，所以会出现三种情况。

- 点

- 链

- 环

由于要分成两队人数一样的，所以每次将一种情况拆成两半就会产生贡献。

- 孤点的个数为奇数

- 链长为奇数

- 环长为奇数

很显然点和链的情况可以合并考虑（链拆成两半，一半为奇数，一半为偶数，将孤点插入奇数那一半）

那么我们就可以用并查集，
维护一个集合内的元素个数，判环，最后特判链和点，计算答案。

附上二十行极简代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[110],ans,siz[110];
inline int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;//并查集预处理
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		int fx=find(x);
		int fy=find(y);
		if(fx!=fy)fa[fy]=fx,siz[fx]+=siz[fy];//合并集合
		else if(siz[fx]&1)ans++;//如果出现环的情况
	}
	if((n-ans)&1)ans++;//特判链和点
	printf("%d",ans);
	return 0;
}
```


---

## 作者：sodalyghat (赞：2)

### 思路
注意到题目里有这么一句话：每个人至多仇视两个人。稍微转化一下，如果把他们的仇视关系看做一个无向图，也就是代表着这个图里只有点、链和环。这样一来，这道题就很好办了。对于每一个连通块，二分图染色判定一下奇环即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ac{
	const int MAXN = 105;
	int n, m, tag[MAXN], ans, u, v, num, c;
	int head[MAXN], cnt;
	struct node{
		int next, to;
	}ed[2 * MAXN];
	void add_edge(int u, int v){
		ed[++cnt].next = head[u];
		ed[cnt].to = v;
		head[u] = cnt;
	}
	void color(int u, int fa){
		if(!u) return ;
		num++;
		for(int i = head[u];i;i = ed[i].next){
			int v = ed[i].to;
			if(v == fa) continue;
			if(tag[v]){
				c = 1;
				continue;
			} 
			tag[v] = 1;
			color(v, u);
		}
	}
	int main(){
		scanf("%d%d", &n, &m);
		for(int i = 1;i <= m;i++){
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}for(int i = 1;i <= n;i++){
			tag[i] = 0;
		}for(int i = 1;i <= n;i++){
			if(!tag[i]){
				num = c = 0;
				tag[i] = 1;
				color(i, 0);
				ans += num & 1 & c;
			} 
		}printf("%d", ans + (n - ans & 1));
		return 0;
	}
} int main(){
	return ac::main();
}
```
### tips
题目中还说要分成人数相等的两组，所以最后判断一下奇偶性即可。


---

## 作者：saixingzhe (赞：1)

# 思路
每个人都只仇视至多 $2$ 个人，我们发现一定只存在**点、链、环**三种情况。

对于单独的点我们认为是有 $1$ 个点的链。

分开讨论：

* 对于一个环，我们发现偶数环可以平分成人数一样多的两组，而奇数环一定不行，会有两人互相仇恨，所以每个奇数环都要丢弃 $1$ 个人。

* 对于一条链，我们发现偶数链也是可以平分的，奇数链可以保证不互相仇恨，但每次分组会有一组多出来 $1$ 人。可以发现，如果有奇数条奇数链，我们要从中丢弃 $1$ 人，否则则不用。

## 实现

我们使用并查集维护，如果新输入的两点在同一连通块内则代表这是一个环，否则是一条链。

并查集也可以维护每个连通块的大小，将每个连通块的大小下放到父亲节点上，每次合并父亲节点即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,a[102][102],fa[102],sz[102],vis[102],ans,cnt;
int find(int x){
	if(fa[x]==x)	return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int u=find(x),v=find(y);
	if(u!=v){
		fa[u]=v;
		sz[v]+=sz[u];
		sz[u]=0;	
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		if(find(u)==find(v)&&sz[find(u)]&1) ans++,vis[find(u)]=1;
		else merge(u,v);
	}
	for(int i=1;i<=n;i++){
		if(!vis[find(i)]){
			vis[find(i)]=1;
			if(sz[find(i)]&1)  cnt++;
		} 
	}
	printf("%d",ans+(cnt&1));
    return 0;
}
```

---

## 作者：jamesharden666 (赞：1)

# CF216B

题目给出每个人至多仇视 $2$ 个人的性质，所以这个图只可能由环、链或点组成。

每个环、链、点之间独立，所以我们单独计算他们的贡献。

如果当前环的长度为偶数，那么这个环就不会做出贡献；

反之，总有一个人是不能放的。

如果当前链的长度为偶数，那么这条链同样不会做出贡献；

但是，当链的长度为奇数时，我们可以将空出的那个人当成一个点去看待。

最后，我们将所有单独点的个数统计出来，如果为奇数就会做出贡献，反之则不会。

具体实现参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[1000+10],p[1000+10],siz[1000+10],vis[1000+10],tot=0,ans=0;
set<int> s;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')	
		s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
int fd(int x)
{
	if(fa[x]==x)
		return x;
	else
		return fa[x]=fd(fa[x]);
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		fa[i]=i,siz[i]=1;
	for(int i=1;i<=m;++i)	
	{
		int u=read(),v=read();
		int x=fd(u),y=fd(v);
		if(x!=y)
			fa[y]=x,siz[x]+=siz[y];
		else
			p[x]=1;
		s.insert(x);
		s.insert(y);
	}
	for(int i=1;i<=n;++i)
	{
		if(s.find(i)!=s.end())
		{
			int u=fd(i);
			if(vis[u])
				continue;
			vis[u]=1;
			if(p[u])
				ans+=siz[u]&1;
			else
				tot+=siz[u]&1;
		}
		else
			tot++;
	}	
	ans+=tot&1;
	printf("%d",ans);
	return 0;
}
```



---

## 作者：TLE_AK (赞：1)

### 题意
给出 $n$ 人与 $m$ 条敌对关系，组成人数相同的 $2$ 队（队伍内的人都没有敌对关系），求不能加入这两个队伍的人数。
## 思路
首先**分成两组**与**关系**说明了需要构造出一个二分图（表示队伍关系），考虑用种类并查集维护（也可用 dfs 染色）。

但是我们还需要让**人数相同**，仔细观察发现有一个“至多仇视 $2$ 个人”，说明妹最多有 $3$ 种情况：  
1. 是孤立点
2. 在链里
3. 在环中  

对于在环中的点，奇环必定会剩下一个分不了（见下图，一定有点被红线分割）,而偶环不会(可以直接被切开）。

![233](https://cdn.luogu.com.cn/upload/image_hosting/u333rugd.png)

而对于链而言，我们可以用几个孤立点来拼成偶链，直到拼不了就可以放弃了。

### 代码
```
#include<bits/stdc++.h>

using namespace std;
namespace akak
{
	int fa[110],sz[110];
	int belong(int u)
	{
		if(fa[u]!=u)return fa[u]=belong(fa[u]);
		return u;
	}
	int main()
	{
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			fa[i]=i;
			sz[i]=1;
		}//初始化
		int ans=0;
		for(int i=1;i<=m;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			int al=belong(a),bl=belong(b);
			if(al==bl)//利用并查集来判环
			{
				if(sz[al]&1)//奇环
				{
					ans++;
					sz[al]--;之后不会判重
				}
				continue;
			} 
			fa[bl]=al;
			sz[al]+=sz[bl];
		}
		int num=0;
		for(int i=1;i<=n;i++)//判断链
		{
			if(fa[i]==i)
			{
				num+=sz[i];
			}
		}
		ans+=num&1;//没得选
		cout<<ans;
		return 0;
	} 
}
int main()
{

	akak::main();
	return 0;
}
```

---

## 作者：Oscar12345 (赞：1)

```
#include<bits/stdc++.h>
using namespace std;

int t[111],s[111],a,b,c,d,x,y;
int n=0;

int f(int p)
{
	return p==t[p] ? p : f(t[p]);
}

int main()
{
	cin>>a>>b;
	for(int i=0;i<=a;i++)
	{
		t[i]=i,s[i]=1;
	}

	while(b--)
	{
		cin>>c>>d;
		x=f(c),y=f(d);
		if(x==y&&(s[x]&1))
			n++;
		t[y]=t[x],s[x]+=s[y];
	}

	if((a-n) & 1)
	{
		n++;
	}
	cout<<n;
	return 0;
}

```

---

## 作者：DengDuck (赞：0)

首先你把问题转成图论问题，厌恶关系变成边，问题变成怎么在无向图中删最少的点，使得图变成一个可以黑白染色的图（二分图）。

重点是你要看到那句度数不超过 $2$，所以连通块只能是链或者环，对于环，如果是奇环，你就得找一个删了，删哪个都一样，你记一下就行。

然后你看看，如果删了这些点剩下的点是奇数，那么根据题意，随机杀死一名幸运观众即可，你把答案加一。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=205;
LL n,m,x,y,vis[N],hav[N],cnt,ans;
vector<LL>v[N];
void dfs(LL x,LL f,LL c)
{
	if(vis[x]==c)
	{
		if(hav[c]==0&&cnt%2==1)ans++;
		hav[c]=1;
		return;
	}
	if(vis[x]==2)return;
	cnt++;
	vis[x]=c;
	for(LL i:v[x])
	{
		if(i==f)continue;
		dfs(i,x,c);
	}
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		cnt=0;
		if(!vis[i])dfs(i,0,i);
	}
	if((n-ans)%2==1)ans++;
	printf("%lld",ans);
}
```

---

## 作者：Mine_King (赞：0)

## Problem

[CF216B Forming Teams](https://www.luogu.com.cn/problem/CF216B)

**题目大意：**

$n$ 个人有 $m$ 条关系，每条关系表示两个人互为敌对。每个人最多有两个敌对的人。问最多有多少人使得这些人可以分成**人数相等**两组且每组的人互相不为敌对关系。

**输出不能分组的人数。**

## Solution

我们把每个人当做点，关系当做边。那么点的度数最多是 $2$。  
所以每个连通子图都只有三种情况，分别是点、链、环。

对于点：显然可以任意分组。  
对于链：交叉分组，即相连的两个点分到不同的组。  
对于环：偶环与链相同。奇环必定会有一人无法参与分组。

所以我们可以考虑维护一个带权并查集记录集合大小，合并过程中遇到环判断一下即可。

但是，由于要求人数相等，所以最终还要判断剩余人的奇偶性。

## Code

```cpp
//Think twice,code once.
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,ans;
struct bin
{
	int f[105],sz[105];
	bin(){for(int i=1;i<=100;i++) f[i]=i,sz[i]=1;return ;}
	int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
	int query(int x,int y){return find(x)==find(y);}
	void merge(int x,int y)
	{
		if(query(x,y)&&sz[find(x)]%2) ans++;
		sz[find(y)]+=sz[find(x)];f[find(x)]=find(y);
		return ;
	}
}b;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		b.merge(u,v);
	}
	if((n-ans)%2) ans++;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：myEnd (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF216B)

这道题我的思路是并查集。我们知道在加入路径压缩优化后并查集的复杂度大概为 $O(\log^* n)$。所以可以通过此题。

> 对于 $\log^* x$ 的定义，如下：
> >- $x \le 1:0$
> > - $x > 1:1+\log^*(\log x)$

我们将互相仇视的人连边。根据题目所述，每个学生仇视的敌人最多有两个，每个联通子块只有三种情况，又由于要分成人数一样的两队，所以可以将每一种情况拆成两半，我们进行分讨：

- 点，可以理解为长为 $1$ 的链。
- 链，链长为偶数是可以自然地拆成两队，为奇数时将一个点归到少一人的那队即可。
- 环，当环长为偶数时类似于链，也很简单。

接下来讨论环长为奇数的情况。在此时，总有一人会要“坐板凳”，所以此时将答案加一即可。

参考代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace QIO
{
    // ...
}
using QIO::fixed;
using QIO::setPrecision;
using QIO::endline;

using ll=long long;

#define rep(i, a, n) for(int i=(a); i<=(n); ++i)
#define per(i, a, n) for(int i=(n); i>=(a); --i)

const int inf=0x3f3f3f3f;
const long long infll = 0x3f3f3f3f3f3f3f3f;

#define pb push_back
#define mp make_pair
using pii = pair<int, int>;
using VI = vector<int>;

#define fi first
#define se second

#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())

QIO::InputStream lym;
QIO::OutputStream hmz;

int n, m, fa[107], ans, siz[107], a, b;

int find(int x)
{
    return fa[x]==x ? x : fa[x]=find(fa[x]);
}

inline void merge(int a, int b)
{
    int fx=find(a), fy=find(b);
    if(fx != fy) fa[fy]=fx, siz[fx]+=siz[fy];
    else if(siz[fx]%2==1) ++ans;// 我们用这行来判奇环
}

signed main()
{
    const char endl='\n';

    cin >> n >> m;
    for(int i=1; i<=n; ++i) fa[i]=i, siz[i]=1;

    for(int i=1; i<=m; ++i)
    {
        cin>> a >> b;
        merge(a, b);
    }

    if((n-ans)&1) ++ans;// 最后还剩奇数个人，有一个人要“坐板凳”
    cout << ans;
    return 0;
}
```

---

## 作者：Z_M__ (赞：0)

题目翻译不全，少了一个条件：每个学生**最多只有2个**敌人。

把每个学生看做一个点，每条仇视关系看做边，因为每个学生最多只有2个敌人，即每个点最多有两条边，所以敌对关系只能是**环形**或**链形**。


---
所以所有学生分成3类：

1. 没有敌人的

2. 在链形敌对关系的

3. 在环形敌对关系的

---
- **没有敌人的**

设这类学生的人数为$num_1$

（1）当$num_1$为偶数时,则正好分成两队

（2）当$num_1$为奇数时，有一名学生坐板凳（因为两队人数要相等）

---
- **在链形敌对关系的**

设链长为$num_2$

（1）当$num_2$为偶数时：如$(1-2-3-4)$,则 1、3去A队，2、4去B队，没有人坐板凳。

（2）当$num_2$为奇数时：如$(1-2-3)$，则 1、3号去A队，当$num_1$为奇数时，2号与没有敌人的那一个可以到B队，当$num_1$为偶数时，2号只能坐板凳。

总结上面两种情况，我们可以将没有敌人的和在链形敌对关系的学生一起考虑（**即当$num_1+num_2\%=0$时有一位学生坐板凳，否则没有**）

---
最后
- **在环形敌对关系的**

设环长为$num_3$

（1）当$num_3$为偶数时：如$(1-2-3-4-1)$,则1、3去A队，2、4去B队

（2）当$num_3$为奇数时：如$(1-2-3)$,则1去A队，2去B队，3由于和1、2都为敌对关系，所以只能坐板凳

所以**每出现一个环长为奇数的就多一个坐板凳的**

----
所以坐板凳的学生数就等于**奇环的个数**，如果**不在环中的学生个数为奇数**则坐板凳的学生就**再多1个**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 10;
int n, m, cnt, root, sum, res;
int head[MAXN];
bool vis[MAXN];
struct node {
	int prev, v;
} e[MAXN << 1];
void add (int u, int v)
{
	e[++cnt].v = v;
	e[cnt].prev = head[u];
	head[u] = cnt;
}
bool dfs (int u, int fa)
{
	if (u == root && fa != -1) return true;
	vis[u] = 1;
	for (int i = head[u]; i; i = e[i].prev)
	{
		int v = e[i].v;
		if (v == fa) continue;
		sum++; // 统计环长
		if (dfs (v, u)) return true;
	}
	return false;
}
int main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		add (u, v);
		add (v, u);
	}
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			root = i, sum = 0;
			if (dfs (i, -1)) // 判断是否为环
	            if (sum & 1) // 判断环长是否为奇数
					res++;
		}
	}
	if ((n - res) & 1) // 判断不在环中的学生数是否为奇数
    	res++;
	cout << res << endl;
	return 0;
}
```

---

## 作者：CHENRUIJIE (赞：0)

这道题是一道dfs的题目。                        
话不多说，思路分析一下  
思路:  
我们发现只有奇数环和人数的奇偶才会影响到结果的人数，因为在奇数环中，一定会有一个收到双方的~~歧视~~，就必须做板凳，然而一条奇数链的话没有人会受到~~歧视~~但会因人数的奇偶影响到结果。	
下面附上代码：	
```cpp
#include<bits/stdc++.h>
#define vi vector<int>
#define pb push_back
#define op pop_back
using namespace std;
const int N=105;
vi v[N],c;
set<vi>s;
bool visit[N];
int n,m;
inline void dfs(int now,int root,bool begin,bool check)
{
	if(now==root&&!begin&&check)
	{
		vi c2=c;
		sort(c2.begin(),c2.end());
		s.insert(c2);
		return;
	}
	for(int i=0;i<v[now].size();i++)
	{
		if(!visit[v[now][i]])
		{
			c.pb(v[now][i]);
			visit[v[now][i]]=true;
			dfs(v[now][i],root,0,!check);
			c.op();
			visit[v[now][i]]=false;
		}
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		a--,b--;
		v[a].pb(b);
		v[b].pb(a);
	}
	for(int i=0;i<n;i++)
	{
		memset(visit,false,sizeof(visit));
		c.clear(),dfs(i,i,1,0);
	}
	cout<<s.size()+((n-s.size())%2==1);
}
```

---

## 作者：Error_Eric (赞：0)

### 前言

原来的翻译漏了很重要的条件。差评。

### 正文

这道题可以理解为给定一个**由链和环组成的**无向图，涂上红蓝两色，相邻的不能涂同样的颜色，红色蓝色数目需要相同，求最少剩下几个不涂色。（单独的一个结点被认为是一个链）

可以这样思考：

将连通块分类讨论。

把所有的链首尾相连，假设这个链的长度为 $L$ ，显然可以选中 $2\times\lfloor\frac{L}{2}\rfloor=L-(L\mod 2)$ 个涂色。

对于一个环，偶环可以全部涂色，奇环可以只剩下一个不涂色。

举个栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/sk12ym7m.png)

所以这道题就是结论题。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
#define rei register int
#define il inline
void readln(int&I){
    int f=1;I=0;char C=getchar();
    while(!isdigit(C))(C=='-')?(f=-1):0,C=getchar();
    while (isdigit(C))I=I*10+C-'0',C=getchar();I*=f;
}
bool czh;
struct graph{//图
    int n,m;
    struct edge{
        int fr,to,nxt;
        edge(int rf,int ot,int nx){fr=rf,to=ot,nxt=nx;}
        edge(){}
    };
    vector<edge>e;vector<int>fir;
    void add(int u,int v){
        e.push_back(edge(u,v,fir[u])),fir[u]=e.size()-1;}
    void read(){read(0);}
    void read(bool b){
        readln(n),readln(m);int iu,iv;
        for(rei ei=0;ei<=n;ei++)fir.push_back(-1);
        for(rei ei=1;ei<=m;ei++)readln(iu),readln(iv),add(iu,iv)
        ,(b?add(iv,iu):(void)0);
    }//链式前向星模板
    vector<int>v;
    void dfsinit(){for(rei i=0;i<=n;i++)v.push_back(0);}
    int dfscount(int root,int x,int fa){
        int res=1;if(v[x])return 0;else v[x]=1;
        for(rei i=fir[x];i!=-1;i=e[i].nxt){
            if(e[i].to==root)czh|=(fa!=root);
            else if(e[i].to!=fa)res+=dfscount(root,e[i].to,x);
        }
        return res;
    }
    int dfscount(int root){czh=0;return dfscount(root,root,-1);}//获得连通块的大小
    //dfs模板
    graph(){}graph(int xn,int xm){n=xn,m=xm;}
};int cnt;
int main(){
    graph g;g.read(1),g.dfsinit();int ans=0,nh=0;
    for(rei i=1;i<=g.n;i++)
        (g.v[i])?0:(cnt=g.dfscount(i),czh?(ans+=(cnt&1)):(nh+=cnt));
    //如果是环，那么答案加上(大小&1)，如果是链，(总长度+=长度)
    printf("%d\n",ans+(nh&1));
}
```

---

