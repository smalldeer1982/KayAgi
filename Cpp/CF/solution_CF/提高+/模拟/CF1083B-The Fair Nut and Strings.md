# The Fair Nut and Strings

## 题目描述

最近，Fair Nut 写下了 $k$ 个长度为 $n$ 的字符串，这些字符串仅由字母 "a" 和 "b" 组成。他计算了 $c$ —— 即至少是其中一个已写字符串前缀的字符串的数量。每个字符串只计数一次。

后来，他把写有这些字符串的纸弄丢了。他记得所有写下的字符串的字典序都不小于字符串 $s$，且不大于字符串 $t$。他想知道：他能得到的 $c$ 的最大值是多少。

字符串 $a$ 的字典序小于字符串 $b$ 当且仅当满足以下条件之一：

- $a$ 是 $b$ 的前缀，且 $a \ne b$；
- 在 $a$ 和 $b$ 第一个不同的位置，$a$ 的字母在字母表中比 $b$ 的对应字母更靠前。

## 说明/提示

在第一个样例中，Nut 可以写下字符串 "aa"、"ab"、"ba"、"bb"。这 $4$ 个字符串的所有前缀 "a"、"b" 也是至少某个字符串的前缀。总共有 $6$ 个字符串。

在第二个样例中，Nut 可以写下字符串 "aba"、"baa"、"bba"。

在第三个样例中，只能写下两个不同的字符串。如果这两个都写下，则 $c=8$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 4
aa
bb
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 3
aba
bba
```

### 输出

```
8
```

## 样例 #3

### 输入

```
4 5
abbb
baaa
```

### 输出

```
8
```

# 题解

## 作者：一扶苏一 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10235368.html)

## Description

有 $k$ 个长度为 $n$ 的只含 $a$ 或 $b$ 字符串，并不知道它们具体是多少，只知道它们的字典序不小于字符串 $A$，同时不大于字符串 $B$。定义一个字符串是合法的当且仅当它是这 $k$ 个字符串之一的前缀（如果它是多个串的前缀那么只计算一次）。求合法的字符串最大可能是多少

## Input

第一行是两个整数 $n$ 和 $k$

下面两行，第一行是长度为 $n$ 的字符串 $A$，第二行是长度为 $n$ 的字符串 $B$

## Output

输出一个数代表答案。

## Hint

$1~\leq~n~\leq~5~\times~10^5~,~1~\leq~k~\leq~10^9$

## Solution

我们考虑假如对这 $k$ 个字符串建出一棵~~踹~~Trie树，那么显然一个节点对应一个合法的字符串，答案即为树上节点个数。于是我们的问题即被转化为了最大化Trie树上的节点个数。考虑在一个节点，在合法的条件下孩子数为 $2$ 的答案显然不劣于孩子数为 $1$ 的答案。于是我们依照此按照层数进行贪心，尽可能的多分节点即可。考虑因为最后一层的节点最多有 $k$ 个，所以当算到一层的节点数不小于 $k$ 时，后面就无需枚举，直接分配给每层 $k$ 个节点计算答案即可。

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

const int maxn = 500010;

ll n, k, ans;
char MU[maxn], CU[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(k);
	do MU[1] = IPT::GetChar(); while ((MU[1] > 'z') || (MU[1] < 'a'));
	for (rg int i = 2; i <= n; ++i) MU[i] = IPT::GetChar();
	do CU[1] = IPT::GetChar(); while ((CU[1] > 'z') || (CU[1] < 'a'));
	for (rg int i = 2; i <= n; ++i) CU[i] = IPT::GetChar();
	ll pre = 1;
	for (rg int i = 1; i <= n; ++i) {
		pre <<= 1;
		if (MU[i] == 'b') --pre;
		if (CU[i] == 'a') --pre;
		if (pre >= k) {
			ans += 1ll * k * (n - i + 1);
			break;
		}
		ans += pre;
	}
	qw(ans, '\n', true);
	return 0;
}
```

---

## 作者：liuyifan (赞：4)

## 模拟(可能用到字典树的思想)

来发一篇自认为可读性好一点的题解

我们可以把所有可选的字符串看成一棵字典树。

然后我们发现，如果第i层的节点个数<=k,那么这一层的前缀都可以加入集合(不到k个）

反之，如果第i层的节点个数>k，那这一层的前缀最多只能有k个加入集合。这些前缀长度为i且互不相等

所以只需要算出每一层节点的个数并加入贡献， 就能得到答案

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long//下文中所有ll都会被自动替换为long long
#define inf 0x3f3f3f3f//同上
using namespace std;//c++必备
char a[100005],b[100005];
ll n,k,ans,tmp=1;
int main()
{
    scanf("%lld%lld%s%s",&n,&k,a+1,b+1);//char数组下标从1开始的读入方法
    for(reg int i=1;i<=n;i++)
	{
        tmp<<=1;//位运算,等价于tmp*=2
        if(b[i]=='a')tmp--;
        if(a[i]=='b')tmp--;
        if(tmp>k)tmp=k+1;//只能放k个的情况
        ans+=min(tmp,k);//上述两种情况(前面文字)判断加入集合个数
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Hoks (赞：3)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF1083B)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf1083b)内食用应该不会更佳。

~~duel 到的 +1。~~
## 思路分析
首先看到这题我想到了字典树，先考虑一下暴力处理，总共所有的字符串中取出 $k$ 个构造字典树，计算前缀，在所有情况中取一个最大值。

虽然这种方法是不可行的，但是我们可以从中推出正解。观察题目发现每位可能填的字符只有 $a,b$。

所以考虑每位的个数为 $res$。

首先如果没有 $A,B$ 两个字符串的两端限制的话，每位都有两种情况，所以先乘上 $2$。

接着，如果这一位 $A$ 是 $b$ 那可能性就会少一种，同理，如果这一位 $B$ 是 $a$ 的话，可能性也会少一种。

而 $ans$ 的值就是各个长度的 $res$ 的值之和。这里注意，因为最多只能选择 $k$ 个字符串，所以 $ans$ 一次最多只能加 $k$。 
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,res=1,ans;
char a[500010],b[500010];
int read()
{
    char c=getchar();int x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main()
{
    n=read(),k=read();
    scanf("%s%s",a+1,b+1);
    for(int i=1;i<=n;i++)
    {
    	res=(res<<1)-(a[i]=='b')-(b[i]=='a');
    	res=min(res,k+1);ans+=min(res,k);
        //这里写res和k+1取最小值是为了防止溢出的同时保证后面加的都是k
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：小馄饨 (赞：2)

我来分享另外一种贪心思路， 虽然这种思路要比题解区其他 dalao 的方法要复杂一些。

当然，一个显然的思路就是转化为如何让 Trie 树中的节点最多。

$k = 1$ 时，显然答案为 $n$ ，此时只能插入一个长度为 $n$ 的字符串。

如果 $k \ge 2$， 则字符串 $A$ 和 $B$ 是一定要选取的，我们可以证明如果存在最优解不包含 $A$ 和 $B$，那么就一定存在最优解包含 $A$ 和 $B$。大体思路是可以将一个既不是 $A$ 又不是 $B$ 的字符串改成选择 $A$ 或者 $B$ ，节点数不会变少，这里由于版面原因不再细述。

接着我们考虑插入字符串时要怎样走才合法。首先，它一定走过 $A$ 和 $B$ 的最长公共前缀，然后在 $B$ 走 `b` 边时往 `a` 走， $A$ 走 `a` 边时往 `b` 走，之后就可以随便走了。其中有一次在 $A$ 和 $B$ 分叉时出现。

最后考虑随便走的范围，由题意这是一棵完全二叉树，我们第一次走这里时就会新增和树高一样大的节点数，但是再来走这棵树时由于之前走过了一些节点所以就无法再新建那么多节点了。可以归纳证明，我们从一棵树高为 $H$ 的完全二叉树中抽取出一条链，那么会剩下树高为 $1, 2, \dots , H-1$ 的完全二叉树。我们下一次走的时候，就可以贪心走最高的完全二叉树。

下面是代码。我们在选择了 $A$ 和 $B$ 之后，贪心地选取最高的二叉树来统计答案。这其中涉及到区间加的操作，而这里可以懒惰增加——计算出之前操作对该值的影响，从而降低时间复杂度。

```cpp
#include <cstdio>

const int MAXN = 1000010; 
char s1[MAXN], s2[MAXN];

int tong[MAXN]; //用于维护当前各种树高的完全二叉树的数量

int n, k;
int main() {
	scanf("%d%d", &n, &k);
	scanf("%s%s", s1 + 1, s2 + 1);
	int dif;
	for(dif = 1; s1[dif] == s2[dif] && dif <= n; ++dif);
	if(s1[dif] > s2[dif]) {
		puts("0");
		return 0;
	}
	if(k == 1 || dif > n) {
		printf("%d", n);
		return 0;
	}
	for(int i = dif + 1; i <= n; ++i) {
		if(s1[i] == 'a')
			tong[n - i + 1] += 1;
		if(s2[i] == 'b')
			tong[n - i + 1] += 1;
	}
	long long int ans = n + n - dif + 1;
	k -= 2;
	long long int aris1 = 0; // 用于维护影响大小
	for(int i = n; i; --i) {
		tong[i] += aris1;
		if(k > tong[i])
			ans += 1ll * tong[i] * i,
			k -= tong[i],
			aris1 += tong[i];
		else{
			ans += 1ll * k * i;
			break;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：This_Rrhar (赞：1)

以样例二为例，建出字典树，那么实际上就是一棵完全二叉树：

![](https://cdn.luogu.com.cn/upload/image_hosting/28x9nmhg.png)

一条从根节点到叶节点的路径就是一个字符串。但是由于 $A$ 和 $B$ 限制了我们的想象，所以有些字符串是不可选的，叶节点只能选择为 $9\sim13$。

那么可供选择的字符串组成的字典树就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/dviw63js.png)

考虑如何计算前缀数量，显然前缀的一端为根节点，另一端为选定的字符串上的节点，那么前缀数量就是所有字符串上的节点的数量（不含根节点）。

考虑如何让前缀数量最大，显然若两个字符串存在 $x$ 个公共节点，那么会让答案减少 $x$，故应使字符串的公共节点尽量少，体现在字典树上就是**两个叶节点的 LCA 应当尽量靠近根节点**。例如上图中，若选择 $\{11,12,13\}$ 作为根节点，则其 LCA 劣于选择 $\{9,11,13\}$，故 $\{9,11,13\}$ 优于 $\{11,12,13\}$。

再考虑如何统计答案，显然答案最优时，每一层与根节点形成的前缀数量都是最大的，对于第 $i$ 层来说显然答案最大为 $k$ 或本层可选的节点数。

考虑计算某一层可能成为前缀的节点数，显然若 $A_i$ 为 `b` 和 $B_i$ 为 `a` ，均会产生不可能成为前缀的节点，为上一层可能成为前缀的节点数的两个儿子，再减去本层新产生的不可能成为前缀的节点即可。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;

long long now=2,ans;

string a,b;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k>>a>>b;
	for(size_t i=1;i<=n;i++,now<<=1)
	{
		if(a[i-1]=='b')now--;
		if(b[i-1]=='a')now--;
		if(now>=k)
		{
			ans+=(n-i+1)*k;
			break;
		}
		ans+=now;
	}
	cout<<ans;
}
```

---

## 作者：shao0320 (赞：1)

#### CF1083B The Fair Nut and Strings


 考虑已经有$k$个合法字符串，那么将其插入一棵$Trie$，节点数即为答案。

那么从根开始扩展按层计算贡献，这一层的点数是上一层的二倍，每次把超出边界的减掉即可，当这层节点数大于$k$时就无需计算了，因为最多只有$k$种，所以后边层的贡献也都为$k$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2000005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,k,now=1,ans;
char S[N],T[N];
signed main()
{
	n=read();k=read();
	scanf("%s",(S+1));
	scanf("%s",(T+1));
	for(int i=1;i<=n;i++)
	{
		now<<=1;
		if(S[i]=='b')now--;
		if(T[i]=='a')now--;
		if(now>=k)
		{
			ans+=k*(n-i+1);
			break;
		}
		ans+=now; 
	}
	printf("%lld\n",ans);
	return 0;
}
```





---

## 作者：Garbage_fish (赞：0)

## 分析

为了方便求前缀，我们需要一种东西将相同的前缀归在一起，因此很容易想到字典树，把所有可能出现的字符串的第 $i$ 位挂在树的第 $i$ 层，其中 `a` 放在左子树，`b` 放在右子树，直接拿**样例 #2** 上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tczzqsp9.png)

此时，从原点到任意一个节点的路径组成的字符串，都可能成为一个前缀，在看题目要求，为了让前缀数量最多，我们应该选择尽量多的分支，可以想到每一层能选择的最多分支即为 $\min(p,k)$，其中 $p$ 是本层节点的数量，所以本题的目标就变成了求每一层的节点数。

其中蓝色的是字符串 $A$，绿色的是字符串 $b$，黑色的是可选的，红色的是不可选的。

先看第一层，由于 $A_1$ 是 `a`，$B_1$ 是`b`，因此两个都可选，所以本层的字符的数量，也就是可选的前缀的数量为 $2$。

接着看第二层，若 $A_2$ 是 `a`，$B_2$ 是 `b`，则本层的前缀数量仍应该是上一层的两倍，但是因为 $A_2$ 是 `b`，因此少去了 `aa` 这种情况，`aa` 的儿子自然也全部不合法，不可能参与到后面的贡献，所以本层可选的数量是 $2\times2-1=3$。

第三层也同理，$B_3$ 是 `a`，`bbb` 的情况不合法，减掉一个。

此时，规律已经明显了：

对于第 $i$ 层，$p_i=2p_{i-1}$，其中 $p_0=1$，当 $A_i=\mathsf{b}$ 或 $B_i=\mathsf{a}$ 时，$p_i$ 分别减去 $1$。

## 做法

根据以上的思路，很容易得到以下的代码，但是有个究极坑点，$p$ 可能会溢出，但是由上面的推理我们可以得到 $p$ 对答案的贡献绝对比 $k$ 少，因此当 $p>k$ 时，我们可以直接把后面的都当 $k$ 处理了。

**[AC](https://www.luogu.com.cn/record/144686480) Code:**

```cpp
#include <bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
int n,k,ans,p=1;
string a,b;
signed main(){
	IOS;
	cin>>n>>k;
	cin>>a>>b;
	for(int i=0;i<n;i++){
		if(p>k){
			ans+=k;
			continue;
		}
		p*=2;
		if(a[i]=='b')p--;
		if(b[i]=='a')p--;
		ans+=min(p,k);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Nuisdete (赞：0)

题意转化一下就是在限制内选 $k$ 个字符串使得建出的 01 Trie 节点数最多。

节点数最多的话就考虑树上的叉分的越高越好，那么就一层一层建 Trie。

每一层，能分叉就叉，直到叉的数量等于 $k$ 了就不分了，这样一定是最优的。设层数为 $x$，每层增加的节点数量就是 $n - x + 1$，注意初始还有 $n$ 个节点。

维护一下两个限制字符串在每一层的第几个位置上就可以 $\mathcal{O}(n)$ 快速实现。

https://codeforces.com/contest/1083/submission/229373946.

---

## 作者：VenusM1nT (赞：0)

考虑没有限制的情况，如果把 $\forall \ S\in[A,B]$ 都插入到 trie 里去的话，那么答案就是点数总和。  
接下来考虑有限制，显然每层的点数不能超过 $k$ 个，否则一定不符合限制。同时如果对应这层的字符比较不优秀的话（即 $A_i=$ `b`，$B_i=$ `a` 这两种情况）也是要减去的。于是每层的点数等于上一层的两倍减去对应情况后，跟 $k$ 进行比较，如果 $\leq k$ 的话直接计入答案；如果 $>k$ 的话则令其等于 $k$，这样在下一层也可以取到上限 $k$。
```cpp
#include<bits/stdc++.h>
#define N 500000
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,k,ans;
char a[N+5],b[N+5];
signed main()
{
	scanf("%lld %lld",&n,&k);
	scanf("%s",a+1);
	scanf("%s",b+1);
	reg int cnt=1; 
	for(reg int i=1;i<=n;i++)
	{
		reg int tmp=cnt*2-(a[i]=='b')-(b[i]=='a');
		cnt=tmp>k?k+1:tmp;
		ans+=min(k,cnt);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

