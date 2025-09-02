# [ABC059D] Alice&Brown

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc059/tasks/arc072_b

AliceとBrownはゲームをするのが好きです。今日は以下のゲームを思いつきました。

$ 2 $つの山があり、はじめに$ X,\ Y $個の石が置かれています。 AliceとBrownは毎ターン以下の操作を交互に行い、操作を行えなくなったプレイヤーは負けとなります。

- 片方の山から $ 2i $ 個の石を取り、そのうち $ i $ 個の石を捨て、残りの $ i $ 個の石をもう片方の山に置く。ここで、整数 $ i\ (1≦i) $ の値は山に十分な個数の石がある範囲で自由に選ぶことができる。

Aliceが先手で、二人とも最適にプレイすると仮定したとき、与えられた $ X,\ Y $ に対しどちらのプレイヤーが勝つか求めてください。

## 说明/提示

### 制約

- $ 0≦\ X,\ Y\ ≦\ 10^{18} $

### Sample Explanation 1

Aliceは $ 2 $ 個石のある山から $ 2 $ 個取るしかありません。その結果、山の石の数はそれぞれ $ 0,\ 2 $ 個となり、Brownは $ 2 $ 個の石を取り、山の石の数はそれぞれ $ 1,\ 0 $ 個となります。 Aliceはこれ以上操作を行うことができないので、Brownの勝ちです。

## 样例 #1

### 输入

```
2 1```

### 输出

```
Brown```

## 样例 #2

### 输入

```
5 0```

### 输出

```
Alice```

## 样例 #3

### 输入

```
0 0```

### 输出

```
Brown```

## 样例 #4

### 输入

```
4 8```

### 输出

```
Alice```

# 题解

## 作者：liangbowen (赞：31)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT2400)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16702856.html)

博弈论真好玩！

## 思路

显然，$\begin{cases}n=0\\m=0\end{cases}\space\begin{cases}n=1\\m=0\end{cases}\space\begin{cases}n=0\\m=1\end{cases}\space\begin{cases}n=1\\m=1\end{cases}\space$时，先手必输。

于是可以猜测，当 $|n - m| \le 1$ 时，先手必输；否则先手必胜。~~然后 AC 了，于是下一题。~~

接下来，证明这个结论是正确的。

当 $|n - m| \le 1$ 时，假设先手从第一堆中取出了 $2x$ 个石子。

根据题目，石子数会变成：$\begin{cases}n^{'} = n - 2x\\m^{'} = m+ x\end{cases}\space$ 这时轮到后手。

此时，后手只需要在 $m^{'}$ 里同样取 $2x$ 个石子即可。由于 $n$ 和 $m$ 差最大为 $1$，所以 $m^{'}$ 一定会大于 $2x$。

那么，石子数会变成：$\begin{cases} n^{''} = n^{'} + x = n - x\\m^{''} = m^{'} - 2x = m - x\end{cases}\space$ 于是 $|n^{''} - m^{''}|$ 同样会小于等于 $1$。

这样每次，先手都会获得 $|n - m| \le 1$ 的石子数。由于每次 $n$ 和 $m$ 都会减少，所以迟早会变成最开始的四种情况之一。

综上，$|n - m| \le 1$ 时先手必败。

那 $|n - m| > 1$ 呢？先手很容易将情况变为 $|n - m| \le 1$，于是现在的后手，变成了上一种情况的先手。

故 $|n - m| > 1$ 时先手必胜。

于是就证毕啦！

## 完整代码

这还需要代码吗？

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
int main()
{
	long long n, m;
        cin >> n >> m;
	if (abs(n - m) <= 1) puts("Brown");
	else puts("Alice");
	return 0;
}
```

---

## 作者：Anaxagoras (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/AT2400)

题意：

有两堆石子，数量分别为 a b，Alice 先手，在能拿的前提下，每人每次能拿 $ 2n(n\ge1) $ 个石子，求谁最后一次拿。

思路：

如果 $ \left | a-b \right | =1 $，那么 Alice 将会一直遭遇 $ \left | a-b \right | =1 $ 的情况，某次轮到 Alice 时，一堆为 1，另一堆为 0，Alice 败。

如果 $ \left | a-b \right | =0 $，那么在轮到 Brown 时，将会一堆为 3，另一堆为 0，轮到 Alice 时，就会有两堆都是 1 的情况，即 $ \left | a-b \right | =0 $， Alice 败。

其他情况 Alice 都会赢，于是就可以直接 $ \Theta(1) $ 解决，如果 $ \left | a-b \right | \le 1 $， Brown 胜，否则 Alice 胜。

AC Code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long a,b;
  cin>>a>>b;
  if(abs(a-b)<=1)
    cout<<"Brown\n";
  else
    cout<<"Alice\n";
  return 0;
}

```

帮忙点个赞吧！蟹蟹！

---

## 作者：Farkas_W (赞：6)

$\quad$~~模拟赛考了此题，人均100分~~

$\quad$可以发现有两种状态可以互相转化( $x$，$y$ 为两堆石子的数量)，一种是 $abs(x-y)<=1$ ，可以发现这种情况下要么已经结束游戏，要么转化为 $abs(x-y)>1$，没有其他可能，而对于另一种状态 $abs(x-y)>1$，可以发现这种状态是输不了的，因为一定有一个数大于 $1$，可以发现此时又可以一步操作转化为第一种状态，即 $abs(x-y)<=1$。

$\quad$因为第一种状态没有选择的余地，且有输的可能，只能转化为另外一种状态，第二种状态显然是不会输的，所以当 $Alice$ 初始为第二种状态时，他肯定会选择转化为第一种状态，$Bob$ 没有办法，只能将其转化为第二种状态，这样如此往复，数字越来越小，肯定是 $Bob$ 输，$Alice$ 赢，若 $Alice$ 初始为第一种状态，显然是 $Bob$ 赢，$Alice$ 输。

$\quad$所以只需要判断 $abs(x-y)$ 即可

提供一个 @Quick_Kk 的一个考场神奇思路：

首先设第一堆石头有 $N$ 个，第二堆石头有 $M$ 个，根据题目，可以列得式子：
$$\begin{cases}N-2k \\ M+k\end{cases}$$

$$\begin{cases}N+k \\ M-2k\end{cases}$$

由题可知：想让 $Alice$ 赢不了，当上面的两组式子对应三组情况，分别为

$$\begin{cases}N+k=1 \\ M-2k=0\end{cases}$$
$$\begin{cases}N+k=1 \\ M-2k=1\end{cases}$$
$$\begin{cases}N+k=0 \\ M-2k=1\end{cases}$$
$$和$$
$$\begin{cases}N-2k=1 \\ M+k=0\end{cases}$$
$$\begin{cases}N-2k=1 \\ M+k=1\end{cases}$$
$$\begin{cases}N-2k=0 \\ M+k=1\end{cases}$$

解出可得：$|N-M|<=1$

玄学可得如果第一次不满足这样的条件，那么 $Alice$ 就一定输不了。

~~不会吧，这题也想要代码~~
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define int long long
#define il inline
#define inf 1e18+5
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
signed main()
{
  int n=read(),m=read();
  if(abs(n-m)<=1)puts("Brown");
  else puts("Alice");
  return 0;
}
```

---

## 作者：first_fan (赞：6)

题意翻译：

>现有两堆石子，Alice和Brown以此进行游戏，规则如下：

>* `Alice先手`，两方分别按照`回合制`取石子

>* 每个人每回合可以任意从任一堆中取出`2的倍数个`石子`（前提是该堆里有这么多石子）`。

>* 当一方`无法进行取石子操作`时视作此方失败。

>现给出石子数量n,m(0≤n,m≤1018)(0≤n,m≤10^{18})(0≤n,m≤1018)，请你输出胜方名称(Alice|Brown)。

一道博弈好题。对于博弈，我的观点一直是：先自己跟自己试试，再暴力搜索打张表，观察输入数据与胜败态的关系，最后据此在线性甚至O(1)的时限内完成。

### 1.和自己试试

（此处可以请读者试试看，了解游戏规则，摸索必胜策略，此处不再赘述）

### 2.暴搜打表

此处仅放上[搜索函数](https://i.loli.net/2019/07/22/5d35b04172eeb92283.png)作为参考，这里是打表的结果（仅0-9，Alice视角）

![](https://i.loli.net/2019/07/22/5d35b1d11b12b87107.png)

发现什么没有？`(n-1,n,n+1) n->lose`

也就是说Alice在两堆石子数之差不超过1的情况下必败。

### 3.写出正解

那么思路就不必细讲了：`读入、作差、判断、输出`均在`O(1)`完成。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

int main()
{
	return 0&(int)puts(abs(read()-read())<=1?"Brown":"Alice");
}//主函数一行解决。
```

总结一下：解决此题我们没用到严谨的证明，但是暴力打表帮助我们找到了规律，得到了答案。

---

## 作者：MC小萌新 (赞：5)

结论比较易证的博弈论题。

### 题目分析

先说结论：当 $ |a-b|>1 $ 时先手 Alice 必胜，否则后手 Brown 必胜。

验证发现，结论是对的，但是为什么呢？

我们不妨证明一下。

当 $ |a-b| > 1 $ 时，先手显然可以通过一步操作，把两堆的数量变成 $ |a-b| \leq  1 $，此时相当于转化为 Brown 为先手，$ |a-b|\leq 1 $。

当 $ |a-b| \leq  1 $ 时，先手在一堆中拿掉一些后，后手可以模仿先手在另一堆中拿掉相同的个数，所以最终先手必败。

综上，得证。

### 代码实现
注意```long long```。
```cpp
#include <iostream>
using namespace std;
#define ll long long
ll a,b;
int main(){
    cin>>a>>b;
    if(abs(a-b)>1)
        cout<<"Alice"<<endl;
    else
        cout<<"Brown"<<endl;
    return 0;
    
}
```


---

## 作者：Fishing_Boat (赞：2)

首先，我们可以得到当石子只剩 $1$、$1$ 或 $1$、$0$，先手方必败，由此我们猜测 $\vert x-y \vert \le 1$ 时 Brown 必胜，否则 Alice 必胜。

- 当 $\vert x-y \vert > 1$ 时，则先手可以通过一次操作变成 $\vert x-y \vert \le 1$。
- 当 $\vert x-y \vert \le 1$ 时，则后手一定可以在一堆中拿走和先手数量一样的石子，知道先手无法再拿。

这样就可以通过 $O(1)$ 解决。

---

## 作者：losed_xdl (赞：0)

solution
------------
- 结论：$|a-b| \le 1$，`Brown` 胜；否则 `Alice` 胜。

- 证明：

1. 当 $|a-b| \le 1$，先手取多少个，后手就在另一堆取多少个。

2. 当  $|a-b| > 1$，说明 $a$ 和 $b$ 一个奇数一个偶数，先手总能将其取成 $(a,a+1)$ 或 $(b,b+1)$，和第一种情况一样，但是是后手先动，所以是先手赢。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long n, m;
	cin >> n >> m;
	if (abs(n - m) <= 1) cout << "Brown" << endl;
	else cout << "Alice" << endl;
	return 0;
}
```

注意：十年AT一场空，不打endl见祖宗。做AT的题目，一定要打换行。

---

## 作者：Xdl_rp (赞：0)



设总共有 $a,b$ 两堆.
- 当 $|a-b| \le 1$ 时

	先手取多少个，后手就在另一堆取多少个，
    
    后手必胜。
    
    
- 当 $|a-b| \ge 2$ 时
   
   1. 当 $|a-b|$ 为奇数
   
   		$a$ , $b$ 一定模 $2$ 不同余，
    
    	所以必定一个奇数，一个偶数，
    
    	先手将那一个奇数只需取到另一个偶数 $-1$ 就胜利了，
        或将那个偶数取到另一个奇数 $-1$ 就胜利了。
   
   2. 当 $|a-b|$ 为偶数
   
   		$a$ , $b$ 一定模 $2$ 同余，
         
      必定为两个奇数，或者两个偶数，
      
      先手只需将两个数变成相同的即可。
      
      

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;
    cin>>n>>m;
    if(abs(n-m)<=1) cout<<"Brown";
    else cout<<"Alice";
    return 0;
}
```



---

