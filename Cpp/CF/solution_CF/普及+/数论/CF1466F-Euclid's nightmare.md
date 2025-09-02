# Euclid's nightmare

## 题目描述

给定包含 $n$ 个 $m$ 维向量的向量集 $S$，每个向量 $\overrightarrow{a}$ 满足 $a_i\in \{0,1\}$ 且 $\sum\limits_{i=1}^ma_i\in\{1,2\}$。定义向量加法 $\overrightarrow{c}=\overrightarrow{a}+\overrightarrow{b}$ 为 $\forall i\in \Z\cap[1,m], c_i=a_i\oplus b_i$，其中 $\oplus$ 表示异或运算。

求极大线性空间 $T$ 使得 $T$ 的一组基 $A$ 均为 $S$ 中元素。输出 $|T|,|A|$ 以及 $A$。

要求在 $|A|$ 最小前提下 $A$ 关于向量编号字典序最小。

## 样例 #1

### 输入

```
3 2
1 1
1 2
2 2 1```

### 输出

```
4 2
1 2```

## 样例 #2

### 输入

```
2 3
2 1 3
2 1 2```

### 输出

```
4 2
1 2```

## 样例 #3

### 输入

```
3 5
2 1 2
1 3
1 4```

### 输出

```
8 3
1 2 3```

# 题解

## 作者：zzr8178541919 (赞：5)

非常好的一道思维题

由于本人的英语能力糟糕，导致比赛时翻译花了十多分钟时间来理解题意。

### 题目大意：
就是给你$n$个$m$位的01数字串，保证每个数字串最多有两个1，至少一个1，问你现在从这$n$个串选择若干个出来（假设选了$k$个），将它们的同一位的数相加（$mod \ 2 $）,得到数字串$T$，问最终能得到多少种不同的T。并要求从$n$个串中选一个$|S^{'}|$最小的,且选择的字典序最小的子集$S^{'}$出来，使得用这几个数字串也能拼出集合$T$。
###  _Solution_ 
初看感觉是一道字符串题，而实际上这题可以用并查集解决。

观察题干，注意到每个数字串最多只有两个1，由此入手寻找性质。

#### 如果每个串都是两个1：

我们将每次输入的两个数$ x , y $用并查集连起来，最后会得到若干个连通块，每个连通块大小为$siz[i]$,边数为$siz[i]-1$,选一条边实际上代表的是选了一个数字串，那么每条边都有选与不选两种情况，共$ 2^{siz[i]-1}$种情况。并且有一个十分重要的性质：
#### 这$2^{siz[i]-1}$种情况得到的结果互不相同！ 
所以每个连通块的方案数就是$ 2^{siz[i]-1}$

答案就是各个连通块的方案数相乘

选择$S^{'}$也很简单，每次当前如果$x,y$不在同一个连通块，该数字串就要选。

#### 现在考虑有一个1的情况：
一个非常巧妙的方法就是，新增一个节点:$(m+1)$。对于那些只有一个1的数组串，输入$x$，令$y=m+1$，其它的操作都不变。

于是我们就很方便地求出了$S^{'}$集合。

#### 一个小优化：
$|T|$是可以由$|S^{'}|$(假设为$lens$)推出来的。$S^{'}$集合中不同的选择方案，得到的数字串一定不同。
所以$|T|=\sum\limits_{i=0}^{len_s}C^i_{len_s} =2^{len_s}$

#### code:
```cpp
#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define int long long
#define reg register
using namespace std;
const int maxn=5e5+5;
const int mod=1e9+7;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int father[maxn];
int Find(int x)
{
	if(father[x]!=x)
	father[x]=Find(father[x]);
	return father[x];
}
int n,m;
int s[maxn];
int tot=0;
int siz[maxn];
int v[maxn];
signed main()
{
	v[0]=1;
	n=read(),m=read();
	for(int i=1;i<=max(n,m)+5;i++)
	v[i]=v[i-1]*2%mod;
	for(reg int i=1;i<=m+1;i++)
		father[i]=i;
	int cnt=0;
	for(reg int i=1;i<=n;i++)
	{
		int k=read(),x,y;
		if(k==1)
			x=read(),y=m+1;
		else
			x=read(),y=read();
		int nowx=Find(x),nowy=Find(y);
		if(nowx==nowy)
		continue;
		father[nowx]=nowy;
		s[++tot]=i;
	}
	int ans=v[tot]%mod;
	printf("%lld %lld\n",ans,tot);
	for(reg int i=1;i<=tot;i++)
		printf("%lld ",s[i]);
	printf("\n");
 	return 0;
}
```


---

## 作者：Soulist (赞：3)

## F

给定 $n$ 个二进制数 $a_i$，求他们的线性基的大小，保证每个元素只有不超过两个 $1$（以及按照顺序将元素选入线性基得到的序列）

$n,m\le 5\cdot 10^5$，$m$ 为位数。

### Solution

$2$ 个 $1$ 的情况让人自然的想到连边，添加一个辅助节点 $m+1$，一个位的情况和其连即可。

用并查集维护连通性，环显然是非法的。

---

## 作者：gyh20 (赞：1)

来一个纯线性基角度的理解。

首先，可以发现如果我们能够维护出线性基那么答案就显而易见了。

直接插入是 $O(nm)$ 的，考虑优化。

由于每一个数只有两维，分别为 $a,b$，如果只有一维则 $b=0$，那么线性基中的每个位置上的数也只有两维。

假设当前插入的数是 $A,B(A>B)$，线性基第 $A$ 维上的数是 $a,b$，那么在异或后就会变成 $b,B$，也就是说，把 $A$ 变成了 $b$，然后如果 $b<B$ 交换 $b,B$。我们可以发现，$A$ 最后跳到哪个位置和 $B$ 无关，我们可以直接分别跳 $A,B$。（多跳显然没有问题），然后如果 $\max(A,B)>0$ 从最后的 $A$ 连向 $B$。

这就是一个并查集就搞定的了，和生成树的理解方式不一样但代码却一样。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[500002],b[500002],t,ans,p[500002],fa[500002];
inline int root(re int x){return x==fa[x]?x:fa[x]=root(fa[x]);}
const int M=1000000007;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int ksm(re int x,re int y){
	re int ans=1;
	while(y){
		if(y&1)ans=1ll*ans*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return ans;
}
int main(){
	n=read(),m=read();
	for(re int i=1;i<=m;++i)fa[i]=i;
	for(re int i=1;i<=n;++i){
		re int x=read();
		if(x==1)a[i]=read();
		else a[i]=read(),b[i]=read();
		a[i]=root(a[i]),b[i]=root(b[i]);
		if(a[i]==b[i])continue;
		if(a[i]<b[i])swap(a[i],b[i]);
		if(b[i])fa[a[i]]=b[i];
		else fa[a[i]]=0;
		p[a[i]]=i;
	}
	for(re int i=1;i<=m;++i)if(p[i])++ans;
		printf("%d %d\n",ksm(2,ans),ans);
		sort(p+1,p+m+1);
	for(re int i=1;i<=m;++i)if(p[i])printf("%d ",p[i]);
}
 
```


---

## 作者：lytqwq (赞：1)

~~没做出来自闭了~~

从简单情况入手，如果只有每次只有一个维度的向量，每个输入都会让一个维度可以选 $1$ 或 $0$ ，我们就有  $2^{|S|}$ 种情况， $|S|$ 就是不同维度的个数，最后把不同的输出就行了。

但是现在可能会有两个维度的向量，如果这两个维度没有其他向量干扰的话，把它们当做一个维度就行了。

如果现在有 两个**两个维度的向量**是有刚好一个维度是一样的，如：

第一个向量的两个维度是 $A,B$

第二个向量的两个维度是 $B,C$

有 $A,C;A,B;B,C;\text{空}$ 四种情况，发现把它们分别做一个维度就行了。

如果现在出现 一个向量是 $A,C$ 不计算它 

如果在这之前有 $A,B,C$ 中的维度可以被单独计算出来，不考虑这情况

然后你就发现这实际上形成了一个图，我们可以连一条边表示这个向量被考虑了，每个顶点就代表一个维度，如果现在的这个向量连的两个维度已经相连，说明前面的可以把这个向量表示出来，这个向量没用

如果是一个维度的向量，我们把它连到一个超级点 $m+1$ 表示它可以直接被表示出来，最后统计有多少向量有用，输出答案即可

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long int N=500010,p=1e9+7;
long long int n,m,k;
vector<int> ovo;
long long int father[N];
long long int find(long long int x){
	if(father[x]!=x)father[x]=find(father[x]);
	return father[x];
}
void join(long long int u,long long int v,long long int x){
	long long int fx=find(u),fy=find(v);
	if(fx!=fy){
		ovo.push_back(x);
	}
	father[fx]=fy;
}
long long int Qp(long long int x,long long int y){
	long long int res=1;
	while(y){
		if(y&1){
			res*=x;
			res%=p;
		}
		x*=x;
		x%=p;
		y>>=1;
	}
	return res;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(long long int i=1;i<=m+1;i++){
		father[i]=i;
	}
	for(long long int i=1;i<=n;i++){
		scanf("%lld",&k);
		long long int u,v=m+1;
		scanf("%lld",&u);
		if(k>1)scanf("%lld",&v);
		join(u,v,i);
	}
	long long int len=ovo.size();
	printf("%lld %lld\n",Qp(2,len),len);
	for(long long int i=0;i<len;i++)printf("%lld ",ovo[i]);
	printf("\n");
}

```





---

