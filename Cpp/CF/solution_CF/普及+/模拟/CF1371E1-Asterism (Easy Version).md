# Asterism (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between versions is the constraints on $ n $ and $ a_i $ . You can make hacks only if all versions of the problem are solved.

First, Aoi came up with the following idea for the competitive programming problem:

Yuzu is a girl who collecting candies. Originally, she has $ x $ candies. There are also $ n $ enemies numbered with integers from $ 1 $ to $ n $ . Enemy $ i $ has $ a_i $ candies.

Yuzu is going to determine a permutation $ P $ . A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ \{2,3,1,5,4\} $ is a permutation, but $ \{1,2,2\} $ is not a permutation ( $ 2 $ appears twice in the array) and $ \{1,3,4\} $ is also not a permutation (because $ n=3 $ but there is the number $ 4 $ in the array).

After that, she will do $ n $ duels with the enemies with the following rules:

- If Yuzu has equal or more number of candies than enemy $ P_i $ , she wins the duel and gets $ 1 $ candy. Otherwise, she loses the duel and gets nothing.
- The candy which Yuzu gets will be used in the next duels.

Yuzu wants to win all duels. How many valid permutations $ P $ exist?

This problem was easy and wasn't interesting for Akari, who is a friend of Aoi. And Akari made the following problem from the above idea:

Let's define $ f(x) $ as the number of valid permutations for the integer $ x $ .

You are given $ n $ , $ a $ and a prime number $ p \le n $ . Let's call a positive integer $ x $ good, if the value $ f(x) $ is not divisible by $ p $ . Find all good integers $ x $ .

Your task is to solve this problem made by Akari.

## 说明/提示

In the first test, $ p=2 $ .

- If $ x \le 2 $ , there are no valid permutations for Yuzu. So $ f(x)=0 $ for all $ x \le 2 $ . The number $ 0 $ is divisible by $ 2 $ , so all integers $ x \leq 2 $ are not good.
- If $ x = 3 $ , $ \{1,2,3\} $ is the only valid permutation for Yuzu. So $ f(3)=1 $ , so the number $ 3 $ is good.
- If $ x = 4 $ , $ \{1,2,3\} , \{1,3,2\} , \{2,1,3\} ,         \{2,3,1\} $ are all valid permutations for Yuzu. So $ f(4)=4 $ , so the number $ 4 $ is not good.
- If $ x \ge 5 $ , all $ 6 $ permutations are valid for Yuzu. So $ f(x)=6 $ for all $ x \ge 5 $ , so all integers $ x \ge 5 $ are not good.

So, the only good number is $ 3 $ .

In the third test, for all positive integers $ x $ the value $ f(x) $ is divisible by $ p = 3 $ .

## 样例 #1

### 输入

```
3 2
3 4 5```

### 输出

```
1
3```

## 样例 #2

### 输入

```
4 3
2 3 5 6```

### 输出

```
2
3 4```

## 样例 #3

### 输入

```
4 3
9 1 1 1```

### 输出

```
0```

# 题解

## 作者：huayucaiji (赞：7)

首先我们可以确定是一个 $O(n^2)$ 的算法。而且我们知道为了赢得所有的对战，~~易得~~$x_{min}=\max(a_i)-n+1$。此时 $\max(a_i)$ 放在最后一个位置。我们分三个情况讨论：

1.$x<\max(a_i)-n+1$，此时无解，即 $f(x)=0$，$p\mid f(x)$，所以不是我们想要的解。  
2.$x>\max(a_i)$，此时任意排列都可以，即 $f(x)=n!$，因为 $p\leq n$，$p\mid f(x)$，所以不是我们想要的解。  
3.$max(a_i)-n+1\leq x\leq\max(a_i)$，此时有可能有解。

因此我们只需要考虑第三种情况。由于时间充裕，我们可以枚举 $x$，用 $O(n)$ 的时间来计算 $f(x)$。

我们采取计算每一位上有多少个可以放的怪兽，因为可以放在 $i$ 上的怪兽一定可以放在 $i+1$ 的位置上，满足单调性，所以可以从前往后扫。我们记 $t_i$ 为糖果数量小于等于 $i$ 的怪兽的数量。我们可以用排列组合得出下面的式子：

$$f(x)=\prod\limits_{i=x}^{x+n-1} t_i-(i-x)$$

$i-x$ 就表示已经用过多少怪兽，剩下 $t_i-(i-x)$ 个可以放。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=2e4+10;

int n,a[maxn],p,t[maxn<<1];
vector<int> ans;

signed main() {
	
	n=read();p=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
		t[a[i]]++;
	}	
	
	sort(a+1,a+n+1);
	
	for(int i=1;i<=a[n]+n;i++) {
		t[i]=t[i]+t[i-1];
	}
	
	int k=max(0LL,a[n]-n+1);
	
	for(int x=k;x<=a[n];x++) {
		bool flag=1;
		for(int i=x;i<x+n-1;i++) {
			if((t[i]-(i-x))%p==0) {
				flag=0;
				break;
			}
		}
		if(flag) {
			ans.push_back(x);
		}
	}
	
	cout<<ans.size()<<endl;
	int sz=ans.size();
	for(int i=0;i<sz;i++) {
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：4)

讨论 $x$ 的上下界。

将 $a$ 排序，以贪心的视角来看，先从最小的敌人开始打，然后打次小的敌人，以此类推，这样可以确保在有方案的情况下 $x$ 尽可能地小。

对于第 $i$ 个敌人（$i\ge 0$），打败该敌人之前拥有的糖果数为 $x+i$，因此为了战胜该敌人需要有

$$
x+i\ge a_i
$$

取所有下界的最大值，即得到了 $x$ 的下界。任何低于下界的 $x$ 都有 $f(x)=0$，而 $p|0$，不符合要求。

从位置 $i$ 向右看，其能选到所有 $a_j\le x+i$ 的敌人，若 $j-i+1\ge p$，则后续必然存在一个位置能选到恰好 $p$ 个敌人，从而导致 $p|f(p)$，不符合要求。

因此，对于每个 $i\ge p-1$ 的 $a_i$，其对应的位置 $i-p+1$ 上拥有的糖果数不能 $\ge a_i$，则有

$$
x+i-p+1<a_i
$$

取所有上界的最小值，即得到了 $x$ 的上界。

在该上下界内的 $x$ 均是符合要求的。

AC 代码：（Golang）

```go
package main

import (
	"bufio"
	. "fmt"
	. "os"
	"sort"
)

func main() {
	in := bufio.NewReader(Stdin)
	out := bufio.NewWriter(Stdout)
	defer out.Flush()

	var n, p int
	Fscan(in, &n, &p)
	a := make([]int, n)
	for i := range a {
		Fscan(in, &a[i])
	}
	sort.Ints(a)
	mi, mx := 0, int(2e9)
	for i, v := range a {
		mi = max(mi, v-i)
		if i-p+1 >= 0 {
			mx = min(mx, v-(i-p+1))
		}
	}
	Fprintln(out, max(mx-mi, 0))
	for i := mi; i < mx; i++ {
		Fprint(out, i, " ")
	}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```


---

