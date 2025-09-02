# [ABC134E] Sequence Decomposing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc134/tasks/abc134_e

$ N $ 個の整数からなる数列 $ A\ =\ \{\ A_1,\ A_2,\ \cdots,\ A_N\ \} $ が与えられます。 $ N $ 個それぞれの整数に対して、色を $ 1 $ つ選んでその色を塗ります。 この時、以下の条件を満たす必要があります:

- $ A_i $ と $ A_j\ (i\ <\ j) $ が同じ色で塗られているならば $ A_i\ <\ A_j $ が成立する

条件を満たすように色を塗る時、用いる色の数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

例えば、$ 2,\ 3 $ を赤色、$ 1,\ 4,\ 5 $ を青色で塗れば $ 2 $ 色で条件を満たす塗り方が出来ます。

### Sample Explanation 2

全ての整数を異なる色で塗るしかありません。

## 样例 #1

### 输入

```
5
2
1
4
5
3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
0
0
0
0```

### 输出

```
4```

# 题解

## 作者：Silence_water (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT4825)

---

$Description$

> 给出一个长度为 $n$ 的整数序列：$A_1$，$A_2\ldots A_n$。对于每个数，我们都涂上一种颜色，要求：
>
> 如果 $A_i$ 与 $A_j$ $(i<j)$ 被涂上的颜色相同，则要保证 $A_i<A_j$。
>
> 问最少需要多少种颜色。

---

$Analyse$

转换一下题意。题目相当于让我们求该序列最少能被几个不相交的上升子序列覆盖。

想一下，当一个数 $x$ 要接到一个上升子序列的末尾时，需要满足 $x$ 大于当前末尾的数。假设现在有 $2$ 条序列满足该要求，这 $2$ 条序列的末尾数分别为 $p$ 和 $q$，且 $p>q$。假设在 $x$ 之后存在一个数 $s$ 满足 $q<s<p$。为了使需要的子序列数尽量的少，我们肯定要把 $x$ 接在 $p$ 后面。因为当 $x$ 接在 $p$ 后面时，$s$ 可以接在 $q$ 后面。而 $x$ 接在 $q$ 后面时，$s$ 既不能接在 $p$ 后面，也不能接在 $q$ 后面。所以这样是更优的。

当 $x$ 无法接在已有的所有子序列后时，那么 $x$ 就新成为了一条子序列，它的第一个元素就是 $x$。

---

$Solution$

这里用 `multiset` 来模拟上述过程。其中 `multiset` 用来维护目前已有的所有子序列的末尾元素值。

首先插入 $A_1$，建立一个新的子序列。

然后每遇到一个元素 $x$，进行 `lower_bound` 找到第 $1$ 个大于等于 $x$ 的子序列末尾。如果找到的迭代器 `it=s.begin()`，说明 $x$ 不能接在已有的所有子序列后，需要新建一个，即插入 $x$。否则，`it--`，指向第一个小于 $x$ 的子序列末尾，删除它并插入 $x$。

---

$Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
multiset<int> s;
multiset<int>::iterator it;
int main()
{
    scanf("%d%d",&n,&x);
    s.insert(x);
    for(int i=2;i<=n;i++)
    {
    	scanf("%d",&x);
    	it=s.lower_bound(x);
    	if(it==s.begin())s.insert(x);
    	else
    	{
    		it--;
    		s.erase(it);
    		s.insert(x);
		}
	}
	printf("%d",s.size());
    return 0;
}
```

---

$Another$ $way$

品味一下上述过程，只有当 $x$ 找不到可接入的子序列时，个数才会 $+1$。那么最后 $s$ 中的元素如果按照插入时间顺序排的话，就会形成一个不上升子序列。

那么答案就等价于该序列中的最长不上升子序列长度。这就与[导弹拦截](https://www.luogu.com.cn/problem/P1020)中的第一问相同了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int n,x,dp[M],len=1;
int main()
{
	scanf("%d%d",&n,&dp[1]);
    for(int i=2;i<=n;i++)
    {
    	scanf("%d",&x);
        int p=upper_bound(dp+1,dp+len+1,x,greater<int>())-dp;
        dp[p]=x;
        len=max(len,p);
    }
    printf("%d",len);
	return 0;
}
```

---

$The$ $end$

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：b6e0_ (赞：4)

[题](https://www.luogu.com.cn/problem/AT4825)

题意即为每一种颜色形成的子序列需要是严格单调递增的。类似于[导弹拦截](https://www.luogu.com.cn/problem/P1020)，答案即为 $a$ 的最长非严格单调递减子序列的长度，因为每出现一个小于等于前面上升子序列的数，就要新开一种颜色去涂它。

用离散化+树状数组优化 dp。发现 $a_i$ 只用于比较大小，所以将值域离散化到 $n$ 级别，设新值域大小为 $m$。开一个树状数组维护最大值。因为树状数组求区间（$[a_i,m]$）最大值不方便，所以将离散化后的 $a_i$ 变成 $m-a_i+1$，这样就成了求前缀最大值，可以很方便的维护。时间复杂度 $\mathcal O(n\log n)$。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010],tree[100010],dp[100010];
int main()
{
	int n,m,i,j,ans=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	for(i=1;i<=n;i++)
		a[i]=m-(lower_bound(b+1,b+m+1,a[i])-b)+1;//离散化，将a[i]变成m-a[i]+1 
	for(i=1;i<=n;i++)
	{
		dp[i]=1;
		for(j=a[i];j;j-=j&(-j))//求前缀最大值
			dp[i]=max(dp[i],tree[j]+1);
		for(j=a[i];j<=m;j+=j&(-j))//更新树状数组
			tree[j]=max(tree[j],dp[i]);
		ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：SilverLi (赞：4)

[Sequence Decomposing の 传送门](https://www.luogu.com.cn/problem/AT_abc134_e)

[更杂乱的阅读体验](https://www.cnblogs.com/Silver-Wolf/p/abc134e.html)

### 前置知识

> [$\texttt{multiset}$](https://zh.cppreference.com/w/cpp/container/multiset)

## Description

求一个数列 $a$ 中递增子序列的最少个数。

## Solution

考虑用 `multiset` 存每个递增子序列的最后一个数。

对于每一个 $a_i$($1\le i\le n$)，二分查找 `multiset` 中第一个小于 $a_i$ 的数。

1. 如果有，就删除这个数，再放入 $a_i$。

2. 反之，就直接加入 $a_i$。

## Code

```cpp
#include <iostream>
#include <set>
using namespace std;
const int N = 1e5 + 5;
int n, a[N];
int cnt;
multiset<int> s;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (s.empty()) {
			s.insert(a[i]);
			continue;
		}
		multiset<int>::iterator k = s.lower_bound(a[i]);
		if (k != s.begin()) {
			--k;// 防止越界
			if (a[i] > *k) {
				//上升子序列
				s.erase(k);
				s.insert(a[i]);
			}
		}
		else
			s.insert(a[i]);
	}
	cout << s.size();
	return 0;
}
```

---

## 作者：zhangjiting (赞：3)

## 题意

给你一个长度为 $N$ 的整数序列：$A=\{A_1,A_2,A_3,\cdots,A_N\}$，对于 $N$ 个整数，我们可以为每一个整数涂上颜色。但要求满足下面这个条件：

> 如果 $A_i$ 与 $A_j$ 被涂上同一种颜色，那一定满足 $A_i < A_j$。

找到满足上述条件的最小颜色数。

## 思路

其实就是求将该序列剖成若干严格递增的子序列的最少个数。

那么就可以转换成求最长下降子序列长度。

数据范围比较大，$O(n^2)$ 算法会超时，所以要用二分优化，时间复杂度 $O(n \log_{}{n})$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[100005],a[100005];
int main(){
	int n,l=1;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	dp[1]=a[1];
    for(int i=2;i<=n;i++){
    	if(a[i]<=dp[l]) dp[++l]=a[i];
    	else{
    		int x=upper_bound(dp+1,dp+l+1,a[i],greater<int>())-dp;
        	dp[x]=a[i];
		}
    }
    cout<<l;
	return 0;
}
```


---

## 作者：shenbairui (赞：1)

### 题目分析
这题不就是求有多少个上升子序列吗。

### [导弹拦截](https://www.luogu.com.cn/problem/P1020)（大佬请自动忽略）。

这题就是暴力，但是如果从 $1-ans$ 暴力一遍时间复杂度为 $O(n^2)$，会超时，那怎么办呢？有了用二分就能完美避免这个问题，现在时间复杂度为 $O(n \log n)$，最后输出 $ans$ 就行啦。

### 代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,k,ans;
int a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		k=upper_bound(a+1,a+ans+1,x,greater<int>())-a;//二分
		if(k>ans){//比较
			a[++ans]=x;	
		}
		else{
			a[k]=x;
		}
	}
	cout<<ans;//输出
	return 0;//好习惯
}
```
下期见！

---

## 作者：JWRuixi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT4825)。

[导弹拦截](https://www.luogu.com.cn/problem/P1020)。

- Description

给定一个长度为 $n$ 的数列 $a$，将该序列剖成若干严格递增的子序列，求最少个数。

- Solution

有一点像导弹拦截的第二问，类似的做法，维护最长上升子序列的数量，就相当于维护最长下降子序列的长度。

于是，我们考虑维护每个子序列的最后一个，若存在比所有都要小的，那么怎加一个子序列，否则选取其恰大于的一个值替代，这样子的话就可以保证末尾是最小的，即可以保证下一个选择时可供选择的情况最多、最优。

本质上就是优化 dp，相信最长下降子序列长度大家都会。

- code

```cpp
#include <bits/stdc++.h>
#pragma target("avs,sse2,sse3,see4,mmx")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 1e5 + 500;

int n, a[maxn], j, c[maxn];

int main () {
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	c[0] = 1e9 + 7;
	for (int i = 1; i <= n; i++) {
		if (a[i] <= c[j]) c[++j] = a[i];
		else c[upper_bound(c + 1, c + j + 1, a[i], greater<int>()) - c] = a[i];//这里这里就是这里。
	}
	write(j);
}
```

---

## 作者：Horal (赞：1)

[链接戳这里](https://www.luogu.com.cn/problem/AT4825)

题意：输入一个序列，分成若干个上升序列，问至少需要几个上升序列。

本题属于入门动态规划，答案是最长不上升子序列的长度。套个模板，就过了~

注意：要注意有 0 的情况，取反的时候要 -1 。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,z=INT_MIN;
int f[100001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		f[i]=1;//初始全为1
	}
	for(int i=0;i<n;i++){
		cin>>x;
		x=-x-1;	//取反减1
		*upper_bound(f,f+n,x)=x;
	}
	cout<<lower_bound(f,f+n,0)-f;
	return 0;
}
```



---

## 作者：_7Mr (赞：1)

# 思路
看到这道题，我们很容易可以知道思路。对于每一个输入的 $a_i$ 我们建一个统计数组 $sum$ 当这个 $a_i$ 大于 $sum$ 其中的任何一个数时，替换，最后的答案就是 $sum$ 数组里不为 $0$ 的个数。这样我们既能保证每一个颜色都是单调递增的，并且 $i<j$。如果没有符合呀要求的，那么我们就多刷一个颜色。

这时我们可以轻易地写出代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn],sum[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	int cnt=0;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		if(cnt==0) sum[++cnt]=a;//第一个特殊处理
		else{
			int flag=INF;
			for(int j=1;j<=cnt;j++){
				if(a-sum[j]<=0) continue;//要保证单调递增
				sum[j]=a;//替换
				flag=-INF;
				break;
			}
			if(flag==INF) sum[++cnt]=a;//没有符合要求的，那么多增加一个颜色
		}
	}
	cout<<cnt<<endl;
	return 0;
}

```

当我们将以上代码交上去后，会发现会超时 $5$ 个点。那这时怎么办呢？我们考虑二分。

对于每一个我们输入 $a_i$ 我们依旧按照上面处理，唯一不同的是，在 $sum$ 数组中查找的时候我们进行二分。当我们二分到一个 $sum$ 数组中还未进行存储的数时，说明此时没有符合要求的，那么我们就多刷一个颜色。如果当前二分到的这个值在 $sum$ 数组中已经存储，说明我们要进行替换。最后输出答案。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn],sum[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	int cnt=0;
	for(int i=1; i<=n; i++) {
		int a;
		cin>>a;
		if(cnt==0) sum[++cnt]=a;//第一个特殊处理
		else {
			int l=1,r=cnt;
			while(l<=r){//进行二分
				int mid=(l+r)/2;
				if(sum[mid]<a) r=mid-1;
				else l=mid+1;
			}
			if(l==cnt+1) sum[++cnt]=a;//如果还未有值，那么多刷一个颜色
			else sum[l]=a;//替换
		}
	}
	cout<<cnt<<endl;
	return 0;
}

```

---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
每次输入 $a_i$ 时，寻找一个小于 $a_i$ 的数，就满足 $a_i<a_j$，因为是按顺序输入的，所以满足 $i<j$，两种情况都满足就可以填相同颜色。

如果两种情况不同时满足，就需用其他颜色。

如果从 $1\sim ans$ 种颜色全部遍历一遍去寻找，时间可能会超，就要用二分。

最后输出 $ans$ 即可。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,k,ans;
int v[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		k=upper_bound(v+1,v+ans+1,x,greater<int>())-v;
		if(k>ans) v[++ans]=x;	
		else v[k]=x;
	}
	cout<<ans;	
	return 0;
}

```


---

## 作者：Mu_leaf (赞：0)

## [思路]

把题面翻译过来的意思就是求有多少个上升子序列。

经典例题：[P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)。

~~几乎重题。~~

我们想要它的颜色总数尽量少，那么我们肯定要让能染同一种颜色的几个数染同一种颜色。根据它的要求，我们不难发现，要求的就是有多少组严格上升子序列。

暴力肯定爆毕竟 $O(n^2)$ 了，可以用二分将复杂度降到 $O(n$ $\log$ $n)$。

# [Code](https://atcoder.jp/contests/abc134/submissions/43497589)。

---

## 作者：_AyachiNene (赞：0)

# 题意：
给一个长度为 $n$ 的序列如果 $a_i<a_j(i<j)$ 那么它们可以染成同一种颜色，问所需要的最小颜色数量。
# 思路：
我们想要它的颜色总数尽量少，那么我们肯定要让能染同一种颜色的几个数染同一种颜色。根据它的要求，我们不难发现，要求的就是有多少组严格上升子序列（可以参考导弹拦截）。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[114514],a[114514],k,x[114514],cnt=1;
int main()
{
	x[1]=1e9;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	dp[1]=a[1];
	for(int i=2;i<=n;i++)
	{
		if(a[i]<=dp[cnt]) 
			dp[++cnt]=a[i];
		else 
			dp[upper_bound(dp+1,dp+cnt+1,a[i],greater<int>())-dp]=a[i];
	}
	cout<<cnt<<endl;
}
```


---

