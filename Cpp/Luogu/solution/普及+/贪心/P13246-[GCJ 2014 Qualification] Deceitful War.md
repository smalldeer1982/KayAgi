# [GCJ 2014 Qualification] Deceitful War

## 题目背景

这是本轮比赛中最难理解的一道题。如果你是 Code Jam 的新手，建议先尝试解决其他题目。

## 题目描述

Naomi 和 Ken 有时会一起玩游戏。在每局游戏开始前，他们每人会获得 $N$ 块看起来完全一样的木块，质量在 $0.0\,\text{kg}$ 到 $1.0\,\text{kg}$ 之间（不包括端点）。所有木块的质量彼此不同。他们可以用这些木块玩许多种游戏，但他们通常玩的游戏叫作 **War**（战争）。War 的规则如下：

1. 每位玩家会称量自己所有木块的质量，因此他们都知道自己所有木块的重量，但不知道对方木块的重量。
2. 他们会重复进行以下过程共 $N$ 次：
    1. Naomi 选择她的一块木块，质量为 $\text{chosen}_{\text{Naomi}}$。
    2. Naomi 将这块木块的质量告诉 Ken。
    3. Ken 选择他的一块木块，质量为 $\text{chosen}_{\text{Ken}}$。
    4. 他们分别将自己的木块放在天平的两边，质量较大的那一方获得一分。
    5. 两块木块随后一同被焚毁。

Naomi 意识到了关于 War 的三件事。首先，她意识到自己经常输。其次，她意识到 Ken 有一个**唯一的**策略，可以在不假设 Naomi 策略的前提下最大化自己的得分，而 Ken 总是采用该策略。第三，她意识到自己讨厌输。因此 Naomi 决定不再玩 War，而是玩她自创的游戏，称为 **Deceitful War（欺诈战争）**。这个游戏的妙处在于，Ken 仍然以为他们在玩 War！

Deceitful War 的规则如下，区别于 War 的部分用**粗体**标出：

1. 每位玩家称量自己所有木块的质量。**Naomi 还会在 Ken 不注意时称量他的木块，因此 Naomi 知道所有木块的质量，而 Ken 只知道自己木块的质量。**
2. 他们会重复以下过程共 $N$ 次：
    1. Naomi 选择她的一块木块，质量为 $\text{chosen}_{\text{Naomi}}$。
    2. **Naomi 向 Ken 报出一个数 $\text{Told}_{\text{Naomi}}$，其值在 $0.0\,\text{kg}$ 到 $1.0\,\text{kg}$ 之间（不包括端点）。Ken 认为他们在玩 War，因此他会以为 Naomi 报的这个数就是她选择的木块的质量，即 $\text{chosen}_{\text{Naomi}}$。**
    3. Ken 选择他的一块木块，质量为 $\text{chosen}_{\text{Ken}}$。
    4. 他们将各自的木块放在天平两侧，质量较大的一方获得一分。
    5. 两块木块随后一同被焚毁。

Naomi 不希望 Ken 发现她实际上并没有在玩 War。因此，在选择要使用的木块及要告知 Ken 的质量时，她必须确保天平不会揭示出 $\text{Chosen}_{\text{Naomi}} \neq \text{Told}_{\text{Naomi}}$。换句话说，她的决策必须满足以下条件：

- 当且仅当 $\text{Chosen}_{\text{Naomi}} > \text{Chosen}_{\text{Ken}}$ 时，才有 $\text{Told}_{\text{Naomi}} > \text{Chosen}_{\text{Ken}}$；
- $\text{Told}_{\text{Naomi}}$ 不得与 Ken 的任意一块木块的质量相等，因为他知道那是不可能的。

你可能会觉得 Naomi 通过欺骗并不能获得更多分数，因为 Ken 可能会发现她不是在玩 War；但 Naomi 知道 Ken 相信双方都在玩 War，而她也知道 Ken 会始终采用他在 War 中的最优策略，因此 Naomi 能预测 Ken 的每一步行动。

你将获得 Naomi 和 Ken 最初的木块质量数据。Naomi 将使用 Deceitful War 的最优策略来获得尽可能多的分数；Ken 将使用 War 的最优策略（假设双方都在玩 War）来获得尽可能多的分数。你的任务是计算：

- 如果 Naomi 玩的是 Deceitful War，她最多能获得多少分？
- 如果 Naomi 玩的是 War，采用最优策略，她最多能获得多少分？

**示例说明**

如果每位玩家只剩下一块木块，Naomi 的质量是 $0.5\,\text{kg}$，Ken 的质量是 $0.6\,\text{kg}$，那么 Ken 保证得分。Naomi 无法声称她的木块质量是 $\geq 0.6\,\text{kg}$，否则当天平显示 Ken 的木块更重时，Ken 会发现她没有在玩 War。

如果每位玩家还剩两块木块，Naomi 拥有 $[0.7\,\text{kg}, 0.2\,\text{kg}]$，Ken 拥有 $[0.8\,\text{kg}, 0.3\,\text{kg}]$，那么 Naomi 可以选择她的 $0.2\,\text{kg}$ 木块，并对 Ken 谎称其质量是 $0.6\,\text{kg}$。Ken 会误以为 Naomi 说的是真话（因为他以为他们在玩 War），于是他会选择他的 $0.8\,\text{kg}$ 木块来争取得分。Ken 的确得了一分，却没有意识到自己被骗了，因为天平确实显示他的木块更重。接下来 Naomi 可以使用她的 $0.7\,\text{kg}$ 木块，并如实告诉 Ken，它的质量是 $0.7\,\text{kg}$，从而赢得该轮得分。

若 Naomi 此前没有欺骗，而是一直玩 War，那么 Ken 会赢得两分，Naomi 将一分未得。

## 说明/提示

**限制条件**

- $1 \leq T \leq 50$；
- 所有 Naomi 和 Ken 的木块质量彼此不同，且位于 $0.0$ 与 $1.0$ 之间（不包括端点）。

**小数据集**

- 时间限制：~~60~~ 3 秒；
- $1 \leq N \leq 10$。

**大数据集**

- 时间限制：~~120~~ 5 秒；
- $1 \leq N \leq 1000$。

翻译由 ChatGPT-4o 完成。

## 样例 #1

### 输入

```
4
1
0.5
0.6
2
0.7 0.2
0.8 0.3
3
0.5 0.1 0.9
0.6 0.4 0.3
9
0.186 0.389 0.907 0.832 0.959 0.557 0.300 0.992 0.899
0.916 0.728 0.271 0.520 0.700 0.521 0.215 0.341 0.458```

### 输出

```
Case #1: 0 0
Case #2: 1 0
Case #3: 2 1
Case #4: 8 4```

# 题解

## 作者：DecemberFox (赞：0)

# P13246 [GCJ 2014 Qualification] Deceitful War

## 题目分析
题目很长，简单来说，题目要求出 Naomi 在两场游戏（War 和 Deceitful War）中最多可以获得多少分。

首先 Naomi 和 Ken 两名玩家都有 $n$ 个质量都不相同的木块。其次，Naomi 和 Ken 都会按照最优且唯一的策略进行操作。

在游戏 War 中，Naomi 先选择一个自己的木块并告诉 Ken 这个木块的**真实**质量，随后 Ken 选择一个自己的木块与 Naomi 比大小，质量大者获胜，随后木块作废，不继续参与后面的游戏。

游戏 War 显然不公平，于是 Naomi 可以欺骗 Ken，即**谎报**自己木块的质量，称为 Deceitful War。为了不被 Ken 发现 Naomi 谎报，称量的实际结果必须符合 Naomi 所说的质量大小关系，且质量不能与其余 $2n-1$ 个木块质量相等。

## 解法分析
首先找到 Ken 的最优策略：**Ken 总会选取比 Naomi 木块质量更大的木块中，质量最小的一个；若没有，则选取质量最小的一个木块**。

### War
War 的情况较好分析，只需了解 Ken 的最优策略就可以判断。

只要 Naomi 选取的木块质量不比 Ken 手中最大的木块大，Ken 一定会获胜，直至 Naomi 在某一局中拥有的木块质量更大。

因此**按从大到小的顺序一一配对两者的木块，若 Naomi 质量最大的木块比 Ken 最大的大，此时 Naomi 一定可以获胜一轮；否则 Ken 获胜一轮**。

### Deceitful War
由于质量为一个 $(0,1)$ 的实数，对于任意一个质量 $m_0$ 的木块，总能找到一个 $m\in(0,1)$ 使得 $m>m_0$ 或 $m<m_0$，因此在欺骗的过程中可以不用管对方木块的质量。

Deceitful War 可以通过利用 Ken 的策略，Naomi 可以谎报自己质量较小的木块的质量，让 Ken 认为自己无法比过 Naomi 而出最小的木块，此时从实际和 Naomi 告诉 Ken 的信息表现相同。

因此**按从小到大的顺序一一配对两者的木块，若 Ken 质量最小的木块比 Ken 最小的大，此时 Ken 一定可以扳回一局；否则 Naomi 将会获胜**。

最终代码如下：
```cpp
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const int const1=1e3+10;
	double mn[const1],mk[const1];
	bool cmp(double a,double b)
	{
		return a>b;
	}
	void solve(int task)
	{
		int i,j,n,ws(0),dws(0);
		read(n);
		for(i=1;i<=n;++i) scanf("%lf",&mn[i]);
		for(i=1;i<=n;++i) scanf("%lf",&mk[i]);
		std::sort(mn+1,mn+n+1,cmp);
		std::sort(mk+1,mk+n+1,cmp);
		for(i=1,j=1;i<=n&&j<=n;)
		{
			if(mn[i]>mk[j]) ++ws,++i;
			if(mn[i]<mk[j]) ++i,++j;
		}
		for(i=n,j=n;j>=1&&i>=1;)
		{
			if(mn[i]>mk[j]) ++dws,--i,--j;
			if(mn[i]<mk[j]) --i;
		}
		printf("Case #%d: ",task);
		write(dws,' ',ws);
	}
}
int main()
{
	int t,tk(0);
	read(t);
	while(t--) SOLVE::solve(++tk);
	return 0;
}
```

---

