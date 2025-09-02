# In Search of Truth (Hard Version)

## 题目描述

The only difference between easy and hard versions is the maximum number of queries. In this version, you are allowed to ask at most $ 1000 $ queries.

This is an interactive problem.

You are playing a game. The circle is divided into $ n $ sectors, sectors are numbered from $ 1 $ to $ n $ in some order. You are in the adjacent room and do not know either the number of sectors or their numbers. There is also an arrow that initially points to some sector. Initially, the host tells you the number of the sector to which the arrow points. After that, you can ask the host to move the arrow $ k $ sectors counterclockwise or clockwise at most $ 1000 $ times. And each time you are told the number of the sector to which the arrow points.

Your task is to determine the integer $ n $ — the number of sectors in at most $ 1000 $ queries.

It is guaranteed that $ 1 \le n \le 10^6 $ .

## 说明/提示

Hacks

To hack, use the following test format.

In the first line, output a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of sectors.

In the second line, output $ n $ different integers $ 1 \le a_1, a_2, \dots, a_n \le n $ — the numbers of the sectors in clockwise order, the arrow initially points to the sector with the number $ a_1 $ .

## 样例 #1

### 输入

```
1

5

6

7

2

10

9

8

4

3

1```

### 输出

```
+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

! 10```

# 题解

## 作者：YxYe (赞：40)

## 题意

[交互题](https://www.luogu.com.cn/problem/CF1840G2)，给你一个写有 $1\sim n$ 的乱序的转盘，每次可以顺时针转 $k$ 格，告诉你旋转后格子上的数，求 $n$ 的值。

强化版数据范围：$n \le 10^6, k\le 1000$

## 分析

首先我们需要拥有[简单版的思维](https://www.luogu.com.cn/blog/YxYe/solution-cf1840g1)。

看到能够旋转的次数变少了！怎么办？

优化呗！先看看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hgkacptn.png)

我们可以发现此时的 $n$ 范围超过了 $(k\div 2)^2$ 。

现在有两种思路：一是扩大 $k$ 的范围，二是缩小 $n$ 的范围。

思路一显然不行，因为题目都确定了 $k$ 的限制，所以我们考虑思路二。

想到每次询问都会给出一个数我们没用啊！这不正可以缩小 $n$ 的范围？

为了防止被卡，最好用随机化先确定范围。

于是我们就有了如下策略：先随机跳取范围，再取连续段，最后找答案。

好了，那么具体我们应该对于每个询问执行多少次呢？在简单版中，我们已经知道后两个操作数相同时最后，那么第一个呢？是滴，也相同。为什么呢？这里就用到了概率论。设操作一 $d$ 次，操作二三各 $m$ 次，则有失误概率为：

$$
{(\frac{n-m-1}{n})}^d
$$

由 $d+2\times m=k$ 的限制，计算可得约 $d=m$ 时上式值最小。（如果连 $10^{-17}$ 都能碰上，那证明你的 rp 欠费了！）

偷偷告诉你^_^，在这里点赞者 rp++。

---

## 作者：Moya_Rao (赞：33)

第一次写紫题题解喵，希望各位能阅读到最后。

首先我来解析一下题意吧喵。注意这个题目是交互题哦。

出题人隐藏了一个转盘，这个转盘上一共有 $n$ 个格子并且分别写有 $1 \sim n$ 这些数字，但是，你是不知道 $n$ 是多少的喵。而且，出题人非常狡猾，这 $n$ 个格子的顺序完全是乱的喵！转盘上当然是有一个箭头的喵，这个箭头一开始指向的位置，出题人是会告诉你的喵，就是 $x$ 喵！

现在，你可以指挥出题人将这个转盘进行旋转。具体来说，如果你输出 `+ k`，表示你让出题人将这个转盘顺时针旋转 $k$ 格；反过来，如果你输出 `- k`，就表示你让出题人将这个转盘逆时针旋转 $k$ 格啦喵。

旋转了转盘以后，出题人会告诉你当前箭头指向的格子上写的那个数字是什么喵。你需要根据这一些乱七八糟的数据，在不超过 $1000$ 次的操作中，准确猜出 $n$ 是多少喵！如果最后你猜出来了，需要输出 `! n` 哦喵！

题意有点复杂，希望各位好好分析分析一下喵。

接下来就是思路环节了喵！各位要认真看哦喵。讲得可能不是很好请各位原谅喵。

首先我们考虑一个简单一点的做法喵。

弄一个数值 $M=10^3$。

接着我们分两步：
- 一共输出 $M$ 次 `+ 1`，如果中间碰到了相同的就直接输出答案；
- 如果上面没能算出答案，接着输出 $M$ 次 `+ M`，找到第一个与前面 `+ ` 时相同的值，就可以对应计算输出啦。

这个方法好像不错呢喵，能过掉这题吗？思路没毛病，只可惜最多需要 $2000$ 次操作机会，而题目只给了 $1000$ 次，没办法顺利过题喵。但是这种方法是可以过简单版的喵！

接下来就只能考虑优化一下刚才的那种方法咯喵。

想想看，如果咱们能把 $n$ 的范围自己整得更小一点就好了，对吧喵？

那咱可以先求出一个 $n$ 的下界，假设就是 $minn$ 吧喵。咋弄？不妨用点儿人类智慧，随机地来上个 $M$ 次 `+ k` 操作，取中间拿到的最大值就好啦。

你是不是好奇 $M$ 是多少呀喵？总要知道的，但咱们等会再说。

我们肯定想设定一个范围，比方说是 $[minn,minn+K]$，如果咱能保证 $n$ 在这个范围内的话，肯定就可以再用 $2 \times \sqrt{K}$ 次机会来找出 $n$ 了，对不？至于为什么是用这么多次——各位可别忘了刚才说的那种简单版的方法哦！

接下来就要上数学了喵。我们该如何确定了这个 $M$ 和 $K$ 喵？

首先有个简单的结论：  
如果固定了一个 $M$ 值，直接取 $K=(\frac{10^3-M}{2})^2$ 就行了，是吧喵？可别问我为啥，这可是在有限的操作次数里能选到的最大的 $K$ 了！

接下来咱来算算概率。如果 $n \le minn-K$，那么前面随机算出的数全都 $\le minn$ 的概率为 $(\frac{minn}{n})^M$。不过 $n$ 是我们不知道的，这玩意儿有点不好算喵，是不是？那咱们就把概率整大点儿嘛，变成 $(\frac{minn}{minn+K+1})^M$ 总行了，对不？因为现在这个值比前边那个大喵。

上面算的是错误率，那这个错误率要取怎样的 $M$ 和 $K$，值才会最小呢？我们取 $M=300$ 和 $K=122500$，当 $minn=10^6$ 的时候，我们的错误率只有 $10^{-17}$ 左右哦！这个概率这么小，完全足够你过了这题，对不对呀喵？

顺便讲个事儿，如果你这题没过，你可以去买彩票了，这么小的概率都给你撞上了，说明你运气很好哦喵！哈哈！

最后我来放上我的 [AC](https://codeforces.com/contest/1840/submission/318314526) 代码，保证对的啦喵！里面还有详细注释呢喵，保证能让你明明白白喵！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 300;
const int N = 1e6+5;
const int K = 350;
//定义三个常量方便后面的使用
//M：一开始的随机跳次数
//N：转盘大小，定义数组时使用
//K：最后锁定的区间，我们取最合适的长度
int x,minn,v[N];
int main(){
    cin>>x;minn=0;
    //读入 + 初始化
    mt19937 Rand(time(0));
    //用当前时间作为随机种子
    for(int i=1;i<=M;i++){
        //一共随机 M 次
        int Move=Rand()%1000000000+1;
        //随机生成一个数值 Move
        cout<<"+ "<<Move<<"\n";fflush(stdout);
        //移动随机数 Move 步
        int now;cin>>now;minn=max(minn,now);
        //拿到当前所在位置并取最大值
    }
    cout<<"+ "<<minn<<"\n";
    //再次移动 minn 步
    fflush(stdout);cin>>x;
    //取到当前新的位置并存下来
    for(int i=1;i<=1000000;i++)v[i]=-1;v[x]=0;//初始化
    if(minn<=K){
        //如果值域较小，直接在这个范围里查
        for(int i=1;;i++){
            cout<<"+ 1\n";
            fflush(stdout);
            cin>>x;
            //每次 +1 并取到当前值
            if(v[x]!=-1){
                //如果这个位置被遍历过说明找到了
                cout<<"! "<<i-v[x]<<"\n";
                fflush(stdout);break;//输出并结束查询
            }
            v[x]=i;//存下来，证明这个位置遍历过了
        }
    }
    else{
        //否则值域范围较大，处理方式更为复杂
        for(int i=1;i<=K;i++){
            cout<<"+ 1\n";
            fflush(stdout);
            cin>>x;v[x]=i;
            //首先每次 +1 并记录位置
        }
        cout<<"+ "<<minn-K<<"\n";
        fflush(stdout);cin>>x;
        //移动 minn-K 步并更新当前位置
        for(int i=1;;i++){
            cout<<"+ "<<K<<"\n";
            fflush(stdout);cin>>x;
            //每次移动 K 步并取当前位置
            if(v[x]!=-1){
                //如果这个位置曾被遍历过
                cout<<"! "<<minn+K*i-v[x]<<"\n";
                fflush(stdout);break;
                //对应计算出答案并输出，结束查询
            }
        }
    }
    return 0;
}
```

如果你们觉得本篇题解还不错的话，麻烦各位点一个小小的赞，万分感谢喵！

---

## 作者：Lucky_Xiang (赞：9)

# 题目

[CF1840G2](https://www.luogu.com.cn/problem/CF1840G2)

# 思路

对于 Easy Version，可以参考 BSGS 算法的思路，先转 $\sqrt{n}$ 次一格，就可以记录相邻 $\sqrt{n}$ 格的数字；再不停地转 $\sqrt{n}$ 格，直到出现前面记录的数字，就知道转了一圈了，总操作次数 $2\sqrt{n}$。

[Code](https://codeforces.com/contest/1840/submission/208786059) 

但是我们并没有充分利用询问的信息。假如一次操作后得到的数字为 $x$，它不仅可以让我们区分不同的格子，而且还告诉我们了一个隐藏信息：最终答案 $n\geq x$。那么，我们就可以先随机转 $k$ 次并记录得到的最大值 $n_0$，不妨设 $n_0\le n\le n_0+d$，则所有的格子就被分为了数量分别为 $n-n_0$ 和 $n_0$ 的两部分。因为 $n-n_0\le d$，所以我们可以参考 Easy Version 的思路，在数量为 $n-n_0$ 的部分的一端标记 $\sqrt{d}$ 个格子，并从另一端开始不断转 $\sqrt{d}$ 格，就可以确定 $n-n_0$ 的值了，总操作次数 $k+2\sqrt{d}$。

但是，这个做法不完全正确，因为 $n$ 可能大于 $n_0+d$。其出错概率 $P(A)=({{n-d-1}\over{n}})^k$。当 $k=400,d=90000$ 时，$P(A) \approx 4.1 \times 10^{-17}$，足以通过此题。

[Code](https://codeforces.com/contest/1840/submission/208909073)

---

## 作者：EuphoricStar (赞：5)

每次询问获得的信息只有当前所在位置的数字。考虑这样一件事情，如果我们询问了 $b_1, b_2, ..., b_k$ 之后，走到了询问 $b_1$ 前所在的数字，就说明 $n \mid \sum\limits_{i = 1}^k b_i$。可以考虑构造一个步数序列 $a_1, a_2, ..., a_m$，如果能满足任何一个 $x \in [1, 10^6]$ 都存在 $1 \le l \le r \le m$ 使得 $\sum\limits_{i = l}^r a_i = x$，那么就做完了。

先考虑 G1 $2023$ 次询问怎么做。发现是 $2 \sqrt{n}$ 级别，启发我们类似 BSGS 地，构造 $a_1 = a_2 = \cdots = a_{1000} = 1, a_{1001} = a_{1002} = \cdots = a_{2000} = 1000$。所用询问次数为 $2000$，[可以通过 G1](https://codeforces.com/contest/1840/submission/208838446)。

但是 G2 只能询问 $1000$ 次。发现此时无论如何都不能构造出满足条件的 $m \le 1000$ 的步数序列。我们还发现一件事情，就是所到达位置的数字一定 $ \le n$。那我们是不是可以先在这个圆上随机游走一会，得到 $n$ 的一个紧一点的下界呢？发现这样是可行的。具体地，设置一个 $B$，先随机游走 $998 - 2B$ 次，得到经过的数字的最大值 $k$，然后构造 $a_1 = a_2 = \cdots = a_B = 1, a_{B + 1} = k, a_{B + 2} = a_{B + 3} = \cdots = a_{2B + 1} = B^2$ 即可。总共使用 $999$ 次询问（不知道为什么最多用 $999$ 次，用 $1000$ 次就不行）。

可以发现出错的情况就是，随机 $998 - 2B$ 次随不到 $[n - B(B + 1), n]$ 的数。取 $B = 339$，出错概率 $< 10^{-17}$，[可以通过 G2](https://codeforces.com/contest/1840/submission/208840374)。

---

## 作者：Leasier (赞：1)

请先阅读[这篇题解](https://www.luogu.com.cn/blog/Leasier/solution-CF1840G1)。

------------

考虑在 G1 做法的基础上进行优化。

有一个人类智慧的想法：如果所求 $n$ 的范围可以卡到一个较小的区间内就好了。

不妨先求出 $n$ 的某一个下界 $\min_n$。考虑随机 $M$ 次 $+ k$ 操作，将中间各次的 $x$ 最大值作为 $\min_n$。

那么我们应该如何设定这个范围呢？若我们钦定 $n \in [\min_n, \min_n + K]$，只要 $n$ 在这个范围内的概率足够大，则我们只需要再来 $\leq 2 \sqrt{K}$ 次操作就可以了。

显然对于一个确定的 $M$，我们令 $K = (\frac{10^3 - M}{2})^2$ 即可。

现在我们来算算概率。若 $n > \min_n + K$，则前面随机到的数都 $\leq \min_n$ 的概率为 $(\frac{\min_n}{n})^M \leq (\frac{\min_n}{\min_n + K + 1})^M$，即正确率 $\geq 1 - (\frac{\min_n}{\min_n + K + 1})^M$。

取 $M = 300, K = 350^2 = 122500, \min_n = 10^6$ 可得正确率 $\geq 1 - 8.8 \times 10^{-16}$，因此可以通过。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 1e6, M = 300, K = 350;
int vis[N + 7];

inline int rand32(){
#if RAND_MAX == 0x7fff
	return rand() * rand();
#else
	return rand();
#endif
}

int main(){
	int x, minn = 0;
	scanf("%d", &x);
	srand(time(NULL));
	for (int i = 1; i <= M; i++){
		int delta = rand32() % 1000000000 + 1;
		printf("+ %d\n", delta);
		fflush(stdout);
		scanf("%d", &x);
		if (minn < x) minn = x;
	}
	printf("+ %d\n", minn);
	fflush(stdout);
	scanf("%d", &x);
	for (int i = 1; i <= N; i++){
		vis[i] = -1;
	}
	vis[x] = 0;
	if (minn <= K){
		for (int i = 1; ; i++){
			printf("+ 1\n");
			fflush(stdout);
			scanf("%d", &x);
			if (vis[x] != -1){
				printf("! %d\n", i - vis[x]);
				fflush(stdout);
				return 0;
			}
			vis[x] = i;
		}
	} else {
		for (int i = 1; i <= K; i++){
			printf("+ 1\n");
			fflush(stdout);
			scanf("%d", &x);
			vis[x] = i;
		}
		printf("+ %d\n", minn - K);
		fflush(stdout);
		scanf("%d", &x);
		for (int i = 1; ; i++){
			printf("+ %d\n", K);
			fflush(stdout);
			scanf("%d", &x);
			if (vis[x] != -1){
				printf("! %d\n", minn + K * i - vis[x]);
				fflush(stdout);
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：the_Short_Path (赞：0)

这题是个经典的概率论，~~A 不了说明运气好~~，只有 $10^{-17}$ 的概率会 WA。

建议先看 [Easy Version](https://www.luogu.com.cn/problem/CF1840G1)。

按照原先的思路，但是旋转次数少了，$n$ 超过了 $(\frac{k}{2})^{2}$。

所以只能缩小 $n$。（题目确定了 $k$ 的限制，不能扩大 $k$）

设所有操作各 $k$ 次，则失误概率为：
$$(\frac{n-k-1}{n})^k$$
打表发现，$k\approx325$时该式值较小（有没有大佬会用微积分证明一下），也就是前面说的，大约 $10^{-17}$，~~应该没有人运气这么好吧~~。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6, M = 300, k = 325;
int x, mx = 0, vis[N + 5];
inline int rand32(){
    if (RAND_MAX == 0x7fff) return rand() * rand();
    else return rand();
}
int main() {
	cin >> x;
	srand(time(NULL));
	for (int i = 1; i <= M; i++) {
		int d = rand32() % 1000000000 + 1;
		cout << "+ " << d << "\n";
		fflush(stdout);
		cin >> x;
		if (mx < x) mx = x;
	}
	cout << "+ " << mx << "\n";
	fflush(stdout);
	cin >> x;
	for (int i = 1; i <= N; i++) vis[i] = -1;
	vis[x] = 0;
	if (mx <= k){
		for (int i = 1; ; i++){
			cout << "+ 1\n";
			fflush(stdout);
			cin >> x;
			if (vis[x] != -1){
				cout << "! " << i - vis[x] << "\n";
				fflush(stdout);
				return 0;
			}
			vis[x] = i;
		}
	} else {
		for (int i = 1; i <= k; i++){
			cout << "+ 1\n";
			fflush(stdout);
			cin >> x;
			vis[x] = i;
		}
		cout << "+ " << mx - k << "\n";
		fflush(stdout);
		cin >> x;
		for (int i = 1; ; i++){
			cout << "+ " << k << "\n";
			fflush(stdout);
			cin >> x;
			if (vis[x] != -1){
				cout << "! " << mx + k * i - vis[x] << "\n";
				fflush(stdout);
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：0)

今年（2024）一月学长给我讲的题。

Solve G1 first.

注意到编号似乎在 G1 的做法中没有用到，但题目却蹊跷的保证了编号是一个 $1\sim n$ 的排列，这启示我们随机问一些编号，找出其中的最大值 $m$，然后直接猜 $n=\Theta(m)$。

于是我们便只用把实际的 $n$ 限制在很小的范围内了。

---

