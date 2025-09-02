# Almost Regular Bracket Sequence

## 题目描述

You are given a bracket sequence $ s $ consisting of $ n $ opening '(' and closing ')' brackets.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

You can change the type of some bracket $ s_i $ . It means that if $ s_i =  $ ')' then you can change it to '(' and vice versa.

Your task is to calculate the number of positions $ i $ such that if you change the type of the $ i $ -th bracket, then the resulting bracket sequence becomes regular.

## 样例 #1

### 输入

```
6
(((())
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
()()()
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1
)
```

### 输出

```
0
```

## 样例 #4

### 输入

```
8
)))(((((
```

### 输出

```
0
```

# 题解

## 作者：一扶苏一 (赞：4)

## Description

给定一个长度为 $n$ 的小括号序列，求有多少个位置满足将这个位置的括号方向反过来后使得新序列是一个合法的括号序列。即在任意一个位置前缀左括号的个数不少于前缀右括号的个数，同时整个序列左右括号个数相同

## Input

第一行是一个整数 $n$ 代表序列长度

下面一行是括号序列

## Output

输出一行一个数字代表的答案

## Hint

$1~\leq~n~\leq~10^6$

## Solution

考虑一个位置，如果是左括号，那么能将其变成右括号当且仅当：

>整个序列左括号个数比右括号多 $2$
>
>在这个位置之前，所有位置的前缀左括号个数都不少于前缀右括号个数
>
>在这个位置和这个位置之后，在修改后所有位置的前缀左括号个数都不少于前缀右括号个数

我们将第三条转化一下，由于在修改之后左括号个数减一，右括号个数加一，于是我们可以将第三条改为

> 在这个位置和这个位置之后，修改前所有位置的前缀左括号个数都比前缀右括号个数至少多两个

这样一个位置能不能修改就仅与原序列有关了。

若果是右括号，也同理进行分析，将两个改为 $-2$ 个即可。

于是我们处理一下前缀左括号个数-右括号个数。

考虑第二条限制，等价于 $[1,pos]$ 这些前缀中的最小值不小于 $0$。于是我们对这些前缀求一个前缀最小值，就可以做到 $O(1)$ 判断了。

对于第三条限制，等价于 $[pos,n]$ 这些前缀中的最小值不小于 $2$。于是我们对这些前缀求一个后缀最小值，也可以做到 $O(1)$ 判断了。

这个位置是右括号的情况同理。细节参考代码

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 1000010;

int n, ans;
int cnt[maxn], pre[maxn], post[maxn];
char MU[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) {
		do {MU[i] = IPT::GetChar();} while ((MU[i] != '(') && (MU[i] != ')'));
		if (MU[i] == '(') cnt[i] = cnt[i - 1] + 1;
		else cnt[i] = cnt[i - 1] - 1;
	}
	if ((cnt[n] != 2) && (cnt[n] != -2)) return puts("0") & 1;
	pre[0] = maxn; post[n + 1] = maxn;
	for (rg int i = 1; i <= n; ++i) pre[i] = std::min(pre[i - 1], cnt[i]);
	for (rg int i = n; i; --i) post[i] = std::min(post[i + 1], cnt[i]);
	for (rg int i = 1; i <= n; ++i) {
		if (MU[i] == '(') {
			if ((cnt[n] == 2) && (post[i] >= 2) && (pre[i - 1] >= 0)) ++ans;
		} else {
			if ((cnt[n] == -2) && (post[i] >= -2) && (pre[i - 1] >= 0)) ++ans;
		}
	}
	qw(ans, '\n', true);
	return 0;
}
```

---

## 作者：F_Mu (赞：3)

**题意**

给定一个长度为 $n$ 的小括号序列，求有多少个位置满足将这个位置的括号方向反过来后使得新序列是一个合法的括号序列。即在任意一个位置前缀左括号的个数不少于前缀右括号的个数，同时整个序列左右括号个数相同。

**分析**

括号序列显然采取前缀和思想，将$'('$记做$1$，将$')'$记做$-1$，记为$sum[]$数组，并统计$'('$的前缀和，即为$suml[]$数组，统计$')'$的前缀和，即为$sumr[]$数组。

可以发现，对于某一个序列，只能翻转$'('$或$')'$一种类型，分类进行分析：

$(1)'('$比$')'$多$2$个，则翻转$'('$可以使得$sum[n]$变为$0$。考虑翻转第$i$位的$'('$会产生的影响。对于$i\leq j\leq n$来说，所有的$sum[j]$都减去$2$，所以要保证所有的$sum[]$都大于0，即找到$i$，有

+ $1\leq k <i$,$sum[k]>=0$
+ $i < j \leq n$,$sum[j]>=2$
+ $sum[i]=1$

答案即为$i$~$n$中$'('$数量。

$(2)'('$比$')'$少$2$个，可以通过翻转字符串并将所有的$'('$和$')'$翻转获得第$(1)$种情况。也可以通过考虑翻转第$i$位的$')'$会产生的影响，对于$i\leq j\leq n$来说，所有的$sum[j]$都加上$2$，所以要保证所有的$sum[]$都大于0，即找到$i$，有

+ $1\leq k <i$,$sum[k]>=0$
+ $i < j \leq n$,$sum[j]>=-2$
+ $sum[i]=-1$

答案即为$1$~$i$中的$')'$数量。

$(3)$其他情况输出$0$即可，存在已经为括号序列的字符串，也存在不可能满足条件的字符串。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
#define int ll
using namespace std;
const int maxn = (ll) 1e6 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;
int sum[maxn];
int suml[maxn];
int sumr[maxn];
char s[maxn];

signed main() {
    start;
    int n;
    cin >> n;
    cin >> (s + 1);
    for (int i = 1; i <= n; ++i) {
        suml[i] = suml[i - 1];
        sumr[i] = sumr[i - 1];
        if (s[i] == '(')
            sum[i] = sum[i - 1] + 1, ++suml[i];
        else
            sum[i] = sum[i - 1] - 1, ++sumr[i];
    }
    if (sum[n] == 2) {
        for (int i = 1; i <= n; ++i)
            if (sum[i] < 0) {
                cout << 0;
                return 0;
            }
        int l = n;
        for (; l > 0; --l)
            if (sum[l] == 1)
                break;
        cout << suml[n] - suml[l];
    } else if (sum[n] == -2) {
        for (int i = 1; i <= n; ++i)
            if (sum[i] < -2) {
                cout << 0;
                return 0;
            }
        int l = 1;
        for (; l <= n; ++l)
            if (sum[l] == -1)
                break;
        cout << sumr[l];
    } else
        cout << 0;
    return 0;
}
```



---

## 作者：wnsyou (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1095E)

# 题意

有一个长度为 $n$ 的括号序列。

求有多少个位置使得改变了该位置的括号种类可以使得括号序列合法。

# 思路

令左括号为 $1$，右括号为 $-1$，且这个序列所有数之和为 $x$。

首先分为三种情况。

1. $x = 2$，那么说明左括号多了一个（一个右括号变一个左括号会使得 $x$ 减少 $2$），要选择一个左括号变成右括号。
2. $x = -2$，那么说明右括号多了一个，要选择一个右括号变成左括号。
3. $x < -2$ 或 $x > 2$ 或 $-2 < x < 2$，答案必将为 $0$，可以直接输出。

### 对于情况一

设前 $i$ 个括号序列的和为 $sum_i$。

首先，我们来观察一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ijpf374q.png)

在这种情况里，虽然 $x = 2$，但是仍然没有答案。Why？

合法的括号序列，有一个条件，那就是**在任何时候，左括号的数量都不能比右括号少**！

所以，我们可以推出第一个条件：

- 可以作为答案的位置 $i$ 必然要满足 $\sum\limits_{1 \leqslant j < i}{(sum_ j\geqslant 0)} = i - 1$

那么，当我们第一次发现 $sum_{i-1} < 0$ 时，就可以退出找答案的循环了，后面的所有位置**均不可成为答案。**

再来观察一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nja3e0ly.png)

位置 $2$ 和位置 $3$ 给答案有贡献，那为啥位置 $1$ 没有贡献呢？

虽然我们知道，位置 $1$ 一旦变化，就会出现 $sum_1 = -1$ 的情况，可究竟怎样筛掉这些情况呢？

手推一下，我们会发现：把位置 $i$ 上的左括号变为右括号，会使得 $sum_j-2\ (j \geqslant i)$。

那么就好办了，只要 $\min\limits_{i \leqslant j \leqslant n}\{sum_j\} \geqslant 2$ 且位置 $i$ 为左括号，这个位置即可对答案产生贡献。

### 对于情况二

同理，只要 $\min\limits_{i \leqslant j \leqslant n}\{sum_j\} \geqslant -2$ 且位置 $i$ 为右括号，这个位置即可对答案产生贡献。

### 总结

- 如果 $\left\vert x \right\vert \neq 2$，答案必为 $0$。
- 如果 $x = 2$，答案为满足要求的 $i$ 的个数。
  - $s_i = ($。
  - $\sum\limits_{1 \leqslant j < i}{(sum_ j\geqslant 0)} = i - 1$ 且 $\min\limits_{i \leqslant j \leqslant n}\{sum_j\} \geqslant 2$。
- 如果 $x = -2$，答案为满足要求的 $i$ 的个数。
  - $s_i = )$。
  - $\sum\limits_{1 \leqslant j < i}{(sum_ j\geqslant 0)} = i - 1$ 且 $\min\limits_{i \leqslant j \leqslant n}\{sum_j\} \geqslant -2$。

用前缀和思想处理出 $sum$ 数组，再求一遍 $sum$ 的后缀最小值，统计答案即可。

# Code

```cpp
#include <iostream>
#include <string>

using namespace std;

const int N = 1e6 + 10;

string s;
int n, sum[N], mi[N], ans; // sum 为前缀和，mi 为 sum 的后缀最小值

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> s;
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1];
    if (s[i - 1] == '(') { // 处理好前缀和
      sum[i]++;
    } else {
      sum[i]--;
    }
  }
  mi[n] = sum[n];
  for (int i = n - 1; i; i--) { // 处理后缀最小值
    mi[i] = min(mi[i + 1], sum[i]);
  }
  for (int i = 1; i <= n; i++) {
    if (sum[n] == 2 && mi[i] >= 2 && s[i - 1] == '(') { // 判断，情况 1
      ans++;
    } else if (sum[n] == -2 && mi[i] >= -2 && s[i - 1] == ')') { // 判断，情况 2
      ans++;
    }
    if (sum[i] < 0) { // 处理 i + 1 时，sum[i] < 0，结束循环
      break;
    }
  }
  cout << ans;
  return 0;
}
```



---

## 作者：mango2011 (赞：1)

这题这能说是“双无产品”：无思维难度，无代码难度。

判断一个序列是否是合法括号序列只有两个条件：

1) 左右括号数相等（容易判断）。

2) 不存在位置 $p$，使得 $s_{1,2,3,\dots,p}$ 中左括号数量大于右括号数量。

令 $pre_i$ 为 $s_{1,2,3,\dots,i}$ 中左括号数减去有括号数。令 $d_i=\min\{pre_j\}(i\le j\le n)$。

对于一个括号 $i$，使得左括号数大于等于右括号数的位置可能在其左侧（不包含自身），可能在其右侧（包含自身），那么我们只需要讨论：

1) 维护左侧的所有位置，每次暴力更新即可。

2) 考虑 $d_i$，看看把这个括号修改之后，能否让 $d_i\ge 0$。

3) 注意检查括号总数。

维护上面的 $3$ 个东西，我们就可以解决问题了，时空复杂度均为 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int pre[maxn],d[maxn];
string s;
int main()
{
    ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);//读入优化
    int n,i,ans=0;
    cin>>n>>s;//输入
    s='*'+s;
    for(i=1;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if(s[i]=='(')
        {
            pre[i]++;
        }
        else
        {
            pre[i]--;
        }
    }
    d[n+1]=1e9;
    for(i=n;i>=1;i--)
    {
        d[i]=min(d[i+1],pre[i]);
    }
    bool fl=1;
    for(i=1;i<=n;i++)
    {
        if(fl)
        {
            if(s[i]=='(')
            {
                //pre[n]==2 为全局数量的判断
                if(pre[n]==2&&d[i]>=2)
                {
                    ans++;
                }
            }
            else
            {
                //pre[n]==-2 为全局数量的判断
                if(pre[n]==-2&&d[i]>=-2)
                {
                    ans++;
                }
            }
        }
        if(pre[i]<0)
        {
            fl=0;
        }
        //fl 为 flag 的缩写，维护的是当前位置的左侧是否存在不合法的位置
    }
    cout<<ans<<endl;//输出
    return 0;//功德圆满，我佛保佑 AC
}

```

---

## 作者：开始新的记忆 (赞：1)

题目大意：给你一个长度为n的括号字符串，让你在最多改变一个括号的情况下使括号匹配（改变为'('-->')'，')'-->'('），并输出需要改变的括号的位置（没有则输出0）

思路：此题思维难度较大，但是代码实现难度较小。不难发现，当我们算了一下最后两种括号的差时，发现如果有答案的话差值只为-2，0，2，不然是不会有解的。
所以只需要先看后面最少会成多少，然后依次扫一遍，符合就加，不符合就不变，然后随时判断一下这种情况可不可能出现即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int cnt[maxn],n,x=0;
string s;

int main() 
{	cin>>n>>s;
    for(int i=0;i<n;++i) 
	{
        if(s[i]=='(') 
			x++;
        else 
			x--;
        cnt[i]=x;
    }
    for(int i=n-2;i>=0;--i)
        cnt[i]=min(cnt[i+1],cnt[i]);
    int ans=0,b=0;
    for(int i=0;i<n;++i) 
	{
        if(s[i]=='(') 
		{
            if(cnt[i]>=2 && x==2) 
				ans++;
            b++;
        } 
		else 
		{
            if(cnt[i]>=-2 && x==-2) 
				ans++;
            b--;
        }
        if(b<0)
            break;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：liuli688 (赞：0)

### 思路
由于“序列是一个合法的括号序列需要任意一个位置前缀左括号的个数不少于前缀右括号的个数”，所以考虑前缀和，将 `(` 视为 $1$，`)` 视为 $-1$。

将位于 $i$ 位的 `(` 翻转会使区间 $[i, |s|]$ 的前缀和减少 $2$，反之加 $2$。如果该区间在减完后发现任意一位小于 $0$ 则不匹配。于是可以再后缀取 $\min$，对于每一位检查这一位往后的最小值是否小于 $2$（或 $-2$）。

还有一种可能是这一位前面的括号序列就不合法，可以再开一个前缀取 $\min$ 维护每一位往前的最小值。
### 代码
```cpp
#include <cstdio>
#include <algorithm>

constexpr int N = 1e6 + 2;
int n, sum[N], pre[N], suf[N], ans;
char s[N];

signed main()
{
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + (s[i] == '(' ? 1 : -1);
    if (sum[n] != 2 and sum[n] != -2)
        return printf("0\n"), 0;
    pre[0] = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i)
        pre[i] = std::min(pre[i - 1], sum[i]);
    suf[n + 1] = 0x3f3f3f3f;
    for (int i = n; i; --i)
        suf[i] = std::min(suf[i + 1], sum[i]);
    if (sum[n] == 2)
        for (int i = 1; i <= n; ++i)
            ans += (s[i] == '(' and pre[i - 1] >= 0 and suf[i] >= 2);
    else
        for (int i = 1; i <= n; ++i)
            ans += (s[i] == ')' and pre[i - 1] >= 0 and suf[i] >= -2);
    printf("%d\n", ans);
    return 0;
}
```

---

