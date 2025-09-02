# [THUPC 2025 初赛] Harmful Machine Learning

## 题目背景

人工智能领域大神 The NIT 正在训练机器人 The BOT。

## 题目描述

The BOT 在一个 $1\times n$ 的网格上移动，其中在 $(1,i)$ 上有数字 $a_i$。The BOT 初始在格子 $(1,x)$, The BOT 想要走到一个数字尽量大的格子。每一步 The BOT 可以选择移动到相邻的一个格子或是不动，并且在移动后可以选择是否选择格子上的数字并结束游戏，而为了训练 The BOT 的能力，The NIT 会给出一些阻碍，在 The BOT 选择是否结束之后，The NIT 可以将两个数字交换位置。

具体地说，我们可以把整个游戏看成若干个回合，初始 The BOT 在位置 $(1,x)$，在一个回合中，以下事件会按顺序依次发生：

1. The NIT 选择两个位置 $1\leq i,j\leq n$，并交换 $a_i,a_j$ 的值，注意 $i$ 可以等于 $j$，此时交换不会带来任何变化。
2. The BOT 选择移动到一个相邻的位置或是原地不动，令 The BOT 现在所在的位置为 $y$，即选择 $1\leq z\leq n$ 且 $|z-y|\leq 1$，并移动到 $(1,z)$。
3. The BOT 选择是否结束游戏，令 The BOT 现在所在的位置为 $y$，如果选择结束则会获得 $a_y$ 的分数并**立刻结束游戏**，否则无事发生。

可以发现，如果 The BOT 一直不选择结束游戏，则游戏永远不会结束，为了防止这个情况的发生，在游戏的第 $10^{114514}$ 个回合，The BOT 必须选择立刻结束游戏。

The NIT 希望 The BOT 结束游戏时的分数最小，而 The BOT 希望这个分数最大。The NIT 和 The BOT 都是绝顶聪明的，但他们并没有时间玩 $10^{114514}$ 个回合，于是他们请你帮他们计算一下，The BOT 最终的分数是多少？

## 说明/提示

### 题目来源

题目来自 THUPC2025（2025年清华大学学生程序设计竞赛暨高校邀请赛）初赛，信息来源于 [THUSAAC 仓库](https://gitlink.org.cn/thusaa/thupc2025pre)。

## 样例 #1

### 输入

```
4
3 2
1 2 3
13 4
1 1 4 5 1 4 1 9 1 9 8 1 0
4 2
1 10 100 1000
1 1
114514```

### 输出

```
3
4
100
114514```

# 题解

## 作者：MassPoint (赞：3)

赛时全队花费 2h+ 的时间才写出的题。

## 思路

分类讨论。

1. 当 $n \le 3 $ 时，容易想到，此时的答案就是 $a_i$ 的最大值。

2. 当 $n > 3$时，考虑$1 < x < n$ 和 $x=1$ 或者 $x=n$ 两种情况。

### 当 $1 < x < n$ 时

首先，要使分数最小，NIT 一定会把 BOT 走不到的格子中最小的那个格子和 BOT 能走到的最大的格子交换（如果 BOT 能走到的格子本身就是最小的那几个，可以看作不交换），让 BOT 只能选移动前三个格子中的次大值。

而且，BOT 每移动一次，NIT 都能将它周围的格子换成较小的格子，并把每次往自己周围次大格移动的 BOT 控制在两个格子之内。BOT 和 NIT 玩的回合数越多，局势对 BOT 越不利。

因此，在该情况下，BOT 只玩一个回合是最有利的。

### 当 $x = 1$ 或 $x = n$ 时

此时开局，BOT 只能停在两个位置，考虑两种情况。

1. 能停在的格子是序列中的次小值和最小值。此时 NIT 不动，模拟易得，最大分数即为除能达到的的两个数外的数中最小的那个（即所有数中第三小的那个）。

2. 否则，可以直接一轮结束游戏，也可以向中间走一格，转化为 $1 < x < n$ 的情况。答案即为这两种情况得出的分数的最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int a[100001]; 
int cmp(int a,int b){
	return a<=b;
}
int main(){
	scanf("%d",&t);
	a[0]=1e9;
	while(t--){
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
		if(n<=3){
			int mx=0;
			for(int i=1;i<=n;i++){
				mx=max(mx,a[i]);
			}
			printf("%d\n",mx);
			continue;
		}
		if(x==n){	//当 x=n 时，将数列翻转，转化为 x=1 的情况。
			x=1;
			for(int i=1;i<=n/2;i++){
				swap(a[i],a[n-i+1]);
			}
		}
		if(x==1){	//当 x=1，BOT 要努力走到中间。 
			int res;
			int fl=1e9,op;
			for(int i=3;i<=n;i++){	//找到 BOT 这一回合不能抵达的格子中数字最小的那个格子。
				if(a[i]<fl) op=i; 
				fl=min(fl,a[i]);
			}
			if(fl<a[1]||fl<a[2]){	//按照 NIT 的策略，把 a[1] 和 a[2]中的最大值与序列中 BOT 到不了的地方的最小值交换。
				res=min(a[1],a[2]);	//直接一轮结束游戏，取最小值是因为能够到的最大值被 NIT 交换走了。
				if(a[2]>a[1])
					swap(a[2],a[op]);
				else
					swap(a[1],a[op]);
			}
			else{	//说明 a[1] 和 a[2] 分别是序列中的最小值和次小值，此时 BOT 顶多只能拿到 fl 点分数，直接特判。
				printf("%d\n",fl);
				continue;
			}
			x++;	//否则向中心移动，花费两轮结束游戏。
			int mi=x-1,mx=x+1;
			sort(a+mi,a+mx+1,cmp);	//由于 BOT 周围够得到的格子的位置关系其实不影响游戏结果，所以可以直接排序。
			fl=0;
			for(int i=1;i<=n;i++){
				if(abs(i-x)<=1) continue;	//不把 BOT 能达到的格子算入。
				if(a[i]<=a[fl])	fl=i;
			}
			if(a[fl]<a[mx])	swap(a[mx],a[fl]);
			sort(a+mi,a+mx+1);
			res=max(res,a[mx]);	//取一轮结束与两轮结束答案的最大值。
			printf("%d\n",res);
			continue;
		}
		int mi=x-1,mx=x+1;
		sort(a+mi,a+mx+1,cmp);
		int fl=0;
		for(int i=1;i<=n;i++){
			if(abs(i-x)<=1) continue;
			if(a[i]<=a[fl])	fl=i;
		}
		if(a[fl]<a[mx])	swap(a[mx],a[fl]);	//NIT 进行交换。
		sort(a+mi,a+mx+1);
		printf("%d\n",a[mx]);	//交换完毕后，BOT 选择停在它周围数字最大的格子上，直接结束游戏。
	}
	return 0;
}
```

---

## 作者：F_L_Bird (赞：2)

# Luogu P11522 题解

## 一：题意

有两人 A、B 在玩一个游戏，其中 B 将棋子在数列上移动（也可以不动），而 A 可以交换数列中的数（当然也可以不换）。两人按先 A 后 B 的顺序进行操作。每轮操作后，B 可以选择是否结束游戏，此时 B 的得分就为棋子所在位置的值，A 要使 B 的得分尽可能小，而 B 要使自己的得分尽可能大。若两人都按照最优策略进行游戏，问 B 的最大得分是多少。

## 二：分析样例

观察每组测试数据对应的解：


```
3 2
1 2 3        => 3


13 4
1 1 4 5 1 4 1 9 1 9 8 1 0        => 4


4 2
1 10 100 1000        => 100


1 1
114514        => 114514
```

观察到每一组数据的解都在 $a_{x-1},a_{x},a_{x+1}$ 中产生， ~~于是解法呼之欲出~~于是我们可以考虑从这方面入手。

## 三：推导结论

考虑一个数列 $a_1,a_2,a_3 \cdots a_n$ ，其中棋子最开始在 $a_x$ 的位置。无论玩家 A 如何操作，分数总能达到 $a_{x-1},a_{x},a_{x+1}$ 中的次大值。

如果 $a_{x-1},a_{x},a_{x+1}$ 已经是整个数列中的极小值，那么玩家 B 的最高分数就是这三个数中的最大值。

如果玩家 B 比较贪心，想要争取到更大的分数（并且数列中存在更大的数），那么此时最优的情况是数列中的最大值 $a_{max}$ 位于 $a_{x-2} $ 或 $a_{x+2}$ 的位置。此时无论玩家 B 向前或向后移动，玩家 A 总能找到**比 $a_{max}$ 小**的并且**玩家 B 一步之内无法到达**的**最小**的值与 $a_{max}$ 交换，并且游玩的步数越多，对玩家 B 就越不利，到最后玩家 B 的得分会是**整个数列中的第三小值**。

同理，我们可以证明， 对于所有的 $a_i>\max(a_{x-1},a_{x},a_{x+1})$ 或位于其他位置时，仍然不存在除整个数列中的第三小值之外可能的更优解。

综上所述，玩家 B 的得分就是 $a_{x-1},a_{x},a_{x+1}$ 中的次小值与数组中**整个数列中的第三小值**的最大值。

## 四：代码（其实到这一步已经不需要什么代码了）


```cpp
#include<iostream>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	for(int rct = 1;rct <= t;rct += 1)
	{
		int n,x;
		cin>>n>>x;
		int a[n + 5],mn = 0x3f3f3f3f,mx = -0x3f3f3f3f,mni = 0;
		
		for(int i = 1;i <= n;i += 1)	//输入，统计最大值
		{
			cin>>a[i];
			mx = max(a[i],mx);
		}
		
		if(n <= 3)		//如果数列中只有三个数，很明显答案是数组中的最大值
		{
			cout<<mx<<'\n';
			continue;
		}
		
		if(x == 1)	//数组中不只有三个数，先统计出可以到达位置的次大值(记得特判x在边界处的情况)
		{
			mx = min(a[x],a[x + 1]);
		}
		else if(x == n)
		{
			mx = min(a[x],a[x - 1]);
		}
		else if(a[x - 1] < a[x])
		{
			mx = (a[x] < a[x + 1] ? a[x] : max(a[x - 1],a[x + 1]));
		}
		else
		{
			mx = (a[x - 1] < a[x + 1] ? a[x - 1] : max(a[x],a[x + 1]));
		}
		for(int i = 1;i <= 3;i += 1)		//暴力统计出数组的第三小值
		{
			mni = 0;
			mn = 0x3f3f3f3f;
			for(int j = 1;j <= n;j += 1)
			{
				if(mn > a[j])
				{
					mn = a[j];
					mni = j;
				}
			}
			a[mni] = 0x3f3f3f3f;
		}	
		cout<<max(mx,mn)<<'\n';
	}
	return 0;
}
```

## 五：写在最后

不要抄题解！有错误的地方请各位神犇指出，谢谢 ouo。

---

## 作者：lzx111218 (赞：2)

## P11522 [THUPC2025 初赛] Harmful Machine Learning 题解
### 思路
既然 The NIT 会交换数组的元素，The BOT 则会选择最靠近当前位置 $k$ 的最大值。这意味着 The BOT 在最终选择时会考虑以下几个值：
* 当前位置 $a[k]$。
* 左侧的相邻位置 $a[k-1]$。
* 右侧的相邻位置 $a[k+1]$。

由此我们可以得出 The BOT 选择的最大值一定是：
1.  当前位置 $k$ 的值。
2.  左侧相邻位置 $a[k−1]$ 和右侧相邻位置 $a[k+1]$ 的值。
3.  The NIT 最多只能交换数组中的两个位置，因此，The BOT 会选择一个数字，这个数字是当前数组中 $k$ 位置、$
k−1$ 位置和 $k+1$ 位置中的最大值之一。
4.  我们还要注意，数组中的最小值是一个有效的选择，如果 $n$ 足够小，则只考虑这些相邻元素。
### Code

```cpp
#include<bits/stdc++.h> 
using namespace std;
int t, n, k, a[100005], b[4];
int main(){
    scanf("%d", &t); 
    while (t--) {
        scanf("%d %d", &n, &k); 
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]); 
        }
        a[0] = a[n + 1] = -2e9;
        b[0] = a[k - 1];
        b[1] = a[k];     
        b[2] = a[k + 1];    
        sort(b, b + 3);     
        sort(a + 1, a + n + 1);
        printf("%d\n", max(a[min(3, n)], b[1]));
    }
    return 0;
}

```

---

## 作者：Pratty (赞：2)

不错的黄题。

看到有大佬用二分写了，承认这种做法的巧妙和简易性的同时也来分享另外一种做法。

闲言少叙，题解继续。

## 思路

模拟样例不难发现，可以将 $n$ 的取值归纳为以下两种情况：

- $n\le3$ 时，可以直接判断，并且若不直接判断而是和统一处理放在一起时，既不好证明正确性，也不好操作，不如提前特判了。故在此时，我们只需要找到 $a_i$（$1\le i\le n$）的最大值即可。
- $n>3$ 时，考虑计算。

计算过程：

为了方便，在以下的叙述中，The BOT 将简称 B，The NIT 将简称 N。

假设在一回合当中，B 在 $x$ 位置，则他可能会来到 $x-1,x,x+1$ 中的任意一个位置，即取 $a_{x-1},a_x,a_{x+1}$ 中的任意一个值。为了防止 B 取得较大的分数，一开始 N 进行操作时，一定会将 $a_{x-1},a_x,a_{x+1}$ 的最大值换掉，即 B 只能选择其中的次大值。

我们不妨举个例子：

假设 $a_{x-1},a_x,a_{x+1}$ 分别为 $2,3,4$。

很明显的，为了防止 B 取得较大分数，N 会将 $4$ 换去，我们暂时不关心 $4$ 去到了哪里，但假设 N 换回来了一个 $c$（$c<4$）。在这里，我们假设 $c$ 一定存在，应为若 $c$ 不存在，则 N 一定无法操作，B 就会直接走到 $a_{x-1},a_x,a_{x+1}$ 中的最大值去了，不需进行计算。

现在 $a_{x-1},a_x,a_{x+1}$ 分别为 $2,3,c$。

根据贪心的策略，B 下一步只会去往 $3$，也可以证明这是最优策略。故 B 在这一回合中最终选择了 $a_{x-1},a_x,a_{x+1}$ 的次大值，即 $3$。

根据正确的贪心策略，在 N 改变顺序之后，B 每一步只会去往 $a_{x-1},a_x,a_{x+1}$ 中的最大值（即 N 未改变顺序时的次大值），所以 N 可以判断出来 B 下一步的去向。由此我们得出结论，当第三回合及之后，$a_{x-1},a_x,a_{x+1}$ 一定是数组 $a$ 中的最小的三个值。换句话说，在第三回合后的每一回合，B 身边一定有且仅有 $a$ 中的最小的三个值，故答案可以直接计算。

最后的答案就是以下两种的较大值：$a$ 中第三小的值、$a_{x-1},a_x,a_{x+1}$ 中的次大值。

一个判断结束，代码略。

---

## 作者：ztlh (赞：2)

## Solution

先不考虑 $x=1$ 和 $x=n$ 的情况。

考虑如果第一回合 The NIT 什么都不做会发生什么：The BOT可以抵达 $x-1$，$x$，$x+1$ 三个位置之一。

不妨 The BOT 移动到了 $x-1$，则在下一回合中，The NIT 可以交换 $a_{x-2}$ 和 $a_{x+1}$，从而将 The BOT 行动范围中的 $a_i$ 限制在同样的三个数中。因此最后的答案就是三者的最大值。

但第一回合一开始，The NIT 还有一次操作机会，他可以把除 $x-1$，$x$，$x+1$ 三个位置外的全局最小值与这三个位置的最大值交换（若全局最小值大于等于该最大值则无需交换）。操作后，三个位置上的最大值即为答案。

再考虑 $x=1$（$x=n$ 同理）。

此时 The BOT 一步可达的位置只有 $1$ 和 $2$。像之前一样取出剩余位置全局最小值并与 $\max(a_1,a_2)$ 比较，若更小则交换。那么 The BOT 可取得操作后的 $\max(a_1,a_2)$ 并结束游戏。

当然 The BOT 也可以选择不结束游戏，此时局面相当于 $x=2$ 情况，再计算一遍答案，与上面得到的答案取较大值即可。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x;
int a[100005];
int idx,ia;
int ans=0;
inline void Geti(int b,int &id,int &mn){
	if(b+2<=n) id=b+2,mn=a[b+2];
	else id=1,mn=a[1];
	for(int i=1;i<=n;i++){
		if(abs(i-b)<=1) continue;
		if(a[i]<mn) id=i,mn=a[i];
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if(n==1){
			printf("%d\n",a[1]);
			continue;
		}
		if(n==2){
			printf("%d\n",max(a[1],a[2]));
			continue;
		}
		if(n==3){
			printf("%d\n",max(max(a[1],a[2]),a[3]));
			continue;
		}
		if(x==n){
			for(int i=1;i*2<=n;i++) swap(a[i],a[n-i+1]);
			x=1;
		}
		Geti(x,idx,ia);
		if(x==1){
			ans=max(min(a[1],a[2]),ia);
			x=2;
			if(a[1]>a[2]) swap(a[1],a[idx]);
			else swap(a[2],a[idx]);
			Geti(x,idx,ia);
			printf("%d\n",max(ans,max(a[x-1],max(a[x],min(ia,a[x+1])))));
			continue;
		}
		sort(a+x-1,a+x+2);
		printf("%d\n",max(a[x-1],max(a[x],min(ia,a[x+1]))));
	}
	return 0;
}
```

---

## 作者：CraaazyShep (赞：2)

[P11522 [THUPC2025 初赛] Harmful Machine Learning](https://www.luogu.com.cn/problem/P11522)

### 分析

显然当 $n\le2$ 时答案即为 $a_i$ 中的最大值，特判解决即可。接下来我们讨论 $n\ge3$ 的部分。

我们假设 The BOT 在某回合开始时位于 $p$ 位置。在这一回合移动时，The BOT 可能移动至 $p-1,p,p+1$ 三个位置，也即回合结束后，The BOT 的得分可能变为 $a_{p-1},a_p$ 或 $a_{p+1}$。

我们目光短浅地来看，The BOT 在某一回合中最优策略是走向 $a_{p-1},a_p,a_{p+1}$ 中较大的那个。

那么由此，在任一回合中，The NIT 的最佳策略是取 $a_{p-1},a_p,a_{p+1}$ 以外的最小值，与 $a_{p-1},a_p,a_{p+1}$ 中的最大值交换。

第一回合中，The NIT 会将初始位置及其左右三个值的最大值换走，第一回合中 The BOT 可获取的最高分为**初始位置及其左右的第二大值**。

当游戏进行至第三回合及之后，The NIT 总有办法使得 $p-1,p,p+1$ 三个位置所包含的，恰为所有 $a_i$ 中最小的三个值。此时 The BOT 可以得到的最大值即为**总体的第三小值**。

那么答案为 $\max($初始位置及其左右的第二大值，总体的第三小值$)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
void solve(){
	cin>>n>>x;
	vector<int>a(n+1),b;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=x-1;i<=x+1;i++){
		if(1<=i&&i<=n)b.push_back(a[i]);
		else b.push_back(0);
	}
	sort(a.begin()+1,a.end());
	sort(b.begin(),b.end());
	if(n<=2)cout<<a[n]<<"\n";
	else cout<<max(a[3],b[1])<<"\n";
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
} 
```

---

## 作者：hgcnxn (赞：1)

## P11522 [THUPC2025 初赛] Harmful Machine Learning 题解

### 思路

将 Bot 所在的格子以及与 Bot 相邻的格子称之为关键格，其中数字最大的关键格为最关键格，其它格子称之为非关键格。所以，关键格与最关键格可以改变。

当 $n\le 2$ 时，直接输出所有格子中的最大值即可。

当 $n\ge 3$ 时，NIT 一定会尽可能减小关键格的数字的最大值。所以，NIT 每一轮的操作只有以下两种可能：

- 最关键格比数字最小的非关键格大，此时将这两格对换。
- 最关键格不比数字最小的非关键格大，随意选两个关键格对换（相当于没换）。

如果 Bot 不在第 $1$ 格或第 $n$ 格，就有一个很重要的结论：Bot 在第一回合中走到最关键格并立刻结束游戏一定是最优的。

如果 Bot 不这么做呢？不难发现，NIT 可以将关键格控制在初始的三格之内，如图所示（椭圆为机器人，颜色不为红色的格子是关键格）：
![](https://cdn.luogu.com.cn/upload/image_hosting/avzthfwg.png)

而且，NIT 还可以将数字更小的格子换为关键格，而这只会对 Bot 更劣。
因此 Bot 一定在第一轮就结束游戏。此时，得分为 NIT 操作后的最关键格的数。

如果 Bot 在第 $1$ 或第 $n$ 格呢？

假如 Bot 在第一轮结束游戏，得分即为操作后的最关键格；如果 Bot 选择离开端点而不结束游戏，那么从上文的结论可知，第二轮必然结束游戏。

现在只需求出最终得分就结束了。将上文的做法模拟一遍，可以得到：

**得分为初始关键格中第二大的格子与所有格子中第三小的格子的最大值。**

至于为什么，是因为 Bot 可以使它的周围有三个格子，所以得分最小为所有格子中第三小的格子。而不论 Bot 初始时在哪里，所能得到的最大值都不会大于第一轮操作过的最关键格，即原关键格中的第二大值。

~~结论非常简单我还吃了两发~~

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[100005],b[4];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		a[0]=a[n+1]=-2e9;
		b[0]=a[k-1],b[1]=a[k],b[2]=a[k+1];
		sort(b,b+3);
		sort(a+1,a+n+1);
		cout<<max(a[min(3,n)],b[1])<<"\n";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

我们队里的大神 @54ycy 赛后 15min 过了这道题，艹。当时队里有一个人直接开 generals 了，所以未能赛时 A 了这题。

## 思路

首先 $n\leq2$ 时可以特判掉，然后考虑剩下部分。

考虑二分答案，当数字都是 $0/1$ 时怎么做。

模拟一下会发现，在开始位置相邻的数字有两个及以上是 $1$ 时可以成功取到（其中一个被换掉时跳到另一个上即可）。

然后还要考虑边界位置的情况。边界情况只要有一个 $1$ 就可以取到。

然后二分时把大于等于 $mid$ 的数看作 $1$，小于 $mid$ 的数看作 $0$ 即可。

---

## 作者：World_Creater (赞：1)

Learn How To Use Binary Search

怎么题解里没有人写二分做法的/xia

先把 $n\leq 2$ 的部分特判一下，接下来不妨假设 $n\geq 3$。

考虑如果原来的数字序列只有 $0/1$ 怎么做。

发现我们至少需要三个 $0$，才能至少保证 The BOT 没有办法拿走 $1$，因为 The BOT 在非边界上，一步可以到达三个点作为终点。

另外，这三个 $0$ 还需要能够保证“困住” The BOT，假设 The BOT 一开始在 $x$ 且 $1<x<n$，那么我们第一次操作完之后，需要使得 $x-1,x,x+1$ 都必须是 $0$ 才能使得 The BOT 不能取到 $1$。

发现第一次这样操作过后，如果 The BOT 不动，那么我们也不动，如果 The BOT 向 $x-1$ 移动，那么我们就把原来在 $x+1$ 位置的 $0$ 移到 $x-2$ 上，反过来也是一样的。

因此我们只需要一开始在非边界位置上
“困住”了 The BOT，接下来我们就能一直“困住” The BOT。

特殊处理一下 The BOT 一开始在边界上的情况，这个时候相当于是第一次只需要两个 $0$ 来困住它，第二次开始才需要三个 $0$。

整理一下，可以得到答案为 $0$ 的充要条件为：

1. 序列里有不超过三个 $0$。
2. 初始时与 $x$ 相邻的位置里至多只有一个 $1$。

然后如果序列不是 $0/1$ 的怎么办？

二分答案，每次选一个 $mid$，判断最终答案能不能大于等于 $mid$，也就是将序列中大于等于 $mid$ 的位置当成 $1$，其他当成 $0$，然后使用上面针对 $0/1$ 序列的算法即可。

仔细讨论是可以去掉这个二分的，但是二分好写。

代码中的实现细节与上面略有不同。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,a[100005];
bool check(int x)
{
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<x)
		{
			if(abs(i-p)<=1) cnt1++;
			else cnt2++;
		}
	}
	if(p==1||p==n) return (cnt1>=2&&cnt2>=1)||(cnt1==1&&cnt2>=2);
	else return (cnt1>=3)||(cnt1>=2&&cnt2>=1);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>p;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		if(n==1) cout<<a[1]<<"\n";
		else if(n==2) cout<<max(a[1],a[2])<<"\n";
		else
		{
			int l=0,r=1e9;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(check(mid)) r=mid;
				else l=mid+1;
			}
			cout<<l-1<<"\n";
		}
	}
}
```

---

## 作者：fish_love_cat (赞：0)

赛时除去送分唯一过的。

多测没清调了一个世纪。

思路实现比较鬼畜见谅。

笑点下面大家尽情嘲讽。

![](https://cdn.luogu.com.cn/upload/image_hosting/etu55jaq.png)

---

对于 $n\le3$ 特判处理。这不困难。

对于其他情况：

首先显然的 NIT 的操作会用序列最小值替换掉 BOT 可达的三个数中的最大值。

因此一般情况下，可以注意到 BOT 的移动会被序列最小值赶着跑。而且如果迎面撞上次小值局面更加不利。所以容易得到 BOT 持续移动不会更优。

~~NIT 又不是傻，你每跑一步就只更新一个值，如果这个值更优 NIT 还不速度扔了（~~

当然有例外。如果被最小值和次小值逼在角落，BOT 可以尝试移动然后让 NIT 召唤第三小值封堵。选择第三小值显然更优。

所以无论怎么样一定可以吃到第三小值的大保底。另外可以得到无论怎么移动除了初始脚边的三个数不会有更优。

脚边三个数的最大值理论是取不到的，除非是第三小。

所以我们让脚边第二大和序列第三小取较大值作为答案。

做完了。多测。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,a[100005],p[5];
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld",&n,&x);
        a[n+1]=0;
        int maxx=-1;
        for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),maxx=max(maxx,a[i]);
        if(n<=3){
        	printf("%lld\n",maxx);
        	continue;
		}
        p[1]=a[x-1];
        p[2]=a[x];
        p[3]=a[x+1];
        sort(p+1,p+4);
        sort(a+1,a+n+1);
        printf("%lld\n",max(a[3],p[2]));
    }
    return 0;
}
/*
10 4
9 8 7 1 5 4 2 3 9 10
*/
```

代码来自：《半AFO大队场内口胡》全体成员。

---

## 作者：BrotherCall (赞：0)

每一轮到 BOT 回合的时候，设它处于的位置为 $i$，则可获得的最大分数为 $\max\{a_{i-1} , a_i , a_{i+1}\}$。

BOT 肯定希望找更大的分数嘛，但不幸的是，BOT 每向左移动一格，NIT 就可以把 $a_{i + 1}$ 和 $a_{i - 2}$ 交换；BOT 每向右移动一格，NIT 就可以把 $a_{i - 1}$ 和 $a_{i + 2}$ 交换。这导致 BOT 能选的数只由它第一回合的状态决定。

问题直接被简化成了，NIT 只操作一次，如何使 BOT 能获得的分最小。

直观上觉得，如果 $x$ 及其邻近共三个位置以外 $a$ 的最小值，比这三个位置的最大值小的话，就交换这两个位置，然后取这三个位置的最大值。

但是这还少考虑了位置 $x$ 一开始在边上的情况。

如果 $x$ 一开始在边上，就把它向左/右移动一位，使它不在边上，然后拿剩下位置的两个最小的值和邻近三个位置中最大的两个比较并交换，再取最大。

这个代码感觉不是很好写，但是基于这个思路，可以把求答案转化成 $\max($全局第三小，$x$ 和其邻近位置中的次大$)$。

因为 $x$ 和其邻近位置中的次大是 NIT 换不走的位置，而 BOT 又起码有三个数的选择，所以要和全局第三小取个 $\max$。

最后一嘴，特判一下 $n = 1$ 和 $2$。

Code：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n , x;
    cin >> n >> x;
    vector<int> a(n + 1);
    for(int i = 1;i <= n;i ++) 
        cin >> a[i];
    vector<int> ps;
    for(int i = max(1ll , x - 1);i <= min(n , x + 1);i ++) 
        ps.push_back(a[i]);
    sort(ps.begin() , ps.end());
    sort(a.begin() + 1 , a.begin() + n + 1);
    cout << max(a[min(3ll , n)] , ps[max(0ll , (int)ps.size() - 2)]) << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0) , cout.tie(0);
    int t;cin >> t;while(t --) solve();
    return 0;
}
```

---

## 作者：_xdd_ (赞：0)

可爱小黄题。

首先如果 $n\le3$ 则答案为 $a_i$ 的最大值。

当 $n>3$ 时，设当前这一回合 BOT 的位置在 $(1,i)$。

第一回合 NIT 会把 $i-1,i,i+1$ 三个位置的最大值换走，此时 BOT 可以选择取这三个位置的次大值。

第三回合及之后，按照 NIT 的策略，$i-1,i,i+1$ 一定都会被换成 $a$ 中最小的三个数，此时 BOT 可以选择 $a$ 中第三小的值。

答案即为上面两种答案的最大值。

### code


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define maxn 100000+5
//#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int a[maxn],t,n,x;
int main(){
    cin >> t;
    while(t--){
        cin >> n >> x;
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }
        int g1=a[x-1],g2=a[x],g3=a[x+1];
        if(x==1){g1=-1;}
        if(x==n){g3=-1;}
        sort(a+1,a+n+1);
        if(n<=2){
            cout << a[n] << endl;
            continue;
        }
        int ans;
        if((g1<=g2 && g1>=g3) || (g1>=g2 && g1<=g3)){
            ans=g1;
        }else if((g2<=g1 && g2>=g3) || (g2>=g1 && g2<=g3)){
            ans=g2;
        }else{
            ans=g3;
        }
        cout << max(ans,a[3]) << endl;
    }
    return 0;
}
```

---

