# Asterism (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between versions is the constraints on $ n $ and $ a_i $ . You can make hacks only if all versions of the problem are solved.

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

## 样例 #4

### 输入

```
3 2
1000000000 1 999999999```

### 输出

```
1
999999998```

# 题解

## 作者：huayucaiji (赞：7)

**我们下面的推导和讲解需要用到本题 [Easy Version](https://codeforces.com/contest/1348/problem/E1) 中的结论，可以参考我的 [题解](https://www.luogu.com.cn/blog/huayucaji/solution-cf1371e1)。**

我们知道 

$$f(x)=\prod\limits_{i=x}^{x+n-1} t_i-(i-x)$$

变形得到：

$$f(x)=\prod\limits_{i=x}^{x+n-1} x-(i-t_i)$$

所以一旦 $x\equiv i-t_i (\operatorname{mod} p)$，那么 $p\nmid f(x)$。我们只要能在 O(1) 的时间内判断，就可以解决此题。我们发现 $i-t_i$ 是一个可以预处理的数。而对于不同的 $x$，也有许多重复部分，所以我们选择预处理 $i-t_i$，最后判断是否有与 $x$ 同于的即可。

顺便提一下怎么处理 $a_i$。因为 $a_i\leq 10^9$，我们不能再用数组存放了，我们可以采取二分查找的方式。比如我们看样例：

```plain
3 2
1000000000 1 999999999
```

排好序后是 $1,999999999,1000000000$。我们注意到 $\forall i\in [1,999999999)，t$ 的值都是相等的。所以用一个 $\operatorname{upperbound}$ 的简单变形即可。

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

const int maxn=1e5+10; 

int n,ex[maxn<<1],a[maxn],p;
map<int,int> t;
vector<int> ans;

int mod(int x,int p) {
	return (x+p)%p;//注意i-ti可能小于 0
}

signed main() {
	n=read();p=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
	}
	
	sort(a+1,a+n+1);
	a[n+1]=a[n]+1;
	
	for(int i=a[n]-n+1;i<=a[n];i++) {
		int q=upper_bound(a+1,a+n+1,i)-a-1;
		ex[mod(i-q,p)]++;
	}
	
	int k=max(0LL,a[n]-n+1);
	for(int x=k;x<=a[n];x++) {
		if(!ex[x%p]) {
			ans.push_back(x);
		}
		ex[mod(x-(upper_bound(a+1,a+n+1,x)-a-1),p)]--;
		ex[mod(x+n-(upper_bound(a+1,a+n+1,x+n)-a-1),p)]++;
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

## 作者：灵茶山艾府 (赞：5)

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

## 作者：FSC004 (赞：2)

## 前言

想出了一个很简洁的做法，看了一遍，题解区没有相应的题解。

## 思路

首先将 $a$ 排序。

考虑对于 $a_{1 \dots i}$：
- 最小的满足条件的 $x$ 为 $a_i-i+1$，这是显然的。
- 最大的满足条件的 $x$:
  -  当 $i\in [1,p)$ 时为 $+\infty$。
  -  证明：此时 $p\nmid f(+\infty)=i!$。
  -  当 $i\in [p,n]$ 时为 $a_i-i+p-1(i \in [p,n])$。
  -  证明：此时 $p \nmid f(a_i-i+p-1)=C_i^{p-1}\times (p-1)!$ 且 $p | f(a_i-i+p)=C_i^p\times p!$。

综上，答案即为 $[\max_{i=1}^n\{a_i-i+1\},\min_{i=1}^n\{a_i-i+p\})$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100100,inf=0x7fffffffffffffff;
int n,p,a[N],l=0,r=inf;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>p;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		l=max(l,a[i]-i+1);
		if(i>=p) r=min(r,a[i]-i+p);
	}
	cout<<max(r-l,0ll)<<endl;
	for(int i=l;i<r;i++) cout<<i<<' ';
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

首先，从 E1 的结论，如果初始的糖数量是 $x$，答案是

$$f(x)=\prod_{i=0}^{n-1}(t_{x+i}-i)$$

其中 $t_i$ 是有多少个怪物有至多 $i$ 个糖。

证明：注意题目要求赢所有的 duel。因此，我们就假设在第 $i$ 个 duel 之前的 duel 都赢了，想对答案乘上有多少个方法来赢第 $i$ 个 duel。

如果 duel 从零开始编号，那么在第 $i$ 个 duel 的时候会有 $x+i$ 个硬币。那么，在这个时候如果想赢第 $i$ 个 duel，必须选择一个有少于 $x+i$ 个糖的怪物，但是又不能选一个以前选过的怪物。这种总共有 $t_{x+i}-i$ 个选择。

在有些情况 $t_{x+i}-i$ 会变负，但是这个也没事，因为 $i$ 加一的时候 $t_{x+i}-i$ 最多减少一个单位，因为 $t_{x+i}$ 是单调非递减的序列；如果 $t_{x+i}-i$ 取负值那对于一个前面的 $i$ 它等于0。

因为这道题目里面 $a_i$ 最大值到 $10^9$，显然不能判断所有 $x$。但是，当 $x<\max(a)-n$ 的时候，肯定有 $f(x)=0$（任何排列都在和 $\max(a)$ duel 的时候赢不了）；当 $x>\max(a)$ 的时候，肯定有 $f(x)=n!$（任何排列都可以）；这些情况的数显然不用考虑。

所以我们现在想知道是有多少 $x$（$\max(a)-n\le x\le\max(a)$），使得以下不成立：

$$\prod_{i=0}^{n-1}(t_{x+i}-i)\equiv0\pmod p$$

由于 $p$ 是质数，这个等价于有多少 $x$ 使得对于所有 $0\le i<n$，$t_{x+i}-i\not\equiv0\pmod p$ 。

换一换 $i$ 的定义：对于所有 $x\le i<x+n$，

$$t_i-(i-x)=x-(i-t_i)\not\equiv0\pmod p$$
$$i-t_i\not\equiv x\pmod p$$

到这里就很简单来处理了，对于所有 $i$ 满足 $\max(a)-n\le x\le\max(a)+n$ 的 $i-t_i$，然后维护一个滚动区间里的摸 $p$ 统计数组。（注意有 +n，因为这里要处理到 $i$ 的最大值）

如果滚动数组里面没有统计到摸 $p$ 等于 $x$，则把 $x$ 放入答案列表里面。

然后好了。

---

## 作者：Meatherm (赞：1)

Update On 2020.07.07：修复了公式错误。

搬运官方题解

----

设 $b_i$ 表示糖果数量不超过 $i$ 的敌人数量，那么我们可以说，

$$f(x)=\prod \limits_{i=x}^{x+n-1} b_i-(i-x)=\prod \limits_{i=x}^{x+n-1} x-(i-b_i)$$

显然的，当 $x\equiv i-b_i(\mod p)$ 时，$f(x)\mid p$。


容易观察到，当 $f(x)\nmid p$ 时，$\max(a_i)-n\leq x \leq \max(a_i)$。当 $x<\max(a_i)-n$，$f(x)=0$；当 $x>\max(a_i)$，$f(x)=n!$。它们都能被 $p$ 整除。

我们计算出 $x=\max(a_i)-n$ 时所有的 $i-b_i$，将它们$\mod p $ 的结果放入计数数组 $cnt$，然后 $O(n)$ 求解。

具体来讲，当 $x=i$ 时，首先查看 $cnt_{i \mod p} $ 是否为 $0$。如果为 $0$，则 $x=i$ 是一个可行解。

删除 $i-b_i$ 的贡献，然后加入 $i+n-b_{i+n}$ 的贡献，为 $x=i+1$ 时的计算做准备。

关于值域问题：可以把 $\max(a_i)$ 当作 $n$。即：$a_i \to \max\{0,a_i-\max(a_i) +n\}$。

当然，也可以将 $a_i$ 排序，然后使用二分查找的方式来求解（纯口胡，待验证）。

```cpp
# include <bits/stdc++.h>
# define rr
const int N=100010,INF=0x3f3f3f3f;
int n,p;
int b[N*2];
int cnt[N];
int a[N];
int val,maxx;
int c[N],ans;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
inline int mod(int x){// 小心负数
	return (x%p+p)%p;
}
int main(void){
	n=read(),p=read();
	for(rr int i=1;i<=n;++i){
		maxx=std::max(maxx,a[i]=read());
	}
	val=maxx-n;
	for(rr int i=1;i<=n;++i){
		++b[std::max(0,a[i]-val)];
	}
	for(rr int i=1;i<=(int)2e5;++i){
		b[i]+=b[i-1];
	}
	for(rr int i=0;i<n;++i){
		++cnt[mod(i+val-b[i])];
	}
	for(rr int i=0;i<=n;++i){
		if(!cnt[mod(i+val)]){
			c[++ans]=i+val;
		}
		--cnt[mod(i+val-b[i])];
		++cnt[mod(i+n+val-b[i+n])];
	}
	printf("%d\n",ans);
	for(rr int i=1;i<=ans;++i){
		printf("%d ",c[i]);
	}
	return 0;
}

```

---

## 作者：中缀自动机 (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1371E2)

记 $M=\max{a_i}$，那么满足条件的 $x$ 一定位于 $[M−n,M]$ 之间，这是因为在这个区间之外的 $f(x)$ 只可能为 $0$ 或 $n!$。

接下来计算 $f(x)$。

注意到，第 $i$ 次可以打的敌人第 $i+1$ 次也可以打，那么记 $\le i$ 个糖果的敌人数量为 $t_i$，第 $j$ 次能打的敌人的数量恰好为 $t_{x+j−1}−j+1=x−(x+j−1−t_{x+j−1})$。

总共的方案数就是这些数量乘起来，所以判断是否能被 $p$ 整除可以通过对每个数量判断。 

记 $g_i=i−t_i$，那么 $f(x)=\prod_{i=x}^{x+n−1}(x−g_i)$，若 $x$ 与某个 $g_i$ 在模 $p$ 意义下同余，那么 $p\mid f(x)$。

那么我们可以开一个桶记录在区间 $[x,x+n−1]$ 中 $g_i \bmod p$ 的值。从小往大枚举 $x$，并且更新桶即可。

时间复杂度 $O(n)$。

---

## 作者：Helloworldwuyuze (赞：0)

# CF1371E2 题解

## Des

给定一个序列 $a_n$，现在有常数 $x$，我们称一个序列是好的，当且仅当对于 $\forall i\in [1,n]\cap \mathbb{Z}$，都有 $x+i-1\ge a_i$。

现在，我们设 $f(x)$ 表示序列 $a$ 中常数为 $x$ 时好的序列的数量。

现给定序列 $a$，问有多少个 $x$ 使得 $p\nmid f(x)$，其中 $p$ 是给定质数。

## Sol

### Part 1

首先，容易发现的是，对于上面的不等式 $x+i-1\ge a_i$，当 $i=n$ 的时候，可以得到 $x+n-1\ge a_n$。这里我们不妨设 $a_n$ 已经从小到大排序。因此我们注意到，$x$ 必须要比 $a_n-n$ 要大。否则无论如何都不能够使 $x-i \ge a_n$。

这样，我们就将值域变成了 $O(n)$ 级别。

另外，当 $x>a_n$ 的时候，显然这个时候 $f(x) = n!$，而由题意有 $p\le n$，故一定有 $p\mid n!$。因此对于 $x>a_n$ 的讨论也是无意义的。

### Part 2

我们容易想到先考虑对于一个 $x$，$f(x)$ 是什么。

我们设 $t_i$ 表示 $\sum\limits_{k=1}^n [a_k\le i]$。说人话就是小于等于 $i$ 的元素数量。那么，第一个地方可以填的就只有小于等于 $x$ 的数，同理，第二个地方就是小于等于 $x+1$ 的数的数量再 $-1$，以此类推。

于是，我们就不难写出公式：
$$
f(x) = \prod_{i=x}^{x+n-1} (t_i-(i-x))
$$

### Part 3

思路一下子就清晰了许多。因为 $f(x)$ 可以写成一个积的形式，所以我们保证 $p\nmid f(x)$ 只需保证对于任意的 $i\in[x,x+n-1]$，都有 $p \nmid (t_i-(i-x))$ 即可。

对 $t_i-(i-x)$ 进行变形，将有关 $i$ 的项提出来，得到新的式子 $x-(i-t_i)$。也就是说，只要 $x\equiv i-t_i\pmod{p}$ 就不能够满足不等式。其中值得注意的是 $i-t_i$ 是可以预处理的。

### Part 4

正解已经浮出水面了。我们从 $1$ 扫到 $n$，分别表示 $x$ 从 $a_n-n+1$ 一直到 $a_n$，然后预处理出来 $t_i$，刚开始暴力统计 $i-t_i\bmod p$ 的状态。也就是说，开一个桶记录一下 $i-t_i\bmod p$ 分别可以取到多少，这个桶是 $O(n)$ 的，然后合法的充分必要条件就变成了桶内 $x\bmod p$ 是没有东西的。

随后，注意到移动一次只会把 $i$ 从桶中去除，把 $i+n$ 加入桶中，于是每一次修改也是 $O(1)$ 的。

这样，我们就得到了一个复杂度为 $O(n)$ 的优秀做法。

### Code

```cpp
const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
typedef pair<int,bool*> PIB;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
inline int max(int x,int y){ return x<y ? y : x; }
inline int min(int x,int y){ return x<y ? x : y; }

int n, p, a[N], t[N<<1], m, s[N];
vector<int> ans;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>p; m = n;
	for(int i=1;i<=n;++i)	cin>>a[i], m = max(m, a[i]);
	for(int i=1;i<=n;++i)
		if(a[i] <= m-n)	++t[1];
		else	++t[a[i]-(m-n)];
	for(int i=1;i<=n<<1;++i)	t[i] += t[i-1];
	for(int i=1;i<=n;++i)	s[((i+m-n-t[i])%p+p)%p]++;
	for(int i=1;i<=n;++i){
		if(!s[(i+m-n)%p])	ans.pb(i+m-n);
		--s[((i+m-n-t[i])%p+p)%p], ++s[((i+m-t[i+n])%p+p)%p];
	}
	cout<<ans.size()<<endl;
	for(int x:ans)	cout<<x<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：subcrip (赞：0)

首先估算一下范围：一方面 $x+n-1\geqslant\max(a_i)$，因为题目要求击败所有敌人；另一方面 $x<\max(a_i)$，否则选择数是 $n!$，它一定被 $p$ 整除。所以 $x\in[\max(a_i)-n+1,\max(a_i)-1]$。也就是说可以把 $x$ 整体往左平移 $x_0:=\max(a_i)-n+1$ 再考虑。

假设 $b_i$ 表示满足 $x_0+j\geqslant a_k$ 的最小自然数 $j$ 恰为 $i$ 的 $k$ 的个数。也就是说如果 Yuzu 初始有 $x_0$ 个糖果，那么这些 $a_k$ 至少要等到 Yuzu 积累 $j-1$ 个额外的糖果之后才能被击败。那么合法的排列数就是

$$
b_1(b_1+b_2-1)(b_1+b_2+b_3-2)\cdots(b_1+\cdots+b_n-(n-1)).
$$

那么如何处理初始值不为 $x_0$ 的情况？容易发现，我们只需要去掉 $b_1$、添加一个 $b_1+\cdots+b_n-(n+1)$，然后把所有括号里的东西全加上 $1$ 就转移到了 $x_0+1$ 的情况。

而且题目只要求判断答案是否被 $p$ 整除，这意味着我们可以只记录上面的大式子中每个括号内的值模 $p$ 之后的值，观察是否有模 $p$ 等于 $0$ 的就行。这样的话，只需要维护一个偏移量，每次用偏移量减一代替所有括号内加一的操作，每次转移后再判断时我们去判断是否有模 $p$ 等于当前偏移量的元素，就实现了 $O(1)$ 转移。

时间复杂度 $O(n)$。

Code:

```cpp
void solve() {
    read(int, n, p);
    readvec(int, a, n);

    int mx = *max_element(a.begin(), a.end());
    int init = mx - n + 1;

    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[max(0, a[i] - init)] += 1;
    }

    vector<int> ps(n + 1);
    vector<int> cnt(p);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = (sum + b[i]) % p;
        ps[i + 1] = mod(sum - i, p);
        cnt[ps[i + 1]] += 1;
    }

    vector<int> res;
    int delta = 0;
    for (int i = 0; i < n; ++i) {
        if (cnt[delta] == 0) {
            res.emplace_back(init + i);
        }

        // remove the previous element
        delta = mod(delta - 1, p);
        cnt[ps[i + 1]] -= 1;

        // add the tail element
        cnt[mod(sum - n - i, p)] += 1;
    }

    cout << res.size() << '\n';
    putvec(res);
}
```

---

