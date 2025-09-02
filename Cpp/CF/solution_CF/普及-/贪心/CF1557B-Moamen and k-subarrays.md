# Moamen and k-subarrays

## 题目描述

Moamen has an array of $ n $ distinct integers. He wants to sort that array in non-decreasing order by doing the following operations in order exactly once:

1. Split the array into exactly $ k $ non-empty subarrays such that each element belongs to exactly one subarray.
2. Reorder these subarrays arbitrary.
3. Merge the subarrays in their new order.

A sequence $ a $ is a subarray of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

Can you tell Moamen if there is a way to sort the array in non-decreasing order using the operations written above?

## 说明/提示

In the first test case, $ a = [6, 3, 4, 2, 1] $ , and $ k = 4 $ , so we can do the operations as follows:

1. Split $ a $ into $ \{ [6], [3, 4], [2], [1] \} $ .
2. Reorder them: $ \{ [1], [2], [3,4], [6] \} $ .
3. Merge them: $ [1, 2, 3, 4, 6] $ , so now the array is sorted.

In the second test case, there is no way to sort the array by splitting it into only $ 2 $ subarrays.

As an example, if we split it into $ \{ [1, -4], [0, -2] \} $ , we can reorder them into $ \{ [1, -4], [0, -2] \} $ or $ \{ [0, -2], [1, -4] \} $ . However, after merging the subarrays, it is impossible to get a sorted array.

## 样例 #1

### 输入

```
3
5 4
6 3 4 2 1
4 2
1 -4 0 -2
5 1
1 2 3 4 5```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：Eason_AC (赞：5)

## Content
给定一个大小为 $n$ 的数组。你可以将其分为 $k$ 个子数组，并按照每个子数组的字典序重新排列这些子数组，再顺次拼接，得到一个新的数组。问是否存在一种划分子数组的方案，使得重新拼接后的数组是单调不降的？

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 1000$，$1\leqslant k\leqslant n\leqslant 10^5$，$0\leqslant |a_i|\leqslant 10^9$，$\sum n\leqslant 3\times 10^5$。**
## Solution
我们不妨将原来的数组中的元素按照其在数组中的大小顺序重新编号。例如说 $[1,-4,0,-2]$（即样例第二组数据）可以按照这种方式重新编号为 $[4,1,3,2]$。然后这道题目就转化为是否可以找到一组划分方案使得重新拼接后的数组是 $[1,2,3,\dots,n]$。

这就非常简单了。首先一个很显然的结论，要想划分的数组尽量少，就尽量把变化后的数组中连续且单调递增的一段分成一个子数组。比如说 $[6,1,4,5,7,8,9,2,3]$ 就可以按照这种思想划分为 $[6],[1],[4,5],[7,8,9],[2,3]$。可以证明这种划分方案可以使得最终划分的子数组尽量少。

设我们按照上面的方案最终划分的子数组的数量为 $x$，则最后只需要看是否有 $x\leqslant k$ 即可。
## Code
```cpp
namespace Solution {
	int a[100007], id[100007];
	
	ib cmp(int ida, int idb) {return a[ida] < a[idb];}
	
	iv Main() {
		MT {
			int n = Rint, k = Rint, cnt = 1;
			F(int, i, 1, n) a[i] = Rint, id[i] = i;
			sort(id + 1, id + n + 1, cmp);
//			F(int, i, 1, n) printf("%d%c", id[i], " \n"[i == n]);
			F(int, i, 2, n) if(id[i] != id[i - 1] + 1) cnt++;
			cnt > k ? No : Yes;
		}
		return;
	}
}
```

---

## 作者：LRL65 (赞：5)

题意：

可以将一个**无重复数字**的数组最多分成 $k$ 个子数组，再将这些子数组按任意顺序拼接在一起。问拼接后这个数组能否为单调递增数组。

思路：

我们先将这个数组每一个数编上号，然后按照数值递增来排序。当排序后挨在一起的数字原来也挨在一起（通过编号确定），那么这些数就是同一个子数组的。数一下数量看是否超过 $k$ 即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
struct node {
    int name,x;
}a[100005];
bool cmp(node a,node b) {
    return a.x<b.x;
}
int main() {
    cin>>t;
    while(t--) {
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i].x,a[i].name=i;
        sort(a+1,a+n+1,cmp);
        int cnt=1;
        for(int i=2;i<=n;i++)
            if(a[i].name!=a[i-1].name+1)cnt++;
        if(cnt>k)cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
}
```


---

## 作者：Zachary_Cloud (赞：4)

## $\text{Problem}$

- 题目传送门 → [CF1557B Moamen and k-subarrays](https://www.luogu.com.cn/problem/CF1557B)

- 题目大意

  有一个长为 $n$ 的序列，现将序列拆分为恰好 $k$ 个**连续的非空**子阵列，问能否重新排列这 $k$ 个子序列使得排列后的序列变为一个非降序列。
  
## $\text{Solution}$

解决很简单，因为如果拆分后变为一个有序序列，则原序列中肯定有小于等于 $k$ 个的连续序列，判断即可。

注意，有可能会出现包含的情况，所以需要先离散化一下。


## $\text{Code}$

```cpp
// Problem: CF1557B Moamen and k-subarrays
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1557B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Date: 2021-08-10 13:42:17
// By Zachary_Cloud

#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
int T,n,k,a[100010];
struct node {
	int val,id;
} b[100010];
bool cmp(node a,node b) {
	return a.val<b.val;
}
signed main() {
	IOS; cin>>T;
	while (T--) {
		cin>>n>>k; int ans=1; //一开始 ans=1 是因为本身就是一个序列
		for (int i=1;i<=n;++i) cin>>b[i].val,b[i].id=i;
		sort(b+1,b+n+1,cmp);
		for (int i=1;i<=n;++i) a[b[i].id]=i;
		for (int i=2;i<=n;++i) if (a[i]!=a[i-1]+1) ++ans;
		if (ans<=k) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}

```


---

## 作者：Hovery (赞：3)

# Problem
给你一个长度为 $n$ 的序列，把它分成连续的 $k$ 段，并按每段首个数的大小排序后合并，问：合并后的序列是否能单调递增。

# Sol

首先考虑一个数 $a_i$ 有多少种情况能在第一个比它大的数 $a_j$ 的前面。

不难发现，只有两种情况：

> $1.i+1 = j$，也就是这两个数是连续的且小的在前。

> $2.$ 第二种情况也很显然，就是把 $k$ 个子序列合并后,$a_i$ 到了 $a_j$ 前面。

我们假设 $a$ 序列排序好后的序列为 $b$。

综合上述两种情况，我们每次只需从 $a$ 中找一段**蓝色**的，再从 $b$ 中找一段**红色**的与 $a$ 中的蓝色相等就行啦。

![](https://cdn.luogu.com.cn/upload/image_hosting/yuk5682w.png)

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, a[100010], b[100010], l, r, x, t;
int main()
{
	ios::sync_with_stdio(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		for (int i = 1;i <= n;i++)
		{
			cin >> a[i];
			b[i] = a[i];
		}
		sort(b + 1, b + n + 1);
		l = 1;
		while (l <= n && k >= 0)
		{
			if (l!=0)
			x = lower_bound(b + 1,b + n + 1,a[l]) - b;
			else x = 0;
			r = l + 1;
			x++;
			k--;
			while (x <= n && r <= n && b[x] == a[r])
			{
				x++;
				r++;
			}
			x--;
			r--;
			l = r + 1;//由于 a 中 L ~ R 的区间已被查询过，所以 L 可以从 R + 1开始找。
		}//不断从 b 中找串。
		if (k >= 0)
		cout << "Yes\n";
		else cout << "No\n";
	}
}
```

---

## 作者：张晟轩 (赞：1)

## 题目分析：
显然，只需要求出数列 $\{a_n\}$ 中有多少有序的块，与 $k$ 比较即可。  
将 $\{a_n\}$ 排序，若 $a_{i-1}$ 在原数列的位置不在 $a_i$ 的前一位，则 $a_{i-1},a_i$ 不在同一个块内，块数增加 $1$。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,tot;
struct Data{
	int x,i;
}a[100005];
bool cmp(Data x,Data y){
	return x.x<y.x;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) scanf("%d",&a[i].x),a[i].i=i;
		sort(a+1,a+1+n,cmp);
		for(int i=2;i<=n;++i)
			if(a[i-1].i+1!=a[i].i) m--; 
		if(m<1) puts("No");
		else puts("Yes");
	}
	return 0;
}

```

---

## 作者：sunzz3183 (赞：0)

# CF1557B Moamen and k-subarrays

## 题面

给你一个长度为 $n (1≤n≤10^5)$  的整数序列 $a (0≤|a_i|≤10^9)$ ，现在你要讲这个序列分为 $k(1≤k≤10^5)$ 个非空子阵列，然后对这 $k$ 个非空子阵列从小到大进行排序，排序后进行合并，得到一个新的整数序列，并使这个新的整数序列成为非降序的有序序列。

现在询问是否有一种方法是否有一种方法可以使用上面写的操作按非降序对数组进行排序，有方法输出 **Yes** ,没有输出 **No**。

T 组数据 $(1≤t≤10^3)$ 。

## 分析

显然，使这个新的整数序列成为非降序的有序序列就是把 $a$ 序列从小到大排序，而排序后仍然挨在一起并前后顺序不变 $(a_{i-1}\leq a_i-1)$ 的数就是在一个子数组。

例如：$[1,5,4,2,3]$ 排序后是 $[1,2,3,4,5]$ 。$[2,3]$ 满足条件我们就把序列划分为 $ \{ [1],[5],[4],[2,3] \}$

而当划分块数 $≤k$ 时是 Yes，$>k$ 时是 No 。

那我们如何知道划分块数呢，我们只需在建一个数组 $b$ ，令 $b_i=i$ ，然后用数组 $a$ 对数组 $b$ 进行排序，最后 $O(n)$ 扫一遍数组 $b$ 如果 $b_{i-1}+1≠b_i$ 划分块数就 $+1$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],b[N];
int T,n,k;
bool cmp(int x,int y){
	return a[x]<a[y];
}
int main(){
	cin>>T;
	while(T--){
		int ans=1;//初始化要为1
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=i;
		}
		sort(b+1,b+n+1,cmp);
		for(int i=2;i<=n;i++)
			if(b[i-1]+1!=b[i])
				ans++;
		if(ans<=k)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	
	return 0;
}
```



---

## 作者：Leasier (赞：0)

根据题目要求，可以发现**离散化后值的大小相邻者如果不挨在一起，则需要新增一个子串**。

证明：加上它们不挨在一起时不需要新增子串，则将整个序列划分完后较大的值插不进来，会导致排序失败。

统计子串个数，若个数 $\leq k$ 输出 `Yes`，否则输出 `No` 即可。

代码：
```cpp
#include <iostream>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
 
int a[100007], b[100007], pos[100007];
 
int main(){
	int t;
	cin >> t;
	pos[0] = -1;
	for (int i = 1; i <= t; i++){
		int n, k, cnt = 0;
		cin >> n >> k;
		for (int j = 1; j <= n; j++){
			cin >> a[j];
			b[j] = a[j];
		}
		sort(b + 1, b + n + 1);
		for (int j = 1; j <= n; j++){
			a[j] = lower_bound(b + 1, b + n + 1, a[j]) - b;
			pos[a[j]] = j;
		}
		for (int j = 1; j <= n; j++){
			if (pos[j] != pos[j - 1] + 1) cnt++;
		}
		if (cnt <= k){
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}
```

---

## 作者：honey_ (赞：0)

# 首先读题：
这个题是给你一个序列，你需要将他分为 $k$ 个子序列，经过重排得到的新的数列是非减的。
# 显然是道贪心题
贪心策略：将数据按数值从小到大排序，再遍历子序列，如果前一个数字的编号与后一个数字的编号不相连，那么 $cnt$ 加 1，输出结果如果 $cnt \le k$ 就是  $\mathbf{Yes}$ 反之 $\mathbf{No}$ （$cnt$ 初始值为 1）
## 简单讲下为什么
题目说子序列中的数字不会重复，那每个编号对应的数字也是唯一的。   
将一个子序列划分为多个子序列，划分的子序列中，子序列内部数字的位置是保持不变了。   
也就是说划分了一个子序列，则这个子序列内部一定是非减且连续的。   
因此就可以得到贪心结论。
# code
[code](https://codeforces.com/contest/1557/submission/125427455)

---

## 作者：_Clown_ (赞：0)

# B.Moamen and k-subarrays
$\mathtt{Difficulty}$=$\mathtt{1100}$

看完题目后，我们得到一个猜想：
> 只要将原串分成递增的小段即可

但是我们轻而易举地 hack 掉了

比如说前面有一个 $\{3,6\}$ 后面有一个 $\{4\}$ 就炸掉了

于是我们稍加改进，不难得到：
> 只要将原串分成递增的小段切实排完序紧挨的即可

然后可以用 pair 来优化写法，于是代码不难写出
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,K,A[100001];
pair< int,int >B[100001];
int main(void)
{
	BetterIO;
	register int Case;cin>>Case;while(Case--)
	{
		register int i;cin>>N>>K;
		for(i=1;i<=N;i++)cin>>A[i];
		for(i=1;i<=N;i++)B[i].first=A[i],B[i].second=i;
		sort(B+1,B+N+1);
		register int Ans=0;
		for(i=2;i<=N;i++)if(B[i].second!=B[i-1].second+1)Ans++;
		if(Ans<K)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

你有一个长度为 $n$ 的有**不同的数**的序列序列。

现在，你可以把它分成 $k$ 个子**串**（注意子串和子序列是有区别的），然后将它们通过任意的顺序连接成一个新序列，你要让新序列变成有序的。

现在，输入 $t$ 代表数据组数。对于每一组数据，输入 $n$、$k$ 和原序列。问：你能做得到吗？

### 2 思路

首先看一句题目里的话：

>Moamen has an array of $n$ **distinct** integers. 

这说明，一个有序的序列是唯一的，不管排序算法稳不稳定，结果都是相同的。

我们可以发现，对于任何的在**同一**子串的 $2$ 个数，如果它们排序前相邻，那么它们在排序后也**必定相邻**。

那么我们可以记录好每个数在排序前和排序后的位置。

以第 $1$ 组数据 $6,3,4,2,1$ 为例。排序后的序列：$1,2,3,4,6$

我们可以整理出一份表格：

| 原序列 | $6$ | $3$ | $4$ | $2$ | $1$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 排序后在序列的位置 | $5$ | $3$ | $4$ | $2$ | $1$ |

一个个枚举可以发现：

只有 $3$ 和 $4$ 在排序后依然连续，也就是说，我们可以将原序列划分成 $4$ 个子串：

$$[6],[3,4],[2],[1]$$

恰好 $k=4$，所以输出 `Yes`。

### 3 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
#define max_n 100000
int n;
int k;
struct A{
	int d;
	int i;
}p[max_n+2],a[max_n+2];
int tot;
bool cmp(A a,A b){
	return a.d<b.d;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1557B_2.in","r",stdin);
	freopen("CF1557B_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i){
			scanf("%d",&p[i].d);
			a[i].d=p[i].d;
			a[i].i=i;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;++i){
			p[a[i].i].i=i;
		}
		tot=0;
		for(int i=2;i<=n;++i){
			if(p[i].i!=p[i-1].i+1)++tot;
		}
		if(tot<k)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/55485201)

By **dengziyue**

---

