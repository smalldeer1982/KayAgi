# 题目信息

# Salyg1n and the MEX Game

## 题目描述

This is an interactive problem!

salyg1n gave Alice a set $ S $ of $ n $ distinct integers $ s_1, s_2, \ldots, s_n $ ( $ 0 \leq s_i \leq 10^9 $ ). Alice decided to play a game with this set against Bob. The rules of the game are as follows:

- Players take turns, with Alice going first.
- In one move, Alice adds one number $ x $ ( $ 0 \leq x \leq 10^9 $ ) to the set $ S $ . The set $ S $ must not contain the number $ x $ at the time of the move.
- In one move, Bob removes one number $ y $ from the set $ S $ . The set $ S $ must contain the number $ y $ at the time of the move. Additionally, the number $ y $ must be strictly smaller than the last number added by Alice.
- The game ends when Bob cannot make a move or after $ 2 \cdot n + 1 $ moves (in which case Alice's move will be the last one).
- The result of the game is $ \operatorname{MEX}\dagger(S) $ ( $ S $ at the end of the game).
- Alice aims to maximize the result, while Bob aims to minimize it.

Let $ R $ be the result when both players play optimally. In this problem, you play as Alice against the jury program playing as Bob. Your task is to implement a strategy for Alice such that the result of the game is always at least $ R $ .

 $ \dagger $ $ \operatorname{MEX} $ of a set of integers $ c_1, c_2, \ldots, c_k $ is defined as the smallest non-negative integer $ x $ which does not occur in the set $ c $ . For example, $ \operatorname{MEX}(\{0, 1, 2, 4\}) $ $ = $ $ 3 $ .

## 说明/提示

In the first test case, the set $ S $ changed as follows:

{ $ 1, 2, 3, 5, 7 $ } $ \to $ { $ 1, 2, 3, 5, 7, 8 $ } $ \to $ { $ 1, 2, 3, 5, 8 $ } $ \to $ { $ 1, 2, 3, 5, 8, 57 $ } $ \to $ { $ 1, 2, 3, 8, 57 $ } $ \to $ { $ 0, 1, 2, 3, 8, 57 $ }. In the end of the game, $ \operatorname{MEX}(S) = 4 $ , $ R = 4 $ .

In the second test case, the set $ S $ changed as follows:

{ $ 0, 1, 2 $ } $ \to $ { $ 0, 1, 2, 3 $ } $ \to $ { $ 1, 2, 3 $ } $ \to $ { $ 0, 1, 2, 3 $ }. In the end of the game, $ \operatorname{MEX}(S) = 4 $ , $ R = 4 $ .

In the third test case, the set $ S $ changed as follows:

{ $ 5, 7, 57 $ } $ \to $ { $ 0, 5, 7, 57 $ }. In the end of the game, $ \operatorname{MEX}(S) = 1 $ , $ R = 1 $ .

## 样例 #1

### 输入

```
3
5
1 2 3 5 7

7

5

-1

3
0 1 2

0

-1

3
5 7 57

-1```

### 输出

```
8

57

0

3

0

0```

# AI分析结果

### 题目内容重写

#### Salyg1n 和 MEX 游戏

**题目描述**

这是一个交互题！

salyg1n 给 Alice 一个包含 $n$ 个不同整数的集合 $S$，元素为 $s_1, s_2, \ldots, s_n$（$0 \leq s_i \leq 10^9$）。Alice 决定用这个集合与 Bob 玩一个游戏。游戏规则如下：

- 玩家轮流操作，Alice 先手。
- Alice 每次操作可以向集合 $S$ 中添加一个数 $x$（$0 \leq x \leq 10^9$），且集合 $S$ 中不能包含 $x$。
- Bob 每次操作可以从集合 $S$ 中移除一个数 $y$，且集合 $S$ 中必须包含 $y$。此外，$y$ 必须严格小于 Alice 上一次添加的数。
- 游戏在 Bob 无法操作或进行了 $2 \cdot n + 1$ 次操作后结束（此时 Alice 的操作将是最后一次）。
- 游戏的结果是最终集合 $S$ 的 $\operatorname{MEX}\dagger(S)$。
- Alice 的目标是最大化结果，而 Bob 的目标是最小化结果。

设 $R$ 为双方都采取最优策略时的结果。在这个问题中，你扮演 Alice，与扮演 Bob 的裁判程序对抗。你的任务是实现 Alice 的策略，使得游戏的结果至少为 $R$。

$\dagger$ $\operatorname{MEX}$ 定义为一个整数集合 $c_1, c_2, \ldots, c_k$ 中未出现的最小非负整数。例如，$\operatorname{MEX}(\{0, 1, 2, 4\}) = 3$。

**说明/提示**

在第一个测试用例中，集合 $S$ 的变化如下：

$\{1, 2, 3, 5, 7\} \to \{1, 2, 3, 5, 7, 8\} \to \{1, 2, 3, 5, 8\} \to \{1, 2, 3, 5, 8, 57\} \to \{1, 2, 3, 8, 57\} \to \{0, 1, 2, 3, 8, 57\}$。游戏结束时，$\operatorname{MEX}(S) = 4$，$R = 4$。

在第二个测试用例中，集合 $S$ 的变化如下：

$\{0, 1, 2\} \to \{0, 1, 2, 3\} \to \{1, 2, 3\} \to \{0, 1, 2, 3\}$。游戏结束时，$\operatorname{MEX}(S) = 4$，$R = 4$。

在第三个测试用例中，集合 $S$ 的变化如下：

$\{5, 7, 57\} \to \{0, 5, 7, 57\}$。游戏结束时，$\operatorname{MEX}(S) = 1$，$R = 1$。

**样例 #1**

**输入**

```
3
5
1 2 3 5 7

7

5

-1

3
0 1 2

0

-1

3
5 7 57

-1
```

**输出**

```
8

57

0

3

0

0
```

### 算法分类

**贪心**

### 题解分析与结论

该题的核心是通过贪心策略来最大化集合的 MEX 值。Alice 的目标是每次添加当前集合中缺失的最小非负整数（即 MEX），而 Bob 则会移除一个小于 Alice 上次添加的数的元素。通过这种策略，Alice 可以确保最终的 MEX 值尽可能大。

### 精选题解

#### 题解 1：作者：One_JuRuo (赞：2)

**星级：4**

**关键亮点：**
- 提出每次添加当前集合中缺失的最小非负整数的策略。
- 通过分析 Bob 的操作，证明了该策略的最优性。
- 代码简洁，直接实现了该策略。

**个人心得：**
- 作者在赛时由于使用了 `set` 导致 TLE，赛后优化了代码，避免了不必要的复杂度。

**核心代码：**
```cpp
int T,n,a,p;
set<int>s;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cin>>n,s.clear();
		for(int i=1;i<=n;++i) cin>>a,s.insert(a);
		for(int i=0;i<=100000;++i) if(!s.count(i)){p=i;break;}
		while(1)
		{
			cout<<p<<endl;
			cin>>a;
			if(a==-1||a==-2) break;
			p=a;
		}
	}
	return 0;
}
```

#### 题解 2：作者：Natori (赞：1)

**星级：4**

**关键亮点：**
- 详细分析了 Alice 和 Bob 的操作对 MEX 值的影响。
- 提出 Alice 第一次操作应添加当前集合的 MEX 值，之后每次添加 Bob 移除的数。
- 代码清晰，逻辑严谨。

**核心代码：**
```cpp
int T,n,a,p;
set<int>s;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cin>>n,s.clear();
		for(int i=1;i<=n;++i) cin>>a,s.insert(a);
		for(int i=0;i<=100000;++i) if(!s.count(i)){p=i;break;}
		while(1)
		{
			cout<<p<<endl;
			cin>>a;
			if(a==-1||a==-2) break;
			p=a;
		}
	}
	return 0;
}
```

#### 题解 3：作者：Wunsch (赞：1)

**星级：4**

**关键亮点：**
- 提出 Alice 应始终添加当前集合的 MEX 值，以最大化最终结果。
- 通过分析 Bob 的操作，证明了该策略的有效性。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
#include"iostream"
#define ll long long
using namespace std;

ll rd(){ll x=0,w=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}while(c<='9'&&c>='0'){x=x*10+(c-'0');c=getchar();}return x*w;}

ll T=rd();

ll n;
ll len;
ll ac[100005];
namespace Wunsch{

    void work(){
        n=rd();
        ll qaq=-1;
        f(i,0,n-1){
            i[ac]=rd();
            if(qaq==-1&&i[ac]!=i){
                qaq=i;
            }
        }
        if(qaq==-1)qaq=n;
        printf("%lld\n",qaq);
        fflush(stdout);
        while(1){
            ll y=rd();
            if(y==-1)break;
            printf("%lld\n",y);
            fflush(stdout);
        }
        return ;
    }

    bool main(){
        while(T--){
            work();
        }
        return 1;
    }

}

bool ztt=Wunsch::main();

main(){;}
```

### 最优关键思路

Alice 应始终添加当前集合中缺失的最小非负整数（即 MEX 值），以最大化最终的 MEX 值。Bob 每次移除一个小于 Alice 上次添加的数的元素，Alice 可以通过添加 Bob 移除的数来抵消 Bob 的操作，从而确保最终的 MEX 值不会减小。

### 拓展思路

该题的策略可以应用于类似的交互题中，特别是在需要最大化或最小化某个指标的情况下。通过分析对手的操作，可以设计出最优的策略来达到目标。

### 推荐题目

1. [CF1867C Salyg1n and the MEX Game](https://www.luogu.com.cn/problem/CF1867C)
2. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

---
处理用时：49.04秒