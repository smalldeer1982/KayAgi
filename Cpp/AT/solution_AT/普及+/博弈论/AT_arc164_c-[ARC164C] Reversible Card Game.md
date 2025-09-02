# [ARC164C] Reversible Card Game

## 题目描述

有 $N$ 张卡片，每张卡片的两面分别写有一个数字，第 $i$ 张卡片的一面用红色写着 $A_i$，另一面用蓝色写着 $B_i$。一开始，所有卡片都以红色数字朝上摆放。Alice 和 Bob 进行如下规则的游戏：

- 首先，Alice 从剩下的卡片中选择一张，将其翻面。接着，Bob 从剩下的卡片中选择一张移除。此时，Bob 获得等于该卡片正面数字的分数。

当没有剩余卡片时，游戏结束。

Alice 的目标是让游戏结束时 Bob 的得分最小，Bob 的目标是让自己的得分最大。双方都采取最优策略时，游戏结束时 Bob 的得分是多少？

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq 10^9$（$1 \leq i \leq N$）
- 所有输入的值均为整数。

## 样例解释 1

初始状态下，正面朝上的数字分别为 $6,2,5$。例如，游戏可能按如下方式进行：

1. Alice 翻转第 $1$ 张卡片，此时正面数字变为 $4,2,5$。Bob 移除第 $3$ 张卡片，获得 $5$ 分。
2. Alice 翻转第 $2$ 张卡片，此时正面数字变为 $4,1$。Bob 移除第 $2$ 张卡片，获得 $1$ 分。
3. Alice 翻转最后剩下的第 $1$ 张卡片，此时正面数字变为 $6$。Bob 移除该卡片，获得 $6$ 分。

此时，Bob 的总得分为 $12$。实际上，这是一种双方采取最优策略的流程之一，答案为 $12$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
6 4
2 1
5 3```

### 输出

```
12```

## 样例 #2

### 输入

```
5
166971716 552987438
219878198 619875818
918378176 518975015
610749017 285601372
701849287 307601390```

### 输出

```
3078692091```

# 题解

## 作者：Exp10re (赞：8)

# 前言

非常有趣的结论题，当时我连 B 题都没打就来打 C 题导致差点没 A 掉 B（

# 关于这篇题解

作者对于 $ \LaTeX $ 公式的运用还不够熟练，如果本篇题解公式有误或者思路上有问题，欢迎在评论区进行讨论。

# 解题报告

此处的解题报告会对结论以及赛时思考得出结论的思路进行全面分析，希望能够帮助大家在赛时可以使用类似的思路写出类似的思维类题目。

## 思路

我们假设对于每一张卡片，其双面中较大的数字为 $ U_i $，较小的数字为 $ D_i $，设两面数字的差 $ U_i - D_i = Delta_i $，那么容易得到以下结论：

1. 游戏开始时，每一张卡片正面的数字不是 $ U_i $ 就是 $ D_i $，即：每一张卡片的写有数字较大值的一面不是朝上就是朝下 ~~（废话）~~。

2. **无论何时，Bob 取走第 $ i $ 张卡片至少能得到 $ D_i $ 的分数，至多能得到 $ D_i + Delta_i $ 的分数。**

3. 对于任意 $ i $，均有 $ Delta_i \geq 0 $。

注意到以上的结论 2，我们可以把原先的问题转变为等价的问题：我们认为 Bob 原本就有 $ \sum D_i $ 的分数，现在第 $ i $ 张卡片中较大的数字为 $ Delta_i $，较小的数字为 $ 0 $，其余问题不变，我们称新问题为问题 2，以与原问题区分。

为了方便，我们定义一张卡片的分数为 $ Delta_i $，然后，我们定义一张卡片 **非零**，当且仅当其正面的数字为 $ Delta_i $。注意，一张卡片非零是由其正面是否为 $ Delta_i $ 决定而非是否数字为为 $ 0 $ 决定的。

由此，对于问题 2 我们可以得知 Alice 进行的最优思路：轮到 Alice 操作时，Alice 必定会翻转场上正面数字较大且状态为 **非零** 的卡片。

显而易见，如果 Alice 不翻转场上正面数字较大且 **非零** 的卡片， Bob 必定会取走该卡片，因为取走该卡片是对于 Bob 而言最优的思路，取走正面数字为 $ 0 $ 的卡片一定是劣的，当场上有至少两张 **非零** 卡片时，取走正面数字最大的一张卡片一定是更优的。

那么 Bob 的思路也显而易见了，上文有提及，此处不多做赘述。

我们又注意到：Alice 的操作是建立在场上有 **非零** 的卡片的前提上的，那么如果场上所有的卡片正面都为 $ 0 $ 且轮到 Alice 操作，会发生什么呢？

此时，Alice 无论反转哪张卡片都会使得一张卡片从写有 $ 0 $ 的一面翻转至写有 $ Delta_i $ 的一面。此时轮到 Bob 进行操作，显然 Bob 会取走这一张唯一的被翻到 $ Delta_i $ 的一面的卡片。

于是我们又得到一个结论：

- 当场上所有卡片正面都为 $ 0 $ 且轮到 Alice 操作时， Bob 会得到相当于场上所有卡牌的 $ \sum Delta_i $ 的分数。

我们称以上情况为 **状态 A**。

那么，当场上所有的卡片正面都为 $ 0 $ 且轮到 Bob 操作会发生什么情况呢？

我们设此时 Bob 取走了卡片 $ p $ 的情况为 **状态 B**，显然，Bob 无论取哪张卡片 $ p $，都会先损失该张卡牌的分数 $ Delta_p $，然后进入 **状态 A** 并获得其余所有卡牌的分数 $ \sum Delta_i ( i \neq p ) $。

因此，Bob 在该种状态下会取得 $ \sum Delta_i - Delta_p $ 的分数，因为在进入 **状态 B** 时 $ \sum Delta_i $ 已经确定，所以 Bob 会最小化 $ Delta_p $ 来最大化 $ \sum Delta_i ( i \neq p ) $ 的值。

因此，又出现一个结论：

- 当场上所有卡片正面都为 $ 0 $ 且轮到 Bob 操作时， Bob 取走场上分数最小的卡牌 $ p $ 并得到相当于场上所有卡牌的分数总和减去卡牌 $ p $ 的分数，即 $ \sum Delta_i ( i \neq p ) $ 的分数。

在两个结论都确定时，我们尝试考虑在什么情况下经过若干次操作后会进入 **状态 A**，又在什么情况下经过若干次操作后会进入 **状态 B**。

对于问题 2，我们设在初始状态下有 $ cnt $ 张 **非零** 卡片，然后 Alice 和 Bob 都使用最优思路进行行动，容易得知：在两人各行动一次后， **非零** 卡片的数量一定会减少 $ 2 $，直到剩余 **非零** 卡片的数量为 $ 0 $ 或 $ 1 $。

当剩余卡片 **非零** 数量为 $ 0 $ 时，此时轮到 Alice 行动，可以知道此时状态就是 **状态 A** ，又根据先前 Bob 操作的思路，易知 Bob 在 **状态 A** 之前取走的卡牌必定全为 **非零** 卡片，又知道 Bob 在 **状态 A** 同样取卡片时会取剩余的所有 **非零** 卡片，因此有：

- 当 $ cnt $ 为 $ 2 $ 的倍数时，Bob 分数为 $ \sum Delta_i $。

在原问题中，Bob 的分数就是 $ \sum ( Delta_i + D_i ) $ ，即 $ \sum U_i $。

当剩余卡片 **非零** 数量为 $ 1 $ 时，Alice 会将其翻转，然后进入 **状态 B**。此时我们容易证明：分数最小的一张卡片必定没被取走（如果这张卡片初始 **非零**，那么取走前 $ cnt - 1 $ 张 **非零** 卡片必定会剩余该张卡片，然后其又会被Alice翻转，否则，这一张卡片初始为 $ 0 $，更不可能被取走），所以 Bob 分数为 $ \sum Delta_i - \min ( Delta_i ) $。即：

- 当 $ cnt $ 不为 $ 2 $ 的倍数时，Bob 分数为 $ \sum Delta_i - \min ( Delta_i ) $。

在原问题中，Bob 的分数就是 $ \sum ( Delta_i + D_i ) - \min ( Delta_i )  $ ，即 $ \sum U_i - \min ( Delta_i ) $。

求出 $ \min ( Delta_i ) $，问题就解决了。

# 代码

得出结论，代码实现就很简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Exp10reMAXN=200020; 
long long dist[Exp10reMAXN],MINN=(1ll<<60),tot;
int main()
{
	int n,i;
	long long ta,tb,ccnt=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&ta,&tb);
		if(ta<tb)
		{
			swap(ta,tb);
		}
		else
		{
			ccnt++;
		}
		dist[i]=ta-tb;
		tot+=ta;
		MINN=min(MINN,dist[i]);
	}
	if(ccnt%2==1)
	{
		tot-=MINN;
	}
	printf("%lld",tot);
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：6)

## 题意

有 $n$ 张卡片，第 $i$ 张的正面写有数字 $a_i$，背面写有数字 $b_i$。Alice 和 Bob 用这些卡片做游戏。一开始所有卡片都是正面朝上，每一轮 Alice 任意翻转一张卡片，Bob 任意取走一张卡片并得到这张卡片当前朝上一面的分值。卡片全部取走则游戏结束。Alice 想要最小化 Bob 的总分，而 Bob 想要最大化。问若两人都足够聪明，则 Bob 的总分是多少。
## 分析

这是一道很考验人类思维的博弈论的题目。Alice 要让 Bob 的得分最小，每次一定是将当前正面大于反面且差值最大的那一张牌翻个面，那么我们假设使用 $s$ 表示正面大于反面的纸牌张数。有以下两种情况。

- $s$ 为偶数，那么 Alice 把所有牌都反过来后，也就是经过 $s/2$ 次后，又需要再将一张牌翻回来，然后 Bob 又会选当前最大的牌，Alice 就又要再将一张已经在最优状态的牌翻到大的一面，这时 Bob 一定会选这张。以此类推，Bob 会把所有牌大的一面都选走。
- $s$ 为奇数，当 Alice 把最后一张翻完以后，留给 Bob 的都是小的那一面朝上的牌，自然，Bob 会选走正反之差最小的那张牌，因为这是损失最小的方法。

那么我们就得到一种策略，就是首先统计所有牌大的那一面的和记为 $x$。如果 $s$ 是偶数，就直接输出 $x$，否则就可以用 $x$ 减去这个正反两面数字的最小差距，得到答案，因为 Bob 会选择正反差距最小的那一张，损失这个差距的值，其他的就还是最大值。

## 代码+注释

一定要注意，记得开 long long 呀！
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,a,b,ans=0,cha=INT_MAX,cnt=0;//注意初始化
    cin>>n;
    for(int i=1;i<=n;i++){
		cin>>a>>b;
		if(a>b) //记录正面大于反面，也就是Alice要翻的牌 
			cnt++;
		ans+=max(a,b);//统计所有牌大的那一面的和
		cha=min(cha,abs(a-b));//记录最小的差值 
	}
	if(cnt%2) //奇数就减去最小的差，原因见上 
		cout<<ans-cha;
	else //偶数直接输出 
		cout<<ans;
    return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：3)

## 题意

有 $n(1\le n\le 2\times 10^5)$ 张卡片，第 $i$ 张的正面写有数字 $a_i$，反面写有数字 $b_i$。Alice 和 Bob 用这些卡片做游戏。一开始所有卡片都是正面朝上，每一轮 Alice 任意翻转一张卡片，Bob 任意取走一张卡片并得到这张卡片朝上一面的分值。卡片全部取走则游戏结束。Alice 想要最小化 Bob 的总分，而 Bob 想要最大化。问若两人都足够聪明，则 Bob 的总分是多少。

## 代码

先放代码吧，应该是最短解且时间复杂度 $O(n)$。结论题，我看赛时很多人没有发现结论稍稍浪费了些码力，都是 $O(n\log n)$ 做法。但这个结论推一下也不算难，如果不会证明，再前往下一部分。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,a[200005],b[200005],cnt,sum,mini=1e18;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++)sum+=max(a[i],b[i]);
    for(int i=1;i<=n;i++)cnt+=(a[i]>b[i]);
    for(int i=1;i<=n;i++)mini=min(mini,abs(a[i]-b[i]));
    if(cnt%2)cout<<sum-mini<<endl;
    else cout<<sum<<endl;
    return 0;
}
```

## 思路

大家应该已经看懂了结论。

拿到这道题，首先会有这样对 Bob 的分析，若有朝上面为较大数的卡片，则取走；若没有，则取卡片上两数的绝对值差小的以减小损失。再进一步去考虑，若 Bob 留给 Alice 的是一个朝上面全是较小数的状态，则最后这些卡片 Bob 都能以较大值取走（Bob 留给 Alice 的状态将不再发生变化）。而如果 Bob 留给 Alice 的状态是朝上面为较大数的卡片有大于等于 $2$ 张，那么下一轮 Bob 所得的分值仍能是较大值；而如果 Bob 只剩给 Alice 一张朝上面较大的卡片，那么 Alice 可使得 Bob 当前一轮取不到较大值。

一番分析稍作总结：如果 Bob 尽可能去取较大值，那么他最多只会有一张卡片取到的是较小值（因为一旦出现 Bob 只剩给 Alice 一张朝上面较大的卡片这种状态，那么此后都将是 Bob 留给 Alice 一个朝上面全是较小数的状态）。

你算下样例就可以猜测出 Bob 取到最小数的那张卡片一定是绝对值最小的那一张，下面考虑证明。

首先看什么情况下能够形成 Bob 只剩给 Alice 一张朝上面较大的卡片这种状态。我们发现，如果 Bob 按原始思路走，必定是减少一张朝上面较大的卡片，而 Alice 可任选增加或减少一张，由此可知，朝上面较大的卡片的奇偶性不变。由此可知，当初始朝上面较大数的个数为偶时，Bob 可以以较大值取走所有卡片。

接下来讨论初始朝上面较大数的个数为奇的情况，这样 Bob 一定会有一张取到的是较小数，那根据猜想，我们可以改变 Bob 取卡片的策略。如果绝对值最小的那张卡片朝上面为较小值，则立即取走，将朝上面较大的卡片的个数变为偶数，剩下卡片都能以较大值取走。如果这张卡片朝上的是较大值，那么 Bob 不能动，Alice 也不能动，可以看作这张卡片废了。因为一旦 Alice 翻了这张卡片，Bob 立即拿掉就好了。剩下的卡片朝上面较大的共有偶数张，可以全部较大值拿下。

综上所述：当卡片朝上面较大数的个数为奇时，仅有正反两数差绝对值最小的卡片取得较小值，其余均可取得较大值；当卡片朝上面较大数的个数为偶时，均可取得较大值。

结论有了，代码分分钟搞定！

---

## 作者：Hog_Dawa_IOI (赞：2)

### 题意简述
有 $n$ 张牌，每张牌有红色和蓝色两面，每一面有一个数字。      
最初，所有卡片的红色面朝上放置。爱丽丝和鲍勃玩一个游戏，他们重复下面的步骤：    
首先，爱丽丝从剩下的一张牌中选择一张，并将其翻转过来。接下来，鲍勃在剩下的所有牌中拿走一张牌。然后，鲍勃得到的分数等于拿走的卡片正面朝上写的数字。      
游戏在没有牌的时候结束。           
爱丽丝试图在游戏结束时最小化鲍勃的得分，而鲍勃试图将其最大化。当两名玩家都采取最佳步骤时，鲍勃在游戏结束后的得分是多少？    

-----

### 思路分析    
一眼博弈论。           
~~不知是谁口口声称这是个数学题，我不说他是不是在我样例还没分析完就有了思路。~~      
首先通过分析不难看出：每一轮，爱丽丝一定会把一张当前正面数字大于反面数字的牌反过来，而鲍勃一定会选择一张当前正面数字大于反面数字的牌。    
设 $x$ 为正面数字大于反面数字的牌的数量。
1. 如果 $x$ 是偶数，$x/2$ 轮之后，所有留下的牌都是正面数字小于反面数字的了。此时到爱丽丝选择，她只好把其中一张反过来，这一张就变成了正面大于反面，而鲍勃一定会选这张牌拿走。这样下去，可得出鲍勃一定会把所有牌中数字大的那一面上的数字取走。    
1. 如果 $x$ 是奇数，那么到第 $x/2+1$ 轮时，还剩一张正面大于反面的牌，此时爱丽丝会把它反过来，那么鲍勃面对的就会都是正面小于反面的牌。此时，选择正面比反面差距最小的牌（即以背面为参照物，使正面尽量大），是鲍勃的最佳策略。（大家感性理解哈）   

于是有如下策略：
1. 统计初始的时候正面数字大于反面数字的牌的数量。
1. 如果是偶数，那么把所有牌的最大值累加即可；如果是奇数，对于正反两面两个数差距最小的那张牌，计算最小值，否则计算最大值。

下面是喜闻乐见的代码时间：  
（在这里使用了亿点小技巧，即事先统计所有牌的最大值的和，当 $x$，即代码中的 $sum$，是奇数时，把这个和减去正反两面两个数差距最小的那张牌的正反两面两个数的差，就是答案。）
```cpp
#include<stdio.h>
long long n,a[200005],b[200005],sum,all,minn=2000000005;
long long abs(long long num) {return num>0?num:-num;}
long long max(long long a,long long b) {return a>b?a:b;}
long long min(long long a,long long b) {return a<b?a:b;}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]),sum+=(a[i]>b[i]),
    all+=max(a[i],b[i]),minn=min(minn,abs(a[i]-b[i]));
    if(sum&1) printf("%lld",all-minn);
    else printf("%lld",all);
}
```    

---

### 时间复杂度分析
由只有短短十三行的代码可以看出，这个思路的时间复杂度为 $O(n)$，十分轻松就通过了。    

在这里感谢[这位大佬](https://www.luogu.com.cn/user/808529)提供的思路，是他给我的思路帮助我一次就过了这道题，没吃罚时。    
完结撒花。

---

## 作者：TernaryTree (赞：1)

有趣题。

考虑 Bob 所选的牌在初始牌中的位置。假设他在原来红色数字中选了 $p$ 个，在蓝色数字中选了 $q$ 个。当 Alice 翻转一次后，$p$ 会变成 $p-1$ 或 $p+1$。要让方案成立，变化过后的 $p$ 应该 $>0$。而取走一个之后 $p$ 相较 Alice 操作前 要么不变要么 $-2$，这引导我们往奇偶性思考。

当 Bob 初始选了偶数张牌，则 Alice 翻转后为奇数，一定存在一张牌能选。而选走这张牌后能选的又变成了偶数，回到初始情况。

当 Bob 初始选了奇数张牌，Alice 可以操作使得其方案不成立。

所以答案即为在 $A$ 中选偶数个，剩余的选 $B$ 的最大值。

dp。设 $f_{i,0/1}$ 表示 $1\sim i$ 在 $A$ 中选了偶数/奇数个的最大值。有

$$
\begin{aligned}
&f_{i,0}=\max(f_{i-1,0}+B_i,f_{i-1,1}+A_i) \\
&f_{i,1}=\max(f_{i-1,0}+A_i,f_{i-1,1}+B_i)
\end{aligned}
$$

时间复杂度 $\Theta(n)$。

[Code](https://www.luogu.com.cn/paste/2sxsywlo)。

---

## 作者：gcx114514 (赞：0)

首先发现 Bob 第 $i$ 个位置至少可以获得 $\min(a_i,b_i)$ 的分数，设 $d_i=\text{abs}(a_i-b_i),f_i=[a_i>b_i] $ 那么每次 Alice 的操作可以看作选择一个位置将 $d_i$ 取反，Bob 的操作是删除一个位置，获得 $d_i\times f_i$ 的贡献。

考虑当存在 $d_i=1$ 时，Alice 一定是选择最大的满足 $d_i=1$ 的 $f_i$ 并将其 $d_i$ 取反。同理 Bob 一定删去的是最大满足 $d_i=1$ 的 $f_i$。

当不存在 $d_i=1$ 时，无论 Alice 选择哪个数将其 $d_i$ 取反，Bob 直接选择这个数将其删去，这样依然不存在 $d_i=1$。而对于 Bob，他一定会删去 $f_i$ 最小的数，这样转换成 Alice 来决策。

综上，直接用两个优先队列分别维护即可，时间复杂度 $O(n\log n)$。
### Code
```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define int long long
#define mk make_pair
#define se second
#define fi first
//#define mid ((l+r)>>1)
//#define rs now<<1|1
//#define ls now<<1
using namespace std;
bool Mst;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}


int a[Max],b[Max];
priority_queue<int,vector<int>,greater<int> >q;
priority_queue<int,vector<int>,less<int> >p;


bool Med;
signed main(){
	int n=read(),ans=0;
	for(int i=1;i<=n;++i){
		a[i]=read();b[i]=read();
		if(a[i]>b[i])p.push(abs(a[i]-b[i]));
		else q.push(abs(a[i]-b[i]));
		ans+=min(a[i],b[i]);
	}
	int opt=0;
	while(!p.empty()){
		if(!opt)q.push(p.top()),p.pop();
		else{
			ans+=p.top();p.pop();
		}
		opt^=1;
	}
	if(opt)q.pop();
	while(!q.empty()){ans+=q.top();q.pop();}
	cout << ans << '\n'; 
	
	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
/*

*/

```

---

## 作者：Lovely_Sun (赞：0)

假设 Bob 在游戏开始前决定了他想要每张牌的方向，并考虑他是否可以实现它。

在每个回合开始时，如果 Bob 想要的方向上的牌数是偶数，那么在 Alice 掷出一张牌后，这个牌数将是奇数。也就是说，它不可能是零，所以 Bob 可以在期望的方向上取一张牌。然后，下一个回合再次开始，在期望的方向上有偶数张牌。

因此，如果游戏开始时 Bob 想要的方向上有偶数张牌，他就可以在他想要的方向上挑出所有的牌（类似地，考虑奇偶性，如果游戏开始时 Bob 想要的方向上有奇数张牌，他就不可能在想要的方向上挑出所有的牌）。

如果带有 $A_i > B_i$ 的牌的数量是偶数，则最好将所有牌的所需方向设置为数量较大的一面，因为这样会导致所需方向上的牌的数量为偶数。当 $A_i > B_i$ 的牌数为奇数时，通过将牌数较小的一面设置为差值最小的牌的期望方向，游戏可以从期望方向上的偶数牌开始。这是最好的考虑，它是不可能挑出所有牌与较大的数字面朝上。

---

## 作者：gxp123 (赞：0)

# arc164 C - Reversible Card Game

## 题意

有 $N$ 张卡片，第 $i$ 张的正面写有数字 $A_i$，反面写有数字 $B_i$。

$\text{Alice}$ 和 $\text{Bob}$ 用这些卡片做游戏。

一开始所有卡片都是正面朝上。

每一轮 $\text{Alice}$ 任意翻转一张卡片，$\text{Bob}$ 任意取走一张卡片并得到这张卡片朝上一面的分值。

卡片全部取走则游戏结束。

$\text{Alice}$ 想要最小化 $\text{Bob}$ 的总分，而 $\text{Bob}$ 想要最大化。

问若两人都足够聪明，则 $\text{Bob}$ 的总分是多少。

- $ 1\leq\ N\leq\ 2\times 10^5 $
- $ 1\leq\ A_i,\ B_i\leq\ 10^9 $ $ (1\leq\ i\ \leq\ N) $

## 题解

仔细观察可以发现，我们选择的方案只和正面的数和反面的数的差值有关系。

换言之，因为我们一定会把所有卡片拿走，所以我们一定会拿卡牌上那一面较大的数。

所以我们把每张卡片的初始状态转换成 $C_i = A_i - B_i$。

则翻转一次就是把 $C_i = -C_i$。

答案就是 $\sum\limits_{i = 1}^{N}\frac{C_i + A_i+B_i}{2}$，$C_i$ 是我们最后选的值。

如果我们选的是 $C_i = A_i - B_i$，则 $\frac{C_i + A_i+B_i}{2} = A_i$，即我们选了 $A_i$。

如果我们选的是 $C_i = B_i - A_i$，则 $\frac{C_i + A_i+B_i}{2} = B_i$，即我们选了 $B_i$。

所以就满足了方案合法。

这样子，我们就把问题转化成了选数和把一个数变成相反数。

如果我们自己手推一下会发现，$\text{Bob}$ 至多会选一个 $C_i < 0$。

证明一下：

当场上还有 $C_i > 0$ 的牌时,

因为是最优，则 $\text{Alice}$ 一定会把当前 $C_i$ 最大的牌翻转；

否则它一定会被 $\text{Bob}$ 选走，同时 $\text{Bob}$ 也会的选 $C_i$ 尽可能大的牌。

存在 $C_i = 0$ ，在 $\text{Alice}$ 把所有能选的数字变成负数之后，$\text{Bob}$ 一定可以选 $0$（因为 $0$ 不受翻转影响）。

此后 $\text{Alice}$ 无论翻转哪张牌，都会被 $\text{Bob}$ 拿走（因为负数 $\rightarrow$ 正数之后，把它选走更优，如果翻转的是 $0$，则把它选走也是没有问题的）。

如果没有 $C_i = 0$，我们假设有偶数个 $C_i > 0$，则最后一张 $C_i > 0$ 一定会被 $\text{Bob}$ 选走。

此时场上一定剩下的都是 $C_i < 0$ 的牌， $\text{Alice}$ 无论翻转哪张牌，都会被 $\text{Bob}$ 拿走。

如果 $C_i > 0$ 的牌为奇数个，则最开始的所有满足 $C_i > 0$ 中 $C_i$ 最小的牌一定会被 $\text{Alice}$ 变成负数。

则此时 $\text{Bob}$ 一定会选最大的牌 $C_i < 0$ 把它选走。

此时场上一定剩下的都是 $C_i < 0$ 的牌， $\text{Alice}$ 无论翻转哪张牌，都会被 $\text{Bob}$ 拿走。

所以 $\text{Bob}$ 至多会选一个 $C_i < 0$。

我们假设 $\text{Alice}$ 把一个负数变成了正数，则 $\text{Bob}$ 一定会的选 $C_i$ 尽可能大的牌。

然后 $C_i > 0$ 的牌的数量并没有改变。

所以我们可以得到一个解法：

- 如果存在 $C_i = 0$ 或有偶数个 $C_i > 0$，则答案就是 $\sum\limits_{i = 1}^n \max(A_i,B_i)$。
- 否则，答案就是  $\sum\limits_{i = 1}^n \max(A_i,B_i) - \min\limits_{i = 1}^{n}\{|A_i - B_i|\}$。

时间复杂度：$O(N)$。

当然，我们也可以用堆维护选择的这个过程，时间复杂度是 $O(N \log N)$ 的。

都可以通过此题。

## code

### code 1

这个是直接 $O(N)$ 的代码。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

int main(){
	int n,i,c0 = 0,c1 = 0;
	long long ans = 0,cmin = (1ll << 60),a,b; 
	scanf("%d",&n);
	bool flag = false;
	for(i = 1 ; i <= n ; ++i){
		scanf("%lld%lld",&a,&b);
		ans += max(a,b);
		if(a - b == 0)	c0 ++;
		else if(a - b > 0)	c1 ++;
		cmin = min(cmin,abs(a - b));
	}
	if(c0 > 0 || ((c1 & 1) == 0))
		cout << ans << endl;
	else	cout << ans - cmin << endl;
	return 0;
}
```

#### code 2

这个是用堆维护过程代码。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;
const int maxN = 2e5 + 10;
ll s[maxN];
priority_queue<ll> q1,q2;
ll n;
int main(){
	scanf("%lld",&n);
	ll ans = 0ll;
	bool flag = false;
	int suma = 0;
	for(ll i = 1,a,b ; i <= n ; ++i){
		scanf("%lld%lld",&a,&b);
		ans += a + b;
		s[i] = a - b;
		if(a - b < 0ll)
			q1.push(a - b);
		else if(a - b >= 0ll)
			q2.push(a - b);
	}
	sort(s + 1,s + 1 + n);
	while(q1.size() || q2.size()){
		if(q2.size()){
			q1.push(-q2.top());
			q2.pop();
		}else{
			q2.push(-q1.top());
			q1.pop();
		}
		if(q2.size()){
			ans += q2.top();
			q2.pop();
		}else{
			ans += q1.top();
			q1.pop();
		}
	}
	printf("%lld",ans / 2);
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

发现我们每一次选一定是选他旋转过后让卡片变小，这次操作做差，取最大的那个。

因为假如不取就会被翻过来，然后就不如让他翻小的牌。

然后考虑翻牌的最优策略，发现可以每次翻差最大的牌，然后用优先队列来维护差就好了。

最后在看了题解之后发现还有 dp 解法，然后发现没看懂。。。

可能是我太菜了。。。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
struct node {
	i64 a, b;
	bool operator <(node _) const {
		return a - b < _.a - _.b;
	}
} c[maxn];
priority_queue<node> qp;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(6);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> c[i].a >> c[i].b;
	}
	for (int i = 1; i <= n; i++) {
		qp.push(c[i]);
	}
	i64 ans = 0;
	while (qp.size()) {
		node tp = qp.top();
		qp.pop();
		qp.push({tp.b, tp.a});
		ans += qp.top().a;
		qp.pop();
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [[ARC164C] Reversible Card Game ](https://www.luogu.com.cn/problem/AT_arc164_c)

不妨令 $c_i$ 表示 $\max(a_i,b_i)$，$d_i$ 表示 $\min(a_i,b_i)$，$delta_i$ 表示 $c_i-d_i$。显然 Bob 最好的情况下可以拿到 $c_i$，最坏也可以拿到 $d_i$，那么先将答案加上 $\sum_{i=1}^n d_i$。接下来就要考虑可以拿到哪些 $c_i$。于是问题变成了有 $n$ 张卡片，每一张有一面写有一个数值 $delta_i$，另一面是 $0$。Alice 每次可以翻转一张卡片，Bob 每次可以取走一张卡片并得到卡片正面的数值，问 Bob 最终最多可以获得的数值最大是多少。

考虑两种情况。如果当前所有卡片都是 $0$ 的那一面朝上，Alice 先手，那么显然 Bob 的总分为 $\sum delta_i$，因为 Alice 每把一张卡片翻过来 Bob 就会把它取走。如果是 Bob 先手，那么他肯定不能获得所有卡片的 $delta_i$ 之和，有一张卡片的 $delta_i$ 他拿不到。根据贪心，他肯定选择舍弃 $delta_i$ 最小的那张卡片。在他操作完后，就又变成了上面那种情况。

那么怎么样会变成上面的两种情况呢？假设初始时正面是 $delta_i$ 的卡片数量为 $cnt$。每一回合正面是 $delta_i$ 的卡片数量肯定会减少两张，因为 Alice 会把一张翻转，Bob 会拿走一张。那么如果 $cnt$ 是奇数，就是第二种情况，否则就是第一种。代码就很好写了。

code 
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll ans,sum;
int n,tot,minn=0x3f3f3f3f;
int a[N],b[N],d[N];
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) 
    {
        scanf("%d%d",&a[i],&b[i]);
        d[i]=abs(a[i]-b[i]);
        sum+=d[i];
        minn=min(minn,d[i]);
        ans+=min(a[i],b[i]);
        if (a[i]>b[i]) tot++;
    }
    if (tot&1) printf("%lld\n",ans+sum-minn);
    else printf("%lld\n",ans+sum);
    return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[Reversible Card Game](https://atcoder.jp/contests/arc164/tasks/arc164_c)。

贪心 + 构造好题。

## 思路

首先令 $cta$ 记录的就是 $B_i<A_i$ 的数量，$ctb$ 记录的就是 $B_i\geq A_i$ 的数量。

那么 Bob 的任务就是尽可能多的取大的一面，他必须逼迫 Alice 将小的一面翻到下面。

以样例二为例，Alice 第一次会将正面为 $918378176$ 的卡片翻过去，以免 Bob 取到最优值。Bob 在 Alice 操作后第一次取走正面为 $701849287$ 的卡片。

然后 Alice 将正面为 $610749017$ 的卡片翻过去，此时可以发现，对于任意卡片，Bob 能取到的正面的数都小于反面，Bob 无奈只能取走正反面差值最小的。

Bob 取走以后，仍然对于任意卡片，正面的数都小于反面，Alice 也无奈，只能反转一张卡片，接下来，Alice 反转哪张，Bob 就去哪张，直到取完，Bob 取到的都是较大面。

这样的话我们的答案为所有较大面之和减去最小的正反面之差，但是不是所有的情况都是这样。

如果再Bob取完最后一张原本正面小于反面的卡片之后，Alice 只好反转一张，之后 Alice 反转哪张，Bob 就去哪张，直到取完，Bob 取到的都是较大面，这样 Bob 取到的全都是较大面。

那么是 Alice 反转最后一张正面小于反面的卡片还是 Bob 取走最后一张正面小于反面的卡片成为了这题的关键。我们很容易发现，当正面大于反面的数量为 $2$ 的倍数时，也就是 $cta$ 为 $2$ 的倍数时，Bob 取走最后一张，否则 Alice 反转最后一张。

根据上述思路，我们就可以写出代码了：[我的 AC
记录 + 代码](https://atcoder.jp/contests/arc164/submissions/43431980)

---

## 作者：未来姚班zyl (赞：0)

### 本题解为 $O(N)$ 的做法
## 题目大意
有 $N$ 张卡牌，每张卡牌的正反两面分别印着 $A_i,B_i$ 两个数字，初始时派都正面朝上，现在 Alice 和 Bob 按以下规则轮流操作，直到游戏结束：

进行 $N$ 个回合，每个回合中，Alice 先将一张牌翻面，然后 Bob 拿走桌面上的一张牌，并获得其朝上的那一面的数字的分数。

Alice 尽全力最小化 Bob 的分数，Bob 尽全力最大化 Bob 的分数，且他们都绝顶聪明。问最后 Bob 得了多少分。

## 题目分析

由于所有的牌最后都会被取走，我们可以先对每张卡牌的较小的值求和，设其为 $ans$，做为一个基本的分数，然后定义每张卡牌的权值 $W_i$ 为较大值与较小值的差，状态 $F_i$ 为较大值是否朝上，是就是 $1$，否则为 $0$。则 Alice 的操作为选择一个 $i$，使得 $F_i$ 异或 $1$，Bob 的操作的就是选择一个 $i$，如果此时 $F_i$ 等于 $1$，则获得 $W_i$ 的贡献，同时，把卡牌 $i$ 移除。特别地，如果 $W_i=0$，则初步将 $F_i$ 的值视为 $0$。


首先，给出结论：

最终的答案为 $ans+\sum\limits_{1\le i\le n}W_i-\min\limits_{1\le i\le n}W_i$，当且仅当初始时 $\sum\limits_{1\le i\le n}F_i$ 为奇数且不存在 $1\le i\le n,A_i=B_i$，否则，最终的答案为 $ans+\sum\limits_{1\le i\le n}W_i$。

接着，给出证明：

- 结论一：当前的牌的状态全部为 $0$ 时，如果此时 Alice 先手，则答案得到这些牌的权值之和的贡献。

这个结论显然，Alice 翻哪张，Bob 就选哪张，这样每次 Bob 选择时，被选的牌的状态都为 $1$。

- 结论二：当前的牌的状态全部为 $0$ 时，如果此时 Bob 先手，则答案得到这些牌的权值之和减去其中最小的权值的贡献。

这个结论也显然，因为 Bob 选完一个后，就会变成结论一的情况。所以要最大化选完后的牌的权值和，即最小化选择的牌的权值。

- 结论三：Bob 最多只需要选择一次状态为 $0$ 的牌。

如果当前的牌还有状态为 $1$，Bob 就会选择状态为 $1$ 的牌，这绝对比选择状态 $0$ 的更优。否则就进入到结论一和二的情况。

- 结论四：当前的牌中状态为 $1$ 的牌的数量为偶数，且 Alice 先手时，Bob 可以得到所有的卡牌的权值的贡献。

如果 Alice 选择将一个状态为 $0$ 的卡牌翻面，则 Bob 把被翻的卡牌取走，不仅得到对应的贡献，而且局面不变，直到没有状态为 $0$ 卡牌。

如果 Alice 选择将一个状态为 $1$ 的卡牌翻面，则 Bob 从剩下的卡牌中取走一张，得到对应的贡献，状态为 $1$ 的卡牌数减少 $2$，直到没有状态为 $1$ 的卡牌，此时，符合结论一。

- 定义一：定义 Bob 能得到所有卡牌的权值的局面为 Bob 的必胜态。

- 结论五：当前的牌中状态为 $1$ 的卡牌的数量为奇数，且 Alice 先手，且当前的牌中不存在 $W_i=0$ 时，Bob 无法达到必胜态。

无论 Alice 怎么翻，Bob 为了维持必胜态，都得选一张状态为 $1$ 的牌取走，这会使得状态为 $1$ 的卡牌数量一直为奇数，直到剩一张状态为 $1$ 的卡牌时，Alice 将其翻面，符合结论二的局面，无法达到必胜态。

因此，Bob 为了最小化损失，就会让最终的卡牌的中的权值的最小值最小，而还剩 $2$ 张以上牌供他选择时，他总可以不选到所有的权值中最小的那一张。

- 最终结论得证。

若初始的牌中不含有 $W_i=0$ 的牌，则对应结论四和结论五。

如果有 $W_i=0$ 的牌，当处于结论四的状态时，处于必胜态，否则，将当中的一张牌的状态视为 $1$（可以这么做是因为无论状态是什么都不会造成贡献），则成为结论四的局面。

题外话：这题就到这里解决了。但是赛时由于这样研究了特别久，还干不过暴力模拟，等别人 D 题写完，我才想出这个结论，等到想出 D 题就没时间写代码了，这场 ARC 就 G 了（卑微）。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int inf=2147000000;
using namespace std;
int n,x,y,cnt,m=inf;
ll ans;
int main(){
	n=read();
	rep(i,1,n){
		x=read(),y=read(),m=min(m,abs(x-y));
		if(x>y)cnt++;
		ans+=max(x,y);
	}
	if(cnt&1)ans-=m;
	cout <<ans;
	return 0;
}
```

 

---

