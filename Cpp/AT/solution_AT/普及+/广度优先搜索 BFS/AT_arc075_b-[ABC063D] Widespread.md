# [ABC063D] Widespread

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc063/tasks/arc075_b

あなたが散歩していると、突然 $ N $ 体の魔物が出現しました。それぞれの魔物は *体力* という値を持ち、$ i $ 体目の魔物の出現時の体力は $ h_i $ です。体力が $ 0 $ 以下となった魔物は直ちに消滅します。

幸い、あなたは熟練の魔法使いであり、爆発を引き起こして魔物を攻撃できます。一回の爆発では、以下のように魔物の体力を減らすことができます。

- 生存している魔物を一体選び、その魔物を中心に爆発を引き起こす。爆発の中心となる魔物の体力は $ A $ 減り、その他の魔物の体力はそれぞれ $ B $ 減る。ここで、$ A $ と $ B $ はあらかじめ定まった値であり、$ A\ >\ B $ である。

すべての魔物を消し去るためには、最小で何回の爆発を引き起こす必要があるでしょうか？

## 说明/提示

### 制約

- 入力値はすべて整数である。
- $ 1\ <\ =\ N\ <\ =\ 10^5 $
- $ 1\ <\ =\ B\ <\ A\ <\ =\ 10^9 $
- $ 1\ <\ =\ h_i\ <\ =\ 10^9 $

### Sample Explanation 1

以下のようにして、$ 2 $ 回の爆発ですべての魔物を消し去ることができます。 - まず、体力が $ 8 $ の魔物を中心に爆発を引き起こす。$ 4 $ 体の魔物の体力はそれぞれ $ 3 $, $ 4 $, $ 1 $, $ -1 $ となり、最後の魔物は消滅する。 - 次に、残りの体力が $ 4 $ の魔物を中心に爆発を引き起こす。残っていた $ 3 $ 体の魔物の体力はそれぞれ $ 0 $, $ -1 $, $ -2 $ となり、すべての魔物が消滅する。

### Sample Explanation 2

それぞれの魔物を中心に $ 2 $ 回ずつ、合計で $ 4 $ 回の爆発を引き起こす必要があります。

## 样例 #1

### 输入

```
4 5 3
8
7
4
2```

### 输出

```
2```

## 样例 #2

### 输入

```
2 10 4
20
20```

### 输出

```
4```

## 样例 #3

### 输入

```
5 2 1
900000000
900000000
1000000000
1000000000
1000000000```

### 输出

```
800000000```

# 题解

## 作者：liruixiong0101 (赞：7)

这题一看就是二分答案因为题目说了：
> 为了消灭所有的魔物，你**最少**需要引起几次爆炸呢?

第一，看到最大最少就应该用二分答案了，其次这个 $n$ 的数据范围不超过 $10^5$ 所以时间复杂度应该是 $O(n)$ 或 $O(nlogn)$ 的时间复杂度，所以基本就是用二分答案做了。最后你可以发现爆炸数量肯定越多可以打败所有怪物的概率也就越大，答案在整个区间的右边，又可以用二分答案。综上，这题用二分答案是最好的。

二分答案求最小值代码如下：
```cpp
int Ceil(int x , int y){
	if(x % y == 0) return x / y;
	else return x / y + 1;
}//向上取整

int main(){
  ......
  for(int i = 1; i <= n; i++){
      cin >> p[i];
      r = max(r , p[i]);
  }
  l = 1; r = Ceil(r , b);//最大范围是怪物体力的最大值除以b向上取整
  while(l < r){
      int mid = (l + r) / 2;
      if(check(mid)) r = mid;
      else l = mid + 1;
  }//二分最小值
  cout << l;
```

二分答案的主函数基本一样，就是 $check$ 函数有所不同这里的 $check$ 函数是判断是否可以用 $x$ 次爆炸将所有怪物打败。首先每个怪物都会受到 $x$ 次伤害为 $B$ 的一次爆炸伤害，也就是每个怪物的体力先减去 $x\times B$ 再看那些怪物的体力 $\gt0$ ，那么让它的体力一直减少 $A$ 直到减到体力 $\le0$ 即可，最后看看减的次数是否 $\le x$ 即可。

$check$ 函数代码如下：
```cpp
int Ceil(int x , int y){
	if(x % y == 0) return x / y;
	else return x / y + 1;
}//向上取整
bool check(int x){
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		if(p[i] <= x * b) continue;
		//若x次伤害为B的爆炸可以把他消灭把它消灭
		cnt += Ceil(p[i] - x * b , a - b);
		//用伤害为A的爆炸将他消灭
	}
	return cnt <= x;
}
```

# AC CODE:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n , a , b , p[100005] , l , r;
int Ceil(int x , int y){
	if(x % y == 0) return x / y;
	else return x / y + 1;
}
bool check(int x){
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		if(p[i] <= x * b) continue;
		cnt += Ceil(p[i] - x * b , a - b);
	}
	return cnt <= x;
}
signed main(){
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++){
		cin >> p[i];
		r = max(r , p[i]);
	}
	l = 1; r = Ceil(r , b);
	while(l < r){
		int mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}
```
**Tips : 一定一定要开 long long。**

---

## 作者：liangbowen (赞：6)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT2580)

[更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-at2580)

这题是常规的**二分答案**。

## 前置知识：二分答案

教大家一个小技巧：如何判断一题是否可以使用二分答案，以及如何编写程序？

1. 设计 $f(x)$ 函数，确认其是否满足单调性。

	如果不满足单调性，可能是 $f(x)$ 函数设计错了，但更有可能是本题无法使用二分答案。

2. 在给定 $x$ 的情况下，结合其他算法，计算出 $f(x)$。

3. 确定答案上下界，然后二分 $x$，并用 $f(x)$ 检验即可。

## 思路

我们试一下上述办法好不好用。

设 $f(x)$ 表示 $x$ 次攻击后能否将所有怪物消灭掉。

可以发现该函数满足单调性，前一段全部无法满足，后一段全部可以满足。

所以可以使用二分答案。

在给定 $x$ 的情况写，我们可以 $O(n)$ 求出 $f(x)$ 是否为真。

思路是贪心，直接看代码。

```cpp
bool chk(int x)
{
	long long cnt = 0, xb = 1ll * x * b;
   //要开 long long 因为 x*b 会爆。
	for (int i = 1; i <= n; i++)
		if (xb < h[i])
		{
			//伤害不够，尝试把一些 b 替换成 a。
			int t = h[i] - xb;
			cnt += ceil(1.0 * t / (a-b));
			if (cnt > x) return false;
		}
	return true;
}
```

然后，二分答案即可。二分答案和二分差不多。

```cpp
int FIND(int l, int r)
{
	//没有什么难点，就是模版。
	while (l < r)
	{
		int mid = l + r >> 1;
		if (chk(mid)) r = mid;
		else l = mid+1;
	}
	return r;
}
```

另外，注意到 $h$ 数组元素最大 $10^9$，所以令 $l = 1, r = 10^9$ 二分即可。

## 完整代码

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#define N 100005
using namespace std;
typedef long long LL;
int n, a, b, h[N];
bool chk(int x)
{
	LL cnt = 0, xb = 1ll * x * b;
	for (int i = 1; i <= n; i++)
		if (xb < h[i])
		{
			int t = h[i] - xb;
			cnt += ceil(1.0 * t / (a-b));
			if (cnt > x) return false;
		}
	return true;
}
int FIND(int l, int r)
{
	while (l < r)
	{
		int mid = l + r >> 1;
		if (chk(mid)) r = mid;
		else l = mid+1;
	}
	return r;
}
int main()
{
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
	printf("%d", FIND(1, 1e9+5));
   //实际上 1e9 就足够了。开大一丢丢保险。
	return 0;
}
```

希望能帮助到大家！

---

## 作者：fengenrong (赞：3)

其实这道是个二分答案的模板题，我们可以二分出一个 $mid$ 进行判断，遍历每一个 $g_i$，看一看 $b\times mid$ 是否大于 $g_i$。如果大于，就不用理它；否则就将 $sum$ 加上需要攻击多少次。最后再判断，如果 $sum\leq mid$ 就用 $ans$ 记录一下答案，再缩小二分中 $r$ 范围。否则将 $l$ 缩小，再继续二分，最后输出 $ans$ 就行了。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b;//分别表示怪物的数量，爆炸中心的魔物减少的体力，其他魔物减少的体力 
int g[1000005];//表示每个怪物的体力 
int ans;//用来记录答案 
bool pd(int x)
{
	int sum=0;//统计 
	for(register int i=1;i<=n;i++)
	{
		if(x*b<g[i])//不能直接被击败 
		{
			sum+=ceil((g[i]-x*b)/(1.0*(a-b)));//加上需要攻击多少次
		}
	}
	return sum<=x?true:false;//判断是否符合 
}
signed main()
{
	cin>>n>>a>>b;
	for(register int i=1;i<=n;i++)
	{
		cin>>g[i];//输入 
	}
	int l=1,r=INT_MAX;//因为不知道范围，所以设定一个极大值 
	while(l<=r)//二分 
	{
		int mid=(l+r)/2;//求中值 
		if(pd(mid)==true)//合法 
	    {
	    	ans=mid;//记录 
	    	r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaoPanda (赞：3)

### Problem
有 $n$ 个魔物，第 $i$ 个魔物有 $h_i$ 滴血。

每次攻击你可以选一个魔物 $i$ 使其血量减去 $x$ ，其他魔物血量减去 $y\ (x>y)$ 。

问使所有魔物血量 $\le 0$ 至少要几次攻击。

### Solution
很明显答案具有单调性，考虑二分。

每次 check 转化为攻击 $now$ 次能否将所有魔物打败。

那么这 $now$ 次攻击对所有的魔物血量减少 $now\times y$（不考虑哪个魔物减少 $x$ 滴血)。

这时候可能会有 $h_i> now\times y$ ，那这个魔物就需要减少 $x$ 滴血，也就是说这个魔物每次多减少 $x-y$ 滴血。

令 $s=h_i-now\times y$ 表示这个魔物剩下的血，那就至少需要攻击它 $\lceil \dfrac{s}{x-y} \rceil$ ( $s$ 除以 $x-y$ 向上取整）次。

如果总次数 $\le now$ ,就代表攻击 $now$ 次可以将所有魔物打败，然后尝试更小的 $now$，反之选择更大的 $now$，时间复杂度为 $O(n\log h_i)$。

upd：实际上这题可以贪心的，每次取剩余血量最大的魔物进行攻击，就像[奶牛晒衣服](https://www.luogu.com.cn/problem/P1843)一样，但注意到这题的数据很大，其时间复杂度使 $O(ans\log n)$ 的，在 $h_i$ 很大的请况下会 TLE。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
#define int long long
int a[N],n,x,y;
bool check(int now)
{
	int sum=0;
	for(int i=1;i<=n;i++)
		if(a[i]>y*now)sum+=ceil((a[i]-y*now)*1.0/(x-y));//计算需要攻击多少次（记得使向上取整）
	//cout<<sum<<" "<<now<<endl;
	return sum<=now;//符合条件
}
main()
{
	int l=1,r=1e9,ans=0;//答案范围在[1,1e9]之间
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	while(l<=r)//二分
	{
		int mid=(l+r)/2;
		if(check(mid))
			r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：shenmadongdong (赞：3)

**思路：二分**  

~~可能还有更优的做法，但我太菜了想不出~~  

首先如果一个怪物被打死了，那它消失与不消失并没有什么区别，只需在最后统计一下是否死亡即可

考虑二分答案，可证答案一定小于$10^9$,所以必然跑得飞快 

而对于每一个答案，验证的时候先假设每次是B点伤害，打不死就换成A点伤害。但是我们知道A点伤害的次数是有限的，每次只能造成一次A点伤害，因此它不能超过发动攻击的次数，所以最后统计一下需要造成A点伤害的次数是否超过答案即可。


```
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,s[100010],l,r,mid;
bool chk(long long x)
{
    long long cnt=0;
    for(int i=1;i<=n;i++)
    {
        if (x*b<s[i]) jyz+=(s[i]-x*b-1)/(a-b)+1;//统计需要造成的A点伤害次数
        if (cnt>x) return 0;//次数超出范围则不合法
    }
    return 1;
}
int main()
{
	cin>>n>>a>>b;
    for(int i=1;i<=n;i++) scanf("%lld",&s[i]),r=max(r,s[i]);
    r=(r-1)/b+1;//最大的答案值显然比每次都用小伤害打最大体力所需的次数小
    while(l<r)
    {
        mid=(l+r)/2;
        if (chk(mid)) r=mid;
        else l=mid+1;
    }//朴素二分
    cout<<l<<'\n';
	return 0;
}
```

---

## 作者：Acerkaio (赞：2)

### 0x00 题
[ $${\color{Violet} 【题面】} $$ ](https://www.luogu.com.cn/problem/AT2580)
### 0x01 二分

您还没有接触二分？[click here](https://baijiahao.baidu.com/s?id=1695817901441280653&wfr=spider&for=pc)

简单来说：
二分算法要求待查找的序列**有序**，每次查找都取**中间位置的值与待查关键字进行比较**，如果中间位置的值比待查找关键字大，则在序列的左半部分继续执行查找；如果中间位置的值比待查关键字小，则在序列的右半部分继续查找，直到查找到关键字为止，否则序列中没有待查关键字。

### 0x02 本题思路
- 我们一般来说，二分的那和值即为题目所求，如本题，我们求最少需要引起几次爆炸，那么就二分它。但是其中问题来了，它在哪个序列中？  
也很容易：我们的这个值即为题目 $h_i$ 范围 $[1,1e9]$。

- check 函数怎么写?  
[click here](https://www.cnblogs.com/BUAA-Wander/p/13311275.html) 在这题当中，攻击 $num$ 次，对于每一次二分枚举到的 $num$ 值，我们只需判断这样行不行得通，判断过程如下。  
	1. 我们首先就可以知道，每个魔物都扣 $b$ 体力，那么 $num$ 次攻击就会全员减少 $num \times b$ 体力。
    2. 这时，就出现问题了，如果有魔物体力大于全体减少的体力，那么就要去攻击他，总共需要攻击 $\left \lceil \frac{h_i-num \times b}{a-b} \right \rceil $次了，记录他。
    3. 最后只需要比较所记录的与 $num$ 了。
### 0x03 CODE
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a, b, h[10000001];
bool check(int num) {
	int sum = 0, js;
	for(int i = 1; i <= n; i++) {
		if(h[i] > num*b) { sum = sum+ceil((h[i]-num*b)/(1.0*(a-b))); }
	}
	return sum <= num;
}
signed main() {
	cin>>n >>a >>b;
	for(int i = 1; i <= n; i++) { cin>>h[i]; }
	int l = 1, r = 1e9, mid, ans;
	while(l <= r) {
		mid	= l+r>> 1;
		if(check(mid)) {
			r = mid-1;
			ans = mid;
		} else {
			l = mid+1;
		}
	}
	cout<<ans <<'\n';
	return 0;
}
```


---

## 作者：kevin1616 (赞：1)

### 审题
选择生存的魔物，以魔物为中心引起爆炸。成为爆炸中心的魔物的减少 $A$ 体力，其他魔物的分别减少 $B$ 体力。消灭所有的魔物的最少爆炸次数。
***
### 方法
【二分答案】我们可以发现问题里有“最”这个字，这种题目里大多是使用二分答案做法。时间复杂度 $O(N \log N)$，主要来自于二分和判断函数。在此题是可行的。
***
### 思路
输入的同时把最大的体力统计一下，然后二分答案。

在判断函数里，每次判断当前魔物是否符合当前的爆炸标准。如果是，那么将和加上他的差距。最后判断这个和是否小于等于当前需要判断的数即可。
***
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b;
int c[100005];
int l = 1,r;
bool check(int x){ //判断函数
    int sum = 0;
    for(int i = 1;i <= n;i++){
        if(c[i] > x * b) sum += ceil((c[i] - x * b) * 1.0 / (a - b));
    }
    return sum <= x;
}
signed main(){
    cin >> n >> a >> b;
    for(int i = 1;i <= n;i++){
        cin >> c[i];
        r = max(r,c[i]); //最大的体力
    }
    r = ceil(r * 1.0 / b);
    while(l < r){ //二分答案
        int mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl; //输出答案
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：Composite_Function (赞：1)

# 前置——二分

二分是一种特殊的解题技巧。通过二分，可以将复杂度 $\log$ 化。

来举一个小栗子。比如猜数这个小游戏，数的范围为 $\left[1, 2 ^ {32} - 1\right]$。我们的第一反应一定是取中间值 $2 ^ {16}$ 来判断数在 $\left[1, 2 ^ {31}\right)$ 还是 $\left(2 ^ {31}, 2 ^ {32} - 1\right]$（当然如果所求数就是 $2 ^ {16}$，那么久不用继续了）的范围里。依次操作，只需 $32$ 次就能求出答案。

显然地，可以将该结论推广到 $\left[1, n\right]$，所求时间复杂度为 $O(\log n)$。

可以看出，二分在解决这类问题上很有优势。不过，二分也有缺点，那就是只能处理具有单调性的问题。

前置讲完了，来看题吧。

------------

# 思路

这里有 $val _ i$ 来表示怪物的体力值。

记 $P(x)$ 为只发动 $x$ 次爆炸是否可以消灭所有怪物。显然地，如果 $P(x) = true$，则 $P(x + t) = true$，其中 $x, t \in Z ^ +$。

从而，可以得出结论 $\left[ P(x) \right]$ 具有单调性。所以可以二分 $a$。显然地，由于对 $a$ 没有限制，肯定有解。

那么如何判断 $P(x)$ 呢？因为 $A \geq B$，所以每个怪物最少会受到 $x \times B$，对于 $i$ 使得 $val _ i \leq x \times B$，这个怪物无需单独以它为爆炸中心来进行爆炸，否则，每次以它爆炸对这个怪物会多造成 $(A - B)$。

时间复杂度 $O(N)$。

```cpp
bool judge(int x)
{
	int num = 0;
	for (int i = 1; i <= n; ++i)
		if (val[i] > b * x)
			num += (val[i] - b * x + a - b - 1) / (a - b);
	return (num <= x);
}
```

接下来，就是二分。时间复杂度是常数 $O(\log 10 ^ 9)$。

```cpp
int find(int l, int r)
{
	int mid = (l + r) / 2;
	if (l > r) return 1e9;
	if (judge(mid) == false) return find(mid + 1, r);
	else return min(mid, find(l, mid - 1));
}
```
注意，出于爆 `long long` 的考虑，初始值设置为 $\left[1, 10 ^ 9 \right]$。

------------

# 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

# define int long long
const int N = 1e5 + 10;

int n, a, b, val[N], ans;

bool judge(int x)
{
	int num = 0;
	for (int i = 1; i <= n; ++i)
		if (val[i] > b * x)
			num += (val[i] - b * x + a - b - 1) / (a - b);
	return (num <= x);
}
int find(int l, int r)
{
	int mid = (l + r) / 2;
	if (l > r) return 1e9;
	if (judge(mid) == false) return find(mid + 1, r);
	else return min(mid, find(l, mid - 1));
}

signed main()
{
	cin >> n >> a >> b;
	for (int i = 1; i <= n; ++i)
		cin >> val[i];
	
	cout << find(1, 1e9) << endl;
	
	return 0;
}
```

总共时间复杂度 $O(R \times N)$，其中 $R$ 为常数 $\log 10 ^ 9 \approx 30$。

---

## 作者：happybob (赞：1)

本题可以很明显看出应该是二分题目，如果需要二分答案，需要满足：

- 答案具有单调性，也就是说确定一个中央，中央左边不符合答案，右边符合，或者反过来。

假设二分答案验证阶段的复杂度是 `O(m)`，总共的答案有 `n` 种选择，则二分答案的复杂度为 $\large \text{O}(log_n 
\,\, m)$。

二分就是在单调性的可能答案 `1 ~ n` 中每次找到中间值并判断是否可行，值得找到最后一个答案。

代码：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e5 + 5;
int n, a, b, arr[N];

bool check(long long x)
{
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		int b_hurt_times = ceil(arr[i] * 1.0 / b);
		if (b_hurt_times > x)
		{
			int s = x * b;
			cnt += (arr[i] - s - 1) / (a - b) + 1;
		}
		if (cnt > x) return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	long long  l = 0, r = 1e13;
	while (l < r)
	{
		long long mid = (l + r) >> 1;
		if (check(mid))
		{
			r = mid;
		}
		else l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
```


---

## 作者：luxiaomao (赞：0)

## 前言（~~废话~~）

什么？竟然还有这么简单的二分绿题？~~还能水题解？~~

赶紧发篇题解造福大家。

## 分析

首先给出题意：

> 给出 $n$ 个怪物的初始血条 $h_i$，你每次以一只怪物为中心放技能，能对这只怪物造成 $A$ 的伤害，并对其他所有怪物造成 $B$ 的溅射伤害。求最少放几次技能能把怪物全部打败。

很明显，你放的技能越多，造成的总伤害就越高（$A$ 和 $B$ 均为正数），也就越有可能打败所有怪物。

用 dalao 的方式讲，这就是**单调性**，在某一个阈值的左边的所有值都无法消灭所有怪物，阈值自己以及右边的所有值都可以，求这个阈值。已经非常明显了，这题我们考虑**二分**。

## 实现

首先给出伪代码：

```test
l = 最小值 
r = 最大值
while(l < r)
{
	mid = (l+r)/2
	if(放 mid 次技能能够消灭所有怪物)
   		r = mid
	else
   		l = mid + 1
}
answer = l
```

这是二分的板子代码，那么剩下的就是，如何判断“放 $mid$ 次技能能否消灭所有怪物”？换句话讲，$check$ 函数怎么写？

看~~伪代码~~具体的代码和注释。（PS：别忘了数据范围，要开 `long long` 哦）

```cpp
#define int long long

int Ceil(int x,int y){return x%y==0 ? x/y : x/y+1;}//手写向上取整函数
//C++自己是有内置的 ceil 向上取整函数的，但似乎不支持 long long 类型

bool check(int x)//此题精华，check 函数
{
	int cnt = 0;//统计除了溅射伤害外，还要放多少次直接伤害
	for(int i = 1;i <= n;i++)
	{
		if(x*b < h[i])//如果只用溅射伤害无法消灭这只怪物
			cnt += Ceil(h[i] - x*b,a-b);//计算这只怪物除了溅射伤害外，还要几次直接伤害才歇菜
	}
	return cnt <= x;如果放技能次数不超过 x 次，说明 x 是一种合法的方案
}
```

## Code Time

接下来就是~~喜闻乐见的~~代码时间~

**目前**在这道题跑到了最优解，个人感觉码风还是比较干净的，希望大家能够看懂。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a,b;
int h[100005];

int Ceil(int x,int y){return x%y==0 ? x/y : x/y+1;}
bool check(int x)
{
	int cnt = 0;
	for(int i = 1;i <= n;i++)
	{
		if(x*b < h[i])
			cnt += Ceil(h[i] - x*b,a-b);
	}
	return cnt <= x;
}

signed main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld",&h[i]);
	}
	
	int l = 1,r = 1e9+10;
	while(l < r)
	{
		int mid = (l+r)>>1;
		if(check(mid))r = mid;
		else l = mid+1;
	}
	printf("%lld",l);
	return 0^_^0;//卖个萌QAQ
}
```

如果大家有什么问题欢迎私信问我~

~~看在我写得这么认真，求过！~~

---

## 作者：Proxima_Centauri (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_arc075_b)

# 题意描述
有一群怪物，每次爆炸，选择一个怪物减少 $A$ 的血量，其余减少 $B$ 的血量，问：最少多少次爆炸，让所有怪物血量**小于等于** $0$。

# 题目解析
关键词**最少**，~~明显地~~提示我们要用**二分法**。

那么，很明显，我们多放几次爆炸，很明显比少放几次爆炸更容易杀死怪物，所以我们二分的代码应该是这样：
```
int l = 1, r = 1e9 + 1, ans = 0;
while (l <= r)
{
	long long m = (l + r) / 2;
	if (chk(m)) ans = m, r = m - 1;//chk函数验证m个爆炸能不能全部杀死
	else l = m + 1;
}
```
那么问题来了，我们的 $chk$ 函数应该怎么写？

1. 如果我们放了 $x$ 次爆炸，那么每个怪物至少会受到 $B \times x$ 的伤害。

2. 那么当一个怪物被打掉了这么多伤害还不死，我们就必须把它当做爆炸中心来打了，那么每次会多有 $A - B$ 的伤害，用 $h_i - B \times x$ 去除以这个数就是所用的次数。

**细节：需要向上取整**

3. 最后判断次数之和是否 $\le x$ 就可以了。

下面是 $chk$ 函数：
```
bool chk(long long x)
{
	long long res = 0; //res是次数之和
	for (int i = 1; i <= n; i++)
	{
		if (h[i] > b * x) res += ceil((h[i] - b * x) * 1.0 / (a - b));
	}
	if (res <= x) return true;//这里的res会爆int，要用long long
	return false;
}
```
# AC code
话不多说，上代码！
```
#include<cstdio>
#include<iostream>
#include<cmath> 
#include<algorithm>
using namespace std;
int h[100010];
int n, a, b, ss;
bool chk(long long x)
{
	long long res = 0;
	for (int i = 1; i <= n; i++)
	{
		if (h[i] > b * x) res += ceil((h[i] - b * x) * 1.0 / (a - b)); 
	}
	if (res <= x) return true;
	return false;
}//chk函数
int main(){
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) 
	{
		cin >> h[i];
	}
	int l = 1, r = 1e9 + 1, ans = 0;
	while (l <= r)
	{
		long long m = (l + r) / 2;
		if (chk(m)) ans = m, r = m - 1;
		else l = m + 1;
	}//二分法
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_wjr_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2580)

## Part 1 题面翻译

有 $n$ 个怪物，每一个怪物有一个血量 $h_i$。我们可以任意选择一只怪物引发爆炸，在爆炸中心点的怪物血量减少 $A$ 点，其他怪物血量减少 $B$ 点。问：最少需要几次爆炸，才能让所有怪物铀好的离开世界。

## Part 2 题目思路

很明显， $O(n^2)$ 的算法在此题的数据范围下会被完美的卡掉。那么，我们就需要效率更高的思路。~~当然，CF少爷机一秒过 2e9 还稍微可能试一试。~~

那么，最简单的，最容易想到做法，差不多就是二分了。

好二分吗？二分什么呢？

我们注意到，这题需要考虑的是最小的爆炸次数，而如果 $m$ 次可以， $m + 1$ 次就没有理由不行。同理，如果 $m + 1$ 次不行， $m$ 次照样不行。

换句话说，答案具有 __单调性__。

那么，我们就可以贴代码了。

## Part 3 AC Code

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int n, A, B, a[100010];

bool check (int x) //考虑爆炸x次时，能否把怪物全部炸死
{
	
	int res = 0;
	for (int i = 1; i <= n; i++)
		if (a[i] > B * x) res += ceil ((a[i] - B * x) * 1.0 / (A - B)); //依次枚举每只怪物被消灭所需要的爆炸次数
	return res <= x;
}

signed main()
{
	cin >> n >> A >> B;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int l = 1, r = 1e9, ans = 0;
	while (l <= r) //二分
	{
		int mid = (l + r) / 2;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}
```

完结撒花！

###### 注：艺术就是***爆炸！

---

