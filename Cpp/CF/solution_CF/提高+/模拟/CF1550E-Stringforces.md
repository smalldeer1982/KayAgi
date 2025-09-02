# Stringforces

## 题目描述

You are given a string $ s $ of length $ n $ . Each character is either one of the first $ k $ lowercase Latin letters or a question mark.

You are asked to replace every question mark with one of the first $ k $ lowercase Latin letters in such a way that the following value is maximized.

Let $ f_i $ be the maximum length substring of string $ s $ , which consists entirely of the $ i $ -th Latin letter. A substring of a string is a contiguous subsequence of that string. If the $ i $ -th letter doesn't appear in a string, then $ f_i $ is equal to $ 0 $ .

The value of a string $ s $ is the minimum value among $ f_i $ for all $ i $ from $ 1 $ to $ k $ .

What is the maximum value the string can have?

## 说明/提示

In the first example the question marks can be replaced in the following way: "aaaababbbb". $ f_1 = 4 $ , $ f_2 = 4 $ , thus the answer is $ 4 $ . Replacing it like this is also possible: "aaaabbbbbb". That way $ f_1 = 4 $ , $ f_2 = 6 $ , however, the minimum of them is still $ 4 $ .

In the second example one of the possible strings is "aabbccdda".

In the third example at least one letter won't appear in the string, thus, the minimum of values $ f_i $ is always $ 0 $ .

## 样例 #1

### 输入

```
10 2
a??ab????b```

### 输出

```
4```

## 样例 #2

### 输入

```
9 4
?????????```

### 输出

```
2```

## 样例 #3

### 输入

```
2 3
??```

### 输出

```
0```

## 样例 #4

### 输入

```
15 3
??b?babbc??b?aa```

### 输出

```
3```

## 样例 #5

### 输入

```
4 4
cabd```

### 输出

```
1```

# 题解

## 作者：zimujun (赞：19)

> 给定一个字符串，其中可能包含 $k$ 种字母或者 `?`，您可以用这 $k$ 种字母中的任意一种替代所有的 `?`，最大化所有种类字母在字符串中连续出现次数最大值的最小值。

题意翻译的可能有点绕。

要求使得最小值最大，可以考虑二分一个限制指 $len$，要求这 $k$ 种字符连续出现的最大次数都大于 $len$，然后判断这个限制值是否合法。

可以考虑然把这 $k$ 个长度为 $len$ 的连续段放入字符串的一个前缀，因为当没有别的限制的时候，我们肯定会选择贪心地加入，使得已经加入的前缀尽可能短，可以证明这样的构造方案一定不会更劣。

但是现在有确定字符的限制，而且不同种类字母的限制不同（被除了当前种类字字母在内的所有其他字母限制）。看到 $k \le 17$，考虑状压。

设 $f(S)$ 表示已经加入的字母种类集合为 $S$ 时所占前缀的最小长度。通过枚举往集合中新加入的字符刷表转移。最后判断 $len$ 是否合法即可转化为判断 $f(\{1,2,\cdots,k\}) \le n$ 是否成立，考虑如何优雅地实现这个转移。

做一个预处理，设 $next(i,j)$ 表示从第 $i$ 个位置，放长度为 $len$ 的第 $j$ 种字母的连续段，可以放到的最小右端点位置。倒序枚举 $i$，如果后面 $len$ 长度内出现了除了 `?` 和第 $j$ 种字母之内的其他字符（通过维护已经扫过去的每一种字符最靠左的位置实现即可），那就把 $next(i, j)$ 赋值为 $next(i + 1, j)$，如果没有出现，那就是 $i + len$。这样处理一遍的复杂度为 $O(nk)$。

完成这个预处理，我们就可以实现这个转移了。

$$\large f(S) = \min_{T\subsetneqq S\land T\cap\{i\} = S}\left\{next(f(T), i)\right\}$$

枚举状态和字符转移即可，复杂度为 $O(k2^k)$。

总的复杂度为 $O((nk + k2^k)\log n)$。

---

## 作者：Alex_Eon (赞：4)

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1550e)

### 主体思路：二分+状压 DP

### 复杂度：$O((kn + k \times 2^k) \log n)$

### 完整思路

直接二分 $len$，问题转化为判断是否存在一种构造使得字符集中每种字符均有长度不小于 $len$ 的连续段。

$k$ 的范围提示我们考虑状压，设 $f_i$ 表示集合 $i$ 中的字符已经出现过合法连续段所占用的最短前缀长度。

对于已经转移好的 $f_i$，尝试向集合 $i$ 中加入一种字符使得集合变为 $i'$，有转移 $f_{i'} = f_i + val$，其中 $val$ 表示从 $i + 1$ 开始到可以构造出使得新加入字符合法的最短长度。

暴力转移复杂度不太能接受，考虑预处理 $to_{ch, i}$ 表示从 $i$ 开始进行构造使得字符 $ch$ 合法的最近位置。

这个东西可以倒序枚举 $i$ 进行处理：

$$
to_{ch, i} = 
\begin{cases}
i + len \quad \forall i\leq k < i + len \land (s_j = ch \lor s_j = \text ?)\\
to_{ch, i + 1} \quad \mathrm{otherwise}
\end{cases}
$$

不那么形式化的说，我们尝试维护一个截止到当前位的连续匹配最大长度，如果当前长度大于 $len$，那么说明从当前位可以直接构造一个合法匹配，直接计算位置即可，否则继承上一位的位置。

于是这样就可以 $O(1)$ 转移了。

边界有 $to_{ch, n + 1} = n + 1$，这样只要判断位置不超过 $n$ 就可以用来转移，最后判断全集的 DP 值是否在 $n$ 以内即可。

### 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 2e5 + 5, K = 17, Sta = (1 << 17) - 1 + 5;

int n, m;
char s[N];

int to[K][N], f[Sta];

bool check(int val) {
    for (int ch = 0; ch < m; ch++) { // 预处理 to 数组
        to[ch][n + 1] = n + 1; // 处理边界
        for (int pos = 0, i = n; i >= 1; i--) {
            if (s[i] == ch + 'a' || s[i] == '?') // 维护极长连续段
                pos++;
            else
                pos = 0;
            if (pos >= val) // 转移
                to[ch][i] = i + val - 1;
            else
                to[ch][i] = to[ch][i + 1];
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 0; i < (1 << m); i++)
        for (int j = 0; j < m; j++)
            if (!((i >> j) & 1) && f[i] < n) // 枚举下一个字符进行转移
                f[i | (1 << j)] = min(f[i | (1 << j)], to[j][f[i] + 1]);
    return f[(1 << m) - 1] <= n;
}

int calc() { // 二分
    int l = 0, r = n / m, res = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid))
            l = (res = mid) + 1;
        else
            r = mid - 1;
    }
    return res;
}
//--------------------//
int main() {
    scanf("%d%d%s", &n, &m, s + 1);
    printf("%d", calc());
    return 0;
}

```

---

## 作者：2huk (赞：2)

> - 给定字符串 $s$ 和整数 $k$，$s$ 由前 $k$ 小的字母或 $\texttt?$ 构成。你需要将每个 $\texttt ?$ 替换成某个前 $k$ 小的字母。定义其价值为前 $k$ 个字母中最小的最大连续出现的长度，例如 $\texttt {aaaabbbbbb}$ 的价值为 $4$。求最大价值。
> - $n\leq 2\times 10^5$，$k\leq 17$。

令 $V$ 表示前 $k$ 个字母组成的集合。

首先二分答案 $x$。我们要检查是否存在一种方案，使得每个字母连续出现的长度都 $\ge x$。

考虑状压 DP。设 $f(S)$ 表示若只考虑 $S$ 中的字母，其中 $S$ 是 $V$ 的子集，最小的需要用到的前缀的长度。例如 $x = 4, s = \texttt{a??ab?????b}$ 时，$f(\{1, 2\}) = 8$。若整个 $s$ 都不能表示 $S$ 则 $f(S) = n + 1$。

二分合法等价于 $f(V) \le n$。

考虑转移。令 $g(c, i)$ 表示从 $i$ 往后，最靠前的一个长度为 $x$ 的连续的字符 $c$ 的段的末尾位置。此时 $g$ 和 $f$ 的转移：
$$
g(c, i) = \left\{\begin{matrix}
i + x - 1  & \forall j \in [i, i + x - 1] ,s_j \in \{c, \texttt ?\}\\
g(c, i + 1)  & \text{otherwise.}
\end{matrix}\right.
$$

$$
f(S\cup \{i\}) = \min_S g(f(S) + 1, i)
$$

```cpp
#include <bits/stdc++.h>

constexpr int N = 200009, M = 18;

int n, k;
std::string str;
int f[1 << M], nxt[N][M], sum[N][M];

int main() {	
	std::cin >> n >> k >> str;
	str = ' ' + str;
	
	for (int i = 1; i <= n; ++ i )
		for (int j = 0; j < k; ++ j )
			sum[i][j] = sum[i - 1][j] + (str[i] == j + 'a' || str[i] == '?');
	
	auto chk = [&](int mid) -> bool {
		for (int j = n + 1; j < N; ++ j )
			for (int i = 0; i < k; ++ i ) nxt[j][i] = n + 1;
		
		for (int i = n; i; -- i )
			for (int j = 0; j < k; ++ j )
				nxt[i][j] = i + mid - 1 <= n && sum[i + mid - 1][j] - sum[i - 1][j] == mid ? i + mid - 1 : nxt[i + 1][j];
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		for (int i = 0; i < (1 << k); ++ i )
			for (int j = 0; j < k; ++ j )
				if (!(i >> j & 1)) f[i | (1 << j)] = std::min(f[i | (1 << j)], nxt[f[i] + 1][j]);
		
		return f[(1 << k) - 1] <= n;
	};
	
	int l = 1, r = n, res = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (chk(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	std::cout << res;
	
	return 0;
}
```

---

## 作者：ricky_lin (赞：2)

[更好的阅读体验](https://www.cnblogs.com/rickylin/p/solution_CF1550E.html)

**阅读须知：本题解较为详细地讲述的该题解法的思路和来龙去脉，但篇幅较长，请耐心阅读。**

---

### Step 1 从题面获取信息

我们考虑，因为最大值最小，所以我们首先想到二分答案。

然后我们又看到 $k \leq 17$ 这个限制，所以会想到可能是关于一个 $2^k$ 之类的复杂度。

以上就是我们第一步从题目的数据范围中挖掘出来的一些思路。

---

### Step 2 从暴力入手进行优化

我们二分答案 $mid$ 之后，就只需要判断答案 $mid$ 的可行性了，也就是说我们要判断是否每一种字母都能有 $mid$ 长度的子串。

对于判断正确性显然有一种非常简单的暴力，就是枚举字母所确定的子串所出现的相对顺序，然后暴力 `check` 是否可行，这是 $O(n\times k!)$ 的，但是显然不能通过这道题。

#### ① 状态枚举的优化

这时，我们复杂度瓶颈在于花去太多时间在出现顺序的枚举（$n!$），而我们上文分析到的 $2^k$ 显然他的一个很好的转化的终点。

那么为什么能转化呢，又如何转化呢？

**为什么能**：我们发现每次加进去一种字母的长为 $mid$ 的段时，并不需要知道之前的字母的出现的顺序到底是什么，而我们的 $n!$ 的暴力算法的顺序枚举显然会多出许多不必要的信息的枚举，这显然给了我们代码时间复杂度的优化空间。

**如何转化**：我们可以设 $dp_S$ 表示让集合 $S$ 中的所有字母都满足有长度为 $mid$ 的子串的最短的前缀（显然前缀越短剩下的字母放完的可能性才更大）。

温馨提示：这里的前缀串在记录时为**开区间**。

这下我们就将状态个数优化到了 $2^k$，$O((n+k)2^k\log n)$ 是不能通过本题的，但是状态显然是已经优化到了极致，所以我们只能从转移上下手，尝试把 $n$ 给干掉。

---

#### ② 转移的优化

我们发现每个位置的转移的显然不需要依赖于当前的整个状态（数量：$2^k$），只需要依赖于当前需要加入哪种字母（数量：$k$）进入集合，所以说我们可以将原本的 $n2^k$ 的转移变成 $nk$ 。

显然地，你需要预处理转移数组 $jump_{i,j}$ 表示原来的前缀串以 $i$ 结束，满足入第 $j$ 种字母的要求后，新的前缀串的最小的右端点的位置，这时需要倒序枚举（后面有解释），转移如下：

$$
jump_{i,j} = 

\begin{cases}
i+len & \forall i\leq k < i+len，s_j = 'a'+j~||~s_j = '?'\\
jump_{i+1,j} & otherwise
\end{cases}
$$

而对于第一种转移的限制条件的判定，我们可以动态维护除了这一种字母、其他字母最左边出现的位置，这显然需要倒序枚举。

### Step 3 思考实现细节并敲出代码

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 2e5 + 8,MM = 20;
int dp[1 << MM];
int n,k;
char s[NN];//字符串
int jump[NN][MM];
int minp[MM];//第i种字母最左边出现的位置
int res[MM];//除第i种字母以外的其他字母最左边出现的位置
bool solve(int len){
	memset(dp,0x3f,sizeof(dp));
	memset(res,0x3f,sizeof(res));//初始化
	for(int i = 0; i < k; ++i) minp[i] = n+1,jump[n+1][i] = n+2,jump[n+2][i] = n+2;//限定边界
	for(int i = n; i >= 1; --i){
		if(s[i] != '?'){//更新res
			minp[s[i]-'a'] = i;
			for(int j = 0; j < k; ++j){
				if(s[i]-'a' == j) continue;
				res[j] = i;
			}
		}
		for(int j = 0; j < k; ++j){//转移
			if(res[j] >= i+len) jump[i][j] = min(n+2,i+len);
			else jump[i][j] = jump[i+1][j];
		}
	}
	dp[0] = 1;
	for(int i = 1; i < (1 << k); ++i){//DP转移
		for(int j = 0; j < k; ++j)if(i >> j & 1){
			dp[i] = min(jump[dp[i^(1 << j)]][j],dp[i]);
		}
	}
	return dp[(1 << k)-1] <= n+1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> k;
	cin >> s+1;
	int l = 0,r = n,ans = 0;
	while(l <= r){
		int mid = (l + r) / 2;
		if(solve(mid)) l = mid + 1,ans = mid;
		else r = mid - 1;
	}
	printf("%d",ans);
}
```

---

## 作者：ZHR100102 (赞：2)

不懂了，为啥这么一道纯靠堆 trick 堆出来的唐氏状压能把全机房难住啊，感觉 CF 评的 \*2500 都评高了。

# 思路

首先观察到求的是最大化最小值，所以显然具有单调性，我们考虑二分这个最小值。

那么如何判断每个数是否都能到这个最小值呢？我们首先可以设计一个很暴力的 dp：定义 $dp_{i,j}$ 表示考虑到第 $i$ 位，已经达到最小值的字符集是 $j$ 是否可行。

转移是显然的，但是显然这个 dp 也是会 T 飞的，我们继续观察，这个 dp 式子的值显然只能有两个：$0,1$。所以说明这个 dp 的值域很小，我们考虑交换 dp 数组两维的 trick，把可行性放到状态定义里，把 $i$ 作为 dp 的值。

于是现在的 dp 定义就是：$dp_j$ 表示已经达到最小值的字符集是 $j$ 的情况下，最小的 $i$ 的值。为啥是最小的 $i$ 呢？因为在 $i$ 最小的时候就能给后面留更多的位置来拼凑出答案。

所以我们再定义一个 $suf_{i,j}$ 表示 $i$ 后面第一个能形成长度为 $mid$ 的 $j$ 字母形成的连续段的结尾位置，通过在二分的时候预处理出来，然后跑状压 dp 转移即可。

转移方程为：$dp_{j}=\min_{c\in j} suf_{dp_{s}+1,c}$。其中 $c\in j$ 表示 $j$ 在二进制下为 $1$ 的位是 $c$，$s$ 表示 $j$ 在去掉第 $c$ 位的 $1$ 后的状态。

那么二分合法的条件就是最终所有字母都满足的情况下的 dp 值 $\le n$。

时间复杂度 $O(2^n k \log n)$。

上面的转移方程用的是填表法，代码里写了刷表法。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,suf[N][20],dp[200005];
char c[N];
void init(int len)
{
	memset(suf,0x3f,sizeof(suf));
	for(int i=0;i<m;i++)
	{
		int now=0;
		for(int j=n-len+2;j<=n;j++)now+=(!(c[j]=='?'||c[j]-'a'==i));
		for(int j=n-len+1;j>=1;j--)
		{
			now+=(!(c[j]=='?'||c[j]-'a'==i));
			suf[j][i]=suf[j+1][i];
			if(now==0)suf[j][i]=j+len-1;
			now-=(!(c[j+len-1]=='?'||c[j+len-1]-'a'==i));
		}
	}
}
bool check(int len)
{
	if(len>n)return 0;
	init(len);
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=0;i<(1<<m);i++)
	{
		int cur=dp[i];
		if(cur>=n)continue;
		for(int j=0;j<m;j++)
		{
			if(((i>>j)&1)==0)
			{
				int v=(i^(1<<j));
				dp[v]=min(dp[v],suf[cur+1][j]);
			}
		}
	}
	return (dp[(1<<m)-1]<=n);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>c+1;
	int l=0,r=200005,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(check(mid))l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

要求最小值最大，套路地二分。

二分后考虑 $dp_{S}$ 表示 $S$ 集合内所有字符都存在长度为 $mid$ 的连续子段的最短前缀长度。预处理出 $pre_{i,j}$ 表示从 $i$ 位置开始最短到哪里才有连续的长度为 $mid$ 的子段。转移枚举下一个出现的字符即可。总复杂度 $O((n+2^k)k\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
string s;
int pre[200005][18],ext[200005][18],dp[131072]; 
signed main(){
	int n,k; 
	cin>>n>>k;
	cin>>s; s=" "+s;
	for(int i=1;i<=n;i++){
		for(int j=0;j<17;j++) pre[i][j]=pre[i-1][j]+(s[i]-'a'==j);
		pre[i][17]=pre[i-1][17]+(s[i]=='?');
	}
	int L=0,R=n;
	while(L<R){
		int mid=(L+R+1)>>1;
		memset(ext,1,sizeof(ext));
		for(int i=1;i+mid-1<=n&&i<=n;i++){
			for(int j=0;j<17;j++){
				if(pre[i+mid-1][j]-pre[i-1][j]+pre[i+mid-1][17]-pre[i-1][17]==mid){
					ext[i][j]=i+mid-1;
				}
			}
		}
		for(int i=n;i>=1;i--){
			for(int j=16;j>=0;j--){
				ext[i][j]=min(ext[i][j],ext[i+1][j]);
			}
		}
		memset(dp,1,sizeof(dp));
		dp[0]=0;
		for(int i=0;i<(1<<k);i++){
			if(dp[i]<n){
				for(int j=1;j<=k;j++){
					if(!((i>>(j-1))&1)){
						dp[i|(1<<(j-1))]=min(dp[i|(1<<(j-1))],ext[dp[i]+1][j-1]);
					}
				}
			}
		}
		if(dp[(1<<k)-1]<=n){
			L=mid;
		}
		else{
			R=mid-1;
		}
	}
	cout<<L;
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

很不错的题。

其实难度并不大，建议自己尝试一下。

## 思路

首先这个经典的求最值的相对的另一个最值，比如这题的求最小值最大，如果满足单调性那么一眼就是二分答案了。

这个题的单调性比较显然，如果做不到每种字符都连续 $k$ 个，就更别提比 $k$ 大了；如果做到了连续 $k$ 个，那么比 $k$ 小的更不成问题。

考虑二分这个最小值最大是 $x$，然后往这个边界进行可行性判定。

那么就有一个朴素的 DP：令 $f_{i,S}$ 表示前 $i$ 位，能否满足了状态为 $S$ 的小写字母集均出现了不少于 $x$ 次。

这样是 $O(2^k kn \log n)$ 的不够优秀，考虑优化。

注意到这个 DP 状态只存储了可行性有点浪费，我们考虑以下状态设计：$f_{S}$ 表示满足状态为 $S$ 的小写字母集均出现不少于 $x$ 次的时候，所需要的最短前缀是多少。

这个状态转移起来的正确性是有的，因为一定有一种状压顺序使得它取到最大。但是这样暴力转移的复杂度也不能接受，不过我们可以预处理一些东西来降低复杂度。

具体的，预处理一个 $R_{i,j}$ 表示以 $i$ 为左端点，一直向右，使得 $j$ 这种小写字母出现 $x$ 次的最左的位置是多少。这个转移比较显然，我们倒序处理这个问题，每次只需要双指针维护 $i \sim i+x-1$ 是否合法，如果合法那么 $R_{i,j}=i+x-1$，否则 $R_{i,j}=R_{i+1,j}$。这部分复杂度 $O(nk)$。

那么我们的转移方程也比较显然了，这里假设**数组下标从 1 开始而状压的 S 从第 0 位开始**存储：

$f_{i,S}=\min\limits_{S\&2^k=1}R_{f_{i,S-2^k},k+1}$，其中 $\&$ 符号表示二进制下按位与（C++ 中的 `&` 符号）。

转移的复杂度为 $O(k2^k)$。至于判断是否合法，就看 $f_{i,2^k-1}$ 是不是小于等于 $n$ 就好了。

所以总的复杂度就是加上二分的 $\log$，为 $O((nk+k2^k)\log n)$，可以通过。

## 代码

[Code & Submission](https://codeforces.com/contest/1550/submission/219444912)

---

## 作者：Engulf (赞：0)

题目要求最大值最小，本题的答案具有单调性，考虑二分这个最大值转化为可行性问题。

设当前二分的答案为 $x$，考虑怎么判断答案是否可行。

注意到 $k\le 17$，考虑状态压缩动态规划。由于我们并不关心字母的先后顺序，即字母是无序排列状态，想到设 $f_S$ 表示让字符集为 $S$ 的字母满足题目要求，即每个字母的最长连续段都 $\ge x$ 的最小长度。$S$ 在代码实现上会使用二进制压缩。

考虑当前集合 $S$，我们加入一个 $S$ 中没有的字符 $c$，想想答案会怎么变。由于 $S$ 是无序的，我们不关心这些字母的先后顺序，可以假定我们在 $S$ 后面加入 $c$，即我们想知道 $f_S + 1$ 这个位置往后要到哪个地方才会出现长度 $\ge x$ 的连续段。

这个东西可以 $O(nk)$ 预处理出来记为 $ne_{i,c}$。

现在可以写出状态转移方程了：

$$f_{S\cup \{c\}} = \min(f_{S\cup \{c\}}, ne_{f_S,c})$$

你可能会有疑问，如果有这样一种情况，当前集合 $S$，现在加入 $c$，我们默认是在末尾加，如果前 $f_S$ 个字符中已经存在 $c$，且它的最长连续段满足了要求，这样是否会漏解？

其实是不会的，因为我们枚举的是集合，可能存在另外两个集合，他们的并和 $S \cup \{c\}$ 是一样的，顺序不一样罢了，肯定会算到在前面的那个 $c$ 的连续段。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n, k;

char str[N];

int ne[N][20];

int f[1 << 20];

bool check(int mid) {
    for (int c = 0; c < k; c++) {
        ne[n + 1][c] = n + 1;
        int len = 0;
        for (int i = n; i; i--) {
            if (str[i] == c + 'a' || str[i] == '?')
                len++;
            else
                len = 0;
            if (len >= mid) ne[i][c] = i + mid - 1;
            else ne[i][c] = ne[i + 1][c];
        }
    }
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 0; i < (1 << k); i++)
        for (int j = 0; j < k; j++)
            if (!(i >> j & 1) && f[i] < n)
                f[i | (1 << j)] = min(f[i | (1 << j)], ne[f[i] + 1][j]);
    return f[(1 << k) - 1] <= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> str + 1;

    int l = 0, r = n, res;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) res = mid, l = mid + 1;
        else r = mid - 1;
    }

    cout << res << "\n";
    return 0;
}
```

---

## 作者：forest114514 (赞：0)

### CF1550E Stringforces

还是不错的题，结合了许多 trick，变得不是那么板。

看到 $K\le 17$ 猜到状压，看到最大化最小的 $\operatorname{MaxLen}(S,v)$ 想到二分答案。

两个 trick 结合起来，我们每次二分能否是所有的 $\operatorname{MaxLen}(S,v)$ 都 $\ge mid$，记录 $f_{mask}$ ，表示当前满足限制的字符集为 $mask$ 是此时填完的最小右端点。

可以直接暴力做，注意到此时最小右端点一定是 $mask$ 中出现过的字符，所以前面的所有字符串都没有贡献，我们可以建一个用于优化转移的类似自动机的玩意，令 $trans_{i,c}$ 为从 $i$ 开始，满足字符 $c$ 有长度 $len$ 的连续段时的最小右端点，注意此时这个区间里面有没有其他未出现字符可以满足条件是没有任何影响的，此时 DP 转移为 $f_{mask|(1<<i)}=trans _{f_{mask}+1,i}$。

考虑如何处理 $trans$ 数组，我们倒序枚举，此时有：
$$
trans_{i,c}=\begin{cases}i+len-1&\forall i\in[i,i+len-1],s_i=?\lor s_i=c\\trans_{i+1,c}&otherwise\end{cases}
$$
最后 $trans_{n+1,c}=\operatorname{inf}$，check 时候判断 $f_{2^{c}-1}$ 是否等于 $\operatorname{inf}$ 即可。

时间复杂度为 $O((nk+k2^k)\log n)$，空间复杂度为 $O(nk+k2^k)$。

---

## 作者：Delov (赞：0)

$K \leq 17$ 显然是要我状压了。最小值最大可以二分，那么 check 就得是 dp 了，但是一开始写出来的是 $n2^k k^2 $ 的垃圾 dp ，dp 的状态是记录当前已经满足要求的字母，最后一个字母是啥，然后 dp 值是最后一个字母的连续段长度，这样每次枚举下一个位置填啥，大概不如直接爆搜。

二分长度 $len$，check 具有一点贪心性质。考虑全都是问号的串，显然我们会充分利用，在前边每 $len$ 个放一种字母。但是现在有一些位置已经放了字母，有些位置可能无法满足放一个长度为 $len$ 的某种字母的串。实际上我们可以延续贪心的做法，假设我就要从这个位置开始填一种字母，那么我们可以找出它最少得填到哪才行，中间多出来的部分就废掉。

那么 dp 就有一个轮廓了，我们状压当前已经满足条件的字符的集合，dp 值为达到当前状态至少要填完长度为多少的前缀，枚举下一个填哪种字母转移，实际上就是枚举了我们贪心填每种字母的顺序，正确性是比较显然的。转移可以预处理出 $Minr_{i,c}$ 表示从第 $i$ 个位置开始填第 $c$ 种字母，至少需要填到什么位置才出现长度为 $len$ 的连续段，倒序枚举一遍即可，如果从 $i$ 开始的恰好为 $len$ 的段恰好能填那么就是 $i+len-1$，否则直接继承下一个位置的值即可。check 的复杂度为 $O(nk+k2^k)$，外层再套一个二分。

---

