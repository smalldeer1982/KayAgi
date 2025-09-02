# Text Editor

## 题目描述

You wanted to write a text $ t $ consisting of $ m $ lowercase Latin letters. But instead, you have written a text $ s $ consisting of $ n $ lowercase Latin letters, and now you want to fix it by obtaining the text $ t $ from the text $ s $ .

Initially, the cursor of your text editor is at the end of the text $ s $ (after its last character). In one move, you can do one of the following actions:

- press the "left" button, so the cursor is moved to the left by one position (or does nothing if it is pointing at the beginning of the text, i. e. before its first character);
- press the "right" button, so the cursor is moved to the right by one position (or does nothing if it is pointing at the end of the text, i. e. after its last character);
- press the "home" button, so the cursor is moved to the beginning of the text (before the first character of the text);
- press the "end" button, so the cursor is moved to the end of the text (after the last character of the text);
- press the "backspace" button, so the character before the cursor is removed from the text (if there is no such character, nothing happens).

Your task is to calculate the minimum number of moves required to obtain the text $ t $ from the text $ s $ using the given set of actions, or determine it is impossible to obtain the text $ t $ from the text $ s $ .

You have to answer $ T $ independent test cases.

## 样例 #1

### 输入

```
6
9 4
aaaaaaaaa
aaaa
7 3
abacaba
aaa
5 4
aabcd
abcd
4 2
abba
bb
6 4
baraka
baka
8 7
question
problem```

### 输出

```
5
6
3
4
4
-1```

# 题解

## 作者：EuphoricStar (赞：16)

## 思路

手玩几组数据可知：

- 若不回到开头删字符，则操作次数为 $n - pl$，其中 $pl$ 表示 $s$ 和 $t$ 的 $\mathrm{LCP}$ 长度。

- 若需要回到开头删字符，则最优解一定是光标先从右往左移动一段，若有不同的字符则按一次 `backspace`；然后按 `home` 回到开头，光标从左往右移动一段，若有不同的字符则需要先按 `right` 再按 `backspace`。中间有一段是跟 $t$ 中相同长度的一段匹配的，因此不用动。

可以把 $s$ 分成前、中、后三部分，然后 dp。设 $f_{i,j,0/1/2}$ 表示当前处理到 $s$ 的第 $i$ 个字符，跟 $t$ 中前 $j$ 个字符匹配，当前光标在前/中/后部分的最少移动次数。

转移：

- 任意时刻，若光标在前/后部分，都可以删除当前字符。在前部分删除一个字符的代价是 $2$（因为要先按 `right` 再按 `backspace`），在后部分删除一个字符的代价是 $1$。因此：

$$f_{i,j,0} \gets \min(f_{i,j,0},f_{i-1,j,0}+2)$$

$$f_{i,j,2} \gets \min(f_{i,j,2},f_{i-1,j,2}+1)$$

注意这里没有 $f_{i,j,1}$ 的转移，是因为中部分的字符不能修改。

- 当 $s_i = t_j$，若光标在前/后部分，则直接按 `right`/`left`，匹配长度增加 $1$。若光标在中部分，则直接沿用之前的值。因此：

$$f_{i,j,0} \gets \min(f_{i,j,0},f_{i-1,j-1,0}+1)$$

$$f_{i,j,1} \gets \min(f_{i,j,1},f_{i-1,j-1,1})$$

$$f_{i,j,2} \gets \min(f_{i,j,2},f_{i-1,j-1,2}+1)$$

- 任意时刻，光标都可以从前部分转入中部分/后部分，或从中部分转入后部分。因此：

$$f_{i,j,1} \gets \min(f_{i,j,1},f_{i,j,0})$$

$$f_{i,j,2} \gets \min(f_{i,j,2},f_{i,j,1},f_{i,j,0})$$

注意最后还要加上按 `home` 的操作，即操作次数为 $f_{n,m,2}+1$。

由于此题卡空间，所以要用滚动数组优化。

## 代码

[code](https://codeforces.com/contest/1701/submission/164386002)

---

## 作者：hcywoi (赞：8)

#### 题目大意
给我们一个字符串 $s$ 和字符串 $t$，我们可以给字符串 $s$ 做以下操作：
- 把光标向左移
- 把光标向右移
- 删除一个字符
- 把光标移到开头
- 把光标移到结尾

问：把 $s$ 变成 $t$，最少的操作次数。

#### 解题思路
我们会发现最优解中一定可以先操作后面，再移动到开头操作前面。

然后我们可以前面做一遍 Dp，在从后面做一遍 Dp。

$f_{i,j}$ 表示光标到了第 $i$ 个位置，且操作后的 $s$ 与 $t_{1 \sim j}$ 匹配。

- 当 $s_i = s_j$，说明可以不用删除，$f_{i, j} = f_{i-1,j-1}+1$
- 如果删除，$f_{i,j}=f_{i-1,j}+2$

设 $s_{1 \sim i}$ 和 $t_{1 \sim j}$ 匹配的最小值为 $f_{i, j}^{'}$。

如果 $s_i = s_j$，且不用删除是小于删除的，那么 $f_{i, j}^{'} = f_{i-1,j-1}^{'}$。否则 $f_{i,j}^{'}=f_{i-1,j}+2$

后面做一遍 Dp 与前面类似，就不在赘述。

最后在把所有方案求一个最小值。

#### Ac Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5010;
const short INF = N;

int n, m;
short f[N][N], g[N][N];
short fp[N][N], gp[N][N];
char s[N], t[N];

int main()
{
	int T;
	scanf("%d", &T);
	while (T -- )
	{
		scanf("%d%d", &n, &m);
		scanf("%s%s", s + 1, t + 1);
		for (int i = 0; i <= n + 1; i ++ )
			for (int j = 0; j <= m + 1; j ++ )
				f[i][j] = g[i][j] = fp[i][j] = gp[i][j] = INF; // 初始化

		f[0][0] = fp[0][0] = 0;
		for (int i = 1; i <= n; i ++ ) // 从前面做 Dp
			for (int j = 0; j <= m; j ++ )
			{
				f[i][j] = fp[i][j] = f[i - 1][j] + 2;
				if (j && s[i] == t[j])
				{
					if (f[i][j] >= f[i - 1][j - 1] + 1)
					{
						f[i][j] = f[i - 1][j - 1] + 1;
						fp[i][j] = fp[i - 1][j - 1];
					}
				}
			}

		g[n + 1][m + 1] = gp[n + 1][m + 1] = 0;
		for (int i = n; i; i -- ) // 从后面做 Dp
			for (int j = m + 1; j; j -- )
			{
				g[i][j] = gp[i][j] = g[i + 1][j] + 1;
				if (j <= m && s[i] == t[j])
				{
					if (g[i][j] >= g[i + 1][j + 1] + 1)
					{
						g[i][j] = g[i + 1][j + 1] + 1;
						gp[i][j] = gp[i + 1][j + 1];
					}
				}
			}
		short res = INF;
		for (int i = 0; i <= n; i ++ )
			for (int j = 0; j <= m; j ++ )
				res = min(res, short(fp[i][j] + gp[i + 1][j + 1] + (fp[i][j] > 0 ? 1 : 0)));
// 求最小值，如果从前面是选 fp[i,j]，那么从后面就是 gp[i + 1, j + 1]
		if (res >= INF) res = -1;
		printf("%d\n", res);
	}

	return 0;
}
```

---

## 作者：MortisM (赞：5)

[传送门](https://codeforces.com/contest/1701/problem/E)
## 题目大意
有一个长度为 $n$ 的字符串 $s$，一个长度为 $m$ 的字符串 $t$。初始时光标在最右边，你可以：
+ 把光标往左移
+ 把光标往右移
+ 删除一个字符
+ 将光标移到最左边
+ 将光标移到最右边

求最少要多少步操作将 $s$ 变成 $t$。
## 思路
考虑什么样的操作是最优的，一定是在最后删掉一些再到开头删掉一些。

形式化地，将 $s$ 分为前缀、中缀、后缀，其中中缀能完全匹配上 $t$ 中的一段。

设 $dp(i,j,k)$ 表示 $s$ 的前 $i$ 个字符能匹配上 $t$ 的前 $j$ 个字符，$k$ 表示当前光标在哪一段。（ $k=0,1,2$ 分别表示在前缀、中缀、后缀）

若 $k=0$，则有：$dp(i,j)=dp(i-1,j)+2$。当 $s_i=t_j$ 时，$dp(i,j)=dp(i-1,j-1)+1$。

若 $k=1$，则当 $s_i=t_j$ 时，$dp(i,j)=dp(i-1,j-1)$。

若 $k=2$，则有：$dp(i,j)=dp(i-1,j)+1$。当 $s_i=t_j$ 时，$dp(i,j)=dp(i-1,j-1)+1$。

答案为 $\min(dp(n,m,0),dp(n,m,1),dp(n,m,2))$。

时间复杂度 $O(n^2)$。

[Code](https://www.luogu.com.cn/paste/xjfm42rm)

---

## 作者：Hovery (赞：3)

首先贪心地想，一定是先删后面的，再删前面的。

考虑把前面后面分开处理。

对于删前面的，设 $f_{i,j}$ 表示 $T$ 的前 $i$ 个由 $S$ 的前 $j$ 个得来的最少操作次数。

那么就有

$$\begin{cases}
  f_{i,j}=f_{i-1,j-1} & S_j=T_i\\
  f_{i,j}=f_{i,j-1} + j- vis_{i,j-1}+1 & S_j\not =  T_i \\
\end{cases}$$

$vis_{i,j}$ 表示处理完 $T$ 的前 $i$ 个由 $S$ 的前 $j$ 个得来时的光标的位置。

还需要记录一个 $g_{i,j}$ 表示 $T$ 的前 $i$ 个能否通过 $S$ 的前 $j$ 个操作后形成。

倒着做同理，最后合并答案即可。

若你的空间很大，不妨开 $\texttt{short}$。


```cpp

#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
using namespace std;

bool mem1;

short _1[5002][5002], _2[5002][5002], __1[5002][5002], __2[5002][5002], vis[5002][5002];
int n, m;
string s1, s2;
short ans;

void solve()
{
	cin >> n >> m;
	cin >> s1 >> s2;
	s1 = " " + s1;
	s2 = " " + s2;
	swap(s1, s2);
	swap(n, m);
	s1 = s1 + " ";
	for (int i = 0;i <= n + 1;i++)
	for (int j = 0;j <= m + 1;j++)
	{
		_1[i][j] = __1[i][j] = _2[i][j] = __2[i][j] = vis[i][j] = 0;
	}
	__1[0][0] = 1;
	vis[0][0] = 0;
	for (int i = 0;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		if (s1[i] == s2[j])
		{
			_1[i][j] = _1[i - 1][j - 1];
			__1[i][j] = __1[i - 1][j - 1] & 1;
			vis[i][j] = vis[i - 1][j - 1];
		}
		else {
			_1[i][j] = _1[i][j - 1] + j - vis[i][j - 1] + 1;
			vis[i][j] = j; 
			__1[i][j] = __1[i][j - 1];
		}
	}
    for (int i = 0;i <= n + 1;i++)
	for (int j = 0;j <= m + 1;j++)
	{
		vis[i][j] = 0;
	}
	__2[n + 1][m + 1] = 1;
	vis[n + 1][m + 1] = m + 1;
	for (int i = n + 1; i ;i--)
	{
		for (int j = m; j ;j--)
		if (s1[i] == s2[j])
		{
			_2[i][j] = _2[i + 1][j + 1];
			__2[i][j] = __2[i + 1][j + 1] & 1;
			vis[i][j] = vis[i + 1][j + 1];
		}
		else {
			_2[i][j] = _2[i][j + 1] + vis[i][j + 1] - j;
			vis[i][j] = j;
			__2[i][j] = __2[i][j + 1];
		}
	}
	ans = 32767;
	for (int i = 0;i <= n;i++)
	{
		for (int j = 0;j <= m;j++)
		if (__1[i][j] && __2[i + 1][j + 1])
		{
			short tag;
			if (i != j)
			tag = 1;
			else tag = 0;
			ans = min(ans, (short)(_1[i][j] + _2[i + 1][j + 1] + tag));
		}
	}
	if (ans == 32767)
	ans = -1;
	cout << ans << '\n';
}

bool mem2;

signed main()
{
	IOS;
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：daniEl_lElE (赞：3)

考虑这类双字符串匹配问题，通常想到动态规划。

我们可以把操作看为：从右边一端，向左，删除，跳到左边，向右，删除。

那么这一段 $n$ 数组中有哪些呢？其实分为三部分：最左边滑动与删除，最右边滑动与删除，和中间不用滑动部分。

考虑 $dp_{i,j,0/1/2}$，$i$ 表示原字符串第 $i$ 位，$j$ 表示改变到的字符串第 $j$ 位，$0/1/2$ 分别表示左边，中间，右边部分。

考虑转移，每一次如果不删除，那么直接转移即可。

如果删除，对于左边，只需要删除的 $+1$ 即可；对于中间，我们会发现这一定是从一个左边的地方转移过来的，那么考虑统一统计前几次所有向右滑的方案以及从右边跳到最左边方案，也就是 $+(i+2)$ 即可；对于右边，我们考虑如果从中间转移过来，可以直接增加滑到这里的 $+(n-i+1)$，如果从右边转移，那么不需要加任何东西。

复杂度 $\Theta(tnm)$，由于空间不行需要使用滚动数组。

重点片段代码如下：~~某些数字是比赛的时候习惯打的作为最大值使用~~

```cpp
dp[0][0][0]=0,dp[0][0][1]=0;
for(int i=1;i<=n;i++){
	int t=i&1;
	int l=t^1;
	for(int j=0;j<=m;j++) dp[t][j][0]=dp[t][j][1]=dp[t][j][2]=1145141919810;
	for(int j=0;j<=m;j++){
		if(j!=m&&s1[i]==s2[j+1]){
			dp[t][j+1][0]=min(dp[t][j+1][0],dp[l][j][0]);
			dp[t][j+1][1]=min(dp[t][j+1][1],dp[l][j][1]);
			dp[t][j+1][2]=min(dp[t][j+1][2],dp[l][j][2]);
		}
		dp[t][j][0]=min(dp[t][j][0],dp[l][j][0]+1);
		dp[t][j][1]=min(dp[t][j][1],dp[l][j][0]+2+i);
		dp[t][j][2]=min(dp[t][j][2],min(dp[l][j][2],dp[l][j][1]+(n-i+1)));
	}
} 
if(min(dp[n&1][m][1],dp[n&1][m][2])==1145141919810) cout<<-1;
else cout<<min(dp[n&1][m][1],dp[n&1][m][2]);
```

---

## 作者：hyman00 (赞：2)

首先观察一下条件就能找到规律：

---

- 操作序列是先从右往左走一段，这一段中如果遇到需要删除的，按 `backspace`，否则，按 `left`，操作数是段长。

- 然后按一次 `home` 到开头去，操作数是 1。

- 然后从左往右走一段，先按 `right`，然后如果需要删除的，就再按一下 `backaspace`。

---

发现 `s` 被最终结束的位置，按 `home` 之前的位置分成了 3 段，记作 `a,b,c`。

那么需要满足的条件是什么呢？

首先，`b` 是 `t` 的一个子串，且这个子串左边的是 `a` 的一个子序列，这个子串右边的是 `c` 的一个子序列。

这时，有很多种方法可以处理这个问题，dp ，kmp 都可以，但是太复杂了。

---

我们枚举 `b` 的起始位置以及 `b` 在 `t` 中子串的起始位置，记为 `i,j`，再设 `k` 为 `b` 的长度。

枚举完，我们发现 `k` 一定取可能的中最大的，否则会影响到 `c` 的长度，一定是不优的。

如果每次暴力做的最坏复杂度在 `aaa...` 这种字符串上是 $O(n^3)$ 的，显然过不了。

---

考虑优化：

发现如果在 `i,j` 时跑出来了 `k` 且 $k\geq1$，那么在 `i+1,j+1` 时就不用跑了，直接算出来是 `k-1`。

记 $nxt_d$ 为当 $j-i=d$ 时的答案，每次如果 $nxt_d=-1$ 就直接暴力跑一遍，然后更新答案并 $nxt_d\leftarrow nxt_d-1$。

这时对每一个 $d$ 都只会跑 $n$ 遍，总复杂度 $O(n^2)$

---

还有一个问题，怎样判断这个子串左边的是 `a` 的一个子序列，这个子串右边的是 `c` 的一个子序列呢

可以发现它的两边恰好是 `s` 的前缀和后缀，就可以把 `t` 的字符尽可能往左，右放。

---

这时，你会喜提 WA，因为没有考虑直接走一个后缀，不按 `home` 键的情况。

---

```c++
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sz(a) ((int)a.size())
#define re return
#define all(a) a.begin(),a.end()
#define int long long
#define rept(i,a,b) for(int i=(a);i<(b);i++)
#define rep(i,a) rept(i,0,a)
#define vi vector<int>
#define pii pair<int,int>
#define F first
#define S second
using namespace std;
const int MOD=1000000007,INF=1000000000000000000;
template<typename T>inline void Mx(T &a,T b){a=max(a,b);}
template<typename T>inline void Mi(T &a,T b){a=min(a,b);}
inline int ad(int &a,int b,int c=MOD){re a=(a+b)%c;}
inline bool is_digit(int msk,int d){re (msk>>d)&1;}
const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int RD[5005];
int lf[5005],rt[5005];
int nxt[10005];
void run(){
	int n,m;
	string s,t;
	cin>>n>>m>>s>>t;
	int x=0,y=0;
	while(x<n&&y<m){
		if(s[x]==t[y]){
			lf[y]=x;
			y++;
		}
		x++;
	}
	if(y<m){
		cout<<"-1\n";
		re;
	}
	x=n-1,y=m-1;
	while(x>=0&&y>=0){
		if(s[x]==t[y]){
			rt[y]=x;
			y--;
		}
		x--;
	}
	int ans=n-m;
	rep(i,m)
		if(lf[i]!=i){
			ans=n-i;
			break;
		}
	rep(i,10005)nxt[i]=-1;
	rep(i,n){
		rep(j,m){
			if(nxt[j-i+5003]==-1){
				int k=0;
				while(i+k<n&&j+k<m&&s[i+k]==t[j+k])k++;
				nxt[j-i+5003]=k;
			}
			int k=nxt[j-i+5003];
			if((j==0||lf[j-1]<i)&&(j+k==m||rt[j+k]>=i+k))
				Mi(ans,(n-i-k)+1+i+(i-j));
			nxt[j-i+5003]--;
		}
	}
	cout<<ans<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int tc=1;
	cin>>tc;
	while(tc--)
		run();
	re 0;
}
```

---

## 作者：jucason_xu (赞：2)

### 分析

我们发现，我们实际上有三种方法：

- 只处理一段前缀

- 只处理一段后缀

- 处理一段后缀之后跳到开头处理一段前缀

而最后一种包括前两种。换而言之，整个字符串被分为三段：前缀、中部、后缀。

在前缀中，我们要经过一个数，花费是 $1$，删除一个数应当先经过它自己，花费是 $2$。在后缀中，经过和删除都是 $1$。

### 算法讨论

~~容易看出，此题应该用动态规划~~

总之，我们通过分析和推理，猜测动态规划可能用于解决这道题。

大家知道，正解的分类讨论是非常简洁漂亮的，但是我想介绍的是我这个蒟蒻的方法。__dp 预处理。__

设 $f_{i,j}$ 为把 $s$ 的前 $i$ 个字符处理成 $t$ 的前 $j$ 个字符，光标至少要行进多少次。（需要删除多少次不需要处理，因为它就是 $i-j$）

相似地，设 $g_{i,j}$ 为把 $s$ 去掉 $i$ 长前缀处理成 $t$ 去掉 $j$ 长前缀，光标至少要行进多少次。

这样，任何时候，$f_{i,j}$ 都可以通过更新值为 $i$ 从 $f_{i-1,j}$ 转移来，$g_{i,j}$ 都可以通过更新值为 $n-i$ 从 $g_{i+1,j}$ 转移来。

当 $s_i=t_j$ 时，$f_{i,j}$ 就可以等于 $f_{i-1,j-1}$，$g_{i,j}$ 就可以等于 $g_{i+1,j+1}$。

然后我们 __枚举前缀__ ，把两个字符串都分成两段，前一段以前缀解决，后一段以后缀解决。答案就是 $f_{i,j}+g_{i,j}+i-j+1$。当然不要忘了，当 $f_{i,j}=0$（也即不需要取前缀）的时候，没有回到开头的开销，答案就是 $g_{i,j}$。

 ### 内存限制

但是，当你发现这道毒瘤题 __卡内存__ 的时候，你就傻眼了，因为这玩意不能用滚动数组优化空间。

为什么呢？因为我们同一时间需要同时调用 $f_{i,j}$ 和 $g_{i,j}$ 的值，但是 $f$ 是从 __小下标推往大下标__ ，$g$ 是从 __大下标推往小下标__ ，只能预处理，不能即算即用。

这就不行了吗？不！

我们发现，$f$ 其实 __是可以通过滚动数组优化的__ ，问题只是出在 $g$ 上。

观察前面的方式，我们发现， __如果我们 dp 到实际上后缀前缀都不需涉足的地方，和直接 dp 到后缀的答案是一样的__ 。这就促使我们： __不要枚举前缀，而是枚举后缀的位置__ （也就是光标从最右边往左一直走到哪里）。而答案就是 $n-i+f_{i,j}+i-j+1$，原来的 $g_{i,j}$ 被直接转化为了 $n-i$ 处理。

但是问题又出现了。 __并非所有的后缀都是合法的__ ，我们必须保证选出的 $s$ 后缀和 $t$ 后缀有解。

那么令 $g_{i,j}$ 为设 $g_{i,j}$ 为把 $s$ 去掉$i$ 长前缀处理成 $t$ 去掉 $j$ 长前缀，是否有解。

位运算优化转移，

```cpp

g[i][j]=g[i+1][j]||(s[i]==t[j]&&g[i+1][j+1])。

````

但是问题又来了啊，这 $g$ 也不能用滚动数组啊，又得预处理，空间存不下呀！我们看似回到了最初的起点。

空间优化的方法不止一种！

除了常见滚动数组优化，还有一种方便的空间优化方法是 `bitset` 优化，通过压缩的方式，能够使数组缩小 $32$ 倍。（实际上 $256MB$ 的空间开 $5000\times5000$ 的数组也只是多了不到 $10$ 倍左右），它只能应用在 $01$ 数组上（也就是，数组里只有 $01$ 两个值），所以之前的 $f$ 和 $g$ 用不了。但是，我们新的 $g$，就是一个 $01$ 数组！

果断 `bitset` 优化。

而且，注意到 $f$ 在第二维的转移也是严格从小下标推往大下标的，因此可以只使用 __一维数组__ 进行滚动，进一步优化。~~（实际上已经没有必要了）~~

优化之后，我们就以 $3200KB$ 的空间成功切掉这题，还是比较宽裕的。

### 参考代码

```cpp

#include<bits/stdc++.h>
using namespace std;
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define st string
#define vt vector
#define pb push_back
#define int long long
typedef long long ll;
ll n,m;
ll f[5005];
bitset<5005>g[5005];
st s,t;
void solve(){
	cin>>n>>m>>s>>t;
	rep(i,0,n)g[i]=0;
	rep(j,0,m)f[j]=1e18;
	rep(i,0,n)g[i][m]=1;
	rp(i,n)rep(j,1,min(i,m)){
		g[n-i][m-j]=(g[n-i+1][m-j]|(s[n-i]==t[m-j]&&g[n-i+1][m-j+1]));
	}
	ll ans=1e18;
	rep(i,0,n){
		per(j,1,min(i,m)){
			if(f[j]!=1e18)f[j]=i;
			if(s[i-1]==t[j-1])f[j]=min(f[j],f[j-1]);
		}
		f[0]=i;
		rep(j,0,min(i,m))if(g[i][j]){
			ans=min(ans,f[j]+i-j+1+n-i);
			if(f[j]==0)ans=min(ans,n-i);
		}
	}
	if(ans==1e18)cout<<-1<<endl;
	else cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	rd(_,t)solve();
	return 0;
}
//Accepted!

```



---

