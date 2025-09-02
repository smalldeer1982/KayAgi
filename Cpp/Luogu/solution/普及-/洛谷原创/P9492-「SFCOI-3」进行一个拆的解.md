# 「SFCOI-3」进行一个拆的解

## 题目背景

**公告：Subtask 0 数据有误，现已更改。**

------------

三岁的小明非常不喜欢完整的东西，他甚至连序列都想要拆掉。

## 题目描述

给定序列 $a_1\dots a_n$，小明想要把它拆成两个子段 $[1, l][l + 1, n](1 \leq l \lt n)$，即 $a_1\dots a_l$ 和 $a_{l+1}\dots a_n$。

由于小明强迫症很严重，他不希望对于这两个子段，其中一个是另一个的 **子序列**，换句话说，他不希望其中一个子段可以通过删掉若干（可能为 $0$）个元素变成另一个。

在父母出门的时候，小明终于找到了把序列拆开的机会！所以，他想知道，是否存在一种拆解的方式满足：任意一个子段都不是另一个子段的子序列。

## 说明/提示

### 样例解释

对于第一个序列，所有拆分方式有：

- $\lbrace 1 \rbrace,\lbrace 2,1,2,1 \rbrace$。
- $\lbrace 1,2 \rbrace,\lbrace 1,2,1 \rbrace$。
- $\lbrace 1,2,1 \rbrace,\lbrace 2,1 \rbrace$。
- $\lbrace 1,2,1,2 \rbrace,\lbrace 1 \rbrace$。

从任何地方拆开都是不合法的——较短的那个序列都是另一个序列的子序列。

对于第二个序列，其中一种合理的拆分方式为 
$\lbrace 1,2,1,1,2 \rbrace,\lbrace 1,0 \rbrace$。

### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 0（15 points）：$a_i = 0$。
- Subtask 1（15 points）：$n = 10$，保证数据随机生成。
- Subtask 2（30 points）：$n$ 为偶数。
- Subtask 3（40 points）：无特殊限制。

对于所有数据，$1\leq T \leq 10^5$，$2 \leq n \leq 10^5$，$1 \leq \sum n \leq 10^6$，$0 \leq a_i \leq 100$。

## 样例 #1

### 输入

```
2
5 1 2 1 2 1
7 1 2 1 1 2 1 0```

### 输出

```
NO
YES```

# 题解

## 作者：Rei_Sen (赞：8)

やあやあ，这里是铃仙酱 ~。

由于辉夜~~昨晚上~~今早上睡得太晚了，于是现在回房间睡觉了，所以我就来代替她来写这篇题解。

这里辉夜的思路好像和题解的不大一样，辉夜是按照 $n$ 的奇偶性来做了一个小小分类讨论，具体的说：

1. 当 $n$ 为偶数时，若我们想让其没有划分方案，需要保证串 $S$ 可以变成两个相同串 $S'$ 拼起来，这个证明是十分显然的：

>	考虑如果我们的串 $S$ 不能具有上述性质，那我们从中间直接切分就是一个合法的划分方案，故无论如何必须要保证上述性质。
>				
>	现在考虑的是为什么这样对于其他划分位置也不存在合法的构造方案，很简单，如果我们将串 $S$ 劈成两个不等长的串 $S_1$ 和 $S_2$，那么其中较短的串一定是较长的串的子串，因为较长的串一定完整且顺序不变的包含了串 $S'$，而较短的串一定是 $S'$ 的子串，所以能够保证其他划分位置也不存在合法的构造方案。

2. 当 $n$ 为奇数时，我们可以把它认为是在 $n - 1$ 的情况下添了一个元素 $X$，那么根据第一个讨论，我们不难得出 $X$ 的位置只可能是以下三种：

	- $S'S'X$
   
   - $S'XS'$
   
   - $XS'S'$
   
   其中，较为显然的是，第一种和第三种可以被看做同一种情况，所以我们只需要对 $S'S'X$ 和 $S'XS'$ 这两种情况进行讨论：
   
   1. $S'S'X$：
   
      考虑现在我们将 $S$ 划分为两部分 $[1,\dfrac{|S|}{2} + 1]$（设为 $S_1$）和 $[\dfrac{|S|}{2}+2, |S|]$（设为 $S_2$）两部分，那么此时显然，只有 $S_2$ 为 $S_1$ 的后缀的时候才能使得当前划分不合法，那么我们就有结论 $X = S'[1]$，由于我们的串 $S = S'S'X$，所以就有结论 $X = S[1]$。
   
      那么，现在让我们移动划分位置，不难得到和讨论一中一样的情况，故可以证明此时不存在合法方案。
   
   2. $S'XS'$：
   
      这个比较厉害一点，这里我们对 $X$ 不存在任何要求，因为可以把 $X$ 看成一个占位置的元素，无论它归于哪个部分，都不影响讨论一的结论（因为是形成子序列），证明……太简单了，这个就不说了，大家可以手玩一下 qwq。
   
      那么，既然我们可以把 $X$ 看成一个占位置的元素，为什么 $X$ 不能放到其他位置呢？原因很简单，我们将 $X$ 放到中间，这样可以保证 $X$ 一定处于一个较大的划分中，否则我们就需要将 $X$ 匹配进去，这样就会使得将 $X$ 丢进短的一部分的划分方案是合法的，所以我们只能将 $X$ 放到中间。如果放到两边的话，则会变为第一种情况。

综上，我们就不难写出代码啦 ~

```cpp
// Powered by NEET. awa
#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 1e5+10;

int n;
int a[MAX_LEN];

bool check1()
{
	int jbegin = n / 2 + 1;
	for(int i = 1,j = jbegin; i <= n / 2; ++i, ++j) {
		if(a[i]!=a[j])
			return false;
	}
	return a[1] == a[n];
}

bool check2()
{
	int jbegin = n / 2 + 2;
	for(int i = 1, j = jbegin; i <= n / 2; ++i, ++j) {
		if(a[i] != a[j])
			return false;
	}
	return true;
}

void solve()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	if(!(n & 1)) {
		int jbegin = n / 2 + 1;
		for(int i = 1, j = jbegin; i <= n / 2; ++i,++j) {
			if(a[i] != a[j]) {
				printf("YES\n");
				return;
			}
		}
		printf("NO\n");
	} else {
		if(check1() || check2()) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}
}

int main()
{
	int T = 0;
	scanf("%d", &T);
	while(T--) {
		solve();
	}
}
```



---

## 作者：liruixiong0101 (赞：7)

## P0 题意：
给定一个长度为 $n$ 的数组 $a_1,a_2,\dots,a_n$，请问是否有一个数 $l$（$l\in[1,n)$），$[1,l]$ 为 $[l+1,n]$ 子序列，或 $[l+1,n]$ 为 $[1,l]$ 的子序列，若有所有的 $l$ 都合法输出 `NO` 否则输出 `YES`。

## P1 思路：
### 1.暴力：
暴力思路很明显，枚举 $l$，再 $O(n)$ 判断这个 $l$ 是否合法即可，判断 $l$ 是否合法可以用双指针实现。

### 2.正解：
我们来自己手算一下第一个样例，我们会发现当 $l\ge \lfloor \frac{n}{2} \rfloor$ 时，每一个 $l$ 都可行，为什么呢？

- 当 $l=3$ 时，两个序列分别为 `1 2 1` 和 `2 1`，此时 `2 1` 为 `1 2 1` 的子序列。
- 当 $l = 4$ 时，两个序列分别为 `1 2 1 2` 和 `1`，此时第一个序列增加了一个 `2`，而第二个序列减少了一个 `2`，`1` 也为 `1 2 1 2` 的子序列。

研究完样例，我们很容易发现一个性质：  
若 $b$ 序列为 $a$ 序列的子序列，那么在 $b$ 序列中去掉一个元素 $c$，在 $a$ 序列中增加此元素 $c$， $b$ 序列还为 $a$ 序列的子序列。

我们从子序列的定义入手：
> 若一个序列 $a$ 可以通过删除任意数量元素（可以为 $0$ 个），从而让序列 $a$ 变为另一个序列 $b$，那么称 $b$ 为 $a$ 的子序列。

很明显，我们在 $b$ 序列中删除元素不会影响 $b$ 为 $a$ 的子序列这一条件，同样，我们在 $a$ 序列中增加一个元素也不会影响此条件。这样我们得到了上述性质：若 $b$ 序列为 $a$ 序列的子序列，那么在 $b$ 序列中去掉一个元素 $c$，在 $a$ 序列中增加此元素 $c$， $b$ 序列还为 $a$ 序列的子序列。

同理，我们可以得出一下结论：

- 若 $l=\lfloor\frac{n}{2}\rfloor$ 时，这个 $l$ 成立，那么 $l\ge\lfloor\frac{n}{2}\rfloor$ 所有的 $l$ 都成立。
- 若 $l=\lceil\frac{n}{2}\rceil$ 时，这个 $l$ 成立，那么 $l\le\lceil\frac{n}{2}\rceil$ 所有的 $l$ 都成立。

所以我们只需判断 $l=\lfloor\frac{n}{2}\rfloor$ 和 $l=\lceil\frac{n}{2}\rceil$ 的 $l$ 是否合法即可，判断 $l$ 是否合法与暴力判断相同。

## P3 代码：
代码很简单，这里只提供 AC 记录了。  
<https://www.luogu.com.cn/record/119061135>

---

## 作者：信息向阳花木 (赞：3)

~~赛时猜了一个结论，证明完以后就跑路了。~~

看完数据范围 $\sum n \leq 10^6$~~，这么大，一定有猫腻~~，就可以发现，我们要用 $O(n)$ 的时间复杂度解决这道题目。

想到两个序列越长，互相为对方子序列的几率越小。所以我们想让两个子串序列尽量长，就从中间截取。

想一下，如果从 $i$ 点断开序列，两个子串序列分别为 $a_1,a_2,...,a_{i}$ 和 $a_{i+1},a_{i+2},..,a_n$。如果前者是后者的子序列，那么 $i$ 向左移一定也不满足条件。如果后者是前者的子序列，那么 $i$ 向右移动也一定不满足条件。

所以，当 $n$ 为偶数时，$i = \frac{n}{2}$。若不满足条件，则 $a_1,a_2,...a_i$ 和 $a_{i+1},a_{i+2}, a_n$ 完全相同，$i$ 左右移动必定不满足条件。当 $n$ 为奇数时，$i = \frac{n-1}{2}$ 或 $\frac{n+1}{2}$，若两个都不满足，则 $i$ 左右移动也不满足。

讨论 $n$ 的奇偶性，让 $i$ 按上面结论取值，用双指针判断是否满足条件就可以了。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;

int t, n;
int a[N];

bool check(int x)
{
    bool success = 0;
    if(x <= n - x)
    {
        int i = 1, j = x + 1;
        while (i <= x && j <= n) if(a[i] != a[j]) { success = 1; break; } else i ++, j ++;
        if(!success) return 0;
        if(x != n - x)
        {
	        success = 0;
	        i = 1, j = x + 2;
	        while (i <= x && j <= n) if(a[i] != a[j]) { success = 1; break; } else i ++, j ++;
	        if(!success) return 0;
	    }
    }
    else
    {
    	success = 0;
        int i = 1, j = x + 1;
        while (i <= x && j <= n) if(a[i] != a[j]) { success = 1; break; } else i ++, j ++;
        if(!success) return 0;
        success = 0;
        i = 2, j = x + 1;
        while (i <= x && j <= n) if(a[i] != a[j]) { success = 1; break; } else i ++, j ++;
        if(!success) return 0;
	}
    return 1;
}

int main()
{
    scanf("%d", &t);
    while (t -- )
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
        bool flag;
        if(n % 2 == 0) flag = check(n / 2);
        else flag = (check(n / 2) | check(n / 2 + 1));
        
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：Exp10re (赞：3)

简单而有趣的结论题，放在 T1 简直太棒了。

## 解题思路

假设将原序列拆成两个序列的断点位置为第 $p$ 个数之后，那么靠左的序列长度为 $p$，靠右的序列长度为 $n-p$。

那么我们尝试证明以下结论：

1. 当 $p \leq n-p$ 时，若 $a_1\cdots a_p$ 是 $a_{p+1}\cdots a_n$ 的子序列，那么右移断点一定更优。
1. 当 $p \geq n-p$ 时，若 $a_{p+1}\cdots a_n$ 是 $a_1\cdots a_p$ 的子序列，那么左移断点一定更优。

尝试用反证法证明结论 $1$。假设在 $a_1\cdots a_p$ 与 $a_L\cdots a_R$ 全等（$p+1\leq L \leq R \leq n$，即 $a_L\cdots a_R$ 是 $a_{p+1}\cdots a_n$ 的子序列）的情况下左移断点 $p$ 而非右移断点 $p$，那么产生的新的序列为 $a_1\cdots a_{p-1}$ 和 $a_p\cdots a_n$。容易得知，此时 $a_1\cdots a_{p-1}$ 与 $a_L\cdots a_{R-1}$ 全等，而 $a_L\cdots a_{R-1}$ 又必定是 $a_p\cdots a_n$ 的子序列，因此左移一定更劣。想要找到一个满足条件的解仅能右移断点。

结论 $2$ 亦可以用相同方法证明。

那么在这两个结论的约束下，我们就能得知找到一个解得最优方案：

- 若 $n$ 为偶数，那么分成 $a_1\cdots a_{n/2}$ 与 $a_{n/2+1}\cdots a_n$ 两段一定最优。
- 若 $n$ 为奇数，那么有两种方案：分成 $a_1\cdots a_{n/2}$ 与 $a_{n/2+1}\cdots a_n$ 两段，或者分成 $a_1\cdots a_{n/2+1}$ 与 $a_{n/2+2}\cdots a_n$ 两段，都是最优方案。

使用以上结论容易证明该方案必定为最优方案，在此不再证明。

## 代码

当 $n$ 为奇数时实现细节较多，需要注意。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010];
bool check(int n,int l1,int l2)//双指针判断是否为子串 
{
	for(;l2<=n;l2++,l1++)
	{
		if(a[l1]!=a[l2])
		{
			return false;
		}
	}
	return true;
}
void work()
{
	bool flaga,flagb;
	int n,i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	if(n&1)
	{
		flaga=(check(n-1,1,n/2+1)||check(n,1,n/2+2));//断点为 n/2 之后 
		flagb=(check(n,1,n/2+2)||check(n,2,n/2+2));//断点为 n/2+1 之后 
		if(flaga&&flagb)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	else
	{
		if(check(n,1,n/2+1))
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	return;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)//多测 
	{
		work();
	}
	return 0;
}
```

然后就没了。

---

## 作者：_5t0_0r2_ (赞：3)

# 分析：
先放出结论：直接从中间划分，~~如果从中间划分可以的话就可以（废话）~~，否则就不行。

首先，如果一个序列 $b$ 是另一个序列 $c$ 的子序列，那么 $b$ 的所有子序列也都是 $c$ 的子序列。

当 $n$ 为偶数时，设 $b$ 为 $a_1,a_2 \dots a_{mid}$，$c$ 为 $a_{mid + 1},a_{mid + 2} \dots a_n$。如果把划分位置往前移一位，即新序列 $d$ 为 $a_1,a_2 \dots a_{mid - 1}$，$e$ 为 $a_{mid},a_{mid + 2} \dots a_n$。因为 $d$ 是 $b$ 的子序列，所以如果 $b$ 是 $c$ 的子序列（即 $b = c$）的话，$d$ 也是 $c$ 的子序列，而 $c$ 又是 $e$ 的子序列，所以 $d$ 是 $e$ 的子序列。那么划分位置一直往前移，$d$ 都是 $e$ 的子序列。

同理，因为 $b = c$，所以我们也可以说 $c$ 是 $b$ 的子序列，那么划分位置一直往后移，$d$ 都是 $e$ 的子序列。

当 $n$ 为奇数时，设 $mid = \lfloor \frac{1 + n}{2} \rfloor$，我们考虑从 $mid$ 和 $mid + 1$ 划分。

用类似的方法，可以推出，当在 $mid$ 划分不可以时，在 $mid$ 前划分肯定不行；当在 $mid + 1$ 划分不可以时，在 $mid + 1$ 后划分肯定也不行。

因此，如果从中间划分不行，不管怎么划分都不行。

时间复杂度为 $O(Tn)$，因为 $\sum n \leq 10^6$，可以通过此题。

---

## 作者：_Spectator_ (赞：3)

[可能更好的食用体验](/blog/523641/P9492) $|$ 
[题目传送门](/problem/P9492) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

这是一个构造题。首先，可以先将 $n$ 为偶数和 $n$ 为奇数两种情况考虑。

对于 $n$ 为偶数的情况，显然当 $a_1\dots a_{n/2}$ 与 $a_{n/2+1}\dots a_n$ 完全相同，即序列形如 $\tt ab\dots cab\dots c$ 时，无论如何拆分序列，都一定有其中的一段序列在另外一段中出现过（如果无法理解可以自己设计这样的序列试一试，我赛时就是这么做的）。

而对于 $n$ 为奇数的情况，令 $k=\frac{n+1}{2}$，继续将其分为两种情况：

1. $a_1\dots a_k$ 与 $a_k\dots a_n$ 完全相同，即形如 $\tt ab\dots cab \dots ca$，其中中间的 $\tt a$ 的位置为第 $k$ 位。
2. $a_1\dots a_{k-1}$ 与 $a_{k+1}\dots a_n$ 完全相同，即形如 $\tt ab\dots cdab\dots c$，其中 $\tt d$ 的位置为第 $k$ 位。

可以发现，当序列满足这两种情况之一，无论如何拆分序列，都有其中一段在另一段中出现过。

那么如何判断两段序列完全相同呢？可以借助两个指针轻松实现：
```cpp
int p=start1,q=start2;
while(q<=n&&a[p]==a[q])p++,q++;
if(q>n)//两个序列匹配成功
else //两个序列不相同
```

还有不明白可以看代码。时间复杂度 $O(n)$。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n;
int a[100005];
int main()
{
	for(cin>>T;T-->0;)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		if(n%2==1)//n 为奇数的情况
		{
			int p=1,q=n/2+1;//a[1...k] 与 a[k...n] 完全相同
			while(q<=n&&a[p]==a[q])p++,q++;
			if(q>n)cout<<"NO\n";
			else{
				p=1,q=n/2+2;//a[1...k-1] 与 a[k+1...n] 完全相同
				while(q<=n&&a[p]==a[q])p++,q++;
				if(q>n)cout<<"NO\n";
				else cout<<"YES\n";
			}
		}
		else{//n 为偶数的情况
			int p=1,q=n/2+1;//a[1...n/2] 与 a[n/2+1...n] 完全相同
			while(q<=n&&a[p]==a[q])p++,q++;
			if(q>n)cout<<"NO\n";
			else cout<<"YES\n";
		}
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

## 思路

考虑按照 $n$ 的奇偶性分类。

### 结论 $1$

如果 $n$ 是偶数，那么只需要检验拆分位置 $l=\frac{n}{2}$。

如果 $n$ 是奇数，那么只需要检验拆分位置 $l=\frac{n\pm1}{2}$。

很明显如果 $a$ 是 $b$ 的子序列，那么 $b$ 增多元素 $a$ 减少元素不影响 $a$ 是 $b$ 的子序列。所以在 $l$ 按照上面所说的检验后，如果得出拆分不合法（一边是另一边的子序列），那么无论 $l$ 如何移动，要么被归纳到了另一情况（例如将 $n$ 是奇数时的 $l=\frac{n+1}{2}$ 左移变成 $l=\frac{n-1}{2}$），要么就总是一边增加元素，一边减少元素，不影响减少的一边一定是增多的一边的子序列这一事实（因为对于奇数，减少的一边一定是最开始就少的一边，只有可能这边作为另一边的子序列；对于偶数，两边互为另一边的子序列就没有这个问题）。

检验一个序列是否是另一个序列的子序列已经可以做到 $O(n)$ 了，双指针移动即可。

### 代码

```cpp
int n;
int a[N];
vector <int> p1,p2;
bool check(int x){
	p1.clear();
	p2.clear();
	fr1(i,1,x){
		p1.pb(a[i]);
	}
	fr1(i,x+1,n){
		p2.pb(a[i]);
	}
	if(p1.size()<p2.size()){
		swap(p1,p2);
	}
	int poi1=0,poi2=0;
	while(poi1!=p1.size()&&poi2!=p2.size()){
		if(p1[poi1]==p2[poi2]){
			poi2++;
		}
		poi1++;
	}
	if(poi2==p2.size()){
		return 1;
	}
	return 0;
}
void solve(){
	cin>>n;
	fr1(i,1,n){
		cin>>a[i];
	}
	if(n%2==0){
		if(check(n/2)){
			cout<<"NO"<<'\n';
		}
		else{
			cout<<"YES"<<'\n';
		}
	}
	else{
		if(check(n/2)&&check((n+1)/2)){
			cout<<"NO"<<'\n';
		}
		else{
			cout<<"YES"<<'\n';
		}
	}
}
```

但是我不想写双指针啊！太急了！怎么办？

### 结论 $2$

**使用结论 $1$ 的情况下**在检验位置 $l$ 的时候可以检验一边是否是另一边的子段。

这个结论的存在其实导致了赛时许多人乱写判断子序列然后写过了……

首先这个结论在 $n$ 是偶数的时候很显然，因为 $n$ 是偶数的时候 $l$ 拆出的两边长度一样，检验一边是否是另一边的子序列就是检验一边是否是另一边的子段。

考虑 $n$ 是奇数的时候这个结论什么时候会判断出错。很明显如果一边不是另一边的子序列，那么也不可能判断出一边是另一边的子段。所以只有可能一边是另一边的子序列，但不是子段，这种情况会判断错误。

当原序列构成类似 `a x b | a b` 的时候（$a,b$ 为**非空**序列，$x$ 为一个数），我们把拆分的位置放在 `|` 处时判断子段会认为这是一种合法的分拆，但实际上并不是。

所以我们把 $b$ 的最后一个元素 $d$ 拆分出来，留下一个长度为 $|b|-1$ 的前缀 $c$，然后试着构造 $a+x+c$ 是 $d+a+b$ 的一个子序列但不是子段，使得它在两种情况都判断出错，以为有合法拆分 WA 掉。（这里的加号表示连接，后同）

可以注意到 $a+x+c$ 刚好比 $d+a+b$ 少一个元素。不妨考虑少的这一个元素 $p$ 的位置。经过分类讨论这个元素的位置，可以发现：

- 这个少的元素 $p$ 原本不在 $b$ 当中，我们从后往前考虑。因为 $|c|<|b|$，所以 $c$ 一定是 $d+a+b$ 的后缀（唯一缺失的元素已经在前面了）。给 $c$ 往前塞一个 $x$ 就可以覆盖掉 $b$ 的部分，所以这个缺少的元素不会影响 $x+c=b$ 这件事。
- 这个少的元素原本在 $b$ 当中，我们从前往后考虑。因为 $|a+x|=|d+a|$，所以 $a+x$ 一定是 $d+a+b$ 的前缀（唯一缺失的元素已经在后面了），所以这个缺失的元素不会影响 $a+x=d+a$ 这件事。

把这两种情况带回 $a+x+c$ 与 $d+a+b$，可以发现总是存在一边成为另一边的子段。这与我们的构造目的相违背，所以无法构造出使结论 $2$ 不成立的例子。

所以按照结论 $2$ 去写判断一边是否是另一边的子段是正确的！

### 代码

```cpp
int n;
string s;
int x;
bool check(int x){
	string s1=s.substr(0,x);
	string s2=s.substr(x,n-x);
	if(s1.length()>s2.length()){
		swap(s1,s2);
	}
	if(s1+s2[s2.length()-1]==s2||s2[0]+s1==s2){
		return 1;
	}
	return 0;
}
void solve(){
	s="";
	cin>>n;
	fr1(i,1,n){
		cin>>x;
		s+=x+'0';
	}
	if(n%2==0){
		if(s.substr(0,n/2)==s.substr(n/2,n/2)){
			cout<<"NO"<<'\n';
		}
		else{
			cout<<"YES"<<'\n';
		}
	}
	else{
		if(check(n/2)&&check((n+1)/2)){
			cout<<"NO"<<'\n';
		}
		else{
			cout<<"YES"<<'\n';
		}
	}
}
```

写法比较丑请见谅。

[结论 $1$ 的 AC 记录](https://www.luogu.com.cn/record/118898723)

[结论 $2$ 的 AC 记录](https://www.luogu.com.cn/record/118995122)

---

## 作者：Vct14 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P9492)。

我们分 $n$ 的奇偶情况讨论一下。

------------


- 若 $n$ 为偶数。

令 $l=\dfrac{n}{2}$。则序列 $a$ 的两个子段 $[1,l]$ 和 $[l+1,n]$ 的长度相同。则若其中一个是另一个的子序列，那么两个子段里每一个对应的值都相等。即 $a_i=a_{i+l} (1 \leqslant i\leqslant l)$。

此时，如果令 $l'= l-j(0\leqslant j\leqslant l-1)$，即 $l'<l$，则 $[1,l']$ 是 $[1,l]$ 的子串，$[1,l]$ 是 $[l+1,n]$ 的子串（见上文），而 $[l+1,n]$ 又是 $[l'+1,n]$ 的子串，所以 $[1,l']$ 是 $[l'+1,n]$ 的子串。

若令 $l'=l+j(0\leqslant j\leqslant l-1)$（由题目知 $l<n$），也可以按如上证法证明 $[l'+1,n]$ 是 $[1,l']$ 的子序列。

那么只要有 $a_i=a_{i+l} (1 \leqslant i\leqslant l)$，就有无论怎样分，都会有其中一个是另一个的子序列，答案为 `NO`。

否则符合题目要求，答案为 `YES`。

```c++
if(n%2==0){
	int l=n/2;
	string ans="NO";
	for(int i=1; i<=l; i++) if(a[i]!=a[i+l]){ans="YES";break;}
	out(ans);
}
```

- 若 $n$ 为奇数。

令 $l_1=\left\lfloor\dfrac{n}{2}\right\rfloor$。若 $[1,l_1]$ 是 $[l_1+1,n]$ 的子序列，还是可以用上文证法证出对于 $l_1'=l_1- j(0\leqslant j\leqslant l_1-1)$，$[1,l_1']$ 是 $[l_1'+1,n]$ 的子序列。

在判断子序列时，令 $p$ 为此时 $a_i$ 与其对应的数不相等的数量，初始为 $0$。由于 $[1,l_1]$ 的个数一定比 $[l_1+1,n]$ 的个数小 $1$，所以当 $p=2$ 时，$[1,l_1]$ 一定不是 $[l_1+1,n]$ 的子序列。若 $a_i$ 与其对应的数 $a_{i+l+p}$ 不相等，则 $p$ 需要加 $1$。

```c++
bool isSub(){//isSubsequence1
	int p=0;
	for(int i=1; i<=l; i++){
		if(a[i]!=a[i+l+p]){
			if(a[i]!=a[i+l+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}
```

令 $l_2=\left\lceil\dfrac{n}{2}\right\rceil$。同样，若 $[1,l_2]$ 是 $[l_2+1,n]$ 的子序列，还是可以用上文证法证出对于 $l_2'=l_2+ j(0\leqslant j\leqslant l_2-1)$，$[l_2'+1,n]$ 是 $[1,l_2']$ 的子序列。

```c++
bool isSub2(){//isSubsequence2
	int p=0;
	for(int i=l+2; i<=n; i++){
		if(a[i]!=a[i-l-1+p]){
			if(a[i]!=a[i-l-1+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}
```

若上面两个都满足，则对于所有 $l(1\leqslant l\leqslant n)$，都有分出的其中一个是另一个的子序列。那么只要有其中一个不满足，则符合题目要求，答案为 `YES`。

```c++
if(n%2==1) if(!isSub() || !isSub2()) ans="YES";
```

完整代码：

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=100002;

//以下为快读程序
char *p1,*p2,buf[N];
#define r() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=r();
    while(ch<48||ch>57){
        if(ch=='-') f=-1;
        ch=r();
    }
    while(ch>=48 && ch<=57) x=x*10+ch-48,ch=r();
   	return x*f;
}

//以下为输出程序
void write(string x){
	cout<<x;
	puts("");
}

int a[N];
int l,n;

bool isSub(){//isSubsequence1
	int p=0;
	for(int i=1; i<=l; i++){
		if(a[i]!=a[i+l+p]){
			if(a[i]!=a[i+l+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}

bool isSub2(){//isSubsequence2
	int p=0;
	for(int i=l+2; i<=n; i++){
		if(a[i]!=a[i-l-1+p]){
			if(a[i]!=a[i-l-1+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}

int main(){
	int t=read();
    while(t--){
        n=read();
        for(int i=1; i<=n; i++) a[i]=read();
        string ans="NO";
        l=n/2;
        if(n%2==0) for(int i=1; i<=l; i++) if(a[i]!=a[i+l]){ans="YES";break;}
		if(n%2==1) if(!isSub() || !isSub2()) ans="YES";
		write(ans);
    }
    return 0;
}
```

------------


当然，也可以把 $n$ 为偶数的情况一起用 `isSub()` 函数判断。此函数改为：

```c++
bool isSub(){//isSubsequence
	int p=0;
	for(int i=1; i<=l; i++){
		if(a[i]!=a[i+l+p]){
			if(n%2==0) return false;//添加这一句 
			if(a[i]!=a[i+l+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}
```

判断部分也需要修改。

```c++
if(n%2==0 && !isSub()) ans="YES";
if(n%2==1 && (!isSub() || !isSub2())) ans="YES";
```

完整代码：

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=100002;

//以下为快读程序
char *p1,*p2,buf[N];
#define r() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=r();
    while(ch<48||ch>57){
        if(ch=='-') f=-1;
        ch=r();
    }
    while(ch>=48 && ch<=57) x=x*10+ch-48,ch=r();
   	return x*f;
}

void write(string x){
	cout<<x;
	puts("");
}

int a[N];
int l,n;

bool isSub(){//isSubsequence
	int p=0;
	for(int i=1; i<=l; i++){
		if(a[i]!=a[i+l+p]){
			if(n%2==0) return false;//添加这一句 
			if(a[i]!=a[i+l+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}

bool isSub2(){
	int p=0;
	for(int i=l+2; i<=n; i++){
		if(a[i]!=a[i-l-1+p]){
			if(a[i]!=a[i-l-1+p+1]) return false;
			else p++;
			if(p==2) return false;
		}
	}
	return true;
}

int main(){
	int t=read();
    while(t--){
        n=read();
        for(int i=1; i<=n; i++) a[i]=read();
        string ans="NO";
        l=n/2;
        if(n%2==0 && !isSub()) ans="YES";
		if(n%2==1 && (!isSub() || !isSub2())) ans="YES";
		write(ans);
    }
    return 0;
}
```

---

## 作者：zxh923 (赞：1)

# P9492 「SFCOI-3」进行一个拆的解 题解

### 思路  

当我看到 $ \text{Subtask 2}$ 的限制为 $n$ 为偶数时，我就想到，难道 $n$ 的奇偶性对判断有影响吗？  

然后我们便可以得到如下想法：如果 $n$ 为奇数，我们把它分为两段，假设其长度为 $7$，我们把它分为前 $3$ 后 $4$,如果前一段被包含在后一段中，那么我们把第 $3$ 个数归到后一段，前一段也仍然一定被包含在长的那段中。

所以我们可以得出：对于奇数个数，我们可以把它分为前 $n \div 2$ 个，后 $n \div 2+1$ 个或者前 $n \div 2+1$ 个后 $n \div 2$ 个，如果我们对比其中发现有对应的两项不同，我们可以把对应的 $flag$ 标记为 $0$。但是，长的那段有两种方案去对应短的那段，我们需要去枚举所有对应方案。

而偶数个数，则只能被划分为前后长度相同的两个数列。

所以在奇数中有 $4$ 种可能，偶数同理可得，前后长度皆为 $n \div 2$ 即可，有 $1$ 种可能。

### 代码

```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std; 
int t,n,a[100005];
int main(){
//这是思考的样例过程
//1 7 
//1 2 3 || 4 3 2 | 1(不选) 可能1 
//1 2 3 || 4(不选) | 3 2 1 可能2 
//1(不选) | 2 3  4 || 3 2  1 可能3
//1 2 3 | 4(不选) || 3 2  1 可能4
//1 6
//1 2 3 || 1 2 3 唯一的可能 
//双竖杠代表划分开来的位置 ，单竖杠代表选择对应的位置 
	cin>>t;
	while(t--){
		bool f0=1,f1=1,f2=1,f3=1;//判断指标 
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];//读入部分 
		}
		if(n%2==1){//奇数长度的情况 
			for(int i=1,j=n/2+2;j<=n;i++,j++){
				if(a[i]!=a[j]){//如果两者不同 ,可能1成立 
					f0=0;
					break;
				}
			} 
			for(int i=1,j=n/2+1;j<n;i++,j++){
				if(a[i]!=a[j]){//如果两者不同 ,可能2成立 
					f1=0;
					break;
				}
			}
			for(int i=1,j=n/2+2;i<=n/2;i++,j++){
				if(a[i]!=a[j]){//如果两者不同 ,可能3成立 
					f2=0;
					break;
				}
			}
			for(int i=2,j=n/2+2;i<=n/2+1;i++,j++){
				if(a[i]!=a[j]){//如果两者不同 ,可能4成立 
					f3=0;
					break;
				}
			}
			if((f0||f1)&&(f2||f3)){//如果两种划分的方式都至少有一种为1,(即被包含) ,输出NO 
				cout<<"NO"<<'\n';
				continue;
			}
			else{//反之输出YES 
				cout<<"YES"<<'\n';
			}
		}
		else{//偶数长度的情况 
			for(int i=1,j=n/2+1;j<=n;i++,j++){
				if(a[i]!=a[j]){//只要有1个不一样,一定就不会被包含,输出YES 
					cout<<"YES"<<'\n';
					f0=0;
					break;
				}
			}
			if(f0){//反之输出NO 
				cout<<"NO"<<'\n';
				continue;
			}
		}
	}
	return 0;
}
```


---

## 作者：lemon_qwq (赞：0)

暴力判断所有子段时间复杂度过高，我们可以想一下等价的简单做法。

明显，我们只需要从中间分成两个子段，然后判断是否包含即可。

大概原理是因为最多的字串都全部包含了，所以更简单的子段也肯定包含。

$n$ 为偶数的部分比较简单，加上特判 $a_i$ 全是 $0$ 的情况能获得 $60$ 分。

直接暴力判断前后两个子段是否相同即可。

$n$ 为奇数部分考虑的情况比较多：

假设有一个长度为五的数组 $a,b,c,d,e$。

我们可以拆成 $\color{red}\{a,b\}\color{black},\color{blue}\{c,d,e\}$ 或者 $\color{red}\{a,b,c\}\color{blacl},\color{blue}\{d,e\}$。

前者判断 $a,b$ 是否等于 $c,d$ 和 $a,b$ 是否等于 $d,e$。

后者判断 $d,e$ 是否等于 $a,b$ 和 $d,e$ 是否等于 $b,c$。

这样每次操作双指针 $O(n)$ 处理即可。

放一下代码吧，写的有点乱，其实不用这么麻烦的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[1000005];
bool b=0;
void pd1(){
	int n1=n/2+1,n2=n/2+2,f=2;
	for(int i=1;i<=n/2;i++,n1++){
		if(a[i]!=a[n1]){
			f--;
			break;
		}
	}
	n1=n;
	for(int i=n/2;i>=1;i--,n1--){
		if(a[i]!=a[n1]){
			f--;
			break;
		}
	}
	if(!f){
		cout<<"YES"<<endl;
		return ;
	}
	f=2;
	n1=n/2+2;
	for(int i=1;n1<=n;i++,n1++){
		if(a[i]!=a[n1]){
			f--;
			break;
		}
	}
	n1=n;
	for(int i=n/2+1;n1>=n/2+2;i--,n1--){
		if(a[i]!=a[n1]){
			f--;
			break;
		}
	}
	if(!f){
		cout<<"YES"<<endl;
		return ;
	}
	cout<<"NO"<<endl;
	return ;
}
void pd(){
	b=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=0){
			b=1;
		}
	}
	if(b==0){
		cout<<"NO"<<endl;
		return ;
	}
	if(n%2==0){
		n/=2;
		n++;
		int l=1,r=n,r1=r;;
		while(1){
			if(l==r1){
				cout<<"NO"<<endl;
				return ;
			}
			else if(a[l]!=a[r]){
				cout<<"YES"<<endl;
				return ;
			}
			l++,r++;
		}
	}else{
		pd1();
	}
	return ;
}
int main(){
	cin>>T;
	while(T--){
		pd();
	}
	return 0;
}
```

~~谁家好人输入写判断里啊~~。

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9492)

先给大家讲一下我赛时的思路。

可以看到 Subtask $2$ 的一个性质是 $n$ 为偶数。看到偶数就会想到 $2$，会想到除以 $2$ 没有余数。除以 $2$ 又能联想到对半分。所以我就在猜会不会在拆分的时候直接对半分就一定是最优的，如果对于奇数就把最中间的数分类讨论，分到左序列或右序列。于是我就斗胆交了一发，结果过了。

后面想了一下这个结论的证明，发现好像还挺简单的。如果要保证一个序列不为另一个序列的子序列，那么一定要让它们的长度相近。举个例子，像序列 $2,3,1,3$ 和 $1,2,3$，若 $1,2,3$ 要成为 $2,3,1,3$ 的子序列，那么它们之间不同的元素就只有 $1$ 个，由 $2,3,1,3$ 构成子序列 $1,2,3$ 的选择不选的项只有 $1$ 个，情况只有 $4$ 种（我们暂且认为 $1,2,3$ 有 $4$ 项），但如果是 $2,3,1,3,1$ 和 $2,3$，它们之间对于构成子序列 $2,3$ 的选则不选的项有 $3$ 个，情况数明显超过前一种。而且构成序列 $2,3$ 只需两个元素，概率比构成 $1,2,3$ 要来得大。

既然要让两个序列长度相近，那么对半分就可以了。你把 $n$ 除以 $2$ 后两个序列的长度之差最多就为 $1$。对于 $n$ 为奇数，需要分类讨论中间的数属于左边的序列还是右边的序列。

判断是否为另一个序列的子序列就不用我说了吧，这个倒是很简单，看我代码里的注释。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int f=1;
		a[0]=0;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]!=a[i-1]) f=0;
		}
		if(f){puts("NO");continue;}
		if(n%2==0)
		{
			int now=1;                     //表示长度小的序列现在匹配到了第几项
			for(register int i=n/2+1;i<=n;i++)
			{
				if(a[i]==a[now]) now++;         //如果这一项匹配成功now++
				if(now>n/2) break;            //如果全部匹配完就退出。
			}
			f=now>n/2;                     //判断是否全部匹配完
			if(!f) puts("YES");
			else puts("NO");
			continue;
		}
		int now=1;
		for(register int j=n/2+1;j<=n;j++)
		{
			if(a[j]==a[now]) now++;
			if(now>n/2) break;
		}
		f=now>n/2;
		if(!f){puts("YES");continue;}
		now=n/2+2;
		for(register int j=1;j<=n/2+1;j++)
		{
			if(a[j]==a[now]) now++;
			if(now>n) break;
		}
		f=now>n;
		if(!f) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：zhzkiller (赞：0)

## 题目描述
这道题要求我们将一个序列 $a$ 拆分成非空的两段，使得这两段互相不为另一个的子序列。

## 解题思路
很容易想到一个暴力算法：$O(n)$ 枚举分割处，再 $O(n^2)$ 判断小段是否为大段的子序列。整体时间复杂度 $O(n^3)$。

考虑进行优化。不难发现，如果较大的段是另一个更大的段的子序列，那么这个较大段中的所有子序列都必然是更大段的子序列。从此入手，我们便可以直接将序列分成两段检查，更小的段则忽略不计即可。整体复杂度在 $O(n)$ 到 $O(n^2)$ 之间，视 $n$ 的奇偶性而定，需要一点卡常和优化的小技巧，实际测试最慢不到 500ms。

本算法仅供通过本题，适合初学者。如果需要学习正解请前往其他大佬们的高阶题解。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010;

int t;
int n,a[N];

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);bool flag=true;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int cnt=(n&1)?n/2+1:n/2;
		if(!(n&1))
		{
			for(int i=1;i<=cnt;i++)
			{
				if(a[i]!=a[i+cnt])
				{
					puts("YES");
					flag=false;
					break;
				}
			}
			if(flag) puts("NO");
		}
		else
		{
			bool flag2=false;flag=false;
			for(int i=1,j=cnt;j<=n;j++)
			{
				if(a[i]==a[j]) i++;
				else j=j-i+1,i=1;
				
				if(i==cnt)
				{
					flag=true;
					break;
				}
			}
			if(!flag)
			{
				puts("YES");
				continue;
			}
			
			for(int i=1,j=cnt+1;i<=cnt;i++)
			{
				if(a[i]==a[j]) j++;
				else i=i-(j-cnt)+1,j=cnt+1;
				
				if(j==n+1)
				{
					flag2=true;
					break;
				}
			}
			if(!flag2)
			{
				puts("YES");
				continue;
			}
			
			puts("NO");
		}
	}
	return 0;
}
```

### 代码中细节/优化

1.如果 $n$ 为偶数可以直接 $O(n)$ 扫一半查一半。

2.如果 $n$ 为奇数则需要将序列中间数分别放在左右各考虑一次。

3.如果能够确定答案立即下一步，不要左右都查，会 TLE 两个点。别问我怎么知道的。

---

## 作者：DengDuck (赞：0)

我们考虑把问题分成两部分，一部分考虑前面比后面大，一部分考虑后面比前面大，然后分别处理。

对于前面比后面小的情况，我们发现割点的位置具有单调性，因为如果 $x$ 是合法的，就说明 $[x+1,n]$ 中一定有与前缀 $[1,x]$ 的子序列，而 $[1,x-1]$ 作为 $[1,x]$ 的一部分，自然也是有的。

同理，对于不合法的 $x$,在 $[x+1,n]$ 中 $[1,x]$ 不存在，包含其的 $[1,x+1]$ 就更不能存在了。

考虑二分答案，对于每个答案，双指针匹配（考场上这个写错了呜呜呜）。

第二种情况是类似的，你可以直接把数组倒过来。

因此时间复杂度为 $\mathcal O (n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
LL T,n,a[N],b[N];
bool pd(LL x)
{
	LL t1=1,t2=x+1;
	while(t1<=x&&t2<=n)
	{
		if(a[t1]==a[t2])t1++;
		t2++;
	}
	if(t1==x+1)return false;
	return true;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			b[n-i+1]=a[i];
		}
		LL l=1,r=n/2,flg1=0;
		while(l<=r)
		{
			LL mid=(l+r)/2;
			if(pd(mid))
			{
				flg1=1;
				break;
			}
			else l=mid+1;
		}
		for(int i=1;i<=n;i++)
		{
			a[i]=b[i];
		}
		l=1,r=n/2;
		LL flg2=0;
		while(l<=r)
		{
			LL mid=(l+r)/2;
			if(pd(mid))
			{
				flg2=1;
				break;
			}
			else l=mid+1;
		}		
		if(flg1||flg2)
		{
			puts("YES");
		}
		else
		{
			puts("NO");
		}
	}
}
```

---

