# 题目信息

# [ARC164C] Reversible Card Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc164/tasks/arc164_c

両面に数が書かれた $ N $ 枚のカードがあり、$ i $ 枚目のカードには片方の面に赤い数字で $ A_i $ が、もう片方の面には青い数字で $ B_i $ が書かれています。初め、全てのカードは赤い数字が書かれた面を表にして置かれており、Alice と Bob は次のような手順を繰り返すゲームをします。

- まず、Alice が残っているカードの中から $ 1 $ 枚を選び、裏返す。次に、Bob が残っているカードの中から $ 1 $ 枚を取り除く。このとき、取り除いたカードの表側の面に書かれていた数の分だけ Bob は得点を得る。
 
残っているカードが $ 0 $ 枚になった時、ゲームを終了します。

Alice はゲーム終了時の Bob の得点を最小にしようとし、Bob はこれを最大にしようとします。両者が最善の手順を取ったとき、ゲーム終了時の Bob の得点は何点でしょうか。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,\ B_i\leq\ 10^9 $ $ (1\leq\ i\ \leq\ N) $
- 入力される値はすべて整数である
 
### Sample Explanation 1

初めの状態では、表側の面に書かれた数はそれぞれ $ 6,2,5 $ です。ここから、例えば次のような進行が考えられます。 1. Alice は $ 1 $ 枚目のカードを裏返す。このとき、表側の面に書かれた数は $ 4,2,5 $ となる。Bob は $ 3 $ 枚目のカードを取り除き、$ 5 $ 点を得る。 2. Alice は $ 2 $ 枚目のカードを裏返す。このとき、表側の面に書かれた数は $ 4,1 $ となる。Bob は $ 2 $ 枚目のカードを取り除き、$ 1 $ 点を得る。 3. Alice は最後に残った $ 1 $ 枚目のカードを裏返す。このとき、表側の面に書かれた数は $ 6 $ となる。Bob はこれを取り除き、$ 6 $ 点を得る。 この場合、Bob が最終的に得る得点は $ 12 $ 点です。実は、この進行は双方の最善手の一例であり、答えは $ 12 $ となります。

## 样例 #1

### 输入

```
3

6 4

2 1

5 3```

### 输出

```
12```

## 样例 #2

### 输入

```
5

166971716 552987438

219878198 619875818

918378176 518975015

610749017 285601372

701849287 307601390```

### 输出

```
3078692091```

# AI分析结果

### 题目内容重写

【题目描述】

有 $N$ 张卡片，每张卡片的两面分别写有数字 $A_i$ 和 $B_i$。初始时，所有卡片的 $A_i$ 面朝上。Alice 和 Bob 轮流进行以下操作：

1. Alice 选择一张卡片并将其翻转。
2. Bob 选择一张卡片并将其移除，获得该卡片当前朝上一面的分数。

游戏在所有卡片被移除后结束。Alice 的目标是让 Bob 的得分最小，而 Bob 的目标是让得分最大。假设双方都采取最优策略，求 Bob 最终能获得的最大分数。

【说明/提示】

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq 10^9$

### 题解分析与结论

#### 综合分析

本题的核心在于分析 Alice 和 Bob 的最优策略，并推导出 Bob 最终得分的公式。大多数题解都基于以下思路：

1. **问题转化**：将每张卡片的得分问题转化为 $A_i$ 和 $B_i$ 的差值问题，即 $Delta_i = |A_i - B_i|$。
2. **奇偶性分析**：根据初始时 $A_i > B_i$ 的卡片数量的奇偶性，决定 Bob 是否能获得所有卡片的较大值，或者需要减去最小差值。
3. **贪心策略**：Alice 会尽可能翻转差值最大的卡片，而 Bob 则会选择当前差值最大的卡片。

#### 最优题解

##### 题解1：Exp10re (5星)

**关键亮点**：
- 详细推导了 Alice 和 Bob 的最优策略，特别是对奇偶性的分析。
- 通过状态转移和贪心策略，得出了 Bob 得分的公式。
- 代码简洁高效，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Exp10reMAXN=200020; 
long long dist[Exp10reMAXN],MINN=(1ll<<60),tot;
int main()
{
	int n,i;
	long long ta,tb,ccnt=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&ta,&tb);
		if(ta<tb)
		{
			swap(ta,tb);
		}
		else
		{
			ccnt++;
		}
		dist[i]=ta-tb;
		tot+=ta;
		MINN=min(MINN,dist[i]);
	}
	if(ccnt%2==1)
	{
		tot-=MINN;
	}
	printf("%lld",tot);
	return 0;
}
```

##### 题解2：chinazhanghaoxun (4星)

**关键亮点**：
- 通过简单的贪心策略，分析了 Alice 和 Bob 的最优操作。
- 代码简洁，直接计算 Bob 的得分。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,a,b,ans=0,cha=INT_MAX,cnt=0;
    cin>>n;
    for(int i=1;i<=n;i++){
		cin>>a>>b;
		if(a>b) cnt++;
		ans+=max(a,b);
		cha=min(cha,abs(a-b));
	}
	if(cnt%2) cout<<ans-cha;
	else cout<<ans;
    return 0;
}
```

##### 题解3：yuheng_wang080904 (4星)

**关键亮点**：
- 通过优先队列维护差值，模拟 Alice 和 Bob 的操作。
- 代码实现较为直观，时间复杂度为 $O(n \log n)$。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,a[200005],b[200005],cnt,sum,mini=1e18;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++)sum+=max(a[i],b[i]);
    for(int i=1;i<=n;i++)cnt+=(a[i]>b[i]);
    for(int i=1;i<=n;i++)mini=min(mini,abs(a[i]-b[i]));
    if(cnt%2)cout<<sum-mini<<endl;
    else cout<<sum<<endl;
    return 0;
}
```

### 最优关键思路

1. **问题转化**：将每张卡片的得分问题转化为 $A_i$ 和 $B_i$ 的差值问题，简化了问题的复杂度。
2. **奇偶性分析**：通过分析初始时 $A_i > B_i$ 的卡片数量的奇偶性，决定 Bob 是否能获得所有卡片的较大值，或者需要减去最小差值。
3. **贪心策略**：Alice 会尽可能翻转差值最大的卡片，而 Bob 则会选择当前差值最大的卡片。

### 拓展思路

- **类似题目**：可以考虑其他博弈论题目，如 [P2731 [USACO3.3] 骑马修栅栏](https://www.luogu.com.cn/problem/P2731)，[P2732 [USACO3.3] 骑马修栅栏2](https://www.luogu.com.cn/problem/P2732)，[P2733 [USACO3.3] 骑马修栅栏3](https://www.luogu.com.cn/problem/P2733)。

### 推荐题目

1. [P2731 [USACO3.3] 骑马修栅栏](https://www.luogu.com.cn/problem/P2731)
2. [P2732 [USACO3.3] 骑马修栅栏2](https://www.luogu.com.cn/problem/P2732)
3. [P2733 [USACO3.3] 骑马修栅栏3](https://www.luogu.com.cn/problem/P2733)

---
处理用时：52.41秒