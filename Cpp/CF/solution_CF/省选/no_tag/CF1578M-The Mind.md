# The Mind

## 题目描述

This is an interactive problem.

In this problem, you need to come up with a strategy for a cooperative game. This game is played by two players. Each player receives 5 cards. Each card has a random integer between 1 and 100 on it. It is guaranteed that all numbers on cards are distinct.

The goal of the game is to play a card with a minimal number on it out of all 10 cards dealt to the players before any other card. The problem is that each player can only see their own cards and cannot communicate with another player in any way.

The game consists of 5 turns. During each turn, players simultaneously make a move. Each player can either play their smallest card or do nothing. If on some turn the smallest card is played, and no other card is played on or before that turn, players win. If two cards are played at the same turn or if after all 5 turns, no card is still played, players lose.

Players cannot communicate, so a strategy for the game should only be based on 5 cards that the player has. You can describe a strategy as five numbers $ 0.0 \le p_i \le 1.0, \sum_{i=1}^{5}p_i \le 1 $ , where $ p_i $ — the probability of playing the player's smallest card in their hand on $ i $ -th turn. If you know the cards dealt to the players, and the strategies that players choose, you can compute the probability of winning by a simple formula.

You will be given $ n=1000 $ randomly generated hands of 5 cards. You need to generate a strategy for each of the hands to maximize the probability of winning. After the judge program receives all $ n $ strategies, it generates all possible valid pairs of those hands (pairs which have the same numbers are discarded), and computes a probability of winning based on two strategies provided by your program.

To ensure that answers for different hands are independent, you must output a strategy for a hand and flush the standard output before reading information about the next hand.

If the average probability of winning a game is more than 85% over all valid pairs of hands, the test is considered passed. This problem contains the sample test and $ 20 $ randomly generated tests with $ n = 1000 $ .

## 说明/提示

In the example test there is only one valid pair of hands. The winning probability for the example output is equal to $ 0.8 + 0.2 \cdot (1 - 0.2) = 0.96 $ . Also note that the second player will not play a card at all with probability 0.1.

## 样例 #1

### 输入

```
2
2 12 27 71 100

22 29 39 68 90```

### 输出

```
0.8 0.2 0.0 0.0 0.0 

0.0 0.2 0.2 0.2 0.3```

# 题解

## 作者：Reanap (赞：2)

大概找到了这道题目的正确打开方式。

假设我们有 $100$ 轮该怎么做？

显然，$i$ 在第 $i$ 轮打出，可以保证 $100\%$ 胜率。

但我们只有 $5$ 轮。

考虑最小值出现在每个位置的概率。

我们把 $100$ 划分为 $6$ 段，最小值在第 i 端就在第 i 轮打出。

所以希望每段的最小值出现概率和相等，这样子我们获胜的概率大概可以做到 $\frac{5}{6}$。

出去不合法的情况可以让概率稍稍提升，压着 $85\%$ 的线过。

讲一下怎么分为 $6$ 段。其实由于保证纯随机，所以随机 $1000$ 组统计一下每个位置的频率就好了，均分频率就好了。

```cpp
int x[] = {0 , 4 , 8 , 14 , 20 , 34 , 100};

int main() {
	int n;
	read(n);
	for (int i = 1; i <= n; ++i) {
		int a[10] = {};
		for (int j = 1; j <= 5; ++j) cin >> a[j];
		for (int j = 1; j <= 5; ++j) {
			if(a[1] > x[j - 1] && a[1] <= x[j]) cout << "1.0 ";
			else cout << "0.0 ";
		}
		cout << endl;
	}
	return 0;
} 
```

---

