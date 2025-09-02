# [PA 2020] Tekstówka

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 4 [Tekstówka](https://sio2.mimuw.edu.pl/c/pa-2020-1/tek/)**

在去年我们在某社交网络的粉丝页上进行的 PA 中，参与者大声地问我们：「题呢？」。今年，我们决定满足您的期望。

给出了由英文小写字母组成的字符串 $s$ 和 $t$。令 $s_{i,j}\ (1\le i\le j\le |s|)$ 表示由 $s$ 的第 $i$ 个到第 $j$ 个（包含两端）字符依次组成的子串。我们也同样定义 $t_{i,j}$。

你的任务是处理 $q$ 次查询。每次查询用四个整数 $i,j,k,l$ 表示，这里 $1\le i\le j\le |s|,1\le k\le l\le |t|$。对于每次查询，你需要输出子串 $s_{i,j}$ 和子串 $t_{k,l}$ 的最长公共子序列。

注：一个字符串的子序列是指一个字符串通过删除一些（可能不删除）字符且不改变剩余字符顺序得到的串。例如，$\texttt{potyczki}$ 的子串可以是 $\texttt{tyki}$ 或 $\texttt{pi}$，但不能是 $\texttt{koty}$。

我们称字符串 $a$ 和 $b$ 的公共子序列为既是 $a$ 的子序列，又是 $b$ 的子序列的子序列。

我们称字符串 $a$ 和 $b$ 的最长公共子序列为 $a$ 和 $b$ 的子序列中最长的一个。

## 说明/提示

#### 数据范围

**本题采用捆绑测试**

- 对于一些子任务，满足 $n,m,q\le 600$；
- 对于一些其他的子任务，满足 $n,m\le 600$；
- 对于一些其他的子任务，满足 $q\le 5\times 10^3$。

对于上述情况，至少有一个子任务满足。

对于 $100\%$ 的数据，保证 $1\le n,m\le 3\times 10^3$，$1\le q\le 10^5$，$1\le i\le j\le n$，$1\le k\le l\le m$。

## 样例 #1

### 输入

```
5 6 7
abaab
babbaa
1 5 1 6
1 3 2 4
2 5 2 5
1 4 2 5
2 5 3 6
2 2 5 6
3 4 2 2```

### 输出

```
4
2
2
3
3
0
1```

# 题解

## 作者：do_while_true (赞：15)

![](https://s11.ax1x.com/2024/02/20/pFYRGmd.jpg)

![](https://s11.ax1x.com/2024/02/19/pFYnbvR.jpg)

像一棵海草海草海草海草，浪花里舞蹈。

差不多是抄来的题解/wq。

首先对 $S$ 作猫树分治，把询问挂在第一次分割出它的那个节点处。现在需要做的问题就是需要快速处理这样的询问 $f(i,j,k)=LCS(X[i,j],Y[1,k])$，询问 $T[l,r]$ 时利用其处理出 $T[l,r]$ 每个前缀和 $S$ 左半区间后缀的 LCS，每个后缀和 $S$ 右半区间前缀的 LCS，再选最优的拼接方案即可。不考虑处理 LCS，这部分的时间复杂度是 $\mathcal{O}(qm)$ 的。

考虑这样的性质：

①：$f(i-1,j,k)>f(i-1,j-1,k)\Rightarrow f(i,j,k)>f(i,j-1,k)$

②：$f(i,j,k)>f(i,j,k-1)\Rightarrow f(i-1,j,k)>f(i-1,j,k-1)$

这里照抄一下证明。考虑一张网格图，如果 $X_i=Y_j$ 则 $(i,j)\to (i+1,j+1)$ 有一条斜向上的路径，将 LCS 视作一条斜向上次数最多的路径。

对于 ①，考虑 $(i-1,1)$ 到 $(j+1,k+1)$ 的路径 $C_1$，与 $(i,1)$ 到 $(j,k+1)$ 的路径 $C_2$，它们代表了 $f(i-1,j,k),f(i,j-1,k)$。它们必有一交点，假设为 $A$。将 $C_2$ 在 $A$ 之前的路径替换为 $C_1$ 在 $A$ 之前的路径，得到一条 $\leq f(i-1,j-1,k)$ 的路径，根据假设有 $A$ 后面的路径满足 $C_1>C_2$。

同样地将 $C_2$ 在 $A$ 之后的路径替换为 $C_1$ 在 $A$ 之后的路径，得到一条路径 $P$ 满足 $P\leq f(i,j,k)$ 的路径 $P$，而 $C_2$ 替换了一个更大的路径得到 $P$，于是有 $f(i,j-1,k)=C_2<P\leq f(i,j,k)$，得证。

对于 ② 也是同理的。

这两条性质表明：

①：$j\gets j+1$ 时，会 $+1$ 的是个后缀，记为 $p(k,j)$（$j$ 是 $+1$ 后的，$\geq p(k,j)$ 的 $+1$）。

②：$k\gets k+1$ 时，会 $+1$ 的是个前缀，记为 $q(k,j)$（$k$ 是 $+1$ 后的，$<q(k,j)$ 的 $+1$）。

我们令 $F=f(i,j-1,k-1),P=p(k-1,j),Q=q(k,j-1)$。

当 $X_j\neq Y_k$ 时，若 $P<Q$：

![](https://s11.ax1x.com/2024/02/20/pFY4l4I.jpg)

对比 $(1)$ 和 $(3)$ 得 $p(k,j)=Q$，对比 $(2)$ 和 $(3)$ 得 $q(k,j)=P$。

当 $X_j\neq Y_k$ 且 $P\geq Q$ 时：

![](https://s11.ax1x.com/2024/02/20/pFY4grF.jpg)

对比 $(1)$ 和 $(3)$，$(2)$ 和 $(3)$ 得到：$p(k,j)=P,q(k,j)=Q$.

类似地，$X_j=Y_k$ 时，$f(i,j,k)$ 一定为 $F+1$，此时 $p(k,j)=Q,q(k,j)=P$。综上，我们得到了：
$$
(p(k,j),q(k,j))=\left\{\begin{matrix}
 (P,Q) & X_j\neq Y_k,P\geq Q\\
 (Q,P) & otherwise
\end{matrix}\right.
$$
初始 $p(0,i)=i+1$，将 $p,q$ 都递推出来后再处理原问题只需用差分得到 $f$。

对于挂着询问的线段树节点都要 $\mathcal{O}(len\times m)$ 跑出来 $p,q$，所以总的时间复杂度是 $\mathcal{O}((q+n\log n)m)$。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pll>vpll;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int N=3010;
struct DS{
	int n,m;
	char s[N],t[N];
	int p[N][N],q[N][N],o[N][N];
	//LCS(s[i,j], t[1,k])
	void solve(){
		for(int i=0;i<=n;i++)p[i][0]=i+1;
		for(int i=0;i<=m;i++)q[0][i]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				const int P=p[i][j-1],Q=q[i-1][j];
				if(s[i]!=t[j]&&P>=Q)p[i][j]=P,q[i][j]=Q;
				else p[i][j]=Q,q[i][j]=P;
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				o[j][i]=p[i][j];
	}
}ds1,ds2;
int n,m,q;
char s[N],t[N];
struct Node{
	int a,b,c,d,id;
};
vector<Node>vec[N*4];
void modify(int x,int tl,int tr,Node &o){
	int mid=(tl+tr)>>1;
	if(o.b<=mid)modify(x<<1,tl,mid,o);
	else if(o.a>mid)modify((x<<1)|1,mid+1,tr,o);
	else vec[x].push_back(o);
}
int s1[N],s2[N],ans[100010];
void dfs(int x,int tl,int tr){
	if(tl==tr)return ;
	int mid=(tl+tr)>>1;
	if(!vec[x].empty()){
		ds1.m=0;
		for(int i=mid;i>=tl;i--)ds1.t[++ds1.m]=s[i];
		ds1.solve();
		
		ds2.m=0;
		for(int i=mid+1;i<=tr;i++)ds2.t[++ds2.m]=s[i];
		ds2.solve();
		for(auto o:vec[x]){
			int a=o.a,b=o.b,c=o.c,d=o.d,id=o.id;
			for(int i=c-1;i<=d+1;i++)s1[i]=s2[i]=0;
			for(int i=m-d+1;i<=m-c+1;i++){
				int l=m-i+1,r=m-ds1.o[mid-a+1][i]+1;
				s1[l]++,s1[r+1]--;
			}
			for(int i=c;i<=d+1;i++)s1[i]+=s1[i-1];
			for(int i=c;i<=d;i++){
				int l=max(c,ds2.o[b-mid][i]),r=i;
				if(l<=r)
					s2[l]++,s2[r+1]--;
			}
			for(int i=c;i<=d+1;i++)s2[i]+=s2[i-1];
			int mx=0;
			for(int i=c;i<=d+1;i++)
				mx=max(mx,s1[i-1]+s2[i]);
			ans[id]=mx;
		}
	}
	dfs(x<<1,tl,mid);
	dfs((x<<1)|1,mid+1,tr);
}
signed main(){
	read(n);read(m);read(q);
	scanf("%s%s",s+1,t+1);
	ds1.n=0;
	for(int i=m;i>=1;i--)ds1.s[++ds1.n]=t[i];
	ds2.n=0;
	for(int i=1;i<=m;i++)ds2.s[++ds2.n]=t[i];
	for(int i=1;i<=q;i++){
		int a,b,c,d;read(a);read(b);read(c);read(d);
		Node o={a,b,c,d,i};
		if(a!=b)modify(1,1,n,o);
		else{
			for(int j=c;j<=d;j++)
				if(t[j]==s[a]){
					ans[i]=1;
					break;
				}
		}
	}
	dfs(1,1,n);
	for(int i=1;i<=q;i++)cout << ans[i] << '\n';
	return 0;
}
```

---

