# AmShZ Wins a Bet

## 题目描述

在 2020 年欧洲杯之前，AmShZ 和 Safar 打赌谁会成为冠军，AmShZ 赌意大利，Safar 赌法国。

当然，AmShZ 赢了。因此，Safar 给了他一个括号序列 $S$。注意，括号序列是由 '(' 和 ')' 字符组成的字符串。

AmShZ 可以进行如下操作任意次：

- 首先，他将字符串 $S$ 切分为三个（可能为空的）连续子串 $A$、$B$ 和 $C$。然后，他用一个 '(' 和一个 ')' 字符将它们重新拼接，得到新字符串 $S = A + "(" + B + ")" + C$。例如，如果 $S = "))((" $，AmShZ 将其切分为 $A = ""$，$B = "))"$，$C = "(("$，他将得到新字符串 $S = "()))(("$。

在进行若干次（也可能不进行）操作后，AmShZ 把他的字符串交给 Keshi，并让他找出初始字符串。当然，Keshi 可能会想到多个可能的初始字符串。Keshi 对于找到字典序最小的初始字符串感兴趣。

你的任务是帮助 Keshi 实现他的目标。

如果字符串 $a$ 在字典序上小于字符串 $b$，当且仅当满足以下条件之一：

- $a$ 是 $b$ 的前缀，且 $a \ne b$；
- 在 $a$ 和 $b$ 第一个不同的位置，$a$ 的字母在字母表中比 $b$ 的对应字母更靠前。

## 说明/提示

在第一个样例中，可以将 ")((())))" 变为 ")(()(())))"，方法是将其切分为 ")("、空串和 "(())))"。可以证明这是字典序最小的初始字符串。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
)(()(())))```

### 输出

```
)((())))```

# 题解

## 作者：feecle6418 (赞：16)

> 蓝有一个括号串 $S$，其中括号串定义为仅由 `(` 和 `)` 组成的字符串。
>
> 现在她进行了任意次如下操作：
>
> - 将 $S$ 分为三个可以为空的连续子串 $A,B,C$，接着将 $S$ 变为一个新串 $A(B)C$（即在 $B$ 前加上左括号，在 $B$ 后加上右括号）。
>
> 接着，她给出了经过她任意次操作后的括号串 $S$，她希望你能还原出原串 $S'$，使得 $S'$ 的字典序最小。
>
> 对于两个字符串 $a$ 和 $b$，若 $a$ 字典序比 $b$ 小，那么满足如下条件：
>
> - $a$ 为 $b$ 的前缀，且 $a\neq b$；
> - 令 $i$ 为最小的数使得 $a_i\neq b_i$，那么 $a_i$ 为左括号。
>
> 本题数据满足：$1 \leq |S| \leq 3\times10^5$。

容易发现只要移除了 $S_i,S_j$，那么 $\forall i<k<j$，$S_k$ 都会移除，这是因为如果移除了 `(?...)`：

- 如果 ? 是 (，移除 ?) 可以使得 ( 往前。
- 如果 ? 是 )，移除 (? 可以使得 ) 往后。

因此移除的一定是一些连续的合法的括号序列。

设 $to_i$ 表示 $[i,to_i]$ 这段区间构成合法的括号序列，设 $f_i$ 表示 $[i,n]$ 移除之后字典序最小的串，有

- $to_i$ 不存在：$f_i=S_i+f_{i+1}$（$+$ 表示拼接）
- $to_i$ 存在：$f_i=\min(S_i+f_{i+1},f_{to_i+1})$

直接 dp 可以做到 $O(n^2)$。

如果要用数据结构优化，其实是要解决如下问题：

> 对于一个字符串 $S$，可持久化地支持：
>
> - 在某个版本前面添加字符。
> - 比较第 $i$ 个版本和第 $j$ 个版本的字典序大小。（其实就是求 LCP 长度）

暴力上可持久化平衡树可以做到双 log（二分 + 平衡树维护哈希）。

上面的做法大问题是，二分和平衡树的 log 是不能兼容的（因为这时两边结构不同不能平衡树上二分）。有没有什么方法不需要这么 monstrous 的数据结构？

考虑一个更显然的类似问题：

> 对于序列 $S$，支持在前面添加数、求区间最小值。

在加入数的过程中动态维护一个 ST 表，加入一个数就 $O(\log n)$ 预处理一下新前缀的 ST 表。

而且这个做法也可以可持久化，把 ST 表建成树上倍增数组类似物。并且，ST 表的结构决定了它可以容下在不同地方开始的二分：将其换为倍增即可。

回到原问题，套用这个做法，倍增维护哈希值即可。

具体地，开两个倍增数组，分别维护 $f_i$ 的第 $2^j$ 位在原串中的位置、$f_i$ 的 $[0,2^{j-1}]$ 的哈希值。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int B=233,mod=998244853;
string s,f[300005];
int st[300005],top,n,to[300005],p[300005][20],hsh[300005][20],pw[300005]={1},S[300005];
int main(){
	cin>>s,n=s.length();
	for(int i=1;i<=n;i++)pw[i]=1ll*pw[i-1]*B%mod;
	for(int i=0;i<n;i++){
		if(s[i]=='(')st[++top]=i;
		else {
			if(top)to[st[top]]=i+1,top--;
		}
	}
	p[n][0]=S[n]=n;
	for(int i=n-1;i>=0;i--){
		p[i][0]=S[i+1],hsh[i][0]=s[i],S[i]=i;
		for(int j=1;j<=18;j++){
			p[i][j]=p[p[i][j-1]][j-1];
			hsh[i][j]=(hsh[i][j-1]+1ll*hsh[p[i][j-1]][j-1]*pw[(1<<j-1)])%mod;
		}
		if(to[i]){
			int x=i,y=S[to[i]];
			for(int j=18;j>=0;j--){
				if(hsh[x][j]==hsh[y][j]){
					x=p[x][j],y=p[y][j];
				}
			}
			if(y==n||(s[x]>s[y]))S[i]=S[to[i]];
		}
	}
	int x=S[0];
	while(x<n)cout<<s[x],x=p[x][0]; 
}
```



---

## 作者：xcyle (赞：5)

经典简单数据结构藏后面

考虑一对被删掉的$()$，在它们之间的所有字符一定也被删掉了。

因此问题可以转化成从括号串中选取若干段不交的合法子串并删除

考虑倒序dp，设 $f_i$ 表示 $i$ 到 $n$ 之间的字符作为原括号串的答案串

转移讨论是否删第 $i$ 个字符，不难发现这样定义状态可以将一次删掉合法子串的操作分解成多次，因此如果删 $i$ 必定选取 $i$ 后第一次合法的前缀删除。

后者不难用单调栈求出，设为 $nxt_i$。有 $f_i = \min(S_i+f_{i+1},f_{nxt_i})$

比较字典序大小不难想到哈希，直接上主席树维护是两只 $\log$ 的

容易发现字符串之间的关系是树形的。问题转化为维护一个 trie 树，每次添加一个叶子或者询问两个树上的字符串倒序的字典序关系

这个问题直接在祖先上倍增跳并前缀和相减求哈希值即可

时间复杂度 $O(n\log n)$

---

## 作者：5ab_juruo (赞：4)

模拟赛的时候写了个奇怪做法，交了以后莫名其妙拿了最优解，记录一下。

首先可以观察到性质：移除的一定是连续的合法括号串，证明可以看其他题解。

把 `(` 看作 $+1$，`)` 看作 $-1$，把整个串根据前缀和的前缀 min 分成若干个串。除了最后一个串，每个串都形如一个合法括号串加上 `)`。

最后一个串的情况是 trivial 的，我们只需要尽可能多地删即可，最后会变成一些 `(`，必然是字典序最小的。

对于中间的合法括号串 $s$，我们考虑一个暴力策略来最小化字典序：

- 将 $s$ 分成尽可能多的合法括号串 $t_1,t_2,\cdots,t_n$；
- 将每个 $t_i$ 去掉左右括号后递归处理；
- 对 $t_1,t_2,\cdots,t_n$ 跑单调栈，留下后缀最小值。

注意到两个字符串 $s,t$ 的比较复杂度是 $O(\min(|s|,|t|))$，则单调栈过程中的比较次数必然不超过 $|s|-\max\{|t_i|\}$。把递归树画出来，则每个点只有在跳轻边的时候会贡献复杂度，则复杂度显然是 $O(n\log n)$ 的。

写的比较复杂，应该是有比较简单的写法的。

```cpp
const int max_n = 3e5;

struct node
{
	int up, nxt;
}
tr[max_n];
char s[max_n + 1], t[max_n + 1];
int ti = 0;

int cmp(int x, int y)
{
	while (x != -1 && y != -1)
	{
		if (tr[x].up != -1)
		{
			int t = cmp(tr[x].up, tr[y].up);
			if (t != 0)
				return t;
		}
		x = tr[x].nxt, y = tr[y].nxt;
	}
	if (x != -1)
		return 1;
	if (y != -1)
		return -1;
	return 0;
}

void solve(int &x)
{
	if (tr[x].up != -1)
		solve(tr[x].up);
	if (tr[x].nxt != -1)
	{
		solve(tr[x].nxt);
		if (cmp(tr[x].up, tr[tr[x].nxt].up) < 0)
			x = tr[x].nxt;
	}
}

void write(int x)
{
	if (tr[x].up != -1)
	{
		t[ti++] = '(';
		write(tr[x].up);
		t[ti++] = ')';
	}
	if (tr[x].nxt != -1)
		write(tr[x].nxt);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> s;
	int n = strlen(s);
	
	int x = 0, ind = 0;
	
	vector<int> stk;
	while (x < n)
	{
		int y = x, sm = 0;
		ind = 0;
		
		stk.clear();
		for (; y < n && sm >= 0; y++)
		{
			if (s[y] == '(')
			{
				sm++;
				if (empty(stk) || tr[stk.back()].up != -1)
				{
					tr[ind] = { -1, -1 };
					if (!empty(stk))
					{
						tr[stk.back()].nxt = ind++;
						stk.back() = tr[stk.back()].nxt;
					}
					else
						stk.push_back(ind++);
				}
				tr[ind] = { -1, -1 };
				tr[stk.back()].up = ind;
				stk.push_back(ind++);
			}
			else
			{
				sm--;
				if (!empty(stk))
				{
					tr[stk.back()].nxt = -1;
					stk.pop_back();
				}
			}
		}
		if (sm >= 0)
		{
			for (int i = 0; i < sm; i++)
				t[ti++] = '(';
			break;
		}
		
		if (ind)
		{
			int rt = 0;
			solve(rt);
			write(rt);
		}
		t[ti++] = ')';
		x = y;
	}
	cout << t << endl;
	
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：4)

**CF1610G**

大量手玩一下，凭感觉可以倒着往前做。

发现一个结论：删除的任意括号 $\text i,\text j$ 满足区间中的所有括号都被删除的情况下删除一定可以到达最优态。讨论 $[\text i,\text j - \text 1]$ 和 $[\text {j} - \text 1,\text n]$ 两段发现前面一段在整体左移后显然不更优（因为删去了头的左括号），并且此时该区间一定全为左括号，那么不用管后面的一段了，直接匹配 $\text p\in[\text i,\text j - \text 1]$ 和 $\text j$ 也可以到达期望的效果。

考虑倒着 $\text {dp}$。

我们维护 $\text {dp}_{\text i}$ 表示当前后缀 $\text [\text i,\text n]$ 的最小字典序字符串，显然如果要按照上述方法删除括号中间不能留数，我们维护出来从 $\text i$ 之后第一个满足 $[\text i,\text j]$ 是合法括号匹配区间的 $\text j$，如果删除区间时要删除足 $\text j < \text j'$ 的区间 $[\text i,\text j']$，那么一定可以拆成两个括号序列删除，并且后面的情况也会被 $\text f_{\text j + \text 1}$ 给考虑。

那么转移就是 $\text f_{\text i} = \min(\text f_{\text{nxt}_{\text i + \text 1}},\text S_{\text i} + \text f_{\text i + \text 1})$，直接建出来树形关系然后爬个倍增前缀 hash 值即可。

时间复杂度 $\text O(\text n \log \text n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
const int Len = 1e6 + 5 , mod = 1e9 + 7;
int n,m,fa[25][Len],lg[Len],nxt[Len],stk[Len],top;ll hsh[25][Len],pw[25];
char s[Len];
int main()
{
	scanf("%s",s + 1);n = strlen(s + 1);for(int i = 2 ; i <= n ; i ++) lg[i] = lg[i >> 1] + 1;pw[0] = 131;for(int i = 1 ; i <= n ; i ++) pw[i] = pw[i - 1] * pw[i - 1] % mod; 
	for(int i = 1 ; i <= n ; i ++)
	{
		if(s[i] == '(') stk[++ top] = i;
		else{if(top) nxt[stk[top --]] = i;}
	} 
	hsh[0][n + 1] = -1;
	for(int i = n ; i >= 1 ; i --)
	{
		fa[0][i] = (i == n) ? 0 : i + 1;
		hsh[0][i] = (s[i] == '(') ? 0 : 1;
		for(int j = 1 ; j <= lg[n] ; j ++) fa[j][i] = fa[j - 1][fa[j - 1][i]] , hsh[j][i] = (hsh[j - 1][i] + pw[j - 1] * hsh[j - 1][fa[j - 1][i]] % mod) % mod;
		if(nxt[i])
		{
			int x = i , y = nxt[i] + 1;
			for(int j = lg[n] ; j >= 0 ; j --) if(fa[j][x] && fa[j][y] && hsh[j][x] == hsh[j][y]) x = fa[j][x] , y = fa[j][y];
			if((hsh[0][x] > hsh[0][y]) || (hsh[0][x] == hsh[0][y] && !fa[0][y])) 
			{
				//upd fa
				fa[0][i] = fa[0][nxt[i] + 1] , hsh[0][i] = hsh[0][nxt[i] + 1];
				for(int j = 1 ; j <= lg[n] ; j ++) fa[j][i] = fa[j - 1][fa[j - 1][i]] , hsh[j][i] = (hsh[j - 1][i] + pw[j - 1] * hsh[j - 1][fa[j - 1][i]] % mod) % mod;
			}
		}
	}
	int x = 1;
	while(x && x <= n) 
	{
		if(hsh[0][x] < 0 || hsh[0][x] > 1) break;
		putchar(hsh[0][x] + '(');
		x = fa[0][x];
	}
	return 0;
}
```

---

## 作者：xcyyyyyy (赞：2)

### [CF1610G] AmShZ Wins a Bet

首先规定我们只能删掉中间没有任何字符的 $()$。

很好证明：假设是这样一个情形 $(...))$，那么我们删除另外一对是等价的；如果是这样一个情形 $(...,()$，那么我们不如删除另一对，这样一定更优：删除后的字符串更大，而且以后的操作空间也会更大。

那么我们一定只能删除若干个合法的括号字符串，考虑设计`dp`： $f_{i}=\min(s_i+f_{i+1},f_{nxt_i+1})$。

不正着设计的原因是，如果我们这样设计： $f_{i}=\min(f_{i-1}+s_i,f_{lst_i-1})$，那么如果我们需要加入 $s_i$ 这个项，那么我们的转移不一定需要最小，即：

> 若 $a\lt b$，我们不能保证 $a+s \lt b+s$，比如 $a\lt aa$，$ab \gt aab$。

当常识记住，设计此类 `dp` 必须要从后往前 `dp`。

然后考虑如何优化这个 `dp`，发现我们每一次只会在一个字符串前面添加一个 $s_i$，不妨将串倒过来，然后建立字典树，考虑比较，我们只需要倍增维护 `hash` ，找到第一个不一样的位置即可。

---

## 作者：PTqwq (赞：1)

https://www.luogu.com.cn/problem/CF1610G

这题真的有 *3300 吗？

首先转化为给定了 $S$ 要删除 $S_i, S_j(1 \leq i < j \leq |S|, S_i = \texttt{(}, S_j = \texttt{)})$。

然后一个比较重要的观察就是，如果我们在在一次删除中删掉了 $S_L, S_R$，那么 $S_{L + 1}, S_{L + 2}, \dots, S_{R - 1}$ 这些字符在最后的至少一个最优解里面也都被删除了。证明可以考虑如果 $S_{[L + 1...R - 1]}$ 都是左括号那么可以调整为删除 $S_{R - 1}, S_{R}$，否则我们一定可以删除 $S_{[L + 1...R - 1]}$ 其中的一个右括号来代替 $S_R$，容易发现字典序不会变大。

根据这个观察，其实可以推出最后一定是删掉了若干个 $S$ 的连续合法括号子串，然后考虑 DP，设 $f_{i}$ 表示 $S_{[i...|S|]}$ 删掉若干个连续合法括号子串后可以得到的最小字典序字符串，转移也不难，只需分讨从 $i$ 开始往后延申的第一个合法括号子串（如果存在，设为 $S_{[i...p]}$）是否删除即可，即：

$$f_{i} = \min(S_i + f_{i + 1}, f_{p + 1})$$

然后发现每个 $f_{i}$ 其实形如一个 DAG 上面从一个节点开始走到一个 $0$ 度点的一条路径上，所有节点上的字符拼起来得到的序列，这个 DAG 显然是可以根据 DP 决策动态构建的：

- 设 $top_i$ 表示 $f_i$ 的第一个字符是 $S_{top_i}$，如果为空则为 $0$。
- 如果 $f_{i} = f_{p + 1}$ 则 $f_i$ 的信息和 $f_{p + 1}$ 完全一致，即 $top_i = top_{p + 1}$。
- 否则 $top_i = i$，连边 $i \to top_{i + 1}$。

容易使用倍增维护哈希值优化，时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace PTqwq {

int readqwq() {
    int x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

ll readllqwq() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

const ll valB = 41;
const ll mod = 1610612741;
const int N = 3e5 + 50;

struct Info {
    ll curb, hsh;
    Info() {curb = 1; hsh = 0;}
    Info(ll a, ll b) {curb = a % mod; hsh = b % mod;}
    Info(char c) {curb = valB; hsh = (c == '(' ? 17ll : 23ll);}
};
bool operator == (Info Lhs, Info Rhs) {
    if (Lhs.curb == Rhs.curb && Lhs.hsh == Rhs.hsh) {
        return true;
    } else {
        return false;
    }
}
Info operator + (Info Lhs, Info Rhs) {
    Info res = Info();
    res.curb = Lhs.curb * Rhs.curb % mod;
    res.hsh = (Lhs.hsh * Rhs.curb + Rhs.hsh) % mod;
    return res;
}

char s[N];
int n, nxt[N], st[N], pos[20][N], pre[20][N], mp[N * 2], vaLg[N];
Info valst[20][N];

void init(int u) {
    pos[0][u] = nxt[u];
    valst[0][u] = Info(s[u]);
    for (int i = 1; i < 20; ++ i) {
        pos[i][u] = pos[i - 1][pos[i - 1][u]];
        valst[i][u] = valst[i - 1][u] + valst[i - 1][pos[i - 1][u]];
    }
}

void InitInfo() {
    for (int i = 0; i <= n * 2; ++ i) {
        mp[i] = -1;
    }
    nxt[0] = 0;
    nxt[n] = 0;
    st[n] = n;
    init(0);
    init(n);
    pre[0][0] = 0; vaLg[0] = -1;
    for (int i = 1; i <= n; ++ i) {
        pre[0][i] = pre[0][i - 1];
        if (s[i] == '(') {
            pre[0][i] ++;
        } else {
            pre[0][i] --;
        }
        vaLg[i] = vaLg[i / 2] + 1;
    }
    for (int i = 1; i < 20; ++ i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++ j) {
            pre[i][j] = min(pre[i - 1][j], pre[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int queryMin(int L, int R) {
    if (L < 1 || R > n || L > R) {
        return -1;
    } else {
        int k = vaLg[R - L + 1];
        return min(pre[k][L], pre[k][R - (1 << k) + 1]);
    }
}
bool chk(int L, int R) {
    if (L < 1 || R > n || L > R) {
        return false;  
    } else if (queryMin(L, R) - pre[0][L - 1] >= 0 && pre[0][R] == pre[0][L - 1]) {
        return true;
    } else {
        return false;
    }
}

int query(int i, int cur) {
    if (mp[cur + n] == -1) {
        return -1;
    } else {
        int j = mp[cur + n] - 1;
        if (chk(i, j)) {
            return j;
        } else {
            return -1;
        }
    }
}

void Solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    InitInfo();
    int cur = 0;
    mp[cur + n] = n + 1;
    if (s[n] == '(') {
        cur ++;
    } else {
        cur --;
    }
    mp[cur + n] = n;
    for (int i = n - 1; i >= 1; -- i) {
        if (s[i] == '(') {
            cur ++;
        } else {
            cur --;
        }
        int p = query(i, cur);
        mp[cur + n] = i;
        if (p == -1) {
            st[i] = i;
            nxt[i] = st[i + 1];
        } else if (p == n) {
            st[i] = 0;
            nxt[i] = 0;
        } else {
            if (st[p + 1] == 0) {
                st[i] = 0;
                nxt[i] = 0;
            } else if (s[i] == s[st[p + 1]]) {
                int u = st[i + 1];
                int v = nxt[st[p + 1]];
                for (int j = 19; j >= 0; -- j) {
                    if (valst[j][u] == valst[j][v]) {
                        if (pos[j][u] == pos[j][v] && pos[j][u] != 0 && pos[j][v] != 0) {
                            u = pos[j][u];
                            v = pos[j][v];
                        }
                    }
                }
                while (u != 0 && v != 0) {
                    if (s[u] != s[v]) break;
                    u = nxt[u];
                    v = nxt[v];
                }
                if (u == 0 && v == 0) {
                    st[i] = i;
                    nxt[i] = st[i + 1];
                } else if (u == 0 && v != 0) {
                    st[i] = i;
                    nxt[i] = st[i + 1];
                } else if (u != 0 && v == 0) {
                    st[i] = st[p + 1];
                    nxt[i] = 0;
                } else {
                    if (s[u] == '(') {
                        st[i] = i;
                        nxt[i] = st[i + 1];
                    } else {
                        st[i] = st[p + 1];
                        nxt[i] = 0;
                    }
                }
            } else if (s[i] == '(') {
                st[i] = i;
                nxt[i] = st[i + 1];
            } else {
                st[i] = st[p + 1];
                nxt[i] = 0;
            }
        }
        init(i);
    }
    for (int i = st[1]; i != 0; i = nxt[i]) {
        putchar(s[i]);
    }
    putchar('\n');
}

}

int main() {
    PTqwq::Solve();

    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1610G)

**题目大意**

> 给定长度为 $n$ 的括号串 $S$，每次可以删去一对括号，求能生成的字典序最大的括号串。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

注意到如果我们删除的括号不连续，不妨设形如 `(?......)`，那么如果 `?` 是左括号，改成删除 `?)` 不影响结果，否则删除 `(?` 可以减少串首的一个 `)`。

根据调整法，我们删除的括号一定是连续的，那么这就等价于删除若干个匹配括号子串。

设 $[i,nxt_i]$ 为极小匹配括号子串，$f_i$ 为 $S[i,n]$ 后缀的最大字典序字符串，那么 $f_i=\min(f_{nxt_i+1},S_i+f_{i+1})$。

设 $g_i$ 表示 $f_i$ 的开头所在位置，我们维护一棵树状结构，其中 $\mathrm{fa}(i)=g_{i+1}$，那么 $f_i$ 等于树上 $g_i\to \mathrm{root}$ 的链拼接成的字符串。

那么我们就是要比较 $g_i\to \mathrm{root},g_{nxt_i+1}\to\mathrm{root}$ 两条链的字典序，倍增维护哈希即可求出 $\mathrm{lcp}$。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MAXN=3e5+5;
mt19937_64 rnd(time(0));
char str[MAXN];
int n,sk[MAXN],tp,nxt[MAXN],hd[MAXN],fa[MAXN][20];
ull B,hw[2],hv[MAXN][20],pw[20];
signed main() {
	B=pw[1]=rnd()|1,hw[0]=rnd()|1,hw[1]=rnd()|1;
	for(int i=2;i<20;++i) pw[i]=pw[i-1]*pw[i-1];
	scanf("%s",str+1),n=strlen(str+1);
	for(int i=1;i<=n;++i) {
		if(str[i]=='(') sk[++tp]=i;
		else if(tp) nxt[sk[tp--]]=i;
	}
	fa[n+1][0]=hd[n+1]=n+1,str[n+1]=0;
	for(int i=n;i>=1;--i) {
		hd[i]=i,fa[i][0]=hd[i+1],hv[i][0]=hw[str[i]-'('];
		for(int k=1;k<20;++k) {
			fa[i][k]=fa[fa[i][k-1]][k-1];
			hv[i][k]=hv[i][k-1]+hv[fa[i][k-1]][k-1]*pw[k];
		}
		if(!nxt[i]) continue;
		int x=hd[i],y=hd[nxt[i]+1];
		for(int k=19;~k;--k) if(hv[x][k]==hv[y][k]) x=fa[x][k],y=fa[y][k];
		if(str[y]<str[x]) hd[i]=hd[nxt[i]+1];
	}
	for(int p=hd[1];p<=n;p=fa[p][0]) printf("%c",str[p]); puts("");
	return 0;
}
```

---

## 作者：MiniLong (赞：1)

小清新贪心题。

括号序列就直接想括号树。但因为原串不是合法的，所以我们做一些特殊处理。对于多余的 `(`，把它看成一个特殊的点，使得其返回父亲的时候不会有加右括号。对于多余的 `)`，我们在上一个合法子段后标记一下。

然后就考虑在括号树中的每个节点中删除它的一些儿子。设它的儿子为 $son_1,son_2,...,son_k$，那么对于相邻两个儿子 $son_x,son_{x+1}$，如果 $son_x$ 生成的字典序大于 $son_{x+1}$ 生成的字典序，**并且 $son_x$ 后面没有多余的 `)`（显然这里只会在第一层出现）**，就把 $x$ 子树整个删掉（因为如果把 $son_x$ 删掉那么第一个字符就是 `)` 了，肯定不优）。

还有一个方式，对于**最后一个**多余的 `)`，后面所有的字符都可以删掉，这个是显然的。

建出括号树暴力地递归去做就行，比较也可以暴力搜索一遍。因为每次要比较的节点至少有 $2$ 个儿子，每次复杂度是 $\Theta(\min(siz_{son_x},siz_{son_{x+1}}))$，所以平均下来最劣复杂度为二叉树的形式，$\sum siz$ 是 $\Theta(n\log n)$ 级别的，可以通过。

所以总复杂度是 $\Theta(n \log n)$，简单好写。

---

## 作者：541forever (赞：1)

可以发现一个有趣的性质，就是如果一组 $()$ 最终被删去，那它中间的东西也必须全部删去，不然字典序一定不优，根据这个性质，我们便可以推断出左括号 $i$ 对应删去的右括号，一定是从 $i$ 开始往后第一个满足构成合法括号序列的位置 $nxt_i$。这样，我们便可以钦定一个删的顺序了，考虑从后往前 dp，设 $f_i$ 表示从 $i$ 开始的整个后缀能被删成的字典序最小的字符串。那么

$$f_i=\min(f_{nxt_i},s_i+f_{i+1})$$

暴力做这个 dp 是 $O(n^2)$ 的，考虑去优化。发现这个复杂度很劣的一个原因是字符串比较字典序的复杂度很劣。考虑将字符串 hash 一下，并把每个 $f_i$ 插入到 trie 树中去，同时记录每个点往上跳 $2^i$ 步组成字符串的 hash 值，可以发现，每个 $f_i$ 至多会在原本的 trie 树中增添一个字符，考虑将 $s_i$ 插入到 $f_{i+1}$ 的后面后直接拿这个位置和 $f_{nxt_i}$ 比，具体地，我们在 trie 树上根据 hash 值倍增，找到第一个不同的位置比大小即可。时空复杂度均为 $O(n \log n)$。

Tips:
1. 倍增时要注意不要跳出了字符串。
2. 字符串比较次数多，请选用较大模数或直接自然溢出。

[Code](https://codeforces.com/contest/1610/submission/211889139)

---

## 作者：Purslane (赞：1)

# Solution

这能黑？这能 `*3300`？？

-------

对于一个括号串 $A$，显然有：$(A$ 的字典序不大于 $A($。（考虑 $A$ 中第一个不为 $($ 的字符即可。）同样有 $A)$ 的字典序不大于 $)A$。

因此，我们删除的括号串不会太复杂：每次都是删掉相邻的 $()$

所以我们只相当于在原串中扣去若干个连续的合法括号串。

很容易想到设 $dp_i$ 表示前 $i$ 个字符删掉若干个合法括号串得到的最小的字符串。

然而有一个很大的 Bug：如果 $S$ 是 $S'$ 的前缀，那么必定有 $S<S'$，但是选 $S$ 不一定更优。

然而容易发现，如果是后缀的话，显然最小化它是合理的。（一种处理字典序最小的常见思路）

因此考虑设 $dp_i$ 表示处理了 $i$ 以后的字符能获得的最小字符串。

有两种转移：

1. 从 $dp_{i+1}$ 转移，在前面加上 $S_i$；
2. 从 $dp_{r+1}$ 转移，其中 $S[l \dots r]$ 是极长的匹配括号串。

直接做是 $O(n^2)$ 的，考虑优化。

显然每个 $dp_i$ 都可以写作 $dp_j$ 或者 $\mathcal{C} + dp_j $ 的形式，这是一个树形结构，因此可以在树上倍增，并且使用哈希 + 二分（这里就是倍增）确定两种方案的优劣。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=300000+10,MOD1=1e9+9,MOD2=998244353;
int n,pre[MAXN],tp[MAXN],rt[MAXN],fa[MAXN][20],hval1[MAXN][20],hval2[MAXN][20],pw1[MAXN],pw2[MAXN];
string S;
map<int,int> mp;
void insert(int u,int f,int t) {
	tp[u]=t,fa[u][0]=f,hval1[u][0]=hval2[u][0]=t;
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1],hval1[u][i]=(hval1[u][i-1]+hval1[fa[u][i-1]][i-1]*pw1[1<<i-1])%MOD1,hval2[u][i]=(hval2[u][i-1]+hval2[fa[u][i-1]][i-1]*pw2[1<<i-1])%MOD2;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S;
	ffor(i,1,n) pre[i]=pre[i-1]+(S[i]=='('?1:-1);
	pw1[0]=1;
	ffor(i,1,n) pw1[i]=pw1[i-1]*2%MOD1;
	pw2[0]=1;
	ffor(i,1,n) pw2[i]=pw2[i-1]*2%MOD2;
	mp[pre[n]]=n+1,rt[n+1]=n+1,tp[n+1]=-1;
	roff(i,n,1) {
		insert(i,rt[i+1],S[i]==')');
		if(S[i]=='('&&mp.count(pre[i-1])) {
			int u=i,v=rt[mp[pre[i-1]]];
			roff(j,19,0) if(fa[u][j]&&fa[v][j]&&hval1[u][j]==hval1[v][j]&&hval2[u][j]==hval2[v][j]) u=fa[u][j],v=fa[v][j];
			if(tp[u]<tp[v]) rt[i]=i;
			else rt[i]=rt[mp[pre[i-1]]];
		}
		else rt[i]=i;
		mp[pre[i-1]]=i;
	}
	int u=rt[1];
	while(u!=n+1) {
		if(tp[u]) cout<<')';
		else cout<<'(';
		u=fa[u][0];	
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

如何最优地删除？考虑你要删除一个 ```(```，因为要最小化字典序，所以贪心地找下一个 ```)``` 一并删除。那么这个过程等价于找到一个连续的 ```()``` 删除，因为可以做任意次，又等价于找到一个连续的合法子串删除。

设 $dp_i$ 表示 $[i, n]$ 后缀的对于原问题的答案，那么转移已经明确了，剩下的便是优化判断字典序大小的过程。转移共两种形式：$dp_i = s_i + dp_{i + 1}, dp_i = dp_{g_i + 1}$（其中 $g$ 是我们预处理出的最短合法子串对应的结束位置），那么这个转移形如字典树，可以树上倍增维护哈希值。

记录 $st_i, f_{i, j}, ps_{i, j}$ 表示 $dp_i$ 对应字典树上的哪个点，从它开头 $2^j$ 个字符的哈希值，从开头往后数 $2^j$ 个字符到字典树的哪个节点即可。

---

