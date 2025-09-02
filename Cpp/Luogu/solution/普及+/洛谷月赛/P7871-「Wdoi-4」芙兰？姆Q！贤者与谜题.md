# 「Wdoi-4」芙兰？姆Q！贤者与谜题

## 题目背景

题目背景不包含解题的关键信息，可以跳过。

---

芙兰朵露·斯卡蕾特是曾居住在红魔馆地下室的吸血鬼。与众不同的是，芙兰朵露有着彩色结晶的特殊翅膀，与其他吸血鬼蝙蝠一般的翅膀不同：颜色各异的结晶按照顺序一字排开。

芙兰朵露翅膀的彩色结晶的颜色从内到外分别是天蓝、蓝、紫、粉、橙、黄、淡绿和天蓝。因此事实上，芙兰朵露的翅膀很可能就是帕秋莉的「贤者之石」组成的。

但是芙兰朵露并不关心这些，她只关心排列成翅膀形状的贤者之石之间发生的能量流动——如果一块贤者之石被赋予了能量，就会处于激发态。处于激发态的贤者之石很不稳定——它大量能量的爆发会波及周围的贤者之石，以造成能量的转移。

芙兰朵露非常感兴趣，并以此出了一个谜题来考考帕秋莉。但是作为贤者的帕秋莉不想思考只想摸鱼，于是任务就交给你啦！![](https://www.luogu.com.cn/paste/tkub6dq3)

## 题目描述

芙兰朵露从帕秋莉那里搞来了 $n$ 块贤者之石，并从左往右排成了一列。帕秋莉可以赋予每块贤者之石一定的能级，这会决定贤者之石之间能量的传递。值得注意的是，**能级必须要是正整数，并且不能有两块贤者之石能级相同**。

如果第 $i$ 块贤者之石被赋予了能量（处于激发态），它就会将能量传递给第 $i-1$ 和第 $i+1$ 块里**能级较小**的那一块。特别地，如果某块贤者之石周围只有一块，那么它只会向这一块发送能量。注意，即使第 $i$ 块的能级低于第 $i-1$ 和第 $i+1$ 块，它**照样可以传输能量**。

现在芙兰有 $q$ 个条件——每个条件给定两个正整数 $s,t$，表示如果芙兰激活了第 $s$ 块贤者之石的能量，那么能量最终会经过第 $t$ 块。

然而由于帕秋莉有哮喘的老毛病，设定贤者之石的能级是很费力的。因此，如果存在一种合法的赋予贤者之石能级的方案，请你找出其中**字典序最小**的那个方案。对于两种方案 $A,B$，我们称 $A$ 的字典序小于 $B$，当且仅当存在一个 $p$，使得 $\forall i<p$ 有 $A_i=B_i$，且 $A_p<B_p$。 

如果存在合法方案，请你输出字典序最小的方案；否则输出 `QED`。

## 说明/提示

输入/输出样例 $2$ 见下发的附件 $\textbf{\textit{qed2.in}/\textit{qed2.out}}$。

输入/输出样例 $3$ 见下发的附件 $\textbf{\textit{qed3.in}/\textit{qed3.out}}$。

---

### 数据范围及约定

对于 $100\%$ 的数据，$0\le q \le 3\times 10^5$，$3\le n \le 3\times 10^5$，$1\le s_i,t_i \le n$。

$$
\def{\arraystretch}{1.5}
\begin{array}{|c|c|c|c|} \hline
\textbf{测试点} & \bm{n\le} & \bm{q\le} & \textbf{特殊限制} \cr \hline
1\sim 3 & 7 & 7 & - \cr \hline
4\sim6 & 100 & 100 & - \cr \hline
7 & 10^5 & 1 & -\cr \hline
8\sim 10 & 3\times 10^5 & 3\times 10^5 & s_i\le t_i \cr \hline
11\sim 12 & 10^5 & 10 & - \cr \hline
13\sim 20 & 3\times 10^5 & 3\times 10^5 & -\cr \hline
\end{array}$$


## 样例 #1

### 输入

```
10 4
1 2
3 7
8 10
5 6```

### 输出

```
1 4 8 3 7 2 6 10 5 9```

# 题解

## 作者：囧仙 (赞：17)

### 题解

[简化题面](https://www.luogu.com.cn/paste/6exb0i75)

根据题意，在第 $i$ 块贤者之石里的能量若会向左传递，当且仅当 $w_{i-1}<w_{i+1}$，因此我们从 $i+1$ 向 $i-1$ 连边；若会向右传递，当且仅当 $w_{i-1}>w_{i+1}$，因此我们从 $i-1$ 向 $i+1$ 连边。

可以发现，最终连出来的边里，只会是奇数编号的点连向奇数编号的点、偶数编号的点连向偶数编号的点。考虑分为奇偶两块来考虑。又能发现，单独抽出奇数/偶数的节点，那么这些边连出来的必然是链的形状。

$$
\boxed{1} \leftarrow
\boxed{2} \phantom{\leftrightarrow}
\boxed{3} \rightarrow
\boxed{4} \leftarrow
\boxed{5} \leftrightarrows
\boxed{6}
$$

对于这张图，可以发现由于 $w_5>w_6,w_6>w_5$ 产生了矛盾，因此必然无解。

那么考虑，如果一张图有解，我们怎么确定它的最小字典序呢？

使用贪心。从左往右考虑每个点能被标注的最小的值。使用 $\mathit{cnt}$ 表示当前标注了编号的点的数目（下文构造方案可以证明，此时 $1\sim \mathit{cnt}$ 的标号都被用过了）。但是可能出现如下状况：

$$
\boxed{1} \rightarrow
\boxed{2} \rightarrow
\boxed{3} \leftarrow
\boxed{4}
$$

如果我们把 $1$ 标为 $\mathit{cnt}+1$ ，那么点 $2$ 和点 $3$ 就没办法标了。因此，我们应该把 $3$ 标为 $\mathit{cnt}+1$，把 $2$ 标为 $\mathit{cnt}+2$，最后把 $1$ 标为 $\mathit{cnt}+3$。容易发现，不存在一种更好的方案使得 $1$ 标到的数字更小了。然后更新 $\mathit{cnt}$。

因为有两条链，所以处理完一条链后记得转换到另外一条链上。如果一个点已经被标号了，那就直接跳过。

---

然后我们要做的就是对于每个条件，将对应的点连边。首先我们肯定得按照奇偶分开。

$$
\boxed{2} \phantom{\leftrightarrow}
\boxed{4} \phantom{\leftrightarrow}
\boxed{6} \phantom{\leftrightarrow}
\boxed{8}
\\[1em]
\boxed{1} \phantom{\leftrightarrow}
\boxed{3} \phantom{\leftrightarrow}
\boxed{5} \phantom{\leftrightarrow}
\boxed{7} \phantom{\leftrightarrow}
\boxed{9}
$$

使用数组 $A,B$，若 $A_i=\verb!true!$ 则表示链上 $i$ 到 $i+2$ 有一条边；同样地，若 $B_i=\verb!true!$ 则表示链上 $i+2$ 到 $i$ 有一条边。

以该图举例。假设有个条件 $\{s=3,t=6\}$，应该连的边为：

$$
\boxed{2} \rightarrow
\boxed{4} \rightarrow
\boxed{6} \phantom{\leftrightarrow}
\boxed{8}
\\[1em]
\boxed{1} \phantom{\leftrightarrow}
\boxed{3} \rightarrow
\boxed{5} \phantom{\leftrightarrow}
\boxed{7} \phantom{\leftrightarrow}
\boxed{9}
$$

其中，$A_2,A_3,A_4$ 应当被赋值为 $\verb!true!$。容易证明，需要赋值的部分的下标，应当为 $s-1,s,\cdots,t-2$。

假设有个条件 $\{s=7,t=2\}$，应该连的边为：

$$
\boxed{2} \leftarrow
\boxed{4} \leftarrow
\boxed{6} \leftarrow
\boxed{8}
\\[1em]
\boxed{1} \phantom{\leftrightarrow}
\boxed{3} \leftarrow
\boxed{5} \leftarrow
\boxed{7} \phantom{\leftrightarrow}
\boxed{9}
$$

其中，$B_2,B_3,B_4,B_5,B_6$ 应当被赋值为 $\verb!true!$。容易证明，需要赋值的部分的下标，应当为 $t,t+1,\cdots,s-1$。

考虑使用差分数组进行区间赋值为 $\verb!true!$。如果我们要对某个数组 $X$ 的 $[l,r]$ 段区间赋值为 $\verb!true!$，可以先维护它的差分数组 $X'$，让 $X'_l\gets X'_l+1,X'_{r-1}\gets X'_{r-1}-1$。然后对它求前缀和，就能求出 $X$ 数组。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =1e5+3;
int n,t,q,A[MAXN],B[MAXN],N[MAXN]; bool f;
int main(){
    up(1,qread(),T){
        n=qread(),q=qread(),f=false,t=0;
        memset(A,0,sizeof(int)*(n+1));
        memset(B,0,sizeof(int)*(n+1));
        memset(N,0,sizeof(int)*(n+1));
        up(1,q,i){
            int s=qread(),t=qread();
            if(s<t) ++A[s-1],--A[t-1]; else if(s>t) ++B[t],--B[s];
        }
        up(1,n,i) A[i]+=A[i-1],B[i]+=B[i-1];
        up(1,n-2,i) if(A[i]&&B[i]) f=true;
        if(f){puts("QED");continue;}
        up(1,n,i) if(!N[i]){
            int c=1; for(int j=i;A[j]&&j+2<=n;j+=2) ++c;
            up(1,c,j) N[i+2*c-2*j]=++t;
        }
        up(1,n,i) printf("%d%c",N[i],i==n?'\n':' '); 
    }
    return 0;
}
```

---

## 作者：C_liar (赞：8)

### 题目描述

[简化题面](https://www.luogu.com.cn/paste/6exb0i75)

---

### 题解

提供一种和大家不太一样的，贪心+并查集优化的思路。

假设我们构造的数列为 $c$。

对于题目中每个给出的条件 $s_i$ 和 $t_i$，相当于要求：

- 若 $s_i<t_i$，则 $\forall j\in[s_i,t_i-1]$ 都满足：$c_{j-1}>c_{j+1}$。
- 若 $s_i>t_i$，则 $\forall j\in[t_i+1,s_i]$ 都满足：$c_{j+1}>c_{j-1}$。

首先，我们可以考虑拓扑排序，对每组 $c_i>c_j$，从 $i$ 向 $j$ 连边。

先将所有边暴力建完，然后一遍拓扑排序判断是否有环，有环说明存在矛盾，无解。

判断完之后，此时的图变成了许多条链，再按照贪心的思路，依次从结点 $1$ 到 $n$ 对没有确定 $c_i$ 的结点进行 $\text{dfs}$，一直到最深层，然后在回溯的过程中倒序为途径的 $c_i$ 赋值。

这样做可以保证构造的正确性和最优性，在回溯的过程中倒序赋值可以保证 $c_i>c_j$，使构造一定正确。

而最优性，我们容易发现，图中的每个结点出度最多是 $1$，$\text{dfs}$ 的过程中不会出现奇怪的分支，而结点可以有多个入度，按照编号从小到大 $\text{dfs}$ ，可以保证字典序最小。

---

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
typedef long long ll;
const int _=3e5+10;
using namespace std;

int n;

struct Edge{
	int head[_],next[_*10],to[_*10],t,ind[_];
	void add(int u,int v){
		to[++t]=v,next[t]=head[u],head[u]=t,ind[v]++;
	}
}e;

int cpy[_];

bool toposort(){
	queue<int> q;
	int cnt=0;
	for(int i=1;i<=n;i++) if(e.ind[i]==0) q.push(i),cnt++;
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=e.head[u],y;i;i=e.next[i]){
			if(e.ind[(y=e.to[i])]==0) continue;
			e.ind[y]--;
			if(!e.ind[y]) q.push(y),cnt++;
		}
	}
	return cnt==n;
}

int tot,dfn[_];

void dfs(int x){
	for(int i=e.head[x],y;i;i=e.next[i]){
		if(dfn[y=e.to[i]]) continue;
		dfs(y);
	}
	dfn[x]=++tot;
}

int main(){
	int q;scanf("%d%d",&n,&q);
	for(int i=1,s,t;i<=q;i++){
		scanf("%d%d",&s,&t);
        // 这里是建图过程
		if(s==t) continue;
		if(s<t){
        // 暴力建边
			for(int j=s;j!=t;j++){
				if(j-1==0) continue;
				e.add(j-1,j+1);
			}
		}else{
			for(int j=s;j!=t;j--){
				if(j==n) continue;
				e.add(j+1,j-1);
			}
		}
	}
    // 拓扑排序，判断无解
	if(!toposort()) return puts("QED"),0;
	for(int i=1;i<=n;i++){
    // dfs+贪心
		if(!dfn[i]) dfs(i);
	}
	for(int i=1;i<=n;i++) printf("%d%c",dfn[i]," \n"[i==n]);
	return 0;
}

```

但很遗憾，这样的程序交上去只有 $45$ 分，原因是 $\text{Subtask\#4}$ 和 $\text{Subtask\#6}$ 的条件个数太多了，达到 $3\times 10^5$ 的规模，暴力建图还没等到超时就已经爆空间了，考虑优化建图的过程。

---

### 优化

容易发现，每个 $s_i$ 到 $t_i$ 间有许多重复的段，如果去掉这些重复的段，边的规模只有 $O(n)$，大大降低了复杂度。

那只需要判断 $s_i$ 到 $t_i$ 中有哪些建过边的段，跳过这些片段即可。

这样，我们可以想到并查集优化，令结点 $i$ 指向 $i$ 后面第一个没有建过边的结点。

具体地，在每个 $i\in[1,n]$ 处建立并查集，初始 $f_i=i$。

对于每个条件 $s_i$ 和 $t_i$，先考虑 $s_i<t_i$ 的情况，对于这种情况，遍历 $j\in[s_i,t_i-1]$，分两种情况。

- 如果 $f_j=j$，则从 $j-1$ 向 $j+1$ 建边，同时令 $f_j=j+1$，$j=get(j)$。
- 如果 $f_j\not=j$，则直接令 $j=get(j)$。

至于 $s_i>t_i$ 的情况，也是类似上面。

由于使用并查集，我们可以在输入条件过程中判断无解，这样省去了拓扑排序的过程，最后一遍 $\text{dfs}$ 就可以解决问题。

具体实现详见代码。

---

### 代码

下面是满分代码。

```cpp
#include<cstdio>
const int _=3e5+10;

int n;

class FindUnionSet{
	int f[_];
public:
	FindUnionSet(){}
	FindUnionSet(int x){for(int i=1;i<=x;i++) f[i]=i;}
	int getf(int x){return x==f[x]?x:f[x]=getf(f[x]);}
	void mergef(int x,int y){f[getf(x)]=getf(y);}
};

struct Edge{
	int head[_],next[_],to[_],t;
	void add(int u,int v){
		to[++t]=v,next[t]=head[u],head[u]=t;
	}
}e;

int tot,dfn[_];

void dfs(int x){
	for(int i=e.head[x],y;i;i=e.next[i]){
		if(dfn[y=e.to[i]]) continue;
		dfs(y);
	}
	dfn[x]=++tot;
}

int main(){
	int q;scanf("%d%d",&n,&q);
	// 这里建了两个并查集，d1存s<t的情况，d2存s>t的情况
	FindUnionSet d1(n),d2(n);
	for(int i=1,s,t;i<=q;i++){
		scanf("%d%d",&s,&t);
		if(s==t) continue;
		if(s<t){
			for(int j=s;j<t;){
				// 注意边界 
				if(j-1==0){j++;continue;} 
				if(d2.getf(j)!=d2.getf(j-1)){
				// 这里是有解的情况 
					if(d1.getf(j)==j){
						// j-1到j+1没有建过边 
						e.add(j-1,j+1);
						d1.mergef(j,j+1);
						j=d1.getf(j);
					}else{
						// 已经建过边，调到下一个没有建过边的j 
						j=d1.getf(j);
					}
				// 如果j和j-1已经在s>t的情况里被建边，说明矛盾，无解
				}else return puts("QED"),0;
			}
		}else{
			// 与上面同理 
			for(int j=s;j>t;){
				if(j==n){j--;continue;}
				if(d1.getf(j)!=d1.getf(j+1)){
					if(d2.getf(j)==j){
						e.add(j+1,j-1);
						d2.mergef(j,j-1);
						j=d2.getf(j);
					}else{
						j=d2.getf(j);
					}
				}else return puts("QED"),0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) dfs(i);
	}
	for(int i=1;i<=n;i++) printf("%d%c",dfn[i]," \n"[i==n]);
	return 0;
}

```
---

### 时间复杂度

并查集使用了路径压缩，没有使用按秩合并，$\text{Trajan}$ 教授证明过，复杂度上界为 $O(n\log n)$。

这样建图建出来的边，由于去掉重复的情况，复杂度为 $O(n)$。

使用 $\text{dfs}$ 遍历所有点，复杂度为 $O(n)$。

故程序总时间复杂度为 $O(n\log n)$，空间复杂度 $O(n)$，可以通过本题。

---

觉得题解有帮助的可以点个赞哦！

---

## 作者：言琢დ (赞：7)

考虑一种线性模拟的思路：

- 第 $a$ 块能传递到第 $b(>a)$ 块，就说明了一个关系：
  - 第 $a-1$ 块 $>$ 第 $a+1$ 块
  - 第 $a$ 块 $>$ 第 $a+2$ 块
  - 第 $a+1$ 块 $>$ 第 $a+3$ 块
  - $\dots$
  - 第 $b-2$ 块 $>$ 第 $b$ 块
  
当 $b<a$ 时同理可得。实际上我们发现，不需要真的把 $O(\sum |s_i-t_i|)$ 个关系全部存下来。

因为有用的关系其实只有 $O(n)$ 个。

本代码中的思路考虑使用一个差分数组来压缩这些信息，并在最后一次性把处理出来。

另外同时使用一个 dfs 的过程，来遍历一下看看有没有矛盾的即可。

详见代码及其注释。

```cpp
#include<cstdio>
inline int in();
inline void wr(int);
const int N=(int)3e5+5;
int a[N],b[N],du[N];
struct Node{
	int next,to;
}s[N<<1];int head[N],sLen;
inline void AddEdge(int,int);
int val[N];bool vis[N];
inline void dfs(int);
inline int mx(int,int);
int main(int argc,char**argv){
#ifndef ONLINE_JUDGE
	freopen("qed.in","r",stdin);
	freopen("qed.out","w",stdout);
#endif
	register int n=in(),q=in();
	for(register int i=1;i<=q;++i){
		register int s=in(),t=in();
		if(s==t)continue;
		if(s<t)++a[s],--a[t];
		else ++b[s],--b[t];
	} // 简单的差分
	for(register int i=1;i<=n;++i)
		a[i]+=a[i-1]; // 还原
	for(register int i=n;i>=1;--i)
		b[i]+=b[i+1]; // 还原
	for(register int i=2;i<n;++i)
		if(a[i]>0)
			AddEdge(i-1,i+1); // 建图求解，但与朴素的差分约束有不同，真正意义上的差分约束考虑了任意连边，但是我们这里只有一个链上的情况
	// p[i-1] > p[i+1]
	for(register int i=2;i<n;++i)
		if(b[i]>0)
			AddEdge(i+1,i-1); // 倒着也要连边
	// p[i+1] > p[i-1]
	for(register int i=1;i<=n;++i)
		dfs(i);
	if(val[0]<n)puts("QED"); // 最后找到了环，就无解
	else{
		for(register int i=1;i<=n;++i)
			wr(val[i]),putchar(' '); // 否则就输出方案即可
	}
}
inline void dfs(int u){
	if(vis[u])return;
	vis[u]=1;
	for(register int i=head[u];i;i=s[i].next){
		register int v=s[i].to;
		dfs(v);
		if(!val[v])return;
	}
	val[u]=++val[0];
}
inline int mx(int x,int y){
	return x>y?x:y;
}
inline void AddEdge(int u,int v){
	++du[v];
	s[++sLen].next=head[u];
	s[sLen].to=v;
	head[u]=sLen;
}
inline int in(){
	register char c=getchar();
	register int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	return x*f;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)wr(x/10);
	putchar(x%10+'0');
}
```

---

## 作者：Hanx16Kira (赞：6)

# 「Wdoi-4」芙兰的贤者时间

[Luogu P7871](https://www.luogu.com.cn/problem/P7871)

一道很有意思的题目。

题目中有说到：能量只会往左右两边更低的一侧流动，这也就意味着，给出 $s,t$， 我们就可以得到一连串的数的大小关系。

先手玩一下样例，会发现：

- $s=1,t=2$ 这一组没有作用，因为 $1$ 只会流向 $2$。

- $s=3,t=7 \rightarrow a_3 > a_5 > a_7, a_2 > a_4 > a_6$。

- $s=8,t=10 \rightarrow a_7 > a_9, a_8 > a_{10}$。

- $s=5,t=6 \rightarrow a_4 > a_6$。

这样模拟一下，感觉就差不多找到规律了。

首先，大小关系一定是奇数和奇数，偶数和偶数之间的（这点很好说明，因为每次能量的流向是由左右两个位置的值决定的，也就是说每次的大小关系是两个间隔 $1$ 的数形成的）。

其次，会发现当 $s<t$ 时，形成大小关系的数的区间是 $[s-1,t]$ 的（需要注意的是，题目中说到的 $t$ 是经过而不是终点）。类似的，也可以推出 $s>t$ 的方式形成大小关系的数的区间是 $[s,t+1]$。

现在，得到了大小关系，该如何转换一下变得好给出方案呢？选择对于每一组大小关系，从大数向小数连一条边，那么在最后给出方案的时候就可以用类似拓扑排序的方式给出。

但是很快遇到了一个问题，如果对于每一组 $s,t$ 都需要暴力枚举连边的话，时间复杂度是 $\mathcal O(qn)$ 的，显然是过不了 $3\times 10^5$ 的数据量的。不过可以发现，这种连边方式很像是一种区间操作，那么就可以尝试将每一组操作变成区间操作。

考虑定义 $A[i]$ 表示 $i$ 向 $i+2$ 有连边，那么对于 $s,t$ 这一组操作就可以转化为区间 $[s-1,t-2]$ 的区间赋 $1$。因为不会出现 $-1$ 的情况，所以可以用差分维护区间加的方式优化。也就是说，对于一组操作 $s,t$，只需要 $A[s-1]+1,A[t-1]+1$ 即可。类比着，可以推导出 $s>t$ 的情况。

对于无解的情况，就是有两个数之间连成了双向边（也就是既满足 $a>b$ 又满足 $a<b$），这显然是不符合的，直接 `for` 循环找一下有没有这种边就行了。

现在我们维护出来了连边的方式，考虑怎么赋值。如果直接贪心的前面的数赋值较小，然后按照图的边逐个赋值，可能会出现赋不出值的情况（如果最左侧的数在它处于的不等式链中处于一个较大的位置，并且向右是大于，如果直接贪心的赋值最左侧的数为最小值，会导致右侧的数无法赋值）。因此需要将右侧的所有数从不等式链的底端开始赋值，具体实现方式参考了题解的第一篇。

## Code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof a)
//#define int long long
constexpr int _SIZE = 3e5;
int n, q;
int A[_SIZE + 5], B[_SIZE + 5];
int ans[_SIZE + 5], cnt;
using namespace std;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		int s, t;
		cin >> s >> t;
		if (s < t) A[s - 1]++, A[t - 1]--; // 差分区间加
		else if (s > t) B[s]--, B[t]++;
	}
	for (int i = 1; i <= n; i++) // 差分数组还原
		A[i] += A[i - 1], B[i] += B[i - 1];
	bool noAnswer = 0;
	for (int i = 1; i <= n - 2; i++) // 判定无解
		if (A[i] && B[i]) {noAnswer = 1; break;}
	if (noAnswer) return puts("QED") & 0;
	for (int i = 1; i <= n; i++) {
		if (!ans[i]) {
			int c = 1;
			for (int j = i; j + 2 <= n && A[j]; j += 2) c++; // 找到不等式链的底端
			for (int j = 1; j <= c; j++) ans[i + 2 * c - 2 * j] = ++cnt; // 从底端向上赋值
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：George_Je (赞：2)

提供一个~~简单粗暴~~比较独特的方法。

可以发现各种限制最后会形成一些形如 $a>b>c>d>e>...$ 的链，这些链可能从右往左，也可能从左往右，具体方向取决于限制中 $s,t$ 的大小关系。

又因为题目要求字典序最小，所以贪心的思路是显然的：

从前往后扫，如果当前位置是一条从左往右的链的头，就遍历这条链，同时把元素都放进一个栈里。扫完一整条链后直接边退栈边标号；如果不是从左往右的链头的话，就直接标号。这个部分说起来复杂，其实等会儿看一下代码就明白了（大抵是我表达能力较弱，悲）。至于无解的情况，那当然是某条从右往左的链跟某条从左往右的链交集非空。

然后问题就转化成怎么判断每个位置是从左往右的链，还是从右往左的链，还是没有任何限制条件。这里我的做法是差分。

记 $a$ 为差分数组，对于每对 $s,t$ ，如果 $s<t$，说明这是一条从左往右的链，我们令 $a[s-1]+1$，$a[t-1]-1$；如果 $s>t$，说明这是一条从右往左的链，我们令 $a [t]-INF$，$a [s]+INF$。其中 $INF$ 表示一个极大值，这里取 $3\times 10^5+1$ 即可。最后对 $a$ 做完前缀和后，对于每个 $a[i]$，我们有如下的结论。

- 若 $a[i]>0$，说明 $i$ 在某条从左往右的链上。
- 若 $a[i]=0$，说明 $i$ 这个位置没有任何的限制条件。
- 若 $a[i]<0$ 并且 $INF\mid a[i]$，说明 $i$ 在某条从右往左的链上。
- 若 $a[i]<0$ 并且 $INF\nmid a[i]$，说明 $i$ 既在某条从左往右的链上，又在某条从右往左的链上，遇到这种情况，输出 ```QED``` 表示无解即可。

至此整个算法已经呼之欲出。注意特判与 ```long long``` 。正确性容易证明，也比较好理解。复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e5, MAX_N = N + 3;
constexpr int INF = N + 1;
int n, q;
long long a [MAX_N];
int ans [MAX_N];
signed main () {
	cin >> n >> q;
	while (q--) {
		static int s, t;
		cin >> s >> t;
		if (s < t) {
			if (s == 1) ++a [s];
			else ++a [s - 1];
			--a [t - 1];
		}
		if (s > t) {
			if (s == n) a [s - 1] += INF;
			else a [s] += INF;
			a [t] -= INF;
		}
	}
	for (int i = 1; i <= n; ++i) {
		a [i] += a [i - 1];
		if (a [i] < 0 && a [i] % INF)
			return cout << "QED", 0;
	}
	static bool vis [MAX_N];
	static stack <int> stk;
	int now = 0;
	for (int i = 1; i <= n; ++i) {
		if (vis [i]) continue;
		vis [i] = 1;
		stk.push (i);
		for (int j = i; a [j] > 0; j += 2)
			vis [j + 2] = 1, stk.push (j + 2);
		while (!stk.empty ()) {
			ans [stk.top ()] = ++now;
			stk.pop ();
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << ans [i] << ' ';
}
```


---

## 作者：君と僕のNOIP (赞：2)

一句话题意：构造一个长度为 $ n $ 的数列，给定 $q$ 个区间，使得区间内元素隔位递增或递减，使得数列字典序尽可能小 $ n\in[3,3e5],q\in[0,3e5] $

这里提供一种没脑子的 $topo$ 做法，建议配合[$[P3243 \text{菜肴制作}]$](https://www.luogu.com.cn/problem/P3243)一起食用

**正文：**

我们将题目所求的数列转化一下，改为通过取数构造数列，再通过构造的数列转化为题目所需的数列

设题目所求的数列为 $ a $ ，我们将要构造的数列为 $b$

首先，我们将要构造数列 $b$ 为 从$[1,n]$ 中取 $n$ 次数加入原始的空列，然后 $a$ 中第 $i$ 位为 $a[i]$ 代表了 $i$ 这个数是在第 $a[i]$ 次被加入数列 $b$ 的，也就是说 $b[a[i]]=i$ 下面就是一个例子：

题目所求数列: $a=[1,3,5,4,2]$

通过插入所构造的数列: $b=[1,5,2,4,3]$

题目要求所求的数列字典序最小，因此我们在插入每个数时要让小的数尽量早插入，具体规则和菜肴制作一样，这里就不在赘述

因此条件 $ a[i+1]>a[i-1] $ 就等价于 $i+1$ 要在 $i-1$ 之后加入数列 $b$ ，反过来也是一样。

以上这些东西用 $topo$ 和优先队列能够轻松维护 $b$ 的构造

**注意：不能直接建正图，让最小的数尽早插入和让 $b$ 的字典序最小有所不同，而反向建图求字典序最大再反转数列就行了，细节见菜肴制作**

另外，输入量较大，需要用前缀和维护连边情况，剩下的代码都很清楚了

```
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,less<long long> >q;
long long n,s,t,Q;
struct node{
	long long from,to,next;
}edge[5000001];
long long head[5000001],tot;
long long ca[1000001],ba[1000001];
map<long long,map<long long,long long> >b;
void add(long long from,long long to){
	++tot;
	edge[tot]=(node){from,to,head[from]};
	head[from]=tot;
}
long long in[5000001],vis[5000001],a[5000001];
bool check(){
	for(int i=1;i<=n;i++)
	  if(!a[i]){
	  	printf("QED");
	  	return false;
	  }
	return true;
}
int main(){
	scanf("%lld%lld",&n,&Q);
	while(Q--){
		scanf("%lld%lld",&s,&t);
		if(s==t)continue;
		if(t>s){
			ca[s]++;
			ca[t]--;
		}
		if(s>t){
			ba[t+1]++;
			ba[s+1]--;
		}
	}
	for(int i=1;i<=n;i++)
	  ca[i]+=ca[i-1],ba[i]+=ba[i-1];
	for(int i=1;i<=n;i++){
		if(ca[i]>=1&&ba[i]>=1){
			printf("QED");
			return 0;
		}
		if(ca[i]>=1&&i!=1&&i!=n)add(i-1,i+1),in[i+1]++;
		if(ba[i]>=1&&i!=n&&i!=1)add(i+1,i-1),in[i-1]++;
	}
	for(int i=1;i<=n;i++)
	  if(!in[i])q.push(i);
	long long cont=n+1;
	while(!q.empty()){
		long long u=q.top();
		q.pop(),vis[u]=1;
		a[u]=--cont;
		for(int i=head[u];i;i=edge[i].next){
			long long v=edge[i].to;
			if(vis[v]){
				printf("QED");
				return 0;
			}
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
	if(check())for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	return 0;
}
```


---

## 作者：tymzzh_01 (赞：0)

拿到这题先看一下样例：

- 当 $s=1$，$t=2$ 时，$1$ 只会往 $2$ 流，没有作用。

- 当 $s=3$，$t=7$ 时，$a_3>a_5>a_7$，$a_2>a_4>a_6$。

- 当 $s=8$，$t=10$ 时，$a_7>a_9$，$a_8>a_{10}$。

到这差不多就找到规律了，再看看最后一个。

- 当 $s=5$，$t=6$ 时，$a_4>a_6$。

这下规律就显而易见了：

首先能确定，大小关系一定是奇数配奇数，偶数配偶数

其次，会发现当
$s<t$ 时，形成大小关系的数的区间是 $[s−1,t]$ 的。类似的，也可以推出 
$s>t$ 的方式形成大小关系的数的区间是
$[s,t+1]$。

此外，大致思路与其他题解差不多，剩下的就不讲了。

码风可能有点怪。

# Code


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q;
int a[300005],b[300005];
int ans[300005],cnt = 0;
int read() //快读
{
    int f=1,c,x;
    while((c=getchar())> '9'||c< '0') f=(c=='-'?-1:1); x=c-'0';
    while((c=getchar())>='0'&&c<='9') x=x*10+c-'0';
    return x*f;
}
int main()
{
	n = read();
	q = read();
	while (q--)
	{
		int s = read(),t = read();
		if (s < t)
		{
			a[s - 1]++;
			a[t - 1]--;
		}
		else if (s > t)
		{
			b[s]--;
			b[t]++;
		}
	}
	for (int i = 1;i <= n;i++)
	{
		a[i] += a[i - 1];
		b[i] += b[i - 1];
	}
	bool f = 0;
	for (int i = 1;i <= n - 2;i++)
	{
		if (a[i] && b[i])
		{
			f = 1;
			break;
		}
	}
	if (f)
	{
		cout << "QED";//不存在合法方案
		return 0;
	}
	for (int i = 1;i <= n;i++)
	{
		if (ans[i]) continue;
		{
			int x = 1;
			for (int j = i;(j <= n - 2) && a[j];j += 2) ++x;
			for (int j = 1;j <= x;j++)
			{
				++cnt;
				ans[i + 2 * (x - j)] = cnt;
			}
		}
	}
	for (int i = 1;i <= n;i++) cout << ans[i] << ' ';
	return 0;
}
```

---

