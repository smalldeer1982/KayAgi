# XOR Break — Game Version

## 题目描述

This is an interactive problem.

This is the game version of the problem. Note that the solution of this problem may or may not share ideas with the solution of the solo version. You can solve and get points for both versions independently.

Alice and Bob are playing a game. The game starts with a positive integer $ n $ , with players taking turns. On each turn of the game, the following sequence of events takes place:

- The player having the integer $ p $ breaks it into two integers $ p_{1} $ and $ p_{2} $ , where $ 0 \lt p_{1} \lt p $ , $ 0 \lt p_{2} \lt p $ and $ p_{1} \oplus p_{2} = p $ .
- If no such $ p_{1} $ , $ p_{2} $ exist, the player loses.
- Otherwise, the opponent does either select the integer $ p_{1} $ or $ p_{2} $ .
- The game continues with the selected integer. The opponent will try to break it.

As Alice, your goal is to win. You can execute a maximum of $ 63 $ break operations. You have the choice to play first or second. The system will act for Bob.

Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 说明/提示

Explanation for the interaction.

Interactor / BobAliceExplanation4 $ t $ 1 $ n $ for the first test casesecondAlice chooses to go second0 0Bob says he cannot break $ p = 1 $ 3 $ n $ for the second test casefirstAlice chooses to go first1 2Alice breaks $ p = 3 $ into $ p_1 = 1 $ and $ p_2 = 2 $ 0 0Bob says he cannot break $ p = 1 $ or $ p = 2 $ 13 $ n $ for the third test casefirstAlice chooses to go first10 7Alice breaks $ p = 13 $ into $ p_1 = 10 $ and $ p_2 = 7 $ 3 4Bob breaks $ p = 7 $ into $ p_1 = 3 $ and $ p_2 = 4 $ 1 2Alice breaks $ p = 3 $ into $ p_1 = 1 $ and $ p_2 = 2 $ 0 0Bob says he cannot break $ p = 1 $ or $ p = 2 $ 777777770001 $ n $ for the fourth test casefirstAlice chooses to go first777777770000 1Alice breaks $ p = 777\,777\,770\,001 $ into $ p_1 = 777\,777\,770\,000 $ and $ p_2 = 1 $ 0 0Bob says he cannot perform break operation.This table is for explanation only and does not reflect the actual behavior of the interactor.

Note that in the last test case Bob could choose $ p_1 $ and perform a break operation but he gave up.

## 样例 #1

### 输入

```
4
1

0 0
3


0 0
13


3 4

0 0
777777770001


0 0```

### 输出

```
second


first
2 1


first
10 7

1 2


first
777777770000 1```

# 题解

## 作者：sunkuangzheng (赞：2)

$\textbf{CF1934D2 *2400}$

> - 有一个整数 $n$，你和交互库轮流进行拆分。一次拆分指的是一方选择两个整数 $p_1,p_2$ 满足 $0 < p_1,p_2 < n,p_1 \oplus p_2 = n$，对方从 $p_1,p_2$ 中选择一个替换掉 $n$，然后对方继续拆分。当一方无法拆分时视为失败。
> - 你可以选择先手或者后手和交互库博弈。
> - $1 \le n \le 10^{18}$。

记 $f(x) = \operatorname{popcount}(x)$，容易发现 $f(x) = 1$ 时无法拆分，先手必败；$f(x)=2$ 时可以拆分使得 $f(p_1)=f(p_2)=1$，先手必胜。

猜测结论：$f(x) \bmod 2 = 1$ 时先手败，否则先手胜。

> - $f(x)$ 是奇数时拆出的 $f(p_1),f(p_2)$ 一定一奇一偶，后手可以选择那个偶数，后手必胜。
> - $f(x)$ 是偶数时拆出的 $f(p_1),f(p_2)$ 的奇偶性相同，先手可以拆成两个奇数，后手必败。

然后模拟上述过程构造方案即可。注意到我们只会进行拆分偶数操作，我们每次可以直接拆成 $\operatorname{hb}(n)$ 和 $n \oplus \operatorname{hb}(n)$，其中 $\operatorname{hb}(n)$ 指的是 $n$ 的最高二进制位值。这样拆分一次一定会少一位，操作次数是严格 $\mathcal O(\log n)$ 的。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 02.03.2024 12:24:54
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T; ll n,p1,p2;
void los(){
    cin >> n;
    auto ck = [&](ll x){return __builtin_popcountll(x) & 1;};
    auto lb = [&](ll x){return 1ll << (63 - __builtin_clzll(x));};
    cout << (ck(n) ? "Second" : "First") << endl;
    if(!ck(n)) cout << lb(n) << " " << (n ^ lb(n)) << endl;
    while(1){
        cin >> p1 >> p2; if(p1 == -1) assert(0);
        if(!p1 && !p2) return ;
        if(ck(p1)) cout << lb(p2) << " " << (p2 ^ lb(p2)) << endl;
        else cout << lb(p1) << " " << (p1 ^ lb(p1)) << endl;
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```
~~请注意，拆成 $\operatorname{lowbit}$ 可能会导致操作次数达到 $\mathcal O(\log^2 n)$ 级别，不满足限制。~~

--- 

**UPD**：拆成 $\operatorname{lowbit}$ 的操作次数可以达到 $\mathcal O(n)$ 级别。具体的，对于 $m$ 位的二进制数把后 $2$ 位分离，每次后手给前 $m -2$ 位做 $-1$ 操作，并用后两位平衡 $1$ 的数量奇偶性。先手每次只能拆最后两位，无法影响前面 $m-2$ 位，操作数量是 $\mathcal O(n)$ 级别的。感谢 @qweradf 指出 /bx /bx

---

## 作者：Engulf (赞：0)

建议先解决 Solo Version，对此题有些许帮助。

记 $\textrm{popcount}(x)$ 为 $x$ 在二进制表示下 $1$ 的个数。

> 性质 1：若 $p_1, p_2$ 均为 $2$ 的整数次幂，则当前操作者必败无疑。

Solo Version 中已经证过。

为了赢，应该尽量地把 $p$ 拆分成两个 $2$ 的整数次幂，这样 Bob 就无法操作而输掉。

> 性质 2：若 $\textrm{popcount}(p)$ 是奇数，那么任意的 $0 < p_1, p_2 < p$ 且 $p_1 \oplus p_2 = p$ 的 $(p_1, p_2)$，都满足 $\textrm{popcount}(p_1)$ 和 $\textrm{popcount}(p_2)$ 一个是奇数，一个是偶数。

证明这个很容易，
- 若 $\textrm{popcount}(p_1), \textrm{popcount}(p_2)$ 均为偶数，$\textrm{popcount}(p_1 \oplus p_2)$ 也是偶数，因为只可能成对减少 $1$。
- 若 $\textrm{popcount}(p_1), \textrm{popcount}(p_2)$ 均为奇数，$\textrm{popcount}(p_1 \oplus p_2)$ 也是偶数，若没有同位是 $1$，那么和是偶数，否则 $1$ 是成对减少，和仍是偶数。

> 性质 3：若 $\textrm{popcount}(p_1), \textrm{popcount}(p_2)$ 有一个是偶数，当前操作者有必胜策略。

不妨就设 $\textrm{popcount}(p_1)$ 是偶数，策略是这样的，记 $\textrm{msb}(x)$ 是 $x$ 的最高有效位。
- 将 $p_1$ 拆分为 $2^{\textrm{msb}(p_1)}$ 和 $2^{\textrm{msb}(p_1)} \oplus p_1$。
- 由性质 1 可得，对手只能选择 $2^{\textrm{msb}(p_1)} \oplus p_1$。
- $2^{\textrm{msb}(p_1)} \oplus p_1$ 就是 $p_1$ 去掉了它的最高有效位，所以 $\textrm{popcount}(2^{\textrm{msb}(p_1)} \oplus p_1)$ 是奇数。
- 对手拆分这个数。由性质 2 可得，$2^{\textrm{msb}(p_1)} \oplus p_1$ 一定能被拆分成 $\textrm{popcount}$ 一奇一偶的两个数。
- 继续选择 $\textrm{popcount}$ 是偶数的那个，重复上述的步骤。

这样，每次都去掉当前 $p$ 的最高有效位，所以上述策略能在 $60$ 步之内赢下游戏。

最后是先后手的问题。
- 若 $\textrm{popcount}(n)$ 是偶数，选择先手，按照上述策略赢下游戏。
- 若 $\textrm{popcount}(n)$ 是奇数，选择后手，让对手操作一次，由性质 2，现在有 $\textrm{popcount}$ 是偶数的数了，选择它，按照上述策略赢下游戏。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        ll n;
        cin >> n;

        auto getmsb = [](ll x) {for (int i = 59; ~i; i--) if (x >> i & 1) return i;};
        auto popcount = [](ll x) {int res = 0; for (int i = 59; ~i; i--) if (x >> i & 1) res++; return res;};

        if (~popcount(n) & 1) {
            cout << "first" << endl;

            ll p1 = 1ll << getmsb(n), p2 = n ^ p1;

            cout << p1 << " " << p2 << endl;

            do {
                cin >> p1 >> p2;
                if (!p1 && !p2) break;
                ll p = popcount(p1) & 1 ? p2 : p1;
                ll p1 = 1ll << getmsb(p), p2 = p ^ p1;
                cout << p1 << " " << p2 << endl;
            } while (p1 && p2);

        } else {
            cout << "second" << endl;

            ll p1 = 1, p2 = 1;
            do {
                cin >> p1 >> p2;
                if (!p1 && !p2) break;
                ll p = popcount(p1) & 1 ? p2 : p1;
                ll p1 = 1ll << getmsb(p), p2 = p ^ p1;
                cout << p1 << " " << p2 << endl;
            } while (p1 && p2);
        }
    }
    return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：0)

（说句闲话：这洛谷题面一看就是机翻的，可读性感人）

**题意**

玩这样的游戏：

- 给定数 $N$。先手将 $N$ 分为 $p_1,p_2 \in (0,N)$ 使得 $p1 \oplus p2=N$。后手将 $p1,p2$ 中的一者变为新一轮的 $N$ 并分解。之后先手再进行....直到无法分解为止。

你要选择当先手或后手，并赢得该游戏，并保证交互次数不超过 $\log N$。

**分析**

首先考虑何时该游戏结束。~~暴力检验一千以内的数~~，发现当 $P$ 为 $2$ 的次幂时不能被分解。这点容易证明：此时数 $P$ 的二进制表示中只包含一个 $1$，且在最高位。那 $p1,p2$ 中包含这个 $1$ 的数必然 $\ge P$，不符合要求。

进一步考虑：若 $P$ 二进制下有 $2$ 个 $1$，则玩家可以将其分为两个不同的数，分别占有原来 $P$ 的一个 $1$。这样对后手而言，两个 $p$ 都不可分解。因此有两个 $1$ 时，是先手必胜的。

当 $P$ 的 $1$ 位数更多时就有些难分析了，有许多分解策略。但可以确定的是：

- $P$ 有奇数个 $1$ 时，$p1,p2$ 有一者为奇数 $1$，一者为偶数 $1$；

- $P$ 有偶数个 $1$ 时，$p1,p2$ 全为奇数 $1$ 或全为偶数 $1$。

原因：对于 $P$ 的每个 $1$，要么交给 $p1$，要么给 $p2$；对于每个 $0$，则 $p1,p2$ 的相应位要么全为 $1$，要么都不是。

考虑先手时 $P$ 有偶数个 $1$。那他可以将它分为两个有奇数 $1$ 的。此时后手必须选择一个奇数 $1$，从而分解出一个偶数 $1$ 给到先手。如果先手最终获得了有 $2$ 个 $1$ 的数，那他就赢了。

因此可以得到：若 $N$ 有偶数个 $1$，先手胜利；否则后手胜利。

从而可以得到你的策略。

- 若 $N$ 有偶数个 $1$，成为先手；

- 否则成为后手，并选取 $p1,p2$ 中有偶数个 $1$ 的那个。

而在你分解 $P$ 时，你应将其分解为：

- 最高位的 $1$ 后面全是 $0$ 的数

- 剩余 $1$ 组成的数

这两个数异或起来刚好是 $P$，且两个都有奇数个 $1$，且后手必然选择第二项，数的位数会 $-1$。因此可以保证在 $\log$ 的次数内完成任务。

> 评价：本题的重点是由结束情况想到从数字和的方面解决问题，想到从奇偶性的方面解决是很重要的。之后贪心的游戏策略就相对简单了。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int T;
LL N;
int PopCount(LL x)
{
    int res=0;
    while(x)
    {
        res+=x&1;
        x>>=1;
    }
    return res;
}
LL Highbit(LL x)
{
    LL t=1ll<<62;
    for(;t;t>>=1)
    {
        if(t&x) return t;
    }
    return 0;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&N);
        if(PopCount(N)&1)
        {
            puts("second");
            fflush(stdout);
        }
        else
        {
            puts("first");
            fflush(stdout);
            printf("%lld %lld\n",Highbit(N),N^Highbit(N));
            fflush(stdout);
        }
        while(1)
        {
            LL p1,p2;
            scanf("%lld %lld",&p1,&p2);
            if(p1==0||p2==0) break;
            int c1=PopCount(p1),c2=PopCount(p2);
            if(c1&1) swap(p1,p2);
            printf("%lld %lld\n",Highbit(p1),p1^Highbit(p1));
            fflush(stdout);
        }
    }
}
```

---

