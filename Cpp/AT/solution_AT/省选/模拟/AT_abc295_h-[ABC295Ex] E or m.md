# [ABC295Ex] E or m

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc295/tasks/abc295_h

$ N $ 行 $ M $ 列のグリッド $ A $ があり、はじめ全てのマスに $ 0 $ が書き込まれています。  
 ここに以下の操作を行います。

- $ 1\ \le\ i\ \le\ N $ を満たす各整数 $ i $ に対して、 $ A $ の $ i $ 行目の左から $ 0 $ 個以上のマスの数字を $ 1 $ にする。
- $ 1\ \le\ j\ \le\ M $ を満たす各整数 $ j $ に対して、 $ A $ の $ j $ 列目の上から $ 0 $ 個以上のマスの数字を $ 1 $ にする。
 
この手続きによって作ることのできる $ A $ の集合を $ S $ とします。

`0`, `1`, `?` からなる $ N $ 行 $ M $ 列のグリッド $ X $ が与えられます。  
 `?` を `0` か `1` に置き換えて得られるグリッドは $ X $ に含まれる `?` の総数を $ q $ とすると $ 2^q $ 個ありますが、このうち $ S $ の要素であるものはいくつありますか？  
 答えは非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ N,M $ は整数
- $ 1\ \le\ N,M\ \le\ 18 $
- $ X $ は `0`, `1`, `?` からなる $ N $ 行 $ M $ 列のグリッド
 
### Sample Explanation 1

条件を満たすグリッドは以下の $ 6 $ つです。 ``` 011 011 001 010 011 110 001 011 011 111 110 111 ```

### Sample Explanation 2

$ X $ に `?` が存在しない場合も、答えが $ 0 $ である場合もあります。

### Sample Explanation 3

答えを $ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
2 3
0?1
?1?```

### 输出

```
6```

## 样例 #2

### 输入

```
5 3
101
010
101
010
101```

### 输出

```
0```

## 样例 #3

### 输入

```
18 18
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????
??????????????????```

### 输出

```
462237431```

# 题解

## 作者：Lavaloon (赞：3)

不会轮廓线 DP 喵，这里是高维后缀和解法！

## $\text{Statement}$

开始你有一个全 $\mathtt{0}$ 矩阵，你可以随意执行如下操作：

- 选择任意一行，将其从最左端开始的连续一段染成 $\mathtt{1}$。
- 选择任意一列，将其从最上端开始的连续一段染成 $\mathtt{1}$。

如果一个矩阵可以由此得到，那么这个矩阵被称为好的。

现在你有一个 $\mathtt{01?}$ 矩阵 $a$，你需要将所有 $\mathtt{?}$  替换为 $\mathtt{0}$ 或 $\mathtt{1}$，问得到的矩阵中有多少个是好的。答案对 $998244353$ 取模。

$1\le n,m\le 18$。

## $\text{Analysis}$

下称一个坐标 $(i,j)$ 的“**列坐标**”为它所在的列，即为 $j$。

这个问题考察的对象是所有好的矩阵，因此，首先应该考虑：**如何判定一个矩阵是好的。**

经过简单思考可以发现如下的判定方法：

- 题目告诉我们：对于一个位置 $(i,j)$，其可以是 $\mathtt{1}$ 当且仅当它上面都是 $\mathtt{1}$ 或者它前面都是 $\mathtt{1}$。
- 那么，**假如不考虑每行的全 $\mathtt{1}$ 前缀，上下相邻两行的 $\mathtt{1}$ 的列坐标的集合，应该是包含的关系**——下一行的 $\mathtt{1}$ 的列坐标的集合被上一行的 $\mathtt{1}$ 的列坐标的集合包含。

于是我们想到：**一行一行地填数，同时记录哪一些列坐标还能再填 $\mathtt{1}$**。

于是记 $f_{i,S}$ 为：**填完了第 $i$ 行，集合 $S$ 里面的列坐标在下一行还能填 $\mathtt{1}$ 的方案数**——$S$ 是一个列坐标的集合，亦可以表示为一个二进制数，在 $2^b$ 上为 $1$ 代表这个集合包含 $b$。

设计状态转移：

- 我们枚举在这一行是如何填数的，填 $\mathtt{1}$ 的列坐标的集合为 $X$。（这并非枚举 $S$，注意区分）
- 我们枚举上一行的每一个状态，记这个状态所对应的列坐标集合为 $Y$。
- 假如可以在这一行填这个 $X$，那么：
  -  在 $X$ 的一段**前缀 $\mathtt{1}$ 之外**的 $\mathtt{1}$，都应该被 $Y$ 所包含。例：
     - $X={\color{red}{111}}01101$
     - $Y={\color{green}{101}}01111$

这确实给出了一个正确的状态转移方程，但是你发现这样我们是时间复杂度已经炸了，这一部分就 $\mathcal{O}(2^{2m})$ 了。

接下来我们来优化这个东西！

首先我们发现 $Y$ 的这一段绿色前缀很烦人。

但是事实上，我们发现这一段绿色前缀可以暴力枚举。

因为对每个前缀 $\mathtt{1}$ 的长度计算枚举次数的贡献，它是 $1+\sum_{i=0}^{m-1}2^i\cdot 2^{m-i-1}$，其中 $2^i$ 表示暴力枚举绿色前缀的复杂度，$2^{m-i-1}$ 是拥有这么长的全 $\mathtt{1}$ 前缀的 $X$ 的个数，$+1$ 表示计算上长度为 $m$ 的全 $ \mathtt{1} $ 二进制数。它是 $\mathcal{O}(m2^m)$ 的。

枚举出 $Y$ 的那一段绿色前缀之后，我们就需要计算：拥有这样的一段前缀的所有 $Y$，它们的 $f_{i-1,Y}$ 的和。

我们上面提到：在 $X$ 的一段**前缀 $\mathtt{1}$ 之外**的 $\mathtt{1}$，都应该被 $Y$ 所包含。感觉一下，这不就是__没有完全做完的高维后缀和__嘛——后面几维做了，前面几维还没做。

这样我们就可以在 $\mathcal{O}(m2^m)$ 内处理出来这个东西了。

从实现方面来说，比较好写的一个方法是：令 $g_{i,S}$ 表示 $S$ 前 $i$ 小的维度还没有做后缀和，其余的做过了，所有满足转移条件的的状态的和。

实际上我们已经做完了。

总时间复杂度为 $\mathcal{O}(nm2^m)$。

读者务必手玩几组数据并感知一下整个过程，理明白思路之后再开始写。

## $\text{Code}$

洛谷最优解第一页，这个速度我还是比较认可的。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<unordered_map>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<random>
#include<numeric>
#include<assert.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define lc (x<<1)
#define rc (x<<1|1)
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
#define cout (cerr<<">> ",cout)
const int Mx=18,p=998244353;
int read(){
	char ch=getchar();
	int Alice=0,Aya=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') Aya=-Aya;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		Alice=(Alice<<3)+(Alice<<1)+(ch^48),ch=getchar();
	return (Aya==1?Alice:-Alice);
}
int n,m;
string s[Mx];
int f[1<<Mx];
int g[Mx+1][1<<Mx];
void Calc(){
	for(int j=0;j<(1<<m);j++) g[m][j]=f[j];
	for(int i=m-1;i>=0;i--){
		for(int j=(1<<m)-1;j>=0;j--){
			if((j&(1<<i))==0) (f[j]+=f[j^(1<<i)])%=p;
		}
		for(int j=(1<<m)-1;j>=0;j--) g[i][j]=f[j];
	}
	for(int j=0;j<(1<<m);j++) f[j]=0;
}
signed main(){
	n=read(),m=read();
	for(int i=0;i<n;i++) cin>>s[i];
	for(int S=0;S<(1<<m);S++){
		bool ok=1;
		for(int i=0;i<m;i++){
			if(s[0][i]-'0'==1-((S>>i)&1)){
				ok=0;
				break;
			}
		}
		if(ok) f[S]=1;
	}
	for(int i=1;i<n;i++){
		Calc();
		for(int S=0;S<(1<<m);S++){
			bool ok=1;
			for(int j=0;j<m;j++){
				if(s[i][j]-'0'==1-((S>>j)&1)){
					ok=0;
					break;
				}
			}
			if(!ok) continue;
			int len=0;
			for(int j=0;j<m;j++) if((S>>j)&1) len=j+1; else break;
			for(int T=0;T<(1<<len);T++){
				int R=((S>>len)<<len)|T;
				(f[R]+=g[len][R])%=p;
			}
		}
	}
	int ans=0;
	for(int S=0;S<(1<<m);S++){
		(ans+=f[S])%=p;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

轮廓线 $\rm DP$ 模板题。

-------

给你一个局面，如何判定是否合法？很简单，对于每个 $1$，只要它的上面或者左边全是 $1$，局面就合法。

考虑逐格状压。具体的，我们记录 $dp_{i,j,op,S}$ 表示：从左到右、从上到下考虑到了第 $(i,j)$ 个格子，这一列是否出现了 $0$，哪些行已经出现了 $0$。

考虑转移。从 $(i,j)$ 转移到 $(i+1,j)$ 时，考虑枚举当前格子是 $0$ 还是 $1$。如果是 $0$，转移到 $dp_{i+1,j,1,S \cup \{i+1\}}$；如果是 $1$，转移到 $dp_{i+1,j,op,S}$，但前提是 $op=0$ 或 $S \cap \{i+1\} = \varnothing$。

复杂度 $O(nm 2^n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20,MAXM=(1<<18)+10,MOD=998244353;
int n,m,flg[MAXN][MAXN],dp[2][2][MAXM];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {
		string S;
		cin>>S;
		ffor(j,1,m) {
			if(S[j-1]=='0') flg[i][j]=0;
			else if(S[j-1]=='1') flg[i][j]=1;
			else flg[i][j]=-1;
		}
	}
	int lst=0,st=0;
	dp[0][0][0]=1;
	ffor(j,1,m) ffor(i,1,n) {
		lst=st,st^=1;
		memset(dp[st],0,sizeof(dp[st]));
		ffor(op,0,1) ffor(fbd,0,(1<<n)-1) {
			//增加 0
			if(flg[i][j]!=1) dp[st][1][fbd|(1<<i-1)]=(dp[st][1][fbd|(1<<i-1)]+dp[lst][op][fbd])%MOD;
			//增加 1
			if(flg[i][j]!=0&&(!op||!(fbd&(1<<i-1)))) dp[st][op][fbd]=(dp[st][op][fbd]+dp[lst][op][fbd])%MOD; 
		}
		if(i==n) ffor(fbd,0,(1<<n)-1) dp[st][0][fbd]=(dp[st][0][fbd]+dp[st][1][fbd])%MOD,dp[st][1][fbd]=0;
	}
	int sum=0;
	ffor(fbd,0,(1<<n)-1) sum=(sum+dp[st][0][fbd])%MOD;
	cout<<sum;
	return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

首先考察合法的充要条件：对于每个是 $1$ 的位置，要么其上方所有格子都是 $1$，要么其左方所有各自都是 $1$。有了这个条件，结合 $n,m\le 18$ 的数据范围容易想到状压 dp。

具体而言，设 $f_{i,j,S}$ 表示目前从上往下，从左往右填到 $(i,j)$，状态为 $S$ 的方案数，其中状态 $S$ 记录了每列目前的所有格子是否都为 $1$ 和当前行目前所有格子都为 $1$。转移只需要考虑枚举当前格子是 $0$ 还是 $1$，更新对应行列的状态即可。注意需要特殊处理换行的转移。时间复杂度 $\mathcal O(nm2^m)$，空间复杂度 $\mathcal O(2^m)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll Mod=998244353;
ll n,m,dp[2][(1<<19)+9],cur;
char s[21][21];
void Upd(ll&x,ll y){
    x+=y;
    if(x>=Mod)x-=Mod;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,0,n-1)scanf("%s",s[i]);
    dp[0][(1<<(m+1))-1]=1;
    rep(i,0,n-1){
        rep(j,0,m-1){
            memset(dp[cur^1],0,sizeof(dp[cur^1]));
            rep(S,0,(1<<(m+1))-1){
                if(!dp[cur][S])continue;
                rep(k,0,1){
                    if(s[i][j]!='?'&&s[i][j]!='0'+k)continue;
                    ll col=(S>>j)&1,row=(S>>m)&1;
                    if(k){
                        if(!col&&!row)continue;
                    }
                    ll nS=S^(col<<j)^(row<<m)^((col&&k)<<j)^((row&&k)<<m);
                    Upd(dp[cur^1][nS],dp[cur][S]);
                }
            }
            cur^=1;
        }
        memset(dp[cur^1],0,sizeof(dp[cur^1]));
        rep(S,0,(1<<(m+1))-1)Upd(dp[cur^1][S|(1<<m)],dp[cur][S]);
        cur^=1;
    }
    ll ans=0;
    rep(S,0,(1<<(m+1))-1)Upd(ans,dp[cur][S]);
    write(ans);
    return 0;
}
```

---

## 作者：Phartial (赞：1)

状压 dp，2 hd 4 me/ng。

## 题意

开始你有一个全 $0$ 矩阵，你可以随意执行如下操作：

- 选择任意一行，将其从最左端开始的连续一段染成 $1$。
- 选择任意一列，将其从最上端开始的连续一段染成 $1$。

如果一个矩阵可以由此得到，那么这个矩阵被称为好的。

现在你有一个 `01?` 矩阵 $a$，你需要将所有 `?` 替换为 `0` 或 `1`，问得到的矩阵中有多少个是好的。答案对 $998244353$ 取模。

$1\le n,m\le 18$。

## 思路

可以发现一个矩阵是否合法取决于对每个格子而言，其上方或左方是否有一方仍是全 $1$ 段。

于是考虑设 $f_{(i,j),k=0/1,s}$ 表示现在处理完了 $(i,j)$，列状态为 $s$（列状态指目前 $m$ 列里每一列是否仍为全 $1$ 段），行状态为 $k$（即当前行是否仍为全 $1$ 段）。

初始状态为 $f_{(1,0),1,\text{full}}=1$，即啥都没填的情况。

对当前状态 $f_{(i,j),k,s}$，我们分类讨论：

### 格子不在行末

那么下一个格子即为 $(i,j+1)$，我们继续分类讨论：

- $a_{i,j+1}=0$：那么第 $j+1$ 列的列状态则变成 $0$，第 $i$ 行的行状态变为 $0$，即 $f_{(i,j),k,s}\to f_{(i,j+1),0,s_{j+1}\gets 0}$。
- $a_{i,j+1}=1$：要求当前行状态与第 $j+1$ 列的列状态不能全为 $0$，转移方程为 $f_{(i,j),k,s}\to f_{(i,j+1),k,s}$。
- $a_{i,j+1}=\text{?}$：综合上面两种情况即可。

### 格子在行末

可以发现这种情况相当于将 $(i,j)$ 移到了下一行的 $(i+1,0)$，重置行状态，然后按 $j<m$ 做即可。

最终答案即为 $\displaystyle\sum_{i}\sum_{j}f_{(n,m),i,j}$。

```cpp
#include <iostream>

using namespace std;

const int kN = 19;
const int kM = 998244353;

int n, m;
char a[kN][kN];
int f[kN][kN][2][1 << kN], ans;

void A(int &f, int v) {
  if ((f += v) >= kM) {
    f -= kM;
  }
}
void E(int x, int y, int k, int s, int v) {
  if (x == n && y == m) {
    A(ans, v);
    return;
  }
  if (y == m) {
    ++x, y = 0, k = 1;
  }
  if (a[x][y + 1] != '1') {
    A(f[x][y + 1][0][s & ~(1 << y)], v);
  }
  if (a[x][y + 1] != '0' && (k || (s >> y & 1))) {
    A(f[x][y + 1][k][s], v);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] + 1;
  }
  E(1, 0, 1, (1 << m) - 1, 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k < 2; ++k) {
        for (int p = 0; p < (1 << m); ++p) {
          E(i, j, k, p, f[i][j][k][p]);
        }
      }
    }
  }
  cout << ans;
  return 0;
}
```


---

## 作者：Jerrywang09 (赞：0)

记状态 $f(i,j,k,s)$ 表示现在到了格子 $(i,j)$，$k$ 表示 $i$ 这一行是否可以继续填 $1$，$s$ 状压每一列是否可以继续填 $1$。

枚举每个状态，然后更新下一列的元素。如果在行末就要跳到下一行。总体来看本题并不难。

```cpp
// Title:  E or m
// Source: ABC295Ex
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=19, mod=998244353;
using namespace std;

int m, n, res, f[N][N][2][1<<N]; char a[N][N];
void upd(int &x, int y)
{
	x+=y; if(x>=mod) x-=mod;
}
void extend(int i, int j, int k, int s, ll val)
{
	if(i==m && j==n) return upd(res, val);
	if(j==n) i++, j=0, k=1;
	if(a[i][j+1]!='1')
	{
		if(s>>j&1) upd(f[i][j+1][0][s^(1<<j)], val);
		else upd(f[i][j+1][0][s], val);
	}
	if(a[i][j+1]!='0' && (k || s>>j&1))
		upd(f[i][j+1][k][s], val);
}

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d%d", &m, &n);
	rep(i, 1, m) scanf("%s", &a[i][1]);
	extend(1, 0, 1, (1<<n)-1, 1);
	rep(i, 1, m) rep(j, 1, n) rep(k, 0, 1) rep(s, 0, (1<<n)-1)
		extend(i, j, k, s, f[i][j][k][s]);
	printf("%d", res);
	
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](https://atcoder.jp/contests/abc295/tasks/abc295_h)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc295_h)

## 分析
容易发现一个位置可以是 $1$ 当且仅当其上全 $1$ 或其左全 $1$。于是容易想到进行按格转移的轮廓线dp，状态 $f[i][j][S][0 / 1]$ 表示处理到第 $i$ 行第 $j$ 列，每一列目前是否是全 $1$，当前行前面是否是全 $1$。然后转移就是平凡的，只需要考虑当前列是否全 $1$ 和当前行是否全 $1$ 即可。转移到行末之后要记得换行，无论当前行是否全 $1$ 到了下一行都是全 $1$。

## 代码
```cpp
#include <iostream>
using namespace std;
const int P = 998244353;
int n, m;
string str[20];
int dp[20][20][262200][2];
void Madd(int& x, int y) { ((x += y) >= P) ? (x -= P) : 0; }
signed main() {
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> str[i], str[i] = ' ' + str[i];
    dp[1][0][(1 << m) - 1][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < (1 << m); k++) {
                if (str[i][j] != '1') {
                    int x = (k ^ (k & (1 << (j - 1))));
                    Madd(dp[i][j][x][0], (dp[i][j - 1][k][0] + dp[i][j - 1][k][1]) % P);
                }
                if (str[i][j] != '0') {
                    Madd(dp[i][j][k][1], dp[i][j - 1][k][1] % P);
                    if (k & (1 << (j - 1))) 
                        Madd(dp[i][j][k][0], dp[i][j - 1][k][0] % P);
                }
            }
        }
        for (int k = 0; k < (1 << m); k++) Madd(dp[i + 1][0][k][1], (dp[i][m][k][0] + dp[i][m][k][1]) % P);
    }
    int ans = 0;
    for (int i = 0; i < (1 << m); i++) Madd(ans, dp[n + 1][0][i][1]);
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：cyq32ent (赞：0)

先考虑暴力搜索。假如我们当前搜索到了格子 $(x,y)$，那么暴力计算 $(x,y)$ 与上方、左方的连通性。这样可以通过小样例。

```cpp
int slv(int x,int y){
  if(x==n)return 1;
  if(y==m)return slv(x+1,0);
  if(a[x][y]=='0')return slv(x,y+1);
  int r=1,c=1,s=0;
  for(int i=0;i<y;i++)if(a[x][i]!='1')r=0;
  for(int i=0;i<x;i++)if(a[i][y]!='1')c=0;
  if(a[x][y]=='1')return (r|c)?(slv(x,y+1)):0;
  a[x][y]='0';
  s=slv(x,y+1);
  a[x][y]='1';
  s+=(r|c)?(slv(x,y+1)):0;
  a[x][y]='?';
  return s%M;
}
```

我们发现，事实上没有必要暴力计算 $c$（$(x,y)$ 与上方的连通性）。可以用一个数组存储每一列的 $c$。这个数组就是当前的轮廓线上的 $c$。因此，可以用一个二进制数来表示数组，并用记忆化搜索优化。

```cpp
int slv(int x,int y){
  if(x==n)return 1;
  if(y==m)return slv(x+1,0);
  if(mem[x][y][r][b])return memory[x][y][r][b];
	mem[x][y][r][b]=1;
  if(a[x][y]=='0'){
    int tmp=c[y];
    c[y]=0;
    int s=slv(x,y+1);
    c[y]=tmp;
    return memory[x][y][r][b]=s%M;
  }
  int r=1,s=0,b=0;
  for(int i=0;i<y;i++)if(a[x][i]!='1')r=0;
  //for(int i=0;i<x;i++)if(a[i][y]!='1')c=0;
  for(int i=0;i<m;i++)(b<<=1)+=c[i];
  if(a[x][y]=='1')return memory[x][y][r][b]=((r|c[y])?(slv(x,y+1)):0)%M;
  a[x][y]='0';
  int tmp=c[y];
  c[y]=0;
  s=slv(x,y+1);
  c[y]=tmp;
  a[x][y]='1';
  s+=(r|c[y])?(slv(x,y+1)):0;
  a[x][y]='?';
  return memory[x][y][r][b]=s%M;
}
```

这样虽然优化了不少，但是仍然不能通过大样例，仔细观察，发现 $r$、$b$ 其实没有必要单独计算，只需从之前的状态传下来即可。

```cpp

int slv(int x,int y,int r,int b){
	if(mem[x][y][r][b])return memory[x][y][r][b];
	if(x>=n)return 1;
	if(y>=m)return slv(x+1,0,1,b);
	mem[x][y][r][b]=1;
	int s=0;bool q=(b&(1<<y));
	if(a[x][y]=='0'){
		if(b&(1<<y))b^=(1<<y);
		s=slv(x,y+1,0,b);
	}
	else if(a[x][y]=='1'){
		if(r|q)s+=slv(x,y+1,r,b);
	}else{
		int v=b;
		if(v&(1<<y))v^=(1<<y);
		s+=slv(x,y+1,0,v);
		if(r|q)s+=slv(x,y+1,r,b);
	}
	return memory[x][y][r][b]=s%M;
}
```

速度有很大提升，可以在约 $15$ 秒内通过大样例。这仍然超时，所以应将递归用 `for` 循环替代。（$100pts$）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=998244353;
int n,m,dp[19][19][2][1<<18];char a[20][20];
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>a[i][j];
	for(int x=n;x>=0;x--)
		for(int y=m;y>=0;y--)
			for(int r=1;r>=0;r--)
				for(int b=(1<<m)-1;b>=0;b--){
					if(x==n)dp[x][y][r][b]=1;
					else if(y==m)dp[x][y][r][b]=dp[x+1][0][1][b];
					else{
						int s=0;bool q=(b&(1<<y));
						if(a[x][y]=='0'){
							int v=b;
							if(v&(1<<y))v^=(1<<y);
							s=dp[x][y+1][0][v];
						}
						else if(a[x][y]=='1'){
							if(r|q)s+=dp[x][y+1][r][b];
						}else{
							int v=b;
							if(v&(1<<y))v^=(1<<y);
							s+=dp[x][y+1][0][v];
							if(r|q)s+=dp[x][y+1][r][b];
						}
						dp[x][y][r][b]=s%M;
					}
				}
	cout<<dp[0][0][1][B];
	return 0;
}
```

---

