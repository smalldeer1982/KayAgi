# Sasha and the Casino

## 题目描述

Sasha decided to give his girlfriend the best handbag, but unfortunately for Sasha, it is very expensive. Therefore, Sasha wants to earn it. After looking at earning tips on the internet, he decided to go to the casino.

Sasha knows that the casino operates under the following rules. If Sasha places a bet of $ y $ coins (where $ y $ is a positive integer), then in case of winning, he will receive $ y \cdot k $ coins (i.e., his number of coins will increase by $ y \cdot (k - 1) $ ). And in case of losing, he will lose the entire bet amount (i.e., his number of coins will decrease by $ y $ ).

Note that the bet amount must always be a positive ( $ > 0 $ ) integer and cannot exceed Sasha's current number of coins.

Sasha also knows that there is a promotion at the casino: he cannot lose more than $ x $ times in a row.

Initially, Sasha has $ a $ coins. He wonders whether he can place bets such that he is guaranteed to win any number of coins. In other words, is it true that for any integer $ n $ , Sasha can make bets so that for any outcome that does not contradict the rules described above, at some moment of time he will have at least $ n $ coins.

## 说明/提示

In the first test case, Sasha can proceed as follows:

- If Sasha places a bet for the first time or if he won the previous bet, then he places $ 1 $ coin.
- If Sasha lost the previous bet, then he places $ 2 $ coins.

Note that Sasha cannot lose more than once in a row.

It can be proven that with this strategy, Sasha can obtain as many coins as he wants.

In the second test case, Sasha can only place $ 1 $ coin for the first time. But in case of a loss, he will not be able to place any more bets, so he will not be able to guarantee having as many coins as he wants.

## 样例 #1

### 输入

```
9
2 1 7
2 1 1
2 3 15
3 3 6
4 4 5
5 4 7
4 88 1000000000
25 69 231
13 97 18806```

### 输出

```
YES
NO
YES
NO
NO
YES
NO
NO
NO```

# 题解

## 作者：_Ink (赞：13)

介绍一下倍投法。

我们先来考虑一个很经典的赌徒问题：

你现在有一定数量的金币，而你面前有一个神奇的盒子。把一些金币投进去，有一半的概率会成功，使金币数量翻倍；有一半的概率会失败，金币会消失。投入不限次数。问怎样才能使你赚的更多。

而这个经典问题有一种经典的方案，就是倍投法。简而言之，倍投法可以概括为两个步骤：

- 1、如果是第一次投或者上一次投金币成功翻倍，则本次投 1 金币。

- 2、如果上一次投金币消失，则本次投上一次投的金币数的两倍。

为什么这样投是合理的呢？

假如我们已经投了 $n$ 次，前 $n-1$ 次全部失败，那么我们已经亏损了 $1+2+4+...+2^{n-1}=2^n-1$ 的金币。但是如果我第 $n$ 次成功了，我可以赚得 $2^k$ 数量的金币。这样相当于把以前亏的金币全部赚回来了。而在成功与失败概率不变的情况下，连续失败的概率会越来越小。所以，倍投法是一种理论上“稳赚不赔”的方法。

当然，之所以是“理论上”，是因为倍投法受限于很多限制。比如你需要有足够多的本金（初始金币），以及必须保证成功与失败概率不变等。

---

回到本题。

本题不一样的地方在于，赢得的钱数是投注的 $(k-1)$ 倍。

但其实这无伤大雅。我们发现倍投法的主要思想在于，用某一次赢的钱来赚回之前所有亏损的钱。

所以我们一样可以利用倍投法的思想：如果我们已经投了 $n$ 次，前 $n-1$ 全部失败，那么第 $n$ 次要投的钱数 $c_n$ 满足 $c_n \times (k-1) > \sum_{i=1}^{n-1}{c_i}$ 即可。这是可以递推做的。

另外，本题限制了不会连续输超过 $x$ 次。所以最坏的情况下就是连续输了 $x$ 次，换句话说就是你需要连续下注 $x+1$ 次。所以你必须要保证你的本金数必须支持你下注这 $x+1$ 次。如果本金数不够，答案显然是 `NO`。否则就是 `YES` 了。

---

## $\text{main code:}$

```cpp
void solve()
{
	int k, x, a; cin >> k >> x >> a;
	ll sum = 0;
	for(int i = 1; i <= x + 1; i ++){
		sum += sum / (k - 1) + 1;
		if(sum > a) {cout << "NO\n"; return;}
	}
	cout << "YES\n";
}
```

---

## 作者：CaoXian (赞：12)

保底是下注 $x + 1$ 次赢一次，所以现在假设我们次次都吃保底，如何安排每一次下注的金额才能使得最终能盈利？

不妨设第 $i$ 次下注的金额为 $c_{i}$，那么应该有：

$$
\sum\limits_{i = 1}^{x + 1}c_{i} < kc_{x + 1}
$$

把一个 $c_{x + 1}$ 抵消掉，再把 $k - 1$ 除过去：


$$
\dfrac{\sum\limits_{i = 1}^{x}c_{i}}{k - 1} < c_{x + 1}
$$

如果我们运气好一点了，没吃保底，那么这个条件也应是一样的，所以假设我们会在第 $i$ 次下注后盈利，那么有：

$$
\dfrac{\sum\limits_{j = 1}^{i - 1}c_{j}}{k - 1} < c_{i}
$$

而我们不知道会在哪一次下注后盈利，所以在一次保底内我们应保证每一个 $i$ 都满足上面的式子，也就是：

$$
\begin{cases}
\dfrac{c_{1}}{k - 1} < c_{2}\\
\dfrac{c_{1} + c_{2}}{k - 1} < c_{3}\\
\dfrac{c_{1} + c_{2} + c_{3}}{k - 1} < c_{4}\\
\cdots\\
\dfrac{\sum\limits_{j = 1}^{x}c_{j}}{k - 1} < c_{x + 1}\\
\end{cases}
$$

对于第一次下注，此时赢的话肯定是盈利的（因为 $k \geqslant 2$），所以不用考虑。

而上面只是不考虑总金额的情况下，为了使我们的钱够用，每一次下注的金额应取到下限，也就是：

$$
c_{i} = \left\lfloor\dfrac{\sum\limits_{j = 1}^{i - 1}c_{j}}{k - 1}\right\rfloor + 1
$$

$c_{1}$ 显然会取到 $1$。

上面的求和式用一个前缀和优化即可。

最后检查 $\sum\limits_{i = 1}^{x + 1}c_{i}$ 和 $a$ 的大小关系，若 $\sum\limits_{i = 1}^{x + 1}c_{i} \leqslant a$ 说明钱够用，可以一直盈利，输出 `YES`，否则输出 `NO`。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t, k, x, a, sum, c[105];
bool flag;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> k >> x >> a;
		c[1] = 1, sum = 0, flag = true;
		for(int i = 1; i <= x; ++i) {
			sum += c[i];
			c[i + 1] = sum / (k - 1) + 1;
			if(sum > a) {
				flag = false;
				break;
			}
		}
		sum += c[x + 1];
		if(sum <= a && flag) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
```

---

## 作者：No_Rest (赞：6)

## 思路

~~赛场上被题目描述的 at least $n$ coins 给坑了，痛失青名 www。~~

为了让 Sasha 能赢回来钱，必须保证任意回合赢回来的钱比用作赌博所花的钱多。令 $b_i$ 为为保证第 $i$ 回合赢后钱比初始钱多的最小下注钱数，那么可以得到： 

$$b_i \times (k-1) > \displaystyle \sum^{i-1}_{j=1} b_j$$

即

$$b_i \ge \lfloor \frac{\sum^{i-1}_{j=1} b_j}{k-1} \rfloor + 1$$

为了使 $b_i$ 尽量小，那么 $b_i$ 就应该取 $\lfloor \frac{\sum^{i-1}_{j=1} b_j}{k-1} \rfloor + 1$。

于是一个循环就结束了，注意循环要从 $1$ 到 $x + 1$（想想 $b_{x + 1}  $ 的定义：为保证第 $x + 1$ 回合赢后钱比初始钱多的最小下注钱数），一旦 $\displaystyle \sum^{x+1}_{i=1} b_i > a$ 就输出 $\texttt{No}$。

时间复杂度 $\mathcal O(Tx)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Yes puts("Yes")
#define No puts("No")
using namespace std;
const ll maxn = 2e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), k, x, a, sum, b[maxn];
void solve(){
	k = read(), x = read(), a = read(), sum = 0;
	for(ll i = 1; i <= x + 1; ++i){//注意从 1 到 x + 1
		b[i] = floor(1.0 * sum / (k - 1)) + 1, sum += b[i];//计算 b[i] 与 sum
		if(sum > a){//如果下注所用的钱数和比原来钱还要多，就输出 No
			No;
			return;
		}
	}
	Yes;
}
int main(){	
	for(; t; --t) solve(); 
    return 0;
}
```

---

## 作者：ran_qwq (赞：6)

你在赌场，初始有 $a$ 块钱。

你每次可以下注任意正整数 $n$ 块钱（$n\le a$）。如果你赢了可以获得 $nk$ 块钱（在下注过程中赚 $n(k-1)$ 块钱）；如果你输了这 $n$ 块钱就不会还。

除此之外，你还保证不会连续输超过 $x$ 轮。

你可以进行无限轮下注，求是否可以赢得无限块钱。

$2\le k\le30$，$1\le x\le100$，$1\le a\le10^9$。

---
换句话说，你需要构造一种方案，使得开始时输任意 $t\in[0,x]$ 场，再赢一场能回本。回本后更能进行这些操作，更能继续加。

如果 $t=0$，肯定能回本。

如果 $t=1$，先下注 $p$ 块钱，再把剩下的 $a-p$ 块钱全部丢进去。

如果 $t=2$，因为你不知道 $t$ 是多少，所以要先下注 $p$ 块钱，再下注 $\lfloor\dfrac{p}{k-1}\rfloor+1$ 块钱（让 $t=1$ 时回本），最后把剩下的钱全部丢进去。

以此类推。如果存在一个 $t$，这样下不够钱就输出 `NO`。因为要让剩下的钱尽量多，所以令 $p=1$。

如果 $t=x$ 时剩下的钱下注不能回本也输出 `NO`。

否则输出 `YES`。

---

## 作者：ECNUAT_LZX (赞：1)

这道题可以使用**倍投法**的思想来做。所谓倍投法，顾名思义，成倍成倍的投注。例如：你在赌钱，你有 $\frac{1}{2}$ 的概率会获得 $2$ 倍的赌注，你也有 $\frac{1}{2}$ 的概率会输掉赌注，一分不得。按倍投法算，你可以每次赌 上一次赌的两倍（第一次赌 $1$ 元），这样理论上是稳赚不赔的。

因为就算你输了 $n-1$ 局，累计输的钱是 $2^0 +2^1+...+2^{n-1} = 2^n-1$ ，在第 $n$ 局成功就会赚 $2^n$ 元，将此前输的全部赚回来，且因为连续输的概率会越来越低，就会越来越容易赚。

但由于输的钱可能超过本金，还有输的概率问题，此方法只是理论上的。

回到本题，题目是赚 $ky$ 元，且不会一直输，便可以应用倍投法的思路，将每次赌的值递推求出，我们可以用 $f[i]$ 表示第 $i$ 轮的最大亏损值,并可以得出以下式子 $f[i] * (k-1) > f[1]+f[2]+f[3]+...+f[i-1]$ ，可以转化为 $f[i] = f[i - 1] + f[i - 1] / (k - 1) + 1$ 。如果超过了 $a$ ，就表示回不了本，就不行，反之可以。于是可以得出以下递推代码。


**源代码：**
```cpp
#include<bits/stdc++.h>

#define int long long
using namespace std;
int f[110];

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int a, x, k;
        cin >> k >> x >> a;
        memset(f, 0, sizeof(f));
        bool flag = 0;
        for (int i = 1; i <= x + 1; i++) {
            f[i] = f[i - 1] + f[i - 1] / (k - 1) + 1;//f[n] * (k-1) > f[n-1]
            if (f[i] > a) {
                puts("NO");
                flag = 1;
                break;
            }
        }
        if (!flag) {
            puts("YES");
        }
    }
    return 0;
}
```

---

## 作者：ylch (赞：1)

# [CF1929C](https://www.luogu.com.cn/problem/CF1929C) Sasha and the Casino 题解

## 题目大意

萨沙去赌场，赌场是按照以下规则运作的。假设下注 $y$ 硬币（$y$ 是正整数），那么如果获胜，将获得 $y\cdot k$ 枚
硬币（即，他的硬币数量将增加 $y\cdot(k-1)$ 枚）。如果输了，他将输掉全部赌注（即，他的硬币数量将减少 $y$ 枚）。

同时萨沙知道了赌场有一个促销活动：每个客户最多输 $x$ 次。

最初，萨沙有 $a$ 枚硬币。他想知道自己是否可以按照某种方法下注，从而保证一定可以赢得无限数量的硬币。

$2\leq k\leq 30,1\leq x\leq 100,1\leq a\leq 10^9$

## 解题方法

考虑怎样的策略是最优的，可以在每一次赢的时候都可以连本带利地把钱赚回来。

因为最多输 $x$ 次，所以可以把每 $(x+1)$ 轮看作一个轮回，同时只要考虑前 $x$ 轮全输的最坏情况即可。（因为如果我们在最坏情况下都可以回本的话，那不输到 $x$ 轮就赢了我们肯定也能回本，回的还更多）。

乍一看没有思路，尝试模拟样例：

`2 1 7` 输出是 `YES`。

第一次投 $1$ 个，输，还剩 $6$ 个；
 
第二次投 $1$ 个，必须赢，还剩 $5+1 \times 2=7$ 个；
 
循环往复，我们可以赚到无限多的钱。


------------

`3 3 6` 输出是 `NO`。

第一次投 $1$ 个，输，还剩 $5$ 个；

第二次投 $1$ 个，输，还剩 $4$ 个；

第三次投 $2$ 个，输，还剩 $2$ 个（本轮投 $1$ 个，赢的话还剩 $3+1 \times 3=6$ 个，只能回本，赚不了钱）；

第四次只能投 $2$ 个（此时只剩 $2$ 个金币），必须赢，还剩 $0+2 \times 3=6$ 个；

发现我们每次 $(x+1)$ 轮的轮回都卡在 $6$ 个金币上，会陷入死循环，所以不行。


------------

通过模拟样例，我们好像发现了一个规律：开始投 $1$；后来每一轮投的数量是 $y$，保证如果本轮赢的话，$y \times k$ 大于前面的总投注。

设当前进行到第 $t$ 轮，$b_i$ 表示**第 $i$ 轮赢的话可以赚钱的最少下注钱数**。

则可以推出数学公式：

$$
b_t \times k > \sum\limits_{i=1}\limits^{t}b_i
$$


等式两边各消掉一个 $b_t$，得

$$
b_t \times (k-1) > \sum\limits_{i=1}\limits^{t-1}b_i
$$

即

$$
b_t > \dfrac{\sum\limits_{i=1}\limits^{t-1}b_i}{k-1}
$$

因为我们要赚钱，也就是说每一轮的投注金额都要在满足如果当前轮赢可以赚钱的条件下尽量取**最低**。


变换公式为

$$
b_t \ge \lfloor \dfrac{\sum\limits_{i=1}\limits^{t-1}b_i}{k-1}\rfloor + 1
$$

所以每一轮下注的就是最小的满足条件的金额，即

$$
b_t \ge \lfloor \dfrac{\sum\limits_{i=1}\limits^{t-1}b_i}{k-1}\rfloor + 1
$$

这样判断条件就是：只循环一个轮回（$x+1$ 轮），如果在每一轮的投注金额是**满足如果当前轮赢可以赚钱的条件的最低值**，且到第 $(x+1)$ 轮时还有钱，说明一定可以赚到无限多的钱，输出 `YES`；

如果半道没钱了，那么连回本都是问题，更别说赚无限的钱了，输出 `NO`。

这样每次只要循环 $(x+1)$ 次，时间复杂度约为 $O(Tx)$。

## AC 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve()
{
    int k, x, a;
    cin >> k >> x >> a;

    ll sum = 0; // 记录前面轮投注的总钱数，要开long long
    vector <int> b; // 记录每一轮的投注
    b.push_back(1); // 第一轮固定投1个
    for(int i = 0; i < x + 1; i ++){ // 循环x+1轮
        sum += b[i];
        b.push_back(sum / (k - 1) + 1); // 计算下一轮的最小投注
        if(sum > a){ // 没有钱了
            cout << "NO\n";
            return ;
        }
    }
    cout << "YES\n"; // 没钱的情况在循环末尾已经判断完了，这里就不用判断了
}

int main()
{
    ios :: sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T --) solve();
    return 0;
}
```
## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：run_away (赞：1)

## 题意

最开始有 $a$ 个金币，每次你可以选择 $y\in[1,a]$ 个金币**交给赌场**赌博，赌场决定胜负（反正不是你决定）。如果胜，就获得 $ky$ 个金币；否则获得 $0$ 个金币。赌场保证你最多连输 $x$ 次。

有 $t$ 组询问，每次给出 $k,x,a$，求是否能获得任意数量的金币。

## 分析

对于小于等于当前数量的金币数，肯定可以一次获得。

所有我们只要求是否能在 $[1,x]$ 次内使金币数增加。

设第 $i$ 次赌博投入 $c_i$ 个金币，其中 $c_0$ 肯定为 $1$。

对于已经输了 $i$ 次的一次赌博，如果本局赢且能增加数量，那么肯定满足 $\sum\limits^{i+1}_{j=0}c_j<k\times c_{i}$。

消掉一个 $c_{i}$，移项得 $\frac{\sum\limits^{i-1}_{j=0}c_j}{k-1}<c_{i}$。

所以得 $c_{i}$ 最小为 $\lfloor \frac{\sum\limits^{i-1}_{j=0}c_j}{k-1}\rfloor+1$。

其中 $\sum\limits^{i-1}_{j=0}c_j$ 可以用前缀和处理。循环 $1\sim x$，判断当前若 $sum>a$，即花销大于拥有的数了，就直接输出 `NO`。

总时间复杂度 $O(tx)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=998244353,maxn=1e2+5,maxt=505;
ll t,k,x,a,s,c[maxn]={1};
inline void solve(){
    k=read(),x=read(),a=read(),s=1;
    for(ll i=1;i<=x;++i){
        c[i]=s/(k-1)+1;
        if(s>a){puts("NO");return;}
        s+=c[i];
    }
    if(s<=a)puts("YES");
    else puts("NO");
    return;
}
signed main(){
    t=read();
    while(t--)solve();
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

感觉挺好玩的。

首先，我们假定作为 Sasha 的另一方，和他博弈。

首先需要明确一个事实，如果当前我们赔给 Sasha 之后，他就连续输 $0$ 场了，如果此时他的钱小于等于 $a$ 元，说明他没有多赚，那么显然不优。

如果我们是 Sasha，就要保证每一步走下去都可以赔回来 $a$ 元以上，中途如果没钱了自然不可行。

当 Sasha 连续输了 $x$ 次之后，那么他把所有的钱压上去，等着陪过来，判断是否超过 $a$ 元即可。

感觉比较好玩，吃了两发罚时。

```cpp
#include<bits/stdc++.h>
using namespace std;
int k, x, a, T, tmp, kk;
inline bool solve(){
	tmp = a;
	for(int i = 1; i <= x; i++){
		kk = (a + 1 - tmp + k - 2) / (k - 1);
		if(tmp <= kk) return 0;
		tmp -= kk;
	}
	if(1ll * tmp * k <= 1ll * a) return 0;
	return 1;
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &k, &x, &a);
		puts(solve() ? "YES" : "NO	");
	}
	return 0;
}
```

---

## 作者：Jerry_heng (赞：1)

（一）

每次下注，要么赚 $y\times (k-1)$，要么亏 $y$。

由于不知道什么时候会输，每次都下能赚回前面所有的金额好了。

第一次下 $1$ ，共下 $x+1$ 次。

（二）

AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,x,a;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&k,&x,&a);
		int sum=0;
		for(int i=1;i<=x+1;i++){
			sum+=sum/(k-1)+1;
			if(sum>a)break;
		}
		if(sum>a)puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

### 题目大意

你去赌场，开始有 $n$ 元，**每次赌场选择你是否获胜**。当你赌注 $y$ 元时，赢了钱会增加 $y(k-1)$ 元，输了会减少 $y$ 元。但是你不能连续输超过 $x$ 次。问你能不能获得任意数量的钱。

首先我们发现，只要你赚了钱，就可以通过刚才的操作赚到无限多的钱，最后通过输钱达到任意数目的钱。所以题目就变为了能不能赚钱。

为了使花费的钱更少，我们先考虑每次都赌 $1$ 元。但是，假设 $k=2,x=2$，赌场会先让你赢一局，再输一局，你的钱是不变的。因此，**我们每一次赌的钱需要保证若你赢了**，**赚的钱能回本**。也就是得赌 $\displaystyle\lfloor \frac{sum}{k}\rfloor+1$ 元。若你赌的所有钱超过了你的资金，则不能赚钱。

注意得循环 $x+1$ 次，因为最后一次赌需要赚回你之前输掉的钱。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,k;
signed main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n>>m>>k;
  	n--;
  	int sum=0,f=1;
    for(int i=1;i<=m+1;i++)
  	{
  	  sum+=sum/n+1;
  	  if(sum>k)
  	  {
  	  	f=0;
  	  	break;
	  }
	}
	if(f==0) cout<<"NO\n";
	else cout<<"YES\n";
  }
  return 0;
}
```

---

## 作者：L_S_ (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF1929C)

题目大意:Sasha去赌场，如果Sasha下注 $y$ 个硬币，如果他赢了，将会获得 $y\times k$ 个硬币。如果输了，硬币将会全输光。下注金额不能超过硬币数。但他最多不会连续输 $x$ 次。现在给你 $k,x,a$ ，问你能否赢得无限个金币。

我们要让每一次下注都回本，如果第一次输了就下注能让前面输的金币都赚回来并额外赚一个金币的金币。

我们第一次下注 $1$ 个金币，第 $i$ 次下注 $(a-sum)/(k-1)+1$ 个金币，其中 $sum$ 为当前的金币数量。

要注意有可能把金币输光的情况。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,k,x,a;
	cin>>t;
	while(t--)
	{
		cin>>k>>x>>a;
		int cost=1;
		int sum=a;
		for(int i=1;i<=x;i++)
		{
			sum-=cost;
			if(sum<0) break;
			cost=(a-sum)/(k-1)+1;
		}
		if(sum>=cost)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
 } 
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

递推计算 $x+1$ 次的总投入金额 $c_i$，每次判断钱是否够，不够就输出 `NO`，记 $sum_i$ 为前 $i$ 次的总和，显然我们有 $c_i = \lfloor sum_{i-1}\div (k-1) \rfloor$，
由于每个 $sum_i$ 只在当前和下一个用到，所以可以优化成变量。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,k,x,a,sum;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>k>>x>>a;
		sum=0;
		for(int i=1;i<=x+1;i++)
		{
			sum+=sum/(k-1)+1;
			if(sum>a)
			{
				cout<<"NO";
				return 0;
			}
		}
		cout<<"YES";
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

考虑贪心。

题目的目的是让你找到一个最小的下注 $b_i$，使得 $b_i \times (k-1) > \sum_{j = 1}^{i-1}b_i$。

转化一下式子：

$$
b_i \ge \lfloor \frac{\sum_{j = 1}^{i-1}b_j}{k-1} \rfloor+1
$$

题目说，最多连续输 $x$ 次，所以 $i = x+1$，而为了使 $b_{x+1}$ 最小，那么 $b_{x+1}$ 就应该取 $\lfloor \frac{\sum_{j = 1}^{i-1}b_j}{k-1} \rfloor+1$，于是我们就可以从 $1$ 到 $x+1$，计算 $b$ 的值，只要发现 $b_j > a$，就说明下注的钱比你拥有的钱多，输出 ```NO```，否则输出 ```YES```。

代码（太短了，解释上面有，不放注释了）：
```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int k,x,a,sum = 0;
		scanf("%d %d %d",&k,&x,&a);
		bool flag = 1;
		for(int i = 1;i<=x+1;i++)
		{
			sum+=sum/(k-1)+1;
			if(sum>a)
			{
				flag = 0;
				printf("NO\n");
				break;	
			} 
		}
		if(flag == 1)
		{
			printf("YES\n");
		}
	}
	return 0;
}
```

---

## 作者：Alcl000000 (赞：0)

题目大意：萨沙去赌场，赌场的运作规则如下。如果萨沙下注 $y$ 个硬币 (其中 $y$ 为正整数)，那如果赢了，他将获得 $y \times k$ 个硬币 (即他的硬币数量将增加 $y \times (k-1)$。如果输了，他的硬币数量将减少 $y$。

下注金额不能超过萨沙当前的硬币数量。另外赌场有一个促销活动：萨沙最多不会连续输超过 $x$ 次。

给你 $k,x,a$。询问萨沙能否赢无限个硬币，可以输出 `YES`，否则输出 `NO`。

思路：初始下注一个硬币，此后每次都下注**在赢的情况下会赚一个硬币的金额**，最坏情况下赌场一定会让萨沙输，因为如果让萨沙赢，萨沙就赚了一个硬币，比初始金额更多，那么就一定可以赢无限硬币。
同理，如果输 $x$ 轮后仍可以下注**在赢的情况下会赚一个硬币的金额**，就一定可以赢无限个硬币。

在赢的情况下会赚一个硬币的金额的计算方式：记第 $i$ 轮时还有 $sum$ 个硬币，则前 $i-1$ 轮共输了 $a-sum$ 个硬币，即如果第 $i$ 轮赢，需要赢 $a-sum+1$ 个硬币，故下一轮需要下注的硬币 $cost=\lceil a-sum+1\rceil$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,k,x,a;
int main(){
	cin>>t;
	while(t--){
		cin>>k>>x>>a;
		int cost=1;
		int sum=a;
		for(int i=1;i<=x;i++){
			sum-=cost;
            if(sum<0) break;
			cost=ceil((a-sum+1)*1.0/(k-1));
		}
		if(sum>=cost){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：MA_tian (赞：0)

~~所有，或者一无所有！~~
# 题目大意
最开始时有 $ a $ 个金币,每次可以赌注 $ y $ 枚，由赌场决定你能否获胜，获胜可以获得 $ n \times y $ 枚金币，失败则丢掉 $ y $ 金币，最多失败 $ x $ 次后就必定获胜。询问能不能无限赢钱。

有 $ T $ 组数据,每组数据按顺序输入 $ k,x,a $。
# 做法
题目的意思就是让你去寻找一种方案，输了 $ t $ 局后（$0 \le t \le x$）获胜可以一次回本。找到之后，一直按照这种方式下注即可。若找不到，则证明不能一直赢钱。

那么，我们该如何寻找方案呢？

通过观察，我们可以发现，想要实现这个方案的最坏情况是已经下注了 $ x $ 次还没有获胜，那么我们需要下注第 $ x+1 $ 次才能获胜。基于只要获胜就能回本的方案下，我们唯一需要考虑的问题就是财力能否支撑最坏情况下的花费。判断财力够不够的标准就是你的钱是否大于最坏情况下的花费。那么，我们就明确了一件事，那就是我们需要计算每次赌注的花费，并将其相加。如果花费大于你目前的钱就不行，小于或等于就可以。

重头戏来了，如何计算花费呢？

其实很简单，为了保证能够回本，本次赌注的花费就是 $ \lfloor \dfrac{sum}{k} \rfloor + 1 $ 元。按照刚刚的思路，计算每次的花费，判断是否大于目前的钱即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long sum=0,a[105];//sum是每次的花费
	int flag=0,T;
	cin>>T;
	while(T--){
		long long k,x,use;
		cin>>k>>x>>use;
		a[1]=1,sum=0;
		flag=1;
		for(int i=1;i<=x;i++){
			sum+=a[i];
			a[i+1]=sum/(k-1)+1;
			if(sum>use){
				flag=0;
				break;
			}
		}
		sum+=a[x+1];
		if(sum<=use&&flag){
			cout<<"Yes"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```
感谢您的观看，我们下次剧目再见。

---

## 作者：Tasty_Cockroach (赞：0)

### **题目大意：**

你有 $a$ 元本金，每次可以赌博下注 $y$ 元，若赌赢就可以拿到 $k$ 倍的奖金，也就是会有 $(k-1)\times y$ 元的利息；若赌输则没有任何回报。你可能会输，但是最多连续输 $x$ 次。问你是否可以获得无限钱。

### **思路：**

根据题意，
注意到题目中提到不会连续输超过 $x$ 次，也就是下注 $x+1$ 次，必定有一次是胜利的。而只要保证这次胜利时赢回的钱比下注用的钱多就可以了。用递推可以算出第 $i$ 次下注最少需要 $ans_i=\lfloor \frac {\sum \limits _ {j=1}^{i-1} ans_j}{k-1}\rfloor +1$ 元。如果 $\sum \limits _ {x+1}^{i=1} ans_i > a$，即本金不够下注 $x+1$ 次，那么肯定不能够满足题目要求，输出 NO，反之输出 YES。

# 码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int k,x,a,T;
LL ans,p;
bool flag;
int main() {
	cin>>T;
    while(T--) {
    	cin>>k>>x>>a;
	    ans=0;
		p=1;
		flag=0;
	    for(int i=1;i<=x+1;i++) {
	        ans+=p;
	        if(ans>a) {
				cout<<"NO"<<endl;
				flag=1;
				break;
			}
	        p=ans/(k-1)+1;
	    }
	    if(flag) {
	    	continue;
		}
	    if(ans<=a) {
	    	cout<<"YES"<<endl;
		}
	    else {
	    	cout<<"NO"<<endl;
		}
	}
    return 0;
}//有防抄袭/cf/cf/cf
```

---

## 作者：Link_Cut_Y (赞：0)

非常好题目，使我不开 long long。

想让他在任何情况下赢，一个很简单的原则是，只要能撑过 $x$ 局失败，眼前就是一片光明，因为这一局就必赢。他需要做的就是把所有钱都押上。

怎么才能保证他撑过 $x$ 局失败呢？不妨设 $a_i$ 为他第 $i$ 局赌的钱数，$S_i$ 表示前 $i$ 局赌的钱数之和。

如果第 $i$ 局输了，他会损失 $a_i$ 元。这无伤大雅。但是一旦第 $i$ 局赢了，他可以赢得 $a_i \times k$ 元，而前面一共花费了 $S_i$ 元。假如 $a_i \times k \le S_i$，也就是说没有把前面输的钱赢回来，那么我就可以继续用这个死循环直到把你的钱卡没有（或者让你的钱数不变）。

因此要保证 $a_i \times k > S_i$，也就是 $a_i \times (k - 1) > S_{i - 1}$。让 $a_i > \dfrac{S_{i - 1}}{k - 1}$ 即可。

这样我们可以计算出前 $x$ 局的最小花费。最后一局必胜，把所有钱放进去就可以了。最后需要判断一下，最后一句赢的钱是否大于前面输的钱。

复杂度 $O(n)$。记得开 long long，记得在计算 $S$ 时，如果 $S_i$ 比持有的钱数多直接退出，否则会爆 long long。



---

## 作者：Drind (赞：0)

太好玩儿了这个题。

### 题目解析

赌场，每次获胜下注金额翻 $k$ 倍，初始有 $a$ 个筹码，并且连续的 $x+1$ 次下注中必有一次获胜。问有无无限赚钱的策略。

显然这种游戏我们可以用倍投法秒掉，但是注意到不是翻两倍，所以我们下注不需要每次都翻倍，只要保证能把前面亏的钱全部赚回来就行，而且还有保底，所以这个策略是绝对可行的。

判断手上的钱能不能倍投撑过 $x$ 轮即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

inline void fake_main(){
	int k,x,a; cin>>k>>x>>a;
	int cnt=0;//记录前面花了多少钱。
	for(int i=1;i<=x+1;i++){
		int tmp=(cnt+k-1)/(k-1);//这次要下注多少才能赚回本，本质上就是赚 k-1 倍所以除以 k-1 向上取整，注意不能不赚钱。
		if(i==1) tmp=1;
		cnt+=tmp;
		if(cnt>a){//因为算完会爆 long long 所以尽早输出。
			cout<<"NO\n";
			return;
		}
	}
	if(cnt<=a) cout<<"YES\n";
	else cout<<"NO\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

