# [ARC144B] Gift Tax

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc144/tasks/arc144_b

$ a\leq\ b $ を満たす正整数 $ a,\ b $ および，正整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます．

あなたはこの数列に対して，以下の操作を何度でも行うことができます（$ 0 $ 回でもよいです）：

- 相異なる添字 $ i,\ j $ ($ 1\leq\ i,\ j\ \leq\ N $) を選ぶ．$ A_i $ に $ a $ を加え，$ A_j $ から $ b $ を引く．

操作後の $ \min(A_1,\ A_2,\ \ldots,\ A_N) $ としてありうる最大値を求めてください．

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ a\leq\ b\leq\ 10^9 $
- $ 1\leq\ A_i\leq\ 10^{9} $

### Sample Explanation 1

例えば次のように操作を行うことで， $ \min(A_1,\ A_2,\ A_3)\ =\ 5 $ を達成できます． - $ i\ =\ 1,\ j\ =\ 3 $ として操作を行う．$ A $ は $ (3,\ 5,\ 7) $ に変化する． - $ i\ =\ 1,\ j\ =\ 3 $ として操作を行う．$ A $ は $ (5,\ 5,\ 5) $ に変化する．

### Sample Explanation 2

例えば次のように操作を行うことで， $ \min(A_1,\ A_2,\ A_3)\ =\ 3 $ を達成できます． - $ i\ =\ 1,\ j\ =\ 3 $ として操作を行う．$ A $ は $ (13,\ 1,\ -1) $ に変化する． - $ i\ =\ 2,\ j\ =\ 1 $ として操作を行う．$ A $ は $ (10,\ 3,\ -1) $ に変化する． - $ i\ =\ 3,\ j\ =\ 1 $ として操作を行う．$ A $ は $ (7,\ 3,\ 1) $ に変化する． - $ i\ =\ 3,\ j\ =\ 1 $ として操作を行う．$ A $ は $ (4,\ 3,\ 3) $ に変化する．

### Sample Explanation 3

一度も操作を行わないことにより， $ \min(A_1,\ A_2,\ A_3)\ =\ 5 $ を達成できます．

## 样例 #1

### 输入

```
3 2 2
1 5 9```

### 输出

```
5```

## 样例 #2

### 输入

```
3 2 3
11 1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
3 1 100
8 5 6```

### 输出

```
5```

## 样例 #4

### 输入

```
6 123 321
10 100 1000 10000 100000 1000000```

### 输出

```
90688```

# 题解

## 作者：WsW_ (赞：2)

### 思路
假设经过最优操作后的数列为 $A'$。那么答案就是 $\min\{A'\}$。  

看到最小值最大，考虑二分答案。  
先证明答案具有单调性：假设我们二分出来一个答案 $X$，如果 $X\le \min\{A'\}$ 那么可行，否则不可行。定义检验函数 $f(X)=[X\le \min\{A'\}]$，显然 $f(X)$ 单调不升。  

接着考虑检验函数 $f(X)$ 该怎么写。  
我们最终的目的是要通过操作，使 $X\le \min\{A'\}$。不妨把操作拆成**加**和**减**两个操作，先使 $\forall i\le N,X\le \min\{A'\}$，再比较**加**操作进行的次数和**减**操作的次数。  
一个显然的结论是，对于任意一个 $A_i$，要么不进行操作，要么进行一定次数的加操作，要么进行一定次数的减操作。既进行加操作又进行减操作一定不优，请自行证明。  

所以对于任意一个 $A_i$，如果可以对它进行减操作，那么对它进行**次数尽可能多的**减操作；如果需要对它进行加操作，那么对它进行**次数尽可能少的**减操作。  
容易得出，最多可以进行 $\lfloor\frac{A_i-X}{b} \rfloor$ 次减操作，最少需要进行 $\lceil\frac{X-A_i}{a}\rceil$ 次加操作。对于每个 $A_i$ 分别统计即可，单次检验的时间复杂度为 $O(n)$。  

总时间复杂度为 $O(n\log A_i)$。  

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=3e5+5;
int n,a,b;
int A[maxn];

bool check(int x){
	ll k=0;
	for(int i=1;i<=n;i++){
		if(A[i]>=x)k+=(A[i]-x)/b;
		else k-=(x-A[i]+a-1)/a;
	}
	return k>=0;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>a>>b;
	int l=1,r=1,mid=1,ans=1;
	for(int i=1;i<=n;i++){
		cin>>A[i];
		r=max(r,A[i]);
	}
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Binary_Lee (赞：2)

## [题面传送门](https://www.luogu.com.cn/problem/AT_arc144_b)

### 题目大意

给出 $n,a,b$ 和一个长度为 $n$ 数列 $A_i\sim A_n$，你可以进行若干次操作（可以为 $0$ 次），每次操作可以选定一个 $A_i$，给它 $+a$，同时选另一个 $A_j$，给它 $-b$。求操作后最大的 $\min(A_1,A_2,\dots,A_n)$。

### 解决思路

求最大的最小值，考虑二分答案。

设二分出的最小值为 $x$。对于数列中的每一个 $A_i$，它不到 $x$ 的话需要加若干次 $a$，否则，它可以贡献出减若干次 $b$。

- 若 $A_i<x$，则这个数需要加 $\lceil \frac{x-A_i}{a}\rceil$ 次

- 否则，这个数最多可以被减 $\lfloor \frac{A_i-x}{b}\rfloor$ 次

若最后能减的次数 $\ge$ 需要加的次数，则说明当前的答案可行。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int n,a,b,A[300005],l=1e18,r;
bool check(int x){
	int c1=0,c2=0;
	for(int i=1;i<=n;i++){
		if(A[i]<x) c1+=(int)ceil((double)(x-A[i])/a);
		else c2+=(A[i]-x)/b;
	}
	return c1<=c2;
}
signed main(){
	IOS;TIE;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>A[i];
		l=min(l,A[i]),r=max(r,A[i]);
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<l-1<<endl;
	return 0;
}
```

---

## 作者：I_like_magic (赞：1)

这道题其实不难。

这是一道简单的二分答案题。

我们要求出 $A$ 数列最小值的最大值可能值，那么我们可以二分答案。

首先，假定答案为 $m$，那么，原 $A$ 数列中小于 $m$ 的值都要通过若干次 $A_i \gets A_i + a$ 操作使其大于等于 $m$。具体操作次数为**至少** $\lceil\frac{m - A_i}{a}\rceil$。

那么我们对数列中每个小于 $m$ 的数求出最少操作次数，并求和，得到的即为**总共的最少操作次数**，记为 $L$。

接下来，我们看向数列中大于 $m$ 的数字，这些数字可以进行若干次 $A_i \gets A_i - b$ 操作，但是我们要保证操作完 $A_i \ge m$，于是我们可以求出它们的**最多**操作次数，即为 $\lfloor\frac{A_i - m}{b}\rfloor$。

同样对它们求和，得到**总共的最多操作次数**，记为 $R$。

由于两种操作是合并在一起的，所以一种操作的次数就是总操作次数。

显然，最小操作次数应当是**小于等于**最大操作次数的，所以如果 $L > R$，那么这个答案 $m$ 就是不合法的。

然后就完成二分的 `check` 函数了。

接下来就是模板了。

注意要开 `long long`，运算过程中可能会爆 `int`。

复杂度为 $O(n\log m)$，$m$ 为数字的值域。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 注意要开 long long，运算过程中会爆 int
using namespace std;
const int N = 300005; // 数据范围
int n, a, b;
int A[N];
bool check(int mid) { // 判断 mid 是否合法
    int res = 0;
    for(int i = 1; i <= n; i ++) {
        if(A[i] < mid) {
            int d = mid - A[i];
            res += (d + a - 1) / a; // 至少操作次数
        } else {
            int d = A[i] - mid;
            res -= d / b;  // 至多操作次数
        }
    }
    // res 即为两者的差，如果差小于等于 0，则为至多操作次数大于至少操作次数，合法，返回 1，否则返回 0
    return res <= 0;
}
signed main() {
    cin >> n >> a >> b;
    for(int i = 1; i <= n; i ++) {
        cin >> A[i];
    }
    int l = 1, r = 1000000000; // 范围
    while(l + 1 < r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            l = mid; // mid 合法，说明答案可能可以更大，答案在 mid 到 r 的范围
        } else {
            r = mid - 1; // mid 不合法，说明这个 mid 偏大了，答案只能在 l 到 mid - 1 的范围
        }
    }
    if(check(r)) cout << r << "\n"; // 如果 r 合法，输出 r
    else cout << l << "\n"; // 否则答案就是 l
    return 0;
}
```

---

## 作者：Z3k7223 (赞：0)

基础二分答案习题。

## Solution

看到最大化最小值，首先考虑二分，显然答案具有单调性，关键在于如何判断一个最小值 $x$ 是否合法。

既然钦定了最小值，就要把原序列中 $<x$ 的数全部通过若干次加操作调整到大于等于 $x$。因为每次加 $A$，显然操作次数是 $\left\lceil\frac{x-a_i}{A}\right\rceil$。同理，对于 $>x$ 的数，我们可以计算出最大允许减的次数，显然是 $\left\lfloor\frac{a_i-x}{B}\right\rfloor$，二者比较一下即可判断合法与否。

## Code

~~~cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3e5 + 10;
int n;
ll A, B;
ll a[N];

int check(ll mid) {
	ll cl = 0, cr = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] < mid) {
			cl += ceil((double)(mid - a[i]) / A);
		}
		if (a[i] > mid) {
			cr += (a[i] - mid) / B;
		}
	}
	return cl <= cr;
}

int main() {
	cin >> n >> A >> B;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	ll l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << ans << endl;
	return 0;
}
~~~

---

## 作者：Bpds1110 (赞：0)

考虑二分最大的最小值，设为 $Min$。

对于每次二分，令 $s1$ 表示最少进行的增加操作的次数，使得对于每个 $A_i \ge Min$。$s2$ 表示最多进行的减少的次数，但也要满足 $A_i \ge Min$。

枚举 $i = 1 \sim n$，对于每个 $A_i$ 进行统计。若 $A_i > x$，则可以增加 $s2$，即 $s2 \gets s2 + \left \lfloor (A_i - Min) \div b \right \rfloor $。若 $A_i < x$，增加 $s1$，即 $s1 \gets s1 + \left \lceil (Min - A_i) \div a \right \rceil $。

我们发现，当减少的次数不少于增加的次数时，我们可以减少**减少的次数**，因为越大也满足条件。所以，当 $s2 \ge s1$ 时，结果可行。

最后输出二分的结果即可。

---

## 作者：wenjunyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc144_b)


---

## 思路

既然是求最小值的最大可能值，就可以考虑二分答案。

假设我们二分最小值 $mid$。

如果 $A_i < mid$ 那么它就要加 $\lceil \frac{mid-A_i}{a} \rceil $ 次 $a$。

如果 $A_i \ge mid$ 那么它就可以贡献 $\lceil \frac{a_i-mid}{b} \rceil $ 次 $a$。

只要贡献的次数 $\ge$ 要加的次数就可以了。


---


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long //开long long
int n,a,b,arr[300005],l,r=1e9,mid,ans;
bool check(int mid){
	int sum=0;//sum记录有多少可用的贡献（可以为负数）
	for(int i=1;i<=n;i++){
		int o=abs(arr[i]-mid);
		if(arr[i]<mid){//情况1（不可以贡献）
			if(o%a==0){
				sum-=o/a;
			}
			else{
				sum-=o/a+1;
			}
		}
		else{//情况2（可以贡献）
			sum+=o/b;
		}
	}
	if(sum<0){
		return 0;//贡献次数少了
	}
	else{
		return 1;
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;//可以更多
			ans=mid;
		}
		else{
			r=mid-1;//要更少一点
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：ny_Dacong (赞：0)

# 思路

看到题目中“最小值最大”的信息。像这样的“双最值问题”，考虑使用二分。

二分最终的答案，即最小值的最大可能。

单调性很明显：

设当最终的答案是 $X$，则我可以让它减去 $b$ 使这个 $X$ 变得更小。尽管与此同时还有一个元素会加上 $a$，但是都是正数，不影响 $X$ 变小。因此，比 $X$ 小的数都可以满足。

但是如果我们想要 $X$ 加上 $a$，那么与此同时会有一个元素减去 $b$。题目告诉我们，$a \le b$。因此这个减去 $b$ 的元素有可能成为新的最小值。所以大于 $X$ 的数不一定满足。

然后考虑怎么写 `check` 函数。

对于一个小于 $X$ 的数（不妨设其为 $p$），则 $p$ 至少需要加上 $\lceil \frac{X-p}{a} \rceil$ 个 $a$ 才可以满足大于等于 $X$。

对于一个打于 $X$ 的数（不妨设其为 $q$），则 $q$ 可以给小于的数贡献 $\lfloor \frac{q-X}{b} \rfloor$ 次加 $a$ 的机会。

因此，看看最后增加的需求次数是否小于可以减去的次数即可。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,l = 0,r = 1e9+20,mid,ans;
long long num[300005];
bool check(long long x){
	long long add = 0,sub = 0;
	for(long long i = 1; i <= n; i++){
		if(num[i] < x){
			add += (x-num[i]+a-1)/a;
		}
		if(num[i] > x){
			sub += (num[i]-x)/b;
		}
	}
	return sub >= add;
}
int main(){
//	freopen("present.in","r",stdin);
//	freopen("present.out","w",stdout);
	scanf("%lld%lld%lld",&n,&a,&b);
	for(long long i = 1; i <= n; i++){
		scanf("%lld",&num[i]);
	}
	while(l <= r){
		mid = l+((r-l)>>1);
		if(check(mid)){
			l = mid+1;
			ans = mid;
		}else{
			r = mid-1;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

