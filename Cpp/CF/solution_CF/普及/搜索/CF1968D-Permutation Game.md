# Permutation Game

## 题目描述

Bodya and Sasha found a permutation $ p_1,\dots,p_n $ and an array $ a_1,\dots,a_n $ . They decided to play a well-known "Permutation game".

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

Both of them chose a starting position in the permutation.

The game lasts $ k $ turns. The players make moves simultaneously. On each turn, two things happen to each player:

- If the current position of the player is $ x $ , his score increases by $ a_x $ .
- Then the player either stays at his current position $ x $ or moves from $ x $ to $ p_x $ .

 The winner of the game is the player with the higher score after exactly $ k $ turns.Knowing Bodya's starting position $ P_B $ and Sasha's starting position $ P_S $ , determine who wins the game if both players are trying to win.

## 说明/提示

Below you can find the explanation for the first testcase, where the game consists of $ k=2 $ turns.

 TurnBodya's positionBodya's scoreBodya's moveSasha's positionSasha's scoreSasha's movefirst $ 3 $  $ 0 + a_3 = 0 + 5 = 5 $ stays on the same position $ 2 $  $ 0 + a_2 = 0 + 2 = 2 $ moves to $ p_2=1 $ second $ 3 $  $ 5 + a_3 = 5 + 5 = 10 $ stays on the same position $ 1 $  $ 2 + a_1 = 2 + 7 = 9 $ stays on the same positionfinal results $ 3 $  $ 10 $  $ 1 $  $ 9 $ As we may see, Bodya's score is greater, so he wins the game. It can be shown that Bodya always can win this game.

## 样例 #1

### 输入

```
10
4 2 3 2
4 1 2 3
7 2 5 6
10 8 2 10
3 1 4 5 2 7 8 10 6 9
5 10 5 1 3 7 10 15 4 3
2 1000000000 1 2
1 2
4 4
8 10 4 1
5 1 4 3 2 8 6 7
1 1 2 1 2 100 101 102
5 1 2 5
1 2 4 5 3
4 6 9 4 2
4 2 3 1
4 1 3 2
6 8 5 3
6 9 5 4
6 1 3 5 2 4
6 9 8 9 5 10
4 8 4 2
2 3 4 1
5 2 8 7
4 2 3 1
4 1 3 2
6 8 5 3
2 1000000000 1 2
1 2
1000000000 2```

### 输出

```
Bodya
Sasha
Draw
Draw
Bodya
Sasha
Sasha
Sasha
Sasha
Bodya```

# 题解

## 作者：spire001 (赞：7)

## CF1968D题解

### 题目大意

`Bodya` 和 `Sama` 发现了一个排列 $p_1,\dots,p_{n}$ 和一个序列 $a_1,\dots,a_{n}$。

他们都选择了排列的起始位置。

如果棋手当前的位置是 $x$ ，他的得分就会增加 $a_x$。

他们每个回合可选择两种操作之一：要么停留在当前位置 ，要么从 $x$ 移动到 $p_x$。

在 $k$ 个回合后，得分较高的一方即为获胜者。求最优策略下的胜者。

### 分析

首先，最优策略的存在性是可以确定的，毕竟肯定存在一种或多种策略使最后得分最大。

那么怎样最优呢？

从直觉的角度，感觉如果 $k$ 很大的话到某一个很优的位置后待着不动最优，如果 $k$ 很小的话直接暴力求最优值就可以了。

证明其实也好证明，如果最优策略是逛完一圈后再回到某个位置不动的话，那么直接到这个位置不动不就更优了吗。。

所以我们可以直接暴力枚举停留位置，如果某个位置到了两遍说明逛完一轮了，最优答案已经出来了。

### CODE

```cpp
# include <iostream>
# include <climits>
# include <cstring>
# include <algorithm>
# include <vector>
# include <cstdio>

using namespace std;
constexpr int N = 2e5 + 20;

int T, n, k;
int a[N], b[N], sa, sb;
int box[N];
void solve()
{
	cin >> n >> k >> sa >> sb;
	
	for(int i = 1; i <= n; i++) cin >> b[i];
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	int tk = k;
	long long sum1 = 0, sum2 = 0, ns = 0;
	
	for(int i = sa; tk; i = b[i])// 记得判断 k 比较小的情况
	{
		if(box[i]) break; box[i] = 1;
		
		sum1 = max(sum1, ns + (long long)a[i] * tk);
		tk--; ns += a[i];
	}
	
	ns = 0; memset(box, 0, sizeof box);
	
	for(int i = sb; k; i = b[i])
	{
		if(box[i]) break;
		box[i] = 1;
		
		sum2 = max(sum2, ns + (long long)a[i] * k);
		k--; ns += a[i];
	}
	
	memset(box, 0, sizeof box); // 记得清空标记数组
	
	if(sum1 == sum2) cout << "Draw\n";
	else cout << (sum1 > sum2 ? "Bodya\n" : "Sasha\n");
	
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> T;
	
	while(T--) solve();
	
	return 0;
}

```

---

## 作者：DrAlfred (赞：6)

摘要：图论，简单博弈

[传送门：https://www.luogu.com.cn/problem/CF1968D](https://www.luogu.com.cn/problem/CF1968D)

## 题意

给定一个长度为 $n$ 的数列 $a_1, a_2, \cdots, a_n$ 与一个长度为 $n$ 的排列 $p$。`Bodya` 与 `Sasha` 两人玩一个游戏，游戏持续 $k$ 轮。`Bodya` 与 `Sasha` 两人分别一开始在 $P_B, P_S$ 两个位置，每一轮玩家都会做以下两件事情：

- 如果当前该玩家停留的位置为 $x$，则他的分数增加 $a_x$；
- 该玩家可以选择停留在当前位置 $x$ 或前往 $p_x$。

若 `Bodya` 与 `Sasha` 都采取最优策略，最终谁的分数更高？输出分数更高者的名字，若分数相等输出 `Draw`。

## 分析思路

我们以样例中的第四组数据为例：

```
8 10 4 1
5 1 4 3 2 8 6 7
1 1 2 1 2 100 101 102
```

由于两人在排列上移动，排列之间互相到达的关系又可以视作是一个有向图（基环森林），可以证明两个人最终能到达的点个数有限。例如样例可以看作如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xyqfnmqu.png)

`Bodya` 先后能到达的点是 $\{4, 3\}$，`Sasha` 先后能到达的点是 $\{1, 5, 2\}$。两人先后能到达的点我们可以使用 `dfs` 或其他方法求出。

然后我们考虑两人的最优策略。注意到两人最终应该会在某个点停止不动。我们可以枚举他们最终停下的点 $pos$。设从他们各自的起点 $P$ 到当前点 $pos$ 经历了 $x$ 步（$0 \leq x \leq k$），路径上经过的所有点的点权和为 $sum$，则最终的答案即为 $sum + (k - x) \times a_{pos}$。我们只要找到这个表达式的最大值，暴力枚举即可。

时间复杂度 $O\left(n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
using i64 = long long;
using i128 = __int128;
i64 t, n, k, pb, ps, a[N], p[N];
inline void solve(void) {
    cin >> n >> k >> pb >> ps;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    set<int> B, S;
    vector<int> BR, SR;
    for (; !B.count(pb); pb = p[pb]) {
        B.insert(pb), BR.push_back(pb);
    }
    for (; !S.count(ps); ps = p[ps]) {
        S.insert(ps), SR.push_back(ps);
    }
    i64 maxB = 0, maxS = 0, bSum = 0, sSum = 0;
    for (int i = 0; i <= min((size_t)k, BR.size() - 1); i++) {
        maxB = max(maxB, bSum + (k - i) * a[BR[i]]);
        bSum += a[BR[i]];
    }
    for (int i = 0; i <= min((size_t)k, SR.size() - 1); i++) {
        maxS = max(maxS, sSum + (k - i) * a[SR[i]]);
        sSum += a[SR[i]];
    }
    if (maxB > maxS) {
        cout << "Bodya\n";
    } else if (maxB == maxS) {
        cout << "Draw\n";
    } else {
        cout << "Sasha\n";
    }
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Pursuewind (赞：5)

简单题赛时都写了 30 分钟，菜。

## 题意简述

给你 $n,k,A,B$，和一个排列 $p_{1 \sim n}$，还有 $a_{1 \sim n}$

Bodya 和 Sasha 两个人初始时在点 $A$ 和点 $B$，他们都可以移动 $k$ 次，对于每一次，如果他们在点 $x$，他们的得分就会增加 $a_x$，然后他们有 $2$ 种选择：呆在原地或者移动到 $p_x$。

两人绝顶聪明，谁会赢（或报告平局）呢？

## 做法

我们发现，当 $k$ 很大时，他们很可能会移动到点权最大的点，然后呆在上面不动了。

$k$ 较小时怎么样呢？

类似的，他们的策略都是先移动到点 $i$，然后呆在 $i$ 上不动了。

于是可以进行 BFS，具体见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int inf = (1 << 31) - 1;
int n, k, A, B, cnt, dis[N], vis[N];
int p[N], a[N], ans[N];
struct node{
	int now, res, step;
};
queue <node> q;
void Record(int now, int res, int step){
	if (vis[now]) return ;
	vis[now] = 1;
	ans[now] = res + (k - step) * a[now]; //移动到点 now 然后不动了
	q.push({now, res, step});
}
void BFS(int s){
	while (!q.empty()) q.pop();
	Record(s, 0, 0);
	while (!q.empty()){
		int x = q.front().now;
		int res = q.front().res;
		int step = q.front().step;
		if (step >= k) return ;
		q.pop();
		Record(p[x], res + a[x], step + 1);
	}
}
void init(){
	for (int i = 1; i <= n; i ++){
		ans[i] = vis[i] = 0;
	}
}
void solve(){
	cin >> n >> k >> A >> B;
	for (int i = 1; i <= n; i ++){
		cin >> p[i];
	}
	for (int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	init();
	int ansa = 0, ansb = 0;
	BFS(A);
	for (int i = 1; i <= n; i ++){
		ansa = max(ansa, ans[i]);
	}
	init();
	BFS(B);
	for (int i = 1; i <= n; i ++){
		ansb = max(ansb, ans[i]);
	}
	if (ansa > ansb){
		cout << "Bodya";
	}
	if (ansb > ansa){
		cout << "Sasha";
	}
	if (ansa == ansb){
		cout << "Draw";
	}
	cout << "\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
```

---

## 作者：ilibilib (赞：1)

## 分析：

`Beyond` 和 `Sama` 玩游戏。

考虑贪心，显然他们两人只有初始位置的区别，所以贪心策略应该是一样的。

我们思考操作的意义：

去往 $p_x$。为什么要去 $p_x$ 呢？当然是为了去到一个 $a$ 更大位置，这样停留的时候就能得到更高的分数，那么显然在途中停留不会优于在那么个 $a$ 更大的终点停留。

那么显然，最终是在一个地方停留下来的，然后不断的加 $a$。

在哪儿停呢？枚举就行了，毕竟 $n\leq 2\times10^5$，也就是一直跳 $p_x$，直到重复（因为这样就没意义了）。

## code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],p[N];
bool f[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int n,k,m,p1,p2,s1=0,s2=0,s=0;
		cin>>n>>k>>p1>>p2;
		for(int i=1;i<=n;++i) cin>>p[i];
		for(int i=1;i<=n;++i) cin>>a[i];
		m=k;
		do
		{
			if(f[p1]) break;
			f[p1]=true;
			s1=max(s1,s+m*a[p1]);
			s+=a[p1];
			p1=p[p1];
		}
		while(m--);
		for(int i=1;i<=n;++i) f[i]=false;
		m=k;s=0;
		do
		{
			if(f[p2]) break;
			f[p2]=true;
			s2=max(s2,m*a[p2]+s);
			s+=a[p2];
			p2=p[p2];
		}
		while(m--);
		for(int i=1;i<=n;++i) f[i]=false;
		if(s1>s2) cout<<"Bodya\n";
		else if(s1==s2) cout<<"Draw\n";
		else cout<<"Sasha\n";
	}
	return 0;
}
```

---

## 作者：ys_kylin__ (赞：0)

不难发现，两人换的位置是有规律的，具体来说，是一个循环。而要想得到的分数最大，那就是循环到某个位置，一直不动。不难发现，绝对不存在换到以前换过的位置且分数最大的情况，因为这种情况绝对比不上换到某个已经走过的数值最大的点位一直不动的得分。所以可以考虑广搜，搜到每个点都计算一直在那个点位的最高得分，再取最大值。在这期间，一旦走到走过的点，立刻退出。最后进行比较。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int p[200005],a[200005],vis[200005],sc[200005];//sc计算停在每个点的最终得分
int n,k;
struct node {
	int x,stp,val;
}q[200005];
void bfs(int st) {
	int head=1,tail=1;
	q[head].x=st,q[head].stp=0,q[head].val=0;
	vis[st]=1;
	sc[st]=k*a[st];//一直不动
	while(head<=tail) {
		int x=q[head].x;
		if(q[head].stp>=k) return;//走到次数限制退出
		if(vis[p[x]]) return;//走到走过的点退出
		tail++;
		q[tail].stp=q[head].stp+1,q[tail].x=p[x],q[tail].val=q[head].val+a[x]; //移动位置，计算分数
		vis[p[x]]=1;
		sc[p[x]]=q[tail].val+(k-q[tail].stp)*a[p[x]];//计算停在这个点的最终得分
		head++;
	}
}
signed main() {
	int t;
	scanf("%lld",&t);
	while(t--) {
		int s1,s2;
		scanf("%lld%lld%lld%lld",&n,&k,&s1,&s2);
		for(int i=1;i<=n;i++) {
			scanf("%lld",&p[i]);
		}
		for(int i=1;i<=n;i++) {
			scanf("%lld",&a[i]);
		}
		bfs(s1);
		int sum1=0;
		for(int i=1;i<=n;i++) {
			sum1=max(sc[i],sum1);
		}
		memset(vis,0,sizeof vis);
		memset(sc,0,sizeof sc);
		bfs(s2);
		int sum2=0;
		for(int i=1;i<=n;i++) {
			sum2=max(sc[i],sum2);
		}
		memset(vis,0,sizeof vis);
		memset(sc,0,sizeof sc);
      //比较
		if(sum1>sum2) printf("Bodya\n");
		if(sum1==sum2) printf("Draw\n");
		if(sum1<sum2) printf("Sasha\n");
	}
	return 0;
}

```

---

## 作者：HasNoName (赞：0)

### 思路

对于每个人，由于 $p$ 是一个长度为 $n$ 的排列，所以 $n$ 次跳转之后回到原点。对于每一个点，如果这一个点最优，则之前的数相加再加上后面的次数乘这个数一定最优。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int a[N],ne[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,n,k,x,y;
    cin>>T;
    while(T--)
    {
        cin>>n>>k>>x>>y;
        for(int i=1;i<=n;i++)
        {
            cin>>ne[i];
        }
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        long long ansa=0,ansb=0,suma=0,sumb=0,p=k,q=n;//q表示长度为n的循环节
        while(q>=0&&p>=0)
        {
            ansa=max(ansa,a[x]*p+suma);//得出之前的数相加再加上后面的次数乘这个数
            p--;
            q--;
            suma+=a[x];
            x=ne[x];//下一项
        }
        p=k;q=n;
        while(q>=0&&p>=0)
        {
            ansb=max(ansb,a[y]*p+sumb);
            p--;
            q--;
            sumb+=a[y];
            y=ne[y];
        }
        //cout<<ansa<<' '<<ansb<<' ';
        if(ansa>ansb)cout<<"Bodya\n";
        else if(ansa<ansb)cout<<"Sasha\n";
        else cout<<"Draw\n";
    }
    return 0;
}
```

---

## 作者：junee (赞：0)

# CF1968D 题解

## 前置知识

图论，博弈论。

## 题目分析

对于本题来说，由于 $k$ 比较大，而 $n$ 比较小，所以我们可以知道，对于任意一个人，最终都会停在他可以走到的一个点上。我们不妨枚举每个人跳到第 $x$ 个点时停下不动可以获得的最大值，然后做比较。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
const int N=2e5+10;
LL n,m,x,y;
LL p[N],a[N],st[N];
int T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		LL tt=0,sum=0,ans=0,res=0;
		cin>>n>>m>>x>>y;
		for(int i=1;i<=n;i++)cin>>p[i];
		for(int i=1;i<=n;i++)cin>>a[i];
		memset(st,0,sizeof st);
		while(1){
			if(tt>m||st[x])break;
			st[x]=1;
			ans=max(ans,sum+(m-tt)*a[x]);
			tt++;
			sum+=a[x];
			x=p[x];
		}
		tt=0,sum=0;
		memset(st,0,sizeof st);
		while(1){
			if(tt>m||st[y])break;
			st[y]=1;
			res=max(res,sum+(m-tt)*a[y]);
			tt++;
			sum+=a[y];
			y=p[y];
		}
		if(ans>res){
			cout<<"Bodya"<<'\n';
		}
		else if(ans==res){
			cout<<"Draw"<<'\n';
		}
		else{
			cout<<"Sasha"<<'\n';
		}
	}
	return 0;
}

```

---

## 作者：Special_Tony (赞：0)

# 思路
首先他们两人都一定是移动一段时间后永远停在某个位置上分，不可能是转了一圈回到起点（因为他不如留在那个最大分数的点），所以我们只要沿着 $p_i$ 跑一圈遍历，选择最终得分最大的那个店就好了，另一个人同理。另外注意可能出现跑不满一圈的情况，那跑到第 $k$ 个点就退出循环。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, k, sb, ss, p[200005], now, x;
ll maxb, maxs, sum, a[200005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> k >> sb >> ss;
		for (int i = 1; i <= n; ++ i)
			cin >> p[i];
		for (int i = 1; i <= n; ++ i)
			cin >> a[i];
		maxb = maxs = sum = 0, now = sb, x = k;
		do {
			maxb = max (maxb, x * a[now] + sum);
			sum += a[now];
			-- x;
			now = p[now];
		} while (~x && now != sb);
		sum = 0, now = ss, x = k;
		do {
			maxs = max (maxs, x * a[now] + sum);
			sum += a[now];
			-- x;
			now = p[now];
		} while (~x && now != ss);
		cout << (maxb > maxs ? "Bodya\n" : maxb < maxs ? "Sasha\n" : "Draw\n");
	}
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：0)

# 题解 CF1968D - Permutation Game

### 题意

已提交翻译。

给定长度为 $n$ 的**排列** $p$ 和长度为 $n$ 的数组 $a$，现在 Bodya 和 Sasha 分别位于 $P_B,P_S$，并进行一个游戏。游戏共有 $k$ 轮，玩家的初始得分为 $0$，每轮每个玩家的过程均如下：
- 设玩家所在的位置为 $x$，则其得分增加 $a_x$。
- 玩家可以选择待在 $x$，也可以走到 $p_x$。

求双方都按最优策略进行的前提下谁会赢。若平局，输出 `Draw`。

数据范围：$\sum n\le 2\times10^5$。

### 做法

显然我们要求出两人的最大得分，然后进行比较。所以现在考虑如何求出一个人的最大得分。

做过从 $x$ 跳 $p_x$ 这种操作的应该知道，只要这么一直跳，早晚会进一个环。所以如果 $k$ 足够大，我就可以跳到可能经过的点里 $a$ 最大的那个，然后赖在那里，这样一定最优。但是 $k$ 可能不够大。所以我可以从起点一直跳，并维护跳到的点的最大值，每到一个新的最大值就判一下赖在这里是否更优即可。

然后比较两人的最大值即可。复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll t,n,k,sa,sb,p[200010],a[200010];
bool vis[200010];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>sa>>sb;
		sa--;sb--;
		for(int i=0;i<n;i++){
			cin>>p[i];
			p[i]--;
		}
		for(int i=0;i<n;i++)cin>>a[i];
		memset(vis,0,sizeof(vis));
		ll mxa=0,cnt=0,tot=0,mxx=0,mxb=0;
		while(cnt<k&&!vis[sa]){
			vis[sa]=1;
			if(a[sa]>mxx){
				mxx=a[sa];
				mxa=max(mxa,tot+a[sa]*(k-cnt));
			}
			cnt++;
			tot+=a[sa];
			sa=p[sa];
		}
		mxx=0;cnt=0;tot=0;
		memset(vis,0,sizeof(vis));
		while(cnt<k&&!vis[sb]){
			vis[sb]=1;
			if(a[sb]>mxx){
				mxx=a[sb];
				mxb=max(mxb,tot+a[sb]*(k-cnt));
			}
			cnt++;
			tot+=a[sb];
			sb=p[sb];
		}
		if(mxa==mxb){
			cout<<"Draw";
		}
		else if(mxa>mxb){
			cout<<"Bodya";
		}
		else{
			cout<<"Sasha";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：

- 这题做法挺妙的。首先先来分析题目，得出一下几点：
1. $\forall p_i \in{1,2,3,\dots,n-1,n}$。
1.  所有的 $p_i$ 都是唯一的。
1. 进行题目中的操作，位置 $x$，变为位置 $p_x$，就能找到在 $k$ 回合内能走到的 $a_x$ 的最大值。
- 有些人可能会疑问，第三点有是咋求出来的，我就来解释解释。根据第一点和第二点可得知，至多 $n$ 次，能走到不重复的位置。那么，题目不就转化为在所有能走到的位置 $x$ 中找到最大的值 $a_x$，之后的 $k-\lvert x\rvert+1$ 个回合内，每一次得分都得到 $a_x$，在之前的 $\lvert x\rvert-1$ 个回合，每一次得分也相应增加 $a_i$。（$\lvert x\rvert$ 的意思为到 $x$ 需要的最小回合数）。所以本程序的复杂度约为 $O(n)$。

### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int b[200010];
int s[200010];
long long  p[200010];
long long a[200010];
int sum1[200010];
int sum2[200010];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,pb,ps;
		cin>>n>>k>>pb>>ps;
		int mx=0;
		for(int i=1;i<=n;i++)
		{
			cin>>p[i];
		}
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int ku=min(k,n);
		int id1=k+1;
		long long sum1=0;
		long long mx1=0;
		for(int i=1;i<=ku;i++)
		{
			mx1=max(mx1,sum1+a[pb]*(k-i+1));
			sum1+=a[pb];
			pb=p[pb];
		}
		int id2=k+1;
		long long sum2=0;
		long long mx2=0;
		for(int i=1;i<=ku;i++)
		{
			mx2=max(mx2,sum2+a[ps]*(k-i+1));
			sum2+=a[ps];
			ps=p[ps];
		}
		//cout<<mx1<<" "<<mx2<<endl;
		if(mx1>mx2)
		{
			cout<<"Bodya";
		}
		else if(mx1<mx2)
		{
			cout<<"Sasha";
		}
		else
		{
			cout<<"Draw";
        }
		cout<<endl;
	}
}
```
[AC 记录](https://codeforces.com/contest/1968/submission/259226079)

---

