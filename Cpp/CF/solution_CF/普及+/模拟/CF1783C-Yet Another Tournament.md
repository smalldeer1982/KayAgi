# Yet Another Tournament

## 题目描述

You are participating in Yet Another Tournament. There are $ n + 1 $ participants: you and $ n $ other opponents, numbered from $ 1 $ to $ n $ .

Each two participants will play against each other exactly once. If the opponent $ i $ plays against the opponent $ j $ , he wins if and only if $ i > j $ .

When the opponent $ i $ plays against you, everything becomes a little bit complicated. In order to get a win against opponent $ i $ , you need to prepare for the match for at least $ a_i $ minutes — otherwise, you lose to that opponent.

You have $ m $ minutes in total to prepare for matches, but you can prepare for only one match at one moment. In other words, if you want to win against opponents $ p_1, p_2, \dots, p_k $ , you need to spend $ a_{p_1} + a_{p_2} + \dots + a_{p_k} $ minutes for preparation — and if this number is greater than $ m $ , you cannot achieve a win against all of these opponents at the same time.

The final place of each contestant is equal to the number of contestants with strictly more wins $ + $ $ 1 $ . For example, if $ 3 $ contestants have $ 5 $ wins each, $ 1 $ contestant has $ 3 $ wins and $ 2 $ contestants have $ 1 $ win each, then the first $ 3 $ participants will get the $ 1 $ -st place, the fourth one gets the $ 4 $ -th place and two last ones get the $ 5 $ -th place.

Calculate the minimum possible place (lower is better) you can achieve if you can't prepare for the matches more than $ m $ minutes in total.

## 说明/提示

In the first test case, you can prepare to all opponents, so you'll win $ 4 $ games and get the $ 1 $ -st place, since all your opponents win no more than $ 3 $ games.

In the second test case, you can prepare against the second opponent and win. As a result, you'll have $ 1 $ win, opponent $ 1 $ — $ 1 $ win, opponent $ 2 $ — $ 1 $ win, opponent $ 3 $ — $ 3 $ wins. So, opponent $ 3 $ will take the $ 1 $ -st place, and all other participants, including you, get the $ 2 $ -nd place.

In the third test case, you have no time to prepare at all, so you'll lose all games. Since each opponent has at least $ 1 $ win, you'll take the last place (place $ 6 $ ).

In the fourth test case, you have no time to prepare, but you can still win against the first opponent. As a result, opponent $ 1 $ has no wins, you have $ 1 $ win and all others have at least $ 2 $ wins. So your place is $ 4 $ .

## 样例 #1

### 输入

```
5
4 401
100 100 200 1
3 2
1 2 3
5 0
1 1 1 1 1
4 0
0 1 1 1
4 4
1 2 2 1```

### 输出

```
1
2
6
4
1```

# 题解

## 作者：liujy_ (赞：8)

 ###  题目大意   
 你和 $n$ 个选手比赛。每两个选手之间都会比一场，编号为 $i$ 的选手可以赢过所有编号小于他的选手。你想要战胜第 $i$ 个选手需要耗费 $a_i$ 的时间。你一共有 $m$ 的时间，问你的最小排名为多少。  
 
------------

 一个非常显然的思路就是贪心的选择最小的 $a_i$，这样一定可以使得战胜的人数最多。于是我们非常愉快的打完代码发现样例都过不了。  
 这个思路有一个问题，如果你不选择战胜编号为 $i$ 的选手，那么编号为 $i$ 的选手就会战胜你。假设你可以最多战胜 $cnt$ 个选手，但是你没有选择战胜编号为 $cnt+1$ 的选手，那么原本你与编号为 $cnt+1$ 的选手胜利的场数都是 $cnt$，但是由于他战胜了你，所以他的排名超过了你。   
 我们先求出直接贪心选择的排名，然后再算一遍强制选择战胜编号为 $cnt+1$ 的选手的排名。这两个去一个较小值就可以了。   
 ```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=5e5+5;
int T,n,m,t[N],ans;
struct node{
	int x,id;
	bool operator < (node y)const{
		if(x==y.x)return id>y.id;
		return x<y.x;
	}
}a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);int tmp=m;
		for(int i=1;i<=n;i++)scanf("%d",&a[i].x),a[i].id=i,t[i]=i-1;
		sort(a+1,a+n+1);int cnt=0;
		for(int i=1;i<=n;i++){
			if(m<a[i].x)t[a[i].id]++;
			else m-=a[i].x,cnt++;
		}
		int tot=0,x=0;
		for(int i=1;i<=n;i++){
			if(t[i]>cnt)tot++;
			t[i]=i-1;
			if(a[i].id-1==cnt)x=i;
		}
		cnt=0;ans=tot+1;m=tmp;
		if(m>=a[x].x)m-=a[x].x,a[x].x=m+1000,t[a[x].id]--,cnt++;
		for(int i=1;i<=n;i++){
			if(m<a[i].x)t[a[i].id]++;
			else m-=a[i].x,cnt++;
		}
		tot=0;
		for(int i=1;i<=n;i++)
			if(t[i]>cnt)tot++;
		printf("%d\n",min(ans,tot+1));
	}
	return 0;
}
```

 

---

## 作者：AllenKING_RED (赞：6)

## 题目大意

你和其他 $n$ 个选手将参加一项竞赛，每两名选手间会进行一场比赛，此时与你无关的比赛已经比完，从第 $1$ 到第 $n$ 名选手的胜场数分别为从 $0$ 到 $n-1$ 的 $n$ 个整数，你需要同这 $n$ 名选手进行比赛。

对于第 $i$ 名选手，你需要至少 $a_i$ 分钟来准备与其的比赛才能击败他，你的总准备时间为 $m$ 分钟。

现在请你求出按照胜场数排名后你的最高名次，注意这时如果我们没有选择击败一名对手那么他的胜场数会加 $1$。

$tips:$

如果 $3$ 名选手各 $5$ 胜，$1$ 名选手各 $3$ 胜，$2$ 名选手各 $1$ 胜，那么前 $3$ 名选手将获得第 $1$ 名，第 $4$ 名选手获得第 $4$ 名，最后 $2$ 名选手获得第 $5$ 名。

## 基本思路

- ###  part 1

	假设我们比赛后胜场数为 $x$，相当于在 $n$ 个选手中有 $n-x$ 个选手的胜场数会加 $1$。

	因为这 $n$ 名选手开始时的胜场数分别为 $0$ 到 $n-1$ 的整数，所以在其他选手最后一轮的胜场计算前我们与胜场数为 $x$ 的选手并列。
    
    由于胜场数最多加 $1$，所以胜场计入后我们的排名不可能落后于胜场数 $x-1$ 或超过胜场数 $x+1$ 的选手，所以我们的排名只与胜场数为 $x$ 的选手有关，如果战胜他则与其并列否则就落后他一名。
    
    此时显而易见的可以看出：如果战胜该对手后仍然能保证胜场数为 $x $ 则排名为 $n-x$ 否则为 $n-x+1$。

	现在我们可以枚举胜场数 $x$ 进行计算，但这样的时间复杂度是 $n^2$ 的不符合要求，需要优化。

- ### part 2

	我们可以得出一个关键的结论：胜场数最多时的最高排名不会低于其他情况下的最高排名。
    
	最坏情况下，假设最多胜场数为 $a$ 此时排名为 $n-a+1$，而另一种情况下胜场数为 $a-k$，排名为 $n-a+k$，因为 $a$ 为最多胜场数，所以 $k \geq 1$，所以 $n-a+1 \geq n-a+k$，上述结论可以仍然成立，所以我们可以直接考虑胜场数最大时的情况。

- ### part 3

 	根据上述结论，此时我们可以考虑先根据 $a_i$ 排序贪心求出最大胜场数，并标记此时消耗时间最少情况下剩余时间以及选择击败的对手。
    
    然后我们可以找到计入最后一轮前胜场数与我们相同的选手，此时如果我们已经选择过他，那么肯定可以战胜他，否则我们考虑将之前战胜过的对手进行替换。
    
    贪心的考虑，我们将之前消耗时间最多的对手与该对手消耗的时间进行对比，如果差值小于剩余的时间，那么我们可以替换，就可以战胜该对手，否则不可以。
    
    以上即为题解的基本思路。
    
## 代码实现

以下为赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
struct mem{
	int id;
	int sum;
}pr[N];
bool cmp(mem x,mem y)
{
	return x.sum<y.sum;
}
int a[N],vis[N];
int n,m;
int T;
signed main(void)
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			pr[i].id=i;
			pr[i].sum=a[i];
			vis[i]=0;
		}
		sort(pr+1,pr+n+1,cmp);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(m>=pr[i].sum)
			{
				ans++;
				m-=pr[i].sum;
				vis[pr[i].id]=1;
			}
		}
		int last=ans;
		int sum=n-ans+1;
		if((vis[ans+1]||m>=(a[ans+1]-pr[last].sum))&&sum>1)--sum;
		cout<<sum<<endl;
	}
	return 0;
}
```


    

---

## 作者：Air_Color5 (赞：4)

# 题目
[CF1783C题目传送门](https://www.luogu.com.cn/problem/CF1783C)
# 分析
首先，在所有你不参与的比赛中，结果都已经定好了，按照题目每组数据输入的顺序，每个人分别赢 $[0, n)$ 场（这里所有的下标都从 1 开始）。

设 $x$ 为你最终战胜了多少人。那对于编号为 $[1,x)$ 的人来说，即使他们都战胜了你，那他们赢的场数也不超过 $x$，对你没有威胁；而对于编号为 $(x,n]$ 的人来说，就算他们都输给了你，那他们赢的场数也多余 $x$，你不可能超越他们。那么，唯一对你的名次有影响的，就是编号为 $x$ 的人。如果你打败了他，那么你的名次便是 $n - x$，否则你的名次是 $n - x + 1$。

显然，让 $x$ 越大便能使排名更靠前，那么这道题目贪心的算法应该已经很显然了。我们先对 $a$ 数组排序（排完序的数组记为 $b$ 数组），然后从前往后取，直到其总和超过 $m$ 为止。那么，我们之前的 $x$ 就已经确定了。接下来，将现在的总和减去最后加上的那个数，即 $b_x$，再加上 $a_x$，如果大于 $m$，则说明不不能取，排名为 $n - x + 1$；否则能取，排名为 $n - x$。

那么怎么证明最后一步是对的呢？分类讨论即可：~~（前排提示：有点乱，不想看的可以跳过）~~

（1）若总和中已包含 $a_x$，则因为 $b$ 的不下降的特性，所以可得 $b_x \ge a_x$，既然现在的总和不大于 $m$，那减去 $b_x$ 加上 $a_x$ 也一定不大于 $m$。

（2）若总和中不包含 $a_x$，还有两种情况：

1. 总和减去 $b_x$ 加上 $a_x$ 不大于 $m$。那么这就是最好的情况了，我们不能有更高的排名了。

2. 总和减去 $b_x$ 加上 $a_x$ 大于 $m$。这说明想要保持在打赢包含第 $x$ 个人在内的共 $x$ 个人是不可能的了，如果我们硬是要打赢第 $x$ 个人，最好情况是减去 $b_x$ 和 $b_{x-1}$ 再加 $a_x$ 就不大于 $m$，打赢 $x - 1$ 个人，那排名也只能是 $n - (x - 1) + 1 = n - x$，和干脆不打第 $x$ 个人的结果是一样的。

~~终于结束了~~
# 代码
思路分析完了，最后的代码也自然要放一下。因为有排序的存在，时间复杂度 $O(n log n)$，能通过本题。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int rd(){
	int res = 0;
	bool flag = false;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-')
		flag = true;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		res = (res << 3) + (res << 1) + (48 ^ c);
		c = getchar();
	}
	return flag ? -res : res;
}
int t, n, m;
void solve(){
	int x = 0;
	n = rd(), m = rd();
	vector<int> a(n), b;
	for(int i = 0; i < n; i++)
	a[i] = rd(); // 输入 
	// 注：这份代码中， m 为剩余时间 
	b = a;
	sort(b.begin(), b.end()); // 排序 
	for(int i = 0; i < n && m >= b[i]; i++)
	// 只要数组没越界，并且总和不大于 m ，就接着从前往后取 
	m -= b[i], x++; // 花费掉 b[i] 的时间，多打败一个人 
	if(x > 0 && x < n && m + b[x - 1] - a[x] >= 0) x++;
	// 如果取了不止一个且没有全部取完并且时间还够，就能和第 x 个人并列，则排名加一 
	printf("%d\n", n - x + 1); // 输出排名 
}
int main(){
	t = rd(); // 快读输入 
	while(t--)
	solve(); // 多组测试数据 
	return 0; // 华丽地结束！ 
}
```

---

## 作者：jiangchen1234 (赞：0)

# Part 0 闲话

[原题链接(luogu)](https://www.luogu.com.cn/problem/CF1783C)

[原题链接](https://codeforces.com/problemset/problem/1783/C)

# Paat 1 分析

首先我们需要证明一点，就是当我们赢了 $x$ 时的排名。

对于 $n$ 个选手来讲，当我们不参加时，第 $i$ 名选手（$1 \le i \le n$）共赢了 $i - 1$ 局。

接下来需要分类讨论：

1. 当我们赢了第 $x + 1$ 名选手时，我们的排名是 $n - x$。

1. 当我们没有赢了第 $x + 1$ 名选手时，我们的排名是 $n - x + 1$。

接下来我们需要证明一件事，当 $x$ 最大时一定最优。

我们现设我们赢了 $x$ 场，当我们多赢一场时，我们的胜利场次为 $x + 1$。

先看 $x$ 场时，我们排名最高是 $n - x$。

再看 $x + 1$ 场时，我们的排名最低是 $n - (x + 1) + 1$，也就是 $n - x$。

由此我们根据数学归纳法知道赢的场数越多一定是越优的。

根据贪心的思想，我们可以将所要花费的时间排序，从小到大取，直到取不了了为止。

这时我们的分析还没有结束。

我们要判断我们有没有战胜第 $x + 1$ 名对手（$x$ 为最大胜利场次）。

如果战胜了的话输出 $n - x$。

否则我们需要判断我们剩下的时间加上我们花费最大的时间战胜的敌人的时间是否可以战胜他。

如果可以，最大胜利场次数不变，输出 $n - x$。

否则输出 $n - x + 1$。

分析结束啦！

# Part 2 代码

[codeforces 的提交记录](https://codeforces.com/contest/1783/submission/243909591)

代码：

```cpp
#pragma comment(linker,"ack:200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#include<bits/stdc++.h>
#define int long long
#define il inline
#define rg register
#define F(i,l,r) for(int i=l,i##end=r;i<=i##end;++i)
#define G(i,l,r) for(int i=l,i##end=r;i>=i##end;--i)
#define endl '\n'
using namespace std;
il int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
il void write(int x) {
	if(0<=x&&x<=9) {
		putchar(x + '0');
		return ;
	}
	write(x/10);
	putchar(x%10+'0');
}
il int max(int a,int b) {
	return a > b ? a : b;
}
il int min(int a,int b) {
	return a < b ? a : b;
}
struct node{
	int a,b;
};
node a[500005];
int b[500005];
bool flag[500005];
il bool cmp(node x,node y){
	return x.a < y.a;
}
il void solve(){
	int n = read(),m = read(),maxx = 0;
	F(i,1,n) b[i] = read(),a[i].a = b[i],a[i].b = i;
	sort(a + 1,a + n + 1,cmp);
	F(i,1,n){
		if(a[i].a <= m){
			m -= a[i].a;
			++maxx;
			flag[a[i].b] = 1;
		}else{
			break;
		}
	}
	int ans = n - maxx + 1;
	if(flag[maxx + 1] || m >= ((b[maxx + 1] - a[maxx].a)) && ans > 1) --ans;
	cout<<ans<<endl;
	F(i,1,n) flag[i] = 0;
}
signed main() {
	int T = read();
	while(T--){
		solve();
	}
	return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：0)

最近打 CF 总是做不出 $1500 \sim 1800$ 的题，于是就板刷这个难度，然后……这题不应该……$1200$ 吗？

**【题目分析】**

我们转化一下原题意：

两个序列 $c,a$，其中 $c_i = i$，$a_i$ 是输入的值。你有的钱数是 $m$，同时你还有一个初始为 $0$ 的变量 $x$，可以选择花费 $a_i$ 的代价使 $c_i \gets c_i -1,x \gets x+1$，但是每个 $i$ 只能被选择一次。问最终 $x$ 在 $c$ 序列的最高排名是多少（即排名的最低数值）。

显然的贪心是我们希望最大化 $x$ 的数值。这是好证的。考虑每个 $c_i$ 最多只能减少 $1$，因此增大 $x$ 的值一定不劣于让某一个 $c_i \gets c_i - 1$。因此我们先给 $a$ 排序，并求出最多能让 $x$ 增加几。

此时又有一个思路：我们能否降低 $x+1$ 位置的数字的值？这样排名就会更优。我们贪心的希望把 $a$ 第 $x$ 大的数字和**排序前** $a_{x+1}$ 的代价调换，判断是否仍然合法。如果合法排名就能更优。

时间复杂度瓶颈在排序上，时间复杂度 $\mathcal O(n \log n)$。

感觉到不了绿捏。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
struct pp{int a,b;}a[500005];
bool cmp(pp aa,pp bb){return aa.a < bb.a;}
int main(){
    cin >> t;
    while(t --){
        cin >> n >> m;
        for(int i = 1;i <= n;i ++) cin >> a[i].a,a[i].b = i;
        sort(a+1,a+n+1,cmp);int cnt = 0,i,p;
        for(i = 1;i <= n;i ++) if(m >= a[i].a) cnt ++,m -= a[i].a; else break;
        if(cnt == n) {cout << "1\n";continue;}
        for(int j = 1;j <= n;j ++) if(a[j].b == cnt + 1) {p = j;break;}
        cout << n - (cnt + (a[p].a - a[i-1].a <= m)) + 1 << "\n";
    }
}
```

---

## 作者：masonpop (赞：0)

首先，我们先限定此人胜利场数为 $x$，考虑其排名。

注意到关键性质：对于编号为 $[1,x]$ 的选手，他们不可能超越我。而对于编号 $[x+2,n]$ 的选手，我们不可能达到他们的高度。因此，我们直接考虑标号为 $x+1$ 的选手。如果我们战胜了他，则排名为 $n-x$，否则排名为 $n-x+1$。

所以，我们在限定 $x$ 的情况下，最小胜利次数和最大胜利次数只相差一。因此可以断定，一定存在最优解是最大化 $x$ 的。

首先先将序列排序，贪心的选择代价小的准备。然后，我们考虑能否战胜标号为 $x+1$ 的选手。如果已经准备了他当然就可以。否则，我们考虑能否把代价最大的选手换成它即可。

一定注意这里的标号是原来的序号，别把数组弄混了。

时间复杂度 $O(n\log n)$，瓶颈在于排序。[代码](https://www.luogu.com.cn/record/112641155)。

---

## 作者：青鸟_Blue_Bird (赞：0)

## 题目大意

首先容易推出假如不算我们自己，那么剩下的敌人的得分就是数列 $a_i = i$。现在我们要做的就是花一定数量的时间来训练对应一部分敌人，打败他们同时自己获得一分（当然被打败的那个敌人就少获得一分）。

## 主要思路

容易想到我们肯定是想要自己的分尽量高，那么显然就是贪心，从小到大选择花费时间最小的敌人，一直到总和超过 $m$ 为止。但存在一个问题，就是未被我们选中的敌人会增加 $1$ 分。下面就此进行讨论。

假设我们按照贪心的方法选择了 $k$ 个敌人进行训练，那么容易知道 $k$ 就是我们自身的最大得分。假设有一敌人的初始得分大于 $k$, 那我们完全就可以忽略他。因为显而易见的是无论我们如何“努力”，我们都不可能战胜他。对于初始得分小于 $k$ 的敌人，显然排名永远会落后我们。所以，我们只需要考虑剩下一个唯一情况，就是初始得分等于 $k$ 的人。假设我们在**保持总分不变的情况下**没有选择战胜他，那么我们就会损失一个排名。所以尝试将该人与最大值进行交换，尽可能选中他。

## 正确性

下面简略说一下上述方法的正确性（最优性）。假设我们的得分为 $k$, 那么我们能战胜的敌人就是 $k$ 个（不算临界情况）。如果我们能将临界者战胜，就是 $k+1$ 个。如果为了加入当前临界者而导致 $k$ 减少一，显然也不优。所以最大化 $k$ 并尽量拉入临界者是最优做法。

## 代码时间

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 500010

int n, m; 

struct node{
    int w, id; 
} t[N]; 
int a[N]; 
int b[N];

bool cmp1(node a, node b){
    return a.w < b.w; 
}

int main(){
    int T; cin >> T; 
    while(T--){
        cin >> n >> m; 
        for(int i = 1; i <= n; i++){
            cin >> t[i].w;
            t[i].id = i; 
            a[i] = t[i].w; 
        } 
        sort(t + 1, t + n + 1, [](node a, node b){
            return a.w < b.w; 
        }); 
        bitset <N> vis(0); 
        int sum = 0, maxn = n, ans = 0; 
        for(int i = 1; i <= n; i++){
            if(sum + t[i].w > m){
                maxn = i-1; 
                break; 
            } 
            sum += t[i].w;
            vis[t[i].id] = 1; 
            ans++; 
        }
        if(!vis[ans+1]){
            if(sum - t[maxn].w + a[ans+1] <= m){
                vis[ans+1] = 1;
                vis[t[maxn].id] = 0; 
            }
        }
        for(int i = 1; i <= n; i++)
            b[i] = i - 1 + (!vis[i]);
        b[n+1] = ans; 
        sort(b + 1, b + n + 2, [](int a, int b) -> bool {return a > b; });  // 排序计算排名
        int num = 0; 
        for(int i = 1; i <= n + 1; i++){
            num++; 
            if(b[i] == ans){
                break; 
            }
        }
        cout << num << endl; 
    }
    return 0; 
}
```

---

## 作者：honglan0301 (赞：0)

## 题意简述

你和 $n$ 个编号为 $1,2,\cdots,n$ 的人参加单循环比赛，在不考虑你的胜负时，编号为 $i$ 的人获胜 $i-1$ 场。你共有 $m$ 的时间，对于每一个人，你可以花费 $a_i$ 的时间赢得与 $i$ 的比赛（否则输给他），求你最终可以获得的最优排名。

## 题目分析

容易发现我们与其他人的比赛结果不影响其它人的相对排名（即编号为 $i$ 的人最终胜场不可能大于编号为 $i+1$ 的人）。于是考虑先贪心地赢得最多的比赛。

假设此时我们的胜场为 $x$, 则显然编号 $\leq x$ 的人不可能比我们赢得多，而编号 $\geq x+2$ 的人一定比我们赢得多。那么只需考虑我们与编号为 $x+1$ 的人的胜负关系，即如果能在保证胜场不变的前提下（胜场减小显然不优）赢得与 $x+1$ 的比赛，则答案为 $n-x$, 否则答案为 $n-x+1$。时间复杂度取决于排序的 $O(n\log n)$, 可以通过本题。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int t,n,m,ans,sum,b[500005],flag;

struct a
{
	int num,bh;
}a[500005];
bool cmp(struct a xx,struct a yy) {return xx.num<yy.num;}

int main()
{
	cin>>t;
	while(t--)
	{
		flag=0;
		cin>>n>>m; for(int i=1;i<=n;i++) {cin>>a[i].num; b[i]=a[i].num; a[i].bh=i;}
		sort(a+1,a+n+1,cmp);
		int nowm=m,nowcnt=0;
		for(int i=1;i<=n;i++)
		{
			if(nowm>=a[i].num) {nowm-=a[i].num; nowcnt++;}
			else break;
		}
		for(int i=1;i<=nowcnt;i++)
		{
			if(a[i].bh==nowcnt+1) {flag=1; break;}
		}
		if(flag||nowm+a[nowcnt].num>=b[nowcnt+1]) cout<<max(n-nowcnt,1)<<endl;
		else cout<<n-nowcnt+1<<endl;
	}
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# CF1783C 题解



## 思路分析

显然首先应该击败尽可能多的人，这一步可以按 $a_i$ 小到大贪心。

然后假设你已经确定你最多击败 $k$ 个人，那么第 $1\sim k$ 个人获胜次数一定不超过 $k$，第 $k+2\sim n$ 个人获胜次数一定超过 $k$，而第 $k+1$ 个人获胜次数为 $k$ 或 $k+1$，假如你能在不影响获胜次数的前提下击败 $k+1$，你的排名会更高。

因此你只需要优先击败 $k+1$，然后判断剩下的 $m$ 够不够你再击败 $k-1$ 个人即可。

时间复杂度 $\Theta(n\log n)$，瓶颈在对 $\{a_i\}$ 排序上。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int> 
using namespace std;
const int MAXN=5e5+1;
int n,m,a[MAXN];
inline int calc(const vector<pii> &p) {
	int lim=m;
	for(int i=0;i<n;++i) {
		if(p[i].first>lim) return i;
		lim-=p[i].first;
	}
	return n;
}
inline void solve() {
	scanf("%lld%lld",&n,&m);
	vector <pii> p;
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),p.push_back(make_pair(a[i],i)); 
	sort(p.begin(),p.end());
	int ans=calc(p);
	if(ans==n) printf("1\n");
	else if(ans==0) printf("%lld\n",n+1);
	else {
		for(int i=0;i<n;++i) {
			if(p[i].second==ans+1) {
				auto del=p[i];
				p.erase(p.begin()+i);
				p.insert(p.begin(),del);
			}
		}
		if(calc(p)==ans) printf("%lld\n",n-ans);
		else printf("%lld\n",n-ans+1);
	}
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```

---

