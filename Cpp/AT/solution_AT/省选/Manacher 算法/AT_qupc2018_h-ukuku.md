# ukuku

## 题目描述

给定一个长为 $n$ 的整数序列 $a$，表示一个字符串中从前往后数以第 $i$ 位为中心的回文串的最长长度。请输出任意一个满足条件的字符串。数据保证有解。

## 说明/提示

#### 数据规模与约定

$1 \le n \le 2 \times 10^5$，$1 \le a_i \le n$。

## 样例 #1

### 输入

```
5
1 3 5 3 1```

### 输出

```
ukuku```

## 样例 #2

### 输入

```
7
1 1 3 5 5 3 1```

### 输出

```
ukekeke```

# 题解

## 作者：Hadtsti (赞：2)

### 题意简述

给定长为 $n$ 的序列 $\{a_i\}$。构造长为 $n$ 的由小写字母构成的字符串 $S$，满足以 $i$ 位置为中心的极大奇回文串长度为 $p_i$，保证有解。

### 题目分析

不妨将回文串长度 $p_i$ 转为回文半径 $a_i=\frac{p_i+1}2$。注意到 $a_i$ 的限制等同于 $\forall j<a_i,S_{i-j}=S_{i+j}$，且当 $a_i<i$ 时 $S_{i-a_i}\neq S_{i+a_i}$。

那么我们只需要从前往后构造，扫一遍 $1$ 到 $n$。不断维护以 $i$ 之前位置为中心的回文串最远能“够”到哪个位置。如果 $i$ 位置被包含在了以之前位置为中心的回文串中，就可以确定该位置的字符；否则判断 $i$ 位置的字符不能与之前哪些位置相同，找到最小没出现过的字符填入即可。由于我们找的是最小合法的字符，当原问题有解时一定能找到。答案合法性不必多说，所有 $p$ 的限制都满足了，自然合法。

总时间复杂度是线性的，带有字符集大小的常数。实现细节看代码。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],mid;
bool vis[26];
vector<int>vec[200010];
char str[200010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]>>=1;
		if(i+a[i]+1<=n&&i-a[i])
			vec[i+a[i]+1].push_back(i-a[i]-1);
	}
	for(int i=1;i<=n;i++)
	{
		if(mid+a[mid]>=i)
			str[i]=str[2*mid-i];
		else
		{
			memset(vis,0,sizeof vis);
			for(int j:vec[i])
				vis[str[j]-'a']=1;
			for(int j=0;j<26;j++)
				if(!vis[j])
				{
					str[i]=j+'a';
					break;
				}
		}
		if(i+a[i]>mid+a[mid])
			mid=i;
	}
	printf("%s",str+1);
	return 0;
}
```

---

## 作者：Wilderness_ (赞：1)

## 思路：

本文除特殊说明外，$s_i$ 表示字符串 $s$ 的第 $i$ 个字符。
### Subtask 0x01：
正向思考。

对于以 $i$ 为中心的长度为 $a_i$ 的回文串，回文串长度定为奇数（偶数的话中心应在两个数之间），则除中间字符 $s_i$ 以外，以 $s_i$ 为对称中心且位置在区间 $[i-\frac{a_i-1}{2},i+\frac{a_i-1}{2}]$ 的字符对如 $(s_{i-1},s_{i+1}),\ (s_{i-2},s_{i+2})\cdots ,\ (s_{i-\frac{a_i-1}{2}},s_{i+\frac{a_i-1}{2}})$ 都是两两相同的。

我们可以将每一个字符与其相同的字符连起来，然后将联通的字符一同赋上字母。例如：
$$1\ 3\ 5\ 7\ 5\ 3\ 1$$
我们可以发现与 $1$ 相连的有 $3,5,7$，与 $2$ 相连的有 $4,6$，将 $1,3,5,7$ 赋为 $a$，$2,4,6$ 赋为 $b$ 即可。

如此可过 $43$ 个点：[Submission](https://atcoder.jp/contests/qupc2018/submissions/54156665)。

分析原因，估计在于最多只有 $26$ 个小写字母，数量显然不够（毕竟是长度为 $2\times 10^5$ 的字符串）。我们考虑对其 $26$ 个字符用完后再从 $a$ 开始赋值。

如此可过 $56$ 个点（是否是数据过水？）：[Submission](https://atcoder.jp/contests/qupc2018/submissions/54157737)。

估计时间复杂度最坏情况下为 $O(n^2)$，实测下也有两个点 T。至于 WA 的点，hack 大概如下：
```
Input:
76
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 49 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Wrong Output:
abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyxwvutsrqponmlkjihgfedcbaz

Right Output:(其中一种)
aabbaabbaabbaabbaabbaabbaabbaabbaabbaabbaabbaabbaabaabbaabbaabbaabbaabbaabbc
```
### Subtask 0x02：
~~考完语文考试忽然有了思路~~

反向思考。

对于以 $i$ 为中心的长度为 $a_i$ 的回文串，$(s_{i-\frac{a_i+1}{2}},s_{i+\frac{a_i+1}{2}})$ 这一对字符一定不相同。

我们可以存下不相同的字符对位置，对这些位置赋上新的字符，其余的位置赋上与这些位置字符相同的位置上的字符即可（也就是之前 Subtask 0x01 中提到的以 $s_i$ 为对称中心且位置在区间 $[i-\frac{a_i-1}{2},i+\frac{a_i-1}{2}]$ 的字符对）。

改完之后跑得飞快，只用了 $21 \text{ms}$：[Submission](https://atcoder.jp/contests/qupc2018/submissions/54166229)。

## Code：
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define l first
#define r second
#define M 211451
using namespace std;
int n,num[M];
vector<int>ivt[M];
char ans[M];
bool vis[30];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&num[i]);
		int len=(num[i]+1)>>1,l=i-len,r=i+len;ans[i]=96;
		if(l>=1&&r<=n)ivt[r].emplace_back(l);
	}
	auto In=mp(-1,-1);
	for(int i=1;i<=n;++i)
	{
		if(In.l>=(i<<1)+1)ans[i]=ans[(In.r<<1)-i];
		else
		{
			memset(vis,0,sizeof vis);
			for(auto j:ivt[i])vis[ans[j]^96]=1;
			for(int j=1;j<=27;++j)
				if(!vis[j])
				{
					ans[i]+=j;
					break;
				}
		}
		In=max(In,mp((i<<1)+num[i],i));
	}
	printf("%s",ans+1);
	return 0;
}
```
### Update 2024/6/3/21:24：原思路优化后实际可行，至于按原思路的方法，见大佬 [dontwannacry](https://www.luogu.com.cn/user/564225) 的提交记录：[Submission](https://atcoder.jp/contests/qupc2018/submissions/54207922)。

---

