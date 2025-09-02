# [ABC343G] Compress Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc343/tasks/abc343_g

$ N $ 個の文字列 $ S_1,S_2,\ldots,S_N $ が与えられます。

これらの文字列全てを部分文字列として含むような文字列の長さの最小値を求めてください。

ただし、ある文字列 $ S,T $ に対して、$ S $ が $ T $ を部分文字列として含むとは、$ S $ の先頭から $ 0 $ 文字以上、末尾から $ 0 $ 文字以上削除することで $ T $ が得られることをいいます。

## 说明/提示

### 制約

- $ N $ は整数
- $ 1\leq\ N\ \leq\ 20 $
- $ S_i $ は英小文字からなる長さ $ 1 $ 以上の文字列
- $ S_1,S_2,\dots,S_N $ の長さの総和は $ 2\times\ 10^5 $ 以下

### Sample Explanation 1

長さ $ 9 $ の文字列 `snukensho` は $ S_1,S_2,S_3 $ 全てを部分文字列として含みます。 具体的には、`snukensho` の $ 1 $ 文字目から $ 5 $ 文字目までが $ S_1 $ に、$ 4 $ 文字目から $ 9 $ 文字目までが $ S_2 $ に、$ 3 $ 文字目から $ 4 $ 文字目までが $ S_3 $ にそれぞれ対応しています。 これより短い文字列であって、$ S_1,S_2,S_3 $ 全てを部分文字列として含むものは存在しません。 よって、答えは $ 9 $ です。

## 样例 #1

### 输入

```
3
snuke
kensho
uk```

### 输出

```
9```

## 样例 #2

### 输入

```
3
abc
abc
arc```

### 输出

```
6```

## 样例 #3

### 输入

```
6
cmcmrcc
rmrrrmr
mrccm
mmcr
rmmrmrcc
ccmcrcmcm```

### 输出

```
27```

# 题解

## 作者：SkyWave (赞：7)

# 题意

给你 $N$ 个由小写字母组成的字符串 $S_1, S_2, \ldots, S_N$，找出一个母串使得它包含所有这些字符串作为它的子串，最小化该母串的长度并输出。

$1 \leq N \leq 20$，$\sum |S_i| \leq 2 \times 10 ^ 5$

（没错洛谷翻译就是我写的）

# 思路

首先如果有一个字符串被另一个字符串完全包括，那么直接把被包括的字符串删了显然是不影响答案的。

对于剩下的字符串，直接把所有字符串拼接在一起形成母串肯定可行，但假如我们有两个字符串，前一个字符串的后缀和后一个的字符串前缀有一段匹配，那么将后一个字符串的这段前缀删去再加入显然也是合法的母串，所以我们可以贪心删最长匹配。

![](https://cdn.luogu.com.cn/upload/image_hosting/o9qeuc2j.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/41rm9kew.png)

我们设 $l_i$ 为第 $i$ 为 $S_i$ 的长度，$d(i, j)$ 为第 $j$ 个字符串拼接在第 $i$ 个字符串后面时最少需要额外追加的字符数量，按照刚才的思路 $d(i, j)$ 就等于 $l_j$ 减去 $S_i$ 的后缀与 $S_j$ 的前缀的最长匹配。那么该如何计算这个最长匹配呢？~~当然可以使用 exkmp~~。对于每对 $(i, j)$，因为最长匹配长度 $\leq \min(l_i, l_j)$，所以直接枚举最长匹配可能的取值再用哈希判断复杂度就对了，$O(n^2 + n \sum l_i)$。

那么根据刚才的思路，问题现在被转换成了如果 $S_i$ 成为母串开头的字符串，那么母串会增加 $l_i$ 长度。如果 $S_j$ 要接在 $S_i$ 后面，母串最少会增加 $d(i, j)$ 长度。还是问你母串最短能是多少。

那直接把每个字符串看成一个点，$d(i, j)$ 看成 $i$ --> $j$ 的一条边的边权，从第 $i$ 个点出发初始有 $l_i$ 的代价，那么经过所有点恰好一次的通路的最小代价就是母串的最短长度。不难发现实际上就是经典的 TSP 问题，状压 dp 解决之。这部分时间复杂度为 $O(n^2 \times 2^n)$，所以总复杂度就是 $O(n^2 + n \sum l_i + n^2 \times 2^n)$，5 秒非常宽松，??！

# 实现

这份代码在作者写这篇题解的时候还是 atc 全站最优解。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

template <class T>
inline void cmin(T &a, const T &b) {
    if (a > b) {
        a = b;
    }
}

const int N = 20, M = 2e5 + 1, Base = 29;

char str[M + 1]; int len[N];
unsigned powBase[M], hashy[N][M];

int dis[N][N], dp[1 << N][N];

int main(int argc, const char * argv[]) {
    powBase[0] = 1;
    for (int i = 1; i < M; ++i) {
        powBase[i] = powBase[i - 1] * Base;
    }
    
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", str + 1);
        len[i] = (int)strlen(str + 1);
        for (int j = 1; j <= len[i]; ++j) {
            hashy[i][j] = hashy[i][j - 1] * Base + str[j] - 'a' + 1;
        }
    }
    int del = 0;
    for (int i = 0; i < n; ++i) if (!(del & 1 << i)) {
        for (int j = 0; j < n; ++j) if (i != j && !(del & 1 << j)) {
            int leni = len[i], lenj = len[j];
            for (int k = 1; k <= leni - lenj + 1; ++k) {
                if (hashy[i][k + lenj - 1] - hashy[i][k - 1] * powBase[lenj] == hashy[j][lenj]) {
                    del |= 1 << j;
                    break;
                }
            }
            if (del & 1 << j) {
                continue;
            }
            for (int k = lenj - 1; k >= 0; --k) {
                if (hashy[j][k] == hashy[i][leni] - hashy[i][leni - k] * powBase[k]) {
                    dis[i][j] = lenj - k;
                    break;
                }
            }
        }
    }
    int undel[N], r = 0;
    for (int i = 0; i < n; ++i) if (!(del & 1 << i)) {
        undel[r++] = i;
    }
    n = r;
    int all = (1 << n) - 1;
    for (int i = 1; i <= all; ++i) {
        memset(dp[i], 127, sizeof(int) * (n + 1));
    }
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = len[undel[i]];
    }
    for (int state = 1; state < all; ++state) {
        for (int i = state; i; i &= i - 1) {
            int pi = __builtin_ctz(i);
            for (int j = all ^ state; j; j &= j - 1) {
                int pj = __builtin_ctz(j);
                cmin(dp[state | 1 << pj][pj], dp[state][pi] + dis[undel[pi]][undel[pj]]);
            }
        }
    }
    printf("%d\n", *min_element(dp[all], dp[all] + n));
    return 0;
}
```

---

## 作者：Expert_Dream (赞：5)

第一次赛时秒 G！！！（鼓掌。。

这题其实很简单。

我们看到 $n \le 20$，那是什么？状压 Dp。没错。考虑如何转移呢？

应该说如果状态里已经有了 $i$ 这个字符串，我们还有一个字符串 $j$，该如何转移进去呢？

那我们分两种情概况：
- 字符串 $s_j$ 完全在 $s_i$ 中，我们可以不用增加代价的转移，为了实现，我们需要预处理每两个字符串是否互相包含，用 KMP 来预处理。
- $s_j$ 要拼在 $s_i$ 后面，我们要重合尽可能多，才能保证长度尽可能小，所以我们可以算出这两个字符串的最长公共前后缀，这是什么？对，KMP 的 next 数组！也是预处理得出来。如果我们要看 $s_j$ 拼在 $s_i$ 后面的最长前后缀，那么我们将 $s_j$ 在前，$s_i$ 在后（~~我没有写错，就应该反着拼~~），然后拼接成新的字符串，去跑 KMP 用的那个 next 数组。注意，这个字符串的最长公共前后缀必须要小于两个字符串分别的长度。我们就不停的往回跳，直到符合长度。这是 KMP 算法的精髓，就是不断找次长的最长公共前后缀。不懂的看这 [link](https://www.cnblogs.com/gsczl71/p/17888951.html)。这样，我们就可以算出 $s_j$ 要拼在 $s_i$ 后面，最长重合多少。

这样，我们就可以直接状压 DP 解决。按照上述两种情况转移。

$len$ 是字符串长度 $2 \times 10^5$。

预处理时间复杂度 $O(n^2 \times len)$。

状压是 $O(n \times 2^n)$。乍一看像是 $O(n^2 \times 2^n)$，实际上其中一个 $O(n)$ 的时间复杂度是拆位状态，判断这一位有没有，但这个可以约做常数，仅仅是给时间复杂度中 $2^n$ 的指数增加一个小常数，完全可以忽略。

[code](https://atcoder.jp/contests/abc343/submissions/50840179)。

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc343_g%20[ABC343G]%20Compress%20Strings)

# 思路

首先假设有两个串 $a,b$，如果 $b$ 是 $a$ 的子串，且 $a \neq b$ 则不需要考虑 $b$；如果 $a = b$，则如需要保留一个 $a$。

做完上述操作后，显然最终的答案是由这些串按照一定顺序拼接起来，再删掉重叠部分。

例如：`abbcc` 与 `ccdde` 拼接为 `abbccccdde`，发现 `cc` 是重复的，所以删掉重叠部分为 `abbccde`。

显然我们可以使用 KMP 在 $\Theta(n^2 \cdot |S|)$ 的复杂度内求解出任意两个串 $s_i,s_j$ 的重叠部分，记作 $num_{i,j}$。

于是就变成了经典状压，我们定义 $dp_{st,i}$ 表示选取串的集合表示为 $st$，且最后选的一个串为 $s_j$。

然后就是经典状压转移了。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 24,M = 4e5 + 10,K = (1 << 20) + 10,inf = 0x3f3f3f3f;
int n,m,ans = inf;
int nxt[M],len[N];
int num[N][N],dp[K][N];
string t[N],s[N];
unordered_map<string,bool> vis;

inline int kmp(string a,string b){
    string s = a + '&' + b; int len = s.length();
    for (re int i = 0;i < len;i++) nxt[i] = 0;
    for (re int i = 1,j = 0;i < len;i++){
        while (j && s[i] != s[j]) j = nxt[j - 1];
        if (s[i] == s[j]) j++;
        nxt[i] = j;
    }
    return nxt[len - 1];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(dp,inf,sizeof(dp));
    cin >> n;
    for (re int i = 1;i <= n;i++) cin >> t[i];
    for (re int i = 1;i <= n;i++){
        for (re int j = 1;j <= n;j++){
            if (i == j) continue;
            if (t[j].find(t[i]) != string::npos && t[i] != t[j]) goto End;
        }
        if (vis.count(t[i])) continue;
        vis[t[i]] = true;
        s[++m] = t[i]; len[m] = t[i].length();
        End:;
    }
    n = m;
    for (re int i = 1;i <= n;i++){
        for (re int j = 1;j <= n;j++){
            if (i != j) num[i][j] = kmp(s[j],s[i]);
        }
    }
    for (re int st = 1;st < (1 << n);st++){
        int cnt = __builtin_popcount(st);
        if (cnt == 1){
            int x;
            for (re int i = 0;i < n;i++){
                if ((st >> i) & 1){
                    x = i + 1; break;
                }
            }
            dp[st][x] = len[x];
        }
        for (re int i = 0;i < n;i++){
            if (!((st >> i) & 1)) continue;
            for (re int j = 0;j < n;j++){
                if ((st >> j) & 1) continue;
                dp[st | (1 << j)][j + 1] = min(dp[st | (1 << j)][j + 1],dp[st][i + 1] + len[j + 1] - num[i + 1][j + 1]);
            }
        }
    }
    for (re int i = 1;i <= n;i++) ans = min(ans,dp[(1 << n) - 1][i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：1234567890sjx (赞：2)

首先考虑弱化版 [CF25E](https://www.luogu.com.cn/problem/CF25E) 一题，即 $n=3$ 的特殊情况的做法。

容易发现，当 $n=3$ 的时候一共只有 $3!=6$ 种不同的组合顺序满足母串 $S$ 中 $S_1,S_2,S_3$ 的出现顺序不同。所以考虑暴力枚举全排列得到这些不同的顺序，然后设当前枚举到的顺序为 $S_i,S_j,S_k$，则为了让母串的长度相等，求出 $S_i$ 的后缀和 $S_j$ 的前缀的最长相同的长度 $P_1$，$S_j$ 的后缀和 $S_k$ 的前缀的最长相同的长度 $P_2$，那么 $(i,j,k)$ 这个三元组顺序的贡献就是 $\sum\limits_{i=1}^3 |S_i|-P_1-P_2$。

但是也有一些特殊的情况，如 $S_i$ 为 $S_j$ 的子串，那么因为 $S_j$ 中至少包含一个子字符串 $S'$ 满足 $S'=S_i$，所以 $S_i$ 为无用的字符串，需要特判把她去掉。

回到原题。原题的数据范围 $n\le 20$，$20!$ 是一个天文数字，不可能枚举 $20$ 个字符串的全排列。但是发现若在一个母字符串的后面添加一个子字符串，那么这个子字符串的取值一定只和当前最后一个添加进母字符串的字符串有关。所以考虑设 $f_{i,j}$ 表示当前选择了下标在 $i$ 这个集合中的所有字符串进入母串，当前最后一个加入母串的字符串的下标是 $j$，此时母串的长度最小为多少，然后预处理出 $g_{i,j}$ 表示下标为 $i$ 的字符串和下标为 $j$ 的字符串拼接在一起得到的母串的长度最小为多少。这个可以用弱化版的方法用一个**字符串哈希**来在 $O(|S|)$ 的时间复杂度内解决。所以说这一部分的时间复杂度为 $O(n^2\times |S|)$。

然后考虑 $f$ 数组的转移。容易发现初始条件为 $f_{2^i,i}=|S_i|$，答案为 $\min\limits_{i=0}^{n-1} f_{2^n-1,i}$。转移式：$f_{i\operatorname{or} 2^j,j}$ 可以通过 $f_{i,k}+|S_j|-g_{k,j}$ 来转移得到。所以这一个状压 DP 的部分就解决了。这一部分的时间复杂度为 $O(2^n\times n^2)$。

所以总的时间复杂度为 $O(2^n\times n^2)$，在 `5s` 的时间加持下可以解决问题。

---

## 作者：Ac_forever (赞：2)

# 题目大意
给定 $N (1 \leq N \leq 20)$ 个字符串，求出一个最短的字符串，使得这个串包含所有给定的 $N$ 个串。

# solution
由于 $1 \leq N \leq 20$ ，所以考虑状压。

可以先把被其他字符串包含的字符串去除，再预处理出 $p_{i,j}$ 表示字符串 $i$ 的后缀与字符串 $j$ 的前缀的最长相同长度。

设 $f_{i,S}$ 表示已选的字符串的集合为 $S$，最后一个选的字符串是 $i$。那么若要从当前状态 $i$ 转移到新状态 $j$，则必须满足串 $i$ 在集合 $S$ 里，串 $j$ 不在集合 $S$ 里。若满足以上条件，则有转移：

 $$
 f_{j,S|2^{j-1}}=\min(f_{j,S|2^{j-1}},f_{i,S}+len_{j}-p_{i,j})
 $$ 
 
 其中 $len_{i}$ 表示字符串 $i$ 的长度。
 
 初始值全为 $\inf$，$f_{i,2^{i-1}}=len_{i}$。
 
 code:
```cpp
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 22
#define L 400001
using namespace std;
int f[N][1<<N],n,p[N][N],pi[L],len[N],ans=2147483647;
string s[N],ss[N];
bool bz[N];
int pre(string s1,string s2){
	string s=s1+s2;
	int l=s.size();
	pi[0]=0;
	for(int i=1;i<l;i++){
		int j=pi[i-1];
		while(j>0&&s[i]!=s[j])j=pi[j-1];
		if(s[i]==s[j])j++;
		pi[i]=j;
	}
	return pi[l-1];
}
int pre1(string s1,string s2){
	string s=s1+s2;
	int l=s.size();
	pi[0]=0;
	for(int i=1;i<l;i++){
		int j=pi[i-1];
		while(j>0&&s[i]!=s[j])j=pi[j-1];
		if(s[i]==s[j])j++;
		pi[i]=j;
		if(i>=2*s1.size()-1&&pi[i]==s1.size())return s1.size();
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)cin>>ss[i];
	sort(ss+1,ss+n+1);
	n=unique(ss+1,ss+n+1)-ss-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(pre1(ss[j],ss[i])&&i!=j)bz[j]=1;
	int u=0;
	for(int i=1;i<=n;i++)
		if(!bz[i])s[++u]=ss[i];
	n=u;
	for(int i=1;i<=n;i++)len[i]=s[i].size();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				//i:first j:second
				//ji
				string g=s[j]+s[i];
				p[i][j]=pre(s[j],s[i]);
				if(p[i][j]==0)p[i][j]=pre1(s[j],s[i]);
			}
		}
	}
	memset(f,127,sizeof(f))
	for(int i=1;i<=n;i++)f[i][1<<(i-1)]=len[i];
	for(int i=0;i<1<<n;i++)
		for(int j=1;j<=n;j++)
			for(int l=1;l<=n;l++)
				if(j!=l&&(i&(1<<(j-1)))&&(!(i&(1<<(l-1)))))
					f[l][i|(1<<(l-1))]=min(f[j][i]+len[l]-p[j][l],f[l][i|(1<<(l-1))]);
	for(int i=1;i<=n;i++)ans=min(ans,f[i][(1<<n)-1]);
	printf("%d",ans);
}
```

---

## 作者：紊莫 (赞：1)

难蚌，一个唐题写了这么久。

---

首先观察数据，我们可以状态压缩（不熟悉的同学可以参考[我的博客](https://www.luogu.com.cn/article/ytfpke6q)），记录 $S$ 表示当前字符串要接入的情况，由于是拼接，那么我们需要记录上一个位置是谁。

你可能有问题：万一一个字符串要和前面两个去拼接呢？那么我们称这种情况是**包含**。

对于包含的情况，那么短的字符串实际上是不用考虑的，也就是上面的情况一定可以转化为先放个长的，在放个短的来实现。

那么我们对于不能包含的两个字符串，需要**拼接**，这一步使用哈希或者 KMP 即可做到 $O(N^2|S|)$，因为需要两两枚举，不会的同学可以参考 CF25E。

那么转移就很明显了，枚举当前要放的和之前最后放的一个，直接转移即可，注意一个易错点是当现在放了一个包含的字符串后无需改变最后放的那个元素。

[参考代码。](https://atcoder.jp/contests/abc343/submissions/50987711)

---

## 作者：Shunpower (赞：1)

唐，不会写 KMP。

首先我们很容易想到想要让母串包含所有字符串，就要把这些串拼在一起，然而有些部分是可以合并在一起的：

```
leftshun
    shunpower
=> leftshunpower

    shunli
leftshunlili
=> leftshunlili
```

第一种好像不太好搞，所以我们先去掉第二种那种是别人子串的串，可以发现这种串不会影响答案（因为其他串无论怎么拼都肯定会保证自身完整，所以它一直都会能作其他串的子串）。先枚举任意两个字符串 $s_i,s_j$，同时继续枚举其中一个字符串的断点，再使用哈希就可以了。当然也可以直接上 KMP。时间复杂度 $\mathcal O(n\sum|s|)$。

现在我们再考虑第一种合并方式怎么办。

那么有一个显然的结论是如果两个串能拼，就让合并在一起的部分尽量长。这样显然最小化了这一次拼接操作对母串长度的增量，且不影响其他串。

假设我们得到了 $i$ 拼在 $j$ 前面时 $s_i,s_j$ 的最长合并长度 $w_{ij}$，我们考虑对于任意 $i\to j$ 连边，边权为 $w_{ij}$。那么问题转化为，我们需要求一个边权和最大的路径且每个点都经过一次。显然，这个最大值就是在最优拼接方案下可以最多合并掉多长的串，所以用所有有效串（不是其他串子串的串）的总长减掉这个东西就是最终答案。

发现求这个东西等价于求边权最大哈密顿路，设 $f_{S,i}$ 表示目前从点 $i$ 出发，已经走过的点点集为 $S$ 的路径最大边权和，简单转移一下就能直接 $\mathcal O(n^22^n)$ 解决。

现在回到怎么求 $w_{ij}$。这东西可以像我们检验子串那样，枚举 $j$ 的哪个前缀和 $i$ 的后缀匹配上，然后用哈希检验是否相等，然后取最长的那一个就行了。当然也可以用 KMP，我们需要的就是在 $i$ 的最后一个字符处最多匹配上了多少个 $j$ 的字符。

然后就做完了。我场上现写的 KMP 特别丑，状压也写丑了，大家当乐子看看就行：

```cpp
int n;
string s[25];
int lcp[25][25];
bool vis[25],bad[25][25];
int kmp[N],border[25][N];
int calc(int x,int y){
    int j=0;
    fr1(i,1,s[x].length()-1){
        while(j&&s[x][i]!=s[y][j+1]) j=border[y][j];
        if(s[x][i]==s[y][j+1]) j++;
        kmp[i]=j;
    }
    return kmp[s[x].length()-1];
}
int dp[21][(1<<20)];
int main(){
#ifdef Griffin
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    cin>>n;
    fr1(i,1,n) cin>>s[i],s[i]='@'+s[i];
    fr1(i,1,n){
        int k=0;
        fr1(j,2,s[i].length()-1){
            while(k&&s[i][j]!=s[i][k+1]) k=border[i][k];
            if(s[i][j]==s[i][k+1]) k++;
            border[i][j]=k;
        }
    }
    fr1(i,1,n){
        fr1(j,1,n){
            calc(i,j);
            fr1(k,1,s[i].length()-1){
                if(kmp[k]==s[j].length()-1){
                    bad[i][j]=1;
                    break;
                }
            }
        }
    }
    fr1(i,1,n){
        fr1(j,1,n){
            lcp[i][j]=calc(i,j);
        }
    }
    int ans=0;
    fr1(i,1,n) ans+=s[i].length()-1;
    memset(dp,-0x3f,sizeof dp);
    fr1(i,1,n) dp[i][1<<i-1]=0;
    fr1(mask,0,(1<<n)-1){
        fr1(i,1,n){
            fr1(j,1,n){
                if(!((mask>>j-1)&1)){
                    if(bad[i][j]) dp[i][mask|(1<<j-1)]=max(dp[i][mask|(1<<j-1)],dp[i][mask]+(int)s[j].length()-1);
                    dp[j][mask|(1<<j-1)]=max(dp[j][mask|(1<<j-1)],dp[i][mask]+lcp[i][j]);
                }
            }    
        }
    }
    int maxn=0;
    fr1(i,1,n) maxn=max(maxn,dp[i][(1<<n)-1]);
    cout<<ans-maxn<<endl;
    ET;
}
//ETERNAL LOVE FOR Zhang Junhao, Mu Zhicheng and Zuo Hang.
//ALL FOR Zhang Junhao.
```

---

## 作者：Otue (赞：1)

第一次场切 不是数据结构的 G，激动。

找到一个最短串，这个串包含给定的 $n$ 个串。首先可以发现，如果这 $n$ 个串之间有相互包含的两个串，那么那个短串就可以忽略。比如样例 `snuke` 和 `uk`，`uk` 可以完全忽视掉。

去掉包含的情况后，那么这 $n$ 个串就是相交的情况了（相交的长度可以为 $0$）。比如样例 `snuke
  kensho`，其中 `ke` 就是相交的串。

那么最短长度就是：把 $n$ 个串按照任意顺序拼接起来，去掉中间相交的部分后的最短长度。

可以状压 dp，$dp_{i,j}$ 表示当前已经拼接了 $i$ 的集合，最后一个串是串 $j$ 的最短拼接长度。

转移：$dp_{i∪j,k}=\min\{dp_{i,j}+len_k-cost_{j,k}\}$。即枚举串 $k$，将其拼接在串 $j$ 的后面，并且去掉公共部分长度 $cost_{j,k}$。

先预处理 $cost$ 数组，不需要 KMP 和 hash，暴力处理就行，原因自己思考一下。总复杂度 $n^22^n$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 21, M = 2e5 + 5;

int n, dp[1 << N][N], vis[N], cost[N][N], vv[N];
string s[N], t[N];
char a[N][M];
int n2, id[N], dd[N];

int get(int x, int y) {
	int lenx = strlen(a[x] + 1), leny = strlen(a[y] + 1);
	for (int i = leny; i >= 1; i--) {
		int flg = 0;
		for (int j = 1; j <= i; j++) {
			if (lenx - i + j < 0) {
				flg = 1;
				break;
			}
			if (a[y][j] != a[x][lenx - i + j]) {
				flg = 1;
				break;
			}
		}
		if (!flg) return i;
	}
	return 0;
}

bool cmp(int x, int y) {
	return (int)s[x].size() < (int)s[y].size();
}

signed main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> (a[i] + 1);
	for (int i = 0; i < n; i++) {
		int lena = strlen(a[i] + 1);
		for (int j = 1; j <= lena; j++) s[i] += a[i][j];
	}
	for (int i = 0; i < n; i++) dd[i] = i;
	sort(dd, dd + n, cmp);
	for (int i = 0; i < n; i++) {
		int flg = 0;
		for (int j = i + 1; j < n; j++) {
			if (s[dd[j]].find(s[dd[i]]) != string::npos) {
				flg = 1;
				break;
			}
		}
		if (!flg) {
			for (int j = 0; j < s[dd[i]].size(); j++) t[n2].push_back(s[dd[i]][j]);
			id[n2] = dd[i], n2++;
		}
	}
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) if (id[i] != -1 && id[j] != -1 ) cost[i][j] = get(id[i], id[j]);
	}
	memset(dp, 0x3f, sizeof dp);
	for (int i = 0; i < n2; i++) dp[1 << i][i] = t[i].size();
	for (int i = 1; i < (1 << n2); i++) {
		for (int j = 0; j < n2; j++) {
			if (!(i >> j & 1) ) continue;
			for (int k = 0; k < n2; k++) {
				if ((i >> k & 1)) continue;
				dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + (int)t[k].size() - cost[j][k]);
			}
		}
	}
	int res = 2e9;
	for (int i = 0; i < n2; i++) res = min(res, dp[(1 << n2) - 1][i]);
	cout << res << endl;
}
```

---

## 作者：Gaode_Sean (赞：1)

~~原本是围观大佬打 ABC，没想到顺便把 G 题想出来了，可惜没调完~~

考虑先消去一些被其它字符串严格包含的字符串串，注意一些相同的字符串的处理，正确性显然。

由于 $n \le 20$，所以我们考虑状压 dp。

因为剩下的字符串不存在完全包含的情况，所以我们可以直接将一个字符串接到所求字符串的结尾，同时要减去前一个字符串的后缀和当前字符串前缀的最长匹配。

设 $a_{i,j}$ 表示字符串 $i$ 的后缀 和 $j$ 的前缀的最长匹配，这一部分可以用 hash 来完成。

设 $f_{i,j}$ 表示已经被选择的字符串状态为 $i$，结尾的字符串为 $j$。有转移方程：$f_{i,j}=\min(f_{i,j},f_{i-2^j,k}+len_j-a_{k,j})$。

时间复杂度 $\mathcal{O}(2^nn^2)$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N=2e5+5;
int n,ta;
int len[22],f[(1<<20)-1][22],a[22],lcp[22][22],b[N];
ll hsh[22][N],val[N];
char ch[22][N];
map<ll,int> cnt;
bool check(int x,int y)
{
	if(len[x]>len[y]) return false;
    for(int i=1;i<=len[y]-len[x]+1;i++) if(hsh[y][i+len[x]-1]-hsh[y][i-1]*val[len[x]]==hsh[x][len[x]]) return true;
    return false;
}
bool work(int x)
{
	for(int i=1;i<=n;i++) if(x!=i&&check(x,i)) return false;
	return true;
}
bool judge(int x)
{
	for(int i=1;i<=n;i++) if(hsh[i][len[i]]!=hsh[x][len[x]]&&check(x,i)) return false;
	return true;
}
int main()
{
	scanf("%d",&n); val[0]=1;
	for(int i=1;i<N;i++) val[i]=val[i-1]*131;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch[i]+1);
		len[i]=strlen(ch[i]+1); 
		for(int j=1;j<=len[i];j++) hsh[i][j]=hsh[i][j-1]*131+(ll)(ch[i][j]-'a'); 
		b[i]=++cnt[hsh[i][len[i]]];
	}
	for(int i=1;i<=n;i++) if(work(i)) a[++ta]=i;
	for(int i=1;i<=n;i++) if(b[i]==2&&judge(i)) a[++ta]=i;
	for(int i=1;i<=ta;i++)
	{
		for(int j=1;j<=ta;j++)
		{
			if(i==j) continue;
			int x=a[i],y=a[j];
		    for(int l=1;l<=min(len[x],len[y]);l++) if(hsh[y][l]==hsh[x][len[x]]-hsh[x][len[x]-l]*val[l]) lcp[i][j]=l;
		}
	}
	for(int i=1;i<(1<<ta);i++)
	{
		for(int j=0;j<ta;j++)
		{
			f[i][j]=1e9;
			if(i&(1<<j))
			{
				if(i==(1<<j)){f[i][j]=len[a[j+1]];continue;}
				for(int k=0;k<ta;k++) if((i-(1<<j))&(1<<k)&&j!=k) f[i][j]=min(f[i][j],f[i-(1<<j)][k]+len[a[j+1]]-lcp[k+1][j+1]);
			}
		}
	}
	int ans=1e9;
	for(int i=0;i<ta;i++) ans=min(ans,f[(1<<ta)-1][i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

水题，评分能有 $2100$ 可能是因为很多人卡 E 了。

~~我说真的，E 好难啊。~~

$n$ 只有 $20$，考虑从状压的角度入手。定义状态函数 $f_{s,i}$ 表示当某个字符串 $T$ 包含了所有 $s$ 的二进制中为 $1$ 的下标 $S_j$ 且 $T$ 末尾包含的子串为 $S_i$ 时 $T$ 的最小长度。那很显然的就有转移方程：$f_{s+2^{j},j}=\min(f_{s+2^{j}},f_{s,i}+|S_j|-\Delta)$。其中 $\Delta$ 表示 $S_j$ 和 $S_i$ 拼起来时，$S_i$ 的后缀与 $S_j$ 的前缀的最大匹配长度。

有个问题，当 $S_1=aab,S_2=bc,S_3=abc$ 时，上面的 DP 得到的答案是 $7$，即 $T=aabcabc$。但是很显然在 $S_1$ 和 $S_2$ 拼起来之后，$S_3$ 与其的 $\Delta$ 是 $3$。此时的 $S_2$ 已经被 $S_3$ 完全包含了，就相当于是 $S_1$ 和 $S_3$ 拼起来的情况。所以当 $S_i$ 被 $S_j[j \ne i]$ 包含时，$S_i$ 对答案的代价为 $0$（可以不管 $S_i$）。

任意 $S_i,S_j$ 的 $\Delta$ 可以暴力哈希，判断 $S_i$ 是否被 $S_j$ 包含也可以暴力哈希。这两个预处理出来之后跑状压就行了。

复杂度 $O(n^2 2^{n})$，实测删掉被包含的之后飞快。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,string>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=21,M=2e5+10;
int n,m;
string s_[N],s[N];
int f[1<<N][N];
int b[M],c[N][N];
int hs_,hs[N][M],bk=12347;
bool vis[N];

il int get(int now,int l,int r){
	return hs[now][r]-hs[now][l-1]*b[r-l+1];
}
il bool check(int now,string a,int hs_){
	if(s_[now].size()<=a.size()) return 0;
	for(re int l=0;l+a.size()-1<s_[now].size();++l){
		int r=l+a.size()-1;
		if(get(now,l+1,r+1)==hs_) return 1;
	}
	return 0;
}

il void solve(){
	n=rd,b[0]=1;
	for(re int i=1;i<M;++i) b[i]=b[i-1]*bk;
	for(re int i=1;i<=n;++i){
		cin>>s_[i];
		for(re int j=0;j<s_[i].size();++j)
			hs[i][j+1]=hs[i][j]*bk+s_[i][j]-'A'+1;
	}
	for(re int i=1;i<=n;++i){
		hs_=0;
		for(re int j=0;j<s_[i].size();++j)
			hs_=hs_*bk+s_[i][j]-'A'+1;
		for(re int j=1;j<=n;++j)
			if(check(j,s_[i],hs_)){
				vis[i]=1;break;
			}
	}
	for(re int i=1;i<=n;++i)
		if(!vis[i]){
			s[++m]=s_[i];
			for(re int j=0;j<s[m].size();++j)
				hs[m][j+1]=hs[m][j]*bk+s[m][j]-'A'+1;	
		}
	for(re int i=1;i<=m;++i)
	for(re int j=1;j<=m;++j){
		int Mx=0;
		for(re int len=1;len<=min(s[i].size(),s[j].size());++len)
			if(hs[j][len]==get(i,s[i].size()-len+1,s[i].size())) Mx=len;
		c[i][j]=Mx;		
	}
	for(re int i=0;i<(1<<m);++i)
	for(re int j=1;j<=m;++j)
		f[i][j]=1e9;
	for(re int i=1;i<=m;++i) f[1<<(i-1)][i]=s[i].size();
	for(re int i=0;i<(1<<m);++i)
	for(re int lst=1;lst<=m;++lst)
		if((i>>(lst-1))&1)
			for(re int now=1;now<=m;++now){
				if((i>>(now-1))&1) continue;
				f[i+(1<<(now-1))][now]=min(f[i+(1<<now-1)][now],f[i][lst]+s[now].size()-c[lst][now]);
			}
	int ans=1e9;
	for(re int i=1;i<=m;++i) ans=min(ans,f[(1<<m)-1][i]);
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

注：P2322 是这题的输出方案版。

---

## 作者：Unnamed114514 (赞：0)

\* 2114

首先容易想到的是删掉原串的子串。

这一步可以考虑哈希解决。

然后考虑处理拼接的情况，即求最长公共前后缀。

比如我们要求 $t$ 的一个和 $s$ 前缀相等的玩意。

考虑 $t_{\left|t\right|}$ 是否匹配到：

- 没有匹配到，那么答案为 $0$。

- 匹配到了，考虑 $s_i=t_{\left|t\right|}$，那么由于它必须是 $s$ 的前缀，所以只能是 $s_{[1,i]}$ 和 $t_{\left|t\right|-i+1,\left|t\right|}$ 进行匹配，直接用 `hash` 判即可。

最后求答案，考虑状压，$dp_{lst,state}$ 表示的是字符串以 $S_{lst}$ 结尾，状态为 $state$ 的最小长度。

时间复杂度 $O(n^22^n)$。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=2e5+5;
const ull base=131;
int dp[25][1<<20],n,m,w[25][25],len[25],L[25];
ull hsh[25][N],p[N],H[25][N];
string s[25],t[25];
vector<int> vec[25][26];
inline ull get(ull *hsh,int l,int r){ return hsh[r]-hsh[l-1]*p[r-l+1]; }
inline bool check(int i){
	for(int j=1;j<=n;++j){
		if(s[j]==s[i]&&j<=i) continue;
		for(int k=1;k+len[i]-1<=len[j];++k) if(get(hsh[j],k,k+len[i]-1)==hsh[i][len[i]]) return 0;
	}
	return 1;
}
inline int dfs(int lst,int state){
	if(state==(1<<m)-1) return 0;
	if(~dp[lst][state]) return dp[lst][state];
	dp[lst][state]=INT_MAX;
	for(int j=1;j<=m;++j) if(!(state&(1<<j-1))) dp[lst][state]=min(dp[lst][state],dfs(j,state|(1<<j-1))+L[j]-w[lst][j]);
	return dp[lst][state];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	p[0]=1;
	for(int i=1;i<=2e5;++i) p[i]=p[i-1]*base;
	for(int i=1;i<=n;++i){
		cin>>s[i];
		len[i]=s[i].size();
		s[i]=' '+s[i];
		for(int j=1;j<=len[i];++j) hsh[i][j]=hsh[i][j-1]*base+s[i][j];
	}
	for(int i=1;i<=n;++i) if(check(i)){
		t[++m]=s[i];
		L[m]=len[i];
		for(int j=1;j<=len[i];++j) H[m][j]=hsh[i][j];
	}
	for(int i=1;i<=m;++i) for(int j=1;j<=L[i];++j) vec[i][t[i][j]-'a'].push_back(j);
	for(int i=1;i<=m;++i) for(int j=1;j<=m;++j) for(auto x:vec[j][t[i][L[i]]-'a']){
		if(x>L[i]) break;
		if(H[j][x]==get(H[i],L[i]-x+1,L[i])) w[i][j]=x;
	}
	memset(dp,-1,sizeof(dp));
	cout<<dfs(0,0)<<endl;
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc343_g)

# 前置知识

[前缀函数与 KMP 算法](https://oi-wiki.org/string/kmp/) | [状压 DP](https://oi-wiki.org/dp/state/)

# 解法

由于 $\sum\limits_{i=1}^{n} |S_{i}|$ 极大且不需要记录路径，所以 [luogu P2322 [HNOI2006] 最短母串问题](https://www.luogu.com.cn/problem/P2322) 的枚举所有可能的字符串 $T$ 进行判断不可做。

设 $f_{i,j}$ 表示当“字符串包含状态”对应的二进制数为 $i$ 时，且结尾为 $j$ 时的最小长度，状态转移方程为 $f_{i,j}= \min\limits_{j \ne k}^{} \{f_{i-2^{j},k}-g_{k,j}+|S_{j}| \}$，其中 $g_{k,j}$ 表示 $S_{k}$ 的后缀和 $S_{j}$ 的前缀匹配的最长长度，且状态 $i$ 中包含 $j,k$。

$g$ 数组可以用 KMP 维护。

注意去重和删去在其他字符串中已被包含的字符串。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int nxt[200010],f[(1<<22)+10][22],g[22][22];
string s[22],ss[22],t;
int main()
{
	int m,n=0,ans=0x7f7f7f7f,flag,i,j,k,x,y;
	cin>>m;
	memset(f,0x3f,sizeof(f));
	for(i=0;i<=m-1;i++)
	{
		cin>>ss[i];
	}
	sort(ss+0,ss+m);
	m=unique(ss+0,ss+m)-ss;
	for(i=0;i<=m-1;i++)
	{
		flag=0;
		for(j=0;j<=m-1;j++)
		{
			if(i!=j&&ss[j].find(ss[i])!=string::npos)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			s[n]=ss[i];
			n++;
		}
	}
	for(x=0;x<=n-1;x++)
	{
		for(y=0;y<=n-1;y++)
		{
			if(x!=y)
			{
				t=' '+s[y]+'#'+s[x];
				for(i=2,nxt[1]=j=0;i<t.size();i++)
				{
					while(j>=1&&t[i]!=t[j+1])
					{
						j=nxt[j];
					}
					j+=(t[i]==t[j+1]);
					nxt[i]=j;
				}
				g[x][y]=nxt[t.size()-1];
			}
		}
	}
	for(i=0;i<=n-1;i++)
	{
		f[(1<<i)][i]=s[i].size();
	}
	for(i=0;i<=(1<<n)-1;i++)
	{
		for(j=0;j<=n-1;j++)
		{
			if((i>>j)&1)
			{
				for(k=0;k<=n-1;k++)
				{
					if(j!=k&&((i>>k)&1))
					{
						f[i][j]=min(f[i][j],f[i-(1<<j)][k]-g[k][j]+(int)s[j].size());
					}
				}
			}
		}
	}
	for(i=0;i<=n-1;i++)
	{
		ans=min(ans,f[(1<<n)-1][i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

# 后记

多倍经验：[CF25E Test](https://www.luogu.com.cn/problem/CF25E)

---

## 作者：happybob (赞：0)

唐题。

考虑瞎状压，$f_{i,S}$ 表示末尾的字符串是 $s_i$，目前 $S$ 这个二进制状态为 $1$ 的位置已经是子串了。转移直接枚举上一个位置哈希。注意要把本身就在另一个字符串的子串中的删掉并去重。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

using ll = long long;

const int N = 22, MOD = 1e9 + 9, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, m, q, t, a[N];
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

long long qpow(long long a, long long b)
{
	long long res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

bool isprime(int x)
{
	if (x == 1) return 0;
	for (int i = 2; 1ll * i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

template<typename T>
class Bit
{
public:
	T lowbit(T x)
	{
		return x & -x;
	}
	T tr[N];
	void add(T x, T y)
	{
		while (x < N)
		{
			tr[x] += y;
			x += lowbit(x);
		}
	}
	T query(T x)
	{
		T sum = 0;
		while (x)
		{
			sum += tr[x];
			x -= lowbit(x);
		}
		return sum;
	}
};

int f[N][1<<21];
string s[N];

struct Two_Hash
{
	long long hs1,hs2;
	Two_Hash()=default;
	Two_Hash(long long h1,long long h2):hs1(h1),hs2(h2){}
	Two_Hash operator+(const Two_Hash x)
	{
		return Two_Hash((hs1+x.hs1)%MOD,(hs2+x.hs2)%HSMOD);
	}
	Two_Hash operator-(const Two_Hash x)
	{
		return Two_Hash((hs1-x.hs1+MOD)%MOD,(hs2-x.hs2+HSMOD)%HSMOD);
	}
	Two_Hash operator-(const long long x)
	{
		return Two_Hash((hs1-x+MOD)%MOD,(hs2-x+HSMOD)%HSMOD);
	}
	Two_Hash operator+(long long x)
	{
		return Two_Hash((hs1+x)%MOD,(hs2+x)%HSMOD);
	}
	Two_Hash operator*(const Two_Hash x)
	{
		return Two_Hash((hs1*x.hs1)%MOD,(hs2*x.hs2)%HSMOD);
	}
	Two_Hash operator*(const long long x)
	{
		return Two_Hash((hs1*x)%MOD,(hs2*x)%HSMOD);
	}
	bool operator==(const Two_Hash x)
	{
		return (hs1==x.hs1&&hs2==x.hs2);
	}
}; 

const int M=5e5+5;

Two_Hash powe[M];

vector<Two_Hash> v1[N],v2[N];
int ans[N][N];

int getres(int x,int y)
{
	int cnt=0;
	for(int i=0;i<min(s[x].size(),s[y].size());i++)
	{
		if(v1[y][i]==v2[x][i]) cnt=i+1;
	}
	for(int i=0;i+s[y].size()-1<s[x].size();i++)
	{
		Two_Hash rr=v1[x][i+s[y].size()-1]-(i?v1[x][i-1]:Two_Hash(0,0))*powe[s[y].size()];
		//cout<<"!!!!!: " <<rr.hs1<<" "<<rr.hs2<<"\n";
		if(rr==v1[y][s[y].size()-1])
		{
			cnt=s[y].size();
		} 
	}
	return cnt;
}

vector<string> vecs;

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	memset(f,0x3f,sizeof f);
	cin>>n;
	f[0][0]=0;
	powe[0]=Two_Hash(1,1);
	for(int i=1;i<M;i++) powe[i]=powe[i-1]*26;
	set<string> ss;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		ss.insert(s[i]);
	}
	sort(s+1,s+n+1);
	n=unique(s+1,s+n+1)-s;
	if(ss.size()==1)
	{
		cout<<s[1].size()<<"\n";
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		v1[i].clear(),v2[i].clear();
		auto g=Two_Hash(0,0);
		for(auto&j:s[i])
		{
			g=g*26+(j-'a'+1);
			v1[i].emplace_back(g);
		}
		reverse(s[i].begin(),s[i].end());
		g=Two_Hash(0,0);
		Two_Hash nw=Two_Hash(1ll,1ll);
		for(auto&j:s[i])
		{
			g=Two_Hash(j-'a'+1,j-'a'+1)*nw+g;
			nw=nw*26;
			v2[i].emplace_back(g);
		}
		reverse(s[i].begin(),s[i].end());
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) ans[i][j]=getres(i,j);
	}
	for(int i=1;i<=n;i++)
	{
		bool f=1;
		for(int j=1;j<=n;j++) 
		{
			if(ans[j][i]==s[i].size()&&i!=j)
			{
				f=0;
			} 
		}
		if(f) vecs.emplace_back(s[i]);
	}
	n=vecs.size();
	for(int i=1;i<=n;i++) 
	{
		v1[i].clear(),v2[i].clear();
		s[i]=vecs[i-1];
		auto g=Two_Hash(0,0);
		for(auto&j:s[i])
		{
			g=g*26+(j-'a'+1);
			v1[i].emplace_back(g);
		}
		reverse(s[i].begin(),s[i].end());
		g=Two_Hash(0,0);
		Two_Hash nw=Two_Hash(1ll,1ll);
		for(auto&j:s[i])
		{
			g=Two_Hash(j-'a'+1,j-'a'+1)*nw+g;
			nw=nw*26;
			v2[i].emplace_back(g);
		}
		reverse(s[i].begin(),s[i].end());
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) ans[i][j]=getres(i,j);
	}
	for(int j=1;j<(1<<n);j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(!((j>>(i-1))&1)) continue;
			if(__builtin_popcount(j)==1)
			{
				f[i][j]=s[i].size();
			}
			else
			{
				for(int k=1;k<=n;k++)
				{
					if(k==i||((!((j>>(k-1))&1)))) continue;
					f[i][j]=min(f[i][j],f[k][j-(1<<(i-1))]+(int)s[i].size()-ans[k][i]);
				}
			}
			//cout<<"???????: "<<f[2][1]<<"\n";
		}
	}
	int ans=(int)1e9;
	for(int i=1;i<=n;i++) ans=min(ans,f[i][(1<<n)-1]);
	cout<<ans<<"\n";
	return 0;
}



```

---

## 作者：DerrickLo (赞：0)

我们先将所有被其他串所包含的串删除，注意多个相同的串需要保留一个。

然后预处理出对于每两个串 $s_i$ 与 $s_j$，$s_i$ 放在前面和 $s_j$ 放在后面所能构成的最大重合部分 $a_{i,j}$，这可以使用哈希解决。

然后考虑状压。设 $f_{S,i}$ 表示由集合 $S$ 中的串拼起来，且最后一个串是 $s_i$ 的长度的最小值，那么：

$$f_{S,i}=\min_{j\in S}f_{S\backslash\{j\},j}+|s_i|-a_{j,i}$$

初始化 $f_{\{i\},i}=|s_i|$，复杂度 $O(2^n\times n)$。

```cpp
#include<bits/stdc++.h>
#define base 366171
#define int long long
using namespace std;
int n,ans[25][25],dp[2000005][25],anss=1e18,vis[25],mm;
unsigned long long pw[200005];
string s[200005],t[200005];
map<unsigned long long,vector<int>>mp;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,pw[0]=1,mm=n;
	for(int i=1;i<=200000;i++)pw[i]=pw[i-1]*base;
	for(int i=1;i<=n;i++)cin>>t[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j){
		if(t[i].find(t[j])!=-1&&(t[i]!=t[j]||!vis[i]))vis[j]=1;
	}
	n=0;
	for(int i=1;i<=mm;i++)if(!vis[i])s[++n]=t[i];
	for(int i=1;i<=n;i++){
		unsigned long long hs=0;
		for(int j=0;j<s[i].size();j++){
			hs=hs*base+s[i][j]-'0';
			mp[hs].emplace_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		unsigned long long hs=0;
		for(int j=0;j<s[i].size();j++){
			hs=hs*base+s[i][j]-'0';
			mp[hs].erase(find(mp[hs].begin(),mp[hs].end(),i));
		}
		hs=0;
		for(int j=s[i].size()-1;~j;j--){
			hs=hs+(s[i][j]-'0')*pw[s[i].size()-j-1];
			for(int v:mp[hs]){
				ans[i][v]=max(ans[i][v],(int)s[i].size()-j);
			}
		}
		hs=0;
		for(int j=0;j<s[i].size();j++){
			hs=hs*base+s[i][j]-'0';
			mp[hs].emplace_back(i);
		}
	}
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++)dp[(1<<(i-1))][i]=s[i].size(); 
	for(int S=1;S<(1<<n);S++){
		for(int i=1;i<=n;i++)if(S&(1<<(i-1)))for(int j=1;j<=n;j++)if(j!=i&&(S&(1<<(j-1)))){
			dp[S][i]=min(dp[S][i],dp[S^(1<<(i-1))][j]+(int)s[i].size()-ans[j][i]);
		}
	}
	for(int i=1;i<=n;i++)anss=min(anss,dp[(1<<n)-1][i]);
	cout<<anss;
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

发现 $n \leq 20$，所以考虑状压 dp。定义 $f_{u,s}$ 表示选择的最后一项为 $u$，已选的集合为 $s$ 时的最小长度。

不难得到状态转移方程：

```
int p=S|(1<<i),len=strlen(s[i]+1); 
for(int j=0;j<n;j++) if(i!=j&&(S>>j&1)) f[p][i]=min(f[p][i],f[S][j]+len-w[j][i]); 
```

其中 $w_{i,j}$ 表示字符串 $i$ 和 $j$ 重合的长度。

但是此时会有一个问题，字符串 $A$ 在字符串 $B$ 中出现过，但如果首尾不匹配，答案就会算重。

所以考虑利用字符串哈希对原字符串去重并预处理出 $w_{i,j}$ 即可。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=20,M=2e5+10; 
const int Tim=133,Mod=1e9+7; 
int n; 
int mp[N]; 
int w[N][N]; 
int Base[M]; 
int hs[N][M]; 
int f[1<<N][N]; 
char s[N][M],t[N][M]; 
il int calc(int i,int l,int r){ 
	return ((hs[i][r]-hs[i][l-1]*Base[r-l+1]%Mod)%Mod+Mod)%Mod; 
} 
signed main(){ 
	Base[0]=1; 
	int num=read(); 
	memset(f,0x3f,sizeof f); 
	for(int i=1;i<M;i++) Base[i]=Base[i-1]*Tim%Mod; 
	for(int i=0;i<num;i++){ 
		cin>>t[i]+1; 
		int len=strlen(t[i]+1); 
		for(int j=1;j<=len;j++) hs[i][j]=(hs[i][j-1]*Tim%Mod+(t[i][j]-'a'))%Mod; 
	} for(int i=0;i<num;i++){ 
		bool flg=true; 
		for(int j=0;j<num;j++){ 
			int l1=strlen(t[i]+1),l2=strlen(t[j]+1); 
			if(i==j||l1>=l2) continue; 
			for(int k=l1;k<=l2;k++){ 
				int w=calc(j,k-l1+1,k); 
				if(w==hs[i][l1]){ flg=false; break; } 
			} if(!flg) break; 
		} if(flg){ 
			int len=strlen(t[i]+1); 
			for(int k=0;k<=len;k++) s[n][k]=t[i][k]; 
			f[1<<n][n]=len; mp[n++]=i; 
		} 
	} for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i==j) continue; 
			int l1=strlen(s[i]+1),l2=strlen(s[j]+1);  
			for(int k=1;k<=min(l1,l2);k++){ 
				int w1=calc(mp[i],l1-k+1,l1),w2=calc(mp[j],1,k); 
				if(w1==w2) w[i][j]=k; 
			} 
		} 
	} for(int S=0;S<1<<n;S++){ 
		for(int i=0;i<n;i++){ 
			if(S>>i&1) continue; 
			int p=S|(1<<i),len=strlen(s[i]+1); 
			for(int j=0;j<n;j++) if(i!=j&&(S>>j&1)) f[p][i]=min(f[p][i],f[S][j]+len-w[j][i]); 
		} 
	} int ans=1e18+7; 
	for(int i=0;i<n;i++) ans=min(ans,f[(1<<n)-1][i]); 
	printf("%lld\n",ans); 
	return 0; 
} 
```

---

