# Link Cut Centroids

## 题目描述

#### 题意

给定一棵节点数为 $n$ 的树 ， 删一条边然后加上一条边 ， 使得该树的重心唯一 。（删掉的边和加上的边可以是同一条）

## 样例 #1

### 输入

```
2
5
1 2
1 3
2 4
2 5
6
1 2
1 3
1 4
2 5
2 6```

### 输出

```
1 2
1 2
1 3
2 3```

# 题解

## 作者：QwQcOrZ (赞：29)

众所周知树的重心有个性质：一棵树最多有两个重心，且相邻

那么只需要考虑只有一个重心和两个重心的情况

首先如果这棵树只有一个重心，那么随便删一条边再加回来就好了

然后是两个重心的情况，考虑这样一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/mui5q3yu.png)

设节点 $1$ $2$ 是这棵树的两个重心，那么删去节点 $1$ 后最大的子树必定是节点 $2$ 这棵子树，删去节点 $2$ 后最大的子树也必定是节点 $1$ 这棵子树

为什么？考虑反证法，如果删去节点 $1$ 后最大的子树是 $3$ 这棵子树，那么将节点 $2$ 删去后，节点 $1$ 这棵子树的大小至少为子树 $3$ 的大小$+1$（节点 $1$）

也就是说删去节点 $2$ 后，最大子树的大小至少为子树 $3$ 的大小$+1$，这个值比节点 $1$ 最大的子树也就是 $3$ 这棵子树大，所以节点 $2$ 就不可能是重心了，不符合设定。所以原命题成立

由此我们可以推出节点 $1$ 的子树和节点 $2$ 的子树大小相等（因为他们两个都是重心，删去后最大子树相等）

接下来就好办了，我们只要两个子树不相等就可以了

从节点 $2$ 的子树里取一个叶子出来连到节点 $1$ 上即可

$Code\ Below$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5; 

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt;
}e[N*2];
int head[N],cnt=0;
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,siz[N],Max[N],Min,a[N],cntt,tmp2;
void dfs(int now,int fa)
{
	siz[now]=Max[now]=1;
	for (int i=head[now];i;i=e[i].nxt)
	if (e[i].to!=fa)
	{
		int to=e[i].to;
		dfs(to,now);
		siz[now]+=siz[to];
		Max[now]=max(Max[now],siz[to]);
	}
	Max[now]=max(Max[now],n-siz[now]);
	if (Max[now]<Min) Min=Max[now];
}
int find(int now,int fa)
{
	for (int i=head[now];i;i=e[i].nxt)
	if (e[i].to!=fa)
	{
		tmp2=now;
		return find(e[i].to,now);
	}
	return now;
}

signed main()
{
	int T=read();
	while (T--)
	{
		cnt=cntt=0;
		n=read();
		Min=n+1;
		for (int i=1;i<=n;i++) head[i]=0;
		for (int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		dfs(1,0);
		for (int i=1;i<=n;i++)
		if (Max[i]==Min)
		a[++cntt]=i;
		if (cntt==1) printf("%d %d\n%d %d\n",a[1],e[head[a[1]]].to,a[1],e[head[a[1]]].to);
		else
		{
			int tmp=find(a[2],a[1]);
			print(tmp2,' ');
			print(tmp);
			print(a[1],' ');
			print(tmp);
		}
	}

	return 0;
}
```

---

## 作者：Chinese_zjc_ (赞：10)

分类讨论.

首先当树只有一个重心的时候,我们删掉任意边再加上原边即可.

再看有两个重心的情况.

显然这棵树必定是类似这样的:

![Photo for CF1406C](https://cdn.luogu.com.cn/upload/image_hosting/t1x1nrei.png)

即删掉 $ A $ 后,以 $ B $ 为根的子树是剩下的最大连通块,反之亦然.

那就可以得到一个结论:

- 删掉边 $ (A,B) $ 后,两棵树的大小相等.

那我们只要使两棵树的大小不相等,且不使新的点成为重心即可.

那就考虑直接从 $ A $ 树中随机抽取一位~~幸运~~叶子节点,把这个节点与它父亲的边断开,连到 $ B $ 的直接儿子里去.

这样, $ A $ 树的大小变小了,而 $ B $ 树的大小变大了,且不会有新的节点成为重心.

那 $ A $ 就不再是重心了,而 $ B $ 则成为了唯一的重心.

$Code$:

```
//This Code was made by Chinese_zjc_.
#define int long long
#define PI 3.14159265358979323
#define INF 0x3fffffffffffffff
using namespace std;
int T,n,a,b,fa[100005],siz[100005],v[100005];
vector<int> son[100005];
void init(int now)// Initiation ♪
{
    siz[now]=1;
    for(int i=0;i<(int)son[now].size();++i)
    {
        if(fa[now]==son[now][i])
        {
            swap(son[now][i],son[now].back());
            --i;
            son[now].pop_back();
            continue;
        }
        fa[son[now][i]]=now;
        init(son[now][i]);
        siz[now]+=siz[son[now][i]];
    }
}
void dfs(int now)// 求删掉这个点后的最大连通块大小
{
    v[now]=siz[1]-siz[now];
    for(int i=0;i<(int)son[now].size();++i)
    {
        v[now]=max(v[now],siz[son[now][i]]);
        dfs(son[now][i]);
    }
}
int fin(int now)
{
    if(son[now].size())
    {
        return fin(son[now][0]);
    }
    else
    {
        return now;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;++i)
        {
            son[i].clear();
            fa[i]=0;
        }
        for(int i=1;i<n;++i)
        {
            cin>>a>>b;
            son[a].push_back(b);
            son[b].push_back(a);
        }
        init(1);
        dfs(1);
        int MIN=INF;
        for(int i=1;i<=n;++i)
        {
            MIN=min(MIN,v[i]);
        }
        vector<int> z;
        for(int i=1;i<=n;++i)
        {
            if(v[i]==MIN)
            {
                z.push_back(i);
            }
        }
        if(z.size()==1)//分类讨论
        {
            cout<<1<<' '<<son[1][0]<<endl;
            cout<<1<<' '<<son[1][0]<<endl;
        }
        else
        {
            if(fa[z[0]]!=z[1])
            {
                swap(z[0],z[1]);
            }
            int k=fin(z[0]);
            cout<<k<<' '<<fa[k]<<endl;
            cout<<k<<' '<<z[1]<<endl;
        }
    }
    return 0;
}
```



---

## 作者：kradcigam (赞：7)

有一个性质是这样的——重心连接的最大的子树大小不超过整棵树的一半。

当重心连接的最大的子树大小小于整棵树的一半时，这个树的重心是唯一的。

有了这个性质就好做了，我们可以随便找到一个重心，然后将它连接的最大的子树下的一个点连向它。

举个例子：

![](https://i.loli.net/2020/09/14/7F9RnlWrABJx8de.png)

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
vector<int>v[100010];
int n,s[100010],ans[100010],as;
void dfs(int x,int fa){
	s[x]=1;ans[x]=0;
	for(int i:v[x])
		if(i!=fa){
			dfs(i,x);
			ans[x]=max(ans[x],s[i]);
			s[x]+=s[i];
		}
	ans[x]=max(ans[x],n-s[x]);
	as=min(as,ans[x]);
}
void work(){
	memset(s,0,sizeof(s));//多测不清空，爆零两行泪。
	read(n);as=n;
	for(int i=1;i<=n;i++)v[i].clear();//多测不清空，爆零两行泪。
	for(int i=1;i<n;i++){
		int x,y;read(x);read(y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		if(ans[i]==as){
			dfs(i,0);
			for(int j:v[i])
				if(s[j]==as){
					if(as==1){//这里需要特判
						cout<<i<<" "<<j<<endl<<i<<" "<<j<<endl;
						return 0;
					}
					for(int k:v[j]){
						if(k!=i){
							cout<<k<<" "<<j<<endl<<k<<" "<<i<<endl;
							return 0;
						}
					}
				}
		}
}
```



---

## 作者：gyh20 (赞：6)

出题人题解：

如果只有一个重心，随便删一条再加一条即可。

否则只有两个重心，且相互连接，此时我们只要断掉一条其中一个重心连出去的其他的边然后连向另一个重心。此时一个点会变为不为重心，也就是说重心唯一。

可以自己画图或者根据样例推一推，还是比较好理解。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,size[100005],fa[100005],minn=1e9,cent1,cent2;
vector<int> g[100005];
void dfs(int x,int f){
	fa[x]=f,size[x]=1;
	int mx=0;
	for(int y:g[x]){
		if(y==f)continue;
		dfs(y,x);
		size[x]+=size[y];
		mx=max(mx,size[y]);
	}
	mx=max(mx,n-size[x]);
	if(mx<minn)minn=mx,cent1=x,cent2=0;
	else if(mx==minn)cent2=x;
}
int S;
void dfs2(int x,int f){
	if(g[x].size()==1){
		S=x;
		return ;
	}
	for(int y:g[x]){
		if(y==f)continue;
		dfs2(y,x);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
	cin>>n,cent1=cent2=0,minn=1e9;
	for(int i=1;i<=n;i++)g[i].clear(),fa[i]=0;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y),g[y].push_back(x);
	}
	dfs(1,0);
	if(!cent2){
		printf("1 %d\n1 %d\n",g[1][0],g[1][0]);
		continue;
	}
	if(fa[cent1]!=cent2)swap(cent1,cent2);
	dfs2(cent1,cent2);
	printf("%d %d\n%d %d\n",S,fa[S],S,cent2);}
	return 0;
}
```


---

## 作者：pigstd (赞：5)

题意：给你一棵树，让你删去一条边再添上一条边，使树只有一个重心

我的构造方法：先删去一个叶子节点，然后找到删去后的重心之一，然后将这个叶子节点连到重心上

为什么这么做是对的呢？

首先，删去一个节点的数只有$n-1$个节点

1.删去节点后的树只有一个重心，设这个重心的编号为$k$：

那么，$k$也肯定是新的重心之一，而且因为树最多只有两个相连的重心，所以若有第二个重心，则第二个重心一定和$k$相连

根据树的重心的性质：删除重心后所得的所有子树，节点数不超过原树的节点数的$\frac1 2$，那么说明当其他与重心相连的点作为根时，原重心所在的子树的节点数一定$ \ge \frac1 2 (n-1)$，然后又因为把删去的节点连到$k$上，那么就有$ \ge \frac 1 2 (n+1)$个节点，与$ \le \frac 1 2 n$矛盾。所以只有一个重心

2.删去节点后的树有两个重心，设重心的编号分别为$k1,k2$：

首先我们可以得到一个~~显然的~~结论：设$n1$为以$k1$为根，$k2$的子树中的节点个数，$n2$为以$k2$为根，$k1$的子树中的节点个数，那么$n1+n2 = n - 1$

又因为$n1 \le \frac 1 2 (n - 1)$，$n2 \le \frac 1 2 (n - 1)$，所以$n1 = n2 = \frac 1 2 (n - 1)$

当叶子节点连到$k1$上时，$k1$肯定还是重心，但是$n2=\frac 1 2 (n - 1)+1 = \frac 1 2 (n + 1)$，矛盾，所以此时$k2$不是重心。然后可以用前面的方法证明其他节点也不是重心，所以重心唯一

若连到了$k2$，那么同理可得重心唯一

所以这种方法是正确的

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=1e5+10;
int T,n,sum[M],fa[M],minn,ssum;
int x,y,mm[M],out[M];

vector<int>e[M];

void dfs(int u,int fat)
{
	sum[u]=1,fa[u]=fat;
	for (int i=0;i<e[u].size();i++)
	{
		int to=e[u][i];
		if (to!=fat)
			dfs(to,u),sum[u]+=sum[to];
	}
	for (int i=0;i<e[u].size();i++)
	{
		int to=e[u][i];
		if (to!=fat)
			mm[u]=max(mm[u],sum[to]);
	}
	mm[u]=max(mm[u],n-1-sum[u]);
	minn=min(minn,mm[u]);
}

int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;minn=n+10;
		for (int i=1;i<n;i++)
		{
			cin>>x>>y;
			e[x].push_back(y),e[y].push_back(x); 
			out[x]++,out[y]++;
		}
		for (int i=1;i<=n;i++)
			if (out[i]==1)
			{
				x=i;y=e[i][0];
				e[x].erase(find(e[x].begin(),e[x].end(),y));
				e[y].erase(find(e[y].begin(),e[y].end(),x));
				break;
			}
		dfs(x==1?2:1,0);//因为叶子节点也可能是1号点，所以特判
		for (int i=1;i<=n;i++)
			if (mm[i]==minn)
			{
				printf("%d %d\n%d %d\n",x,y,x,i);
				break;
			}
		for (int i=1;i<=n;i++)e[i].clear();
		for (int i=0;i<=n;i++)fa[i]=sum[i]=out[i]=mm[i]=0;//记得清空
	}
	return 0;
}

```

---

## 作者：chenxia25 (赞：3)

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1406C ) & [CF 题目页面传送门]( https://codeforces.com/contest/1406/problem/C )
>
> 给定一棵大小为 $n$ 的树。要求删掉一条边加上一条边使重心唯一。给出方案。本题多测。
>
> $n\in\left[3,10^5\right],\sum n\leq 10^5$。

假如说本来就唯一的话不用说。否则：

显然两个重心相邻。钦定其中一个为根，那么另一个就是第 $2$ 层。我也不知道怎么想出来的，就随便试吧，可以删掉第 $2$ 层重心的任意一条通向儿子的边（由 $n\geq 3$ 易证一定有儿子），然后把那个儿子连向根即可。

证明的话，显然删加过之后根依然是重心，因为子树大小最大值变小了嘛。而第 $2$ 层那个的相对应的显然变大了，那么它们的最大子树大小就不等了，就不可能同时为重心。然后如何证其他点不为重心呢？因为要想是重心就必须与根相邻，而这三个点发生关系跟其他儿子有个屁的关系，那最大子树大小肯定就不变啊，就无法翻身。得证。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=100000;
int n;
vector<int> nei[N+1];
int sz[N+1];
void dfs(int x=1,int fa=0){
	sz[x]=1;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
	}
}
void mian(){
	cin>>n;
	for(int i=1;i<=n;i++)nei[i].clear();
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs();
	vector<int> cen;
	for(int i=1;i<=n;i++){
		bool flg=true;
		int sum=1;
		for(int j=0;j<nei[i].size();j++){
			int x=nei[i][j];
			if(sz[x]>sz[i])continue;
			flg&=sz[x]<=n/2;
			sum+=sz[x];
		}
		flg&=n-sum<=n/2;
		if(flg)cen.pb(i);
	}
	assert(cen.size()<=2);
	if(cen.size()==1)printf("%d %d\n%d %d\n",1,nei[1][0],1,nei[1][0]);
	else{
		int son=nei[cen[0]][0]==cen[1]?nei[cen[0]][1]:nei[cen[0]][0];
		printf("%d %d\n%d %d\n",cen[0],son,cen[1],son);
	}
}
int main(){
	int testnum=1;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：VanHelsing (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1406C)  

题意挺清晰的，就是一棵由 $n$ 个节点构成的树，删去一条边在加上一条边使得这棵树只有一个重心，问删去的边和加上的边都是哪条边。  


首先，我们考虑一棵树一共会有几个重心？  

诶？重心的定义是什么？  
对于树上的每一个点，计算其所有子树中最大的子树节点数，这个值最小的点就是这棵树的重心。——OI Wiki  
这啥呀这是...  
换成人话，就是以这个节点为根的时候，一棵子树大小不超过 $n/2$ 。  
所以很容易可以推得一棵树最多会有两个重心，最少会有一个重心。  

如果只有一个重心的话，很好做，随便删一条边再加上就行了

如果有两个重心，那就从一个重心的子树里抽出一部分接到另一个重心的子树上。  

等等，重心怎么找？

对于一个节点 $u$ ，找到它所有子节点 $v$ 的子树大小的最大值，并且和 $n-siz_u$ 再取个最大值，就是以他为根的最大子树大小，然后如果这个最大子树大小 $\leq n/2$ 的话就是重心。

总结一下就是
$$Controid_u=max(siz_v , n-siz_u)$$

$O(n)$ 树形dp可求  

$Code\ Time\ :$  
```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=1e5+5;

int head[maxn],cnt=0,nxt[maxn<<1],to[maxn<<1];

void add(int u,int v)
{
	cnt++;
	
	to[cnt]=v;
	
	nxt[cnt]=head[u];
	
	head[u]=cnt;
}

int n,siz[maxn],Max[maxn],Min,a[maxn],cntt,tmp2;

void dfs(int x,int fa)
{
	siz[x]=Max[x]=1;
	
	for(int i=head[x];i;i=nxt[i])
	{
		int v=to[i];
		
		if(v==fa)
		{
			continue;
		}
		
		dfs(v,x);
		
		siz[x]+=siz[v];
		
		Max[x]=max(Max[x],siz[v]);
		
	}
		
	Max[x]=max(Max[x],n-siz[x]);
	
	if(Max[x]<Min)
	{
		Min=Max[x];
	}
}

int find(int x,int fa)
{
	for(int i=head[x];i;i=nxt[i])
	{
		int v=to[i];
		
		if(v==fa)
		{
			continue;
		}
		
		tmp2=x;
		
		return find(v,x);
		
	}
	
	return x;
}

int main()
{
	int T;
	
	cin>>T;
	
	while(T--)
	{
		cnt=cntt=0;
		
		scanf("%d",&n);
		
		Min=n+1;
		
		memset(head,0,sizeof head);
		
		for(int i=1;i<n;i++)
		{
			int x,y;
			
			scanf("%d%d",&x,&y);
			
			add(x,y);
			
			add(y,x);
		}
		
		dfs(1,0);
		
		for(int i=1;i<=n;i++)
		{
			if(Max[i]==Min)
			{
				a[++cntt]=i;
			}
		}
			
		if(cntt==1)
		{
			printf("%d %d\n%d %d\n",a[1],to[head[a[1]]],a[1],to[head[a[1]]]);
		}
		
		else
		{
			int tmp=find(a[2],a[1]);
			
			printf("%d %d\n%d %d\n",tmp2,tmp,a[1],tmp);
		}
	}

	return 0;
}
```

---

## 作者：傅天宇 (赞：1)

[luogu's link](https://www.luogu.com.cn/problem/CF1406C)

[CF's link](http://codeforces.com/problemset/problem/1406/C)

#### 题意：

给定一棵节点数为 $n$ 的树 ， 删一条边然后加上一条边 ， 使得该树的重心唯一 。（删掉的边和加上的边可以是同一条）

#### Solution：

1. 如果这棵树的重心是唯一的，那么可以删任一条边再加上这一条边。
2. 如果这棵树的重心不是唯一的，那么以其中一个重心为根，删去另一个重心所在子树中一条与叶子连接的边，加到另外一个子树中。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-30 16:02:08 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-12-01 16:13:50
 */
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=1e5+5;
namespace work{
    int n,tot,fir[N],sum[5],cnt,tmp;
    struct edge{
        int nxt,to;
    }e[N<<1];
    inline void add(int u,int v){
        tot++;
        e[tot].nxt=fir[u];
        e[tot].to=v;
        fir[u]=tot;
    }
    int siz[N],ma[N],mi;
    inline void clear(){
        memset(fir,0,sizeof fir);
        memset(sum,0,sizeof sum);
        tot=0;tmp=0;cnt=0;mi=n+1;
        memset(ma,0,sizeof ma);
        memset(siz,0,sizeof siz);
    }
    inline void dfs(int u,int dad){
        siz[u]=ma[u]=1;
        for(int i=fir[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(v==dad) continue;
            dfs(v,u);
            siz[u]+=siz[v];
            ma[u]=max(ma[u],siz[v]);
        }
        ma[u]=max(ma[u],n-siz[u]);
        mi=min(mi,ma[u]);
    }
    inline int dfs1(int u,int dad){
        for(int i=fir[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(v==dad) continue;
            tmp=u;
            return dfs1(v,u);
        }
        return u;
    }
    inline void main(){
        n=read();
        clear();
        int noteu,notev;
        FOR(i,1,n-1){
            int u=read(),v=read();
            add(u,v);
            add(v,u);
            if(i==1) noteu=u,notev=v;
        }
        dfs(1,0);
        FOR(i,1,n) if(ma[i]==mi) sum[++cnt]=i;
        if(cnt==1){
            write(noteu),putchar(' ');
            write(notev),puts("");
            write(noteu),putchar(' ');
            write(notev),puts("");
        }
        else{
            int x=dfs1(sum[2],sum[1]);
            write(tmp);putchar(' ');
            write(x);puts("");
            write(sum[1]);putchar(' ');
            write(x);puts("");
        }
    }
}
int main(){
    int t=read();
    while(t--) work::main();
    return 0;
}
```





---

## 作者：XyzL (赞：1)

## 题意：

给一棵树删一条边再加一条边，是该树中心唯一。

## 分析：

若只有一个重心，随便删一条再加回去。若有两个重心，根据一个推论，树至多有两个重心且这两个重心呈父子关系。所以可将一重心连到另一重心的孩子节点上。

这样题就做完了。

放上最短代码...

## 代码：

```cpp
#include <bits/stdc++.h>
std::vector<int>v[100001];
int t,n,p,s[100001];
int d(int x,int f){
	for(int i=0;i<v[x].size();i++)if(v[x][i]!=f)s[x]+=d(v[x][i],x);
	if(p&&s[x]*2==n)p=0,printf("%d %d\n%d %d\n",x,v[x][v[x][0]==f],v[x][v[x][0]==f],f);
	return s[x];
} main(){
	scanf("%d",&t); while(t--){
		p=1,scanf("%d",&n);
		for (int i=1;i<=n;i++)v[i].clear(),s[i]=1;
		for (int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);d(1,0);
		if(p)printf("%d %d\n%d %d\n",1,v[1][0],1,v[1][0]);
	}
}
```

---

## 作者：code_hunter (赞：1)

## 题目大意
- 给定一棵点数为 n （n $\ge$ 3）的无根树
- 将其删掉一条边并加上一条边，使树的重心唯一

## 前置知识
1. 一个点是树的重心当且仅当其所有子树的大小不大于$\frac{n}{2}$ 。
1. 一个树至多有两个重心，且相邻。
1. 树形 dp 求树的重心。

## 解法
1. 第一种情况，树的重心只有一个。将任意一条**存在的**~~我因此而WA~~边删除，并原处添加即可。
1. 第二种情况，树有两个重心，显然它们之间相邻且其边将树分为两个点数相同的部分，否则必有一个“重心”有一个大于 $\frac{n}{2}$ 的子树。不难想出策略，即在任意一个重心 $c_{1}$ 上找任意一条边（不与另一重心 $c_{2}$ 相连），将其删除，并将该边另一端点 v 与另一重心相连即可。
	
   证明：
   1. 以 $c_{2}$ 为根进行讨论。显然 $c_{2}$ 依然是重心，因为他有三类子树，一是以 $c_{1}$ 为根的子树，其大小显然变小，二是以 v 为根的子树，显然$\operatorname{size}$(以 v 为根的子树) $\le$ $\operatorname{size}$(原来以 $c_{1}$ 为根的子树) $\le$ $\frac{n}{2}$ ，三是未改变的子树，显然不会造成影响。
   1. 以 $c_{1}$ 为根进行讨论。显然 $\operatorname{size}$(以 $c_{2}$ 为根的子树) $=$ $\operatorname{size}$(原来以 $c_{2}$ 为根的子树) + $\operatorname{size}$(原来以 v 为根的子树) $=$  $\operatorname{size}$(原来以 v 为根的子树) + $\frac{n}{2}$ $>$ $\frac{n}{2}$。故非树根。
   1. 以 v 为根进行讨论。显然 $\operatorname{size}$(以 $c_{2}$ 为根的子树) $=$ $\operatorname{size}$(原来以 $c_{2}$ 为根的子树) + $\operatorname{size}$（以 $c_{1}$ 为根的子树) $=$  $\operatorname{size}$(原来以 $c_{1}$ 为根的子树) + $\frac{n}{2}$ $>$ $\frac{n}{2}$。故非树根。
   1. 对于其它任一节点，其子树大小均未改变，故不会变成重心。
   
## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#define lowbit(x) ((x) & (-(x)))
typedef long long ll;
ll MIN(ll x, ll y) { return x < y ? x : y; }
ll MAX(ll x, ll y) { return x > y ? x : y; }
const ll INF = 0x7fffffffffffffff;
const int MAXN = 1e5 + 123;
using namespace std;

int T , N;
int h[MAXN] , now;
struct Edge{
    int u , v , next;
}e[MAXN << 1];
void addEdge(int u , int v) {
    now ++;
    e[now].u = u;
    e[now].v = v;
    e[now].next = h[u];
    h[u] = now;
}

int sz[MAXN] , mx[MAXN];
void dfs(int x , int f) {
    sz[x] = 1;
    mx[x] = 0;
    for (int i = h[x] ; i ; i = e[i].next) {
        const int &v = e[i].v;
        if (v == f)
            continue;
        dfs(v , x);
        sz[x] += sz[v];
        mx[x] = max(mx[x] , sz[v]);
    }
    mx[x] = max(mx[x] , N - sz[x]);
}
int mi , id , ed;
void work() {
    scanf ("%d" , &N);
    for (int i = 1 ; i <= N ; i ++)
        h[i] = 0;
    now = 0;
    for (int i = 1 ; i < N ; i ++) {
        register int x , y;
        scanf ("%d %d" , &x , &y);
        addEdge(x , y);
        addEdge(y , x);//一句遂成千古恨
    }
    dfs(1 , 0);
    mi = 0x7fffffff;
    for (int i = 1 ; i <= N ; i ++) {
        if (mi > mx[i]) {
            mi = mx[i];
            id = i;
        }
    }
    for (int i = h[id] ; i ; i = e[i].next) {
        const &v = e[i].v;
        if (mx[v] == mi) {
            for (int j = h[v] ; j ; j = e[j].next) {
                if (e[j].v != id) {
                    printf ("%d %d\n%d %d\n" , v , e[j].v , id , e[j].v);
                    return;
                }
            }
        }
    }
    printf ("%d %d\n%d %d\n" , e[1].u , e[1].v , e[1].u , e[1].v);//千古恨
}

int main() {
    scanf ("%d" , &T);
    while (T --) {
        work();
    }
    return 0;
}
```


---

## 作者：GIFBMP (赞：1)

这题要用到重心的两个重要结论：

$1.$ 重心至多有两个。  
$2.$ 若一棵树有两个重心，那么它们必然相邻。

那么我们先找到两个重心，然后割掉它们之间连接的边，然后将其中一个重心与另一个重心的一个儿子连边。可以证明，这样处理后的树必然只有一个重心。

Code:

```cpp
#include <cstdio>
#include <vector>
using namespace std ;
const int MAXN = 1e5 + 10 ;
int T , n , size[MAXN] , rt[MAXN] , cnt , minn , fa[MAXN] ;
vector <int> G[MAXN] ;
vector <pair <int , int> > S ; 
void dfs (int x , int f) {
	int maxx = -1 ;
	size[x] = 1 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == f) continue ;
		dfs (v , x) ;
		size[x] += size[v] ;
		if (size[v] > maxx) maxx = size[v] ;
	}
	if (n - size[x] > maxx) maxx = n - size[x] ;
	if (maxx < minn) {
		minn = maxx ;
		cnt = 0 ;
		rt[++cnt] = x ;
	}
	else if (maxx == minn) rt[++cnt] = x ; 
}
void dfs2 (int x) {
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == fa[x]) continue ;
		fa[v] = x ;
		dfs2 (v) ;
	}
}
int main () {
	scanf ("%d" , &T) ;
	while (T--) {
		scanf ("%d" , &n) ; cnt = 0 ; minn = 0x3f3f3f3f ;
		for (int i = 1 ; i <= n ; i++) G[i].clear () , fa[i] = 0 ;
		S.clear () ; 
		for (int i = 1 ; i < n ; i++) {
			int u , v ;
			scanf ("%d %d" , &u , &v) ;
			G[u].push_back (v) ;
			G[v].push_back (u) ;  
		} 
		dfs (1 , 0) ;
		if (cnt == 1) {
			printf ("%d %d\n%d %d\n" , rt[1] , G[rt[1]][1] , rt[1] , G[rt[1]][1]) ;
			continue ;
		} 
		dfs2 (rt[1]) ;
		for (int i = 0 ; i < G[rt[2]].size () ; i++) {
			int v = G[rt[2]][i] ;
			if (v == fa[rt[2]]) continue ;
			S.push_back (make_pair (rt[2] , v)) ;
			S.push_back (make_pair (v , rt[1])) ; 
			break ;
		}
		for (int i = 0 ; i < 2 ; i++)
			printf ("%d %d\n" , S[i].first , S[i].second) ;
	}
	return 0 ;
}
```

---

## 作者：wlj_55 (赞：0)

## 题意简述
给定一棵 $n$ 个点的树，要求切断一条边并连接一条边，使得修改后的图是一棵树，且只有一个重心。

$n \le 10^5$

## Sol
我们考虑具有两个重心的树的性质，观察到如果树有两个重心，那么它们必定是相邻的，我们考虑利用这个性质求解。

![](https://cdn.luogu.com.cn/upload/image_hosting/mpa9b00c.png)

我们观察到有两个重心的树必定长的像上图那样（图中红点为重心），也就是对于一个重心而言，它除了连向另一个重心外，必然有另外的节点与其相连，证明也很简单，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/d6gb6zsx.png)

无论如何，最上面的那个点永远不会是重心。

![](https://cdn.luogu.com.cn/upload/image_hosting/5sc2vzzx.png)

考虑如上图所示的构造方式，删去黄色边，连上绿色边，那么现在我们要证明该方法构造出的树只有一个重心。

对于结点 $2$ 来说，其原来的最大子树要么是它自己的子树，要么是除了以它自己为根的子树剩下的部分，而新的构造方式中， 结点 $2$ 新增的子树大小是从剩下的部分分离而来，故大小肯定小于原来最大子树的大小，而剩下的部分大小减小，自己的子树大小不变，故最大子树大小是小于等于原来的情况。

对于结点 $1$ 来说，同样分两种情况讨论，得到 $1$ 在新的树中的最大子树大小是大于等于原来的情况。

那么我们可得 $2$ 的最大子树大小是小于等于 $1$ 的最大子树大小的，但我们观察等于时的情况，发现这种情况是显然矛盾的，故不可能取等，那么新构造的树就只能有一个重心，就是结点 $2$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
vector<int> Edg[100005];
int rt, sum, sz[100005], son[100005], rt1, rt2;
void getrt(int u, int fa) {             //找重心
	sz[u] = 1, son[u] = 0;
	for(int i = 0; i < Edg[u].size(); i++) {
		int v = Edg[u][i];
		if(v == fa)  continue;
		getrt(v, u);
		sz[u] += sz[v];
		son[u] = max(son[u], sz[v]);n
	}
	son[u] = max(son[u], sum - sz[u]);
	if(!rt1)  rt1 = u;
	if(rt1 && son[u] < son[rt1])  rt1 = u, rt2 = 0;
	else if(rt1 && son[u] == son[rt1])  rt2 = u;
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		rt1 = rt2 = 0;
		int n; scanf("%d", &n);
		for(int i = 1; i <= n; i++)  Edg[i].clear();
		for(int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			Edg[x].push_back(y); Edg[y].push_back(x);
		}
		sum = n;
		getrt(1, 0);
		if(rt2 == 0) {
			printf("%d %d\n%d %d\n", 1, Edg[1][0], 1, Edg[1][0]);
			continue;
		}
		for(int i = 0; i < sz[rt1]; i++) {
			int v = Edg[rt1][i];
			if(v != rt2) {
				printf("%d %d\n%d %d\n", rt1, v, rt2, v);
				break;
			}
		}
	}
}

---

## 作者：幻影星坚强 (赞：0)

题意是给定一棵树，删掉一条边并加入一条边，使得其仍为一棵树且重心只有一个。

如果重心本来就只有一个，那么删去并加入同一条边即可。

如果重心有两个，那么根据重心的性质，两重心相邻且删掉两重心的边后两棵子树大小为$n/2$。我们将一个重心的儿子接在另一个重心。

正确性（以下默认所讨论节点为根）：

- 所有非重心节点肯定不会成中心（始终有一个子树大小大于$n/2$）。

- 一个重心因为把儿子接在了它的另一个子树大小为$n/2$中，所以最大值大于$n/2$，不是重心。

- 另一个重心它最大的子树减小，且嫁接过来儿子的子树大小（以该重心为根的情况下）不会超过$n/2$。所以是重心

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct bian
{
    int from, to;
}eg[200010];
int fa[100010], t, n, siz[100010], f[100010];
int front[100010], num;
void lian(int x, int y)
{
    eg[++ num].to = y;
    eg[num].from = front[x];
    front[x] = num;
}
void dfs(int o, int from)
{
    siz[o] = 1;
    fa[o] = from;
    for (int i = front[o]; i; i = eg[i].from)
    {
        int to = eg[i].to;
        if(to == from)continue;
        dfs(to, o);
        siz[o] += siz[to];
        f[o] = max(f[o], siz[to]);
    }
    f[o] = max(f[o], n - siz[o]);
}
int main()
{
    scanf("%d", &t);
    while(t --)
    {
        memset(fa, 0, sizeof(fa));
        memset(eg, 0, sizeof(eg));
        memset(front, 0, sizeof(front));
        memset(f, 0, sizeof(f));
        num = 0;
        scanf("%d", &n);
        int x, y;
        for (int i = 1; i < n; ++ i)
        {
            scanf("%d%d", &x, &y);
            lian(x, y);
            lian(y, x);
        }
        dfs(1, 0);//求重心
        int mins = n + 1, zong = 0;
        for (int i = 1; i <= n; ++ i)
        {
            if(mins == f[i])
            {
                ++ zong;
            }
            if(mins > f[i])
            {
                zong = 1;
                mins = f[i];
            }
        }
        if(zong == 1)//重心数量为1
        printf("%d %d\n%d %d\n", x, y, x, y);
        else//重心数量为2
        {
            int a = 0, b = 0;
            for (int i = 1; i <= n; ++ i)
            {
                if(f[i] == mins)
                {
                    if(a)
                    b = i;
                    else
                    a = i;
                }
            }
            int i, ne;
            for (i = front[a]; i; i = eg[i].from)
            {
                int to = eg[i].to;
                if(to != b)
                {
                    ne = to;
                    break;
                }
            }
            printf("%d %d\n%d %d\n", a, ne, b, ne);
        }
    }
}

```


---

## 作者：dead_X (赞：0)

## 前言
原来是结论题=_=

想了半天没思路QAQ
## 题意
将一棵树删一条边加一条边，使得新生成的树重心唯一。
## 思路
一棵树最多只有 $2$ 个重心。

如果只有一个重心，你什么也不需要干，随便删一条再加回去就行了。

如果有两个重心，你可以直接把一个重心连到另外一个重心的孩子节点上，万事大吉。
## 代码
```
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
vector<int> e[1000003];
int a[1000003],b[1000003],f[1000003],sz[1000003];
int n,zx;
bool flag;
inline void dfs(int u,int fa) {
	sz[u]=1;
	f[u]=fa;
	int s=e[u].size();
	for(int i=0; i<s; i++) if(e[u][i]!=fa) dfs(e[u][i],u),sz[u]+=sz[e[u][i]];
	if(sz[u]==n-sz[u]) flag=1,zx=u;
	return ;
}
int main()
{
	int T=read();
	while(T--)
	{
		n=read(),zx=0;
		for(int i=1; i<=n; i++) e[i].clear();
		flag=0;
		for(int i=1; i<n; i++) 
		{
			int u=read(),v=read();
			e[v].pb(u),e[u].pb(v);
			a[i]=u,b[i]=v;
			if(a[i]<b[i]) swap(a[i],b[i]);
		}
		dfs(1,0);
		if(flag) for(int i=1; i<n; i++) 
		{
 			if(zx==a[i] && f[a[i]]!=b[i]) { printf("%d %d\n%d %d\n",a[i],b[i],b[i],f[a[i]]); break; }
			if(zx==b[i] && f[b[i]]!=a[i]) { printf("%d %d\n%d %d\n",a[i],b[i],a[i],f[b[i]]); break; }
		}
		else for(int i=1; i<=2; i++) printf("%d %d\n",a[1],b[1]);
	}
	return 0;
}

```

---

