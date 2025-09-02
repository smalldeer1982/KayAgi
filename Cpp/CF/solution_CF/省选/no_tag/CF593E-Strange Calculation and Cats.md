# Strange Calculation and Cats

## 题目描述

## 题目翻译

LBW 有一张 $n\times m$ 的网格图，有一只猴子初始在$(1,1)$。

猴子每秒钟可以移动一格，或者不动。

LBW 有 $T$ 次操作，每一次询问想知道不同的内容，如下。

+ 操作一：询问第 $i$ 秒时，猴子走到 $(x, y)$ 的方案数。
+ 操作二：第 $i$ 秒，$(x, y)$ 出现了障碍，不能走在障碍上。
+ 操作三：第 $i$ 秒，$(x, y)$ 出的障碍消失了。

对于所有操作一，告诉 LBW 方案数。

## 说明/提示

- $n \times m \le 20$；
- $1 \le T \le 10^4$；
- 每次操作，保证 $op \in \{1, 2, 3\}$，$1 \le x \le n$ 并且 $1 \le y \le m$，$i \le 10^9$。
- 保证每个格子最多只有一个障碍，且 $i$ 是递增的。

## 样例 #1

### 输入

```
1 3 3
2 1 2 3
3 1 2 5
1 1 1 7
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3 3
2 2 2 2
1 3 3 5
1 3 3 7
```

### 输出

```
2
42
```

## 样例 #3

### 输入

```
4 5 5
2 2 5 3
2 2 4 6
3 2 4 9
1 4 4 13
1 4 4 15
```

### 输出

```
490902
10598759
```

# 题解

## 作者：封禁用户 (赞：8)

远古 $2400$ 也就这样？

首先先把地图压成一维的。我们可以构造一个 $nm \times nm$ 的矩阵，如果我现在在 $(i,j)$ 点，我就可以去到 $(i,j),(i+1,j),(i-1,j),(i,j-1),(i,j+1)$，对应的在矩阵中 

$$((i-1)\times m+j,(i-1)\times m+j-1)$$

$$((i-1)\times m+j,(i-1)\times m+j+1)$$

$$((i-1)\times m+j,(i-2)\times m+j)$$

$$((i-1)\times m+j,i\times m+j)$$

这些位置都要标为 $1$。

因为时间升序排列，会存在 $n+1$ 个段，这每一个段中不能走的位置是相同的，于是我们就可以在每一段中矩阵快速幂。至于处理不能到达的点，拿一个 vis 数组记录一下，如果 $vis_{i,j}$ 存在值，那矩阵中 $(i-1)\times m+j$ 这一列都不能用来转移值（因为本都应该是 $0$）。这里的证明很好证，请读者自行理解。 

然后就没了。设 $W$ 为值域 $10^9$，时间复杂度 $\mathcal{O}(n^2m^2T\log_2(W\div T))$。

感谢大佬 @mayike 教萌新算复杂度！

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(long long i=j;i<=n;i++)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define pb push_back
#define XQZ
using namespace std;
const int mod=1e9+7;
int vis[25];
struct abc{
	int jz[25][25],n,m,kd[25];
	void init(int ns,int ms){
		n=ns,m=ms;
		f(i,0,20)f(j,0,20)jz[i][j]=0;
		f(i,0,20)kd[i]=0;
	}
	friend abc operator *(abc a,abc b){
		abc c;c.init(a.n,b.m);
		f(i,1,a.n){
			f(j,1,a.m){
				f(k,1,b.m){
					if(a.kd[k]||vis[k]||vis[j]){c.jz[i][k]+=0;continue;};
					c.jz[i][k]=(c.jz[i][k]+a.jz[i][j]*b.jz[j][k]%mod)%mod;
				}
			}
		}
		return c;
	}
}it,oc,cl;
int n,m,T;
inline abc K(abc a,int b){
	abc c;c=cl;c.n=c.m=a.n;
	while(b){
		if(b&1)c=c*a;
		a=a*a;
		b>>=1;
	}
	return c;
}
void gs(){
	cin>>n>>m>>T;
	cl.init(n*m,n*m);
	f(i,0,n*m)cl.jz[i][i]=1;
	oc.init(n*m,n*m);
	it.init(1,n*m);
	it.jz[1][1]=1;
	f(i,1,n){
		f(j,1,m){
			oc.jz[(i-1)*m+j][(i-1)*m+j]=1;
			if(j!=1)oc.jz[(i-1)*m+j][(i-1)*m+j-1]=1;
			if(j!=m)oc.jz[(i-1)*m+j][(i-1)*m+j+1]=1;
			if(i!=1)oc.jz[(i-1)*m+j][(i-2)*m+j]=1;
			if(i!=n)oc.jz[(i-1)*m+j][(i)*m+j]=1;
		}
	}
	int lst=1;
	f(i,1,T){
		int opt,x,y,tim;
		cin>>opt>>x>>y>>tim;
		abc uu=K(oc,tim-lst);
		it=it*uu;lst=tim;
		if(opt==1){
			cout<<max(0ll,it.jz[1][(x-1)*m+y])<<endl;
		}else if(opt==2){
			it.kd[(x-1)*m+y]=1;
			vis[(x-1)*m+y]=1;
			it.jz[1][(x-1)*m+y]=0;
		}else{
			vis[(x-1)*m+y]=0;
		}
	}
}
signed main(){
#ifndef XQZ
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
#ifdef NXD
	int t=0;cin>>t;while(t--)
#endif
		gs();
	return 0;
}
```

---

## 作者：GGMU (赞：1)

&emsp;&emsp;题目大意：给你一张n\*m个的网格图，初始在（1,1），每秒钟可以移动一个单位或者不动，现在有q次操作，有三种操作，1操作：问到第t秒的时候，有多少种方法走到点$(x_{i},y_{i})$，2操作：从t秒开始，点$(x_{i},y_{i})$有一只猫，所以不能走到该点，3操作：从t秒开始，点$(x_{i},y_{i})$的猫走了，又可以重新到这个点了。保证每个点最多只有一只猫，且t是递增的。

&emsp;&emsp;解题思路：看到题目相信很多人会想到dp，但是看下t范围肯定不行。但是我们可以可以看到n和m非常小，只有20。先科普一下离散数学的知识，假设目前有n个点，我们设置大小为n\*n的矩阵r，其中$r_{ij}$表示第i个点到第j个点的路径数，当然本题路径数肯定都是1。接下来，左矩阵l为1\*n的矩阵，$l_{1j}$表示当前时间状态下，到各个点的方案数。0s时自然就是$(1,0,0,0,....)$了，接下来，我们只要计算 $l*$$r^{t}$,就可以知道t秒后到各个点的方案（大家可以自行验证一下，本质还是dp的思想）。而对于矩阵$r^{t}$，我们只需要矩阵快速幂计算一下即可。当有猫进入某点时，这个点的方案数清0，与其相连的边也都删除，而当猫又回来的时候，它和其他没有猫相连的边也可以加回来。

&emsp;&emsp;时间复杂度$O(qn^{3}logt)$，给了4秒，完全能过。

最后贴上AC代码

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <ll,ll> pii;
#define rep(i,x,y) for(int i=x;i<y;i++)
#define rept(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define se second
#define mes(a,b) memset(a,b,sizeof a)
#define mp make_pair
#define dd(x) cout<<#x<<"="<<x<<" "
#define de(x) cout<<#x<<"="<<x<<"\n"
#define debug() cout<<"I love Miyamizu Mitsuha forever.\n"
const int inf=0x3f3f3f3f;
const int mod=1e9+7;

int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
int n,m,q;

class Matrix
{
	public:
		ll matrix[40][40];
		int sz;
	void show()
	{
		rep(i,0,sz)
		{
			rep(j,0,sz) cout<<matrix[i][j]<<" ";
			cout<<"\n";
		}
	}
}way,dp;
Matrix mul(Matrix a,Matrix b)//矩阵乘法 
{
	Matrix ans;
	ans.sz=a.sz;
	mes(ans.matrix,0);
	rep(i,0,a.sz)
		rep(j,0,a.sz)
			rep(k,0,a.sz)
				ans.matrix[i][j]=(ans.matrix[i][j]+(ll)a.matrix[i][k]*b.matrix[k][j])%mod;
	return ans;
}
Matrix qpow(Matrix mat,int k)//矩阵快速幂 
{
	Matrix ans=mat;
	k--;
	for(;k;k>>=1,mat=mul(mat,mat))
		if(k&1) ans=mul(ans,mat);
	return ans;
}

bool cat[25][25];//记录有没有猫 
void init()
{
	dp.matrix[0][0]=1;
	dp.sz=way.sz=n*m;
	rep(i,0,n)
	{
		rep(j,0,m)
		{
			rep(k,0,4)
			{
				int goi=i+dx[k],goj=j+dy[k];
				if(goi<0||goi>=n||goj<0||goj>=m) continue;//防止越界 
				way.matrix[i*m+j][goi*m+goj]=1;//和相邻的边建一条边 
			}
			way.matrix[i*m+j][i*m+j]=1;//可以留在原地！
		}
	}
}

int main()
{
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>q;
	int tnow=1;
	init();//初始化建立左矩阵dp，距离到各个点方案数，建立右矩阵way，记录各点之间路径数 
	rep(i,0,q)
	{
		int op,x,y,t;
		cin>>op>>x>>y>>t;
		x--,y--;
		if(op==1)
		{
			dp=mul(dp,qpow(way,t-tnow));//更新状态 
			cout<<dp.matrix[0][x*m+y]<<"\n";//输出到该点方案即可 
		}
		else if(op==2)
		{
			dp=mul(dp,qpow(way,t-tnow)); 
			dp.matrix[0][x*m+y]=0;//到该点方案为0 
			way.matrix[x*m+y][x*m+y]=0;
			cat[x][y]=1;
			rep(j,0,4)
			{
				int gox=x+dx[j],goy=y+dy[j];
				if(gox<0||gox>=n||goy<0||goy>=m) continue;
				int id1=x*m+y,id2=gox*m+goy;
			//	dd(id1);de(id2);
				way.matrix[id1][id2]=way.matrix[id2][id1]=0;//该点无法通享其他的点，删除路径 
			}
		}
		else
		{
			dp=mul(dp,qpow(way,t-tnow));
			cat[x][y]=0;
			way.matrix[x*m+y][x*m+y]=1;
			rep(j,0,4)
			{
				int gox=x+dx[j],goy=y+dy[j];
				if(gox<0||gox>=n||goy<0||goy>=m) continue;
				int id1=x*m+y,id2=gox*m+goy;
				if(cat[x][y]==0&&cat[gox][goy]==0)way.matrix[id1][id2]=way.matrix[id2][id1]=1;//将四周点进行判断，没有猫的可以的重新连边 
			}
		}
		tnow=t;//更新当前时间 
	}
	return 0;
}
```


---

