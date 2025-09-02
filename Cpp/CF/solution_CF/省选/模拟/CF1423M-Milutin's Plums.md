# Milutin's Plums

## 题目描述

As you all know, the plum harvesting season is on! Little Milutin had his plums planted in an orchard that can be represented as an $ n $ by $ m $ matrix. While he was harvesting, he wrote the heights of all trees in a matrix of dimensions $ n $ by $ m $ .

At night, when he has spare time, he likes to perform various statistics on his trees. This time, he is curious to find out the height of his lowest tree. So far, he has discovered some interesting properties of his orchard. There is one particular property that he thinks is useful for finding the tree with the smallest heigh.

Formally, let $ L(i) $ be the leftmost tree with the smallest height in the $ i $ -th row of his orchard. He knows that $ L(i) \le L(i+1) $ for all $ 1 \le i \le n - 1 $ . Moreover, if he takes a submatrix induced by any subset of rows and any subset of columns, $ L(i) \le L(i+1) $ will hold for all $ 1 \le i \le n'-1 $ , where $ n' $ is the number of rows in that submatrix.

Since the season is at its peak and he is short on time, he asks you to help him find the plum tree with minimal height.

## 样例 #1

### 输入

```
5 5
13 15 10 9 15
15 17 12 11 17
10 12 7 6 12
17 19 14 13 19
16 18 13 12 18```

### 输出

```
```

# 题解

## 作者：Lynkcat (赞：11)

APIO2021 讲课 $\color{black}{I}\red{tst}$ 讲的一个神仙算法。

此题大致题意是，给定一个 $n\times m$ 矩阵 $A$ 满足 $1\leq x<y \leq n,min_x(A)\leq min_y(A)$。 $min_k(A)$ 指 $A$ 中第 $k$ 行最小值的位置。要通过不超过 $4\times(n+m)$ 次查询单个元素的值求出矩阵中的最小值。

这里直接引入 SMAWK 算法。

首先介绍 SMAWK 算法的一个重要过程：$reduce$ 过程。

首先我们定义，当一个位置不可能是当前行的最小值位置，那么称其为冗余位置。

那么我们发现每一列上面冗余位置一定包括了一个列上的前缀。接下来我们考虑如何删除冗余的列来得到 $n\times \min(n,m)$ 的矩阵。

我们维护一个指针 $k$ 初始为 $1$ ，然后进行如下操作：

1:当 $n ≥ m$ 时结束，否则比较 $a_{k,k}$ 和 $a_{k,k+1}$。
 
2:若 $a_{k,k}  ≥ a_{k,k+1}$，删除第 $k$ 列，$k = \max(k-1,1) $，回到步骤 1；

3:若 $a_{k,k}  < a_{k,k+1}$ 且 $k=n$ ，删除第 $n+1$ 列，回到步骤 1；

4:若 $a_{k,k}  < a_{k,k+1}$ 且 $k < n$ ，$k=k+1$，回到步骤 1。

接下来我们考虑这么做为什么是对的：
![](https://cdn.luogu.com.cn/upload/image_hosting/89nv804r.png)

我们目前维护的矩阵 $k\times k$ 显然在对角线以上（注意不包括对角线）的必定是冗余位置，否则中间一定有冗余列。

若 $a_{k,k}  ≥ a_{k,k+1}$ 那么显然第 $k$ 整列都是冗余列，因为 $a_{k,1……k-1}$ 部分已经确定为冗余位置，而 $a_{k,k}$ 也被确定为冗余位置也直接导致整列被确定为冗余列，于是删除此列。

否则我们考虑，若 $a_{k,k}  < a_{k,k+1}$ 且 $k=n$ 那么显然下一列必定是冗余列，删除即可，否则我们还不能确定下一列是否为冗余列，将 $k++$ 即可。

于是 $reduce$ 过程结束了，返回一个 $n\times \min(n,m)$ 的矩阵 $b$ 。

考虑一次 $reduce$ 会查询几个值，每次我们会发现 $k$ 要么加 $1$ 或减 $1$ 且删除一列，查询的值差不多是 $O(n+m)$ 个。  

接下来引入 SMAWK 的主体 $SMAWK(a)$ 

接下来我们考虑将 $b$ 分成两部分，奇数行与偶数行分开，这样子我们就把这个矩阵分成了两个集合 $a,c$ ，我们先运行 $SMAWK(c)$，求出偶数行每行的最小值位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/w5uy90oi.png)

接下来我们根据这个矩阵的性质，可以得出第一行最小值所在的位置 $p_1$ 一定在 $1$ ~ $p_2$ 之间 $p_3$ 一定在 $p_2$ ~ $p_4$ 之间……以此类推。

然后我们这部分暴力查询就得到了 $a$ 中每一行的最小值的位置，一次查询了 $O(n+m)$ 个值。

接下来我们分析一下总体的复杂度：

设 $f(n,m)$ 是 $n\times m$ 的矩阵进行 SMAWK 的复杂度，那么可以得到当 $n\leq m$ 时有 $f(n,m)=f(\frac{n}{2},n))+n+m$，$n>m$ 时为 $f(n,m)=f(\frac{n}{2},m)+n+m$ 并且 $n>m$ 的情况递归 $\log\frac{n}{m}$ 层后变为了 $n\leq m$ 的情况，所以总体复杂度是 $O(m(1 + \log\frac{n}{m}) + n)$。

具体实现我用的是链表进行删除列的操作，子矩阵用维护列与行的集合操作。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
//#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1e18
#define mod 998244353
//#define int ll
#define N 1000005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int pre[N],suf[N],M[N],n,m,ans=1e18,P=0;
vector<int>L,H;
map<int,int>Mp[N];
int query(int x,int y,int z)
{
	if (Mp[x][y]) return Mp[x][y];
	cout<<"? "<<x<<" "<<y<<endl;
	int p;
	cin>>p;
	Mp[x][y]=p;
	return p;
}
void del(int x)
{
	if (pre[x]!=-1)
		suf[pre[x]]=suf[x]; else P=suf[x];
	pre[suf[x]]=pre[x];
}
vector<int> reduce(vector<int>X,vector<int>Y)
{
	for (int i=0;i<Y.size();i++) pre[i]=i-1,suf[i]=i+1;
	int x=0,y=0;
	P=0;
	for (int nmsl=Y.size()-X.size();nmsl>0;nmsl--)
	{
		if (query(X[x],Y[y],0)>query(X[x],Y[suf[y]],0))
		{
			y=suf[y];
			del(pre[y]);
			if (x) y=pre[y],x--;
		} else
		{
			if (x==X.size()-1) del(suf[y]);
			else
			{
				y=suf[y];
				x++;
			}
		}
	}
	vector<int>ret;
	for (int i=P;i!=Y.size();i=suf[i])	ret.push_back(Y[i]);
	return ret;
}
void Solve(vector<int>X,vector<int>Y)
{
	Y=reduce(X,Y);
	if (X.size()==1)
	{
		M[X[0]]=Y[0];
		return;
	}
	vector<int>Z;
	for (int i=0;i<X.size();i++)
		if (!(i%2)) Z.push_back(X[i]);
	Solve(Z,Y);
	for (int i=0;i<X.size();i++)
	{
		if (!(i%2)) continue;
		int l=lower_bound(Y.begin(),Y.end(),M[X[i-1]])-Y.begin();
		int r=0;
		if (i==X.size()-1) r=Y.size()-1;
		else 
		{
			r=lower_bound(Y.begin(),Y.end(),M[X[i+1]])-Y.begin();
		}
		M[X[i]]=Y[l];
		while (l<r)
		{
			l++;
			if (query(X[i],Y[l],1)<query(X[i],M[X[i]],1)) M[X[i]]=Y[l];
		}
	}
}
signed main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		H.push_back(i);
	}
	for (int i=1;i<=m;i++) L.push_back(i);
	Solve(H,L);
	for (int i=1;i<=n;i++)
		ans=min(ans,query(i,M[i],1));
	cout<<"! "<<ans<<endl;
	 
}
/*

*/




---

## 作者：WrongAnswer_90 (赞：2)

# [My Blogs](https://wronganswer90.github.io/2024/11/12/CF1423M-Milutin's-Plums)

### [CF1423M Milutin's Plums](https://www.luogu.com.cn/problem/CF1423M)

完全单调性的定义：一个 $n\times m$ 的矩阵，如果对于所有 $S\subseteq \left \{ 1,2,3\dots n\right\}$，$T\subseteq \left \{1,2,3\dots m\right \}$，只保留 $S$ 中的行和 $T$ 中的列时，每行第一个最小值的位置都是非降的，则称其有完全单调性。

SMAWK 算法：一种能在线性的单点询问次数内，求出一个满足完全单调性矩阵每行最小值及其位置的算法。

#### 外层分治

首先可以通过分治得到一个简单的 $\mathcal O((n+m)\log n)$ 的做法：把所有奇数行删掉之后求出所有偶数行的决策点，奇数行的决策点一定在相邻两个之间。每层询问 $\mathcal O(n+m)$ 次。

上面复杂度带 $\log$ 的原因在于，矩阵可能变得 $n$ 非常小，但是 $m$ 仍然非常大。

#### reduce 操作

注意到每一行只需要保留最小值第一次出现的位置，所以有效的列数是 $\min(n,m)$ 而不是 $m$。SMAWK 的 reduce 操作可以用 $\mathcal O(m)$ 次操作，通过删去全都不可能是最小值的列，将 $m$ 变成 $\min(n,m)$。

考虑询问 $(x,y)$ 和 $(x,y+1)$ 之间的大小关系可以知道什么。如果 $f(x,y)>f(x,y+1)$，取一个只保留 $y,y+1$ 列的子矩形，则 $(x,y)$ 不是最小值点。由完全单调性得，$\forall i\geq x,f(i,y)$ 不是第 $y$ 行对应的最小值点。

而如果 $f(x,y)\leq f(x,y+1)$，同理说明 $\forall i\leq x,f(i,y)$ 也不是最小值点。

考虑维护一个指针 $k$，初始为 $1$，不断询问 $f(k,k)$ 和 $f(k,k+1)$ 的关系。

如果 $f(k,k)\leq f(k,k+1)$，如果 $k=n$ 则删掉第 $k+1$ 行。否则令 $k\leftarrow (k+1)$。容易发现这样的操作保证了，每时每刻，$\forall i\leq j\leq k,f(i,j)$ 都不是最小值点，也就是 $k$ 上方的一个三角形都是没用的。

如果 $f(k,k)>f(k,k+1)$，因为 $k$ 所在列的 $[1,k]$ 的位置都是没用的，这次询问又得到了 $k$ 下方的部分没用，所以删掉第 $k$ 列，令 $k\leftarrow \max(1,k-1)$。

这样分治的时候，每层先调用 reduce 操作，再按照一开始的分治运行即可。实现的时候可以封装一个交互的询问函数，记忆化已经问过的位置来减小常数。

```cpp
int n,m;
int a[1010][1010];
unordered_map<ull,int> hash;
#define id(x,y) 1000000ull*x+y
inline int get(int x,int y,int tp=0)
{
	if(hash.find(id(x,y))!=hash.end())
	return hash[id(x,y)];
	cout<<"? "<<x<<" "<<y<<endl;
	fflush(stdout);
	cin>>hash[id(x,y)];
//		hash[id(x,y)]=a[x][y];
	return hash[id(x,y)];
}

int nex[1000010],pre[1000010];
inline void init(int n)
{
	for(int i=0;i<n;++i)nex[i]=i+1;
	for(int i=1;i<=n;++i)pre[i]=i-1;
	pre[0]=0,nex[n]=n;
}
inline void del(int x)
{
	nex[pre[x]]=nex[x];
	pre[nex[x]]=pre[x];
}
vi solve(vi x,vi y)
{
	{
		for(int i=0;i+1<(int)y.size();++i)
		nex[y[i]]=y[i+1],pre[y[i+1]]=y[i];
		pre[y[0]]=0,nex[0]=y[0];
		nex[y.back()]=-1;
		int i=0,Y=y[0],tat=(int)y.size()-(int)x.size();
		while(tat>0)
		{
			if(get(x[i],Y,1)>get(x[i],nex[Y],1))
			{
				del(Y),--tat;
				if(i)Y=pre[Y],--i;
				else Y=nex[Y];
			}
			else
			{
				if(i+1==(int)x.size())
				del(nex[Y]),--tat;
				else Y=nex[Y],++i;
			}
		}
		y.clear();
		for(int i=0,j=nex[0];i<(int)x.size();++i)
		{
			if(j==-1)break;
			y.eb(j),j=nex[j];
		}
	}
	if(x.size()==1)return y;
	vi xx;
	for(int j=1;j<(int)x.size();j+=2)
	xx.eb(x[j]);
	vi pos=solve(xx,y);
	vi realpos,Pos(x.size());
	
	realpos.eb(0);
	for(int j=0,k=0;k<(int)xx.size();++j)
	{
		while(k<(int)xx.size()&&y[j]==pos[k])
		realpos.eb(j),++k;
	}
	realpos.eb((int)y.size()-1);
	int mx=inf,p=0;
	
	for(int j=0;j<(int)xx.size();++j)
	Pos[(j<<1)|1]=pos[j];
	for(int j=0;j<(int)x.size();j+=2)
	{
		mx=inf,p=-1;
		for(int k=realpos[j>>1];k<=realpos[(j>>1)+1];++k)
		if(Mmin(mx,get(x[j],y[k])))p=y[k];
		Pos[j]=p;
	}
	
	return Pos;
}
void mian()
{
	read(n,m);
//		for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
//		read(a[i][j]);
	vi X,Y;
	for(int i=1;i<=n;++i)X.eb(i);
	for(int i=1;i<=m;++i)Y.eb(i);
	int ans=inf;
	vi pos=solve(X,Y);
	for(int i=0;i<n;++i)Mmin(ans,get(i+1,pos[i]));
	cout<<"! "<<ans<<endl;
}
```

---

## 作者：约瑟夫用脑玩 (赞：2)

## 一些定义

1D/1D 方程：$f_i=\min_{j<i}g_j+w_{j,i}$

最优决策：不妨设为 $ps_i<i$，满足 $f_i=g_{ps_i}+w_{ps_i,i}$。

决策单调性：$\forall i<n,ps_i\le ps_{i+1}$。

~~以上和本题没有太大关系。~~

对于矩阵 $A$ 定义 $pos_i=\{j|\forall p,A_{j,i}\le A_{p,i}\}$。

单调矩阵：满足 $\forall i<j,pos_i\le pos_j$ 的矩阵 $A$。

完全单调矩阵：满足任意一个子矩阵均为单调矩阵的矩阵 $A$。

子矩阵：对于行集合 $i_1,i_2,\cdots,i_n$ 和列集合 $j_1,j_2,\cdots,j_m$，仅保留 $x\in\{i\},y\in\{j\}$ 的元素 $A_{x,y}$ 所形成的矩阵。

性质：完全单调矩阵的子矩阵还是完全单调矩阵。

## 可能是正文

一般的 1D/1D 可以通过令 $A_{i,j}=g_j+w_{j,i}$，$f_i=A_{pos_i,i}$ 从而套用下述算法。

不难发现题目给出条件即为完全单调矩阵的定义，我们只要求出 $\{pos\}$ 即可在 $n$ 次询问内给出回答，事实上，在求出 $pos$ 的过程中可以记录下本题的答案。

求出一个完全单调矩阵的 $pos$ 数组，可以使用 SMAWK 算法。（读音同：smoke 算法）

## 简单分治

我们取出奇数列，递归求出它们的 $pos$，递归到底层只有一行时暴力求出 $pos$ 并返回。

则对于偶数列的决策 $pos_{2k}$ 可以通过遍历 $i\in[pos_{2k-1},pos_{2k+1}]$ 来解决，复杂度是 $O(t\times(pos_{n+1}-pos_0)=tn)$，其中 $t$ 为递归层数，显然为 $\log_2n$。

## 优化

每列只需要一个 $pos$，若我们将 $n\times n\to \frac n2\times n\to\frac n4\times n\to\cdots$ 的矩阵传下去，发现第二维有许多元素无用。

利用完全单调矩阵的性质，我们有如下结论：

$A_{i_1,j}<A_{i_2,j}\to pos_{i_2}\neq\{A_{i_2,c}|1\le c\le j\}$

$A_{i_1,j}\ge A_{i_2,j}\to pos_{i_1}\neq\{A_{i_1,c}|j\le c\le n\}$

这里 $\neq$ 非严谨的定义为除去后还存在位置满足 $pos$ 的定义。

根据此性质我们设计如下过程，定义 $Del(i)$ 为去除第 $i$ 行：

- 初始位置在 $(1,1)$，当前位置在 $(i,i)$。
- 比较 $A_{i,i},A_{i,i+1}$：
  - 若 $A_{i,i}\ge A_{i,i+1}$，则 $Del(i)$。
    - 若 $i\neq 1$，则 $i-1\to i$。
  - 若 $A_{i,i}<A_{i,i+1}$：
    - 若 $i=n$，则 $Del(n+1)$。
    - 若 $i\neq n$，则 $i+1\to i$。
    
这个过程被称之为 $Reduce$ 操作，将其在每次递归取奇数行前调用即得到了 SMAWK 算法。

## 实现

~~我怎么能公然说我的实现好呢？~~

我的实现和其他人不一样，**主要**体现在：

- 非递归。
- 无链表，也无 `vector` 一类。

~~由于本题卡交互次数代码已经被改的面目全非，有需要的找我，我可以据情况友情提供帮助。~~

提供[代码](https://www.luogu.com.cn/paste/tn5u639f)，含注释。

实际上，只要 $Reduce$ 操作对了，删除真的删掉了，遍历 $[pos_{2k-1},pos_{2k+1}]$ 也没写错，这算法必定是线性的。

剩下的就是卡次数，给出两点需要注意的地方：

- $Reduce$ 询问过的地方可以存下来，在 $A_{i,i}\ge A_{i,i+1},i\neq 1$ 的回退时不要重新询问，少一倍次数。
- 最后的 $pos$ 不用重新询问，在处理过程中时刻更新答案，少一倍次数。

正着 $Reduce$ 两倍次数，反着处理偶数列一倍次数，剩下的一倍次数我用来重新询问（这大概就是我 nt 的地方

CF 评测系统上超过次数为 TLE，除非手动返回，否则不给提示信息，这是我没想到的。

---

## 作者：not_clever_syl (赞：1)

这里直接给出 SMAWK 算法的主流程，它返回 $n \times m$ 矩阵每一行的最小值位置。

首先把偶数行都挑出来，递归 $\lfloor \frac n 2 \rfloor \times m$ 的子矩阵，得出偶数行的最小值位置，然后我们就可以轻松 $O(n+m)$ 得到所有奇数行的最小值位置。

这样复杂度就是 $O(n+m\log n)$，虽然看着挺好了，但是我们无法接受。

这是因为当 $m \gg n$ 时，有很多无用的冗余列，也就是不包含任何一行的最小值的列。

这时候我们引入一个 reduce 流程，它可以把 $n \times m$ 的矩阵减小成 $n \times \min(n,m)$ 的矩阵，**且包含了所有行的最小值。** 这样只需要每次 SMAWK 前 reduce 一下就可以保证复杂度为 $O(n+m(1+\log \frac n m))$，由于 $m(1 + \log \frac n m) \leq m(1 + \frac n m)=m+n$，所以还是线性。

reduce 需要额外维护一个指针 $k$，设 $A_{i,j}$ 为传入的矩阵的第 $i$ 行第 $j$ 列位置上的值。

下面是算法流程。

1. 赋值 $k=1$。
2. 若行数大于等于列数（比较动态的行数和列数，因为后面会删列），则停止 reduce 过程。
3. 比较 $A_{k,k}$ 与 $A_{k,k+1}$，若 $A_{k,k} > A_{k,k+1}$，则删去第 $k$ 列，令 $k=\max(1,k-1)$，回到第二步（注意此题内的 $L(i)$ 是**第一个**最小值位置，所以等于是不需要删的，但是 CF 数据弱，两种写法都能过）。
4. 否则此时 $A_{k,k} \leq A_{k,k+1}$，若 $k=n$ 显然第 $n+1$ 列无用，删去第 $n+1$ 列，回到第二步。
5. 否则此时 $k<n$，令 $k=k+1$，回到第二步。

算法不难理解，下面我们看这个算法为什么是对的。

以下使用 `#` 表示一行内的最小值位置，`.` 表示一行内的非最小值位置，`!` 是 $A_{k,k}$ 所在位置的标记，`a=b` 表示标记 `a` 的位置是 `b`, `b` 是 `.` 或 `#`。

对于 `!=#` 的时刻 reduce 显然正确，考虑 `!=.` 的情况。

```text
#....... !=.
.#...... $=.
.#......
.#.!....
...#....
.....#.$
```

我们考察 `!` 与 `#` 同一列的时刻，此时怎么保证 reduce 不会把 `!` 所在行删去呢？

考虑 `!` 到 `$` 的子矩阵，注意题目条件是**每个子矩阵**都有 $L(i) \leq L(i+1)$，因此 `!` 一定是这个**子矩阵中**对应行的最小值位置，那么 $A_{k,k}<A_{k,k+1}$，所以 `!` 的那一行一定可以被保留，可以保证 reduce 的正确性。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000005
int n,m;
map<int,int>mp[MAXN];
int ask(int x,int y){
	if(x>n||y>m||x<1||y<1)return 1e9+2;
	if(mp[x].count(y))return mp[x][y];
	cout<<"? "<<x<<' '<<y<<endl;
	int r;cin>>r;
	return mp[x][y]=r;
}
struct node{
	int pre,nxt;
}l[MAXN];
inline void lnk(int x,int y){l[x].nxt=y;l[y].pre=x;}
void reduce(vector<int>&xx,vector<int>&yy){
	if(xx.size()>=yy.size())return;
	int k=0,t=yy[0],tot=yy.size();
	lnk(0,yy[0]),lnk(yy.back(),0);
	for(int i=0;i+1<(int)yy.size();++i)lnk(yy[i],yy[i+1]);
	while((int)xx.size()<tot){
		int a=ask(xx[k],t),b=ask(xx[k],l[t].nxt);
		if(a>b){
			if(k){
				--k;
				lnk(l[t].pre,l[t].nxt);
				t=l[t].pre;
			}
			else{
				lnk(0,l[t].nxt);
				t=l[t].nxt;
			}
			--tot;
		}
		else{
			if(k<(int)xx.size()-1){
				++k;
				t=l[t].nxt;
			}
			else{
				lnk(t,l[l[t].nxt].nxt);
				--tot;
			}
		}
	}
	while(l[t].pre)t=l[t].pre;
	yy.clear();
	for(;t;t=l[t].nxt)yy.emplace_back(t);
}
vector<int>SMAWK(vector<int>xx,vector<int>yy){
	reduce(xx,yy);
	if(xx.size()==1){
		return yy;
	}
	vector<int>tmp,r2;
	tmp.reserve(xx.size()/2);
	for(int i=1;i<(int)xx.size();i+=2)tmp.emplace_back(xx[i]);
	r2=SMAWK(tmp,yy);
	tmp.clear(),tmp.reserve(xx.size());
	int lst=yy[0],p=0;
	for(int i=0;i<(int)xx.size();++i){
		if(i&1){
			tmp.emplace_back(lst=r2[i>>1]);
		}
		else{
			if((i>>1)<(int)r2.size()&&lst==r2[i>>1]){
				tmp.emplace_back(lst);
			}
			else{
				int tt=((i>>1)==(int)r2.size()?yy.back():r2[i>>1]);
				while(p<(int)yy.size()&&yy[p]<lst)++p;
				int mn=ask(xx[i],lst),id=yy[p];
				while(p+1<(int)yy.size()&&yy[p+1]<=tt){
					++p;
					int v=ask(xx[i],yy[p]);
					if(v<mn){
						mn=v;
						id=yy[p];
					}
				}
				tmp.emplace_back(id);
			}
		}
	}
	return tmp;
}
signed main(){
	cin>>n>>m;
	vector<int>xx,yy;
	xx.reserve(n),yy.reserve(m);
	for(int i=1;i<=n;++i)xx.emplace_back(i);
	for(int i=1;i<=m;++i)yy.emplace_back(i);
	auto res=SMAWK(xx,yy);
	int mn=1e9+5;
	for(int i=1;i<=n;++i){
		mn=min(mn,ask(i,res[i-1]));
	}
	cout<<"! "<<mn<<endl;
}
```

---

## 作者：滑稽生物 (赞：1)

# 题意
给定一个 $n\times m$ 矩阵，其所有子矩阵满足：
- 令 $L(i)$ 为矩阵第 $i$ 行的最左边的取到最小值的位置，则有$L(i)<=L(i+1)$

你需要在 $4(n+m)$ 次询问矩阵单点值的操作内得出矩阵的最小元素的值。

# SMAWK算法
功能：对于一个**完全单调矩阵**（即题中的矩阵），可以在 $O(n + m(1 + max(0, log \frac nm)))$ 次求矩阵中某点的值的操作中求出每行的最小值及其所在位置。

以下内容主要改自$\tt I\color{red}tst$的APIO课件。

本题和课件的不同之处在于：本题定义的完全单调矩阵是最左边的取到最小值的店，而课件中是最右边的取到最小值的点。这可能需要你改变一些 $\ge$ 和 $>$ （不过不改也可以通过本题）。以下内容按照本题考虑。

## 子过程 reduce
求解行最小值的矩阵行数少而列数多时，有很多列冗余，删除它们对答案不产生影响。故考虑子过程 $\tt reduce(A)$，$A$ 是 $ n \times m$ 的完全单调矩阵。其返回一个 $n \times \min(n, m)$ 的矩阵，结果为 $A$ 删除若干冗余的列得到的矩阵。其算法流程如下：

1. 定义 $k=1$ ;
2. 当 $n \ge m$ 时结束，否则比较 $A_{k,k}$ 和$A_{k,k+1}$ 。
3. 若 $A_{k,k}>A_{k,k+1}$ ，删除第 $k$ 列，$k \larr \max{k-1,1}$ ；

4. 若 $A_{k,k}\le A_{k,k+1}$ 且 $k=n$ ，删除第 $n+1$ 列，回到步骤 $2$ ；
5. 若 $A_{k,k}\le A_{k,k+1}$ 且 $k\ne n$ ， $k\larr k+1$ ，回到步骤 $2$ 。

可以理解为维护一个对角线。reduce 一共会删除 $m-n$ 列，每次要么 $k$ 加一，要么删一列（同时 $k$ 最多减一）故复杂度为 $O(m+n)$。

## SMAWK 算法流程

SMAWK 算法是一个递归算法，借用 reduce 作为子过程。过程 $\tt SMAWK(A)$ 表示计算 $n \times m$ 的完全单调矩阵 $A$ 的每行最小值所在列。算法流程如下：

1. 若 $\min(n, m) = 1$ 直接计算答案； 
2. 设 $B = \tt reduce(A), $ $C$ 为 $B$ 的子矩阵， $C = B_{[2,4,··· ,2⌊ n 2 ⌋],[1,2,··· ,min(n,m)]}$； 
3. 递归计算 $\tt SMAWK(C)$ 得到偶数行最小值所在列； 
4. 对于 B 中的奇数行，在其相邻两行的最小值所在列之间暴力枚举计算出其最小值所在列。

步骤4的复杂度为 $O(m)$，当$m\ge n$时复杂度为 $O(m+n)$ （由于有reduce），当 $m<n$ 时递归 $\log \frac nm$ 层之后进入 $n \le m$ 的情况，所以复杂度为 $O(m(1+\max(0,\log \frac nm))+n)$ 



实现时需要用链表表示子矩阵 ~~然而Itst用了vector~~ 以保证复杂度正确。

代码：

[Itst的代码](https://codeforces.ml/contest/1423/submission/94775385)

我的代码：（因为不会搞链表所以写得特别拉）

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define INF 0x3f3f3f3f
using namespace std;
int n,m,ans[N],Ans;
unordered_map<int,int> mp[N];
int get(int i,int j){
	if(mp[i].find(j)!=mp[i].end())return mp[i][j];
	printf("? %d %d\n",i,j);
	fflush(stdout);int res;
	scanf("%d",&res);mp[i][j]=res;
	return res;
}
struct node{
	int val;char opt;
	node *lst,*nxt;
	node(){val=opt=0;lst=nxt=NULL;}
};
struct List{
	int len;
	node *s,*e;
	List(){
		len=0;
		s=new node();s->opt=1;
		e=new node();e->opt=-1;
		s->nxt=e;e->lst=s;
	}
	void append(int x){
		node *n=new node();n->val=x;
		node *a=e->lst;
		a->nxt=n;n->lst=a;
		n->nxt=e;e->lst=n;
		++len;
	}
	List(const List &a){
		len=0;
		s=new node();s->opt=1;
		e=new node();e->opt=-1;
		s->nxt=e;e->lst=s;
		node *n=a.s->nxt;
		while(n->opt!=-1)append(n->val),n=n->nxt;
	}
	node* del(node *n){
		--len;
		node *a=n->lst,*b=n->nxt;
		a->nxt=b;b->lst=a;
		delete(n);
		return a;
	}
};
struct submat{
	List r,c;
}A;
submat reduce(const submat&A){
	submat B;
	B.r=List(A.r);B.c=List(A.c);
	int n=A.r.len,m=A.c.len;
	if(n>=m)return B;
	node *nr=B.r.s->nxt,*nc=B.c.s->nxt;
	int k=1;
	while(n<m){
		//三种情况 
		if(get(nr->val,nc->val)>get(nr->val,nc->nxt->val)){
			nc=B.c.del(nc);--m;
			if(k>1){
				--k;
				nr=nr->lst;
			}else{
				nr=B.r.s->nxt,nc=B.c.s->nxt;
			}
		}else if(k==n){
			B.c.del(nc->nxt);--m;
		}else{
			k=k+1;
			nr=nr->nxt,nc=nc->nxt;
		}
	}
	return B;
}
void SMAWK(submat A){
	int n=A.r.len,m=A.c.len;
	if(n==1){
		int x=A.r.s->nxt->val,minp=0,minv=INF;
		node *nc=A.c.s->nxt;
		while(nc->opt!=-1){
			if(get(x,nc->val)<minv)minp=nc->val,minv=get(x,nc->val);
			nc=nc->nxt;
		}
		ans[x]=minp;Ans=min(minv,Ans);
		return;
	}
	if(m==1){
		int y=A.c.s->nxt->val;
		node *nr=A.r.s->nxt;
		while(nr->opt!=-1){
			ans[nr->val]=y;
			nr=nr->nxt;
		}
		return;
	}
	submat B=reduce(A);
	submat C;
	C.c=List(B.c);
	node *nr=B.r.s->nxt;bool o=0;
	while(nr->opt!=-1){
		if(o)C.r.append(nr->val);
		nr=nr->nxt;
		o^=1;
	}
	SMAWK(C);
	nr=B.r.s->nxt;o=0;
	node *nc=B.c.s->nxt;
	while(nr->opt!=-1){
		if(!o){
			int z=ans[nr->nxt->val],x=nr->val,minp=0,minv=INF;
			if(z==0)z=INF;
			while(nc->opt!=-1&&nc->val<=z){
				if(get(x,nc->val)<minv)minp=nc->val,minv=get(x,nc->val);
				nc=nc->nxt;
			}
			if(nc->lst->val==z)nc=nc->lst;
			ans[x]=minp;Ans=min(Ans,minv);
		}
		nr=nr->nxt;
		o^=1;
	}
}
int main(){
	Ans=INF;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)A.r.append(i);
	for(int i=1;i<=m;++i)A.c.append(i);//A为整个矩阵 
	SMAWK(A);
	printf("! %d\n",Ans);
	return 0;
}
```





---

