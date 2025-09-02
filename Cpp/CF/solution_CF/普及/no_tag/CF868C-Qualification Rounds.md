# Qualification Rounds

## 题目描述

斯纳克和菲利普正在为即将到来的半决赛预赛做准备。他们有一个含有N个问题的银行，他们想选择任何非空子集作为问题集。  
有K个经验丰富的球队正在参加比赛。这些团队中的一些已经知道了一些问题。为了让比赛变得有趣，每个球队都应该知道不超过一半的问题。  
确定斯纳克和菲利普是否能做出有趣的问题集！

## 说明/提示

在第一个例子中，你不能制造任何有趣的问题，因为第一个团队知道所有的问题。

在第二个例子中，你可以选择第一个和第三个问题。

## 样例 #1

### 输入

```
5 3
1 0 1
1 1 0
1 0 0
1 0 0
1 0 0
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 2
1 0
1 1
0 1
```

### 输出

```
YES
```

# 题解

## 作者：三点水一个各 (赞：2)

## 题意

主办方要出若干个问题作为晋级半决赛的依据，但有一些问题已经被某些队伍知道了.

现在已知预备的（共n个，1<=n<=$10^{5}$）所有问题，以及k（1<=k<=4）支队伍对这些问题是否了解的情况（1表示知道，0表示不知道）。

现在请你计算，有没有存在可能的方案（**选择x个问题，x可以你自己订**），使每支队伍知道的问题**不超过**x的一半。

***

## 思路

把对于每个问题的每支队伍的知晓程度转换为数字，只需要将所有问题两两比较，判断是否有其一符合要求，即是答案。这一过程可以用**与运算**解决。

**如何证明算法正确？**

除去特殊情况：**有一个问题没有队伍知道**

对于任意两个问题，如果没有符合要求的解，

那么就意味着有一个或多个队伍知道n-1或n个问题。

在这种情况下，不管选择几个问题都不符题意~~（不信可以举反例）~~，

所以证明了算法的正确。

***

**CODE**
````
#include<cstdio>
#include<math.h>
int n,k,cnt[16],flag;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        int p=0,num;
        for(int j=1;j<=k;++j) 
	  scanf("%d",&num),p+=num*pow(2,j-1);
	cnt[p]++;
    }
    if(cnt[0]) flag=1;
    else for(int i=1;i<=k*k-2;++i)
           for(int j=1;j<=k*k-2;++j)
	     if(!(i&j)&&cnt[i]&&cnt[j]) 
	       flag=1;
    if (flag) printf("YES");
      else printf("NO");
}
```

---

## 作者：Jayun (赞：0)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF868C)

# 题目大意：

$n$ 个长 $m$ 的 01 串，问能否找到一个选择方案使得每一位 $0$ 的个数都不小于 $1$ 的个数。

$m\leq 4$。

# 正文:

这个问题有两个性质：

1. 手玩几个数据会发现方案中最多两个 01 串。
1. $m\leq4,2^m\leq16$，所以总共至多 $16$ 个串。

$n\leq16$，然后暴力 $\mathcal{O}(n^2)$。

# 代码：

```cpp
const int N = 1e5 + 10;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n, m;
int a[N];

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);cal
	n = Read(), m = Read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i] += Read() * (1 << j - 1);
	sort (a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	if (!a[1]) {
		puts("YES");
		return 0;
	}
	bool flag = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++)
			if (!(a[i] & a[j])) {
				flag = 1;
				break;
			}
		if (flag) break;
	}
	puts(flag? "YES": "NO");
	return 0;
}

```

---

