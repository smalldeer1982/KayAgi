# News Distribution

## 题目描述

In some social network, there are $ n $ users communicating with each other in $ m $ groups of friends. Let's analyze the process of distributing some news between users.

Initially, some user $ x $ receives the news from some source. Then he or she sends the news to his or her friends (two users are friends if there is at least one group such that both of them belong to this group). Friends continue sending the news to their friends, and so on. The process ends when there is no pair of friends such that one of them knows the news, and another one doesn't know.

For each user $ x $ you have to determine what is the number of users that will know the news if initially only user $ x $ starts distributing it.

## 样例 #1

### 输入

```
7 5
3 2 5 4
0
2 1 2
1 1
2 6 7
```

### 输出

```
4 4 1 4 4 2 2 ```

# 题解

## 作者：A_Đark_Horcrux (赞：6)

可以看出，如果把每一个人看作一个结点，每个关系就相当于把关系里的所有人合并到同一个连通块中，很容易想到用并查集实现，每次输入一个关系可以任选一个人（比如第一个人）然后把其他人都合并到他的连通块里。

```cpp
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}//找爸爸（路径压缩）
...
k=read();//关系所包含的人数
		if(k)
		{
			yee=read();//输入第一个人
			for(j=2;j<=k;j++)
			{
				x=read();//对于输入的每一个人
				int p=find(x),q=find(yee);//找爸爸
				if(p!=q) f[q]=p;//合并
			}
		}
```

最后只要输出每个人所在的连通块里的人数就好了，可以开一个数组记录联通块大小，对每个人找出爸爸并让爸爸所在联通块的大小加一，最后输出即可。

```cpp
for(i=1;i<=n;i++) size[find(i)]++;
for(i=1;i<=n;i++) printf("%d ",size[find(i)]);
```



---

## 作者：AC_Dolphin (赞：3)

明显并查集板子题

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500010
using namespace std;
int fa[N],ans[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}//查找所在集合(fa)
int main()
{
	int n,i,k,j,t,m,lst;
    cin>>n>>m;
	for (i=1;i<=n;i++) fa[i]=i;//初始化
	for (i=1;i<=m;i++)
	{
		cin>>k;
        if (k==0) continue;//如果输入是0就直接continue
		cin>>t;lst=t;
		for (j=2;j<=k;j++)
		{
			cin>>t;int a=find(lst),b=find(t);
			fa[a]=b;//合并
		}
	}
	for (i=1;i<=n;i++) ans[find(i)]++;for (i=1;i<=n;i++) cout<<ans[find(i)]<<' ';//输出
    return 0;
}
```

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给出 $n$ 个人和 $m$ 组关系，可以把这 $n$ 个人分成若干组，输出每个人所在的组的人数。

#### 思路分析


------------
很明显需要使用并查集维护此题。

用并查集将这 $n$ 个人分组后记录每组的大小，输出即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdlib>
#define int long long

using namespace std;
const int N=500010;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int n,m,fa[N],siz[N];
int find(int x){
	if(fa[x] == x) return x;
	else return fa[x] = find(fa[x]);
}
signed main(){
    n = read() , m = read();
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        int cnt = read();
        if(!cnt) continue;
        int x = read();
        for(int i=1;i<cnt;i++){
            int y = read();
            int fx=find(x),fy=find(y);
            if(fx!=fy)fa[fx]=fy;
        }
    }
    for(int i=1;i<=n;i++){
		siz[find(i)]++;
	}
    for(int i=1;i<=n;i++){
		printf("%lld ",siz[find(i)]);	
	}
	return 0;
}
```


---

## 作者：墨舞灵纯 (赞：1)

仅存的题解非常神仙只有一句话，很难理解，我补充一点。

这题很显然要求每个点所在的连通块大小，由于是双向边，写tarjan可以但是有些麻烦。所以我们使用并查集，每次把在同一组的节点合并起来。

给一个合并部分的核心代码吧。其他代码参见现有的神仙题解。

$\mathcal\textcolor{LightBlue}{Code}$

```
void merge(int u,int v)
{
	int t1=fd(u),t2=fd(v);
	if(t1==t2) return;
	if(cnt[t1]>cnt[t2]){cnt[t1]+=cnt[t2];fa[t2]=t1;}
	else{cnt[t2]+=cnt[t1];fa[t1]=t2;}
}
```

---

## 作者：Tobiichi_Origami (赞：0)

这不就是一道**并查集**模板题嘛！

**题意**

有 $n$ 个人和 $m$ 组关系，每组关系包含若干人,对于每个人，求出其可以把一条消息传递给最多多少人。

**思路**

这道题其实就是求每个人的连通块里的人数，用并查集即可，所以，我们让每个人都连上自己那一组的第一个人，然后让每个人都找到自己的父亲结点的连通块个数就可以了。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[500001];
int a[500001];
int find(int x)
{
    if(f[x]==x) return x;
    else return f[x]=find(f[x]);
}
void merge(int x,int y)
{
    int p=find(x),q=find(y);
    if(p!=q) f[q]=p;
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x;
        if(!x) continue;
        cin>>y;
        int y2=y;
        for(int j=2;j<=x;j++)
        {
            cin>>y;
            merge(y2,y);
        }
    }
    for(int i=1;i<=n;i++) a[find(i)]++;
    for(int i=1;i<=n;i++) cout<<a[find(i)]<<" ";
    return 0;
}
```


---

## 作者：Steven_lzx (赞：0)

## Solution

本题题意就是求每个结点所在的连通块的大小。Tarjan 虽然可以但是非常麻烦，于是我们考虑用**并查集**来维护，最后统计时开一个数组 $ans$ 来维护连通块的大小。

## Code

这里仅给出关键代码。

```cpp
for(int i=1;i<=m;i++)
{
	k=fastio_read();
	if(!k)
	{
		continue;
	}
	last=t=fastio_read();
	for(int j=2;j<=k;j++)
	{
		t=fastio_read();
		fl=ufs_find(last);
		ft=ufs_find(t);
		fa[fl]=ft;
	}
}
for(int i=1;i<=n;i++)
{
	ans[ufs_find(i)]++;
}
```


---

## 作者：红尘仙 (赞：0)

### 【引言】：

这个题这么可爱 ~~（高价值）~~ ，竟然没有人做，太悲催了，所以我来了

---
### 【思路分析】：
我们发现，n 个人， m 个关系。我们假设其中一个点为 a ,那么与 a 相连的那一条边的点数，其实就是能传给别人的数。

那也就是一个并查集板子。

就这样就 OK 了。

其实最小生成树算法 Kruskal ，就已经包含了。

---
### 【code】：


```
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define fa point_to
const int maxn = 1e6;
using namespace std;
inline int read()
{
  int x=0 , f=1; char ch=getchar();
  while( !isdigit(ch) ){ if(ch == '-')f = -1; ch = getchar();}
  while( isdigit(ch) ){ x = x *10 + ch - '0';ch = getchar();}
  return x * f;
}
int point_to[maxn],ans[maxn];
int findx(int x) //路径压缩 
{
	if(x == point_to[x])
	{
		return x;
	}
	else 
	{
		return point_to[x] = findx(point_to[x]);
	}
}
int n,m,qwq;
int main()
{
    n = read() , m = read();
	for(int i=1;i<=n;i++) 
	{
		point_to[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		int s = read();
		if(s == 0) continue ;
		int to = read();
		qwq = to;
		for(int j = 2;j <= s;j ++)
		{
			int to = read();
			int a=findx(qwq),b=findx(to);
			point_to[a]=b;
		}
	}
	for(int i=1;i<=n;i++) 
	{
		ans[findx(i)]++;
	}
	for(int i=1;i<=n;i++) 
    {
    	printf("%ld ",ans[findx(i)]);
	}
	return 0;
}
```

---

