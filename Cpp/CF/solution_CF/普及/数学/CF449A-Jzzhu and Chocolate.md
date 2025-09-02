# Jzzhu and Chocolate

## 题目描述

Jzzhu has a big rectangular chocolate bar that consists of $ n×m $ unit squares. He wants to cut this bar exactly $ k $ times. Each cut must meet the following requirements:

- each cut should be straight (horizontal or vertical);
- each cut should go along edges of unit squares (it is prohibited to divide any unit chocolate square with cut);
- each cut should go inside the whole chocolate bar, and all cuts must be distinct.

The picture below shows a possible way to cut a $ 5×6 $ chocolate for $ 5 $ times.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF449A/f603977ae2da90c32a153ce408d6e4d1586349b7.png)Imagine Jzzhu have made $ k $ cuts and the big chocolate is splitted into several pieces. Consider the smallest (by area) piece of the chocolate, Jzzhu wants this piece to be as large as possible. What is the maximum possible area of smallest piece he can get with exactly $ k $ cuts? The area of a chocolate piece is the number of unit squares in it.

## 说明/提示

In the first sample, Jzzhu can cut the chocolate following the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF449A/9c469c7998d7372246af19aeed82d0eba53211c4.png)In the second sample the optimal division looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF449A/4201d969cba3a3158e29e86ca8b9fbb2d41819d5.png)In the third sample, it's impossible to cut a $ 2×3 $ chocolate $ 4 $ times.

## 样例 #1

### 输入

```
3 4 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6 4 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
2 3 4
```

### 输出

```
-1
```

# 题解

## 作者：ZLCT (赞：4)

# CF449A Jzzhu and Chocolate
## 题目翻译
给一个 $n\times m$ 的矩形，要切 $k$ 刀，求切完以后最小矩形面积的最大值。
## 平面几何 vs 基础数论
#### NO.1 平面几何（官方题解）
首先看到这个题自然就会想到以几何的思路去划分，假设横着切 $w$ 刀，则竖着切 $k-w$ 刀。由于我们要最小面积最大，于是肯定平均切更优。\
那么答案就是 $\lfloor{\frac{n}{w+1}}\rfloor\times \lfloor{\frac{m}{k-w+1}}\rfloor$。根据数轮分块的知识我们知道 $\lfloor{\frac{n}{w+1}}\rfloor$ 的取值只有 $\sqrt{n}$ 种，于是我们可以枚举 $\lfloor{\frac{n}{w+1}}\rfloor$ 的值取最大的 $\lfloor{\frac{n}{w+1}}\rfloor\times \lfloor{\frac{m}{k-w+1}}\rfloor$。\
无解就是切割的刀数比“空隙”还多。
#### code by `tfg`
```cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
 
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
 
int main() {
	std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
	long long n, m, k;
	std::cin >> n >> m >> k;
	long long ans = -1;
	for(long long l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		// making r-1 cuts
		// we can get side size n / r
		long long side = n / r;
		long long need = std::max(0LL, k - (r - 1));
		if(need > m - 1) continue;
		ans = std::max(ans, side * (m / (need + 1)));
	}
	std::cout << ans << '\n';
}
```
#### NO.2 数论（慎入）
无解情况依旧和上面一样，我们着重考虑有解情况。\
这个题如果有关于数论的一些直觉，那可以发现如果 $k+1|n$ 或 $k+1|m$，那么直接全横着或竖着切分成 $\frac{n}{k+1}$ 或 $\frac{m}{k+1}$。因为一刀至少使分的部分 $+1$，所以至少存在 $k+1$ 个部分，于是 $ans\le \lfloor\frac{nm}{k+1}\rfloor$，而我们的构造方法恰好可以取到。\
由于下面贪心结论比较容易想到，但是不好证明且目前网上尚未找到一份很好的证明，于是我们先贪再证。\
首先给出结论，我们尽可能沿着一个方向（横或竖）切，若无法切再换方向。\
证明：我们考虑存在一组最优解比贪心解更优，假设横竖分别切了 $x\le n-1,k-x\le m-1$ 刀。根据 `NO.1` 的选平均思想，那么此时的答案就是 $\lfloor{\frac{n}{x+1}}\rfloor\times \lfloor{\frac{m}{k-x+1}}\rfloor$。\
我们贪心解则会根据先横切还是先竖切构造出两个解，下面对于 $k$ 与 $n-1,m-1$ 的关系分成如下情况分别证明：
- $k\le n-1$ 且 $k\le m-1$ 这种情况根据贪心构造我们只会全横切或全竖切，答案分别为\
$\lfloor\frac{n}{k+1}\rfloor\times m$ 和 $\lfloor\frac{m}{k+1}\rfloor\times n$。\
于是我们要证明的就是：\
$\lfloor{\frac{n}{x+1}}\rfloor\times \lfloor{\frac{m}{k-x+1}}\rfloor\le\max(\lfloor\frac{m}{k+1}\rfloor\times n,\lfloor\frac{n}{k+1}\rfloor\times m)$。\
当然左式是小于右式任意一个的，我们以 $\lfloor\frac{m}{k+1}\rfloor\times n$ 为例证明。\
我们考虑放缩左式：\
$\lfloor{\frac{n}{x+1}}\rfloor\times \lfloor{\frac{m}{k-x+1}}\rfloor\le\frac{n}{x+1}\times\lfloor{\frac{m}{k-x+1}}\rfloor$\
（不下取证可能还多了小数部分）\
我们接下来就变成了证明\
$\frac{n}{x+1}\times\lfloor{\frac{m}{k-x+1}}\rfloor\le\lfloor{\frac{m}{k+1}}\rfloor\times{n}$。\
首先把 $\frac{n}{x+1}$ 乘到右面：\
$\lfloor{\frac{m}{k-x+1}}\rfloor\le\lfloor{\frac{m}{k+1}}\rfloor\times{(x+1)}$。\
我们继续放缩左式：\
$\lfloor{\frac{m}{k-x+1}}\rfloor\le\frac{m}{k-x+1}$\
（原理同上面放缩）\
所以我们要证明：\
$\frac{m}{k-x+1}\le\lfloor{\frac{m}{k+1}}\rfloor\times{(x+1)}$\
我们等式两边同时 $\times(k-x+1)$ 变成：\
$ m\le\lfloor{\frac{m}{k+1}}\rfloor\times{(x+1)}\times(k-x+1)$\
把 $(x+1)\times(k-x+1)$ 展开得：\
$xk-x^2+x+k-x+1=xk-x^2+k+1$\
我们用这个式子与 $k+1$ 比大小（作差法）：\
$xk-x^2+k+1-(k+1)=xk-x^2=x(k-x)$\
由于 $k>x$ 于是 $x(k-x)>0$ 所以 $(x+1)\times(k-x+1)>k+1$\
所以我们现在只需要证明：\
$ m\le\lfloor{\frac{m}{a}}\rfloor\times{b}$（$b>a$且$a<m$）\
到这里应该可以直接感性证明了，但是为了严谨我们继续对 $b$ 放缩：\
因为 $b\le a+1$，所以 $\lfloor{\frac{m}{a}}\rfloor\times{b}\ge\lfloor{\frac{m}{a}}\rfloor\times{(a+1)}$\
证明对象就变成了：
$ m\le \lfloor{\frac{m}{a}}\rfloor\times{(a+1)}$\
这个好证明，$\lfloor{\frac{m}{a}}\rfloor\times{a}$ 是 $m\div{a}$ 的整数部分，而因为 $m>a$，所以 $\lfloor{\frac{m}{a}}\rfloor\ge 1$。因为 $1$ 肯定大于 $m\div{a}$ 的小数部分，所以 $ m\le \lfloor{\frac{m}{a}}\rfloor\times{(a+1)}$ 证毕。\
接下来一步一步向上回带就能证明我们最初猜想。

- 利用上面的证明，对于 $k\le n-1$ 或 $k\le m-1$ 的情况都可以用我们的构造做到最优。
- 那对于 $k>n-1$ 且 $k>m-1$ 的情况呢？\
按照我们的构造则会沿一个方向全部切完，使之变成若干个 $1\times x$ 的长条。\
具体地最后我们切出来的最小面积就是 $\max(\lfloor{\frac{m}{k-n+2}}\rfloor,\lfloor{\frac{n}{k-m+2}}\rfloor)$。\
那我们要证明的就是：
$ \lfloor{\frac{n}{x+1}}\rfloor\times \lfloor{\frac{m}{k-x+1}}\rfloor\le\max(\lfloor{\frac{m}{k-n+2}}\rfloor,\lfloor{\frac{n}{k-m+2}}\rfloor)$\
这个式子我们发现与第一条的式子十分相似，于是也可以用放缩法证明，由于篇幅过长，这里给予另一种优雅的证明：\
首先我们证明一个引理：\
如果 $ \lfloor{\frac{n}{x+1}}\rfloor$ 或 $\lfloor{\frac{m}{k-x+1}}\rfloor$ 有一个为 $1$，那么我们一定会把那个方向都切掉。\
因为一旦出现一个为 $1$，那么无论在这个方向怎么切，最后都不会对答案产生影响，于是只要出现长或宽为 $1$，那么我们的结论一定成立。\
接下来我们假设 $n\ge m$，那么如果我们不希望出现 $1$ 的情况，那么横着最多切 $\lfloor{\frac{n-1}{2}}\rfloor$，竖着最多切 $\lfloor{\frac{m-1}{2}}\rfloor$ 刀，由于 $k>\max(n-1,m-1)$，所以 $k\ge\max(n,m)$（这个真的显然）。\
因为切的刀术要等于 $k$，所以 $\lfloor{\frac{n-1}{2}}\rfloor+\lfloor{\frac{m-1}{2}}\rfloor=k$。\
我们稍微观察一下上面的条件，会发现这种情况不可能出现。\
（分类讨论 $n,m$ 奇偶即可）

于是，我们就全部证完了！！！\
证了整整一天一夜，但是从看似不可证之物中寻其奥妙，从看似显然易证之事中寻求严谨，这正是数论美妙的地方啊。
#### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans;
signed main(){
    cin>>n>>m>>k;
    if(n-1+m-1<k){
        cout<<-1<<'\n';
        return 0;
    }
    if(n%(k+1)==0||m%(k+1)==0){
        cout<<n*m/(k+1)<<'\n';
        return 0;
    }
    if(k<n){
        ans=max(ans,(n/(k+1))*m);
    }
    if(k<m){
        ans=max(ans,(m/(k+1))*n);
    }
    if(k-n+2>0)ans=max(ans,m/(k-n+2));
    if(k-m+2>0)ans=max(ans,n/(k-m+2));
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：是个汉子 (赞：4)

### Solution

可以设横向切了 $x$ 次，则纵着切了 $k-x$ 刀，为使最小值最大化，所以要切的均匀。那么 $ans=\left\lfloor\dfrac n{x+1}\right\rfloor\cdot\left\lfloor\dfrac m{k-x+1}\right\rfloor(0\leq x\leq k)$ 。

因为 $\left\lfloor\dfrac n{i}\right\rfloor$ 最多有 $\sqrt n$ 种取值，所以枚举找最小值即可。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
ll n,m,k;

ll solve(ll n,ll m,ll k){
    ll ans=1;
    for(int i=1,pre=0;i<=n;i=pre+1){
        pre=n/(n/i);
        if(pre>k+1){
            ans=max(ans,n/(k+1)*m);
            break;
        }
        ans=max(ans,(n/pre)*(m/(k-pre+2)));
    }
    return ans;
}

int main(){
    while(~scanf("%lld%lld%lld",&n,&m,&k)){
        if(k>n+m-2) puts("-1");
        else printf("%lld\n",solve(n,m,k));
    }
    return 0;
}
```



---

## 作者：ZSYZSYZSYZSY (赞：2)

# CF449A Jzzhu and Chocolate

## Description
给出一个 $N \times M$ 的矩阵，给 $K$ 个操作，每次操作可以横或竖切割矩阵，求 $K$ 次切割，最大化最小块的面积.

## Solution
由题意，可以设横向切了 $x$ 次，则纵着切了 $k-x$ 刀，为使最小值最大化，所以要切的均匀。那么难点来了！怎么求面积呢？非常简单！长能切的块数乘宽能切的块数就行了。那么 $ans = \lfloor \frac {n}{x+1}\rfloor \times \lfloor \frac {m}{k-x+1} \rfloor (0 \leq x \leq k)$ 种取值。

因为 $\lfloor \frac {n}{i} \rfloor$ 最多有 $\sqrt{n}$ 种取值，所以枚举找最小值即可。

还有一种情况，就是如果无法切大巧克力 $k$ 次，要打印 $-1$。情况就是首先，先分析最多能且几刀，横着切最多可以切 $n-1$ 刀，竖着切最多可以切 $m-1$ 刀，所以 $k \leq n+m-2$ ，也就是当 $k > n+m-2$ 时，直接输出 $-1$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, k;

ll calc(ll n, ll m, ll k)
{
    ll ans = 1;
    ll tmp = 0;
    for (int i = 1; i <= n; i = tmp + 1)
    {
        tmp = n / (n / i);
        if (tmp > k + 1) // 就是0小于等于x小于等于k
        {
            ans = max(ans, n / (k + 1) * m);
            break;
        }
        ans = max(ans, (n / tmp) * (m / (k - tmp + 2)));
    }
    return ans;
}

int main()
{
    scanf("%lld %lld %lld", &n, &m, &k);
    if (k > n + m - 2)
        printf("-1");
    else
        printf("%lld\n", calc(n, m, k));
    return 0;
}

```


---

## 作者：naroto2022 (赞：2)

# CF449A题解
    
### 思路

切法分为这几种情况：

1. 输出 $-1$ 的情况：首先，先分析最多能且几刀，横着切最多可以切 $n-1$ 刀，竖着切最多可以切 $m-1$ 刀，所以 $k \leqslant n+m-2$。也就是说当 $k>n+m-2$ 时，直接输出 $-1$。
2. 当 $k<m$ 且 $k<n$ 时，这种情况非常简单，最优的就是都是横着切或者都是竖着切，且 $k$ 刀就把整块分成了 $k+1$ 块，这时重点就来了，要比较全横着切和全竖着切，要是全横着切，长为 $m$，宽为 $\lfloor n*\frac{1}{k+1}\rfloor$，全竖着切同理，最后输出两个中最大的。
3. 当 $k<m$ 且 $k\geqslant n$ 时，那竖着最优的就是全竖着切，与第 $2$ 种同理。另一种就是先横着切把一整块切成 $n$ 条 $1\times m$ 的条条，这时已经切了 $n-1$ 刀，剩下 $k-n+1$ 刀，这么多刀会将每条 $1\times m$ 切成 $k-n+2$ 块，所以这时的最优情况为长为 $\lfloor m*\frac{1}{k-n+2}\rfloor$，宽为 $1$。最后输出两个中最大的。
4. 当 $k\geqslant m$ 且 $k<n$ 时，方法同第 $3$ 种情况。
5. 当 $k\geqslant m$ 且 $k\geqslant n$ 时，方法同第 $3$ 种情况。一种是长为 $\lfloor m*\frac{1}{k-n+2}\rfloor$，宽为 $1$；一种是长为 $\lfloor n*\frac{1}{k-m+2}\rfloor$，宽为 $1$。输出两者中大的即可。

那么难点来了！怎么求面积呢？非常简单！长乘宽就行了。

### 总结

1. 本题因为输出必须为整数，所以要向下取整，因此每种情况都需要比较横竖那个更大。
2. 要分类讨论。
3. 面积公式是长乘宽。

废话不多说，上代码！
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,k;
int main(){
	scanf("%lld %lld %lld",&n,&m,&k);//输入 
   if(k>n+m-2) cout<<"-1";//情况1 
	else if(k<m&&k<n) cout<<max(n*(m/(k+1)),m*(n/(k+1)));//情况2 
	else if(k<m&&k>=n) cout<<max(n*(m/(k+1)),m/(k-n+2));//情况3 
	else if(k>=m&&k<n) cout<<max(n/(k-m+2),m*(n/(k+1)));//情况4 
	else cout<<max(n/(k-m+2),m/(k-n+2));//情况5 
    return 0;//完结撒花 
}
//一定要有max比较每种情况中较大的，必然听取WA声一片 
```


---

## 作者：QuAckB33 (赞：1)

### 分析

先来考虑最多能切几刀。 横着切，最多 $n-1$ 刀；竖着切，最多 $m-1$ 刀，不用解释。所以如果 $k > n+m-2$， 输出肯定是 -1。

要让最小的一块最大，那就要尽可能平均分。于是接下来考虑四种情况：


------------


1.  $k<m$ 且 $k<n$ 

此时尽量平均分配的方法有两种，一是竖着一通切，二是横着一通切。

竖着切 k 刀，分成了 $k+1$ 段，每块宽为 n，长为  $\frac{m}{k+1}$，最小的一块的长只需要向下取整。横着切同理。最后取最大值。

------------

2. $k<m$ 且 $k>=n$

这会儿只能竖着一通切。

不过我们还可以先横着切成 $1 \times m$ 的条，再竖着切。

先横着切需要 $n-1$ 刀，那么还剩下 $k-(n-1)$ 刀， 能将 m 分成 $k-(n-1)+1$ 块，所以每一块长为 $\frac{m}{k-(n-1)+1}$ ，宽为 1。 也是取最大值。

------------

3. $k>=m$ 且 $k<n$

同 2。横竖交换。

------------

4. $k>=m$ 且 $k>=n$

先竖着或横着切成长或宽为 1 的块，再在另一个方向上切。和 2 的第二种情况一样。


------------
所以剩下就是算面积了…… 见代码吧。

~~应该没什么注释的必要了~~

~~以下是丑陋的代码~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,k;
int main(){
	cin>>n>>m>>k;
    if(k>n+m-2){
    	cout<<"-1";	return 0;
	} //切不了的情况
    //众所周知求面积是长乘宽
	if(k<m){
		if(k<n){
			cout<<max(n*(m/(k+1)),m*(n/(k+1)));	
		}//情况1
		else{
			cout<<max(n*(m/(k+1)),m/(k-n+2));
		}//情况2
	} 
	else{
		if(k<n){
			cout<<max(n/(k-m+2),m*(n/(k+1)));
		}//情况3
		else{
			cout<<max(n/(k-m+2),m/(k-n+2));
		}//情况4
	}
    return 0;
}
```


---

## 作者：qusia_MC (赞：0)

## 方法1
第一种就是，简化题意就是求 $\max_{i=1}^{\min(n,m)} \lfloor \frac{n}{i+1}\rfloor \times \lfloor \frac{m}{k-i+1}\rfloor(i\in \{x|1\le x\le k\})$

第二种思路，就是首先想到一个贪心，就是尽量“浪费”掉尽量多的刀数。

比如说现在的 $a$ 数组（就是沿着 $x$ 轴方向切成了 $5$ 块，每一块的长度）为 $1,2,2,2,2$，则不难发现，我们可以在后面四个二上各切一刀，这样最小值没有改变，刀数还少了。

不难想到：

- 若是沿着长切，则每 $1$ 单位长度就切一下，一直切完。

- 若是沿着宽切，也和长一样。

- 若切不完，剩下的沿着另一条边切。

在把沿着长、宽切各写一遍，取个最大值就行了。

---

## 作者：Nuclear_Fish_cyq (赞：0)

我们先考虑无解的情况。我们不可以切一个地方两次，所以我们最多只能竖着切切 $n-1$ 刀，横着切 $m-1$ 刀，总共 $n+m-2$ 刀。如果 $k>n+m-2$，那么就无解了。

首先我们可以注意到题目要使最小的一块最大，那么我们就需要尽量平均切。接下来我们设 $a$ 为竖着平均切的块数， $b$ 为横着平均切的块数。我们注意到总块数 $a\times b$ 越大，由于矩阵的面积固定，平均一块就越小。也就是说，为了使答案最大，我们需要使 $a\times b$ 取最小值。我们知道，$a+b=k+2$ 是定值，通过数学常识（好像这个法则在小奥里被称为“和定差大积小”？和基本不等式有一定关联），我们知道我们要使 $|a-b|$ 尽量大。然后考虑贪心。我们先尽量切横的，实在不行再切竖的，得到一个可能的答案，再把矩阵横竖交换，再执行前面的步骤，得到另一个可能的答案，最后取最大值。时间复杂度是 $O(1)$ 的。

最后还有几个细节：

1.注意开 `long long`。

2.面积公式是长乘宽。

3.刀数加一等于块数。

上代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
ll n, m, k, a, b, ans1, ans2;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	if(n + m - 2 < k){//无解 
		cout << -1 << endl;
		return 0;
	}
	//计算方案 
	if(k < n){
		a = k + 1;
		b = 1;
	}
	else{
		a = n;
		b = k - n + 2;
	}
	ans1 = n / a * m / b;
	swap(n, m);//横纵交换再算一遍
	if(k < n){
		a = k + 1;
		b = 1;
	}
	else{
		a = n;
		b = k - n + 2;
	}
	ans2 = n / a * m / b;
	cout << max(ans1, ans2) << endl;
	return 0;
}

```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出一个 $N \times M$ 的矩阵，给 $K$ 个操作，每次操作可以横/竖切割矩阵，求 $K$ 次切割，最大化最小块的面积.  
## $\text{Solution}$
显然要尽可能平均的切.  
那么答案就是 $\lfloor \dfrac{n}{x}\rfloor \times \lfloor \dfrac{m}{k+2-x}\rfloor$.  
$\lfloor \dfrac{n}{x}\rfloor$ 只有 $O(\sqrt n)$ 中取值，整除分块枚举这些值，然后贪心的让 $x$ 尽可能的大即可.  
需要开 longlong.  
细节上，当 $k+2-x\le0$ 时，要当成 $1$ 处理.

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1050;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
ll ans;
inline void check(int a){
  int b=k+2-a;
  if(b>m) return;
  if(b<=0) b=1;
  ans=max(ans,1ll*(n/a)*(m/b));
  return;
}
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();k=read();
  if(n+m<k+2){
    printf("-1");return 0;
  }
  for(int i=1;i<=n;){
    check(n/(n/i));i=n/(n/i)+1;
  }
  for(int i=1;i*i<=n;i++){
    if(n%i) continue;
    check(i);check(n/i);
  }
  printf("%lld\n",ans);
  return 0;
}
/*
3 3
tsy
*/

```


---

