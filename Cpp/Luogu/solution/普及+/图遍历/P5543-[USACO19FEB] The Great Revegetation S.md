# [USACO19FEB] The Great Revegetation S

## 题目描述

一场漫长的干旱使农场主约翰的 $N$ 个牧场没有草。然而，随着雨季的到来，是时候“重新种植”了。在农夫约翰的小屋里，他有两个桶，每个桶都有不同类型的草籽。他想在他的每一个牧场种草，在每一个牧场中选择一种类型的草。

作为一名奶农，农场主约翰想确保他能满足他那几头奶牛的特殊饮食需求。他的 $m$ 头奶牛都有两个最喜欢的牧场。他的一些奶牛有一个饮食限制，那就是他们应该只吃一种类型的草，因此农场主约翰希望确保在这类奶牛最喜欢的两个田里种植同一种类型的草。其他的奶牛有一个不同的饮食限制，要求他们吃不同类型的草。对于那些奶牛，农场主约翰当然想确保他们最喜欢的两块田地里有不同的草。


请帮助农场主约翰确定他在他的 $N$ 个牧场上种植草的不同方式的数量。

## 说明/提示

USACO 2019 二月月赛银牌组第三题

## 样例 #1

### 输入

```
3 2
S 1 2
D 3 2```

### 输出

```
10```

# 题解

## 作者：potatoler (赞：15)

### [题目](https://www.luogu.com.cn/problem/P5543)描述：

一场漫长的干旱使农场主约翰的N牧场没有草, 然而, 随着雨季的到来, 是时候“重新种植”了。在农夫约翰的小屋里, 他有两个桶, 分别有一种草籽。他想在他的每一个牧场种草, 在每一个牧场中只能种一种草。 作为一名奶农, 农场主约翰想确保他能满足他的M头奶牛的特殊饮食需求。他每头奶牛都有两个自己最喜欢的牧场。一些奶牛只吃一种草, 因此约翰希望确保在这些奶牛最喜欢的两个牧场里种植同一种的草; 剩下的奶牛则吃不同种类的草。对于那些奶牛，约翰当然想确保它们最喜欢的两块牧场里有不同的草。 请帮助农场主约翰确定他在他的N块牧场上有多少种种植草的不同方式。

### 思路：

与关押罪犯有很多相似之处，实用并查集补集的思路，将两个牧场种相同草的关系当作「友好」，将两个牧场种不同草的关系当作「敌对」，但值得注意的一点是并非所有的牧场一定为任意一只奶牛所喜爱，所以我们还需要额外的一个并查集来维护被提到的牧场的连通性。

如果产生冲突，那么最终方案数必定为0；若没有冲突，就在第三个并查集中判断连通块，连通块数为为cnt，则$ans=2^{cnt}$;

### 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m,a,b,ans;
char op;
int fa[100005],gr[200005];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
int com(int x){
    if(gr[x]==x) return x;
    else return gr[x]=com(gr[x]);
}
int main(){
    scanf("%d%d",&n,&m);
    ans=n;
    for(int i=1;i<=n;i++){
        gr[i]=i;
        gr[i+n]=i+n;
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>op>>a>>b;
        // op=getchar();
        // getchar();
        // scanf("%d%d",&a,&b);
      //乖乖用cin（笑）
        if(op=='S'){
            gr[com(a)]=com(b);
            gr[com(a+n)]=com(b+n);
        }
        else{
            if(com(a)==com(b)){
                ans=0;
                break;
            }
            gr[com(a+n)]=com(b);
            gr[com(a)]=com(b+n);
        }
        if(find(a)!=find(b)){
            fa[find(a)]=find(b);
            ans--;
        }
    }
    if(ans==0){
        printf("%d",ans);
        return 0;
    }
    printf("1");
    for(int i=1;i<=ans;i++) printf("0");
    return 0;
}
```



---

## 作者：SzTC (赞：5)

### 题目简述   
- 给出 $n$ 个点，$m$种限制：$a$ 与 $b$ 相等或不等。
- 每个点只有两种数值。
- 求最后满足限制的方案总数。
- 最后用二进制表示答案。
- $n,m<=1e5$
### 思路分析  
先假设没有限制条件，则 $1..n$ 的排列方案数为 $2^n$ 。而我们都知道， $2^n$ 用二进制表示就是 $1$ 后面 $n$ 个 $0$，如：  
$2^3= (1000)_2$   
$2^4= (10000)_2$  
$2^5= (100000)_2$  
观察题目可以发现，不管是哪种限制条件（两个点相等或不等），实际上都是将这两个点“捆绑”在了一起。原本两个点分别有两种数值，在限制之后，一个点的数值决定于另一个点的数值，这两个点完全可以看做一个点。所以，最后求的答案就转换成了，$n$ 个点中有多少个互相没有关系的部分。求出这个答案，不需要考虑两种限制条件的区别，通过一个并查集全都合并即可。  
但是这样做有一个问题：题目给的数据并不保证各组数据之间互不冲突，所以还需要进行判断.这个判断比较简单，直接建图暴力染色，中途如果遇到矛盾就表示冲突了，直接输出 $0$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct E{
		int to,next,v;//结构体存边
}e[211111];
int e_num,p[111111];
void e_add(int x,int y,int v)//建边
{
		e[++e_num].to=y;
		e[e_num].v=v;
		e[e_num].next=p[x];
		p[x]=e_num;
}
int n,m;
int f[311111];
int find(int x)//并查集
{
		if(x==f[x])return x;
		return f[x]=find(f[x]);
}
int mark[111111];
int col[111111];
int fl=0;
void dfs(int x)//暴力染色
{
		 if(fl)return ;
		 for(int i=p[x];i;i=e[i].next)
		 {
	 		int y=e[i].to;
			if(col[y]==-1)//不同情况一一判断
			{
				if(e[i].v==0)
				{
					col[y]=col[x];
					dfs(y);
				}
				if(e[i].v==1)
				{
					col[y]=!col[x];
					dfs(y);
				}
			}
			else
			{
				if((e[i].v==0 && col[x]!=col[y]) || (e[i].v==1 && col[x]==col[y]))
				{
					fl=1;
					cout<<0;//结果矛盾，直接输出0
					return ;
				}
			}
			if(fl)return ;
		}
}
int main()
{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)f[i]=i;
		memset(col,-1,sizeof(col));//颜色数组初始化
		for(int i=1;i<=m;i++)
		{
			char c;
			int a,b;
			cin>>c>>a>>b;
			if(c=='S')
				e_add(a,b,0),e_add(b,a,0);//若相等，则边权为0
			else 
				e_add(a,b,1),e_add(b,a,1);//若不等，则边权为1
			int ra=find(a),rb=find(b);
			f[ra]=rb;//不管条件，直接合并
		}
		for(int i=1;i<=n;i++)
		{
			if(col[i]==-1)//建出来的图不一定联通，每个点都要判断一边
			{
				col[i]=0;
				dfs(i);
			}
		}
		if(fl)return 0;//如果冲突，就在这里结束程序
		int cnt=0;//统计个数
		for(int i=1;i<=n;i++)
		{
			find(i);
			if(!mark[f[i]])
			{
				mark[f[i]]=1;
				cnt++;
			}
		}
		cout<<1;
		for(int i=1;i<=cnt;i++)cout<<0;
		return 0;
}
```


---

## 作者：名杨天吓 (赞：5)

观察题目可以发现，如果某几个牧场被提到之后，若牧场之间没有冲突，他们的方案数肯定是2。对于没有被提到的牧场，他们肯定有2种方案。于是就可以想到是联通块和种类并查集问题。开3个并查集，第一个并查集判断他们是否联通（即被提到），另外两个种类并查集判断他们有没有冲突，即如果同时需要相同和不同就失败。如果失败方案数就必定为0。若处理完后没有冲突，那么只需要在第一个并查集中判断联通块，有几个联通块，方案数则为$2^{cnt}$(cnt=联通块个数),变成2进制表示，就是1后面cnt个0

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int n,m,cnt;
int fa[3*maxn];
bool b;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void join(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fy]=fx;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=3*n;i++)	fa[i]=i;
	for(int i=1;i<=m;i++)
		{
			int x,y;
			char a;
			cin>>a>>x>>y;
			join(x,y);
			if(a=='S')
				{
					if(fa[x+n]==fa[y+2*n] || fa[x+2*n]==fa[y+n])
						{
							b=1;
							break;
						}
					join(x+n,y+n);
					join(x+2*n,y+2*n);
				}
			if(a=='D')
				{
					if(fa[x+n]==fa[y+n])
						{
							b=1;
							break;
						}
					join(x+2*n,y+n);
					join(x+n,y+2*n);
				}
		}
	for(int i=1;i<=n;i++)
		if(fa[i]==i)	cnt++;
	if(b) cnt=0;
	if(!cnt) printf("0\n");
	else
		{
			printf("1");
			for(int i=1;i<=cnt;i++)
				printf("0");
		}
		
	return 0; 
}
```


---

## 作者：哈士奇憨憨 (赞：3)

## 题意
对给定图进行 `01` 染色，每条边描述了两个点是同色或者异色，求染色方案数。
## 思路
因为只有两种颜色，所以连通块中只要有任何一个点的颜色确定了，就可以确定其他点的颜色，因此每个连通块如果可以进行二分图染色，则必然有两种不同的染色方法，$K$ 个连通块则有 $2^K$ 种染色方法。如果有一个连通块无法二分图染色，则总的染色方案为 $0$。我们依次找到每个连通块并进行模拟染色即可。
## 复杂度
### 时间
遍历图 $O(N+M)$。
### 空间
记录图 $O(N+M)$。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1e5 + 1;
struct V {        // 点
  int c;          // 染色
  vector<pair<int, int>> e;  // 邻边
} v[kMaxN];
int n, m, x, y, t;
char ch;
void S(int x, int c) {      // 点x染色c
  if (v[x].c) {             // 已经染色
    if (v[x].c != c + 1) {  // 与之前的染色不同
      t = -n;               // 标记无解
    }
    return;
  }
  v[x].c = c + 1;          // 染色
  for (auto i : v[x].e) {  // 遍历邻边
    S(i.first, c ^ i.second);
  }
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> ch >> x >> y;
    v[x].e.push_back({y, ch == 'D'}), v[y].e.push_back({x, ch == 'D'});
  }
  for (int i = 1; i <= n; i++) {  // 枚举点
    if (!v[i].c) {                // 找到新的连通块
      S(i, 0);                    // 染色
      t++;                        // 累加数量
    }
  }
  cout << (t > 0 ? "1" + string(t, '0') : "0");
  return 0;
}
```

---

## 作者：SymphonyOfEuler (赞：2)

因为只有两种草，所以我们可以黑白染色。必须相同的一个点染一样的一个颜色，否则然不一样的颜色。可以用1和-1表示这两种颜色，然后用初始化为0表示还没有走到。

用一个dfs，从一个点开始，根据规则染色，如果任何时间发现矛盾，就返回 非。

题目让输出二进制，所以每次染完的方案数乘二，结果末尾多一个0即可。

我们定一个数组color表示某点的颜色，初始化为0，当我们发现一个点为0就开始从他跑dfs，dfs为布尔类型，返回true表示没有矛盾，false表示有矛盾。在main里如果得到没有矛盾就答案加一，否则输出0（因为如果图中有一个矛盾就输出0），没有的话就是1后面答案个数个0。

dfs里传进来一个点，还有这个点的颜色。进来第一件事就是记录在color数组中。adj1表示和你相同的点，所以循环到adj1[u].size()（表示和你这个点的相同的个数），找到一个新的点，看看是不是0，如果是，再在他身上跑一遍dfs，如果这个也有矛盾，那么u点也有矛盾，所以返回false即可。然后如果这个点的颜色和u的颜色不同，明显矛盾，也返回false。不同的也是一样的，但是dfs时候注意color要用这u点相反的颜色。

贴一下dfs的代码就行了，其他的都很简单。

```
bool dfs(int u, int c) {
    color[u] = c;
    for (int i = 0; i < adj1[u].size(); ++i) {
        int v = adj1[u][i];
        if (color[v] == false) if (dfs(v, c) == false) return false;
        if (color[v] != color[u]) return false;
    }
    for (int i = 0; i < adj2[u].size(); ++i) {
        int v = adj2[u][i];
        if (color[v] == false) if (dfs(v, -c) == false) return false;
        if (color[v] == color[u]) return false;
    }
    return true;
}

```



---

## 作者：VTloBong (赞：2)

容易想到，可以用并查集把每个约束条件中提到的两牧场所在集合合并。  
设最后集合的个数为 cnt 如果不发生冲突每个集合都有两种选择，那么方案数即为 $2^{cnt}$，其二进制即为1后 cnt 个0。

是否冲突怎么判定呢？

可以用带权并查集解决，所谓带权并查集就是在普通并查集fa数组的基础上，增加val数组来记录一个节点与其父节点的关系（即“权”）。  
如何记录关系呢？  
最开始，每个节点的 fa 都是自己， val 都为0；  
在查找 a 的祖先并路径压缩时，在普通并查集路径压缩的基础上  使$val_a=(val_{{fa}_a}+val_a)\bmod \texttt{base}$  ；  
若要合并 a , b 两节点，权为 w ，就让 a 的祖先成为 b 的 fa,
并使 $val_{{fa}_b}=(w-val_a-val_b) \bmod \texttt{base}$ 。  
base视情况而定。   
在这道题中，可以用 0 来表示相同，用 1 来表示相异；  
相同合并时的权值为 0 ，相异时权值为 1 ；  
显然，$(1+1) \bmod2=0$,则 base=2。  
当合并时发现a和b在同一集合中时，若$(val_a+val_b)\bmod2=w$，不成立，则有冲突，方案数为 0 。


##
## 参考代码：
```cpp
#include<stdio.h>
const int maxn=100010;
int p[maxn],s[maxn],v[maxn];
int find(int x){
	if(p[x]==x)return x;
	int f=find(p[x]);
	v[x]=(v[x]+v[p[x]])&1,p[x]=f;
	return f;
}
int main(){
	int n,m,impossible=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)p[i]=i,s[i]=1;
	char str;
	while(m--){
		str=getchar();
		while(str!='S'&&str!='D')str=getchar();
		int a,b;
		scanf("%d%d",&a,&b);
		if(impossible)continue;
		int fa=find(a),fb=find(b),t,l,w=(str=='D');
		if(fa!=fb){
			if(s[fa]>s[fb])t=fa,fa=fb,fb=t,l=a,a=b,b=l;
			p[fa]=fb,s[fb]+=s[fa],v[fa]=(w>=v[a]+v[b]?w-v[a]-v[b]:v[a]+v[b]-w)&1;
		}else impossible=(((v[a]+v[b])&1)!=w);
	}if(impossible){
		putchar('0');
		return 0;
	}for(int i=1;i<=n;i++)
		if(p[i]==i)s[0]++;
	putchar('1');
	while(s[0]--)putchar('0');
	return 0;
} 
```

---

## 作者：MyukiyoMekya (赞：0)

我们会发现几个性质：

把每个限制的两个点连边，如果能满足所有限制，那么方案数就是 $2^{\text{连通块的个数}}$

因为，一个连通块内如果能满足所有限制，那么把所有连通块内的类型都换一下也能满足所有限制

也就是说，一个连通块存在两种不同种草方式

那么如果存在一个连通块内无论怎么种草都没办法使连通块内的所有限制都能满足

那么直接输出 0

这个判断可以贪心的判，直接暴力染色，然后最后再扫一遍就行了

因为贪心可以满足当前这个限制是满足的，但是不能保证会不会使其他限制不满足，如果他和其他限制产生了冲突，那么在最后扫的过程中一定会被判断出来，否则就没有冲突

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=100050;
struct Edge
{
	int nxt,to,w;
	// S 0  D 1
}E[MaxN<<2];
struct Quetion
{
	int opt,u,v;
	// S 0  D 1
}Q[MaxN<<1];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int hd[MaxN],en,n,m;
int col[MaxN];
inline void adde(int u,int v,int w)
{
	++en;
	E[en]=(Edge){hd[u],v,w};
	hd[u]=en;
	return;
}
inline void dfs(int u,int fa)
{
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa||col[v]!=-1)
			continue;
		if(!E[i].w)
			col[v]=col[u];
		else
			col[v]=1-col[u];
		dfs(v,u);
	}
	return;
}
signed main(void)
{
	memset(hd,-1,sizeof hd);
	memset(col,-1,sizeof col);
	cin>>n>>m;
	reg int u,v;
	char opt[3];
	for(int i=1;i<=m;++i)
	{
		scanf("%s",opt);
		read(u);read(v);
		Q[i]=(Quetion){
			0,u,v
		};
		if(opt[0]=='S')
			adde(u,v,0),adde(v,u,0);
		else
			adde(u,v,1),adde(v,u,1),Q[i].opt=1;
	}
	reg int ans=0;
	for(int i=1;i<=n;++i)
		if(col[i]==-1)
		{
			++ans;
			col[i]=0;
			dfs(i,0);
		}
	for(int i=1;i<=m;++i)
		if(!Q[i].opt)
		{
			if(col[Q[i].u]!=col[Q[i].v])
			{
				puts("0");
				return 0;
			}
		}
		else
		{
			if(col[Q[i].u]==col[Q[i].v])
			{
				puts("0");
				return 0;
			}
		}
	printf("1");
	for(int i=1;i<=ans;++i)
		putchar('0');
	puts("");
	return 0;
}
```



---

## 作者：yangyujia18 (赞：0)

这是一道种类并查和普通并查的综(keng)合(die)题  
种类并查是一种可以用于解决分类关系的算法  
它需要一个同类集和n个异类集（n为总类别-1），每个异类集的每一个元素都对应同类集的一个元素  
异类集的元素在一个集就表示同类集元素不在某个集  

举个栗子qwq  
现在有5个人，分为3支队伍  
1号跟2号不在一队
1号同类集合2号异类集合并，2号和1号异类集合并  
如果1号和2号的同类集已合并，则出现错误  

#### 注意同类的合并时不需要判断是否符合条件，异类合并需要判断（因为这个我调了三周）！  
普通的并查这里不再细说，具体可以看程序中的findf,unite函数和fa数组  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,ans;
int fa[100005],grass[200005];
int findf(int a)
{
	if(fa[a]==a)
		return a;
	fa[a]=findf(fa[a]);
	return fa[a];
}
int findg(int a)
{
	if(grass[a]==a)
		return a;
	grass[a]=findg(grass[a]);
	return grass[a];
}
bool unite(bool s,int a,int b)
{
	if(s)
	{
		grass[findg(a)]=findg(b);
		grass[findg(a+n)]=findg(b+n);
	}
	else
	{
		if(findg(a)==findg(b))
			return false;
		grass[findg(a+n)]=findg(b);
		grass[findg(a)]=findg(b+n);
	}
	if(findf(a)!=findf(b))
	{
		fa[findf(a)]=findf(b);
		ans--;
	}
	return true;
}
int main()
{
	char c;
	cin>>n>>m;
	ans=n;
	for(int i=1;i<=n;i++)
	{
		grass[i]=i;
		grass[i+n]=i+n;
		fa[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>c>>u>>v;
		if(!unite(c=='S',u,v))
		{
			ans=0;
			break;
		}
	}
	if(ans==0)
	{
		cout<<ans<<endl;
		return 0;
	}
	cout<<1;
	for(int i=1;i<=ans;i++)
		cout<<0;
	cout<<endl;
	return 0;
}
```


---

## 作者：zhmshitiancai (赞：0)

题意：$n$头牛，$m$个条件，每个条件关于两头牛$i$,$j$。为这两头牛的口味是否相同。求所有牛的口味的方案数，以二进制输出。

解：容易想到，应用并查集。如果有关于两头奶牛的条件，一个的口味就随另一个的确定而确定，就把他们并起来。设最后并查集的个数为$cnt$，答案为$2^{cnt}$。但如何判是否可行呢？

如果开始时开两个集合，相同的在一个集合，不相同的不在一个集合，可以吗？

不行，因为，在读到一个奶牛时，它可以被放到A中，也可以被放到B中，如果你随便把它扔进一个集合中，就会错判。

我的做法是，先建一张带权图，权值为0或1，表示是否不同，在图上以深搜黑白染色，就能避免上面的问题。

``` cpp

//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long  
const int INF=0x3f3f3f3f,MAX=1e5+5;
int n,m;
int f[MAX];
int find(int x)
{
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void hebing(int x,int y){
	x=find(x);y=find(y);
	if(x!=y) f[x]=y;
}
int head[MAX*2],to[MAX*2],type[MAX*2],cnt,Next[MAX*2];
void add(int x,int y,int z)
{
	cnt++;
	Next[cnt]=head[x];head[x]=cnt;
	to[cnt]=y;type[cnt]=z;
}
int col[MAX];
bool vis[MAX];
bool dfs(int x)
{
	int i;
	for(i=head[x];i;i=Next[i])
	{
		int u=to[i],z=type[i];
		int yg=col[x]^z;		
		if(col[u]&&col[u]!=yg)
			return false;
		if(col[u]) continue;

		col[u]=yg;
		if(!dfs(u))	 return false;
	}
	return true;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i;
	cin>>n>>m;
	
	char c;
	for(i=1;i<=n;i++)
		f[i]=i;
	c=getchar();
	for(i=1;i<=m;i++)
	{
		c=getchar();
		int x,y;
		scanf("%d%d",&x,&y);
		
		
		hebing(x,y);
		if(c=='D'){
			add(x,y,1);
			add(y,x,1);
		}
		else {
			add(x,y,0);
			add(y,x,0);
		}
		c=getchar();
	}
	
/*	for(i=1;i<=cnt;i++)
		cout<<type[i]<<" ";
	cout<<endl;*/
	bool f=1;
	for(i=1;i<=n;i++)
	{
		if(!col[i])
		{
			col[i]=2;
			f&=dfs(i);
		}
	}
	if(!f) cout<<0<<endl;
	else 
	{
		int ans=0;
		for(i=1;i<=n;i++)
		{
			int x=find(i);
			if(!vis[x]){
				ans++;
				vis[x]=1;
			}
		}
		
		cout<<1;
		for(i=1;i<=ans;i++)
			cout<<0;
	}
}
/*
3 3
S 1 2
D 3 2
S 1 3
*/
```

---

