# [ICPC 2022 Xi'an R] Strange Sum

## 题目描述

给定一个序列 $a_1, a_2, \ldots, a_n$。

你需要选择 $a$ 中的零个或多个元素，使得：如果你选择了 $a_i$，那么在任何长度为 $i$ 的区间内（形式上，对于任何 $1 \le j \le n - i + 1$ 的 $a[j, j + i - 1]$），最多可以选择 $2$ 个元素。

计算你选择的元素的最大和。

## 说明/提示

**来源**：2022 ICPC 亚洲西安区域赛问题 J。

**作者**：JohnVictor。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
1 4 3 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3
-10 -10 -10
```

### 输出

```
0```

# 题解

## 作者：cff_0102 (赞：4)

### 题意：

给定一个序列 $a_1, a_2, \ldots, a_n$。

你需要从中选出若干个元素，使得：如果你选了 $a_i$，则对于任意长度为 $i$ 的区间（即 $a[j,j+i-1]$，其中 $1\le j\le n-i+1$），至多选 $2$ 个元素。

求出所选元素的最大和。

### 题解：

假设选了 $a_{i}$，那么 $a[1,i]$ 应当只有至多两个元素。

假设我们一共选了三个（或更多）元素，它们分别是 $a_x,a_y,a_z$，那么因为 $a[1,z]$ 只能有两个元素被选取，导致矛盾。

所以至多只能选两个元素。

排序一下，选取最大的那两个元素（如果非负的话），相加就是答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[542457];
int main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a,a+n);
    cout<<max(0,a[n-2])+max(0,a[n-1]);//max(0,x)，即当x>0时取x（表示选取这个数），否则是0（不选择x这个数）
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/111110501)。

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 P9367 [ICPC2022 Xi'an R] Strange Sum](https://www.luogu.com.cn/problem/P9367)

## 题意简述

给定一个长度为 $n$ 的序列 $a_i$。需要选择若干元素（可以不选），满足如果选择了 $a_i$，则所有长度为 $i$ 的子区间中最多只能选择两个元素。求在满足该条件下所能选择的元素之和的最大值。

## 解题思路

1. 假设选择编号最大的元素为 $a_x$，那么在区间 $[1,x]$ 中最多只能选择两个元素，因为序列中没有比 $a_x$ 编号更大的元素。因此，整个序列中最多只能选择两个元素。

2. 所以最终答案为以下三种情况的最大值：

- 不选择任何元素：和为 $0$。
- 选择 $1$ 个元素：选择最大值，和为 $max_1$。
- 选择 $2$ 个元素：选择最大值和次大值，和为 $max_1+max_2$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	int max1=-inf,max2=-inf;
	for(int i=1;i<=n;i++)
	{
		int t;
		cin>>t;
		if(t>max1)
		{
			max2=max1;
			max1=t;
		}
		else if(t>max2)
		{
			max2=t;
		}
	}
	cout<<max(0,max(max1,max1+max2))<<'\n';
	return 0;
}
```

---

## 作者：zhuweiqi (赞：3)

拿到这题的第一反应，我们首先思考的应该是怎么样选才能使得选的数尽可能地多，然后再去考虑正负问题，思考了一小会儿后，我们会惊奇地发现一个问题，那就是无论我们怎么选，都不可能选到 $3$ 个数及以上，那又是为什么呢？下面给出证明：这里使用反证法，设我们想选的 $3$ 个数分别为 $a_i$、$a_j$ 和 $a_k$（其中 $1\leq i<j<k \leq n$），因为我们已经选了 $a_k$ 了，那就意味着我们最多只能在 $a_1$ 至 $a_k$ 这段区间内再选一个数了，而很显然 $a_i$ 和 $a_j$ 都属于这段区间，而我们又把它们全选了，肯定是不行的，因此得出结论，答案为 $a$ 中的最大值 和 $a$ 中的最大值与次大值的和 和 $0$ 三者之间的最大值（因为数有正负，而我们只是最多选两个数，只选一个数或者不选任何一个数都是可以的）。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
int main(){
	int n=read(),maxs=0,ans=0,x;
	for(int i=1;i<=n;i++){
		x=read();
		ans=max(ans,x+maxs);
		maxs=max(maxs,x);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：_Komorebi_ (赞：2)

题意：

给定一个数组，从中选择 $0$ 或多个元素，如果选了 $a_{i}$，则每一个长度为 $i$ 的区间最多选 $2$ 个。

思路：

假如我们选了下标最大的数，那么从 $1$ 到这个最大的下标，也就是 $n$ 内也只能选 $2$ 个。由此我们得出最多只能够选两个。

最后附上完整代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);//快排 
	ans=max({a[n],a[n]+a[n-1],0});
	cout<<ans<<'\n';
	return 0;
}

```

[通过记录](luogu.com.cn/record/111089635)

---

