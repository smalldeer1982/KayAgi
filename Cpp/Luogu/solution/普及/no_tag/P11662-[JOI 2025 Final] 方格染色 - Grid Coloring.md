# [JOI 2025 Final] 方格染色 / Grid Coloring

## 题目背景

译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T1。


## 题目描述


要把一个 $N\times N$ 的网格图染色。我们记第 $i$ 行第 $j$ 列的格子为 $(i,j)$。

第一行和第一列的格子已经被染了色。具体地，$\forall 1\le i\le N$，格子 $(i,1)$ 的颜色为 $A_i$，格子 $(1,i)$ 的颜色为 $B_i$。根据定义 $A_1=B_1$。

对于剩下的格子，考虑如下的染色过程：

- 对于 $i=2,3,\cdots,N$，按如下的方案染色第 $i$ 行：
    - 对于 $j=2,3,\cdots,N$，按如下的方案染色格子 $(i,j)$：
        - 记 $\operatorname{color}(i,j)$ 为格子 $(i,j)$ 的颜色（对应的数字）。则 $\operatorname{color}(i,j)=\max(\operatorname{color}(i-1,j),\operatorname{color}(i,j-1))$。

在染色结束后，输出哪种颜色被染在最多的格子上，以及这种颜色被染在多少个格子上。如果有多种颜色，输出数字最大的那种。

## 说明/提示


### 样例解释

#### 样例 $1$ 解释

最后各个格子的颜色如下所示：

| $5$ | $3$ | $1$ |
| :--: | :--: | :--: |
| $2$ | $3$ | $3$ |
| $5$ | $5$ | $5$ |

颜色 $5$ 被染在了 $4$ 个格子上，所以输出 $\texttt{5 4}$。


该样例满足子任务 $1,2,5$ 的限制。

#### 样例 $2$ 解释

最后各个格子的颜色如下所示：

| $1$ | $3$ | $5$ |
| :--: | :--: | :--: |
| $7$ | $7$ | $7$ |
| $8$ | $8$ | $8$ |

颜色 $7,8$ 都被染在了 $3$ 个格子上，所以输出较大的 $\texttt{8 3}$。


该样例满足子任务 $1,2,4,5$ 的限制。

#### 样例 $3$ 解释

该样例满足子任务 $1,2,3,5$ 的限制。

### 数据范围

- $2\le N\le 2\times 10^5$。
- $1\le A_i\le 10^9$（$1\le i\le N$）。
- $1\le B_i\le 10^9$（$1\le i\le N$）。
- $A_1=B_1$。
- 输入的值全部是整数。

### 子任务

1. （15pts）$N\le 500$，$A_i,B_i\le 10^5$（$1\le i\le N$）。
2. （10pts）$N\le 500$。
3. （20pts）$A_i,B_i\le 2$（$1\le i\le N$）。
4. （25pts）$A_i\lt A_{i+1},B_i\lt B_{i+1}$（$\forall 1\le i\le N-1$）；
5. （30pts）无额外限制。



## 样例 #1

### 输入

```
3
5 2 5
5 3 1```

### 输出

```
5 4```

## 样例 #2

### 输入

```
3
1 7 8
1 3 5```

### 输出

```
8 3```

## 样例 #3

### 输入

```
4
2 1 2 1
2 1 1 2```

### 输出

```
2 10```

# 题解

## 作者：I_AM_TLEer (赞：4)

此题评价：本题思想工作挺难的，但想好后就容易多了。

# 正文

相信各位都读懂题意了，在此我就不再赘述了。

定义：在网格图中，第一列第 $n$ 个数记作 $A_{n}$ 。第一行第 $n$ 个数记作 $B_{n}$ 。网格图中第 $i$ 列第 $j$ 行的格子记作 $O_{i,j}$ 。（不存在 $O_ {i,0},O_{0,j}$）。

如果只是单纯的暴力加模拟，一定会 TLE or MLE。

那么，该如何解决呢？

## MLE 问题

注意到：对于任意 $O_{i,j}$ 都有 $O_{i,j}=\max(A_{1}\dots A_{i},B_{1}\dots B_{j})$。

为了简化操作 ， 我们用一种类似于前缀和的方式做预处理。
使得 $A_{i}=\max(A_{1}\dots A_{i})$ ， $B_{i}=\max(B_{1}\dots B_{i})$ 。
即：让序列 A ，序列 B 单调不降。

这样， $O_{i,j}=\max(A_{i},B_{j})$ 。
我们可以直接从预处理的序列 A ，序列 B 推出网格图中的某一格子，空间复杂度从 $O(n^{2})$ 降到了 $O(n)$ 。

## TLE 问题

为了解决 MLE 问题，我们竟阴差阳错地得到了一个宝贝**单调不降序列**。

目前，我们每次要提出一个 $A_{i}$ 并与整个序列 B 做一轮比较。

容易发现：总有前几个数数值是相同的且等于 $A_{i}$ ，我们暂时把这个“几”记作 $xp$ 吧。

很容易明白，这是因为序列 B 单调不降。前 $xp$ 个数都小于等于 $A_{i}$ 。

可以考虑二分。这样的话，时间复杂度就会变为 $O(n\log{n})$ 了。

别忘了序列 A 也是单调不降的。

因为 $A_{i}\le A_{i+1}$ 这使得 $xp$ 也只增不减。

考虑双指针。因为两个指针只把两个序列扫一遍，因此时间复杂度变成 $O(n)$ 了。

## 查找，输出答案

实在想不出别的算法了，就排序吧（痛失 $O(n)$ 的时间复杂度）。

# AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N (int)2e5+10
int n, xp = 1;

struct num {
	int t, m;
	long long c;
}A[N], B[N], AB_h[2*N];

//-----------------------------------------------------
/*		第一部分 
N 代表 n 的上限 
n 接收 网格图的边长
xp 是 辅助变量，用于查找各个数出现的次数

结构体 num 中：
	t 记录输入的原始数据。 
	m 类似指针，在预处理时指向比它大的数或自己。 
	c 用于记录此数 (t) 出现的次数。

序列A，序列B，分别储存输入的数。
在代码的最后用 AB_h 合并序列A，序列B以便求出答案。

温馨提示： 不开 long long 见祖宗。 
*/ 

bool cmp_one (num a,num b) {
	return a.t > b.t;
}

bool cmp_two (num a,num b) {
	if (a.c == b.c)
		return a.t > b.t;
	else return a.c > b.c;
}

//-----------------------------------------------------
/*		第二部分
两次排序 cmp 均对 num 结构体。 
第一次排序：把相同数 (t) 的放在一起，方便次数相加。 
第二次排序：按照题目要求排序，查找到答案。 
*/ 

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; i ++) {
		scanf("%d", &A[i].t);
		A[i].m = i;	A[i].c = 1;
		if (i >= 2 && A[i].t < A[A[i-1].m].t)
			A[i].m = A[i-1].m;
	}
	for (int i = 0; i < n; i ++) {
		scanf("%d", &B[i].t);
		B[i].m = i;	B[i].c = 1;
		if (i >= 2 && B[i].t < B[B[i-1].m].t)
			B[i].m = B[i-1].m;
	}
	B[0].c = 0;
	
//-----------------------------------------------------
/*		第三部分-输入部分
输入序列A，序列B并初始化。同时对两者做预处理。 
特殊的东西必须特殊对待，直接把左上角的数的次数调为0
*/ 
	
	for (int i = 1; i < n; i ++) {
		while (A[A[i].m].t >= B[B[xp].m].t && xp < n){
			B[B[xp].m].c += i-1;
			xp ++;
		}
		A[A[i].m].c += xp-1;
	}
	while (xp < n) {
		B[B[xp].m].c += n-1;
		xp ++;
	}
	
//-----------------------------------------------------
/*		第四部分-处理部分1 
xp 作辅助变量，找到各个数的次数，累加到序列A，序列B中。
有个别的数据点使得 xp 不能扫到最后，因此再用 While 封个底
*/ 
	
	for (int i = 0; i < n; i ++) {
		AB_h[2*i+0].t = A[i].t; AB_h[2*i+0].c = A[i].c;
		AB_h[2*i+1].t = B[i].t; AB_h[2*i+1].c = B[i].c;
	}
	sort(AB_h, AB_h+2*n, cmp_one);
	for (int i = 2*n; i >= 0; i --) {
		if (AB_h[i].t == AB_h[i+1].t) {
			AB_h[i].c += AB_h[i+1].c;
			AB_h[i+1].t = AB_h[i+1].c = 0;
		}
	}
	
//-----------------------------------------------------
/*		第五部分-处理部分2
交错存储到AB_h中。
第一次排序后对相同数(t)的次数相加并把后者删除。 
*/ 
	
	sort(AB_h, AB_h+2*n, cmp_two);
	printf("%d %lld", AB_h[0].t, AB_h[0].c);
	
//-----------------------------------------------------
/*		第六部分-输出部分 
第二次排序 输出答案
*/ 
	
    return 0; //完结 
}

```

# 后记

时间复杂度为 $O(n\log{n})$ 。
空间复杂度为 $O(n)$ 。

[AC 记录。](https://www.luogu.com.cn/record/202118264)

运行得还算快，用时 $280ms$ 。

` What can I say ?  I_AM_TLEer out ! `。

---

## 作者：jojo222 (赞：2)

同样都是 AC，这道题大家的解法为什么不一样？膜拜其他解法的大佬。

### 思路
就拿样例三举例来说：
1. 把 $a$ 和 $b$ 数组堆在一起从大到小排序。
2. 遍历包含 $a$ 和 $b$ 的大数组，最大的中，第一个位于 $a_3$，从这个点一直到右下角都是它。$2$ 的出现次数增加 $2\times3=6$ 次。
   
如图一：
![](https://cdn.luogu.com.cn/upload/image_hosting/z3xr032r.png)

3. 第二个 $2$ 位于 $b_4$（左上角不会影响剩下的格子），从这个点一直到蓝色菱形处也是它。$2$ 的出现次数再增加 $1\times1=1$ 次。

如图二：
![](https://cdn.luogu.com.cn/upload/image_hosting/iz2bkzbv.png)
4. 第一个 $1$ 位于 $a_2$，剩下的两个格子就归它了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[200001], b[200001];
map<int, long long> mp;
struct node
{
	int x; bool f;
	bool operator>(node v) const
	{
		if(f && v.f) return a[x] > a[v.x];
		else if(f && !v.f) return a[x] > b[v.x];
		else if(!f && v.f) return b[x] > a[v.x];
		return b[x] > b[v.x];
	}
};
vector<node> c;
int main()
{
	cin >> n >> a[1];
	for(int i = 2; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mp[a[i]]++;
		c.push_back({i, true});
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		mp[b[i]]++;
		c.push_back({i, false});
	}
	sort(c.begin(), c.end(), greater<node>());
	int x = n, y = n;
	for(auto i = c.begin(); i != c.end(); i++)
	{
		if(i->x == 1) continue;
		if(i->f)
		{
			if(i->x > x) continue;
			mp[a[i->x]] += 1ll * (x - i->x + 1) * (y - 1);
			x = i->x - 1;
		}
		else
		{
			if(i->x > y) continue;
			mp[b[i->x]] += 1ll * (x - 1) * (y - i->x + 1);
			y = i->x - 1;
		}
	}
	int ans = 0;
	long long mx = 0;
	for(auto p : mp)
		if(p.second >= mx)
		{
			ans = p.first;
			mx = p.second;
		}
	cout << ans << ' ' << mx;
	return 0;
}
```

---

## 作者：JACK2021 (赞：1)

[原题面](https://www.luogu.com.cn/problem/P11662)\
~~不行只是你的借口，仔细想想还是可行的~~
## 思路
~~不要说我PUA你，不信你看这一题。~~

看了题目，你是不是已经放弃了统计的想法，但其实是可行的。我们不难发现题目的意思就一个格子里的数等于上面和左面两个数的较大值所以不难发现对于任意的小于它的数都不会影响它。

换种说法，我们称一个数有自己的“管辖范围”，那么我们就可以从较大数开始统计“管辖范围”，在给较小数作统计时，我们减掉已成为其它数的管辖范围内的格子。

举个栗子：

|1|3|4|6|2|
|:-:|:-:|:-:|:-:|:-:|
|**3**|||||
|**7**|||||
|**9**|||||
|**8**|||||

我们先统计“9”的“管辖范围”

|1|3|4|6|2|
|:-:|:-:|:-:|:-:|:-:|
|**3**|||||
|**7**|||||
|**9**|9|9|9|9|
|**8**|9|9|9|9|

再统计“8”时，发现其没有额外的“管辖范围”了，接下来统计“7”：

|1|3|4|6|2|
|:-:|:-:|:-:|:-:|:-:|
|**3**|||||
|**7**|7|7|7|7|
|**9**|9|9|9|9|
|**8**|9|9|9|9|

然后是“6”，以此类推……

|1|3|4|6|2|
|:-:|:-:|:-:|:-:|:-:|
|**3**|3|4|6|2|
|**7**|7|7|7|7|
|**9**|9|9|9|9|
|**8**|9|9|9|9|

最后按题面输出即可

## 主体
我们将$A、B$两数组排序后，像“归并排序”一样取两个数组的头部进行比较，取较大，然后推导公式进行计算。

主题部分代码：
```cpp
	int cx=n,cy=n,j=1,k=1;
	for(int i=1;i<2*n-1;i++){
		if(k==n || a[j].first>b[k].first){
			if(a[j].second<cx){
				mp[a[j].first]+=(cy-1)*(cx-a[j].second);
				cx=a[j].second;
			}
			j++;
		}
		else{
			if(b[k].second<cy){
				mp[b[k].first]+=(cx-1)*(cy-b[k].second);
				cy=b[k].second;
			}
			k++;
		}
	}
```
## 代码
完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
pair<int,int> a[222222],b[222222];
pair<int,int> cnt[222222];
map<int,int> mp;
bool cmp(pair<int,int> x,pair<int,int> y){
	if(x.first>y.first) return true;
	if(x.first<y.first) return false;
	return x.second>y.second;
}
signed main()
{
	cin>>n;
	for(int i=0;i<n;i++){
		int num;
		cin>>num;
		a[i]=make_pair(num,i);
		mp[a[i].first]++;
	}
	for(int i=0;i<n;i++){
		int num;
		cin>>num;
		b[i]=make_pair(num,i);
		if(i!=0) mp[b[i].first]++;
	}
	sort(a+1,a+n,cmp);
	sort(b+1,b+n,cmp);
	int cx=n,cy=n,j=1,k=1;
	for(int i=1;i<2*n-1;i++){
		if(k==n || a[j].first>b[k].first){
			if(a[j].second<cx){
				mp[a[j].first]+=(cy-1)*(cx-a[j].second);
				cx=a[j].second;
			}
			j++;
		}
		else{
			if(b[k].second<cy){
				mp[b[k].first]+=(cx-1)*(cy-b[k].second);
				cy=b[k].second;
			}
			k++;
		}
	}
	for(int i=0;i<n;i++){
		cnt[i]=make_pair(mp[a[i].first],a[i].first);
	}
	for(int i=1;i<n;i++){
		cnt[i+n]=make_pair(mp[b[i].first],b[i].first);
	}
	sort(cnt+1,cnt+2*n,cmp);
	cout<<cnt[1].second<<" "<<cnt[1].first<<endl;
	return 0;
}

```

完美AC！！！

---

## 作者：nbhs23a28 (赞：1)

~~做本题的感言：STL 真好用！~~  
本题是一道经典的由 DP 思路出发的技巧性线性优化题，不过细节有点多。

本题的染色过程十分简约，我们一眼就能看出本题的朴素 DP 思路，至于对颜色的计数，则可用 STL 的 map 或离散化实现开计数桶对颜色的计数。  
（**细节一（伏笔）**：$a_1$ 和 $b_1$ 是同一格，不要重复计数；另一方面，注意用较大值染色开始于第二行，即 $(1,1)$ 初颜色对后续**无影响！**）

接下来，我们考虑优化。我们发现，随着行列的增长，格中数字**单调不减**！这样，我们便能很自然地想到优化方法：二分或双指针优化。

接下来，让我们具体看看如何实现。对于每一格 $(i,j)$，其颜色只能来自 $a_1,a_2,⋯,a_i$ 和 $b_1,b_2,⋯,b_j$ 之中，即为其中最大值。所以，我们便可以分别预处理第一行及第一列最大值数组，对于每行每列双指针维护或二分查找当前行/列所指向数所染的格子个数，对于每种颜色的计数桶累加即可。本题就这样解决了。  
（**细节二**：考虑有可能某些格行列最大值相同可能导致重复计数，可以在统计其一时包含相同）

时间复杂度为 $O(N \log N)$，可以通过此题。

[Code](https://www.luogu.com.cn/paste/fnlleex9)

---

## 作者：cosf (赞：1)

由题意可得，点 $(i, j), i, j\ge 2$ 的值是它左上角的最大值。令 $V_{i, j}$ 表示该值，则有 $V_{i, j} = \max\{\max_{k \le i}V_{k, 1}, \max_{k \le j}V_{1, k}\}$。

于是我们可以从大到小枚举每一个值，并对它们的右下角都赋上值。由定义可知，这样得出的 $V$ 和原题中是一样的。

具体的，我们可以维护两个量 $r, c$ 分别表示最下的、最右的被赋值的行或列。没有即 $n + 1$。

假设当前 $A_i, B_i$ 中最大的是 $A_i$，则它的右下角，$(i, 2)$ 到 $(r - 1, c - 1)$，都会等于 $A_i$。因此我们可以给 $A_i$ 出现的次数加上 $(r - i)(c - 2)$。当然这个前提是 $r \gt i$。然后我们将 $r$ 赋值为 $i$。最大值是 $B_i$ 同理。

注意 $V_{1, 1}$ 是不会对任何数做贡献的，即使是最大值。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAXN 200005

using ll = long long;
using tii = tuple<int, int, int>;

vector<tii> v;

int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        v.emplace_back(a, i, 2 | (i == 1));
    }
    for (int i = 1; i <= n; i++)
    {
        int b;
        cin >> b;
        v.emplace_back(b, i, 1 ^ (i == 1));
    }
    sort(v.begin(), v.end(), greater<tii>());
    ll mx = 0, cu = 0;
    int id = 0;
    ll r = n + 1, c = n + 1;
    for (int i = 0; i < 2 * n; i++)
    {
        auto [u, p, t] = v[i];
        if (t == 3)
        {
            cu++;
        }
        else if (t == 2)
        {
            if (c > p)
            {
                cu += (r - 2) * (c - p);
                c = p;
            }
            cu++;
        }
        else if (t == 1)
        {
            if (r > p)
            {
                cu += (r - p) * (c - 2);
                r = p;
            }
            cu++;
        }
        if (i == 2 * n - 1 || u != get<0>(v[i + 1]))
        {
            if (cu > mx)
            {
                mx = cu;
                id = u;
            }
            cu = 0;
        }
    }
    cout << id << ' ' << mx << endl;
    return 0;
}
```

---

## 作者：yi_hr (赞：0)

## 题目描述

题目要求对一个 $N\times N$ 的网格着色，着色规则为：
$$
\operatorname{color}(i,j)=\max\big(\operatorname{color}(i-1,j),\,\operatorname{color}(i,j-1)\big)
$$
而已知第一行和第一列已经给定颜色，分别存放在序列 $B$ 和 $A$ 中，并且有 $A_1=B_1$。  
## 思路

1. **转化答案：**\
   我们注意到，对于任意格子 $(i,j)$（$i,j\ge2$），由于染色过程具有“最大值传递”的性质，有
   $$
   \operatorname{color}(i,j)=\max(A_1,\dots,A_i,\,B_1,\dots,B_j)
   $$
   因此如果先将两个序列做前缀处理，使得
   $$
   A_i=\max(A_1,\dots,A_i),\quad B_j=\max(B_1,\dots,B_j),
   $$
   那么网格中每个格子的颜色就可以直接写成
   $$
   \operatorname{color}(i,j)=\max(A_i,B_j).
   $$
   这样我们再进行暴力时就可避免 MLE 的问题了。
2. **考虑性质：**\
   我们分别对于每个 $A_i$ 计算，我们发现，只有 $B_i$ 中比 $A_i$ 小的数才会产生贡献，对于每个 $B_i$ 同理，所以我们的答案转化为了：
   - 对于每个行 $i$（对应 $A_i$），有多少列 $j$ 满足 $B_j \le A_i$（此时 $\max(A_i,B_j)=A_i$）；
   - 对于每个列 $j$（对应 $B_j$），有多少行 $i$ 满足 $A_i < B_j$（此时 $\max(A_i,B_j)=B_j$）。\
     因为**两个序列均单调不降**，因此我们可以用双指针或二分来统计这些贡献，从而避免直接遍历整个 $N^2$ 的网格导致 TLE。

## 代码

细节：\
1\. 预处理 $A_i,B_i$ 数组时要跳过 $A_1,B_1$。\
2\. 对于 $A_i=B_i$ 时，要保证贡献只算一遍。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define debug puts("I will ak ioi");
using namespace std;
constexpr int N = 2e5 + 9;
int n;
int a[N], b[N];
int ans;
unordered_map<int, ll> cnt;
int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int x;
    cin >> x;
    ++cnt[x];
    ans = x;
    for (int i = 2; i <= n; i++) {
        cin >> x;
        ++cnt[x];
        if (cnt[x] > cnt[ans]) {
            ans = x;
        } else if (cnt[x] == cnt[ans] && x > ans) {
            ans = x;
        }
        a[i] = max(a[i - 1], x);
    }
    cin >> x;
    for (int i = 2; i <= n; i++) {
        cin >> x;
        ++cnt[x];
        if (cnt[x] > cnt[ans]) {
            ans = x;
        } else if (cnt[x] == cnt[ans] && x > ans) {
            ans = x;
        }
        b[i] = max(b[i - 1], x);
    }
    for (int i = 2; i <= n; i++) {
        int p = upper_bound(b + 2, b + 1 + n, a[i]) - b - 2;
        cnt[a[i]] += p;
        if (cnt[a[i]] > cnt[ans]) {
            ans = a[i];
        } else if (cnt[a[i]] == cnt[ans] && a[i] > ans) {
            ans = a[i];
        }
    }
    for (int i = 2; i <= n; i++) {
        int p = lower_bound(a + 2, a + 1 + n, b[i]) - a - 2;
        cnt[b[i]] += p;
        if (cnt[b[i]] > cnt[ans]) {
            ans = b[i];
        } else if (cnt[b[i]] == cnt[ans] && b[i] > ans) {
            ans = b[i];
        }
    }
    cout << ans << " " << cnt[ans];
    return 0;
}
/*
 ／|、
('、.7
 |、~丶
 じしf_,)ノ
*/
```

---

## 作者：LEE114514 (赞：0)

## 思路

感觉可能做麻烦了。

记原矩阵为 $M$。

把去掉第一行第一列的矩阵提取出来，则可以证明这必定可以分割成若干个与左边界相邻或与上边界相邻的矩形，毕竟若干个 $1 \times m$ 的长条一定能构成满足条件的图形。

那我们不妨让行和列分别向外扩展，$M_{1,1}$ 特殊处理。

对于 $A_i (i \gt 1)$ ，它应从 $M_{2,i}$ 拓展至 $M_{p,q}$，其中 $p$ 为第一个满足 $B_x > A_i$ 的 $x-1$，$q$ 为第一个满足条件 $A_x > A_i$ 的 $x-1$。

对于 $B$ 同理，注意所有不等号是否取等相反。

显然我们可以通过离散化将值域 $V$ 降至 $O(2n)$，并且用一个 $O(V)$ 的预处理求出每一个值对应的第一个大于的位置。

发现同向（即行对行，列对列）的限制可以用一个前缀最大值规避掉，具体的，如果前面有大于等于自生的，显然可以取前面的最大值，它一定可以一路向右（或向下），因为它是最大的，除非它出不了第二行（或列），在代码实现中我们解决这个问题。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],b[maxn],pre[maxn],len;
int vec[maxn<<1],f[maxn<<1],p;
long long cnt[maxn<<1];
int ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",a+i),vec[i]=a[i];
	for(int i=1;i<=n;++i) scanf("%d",b+i),vec[i+n]=b[i];
	sort(vec+1,vec+n+n+1);
	len=unique(vec+1,vec+n+n+1)-vec-1;
	for(int i=1;i<=n;++i) a[i]=lower_bound(vec+1,vec+len+1,a[i])-vec;
	for(int i=1;i<=n;++i) b[i]=lower_bound(vec+1,vec+len+1,b[i])-vec;
	cnt[a[1]]=1;
	p=1;
	for(int i=1;i<=len;++i){
		while(p<n&&b[p+1]<=i) ++p;
		f[i]=p;
	}
	for(int i=2;i<=n;++i) pre[i]=max(pre[i-1],a[i]),cnt[pre[i]]+=f[pre[i]]-1,++cnt[a[i]];
	memset(pre,0,sizeof pre);
	p=1;
	for(int i=1;i<=len;++i){
		while(p<n&&a[p+1]<i) ++p;
		f[i]=p;
	}
	for(int i=2;i<=n;++i) pre[i]=max(pre[i-1],b[i]),cnt[pre[i]]+=f[pre[i]]-1,++cnt[b[i]];;
	for(int i=1;i<=len;++i) ans=(cnt[i]>=cnt[ans])?i:ans;
	printf("%d %lld\n",vec[ans],cnt[ans]);
}
```

---

## 作者：hbhz_zcy (赞：0)

## solution-P11662  

注：容易发现 $A$ 和 $B$ 序列互换只会使数表转置，并不影响最终的结果，所以按一般习惯，$A$ 表示第一行，$B$ 表示第一列。  
首先 $N \le 2 \cdot 10^5$，因此不能简单地枚举数表的全部。根据生成规则，容易证明 $\forall i,j,i',j' \in [2,N],i \le i',j \le j',color(i,j) \le color(i',j')$。第一行和第一列比较特殊，单独进行讨论即可。  
现在关注一维的情况，每一行、每一列的值都是单调不减的，于是对于某个 $(1,t)$，它作用的范围横向上是一段连续区间 $[t,t']$，其中 $color(1,t'+1)$ 是 $t$ 处开始，从左往右数第一个大于 $color(1,t)$ 的；或者是$t'=N$ 到达边界。它作用的纵向范围是 $[2,c]$，其中，$color(c+1,t)$ 是从 $2$ 处开始，从上往下数第一个大于 $color(1,t)$ 的；或者是 $c=N$ 到达边界。列同理。进一步地，我们根据上述分析画出的一条横向线段和一条纵向线段，视为矩形的两条边，构成的这个矩形中的所有点都被染色为左上角的颜色。（矩形不存在即贡献为 $0$）。  
容易联想到使用类似单调栈与双指针的思想进行处理：首先我们记录下所有 $A$ 和 $B$ 的点并按 $color$ 从小到大排列，最开始指针 $u$ 指向最小点。按原序列依此扫描序列 $A$ 和 $B$。每扫描到一个新点 $v$，指针 $u$ 不断右移，对于所有 $color_v \gt color_u$ 对应的 $u$ 点找到其贡献区间的右边界为 $v$ 处。分别找到 $A$ 和 $B$ 处的右边界，即可根据原有位置构造出上述矩形。  
但是注意到答案是直接统计的某一颜色，发现贡献至多由这几部分构成：第一行或第一列的数；左上角对应第一行的矩形；左上角对应第一列的矩形。首先由于单调不减的性质，发现对于 $(1,t)$，若 $\max\limits_{i=1}^{t-1} color(1,i) \gt color(1,t)$，则没有贡献，若 $\max\limits_{i=1}^{t-1} color(1,i) = color(1,t)$，则贡献的矩形必定被前面的包含，只有 $\max\limits_{i=1}^{t-1} color(1,i) \lt color(1,t)$ 贡献的矩形是极大的。于是我们简要处理一下去除无效点，于是每行或每列，对于一个确定的颜色分别至多得到一个矩形。然后，只要把每行和每列的矩形求一下并集的点数即可。第一行和第一列不会与上述构成的任何矩形有交集，位置 $(1,1)$ 注意不要反复统计即可。  
记录过程使用了 `set`,`map` 等容器，并进行过排序，因此时空复杂度均为 $\Theta(N\log N)$。  
个人认为细节比较多，代码实现难度在同等水平题里较高。  

```cpp
//g++ a.cpp -o a -g -std=c++14 -O0 -Wall
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#define LL long long
using namespace std;
int qd(){
	int rt=0;char c=getchar();
	while(c<'0'||c>'9')  c=getchar();
	while('0'<=c&&c<='9')  rt=(rt<<3)+(rt<<1)+c-48,c=getchar();
	return rt;
}
const int maxn=2e5+10,maxh=1e9+10;
int a[maxn],b[maxn],f[maxn<<1][2],dtop=0;
struct node{int t,v;}d[maxn<<1];
bool cmp(const node &x,const node &y){return x.v<y.v;}
multiset<int>sat;
struct nodem{int xa,xb,ya,yb;};
map<int,nodem>mp;
LL upd(int v,int xa,int xb,int ya,int yb){//[)
	if(xa>=xb||ya>=yb)  return 0;
	auto it=mp.find(v);
	if(it==mp.end()){mp[v]={xa,xb,ya,yb};return 1LL*(xb-xa)*(yb-ya);}
	nodem t=it->second;LL rt=1LL*(xb-xa)*(yb-ya)+1LL*(t.xb-t.xa)*(t.yb-t.ya);
	if(max(xa,t.xa)<min(xb,t.xb)&&max(ya,t.ya)<min(yb,t.yb))  rt-=1LL*(min(xb,t.xb)-max(xa,t.xa))*(min(yb,t.yb)-max(ya,t.ya));
	return rt;
}
int main(){
	//freopen("in.txt","r",stdin);
	int N=qd();
	for(int i=1;i<=N;i++)  a[i]=qd();
	for(int i=1;i<=N;i++)  b[i]=qd();
	sat.insert(a[1]);for(int i=2;i<=N;i++)  sat.insert(a[i]),sat.insert(b[i]);
	for(int i=1;i<=N;i++)  a[i]=a[i+1],b[i]=b[i+1];
	N--;
	for(int x=0,i=1;i<=N;i++)  if(a[i]>x)  x=a[i],d[++dtop]={i,a[i]};
	for(int x=0,i=1;i<=N;i++)  if(b[i]>x)  x=b[i],d[++dtop]={N+i,b[i]};
	sort(d+1,d+dtop+1,cmp);a[N+1]=b[N+1]=maxh;
	for(int i=1,t=1;i<=N+1;i++)  while(t<=dtop&&a[i]>d[t].v)  f[d[t].t][0]=i,t++;
	for(int i=1,t=1;i<=N+1;i++)  while(t<=dtop&&b[i]>d[t].v)  f[d[t].t][1]=i,t++;
	//for(int i=1;i<=dtop;i++)  printf("%d,%d ",d[i].t,d[i].v);
	//putchar('\n');
	//for(int i=1;i<=2*N;i++)  printf("%d,%d ",f[i][0],f[i][1]);
	//putchar('\n');
	int anst=0;LL ansv=0;
	for(int i=1;i<=dtop;i++){
		if(!d[i].t)  continue;
		LL t=d[i].t,v=(t>N?upd(d[i].v,1,f[t][0],t-N,f[t][1]):upd(d[i].v,t,f[t][0],1,f[t][1]))+sat.count(d[i].v);
		if(v>ansv||(v==ansv&&d[i].v>anst))  anst=d[i].v,ansv=v;
	}
	printf("%d %lld\n",anst,ansv);
	return 0;
}
```

---

