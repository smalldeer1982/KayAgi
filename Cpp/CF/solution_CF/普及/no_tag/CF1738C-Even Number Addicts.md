# Even Number Addicts

## 题目描述

Alice and Bob are playing a game on a sequence $ a_1, a_2, \dots, a_n $ of length $ n $ . They move in turns and Alice moves first.

In the turn of each player, he or she should select an integer and remove it from the sequence. The game ends when there is no integer left in the sequence.

Alice wins if the sum of her selected integers is even; otherwise, Bob wins.

Your task is to determine who will win the game, if both players play optimally.

## 说明/提示

In the first and second test cases, Alice always selects two odd numbers, so the sum of her selected numbers is always even. Therefore, Alice always wins.

In the third test case, Bob has a winning strategy that he always selects a number with the same parity as Alice selects in her last turn. Therefore, Bob always wins.

In the fourth test case, Alice always selects two even numbers, so the sum of her selected numbers is always even. Therefore, Alice always wins.

## 样例 #1

### 输入

```
4
3
1 3 5
4
1 3 5 7
4
1 2 3 4
4
10 20 30 40```

### 输出

```
Alice
Alice
Bob
Alice```

# 题解

## 作者：Sycamore_Ma (赞：12)

## 题目链接
Codeforces Global Round 22, Problem C
[1738C Even Number Addicts](https://codeforces.com/problemset/problem/1738/C)

## 题目大意
给定长度为 $n$ 的数列 $a_1, a_2, \dots, a_n$  ，两名玩家 Alice 、 Bob 依次以最优策略从数列中取走一个数，**Alice 先取**，直至为空博弈结束。若 **Alice** 取走的所有数之和为**偶**，**Alice 胜利**；若 **Alice** 取走的所有数之和为**奇**，**Bob 胜利**。输入给定序列，请输出必胜玩家。

---
## 解法 1 DP
### *定义*
 - 定义两个二维 DP（每个 DP 的第一维代表序列 $a$ 中偶数 $a_i$ 的个数，第二维代表 $a$ 中奇数 $a_i$ 的个数）：
 	 -  `dpEven[maxn][maxn]` ：代表**首名开始的玩家能否**以最优策略得到**偶数和**，简称***首名以偶胜***；
	 -  `dpOdd[maxn][maxn]` ：代表**首名开始的玩家能否**以最优策略得到**奇数和**，简称***首名以奇胜***。

```cpp
const int maxn = 100 + 10;
// dp[i][j]: odd num == i, even num == j
// Whether the person who starts first can get an EVEN sum. (plays the optimal strategy)
bool dpEven[maxn][maxn];
// Whether the person who starts first can get an ODD sum. (plays the optimal strategy)
bool dpOdd[maxn][maxn]; 
```

一些实例：

```cpp
// n == 1
dpEven[1][0] = false;   dpOdd[1][0] = true;
dpEven[0][1] = true;    dpOdd[0][1] = false;
// n == 2
dpEven[2][0] = false;   dpOdd[2][0] = true;
dpEven[1][1] = true;    dpOdd[1][1] = true;
dpEven[0][2] = true;    dpOdd[0][2] = false;
// n == 3
dpEven[3][0] = true;    dpOdd[3][0] = false;
dpEven[2][1] = false;   dpOdd[2][1] = true;
dpEven[1][2] = false;   dpOdd[1][2] = true;
dpEven[0][3] = true;    dpOdd[0][3] = false;
```

> 为理解方便，此处采用两个二维 DP 的定义方法，读者也可采用三维 DP 的定义方法。

### _初始状态_
 - 不难得到当序列**全为偶数**时，***首名以偶胜*** 为**真**，***首名以奇胜*** 为**假**；
 - 当序列**全为奇数**时：
	 - 若首名玩家从序列 $a$ 中最终取走偶数个数，***首名以偶胜*** 为**真**，***首名以奇胜*** 为**假**；
	 - 若首名玩家从序列 $a$ 中最终取走奇数个数，***首名以偶胜*** 为**假**，***首名以奇胜*** 为**真**。
     
```cpp
for (int tot = 1; tot < maxn; tot ++){
	dpEven[0][tot] = true;
	dpOdd[0][tot] = false;
	
	int aliceNum = (tot+1) / 2;
	if (aliceNum % 2 == 0){
	    dpEven[tot][0] = true;
	    dpOdd[tot][0] = false;
	}
	else {
	    dpEven[tot][0] = false;
	    dpOdd[tot][0] = true;
	}
}
```

### _状态转移_

> 共识：从序列拿走一个**偶数**，剩余序列和的**奇偶性不改变**；拿走一个**奇数**，剩余序列和的**奇偶性改变**。

我们不妨假设 Alice 已经从 $n$ 个数字中拿走了一个数字，并把 Bob 当成首名玩家来分析在 $n-1$ 个数字的序列中的 ***首名以偶胜*** 和 ***首名以奇胜*** 状态，Bob 的胜负条件可以决定 Alice 是否胜负。此问题在上一次转移已得到求解。
 - 若**初始序列和为偶数**，Bob 最终需要得到奇数和才能击败 Alice ：
	 - 无论 Alice 从序列 $a$ 中拿走一个奇数还是偶数，若 Bob 在剩余数字中的 ***首名以奇胜*** 状态全为 **假**，则 Alice 的 ***首名以偶胜*** 为**真**，反之为假。
	 - 同时更新 Alice 的 ***首名以奇胜***，无论 Alice 拿走一个奇数还是偶数，若 Bob 在剩余数字中的 ***首名以偶胜*** 状态全为 **假**，则 Alice 的 ***首名以奇胜*** 为**真**，反之为假。
 - 若**初始序列和为奇数**，Bob 最终需要得到偶数和才能击败 Alice ：
	 - 无论 Alice 从序列 $a$ 中拿走一个奇数还是偶数，若 Bob 在剩余数字中的 ***首名以偶胜*** 状态全为 **假**，则 Alice 的 ***首名以偶胜*** 为**真**，反之为假。
	 - 同时更新 Alice 的 ***首名以奇胜***，无论 Alice 拿走一个奇数还是偶数，若 Bob 在剩余数字中的 ***首名以奇胜*** 状态全为 **假**，则 Alice 的 ***首名以奇胜*** 为**真**，反之为假。
     
```cpp
for (int tot = 1; tot < maxn; tot ++){
    for (int k = 1; k < tot; k ++){
        // totSum == even, Bob need ODD sum to defeat Alice
        if ((tot-k) % 2 == 0){
            dpEven[tot-k][k] = !(dpOdd[tot-k-1][k] && dpOdd[tot-k][k-1]);
            dpOdd[tot-k][k] = !(dpEven[tot-k-1][k] && dpEven[tot-k][k-1]);
        }
        // totSum == odd, Bob need EVEN sum to defeat Alice
        else {
            dpEven[tot-k][k] = !(dpEven[tot-k-1][k] && dpEven[tot-k][k-1]);
            dpOdd[tot-k][k] = !(dpOdd[tot-k-1][k] && dpOdd[tot-k][k-1]);
        }
    }
}
```

### *代码*
最终统计序列 $a$ 中偶数 $a_i$ 和奇数 $a_i$ 分别出现的次数`cntEven`、`cntOdd`，并判断 ***首名以偶胜*** `dpEven[cntOdd][cntEven]` 的状态即可输出胜利者姓名。
代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define YN(x) cout << (x ? "Alice" : "Bob") << endl
#define Yn(x) cout << (x ? "Yes" : "No") << endl
#define yn(x) cout << (x ? "yes" : "no") << endl

const int maxn = 100 + 10;
// dp[i][j]: odd num == i, even num == j
// Whether the person who starts first can get an EVEN sum. (plays the optimal strategy)
bool dpEven[maxn][maxn];
// Whether the person who starts first can get an ODD sum. (plays the optimal strategy)
bool dpOdd[maxn][maxn];

void init()
{
    for (int tot = 1; tot < maxn; tot ++){
        dpEven[0][tot] = true;
        dpOdd[0][tot] = false;

        int aliceNum = (tot+1) / 2;
        if (aliceNum % 2 == 0){
            dpEven[tot][0] = true;
            dpOdd[tot][0] = false;
        }
        else {
            dpEven[tot][0] = false;
            dpOdd[tot][0] = true;
        }

        for (int k = 1; k < tot; k ++){
            // totSum == even, Bob need ODD sum to defeat Alice
            if ((tot-k) % 2 == 0){
                dpEven[tot-k][k] = !(dpOdd[tot-k-1][k] && dpOdd[tot-k][k-1]);
                dpOdd[tot-k][k] = !(dpEven[tot-k-1][k] && dpEven[tot-k][k-1]);
            }
            // totSum == odd, Bob need EVEN sum to defeat Alice
            else {
                dpEven[tot-k][k] = !(dpEven[tot-k-1][k] && dpEven[tot-k][k-1]);
                dpOdd[tot-k][k] = !(dpOdd[tot-k-1][k] && dpOdd[tot-k][k-1]);
            }
        }
    }
}

int main()
{
	init();
    int tt;     cin >> tt;
    while (tt --){
        int n; 		cin >> n;
        int cntOdd = 0, cntEven = 0;
        int x;      
        for (int i = 0; i < n; i ++){
            cin >> x;
            if (x & 1)  cntOdd ++;
            else        cntEven ++;
        }
        YN(dpEven[cntOdd][cntEven]);
    }
    return 0;
}
```

---
## 解法 2 数学推理

> 共识：奇数 + 奇数 = 偶数；奇数 + 偶数 = 奇数；偶数 + 偶数 = 偶数。

统计序列 $a$ 中偶数 $a_i$ 和奇数 $a_i$ 分别出现的次数 $e$、$o$，依次可确定下列几种情况，决定二人胜负态：

 1. 当 $o \equiv 2 \pmod 4$ 时， Bob 存在必胜态；
 
> Bob 仅需保证每次所取数字与 Alice 所取数字奇偶性相同即可，这样可以使二者取走的奇数个数相同。若在此过程中 Alice 取走了最后一个偶数，奇数必然剩余偶个。随后，Alice 和 Bob 各自将选择剩余奇数的一半。最后，Alice 和 Bob 都拥有 $\frac{o}{2}$ 个奇数，Alice 和为奇数，Alice 败。

 2. 当 $o \equiv 3 \pmod 4$ 时， Alice 存在必胜态；
 
> Alice 首先选择一个奇数，若 Bob 能从剩下的数字中取走偶个奇数，则 Bob 胜。从情况 1 中可知，Bob 必败。

 3. 当 $o \equiv 0 \pmod 4$ 时， Alice 存在必胜态；
 
> Alice 首先选择一个偶数，在随后的操作中，Alice 仅需保证每次所取数字与 Bob 所取数字奇偶性相同即可，这样可以使二者取走的奇数个数相同。若在此过程中偶数被取完，奇数必然剩余偶个。随后，Alice 和 Bob 各自将选择剩余奇数的一半。最后，Alice 和 Bob 都拥有 $\frac{o}{2}$ 个奇数，Alice 和为偶数，Alice 胜。

 4. 当 $o \equiv 1 \pmod 4$ 时，先选择奇数的人败。
 
> 先选择奇数的人将会导致对手出现情况 3，对手必胜。博弈开始时，如果 $e$ 为偶即 $e \equiv 0 \pmod 2$，则 Bob 将会取走最后一个偶数，Alice 败；$e$ 为奇即 $e \equiv 1 \pmod 2$，则 Alice 胜。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define YN(x) cout << (x ? "Alice" : "Bob") << endl

int main()
{
    int tt;     
    cin >> tt;
    while (tt --){
        int n; 		
        cin >> n;
        int cntOdd = 0, cntEven = 0;
        int x;      
        for (int i = 0; i < n; i ++){
            cin >> x;
            if (x & 1)  cntOdd ++;
            else        cntEven ++;
        }
        
        bool ok = false;
        if (cntOdd % 4 == 2)		ok = false;
        else if (cntOdd % 4 == 3)	ok = true;
    	else if (cntOdd % 4 == 0)	ok = true;
    	else if (cntEven % 2 == 1)	ok = true;
    	
        YN(ok);
    }
    return 0;
}
```


---

## 作者：Land_ER (赞：3)

## 题意简述
- Alice 与 Bob 玩关于一个长为 $n$ 的数列 $a_1, a_2, \dots, a_n$ 的游戏，其中 $1 \leqslant n \leqslant 100$。
- Alice 先手，两人轮流从数列中取走一个数字，直到数列为空。
- 若最后 Alice 手中所有数字之和为偶数，则 Alice 赢，否则 Bob 赢。
- $t$ 组数据，其中 $1 \leqslant t \leqslant 100$，对于每组数据输出胜者的名字。

## 解题思路
数学解法需要较为复杂的推导证明，这里提供一个暴力思路。

记原数列中有 $x$ 个奇数， $y$ 个偶数。由于 $1 \leqslant n \leqslant 100$，选择对于数据范围内所有的 $(x,y)$ 预处理答案。

我们对于每一组 $(x,y)$，计算以下四项：
- 先手是否有取到和为偶数的策略。
- 先手是否有取到和为奇数的策略。
- 后手是否有取到和为偶数的策略。
- 后手是否有取到和为奇数的策略。

1. 当 $x = 0$ 时，无论先后手都只能取到偶数。
2. 当 $y = 0$ 时，先手能且只能取到 $\lceil \frac{x}{2} \rceil$ 个奇数，后手能且只能取到 $\lfloor \frac{x}{2} \rfloor$ 个奇数。
3. 其他情况：

    3.1 当对于局面 $(x-1,y)$ 后手能取到奇数个奇数**或**对于局面 $(x,y-1)$ 后手能取到偶数个奇数时，局面 $(x,y)$ 中先手能取到偶数个奇数。

    3.2 当对于局面 $(x-1,y)$ 后手能取到偶数个奇数**或**对于局面 $(x,y-1)$ 后手能取到奇数个奇数时，局面 $(x,y)$ 中先手能取到奇数个奇数。


    3.3 当对于局面 $(x-1,y)$ 先手能取到偶数个奇数**且**对于局面 $(x,y-1)$ 先手能取到偶数个奇数时，局面 $(x,y)$ 中后手能取到偶数个奇数。

    3.4 当对于局面 $(x-1,y)$ 先手能取到奇数个奇数**且**对于局面 $(x,y-1)$ 先手能取到奇数个奇数时，局面 $(x,y)$ 中后手能取到奇数个奇数。

预处理后直接查询即可。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int ans[105][105][4];

void init(void) {
    ans[0][0][0] = 1;
    ans[0][0][1] = 0;
    ans[0][0][2] = 1;
    ans[0][0][3] = 0;
    for(int i = 1; i <= 100; ++ i)
        ans[i][0][0] = !(int(ceil(double(i) / 2.0)) & 1),
        ans[i][0][1] = !ans[i][0][0],
        ans[i][0][2] = !((i / 2) & 1),
        ans[i][0][3] = !ans[i][0][2],
        ans[0][i][0] = 1,
        ans[0][i][1] = 0,
        ans[0][i][2] = 1,
        ans[0][i][3] = 0;

    for(int i = 1; i <= 100; ++ i) {
        for(int j = 1; j <= 100; ++ j) {
            ans[i][j][0] = ans[i-1][j][3] || ans[i][j-1][2];
            ans[i][j][1] = ans[i-1][j][2] || ans[i][j-1][3];
            ans[i][j][2] = ans[i-1][j][0] && ans[i][j-1][0];
            ans[i][j][3] = ans[i-1][j][1] && ans[i][j-1][1];
        }
    }
    return;
}

void solve(void) {
    int n, a;
    int p = 0, q = 0;
    cin >> n;
    for(int i = 0; i < n; ++ i) {
        cin >> a;
        if(a & 1)
            ++ p;
        else
            ++ q;
    }

    puts(ans[p][q][0] ? "Alice" : "Bob");
    
    return;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    init();
    while(t --) {
        solve();
    }
    return 0;
}
```

---

## 作者：XenonWZH (赞：2)

[更好的阅读体验请点这](https://xenonwzh.github.io/cf-1738c/)

# 题意描述

[Codeforces 链接](https://codeforces.com/problemset/problem/1738/C)

Alice 和 Bob 玩一个游戏，这个游戏中有一个有 $n$ 项的序列 $a$，Alice 先手，两人轮流在 $a$ 中取走一个数。若最终取完后 Alice 取走的数的和为偶数则 Alice 获胜，否则 Bob 获胜。若两人均按最优策略决策，求出最终的获胜方。

# 解题思路

目前问题过于复杂，我们可以先考虑一个简单问题：若序列 $n$ 中只有奇数，谁会赢？

这个问题答案显然。若 $n \bmod 4 = 1$ 或 $n \bmod 4 = 2$ 时 Bob 赢，否则 Alice 赢。

接下来我们把偶数加进来，我们设奇数个数为 $\text{cnt1}$，偶数个数为 $\text{cnt0}$。对于 $\text{cnt0} \bmod 2 = 0$ 的情况与 $n$ 全为奇数的情况相同。因为只要其中有一个人选了偶数，则下一个人立即选偶数，相当于转化为 $\text{cnt0} - 2$ 的局面，这样周而复始可将 $\text{cnt0}$ 消为 $0$。且后手跟着先手选偶数的抉择对于 Alice 和 Bob 均是最优策略。

接下来我们考虑 $\text{cnt0} \bmod 2 = 1$ 的情况。我们依然可以将 $\text{cnt1} \bmod 4$ 的情况分类讨论：当 $\text{cnt1} \bmod 4 = 1$ 时，Alice 最优策略是取走“唯一的”偶数，然后 Alice 必胜；当 $\text{cnt1} \bmod 4 = 0$ 或 $\text{cnt1} \bmod 4 = 3$ 时，Alice 最优策略是无论如何都不取“唯一的”偶数，然后 Alice 必胜；当 $\text{cnt1} \bmod 4 = 2$ 时，无论 Alice 取不取“唯一的”偶数，Bob 都必胜。

# 代码演示

```cpp
#include <cstdio>
#include <iostream>

void solve() {
    int n;
    int cnt0 = 0, cnt1 = 0;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        if (a % 2)
            cnt1++;
        else
            cnt0++;
        cnt0 &= 1;
    }

    if (cnt0 == 0) {
        if ((cnt1 % 4 == 1 || cnt1 % 4 == 2))
            puts("Bob");
        else
            puts("Alice");
    } else {
        if ((cnt1 % 4 == 1 || cnt1 % 4 == 3 || cnt1 % 4 == 0))
            puts("Alice");
        else
            puts("Bob");
    }
}

int main() {
    int t;

    scanf("%d", &t);

    while (t--) solve();

    return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

因为只有每个数的奇偶性重要，所以问题简化为 $a_i = 0 / 1$。

设 $f_{o, z, par, play}$ 表示面对还有 $o$ 个 $1$，$z$ 个 $0$，当前 Alice 选择的数的和的奇偶性和当前先手为 Alice（$0$） 或 Bob（$1$） 时，先手是否必胜。

当 $o = z = 0$ 时，$f_{o, z, par, play} = [par = play]$。否则枚举选择奇数或偶数，根据实际情况转移即可。若后继态先手必败，则当前态先手必胜。

$$
f_{o, z, par, play} = (\lnot f_{o - 1, z, par \oplus (play \oplus 1), play \oplus 1}) \lor (\lnot f_{o, z - 1, par, play \oplus 1})
$$
时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1738/submission/174183895)。

通过下模仿棋可知 $0$ 的个数可对 $2$ 取模，$1$ 的个数可对 $4$ 取模。手玩所有 $0\leq o < 4$ 和 $0 \leq z < 2$ 的局面可以除输入外 $\mathcal{O}(1)$ 回答单组询问。[代码](https://codeforces.com/contest/1738/submission/174203923)。

---

## 作者：Allanljx (赞：1)

## 题意
给定一个数组 $a$，Alice 和 Bob 要轮流取数，Alice 要尽量使她取得数的和是偶数，Bob 要尽量使 Alice 取得数的和是奇数。假设两人都足够聪明，问谁能获胜。
## 思路
由于只考虑奇偶性，所以可以将 $a$ 数组的值改为 $0/1$，设 $x$ 是 $0$ 的个数，$y$ 是 $1$ 的个数。以下讨论的 $y$ 均为模 $4$ 后的结果。
- 当 $y=0$ 时 Alice 可以先随便取一个，然后跟着 Bob 取，最终一定能取到偶数个 $1$，最终 Alice 会赢。
- 当 $y=1$ 时 Alice 和 Bob 都要尽可能后开始取 $1$，因为先开始取 $1$ 的人会拿到奇数个 $1$，所以当 $x$ 是奇数时 Alice 会赢，否则 Bob 会赢。
- 当 $y=2$ 时 Alice 必然会取到奇数个 $1$，所以 Bob 赢。
- 当 $y=3$ 时 Alice 先取 $1$ 个 $1$ 然后跟着 Bob 取就可以取到偶数个 $1$。

具体细节见代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a,b;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		a=b=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			if(x%2) b++;
			else a++;
		}
		if(!(b%4)) cout<<"Alice\n";
		else if(b%4==1)
		{
			if(a%2) cout<<"Alice\n";
			else cout<<"Bob\n";
		}
		else if(b%4==2) cout<<"Bob\n";
		else cout<<"Alice\n";
	}
}
```

---

## 作者：zuytong (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1738C)


------------
## 思路

由于 $n\le 100$，可以直接跑 DP 判断，下面讲的是博弈解法：

显然，我们只需要将数按 $\bmod~2$ 分成两类，我们假设有 $a$ 个 $0$ 和 $b$ 个 $1$。

- 1. $b \equiv 0 \pmod 4$，Alice Win

Alice 开局一直选 $0$，当 Bob 开始选 $1$ 时，Alice 也跟着选 $1$，这样双方各拿一半 $1$；

或者没有 $0$ 能选，那显然还是 Alice 和 Bob 各拿一半 $1$，依旧是 Alice 胜出。

- 2. $b \equiv 3 \pmod 4$，Alice Win

Alice 开局先取一个 $1$，局面就和上面的一样了，双方都会各拿**剩下**的一半的 $1$；而由于 Alice 开局就拿了一个 $1$，她手上的数的和是偶数。

- 3. $b \equiv 2 \pmod 4$，Bob Win

还是经典局面，双方依旧会各取到一半的 $1$，而此时 Alice 手上的数的和是奇数，Bob 获胜。

- 4. $b \equiv 1 \pmod 4$ 且 $a  \equiv 0 \pmod 2$，Bob Win

此时 Alice 如果开局选 $1$，那么就回到经典局面，双方各拿**剩下**的一半 $1$，Alice 输掉比赛；如果 Alice 开局选 $0$，那么 Bob 会跟着选 $0$，~~奉陪到底，~~ Alice 依旧输掉比赛。

- 5. $b \equiv 1 \pmod 4$ 且 $a  \equiv 1 \pmod 2$，Alice Win

此时 Alice 的最优策略就是开局选 $0$，就回到第 $4$ 种情况，只不过是 Bob 先选，此时 Bob 只能选到奇数个 $1$，而 Alice 就能拿偶数个 $1$，Alice 胜。


------------
## 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define FOR(i, x, y) for(int i = (x); i <= (y); i++)
#define ROF(i, x, y) for(int i = (x); i >= (y); i--)
#define PFOR(i, x) for(int i = he[x]; i; i = r[i].nxt)
using namespace std;
inline int rd()
{
    int sign = 1, re = 0; char c = getchar();
    while(!isdigit(c)){if(c == '-') sign = -1; c = getchar();}
    while(isdigit(c)){re = re * 10 + (c - '0'); c = getchar();}
    return sign * re;
}
int T, n, a[2];
signed main()
{
    T = rd();
    while(T--)
    {
    	n = rd(); a[0] = a[1] = 0;
    	FOR(i, 1, n) a[rd() & 1]++;
    	if(a[1] % 4 == 0 || a[1] % 4 == 3) {puts("Alice"); continue;}
    	if(a[1] % 2 == 0) {puts("Bob"); continue;}
    	if(a[0] & 1) {puts("Alice"); continue;}
    	puts("Bob");
	}
    return 0;
}
```


---

