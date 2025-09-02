# [BalticOI 2011] Meetings (Day2)

## 题目描述

拯救世界协会召集了他们的 $N$ 名成员参加紧急会议，以最终商定一个拯救世界的计划。为了在会议上达成共识，参与者按如下步骤进行：

1. 每个人都有一个提案，并花费 $P$ 分钟向其他人展示。
2. 在所有参与者完成展示后，他们会投票选出最佳提案，这需要 $V$ 分钟。

例如，如果每个提案需要一分钟（$P = 1$），投票也需要一分钟（$V = 1$），那么有 $100$ 名参与者的会议将在 $101$ 分钟内达成决议。为了加快整体决策过程，会议的参与者决定分成小组并行工作。每个小组使用上述程序选出自己的最佳提案。然后，各小组的代表会面，从每个小组投票选出的最佳提案中选出最终计划。例如，如果 $100$ 名参与者分成两个小组，分别为 $40$ 人和 $60$ 人，过程可能如下（同样，$P = V = 1$）：

- 较大组花费 $61$ 分钟选出他们的最佳提案；
- 较小组花费 $41$ 分钟做同样的事情，然后必须等待较大组完成；
- 然后两个小组的代表会面，花费 $2$ 分钟互相展示，$1$ 分钟投票。

因此，总共花费的时间是 $61 + 2 + 1 = 64$ 分钟。但小组可能会进一步分成子小组，有时分成两个以上的小组可能更有用。作为一个特例，一个成员的小组可以立即做出决定，因为不需要向自己展示自己的提案。编写一个程序，给定展示和投票时间 $P$ 和 $V$，计算出会议的 $N$ 名参与者在最优组织会议和小组情况下达成共识所需的最少时间。

## 说明/提示

**样例解释 1**

在样例 1 中，九个人应分成 3 组。每组应有 3 个人。

**数据范围**

对于 $40\%$ 的数据，$1 \le N \le 5000$。

对于 $70\%$ 的数据，$1 \le N \le 5 \times 10^4$。

对于所有数据，$1 \le N \le 10^{15},1 \le P,V \le 1000$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
9 1 1```

### 输出

```
8```

## 样例 #2

### 输入

```
6 1 2```

### 输出

```
8```

## 样例 #3

### 输入

```
6 2 1```

### 输出

```
12```

# 题解

## 作者：jockbutt (赞：4)

一种代码特别短的解法。

考虑到 $ p $ 和 $ v $ 都非常小，答案应该也不是很大。于是考虑枚举答案。

设当前枚举到的答案为 $ t$，用 $ f_t $ 表示所需的时间。可以得到转移方程式

$ f_t = \max (f_{t-v-i\times p}\times i) $

这样一直枚举，直到 $ f_t $ 大于 $ n $ 时停止。

最后测试了一下极限数据，最大也就十二万左右。

代码如下 ：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,p,v;
vector <int> f;
int t;
signed main(){
    cin>>n>>p>>v;
    f.push_back(1);
    while(f[t]<n)
    {
        f.push_back(f[t++]);
        for(int i=2;i<=(t-v)/p;++i)   f[t]=max(f[t],f[t-v-i*p]*i);
    }
    cout<<t<<endl;
    return 0;
}
```


---

## 作者：渔歌 (赞：3)

#### 挺巧妙的一道题
1.  我们先考虑将 n 个人分成 k 组怎样分最优。
	- 设 n 讨论时间为 $f(n)$
	- 一起讨论最终方案的时间为定值 v 。
	- 假设小组数目固定，所以每个小组分别讲述最佳方案的时间和为定值 kp 。
	- 小组同时进行讨论，那小组中讨论时间最长的内个就是总共的讨论时间，我们希望讨论时间最短，尽可能平均，根据鸽巢原理，最短时间为 $f(\left \lceil \frac{n}{k} \right \rceil)$ 。
	- 而小组数又可以变化，故得到公式：
$$
f(n)=v+\min(f(\left \lceil \frac{n}{k} \right \rceil)+k*p)
$$

2. 拿到这个式子便可用 DP (~~或者叫记忆化搜索~~ )，适当调常数可以再开个$O(2)$ 能拿到 70 pts 。 
3. 但 70pts 是肯定满足不了我们的。接下来要讲的解法不仅能 A 而且比 DP 代码要短。
	- 通过这个公式，我们可以把本题抽象成一棵树。
	- 根节点为 $f(n)$ ,下面连着 k 个$f(\left \lceil \frac{n}{k} \right \rceil)$ 节点，每个 $f(\left \lceil \frac{n}{k} \right \rceil)$ 再以此方式各自连着 $k_1$ 个节点·····最底下一层是 $f(1)$ 节点。
	- 设这棵树第 i 层的节点的出度为 $k_i$ ,共有 m 层。
	- 每一层中会产生 $k_i*p$ 的贡献 (同时进行) 加上每一层的必须贡献 v 。
	- 则答案为  $\min(\sum_{i=1}^m k_i*p+v*m)$ 。
	- 又因为最底下一层都是 $f(1)$ ，共有 n 个，叶子节点数目为定值 n ,则有 $\prod_{i=1}^m k_i \ge n$
	- 高中的同学们肯定都很熟悉了。这是一个**耐克函数** 。
	- (~~好家伙这道题从DP延伸到树又延伸到数学~~)
	- 我们枚举层数 m ，找最大的 k ,使得 $ pow(k,m)\le n$ ,换句话说，  $k=\left \lfloor pow(n,1/m) \right \rfloor$ ，然后更改一定的 k 变为  k+1 ,使得乘起来刚好大于 n ，取较小的。
	- P.S. 这个地方有个离谱的事情，用系统库函数 $pow(n,1/m)$ 的效率要高于二分+快速幂（后者 T 到和 DP 一个分数)， $pow$ 的效率我们姑且当做$O(\log n)$ 。总时间复杂度为 $O(\log n^2)$ 。

```cpp
	#include<cstdio>
	#include<cmath>
	#include<algorithm>
	#define int long long
	using namespace std;
	int n,p,v,ans=0x3f3f3f3f3f3f3f3f;
	signed main(){
		scanf("%lld%lld%lld",&n,&p,&v);
		int x,he,cnt1,cnt2;
		for(int m=1;;m++){
			x=pow(n,1.0/m);
			he=1;
			cnt1=m;//k的数目 
			cnt2=0;//k+1的数目 
			if(x==1){//x=1首先是死循环，其次是从1改到2就等价于只有2，肯定是枚举过了的 
				printf("%lld",ans);
				return 0;
			}
			he=pow(x,m);//乘积 
			while(he<n){
				he/=x;//更新部分x到x+1 
				he*=x+1;
				cnt1--;
				cnt2++;
			}
			ans=min(ans,m*v+cnt1*x*p+cnt2*(x+1)*p);//答案计算 
		}
	}
```


---

## 作者：YAOhc2012 (赞：1)

这个题真的是思路极其简单，而且代码及其好写，但你会觉得匪夷所思。

我们注意到 $1\le P,V\le 1000$。

那我们考虑动态规划，我们设 $dp_i$ 表示花费 $i$ 时间最多让 $dp_i$ 人选出最优方案。

那么转移方程怎么列呢？

我们可以枚举将 $dp_i$ 人分成多少份，假设分成 $k$ 份，那么每组最多有 $i-k\times P-V$ 的时间商讨，因为最后报方案是有 $k$ 组，每组要 $P$ 分钟，最后要花 $V$ 分钟决定。

所以 $dp_i=\max\limits_{k=1}^\frac{i-V}{P}dp_{i-P\times k-V}\times k$。

最后如果 $dp_i\ge n$，就直接退出。

这个代码时间复杂度看着很玄学，实际最大用时连 $2\times 10^5$ 都没到。

你以为这就完了，别急，还有证明。

我们可以花费 $10P+V$ 的代价将可商讨人数乘上十，而由于 $N\le10^{15}$，所以我们可以花费至多 $15\times(10P+V)\le1.65\times 10^5$ 的时间满足要求。

最终代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,p,v,dp[200005];
signed main()
{
    cin>>n>>p>>v;
    dp[0]=1;
    for(int i=1;;i++)
    {
        for(int j=1;j<=(i-v)/p;j++)dp[i]=max(dp[i],dp[i-v-j*p]*j);
        if(dp[i]>=n)
        {
            cout<<i;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：ZPB2011 (赞：1)

# Meetings

[题目传送门](https://www.luogu.com.cn/problem/P4669)。

## 思路

先看眼数据：$1\le P,V \le 1000$。

我们发现 $P,V$ 很小，然后~~看到标签里的枚举~~想到了以时间来枚举，一直枚举到大于 $n$ 结束。

定义一个数组 $f_{tim}$ 表示枚举到tim时需要的时间，于是我们得出转移方程：$f_{tim}=\max(f_{tim-v-i\times p}\times i)(2\le i \le \frac{tim - v}{p})$。

易错：
> 十年 OI 一场空，不开 `long long` 见祖宗。

## 代码

~~好短啊一共才18行。~~

```cpp
#include <iostream>
#include <vector>
#define ll long long//十年OI一场空，不开long long见祖宗。
using namespace std;

vector<ll> f;

int main() {
	ll n, p, v, tim = 0;
    cin >> n >> p >> v;
    f.push_back(1);
    while(f[tim] < n) {//暴力
        f.push_back(f[tim++]);
        for(int i = 2; i <= (tim - v) / p; i++) f[tim] = max(f[tim], f[tim - v - i * p] * i);
    }
    cout << tim << endl;
    return 0;
}
```

---

## 作者：yyz1005 (赞：1)

有一种脑筋急转弯的美。

首先考虑 $dp_t$ 表示时间 $t$ 内最多可供多少人讨论。

应有 $dp_t = \max\{dp_{t - i \cdot p +v} \cdot i\}$，$i \not= 1$。

看上去因为 $n \le 10^{15}$ 极不可做。

实际上要注意到这个式子有一点指数函数的意思。

由于 $v$ 相较于 $i \cdot p$ 可以忽略，考虑一个函数 $f(x)=f(x - k \cdot p) \cdot k$，取 $k=2$，应当注意到 $dp_x$ 远大于 $f(x)$，因为 $dp_x$ 要取所有 $k \not= 1$ 中的最大值。

此时 $f(x)=f(x-2p) \cdot 2$，该式的结果在 $x >> p$ 时远超 $f(x)=f(x-1) \cdot 2$。

若 $t$ 极大，$dp_t >> 2^t$，因此最后的结果一定不会极大。

所以直接枚举 $t$ 是可以通过的。

[Code](https://www.luogu.com.cn/paste/a0s9jzjc)

---

