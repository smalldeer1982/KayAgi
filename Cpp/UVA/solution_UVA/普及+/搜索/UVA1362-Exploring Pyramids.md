# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 样例 #1

### 输入

```
ABABABA
AB```

### 输出

```
5
0```

# 题解

## 作者：Kevin_Zhen (赞：8)

题目链接 [$\mathfrak{UVA1362}$](https://www.luogu.com.cn/problem/UVA1362)。  
[可能更好的阅读体验](https://www.luogu.com.cn/blog/150cm/solution-uva1362)。

### 题目大意
给出一棵树的 dfs 序，求可能的构成方案数。

### 为什么区间 dp？
在对一棵树进行深度优先遍历时，一定最先访问其根结点，递归遍历其子树，最后回溯回根结点。所以一棵树的 dfs 序左右两端颜色相同，并且是连续的一段区间。  
一棵树的构成方案数可以由其子树的构成方案数推出，对应到 dfs 序上，一个大区间的方案数可以由小区间转移得到。故思考方向应偏向区间 dp。

### 定义状态
- $F_{i,j}$：区间 $[i,j]$ 可能的构成方案数。

所求答案为 $F_{1,n}$（字符串从下标 $1$ 处开始读入）。

### 状态转移
一棵树有几个儿子是不确定的。如果枚举划分点的个数和位置进行转移，复杂度很高。  
注意到**结点的子树之间有序**，所以对于两种方案，只要有一处对应位置上的子树构造不同，这两种方案就是不同的。所以不妨只考虑第 $1$ 棵子树和其他子树的构造方案，进行转移。

对于一个区间，如果左右端点颜色不同，则无法构成一棵树，方案数为 $0$。  
对于只有一棵子树的情况，$F_{l,r}=F_{l+1,r-1}$。  
枚举**第一次回到根结点的位置** $k$。这个位置的范围是 $[l+2,r-2]$，因为相邻的两个颜色不可能属于同一结点。此时一棵树被分成了两部分：第一棵子树（对应区间 $[l+1,k-1]$）和除第一棵子树以外的部分（对应区间 $[k,r]$）。这棵树的构成方案数就是两部分的乘积，即 $F_{l,r}=\sum\limits_{k=l+2}^{r-2} F_{l+1,k-1}\times F_{k,r}$  
**使用 int 的同学记得在乘法运算前强制类型转换，不然会爆**。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int maxn = 310;
const int Mod = 1e9;

char s[maxn]; int n, f[maxn][maxn];

int main() {
	while (~scanf("%s", s + 1)) {
		memset(f, 0, sizeof(f));
		n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) f[i][i] = 1;
		for (int len = 2; len <= n; ++len) {
			for (int r = len; r <= n; ++r) {
				int l = r - len + 1;
				if (s[l] != s[r]) continue;
				f[l][r] = f[l + 1][r - 1];
				for (int k = l + 2; k <= r - 2; ++k) {
					if (s[l] == s[k]) f[l][r] = (f[l][r] + (ll)f[l + 1][k - 1] * f[k][r] % Mod) % Mod; 
				}
			}
		}
		printf("%d\n", f[1][n]);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

### Preface

反复强调一件事：多组数据。（本人因为这个卡了3发提交）

### 题意：

虽然题面很丑，但是可以概括为给你一个欧拉序，求满足这个欧拉序的树的数量。

### 思路:

以下是几个性质:

- 如果一棵树有一个合法 $\texttt{dfs}$ 序，那么这个 $\texttt{dfs}$ 序头尾必定是相同的。

- 一个树被分成若干个子树，答案为子树答案之积。

有了这两个性质，定义状态 $f_{i,j}$ 为欧拉序 $i \sim j$ 段的答案，进行区间 $\texttt{DP}$ 即可。

状态转移方程:

$f_{i,j} + \sum_{k=i+2}^{j} f_{i+1,k-1}\times f_{k,j} \to f_{i.j}$

边界：

如果满足 $s_i \neq s_j$，这样的欧拉序构不成树，$0 \to f_{i,j}$。

### [Code](https://www.luogu.com.cn/paste/xjm6quaa)

---

## 作者：CommandSR (赞：2)

## 题意简述

一棵有根有序树，每个节点被涂有某种颜色。机器人对这棵树进行深度优先遍历，每次进入或离开节点时都会记录该节点的颜色，最终生成一个颜色序列。

给定一个颜色序列，我们需要计算有多少种不同的有根有序树结构能够产生这个序列。

## 基本思路

树的结构可以从其子树的结构转移而来，类比到大区间可以由小区间转移而来，故可以考虑区间 DP。

不妨令 $f_{i, j}$ 为子序列 $[i, j]$ 对应的方案数。

则 $s_i = s_j$ 时为合法状态，有 $f_{i, j} = f_{i, j} + f_{i, k} \times f_{k+1, j-1}$ 其中保证 $s_k = s_i$。

可以理解为我们将子序列 $[i, j]$ 划分为两颗子树，两颗子树的方案数相乘就是当前方案数，对于每一种子树划分方案的方案数相加就是总方案数。

初始状态 $f_{i, i} = 1$。

最终答案在 $f_{1, n}$。

## AC Code

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
using namespace std;
const int N = 310, mod = 1e9;
string s;
ll n, f[N][N];
int main() {
	cin >> s; s = " " + s; n = s.length()-1;
	F(i, 1, n) f[i][i] = 1;
	F(len, 2, n) {
		for (int i = 1, j = len; j <= n; ++i, ++j) {
			if (s[i] != s[j]) continue ;
			F(k, i+2, j-2) if (s[k] == s[i]) f[i][j] = (f[i][j] + f[i][k] % mod * f[k+1][j-1] % mod) % mod;
			f[i][j] = (f[i][j] + f[i+1][j-1]) % mod;
		}
	}
	cout << f[1][n] % mod << '\n';
	return 0;
}
```

---

## 作者：伟大的王夫子 (赞：2)

本题是一个区间 DP。思路十分巧妙。

我们假设原序列为 $a$，令 $f_{l,r}$ 表示子序列 $[l,r]$ 所对应的树的方案有多少种。因为是计数 DP，为了保证不重不漏，我们只需要枚举他的第一棵子树就可以了。对于子序列 $[l, r]$ 所对应的子树，$a_l$ 为根，我们可以通过枚举根的位置 $k$ 进行转移，那么剩下的子树就对应了序列 $[k,r]$，$a_k$ 为根。

于是 $f_{l,r} = \sum_{k=l+2}^r f_{l+1,k-1} \times f_{k,r}(a_l = a_k)$。

边界：$f_{i,i}=1$。

注意，我们枚举的这棵子树不能为空，所以 $k$ 从 $l+2$ 开始枚举。否则，会在 $k = r$ 时重复计算。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
typedef long long LL;
char a[305];
LL f[305][305];
const LL P = 1e9;
LL dfs(int l, int r) {
	if (~f[l][r]) return f[l][r];
	if (l == r) return f[l][r] = 1;
	f[l][r] = 0;
	for (int k = l + 1; k <= r; ++k)
		if (a[l] == a[k])
			(f[l][r] += 1ll * dfs(l + 1, k - 1) * dfs(k, r)) %= P;
	return f[l][r];
}
int main() {
	while (~scanf("%s", a + 1)) {
		n = strlen(a + 1);
		memset(f, -1, sizeof f);
		printf("%lld\n", dfs(1, n));
	}
}
```

---

## 作者：luckydrawbox (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/UVA1362)

## 题意

给定一棵树的 $\text{dfs}$ 序 $s$，求这棵树的形态数量，答案对 $10^9$ 取模。

**有多组数据**。

## 分析

我们知道，一棵树的 $\text{dfs}$ 序长这样：

``根|子树 1|根|子树 2|根|子树 3|根|……|根|子树 n|根``

因为可能会有相同的颜色，所以与根颜色相同的节点也可能为子树。

一棵树的形态个数显然由它子树的形态个数得到，于是我们设 $dp_{i,j}$ 为以区间 $[i,j]$ 为树的形态的个数。

显然，若 $i=j$，$dp_{i,j}\Leftarrow1$；若 $s_i\ne s_j$，$dp_{i,j}\Leftarrow0$。

接下来考虑 $s_i=s_j$ 的情况:

- 只有一颗子树。

此时树的形态为 ``根|子树 1|根``，这时树的形态数量就是子树 $1$ 的形态数量个数，即 $dp_{i,j}\Leftarrow dp_{i+1,j-1}$。

- 有多棵子树。

此时树的形态为 ``根|子树 1|根|其他子树|根``，我们发现其中 ``子树 1`` 和 ``根|其他子树|根`` 是两个子问题，于是我们枚举子树 $1$ 的根端点 $k-1$，满足 $s_i=s_k$，根据乘法原理及加法原理，$dp_{i,j}\Leftarrow\sum\limits_{i+2\le k\le j-2\land s_i=s_k}dp_{i+1,k-1}\times dp_{k,j}$。

答案为 $dp_{1,n}$。

像这样，一个大区间的答案从小区间得到，我们就想到了[区间 dp](https://oi-wiki.org/dp/interval/)。

然后就是板子了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
    long long x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=310;
const ll mod=1e9;
string s;
int n;
ll dp[N][N];
int main(){
	while(cin>>s){
		n=s.size();
		s=" "+s;//字符串下标从0开始，前面加一个空格使下标从1开始
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)
			dp[i][i]=1;
		for(int l=2;l<=n;l++){
			for(int i=1,j;i+l-1<=n;i++){
				j=i+l-1;
				if(s[i]!=s[j])
					continue;
				dp[i][j]=dp[i+1][j-1];
				for(int k=i+2;k<=j-2;k++)
					if(s[i]==s[k])
						dp[i][j]=(dp[i][j]+dp[i+1][k-1]*dp[k][j]%mod)%mod;
			}
		}
		write(dp[1][n]);
		putchar('\n');
	}
    return 0;
}
```


---

## 作者：Itst (赞：2)

### 最近热衷于写DP与写DP题解的我233
### 首先这题需要明白的是：在树的DFS序中，一个子树的DFS序会对应其中的一段区间！
### 区间！！
## 区间！！！
# 区间DP！！！！
### 于是奇怪的想法诞生，设f( i , j )为i到j区间对应多少种可能的树形结构
### 然后？转移方程？
### 显然不能用石子合并类方法（划分点有可能很多，时间复杂度会爆炸），而且很有可能从多种不同状态转移到同一状态从而出现重复解
### 所以不妨枚举其中的一个划分点，也就是枚举第一个子树的大小
### 那么这样的话，不管其它子树怎么弄，只要第一个子树大小不相同，两种方案一定就不相同了，也就避免了重复解的情况，而且将时间复杂度降为O（ L ^ 3 ）（其中L为字符串长度），不会卡时
### 还有不要忘记只有一个子树的情况！
### 直接上代码qwq
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9;
char s[301];
long long maxN[301][301];
int main(){
	while(scanf("%s" , s) != EOF){
		memset(maxN , 0 , sizeof(maxN));
		int l = strlen(s);
		for(int i = 0 ; i < l ; i++)	maxN[i][i] = 1;
		for(int i = l - 2 ; i >= 0 ; i--)
			for(int j = i + 1 ; j < l ; j++)
				if(s[i] == s[j]){
					maxN[i][j] = (maxN[i][j] + maxN[i + 1][j - 1]) % MOD;
                    //只有一个子树的情况，子树的遍历序就是i+i至j-1的一段区间
					for(int k = i + 2 ; k < j - 1 ; k++)
                    //枚举第一个子树的位置
						if(s[i] == s[k])
							maxN[i][j] = (maxN[i][j] + maxN[i + 1][k - 1] * maxN[k][j]) % MOD;
                            //乘法原理了解一下：所有可行情况=第一个子树的排列种数*其它子树的排列种数
				}
		cout << maxN[0][l - 1] << endl;
	}
	return 0;
}
```

---

## 作者：andyli (赞：2)


## 题目大意

给出一棵多叉树，每个结点的任意两个子结点都有左右之分。从根结点开始，每次尽量往左走，走不通了就回溯，把遇到的字母顺次记录下来，可以得到一个序列。如图所示的$5$个图的序列均为`ABABABA`。给定一个序列，问有多少棵树与之对应。
![](https://i.loli.net/2019/01/25/5c4b0b522d6bc.png)

## 问题求解

设输入序列为$S$，$d(i,j)$为子序列$S_i$，$S_{i+1}$，…，$S_j$对应的树的个数，则边界条件是$d(i,i)=1$，且$S_i\not= S_j$时$d(i,j)=0$（因为起点和终点应是同一点）。在其他情况下，设第一个分支在$S_k$时回到树根（必须有$S_i=S_k$），则这个分支对应的序列是$S_{i+1}$，…，$S_{k-1}$，方案数为$d(i+1,k-1)$；其他分支对应的访问序列为$S_k$，…，$S_j$，方案数为$d(k,j)$。这样，在非边界情况，递推关系为$d(i,j)=\text{sum}\{d(i+1,k-1)\times d(k,j)|i+2\le k\le j, S_i=S_k=S_j\}$。

## 参考代码

```cpp
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 305, MOD = 1000000000;
typedef long long LL;

char S[maxn];
int d[maxn][maxn];

int dp(int i, int j)
{
	if (i == j)
		return 1;
	if (S[i] != S[j])
		return 0;
	int &ans = d[i][j];
	if (ans >= 0)
		return ans;
	ans = 0;
	for (int k = i + 2; k <= j; k++)
		if (S[i] == S[k])
			ans = (ans + (LL)dp(i + 1, k - 1) * (LL)dp(k, j)) % MOD;
	return ans;
}

int main()
{
	while (~scanf("%s", S))
	{
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(0, strlen(S) - 1));
	}
	return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

考虑**欧拉序**的性质，**一个子树在欧拉序上一定形成一段头尾都相同的区间**。

于是考虑区间 DP，定义 $dp_{l,r}$ 表示区间 $[l,r]$ 对应的子树个数。接下来考虑如何在一个区间后拼接一个区间。观察可知，一个子树被拍在欧拉序上后，会被与根节点相同颜色的节点分为若干段，则一个区间 $[c,d]$ 能接到另一个区间 $[a,b]$ 后面的条件就是 $b=c$ 且 $S_a=S_b=S_d$，转移即可。

但是这样拼接子树会导致同一颗子树被不同的分割方式统计了多次，于是我们考虑**强制钦定从后面加进来的区间只能是原区间根节点的一颗子树**，而非多颗。也就是做转移的时候转移 $dp_{c+1,d-1}$ 而非 $dp_{c,d}$。这样计数即可保证不重不漏。

枚举分割点后，判断并利用乘法原理转移即可。时间复杂度 $O(n^3)$。

注意到一个合法的欧拉序长度只能是奇数，可以在枚举长度的时候跳过偶数，常数能减少一半。

普通递推版本：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=305;
const ll mod=1000000000;
char s[N];
int n;
ll dp[N][N];
void solve()
{
    n=strlen(s+1);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++)dp[i][i]=1;
    for(int len=3;len<=n;len+=2)
    {
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            for(int k=i;k<j;k++)
            {
                if(s[i]==s[k]&&s[k]==s[j])
                    dp[i][j]=(dp[i][j]+dp[i][k]*dp[k+1][j-1]%mod)%mod;
            }
        }
    }
    cout<<dp[1][n]<<'\n';  
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin>>s+1)solve();
    return 0;
}
```

记忆化搜索版本：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=305;
const ll mod=1000000000;
char s[N];
int n;
ll dp[N][N];
ll dfs(int l,int r)
{
    if(dp[l][r]>=0)return dp[l][r];
    if(r<l||s[l]!=s[r]||(r-l+1)%2==0)return 0;
    if(l==r)return 1;
    dp[l][r]=0;
    for(int i=l;i<r;i++)
    {
        if(s[l]==s[i])
            dp[l][r]=(dp[l][r]+dfs(l,i)*dfs(i+1,r-1)%mod)%mod;
    }
    return dp[l][r];
}
void solve()
{
    n=strlen(s+1);
    memset(dp,-1,sizeof(dp));
    cout<<dfs(1,n)<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin>>s+1)solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 思路：

显然的，若不是叶子结点都应该至少遍历两次。

于是两个相同访问之间就可能是一颗子树。

更加具体的，如同 $s_l,\dots,s_k ,\dots,s_r$，使得 $s_l=s_k$，那么就可以认为 $s[l,k]$ 是 $s[l,r]$ 的一颗子树，设区间 $s[l,r]$ 的结构数量为 $f_{l,r}$，那么根据乘法原理，当把 $s[l,k]$ 看作 $s[l,r]$ 的第一棵子树时，其方案数为 $f_{l+1,k-1} \times f_{k,r}$。

为什么是 $k+1$ 和 $l-1$，是因为那是因为两个子树不能一样，不能重复。

之后区间 DP 即可。

## AC Code


```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,f[305][305];
const int mod=1e9;
char s[305];
signed main() {
	ios::sync_with_stdio(false);
	while(cin>>s+1){
		memset(f,0,sizeof(f));
		n=strlen(s+1);
		for(int i=1; i<=n; i++)f[i][i]=1;
		for(int i=2; i<=n; i++)
			for(int l=1; l<=n+1-i; l++) {
				int r=l+i-1;
				for(int k=l; k<=r; k++) 
					if(s[l]==s[k]) {
						f[l][r]+=f[l+1][k-1]*f[k][r];
						f[l][r]%=mod;
					}
			}
		cout<<f[1][n]<<"\n";
	}
	return 0;
}
```

### 之后更改：

由校友 gaomingyang101011 发现 $f_{l,k}$ 误写为 $f_{1,k}$。

---

## 作者：_ChongYun_ (赞：1)

### Solution

考虑区间 dp。很容易想到定义 $dp_{l,r}$ 表示区间 $[l,r]$ 对应的满足条件的子树的方案数。

一般区间 dp 的套路无非就是枚举一个断点 $k$，使得这个大状态由两个小状态转移过来，我们现在需要考虑的就是如何划分每一个状态。

状态对应的子树也有若干个子树。不妨只考虑第一棵子树是什么样的，这样我们将整个状态划分成了第一棵子树和其他子树。所以考虑递归地把每一个 $dp_{l,r}$ 计算。具体地，每次依然枚举一个断点 $k$，分割第一棵子树和其他子树，再分别递归计算第一棵子树和其他子树的答案。

下面假设每一个 $dp_{l,r}$ 已经算出，那么：

$$dp_{l,r}=\sum^{r}_{k=l+2}dp_{l+1,k-1} \times dp_{k,r}$$

### Code

使用的是记忆化搜索。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9;
string str;
int n,dp[305][305];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int dfs(int l,int r){
	if(l>r) return 0;
	if(l==r) return 1;
	if(str[l]!=str[r]) return 0;
	if(dp[l][r]!=-1) return dp[l][r];
	dp[l][r] = 0;
	for(int i=l+2;i<=r;i++){
		if(str[l]==str[i]) dp[l][r]=(dp[l][r]+dfs(l+1,i-1)*dfs(i,r))%mod;
	}
	return dp[l][r];
}
signed main(){
	while(cin>>str){
		n=str.size();
		str=" "+str;
		for(int i=1;i<=n;i++){
		    for(int j=1;j<=n;j++){
		        dp[i][j]=-1;
		    }
		}
		printf("%lld\n",dfs(1,n));
	}
	return 0;
}
```

---

## 作者：zbzbzzb (赞：0)

可以发现，序列一定是 `rt A rt B ...... rt C rt` 这样的，`A`，`B`，`C` 是根节点的子树，

于是，发现一棵树可以被他的子树所转移而来，使用区间 DP。

设 $dp_{i,j}$ 代表可能组成区间 $\left[i,j\right]$ 这个序列的结构数量，于是，再枚举一个中点 $k$，转移方程便为 $dp_{i,j}=dp_{i,j}+dp_{i,k} \times dp_{k+1,j-1}$。

然后记得清空。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9;
string s;
int n;
long long dp[310][310];
int main(){
	while(cin>>s){
		memset(dp,0,sizeof dp);
		n=s.size();
		s=" "+s;
		for(int i=1;i<=n;i++){
			dp[i][i]=1;
		}for(int len=2;len<=n;len++){
			for(int l=1;l+len-1<=n;l++){
				int r=l+len-1;
				if(s[l]==s[r]){
					for(int k=l;k<=r-1;k++){
    					if(s[k]==s[l]){
    						dp[l][r]=(dp[l][r]+dp[l][k]*dp[k+1][r-1])%mod;
    					}
    				}
				}
			}
		}printf("%lld\n",dp[1][n]%mod);
	}return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

双倍经验：[P10956](https://www.luogu.com.cn/problem/P10956)。

## Solution UVA1362

### Problem

给定一棵树的 dfs 遍历顺序，求其可能对应的树的个数。

### Idea

不难发现每一次我们到达一个点，都会立即开始遍历它的子树，经过若干次遍历再回到这个点，然后进行遍历它的下一个子树（如果没有子树了就返回父亲）。

因此，一个树的 dfs 遍历序列一定形如 $\{x,y,\cdots,y,\cdots,y,x,\cdots,x\}$。

还不理解？看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zr5rrmjb.png)

我们从点 $1$ 出发，设遍历序列为 $a$。

先遍历到 $2$，$a=\{1,2\}$。

然后遍历到 $5$，$a=\{1,2,5\}$。

然后回到 $2$，$a=\{1,2,5,2\}$。

然后依次遍历 $6$、$7$、$8$，最后回到 $1$，则 $a=\{1,2,5,2,6,2,7,2,8,2,1\}$。

然后遍历子树 $3$ 和 $4$，则 $a=\{1,2,5,2,6,2,7,2,8,2,1,3,9,3,10,13,10,14,10,15,10,3,11,3,12,3,1,4,1\}$。

因此，我们发现一个数 $x$ 一定会在遍历序列中输出 $son_x+1$ 次（其中 $son_x$ 为 $x$ 的儿子的个数）。

我们发现每个子树都是相互独立的，即一个子树的统计结果不会影响没有包含关系的另一个子树的统计结果。

这个信息显然是可合并的，所以可以区间 $dp$。

设 $dp_{i,j}$ 为 $[i,j]$ 区间的方案数。

则显然有：$dp_{i,j}=\sum_{}^{}(dp_{i,k}\times dp_{k+1,j-1})$，其中 $i\le k<j$ 且 $s_i=s_k=s_j$。

解释一下就是枚举断点，使得 $[i+1,k-1]$ 和 $[k+1,j-1]$ 变为两个不同子树。

答案就是 $dp_{1,n}$。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=305,mod=1000000000;
string s;
int n;
long long dp[N][N];
int main(){
	while(cin>>s){
		n=s.length();
		s=' '+s;
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)dp[i][i]=1ll;
		for(int len=2;len<=n;len++){
			for(int i=1,j=len;j<=n;j++,i++){
				if(s[i]!=s[j])continue;
				for(int k=i;k<j;k++){
					if(s[k]!=s[i])continue;
					dp[i][j]=dp[i][j]+dp[i][k]*dp[k+1][j-1]%mod;
					dp[i][j]%=mod;
				}
			}
		} 
		printf("%lld\n",dp[1][n]);	
	}	
	return 0;
}
```

---

## 作者：sad_lin (赞：0)

题意是对一个字符串颜色序列的 dfs 序求树的可能数，所以考虑区间dp，设状态 $dp[i][j]$ 为区间 $i$ 到 $j$ 树的状态数。

在转移的过程中如果 $s_i=s_j$ 时代表这可能为同一个根节点组成的树，所以才可以开始枚举中间点，当中间点与根节点的颜色相同时，我们就可以将分为两个子树，然后根据乘法原理，将每个区间状态数相乘就是这么划分的方案数，再将所有的状态数相加就得到了大区间的状态数，转移方程为 $dp[i][j]=(dp[i][j]+dp[i][k]\times dp[k+1][j-1])$，$k+1$ 和 $j-1$ 是为了得到两个不同子树乘积。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1e9;
const int N=1e5;
char s[N];
int n;
ll dp[1005][1005];
int main(){#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1e9;
const int N=1e5;
char s[N];
int n;
ll dp[1005][1005];
int main(){
    ios::sync_with_stdio(false);
	while(~scanf("%s",s+1)){//多组测试点
		memset(dp,0,sizeof dp);//多测清空
		n=strlen(s+1);
		for(int i=1;i<=n;i++){
			dp[i][i]=1;
		}
		for(int len=2;len<=n;len++){
			
			for(int i=1;i<=n-len+1;i++){
				int j=i+len-1;
				if(s[i]==s[j]){
					for(int k=i;k<=j-1;k++){
						if(s[k]==s[i]){
							dp[i][j]+=(dp[i][k]*dp[k+1][j-1])%mod;
							dp[i][j]%=mod;
						}
					}
				}
			}
		}
		
		cout<<dp[1][n]<<"\n";
	}
    return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定一棵树的 dfs 遍历路径 $s$，问这棵树的排列有多少种。

**解题思路**

对于一个非叶子节点，在扫完它的一棵子树后就会回到这个节点，所以 $s$ 就相当于是根节点 + 子树一 + 根节点 + 子树二 + $\cdots$ + 根节点。

将整棵树转换为字符串（线性），就可以想到区间 dp，而又根据 $s$ 的构成，所以我们只需要枚举每个满足左右两端点相同的区间即可。

为了代码简洁，所以使用了记忆化搜索。

初始：$f_{i,j}=-1$

答案：$f_{1,n}$

边界：

1. $l > r$：$0$。
2. $l = r$：$1$。
3. $s_l\neq s_r$：$0$。
4. $f_{l,r}\neq -1$：$f_{l,r}$

转移方程：

$$
f_{l,r}=\sum_{i=l+2}^r[s_l=s_i]\times f_{l+1,i-1}\times f_{i,r}
$$

注意一下，模数是 $10^9$ 而不是 $10^9+7$（我先前就错了）。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 305, Mod = 1e9;
string s;
int n, f[N][N];
inline int dfs(int l, int r) {
  if(l > r) { return 0; }
  if(l == r) { return 1; }
  if(s[l] != s[r]) { return 0; }
  if(f[l][r] != -1) { return f[l][r]; }
  f[l][r] = 0;
  for(int i = l + 2; i <= r; i++) {
    if(s[l] != s[i]) { continue; }
    f[l][r] = (f[l][r] + dfs(l + 1, i - 1) * dfs(i, r) % Mod) % Mod;
  }
  return f[l][r];
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  while(cin >> s) {
    n = s.size();
    s = " " + s;
    memset(f, -1, sizeof(f));
    cout << dfs(1, n) << '\n';
  }
  return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

根据题意，金字塔房间的结构是一棵树，每个房间有一个颜色，要求根据访问颜色序列来计算可能的树结构数量。

很明显，除了叶节点的所有节点在遍历时都应该被访问至少两次。两次访问之间的序列就为节点的子树（可能多于一个）。

更具体的，如果有颜色序列 $s_l,\cdots,s_k,\cdots,s_r$ 使得 $s_l=s_k$，那么 $s[l,k]$ 可以作为 $s[l,r]$ 的一颗子树。

设区间 $s[l,r]$ 的结构数量为 $f_{l,r}$，那么根据乘法原理，当把 $k$ 看作 $s[l,r]$ 的第一棵子树时，其方案数为 $f_{l+1,k-1} \times f_{k,r}$

由此可得区间 DP 算法：枚举区间 $[l,r]$，如果有 $k \in [l,r]$ 使得 $s_l=s_k$，那么令 $f[l,r]$ 加上 $f_{l+1,k-1} \times f_{k,r}$。

代码如下，注意开 `long long`：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=305,P=1e9;
int n; char s[N];
long long f[N][N];

int main()
{
	while(scanf("%s",s+1)!=EOF)
	{
		memset(f,0,sizeof(f));
		n=strlen(s+1);
		for(int i=1;i<=n;i++) f[i][i]=1;
		for(int len=2;len<=n;len++)
			for(int l=1;l+len-1<=n;l++)
			{
				int r=l+len-1;
				for(int k=l;k<=r;k++)
					if(s[l]==s[k])
					{
						f[l][r]+=f[l+1][k-1]*f[k][r];
						f[l][r]%=P;
					}
			}
		printf("%lld\n",f[1][n]);
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1362)

# 前置知识

[欧拉序](https://oi-wiki.org/graph/lca/#定义_1) | [区间 DP](https://oi-wiki.org/dp/interval/) | [乘法原理](https://oi-wiki.org/math/combinatorics/combination/#乘法原理)

# 解法

颜色序列本质上是欧拉序，故考虑区间 DP。

设 $f_{l,r}$ 表示 $[l,r]$ 对应的二叉树的个数，状态转移方程为 $f_{l,r}=\begin{cases} 1 & l=r \\ [s_{l}=s_{r}] \times \sum\limits_{i=l+2}^{r}[s_{l}=s_{i}] \times f_{l+1,i-1} \times f_{i,r} & l \ne r\end{cases}$。

最终，有 $f_{1,n}$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=1000000000;
ll f[400][400];
char s[400];
int main()
{
	ll n,len,l,r,i;
	while(cin>>(s+1))
	{
		n=strlen(s+1);
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++)
		{
			f[i][i]=1;
		}
		for(len=1;len<=n;len++)
		{
			for(l=1,r=l+len-1;r<=n;l++,r++)
			{
				if(s[l]==s[r])
				{
					for(i=l+2;i<=r;i++)
					{
						f[l][r]=(f[l][r]+(s[l]==s[i])*f[l+1][i-1]*f[i][r]%p)%p;
					}
				}
			}
		}
		cout<<f[1][n]<<endl;
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

题意：给出一棵树的 dfs 序，求这棵树的形态的可能性。

首先，我们定义 $dp_{l,r,0/1}$，表示左端点 $l$，右端点 $r$，$0$ 表示 $[l,r]$ 这个区间可以回到起点；$1$ 表示这个区间可以不能回到起点。

对于 $dp_{l,r,0}$，当且仅当 $s_l=s_r$，这样最后才能回到起点，那么我们就要搜索中间的那些子节点，即 $dp_{l+1,r-1,1}$。

对于 $dp_{l,r,1}$，枚举中间的分割点 $k$，如果从 $i$ 可以回到 $k$，那么 $s_i=s_k$，剩下的部分可以不回到 $i$，运用乘法原理，此时 $dp_{l,r,1}=dp_{l,k,0}\times dp_{k,r,1}$。

典型区间 dp，时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9;
string s;
int dp[305][305][2],len; 
signed main(){
	while(cin>>s){
		len=s.size();
		s=' '+s;
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=len;++i)
			dp[i][i][0]=dp[i][i][1]=1;
		for(int i=3;i<=len;i+=2)
			for(int l=1,r=l+i-1;r<=len;++l,++r){
				if(s[l]==s[r])
					dp[l][r][0]=dp[l+1][r-1][1];
				for(int k=l;k<=r;k+=2)
					if(s[l]==s[k])
						dp[l][r][1]=(dp[l][r][1]+dp[l][k][0]*dp[k][r][1])%mod;
			}
		printf("%lld\n",dp[1][len][1]);
	}
	return 0;
}
```

---

## 作者：Mobius127 (赞：0)

[题传](https://www.luogu.com.cn/problem/UVA1362)

似乎是一个经典的问题。

>问多少颗树的 $\operatorname{Euler}$ 序（欧拉环游序）是给定的字符串 $s$。

$\operatorname{Euler}$ 序本身的性质是跟 $\operatorname{dfs}$ 序差不多的（但两者不能混为一谈）。若记 $st_i$ $ed_i$ 分别为第 $i$ 个节点上的字符（也就是说，不同节点的字符可能一样）最早出现和最晚出现位置，那么由定义可知，$[st_i, ed_i]$ 中的节点都是 $i$ 的子树节点，子树对应区间，不难想到区间 DP。

设 $f_{l, r}$ 为处理 $[l, r]$ 这段字符能形成以 $l=st,r=ed$ 的不同的“子树”个数，为了不出现 [P7914](https://www.luogu.com.cn/problem/P7914) 那样的算重惨案，我们枚举第一颗被遍历完的**次根子树**（就是根的父亲为 $l$ 的子树）的 $ed$ 的后一位 $k$（因为要第一个遍历完，所以 $st=l+1$），显然 $s_l=s_k$，因为遍历完了要回到根，根据乘法原理，就有：

$$f_{l, r}=\sum_{k=l+2}^{r} f_{l+1, k-1} \times f_{k, r} [s_l=s_r=s_k]$$

复杂度 $O(Tn^3)$。

这么简单的题还要代码？

---

## 作者：zzyeeeh (赞：0)

**这道题看似是一个搜索顺序问题，可以构建结点个数不相同的树来进行遍历，但是时空复杂度和代码难度过大**

我们可以这样想：

**①从构建树的思想出发，最终的树都是由一个或多个小的树加上新的结点之后构建成的一棵较大的树**

**②两棵不同的树加上一个公共结点就可以合并为一棵树**

**③对于两棵合并的树，它们遍历的方案数就是两棵小树方案数的乘积（乘法原理）**

**④对于N个结点树遍历方案数，就是有不同结构的N个结点的树的方案数之和（加法原理）**

**在处理遍历顺序上，我们注意到：**

**①对于每个完整的树，其遍历顺序的起点和终点的结点符号都是相同的，即**
```cpp
ABA
ABABA
```
**是对一棵树完整的遍历顺序，而**
```cpp
AB 
ABAB
```
**不是合法的遍历顺序**

**②来到这道题的解决上，将一棵树分为两个子树，总的方案数就是两个子树方案数的乘积，再改变第一棵子树的形状，计算积后将多个积相加，就能做到不重不漏地得到所有方案数**

这时，我们便得出了这道题的最终解法：

### 区间DP

将**树的大小**看作区间，区间分割点就是**两棵子树的公共结点位置**，这里采用**递归**的方法来求出最终的遍历方案数

**状态转移方程为:**
```
dp[l][r]=
① 0  ( a[l]!=a[r] ) 
② dp[l][r] + solve(l+1,k-1) * solve(k,r)  ( l+2<=k<=r ) 
```
**其中solve为递归函数**

**具体代码及注释如下：**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000000
using namespace std;

char a[310];
long long dp[310][310];//注意要开long long
long long ans;
string tree;
int N;

void getdata()
{
	cin>>tree;
	int len=tree.length();
	for(int i=1;i<=len;i++) a[i]=tree[i-1];
    //将string复制到char数组中，避免数组下标从零开始成为坑点
	N=len;
}

long long solve(int l,int r)
{
	if(a[l]!=a[r])return 0;//转移方程的第一种情况
	if(l>r) return 0;//边界情况
	if(l==r)return 1;//边界情况
	if(dp[l][r]!=-1)return dp[l][r];//记忆化
	dp[l][r]=0;//更新并初始化，标记为搜索过
	for(int k=l+2;k<=r;k++)//这里特别注意k的范围
	{
		if(a[l]==a[k])//注意第二种情况的成立条件
		dp[l][r]= (   dp[l][r]%MOD  +  ( ((long long)solve(l+1,k-1) )%MOD* ( (long long)solve(k,r) %MOD) )%MOD  )%MOD;
//鉴于数组会很大，所以每个数都要加long long 并取模
//并且注意不能写成dp+=的形式，同样会溢出
	}
	return dp[l][r];
}

int main()
{
	getdata();
	memset(dp,-1,sizeof(dp));//记忆化初始化
	cout<<solve(1,N);
	return 0;
} 
```


---

