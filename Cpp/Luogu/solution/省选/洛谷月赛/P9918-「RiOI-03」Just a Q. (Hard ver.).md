# 「RiOI-03」Just a Q. (Hard ver.)

## 题目背景

「Yes, I am Q.」

面前的小 R 莞尔一笑。

+ 保证本题的任何合理的部分分或正解的 std + spj 均可以在当前数据下，$900$ ms 的时间限制、$32$ MB 的空间限制内正确运行并获得 AC 状态。
+ 本题不添加仅为无意义地卡满 spj 运行时间的 hack 数据。

**请注意，本题只有约束范围与普通版不同，且两个版本的约束范围并不完全重叠。**

## 题目描述

**这是一道交互题。**

小 R 有一个变量 $Q$。$Q$ 初始为 $0$。

小 R 有 $n$ 个隐藏的整数 $q_1 \dots q_n$，满足 $1 \leq \lvert q_i \rvert \leq V$，且有且仅有一个 $i$ 满足 $q_i \lt 0$，而面前的你，需要得出这个满足 $q_i \lt 0$ 的下标 $i$。

小 R 承诺不会让你以仅仅 $\frac{1}{n}$ 的几率盲猜，所以她可以允许你进行最多 $k$ 次询问。每次询问，你可以向小 R 给出**可重**正整数集合 $S$ 满足 $0 \leq \lvert S \rvert \leq S_{\max}$ 且 $\forall i \in S, i \leq n$，她会计算 $M = \prod\limits_{i\in S}q_i$，然后让 $Q \leftarrow Q + M$。特殊地，若 $S$ 为空集，则 $M = 1$。

一次询问后，小 R 会向你给出此时的 $\text{sgn}(Q)$（为 `+`，`-` 或 `0`），表示 $Q$ 的符号。具体地，若 $Q \gt 0$，小 R 返回 `+`；若 $Q \lt 0$，小 R 返回 `-`；否则返回 `0`。

请你在不超过 $k$ 次询问后，找到那个满足 $q_i \lt 0$ 的下标 $i$。

**保证对于所有数据，满足 $q_i \lt 0$ 的下标 $i$ 是在 $[1, n]$ 内均匀随机选取的。请注意报告下标属于一次询问。**

## 说明/提示

### 样例解释 1

$q = \{-1, 1, 4, 5, 1, 4\}$。

### 数据规模与约定

**本题采用捆绑测试。**

| 子任务编号 | $n \leq$ | $T \leq$ | $k = $ | $S_{\max} = $ | 分值 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $0$ | $200$ | $500$ | $20$ | $20n + 1$ | $11$ |
| $1$ | $1000$ | $50$ | $41$ | $8n + 10$ | $25$ |
| $2$ | $1000$ | $50$ | $50$ | $6n + 10$ | $30$ |
| $3$ | $10^4$ | $10$ | $39$ | $\lceil 1.5n\rceil + 10$ | $34$ |

对于子任务 $0, 1, 3$，若通过所有测试点则获得全部分数，否则获得 $0$ 分。

对于子任务 $2$：

+ 你需要保证你所使用的实际操作次数 $k'$ 满足 $0 \leq k' \leq 50$。
+ 你需要保证你所使用的实际操作次数 $S'$ 满足 $0 \leq S' \leq 6n + 10$。
+ 单个测试点的得分为 $\left(1 - \max(\frac{\max k' - 35}{20}, \max(\frac{S' - 3n - 10}{4n + 1}), 0)\right)\times 30$。
+ Subtask 的得分取所有测试点的得分最小值。

对于所有数据，$1 \leq V \leq 10^6$，$1 \leq n \leq 10^4$，$1 \leq T \leq 500$，**注意由于交互库限制 $\bm{n, T}$ 不会同时取到最大值**；此外，对每个子任务 $k, S_{\max}$ 的值已经给出。

## 样例 #1

### 输入

```
1
6 6 6

-

-

-

+

0


```

### 输出

```


? 1 1

? 5 1 2 3 4 5

? 3 2 4 6

? 1 4

? 3 1 5 6

! 1```

# 题解

## 作者：irris (赞：6)

有人觉得 Hard Ver 比 Easy Ver 简单，哎。

设上一次询问的集合 $S$。我们使用 $\lang S \rang$ 表示 $S$ 内元素的乘积。同时，考虑维护 $S$ 的符号。

我们维护 $\lvert Q \rvert \in [0, \lvert\lang S \rang\rvert]$，这是一个看起来很自然的想法，因为我们就可以比较少的减小 $Q$ 对后续状态的影响。

根据 Easy Ver 的思路，施二分 $[l, r]$。考虑把当前区间集合分成两半 $A, B$。首先，令 $Q \gets Q + \lang S\rang\cdot\lang A\rang$。如果 $Q$ 改变了符号，那么此时一定有 $\lang S \rang \cdot \lang A \rang$ 的符号是确定的。令 $S \gets S \cup A$ 后继续找到相应的一部分二分即可。

否则，$Q$ 没有改变符号，这说明一定有 $\lang S\rang \cdot \lang A \rang$ 与原来的 $Q$ 同号，我们已经确定了负号存在于 $A$ 或 $B$ 中。因为这个时候 $\frac{\lang S\rang \cdot \lang A \rang}{\lvert Q\rvert}$ 其实也不是很大，那么我们由于仿照上例需要给 $Q$ 的符号改变方便后续维护，所以令 $S \gets S \cup A \cup B$，这样 $S$ 的符号就变化掉了，我们最多实行两次 $Q \gets Q + S$ 就可以把 $Q$ 的符号变掉，这样同样形成了易于维护的形式。

朴素实现是 $S_{\max} \leq n + \lceil \frac n2 \rceil + \lceil \frac n4 \rceil + \cdots \leq 2n + \mathcal O(\log_2 n)$ 的，但是注意到我们可以先行询问一次 $[1, \lceil\frac n2\rceil]$ 来找到负号的位置，所以就变成了 $\frac n2 + 2(\frac n2 + \mathcal O(\log_2 n)) = 1.5n + \mathcal O(\log_2 n)$，非常优秀。

实际上没有卡交互次数，反正都是期望 $2.5n$，就直接保证负号位置随机了。

Subtask 0 特判乘积为 $-1$ 后二分，Subtask 1 是古老做法被 srz 一拳爆了（想要看的可以私聊我），Subtask 2 是增加区分度用的。

```cpp
std::vector<int> S;
inline char query(int l = 1, int r = 0) {
	std::cout << "? " << S.size() + (r - l + 1) << ' ';
	for (int i : S) std::cout << i << ' ';
	for (int i = l; i <= r; ++i) std::cout << i << ' ';
	std::cout << std::endl;
	char x; std::cin >> x; return x;
}
inline void pb(int l, int r) { for (int i = l; i <= r; ++i) S.push_back(i); }

inline char reverse(char ch) { return ch == '+' ? '-' : ch == '-' ? '+' : ch; }
inline char func(char ch1, char ch2) { return ch1 == '0' ? ch2 : ch1; }
void solve() {
	int N, K, Smax; std::cin >> N >> K >> Smax; S.clear();
	if (N == 1) {
		std::cout << "! 1" << std::endl;
		return;
	}
	pb(1, pos[N]); char lst = query(), Ssgn = lst;
	int l = 1, r = N; if (lst == '+') l = pos[N] + 1; else r = pos[N];
	while (l < r) {
		int mid = l + r >> 1; char now = query(l, mid);
		if (now != lst) {
			char Nsgn = func(reverse(lst), now);
			pb(l, mid);
			if (Ssgn == Nsgn) l = mid + 1; else r = mid, Ssgn = Nsgn;
		} else {
			char Asgn = lst == Ssgn ? '+' : '-', orig = now;
			pb(l, mid), pb(mid + 1, r), Ssgn = reverse(Ssgn);
			while ((now = query()) == orig);
			if (Asgn == '+') l = mid + 1; else r = mid;
		}
		lst = now;
	}
	std::cout << "! " << l << std::endl;
}
```

其中 $pos_i$ 是提前 $\mathcal O(n^2)$ 预处理出来的最优下标，可以保证通过 Subtask，不过反正我数据里 $n$ 是一定范围和一定概率随的，$p$ 是 shuffle 的，所以似乎并不很有必要。

---

## 作者：lgvc (赞：6)

考虑分治求出 $<0$ 的下标。假设现在已经确定这个下标在 $[l,r]$ 内。取 $mid=(l+r)/2$。

只需要求出 $[l,mid]$ 中所有数的乘积的正负性。但这并不容易，因为原题的 $Q$ 变量无法复原。

考虑到如果每次询问能乘一个很大的数，（比如第 k 次询问将得到的乘积乘上 $10^{10^{10^{10^k}}}$），那么是否复原已经不重要。

于是考虑如何取到这个巨大的数。比如考虑 $l=1,r=n$ 的情况。此时假设 $a=\prod_{i=l}^{mid}q_i,b=\prod_{i=mid+1}^{r}q_i$。求出 $a,a+b$ 的符号。

此时，递归下去时，巨大的数取 $\max(|a|,|b|)$。这样做是因为 $\max(|a|,|b|)>|a+b|$ （因为 $a,b$ 一正一负）。这让这个巨大的数足够大。

根据 $a,a+b$ 的值求出 $|a|,|b|$ 哪个大，以及要求出的下标在哪一侧。

递归下去，每次把这个巨大的数乘上一个新的东西，这样每一次递归开始时可以认为 $Q=0$。

这样，$S_{max}=n+\lg_n$，$k_{max}=2\lg_n$，可以通过。

细节见代码：

```
#include <bits/stdc++.h>
int T,N,K,S,ff;
std::multiset<int> s1,s2,ss;
int q(std::multiset<int> s) {
	std::vector<int> vq; 
	for(auto it=s.begin();it!=s.end();it++) vq.push_back((*it));
	for(auto it=ss.begin();it!=ss.end();it++) vq.push_back((*it));
	printf("? %d ",vq.size());
	for(int i=0;i<vq.size();i++) printf("%d ",vq[i]);
	printf("\n");fflush(stdout);
	char sq[5];scanf("%s",sq+1);
	if(sq[1]=='-') return -1;
	if(sq[1]=='0') return 0;
	if(sq[1]=='+') return 1;
}
int sv(int l,int r) {
	if(l==r) return l;
	int md=(l+r)>>1;
	std::multiset<int> s1,s2;
	for(int i=l;i<=md;i++) {
		s1.insert(i);
	} 
	for(int i=md+1;i<=r;i++) {
		s2.insert(i);
	} 
	int a=q(s1);
	int b=q(s2);
	if(ff) a=-a,b=-b;
	if(a>=0) {
		if(b>=0) {
			for(int i=l;i<=md;i++) ss.insert(i);
		} else {
			for(int i=md+1;i<=r;i++) ss.insert(i);	
			ff^=1;		
		}
		return sv(md+1,r);
	} else {
		if(b<=0) {
			for(int i=l;i<=md;i++) ss.insert(i);
			ff^=1;
		} else {
			for(int i=md+1;i<=r;i++) ss.insert(i);			
		}
		return sv(l,md);	
	}
}
signed main(void) {
    scanf("%d",&T);
    while(T--) {
    	ss.clear();ff=0;
    	scanf("%d %d %d",&N,&K,&S);
    	printf("! %d\n",sv(1,N));
    	fflush(stdout);
	}
    return 0;
}
```


---

## 作者：vzcx_host (赞：1)

如果询问之间没有任何影响，我们可以直接二分解决，询问次数 $\lceil\log n\rceil+1$。

现在考虑如何消除询问之间的影响。在每次询问前将变量 $Q$ 还原回 $0$ 不太可能，因此考虑在每次修改时增加修改幅度来达到消除影响的效果。

尽管我们可以大量增加询问位，但很遗憾，如果 $|q_i|=1$，增加更多的询问位没有任何意义。我们考虑“增加询问位”和“降低 $|Q|$ 的值”二者兼得，可以发现对于集合 $S$，设其补集为 $T$，则 $S$ 的乘积与 $T$ 的乘积必为一正一负，加和后 $|Q|$ 必然小于 $S$ 和 $T$ 的乘积的绝对值中较大者。考虑将较大者加入常驻集合$R$，在接下来所有的询问中都把 $R$ 加入询问即可。

考虑这样做为什么是对的，定义 $\operatorname{Mul}(S)=|\prod\limits_{i\in S}q_i|$，若某次操作前 $|Q|<\operatorname{Mul}(R)$，操作时变化幅度至少为 $\operatorname{Mul}(R)$，$Q$ 无法为询问带来任何影响；操作后 $|Q|$ 至多变化 $(\max(\operatorname{Mul}(S),\operatorname{Mul}(T))-1)\times \operatorname{Mul}(R)$，而 $\operatorname{Mul}(R)$ 一定会增加这么多，因此在操作后 $|Q|<\operatorname{Mul}(R)$ 仍然成立。第一次操作前 $Q=0,\operatorname{Mul}(R)=1$，这样做没有任何问题。

询问次数 $K_{\max}=2\lceil\log n\rceil+1$，集合上限 $S_{\max}=n+\lceil\log n\rceil$。

---

