# Card Game

## 题目描述

There are $ n $ cards stacked in a deck. Initially, $ a_{i} $ is written on the $ i $ -th card from the top. The value written on a card does not change.

You will play a game. Initially your score is $ 0 $ . In each turn, you can do one of the following operations:

- Choose an odd $ ^{\dagger} $ positive integer $ i $ , which is not greater than the number of cards left in the deck. Remove the $ i $ -th card from the top of the deck and add the number written on the card to your score. The remaining cards will be reindexed starting from the top.
- Choose an even $ ^{\ddagger} $ positive integer $ i $ , which is not greater than the number of cards left in the deck. Remove the $ i $ -th card from the top of the deck. The remaining cards will be reindexed starting from the top.
- End the game. You can end the game whenever you want, you do not have to remove all cards from the initial deck.

What is the maximum score you can get when the game ends?

 $ ^{\dagger} $ An integer $ i $ is odd, if there exists an integer $ k $ such that $ i = 2k + 1 $ .

 $ ^{\ddagger} $ An integer $ i $ is even, if there exists an integer $ k $ such that $ i = 2k $ .

## 说明/提示

In the first test case, one can get the score of $ 5 $ as follows:

1. In the first turn, choose $ i=2 $ . Your score remains $ 0 $ and the numbers written on the cards from the top will become $ [-4, -3, 5] $ .
2. In the second turn, choose $ i=3 $ . Your score will become $ 5 $ and the numbers written on the cards from the top will become $ [-4, -3] $ .
3. In the third turn, end the game with the score of $ 5 $ .

In the second test case, one can get the score of $ 4 $ as follows:

1. In the first turn, choose $ i=3 $ . Your score will become $ 3 $ and the numbers written on the cards from the top will become $ [1, -2, -4] $ .
2. In the second turn, choose $ i=1 $ . Your score will become $ 4 $ and the numbers written on the cards from the top will become $ [-2, -4] $ .
3. In the third turn, end the game with the score of $ 4 $ .

In the third test case, one can get the score of $ 2 $ as follows:

1. In the first turn, choose $ i=1 $ . Your score will become $ -1 $ and the numbers written on the cards from the top will become $ [3, -5] $ .
2. In the second turn, choose $ i=1 $ . Your score will become $ 2 $ and the numbers written on the cards from the top will become $ [-5] $ .
3. In the third turn, end the game with the score of $ 2 $ .

## 样例 #1

### 输入

```
4
4
-4 1 -3 5
4
1 -2 3 -4
3
-1 3 -5
1
-1```

### 输出

```
5
4
2
0```

# 题解

## 作者：Leeb (赞：8)

### 题目大意

给你一个长度为 $n$ 的序列 $a$，有如下三种操作：

- 选择奇数 $i$，得分加上 $a_i$ 并从序列中删去 $a_i$。
  
- 选择偶数 $i$，直接从序列中删去 $a_i$ 且得分不变。
  
- 停止选择。
  

求最大得分。

### 解题思路

- 显然的，我们可以发现，从第三张牌开始后的正数牌（包括第三张牌）都可以取到。
  
  - 证明：对于任意一个编号大于三的正数牌，如果在奇数位上，则可以直接取；如果在偶数位上，则先删去它前面的一张负数牌，再直接取出。
    
- 所以我们可以将 $a_3, a_4, a_5, ... ,a_n$ 当中的正数求和，然后讨论 $a_1 和 a_2$。
  
  - 当 $a_1$，$a_2$ 均为正数时，两张都取。
    
  - 只有 $a_1$ 为正数时，只取 $a_1$。
    
  - 当 $a_1$，$a_2$ 一正一负且 $a_1+a_2>0$ 时，两张都取。
    
  - 其余情况两张均不取。
    

### 代码参考

数据量较大，记得开`long long`。

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 200005
#define inf 0x3f3f3f3f
#define elif else if
#define int long long
#define ub upper_bound
#define lb lower_bound
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, a[N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
	int t = in();
	while (t--) {
		n = in(); int ans = 0; mem(a, 0);
		for (int i = 1; i <= n; ++i) {
			a[i] = in();
			if (i >= 3 && a[i] > 0) ans += a[i]; 
		}
		if (a[1] >= 0 && a[2] >= 0) ans += a[1] + a[2];
		elif (a[1] >= 0) ans += a[1];
		elif (a[1] + a[2] > 0) ans += a[1] + a[2];
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：佬头 (赞：4)

## Description
有 $n$ 个整数 $a_i$ 和两种操作：
- 选择奇数 $i$，删除第 $i$ 个数并获得这个数的分值，下文中称为**取走**。
- 选择偶数 $i$，删除第 $i$ 个数，下文中称为**删除**。

得分初始是 $0$，求你能获得的[**最大得分**](https://www.luogu.com.cn/problem/CF1882C)。

## Solution
肯定尽量取走 $a_i\ge0$ 的，考虑到**从后往前**把所有奇数位上的非负数取走，那么此时的非负数便都在偶数位上了，接下来就要尽量把这些数也取走（即把偶数位上的非负数转移到奇数位上）：
- 当 $a_1\ge0$ 时，此前我们将其取走后便已经达到了目的。
- 当 $a_1\lt0,a_2\lt0$ 时，显然我们把 $a_2$ 删除也能达到目的。
- 当 $a_1\lt0,a_2\ge0$ 时，如果 $a_1+a_2\ge0$，我们就取走 $a_1$；否则，直接删除 $a_2$。

综上，对于任意一个 $a_i\ge0\ (i\gt2)$，我们都可以取走，然后在对前两个数进行分类讨论即可。

时间复杂度 $\mathcal{O}(\sum n)$。记得开 `long long`。

## Code
```cpp
#include <iostream>
using namespace std;
int n, a;
long long ans;
int read(){
	int x = 0;
	bool tf = 0;
	char a = getchar();
	while(a < '0' || '9' < a){
		if(a == '-') tf = 1;
		a = getchar();
	}
	while('0' <= a && a <= '9') x = (x << 3) + (x << 1) + (a ^ 48), a = getchar();
	return tf? -x: x;
}
void write(long long x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	for(int _ = read(); _ >= 1; _ --){
		n = read(), a = read();
		if(n == 1){
			write(a > 0? a: 0), puts("");
			continue;
		}
		if(a > 0){
			ans = a;
			a = read(), ans += a > 0? a: 0;
		}
		else a += read(), ans = a > 0? a: 0;
		for(int i = 3; i <= n; ++ i) a = read(), ans += a > 0? a: 0;
		write(ans), puts("");
	}
	return 0;
}
```

---

## 作者：phigy (赞：4)

我们开始的时候只有奇位的数拿走可以计入。

我们发现当我们拿走一个数后，这个数前面的奇偶不变，而后面的相当奇偶交换了。

因此我们设 $f_{i,1/0}$ 表示对于后 $i$ 个在第 $i$ 个时能拿 奇/偶 位时的最大答案。

那么那么如果 $i$ 可以拿我们就有两种选择，先拿 $i$ 再拿后 $i+1$ 的，或反过来，那么实际上就是奇偶都可以拿转移过来。

```cpp
#include <cinttypes>
#include <iostream>

#define int long long

using namespace std;

int T;
int n;
int a[200005];
int f[200005][2];

signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        for(i=n;i>=1;i--)
        {
            if(i&1)
            {
                f[i][1]=max(f[i+1][1],max(f[i+1][1],f[i+1][0])+a[i]);
                f[i][0]=max(f[i+1][1],f[i+1][0]);
            }
            else
            {
                f[i][1]=max(f[i+1][0],f[i+1][1]);
                f[i][0]=max(f[i+1][0],max(f[i+1][1],f[i+1][0])+a[i]);
            }
        }
        cout<<f[1][1]<<endl;
        for(i=1;i<=n;i++)
        {
            f[i][0]=f[i][1]=0;
        }
    }
    return 0;
}

```


---

## 作者：BugGod (赞：2)

## $\texttt{Solution}$
显然的，为了使分数尽量的大，我们尽量取正数的牌。对于一般的正数牌，如果它在奇数位，直接取即可。如果它在偶数位，可以弃掉它前面一张负数牌。

但是，这仅对 $a_3,a_4,\cdots,a_n$ 有效。那么，我们就可以将 $a_3,a_4,\cdots,a_n$ 中的正数牌加起来，然后特判 $a_1,a_2$ 的情况。

1. $a_1>0$ ，则取走 $a_1$ ，如果 $a_2>0$ ，那么再取走 $a_2$ 。
1. $a_1\leq 0$ ，如果 $a_1+a_2>0$ ，那么都取，否则不取。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[200010],ans;
signed main()
{
	cin>>t;
	while(t--)
	{
		ans=0;
		memset(a,0,sizeof(a));
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=3;i<=n;i++)
		{
			if(a[i]>=0)ans+=a[i];
		}
		if(a[1]>0)
		{
			ans+=a[1];
			if(a[2]>0)ans+=a[2];
		}
		else
		{
			if(a[1]+a[2]>0)ans+=a[1]+a[2];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Reseamus (赞：1)

可以发现，可以取到所有第 $3$ 张牌及以后的牌中的价值为正的牌（找到这些牌中第一张价值为正的牌，若它在偶数位置就将它前面一张价值为负的牌弃掉，然后不断地去掉它后面的负牌，取正牌即可）。

那么只需求第 $3$ 张牌之后所有正牌的和，再判断一下取第 $1$ 张和第 $2$ 张牌能否使答案更优即可。若第一张牌为正，那么很显然可以取到所有正牌，将第 $1$ 张牌与第 $2$ 张牌中的正牌加上；若第 $1$ 张牌为负，且第二张牌为正，那就可以取第一张牌以及它之后的所有正牌或不取第 $1$ 张和第 $2$ 张牌，判断一下谁大即可。

[代码](https://codeforces.com/contest/1882/submission/225583817)很短，时间复杂度 $O(n)$。

---

## 作者：lol_qwq (赞：0)

# CF1882C 题解

### 思路

有点绕，但是我们只需要取正数，负数舍掉就行，由此，第三个数开始，每个数都能通过舍去负数选取正数。

1. 若前两个均为正，直接取。
1. 若前两个一正一负，和为正，都取，否则只取第一位。
1. 若前两为负，不取。

### 代码

有了思路，代码就很清晰，把上面分类讨论即可，这里就不放了。

---

## 作者：Flyingsnow (赞：0)

## 题意

有一叠 $n$ 张卡牌的有序牌堆，每张牌上有一个整数数值 $a_i$，你可以按照如下的方案获取得分，得分初始是 $0$。

每次你可以做下面三种操作之一：

- 选择奇数 $i$，则选择牌堆从上往下数第 $i$ 张牌弃掉后获得等同于其卡面上数值的分数；
- 选择偶数 $i$，则选择牌堆从上往下数第 $i$ 张牌弃掉后，**什么都不做**；
- 直接结束游戏，你可以在任意时刻结束游戏，无论牌桌上有没有剩余的牌。

求你能获得的最大分数。

$1\le t \le 10^4 , 1\le n,\sum n \le 2\times10^5,-10^9\le a_i \le 10^9 $

## 思路

很显然，我们可以得出一个结论，从第三位开始，任意一个数都可取到。

证明：如果是第三个数以后的正数，如果是奇数位置上，直接取；在偶数位置上，删去前面的负数牌，这样取。

那这样这道题就相当简单了。

于是我们考虑从第三位开始取所有的正数，讨论第一位与第二位。

1. 当第一位与第二位都为正，都取。
2. 当两个数一正一负，第一位 $+$ 第二位 $> 0$，都取。否则只取第一位。
3. 其他都不取。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 7;

int a[N];

int T, n;

signed main() {
	for (scanf("%lld", &T); T; --T) {
		int ans = 0;
		scanf("%lld", &n);
		memset(a, 0, sizeof a);
		
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
			
			if (i >= 3 && a[i] > 0)
				ans += a[i];
		}
		
		if (a[1] >= 0 && a[2] >= 0)
            ans += a[1] + a[2];
        else if (a[1] >= 0) 
        	ans += a[1];
        else if (a[2] >= 0 && a[1] + a[2] > 0)
        	ans += a[1] + a[2];
		
		printf("%lld\n", ans);
	}
	
	return 0;
}

```





---

## 作者：MhxMa (赞：0)

## 题意

给定一个长度为 $n$ 的数组 $a$，其中 $a[i]$ 表示第 $i$ 张牌的点数。现在有两个玩家进行游戏，他们轮流从数组中选择一张牌，每次选择时可以选择任意一张还未被选中的牌。每个玩家只能选择奇数下标或偶数下标的牌，也就是说，第一个玩家只能选择奇数下标的牌，第二个玩家只能选择偶数下标的牌。两个玩家依次选择直到数组中所有的牌都被选中。每次选择时，被选择的牌的点数将被加入该玩家的得分。求第一个玩家的得分。

## 分析
我们可以从卡牌堆的末尾开始向前遍历。假设当前的卡牌编号为 $i$ ，我们需要根据这张卡牌的数值 $a[i]$ 作出决策。

- 若 $a[i]\le0$ ，说明这张卡牌是一个负数，对游戏得分没有影响，可以直接跳过。
- 若 $a[i]>0$ ，那么我们有两种选择：
  - 选择移除卡牌 $i$ ，并将其数值 $a[i]$ 加到当前的总得分 $sum$ 中。
  - 选择不移除卡牌 $i$ ，继续游戏。
  
那么我们需要找到一个合适的位置，使得在这个位置右边的卡牌不再有正数。如果找到了这样的位置，那么我们就可以选择结束游戏。否则，我们需要继续游戏。

由于只能选择奇数卡牌，所以我们可以确定一定会有偶数个卡牌留在卡堆中。因此，如果找到的位置是 $2$，那么我们就需要在移除卡牌 $i$ 和结束游戏两种决策中选择得分更高的那个。

## 实现
注意：本题必须开 ```long long``` 否则会溢出。
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int N = 1e6 + 10;

long long n, m;
long long a[N];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	long long fg = 3, sum = 0;
	for (int i = n; i >= 1; i--) {
		if (a[i] <= 0) continue;
		fg = i;
		sum += a[i];
	}
	if (fg != 2) cout << sum << '\n';
	else {
		cout << max(-a[2], a[1]) + sum << '\n';
	}
}
int main() {
	long long T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

- 时间复杂度：遍历卡牌堆需要 $O(n)$ 的时间。因此，总的时间复杂度为 $O(n)$ 。
- 空间复杂度：使用了 $O(n)$ 的额外空间来存储卡牌的数值。


本题是一个贪心算法问题。通过从后向前遍历卡牌堆，根据卡牌的数值作出合适的决策，即可求得最大得分。

---

## 作者：_299817_ (赞：0)

## Part 1：主要思路
对于整个数列，我们可以发现一个性质，就是从第三位开始，任意一个数都可取到。

于是我们考虑从第三位开始取所有的正数，再特判第一位和第二位的所有情况中哪种情况可以取到的值最大。

时间复杂度 $O(n)$，记得开 `long long`。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#define sort stable_sort
#define int long long // 记得开 long long
#define map unordered_map
using namespace std;
typedef long long ll;

int T;
int n;
int a[200010];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        int ans = 0; // 记录答案
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(i >= 3 && a[i] > 0){ // 取从第三位开始的所有正数
                ans += a[i];
            }
        }
        if(n == 1){
            cout << max(0LL, a[1]) << endl; // 特判 n = 1 的情况
            continue;
        }
        cout << ans + max({0LL, a[1], a[1] + a[2]}) << endl; // 考虑前三位的所有情况
    }
    return 0;
}////d//d/dd//d/d/d/d
```


---

