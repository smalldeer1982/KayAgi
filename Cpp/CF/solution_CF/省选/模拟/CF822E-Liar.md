# Liar

## 题目描述

The first semester ended. You know, after the end of the first semester the holidays begin. On holidays Noora decided to return to Vičkopolis. As a modest souvenir for Leha, she brought a sausage of length $ m $ from Pavlopolis. Everyone knows that any sausage can be represented as a string of lowercase English letters, the length of which is equal to the length of the sausage.

Leha was very pleased with the gift and immediately ate the sausage. But then he realized that it was a quite tactless act, because the sausage was a souvenir! So the hacker immediately went to the butcher shop. Unfortunately, there was only another sausage of length $ n $ in the shop. However Leha was not upset and bought this sausage. After coming home, he decided to cut the purchased sausage into several pieces and number the pieces starting from $ 1 $ from left to right. Then he wants to select several pieces and glue them together so that the obtained sausage is equal to the sausage that Noora gave. But the hacker can glue two pieces together only when the number of the left piece is less than the number of the right piece. Besides he knows that if he glues more than $ x $ pieces, Noora will notice that he has falsified souvenir sausage and will be very upset. Of course Leha doesn’t want to upset the girl. The hacker asks you to find out whether he is able to cut the sausage he bought, and then glue some of the pieces so that Noora doesn't notice anything.

Formally, you are given two strings $ s $ and $ t $ . The length of the string $ s $ is $ n $ , the length of the string $ t $ is $ m $ . It is required to select several pairwise non-intersecting substrings from $ s $ , so that their concatenation in the same order as these substrings appear in $ s $ , is equal to the string $ t $ . Denote by $ f(s,t) $ the minimal number of substrings to be chosen so that their concatenation is equal to the string $ t $ . If it is impossible to choose such substrings, then $ f(s,t)=∞ $ . Leha really wants to know whether it’s true that $ f(s,t)<=x $ .

## 说明/提示

Let's consider the first sample.

In the optimal answer, Leha should cut the sausage he bought in the following way: hloyaygrt = h + loy + a + y + g + rt. Then he numbers received parts from $ 1 $ to $ 6 $ :

- h — number $ 1 $
- loy — number $ 2 $
- a — number $ 3 $
- y — number $ 4 $
- g — number $ 5 $
- rt — number $ 6 $

Hereupon the hacker should glue the parts with numbers $ 2 $ , $ 4 $ and $ 6 $ and get sausage loyygrt equal to one that is given by Noora. Thus, he will have to glue three pieces. Since $ x=3 $ you should print "YES" (without quotes).

In the second sample both sausages coincide with sausages from the first sample. However since $ x=2 $ you should print "NO" (without quotes).

## 样例 #1

### 输入

```
9
hloyaygrt
6
loyyrt
3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
9
hloyaygrt
6
loyyrt
2
```

### 输出

```
NO
```

# 题解

## 作者：Alex_Wei (赞：4)

UPD on 2022.3.8：修改一处笔误。

UPD on 2022.6.15：修改笔误。

> I. [CF822E Liar](https://www.luogu.com.cn/problem/CF822E)
>
> [常见字符串算法](https://www.cnblogs.com/alex-wei/p/Common_String_Theory_Theory.html) SA。

使用贪心的思想可知在一轮匹配中，我们能匹配尽量匹配，即若从 $s_i$ 和 $t_j$ 开启新的一段，那么我们一定会匹配直到第一个 $k$ 使得 $s_{i + k} \neq t_{j + k}$。因为匹配到一半就断掉没有匹配到不能继续为止更优。若前者存在符合题意的分配方案，则后者必然存在，调整法易证。

注意到 $x\leq 30$ 的限制，说明总状态数不会很多，考虑动态规划。

设 $f_{i, j}$ 表示 $s[1, j]$ 选出 $i$ 个子串时最多能匹配到 $t$ 的哪个位置。对于每个 $f_{i, j}$，首先可以转移到 $f_{i, j + 1}$ 表示不开启一段匹配。若开启一段匹配，则需找到 $s[j + 1, n]$ 和 $t[f_{i - 1, j} + 1, m]$ 的最长公共前缀长度 $L$，并令 $f_{i, j + L} \gets \max(f_{i, j + L}, f_{i - 1, j} + L)$。

求一个字符串某两个后缀的 LCP 是后缀数组的拿手好戏，时间复杂度 $\mathcal{O}(n(x + \log n))$。

本题同时用到了贪心，DP 和 SA 这三个跨领域的算法，是好题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int K = 18;
const int N = 2e5 + 5;
int n, m, tot, x, lg[N], f[31][N];
int ht[N], mi[K][N];
char s[N], t[N], st[N];
int sa[N], rk[N], ork[N], buc[N], id[N];
bool cmp(int a, int b, int w) {return ork[a] == ork[b] && ork[a + w] == ork[b + w];}
void build() {
  int m = 1 << 7, p = 0;
  for(int i = 1; i <= tot; i++) buc[rk[i] = st[i]]++;
  for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
  for(int i = tot; i; i--) sa[buc[rk[i]]--] = i;
  for(int w = 1; ; w <<= 1, m = p, p = 0) {
    for(int i = tot - w + 1; i <= tot; i++) id[++p] = i;
    for(int i = 1; i <= tot; i++) if(sa[i] > w) id[++p] = sa[i] - w;
    memset(buc, 0, sizeof(buc));
    memcpy(ork, rk, sizeof(rk));
    p = 0;
    for(int i = 1; i <= tot; i++) buc[rk[id[i]]]++;
    for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
    for(int i = tot; i; i--) sa[buc[rk[id[i]]]--] = id[i];
    for(int i = 1; i <= tot; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
    if(p == tot) break;
  }
  for(int i = 1, k = 0; i <= tot; i++) {
    if(k) k--;
    while(st[i + k] == st[sa[rk[i] - 1] + k]) k++;
    ht[rk[i]] = k;
  }
  for(int i = 1; i <= tot; i++) mi[0][i] = ht[i];
  for(int i = 1; i <= lg[tot]; i++)
    for(int j = 1; j + (1 << i) - 1 <= tot; j++)
      mi[i][j] = min(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
}
int lcp(int i, int j) { // s[i] & t[j]
  if(j > m || i > n) return 0;
  j += n + 1;
  if((i = rk[i]) > (j = rk[j])) swap(i, j);
  int d = lg[j - (i++)];
  return min(mi[d][i], mi[d][j - (1 << d) + 1]);
}
int main() {
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> s + 1 >> m >> t + 1;
  for(int i = 1; i <= n; i++) st[++tot] = s[i];
  st[++tot] = '#';
  for(int i = 1; i <= m; i++) st[++tot] = t[i];
  for(int i = 2; i <= tot; i++) lg[i] = lg[i >> 1] + 1;
  build();
  cin >> x;
  for(int i = 1; i <= x; i++)
    for(int j = 0; j < n; j++) {
      int L = lcp(j + 1, f[i - 1][j] + 1);
      f[i][j + L] = max(f[i][j + L], f[i - 1][j] + L);
      f[i][j + 1] = max(f[i][j + 1], f[i][j]);
    }
  if(f[x][n] == m) puts("YES");
  else puts("NO");
  return cerr << "Time: " << clock() << endl, 0;
}
/*
2022/6/15
start coding at 8:55
finish debugging at 9:20
*/
```

---

## 作者：tzc_wk (赞：3)

## DP+二分+Hash

刚一看到题面，心想：这道题和[NOIP 2015 D2T2](https://www.luogu.org/problem/P2679)好像。因此我们可以使用仿照哪一题，使用dp的方法

我们设$ dp[i][j] $表示用$ s $的前$ i $位切割$ j $次，最多可以匹配到$ t $的多少位。很显然

```
dp[i+1][j]=max(dp[i+1][j],dp[i][j])
dp[i+k][j+1]=max(dp[i+k][j+1],dp[i][j]+k)
//其中s[i+1]=t[dp[i][j]+1],s[i+2]=t[dp[i][j]+2],...,s[i+k]=t[dp[i][j]+k]
```
而这个k值我们可以考虑二分+哈希在$ O(logn) $的时间内求得。

完整代码如下，时间复杂度$ O(nx logn) $，细节见注释：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;//哈希的模数
const int B=127;//哈希的底数
int n,m,x;
string s,t;
int f[100005][32];//dp数组
int s1[100005],s2[100005],c[100005];//s1表示字符串s的哈希值，s2表示字符串t的哈希值，c[i]表示B的i次方%MOD
bool check(int l1,int r1,int l2,int r2){//判断两字符串是否相等
	return ((s1[r1]-s1[l1-1]*c[r1-l1+1])%MOD+MOD)%MOD==((s2[r2]-s2[l2-1]*c[r2-l2+1])%MOD+MOD)%MOD;
}
int get(int x,int y){//二分寻找上文中所说的i+k的值
	int l=x,r=min(n,m+x-y);
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(x,mid,y,mid-x+y))	l=mid+1;
		else						r=mid-1;
    }
    return r;
}
signed main(){
	cin>>n>>s>>m>>t>>x;
	s=" "+s;t=" "+t;
	c[0]=1;
	for(int i=1;i<=n;c[i]=c[i-1]*B%MOD,i++)
		s1[i]=(s1[i-1]*B+s[i]-'a'+1)%MOD;
	for(int i=1;i<=m;i++)
		s2[i]=(s2[i-1]*B+t[i]-'a'+1)%MOD;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=x;j++){//dp的过程
			f[i+1][j]=max(f[i][j],f[i+1][j]);
			if(j!=x){
				int p1=get(i+1,f[i][j]+1);
				if(p1>i)	f[p1][j+1]=max(f[p1][j+1],p1-i+f[i][j]);
			}
		}
	}
	for(int i=1;i<=x;i++)
		if(f[n][i]==m)//如果找到能够完全匹配的就输出YES
			return puts("YES"),0;
	puts("NO");
}
```

---

## 作者：violin_wyl (赞：2)

# Liar

## 解析：

### 题目大意：

给定两个字符串 $s,t$，长度分别为 $n,m$（$m\leq n\leq 10^5$）。你需要选择 $s$ 的若干个两两不相交的子串，然后将它们按照原先在 $s$中出现的顺序合并起来，希望得到 $t$。

令 $f(s,t)$ 表示要选择的 $s$ 的子串数目，以便它们的并是串 $t$。如果无法合理选择这样的子串，则$f(s,t)=+∞$。

现在我们想知道，对于给定的 $s,t$，是否有 $f(s,t)\leq x$（$x\leq 30$）。

**一句话题意：在 $s$ 串中找不超过 $x$ 个两两不相交的子串，使得最后这些子串首尾连接后得到 $t$，你的任务就是判断是否可行**

--------------------------

### 思路：

板刷到的题，最开始看题发现这不就一个板子题吗，然后就还是码，码到一半发现假了，zbl很久。

最开始我考虑设 $dp_{i,j}$ 表示 $t$ 串前 $i$ 位拆成 $j$ 段后能在 $s$ 中匹配的最小的位置，根据贪心易发现对于 $i,j$，他能在 $s$ 中匹配的位置肯定越靠前越好，结果就假了。

我们考虑假的原因，在某一次失配后，我们无法快速找到一下个可以匹配且是极长连续段的位置，最开始我考虑可以用类似子序列自动机一样往后找，但是发现找到的不一定是最长的，所以可以被hack掉（希望大佬有人顺着这个思路接着想想，笔者太菜了没接着想了）。

其实 dp 的设计以没什么问题，只是把 $s,t$ 交换一下位置就行了，考虑设 $dp_{i,j}$ 表示 $s$ 串前 $i$ 位拆成 $j$ 段后能在 $s$ 中匹配的最大的位置，为什么这样就是对的呢？考虑每次选择了位置 $i$，我们钦定这个位置就是极长连续段的起始，而拼成的 $t$ 一定是连续的，所以不会存在在 $t$ 中失配的情况。

有转移方程：
$$
dp_{i,j}=dp_{i-1,j}\\
dp_{i+k,j+1}=dp_{i,j}+k
$$
其中我设 $k$ 为当前极长连续段的长度。

往后找极长段我用到的是二分+哈希，用 SA 复杂度会更好看一点。

时间复杂度 $\mathcal O(nx\log n)$。

----------------------------------------------------

## code：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int sed1 = 27, sed2 = 127;
const int mod1 = 11451499, mod2 = 19260817; // 阴间的双哈希
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n, m, k;
char a[N], b[N];
int dp[N][40];
int ha1[N], ha2[N], inv1[N];
int hb1[N], hb2[N], inv2[N];
int fastpow (int a, int p, int mods)
{
    int res = 1;
    while (p)
    {
        if (p & 1) res = (res * a) % mods;
        p >>= 1;
        a = (a * a) % mods;
    }
    return res;
}
void init ( ) // 没错，cf他卡哈希
{
    for (int i = 1, bas = 1; i <= n; i++, bas = (bas * sed1) % mod1)
        ha1[i] = (ha1[i - 1] + ((a[i] - 'a' + 1) * bas) % mod1) % mod1;
    for (int i = 1, bas = 1; i <= n; i++, bas = (bas * sed2) % mod2)
        ha2[i] = (ha2[i - 1] + ((a[i] - 'a' + 1) * bas) % mod2) % mod2;
    for (int i = 1, bas = 1; i <= m; i++, bas = (bas * sed1) % mod1)
        hb1[i] = (hb1[i - 1] + ((b[i] - 'a' + 1) * bas) % mod1) % mod1;
    for (int i = 1, bas = 1; i <= m; i++, bas = (bas * sed2) % mod2)
        hb2[i] = (hb2[i - 1] + ((b[i] - 'a' + 1) * bas) % mod2) % mod2;
    inv1[0] = 1; inv1[1] = fastpow (sed1, mod1 - 2, mod1);
    for (int i = 2; i <= n; i++) inv1[i] = (inv1[i - 1] * inv1[1]) % mod1;
    inv2[0] = 1; inv2[1] = fastpow (sed2, mod2 - 2, mod2);
    for (int i = 2; i <= n; i++) inv2[i] = (inv2[i - 1] * inv2[1]) % mod2;
}
bool check (int l1, int r1, int l2, int r2)
{
    int fa1 = (ha1[r1] - ha1[l1 - 1] + mod1) % mod1 * inv1[l1 - 1] % mod1;
    int fa2 = (ha2[r1] - ha2[l1 - 1] + mod2) % mod2 * inv2[l1 - 1] % mod2;
    int fb1 = (hb1[r2] - hb1[l2 - 1] + mod1) % mod1 * inv1[l2 - 1] % mod1;
    int fb2 = (hb2[r2] - hb2[l2 - 1] + mod2) % mod2 * inv2[l2 - 1] % mod2;
    return (fa1 == fb1) & (fa2 == fb2);
}
int find (int x, int y)
{
    int l = x, r = min (n, x + m - y), res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check (x, mid, y, mid - x + y)) l = mid + 1, res = mid;
        else r = mid - 1;
    }
    return res;
}
signed main()
{
    n = read ( ); scanf ("%s", a + 1);
    m = read ( ); scanf ("%s", b + 1);
    k = read ( );
    init ( );
    memset (dp, ~0x3f, sizeof (dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= min (i, k); j++)
        {
            if (dp[i - 1][j] < 0) continue;
            dp[i][j] = max (dp[i - 1][j], dp[i][j]);
            if (j < k)
            {
                int x = find (i, dp[i - 1][j] + 1);
                dp[x][j + 1] = max (dp[x][j + 1], dp[i - 1][j] + x - i + 1);
            }
        }
    }
    int ans = false;
    for (int i = 1; i <= k; i++)
        if (dp[n][i] == m) ans = true;
    printf (ans ? "YES\n" : "NO\n");
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

### 题意

给定字符串 $s,t$，问能否在 $s$ 中找最多 $x$ 个不相交的子串拼起来得到 $t$。$|s|,|t|\le10^5,x\le30$。

### 题解

显然如果你可以用 $s[l_1,r_1]$ 拼到 $t$ 的一段，那么这一段用 $s[l_1,r_2]+s[l_2,r_3](l_1\le r_2<r_1<l_2\le r_3)$ 显然不优，因为你此时剩下可选的位置的长度更小。这代表你每一次可以匹配的时候直接贪心匹配满是对的。

设 $f_{i,j}$ 表示在 $s$ 的前 $i$ 个位置中选最多 $j$ 个不相交的子串可以在 $t$ 中拼得的最长长度。

考虑刷表。哈希加二分找到 $s[i+1,n]$ 和 $t[f_{i,j}+1,m]$ 的最长公共前缀长度 $ms$，用 $f_{i,j}$ 尝试更新 $f_{i+ms,j+1}$，在一层更新完后更新前缀 max 即可。

```cpp
#include <bits/stdc++.h>
#define lint __int128
#define int long long
#define fi first
#define se second
#define Il inline
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_q priority_queue

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;
const int N=1e5,mod=1e9+7;
const db eps=1e-9,pi=acos(-1.0);

mt19937 rnd(time(0));
Il int rint(int l,int r){return rnd()%(r-l+1)+l;}

int n,m,K,f[N+5][30],h[N+5][2],pw[N+5];
string s,t;

Il int hs(int l,int r,int p){return (h[r][p]-h[l-1][p]*pw[r-l+1]%mod+mod)%mod;}

Il int fd(int p1,int p2){
    int l=0,r=min(n-p1,m-p2);
    while(l<=r){
        int mid=(l+r)>>1;
        if(hs(p1,p1+mid,0)^hs(p2,p2+mid,1))r=mid-1;
        else l=mid+1;
    }
    return r+1;
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>s>>m>>t>>K;s=" "+s;t=" "+t;
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*31%mod;
    for(int i=1;i<=n;i++)h[i][0]=(h[i-1][0]*31%mod+s[i]-'a')%mod;
    for(int i=1;i<=m;i++)h[i][1]=(h[i-1][1]*31%mod+t[i]-'a')%mod;
    for(int j=0;j<K;j++){
        for(int i=1;i<=n;i++)f[i][j+1]=f[i][j];
        for(int i=0;i<n;i++){
            int ms=fd(i+1,f[i][j]+1);
            f[i+ms][j+1]=max(f[i+ms][j+1],f[i][j]+ms);
        }
        for(int i=1;i<=n;i++)f[i][j+1]=max(f[i][j+1],f[i-1][j+1]);
    }
    cout<<(f[n][K]^m?"NO":"YES");
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

显然 $S$ 的一段前缀可以匹配上 $T$ 的一段前缀，不妨 $f_{i,j}$ 表示 $S[1,i]$ 划分为至多 $j$ 段最长可以匹配到 $T[1,f_{i,j}]$。

不妨枚举第 $j$ 段的开始位置 $i$，显然第 $j$ 段能接上的条件是 $[j,n]$ 能匹配 $T[l,r]$ 并且 $l \leq f_{i,j-1}+1$，注意到把 $[l,f_{i,j-1}]$ 移到第 $j-1$ 段处是不劣的，因此我们可以直接从 $f_{i,j-1}+1$ 开始匹配，注意到此处我们尽可能匹配更长的段即可，因为假若匹配的段是最长匹配段的一个前缀，把剩下的后缀从后面的位置移动到前面来是不劣的，求解最长的匹配段可以哈希二分，贡献的位置是一段后缀，直接挂在第一个贡献位置，再向后传递贡献即可做到 $O(n \times x \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+114;
int mod[2] = {1145141,998244353};
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
int base = 1387;
int n,m,x;
char S[maxn],T[maxn];
int preS[maxn][2],preT[maxn][2];
int _pow[maxn][2];
int f[maxn],g[maxn];
bool cmp(int l1,int r1,int l2,int r2){
	return ((preS[r1][0]+mod[0]-preS[l1-1][0])%mod[0]*_pow[l2][0]%mod[0]==(preT[r2][0]+mod[0]-preT[l2-1][0])%mod[0]*_pow[l1][0]%mod[0])&&((preS[r1][1]+mod[1]-preS[l1-1][1])%mod[1]*_pow[l2][1]%mod[1]==(preT[r2][1]+mod[1]-preT[l2-1][1])%mod[1]*_pow[l1][1]%mod[1]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	_pow[0][0]=_pow[0][1]=1;
	for(int i=1;i<maxn;i++) _pow[i][0]=_pow[i-1][0]*base%mod[0],_pow[i][1]=_pow[i-1][1]*base%mod[1];
	cin>>n;
	for(int i=1;i<=n;i++) cin>>S[i],preS[i][0]=(preS[i-1][0]+S[i]*_pow[i][0]%mod[0])%mod[0],preS[i][1]=(preS[i-1][1]+S[i]*_pow[i][1]%mod[1])%mod[1];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>T[i],preT[i][0]=(preT[i-1][0]+T[i]*_pow[i][0]%mod[0])%mod[0],preT[i][1]=(preT[i-1][1]+T[i]*_pow[i][1]%mod[1])%mod[1];
	cin>>x;
	for(int y=1;y<=x;y++){
		for(int i=0;i<=n;i++){
			int l=0,r=min(n-i+1,m-f[i]+1);
			while(l+1<r){
				int mid=(l+r)>>1;
				if(cmp(i+1,i+mid,f[i]+1,f[i]+mid)==true) l=mid;
				else r=mid;
			}
			g[i+l]=max(g[i+l],f[i]+l);
		}			
		for(int i=1;i<=n;i++){
			g[i]=max(g[i],f[i-1]);
			f[i]=g[i];
			if(g[i]==m){
				cout<<"YES\n";
				return 0;
			}
		}		
	}
	cout<<"NO\n";
	return 0;
}

```

---

## 作者：Phartial (赞：0)

题意：给你长度分别为 $n,m$ 的两个字符串 $S,T$，再给你一个数 $x$，问是否能在 $S$ 中选出不超过 $x$ 段不交的子串，使得这些子串按顺序拼起来后等于 $T$。

$1\le m\le n\le 10^5$，$1\le x\le 30$。

题解：如果我们在 $S[i]$ 处选择开一段子串拼到 $T$ 上，那肯定是在这一段中贪心地匹配尽量长的位置最优，于是设 $f(i,j)$ 表示在 $S[1:i]$ 中选 $j$ 段子串最长能匹配到 $T$ 的哪里，就有转移：

- $S[i+1]$ 处不开新的一段：$f(i,j)\to f(i+1,j)$；
- $S[i+1]$ 处开新的一段：则我们贪心地进行匹配，最长匹配长度显然是 $k=\operatorname{lcp}(S[i+1:n],T[f(i,j)+1:m])$，则有转移 $f(i,j)+k\to f(i+k,j+1)$。

于是问题转化为求 $S,T$ 的某两个后缀的 lcp，直接把 $S$ 和 $T$ 拼在一起，即可转化成子串 lcp，使用后缀数组与 RMQ 可以解决。

时间复杂度 $\Theta((n+m)\log(n+m)+nx)$。

[code](https://codeforces.com/contest/822/submission/268063453).

---

## 作者：AC_love (赞：0)

一开始打算用 $f(i,  j)$ 表示 $s$ 的前 $i$ 位和 $t$ 的前 $j$ 位匹配所需的切割次数，后来发现数组根本开不下，于是作罢。

然后我观察到 $n, m$ 都很大，但是 $x$ 很小，于是想到可以把 $x$ 放到 DP 的状态设计里。

用 $f(i,  j)$ 表示 $s$ 的前 $i$ 为切割 $j$ 次最多能匹配到 $t$ 的第几位。

那么很显然有：

$$f(i + 1,  j) = \max(f(i,  j), f(i + 1,  j))$$

这种转移就是如果当前这一位我们不取的话，直接从上一位往这里转移。

$$f(i + k,  j + 1) = \max(f(i + k,  j + 1), f(i,  j) + k)$$

其中 $k$ 是 $s$ 从第 $i + 1$ 位开始，$t$ 从第 $f(i,  j)$ 开始时的极长匹配的长度。

这种转移就是：如果 $s$ 从 $i$ 往后 $k$ 位开始和 $t$ 从 $f(i,  j)$ 开始往后 $k$ 位相同的话，我们就可以把 $s$ 往后的这 $k$ 位截下来和 $t$ 往后的这 $k$ 位匹配。

问题转化为如何求 $k$。

这是个很典型的后缀数组的应用，当然也可以用哈希 + 二分来解决，复杂度稍逊一筹，但也可以过。

警告：在做 CF 的题目时，请尽量不要使用单哈希，后果自负！

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 114514;
const int X = 32;
const int seed1 = 29;
const int mod1 = 11451497;
const int seed2 = 41;
const int mod2 = 11451499;
int n, m, x;
char s[N], t[N];
int f[N][X];

int pw1[N];
int pw2[N];

int hash1s[N], hash1t[N];
int hash2s[N], hash2t[N];

void pre()
{
	pw1[0] = pw2[0] = 1;
	for(int i = 1; i <= n; i = i + 1)
		pw1[i] = pw1[i - 1] * seed1,
		pw1[i] %= mod1,
		pw2[i] = pw2[i - 1] * seed2,
		pw2[i] %= mod2;
}

void Hash()
{
	for(int i = 1; i <= n; i = i + 1)
		hash1s[i] = (hash1s[i - 1] * seed1 + s[i] - 'a' + 1) % mod1;
	for(int i = 1; i <= m; i = i + 1)
		hash1t[i] = (hash1t[i - 1] * seed1 + t[i] - 'a' + 1) % mod1;
	for(int i = 1; i <= n; i = i + 1)
		hash2s[i] = (hash2s[i - 1] * seed2 + s[i] - 'a' + 1) % mod2;
	for(int i = 1; i <= m; i = i + 1)
		hash2t[i] = (hash2t[i - 1] * seed2 + t[i] - 'a' + 1) % mod2;
}

bool check(int x, int y, int len)
{
	int h1s = (hash1s[x + len - 1] - hash1s[x - 1] * pw1[len] % mod1 + mod1) % mod1;
	int h1t = (hash1t[y + len - 1] - hash1t[y - 1] * pw1[len] % mod1 + mod1) % mod1;
	int h2s = (hash2s[x + len - 1] - hash2s[x - 1] * pw2[len] % mod2 + mod2) % mod2;
	int h2t = (hash2t[y + len - 1] - hash2t[y - 1] * pw2[len] % mod2 + mod2) % mod2;
	return (h1s == h1t && h2s == h2t);
}

int binary(int x, int y)
{
	int l = -1, r = min(n - x + 1, m - y + 1) + 1;
	while(l < r - 1)
	{
		int mid = (l + r) / 2;
		if(check(x, y, mid))
			l = mid;
		else
			r = mid;
	}
	return l;
}

signed main() 
{
	cin >> n;
	for(int i = 1; i <= n; i = i + 1)
		while(s[i] < 'a' || s[i] > 'z')
			s[i] = getchar();
	cin >> m;
	for(int i = 1; i <= m; i = i + 1)
		while(t[i] < 'a' || t[i] > 'z')
			t[i] = getchar();
	cin >> x;
	pre();
	Hash();
	for(int i = 0; i <= n; i = i + 1)
	{
		for(int j = 0; j <= x; j = j + 1)
		{
			f[i + 1][j] = max(f[i][j], f[i + 1][j]);
			if(j != x)
			{
				int k = binary(i + 1, f[i][j] + 1);
				if(k > 0)
					f[i + k][j + 1] = max(f[i + k][j + 1], f[i][j] + k);
			}
		}
	}
	for(int i = 1; i <= x; i = i + 1)
		if(f[n][i] == m)
		{
			cout << "YES\n";
			return 0;
		}
	cout << "NO\n";
	return 0;
}
```

---

## 作者：why_cb (赞：0)

不要用自然溢出！不要用自然溢出！不要用自然溢出！

（对拍 6h 没结果，我这个小可爱不知道 CF 的险恶）

---
纯贪心做法。

我们考虑一种暴力做法，从左往右遍历 $s$，将当前的 $s_i$ 与之前所有合法的分割方式匹配（包括 0），将产生的新的合法方案塞进去，这样做法显然正确，但是会导致状态数爆炸。

看到 $x\le30$，我们考虑将一些重复状态合并取最优的。于是我们设出 $bkt_{i,j\in\{0,1\}}$，$bkt_{i,0}$ 代表之前分割 $i$ 次，当前遍历到的数匹配上的最优方案，$bkt_{i,1}$ 则是当前遍历到的数没匹配到的最优方案。

我们考虑如何定义最优方案。

一种很显然的想法是将匹配到 $t$ 中的右端点取 $\max$，我们会得到如下转移方程：

$s_i=t_{bkt_{j,1}+1},bkt_{j+1,0}=\max(bkt_{j+1,0},bkt_{j,1}+1)$

$s_i=t_{bkt_{j,0}+1},bkt_{j,0}=bkt_{j,0}+1$

$s_i\not=t_{bkt_{j,0}+1},bkt_{j,1}=\max(bkt_{j,1},bkt_{j,0}),bkt_{j,0}=0$

但是这里有一组 hack 数据：

```
10
bacbcbbccb
5
cbbbc
2

YES
```

思考一下会发现问题出在 $s_i=t_{bkt_{j,1}+1},bkt_{j+1,0}=\max(bkt_{j+1,0},bkt_{j,1}+1)$，这里取 $\max$ 不可取因为对于这两个重复状态它们之间并不是当前 $t$ 中的右端点决定的，而是从当前开始一直匹配到连续的最远的右端点，我们称其为“潜能”，如何求出“潜能”，我们可以上字符串 hash+二分复杂度 $O(xn\log n)$，或者 SAM 预处理，复杂度 $O(xn)$。

新的转移方程为：

$
bkt_{j+1,0}+get(i+1,bkt_{j+1,0}+1)<bkt_{j,1}+1+get(i+1,bkt_{j,1}+1+1),bkt_{j+1,0}=bkt_{j,1}+1
$

部分代码：

```cpp
for(int i=1;i<=n;i++)
    {
        for(int j=x;j>=1;j--)
        {
            if(bkt[j][1])
            {
                if(s[i]==t[bkt[j][1]+1]) 
                {
                    if(j+1<=x) 
                    {
                        if(bkt[j+1][0]+get(i+1,bkt[j+1][0]+1)>bkt[j][1]+1+get(i+1,bkt[j][1]+1+1))
                        	bkt[j+1][0]=bkt[j][1]+1;
                        //判断“潜能”
                        if(bkt[j+1][0]==m)
                        {
                            puts("YES");
                            return 0;
                        }
                    }
                    //不要删掉 bkt[j][1]
                }
            }
            if(bkt[j][0])
            {
                if(s[i]==t[bkt[j][0]+1])
                {
                    bkt[j][0]++;//此状态下能匹配就匹配
                    if(bkt[j][0]==m)
                    {
                        puts("YES");
                        return 0;
                    }
                }
                else
                {//不能匹配就要 0->1
                    bkt[j][1]=max(bkt[j][1],bkt[j][0]);//因为最后都是 1 状态所以取 max 即可
                    bkt[j][0]=0;//强制转换，删除
                }
            }
        }
        if(s[i]==t[1])
        {//相当于将 bkt[0][1]->bkt[1][0]
            if(!bkt[1][0]) bkt[1][0]=1;
            else bkt[1][0]=bkt[1][0]+get(i+1,bkt[1][0]+1)>1+get(i+1,2)?bkt[1][0]:1;
            if(m==1)
            {
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
```

---

## 作者：SoyTony (赞：0)

贪心地想，$s$ 同一段前缀 $[1,i]$，分段匹配到 $t$ 的前缀越大越好，这意味着 $[i+1,n]$ 的部分需要匹配的剩余串更小。

于是可以设计一个同 $s$ 前缀分段匹配 $t$ 前缀的最大值有关的解法。

$k$ 很小，是可以作为状态的，设 $dp_{i,j}$ 表示 $s[1,i]$ 取出 $j$ 段拼接得到 $t$ 的最大前缀长。

对于 $dp_{i,j-1}$，在 $s$ 中匹配到 $i+1$，在 $t$ 中匹配到 $dp_{i,j-1}+1$，想求出这一段可以匹配多少，也就是求最长公共子串，可以用分隔符拼接结合 $\text{SA}$ 求 $\operatorname{lcp}$ 得到。

唯一需要解决的是，对于 $dp_{i,j-1}$，我们的定义不要求 $i$ 是最后一段的结尾，而转移后的 $dp_{i+\operatorname{lcp},j}$，最后一段结尾一定是 $i+\operatorname{lcp}$。

只需要对于每个 $j$，在转移之前对 $i$ 取一个前缀 $\max$。

```cpp
int n,m,len,lim;
char s[maxn<<1],t[maxn];
int dp[maxn][32];
int sa[maxn<<1],rk[maxn<<2],cnt[maxn<<1],oldsa[maxn<<1],oldrk[maxn<<2],tmp[maxn];
inline bool cmp(int x,int y,int l){
    return oldrk[x]==oldrk[y]&&oldrk[x+l]==oldrk[y+l];
}
int height[maxn<<1];
int st[maxn<<1][20];
inline void get_sa(){
    int siz=max(len,127);
    for(int i=1;i<=len;++i) ++cnt[rk[i]=s[i]];
    for(int i=1;i<=siz;++i) cnt[i]+=cnt[i-1];
    for(int i=len;i>=1;--i) sa[cnt[rk[i]]--]=i;
    for(int l=1,k;;l<<=1){
        k=0;
        for(int i=len;i+l>len;--i) oldsa[++k]=i;
        for(int i=1;i<=len;++i) if(sa[i]>l) oldsa[++k]=sa[i]-l;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=len;++i) ++cnt[tmp[i]=rk[oldsa[i]]];
        for(int i=1;i<=siz;++i) cnt[i]+=cnt[i-1];
        for(int i=len;i>=1;--i) sa[cnt[tmp[i]]--]=oldsa[i];
        for(int i=1;i<=len;++i) oldrk[i]=rk[i];
        k=0;
        for(int i=1;i<=len;++i) rk[sa[i]]=cmp(sa[i],sa[i-1],l)?k:++k;
        if(k==len) break;
        siz=k;
    }
    for(int i=1,k=0;i<=len;++i){
        if(k) --k;
        while(s[i+k]==s[sa[rk[i]-1]+k]) ++k;
        height[rk[i]]=k;
        st[rk[i]][0]=height[rk[i]];
    }
    for(int k=1;k<=18;++k){
        for(int i=1;i+(1<<k)-1<=len;++i){
            st[i][k]=min(st[i][k-1],st[i+(1<<k-1)][k-1]);
        }
    }
}
inline int query(int l,int r){
    int rkl=min(rk[l],rk[r])+1,rkr=max(rk[l],rk[r]);
    // printf("%d %d %d %d\n",l,r,rkl,rkr);
    int k=log2(rkr-rkl+1);
    // printf("%d\n",k);
    return min(st[rkl][k],st[rkr-(1<<k)+1][k]);
}
int main(){
    n=read();
    scanf("%s",s+1);
    m=read();
    scanf("%s",t+1);
    s[n+1]='|';
    for(int i=1;i<=m;++i) s[n+1+i]=t[i];
    lim=read();
    len=n+1+m;
    get_sa();
    for(int j=0;j<lim;++j){
        for(int i=1;i<n;++i) dp[i][j]=max(dp[i][j],dp[i-1][j]);
        // for(int i=0;i<=n;++i) printf("(%d %d) %d\n",i,j,dp[i][j]);
        for(int i=0;i<n;++i){
            int lcp=query(i+1,n+1+dp[i][j]+1);
            // printf("i=%d dp=%d lcp=%d\n",i+1,dp[i][j]+1,lcp);
            dp[i+lcp][j+1]=max(dp[i+lcp][j+1],dp[i][j]+lcp);
            if(dp[i+lcp][j+1]==m) return printf("YES\n"),0;
        }
    }
    printf("NO\n");
    return 0;
}
```

---

## 作者：xuyiyang (赞：0)

### [CF822E Liar](https://www.luogu.com.cn/problem/CF822E)
### Solution
考虑 DP。$\\$
首先有个性质，就是如果说可以用相同的 $s$ 前缀选取拼出更长的 $t$ 前缀，那么绝对是拼长的更优，由调整法易证。$\\$
发现 $1 \le n,m \le 10^5$，但是 $k \le 30$，所以考虑 $f_{i,j}$ 表示 $s$ 的前 $i$ 个字符最多选取 $j$ 个子串的最大可以表示 $t$ 的前缀长度。那么转移是简单的。只需要求出两个后缀的 LCP 即可。直接 SA/HASH 带走就好。$\mathcal O(nk + (n + m) \log (n + m))$。
```cpp
const int N = 2e5 + 10;

int n, m, k;
char s[N];
int f[N][1 << 5];
int sa[N], rk[N], ork[N];
int buc[N], id[N], ht[N];
int mi[19][N];

void build() {
	int m = 127, p = 0;
	for (int i = 1; i <= n; i ++ ) buc[rk[i] = s[i]] ++ ;
	for (int i = 1; i <= m; i ++ ) buc[i] += buc[i - 1];
	for (int i = n; i; i -- ) sa[buc[rk[i]] -- ] = i;
	for (int w = 1; ; w <<= 1, m = p, p = 0) {
		for (int i = n - w + 1; i <= n; i ++ ) id[ ++ p] = i;
		for (int i = 1; i <= n; i ++ ) if (sa[i] > w) id[ ++ p] = sa[i] - w;
		memset(buc, 0, (m + 1) << 2); memcpy(ork, rk, (n + 1) << 2), p = 0;
		for (int i = 1; i <= n; i ++ ) buc[rk[i]] ++ ;
		for (int i = 1; i <= m; i ++ ) buc[i] += buc[i - 1];
		for (int i = n; i; i -- ) sa[buc[rk[id[i]]] -- ] = id[i];
		for (int i = 1; i <= n; i ++ )
			rk[sa[i]] = (ork[sa[i - 1]] == ork[sa[i]] && ork[sa[i - 1] + w] == ork[sa[i] + w]) ? p : ++ p;
		if (p == n) break ; 
	}
	for (int i = 1, k = 0; i <= n; i ++ ) {
		if (k) k -- ;
		while (s[i + k] == s[sa[rk[i] - 1] + k]) k ++ ;
		ht[rk[i]] = k;
	}
	for (int i = 1; i <= n; i ++ ) mi[0][i] = ht[i];
}
inline int lcp(int x, int y) {
	if (x == y) return n - x + 1;
	if ((x = rk[x]) > (y = rk[y])) swap(x, y);
	int k = __lg(y - (x ++ ));
	return min(mi[k][x], mi[k][y - (1 << k) + 1]);
}
inline void upd(int &x, int y) { if (x < y) x = y; }

int main() {
	scanf("%d", &n); scanf("%s", s + 1); s[ ++ n] = '#';
	scanf("%d", &m); scanf("%s", s + n + 1); n += m;
	scanf("%d", &k); build();
	
	for (int i = 1; i <= __lg(n); i ++ )
		for (int j = 1; j + (1 << i) - 1 <= n; j ++ )
			mi[i][j] = min(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
	memset(f, -0x3f, sizeof f); f[0][0] = 0;
	for (int i = 0; i < n - m - 1; i ++ ) {
		for (int j = 0; j <= k; j ++ ) {
			int val = f[i][j]; if (val < 0) continue ;
			upd(f[i + 1][j], val); int d = lcp(i + 1, n - m + val + 1);
			upd(f[i + d][j + 1], val + d);
		}
	}
	int res = 0;
	for (int i = 0; i <= k; i ++ ) res = max(res, f[n - m - 1][i]);
	puts(res >= m ? "YES" : "NO"); return 0;
}
```

---

