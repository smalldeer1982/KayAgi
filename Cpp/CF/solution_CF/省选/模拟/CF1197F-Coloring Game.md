# Coloring Game

## 题目描述

- 有 $n$ 条纸条，第 $i$ 个纸条被分成了 $a_i$ 个格子，编号从 $1$ 到 $a_i$，最开始每个格子是 $3$ 种颜色中的一种。  
- 游戏开始时，有 $n$ 个棋子放在每个纸条的第 $a_i$ 个格子（即最后一个格子）。然后两个玩家进行轮流操作，先不能操作者输。  
- 每次操作选择一枚棋子，向后移动 $1,2$ 或 $3$ 格。要求棋子不能越过纸条的边界，且若要从颜色为 $i$ 的格子向前移动 $j$ 个格子必须满足 $f_{i,j}=1$。  
- 现在有些格子是未进行过染色的，问有多少种染这些格子的方案，使得后手有必胜策略，对 $998244353$ 取模。

## 说明/提示

$1\le a_i\le10^9$，$1\le m\le1000$，$1\le x_i\le n$，$1\le y_i\le a_{x_i}$，$1\le c_i\le 3$， $0\le f_{i,j}\le1$。

## 样例 #1

### 输入

```
3
3 4 5
2
1 1 1
2 2 2
1 1 1
1 0 0
0 1 1
```

### 输出

```
14346
```

## 样例 #2

### 输入

```
1
1
1
1 1 1
1 1 1
1 1 1
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 1 1
1
1 1 1
1 1 1
1 1 1
1 1 1
```

### 输出

```
9
```

# 题解

## 作者：AsunderSquall (赞：1)

**题意**  
- 有 $n$ 条纸条，第 $i$ 个纸条被分成了 $a_i$ 个格子，编号从 $1$ 到 $a_i$，最开始每个格子是 $3$ 种颜色中的一种。  
- 游戏开始时，有 $n$ 个棋子放在每个纸条的第 $a_i$ 个格子（即最后一个格子）。然后两个玩家进行轮流操作，先不能操作者输。  
- 每次操作选择一枚棋子，向后移动 $1,2$ 或 $3$ 格。要求棋子不能越过纸条的边界，且若要从颜色为 $i$ 的格子向前移动 $j$ 个格子必须满足 $f_{i,j}=1$。  
- 现在有些格子是未进行过染色的，问有多少种染这些格子的方案，使得后手有必胜策略，对 $998244353$ 取模。  

**题解**  
博弈部分只要会 $sg$ 函数就非常简单，这里不再赘述，考虑 $sg$ 函数的转移。  
注意到 $a_i$ 比较大，而初始位置有颜色的点 $m$ 比较少，考虑用矩阵快速幂来加速转移。  
将当前位置，上一个位置，和上上个位置的 $sg$ 值压缩存下来，因为最多只有 $3$ 个位置可以选择，所以 $sg$ 函数的值不超过 $3$。那么压缩下来大小为 $4^3=64$，另其等于 $k$ 方便复杂度分析。    
我们可以构造 $3$ 个矩阵，分别表示颜色为 $1,2,3$ 以及未染色的时候的转移。注意到未染色时候的矩阵其实就是颜色为 $1,2,3$ 的矩阵相加。  
遇到断点的时候暴力乘法，其他段用矩阵快速幂，时间复杂度为 $O(k^3n \log a)$。无法通过此题。  
有一个套路，就是预处理出矩阵的二次幂，然后转移过去的时候用向量乘上长度的二进制拆分对应的矩阵，这样复杂度降为 $O(k^2 n \log a+ k^3 \log a)$，就可以过了。  

**代码**  
```
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define rd(x) x=read()
#define wt(x) write(x)
#define pos(x) (((x)-1)/SZ+1)
#define endl "\n"
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=1e6+5;
const int M=64;
const int mod=998244353;
int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-');x=-x;}if(x>=10)write(x/10);putchar(x%10+'0');}

void add(int &x,int y) {x+=y;if (x>=mod) x-=mod;}
int n,m,a[N],f[4][4],ans[N][4];
vector<pii> v[N];
struct Mat{int e[M][M];int* operator [](int p){return e[p];}}pw[M],col[4],tmp;
Mat operator + (Mat a,Mat b){Mat c;for (int i=0;i<M;i++) for (int j=0;j<M;j++) c[i][j]=(a[i][j]+b[i][j])%mod;return c;}
Mat operator * (Mat a,Mat b){Mat c;for (int i=0;i<M;i++) for (int j=0;j<M;j++) c[i][j]=0;for (int k=0;k<M;k++) for (int i=0;i<M;i++) if (a[i][k]) for (int j=0;j<M;j++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;return c;}
void ksm(Mat &x,int y){for (int i=0;i<=30;i++) if (y>>i&1) x=x*pw[i];}
int F(int c,int S){for (int i=0;i<=3;i++) if((!f[c][3] || (S&3^i)) && (!f[c][2] || (S>>2&3^i)) && (!f[c][1] || (S>>4^i))) return S>>2|i<<4;}

signed main()
{
    rd(n);for (int i=1;i<=n;i++) rd(a[i]);
    rd(m);for (int i=1,x,y,c;i<=m;i++) rd(x),rd(y),rd(c),v[x].push_back(mp(y,c));
    for (int i=1;i<=3;i++) for (int j=1;j<=3;j++) rd(f[i][j]);
    for (int i=1;i<=3;i++) for (int S=0;S<M;S++){int x=F(i,S);col[i][S][x]++;pw[0][S][x]++;}
    for (int i=1;i<=30;i++) pw[i]=pw[i-1]*pw[i-1];
    ans[0][0]=1;for (int i=1;i<=n;i++) sort(v[i].begin(),v[i].end());
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<M;j++) for (int k=0;k<M;k++) tmp[j][k]=0;tmp[0][63]=1;
        int la=1;for (pii p:v[i]) ksm(tmp,p.fi-la),tmp=tmp*col[p.se],la=p.fi+1;
        ksm(tmp,a[i]+1-la);for (int j=0;j<=3;j++) for (int S=0;S<M;S++) add(ans[i][j^(S>>4)],ans[i-1][j]*tmp[0][S]%mod);
    }
    cout<<ans[n][0]<<endl;
}
```



---

## 作者：Inui_Sana (赞：0)

讲一点不同做法&常数优化。

首先既然有 $n$ 个游戏，那么显然需要求每个游戏的 sg 值再套 sg 定理。则最后一步一定是，对于每个游戏求出 $f_{i,j}$ 表示第 $i$ 个游戏，$sg=j$ 的概率后，再设 $dp_{i,j}$ 表示前 $i$ 个游戏，当前 sg 值的异或和为 $j$ 的方案数。

此时注意到，对于一个游戏的一个局面，它的后继状态最多有 $3$ 个，于是 $sg\le 3$。这样最后一步 dp 的复杂度就是可以接受的了。

于是只需要求 $f_{i,j}$。对于一个游戏，显然可以设 $dp_{i,x,y,z}$ 表示当前在第 $i$ 个格子上，第 $i/i-1/i-2$ 个格子的 $sg$ 值分别为 $x,y,z$ 的方案数。转移是显然的。

然后由于 $a_i\le 10^9$，不难想到可以构造矩阵转移。构造的方法就是枚举 $x,y,z$，再根据下一个格子填什么颜色求 $sg_{i+1}$，转移到 $sg_{i+1},y,z$。

然后对于一个游戏，转移就形如乘上若干个任意颜色的矩阵，再乘上一个指定颜色的矩阵。矩阵快速幂即可做到 $O((n+m)k^3\log V)$，$k=64$。差了一些。

此时先想了一点常数优化：实际上有用的状态并没有 $64$ 个，大概是 $40$ 多个。但是这样似乎过不去第 $34$ 个点。

那就另外考虑一些优化：注意到我们的瓶颈在于求一个固定矩阵的次幂，快速幂不行，那就光速幂。具体地，预处理出这个矩阵的 $i,i\times 10^3,i\times 10^6(i\le 10^3)$ 次幂，于是后面单次就是 $O(1)$ 的了。

于是复杂度变成 $O(Bk^3+(n+m)k^3)(B=10^3,k\le 50)$。可以通过。

当然题解区里另一个做法要更厉害一点，也可以和这个做法相结合获得更好一点的复杂度。

code：

```cpp
int n,m,k,B=1e3,a[N],b[4][4],id[4][4][4],dp[N][4];
vector<pii> g[N];
queue<tuple<int,int,int>> q;
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
struct mat{
	int a[51][51];
	mat(){
		mems(a,0);
	}
	mat operator+(const mat &rhs)const{
		mat r;
		rep(i,0,k-1){
			rep(j,0,k-1){
				r.a[i][j]=Mod(a[i][j],rhs.a[i][j]);
			}
		}
		return r;
	}
	mat operator*(const mat &rhs)const{
		mat r;
		rep(i,0,k-1){
			rep(l,0,k-1){
				rep(j,0,k-1){
					r.a[i][j]=Mod(r.a[i][j],1ll*a[i][l]*rhs.a[l][j]%mod);
				}
			}
		}
		return r;
	}
}tran[4],sig,f[3][N];
il mat qpow(int x){
	return f[0][x%B]*f[1][x/B%B]*f[2][x/B/B];
}
void init(){
	id[3][2][1]=k=1;
	q.emplace(3,2,1);
	while(q.size()){
		auto [x,y,z]=q.front();
		q.pop();
		rep(i,1,3){
			int t=0;
			rep(j,0,3){
				if((x!=j||!b[i][1])&&(y!=j||!b[i][2])&&(z!=j||!b[i][3])){
					t=j;
					break;
				}
			}
			if(id[t][x][y]){
				continue;
			}
			id[t][x][y]=++k;
			q.emplace(t,x,y);
		}
	}
}
void Yorushika(){
	read(n);
	rep(i,1,n){
		read(a[i]);
	}
	read(m);
	while(m--){
		int x,y,k;read(x,y,k);
		g[x].eb(y,k);
	}
	rep(i,1,3){
		rep(j,1,3){
			read(b[i][j]);
		}
	}
	init();
	rep(i,0,k-1){
		sig.a[i][i]=1;
	}
	rep(p,1,3){
		rep(i,0,3)rep(j,0,3)rep(k,0,3){
			if(!id[i][j][k]){
				continue;
			}
			int t=0;
			rep(l,0,3){
				if((i!=l||!b[p][1])&&(j!=l||!b[p][2])&&(k!=l||!b[p][3])){
					t=l;
					break;
				}
			}
			assert(id[t][i][j]);
			tran[p].a[id[i][j][k]-1][id[t][i][j]-1]=1;
		}
		tran[0]=tran[0]+tran[p];
	}
	f[0][0]=f[1][0]=f[2][0]=sig;
	rep(i,1,B){
		f[0][i]=f[0][i-1]*tran[0];
	}
	rep(i,1,B){
		f[1][i]=f[1][i-1]*f[0][B];
	}
	rep(i,1,B){
		f[2][i]=f[2][i-1]*f[1][B];
	}
	dp[0][0]=1;
	rep(i,1,n){
		sort(g[i].begin(),g[i].end());
		mat s;
		s.a[0][id[3][2][1]-1]=1;
		int lst=0;
		for(auto [j,k]:g[i]){
			s=s*qpow(j-lst-1)*tran[k];
			lst=j;
		}
		s=s*qpow(a[i]-lst);
		rep(x,0,3)rep(y,0,3)rep(z,0,3){
			if(!id[x][y][z]){
				continue;
			}
			rep(j,0,3){
				dp[i][j^x]=Mod(dp[i][j^x],1ll*dp[i-1][j]*s.a[0][id[x][y][z]-1]%mod);
			}
		}
	}
	printf("%d\n",dp[n][0]);
	cerr<<k<<'\n';
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

