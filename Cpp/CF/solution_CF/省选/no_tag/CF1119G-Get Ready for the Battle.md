# Get Ready for the Battle

## 题目描述

最近，Evlampy 安装了一款有趣的电脑游戏，其中一个玩法是将军队分成若干小组，然后与敌人的小组作战。我们来考虑这个战斗的简化版本。

在即将到来的战斗中，Evlampy 需要对抗由 $m$ 个小组组成的敌军，第 $i$ 个小组拥有 $hp_i$ 点生命值。

Evlampy 的军队由 $n$ 名相同的士兵组成。在每场战斗前，他需要将自己的军队恰好分成 $m$ 个小组（可以有空组），使得所有小组的总人数为 $n$。战斗按回合进行。在每一回合中，Evlampy 的每个小组会攻击恰好一个敌方小组。因此，每一回合可以用一个长度为 $m$ 的数组 $a_1, a_2, \ldots, a_m$ 来描述，表示第 $i$ 个 Evlampy 的小组攻击第 $a_i$ 个敌方小组。不同的小组可以攻击同一个敌方小组，每一回合可以独立选择数组 $a$。

每一回合后，每个敌方小组的生命值会减少本回合中所有攻击该小组的 Evlampy 小组的士兵总数。当某个敌方小组的生命值降至 $0$ 或更低时，该小组被摧毁。Evlampy 的士兵不会损失生命值。

Evlampy 意识到即将到来的战斗将持续整晚，这让他很沮丧，因为这样他就没有时间完成作业了。现在，Evlampy 希望你编写一个程序，帮助他用最少的回合赢得战斗。你能帮帮他吗？

换句话说，请你找出摧毁所有敌方小组所需的最少回合数，并给出一种可行的方案。你需要给出军队分组的方法，以及每一回合的攻击数组 $a$。

## 说明/提示

第一个样例如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119G/83b26697e1512ab6ed6ffa18c7896b3d481f3fad.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
13 7
6 4 3 7 2 1 5
```

### 输出

```
3
0 1 2 3 1 2 4
2 6 2 4 4 2 4
3 1 7 1 7 7 1
3 1 5 3 7 5 1
```

## 样例 #2

### 输入

```
6 5
3 3 3 3 3
```

### 输出

```
3
3 3 0 0 0
1 2 3 4 5
3 4 5 5 5
5 5 5 5 5
```

## 样例 #3

### 输入

```
7 4
1 5 9 2
```

### 输出

```
3
1 2 4 0
1 4 2 3
2 3 3 3
3 3 3 3```

# 题解

## 作者：Scintilla (赞：9)

**Description**

给定 $n, m$ 和一个长度为 $m$ 的序列 $a$。你可以构造一个长度为 $m$ 的非负整数序列 $s$，满足 $\sum_{i = 1} ^ m s_i = n$。定义一次操作为指定一个长度为 $m$ 的序列 $p$ 满足 $p_i \in [1, m]$，然后对于 $i \in [1, m]$ 令 $a_{p_i} \leftarrow a_{p_i} - s_i$。求所有可能情况中使得最后 $a_i \le 0$ 所需要的最小操作次数及其对应的方案。

$m \le n \le 10^6, \sum a_i \le 10^6$。

**Solution**

首先答案的下界是 $\left\lceil \frac{\sum_i a_i}{n} \right\rceil$，我们考虑能否达到这个下界。一个想法是大致按照 $a$ 的比例分配，但是剩余的不好处理。所以我们考虑每次主要在一或两个数上集中火力。

我们每次最多能够让一个数减少 $n$，为了不造成浪费，我们尝试保证对于 $i < m$ 在放完某些人（不一定是 $m$ 的倍数之后）之后第 $i$ 个数恰好为 $0$。设 $sum_i = \sum_{j = 1} ^ i a_j$，不妨钦定每次都是按从 $1$ 到 $m$ 的顺序放，这等价于 $s$ 存在一个前缀和为 $sum_i$ 模 $n$。对于 $i = m$，因为它是最后一个，所以难免有剩余，所以 $sum_m$ 是没有意义的。又因为要保证 $\sum_i s_i = n$，不妨设 $sum_m = n$。所以我们可以令 $sum_m = n$ 之后把所有的 $sum_i(i < m)$ 对 $n$ 取模的结果排序，结果设为 $r$，然后令 $s_i = r_i - r_{i - 1}(i \le m)$ 即可。

这样我们输出方案只需要无脑放即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define rep(i, s, e) for (re int i = s; i <= e; ++i)
#define drep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

const int N = 1000000 + 10;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = false; c = getchar();}
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int n, m, a[N], r[N], sum, s[N], pos = 1;

int main() {
    n = read(), m = read();
    rep(i, 1, m) a[i] = read(), sum += a[i], r[i] = sum % n;
    r[m] = n, sort(r + 1, r + m + 1);
    rep(i, 1, m) s[i] = r[i] - r[i - 1];
    printf("%d\n", (sum + n - 1) / n);
    rep(i, 1, m) printf("%d ", s[i]);
    puts("");
    rep(i, 1, m) while (a[i] > 0) a[i] -= s[pos], printf("%d%c", i, " \n"[pos == m]), pos = pos % m + 1;
    if (pos > 1) while (pos <= m) printf("%d%c", m, " \n"[pos == m]), ++pos;
    return 0;
}
```

---

## 作者：SIGSEGV (赞：6)

搬运一下[CF官方题解](https://codeforces.com/blog/entry/66411)

最好的情况是除最后一次外都不浪费士兵，因此次数为$\lceil \frac{\sum\nolimits_{i=1}^n{hp}_{i}}{n} \rceil$

考虑构造。首先一开始让所有人打第一个敌人，只要他的血量$<n$了，假设我们有一些兵团的士兵数量总和刚好为敌人剩余血量$k_1$,那么我们就让这些士兵去打敌人1，其余人在同一回合内去打敌人2.然后所有人再去打敌人2. 当敌人2血量$<n$时，假设我们又有一些兵团的士兵数量总和刚好为敌人剩余血量$k_2$，那么我们就让这些士兵去打敌人2，其余人在同一回合去打敌人3......

重复此步骤直到弄死敌人为止。只剩最后一个敌人时可以让所有人都去打他。这样我们的回合数就是$\lceil \frac{\sum\nolimits_{i=1}^n{hp}_{i}}{n} \rceil$

对于$k_1 ... k_n$,使用差分构造。将$k$排序后，令第$1$组的士兵数量为$k_1$,第$i$组$(i\neq1)$士兵数量为$k_i-k_{i-1}$即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,hp[1000005],num[1000005];
int main ()
{
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= m;i++)
		scanf("%d",&hp[i]);
	vector<int> last = {0,n};
	int sum = 0;
	for (int i = 1;i < m;i++)
	{
		sum += hp[i];
		last.push_back(sum % n);
	}
	sort(last.begin(),last.end());
	vector<int> sizes;
	for (int i = 1;i < last.size();i++)
		sizes.push_back(last[i] - last[i - 1]);
	printf("%d\n",(sum + hp[m] + n - 1) / n);
	for (int i = 0;i < sizes.size();i++) printf("%d ",sizes[i]);
	puts("");
	int ptr = 0;
	for (int i = 1;i <= m;i++)
	{
		while (hp[i] > 0)
		{
			hp[i] -= sizes[ptr++];
			printf("%d ",i);
			if (ptr == m)
			{
				ptr = 0;puts("");
			}
		}
	}
	while (ptr && ptr++ != m) printf("%d ",m);
	return 0;
} 
```

对着Rank2的代码写的

---

## 作者：irris (赞：1)

#### CF1119G Get Ready for the Battle

> 有 $m$ 个正整数 $a_1, \ldots, a_m$，你需要构造一个非负整数序列 $s_1, \ldots, s_m$，$\sum s_i = n$，每一轮，你对每个 $1 \leq i \leq m$ 选择一个 $1 \leq j \leq m$ 让 $a_j \gets a_j - s_i$，求最小的轮数使得所有 $a_i \leq 0$，并构造方案。$\sum a_i \leq 10^6$。

提供一个不需要任何注意力的做法。

我们猜想 $\lceil \frac{\sum a_i}{n} \rceil$ 的下界总是能达到。不妨设 $n \mid \sum a_i$。考虑 **逐个确定** $s_i$ 和其每一轮对应消除的位置。于是我们有如下两种消除方式：

- 如果当前剩余 $a$ 最大的某个元素 $a_x$ 不低于剩余未被确定的 $\sum s_i$，让这些元素在新的一轮里都攻击 $a_x$；
- 否则，设还有 $k$ 轮未被确定，于是剩余的 $\sum a_x = k \cdot \sum s_i$，而 $\boldsymbol{a_x < \sum s_i}$，所以我们 **一定能够** 选出 $k$ 个位置 $a_{i_1}, a_{i_2}, \ldots, a_{i_k} > 0$，不妨设 $a_{i_1}$ 是其中最小的元素，我们确定一个 $s_i = a_{i_1}$，并让它在剩下的 $k$ 轮里攻击 $a_{i_1}, \ldots, a_{i_k}$ 即可。

容易发现上述的构造过程没有任何的浪费，可以恰好达到下界。具体实现时，可以用优先队列维护剩余元素的值，因为每取出一个元素 $\sum a_i$ 都至少减少 $1$，时间复杂度 $\mathcal O(\sum a_i \log (\sum a_i))$。

---

## 作者：Fesdrer (赞：1)

容易得到答案的下界为 $\frac{\sum hp_i}n$，考虑构造出达到这一下界的方案。

我们按照敌人顺序一个一个击破，即一开始所有人都去打第一个敌人，等到第一个敌人血量小于 $n$ 时（假设为 $k_1$），让一些总人数为 $k_1$ 的组去击杀第一个敌人，剩下的去攻击第二个敌人，然后所有人再一起攻击第二个敌人，等到第二个敌人血量小于 $n$ 时（假设为 $k_2$），让一些总人数为 $k_2$ 的组去击杀第二个敌人，剩下的去攻击第三个敌人，依此类推，直到最后一个敌人就让所有人都去打他，这样就能达到下界 $\frac{\sum hp_i}n$。

现在的问题是：如何使得每一次都能拼出总人数为 $k_i$ 的组。容易发现我们只需要考虑如何对每个 $i\in[1,m-1]$ 都能拼出总人数为 $(\sum_{j=1}^ihp_j)\bmod n$ 的组。我们考虑差分构造，即将需要构造出的 $m-1$ 个 $(\sum_{j=1}^ihp_j)\bmod n$ 和 $n$ 这 $m$ 个数字从小到大排序，则最终的队伍人数即为排序后的序列的差分。记队伍人数为 $s_1,s_2,\cdots,s_m$。

最后的问题是如何确定一个具体的攻击方案。容易发现，我们只需要依次把 $s_1,s_2,\cdots$ 往第一个敌人攻击，等到第一个敌人被消灭了，从下一个队伍开始攻击第二个敌人，如此循环。因为我们差分的构造，每一个都能精准的把敌人血量消灭到 $0$。这样就做完了。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,sum,hp[N],p[N],s[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)	cin>>hp[i];
	for(int i=1;i<m;i++)	s[i]=p[i]=(p[i-1]+hp[i])%n,sum+=hp[i];
	p[m]=s[m]=n,sum+=hp[m];
	sort(s+1,s+m+1);
	for(int i=m;i>1;i--)	s[i]-=s[i-1];
	cout<<(sum+n-1)/n<<endl;
	for(int i=1;i<=m;i++)	cout<<s[i]<<" ";
	cout<<endl;
	int top=1;
	while(hp[m]>0){
		for(int i=1;i<=m;i++){
			cout<<top<<" ";
			hp[top]-=s[i];
			if(top!=m&&hp[top]<=0)	top++;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1119G)

**题目大意**

> 给定 $s_1\sim s_m$，选取一组 $a_1\sim a_m$，使得 $\sum a_i=n$，每轮操作可以任选 $p_1\sim p_m\in[1,m]$，然后令 $s_{p_i}\gets s_{p_i}-a_i$。
>
> 求让所有 $s_i$ 变成非正数至少要几轮，给出构造。
>
> 数据范围：$n,m,\sum s_i\le 10^6$。

**思路分析**

显然答案的下界是 $\left\lceil\dfrac{\sum s_i}n\right\rceil$，考虑是否能取到。

自然的想法就是先让所有人集中操作 $s_1$，直到 $s_1<n$ 的时候，选取一些 $a_i$ 和恰好为 $s_1$，他们操作 $s_1$，剩余的数操作 $s_2$。

那么我们就要要求 $s_1\bmod n,(s_1+s_2)\bmod n,\cdots,(s_1+\cdots+s_{m-1})\bmod n$ 都可以被若干 $a_i$ 表出。

那么 $a_i$ 取把这 $m-1$ 个数排序后两两元素间的差分即可，构造是简单的。

时间复杂度 $\mathcal O(m\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int x[MAXN],a[MAXN],t[MAXN];
signed main() {
	int m,n,s;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) scanf("%d",&a[i]),t[i]=a[i]+t[i-1],x[i]=t[i]%n;
	x[m]=n,sort(x+1,x+m+1),printf("%d\n",s=(t[m]-1)/n+1);
	for(int i=m;i>1;--i) x[i]-=x[i-1];
	for(int i=1;i<=m;++i) printf("%d ",x[i]); puts("");
	for(int c=1;s--;) {
		for(int i=1;i<=m;++i) {
			printf("%d ",c),a[c]-=x[i];
			if(a[c]<=0) c=min(c+1,m);
		}
		puts("");
	}
	return 0;
}
```

---

