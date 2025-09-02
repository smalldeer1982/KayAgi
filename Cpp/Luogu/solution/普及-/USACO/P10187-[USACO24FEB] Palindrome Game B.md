# [USACO24FEB] Palindrome Game B

## 题目描述

Bessie 和 Elsie 正在使用一堆初始时共 $S$ 个石子（$1\le S<10^{10^5}$）进行一个游戏。两头奶牛依次行动，Bessie 先行动。当轮到一头奶牛行动时，她必须从堆中取走 $x$ 个石子，其中 $x$ 是该奶牛选定的任意正整数回文数。如果当一头奶牛的回合开始时石子堆是空的，那么这头奶牛就输了。

**定义**：一个正整数如果从前向后和从后向前读相同，则该数为回文数；回文数的例子有 $1$，$121$ 和 $9009$。数不允许有前导零；例如，$990$ **不是**回文数。

有 $T$（$1\le T\le 10$）个独立的测试用例。对于每一个测试用例，输出如果两头奶牛都采取最优策略，谁会赢得游戏。 

## 说明/提示

### 样例解释

对于第一个测试用例，Bessie 可以在第一次行动中取走所有石子，因为 $8$ 是回文数，使她获胜。

对于第二个测试用例，$10$ 不是回文数，因此 Bessie 无法在第一次行动中取走所有石子。无论 Bessie 第一回合取走多少石子，Elsie 总能在第二回合取走所有余下的石子，使她获胜。

对于第三个测试用例，可以证明在最优策略下 Bessie 可以获胜。 

### 测试点性质

- 测试点 $2-4$：$S<100$。
- 测试点 $5-7$：$S<10^6$。
- 测试点 $8-10$：$S<10^9$。
- 测试点 $11-13$：没有额外限制。

## 样例 #1

### 输入

```
3
8
10
12```

### 输出

```
B
E
B```

# 题解

## 作者：cff_0102 (赞：17)

不难发现所有整除 $10$，即以 $0$ 结尾的正整数都不是回文数。

因为 $1,2,3,4,5,6,7,8,9$ 都是回文数，而 $10$ 不是，所以当 $n\le9$ 时先手必胜，而 $n=10$ 时先手必输。

假设 $x$ 整除 $10$，且已知对于所有的 $n\le x$，当 $n$ 整除 $10$ 时先手输，否则先手赢。显然，$x=10$ 时满足条件。接下来证明：对于任意的 $x$，当 $x$ 满足条件时，$x+10$ 也满足条件。

- 当 $x<n<x+10$ 时，因为 $1,2,3,4,5,6,7,8,9$ 都是回文数，所以先手可以取走任意的在 $1$ 到 $9$ 之间的数量的石子。此时先手必能一次将 $n$ 变为 $x$。而根据假设，$x$ 整除 $10$，是必输局面。所以当 $x<n<x+10$ 时，先手可以取一次将局面变成必输局面，接下来后手怎么取都会输，所以先手赢。
- 当 $n=x+10$ 时，因为根据假设，所有小于 $n$ 的不整除 $10$ 的数是必胜的，那么先手要是取完之后剩下的 $n$ 不整除 $10$，后手就会有必胜策略，先手就输了。然而，因为所有整除 $10$ 的正整数都不是回文数，所以先手不可能取走一个整除 $10$ 的数，从而剩下的局面就必然不整除 $10$。因此，此时先手是必输的。

现在就成功证明了“若 $x$ 整除 $10$，且对于所有的 $n\le x$，当 $n$ 整除 $10$ 时先手输，否则先手赢，那么此时对于所有的 $n\le x+10$，当 $n$ 整除 $10$ 时先手输，否则先手赢”。而我们又知道 $x=10$ 时满足条件，所以所有的 $x$ 都满足条件，所以只要 $n$ 整除 $10$ 就先手输，否则先手赢。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;while(t--){
		string s;cin>>s;
		if(s.back()=='0')cout<<"E\n";
		else cout<<"B\n";
	} 
	return 0;
}
```

---

## 作者：Harrylzh (赞：9)

这道题的突破口在于末尾是 $0$ 的数一定不是回文数。如果我每次留给对方末尾为 $0$ 的数，要么我赢了（剩余 $0$ 个）要么对方下一步一定赢不了。这样看似一定是先手赢，但如果最开始末尾就是 $0$，留给后手的一定末尾不为 $0$，就变成了上一个情况，后手必胜。代码实现很简单，但要注意数据范围，用字符串读入。

---

## 作者：xd244 (赞：6)

题目描述：两个人每次可以在一堆石子里面取走 $x$ 个，其中 $x$ 是回文数。请问谁会去到最后一颗石子。

显然，在做题之前，我们要先**分类讨论**：（设总共有 $n$ 颗石子）

当 $1\leq n\leq9$ 时，显然个位数都是回文数，所以 Bessie 一定可以一次拿光。所以 Bessie 获胜。

当 $11\leq n\leq19$ 时，Bessie 先拿 $n\text{ mod }10$颗石子，剩下 10 颗。剩 10 颗时，因为 10 不是回文数，所以 Elsie 不可能一次拿光。所以 Bessie 还是会获胜。

两个例子让我们有了猜想：当 $n≡0(\text{mod }10)$ 时，Elsie 获胜（因为 Bessie 不能一次拿光），否则 Bessie 获胜。

证明也很简单：

当 $n≡0(\text{mod }10)$ 不成立时，Bessie 先拿 $n\text{ mod }10$ 颗石子，此后不管 Elsie 拿多少，都将 $n$ 拿成 $n≡0(\text{mod }10)$ 的样子，所以最后一定是 Bessie 获胜。反之，如果 $n$ 一开始就满足 $n≡0(\text{mod }10)$，则相当于上一种情况去掉第一步，所以 Elsie 获胜。

所以 std 也很好写了：
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;cin>>t;
    for(int c=1;c<=t;c++){
        long n;cin>>n;
        if(n%10==0)cout<<"E\n";
        else cout<<"B\n";
    }
}
```
但是......
![](https://cdn.luogu.com.cn/upload/image_hosting/7n4gthtj.png)

于是又一次读题：$1\leq s\leq10^{10^5}$，所以 long long 已经存不下了！

于是改成了 string 类型：
```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    int t;cin>>t;
    for(int c=1;c<=t;c++){
        string n;cin>>n;
        if(n[n.length()-1]=='0')cout<<"E\n";
        else cout<<"B\n";
    }
}
```

---

## 作者：卷王 (赞：6)

这是一道猜结论的题，证明有点复杂，但手玩几组数据其实就可以发现规律。

我们来看看 $n$ 的一些情况：

* $n<10$，$n$ 肯定是回文数，Bessie 可以一次性取完，Elsie 就没有可取的。输出 `B`。

* $10<n<20$，$n$ 可以先被 Bessie 变成 $10$，然后再被（也只能被）Elsie 变成一个一位数，那就是第一种情况。输出 `B`。
* $\dots$

再看看 $n$ 是一个整十数的情况：

* $n=10$，在上面的第二种情况已经讨论过了。输出 `E`。

* $n=20$，Bessie 可以把 $n$ 变成一个 $11$ 到 $19$ 的数，情况又成为了上面的第二种。输出 `E`。

* $\dots$

那么我们可以发现 **当 $n$ 为整十数的时候** 永远是 Elsie 赢，否则则永远是 Bessie 赢。

考场代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(l, r, i) for(int i = (l); i <= (r); i++)
#define down(r, l, i) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int a[1000007];
char s[1000007];
bool flag = 0;

signed main() {
	T = read();
	while(T--) {
		cin >> (s + 1);
		if(s[strlen(s + 1)] == '0') cout << "E\n";
		else cout << "B\n";
	}
	return 0;
}
```

---

## 作者：MicroSun (赞：4)

博弈论结论题。

## 题目大意

- B 和 E 在玩一个游戏，B 是先手。

- 读入一个数 $x$，满足 $x\le 10^{10^6}$。在接下来的游戏中，每名玩家需要令 $x\gets x-k$，在这里，$k$ 为大于零的回文数。

- 如果在某名玩家的回合结束后，$x=0$，该玩家即为胜者。

- 如 B 和 E 都以最优策略进行游戏，请判断谁为最后的赢家。

## 思路

本题与[巴什博弈](https://baike.baidu.com/item/%E5%B7%B4%E4%BB%80%E5%8D%9A%E5%BC%88/1819345)较为类似，建议初步了解巴什博弈后再观看本题解。

考虑巴什游戏的解题思路：找出当前玩家的必胜局面（下文记为 N-pos）和上次操作玩家的必胜局面（下文记为 P-pos）。

易发现 P-pos 在一次操作后必定为 N-pos，而 N-pos 在一次最优操作后必定为 P-pos。所以，我们需要找出一种数，使得其在进行了一次操作之后，一定不为该种数。同时，一个不为该种数的数，一定可以转换为该种数。

可以发现，结尾为 $0$ 的数符合该性质。即，如果一个数结尾为 $0$，则 $x$ 为该数的局面一定为 P-pos，反之则为 N-pos。

以下为简单的证明：

- 因为没有结尾为 $0$ 的回文数，所以在进行了一次操作后结尾必定不为 $0$。

- 当结尾不为 $0$ 时，可以选一个结尾与该数相同的回文数（易证这个数一定存在）进行操作，将结尾变为 $0$。

- 最终，$x$ 会变为 $0$。

代码实现非常简单，只需判断结尾是否为 $0$ 即可。

非常简短的 code：
```cpp
#include<bits/stdc++.h>
int main(){
	int t;std::string s;
	std::cin>>t;
	while(t--){
		std::cin>>s;
		std::cout<<(s.back()=='0'?"E\n":"B\n");
	}
}
```

---

## 作者：carbon_monoxide (赞：4)

经典的博弈论~~水~~题。

先上结论：当 n 个位为 0 时，`Elsie` 胜；反之，`Bessie` 胜。

证明：如果 n 个位等于 0，`Bessie` 任意减一个回文数后个位一定不等于 0，此时 `Elsie` 减去一个一位数（也是回文数），使 n 的个位保持为 0。当 `Bessie` 在某一次给 n 减去一个数后 n 小于 10，`Elsie` 减去 n 即可获胜；

如果 n 个位不为 0，只要 `Bessie` 先把 n 的个位减成 0，之后采用上面的方法，`Bessie` 必胜。

总的来说，证明过程还是较为简单的吧。

代码就不放了，注意不开 string 见祖宗（$n<10^{10^5}$）。

---

## 作者：_QWQ_TAT_ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P10187)




## 题目思路
  一眼博弈论，可以用枚举解决问题：

- $ n \le 10$可以取这个数的石子使得对手无石子可拿，`Bessie` 获胜。
- $ n = 10$ 先手无论取任意合法个数的石子都会转为上面一种情况，`Elsie`获胜。
- $ 10 \le n \le 20$ 可以将剩余石子变为上面一种情况，`Bessie`获胜。
- $ n = 20$  先手无论取任意合法个数的石子都会转为上面一种情况，`Elsie`获胜。
- 剩余同理。

所以结论是：当$ n\equiv0 \pmod {10}$时`Elsie` 获胜，其余`Bessie`获胜。

因为它的数据太大，只能用字符串去存，所以这样子就做出来啦。

## 代码大放送
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
typedef long long ll ;

int t;
string s; 

signed main(){
	cin>>t;
	for (int i=1;i<=t;i++){
		cin>>s;
		int l=s.size();
		if (s[l-1]=='0') puts("E");//结论
		else puts("B");//结论
	}
	return 0;//华丽的结尾
}
```

---

## 作者：dinghongsen (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/P10187)

### 解题思路

简单的博弈论。

列举一下回文数可以发现从 1 到 9 都是回文数，并且所有整十的数都不是回文数，因此只要剩下整十的石子数量，就不能一次性取完，且还剩下的石子数量不为整十，所以对方便可以取完剩下数量的个位的数量，再留下整十的石子。

总结一下，只要石子的数量是整十的数，那么后手赢。反之，先手赢。

### code
```cpp
# include <bits/stdc++.h>
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		string s;
		cin >> s;
		(s[s.size() - 1] == '0') ? puts("E") : puts("B");
	}
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：3)

## 题意

两个人进行一个博弈游戏，初始时有 $S$ 个石子，两个人依次轮流取石子，每个人取的石子数量必须为回文数。当轮到其中一个人时剩余石子数量为 $0$，那么这个人就输了。

若双方都选择最优策略，求先手还是后手会赢。

多组询问，每组询问保证 $1\le S\le 10^{10^5}$。

## 思路

考虑从最简单的情况开始模拟。

当 $1\le S\le 9$ 时，显然先手赢，因为他可以取走所有的石子（此时 $S$ 是回文数）。

当 $S=10$ 时，应该是后手赢，因为先手无论怎么走，都肯定取不完所有石子，而轮到对方时的石子数量 $S'$ 就变成了 $1\le S'\le 9$，根据上面的推论显然后手会直接赢。

当 $11\le S\le 19$ 时，先手赢，因为考虑到轮到谁有 $10$ 个石子谁就会输，所有此时先手可以取 $S-10$ 个石子（此时 $S-10$ 是回文数），此时把 $10$ 个石子的情况留给对方，则先手赢。

当 $S=20$ 时，同样后手赢，因为无论怎么走，先手都无法把输的情况留给对方（根据前面的推论只有当对方的石子是 $10$ 的时候先手才能赢，而 $20-10$ 并非回文数）所以此时自然后手赢。

仿照这个规律下去，我们可以得出一个结论：

**当 $S=10k$ 的时候，后手赢，否则先手赢，其中 $k$ 为正整数。**

这个结论也可以从策略上很好的证明，因为若当前的石子数量是 $10k$，则他无法把数变成 $10k'$ 的形式，则若他取了 $x$ 个，对方只需要取 $10-x\bmod 10$ 个，他此时的石子数量还会是：

$10k-x-(10-x\bmod 10)=10(k-1-\left\lfloor\dfrac{x}{10}\right\rfloor)$

注意到还是 $10k$ 的形式。这种情况将一直持续到 $S=0$ 则他必然输。

代码很简单，就不放了。

---

## 作者：2021zjhs005 (赞：3)

[洛谷题目传送门](https://www.luogu.com.cn/problem/P10187)

Despriction
------------

给定 $T$ 个整数 $x$（$1\le x\le 10^{10^5}$），每次可以让 $x$ 变为 $x-y$，其中 $y$ 必须是回文数（$1\le y\le n$）。谁先让 $x$ 变为 $0$，谁就获胜。

`Bessie` 和 `Elsie` 轮流操作，`Bessie` 先。已知两头牛都是职业选手，问对于每个 $x$，谁获胜（`Bessie` 胜输出一行 `B`，否则输出一行 `E`）？

Solution
------------
一看就是博弈论入门题，可以尝试枚举：

- $n<10$，`Bessie` 胜，因为一位数都是回文数。

- $n=10$，`Elsie` 胜，`Bessie` 怎么操作也只能将 $x$ 变为一位数，这是 `Elsie` 获胜。

- $11\leq n < 20$，`Bessie` 胜，它可以让 $x$ 操作后变为 $10$。

- $n=20$，`Elsie` 胜，它可以让 $x$ 变为 $11\sim 19$ 的一个数。

- $\cdots\cdots$

也就是说，答案分两类，上面的 `Bessie` 败，否则 `Elsie` 败：

$$\begin{cases}n\bmod 10 = 0 &E\ \ win\\n\bmod 10\ne 0&B\  \ win\end{cases}$$

尝试证明这一点：

- $n\bmod 10=0$，`Bessie` 怎么减 $y$ 都是输。因为大于等于 $1$ 的回文数的个位都不是 $0$（不然首位变成 $0$ 了），那么减去 $y$ 之后会变为 $\overline{abcd\cdots lmn}$（这个数的位数不一定），这个数一定不是 $10$ 的倍数。这样，后手可以让这个数减去 $n$，得到 $\overline{abcd\cdots lm0}$，让这个数再次变为 $10$ 的倍数。由于 $0\bmod 10 = 0$，所以后者必胜。

- $n\bmod 10\ne 0$，`Bessie` 获胜。由于上面已经证明 $n\bmod 10=0$ 是 `Bessie` 败，所以 `Bessie` 可以让这个数（设其为 $\overline{abcd\cdots lmn}$）减去 $n$，变为 $\overline{abcd\cdots lm0}$，这样就变成了此轮的先者必败，也就是 `Elsie` 必败。按照上面的策略玩下去，这种情况一定是 `Bessie` 获胜。

因此只要判断 $x$ 是不是 $10$ 的倍数，然后分情况讨论即可。

但是由于 $1\le x\le 10^{10^5}$，所以需要用字符串或者字符数组来存储 $x$，判断是否是 $10$ 的倍数就看末尾一位是否为 $0$ 即可。

[Code](https://www.luogu.com.cn/paste/whg693lt)。

---

## 作者：_O_v_O_ (赞：2)

前置知识：[巴什博弈](https://baike.baidu.com/item/%E5%B7%B4%E4%BB%80%E5%8D%9A%E5%BC%88/1819345?fr=ge_ala)。

首先，我们意识到 $1\sim 9$ 都是回文数，如果只取 $1\sim 9$ 那这就是一道标准的巴什博弈。

其次我们意识到所有回文数 $\bmod\ 10$ 后只能为 $1\sim 9$，所以假设先手选了 $x$，那么后手取 $10-x\bmod 10$ 仍然能满足巴什博弈的必胜条件。

所以当 $S\bmod 10=0$ 时，输出 $\texttt{E}$，否则输出 $\texttt{B}$。

---

## 作者：yuyc (赞：2)

## 题意
有 $S$ 个石子，二人轮流取石子，每次可以取 $x$ 个石子，$x$ 为正整回文数，没有石子可取的一方失败，问如果两人均按照最优策略操作，最终的获胜者。

## 解析
这个问题让人很容易联想到巴什博弈，即一堆总数为 $S$ 的石子，二人轮流取石子，每次至少取 $1$ 个石子，**最多**可以取 $x$ 个石子，没有石子可取的一方失败。

巴什博弈的结论是：如果 $S$ 是 $x + 1$ 的倍数，则后手方必胜，否则先手方必胜。

不妨考虑这样一种情况：现在还剩下 $x + 1$ 个石子，那么无论取多少石子，对方都可以在下一轮里取完所有石子。

所以我们可以得到一个结论：需要在 $x+1$ 个石子里取石子的一方必败，或者说，取完石子后使得石子总数变为 $x+1$ 的一方必胜。

有了这个结论，我们就可以开始分类讨论：

如果开始时 $S$ 是 $x + 1$ 的倍数，那么先手方取完石子后，剩余的石子总数 $S$ 必定不是 $x + 1$ 的倍数，因为先手方至多取 $x$ 个石子。而后手方必定可以在取完石子后，使得 $S$ 重新变为 $x + 1$ 的倍数，如此一直取下去，必定存在某个后手方取完石子的时刻，石子总数为 $x+1$，故后手方必胜。

如果开始时 $S$ 不是 $x + 1$ 的倍数，这就意味着先手方可以保证在自己取完石子后，石子的总数是 $x+1$ 的倍数，故先手方必胜。

回到这个问题，发现取石子的数目限制由不超过某个数变成了必须是回文数，由于题目不允许前导 $0$ 的存在，故可以发现取石子的数目必不能是 $10$ 的倍数。 

故总有一方可以在取完石子后使得石子总数变为 $10$ 的倍数，因为 $1$ 到 $9$ 均被视为回文数，此时另一方无法在取完石子后使得石子总数依然是 $10$ 的倍数，这一方是必败的。

最终结论：如石子数是 $10$ 的倍数，后手方必胜，否则先手方必胜

## 代码
仅需判断最后一位是否是 $0$ 即可
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		cout<<(s[s.size() - 1] == '0' ? 'E' : 'B')<<'\n';
	}
    return 0;
}
```


---

## 作者：zzx114514 (赞：1)

# 题目大意
`B,E` 两人进行抓石子游戏，`B` 先手，两人依次在石子中抓取个数为回文数的石子，将石子抓完者胜，注意**回文数不含前导零**。
# 解题思路
## 推导过程
博弈论，只需猜结论。注意到回文数**不含前导零**，也就是说末尾为 $0$ 的数一定不是回文数。  
假设石子数个位不为 $0$，由于 `B` 先手，他只需使自己抓完后石子总数个位始终为 $0$（每次抓取石子数为石子总数的个位数），这样可以保证 `E` 一定不能一次性将剩余石子抓完。当石子数最终降至 $10$，此时轮到 `E`，而他只能抓取一个个位数，不论抓多少，最终剩余的石子数一定是个位数，即回文数，此时 `B` 一定能够一次性抓完，获得胜利。  
同理，当石子数个位为 $0$，`B` 抓取后石子数个位一定不为 $0$（不能抓 $0$ 个石子），此时 `E` 只要保证每次抓完后石子数个位为 $0$ 即可获胜。
## 结论
只需判断初始石子数个位是否为 $0$，如果是 $0$ 则 `E` 胜，否则是 `B` 胜。  
注意石子数 $S\le10^{10^5}$，只能使用字符串输入。
# 完整代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t;
string s;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>s;
		cout<<(s[s.size()-1]=='0'?'E':'B')<<endl;
	}
	return 0;
}
```

---

## 作者：_dbq_ (赞：1)

### 考虑一些 $n$ 的情况：
1. $1 \le n \le 9$，此时先手可以全部拿完，所以先手胜。
1. $n=10$，此时先手无论如何都拿不完，剩下的后手可以全部拿完，所以后手胜。
1. $11 \le n \le 19$，此时先手可以拿到只剩下 $10$ 个石子，回到第二种情况，所以先手胜。
1. $n=20$，此时先手可以拿走 $1$ 至 $9$ 个或 $11$ 个石子，回到第一种或第三种情况，所以后手胜。
1. ……

## 经过分析可以发现当 $n$ 为整十数时后手胜，否则先手胜。

因此得到如下代码
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
inline auto read(){
    auto x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    #ifdef dbq
    freopen("P10187.in","r",stdin);
    freopen("P10187.out","w",stdout);
    #endif
    int T=read();//多组数据
    while(T--)
    {
        string s;//要用字符串读，long long存不下
        cin>>s;
        //最后一位是0就是整十数
        if(s[s.size()-1]=='0') putchar('E'),putchar('\n');//后手胜
        else  putchar('B'),putchar('\n');//先手胜
    }
    return 0;
}
```

---

## 作者：_weishiqi66_ (赞：1)

[P10187 [USACO24FEB] Palindrome Game B](https://www.luogu.com.cn/problem/P10187)

经典博弈论。手动枚举一下，很容易发现规律，当 $S$ 为 $10$ 的倍数时，先手输。反之则先手必赢。

遇到这种题，我们首先根据题意，枚举答案，尝试寻找规律。拿出你的草稿纸动笔算一算。

手动枚举需注意，不会证明你先别急，枚举要多，才能得出普遍规律。

需要注意的是 $S$ 的非常大。所以可以用字符串存储。代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int T;
string c;
int main(){
	cin>>T;
	while(T--){
		cin>>c;
		if(c[c.size()-1]=='0') cout<<'E'<<endl;
		else cout<<'B'<<endl;
	}
	return 0;
}
```

---

## 作者：newbieTroll (赞：1)

博弈论。

考虑找规律分析：

- 情况 $1$：当 $1\le s\le 9$ 时，Bessie 可以直接取走这 $s$ 颗石子，所以输出 $\texttt{B}$。

- 情况 $2$：当 $s=10$ 时，因为 $10$ 不是回文数，所以 Bessie 只能先拿走 $1\sim 9$ 个石子。然后就变成了情况 $1$，所以输出 $\texttt{E}$。

- 情况 $3$：当 $11\le s\le 19$ 时，Bessie 可以先拿走 $s\bmod 10$ 个石子，就又变成了情况 $2$，输出 $\texttt{B}$。

依次类推，可知如果 $s\equiv 0 \pmod{10}$，输出 $\texttt{E}$，否则输出 $\texttt{B}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n;
	while(n--){
		cin>>s;
		int len=s.size();
		if(s[len-1]=='0'){
			cout<<'E'<<endl;
		}else{
			cout<<'B'<<endl;
		}
	}
	return 0;
}
```

---

## 作者：xykzzz (赞：1)

### 题目大意

给定一个整数 $x$，两人轮流让这个数减去一个回文数，并且都采取最优策略。输出先让这个数变为 $0$ 的人。

------

### 题解

我们枚举下不同数的结果：

当 $n<10$ 时，Bessie 获胜，因为一位数是回文数。

当 $n=10$ 时，Elsie 获胜，因为如果 Bessie 取了数 $x$，Elsie 总可以取 $10-x$，获得胜利。

当 $11 \le n \le 19$ 时，Bessie 获胜，因为在这种情况下，Bessie 可以将 $n$ 变为 $10$，接下来的情况与 $n=10$ 的情况相同。

当 $n=20$ 时，Elsie 获胜，因为 Elsie 可以使用 $2$ 次与 $n=10$ 的情况相同的方法，获得胜利。

**发现**：当 $n \bmod 10 = 0$ 时，Elsie 获胜，否则 Bessie 获胜。

- 当 $n \bmod 10 = 0$ 时，Elsie 可以使用 $n \div 10$ 次与 $n=10$ 的情况相同的方法，每次减去 $n \bmod 10$ （即 $n$ 的最后一位）。

- 当 $n \bmod 10 \ne 0$ 时，Bessie 可以减去 $n$ 的最后一位，然后与 $n \bmod 10 = 0$ 时的情况相同。

[评测记录](https://www.luogu.com.cn/record/148443069)

---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10187)

赛时 $5$ 分钟切了，纯规律题。

首先，样例给了我们一个启示：

当 $S = 10$ 时，不管 Bessie 拿多少颗石子，拿完后总会剩下 $1$ 到 $9$ 颗，此时 Elsie 是必胜的。

不过，当 $S = 12$ 时，Bessie 只要开局拿 $2$ 颗石子，$S$ 就会变成 $10$，那么和上局同样的情况出现在 Elsie 手中，此时 Bessie 是必胜的。

所以，我们可以推导出如下结论：

当游戏刚开始时，$S$ 有两种情况：

1.$S$ 为 $10$ 的倍数，即个位是 $0$。这个时候，无论 Bessie 拿多少颗石子，由于没有个位是 $0$ 的正回文数，Elsie 总能拿和 Bessie 拿的石子数加起来为 $10$ 的倍数颗的石子，这样 $S$ 个位又是 $0$ 了。因为 $0$ 的个位也是 $0$（废话），所以最终 Elsie 会取完石子。

2.$S$ 不为 $10$ 的倍数，即个位不是 $0$。此时 Bessie 可以拿个位与 $S$ 一样的石子数，这样到 Elsie 时 $S$ 的个位变成 $0$，和上面的情况相反了，所以 Bessie 会取完石子。

综上所述，$S$ 个位是 $0$ 时 Elsie 必胜，否则 Bessie 必胜。

因为 $S$ 有 $10 ^ {10 ^ 5}$，所以要用字符串。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n; string s;
int main(){
	scanf("%d", &t);
	while (t--){
		cin >> s; n = s.length();
		if (s[n - 1] == '0') puts("E");
		else puts("B");
	}
	return 0;
}
```

---

## 作者：DFM_O (赞：0)

## [P10187 题目](https://www.luogu.com.cn/problem/P10187)

### 解题思路
这种题目可以先枚举几种情况，经过枚举后可发现当 $n\bmod10=0$ 时，Elsie 必胜，否则 Bessie 必胜。

### 证明
不难发现，若某头奶牛的回合开始时石子的数量为 $10$，那么这头奶牛就输了。

所以当 $n\bmod10=0$ 时，每当 Bessie 取走 $x$ 个石子，Elsie 就取走 $10-x\bmod10$ 个石子，这样每次 Bessie 行动时剩余的石子的个数都是 $10$ 的倍数，那么总有一次 Bessie 行动时剩余的石子的个数为 $10$，Bessie 必输。

当 $n\bmod10>0$ 时，开始时 Bessie 取走 $10-n\bmod10$ 个石子即可变成上面一种情况，Elsie 必输。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		if(s[s.size()-1]=='0')
			cout<<"E\n";
		else
			cout<<"B\n";
	}
	return 0;
}
```

---

## 作者：DL_Lingkong (赞：0)

# P10187 [USACO24FEB] Palindrome Game B 题解

## 题目大意

$\texttt {Bessie}$ 和 $\texttt {Elsie}$ 面前有 $S$ 个石子（$1 \le S \le {10} ^ {{10} ^ {5}}$），两头牛轮流求出若干个石子，取出的石子数必须是**回文数**，$\texttt {Bessie}$ 先取，当一头牛取完剩下的石子就获胜，问谁能胜利。

## 题目分析

首先来推 $1 \le S \le 10$。

1. 当 $1 \le S \le 9$ 时，因为 $1$ 位数是回文数，所以 $\texttt {Bessie}$ 必胜。

2. 当 $S = 10$ 时，因为 $10$ 不是回文数，所以它只能拆成两个 $1$ 位数相加，此时 $\texttt {Elsie}$ 必胜。

对于 $S \ge 11$，我们就不用推了。原因如下：

假设 $\texttt {Elsie}$ 取 $k$ 个，则 $\texttt {Bessie}$ 一定可以取 $10 \times n - k$ 个与其凑 $10$，这样又变为了 $1 \le S \le 10$ 的情况。（其中 $10 \times n \le S$）

所以我们只需判断这个数是不是 $10$ 的倍数就好了。

但是，看看数据范围！！！

$$1 \le S \le {10} ^ {{10} ^ {5}}$$

`long long` 都存不下，要用 `string`。

`string` 类型的话，判断它最后一位是否为 $0$ 就好了。

## 上代码！

```cpp
#include <iostream>
using namespace std;
int n;
string x; 
void be() // init & input
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> x;
		if(x[int(x.length()) - 1] == '0') // 最后一位是否为0，为0则Elsie必胜，否则Bessie必胜
		{
			puts("E");
		}
		else
		{
			puts("B");
		}
	}
	return ;
}
void kin() // programming
{
	return ;
}
void ei() // output
{
	return ;
}
int main()
{
	be();
	kin();
	ei();
	return 0;
}
```

---

