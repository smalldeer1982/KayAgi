# Rescue Niwen!

## 题目描述

Morning desert sun horizonRise above the sands of time...



Fates Warning, "Exodus"



After crossing the Windswept Wastes, Ori has finally reached the Windtorn Ruins to find the Heart of the Forest! However, the ancient repository containing this priceless Willow light did not want to open!

Ori was taken aback, but the Voice of the Forest explained to him that the cunning Gorleks had decided to add protection to the repository.

The Gorleks were very fond of the "string expansion" operation. They were also very fond of increasing subsequences.

Suppose a string $ s_1s_2s_3 \ldots s_n $ is given. Then its "expansion" is defined as the sequence of strings $ s_1 $ , $ s_1 s_2 $ , ..., $ s_1 s_2 \ldots s_n $ , $ s_2 $ , $ s_2 s_3 $ , ..., $ s_2 s_3 \ldots s_n $ , $ s_3 $ , $ s_3 s_4 $ , ..., $ s_{n-1} s_n $ , $ s_n $ . For example, the "expansion" the string 'abcd' will be the following sequence of strings: 'a', 'ab', 'abc', 'abcd', 'b', 'bc', 'bcd', 'c', 'cd', 'd'.

To open the ancient repository, Ori must find the size of the largest increasing subsequence of the "expansion" of the string $ s $ . Here, strings are compared lexicographically.

Help Ori with this task!

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In first test case the "expansion" of the string is: 'a', 'ac', 'acb', 'acba', 'acbac', 'c', 'cb', 'cba', 'cbac', 'b', 'ba', 'bac', 'a', 'ac', 'c'. The answer can be, for example, 'a', 'ac', 'acb', 'acba', 'acbac', 'b', 'ba', 'bac', 'c'.

## 样例 #1

### 输入

```
7
5
acbac
8
acabacba
12
aaaaaaaaaaaa
10
abacabadac
8
dcbaabcd
3
cba
6
sparky```

### 输出

```
9
17
12
29
14
3
9```

# 题解

## 作者：wtyqwq (赞：17)

- 经典的 LIS 问题，只不过将数字变成了字符串，比较的关键字变成了字符串的字典序。

- 子串的数量是 $O(n^2)$ 级别的，$\sum n\le 10^4$ 要求我们有 $O(n^2)$ 及以下的做法，也就是每个子串最多遍历一次。对所有子串直接做 LIS 肯定爆炸。

- 令 $[l,r]$ 表示字符串 $S$ 的一个字串 $S_l\sim S_{r}$，那么我们发现 $[l,r+1]$ 的字典序一定大于 $[l,r]$。也就是说，假如 $[l,r]$ 能从前面某个状态转移过来，那么 $[l,r+1]$ 也一定可以。

- 令 $f(i)$ 表示以子串 $[i,p](i<p\le n)$ 为 LIS 末尾的答案，$g(i,j)(i>j)$ 为满足 $S_{i+k}$ 与 $S_{j+k}$ 不相等的最小的 $k$。如果 $i + g(i,j) \le n + 1$ 并且 $S_{i+g(i,j)}>S_{j+g(i,j)}$，说明状态 $i$ 可以从状态 $j$ 转移过来，即 $[i,i+g(i,j)\sim n]$ 都可以继承 $j$。状态转移方程为：

  $$f(i)=\max_{1\le j<i}\{n-i+1,f_j+n-i-g(i,j)+1\}$$

- 如何求快速求出 $g(i,j)$ 呢？求 $g(i,j)$ 等价于求 $[i,n]$ 和 $[j,n]$ 的最长公共前缀 LCP 的长度，可以用 DP 求解。如果 $S_i\neq S_j$，显然 $g(i,j)=0$。否则：

  $$g(i,j)=g(i+1,j+1)+1$$
  
- 时间、空间复杂度为 $O(n^2)$。由于多测，不能每次都用 memset 重新清空 $g$ 数组。

```cpp
#include <bits/stdc++.h>
#define N 5005
using namespace std;
int T, n, Ans, f[N][N], dp[N]; // f 数组就是上文的 g 数组，dp 数组就是上文的 f 数组，懒得改了。
char S[N];
bool compare(int x, int y) { // 判断能否由 y 转移到 x。
    if (x + f[x][y] > n + 1) return false;
    return S[x + f[x][y]] > S[y + f[x][y]];
}
int solve(int x, int y) { // 转移
    if (!compare(x, y)) return 0;
    return dp[y] + n - x - f[x][y] + 1;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %s", &n, S + 1);
        for (int i = n - 1; i >= 1; --i) f[n][i] = (S[n] == S[i]);
        for (int i = n - 1; i >= 1; --i)
            for (int j = i - 1; j >= 1; --j)
                f[i][j] = (S[i] == S[j]) ? (f[i + 1][j + 1] + 1) : 0; // DP 求解 LCP
        dp[1] = Ans = n;
        for (int i = 2; i <= n; ++i) {
            dp[i] = n - i + 1;
            for (int j = 1; j < i; ++j)
                dp[i] = max(dp[i], solve(i, j)); // DP 求解 LIS。
            Ans = max(Ans, dp[i]);
        }
        printf("%d\n", Ans);
    }
	return 0;
}
```


---

## 作者：BBD186587 (赞：10)

首先，容易发现，$s[i,j+1]$ 的字典序一定大于 $s[i,j]$，所以，$s[i,j]$ 后面一定能接上 $s[i,j+1]$。

有一个结论，一定存在一种答案最优的选择方案，使得，若 $s[i,j]$ 被选了，则 $s[i,j+1 \sim n]$ 也被选。下面证明这个结论。

假设 $s[i,j \sim k]$ 全都选了，$s[i,k+1]$ 忽然不选了。考虑在什么情况下才会导致这样改变选择。显然，一定存在一对 $l,r$，使得 $l>i$ 且 $s[l,r] > s[i,k]$ 且 $s[l,r] < s[i,k+1]$。

首先，一定有 $s[l,r-1]=s[i,k]$。

若 $s[l,r-1]<s[i,k]$，则显然在 $k$ 更小的时候就可以改变选择了，得到的答案一定不会比现在劣。若 $s[l,r-1]>s[i,k]$，则一定有 $s[l,r]>s[i,k+1]$。不满足定义的条件。

既然如此，选 $s[i,k]$ 就可以视作是选了 $s[l,r-1]$，并从 $s[l,r]$ 开始继续往后选。可以把这个理解为一个“继承”的过程，一定会不断“继承”，直到选上了一个 $s[x,n]$（否则，答案一定不优）。总的来看，就可以认为我们选择了 $s[x,y \sim n]$。

这样一个“继承”的过程就包含了所有**可能会使答案更优的**改变选择的情况，至此，结论证毕。所以，只需考虑所有以 $s[i,n]$ 为结尾的 LIS 即可。

令 $\operatorname{lcp}(i,j)$ 表示满足 $s_{i+k}$ 与 $s_{j+k}$ 不相等的最小的 $k$，令 $f_i$ 表示以 $s[i,n]$ 为结尾的 LIS。

若 $s_{i+\operatorname{lcp}(i,j)}>s_{j+\operatorname{lcp}(i,j)}$，则 $f_i$ 是可以由 $f_j$ 转移过来的，转移为：$f_i=(n-i+1)+\max \limits_{1 \leq j <i}\{f_j-\operatorname{lcp}(i,j)\}$。

$\operatorname{lcp}$ 和 $f$ 都容易在 $O(n^2)$ 的复杂度内得到。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=5010;
int T,n,f[N];
int lcp[N][N];
char s[N];
int MAX(int x,int y)
{
	return x>y?x:y;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		scanf("%s",s+1);
		for(int i=1;i<n;i++)
			lcp[i][n]=(s[i]==s[n]);
		for(int j=n-1;j>=1;j--)
			for(int i=j-1;i>=1;i--)
			{
				if(s[i]==s[j]) lcp[i][j]=lcp[i+1][j+1]+1;
				else lcp[i][j]=0;
			}
		for(int i=1;i<=n;i++) f[i]=n-i+1;
		for(int i=2;i<=n;i++)
			for(int j=1;j<i;j++)
				if(s[i+lcp[j][i]]>s[j+lcp[j][i]])
					f[i]=MAX(f[i],f[j]+n-i+1-lcp[j][i]);
		int ans=0;
		for(int i=1;i<=n;i++) ans=MAX(ans,f[i]);
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：KSToki (赞：5)

# 题目大意
给定一个字符串 $s$，求其依次放置的所有后缀的前缀的字典序最长上升子序列。
# 题目分析
大佬们的做法都好高级啊，蒟蒻用的是纯暴力预处理 dp。

首先这个数据范围是使用 $O(n^2)$ 通过的，我们可以使用暴力求 LIS，这样就可以在其中加入限制。证明一个引理：当一个后缀的某个前缀被取了，那么后面的前缀取完一定不会更劣。由于是从前往后 dp，越靠后的后缀前缀数量越少，如果必须要顶替之前的某一个后缀后面的一段前缀，两个后缀设为 $s1$ 和 $s2$，那么 $s1$ 的一段前缀等于 $s2$ 的一段前缀，否则可以直接完全拼接。然而 $s1$ 剩下的前缀更少，所以一定不优于 $s2$。

有了这个结论，题目就可以转化为一个类似于带权 LIS 的东西，就可以初步设计 dp 了：从前往后枚举后缀，再在之前枚举首字母严格小的后缀，暴力转移。但这时出现一个问题，可能有相等的。仍用之前的设定，即虽然 $s1$ 整个不能拼在 $s2$ 后面，但 $s1$ 后面某一段后缀可能可以拼接，例如 zazb，虽然 z 不可以接在 zazb 后面，但 zb 就可以接在 zazb 后面。

对于这种情况，我们仍暴力处理。由于存在公共前缀，预处理一个数组 $to$，$to[i][j]$ 表示从 $i$，$j$ 开头的公共前缀长度加一（方便处理转移和边界问题），如果不存在则为 $0$。从后往前扫，如果 $s[i]==s[j]$，那么 $to[i][j]=to[i+1][j+1]+1$，否则 $to[i][j]=1$，可以 $O(n^2)$ 解决。

有了这个数组，我们就可以暴力 dp 啦，注意一下边界问题和多测清空即可！
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,f[5005],to[5005][5005];
char s[5001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		scanf("%s",s+1);
		For(i,1,n+1)
		{
			f[i]=0;
			For(j,1,n+1)
				to[i][j]=0;
		}
		Rof(i,n,2)
			Rof(j,i-1,1)
			{
				if(s[i]==s[j]&&to[j+1][i+1])
					to[j][i]=to[j+1][i+1]+1;
				else
					to[j][i]=1;
			}
		For(i,1,n)
		{
			f[i]=n-i+1;
			For(j,1,i-1)
			{
				if(s[j]<s[i])
					chkmax(f[i],f[j]+n-i+1);
				if(s[j]==s[i]&&to[j][i]&&s[j+to[j][i]-1]<s[i+to[j][i]-1])
					chkmax(f[i],f[j]+n-i-to[j][i]+2);
			}
		}
		int ans=0;
		For(i,1,n)
			chkmax(ans,f[i]);
		putint(ans);
	}
	return 0;
}

```

---

## 作者：王熙文 (赞：4)

第一次想出来最近 CF 2500 的题。

## 思路

以下用 $s_{[l,r]}$ 表示 $s_l,s_{l+1},\cdots ,s_r$ 组成的子串。$s<t$ 表示 $s$ 的字典序比 $t$ 小。

首先，根据字典序的定义，显然有 $s_{[l,r]}<s_{[l,r+1]}$。那么如果选 $s_{[l,r]}$，则 $s_{[l,r+1]},s_{[l,r+2]},\cdots , s_{[l,n]}$ 都可以选。

可以猜一个结论：如果选了 $s_{[l,r]}$，则 $s_{[l,r+1]},s_{[l,r+2]},\cdots , s_{[l,n]}$ 一定选。

证明：显然不可能从中间抽出一个子串来，这样显然不优。现在考虑删除 $s_{[l,n]}$ 是否更优。假设在选 $s_{[l,n]}$ 的时候，下一个选的是 $s_{[l2,r2]}$，那不选 $s_{[l2,r2-1]}$ 的原因一定是 $s_{[l2,r2-1]} \le s_{[l,n]}$，而又因为会选 $s_{[l2,r2]}$，所以 $s_{[l2,r2-1]}=s_{[l,n]}$。更进一步，$s_{[l2,r2-2]}=s_{[l,n-1]}$。如果不选 $s_{[1,n]}$，只会在后面添加一个 $s_{[l2,r2-1]}$（因为 $s_{[l2,r2-2]}=s_{[l,n-1]}$ 所以不可能添加 $s_{[l2,r2-2]}$），此时不会增加贡献。所以每删最后一个都不会增加贡献。

设 $dp_i$ 表示选 $i$ 作为左端点的若干子串。枚举上一个选的 $j$，那么 $s_{[j,n]}$ 即为上一个选的。现在需要找到一个最小的 $k$，使得 $s_{[j,n]}<s_{[i,k]}$，然后接上去。

若 $s<t$，则 $s,t$ 的最长公共前缀的下一个位置 $lcp+1$ 必须满足 $s_{lcp+1}<t_{lcp+1}$。对于上面的问题可以用同样的方式做。找到 $i$ 后缀和 $j$ 后缀的最长公共前缀，则若 $i$ 的下一个位置比 $j$ 的大，那个位置（以及后面的）就可以接上了。

现在转化成一个问题：求两个后缀的最长公共前缀。这个问题可以用后缀数组解决（也有别的做法），时间复杂度预处理 $\mathcal O(n \log n)$（或者 $\mathcal O(n \log^2 n)$），查询 $\mathcal O(1)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

string s;

int dp[5010];

int rk[5010],sa[5010];

struct px
{
	int a,b,id;
} p[5010];
bool cmp(px x,px y) { return x.a==y.a?x.b<y.b:x.a<y.a; }

int height[5010];

int lg2[5010],st[20][5010];

int query(int l,int r)
{
	int len=lg2[r-l+1];
	return min(st[len][l],st[len][r-(1<<len)+1]);
}

int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>s;
		s=" "+s;
		for(int i=1; i<=n; ++i) rk[i]=s[i];
		for(int w=1; w<n; w<<=1)
		{
			for(int i=1; i<=n; ++i)
			{
				p[i].a=rk[i],p[i].b=(i+w>n?0:rk[i+w]),p[i].id=i;
			}
			sort(p+1,p+n+1,cmp);
			int now=0;
			bool flag=1;
			for(int i=1; i<=n; ++i)
			{
				if(p[i].a!=p[i-1].a || p[i].b!=p[i-1].b) ++now;
				else flag=0;
				rk[p[i].id]=now;
			}
			if(flag) break;
		}
		lg2[1]=0; for(int i=2; i<=n; ++i) lg2[i]=lg2[i>>1]+1;
		for(int i=1; i<=n; ++i) sa[rk[i]]=i;
		int now=0;
		for(int i=1; i<=n; ++i)
		{
			if(now) --now;
			while(s[i+now]==s[sa[rk[i]-1]+now]) ++now;
			height[rk[i]]=now;
		}
		for(int i=1; i<=n; ++i) st[0][i]=height[i];
		for(int i=1; i<=15; ++i)
		{
			for(int j=1; j<=n-(1<<i)+1; ++j)
			{
				st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
			}
		}
		int ans=0;
		for(int i=1; i<=n; ++i)
		{
			dp[i]=n-i+1;
			for(int j=1; j<i; ++j)
			{
				int wz1=rk[i],wz2=rk[j];
				if(wz1>wz2) swap(wz1,wz2);
				int lcp=query(wz1+1,wz2),k1=i+lcp-1,k2=j+lcp-1;
				if(k1==n) continue;
				if(s[k1+1]>s[k2+1]) dp[i]=max(dp[i],dp[j]+n-(k1+1)+1);
			}
			ans=max(ans,dp[i]);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：云浅知处 (赞：3)

我们注意到这个字符串 $\text{Expansion}$ 出来的序列在字典序上大致是很多个连续递增的段。

具体地，设 $S=\tt{s_1s_2\cdots s_n}$，那么 $\text{Expansion}$ 出来的序列中就是以下 $n$ 段递增的序列：

- $\tt{s_1,s_1s_2,\cdots,s_1s_2\cdots s_n}$
- $\tt{s_2,s_2s_3,\cdots,s_2s_3
\cdots s_n}$
- $\cdots$
- $\tt{s_{n-1},s_{n-1}s_n}$
- $\tt{s_n}$

因此，这个东西的 $\text{LIS}$ 大致就是从这 $n$ 段区间中选出来一些，然后拼在一起。

这样，**如果字符串中的字符互不相同**，类似 $\text{LIS}$ 的 dp，用 $F(i)$ 表示以第 $i$ 个段结尾的最长上升子序列，那么转移方程就是：

$$
F(i)=\max\{F(j)+n-j|\tt{s_j<s_i}\}
$$

但是这样做有个问题：如果字符串中有两个相同的字符，那么我们的比较就失去了正确性。

稍加思考可以发现我们比较的实际上是后缀串，于是考虑令 $a_i$ 为 $S[i...n]$ 这一后缀在所有后缀中的排名，然后把转移方程中的 $\tt{s_j<s_i}$ 改成 $a_j<a_i$。

但是我们发现：当两个首字母相同的段合并时，我们需要舍掉一些。

比如 `abcab`，如果我们选择将 $j=1,i=4$ 这两个 `a` 合并起来，那么我们需要舍掉 `a` 和 `ab` 这两个。

因此我们考虑另一个 dp：令 $G(i,j)$ 为「按上述方式合并时至少需要舍掉的个数」，那么转移方程就是：

$$
G(i,j)=\begin{cases}G(i+1,j+1)+1&,\tt{s_i=s_j}\\0&,\tt{s_i\neq s_j}\end{cases}
$$

这样，我们用 $O(n\log n)$ 的时间利用后缀排序预处理出 $a$，再用 $O(n^2)$ 的时间做两次 $\text{dp}$，就在 $O(n^2)$ 的时间内解决了这个问题。

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#pragma GCC optimize(3)

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int MN=5005;

using namespace std;

int t,n;
int a[MN],dp[MN],f[MN][MN];
int N,M,rak[MN],sa[MN],tax[MN],tp[MN];
string s;

void Qsort() {
    for(int i=0;i<=M;i++)tax[i]=0;
    for(int i=1;i<=N;i++)tax[rak[i]]++;
    for(int i=1;i<=M;i++)tax[i]+=tax[i-1];
    for(int i=N;i>=1;i--)sa[tax[rak[tp[i]]]--]=tp[i];
}

void SuffixSort(){
    M=75;for(int i=1;i<=N;i++)rak[i]=s[i-1]-'0'+1,tp[i]=i;
    Qsort();
    for(int w=1,p=0;p<N;M=p,w<<=1){
        p=0;for(int i=1;i<=w;i++)tp[++p]=N-w+i;
        for(int i=1;i<=N;i++)if(sa[i]>w)tp[++p]=sa[i]-w; 
        Qsort();swap(tp, rak);rak[sa[1]]=p=1;
        for(int i=2;i<=N;i++)rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
    }
}

signed main(void){

    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        memset(sa,0,sizeof(sa));
        memset(rak,0,sizeof(rak));
        memset(tax,0,sizeof(tax));
        memset(tp,0,sizeof(tp));
        
        cin>>n;N=n;
        cin>>s;
        SuffixSort();
        
        for(int i=0;i<n;i++)a[sa[i+1]-1]=i;
        for(int i=n-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(s[i]!=s[j])f[i][j]=0;
                else f[i][j]=f[i+1][j+1]+1;
            }
        }

        dp[0]=n;int ans=n;
        for(int i=1;i<n;i++){
            dp[i]=n-i;
            for(int j=0;j<i;j++){
                if(a[i]>a[j])dp[i]=max(dp[i],dp[j]+n-i-f[i][j]);
            }
            ans=max(ans,dp[i]);
        }

        cout<<ans<<endl;
    }

    return 0;
}
```

---

## 作者：chenzida (赞：1)

仅以此纪念我被诈骗题+题目难度顺序坑了的CF比赛

这一题比D2简单不知道多少倍，甚至比D1还简单，如果我先做的E的话我肯定不至于掉分。。。

这题首先有一个好想好写的暴力，就是把 $O(n^2)$ 个字符串都考虑进去，然后直接最长上升子序列+ $\text{SA}$ 判断两个子串的字典序大小即可。

时间复杂度 $O(n^2\log n)$，很明显过不去。

考虑优化，发现有一个很显然的结论，就是如果我取了以 $i$ 为开头的子串，我一定会把它取完，感性理解一下，就是如果我不弄完让后面的接上去，那这样的话不可能更优，因为如果更优的话那后面的子串也能接到完整的上面去。

然后直接 $dp[i]$ 表示目前考虑到以 $i$ 为开头的子串，并强制取 $i$ 开头的子串，最长上升子序列长度是多少，然后用 $SA$ 计算一下如果从 $j\rightarrow i$ 的话那 $i$ 能取多少个，也就是 $len_i-lcp_{i,j}$。

```.cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=5005;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m;
char s[NR<<1];
int sa[NR<<1],id[NR<<1];
int rk[NR<<1],lark[NR<<1];
int cnt[NR];
int h[NR<<1];
int dp[NR<<1];
int mn[NR][NR];
void work()
{
	memset(s,0,sizeof(s));
	memset(sa,0,sizeof(sa));
	memset(rk,0,sizeof(rk));
	n=read(),scanf("%s",s+1);m=max(n,300);
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)cnt[rk[i]=s[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--)sa[cnt[rk[i]]--]=i;
	for(int w=1;w<n;w<<=1)
	{
		memset(cnt,0,sizeof(cnt));int p=0;
		for(int i=n-w+1;i<=n;i++)id[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>w)id[++p]=sa[i]-w;
		for(int i=1;i<=n;i++)cnt[rk[id[i]]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)sa[cnt[rk[id[i]]]--]=id[i];
		memcpy(lark,rk,sizeof(lark));
		rk[sa[1]]=m=1;
		for(int i=2;i<=n;i++){
			if(lark[sa[i]]==lark[sa[i-1]]&&lark[sa[i]+w]==lark[sa[i-1]+w])rk[sa[i]]=m;
			else rk[sa[i]]=++m;
		}
	}
	memset(h,0,sizeof(h));
	int lcp=0;
	for(int i=1;i<=n;i++)
	{
		if(lcp)lcp--;
		while(s[i+lcp]==s[sa[rk[i]-1]+lcp])lcp++;
		h[rk[i]]=lcp;
	}
	for(int i=1;i<=n;i++)
	{
		mn[i][i]=h[i];
		for(int j=i+1;j<=n;j++)
			mn[i][j]=min(mn[i][j-1],h[j]);
	}
	int ans=0;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++)
	{
		int len=dp[i]=n-i+1;
		for(int j=1;j<i;j++)
		{
			if(rk[i]<rk[j])continue;
			dp[i]=max(dp[i],dp[j]+len-mn[rk[j]+1][rk[i]]);
		}
		ans=max(ans,dp[i]);
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mn[i][j]=0;
}
int main()
{
	int T=read();while(T--)work();
	return 0;
}
/*
1
8
acabacba
*/
```

---

## 作者：meyi (赞：1)

前置知识：[后缀数组及 height 数组](https://oiwiki.org/string/sa/)。

一些定义：原串为 $S[1..n]$，$\text{suf}_i$ 表示 $S[i..n]$，$\text{LCP}(i,j)$ 表示 $\text{suf}_i$ 和 $\text{suf}_j$ 的最长公共前缀的长度。

由于子串 $S[i..j]$ 的实质为 $\text{suf}_i$ 的一个前缀，且在 $j<n$ 的情况下必定能转移到 $S[i..j+1]$，直到 $S[i..j]=\text{suf}_i$，因此只需考虑所有后缀。

令 $dp_i$ 表示 $rank$ 值为 $i$ 的后缀的 LIS的长度，考虑按 $rank$ 值从小到大转移，则有 $dp_i=\max\limits_{j<i \text{且} sa[j]<sa[i]}(dp_j+n-sa[i]+1-\text{LCP}(\text{suf}_i,\text{suf}_j))$。

其中 $n-sa[i]+1$ 表示 $\text{suf}_i$ 的长度，减去重复计算的公共前缀的长度后便为贡献，最终答案为 $\max\limits_{i=1}^ndp_i$。

时间复杂度 $O(n^2)$，瓶颈在于转移。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define DEBUG(k...) fprintf(stderr,k)
typedef long long ll;
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,true:false;}
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,true:false;}
const int maxn=2e4+10;
template<class T>inline void clear(T *arr,int siz){memset(arr,0,sizeof(T)*(siz+1));}
int cnt[maxn],mx,n,rk[maxn],sa[maxn],tmp[maxn];
char s[maxn];
inline void base_sort(){
	clear(cnt,mx);
	for(ri i=1;i<=n;++i)++cnt[rk[i]];
	for(ri i=1;i<=mx;++i)cnt[i]+=cnt[i-1];
	for(ri i=n;i;--i)sa[cnt[rk[tmp[i]]]--]=tmp[i];
}
inline void suffix_sort(){
	mx=0;
	for(ri i=1;i<=n;++i)mx=max(mx,rk[i]=s[i]),tmp[i]=i;
	base_sort();
	for(ri len=1,dif=0;dif<n;len<<=1,mx=dif){
		ri p=0;
		for(ri i=n-len+1;i<=n;++i)tmp[++p]=i;
		for(ri i=1;i<=n;++i)
			if(sa[i]>len)
				tmp[++p]=sa[i]-len;
		base_sort();
		swap(rk,tmp);
		rk[sa[1]]=dif=1;
		for(ri i=2;i<=n;++i){
			if(tmp[sa[i-1]]!=tmp[sa[i]]||tmp[sa[i-1]+len]!=tmp[sa[i]+len])++dif;
			rk[sa[i]]=dif;
		}
	}
}
int ht[maxn];
inline void calc_ht(){
	for(ri i=1,h=0;i<=n;++i){
		if(h)--h;
		ri j=sa[rk[i]-1];
		while(s[i+h]==s[j+h])++h;
		ht[rk[i]]=h;
	}
}
int lg,lg2[maxn],st[(int)log2(maxn)+1][maxn];
inline void build_st(){
	for(ri i=1;i<=n;++i)lg2[i]=lg2[i-1]+((2<<lg2[i-1])==i),st[0][i]=ht[i];
	lg=lg2[n];
	for(ri i=1;i<=lg;++i)
		for(ri j=1;j+(1<<(i-1))<=n;++j)
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
inline int query(int l,int r){
	ri k=lg2[r-l+1];
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
int f[maxn],t_case;
int main(){
	scanf("%d",&t_case);
	while(t_case--){
		scanf("%d%s",&n,s+1);
		suffix_sort();
		calc_ht();
		build_st();
		ri ans=0;
		for(ri i=1;i<=n;++i){
			for(ri j=0;j<i;++j)
				if(sa[j]<sa[i])
					ckmax(f[i],f[j]+n-sa[i]+1-query(j+1,i));
			ckmax(ans,f[i]);
		}
		printf("%d\n",ans);
		clear(f,n);
		clear(s,n);
		clear(rk,n);
		clear(sa,n);
		clear(tmp,n);
	}
	return 0;
}
```

---

## 作者：遮云壑 (赞：0)

# Description

一个字符串，对于它的所有后缀子串的所有前缀，构成了一个很大的字符串序列，求这个序列的最长上升子序列。

[传送门](https://www.luogu.com.cn/problem/CF1562E)

# Solution

产生的字符串的数量级是 $n^2$ 级别的，直接跑 LIS 的 dp 会 T 到起飞，那么这题是否有什么特殊的地方呢。

的确，这题有一个性质：

对于每一个后缀（设长度为 $len$ ），**它产生的 $len$ 个子串一定会把后面的一串全选上**。 比方说串 "aabc" ,有子串 "aabc","abc","bc","c" 那么最后在 LIS 里的一定会是后面的一段，而不会是 "aabc","bc","c" （不连续）或 "aabc","abc" （没有一直选到最后）。

为什么呢，连续选很好理解，然后选到最后是因为你后面的串如果可以接在这个串后面，那么这个串后面再接一点别的东西字典序也一定比后面那个大。

这样就可以转移了，我们设 $f_i$ 为在原串上到了 $i$ 位置的 LIS 。设 $g_{i,j}$ 为 $i$ 位置的后缀串和 $j$ 位置的后缀串的最长公共前缀（意思是这些串都一样，要从 $g_{i,j} + 1$ 开始转移）。

$$f_i=\max_{j\in \left [ 1,i-1 \right ] }{f_i,f_j+n-i+1-g_{i,j}}$$

注： $n-i+1$ 为串长。还有，转移的时候要判一下字典序是不是比前面大，这里不是太难，具体看代码吧。

然后 $g$ 数组的话我们可以 $O(n^2)$ 处理，总的复杂度也是 $O(n^2)$ 的。

# Code

```cpp
#include<bits/stdc++.h>
#define N 5010
using namespace std;
inline void read(int& x)
{
	x=0;int y=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x=x*y;
}
int n,t,g[N][N],f[N];
char s[N];
inline bool chk(int i,int j)
{
	if(i+g[i][j]>n+1)return false;
	if(s[i+g[i][j]]>s[j+g[i][j]])return true;
	else return false;
}
int main(){
	read(t);
	while(t--)
	{
		read(n);
		scanf("%s",s+1);
		for(int i=n-1;i>=1;i--)
			if(s[i]==s[n])g[n][i]=1;
			else g[n][i]=0;
		for(int i=n-1;i>=1;i--)
		{
			for(int j=i-1;j>=1;j--)
			{
				if(s[i]==s[j])g[i][j]=g[i+1][j+1]+1;
				else g[i][j]=0;
			}
		}
		f[1]=n;
		int ans=f[1];
		for(int i=2;i<=n;i++)
		{
			f[i]=n-i+1;
			for(int j=1;j<i;j++)
			{
				if(!chk(i,j))continue;
				f[i]=max(f[i],f[j]+n-i+1-g[i][j]);
			}
			ans=max(ans,f[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

# Conclusion

对于这种经典问题的变形，原算法跑不过去的新问题，我们要善于发现它们的性质，从而找到合适的方法。

---

## 作者：Zxsoul (赞：0)

## 思路

菜狗第一次接触 `E` 题，学到的东西还挺多。官方题解是真的难懂，口胡了两大段为什么要 `lcp` 硬是让谷歌翻译的乱七八糟，搞了一天才懂。



题目意在找出特殊的 LIS ，如何真的按照题目要求的，求出所有字串，然后挨个比较，那么就是 $O(n^4)$ 的时间复杂度。这启发我们去看性质。

不难发现，如果一个以 $l$ 开头的字串，如何一开始就在 LIS 中，那么字串 $[l,l+1..n]$ 也一定会在字串中。

但也存在另外的情况，就是以 $l$ 开头的部分字串已经在前面出现过了，即前面也有一个以 $l$ 开头的字串，但是另一部分的字串比前面那个的字串 $[l，n]$ 还大，此时可以直接拼上去。

那么如何知道什么时候拼上去，即比较两个用着公共前缀的字串的大小。求出两个字串的 LCP，比较下一位即可。

求 LCP 的方式是 DP ，设 $lcp_{i,j}$ 表示后缀 $[i,n]$ 和后缀 $[j,n]$ 的LCP，本来自己是想不到的，还以为要去学后缀排序，然后看了题解才知这么显然：
$$
lcp_{i,j}=lcp_{i+1,j+1}+1 (s[i]=s[j])
$$
然后就是求 LIS ，决策就上前面说的，是否可以产生拼接的情况。

令 $f_{i}$ 表示到 $i$ 开头的字符串前的所有字串产生的 LIS 

转移我们需要判断两个东西，因为代码也许对于一些人比较难懂（~~我~~ ，我做一下解释。

我们大力枚举前面已经求过的 LIS ，就当是 $j$，如果此时的 $i$ 和 $j$ 存在 LCP 考虑拼接问题，如果不能拼接，看将 $j$ 全部除去是否会更优

```c
	if (l[j]-lcp[i][j]>l[i] && s[j+lcp[i][j]]<s[i+lcp[i][j]])
	l[i]=l[j]-lcp[i][j];
		
```

这段说明的是如果 $j$ 去除 LCP 后长度在 $i$ 的决策点中属于最优的，并且 $i$ 可以拼接上来，那么直接转移

转移时减去 LCP 的原因，如下：

```c
l[i]=l[i]+n-i+1;
if (l[i]>ans) ans=l[i];
```

如果可以拼接那么 $n-i+1$ 就会将 LCP 抵消掉，相当于只加了后面的一部分。同理如果没有可以拼接的，证明前面没有公共前缀，那么直接将自己的全部字串记录到贡献里即可。所以这一步可以理解为是为两种情况的同一处理。

```c
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int B=5e3+10;
int lcp[B][B];
int T;
int n;
int l[B];
char s[B];
int read() {int x; scanf("%d",&x); return x;}
void solve()
{
	n=read();
	cin>>s+1;
	for (int i=0;i<=n;i++)
		for (int j=0;j<=n;j++) lcp[i][j]=0;
	for (int i=n;i>=1;i--)
	{	
		l[i]=0;
		for (int j=n;j>=1;j--)
		{
			if (s[i]==s[j]) lcp[i][j]=lcp[i+1][j+1]+1;
		}
	}
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			if (l[j]-lcp[i][j]>l[i] && s[j+lcp[i][j]]<s[i+lcp[i][j]])
			l[i]=l[j]-lcp[i][j];
		}
		l[i]=l[i]+n-i+1;
		if (l[i]>ans) ans=l[i];
	}	
	printf("%d\n",ans);
}
int main()
{
	T=read();
	while (T--) solve(); 
} 
```
注：LCP 表示两个字串的最大公共前缀


---

## 作者：Cry_For_theMoon (赞：0)

[传送门](https://codeforces.com/problemset/problem/1562/E)

还没有出现优于平方的做法，所以 lcp 部分听说被二分+hash搞过去了。

手玩以后发现如果选了 $s_{l...r}$，那么 $s_{l...r+1},s_{l...r+2}$ 一直到 $s_{l...n}$ 都会被选择。因为假设后面又选择了一个串 $t$ 大于 $s_{l...r}$，那么 $t$ 也一定大于 $s_{l...r+1},s_{l...r+2},...,s_{l...n}$ 这些串。

所以直接设 $dp_i$ 是最后选的是 $i$ 后缀的 LIS 长度。考虑 $dp_i$ 从 $dp_j$ 转移而来（$j<i$），那么为了让 $i$ 后缀这里选择的串尽可能多且大于 $s_{j...n}$，我们只需要求出 $i$ 后缀和 $j$ 后缀的 $lcp$ 值 $len$。如果 $i+len \le n$ 且 $s_{i+len}>s_{j+len}$，我们就把 $s_{i,i+len}$ 一直到 $s_{i,n}$ 这 $(n-i+1)-len$ 个子串全部选择。

时间复杂度 $O(n^2)$。注意这里的 $lcp$ 可以求出 $height$ 以后 $O(n^2)$ 预处理，不用麻烦地再去写一个 RMQ。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=5010;
int T,n,ans,f[MAXN];
char s[MAXN];
struct SA{
	int sa[MAXN],rk[MAXN*2],oldrk[MAXN*2],cnt[MAXN],tmp[MAXN];
	int lcp[MAXN][MAXN],height[MAXN];
	void build(char* s,int n){
		rep(i,0,n*2+5){rk[i]=oldrk[i]=0;}
		int m=max(n,150);
		rep(i,0,m)cnt[i]=0;
		rep(i,1,n)rk[i]=s[i]; 
		rep(i,1,n)cnt[rk[i]]++;
		rep(i,1,m)cnt[i]+=cnt[i-1];
		per(i,n,1)sa[cnt[rk[i]]--]=i;
		for(int w=1;w<n;w<<=1){
			int p=0;
			rep(i,n-w+1,n)tmp[++p]=i;
			rep(i,1,n)if(sa[i]>w)tmp[++p]=sa[i]-w;
			rep(i,0,m)cnt[i]=0;
			rep(i,1,n)cnt[rk[tmp[i]]]++;
			rep(i,1,m)cnt[i]+=cnt[i-1];
			per(i,n,1)sa[cnt[rk[tmp[i]]]--]=tmp[i];
			rep(i,1,n)oldrk[i]=rk[i];
			rk[sa[1]]=1;
			rep(i,2,n){
				rk[sa[i]]=rk[sa[i-1]];
				if(oldrk[sa[i]] != oldrk[sa[i-1]] || oldrk[sa[i]+w] != oldrk[sa[i-1]+w])rk[sa[i]]++;
			}
		}
		int j=0;
		rep(i,1,n){
			if(j)j--;
			while(s[i+j]==s[sa[rk[i]-1]+j])j++; 
			height[rk[i]]=j;
		}
		rep(i,1,n){
			lcp[i][i]=(n-sa[i]+1);
			rep(j,i+1,n){
				lcp[i][j]=min(lcp[i][j-1],height[j]);
			}
		}
	}
	int query(int L,int R){
		L=rk[L];R=rk[R];
		if(L>R)swap(L,R);
		return lcp[L][R];
	}
}sa;
void solve(){
	scanf("%d%s",&n,s+1);
	sa.build(s,n);
	ans=0;
	rep(i,1,n){
		f[i]=n-i+1;
		rep(j,1,i-1){
			//f[i]由f[j]转移而来
			int len=sa.query(i,j);
			if(i+len-1==n || s[i+len]<s[j+len])continue; //不能转移
			f[i]=max(f[i],f[j]+(n-i+1-len)); 
		}
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--){
		solve();
	}
	
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### 题目分析

先设原串中以 $x$ 位置为开头的所有子串的集合为 $sw(x)$，$s(x,y)$ 表示原串中从 $x$ 到 $y$ 的子串。

由于同一个 $x$ 对应的 $sw(x)$ 在最后的 LIS 里出现的一定是连续的，

而且一定有一种最优方案使得若 $sw(x)$ 中存在一个串在 LIS 中出现过，则 $s(x,n)$ 也出现过，（证明先鸽着，有需要的催我）

所以设 `dp[i]` 表示以 $s(i,n)$ 为结尾的最长上升子序列的长度。

线性枚举 `dp[i]` 是从哪个 `dp[j]`$(j<i)$ 推过来。

### Details

先 init 出 `lcp[i][j]`，即 $i$ 和 $j$ 的最长公共后缀的长度，便于决策。

### ACcode

复杂度 $O(Tn^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T> inline void ckmx(T &a,T b){ if(a<b)a=b; }
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(register int i=j;i<=k;i++)
#define Rof(i,j,k) for(register int i=j;i>=k;i--)
#define N 5050

int T,n;
string s;
int ans;
int lcp[N][N];//i和j的最长公共后缀的长度 
int dp[N];//以[i,n]为结尾的最长上升子序列的长度 
bool bigger(int x,int y){//以x为开头的后缀 是否比 以y为开头的后缀 大（x>y） 
	if(x+lcp[x][y]==n)return false;
	else return s[x+lcp[x][y]]>s[y+lcp[x][y]];
}
int contri(int x,int y){//j更新i 
	if(bigger(x,y)) return dp[y]+n-x-lcp[x][y];
	else return 0;
}
signed main(){
	IOS;
	cin>>T;
	while(T--){
		cin>>n;
		cin>>s;
		For(i,0,n)For(j,0,n)lcp[i][j]=0;//归零 
		Rof(i,n-1,0)
			Rof(j,n-1,0)
				if(i==j)
					lcp[i][j]=n-i;//之后都相等 
				else if(s[i]==s[j])
					lcp[i][j]=lcp[i+1][j+1]+1;//递推 
		ans=n;
		dp[0]=n;
		For(i,1,n-1){
			dp[i]=n-i;
			For(j,0,i-1)
				ckmx(dp[i],contri(i,j));
			ckmx(ans,dp[i]);
		}
		cout<<ans<<endl;
	} 
    return 0;
}

```

---

