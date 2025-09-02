# [ABC290D] Marking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc290/tasks/abc290_d

$ 0 $ から $ N-1 $ までの番号がつけられた $ N $ 個のマスが並んでいます。 今から、すぬけくんが以下の手順に従って全てのマスに印をつけていきます。

1. マス $ 0 $ に印をつける。
2. 次の i - iii の手順を $ N−1 $ 回繰り返す。 
  1. 最後に印をつけたマスの番号を $ A $ としたとき、変数 $ x $ を $ (A+D)\ \bmod\ N $ で初期化する。
  2. マス $ x $ に印が付いている限り、 $ x $ を $ (x+1)\ \bmod\ N $ に更新することを繰り返す。
  3. マス $ x $ に印をつける。

すぬけくんが $ K $ 番目に印をつけるマスの番号を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ T\ \leq\ 10^5 $
- $ 1\leq\ K\leq\ N\ \leq\ 10^9 $
- $ 1\leq\ D\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ N=4,D=2 $ のとき、すぬけくんは以下のように印をつけていきます。 1. マス $ 0 $ に印をつける。 2. (1回目) $ x=(0+2)\bmod\ 4=2 $ と初期化する。マス $ 2 $ は印がついていないので、印をつける。 (2回目) $ x=(2+2)\bmod\ 4=0 $ と初期化する。マス $ 0 $ は印がついているので、$ x=(0+1)\bmod\ 4=1 $ と更新する。マス $ 1 $ は印がついていないので、印をつける。 (3回目) $ x=(1+2)\bmod\ 4=3 $ と初期化する。マス $ 3 $ は印がついていないので、印をつける。

## 样例 #1

### 输入

```
9
4 2 1
4 2 2
4 2 3
4 2 4
5 8 1
5 8 2
5 8 3
5 8 4
5 8 5```

### 输出

```
0
2
1
3
0
3
1
4
2```

# 题解

## 作者：yemuzhe (赞：5)

### 简化题意

- 有一个变量 $x$，刚开始 $x _ 1 = 0$。
- 每次令 $x _ i = (x _ {i - 1} + D) \bmod N$（$2 \le i \le N$），如果 $x _ i$ 在之前的 $x _ 1 \sim x _ {i - 1}$ 已经出现过了，就一直令 $x _ i = (x _ i + 1) \bmod N$，直到 $x$ 在之前的 $x _ 1 \sim x _ {i - 1}$ 中未出现过。

- 题目要求 $x _ k$ 的值。
- 有 $T$ 组数据，$1 \le T \le 10 ^ 5$，$1 \le k \le N \le 10 ^ 9$，$1 \le D \le 10 ^ 9$。

### 解题思路

容易发现，当 $N, D$ 互质时，$x _ i = (i - 1) D \bmod N$。

否则设 $\gcd (N, D)$ 为 $g$，则如果不考虑 $x _ i$ 之前出现过的话，$x _ 1 \sim x _ n$ 共有 $g$ 个循环周期，且 $x _ i = (i - 1) D \bmod N$。

如当 $N = 12, D = 9$ 时，不考虑 $x _ i$ 之前出现过，$x _ {1 \sim N} = [0, 9, 6, 3, 0, 9, 6, 3, 0, 9, 6, 3]$。

如果考虑 $x _ i$ 之前出现过要进行 $x _ i = (x _ i + 1) \bmod N$ 的话，$[x _ 1, x _ 2, \cdots, x _ {N / g}] = [x _ {N / g + 1} - 1, x _ {N / g + 2} - 1, \cdots, x _ {2(N / g)} - 1] = \cdots$。

如当 $N = 12, D = 9$ 时，$x _ {1 \sim N} = [0, 9, 6, 3, 1, 10, 7, 4, 2, 11, 8, 5]$（可四个数为一组断开观察）。

这样，我们可以把 $x _ 1 \sim x _ N$ 分为 $g$ 组，每组 $N \over g$ 个数。

记 $t$ 为 $x _ k$ 所在组的编号（编号从 $0$ 到 $g - 1$），则容易得到 $t = \Big \lfloor {k - 1 \over N / g} \Big \rfloor$。$x _ k$ 则为 $[(k - 1)D + t] \bmod N$。

### AC Code

```cpp
#include <cstdio>
using namespace std;

int T, n, d, k, g, t;

int gcd (int a, int b)
{
    return b ? gcd (b, a % b) : a;
}

int main ()
{
    scanf ("%d", &T);
    while (T --)
    {
        scanf ("%d%d%d", &n, &d, &k);
        g = gcd (n, d), t = (k - 1) / (n / g);
        printf ("%d\n", ((k - 1ll) * d + t) % n);
    }
    return 0;
}
```

---

## 作者：_qingshu_ (赞：4)

# 题意：

有一个环，环上的点编号为 $0\sim n-1$。现在进行如下操作。

- 选择 0 号格子，标记它。

- 选择上一个选择的格子 $d$ 个格子后第一个还没有打上标记的格子，将其标记。

- 重复以上动作直至所有格子全部都打上标记。

询问第 $k$ 次标记的格子编号。

# 思路：

首先，易证当 $n$ 与 $d$ 互质的时候，$(d\times x)\bmod n$ 的取值是不会有重复的，其中 $ (0\le x \le k)$。

再考虑 $\gcd(n,d)\ne 1$ 的时候，如果不考虑现在预选择的格子已经被标记过的情况，一共可以分为 $\gcd(n,d)$ 组，循环节长度为 $n\div \gcd(n,d)$。再考虑如果出现重复的选择，每一次至少都会跳 $d$ 个，如果出现了重复，我们的选择的位置会再预选位置上 $+1$，继而我们会选择的位置都是上一轮选的位置的下一个，就一定不会出现预选位置 $+2$ 的情况，唯一出现的地方在于全部都选完了，这是不需要考虑的。

这样，每一个循环节内都会再第一个的基础上加上所在循环节编号（从 $0$ 开始），那么可求公式。

$$ans=(k\times d+k\div (n\div \gcd(n,d)))\bmod n$$

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,d,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>d>>k;k--;
		cout<<(k*d+k/(n/__gcd(n,d)))%n<<endl;
	}
}
```

update：

- 修改了取模运算。

---

## 作者：kczw (赞：3)

# 题意
一个长度为 $n$ 由 $0$ 到 $n-1$ 的数组成的环，从 $0$ 开始标记，以后每隔 $d$ 个数标记一个数，如果要被标记的数已被标记，再继续隔 $1$ 个单位标记，问第 $k$ 个被标记的数。
# 思路
看到 $T$ 组多测并且 $T\le10^5$，而且对于每一个测试点 $1\le k\le n\le10^9,1\le d\le 10^9$，不难猜到，这是一道结论题。那我们来稍微分析一下：

将这个环拆成链，然后将 $n$ 条链连接到一起。易得每隔只有 $n$ 个数标记的数是一样的，所以也只有当每次隔 $d$ 隔到相隔的总距离是 $n$ 的倍数时才会重复，而这个隔的总距离最小就是 $n$ 和 $d$ 的最小公倍数。

所以当 $n$ 和 $d$ 互质也就是 $\gcd(n,d)=1$ 时，只有隔了 $n\times d$ 个数才会取重，也就是只有取了大于 $n$ 个数才会取重，所以可得到公式：

- $ans=(k\times d)\bmod n$

同时当 $n$ 和 $d$ 不互质时，每隔 $n\times d\div\gcd(n,d)$ 也就是 $n$ 和 $d$ 的最小公倍数隔个数后会取重，并且此时需要额外隔一个数，所以可以得到公式。

- $ans=(k\times d+k\times d\div(n\times d\div\gcd(n,d)))\bmod n$

最后合并两个公式
 
- $ans=(k\times d+k\div n \times \gcd(n,d))\bmod n$

以下是手写的 gcd 函数，函数库的也可以。
```cpp
inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
```

---

## 作者：徐晨轩✅ (赞：2)

## 题目大意

* 一个 $1 \times n$ 的长方形，划分为 $1 \times 1$ 的小格。（序号从 $0$ 编号）

* 执行如下操作：

  * 在第 $0$ 个格子放一个棋子，并令 $pos=0$。
  
  * 执行如下操作 $k-1$ 次：
  
    * 令 $w=(pos+d)\mod n$，让 $w$ 不断赋值为 $(w+1)\mod n$，直到第 $w$ 个格子没有放棋子。
    
    * 在第 $w$ 个格子放一个棋子。

* 问最后一个棋子放的位置。

## 解法

尝试一下，可以发现：对于 $\gcd(n,d)=1$ 的情况，每次都不会往后找（即每次放的地方都是空的）。这种情况的答案就非常显然了（即 $(k-1)\times d$）。

但是，如果 $\gcd(n,d) \ne 1$，就会比较复杂。

给一组数据 $n=6, d=4$：

![](https://cdn.luogu.com.cn/upload/image_hosting/h6357w9s.png)

我们将 $(0,2,4)$ 分为一组（表示为 $a$），剩下的 $(1,3,5)$ 分为另一组（表示为 $b$）。$(1,4,3,6,2,5)$，即放棋子的时间戳，表示为 $v$。可以发现：

$$v_{b_i} = v_{a_i} + 3 = v_{a_i} + \dfrac{n}{\gcd(n,d)} (1 \le i \le 3)$$

$$b_i = a_i + 1 (1 \le i \le 3)$$

于是猜想：对于任意的 $n, d$，都满足此式。经过模拟其他样例，发现成立。这样，我们就只要算出 $k$ 在哪一组里，就完了。这个就很简单了，可以对照代码理解。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, n, d, k;
int rptTimes, rptPeriod, rptIn;

signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> d >> k;
        d %= n;
        rptTimes = __gcd(n, d); // 组的个数
        rptPeriod = n / rptTimes; // 每组元素个数
        rptIn = (k + rptPeriod - 1) / rptPeriod; // 在哪一个组里
        k -= (rptIn - 1) * rptPeriod; // 减掉不在当前组里的棋子编号
        cout << (rptIn - 1 + (k - 1) * d) % n << endl; // 加上这个组里的棋子
    }
    return 0;
}

```

---

## 作者：六楼溜刘 (赞：2)

本题解适合（和我一样）pj2=水平的选手参考

2023/2/21 Update：修正一点错误,感谢 [liyijin](https://www.luogu.com.cn/user/431349) 指出错误。

2023/2/22 Update：修改了一些笔误和 $\LaTeX$ 使用不当。

2023/2/27 Update：修改了部分中英文间少空格。
### 题意
你要按一个特殊的顺序将一个长度为 $n$，初始全为 $0$ 的 $01$ 序列 $a_0,a_1,\dots,a_{n-1}$ 依次改为 $1$。

1. 第一次将 $a_0$ 改为 $1$。
1. 重复执行以下步骤 $n-1$ 次。
	- 将上一次修改的位置记为 $A$。
	- 记 $x=(A+d) \bmod n$。
	- 若 $a_x=0$ 修改 $a_{x}$。
   - 若 $a_x=1$ 重复执行 $x=(x+1)\bmod n$ 直到 $a_x = 0$，修改 $a_x$。

现在你想知道第 $K$ 次修改的元素的下标是多少。
### 题解
这道题一看就是找规律，我们先写一个小程序打表，输出每次修改的位置构成的序列。
```cpp
//参考代码
	int n,d,ans[20];
	scanf(" %d %d",&n,&d);
	int j=-d;
	for(int i=1;i<=n;i++){
		j=(j+d)%n;
		while(ans[j]!=0) j=(j+1)%n;
		ans[j]=i;
		printf("%d ",j);
	}
```
我们自己准备几组数据跑一下，
```
//数据1
20 7
0 7 14 1 8 15 2 9 16 3 10 17 4 11 18 5 12 19 6 13
//数据2
10 4
0 4 8 2 6 1 5 9 3 7
..数据3
10 5
0 5 1 6 2 7 3 8 4 9
```
记第 $i$ 次修改的元素下标为 $w_i$，容易发现以下规律：
> - （由数据1可推）若 $\forall 0 \leq j \leq i ,(j \times d)\bmod n \ne 0$，则 $w_i = ((i-1) \times d )\bmod n$。
$$\Downarrow$$
> - （由数据2可推）若存在且仅存在一个 $j$，满足 $0 \leq j \leq i ,(j \times d)\bmod n = 0$，则 $w_i = ((i-1) \times d )\bmod n +1$。
$$\Downarrow$$
> - （由数据3可推）若存在 $p$ 个 $j$，满足 $0 \leq j \leq i ,(j \times d)\bmod n = 0$，则 $w_i = ((i-1) \times d )\bmod n + p$。

并且这也十分好理解，如果第 $i$ 次前自始至终都没有标记 $n$ 的倍数，那么必定每次 $a_{(A+d) \bmod n}=0$ 都成立，不会出现需要移动的情况，反之，如果标记到 $n$ 的倍数，那么必定需要往后移动一位，并且后续标记都会往后移动一位。

那么问题就转化成了如何求 $p$。

数学知识告诉我们，$a$ 和 $b$ 的最小公倍数等于 $\frac{a \times b}{\gcd(a,b)}$。所以，$b$ 的 $\frac{a \times k}{\gcd(a,b)}\,(k \in N)$ 倍是 $a$ 和 $b$ 的公倍数。

容易发现 $p$ 其实就是在集合 $\{j \times d \,|\, 0\leq j \leq K-1\}$ 中，$n$ 的倍数的个数。

即满足 $0 \leq j \leq K-1, j = \frac{n}{\gcd(d,n)} \times k\,(k \in N)$ 的 $j$ 的个数。

即：
$$p=\left\lfloor \dfrac{K-1}{\frac{n}{\gcd(d,n)}} \right\rfloor$$
故最终的答案为：
$$((K-1) \times d )\bmod n+\left\lfloor \dfrac{K-1}{\frac{n}{\gcd(d,n)}} \right\rfloor$$
### code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
 
#define int long long
 
using namespace std;
 
int t,n,k,d;
 
int gcd(int a,int b){//由于我怕栈溢出我用的迭代写法，递归写法应该是能过的
	while(b!=0){
		int c=b;
		b=a%b;a=c;
	}
	return a;
}
 
signed main(){
	scanf(" %lld",&t);
	while(t--){
		scanf(" %lld %lld %lld",&n,&d,&k);
		printf("%lld\n",(d*(k-1))%n+(k-1)/(n/gcd(n,d)));
	}
}
```

---

## 作者：ダ月 (赞：2)

### 题意概要：
多组询问。给定 $n$ 个物品，分别以 $0,1,2,\dots,(n-1)$ 进行编号。现从第编号为 $0$ 物品开始打标记。若当前打标记的物品编号为 $x$，那么给 $(x+d)\bmod n $ 的物品打编号。若当前的物品已经打上编号，则给下一个没打编号的物品打上编号。求第 $k$ 次打上编号的物品的编号。

### 题目分析：

我们定义一个循环为这个循环内打到已经打上编号的物品为止。

有 $n$ 个物品，隔 $d$ 个距离打标记，那么一个循环内的元素有 $\frac{n}{\gcd(n,d)}$ 个。

所以我们只需要统计每一个循环内的元素个数 $x$，$k$ 步时已经跳了的完整循环数 $y$，$k$ 步时最后一个不完整的循环内的元素个数 $z$。答案就是 $y+(z\times d\bmod n)$。

### 代码如下：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll x,ll y){
	if(x<y) swap(x,y);
	return !y?x:gcd(y,x%y);
}
int T;
ll n,d,k;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&d,&k);k--;d%=n;
      		/*注意到上文第k步都是从0开始记的，而题目是从1开始记，所以要减去1*/
		ll p=gcd(n,d);
		ll c=n/p;/*c就是上面的x*/
		ll e=k/c;/*e就是上面的y*/
		ll f=k%c;/*f就是上面的z*/
		printf("%lld\n",e+f*d%n);
	}return 0;
}
```

时间复杂度：$O(T\log n)$。

---

## 作者：lsj2009 (赞：2)

## Solution

引理：每执行 $\frac{n}{\gcd(n,d)}$ 次 $x\gets(x+d)\bmod{n}$ 就执行一次 $x\gets(x+1)\bmod n$。

- 证明：显然第 $i$ 次到第 $i+1$ 次和第 $i+1$ 次到第 $i+2$ 次执行 $\text{ii}$ 操作之间所执行的 $\text{i}$ 操作时一定的，因为所有操作的下标集体向右挪了一位，同时重复的那次一定是这一轮开始的那一次，因为所有的遍历过的下标都是开始位置加上 $d$ 的若干倍在模 $n$ 意义下的值，即为在模意义下减开始的数后均为 $d$ 的倍数，所以如果要在遍历中重合点 $x$，必将先重合点 $x-d$，所以通过反证法可得；所以我们只需要算出第一次执行操作 $\text{ii}$ 时共执行了几次 $\text{i}$。那么这也就相当于找到一个最小的数 $a$ 使得 $n\mid ad$，那不妨先考虑令 $a\gets n$，然后进行约分，得 $ad=n\frac{d}{\gcd(n,d)}$，得 $d=\frac{n}{\gcd(n,d)}$。

然后接下来就简单了，直接算出第 $k$ 次已经重合了几次（即第 $k$ 轮的开头），和当前时第 $k$ 轮的第几个。

然后就做完了。

## Code

正解：<https://atcoder.jp/contests/abc290/submissions/39026820>。

---

## 作者：Crazyouth (赞：1)

**翻译**

给你正整数 $n,d,k$。你的任务是标记数，按如下方法标记：
1. 第一步标记 $0$。
2. 如果上一个标记的数是 $a$，标记 $(a+d)\bmod n$，如果这个数被标记过了，标记 $(a+d+1)\bmod n$，如果依然被标记过了，继续标记下一个数，直到它没有被标记过。
3. 如果 $0$ 到 $n-1$ 都被标记了，停止；否则重复步骤 $2$。

求第 $k$ 次标记的是什么数。

**分析**

看这题数据范围，就知道只能是 $O(t)$ 的，也就是说对于每一组数据，都必须是 $O(1)$ 的，说明这是数学题。

首先很明显，如果 $k$ 是 $1$，直接输出 $0$ 即可。

正常情况下，第 $k$ 次标记的数应该就是 $((k-1)\times d)\bmod n$，但是有些情况会往前进位。那么“正常情况”是什么呢？很容易想到，那就是 $\gcd(n,d\bmod n)=1$ 时。

遇到非“正常情况”应该怎么办呢？易发现，除了那个特殊的 “$0$” 以外，加一情况是有规律地出现的，这时我们就可以计算它的循环节，也就是多少个数会出现一次加一。易知，出现加一情况的次数一共是 $n\div \gcd(n,d\bmod n)$。我们先算出 $((k-1)\times d)\bmod n$，再给输出的答案加上这个循环节数量就行了。

**AC Code**
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long t,n,d,k,tp,xhj;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		tp=0;
		cin>>n>>d>>k;
		if(d%n==0)//如果d是n的倍数，那明显就是一个一个加的
		{
			cout<<k-1<<endl;
			continue;
			
		}
		if(k==1)//特判k=1
		{
			cout<<0<<endl;
			continue;
		}
		if(__gcd(n,d%n)==1)//判断是不是“正常情况”
		{
			tp=((k-1)*d)%n;
			cout<<tp<<endl;
			continue;
		}
		xhj=n/__gcd(n,d%n);//统计循环节
		tp+=(k+xhj-1)/xhj-1;//答案加上循环节数量
		tp+=((k-1)*d)%n;//加上k-1个d
		cout<<tp<<endl;
	}
	return 0;
}
```


---

## 作者：ssilrrr (赞：1)

给你一个循环向量，长度为 $N(0\to N-1)$ ，从 $0$ 开始每次往前走 $D$ ，**遇到重复时，直接走最近的未占用方块**。求走了 $K$ 步后到达的位置。

不难发现，如果没有**加粗**条件，我们实际上就是求同余式：
$$
Dk\equiv x\pmod n
$$
但是考虑到不能重复（重复会向后走），这是比较麻烦的。

并且我们需要做到每次 $O(\log n)$ 甚至是 $O(1)$ ，而且数据范围很大，于是就只能继续推柿子。

我们感性理解，$Dk \bmod n$ 一定是一个循环式，我们有没有可能找到它的通项公式呢？

显然可以。$ Dk \equiv x \pmod n$ 可以推得 $Dk-np\equiv x$ ，所以 $ \gcd(D,n)|x$，两者充要。

重复时，每重复一个循环节，相当于在以下式子中给 $b$ 贡献了 $1$：
$$
Dk+b\equiv x \pmod n
$$
所以我们容易发现其实我们只需要用 $k$ 模一下这个循环节的长度，最后再暴力取模一次就可以解决。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,d,k;
int lcm(int x,int y){
	return x*y/__gcd(x,y);
}
void solve(){
	cin>>n>>d>>k;k--;
	int w=__gcd(n,d);
	int x=n/__gcd(n,d);
    int b=k/x;
	x=k%x;
	cout<<(b+x*d)%n<<endl;
}
signed main(){
	cin>>t;
	while(t--)solve();
}
```

---

## 作者：Chillturtle (赞：0)

# 题意

有 $n$ 个排成环的格子，编号从 $0$ 开始。现对其进行如下操作：

- 选择 $0$ 号格子，将其打上标记。

- 选择 $d$ 个格子后的第一个尚未被标记的格子，将其打上标记。

- 重复执行操作直到全部被打上标记。

你需要输出第 $k$ 次标记的格子的编号。

# 思路

首先，先来看 $n$ 和 $d$ 互质的时候。那么这时每次打标记的位置是不会有重复的，所以此时的位置就是 $(k \times d) \bmod n$。

那么，如果 $n$ 和 $d$ 不互质呢？这个时候我们能够发现原数组能够被分成 $\gcd(n,d)$ 组。所以对于重复的次数即为每 $\gcd(n,d)$ 个数一次。每重复一次我们就需要在 $(k \times d) \bmod n$ 再加上组数 $k \div \gcd(n,d)$ 就可以算出当前位了。

具体证明过程如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b1gd64el.png) 

因为 $\gcd(4,2)$ 等于 $2$，所以前两次操作为一组，后面的就要开始重复了。

![](https://cdn.luogu.com.cn/upload/image_hosting/t6xamdqd.png) 

这里本来的组数在算的时候要减一的，我直接把 $k$ 减了一，也是一样的。

最后总结公式，即为：

$$
ans = (d \times k + k \div (n \div \gcd(n,d))) \bmod n
$$ 

# AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n,k,d;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>d>>k;
		k--;
		if(k==0){
			cout<<0<<endl;  
		}else{
			cout<<(d*k+k/(n/__gcd(n,d)))%n<<endl;
		}
	}
return 0;
}
```

---

## 作者：NaOHqwq (赞：0)

笔者模拟模了半个多小时才发现这题不用模拟做，，还是太菜了。。

## 题意

有 $n$ 个排成一个环的格子，编号为 $0\sim n-1$。现在进行如下操作：

+ 选择 $0$ 号格子，将其打上标记。
+ 选择 **$d$ 个格子后的第一个尚未被标记的格子**，将其打上标记。
+ 重复执行直到所有格子都被打上标记。

你需要输出第 $k$ 次标记的格子的编号。

## 思路

一开始看这道题就感觉有点像约瑟夫环（可以看看[这篇文章](https://zhuanlan.zhihu.com/p/35487124)），但是它跟一般的约瑟夫环做法是不一样的。

首先拜谢楼上的各位大佬给我的思路 qwq。

数据范围 $1\le T\le 10^5$，$1\le k\le n\le10^9$，$1\le d\le 10^9$，也说明了这题是数学题。

首先当 $\gcd(n,d)=1$ 即 $n$ 与 $d$ 互质时，结果应为 $((k-1)\times d)\bmod n$。

但是不要只看这一种情况呀 qaq。

当不满足上述情况是该怎么办呢？我们可以发现，除 $0$ 以外的 $+1$ 情况是按规律出现的。

那我们就可以通过计算循环节来解决这种特殊情况啦。容易发现出现 $+1$ 情况的次数为 $\frac{n}{\gcd(n,d \bmod n)}$，所以只需要先计算出第一种情况中的算式，再加上这个次数就可以啦。

终于可以写代码啦！（给菜菜的自己和大家鼓鼓掌）

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long //开不开 long long 可以视情况而定
using namespace std;
signed main(){
	int t, n, d, k, qwq, pwp;
	cin >> t;
	while(t--){
		qwq = 0;
		cin >> n >> d >> k;
		if(d%n == 0){
			cout << k-1 << endl;
			continue;
			
		}
		if(k == 1){
			puts("0");
			continue;
		}
		if(__gcd(n,d%n) == 1){
			qwq = ((k-1)*d)%n;
			cout << qwq << endl;
			continue;
		}
		pwp = n/__gcd(n,d%n);
		qwq += (k+pwp-1)/pwp-1;
		qwq += ((k-1)*d)%n; //具体做法见思路 qwq
		cout << qwq << endl; //要记得换行！
	}
	return 0;
}
```

---

## 作者：_Z_F_R_ (赞：0)

这道题很玄妙。
***
### 题目简述
按以下方法给 $N$ 个数字标记：

* 给第 $0$ 个数打上标记；
* 按以下操作执行 $N-1$ 次：
* 若上一次打上标记的数的编号为 $A$，定义 $x \gets (A + D) \mod N$；
* 若第 $x$ 个数标记过了，则 $x \gets x + 1$；
* 标记第 $x$ 个数，回到第三步。

问第 $K$ 次被编号的数是多少。
***
### 解法
首先，一定不会有：在某个操作开始时，记当前位置为 $i$，则 $i$ 和 $(i + 1) \mod N$ 同时被标记。

证明（~~给我这样的菜鸡看的，勿喷~~）：

记 $p = \gcd(N,D)$。

可知在第 $\dfrac{N}{p},\dfrac{2N}{p},\dfrac{3N}{p},\dots,\dfrac{(p - 1)N}{p}$ 次操作中，必定会与某一个标记过的点重复。

* 若 $p = 1$ 或 $N$，则这一次操作**不存在**，因为当 $p = 1$ 时，$\dfrac{N}{p} = N > N - 1$；当 $p = N$ 时，上一个标记的编号必定比这一次的小 $1$。
* 否则 $1 < p < N$，则 $\dfrac{N}{p}$ 是一个周期。若是第 $x$ 个周期，周期内标记的数从左往右（不是按标号的先后）记为 $a_{x,1},a_{x,2},\cdots,a_{x,\frac{N}{p}}$，都会有:
$$\forall i = [1,p],j = [1,\dfrac{N}{p}),a_{i,j} - a_{i,j - 1} = p$$
再观察可知：
$$\forall i = (1,p],j = [1,\dfrac{N}{p}],a_{i,j} - a_{i - 1,j} = 1$$
例：如图，$N = 6,D = 3$ 时，$a_{1,1} = 0,a_{1,2} = 3,a_{2,1} = 1,a_{2,2} = 4,a_{3,1} = 2,a_{3,2} = 5,p = 3$。
![](https://cdn.luogu.com.cn/upload/image_hosting/dnq220nq.png)

综上所述，不存在这种情况。
***
既然不存在这种情况，第 $4$ 种操作必定执行了 $\dfrac{K - 1}{\frac{N}{p}}$ 次（为什么要 $K - 1$？因为第 $1$ 次标的是 $0$，不算在内），加上第 $3$ 种操作执行了 $K - 1$ 次，答案即为：
$$[(K - 1) \times D + \lfloor \dfrac{K - 1}{\frac{N}{p}} \rfloor] \mod N$$
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,k,d;
long long gcd(long long x,long long y)
{
    return (y == 0)?x:(gcd(y,x % y));
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld%lld",&n,&d,&k);
        k--; // k 要减 1
        long long routine = n / gcd(n,d); //循环周期
        printf("%lld\n",(k * d % n + k / routine) % n);
    }
}
```

---

## 作者：zeekliu (赞：0)

看到这道题有 $10^5$ 组数据，就知道每组数据肯定是 $O(\log)$，因此就知道是推式子。

这个题很自然的就会想到这么大的数据肯定存在循环节，对于 $N,K$，如果 $N$ 和 $K$ 互质，则直接输出即可。

否则，需要寻找循环节。

设初始位置为 $A$，共进行 $t$ 次操作，则有

$$A \equiv A+tD \ (\bmod \ N)$$

转换一下就是

$$tD \equiv 0 \ (\bmod \ N)$$

这时的 $t$ 最小为 $\gcd(N,D)$。

所以一共就有 $\frac{k}{\frac{n}{\gcd(n,d)}}$ 个循环节，相应的答案也会增加 $\frac{k}{\frac{n}{\gcd(n,d)}}$。

那么剩下的就是零头了，这些不需要减去循环节，直接正常去模就可以了。

代码：

```
//ABC290D 23.02.24
#include <bits/stdc++.h>
using namespace std;
long long _,n,d,k;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>_;
    while (_--)
    {
        cin>>n>>d>>k;
        k--;
        cout<<k/(n/__gcd(n,d))+d*k%n<<endl;
    }
    exit(0);
}
```

---

## 作者：Register_int (赞：0)

比较抽象的一题。首先，如果排除标记条件，那么打的标记会构成一个长度为 $\dfrac n{\gcd(n,d)}$ 的圈，元素间的间隔相等，为 $\gcd(n,d)$。接着，由于 $\gcd(n,d)$ 个圈均没有交点（为 $\bmod \gcd(n,d)$ 的等价类），所以每过一圈位置增加 $1$。所以，答案即为在圈上的位置加上圈位移的格数，直接计算即可。

# AC 代码

```cpp
#include <bits/stdc++.h> 
 
using namespace std;
 
typedef long long ll;
 
int t, n, d, k, x;
 
int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d%d%d", &n, &d, &k), k--, x = n / __gcd(n, d);
		printf("%lld\n", (((ll)k * d) + k / x) % n);
	}
}
```

---

