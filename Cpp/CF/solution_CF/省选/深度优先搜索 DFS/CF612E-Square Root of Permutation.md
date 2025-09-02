# Square Root of Permutation

## 题目描述

A permutation of length $ n $ is an array containing each integer from $ 1 $ to $ n $ exactly once. For example, $ q=[4,5,1,2,3] $ is a permutation. For the permutation $ q $ the square of permutation is the permutation $ p $ that $ p[i]=q[q[i]] $ for each $ i=1...\ n $ . For example, the square of $ q=[4,5,1,2,3] $ is $ p=q^{2}=[2,3,4,5,1] $ .

This problem is about the inverse operation: given the permutation $ p $ you task is to find such permutation $ q $ that $ q^{2}=p $ . If there are several such $ q $ find any of them.

## 样例 #1

### 输入

```
4
2 1 4 3
```

### 输出

```
3 4 2 1
```

## 样例 #2

### 输入

```
4
2 1 3 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
2 3 4 5 1
```

### 输出

```
4 5 1 2 3
```

# 题解

## 作者：hxhhxh (赞：8)

## 大意

对于一个排列 $ p $ ，若 $ q = p ^ 2 $ ，则 $ q_i = p_{p_i} $ ，已知 $ q $ ，求任意一个 $ p $ ，使得 $ p ^ 2 = q $ 。

## 思路

首先，将一个排列里的 $ i $ 向 $ p_i $ 连边，可以发现所得的图是由若干个环组成。

对于一个环，我们把它平方看看：

设这个环为 $ s_1 \rightarrow s_2 \rightarrow \dots \rightarrow s_k \rightarrow s_1 $ 

当 $ 2 \nmid k $ 时，环变为 $ s_1 \rightarrow s_3 \rightarrow \dots \rightarrow s_k \rightarrow s_2 \rightarrow s_4 \rightarrow \dots \rightarrow s_{k-1} \rightarrow s_1 $ ，还是一个环。

当 $ 2 \mid k $ 时，环变成 $ s_1 \rightarrow s_3 \rightarrow \dots \rightarrow s_{k-1} \rightarrow s_1 $ 和 $ s_2 \rightarrow s_4 \rightarrow \dots \rightarrow s_k \rightarrow s_2 $ 两个环。

可以看出，一次平方产生了偶环一定是偶数个大小相同的，而奇环则无所谓。

那么，对于 $ q $ ，它的每一个奇环应稍作处理，而每一个大小的偶环两两配对，如果没有偶数个就输出 $ -1 $ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,p[1000006],ans[1000006],vis[1000006];
vector<int>a[1000006],b[1000006];
void dd(int x){
	for(int i=0,j=a[x].size()/2+1;i<a[x].size()/2;i++,j++){
		ans[a[x][i]]=a[x][j];
		ans[a[x][j]]=a[x][i+1];
	}
	ans[a[x][a[x].size()/2]]=a[x][0];
}
void vn(int x,int y){
	for(int i=0;i<a[x].size();i++){
		ans[a[x][i]]=a[y][i];
		ans[a[y][i]]=a[x][(i+1)%a[x].size()];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			a[++cnt].push_back(i);
			vis[i]=true;
			int x=p[i];
			while(!vis[x]){
				vis[x]=1;
				a[cnt].push_back(x);
				x=p[x];
			}
			b[a[cnt].size()].push_back(cnt);
		}
	}
		
	for(int i=2;i<=n;i+=2){
		if(b[i].size()&1){
			putchar('-');
			putchar('1'); 
			return 0;
		}
	}
	for(int i=1;i<=n;i+=2) for(int j=0;j<b[i].size();j++) dd(b[i][j]);
	for(int i=2;i<=n;i+=2) for(int j=0;j<b[i].size();j+=2) vn(b[i][j],b[i][j+1]);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
}
```

---

## 作者：chenxia25 (赞：6)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF612E) & [CodeForces题目页面传送门](https://codeforces.com/contest/612/problem/E)

>定义一个$1\sim n$的排列$a$的平方$a^2=b$，当且仅当$\forall i\in[1,n],b_i=a_{a_i}$，即$a^2$为将$a$在$[1,2,\cdots,n]$上映射$2$次所得的排列。现在给定一个$1\sim n$的排列$a$，求$b$使得$b^2=a$，即求$a$的平方根。若有多解，输出任意一个。若无解，输出$-1$。

>$n\le10^6$。

看到关于映射的题目，首先想到转化为图论。$\forall i\in[1,n]$，从$i$到$a_i$建一条有向边，得到一张有向图$G=(V=[1,n]\cap\mathbb Z,E=\{(x,y)\mid a_x=y\})$。很显然，对于一个排列建出的图一定是由若干个环组成的，因为每个节点的入度、出度均为$1$。那么将$a$平方之后，每个节点会指向它原来指向的节点原来指向的节点。考虑平方之后每个环会变成什么样子：很显然，若此环大小为奇，则仍然是一个奇环；若此环大小为偶，则会分裂成$2$个大小为原来一半的环。

现在我们得到$a$的图，需要根据上述变形规律还原出它的平方根。考虑每个环，分$2$种情况：

1. 大小为奇。它在$a$的平方根的图中可能本来就是一个奇环，也可能是由一个偶环分裂出来的一半；
2. 大小为偶。它在$a$的平方根的图中不可能是一个奇环，则只能是一个大小是$4$的倍数的偶环分裂出来的一半。

显然，需要合并的情况都是$2$个大小相同的环合并，所以不同大小的环是互相独立的，我们可以对于每个大小分别考虑还原。分$2$种情况：

1. 大小为奇。那么大小为它的每个环要么是自己还原，要么是另找一个环合并。显然自己还原是无条件的，所以我们贪心地选择将每个环自己还原（将每个节点指向的节点设为平方根图中该节点指向的节点指向的节点）；
2. 大小为偶。此时大小为它的每个环只能是另找一个环合并。于是如果大小为它的环的个数为奇的话，则不能两两配对，直接输出$-1$走人；否则任意组合两两合并（合并时在$2$个环中都任找一个起点，然后$(1,1)\to(2,1)\to(1,2)\to(2,2)\to(1,3)\to\cdots$（其中$(x,y)$表示第$x$个环中从起点开始数的第$y$个节点）作为平方根中的环）。

每个节点都被访问常数次，所以时间复杂度为$\mathrm O(n)$。

下面贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
void read(int &x){//快读 
	x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
void prt(int x){//快写 
	if(x>9)prt(x/10);
	putchar(x%10^48);
}
const int N=1000000;
int n; 
int a[N+1];//平方之后的排列 
bool vis[N+1];//DFS时的标记数组 
vector<int> v;//此SCC（环）中的点 
void dfs(int x){//DFS 
	if(vis[x])return;
	vis[x]=true;
	v.pb(x);
	dfs(a[x]);
}
vector<vector<int> > vv;//所有环 
vector<int> havsz[N+1];//大小为[i]的所有环的编号 
int ans[N+1];//a的平方根 
int main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)if(!vis[i]){//找出每个环 
		v.clear();
		dfs(i);
		if(v.size()&1){//如果是奇环直接自己还原 
			vector<int> v0(v.size());//还原之后的环 
			for(int j=0,now=0;j<v.size();j++,(now+=2)%=v.size())v0[now]=v[j];
			for(int j=0;j<v.size();j++)ans[v0[j]]=v0[(j+1)%v.size()];//将还原之后的环用排列的形式存到a的平方根里 
		}
		else vv.pb(v);//否则存下来等到后面找其他环合并 
	}
	for(int i=0;i<vv.size();i++)havsz[vv[i].size()].pb(i); 
	for(int i=2;i<=n;i+=2)//枚举偶数大小 
		if(havsz[i].size()&1)return puts("-1"),0;//不能两两配对 
		else for(int j=0;j<havsz[i].size();j+=2){//枚举环对 
			vector<int> &v0=vv[havsz[i][j]]/*第1个环*/,&v1=vv[havsz[i][j+1]]/*第2个环*/,v2(2*v0.size())/*还原之后的环*/;
			for(int k=0,now=0;k<v0.size();k++,now+=2)v2[now]=v0[k],v2[now+1]=v1[k];
			for(int k=0;k<v2.size();k++)ans[v2[k]]=v2[(k+1)%v2.size()];//将还原之后的环用排列的形式存到a的平方根里
		}
	for(int i=1;i<=n;i++)prt(ans[i]),putchar(' ');//输出答案 
	return 0;
}
```

---

## 作者：SovietPower✨ (赞：3)

### $Description$
给定一个$n$的排列$p_i$，求一个排列$q_i$，使得对于任意$1\leq i\leq n$，$q_{q_i}=p_i$。无解输出$-1$。

$1\leq n\leq10^6$。

### $Solution$
对排列$q_i$我们建一张图，边为$i\to q_i$。显然这张图是由几个环构成。

发现对于$q_{q_i}$的图，原来$q_i$中的奇环它们还是类似的一个奇环，原来的偶环会分裂成两个大小相等的偶环。

所以对$p_i$建图，找出里面的环，是奇环就把相邻点间隔为$2$地插入到环里，是偶环就找到和它一样大的一个合并，找不到就无解。这样就可以得到$q_i$的图了。

复杂度$O(n)$。

-----
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int nxt[N],q[N],tmp[N],tmp2[N],id[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) nxt[i]=read();
	for(int s=1; s<=n; ++s)
		if(!vis[s])
		{
			int cnt=0,x=s;
			do
			{
				tmp[++cnt]=x, vis[x]=1, x=nxt[x];
			}while(x!=s);
			if(cnt&1)
			{
				for(int i=1,now=0; i<=cnt; ++i,(now+=2)%=cnt) tmp2[now]=tmp[i];
				for(int i=0; i<cnt; ++i) q[tmp2[i]]=tmp2[i+1];
				q[tmp2[cnt-1]]=tmp2[0];
			}
			else
			{
				if(!id[cnt]) id[cnt]=s;
				else
				{
					int y=id[cnt],x=y,t=0;
					do
					{
						tmp2[++t]=x, x=nxt[x];
					}while(x!=y);
					for(int t1=1,t2=1,las=tmp[1],i=t<<1; i; --i)
						las=q[las]=i&1?tmp[++t1]:tmp2[t2++];
					q[tmp2[t]]=tmp[1], id[t]=0;
				}
			}
		}
	for(int i=2; i<=n; i+=2) if(id[i]) return puts("-1"),0;
	for(int i=1; i<=n; ++i) printf("%d ",q[i]);

	return 0;
}
```

---

## 作者：hfctf0210 (赞：2)

这题是个比较好想的构造题，题解大致如下：

首先很容易发现，如果把排列{pi}表示为i到p[i]的一条有向边，那么很容易发现图就是由若干环组成的。

然后可以把环分为奇环和偶环两类，奇环的情况比较简单，假设从某一位置开始的值为{a1,a2,...,a2k-1}，那么不难想到把环拆成两部分，一部分为{a1,a2,...,ak}，另一部分为{ak+1,...,a2k-1}，前面k个数，后面k-1个数，然后让前面的k个连接在一起，后面k-1个插入a1->a2,a2->a3,...,ak-1->ak这k-1个空当中，很容易发现这是对的。

偶环的情况可以这么办，把每条边长度扩展成2，发现要在中间插入，所以只能把2个大小相同的偶环合并为一个。所以当同一大小的偶环数目为奇数时，就无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
int n,cnt,p[N],ans[N],vis[N];
vector<int>a[N],b[N];
void solve_odd(int id)
{
	int sz=a[id].size(),mid=sz/2;
	for(int i=0,j=mid+1;i<mid;i++,j++)
	ans[a[id][i]]=a[id][j],ans[a[id][j]]=a[id][i+1];
	ans[a[id][mid]]=a[id][0];
}
void solve_even(int x,int y)
{
	int sz=a[x].size();
	for(int i=0;i<sz;i++)
	{
		ans[a[x][i]]=a[y][i];
		ans[a[y][i]]=i==sz-1?a[x][0]:a[x][i+1];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)
	if(!vis[i])
	{
		cnt++;
		a[cnt].push_back(i);
		vis[i]=1;
		int u=p[i];
		while(!vis[u])vis[u]=1,a[cnt].push_back(u),u=p[u];
		b[a[cnt].size()].push_back(cnt);
	}
	for(int i=2;i<=n;i+=2)if(b[i].size()%2){puts("-1");return 0;}
	for(int i=1;i<=n;i+=2)
	for(int j=0;j<b[i].size();j++)
	solve_odd(b[i][j]);
	for(int i=2;i<=n;i+=2)
	for(int j=0;j<b[i].size();j+=2)
	solve_even(b[i][j],b[i][j+1]);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
}
```


---

## 作者：AC_love (赞：1)

一个很经典的解决图论问题的思想：对于一个排列 $p$，将 $i$ 向 $p_i$ 连边，最后一定得到的是一些环。

如果我们把一个环平方一下，其实用图论语言理解就是：在环里从每次走一步变成每次走两步，得到新的环。

不难发现，如果原环是奇环，新的环还是一个大小相等的奇环。如果原环是偶环，新的环是两个大小相等都为原环大小 $\dfrac{1}{2}$ 的环。

那么我们对于最后的一些环，进行一下匹配。如果有两个大小相等的偶环，我们就可以把它们拼成一个更大的偶环。如果最后有的偶环拼不起来，则无解。

---

## 作者：hgzxwzf (赞：1)

## 解题思路：
如果我们把 $i$ 和 $q_i$ 之间连边，就会构成一个只由环组成的图，因为每个点出度和入度都为 $1$。

寻找 $q^2$ 与 $q$ 图的关系，发现，

$q$ 中距离为 $2$ 的点在 $q^2$ 中距离变成了 $1$。

对于 $q$ 中的偶环，在 $q^2$ 中会分成两个都相同的偶环；

对于 $q$ 中的奇环，在 $q^2$ 中还是奇环。

那么通过 $p$ 图如何求出 $q$ 的图呢？

对于 $p$ 图中的奇环，在 $q$ 图中要么是奇环，要么是偶环分裂而来的，前者没有限制条件，所以我们选择前者；

对于 $p$ 图中的偶环，肯定是偶环分裂而来的，所以我们将有相同大小的偶环合并，如果最后还有没有被合并的偶环，那么无解。

如何构造答案？

对于奇环，我们发现在 $p$ 图和 $q$ 图中相同两点距离前者是后者的两倍，所以我们可以通过 $p$ 图中两点的距离得到 $q$ 中和 $i$ 距离为 $1$ 的点是哪一个，从而得到。

对于两个大小相同的偶环 $a$ 和 $b$，我们连 $a_i$ 向 $b_i$ 的边，$b_i$ 向 $a_{i+1}$ 的边，发现 $a_i$ 和 $a_{i+1}$ 的距离变成了 $2$，$b$ 也是如此，即得到了 $q$ 图。

## 代码：
```cpp
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<stack>
#include<cmath>
#include<vector>
#include<cstring>
#include<queue>
#include<string>
#include<iostream>
#include<map>
#include<bitset>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long

using namespace std;
const int N=1e6+10;

int q[N],p[N],pre[N],b[N<<1];
bool vis[N];
vector<int>ring[N];

int main()
{
	int n;
	scanf("%d",&n);
	rep(i,1,n)
		scanf("%d",&p[i]);
	rep(i,1,n)
		if(!vis[i])
		{
			int u=i,siz=0;
			while(!vis[u]) 
			{
				b[++siz]=u;
				vis[u]=1;
				u=p[u];
			}
			if(siz&1)
			{
				rep(i,1,siz) b[i+siz]=b[i];
				rep(i,1,siz) q[b[i]]=b[(siz+1)/2+i];
			}
			else
			{
				if(pre[siz])
				{
					int u[2];
					u[0]=i,u[1]=pre[siz];
					q[u[0]]=u[1];
					u[0]=p[u[0]];
					int cur=1;
					while(u[cur]!=i)
					{
						q[u[cur]]=u[cur^1];
						u[cur]=p[u[cur]];
						cur^=1;
					}
					pre[siz]=0;
				}
				else pre[siz]=i;
			}
		}
	rep(i,1,n) if(pre[i]) return puts("-1"),0;
	rep(i,1,n) printf("%d ",q[i]);
	return 0;
}
```


---

## 作者：cike_bilibili (赞：0)

一个排列的映射关系是很容易产生环的，所以将每个环单独考虑。

如果环大小奇数，可以自力更生，在内部构造。

否则，则让两个相同大小的偶环，一一配对即可。

时间 $O(n)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>=48&&ch<=57){
       ans=(ans<<1)+(ans<<3)+ch-48;
       ch=getchar();
    }
    return w*ans;
}
int n;
int a[1000005];
int vis[1000005];
vector<int>vec[1000005];
void find(int x,int id){
    vec[id].push_back(x);
    vis[x]=1;
    if(vis[a[x]])return;
    find(a[x],id);
}
int cnt;
int ans[1000005];
int b[1000005],top;
signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++){
        if(!vis[i])find(i,++cnt);
    }
    for(int i=1;i<=cnt;i++){
        if(vec[i].size()&1){
            for(int j=0;j<vec[i].size();j++){
                ans[vec[i][j]]=vec[i][(j+(vec[i].size()+1)/2)%vec[i].size()];
            }
        }
        else b[++top]=i;
    }
    if(top&1){
        cout<<-1<<"\n";
        return 0;
    }
    sort(b+1,b+1+top,[&](int x,int y){return vec[x].size()<vec[y].size();});
    for(int i=1;i<=top;i+=2){
        if(vec[b[i]].size()!=vec[b[i+1]].size()){
            cout<<-1<<'\n';
            return 0;
        }
        for(int j=0;j<vec[b[i]].size();j++){
            ans[vec[b[i]][j]]=vec[b[i+1]][j];
            ans[vec[b[i+1]][j]]=vec[b[i]][(j+1)%vec[b[i]].size()];
        }
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
    return 0;
}
```

---

## 作者：linyihdfj (赞：0)

## E.Square Root of Permutation ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16419311.html)
### 题目描述： ###
[原题面](https://codeforces.com/contest/612/problem/E)
### 题目分析： ###
（这仿佛是我第一次彻底搞明白这种映射类型的题）

遇到这类的问题我们一般的思路就是把问题转化为图上问题。

假设我们已经有了序列 $q$，很明显我们的建边思路就是 $i - q_i$ 建边，那么考虑进行了 $q_i = q_{q_i}$ 之后会有什么变化：就是由 $i$ 点连向的点由 $q_i$ 变成了由 $q_i$ 连向的点。我们会发现对于 $i - q_i$ 这些边所构成的图肯定是有许许多多的环组成的，考虑对于环进行分类讨论：

（1）奇环：我们自己模拟一组数据就能知道，奇环经过操作之后还是奇环只不过相当于每个点连向其连向点的下一个点，也就是中间隔开了一个点，那么我们就在最后的图上点与点也是隔一个，这样就能隔回来，也就是能还原

（2）偶环：对于偶环经过操作之后就会被分裂为两个偶环这两个偶环一个对应编号为奇数的点一个对应编号为偶数的点，也是一个点隔一个点连边，只不过奇偶分成了两个部分，那么两个环分别一个个地取这样也就是可以还原回去
### 代码详解： ###
（代码学习的第一篇题解的写法因为我一开始并不会做这个题，但是加上了许多的注释）
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
int nxt[MAXN],tmp[MAXN],flag[MAXN],tmp2[MAXN],q[MAXN];
bool vis[MAXN];
int main(){
	int n;
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>nxt[i]; 
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			int cnt = 0;  //记录环大小
			int now = i;
			do{
				vis[now] = true;  //记录被访问过 
				tmp[++cnt] = now;  //记录环上的点+统计长度 
				now = nxt[now];  //跳边 
			}while(now != i);  //神奇的 do-while 
			if(cnt % 2 == 1){  //奇环 
				for(int i=1,x = 0; i<=cnt; i++,x = (x + 2)%cnt){  //因为有取模操作所以只能从 0 开始 
					tmp2[x] = tmp[i];  //隔一个放一个 
				}
				for(int i=0; i<cnt; i++){
					q[tmp2[i]] = tmp2[i+1];  //我们的建边方式 i->q[i] 所以这样逆回去就好了 
				}
				q[tmp2[cnt-1]] = tmp2[0];  //最后一个连向第一个 
			}
			else{  //偶环 
				if(!flag[cnt])	flag[cnt] = i;
				else{  //合并 
					int x = flag[cnt],cnt2 = 0;
					do{  //获取另一个偶环的信息 
						tmp2[++cnt2] = x;
						x = nxt[x];
					}while(x != flag[cnt]);
					flag[cnt] = 0;
					int t1 = 1,t2 = 1,last = tmp[1];
					for(int i=1; i<=cnt*2; i++){  //这样做:1.大小就是cnt*2 2.为了第一步符合条件 
						if(i % 2 == 0){   //相当于一个个取连边的操作 
							last = q[last] = tmp[++t1];  //这个是因为 t1 不能取 
						}
						else{
							last = q[last] = tmp2[t2++];  //因为 t2 可取 
						}
					}
					q[tmp2[cnt2]] = tmp[1];  //最后的连向最前面的 
				}
			}
		}
	}
	for(int i=2; i<=n; i++){
		if(flag[i]){  //意味着有的偶环没有合并自然就不可行了 
			printf("-1");
			return 0;
		}
	}
	for(int i=1; i<=n; i++){
		printf("%d ",q[i]);
	}
	return 0;
}
```

代码里的注释也非常全，有任何不懂的也可以在下方评论

---

