# Nene and the Card Game

## 题目描述

You and Nene are playing a card game. The deck with $ 2n $ cards is used to play this game. Each card has an integer from $ 1 $ to $ n $ on it, and each of integers $ 1 $ through $ n $ appears exactly on $ 2 $ cards. Additionally, there is a table where cards are placed during the game (initially, the table is empty).

In the beginning of the game, these $ 2n $ cards are distributed between you and Nene so that each player receives $ n $ cards.

After it, you and Nene alternatively take $ 2n $ turns, i.e. each person takes $ n $ turns, starting with you. On each turn:

- The player whose turn is it selects one of the cards in his hand. Let $ x $ be the number on it.
- The player whose turn is it receives $ 1 $ point if there is already a card with the integer $ x $ on the table (otherwise, he receives no points). After it, he places the selected card with the integer $ x $ on the table.

Note that turns are made publicly: each player can see all the cards on the table at each moment.

Nene is very smart so she always selects cards optimally in order to maximize her score in the end of the game (after $ 2n $ rounds). If she has several optimal moves, she selects the move that minimizes your score in the end of the game.

More formally, Nene always takes turns optimally in order to maximize her score in the end of the game in the first place and to minimize your score in the end of the game in the second place.

Assuming that the cards are already distributed and cards in your hand have integers $ a_1, a_2, \ldots, a_n $ written on them, what is the maximum number of points you can get by taking your turns optimally?

## 说明/提示

In the first test case, the integers written on your cards are $ 1 $ , $ 1 $ , $ 2 $ and $ 3 $ . The integers written on Nene's cards are $ 2 $ , $ 3 $ , $ 4 $ and $ 4 $ . The game may proceed as follows:

1. You select one of the cards with an integer $ 1 $ written on it and place it on the table.
2. Nene selects one of the cards with an integer $ 4 $ written on it and places it on the table.
3. You select the card with an integer $ 1 $ written on it, receive $ 1 $ point, and place the selected card on the table.
4. Nene selects the card with an integer $ 4 $ written on it, receive $ 1 $ point, and places the selected card on the table.
5. You select the card with an integer $ 2 $ written on it and place it on the table.
6. Nene selects the card with an integer $ 2 $ written on it, receive $ 1 $ point, and places the selected card on the table.
7. You select the card with an integer $ 3 $ written on it and place it on the table.
8. Nene selects the card with an integer $ 3 $ written on it, receive $ 1 $ point, and places the selected card on the table.

At the end of the game, you scored $ 1 $ point, and Nene scored $ 3 $ . It can be shown that you cannot score more than $ 1 $ point if Nene plays optimally, so the answer is $ 1 $ .

In the second test case, if both players play optimally, you score $ 2 $ points and Nene scores $ 6 $ points.

## 样例 #1

### 输入

```
5
4
1 1 2 3
8
7 4 1 2 8 8 5 5
8
7 1 4 5 3 4 2 6
3
1 2 3
1
1```

### 输出

```
1
2
1
0
0```

# 题解

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF1956B Nene and the Card Game](https://www.luogu.com.cn/problem/CF1956B)

## 题意简述

一副牌有 $1\sim n$ 各 $2$ 张，分给 $2$ 名玩家并轮流出牌。当桌上有相同牌时能获得 $1$ 分，求最优策略下先手的最大得分。

## 解题思路

每种牌各有 $2$ 张，有两种情况：

- 对子：$2$ 张牌都在同一名玩家手里，无论如何迟早会得分。
- 单牌：双方各有 $1$ 张，后出牌的玩家会得分。

对于每一回合，分类讨论：

- 若先手出对子，后手也出对子（双方的对子数量相同）。
- 若先手出单牌，后手出对应的单牌。

不难发现先手在单牌中无法得分，所以先手的最终得分为先手牌中的对子数量。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=200005;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int t;
			cin>>t;
			a[t]++;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==2)ans++;
		}
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++)a[i]=0;
	}
	return 0;
}
```

---

## 作者：roumeideclown (赞：1)

## 解法分析

对于一个数 $x$ 对应的 $2$ 张牌，存在 $3$ 种状态：

1. 都在玩家手中；
2. 都在 Nene 手中；
3. 一张在玩家手中，另一张在 Nene 手中。

对于第 $2$ 种状态，显然玩家无法得分；

对于第 $3$ 种状态，由于玩家先手，于是 Nene 的最佳策略为：当玩家打出写有 $x$ 的牌之后打出同一张牌，此时玩家无法得分；

因此，只有状态 $1$ 玩家可以得分。

## 代码实现

用数组 $a_i$ 存储牌 $i$ 在玩家手中出现的次数，最后输出值为 $2$ 的 $a_i$ 的个数即为玩家所得分数。

## 示例代码

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2)
using namespace std;
int n,a[200005],ans;
void play() {
	memset(a,0,sizeof(a)); //初始化
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;i++) {
		scanf("%d",&x);
		a[x]++; //统计x出现的次数
	}
	ans=0;
	for(int i=1;i<=n;i++) {
		if(a[i]==2) { //若某数出现两次则答案加1
			ans++;
		}
	}
	printf("%d\n",ans);
}
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0);
//  cout.tie(0);
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) {
		play();
	}
	return 0;
}

```

---

## 作者：cosf (赞：0)

我们可以将 $1$ 到 $n$ 的数字分三类：

1. 两张都在自己这里的数。
2. 一张在自己这里，一张在对方。
3. 两张都在对方。

显然第一类牌和第三类牌的数量一样多。

对方不想让你拿分，那她一定会先打第三类牌。你打第二类牌，就是给对方送分，你肯定不愿意做。

综合一下，策略就是：先打两张都是自己的牌，打完后，如果桌子上存在你有的牌，那你就把你的那张打出去。

不过，由于你是先手，所以打完第一类牌后桌面上不可能有同时也在你手牌中的第二类牌，这也就说明答案就是第一类牌的个数。

---

## 作者：ztrztr (赞：0)

## 前言
题目算比较简单的思维题目，很符合 CF 的出题特点。
## 题目大意
现在有 $1$ 到 $n$ 的牌每个两张。你现在有 $n$ 张，并且在输入中给出。另一个人有剩下的 $n$ 张牌。

你和那个人进行一个游戏：

1. 两人轮流。你先手，另一个人后手。一共进行 $2 \times n$ 轮。
2. 每轮的那个人需要出一张牌。
3. 如果那张牌上的数字是之前出过的，那么这个人的一分，否则不得分。
4. 牌出完后就扔掉，无论你有没有得分。

注意每个人都可以看见出过的牌。
## 思路
我们假设第一个人有 $s$ 对相同的牌。

那么这个人就有 $n - 2s$ 张不成对的牌。

那么你也有 $n - 2s$ 张不成对的牌。

所以你有 $\frac{n - (n - 2s)}{2} = s$ 对相同的牌。（修正了一下楼上的题解）。

我们发现两个人有着相同多对的牌，所以我们可以发现一个这样的后手必胜策略：

1. 两个人都把对子出完，两个人各得 $s$ 分。
2. 由于现在两个人的牌都是完全一样的了，所以每次先手出了一张牌的时候，后手就可以出相同的牌，这样后手就得分了。

所以，在两个人都极其聪明的情况下，最后的得分是：

先手 $s$ 分，后手 $n-2s+s=n-s$ 分。

由于 $s$ 一定小于 $n$ 的一半，所以答案只用输出 $s$ 就行了。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
int a[200005];
int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T --) {
        int n; cin >> n;
        for (int i = 1; i <= n; i ++) cin >> a[i];
        sort(a + 1, a + n + 1);
        int same = 0;
        for (int i = 1; i <= n; i ++) if (a[i] == a[i - 1]) same ++;
        cout << same << "\n";
    }
    return 0;
}
```

AC 记录：<https://codeforces.com/contest/1956/submission/256619999>。

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1956B)

## 思路

- 如果我们想让先手取得最大的得分，那么最优的策略就是**这两个人先将自己手里所有有两张数字相同的牌出完**，然后此时肯定还是先手先出，此时**先手不会得到任何分数**。

- 因此我们只需要寻找先手的牌中，出现过两次的数的个数即可。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5;

unordered_map<int, int> mp;

int main(){
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		mp.clear();
		for(int i = 1; i <= n; i++){
			int x;
			cin >> x;
			mp[x]++;//统计出现个数。
		}
		int ans = 0;
		for(auto i : mp){
			if(i.second == 2) ans++;//出现过两次。
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1956B
## 题意
你现在玩一个游戏，有 $2n$ 张扑克牌，点数为 $1$ 到 $n$，且每种点数各有两张。你是先手，当出的牌的点数已经出过了，那么出牌者加一分。问在最优策略下，你获得的最大分数。
## 思路
本题可以找规律。我们可以发现最优策略肯定是先出有两张数字相同的扑克牌，这样就能每次得到一分。假设我们手上有 $x$ 个对子，那么我们就可以获得 $x$ 分。

因为都按照最优方案出牌，所以对方肯定先出对子。对方的对子数量为 $\frac{n-(n-2p)}{2}=p$ 个（总共的对子减去双方都有的牌再除二）。然后双方对子都出完了，因为我们是先手，后面我们出一张，对方肯定能出一样的，所以我们不能再获得分数。

综上所述，我们的分数为我们牌对子的数量。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		int ans=0;
		for(int i=1;i<n;i++){
			if(a[i]==a[i+1])ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：破壁人罗辑 (赞：0)

## 题意简述

总共有 $2n$ 张牌，牌上的数字为 $1,2,\cdots,n$ 并且每个数字出现且仅出现两次。如果一人出牌时出的牌编号为 $k$ 且之前两人中有任意一人已经出过编号为 $k$ 的牌，则出牌者得一分。给出先手出牌者手上的牌，求双方都采用最佳策略的情况下先手能得到的最大分值。

## 解题思路

最优策略一定是把自己手中存在数字相同的牌先各出一张，然后若桌上有牌和自己手上的牌数字相同则出此牌，否则任意出一张牌。

如果双方都采用这种策略，假如先手存在 $p$ 个对子（两张编号相同的牌），那么后手持有的对子数量为 $n-(n-2p)-p=p$，和先手对子数量相同，则双方都会先在前 $4p$ 轮出牌中把对子出完，双方各得 $p$ 分，此时双方手中的牌完全相同，留到原先的先手先出牌，先手任出一张牌都可以让后手出同样的牌得分，而先手此时无法得分。

所以只需要统计牌中的对子数量输出即可。

## AC 代码

### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200000];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,p=0;scanf("%d",&n);
		for(int i=0;i<n;i++)scanf("%d",a+i);
		sort(a,a+n);
		for(int i=1;i<n;i++)if(a[i]==a[i-1]){p++;i++;}
		printf("%d\n",p);
	}
	return 0;
}
```

### Python
```python
T=int(input())
for t in range(T):
    d=dict()
    input()
    a=input().split()
    ans=0
    for i in a:
        if i in d:
            ans=ans+1
        else:
            d.setdefault(i,1)
    print(ans)
```

---

