# Sereja ans Anagrams

## 题目描述

### 题目翻译

Sereja 有两个序列 $a$ 和 $b$，还有一个数字 $p$。$a$ 序列为 $a_1,a_2,a_3,\cdots,a_n$，$b$ 序列为 $b_1,b_2,b_3,\cdots,b_n$。

Sereja 像往常一样学习他的序列，今天他想要找到若干个正整数 $q$ 使得 $q+(m-1) \times p \le n$ 并且 $q \ge 1$，同时需要满足的是 $a_q,a_{q+p},a_{q+2 \times p},\cdots,a_{q+(m-1) \times p}$ 和 $b$ 序列一样。

定义这里的序列一样不需要每个位置上的数相同，只需要他们所包含的数值相同。

比如 $1,2,3$ 和 $1,3,2$ 是一样的，但是 $1,3,3$ 和 $1,3,2$ 是不一样的。

## 样例 #1

### 输入

```
5 3 1
1 2 3 2 1
1 2 3
```

### 输出

```
2
1 3
```

## 样例 #2

### 输入

```
6 3 2
1 3 2 2 3 1
1 2 3
```

### 输出

```
2
1 2
```

# 题解

## 作者：daitouzero (赞：1)

有意思的题目

## 题意

两个序列 $a$（长为 $n$）和 $b$（长为 $m$），一个整数 $p$。

我们定义两个序列相同是他们中出现的数相同（包括种类和个数）。

现在有个整数 $q,q\ge1$，使得序列 $\{a_{i}\},i=q+kp,0\le k<m$ 与 $b$ 相同，求 $q$ 的个数。

## Solve

出现的数相同，考虑用 map 维护，存序列中数的种类和个数。

这样我们检验两个序列是否相同可以直接判 map 是否相等，十分方便。

先考虑暴力，我们枚举起点（也就是 $q$）的值，然后暴力检验，这样复杂度铁定会炸。

检验方式没法优化，考虑减少重复枚举量，我们发现，这 $i=q+kp$，$p$ 是个定值，也就是说它每次跳过的距离是相同的。

这表明我们 $1$ 到 $n$ 枚举起点其实有很多重复工作。

你想想你要是把起点往后挪 $1$ 个 $p$，那这个新序列和挪之前的旧序列并没有多大差别。

考虑在这方面优化。

我们用一个队列存序列中的数，那么当起点往后挪一个 $p$ 时弹出队头，把终点后挪 $p$ 后的数加入队尾，同时维护队列内元素的 map。

就这么循环往复直到挪无可挪为止。

这其实就是把序列按照 $\bmod p$ 分了层，每次检查一层，可以保证不重不漏。

那么复杂度就是 $O((p-1)\frac{n}{p}\log m\times (?))$，反正能过。

注意答案按升序输出！

## Code

代码实现几乎没有坑点，只要注意当 map 中一种数的个数为 $0$ 时记得要把它 erase 就行。

```cpp
#include <climits>
#include<cstdio>
#include <ios>
#include<queue>
#include<cmath>
#include<set>
#include<map>
#include<iostream>
#include<stack>
#include<vector>
#include<cstring>
#include<algorithm>
#include<bitset>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N=2e5+5;
std::map<int ,int >B,cnt;
std::vector<int>ans;
int n,m,p,val[N];
int q[N],head,tail;
inline void solve(int x)
{
	cnt.clear();
	head=tail=0;
   for (int i=x;i<=n;i+=p)
	{
		q[++tail]=val[i];
      cnt[val[i]]++;
		if (tail-head==m)
		{
			if (B==cnt) ans.push_back(head*p+x);
			cnt[q[++head]]--;
         if (!cnt[q[head]]) cnt.erase(q[head]);
		}
	}
}
int main()
{
   std::ios_base::sync_with_stdio(false);
   std::cin.tie(0);std::cout.tie(0);
	std::cin>>n>>m>>p;
	for (int i=1;i<=n;i++)
      std::cin>>val[i];
	for (int i=1;i<=m;i++)
   {
      int x;
      std::cin>>x;
      B[x]++;
   }
   for (int i=1;i<=p;i++) solve(i);
	std::sort(ans.begin(),ans.end());
	std::cout<<ans.size()<<'\n';
	for (auto x:ans) std::cout<<x<<' ';
	return 0;
}
```

---

