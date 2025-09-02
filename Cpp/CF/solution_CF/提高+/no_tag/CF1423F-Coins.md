# Coins

## 题目描述

A famous gang of pirates, Sea Dogs, has come back to their hideout from one of their extravagant plunders. They want to split their treasure fairly amongst themselves, that is why You, their trusted financial advisor, devised a game to help them:

All of them take a sit at their round table, some of them with the golden coins they have just stolen. At each iteration of the game if one of them has equal or more than 2 coins, he is eligible to the splitting and he gives one coin to each pirate sitting next to him. If there are more candidates (pirates with equal or more than 2 coins) then You are the one that chooses which one of them will do the splitting in that iteration. The game ends when there are no more candidates eligible to do the splitting.

Pirates can call it a day, only when the game ends. Since they are beings with a finite amount of time at their disposal, they would prefer if the game that they are playing can end after finite iterations, and if so, they call it a good game. On the other hand, if no matter how You do the splitting, the game cannot end in finite iterations, they call it a bad game. Can You help them figure out before they start playing if the game will be good or bad?

## 说明/提示

In the third example the game has no end, because You always only have only one candidate, after whose splitting you end up in the same position as the starting one.

## 样例 #1

### 输入

```
4 2
1 2
2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
6 2
2 3
4 1```

### 输出

```
1```

## 样例 #3

### 输入

```
3 2
1 1
2 2```

### 输出

```
-1```

# 题解

## 作者：Zxc200611 (赞：3)

# CF1423F Coins

注意下文中的 $b$ 长度为 $n$，其中 $b_i$ 表示这 $n$ 个人中第 $i$ 个人拥有的硬币数量。

设 $s=\sum_{i=1}^n b_i$。

当 $s>n$ 时游戏显然不可能结束，因为硬币总数是不变的，而游戏结束时每个人手中的硬币数量小于等于 $1$。

我们定义一个 **$k$-连通块** 为硬币数量的极长子串，满足其中每一项都大于等于 $k$。

我们观察一个序列 `0 1 1 2 1 1 1 1 0` 的变化情况。

```
0 1 1 2 1 1 1 1 0
0 1 2 0 2 1 1 1 0
0 2 0 2 0 2 1 1 0
1 0 2 0 2 0 2 1 0
1 1 0 2 0 2 0 2 0
1 1 1 0 2 0 2 0 1
1 1 1 1 0 2 0 1 1
1 1 1 1 1 0 1 1 1
```

我们发现，这个**操作**相当于，中间的 $1$-连通块往两边扩展了一个 $1$，然后那个 $2$ 所在的位置减少了 $1$，与它在原来的连通块里左右对称的那个位置也减少了 $1$。

观察到上面图案中间 $0$ 与 $2$ 组成的块形状非常有规律，然后证明就很简单了。以下是一个比较感性的解释：

```
...1 1 1 2 1 1 1...
...1 1 2 0 2 1 1...
...1 2 0 2 0 2 1...
```

首先，中间的包含 $0$，$2$ 的块以每次左右各一个位置的速度扩张，并且每个位置不断在 $0$，和 $2$ 间切换。与旁边的 $1$ 相邻的位置总是 $2$。

```
0 1 2 0...
0 2 0 2...
1 0 2 0...
```

当中间包含 $0$，$2$ 的块扩张到边界时，最外面的 $2$ 会往它所在的这边放一个 $1$。

两边出现这个情况的时间可能不相同，但一定会出现，且出现的时间等于一开始这边 $1$ 的个数。

```
1 0 2 0...
1 1 0 2...
1 1 1 0...
```

然后，由于边上变为了 $1$，较靠里面的数无法再维持原来的变换，于是中间包含 $0$，$2$ 的块以每次一个位置的速度缩小，并不断往旁边填充 $1$。与外面的 $1$ 相邻的位置总是 $0$。

```
...1 0 2 0 2 0 1...
...1 1 0 2 0 1 1...
...1 1 1 0 1 1 1...
```

最后，当中间包含 $0$，$2$ 的块缩小为只剩一个 $0$ 时（由于其扩张和缩小的速度都是每次一个位置，最后 $0$ 的位置应与原来 $2$ 的位置左右对称），操作结束。

所以，对于一个有至少一个硬币数量大于 $k$ 的 $k$-连通块，我们可以从中选取一个大于 $k$ 的硬币数量 $b_x$，把它作为上述操作中的 $2$，其他位置上的数作为 $1$，进行上面的操作（此连通块中其他硬币不参与此次操作）。于是我们就可以将 $b_x$ 减少 $1$，此 $k$-连通块中另一个数也减少 $1$，然后把连通块左右的数各加上 $1$。（此时这个连通块可能会被分为两个连通块，也可能与两边的一些硬币数量拼起来成为新的连通块。）

于是我们得到了一个**做法**：每次选择一个最大的硬币数量 $b_m = \max b$，找到它所在的 $(b_m-1)$-连通块，然后对其执行上述操作。操作后 $b_m$ 至少减少 $1$，且一般不会新生成一个大于等于与原来的 $b_m$ 的硬币数量。

注意到上面所说的「一般」。事实上，唯一的**反例**是当选择的 $b_m$ 等于 $2$ 且此连通块左右两边的位置是同一个位置时，此时两边扩展的硬币加在了同一个位置，导致这个位置又出现了一个 $2$，与操作前情况等价。因为硬币数量最多为 $n$，所以上述情况等价于所有硬币数量中，有且仅有一个 $2$，也相当于有且只有一个 $0$。此连通块硬币数量恰好为 $n$，因此此时不存在其他连通块。

我们不断执行上面的做法，如果每个人手中的硬币数量都小于等于 $1$ 则结束。当有至少两个连通块时，由于此时每个连通块左右两边的位置必定不相同，所以我们必定可以执行至少一次做法。

所以，当 $s<n$ 时，由于无法构成上面的反例，游戏必定会结束。

只剩下 $s=n$ 的情况了。我们需要较为快速地判断，什么时候会形成上面反例中的情况。

我们发现，当 $s=n$ 时要么形成上面反例中的情况，要么硬币数量最后全是 $1$（否则必然能继续执行上面的做法）。

我们设 $f=\left( \sum_{i=1}^n b_i \right) \bmod n$。我们发现当我们第 $i$ 个人向左右的人分硬币时，$f \gets [f-2i+(i-1)+(i+1)] \bmod n=f$。所以无论怎么操作，$f$ 都是不变的。

对于硬币数量全是 $1$ 的情况，可以发现 $f=\frac{n(n+1)}{2} \bmod n$。对于上面的反例中的情况，若设 $a$，$b$（$a \neq b$）分别表示 $2$ 与 $0$ 的位置，可以发现 $f=\left[\frac{n(n+1)}{2}+a-b\right] \bmod n \neq \frac{n(n+1)}{2} \bmod n$。

所以我们就得到了最终的做法：

+ 对于 $s>n$，游戏必不能结束。
+ 对于 $s<n$，游戏必然能结束。
+ 对于 $s=n$，若 $f=\frac{n(n+1)}{2} \bmod n$，则游戏必能结束，否则游戏必然不能结束。

总时间复杂度为 $O(k)$，可以通过本题。

代码非常简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	int s=0,f=0;
	for(int i=1;i<=k;i++)
	{
		int p,v;
		cin>>p>>v;
		s+=v,f=(f+1LL*p*v)%n;
	}
	if(s>n)
		cout<<-1<<endl;
	else if(s<n)
		cout<<1<<endl;
	else
		cout<<(((1LL*n*(n+1)/2)%n)==f?1:-1)<<endl;
}
```





---

## 作者：st1vdy (赞：1)

# CF1423F Coins

**题意**：$n$ 个人围坐在一个圆环上，其中有 $k$ 个人手上有硬币，位置 $a_i$ 上的人有 $b_i$ 枚硬币。现在每一轮你都可以命令一个至少持有 $2$ 枚硬币的人，让他从他的硬币中拿出两枚，分给他的左右邻居各一枚。询问你是否可以在有限步内让所有人都无法再分配硬币（即每个人手上的硬币数都小于 $2$ ），如果可以输出 $1$ ，不可以输出 $-1$。

**分析**：很容易发现当 $\sum_{i=1}^{k}b_i>n$ 时必定不可以；$\sum_{i=1}^kb_i < n$ 时必定可以；因此本题实际上就是在考察 $\sum_{i=1}^{k}b_i=n$ 的情况。

假设位置 $i$ 上的人有 $c_i$ 枚硬币，设他的权值为 $i\cdot c_i \% n$ ，当他将手上的硬币分配给左右邻居时，权值将会转变为 $(i(c_i-2)\%n+(i-1)\% n+(i+1)\% n)\% n$ ，等价于 $(i(c_i-2)+(i-1)+(i+1))\% n=ic_i\% n$ 。于是我们可以推出结论， $\sum_{i=1}^nic_i\bmod n$ 不论如何变换都是一个定值。

因此本题如果可以在有限步内结束分配，那就必须满足：
$$
\begin{aligned}
\sum^k_{i=1}a_ib_i\bmod n=\sum_{i=1}^ni\bmod n
\end{aligned}
$$

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, k;
	cin >> n >> k;
	long long sum = 0, res = 0;
	for (int i = 1; i <= k; i++) {
		int a, b;
		cin >> a >> b;
		sum += b;
		res += 1LL * a * b;
	}
	if (sum > n) {
		cout << -1;
	} else if (sum < n) {
		cout << 1;
	} else {
		if (res % n == 1LL * n * (n + 1) / 2 % n) {
			cout << 1;
		} else {
			cout << -1;
		}
	}
	return 0;
}
```



---

## 作者：Φρανκ (赞：0)

题意：$n$ 个人呈环状排列，第 $a_i$ 个人有 $b_i$ 枚硬币。一次操作可以令一个人给相邻的两个人各一枚硬币，求有没有方法使得没有人最终有一枚以上硬币。

核心思想：找不变量

解：

显然，若总硬币数超过 $n$ 则必不可能。

对于每一次操作，两枚硬币一枚给了编号大 $1$ 的人，一枚给了编号小 $1$ 的人，所有硬币的所有者的总编号是不变的。考虑从 $1$ 到 $n$ 和从 $n$ 到 $1$，所有硬币的所有者的总编号在模 $n$ 意义下是不变的。若总硬币数小于 $n$，至少有一个 $0$ 可以出现在任意位置，则无论初始硬币总编号数模 $p$ 如何均可转移到结束状态。若总硬币数恰为 $n$，则唯一可能结束状态是所有人均持 $1$ 枚硬币，所以有且只有初始总编号数模 $n$ 余 $\dfrac{n(n+1)}{2}$ 才可以达成。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, a, b, sum, res;
int main()
{
	cin>>n>>k;
	for(int i=1; i<=k; i++)
	{
		cin>>a>>b;
		sum+=b;//记录总硬币数
		res=(res+a*b)%n;//记录总编号值
	}
	if(sum>n)
		cout<<-1;
	else if(sum<n)
		cout<<1;
	else if(res==n*(n+1)/2%n)
		cout<<1;
	else
		cout<<-1;//分类讨论
	return 0;
}
```

---

