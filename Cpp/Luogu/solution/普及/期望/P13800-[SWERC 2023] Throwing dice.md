# [SWERC 2023] Throwing dice

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a11e720cc14242ff598268192fbaaa26b9332c02.png)

:::

Alice and Bob are discussing penalty shoot-outs and their randomness: "We might as well be throwing dice to determine the winner!", Alice said. And so they started simulating penalty shoot-outs by each throwing dice, summing the points indicated on their dice, and comparing these sums. The player with the largest sum wins; in case both sums are equal, there is a tie.


But even in such situations, some player might have an edge over their opponent, depending on which dice they throw. Thus, just by looking at the dice they are about to throw, Alice and Bob want to determine who has the better edge.


Alice has $M$ fair dice, with $A_1, A_2, \dots, A_M$ sides. For all integers $k$ and $l$ such that $1 \leq k \leq M$ and $1 \leq l \leq A_k$, the $k^\text{th}$ die of Alice has a probability $1/A_k$ of showing its face numbered $l$. Then, Alice's score is the sum of the numbers displayed by her $M$ dice. Similarly, Bob has $N$ fair dice, with $B_1, B_2, \dots, B_N$ sides.


Given these dice, Alice has a probability $\mathbb{P}_A$ of having a strictly larger score than Bob, and Bob has a probability $\mathbb{P}_B$ of having a strictly larger score than Alice. Which probability is the largest one?


## 说明/提示

**Sample Explanation 1**

Since Alice has 8 dice, her score is always 8 or more; Bob's score is always 6 or less. Hence, Alice has a probability $\mathbb{P}_A = 100\%$ of beating Bob, and he has a probability $\mathbb{P}_B = 0\%$ of beating her. Consequently, $\mathbb{P}_A > \mathbb{P}_B$.

**Sample Explanation 2**

Alice has a probability $\mathbb{P}_A = 125/288$ of beating Bob; he also has a probability $\mathbb{P}_B = 125/288$ of beating her.

## 样例 #1

### 输入

```
8 1
4 4 4 4 4 4 4 4
6```

### 输出

```
ALICE```

## 样例 #2

### 输入

```
2 2
6 4
4 6```

### 输出

```
TIED```

# 题解

## 作者：Doraeman (赞：1)

## ~~闲聊~~
~~要是想预测 2022 年卡塔尔世界杯决赛阿根廷和法国的点球大战，应该怎么分配骰子啊？  
别的不说，光门神大马丁的实力就能给阿根廷加个 6 点的骰子。~~

## 期望值
期望值：在一个离散性随机变量试验中每次可能结果的概率乘以其结果的总和。  
换句话说，期望值是随机试验在同样的机会下重复多次的结果计算出的等同“期望”的平均值。

还是不懂？~~我也不懂~~！举个例子。  
例如，A 与 B 游戏，A 有 $2/3$ 的概率获胜，B 只有 $1/3$ 的概率获胜；但是每次 A 获胜从 B 那里得到 $1$ 元，每次 B 获胜从 A 那里得到 $3$ 元。  
虽然 A 更有概率获胜，但 A 每次游戏赚到的钱的期望值是 $\frac{2}{3}\times1+\frac{1}{3}\times(-3)=-\frac{1}{3}$，即平均每次游戏少 $\frac{1}{3}$ 元。 

期望值可以帮助我们反应整体的随机情况，也可以应用到本题中。

## 应用
- 如果 Alice 的所有骰子的点数的期望值更大，那么 Alice 获胜概率更大；
- 反之，如果 Bob 更大，那么 Bob 获胜概率更大；
- 最后，如果他们所有骰子的期望值相等，那么概率相等。

## 细节
需要注意的是，虽然无论怎么掷骰子都不会得到小数，但是**期望值可能是小数**（比如 $1\sim6$ 的公平骰子的点数期望值是 $3.5$）。  
所以判断相等时最好不要直接写 `==`，而是另写一个判断误差不超过某个特定值即为相等的函数。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

// 判断相等 
bool equal(double x, double y){
    return fabs(x-y) <= 1e-4;
}

int main(){
    int n, m; cin >> n >> m;
    // 计算期望值  
    double pa = 0, pb = 0;
    while(n--){
        int x; cin >> x;
        pa += (x + 1) / 2.0;
    }
    while(m--){
        int y; cin >> y;
        pb += (y + 1) / 2.0;
    }

    // 分情况 
    if(equal(pa, pb)) cout << "TIED";
    else if(pa > pb) cout << "ALICE";
    else cout << "BOB";
    
}
```

---

## 作者：xiaowenxu_qwq (赞：0)

# 题目意思
ALICE 和 BOB 分别有 $m$ 和 $n$ 个骰子，ALICE 的第 $i$ 骰子有 $a_i$ 面，BOB 的第 $i$ 骰子有 $b_i$ 面，所有骰子投完后谁的总点数大谁就获胜，问他们谁获胜的可能性更大。
# 思路
因为骰子是随机的，为了保证公平，我们计算每个骰子的平均点数，第 $i$ 个骰子的平均点数为 $\lfloor\frac{a_i+1}{2}\rfloor$，我们将两边所有骰子的平均点数相加并进行比较，输出总平均点数和大的一方的名字，如果平局则输出 TIDE。


AC 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}//快读
void write(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else write(x/10),putchar(x%10+'0');
}//快写
int a[100001],b[100001];
int cnta,cntb;
signed main()
{
	int m=read(),n=read();
    for(int i=1;i<=m;i++)a[i]=read(),cnta+=a[i];//ALICE点数和
    for(int i=1;i<=n;i++)b[i]=read(),cntb+=b[i];//BOB点数和
    if(m+cnta>n+cntb)printf("ALICE");
    else if(m+cnta<n+cntb)printf("BOB");
    else printf("TIED");
	return 0;
} 
```

---

## 作者：Crazyouth (赞：0)

## 分析

前言：这题本来要评绿的，但是这个结论过于简单了，所以评黄了。

不难发现两人赢的概率的大小关系和两人的期望和大小关系是一样的，注意到一个 $a_i$ 面骰子的期望点数是 $\frac{a_i(a_i+1)}{2a_i}$，所以比较 $\sum a+m$ 和 $\sum b+n$ 大小关系即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int n,m,sum1=0,sum2=0;
	cin>>m>>n;
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;
		sum1+=x+1;
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		sum2+=x+1;
	}
	cout<<(sum1<sum2?"BOB":(sum1==sum2?"TIED":"ALICE"));
}

---

