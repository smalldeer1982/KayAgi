# Puzzle Lover

## 题目描述

Oleg Petrov loves crossword puzzles and every Thursday he buys his favorite magazine with crosswords and other word puzzles. In the last magazine Oleg found a curious puzzle, and the magazine promised a valuable prize for it's solution. We give a formal description of the problem below.

The puzzle field consists of two rows, each row contains $ n $ cells. Each cell contains exactly one small English letter. You also are given a word $ w $ , which consists of $ k $ small English letters. A solution of the puzzle is a sequence of field cells $ c_{1} $ , $ ... $ , $ c_{k} $ , such that:

- For all $ i $ from $ 1 $ to $ k $ the letter written in the cell $ c_{i} $ matches the letter $ w_{i} $ ;
- All the cells in the sequence are pairwise distinct;
- For all $ i $ from $ 1 $ to $ k-1 $ cells $ c_{i} $ and $ c_{i+1} $ have a common side.

Oleg Petrov quickly found a solution for the puzzle. Now he wonders, how many distinct solutions are there for this puzzle. Oleg Petrov doesn't like too large numbers, so calculate the answer modulo $ 10^{9}+7 $ .

Two solutions $ c_{i} $ and $ c'_{i} $ are considered distinct if the sequences of cells do not match in at least one position, that is there is such $ j $ in range from $ 1 $ to $ k $ , such that $ c_{j}≠c'_{j} $ .

## 样例 #1

### 输入

```
code
edoc

code
```

### 输出

```
4
```

## 样例 #2

### 输入

```
aaa
aaa

aa
```

### 输出

```
14
```

# 题解

## 作者：小粉兔 (赞：12)

对于 $|w| \le 2$ 的情况，我们进行特判，这是为了之后写起来分类讨论可以简洁一些。

观察一下最终的行走方式可能会变成啥样：

![](https://cdn.luogu.com.cn/upload/image_hosting/fkecjfml.png)

很多情况下，会变成这个样子。

注意到可以分成三段，左边一个 U 形，中间一个只会向右走的形状，右边又一个 U 形。

啊，为啥说中间是只会向右走？因为我们是这么钦点的，当然也可能是从右边出发往左走，这时只要把 $w$ 反转，再求一次就行。

我们可以处理出，从一个地方分段，会不会产生向左的，长度为某个值的 U 形。

这可以通过预处理 LCP 做到。

同理可以处理出，从一个地方分段，会不会产生向右的，长度为某个值的 U 形。

处理上述两个数组，它们就能够作为第一部分和第三部分。

我们把第二部分接在第一部分后，记 $f(i, j, k)$ 表示，当前第二部分走到了 $(i, j)$，并且匹配了 $w$ 的前 $k$ 个字符，并且不是从同一列走来的方案数。

类似地，记 $g(i, j, k)$ 为必须从同一列走来的方案数。则 $f, g$ 之间可以互相转移，这部分可以 $\mathcal O (n |w|)$ 处理。

然后考虑在 DP 到 $(i, j, k)$ 时，接上第三部分即可，可以直接判断接不接得上。

当然还有一些其他情况没有讨论的，比如三个部分中的某一部分并不存在，甚至是两个部分不存在之类的，仔细讨论一下即可。

注意要不重不漏，特别注意 $w$ 反转后不要统计重复了。

时间复杂度为 $\mathcal O (n |w|)$，[评测链接](https://codeforces.com/contest/613/submission/70898060)。

---

## 作者：xht (赞：11)

> [CF613E Puzzle Lover](https://codeforces.com/contest/613/problem/E)

## 题意

- 给定一个 $2 \times n$ 的矩阵，每个位置上有一个小写字母。
- 有一个长度为 $k$ 的小写字符串 $w$，询问矩阵中有多少条有向路径满足以下条件：
  - 路径上的字母连起来恰好为 $w$。
  - 不多次经过同一个位置。
  - 只能向上下左右四个方向走。
- $n,k \le 2 \times 10^3$，答案对 $10^9+7$ 取模。

## 题解

假设 $n,k$ 同阶。

考虑**头尾不在同一列**的情况，不妨设头在尾的左侧。对于头在尾的右侧的情况，可以将 $w$ 翻转之后在求一遍。

当头在尾的左侧时，我们将路径划分成连续的三个部分：

1. 头所在的列及其左侧的部分；
2. 在头的右侧尾的左侧的部分；
3. 尾所在的列及其右侧的部分。

对于任意一条路径，它的第 $1/3$ 部分都肯定非空，而第 $2$ 部分可能为空。

下面我们依次考虑每一个部分：

1. 这部分要么是一个格子，要么是一个 U 字形，我们可以对于每个格子求出「若第 $1$ 部分在这个格子结束，所有可能的第 $1$ 部分的长度」，借助 Hash 即可做到 $\mathcal O(n^2)$。
2. 这部分不能往左，考虑 dp，设 $f_{i,j,k}$ 表示「若第 $2$ 部分在 $(i,j)$ 结束，上一个格子为 $(i,j-1)$，且第 $1,2$ 部分的长度和为 $k$ 的方案数」，设 $g_{i,j,k}$ 表示「若第 $2$ 部分在 $(i,j)$ 结束，上一个格子其同一列，且第 $1,2$ 部分的长度和为 $k$ 的方案数」，从左到右转移，转移时枚举下一个格子即可，时间复杂度为 $\mathcal O(n^2)$。
3. 与第 $1$ 部分一样，对于每个格子求出「若第 $3$ 部分从这个格子开始，所有可能的第 $3$ 部分的长度」，然后与第 $2$ 部分接上，即第 $2$ 部分的结束的格子的右边一个格子就是第 $3$ 部分开始的格子，同样借助 Hash 可以做到 $\mathcal O(n^2)$。

还剩下**头尾在同一列**的情况，可以发现我们直接在考虑第 $1/3$ 部分时顺便解决掉就好了，注意翻转前后会重复计算一次，最后除掉就好了。

总时间复杂度 $\mathcal O(n^2)$。

## 代码

```cpp
#define Hash pair<modint, modint>
const Hash B = mp(131, 13331);
inline Hash operator + (Hash a, Hash b) { return mp(a.fi + b.fi, a.se + b.se); }
inline Hash operator - (Hash a, Hash b) { return mp(a.fi - b.fi, a.se - b.se); }
inline Hash operator * (Hash a, Hash b) { return mp(a.fi * b.fi, a.se * b.se); }
inline Hash operator + (Hash a, int b) { return mp(a.fi + b, a.se + b); }

const int N = 2e3 + 7;
int n, m;
char s[3][N];
modint f[2][N][N], g[2][N][N], ans, now;
Hash p[N], h[2][3][N];
bool a[2][N][N], b[2][N][N];

inline Hash H(int o, int i, int l, int r) {
	if (!o) return h[o][i][r] - h[o][i][l-1] * p[r-l+1];
	return h[o][i][l] - h[o][i][r+1] * p[r-l+1];
}

inline bool pd(int o, int i, int j, int k) {
	if (!o) {
		if (j < k) return 0;
		if (H(1, i ^ 1, j - k + 1, j) != H(0, 2, 1, k)) return 0;
		if (H(0, i, j - k + 1, j) != H(0, 2, k + 1, 2 * k)) return 0;
		return 1;
	}
	if (j + k - 1 > n) return 0;
	if (H(0, i, j, j + k - 1) != H(0, 2, m - 2 * k + 1, m - k)) return 0;
	if (H(1, i ^ 1, j, j + k - 1) != H(0, 2, m - k + 1, m)) return 0;
	return 1; 
}

inline void solve() {
	for (int i = 1; i <= m; i++) h[0][2][i] = h[0][2][i-1] * B + s[2][i];
	for (int i = 0; i <= 1; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++) {
				f[i][j][k] = g[i][j][k] = 0;
				if (k == 1) {
					g[i][j][k] = a[i][j][k] = s[i][j] == s[2][1];
					b[i][j][k] = s[i][j] == s[2][m];
				} else if (!(k & 1)) {
					g[i][j][k] = a[i][j][k] = pd(0, i, j, k / 2);
					b[i][j][k] = pd(1, i, j, k / 2);
				}
				if (k == m) {
					now += a[i][j][k];
					if (m > 2) now += b[i][j][k];
				}
			}
	dbg(ans.x);
	for (int j = 1; j <= n; j++)
		for (int k = 1; k <= m; k++) {
			for (int i = 0; i <= 1; i++)
				if (s[i][j] == s[2][k])
					f[i][j][k] += f[i][j-1][k-1] + g[i][j-1][k-1];
			for (int i = 0; i <= 1; i++)
				if (s[i][j] == s[2][k])
					g[i][j][k] += f[i^1][j][k-1];
			for (int i = 0; i <= 1; i++)
				if (b[i][j+1][m-k])
					ans += f[i][j][k] + g[i][j][k];
		}
}

int main() {
	rds(s[0], n), rds(s[1], n), rds(s[2], m), p[0] = mp(1, 1);
	for (int i = 1; i <= max(n, m); i++) p[i] = p[i-1] * B;
	for (int i = 0; i <= 1; i++) {
		for (int j = 1; j <= n; j++)
			h[0][i][j] = h[0][i][j-1] * B + s[i][j];
		for (int j = n; j; j--)
			h[1][i][j] = h[1][i][j+1] * B + s[i][j];
	}
	solve(), reverse(s[2] + 1, s[2] + m + 1), solve(), print(ans + now / 2);
	return 0;
}
```

---

## 作者：奇米 (赞：9)

# $\mathrm{CF613E\ Puzzle \ Lover}$ 
* 头铁地去做一道$*3200$的题，没想到还是比较好想~~（看题解~~ 

## **题目意思**
* [题目传送门](https://www.luogu.com.cn/problem/CF613E)

* 就是给你一个$2\times n$的字符矩阵，以及给你个$m$的字符串$t$。问你有多少种方案使得路径上的字符连接起来的字符串为$t$（每次可以往上下左右走，但不能走到同一格）。答案对$1e9+7$取模
* $n,m\leq 2e3$

## $\mathrm{Sol}$
* 前置知识：**字符串哈希+DP**，是不是$PJ$内容啊。
* 我们设这条路径的端点为$s,t$。那么一条$s\to t$的路径样子如下：
![图1-1](https://img-blog.csdnimg.cn/20200512154909727.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dhbmd5aXlhbmcy,size_16,color_FFFFFF,t_70#pic_center)
* **部分一:** 从$s$往左走，再往右绕回来
* **部分二:** 上下往右边移动
* **部分三:** 绕道$t$的右边再绕回来

* 然后我们对于$1,3$部分字符串哈希。这个很简单，即枚举终点用哈希判断是否合法。以及为中间部分做$dp$预处理。不在过多讲。
* 关键是中间反复横跳的过程，设$f_{i,j,k}$表示到$(i,j)$配对到$t$中第$k$个字符，从$f_{i,j-1,k-1}$转移过来。同理$g_{i,j,k}$表示到$(i,j)$配对到$t$中第$k$个字符，从$g_{3-i,j,k-1}$转移过来。（$3-i$即在第一行与第二行反复横跳的简单转换）。
* 那么转移就很简单（不会往回走）。所以$f,g$之间相互更新即可。具体的：
	* $f_{i,j+1,k+1}=\sum g_{i,j,k}[j\leq n,ch_{i,j+1}=t_{k+1}]$
	* $f_{i,j+1,k+1}=\sum f_{i,j,k}[j\leq n,ch_{i,j+1}=t_{k+1}]$
	* $g_{3-i,j,k+1}=\sum f_{i,j,k}[ch_{3-i,j}=t_{k+1}]$
* 对于第三部分我们来统计答案。我们枚举终点算出起点，那么$ans=\sum f_{i,j-1,m-1}+\sum g_{i,j-1,m-1}$（为什么是$j-1$因为第二部分的结束的那一列加一也是$t$所在的那一列）。
* 我们还存在$s,t$在同一列的情况，此时把字符串翻转的答案是重的所以要删掉。同时也要加上这种情况的贡献（即代码中的$gs$，此时不存在第二部分的贡献）

* 于是我们做出了一道$3200$的题。

## $\mathrm{Code}$
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2005;
const int mo=1e9+7;
const int base=131;

char ch[3][N],t[N];
int Hash1[3][N],Hash2[3][N],Hasht[N],bin[N];
int n,m,f[3][N][N],g[3][N][N],ans,gs;

inline int get1(int l,int r,int id)
{
	return Hash1[id][r]-Hash1[id][l-1]*bin[r-l+1];
}

inline int get2(int l,int r,int id)
{
	return Hash2[id][l]-Hash2[id][r+1]*bin[r-l+1];
}

inline void Add(int &x,int y)
{
	x+=y;
	if(x>=mo) x-=mo;
}

inline int merge(int H1,int H2,int len)
{
	return H2+H1*bin[len];
}

inline void dp()
{
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	for ( int i=1;i<=m;i++ ) 
		Hasht[i]=Hasht[i-1]*base+(t[i]-'a'+1);
	for ( int i=1;i<=2;i++ ) 
		for ( int j=1;j<=n;j++ )
			for ( int k=j;k>=1;k-- )
			{
				int len=2*(j-k+1);
				if(len>m) continue;
				int HA=get1(k,j,i);
				int HB=get2(k,j,3-i);
				int HH=Hasht[len];
				if(merge(HB,HA,j-k+1)==HH) 
				{
					if(len==m) gs++;
					else g[i][j][len]=1;
				}
			}
	for ( int i=1;i<=2;i++ ) 
		for ( int j=1;j<=n;j++ )
			if(ch[i][j]==t[1]) g[i][j][1]=1;
	for ( int i=m;i>=1;i-- ) 
		Hasht[i]=Hasht[i+1]*base+(t[i]-'a'+1);
	for ( int k=1;k<m;k++ ) 
		for ( int j=1;j<=n;j++ ) 
			for ( int i=1;i<=2;i++ ) 
			{
				if(g[i][j][k]) 
					if(j<n&&ch[i][j+1]==t[k+1]) 
						Add(f[i][j+1][k+1],g[i][j][k]);
				if(f[i][j][k]) 
				{
					if(j<n&&ch[i][j+1]==t[k+1]) 
						Add(f[i][j+1][k+1],f[i][j][k]);
					if(ch[3-i][j]==t[k+1]) 
						Add(g[3-i][j][k+1],f[i][j][k]);
				}
			}
	for ( int i=1;i<=2;i++ ) 
		for ( int j=1;j<=n;j++ ) 
		{
			if(ch[i][j]==t[m]) 
			{
				if(m==1) Add(ans,1);
				Add(ans,f[i][j-1][m-1]);
				Add(ans,g[i][j-1][m-1]);
			}
			for ( int k=j;k<=n;k++ )
			{
				int len=(k-j+1)*2;
				if(len>m) continue;
				int HA=get1(j,k,3-i);
				int HB=get2(j,k,i);
				int HH=Hasht[m-len+1];
				if(merge(HA,HB,k-j+1)==HH)
				{
					if(len==m&&m!=2) gs++;
					else 
					{
						Add(ans,f[i][j-1][m-len]);
						Add(ans,g[i][j-1][m-len]);
					}
				}
			}
		}
}
					
signed main()
{
	scanf("%s",ch[1]+1);
	scanf("%s",ch[2]+1);
	n=strlen(ch[1]+1);
	scanf("%s",t+1);
	m=strlen(t+1);
	bin[0]=1;
	int Lim=max(n,m);
	for ( int i=1;i<=Lim;i++ ) 
		bin[i]=bin[i-1]*base; 
	for ( int i=1;i<=2;i++ ) 
		for ( int j=1;j<=n;j++ ) 
			Hash1[i][j]=Hash1[i][j-1]*base+(ch[i][j]-'a'+1);
	for ( int i=1;i<=2;i++ ) 
		for ( int j=n;j>=1;j-- ) 
			Hash2[i][j]=Hash2[i][j+1]*base+(ch[i][j]-'a'+1);
	dp();
	reverse(t+1,t+m+1);
	dp();
	Add(ans,gs/2);
	if(m==1) ans/=2;
	printf("%lld\n",ans);
	return 0;
}



```


---

## 作者：justin_cao (赞：6)

可以发现，如果不走回头路的话这个路径问题还是非常容易用dp来解决的，如果走回头路的话不太好记哪些格子被走了哪些没被走。

但是又可以发现走回头路的只可能是在路径的开头以及结尾。

于是考虑把路径拆成三部分来处理：

- 从起点开始往左走然后绕回起点这一列的路径。
- 起点与终点所在列中间的路径
- 从终点所在列向右绕回终点的路径。

注意，现在所有的讨论都是假设起点在终点左的，如果反过来的话只需要把字符串$w$翻转一下再做一遍同样的即可，但是如果终点与起点在同一列，答案会被计算两次，除掉即可。

首先考虑1,3部分，这个非常好处理，枚举终点位置，然后哈希即可判断，第1部分给第2部分的dp赋上初值。

第2部分考虑dp解决。设$f[i][j][k]$和$g[i][j][k]$分别表示从点$(i,j-1)$点还是从$(3-i,j)$点走过来的，因为没有回头路所以不能向左转移，转移非常简单。

1,2部分合并以后，再找到所有的第3部分，拼起来计算答案即可。

复杂度$O(n^2)$。


code：
```cpp
#include<bits/stdc++.h>
#define maxn 3010
#define mod 1000000007
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[3][maxn],t[maxn];
ll has_pre[3][maxn],has_suf[3][maxn],has[maxn],base[maxn];
int n,m;
int f[3][maxn][maxn],g[3][maxn][maxn];
ll get_pre(int l,int r,int id)
{
    return has_pre[id][r]-has_pre[id][l-1]*base[r-l+1];
}
ll get_suf(int l,int r,int id)
{
    return has_suf[id][l]-has_suf[id][r+1]*base[r-l+1];
}
void add(int &x,int y)
{
    x=x+y>=mod?x+y-mod:x+y;
}
ll merge(ll h1,ll h2,int len)
{
    return h2+h1*base[len];
}
int ans,res;
void solve()
{
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    for(int i=1;i<=m;i++)  has[i]=has[i-1]*131+t[i]-'a'+1;
    for(int i=1;i<=2;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int k=j;k>=1;k--)
            { 
                int len=2*(j-k+1);
                if(len>m)  continue;
                ll h1=get_pre(k,j,i),h2=get_suf(k,j,3-i),hx=has[len];
                if(merge(h2,h1,j-k+1)==hx)
                {
                    if(len==m)   res++;
                    else         g[i][j][len]=1; 
                }
            }
        }
    }
    for(int i=1;i<=2;i++)
      for(int j=1;j<=n;j++)
        if(s[i][j]==t[1])  g[i][j][1]=1;
    for(int i=m;i>=1;i--)  has[i]=has[i+1]*131+t[i]-'a'+1;
    for(int k=1;k<m;k++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int i=1;i<=2;i++)
            {
                if(g[i][j][k])
                {
                    if(j<n&&s[i][j+1]==t[k+1])  add(f[i][j+1][k+1],g[i][j][k]);
                }
                if(f[i][j][k])
                {
                    if(j<n&&s[i][j+1]==t[k+1])  add(f[i][j+1][k+1],f[i][j][k]);
                    if(s[3-i][j]==t[k+1])       add(g[3-i][j][k+1],f[i][j][k]);
                }
            }
        }
    }
    for(int i=1;i<=2;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s[i][j]==t[m])
            {
                if(m==1)  add(ans,1);
                add(ans,f[i][j-1][m-1]);
                add(ans,g[i][j-1][m-1]);
            }
            for(int k=j;k<=n;k++)
            {
                int len=2*(k-j+1);
                if(len>m)  continue;
                ll h1=get_pre(j,k,3-i),h2=get_suf(j,k,i),hx=has[m-len+1];
                if(merge(h1,h2,k-j+1)==hx)
                {
                    if(len==m&&m!=2)  res++;
                    else{
                        add(ans,f[i][j-1][m-len]);
                        add(ans,g[i][j-1][m-len]);
                    }
                }
            }
        }
    }
}
int main()
{

    scanf("%s",s[1]+1);scanf("%s",s[2]+1);n=strlen(s[1]+1);
    scanf("%s",t+1);m=strlen(t+1);
    base[0]=1;for(int i=1;i<=max(n,m);i++)  base[i]=base[i-1]*131;
    for(int i=1;i<=2;i++)
      for(int j=1;j<=n;j++)  has_pre[i][j]=has_pre[i][j-1]*131+s[i][j]-'a'+1;
    for(int i=1;i<=2;i++)
      for(int j=n;j>=1;j--)  has_suf[i][j]=has_suf[i][j+1]*131+s[i][j]-'a'+1;
    solve();
    reverse(t+1,t+m+1);
    solve();
    add(ans,res/2);
    if(m==1)  ans/=2;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Varuxn (赞：5)

>[推销](https://www.cnblogs.com/Varuxn/p/15171225.html)

# 解题思路
其实仔细观察我们可以发现路径一定是一个类似于下图的一个左括号之后中间随便反复曲折，然后右边在来一个右括号。

![](https://cdn.luogu.com.cn/upload/image_hosting/uxlmbwv3.png)

然后对于两个括号形状的东西其实是可以利用 Hash 来判等特殊处理的。

对于中间的部分直接 DP ：

$f_{i,j,k,0/1}$ 表示第 $i$ 行，第 $j$ 列，当前扫到了询问路径的第 $k$ 个位置，并且是否可以向上或者下转移。

然后优先处理一下左括号形，这里可以维护两个 Hash 分别存储正反的 Hash 值进行判等。

接下来就 DP 处理中间曲折的部分（ $ch$ 为字符矩阵， $s$ 为目标字符串），对于 $ch_{i,j}=s_k$ 的情况进行转移，转移方程如下：

$$f_{i,j,k,0}=f_{i,j,k,0}+f_{i,j-1,k-1,0}+f_{i,j-1,k-1,1}$$

$$f_{i,j,k,1}=f_{i,j,k,1}+f_{i\;xor\;1,j,k-1,0}$$

注意转移的时候为了防止当前状态对于之后状态造成过多影响，应该把 k 的循环放在最外层。

对于一个路径而言因为是有向的，因此我们把字符串翻转之后再做一边 DP 就好了。
# code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define f() cout<<"Pass"<<endl
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=2e3+10,mod=1e9+7;
const ull base=1331ull;
ull has[N],pre[2][N],suf[2][N],p[N<<1];
int n,m,ans,f[2][N][N<<1][2];
char ch[2][N],s[N<<1];
void Hash()
{
	for(int i=0;i<=1;i++)
		for(int j=1;j<=n;j++)
			pre[i][j]=pre[i][j-1]*base+ch[i][j];
	for(int i=0;i<=1;i++)
		for(int j=n;j>=1;j--)
			suf[i][j]=suf[i][j+1]*base+ch[i][j];
}
ull get_suf(int x,int l,int r){return suf[x][l]-suf[x][r+1]*p[r-l+1];}
ull get_pre(int x,int l,int r){return pre[x][r]-pre[x][l-1]*p[r-l+1];}
ull get_hash(int l,int r){return has[r]-has[l-1]*p[r-l+1];}
void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
void solve()
{
	Hash();
	for(int i=0;i<=1;i++)
		for(int j=1;j<=n;j++)
		{
			f[i][j][1][0]=(ch[i][j]==s[1]);
			for(int k=2;k<=min(j,m/2);k++)
				if((get_hash(1,k)==get_suf(i^1,j-k+1,j))&&(get_hash(k+1,k<<1)==get_pre(i,j-k+1,j)))
					f[i][j][k<<1][1]=1;
		}
	for(int k=1;k<=m;k++)
		for(int i=0;i<=1;i++)
			for(int j=1;j<=n;j++)
				if(ch[i][j]==s[k])
				{
					add(f[i][j][k][0],f[i][j-1][k-1][0]+f[i][j-1][k-1][1]);
		        	add(f[i][j][k][1],f[i^1][j][k-1][0]);
				}
	for(int i=0;i<=1;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<=m;k++)
				if(m-k!=2&&((k&1)==(m&1)))
					add(ans,(f[i][j][k][1]+f[i][j][k][0])*(m==k||(j+(m-k)/2<=n&&get_pre(i,j+1,j+(m-k)/2)==get_hash(k+1,k+(m-k)/2)&&get_suf(i^1,j+1,j+(m-k)/2)==get_hash(k+(m-k)/2+1,m))));
}
void Special_Judge1()
{
	for(int i=0;i<=1;i++)
		for(int j=1;j<=n;j++)
			ans-=(ch[i][j]==s[1]);
}
void Special_Judge2()
{
	for(int i=0;i<=1;i++)
		for(int j=1;j<=n;j++)
			ans-=(ch[i][j]==s[1]&&ch[i^1][j]==s[2]);
}
signed main()
{
	scanf("%s%s%s",ch[0]+1,ch[1]+1,s+1);
	n=strlen(ch[0]+1);	m=strlen(s+1);
	p[0]=1;	for(int i=1;i<=m;i++)	p[i]=p[i-1]*base;
	for(int i=1;i<=m;i++)	has[i]=has[i-1]*base+s[i];
	if(m==1)	Special_Judge1();
	if(m==2)	Special_Judge2();
	solve();
	memset(f,0,sizeof(f));
	for(int i=0;i<=1;i++)	reverse(ch[i]+1,ch[i]+n+1);
	solve();
	printf("%lld",(ans+mod)%mod);
	return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

模拟赛搬的题。这个东西是怎么评上 3200 的。

你先得把询问串长度为 $1$ 和 $2$ 的情况给特判掉，不然会比较麻烦。

如果只允许你向右走，那么很容易设计 DP：设 $dp_{i,j,1/2}$ 表示，你当前在第 $i$ 列，已经在 $w$ 中匹配了 $j$ 个位置，且下一步即将进入 $i+1$ 列的第 $1/2$ 行的方案数。直接做就是 $O(nk)$ 的。

显然我们可以将路径拆分为三段：左边回折，向右挺近，右边回折。如图所示：

![](https://s21.ax1x.com/2025/04/19/pE4d5wR.png)

而你可以直接枚举左右回折的长度，使用字符串哈希判定。为了避免算重，钦定：

1. 不能只有右回折；
2. 左回折和右回折如果存在至少长度为 $2$（即总长度为 $4$。）

复杂度还是 $O(nk)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MOD1=1e9+7,MOD2=1e9+9;
int n,k,ans,pw1[MAXN],pw2[MAXN],dp[MAXN][MAXN][2];
struct H {int v1,v2,len;}pre[MAXN][3],suf[MAXN][3];
H operator -(H A,H B) {return {((A.v1-B.v1*pw1[A.len-B.len])%MOD1+MOD1)%MOD1,((A.v2-B.v2*pw2[A.len-B.len])%MOD2+MOD2)%MOD2,A.len-B.len};}
H operator +(H A,char B) {return {(A.v1*26+B-'a')%MOD1,(A.v2*26+B-'a')%MOD2,A.len+1};}
bool operator ==(H A,H B) {return A.v1==B.v1&&A.v2==B.v2&&A.len==B.len;}
H gain1(int l,int r,int id) {return pre[r][id]-pre[l-1][id];} //正向的哈希值
H gain2(int l,int r,int id) {return suf[l][id]-suf[r+1][id];} //反向的哈希值
string S1,S2,T; 
void solve(int op) {
	n=S1.size(),k=T.size();
	pw1[0]=pw2[0]=1;
	ffor(i,1,2000) pw1[i]=pw1[i-1]*26%MOD1,pw2[i]=pw2[i-1]*26%MOD2;
	ffor(i,1,n) pre[i][0]=pre[i-1][0]+S1[i-1];
	ffor(i,1,n) pre[i][1]=pre[i-1][1]+S2[i-1];
	ffor(i,1,k) pre[i][2]=pre[i-1][2]+T[i-1];
	roff(i,n,1) suf[i][0]=suf[i+1][0]+S1[i-1];
	roff(i,n,1) suf[i][1]=suf[i+1][1]+S2[i-1];
	roff(i,k,1) suf[i][2]=suf[i+1][2]+T[i-1];
	memset(dp,0,sizeof(dp));
	ffor(i,0,n) {
		dp[i][0][0]=(dp[i][0][0]+1)%MOD1;
		dp[i][0][1]=(dp[i][0][1]+1)%MOD1;
		ffor(s,2,i) if(2*s<=k) {
			if(gain2(i-s+1,i,1)==gain1(1,s,2)&&gain1(i-s+1,i,0)==gain1(s+1,s+s,2)) dp[i][s+s][0]=(dp[i][s+s][0]+1)%MOD1;
			if(gain2(i-s+1,i,0)==gain1(1,s,2)&&gain1(i-s+1,i,1)==gain1(s+1,s+s,2)) dp[i][s+s][1]=(dp[i][s+s][1]+1)%MOD1;
		}
		ans=(ans+dp[i][k][0])%MOD1;
		ans=(ans+dp[i][k][1])%MOD1;
		ffor(s,2,n-i) if(2*s<k) {
			if(gain1(i+1,i+s,0)==gain1(k-s-s+1,k-s,2)&&gain2(i+1,i+s,1)==gain1(k-s+1,k,2)) ans=(ans+dp[i][k-2*s][0])%MOD1;
			if(gain1(i+1,i+s,1)==gain1(k-s-s+1,k-s,2)&&gain2(i+1,i+s,0)==gain1(k-s+1,k,2)) ans=(ans+dp[i][k-2*s][1])%MOD1;
		}
		if(i==n) continue ;
		ffor(s,0,k-1) {
			if(s<=k-2&&T[s]==S1[i]&&T[s+1]==S2[i]) dp[i+1][s+2][1]=(dp[i+1][s+2][1]+dp[i][s][0])%MOD1;
			if(s<=k-2&&T[s]==S2[i]&&T[s+1]==S1[i]) dp[i+1][s+2][0]=(dp[i+1][s+2][0]+dp[i][s][1])%MOD1;
			if(T[s]==S1[i]) dp[i+1][s+1][0]=(dp[i+1][s+1][0]+dp[i][s][0])%MOD1;
			if(T[s]==S2[i]) dp[i+1][s+1][1]=(dp[i+1][s+1][1]+dp[i][s][1])%MOD1;
		}
	}
	return ;
}
signed main() {
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S1>>S2>>T,solve(0);
	if(T.size()==1) {
		int ans=0;
		for(auto ch:S1) if(ch==T[0]) ans++;
		for(auto ch:S2) if(ch==T[0]) ans++;
		return cout<<ans,0;	
	}
	if(T.size()==2) {
		int ans=0;
		int n=S1.size();
		ffor(i,1,n) if(S1[i-1]==T[0]&&S2[i-1]==T[1]) ans++;
		ffor(i,1,n) if(S1[i-1]==T[1]&&S2[i-1]==T[0]) ans++;
		ffor(i,1,n-1) if(S1[i-1]==T[0]&&S1[i]==T[1]) ans++;
		ffor(i,1,n-1) if(S2[i-1]==T[0]&&S2[i]==T[1]) ans++;
		ffor(i,1,n-1) if(S1[i-1]==T[1]&&S1[i]==T[0]) ans++;
		ffor(i,1,n-1) if(S2[i-1]==T[1]&&S2[i]==T[0]) ans++;
		return cout<<ans,0;	
	}
	reverse(S1.begin(),S1.end()),reverse(S2.begin(),S2.end()),solve(1);
	cout<<(ans%MOD1+MOD1)%MOD1;
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：1)

这是一个和题解区清一色的分三段不同的算法，区别在于竖着的过程在转移中体现。

以下均看做 $n,k$ 同阶，故只用 $n$ 进行分析复杂度。

一眼看到 $2\times n$ 的网格图只能上下左右走，不难想到[P4740](https://www.luogu.com.cn/problem/P4740)。

类似的思路，我们设 $f_{i,j,0/1,0/1}$ 表示在第 $i$ 列，字符串从第 $j$ 个位置匹配**并且不能回头**的方案数，后面的 $0/1$ 表示在上一行/下一行，是否进行了左右翻转。

这里**不能回头**不好说，但如果做了[P4740](https://www.luogu.com.cn/problem/P4740)肯定能理解，我用下图解释一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/owdrp64h.png?x-oss-process=image/resize,m_lfit,h_150,w_200)

$f_{x,y,0,0}$ 表示的就是从红色箭头处出发，**但不能走到蓝色的线以左的黑色部分**，只能在白色部分进行匹配的方案数。

先考虑一个 naive 的转移，我们考虑枚举在当前行横着匹配了多长，假设匹配了 $k$，钦定就匹配了这么长，下一步必须转弯，即竖着走。

竖着走了过后要不向左，要不向右，即要不反着往回走，要不顺着往后走。

反着走只有一种走法，而且必须恰好匹配。

顺着往后走就可以直接用 $f_{i+k,j+k+1,f1\hat\ 1,f2}$ 转移到 $f_{i,j,f1,f2}$，注意这里 $j+k+1$ 多加了 $1$ 是因为竖着走了一步.

总复杂度 $O(n^3)$，状态 $O(n^2)$，转移 $O(n)$。

这个转移 naive 的地方在于横着能匹配多长可以预处理出来，但是还得考虑竖着能走才能转移，发现竖着能走的条件有两种：

- 横着下一位匹配且竖着下一位与横着下一位相等
- 横着下一位不匹配但竖着下一位匹配

第二种只会有一处，即失配的位置，特殊考虑即可。

第一种可以预处理带权前缀和，权为竖着下一位与横着下一位是否相等。

反着走的转移及其类似，同样可以用特殊处理和带权前缀和处理，然后只取过半的转移。

然后只要知道能匹配多长就能 $O(1)$ 转移了，而能匹配的长度显然可以随便预处理，至此可以处理出 $f$ 数组。

然后就可以直接统计答案了，我们枚举起始位置并向某个方向走 $O(n)$，再枚举第一次横着走了多长 $O(n)$，显然反着走过后和顺着走都可以直接使用 $f$ 数组转移，然后就做完了。

预处理 $O(n^2)$。

处理 $f$ 数组 $O(n^2)$，因为状态数为 $O(n^2)$，转移 $O(1)$。

统计答案 $O(n^2)$，其实用转移 $f$ 数组的技巧可以做到 $O(n)$，但没必要。

[代码](https://www.luogu.com.cn/paste/ifhrymkx)

亿些细节：

- 如果匹配串 $w$ 只有一个字符直接算很容易重，直接特判找这种字符有多少个。
- 矩阵的串与匹配串能匹配多长的预处理其实就是求两串任意两后缀的 LCP。
  
  在 CF 的标解中列举出了处理这个问题的拉胯算法：Hash、suffix structures（后缀结构）
  
  然后推荐了一个更拉胯的算法：扩展 KMP，~~更喜剧的是我没看 CF 标解然后和标解想一块去了~~。
  
  实际上用一个 DP 就可以轻松解决：$f_{i,j}$ 表示 $i,j$ 两后缀的 LCP，判断当前位置然后用 $f_{i+1,j+1}$ 直接转移即可。
  
- 如果第一次横着走了 1 的长度，即直接往上走，会和反转后的贡献算重，所以特判贡献乘 $\frac12$。
- 前缀和优化部分容易挂，同时 $f$ 转移和统计答案有**很多特判**，建议先写个暴力再对着改，也可以参考我的实现。

Upd：重构了部分拉胯的地方，补充了代码。

---

