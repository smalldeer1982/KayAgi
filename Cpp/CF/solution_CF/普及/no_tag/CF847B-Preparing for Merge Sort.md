# Preparing for Merge Sort

## 题目描述

`Ivan`有一个包含$n$个不同整数的数组。他计划将这个数组变成升序的。`Ivan`喜欢归并排序，所以他想将这个数组变成一个或多个升序数组，之后将它们合并。

他用如下的方式将原数组变成一个或多个升序数组：

`Ivan`将对数组进行若干次迭代，直到数组中所有元素都被放入新数组。

对于每次迭代，`Ivan`将依次从左到右遍历每个还未放入新数组中的元素。如果某个元素是该次迭代中的第一个元素，那么它将会放入属于本次迭代的新数组中。如果某个元素不是该次迭代中的第一个元素，那么当且仅当它比属于本次迭代的新数组中最后一个数大时，它将被放入属于本次迭代的新数组的末尾。

更具体的，对于一串数$[1,3,2,5,4]$，第一次迭代将取出$[1,3,5]$这$3$个元素，第二次迭代将取出$[2,4]$这$2$个元素，因为它们是严格递增的。

## 样例 #1

### 输入

```
5
1 3 2 5 4
```

### 输出

```
1 3 5 
2 4 
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
4 
3 
2 
1 
```

## 样例 #3

### 输入

```
4
10 30 50 101
```

### 输出

```
10 30 50 101 
```

# 题解

## 作者：ZSYZSYZSYZSY (赞：2)

# CF847B Preparing for Merge Sort
## Solution
题目要求将一个包含 $n$ 个不同整数的数组按照升序排序，但是要采用特定的方法来实现。

具体来说，算法要求通过多次迭代将原数组变成一个或多个升序数组，然后将它们合并。每次迭代的规则如下：

1. 从左到右遍历数组的元素。

1. 如果某个元素是该次迭代中的第一个元素，将其放入属于本次迭代的新数组中。

1. 如果某个元素不是该次迭代中的第一个元素，并且比属于本次迭代的新数组中最后一个元素大，那么将它放入属于本次迭代的新数组的末尾。

使用数组 $g$ 和计数器 $cnt$，以及一个二维数组 $ans$ 用来存储新数组。数组 $g$ 的每个元素表示当前迭代次数对应的新数组中最后一个元素的值。计数器 $cnt$ 用来记录当前的迭代次数。

具体实现过程如下：

首先，读取输入的数组长度 $n$ 数组元素。

接着，初始化辅助数组 $g$ 和计数器 $cnt$，并设置 $g_0$ 为一个很大的数。

然后，遍历数组，根据规则判断元素的位置，将元素放入相应的新数组 $ans$ 中，并更新辅助数组 $g$ 和计数器 $cnt$ 的值。

最后，输出每个新数组 $ans_i$ 中的元素。

这种方法通过逐步迭代，将原数组按照升序排序，并输出每次迭代生成的新数组。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read(){
	register ll x=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-'){
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}

ll n, a[200005], dp[200005], maxn;
ll g[200005], cnt, flg;
vector<ll> ans[200005];

int main(){
	ll n=read();
	for (ll i = 1; i <= n; i++)
	{
		a[i]=read();
	}
	g[0] = 2e9;
	for (ll i = 1; i <= n; i++) {
		if (a[i] <= g[cnt]) {
			g[++cnt] = a[i];
			ans[cnt].push_back(a[i]);
		}
		else {
			ll l = 1, r = cnt;
			while (l < r) {
				ll mid = (l + r)/2;
				if (g[mid] < a[i]){
					r = mid;
				} 
				else {
					l = mid + 1;
				}
			}
			g[l] = a[i];
			ans[l].push_back(a[i]);
		}
	}
	for (ll i = 1; i <= cnt; i++) {
		for(ll j=0;j<ans[i].size();j++){
			printf("%lld ",ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Bai_R_X (赞：1)

## 思路
正常暴力是 $O(n^2)$ 的时间复杂度，在 $n\le2\times10^5$ 的数据范围下明显不行。

于是考虑二分。我们维护一个保存每条序列最后一个元素的数组，再二分查找第一个大于最后一个数的序列，最后更新就行了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> v[200005];
int n,i,x,lst[200005]; 
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)lst[i]=INT_MAX;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		int pos=upper_bound(lst+1,lst+n+1,-x)-lst;
		lst[pos]=-x;
		v[pos].push_back(x);
	}
	for(i=1;i<=n&&(!v[i].empty());i++)
	{
		for(auto& j:v[i])cout<<j<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：_Passerby_ (赞：0)

更好的阅读体验：[cnblogs](https://www.cnblogs.com/Eliauk-FP/p/18529164)。**注意，博客园里面包含了CF847这一套题大部分题的题解！**

【题目大意】

给定一个元素互不相同序列 $a$，每次可以取出 $a$ 中最长的一个上升子序列，但要求包含 $a$ 的第一个数，然后将这个子序列删掉。求每次取出来的数。

【解题思路】

我们维护每次取出来的子序列的末尾值 $f$。

显然，这个值是单调递减的。因为如果有 $f_i < f_j, i < j$，那么取第 $i$ 条子序列时可以将 $f_j$ 取走。

所以，对于数 $a_i$，如果当前子序列一共有 $l$ 条，分两种情况考虑：

- 若 $a_i \leq f_l$，如果 $a_i$ 比最小的末尾值还小了，这意味着，没有子序列可以在 $a_i$ 加入后保持单调递增。这时，我们给 $a_i$ 新开一个子序列。

- 否则，$a_i$ 可以加到子序列里。为了维护单调性，我们需要找到一个位置，使得 $a_i$ 加入后，$f$ 依然单调递减。形式化地，我们需要找到一个位置 $j$，使得 $f_{j - 1} > a_i$ 且 $a_i > a_j$，然后将 $a_i$ 插入到第 $j$ 条子序列的后面，并更新 $f$ 数组。注意到 $f$ 具有单调性，二分查找即可。

统计答案使用一个 vector。直接做就做完了。

---

## 作者：Lian_zy (赞：0)

## 题目传送门
[**点我点我**](https://www.luogu.com.cn/problem/CF847B)

## 分析
可以肯定的一点是，如果按照题目的方法模拟，TLE 是妥妥的。

给出一组暴力的 hack 数据：

`4 3 2 1`

每次暴力取数并遍历这个数组，复杂度接近 $O(n^2)$，对于 $10^5$ 的数据范围，肯定会爆炸。

既然暴力不行，那么该怎么办呢？

我们可以开一个二维 vector $A$ 和一个用来统计 vector 行数的计数器 $cnt$。

为什么要这样呢？

我们可以把 $A$ 的每一行看成一个序列，这样就好理解后面的东西了。

接下来，对于每个 $a_i$，找到第一个结尾比 $a_i$ 小的序列，并将 $a_i$ 插入到序列的末尾。

如果找不到，则新开一个序列，然后将 $a_i$ 加入这个序列。

最后依次输出每个序列即可。

### 复杂度分析 & 代码

一共 $n$ 个元素，每个元素进行一次查找（使用二分），总复杂度最坏为 $n \log n$（不计 vector 的操作里的那些奇奇怪怪的常数），除非像文章开头我给出的那组数据，一般情况下是不会到达 $n \log n$ 的。

[**AC记录**](https://www.luogu.com.cn/record/155034239)

``` cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> G[maxn];
int n, x, l, r, mid, cnt, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		l = 1, r = cnt, ans = -1;
		while (l <= r) {
			mid = l + r >> 1;
			if (*(G[mid].end() - 1) >= x) l = mid + 1;
			else {
				ans = mid;
				r = mid - 1;
			}
		}
		if (~ans) G[ans].push_back(x);
		else G[++cnt].push_back(x);
	}
	for (int i = 1; i <= cnt; i++) {
		for (auto j : G[i]) printf("%d ", j);
		putchar(10);
	}
	return 0;
}
```

---

## 作者：Otue (赞：0)

这道题跟 P1020 导弹拦截非常相似。

可以看我之前写得博客 [P1020 solution](https://stotue.blog.luogu.org/solution-p1020)。

## 题意
把原序列划分成若干个子序列，所有子序列的数单调递增，问最少划分的子序列数量。
## 思路
仿照导弹拦截，可以总结出如下的贪心思路：
* 如果说当前的数可以找到之前的一个子序列，满足子序列末尾的数小于当前的数，那么就把这个数放到结尾子序列后面。但是，尽量放子序列末尾数字较小的那一个。
* 否则，这个数为首新开一个子序列。

输出答案的时候开一个  $n$ 维 `vector` 存储所有子序列即可。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N], dp[N], maxn;
int g[N], cnt, flg;
vector<int> ans[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	g[0] = 2e9;  // g数组存储的是子序列末尾的数
	for (int i = 1; i <= n; i++) {
		if (a[i] <= g[cnt]) g[++cnt] = a[i], ans[cnt].push_back(a[i]);
		else {
			int l = 1, r = cnt;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (g[mid] < a[i]) r = mid;
				else l = mid + 1;
			}
			g[l] = a[i], ans[l].push_back(a[i]);
		}
		
	}
	for (int i = 1; i <= cnt; i++) {
		for (auto p : ans[i]) printf("%d ", p);
		puts("");
	}
}
```

---

## 作者：xzggzh1 (赞：0)

题意：

把一个数组分成若干个新的单调增的数组，每次选的元素若比新数组最后一个元素大则加入新数组。

$n\leq 10^6$。

---

对于每一次的组成新数组，新数组中后一个元素都是前一个元素之后第一个比它大的元素。

如果对于每一个新的数组只考虑最后的一个数的大小的话，最后会形成一个单调递减的序列，每次取出一个新的元素，若有数比他小，则可以与已有的新数组连接上。（笔者语言表述的不好，若难以理解可以直接看代码）。

如果有多个数组的尾数比该元素小，则接在其中尾数最大的一个数组后面。这个过程可以用二分查找来实现。


----

核心代码：

```cpp
vector<int> v[Maxn];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        p=lower_bound(a,a+n+1,x)-a-1;
        a[p]=x;v[p].push_back(x);//合并，更新尾数 
    }
    for(int i=n;i>=0&&v[i].size();i--,puts(""))
    for(int j=0;j<v[i].size();j++)printf("%d ",v[i][j]);
}
```

---

