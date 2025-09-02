# [ARC185A] mod M Game 2

## 题目描述

Alice 和 Bob 在玩游戏，初始时他们分别有 $n$ 张牌，上面分别写着 $1\sim n$ 的整数。同时他们给出了一个大于 $n$ 的整数 $m$。现在两个人从 Alice 开始轮流取出一张牌放入牌堆中。如果某一次放牌后牌堆中所有牌的数字之和可以被 $m$ 整除，那么放牌的人就输了，另外一个人就赢了。如果所有牌全部放完后依旧没有分出胜负，那么 Alice 将会赢得胜利。现在给出每次对局的 $n$ 和 $m$，请问在两人都绝对聪明的情况下，谁会取得胜利？

## 说明/提示

对于所有数据，$1\le T\le10^5,1\le n<m\le10^9$。

翻译 @Cure_Wing。

## 样例 #1

### 输入

```
8
2 3
3 6
5 9
45 58
39 94
36 54
74 80
61 95```

### 输出

```
Alice
Alice
Bob
Bob
Alice
Bob
Bob
Alice```

# 题解

## 作者：hh弟中弟 (赞：3)

首先当一个人手中有两张及以上的牌时，他一定不会在当前回合输，所以游戏的胜负都是在 Alice 打出最后一张牌时确定，设 $sum$ 为牌的总价值。\
首先考虑 Alice 最后获胜的情况，此时两人都打完了所有的牌，所以直接计算 $sum$ 是否是 $M$ 的倍数即可。\
再考虑 Alice 打出最后一张后输掉的情况，此时 Bob 手中还剩一张牌 $x$，可以确定此时 $M\mid sum-x$，即 $sum\bmod M=x$，所以我们需要知道是否存在这样的一张牌，这样 Bob 会一直保留它到最后来获胜，计算 $x$ 即可。\
还剩下一个问题，Bob 为什么能保留 $x$，在牌数大于二时，这是显然的，当 Bob 只剩两张牌 $x,y$ 时，此时 Alice 还剩一张 $s$，如果 $m\mid sum-x-s$，那么 Bob 不能打出 $y$，只能打 $x$，又因为 $x=sum\bmod M$，所以 $s\equiv 0\pmod M$，这是不可能的，所以 Bob 一定能保留 $x$ 到最后。\
综上，当 $1\le sum\bmod M\le n$ 时，Bob 必胜，否则 Alice 必胜。

---

## 作者：Binah_cyc (赞：2)

ARC 人类智慧题。

我们可以发现一个十分显然的性质：当一个人手中剩余的牌数多于一张时，这个游戏不会有结果。只有当一个人只剩一张牌的时候，这个游戏才有可能结束。

设整个游戏中所有的牌点数之和为 $sum$，易得 $sum=n \times (n+1)$。

因此，我们快进到 Alice 和 Bob 都只剩下了一张牌，考虑这个时候谁会赢。

考虑 Bob 在手中剩下的牌是哪一张。

设 Bob 手中的牌为 $x$，如果 $m|sum-x$，即 $sum \equiv x \pmod m$，那么 Alice 必输。因为 $sum-x$ 是在 Alice 出完自己最后一张牌，Bob 手中还剩余一张 $x$ 时桌子上牌的点数总和。无论 Alice 怎么出牌，当她出完最后一张牌的时候，桌子上的牌必定是 $m$ 的倍数。

所以，只要 Bob 狡猾的提前算出 $x$ 是多少，并且一直不出这张牌，就能达到必胜的效果。

同时，我们考虑 Alice 能否反制。~~A 题肯定没有那么复杂，直接不考虑了。~~

Alice 也能够知道 $x$ 的值，所以她会思考如何反制。同样的，我们设在倒数第三个回合时，Alice 手中留了一张 $y$，Bob 手中留了 $x$ 与 $k$。这时，Alice 想要让 Bob 只能出 $x$，就要满足 $m|sum -x-y$，即 $sum \equiv x+y \pmod m$。

又因为 $sum \equiv x \pmod m$，所以 $0 \equiv y \pmod m$，即 $m|y$。

又因为 $0 \le y \le n \le m$，所以上面的同余式无法成立，即 Alice 没有反制的机会。

但是，我们前面的讨论都建立在 $m$ **存在**的情况，我们现在还要讨论 $m$ 是否存在。

因为 $sum \equiv x \pmod m$，$x \le n \le m$，所以 $x = sum \bmod m$。

因此，我们只需要判断 $sum \bmod m$ 是否小于等于 $n$ 即可。若小于等于 $n$，那么 Bob 可以预留这张牌，并且 Alice 没有反击的机会。相反，Bob只有这一张牌能够击败 Alice，如果 Bob 没有这张牌，游戏将流局，系统判定 Alice 获胜。

感觉讲的够清楚了，代码就不放了。

---

## 作者：Ratio_Y (赞：2)

分值给 600 有点过于高了，还是很水的。

---

## 结论

当自己手中的牌数大于一张时均不会立即输掉游戏。

## 证明

反证法。

设 Alice 还剩 $n$ 张牌 $a_1,a_2\cdots a_n$ 时出任意一张牌均会使自己输掉比赛（立即结束），设当前打出的牌的总和为 $s$，那么根据题意，有 $a_i+s\equiv 0 \pmod m$。已知 $a_i$ 互不相同，那么满足此情况的条件为 $a_i=(i-1)\times m+x$。而 $a_i$ 是一个 $n$ 的排列，题目给定 $n\lt m$，因此假设不成立，结论得证。

## 思路

证出结论后就很好办了，考虑到 Alice 先手，因此只需考虑 Alice 在打最后一张牌时会不会使自己输掉游戏（立即结束）。转化一下，即此时 Bob 还有一张牌未打，Alice 打出所有牌，判断此时打出牌之和是否为 $m$ 的倍数即可。

考虑 Bob 赢的情况。设 $s=\sum_{i=1}^n\ i$，Bob 最后未打的牌为 $x$，那么有 $2\times s-x\equiv 0\pmod m$，转换一下，即 $2\times s-\lfloor{\frac{2\times s}{m}}\rfloor{}\times m=x$。我们判断一下 $2\times s-\lfloor{\frac{2\times s}{m}}\rfloor{}$ 是否在区间 $\left[1,n\right]$ 内即可。

## 实现

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int Ratio = 0;
int T, n, m;

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		ll sum = 1ll * n * (n + 1);
		ll zc = (sum / m) * m;
		if(sum - zc >= 1 && sum - zc <= n) printf("Bob\n");
		else printf("Alice\n");
	}
	return Ratio;
}
```


---

完结撒花~

---

## 作者：WuMin4 (赞：2)

## [[ARC185A] mod M Game 2](https://atcoder.jp/contests/arc185/tasks/arc185_a)

## 题意

Alice 和 Bob 每人手里有 $n$ 张牌，牌上有数字 $1,2,\cdots,n$，从 Alice 开始轮流出牌，若一个人出牌后场上牌数字的总和能被 $m$ 整除，则这个人输掉，若两人的牌都出完后还没有人输，则 Alice 获胜。

给出 $n,m\pod{n<m}$，问两人都进行最优操作后谁会赢。

## 思路

显然若一个玩家手中牌的数量 $\ge2$，那么他出牌后一定不会输。因为 $n<m$，所以不存在两张数字为 $x,y \pod{x\neq y}$ 的牌使得 $x,y\equiv 0\pmod{m}$，两张以上同理，由此我们可以知道输赢的关键就在 Alice 和 Bob 只剩一张牌的时候。

因为 Alice 先手，所以两人只剩一张牌时是 Alice 先出。Alice 出完牌后，场上的牌的数字和即为 $n\times(n+1)-x$，其中 $x$ 即为 Bob 最后一张牌的数字。Bob 如果想赢，则需要 $n\times(n+1)-x\equiv 0\pmod m$，即 $x=(n\times(n+1))\bmod m$。

那么 Alice 是否可以使 Bob 不剩下数字为 $x$ 的牌呢？若 Alice 出完倒数第二张牌后剩下一张数字为 $y$ 的牌，则 Bob 打出一张牌后场上的牌的数字和为 $n\times (n+1)-x-y$，因为 $n\times(n+1)-x\equiv 0\pmod m$ 且 $1\le y\le n$，所以 $n\times (n+1)-x-y\equiv 0\pmod m$ 不会成立。


因为牌的数字为 $1,2,\cdots,n$，所以当 $1\le x\le n$ 时，Bob 获胜，否则牌会全部出完，Alice 获胜。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long n,m;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>T;
	while(T--){
		cin>>n>>m;
		cout<<(n*(n+1)%m==0?"Alice":(n*(n+1)%m<=n?"Bob":"Alice"))<<endl;
	}
	return 0;
}
```

---

## 作者：hyc42 (赞：1)

## 前置
[题目传送门 1（洛谷）](https://www.luogu.com.cn/problem/AT_arc185_a)

[题目传送门 2（AT）](https://atcoder.jp/contests/arc185/tasks/arc185_a)

[AC 记录](https://www.luogu.com.cn/record/179917011)

## 题目大意
Alice 和 Bob 每个人有 $n$ 张牌，分别是 $1,2,3…n$，从 Alice 开始轮流出牌，若其中有一个人出牌之后场上牌数字总和能被 $m$ 整除（~~居然要算总和，没事干求总和干啥~~），则这个人就输了（~~奇葩的规定~~），若两人出完牌还没有人输，则 Alice 就赢了。（~~这对 Bob 来说不公平~~）

给出 $n,m（n<m）$，问两个人都进行最优策略后获胜的是谁。

## 思路
其实，最重要的是他们还剩下最后一张牌的时候，因为：

- 如果他们有两张及以上的牌，就可以选择不出让自己输掉的牌，所以他们不会立刻输掉。

- 因为是 Alice 先出牌，所以他们只剩一张时也是 Alice 先出。如果 Alice 出最后一张牌时没有输，则 Bob 无论出最后一张牌的结果如何，Alice 都会赢。

因此，Alice 出最后一张牌的时候是决定了游戏的输赢。

我们先假设 $x$ 是 Bob 的最后一张牌。当 Alice 出了最后一张牌的时候，所出的牌总和是 $n\times(n+1)-x$。所以，我们要考虑 $n\times(n+1)-x\mod m$ 是否为 $0$。

如果当 $n\times(n+1)-x=0$时，也就是 $1\leq(n\times(n+1)\mod m)$ 时，我们假设 $y=n\times(n+1)\mod m$。如果 Bob 在之前除了 $y$ 之外的所有牌全都打出了，这样 $x=y$，那么 Alice 在打出最后一张牌时就会输，所以 Bob 获胜了。这是肯能的，因为当 Bob 剩二张及以上的牌时，除了 $y$ 之外还有一张及以上的牌，所以可以保留 $y$ 而不会输。

如果当 $n\times(n+1)-x\neq 0$ 时，则 Alice 保证会赢。

所以，就判断 $1\leq (n\times(n+1)\mod m\leq n)$ 就行了。

## 注意
判断时注意要开 long long，否则会错误。

[没开 long long 的后果](https://www.luogu.com.cn/record/182730384)

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		if(1ll*n*(n+1)%m==0||1ll*n*(n+1)%m>n)cout<<"Alice\n";//判断（注意 long long）
		else cout<<"Bob\n";
	}
	return 0;
}
```
## 祝大家能 AC！！！

---

## 作者：Noah2022 (赞：0)

### 题目大意
每人有 $ N $ 张牌，每人轮流出牌，爱丽丝先，鲍勃后。若某一时刻，桌上的牌之和为 $ M $ 的倍数，则出这张牌的人输，另一人赢。**注：若所有牌都出完了都没结束，则爱丽丝赢。**

### 思路
> 首先，每人的牌的和为 $ \frac{n \times (n+1)}{2} $ 两人牌的总和为 $ n \times (n+1) $ 。

> 其次，如果 $ n \times (n+1) \bmod M $ 为 $ 0 $ ，则保证爱丽丝可以通过手段使游戏顺利进行到最后，最后一次鲍勃出完后输，这种情况鲍勃不可能赢。

> 然后，如果 $ n \times (n+1) \bmod M \le n $ ， 则鲍勃一直不出模剩出来的那张牌，使出现上面相反的情况，则鲍勃必胜。

> 最后，如果 $ n \times (n+1) \bmod M > n $ ，则爱丽丝可以使剩余的牌 $ \bmod M $ 的值变为 $ N + 1 $ ，下一步鲍勃出完后必为第二种情况，所以，爱丽丝必赢。 

**综上所述：** 只有 $ n \times (n+1) \bmod M $ 为 $ 0 $ 时，鲍勃会赢，其余情况皆为爱丽丝赢。

**十年 OI 一场空，不开 long long 见祖宗。**

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,t;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		if(n*(n+1)%m==0||n*(n+1)%m>n) // 判断Alice赢的情况
		{
			cout<<"Alice\n";
		}
		else
		{
			cout<<"Bob\n";
		}
	}
	return 0; // 完美结束
}
```

---

