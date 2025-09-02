# Buying Jewels

## 题目描述

[Nightwish feat. Jonsu - Erämaan Viimeinen](https://youtu.be/QYlFn5q_UQk)

ඞ



Alice has $ n $ coins and wants to shop at Bob's jewelry store. Today, although Bob has not set up the store yet, Bob wants to make sure Alice will buy exactly $ k $ jewels. To set up the store, Bob can erect at most $ 60 $ stalls (each containing an unlimited amount of jewels) and set the price per jewel for each stall to be an integer number of coins between $ 1 $ and $ 10^{18} $ .

Fortunately, Bob knows that Alice buys greedily: and she will go to stall $ 1 $ , buy as many jewels as possible, then go to stall $ 2 $ , buy as many jewels as possible, and so on until the last stall. Knowing this, Bob can choose the number of stalls to set up, as well as set the price for each stall so that Alice buys exactly $ k $ jewels. Help Bob fulfill the task, or determine if it is impossible to do so.

Note that Alice does not need to spend all her coins.

## 说明/提示

In the first test case, at the first stall, Alice buys $ 3 $ jewels and is left with $ 1 $ coin. This is not enough to buy any jewels for any of the remaining stalls, so Alice buys exactly $ 3 $ jewels at the end.

In the third test case,

- At the first stall, Alice buys $ 1 $ jewel and is left with $ 127 $ coins.
- At the second stall, Alice buys $ 1 $ jewel and is left with $ 63 $ coins.
- At the third stall, Alice buys $ 1 $ jewel and is left with $ 31 $ coins.
- At the fourth stall, Alice buys $ 1 $ jewel and is left with $ 15 $ coins.
- At the fifth stall, Alice buys $ 1 $ jewel and is left with $ 7 $ coins.
- At the sixth stall, Alice buys $ 1 $ jewel and is left with $ 3 $ coins.
- At the seventh stall, Alice buys $ 1 $ jewel and is left with $ 1 $ coin.
- At the eighth stall, Alice buys $ 1 $ jewel and is left with $ 0 $ coins.

 Therefore, Alice buys exactly $ 8 $ jewels in total.

## 样例 #1

### 输入

```
3
7 3
6 4
255 8```

### 输出

```
YES
10
2 3 4 5 6 7 8 9 10 11
NO
YES
8
128 64 32 16 8 4 2 1```

# 题解

## 作者：HHH6666666666 (赞：4)

名副其实的脑筋急转弯 ~~jiangly 做了半小时~~。

像这种构造没思路时赶紧小数据打表。把所有方案都看一遍就大概会了。

#### 若 $k>n$ 显然无解。

#### 若 $k=n$，显然设置一个 $1$ 即可。

#### 若 $\frac{n}{2}<k<n$ 则除了 $n=2k+1$ 的情况外均无解。

证明（没那么严谨）：

假设第一个柜台定价为 $p$，则购买 $\lfloor\frac{n}{p}\rfloor$ 次并剩 $n \bmod p$ 元。由 $n$ 元最多买 $n$ 次可得此时购买总数的上界为 $\lfloor\frac{n}{p}\rfloor+p$。根据对勾函数相关知识，这个式子的最值在两端，中间缓慢下降。观察两端最值发现除了 $p=2$ 且 $n$ 为奇时满足其为 $\lfloor\frac{n}{2}\rfloor+1$ 外$\lfloor\frac{n}{p}\rfloor+n \bmod p$ 均 $\le \frac{n}{2}$。

#### 剩下的情况：

第一个柜子定价 $n-k+1$，此时必有 $2(n-k+1)>n$ 所以必然会买一个剩 $k-1$ 元，第二个柜子放 $1$ 即可。

结束，就这么简单。

赛时被创飞了。

![](https://cdn.luogu.com.cn/upload/image_hosting/ra4wf48m.png)

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

void solve() {
    ll n, k; cin >> n >> k;
    if (n == k) {
        cout << "YES" << endl << 1 << endl << 1 << endl;
    }
    else if (k * 2 <= n) {
        cout << "YES" << endl << 2 << endl << n - k + 1 << ' ' << 1 << endl;
    }
    else if ((n & 1) && 2 * k - 1 == n) {
        cout << "YES" << endl << 2 << endl << 2 << ' ' << 1 << endl;
    }
    else cout << "NO" << endl;
    return;
}

signed main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：Day_Tao (赞：2)

### 题目大意

Alice 有 $n$ 元钱，要去买 $k$ 个物品，而买的顺序是从第一个开始买（每个物品有无限件），一直买同一个物品直到手中的钱不够买这个物品，再考虑下一个物品。要求构造一组数据，满足按照这样的购买顺序能够刚好买 $k$ 件。

有 $t(1\le t\le 1000)$ 组数据，每组数据给出 $n,k(1\le n,k\le1\times 10^{18})$。

对于每个测试样例，输出第一行为 YES 或 NO，如果是 YES 则第二行为构造物品数量 $s(1\le s\le60)$，第三行有 $s$ 个数 $p_1,p_2,\dots,p_s$，表示物品价格及顺序。

### Sol

看到这个题的数据范围，肯定是找规律构造题。首先可以发现，对于价格为 $1$ 的物品，Alice 一定会把她所有的钱都砸下去，然后买到当前剩余钱数的物品。所以我们只需要想办法让 Alice 先花费 $n-k+1$ 的钱买一个物品，然后再去买 $k-1$ 的价格为 $1$ 的物品。当然，这也需要保证 $k-1< n-k+1$，即 $k\times2 -2<n$，不然她仍会选择买第一件物品。

那对于 $k\times2 -2\ge n$ 的情况呢？答案是除了 $n=k$ 以外其他都无解。来考虑只有两个物品的情况。

首先考虑如果第一件买两次，第二件仍是价值为 $1$ 的，那么第一件的数量 $\times$ 价格就是 $2\times \frac{n-k+2}{2}$，第二件的数量 $\times$ 价格就是 $(k - 2)\times 1$。这种情况要想成立则必须保证 $k-2< \frac{n-k+2}{2}$，不然留下来买第二件的钱就会在买第一件的时候花去一部分，导致买不到这个数量。化简得 $3\times k-6< n$，即 $3\times(k-1)< n$。

然后考虑如果第一件买一次，而第二件价值为 $2$，那么第一件的数量 $\times$ 价格就是 $1\times (n-2\times k+2)$，第二件的数量 $\times$ 价格就是 $(k - 1)\times 2$。这种情况要想成立则必须保证 $(k-1)\times 2< n-2\times k+2$，化简得 $4\times k-4\le n$，即 $4\times(k-1)\le n$。

可以发现，这两种情况 $k$ 的解集是包含于第一种买一次，第二种价格为 $1$ 的方案，所以说肯定是这个方案更优的。

对于两种以上的商品，其实就是将我上面所说的第一件拆成几件来看。而对于第一件买多个，第二件价格为更大的情况也可以通过我刚刚的证明推得，这就留给读者自己思考啦。

### Code
```
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long // 不开long long见祖宗
const int MAX = 2e5 + 5;
const int INF = 0x7fffffff;
const int mod = 998244353;
int T, n, k;
signed main()
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld%lld", &n, &k); // 不写 %lld 也要见祖宗
		if (n == k)//特判一下
			printf("YES\n1\n1\n");
		else if (k * 2 - 2 < n)
			printf("YES\n2\n%lld 1\n", n - k + 1);
		else
			printf("NO\n");
	}
	return 0;
}
```
---
### END

---

## 作者：Karl_Aldrich (赞：1)

### 题目大意
Alice 有 $n$ 个硬币，想要在 Bob 的珠宝店购物。Bob 希望确保 Alice 会购买恰好 $k$ 件珠宝。问 Bob 该如何设置摊位的个数与每个摊位的价格。

附：Alice 在每个摊位会购买尽量多的宝石。

### 思路
数学问题。

考虑特殊情况：如果 $n < k$，显然无法达成目标，如果 $n = k$，显然可以达成目标（开设一个商铺，此商铺每个宝石的价格为 $1$ 元即可）。

然后考虑其他情况。

对于第一个摊位一定有 $p_1 \ge 2$，假设 Alice 在第一个摊位购买了 $q$ 个珠宝，且 $q \ge 1$，$0 \le r < p_1$，则一定有 $n = p1 \times q + r$，其中 $r$ 为后续摊位所购买的全部珠宝数量。显然，Alice 最多购买 $q + r$ 个珠宝。

则有：

$n - 2(q+r) = (p_1 - 2)q - r$

$n - 2(q+r) \geq (p_1 - 2)q - p_1 + 1$（因为 $r \leq p_1 - 1$）

$n - 2(q+r) \geq (p_1 - 2) - p_1 + 1$（因为 $q \geq 1, p_1 \geq 2$）

得到：$n - 2(q+r) = -1$。

可得：$2(q+r) \leq n + 1$。

也就是说，如果 $n < k$ 并且 $2k > n + 1$，则一定不能实现目标。否则总会有 $p_1 = n - k + 1$ 与 $p_2 = 1$ 可以满足要求。

---

## 作者：kimidonatsu (赞：1)

容易想到设置 $\lfloor \dfrac{n}{k} \rfloor$ 的一个摊位，通过确定剩下的钱能否搞到一个新的货品的思路，然后在 system test 的 case 4 会吃到这个数据炸掉：

```
999999999999999995 499999999999999998
```

---

转换思路，考虑贪心。

注意到 Alice **并不需要花光所有钱**，对于这种比较复杂的边界情况我们要考虑简化条件，这里我们尝试让 Alice 只能买一个货品。

那么对于第一个摊位，Alice 花费的金额就是 $(n - k) + 1$，也就是钱刚好购买一个物品，剩下的差 $k - 1$ 元。显然，Alice 只剩下 $n - (n - k + 1) = k - 1$ 元，只要我们让第二个货摊的价格变为 $1$，Alice 就能刚好收获 $1 + \dfrac{k - 1}{1} = 1 + k - 1 = k$ 件物品了。

无解的情况随之呼出：当 $k \lt n$ 且 $2 \times k \gt n + 1$ 时，$k \gt \dfrac{n + 1}{2}$，构造方法会失效。

[Submission](https://codeforces.com/contest/1951/submission/260526252)

---

## 作者：Brute_Force (赞：1)

### 题意
爱丽丝有 $n$ 硬币，想在鲍勃的珠宝店购物。今天，虽然鲍勃还没有建立商店，但是鲍勃希望确保爱丽丝将购买确切的 $k$ 珠宝。为了建立商店，鲍勃最多可以建立 $60$ 个摊位（每个摊位包含无限数量的珠宝），并将每个摊位的每件珠宝的价格设置为 $1$ 到 $10^{18}$ 之间的整数个硬币。

幸运的是，鲍勃知道爱丽丝买东西很贪婪：她会去 $1$ 号摊位，买尽可能多的珠宝，然后去 $2$ 号摊位，买尽量多的珠宝，如此类推，直到最后一个摊位。知道了这一点，鲍勃可以选择要设置的摊位数量，以及设置每个摊位的价格，这样爱丽丝就可以准确地购买 $k$ 珠宝。帮助鲍勃完成任务，或确定是否不可能这样做。

**请注意，爱丽丝不需要花掉她所有的硬币。**

### 思路
一道贪心题，我们要想方法构造。

首先，既然要爱丽丝准确买 $k$ 珠宝，那么就需要她的钱足够。由此，可以发现 $n < k$ 是无解的。

其次，当 $n = k$ 时，显然有解，只开 $1$ 个店铺，每个珠宝价格为 $1$ 元，完成构造。

最后的情况是最为关键的，如果爱丽丝在第 $1$ 个店铺中买了 $x$ 个珠宝，则剩下爱丽丝买的珠宝为 $k - x$，则必须满足式子 $n = a_{1} \times x + k - x$。
则：
$$n - 2  \times (x + k - x) = (a_1 - 2) \times x - k + x$$

好了，进行化简吧！可得 $2 \times k > n + 1$ 时不能实现构造。其他情况 $2$、$n - k + 1$ 和 $1$ 可以构造出解。

于是便有：
+ 当 $n = k$ 时，有解，且只有一种解 $1$ 和 $1$ 能构造出解。

+ 当 $k \times 2 - 2 < n$ 时，有解，且由 $2$、$n - k + 1$ 和 $1$ 可以构造出解。

+ 其余情况无解。

**数据过大，请开 `long long`。**
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long T, n, k;
int main () {
	cin >> T;
	while (T--) {
		cin >> n >> k;
		if (n == k) printf ("YES\n1\n1\n");
		else if (k * 2 - 2 < n || n < k) printf ("YES\n2\n%lld 1\n", n - k + 1);
		else printf ("NO\n");
	}
	return 0;
}
```
注：这篇题解是我改变码风的第一篇题解

---

## 作者：yingjingxu_NaS2O3 (赞：0)

## 分析

考虑分类讨论。

1. $k>n$

我们注意到所有 $p_i\ge 1$，所以想要买 $k$ 件商品，需要硬币数

$$C=a_1p_1+a_2p_2+\dots+a_mp_m$$

其中 $a_1=\lfloor \frac{n}{p_1}\rfloor$，$a_2=\lfloor\frac{n-a_1p_1}{p_2}\rfloor$，依此类推，

$$a_m=\lfloor \frac{n-\sum\limits_{i=1}^{m-1}a_ip_i}{p_m}\rfloor$$

其中

$$\sum\limits_{i=1}^{m}a_i=k$$

我们注意到

$$C=a_1p_1+a_2p_2+\dots+a_mp_m \ge \sum\limits_{i=1}^{m}a_i = k > n$$

所以无解。

2. $k=n$

同上，我们注意到

$$C=a_1p_1+a_2p_2+\dots+a_mp_m \ge \sum\limits_{i=1}^{m}a_i = k = n$$

当 $a_1p_1+a_2p_2+\dots+a_mp_m = \sum\limits_{i=1}^{m}a_i$ 时，我们发现 $p_1=p_2=\dots=p_m=1$，同时，由于 $a_1=\lfloor\frac{n}{p_1}\rfloor$，所以 $m=1$。

于是我们可以构造出数列：

$$1$$

该数列即为所求答案。

3. $\lfloor\frac{n}{2}\rfloor < k < n$

当 $2k=n+1$ 时，我们可以构造出数列：

$$k,1$$

在此区间内的其余情况均无解，其他题解已经证明，在此不赘述。

4. $k=\lfloor\frac{n}{2}\rfloor$

此时 $n=2k$ 或 $n=2k+1$。

故此时我们可以构造出数列：

$$2$$

5. $k<\lfloor\frac{n}{2}\rfloor$

此时我们不妨令

$$n=n-k+1+k-1=1\times(n-k+1)+(k-1)\times 1$$

所以我们可以构造出数列：

$$n+k-1,1$$

## 最终代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		if(k>n)
		{
			printf("NO\n");
			continue;
		}
		if(k==n)
		{
			printf("YES\n1\n1\n");
			continue;
		}
		if(k==n/2)
		{
			printf("YES\n1\n2\n");
			continue; 
		}
		if(2*k==n+1)
		{
			printf("YES\n2\n%lld 1\n",k);
			continue;
		}
		if(k>n/2&&k<n)
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n2\n%lld 1\n",n-k+1);
	}
	return 0;
}
```

---

## 作者：sea_bird (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1951D)。

# 题目大意

用不超过 $n$ 元钱买正好 $k$ 个商品，如果钱还足够就得一直购买这个商品，判断是否能满足，如果可以就输出满足条件的这个序列。

# 题目分析

这道题的关键是如何正好能满足，因为如果钱还够就得继续买，所以这成了一个问题。首先来看看 `cout<<"NO"<<endl;` 的情况，因为定价不能是小数所以很容易就能发现，当 $n<k$ 时就不符合条件，还有一种特殊的，就是 $n=k$ 时，这样只要用所有的钱去买就能做到。如果说像第三点这样的正常样例来讲，就是让 Alice 花费到只剩用一元满足的情况，第一点可以用 `5 1` 也行（买两次三元的一次一元的）题目说输出任何一个符合条件的方案，所以只要结果是符合的就行。至于何时 `cout<<"NO"<<endl`，只需看所设置**用来消耗到只剩一的那个数**，用来除 $n$ 是否大于 $1$（那个数一定不大于 $n$）。接下来就是用代码实现了。

## Code

```cpp
#include<bits/stdc++.h>

using namespace std;
void ans(unsigned long long a,unsigned long long b){
	if(a<b){
		cout<<"NO"<<endl;
		return;
	}
	else if(a==b){
		cout<<"YES"<<endl;
		cout<<1<<endl;	
		cout<<1<<endl;
		return;
	}
	else{
		if(a/(a-b+1)!=1){
			cout<<"NO"<<endl;
			return;
		}
		else{
			cout<<"YES"<<endl;
			cout<<2<<endl;
			cout<<a-b+1<<" "<<1<<endl;
			return;
		}
		
	}
}
int main(){
  	ios::sync_with_stdio(0);//在C++中关闭输入输出流的同步,提高程序的执行效率
	unsigned long long t;
	unsigned long long n,k;
	cin>>t;
	while(t--){
		cin>>n>>k;
		ans(n,k);
	}
	return 0;
}
```

关于这段代码我要说几句：
- 由于 [Codeforces RemoteJudge 暂不可用](https://www.luogu.com.cn/discuss/598533)。所以我是找别人帮忙交的，在此感谢。
- 一定要开 `long long`。

---

## 作者：naroto2022 (赞：0)

# CF1951D 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1951D)

### 题意

题意翻译成数学语言大概是这样的：

给定 $n,k(1\leqslant n,k\leqslant 10^{18})$，构造一个长度不超过 $60$ 的正整数序列 $a_1,a_2,a_3,\cdots,a_n$，记 $b_0=n,c_i=\lfloor\frac{b_{i-1}}{a_i}\rfloor,b_i=b_{i-1}\bmod a_i$，序列 $c$ 满足 $\begin{aligned}\sum_{i=1}^{m}c_i=k\end{aligned}$。若有合法解请输出 `YES` 及其中一种，否则输出 `NO`。

### 思路

这题真的很想说一句是一个诈骗题，看到 $60$ 自然地想到了二进制，后来发现好像似乎只要输出两个数字，犹豫的提交一下就过了……没 $60$ 啥事情！

首先，分四种情况：

1. $k>n$，显然无解。
2. $k=n$，这个也很显然，直接摆一个商品为 $1$ 的价格即可。
3. $k\leqslant \lceil\frac{n}{2}\rceil$，这个就需要点小头脑构造了，首先 $a_1=n-k+1$，则 $c_1=\frac{b_0}{a_1}=\frac{n}{n-k+1}=1$，而 $b_1=b_0\bmod a_1=k-1$，接下来 $a_2=1,c_2=k-1,c_1+c_2=k$ 解决！
4. 对于剩下的 $k>\lceil\frac{n}{2}\rceil$ 的情况，是可以证明无解的。

证明：首先要是第一个人商品不为 $1$ 要买最多的物品数肯定第一个商品价格为 $2$。接下来分类讨论两种情况：

1. $n$ 是偶数，则最终选出来的物品数最多为 $\frac{n}{2}\leqslant\lceil\frac{n}{2}\rceil$。
2. $n$ 是奇数，则最终选出来的物品数最多为 $\frac{n}{2}+1\leqslant\lceil\frac{n}{2}\rceil$。

综上，当 $k>\lceil\frac{n}{2}\rceil$ 时无解。

所以，快去打代码过了这道题吧~

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll T,n,k; 
void write(ll n){if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
int main(){
	T=read();while(T--){
		n=read();k=read();
		if(n==k) printf("YES\n1\n1\n");
		else if(k<=(n+1)/2) printf("YES\n2\n%lld 1\n",n-k+1);
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：fujiayu (赞：0)

# CF1951D - Buying Jewels 题解

[原题地址](http://codeforces.com/problemset/problem/1951/D)

## 题意：

Alice 有 $n$ 元钱，Bob 要卖最多 $60$ 件物品，Alice 在购买时会直接买到不能再买为止，问能否构造物品的定价方案，使 Alice 恰好购买 $k$ 件物品。

## 思路：

贪心。

我们可以先让 Alice 花去 $n-k+1$ 元购买一件物品 $a$，再让 Alice 以 $1$ 元的单价购买 $k-1$ 件物品 $b$。

在这个过程中，我们还要保证 Alice 不会买到超过一件物品 $a$，所以还要满足 $n<2(n-k+1)$，整理得 $k\le\left\lfloor \frac{n}{2} \right\rfloor+1$，再特殊判断 $n=k$ 的情况即可。

证明：当 $k>\left\lfloor \frac{n}{2} \right\rfloor+1$ 且 $n\ne k$ 时，如果 $a=2$，则最终购买的物品数一定 $\le\left\lfloor \frac{n}{2} \right\rfloor+1$，且随着 $a$ 的增大而减小，所以 $a$ 必须 $<2$，否则无法达到 $k$，而 $a=1$ 显然无法满足题意，所以当 $k>\left\lfloor \frac{n}{2} \right\rfloor+1$ 且 $n\ne k$ 时一定无解。

综上所述，

- 当 $n=k$ 时，$a=1$
  
- 当 $k>\left\lfloor \frac{n}{2} \right\rfloor+1$ 且 $n\ne k$ 时，无解。
  
- 否则，$a=n-k+1$，$b=1$
  

时间复杂度：$\Theta(T)$

## 代码：

```cpp
#pragma gcc optimize(2)
#include<iostream>
#define int long long
using namespace std;

int n, k;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T --)
	{
		cin >> n >> k;
		if(n == k)
			cout << "YES\n1\n1\n";
		else if((n + 1) / 2 < k)
			cout << "NO\n";
		else
			cout << "YES\n2\n", 
			cout << n - k + 1 << " 1\n";
	}
	return 0;
}
```

---

