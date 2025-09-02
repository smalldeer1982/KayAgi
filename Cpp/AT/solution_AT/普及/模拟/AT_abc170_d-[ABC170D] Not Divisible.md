# [ABC170D] Not Divisible

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc170/tasks/abc170_d

長さ $ N $ の数列 $ A $ が与えられます。

次の性質を満たす整数 $ i $ $ \left(1\ \leq\ i\ \leq\ N\ \right) $ の数を答えてください。

- $ i\ \neq\ j $ である任意の整数 $ j $ $ \left(1\ \leq\ j\ \leq\ N\right) $ について $ A_i $ は $ A_j $ で割り切れない

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $

### Sample Explanation 1

問の性質を満たすのは $ 2 $ , $ 3 $ , $ 4 $ です。

### Sample Explanation 2

同じ数が存在する場合に注意してください。

## 样例 #1

### 输入

```
5
24 11 8 3 16```

### 输出

```
3```

## 样例 #2

### 输入

```
4
5 5 5 5```

### 输出

```
0```

## 样例 #3

### 输入

```
10
33 18 45 28 8 19 89 86 2 4```

### 输出

```
5```

# 题解

## 作者：ruanwentao666 (赞：3)

# AT_abc170_d题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc170_d)

## 题目分析
可以先排序，再遍历，把 $a_i$ 的倍数标记一下，类似于埃氏筛。只要 $a_i$ 没有被标记过，答案就加一。

## 代码展示
附上 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],b[1000005];
long long ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(!b[a[i]]){
			if(a[i]!=a[i+1]){
				ans++;
			}
			for(int k=1;a[i]*k<=1000000;k++){
				b[a[i]*k]++;
			}
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：ljy_luogu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc170_d)

## 思路

先将数列从小到大排序，排序后遍历数组。对于第 $i(1 \le i \le n)$ 个数，若它没有被标记，标记上 $a[i]$ 的所有倍数并使答案自增。

最后输出答案即可。

## 代码

```cpp
#define int long long
using namespace std;

void qread(int& in) {//快读
	in = 0;
	bool flag = false;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') {
			flag = true;
		}
		c = getchar();
	}
	while (isdigit(c)) {
		in = in * 10 + (c - '0');
		c = getchar();
	}
	if (flag) {
		in = -in;
	}
	return;
}

int n, ans, maxn;//maxn为数组中最大值
int a[200010];
bool vis[1000010];//标记数组

signed main() {
	qread(n);
	for (int i = 1; i <= n; i++) {
		qread(a[i]);
		if (a[i] > maxn) {
			maxn = a[i];//更新最大值
		}
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (!vis[a[i]]) {
			if (a[i] != a[i + 1] && a[i] != a[i - 1]) {//去掉类似样例二的情况
				ans++;
			}
			for (int j = a[i]; j <= maxn; j += a[i]) {//标记到最大值即可
				vis[j] = true;
			}
		}
	}
	printf("%lld", ans);

	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/118224384)

代码还是比较快的，最慢的点也才用了 $32$ 毫秒。

---

## 作者：Lemonlwl (赞：1)

## AT_abc170_d [ABC170D] Not Divisible 题解
### 题意：

对于给定长度为 $N$ 的数列 $A$，找出满足条件的下标 $i$ 使得该数列中除 $a_i$ 以外的任意数都不能整除 $a_i$，求出满足条件的 $i$ 的个数。

------------

### 分析：
本题可以使用埃氏筛。

对于数列中的每个数，都可以把它们的倍数标记出来，如果在数列中遇到已经标记过的数就筛掉。

**注：在筛之前必须先排序，因为越小的数能筛除的数越多。**

------------

附上 [AC](https://www.luogu.com.cn/record/120948020) 代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,sum;
int a[1000005];
bool t[1000005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}  //输入。
	sort(a+1,a+n+1);  //排序后筛除的数最多，否则后面的数可能筛不掉。
	for(int i=1;i<=n;i++){
		if(!t[a[i]]){  //筛除。
			if(a[i]!=a[i+1]){  //去重。
				sum++;  //满足即累加答案。
			}
			for(int j=1;a[i]*j<=1e6;j++){  //按照范围标记。
				t[a[i]*j]=true;  //标记倍数。
			}
		}
	}
	cout<<sum<<endl;  //输出。
	return 0;
}
```


---

## 作者：Fiendish (赞：1)

一道非常有水平的黄题。

首先，理解题意。题目的意思是要求找出数列中有多少个数不能被数列中其他数整除。对于一个数来说，他的因数一定都小于等于它，所以我们想到对数列进行排序。

接下来，对于每一个数，都将它的倍数标记一下，思路很像筛法。如果当前这个数被标记过，那么它一定不符合要求。此时它的倍数也肯定已经标记过，就没有必要再标记了。最后需要注意，如果 $a_i$ 没有被标记过，就要检查一下 $a_{i+1}$ 是否和 $a_i$ 相等，如果相等，那么 $a_i$ 就不符合要求，不计入答案。

贴上代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[200010];
int vis[1000010],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;i++)
		if(!vis[a[i]]){//如果没有被标记过
			if(a[i]!=a[i+1]) ans++;//符合要求，累计答案
			for(int j=1;j*a[i]<=1e6;j++) vis[j*a[i]]=1;//标记，最大到1e6就可以
		}
	cout<<ans;
}
```
若有疏漏、不详之处，恳请各位大佬指点。

---

## 作者：mi_Y13c (赞：0)

### 算法分析

调和级数。

可以开一个桶 `cnt`，其中  `cnt[i]`  表示  $i$  作为倍数出现的次数。

我们可以枚举序列  $A$  中的每个数  $x$，然后将  $\left[x, 10^{6}\right]$  之间  $x$  的倍数的  $\operatorname{cnt}[i]$  都加上 $1$。

最后的答案就是  $\sum_{x \in A}[\operatorname{cnt}[x]=1] $。

但这样做的时间复杂度是  $O\left(\sum_{x \in A}\left\lfloor\frac{10^{6}}{x}\right\rfloor\right)$，会超时。

考虑进一步优化：

我们可以在遍历  $x$  时，如果此时  $\operatorname{cnt}[x] \neq 0$，那么可以直接将  $\operatorname{cnt}[\mathrm{x}]$  标记为 $2$ ，并跳过当前这次循环，因为已经确定了  $x$  在序列  $A$  中除自身外还有其他的约数。

### 最终代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using namespace std;

const int M = 1000005;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> cnt(M);
    for (int x : a) {
        if (cnt[x] != 0) {
            cnt[x] = 2;
            continue;
        }
        for (int i = x; i < M; i += x) cnt[i]++;
    }

    int ans = 0;
    for (int x : a) {
        if (cnt[x] == 1) ans++;
    }

    cout << ans << '\n';

    return 0;
}
```

---

## 作者：Underage_potato (赞：0)

## Solution

因为整除的性质，一个数的因数一定都小于等于它本身，所以我们可以对其进行排序，时期具有单调性，之后就只用对 $a_i$ 与 $a_i+1$ 进行比较就行了。

然后就是直接一遍埃氏筛，筛整除数就行了，注意一下标记的时候将其标到 $10^6$ 就行了，因为 $a_i$ 最大到 $10^6$。

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000100];
int ans;
bool f[1000100];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(!f[a[i]]){
			if(a[i]!=a[i+1]){
				ans++;
			}
			
			for(int j=1;a[i]*j<=1e6;j++){
				f[a[i]*j]=1;
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

