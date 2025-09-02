# Socks

## 题目描述

Arseniy is already grown-up and independent. His mother decided to leave him alone for $ m $ days and left on a vacation. She have prepared a lot of food, left some money and washed all Arseniy's clothes.

Ten minutes before her leave she realized that it would be also useful to prepare instruction of which particular clothes to wear on each of the days she will be absent. Arseniy's family is a bit weird so all the clothes is enumerated. For example, each of Arseniy's $ n $ socks is assigned a unique integer from $ 1 $ to $ n $ . Thus, the only thing his mother had to do was to write down two integers $ l_{i} $ and $ r_{i} $ for each of the days — the indices of socks to wear on the day $ i $ (obviously, $ l_{i} $ stands for the left foot and $ r_{i} $ for the right). Each sock is painted in one of $ k $ colors.

When mother already left Arseniy noticed that according to instruction he would wear the socks of different colors on some days. Of course, that is a terrible mistake cause by a rush. Arseniy is a smart boy, and, by some magical coincidence, he posses $ k $ jars with the paint — one for each of $ k $ colors.

Arseniy wants to repaint some of the socks in such a way, that for each of $ m $ days he can follow the mother's instructions and wear the socks of the same color. As he is going to be very busy these days he will have no time to change the colors of any socks so he has to finalize the colors now.

The new computer game Bota-3 was just realised and Arseniy can't wait to play it. What is the minimum number of socks that need their color to be changed in order to make it possible to follow mother's instructions and wear the socks of the same color during each of $ m $ days.

## 说明/提示

In the first sample, Arseniy can repaint the first and the third socks to the second color.

In the second sample, there is no need to change any colors.

## 样例 #1

### 输入

```
3 2 3
1 2 3
1 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 2 2
1 1 2
1 2
2 1
```

### 输出

```
0
```

# 题解

## 作者：OldVagrant (赞：7)

## 题意
有一个长度为 $n$ 的整数序列 $a$，值域为 $[1,k]$，有 $m$ 个限定条件，每个限定条件会给定一组下标 $(x,y)$，要求 $a_x=a_y$，问最少修改多少个数的值可以使得这些条件被全部满足。   
$2\le n\le 2\times 10^5,0\le m\le 2\times10^5,1\le k\le2\times 10^5$。
## Solution
不难发现，这些限定条件之间的关系是具有传递性的，即如果 $a_x=a_y$ 且 $a_y=a_z$，那么 $a_x=a_z$，这启发我们使用并查集来维护这些数之间的关系。 
对于每组下标 $(x,y)$ 我们把 $x,y$ 所在的集合合并（注意不是合并原序列里面的数），合并完之后会形成多个下标集合，而题目的要求就是修改若干个数，使得各个集合内的数对应的原序列的数全部相等，还要求修改次数最少。    
暂且把原序列中下标在某一集合内并且出现次数最多的数叫 $b_i$，那么最优的方案就是把该集合对应的原序列中的数全部改为 $b_i$，这样修改次数一定最少。如果有多个出现次数相同的 $b_i$，随便改一个即可，该集合对答案的贡献即为集合大小减去 $b_i$ 出现的次数。对其他集合同理，每处理完一个集合记得清空计数数组。
## Code
~~最优解rk1&rk3，rk1是小号的~~。
```c
#include <bits/stdc++.h>
using namespace std;
int fa[200001],a[200001],x,y,size[200001],col[200001],f[200001],ff[200001],fk;
vector<int> fff[200001];
bool ap[200001];
const int LEN=16384;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57) ch=gc();
	while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);//路径压缩，直接把该点的父亲节点改为集合代表
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;//如果两者已经在同一集合内则无需合并
	if(size[x]<size[y]) swap(x,y);//启发式合并，把小的合并到大的里面
	fa[y]=x,size[x]+=size[y];
}
signed main(){
	int n=read(),m=read(),k=read(),cnt=0,ans=0;
	if(m==0){//如果没有限定条件就不用改。
	    putchar('0');
	    return 0;
	}for(int i=1;i<=n;i++) a[i]=read(),fa[i]=i,size[i]=1;//初始化，每个集合最初的大小都为1.
	for(int i=1;i<=m;i++) x=read(),y=read(),merge(x,y);//合并下标（x,y）所在集合。
	for(int i=1;i<=n;i++){
		int fat=find(i);
		if(ap[fat]==0) ap[fat]=1,f[fat]=++cnt,ff[cnt]=fat;//如果该集合的代表未出现过，那么这就是一个新的集合，cnt为该集合的编号，fat为该集合的代表，f和ff数组用于在知道编号和集合代表中的一个的前提下快速找到对应的另一个。
	}for(int i=1;i<=n;i++) fff[f[find(i)]].push_back(i);//把每个下标都放到所在的集合的vector里。
	for(int i=1;i<=cnt;i++){
		int sz=fff[i].size(),zs=0;
		for(int j=0;j<sz;j++){
			fk=fff[i][j],col[a[fk]]++;
			if(col[a[fk]]>zs) zs=col[a[fk]];//更新每个集合对应的出现次数最多的数 的出现次数。  
		}ans+=size[ff[i]]-zs;//统计到答案里
		for(int j=0;j<sz;j++) fk=fff[i][j],col[a[fk]]=0; //清空计数数组
	}printf("%d",ans);
	return 0;
}
```


---

## 作者：quarmer (赞：7)

## 题意

都清楚，咕了

## 思路
题目要求对于第 $i$ 天的两个袜子颜色相同

那么如果有一天穿了 $i$ 号袜子和 $j$ 号袜子，另一天穿了 $i$ 号袜子和 $k$ 号袜子，那么不难发现相等的关系具有传递性，即第 $i$，$j$，$k$ 三只袜子颜色全相同

对于这种有传递性的关系，一般用并查集来维护，讲颜色需要相同的袜子编号合并。对于每个集合，找到在此集合中出现次数最多的颜色出现的次数，再用这个集合元素的数量减去这个次数，显然的，这是最小修改次数。最后将每个集合最小修改次数累加，就是我们要的答案。

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include<unordered_map>
using namespace std;
//#define  long long int
//#define int long long
//#define int __int128
#define ff first
#define ss second
#define mr make_pair
const int mod = 1e9 + 7 ;
int fa[200005] ; 
int n, k, m ;
int c[200005] ;
int t[200005] ;
int vis[200005] ;
int num ;
unordered_map<int, int>mp ;
int find(int x) {
	if(fa[x] == x) return fa[x] ;
	return fa[x] = find(fa[x]) ;
}
void join(int x, int y) {
	int fx = find(x), fy = find(y) ;
	if(fx != fy) fa[fx] = fy ; 
}
vector<int>zc ;
vector<int>s[200005] ;
signed main() {
	for(int i = 1 ; i <= 200000 ; i++) fa[i] = i ;
	cin >> n >> m >> k ;
	for(int i = 1 ; i <= n ; i++) scanf("%d", c + i) ;//其实这个没什么卵用
	for(int i = 1 ; i <= m ; i++) {
		int x, y ;
		scanf("%d%d", &x, &y) ;
		if(!vis[x]) num++ ;
		if(!vis[y]) num++ ; //num为用到的原色一共有多少种
		vis[x] = vis[y] = 1 ;
		join(x, y) ;
	}
	for(int i = 1 ; i <= n ; i++) {
		s[find(i)].push_back(i); 
		if(fa[i] == i && vis[i]) zc.push_back(i);
	}
	// zc中存的是每个集合的祖宗
	// s[i]表示以i为祖宗的集合的所有元素
	int ans = 0, nns = 0 ;
	for(int i = 0 ; i < zc.size() ; i++) {
		mp.clear() ;
		int now = zc[i] ;
		for(int j = 0 ; j < s[now].size() ; j++) {
			int k = s[now][j] ;
			mp[c[k]]++ ;
			nns = max(nns, mp[c[k]]) ;
		}
		ans += nns ;nns = 0 ;
	}
	cout << num - ans ;
	return 0 ;
}
```


---

## 作者：顾z (赞：4)

> ### Description
>
> 有$n$只袜子，$k$种颜色，在$m$天中，问最少修改几只袜子的颜色，可以使每天要穿的袜子颜色相同。 
>
> ### Input
>
> 第一行$n,m,k$分别对应题目描述。
>
> 接下来$m$行每行两个整数$l_i，r_i$表示第$i$天要穿的两只袜子的编号。
>
> ### Output
>
> 一个整数,代表最小要修改几只袜子的颜色。

首先,对于每一天要穿的袜子,我们加入同一个并查集。(这个很明显吧)

如果有一只袜子需要被穿多次的话,

显然我们会将其染成当前联通块中包含袜子最多的一种颜色。

我们用$vector$维护每个联通块中的袜子的颜色。

再开$vis$数组维护每种袜子的出现次数。(**注意要清空**)

每次我们累加的答案就是$size-mx$

> 其中$size$为联通块大小,$mx$为颜色相同的最多的袜子的个数。

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
#define R register

using namespace std;

const int gz=200001;

inline void in(R int &x)
{
    int f=1;x=0;char s=getchar();
    while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
    while(isdigit(s)){x=x*10+s-'0';s=getchar();}
    x*=f;
}

vector<int>v[gz];

int col[gz],f[gz],n,m,k,ans,vis[gz];

int find(R int x){return f[x]==x?x:f[x]=find(f[x]);}

signed main()
{
    in(n),in(m),in(k);
    for(R int i=1;i<=n;i++)in(col[i]),f[i]=i;
    for(R int i=1,x,y;i<=m;i++)
    {
        in(x),in(y);
        R int fa=find(x),fb=find(y);
        if(fa==fb)continue;
        f[fa]=fb;
    }
    for(R int i=1;i<=n;i++)
    {
        R int fa=find(i);
        v[fa].push_back(col[i]);
    }
    
    for(R int i=1;i<=n;i++)
    {
        R int tmp=v[i].size();
        R int mx=0;
        if(tmp>1)
        {
            for(R int j=0;j<tmp;j++)
            {
                vis[v[i][j]]++;
                mx=max(mx,vis[v[i][j]]);
            }
            for(R int j=0;j<tmp;j++)
                vis[v[i][j]]--;
            ans+=tmp-mx;
        }
    }
    printf("%d",ans); 
}

```



---

## 作者：Fan_Tuan (赞：1)

## 题意：
有 $n$ 只颜色的袜子，有 $m$ 天，每天必须穿 $l$，$r$ 俩个编号的袜子，可以将袜子进行染色，如果想要每次穿的袜子是同一种颜色，问最少染多少次？

## 思路：
可以将 $m$ 天看做 $m$ 条边，最终会处理成若干个连通块，则问题就转化为了将每个联通块中的点染成同一种颜色所需要的次数的和的最小值。

遍历每个连通块，用 vector 将这个连通块中的袜子存放起来，遍历 vector，然后用 map 记录中这个联通块中同种颜色袜子的个数，将这个连通块中的总袜子数减去颜色最多袜子数即为当前连通块中的点染成同一颜色所需要的最小值，将每个连通块所需要的最小值都累加起来即为最终染色次数。

## 代码
```c
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
using  namespace  std;

inline int read() {
	int f = 0, s = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 200010;
int n, m, k, ans, cnt, fa[maxn], color[maxn], num[maxn];

vector<int> v[maxn];
map<int, int> mp;

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

signed main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) color[i] = read();
	for (int i = 1; i <= m; i++) {
		int l, r;
		l = read(), r = read();
		int fl = find(l);
		int fr = find(r);
		if (fl != fr) fa[fr] = fl;
	}
	for (int i = 1; i <= n; i++) if (fa[i] == i) num[i] = ++cnt;
	for (int i = 1; i <= n; i++) v[num[find(i)]].push_back(color[i]);
	for (int i = 1; i <= cnt; i++) {
		int siz = v[i].size(), maxx = 0;
		mp.clear();
		for (int j = 0; j < siz; j++) {
			mp[v[i][j]] ++;
			maxx = max(maxx, mp[v[i][j]]);
		}
		ans += (siz - maxx);
	}
	print (ans);
	return 0;
}
```

---

## 作者：tommymio (赞：1)

写并查集的时候看了一眼，非常 $\text{Naive}$ 的题目。

先并查集处理出哪些袜子颜色必须相同，然后枚举每个颜色相同的块，在这个块里找到一个颜色最多的（并非颜色种数最多），认为这种颜色不需要被修改而其他需要被修改。

其实我们可以想到更具有拓展性的做法，如果在每次添加一双袜子后附加一次询问呢？（大雾

**Show the Code**

```cpp
#include<cstdio>
#include<vector>
int a[200005],fa[200005],t[200005];
std::vector<int> vec[200005]; 
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
} 
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline void merge(int x,int y) {int fx=find(x),fy=find(y); if(fx!=fy) fa[fx]=fy;} 
int main() { 
	int n=read(),m=read(),k=read(),ans=0;
	for(register int i=1;i<=n;++i) {a[i]=read();fa[i]=i;}
	for(register int i=1;i<=m;++i) {int l=read(),r=read();merge(l,r);}
	for(register int i=1;i<=n;++i) {vec[find(i)].push_back(i);}
	for(register int i=1;i<=n;++i) {
		int mx=0;
		for(register int j=0;j<vec[i].size();++j) ++t[a[vec[i][j]]];
		for(register int j=0;j<vec[i].size();++j) {if(mx<t[a[vec[i][j]]]) mx=t[a[vec[i][j]]];}
		for(register int j=0;j<vec[i].size();++j) --t[a[vec[i][j]]]; 
		ans+=vec[i].size()-mx;
	} 
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：傅思维666 (赞：0)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11797495.html)

~~2019.11.5模拟赛95分场~~

题目翻译还挺好的，可以看一下。

我们发现，如果有一只袜子需要在$m$天中的多天出现，那么显然这只袜子要与所有和它配对的袜子颜色一样。

以此联想，我发现：这个关联关系是一张图，图上的节点就是袜子的编号，图的边表示这两只袜子要颜色一样。

那么我们发现，**对于这张图的每一个连通块来讲，它的颜色必须是全部一样的**。那么，对于这个连通块来讲，最优的决策（即修改最少）就是这个子图的全部节点数减去这个子图中出现颜色最多的颜色数。这一点不太明白的小伙伴可以看样例画图解决。

思路出来了：

依题意建图，在图上进行深搜，统计每张子图的节点数和出现次数最多的颜色出现了几次，累加答案即可。

~~于是T到了95~~感谢出题人@littleseven

一开始我使用了计数数组，每次深搜一张子图我清零一次(memset).

后来我学到了一种叫做$map$的容器，因为这个容器的时间复杂度是$log$级别的，而且它提供的映射操作能够统计题目信息，所以我们选用这个东西来优化实现复杂度/

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int maxn=2*1e5+10;
int n,m,k,tmp,ans,t;
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
bool v[maxn];
map<int,int> mp;
map<int,int>::iterator it;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48){if(ch=='-')f=-1;ch=nc();}
    while(ch>47)    x=(((x<<2)+x)<<1)+ch-48,ch=nc();
    return x*f;
}
int col[maxn];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs(int x)
{
    v[x]=1;
    mp[col[x]]++;
    tmp++;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(v[y])
            continue;
        dfs(y);
    }
}
int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)
        col[i]=read();
    for(int i=1;i<=m;i++)
    {
        int x,y;
        x=read();y=read();
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=n;i++)
        if(!v[i])
        {
            tmp=0,mp.clear(),t=0;
            dfs(i);
            for(it=mp.begin();it!=mp.end();it++)
                t=max(t,it->second);
            ans+=(tmp-t);
        }
    printf("%d",ans);
    return 0;
}
```



---

