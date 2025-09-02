# Magician and Pigs (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ n $ and $ x $ . You can make hacks only if both versions of the problem are solved.

Little09 has been interested in magic for a long time, and it's so lucky that he meets a magician! The magician will perform $ n $ operations, each of them is one of the following three:

- $ 1\ x $ : Create a pig with $ x $ Health Points.
- $ 2\ x $ : Reduce the Health Point of all living pigs by $ x $ .
- $ 3 $ : Repeat all previous operations. Formally, assuming that this is the $ i $ -th operation in the operation sequence, perform the first $ i-1 $ operations (including "Repeat" operations involved) in turn.

A pig will die when its Health Point is less than or equal to $ 0 $ .

Little09 wants to know how many living pigs there are after all the operations. Please, print the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the operations are equivalent to repeating four times: create a pig with $ 8 $ Health Points and then reduce the Health Points of all living pigs by $ 3 $ . It is easy to find that there are two living pigs in the end with $ 2 $ and $ 5 $ Health Points.

## 样例 #1

### 输入

```
4
1 8
2 3
3
3```

### 输出

```
2```

## 样例 #2

### 输入

```
6
1 5
1 6
2 2
3
1 4
3```

### 输出

```
5```

## 样例 #3

### 输入

```
12
2 1
1 15
1 9
3
1 12
2 2
1 13
3
2 1
1 9
1 8
3```

### 输出

```
17```

# 题解

## 作者：Little09 (赞：9)


想想 Repeat 在干什么。假设现在是第 $i$ 次，目前总共伤害是 $x$（这个 $x$ 很好计算，每次 Repeat 伤害会乘 $2$）。那么经过 Repeat 后，每只目前生命为 $w$ 猪会克隆一个生命为 $w-x$ 的猪。（原因：Repeat 会重新做一遍之前的东西，那么原有的每只猪肯定还会再生成一份且和它保持一致，而它会遭到 $x$ 的攻击，所以可以认为克隆了 $w-x$ 的猪）

那么考虑每一只创造的猪，每个正常的 Attack 操作都有效，而 Repeat 会克隆。这就表示可以先把猪的生命减掉它后面的所有 Attack，再考虑所有克隆。而克隆也就是每次 Repeat 选择减掉 $x$ 或者不剪掉 $x$，合起来一个 $2$ 的若干次方的集合。

假设第一个操作是 Attack。那么每次 Repeat 伤害会乘 $2$，因此在 $\log$ 次后的 Repeat 伤害足以干掉任何一只猪。所以 $\log$ 次后的 Repeat 必须选择不剪掉 $x$。那么枚举 $\log$ 次前的 Repeat 操作的子集就行了，倒着做。可以用前缀和算出对于一只血量 $x$ 的猪，最后会剩几只。也可以暴力枚举一下子集。

但是第一个操作不一定是 Attack！那我们找到第一个 Attack 再做，前面的部分肯定是猪在不停克隆，只要乘上一个系数就行了。

时间复杂度是 $O((n+x)\log x)$。后来验题的时候大多数人写的是 $O((n+x)\log^2 x)$，用 map 或者线段树等维护猪的血量，这样不用倒过来做。原本时限是 1s，验题的时候 @[JohnVictor](https://www.luogu.com.cn/user/254752) 好像跑了 900ms+，我当时还在犹豫要不要卡掉 2log。后来有 F2 之后我就觉得肯定是不卡了，时限放了 2s。

~~有人说可持久化平衡树？我没仔细想~~。

------------

花絮（1）

出这个题是初三的校三模前一天（4.12）懒得复习语文数学了，于是开始画猪。画着画着想把猪给 attack 了，然后就有了这道题（大雾）。

当时晚自习的时候自己做这个题大概胡了 15min？后来想想感觉这题还可以，于是就交给了 @[1kri](https://www.luogu.com.cn/user/235926) 帮我看。我当时给难度是 E，然后 @[1kri](https://www.luogu.com.cn/user/235926) 改成了 E/F，再到 anton 手里就变成 F 了。

---

## 作者：ningago (赞：4)

简化一下操作。

记当前所有 $2$ 操作的权值和为 $t$。

- 操作 $1$：向集合（可重）里插入一个权值 $v$ 的点。
- 操作 $2$：集合里所有数减去 $v$。随后赋值 $t=t+v$。
- 操作 $3$：把集合里的数复制出一个副本，将副本里的所有数减去 $t$，插入到原集合里。随后赋值 $t=2t$。

考虑平衡树直接维护。

每个节点维护权值 $val$ 和出现次数 $cnt$。

前两个操作可以懒标记实现（因为是全局减）。

容易发现，当且仅当 $t\leq V$ 的时候操作 $3$ 有效（$V=2\times 10^5$）。

所有有效的操作 $3$ 至多为 $\log V$ 次，所以暴力插入即可。

但出现了一个问题，就是 $t=0$ 的时候不满足这个限制。

考虑 $t=0$ 时进行操作的意义，也就是全局 $cnt \times 2$，这个也懒标记维护就可以。

复杂度 $O((V+n)\log V)$。

```cpp
#include <cstdio>
#include <cstring>

#define N 2000010
#define mod 998244353
#define int long long

int n;
unsigned int sd = 233;

int rnd()
{
	sd ^= sd << 13;
	sd ^= sd >> 7;
	sd ^= sd << 11;
	return (int)sd;
}

int root,idx;
struct Tree
{
	int ls,rs;
	int val,sz,key;
	int lazy;
	int cnt,mul_lazy;
}tr[N];

#define lson(k) (tr[k].ls)
#define rson(k) (tr[k].rs)

void push(int k,int z)
{
	if(!k)
		return;
	if(tr[k].val > 0)
		tr[k].val += z;
	tr[k].lazy += z;
}

void mul_push(int k,int z)
{
	if(!k)
		return;
	tr[k].mul_lazy = (tr[k].mul_lazy * z) % mod;
	tr[k].cnt = (tr[k].cnt * z) % mod;
}

void pushdown(int k)
{
	if(tr[k].lazy)
	{
		if(lson(k))
			push(lson(k),tr[k].lazy);
		if(rson(k))
			push(rson(k),tr[k].lazy);
		tr[k].lazy = 0;
	}
	if(tr[k].mul_lazy != 1)
	{
		if(lson(k))
			mul_push(lson(k),tr[k].mul_lazy);
		if(rson(k))
			mul_push(rson(k),tr[k].mul_lazy);
		tr[k].mul_lazy = 1;
	}
}

int newnode(int val,int cnt)
{
	tr[++idx].val = val;
	tr[idx].key = rnd();
	tr[idx].cnt = cnt;
	tr[idx].mul_lazy = 1;
	return idx;
}

void split(int k,int val,int &x,int &y)
{
	if(!k)
		x = y = 0;
	else
	{
		pushdown(k);
		if(tr[k].val <= val)
		{
			x = k;
			split(rson(k),val,rson(k),y);
		}
		else
		{
			y = k;
			split(lson(k),val,x,lson(k));
		}
	}
}

int merge(int x,int y)
{
	if(!x || !y)
		return x | y;
	if(tr[x].key <= tr[y].key)
	{
		pushdown(x);
		rson(x) = merge(rson(x),y);
		return x;
	}
	else
	{
		pushdown(y);
		lson(y) = merge(x,lson(y));
		return y;
	}
}
int x,y,z;
void ins(int val,int cnt)
{
	split(root,val,x,y);
	int p = x;
	while(rson(p))
		p = rson(p);
	if(tr[p].val == val)
	{
		tr[p].cnt += cnt;
		root = merge(x,y);
	}
	else
		root = merge(merge(x,newnode(val,cnt)),y);
}

int sta[N],sta1[N],top;

void dfs(int k,int t)
{
	if(!k)
		return;
	pushdown(k);
	sta[++top] = tr[k].val - t;
	sta1[top] = tr[k].cnt;
	if(lson(k))
		dfs(lson(k),t);
	if(rson(k))
		dfs(rson(k),t);
}

int ans = 0;

signed main()
{
	scanf("%lld",&n);
	int t = 0;
	for(int i = 1,op,p;i <= n;i++)
	{
		scanf("%lld",&op);
		if(op == 1)
		{
			scanf("%lld",&p);
			ins(p,1);
		}
		if(op == 2)
		{
			scanf("%lld",&p);
			if(t <= 200000)
				t += p;
			push(root,-p);
		}
		if(op == 3)
		{
			if(t == 0)
				mul_push(root,2);
			else if(t <= 200000)
			{
				top = 0;
				split(root,t,x,y);
				dfs(y,t);
				root = merge(x,y);
				for(int j = 1;j <= top;j++)
					if(sta[j] > 0)
						ins(sta[j],sta1[j]);
			}
			if(t <= 200000)
				t *= 2;
		}
	}
	dfs(root,0);
	for(int i = 1;i <= idx;i++)
	{
		if(tr[i].val > 0)
			ans = (ans + tr[i].cnt) % mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：RyexAwl (赞：2)

考虑动态维护序列中的元素，将其看成多重集 $S$，令 $tag$ 表示考虑当前所有操作，减法操作的影响，初始时 $S=\emptyset$，$tag=0$，那么三个操作可以看成：

1. $S\gets S\cup \{x\}$。

2. 将集合 $S$ 内每个元素减去 $x$。并令 $tag:=tag+x$。

3. 将集合 $S$ 内每个元素 $x$，复制出一个 $x-tag$ 加入集合 $S$ 内，然后令 $tag:=2\times tag$。

最后相当于查询集合 $S$ 内大于 $0$ 的元素个数。

注意到当 $tag>0$ 后，“有用” 的操作 $3$ 至多 $O(\log V)$ 个。因为在进行 $O(\log V)$ 个操作 $3$ 后，再进行操作 $3$ 复制出来的结果一定小于 $0$，那么我们可以不执行。

我们可以通过枚举每个 $1$ 操作，分别计算其贡献（即该操作插入的 $x$ 在后续复制操作中的贡献），不同的 $1$ 操作贡献是独立的。

对于一个 $1$ 操作，我们只在意其后面的 $2$ 操作和 $3$ 操作，我们可以将连续的一段 $2$ 操作缩成一个操作，那么我们关心的操作序列形如：

$$
123323232323223....
$$

这里直接的想法是暴力模拟，因为至多 $O(\log V)$ 个 $tag$ 非 $0$ 的操作 $3$。但是这样其实是不太行的，因为每次 $3$ 操作集合大小都要翻倍，这样单个 $1$ 的复杂度就到 $O(V)$ 了。

但是注意到我们可以递归子问题，$x$ 经过操作 $2$ 变为了形如 $x-w$ 的子问题，$x$ 经过操作 $3$ 分解成 $x-w$ 和 $x$ 的子问题。并且我们可以把 $2$ 的连续段缩掉。具体实现时先从前向后扫处理出每个操作 $3$ 的 $tag$，然后再从后向前扫，维护 $f_i$ 表示 $x=i$ 时做从前向后做一个后缀的 $2$ 和 $3$ 操作最后对答案的贡献（即有几个大于 $0$ 的元素），扫到一个 $3$ 就更新信息，对于 $tag$ 大于 $0$ 的暴力更新 $f$，对于 $tag$ 等于 $0$ 的相当于偏移加乘 $2$。

复杂度 $O((n+V)\log V)$。

代码：

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define pb push_back
#define mp std::make_pair
#define gin std::cin
#define prt std::cout
#define edl std::endl

namespace Main {
  const int N = 2e5 + 5,mod = 998244353,V = 2e5;
  int n,opt[N],val[N],f[N];
  void main() {
    scanf("%d",&n);
    rep(i,1,n) {
      scanf("%d",&opt[i]);
      if (opt[i] != 3) scanf("%d",&val[i]);
    }
    int tag = 0;
    rep(i,1,n) {
      if (opt[i] == 3) {
        val[i] = tag;
        if (tag <= V) tag *= 2;
      }
      if (tag > V) continue;
      if (opt[i] == 2) tag += val[i];
    }
    rep(i,1,V) f[i] = 1;
    int sum = 0,ans = 0,mul = 1,c = 0;
    bool flag = false;
    per(i,n,1) {
      if (opt[i] == 3) {
        if (val[i] > V) {
          continue;
        }
        if (val[i] != 0) {
          per(j,V,1) {
            if (j - sum > 0) f[j] = f[j - sum];
            else f[j] = 0;
          }
          per(j,V,1) if (j - val[i] > 0) f[j] = (f[j] + f[j - val[i]]) % mod;
        } else {
          mul = mul * 2 % mod; 
          if (c <= V) c += sum;
        }
        sum = 0;
      }
      if (opt[i] == 2) {
        if (sum <= V) sum += val[i];
      }
      if (opt[i] == 1) {
        if (val[i] - sum - c > 0)
          ans = (1ll * ans + 1ll * mul * f[val[i] - sum - c] % mod) % mod;
      } 
    }
    prt << ans;
  }
} signed main() { Main::main(); return 0; }
```


---

## 作者：Alex_Wei (赞：2)

关于 F1，有一个依赖 $x\leq 2\times 10 ^ 5$ 的势能分析的做法：从后往前暴力模拟，操作 $2$ 的次数不超过 $2\times 10 ^ 5$。遇到一个操作 $3$ ，我们暴力递归两次。遇到一个操作 $2$ ，将当前值加上 $x_i$。遇到一个操作 $1$ ，如果 $x_i$ 大于当前值，则将答案加上 $1$。注意要对一段连续的操作 $1$ 批量处理，否则遇到的操作 $1$ 就无法用操作 $2$ 的次数限制，也就是求出一段区间内大于某值的数的个数，主席树维护。

交上去发现 [TLE](https://codeforces.com/contest/1774/submission/185672698)，为什么呢？这是因为在一开始没有操作 $2$ 的极长段，我们会花费大量时间模拟，但没有使得当前值增大。预处理一开始没有操作 $2$ 的极长段，求出每个操作 $1$ 的 $x_i$ 被复制了多少次，加到权值线段树里面，即可在递归到该段时 $\mathcal{O}(\log x)$ 求出贡献。

这样，执行操作 $3$ 的次数关于执行操作 $2$ 和 $n$ 线性：想象一个二叉树，底层是操作 $2$ ，其它节点是操作 $3$，而非叶子节点数关于叶子节点树线性。又因为每次执行一段操作 $1$ 之前必然执行过操作 $2$ 或操作 $3$，所以操作 $1$ 的次数也是线性。

总复杂度 $\mathcal{O}((n + x)\log x)$。[代码](https://codeforces.com/contest/1774/submission/185679095)。

---

## 作者：Cxny (赞：1)

nb 题。sto $\textsf{L\color{red}ittle09}$ orz。

发现一次 $3$ 操作会重复之前的扣血操作，也即扣血量翻倍。于是**出现扣血操作后**，不超过 $\log(\max x_i)$ 次 $3$ 操作就会使所有的猪猪 $\text{GG}$。

先统计出每个 $1$ 操作生成的猪猪**到下一个 $3$ 操作之前**的实际血量，以及每次 $3$ 操作会给**已经在场**的猪猪扣多少血。

尝试倒序枚举，统计操作 $1$ 对答案的贡献。

我们维护 $sum_i$ 表示当前生成一只血量为 $i$ 的猪猪，到最后会变成多少只。

对于每个操作 $3$，若其扣血量没有达到上限，则所有血量大于**当前总扣血量**的猪猪数量乘 $2$。

排除并没有扣血的操作 $3$ 后，$sum$ 只会改动 $\log$ 次，大力维护即可。

当前时间复杂度：离线后预处理 $O(n)$，统计答案时操作 $1$ $O(1)$，操作 $3$ 总复杂度 $O(m\log X)$。

当前空间复杂度：$O(\max(n,x))$。

其中 $X=\max x_i$。

代码就不贴了。

---

## 作者：Mr_罗 (赞：0)

维护可重集 $S\gets\varnothing$ 和变量 $t\gets 0$ ，把三种操作重写成以下形式：

- $1\ x:\quad S\to S\cup\{x\}$
- $2\ x:\quad S\to \{k-x\mid k\in S\},t\to t+x$
- $3\ {\color{white}x}:\quad S\to \{k-t\mid k\in S\}\cup S,t\to 2t$

最后查询 $|\{x\mid x\in S,x>0\}|$ 。

直接平衡树维护即可，时间复杂度 $\mathcal O(n\log V+V\log^2V)$ 。

具体地：

- 操作 $1$ ：直接插入。
- 操作 $2$ ：打「全局加」tag 并直接修改。
- 操作 $3$ ：
  - $t=0$ ：打「全局乘」tag 。
  - $t>0$ ：暴力把大于 $t$ 的减掉 $t$ 之后插入。这个只会做 $\log V$ 次，每次最多做 $V-t$ 次插入，总操作数是
    $$\sum_{i=1}^{\log V}V-2^{i-1}=V\log V-V+\mathcal O(1)$$
    所以时间复杂度是对的。

代码就不贴了~~主要是我懒得写 Treap 直接贴的 F2 的代码过的~~。

---

