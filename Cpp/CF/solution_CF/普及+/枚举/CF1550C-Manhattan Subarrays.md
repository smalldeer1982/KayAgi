# Manhattan Subarrays

## 题目描述

Suppose you have two points $ p = (x_p, y_p) $ and $ q = (x_q, y_q) $ . Let's denote the Manhattan distance between them as $ d(p, q) = |x_p - x_q| + |y_p - y_q| $ .

Let's say that three points $ p $ , $ q $ , $ r $ form a bad triple if $ d(p, r) = d(p, q) + d(q, r) $ .

Let's say that an array $ b_1, b_2, \dots, b_m $ is good if it is impossible to choose three distinct indices $ i $ , $ j $ , $ k $ such that the points $ (b_i, i) $ , $ (b_j, j) $ and $ (b_k, k) $ form a bad triple.

You are given an array $ a_1, a_2, \dots, a_n $ . Calculate the number of good subarrays of $ a $ . A subarray of the array $ a $ is the array $ a_l, a_{l + 1}, \dots, a_r $ for some $ 1 \le l \le r \le n $ .

Note that, according to the definition, subarrays of length $ 1 $ and $ 2 $ are good.

## 说明/提示

In the first test case, it can be proven that any subarray of $ a $ is good. For example, subarray $ [a_2, a_3, a_4] $ is good since it contains only three elements and:

- $ d((a_2, 2), (a_4, 4)) = |4 - 3| + |2 - 4| = 3 $ $ < $ $ d((a_2, 2), (a_3, 3)) + d((a_3, 3), (a_4, 4)) = 3 + 1 + 2 + 1 = 7 $ ;
- $ d((a_2, 2), (a_3, 3)) $ $ < $ $ d((a_2, 2), (a_4, 4)) + d((a_4, 4), (a_3, 3)) $ ;
- $ d((a_3, 3), (a_4, 4)) $ $ < $ $ d((a_3, 3), (a_2, 2)) + d((a_2, 2), (a_4, 4)) $ ;

In the second test case, for example, subarray $ [a_1, a_2, a_3, a_4] $ is not good, since it contains a bad triple $ (a_1, 1) $ , $ (a_2, 2) $ , $ (a_4, 4) $ :

- $ d((a_1, 1), (a_4, 4)) = |6 - 9| + |1 - 4| = 6 $ ;
- $ d((a_1, 1), (a_2, 2)) = |6 - 9| + |1 - 2| = 4 $ ;
- $ d((a_2, 2), (a_4, 4)) = |9 - 9| + |2 - 4| = 2 $ ;

So, $ d((a_1, 1), (a_4, 4)) = d((a_1, 1), (a_2, 2)) + d((a_2, 2), (a_4, 4)) $ .

## 样例 #1

### 输入

```
3
4
2 4 1 3
5
6 9 1 9 6
2
13 37```

### 输出

```
10
12
3```

# 题解

## 作者：liangbowen (赞：17)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1550C)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1550c-TJ)

比赛时，这题写了一个 $O(n^3)$ 算法，然后就过了。

以为是数据水，实际上可以证明时间复杂度是 $O(n)$ 的。

## 思路

关键是一个结论：当 $i < j < k$ 时，若 $a_i, a_j, a_k$ 单调不降或单调不升，则三元组 $(a_i, i), (a_j, j), (a_k, k)$ 必定是坏的。

为什么呢？画个图就很容易理解了。

![](https://cdn.luogu.com.cn/upload/image_hosting/dmabo7mg.png?x-oss-process=image/resize,m_lfit,h_5000,w_5000)

同理，单调不增也是这样的。

所以，我们利用这一点 $O(n^2)$ 实现 `check` 函数。

```cpp
const int N = 2e5 + 5;
int a[N];
bool chk(int l, int r) // [l,r] 区间是否是坏的
{
	for (int i = l; i < r; i++)
		for (int j = l; j < i; j++) //j<i<r
		{
			if (a[j] <= a[i] && a[i] <= a[r]) return true;
			if (a[j] >= a[i] && a[i] >= a[r]) return true; //符号反过来 
		}
	return false;
}
```

接着打个尺取，即可在 $O(n \times n^2)$ 的时间内完成程序。

```cpp
void solve()
{
	int n;
	long long cnt = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int l = 1, r = 1; r <= n; r++) //顺序枚举右端点，左端点尺取
	{
		for (; l <= r && chk(l, r); l++);
		cnt += (r - l + 1);
	}
	printf("%lld\n", cnt);
}
```

那为什么可以跑过去呢？原因在于，$\texttt{check()}$ 函数不会执行这么多次，实际是趋于 $O(1)$ 的！

画一个图，可以发现，**不会**有长度大于等于 $5$ 的好子段。

所以这个方法去掉常数，就是 $O(n)$ 的。那么就可以欢快地打出代码了。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5;
int a[N];
bool chk(int l, int r)
{
	for (int i = l; i < r; i++)
		for (int j = l; j < i; j++)
		{
			if (a[j] <= a[i] && a[i] <= a[r]) return true;
			if (a[j] >= a[i] && a[i] >= a[r]) return true; //符号反过来 
		}
	return false;
}
void solve()
{
	int n;
	long long cnt = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int l = 1, r = 1; r <= n; r++)
	{
		for (; l <= r && chk(l, r); l++);
		cnt += (r - l + 1);
	}
	printf("%lld\n", cnt);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：sunzz3183 (赞：13)

# CF1550C Manhattan Subarrays

## 题面

对于平面上的两点 $p(x_p,y_p),q(x_q,y_q)$ ，我们定义它们之间的曼哈顿距离 $d(p,q)=|x_p-x_q|+|y_p-y_q|$  。进一步定义由三个点构成的一组点 $p,q,r$  是坏的仅当  $d(p,r)=d(p,q)+d(q,r)$ 。

我们定义序列 $b$ 是好的仅当无法选出一组互不相同的整数  $i,j,k$ 使得 $(b_i,i),(b_j,j),(b_k,k)$ 这组点是坏的。

给定长度为 $n$ 的序列 $a$，求 $a$ 有多少个子段是好的。 $T$ 组数据。

## 分析
在什么情况下三元组 $(p,q,r)$ 是坏的？假设 $y_p\leq y_q\leq y_r$ ，根据曼哈顿距离的定义（看图也行），当 点 $q$ 在区间点 $[p,r]$ 中时，这个三元组是坏的。

图：

![](https://cdn.luogu.com.cn/upload/image_hosting/puoyzi10.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ym1c43l2.png)

证明图：

![](https://cdn.luogu.com.cn/upload/image_hosting/meanotgr.png)

回到序列 $a$ ,选出 $i,j,k$ 来，此时为  $p(a_i,i),q(a_j,j),r(a_k,k)$ ,若 $i<j<k$ ，并且 $a_i\leq a_j\leq a_k$ 或者 $a_i\geq a_j\geq a_k$ 时，符合上图1情况（三元组是坏的）。

以上情况总结出：对序列 $a$ 的一个子段不能够找出一个三元组是单调递增或单调递减的，此子段是好的。

下面，我们对子段的长度分情况讨论：

1.子段为长度为 $1$ 时，$a$ 序列中好的字段有 $n$ 个。

2.子段为长度为 $2$ 时，$a$ 序列中好的字段有 $n-1$ 个。

3.子段为长度为 $3$ 或 $4$ 时，直接暴力枚举 $a$ 序列中的每一个三元组。

4.子段为长度为 $\geq 5$ 时，$a$ 序列中没有好的字段，因为，一个长度  $\geq 5$ 的区间的单调不减（增）子序列的长度 $\geq 3$ 。

## 上代码：

```cpp
#include<bits/stdc++.h>
using  namespace std;
int t,n,sum;
int a[200005];
bool cyl_ak_ioi(int a,int b,int c){//判断递增还是递减 
	if((a<=b&&b<=c)||(a>=b&&b>=c))
		return 0;
	else
		return 1;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sum=n*2-1;//一、二种情况 
		for(int i=1;i<=n-2;i++)//第三种情况 
			if(cyl_ak_ioi(a[i],a[i+1],a[i+2]))
				sum++;
		for(int i=1;i<=n-3;i++)//第四种情况 
			if(cyl_ak_ioi(a[i],a[i+1],a[i+2])&&cyl_ak_ioi(a[i],a[i+1],a[i+3])&&cyl_ak_ioi(a[i],a[i+2],a[i+3])&&cyl_ak_ioi(a[i+1],a[i+2],a[i+3]))
			//有些暴力，大家凑活着看吧 XD 
				sum++;
		cout<<sum<<"\n";
	}
	return 0;
}
```





---

## 作者：_RainCappuccino_ (赞：4)

> $\mathtt{TAG}$：暴力、BIT、组合数学
>
> 一开始震惊到我了，$O(n^2 \log_2 n)$ 过了，然后一算发现是 $O(n \log_2 n)$ 的。

# First. 解析坏的三元组

![](https://cdn.luogu.com.cn/upload/image_hosting/1qkk2bo7.png)

画个图发现，当且仅当 $x_1 \le x_2 \le x_3$ 且 $y_1 \ge y_2 \ge y_3$ 或 $y_1 \le y_2 \le y_3$ 的时候构成坏三元组。

回到题目上，由于每个数的横坐标是下标，所以坏三元组就转化为了一个长度为 $3$ 不下降或不上升的子序列。

# Second. 没有坏三元组的区间

首先不妨进行最暴力的想法，枚举每个区间，看它存不存在坏三元组。

而没有坏三元组的子数组的最长长度为 $4$。

> **证明**：
> 
> 如图，当两个同幅度的子序列相错的时候不能再添加任何一个点。
> ![](https://cdn.luogu.com.cn/upload/image_hosting/y9iq9gq2.png)
>
> **补充**：正确证明是代入 Erdős–Szekeres 定理  
> >**Erdős–Szekeres 定理**：对于 $|S| = n \times m + 1$ 的偏序集 $(S,\succ)$ ，一定存在一条长度为 $m + 1$ 的链或长度为 $n + 1$ 的反链。
>
> 然后代入 $m + 1 = 3$，得 $|S| = 5$。
> 所以要是其不存在长度为 $3$ 的链，那么 $|S| < 5$，所以最大为 $4$。

所以对于每个左端点，我们至多会枚举 $4$ 次。
时间复杂度只有 $O(n)$！

# Third. 判三元组

蒟蒻太蒟了，看到这种偏序形式就用树状数组了。

先离散化，建 $3$ 个树状数组，分别维护：权值 $\le x$ 的点的数量，较大数权值 $\le x$ 且 $a_i \ge a_j$ 的二元组数量，较小数权值 $\le x$ 且 $a_i \le a_j$ 的二元组数量。

然后就判断点 $i$ 能否接在之前的一个二元组上，能接上就是坏三元组。

其实暴力更快。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> pi;
#define endl '\n'
const int N = 2e5 + 10;
int n;
int a[N] , b[N];
struct bit {
#define lowbit(x) (x & -x)
    int c[N];
    void add(int x) {
        for (int i = x; i <= n; i += lowbit(i)) c[i]++;
    }
    void erase(int x) {
        for (int i = x; i <= n; i += lowbit(i)) c[i]--;
    }
    int sum(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += c[i];
        return res;
    }
};
bit t1 , t2 , t3;

signed main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i] , b[i] = a[i];
        sort(b + 1 , b + 1 + n);
        ll tmp = 0 , ans = 0;
        for (int i = 1; i <= n; i++) if (b[i] != b[i - 1]) b[++tmp] = b[i];
        for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1 , b + 1 + tmp , a[i]) - b;//离散化
        for (int i = 1; i <= n; i++) {
            bool flag = 1;
            for (int j = i; j <= n; j++) {
                if (t2.sum(a[j]) || t3.sum(n) - t3.sum(a[j] - 1)) {
                    flag = 0; // 不能暴力清空，会 TLE
                    for (int k = i; k < j; k++) {
                        t1.erase(a[k]);
                        if (t2.sum(a[k]) - t2.sum(a[k] - 1)) t2.erase(a[k]);
                        if (t3.sum(a[k]) - t3.sum(a[k] - 1)) t3.erase(a[k]);
                    }
                    break;
                }
                ans++;
                if (t1.sum(a[j])) t2.add(a[j]);
                if (t1.sum(n) - t1.sum(a[j] - 1)) t3.add(a[j]);
                t1.add(a[j]);
            }
            if (!flag) continue;
            for (int k = i; k <= n; k++) {
                t1.erase(a[k]);
                if (t2.sum(a[k]) - t2.sum(a[k] - 1)) t2.erase(a[k]);
                if (t3.sum(a[k]) - t3.sum(a[k] - 1)) t3.erase(a[k]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
# 参考资料

- [【组合数学】Erdős–Szekeres定理](https://zhuanlan.zhihu.com/p/150750621)

---

## 作者：Zzzzzzzm (赞：4)

## 题目解析：

看到大佬们都用了很**高级的数据结构**，蒟蒻献上一篇简单易懂的题解。

题目表示不成立当且仅当 $\exists i, j, k$ 使得 $d(i, j)+d(j,k)=d(i,k)$。

我们可以~~画图找规律~~：

当只有一个点或者两个点的时候毫无疑问是显然成立的。

---

当有三个点的时候需要避免三个点单调递增，可以如下：

![](https://pic.imgdb.cn/item/60f501175132923bf80f0718.png)

可以思考一下为什么图左上和图右上需要区分开。

---

当有四个点的时候，我们发现无论加在哪里图右上与右下都是不成立的。但坐上和右上可以如图(第四个点只要在二三点之间即可)

![](https://pic.imgdb.cn/item/60f5026f5132923bf817d36d.png)

得出结论

设四个点为纵坐标为 $a_i,a_j,a_p,a_q$。
可以得出 $a_p<a_i<a_j$ 且 $a_p<a_q<a_j$ 或 $a_p>a_i>a_j$ 且 $a_p>a_q>a_j$

---
当有五个点的时候，这时候加到哪里都不会成立了

所以我们先枚举长度为 $3$ 与 $4$ 的子段，判断是否成立即可

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t, n, a[200005];

template<typename T>
inline void read(T&x){
    x = 0; char q; bool f = 1;
    while(!isdigit(q = getchar()))  if(q == '-')    f = 0;
    while(isdigit(q)){
        x = (x<<1) + (x<<3) + (q^48);
        q = getchar();
    }
    x = f?x:-x;
}

template<typename T>
inline void write(T x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)	write(x/10);
    putchar(x%10+'0');
}

signed main(){
	read(t);
	while(t--){
		read(n);
		for(register int i = 1; i <= n; ++i)
			read(a[i]);
		if(n == 1){												//一个点直接输出 
			write(1);
			puts("");
			continue;
		}
		int ans = n*2-1;										//一个点的子段n个，两个点的子段n-1个 
		for(register int i = 3; i <= n; ++i){
			if(a[i-2] <= a[i-1] && a[i-1] <= a[i])	continue; 
			if(a[i-2] >= a[i-1] && a[i-1] >= a[i])	continue;
			if(a[i-2] == a[i-1] || a[i-1] == a[i])	continue;	//若不单增或单减直接continue 
			ans++;
		}
		for(register int i = 4; i <= n; ++i){					//枚举4个的情况 
			if(a[i-3] < a[i-1] && a[i-3] > a[i-2] && a[i] < a[i-1] && a[i] > a[i-2])	ans++;
			if(a[i-3] > a[i-1] && a[i-3] < a[i-2] && a[i] > a[i-1] && a[i] < a[i-2])	ans++;
		}
		write(ans);												//输出 
		puts("");
	}
    return 0;
}
```

---

## 作者：xkcdjerry (赞：3)

（注：本文中所说的单调如非特别注明，皆指非严格单调）  
由于 Bad Triple 满足  $|x_1-x_2|+|x_2-x_3|=|x_1-x_3|$ , $|y_1-y2|+|y_2-y_3|=|y_1-y_3|$    

所以显然当且仅当 $x_1,x_2,x_3$ 单调，$y_1,y_2,y_3$ 单调时 $(x_1,y_1)$ $(x_2,y_2)$ $(x_3,y_3)$ 为 Bad Triple  

   由此可得若 $b$ 存在 $y_1 \neq y_2 \neq y_3$ 使得其为Bad，那么必定有 $y_1<y_2<y_3$ 或 $y_1>y_2>y_3$  
   
由于第二种情况可以令 $y_1=y_3$ , $y_2=y_2$ , $y_3=y_1$，转化为第一种情况。  
那么不妨令 $y_1<y_2<y_3$

由上可得 $b$ 为 good 当且仅当 $b$ 中不存在长度 $\geqslant 3$ 的单调子序列。    
Erdős–Szekeres定理曰：
> 对于任意 $r$, $s$ ，任何长度为 $(r-1)(s-1)+1$ 的实数数列均存在长度为 $r$ 的单调递增子序列或长度为 $s$ 的单调递减子序列

（论文在 [这里](http://www.numdam.org/article/CM_1935__2__463_0.pdf) ）  


所以为了不出现长度为 $3$ 的单调子序列，代入 $r=s=3$ 可得数列长度若 $\geqslant 5$ 则必定不能避免出现。故得到选出的子串长度 $\leqslant 4$ 的结论。  
即暴力枚举所有长度 $\leqslant 4$ 的子串 $b$ 即可：  
* 如 $|b|=1$ : $n$ 个  
* 如 $|b|=2$ : $n-1$ 个  
* 如 $|b|=3$ : 满足 `!(b1<=b2<=b3||b1>=b2>=b3)` 即可  
* 如 $|b|=4$ : 暴力验证所有长为三的子序列（4个）  

复杂度： $O(n)$  
  
代码：
```cpp
/*
    Code by xkcdjerry
    Time: 2021-07-14
    Generated by cf-tools
*/
#include <cstdio>

#define int long long
#define N 200010
inline bool test3(int a,int b,int c)
{
	return !((a<=b&&b<=c)||(a>=b&&b>=c));
}
inline bool test4(int a,int b,int c,int d)
{
	return test3(a,b,c)&&test3(a,b,d)&&test3(a,c,d)&&test3(b,c,d);
}
int a[N];
void once()
{
	int n;
	scanf("%lld",&n);
	for(int i=0;i<n;i++) scanf("%lld",a+i);
	int ans=2*n-1;
	for(int i=0;i<=n-3;i++)
		if(test3(a[i],a[i+1],a[i+2]))
			ans++;
	for(int i=0;i<=n-4;i++)
		if(test4(a[i],a[i+1],a[i+2],a[i+3]))
			ans++;
	printf("%lld\n",ans);
}
#undef int


int main()
{
    int t;
    scanf("%d",&t);
    while(t--) once();
    return 0;
}
```

---

## 作者：KSToki (赞：2)

# 题目大意
定义一个集合 $b$ 是好的为：不存在不同的 $i,j,k$，使得 $|b_i-b_k|+|i-k|=|b_i-b_j|+|i-j|+|b_j-b_k|+|j-k|$。给定数组 $a$，求其中有多少子区间是好的。
# 题目分析
赛时有强者直接一个单调栈加树状数组拍上去了，但是这题是有性质的。首先如果我们能把绝对值直接去掉，那这个式子一定成立，即集合 $b$ 中不降或不升的长度至少为 $3$ 的子序列。那么可以证明如果集合 $b$ 的大小大于 $4$，那么它一定不是好的，最好画个折线图推一推即可。这下就很简单了，对于每个 $a_i$ 暴力往后扫 $4$ 的大小暴力判断即可，答案也用不着开 `long long`。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[200001]; 
bool check(int x,int y)
{
	for(R int i=x;i<=y;++i)
		for(R int j=x;j<=y;++j)
			if(i!=j)
				for(R int k=x;k<=y;++k)
					if(i!=k&&j!=k)
						if(abs(a[i]-a[k])+abs(i-k)==abs(a[i]-a[j])+abs(i-j)+abs(a[j]-a[k])+abs(j-k))
							return 0;
	return 1;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(R int i=1;i<=n;++i)
			a[i]=read();
		int ans=0;
		for(R int i=1;i<=n;++i)
			for(R int j=1;j<=4&&i+j-1<=n;++j)
				if(check(i,i+j-1))
					++ans;
		putint(ans);
	}
	return 0;
}
```

---

## 作者：ZolaWatle (赞：2)

#### 题目大意

给定平面上的 $n$ 个点，其中第 $i$ 个点的坐标为 $(a_i, i)$，$a_i$ 以一个序列 $\{ a_n \}$ 的方式给出。我们称平面上三个点 $p, q, r$ 构成的一个三元组 $(p, q, r)$ 是**菜的**，当且仅当 $p$ 和 $r$ 点间的曼哈顿距离等于 $p$ 点和 $q$ 点、$q$ 点和 $r$ 点间的曼哈顿距离之和。两点之间的曼哈顿距离如下定义：$d_{A, B} = |x_A - x_B| + |y_A - y_B|$。

对于一个区间 $[l, r]$，其中 $1\leq l\leq r\leq n$，我们称一段区间是**巨的**，当且仅当在 $a_l$ 到 $a_r$ 所表示的这些点中，无论如何无法找出一个**菜的**三元组。求这样的区间的个数。为了避免麻烦，设长度 $<3$ 的区间都是**巨的**。

其中 $1\leq n\leq 2\cdot 10^5, 1\leq a_i\leq 10^9$。

#### 解题思路

首先我们考虑对命题进行化简。在什么情况下一个三元组 $(p, q, r)$ 是**菜的**？假设有 $y_p\leq y_q\leq y_r$，根据曼哈顿距离的定义，我们知道，当 $q$ 在 $x, y$ 方向上与 $p, r$ 的距离之和分别等于 $p$ 与 $r$ 在 $x, y$ 方向上的距离时，这是一个**菜的**三元组。换句话说，点 $q$ 应该被点 $p, r$ “夹在中间”。请见图例：

![](https://cdn.luogu.com.cn/upload/image_hosting/dvnkm0cq.png)

回到序列 $a$ 中，设 $p(a_i, i), q(a_j, j), r(a_k, k)$，由以上假设推广，我们知道若 $i<j<k$，这个三元组是**菜的**，当且仅当 $a_i\leq a_j\leq a_k$ 或 $a_i\geq a_j\geq a_k$。换句话说，如果对于一个区间 $[l, r]$ 中，能够找出至少三个 $a_i$ 使其满足这两个单调性的其中之一。接下来，我们分情况考虑：

- 若 $r-l+1<3$：前文提到长度不超过 $2$ 的区间是**巨的**，则所有这样的情况均合法。则这种情况下对于答案的贡献为 $n + (n-1)$。
- 若 $r-l+1=3$ 或 $4$：对于这两种情况，暴力判断是否能够找出**菜的**三元组即可。由于长度为 $3$ 时只有 $\text{C}_{3}^{3} = 1$ 种，长度为 $4$ 时只有 $\text{C}_{4}^{3} = 4$ 种情况，枚举的复杂程度可以接受。
- 若 $r-l+1\geq 5$：对于前文提到的单调性，我们更进一步地抽象。可以知道，原命题等价为若这段区间中存在长度大于等于 $3$ 的单调不降或单调不增子序列时，则表明至少存在一个**菜的**三元组，即说明这个区间不是**巨的**。我们知道，由于单调不减（增）子序列的性质可知，一个长度 $\geq 5$ 的区间的单调不减（增）子序列的长度 $\geq 3$。那么显然，当区间长度 $\geq 5$ 时，这个区间一定不是**巨的**。

综上所述，设对于 $r-l+1=3$ 或 $4$ 的情况的区间中枚举判断得有 $cnt$ 个区间是**巨的**，则答案为 $ans = cnt+2n -1$。至此，我们将此问题解决。思路已经很详细了，完整代码略，如有需要请私信笔者。

感谢阅读！

---

## 作者：bsdsdb (赞：1)

题意：若点 $A,B,C$ 满足 $d(A,B)+d(B,C)=d(A,C)$，则称他们是「坏三重」。对序列 $\{a_n\}$ 询问有多少对 $(l,r)$ 满足存在两两不同的 $i,j,k\in[l,r]$ 使得 $(i,a_i),(j,a_j),(k,a_k)$ 组成坏三重。$d$ 是曼哈顿距离。

首先对于 $i<j<k$，当且仅当 $a_i\le a_j\le a_k$ 或 $a_i\ge a_j\ge a_k$ 的时候他们是坏三重。接下来有两种方法：

法一：注意到长度大于等于 $5$ 的序列肯定包含坏三重。证：如果想要 $a,b,c,d,e$ 不出现坏三重，又想有两个数相等，那么一定有 $a=e$，否则相等的两数加上 $a$ 或 $e$ 就矛盾了。同理对 $a,b,c,d$ 分析得 $a=d$，然后矛盾，所以五个数互不相同，只能是 $a>b<c>d<e$ 或者相反。如果 $a>c$，那么 $a,c,d$ 就是坏三重，否则 $a,c,e$ 就是坏三重，证毕。所以枚举所有长度不超过 $4$ 的子段即可。

注意不到怎么办？别急，有法二：利用 st 表和二分预处理两个数组 $l,g$，$l_i$ 表示最小的满足 $j>i,a_j\le a_i$ 的 $j$，$g_i$ 就是换成 $\ge$。对于一个固定的 $l$，记 $b_l$ 为最小的使得 $a_{[l,b_l]}$ 包含坏三重的数（最大为 $n+1$），那么 $l$ 对答案的贡献就是 $b_l-l$。有 $b_l=\min(b_{l+1},\min_{i>l,a_i\ge a_l}g_i,\min_{i>l,a_i\le a_l}l_i)$，这一步可以用 BIT 做。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _log2(x) (63-__builtin_clzll(x))

const ll MAXN = 2e5 + 5;
ll n, a[MAXN], nxtge[MAXN], nxtle[MAXN], st_mn[21][MAXN], st_mx[21][MAXN];
map<ll, ll> dc;

struct BIT {
	#define lb(x) (x&-x)
	ll size, val[MAXN];
	void init(ll x = 0) {
		size = x + 2;
		fill_n(val, x + 3, x + 1);
	}
	void add(ll p, ll x) {
		while (p <= size) {
			val[p] = min(val[p], x);
			p += lb(p);
		}
	}
	ll qry(ll p) {
		ll ret = inf;
		while (p) {
			ret = min(ret, val[p]);
			p -= lb(p);
		}
		return ret;
	}
} minnxtge, minnxtle;
ll qry_max(ll l, ll r) {
	ll len = r - l + 1;
//	cerr << "max(" << l << "," << r << ")=" << max(st_mx[_log2(len)][l], st_mx[_log2(len)][r - (1 << _log2(len)) + 1]) << endl;
	return max(st_mx[_log2(len)][l], st_mx[_log2(len)][r - (1 << _log2(len)) + 1]);
}
ll qry_min(ll l, ll r) {
	ll len = r - l + 1;
//	cerr << "min(" << l << "," << r << ")=" << min(st_mn[_log2(len)][l], st_mn[_log2(len)][r - (1 << _log2(len)) + 1]) << endl;;
	return min(st_mn[_log2(len)][l], st_mn[_log2(len)][r - (1 << _log2(len)) + 1]);
}

void init() {
	fill_n(a, n + 3, 0);
	fill_n(nxtge, n + 3, 0);
	fill_n(nxtle, n + 3, 0);
	dc.clear();
	for (ll k = 0; k <= 20; ++k) {
		fill_n(st_mx[k], n + 3, 0);
		fill_n(st_mn[k], n + 3, 0);
	}
}
#define deb(a) cerr << #a << endl;for(ll i = 1; i <= n + 1; ++i) cerr << a[i] << ' '; cerr << endl
int mian() {
	read(n);
	for (ll i = 1; i <= n; ++i) {
		read(a[i]);
		dc[a[i]] = 1;
	}
	ll dcc = 0;
	for (auto& i : dc) {
		i.second = ++dcc;
	}
	for (ll i = 1; i <= n; ++i) {
		a[i] = dc[a[i]];
		st_mn[0][i] = st_mx[0][i] = a[i];
	}
	st_mn[0][n + 1] = st_mx[0][n + 1] = n + 1;
	for (ll k = 1; k <= 20; ++k) {
		for (ll i = 1; i + (1 << k) - 1 <= n + 1; ++i) {
			st_mn[k][i] = min(st_mn[k - 1][i], st_mn[k - 1][i + (1 << (k - 1))]);
			st_mx[k][i] = max(st_mx[k - 1][i], st_mx[k - 1][i + (1 << (k - 1))]);
		}
	}
	nxtge[n + 1] = nxtle[n + 1] = n + 1;
	for (ll i = 1; i <= n; ++i) {
		// nxtg
		ll l = i + 1, r = n + 1, mid;
		while (l < r) {
			mid = (l + r) >> 1;
			if (qry_max(i + 1, mid) >= a[i]) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		nxtge[i] = l;
		// nxtl
		l = i + 1, r = n + 1, mid;
		while (l < r) {
			mid = (l + r) >> 1;
			if (qry_min(i + 1, mid) <= a[i]) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		nxtle[i] = l;
	}
	ll ans = 0;
	minnxtge.init(n), minnxtle.init(n);
	ll lim = n + 1;
	for (ll i = n; i; --i) {
		lim = min(lim, min(minnxtle.qry(a[i]), minnxtge.qry(n + 2 - a[i])));
		ans += lim - i;
		minnxtle.add(a[i], nxtle[i]);
		minnxtge.add(n + 2 - a[i], nxtge[i]);
	}
	write(ans), enter();
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：Joker_M (赞：1)

~~考前写题解攒人品~~

首先，$a$ 的一个子段是好的当且仅当该子段不存在长度大于等于 $3$ 的单调不增（或不减）子序列。

这个结论其他题解都证明的很清楚了，此处不与赘述。

本篇题解主要证明一个被大多数题解一笔带过的结论：

**长度 $\geq 5$ 的子段一定不满足条件。**

或者说：

**长度 $\geq 5$ 的子段必然存在一个长度 $\geq 3$ 的单调不增（或不减）子序列。**

证明方法来源于**《组合数学》。**

定理：

对于一个长度为 $ n^2+1$ 的序列 $a_1,a_2,...,a_{n^2+1}$，它或者存在一个长度为 $ n+1$ 的单调不增子序列，或者存在一个长度为 $n+1$ 的单调不减子序列。

证明：

我们假设不存在长度为 $n+1$ 的单调不减子序列，

**证明必然存在长度为 $ n+1$ 的单调不增子序列**。

我们设 $dp_i$ 表示从 $a_i$ 开始的最长单调不减子序列的长度。

由于不存在长度为 $n+1$ 的单调不减子序列，所以对于所有的 $dp_i$ ，满足 $dp_i \le n$。

因为我们可以以 $a_i$ 自身作为一个长度为 $1$ 的子序列，所以对于所有的 $dp_i$，满足 $1\le dp_i$。

综上， $\forall i \in [1,n^2+1],dp_i\in[1,n]$。

$[1,n]$ 共有 $n$ 个不同的数字，所以 $dp_i$ 有 $n$ 种不同的取值，

根据鸽巢原理可得，$n^2+1$ 个 $dp$ 值中必然有 $n+1$ 个 $dp$ 值取值相同。

等同于把 $n^2+1$ 个小球放进 $n$ 个盒子里，必然有一个盒子中有至少 $n+1$ 个小球。

我们设这 $n+1$ 个相同 $dp$ 值的下标为 $pos_1,pos_2,...pos_{n+1}$，

其中 $1 \le pos_1 < pos_2 < ...<pos_{n+1} \le n^2+1$

那么 $dp_{pos_1}=dp_{pos_2}=...=dp_{pos_{n+1}}$。

**假设**对于某个 $i \in[1,n]$，有 $a_{pos_i}<a_{pos_{i+1}}$，

又因为 $pos_i<pos_i+1$，

那么我们可以将以 $a_{pos_{i+1}}$ 为开头的最长单调不减子序列拿过来，

并且在最前面添上一个 $a_{pos_i}$，组成一个以 $a_{pos_i}$ 为开头的最长单调不减子序列。

所以 $dp_{pos_i} > dp_{pos_i+1}$，

与 $dp_{pos_1}=dp_{pos_2}=...=dp_{pos_{n+1}}$ 相互矛盾，

故假设不成立，所以 $\forall i \in[1,n],a_{pos_i} \geq a_{pos_{i+1}}$，

那么 $a_{pos1} \geq a_{pos_2} \geq ...\geq a_{pos_{n+1}}$ ，

组成了一个长度为 $n+1$ 的单调不增子序列。

原定理得证。

我们再看到最初的结论上，

当 $n=2$ 时，$n^2+1=5$，$n+1=3$，

所以**长度 $\geq 5$ 的子段必然存在一个长度 $\geq 3$ 的单调不增（或不减）子序列，**

得证。

对于原问题，易得长度 $\le2$ 的子段一定满足条件，

长度 $\geq 5$ 的子段一定不满足条件，

所以我们只需要暴力枚举所有长度为 $3$ 或 $4$ 的子段，

再暴力判断他们之中是否存在长度 $\geq 3$ 的单调不增（或不减）子序列即可，

时间复杂度 $\mathcal O(n)$。

---

## 作者：V1mnkE (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1550C)

一道非常不（du）错（liu）的思维题

## 思路
如果你会基本语法的话，很快就可以写出一个 $\mathcal O(tn^5)$ 的做法：

```cpp
 for (int len = 1; len <= n;len++){
            for (int i = 1; i <= n-len+1;i++){
                int j = i + len - 1;
                if(len<=2){
                    ans++;
                    continue;
                }
                bool flag = 0;
                for (int p = i; p <= j;p++){
                    for (int q = p+1; q <= j;q++){
                        for (int r = q+1; r <= j;r++){
                            if(p!=q&&q!=r&&r!=p){
                                if (abs(p - q) + abs(a[p] - a[q]) + abs(q - r) + abs(a[q] - a[r]) == abs(p - r) + abs(a[p] - a[r])){
                                	 flag = 1;
                                	 break;
								}
                            }
                        }
                        if(flag)break;
                    }
                    if(flag)break;
                }
                ans += !flag;
            }
        }
```
虽然肯定跑不满，但这个复杂度还是太高了，我们可以考虑胡一个玄学性质。

在样例中找几组“坏的”三元组 $(i,j,k)$，观察到在 $i<j<k$ 的情况下只有 $b_i\leq b_j\leq b_k$ 或 $b_i\geq b_j\geq b_k$ 时它是坏的，也就是说，一个序列是好的当且仅当这个序列中找不到长度大于等于 $3$ 的单调不升和单调不降子序列。

对于任意一个长度大于 $2$ 的序列 $b$，不妨设 $b_1\leq b_2$，此时对于 $b_3$ 的取值有两种情况：

- $b_1\leq b_3\leq b_2$，则 $b_4\geq b_3$ 时三元组 $(b_1,b_3,b_4)$ 是坏的，$b_4\leq b_3$ 时三元组 $(b_2,b_3,b_4)$ 是坏的。

- $b_3\leq b_1\leq b_2$，则 $b_3\leq b_4\leq b_2$，$b_5$ 无论比 $b_4$ 大还是小，$b_4,b_5$ 都会与 $b_2$ 或 $b_3$ 组成一个坏的三元组。

于是我们得到一个性质：没有长度大于 $4$ 的好的序列，那么这个时候我们就可以把最外面那重循环的上界从 $n$ 改成 $4$，本来的朴素暴力复杂度就会退化到 $\mathcal O(\sum n)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    return x * f;
}
inline void write(int x) {
    static char buf[20];
    static int len = -1;
    if (x < 0) putchar('-'), x = -x;
    do buf[++len] = x % 10, x /= 10;
    while (x);
    while (len >= 0) putchar(buf[len--] + '0');
    putchar('\n');
}
int t, n, a[200005];
long long ans;
int main() {
    t = read();
    while(t--){
        n=read();
        for (int i = 1; i <= n; i++) a[i] = read();
        for (int len = 1; len <= 4;len++){
            for (int i = 1; i <= n-len+1;i++){
                int j = i + len - 1;
                if(len<=2){
                    ans++;
                    continue;
                }
                bool flag = 0;
                for (int p = i; p <= j;p++){
                    for (int q = p+1; q <= j;q++){
                        for (int r = q+1; r <= j;r++){
                            if(p!=q&&q!=r&&r!=p){
                                if (abs(p - q) + abs(a[p] - a[q]) + abs(q - r) + abs(a[q] - a[r]) == abs(p - r) + abs(a[p] - a[r])){
                                	 flag = 1;
                                	 break;
								}
                            }
                        }
                        if(flag)break;
                    }
                    if(flag)break;
                }
                ans += !flag;
            }
        }
        write(ans);
        ans = 0;
    }
}
```

---

## 作者：BetaCutS (赞：0)

下面好像有 dp 做法，我来补充一下代码。

思路我就简单讲讲吧。

引理：如果对于 $i,j,k(i,j,k\le n)$，$(a_i,i),(a_j,j),(a_k,k)$ 是坏的，当且仅当 $a_i\le a_j\le a_k$ 或 $a_i\ge a_j\ge a_k$。

证明：

如果 $a_i\le a_j\le a_k$，则三个点的位置关系为：

![](https://cdn.luogu.com.cn/upload/image_hosting/3cawayxy.png)

容易看出，蓝线长度等于黑线长度加上红线长度。所以这时 $(a_i,i),(a_j,j),(a_k,k)$ 是坏的。

同理，当 $a_i\ge a_j\ge a_k$ 时，$(a_i,i),(a_j,j),(a_k,k)$ 也是坏的。

我们就可以枚举每个区间 $l,r$，用 dp 求出是否有长度大于等于 $3$ 的最长上升子序列或最长下降子序列。

但这样会超时。我们必须优化一下。

对于一个 $5$ 个数的序列，它一定是坏的（证明具体看下面的 dalao）。

然后就可以优化到 $\mathcal O(n)$。

代码：

```cpp
#include<iostream>
using namespace std;
int T,n,a[202219],f[202219],g[202219];
bool check(int l,int r)
{
	for(int i=l;i<=r;i++)
		f[i]=g[i]=1;
	for(int i=l+1;i<=r;i++)
		for(int j=l;j<i;j++)
		{
			if(a[i]>=a[j])
				f[i]=max(f[i],f[j]+1);
			if(a[i]<=a[j])
				g[i]=max(g[i],g[j]+1);
		}
	for(int i=l;i<=r;i++)
		if(f[i]>=3||g[i]>=3)
			return 0;
	return 1;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=i;j<=min(n,i+3);j++)
				if(check(i,j))
					ans++;
		printf("%d\n",ans);
	}
}
```


---

## 作者：白鲟 (赞：0)

## 前言
好像这场 CF 过了挺久了……

不过纪念一下暴力的思路吧。

## 题目分析
题目要求对无法找到三个点 $(b_i,i),(b_j,j),(b_k,k)$ 间的曼哈顿距离满足 $d(p,r)=d(p,q)+d(q,r)$ 的子段计数。分析可知当且仅当 $b_i,b_j,b_k$ 单调且 $i,j,k$ 单调时满足。于是问题转化为对无法找到满足 $i<j<k\wedge(b_i\le b_j\le b_k\vee b_i\ge b_j\ge b_k)$ 的 $(i,j,k)$ 的子段计数。

考虑枚举右端点 $k$，可以发现在以最靠右的满足上述式子的 $i$ 出现位置的右侧位置为左端点的区间均为需要计数的区间。

先仅考虑 $b_i\le b_j\le b_k$ 的情况，那么符合条件的 $i$ 为所有满足 $b_k\ge b_j$ 的 $j$ 前最近满足 $b_j \ge b_i$ 的 $i$ 的最大值。每个 $j$ 前最近满足 $b_j \ge b_i$ 的 $i$ 可用单调栈求出，而对于最终统计可用树状数组维护前后缀最大值。$b_i\ge b_j\ge b_k$ 同理。

最终复杂度为 $\operatorname{O}(n\log n)$。

事实上稍加分析可发现符合题意的子段长度有限。然而如上所述，不发现此性质亦可做。

## 代码
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=2e5;
int T,n,a[maxn+1],copies[maxn+1],last[2][maxn+1],stk[2][maxn+1],BIT[2][maxn+1];
long long ans;
inline int lowbit(int x)
{
	return x&(-x);
}
void change(int opt,int x,int value)
{
	for(int i=x;i<=n;i+=lowbit(i))
		BIT[opt][i]=max(BIT[opt][i],value);
	return;
}
int query(int opt,int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res=max(res,BIT[opt][i]);
	return res;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			BIT[0][i]=BIT[1][i]=0;
			copies[i]=a[i];
		}
		sort(copies+1,copies+n+1);
		stk[0][0]=stk[1][0]=0;
		for(int i=1,r=0;i<=n;++i)
		{
			while(stk[0][0]&&a[stk[0][stk[0][0]]]>a[i])
				--stk[0][0];
			while(stk[1][0]&&a[stk[1][stk[1][0]]]<a[i])
				--stk[1][0];	
			last[0][i]=stk[0][stk[0][0]];
			last[1][i]=stk[1][stk[1][0]];
			int pos=lower_bound(copies+1,copies+n+1,a[i])-copies;
			r=max(r,max(query(0,pos),query(1,n-pos+1)));
			change(0,pos,last[0][i]);
			change(1,n-pos+1,last[1][i]);
			ans+=i-r;
			stk[1][++stk[1][0]]=stk[0][++stk[0][0]]=i;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：f_x_f (赞：0)

这道题如果需要暴力，可能有几率 TLE 。

所以我们可以考虑一个比较简单找规律问题。

设 $l$ 表示子段的长度。

当 $l=1$ 的时候答案可以看出来一定为 $n$。

当 $l=2$ 的时候答案一定为 $n\times (n-1) /2$。

当 $l=3$ 的时候，用一个 $O(n)$ 的复杂度求出答案。

当 $l=4$ 的时候，用一个 $O(n)$ 的复杂度求出答案。

对于 $5\leqslant l$ 的时候，一定没有好的子段，一下是证明。

设数列 $a$ ，长度为 $n$ ，其中 $5 \leqslant n$ 。

当第一种情况， $a_1\leqslant a_2$ ，为了使数列 a 为好的子段，必有 $a_3 \leqslant a_2$ 。此时在进行分类讨论。
1. 当 $a_3\leqslant a_1$ 不论 $a_4$ 的大小如何 $a_1,a_3,a_5$ 与 $a_1,a_3,a_4$ 与 $a_3,a_4,a_5$ 与 $a_1,a_2,a_4$ 与 $a_1,a_2,a_5$ 中一定有一个是坏的子段 。
1. 当 $a_1\leqslant a_3$ 不论 $a_4$ 的大小如何 $a_1,a_3,a_5$ 与 $a_1,a_3,a_4$ 与 $a_3,a_4,a_5$ 与 $a_1,a_2,a_4$ 与 $a_1,a_2,a_5$ 中一定有一个是坏的子段 。

第二种情况是 $a_2\leqslant a_1$ ，进行与上述过程大致相似的分类讨论可以得知当长度为 $len$ ，且 $5\leqslant len$ 一定不是好的子段，所以仅需枚举 $n,n\in {1,2,3,4}$ 既可以求出答案了。 



```cpp
#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	using namespace std;
	#define ll long long
	#define ch char
	#define st string
	#define pa pair<ll,ll>
	#define N 1005
	#define fi first
	#define se second
	#define ref(i,x,y) for(ll i=(x);i<=(y);++i)
	#define fer(i,x,y) for(ll i=(x);i>=(y);--i)
	inline ll read(){
    	ll x=0,f=1;
		ch c=getchar();
		while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}
		while(c>='0' && c<='9') {x=x*10+c-48;c=getchar();}
		return x*f;
	}
}
using namespace my_std;
ll t,n,a[200002],ans;
int Main(){
	n=read();
	ref(i,1,n){
		a[i]=read();
	}
	if(n==1){
		cout<<1<<endl;
		return 0;
	}
//	if(n==2){
//		cout<<3<<endl;
//		return 0;
//	}
	ans=2*n-1;
	ref(i,2,n-1){
		if(a[i-1]==a[i]&&a[i]==a[i+1]){
			continue;
		}
		else if(a[i-1]>=a[i]&&a[i]>=a[i+1]){
			continue;
		}
		else if(a[i-1]<=a[i]&&a[i]<=a[i+1]){
			continue;
		}
		ans++;
	}
	ref(i,3,n-1){
		if(a[i+1]<a[i]&&a[i+1]>a[i-1]&&a[i-2]<a[i]&&a[i-2]>a[i-1]){
			ans++;
		}
		else if(a[i+1]>a[i]&&a[i+1]<a[i-1]&&a[i-2]>a[i]&&a[i-2]<a[i-1]){
			ans++;
		}
	}
	cout<<ans<<endl;
}
int main(){
	t=read();
	while(t--){
		Main();
	}
}
```

---

## 作者：天泽龟 (赞：0)

本题正解是基于某个数学结论的贪心，具有一定的思维性而不具有普适性，这里给大家介绍一种比较通用的解法：**单调栈+线段树**。

### 题意解析

本题题目大意是给定一系列点 $(i,b_i)$，找出所有的子区间，使得该区间内任意三点 $A,B,C$ 中，任意两点的曼哈顿距离与二者分别到第三点的曼哈顿距离和不等。

原题意思很绕，但你分析一下就可以将其转换为：**对于子区间内任意三点的 y 值 $b_x,b_y,b_z$，保证不会单调增，也不会单调减**。换句话说，该子区间的最长不上升子序列与其最长不下降子序列的长度不会超过三。

这样一想就会有很多方式可以去维护信息了。

### 算法解析

由于最长不上升与最长不下降问题是类似的，我们这里只讨论最长不下降问题。

既然我们不能让最长不下降子序列长度为三，那么对于任意一个点 $i$，我们只需要找到恰好使长度为三的点 $l$，之后的点就都满足条件了，那么 i 点对于答案的贡献就是$i-l$。

我们有一个最直观的想法：维护一个 $up[i]$ 表示小于等于 $b_i$ 的点出现的最大位置。很明显，$up[i]$ 可以用单调栈进行维护，这样的话 $up[up[i]]$ 不就是我们要找的答案了吗？

但这明显是有问题的，HACK 数据如下：
	
    5
    1 4 5 2 6
 
对于 $i=5$，$ up[5]=4 , up[4]=1$，而我们发现对于 $i=2,3,5$ 已经构成了长度为三的最长不上升子序列。这种想法的问题在于过于贪心造成了目光短浅。

现在我们要做的就是找一种方法，可以**维护当前点之前（换句话说，$j \in [1,i)$ ）所有的 $up[j]$值，并在 $b_j \leqslant b_i$ 的范围内挑一个 $up[j]$ 最大的**，那就是我们要的 $l$。

于是我们就维护一个经离散化的权值线段树（你要是会动态线段树那就更好了），在 $b_j$ 的位置上维护其 $up[j]$ 的最大值，当询问至 $i$ 点时，我们只需要查询 $(1,b_i ]$ 中的最大值，就是我们要找的答案了。

### 细节实现

- 我们仍要注意到，询问第 $i$ 个节点并不意味着最长不上升子序列的第三位必须以 $b_i$ 结束，HACK 数据如下：

	7
   7 4 8 1 4 5 2

	对于 $i=7$，以 $b_7=2$ 结尾的最短不上升子序列是 以 $i=3$ 为首的 $8,5(4),2$ ，然而我们可以注意到对于以 $i=4$ 为首的 $1,4,5$ 已经构成了最长不下降子序列，因此 $l=4$，因此我们应该保证我们求得的$l$应该是不单调递增的。代码对这里进行处理。

- 其次，对于多个小问的题目不能用 memset，会被 TLE 成傻逼。

然后就没了，献上丑陋的代码：
```cpp
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#define inf 2147483647
#define maxn 200010
#define mid (l+r)/2

using namespace std;

int t,n,a[maxn],b[maxn],dn[maxn],up[maxn];
int t_s[maxn*4],t_b[maxn*4];

void build_s(int o,int l,int r)
{
	if (l==r) t_s[o]=0;
else
{
	build_s(o*2,l,mid); build_s(o*2+1,mid+1,r);
	t_s[o]=0;	
}
}

void build_b(int o,int l,int r)
{
	if (l==r) t_b[o]=0;
else
{
	build_b(o*2,l,mid); build_b(o*2+1,mid+1,r);
	t_b[o]=0;
}
}

int find_s(int o,int l,int r,int x,int y)
{
//	printf("%d %d %d -> %d %d\n",o,o<<1,o<<1 |1,x,y);
	if (x<=l && r<=y) return t_s[o];
	if (l>y || r<x) return -1;
	return max(find_s(o*2,l,mid,x,y),find_s(o*2+1,mid+1,r,x,y));
}

int find_b(int o,int l,int r,int x,int y)
{
	if (x<=l && r<=y) return t_b[o];
	if (l>y || r<x) return -1;
	return max(find_b(o*2,l,mid,x,y),find_b(o*2+1,mid+1,r,x,y));
}

void update_s(int o,int l,int r,int x,int k)
{
	if (l==r && l==x) {t_s[o]=max(t_s[o],k);return;}
	if (l>x || r<x) return;
	update_s(o<<1,l,mid,x,k); update_s(o<<1 | 1,mid+1,r,x,k);
	t_s[o]=max(t_s[o<<1],t_s[o<<1 |1]);
}

void update_b(int o,int l,int r,int x,int k)
{
	if (l==r && l==x) {t_b[o]=max(t_b[o],k);return;}
	if (l>x || r<x) return;
	update_b(o<<1,l,mid,x,k); update_b(o<<1 |1,mid+1,r,x,k);
	t_b[o]=max(t_b[o<<1],t_b[o<<1 |1]);
}

int main()
{	
scanf("%d",&t);
while (t--)
{
	scanf("%d",&n);	
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]),b[i]=a[i];
	}	
	for (int i=1;i<=n;i++) dn[i]=up[i]=0;
	sort(b+1,b+n+1); int N=unique(b+1,b+n+1)-(b+1);  stack<int> s;
	for (int i=1;i<=n;i++) {  //find the smaller left
		while (!s.empty() && a[s.top()]>a[i]) s.pop();
		if (!s.empty()) up[i]=s.top();	s.push(i);
	}	
	while (!s.empty()) s.pop();
	for (int i=1;i<=n;i++) {  //find the bigger left
		while (!s.empty() && a[s.top()]<a[i]) s.pop();
		if (!s.empty()) dn[i]=s.top();	s.push(i);
	}
//	for (int i=1;i<=n;i++) printf("%d,%d\n",dn[i],up[i]);

	int ans=0,l=0;
	build_s(1,1,N); build_b(1,1,N);
	for (int i=1;i<=n;i++) {
		int p=lower_bound(b+1,b+N+1,a[i])-b;
		int second_s=find_s(1,1,N,1,p),second_b=find_b(1,1,N,p,N);
		l=max(l,max(second_s,second_b));
     //对细节一的处理
     	ans+=i-l;  
		update_s(1,1,N,p,up[i]); update_b(1,1,N,p,dn[i]);
	}
	printf("%d\n",ans);
}
}

```

---

