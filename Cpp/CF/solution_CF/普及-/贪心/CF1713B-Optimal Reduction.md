# Optimal Reduction

## 题目描述

Consider an array $ a $ of $ n $ positive integers.

You may perform the following operation:

- select two indices $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ), then
- decrease all elements $ a_l, a_{l + 1}, \dots, a_r $ by $ 1 $ .

Let's call $ f(a) $ the minimum number of operations needed to change array $ a $ into an array of $ n $ zeros.

Determine if for all permutations $ ^\dagger $ $ b $ of $ a $ , $ f(a) \leq f(b) $ is true.

 $ ^\dagger $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 说明/提示

In the first test case, we can change all elements to $ 0 $ in $ 5 $ operations. It can be shown that no permutation of $ [2, 3, 5, 4] $ requires less than $ 5 $ operations to change all elements to $ 0 $ .

In the third test case, we need $ 5 $ operations to change all elements to $ 0 $ , while $ [2, 3, 3, 1] $ only needs $ 3 $ operations.

## 样例 #1

### 输入

```
3
4
2 3 5 4
3
1 2 3
4
3 1 3 2```

### 输出

```
YES
YES
NO```

# 题解

## 作者：Epi4any (赞：6)

因为有这两个：
> $1 \leq$ t $\leq 10^4$，$1 \leq n \leq 10^5$

所以我们不难看出这道题最快的算法 $O(nt)$ 差不多能过去。

也就是说，我们需要用 $O(n)$ 的复杂度判断当前序列是不是最优的。

易见，如果一个序列的最大值为 $mx$ ，则这个序列最少需要 $mx$次操作才可以得到一个全 $0$ 的序列。

然后我们通过一些简单的找规律可以发现，能让次数最少当且仅当这个序列是一个山峰序列。（就是说有一个 $x$ 使 $a_1$，$a_2$，$...$，$a_x$ 为上升序列，$a_{x+1}$，$a_{x+2}$，$...$，$a_n$为下降序列）

然后我们就只需要**判断一个序列是不是山峰序列**就行了！

具体实现见代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int t, n;
int a[100005];

void solve() {
	bool f = true, ans = true;
	//f 为现在序列是否上升
	for (int i = 1; i <= n; i++) a[i] = read();

	for (int i = 2; i <= n; i++) {
		if (a[i] > a[i - 1]) {
			if (!f) {//如果现在在上升但是已经开始下降
				ans = false;//就不行
				break;
			}
		}
		if (a[i] < a[i - 1]) {
			f = false;//如果开始下降就标记为正在下降
		}
	}

	if (ans) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main() {
	t = read();
	while (t--) {
		n = read();
		solve();
	}
	return 0;
}
//结尾警告：理解思路 杜绝抄袭
```

---

## 作者：xiaomuyun (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1713B)

## 题目分析

我们思考一下，怎样的排列会让一个数组 $a$ 的 $f(a)$ 更大。

假设有一个数组 $a=\{1,2,3,5,4\}$，我们可以发现，当 $a$ 的一个排列 $b=\{1,3,2,5,4\}$ 时，$f(a)<f(b)$。这是为什么？

稍微想一想就可以发现，$f(a)<f(b)$ 是因为 $a$ 中几个相对较大的数都在一块，进行操作时可以一起减少，不用分段去减。

所以实际上，就是要在 $a$ 中寻找相对较大的数是否都在一块，换句话说，就是找坑（$a_{i-1}>a_i<a_{i+1}$）。比如说 $b$ 中的 $3,2,5$ 就是一个坑。找到坑之后，我们就会发现如果把坑两边的两个 相对坑中间的数 较大的数放在一起，$f$ 函数求出来之后就会更优，因此把坑消掉就是更优的答案。
## 代码实现
实现时要注意，像 $7,4,4,8$ 这样的也是一个坑，要注意不要判断错了。

```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1e5+1;
int t,n,a[maxn];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		bool flag=false,res=false;
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			if(i==1) continue;
			if(a[i]<a[i-1]) flag=true;//判断是否是坑的下坡
			else if(a[i]>a[i-1]){//判断是否是坑的上坡
				if(flag) res=true;
				flag=false;
			}
		}
		if(!res) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：yingkeqian9217 (赞：3)

这题面看起来很绕，其实核心就是操作部分。

因为总和不变，所以可以看做一次在 $ ( l , r ) $ 减一个数，这个数就是 $ ( l , r ) $ 中的最小值。

最好的办法就是不断地加最小值，减到 0 的不再减：

![](https://cdn.luogu.com.cn/upload/image_hosting/78jvsfb0.png)

但是这样有一个问题：操作针对的区间必须对于 **原数组** 连续，否则就需要分成几次减去各自的最小值：

![](https://cdn.luogu.com.cn/upload/image_hosting/6jfsbbq3.png)

由此推出， 最好方案一定是区间（减去后）永远连续的。

而显然，所谓的“山峰序列”就是最优解：

![](https://cdn.luogu.com.cn/upload/image_hosting/3lm35fqq.png)

问题就转换成了判断一个序列是否是“山峰序列”，
由此可见，问题的转化是多么重要。

这还不 ~~是有手就行~~ 简单，其他细节详见代码。

 $\large\texttt{AC  }_{\large\texttt{Code:}}$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100001];
bool judge(){//判断山峰
	int maxn=0,maxid;//记录最大值数值及坐标
	for(int i=1;i<=n;i++)
	 if(a[i]>maxn){
	 	maxn=a[i];//求最大值
	 	maxid=i;
	 }
	for(int i=1;i<maxid;i++) if(a[i]>a[i+1]) return 0;//最大值左边，应该呈不下降子序列
	for(int i=maxid;i<n;i++) if(a[i]<a[i+1]) return 0;//最大值右边，应该呈不上升子序列
	return 1;
}
int main(){
	cin>>t;
	while(t--){//多组数据，忘了就悲催了
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(judge()) cout<<"Yes"<<endl;//CF良心，不区别大小写
		else cout<<"No"<<endl;
	}
	
}//完美收官
```

画图不易，给个赞吧

---

## 作者：Toothless03 (赞：1)

~~水一篇题解~~

可以发现一个数列 $a$ 的最少操作次数的下限是是 $f(a) \ge \max\{a[i]\}$ ，因为需要把最大的数减为 $0$ 。所以对于 $a$ 的某个排列 $b$ ，其中 $\max\{a[i]\}=\max\{b[i]\}$ ， 既 $f(b) \ge \max{a[i]}$。

为了方便，我们设数值等于 $\max\{a[i]\}$ 其中一个的脚标为 $k$ 。

在 $a$ 的排列中，操作数为 $a[k]$ 的存在性：

> 将 $a$ 排序，得到序列 $b$ ， $b$ 的操作次数为 $\max\{b[i]\}=\max\{a[i]\}$ ，所以一定存在。

辣么如何判断一个序列 $a$ 的操作次数是否为 $a[k]$ （期望最少操作次数）呢。

> 对于最大数 $k$ 的左侧，每次操作完 $l$ 应该不动或向右移，既左侧单调不减。同理，对于 $k$ 右侧，每次 $r$ 应不动或向左移，既右侧单调不增。所以只需判定 $a[0]\le a[1]\le a[2]\cdots\le a[k], a[k]\ge a[k+1]\ge a[k + 2]\cdots a[n - 2]\ge a[n - 1]$ 。

贴上核心代码：
（貌似我的脚标从 $0$ 开始）
```cpp
int l = 0, r = n - 1;
while (l < n -1 && arr[l + 1] >= arr[l])
	l++;
while (r >= 1 && arr[r - 1] >= arr[r])
	r--;
if (l >= r)
	cout << "YES" << endl;
else
	cout << "NO" << endl;
```

---

## 作者：Jeremiahy (赞：0)

### 题意

给一个序列 $a$，每次可以将下标 $l$ 到 $r$ 的部分减 $1$（$l,r$ 自行选择），问 $a$ 是否是它的所有排列中将元素全部减到 $0$ 所用次数最少的一种，（即不存在 $a$ 的另一种排列 $b$ 使得将 $b$ 全部减为 $0$ 的次数更少）。

## 分析

经过一些模拟，我们发现：如果存在凹坑，那肯定有更少的。因为我们可以先 $a$ 序列全部减，中间的凹坑会先到 $0$，这时把 $a$ 序列分成了两个部分，操作次数增多，而如果是一个山峰形状，可以一直连贯地减。

所以，我们只需要判断是否是山峰（或者山峰的一侧）即可。判断方法是找到最大值，向左向右遍历都要是单调不增的才满足。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, a[200005];
signed main () {
	cin >> t;
	while (t--) {
		bool flag = 0;
		int ans = 1;
		cin >> n;
		for (register int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[ans] < a[i]) 
				ans = i;//最大值
		}
		for (register int i = ans - 1; i >= 1; i--)
			if (a[i] > a[i + 1])//存在凹坑（不是单调不增
				flag = 1;
		for (register int i = ans + 1; i <= n; i++)
			if (a[i] > a[i - 1])
				flag = 1;
		puts((flag ? "NO" : "YES"));
	}
	return 0;
}
```


---

## 作者：cachejtt (赞：0)

## 题意
给你一个序列，可以进行若干次操作，每次操作为选取一个 $l$ 与 $r$，你可以将 $a_l,a_l+1,\dots,a_r$ 全部减去 $1$，记 $f(a)$ 为将 $a$ 数组全部变为 $0$ 所需要的步数。

设 $b$ 为 $a$ 的一个排列，若对于任意 $b$，$f(b)\le f(a)$， 则我们称 $a$ 为好的。给你一个序列 $a$，问你是否是好的。

## 思路
由于我们需要对区间进行全部减一，因此对于一个区间，单增或单减总是最优秀的。所以对于整个区间，若其是一个单增或单减的数列，则它是好的。

再考虑一个单峰的序列，即先单增，再单减，显然也是好的。但对于不止一次下降的序列，就是不好的。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t,n,a[100005],flag1,flag2,ab;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    flag1=0;
    flag2=0;
    cin>>n;
    ab=1;
    rep(i,1,n){
      cin>>a[i];
    }
    rep(i,2,n){
      if(a[i]>a[i-1]){
        if(flag2==1)ab=0;
        flag1=1;
      }
      if(a[i]<a[i-1]){
        flag2=1;
      }
    }
    if(ab)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
  }
  return 0;
}
``

---

## 作者：Ender_hz (赞：0)

# 题意

给定一个长度为 $n(1\le n\le10^5)$ 的数组 $a$，你可以进行若干次操作，每次操作，你可以选择两个数 $l,r(1\le l \le r \le n)$，让 $a_l,a_{l+1},\cdots,a_r$ 各自减 $1$，记 $f(a)$ 为使数组 $a$ 的每个元素均变成 $0$ 所需要的最小操作次数，请你判断对于 $a$ 打乱后的任意排列 $b$，是否有 $f(a)\le f(b)$ 恒成立。



# 分析

我们不妨考虑数组 $a$ 打乱后的任意排列中（包括 $a$ 本身），函数 $f$ 的最小值以及取到最小值需要的条件。

由于数组的末状态为每个元素均为 $0$，所以不可能对已经等于 $0$ 的元素进行操作；又因为每次操作选择的都是连续区间，所以应该保证操作后 $0$ 一定出现在数组的两端（或一端）。

为了满足上述条件，不难想到原数组应满足的条件：由一段非严格单调递增序列和一段非严格单调递减序列构成，或由两者之一构成；这时 $f$ 函数取到最小值，即 $\max(a_i)$。

满足这样的排列有很多种，我们只需判断 $a$ 数组是否满足上述条件即可。

# 代码

```cpp
#include<iostream>
#define sfor(i, h, t) for(int i = (h); i <= (t); ++i)
using namespace std;
const int MAXN = 0x186A8;
int T = 1, N;
int num[MAXN];
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N;
        bool f = 0, g = 0;
        sfor(i, 1, N) {
            cin >> num[i];
            if(g)
                continue;
            if(!f)
                if(num[i] < num[i - 1])
                    f = 1;
            if(f)
                if(num[i] > num[i - 1])
                    g = 1;
        }
        cout << (g ? "NO\n" : "YES\n");
    }
    return 0;
}
```



---

## 作者：lsj2009 (赞：0)

## Problem

给定序列 $\{a_n\}$，你可以进行若干次操作：

- 选定区间 $[l,r]$，将 $a_{l\sim r}$ 中的数减一。

记 $f(a)$ 为将序列 $\{a_n\}$ 操作至全 $0$ 序列的最少操作数。

求 $\{a_n\}$ 是否满足对于 $\{a_n\}$ 的任意排列 $\{a_i'\}$ 都有 $f(a)\le f(a')$。 

$\sum n\le 10^5,a_i\le10^9$。

link-><https://codeforces.com/contest/1713/problem/B>。

## Solution

显然有 $f(a)=\sum\limits_{i=1}^n [a_i\ge a_{i-1}](a_i-a_{i-1})$，具体可见 <https://www.luogu.com.cn/problem/P1969>，这里不再赘述。观察样例，发现满足条件的排列都满足前半部分单调递增，后半部分单调递减，尝试证明这一点：

构造序列 $\{a_n'\}$ 为原满足条件的序列 $a$ 交换数对 $(a_i,a_{i+1}),a_i> a_{i+1}$，显然交换后 $a_i<a_{i+1}$，这时对答案就会产生 $a_i<a_{i+1}$ 的贡献，显然不比交换前更优。同理，我们如果不断按上述方法交换，答案始终不更优。


## Code

```
#include<bits/stdc++.h>
#define F fisrt
#define S second
#define INF 0x7fffffff
#define inf 0x3f3f3f3f
#define inf 0x3f3f3f3f3f3f3f3f
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e5+5;
int T,n,a[N];
signed main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		_for(i,1,n)
			scanf("%d",&a[i]);
		int ans=0,p=1;
		while(a[p]>=a[p-1])
			++p;
		while(a[p]<=a[p-1])
			++p;
		puts(p<=n? "NO":"YES");
	}
	return 0;
}
```

---

