# [ABC214G] Three Permutations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc214/tasks/abc214_g

$ (1,\ \dots,\ N) $ の順列 $ p\ =\ (p_1,\ \dots,\ p_N),\ q\ =\ (q_1,\ \dots,\ q_N) $ が与えられます。

$ (1,\ \dots,\ N) $ の順列 $ r\ =\ (r_1,\ \dots,\ r_N) $ であって、全ての $ i\ \,\ (1\ \leq\ i\ \leq\ N) $ に対し $ r_i\ \neq\ p_i $ かつ $ r_i\ \neq\ q_i $ となるようなものの総数を $ (10^9\ +\ 7) $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ p_i,\ q_i\ \leq\ N $
- $ p_i\ \neq\ p_j\ \,\ (i\ \neq\ j) $
- $ q_i\ \neq\ q_j\ \,\ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 1

$ (3,\ 4,\ 1,\ 2),\ (3,\ 4,\ 2,\ 1),\ (4,\ 3,\ 1,\ 2),\ (4,\ 3,\ 2,\ 1) $ の $ 4 $ つが条件を満たします。

### Sample Explanation 2

答えが $ 0 $ になることもあります。

### Sample Explanation 3

$ (10^9\ +\ 7) $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
4
1 2 3 4
2 1 4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 2 3
2 1 3```

### 输出

```
0```

## 样例 #3

### 输入

```
20
2 3 15 19 10 7 5 6 14 13 20 4 18 9 17 8 12 11 16 1
8 12 4 13 19 3 10 16 11 9 1 2 17 6 5 18 7 14 20 15```

### 输出

```
803776944```

# 题解

## 作者：0xyz (赞：14)

“组合意义天地灭”。

看见大家求还上删点写的都是动态规划，那我就来天地灭一下。我觉得这一题组合做法比较巧妙，码量也大幅度降低。

做法学习于[这篇题解](https://www.cnblogs.com/ak-dream/p/AK_Dream123.html)。

我们可以尝试求一下对于 $k={1,2,…,n}$，我们只看 $k$ 个条件，都没被满足的残存排列 $r'$ 的个数 $f_{k}$（注意 $r'$ 是指 $n$ 中选出 $k$ 个不同的数后进行排列）。并且我们在将一个 $r'$ 对应成 $r$ 时，假设 $r'$ 对于条件 $i_1,i_2,…,i_k$ 不满足，那么 $r'$ 就对应着 $r_{i_1},r_{i_2},…,r_{i_k}$。由于剩下的 $n-k$ 个数有 $(n-k)!$ 种排法，由容斥原理，最后的答案就是

$$\sum\limits_{k=0}\limits^n (-1)^kf_k(n-k)!$$

然后我们发现，只要求出 $f_k$ 就可以啦。

那么怎么求这个 $f_k$ 呢？

我们只要考虑 $k$ 个数就行了，先指定 $k$ 个不满足的条件是 $i_1,i_2,…,i_k$。我们凭空变出 $n$ 个标号为 $1,2,…,n$ 的点，将所有 $p_{i_j}$ 与 $q_{i_j}$ 相连，得到一个由 $n$ 个点，$k$ 条边组成的图。容易知道，这个图的度数最大为 $2$。所以它一定由链、环（自环）组成。

对于这样的一张图，对 $f_k$ 的贡献是多少呢？我们将连接 $p_{i_j}$ 和 $q_{i_j}$ 的边作为 $r_{i_j}$，也就是 $r'_j$。然后由于 $r'$ 必须不满足这 $k$ 个条件，所以 $r'_j$ 必须等于 $p_{i_j}$ 和 $q_{i_j}$ 二者之一。

所以总贡献就是任选 $i_1,i_2,…,i_k$ 对应的边，然后在这 $k$ 条边上标上端点上的数之一，并且所有标的数都不一样的方法数。

现在换一个思路。我们令 $k=n$，将所有 $p_i$ 和 $q_i$ 相连。此时，图上所有点的度数都是 $2$，所以整个图是由一个一个的环（自环）组成的。

我们假设已经处理了若干个环，这些环一共有 $s$ 个点，然后又出现一个新的环，这个环上有 $c$ 个点。

假设我们处理完 $s$ 个点之后的是 $f$，处理完 $s+c$ 个点之后的数组是 $g$，然后直接滚动数组。

如果 $c=1$，也就是这是一个自环，那么对于 $s+c$ 个点的那些环，可以不选这个自环，也就是 $f_j$，也可以选这一个自环上的唯一一条边，并且无论之前怎么选，能且只能标上这个自环上唯一一个点的编号，也就是 $f_{j-1}$。所以转移方程是（刷表法）

$$g_j=f_j+f_{j-1}$$

如果 $c>1$，也就是这是一个货真价实的环，那么我们枚举，在原本 $s$ 条边中选 $j$ 条边，在新的 $c$ 条边中选 $k$ 条边并且按照规则标上数的方案数。由于原本的 $s$ 条边和新的 $c$ 条边在不同的环上，所以这两玩意互不干扰，可以将选边并标号的方法数相乘。原本的 $s$ 条边中选出 $j$ 条边并标号的方法数是 $f_j$，那么问题就转换成了要在一个 $c$ 条边的环上选择 $k$ 条边并进行标号。

针对这个组合问题，我们先将一条边 $(u,v)$ 拆成两条边 $(u,w)$ 和 $(w,v)$。

在原问题中，选择了边 $(u,v)$ 并且标上 $u$，就对应在新的环中选择边 $(u,w)$；选择了边 $(u,v)$ 并且标上 $v$，就对应在新的环中选择边 $(w,v)$。

那么问题就转换成给你一个有 $2c$ 条边的环中选择两两不相邻的 $k$ 条边。

可以分类讨论。在环上编号最小的点设为 $a$，其逆时针的第一个点是 $b$。

①不选择 $(a,b)$，那么我们要在剩下的 $2c$ 个点，$2c-1$ 条边的链中选出 $k$ 条不相邻的边。那么我们可以看做是先从 $2c-k$ 个点中选出 $k$ 个右端点，再将 $k$ 个左端点按顺序插在它们前面。所以是 $C_{2c-k}^k$。

②选择 $(a,b)$，那么与它相邻的两条边都不能选，那么我们要在剩下的 $2c-2$ 个点，$2c-3$ 条边的链中选出 $k-1$ 条不相邻的边。所以是 $C_{2c-2-(k-1)}^{k-1}=C_{2c-k-1}^{k-1}$。

所以转移方程就是（填表法）

$$g_{j+k}=g_{j+k}+f_j\times \big(C_{2c-k}^k+C_{2c-k-1}^{k-1}\big)$$

那么这道题就做完了，时间复杂度是 $O(\sum c^2)$，最坏情况下是 $O(n^2)$。

代码不长，轻度压行。

```cpp
#include<bits/stdc++.h>
#define D(x,y) for(ll x=y;~x;x--)
#define U(x,y) for(ll x=1;x<=y;x++)
using namespace std;
typedef long long ll;
const ll M=1000000007,_=6010;
ll n,m,p[_],q[_],r[_],f[_],g[_],v[_],c,s,A;
inline ll C(ll x,ll y){return x<0||y<0||x<y?0:p[x]*q[x-y]%M*q[y]%M;}
int main(){
	cin>>n;m=n*2+1;p[0]=q[m]=f[0]=1;
	U(i,n)cin>>p[i];
	U(i,n)cin>>r[p[i]];
	U(i,m)p[i]=p[i-1]*i%M;
	for(ll i=M-2,j=p[m];i;i>>=1,j=j*j%M)
		if(i&1)q[m]=q[m]*j%M;
	D(i,m-1)q[i]=q[i+1]*(i+1)%M; 
	U(i,n)if(!v[i]){
		for(ll j=i;!v[j];j=r[j])c++,v[j]=1;
		if(c==1)for(ll j=s+1;j;j--)f[j]=(f[j]+f[j-1])%M;
		else{
			memset(g,0,_*4);
			D(j,s)D(k,c)g[j+k]=(g[j+k]+f[j]*(C(2*c-k,k)+C(2*c-k-1,k-1)))%M;
			memcpy(f,g,_*4);
		}
		s+=c;c=0;
	}
	D(i,n)A=i&1?(A-p[n-i]*f[i]%M+M)%M:(A+p[n-i]*f[i])%M;
	cout<<A<<'\n';
	return 0;
}
```


---

## 作者：EuphoricStar (赞：9)

比较平凡的一个容斥。

考虑把问题转化成，求 $\forall i \in [1, n], r_i \ne i \land r_i \ne p_i$ 的 $r$ 方案数。考虑到不弱于错排，所以容斥。设钦定 $i$ 个 $r_i$ 取了 $i, p_i$ 中的一个的方案数为 $f_i$，其余任意，那么：

$$ans = \sum\limits_{i = 0}^n (-1)^i f_i (n - i)!$$

考虑求 $f_i$。连边 $i \to p_i$，对每个环单独考虑。设第 $i$ 个环点数为 $s_i$。这个东西抽象到环上就相当于，每一个点，可以不选，可以选择选它自己，也可以选择选它在环上的下一个点。设 $h_{i, j, 0/1}$ 表示当前考虑到环上第 $i$ 个点，有 $j$ 个点选了，这个点是否选择第 $i + 1$ 个点。枚举第一个点的状态，然后直接做即可。合并到 $f_i$，就是做一个加法卷积，暴力即可。

总时间复杂度 $O(\sum s_i^2 + n \sum s_i) = O(n^2)$。

[code](https://atcoder.jp/contests/abc214/submissions/41890357)

---

## 作者：Iam1789 (赞：9)

考虑容斥，设构造出来的排列为 $r$，令第 $i$ 条限制为 $r_i \neq p_i,r_i \neq q_i$，$h_i$ 为只看其中 $i$ 条限制，均不满足的方案数，则答案为 $\sum_{i=0}^n (-1)^i h_i (n-i)!$。

考虑如何求出 $h$。对于每对 $p_i,q_i$，从 $p_i$ 向 $q_i$ 连边，可以得到若干个环，每条限制对应一条边，$r_i$ 则相当于第 $i$ 条边对应这 $r_i$ 这个点。若不满足某一条限制，则相当于这条边对应了起点或者终点。则 $h_i$ 为选择 $i$ 条边，求他们对应点的方案数。

先考虑单独的一个环。设环大小为 $n$，选择 $i$ 条边，则会形成 $\max(i-1,1)$ 个连通块。当 $i=0$ 时，整个环都被选择，则每条边要么都选择起点，要么选择终点，总方案数为 $2$。在 $i>1$ 时，环会被分成若干条链，对于每一条链，选择一个点，起点方向的边都选起点，终点方向的边都选终点，因此总方案数为链的大小。不同的链之间互相独立，因此多条链的总方案数为链大小的积。

设 $dp_{n,m}$ 表示将一条大小为 $n$ 的链删掉 $m$ 条边的总贡献（即选择 $n-m$ 条边对应点的方案数）。枚举最后一个点对应的连通块大小 $i$，有 $dp_{n,m}=\sum_{i=1}^n dp_{n-i,m-1}i$。动态维护后面的式子，具体方式可见代码，转移时间复杂度可做到 $\Theta(1)$，这部分总时间复杂度为 $\Theta(n^2)$。

设 $f_{n,m}$ 为将一个大小为 $n$ 的环删掉 $m$ 条边的总贡献，$m=0$ 时，$f_{n,m}=2$，否则枚举 $1$ 所在的联通块，设其大小为 $i$，则一共会有 $i$ 种大小为 $i$ 的联通块， $f_{n,m}=i^2 dp_{n-i,m-1}$。可以利用上面类似的方式动态维护做到 $\Theta(1)$ 转移，这部分总时间复杂度 $\Theta(n^2)$。

设第 $i$ 个环大小为 $v_i$，设 $g_{n,m}$ 为只看前 $n$ 个环，删掉 $m$ 条边的总贡献。设最后一个环删 $i$ 条边，不同环之间互相独立，因此 $g_{n,m}=\sum_{i=0}^{v_n} g_{n-1,m-i}f_{v_n,i}$。这玩意看起好像是 $\Theta(n^3)$ 的，并且貌似需要一个 `NTT` 优化，但是仔细想一下其实复杂度是对的。转移到 $i$ 的复杂度为 $\Theta(v_nn)$，这部分总时间复杂度为 $\Theta(n\sum v)=\Theta(n^2)$。

整个做法的总时间复杂度为 $\Theta(n^2)$，可以通过。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		f=-1;
		c=getchar(); 
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*f;
}
int n;
int p[3007],q[3007];
int ne[3007],la[3007];
vector <int> d;
bool vis[3007];
long long jc[3007];
long long dp[3007][3007],f[3007][3007],g[3007][3007],h[3007];
const int mod=1e9+7;
int main()
{
	n=read();
	jc[0]=1;
	for(int i=1;i<=n+1;++i)
	dp[1][i]=i,jc[i]=jc[i-1]*i%mod;
	for(int j=2;j<=n+1;++j)
	{
		long long sum1=0,sum2=0;
		sum1=sum2=dp[j-1][j-1];
		for(int i=j;i<=n+1;++i)
		dp[j][i]=sum2,sum1=(sum1+dp[j-1][i])%mod,sum2=(sum2+sum1)%mod;
	}
	for(int i=1;i<=n;++i)
	f[1][i]=i*i%mod,f[0][i]=2;
	for(int j=2;j<=n;++j)
	{
		long long sum1=dp[j-1][j-1],sum2=dp[j-1][j-1],sum3=dp[j-1][j-1];
		for(int i=j;i<=n;++i)
		{
			f[j][i]=sum3;
			//cout<<j<<" "<<i<<" "<<f[j][i]<<endl; 
			sum2=(sum2+sum1*2%mod)%mod,sum1=(sum1+dp[j-1][i])%mod,sum2=(sum2+dp[j-1][i])%mod,sum3=(sum3+sum2)%mod;
		}
	}
	for(int i=1;i<=n;++i)
	p[i]=read();
	for(int i=1;i<=n;++i)
	{
		q[i]=read();
		ne[p[i]]=q[i];
		la[q[i]]=p[i];
	}
	for(int i=1;i<=n;++i)
	{
		if(!vis[p[i]])
		{
			int num=1;
			int wz=p[i];
			vis[wz]=1;
			while(ne[wz]!=p[i])
			wz=ne[wz],++num,vis[wz]=1;
			d.push_back(num);
		}
	}
	int sum=0;
	for(int i=0;i<d.size();++i)
	{
		int v=d[i];
		sum+=v;
	//	cout<<v<<endl;
		if(i==0)
		{
			if(v==1)
			{
				g[i][0]=1;
				g[i][1]=1;
				continue;
			}
			g[i][0]=2;
			for(int j=1;j<=v;++j)
			g[i][j]=f[j][v];
			continue;
		}
		if(v==1)
		{
			for(int j=0;j<=sum;++j)
			{
				g[i][j]=g[i-1][j];
				if(j)
				g[i][j]=(g[i][j]+g[i-1][j-1])%mod;
			}
			continue;
		}
		for(int j=0;j<=sum;++j)
		{
			for(int k=max(j-v,0);k<=sum-v;++k)
			g[i][j]=(g[i][j]+g[i-1][k]*f[j-k][v]%mod)%mod;
		}
	}
	for(int i=0;i<=n;++i)
	h[n-i]=g[d.size()-1][i];
	long long ans=0;
	for(int i=0;i<=n;++i)
	{
		if(i&1)
			ans=(ans-h[i]*jc[n-i]%mod+mod)%mod; 
		else
			ans=(ans+h[i]*jc[n-i]%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：KingPowers (赞：6)

考虑容斥，钦定 $n$ 个位置中有 $i$ 个不合法，剩下的 $n-i$ 个位置随便填，那么问题就是算出钦定 $i$ 个不合法的方案数。

对每个 $i$ 连边 $p_i\to q_i$，这样我们就一定会连出来好几个置换环。我们尝试在置换环上描述不合法的限制：对于环上的点 $x$，我们设它连向的点为 $y$，考虑 $r_{p_x}$ 这个位置应该填什么数，如果和 $p$ 相等就会填 $x$，和 $q$ 相等就会填 $y$。因此我们在置换环上刻画出了不合法的条件：填了当前点的数或者当前点连向的数。

因此对每个置换环直接 dp，设 $f_{i,j,0/1}$ 表示考虑了环上的前 $i$ 个点，当前环上有 $j$ 个点不合法，$0$ 表示没有被钦定不合法或者填了当前的数，$1$ 表示填了连向的数的方案数。因为只有填连向的点时才会影响后续决策，所以可以把不钦定和填当前点的情况压在同一状态。转移比较容易，如果当前位置没被钦定有 $f_{i,j,0}\leftarrow f_{i-1,j,0/1}$，否则有 $f_{i,j,0}\leftarrow f_{i-1,j-1,0}$ 和 $f_{i,j,1}\leftarrow f_{i-1,j-1,0/1}$。

dp 时需要注意的一点是，如果环上的第一个点选择了填自己那么最后一个点再填连向的数是不合法的，因为此时环上第一个点被填了两次，不满足排列的条件，方法是分别强制第一个点的状态为 $0$ 或 $1$ 跑两遍 dp 即可。以及注意特判掉长度为 $1$ 的置换环。

对于每个环 dp 完之后，将每个环的 dp 值做一个背包合并，我们就得到了整体钦定 $i$ 个位置不合法的方案数，设其为 $h_i$，那么答案为：

$$
\sum_{i=0}^n(-1)^ih_i(n-i)!
$$

后面多乘的 $(n-i)!$ 是我们钦定 $i$ 个位置之后剩下 $n-i$ 个数可以随便乱放。

对每个置换环我们都需要做一个平方 dp 再背包合并，但是显然所有置换环的大小之和为 $n$，所以该做法的总时间复杂度为 $O(n^2)$，可以通过。

本人写的代码可能有点笨。

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define deb(x) cerr << #x"=" << x << '\n';
using namespace std;
const int N = 3005;
template<int mod>
struct modint{
	unsigned int x;
	modint(unsigned int x = 0):x(x){}
	#define down(x) (x >= mod ? x - mod : x)
	friend istream& operator>>(istream& in, modint& a){return in >> a.x;}
	friend ostream& operator<<(ostream& out, modint a){return out << a.x;}
	friend modint operator+(modint a, modint b){return down(a.x + b.x);}
	friend modint operator-(modint a, modint b){return down(a.x - b.x + mod);}
	friend modint operator*(modint a, modint b){return 1ull * a.x * b.x % mod;}
	friend modint operator/(modint a, modint b){return a * ~b;}
	friend modint operator^(modint a, int b){modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend modint operator~(modint a){return a ^ (mod - 2);}
	friend modint operator-(modint a){return down(mod - a.x);}
	friend modint operator++(modint& a, int){modint x = a; a += 1; return x;}
	friend modint operator--(modint& a, int){modint x = a; a -= 1; return x;}
	friend modint& operator+=(modint& a, modint b){return a = a + b;}
	friend modint& operator-=(modint& a, modint b){return a = a - b;}
	friend modint& operator*=(modint& a, modint b){return a = a * b;}
	friend modint& operator/=(modint& a, modint b){return a = a / b;}
	friend modint& operator^=(modint& a, int b){return a = a ^ b;}
	friend modint& operator++(modint& a){return a += 1;}
	friend modint& operator--(modint& a){return a -= 1;}
	friend bool operator!(modint a){return !a.x;}
	friend bool operator<(modint a, modint b){return a.x < b.x;}
	friend bool operator>(modint a, modint b){return a.x > b.x;}
	friend bool operator==(modint a, modint b){return a.x == b.x;}
	friend bool operator!=(modint a, modint b){return a.x != b.x;}
	#undef down
};
using Z = modint<1000000007>;
int n, cnt, p[N], q[N];
Z ans, f[N][N][2], g[N], h[N], t[N], fac[N];
bool vis[N];
vector<int> G[N];
void dfs(int now){
	vis[now] = 1; cnt++;
	for(int to : G[now]) if(!vis[to]) dfs(to);
}
void calc(int len){
	For(i, 0, len) For(j, 0, len)
		f[i][j][0] = f[i][j][1] = g[j] = 0;
	if(len == 1){
		g[0] = g[1] = 1;
		goto here;
	}
	f[1][1][0] = 1;
	For(i, 2, len) For(j, 0, i){
		f[i][j][0] += f[i - 1][j][0] + f[i - 1][j][1];
		if(j) f[i][j][0] += f[i - 1][j - 1][0];
		if(j) f[i][j][1] += f[i - 1][j - 1][0] + f[i - 1][j - 1][1];
	}
	For(j, 0, len) g[j] += f[len][j][0];
	For(i, 0, len) For(j, 0, len)
		f[i][j][0] = f[i][j][1] = 0;
	f[1][0][0] = f[1][1][1] = 1;
	For(i, 2, len) For(j, 0, i){
		f[i][j][0] += f[i - 1][j][0] + f[i - 1][j][1];
		if(j) f[i][j][0] += f[i - 1][j - 1][0];
		if(j) f[i][j][1] += f[i - 1][j - 1][0] + f[i - 1][j - 1][1];
	}
	For(j, 0, len) g[j] += f[len][j][0] + f[len][j][1];
	here:; For(i, 0, n) t[i] = 0;
	For(i, 0, len) For(j, 0, n - i) t[i + j] += g[i] * h[j];
	For(i, 0, n) h[i] = t[i]; 
}
void Solve(){
	cin >> n;
	For(i, 1, n) cin >> p[i];
	For(i, 1, n) cin >> q[i];
	For(i, 1, n) G[p[i]].emplace_back(q[i]);
	fac[0] = h[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i;
	For(i, 1, n){
		if(vis[i]) continue;
		cnt = 0; dfs(i); calc(cnt);
	}
	For(i, 0, n){
		if(i & 1) ans -= h[i] * fac[n - i];
		else ans += h[i] * fac[n - i];
	}
	cout << ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：Duantree (赞：2)

容斥，记 $f(i)$ 为钦定 $i$ 个位置不满足要求的方案数。答案即为 $\sum (-1) ^ if(i) (n - i)!$。

将 $a_i$ 向 $b_i$ 连边，一定会连出一些 $a_i = b_{i-1}$ 的环。容易发现，不同环之间不会互相影响，且每个环上的答案只与环的长度有关。记 $ans_{i,j}$ 为在前 $i$ 个环内，选出 $j$ 个位置满足要求的方案数。预处理出 $c_{i,j}$ 表示长度为 $i$ 的环中，选出 $j$ 个位置不满足要求的方案数。

考虑如何处理 $c_{i,j}$。记 $dp_{i,j,0/1}$ 为环上前 $i$ 个位置，选出 $j$ 个位置不满足要求，第 $i$ 个位置必选且选择的是 $a_i$ 或 $b_i$ 的方案数。

$dp_{i,j,0} = \sum_{i'< i} dp_{i',j-1,0} + \sum_{i' < i-1}dp_{i',j - 1,1}$

$dp_{i,j,1} = \sum_{i'< i} dp_{i',j-1,0} + dp_{i',j - 1,1}$

前缀和优化即可。时间复杂度 $O(n^2)$。

对于环上最后一个位置的影响，我们强行钦定后断环成链，考虑以下三种情况对 $c$ 的贡献：

- 第一个位置选 $a$.

初值：$dp_{1,1,0}=1$

贡献：$c_{i,j} = c_{i,j} + dp_{i,j,0} + \sum_{i'< i} dp_{i',j,0} + dp_{i',j,1}$

- 第一个位置选 $b$.

初值: $dp_{1,1,1}=1$

贡献：$c_{i,j} = c_{i,j} + \sum_{i'\leq i} dp_{i',j,0} + dp_{i',j,1	}$

- 第一个位置不选。

初值: $dp_{i,1,0} = dp_{i,1,1} = 1(i\ne1)$

贡献：$c_{i,j} = c_{i,j} + \sum_{i'\leq i} dp_{i',j,0} + dp_{i',j,1	}$

以上三种情况只有初值不同，转移方式相同。注意 $c_{1,1} = 1$。

得到 $c$ 数组后，做一次背包求出 $ans$。如果每次只枚举到环长的上界，那么每对数的贡献只会被计算一遍。总时间复杂度 $O(n^2)$。

[模拟赛赛时代码，可读性较差。](https://www.luogu.com.cn/paste/c9wqs7y8)

---

## 作者：红黑树 (赞：1)

[可能更好的阅读体验](https://rbtr.ee/abc-214-g)

## [题意](https://atcoder.jp/contests/abc214/tasks/abc214_g)
给定长度为 $N$ 的两个排列 $p$ 和 $q$，求长度为 $N$ 的排列 $r$ 的个数，使得 $r_i \neq p_i$ 且 $r_i \neq q_i$，对于任意的 $1 \leq i \leq N$ 都成立。

$1 \leq N \leq 3000$

## 题解
设 $f_i$ 表示任意选 $i$ 个位置，对于这些位置都有 $r_i = p_i$ 或 $r_i = q_i$。根据容斥，答案是

$$\sum\limits_{0 \leq i \leq N}\left(-1\right)^if_i\left(n - i\right)!$$

考虑 $f_i$ 的计算。由于 $r_i$ 不能重复导致不好计数，我们可以换一种思路，让限制匹配位置。具体来说，在 $p_i$ 和 $q_i$ 之间连边，如此在图中，限制 $i$ 被满足表示为把 $p_i$ 或 $q_i$ 分配给了 $\left(p_i, q_i\right)$ 这条边。

还是不好计数，但还有救，把 $\left(p_i, q_i\right)$ 变成 $\left(p_i, s_i\right)$ 和 $\left(s_i, q_i\right)$，相当于在这两条边之间新增一个点。于是点到边的分配被转化成了点到点的匹配。

没什么用，我们需要更多性质。发现图中每个点刚好有一个入和一个出，构成若干个环（可能包含自环）。环之间显然是独立的。于是我们可以对环求出答案然后 DP 合并。

环内的答案是好计算的。假设有 $n$ 个点（包含我们新增的 $s$ 系列点），我们要选出 $k$ 组匹配。如果 $\left(1, n\right)$ 不被选为匹配，那么方案数是 $\binom{n - k}k$。如果 $\left(1, n\right)$ 被选为匹配，那么方案数是 $\binom{n - 2 - \left(k - 1\right)}{k - 1}$。于是相加得到总方案数

$$\binom{n - k}k + \binom{n - k - 1}{k - 1}$$

---
其实是有 $\tilde{\mathcal O}\left(n\right)$ 做法，不过要多项式，果断放弃。想学可以看[这里](https://st1vdy.xyz/index.php/2021/08/26/abc214g-three-permutations/)。

## 代码
```cpp
/* Please submit with C++17! It's best to use C++20 or higher version.
 * No header file and no RBLIB (https://git.rbtr.ee/root/Template).
 * By Koicy (https://koicy.ly)
 * Email n@rbtr.ee
 * I've reached the end of my fantasy.

         __    __                             __         _
   _____/ /_  / /_________  ___              / /______  (_)______  __
  / ___/ __ \/ __/ ___/ _ \/ _ \   ______   / //_/ __ \/ / ___/ / / /
 / /  / /_/ / /_/ /  /  __/  __/  /_____/  / ,< / /_/ / / /__/ /_/ /
/_/  /_.___/\__/_/   \___/\___/           /_/|_|\____/_/\___/\__, /
                               SIGN                         /___*/
#ifndef XCODE
constexpr bool _CONSOLE = false;
#else
constexpr bool _CONSOLE = true;
#endif
#define __NO_MAIN__ false
#define __ENABLE_RBLIB__ true
constexpr bool _MTS = false, SPC_MTS = false;
constexpr char EFILE[] = "";
#define FULL(arg) arg.begin(), arg.end()

// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 1e9 + 7;
  tp n = bin;
  vetp p = bin.vcr(n, 1);
  vetp q = bin.vcr(n, 1);
  vector<vetp> e(n + 1);
  for (tp i = 1; i <= n; ++i) {
    e[p[i]].push_back(q[i]);
    e[q[i]].push_back(p[i]);
  }
  vector<tp> sec { 0 };
  set<tp> vis;
  for (tp i = 1; i <= n; ++i) {
    auto dfs = [&](auto $, tp x, tp& c) -> void {
      if (vis.count(x)) return;
      ++c;
      vis.insert(x);
      for (auto& j : e[x]) $($, j, c);
    };
    if (vis.count(i)) continue;
    sec.emplace_back();
    dfs(dfs, i, sec.back());
  }
  vector<vetp> f(sec.size(), vetp(n + 1));
  vetp fact(2 * n + 1, 1);
  vetp ifac(2 * n + 1);
  for (tp i = 2; i <= 2 * n; ++i) fact[i] = fact[i - 1] * i % mod;
  for (tp i = 0; i <= 2 * n; ++i) ifac[i] = RCAL::inverse(fact[i], mod);
  auto binom = [&](tp n, tp m) -> tp {
    if (n < 0 || m < 0 || n < m) return 0;
    return fact[n] * ifac[m] % mod * ifac[n - m] % mod;
  };
  f[0][0] = 1;
  for (tp i = 1; i < sec.size(); ++i) {
    if (sec[i] == 1) {
      f[i][0] = f[i - 1][0];
      for (tp j = 1; j <= n; ++j) f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % mod;
      continue;
    }
    for (tp j = 0; j <= n; ++j) {
      for (tp k = 0; k <= sec[i] && j + k <= n; ++k) {
        tp l = 2 * sec[i];
        f[i][j + k] = (f[i][j + k] + f[i - 1][j] * (binom(l - k, k) + binom(l - k - 1, k - 1))) % mod;
      }
    }
  }
  tp tar = 0;
  for (tp i = 0; i <= n; ++i) {
    tp t = (i & 1 ? -1 : 1) * fact[n - i];
    tar = (tar + t * f.back()[i]) % mod;
  }
  bin << (tar + mod) % mod << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：lfxxx (赞：0)

这个限制直接做有点不太能做，考虑容斥不合法的位置数。

一个限制形如 $r_i$ 必须等于 $x$，显然有些限制之间存在冲突，有些限制本质相同，为了使得没有被约束的位置恰好是 $n$ 减去选出的约束个数，我们将所有 $p_i=q_i$ 的位置单独处理，总体上设计 $dp_i$ 表示存在 $i$ 个位置有约束（约束会使得这个位置一定不合法）的方案数，答案显然是 $n!-\sum_{i=1}^n (-1)^i \times dp_i \times (n-i)!$。

考虑哪些限制不能同时选择，显然一个位置上 $p_i,q_i$ 不能同时选，并且对于 $p_i=q_j$ 的也不能同时选，为了形式化地刻画不能同时选，我们将不能同时选的限制之间连边，不难发现一个点度数恰好为 $2$，故图是若干简单环，每个环上选出若干个互不相邻点的方案可以简单组合数，具体而言，$g(i,j),f(i,j)$ 分别表示大小为 $i$ 的环和链选出 $j$ 个互不相邻点的方案数，有 $g(i,j)=f(i,j)-f(i-4,j-2)$，计算 $f(i,j)$ 可以考虑插板法，不难得到 $f(i,j)={{i-j+1} \choose j}$，然后暴力 $O(n^2)$ 更新 dp 数组即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxn = 6e3+114;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b&1) res=res*a%mod;
    return res;
}
int fac[maxn],inv[maxn];
int dp[maxn];//选出 i 个约束的方案
int p[maxn],q[maxn];
vector<int> E[maxn];
int n;
int ans;
int vis[maxn];
int sz;
int use[maxn];
void dfs(int u){
    sz++;
    use[u]=1;
    for(int v:E[u]){
        if(use[v]==0){
            dfs(v);
        }
    }
}
int C(int n,int m){
    if(n<m) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int f(int i,int j){
    if(i<0||j<0) return 0;
    return C(i-j+1,j);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    fac[0]=inv[0]=1;
    for(int i=1;i<=2*n;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>q[i];
    dp[0]=1;
    for(int i=1;i<=n;i++){
        if(p[i]==q[i]){
            for(int j=n;j>=1;j--){
                dp[j]=(dp[j]+dp[j-1])%mod;
            }
            vis[p[i]]=1;
        }else E[p[i]].push_back(q[i]+n),E[q[i]+n].push_back(p[i]);
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==0) E[i].push_back(i+n),E[i+n].push_back(i);
    }
    //edge 形成若干简单环
    for(int i=1;i<=2*n;i++){
        if(use[i]==0&&E[i].size()>0){
            sz=0;
            dfs(i);
            for(int j=n;j>=1;j--){
                for(int k=1;k<=j&&k*2<=sz;k++) dp[j]=(dp[j]+dp[j-k]*(k==1?sz:(f(sz,k)+mod-f(sz-4,k-2))%mod)%mod)%mod;
            }
        }
    }
    ans=fac[n];
    for(int i=1;i<=n;i++){
        ans=(ans+(i&1?(mod-1):1)*dp[i]%mod*fac[n-i]%mod)%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：happybob (赞：0)

先考虑容斥。

容斥后发现需要求出有多少排列满足有至少 $x$ 个 $r_i = p_i$ 或 $r_i=q_i$。

考虑对于排列建立有向图，具体来说连接 $p_i \rightarrow q_i$，那么图由若干置换环构成。每个环内可以选若干条边，将这些边定向使得不存在点入度为 $2$。这里可以破环为链后 DP，这部分复杂度为 $O(\sum c_i^2) = O(n^2)$。

然后将这些 DP 值卷积合并即可。注意到范围比较小，暴力平方卷积即可。总复杂度 $O(n^2)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <climits>
#include <numeric>
#include <array>
using namespace std;

using ll = long long;

constexpr int N = 3005;
constexpr ll MOD = 1e9 + 7;

int n;
array<int, N> p, q;
array<vector<int>, N> G;
array<array<ll, 2>, N> f, g;
array<ll, N> ret, fac;
array<bool, N> vis;
array<ll, N> h, nh;
array<vector<pair<int, ll>>, N> arr;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	fac[0] = 1ll;
	for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> p[i];
	for (int i = 1; i <= n; i++) cin >> q[i], G[p[i]].emplace_back(q[i]);
	for (int i = 1; i <= n; i++)
	{
		if (vis[i]) continue;
		int j = i, cnt = 0;
		do
		{
			cnt++;
			vis[j] = 1;
			j = G[j][0];
		} while (!vis[j]);
		arr[i].emplace_back(0, 1ll);
		if (cnt == 1)
		{
			arr[i].emplace_back(1, 1ll);
			continue;
		}
		// case1: 最后一条边不选
		for (int x = 0; x <= cnt; x++)
		{
			ret[x] = 0ll;
			for (int y = 0; y < 2; y++) f[x][y] = 0ll;
		}
		f[0][0] = 1ll;
		for (int i = 2; i <= cnt; i++)
		{
			for (int j = 0; j <= cnt; j++)
			{
				g[j] = f[j];
				f[j] = { 0ll, 0ll };
			}
			for (int j = 0; j <= cnt; j++)
			{
				f[j][0] = ((g[j][0] + g[j][1]) % MOD) + (j ? g[j - 1][0] : 0ll) % MOD;
				if (j)
				{
					f[j][1] = (g[j - 1][0] + g[j - 1][1]) % MOD;
				}
			}
		}
		for (int i = 0; i <= cnt; i++) ret[i] = (f[i][0] + f[i][1]) % MOD;
		// case2: 最后一条边选了 1
		for (int x = 0; x <= cnt; x++)
		{
			for (int y = 0; y < 2; y++) f[x][y] = 0ll;
		}
		f[1][1] = 1ll;
		for (int i = 2; i <= cnt; i++)
		{
			for (int j = 0; j <= cnt; j++)
			{
				g[j] = f[j];
				f[j] = { 0ll, 0ll };
			}
			for (int j = 0; j <= cnt; j++)
			{
				f[j][0] = ((g[j][0] + g[j][1]) % MOD) + (j ? g[j - 1][0] : 0ll) % MOD;
				if (j)
				{
					f[j][1] = (g[j - 1][0] + g[j - 1][1]) % MOD;
				}
			}
		}
		for (int i = 0; i <= cnt; i++) ret[i] = (ret[i] + 2ll * f[i][0] % MOD + 2ll * f[i][1] % MOD) % MOD;
		for (int j = 1; j <= cnt; j++)
		{
			arr[i].emplace_back(j, ret[j]);
		}
	}
	h[0] = 1ll;
	for (int i = 1; i <= n; i++)
	{
		if (arr[i].empty()) continue;
		nh.fill(0ll);
		for (int j = 0; j <= n; j++)
		{
			if (!h[j]) continue;
			for (auto& [x, y] : arr[i]) nh[x + j] = (nh[x + j] + h[j] * y % MOD) % MOD;
		}
		h = nh;
	}
	ll ans = 0ll;
	for (int i = 0; i <= n; i++)
	{
		ll ret = h[i] * fac[n - i] % MOD;
		if (i & 1) ans = (ans - ret + MOD) % MOD;
		else ans = (ans + ret) % MOD;
	}
	cout << ans << "\n";
	return 0;
}
```

---

