# Sorting by Subsequences

## 题目描述

给你一个由不同整数组成的序列$a_{1},a_{2},...,a_{n}$  
。要求将这个序列分成最多的子序列，使这些子序列按升序排序后，总体序列也成为一个升序序列。

在对子序列进行排序的过程中，只是对子序列中的元素进行升序排序，不在子序列中的元素不会改变它们的位置。

序列中的每个元素都只能且必须在所有子序列中出现一次。（译者：子序列不重合）

## 样例 #1

### 输入

```
6
3 2 1 6 5 4
```

### 输出

```
4
2 1 3
1 2
2 4 6
1 5
```

## 样例 #2

### 输入

```
6
83 -75 -49 11 37 62
```

### 输出

```
1
6 1 2 3 4 5 6
```

# 题解

## 作者：LKY928261 (赞：2)

## 题目分析

根据题意，为了在每个子序列按升序分别排序后，能使总体序列也变为升序序列，在各个子序列按升序排序后，其中每个元素所对应的位置必须与其在整个序列升序排序后的位置相同。

我们假设第 $i$ 个元素 $a_i$ 在整个序列中是第 $t_i$ 小的数，则 $a_i$ 在子序列中排完序后，其位置须在 $t_i$ 。显然，第 $t_i$ 个元素必须与第 $i$ 个元素在同一子序列中，否则 $a_i$ 在子序列中排完序后的位置不可能是 $t_i$ 。

以此类推，第 $t_{t_i}$ 个元素与第 $i$ 个元素也在同一子序列中……如此递推，直至当前的 $t_i$ 已在该子序列中出现过时，表明该子序列已构造完成。

同时，这也是能使子序列最多的方案。

由于 $1\le n\le10^5$ ，建议用线性表储存答案，最后一次性输出。

时间复杂度为 $O(n\log n)$ 。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

~~（请不要在意我奇丑无比的码风）~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,t,k,a[100005],c[100005],d[100005],i,j;bool f[100005];
pair<ll,ll>b[100005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++){cin>>b[i].first;b[i].second=i;}
	sort(b+1,b+n+1);
	for(i=1;i<=n;i++)a[b[i].second]=i;//记录每个元素的大小关系
	for(i=1;i<=n;i++)if(!f[i]){
		c[t++]=i,f[i]=1;
		for(x=a[i];!f[x];x=a[x])f[x]=1,c[t++]=x;
		d[++k]=t;
	}
	cout<<k<<"\n";
	for(i=1;i<=k;i++){
		cout<<d[i]-d[i-1];
		for(j=d[i-1];j<d[i];j++)cout<<' '<<c[j];
		cout<<"\n";
	}
}
```

---

## 作者：xzggzh1 (赞：1)

其实并不需要 Graphcity 巨佬题解里说的用 $\rm Tarjan$ 找环。

---

题意：

将一个序列分成最多的子序列，使这些子序列按升序排序后，总体序列也成为一个升序序列。

$n\leq 10^5$ 。保证序列中元素各不相同。

---

没思路的话直接看样例 $1$ ，将序列整个排序后，把原来位置上的数与排完序的该数的位置连线结果是这样的。

（显然，目标的升序序列唯一）。

![](https://cdn.luogu.com.cn/upload/image_hosting/e9b3rvb9.png)

由于分出来的子序列必然是交际为空，并集为全集，所以若两个位置有连线，那么这两个位置必然在同一个集合里。

那么我们先排序，然后把对应位置的元素加入同一个集合中，最后输出有多少个集合和集合中的元素即可。这个可以用并查集实现，也可以直接模拟。

---

核心代码：

```cpp
scanf("%d",&n);
for(int i=0;i<n;i++) scanf("%d",&a[i]),b[i]=a[i];
sort(b,b+n);
for(int i=0;i<n;i++) a[i]=lower_bound(b,b+n,a[i])-b;
for(int i=0;i<n;i++)if(!vis[i])
{for(int j=a[i];!vis[j];j=a[j]) vis[j]=1;ans++;}
printf("%d\n",ans);
for(int i=0;i<n;i++)
{
    if(vis[i])
    {
        s.clear();
        for(int j=a[i];vis[j];j=a[j]) s.insert(j+1),vis[j]=0;
        int pos=s.size();
        printf("%d",pos);
        for(it=s.begin();it!=s.end();it++)printf(" %d",*it);
        printf("\n");
    }
}

```

---

## 作者：Graphcity (赞：1)

## 思路

这道题考察的是 **图论**。首先从建模讲起：

把原序列升序排序，把每个数在原序列的位置向它在新序列的位置连边即可，可以看出边的意思是这个数应该从哪里“搬”到哪里。

![](https://cdn.luogu.com.cn/upload/image_hosting/oa2j1jk2.png)

建模之后，可以发现一个神奇的性质：形成一个环时，环中的数经过排序后就可以一一对应新序列了。也就是说，它们可以形成一个 **子序列** 。

接下来，用 Tarjan 算法找出所有的环即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=int(1e5);

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int n;
struct Num //存储数字 
{
	int val,id;
} k[Maxn+5];
inline int cmp(Num x,Num y)
{
	return x.val<y.val;
}

struct Node 
{
	int to,nxt;
} Edge[Maxn+5];
int tot,Head[Maxn+5];

inline void Addedge(int x,int y)
{
	Edge[++tot]=(Node){y,Head[x]};
	Head[x]=tot;
}

vector<int> vec[Maxn+5]; //每种颜色对应的数 
int dfn[Maxn+5],low[Maxn+5],nowd;
int st[Maxn+5],vis[Maxn+5],siz;
int nowcol;

inline void Tarjan(int x)
{
	dfn[x]=low[x]=++nowd;
	st[++siz]=x,vis[x]=1;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(!dfn[y])
		{
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]) //这里跟原来相比需要略微改动 
	{
		++nowcol;
		while(1)
		{
			int y=st[siz--];
			vis[y]=0;
			vec[nowcol].push_back(y);
			if(y==x) break;
		}
	}
}

int main()
{
	n=read();
	for(register int i=1;i<=n;++i)
		k[i].val=read(),k[i].id=i;
	sort(k+1,k+n+1,cmp);
	for(register int i=1;i<=n;++i)
		Addedge(k[i].id,i);
	for(register int i=1;i<=n;++i)
		if(!dfn[i]) Tarjan(i);
	printf("%d\n",nowcol);
	for(register int i=1;i<=nowcol;++i)
	{
		printf("%d ",vec[i].size());
		for(register int j=0;j<vec[i].size();++j)
			printf("%d ",vec[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF843A)
## 思路
咋感觉题解都说的好复杂，这题其实非常水。

首先我们显然需要把这个序列先排个序，设某个数 $x$ 原来的位置为 $x_{pre}$，现在的位置为 $x_{now}$，显然，$x_{pre}$ 和 $x_{now}$ 必须在一个子集中（要不然它咋换过来的）。

题目又让我们求分成子序列数量的最大值，所以我们要分的尽可能多，所以我们可以直接按上述的限制条件并查集。

还有一个坑点就是我们需要记录子序列内的数，我们当然可以线性地求出来，也不难写，但是我（~~一时脑抽~~）用了启发式合并，在并查集的过程中合并子序列。

时间复杂度：
   1. 不用启发式合并 $O(n)$。
   2. 用启发式合并 $O(n \log n)$。

## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define rint register int
using namespace std;
int const N=1e5+10;
int fa[N],to[N];
struct node{int v,id;}a[N];
vector<int>v[N];
inline void Heuristic_merge(int x,int y){
    if (v[to[x]].size()<v[to[y]].size()) swap(to[x],to[y]);
    while (v[to[y]].size()) v[to[x]].push_back(v[to[y]][v[to[y]].size()-1]),v[to[y]].pop_back();
}//标准的启发式合并
inline int find(int x){
    if (x==fa[x]) return x;
    Heuristic_merge(fa[x],x);
    return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    int tx=find(x),ty=find(y);
    if (tx==ty) return;
    Heuristic_merge(tx,ty);
    fa[tx]=ty;
}
inline bool cmp(node x,node y){return x.v<y.v;}
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int n;cin>>n;
    for (rint i=1;i<=n;++i) cin>>a[i].v,a[i].id=i;
    sort(a+1,a+n+1,cmp);
    for (rint i=1;i<=n;++i) fa[i]=i,to[i]=i,v[to[i]].push_back(i);
    for (rint i=1;i<=n;++i) merge(a[i].id,i);
    for (rint i=1;i<=n;++i) fa[i]=find(fa[i]);
    sort(fa+1,fa+n+1);
    int q=unique(fa+1,fa+n+1)-fa-1;//去重，得到最终的答案
    cout<<q<<'\n';
    for (rint i=1;i<=q;++i){
        cout<<v[to[fa[i]]].size()<<' ';
        for (rint j=0;j<v[to[fa[i]]].size();++j)
            cout<<v[to[fa[i]]][j]<<' ';
        cout<<'\n';
    }
    return 0;
}

```


---

## 作者：CaiXY06 (赞：0)

我们先将序列 $a_1,a_2,a_3...a_n$ 进行排序，找到每个元素在排序后应有的位置，我们将元素当前所在位置向目标位置连一条**单向边**，表示当前位置的元素需要转移到目标位置（目标位置的元素并不一定要转移到当前位置）。比如样例一：

![](https://cdn.luogu.com.cn/upload/image_hosting/ipyxpad7.png)

我们会发现所求的答案，即最多的集合数，就是联通环路的个数，又因为这里每个点都会有且仅有一条入边和一条出边，所以联通环路个数就等同于连通块个数，所以我们只要**DFS**遍历整张图即可。

附上code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int to,next;
}e[100010];
int n,cnt,head[100010],a[100010],b[100010],ans;
bool vis[100010];
vector<int>v;
inline void add(int u,int v){
	cnt++;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline void dfs(int u,bool tag){
	vis[u]=tag;
	v.push_back(u);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(vis[v]==tag)continue;
		dfs(v,tag);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		int pos=lower_bound(b+1,b+n+1,a[i])-b;//二分找到目标位置
		add(i,pos);//建边
	}
	for(int i=1;i<=n;i++)//统计连通块个数
	if(!vis[i]){
		v.clear();
		ans++;
		dfs(i,1);
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)//输出集合大小及所含元素
	if(vis[i]){
		v.clear();
		dfs(i,0);
		printf("%d",v.size());
		for(int j=0;j<v.size();j++)printf(" %d",v[j]);
		puts("");
	}
	return 0;
}
```


---

