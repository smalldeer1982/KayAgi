# [ARC155A] ST and TS  Palindrome

## 题目描述

给定一个由小写英文字母组成、长度为 $N$ 的字符串 $S$，以及一个正整数 $K$。

请判断是否存在一个长度为 $K$ 的字符串 $S'$，使得以下条件都成立：

- 将 $S$ 和 $S'$ 按顺序连接得到的字符串是回文串。
- 将 $S'$ 和 $S$ 按顺序连接得到的字符串是回文串。

有 $T$ 组测试数据，请分别判断每组数据。

## 说明/提示

### 限制

- $1 \leq T \leq 10^5$
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq K \leq 10^{18}$
- $S$ 是由小写英文字母组成的长度为 $N$ 的字符串
- 输入的所有数值均为整数
- 所有测试数据中 $N$ 的总和不超过 $2 \times 10^5$

### 样例解释 1

对于第 $1$ 组测试数据，例如取 $S' = $`ba`，则 $S,S'$ 按顺序连接得到的字符串 `abbaabba` 是回文串。同时，$S',S$ 按顺序连接得到的字符串 `baabbaab` 也是回文串。因此 $S' = $`ba` 满足条件，答案为 `Yes`。对于第 $2$ 组测试数据，可以证明不存在满足条件的 $S'$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
6 2
abbaab
5 3
abcbb```

### 输出

```
Yes
No```

## 样例 #2

### 输入

```
3
12 400378271514996652
njvhhvjnnjvh
10 884633988115575508
rrhiyvrrur
36 71630165869626180
vsxmxajrrduhhudrrjaxmxsvvsxmxajrrduh```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：aiquaerjie (赞：5)

## Complaint

什么神笔人类智慧场，不理解捏，应该是有史以来最难 ARC T1 吧。不过这个题本质不难，就是分讨多了点，可能对小朋友不友好。~~毕竟我只不过是吃了八发罚时而已捏~~。

## Solution

题目很清晰，看标题就知道了。就是要找一个串 $T$，使得拼在串 $S$ 前面或者后面都是回文。

首先考虑 $S$ 串本身就是回文的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/irygb72s.png)

如上图，因为拼接起来要求是回文，所以 $T$ 串的最前面和后面都是反的 $S$ 串，又因为 $S$ 串是回文，所以这就是 $S$ 串本身。也就是 $S$ 串本身。很显然 $T$ 串是 $S$ 串的两倍。以此类推，可以自己试着画一下，要满足题目条件当且仅当 $T$ 是 $S$ 串的倍数。

从这个结论就可以很自然地推出任意一个 $S$ 串的**完整**循环节如果是回文，那么只要 $T$ 串的长度是这个子串的倍数就是可行的。直接 KMP 找循环节枚举即可。

但是酱紫我们样例一都过不去。我们来看看这是个什么神奇的东西。

`abbaab`

这是什么呢？我们可以发现，这个串是由 `ab`、反的 `ab` 和 `ab` 组成的，而最后 $T$ 串是反的 `ab`。我们来画一下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/edr08tbr.png)

十分显然，找到一个这样子的“伪循环节” $U$ 串也可以找到适合的 $T$ 串。不过自己画画图可以试试，如果最后 $S$ 串和 $T$ 串拼起来分割成奇数个 $U$ 串是不可行的，所以要判断 $S$ 和 $T$ 的长度和是否是 $U$ 串的偶数倍。

我们可以找到一个不完整的偶数长度的回文循环节，这个循环节的一半就是 $U$ 串，所以同样可以用 KMP 的 `ne` 数组不断跳来解决。那么最后这个题就做完了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
char s[NN];
int ne[NN];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		long long k;
		scanf("%d%lld%s",&n,&k,s+1);
		ne[0]=-1;
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1])
				j=ne[j];
			if(s[i]==s[j+1])
				j++;
			ne[i]=j;
		}
		bool ok=false;
		for(int i=ne[n];~i;i=ne[i])
		{
			int x=n-i;
			if(!(x%2))
			{
				x/=2;
				if(n%x||k%x||(k+n)/x%2)
					continue;
				bool flag=true;
				for(int j=1;j<=x;j++)
					if(s[j]!=s[x*2-j+1])
					{
						flag=false;
						break;
					}
				if(flag)
				{
					ok=true;
					break;
				}
			}
			else
			{
				if(n%x||k%x)
					continue;
				bool flag=true;
				for(int j=1;j<=x;j++)
					if(s[j]!=s[x-j+1])
					{
						flag=false;
						break;
					}
				if(flag)
				{
					ok=true;
					break;
				}
			}
		}
		puts(ok||!(k%n)&&!((k+n)/n%2)?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：Rushroom (赞：4)

# 题意

给定长度为 $n$ 的字符串 $S$ 和一个数 $k$，问是否存在一个长度为 $k$ 的字符串 $T$ 满足字符串 $S+T$ 和 $T+S$ 都是回文串。
$n \le 2\cdot 10^5,k \le 10^{18}$

# 题解

设 $S$ 倒转后得到 $S'$。

考虑如果 $k>2n$，那么  $S'$ 必定是 $T$ 的前缀和后缀，设 $T=S'+t+S'$。

所以可以得到 $S+S'+t+S'$ 和 $S'+t+S'+S$ 都是回文串，进而得到 $S'+t$ 和 $t+S'$ 都是回文串。

简单分析可知，“$S'+t$ 和 $t+S'$ 都是回文串”与“ $S+t$ 和 $t+S$ 都是回文串”是等价的，所以整个转化过程就相当于把 $k$  缩小了 $2n$。

这样一直转化下去，最后相当于把 $k$ 模上 $2n$。

之后分成 $k=0,1\le k \le n$ 和 $n+1\le j \le 2n-1$ 讨论，具体过程比较简单，这里就不赘述了。

# Code

```cpp
ll n, k;
string s, t;
bool ans;
bool check(string st) {
    rep(i, st.size())if (st[i] != st[st.size() - 1 - i])return 0;
    return 1;
}
void solve() {
    cin >> n >> k >> s;
    k %= 2 * n;
    if (!k)ans = check(s);
    else if (k <= n) {
        t = s.substr(0, k);
        reverse(t.begin(), t.end());
        ans = check(s + t) & check(t + s);
    }
    else {
        t = "";
        rep(i, k)t += '1';
        rep(i, n)t[i] = s[n - 1 - i];
        ans = 1;
        rep(i, n) {
            if (t[k - 1 - i] != '1' && t[k - 1 - i] != s[i])ans = 0;
            t[k - 1 - i] = s[i];
        }
        if (ans)ans = check(s + t) & check(t + s);
    }
    if (ans)cout << "Yes\n";
    else cout << "No\n";
}
```


---

## 作者：Register_int (赞：3)

赛时调到心态爆炸的题，这里提供我赛时的大力做法。

设 $S'$ 为 $S$ 的反串。首先可以发现，将该串分解为 $S+S'+S+S'+\cdots$ 的形式后，答案串一定也为 $S+S'+S+S'+\cdots$ 的形式。枚举原串分为几段，复杂度 $O(n\sqrt n)$。

没了？还有一堆。我们还需要对 $S$ 是否是回文串的情况分讨。

- $S$ 为回文串。此时 $S=S'$，只要 $|S|\mid k$ 则可以构造，具体方案为 $S+S+S+\cdots+S$。
- $S$ 不为回文串。此时 $S\not =S'$，因此分割后前缀与后缀必须相等，也就是 $S+S'+\cdots+S'+S$，即 $\dfrac n{|S|}$ 为奇数。并且，$T$ 串也要为这种形式，所以需要 $|S|\mid k$ 且 $\dfrac k{|S|}$ 为奇数才可以构造，具体方案为 $S+S'+\cdots+S'+S$。

那么就做完了。~~这场 ARC 难度是要起飞？~~

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int t, n, ans; ll k;
 
char s[MAXN];
 
inline 
bool check(int x) {
	int y = n / x, f = 1;
	if (k % y) return 0;
	for (int i = 1; i < x; i++) {
		for (int j = 1, k = y << 1; j <= y; j++, k--) {
			if (s[(i - 1) * y + j] != s[(i - 1) * y + k]) return 0;
		}
	}
	for (int i = 1; i <= y; i++) if (s[i] != s[y - i + 1]) f = 0;
	return f || x & 1 && (k / y & 1);
}
 
int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d%lld%s", &n, &k, s + 1), ans = 0;
		for (int i = 1; i <= n; i++) if (n % i == 0 && check(i)) { ans = 1; break; }
		puts(ans ? "Yes" : "No");
	}
}
```

---

## 作者：golden_brick (赞：2)

# arc155A

**题目传送门：**

[ATC](https://atcoder.jp/contests/arc155/tasks/arc155_a) [lg](https://www.luogu.com.cn/problem/AT_arc155_a)

**题意：**

给你一个长度为 $n$ 的字符串 $s$，问你是否存在一个长度为 $k$ 的字符串 $s'$ 使得 $s + s'$ 和 $s' + s$  都是回文串。

**solution：**

我们分讨一下。

1. $k < n$

   对于这种情况我们发现只需 $s$ 的后 $n - k$ 个字符与前 $n - k$ 个字符都是回文串且前 $k$ 个字符与后 $k$ 个字符相等即可。

2. $\left \lfloor \dfrac{k}{n} \right\rfloor \bmod 2 = 0$

   我们只需要在两端各加上一些正着或倒着的 $s$，那最后就变成了 $k$ 为 $k \bmod n$ 时的情况 $1$ 了。

3. $\left \lfloor \dfrac{k}{n} \right\rfloor \bmod 2 = 1$

   同样我们在一端各加上一个倒着的 $s$，就变成了 $s$ 为 $s + \text{倒着的}s$，$k$ 为 $k - n$ 时的情况 $2$ 了。

**code:**  时间复杂度 $\mathcal{O}(n)$

```cpp
#include <bits/stdc++.h>
#define int ll
#define endl '\n'
#define il inline
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
string s;
int n, k;
il bool hw(string s) // 判回文
{
    for (int i = 0; i < s.size(); i++)
        if (s[i] != s[s.size() - i - 1])
            return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> k >> s;
        if ((k / n) & 1) // 情况三
        {
            k -= n;
            string t;
            for (int i = 0; i < s.size(); i++)
                t += s[s.size() - i - 1];
            s = t + s, n *= 2;
        }
        k %= n; // 情况二
        if (s.substr(0, k) == s.substr(n - k, k)) // 情况一
            cout << (hw(s.substr(k, n - k)) && hw(s.substr(0, n - k)) ? "Yes" : "No") << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
```



---

## 作者：Leasier (赞：1)

设 $T_1 = SS'$，$T_2 = S'S$。若 $k$ 足够大，则：

- $T_1[|T_1| - n + 1, |T_1|] = T_2[1, n] = rev(S)$，也即 $S'[|S'_1| - n + 1, |S'_1|] = S'[1, n] = rev(S)$。
- $S'[|S'_1| - 2n + 1, |S'_1| - n] = S'[n + 1, 2n] = S$。
- ……
- $S'[|S'_1| - (2t + 1)n + 1, |S'_1| - 2tn] = S'[2tn + 1, (2t + 1)n] = rev(S)$。
- $S'[|S'_1| - 2tn + 1, |S'_1| - (2t - 1)n] = S'[(2t - 1)n + 1, 2tn] = S$。

这里我们可以得到若干 $S, S$ 之间和 $S, S'$ 之间（因为 $k$ 不一定是 $2n$ 的倍数）的相等关系，且无论从前还是从后开始看均有循环节 $2n$。

用 map 维护一下相等关系是否矛盾即可。时间复杂度为 $O(\sum n \log n)$。

细节可能稍多，可以参考一下代码。

代码：
```cpp
#include <iostream>
#include <map>

using namespace std;

typedef long long ll;

typedef struct {
	map<ll, char> mp;
	
	inline bool assign(ll x, char ch){
		if (mp.count(x)) return mp[x] == ch;
		mp[x] = ch;
		return true;
	}
} Node;

Node x, y, z;
char s[200007];

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n;
		ll k;
		bool ans = true;
		cin >> n >> k;
		cin >> &s[1];
		x.mp.clear();
		y.mp.clear();
		z.mp.clear();
		for (int j = 1; j <= n; j++){
			ll t = n + k - j + 1;
			ans &= x.assign(j, s[j]);
			if (t <= n){
				ans &= x.assign(t, s[j]);
			} else {
				ans &= y.assign(t - n, s[j]);
			}
		}
		for (ll j = k + 1; j <= k + n; j++){
			ll t = n + k - j + 1;
			if (t <= k){
				ans &= y.assign(t, s[j - k]);
			} else {
				ans &= x.assign(t - k, s[j - k]);
			}
		}
		for (map<ll, char>::iterator j = y.mp.begin(); j != y.mp.end(); j++){
			ll t = n + k - j->first + 1;
			ans &= z.assign(j->first % (n * 2), j->second);
			if (0 <= t && t <= k) ans &= y.assign(t, j->second);
		}
		for (map<ll, char>::iterator j = z.mp.begin(); j != z.mp.end(); j++){
			ans &= z.assign((n + k - j->first + 1) % (n * 2), j->second);
		}
		if (ans){
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

## 前言

神经题目，第一眼以为是简单模拟，直到我看见了 $K \le 10^{18}$。

## 分析

由于本题的 $K$ 范围极大，所以必然不可能真的找出 $S'$。

$K$ 与 $N$ 接近或小于时可以直接暴力解决；对于 $K$ 远大于 $N$ 的情况，我们可以模拟一下填写 $S'$ 的过程。

（红色表示 $S$，绿色表示 $S'$ 中的正向 $S$ 子串，黄色表示 $S'$ 中的反向 $S$ 子串）

$$
S+S': \texttt{[\textcolor{red}{\underline{hello}}-------------------------------------------]}\\
S'+S: \texttt{[-------------------------------------------\textcolor{red}{hello}]}
$$

先把上面划线部分回文起来，再与下面的同步：

$$
S+S': \texttt{\textcolor{red}{hello}--------------------------------------\textcolor{yellow}{olleh}}\\
S'+S: \texttt{--------------------------------------\textcolor{yellow}{olleh}\textcolor{red}{\underline{hello}}}
$$

再把下面的划线部分也回文一次，与上面的同步：

$$
S+S': \texttt{\textcolor{red}{hello}[\textcolor{yellow}{\underline{olleh}}---------------------------------]\textcolor{yellow}{olleh}}\\
S'+S: \texttt{\textcolor{yellow}{olleh}[---------------------------------\textcolor{yellow}{olleh}]\textcolor{red}{hello}}
$$

此时可以发现，这好像形成了一个子问题：**“$\texttt{[ ]}$” 框起来的部分中，那一段表示还未填写的“$\texttt{--...--}$”（假设为 $S'''$）和 $S$ 的反向字符串（假设为 $S^*$）组成了一个与原问题等价的问题。**

> **证明**：设 $f(x) \in \{\operatorname{True}, \operatorname{False}\}$ 表示 $x$ 是否是回文字符串。
>
> $
> f(S + S') = f(S + S'' +S^*) = f(S + S^* + S''' + S^*) \\
> f(S' + S) = f(S'' + S^* + S) = f(S^* + S''' + S^* + S)
> $
>
> 在回文中，左右两侧的 $S$ 和 $S^*$ 可以互相抵消，所以：
>
> $
> f(\cancel{S} + S^* + S''' + \cancel{S^*}) = f(S^* + S''') \\
> f(\cancel{S^*} + S''' + S^* + \cancel{S}) = f(S''' + S^*)
> $
>
> 将结果式子与起始式子相比较，可以发现把 $S$ 变成 $S^*$，$S'$ 变成 $S'''$，**解不变**。
>
> 因为我们每次的填写都是**唯一合法解**（填写的必须和已知的构成回文），所以这样做是一定正确的。

即，每步：
+ $S' \leftarrow S'''$
+ $S \leftarrow S^*$

再连续走两步也是一样：

$$
S+S': \texttt{\textcolor{red}{hello}\textcolor{yellow}{olleh}[\textcolor{green}{hello}-----------------------]\textcolor{green}{hello}\textcolor{yellow}{olleh}}\\
S'+S: \texttt{\textcolor{yellow}{olleh}\textcolor{green}{hello}[-----------------------\textcolor{green}{hello}]\textcolor{yellow}{olleh}\textcolor{red}{hello}}
$$

这样可以一直走到无法再填：

$$
S+S': \texttt{\textcolor{red}{hello}\textcolor{yellow}{olleh}\textcolor{green}{hello}[\textcolor{yellow}{olleh}-------------]\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}}\\
S'+S: \texttt{\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}[-------------\textcolor{yellow}{olleh}]\textcolor{green}{hello}\textcolor{yellow}{olleh}\textcolor{red}{hello}}
$$

$$
S+S': \texttt{\textcolor{red}{hello}\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}[\textcolor{green}{hello}---]\textcolor{green}{hello}\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}}\\
S'+S: \texttt{\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}\textcolor{green}{hello}[---\textcolor{green}{hello}]\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}\textcolor{red}{hello}}
$$

## 代码

根据我们刚才获得的递归式：
+ $S' \leftarrow S'''$（长度减少 $2n$）
+ $S \leftarrow S^*$（反转）

可以写出一个简单的伪代码：

```pseudo_code
function check(k)
{
	if k > 2 * n:
		reverse(s)
		return check(k - 2 * n)
	else:
		暴力处理
}
```

但这个递归的复杂度是错的，所以简单优化一下：发现最终 $k$ 值应当是 $k \bmod 2n$；而 $S$ 的反转次数即为 $\left\lfloor\frac{k}{2n}\right\rfloor$，根据奇偶判断是否反转即可。

> 实际上无论如何都不反转也是对的，变换一下视角，把
>
> $$
> S+S': \texttt{\textcolor{red}{hello}\textcolor{yellow}{olleh}\textcolor{green}{hello}[\textcolor{yellow}{olleh}-------------]\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}}\\
> S'+S: \texttt{\textcolor{yellow}{olleh}\textcolor{green}{hello}\textcolor{yellow}{olleh}[-------------\textcolor{yellow}{olleh}]\textcolor{green}{hello}\textcolor{yellow}{olleh}\textcolor{red}{hello}}
> $$
> 
> 的子问题抠出来：
>
> $$
> S+S': \texttt{[\textcolor{yellow}{olleh}-------------]}\\
> S'+S: \texttt{[-------------\textcolor{yellow}{olleh}]}
> $$
>
> 再整体左右反转一下，接着上下交换：
>
> $$
> S+S': \texttt{[\textcolor{green}{hello}-------------]}\\
> S'+S: \texttt{[-------------\textcolor{green}{hello}]}
> $$
>
> 然后就发现**无论什么情况都可以转化成不反转的情况**，反转这一步就可以省略了。

然后最后的暴力处理部分，先根据一组回文要求填写 $S'$，再根据另一组填写还空着的部分。最后检验一下 $S+S'$ 和 $S'+S$ 是否都是回文就行。

时间复杂度 $O(N)$，[AC 记录](https://atcoder.jp/contests/arc155/submissions/66493432)。

```cpp
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;
int n; string s, t;

bool is_palin (const string &tmp)
{
	for (int i = 0; i < (int)tmp.length(); i++)
		if (tmp[i] != tmp[tmp.length() - i - 1]) return false;
	return true;
}

bool check(long long m)
{
	if ((m / (n << 1)) & 1)
		reverse(s.begin(), s.end()); //这个判断反转可以省略
	m %= (n << 1);

	//以下为暴力部分
	if (m <= n)
	{
		t.clear(), t.resize(m);
		for (int i = 0; i < m; i++)
			t[i] = s[m - i - 1];
	}
	else
	{
		t.clear(), t.resize(m);
		for (int i = 0; i < n; i++)
			t[m - i - 1] = s[i];
		for (int i = 0; i < m - n; i++)
			t[i] = s[n - i - 1];
	}
	return is_palin(s + t) && is_palin(t + s);
};

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		long long m;
		scanf("%d%lld", &n, &m);
		cin >> s;
		printf("%s\n", check(m) ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：ljlawa (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/AT_arc155_a)

题目非常清晰，给定长度为 $n$ 的字符串 $S$，试构造长度为 $k$ 的字符串 $T$，使得 $ST$ 和 $TS$ 都为回文串。

第一眼我将问题分成了两类，$k \ge n$ 和 $k < n$（后来发现其实不用分类，只是 $k \ge n$ 比较好想罢了）。

图为 $k \ge n$ 的一种简单情况。（如图）

![](https://cdn.luogu.com.cn/upload/image_hosting/1mnn4ueh.png)

再根据样例（手推几组）可以推出，我们最后的 $ST$ 是形如 $ss'ss'ss'\cdots$（$s$ 和 $s'$ 交替出现且一共出现了偶数次，这里的 $s$ 不同于上图）的，$s$ 为 $S$ 的子序列，$s'$ 为翻转的 $s$。

解法：

枚举 $s$ 长度，使其满足条件，注意有特殊情况 $s$ 本身就是回文串，那这样也是可以满足的。


```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 5;

int t;
long long n, k;
string s, a, b;

bool check (string s) { return (s == string(s.rbegin(), s.rend())); /* 判回文 */}

void solve ()
{
	cin >> n >> k >> s;
	for (int i = 1; i <= n; i ++)
	{
		if (n % i == 0)
		{
			a = s.substr(0, i);
			bool flag = 1;
			for (int j = 0; j < n; j += i)
			{
				b = s.substr(j, i);
				if (j / i % 2 == 1) reverse(b.begin(), b.end()); // 翻转
				if (b != a) flag = 0;
			}
			if (flag && k % i == 0 && (check(a) || (n + k) / i % 2ll == 0))
			{
				cout << "Yes" << endl;
				return ; 
			}
		}
	}
	cout << "No" << endl;
}

int main()
{
	scanf ("%d", &t);
	while (t --) solve ();
	return 0;
}
```

---

## 作者：CReatiQ (赞：0)

考虑 $SS'$ 与 $S'S$ 之间的关系。

不妨用 `1 2 3 4 5` 表示 $k=5$ 的 $S$，用 `6 7 8` 表示 $k=3$ 的 $S'$，可以得到：

$SS'=$ `1 2 3 4 5 6 7 8 `；

$S'S=$ `6 7 8 1 2 3 4 5 `。

根据两者的回文约束，可以得到：

$1=8,2=7,3=6,4=5$；

$6=5,7=4,8=3,1=2$。

对于第一行 $a=b$，第二行 $b=c$，我们将 $a,c$ 连边。

对于第二行 $a=b$，第一行 $b=c$，我们同样将 $a,c$ 连边。

例如上面的例子中，我们会对 $\{1,3\},\{2,4\},\{3,5\},\{4,6\},\{5,7\},\{6,8\}$ 连边。

手玩一下可以得到 $i$ 总与 $i+2 \gcd(n,k)$ 连边。

所以 $2 \gcd(n,k)$ 是 $S$ 的周期是有解的必要不充分条件。

在上述条件下，如果 $n+k \equiv 0 \pmod{2\gcd(n,k)}$，显然是有解的，否则只有 $S$ 回文才能构造出合法的 $S'$。

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define int long long

void R()
{
	int n,k;
	string s;
	cin>>n>>k>>s;
	int t=__gcd(n,k),a=n/t;
	rep(i,1,a-1)
		rep(j,1,t)
			if (s[(i-1)*t+j-1]!=s[(i+1)*t-j])
			{
				puts("No");
				return;
			}
	if ((n+k)/t%2==1)
	{
		int l=0,r=t-1;
		while (l<r)
		{
			if (s[l]!=s[r])
			{
				puts("No");
				return;
			}
			l++,r--;
		}
	}
	puts("Yes");
}
 
signed main()
{
	int T;
	cin>>T;
	while (T--)
		R();
	return 0;
}
```


---

