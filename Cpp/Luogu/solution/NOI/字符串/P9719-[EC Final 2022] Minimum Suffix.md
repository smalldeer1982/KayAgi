# [EC Final 2022] Minimum Suffix

## 题目描述

对于长度为 $n$ 的字符串 $s$，如果 $s[x\ldots j]$ 是 $s[1\ldots j]$ 的最小后缀，则我们定义 $p_j = x$，其中 $j=1,\ldots, n$。（后缀是字符串的最小后缀，如果它在字典序上小于该字符串的任何其他后缀。）

你需要从 $p_1,\ldots, p_n$ 中恢复出 $s$。如果存在多个答案，则找出字典序最小的那个。

## 说明/提示

本题输入输出规模较大，建议使用快速的输入输出方式。

翻译来自于：[ChatGPT](https://chatgpt.com/)。

## 样例 #1

### 输入

```
6
3
1 1 1
3
1 1 2
3
1 1 3
3
1 2 1
3
1 2 2
3
1 2 3```

### 输出

```
1 2 2
-1
1 2 1
1 1 2
2 1 2
1 1 1```

# 题解

## 作者：ningago (赞：7)

前缀的字典序最小后缀问题，考虑 Lyndon 分解。称 Lyndon 分解的结果为 Lyndon 块，记第 $i$ 个 Lyndon 块为 $T_i$。

对于 $p_i$，根据定义有以下性质：

- $[p_i,i]$ 是 Lyndon 串。
- $[j,i](j<p_i)$ 不是 Lyndon 串。

也即，$p_i$ 为 $[1,i]$ 的所有后缀中最长的 Lyndon 串。

通过 $p_n$，可以得出 $n$ 所在的 Lyndon 分解的左端点 $l_n$，而通过 $p_{l_n-1}$ 可以得到下一个 Lyndon 分解的段。一直迭代下去，就可以**通过 $p$ 求出原串的 Lyndon 分解**。

令一个点 $i$ 所在的 Lyndon 块的左端点和右端点为 $l_i,r_i$。

考虑在 Duval 算法中，若 $j$ 是当前考虑的点，$k$ 是 $j$ 在已经求好的循环节中的对应点，则此时需要对 $s_j<s_k/s_j=s_k/s_j>s_k$ 进行讨论。

可以考虑模拟 Duval 算法：

- $s_j<s_k$，此时相当于划分 Lyndon 块，因为求出了 $l,r$，可以不管这种情况。（对每个块独立求解）
- $s_j>s_k$，此时相当于缩了一个大循环节，判断条件为 $p_j=l_j$。
- $s_j=s_k$，此时相当于让循环长度增加，判定条件为 $j-p_j=k-p_k$。
- 上述两条件都不满足，即为无解。

通过模拟 Duval 算法，可以求出：

- $pre_i$ 表示当 $j=i$ 时，对应的 $k$ 是谁。
- $val_i$ 表示是 $s_i=s_{pre_i}$ 还是 $s_i>s_{pre_i}$。令前者为 $0$ 后着为 $1$。 

此时如果整个串只有一个 Lyndon 块，就可以根据条件从前往后字典序贪心（$val=0$ 就照抄，否则加一）。

而有多个 Lyndon 块时，新的条件为 $T_i\geq T_{i+1}$。

此时还是可以字典序贪心，但是按块 $T_i$ 从后往前（块内从前往后贪心）。

贪心时如果遇到当前位置比 $T_{i+1}$ 的对应位置小，分两种情况进行调整：

- 若 $val_i=1$，则可以直接照抄为 $T_{i+1}$ 的对应元素。
- 若 $val_i=0$，则需要让字典序在 $[1,i-1]$ 就定胜负，贪心的方法是：
  - 把上一个 $val_j=1$ 的点加一，然后将 $(j,i]$ 重新贪心分配字符（因为会对后面进行影响）。
- 由于进行一次第二种调整后，字典序就严格大于 $T_{i+1}$ 了，所以第二种调整每个块只会进行一次。复杂度是对的。

最后若 $T_i$ 是 $T_{i+1}$ 的严格前缀，也可以做第二种调整。

复杂度 $O(n)$。

代码参考了隔壁题解，Orz。

```cpp
#define N 3000010
int n, m;
int p[N], last[N], s[N]; 
#define NO { printf("-1\n"); return; }
int pre[N]; bool val[N];
int lst(int x) { if(x > m) return 0; return last[x]; }
void solve()
{
	m = 0;
	n = read(); for(int i = 1; i <= n; i++) p[i] = read();
	for(int r = n, l; r >= 1; r = l - 1)
	{
		val[l = p[r]] = 1; for(int i = l; i <= r; i++) if(p[i] < l) NO;
		for(int i = l + 1, len = 1; i <= r; i++)
		{
			pre[i] = i - len;
			if(p[i] == l) { val[i] = 1; len = i - l + 1; }
			else if(i - p[i] == i - len - p[i - len]) val[i] = 0;
			else NO;
		}
		bool big = 0;
		s[l] = lst(1);
		for(int i = l + 1, j; i <= r; i++)
		{
			s[i] = s[pre[i]] + val[i];
			if(s[i] > lst(i - l + 1)) big = 1;
			if(!big && s[i] < lst(i - l + 1))
			{
				if(val[i]) s[i] = lst(i - l + 1);
				else { for(j = i; !val[j]; j--); s[i = j]++; big = 1; }
			}
		}
		if(!big && r - l + 1 < m)
		{
			int i, j;
			for(j = r; !val[j]; j--); s[i = j]++; big = 1;
			for(i++; i <= r; i++) s[i] = s[pre[i]] + val[i];
		}
		m = r - l + 1;
		for(int i = l; i <= r; i++) last[i - l + 1] = s[i];
	}
	for(int i = 1; i <= n; i++) print(s[i] + 1, ' '); putc('\n');
}
```

---

## 作者：clownor (赞：3)

## 题意

给定一个序列 $s$ 的每个前缀的字典序最小的后缀左端点所在位置 $p_i$，构造出字典序最小的序列 $s$，无解为 `-1`。

多组数据。

## 前置知识

Lyndon 分解

[不了解请左转](https://www.luogu.com.cn/problem/P6114)

## 思路

对照 Lyndon 串的定义，对每个 $p_i=i$ 的 $i$,$i-1$，发现其正好为 Lyndon 串的左右端点（即本串左端点和上一串右端点），这促使我们思考 Lyndon 串的性质。

Lyndon 分解中，相邻两串 Lyndon 串 $s'_i$，$s'_{i+1}$ 之间，有 $s'_i \geq s'_{i+1}$，所以提取出序列的 Lyndon 串，这些串就具有此关系。

进一步讨论各串内部的构造，发现每个 $p_i$ 即为限制 $s_{p_i,i}$ 为 Lyndon 串。

此时无解就方便讨论了，Lyndon 分解中各 Lyndon 串具有明显的 **包含** 关系，一旦不符合此关系，即为无解。

具体一点就是 $p$ 不能与 Lyndon 分解冲突，并且在各 Lyndon 串内只有2种点，一种是 $p_i=i$ 的，另一种是与前面的一串前缀相同的循环。

解释一下就是在进行 Lyndon 分解时，我们对一段未定分解的区间是先维护成多段重复 Lyndon 串+此串一段可为空的前缀，这时如果插入的不符合循环，那它

- 要么是一段 Lyndon 串的尾部（这里的 Lyndon 串可以是分解出的 Lyndon 串的一部分）

- 要么会将这一段 Lyndon 串作为分解的一部分，并成为新一串 Lyndon 串的开头

现在考虑构造。对一个 Lyndon 串内部的划分而言，前面的串比后面的串字典序大（或相等）依然成立。

因此可以以类似 dfs 的方式进行贪心，对当前讨论的区间从前向后贪心，对相邻的兄弟区间从后向前贪心。

但是你大可不必真的实现成 dfs 的形式,因为包含关系的串有共用的点，真的跑 dfs 细节比较多 ~~（虽然直接贪也不少）~~

具体来说可以对第一层 Lyndon 串即 Lyndon 分解出来的串分开考虑，从后往前考虑时需要额外维护一个 $v$ 数组表示这一串的下限，即刚刚考虑完的串的答案。

预处理出串中每个点应该比前面哪个点大或者等于前面哪个点，然后先直接赋值为此点，再扫一遍检查是否符合下限 $v$。

不符的话就是因为有一段区间需要比对应的一段大，把这一段+1，可以暴力扫。

这里直接+1操作对每个点最多一次，所以复杂度是 $O(n)$ 的。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret,c,f=1;
	while (((c=getchar())> '9'||c< '0')&&c!='-');
	if (c=='-') f=-1,ret=0;
	else ret=c-'0';
	while ((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
	return ret*f;
}
int n,p[3000006],ans[3000006],ge[3000006],len,lst[3000006],t,v[3000006];
bool check()
{
	len=0;
	v[1]=1;
	for (int l,r=n;r>=1;)
	{
		l=p[r];
		lst[l]=l,ge[l]=1;
		int L=l;
		if (p[l]!=l) return 0;
		for (int i=l+1;i<=r;i++)
		{
			if (p[i]==l)
			{
				ge[i]=1;
				lst[i]=L;
				L=l;
			}
			else
			{
				if (i-p[i]!=L-p[L]) return 0;
				ge[i]=0;
				lst[i]=L;
				L++;
			}
		}
		bool mr=0;
		ans[l]=v[1];
		for (int i=l+1;i<=r;i++)
		{
			ans[i]=ans[lst[i]];
			if (ge[i])
			{
				ans[i]++;
				if (ans[i]>v[i-l+1]) mr=1;
				if (mr==0&&i-l+1<=len&&ans[i]<v[i-l+1]) ans[i]=v[i-l+1];
			}
			else
			{
				if (ans[i]>v[i-l+1]) mr=1;
				if (mr==0&&i-l+1<=len&&ans[i]<v[i-l+1])
				{
					for (int j=i-1;j>=l;j--) if (ge[j])
					{
						ans[j]++;
						i=j;
						mr=1;
						break;
					}
				}
			}
		}
		if (mr==0&&r-l+1<len)
		{
			for (int i=r;i>=l;i--)
			{
				if (ge[i])
				{
					ans[i]++;
					for (int j=i+1;j<=r;j++) ans[j]=ans[lst[j]]+ge[j];
					break;
				}
			}
		}
		len=r-l+1;
		for (int i=1;i<=len;i++) v[i]=ans[i+l-1];
		r=l-1;
	}
	return 1;
}
signed main()
{
	t=read();
	while (t--)
	{
		n=read();
		for (int i=1;i<=n;i++)
		{
			p[i]=read();
			ge[i]=0;
		}
		if (check()==0)
		{
			printf("-1\n");
		}
		else
		{
			for (int i=1;i<=n;i++) printf("%d ",ans[i]);
			printf("\n");
		}
	}
	return 0;
}
```

---

