# Sweets Eating

## 题目描述

Tsumugi brought $ n $ delicious sweets to the Light Music Club. They are numbered from $ 1 $ to $ n $ , where the $ i $ -th sweet has a sugar concentration described by an integer $ a_i $ .

Yui loves sweets, but she can eat at most $ m $ sweets each day for health reasons.

Days are $ 1 $ -indexed (numbered $ 1, 2, 3, \ldots $ ). Eating the sweet $ i $ at the $ d $ -th day will cause a sugar penalty of $ (d \cdot a_i) $ , as sweets become more sugary with time. A sweet can be eaten at most once.

The total sugar penalty will be the sum of the individual penalties of each sweet eaten.

Suppose that Yui chooses exactly $ k $ sweets, and eats them in any order she wants. What is the minimum total sugar penalty she can get?

Since Yui is an undecided girl, she wants you to answer this question for every value of $ k $ between $ 1 $ and $ n $ .

## 说明/提示

Let's analyze the answer for $ k = 5 $ in the first example. Here is one of the possible ways to eat $ 5 $ sweets that minimize total sugar penalty:

- Day $ 1 $ : sweets $ 1 $ and $ 4 $
- Day $ 2 $ : sweets $ 5 $ and $ 3 $
- Day $ 3 $ : sweet $ 6 $

Total penalty is $ 1 \cdot a_1 + 1 \cdot a_4 + 2 \cdot a_5 + 2 \cdot a_3 + 3 \cdot a_6 = 6 + 4 + 8 + 6 + 6 = 30 $ . We can prove that it's the minimum total sugar penalty Yui can achieve if she eats $ 5 $ sweets, hence $ x_5 = 30 $ .

## 样例 #1

### 输入

```
9 2
6 19 3 4 4 2 6 7 8
```

### 输出

```
2 5 11 18 30 43 62 83 121
```

## 样例 #2

### 输入

```
1 1
7
```

### 输出

```
7
```

# 题解

## 作者：TheOnlyMan (赞：6)

## 题意
题目的意思是说当取 $k$ 个糖果时，最少代价是多少？（代价是天数乘以 $a_{i}$，而且每天最多取 $m$ 个，直到取满 $k$ 个）。而这样的 $k$ 共有 $n$ 个。即从 $1$ 到 $n$ 都算一次。

## 思路
从题目可以看出，选取少量糖果时，我们只需要选 $a_{i}$ 最小的$k$个，这样算出来会是最小。假设只算一次的情况下，我们可以很简单的贪心，把大的在前几天吃完，小的留最后。然而题目要求的是 $n$ 次，如果我们枚举每一个 $k$ 的话，时间复杂度 $O(n^2)$，这样绝对过不了，我们需要有线性复杂度来解决它。可以注意到当我们取 $k$ 个时，我们可以从 $k-m$ 个的答案继承过来，这样答案会是最小的。为什么呢？因为在前面越早买越好，所以我们在第 $1$ 天取最大数 $m$ 个，那么剩下 $k-m$ 个就放到后面的天数。这我们就恰好从$f_{k-m}$继承过来，然后加上前缀和 $sum_{k}$，**表示第 $k-m$ 到第 $k$ 个第一天买，第 $1$ 到 $k-m$ 个在之前的基础上再延后一天。** 则可以顺利得到递推式：

$$f[i] = f[i-m] + sum[i]$$
$$sum[i] = sum[i-1] + a[i]$$
然后就快乐地写出代码了！

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
ll a[maxn],sum[maxn];
ll ans[maxn];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		if(i-m>=0)ans[i]=ans[i-m]+sum[i];
		else ans[i]=sum[i];//如果i小于m直接加上前缀和即可
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	} 
	cout<<endl;
	return 0;
}
```


---

## 作者：许多 (赞：1)

考虑贪心。

显然，选 $n$ 个糖果必然是糖分最少的 $n$ 个。且我们需要先选糖分大的，再选糖分少的。

如果我们暴力统计这 $n$ 种情况，肯定会 TLE，那我们怎么优化呢?

~~首先我们要先排序。~~

**当我们在第一天多选了第 $i$ 个糖果，那么 $i \bmod m=x+1$ 的数都会往后挪一天被选。**

我们维护一个特别的前缀和，即：

$$sum[i]=sum[i-m]+a[i]$$ 

在每次计算时，我们只需要用 $sum[i]$ 加上上次的答案即使这次的答案。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 222222
#define LL long long
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
LL n,m,a[N],sum[N];
long long ans=0;
int main(){
    n=read();m=read();
    for(LL i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+1+n);
    for(LL i=1;i<=m&&i<=n;i++)sum[i]=a[i];
    for(LL i=m;i<=n;i++)sum[i]=a[i]+sum[i-m];
    for(LL i=1;i<=n;i++){
        ans+=sum[i];
        printf("%lld ",ans);
    }
    return 0;
}
```


~~不开 long long 见祖宗。~~

---

## 作者：Register_int (赞：0)

考虑贪心。显然吃 $x$ 个糖果的情况下，应该取糖分最小的 $x$ 个糖果，然后糖分值大的先吃。  
假设 $a_i$ 单调递增，考虑 $x$ 与 $x+1$ 的联系。可以发现：  
1. 每次都会往方案里添加 $a_{x+1}$
2. 所有 $i\bmod m=x+1$ 的数都会往后挪一位。

那我们发现，实际上造成的贡献就是 $\sum_{i\bmod m=x+1}a_i$。对于每一个 $\bmod\ m$ 的余数 $0\sim m-1$ 统计前缀和，再全部累加就可以了。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m, a[MAXN];

vector<ll> sum[MAXN];

ll ans;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 0; i < m; i++) {
		sum[i].push_back(0);
		for (int j = i ? i : m; j <= n; j += m) sum[i].push_back(sum[i].back() + a[j]);
	}
	for (int i = 1; i <= n; i++) ans += sum[i % m][(i - 1) / m + 1], printf("%lld ", ans);
}
```

---

