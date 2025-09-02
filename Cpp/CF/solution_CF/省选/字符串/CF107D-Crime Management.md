# Crime Management

## 题目描述

Zeyad 想要在埃及犯下 $n$ 起罪行，并且不受惩罚。罪行有几种类型。例如，贿赂是一种罪行，但如果重复两次，它就不被视为犯罪。因此，贿赂在重复偶数次时不被视为犯罪。超速也是一种罪行，但如果其重复的次数是 5 的倍数，它也不被视为犯罪。

更具体地说，已知有 $c$ 条关于罪行重复的条件。每个条件描述了罪行的类型 $t_{i}$ 及其重复的次数限制 $m_{i}$ 。如果 Zeyad 犯下的罪行 $t_{i}$ 的次数是 $m_{i}$ 的倍数，则 Zeyad 不会因为该罪行而受到惩罚。如果某种罪行出现多次，满足其中任意一个条件即可不受惩罚。当然，如果某罪行的次数为零，Zeyad 对该罪行无罪。

现在，Zeyad 想知道有多少种方式可以精确犯下 $n$ 起罪行且不受惩罚。

罪行的顺序是重要的。更正式地说，犯下 $n$ 起罪行的两种方式（序列 $w1$ 和 $w2$ ）如果对所有 $1 \leq i \leq n$ ，$w1_{i} = w2_{i}$ ，那么它们是相同的方式。

## 说明/提示

在第一个测试用例中，16 种方式是：AAAAA，AAABB，AABAB，AABBA，ABAAB，ABABA，ABBAA，BAAAB，BAABA，BABAA，BBAAA，ABBBB，BABBB，BBABB，BBBAB，BBBBA。

## 样例 #1

### 输入

```
5 2
A 1
B 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
6 3
A 1
B 2
C 3
```

### 输出

```
113
```

## 样例 #3

### 输入

```
8 3
A 2
A 3
B 2
```

### 输出

```
128
```

# 题解

## 作者：一叶知秋。 (赞：7)

我们发现乘积小于等于 $\text{123}$ ，设 $mul_i=\prod\limits_{j=1}^{c}m_j[t_j = i]$ ，就是相当于这一种限制的积，然后我们发现在每一种的个数对 $mul_i$ 取膜的情况下，状态数最多只有 $123$ 种，就可以考虑把状态压缩为一维。

发现根本不需要搜出所有状态再给编号，考虑一个二维矩阵中的坐标我们是如何把它转成一个数的，这里就相当于多维的坐标，编号就可以变为：

$((r_1 \times mul_2+r_2)\times mul_3+r_3)...$ （这里 $r_i$ 为对 $mul_i$ 取膜以后的数）

所以可以进行 $\text{DP}$ 

然而 $n \le 10^{18}$ ，发现对于从选 $i$ 个到选 $i+1$ 个，怎么转移与 $i$ 无关，可以在一开始处理出来，所以每一次转移其实本质上都一样，就可以直接套矩阵快速幂了

注意最后答案不是 $f_0$ ，因为有些种类虽然膜 $mul_i$ 不为 $\text{0}$ ，但是可能膜某一个 $m_j$ 为 $0$ ，需要枚举每种状态是否可行，然后可行就加上即可

$code$ :

```cpp
#include<cstdio>
#include<cctype>
#include<vector>

using namespace std;

#define maxn 33
#define maxs 222
#define maxc 1111
#define mod 12345

inline long long read(){
	long long r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

inline char get_c(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}

int N=1;

long long n;

int cnt,mul[maxn];

long long ans,f[maxs],a[maxs][maxs],c[maxs][maxs];

vector<int> m[maxn];

inline void mulself(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			for(int k=0;k<N;k++)
				(c[i][j]+=a[i][k]*a[k][j]%mod)%=mod;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++){
			a[i][j]=c[i][j];
			c[i][j]=0;
		}
}

inline void multi(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			(c[0][i]+=f[j]*a[i][j]%mod)%=mod;
	for(int i=0;i<N;i++){
		f[i]=c[0][i];
		c[0][i]=0;
	}
}

int main(){
	n=read(),cnt=read();
	for(int i=1;i<=cnt;i++){
		int t=get_c()-'A'+1;
		int val=read();
		m[t].push_back(val);
		if(!mul[t])mul[t]=1;
		mul[t]*=val;
	}//没有限制的种类是不能选的，所以mul开始要全置0
	for(int i=1;i<=26;i++)
		if(mul[i])N*=mul[i];
	N++;
	for(int i=0;i<N;i++){//枚举对于每种状态
		int num=i;//选一种以后能转移到哪一个
		long long mult=1;
		for(int j=26;j>=1;j--){
			if(!mul[j])continue;
			int tot=num%mul[j];
			int s=i-tot*mult;
			tot++;
			tot%=mul[j];
			s+=tot*mult;
			num/=mul[j];
			mult*=mul[j];
			a[s][i]++;//存在该转移
		}
	}
	f[0]=1;
	for(;n;n>>=1){
		if(n&1)multi();
		mulself();
	}
	for(int i=0;i<N;i++){//找合法状态
		int num=i;
		bool ok=1;
		for(int j=26;j>=1;j--){
			if(!mul[j])continue;
			int tot=num%mul[j];
			bool b=0;
			for(int k=0;k<(int)m[j].size();k++)
				b|=((tot%m[j][k])==0);//只要满足一种即可
			ok&=b;
			num/=mul[j];
		}
		if(ok)(ans+=f[i])%=mod;//合法就加上，记得取膜
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Reaepita (赞：5)

我们可以考虑DP的做法

我们设 `maxn[c]` 为第 $c$ 种字符的所有限制 $cnt$ 的乘积

`dp[i][a][b][c][d].....[z]`，表示枚举到字符串的第 $i$ 位，

每个字符为，出现次数 $\%$  `maxn[c]` 的状态下字符串的总数。

那么最后求答案直接统计合法的方案就行了。

但是这么做空间，时间都是不允许的，所以我们要使用矩阵快速幂来进行优化。

我们可以考虑使用 $map$ 来对每种状态重新编号，将状态存入矩阵中进行转移。

矩阵第 $i$ 行第 $j$ 列如果有值 1，则说明可以转移，最后矩阵的 $n-1$ 次幂
就是状态转移了 $n$ 次，直接统计第 1 行的合法方案。

我统计答案，预处理矩阵用的DFS

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int mod=12345;
long long n;
int m,ans=0;
int maxn[30];
vector<int>ok[30];
struct Matrix
{
	int a[125][125];
	Matrix()
	{
		memset(a,0,sizeof(a));
	};
	Matrix operator * (const Matrix &x) const
	{
		Matrix ans=Matrix();
		for(int i=1;i<=123;i++)
		for(int j=1;j<=123;j++)
		{
			for(int k=1;k<=123;k++)ans.a[i][j]+=a[i][k]*x.a[k][j]%mod,ans.a[i][j]%=mod;
			
		}
		return ans;
	}
	Matrix operator ^ (const long long &x) const
	{
		Matrix ans=(*this),temp=(*this);
		long long now=x;
		while(now)
		{
			if(now&1)ans=ans*temp;
			temp=temp*temp;
			now>>=1;
		}
		return ans;
	}
}mat;
struct dat
{
	int val[30];
	bool operator < (const dat& a)const 
	{
		for(int i=1;i<=26;i++)
		{
			if(val[i]==a.val[i])continue;
			return val[i]<a.val[i];
		}
		return false;
	}
}chuzhi;
map<dat,int>mp;
int pcnt=0;
void dfs(int pos,dat now)
{
	if(pos==27)
	{
		mp[now]=++pcnt;
		return ;
	}
	if(maxn[pos]==0)dfs(pos+1,now);
	for(int i=0;i<maxn[pos];i++)
	{
		now.val[pos]=i;
		dfs(pos+1,now);
	}
}
void calc(int pos,dat now)
{
	if(pos==27)
	{
		ans+=mat.a[1][mp[now]];
		ans%=mod;
		return ;
	}
	if(maxn[pos]==0)calc(pos+1,now);
	for(int i=0;i<maxn[pos];i++)
	{
		bool flag=false;
		for(int j=0;j<ok[pos].size();j++)
		if(i%ok[pos][j]==0){
			flag=true;
			break;
		}
		if(flag)
		{
			now.val[pos]=i;
			calc(pos+1,now);
		}
	}
}
char A;
int x,c;
int main()
{
	scanf("%lld%d",&n,&m);
	if(n==0)//特判 
	{
		printf("1\n");
		return 0;
	}
	if(m==0)//特判 
	{
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		scanf(" %c %d",&A,&x);
		c=A-'A'+1;
		if(maxn[c]==0)maxn[c]=x;
		else maxn[c]*=x;
		ok[c].push_back(x);
		
		
	}
	dfs(1,chuzhi);
	for(map<dat,int>::iterator i=mp.begin();i!=mp.end();i++)
    {
        int s=i->second;
        dat now=i->first;
        for(int j=1;j<=26;j++)
        {
            if(maxn[j]==0)continue;
            dat temp=now;
            temp.val[j]=(temp.val[j]+1)%maxn[j];
            mat.a[s][mp[temp]]++;
        }
    }
    mat=mat^((long long)n-1);
    calc(1,chuzhi);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

考虑到所有限制的乘积 $\le 123$，$n \le 10^{18}$，就想到大概是矩阵乘法了。

首先注意到同一种字符的不同限制不好处理，我们直接模它们的乘积，然后在最后看一下模这些值为 $0$ 的状态的值就好。

肯定是 DP 的，$f_{i, j, k, ...}$ 表示到了第 $i$ 位每种字符的出现次数模限制之后的数，虽然有很多维，但是注意到乘积 $\le 123$，所以我的 DP 数组除了第一维都可以被映射到一个不超过 $123$ 大小的数组上。

然后 $n \le 10^{18}$，我们将 DP 数组转化为二维，发现每一次转移本质上相同，可以爆搜把矩阵打出来，矩阵快速幂即可。

## code

code：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 1e3 + 5;
const int M = 128;
const int mod = 12345;

int n, m, cnt, ans;
int tong[N];
vector < int > chifan[N];
map < vector < int >, int > mp;
vector < int > lim, tmp;

struct matrix {
  int n, m;
  int a[M][M];

  matrix () {
    memset ( a, 0, sizeof ( a ) );
  }
} base, p;

matrix mul ( matrix a, matrix b ) {
  matrix c;
  c.n = a.n, c.m = b.m;
  for ( int k = 1; k <= a.m; k ++ ) {
    for ( int i = 1; i <= a.n; i ++ ) {
      for ( int j = 1; j <= b.m; j ++ ) {
        c.a[i][j] += a.a[i][k] * b.a[k][j] % mod;
        c.a[i][j] %= mod;
      }
    }
  }
  return c;
}

matrix fast_pow ( matrix a, int b ) {
  matrix res;
  res.n = a.n, res.m = a.m;
  for ( int i = 1; i <= res.n; i ++ ) {
    res.a[i][i] = 1;
  }
  while ( b ) {
    if ( b & 1 ) {
      res = mul ( res, a );
    }
    b >>= 1;
    a = mul ( a, a );
  }
  return res;
}

void dfs ( int x ) {
  if ( x == lim.size () ) {
    mp[tmp] = ++ cnt;
    return ;
  }
  for ( int i = 0; i < lim[x]; i ++ ) {
    tmp.push_back ( i );
    dfs ( x + 1 );
    tmp.pop_back ();
  }
}

void dfs2 ( int x, int id ) {
  if ( x == lim.size () ) {
    int u = mp[tmp], tmpp = tmp[id];
    tmp[id] = ( tmp[id] + 1 ) % lim[id];
    int v = mp[tmp];
    tmp[id] = tmpp;
    base.a[u][v] ++;
    return ;
  }
  for ( int i = 0; i < lim[x]; i ++ ) {
    tmp.push_back ( i );
    dfs2 ( x + 1, id ) ;
    tmp.pop_back ();
  }
}

void dfs3 ( int x ) {
  if ( x == lim.size () ) {
    int cnt = 0, f = 1;
    for ( int i = 'A'; i <= 'Z'; i ++ ) {
      if ( tong[i] ) {
        int flag = 1;
        for ( int k : chifan[i] ) {
          if ( tmp[cnt] % k == 0 ) {
            flag = 0;
            break;
          }
        }
        if ( flag ) {
          f = 0;
          break;
        }
        cnt ++;
      }
    }
    if ( f == 1 ) {
      ans += p.a[1][mp[tmp]];
      ans %= mod;
    }
    return ;
  }
  for ( int i = 0; i < lim[x]; i ++ ) {
    tmp.push_back ( i );
    dfs3 ( x + 1 );
    tmp.pop_back ();
  }
}

void Solve () {
  ios :: sync_with_stdio ( false );
  cin.tie ( 0 ), cout.tie ( 0 );
  cin >> n >> m;
  for ( int i = 1; i <= m; i ++ ) {
    char c;
    int k;
    cin >> c >> k;
    if ( !tong[c] ) {
      tong[c] = k;
    }
    else {
      tong[c] *= k;
    }
    chifan[c].push_back ( k );
  }
  for ( int i = 'A'; i <= 'Z'; i ++ ) {
    if ( tong[i] ) {
      lim.push_back ( tong[i] );
    }
  }
  dfs ( 0 );
  int c = 0;
  for ( int i = 'A'; i <= 'Z'; i ++ ) {
    if ( tong[i] ) {
      dfs2 ( 0, c ++ );
    }
  }
  base.n = base.m = cnt, p.n = 1, p.m = cnt;
  p.a[1][1] = 1;
  base = fast_pow ( base, n );
  p = mul ( p, base );
  dfs3 ( 0 );
  cout << ans;
}
 
signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}

```

---

