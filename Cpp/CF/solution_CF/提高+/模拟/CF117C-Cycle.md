# Cycle

## 题目描述

一个 $\texttt{tournament}$ 是一个没有自环的有向图，同时，每两个点之间有一条边连接。这就是说，对于两个点 $u,v (u\neq v)$，有一条从 $u$ 到 $v$ 的边或一条从 $v$ 到 $u$ 的边。

给你一个 $\texttt{tournament}$，请找出一个长度为 $3$ 的环。

## 样例 #1

### 输入

```
5
00100
10000
01001
11101
11000
```

### 输出

```
1 3 2 ```

## 样例 #2

### 输入

```
5
01111
00000
01000
01100
01110
```

### 输出

```
-1
```

# 题解

## 作者：stoorz (赞：32)

给出一种非常简洁的做法。

考虑对于一个点 $x$，我们能找到两个点 $y,z$，满足它们之间的连边如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nvu9zvpi.png)

那么 $x\to z$ 这条边一定是没用的，也就是如果我们能找到一个大小为 $3$ 的环包含 $x\to z$ 这条边，那么我们一定可以找出另一个不包含 $x\to z$ 这条边的大小为 $3$ 的环。如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/tgjkzyk2.png)

假设 $z,a,x$ 三个点形成了一个大小为 $3$ 的环，那么考虑 $a$ 和 $y$ 之间的连边，如果是 $a\to y$，那么 $a,y,z$ 三个点可以形成另一个环；如果是 $y\to a$，那么 $a,x,y$ 三个点可以形成另一个环。

所以我们可以直接把 $x\to z$ 这条边忽略掉。

这样的话把若干条边忽略后，每一个点最多只有一条出边。那么我们只需要枚举两个点 $i,j$，再判断 $i,\text{to}_i,j$ 三点是否形成环即可。

时间复杂度 $O(n^2)$，代码仅有 459B。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=5010;
int n,to[N];
char a[N][N];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (a[i][j]==49 && (!to[i] || a[j][to[i]]==49)) to[i]=j;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (a[to[i]][j]==49 && a[j][i]==49)
				return printf("%d %d %d\n",i,to[i],j),0;
	printf("-1");
	return 0;
}
```

---

## 作者：用户已注销 (赞：13)


首先作为一个有图论常识的人，我们可以轻易看出所谓** tournament **就是 **竞赛图（有向完全图）**

作为一个有图论常识的人，我们可以轻易回想起竞赛图的重要性质：

**竞赛图没有自环，没有二元环；若竞赛图存在环，则一定存在三元环。**

前半句话浅显易懂，后半句话的意思就是说：如果存在一个环大于三元，那么一定存在另一个三元的小环。

### 简单证明：

假设一个竞赛图存在一个 N 元环（大于三元），环上有连续三点 A , B , C （ 存在有向边 AB , BC ）

根据竞赛图的定义，一定存在有向边 CA 或 AC 中的一者。

情况 1 ：若存在 CA ，则 A , B , C 构成三元环；

情况 2 ：若存在 AC ，不考虑 B 点，剩下的点构成一个 (N-1) 元环。显然，如果一直不存在情况 1 的话，最终也会形成一个三元环。

### 证明完毕。

那么这就成了一道有向图找环的裸题，下述代码使用 Tarjan 算法找到一个环，然后**模拟上面的证明过程**找到目标三元环：

```cpp
#include <cstdio>

using namespace std ;

inline bool Bool() {
	
	for(register char C = getchar() ; ; C = getchar() )
		if( C == '0' or C == '1' ) return C - '0' ;
	
}

inline int Readin() {
	
	register int K = 0 ;
	register char C = getchar() ;
	for( ; C < '0' or C > '9' ; C = getchar() ) ;
	for( ; C <= '9' and C >= '0' ; C = getchar() )
		K = ( K << 1 ) + ( K << 3 ) + C - '0' ;
	return K ;
	
}

int N ;

bool Map[5005][5005] ; 
bool Finish ;
bool Vis[5005] ;
bool Instack[5005] ;
int Stack[5005] , Top ;
int Ring[5005] , Rtop ;

void Dfs( int Nod ) {
	
	if( Finish ) return ;
	
	if( Instack[Nod] ) {
		Finish = true ;
		while( Stack[Top] != Nod )
			Ring[++Rtop] = Stack[Top--] ;
			Ring[++Rtop] = Nod ;
		return ;
	}
	
	if( Vis[Nod] ) return ;
	
	Instack[Nod] = Vis[Nod] = true ;
	Stack[++Top] = Nod ;
	
	for(register int i = 1 ; i <= N ; i++ )
		if( Map[Nod][i] ) Dfs(i) ;
	
	Top-- ;
	Instack[Nod] = false ;
	return ;
	
}
 
int main() {
	
	N = Readin() ;
	for(register int i = 1 , j ; i <= N ; i++ )
		for( j = 1 ; j <= N ; j++ ) Map[i][j] = Bool() ;
	
	for(register int i = 1 ; i <= N ; i++ )
		if( not Vis[i] ) Dfs(i) ;
	
	if( not Finish )
		return not printf( "-1\n" ) ;
	
	for(register int i = 1 , T ; i <= Rtop >> 1 ; i++ ) {
		T = Ring[i] ;
		Ring[i] = Ring[Rtop-i+1] ;
		Ring[Rtop-i+1] = T ;
	}
	
	for(register int i = 3 ; i <= Rtop ; i++ )
		if( Map[Ring[i]][Ring[1]] )
			return not printf( "%d %d %d\n" , Ring[1] , Ring[i-1] , Ring[i] ) ;
	return not printf( "%d %d %d\n" , Ring[1] , Ring[Rtop-1] , Ring[Rtop] ) ;
	
}
```

---

## 作者：Mophie (赞：5)

首先注意到每两个点之间必然有一条边。

然后考虑枚举三元环的一个点 $u$。

枚举完后可以发现对于这个点以外的一个点 $v$，要么有 $u -> v$ 要么有 $v -> u$。

我们以此把其他点分为两个颜色，如果对于一个点 $v$，若 $u->v$ 则染黑，$v->u$ 则染白。

那么如果有一个黑点到一个白点这么一条边的话，那么就找到一个三元环了。

如果没有，那么 $u$，白点，黑点之间必然不可能再产生三元环，那么再继续 dfs 白点，黑点，用 vector 存好后遍历方法同上。

可以发现因为所有边都只会被遍历一遍，因此时间复杂度是 $O(n^2)$ 的。同时也可以证明空间复杂度不超过 $O(n^2)$，因为每个点都只会存在于最多 $n$ 个 vector 中。

具体细节见代码吧。

```cpp

//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
//#define int long long
inline int read()
{
	int sum = 0, nega = 1;
	char ch = getchar();
	while (ch > '9'||ch < '0')
	{
	    if (ch == '-') nega = -1;
		ch = getchar();
	}
	while (ch <= '9'&&ch >= '0') sum = sum * 10 + ch - '0', ch = getchar ();
	return sum * nega;
}
const int N = 5009, M = 1e6 + 9;
//int a[N][N];
char s[N][N];	
int n, cnt;
vector<int> G[M];
inline void dfs(int col)
{
	int bla = cnt + 1, whi = cnt + 2; //给黑白分别编号 
	if(G[col].size() <= 1) return ; //若大小小于 1 则这个 vector 就没用了 
	for (int i = 1; i < G[col].size(); i++)
		if(s[G[col][0]][G[col][i]] == '1') G[bla].push_back(G[col][i]); //黑点 
		else G[whi].push_back(G[col][i]); // 白点 
	for (int i = 0; i < G[bla].size(); i++)
		for (int j = 0; j < G[whi].size(); j++)
			if(s[G[bla][i]][G[whi][j]] == '1') //有黑连向白 
			{
				printf("%d %d %d\n", G[col][0], G[bla][i], G[whi][j]); //找到一个答案 
				exit(0);
			}
	cnt += 2; //多了两块 
	dfs(bla);//遍历黑的 
	dfs(whi);//遍历白的 
	return ;
}
signed main()
{
	n = read();
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);//读入 
	cnt = 1;//给块编号 
	for (int i = 1; i <= n; i++) G[cnt].push_back(i); //初始化第一块	
	dfs(1);
	puts("-1");
	return 0;
}

```


---

## 作者：LanrTabe (赞：5)

欢迎来[博客](https://www.cnblogs.com/LanrTabe/p/10384524.html)玩啊~

~~首先作为一个没有图论常识的人，我完全不知道这题怎么用图论知识做~~

似乎这题$DFS$可过。。~~我就是饿死也不会用DFS~~

我们考虑最暴力的做法：枚举$3$个点判断是否形成环。

但是$O(n^3)$是肯定过不了的。

那么先枚举前$2$个点，就要判断第$2$个点出发有没有一个点和第$1$个点联通。

先预处理哪些点和第$1$个点联通，那么就是求第$2$个点能够到达的点集和能够到达第$1$个点的点集有没有交集。

这里用```bitset```优化即可。

时间复杂度 $O(\frac{n^3}{32})$

```bitset``` 要手写，$STL$的常数太大了。

代码：

```cpp
#include <cstdio>
#include <cstring>
typedef unsigned long long ull;

struct Bitset
{
    ull a[80];

    inline void Set(const int x){a[x>>6]|=1ull<<(x&63);}//将第x位设为1

    inline bool Get(const int x){return a[x>>6]>>(x&63)&1;}//获取第x位的值

    inline bool Match(const Bitset &b)//判断和b是否有交集
    {
        for(int i=0;i<80;++i)
            if(a[i]&b.a[i])return true;
        return false;
    }

    inline void Clear(){memset(a,0,sizeof a);}//清空
};

int n;
char s[5005];
Bitset g[5005],a;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",s+1);
        for(int j=1;j<=n;++j)
            if(s[j]&1)g[i].Set(j);
    }
    for(int i=1;i<=n;++i)
    {
        a.Clear();
        for(int j=1;j<=n;++j)
            if(g[j].Get(i))
                a.Set(j);
        for(int j=1;j<=n;++j)
            if(g[i].Get(j))
                if(g[j].Match(a))
                    for(int k=1;k<=n;++k)//有解，暴力找解。
                        if(g[j].Get(k)&&g[k].Get(i))
                            return printf("%d %d %d\n",i,j,k),0;
    }
    return puts("-1"),0;
}
```

---

## 作者：Loser_Syx (赞：3)

我是 naive 的小朋友。我会 $O(n^3)$ 做法！

我们不妨开两个数组 $a,b$，$a_{i,j}=1$ 表示存在 $i \rightarrow j$ 的路径，$b_{j,i} = 1$ 也表示存在一条 $i \rightarrow j$ 的路径。

然后考虑枚举三个数 $i,j,k$，显然这三个数要满足存在 $i \rightarrow j \rightarrow k \rightarrow i$ 的路径，我们可以表示为 $a_{i,j}=1,a_{j,k}=1,b_{i,k}=1$。

这个时候发现，我们枚举 $i,j$ 时，如果 $a_j$ 和 $b_i$ 存在交集，我们可以直接确定一个 $k$。

本来求交集是 $O(n)$ 的，但是如果我们使用 `bitset` 来存储 $a,b$ 的话，可以变成 $O(\frac{n}{\omega})$。

故复杂度为 $O(\frac{n^3}{\omega})$，`bitset` 常数大，去别的哥们题解里贺了一份。

```cpp
const int N = 5010;
struct Bitset {
	unsigned long long a[80];
	inline void Set(const int x) {
		a[x >> 6] |= 1ull << (x & 63);
	}
	inline bool Get(const int x) {
		return (a[x >> 6] >> (x & 63) & 1);
	}
	inline bool Match(const Bitset &b) {
		for (int i = 0; i < 80; ++i)
			if (a[i] & b.a[i]) return true;
		return false;
	}
	inline void Clear() {
		memset(a, 0, sizeof a);
	}
} a[N], b[N];
char Getchar() {
	char c = getchar();
	while (c != '0' && c != '1') c = getchar();
	return c;
}
signed main() {
	int n = read();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (Getchar() == '1') {
				a[i].Set(j); b[j].Set(i);
			}
		}
	}
	for (int i = n; i; --i) {
		for (int j = n; j; --j) {
			if (a[i].Get(j)) {
				if (a[j].Match(b[i])) {
					write(i, ' ');
					write(j, ' ');
					for (int k = 1; k <= n; ++k) if (a[j].Get(k) && b[i].Get(k)) return write(k, '\n'), 0;
				}
			}
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：2)

题解区唯一一个跟我同样做法的题解已经年久失修了，所以再来写一篇。

这篇题解主要证明若竞赛图中存在环，则一定存在三元环。

我们不妨设环上的点分别为 $a_1,a_2,\ldots,a_k$，其中 $a_i$ 向 $a_{i+1}$ 有一条边（对于 $a_k$ 它就和 $a_1$ 连边）。假设这些点中不存在一个包含 $a_1$ 三元环，那么因为 $a_1$ 向 $a_2$ 连边，$a_2$ 向 $a_3$ 连边，所以 $a_1$ 也会向 $a_3$ 连一条边。于是同理可知 $a_1$ 会向每一个 $a_i$ 连一条边，这和我们的假设 $a_k$ 向 $a_1$ 连边相矛盾。因此，一定存在一个包含 $a_1$ 的三元环。

所以跑一遍 tarjan 找个环然后随便从环里找一个点然后找三元环即可。时间复杂度 $O(n^2)$。

---

## 作者：PDAST (赞：1)

## 题意
给出一个邻接矩阵表示一个竞赛图，问是否存在三点环，若有，输出任意一个。
## 思路
三点环是什么？就是有三个点的环。找到三点环最好想的思路就是三重循环暴力枚举，但是经常打 CF 的童鞋们都知道，CF 老年机跑不了那么多，~~其实出题人本来就没想让你暴力~~，重新看一遍题，发现这是一张竞赛图，这我们带来了一条新思路。
## 关于竞赛图
简单来说，竞赛图是一个有向图，里面每两个点都有且仅有一条单向连接，当竞赛图中有环时，必有三点环，证明其他作者都有证，我就不废话了。
## 做法
我们将三个点分别命名为 $A$、$B$、$C$，$A$ 能到达 $B$，$B$ 能到达 $C$，$A$ 也能到达 $C$，这时，我们发现，$B$ 对于构成一个环来说是一个“废点”，这时，我们可以忽视 $B$，把这个点删掉，其他点也如此，由于竞赛图的特性，只要将点删到只剩三个，它们必定成环！！！所以，代码会写了吗？
## 代码
~~我知道你肯定不会，对吧。~~
~~~cpp
#include<bits/stdc++.h>
using namespace std;
char v[5001][5001];
int to[5001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>v[i]+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(v[i][j]=='1'&&(!to[i]||v[j][to[i]]=='1'))to[i]=j;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(v[j][i]=='1'&&v[to[i]][j]=='1'){
				cout<<i<<" "<<to[i]<<" "<<j;
				return 0;
			}
		}
	}
	cout<<-1;
}
~~~
## 总结
这道题的代码倒是挺简单的，主要就是思路难想，评蓝也不是没道理的，总之，学信息一定要多练多思考。

---

## 作者：寒冰大大 (赞：1)

其实之前学过竞赛图的，都应该知道一个定理，就是一个竞赛图存在环的话，那么一定又一个长度为$3$的环

证明也好证明，环上连续的$a,b,c$三个点，$AC$的长度要么是1（此时可以把b忽略）要么是2（此时存在环）

然后有一篇题解是找到一个环然后缩成长度为$3$的环的，然而我tarjan写炸了，于是直接找长度为3的环

怎么找呢，dfs记录当前点，父节点，子节点，如果他们三个构成了环，那么就能够输出答案了。

不过还要注意直接暴力肯定是不行的，我们发现会出现$abc$与$cba$这种等价的情况（它们都不是答案），也就是说我们重复了，所以我们要标记扫过的点，复杂度就变成了$O(N^2)$

另外注意一下读入，有可能会T也有可能会因为没关同步炸

```cpp
#include<touwenjian.h>

using namespace std;

const int maxn=5050;

bool f[maxn][maxn];
int n,m,vis[maxn];
int size;
int sz[maxn],p[maxn],looker,bj;
char c[maxn];

void dfs(int t,int fat)
{
	if(bj) return ; 
	int i,j;
	vis[t]=1;
	for(i=1;i<=n;i++)
	if(f[t][i]){
		j=i;
		if(!bj&&f[j][fat])
		{
			cout<<fat<<" "<<t<<" "<<j;
			bj=1;
			return ;
		}
		if(!vis[j]) dfs(j,t);
	}
 } 

int main()
{
	register int i,j;
	cin>>n;
	char t;
	for(i=1;i<=n;i++)
	{
		scanf("%s",c+1);
		for(j=1;j<=n;j++)
		{
		if(c[j]=='1') f[i][j]=1;
		}
	}
	for(i=1;i<=n;i++)
	if(!vis[i]) dfs(i,0);
	if(!bj) cout<<-1;
	return 0;

}
```


---

## 作者：ZM____ML (赞：1)

## 简化题意

在一张**有向完全图**中，找到任意一个三元环。

## 分析

首先，我们考虑在图中找出任意三个点，那么这个时候，会有两种情况：

1. 这三个点构成一个环；

![](https://cdn.luogu.com.cn/upload/image_hosting/i8s3gk8l.png)

1. 这三个点之间不构成环。

![](https://cdn.luogu.com.cn/upload/image_hosting/fvk2f3hc.png)

如果是第一种情况符合条件，不进行考虑。而对于第二种来说，如果不构成环,则如果这张图上可以找到另外一个三元环，使其与刚才这三个点形成如下关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/7eg6c7rs.png)

那么，从点 $x$ 到点 $k$ 之间一定存在一条边，不论是从 $x$ 连向 $k$ 还是从 $k$ 连向 $x$，都可以与另外两个点中的一个点形成一个三元环。所以从 $z$ 连向 $y$ 的这条边是无用的，可以删去。

即对于每一个这种结构的三个点，都可以删掉一条如图所示的这一条边，那么易证：最后每个点只用保留一个出边，那么只需要暴力枚举两个点，判断这两个点以及其中一点出边所连接的点与这两个点是否形成环即可。

时间复杂度 $O(n^2)$，可以通过本题。

##  $\huge\text{code}$ 

```cpp
#include<cstdio>
using namespace std;
const int N=5005;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,to[N];
char a[N][N];
int main(){
	n=read();
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]==49&&(!to[i]||a[j][to[i]]==49))to[i]=j;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[to[i]][j]==49&&a[j][i]==49)
				return printf("%d %d %d",i,to[i],j)&0;
	printf("-1");
	return 0;
}
```


---

## 作者：TimSwn090306 (赞：0)

提供一种除去读入后 $O(n)$ 的做法。

## 1.题意简述

> 给定 $n$ 个点的竞赛图，找出其中一个三元环或判定无解。 
>
> $n\le 5\times 10^3$。

## 2.解题分析

套路的，考虑竞赛图中出度最大的点，设其为 $X$。

可以发现，如果有点 $Y\rightarrow X$，则必然有三元环 $Y\rightarrow X \rightarrow Z \rightarrow Y$。

证明：若不存在这样的点 $Z$，那么 $Y$ 出度必然大于 $X$ 的出度，与定义相悖。

每次找出度最大的点，如果其入度为 $0$，再找出度第二大的点，一直重复直到入度不为 $0$，时间复杂度 $O(n)$。

总时间复杂度 $O(n^2)$，瓶颈在于输入。

## 3.代码实现


```cpp
#include <bits/stdc++.h>
#define fin(str) freopen(str,"r",stdin)
#define fout(str) freopen(str,"w",stdout)
#define ll long long
using namespace std;

bool MEM_beg;

const int maxn=5e3+5;

int n;
struct node{
	int out,id;
	inline bool operator < (node tmp) const{
		if (out!=tmp.out) return out>tmp.out;
		return id<tmp.id;
	}
}a[maxn];
char ch[maxn][maxn];

bool MEM_end;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%s",ch[i]+1);
		for (int j=1;j<=n;j++){
			if (ch[i][j]=='1') a[i].out++;
		}
		a[i].id=i;
	}
	sort(a+1,a+n+1);// 可以桶排，懒得改了
	for (int i=1;i<=n;i++){
		if (a[i].out==n-i) continue;
		int pos=0;
		for (int j=i+1;j<=n;j++){
			if (ch[a[j].id][a[i].id]=='1'){
				pos=a[j].id;
				break;
			}
		}
		assert(pos);
		for (int j=i+1;j<=n;j++){
			if (ch[a[i].id][a[j].id]=='1' && ch[a[j].id][pos]=='1'){
				printf("%d %d %d\n",a[i].id,a[j].id,pos);
				return 0;
			}
		}
	}
	printf("-1\n");
	
	cerr<<"\nMemory : "<<1.0*abs(&MEM_end-&MEM_beg)/1048576<<" MB\n";
	return 0;
}


```

---

## 作者：Priestess_SLG (赞：0)

首先有一个简单的 $O(n^3)$ 做法是暴力枚举每一条边，考虑优化，枚举两个点之后求她们可以共同到达的点的并集，使用 `bitset` 维护可以做到 $O(\frac{n^3}{\omega})$，经过大力卡常后可过。

但是因为卡常是只有 [aimat](/user/746544) 姐姐才会做的事，所以考虑观察图的性质！

> 一个 $\texttt{tournament}$ 是一个没有自环的有向图，同时，每两个点之间有一条边连接。这就是说，对于两个点 $u,v (u\neq v)$，有一条从 $u$ 到 $v$ 的边或一条从 $v$ 到 $u$ 的边。

图中任意两点之间都恰好有一条有向边相连。

于是挖掘性质！经过手玩之后可以发现下面的结论：

> 一个竞赛图要么不存在环 $^1$，要么一定存在至少一个三元环 $^2$。

考虑将两个部分分别证明。

$(1)$：竞赛图可以不存在环。例如构造下面的竞赛图：

[![pAaeMfP.png](https://s21.ax1x.com/2024/10/20/pAaeMfP.png)](https://imgse.com/i/pAaeMfP)

真的没有环。此时显然更不可能有三元环。

$(2)$：考虑一个 $n$ 个点的竞赛图中存在一个大小为 $k$ 的环，点的编号分别为 $p_1,p_2,\ldots,p_k$，其中 $p_i\to p_{i+1}$（$i\in[1,k)\cup\mathbb{N_+}$），$p_k\to p_1$ 分别有恰好一条有向边。则为了让图中不含有任何三元环，此时 $a_1\to a_2$，$a_2\to a_3$ 都有边，则 $a_1\to a_3$ 也必须有边，否则若 $a_3\to a_1$ 有边，则图中 $1,2,3$ 三个点就形成了一个三元环。以此类推，$a_1\to a_3$ 有边，$a_3\to a_4$ 有边，则 $a_1\to a_4$ 也必须有边……最终 $a_1\to a_k$ 有边，但是因为 $a_k\to a_1$ 已经有边，因此和假设不符，产生矛盾。

于是证明任意一张有环的竞赛图都存在至少一个三元环。

考虑在图上 dfs，每一次记录当前点和当前点的父亲结点。若当前点的儿子结点不为父亲结点，且儿子结点可以到达父亲结点，则找到了一个三元环。时间复杂度为 $O(n^2)$ 可以通过。

代码很简短。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N=200100;
int n,vis[5010];char s[5010][5010];
int dfs(int u,int fa){
    vis[u]=1;for(int i=1;i<=n;++i)if(s[u][i]=='1'){
    !vis[i]&&dfs(i,u);if(s[i][fa]=='1'){cout<<fa<<' '<<u<<' '<<i<<'\n';exit(0);}}
    return 1;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i)scanf("%s",s[i]+1);
    for(int i=1;i<=n;++i)!vis[i]&&dfs(i,i);cout<<"-1\n";
}
```

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

本题比较简单，我们首先要知道两个概念：一个是竞赛图也叫有向完全图。**每对顶点之间都有一条边相连的有向图称为竞赛图**，就像这个题目。第二点是竞赛图**没有自环，没有二元环**（这样的话我们可以减少很多时间复杂度）；若竞赛图存在环，**则一定存在三元环**，如果存在一个环大于三元，那么一定存在另一个三元的小环。

我们再来看这道题，因为竞赛图（有向完全图）如果存在环的话就一定存在三元环，所以我们就可以直接暴力，如果 $x$ 到 $y$，$y$ 能到 $x$ 的父节点，那么父节点，$x$，$y$ 三个点就形成了一个三元环，找到后直接退出，结束程序。

最后，由于本题 $n$ 最大有 $5000$，所以，在输入各点之间的关系时要考虑更高效的输入方式。

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
#define int long long
char mapp[5009][5009];
int n, m;
bool vis[10000009];
bool dfs(int x, int fa)
{
    vis[x] = 1;
    for (int y = 1; y <= n; y++)
    {
        // cout << "x=" << x << "  " << "y=" << y << endl;
        if (mapp[x][y] == '1')
        {
            if (!vis[y])
            {
                if (dfs(y, x))
                {
                    return true;
                }
            }
            if (mapp[y][fa] == '1')
            {
                cout << fa << ' ' << x << ' ' << y << endl;
                return true;
            }
        }
    }
    return false;
}
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mapp[i] + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            if (dfs(i, i))
            {
                // cout << "ouye!" << endl;
                return 0;
            }
        }
    }
    cout << -1;
    return 0;
}

```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18322815)

# 思路

发现最简单的方法就是直接枚举三个点，但是复杂度 $\Theta(n^3)$ 无法接受。

考虑枚举一个点，并确定它的一条边，那么只需要再枚举一个点了。于是转化为了，对于每一个点找到其最好的出边。

观察下图，$a \to c$ 的边是不必要的。因为，如果有一个三元环包含 $a \to c$，那么一定能找到一个不包含 $a \to c$ 的一条边。

![](https://s21.ax1x.com/2024/07/25/pkbuCy6.png)

那么，把这种边全部删除，每一个点都将只剩下一条出边，然后枚举另一个点即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 5010;
int n,to[N];
char arr[N][N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

int main(){
    n = read();
    for (re int i = 1;i <= n;i++) scanf("%s",arr[i] + 1);
    for (re int i = 1;i <= n;i++){
        for (re int j = 1;j <= n;j++){
            if (arr[i][j] == '1' && (!to[i] || arr[j][to[i]] == '1')) to[i] = j;
        }
    }
    for (re int i = 1;i <= n;i++){
        for (re int j = 1;j <= n;j++){
            if (arr[to[i]][j] == '1' && arr[j][i] == '1') return printf("%d %d %d",i,to[i],j),0;
        }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
题目中出现了一个词：tournament。这词的意思是竞赛图。但我也不会，所以我就想成了一个有向图。题意大概是让你在一个有向图中找一个三元环。

画图推理一下：
![画的有点简陋啊](https://cdn.luogu.com.cn/upload/image_hosting/g9777gsv.png)
C 到 B 的边是一定没用的，因为不论箭头指向 C 还是 B 都可以和另一个点构成三元环。

得出结论后，我们可以删掉若干个这种边后，每个点只会有一个出度，暴力枚举即可。

## 代码
注意：如果你用的是 cin 和 cout，一定要禁用缓存，否则会超时。我比赛的时候就出现了这种情况。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,tou[N];
char a[N][N];
int main(){
    ios::sync_with_stdio(false);
cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
		    if(a[i][j]==49&&(tou[i]==0||a[j][tou[i]]==49)) tou[i]=j;
        }
    }
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[tou[i]][j]==49&&a[j][i]==49){
				cout<<i<<" "<<tou[i]<<" "<<j;return 0;
            }
        }
    }
	cout<<-1;
	return 0;
}
```

---

## 作者：小菜鸟 (赞：0)

有人说这题纯$dfs$可过？实测会$WA/TLE$。。。

然后尝试一下改成$bfs$，还是$WA$了QwQ

显然两种做法都有人hack了。（此题$O(n)$解法都是错的）

那么我们把两种方法一起跑一遍。

A了？？？WTF

简单说一下做法。

用$dfs$和$bfs$分别求生成树。如果中途发现一个点与它的爷爷有边，直接输出并`exit(0)`。。。

然后如果还担心被hack可以随机一下边表。

考试的时候这题要卡常，所以用二维数组前向星了。

```cpp
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
char gc()
{
    static char buf[1<<18],*p1=buf,*p2=buf;
    if(p1==p2)
    {
        p2=(p1=buf)+fread(buf,1,1<<18,stdin);
        if(p1==p2)
        {
            return EOF;
        }
    }
    return *p1++;
}
//#define gc getchar
template<typename _Tp>
void read(_Tp& x)
{
    x=0;
    char c=gc();
    while(c<'0'||c>'9')c=gc();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
}
int n;
bool vis[5005];
short G[5005][5005];
short tot[5005];
short fa[5005];
short top=2;
void dfs(int u)
{
    if(vis[u])return;
    vis[u]=1;
    for(int i=0;i<tot[u];++i)
    {
        int v=G[u][i];
        if(vis[v])
        {
            if(fa[fa[u]]==v)
            {
                printf("%d %d %d",fa[fa[u]],fa[u],u);
                exit(0);
            }
            continue;
        }
        fa[v]=u;
        dfs(v);
    }
}
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        for(int i=0;i<tot[u];++i)
        {
            int v=G[u][i];
            if(vis[v])
            {
                if(fa[fa[u]]==v)
                {
                    printf("%d %d %d",fa[fa[u]],fa[u],u);
                    exit(0);
                }
                continue;
            }
            fa[v]=u;
            vis[v]=1;
            q.push(v);
        }
        q.pop();
    }
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            char c=gc();
            while(c!='0'&&c!='1')c=gc();
            if(c&1)
            {
                G[i][tot[i]++]=j;
            }
        }
    }
    for(int i=1;i<=n;++i)dfs(i);
    for(int i=1;i<=n;++i)vis[i]=0;
    for(int i=1;i<=n;++i)bfs(i);
    puts("-1");
}
```

此方法适用于任意图，当心被卡就是了。。。

---

