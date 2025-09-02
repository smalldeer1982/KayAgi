# Chamo and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, Chamo gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Mocha doesn't like arrays containing different numbers, so Mocha decides to use magic to change the array. Mocha can perform the following three-step operation some (possibly, zero) times:

1. Choose indices $ l $ and $ r $ ( $ 1 \leq l < r \leq n $ )
2. Let $ x $ be the median $ ^\dagger $ of the subarray $ [a_l, a_{l+1},\ldots, a_r] $
3. Set all values $ a_l, a_{l+1},\ldots, a_r $ to $ x $

Suppose $ a=[1,2,3,4,5] $ initially:

- If Mocha chooses $ (l,r)=(3,4) $ in the first operation, then $ x=3 $ , the array will be changed into $ a=[1,2,3,3,5] $ .
- If Mocha chooses $ (l,r)=(1,3) $ in the first operation, then $ x=2 $ , the array will be changed into $ a=[2,2,2,4,5] $ .

Mocha will perform the operation until the array contains only the same number. Mocha wants to know what is the maximum possible value of this number.

 $ ^\dagger $ The median in an array $ b $ of length $ m $ is an element that occupies position number $ \lfloor \frac{m+1}{2} \rfloor $ after we sort the elements in non-decreasing order. For example, the median of $ [3,1,4,1,5] $ is $ 3 $ and the median of $ [5,25,20,24] $ is $ 20 $ .

## 说明/提示

In the first test case, $ a=[1,2] $ . Mocha can only choose the interval $ (l,r)=(1,2) $ . The array will be changed to $ a=[1,1] $ . Therefore, the answer is $ 1 $ .

In the second test case, Mocha can perform the following operations:

- Choose the interval $ (l,r)=(4,5) $ , then $ a=[1,2,3,4,4] $ .
- Choose the interval $ (l,r)=(3,5) $ , then $ a=[1,2,4,4,4] $ .
- Choose the interval $ (l,r)=(1,5) $ , then $ a=[4,4,4,4,4] $ .

The array contains only the same number, which is $ 4 $ . It can be proven that the maximum value of the final number cannot be greater than $ 4 $ .

## 样例 #1

### 输入

```
2
2
1 2
5
1 2 3 4 5```

### 输出

```
1
4```

# 题解

## 作者：cute_overmind (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1975C)

### 题目大意
给你一个长度为 $n$ 的**序列**，在原来的序列中选一个**区间**，令这个区间变成**区间的中位数**。现在要将这个序列变成**只有一种数**的区间，求这个数的**最大值**。

### 题目分析

直接由题可得：

- 结论一：第一次操作的数一定是全局解。

- 结论二：第一次操作选择连续三个的一定最优。

证明结论二：考虑第一次最优操作。

若此时选择长度为二，再加入一个答案只增不减。

若长度大于 $3$ 显然可以消除一部分使答案相等。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int a[N];
void solve()
{
	int n , ans = 0;
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 2;i <= n;i++){
		int c[5];
		c[1] = a[i - 2];
		c[2] = a[i - 1];
		c[3] = a[i];
		sort(c + 1, c + 4);
		ans = max(c[2] , ans);
	}
	cout << ans << '\n';
}
signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：xhhhh36 (赞：6)

[传送门](https://www.luogu.com.cn/problem/CF1975C)

首先可以证明一旦数组 $a$ 中一旦有某个长度至少为 $2$ 的子区间中的数全部等于 $x$，可以通过操作使整个数组 $a$ 均为 $x$：因为每次向这个子区间的左边或右边扩展一个位置得到新的区间，此时这个新的区间满足区间中位数为 $x$，那么选取这个新的区间进行一次操作可以使这个新的区间中所有的数都变为 $x$。那么可以通过这样的变化方式让整个数组都变为 $x$。

那么原问题就转化为：将这个数组通过操作使一个长度至少为 $2$ 的子区间中全部的数等于 $x$，求满足的 $x$ 的最大值。

那么可以直接按照题意来分类讨论。

设 $0$ 表示这个数 $< x$，$1$ 表示这个数 $\ge x$（不包括 $x$ 本身）。因为一个数 $x$ 成为 $a$ 数组某个长度为 $len(len\ge 2)$ 的子区间的中位数的条件为这个区间内 $0$ 的个数等于 $1$ 的个数或者 $0$ 的个数 $+1$等于 $1$ 的个数。

- 当 $len=2$ 时，子区间内的另一个数必须 $\ge x$，那么子区间只能为 $1,x$ 或 $x,1$。

- 当 $len=3$ 时，子区间中必须有一个数 $\ge x$，另一个数 $< x$，但是如果这个子区间中出现了 $x,1$ 或 $1,x$ 的情况，就与 $len=2$ 的情况重复了，所以增加的情况只有 $1,0,x$ 和 $x,0,1$。

- 当 $len\ge 4$ 时，要分情况讨论。当 $len$ 为偶数时，共有 $len\div 2$ 个 $1$，加上 $x$ 本身共有 $len\div 2+1$ 个 $\ge x$ 的数，所以无论怎么排列顺序一定会出现 $1,1$ 或者 $x,1$ 在一起的情况。那么此时根据 $len=2$ 的情况一定会出现 $\ge x$ 的答案。当 $len$ 为奇数时，如果要不与 $len=2$ 的情况重复，那么 $x$ 和 $1$ 不能相邻，那么此时区间只能为 $\dots,1,0,x,0,1,\dots$，此时一定会出现 $x,0,1$ 的区间，和 $len=3$ 的情况重复。所以，只需要处理前两种情况即可。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N=1e5+5;
int n,a[N],t,mx;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while (t--){
		cin>>n;
		mx=0;
		for (int i=1;i<=n;i++){
			cin>>a[i];
		}
		a[n+1]=0;
		for (int i=1;i<=n;i++){
			if (a[i]<=a[i-1]||a[i]<=a[i+1]){
				mx=max(mx,a[i]);
			}
		}
		for (int i=2;i<n;i++){
			if (a[i-1]>=a[i]&&a[i]<=a[i+1]){
				mx=max(mx,min(a[i-1],a[i+1]));
			}
		}
		cout<<mx<<endl;
	}
	return 0;
}
```

---

## 作者：lyhqwq (赞：6)

# Solution

提供一个 $O(n)$，做法。

显然，如果我们可以将序列变化出相邻的两个相同的数，那么这个数一定可以成为答案。

对于一个数 $a_i$，若 $a_{i+1} \geq a_i$ 或 $a_{i-1} \geq a_i$，则 $a_i$ 可以成为答案。

否则，若 $a_{i+2} \geq a_i$ 或 $a_{i-2} \geq a_i$，则 $a_i$ 可以成为答案。

其他情况，若 $a_i$ 为答案，那么一定存在两个相邻的比 $a_i$ 大的数，$a_i$ 一定不优。

# Code
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=1e5+5;
    int _;
    int n;
    int a[N];
    int main(){
    	//freopen(".in","r",stdin);
    	//freopen(".out","w",stdout);
    	scanf("%d",&_);
    	while(_--){
    		scanf("%d",&n);
    		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    		int ans=0;
    		for(int i=1;i<=n;i++){
    			if(i-1>=1&&a[i-1]>=a[i]) ans=max(ans,a[i]);
    			if(i+1<=n&&a[i+1]>=a[i]) ans=max(ans,a[i]);
    			if(i-2>=1&&a[i-2]>=a[i]) ans=max(ans,a[i]);
    			if(i+2<=n&&a[i+2]>=a[i]) ans=max(ans,a[i]);
    		}
    		printf("%d\n",ans);
    	}
    	return 0;
    }
     
```

---

## 作者：sbno333 (赞：4)

看到不会的题想想二分。

假设答案大于等于 $x$，则可以将大于等于 $x$ 的数视作 $1$，其他数视作 $0$，要求全员变 $1$。

我们只需要求出是否可以进行一次有利操作即可，如果可以，则此时会有一个长度至少为 $2$ 的连续 $1$ 子串，然后每次一定能找到形如 $0,1,1$ 或 $1,1,0$ 的串并进行改变，直到最终都变为 $1$。

那么对于可以进行操作，显然当且仅当存在一个子串，$1$ 的数量**多于** $0$ 的数量。

那么 $1$ 的数量减 $0$ 的数量大于 $0$。

我们设 $1$ 为 $1$，$0$ 为 $-1$，找到一个和大于 $0$ 的长度至少为 $2$ 的子串。

枚举每一个右边界，每次找到一个能让区间和最大且长度大于等于 $2$ 的左边界，可以转化成寻找一个最小的前缀和并减去，判断区间和是否大于 $0$，如果是，则一定能将 $0$ 变成 $1$，或有连续的 $1$ 的区间，对于后者，显然是可以做到全变 $1$ 的。

于是代码就出啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000009];
int n;
int qz[1000009];
bool ck(int x){
	for(int i=1;i<=n;i++){
		if(a[i]>=x){
			qz[i]=1;
		}else{
			qz[i]=-1;
		}
		qz[i]+=qz[i-1];
	}
	int mi;
	mi=0;
	for(int i=2;i<=n;i++){
		if(qz[i]-mi>0){
			return 1;	
		}
		mi=min(mi,qz[i-1]);
	}
	return 0;
}
void _main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l,r;
	l=1,r=1e9+7;
	while(l<r){
		int mid;
		mid=l+r+1;
		mid>>=1;
		if(ck(mid)){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	cout<<l<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：AKPC (赞：1)

显然，区间长度为 $2$ 的时候，被修改为最小值，当区间长度为 $3$ 且有两个数均为一个值 $v$，那么整个区间都被改成 $v$，那就先操作一个区间长度 $2$，然后进一步延申就可以把整个数列覆盖。

但如果只考虑这个，对于 $\{5,4,5,4,5\}$ 这种数据就是错的，~~罚时寄~~。

其实如果考虑区间长度为 $3$，那会被改成大小上中间那个值，这就应对了特殊情况，但其实区间长度 $3$ 可以直接代替长度 $2$。

[code](https://www.luogu.com.cn/paste/6tgjzzmw)。

---

## 作者：zhanglh (赞：1)

中位数只考虑相对大小，把大于等于 $x$ 的赋为 $1$，把小于 $x$ 的赋为 $0$。二分 $x$，若存在长度为 $3$ 的区间满足区间和大于等于 $2$ 则返回 $\text{true}$，否则返回 $\text{false}$。

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 100010;

int n, a[N], b[N], c[N];

template <typename T> inline void read(T &x) {
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}

inline bool check(int x) {
    for (int i = 1; i <= n; i ++ ) {
        if (a[i] >= x) c[i] = 1;
        else c[i] = 0;
        c[i] += c[i - 1];
    }
    for (int i = 1; i <= n - 2; i ++ )
        if (c[i + 2] - c[i - 1] >= 2) return true;
    return false;
}

inline void solve() {
    read(n);
    for (int i = 1; i <= n; i ++ ) read(a[i]);
    memcpy(b, a, sizeof b);
    sort(b + 1, b + n + 1);
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(b[mid])) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", b[r]);
}

int main() {
    int T;
    read(T);
    while (T -- ) solve();
    return 0;
}
```

---

## 作者：SFlyer (赞：0)

你考虑到如果有两个相同的连续元素了，我们一定可以把这个序列全部变为这个元素。怎么出现两个相同元素呢？容易发现操作 $>3$ 的长度的区间是不优的，一定可以拆成更多的小区间。所以只需要判断 $2,3$ 长度的即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5+5;

int n,a[N];

void solve(){
	cin>>n;
	a[0]=a[n+1]=0;
	for (int i=1; i<=n; i++){
		cin>>a[i];
	}
	int mx=0;
	for (int i=1; i<=n; i++){
		if (a[i-1]>=a[i] || a[i+1]>=a[i]){
			mx=max(mx,a[i]);
		}
		if (i>=3){
			if (a[i-2]>=a[i]){
				mx=max(mx,a[i]);
			}
		}
		if (i+2<=n){
			if (a[i+2]>=a[i]){
				mx=max(mx,a[i]);
			}
		}
	}
	cout<<mx<<"\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：2huk (赞：0)

> - 给定一个长度为 $n$ 序列 $a$，每次操作可以用一个区间内数字的中位数替换这个区间内所有数。求将 $a$ 中所有数变得相同后这个数的最大值。
> - $n \le 2 \times 10^5$，$a_i \le 10^9$。

二分答案 $x$。令 $b_i = \left\{\begin{matrix} 1 & a_i \ge x\\ -1 & a_i < x\end{matrix}\right.$。问题转化成：

- 每次选择一个 $b$ 中和 $\ge 1$ 的区间 $[l, r]$，将 $[l, r]$ 推平成 $1$，能否将 $b$ 全部变成 $1$。

该问题等价于是否存在 $b_i = b_{i + 1} = 1$ 或 $b_i = b_{i+2} = 1$。考虑证明：

- 充分性（若存在 $b_i = b_{i + 1} = 1$ 或 $b_i = b_{i+2} = 1$ 则能将 $b$ 全部变成 $1$）：若某个 $i$ 满足 $b_i = b_{i + 1} = 1$ 或 $b_i = b_{i + 2} =1$，此时区间 $[i, i + 2]$ 中 $1$ 的个数一定 $\ge 2$，那么我们可以先将 $[i, i + 2]$ 推平成 $1$，再将 $[i, i + 3]$ 推平成 $1$，依次类推，最终总能将 $b$ 全部推平成 $1$。
- 必要性（若能将 $b$ 全部变成 $1$ 则存在 $b_i = b_{i + 1} = 1$ 或 $b_i = b_{i+2} = 1$）：考虑证明其逆否命题。若不存在 $b_i = b_{i + 1} = 1$ 且不存在 $b_i = b_{i+2} = 1$，那么 $b$ 一定可以被表示为 $([-1], 1, -1, -1, [-1], 1, -1, -1, [-1], 1, \dots)$ 的形式，其中 $[-1]$ 表示连续出现了若干个（可以 $0$ 个）$-1$。显然此时并不存在某个区间 $[l, r]$（$l < r$）的和 $\ge 1$，也就不能将 $b$ 全部变成 $1$。因此原命题成立。

```cpp
bool chk(int mid) {
	for (int i = 2; i <= n; ++ i )
		if (a[i] >= mid && a[i - 1] >= mid) return true;
	for (int i = 3; i <= n; ++ i )
		if (a[i] >= mid && a[i - 2] >= mid) return true;
		return false;
}
 
void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	int l = 1, r = 1e9, res = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (chk(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	
	fout << res << '\n';
}
```

---

