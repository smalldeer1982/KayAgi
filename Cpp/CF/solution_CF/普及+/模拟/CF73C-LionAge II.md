# LionAge II

## 题目描述

Vasya plays the LionAge II. He was bored of playing with a stupid computer, so he installed this popular MMORPG, to fight with his friends. Vasya came up with the name of his character — non-empty string $ s $ , consisting of a lowercase Latin letters. However, in order not to put up a front of friends, Vasya has decided to change no more than $ k $ letters of the character name so that the new name sounded as good as possible. Euphony of the line is defined as follows: for each pair of adjacent letters $ x $ and $ y $ ( $ x $ immediately precedes $ y $ ) the bonus $ c(x,y) $ is added to the result. Your task is to determine what the greatest Euphony can be obtained by changing at most $ k $ letters in the name of the Vasya's character.

## 说明/提示

In the first example the most euphony name will be $ looser $ . It is easy to calculate that its euphony is 36.

## 样例 #1

### 输入

```
winner 4
4
s e 7
o s 8
l o 13
o o 8
```

### 输出

```
36```

## 样例 #2

### 输入

```
abcdef 1
5
a b -10
b c 5
c d 5
d e 5
e f 5
```

### 输出

```
20```

# 题解

## 作者：基地A_I (赞：10)

简单dp题，但是我太弱了，只好来写一写

------------

设 $f[i][j][y]$ 表示前 $i$ 个字符， 修改 $j$ 次， 这一位字符是 $y$ 的最大默契度

进而可以退出方程

$$f[i][j][y]=\max\{f[i][j][y],f[i-1][j-1][x]+C(x,y)\}(y !=S_i)$$

$$=\max\{f[i][j][y],f[i-1][j][x]+C(x,y)\}(y==S_i)$$

（括号里是条件）

枚举 $x$ ， $C(x,y)$ 就是题目中给出 $x,y$ 相邻的价值

------------

初始化：

```cpp
memset(f, 0xaf, sizeof(a));
for(int i=0;i<26;++i)
	if(i+'a' == s[0]) f[1][0][i] = 0;
   else f[1][1][i] = 0;
```

（带着大家复习一下 ``memset(f, 0xaf, sizeof(f))`` 是赋极小值）

把有用的状态，或者说存在的状态理出来，其他的状态赋极小值，不能从那些状态转移过来。只有在dp的过程中，哪些状态才可以不断有值。

------------

统计答案：

$$ans=\max\{f[len][i][j]\}(0<=i<=k)(0<=j<26)$$

------------

Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define INF 0x3f3f3f3f
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 107;
int k,n;
string s;
map<string,int> C;
int f[N][N][30];
int main()
{
	cin>>s; k = read(), n = read();
	for(int i=1;i<=n;++i) {
		string a,b,c; cin>>a>>b;
		c = a+b; C[c] = read();
	}
	memset(f, 0xaf, sizeof(f));	//所有状态都没有
	for(int i=0;i<26;++i)
		if(i+'a' == s[0]) f[1][0][i] = 0;
		else f[1][1][i] = 0; 
	for(int i=2;i<=s.length();++i)
		for(int j=0;j<=min(i,k);++j)
			for(int x=0;x<26;++x)
				for(int y=0;y<26;++y) {
					string chx,chy,ch;
					chx = x+'a', chy = y+'a';
					ch = chx + chy;
					if(y+'a' == s[i-1]) {	//字符串的s_i 小一位 
						f[i][j][y] = max(f[i][j][y],f[i-1][j][x]+C[ch]);
					} else if(j>0) {
						f[i][j][y] = max(f[i][j][y],f[i-1][j-1][x]+C[ch]);
					}
				}
	int ans = -INF;
	for(int i=0;i<=k;++i)
		for(int j=0;j<26;++j)
			ans = max(ans,f[s.length()][i][j]);
	printf("%d\n",ans);
	return 0;
}
/*
akcbd 2
3
a d 55
b z 100
b c 50

155
*/
```

------------

不妨点个赞吧（~~虽然在洛谷做这种CF题的人少~~）

---

## 作者：细数繁星 (赞：2)

不简单的 dp 题，祭一篇题解。

设：$f_{i,j,k}$ 表示前 $i$ 个字符，修改 $j$ 次，修改后为字母 $k$ 的最优解。

瞪眼法可以瞪出方程（下标有点多，方便观察调大了些）：

$$
\Large f_{i,j,k}=\max\limits_{0<x,y<26}\{ f_{i-1,j-[s_i\neq y],x}+C(x,y) \}
$$

初始化：第一个字符至多修改一次，因此：$f_{0,[c_0\neq x],x}=0$，$0<x<26$。除此之外，所有 $f_{i,j,k}$ 赋为一个极小的值。

答案为 $\max\limits_{0<x<26,\quad 0<i<k}\{f_{|s|,i,x}\}$。

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
	
}
#define ll int
ll dp[106][106][128];
ll ys[128][128];

main() {
//	int t; cin >> t; while (t--) solve();
  stg s;
  int k, n;
  cin >> s >> k >> n;
  memset(ys, 0, sizeof ys);
  rep(i, 1, n) {
    char a, b;
    cin >> a >> b;
    cin >> ys[a][b];
  } 
  memset(dp, -63, sizeof dp);
  repq(i, 0, 26) 
    dp[0][(s[0] - 'a' )!= i][i] = 0;
  repq(i, 0, s.size() - 1) {
    rep(j, 0, k) {
      repq(p, 0, 26) {
        if (dp[i][j][p] > -1e9) {
          repq(q, 0, 26) {
            ll tmp = dp[i + 1][j + ((s[i + 1] - 'a') != q)][q];
            dp[i + 1][j + ((s[i + 1] - 'a') != q)][q] = max(tmp, dp[i][j][p] + ys[p + 'a'][q + 'a']);
          }
        }
      }
    }
  }
  ll ans = INT_MIN;

  rep(i, 0, k) {
    repq(j, 0, 26) {
      ans = max(ans, dp[s.size() - 1][i][j]);
    }
  }
  cout << ans;
	return 0;
}

```

[这里贴出提交记录（CF 貌似禁止公开了，这里证明一下自己做过，逃）。](https://codeforces.com/submissions/2044_space_elevator)

---

## 作者：Lily_White (赞：2)

DP。

设$dp[i][j][k]$代表**处理到第$i$位，已经更换了$j$次，现在位置是$k$** 的最优解。

外层枚举$i,j$，然后枚举原先的$p$和现在的$q$。转移时，可以通过$j \to j + (s[i+1] \neq q)$来判断是不是做出了更改操作。状态转移是
$$dp[i][j+\left(s[i+1]\neq q\right)][q]=
\max(dp[i][j+\left(s[i+1]\neq q\right)][q], dp[i][j][p] + dist[p][q])$$

其中$dist[p][q]$代表$p$和$q$之间产生的权值，初始对于所有$1 \leq i \leq n, dp[0][s[0] \neq i][i]=0$，把其他的$dp$值设为$-\text{INF}$即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
const int N = 130, K = 30;
string s;
int k, n, m;
int d[K][K], dp[N][N][K];
int main() {
	cin >> s;
	n = s.length();
	rep(i, n) s[i] -= 'a';
	cin >> k >> m;
	repn(i, m) {
		char f, t;
		int b;
		cin >> f >> t >> b;
		d[f - 'a'][t - 'a'] = b;
	}
	memset(dp, -INF, sizeof(dp));
	rep(i, 26) dp[0][s[0] != i][i] = 0; 
	rep(i, n - 1) {
		rep(j, k + 1) {
			rep(p, 26) {
				if (dp[i][j][p] != -INF) {
					rep(q, 26) {
						dp[i + 1][j + (s[i + 1] != q)][q] = max(dp[i + 1][j + (s[i + 1] != q)][q], dp[i][j][p] + d[p][q]);
					}
				}
			}
		}
	}
	int ans = -INF;
	rep(i, k + 1)
		rep(c, 26)
			ans = max(ans, dp[n - 1][i][c]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

令 $f(i,j,k)$ 前 $i$ 个字符中修改 $j$ 次，这一位字符为 $k$ 的最大价值，$C(x,y)$ 为题目中相邻两个字母的价值。

则有：
$$
\large f(i,j,k)_{(2\le|S|\le n,0 \le \min(|S|,i),1\le k \le 26)}=\max\{f(i-1,j-1,k_1)+C(k_1,k)\}(k \ne S_i)\\
=\max\{f(i-1,j,k_1)+C(k_1,k)\}(k = S_i)
$$
注意：最后统计答案时候，是统计每种修改多少次的可能，而不是修改 $q$ 次的 $\max$（Wa on 30）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r; i >= l; --i)
using namespace std;

char s1[101];
int n, m;
int f[101][101][30], s[101], a[30][30];

main() {
    cin >> (s1 + 1) >> n >> m;
    int len = strlen(s1 + 1);

    rep(i, 1, len) s[i] = s1[i] - 'a' + 1;

    memset(a, 0, sizeof a);
    rep(i, 1, m) {
        char x, y;
        int z;
        cin >> x >> y >> z;
        a[x - 'a' + 1][y - 'a' + 1] = z;
    }

    memset(f, -0x3f, sizeof f);
    rep(k, 1, 26) f[1][s[1] != k][k] = 0;
    rep(i, 2, len)
        rep(j, 0, min(i, n)) 
            rep(k1, 1, 26)
                rep(k, 1, 26)
                    if (k == s[i]) 
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j][k1] + a[k1][k]);
                    else if (j > 0) 
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k1] + a[k1][k]);

    int ans = LLONG_MIN;
    rep(i, 0, len)
        rep(j, 1, 26) 
            ans = max(ans, f[len][i][j]);

    cout << ans;
    return 0;
}


```

---

## 作者：heyZZZ (赞：0)

思路：

$dp_{i,j,c}$ 它表示在前 $i$ 个字符中使用了 $j$ 次更改操作。

并且最后一个字符是 $c$ 的情况下所能达到的最大美丽度。

状态转移方程：

如果 $m=s[i-1]- \texttt a $：$ dp_{i,j,m}=\max\{dp_{i,j,m},dp_{i-1,j,q}+c_{q,m}\}$

如果 $m \ne s[i-1]-\texttt a$：$dp_{i,j,m}=\max\{dp_{i,j,m},dp_{i-1,j-1,q}+c_{q,m}\}$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c[26][26],dp[105][105][26],k,n,p,ans=INT_MIN;
string s;
char x,y;
signed main() {
	cin>>s>>k>>n;
    for(int i=1;i<=n;i++){
		cin>>x>>y>>p;
		c[x-'a'][y-'a']=p;
	}
	for(int i=1;i<=s.size();i++)
		for(int m=0;m<26;m++) dp[i][0][m]=-1e9;
	dp[1][0][s[0]-'a']=0;
	for(int i=2;i<=s.size();i++)
		for(int j=0;j<=k;j++)
			for(int m=0;m<26;m++)
				if(m==s[i-1]-'a')
					for(int q=0;q<26;q++) dp[i][j][m]=max(dp[i][j][m],dp[i-1][j][q]+c[q][m]);	
				else if(j)
					for(int q=0;q<26;q++) dp[i][j][m]=max(dp[i][j][m],dp[i-1][j-1][q]+c[q][m]);
    for(int m=0;m<26;m++) ans=max(ans,dp[s.size()][k][m]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：__Hacheylight__ (赞：0)

非常沙雕的 $dp$

$dp[i][j][k]$ 表示处理到位置 $i$, 还剩下 $j$ 次机会, 上一位填写的是 $k$

如果不改： $dp[i][j][k]+val(k,s[i+1])\rightarrow dp[i+1][j][s[i+1]]$

如果改，枚举当前位置填的字符 $c$

$dp[i][j][k]+val(k,c)\rightarrow dp[i+1][j-1][c]$

$dp[0][k][26]=0$

我写了记忆化搜索

```cpp
string s ;
int dp[7 * N][N][30] ;
int val[30][30] ;
int n, k ;

int solve(int i, int rem, int pre) {
	if (rem < 0) return -iinf ;
	if (!s[i]) return 0 ;
	int& ans = dp[i][rem][pre] ;
	if (~ans) return ans ;
	ans = solve(i + 1, rem, s[i] - 'a') + val[pre][s[i] - 'a'] ;
	rep(j, 0, 25) chmax(ans, solve(i + 1, rem - 1, j) + val[pre][j]) ;
	return ans ;
}

signed main() {
	cin >> s >> k >> n ;
	while (n--) {
		char a, b ; int c ;
		cin >> a >> b >> c ;
		val[a - 'a'][b - 'a'] = c ;
	}
	ass(dp, -1) ;
	printf("%d\n", solve(0, k, 26)) ;
	return 0 ;
}

```

---

