# [ABC255D] ±1 Operation 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_d

長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。この $ A $ に以下を施すことを「操作」と呼びます。

- まず、 $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ を選択する。
- 次に、以下の $ 2 $ つのうちどちらかを選択し、実行する。
  - $ A_i $ に $ 1 $ を加算する。
  - $ A_i $ から $ 1 $ を減算する。

$ Q $ 個の質問に答えてください。  
$ i $ 個目の質問は以下です。

- 「操作」を $ 0 $ 回以上何度でも使って $ A $ の要素を全て $ X_i $ にする時、必要な「操作」の最小回数を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N,Q\ \le\ 2\ \times\ 10^5 $
- $ 0\ \le\ A_i\ \le\ 10^9 $
- $ 0\ \le\ X_i\ \le\ 10^9 $

### Sample Explanation 1

$ A=(6,11,2,5,5) $ であり、この入力には $ 3 $ つの質問が含まれます。 $ 1 $ つ目の質問について、 $ A $ に以下のように $ 10 $ 回の「操作」を施すことで、 $ A $ の要素を全て $ 5 $ にすることができます。 - $ A_1 $ から $ 1 $ 減算する。 - $ A_2 $ から $ 1 $ 減算することを $ 6 $ 度繰り返す。 - $ A_3 $ に $ 1 $ 加算することを $ 3 $ 度繰り返す。 $ 9 $ 回以下の「操作」で $ A $ の要素を全て $ 5 $ にすることはできません。 $ 2 $ つ目の質問について、 $ A $ に $ 71 $ 回の「操作」を施すことで、 $ A $ の要素を全て $ 20 $ にすることができます。 $ 3 $ つ目の質問について、 $ A $ に $ 29 $ 回の「操作」を施すことで、 $ A $ の要素を全て $ 0 $ にすることができます。

### Sample Explanation 2

出力が $ 32 $bit 整数に収まらない場合もあります。

## 样例 #1

### 输入

```
5 3
6 11 2 5 5
5
20
0```

### 输出

```
10
71
29```

## 样例 #2

### 输入

```
10 5
1000000000 314159265 271828182 141421356 161803398 0 777777777 255255255 536870912 998244353
555555555
321654987
1000000000
789456123
0```

### 输出

```
3316905982
2811735560
5542639502
4275864946
4457360498```

# 题解

## 作者：WaterSun (赞：6)

# 思路

因为 $1 \leq n,q \leq 2 \times 10^5$，所以对于每一次查询的时间复杂度一定要达到 $\Theta(\log n)$，甚至于 $\Theta(1)$。

一个最简单的想法，我们先统计出整个序列 $a$ 的和 $sum$，然后答案是 $|sum - x \times n|$。

很显然，这个想法是错误的，因为对于 $a$ 中只有两个元素 $x - 1,x + 1$ 的时候，这样算出来答案为 $0$，但是，这种情况答案应该是 $2$。

那么，换一个思路。

不难发现，对于一个数 $a_i$，它的操作次数满足如下 $3$ 个结论：

1. 当 $a_i < x$ 时，将操作 $x - a_i$ 次。

2. 当 $a_i = x$ 时，将操作 $0$ 次。

3. 当 $a_i > x$ 时，将操作 $a_i - x$ 次。

那么，我们不妨令序列 $b$ 中存储了 $a$ 中小于 $x$ 的元素，$c$ 中存储了 $a$ 中大于 $x$ 的元素。

很显然，答案就是（$B,C$ 分别为 $b,c$ 中的元素个数）：

$$\sum_{i = 1}^{B}{b_i} + \sum_{i = 1}^{C}{c_i}$$

因此，现在的问题就转化为了求 $b$ 和 $c$。

我们发现，对于此题，打乱 $a$ 的顺序，对答案的正确性无关，于是，我们对 $a$ 从小到大排一次序。

那么，我们就可以用二分查找出分界点 $x$ 的位置 $id$。所以，在 $id$ 之前的元素应在 $b$ 中；反之，应在 $c$ 中。

其实我们的答只于 $b,c$ 的和有关，与 $b,c$ 中真正有哪些元素无关。所以我们并不用求出 $b,c$。

因此，我们可以对排序过后的序列 $a$ 做一个前缀和，然后二分即可。

特别的，对于序列中没有 $x$ 的情况，答案应为 $|s_n - x \times n|$。

时间复杂度 $\Theta(q \log n)$

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,q;
int arr[N],s[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	q = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	sort(arr + 1,arr + 1 + n);
	for (re int i = 1;i <= n;i++) s[i] = s[i - 1] + arr[i];
	while (q--){
		int x;
		x = read();
		int id1 = lower_bound(arr + 1,arr + 1 + n,x) - arr - 1;//因为有可能有多个值为 x 的元素，所以求出值为 x 的区间的边界 
		int id2 = upper_bound(arr + 1,arr + 1 + n,x) - arr;
		if (!id1 || id1 == n){//没查到
			printf("%lld\n",abs(s[n] - n * x));
			continue;
		}
		int pre = abs(id1 * x - s[id1]);//求答案 
		int nxt = abs((n - id2 + 1) * x - (s[n] - s[id2 - 1]));
		printf("%lld\n",pre + nxt);
	}
	return 0;
}
```

---

## 作者：_shine_ (赞：2)

### 1.题目大意
有一个长度为 $n$ 的数组 $a$，对于序列 $a$ 中的 $a_i$，每次可以加或减去 $1$，有 $q$ 次询问，求需要进行多次操作，使得序列 $a$ 中的每一个数均为 $x$。
### 2.思路分析
对于每一次把序列 $a$ 变成 $x$ 的操作，显然使用绝对值进行模拟是不对的，但是，不难发现，对于每一次变为 $x$ 的操作，其实可以分为 三种情况：

1.$a_i=x$，此时不用管，不用进行操作。

2.$a_i<x$，只需要把 $a_i$ 多次加 $1$，直至 $a_i=x$。

3.$a_i>x$，只需要把 $a_i$ 多次减 $1$，直至 $a_i=x$。

对与这三种情况，显然会考虑前缀和 $sum$，可得 $ans=\left|sum_n-\left(n\times x \right)\right|$，显然，在本题中，样例不会通过，因为在上文的三种情况中，第二和第三种情况会互相冲突，因为一个是加，而另一个是减。

举个例子，设序列 $a$ 为 ```1 2 4 5 7```，$x$ 为 $5$，则用上文公式可得 $ans=6$，但答案为 $10$，显然考虑每次对序列 $a$ 进行枚举，显然是用二分查找，枚举出中间的分界点 $l$，使得 $a_l<x,a_{l+1}\ge x$，此时即可通过。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,q;
int a[maxn];
int sum[maxn];
signed main(){
	cin >> n >> q;
	for(int i=1;i<=n;++i){
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1]+a[i];
	}
	while(q--){
		int x;
		cin >> x;
		int p=lower_bound(a+1,a+n+1,x)-a;
//		cout << p << " " << (p-1)*x-sum[p-1] << "  " << (sum[n]-sum[p-1])-(n-p+1)*x << endl;
		cout << (p-1)*x-sum[p-1]+(sum[n]-sum[p-1])-(n-p+1)*x << endl;
	}
	return 0;
}
/*
5 3
6 11 2 5 5
5
20
0

10 5
1000000000 314159265 271828182 141421356 161803398 0 777777777 255255255 536870912 998244353
555555555
321654987
1000000000
789456123
0

*/
```


---

## 作者：封禁用户 (赞：1)

## 分析

因为对于每次的询问，都是独立的。所以每次询问的答案只与 $a_i$ 的大小有关。我们考虑将 $a$ 从小到大排序，对于每次的 $x$，找到一个分界点 $k$，使 $a_1$ 到 $a_k$ 都小于等于 $x$，$a_{k+1}$ 到 $a_n$ 都大于 $x$。这样的话，我们就可以运用前缀和，求出两边的操作次数，再相加就行了。

注：找分界点，直接套用二分函数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q,x;
const int N=1e6+10;
int a[N],s[N];
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];//前缀和 
	for(int i=1;i<=q;i++)
	{
		cin>>x;
		int k=upper_bound(a+1,a+n+1,x)-a;
		k--;//分界点 
		cout<<(x*k-s[k])+((s[n]-s[k])-x*(n-k))<<endl;//前面都<=x,后面都>x 
	}
	return 0;
}
```

---

## 作者：syzxzqy (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc255_d)  
#### 题目大意：
有一个序列 $a$，求序列每个元素与 $x$ 的差之和。  
#### 题目分析：
我们可以把序列分成两部分：第一部分为小于等于 $x$ 的数，第二部分为大于 $x$ 的数。  
分的过程可以用二分，用 $bao$ 记录最后一个小于等于 $x$ 的数。  
二分前，我们要对 $a$ 数组排序，再用 $f$ 数组求 $a$ 的前缀。  
第一部分的差就是：
- $s1=x\times bao-f_{bao}$。  
第二部分的差就是：  
- $s2=f_n-f_{bao}-x\times(n-bao)$。  
答案即为 $s1+s2$。  
#### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000001,M=1001;
int n,T,i,x,l,r,mid,bao,s1,s2,a[N],f[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>T;
	for(i=1;i<=n;i++)	
		cin>>a[i];
	sort(a+1,a+1+n);//排序
	for(i=1;i<=n;i++)
		f[i]=f[i-1]+a[i];//前缀
	while(T--){
		cin>>x;
		l=1;r=n;bao=0;//二分求出最后一个小于等于x的位置
		while(l<=r){
			mid=(l+r)>>1;
			if(a[mid]<=x) bao=mid,l=mid+1;
			else r=mid-1;
		}
		s1=x*bao-f[bao];//第一部分与x的差之和
		s2=f[n]-f[bao]-x*(n-bao);//第二部分与x的差之和
		cout<<s1+s2<<"\n";//输出答案
	}
}
```


---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc255_d) & [AT链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc255_d)

## 思路分析：

这道题我们可以使用中位数的思想，但不是中位数。

先将 $a$ 数组升序排序，然后维护一个前缀和数组 $s$，注意顺序。

如果这里倒序排序，前缀和数组将会变得很大。

分类讨论：

首先如果 $x<a_1$ 或 $x>a_n$，那么直接输出 $|s_n-n\times x|$ 即可。

否则就用二分查找到 $a$ 数组中第一个小于或等于 $x$ 的数的位置 $k$，当然也可以使用库函数。

这样就将 $a$ 数组分为了两部分，前半部分需要加的次数是 $k\times x-s_k$，后半部分需要减的次数是 $s_n-s_k-x\times(n-l)$。最后将两部分相加即可。

## 代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long//前缀和数组以及答案要long long 
using namespace std;
int n,a[200005],x,q;
int s[200005]; 
signed main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);//这里不计算前缀和 
	}
	stable_sort(a+1,a+n+1);//个人感觉stable_sort快一些 
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];//前缀和 
	}
	while(q--){//q次询问 
		scanf("%d",&x);
		if(x>a[n]||x<a[1]){//特判 
			cout<<abs(s[n]-n*x)<<"\n";
			continue;
		}
		int l=1,r=n,mid;
		//二分 
		while(l<r){
			mid=l+((r-l+1)>>1);
			if(a[mid]<=x){
				l=mid;
			}else{
				r=mid-1;
			}
		}
		cout<<x*l-s[l]+s[n]-s[l]-x*(n-l)<<"\n";//计算答案 
	}
	return 0;
}
```


---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc255_d)

## 题目叙述
这道题目让我们把给定的数组中的所有数都变成给定的一个数 $X$。

在这里有两种操作：

> 将 $a_i+1$ 变为 $a_i$
> 
> 将 $a_i-1$ 变为 $a_i$

我们简单的变换一下：

> 将 $a_i$ 变为 $a_i-1$
> 
> 将 $a_i$ 变为 $a_i+1$

这样就比较通俗易懂了。

## 算法分析

我们看到这道题目的题面，心中肯定想的是暴力枚举一遍，然后每次计算一次当前数与要变化的值的差，最后累加就可以了。但是我们一看数据范围 $1\le N,Q\le 2\times 10^5$ 就发现这个题如果这么写一定会超时。于是，我们考虑优化。

怎么优化呢？我们可以考虑前缀和和差分的思想，显然，这道题目更适合用前缀和的思想。但是，这样还是不够，我们使用前缀和只能求出一段区间的和，我们又不知道当前的数与这段区间的所有的数的大小关系。于是，我们便可以使用排序，来让整个数组有序。

但是问题又来了，我们不知道到了哪一个数，$X$ 才比要处理的数大。

我们根据这个问题就想到了二分求这个数。

但是手写二分又有一点长，怎么办呢？

便可以使用二分的专用函数 ``lower_bound`` 和 	``upper_bound``。

``lower_bound`` 是找到**第一个大于等于** $X$ 的数的地址。

``upper_bound`` 是找到第一个大于 $X$ 的数的地址。

有些人就要问了，如果没有怎么办呢？

一般来说，如果没有找到，返回值为末尾位置。

那么，我们使用哪一个二分函数呢？

一开始，我使用 ``upper_bound`` 了。

我们的 ``upper_bound`` 怎么使用呢？

是这样使用的 ``upper_bound(数组名称+开始范围,数组名称+结束范围,查找数据)``

但是这样只能返回这个数的地址，所以我们要再减去数组名称来获取这个数的位置。

这题就结束了。不过在这里我是查询了$X-1$ 的位置。（好像和 ``lower_bound`` 差不多啊）

---
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define ll long long
ll ans,tot,now_tot,d[N];
ll n,num[N],q,x,k;
int main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld",&num[i]);
	sort(num+1,num+n+1);
	for(int i=1;i<=n+1;i++)d[i]=d[i-1]+num[i];
	for(int i=1;i<=q;i++){
		scanf("%lld",&x);//输入
		k=upper_bound(num+1,num+n+1,x)-num-1;//使用upper_bound进行处理
		ans=x*k-d[k])+((d[n]-d[k])-x*(n-k);
		printf("%lld\n",ans);//这里最好开long long
	}
	return 0;
}
```


---

## 作者：ylch (赞：0)

# [ABC255D] ±1 Operation 2 题解

[-题目传送门-](https://www.luogu.com.cn/problem/AT_abc255_d)

### 思路

这道题要求我们求每一个元素与 $x$ 的差。

经过验证，最优方法是把 $a$ 序列排序后分成两段，前段是小于等于 $x$ 的元素，后段是大于 $x$ 的元素，分别求两段元素与 $x$ 的差值和，中间位置为 $p$。

我们先求出数列 $a$ 的前缀和数组 $s$，$p$ 为中点，用 $x \times p - s_p$ 求出前一段的差；用 $(s_n - s_p) - x \times (n-p)$ 求出后一段的差。

---------------------

公式解释：

$x \times p - s_p$：假设元素全是 $x$，中间点为 $p$，其和应该是 $x \times p$，用全部是 $x$ 的和减去前 $p$ 个元素的和，就是前段的差值。

$(s_n - s_p) - x \times (n-p)$：后段区间和是 $s_n-s_p$，假设后段元素全是 $x$，其长度就是 $n-p$，其和应为 $x \times (n-p)$，两方相减，得出答案。 

### 代码

> 十年 OI 一场空，不开 long long 见祖宗！

```cpp
#include <bits/stdc++.h>
#define int long long //开 long long
using namespace std;

int a[200005], s[200005];
int n,q,x;

signed main()
{
	cin >> n >> q;
	for (int i=1; i<=n; i++)
	{
		cin >> a[i];
	}
	sort(a+1, a+n+1);	//要排序
	for (int i=1; i<=n; i++)	//前缀和求的是排序后的，我在这挂了一次
	{
		s[i] = s[i-1] + a[i];
	}
	while (q--)
	{
		cin >> x;
		int p = upper_bound(a+1, a+n+1, x) - a - 1;	//分界点
		int tmp = s[n] - s[p];	//后段的区间和
		cout << labs(( x*p - s[p] ) + ( tmp - x*(n-p) )) << endl;
	}
	return 0;
}
```

End
---------------

管理员大大辛苦啦~

谢谢大家！祝大家 AC！

---

## 作者：max666dong123 (赞：0)

## 题目描述

给定序列 $a_n$，存在两种操作，$a_i \leftarrow a_{i}-1$ 和 $a_i \leftarrow a_{i}+1$，$q$ 次独立询问给定 $x$，求将原序列所有数均变为 $x$ 需要多少次操作。

## 思路

这道题其实就是求：
$$|a_1-x|+|a_2-x|+|a_3-x|+\dots+|a_n-x|$$

零点分段明显不现实，所以我们考虑将 $a_1\sim a_n$ 分成两部分，
小于等于 $x$ 的和大于等于 $x$ 的。

为了更好的统计这两部分，我们``sort``排序一下，排序后取前缀和。

![](https://cdn.luogu.com.cn/upload/image_hosting/q3w9c029.png)

很明显 $where$ 前面的书是小于等于 $x$ 的，所以要用 $x$ 来减，其他的照着上面做就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define debug() cout<<"-------------------"<<endl 
using namespace std;
const int N=2e5+10;
int a[N],s[N];
int n,q;
signed main(){
	IOS;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i]; 
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		int where=upper_bound(a+1,a+1+n,x)-a;
		int ans=(where-1)*x-s[where-1];
//		cout<<s[where-1]<<endl;
		ans=ans+s[n]-s[where-1]-(n-where+1)*x;
//		debug();
//		cout<<((n-where+1)*x)<<endl;
		cout<<ans<<endl;
//		debug();
		
	}
	return 0;
}

```

---

## 作者：szhqwq (赞：0)

## 分析

考虑前缀和 + 二分。

首先将 $a_i$ 从小到大排序，再使用前缀和初始化，令 $s_i$ 为 $a_i$ 的前缀和。

然后 $q$ 次询问，对于每个 $x$ 使用 STL 中的 `lower_bound` 寻找到 $x$ 在序列 $a_i$ 中的大小位置 $l$（第几大），然后值即为 $(l - 1) \cdot x - s_{l - 1}$（$l$ 前的差值）加上 $s_n - s_{l - 1} - x \cdot (n - l + 1)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 10;

int n,q;
int a[N];
int s[N];

signed main() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	sort(a + 1,a + n + 1);
	for (int i = 0; i <= n + 1; ++ i ) s[i] = s[i - 1] + a[i];
	while (q -- ) {
		int x;
		cin >> x;
		int l = lower_bound(a + 1,a + n + 1,x) - a;
		int res = x * (l - 1) - s[l - 1];
		res += s[n] - s[l - 1] - x * (n - l + 1);
		cout << res << endl;
	}
	return 0;
}
```

---

## 作者：endswitch (赞：0)

这道题看穿了就是求序列 $a$ 中每个元素与 $x$ 的差的和。

看数据范围：

$ 1\ \le\ N,Q\ \le\ 2\ \times\ 10^5 $

很显然不可用线性的办法去做，怎么办呢？考虑二分。

我们先将序列 $a$ 升序排序，再找出序列中第一个大于等于 $x$ 的数。这样我们就将序列分为了两个部分：都小于或等于 $x$ 的部分和都大于 $x$ 的部分。

此时我们就可以用前缀和去维护答案了。

令 $p$ 为第一个大于等于 $x$ 的数，序列 $a$ 的前缀和序列为 $sum$，则小于或等于 $x$ 的部分的操作次数为 $p \times x - sum_p$，大于 $x$ 的部分的操作次数为 $s - sum_p \times (n - p)$。

最后相加即可。

* 记得开长整型变量。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,q,a[N],x,sum[N],p;
signed main() {
	scanf("%lld%lld".&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i];
	while(q--) {
		scanf("%lld",&x);
		p=lower_bound(a+1,a+1+n,x)-a-1;
		printf("%lld\n",abs(x*p-sum[p])+(sum[n]-sum[p]-x*(n-p)));
	}
	return 0;
}
```

[$AC$ 记录](https://www.luogu.com.cn/record/109478178)。

---

## 作者：PikachuQAQ (赞：0)

## Description

给定序列 $a_n$，存在两种操作，$a_i = a_i - 1$ 和 $a_i = a_i + 1$，$q$ 次询问给定 $x$，求将原序列所有的元素逐个变为 $x$ 需要多少次操作。

## Solution

前缀和好题。

首先考虑暴力维护序列 $a$，时间复杂度 $O(n)$，显然无法通过本题。

考虑 $O(\log n)$ 做法。

这题有一特性：排序后不影响答案，所以考虑排序并二分。

但是这一题要怎么二分？

考虑用二分找到序列 $a$ 中的最后一个和 $x$ 相同的数，这样就可以分成两个序列：都是小于 $x$ 的数，都是大于 $x$ 的数。

此时，前缀和就派上用场了。

设 $k$ 为的最后一个和 $x$ 相同的数，前缀和数组为 $f$，数组中所有数的和为 $s$，序列一的操作次数为 $k \times x - f_k$，序列二的操作次数为 $s - f_k \times (n - k)$。

记得开长整型！

## Code

```cpp
// 2023/4/27 Accept__

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int kMaxN = 2e5 + 7;

ll n, q, a[kMaxN], x, f[kMaxN], p, l, r, sum;

inline ll myabs(ll a) {
    return (a < 0) ? (-a) : (a);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] + a[i];
    }
    while (q--) {
        cin >> x;
        p = lower_bound(a + 1, a + n + 1, x) - a - 1;
        cout << myabs((x * p - f[p]) + (f[n] - f[p] - x * (n - p))) << '\n';
    }

    return 0;
}

```


---

## 作者：LBYYSM_123 (赞：0)

### 思路
首先将 $a$ 序列排序，通过二分得出最后一个满足条件的点（$a_p\leq x$）。（将此点设为 $p$）          

以此点为分界线，分成两个序列：
1. 一序列都小于 $x$ ,设其结果为 $S1$,该序列和为 $B1$,则：   
	$S1= x\times p-B1$。
1. 二序列都大于 $x$ ,设其结果为 $S2$,该序列和为 $B2$,则  
	$S2=B2-x\times(n-p)$。
    
用前缀和实现即可。


### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],b[200005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,t,x;
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>a[i];	
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		b[i]=a[i]+b[i-1];
	while(t--){
		cin>>x;
		int pos=lower_bound(a+1,a+n+1,x)-a-1;
    	cout<<(x*pos-b[pos])+(b[n]-b[pos]-x*(n-pos))<<endl;
	}
	return 0;
} 
```

---

## 作者：ttq012 (赞：0)

首先将 $a$ 数组从小到大排序，并记录一个前缀和（当然也可以线段树）。

然后对于每一组询问 $x$，在 $a$ 数组中找出最后一个小于等于 $x$ 的数的位置 $p$。

那么对于 $\le x$ 和 $>x$ 两种情况，分类讨论，计算出这两种情况的答案之后根据加法原理将两个答案加起来即可。

时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;int a[N],s[N];
signed main(){
  int n,m;cin>>n>>m;for(int i=1;i<=n;i++)cin>>a[i];
  sort(a+1,a+n+1);
  for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
  while(m--){
    int x;cin>>x;int l=1,r=n,best=0;
    while(l<=r){int mid=l+r>>1;if(a[mid]<=x)best=mid,l=mid+1;else r=mid-1;}
    int p1=x*best-s[best],p2=(s[n]-s[best])-x*(n-best);cout<<p1+p2<<'\n';
  }
}
```



---

## 作者：Leaves_xw (赞：0)

**大意：**

给了 $n$ 个正整数 $a_1,a_2 … a_n$，每个数都可以 $+1$ 或 $-1$ ，给定 $q$ 次询问，每一次有一个数 $x$，求把所有数变成 $x$ 需要几次操作。

**思路：**

思路很好想，就是判断每一个数比 $x$ 大还是小，大的话操作次数增加 $a_i-x$ 次，小的话增加 $x-a_i$ 次，如果相同则跳过,当然用绝对值更好。

代码自己写

---

## 作者：FReQuenter (赞：0)

## 思路

首先将 $a$ 排序，那么对于每一个询问，我们只需要二分出一个点，满足以下要求：

- $a_1,a_2,...,a_{pos}\leq X_i$。

- $a_{pos+1},a_{pos+2},...,a_n\geq X_i$。

这样，每个询问就转化成了求这样一个点，前面所有数加到 $X_i$，后面所有数减到 $X_i$。而计算总共加减多少可以直接前缀和实现。

## 代码

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int a[200005],sum[200005];
signed main(){
  int n,q;
  cin>>n>>q;
  for(int i=1;i<=n;i++) cin>>a[i];
  sort(a+1,a+n+1);
  for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
  while(q--){
    int x;
    cin>>x;
    int pos=lower_bound(a+1,a+n+1,x)-a-1;//二分那个点
    cout<<(x*pos-sum[pos])/*前部*/+(sum[n]-sum[pos]-x*(n-pos))/*后部*/<<'\n';
  }
}
```

---

