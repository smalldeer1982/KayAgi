# Absent Remainder

## 题目描述

You are given a sequence $ a_1, a_2, \dots, a_n $ consisting of $ n $ pairwise distinct positive integers.

Find $ \left\lfloor \frac n 2 \right\rfloor $ different pairs of integers $ x $ and $ y $ such that:

- $ x \neq y $ ;
- $ x $ and $ y $ appear in $ a $ ;
- $ x~mod~y $ doesn't appear in $ a $ .

Note that some $ x $ or $ y $ can belong to multiple pairs.

 $ \lfloor x \rfloor $ denotes the floor function — the largest integer less than or equal to $ x $ . $ x~mod~y $ denotes the remainder from dividing $ x $ by $ y $ .

If there are multiple solutions, print any of them. It can be shown that at least one solution always exists.

## 说明/提示

In the first testcase there are only two pairs: $ (1, 4) $ and $ (4, 1) $ . $ \left\lfloor \frac 2 2 \right\rfloor=1 $ , so we have to find one pair. $ 1~mod~4=1 $ , and $ 1 $ appears in $ a $ , so that pair is invalid. Thus, the only possible answer is a pair $ (4, 1) $ .

In the second testcase, we chose pairs $ 8~mod~2=0 $ and $ 8~mod~4=0 $ . $ 0 $ doesn't appear in $ a $ , so that answer is valid. There are multiple possible answers for that testcase.

In the third testcase, the chosen pairs are $ 9~mod~5=4 $ and $ 7~mod~5=2 $ . Neither $ 4 $ , nor $ 2 $ , appears in $ a $ , so that answer is valid.

## 样例 #1

### 输入

```
4
2
1 4
4
2 8 3 4
5
3 8 5 9 7
6
2 7 5 3 4 8```

### 输出

```
4 1
8 2
8 4
9 5
7 5
8 7
4 3
5 2```

# 题解

## 作者：Jerrlee✅ (赞：4)

## 题意
在长为 $n$ 的数组中找 $[n/2]$ 对 `pair`，每一对 $(x,y)$ 中，$x$ 和 $y$ 在数组中出现过，但 $x \bmod y$ 没有出现过。
## 思路
可以发现：$x \bmod y<y$。

因此，选择 $y$ 作为序列中的最小数时（$x$ 为任意值），至少可以获得 $n−1$ 对。可取 $n-1 \geq [n/2]$ 对。

每个测试组是 $O(n)$ 的时间复杂度。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a(n);
        for(int &x:a) cin>>x;
        int mn=*min_element(a.begin(),a.end()); //取最小值
        for(int i=0,k=0;k<n/2;i++) if(a[i]!=mn){
            cout<<a[i]<<' '<<mn<<'\n';
            k++;
        }
    }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/64189244)

[AC记录（CF）](https://codeforces.com/contest/1613/submission/137892732)

---

## 作者：沉石鱼惊旋 (赞：2)

题目说了，每组数不同，并且 $x$ $mod$ $y$ 也不出现在数组$a$中，那么我们可以对数组进行**排序**，因为 $a$ $mod$ $b$ 得出的结果是**一定比 $b$ 小的**。那么拿数组的其他数分别去取模最小的数，那么得出的结果一定比数组最小的数还小，则一定**不可能出现**在数组 $a$ 之内。

简单解释一下这个数据：

$6$

$2$ $7$ $5$ $3$ $4$ $8$

按我的思路，则会排序成以下数组：

$2$ $3$ $4$ $5$ $7$ $8$ 

$3$ $mod$ $2$ 不在数组 $a$ 中

$4$ $mod$ $2$ 不在数组 $a$ 中

$5$ $mod$ $2$ 不在数组 $a$ 中

$7$ $mod$ $2$ 不在数组 $a$ 中

$8$ $mod$ $2$ 不在数组 $a$ 中

贴代码：

```cpp
void solve()
{
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++) 
	{
		cin>>a[i];
	}
	sort(a,a+n);
	for(int i=0;i<n/2;i++)//n/2组数据即可 
	{
		cout<<a[n-i-1]<<" "<<a[0]<<endl;//分别输出x与y,注意顺序，必须x在前y在后 
	}
}
```
多组数据，代码未全，当心踩坑


---

## 作者：AFewSuns (赞：1)

### 题目大意

给你 $n$ 个不同的正整数 $\{a_i\}$，现在你要从中选出 $\lfloor \frac{n}{2} \rfloor$ 对不同的数对，使得每一个数对 $(x,y)$ 满足 $x \neq y$，$x$ 和 $y$ 在 $a$ 序列当中，且 $x \bmod y$ 不在 $a$ 序列当中。

多组数据。$t \leq 10^4$，$2 \leq n \leq 2\times 10^5$，$\sum{n} \leq 2\times 10^5$

### 题目分析

$(x,y)$ 的前两个条件我们可以选择性忽略，毕竟最大的难点在于第三个条件。

考虑怎么保证 $x \bmod y$ 不在 $a$ 序列当中。如果满足 $y$ 是 $a$ 中的最小值，那么 $0 \leq x \bmod y < y$，一定不在 $a$ 当中。否则与 $y$ 是 $a$ 中的最小值矛盾。

发现了这个性质，其实就已经做完了。把 $a_i$ 从小到大排序，然后随便选取 $\lfloor \frac{n}{2} \rfloor$ 个数与 $a_1$ 配对。

因为 $n \geq 2$，所以一定能从除了 $a_1$ 的数中选 $\lfloor \frac{n}{2} \rfloor$ 个数。

时间复杂度 $O(n \log n)$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200020];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n/2;i++) printf("%d %d\n",a[n-i+1],a[1]);
	}
}
```

---

## 作者：LYqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1613B)
# 题目大意
在一个长度为 $n$ 的序列中，找出 $\lfloor \cfrac{n}{2} \rfloor$ 个不同的二元组 $(x,y)$，满足一下性质：  
- $x \neq y$。
- $x$ 和 $y$ 均在序列中。
- $x \bmod y$ 不在序列中。

# 思路
前两条性质很容易实现，关键是第三条。
> $x \bmod y$ 不在序列中。  

我们可以发现，无论如何，$x \bmod y$ 的结果总是比 $y$ 小。  
这样我们就可以很容易地解决这一条性质，先将序列排序，这样第一位就是最小值，把它当作 $y$。接着，再从序列中随便调出 $\lfloor \cfrac{n}{2} \rfloor$ 个数来充当 $x$ 就 ok 了qwq。  
排序之后，从第二项遍历到第 $\lfloor \cfrac{n}{2} \rfloor +1$ 项，每次输出二元组。  
$\lfloor \cfrac{n}{2} \rfloor +1$ 可以使用位运算优化，记得位运算符优先级很低，要加上括号再加一：`(n>>1)+1`。

# 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int t,n,a[200005];

int main(){
	cin >> t;
	while(t--){
		cin >> n;
		for(int i=1; i<=n; i++){
			cin >> a[i];
		}
		sort(a+1,a+n+1);
		for(int i=2,l=(n>>1)+1; i<=l; i++){
			cout << a[i] << " " << a[1] << endl;
		}
	}
	return 0;
}
```

---

## 作者：miao5 (赞：0)

这道题有一个性质，当我们使 $y=\min\{a_1,a_2,a_3,\dots,a_n\}$，$x$ 为序列中除 $y$ 以外任意值时，由 $x$ 和 $y$ 组成的二元组合法。

这是为什么呢？题目中保证了序列中的数不同，那么由于 $x \bmod y <y$，并且 $y$ 为序列中最小数，那么 $x\bmod y$ 一定是不在序列中的。

我们可以轻松的看出这样的二元组有 $n-1$ 个，那么题目中说要求输出 $\left\lfloor\frac{n}{2}\right\rfloor$ 个这样的二元组，那么是足够的。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[200005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n/2;i++){
			cout<<a[i+1]<<' '<<a[1]<<endl;
		}
	}
}
```

---

## 作者：szkzyc (赞：0)

思路：$O(N^2)$ 暴力肯定会超时，但只需要输出 $[\frac{n}{2}]$ 的二元组就行了。考虑将数组排序后找到最小值，然后比它大的数对他取模的结果只可能小于它，而它已经是最小值了，所以都成立。

即对于递增数列 $a_1≤a_2≤a_3,...,a_{n-1}≤a_n$

可以构造出至少 $n-1$ 组二元组 $(a_x,a_1),x∈[2,n]$

证明：

$\because a_x≥a_1$

$\therefore a_x \bmod a_1 < a_x$

又 $\because a_1≤a_y , y∈[2,n]$

$\therefore a_x \bmod a_1$ 没有出现过

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define debug puts("qwq")
using namespace std;
int a[1000000];
int main(){
	int T;
	cin >> T;
	while(T--){//t组数据 
		int n;
		cin >> n; 
		bool flag = true;
		for(int i = 1; i <= n; i++) cin >> a[i];//输入 
		sort(a + 1, a + 1 + n);//排序 
		for(int i = 2; i <= n / 2 + 1; i++){//构造[n/2]组二元组 
			cout << a[i] << ' ' << a[0] << endl;//第i个数与第1个数 
		}
	} 
	return 0;
}

```


---

## 作者：徐晨轩✅ (赞：0)

**本题唯一的重点是：$x \bmod y < y$（余数一定比除数小）。**

也就是说，我们找到数列里的最小值，把它当做 $y$，再从数列里任意选一个 $x$ 即可。这样就必定有 $n-1$ 对 $(x,y)$。而题目只需要 $\left\lfloor \frac n 2 \right\rfloor$ 对，且 $n-1 \ge \left\lfloor \frac n 2 \right\rfloor$，所以一定是足够的。

PS: `min_element(a+1,a+n+1)` 表示求 $a$ 中的最小值，返回其指针，平均时间复杂度 $O(n)$。 

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int t,n,mn,a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i=1;i<=n;i++)
			cin >> a[i];
		mn=*min_element(a+1,a+n+1);
		for(int i=1,k=1;k<=n/2;i++)
			if(a[i]!=mn)
				cout << a[i] << ' ' << mn << endl,k++;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1613B Absent Remainder  题解

## 题目描述

给定一个 $n$ 个数的数组 $a$，让你在 $a$ 中找到 $\left\lfloor \dfrac{n}{2} \right\rfloor$ 个有序数对 $(x,y)$ 满足：

1. $x$，$y$ 均为 $a$ 中的元素
2. $x\ne y$
3. $x\bmod y$ 不是在 $a$ 中的元素

## 思路分析

### 结论

用 $m$ 表示 $a$ 中的最小值，当 $x\in a$ 且 $x\ne m$ 时，$(x,m)$ 为一个合法的有序数对

### 证明

显然，数对 $(x,m)$ 满足条件 1 和 2

又因  $\forall\,x\in a\,,m\leq x$ 且 $0\leq x\bmod m <m$

所以 $\forall\,x\in a\,,x\bmod m<x$

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN];
inline void solve(int n) {
	sort(a+1,a+n+1);
	unique(a+1,a+n+1);
	//去重,防止输出相同的数对 
	for(register int i=1;i<=(n>>1);++i) { //输出n/2个数对 
		printf("%d %d\n",a[i+1],a[1]); //每一次输出 (x,m),正确性已经证明
	}
	return ;
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n;
		scanf("%d",&n);
		for(register int i=1;i<=n;++i) scanf("%d",a+i);
		solve(n);
	}
	return 0;
}
```

---

## 作者：Skylmt (赞：0)

### 思路

显然的，$x \bmod y < y$

于是我们可以先把序列排一下序，然后找出其中最小的值。

用其他数依次对最小值取模。

由于上面的柿子，比最小值小的数肯定没出现过。

可以产生 $n-1$ 个柿子，由于 $ n - 1 > \left\lfloor\dfrac{2}{n}\right\rfloor$ ，因此显然满足条件。

### code：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define mod 1000000007
typedef unsigned long long ull;
typedef long long ll;
using namespace std;

void solve()
{
	int n; cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	int t = 0;
	for(int i=n;i>1;i--)
	{
	    cout<<a[i]<<" "<<a[1]<<'\n';
	    t++; if(t==n/2) return;
	}
}

int main()
{
	int t;
	t=read();
	while(t--)
	{
		solve();
	}
	return 0;
}
```


---

## 作者：Tritons (赞：0)

显然，$x\bmod y < y$

因此，选择 $y$ 作为序列中的最小数字，选择 $x$ 作为其他任何数字，就可以得到至少 $n-1$ 对。对于任何正的 $n$ ，显然有 $n-1≥ \left \lfloor \frac{n}{2} \right \rfloor$ 。

复杂度 $O(Tn)$ 。

```cpp
#include <cstdio>
#include <algorithm>
int a[2000005], minn;
int main()
{
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        minn = 2147483647;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]), minn = std::min(minn, a[i]);
        for (int i = 1, k = 1; k <= n / 2; i++) 
            if (a[i] != minn) 
                printf("%d %d\n", a[i], minn), k++;
    }
    return 0;
}
```

---

## 作者：Gloaming (赞：0)

## 题目描述

给你一个长度为 $n$ 的整数数列 $a$，请你构造 $\left[\frac{n}{2}\right]$ 对整数满足以下条件。

 1. $x\neq y$
 2. $x,y$ 在 $a$ 数列中
 3. $x\mod{y}$ 不在 $a$ 中

## 分析

我们可以观察到一个性质：$x\mod{y}< y$，那么这一个序列中最小的数可以作为 $y$，其他数作为 $x$，那么我们就可以很容易的构造出 $\left[\frac{n}{2}\right]$ 对 $x,y$ 了。

代码实现

```c++
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,a[N];
inline void WORK(void) {
    int cnt=0;
    for(int i=2;i<=n;i++){
        cnt++;
        cout<<a[i]<<' '<<a[1]<<endl;
        if(cnt==n/2) return ;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        WORK();
    }
    return 0;
}
```

---

