# [ABC314G] Amulets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc314/tasks/abc314_g

洞窟に、モンスター $ 1 $ 、モンスター $ 2 $ 、$ \ldots $ 、モンスター $ N $ の $ N $ 体のモンスターがおり、各モンスターには正整数の**攻撃力**と、$ 1 $ 以上 $ M $ 以下の整数で表される**タイプ**が定められています。 具体的には、$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、モンスター $ i $ の攻撃力は $ A_i $ でタイプは $ B_i $ です。

高橋君はお守り $ 1 $ 、お守り $ 2 $ 、$ \ldots $ 、お守り $ M $ の $ M $ 個のお守りのうちのいくつかを持って、**体力**が $ H $ の状態でこの洞窟に冒険に出かけます。

冒険では高橋君は（体力が $ 0 $ 以下になって力尽きない限り）$ i\ =\ 1,\ 2,\ \ldots,\ N $ の順に下記の手順を行います。

- もし高橋君がお守り $ B_i $ を冒険に持ってきていないなら、高橋君はモンスター $ i $ の攻撃を受け、高橋君の体力が $ A_i $ だけ減少する。
- その後の時点での高橋君の体力が、
  - $ 0 $ より大きいならば、高橋君はモンスター $ i $ を倒す。
  - $ 0 $ 以下ならば、高橋君はモンスター $ i $ を倒せずに力尽きて冒険を終了する。

$ K\ =\ 0,\ 1,\ \ldots,\ M $ のそれぞれの場合について独立に、下記の問題を解いてください。

> 高橋君が全 $ M $ 個のお守りの中から $ K $ 個を選んで冒険に持っていくときの、高橋君が倒すモンスターの数としてあり得る最大値を求めよ。

なお、任意の $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、タイプが $ i $ であるモンスターが必ず $ 1 $ 体以上いることが、制約として保証されます。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ H\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ M $
- 任意の $ 1\ \leq\ i\ \leq\ M $ に対して、ある $ 1\ \leq\ j\ \leq\ N $ が存在して $ B_j\ =\ i $ が成り立つ
- 入力はすべて整数

### Sample Explanation 1

$ K\ =\ 1 $ の問題を考えます。この場合、高橋君はお守り $ 2 $ を持っていくことで、$ 5 $ 体のモンスターを倒し、倒すモンスターの数の最大値を達成することができます。 その際の冒険は、下記の通りに進行します。 - $ i\ =\ 1 $ について、高橋君はお守り $ 2 $ を持っているため、モンスター $ 1 $ の攻撃を免れます。その後、高橋君はモンスター $ 1 $ を倒します。 - $ i\ =\ 2 $ について、高橋君はお守り $ 1 $ を持っていないため、モンスター $ 2 $ の攻撃を受けて体力が $ 6 $ になります。その後、高橋君はモンスター $ 2 $ を倒します。 - $ i\ =\ 3 $ について、高橋君はお守り $ 2 $ を持っているため、モンスター $ 3 $ の攻撃を免れます。その後、高橋君はモンスター $ 3 $ を倒します。 - $ i\ =\ 4 $ について、高橋君はお守り $ 2 $ を持っているため、モンスター $ 4 $ の攻撃を免れます。その後、高橋君はモンスター $ 4 $ を倒します。 - $ i\ =\ 5 $ について、高橋君はお守り $ 1 $ を持っていないため、モンスター $ 5 $ の攻撃を受けて体力が $ 1 $ になります。その後、高橋君はモンスター $ 5 $ を倒します。 - $ i\ =\ 6 $ について、高橋君はお守り $ 3 $ を持っていないため、モンスター $ 6 $ の攻撃を受けて体力が $ -8 $ になります。その後、高橋君はモンスター $ 6 $ を倒せずに力尽きて冒険を終了します。 同様に、$ K\ =\ 0 $ の場合は $ 2 $ 体のモンスターを、 $ K\ =\ 2 $ の場合はお守り $ 2,\ 3 $ を持っていくことで $ 7 $ 体のモンスター全てを、 $ K\ =\ 3 $ の場合はお守り $ 1,\ 2,\ 3 $ を持っていくことで $ 7 $ 体のモンスター全てを倒すことができます。

## 样例 #1

### 输入

```
7 3 7
3 2
1 1
4 2
1 2
5 1
9 3
2 3```

### 输出

```
2 5 7 7```

## 样例 #2

### 输入

```
15 5 400
29 5
27 4
79 1
27 2
30 3
4 1
89 2
88 3
75 5
3 1
39 4
12 1
62 4
38 2
49 1```

### 输出

```
8 12 15 15 15 15```

# 题解

## 作者：lvvd (赞：7)

## 题目大意

有 $N$ 个洞穴排成一排，分别编号为 $1 \sim N$，每个洞穴里有一只怪兽，对于怪兽 $i$ 有攻击力 $A_{i}$ 和类型 $B_i$。

高桥君有 $M$ 种不同的护身符，编号为 $1 \sim M$，每一种护身符都可以让对应类型的怪兽无法攻击他。

高桥君要进行一次冒险，刚开始他有 $H$ 健康值，他可以带上任意数量的护身符。高桥君会按照编号从 $1$ 到 $N$ 的顺序探索洞穴，对于如果他没有携带 $B_i$ 类型的护身符，他就会受到 $A_i$ 攻击力的伤害（也就是健康值减去 $A_i$），反之，他就不会受到伤害。

任意时刻，如果高桥君的健康值小于等于 $0$，他就会退出这次冒险。

现在高桥君想知道，对于任意的 $i (0 \leqslant i \leqslant M)$，如果他携带 $i$ 个护身符（类型没有限制），他最多可以探索到第几个洞穴？

## 解法

很显然的暴力的做法就是 $\mathcal{O}(2^{M})$ 枚举每个护身符带与不带，然后 $\mathcal{O}(N)$ 判断答案。

假设当前高桥君走到了洞穴 $i$ 并且不携带任何护身符，那么我们可以统计出不同类型的怪兽分别会对高桥君造成的总伤害。

例如，对于样例一，假设高桥君目前走到了编号为 $6$ 的洞穴。

那么类型 $1$ 的怪兽总共会对高桥君造成 $6$ 伤害，类型 $2$ 的怪兽总共会对高桥君造成 $8$ 伤害，类型 $3$ 的怪兽总共会对高桥君造成 $9$ 伤害.

如果高桥君要携带护身符，那么贪心地想，肯定是要先规避掉总伤害值最高的那一类怪兽。

所以可以枚举带多少个护身符，然后二分答案，每次 `check` 看规避掉最高的那几个伤害后剩余怪兽造成的伤害是否大于等于 $H$。

时间复杂度 $\mathcal{O}(MN\log N)$。

仍然需要优化。

注意到用上面的方法每次 `check` 可以直接算出走到编号为 $i$ 的洞穴至少需要带的护身符数量，并且越走到后面的洞穴，携带的护身符数量只会增加不会减少。

想到可以利用前一个洞穴的答案递推出当前洞穴的答案。

先维护走到当前洞穴每一个类型的怪兽会对高桥君造成的总伤害，再不停减去总伤害最大的那一类怪兽，直到剩下的怪兽对高桥的伤害不超过 $H$。

感觉要直接这么做的话可以用平衡树维护，但是没有实现过。

更简单的做法是分别维护一个大根堆和一个小根堆，小根堆里存放当前携带的护身符，大根堆存放为携带的护身符，对应的权值是携带这种护身符能规避掉多少伤害。

这玩意好像是叫对顶堆，要保证小根堆里的权值都比大根堆里的权值大。

每遇到一个新的洞穴都把这一类怪兽的总伤害和小根堆的堆顶比较，使小根堆堆顶大于大根堆堆顶。

维护这个对顶堆后要看大根堆里的伤害总值是否大于等于 $H$，如果是，就需要不停把大根堆堆顶转移到小根堆里。

这种做法每加入一个新的洞穴最多更新一次对顶堆，每一个大根堆的元素进入了小根堆后就不会自己返回大根堆（除非是新加入的洞穴导致堆顶元素更新），所以时间复杂度均摊 $\mathcal{O}(N \log M)$。

实现代码时要注意几点：

1. 维护对顶堆时可能会出现一些节点的历史版本（没有来得及弹出的），在操作时需要判断一下。

2. 如果新加入的怪兽对应的护身符已经携带，那么就不用判断它和小根堆堆顶的关系了，但还是要维护这个类型的怪兽攻击力总值。

[代码](https://www.luogu.com.cn/paste/p6ltz0nv)。

码风很烂，轻喷，有什么不懂的可以问我。

---

## 作者：Minuswy (赞：4)

## 题意解释

高桥君在冒险。他面对着 $n$ 只怪兽。对于每只怪兽 $i$，有一个攻击力 $a_i$ 和一个类型 $b_i$（$1 \le b_i \le m$）。高桥君初始永有 $h$ 点血量和 $m$ 种护身符各一个，护身符类型分别为 $1,2,…,m$。

$N$ 只怪兽会按照 $i=1,2,…,n$ 的顺序依次向他扑来。当他的血量 $\ge 0$ 时，

- 如果高桥君没有带第 $b_i$ 种护身符，那么第 $i$ 只怪兽会攻击他，使他降 $a_i$ 的血量。

- 之后，如果他血量 $\ge 0$，他打败了怪兽 $i$；不然，他被第 $i$ 只怪兽打败了，冒险结束。

对于每个 $0 \le k \le m$，你要输出高桥君带 $k$ 个护身符时，最多能打败多少怪兽。

数据保证对于每种类型的怪兽都至少有一只。

## 题解

### 写在前面

在翻译官方题解的基础上加了一些自己的理解。我用的是 set 维护信息，相对稍微好写一点。

### 题解部分

维护带 $k$ 个护身符时，最多能打败多少怪兽比较困难，我们可以转换一个思路，维护打败第 $i$ 个怪兽 **最少需要带** 的护身符数 $l_i$。

但是 $l_i$ 也不好维护啊，所以我们可以维护 **最多不需要带** 的护身符数，也就是最大化 **攻击他的怪兽种类** ，即 $m-l_i$。

考虑前 $i$ 个怪兽。令 $c_j$ 表示前 $i$ 头怪兽中，类型为 $j$ 的怪兽的攻击力总和。显然，要使攻击他的怪兽种类最多，每种怪兽的攻击力，即 $c_j$ 要尽可能小。所以我们从小到大取出 $c_j$，如果选了类型为 $j$ 的怪兽，高桥君血量仍 $>0$，也就是被选的 $ c_j$ 之和 $sum < h$ ，那么就选上，否则就停止。

那么我们现在考虑如何求出 $m-l_i$。当从第 $i$ 个怪兽推到第 $i+1$ 个怪兽的状态时，只有 $c_{b[i+1]}$ 发生了变化。所以对于选择的怪兽集合 $S$ 和不选的怪兽集合 $T$，它们中肯定有一些元素依然存在于它原来的集合中（即一直被选或一直没被选）。具体实现可以看代码。

那么我们现在要找一种数据结构，支持删除（删掉老的 $c_{b[i+1]}$）、加入（更新 $c_{b[i+1]}$）、找最大/最小值（贪心选择最小的 $c_j$/踢掉 $S$ 中最大的 $c_j$）。这就是 set 了！

## 代码

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#deifne int long long
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
using namespace std;
const int inf=1e18;
const int N=3e5+10;
int n,m,h,sum,cnt;
int a[N],b[N],c[N],l[N];
set<pii>S,T;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>h;
	FOR(i,1,n) cin>>a[i]>>b[i];
	FOR(i,1,m) S.insert(mkp(0,i)); 
	// S 集合中加入一个pair，第一维表示到目前为止（即第 0 只怪兽）的 c[i]，第二维表示怪兽种类 i
	T.insert(mkp(inf,inf)); 
	FOR(i,1,n){
		pii p=mkp(c[b[i]],b[i]); //判断之前 b[i] 有没有被选 
		auto it=S.find(p);
		if(it!=S.end()){ sum-=it->fi; S.erase(it); } //被选了
		else T.erase(p); //没被选 
		c[b[i]]+=a[i]; //更新 c[i] 
		
		p=mkp(c[b[i]],b[i]);
		if(p< *T.begin()) { sum+=p.fi; S.insert(p); }  
		else T.insert(p);
		//在集合 T 中最小的 c[j]，与新更新 c[i] 中二选一
		
		while(sum>=h){
			auto it=S.end();
			it--;
			T.insert(*it);
			sum-=it->fi;
			S.erase(it);
		}
		//选得太多导致 sum > h 了，就去掉一些 
		
		while(sum+T.begin()->fi <h){
			auto it=T.begin();
			sum+=it->fi;
			S.insert(*it);
			T.erase(it);
		}
		//选得太少，就再选一些 
		
		l[i]=m-S.size();
	}
	l[n+1]=inf;
	FOR(i,0,m){
		while(l[cnt+1]<=i) cnt++;
		cout<<cnt<<" ";
	}
	return (0-0);
}

```


---

## 作者：Unnamed114514 (赞：2)

答案具有单调性，显然可以二分。

对于有 $i$ 个护身符的情况，前 $mid$ 个怪物造成的最小伤害就是前面 $mid$ 个怪物的伤害总和然后减去造成伤害最大的 $i$ 种怪物造成的伤害。

如果你直接枚举护身符的数量 $a$，然后 `check` 能否通过前 $b$ 个怪物，根据前面的推理，时间复杂度应该是 $O(n^2\log^2n)$ 的。

那么考虑二分通过前 $i$ 个怪物的最少护身符数。

我们可以容易地求出前 $i$ 个怪物每种的伤害，对于护身符数 $mid$，问题转化成了求伤害前 $k$ 大的和。

考虑到 $i-1\to i$ 时，只有一种怪物的伤害会改变，就是一个单点插入单点删除，然后需要求出前 $k$ 大的和，就可以考虑用权值线段树维护，时间复杂度 $O(n\log^2n)$，理论可过。

但是还有一个更加优秀的做法：怪物少的需要的护身符的数量一定少于怪物多的时候需要的护身符的数量，那么我们就可以在整体复杂度 $O(n)$ 的时间复杂度内枚举需要的部分。

因为整体是 $O(n)$，那么我们就可以暴力移动护身符的数量。

考虑定义两个集合 $S_1,S_2$，分别表示选择的和没有被选择的，如果 $S_2$ 中的和已经大于了 $H$，那么就增加护身符的数量，$S_2$ 的最大值就会不造成伤害，转移到 $S_1$ 中，同时减少 $S_2$ 的伤害和 $sum$。

然后新增怪物的时候，我们就把它所在集合的原伤害删除并加入它的新伤害。注意此时可能它可以加入 $S_1$，那么此时 $S_1$ 的最小值就会来到 $S_2$，然后它就加入 $S_1$。

删除、插入、最小、最大？~~权值线段树~~可以用 `multiset` 解决，并且时间复杂度是 $O(n\log n)$。

---

## 作者：Exp10re (赞：2)

鄙人不才，提供一种平衡树做法。

## 解题思路

考虑枚举 $1,2,\cdots,N$ 的每个 $i$，在 $[1,i]$ 范围内，每一种护符对应的怪物会造成的伤害总和，记为 $cnt_i$。

那么显然的，如果我们能携带 $K$ 个护符，想要在到达怪物 $i$ 时损失的生命值最小，那么携带 $cnt$ 值前 $K$ 大的 $K$ 个护符能够最小化损失的生命值。

注意到答案具有单调性，那么考虑以下做法：

1. 枚举 $1,2,\cdots,N$ 的每个 $i$，统计在 $[1,i]$ 范围内，每一种护符对应的怪物会造成的伤害总和以及所有种类怪物造成的伤害总和，分别记为 $cnt_i$ 和 $tot$，因为枚举为正序，因此可以用类似前缀和方法维护。

1. $K$ 从 0 开始，在枚举过程中统计 $[1,i]$ 范围内前 $K$ 大的护符 $cnt$ 值的和，如果 $tot$ 减去这个和（即失去生命值）大于等于初始生命值，那么说明携带 $K$ 个护符最多只能到达 $i-1$，走到 $i$ 就一定会结束游戏。统计答案，将 $K$ 增加 1，重复步骤 2，直到失去生命值小于初始生命值，说明当前携带 $K$ 个护符的答案一定大于等于 $i$，继续步骤 1。

1. 如果枚举已经结束，而 $K$ 仍然小于 $M$，那么说明携带大于等于 $K$ 个护符的答案一定为 $N$。（在携带 $K$ 个护符能保证“通关”，而答案具有单调性）

可以考虑使用平衡树维护当前前 $K$ 大的护符 $cnt$ 值的和，具体做法见代码以及注释。

## 代码

平衡树的实现太长了，就不放了，在这里放一下核心部分的代码，完整代码见[这里](https://www.luogu.com.cn/paste/p9798meq)。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=300100,VERY_INF=1145141919810810ll;//当查询第 M+1 大值的时候返回极大值。 
struct node
{
	long long cnt,tot,rng,val,son[2];
};
node tree[MAXN];
long long tval;
void pushup(long long x);
void rotate(long long &p,long long d);
void inc(long long &p,long long c);
void del(long long &p,long long c);
long long find(long long p,long long t);
long long root=0,n,cval[MAXN],cnum[MAXN],ccnt[MAXN],ans[MAXN],ctot,lst,HP,m;
int main()
{
	srand(time(0));
	long long i,j,flag=0,tmp;
	scanf("%lld%lld%lld",&n,&m,&HP);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&cval[i],&cnum[i]);
	}
	for(i=1;i<=m;i++)
	{
		inc(root,0);
	}
	for(i=1;i<=n;i++)
	{
		ctot+=cval[i];
		tmp=find(root,m-flag+1);
		if(ccnt[cnum[i]]<tmp)// 如果增加前的数值小于第 K 大值并且增加后大于第 K 大值
		{
			if(ccnt[cnum[i]]+cval[i]>=tmp)//那么就减去原先的第 K 大值，加入新的值（第 K 大被更新了） 
			{
				lst-=tmp;
				lst+=ccnt[cnum[i]]+cval[i];
			}
		}
		else//如果原先就大于 K，那么仅需加入增加的值即可。 
		{
			lst+=cval[i];
		}
		del(root,ccnt[cnum[i]]);//删除原先的值 
		ccnt[cnum[i]]+=cval[i];
		inc(root,ccnt[cnum[i]]);//加入新的值 
		while(ctot-lst>=HP)
		{
			ans[flag]=i-1;//找到新的合适的 K，代码中表现为 flag 
			flag++;
			lst+=find(root,m-flag+1);//步骤 2 
		}
	}
	for(;flag<=m;flag++)
	{
		ans[flag]=n;
	}
	for(i=0;i<=m;i++)
	{
		printf("%lld ",ans[i]);
	}
	printf("\n");
	return 0;
}
```

然后就没了。

---

## 作者：yzy1 (赞：2)

直接通过护符数量求出最多能击败的怪物数量可能不是很好做．考虑反过来，枚举怪物数量，然后计算最少需要几个护符才能打败这么多的怪物．

转化后的问题有一个简单的暴力做法：枚举怪物数量 $i$，然后计算前 $i$ 只怪物中每种类型怪物的伤害值的总和．从大到小排序，贪心地选择若干个伤害值总和最大的怪物类型来携带对应的护符即可．时间复杂度 $O(N^2 \log N)$．

考虑优化上述做法．考虑扫描线扫 $1$ 到 $N$，然后使用数据结构来维护每种类型怪物的伤害值的总和．我们需要的数据结构要维护一个可重集合，并支持以下几种操作：

- 插入一个数．
- 删除一个数．
- 询问至少要选前几大，才能让选出来的数的和至少为 $k$．

我们可以使用动态开点的值域线段树来维护这些操作．前两个操作相当于单点加减，第三个操作可以通过在线段树上二分来实现．

时间复杂度 $O(N \log N)$．

代码参考见 [原始 OJ 提交](https://atcoder.jp/contests/abc314/submissions/44547557)．


---

## 作者：xieziheng (赞：1)

在赛时代码基础上修改 $5\%$ 就过了，只能说我还有很多向 $cls$ 学习的地方。

首先按顺序枚举每个怪物，然后维护一个单调不降的护符数量 $k$，对于位置 $i$，更新所有在当前位置会死的答案。

显然，你此时会选出当前前缀攻击力和最大的 $k$ 种的护符，考虑维护这个玩意。

你需要支持：

- 修改某个点值

- 查询当前全局前 $k$ 大的和

这玩意看起来不太好做，不过修改点等价于删除再加入，查询前 $k$ 大的和可以在每次 $k$ 增大时依次加，然后在修改的时候维护。所以可以用平衡树做，复杂度 $O(n$ $log$ $n)$。细节不少，坑死我了。

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
const int N=5e5+5;
int n,m,b[N],cur,ans[N];ll h,a[N],s[N];
int tot,root;
struct node{
	int w,siz,cnt,ls,rs;ll v;
	il node(){v=0ll,w=siz=cnt=ls=rs=0;}
}tree[N];
il void pushup(int x){tree[x].siz=tree[tree[x].ls].siz+tree[tree[x].rs].siz+tree[x].cnt;}
il void lrot(int &x){
	int y=tree[x].rs;
	tree[x].rs=tree[y].ls,tree[y].ls=x,tree[y].siz=tree[x].siz;
	pushup(x),x=y;
}
il void rrot(int &x){
	int y=tree[x].ls;
	tree[x].ls=tree[y].rs,tree[y].rs=x,tree[y].siz=tree[x].siz;
	pushup(x),x=y;
}
void insert(int &x,ll val){
	if(!x){
		x=(++tot),tree[x].v=1ll*val,tree[x].w=rand(),tree[x].siz=tree[x].cnt=1;
		return ;
	}
	++tree[x].siz;
	if(tree[x].v==val){++tree[x].cnt;return ;}
	else if(val<tree[x].v){
		insert(tree[x].ls,val);
		if(tree[tree[x].ls].w<tree[x].w) rrot(x);
	}
	else{
		insert(tree[x].rs,val);
		if(tree[tree[x].rs].w<tree[x].w) lrot(x);
	}
}
int del(int &x,ll val){
	if(!x) return 0;
	if(tree[x].v==val){
		if(tree[x].cnt>1){--tree[x].siz,--tree[x].cnt;return 1;}
		if(!tree[x].ls || !tree[x].rs) {x=tree[x].ls+tree[x].rs;return 1;}
		else if(tree[tree[x].ls].w<tree[tree[x].rs].w){rrot(x);return del(x,val);}
		else {lrot(x);return del(x,val);}
	}
	else if(val<tree[x].v){
		int y=del(tree[x].ls,val);
		if(y) --tree[x].siz;
		return y;
	}
	else{
		int y=del(tree[x].rs,val);
		if(y) --tree[x].siz;
		return y;
	}
}
ll querynum(int x,int val){
	if(!x || !val) return 0ll;
	if(val<=tree[tree[x].ls].siz) return querynum(tree[x].ls,val);
	else if(val>tree[tree[x].ls].siz+tree[x].cnt) return querynum(tree[x].rs,val-tree[tree[x].ls].siz-tree[x].cnt);
	else return tree[x].v;
}
int x,y,z;ll u,v,w,sum,sumd;
int main(){
    scanf("%d%d%lld",&n,&m,&h);
    for(int i=1;i<=n;++i) scanf("%lld%d",&a[i],&b[i]);
    for(int i=1;i<=m;++i) insert(root,0ll);
    u=0ll;
    for(int i=1;i<=n;++i){
        u+=1ll*a[i];
        if(u>=h){ans[0]=i-1;break;}
    }
	if(u<h) ans[0]=n;
    cur=1;
    for(int i=1;i<=n;++i){
        u=querynum(root,m-cur+1),x=0;
        if(s[b[i]]>=u) sumd-=s[b[i]],x=1;
        del(root,s[b[i]]),insert(root,s[b[i]]+1ll*a[i]);
        if(x) sumd+=s[b[i]]+1ll*a[i];
        else{
            if(s[b[i]]+1ll*a[i]>=u) sumd+=s[b[i]]+1ll*a[i]-u;
        }
        sum+=1ll*a[i];
        while(cur<=m && sum-sumd>=h){
            ans[cur]=i-1,++cur;if(cur>m) break;
            sumd+=querynum(root,m-cur+1);
        }
        s[b[i]]+=a[i];
    }
    for(int i=cur;i<=m;++i) ans[i]=n;
    for(int i=0;i<=m;++i) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：happybob (赞：1)

考虑对每个怪物数量二分至少需要多少遗物。假设用了 $k$ 个遗物，那么必然选前面这些怪物类型中，能挡住伤害最多的前 $k$ 种。问题转化成求前 $k$ 大的和。考虑用个平衡树维护之，就是两只 $\log$ 了。

此外我们还需要维护答案，我写了个支持区间覆盖的线段树。

[代码。](https://www.luogu.com.cn/paste/s06hfnly)

---

## 作者：SegTree (赞：1)

记录一道场切的简单 ABC G 题。

### 题意

$n$ 个怪物，怪物属性为 $(a_i,b_i)$，$m$ 种护身符，初始生命值为 $h$。对于每个怪物，如果没有护身符 $b_i$，那么生命值减去 $a_i$。如果生命值小于等于 $0$ 就死亡了。对于 $i\in[0,m]$ 求携带 $i$ 个护身符的情况下最多能按顺序打到第几个怪物而不死亡。

$n,m\le 3\times 10^5,1\le a_i,h\le 10^9,1\le b_i\le m$。

### 题解

首先考虑如何选择护身符最优。显然要选择 $\sum[b_i=j]a_i$ 最大的几个 $j$，也就是说，如果 $1$ 到 $x$ 中 $a_i$ 的和减掉前 $k$ 大的 $\sum[b_i=j]a_i$ 小于 $h$，那么就不死亡，反之死亡。

注意到随着携带护身符的数量增多，答案肯定不降，因此双指针优化上面的过程。

现在需要一个数据结构支持对于 $m$ 种护身符的 $\sum[b_i=j]a_i$ 的维护：

+ 单点修改。

+ 前 $k$ 大的数的和。

不难想到使用平衡树。时间复杂度 $\mathcal{O}(n\log n)$。

[submission](https://atcoder.jp/contests/abc314/submissions/44533739)。

---

## 作者：forgotmyhandle (赞：1)

[原题传送门](https://atcoder.jp/contests/abc314/tasks/abc314_g)

[你谷传送门](https://www.luogu.com.cn/problem/AT_abc314_g)

提供一个常数巨大的暴力数据结构做法。

## 分析

看到这种极值类问题，可以先想一想二分。由于这题中可以击败的怪物一定是一段连续的前缀，所以考虑二分这段前缀的长度。

由于本题中一道护身符免掉的是一种类型的怪物所造成的总伤害，所以考虑单个怪物的伤害是没有意义的。接下来我们只考虑某一区间中同一类型的怪物所造成的总伤害。

那么二分之后考虑如何判断可行性。显然根据贪心的原则，我们一定会优先考虑免掉 造成最多伤害的 怪物类型 所造成的 总伤害。也就是说，对于一段前缀，我们每次去询问出现在这段前缀中的 每种类型的怪物 造成的总伤害 的前 $k$ 大的和。前 $k$ 大问题，想到主席树。发现主席树的本质实际上是前缀线段树，正好与本题相像。接下来考虑主席树维护什么东西。

以下所说的前 $k$ 大都指前 $k$ 大的和。

直接讲可能不太好讲，所以我们先从权值线段树讲起。这题用到的权值线段树的本质上是一个桶，但是这个桶可以查询前 $k$ 大。而一旦将他可持久化，那就是一个可查询任意历史状态中所有元素前 $k$ 大的桶。那对于这题来说，任一时刻的桶里存的应当是所有出现了的类型的怪物的总伤害，而时刻就是输入每一个怪物的顺序，也就是我们加入每一个怪物的顺序。

接下来考虑如何维护主席树。显然，加入一个怪物时，其所属的类型的怪物的总伤害会增加，对于桶来说就是原本的值少了一个，加上后得到的值多了一个。那么到线段树上就是先删掉原本的值，再加上现在的值。这样我们就可以得到一棵前缀线段树 ~~（可持久化桶）~~。其中每个 $1$ 到 $n$ 之间的每个下标 $i$ 对应一个前缀线段树的根， **其中保存了从 $1$ 到 $i$ 中出现的每一种怪物类型的怪物的伤害和。** 然后前 k 大就是平凡的。

那么这样就有了一棵前缀线段树。对于每一个 $k \in [0, m]$，我们二分最多能击败多少怪物。那么由于击败的所有怪物一定处在一段连续的前缀中，所以我们的判定就是使用 $k$ 道护身符能否走过一段特定长度的前缀。根据我们之前讲的贪心原则，**我们一定免掉造成伤害最高的怪物类型。** 那么考虑最多能免掉多少伤害，这其实就是前 k 大问题，线段树已经维护好了。有了这个值之后就可以算出走完这一段前缀最少会受到多少伤害，然后跟初始生命值比较一下即可判定。

总时间复杂度 $O(m (\log n)(\log S))$，其中 $S$ 为值域大小。由于线段树维护的值域实在太大，导致 $\log S$ 也十分巨大，所以可能需要开个 O2 才能卡过。

## 代码
```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <set>
#define ll long long
using namespace std;
const ll N = 3e14;
int n, m, h;
int a[300005], b[300005];
int ptcnt[300005];
ll msum[300005];
int rt[600005];
ll S[300005];
set<int> st;
struct Persistent_Segment_Tree {
    struct node {
        int l, r, sm;
        ll smv;
    } T[31000005];
    int ncnt;
    void Build(int& o, ll l, ll r) noexcept {
        o = ++ncnt;
        T[o].sm += m;
        if (l == r) 
            return;
        Build(T[o].l, l, (l + r) >> 1);
    }
    void Insert(int p, int& q, ll l, ll r, ll x, int y) noexcept {
        q = ++ncnt;
        T[q] = T[p];
        T[q].sm += y;
        T[q].smv += y * x;
        if (l == r) 
            return;
        ll mid = (l + r) >> 1;
        (x <= mid) ? Insert(T[p].l, T[q].l, l, mid, x, y) : Insert(T[p].r, T[q].r, mid + 1, r, x, y);
    }
    ll Query(int o, ll l, ll r, int k) noexcept {
        if (!o) 
            return 0;
        if (l == r) 
            return l * k;
        ll mid = (l + r) >> 1;
        return (T[T[o].r].sm >= k) ? Query(T[o].r, mid + 1, r, k) : (T[T[o].r].smv + Query(T[o].l, l, mid, k - T[T[o].r].sm));
    }
} seg;
inline bool chk(int c, int k) noexcept {
    if (ptcnt[k] <= c) 
        return 1;
    ll tmp = seg.Query(rt[k], 0, N, c);
    ll dt = S[k] - tmp;
    return (dt < h);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> h;
    seg.Build(rt[0], 0, N);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        S[i] = S[i - 1] + a[i];
        st.insert(b[i]);
        ptcnt[i] = st.size();
        seg.Insert(rt[i - 1], rt[i + n], 0, N, msum[b[i]], -1);
        msum[b[i]] += a[i];
        seg.Insert(rt[i + n], rt[i], 0, N, msum[b[i]], 1);
    }
    for (int i = 0; i <= m; i++) {
        int l = 0, r = n, ans = 0, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (chk(i, mid)) 
                ans = mid, l = mid + 1;
            else 
                r = mid - 1;
        }
        cout << ans << " ";
    }
    return 0;
}
```

---

