# [ABC230E] Fraction Floor Sum

## 题目描述

求 $\large{\sum\limits_{i=1}^N ⌊\frac{N}{i}⌋}$ 的值

## 样例 #1

### 输入

```
3```

### 输出

```
5```

## 样例 #2

### 输入

```
10000000000```

### 输出

```
231802823220```

# 题解

## 作者：Kreado (赞：6)

题解都只写了整除分块算法，这里介绍另外一种做法：

## Dirchlet 双曲线法

假设 $f=h*g$，$g,h$ 是两个积性函数。

那么有 $\displaystyle\sum_{i=1}^n f(i)=\sum_{i=1}^n(h*g)=\sum_{xy\le n}h(x)g(y)$。

不妨令 $G(n)=\displaystyle\sum_{i=1}^n g(i),H(n)=\sum_{i=1}^n h(i)$，我们钦定两个数 $u,v$ 满足 $uv=n$，则有

$$\begin{aligned}\displaystyle \sum_{i=1}^n f(i)&= \sum_{xy\le n}g(x)h(y)\\ &=\sum_{x\le u,xy\le n}g(x)h(y)+\sum_{u<x\le n,xy\le n}g(x)h(y)\\ &=\sum_{x\le u}g(x)\sum_{y\le n/x}h(y)+\sum_{y\le v}h(y)\sum_{x\le n/y}g(x)-\sum_{x\le u,y\le v} g(x)h(y)\\ &=\sum_{x\le u}g(x)H(n/x)+\sum_{y\le v}h(y)G(n/y)-H(v)G(u) \end{aligned}$$ 

当 $u=v=\sqrt n$ 时，不计入 $H,G$ 的计算时间，那么时间复杂度就是 $O(\sqrt n)$。

这个恒等式我们称之为 Dirichlet 双曲线法，这个式子的三个部分可以被 $y=\dfrac{n}{x}$ 的图像的蓝色，红色，紫色部分所描述。

![](https://picx.zhimg.com/80/v2-23dd303f21f7a223705835c1ba28828b_720w.png?source=d16d100b)

我们假设 $g=h=1$，那么 $g*h=d$，也就是 $f=d$，通过 Dirchlet 双曲线法，我们可以得到：

$$\sum_{i=1}^nf(i)=2\sum_{x\le \sqrt n}(n/x)-\lfloor\sqrt n\rfloor^2$$

对比于整除分块，常数更小，实现也更为简单。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,sq,ans; 
int main(){
	scanf("%lld",&n);
	sq=sqrt(n);
	for(ll i=1;i<=sq;i++) ans+=n/i;
	printf("%lld",ans*2-sq*sq); 
	return 0;
}

```


---

## 作者：CQ_Bob (赞：0)

## 分析

整除分块模板题。

对于这道题，很显然地能够发现，有一些 $\lfloor \frac{n}{i} \rfloor$ 是相同的。如果我们将这些相同的贡献统一算出来，时间复杂度将大大减小，因为随着 $i$ 的增加，$\lfloor \frac{n}{i} \rfloor$ 相同的数量是越来越多的。

考虑一个区间 $[l,r]$ 的任意一个 $l\le i \le r$ 都有 $\lfloor \frac{n}{l} \rfloor=\lfloor \frac{n}{i} \rfloor$ 时的情况。因为 $\lfloor \frac{n}{l} \rfloor=\lfloor \frac{n}{r} \rfloor$，所以 $\frac{n}{r} \ge \lfloor \frac{n}{l} \rfloor$，即 $r \le \frac{n}{\lfloor \frac{n}{l} \rfloor}$。从中不难发现对于一个区间 $[l,r]$，已知 $l$ 就能够求出来对应的 $r$。可以枚举 $l$，根据区间的连续性，下一个区间的左端点一定等于这个区间的右端点下标 $+1$。而一个区间 $[l,r]$ 的贡献就是 $(r-l+1)\times \lfloor\frac{n}{l}\rfloor$，累加起来就行。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
il void solve(){
	int n,ans;cin>>n;
	for(re int l=1,r;l<=n;l=r+1) r=n/(n/l),ans+=(r-l+1)*(n/l);
	cout<<ans;return ;
}
signed main(){
	solve();return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路
暴力思路很好想，但是复杂度是会超时。

因为 $\lfloor\frac{n}{i}\rfloor$ 会出现一些重复的数字，那么我们可以看一下在 $i\le \sqrt n$ 的时候会有 $\sqrt n$ 种不同的数字，当 $i>\sqrt n$ 的时候，因为当 $i\le\sqrt n$ 的时候最小的是 $\sqrt n$，然后因为后面的一定是小于等于前面的，那么后面的最多是 $\sqrt n$ 个的。

我们可以把他分成好几个块来进行快速求和，我们考虑怎么求出某一个值的右端点，第 $i$ 个所在的块值是 $k=\lfloor\frac{n}{i}\rfloor$，显然 $k\le \frac{n}{i}$，根据这个可以推出 $\lfloor\frac{n}{k}\rfloor\ge\lfloor\frac{n}{\frac{n}{i}}\rfloor$，通过约分 $\lfloor\frac{n}{k}\rfloor\ge i$，所以他所在的右端点是 $\lfloor\frac{n}{\lfloor\frac{n}{i}\rfloor}\rfloor$。

最后下一个的块的左端点是上一个块的右端点加一。

我们就可以直接把区间的长度乘上 $\frac{n}{i}$ 就可以了。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n;
	cin>>n;
	int ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=(n/l)*(r-l+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Prolystic (赞：0)

## Part 0 前言
[原题目](https://www.luogu.com.cn/problem/AT_abc230_e)
## Part 1 题意简述
* 给定 $N$。
* 求 $\sum^N_{i=1}\lfloor \frac{N}{i}\rfloor$。

## Part 2 分析
看到本题大家应该不难想到直接暴力求和，毕竟题目问题非常简单（至少看起来）。这样的求和时间复杂度 $O(N)$，虽说总体来讲不算很高，但 $N\leq10^{12}$ 的数据规模就决定了不可能用这种方法求解。最终结果就是 TLE。（代码及评测结果在 Solve1 中给出）。

我么不妨列举一下，当 $N=5$ 时的情况。

$\lfloor\frac{5}{1}\rfloor=5,\lfloor\frac{5}{2}\rfloor=2,\lfloor\frac{5}{3}\rfloor=1,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{5}{5}\rfloor=1$

不难发现后三个的结果都是 $1$。也就是说，在一段区间 $l$ 到 $r$ 内，每个 $\lfloor\frac{N}{i}\rfloor$ 都是一个固定值 $k$。

我们可以求出所有不同的 $\lfloor\frac{N}{i}\rfloor$，乘上它们对应的个数，加起来，得到结果。

在区间内，右端点 $r=\lfloor\frac{N}{k}\rfloor$，而 $k=\lfloor\frac{N}{l}\rfloor$，所以 $r=\lfloor\frac{N}{\lfloor\frac{N}{l}\rfloor}\rfloor$。

所以我们只需要枚举每个 $l,r$，算出 $k$，乘上区间元素个数 $r-l+1$，加起来即可。（代码及评测结果在 Solve2 中给出）

本体实质是一道求数论分块的题，可以证明时间复杂度 $O(\sqrt{N})$。
## Part 3 代码

* Solve1 

```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
long long n,sum = 0;
int main()
{
	scanf("%lld",&n);
    for(long long i = 1;i<=n;i++)
    {
    	sum+=(n/i);
    }
    printf("%lld",sum);
	return 0;
}
```

* Solve2

```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
long long n,sum = 0;
int main()
{
	scanf("%lld",&n);
    for(long long l = 1,r;l<=n;l = r+1)
    {
    	r = n/(n/l);
        sum+=(r-l+1)*(n/l);
    }
    printf("%lld",sum);
   	return 0;
}
```

## Part 4 测试信息
![](https://cdn.luogu.com.cn/upload/image_hosting/yl7sbkkh.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/vlqoj39c.png)

[记录(Solve1)](https://atcoder.jp/contests/abc230/submissions/39366695)

[记录(Solve2)](https://atcoder.jp/contests/abc230/submissions/39366644)

创造和谐洛谷，拒绝抄袭题解。

适度刷题益脑，沉迷刷题伤身。

拒绝盗版代码，提倡自我思考。

健康学习ＯＩ，快乐美好生活。


---

## 作者：lzyqwq (赞：0)

整除分块模板题。

根据向下取整的性质，肯定有一些数是相同的。并且是一段连续的区间。所以我们枚举左端点 $l$，则这一段的值为 $\left\lfloor\dfrac{n}{l}\right\rfloor$，设 $[l,r]$ 的值相同，则有 $\left\lfloor\dfrac{n}{l}\right\rfloor=\left\lfloor\dfrac{n}{r}\right\rfloor$。去掉向下取整，则 $\dfrac{n}{r}\ge \left\lfloor\dfrac{n}{l}\right\rfloor$，即 $r\le \dfrac{n}{\left\lfloor\frac{n}{l}\right\rfloor}$。显然右端点就是 $\dfrac{n}{\left\lfloor\frac{n}{l}\right\rfloor}$，所以 $\left\lfloor\dfrac{n}{l}\right\rfloor$ 的贡献就是 $r-l+1$ 个。下一个 $l$ 即为当前 $r$ 加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,sum;
signed main(){
    scanf("%lld",&n);
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        sum+=(r-l+1)*(n/l);
    }
    printf("%lld",sum);
}
```


---

## 作者：中缀自动机 (赞：0)

基础：

- 求和符号

- $\sum\limits_{i=1}^na_i=a_1+a_2+...+a_n$

- 向下取整：

- $\left\lfloor\dfrac{1}{2}\right\rfloor=0,\left\lfloor-\dfrac{1}{2}\right\rfloor=-1$

- 向上取整：

- $\left\lceil\dfrac{1}{2}\right\rceil=1,\left\lceil-\dfrac{1}{2}\right\rceil=0$

------------
正题：

当有一个这样的问题：

$\sum\limits_{i=1}^{10}{\left\lfloor\tfrac{10}{i}\right\rfloor}=?$

列个表格?

$\boxed{\left\lfloor\dfrac{10}{1}\right\rfloor=10},\boxed{\left\lfloor\dfrac{10}{2}\right\rfloor=5},\boxed{\left\lfloor\dfrac{10}{3}\right\rfloor=3},\boxed{\left\lfloor\dfrac{10}{4}\right\rfloor=2},\boxed{\left\lfloor\dfrac{10}{5}\right\rfloor=2},$

$\boxed{\left\lfloor\dfrac{10}{6}\right\rfloor=1},\boxed{\left\lfloor\dfrac{10}{7}\right\rfloor=1},\boxed{\left\lfloor\dfrac{10}{8}\right\rfloor=1},\boxed{\left\lfloor\dfrac{10}{9}\right\rfloor=1},\boxed{\left\lfloor\dfrac{10}{10}\right\rfloor=1}$

如果我们把这些一个一个加起来，那会很慢，那么怎么办呢？

于是，观察表格可以发现，有一些答案和后面的答案一样（一段区间内一样）

那么我们就可以把 $1\sim 10$ 分个段：分别是 $1,2,3,4\sim 5,6\sim 10$

这样我们就只用计算 $5$ 次 $\left\lfloor\dfrac{10}{i}\right\rfloor$就行了。

那么，问题来了，如何确定答案相同的区间呢？

公式推导：

$\sum\limits_{i=1}^{n}{\left\lfloor\tfrac{n}{i}\right\rfloor}=?$

（注：$n$ 为正整数）

假设我们已知某一个分块的左端点 $l$，要求解出该分块的右端点 $r$。设该分块的数值为 $k$，对于该分块中的每个数 $i$，有 $k=\left\lfloor\dfrac{n}{i}\right\rfloor=\left\lfloor\dfrac{n}{l}\right\rfloor$，即 $ik\leq n$，想一想就可以知道当 $i=r$ 时，也就是 $\max(rk)\leq n$ 为最大值。

所以，就可以发现：

$r=\left\lfloor\dfrac{n}{k}\right\rfloor$


又因为：

$k=\left\lfloor\dfrac{n}{l}\right\rfloor$

所以：

$r=\left\lfloor\dfrac{n}{\left\lfloor\dfrac{n}{l}\right\rfloor}\right\rfloor$
 

------------


则，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
int t,n;
signed main(){
	n=read();
	int ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=(r-l+1)*(n/l);
	}
	print(ans); 
	return 0;
}
```


------------

$\forall l\leq n$，寻找最大的 $r$，使得：

$\left\lfloor \frac{n}{l}\right\rfloor=\left\lfloor\frac{n}{r}\right\rfloor$

证：

$r=\left\lfloor\frac{n}{\left\lfloor\frac{n}{l}\right\rfloor}\right\rfloor$

证明：

$\left\lfloor\frac{n}{l}\right\rfloor\leq\frac{n}{l}$

$l=\left\lfloor\frac{n}{\frac{n}{l}}\right\rfloor \leq \left\lfloor\frac{n}{\left\lfloor\frac{n}{l}\right\rfloor}\right\rfloor$

$l_{\max}=\left\lfloor\frac{n}{\left\lfloor\frac{n}{l}\right\rfloor}\right\rfloor=r$

证毕。

---

## 作者：MYiFR (赞：0)

### 题目大意
如原题面，给定 $N$，求 $\displaystyle\sum_{i=1}^{N}\lfloor\frac{N}{i}\rfloor$，其中 $\lfloor x\rfloor$ 表示 $x$ 向下取整，即不大于 $x$ 的最大整数。

### 解题思路
看了一眼以前的题解，基本都是分块，现在给一个全新且不抽象的糊分大法。

考虑暴力。显然时间复杂度是 $O(N)$ 的，这很不好，于是我们来想想怎么优化。

注意到数据范围，$1\leq N\leq 10^{12}$，这是在很明显地暗示我们整出一个 $O(\sqrt N)$ 或者差不多的做法。但是 $\displaystyle\frac{N}{i}$ 的取值范围无疑是在 $[1,N]$ 内，显然不存在像分解因数一样可以只枚举 $\sqrt N$ 就能求出全部答案的方法。（想到分解因数其实是因为我一开始就打算这么写的）

但是我们很容易就发现这么一个事：就是在 $i\in [1,\lfloor\sqrt N \rfloor]$ 区间以内，$\displaystyle\frac{N}{i}$ 的值在 $[\sqrt N,N]$ 以内，但并不能取到这里面的所有值。

那我们就不需要枚举 $[\sqrt N,N]$，直接对 $i\in [1,\lfloor\sqrt N \rfloor]$ 暴力求答案，这是 $O(\sqrt N)$ 的。

剩下的 $i$ 怎么办呢？我们又注意到对于剩下的 $i$ ，$\displaystyle\frac{N}{i}$ 的值在 $[1,\sqrt N]$ 内，不能枚举 $i$，但是现在就可以枚举 $\displaystyle\frac{N}{i}$ 求贡献了，毫无疑问，这也是 $O(\sqrt N)$ 的。

统一一下，总时间复杂度为 $O(\sqrt N)$，这是好的。 

（tips：上面说过了，原本我是打算分解因数的，需要判断 $\sqrt N$ 的去重问题，于是我就打算逃课，用了 set。后来发现这个方法不对，但又懒得把 set 改成 vector 或者什么其他的东西，所以下面的 AC 代码其实是 $O(\sqrt N \log\sqrt N)$ 的，这也就是我为什么说可以用 $O(\sqrt N)$ **或者差不多**的做法的原因。）

### AC 代码
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<utility>
#include<string>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<unordered_map>
#include<chrono>
#define ll long long
#define ull unsigned ll
#define db double
#define ldb long db
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
#define DEBUG
using namespace std;
//mt19937_64 rnd=mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
ll n,lst,ans;
set<ll> a;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i*i<=n;++i){
		ans+=n/i;
		a.insert(n/i);
		lst=i;
	}
	for(auto itr=a.begin();itr!=a.end();++itr){
		ll tmp=(*itr);
		ans+=(tmp-lst)*(n/tmp);
		lst=tmp;
	}
	printf("%lld",ans);
	return 0;
}
//Ltwcfm.
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_abc230_e)

[Atcoder 链接](https://atcoder.jp/contests/abc230/tasks/abc230_e)

题目大意：

求 $\sum\limits_{i=1}^{n}\left\lfloor\dfrac{n}{i}\right\rfloor(1\leq n\leq 10^{12})$。

思路：

这一个题让我们求向下取整的值。我们可以考虑向下取整的取值分块。显然，$\left\lfloor\dfrac{n}{i}\right\rfloor$ 有单调性。

- 在 $1\leq i\leq n$ 的情况下，$\left\lfloor\dfrac{n}{i}\right\rfloor$ 只有不超过 $\lfloor2\sqrt{n}\rfloor$ 中取值。下证结论的正确性。

如果 $i\leq\sqrt{n}$，那么 $\left\lfloor\dfrac{n}{i}\right\rfloor$ 最多有 $\lfloor\sqrt{n}\rfloor$ 种取值。如果 $i>\sqrt{n}$，那么 $\left\lfloor\dfrac{n}{i}\right\rfloor\leq\lfloor\sqrt{n}\rfloor$，也最多有 $\lfloor\sqrt{n}\rfloor$ 种取值。综上，$\left\lfloor\dfrac{n}{i}\right\rfloor$ 最多有 $\lfloor2\sqrt{n}\rfloor$ 种取值。

- 如果在 $[l,r]$ 的区间内 $\left\lfloor\dfrac{n}{i}\right\rfloor$ 相等，那么 $r\leq\dfrac{n}{\left\lfloor\frac{n}{i}\right\rfloor}$。下证结论正确性。

显然有 $\left\lfloor\dfrac{n}{l}\right\rfloor=\left\lfloor\dfrac{n}{r}\right\rfloor$。去掉 $\dfrac{n}{r}$ 的取整符号，则有：$\dfrac{n}{r}\geq\left\lfloor\dfrac{n}{l}\right\rfloor$。化简得 $r\leq\dfrac{n}{\left\lfloor\frac{n}{i}\right\rfloor}$。

综上，我们可以枚举每一个取值区间 $[l,r]$ 的 $l$，再根据 $l$ 求出 $r$，存储 $l$ 的变量变成 $r+1$。时间复杂度为 $\Theta(\sqrt{n})$。

坑点：

1. 全程开 ```long long```（包括循环变量），否则会炸精度！
1. ```for``` 循环末尾循环体空着就行，不要写成 ```i++```！
1. 改循环变量时的 $r$ 的取值要写成 $\left\lfloor\dfrac{n}{\left\lfloor\frac{n}{i}\right\rfloor}\right\rfloor+1$，因为不能重复枚举 $\left\lfloor\dfrac{n}{\left\lfloor\frac{n}{i}\right\rfloor}\right\rfloor$！

上代码：
```cpp
#include <iostream>
using namespace std;

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    long long n;
    cin >> n;
    long long sum = 0;// 坑点 1：全程开 long long！
    for (long long i = 1; i <= n;){// 坑点 2：末尾循环体空着！
        long long temp = n / i;
        long long r = n / temp + 1;// 坑点 3：r 的取值
        sum += (r - i) * temp;
        i = r;
    }
    cout << sum << "\n";
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

题意：计算 $ \displaystyle\sum_{i=1}^N\ \left[\ \frac{N}{i}\ \right],n\leq 10^{12} $。

这题和 [H(n)](https://www.luogu.com.cn/problem/UVA11526)
完全一致，可以用数论分块解决。

数论分块：通过手动模拟小数据的值可以发现，实际上会被用上的本质不同的值只有 $ \sqrt{n} $ 个，于是直接把答案相同的块一起统计即可，具体过程见代码实现。

时间复杂度 $ \mathcal{O}(\sqrt{n}) $，可以通过。

代码：

```cpp
#include <iostream>
using namespace std;
#define int long long
signed main()
{
int n,t;
cin>>n;
int ans=0;
for(int l=1,r;l<=n;l=r+1)
{
	r=n/(n/l);
	ans+=(r-l+1)*(n/l);
}
cout<<ans;
}
```


---

