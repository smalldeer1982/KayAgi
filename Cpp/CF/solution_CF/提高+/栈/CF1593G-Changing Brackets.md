# Changing Brackets

## 题目描述

A sequence of round and square brackets is given. You can change the sequence by performing the following operations:

1. change the direction of a bracket from opening to closing and vice versa without changing the form of the bracket: i.e. you can change '(' to ')' and ')' to '('; you can change '\[' to '\]' and '\]' to '\['. The operation costs $ 0 $ burles.
2. change any square bracket to round bracket having the same direction: i.e. you can change '\[' to '(' but not from '(' to '\['; similarly, you can change '\]' to ')' but not from ')' to '\]'. The operation costs $ 1 $ burle.

The operations can be performed in any order any number of times.

You are given a string $ s $ of the length $ n $ and $ q $ queries of the type "l r" where $ 1 \le l < r \le n $ . For every substring $ s[l \dots r] $ , find the minimum cost to pay to make it a correct bracket sequence. It is guaranteed that the substring $ s[l \dots r] $ has an even length.

The queries must be processed independently, i.e. the changes made in the string for the answer to a question $ i $ don't affect the queries $ j $ ( $ j > i $ ). In other words, for every query, the substring $ s[l \dots r] $ is given from the initially given string $ s $ .

A correct bracket sequence is a sequence that can be built according the following rules:

- an empty sequence is a correct bracket sequence;
- if "s" is a correct bracket sequence, the sequences "(s)" and "\[s\]" are correct bracket sequences.
- if "s" and "t" are correct bracket sequences, the sequence "st" (the concatenation of the sequences) is a correct bracket sequence.

E.g. the sequences "", "(()\[\])", "\[()()\]()" and "(())()" are correct bracket sequences whereas "(", "\[(\])" and ")))" are not.

## 说明/提示

Consider the first test case. The first query describes the whole given string, the string can be turned into the following correct bracket sequence: "(\[()\])()\[\[\]\]". The forms of the brackets aren't changed so the cost of changing is $ 0 $ .

The second query describes the substring ")\[)()\]". It may be turned into "(()())", the cost is equal to $ 2 $ .

The third query describes the substring "))\[)". It may be turned into "()()", the cost is equal to $ 1 $ .

The substrings of the second test case contain only round brackets. It's possible to prove that any sequence of round brackets having an even length may be turned into a correct bracket sequence for the cost of $ 0 $ burles.

In the third test case, the single query describes the string "\[\]" that is already a correct bracket sequence.

## 样例 #1

### 输入

```
3
([))[)()][]]
3
1 12
4 9
3 6
))))))
2
2 3
1 4
[]
1
1 2```

### 输出

```
0
2
1
0
0
0```

# 题解

## 作者：DaiRuiChen007 (赞：5)

# CF1593G 题解



## 思路分析

由于题目数据进行了保证，以下的讨论均在 $|S|$ 为偶数的前提下进行。

记 $\operatorname{cost}(S)$ 表示按题目要求使得 $S$ 变成有一个合法括号序列的最小代价。

注意到 `[` 和`]`，`(` 和 `)` 没有区别，因为它们可以在不花费代价的情况下互相转化。

所以我们只需要防止形如 `([)]` 的情况出现即可。

观察一个合法的序列，我们发现任意一对匹配的 `[]` 中间都有一个合法的括号序列，而这个括号序列的长度一定是偶数。

因此每一对匹配的 `[` 和 `]`，这两个字符在原串的下标一定是一奇一偶的。

假设在串 $S$ 中，奇数位置上的中括号有 $c_1$ 个，偶数位置上的中括号有 $c_2$ 个，注意到如下观察：

> 观察：
>
> 对于任意 $S$，$\operatorname{cost}(S)=0\iff c_1=c_2$。
>
> 考虑对 $\min(c_1,c_2)$ 归纳：
>
> 当 $\min(c_1,c_2)=0$ 的时候，若 $c_1=c_2=0$，那么显然 $S$ 可以通过把前一半小括号变成 `(`，后一半小括号变成 `)` 来满足题目要求。
>
> 如果 $\max(c_1,c_2)>0$，此时可以证明任意两个中括号间的字符数量都是奇数，因此这中间不存在任何一对可以配对的中括号。
>
> 由于在一个合法的括号匹配序列中，任取一段匹配的子串删去仍然是一个合法的括号匹配。
>
> 那么当 $c_1,c_2\ne0$ 我们必然可以找到一对相邻的，分别处于奇偶位置上的中括号，我们取出这两个中括号和其中间的所有字符构成的子串。
>
> 容易发现其中间恰好有偶数个小括号，而有且仅有两侧的中括号，显然这个子串可以在 $0$ 的代价内处理成一个匹配括号序列，因此将这个序列从 $S$ 中删去，容易发现 $\min(c_1,c_2)\gets\min(c_1,c_2)-1$，那么根据归纳假设即得证。

因此我们能够大胆猜想，对于任意 $S$，$\operatorname{cost}(S)=|c_1-c_2|$。

> 证明：
>
> 1. $\operatorname{cost}(S)\ge |c_1-c_2|$。
>
> 考虑对每个代价为 $1$ 的操作，显然可以通过枚举分讨证明一次修改只会对 $c_1-c_2$ 产生 $\pm 1$ 的贡献，所以想要使得 $c_1-c_2=0$，至少需要 $|c_1-c_2|$ 次代价为 $1$ 的操作。
>
> 2. $\operatorname{cost}(S)\le |c_1-c_2|$。
>
> 显然每次将 $c_1,c_2$ 中较大的那个数对应的那些下标中选一个操作成小括号即可得到一个代价为 $|c_1-c_2|$ 的操作方案，所以 $\operatorname{cost}(S)\le |c_1-c_2|$。
>
> 因此结合两个方向的不等号得到 $\operatorname{cost}(S)=|c_1-c_2|$。

因此每次计算一个子段的答案只需要预处理出 $c_1$ 和 $c_2$ 的前缀和即可 $\Theta(1)$ 处理每次询问。

时间复杂度 $\Theta(n+q)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=1e6+1;
char str[MAXN];
int sum[MAXN][2];
inline void solve() {
	scanf("%s",str+1);
	int n=strlen(str+1);
	for(int i=1;i<=n;++i) {
		sum[i][0]=sum[i-1][0],sum[i][1]=sum[i-1][1];
		if(str[i]=='['||str[i]==']') ++sum[i][i%2];
	}
	int q;
	scanf("%d",&q);
	while(q--) {
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",abs((sum[r][0]-sum[l-1][0])-(sum[r][1]-sum[l-1][1])));
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：_zzi_ (赞：4)

考虑到 $"(,["$ 等全部都可以自由翻转，那么只用考虑这个区间内多少 $"["$ 或者 $"]"$ 无法配对，

那么我们考虑到两个奇数的 $"["$ 或者 $"]"$ 无法配对，
只能奇数位置的和偶数位置的配对，不然中间的个数是奇数个，
没法配对，这个时候就需要一个 $"("$  或者  $")"$ 来转换，
那么前缀和处理即可
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int readint(){
	int x=0,f=1;char s=getchar();
	#define sc (s=getchar())
	while(s<'0'||s>'9'){
		if(s=='-')
			f=-1;
		sc;
	}
	while(s>='0'&&s<='9'){
		x=(x<<3)+(x<<1)+(s^48);
		sc;
	}
	#undef sc
	return x*f;
} 
int Fabs(int x){
	if(x<0)
		x=-x;
	return x;
}
char s[maxn];
int pre[maxn]; 
int main (){
	int t=readint();
	while(t--){
		scanf("%s",s+1);
		int n=strlen(s+1);
		for(int i=1;i<=n;i++){
			pre[i]=pre[i-1];
			if(s[i]=='['||s[i]==']')
				pre[i]+=(i%2?1:-1);
		}
		int q=readint();
		while(q--){
			int l=readint(),r=readint();
			printf("%d\n",Fabs(pre[r]-pre[l-1]));
		} 
	}
	return 0;
}
```

---

## 作者：xuyifei0302 (赞：1)

读完题，我们发现只有将中括号变为小括号需要花费 $1$ 的代价。所以，我们可以不考虑方向的因素。我们考虑合法的情况，即相邻两个中括号之间有偶数个小括号。因为要有偶数个小括号，所以中括号的下标一定是一奇一偶。所以我们考虑使用三个前缀和来记录这段区间内中括号的总数、下标为奇数的中括号总数以及下标为偶数的中括号的总数。所以，最后的花费为区间内中括号的数量减去下标为奇数的中括号总数和下标为偶数的中括号的总数的较小值的两倍。

接下来是代码环节：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, q, sum[1000005], sum1[1000005], sum2[1000005];
string s;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> s >> q;
		int len = s.size();
		s = " " + s;
		for (int i = 1; i <= len; i ++) {
			sum[i] = sum[i - 1], sum1[i] = sum1[i - 1], sum2[i] = sum2[i - 1];
			if (s[i] == '[' || s[i] == ']') {
				sum[i] ++;
				if (i % 2 == 1) {
					sum1[i] ++;
				} else {
					sum2[i] ++;
				}
			}
		}
		while (q --) {
			int l, r;
			cin >> l >> r;
			cout << sum[r] - sum[l - 1] - min(sum1[r] - sum1[l - 1], sum2[r] - sum2[l - 1]) * 2 << "\n";
		}
		sum[0] = sum1[0] = sum2[0] = 0;
	}
	return 0;
}
```

---

## 作者：Φρανκ (赞：1)

题意：有小括号和中括号共 $n$ 个，可以任意翻转其方向。求至少需要将多少个中括号变为小括号以使该括号序列合法。

核心思想：前缀和

解：

首先，可以发现，只要中括号序列合法并且所有中括号内部都有偶数个小括号，则可以将中括号内的小括号两两分组，并将中括号外的小括号围绕中括号安排使序列合法。如：在 $12$ 个括号长的序列中 $2,7,10,11$是中括号，则有：

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11| 12|
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | 
| ( | [ | ( | ( | ) | ) | ] | ( | ) | [ | ] | ) |  |  |  |  |  |  |

然后可以发现，只要奇数位与偶数位上中括号数量相等，就可以将它们一一对应以满足上述条件。对于每个初始序列，可以用前缀和来存储中括号位置（奇数位记为 $1$，偶数位记为 $-1$），再求出奇偶位置中括号数量差的绝对值即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long t, n, q, l, r, s[1000001];
char ch[1000001];
int main()
{
	cin>>t;
	for(int i=1; i<=t; i++)
	{
		memset(ch, 0, sizeof(ch));
		memset(s, 0, sizeof(s));
		cin>>ch+1>>q;
		n=strlen(ch+1);
		for(int j=1; j<=n; j++)
			if(ch[j]=='[' || ch[j]==']')
				if(j%2==1)
					s[j]=s[j-1]+1;
				else
					s[j]=s[j-1]-1
			else
				s[j]=s[j-1];//计算前缀和
		for(int j=1; j<=q; j++)
		{
			cin>>l>>r;
			cout<<abs(s[r]-s[l-1])<<endl;//计算差值
		}
	}
	return 0;
}
```

---

## 作者：Dovе (赞：1)

## 题目大意

&#8195;&#8195;给定一个括号序列，同类括号如 $'('$ 与 $')'$ 和 $'['$ 与 $']'$，可以直接转换，而不同类括号可以花费 $1$ 的代价转化。问将 $[l,r]$ 区间括号序列合法的最小费用。

## 大致思路

&#8195;&#8195;设 $a[i]$ 为到 $i$ 时的匹配费用。

&#8195;&#8195;对于一对括号，必然有一个在奇数位上，一个在偶数位上。我们假定将 $'['$ 与 $']'$ 保留，小括号转化为中括号。对于在奇数位上的小括号（不一定是左括号），$a[i] = a[i - 1] + 1$。对于在偶数位上的小括号，$a[i] = a[i - 1] - 1$。表示匹配。

&#8195;&#8195;那么，我们得到如下：

```cpp
a[i] = a[i - 1];
if (s[i - 1] == '(' || s[i - 1] == ')') a[i] += (i - 1 & 1 ? 1 : -1);

```

&#8195;&#8195;查询时只需要将 $a[r] - a[l - 1]$ 即可完成查询。

## $Code$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 50;

int n;
int a[maxn];
char s[maxn];

signed main()
{
    ios::sync_with_stdio(false);
    register int T;
    cin >> T;
    while (T--)
    {
        cin >> s;
        cin >> n;
        memset(a, 0, sizeof a );
        register int len = strlen(s); 
        for (register int i = 1; i <= len; ++i)
        {
            a[i] = a[i - 1];
            if (s[i - 1] == '(' || s[i - 1] == ')') a[i] += (i - 1 & 1 ? 1 : -1);
        } 

        while (n--)
        {
            register int l, r;
            cin >> l >> r;
            cout << abs(a[r] - a[l - 1]) << endl;
        }   
    }

    return 0;
}
```

### 致谢

&#8195;&#8195;感谢 ["Dragon_in_Bed"](https://www.luogu.com.cn/user/65289) 的提醒，之前的 $Code$ 数组 $a$ 调用时越位了，现已更正，可放心食用。

---

## 作者：Hisaishi_Kanade (赞：0)

第一种操作等价于任意调换括号方向。第二种操作相当于小括号中括号相互转化。

考虑一种策略，钦定先进行第二种操作再进行第一种操作。我们容易发现的是，对于任意一个长度为偶数的仅包含小括号的串可以不需要花费将它变得合法。

那么我们直接考虑中括号的配对。两个中括号能够匹配的充要条件是两个中括号之间有偶数个括号并且这些括号可以匹配。那么显然这两个括号的位置奇偶性不同。

所以直接统计一个区间内位置为奇数的括号数和偶数的括号数。设为 $x,y$，当 $x=y$ 时必然可以。

当 $x>y$ 时，因为我们要花费最小，显然不会去动 $y$。因为动了 $y$，$x$ 就需要更多的来和他配平。当 $x<y$ 时同理。

不难想到答案是 $|x-y|$。策略是将大的那个一直减到和小的那个相等。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=1e6+5;
int pre[2][N]; char str[N];
int n, i, j, t, l, r, q;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s", str+1); n=strlen(str+1); rep(i, 1, n) pre[0][i]=pre[1][i]=0;
		rep(i, 1, n) if(str[i]=='[' || str[i]==']') ++pre[i&1][i];
		rep(i, 1, n) pre[0][i]+=pre[0][i-1], pre[1][i]+=pre[1][i-1];
		scanf("%d", &q);
		while(q--)
		{
			scanf("%d %d", &l, &r);
			printf("%d\n", abs((pre[0][r]-pre[0][l-1])-(pre[1][r]-pre[1][l-1])));
		}
	}
	return 0;
}
```

---

## 作者：lingfunny (赞：0)

想起了之前做的一道 trie 维护可持久化栈的题目：[UOJ#327. 【UTR #3】去月球](https://uoj.ac/problem/327)。

类似这种思路的话，这题可以拓展。

记圆括号为 $\texttt{a}$，方括号为 $\texttt{b}$。

模拟一下栈，对于一个前缀，栈最后会剩下形如 $\texttt{abab...}$ 或者 $\texttt{baba...}$。

> 对于区间 $[l,r]$ 询问，可以用前缀 $l-1$ 和前缀 $r$ 的栈状态回答：如果 $l-1$ 的状态是 $a_1,a_2,\dots,a_x$，加入 $[l,r]$ 后，变成 $a_1,a_2,\dots,a_y$，其中两段的 $\operatorname{lcp}$ 为 $a_1,a_2,\dots,a_k$。区间 $[l,r]$ 内无法匹配的括号数量即为 $x+y-2k$。证明如下：
> 1. 如果区间 $[l,r]$ 中的一段完美匹配没有被用来配对 $l-1$ 的栈，那么这段完美匹配不会被用来贡献答案，理由显然，因为这一段完美匹配根本不会影响 $l-1$ 的栈状态。
> 2. 如果区间 $[l,r]$ 中的一段完美匹配的部分被用来配对 $l-1$ 的栈，会发现这一段仍然不会修改 $l-1$ 的栈状态。因为如果完美匹配的其中一个左括号用来匹配 $l-1$，右括号就一定会填回原来的位置。

记一下剩下的数量和开头，就可以快速求 $\operatorname{lcp}$。不过答案是无法匹配的括号数量除以 $2$（改一个括号可以消掉两个括号）。

可以拓展到有多种括号，这种做法的括号匹配和括号种类数没有关系。

```cpp
// Problem: G. Changing Brackets
// From: Codeforces - Codeforces Round #748 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1593/G
// Time: 2022-06-24 18:19
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 1e6+10;

int n, op[mxn], len[mxn], stk[mxn], top;
char s[mxn];

inline void solve() {
	scanf("%s", s+1);
	n = strlen(s+1);
	top = 0;
	for(int i = 1; i <= n; ++i) {
		int o = s[i] == '[' || s[i] == ']';
		if(top && stk[top] == o) --top;
		else stk[++top] = o;
		if(top) op[i] = stk[1];
		len[i] = top;
	}
	int q; scanf("%d", &q);
	for(int l, r; q--; ) {
		scanf("%d%d", &l, &r); --l;
		if(op[l] == op[r]) printf("%d\n", (max(len[r], len[l]) - min(len[r], len[l])) / 2);
		else printf("%d\n", (len[r] + len[l]) / 2);
	}
}

int main() {
	int tt;
	scanf("%d", &tt);
	while(tt--) solve();
}
```

---

