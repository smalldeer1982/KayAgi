# [NOISG 2023 Finals] Toxic Gene

## 题目背景

**这是一道交互题。**

本题只支持 C++ 提交，建议使用 C++17。

提交时不需要包含 toxic.h 头文件。

为了确保程序正常编译，你需要在你提交的程序开头加上如下函数声明语句：

```cpp
int query_sample(std::vector<int> species);
void answer_type(int x, char c);
```

如遇评测问题，请联系搬题人。

## 题目描述

**建议仔细区分题面中的“种类”和“个体”。**

兔子 Benson 的飞机被有害病毒侵袭了，他必须对此展开调查！

Benson 发现了 $n$ 种病毒，每种病毒恰好属于三个类型之一：普通、强悍和毒害。保证至少有一种毒害病毒。

Benson 必须识别每种病毒的类型。为了分析之，他将使用一个特殊的机器。每一次，他可以选择任意数量的病毒（包括 $0$）制成标本，并将其放入机器中。受机器大小的影响，每个标本里不能有超过 $300$ 个病毒。每个病毒的种类由 Benson 任意指定。

标本放入机器后，其中三个类型的病毒会发生如下反应：

- 当且仅当不存在毒害病毒，普通病毒可以存活。

- 强悍病毒总是存活。

- 毒害病毒产生有害物质并杀死强悍病毒外的所有病毒。因此，毒害病毒总是死亡。

对于每个样本，机器会告诉 Benson 有多少病毒存活。由于机器分析消耗太多时间，Benson 最多只能使用 $600$ 次机器。请帮助 Benson 确定每种病毒的类型：普通、强悍或毒害。


### 实现细节

这是一道交互题。你需要实现如下函数：

- `void determine_type(int n)`

每个测试数据中，该函数最多被调用 $100$ 次，每次调用将对应不同的病毒组合。对于每个测试数据，你必须保证所有调用不超过时间限制和空间限制。

你可以通过调用如下函数完成题目：

- `int query_sample(std::vector<int> species)`
- `void answer_type(int x, char c)`

调用 `query_sample` 函数时，需传入一维数组 `species`，表示标本中你所选择的病毒种类。该数组的大小不能超过 $300$。此外，你可以假定该函数调用结束后，`species` 数组不会改变。

调用 `answer_type` 函数时，需传入一个整数 $x$ 和一个字符 $c$。当你确定第 $x$ 种病毒的类型时，调用该函数，其中 $c$ 是 `R`、`S` 或 `T` 之一，分别表示普通病毒、强悍病毒和毒害病毒。你必须对每种病毒都调用该函数。

下列情况可能导致你收到 Wrong Answer 反馈并立即结束评测：

- `query_sample` 函数或 `answer_type` 函数的调用非法
- `answer_type` 函数给出的病毒种类有误
- `determine_type` 函数结束时，存在某种病毒未被 `answer_type` 确认
- 某次 `determine_type` 函数调用过程中，`query_sample` 被调用了超过 $600$ 次

请注意，题目中的交互库是**非自适应的**，即每个测试数据的答案被提前确定，且不会在交互过程中改变。

## 说明/提示

### 调用示例

假定 $n=5$，第一种病毒和第二种病毒是毒害病毒，第三种病毒和第四种病毒是普通病毒，第五种病毒是强悍病毒。该情况可用字符串 `TTRRS` 表达。

你的函数会被这样调用：

- `determine_type(5)`

一个可能的交互过程如下：

- `query_sample([1,2,3,4,5]) = 1`
所有种类的病毒都被放置在标本中，只有种类 $5$ 的病毒存活，故返回 $1$。

- `query_sample([3,3,4,5]) = 4`
两个“第三种病毒”、一个“第四种病毒”和一个“第五种病毒”被放置在标本中。由于不存在毒害病毒，所有病毒均存活，故返回 $4$。

此时，程序认为其已经确认所有病毒的类型，故进行了如下 $5$ 次调用：

- `answer_type(1,'T')`
- `answer_type(2,'T')`
- `answer_type(3,'R')`
- `answer_type(4,'R')`
- `answer_type(5,'S')`

这些函数都没有返回值。当程序正确地确认了 $n=5$ 种病毒的种类，且未使用超过 $600$ 次询问时，会在该测试点中被认为是正确的。

请注意，该示例仅供展示交互过程，不一定存在合理逻辑。

### 得分细则

设 $t$ 表示毒害病毒的数量。保证测试数据中 $n=300$，$1\leq t\leq 30$。

某测试点中，你的得分与所有 `determine_type` 调用中，询问次数的最大值有关，设为 $m$。

- 当 $m>600$ 时，得分为 $0$。
- 当 $340<m\leq 600$ 时，得分为 $2+7\times \frac{600-m}{260}$。
- 当 $275<m\leq 340$ 时，得分为 $9+15\times \frac{340-m}{65}$。
- 当 $190<m\leq 275$ 时，得分为 $24+22\times \frac{275-m}{85}$。
- 当 $150<m\leq 190$ 时，得分为 $46+54\times \frac{190-m}{40}$。
- 当 $m\leq 150$ 时，得分为 $100$。

### 程序测试

下发文件中有两个数据可供测试。`sample1.txt` 是上文的【调用示例】，`sample2.txt` 中含有一组 $tc=100,n=300$ 的测试数据。请使用 `compile.sh` 编译并运行你的程序。

# 题解

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/P11537)

**题目大意**

> 给定 $n$ 个字符，字符集 $\texttt{R,S,T}$，每次可以选出若干个字符（可重复）并询问：
>
> - 如果询问的字符中有 $\texttt T$，那么会返回 $\texttt S$ 的个数。
> - 否则会返回询问字符的个数。
>
> 在 $150$ 次询问内确定每个字符的种类，每次询问至多选 $300$ 个字符。
>
> 交互器不是自适应的。
>
> 数据范围：$n\le 300$，$\texttt T$ 的个数 $t\le 30$。

**思路分析**

由于交互库不自适应，因此可以随机重排整个序列。

首先 $2n$ 次询问是简单的，询问每个单点得到所有 $\texttt T$，然后每个不为 $\texttt T$ 的字符和 $\texttt T$ 一起询问就能确定是 $\texttt S$ 还是 $\texttt T$。

然后可以优化，由于可以加入重复元素，因此可以用二进制一次性询问多个字符：

- 选出若干个非 $\texttt T$ 字符，对于第 $i$ 个字符选择 $2^{i-1}$ 次，再加上一个 $\texttt T$，得到的结果里二进制为 $1$ 的位对应的字符是 $\texttt S$，否则对应的字符是 $\texttt R$。

由于 $2^8-1<300$，因此一次可以解决 $8$ 个字符，可以做到 $n+n/8$ 次操作。

如果用二分确定每个 $\texttt T$，操作次数 $8t+n/8$。

直接二分未必优秀，可以先套一层分块。

我们 $8$ 个元素分一块，每块先询问一次，如果有 $\texttt T$ 再二分。

此时询问次数不超过 $n/8+3t+n/8$，我们再在这上面进行一些常数优化。

首先首轮分块我们只询问 $8$ 个元素，那么可以用刚刚的二进制做法，如果块中有 $\texttt T$，那么就能确定这个块里所有的 $\texttt S$。

对于每个有 $\texttt T$ 的块，求出最左边的 $\texttt T$，然后右边剩余的元素全部放入集合 $Q$ 中，这些元素字符集为 $\{\texttt R,\texttt T\}$。

然后每次取出 $Q$ 的前 $8$ 个元素，先判定是否有 $\texttt T$ 再二分，把剩下的元素放回 $Q$。

然后对于首次二分中没有 $\texttt T$ 的块，我们在后续的判定与二分过程中，取出 $8$ 个元素然后用用二进制做法，如果这次判定中有 $\texttt T$ 字符，那么这 $8$ 个元素也能被确定。

那么这些没有 $\texttt T$ 的块期望上来说肯定在求 $\texttt T$ 的块的过程中就会被确定。

其次在随机的过程中，如果第一个 $\texttt T$ 的位置比较大，那么被插入 $Q$ 的元素期望并不多。

不妨把询问次数近似看成 $n/8+3t+|Q|/8$，而 $|Q|$ 不妨看作 $t$ 个 $[0,7]$ 的随机变量之和。

如果每个变量都是均匀随机的用一个简单的 dp 能算出询问次数 $\le 146$ 的概率已经超过 $99.9\%$。

如果粗略地考虑每个变量在 $[0,7]$ 上的分布，则询问次数 $\le 147$ 的概率超过 $99.5\%$，$\le 148$ 的概率超过 $99.9\%$。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
int query_sample(vector<int>s);
void answer_type(int x,char c);
mt19937 rnd(time(0));
typedef vector<int> vi;
int sz(vi x) { return x.size(); }
void operator +=(vi &x,vi y) { for(int i:y) x.push_back(i); }
vi I(vi x,int l,int r) { return vi(x.begin()+l,x.begin()+r); }
void pop(vi &x,int m) { x.erase(x.begin(),x.begin()+m); }
char st[305];
void determine_type(int n) {
	vi A; for(int i=1;i<=n;++i) A.push_back(i),st[i]=0;
	shuffle(A.begin(),A.end(),rnd);
	vi R,S,T,RS,RT; vector <vi> G;
	while(A.size()) {
		int m=min(sz(A),8);
		vi q,u;
		for(int i=0;i<m;++i) for(int j=0;j<(1<<i);++j) q.push_back(A[i]);
		int z=query_sample(q);
		if(z==sz(q)) RS+=I(A,0,m);
		else for(int i=0;i<m;++i) {
			if(z>>i&1) st[A[i]]='S';
			else u.push_back(A[i]);
		}
		if(u.size()) G.push_back(u);
		pop(A,m);
	}
	auto chk=[&](vi q) {
		int m=min(sz(RS),8);
		for(int i=0;i<m;++i) for(int j=0;j<(1<<i);++j) q.push_back(RS[i]);
		int z=query_sample(q);
		if(z==sz(q)) return false;
		for(int i=0;i<m;++i) st[RS[i]]="RS"[z>>i&1];
		pop(RS,m);
		return true;
	};
	auto sol=[&](vi q) {
		shuffle(q.begin(),q.end(),rnd);
		int l=0,r=sz(q)-1;
		while(l<r) {
			int mid=(l+r)>>1;
			if(chk(I(q,l,mid+1))) r=mid;
			else l=mid+1;
		}
		for(int i=0;i<=l;++i) st[q[i]]="RT"[i==l];
		return I(q,l+1,sz(q));
	};
	for(auto it:G) RT+=sol(it);
	while(RT.size()) {
		int m=min(sz(RT),8);
		auto it=I(RT,0,m); pop(RT,m);
		if(!chk(it)) for(int i:it) st[i]='R';
		else RT+=sol(it);
	}
	int _=find(st+1,st+n+1,'T')-st;
	while(RS.size()) chk({_});
	for(int i=1;i<=n;++i) answer_type(i,st[i]);
}
```

---

