# [ARC170D] Triangle Card Game

## 题目描述

Alice 和 Bob 正在进行一场游戏。

开始时，Alice 和 Bob 各自拥有 $N$ 张卡片，Alice 的第 $i$ 张卡片上写有整数 $A_i$，Bob 的第 $i$ 张卡片上写有整数 $B_i$。

游戏按照以下步骤进行：

- 准备一块空白的黑板。
- Alice 吃掉自己的一张卡片，并将该卡片上的整数写在黑板上。
- 接着，Bob 吃掉自己的一张卡片，并将该卡片上的整数写在黑板上。
- 最后，Alice 再吃掉自己的一张卡片，并将该卡片上的整数写在黑板上。

如果黑板上写的 $3$ 个整数可以作为三角形的三条边的长度（即存在非退化三角形），则 Alice 获胜；否则 Bob 获胜。

请判断在双方都采取最优策略的情况下，谁会获胜。

给定 $T$ 组测试数据，请分别输出每组的答案。

## 说明/提示

### 限制条件

- $1 \leq T \leq 10^5$
- $2 \leq N \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq 10^9$
- 所有输入的数值均为整数
- 所有测试数据中 $N$ 的总和不超过 $2 \times 10^5$

### 样例解释 1

对于第 $1$ 组测试数据，游戏可以如下进行：

- Alice 吃掉写有 $2$ 的卡片，在黑板上写下 $2$。
- Bob 吃掉写有 $4$ 的卡片，在黑板上写下 $4$。
- Alice 吃掉写有 $1$ 的卡片，在黑板上写下 $1$。
- 黑板上的数字为 $2, 4, 1$，这三条边无法组成三角形，因此 Bob 获胜。

对于本组数据，上述步骤未必是双方的最优策略，但可以证明，在双方都采取最优策略的情况下，Bob 会获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
1 2 3
4 5 6
4
6 1 5 10
2 2 4 5
10
3 1 4 1 5 9 2 6 5 3
2 7 1 8 2 8 1 8 2 8```

### 输出

```
Bob
Alice
Alice```

# 题解

## 作者：Assembly_line (赞：9)

设三张牌依次是 $A_i,B_i,C_i$，那么 $\max(A_i-B_i,B_i-A_i)<C_i<A_i+B_i$。

只考虑一边的不等号，$B_i$ 要尽可能小，或尽可能大。（这样使得限制较紧。当然考虑两边的不等号就不行了）

我们充分发扬人类智慧：

将 $A,B$ 排序。

根据数学直觉，在排序后，$B_i$ 一定要选较小或较大的数。

所以我们枚举 $A_i$，取最小的 $15$ 个 $B_i$ 与最大的 $15$ 个 $B_i$，二分找是否有满足条件的 $C_i$。

这样速度快得飞起，在 $n=200000$ 时都可以在 300ms 内卡过。

---

## 作者：Leo_SZ (赞：8)

假设第一次 Alice 选择了 $a$，第二次 Bob 选择了 $b$，第三次 Alice 选择了 $c$。
如果这三个数能构成三角形的三条边，那么应该满足：
$$\lvert a - b \rvert \lt c \lt a + b$$

分类讨论一下绝对值：

- 若 $b \lt a$，则 $a - b \lt c \lt a + b$；
- 若 $b \geq a$，则 $b - a \lt c \lt a + b$。

我们先枚举 $a$。对于第一种情况，由于 $a$ 已经确定了，则 Bob 想要获胜，一定会使 $b$ 最小，这样满足条件的 $c$ 就最少。所以，只需要判断当 Bob 选择了最小的 $b$ 时，已经选好的 $a$ 是否有对应的 $c$ 满足条件。

此时的 $c$ 应该是离 $a$ 最近的数。我们将 Alice 所有可以选择的 $a$ 排序，每次判断相邻的两个是否大于最小的 $b$ 即可。

对于第二种情况，可以发现，$c$ 可取的区间是以 $b$ 为中心，以 $a$ 为半径的。那么 $a$ 越大，越有可能有 $c$ 在区间范围内。

但是，由于不能选择重复的数字，有没有可能有一个 $a_2$ 比较大，但是取了 $a_2$ 之后，恰好取走了 $( b - a_2,a_2 + b )$ 中唯一的一个 $a$，而有一个较小的 $a_1$，却有 $a_2 \in ( b - a_1,a_1 + b )$？

实际上，若 $a_1 \lt a_2$，$a_1 \notin ( b - a_2,b + a_2 ) $ 与 $a_2 \in ( b - a_1,b + a_1 ) $ 是不会同时满足的。

- 若 $b \lt a_1 \lt a_2$：

	$\begin{cases} b + a_1 \gt a_2 \\ b + a_2 \leq a_1 \end{cases}$
    
	不成立；

- 若 $ a_1 \leq b \lt a_2$：

	$\begin{cases} b + a_1 \gt a_2 \\ b - a_2 \geq a_1 \end{cases}$
    
	不成立；

- 若 $a_1 \lt a_2 \leq b$：

	$\begin{cases} b - a_1 \lt a_2 \\ b - a_2 \geq a_1 \end{cases}$
    
	不成立。

综上，当满足第一种情况时，$a$ 取更大的数是不劣的。

所以，将数组从小到大排序后，先枚举 $a$，判断 Bob 取 $b_1$ 时是否存在 $c \in ( a - b,a + b )$。对于满足条件的最大的 $a$，判断是否对于所有的 $b$，都存在 $c \in ( b - a,a + b )$。

```cpp
#include<bits/stdc++.h>
#define Maxn 200005
using namespace std;
const int inf = 0x3f3f3f3f;
int n,a[Maxn],b[Maxn];
bool slv(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){ scanf("%d",a+i); }
	for(int i=1; i<=n; i++){ scanf("%d",b+i); }
	sort(a+1, a+n+1);
	sort(b+1, b+n+1);
	
	int cur = 0;
	
	// if B<A, A-B < C < A+B
	// |C - A| < B_min
	for(int i=1; i<n; i++){
		if(a[i+1]-a[i] < b[1]){
			cur = i+1;
		}
	}
	if(!cur){
		return false;
	}
	
	// if B>=A, B-A < C < B+A
	// A = a[cur]
	int cl=0, cr=0, dis;
	for(int i=1; i<=n; i++){
		if(b[i] < a[cur]){ continue; }
		while(cr <= n && (a[cr] < b[i] || cr == cur)){
			cr++;
		}
		cl = cr-1;
		if(cl == cur){
			cl--;
		}
		
		dis = inf;
		if(cr <= n){
			dis = min(dis, a[cr] - b[i]);
		}
		if(1 <= cl){
			dis = min(dis, b[i] - a[cl]);
		}
		
		if(dis >= a[cur]){
			return false;
		}
	}
	return true;
}
int main(){
	int ttt;
	scanf("%d",&ttt);
	while(ttt--){
		slv() ? printf("Alice\n") : printf("Bob\n");
	}
	return 0;
}

```

---

## 作者：eastcloud (赞：3)

我们先转换一下题目，变成判定 Alice 是否存在一张手牌，使得出这张手牌作为第一张后无论 Bob 出什么 Alice 都有办法获胜，也就是说固定 Alice 第一张牌后，每张 Alice 的第二张牌能赢过的 Bob 的牌的并等于 Bob 所有的牌。

先考虑一张 Alice 的第二张牌能赢过哪些 Bob 的牌，我们固定第一张牌，设其数值为 $a$，同样设第二张牌数值为 $b$，可得：


* 当 $b \leq a$ 时，范围为 $(a-b,a+b)$。

* 当 $b>a$ 时，范围为 $(b-a,b+a)$。

注意到在第一种情况中选 $b$ 为最靠近 $a$ 的那个数肯定最优，第二种范围中心点不变，如果我们倒着扫，向外延伸的范围也是递减的，于是我们倒着钦定每个 $a$，动态维护一下范围即可做到 $O(n \log n)$。

但是上述做法细节比较多，需要根据 $a$ 的变化动态维护范围，有没有更容易的思路呢？

我们尝试能不能只考虑某些极值的取值而不考虑所有点。首先，选取的 $a$ 一定要对于最小的 Bob 的卡片有解，这样一来，小于 $a$ 的所有 Bob 的卡都肯定有解，而对于大于 $a$ 的那些卡，在 $a$ 取到所有对最小 Bob 的卡片有解的所有数中的最大值肯定是最优的。

如果有 $a'<a$ 且有数在 $a'$ 中有解 $a$ 中无解，我们可以考虑这个数肯定大于 $a$，然后可以分为以下两种情况：

* 如果这个数在 $a'$ 中是由一个 $(a'-k,a'+k)$ 的区间覆盖到，那显然因为 $a'>k$ 且 $a>a'$，$(a-a',a+a')$ 更能覆盖到。

* 如果是由一个 $(k-a',k+a')$ 的区间覆盖到，如果$k$ 大于 $a$ 则显然 $a$ 同样能覆盖到，否则同理 $(a-a',a+a')$ 更能覆盖到。

证明完毕，于是我们贪心地选取这个 $a$ 并判定就是最优的，维护是容易的，时间复杂度为 $O(n \log n)$，瓶颈在排序。

```cpp
void solve(){
	int n=read(),pos=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(a+1,a+n+1);sort(b+1,b+n+1);a[n+1]=inf;
	for(int i=1;i<=n;i++){
		int dis=inf;
		if(i!=1)dis=min(dis,a[i]-a[i-1]);
		if(i!=n)dis=min(dis,a[i+1]-a[i]);
		if(dis<b[1])pos=max(pos,i);
	}
	if(!pos){printf("Bob\n");return;}
	for(int i=1;i<=n;i++){
		int l=abs(b[i]-a[pos]),r=b[i]+a[pos];
		int p=upper_bound(a+1,a+n+2,l)-a;
		if(p==pos)p++;
		if(a[p]>=r){printf("Bob\n");return;}
	}
	printf("Alice\n");
}
```


---

## 作者：Disjoint_cat (赞：2)

# [ARC170D Triangle Card Game](https://atcoder.jp/contests/arc170/tasks/arc170_d)

赛时 C 题做了 $50$ 多分钟，D 题不到 $20$ 分钟就切了。

## 题意

Alice 和 Bob（以下简称 A 和 B）要玩一个游戏。两人初始均有 $n$ 个数。

- A 先选他手中的一个数；
- B 再选他手中的一个数；
- A 最后再选他的另一个数（不能选他第一次选的数）。
- 如果最后选出的三个数能构成三角形，A 赢；否则 B 赢。

问两人均采用最优策略时，最后的胜者。

$2\le n\le2\times10^5$。

## 题解

博弈论的经典套路就是倒着想。

设 A 一开始选了 $a$，然后 B 选了 $b$。

此时如果 A 要赢，那么他选的第二个数 $c$ 就必须在 $(|b-a|,a+b)$ 之间。

对 A 的数排序，就能在 $\Theta(\log n)$ 内判断 A 是否能选出这样的 $c$，从而判断此时的胜者。

但我们显然不能直接枚举 $a$ 和 $b$，考虑挖掘性质。先把绝对值符号去掉，此时 A 胜的条件为：

- $b<a$ 时，$c\in(a-b,a+b)$；
- $b\ge a$ 时，$c\in(b-a,a+b)$。

可以发现，如果 $b_1<b_2$，则有 $(a-b_1,a+b_1)\subseteq(a-b_2,a+b_2)$。

也就是说，A 选数之后，B 如果想靠「$b<a$ 时」的条件赢，肯定会选最小的 $b$。

如果靠 $b<a$ 的情况无法获胜，B 只能尝试令 $b\ge a$。

但是 $(b-a,a+b)$ 在 $b$ 变化时并没有包含关系，也就无法简单地找出最优策略。

再回到 A 选第一个数时的场景。如果 A 要赢，他选的 $a$ 首先需要在「$b<a$ 时」，即 B 取最小值时，能赢；

在此基础上，要满足 $b\ge a$ 时，不管 B 取什么数，也能赢。

又可以发现，如果 $a_1>a_2$，则（无论 $b$ 的取值）有 $(b-a_2,b+a_2)\subseteq(b-a_1,b+a_1)$。

所以在保证 $b<a$ 能赢的情况下，A 肯定会取最大的那个 $a$。

所以我们从大到小枚举 $a$，先判断 $b$ 取最小值时的胜者；如果此时 A 赢，那么我们可以断定 A 取的 $a$ 就是这个值。

于是此时再暴力枚举 $b$ 并判断即可。

时间复杂度 $\Theta(n\log n)$。

## 代码

赛时代码，有改动。

```cpp
const int N=200005;
int n,a[N],b[N];
bool chk(int l,int r,int forbid)
{//A 选的数必须在 [l,r] 中，他选的第一个数是 forbid，能否选出
	int pl=lower_bound(a+1,a+n+1,l)-a,pr=upper_bound(a+1,a+n+1,r)-a-1;
	return pr>pl||pl==pr&&a[pl]!=forbid;
}
void Solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=n;i;i--)
		if(chk(a[i]-b[1]+1,a[i]+b[1]-1,a[i]))
		{
			for(int j=1;j<=n;j++)
				if(b[j]>a[i]&&!chk(b[j]-a[i]+1,b[j]+a[i]-1,a[i]))
					{puts("Bob");return;}
			puts("Alice");return;
		}
	puts("Bob");
}
```

---

## 作者：快乐的大童 (赞：1)

### 题意简述
先手有 $n$ 张卡片 $a_i$，后手有 $n$ 张卡片 $b_i$，一局游戏由先手先选一张卡、后手其次选一张卡、先手最后再选一张卡，若三张卡上的数字能构成三角形则先手胜，否则后手胜，求谁有必胜策略。

$n\le 2\times10^5$。

### 分析
枚举先手第一步选择的牌，设其为 $a$。令先手取完 $a$ 后剩余的 $n-1$ 张卡牌构成的集合为 $S$。

如果后手对于该牌没有应对之策，那么先手就是必胜的。设后手选的牌为 $b$，则后手有应对之策当且仅当不存在 $c\in S,|a-b|<c<a+b$。

拆掉绝对值分类讨论：

- 若 $a\ge b$，此时 $a-b<c<a+b$，开区间中心一定，那么半径 $b$ 越小，可能包含的数越少，因此此时取最小的 $b$ 更优。
- 若 $a<b$，此时 $b-a<c<b+a$，开区间半径一定，我们需要选择一个合适的中心 $b$，使得开区间中不包含任何 $c$。
 
接下来重点讨论第二种情况。

此时我们需要知道对于每个 $b$ 和与其距离最近的那个 $c$ 的距离是多少，设其为 $dis_b$。则若存在一个 $dis_b$ 满足 $dis_b\ge a$（即最近的 $c$ 在开区间范围之外，注意可以取等），那么后手就有应对之策。但有可能最近的 $c$ 是先手第一部就选择过的 $a$，故此时对于每个 $b$ 仍需维护一个次大值，当最大值对应的 $c$ 是 $a$ 时，去掉最大值，加入次大值，直到处理下一个 $a$ 时在加回来，并把次大值去掉。

这里需要支持插入、删除和取最大值操作，可以用 set 或者可删堆，时间复杂度都是 $O(n\log n)$。

小问题：如何求最大值和次大值？最大值一定是 $b$ 的前驱后继，次大值一定是 $b$ 的前驱后继以及前驱的前驱和后继的后继。具体见代码。

[code](https://atcoder.jp/contests/arc170/submissions/49585167)

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

Alice 和 Bob 又双叒叕开始博弈了。

Alice 有 $n$ 张牌，权值分别为 $a_i$；Bob 也有 $n$ 张牌，权值分别为 $b_i$。

Alice 打一张牌，然后 Bob 打一张牌，最后 Alice 打一张牌（不能和第一张一样）。

如果这三张牌的权值能够组成一个正常的三角形，Alice 就赢了，否则就是 Bob 赢。

众所周知，Alice 和 Bob 都绝顶聪明，请你预测比赛结果。

## 题目大意

设打出的三张牌的权值依次为 $x$，$y$，$z$。

像这种轮流出牌且轮次较少的博弈题，可以从后往前推出牌人的想法。

- 已知 $x$ 与 $y$，Alice 该如何选 $z$？

显然，根据小学数学知识，Alice 选的 $z$ 应当属于区间 $[|x-y|+1,x+y-1]$。

所以只要存在这样的 $z$，Alice 就赢了。

所以，Bob 的目的就是使得不存在这样的 $z$。

- 已知 $x$，Bob 要选择怎样的 $y$，才能使得不存在 $z$ 使得 Alice 赢？

显然，我们要通过分类讨论消去绝对值。

 1. 当 $y\le x$ 时，区间为 $[x-y+1,x+y-1]$，注意到这个区间始终以 $x$ 为中心，所以 $y$ 越大，区间覆盖的范围越大，Alice 就越容易赢，所以 Bob 为了赢只能选最小的 $y$。
 
 2. 当 $y>x$ 时，区间为 $[y-x+1,y+x-1]$，注意到这个区间始终以 $y$ 为中心，所以 $x$ 越大，Alice 越容易赢。这时候对于每一个 $y$，能使 Bob 获胜的 $x$ 小于 $a_i$ 与 $y$ 的差的最小值，由于 Alice 第一轮可能把最近的 $a_i$ 用过了，所以还得记一个次小值。这部分可以通过将 $a$ 数组排序并通过二分 $O(n\log n)$ 预处理出来。
 
这时候再考虑 $x$ 的选择，只要选择的 $x$ 能够使得 Bob 选出最优的 $y$ 都存在 $z$ 处在区间内，Alice 就能赢，即：

$$\exists i\in[1,n],\forall j\in[1,n],\exists k\ne i,a_k\in[|a_i-b_j|+1,a_i+b_j-1]$$

以上是这题的核心内容，理解后就可以很轻松地设计算法流程了：

$a_i,b_j,a_k$ 对应 $x,y,z$，以下是整体思路：

 1. 将 $a$、$b$ 数组均从小到大排序，枚举 Alice 选择的第一张牌 $i$。
 
 2. 判断两类 $y$ 的最优情况能否使得 Bob 赢。
 
对于第一类，只需判断 $a_i$ 与 $b_1$ 的关系，并在 $a$ 中二分找到区间的位置即可。

对于第二类，我们考虑从大到小枚举 $i$，用一个类似平衡树的数据结构存储这类 $y$ 对应的最小距离，对于每一个 $j$，至多有一个 $i$ 被选时会删除最小距离并加入最大距离，所以直接挂在 $i$ 上即可。然后查询存储的值中的最大值与 $x$ 的关系即可。这题用 map 就行了。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define mid (l+r>>1)
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define pb push_back
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =3e5+5,inf=(1LL<<31)-1;
int n,m,a[N],b[N];
int findr(int x){
	int l=1,r=n,ans=0;
	while(l<=r)if(a[mid]<=x)ans=mid,l=mid+1;
	else r=mid-1;
	return ans; 
}
int findl(int x){
	int l=1,r=n,ans=n+1;
	while(l<=r)if(a[mid]>=x)ans=mid,r=mid-1;
	else l=mid+1;
	return ans; 
}
//二分
int val[N],ex[N];//最小距离，次小距离
vector<int>p[N];
map<int,int>P;
void del(int x){
	if(P[x]==1)P.erase(x);
	else P[x]--;
}
void Main(){
	n=read();
	repn(i)a[i]=read(),p[i].clear();
	P.clear();
	repn(i)b[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1);     
	repn(i){
		int ps=findr(b[i]);
		if(!ps){
			val[i]=a[1]-b[i];
			continue;
		}
		int d=b[i]-a[ps],d2=inf;
		if(ps<n)d2=a[ps+1]-b[i];
		if(ps>1)d2=min(d2,b[i]-a[ps-1]);
		val[i]=min(d2,d);
		if(d<d2)p[ps].pb(i),ex[i]=d2;
        //预处理最、次小值
	}
	int Rr=n;
	per(i,n,1){
		while(Rr&&b[Rr]>a[i])P[-val[Rr--]]++;
		if(a[i]>=b[1]){
			int l=findl(a[i]-b[1]+1),r=findr(a[i]+b[1]-1);
			if(!(l<=r&&!(l==r&&l==i)))continue;
		}//第一类点
		E(i)del(-val[y]),P[-ex[y]]++;
		Pi nw=*P.begin();
		if(-nw.first<a[i])return cout <<"Alice\n",void();//第二类点
		E(i)del(-ex[y]),P[-val[y]]++;
	}
	cout <<"Bob\n";               
}
signed main(){
	int T=read();
	while(T--)Main();
    return 0;
}
```


---

## 作者：XYQ_102 (赞：0)

## 思路
先将 $A,B$ 从大到小排序，设 $A$ 数组中取出的第一个数字为 $x$，第二个数字为 $z$，$B$ 数组中取出的数字为 $y$。
- 当 $y<x$ 时，组成三角形的条件为 $y+z>x$ 或者 $x+y>z$，对于 Bob 来说，选择最小的 $y$ 更不容易组成三角形。所以 Bob 会选择 $B_1$。
- 当 $x\le y$ 时，组成三角形的条件为 $x+y>z$ 或 $x+z>y$，那么组不成三角形的条件变为 $\min\lvert y-z\rvert\geq x$，利用双指针进行维护。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int mod = 998244353;
const int N = 2e5 + 5;
int a[N], b[N], v[N];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        a[0] = -1e9, a[n + 1] = 2e9;
        for (int i = 0; i <= n; i++)
            v[i] = 1;
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);
        for (int i = 1; i <= n; i++) {
            if (b[1] <= a[i]) {
                if (b[1] + a[i - 1] <= a[i] && b[1] + a[i] <= a[i + 1])
                    v[i] = 0;
            }
        }
        int num = 0, ans = 0;
        for (int i = n, j = n; i; i--) {
            if (num >= a[i])
                v[i] = 0;
            while (j && b[j] >= a[i]) {
                if (a[i - 1] + a[i] <= b[j] && a[i] + b[j] <= a[i + 1])
                    v[i] = 0;
                num = max(num, min(b[j] - a[i], a[i + 1] - b[j]));
                j--;
            }
            ans |= v[i];
        }
        if (ans)
            cout << "Alice" << endl;
        else
            cout << "Bob" << endl;
    }
    return 0;
}
```

---

## 作者：Phartial (赞：0)

给一个简单无脑好写好调确定性做法。

先假设三步选出来的数分别是 $a,b,c$。

倒着看，若 $a\le b$，则 $c$ 有两种决策，一种是取 $\ge b$ 的最小数（尝试做到 $a+b>c$），一种是取 $\le b$ 的最大数（尝试做到 $a+c>b$）。若 $a>b$，则 $c$ 的决策就是取 $\ge a$ 的最小数与 $\le a$ 的最大数，获胜条件是 $b+a>c$ 或 $b+c>a$。

然后是 Bob 的决策，如果他选择让 $a\le b$，那么 $c$ 的决策其实是几乎不受 $a$ 影响的（我们肯定是取离 $b$ 最近的数作为 $c$，唯一的特例是离 $b$ 最近的数是 $a$），然后对每个 $b$ 预处理离它最近/第二近的 $c$ 与它的距离，固定 $a$ 后容易找到哪些 $b$ 是 $a$ 离它最近（必然是一段前缀），由于 $b$ 希望 $c$ 离它的距离尽量大，跑一个 RMQ 就能得到这个距离（由于这个东西有单调性，可以直接双指针求）。而若 $b<a$，为了让获胜条件尽量难达到，$b$ 必然取最小值。

最后 $a$ 的决策直接枚举即可。

时间复杂度单组数据 $\Theta(N \log N)$，瓶颈在排序。

https://atcoder.jp/contests/arc170/submissions/56199720.

---

## 作者：快斗游鹿 (赞：0)

题意可以转化为，是否可以取到一个 $a_i$，满足对于任意的 $b_i$，都存在 $a_j(j\neq i)$ 满足 $|a_i-b_i|<a_j<|a_i+b_i|$。

先将 $a,b$ 从小到大排序，分类讨论一下：

如果 $a_i\ge b_i$，则 $a_i-b_i<a_j<a_i+b_i$，对于后手来说，$b_i$ 越小，肯定越优，因为范围更小，因此后手肯定会取 $b_1$，这部分可以简单判断。

如果 $a_i<b_i$，则 $b_i-a_i<a_j<a_i+b_i$，这时对于每个 $b_i$ 来说，$a_i$ 取值具有单调性。证明如下：

设 $a_1<a_2$，如果存在 $a_1,a_1\notin(b-a_2,b+a_2)$，且 $a_2\in(b-a_1,b+a_1)$，才有可能使得 $a_i$ 不满足单调性（$a_1,a_2,b\ge 0$）。仍然进行分类讨论：

如果 $b<a_1<a_2$，则可以得到 $a_1\ge b+a_2,a_2<b+a_1$，不可能成立。

如果 $a_1\le b < a_2$，则可以得到 $a_1\le b-a_2,a_2<b+a_1$，不可能成立。

如果 $a_1<a_2\le b$，则可以得到 $a_1\le b-a_2,a_2>b-a_1$，不可能成立。

因此 $a_i$ 满足单调性。

因此可以二分出满足的区间，做差分后判断是否存在一个 $a_i$，满足对于所有 $b_i>a_i$，$a_i$ 都满足条件。

最后只要合起来判断一下就行了。


```cpp
#include<bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <math.h>
#include <cstdio>
#define int long long
using namespace std;
const int inf=1e18;
const int N=4e5+5;
int n,a[N],b[N],c[N],len,g[N],s[N],ans[N];
bool flag[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int getlsh(int x){
	return lower_bound(c+1,c+1+len,x)-c;
}
void add(int x){
	for(x;x<=len;x+=(x&-x))g[x]++;
}
int ask(int x){
	int aaa=0;
	for(x;x>0;x-=(x&-x))aaa+=g[x];
	return aaa;
}
int down(int x){
	return upper_bound(c+1,c+1+len,x)-c-1;
}
int up(int x){
	return lower_bound(c+1,c+1+len,x)-c;
}
bool check(int x,int w){
	int op=0;
	if(x-w<w&&w<x+w)op=1;
	int R=down(x+w-1),L=up(x-w+1);
	if(ask(R)-ask(L-1)>=1+op)return 1;
	return 0;
}
void solve(){
	n=read();len=0;
	for(int i=1;i<=n;i++)a[i]=read(),c[++len]=a[i];
	for(int i=1;i<=n;i++)b[i]=read(),c[++len]=b[i];
	sort(c+1,c+1+len);
	len=unique(c+1,c+1+len)-c-1;
	for(int i=1;i<=len;i++)g[i]=0;
	sort(a+1,a+1+n);sort(b+1,b+1+n); 
	for(int i=1;i<=n;i++)add(getlsh(a[i]));
	for(int i=1;i<=n;i++)flag[i]=0,ans[i]=0;
	for(int i=1;i<=n;i++){
		if(b[1]>a[i]){flag[i]=1;continue;}
		int w=b[1];
		int mi=inf;
		if(i-1>=1)mi=min(mi,a[i]-a[i-1]);
		if(i+1<=n)mi=min(mi,a[i+1]-a[i]);
		if(mi<w)flag[i]=1;
	}
	//for(int i=1;i<=n;i++)cout<<flag[i]<<" ";
	//cout<<endl; 
	for(int i=1;i<=n;i++){
		int x=upper_bound(b+1,b+1+n,a[i])-b;
		s[i]=n-x+1;
		//cout<<s[i]<<" ";
		x=lower_bound(a+1,a+1+n,b[i])-a-1;
		//cout<<"!"<<x<<endl;
		if(x<1)continue;
		int l=1,r=x,aaa=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(b[i],a[mid]))aaa=mid,r=mid-1;
			else l=mid+1;
		}
		if(aaa!=-1)ans[aaa]++,ans[x+1]--;
	}
	//cout<<endl;
	for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
	//for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	//cout<<endl;
	for(int i=1;i<=n;i++){
		if(flag[i]&&ans[i]==s[i]){
			puts("Alice");return;
		}
	}
	puts("Bob");
}
signed main(){
	//freopen("data.in","r",stdin);
	//ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	int T;T=read();while(T--)solve();
	return 0;
}

```

---

## 作者：TernaryTree (赞：0)

首先 $a,b$ 升序排序。

枚举 Alice（以下称作 A，同理把 Bob 称为 B）出的牌。

当 A 出了 $a_i$：我们需要判断 B 是否存在一个 $b_j$，满足

$$\forall k\neq i,a_k\le |a_i-b_j|\lor a_k\ge a_i+b_j $$

若对于所有 $i$ 都满足存在一个 $j$ 满足上述命题，则 B 胜，否则 A 胜。

当 $b_j\lt a_i$ 时，化为

$$\forall k\neq i,|a_k-a_i|\ge b_j $$

记为情况 $1$。

同理当 $b_j\ge a_i$ 时，化为

$$\forall k\neq i,|a_k-b_j|\ge a_i$$

记为情况 $2$。

对于情况 $1$，只需要判断 $\min(a_{i+1}-a_i,a_i-a_{i-1})\ge b_1$ 即可。因为左右两边都显然贪心选最小的。

对于情况 $2$，右边是不变量，左边要贪小，所以左边的最小值是 $b_j$ 在 $\{a_1,a_2,\dots,a_{i-1},a_{i+1},a_{i+2},\dots,a_n\}$ 中与其前驱后继的差值的较小值。这个等价于在原序列中前驱后继，若前驱/后继的下标为 $i$ 那么再往前/后找一个。对于每一个 $j$ 的这个较小值可以预处理出前驱后继之后，用线段树维护：每次快速找出前驱/后继中等于 $i$ 的位置并进行单点修改，区间查询最大值。这里最大的原因是，我们贪的任意一个小中只要比 $a_i$ 大，B 就是赢的。结合 min-max 理解。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r

using namespace std;

const int maxn = 1e6 + 10;
const int inf = 1e18;

int T, n;
int a[maxn], b[maxn], c[maxn];
int p[maxn], q[maxn];
vector<int> s[maxn], t[maxn];

struct node {
	int v, a, b;
} tr[maxn << 2];

void pushup(int u) {
	tr[u].v = max(tr[ls].v, tr[rs].v);
}

void modify(int u, int l, int r, int p, int k, int z) {
	if (l == r) {
		if (!z) tr[u].a = k;
		else tr[u].b = k;
		tr[u].v = min(tr[u].a, tr[u].b);
		return;
	}
	if (p <= mid) modify(lc, p, k, z);
	else modify(rc, p, k, z);
	pushup(u); 
}

int query(int u, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return tr[u].v;
	int v = -inf;
	if (ql <= mid) v = max(v, query(lc, ql, qr));
	if (qr > mid) v = max(v, query(rc, ql, qr));
	pushup(u);
	return v;
}

void build(int u, int l, int r) {
	if (l == r) {
		tr[u].a = (p[l] >= 1 && p[l] <= n ? b[l] - a[p[l]] : inf);
		tr[u].b = (q[l] <= n && q[l] >= 1 ? a[q[l]] - b[l] : inf);
		tr[u].v = min(tr[u].a, tr[u].b);
		return;
	}
	build(lc), build(rc);
	pushup(u);
}

signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];
		for (int i = 0; i <= n + 1; i++) s[i].clear(), t[i].clear();
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + n);
		for (int j = 1; j <= n; j++) {
			p[j] = upper_bound(a + 1, a + 1 + n, b[j]) - a - 1;
			q[j] = lower_bound(a + 1, a + 1 + n, b[j]) - a;
			s[p[j]].push_back(j);
			t[q[j]].push_back(j);
		}
		build(1, 1, n);
		bool fl = 1;
		for (int i = 1; i <= n; i++) {
			int mn = 1e18;
			if (i > 1) mn = min(mn, a[i] - a[i - 1]);
			if (i < n) mn = min(mn, a[i + 1] - a[i]);
			bool f = 0;
			if (b[1] < a[i]) f |= (mn >= b[1]);
			for (int j : s[i]) {
				p[j]--;
				modify(1, 1, n, j, (p[j] >= 1 && p[j] <= n ? b[j] - a[p[j]] : inf), 0);
			}
			for (int j : t[i]) {
				q[j]++;
				modify(1, 1, n, j, (q[j] <= n && q[j] >= 1 ? a[q[j]] - b[j] : inf), 1);
			}
			if (b[n] >= a[i]) {
				int pos = lower_bound(b + 1, b + 1 + n, a[i]) - b;
				f |= (query(1, 1, n, pos, n) >= a[i]);
			}
			for (int j : s[i]) {
				p[j]++;
				modify(1, 1, n, j, (p[j] >= 1 && p[j] <= n ? b[j] - a[p[j]] : inf), 0);
			}
			for (int j : t[i]) {
				q[j]--;
				modify(1, 1, n, j, (q[j] <= n && q[j] >= 1 ? a[q[j]] - b[j] : inf), 1);
			}
			fl &= f;
			if (!fl) break;
		}
		cout << (fl ? "Bob" : "Alice") << endl;
	}
	return 0;
}


```

---

## 作者：int_R (赞：0)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/17980853/AT_arc170_d)

[原题链接](https://www.luogu.com.cn/problem/AT_arc170_d)

当 Alice 先出了一张牌 $A$，Bob 又出了一张 $B$，分类讨论一下。

当 $B\leq A$，如果 Alice 不再出一张 $(A-B,A+B)$ 中的牌 Bob 就赢了，所以这种情况 Bob 会出最小的牌。

当 $B>A$，如果 Alice 不再出一张 $(B-A,B+A)$ 中的牌 Bob 就赢了，这时无法贪心，对每个 $B_i$ 考虑，找到 $B_i$ 在 $A$ 中第一个小于等于和第一个大于等于它的，取差值小的一个，则所有小于等于这个差值的 $A_j$ 都可以被这个 $B_i$ 卡掉。

但是还不完全，因为忘记了一条限制是不能重复出一张牌两次，所以当 $A_j$ 等于这个第一个小于等于或第一个大于等于 $B_i$ 的话，还可以在拓展一下，这种情况只能单独限制这一张牌。

当一个 $A_j$ 不可以被任何一个 $B_i$ 限制的时候 Alice 赢，否则 Bob 赢。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
int T,n,a[MAXN],b[MAXN],C[MAXN];
inline void work()
{
    cin>>n;int cur=0;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i) cin>>b[i];
    for(int i=1;i<=n;++i) C[i]=0;
    sort(a+1,a+1+n),sort(b+1,b+1+n);
    for(int i=1;i<=n;++i)
    {
        int now1=2e9,now2=2e9;
        int c=upper_bound(a+1,a+1+n,b[i])-a-1;
        int d=lower_bound(a+1,a+1+n,b[i])-a;
        if(c>=1&&c<=n) now1=b[i]-a[c];
        if(d>=1&&d<=n) now2=a[d]-b[i];
        if(c>=1&&c<=n)
        {
            if(c-1>=1&&c-1<=n)
                C[c]=max(C[c],min(b[i]-a[c-1],now2));
            else C[c]=max(C[c],now2);
        }
        if(d>=1&&d<=n)
        {
            if(d+1>=1&&d+1<=n)
                C[d]=max(C[d],min(a[d+1]-b[i],now1));
            else C[d]=max(C[d],now1);
        }
        cur=max(cur,min(now1,now2));
    }
    for(int i=1;i<=n;++i)
    {
        bool flag=true;if(a[i]<=cur||a[i]<=C[i]) continue;
        if(b[1]<=a[i])
        {
            int k=upper_bound(a+1,a+1+n,a[i]-b[1])-a;
            if(k==i) ++k;if(k>n||a[k]>=a[i]+b[1]) flag=false;
        }
        if(flag){cout<<"Alice\n";return ;}
    }
    cout<<"Bob\n";return ;
}
int main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();
    return 0;
}
```

---

## 作者：StarPatrick (赞：0)

此题的博弈显然是有先后顺序的，我们不妨先假设 Alice 先选了一张写着 $A$ 的卡片，Bob 选了写着 $B$ 的卡片，Alice 第二次选了写着 $C$ 的卡片。

此时如果 bob 如果无论选什么 $B$，Alice 都有应对的卡片 $C$ 的话，那么 Alice 获胜，否则 Alice 第一次是不能选择 $A$ 这张卡片的，如果对于所有的 $A$，Alice 都不能获胜的话，那么最终 Bob 获胜。

以上是对于博弈过程很直觉的翻译，下面我们来翻译三角形这个条件。

$|A-B| < C < A+B$

把绝对值拆开，发现当 $B<=A$ 时：

$A-B < C < A+B$

那么 Bob 要让 Alice 无法选出 $C$，显然 $B$ 取**最小**是**最优**的，直接判断就可以了。

下面一种情况稍微麻烦一点，$B > A$：

$B-A < C < B+A$

发现似乎很多 $B$ 都有可能是最优的，但是当 $A$ 固定了以后，你发现这个区间长度一定，相当于 **存在一个C，B与C的距离小于A**。

接下来就很显然了，从大到小枚举 $A$，用你喜欢的数据结构维护每个大于 $A$ 的 $B$ 与 $C$ 的最小的距离，直接判断就可以了，这里我用的 multiset，值得注意的是，这里要保证 $A$ 与 $C$ 不是同一张卡片。

---

## 作者：EuphoricStar (赞：0)

赛后调了 40min，哈哈。

首先先把 $a, b$ 排序。

考虑先枚举 Alice 选的数 $a_i$，然后若 $\forall j, \exists k \ne i, (a_i, b_j, a_k)$ 能组成三角形，Alice 就赢了。

考虑简化条件。$(x, y, z)$ 能形成三角形的充要条件是 $z \in (|x - y|, x + y)$。那么条件变为 $\forall j, \exists k \ne i, a_k \in (|b_j - a_i|, b_j + a_i)$。

看到有个绝对值，考虑分类讨论。若 $b_j \le a_i$，那么 $a_k \in (a_i - b_j, a_i + b_j)$。可以发现 $b_j$ 越小这个范围越窄。所以只用判断 $b_j$ 最小，即 $j = 1$ 的情况。这个可以维护一个 multiset，然后 upper_bound 找大于 $a_i - b_1$ 的最小数判断。

考虑 $b_j > a_i$。考虑对每个 $i$ 求出一个分界点 $p_i$ 使得 $b_{p_i}$ 为第一个大于 $a_i$ 的数。那么条件变为 $\forall j \ge p_i, \exists k \ne i, a_k \in (b_j - a_i, b_j + a_i)$。

变形一下可得 $b_j \in (a_k - a_i, a_k + a_i)$。

这个条件就比较有意思了。可以把它看成是一个中点为 $a_k$，长度为 $2a_i$ 的线段。考虑把所有 $a, b$ 排列在数轴上，设 $b_j$ 夹在 $a_x, a_{x + 1}$ 之间。那么当 $a_i \le t = \min(b_j - a_x, a_{x + 1} - b_j)$ 时，$b_j$ 是不能被覆盖的。所以对于一个 $i$，若 $i \le q_j$ 且 $j \ge p_i$，$i$ 就不满足条件，就不能让 Alice 赢。这是一个二维偏序的形式，考虑第一维扫描线，第二维树状数组维护即可。

然后你写出来这个东西发现被这个 case 卡掉了：

```
1
2
3 8
4 4
```

答案是 Bob，而你输出了 Alice。原因是我们没有考虑 Alice 不能选重复的数的情况。考虑若 $q_j = x$ 就会出现选重复数的情况，若 $a_{x + 1}$ 不能用长度为 $2a_x$ 的线段覆盖到 $b_j$，即 $a_x + b_i \le a_{x + 1}$，就让 $q_j \gets q_j + 1$。

总时间复杂度为 $O(n \log n)$。

[code](https://atcoder.jp/contests/arc170/submissions/49561716)

---

