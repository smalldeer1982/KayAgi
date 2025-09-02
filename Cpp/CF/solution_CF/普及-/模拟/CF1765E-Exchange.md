# Exchange

## 题目描述

Monocarp is playing a MMORPG. There are two commonly used types of currency in this MMORPG — gold coins and silver coins. Monocarp wants to buy a new weapon for his character, and that weapon costs $ n $ silver coins. Unfortunately, right now, Monocarp has no coins at all.

Monocarp can earn gold coins by completing quests in the game. Each quest yields exactly one gold coin. Monocarp can also exchange coins via the in-game trading system. Monocarp has spent days analyzing the in-game economy; he came to the following conclusion: it is possible to sell one gold coin for $ a $ silver coins (i. e. Monocarp can lose one gold coin to gain $ a $ silver coins), or buy one gold coin for $ b $ silver coins (i. e. Monocarp can lose $ b $ silver coins to gain one gold coin).

Now Monocarp wants to calculate the minimum number of quests that he has to complete in order to have at least $ n $ silver coins after some abuse of the in-game economy. Note that Monocarp can perform exchanges of both types (selling and buying gold coins for silver coins) any number of times.

## 说明/提示

In the first test case of the example, Monocarp should complete $ 4 $ quests, and then sell $ 4 $ gold coins for $ 100 $ silver coins.

In the second test case, Monocarp should complete $ 400000 $ quests, and then sell $ 400000 $ gold coins for $ 10 $ million silver coins.

In the third test case, Monocarp should complete $ 1 $ quest, sell the gold coin for $ 50 $ silver coins, buy a gold coin for $ 48 $ silver coins, and then sell it again for $ 50 $ coins. So, he will have $ 52 $ silver coins.

In the fourth test case, Monocarp should complete $ 1 $ quest and then sell the gold coin he has obtained for $ 50 $ silver coins.

## 样例 #1

### 输入

```
4
100 25 30
9999997 25 50
52 50 48
49 50 1```

### 输出

```
4
400000
1
1```

# 题解

## 作者：cff_0102 (赞：2)

### 题面翻译

可以随时且不限次数地进行以下交易：

+ 使用 $1$ 个金币买入 $a$ 个银币。
+ 使用 $b$ 个银币买入 $1$ 个金币。

一次探险可以获得 $1$ 个金币，求需要通过完成探险来争取至少 $n$ 个银币。有多测。

### 题解

显然需要对 $a,b$ 大小进行讨论。

- 当 $a>b$ 时，先探险 $1$ 次获得 $1$ 金币，再变成 $a$ 银币，接着拿其中的 $b$ 银币换 $1$ 金币，再换 $a$ 银币，……，最后就能实现从 $1$ 到 $+\infty$ 的过程，这个过程需要探险 $0$ 次。那么在这种情况下，总共只需要探险 $1$ 次，实现从 $0$ 到 $1$ 的过程，就能一生二，二生三，三生万物了。
- 当 $a=b$ 时，换币没什么卵用，探险 $\lceil\frac{n}{a}\rceil$ 次，就能换到 $\lceil\frac{n}{a}\rceil\times a\ge n$ 银币了（在 $a|n$ 时取等）。
- 当 $a>b$ ，将 $b$ 银币换 $1$ 金币绝对是不可取的，那么还是选择不换，跟第二种情况一样探险 $\lceil\frac{n}{a}\rceil$ 次就行了。

### 代码

小知识：用 `ceil()` 即可实现浮点数向上取整，省了判断或者不必要的脑力风暴。但是！这个函数的返回值是 `double`！还会有[神奇的精度误差](https://www.luogu.com.cn/record/106648349)！所以还需要转为 `int`！[然后就 A 了](https://www.luogu.com.cn/record/106649244)！~~太神奇了~~！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){//别忘了有多测 
		int n,a,b;cin>>n>>a>>b;
		if(a>b)cout<<"1\n";//第一种情况，记得换行
		else cout<<(int)ceil(1.0*n/a)<<endl;//后面两种情况，其中乘1.0是转double，前面加(int)是转回int类型避免精度问题 
	}
	return 0;
}
```


---

## 作者：hanjinghao (赞：1)

题意：一枚金币可以换 $ a $ 枚银币，$ b $ 枚银币可以换一枚金币。问想要拥有 $ n $ 枚银币，最开始的时候至少要拥有多少枚金币。

============================

如果 $ a $ 大于 $ b $，那么只要有一枚金币就够了。因为可以把一枚金币换成 $ a $ 枚银币，再从 $ a $ 枚银币中抽出 $ b $ 枚，换成一枚金币。如此反复操作，银币会越来越多，最终一定能达到 $ n $。

否则，一定是不用银币换金币最优。因为用银币是用金币换来的，而我们的目标是获得 $ n $ 枚银币。先用金换银，再用银换金会导致银币的数量变少。因此，答案即为 $ n $ 除以 $ a $ 上取整。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T, n, a, b;
	read(T);
	while (T--)
	{
		read(n);
		read(a);
		read(b);
		if (a > b) puts("1");
		else writeln((n + a - 1) / a);
	}
	return 0;
}
```

---

## 作者：MornHus (赞：1)

**可能是史上最简单的贪心题**

仔细阅读题目后，我们敏锐的发现：
 
 - 金币可以买银币
 - 银币可以买金币
 - 汇率可能不等
 
 给了我们一个思路：~~投机倒把~~赚差价
 
 对于 $a$ 和 $b$ 的大小关系我们分两种情况讨论：
 
 1. 若 $a>b$ 我们发现一个金币买入的银币可以兑换一个以上金币！如此我们只需冒险一次就可以无限利用差价赚取我们想要的银币数目。
 
 2. 若 $a \le b$ 我们刚刚那个策略就会亏本，所以我们干脆不买入金币，此时我们需要进行的冒险次数就是 $n÷a$ 向上取整
 
 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    double n,a,b;
    int t;
    cin>>t;
    while(t--){
        cin>>n>>a>>b;
        if(a>b){
            cout<<1<<endl;
        }else{
            cout<<(int)ceil(n/a)<<endl;
        }
    }
    return 0;
}
```

---

## 作者：yanxu_cn (赞：1)

### 题意简述
要得到 $n$ 个银币，求要得到至少多少个金币。

### 分析
经过简要的分析，我们可以发现题目实际上有两种情况：

+ 对于 $a>b$ 时，我们可以发现，如果先拿 $1$ 个金币换 $a$ 个银币，再拿其中的 $b$ 个银币去换 $1$ 个金币，就能赚到剩下的 $a-b$ 个金币。经过反复操作，只需 $1$ 个金币，就能得到要求的银币。
+ 对于 $a\le b$ 时，用 $b$ 个银币换 $1$ 个金币的操作会使银币的数量减少，所以我们不进行这样的操作，则需要 $\lceil n \div a\rceil$ 个金币才能达到目的。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,a,b,n;
	cin>>t;
	while(t--)
	{
		cin>>n>>a>>b;
		if(a>b)
		{
			cout<<1<<'\n';
		}
		else
		{
			cout<<(n+a-1)/a<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：undefined_Ryan (赞：1)

转化题意：需要 $n$ 个银币，至少需要几个金币来交易得到。

将交易操作分为 $2$ 种：
1. 消耗 $1$ 个金币获得 $a$ 个银币；
2. 消耗 $b$ 个银币获得 $1$ 个金币。

如果 $a>b$，那么只要有 $1$ 个金币，按照 $1\rightarrow2$ 的顺序交易，就可以产生 $a-b$ 个银币；足够多次即可得到任何数量的银币。

否则，进行交易 $2$ 是没有好处的，只进行第 $1$ 种交易，需要 $\lceil\frac na\rceil$ 个金币。

附上代码：
```cpp
#include <iostream>
using namespace std;
int t,n,a,b;
int main() {
    cin>>t;
    for (int i=1;i<=t;i++) {
        cin>>n>>a>>b;
        if (a>b) cout<<"1\n";
        else cout<<(n-1)/a+1<<endl;
    }
}
```

---

## 作者：Neilchenyinuo (赞：0)

## 解题思路

##### 可以把题意转化成：需要 $n$ 个银币，至少需要几个金币来交易得到。

1. 当 $a>b$ 时，就可以用一个金币换多个银币，然后用少量的银币换一个金币。那不就能一直换下去，一直到达到 $n$ 为止，所以直接输出 $1$。

2. 当 $a<b$ 时，就不要交换了（甚至会越换越少），答案就是 $n$ 除以 $a$ 向上取整。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,a,b,n;
	cin>>t;
	while(t--)
	{
		cin>>n>>a>>b;
		if(a>b)
			cout<<"1\n";
		else
			cout<<(n+a-1)/a<<"\n";
	}
	return 0;
}

```


---

## 作者：Underage_potato (赞：0)

读题可知，我们要拿到 $n$ 个银币，而一次探险可得一枚金币。

金币与银币的兑换规则如下：

- 1 个金币 $= a$ 个银币。

- $b$ 个银币 $ =$ 1 个金币。

通过兑换规则可知，如果 $a>b$ 那么在探险一次获得一枚金币后便可无限兑换。

而 $a \leq b$ 时则没有必要进行兑换，只需数次探险可完成目标。

## Code：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n,a,b;
		cin>>n>>a>>b;
		if(a>b){
			cout<<1<<endl;
			continue;
		}
		else{
			cout<<ceil(n*1.0/a)<<endl;//注意要*1.0后向上取整
			continue;
		}
	}
	return 0;
}
```

---

## 作者：_xbt (赞：0)

**题目传送门** <https://www.luogu.com.cn/problem/CF1765E>

首先观察题目后发现，这应该是一道很简单的贪心题。

这道题有以下几个关键的地方：

1. 金币和银币都可以按照一定的规则转换；
2. 每次的转换个数不一定。

思路就是利用金银币转换个数不同**赚差价**。

当 $a>b$ 时，只需要进行 $1$ 次探险，就可以一直互相转换，就能得到至少 $n$ 个银币。

当 $a \le b$ 时，再利用刚才的思路的话就会不赚反亏，所以就要进行 $\left\lceil n \div a \right\rceil$ 次探险才能至少 $n$ 个银币。

# $code$

``` cpp
#include<iostream>
#include<cmath>
using namespace std;
int t,n,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>a>>b;
		if(a>b) cout<<1<<endl;
		else cout<<int(ceil(n*1.0/a))<<endl;
		//一定要强制转换成int类型，不然会错，我就因为这个错了QAQ
	}
}
```

---

## 作者：FstAutoMaton (赞：0)

看到这题数据范围，肯定是要 $\text{O}(T)$ 到 $\text{O}(T\log n)$ 左右的时间复杂度。但是根据题意，貌似无法将基础的暴力优化成 $\log$ 级别的算法，所以考虑 $\text{O}(1)$ 时间复杂度。

那么 $O(1)$ 复杂度基本就是数学了。我们进行思考可以发现，如果你用一枚金币买到的银币数无法获得利益，即 $a\le b$，就不进行交易（应为此时进行交易无法把手中的金币数量变的更多，不如不进行交易）。否则，可以不断的进行交易，这样金币数量越来越多，只需要一次探险即可。所以，对 $a$ 与 $b$ 的数量关系进行分类讨。$a\le b$ 则直接一直进行探险，直到金币的数量足够交易成 $n$ 枚银币。否则就探险一次，然后不断进行交易，代码如下：

```
#include <bits/stdc++.h>
using namespace std;
int T;
int main() {
  for( cin >> T; T; T -- ) {
    int n, a, b;
    cin >> n >> a >> b;
    if( a > b ) {
      cout << 1 << endl;
    }
    else {
      cout << n / a + bool( n % a ) << endl;
    }
  }
}
```


---

