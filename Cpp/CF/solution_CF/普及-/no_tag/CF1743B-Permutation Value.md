# Permutation Value

## 题目描述

You are given an integer $ n $ . You have to construct a permutation of size $ n $ .

A permutation is an array where each integer from $ 1 $ to $ s $ (where $ s $ is the size of permutation) occurs exactly once. For example, $ [2, 1, 4, 3] $ is a permutation of size $ 4 $ ; $ [1, 2, 4, 5, 3] $ is a permutation of size $ 5 $ ; $ [1, 4, 3] $ is not a permutation (the integer $ 2 $ is absent), $ [2, 1, 3, 1] $ is not a permutation (the integer $ 1 $ appears twice).

A subsegment of a permutation is a contiguous subsequence of that permutation. For example, the permutation $ [2, 1, 4, 3] $ has $ 10 $ subsegments: $ [2] $ , $ [2, 1] $ , $ [2, 1, 4] $ , $ [2, 1, 4, 3] $ , $ [1] $ , $ [1, 4] $ , $ [1, 4, 3] $ , $ [4] $ , $ [4, 3] $ and $ [3] $ .

The value of the permutation is the number of its subsegments which are also permutations. For example, the value of $ [2, 1, 4, 3] $ is $ 3 $ since the subsegments $ [2, 1] $ , $ [1] $ and $ [2, 1, 4, 3] $ are permutations.

You have to construct a permutation of size $ n $ with minimum possible value among all permutations of size $ n $ .

## 说明/提示

In the first example, the permutation $ [1, 4, 3, 5, 2] $ is one of the possible answers; its value is $ 2 $ .

In the second example, the permutation $ [4, 1, 6, 2, 5, 3] $ is one of the possible answers; its value is $ 2 $ .

## 样例 #1

### 输入

```
2
5
6```

### 输出

```
1 4 3 5 2
4 1 6 2 5 3```

# 题解

## 作者：Larryyu (赞：1)

## _Description_
给定一个 $n$，需要构造一个长度为 $n$ 的数列，使得数列中所有子段中有特殊性质的子段数量最小。

特殊性质：设子段长度为 $k$，则该子段需包含 $1\sim k$ 的所有数。
## _Solution_
可以确定，不管如何都有两个子段满足特殊性质，即 $1$ 和 $1,2\dots,n$。

对于所有 $k\ge2$ 的子段，都需要有 $2,1$  才能满足性质，那么将 $2$ 放在第 $n$ 个位置，$1$ 放在第一个位置，此时满足性质的且 $k\ge2$ 的子段只有 $1,2\dots,n$。此时有最小值，$2$。

中间第 $2$ 到第 $n-1$ 的位置随意放即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int n;
int a[100],b[100];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	n=read();
	cout<<1<<" ";  //1在第一位
	for(int i=3;i<=n;i++){
		cout<<i<<" ";  //中间无论如何排都无法构成有特殊性质的子段
	}
	cout<<2<<endl;  //2在最后一位
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```
#### _完结撒花！！_

---

## 作者：隐仞Mrsu (赞：0)

# 题意
给定一个正整数 $n$，要构造出一个 $n$ 长的排列，使得其合法子段的数量最少。

合法子段需要满足：
- 是原排列中连续的子段；
- 子段本身也是一个排列。

# 分析
长度为 $1$ 的排列，合法子段的数量就是 $1$。

对于此外的任意一个排列，合法子段的数量最少是 $2$。

首先，单独的 $1$ 就可以构成一个合法子段。其次，整个排列也可以看成一个合法子段。

为了不使增加其余的合法子段，我们首先可以将 $1$ 和 $2$ 放在两端。这样一来，要提取出合法子段，除了单独的 $1$ 以外，只能取两头的 $1$ 和 $2$，即提取出整个排列，使得合法子段的数量就是最少的 $2$。

中间的元素可以从大到小依次放入。

# 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL _,n;
int main(){
	cin>>_;
	while(_--){
		cin>>n;
		cout<<"1 ";
		for(LL i=n;i>1;i--){
			cout<<i<<' ';
		}
		cout<<'\n';
	}
}
```


---

## 作者：yanxu_cn (赞：0)

### 分析

这一道题，我们可以形象的定义一个值为“愤怒值”，即代表这个一个数可以形成的符合题意的子段。

比如给出一个序列 `1 2 3 4 5` ，此时定义整数 $l,r$，分别表示子段的开头与结尾（此时我们令这个数组的开头为 $1$ ） 由于对于 $l=1 , r=1,2,3,4,5$ 时，均是符合题目要求的子段，故可定义序列中第一个元素的“愤怒值”为 $5$。

同理，可求得对于上述序列，第 $n$ 个元素的“愤怒值”为 $6-n$。

我们也可以发现，对于一个序列，如果没有元素 $1$ 则一定构不成符合题意的子段。于是，我们考虑让 $1$ 在子段中出现的越少越好。此时 $1$ 应当出现在队列的一端。

此时，我们发现，还需要尽量减少 $1$ 与 $2$ “接触”的关系，如果把 $2$ 放在序列的另一端，这样除了子段 `1` 以外，就只有整个序列可以满足上面的条件了。很显然，这是最优解。剩下的数据就没什么关系了，这边呢为了方便就从小到大输出了。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			if(i==0)cout<<"1 ";
			else if(i==n-1)cout<<"2\n";
			else cout<<i+2<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Dry_ice (赞：0)

[更佳的阅读体验](https://www.cnblogs.com/dry-ice/p/cf1743b.html)

题链：[cf](https://codeforces.com/contest/1743/problem/B) [luogu](https://www.luogu.com.cn/problem/CF1743B)

> 构造。

## Description
构造一个 $1\sim n$ 的排列，使之连续子串构成 $1\sim k$ 排列的数目最少。

## Analysis
显然，**最小数目可以为 $2$**。因为可以构造所示的排列：
$$1,A_2,A_3,A_4,\cdots,A_{n-1},2$$

此时 **$1$ 和 $2$ 分居两侧**，中间的 $n-2$ 个数排列任意，**连续的**排列仅 $\left[1,n\right]$ 和 $\left[1,1\right]$ 两个。

## Code

```cpp
#include <stdio.h>
int n;
inline void Solve() {
	scanf("%d", &n);
	printf("1 ");
	for (int i = n; i >= 2; --i)
		printf("%d ", i);
	putchar('\n');
}
int main(void) {
	int T; for (scanf("%d", &T); T--; ) Solve();
	return 0;
}
```

## The end. Thanks.

~~（鞠躬撒花~~

---

## 作者：lizhehao2009 (赞：0)

对于本题而言，正确输出的答案有很多种，并非唯一。下面就给大家介绍我认为最简单的一种：

首先输入 $t$，表示测试数据的组数。对于每组测试数据，我们只需先输入 $n$（表示你需要构造的排列的大小），接着输出一个 $1$（即将 $1$ 置于每组输出的开头），再逆序输出 $2\sim n$，最后换行即可。这样可以保证在每组输出的数据当中，只有排列 $[1]$ 和排列 $[1,n,n-1…3,2]$（即整组输出的数据），使排列的数量最少。

参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n;
	cin>>t;
	while (t--)//循环t次
	{
		cin>>n;
		printf("1 ");//先输出1
		for (int i=n;i>=2;i--)//i从n到2循环
		{
            printf("%d ",i);//依次输出n到2
		}
		printf("\n");//注意换行
	}
	return 0;
}
```


---

## 作者：mutan (赞：0)

## 简要翻译
给定一个长度为 $n$ 的正整数，构造一个长度为 $n$ 的排列数。定义一个排列的**权值**为其中能构成排列的子串数量。形式化来讲，一个长度为 $a$ 的子串需要包含 $[1,a]$ 中的所有数。

输出长度为 $n$ 的排列数中**权值**最小的一种排列。

## 题目分析

需要**权值**最小，也就是其中能构成排列的子串最少。而构成排列需要从 $1$ 开始。所有的排列都需要 $1$。这样一来，只要把 $1$ 放到最后，其他数依次排列，$1$ 就不能与前面的数组成排列（除了整个排列）。

例如，当 $n=6$ 时，构造排列 $\{2,3,4,5,6,1\}$，前面的 $\{2,3,4,5,6\}$ 都无法自己组成排列。整个排列的子排列只有 $\{1\},\{2,3,4,5,6,1\}$，**权值** $=2$。

于是代码很简单，依次输出 $2\sim n$ 的数，最后输出 $1$ 即可。

```
#include <iostream>
#include <cstdio>

using namespace std;
int T;
int main()
{
	int n,i,j;
	cin>>T;
	for(i=0;i<T;i++)
	{
		cin>>n;
		for(j=2;j<=n;j++)
		printf("%d ",j);
		printf("1\n");
	}
	return 0;
}
```

---

## 作者：zfx_VeXl6 (赞：0)

对于每个 $n$，先输出 $1$，再倒序输出 $2$ 到 $n$ 即可。可以证明构造的排列只有 $[1]$ 和 $[1,n,n-1,\cdots,3,2]$ 共 $2$ 个子集为排列。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout<<1<<' ';
		for(int i=n;i>=2;i--)
			cout<<i<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：sw2022 (赞：0)

## 题意简析

给定一个排列的长度 $n$，构造一个排列，最小化这个排列的子段中是排列的子段数量。因为对于任意一个长度为 $k$ 的排列，它的子段中是排列的子段都至少包含 $\{1\}$ 和整个排列，所以只要使得这个排列中没有其他满足条件的子段即可。当 $n=1$ 时，显然排列只有一种可能。$\forall n\ge 2$，只需要把 $1$ 置于排列的开头，$2$ 置于排列的结尾，满足条件的子段一定只有 $\{1\}$ 和整个排列，可得数量为最小值。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,i;
    cin>>t;
    while(t--)
    {
        cin>>n;
        printf("1 ");
        for(i=n;i>=2;i--)
        printf("%d ",i);
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：小明小红 (赞：0)

# CF1743B题解

**直接给结论**：无论长度为几，子段数最小都为 $2$。

**过程**：先将 $1$ 放在最前面，然后为了不让后面的和 $1$ 连起来，逆序排列 $2$ 至 $n$。这样刚好只会产生长度为 $1$ 和长度为 $n$ 的子段。

# code
```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,a;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>a;
		cout<<1<<' ';//如题，输出 
		for(ll i=a;i>=2;i--)
		{
			cout<<i<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```


---

