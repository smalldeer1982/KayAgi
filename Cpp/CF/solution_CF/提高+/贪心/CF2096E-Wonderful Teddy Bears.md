# Wonderful Teddy Bears

## 题目描述

你是 $n$ 只泰迪熊的骄傲主人，它们被排成一列放在架子上。每只泰迪熊的颜色是黑色或粉色。

如果所有黑色泰迪熊都位于所有粉色泰迪熊的左侧，则称这种排列是美丽的。换句话说，不存在一对索引 $(i, j)$（$1 \leq i < j \leq n$）使得第 $i$ 只泰迪熊是粉色且第 $j$ 只泰迪熊是黑色。

你希望将这些泰迪熊重新排列成美丽的顺序。由于你够不到架子，但幸运的是，你可以向机器人发送指令来移动泰迪熊。在单条指令中，机器人可以：

- 选择一个索引 $i$（$1 \le i \le n - 2$），并将位置 $i$、$i + 1$ 和 $i + 2$ 的泰迪熊重新排列，使得所有黑色泰迪熊位于所有粉色泰迪熊的左侧。

最少需要多少条指令才能完成重新排列？

## 说明/提示

对于第一个测试用例，所有泰迪熊都是粉色。因此，排列已经是美丽的，答案为 $0$。

对于第二个测试用例，所有黑色泰迪熊已经位于所有粉色泰迪熊的左侧。因此，答案为 $0$。

对于第三个测试用例，我们可以执行 $1$ 条指令，选择 $i = 1$。

执行指令后，颜色序列从 $\texttt{PPB}$ 变为 $\texttt{BPP}$，任务完成。

对于第四个测试用例，我们可以执行 $5$ 条指令如下：

- $i = 1$：$\texttt{}\color{magenta}{\texttt{PPB}}\texttt{PPBB} \rightarrow \texttt{}\color{magenta}{\texttt{BPP}}\texttt{PPBB}$
- $i = 5$：$\texttt{BPPP}\color{magenta}{\texttt{PBB}}\texttt{} \rightarrow \texttt{BPPP}\color{magenta}{\texttt{BBP}}\texttt{}$
- $i = 4$：$\texttt{BPP}\color{magenta}{\texttt{PBB}}\texttt{P} \rightarrow \texttt{BPP}\color{magenta}{\texttt{BBP}}\texttt{P}$
- $i = 3$：$\texttt{BP}\color{magenta}{\texttt{PBB}}\texttt{PP} \rightarrow \texttt{BP}\color{magenta}{\texttt{BBP}}\texttt{PP}$
- $i = 2$：$\texttt{B}\color{magenta}{\texttt{PBB}}\texttt{PPP} \rightarrow \texttt{B}\color{magenta}{\texttt{BBP}}\texttt{PPP}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
PPP
3
BPP
3
PPB
7
PPBPPBB
15
BPBPBBBBBPBBBBB```

### 输出

```
0
0
1
5
14```

# 题解

## 作者：wptt (赞：1)

本题解是官方题解思路。

人菜没想出来怎么做😞。

把黑的看作 $0$，粉的看作 $1$。

什么情况最优秀？
>  $110$ 或者 $100$ 的情况，这样每次能够直接减少两个逆序对，其它情况只能减少一个，称它为**最优操作**。

现在考虑做完这个最优操作后序列的样子。

因为它不存在 $110$ 和 $100$ 了，那么就只会出现 $101, 010, 111, 000, 011, 001$ 再整理一下就是 $00000 \cdots 00001010101010111 \cdots 111$ 就是两边已经排好序了，中间会出现一段 $01$ 交替的玩意。

这就启发我们去考虑 $01$ 交替的情况，有一个想法是将其转化为最优操作来执行，考虑最优操作有什么性质，对于 $0110$，发现忽略掉 $11$ 后的 $00$ 与 $0110$ 中 $00$ 的位置的奇偶性不变，这就启发我们考虑序列中 $0$ 的位置的奇偶性关系。

现在我们假设 $a$ 为序列中 $0$ 的数量，$b$ 为序列中 $0$ 在偶数位置的数量。

那么我们最终会要让 $b$ 变成 $\lfloor \frac{a}{2} \rfloor$。

考虑执行一次 $010$ 或者 $101$ 会让一个 $0$ 的奇偶性发生改变，也就是只需要操作 $| \lfloor \frac{a}{2} \rfloor - b |$ 次，就能让 $b$ 变成 $\lfloor \frac{a}{2} \rfloor$。

我们知道最优操作的次数是和逆序对个数相关，观察操作 $010$ 或者 $101$ 会减少一个逆序对，总共会减少 $| \lfloor \frac{a}{2} \rfloor - b |$ 对。
操作到这里序列中所有 $01$ 交替的序列就都没有了，都变成了 $110$ 和 $011$。
这个时候就好统计答案了，就是经过 $010$ 和 $101$ 操作后，序列中逆序对个数除以 $2$。

---

## 作者：Mr_罗 (赞：0)

首先题目的要求等价于把原序列逆序对数（设为 $X$）归零，考察所有可能的操作发现只有 `PBB` 和 `PPB` 会让逆序对数减少 $2$ ，因此一个基本的贪心思路是优先做这两个「最优操作」。

考虑什么情况下无法做最优操作，发现当且仅当序列变成了 `BB...B PBPB...PB PP...P` 。下面思考如何把 `PBPB...PB` 变成 `BB...BPP...P` ：

- 每次做一个 `BPB/PBP` 造一个 `BPPB` 出来，接着不停做 `PPB` 直到又无法做最优操作。重复直到全对为止。

发现 `BPB/PBP` 会让一个 `B` 的位置的奇偶性发生改变而两种最优操作不会，因此做 `BPB/PBP` 的次数（设为 $Y$）为实际在奇数位置上的 `B` 的个数与应该在奇数位置上的个数的差，这个可以简单求出。而每做一次 `BPB/PBP` 都会让逆序对数减一，因此最优操作的总次数为剩下的逆序对数除以二，即 $\frac{X-Y}{2}$ 。

因此答案为 $\frac{X-Y}{2}+Y=\frac{X+Y}{2}$ ，时间复杂度是求 $X,Y$ 所需的 $\mathcal O(n)$ 。

```cpp
rd(n), rds(s + 1); // input
int a = 0, b = 0; ll ans = 0;
per(i, n, 1) if (s[i] == 'B') a++, b += !(i & 1); else ans += a;
prs((ans + abs((a >> 1) - b)) >> 1); // output
```

---

## 作者：conti123 (赞：0)

我们发现最优策略肯定是 `PPB` 变成 `BPP` 或者 `PBB` 变成 `BBP`。

我们定义 $f(s)$ 表示序列 $s$ 需要的调换次数，即 `PB` 变成 `BP` 记为一次调换次数。

我们记 $a$ 为整个字符串中 `B` 的个数，$b$ 为整个数组中偶数位置 `B` 的个数。

那么在最终 $b$ 会变成 $\left \lfloor \frac{a}{2} \right \rfloor$，发现最优策略无法改变 $b$ 的大小，所以需要另外的操作如 `PBP` 变成 `BPP` 或者 `BPB` 变成 `BBP`，这会让 $b$ 减 $1$。

所以需要 $\left| \left \lfloor \frac{a}{2} \right \rfloor -b \right|$ 次这样的操作。

那么剩下的就是 $\frac{f(s)-\left| \left \lfloor \frac{a}{2} \right \rfloor -b \right|}{2}$ 次最优策略了。

可以证明分母一定是个偶数。

答案就是两者相加。

```cpp
int n;
string s;
void solve(){
	cin>>n>>s;
	s=" "+s;
	int cnt1=0,cnt2=0,ans=0;
	for(int i=n;i>=1;i--){
		if(s[i]=='B'){
			cnt1++;
			if(!(i&1))
				cnt2++;
		}
		if(s[i]=='P')
			ans+=cnt1;
	}
	int o=abs(floor(cnt1/2.0)-cnt2);
	cout<<(ans+o)/2<<"\n";
}
```

---

