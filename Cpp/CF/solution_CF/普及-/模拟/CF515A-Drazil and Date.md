# Drazil and Date

## 题目描述

Someday, Drazil wanted to go on date with Varda. Drazil and Varda live on Cartesian plane. Drazil's home is located in point $ (0,0) $ and Varda's home is located in point $ (a,b) $ . In each step, he can move in a unit distance in horizontal or vertical direction. In other words, from position $ (x,y) $ he can go to positions $ (x+1,y) $ , $ (x-1,y) $ , $ (x,y+1) $ or $ (x,y-1) $ .

Unfortunately, Drazil doesn't have sense of direction. So he randomly chooses the direction he will go to in each step. He may accidentally return back to his house during his travel. Drazil may even not notice that he has arrived to $ (a,b) $ and continue travelling.

Luckily, Drazil arrived to the position $ (a,b) $ successfully. Drazil said to Varda: "It took me exactly $ s $ steps to travel from my house to yours". But Varda is confused about his words, she is not sure that it is possible to get from $ (0,0) $ to $ (a,b) $ in exactly $ s $ steps. Can you find out if it is possible for Varda?

## 说明/提示

In fourth sample case one possible route is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515A/c7eeb592e99c054b70275e1c11760c4bf457a818.png).

## 样例 #1

### 输入

```
5 5 11
```

### 输出

```
No
```

## 样例 #2

### 输入

```
10 15 25
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
0 5 1
```

### 输出

```
No
```

## 样例 #4

### 输入

```
0 0 2
```

### 输出

```
Yes
```

# 题解

## 作者：_Haoomff_ (赞：3)

~~大水题~~
## 题意
从 $(0,0)$ 到 $(a,b)$ 能不能用 $s$ 步走到。
## 思路
因为 $a$ 和 $b$ 可能为负数，所以需要使用 abs（求绝对值）函数。

+ $\left\vert a\right\vert + \left\vert b\right\vert$ 如果小于 $s$，那么无论如何都是走不到的，因为步数不够。
+ $\left\vert a\right\vert + \left\vert b\right\vert$ 如果正好等于 $s$，那么是可以走到的，也就是一遍到，不会存在某个点要走两遍或者更多的情况。
+ $\left\vert a\right\vert + \left\vert b\right\vert$ 如果大于 $s$，分两种情况：
  1. $s - \left\vert a\right\vert - \left\vert b\right\vert$ 除以 $2$ 的余数为 $1$，那么是无法走到的，因为从 $A$ 点走到 $B$ 点再回到 $A$ 点肯定需要偶数步。
  2. $s - \left\vert a\right\vert - \left\vert b\right\vert$ 除以 $2$ 的余数为 $0$，那么是可以走到的，理由同上。
  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b>>s;
	c=abs(a)+abs(b);
	if(c==s)cout<<"Yes";
	else if(c<s&&(s-c)%2==0)cout<<"Yes";
	else cout<<"No";
	return 0;
}
```


---

## 作者：BrokenStar (赞：3)

## 思路

这道题判断能否从 $(0,0)$ 走到 $(a,b)$ ，并且**恰好**上下左右走 $s$ 步。

我们知道最短的步数就是朝着 $(a,b)$ 一直走，也就是走 $a+b$ 步，但题目中说了 $-10^{9}\leq a,b\leq 10^{9}$ ，所以应该加绝对值，即 $|a|+|b|$ 步。所以当 $(|a|+|b|) > s$ 时，就一定不能走到。

但是走到了 $(a,b)$ ，步数 $s$ 不一定就全部走完了。怎么办呢？很简单，走出去再走回来，循环往复就能消耗光。但又出现一个问题，就是如果出去了，发现 $s$ 用光了，就回不来了。

也就是说，当走到 $(a,b)$ 后，剩余的步数 $s-(|a|+|b|)$ 是奇数，就不能走到。

由此得到代码如下。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,s;
signed main(){
    cin>>a>>b>>s;
    int d=abs(a)+abs(b);
    if((d-s)%2==0&&d<=s){
        puts("Yes");
    }
    else puts("No");
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

## CF515A Drazil and Da☆ze 
在本题中只能上下左右行走 $s$ 步，问是否能够从 $(0,0)$ 到达 $(a,b)$ .

首先，如果你足够聪明的话，你会只走 $a+b$ 步到达 $(a,b)$ 这是最短的路线，也就是 $s<a+b$ 一定不可行 .

那如果 $s>a+b$ 时，就是主人公比较睿智，到达了终点后在原地蹦跶，黑白染色可以知道若 $s$ 与 $a+b$ 不同奇偶，肯定在 $s$ 步后不能蹦回去 $(a,b)$ .这时也是不可行的 .

终上所述即可以 $O(1)$ 求解 .

## Code

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a,b,s;
int main(){
	cin>>a>>b>>s;
	if ((abs(a)+abs(b)-s)%2==0&&abs(a)+abs(b)<=s)
		cout<<"Yes";
	else
		cout<<"No";
	return 0;
}
```


---

## 作者：minVan (赞：1)

**题目大意**

问从 $(0,0)$ 到 $(a,b)$ 能否恰好走 $s$ 步到达。

**解题思路**

从 $(0,0)$ 到 $(a,b)$ 至少花 $|a|+|b|$ 步到达，还剩下 $t=s-|a|-|b|$ 步，这就从 $(a,b)$ 不断的来回走，但如果剩下奇数步，那就不能到达终点了，当然  $t<0$ 的情况也不能到达。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, b, s;
signed main() {
    cin >> a >> b >> s;
    int d = abs(a) + abs(b);
    if((s - d) % 2 == 0 && d <= s) {
        puts("Yes");
    } else puts("No");
    return 0;
}
```

---

## 作者：ZolaWatle (赞：1)

### CF515A 题解

题目大意：

给定一个坐标，设每一步可以上下左右移动一个单位，问从原点走到这里能否恰好画费$ s $步。

------------

思路:

我们假设题中的主人公是非常睿智的，于是先计算从原点到( $ a,b $ )的最短距离，也就是**曼哈顿距离**。

曼哈顿距离公式想必大家都很熟悉，大概是这个样子的：

$$ dis = |X_1 - X_2| + |Y_1 - Y_2| $$

又由于题中的起始点为原点，所以最短路径可以简化为：

$$ dis=|a| + |b| $$

------------

接下来是判断过程：

- 如果最短距离等于给的$ s $，那么直接满足

- 如果最短距离大于给的$ s $，那么肯定不满足

如果出现$ dis < s $的情况呢？

题目上说了，主人公睿智到一种境界：他在走到目标点的情况下竟然还不自知！

那么如果他在以最短距离到达目标点后，一直在“转圈圈”（往前走一步再倒回来），直到他走完$ s $步，那么这也是符合要求的。

所以只要

$$ (s - dis)|2$$

那也是符合要求的。

------------

经过上面的分析，可以轻易地得到代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define re rgister int
using namespace std;

int a,b,s,dis;

int main()
{
	std::scanf("%d%d%d",&a,&b,&s);
	
	dis=std::abs(a)+std::abs(b);
	
	if(dis==s)
	{
		std::printf("Yes");
		return 0;
	}
	if(dis>s)
	{
		std::printf("No");
		return 0;
	}
	
	dis=s-dis;
	
	if(dis%2==0)
	{
		std::printf("Yes");
		return 0;
	}
	std::printf("No");
	return 0;
}
```

------------

本人第一次写的时候没加绝对值写挂了~

---

## 作者：Huran201803 (赞：0)

## 题目思路
这道题就用了点小学数学，从 $(0,0)$ 走到 $(a,b)$ 的最短路线是 $\left| a\right| +\left| b\right|$，如果最大步数不够的话就不能，直接输出结束。如果 $\left| a\right| +\left| b\right|$ 大于最大步数，也就是说走到了还剩，那么最大步数减 $\left| a\right| +\left| b\right|$ 就一定要是偶数，才能一去一回抵消。
## 代码实现
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a, b, s;
	cin >> a >> b >> s;
	long long maxn = abs(a) + abs(b);//最大步数 
	if(t == s)
	{
		cout << "Yes";
		return 0;//直接结束 
	}
	else if(t>s)
	{
		cout<<"No";
		return 0;
	}
	else
	{
		if((s-t)%2==0)
		{
			cout<<"Yes";
			return 0;
		}
		else
		{
			cout<<"No"; 
		}
	}
	return 0;
}


```


---

## 作者：yghjsk (赞：0)

# 题意：
一开始你位于 $(0,0)$，然后会给出两个数也就是 $a$ 和  $b$，还有步数 $s$，你要从 $(0,0)$ 通过上、下、左、右四种方式走 $s$ 步不偏不倚到达目的地，问你可不可以做到做到，可以的话输出 Yes，不可以的话就输出 No。
# 思路：
这道题关键就在于 $s$，我们只能走 $s$ 步。我们都知道最少步数 $a+b$，由于你每次只能向一个方向走一步，所以步数减去最短路径的步数必须是个偶数，因为得出偶数的话，我们可以反复横跳到达终点，所以 $s-(a+b)$ 除以二的余数必须为 $0$。
# 你们的最爱代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,s;
int main(){
	cin>>a>>b>>s;
	if(abs(a)+abs(b)<=s&&(abs(a)+abs(b)-s)%2==0) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```


---

## 作者：Vct14 (赞：0)

### 题意

你在 $(0,0)$，求能否恰好使用 $s$ 步走到 $(a,b)$。

### 思路

先考虑能否走到。

由[曼哈顿距离](https://baike.baidu.com/item/%E6%9B%BC%E5%93%88%E9%A1%BF%E8%B7%9D%E7%A6%BB/743092)可知，从 $(0,0)$ 到 $(a,b)$，最短路径必然是一直向左（或右）移动 $a$ 步，再向上（或下）移动 $b$ 步。则最少的步数为 $\left| a\right|+\left| b\right|$。如果连最少的步数都还比 $s$ 多的话，即 $\left| a\right|+\left| b\right|>s$，那必然不可能走到。

再考虑能否**恰好**走到。

在使用 $\left| a\right|+\left| b\right|$ 步后，还剩下 $s-(\left| a\right|+\left| b\right|)$ 步。我们可以不停地走出去一步，再退回来，这样的话每一个来回就可以“消耗”两步。那么如果 $s-(\left| a\right|+\left| b\right|)$ 是偶数，便可以走到，否则不能走到。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long a,b,s;
    cin>>a>>b>>s;
    long long c=abs(a)+abs(b);
    if(c>s || (c-s)%2) cout<<"No";
    else cout<<"Yes";
    return 0;
}
```

---

## 作者：The_FAKIR (赞：0)

## 题目大意
给定 $a$ 与 $b$，询问 Drazil 能否恰好走 $s$ 步从 $(0,0)$ 到 $(a,b)$。注意每次 Drazil 只能向上下左右走一步。

## 分析
由于 Drazil 一次只能往上下左右走一步，所以要求的步数减去最短路径的步数必须是个偶数（多余的步数可以通过来回走的方式消耗掉），那么只需判断一下要求的步数减去最短路径是不是偶数就行了。而最短路径就是 $a$ 的绝对值减去 $b$ 的绝对值
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,bs;
int main(){
	cin>>x>>y>>bs;
	if((abs(x)+abs(y)-bs)%2==0&&abs(x)+abs(y)<=bs) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```


---

## 作者：zwye (赞：0)

## 题目意思
问你能不能只用 $ s $ 步从 $ (0,0) $ 走到 $ (a,b) $。可以输出  `Yes`，否则输出 `No`。
## 思路
由于 $a$ 和 $b$ 可能是负数，所以要求绝对值。$s$ 需要满足以下条件：  
走到 $ (a,b) $ 需要 $ a + b $ 步，所以 $ s $ 必须大于 $ a + b $。如果有多余的步数，可以往随便一个地方走了再走回去，但是多余的数必须是偶数，否则就走不回来。
## 代码
```c
#include<bits/stdc++.h>
using namespace std;
long long a,b,s;
int main()
{
    cin>>a>>b>>s;
    long long w=abs(a)+abs(b);
    if(w<=s&&(w-s)%2==0)cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

---

## 作者：liukangyi (赞：0)

# 题目大意
这道题是发生在一张地图上的事。说你位于第 $0$ 行第 $0$ 列，然后会给出两个数 $a$ 和 $b$ 以及 $s$，代表你需要到达的目的地位于第 $a$ 行第 $b$ 列，并且要通过上、下、左、右四种方式使用 $s$ 步**正好**到达目的地。最后问你能否做到，能则输出 Yes，否则输出 No。


------------
# 思路
这道题的关键点就在于要正好 $s$ 步，那我们就可以运用一种思想，就是先尽快到达终点后，开始反复横跳：先往右，再往左。不停地**循环重复**下去。这样一来，最后就很有可能刚好落在目的地上。

------------
# 具体步骤
### 第一环节
既然我们要尽快到达终点，所以我们就先要求出**最少步数**。最少步数为 $\operatorname{abs}(a+b)$。但是在求出最少步数后，我们要看看最少步数是不是已经大于要求步数。

------------
### 第二环节
其次我们要看看到达目的地后反复横跳最后会落在那个地方，那我们就可以以**两步一组**，看看剩余步数能否刚好支撑完若干组。进行此步骤时，我们需求**余数**。余数为 $(s-\operatorname{abs}(a+b)) \bmod 2$。接下来，如果余数为 $0$ 则证明可以正好通过 $s$ 步走到目的地，反之不能。


------------
# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
int a,b,s;
int main(){
    scanf("%d%d%d",&a,&b,&s);
    int MinStep=abs(a+b); //最少步数 
    int ResidueStep=s-MinStep; //剩余步数 
    if(ResidueStep<0){
    	cout<<"No";
    	return 0;
	} //判断最少步数是否已经大于目标步数 
    int Num=ResidueStep%2; //反复横跳结果余数 
    Num?(cout<<"No"):(cout<<"Yes");
    return 0;
}
```


---

## 作者：Lemon_zqp (赞：0)

### 思路
这题有点考数学，首先我们要知道从 $(0,0)$ 走到 $(a,b)$ 的最短路线是 $\left| a\right| +\left| b\right|$，如果最大步数不够的话就不能，直接输出结束。如果在最大步数以内，还有一种情况，如果 $\left| a\right| +\left| b\right|$ 大于最大步数，也就是说走到了还剩，那么最大步数减 $\left| a\right| +\left| b\right|$ 就必须是偶数，才能保证一去一回抵消。

### 代码
```
#include<bits/stdc++.h>
using namespace std;

long long abss(long long a)
{
	if(a < 0)
	{
		return -a;
	}
	else
	{
		return a;
	}
}

int main()
{
	long long a, b, s;
	cin >> a >> b >> s;
	long long t = abss(a) + abss(b);
	if(t == s)
	{
		cout << "Yes";
	}
	else if(t > s)
	{
		cout << "No";
	}
	else
	{
		if((s - t) % 2 == 0)
		{
			cout << "Yes";
		}
		else
		{
			cout << "No"; 
		}
	}
	return 0;
}

```


---

## 作者：zwy__ (赞：0)

### 题目意思
有 $a$，$b$ 和 $s$。问你能不能只用 $s$ 步从 $(0,0)$ 走到 $(a,b)$。可以输出 Yes，否则输出 No。
### 题目思路
需要满足以下条件：
+ 走到 $(a,b)$ 需要 $a+b$ 步，所以 $s$ 必须大于 $a+b$。
+ 如果有多余的步数，可以往随便一个地方走了再走回去，但是多余的数必须是偶数，否则就走不回来。

只要满足以下条件，就输出 Yes，否则就输出 No。
### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,s;
int main()
{
    cin>>a>>b>>s;
    if(abs(a)+abs(b)<=s&&(abs(a)+abs(b)-s)%2==0)cout<<"Yes";
    else cout<<"No";
    return 0;
}
```


---

## 作者：InversionShadow (赞：0)

## CF515A Drazil and Date 题解

+ 易知 $s<|a|+|b|$ 时，无论如何不能到达 $(a,b)$。

+ 如果 $|a|+|b| \bmod 2 = 1$，不可以到达。原因很简单：可以发费 $|a|+|b|$ 从 $(0,0)$ 到 $(a,b)$，如果 $|a|+|b| < s$，还可以走 $s-(|a|+|b|)$ 步，如果它是奇数，则可以来回奇数步，达不到 $(a,b)$。

+ 反之，则可以达到。

## Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, s;
  cin >> a >> b >> s;
  if (abs(a) + abs(b) > s) {  
    cout << "No";
    return 0;
  }
  if ((s - (abs(a) + abs(b))) % 2 == 1) {
    cout << "No";
  } else {
    cout << "Yes";
  }
  return 0;
}
```




---

## 作者：szhqwq (赞：0)

## 分析

因为需要恰好 $s$ 步走到 $(a,b)$，最少需要走 $a + b$ 步，所以当 $s < a + b$ 时一定不能到达。当 $s \ge a + b$ 时，多出来的步数需要判断一下奇偶，如果为奇数那么不能恰好 $s$ 步到达 $(a,b)$。

综上，判断条件如下：

1. $s < a + b$，不能恰好到达；
2. $(a + b - s) \bmod 2$ 为奇数，不能恰好到达；
3. 不满足以上 $2$ 个条件则能恰好到达。

**注意：因为 $-10^{9} \le a,b \le 10^9$，所以 $a,b$ 要加上绝对值。**

## AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int a,b,s;

signed main() {
	ios :: sync_with_stdio(false);
	cin >> a >> b >> s;
	a = abs(a),b = abs(b);
	if (s < a + b) puts("No");
	else if ((a + b - s) & 1) puts("No");
	else puts("Yes");
	return 0;
}
```

---

## 作者：Firstly (赞：0)

这是一道考察思维的题，我们在分析其性质后可以用 $O(1)$ 的时间复杂度完成。

## **题目思路：**
------------
相信大家都知道，算从一点到另一点的最短距离（只能向上下左右的情况之下）为 $\left\vert x2-x1\right\vert + \left\vert y2-y1\right\vert$。所以说，当要求的距离小于这个值，那么不可以完成。

如果进行了一些偏离，那么我们可以发现，偏离的总是要一去一回。所以，走的总距离与最短距离的差总是一个偶数。如果差为奇数，则同样不可能完成。

分析结束，代码如下：

## **Code：**
------------
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int a,b,s;
	cin>>a>>b>>s;
	a=abs(a),b=abs(b);//因为数据可能为负数，所以我们在开始时就要取a,b的绝对值
	if(a+b>s)cout<<"No";
	else if(s-(a+b)&1)cout<<"No";
	else cout<<"Yes";
	return 0;
}
```


---

## 作者：yf最qhhh (赞：0)

~~这道题过的人怎么才这么点啊。。。。而且上一篇题解怎么写了这么多代码。~~

首先，从原点走到任意一个点 $(a,b)$ 的距离就是 $|a|+|b|$。

小学数学嘛。

比如这样一个正方形：

![原正方形](https://cdn.luogu.com.cn/upload/image_hosting/n9wjmy9u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

它的周长就是 $2(a+b)$，即使变成了这样：

![变换后](https://cdn.luogu.com.cn/upload/image_hosting/vrckwu2b.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

它的周长还是 $2(a+b)$。

原理很简单：

$\qquad$![原理](https://cdn.luogu.com.cn/upload/image_hosting/bh3fxgrj.png?x-oss-process=image/resize,m_lfit,h_150,w_200)

把那些缺失的边补回去就能重新构成一个长方形。

~~如果你还没听懂，你就真的没救了。~~

在坐标轴上同理，不管你怎么绕，你走的路程永远是 $|a|+|b|$。

注意一下，因为只能上下左右移动，也就是说不能用 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 计算。

回到这道题，既然已经知道了距离怎么算，只需要判断一下是否等于 $s$ 就好了，是不是就能做了？是不是就写出了这份代码？

```cpp
#include<bits/stdc++.h>
#define rll register long long
#define ll long long
using namespace std;

int main(){
	rll a,b,s;
	scanf("%lld%lld%lld",&a,&b,&s);
	if(abs(a)+abs(b)==s)printf("Yes");
	else printf("No");
	return 0;
}

```


不，观察第4个样例:
```
0 0 2
```
如果按我们的思路，输出应该为 $No$，可样例输出却为 $Yes$。

所以我们就可以发现到达目标点后你是可以通过反复横跳把步数耗完的，那么既然要反复横跳，必须剩下的步数为偶数才行，否则就跳不回来了。

所以现在才是 $ACCode$：
```cpp
#include<bits/stdc++.h>
#define rll register long long
#define ll long long
using namespace std;

int main(){
	rll a,b,s;
	scanf("%lld%lld%lld",&a,&b,&s);
	if((abs(a)+abs(b)-s)%2==0&&abs(a)+abs(b)<=s)printf("Yes");//首先要确保|a|+|b|小于等于s，否则根本就走不到(a,b)，然后再来判断剩下的步数是否为偶数。
	else printf("No");
	return 0;
}

```
好了，本题解到这里就完美结束！

---

