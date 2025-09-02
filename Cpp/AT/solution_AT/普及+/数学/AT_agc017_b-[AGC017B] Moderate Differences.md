# [AGC017B] Moderate Differences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc017/tasks/agc017_b

$ N $ 個のマスが一列に並んでいます． 一番左のマスには整数 $ A $ が，一番右のマスには整数 $ B $ が書かれており，他のマスには何も書かれていません．

青橋君は，何も書かれていないマスに整数を書き込み，次の条件を満たすようにしたいです：

- どの隣接する $ 2 $ マスについても，書かれている整数の差は $ C $ 以上 $ D $ 以下である．

青橋君は，この条件を満たす限り，いくらでも大きい整数や小さい整数を書き込むことができます． 青橋君が条件を満たすように整数を書き込むことができるかを判定してください．

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 500000 $
- $ 0\ \leq\ A\ \leq\ 10^9 $
- $ 0\ \leq\ B\ \leq\ 10^9 $
- $ 0\ \leq\ C\ \leq\ D\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

例えば，左のマスから順に $ 1,\ -1,\ 3,\ 7,\ 5 $ となるように整数を書き込めばよいです．

## 样例 #1

### 输入

```
5 1 5 2 4```

### 输出

```
YES```

## 样例 #2

### 输入

```
4 7 6 4 5```

### 输出

```
NO```

## 样例 #3

### 输入

```
48792 105960835 681218449 90629745 90632170```

### 输出

```
NO```

## 样例 #4

### 输入

```
491995 412925347 825318103 59999126 59999339```

### 输出

```
YES```

# 题解

## 作者：MY（一名蒟蒻） (赞：10)

[原题传送门](https://www.luogu.com.cn/problem/AT2665)

这题代码应该是蓝题里最短的一道了。

题解区有巨佬用了 $\text{O(1)}$ 的做法，蒟蒻表示并不会。观察一下数据范围，$\text{max(n)=5e5}$ ，可以接受 $\text{O(n)}$ 甚至 $\text{O(nlogn)}$ 的做法。所以直接挑简单的来就好啦。

本文的算法是 $\text{O(n)}$ 的，可能并没有 $\text{O(nlogn)}$ 做法。

---
这题的输出在众多构造题中是比较简单的。只需要输出是否有合法方案。考场上大家想不出转化可以考虑人品骗分。

**任意相邻两个数的差的绝对值在 $\text{[C,D]}$ 之间。**

这玩意好像不是很好构造？

如果 $\text{C=0}$ ，题目就变得简单很多了。

那么可不可以尝试把范围通过某种手段转化为 $\text{[0,D-C]}$ 呢？

考虑每个数字相对于前面那个数字变化了多少，列出式子。

$A + x_1 + · · · + x_{n-1} = B$

其中有的是加有的是减，不妨枚举加的有多少个。因为至少要加 $\text{C}$ ，所以等式两边可以同时减去若干个个 $\text{C}$ ，对于减同理。

这样，加和减的数字范围就变成了 $\text{[0,D-C]}$ ，**问题转化为等式左边能否弄出一个范围使得等式右边在这个范围内**，贪心构造即可。

时间复杂度 $\text{O(n)}$ 。

### Code
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

long long n,a,b,c,d;

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
   //(2*(i+1)-n)*c表示有效的C
	for(int i=0;i<n-1;i++)//枚举加号
		if(b-(2*(i+1)-n)*c <= a+i*(d-c)+d && b-(2*(i+1)-n)*c >= a+(n-2-i)*(c-d)+c)//上下界，至于加D和加C是为了满足题目条件
			return printf("YES"),0;
	printf("NO");
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
## $\text{Thank you for your reading!}$
您的点赞和评论是对作者最大的支持！

---

## 作者：BLUESKY007 (赞：10)

又是一道思路特别清奇的题qwq...~~(瞪了一上午才发现O(1)的结论...差点还想用O(n)解决)~~  
问题可以转化为是否能够由$f_{1}=a$通过$\pm x \in[c,d]$得到$f_{n}=b$,于是考虑用数学方法解决  
证明比较简单...就是...能想到这一点就很毒瘤了qwq...~~让我来随手拿一个样例举例qwq~~  
```
输入样例2：4 7 6 4 5
输出样例2：NO
```
~~丝毫不想画图...太乱惹qwq~~  
为了能看的更明白我还是画吧qwq(感谢GeoGebra)  
注：横坐标表示框内数值,纵坐标表示编号~~(宽屏没办法qwq...看不清就保存图片放大...还是能看清楚一点的...实在不行下面会放坐标)~~  
![](https://cdn.luogu.com.cn/upload/pic/28713.png)  
![](https://cdn.luogu.com.cn/upload/pic/28720.png)  
做出上图后发现,绿色线段对应位置是可以到达的,此时问题转化为点$B$是否在某一条绿色线段(含端点)上  
取所有线段中点后发现,在纵坐标为奇数时,所有线段中点到点$A$的横坐标距离为$2k \times \frac{c+d}{2}(k \in N)$,在纵坐标为奇数时,所有线段中点到A的横坐标距离为$(2k+1) \times \frac{c+d}{2}(k \in N)$,位于$y=k$上的最远的线段中点到点$A$的横坐标距离为$(k-1) \times \frac{c+d}{2}$,且长度为$(k-1) \times (d-c)$,也即点$B$与点$A$的横坐标距离$\leq (n-1) \times \frac{c+d}{2}$且与位于$y=n$上某条线段的中点距离$\leq \frac{(n-1) \times (d-c)}{2}$时由$A$可以到达$B$,所以只需要按照$n$的奇偶性分类$O(1)$计算结果即可.  
~~全都是数学推导...感性理解一下就好~~  
下面放代码$\downarrow \downarrow \downarrow $  
```cpp
#include<cstdio>//AT2665
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;

int n,a,b,c,d,delta,whole;

double nxt,half=0.5,maxhalf,lft;

int main(){
    scanf("%d%d%d%d%d",&n,&a,&b,&c,&d);
    nxt+=c+d;
    nxt/=2;
    half=nxt-c;
    maxhalf=half*(n-1);
    delta=abs(a-b);
    if(delta>(n-1)*nxt+maxhalf){//超过最远距离
        printf("NO\n");
        return 0;
    }
    whole=(int)(delta/nxt);
    lft=delta-nxt*whole;
    if(n&1){//n%2==1
        if(whole&1){
            lft=nxt-lft;
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
        else{
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
    }
    else{//n%2==0
        if(whole&1){
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
        else{
            lft=nxt-lft;
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
    }
    return 0;
}

```

---

## 作者：chl090410 (赞：7)

## The Solution to AT_agc017_b [AGC017B] Moderate Differences

### Description

有 $N$ 个格子排成一排，第一个格子写了数字 $A$，最后一个格子写了数字 $B$，你需要在中间的格子中填入一些数字，问是否存在一种方案使得任意相邻两个格子的数字的差的绝对值都在 $[C,D]$ 之间，是则输出 ```YES```，否则输出 ```NO```。

### Solution

我们考虑把第一个格子写 $A$，相邻两个格子的数字的差的绝对值都在 $[C,D]$ 之间时最后一个格子可能填写的数求出来，再看 $B$ 是否在其中即可。

我们假设后一个数减前一个数所得的差为一组差，因为有 $N$ 个数，所以共有 $N-1$ 组差，我们先假设所有的差均为正数，那么此时 $B$ 的最小值在这些差都为最小值 $C$ 时取到，为 $A+C\times(N-1)$，同理，$B$ 的最大值在差都为 $D$ 时取到，为 $A+D\times(N-1)$，此时 $B$ 的取值范围为 $[A+C\times(N-1),A+D\times(N-1)]$。

我们再假设有一组差为负数，此时 $B$ 若要取最小值，就要保证每一个差都最小，我们让所有正数都为 $C$，而负数为 $-D$ 即可，此时 $B$ 的最小值为 $A+C\times(N-1)-(C+D)$，同理，此时 $B$ 的最大值为 $A+D\times(N-1)-(C+D)$。

以此类推，我们便可得到规律：有 $K$ 组差为负数时 $B$ 的取值范围为    $[A+C\times(N-1)-K\times(C+D),A+D\times(N-1)-K\times(C+D)]$，而输入的 $B$ 只要在其中一个范围里则输出 ```YES```，否则输出 ```NO```。

而若左端点离 $B$ 较远的区间都能满足 $B$ 在范围内，那么左端点离 $B$ 较近的区间一定能满足 $B$ 在范围内，而若左端点的位置大于 $B$ 则 $B$ 一定不在范围内，所以我们只需判断左端点离 $B$ 最近且 $\le B$ 的区间是否能让 $B$ 在范围内即可。

无论 $K$ 为何值，区间长度都是不会变的，其值恒为 $(D-C)\times(N-1)$，而区间左端点 $\bmod(C+D)$ 的值也不变，为 $A+C\times(N-1)\bmod(C+D)$，我们设其为 $p$，$B\bmod (C+D)$ 为 $q$，那么因为只需判断离 $B$ 最近且 $\le B$ 的区间的左端点所在的区间是否能让 $B$ 在范围内，即是判断这个左端点与 $B$ 的距离与区间长度的关系，若其 $\le$ 区间长度则输出 ```YES```，否则输出 ```NO```。

而因为该左端点离 $B$ 最近，又要比 $B$ 小，所以当 $p<q$ 时，这个距离为 $q-p$，而若 $p>q$，这个距离就为 $(q-(p-(C+D)))=(q-p+C+D)$，而这两种情况可以合并写为 $(q-p+C+D)\bmod(C+D)$。

于是问题就转化成了判断 $(q-p+C+D)\bmod(C+D)$ 与区间长度 $(D-C)\times(N-1)$ 的关系，若前者 $\le$ 后者则输出 ```YES```，否则输出 ```NO```。

这个问题用一个 ```if``` 语句判断一下即可。

另外，代码中的 $a,b,c,d,e$ 分别代表题目中的 $N,A,B,C,D$。

### AC code 如下：

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e;
signed main(){
	cin>>a>>b>>c>>d>>e;
	if((c%(d+e)+(d+e)-(b+d*(a-1))%(d+e))%(d+e)<=(e-d)*(a-1)&&e*(a-1)+b>=c) cout<<"YES";
	else cout<<"NO";
	return 0;
}

---

## 作者：water_tomato (赞：4)

本文同步发表与个人博客：[Link](https://www.watertomato.com/at2665-agc017b-moderate-differences-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/AT2665)。

一共有 $n$ 个格子，给定两个整数 $A,B$ 分别位于第 $1$ 和第 $n$ 格，中间有 $n-2$ 个空格。询问是否存在一种填数方案满足任意相邻两个数之差的绝对值在 $[C,D]$ 之间。

## 解析

考虑这 $n$ 个数之间有 $n-1$ 对差，因此题目等价于：

是否存在 $A+\sum\limits^{n-1}_{i=1} x_i=B,x_i\in[-D,-C]\cup[C,D]$。

尝试枚举 $x_i$ 中为正数的数量。假设有 $p$ 个 $x_i$ 为正，则有：

$A+\sum\limits_{i=1}^{p}x_i-\sum\limits_{i=p+1}^{i=n-1}x_i=B,x_i\in[C,D]$。

由于形似 $[0,a]$ 的区间容易求范围，我们考虑设法将 $[C,D]$ 转化为 $[0,D-C]$。将两边式子同时减去 $p$ 个 $C$，再同时加上 $n-1-p$ 个 $C$，又有：

$A+\sum\limits_{i=1}^{p}x_i-\sum\limits_{i=p+1}^{i=n-1}x_i=B+(n-1-2\times p)\times C ,x_i\in[0,D-C]$。

对于这个式子，左边的最大值为 $A+p\times(D-C)$，最小值为 $A-(n-1-p)\times(D-C)$，依次枚举正数的数量后，分别判断变形后的 $B$ 是否在该区间内即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,A,B,C,D,Max,Min;
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&A,&B,&C,&D);
	for(int i=0;i<=n-1;i++){
		int tB=B+C*(n-1-2*i);//B 变形
		int Max=A+i*(D-C);//最大值
		int Min=A-(n-1-i)*(D-C);//最小值
		if(tB>=Min&&tB<=Max){//是否在区间内
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```



---

## 作者：So_noSlack (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT_agc017_b)&[Atcoder 链接](https://atcoder.jp/contests/agc017/tasks/agc017_b)

本篇题解为此题较**简单做法**，请放心阅读。

## 题目简述

一共有 $n$ 个格子，给定两个整数 $A,B$ 分别位于第 $1$ 和第 $n$ 格，中间有 $n−2$ 个空格。询问是否存在一种填数方案满足任意相邻两个数之差的绝对值在 $[C,D]$ 之间。

依次输入 $n,a,b,c,d$。

若能，输出 `YES`；反之输出 `NO`。

## 思路

遇事不决先看**数据范围**，发现数据范围 $3 \le N \le 5 \times 10^5$，那么时间复杂度在 $O(N)$ 以内就可以接受，本篇题解就**详细解释一下** $O(N)$ 的算法。

首先可以想到 $O(N)$ 的复杂度就是**遍历** $N$，可以想到枚举在 $A,B$ 之间填了 $i$ 个数，从 $0 \sim N-2$ 遍历即可，遍历时进行判断，如果满足要求可直接输出 `YES`，否则遍历完后输出 `NO`。

接着可以先把区间 $[C,D]$ **转化**为区间 $[0,D-C]$，那么判断条件就需要判断 $C$ 的**合法性及可行性**：

$$B - (2 \times (i + 1) - N) \times C$$

接着可写出判断条件的**边界条件**，首先是最大值即**右区间**，通过右区间 $D-C$ 很容易得出：

$$A + i \times (D - C) + D$$

以及**左区间**：

$$A + (N - 2 - i) \times (C - D) + C$$

如果**合法**的 $C$ 在此区间内则输出 `YES`，否则在**遍历后输出** `NO`。

**注意：因为均为闭区间**，**所以需是 $\le$ 而不是 $<$**。

经过以上**分析及转化**，很容易即可得出代码了。

[提交记录](https://www.luogu.com.cn/record/117450111)

$$\text{The End!}$$

---

## 作者：robinyqc (赞：1)

一个比题解区简单一些的 $O(1)$ 做法。

### 题意简述

给定 $n, a, b, c, d$，问是否能构造一个长度为 $n$ 的序列 $S$，满足：

+ $S_1 = a, S_n = b$。
+ $\forall i \in [1, n), c\leq |S_{i + 1} - S_i| \leq d$。

（当然本题也很好 $O(n)$ 构造方案）

### 解题思路

我们把 $S$ 差分得到 $\Delta$，可以发现，任意调换 $\Delta$ 内的元素，$S_1, S_n$ 都不会改变。因此对于任意一种合法方案，我们都可以调整成前半段上升，后半段下降的形式，同样是合法的。

比如 $S = (3, 8, 7, 8, 5, 10)$，有 $\Delta = (\sim, 5, -1, 1, -3, 5)$，调整 $\Delta$ 顺序可得 $\Delta = (\sim, 5, 1, 5, -1, -3)$，那么有 $S = (3, 8, 9, 14, 13, 10)$。$S_1$ 和 $S_n$ 并未改变。

只上升的范围是容易得到的：上升 $k$ 次，可以到达的范围为 $[ck, dk]$。下降，相当于从末尾上升。所以直接枚举中间的转折点，判断从开头能到达的区间和从末尾能到达的区间是否有交即可。$O(n)$ 可以通过此题。

这东西看着就很好优化。$O(\log n)$ 是简单的。注意到转折点 $i$ 增大时，能够从开头到达的区间是单调地移动的。所以可以二分。

其实 $O(1)$ 也不难。两个区间有交相当于其中一个区间的端点属于另一个区间。比如存在 $a + ci\in [b + c(n - i), b + d(n - i)]$。简单解下不等式求出 $i$ 的合法区间。最后判 $i$ 的合法区间是否在 $[0, n)$ 就行了。

### 代码实现

```rust
use proconio::input;

fn is_cap(x: i64, y: i64, n: i64) -> bool
{
    std::cmp::min(y, n) >= std::cmp::max(x, 0)
}

fn main()
{
    input! { n: i64, a: i64, b: i64, c: i64, d: i64 }
    let n = n - 1;
    let v1 = b + c * n - a;
    let v2 = b + d * n - a;
    if is_cap((v1 + c + d - 1) / (c + d), v1 / (c + c), n)
    || is_cap((v2 + d + d - 1) / (d + d), v2 / (c + d), n)
    || is_cap((v1 + c + c - 1) / (c + c), v2 / (c + d), n) {
        println!("YES");
    } 
    else {
        println!("NO");
    }
}
```

---

## 作者：Aw顿顿 (赞：1)

## 题目大意

有 $n$ 个格子，最左边是 $a$ 最右边是 $b$，中间是空的，问是否能填充中间的格子，使得任意相邻两数的差的绝对值在 $[c,d]$之间。

顺次输入 $n,a,b,c,d$。

若能，输出 `YES`；反之输出 `NO`。

## 解法简析

先看 $a,0,0,\cdots,0,b$ 这样一个序列怎么填充。

由于存在绝对值，我们可以不考虑正负然后去构造，存在 $a+x_2+x_3+x_4+\cdots x_{n-2}+x_{n-1}=b$ 即：

$$a+\sum\limits_{i=2}^{n-1}x_i=b$$

因为到这里都还没有什么头绪，所以正文开始。

## 换个角度

首先，我们可以形象地把题目理解为“从 $a$ 到达 $b$ 要走多少路”，每一步可以往回走或者往前走。

首先如果 $n$ 次内都不能从 $a$ 到达 $b$ 肯定不行。

如果能到达呢？那我们要看到达需要几次。

## 分类讨论

**如果同时可以用两种奇偶性不同的步次到达，就一定有解。** 比如：

$$5,0,0,0,10\quad [1,4]$$

你既可以 $2,3$ 到达，也可以 $1,2,2$ 到达，所以一定能满足条件。

**如果只能由一种步次到达，再讨论奇偶性，如果剩下到达后剩下偶数步，就可以，反之不可。** 比如：

$$5,0,0,0,10\quad [2,4]$$

你只能 $2,3$ 或者 $3,2$ 到达，之后剩下一步，不行了。

$$5,0,0,0,0,10\quad [2,4]$$

而这样 $2,3$ 到达之后可以 $2,-2$ 消磨步数，可以到达。

那么依据这样的一种方式就可以解决这个问题了。






---

## 作者：Moeebius (赞：0)

> 好题要点赞。

题意可以转化为，是否可以构造出一组 $x_i \in [-D, -C] \cup [C,D]$，使得 $\sum_{i=1}^{n-1} x_i = B - A$。

进一步，若 $B - A < 0$，则我们可以将所有 $x_i$ 改变符号，故我们只需要考虑 $|B-A|$。

注意到 $[C, D]$ 和 $[-D,-C]$ 中的数，对 $C + D$ 取模后的值都落在 $[C, D]$ 中，因此考虑如下做法：

- 记 $\Delta = |B-A|$，若 $\Delta > D(n - 1)$，则无解；若 $\Delta \in [C(n-1), D(n-1)]$，则有解。
- 否则，记 $f = \Delta \bmod (C + D)$，若 $\exist i$ 满足 $i \in [C(n-1),D(n-1)] \land i \bmod (C + D) = f$，则有解。否则无解。

第一个条件是平凡的；对于第二个条件，其必要性显然，下证充分性。

假设有 $k$ 个 $x_i \in [-D, -C]$，则 $\sum{x_i}$ 的取值范围是 $[-kD+(n-1-k)C, -kC+(n-1-k)D]$，其中 $k \in [0, n-1]$。

将左端点的柿子改写为 $C(n-1)-k(C+D)$，同理右端点也可以改写为 $D(n-1)-k(C+D)$，而我们仅需要考虑 $\Delta \in [0, (n-1)C)$ 的情况，所以只要能找到这样的 $k$ 就一定合法。

假设我们之前找到了 $i$，那么取 $k=\lfloor\dfrac{i}{C+D}\rfloor-\lfloor\dfrac{\Delta}{C+D}\rfloor$，则 $i-k(C+D)=\Delta$；又因为 $i\in [C(n-1),D(n-1)]$，故 $i-k(C+D) \in [C(n-1)-k(C+D), D(n-1)-k(C+D)]$。$\square$

可以轻松做到 $O(1)$。[代码](https://atcoder.jp/contests/agc017/submissions/57207403)。

---

## 作者：Leaper_lyc (赞：0)

思维大好题！！！

第一个格子里是 $A$，最后一个格子是 $B$。相邻两个数的差的绝对值在 $[C,D]$ 之间。

假设我们不知道 $B$ 是多少。我们可以估计 $B$ 的取值范围，在看看 $B$ 是否在这个取值范围内。

先假设每个 $a_{i+1}>a_i$ 的情况，则 $B$ 的最小值为 $A+C(n-1)$，最大值为 $A+D(n-1)$。接下来考虑若有 $k$ 个位置满足 $a_{i+1}<a_i$ 的情况，此时 $B$ 的最小值为 $A+C(n-1)-k(C+D)$，最大值为 $A+D(n-1)-k(C+D)$。

由此得到一个结论：有 $k$ 个差值为负数时，$B$ 的取值范围是 $[A+C(n-1)-k(C+D),A+D(n-1)-k(C+D)]$。

仔细观察、计算，发现区间长度 $len$ 恒等于 $(D-C)(n-1)$。且区间左端的值对 $(C+D)$ 取模也恒为 $A+C(n-1)\bmod (C+D)$，记作 $p$。将 $B\bmod C$只要考虑某个左端点开始的区间能否覆盖到 $B$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long N, A, B, C, D;
signed main() {
	cin >> N >> A >> B >> C >> D;
	int p = (A + (N - 1) * C) % (C + D);
	int q = B % (C + D);
	if (B <= A + D * (N - 1) && (q - p + C + D) % (C + D) <= (D - C) * (N - 1))
		puts("YES");
	else puts("NO");
}
```

---

