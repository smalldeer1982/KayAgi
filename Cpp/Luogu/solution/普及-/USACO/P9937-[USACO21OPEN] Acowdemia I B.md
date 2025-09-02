# [USACO21OPEN] Acowdemia I B

## 题目描述

由于对计算机科学的热爱，以及有朝一日成为 「Bessie 博士」的诱惑，奶牛 Bessie 开始攻读计算机科学博士学位。经过一段时间的学术研究，她已经发表了 $N$ 篇论文（$1 \le N \le 10^5$），并且她的第 $i$ 篇论文得到了来自其他研究文献的 $c_i$ 次引用（$0 \le c_i \le 10^5$）。

Bessie 听说学术成就可以用 $h$ 指数来衡量。$h$ 指数等于使得研究员有至少 $h$ 篇引用次数不少于 $h$ 的论文的最大整数 $h$。例如，如果一名研究员有 $4$ 篇论文，引用次数分别为 $(1,100,2,3)$，则 $h$ 指数为 $2$，然而若引用次数为 $(1,100,3,3)$ 则 $h$ 指数将会是 $3$。

为了提升她的 $h$ 指数，Bessie 计划写一篇综述，并引用一些她曾经写过的论文。由于页数限制，她至多可以在这篇综述中引用 $L$ 篇论文（$0 \le L \le 10^5$），并且她只能引用每篇她的论文至多一次。

请帮助 Bessie 求出在写完这篇综述后她可以达到的最大 $h$ 指数。

注意 Bessie 的导师可能会告知她纯粹为了提升 $h$ 指数而写综述存在违反学术道德的嫌疑；我们不建议其他学者模仿 Bessie 的行为。 

## 说明/提示

### 样例解释 1

Bessie 不能引用任何她曾经写过的论文。上文中提到，$(1,100,2,3)$ 的 $h$ 指数为 $2$。

### 样例解释 2

如果 Bessie 引用她的第三篇论文，引用数会变为 $(1,100,3,3)$。上文中提到，这一引用数的 $h$ 指数为 $3$。

### 测试点性质

- 测试点 $1-7$ 满足 $N\le 100$。
- 测试点 $8-10$ 满足 $N\le 1000$。
- 测试点 $11-17$ 满足 $N \le 10^5$。

## 样例 #1

### 输入

```
4 0
1 100 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4 1
1 100 2 3```

### 输出

```
3```

# 题解

## 作者：vectorxyz (赞：5)

一道特别简单的贪心题。

#### 简化题意

本题就是让我们先求一个最大的 $h$，在根据 $l$ 把后面能补的补一补，最终再求一个 $h$。

#### 题目分析

一眼贪心。

先将数组从小到大排序，因为要求最大的 $h$，再在满足要求的最后一个数后数 $l$ 个，分别加上 $1$，再重复此操作，输出答案。

具体如下图所示（样例二举例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/uwnm7qln.png)

#### 核心代码
```cpp
n = read, l = read;

for(int i = 1;i <= n;i ++ )
{
    cin >> a[i];
}
sort(a + 1,a + 1 + n, greater<int>());

int h =  get();
h ++ ;
    
while(l > 0 && h > 0) a[h -- ] ++ , l -- ;
    
sort(a + 1,a + 1 + n, greater<int>());
    
return cout << get() ,0;
```

---

## 作者：we_are_the_chuibing (赞：5)

### 题目解析：

1. 要求：给定 $n$ 篇文章，求最大的 $h$ 指数可能，$h$ 指数的意思是，至少有 $h$ 篇文章被引用了 $h$ 次及以上，可以写一篇综述引用自己的文章，但是每篇文章最多引用1次。

2. 思路：这道题目是要我们查找一个 $h$ 值，看是否满足条件。但是当我看到 $n \le 10^5$ 时，内心就已经暗暗想到莫非是二分，恐怖！青铜的第一题就开始搞二分了？！还真是。

3. 二分一个 $h$ 值，如果当前已经有大于等于 $h$ 篇文章被引用大于等于 $h$ 次，则说明 $h$ 太小，可以增大；若当前少于 $h$ 篇文章被引用 $h$ 次，则数出能够引用一次就达到 $h$ 次的文章数量，看是否加上这些文章能够满足 $h$ 篇，若可以，则说明 $h$ 可继续增大；若以上两个条件都不可以，则减小 $h$ 继续尝试。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm> 
using namespace std;
int quote[100005];
int N, L;//N篇文章，综述可引用次数L
//判断当前是否能在L次引用的帮助下，存在h篇文章引用了h次以上 
bool check(int h){
	int cnt = 0;//统计需要增加cnt次引用,共有count篇文章满足h次引用要求 
	//先扫一遍，看当前是否已经有h篇文章满足引用>=h 
	int count_1 = 0;//有count_1篇文章满足h次引用要求
	int count_2 = 0;//有count_2篇文章引用了h-1次 
	for (int i = 1; i <= N; i++){ 
		if (quote[i] >= h){
			count_1++;
		}
		if (quote[i] == h - 1){
			count_2++;
		} 
	}
	//若已经超过h篇论文被引用了h次，则可扩大h 
	if (count_1 >= h)return true;
	//若没有，再考虑是否写入综述，共有h-count_1篇需要写入综述，同时要满足有至少h-count_1篇文章可以写 
	if (h - count_1 <= L && count_2 >= h - count_1)return true;
	return false;
} 
int main(){ 
//	freopen("9.in", "r", stdin); 
	cin >> N >> L;
	for(int i = 1; i <= N; i++){
		cin >> quote[i];
	} 
	sort(quote + 1, quote + N + 1);
	//二分查找最大h指数 
	int l = 0, r = N;
	while(l <= r){
		int mid = (l + r) / 2;
//		cout << " l " << l << " mid " << mid << " r " << r << endl;
		if (check(mid))l = mid + 1;
		else r = mid - 1;
	}
	cout << r;
	return 0;
} 
```


---

## 作者：tder (赞：4)

[简单](https://www.luogu.com.cn/record/list?pid=P9937&user=714254)贪心。

---

据题意，$h$ 为最大的 $x$ 使得有至少 $x$ 篇文章的引用次数大于等于 $x$。考虑如何计算 $h$。

先将 $c$ 排序，显然有对于第 $i$ 篇文章，$c_{i+1}\ge c_i$，且共有 $n-i+1$ 篇文章的引用次数大于等于 $c_i$。此时：

- 当这 $n-i+1$ 篇文章的引用次数均大于等于 $n-i+1$，即 $c_n\ge c_{n-1}\ge\cdots\ge c_i\ge n-i+1$ 时，$x=n-i+1$；
- 反之，当这 $n-i+1$ 篇文章的引用次数不都大于等于 $n-i+1$，即 $c_i<n-i+1$ 时，有 $n-i+1$ 篇文章的引用次数大于等于 $c_i$，那必定有 $c_i$ 篇文章的引用次数大于等于 $c_i$，故 $x=c_i$。

综上，对于第 $i$ 篇文章，$x=\min(c_i,n-i+1)$。而 $h=\max(x)$，那么，形式化地，有：

$$
h=\max_{1\le i\le n}\min(c_i,n-i+1)
$$

现在我们知道了如何在 $O(n)$ 内求 $h$，即 $l=0$ 时的情况，下面讨论如何通过将 $l$ 个 $c_i$ 增加 $1$ 最大化 $h$。

令 $(n-p+1)\sim n$ 共 $p$ 篇文章的引用次数大于等于 $h$，且由于已经排序，$c_{n-p+1}\le c_{n-p+2}\le\cdots\le c_{n-1}\le c_n$。若 $c_{n-p+1}\neq c_n$，那必然存在一个 $q_1$ 使得 $c_{n-p+1}=c_{n-p+2}=\cdots=c_{q_1}<c_{q_1+1}\le\cdots\le c_n$。为了使 $h$ 尽可能大，考虑将 $c_{n-p+1}\sim c_{q_1}$ 依次增加 $1$。

此时，若还没用完 $l$ 次，那么必然存在一个 $q_2$ 使得 $c_1\le c_2\le\cdots\le c_{q_2-1}<c_{q_2}=c_{q_2+1}=\cdots=c_{n-p-1}=c_{n-p}$，将 $c_{q_2}\sim c_{n-p}$ 依次增加 $1$。若还没用完，使用二分重新计算 $h,p,q_2$，重复本段中上述过程直到用满 $l$ 次操作。

另外注意，「她只能引用每篇她的论文至多一次」。

时间复杂度 $O(n\log n+l)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, l, c[N];
int f() {
	sort(c + 1, c + n + 1);
	int h = -1;
	for(int i = n; i >= 1; i--) 
		h = max(h, min(c[i], n - i + 1)); 
	return h;
} 
signed main() {
	cin>>n>>l;
	for(int i = 1; i <= n; i++) cin>>c[i];
	int h = f(), p = lower_bound(c + 1, c + n + 1, h) - c, ll = l;
	for(int i = p; ll; ll--) {
		if(c[i] == c[p] && ll != l) break;	
		c[i]++, i++;
	}
	h = f(), l = ll;
	for(int i = h - 1; i >= 0 && ll; i--) {
		p = lower_bound(c + 1, c + n + 1, i) - c;
		for(int j = p; ll; ll--) {
			if(c[j] == c[p] && ll != l) break;
			c[j]++, j++;
		}
	}
	cout<<f()<<endl;
	return 0;
}
```

---

## 作者：precho (赞：1)

### **题目含义**

稍微有一点点绕，我们需要找到一个最大的 $h$ 指数，使得至少有 $h$ 篇文章引用次数大于等于 $h$ 次。

### **题目思路**

**1.主要思路**：二分，设定一个右边界 `r = n`  和左边界 `l = 0`，$mid$ 的值代表可能的  $h$  值。（因为 $h$ 的值一定小于或等于文章数 $n$，所以右边界`r = n`）如果 $mid$ 值满足条件，则表示 $mid$ 值可能还可以更大，更新左边界`l = mid + 1`，否则更新右边界`r = mid - 1`。

**2.check 函数逻辑**：

- 由后向前遍历（由大到小），如果 `line[i] >= x`，则满足条件，继续遍历。

- 如果`line[i] < x`。再分两种情况，分别是 `line[i] + 1 == x` 和 `line[i] + 1 < x`。第一种情况下，`sum++`（可以通过引用至多一次，使得 `line[i] + 1 == x` ），第二种情况表示即使引用一次后也不满足条件，则可以提前终止遍历（`return 0;`）。最后再判断 $sum$ 的值是否超过了最大引用次数  $L$，超过了就 `return 0`， 没超过就 `return 1`。

**3.细节注意**：

- 每个文章最多可以增加一次引用。

- check 函数设计遍历边界为 `i >= n - x` 是因为对于一个设定的 $x$ 值只需要从后向前遍历长度为 $x$ 的序列就足够了（贪心）。


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, L, line[100010];

bool check(int x) {
    int sum = 0;
    for (int i = n - 1; i >= (n - x); i--) {
        if (line[i] + 1 == x) sum += x - line[i];
        else if (line[i] + 1 < x) return 0;
    }
    if (sum <= L) return 1;
    else return 0;
}

int main() {
    cin >> n >> L;
    int r = n, l = 1, ans = 0;
    for (int i = 0; i < n; i++) cin >> line[i];
    sort(line, line + n);
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    cout << r << endl;
    return 0;
}
```

---

