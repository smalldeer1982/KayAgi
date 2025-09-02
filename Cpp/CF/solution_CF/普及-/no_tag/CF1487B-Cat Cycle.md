# Cat Cycle

## 题目描述

Suppose you are living with two cats: A and B. There are $ n $ napping spots where both cats usually sleep.

Your cats like to sleep and also like all these spots, so they change napping spot each hour cyclically:

- Cat A changes its napping place in order: $ n, n - 1, n - 2, \dots, 3, 2, 1, n, n - 1, \dots $ In other words, at the first hour it's on the spot $ n $ and then goes in decreasing order cyclically;
- Cat B changes its napping place in order: $ 1, 2, 3, \dots, n - 1, n, 1, 2, \dots $ In other words, at the first hour it's on the spot $ 1 $ and then goes in increasing order cyclically.

The cat B is much younger, so they have a strict hierarchy: A and B don't lie together. In other words, if both cats'd like to go in spot $ x $ then the A takes this place and B moves to the next place in its order (if $ x < n $ then to $ x + 1 $ , but if $ x = n $ then to $ 1 $ ). Cat B follows his order, so it won't return to the skipped spot $ x $ after A frees it, but will move to the spot $ x + 2 $ and so on.

Calculate, where cat B will be at hour $ k $ ?

## 说明/提示

In the first and second test cases $ n = 2 $ , so:

- at the $ 1 $ -st hour, A is on spot $ 2 $ and B is on $ 1 $ ;
- at the $ 2 $ -nd hour, A moves to spot $ 1 $ and B — to $ 2 $ .

 If $ n = 3 $ then: - at the $ 1 $ -st hour, A is on spot $ 3 $ and B is on $ 1 $ ;
- at the $ 2 $ -nd hour, A moves to spot $ 2 $ ; B'd like to move from $ 1 $ to $ 2 $ , but this spot is occupied, so it moves to $ 3 $ ;
- at the $ 3 $ -rd hour, A moves to spot $ 1 $ ; B also would like to move from $ 3 $ to $ 1 $ , but this spot is occupied, so it moves to $ 2 $ .

In the sixth test case:

- A's spots at each hour are $ [5, 4, 3, 2, 1] $ ;
- B's spots at each hour are $ [1, 2, 4, 5, 2] $ .

## 样例 #1

### 输入

```
7
2 1
2 2
3 1
3 2
3 3
5 5
69 1337```

### 输出

```
1
2
1
3
2
2
65```

# 题解

## 作者：7KByte (赞：7)

观察一下。

首先考虑 $n$ 为偶数的情况，不难发现两只猫并不会相遇，$Ans=(k-1) \bmod n +1$。

然后考虑 $n$ 为奇数的情况，两只猫每$\frac{n-1}{2}$秒相遇一次，每次相遇 $B$ 猫位置增加 $\frac{n+1}{2}$，令周期 $T=\frac{n-1}{2}$ ，则 $Ans=(\left\lfloor \frac{k}{T}\right\rfloor\times(T+1)+k\bmod T)\bmod n +1$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int n,k;
void solve(){
	scanf("%d%d",&n,&k);
	if(n&1){
		k--;
		int w=(n-1)>>1,mid=(n+1)>>1;
		int now=k/w;k%=w;
		int st=(now*mid)%n+1;
		printf("%d\n",(st-1+k)%n+1);
	}
	else{
		printf("%d\n",(k-1)%n+1);
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：张语诚ZYC (赞：5)

## 题意回顾

猫 A 和猫 B ，共同拥有 $n$ 个休息地点排成一个环，位置顺时针编号为 $1$ 至 $n$，他们要选择休息位置。

猫 A 在第 $1$ 小时会选择休息位置 $n$，接下来每过一小时它就会逆时针移一个位置，也就是说它选择的位置的序列为 $n$,$n-1$,$n-2$, $...$ ,$3$,$2$,$1$,$n$,$n-1$,$...$,$n$,$n−1$,$n−2$,$...$,$3$,$2$,$1$,$n$,$n−1$,$...$ 。

猫 B 在第 $1$ 小时会选择休息位置 $1$，接下来每过一小时它就会顺时针移一个位置，也就是说它选择的位置的序列为 $1$,$2$,$3$,$...$,$n-1$,$n$,$1$,$2$,$...$,$1$,$2$,$3$,$...$,$n−1$,$n$,$1$,$2$,$...$ 。

特别的，因为猫 A 比猫 B 老，所以猫 A 比猫 B 地位高一些，因此当两只猫相中了同一个位置时，由猫 A 占领这个位置，猫 B 会再顺时针移一个位置到下一个位置。

## 题目分析

### 确定方法

这种题无非就两种方法：**模拟**和**找规律**。

~~已知洛谷测评机则测评速度大约是~~ $10^{9}$。通过阅读数据规模：

$1 \leq T \leq 10^{4}$;

$2 \leq n \leq 10^{9}$;

$1 \leq k \leq 10^{9}$;

发现**模拟会超时**，所以只能**找规律**。

### 具体分析

#### 当 $n \bmod 2 = 0$ 时：

当 $n=2$ 时：很明显，猫 A 和猫 B 每一个小时会交换一次位置。不难发现，第 $k$ 小时猫 $B$ 在 $k \bmod n$ 处。

当 $n=4$ 时：如下图。


[![](https://img.imgdb.cn/item/605185c6524f85ce297e73d6.png)](https://img.imgdb.cn/item/605185c6524f85ce297e73d6.png)

此时，猫 A 在 $4$ ，猫 B 在 $1$ 处。一小时后，猫 A 在 $3$ ，猫 B 在 $2$ ,再过一个小时，猫 A 在 $2$ ，猫 B 在 $4$ ,第 $k$ 小时猫 $B$ 也在 $k \bmod n$ 处。

所以：当 $n \bmod 2 = 0$，**猫 B 不会和猫 A 的位置起冲突，第 $k$ 小时猫 $B$ 也在 $k \bmod n$ 处。**

#### 当 $n \bmod 2 = 1$ 时：

当 $n=3$ 时：如下图。

[![](https://img.imgdb.cn/item/60518a1c524f85ce298160eb.png)](https://img.imgdb.cn/item/60518a1c524f85ce298160eb.png)

此时，猫 A 在 $3$ ，猫 B 在 $1$ 处。一小时后，猫 A 在 $2$ ，猫 B 本应该在 $2$ ，但是要给猫 A 让位置，所以在 $3$ ，再过一个小时，猫 A 在 $1$ ，猫 B 在 $2$ ，再过一个小时，猫 A 在 $3$ ，猫 B 在 $1$ 处。我们发现，每相遇一次，两只猫相遇 $2$ 次，设 $t$ 是猫 B 移动次数，不难推出，当 $t \bmod n = 0$,猫 B 在位置 $1$；否则，第 $k$ 小时猫 B 在 $t \bmod n$ 处。

---

## 作者：felixshu (赞：2)

[我是传送门](https://www.luogu.com.cn/problem/CF1487B)

## 题目描述

猫 $A$ 与猫 $B$ 有 $n$ 个休息点。每小时会移动。猫 $A$ 是从 $n$ 向 $1$ 移动。猫 $B$ 是从 $1$ 向 $n$ 移动，无限循环。若猫 $A$ 与猫 $B$ 相遇，则猫 $B$ 会移动到下一个它要移动到位置。求 $k$ 小时后猫 $B$ 的位置。

## 分析

$1≤T≤10^4;2≤n≤10^9;1≤k≤10^9;$

如果直接模拟必然超时。既然不能模拟，就只能找规律了。

可以发现：

- 可以发现当 $n$ 为偶数时，两只猫不会相遇。答案 $k-1 \pmod n +1$。

- 当 $n$ 为奇数时，两只猫每移动 $n÷2$ 次就会相遇一次。额外移动的距离就是相遇的次数。答案  $\frac{k-1}{T}+k-1$。

## 下面是 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
	int n,k;
    while (t--) 
	 { 
    cin>>n>>k;
        int k1=(n-1)/2;
        if (n % 2==1) 
		{
          cout<<((k+(k-1)/k1)-1)%n+1<<endl;
        } 
        else
		{
          cout<<(k-1)%n+1<<endl;
        }
    }
    return 0;
}
```



---

## 作者：33aaron (赞：2)

## 题目大意
两只猫：A和B。它们在睡觉。每小时它们会移动它们的睡觉位置。其中A猫的移动顺序是从 $n$ 移动到 $1$，无限循环；B猫的移动顺序是从 $1$ 移动到 $n$，无限循环。若A猫与B猫相遇，则B猫会移动到下一个它要移动到位置。询问 $k$ 小时后B猫的位置。
## 题目分析
数据大，模拟必超时。我们可以发现当 $n$ 为偶数时，两只猫不会相遇；当 $n$ 为奇数时，两只猫每移动 $n ÷ 2$ 次就会相遇一次。

我们使用取余的方式来确定最后B猫的位置，也就是算出B猫移动总次数除以 $n$ 的余数，这个余数如果不等于 $0$，则B猫所在的位置就是这个余数，否则B猫就在 $n$ 的位置。
## AC Code
```cpp
#include <iostream>
using namespace std;
int main() {
    int times;
    cin >> times;
    while (times--) {
        int n, k;
        cin >> n >> k;
        if (n % 2) {
            if (k - 1) {
                if ((k + (k - 1) / (n / 2)) % n) cout << (k + (k - 1) / (n / 2)) % n << endl; 
                else cout << n << endl;
            } else {
                cout << 1 << endl;
            }
        } else {
            if (k % n) cout << k % n << endl;
            else cout << n << endl;
        }
    }
    return 0;
}
```

---

## 作者：dalao_see_me (赞：1)

## 题目大意
有一个圈，圈上有 $n$ 个点，编号按顺时针为 $1$ 到 $n$。两只猫转圈，A 猫在 $n$ 位置朝着逆时针走，B 猫在 $1$ 位置朝着顺时针走。

因为 A 猫比较有资历，当 A 猫和 B 猫在同一位置时，B 猫额外移动一格。
## 做法
显然这是**找规律题**。另外，我们令 $m=k-1$。

当 $n\mod 2=0$ 时，A 猫和 B 猫永远不会在同一位置上，不难得出，此时答案为 $(m\mod n)+1$。

当 $n\mod 2=1$ 时，A 猫和 B 猫两次相遇间隔时间为 $T=\frac{n-1}{2}$。显然 B 猫的额外移动距离就是相遇次数，相遇次数为总时间除以相遇间隔时间（当然是向下取整啦）。

于是此时的答案我们就得出来了，为 $(\frac{m}{T}+m)$ 除以 $n$ 的余数再加上 $1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int _,n,k;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	_=read();
	while(_--){
		n=read();k=read();
		k--;
		if(n&1){
			int p=n-1>>1,Move=k/p;//p为两次相遇间隔时间，Move为额外移动距离
			printf("%d\n",(Move+k)%n+1);
		}
		else printf("%d\n",k%n+1);
	}
	return 0;
}
```


---

## 作者：CodingOIer (赞：0)

## CF1487B Cat Cycle 题解

### 思路分析

在这道题中，很明显是一道数学题，因为有十分明显的数据范围：

$$
n \le 10 ^ {9} , k \le 10 ^ {9}
$$

分析如下：

- 对于 $n$ 为偶数的情况下，猫 $A$ 和猫 $B$ 永远不可能相遇，所以直接输出 $( k - 1 ) \bmod n$。
- 对于 $n$ 为奇数的情况下，猫 $A$ 和猫 $B$ 的相遇周期如下：

$$
cycle \gets \frac{n - 1}{2}
$$

猫 $B$ 多走的路程为 $\lfloor ( k - 1 ) \div cycle \rfloor$，最后猫 $B$ 一共走的路程再对 $n$ 取模后即为答案，即：

$$
ans \gets ( k + \lfloor ( k - 1 ) \div cycle \rfloor - 1 ) \bmod n + 1
$$

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t;
long long n, k;
long long cycle;
int main()
{
    scanf("%lld", &t);
    for (long long i = 1; i <= t; i++)
    {
        scanf("%lld%lld", &n, &k);
        if (n % 2 == 0)
        {
            printf("%lld\n", (k - 1) % n + 1);
        }
        else
        {
            cycle = (n - 1) / 2;
            printf("%lld\n", ((k + (k - 1) / cycle) - 1) % n + 1);
        }
    }
    return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## 题目大意：

在一个有 $n$ 个点的圆形上，猫 A 最开始在 $n$ 点，猫 B 最开始在 $1$ 点，猫 A 逆时针走，猫 B 顺时针走。每小时走一格。若猫 A 与猫 B 到同一个位置，猫 B 往前一格。

给你一个 $n$ 和 $k$，求 $k$ 时后猫 B 在什么位子。

## Solution:

很容易看出，当 $n$ 为偶数时两猫永不相遇，所以直接取模即可。

再看 $n$ 为奇数。

两猫只有相遇时才会有跳格的行为，而两猫每 $\frac{n}{2}$ 时变一次，猫 $B$ 则会走 $\frac{n+1}{2}$ 格。

令 $x=\frac{n-1}{2}$。

那答案就是 $(\frac{k}{x}\times(x+1)+k \bmod x) \bmod (n+1)$。

最后输出即可。

---

## 作者：haokee (赞：0)

## 题意分析

我们可以先画图，就可以知道在 $n$ 为偶数的情况下，他们永远不会重叠，直接计算 $(k-1)\bmod n+1$。（当 $k=n$ 的情况下，直接计算 $k\bmod n$ 会导致等于 0，因此需要先 $-1$ 再 $+1$）

![](https://cdn.luogu.com.cn/upload/image_hosting/kyi5p2x3.png)

对于 $n$ 为奇数的情况下，我们先计算它在可以重叠的情况下需要移动多少次，再计算挪位置的次数。我们可以发现，在 $n=7$ 的情况下，移动 $3$ 次就需要移位置，那么在 $n$ 的情况下，移动 $\lfloor n\div 2 \rfloor$ 次就需要换一次位置，总共需要换位置的次数是 $(k-1)\div \lfloor n\div 2\rfloor$，按照之前的方式取模即可。

## 代码

```cpp
#include <iostream>
using namespace std;

int t, n, k, p;

int main() {
  for (cin >> t; t; --t) {
    cin >> n >> k;
    if (!(n & 1)) {  // 如果不会重叠
      p = (k - 1) % n + 1;  // 直接计算
    } else {
      p = ((k - 1)               // 原本需要走的次数，这里提前-1
        + ((k - 1) / (n >> 1)))  // 需要多走的步数
        % n + 1;                 // 取模
    } 
    cout << p << '\n';
  }
  return 0;
}
```

---

## 作者：Fa1thful (赞：0)

### 题意：
有两只猫在一个环上运动， `A` 猫逆时针运动， `B` 猫顺时针运动，当他们撞上时 `B` 会主动让位（顺时针再走一次），求第 `k` 时刻 `B` 猫的位置。
### 分析：
我们看到数据范围 $2\le n,k\le10^9$，一开始模拟两只猫的位置肯定会TLE。所以我们可以判断在什么时候两只猫会撞上。一个小猜想：和 `n` 的奇偶性有关。

当 `n` 为偶数时

![](https://cdn.luogu.com.cn/upload/image_hosting/u1e9pscz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
我们发现 `A` 和 `B` 会擦肩而过，不会碰上，所以直接模拟就行。

当 `n` 为奇数的时候

![](https://cdn.luogu.com.cn/upload/image_hosting/qao70y0b.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
我们发现会相遇。

所以只有 `n` 为奇数的时候才需要考虑 `B` 让位的情况，所以直接算就行。
### 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		if (n % 2 != 0)    //要让位 
		{
			if (k - 1 != 0)   //如果可以走 
			{
				if ((k + (k - 1) / (n / 2)) % n != 0) //用模来确定位置 
				{
					cout << (k + (k - 1) / (n / 2)) % n << endl;
				}
				else cout << n << endl;   //如果还是原点 
			}
			else cout << 1 << endl; //走不了 
		}
		else
		{
			if (k % n != 0)  //偶数直接算 
			{
				cout << k % n << endl;
			}
			else cout << n << endl;
		}
	}
	return 0;
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1487B)

## 思路

这题如果直接模拟的话一定超时，但我们可以从样例中找规律。

- 当 $n$ 为偶数时，两只猫不会相遇，只要输出$ (k-1) \bmod  n +1$ 即可。

- 当 $n$ 为奇数时，两只猫每移动 $n\div2$ 次就会相遇一次，答案为$\frac{k-1}{T}+ k - 1$。

结论有了，代码也不会太难。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin>>t;
    int n,k;
    while(t--) 
    { 
    	cin>>n>>k;
        int K=(n-1)/2;
        if(n%2==1)cout<<((k+(k-1)/K)-1)%n+1<<endl;//n为奇数时
        else cout<<(k-1)%n+1<<endl;//n为偶数时
    }
    return 0;
}
```


---

