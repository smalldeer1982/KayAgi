# Gluttony

## 题目描述

You are given an array $ a $ with $ n $ distinct integers. Construct an array $ b $ by permuting $ a $ such that for every non-empty subset of indices $ S={x_{1},x_{2},...,x_{k}} $ ( $ 1<=x_{i}<=n $ , $ 0&lt;k&lt;n $ ) the sums of elements on that positions in $ a $ and $ b $ are different, i. e.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891B/3cd3fa1580a1bdd16185974adbd0425cf2d97136.png)

## 说明/提示

An array $ x $ is a permutation of $ y $ , if we can shuffle elements of $ y $ such that it will coincide with $ x $ .

Note that the empty subset and the subset containing all indices are not counted.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
4
1000 100 10 1
```

### 输出

```
100 1 1000 10
```

# 题解

## 作者：我梦见一片焦土 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF891B)
# 思路：
首先考虑对于每个 $a_i$ 向它对应 $b_i$ 连边，然后如果连出来的不是一个大小为 $n$ 的环的话显然是错的，因为一次选择相当于选择环上的一条边，那么选一个环显然是对的。

然后现在问题就变成了找一个环排列满足以上的条件，再考虑怎么找这个环排列，发现对应环上选择的连续一段那么最后肯定是头加加而且尾减减，然后中间的不计贡献，换句话就是无法在这个环上选出一个子序列，然后加除减交错使得和为 $0$。

对于这个问题的构造就很简单了，直接选择一个递增的序列，这样每个加加肯定有个比他更大或小的减减与它抵消。

不过这样看上去其实是想复杂了，换种想法其实就是对于每个选出的除了最大的 $a_i$ 都有一个更大的 $b_i$ 对应，然后如果选择了最大的 $a_i$ 那么这个差值需要选择另外 $n - 1$ 个才能抵上。

------------
代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=30;
int n,a[N],b[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++){
		if(a[i]==b[n])printf("%d ",b[1]);
		else printf("%d ",b[upper_bound(b+1,b+1+n,a[i])-b]);
	}
	return 0;
}
```


---

## 作者：pufanyi (赞：2)

害怕，乱搞了一发，然后就A掉了（我`-1`都没判啊）。  
大概就是排序之后全部右移一位，然后把最大的数于最小的数配。  
现在想想确实是这样啊。  
这里给出证明：  
假设排序后数组为$\{a_i\}$，右移后数组为$\{b_i\}$。如果集合不选$a_1, b_1$，那么显然有$\sum a < \sum b$。选$a_n, b_n$？把$\{x_i\}$取个补集即可（两个数组的总和是相等的嘛）。  
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 30;

int ans[maxn];

struct E
{
	int id, x;
	
	inline bool operator < (const E& other) const
	{
		return this->x < other.x;
	}
} aa[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &aa[i].x);
		aa[i].id = i;
	}
	sort(aa + 1, aa + n + 1);
	for(int i = 1; i < n; ++i)
		ans[aa[i].id] = aa[i+1].x;
	ans[aa[n].id] = aa[1].x;
	for(int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	return 0;
}
```

所以为什么$n$那么小呢？大概是spj的复杂度有问题吧……

---

## 作者：Hutao__ (赞：0)

## 思路
将数组排序后每一个都右移一位即可。

## 证明

显然，你不选第一个时，有 $\sum a < \sum b$，选最后一个，然后取补集即可。

## 
```cpp
//lgRMJ坏了不保证此代码能通过此题
#include<bits/stdc++.h>
using namespace std;
int n;
int ans[25];
struct m{
	int x;
	int id;
}a[205];
bool kkk(m a,m b){
	return a.x<b.x;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		a[i].id=i;
	}
	sort(a+1,a+n+1,kkk);
	for(int i=1;i<n;i++)ans[a[i].id]=a[i+1].x;//右移一位
	ans[a[n].id]=a[1].x;
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
        return 0;
} 
```
代码

---

