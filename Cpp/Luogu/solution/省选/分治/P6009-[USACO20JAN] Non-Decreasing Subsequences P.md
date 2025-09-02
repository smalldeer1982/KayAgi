# [USACO20JAN] Non-Decreasing Subsequences P

## 题目描述

Bessie 最近参加了一场 USACO 竞赛，遇到了以下问题。当然 Bessie 知道怎么做。那你呢？

考虑一个仅由范围在 $1 \ldots K$（$1 \leq K \leq 20$）之间的整数组成的长为 $N$ 的序列 $A_1,A_2, \ldots ,A_N$（$1 \leq N \leq 5 \times 10^4$）。给定 $Q$（ $1 \leq Q \leq 2 \times 10^5$ ）个形式为 $[L_i,R_i]$（$1 \leq L_i \leq R_i \leq N$）的询问。对于每个询问，计算 $A_{L_i},A_{L_i+1}, \ldots ,A_{R_i}$ 中不下降子序列的数量模 $10^9+7$ 的余数。

$A_L,\ldots ,A_R$ 的一个不下降子序列是一组索引 （$j_1,j_2, \ldots ,j_x$），满足 $L\le j_1<j_2<\ldots<j_x\le R$ 以及 $A_{j_1}\le A_{j_2}\le \ldots \le A_{j_x}$。确保你考虑了空子序列！

## 说明/提示

### 样例解释

对于第一个询问，不下降子序列为 $()$、$(2)$ 和 $(3)$。$(2,3)$ 不是一个不下降子序列，因为 $A_2\not \le A_3$。

对于第二个询问，不下降子序列为 $()$、$(4)$、$(5)$ 和 $(4,5)$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 1000$。
- 测试点 $4 \sim 6$ 满足 $K \leq 5$。
- 测试点 $7 \sim 9$ 满足 $Q \leq 10^5$。
- 测试点 $10 \sim 12$ 没有额外限制。

## 样例 #1

### 输入

```
5 2
1 2 1 1 2
3
2 3
4 5
1 5```

### 输出

```
3
4
20```

# 题解

## 作者：cwfxlh (赞：14)

# [P6009](https://www.luogu.com.cn/problem/P6009)   

模拟赛考了这道题，但不知道为什么没做出来。    

DP 式子的转移是很好列的，令 $dp_{i}$ 表示当前以值为 $i$ 的元素结尾的不降子序列个数，特别的，令 $dp_0$ 表示空序列个数，则令当前枚举到了第 $j$ 个元素，转移为 $dp_{A_j}+=\sum_{u=0}^{A_j}dp_u$。很容易发现这个东西可以写成矩阵的形式，于是问题就变成了一个区间矩阵乘积的问题。我们不妨用前缀积与逆前缀积来维护。但是我们发现，转移写成的矩阵逆是很好求的，不需要高消求逆（数学计算推一下即可，形式与原矩阵相似），于是直接暴力乘出一个前缀积和逆前缀积，询问的时候相乘即可。复杂度 $O((n+q)k^3)$。    

但是这个复杂度是过不去的，我们发现，转移写出来的矩阵只有 $O(k)$ 个元素有值，于是预处理的矩乘就可以加速到 $O(nk^2)$。询问的时候，答案矩阵可以由 $base\times InvPre(L-1)\times Pre(R)$ 得到，其中 $base$ 是一个仅有一个元素为 1 的 $1\times (k+1)$ 的矩阵，于是乘上 $base$ 后，矩阵大小只有 $k+1$，暴力矩阵乘的复杂度会变为 $O(qk^2)$，可以通过此题。当然利用前缀和可以优化到 $O(qk)$。总复杂度 $O((n+q)k^2)$。   

代码：

```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
#define ll long long
using namespace std;
struct Matrix{
	int h;
	int w;
	int v[23][23];
}InvPre[50003],Pre[50003],res,ans;
Matrix operator*(Matrix A,Matrix B){
	res.h=A.h;
	res.w=B.w;
	for(int i=1;i<=res.h;i++){
		for(int j=1;j<=res.w;j++){
			res.v[i][j]=0;
			for(int u=1;u<=A.w;u++)res.v[i][j]=(res.v[i][j]+((ll)(A.v[i][u])*(ll)(B.v[u][j])%MOD))%MOD;
		}
	}
	return res;
}
void print(Matrix A){
	for(int i=1;i<=A.h;i++){
		for(int j=1;j<=A.w;j++)printf("%d ",(A.v[i][j]+MOD)%MOD);
		printf("\n");
	}
	return;
}
int n,k,q,w[50003],op1,op2,sum;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	scanf("%d",&q);
	Pre[0].h=Pre[0].w=InvPre[0].h=InvPre[0].w=k+1;
	for(int i=1;i<=k+1;i++)Pre[0].v[i][i]=InvPre[0].v[i][i]=1;
	for(int i=1;i<=n;i++){
		Pre[i].h=Pre[i].w=InvPre[i].h=InvPre[i].w=k+1;
		Pre[i]=Pre[i-1];
		for(int u=1;u<=k+1;u++){
			for(int p=1;p<=w[i]+1;p++)Pre[i].v[u][w[i]+1]=(Pre[i].v[u][w[i]+1]+Pre[i-1].v[u][p])%MOD;
		}
		for(int j=1;j<=k+1;j++){
			for(int u=1;u<=k+1;u++){
				InvPre[i].v[j][u]=(InvPre[i-1].v[j][u]-(500000004ll*(ll)(InvPre[i-1].v[w[i]+1][u])*(ll)(j<=w[i]+1))%MOD)%MOD;
			}
		}
	}
	while(q--){
		scanf("%d%d",&op1,&op2);
		ans.h=1;
		ans.w=k+1;
		for(int i=1;i<=k+1;i++)ans.v[1][i]=(int)(i==1);
		ans=(ans*InvPre[op1-1]);
		ans=(ans*Pre[op2]);
		sum=0;
		for(int i=1;i<=k+1;i++)sum=(sum+ans.v[1][i])%MOD;
		sum+=MOD;
		sum%=MOD;
		printf("%d\n",sum);
	}
	return 0;
}
```


---

## 作者：lfxxx (赞：5)

看到静态区间查询首先想想猫树。

考虑对于每个区间记录 $f_{i,j}$ 表示以数 $i$ 开头，数 $j$ 结尾的不下降子序列数量。

然后可以滚一遍前缀和快速计数。

但是猫树的空间很爆炸，所以考虑 **离线** 处理猫树的整个操作。

那么最后我们就 $O((n \log n + q) \times k^2)$ 的做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9+7;
using namespace std;
const int maxn = 2e5+114;
int pre[50001][21];
int ans[maxn],a[maxn],lm[21][21],rm[21][21];
struct query{
	int l,r,id;
};
void solve(int l,int r,queue<query> &s){
	if(s.size()==0||l>r) return ;
	if(l==r){
		while(s.size()>0){
			ans[s.front().id]=1;
			s.pop();
		}
		return ;
	}
	int mid=(l+r)/2;
	queue<query> L,R,M;
	while(s.size()>0){
		int lt=s.front().l,rt=s.front().r;
		if(rt<=mid){
			L.push(s.front());
		}
		else if(lt>mid){
			R.push(s.front());
		}
		else{
			M.push(s.front());
		}
		s.pop();
	}
	solve(l,mid,L);
	solve(mid+1,r,R);
	for(int i=l;i<=r;i++)
		for(int j=1;j<=20;j++)
			for(int k=1;k<=20;k++) pre[i][j]=0,lm[j][k]=0,rm[j][k]=0;
	for(int i=mid;i>=l;i--){
		for(int j=a[i];j<=20;j++){
			for(int k=1;k<=20;k++){
				lm[a[i]][k]+=lm[j][k];
				lm[a[i]][k]%=mod; 				
			}
		}
		lm[a[i]][a[i]]++;
		lm[a[i]][a[i]]%=mod;
		for(int j=1;j<=20;j++){
			for(int k=j;k<=20;k++){
				pre[i][k]+=lm[j][k];
				pre[i][k]%=mod;
			}
		}
	}
	for(int i=mid+1;i<=r;i++){
		for(int j=1;j<=20;j++){
			for(int k=a[i];k>=1;k--){
				rm[j][a[i]]+=rm[j][k];
				rm[j][a[i]]%=mod;
			}
		}
		rm[a[i]][a[i]]++;
		rm[a[i]][a[i]]%=mod;
		for(int j=1;j<=20;j++){
			for(int k=j;k<=20;k++){
				pre[i][j]+=rm[j][k];
				pre[i][j]%=mod;
			}
		}
	}
	while(M.size()>0){
		int lt=M.front().l,rt=M.front().r;
		for(int i=1;i<=20;i++){
			for(int j=i;j<=20;j++){
				ans[M.front().id]+=(pre[lt][i]*pre[rt][j])%mod;
				ans[M.front().id]%=mod;
			}
		}
		for(int i=1;i<=20;i++){
			ans[M.front().id]+=(pre[lt][i]+pre[rt][i])%mod;
			ans[M.front().id]%=mod;
		}
		M.pop();
	}
}
int n,m,K;
queue<query> S;
signed main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>n>>K;
for(int i=1;i<=n;i++) cin>>a[i];
cin>>m;
for(int i=1;i<=m;i++){
	query Q;
	cin>>Q.l>>Q.r;
	Q.id=i;
	S.push(Q);
}
solve(1,n,S);
for(int i=1;i<=m;i++){
	cout<<(ans[i]+1)%mod<<'\n';
}
return 0;
}

```


---

## 作者：YFXj_38 (赞：5)

###### 树分治好题，至少对于我这个树分治初学者
[洛谷P6009](https://www.luogu.com.cn/problem/P6009)
### 题目：
求区间不下降子序列个数
且$a_i\leq k,k\leq 20,N\leq 5\times 10^4,Q\leq 2\times 10^5$
### 题解：
很难想到，要用CDQ分治
要分了之后怎么进行维护复杂度尽量小，这是CDQ分治很难受的地方。

 - 定义数组
 在每个$solve(l,r)$中都有
 
 $f_{i,j}$  表示
 
 $(l\leq j \leq mid)j$为左端点 ，$k\in [j,mid]$中所有$a_{k}=i$的$k$为右端点，不下降子序列个数
 
  $(mid < j\leq r)j$为右端点 ， $k\in (mid,j]$中所有$a_{k}=i$的$k$为左端点，不下降子序列个数
 - 维护数组
 
  尽可能的找数组之间的联系
  
  首先因为$mid$将$f_{i,j}$分为了两个部分，意义不同（其实泛泛来说差不多）,所以我们也分两部分讨论
  
  这里我们先只分析右边的，左边的同理理解
  
  $$f_{i,j}= \ [a_j==i]+\sum_{mid\leq k<j,a_k\leq a_j}f_{i,k}$$
   然后我开始看到这式子，是懵逼的
   
   $[a_j==i]$指如果$a_j==i$的话，$j->j$就是一个合法区间，$f_{i,j}+1$
   
   $\sum_{mid\leq k<j,a_k\leq a_j}f_{i,k}$指与前面的已合法区间拼接，因为还要满足拼接后不下降，所以$a_k\leq a_j$
   
   于是我们可以想到树状数组维护（略）
   

###### 注意：
 右边循环顺序是$mid+1->r$，但左边循环顺序是$mid->l$,因为是逆着来的，所以注意树状数组也要逆一下
 
因为空集也算合法区间，所以要把$f_{1,mid},f_{k,mid+1}$都要+1
 - 询问求值
 
 yy一下我们想到，我们需要将我们的$f_{i,j}$前缀和一下（左边是后缀和）
 
 我们先只考虑跨过$mid$的询问区间（ql,qr分别为询问的左右端点）
 $$ans=\sum_{1\leq i\leq k}F_{i,ql}\sum_{i\leq j\leq k}F_{j,qr}$$
 理解下，就是左右两端拼接，乘法原理
 
 （我曾迷惑：$ql->s,s->qr$，$mid<s$的情况没有考虑啊，但其实将$s$移到 $\overline{s}<mid$，$ql->\overline{s},\overline{s}<qr$这样是等效的）
 - 复杂度 $O(nklognlogk+qk)$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
const int N=5e4+10,K=25,Q=2e5+10;
int n,k,q;
int a[N];
struct qus{int l,r;}qs[Q];
ll ans[Q];
ll f[K][N];
//---
ll t[K];
int lowbit(int x){return x&(-x);}
void clear(){memset(t,0,sizeof(t));}
void add(int i,int x){for(;i<=k;i+=lowbit(i))t[i]=(t[i]+x)%mod;}
ll qur(int i){ll res=0;for(;i;i-=lowbit(i))res=(res+t[i])%mod;return res;}
//----
ll ls[N];
void solve(int l,int r,vector<ll>v)
{
	if(l==r)
	{
		for(int i=0;i<v.size();i++)ans[v[i]]=2;
		return ;
	}
	int mid=(l+r)>>1;
	for(int i=1;i<=k;i++)
	{
		clear();
		for(int j=mid;j>=l;j--)
		{
			f[i][j]=qur(k+1-a[j]);
			if(a[j]==i)f[i][j]=(f[i][j]+1)%mod;//自己->自己 
			add(k+1-a[j],f[i][j]);//逆转树状数组 
		}
		for(int j=mid-1;j>=l;j--)f[i][j]=(f[i][j]+f[i][j+1])%mod;//前缀和 
	}
	for(int j=l;j<=mid;j++)f[1][j]=(f[1][j]+1)%mod;//空集
	for(int i=1;i<=k;i++)
	{
		clear();
		for(int j=mid+1;j<=r;j++)
		{
			f[i][j]=qur(a[j]);
			if(a[j]==i)f[i][j]=(f[i][j]+1)%mod;
			add(a[j],f[i][j]);
		}
		for(int j=mid+2;j<=r;j++)f[i][j]=(f[i][j]+f[i][j-1])%mod;
	}
	for(int j=mid+1;j<=r;j++)f[k][j]=(f[k][j]+1)%mod;
	vector<ll>vl,vr;
	vl.resize(0);vr.resize(0); 
	for(int i=0;i<v.size();i++)
	{
		int l=qs[v[i]].l,r=qs[v[i]].r;
		if(r<=mid)	  vl.push_back(v[i]);
		else if(mid<l)vr.push_back(v[i]);
		else
		{
			for(int j=k;j>=1;j--)ls[j]=(ls[j+1]+f[j][r])%mod;//前缀又后缀。。。
			for(int j=1;j<=k;j++)ans[v[i]]=(ans[v[i]]+ls[j]*f[j][l]%mod)%mod;
		}
	}
	if(vl.size())solve(l,mid,vl);
	if(vr.size())solve(mid+1,r,vr);
}
vector<ll>v;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)scanf("%d%d",&qs[i].l,&qs[i].r);
	for(int i=1;i<=q;i++)v.push_back(i);
	solve(1,n,v);
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}
```

[从这位巨佬博客看懂的](https://www.cnblogs.com/xh092113/p/12283379.html)


---

## 作者：x_faraway_x (赞：5)

题目的 DP 显然可以写成矩乘的形式。类似 LNRD1T1，记下转移矩阵和逆矩阵的前缀积 $pref,ipref$，答案即为 
$$\sum_{i=1}^{K}(ipref[L-1]\cdot pref[R])[1][i]$$

注意只有 $O(K)$ 个位置有值，所以矩乘的复杂度是 $O(K^2)$ 的，直接做复杂度是 $O((N+Q)K^2)$ 的，精细实现可以通过。

也可以记前缀积的前缀和：

$$\sum_{i=1}^{K}ipref[L-1][1][i]\cdot \left(\sum_{j=1}^{K}pref[R][i][j]\right)$$

可以做到 $O(NK^2+QK)$.

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int gi()
{
	char c=getchar(); int x=0;
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+c-'0';
	return x;
}
const int N=5e4+5,K=23,Mod=1e9+7,iM=Mod+1>>1;
int m[K][K],im[K][K],pre[N][K],inv[N][K],n,k,q;
#define mul(x,y) (1ll*(x)*(y)%Mod)
inline int add(int x, int y)
{	return (x+y>=Mod?x+y-Mod:x+y);
}
inline int sub(int x, int y)
{	return (x-y<0?x-y+Mod:x-y);
}
int main()
{
	n=gi(),k=gi();
	for(int i=1;i<=k;++i) m[i][i]=im[i][i]=pre[0][i]=1;
	inv[0][1]=1;
	for(int l=1;l<=n;++l)
	{
		int x=gi();
		for(int i=1;i<=x;++i)
			for(int j=x;j>=i;--j) m[i][x]=add(m[i][x],m[i][j]);
		for(int i=1;i<x;++i)
			for(int j=x;j<=k;++j) im[i][j]=sub(im[i][j],mul(iM,im[x][j]));
		for(int i=x;i<=k;++i) im[x][i]=mul(im[x][i],iM);
		for(int i=1;i<=k;++i)
		{
			inv[l][i]=im[1][i];
			for(int j=i;j<=k;++j) pre[l][i]=add(pre[l][i],m[i][j]);
		}
	}
	q=gi();
	while(q--)
	{
		int l=gi(),r=gi(),ans=0;
		for(int i=1;i<=k;++i) ans=add(ans,mul(pre[r][i],inv[l-1][i]));
		printf("%d\n",ans);
	}
}
```

---

## 作者：Karry5307 (赞：4)

### 题意

给一个长度为 $n$，值域在 $[1,k]$ 内的序列 $a$，$q$ 次询问，每次询问给 $l,r$，问你 $a_l\sim a_r$ 内不降子序列的总数。

$\texttt{Data Range:}n\leq 5\times 10^4,k\leq 20,q\leq 10^5$

### 题解

考虑如何求 $l=1,r=n$ 时的答案。

注意到值域范围很小，于是可以 $\texttt{dp}$，设 $f_{i,j}$ 表示前 $i$ 个数，钦定最后一个为 $j$ 的不降子序列总数，枚举一下得到

$$f_{i,j}\begin{cases}f_{i-1,j},&j\neq a_i\\f_{i-1,j}+\sum\limits_{k=1}^{j}f_{i-1,k},&j=a_i\end{cases}$$

注意到可以维护矩阵来进行转移，第 $r$ 个位置的转移矩阵大概长这样：

$$T_{r,i,j}=[i=j]+[i\leq j][j=a_r]$$

这样可以求得答案为

$$\begin{pmatrix}1&0&\cdots&0\end{pmatrix}\prod\limits_{i=1}^{n}T_i\begin{pmatrix}1\\1\\\vdots\\1\end{pmatrix}$$

现在把他迁移到任意区间上来，得到

$$\begin{pmatrix}1&0&\cdots&0\end{pmatrix}\prod\limits_{i=l}^{r}T_i\begin{pmatrix}1\\1\\\vdots\\1\end{pmatrix}$$

考虑差分，得到

$$\begin{pmatrix}1&0&\cdots&0\end{pmatrix}\prod\limits_{i=l-1}^{1}T_i^{-1}\prod\limits_{i=1}^{r}T_i\begin{pmatrix}1\\1\\\vdots\\1\end{pmatrix}$$

考虑这个东西的逆矩阵是啥。根据人类智慧得到

$$T_{r,i,j}^{-1}=[i=j]-\frac{1}{2}[i\leq j][j=a_r]$$

于是维护 

$$L_x=\prod\limits_{i=1}^{x}T_i\begin{pmatrix}1\\1\\\vdots\\1\end{pmatrix}$$

和

$$R_x=\begin{pmatrix}1&0&\cdots&0\end{pmatrix}\prod\limits_{i=x}^{1}T_i^{-1}$$

就可以得到答案为 $R_{l-1}L_r$。

但是，暴力矩乘不可取，考虑优化。

注意到 $T_r=I+A_r$，并且 $A_{r,i,j}=[i\leq j][j=r]$

右乘和左乘都可以 $O(n^2)$ 求出，总时间复杂度 $O(nk^2+qk)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=1e9+7;
ll n,kk,qcnt,l,r,res;
ll x[MAXN],p[25][25],f[MAXN][25],g[MAXN][25];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
    n=read(),kk=read();
    for(register int i=1;i<=kk;i++)
    {
		p[i][i]=1;
    }
    for(register int i=1;i<=n;i++)
    {
		x[i]=read();
		for(register int j=1;j<=kk;j++)
		{
			for(register int k=x[i];k;k--)
			{
				p[j][x[i]]=(p[j][k]+p[j][x[i]])%MOD;
			}
		}
		for(register int j=1;j<=kk;j++)
		{
			for(register int k=1;k<=kk;k++)
			{
				f[i][j]=(f[i][j]+p[j][k])%MOD;
			}
		}
    }
    memset(p,0,sizeof(p)),qcnt=read(),g[0][1]=1;
    for(register int i=1;i<=kk;i++)
    {
		p[i][i]=1;
    }
    for(register int i=1;i<=n;i++)
    {
		for(register int j=1;j<=x[i];j++)
		{
			for(register int k=1;k<=kk;k++)
			{
				p[j][k]=(p[j][k]+(li)(5e8+3)*p[x[i]][k]%MOD)%MOD;
			}
		}
		for(register int j=1;j<=kk;j++)
		{
			g[i][j]=p[1][j];
		}
    }
    for(register int i=0;i<qcnt;i++)
    {
		l=read(),r=read(),res=0;
		for(register int j=1;j<=kk;j++)
		{
			res=(res+(li)g[l-1][j]*f[r][j]%MOD)%MOD;
		}
		printf("%d\n",res);
    }
}
```

---

## 作者：Purslane (赞：3)

# Solution

今早模拟赛的题。

既然是模拟赛，肯定要整出点有意思的东西。

## 思路 $1$

考虑维护以 $[l,r]$ 的不降子序列个数。但是这样空间和时间上是 $O(kn^2)$ 的。

下面是几种可能可行的优化方案。
 
1. $n$ 的范围让人想到分块。于是存块内值域为 $[x,y]$ 的不降子序列个数，块内前缀后缀以及块与块间的不下降子序列。但是复杂度为 $O((n+q)k^4)$，不足以通过本题。

2. 考虑使用倍增。存长度为 $2^k$ 的区间内值域为 $[x,y]$ 的不降子序列个数。使用前缀和优化可以做到 $O((n+q)k^2\log n)$。还是不足通过本题。

3. 使用**猫树分治**。这样构建数的时候复杂度还是 $O(n k^2 \log n)$ 的，但是你查询的时候只需要合并一次，所以查询复杂度为 $O(q k^2)$。很显然，瓶颈是后者。

以上都是数据结构做法，但是我没有想到。

## 思路 $2$

考虑动态动态规划（$\text{DDP}$）。设状态为 $dp_{n,k}$ 表示前 $n$ 位，不降子序列的最后一个数是 $k$ 的方案数。那么对 $k \neq a_n$，有 $dp_{n,k}=dp_{n-1,k}$。否则 $dp_{n,k}=dp_{n-1,k}+1+\sum_{i=1}^k dp_{n-1,i}$。第一项表示第 $n$ 位不选，第二项表示 $n$ 是第一个数，第三项表示在之前某个位置之后转移。

这样可以写成一个 $21 \times 21$ 的矩阵。其中你可以认为 $1$ 是 $dp_{n,0}$。那么查询的时候是一段连续的矩阵区间。

这个很容易相当前缀和，复杂度 $O(n k^3)$。只有两个问题：

- 差分性的满足。可以对于每个 $pre$ 求出其逆矩阵。但是这样复杂度也是 $O(n k^3)$，而且常数巨大。所以你考虑 $(AT)^{-1}=T^{-1}A^{-1}$，那么每次求出新来的 $T$ 的逆矩阵。你会发现我们的矩阵本来就很稀疏，所以除了第 $a_n$ 列都不用高斯消元。于是你可以直接构造 $T^{-1}$ 而不是费劲去高斯消元。
- 矩阵乘法。我们有两种矩阵乘法：$AT$ 和 $T^{-1}A^{-1}$。虽然复杂度看似正确但是常数巨大难以通过。但是你考虑到 $T$ 和 $T^{-1}$ 里面绝大多数元素都是 $0$，所以你可以手动跳过不可能产生答案的乘法。比如，如果第二个矩阵的某一列只有一个元素，那么你大可以只用它去乘第一个矩阵中的特定元素。这样事实上做一次矩阵乘法的复杂度是 $O(k^2)$ 的。

然后计算答案。还是类似的，我们要求 $pre_{l-1}^{-1}pre_r$。事实上我们初始矩阵只有 $dp_{0,0}$ 是有值的，所以我们要的也只不过是 $pre_{l-1}^{-1} pre_r$ 中的一行。所以只算这一行即可。做一次矩阵乘法的复杂度也是 $O(k^2)$ 的。

所以你出色的在 $O((n+q)k^2)$ 的复杂度内完成了本题。没有 $\log$。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=22+1,MAXM=5e4+10,MOD=1e9+7;
using LL=long long;
LL qpow(LL base,int p) {
	LL ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int n,K,q,a[MAXM];
struct Matrix {int v[MAXN][MAXN];}pre[MAXM],anti[MAXM];
int pmod(int v) {
	if(v<0) v+=MOD;
	if(v>=MOD) v-=MOD;
	return v;
}
Matrix operator *(Matrix A,Matrix B) {
	Matrix res; memset(res.v,0,sizeof(res.v));
	ffor(i,1,K) ffor(j,1,K) ffor(k,1,K) res.v[i][k]=pmod(res.v[i][k]+1ll*A.v[i][j]*B.v[j][k]%MOD);
	return res;
}
int Inv[MAXN];
Matrix Anti_Matrix(Matrix tsk) {
	Matrix res; memset(res.v,0,sizeof(res.v));
	ffor(i,1,K) res.v[i][i]=1;
	ffor(i,1,K) {
		if(!tsk.v[i][i]) {
			ffor(j,i+1,K) if(tsk.v[i][j]) {
				ffor(k,1,K) swap(tsk.v[k][i],tsk.v[k][j]),swap(res.v[k][i],res.v[k][j]);
				break;	
			}
		}
		int inv=qpow(tsk.v[i][i],MOD-2);
		Inv[i]=inv;
		ffor(j,i+1,K) {
			int mul=1ll*tsk.v[i][j]*inv%MOD;
			if(mul) ffor(k,1,K) tsk.v[k][j]=pmod(tsk.v[k][j]-1ll*mul*tsk.v[k][i]%MOD),res.v[k][j]=pmod(res.v[k][j]-1ll*mul*res.v[k][i]%MOD);
		}
	}
	ffor(i,2,K) {
		int inv=Inv[i];
		ffor(j,1,i-1) {
			int mul=1ll*tsk.v[i][j]*inv%MOD;
			if(mul) ffor(k,1,K) tsk.v[k][j]=pmod(tsk.v[k][j]-1ll*mul*tsk.v[k][i]%MOD),res.v[k][j]=pmod(res.v[k][j]-1ll*mul*res.v[k][i]%MOD);
		}
	}
	ffor(i,1,K) {
		int inv=Inv[i];
		ffor(j,1,K) res.v[j][i]=(1ll*res.v[j][i]*inv)%MOD;	
	}
	return res;
}
Matrix mul(Matrix A,Matrix B,int id) { //只有 B 的 id 列比较特别
	Matrix res;
	ffor(i,1,K+1) ffor(j,1,K+1) {
		if(j!=id) res.v[i][j]=A.v[i][j];
		else {
			res.v[i][j]=0;
			ffor(k,1,K+1) res.v[i][j]=pmod(res.v[i][j]+1ll*A.v[i][k]*B.v[k][j]%MOD);
		}
	}
	return res;
}
Matrix Mul(Matrix A,Matrix B,int id) { //只有 A 的 id 列比较特别
	Matrix res;
	ffor(i,1,K+1) ffor(j,1,K+1) {
		res.v[i][j]=(1ll*A.v[i][i]*B.v[i][j])%MOD;
		if(i!=id) res.v[i][j]=pmod(res.v[i][j]+1ll*A.v[i][id]*B.v[id][j]%MOD);
	}
	return res;
}
signed main() {
	//freopen("subsequence.in","r",stdin);
	//freopen("subsequence.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>K,K++; int _2=(MOD+1)/2;
	ffor(i,1,K) pre[0].v[i][i]=anti[0].v[i][i]=1;
	double st=clock();
	ffor(i,1,n) {
		cin>>a[i];
		Matrix nw; memset(nw.v,0,sizeof(nw.v));
		ffor(j,1,K) nw.v[j][j]=1;	
		ffor(j,1,a[i]) nw.v[j][a[i]]=1;
		nw.v[K][a[i]]=1,nw.v[a[i]][a[i]]=2;
		pre[i]=mul(pre[i-1],nw,a[i]);
		ffor(j,1,a[i]-1) nw.v[j][a[i]]=-_2;
		nw.v[K][a[i]]=-_2,nw.v[a[i]][a[i]]=_2;
		anti[i]=Mul(nw,anti[i-1],a[i]);
	}
	// cout<<clock()-st<<'\n';
	cin>>q;
	ffor(i,1,q) {
		int l,r; cin>>l>>r;
		int ans=0;
		ffor(k,1,K) ffor(id,1,K) ans=pmod(ans+1ll*anti[l-1].v[K][id]*pre[r].v[id][k]%MOD);
		cout<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

在想到 $O(k^3)$ 的矩阵乘法可以变成 $O(k^2)$ 之前我尝试了很多常数优化。事实证明优化算法比优化常数来的快得多。

---

## 作者：detect (赞：3)


## [「USACO 2020.1 Platinum」Non-Decreasing Subsequences](https://loj.ac/problem/3247)

我们要快速求出多组询问一个区间内不下降序列的个数。（不过不同的数不超过20）

设计dp方程，$f[i][j]$表示左端点为i，有段点值为j的方案数。$g[i][j]$表示右端点为i，左端点值为j的方案数。

我们逆向思维，如何求出一个询问。

- 考虑拼接的思想，从这个询问中间的某一个点，只要知道从l[i]到mid的所有f[i][j]和mid+1到r[i]的所有g[i][j]，显然每一种要吗只在左边或只在右边（加一个空集即可），否则必定过mid，所有我们可以枚举拼接的地方，然后从l到mid左右f[l][i]之和乘上从r到mid+1所有g[r][j]（j>=i）之和就是答案。

所以对于每一个询问，我们只需知道任意一个在其中的点的所有f和g数组就可以O（n）求出答案。

但是我们现在有m个询问，如何找出这些mid且保证复杂度。

分治大法好。

考虑二分切割。

于是对于每一个l到r，我们预处理出mid的f，g数组，用数据结构总共$n*log_n^2$。

然后把过mid的所有询问处理掉。把在左侧和右侧的询问分开保证，分别分治即可。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int M=1e6+5;
int n,m,ans[M],tr[50005],a[M],k;
struct node{
	int l,r,id;
}q[M];
inline void add(int pos,int val){
	for(int i=pos;i<=n;i+=(i&-i)) tr[i]+=val,tr[i]%=mod;
}
inline int qusum(int pos){
	int sum=0;
	for(int i=pos;i>0;i-=(i&-i)) sum+=tr[i],sum%=mod;
	return sum;
}
queue <int> qu;
int f[50005][22],g[50005][22];
void cdq(int l,int r){
	if(qu.empty()) return;
	if(l==r){
		while(!qu.empty()){
			ans[q[qu.front()].id]=2;qu.pop();
		}return;
	}
	int mid=l+r>>1;
	for(int i=1;i<=k;i++){
		memset(tr,0,sizeof(tr));
		for(int j=mid;j>=l;j--) f[j][i]=qusum(k-a[j]+1)+(a[j]==i),add(k-a[j]+1,f[j][i]);
	}
	for(int i=mid-1;i>=l;i--) 
	  for(int j=1;j<=k;j++) f[i][j]+=f[i+1][j],f[i][j]%=mod;
	  
	for(int i=1;i<=k;i++){
		memset(tr,0,sizeof(tr));
		for(int j=mid+1;j<=r;j++) g[j][i]=qusum(a[j])+(a[j]==i),add(a[j],g[j][i]);
	}
	for(int i=mid+2;i<=r;i++)
	  for(int j=1;j<=k;j++) g[i][j]+=g[i-1][j],g[i][j]%=mod;
	for(int i=l;i<=mid;i++) f[i][1]++;
	for(int i=mid+1;i<=r;i++) g[i][k]++;
	queue <int> qw,qt;
	while(!qu.empty()){
		int i=qu.front();
		if(q[i].r<=mid) qt.push(i);
		else if(q[i].l>mid) qw.push(i);
		else
		  for(int j=1;j<=k;j++)  
		    for(int z=j;z<=k;z++) 
			  ans[q[i].id]+=f[q[i].l][j]*g[q[i].r][z],ans[q[i].id]%=mod;
	    qu.pop();  
	}
	while(!qt.empty()) qu.push(qt.front()),qt.pop();
	cdq(l,mid);
	while(!qu.empty()) qu.pop();
	while(!qw.empty()) qu.push(qw.front()),qw.pop();
	cdq(mid+1,r);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	cin>>m;
	for(int i=1;i<=m;i++) scanf("%lld%lld",&q[i].l,&q[i].r),q[i].id=i;
	for(int i=1;i<=m;i++) qu.push(i);
	cdq(1,n);
	for(int i=1;i<=m;i++) cout<<(ans[i]%mod+mod)%mod<<"\n";
	return 0;
}
```



---

## 作者：Sumikura (赞：2)

静态区间查询并且 $N$ 较小 $M$ 较大，容易想到猫树。

# 建树

考虑在猫树上做 dp，因为要考虑在查询时合并 $[l, mid]$ 和 $[mid + 1, r]$ 这两个区间，所以我们定义:

- 当 $i \leq mid$ 时：

  $dp_{dep, i, j}$ 表示在猫树深度为 $dep$ 时，在 $[i, mid]$ 的范围内，以 $i$ 为第一位，最后一位的值为 $j$ 的不下降子序列数量。

- 当 $mid < i$ 时：

  $dp_{dep, i, j}$ 表示在猫树深度为 $dep$ 时，在 $[mid + 1, i]$ 的范围内，第一位的值为 $j$，最后一位是 $i$ 的不下降子序列数量。

为了方便描述，之后所写的都是 $i \leq mid$ 的情况，另一种情况同理。

这里有一个 $O(N)$ 的转移：$dp_{dep, i, j} = \sum\limits^{mid}_{l = i + 1} (dp_{dep, l, j} \times [a_l > a_i])$。

> 注：此处及后文的中括号表示若括号中的表达式成立，表达式的值为 $1$，反之值为 $0$。

容易发现这样转移非常的不优秀，注意到值域 $k$ 是极小的，所以我们考虑定义 $sum_{dep, i, j, l}$ 表示在 $[i, mid]$ 的范围内，第一位的值为 $j$，最后一位的值为 $l$ 的不下降子序列数量。

于是有了 $O(K)$ 的转移方程：

$$dp_{dep, i, j} = \sum\limits ^ j _ {l = a_i} sum _ {dep, i, l, j}$$

$$sum_{dep, i, j, l} = sum_{dep, i + 1, j, l} + [j = a_i] \times \sum\limits ^ l _ {q = a_i} sum_{dep, i + 1, i + 1, q, l}$$

整个过程是 $O(N \times K ^ 2)$，建树时空复杂度为 $O(N \log N \times K ^ 2)$。

这样是会爆空间的，所以我们考虑把询问离线下来。我们对于询问按照深度从小到大排序，如果第 i 次询问的深度与第 $i - 1$ 次的深度不同，那么就建这一层。

因为深度排过序了，所以同一层不会建第二次，时间复杂度不变，空间复杂度少了个 $\log N$，变得可以接受。

# 处理询问

朴素查询：$O(K ^ 4)$ 暴力枚举 $i$，$j$，$q$，$p$，$res = \sum\limits ^ k _ {i = 1}\sum\limits ^ k _ {j = i}\sum\limits ^ k _ {q = j}\sum\limits ^ k _ {p = q}sum_{l, i, j} \times sum_{r, q, p} (i \leq j \leq q \leq p)$。

~~非常好做法，爱来自瓷器。~~

首先考虑怎么 $O(K ^ 2)$ 地去做：定义 $ans_{i, j}$ 表示在 $[mid + 1, i]$ 的范围内开头的值 $\geq j$，结尾的值 $\leq k$ 的不下降子序列数量。

那么递推式子是：
$$ans_{i, j} = \sum\limits ^ k _ {q = j} \sum\limits ^ k _ {p = q} sum_{i, q, p}$$

做个差即可得到：

$$ans_{i, j} - ans_{i, j + 1} = \sum\limits ^ k _ {q = j} \sum\limits ^ k _ {p = q} sum_{i, q, p} - \sum\limits ^ k _ {q = j + 1} \sum\limits ^ k _ {p = q} sum_{i, q, p}$$

$$ans_{i, j} - ans_{i, j + 1} = \sum\limits ^ k _ {q = j} sum_{i, j, q}$$

就可以愉快 $O(K ^ 2)$ 递推了。那么答案 $res = \left(\sum\limits ^ k _ {i = 1} \sum\limits ^ k _ {j = i} sum_{l, i, j} \times (ans_{r, j} + 1)\right) + ans_{r, 1} + 1$

事情到这步已经可以结束了，但是还可以做到 $O(K)$ 计算答案。我们再次观察计算答案的式子：

$$res = \left(\sum\limits ^ k _ {i = 1} \sum\limits ^ k _ {j = i} sum_{l, i, j} \times (ans_{r, j} + 1)\right) + ans_{r, 1} + 1$$

它也可以写成：

$$res = \left(\sum\limits ^ k _ {j = 1} \sum\limits ^ j _ {i = 1} sum_{l, i, j} \times (ans_{r, j} + 1)\right) + ans_{r, 1} + 1$$

利用乘法分配律打个括号：

$$res = \left(\sum\limits ^ k _ {j = 1} \left(\sum\limits ^ j _ {i = 1} sum_{l, i, j}\right) \times (ans_{r, j} + 1)\right) + ans_{r, 1} + 1$$

显然 $\sum\limits ^ j _ {i = 1} sum_{l, i, j}$ 可以预处理为 $ans_{l, i}$，最后得到式子：$res = \left(\sum\limits ^ k _ {j = 1} ans_{l, j} \times (ans_{r, j} + 1)\right) + ans_{r, 1} + 1$

~~撒花~~

但如果你按部就班一步一步做，会得到 `TLE` + `MLE` 的结果。

有没有发现一个问题：我们从头到尾计算 $sum$，推 $ans$，得到结果 $res$，都没有用到 $dp$ 数组。所以我们直接删掉就过了。

处理询问时间复杂度 $O(Q \times K)$

排序时间复杂度 $O(Q \log Q)$

总时间复杂度：$O(N \log N \times K ^ 2 + Q \log Q + Q K)$

CODE：
---

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5.0e+4 + 5, M = 2.0e+5 + 5, mod = 1.0e+9 + 7;
int n, k, m, a[N], len(1), lg2[N << 2];
int pos[N << 1], res[M], sum[N << 1][22][22], ans[N << 1][22];
struct node{int l, r, dep, id;}q[M];
inline int read()
{
    int x(0), f(1); char ch(getchar());
    while(!isdigit(ch))f = (ch == '-'? -1: f), ch = getchar();
    while( isdigit(ch))x = x * 10 + ch - '0' , ch = getchar();
    return x * f;
}
inline void build(int l, int r)
{
    if(l == r)return ;
    int mid((l + r) >> 1);
    if(mid >= n)return ;//切记一定要处理空间溢出，这题空间卡的紧
    sum[mid][a[mid]][a[mid]] = 1, sum[mid + 1][a[mid + 1]][a[mid + 1]] = 1;
    for(int i(1); i <= k; i++)for(int j(1); j <= i; j++)ans[mid][i] = (ans[mid][i] + sum[mid][j][i]) % mod;
    for(int i(1); i <= a[mid + 1]; i++)ans[mid + 1][i] = 1;
    for(int i(mid - 1); i >= l; i--)
    {
        for(int j(1); j <= k; j++)for(int l(j); l <= k; l++)
            sum[i][j][l] = sum[i + 1][j][l];
        sum[i][a[i]][a[i]] = (sum[i][a[i]][a[i]] + 1) % mod;
        for(int j(a[i]); j <= k; j++)
        {
            int num(0);
            for(int l(j); l >= a[i]; l--)num = (0ll + num + sum[i + 1][l][j]) % mod;
            sum[i][a[i]][j] = (0ll + sum[i][a[i]][j] + num) % mod;
        }
        for(int j(1); j <= k; j++)for(int l(1); l <= j; l++)ans[i][j] = (ans[i][j] + sum[i][l][j]) % mod;
    }
    for(int i(mid + 2); i <= r; i++)
    {
        if(i > n)break;//处理空间溢出
        for(int j(1); j <= k; j++)for(int l(j); l <= k; l++)
            sum[i][j][l] = sum[i - 1][j][l];
        sum[i][a[i]][a[i]] = (sum[i][a[i]][a[i]] + 1) % mod;
        for(int j(a[i]); j >= 1; j--)
        {
            int num(0);
            for(int l(j); l <= a[i]; l++)num = (0ll + num + sum[i - 1][j][l]) % mod;
            sum[i][j][a[i]] = (0ll + sum[i][j][a[i]] + num) % mod;
        }
        ans[i][k] = sum[i][k][k];
        for(int j(k - 1); j >= 1; j--)
        {
            ans[i][j] = ans[i][j + 1];
            for(int l(j); l <= k; l++)ans[i][j] = (ans[i][j] + sum[i][j][l]) % mod;
        }
    }
}
signed main()
{
    n = read(), k = read();
    for(int i(1); i <= n; i++)a[i] = read();
    for(;len < n; len <<= 1);
    lg2[1] = 1;
    for(int i(2); i <= (len << 1); i++)lg2[i] = lg2[i >> 1] + 1;
    for(int i(1); i <= n; i++)pos[i] = i + len - 1;
    m = read();
    for(int i(1); i <= m; i++)
    {
        int l(read()), r(read());
        q[i] = {l, r, lg2[pos[l]] - lg2[pos[l] ^ pos[r]], i};//预处理深度
    }
    sort(q + 1, q + m + 1, [&](node x, node y){return x.dep < y.dep;});//按深度排序
    for(int i(1); i <= m; i++)
    {
        if(q[i].l == q[i].r){res[q[i].id] = 2; continue;}// 若是只有一个点就特判
        int dep(q[i].dep);
        if(dep != q[i - 1].dep)
        {
            // 若是深度不同，那就把这一层新建出来
            memset(sum, 0, sizeof(sum)), memset(ans, 0, sizeof(ans));
            int num(len >> (dep - 1));
            for(int u(1); u <= (1 << (dep - 1)) && num * (u - 1) + 1 <= n; u++)build(num * (u - 1) + 1, num * u);
            // 这一步最多只会进行 logN 次，因为深度最多只有 logN层。
        }
        int num(0);
        for(int j(1); j <= k; j++)num = (1ll * ans[q[i].l][j] * (ans[q[i].r][j] + 1ll) % mod + num) % mod;
        res[q[i].id] = (1ll + num + ans[q[i].r][1]) % mod;
    }
    for(int i(1); i <= m; i++)cout << res[i] << "\n";
    return 0;
}
```

---

## 作者：Arghariza (赞：1)

先考虑单次询问，设 $f_{i,j}$ 表示考虑到 $i$，当前子序列末尾的数为 $j$ 的方案数，那么 $f_{i,j}\gets f_{i-1,j}(j\neq a_i),f_{i,a_i}\gets f_{i-1,a_i}+\sum\limits_{x\le a_i}f_{i-1,x}$。

写成矩阵的形式，$a_i=x$ 的转移矩阵 $A(x)$ 为：

$$A(x)_{i,j}=[i=j]+[i\le x \wedge j=x]$$

这个矩阵的乘法可以 $O(k^2)$ 维护出来，而计算答案只需要用一个向量乘矩阵，同样是 $O(k^2)$ 的。

于是使用猫树分治，每次处理经过分治区间中点的询问可以就可以做到 $O(k^2(n\log n+q))$。然而我们需要更优秀的复杂度。

接着考虑对 $A(x)$ 求逆，手玩一下可以得到：

$$A(x)^{-1}_{i,j}=[i=j]-\frac{1}{2}[i\le x\wedge j=x]$$

于是只需要求出 $A(a_i)$ 和 $A^{-1}(a_i)$ 的前缀积即可做到 $O(k^2(n+q))$。

实现时要注意左乘和右乘的区别。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int P = 1e9 + 7;
const int i2 = (P + 1) / 2;
const int N = 5e4 + 5;
const int K = 25;

int n, k, q;
int a[N], f[K], g[K];

struct M {
    int s[K][K];
    M () { memset(s, 0, sizeof(s)); }
    void init() { for (int i = 0; i <= k; i++) s[i][i] = 1; }
} s[N], is[N];

M operator * (const M &L, const int &R) {
    M res = L;
    for (int i = 0; i <= k; i++)
        for (int x = i; x <= R; x++)
            (res.s[i][R] += L.s[i][x]) %= P;
    return res;
}

M operator * (const int &L, const M &R) {
    M res = R;
    for (int i = 0; i <= L; i++)
        for (int j = 0; j <= k; j++)
            (res.s[i][j] += 1ll * (P - i2) * R.s[L][j] % P) %= P;
    return res;
}

void solve() {
	cin >> n >> k, s[0].init(), is[0].init();
    for (int i = 1; i <= n; i++) 
        cin >> a[i], s[i] = s[i - 1] * a[i], is[i] = a[i] * is[i - 1];
    cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        for (int i = 1; i <= k; i++) f[i] = 0; f[0] = 1;
        for (int i = 0; i <= k; i++) g[i] = 0; 
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
                (g[i] += 1ll * f[j] * is[l - 1].s[j][i] % P) %= P;
        for (int i = 0; i <= k; i++) f[i] = 0; 
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
                (f[i] += 1ll * g[j] * s[r].s[j][i] % P) %= P;
        int res = 0;
        for (int i = 0; i <= k; i++)
            (res += f[i]) %= P;
        cout << res << '\n';
    }
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# P6009 题解



**题目大意**

> 给数组 $a_1\sim a_n$，值域 $[1,k]$，$q$ 次询问区间上升子序列数。
>
> 数据范围：$n\le 5\times 10^5,k\le 20,q\le 2\times 10^5$。

**思路分析**

考虑 CDQ 分治，对于当前区间 $[l,mid],[mid+1,r]$，分别计算：

- 每个 $[i,mid]$ 中以 $j$ 结尾的 LIS 个数 $L_{i,j}$ 。
- 每个 $[mid+1,i]$ 中以 $j$ 开头的 LIS 个数 $R_{i,j}$。

具体实现时枚举 $i$，动态维护开头为 $j$ 结尾为 $k$ 的 LIS 个数。

对于一个跨越 $mid$ 的询问直接枚举左侧结尾与右侧开头，拼接前后缀回答，特判左右为空的情况。

时间复杂度 $\mathcal O(nk^2\log n+qk^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e4+5,MAXQ=2e5+5,MOD=1e9+7;
struct Query { int l,r,id; };
int m,a[MAXN],f[25][25],L[MAXN][25],R[MAXN][25],ans[MAXQ];
inline void add(int &x,int y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
inline void solve(int l,int r,const vector<Query>&Q) {
	if(Q.empty()) return ;
	if(l==r) { for(auto q:Q) ans[q.id]=2; return ; }
	int mid=(l+r)>>1;
	memset(f,0,sizeof(f));
	for(int i=mid;i>=l;--i) {
		for(int j=a[i];j<=m;++j) for(int k=j;k<=m;++k) add(f[a[i]][k],f[j][k]);
		memset(L[i],0,sizeof(L[i])),add(f[a[i]][a[i]],1);
		for(int j=1;j<=m;++j) for(int k=j;k<=m;++k) add(L[i][k],f[j][k]);
	}
	memset(f,0,sizeof(f));
	for(int i=mid+1;i<=r;++i) {
		for(int j=1;j<=a[i];++j) for(int k=a[i];k>=j;--k) add(f[j][a[i]],f[j][k]);
		memset(R[i],0,sizeof(R[i])),add(f[a[i]][a[i]],1);
		for(int j=1;j<=m;++j) for(int k=j;k<=m;++k) add(R[i][j],f[j][k]);
	}
	vector <Query> LQ,RQ;
	for(auto q:Q) {
		if(q.r<=mid) { LQ.push_back(q); continue; }
		if(mid<q.l)  { RQ.push_back(q); continue; }
		ans[q.id]=1;
		for(int j=1;j<=m;++j) add(ans[q.id],L[q.l][j]),add(ans[q.id],R[q.r][j]);
		for(int j=1;j<=m;++j) for(int k=j;k<=m;++k) add(ans[q.id],1ll*L[q.l][j]*R[q.r][k]%MOD);
	}
	solve(l,mid,LQ),solve(mid+1,r,RQ);
}
signed main() {
	int n,q;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	scanf("%d",&q);
	vector <Query> Q;
	for(int i=1,l,r;i<=q;++i) scanf("%d%d",&l,&r),Q.push_back({l,r,i});
	solve(1,n,Q);
	for(int i=1;i<=q;++i) printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：Anonymely (赞：0)

没啥思维难度。

首先 dp 转移显然能写出来，进而发现可以写成矩阵形式。

暴力的想法是猫树维护矩阵乘法，但是做一次矩阵乘法复杂度为 $O(n^3)$，还有猫树的 $\log$。

转移矩阵形如一个单位矩阵在加上一列，只有 $O(k)$ 个地方有值，于是矩阵乘法变成 $O(k^2)$，但是多个 $\log$ 还是不能过。

考虑一些其他想法，不用数据结构维护而是直接前缀和维护，$[l,r]$ 的乘积应该是 $pre_r \times inv_{l-1}$，其中 $pre_n = \prod_{i=1}^n w_i, inv_{n} = \prod_{i=n}^1 w_i^{-1}$，注意乘法顺序，因为矩阵没有结合律。

逆矩阵也是只有 $O(k)$ 个位置，预处理部分为 $O(k^2)$。

查询时是向量乘矩阵，$O(k^2)$。

总复杂度 $O(nk^2+qk^2)$，注意空间。

---

## 作者：daniEl_lElE (赞：0)

值域较小，考虑离线猫树分治。

每次分治取 $mid$ 后分别往两边计算选出一些位置使得其形成值域在 $[1,t]$ 或 $[t,k]$ 之间的不下降子序列。可以使用动态规划算出方案数。计算过程中记录 $f_{i,j,l}$ 表示看到 $i$ 位置，值域在 $[j,l]$ 中间，最后 $dp_{i,j}=\sum_{l=1}^jf_{i,l,j}$ 即可。（这里以左边为例，右边是镜像的）

每次询问时，只需要枚举左边和右边分别到多少或者只在一边的情况即可。也就是说 $ans=\sum_{i=1}^k\sum_{j=i}^kdp_{l,i}dp_{r,j}+\sum_{i=1}^kdp_{l,i}+\sum_{i=1}^kdp_{r,i}$。前缀和优化即可做到 $O(k^2n\log n+kq)$。具体细节可以见代码。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long 
using namespace std;
const int mod=1e9+7;;
int ans[200005];
struct qry{
	int l,r,pos;
}q[200005],tq[200005];
int a[50005];
int dp[50005][22][22],cnt[50005][22],tot[50005];
void solve(int l,int r,int ql,int qr){
	if(ql>qr) return ;
	if(l==r){
		for(int i=ql;i<=qr;i++){
			ans[q[i].pos]=1;
		}
		return ;
	}
//	cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<"\n";
	for(int i=l;i<=r;i++) memset(dp[i],0,sizeof(dp[i])),memset(cnt[i],0,sizeof(cnt[i])),tot[i]=0;
	for(int i=mid;i>=l;i--){
		if(i!=mid)
		for(int k=0;k<=21;k++){
			for(int j=0;j<=21;j++) dp[i][k][j]=dp[i+1][k][j];
			for(int j=a[i];j<=21;j++) (dp[i][k][a[i]]+=dp[i+1][k][j])%=mod;
		}
		dp[i][a[i]][a[i]]++;
		for(int k=0;k<=21;k++){
			for(int j=0;j<=k;j++) (cnt[i][k]+=dp[i][k][j])%=mod;
			if(k!=0) (cnt[i][k]+=cnt[i][k-1])%=mod;
		}
	}
	for(int i=mid+1;i<=r;i++){
		if(i!=mid+1)
		for(int k=0;k<=21;k++){
			for(int j=0;j<=21;j++) dp[i][k][j]=dp[i-1][k][j];
			for(int j=a[i];j>=0;j--) (dp[i][k][a[i]]+=dp[i-1][k][j])%=mod;
		}
		dp[i][a[i]][a[i]]++;
		for(int k=0;k<=21;k++){
			for(int j=k;j<=21;j++) (cnt[i][k]+=dp[i][k][j])%=mod;
			(tot[i]+=cnt[i][k])%=mod;
		}
	}
	int it1=ql-1,it2=qr+1;
	for(int i=ql;i<=qr;i++){
		if(q[i].l<=mid&&q[i].r>mid){
			int tmp=0;
			for(int j=0;j<=21;j++){
				(tmp+=cnt[q[i].l][j]*cnt[q[i].r][j])%=mod;
			}
			(tmp+=cnt[q[i].l][21]+tot[q[i].r])%=mod;
			ans[q[i].pos]=tmp;
		}
		else if(q[i].r<=mid) tq[++it1]=q[i];
		else if(q[i].l>mid) tq[--it2]=q[i];
	}
	for(int i=ql;i<=it1;i++) q[i]=tq[i];
	solve(l,mid,ql,it1);
	for(int i=qr;i>=it2;i--) q[i]=tq[i];
	solve(mid+1,r,it2,qr);
}
signed main(){
	int n,k; cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	int m; cin>>m;
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].pos=i;
	}
	solve(1,n,1,m);
	for(int i=1;i<=m;i++) cout<<ans[i]+1<<"\n";
	return 0;
}
```

---

