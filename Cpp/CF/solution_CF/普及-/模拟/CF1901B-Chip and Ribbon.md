# Chip and Ribbon

## 题目描述

There is a ribbon divided into $ n $ cells, numbered from $ 1 $ to $ n $ from left to right. Initially, an integer $ 0 $ is written in each cell.

Monocarp plays a game with a chip. The game consists of several turns. During the first turn, Monocarp places the chip in the $ 1 $ -st cell of the ribbon. During each turn except for the first turn, Monocarp does exactly one of the two following actions:

- move the chip to the next cell (i. e. if the chip is in the cell $ i $ , it is moved to the cell $ i+1 $ ). This action is impossible if the chip is in the last cell;
- choose any cell $ x $ and teleport the chip into that cell. It is possible to choose the cell where the chip is currently located.

At the end of each turn, the integer written in the cell with the chip is increased by $ 1 $ .

Monocarp's goal is to make some turns so that the $ 1 $ -st cell contains the integer $ c_1 $ , the $ 2 $ -nd cell contains the integer $ c_2 $ , ..., the $ n $ -th cell contains the integer $ c_n $ . He wants to teleport the chip as few times as possible.

Help Monocarp calculate the minimum number of times he has to teleport the chip.

## 说明/提示

In the first test case of the example, Monocarp can perform the turns as follows:

- place the chip in the $ 1 $ -st cell; the numbers in the cells are $ [1, 0, 0, 0] $ ;
- move the chip to the next ( $ 2 $ -nd) cell; the numbers in the cells are $ [1, 1, 0, 0] $ ;
- move the chip to the next ( $ 3 $ -rd) cell; the numbers in the cells are $ [1, 1, 1, 0] $ ;
- teleport the chip to the $ 2 $ -nd cell; the numbers in the cells are $ [1, 2, 1, 0] $ ;
- move the chip to the next ( $ 3 $ -rd) cell; the numbers in the cells are $ [1, 2, 2, 0] $ ;
- move the chip to the next ( $ 4 $ -th) cell; the numbers in the cells are $ [1, 2, 2, 1] $ .

## 样例 #1

### 输入

```
4
4
1 2 2 1
5
1 0 1 0 1
5
5 4 3 2 1
1
12```

### 输出

```
1
2
4
11```

# 题解

## 作者：zhangshuhang2011 (赞：4)

## 思路

注意到题目实质上就是在求在一个全 $0$ 数组中不断对其子串加 $1$ 至少加多少次才能变成指定数组，但答案要减 $1$，故考虑此方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/5sm5v2pq.png)

注意到我们可以把数组变成柱状图并“切片”，有几片答案就是几，而片数很好统计：每当数组元素增加时都会产生一个或几个“切片”的左端，增加几就是几个“切片”。以下就是代码实现：

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[200005], ans;
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    a[0] = 0; ans = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] > a[i-1]){
            ans += a[i] - a[i-1];
        }
    }
    cout << ans-1 << endl;
}
signed main(){
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}
```

## 注意事项：

- **不开 `long long` 见祖宗**：$n$ 最大是 $2 \times 10^5$，$c_i$ 最大是 $10^9$，答案最大可以达到 $10^{14}$ 的数量级，会爆 `int`。


---

## 作者：WsW_ (赞：3)

### 思路
考虑如何把题目转化成 [P1969 [NOIP2013 提高组] 积木大赛](https://www.luogu.com.cn/problem/P1969)。  

题目求操作二的次数，所以操作一可以无限次使用。  
显然最基本的策略是用操作二移到能移到的最左边，再一直使用操作一。  
那么这样做每次就会使连续的一段全部经过一次。  
也就是说，每使用一次操作二，都能使连续的一段都被经过一次。  

这样，这个问题就被转换成了很经典的[积木大赛](https://www.luogu.com.cn/problem/P1969)，按照[积木大赛](https://www.luogu.com.cn/problem/P1969)的方法处理即可。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int T;
int n,c[200003];
ll sum;

void work(){
	cin>>n;
	sum=0;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		sum+=max(c[i]-c[i-1],0);
	}
	cout<<sum-1<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：LucasXu80 (赞：1)

转化问题为，给定原数列 $\{a_n\}$，题目中的 chip 每到达一个位置 $i$ 就使 $a_i$ 减 $1$，其他规则限制不变。求最少传送几次可以使数列的每一项都变成 $0$。

我们从一个简单的例子入手来考虑这个问题：假设原数列为 $5,1,4$。一轮从左往右后变为 $4,0,3$。

此时第 $2$ 项变成了 $0$，换言之我们不能再从这里通过了。因此我们必须要通过传送才能到下一个位置，这样的传送必须进行 $3$ 次（因为此时 $a_3=3$）。

因此有：对于第 $2$ 项及以后的项 $a_i$，如果本项大于前项，那么欲满足位置 $i$ 的条件，必须传送到这一位置 $a_i-a_{i-1}$ 次。

此外，对于第一项，除了第一次 chip 原来就放在那里之外，其他的 $a_1-1$ 次都需要通过传送到达。

```cpp
#include <iostream>
using namespace std;
int t,n,a[200001];
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>n;
		for (int i=1; i<=n; i++) cin>>a[i];
		long long ans=a[1]-1;
		for (int i=2; i<=n; i++) ans+=max(0,a[i]-a[i-1]);
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：2huk (赞：0)

## Description

有 $n$ 个格子，编号 $1 \sim n$。还有一个机器人，最开始在 $1$ 的位置上。

有两种操作：

1. 向右移动一格。若当前在第 $n$ 个格子上则无法进行此操作；
2. 瞬移到 $x$。其中 $x$ 是你选择的任意一个格子。注意可以瞬移到原地。

机器人希望进行若干次操作后，第 $i$ 个格子被走过恰好 $c_i$ 次，并让瞬移的次数尽量少。请你求出最少的瞬移次数。

$1 \le n \le 2 \times 10^5$，$0 \le c_i \le 10^9$，$c_1 \ge 1$。

## Solution

题目可以转化成，每次走过的位置 $c_i \gets c_i - 1$，求最少多少次操作使得所有 $c_i = 0$。

机器人最开始在 $1$ 的位置，那么我们可以在最开始就一直往右走，直到走到不能走为止。并将这一次走过的位置的 $c_i$ 减一。

接下来我们会选择瞬移到一些位置，然后重复上面的操作，能往右走就往右走。我们希望这里的瞬移次数最少。

其实可以发现，每次重复往右走的操作，实际上就是将某一段区间的 $c_i$ 全部减一。选择的区间数量就是瞬移的次数。那么这样就转化成了：

> 每次选择一个区间全部减一，求最少多少次操作后所有元素为 $0$。

然后仿照 [积木大赛](https://www.luogu.com.cn/problem/P1969) / [铺设道路](https://www.luogu.com.cn/problem/P5019) 做即可，若 $a_i > a_{i - 1}$ 就代表还需要多减 $a_i - a_{i - 1}$ 次，累计答案即可。

## Code

十年 CF 一场空，不开 long long 见祖宗。

```cpp
int solve()
{
	cin >> n;
	bool flg = true;
	for (int i = 1; i <= n; ++ i )
	{
		cin >> a[i];
		if (!a[i]) flg = false;
		if (flg) -- a[i];
	}
	long long res = 0;
	for (int i = 1; i <= n; ++ i )
		if (a[i] > a[i - 1])
			res += a[i] - a[i - 1];
	return res;
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

观察样例发现，需要瞬移操作当且仅当存在 $a_i>a_{i-1}$，并且瞬移次数正好是 $a_i-a_{i-1}-1$，因为可以先给所有连续的 $a_i>0$ 都执行移动操作，这样 $a_i\leftarrow a_i-1,a_{i-1}\leftarrow a_{i-1}-1$，反复执行直到 $a_{i-1}=0$，这时不能执行移动操作，于是还需要执行的瞬移操作便是此时的 $a_i$ 次，也就是开始时的 $a_i-a_{i-1}-1$，计算此值的 $\max$ 即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	a[n+1]=1;
	int ans=0;
	for(int i=1;i<=n;i++) ans+=max(a[i]-a[i-1],0ll);
	cout<<ans-1<<endl;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	solve();
	return 0; 
}

---

## 作者：what_can_I_do (赞：0)

## 题目大意
每次可以在一段长度为 $n$，初始值都为 $0$ 的序列中选取一段连续区间，并将区间内所有元素加 $1$，求最少操作数使得该序列与题目所给的序列所有元素相同，输出最少操作数减 $1$。

其实这一题跟[这一题](https://www.luogu.com.cn/problem/P1969)几乎是一样的。

首先，可以确定的是，如果一段连续的区间里面的元素都还没到达目标时，我们肯定把所有的元素统一加 $1$，并且要让这个区间的长度尽可能大，才能使操作数最小。

对于每个 $i$，$i$ 的取值范围为 $1$ 到 $n$，如果 $a_i>a_{i-1}$，那么在 $a_{i-1}$ 达到目标时 $a_i$ 还需要加上 $a_i-a_{i-1}$，也就是还要操作 $a_i-a_{i-1}$ 次。由于 $a_i>a_{i-1}$，所以 $a_i$ 就相当于是当 $a_{i-1}$ 所在的区间操作了 $a_{i-1}$ 次后它就变成了一个新的利益最大化的区间的左端点，这个区间要花上 $a_i-a{i-1}$ 次操作才能将左端点继续变动，所以操作数加上 $a_i-a_{i-1}$。如果是其它情况，因为 $a_i$ 会在 $a_{i-1}$ 到达目标之间就到达目标，所以没有对答案的贡献。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
long long a[2000010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		long long ans=0;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(register int i=1;i<=n;i++) ans+=max(a[i]-a[i-1],1ll*0);
		printf("%lld\n",ans-1);
	}
	return 0;
}
```

---

