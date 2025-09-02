# [NWRRC 2016] Boys and Girls

## 题目描述

Bob在他那本给孩子们的旧数学书中找到了一个好任务。上面写着：

有 $10$ 个孩子站成一个圆圈，其中 $5$ 个站在一个男孩旁边， $7$ 个站在一个女孩旁边。如何解决这个任务？

这个任务的解决方案如下：如果 $4$ 个男孩和 $6$ 个女孩像这样站着：$bgbgbbggg$，那么有 555 个孩子站在一个男孩旁边（用粗体字标记：b**g**b**g**b**g**b**g**g**g**）， 777 个孩子站在一个女孩旁边（用粗体字标记：**b**g**b**g**b**g**bggg**）。

现在Bob想解决这个任务的广义版本：

有 $n$ 个孩子站在一个圆圈里，其中 $x$ 个孩子站在一个男孩旁边， $y$ 个孩子站在一个女孩旁边。如何解决这个任务？

请编写一个程序来帮助Bob解决这个任务。

## 样例 #1

### 输入

```
10 5 7
```

### 输出

```
BGBGBGBGGG
```

## 样例 #2

### 输入

```
10 3 8
```

### 输出

```
Impossible
```

# 题解

## 作者：Starlight237 (赞：1)

> (**2021集训队作业 P7032 【[NWRRC2016]Boys and Girls】**) 长度为 n 的环二染色，要求恰有 a 个点两侧至少有一个白点，恰有 b 个点两侧至少有一个黑点，问是否可能。如果可能，输出任一种染色方法。

首先假定白点为 0，黑点为 1（在本题的输出中，白点应该是 $\texttt{B}$，黑点则是 $\texttt{G}$）。题目条件相当于要求恰有 $n-b$ 个位置两侧均为 0，恰有 $n-a$ 个位置两侧均为 1。设 $x=n-b,y=n-a$。

设这个环为 $c$，那么条件等价于 $\sum[c_{i-1}=c_{i+1}=0]=x,\sum[c_{i-1}=c_{i+1}=1]=y$，其中 $c_{n+1}=c_1,c_{-1}=c_n$。

Case 1. 当 n 为奇数时，条件转化为在一个环 $c'_j=c_{2j-1}$ 上，要求 $\sum[c'_j=c'_{j+1}=0]=x,\sum[c'_j=c'_{j+1}=1]=y$。

注意，这时候**问题转化到一个不限制长度奇偶性的环上，并且所有限制由隔一位变成相邻位**。为了方便表述，我们形式化地定义 $\text{Problem B}(l,x,y)$ 来表示问题“在某个长度为 $l$ 的环 $c'$ 上求满足  $\sum[c'_j=c'_{j+1}=0]=x,\sum[c'_j=c'_{j+1}=1]=y$ 的染色方案”。下面的讨论针对 $\text{Problem B}(n,x,y)$，而与 $n$ 的奇偶性和原环的其他信息完全无关。换言之，下面的讨论也适用于 $n$ 为偶数的情况。

首先显然有 $x+y\le n$。此外，有等式 $\sum[c'_j=c'_{j+1}=0]+\sum[c'_j=c'_{j+1}=1]+\sum[c'_j\not=c'_{j+1}]=n$，注意到 $\sum[c'_j\not=c'_{j+1}]=2\sum[c'_j=0\text{ or }c'_{j+1}]=1\equiv0(\bmod2)$，则得到了另一个有解的必要条件 $x+y\equiv n(\bmod2)$。考虑根据这两个条件来构造一个解（从而得到这是充要条件），令 $t=\dfrac{n-x-y}2$ 为极长白色连续段的个数减一，则可以构造形如 $111...000...(01)^t$ 的串，容易验证这是满足答案的。构造好之后，从 $\text{Problem B}$ 转化回原问题即可（令 $c_{2j-1}\leftarrow c'_j$）。

但是注意到如果 $x+y=n$，那么不存在极长白色连续段，整个环必须同色，也就要求 $x=0$ 或 $y=0$。否则无解。加个特判即可。

Case 2. 当 n 为偶数时，注意到可以把原环剖开成独立的两个环 $c_1,c_3,...$ 和 $c_2,c_4,...$，这两个环无论如何染色都不会互相影响。我们考虑将 $(x,y)$ 拆成 $(x',y')+(x'',y'')$，使得两个环上面的 $\text{Problem B}$ 都有解，具体地，使得 $\text{Problem B}(\dfrac n2,x',y')$ 和 $\text{Problem B}(\dfrac n2,x'',y'')$ 都有解。

通过类似奇数情况下的推导，容易得出两个必要条件：$x+y\equiv n(\bmod2)$，$x+y\le n$。稍有不同的是，特判有所不同而且还多了几种情况：当 $x+y=n$ 时，我们只需要 $x'=0\text{ or }y'=0$ 和 $x''=0\text{ or }y''=0$ 成立即可。为了达到这个目的，只需 $x=0\text{ or }y=0\text{ or }x=y$。若 $x=y=0$，则 $x'=y'=x''=y''=0$，此时需要 $4|n$ 才有解。若 $x+y=n-2$，则根据 $x'+y'\le \dfrac n2$ 和 $x''+y''\le\dfrac n2$ 知，必然有 $x\not=y$。

在这些条件的基础上，我们下面来构造出一个有解的划分方法（下面不妨设 $x\ge y$）：

若 $x+y=n$，上面已经说过怎么拆了。

若 $x+y=n-2$，拆 $(x,y)=(\dfrac n2,0)+(x-\dfrac n2,y)$，易见这样可以满足 $\text{Problem B}$ 有解的充要条件。

其他情况下的拆法可以参见代码。

```cpp
const int N = 1e5 + 10;
int n, x, y, ans[N], _ans[N];
inline void solve(int n, int x, int y) {
	if (x + y == n) return void(memset(ans, bool(y), sizeof ans));
	for (int i = 1; i <= x; ++i) ans[i] = 0;
	for (int i = x + 1; i <= x + y; ++i) ans[i] = 1;
	for (int i = x + y + 1, t = 1; i <= n; ++i, t ^= 1) ans[i] = t;
}
int main() {
	freopen("1.in", "r", stdin);
	n = rd(), y = n - rd(), x = n - rd();
	if ((x + y & 1) ^ (n & 1) || x + y > n) return puts("Impossible"), 0;
	if (n & 1) {
		if (x + y == n && x && y) return puts("Impossible"), 0;
		solve(n, x, y), memcpy(_ans, ans, sizeof ans);
		int j = 1;
		for (int i = 1; i <= n; i += 2, ++j) ans[i] = _ans[j];
		for (int i = 2; j <= n; i += 2, ++j) ans[i] = _ans[j];
	}
	else {
		if (x + y + 2 == n && x == y || (n & 2) && !x && !y) return puts("Impossible"), 0;
		if (x + y == n) {
			if (!x || !y) memset(ans, bool(y), sizeof ans);
			else if (x == y) for (int i = 1, t = 0; i <= n; ++i, t ^= 1) ans[i] = t;
			else return puts("Impossible"), 0;
			for (int i = 1; i <= n; ++i) putchar(ans[i] ? 'G' : 'B');
			return 0;
		}
		int xx, yy, uu, vv, _ = n >> 1;
		if (x < y) xx = 0, yy = min(_, y - ((y ^ _) & 1));
		else xx = min(_, x - ((x ^ _) & 1)), yy = 0;
		uu = x - xx, vv = y - yy;
		solve(_, xx, yy), memcpy(_ans + 1, ans + 1, _ << 2);
		solve(_, uu, vv), memcpy(_ans + _ + 1, ans + 1, _ << 2);
		int j = 1;
		for (int i = 1; i <= n; i += 2, ++j) ans[i] = _ans[j];
		for (int i = 2; i <= n; i += 2, ++j) ans[i] = _ans[j];
	}
	for (int i = 1; i <= n; ++i) putchar(ans[i] ? 'G' : 'B');
	return 0;
}
```

---

## 作者：max67 (赞：0)

## 前言

感谢 @[Umbrella_Leaf](https://www.luogu.com.cn/user/233462#following) 大佬的指导

（看分类过程的可以看有灰色竖线的部分）
## 题解
设与男孩相邻的数量为 $a$，与女孩相邻的数量为 $b$。

首先可以凭感觉知道：这种既带构造又带环的题目，大多都要分类讨论。为了使我们讨论的顺畅一点，首先我们先特判一些特殊情况，创造出一些性质：

> 当 $a=0$ 时，注意到此时不能填  ```B```，必须全填 ```G```。容易算出此时的 $b$ 的值为 $n$。因此当且仅当 $b=n$ 时有解。$b=0$ 的情况同理。

那么此时满足答案里面至少有一个 ```G```，至少有一个 ```B```。分别考虑每个字符的贡献，注意到这仅与他两边的字符有关。

那么考虑把一段连续的字符缩成一个连续段，分别讨论每个连续段的贡献（假设这个连续段的字符都是 ```B```）：

* 设这个连续段的长度为 $k$，首先可以观察出与这个连续段相邻的连续段的字符都是 ```G```

* 当 $k=1$ 时，注意到他两边的字符都是 ```G```，那么只有对 $b$ 有 $1$ 的贡献

* 当 $k>1$ 时，连续段两端的字符与 ```G``` 相邻，因此对 $b$ 有 $2$ 的贡献；连续段里的所有字符都与 ```B``` 相邻，对 $a$ 有 $k$ 的贡献。

* 注意连续段个数必须为偶数，若为奇数的话一定会有两个字符相同的连续段相邻,就会不合法。


由于上面的分类贡献比较复杂，因此考虑对于总数（$a+b$） 的贡献。当连续段的长度为 $1$ 时，对 $a+b$ 有 $1$ 的贡献；当连续段的长度为 $k>1$ 时，对 $a+b$ 有 $k+2$ 的贡献。

因此若有 $t$ 个大于 $2$ 的连续段，$a+b$ 的总数就为 $n+2t$。

> 因此 $2|t,t\ge 0$，所以若 $a+b<n$ 或 $2\nmid a+b-n$ 就无解。

现在，我们知道了 $t$ 的表达式：$t=\frac{a+b-n}{2}$。

然后似乎很难讨论，那么我们尝试挖掘 $a,b$ 和 $t$ 的性质。观察 $a,b$ 的定义可得

* 因为总人数小于等于 $n$，因此 $0\le a,b \le n$。

* 有 $n-b\le 0,n-a\le 0$，即 $\frac{a+(n-b)}{2}=t \le  \frac{a}{2} $，变形一下有： $2\times t\le a$。

* 同理，有 $2\times t \le b$

但这样还不够，一个常见的构造想法是先构造出一个基础解，再在上面进行增添。那么一个朴素的思路就是往联通块里面插数。那么手模一下，有：

* 当一个连续段的个数大于 $1$ 时，假设字符为 ```B```。往里面插一个相同的字符，只会使得 $a$ 的值增加 $1$。

那么我们可以首先创建 $t$ 个长度为 $2$ 的连续段。注意到上面的性质，也就是只要有一个连续段就能单独调整 $a$ 或 $b$，那么我们肯定保证要给每个字符至少一个连续段。

注意到 $a,b\ge 2t$，即当 $t>1$ 时是上面的想法可能的，那么我们先讨论这种情况。由于 $a,b \ge 2t$，一个暴力的想法是直接给 $a,b$ 分 $\frac{t}{2}$ 个上下浮动的连续段。

当 $2\nmid t$ 时，我们规定一个字符分到 $\frac{t+1}{2}$ 个段（设是字符 ```B```），另一个字符分到 $\frac{t-1}{2}$（设是 ```G```）。因为 $t$ 为奇数，还需要额外增加一个长度为 $1$ 的连续段（否则有两个连续段会合并），字符为分到连续段数小的那个（假设为 ```G```）。那么我们现在对于 $a$ 已经有 $2t+1$ 的贡献，$b$ 已经有 $2t$ 的贡献。由于 $a,b\ge 2t$，也就是说若满足 $a>2t$ 。因此我们的当前构造不会不合法的。由于我们能任意增加 $a$ 或 $b$ 的值（往任意一个长度大于等于 $2$ 的连续段里面插数），因此构造是合法的。同理可以构造 $b>2t$。

考虑 $a=b=2t$ 的情况怎么办。推一下式子，有：$a=b=a+b-n,a=b=n$。由于 $t$ 为奇数，设 $t=2k+1$，那么 $n=2t=2(k+1)=4k+2$，即 $n$ 在模 $4$ 意义下的模数为 $2$。

那么考虑 $a,b$ 的定义，因为 $a=b=n$，一个字符最多产生 $2$ 的贡献，也就是说任意一个位置的相邻的两个字符都不同。假设答案中位置为 $i$ 的字符为 $v_i$。有 $v_1!=v_3,v_3!=v_5,v_1=v_5$，即 $v_1=v_{4k+1}=v{(4k+2)-1}=v_{n-1}$，而 $v_1!=v_{n-1}$，就导出了矛盾。

因此 $a=b=2t$ 的情况不合法。对于 $2|t$ 的情况，同理讨论即可。

> 当 $t>1,2\mid t$ 时，初始设置 $t$ 个长度为 $2$ 的连续段，其中 $\frac{t}{2}$ 个连续段的颜色为 ```B```，$\frac{t}{2}$ 个连续段的字符为 ```G```。那么对于 $a,b$ 的贡献已经为 $2t$

> 其次我们往其中一个字符为 ```B``` 的连续段放入 $a-2t$ 个字符，往其中一个字符为 ```G``` 的连续短放入 $b-2t$ 个字符。

>当 $t>1,2\nmid t$ 时，若 $a=b=2t$，不合法，否则设 $a>b$，设置长度为 $2$ 的连续段 $t$ 个， $\frac{t+1}{2}$ 个连续段的字符为 ```B```，$\frac{t-1}{2}$ 个连续段的字符为 ```G```。再增加一个长度为 $1$ 的连续段，字符为 ```G```。然后分给其中一个字符为 ```B``` 的连续段 $a-2t-1$ 个字符，分给其中一个字符为 ```G``` 的连续短 $b-2t$ 个字符。


然后分类讨论 $t=0,1$ 的情况。

> 当 $t=0$ 时，那么每个连续段的长度为 $1$，因此若 $n$ 为奇数，则至少为出现一个长度为 $2$ 的连续段，无解。那么 $n$ 为偶数，分配了 $\frac{n}{2}$ 个 ```B``` 和 ```G```。易得 $a=b=\frac{n}{2}$ 时合法，否则不合法。


> 当 $t=1$ 时，设一共有 $2x$ 个连续段。其中 $x$ 个连续段的字符为 ```B```，另外的为 ```G```。假设 $a> b$，那么抽出其中一个字符为 ```B``` 的连续段，加入一个字符。那么此时对 $a$ 的贡献为 $x+2$，对 $b$ 的贡献为 $x+1$。由于 $a> b= x+1$，有 $a\ge x+2$。因此合法。当 $a<b$ 时同理。

> 当 $a=b$ 时，由于上面的构造是唯一解，所以不合法。（注意数据没有这个情况）


然后这题就做完了 QAQ。

## 代码

注意一下优先级：

```1?putchar('B'),putchar('B'):putchar('G'),putchar('G')```

的输出为 ```BBG```。


```cpp
#include<bits/stdc++.h>
#define pc putchar
using namespace std;
const int N=1e5+1e3;
int n,a,b;
void print(){puts("Impossible");exit(0);}
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    // a 个孩子站在一个男孩旁边
    // b 个孩子站在一个女孩旁边
    if(a+b<n||((a+b-n)&1))print();
    if(a==0||b==0)
    {
        if(a+b!=n)print();
        if(a==0)for(int i=1;i<=n;i++)pc('G');
        if(b==0)for(int i=1;i<=n;i++)pc('B');
        exit(0);
    }
    int t=a+b-n>>1;
    if(t==0)
    {
        if(n%2||a!=n/2||b!=n/2)print();
        for(int i=1;i<=n;i++)pc(i&1?'G':'B');
        exit(0);
    }
    if(t==1)
    {
        if(a==b)print();
        if(a>b)
        {
            for(int i=1;i<=a-b+1;i++)pc('B');
            for(int i=1;i<=n-(a-b+1);i++)pc(i&1?'G':'B');
        }
        if(a<b)
        {
            for(int i=1;i<=b-a+1;i++)pc('G');
            for(int i=1;i<=n-(b-a+1);i++)pc(i&1?'B':'G');
        }
        exit(0);
    }
    if(t%2==0)
    {
        a-=2*t;b-=2*t;
        for(int i=1;i<=a+2;i++)pc('B');
        for(int i=1;i<=b+2;i++)pc('G');
        for(int i=1;i<=t-2;i++)pc(i&1?'B':'G'),pc(i&1?'B':'G');
        exit(0);
    }
    a-=2*t;b-=2*t;
    if(!a&&!b)print();
    if(a)
    {
        for(int i=1;i<=a+1;i++)pc('B');
        for(int i=1;i<=b+2;i++)pc('G');
        for(int i=1;i<=t-2;i++)pc(i&1?'B':'G'),pc(i&1?'B':'G');
        pc('G');
        exit(0);
    }
    if(b)
    {
        for(int i=1;i<=b+1;i++)pc('G');
        for(int i=1;i<=a+2;i++)pc('B');
        for(int i=1;i<=t-2;i++)pc(i&1?'G':'B'),pc(i&1?'G':'B');
        pc('B');
        exit(0);
    }
    return 0;
}
```

## 后记

在写题时，突然想起了 [P6892 [ICPC2014 WF]Baggage](https://www.luogu.com.cn/problem/P6892)。虽然说两个构造方法不同，但是分类讨论的痛苦是相同的。

---

## 作者：foreverlasting (赞：0)

题意：$n$ 个孩子围成一圈，其中恰有 $x$ 个人的两侧至少有一个男孩，恰有 $y$ 个人的两侧至少有一个女孩，问是否有可能做到。如果可能，并给出一组构造。

做法：容易注意到除了 $x=0$ 或 $y=0$ 以外，一定是一段男一段女间隔的，且男女分别段数一样 ( 因为是环 )。不妨设段数为 $m$，然后男性每一段是 $a_i$，女性是 $b_i$，于是就能容易写出 $x,y,n$ 关于 $a,b$ 的表达式，即：

$$
\sum_{i=1}^m a_i+b_i=n $$
$$
\sum_{i=1}^m a_i-\sum_{i=1}^m [a_i=1]+2m-\sum_{i=1}^m [b_i=1]=x$$
$$
\sum_{i=1}^m b_i-\sum_{i=1}^m [b_i=1]+2m-\sum_{i=1}^m [a_i=1]=y
$$
稍微做一下解释，第一个式子就是总人数为 $n$，第二个式子的前半部分是，对每一段男性而言，若这一段的人数超过了一，则它们相邻有男性的人数就是 $a_i$，否则为零。后半部分是，对于一段女性而言，最两端的女性一定有男性相邻，而 $b_i=1$ 最两端的女性是同一个人，所以会有减法。第三条式子同理。

发现我们要构造的东西不少，但可以整体去考虑。不妨设 $\sum_{i=1}^m [a_i=1]=p,\sum_{i=1}^m [b_i=1]=q,\sum_{i=1}^m a_i=A,\sum_{i=1}^m b_i=B$，于是可以改写一下式子，即
$$
A+B=n$$
$$
A+2m-p-q=x$$
$$
B+2m-p-q=y$$

注意到后两式有许多部分一致，所以对后两式减一减，加一加，有
$$
A-B=x-y$$
$$
A+B+4m-2(p+q)=n+2m-2(p+q)=x+y
$$
于是能得到一个关于 $p+q$ 的式子，即 
$$
p+q=\frac{4m+n-(x+y)}{2}
$$
这里就蕴含了一些有解的条件，首先 $n-(x+y)$ 要为偶数。同时注意到 $p,q\in [0,m]$，所以 $n-(x+y)\leq 0$。

紧接着，我们知道 $p$ 的取值会限制 $A$，除却 $p=m$ 这种大力限制外，剩下的就是 $p<m$ 的情况了，此时 
$$
A=\sum_{i=1}^m a_i=p+\sum_{i=1}^{m-p} a_i\geq p+2(m-p)=2m-p
$$
同理 $B\geq 2m-q$。

将这两条不等式带回最初的等式，有 
$$
A+B=n\geq 4m-p-q$$
$$
A=x+p+q-2m\geq 2m-p\implies x\geq 4m-2p-q$$
$$
y\geq 4m-p-2q
$$
后两个加一加，有
$$
x+y\geq 8m-3(p+q)\implies p+q\geq \frac{8m-x-y}{3}
$$
代入前面得到的 $p+q$ 的等式，有 $\frac{4m+n-x-y}{2}\geq \frac{8m-x-y}{3}$，化简有
$$
m\leq \frac{3n-x-y}{4}
$$
说句实在话，其实我也不知道我在干什么，但到了这一步的时候我觉得我已经基本掌握了所有情况，就没有往下思考了。紧接着，我枚举了 $m$，根据 $x\geq 4m-2p-q$ 以及 $p+q$ 的等式，我们可以得到 $p$ 的取值范围。另一方面，由 $q\leq m$，我们可以得到 $p$ 的另一个范围，我在这里贪心地取了 $p$ 的最小值，于是就求出了 $q$，然后就过了这道题。

通过这题后我阅读了别人的题解，我发现别人似乎是直接构造出来的！确实很厉害啊。不过实际上，我这个思路其实是直接构造出了所有可能的合法解，进一步说，所有的不等式推导都是为了减少非法解的判断，从而让复杂度比较优秀，因此通过了这道题。

具体讨论细节可以参考代码，比较清晰。

时间复杂度 $O(n)$。

```cpp
//2022.9.22 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
namespace MAIN {
	int n,x,y;
	inline bool solve(const int &m){
		int pq=(4*m+n-x-y)/2;
		int A=4*m-x,B=4*m-y;
		A-=pq,B-=pq;
		A=max(A,0),B=max(B,0);
		if(A+B>pq)return 0;
		if(A>m||B>m)return 0;
		int p=max(A,pq-m),q=pq-p;
		A=x+p+q-2*m,B=y+p+q-2*m;
		if(A<2*m-p)return 0;
		if(B<2*m-q)return 0;
		if(A>n)return 0;
		if(B>n)return 0;
		if(m==p){
			if(A!=m)return 0;
		}
		if(m==q){
			if(B!=m)return 0;
		}
		for(int i=1;i<m;i++){
			if(i<=p)putchar('B'),A--;
			else putchar('B'),putchar('B'),A-=2;
			if(i<=q)putchar('G'),B--;
			else putchar('G'),putchar('G'),B-=2;
		}
		for(int i=1;i<=A;i++)putchar('B');
		for(int i=1;i<=B;i++)putchar('G');
		puts("");
		return 1;
	}
	inline void MAIN(const int &Case) {
		n=read(),x=read(),y=read();
		if(x+y<n){puts("Impossible");return;}
		if((x+y-n)&1){puts("Impossible");return;}
		if(x==0){
			if(y==n){
				for(int i=1;i<=n;i++)putchar('G');
				puts("");
			}
			else puts("Impossible");
			return;
		}
		if(y==0){
			if(x==n){
				for(int i=1;i<=n;i++)putchar('B');
				puts("");
			}
			else puts("Impossible");
			return;
		}
		int m=3*n-(x+y);
		m/=4;
		if(m<=0){puts("Impossible");return;}
		for(int i=m;i>=1;i--)if(solve(i))return;
		puts("Impossible");
	}
}
```



---

