# Cutting Game

## 题目描述

Urej 喜欢玩各种类型的沉闷游戏。他通常会邀请其他人和他一起玩。他说，玩这些游戏可以展现他的非凡智慧。最近，Urej 对一个新游戏产生了极大兴趣，而 Erif Nezorf 成为了牺牲品。为了摆脱玩这样一个沉闷游戏的痛苦，Erif Nezorf 请求你的帮助。这个游戏使用一个由 $W \times H$ 格网组成的矩形纸张。两名玩家轮流将纸张切割成两个矩形部分。在每个回合中，玩家可以横向或纵向切割，保持每个格网完整。经过 $N$ 轮后，纸张将被切割成 $N+1$ 片，然后在后续的回合中，玩家可以选择任意一片进行切割。如果一名玩家切割出一个只有一个格网的纸片，他就赢得了游戏。如果这两个人都非常清楚，你应该写一个问题来告诉是否先手的玩家能赢得游戏。

## 样例 #1

### 输入

```
2 2
3 2
4 2```

### 输出

```
LOSE
LOSE
WIN```

# 题解

## 作者：fish_love_cat (赞：13)

前置芝士：[SG 函数](https://zhuanlan.zhihu.com/p/562117547)。

---

分讨写不出来，还是老老实实用 SG 函数做吧。

要两次判断，一次考虑剪长，一次考虑剪宽，剪完后递归求解子局面，结果异或后记录，对记录下来的求 $\operatorname{mex}$ 得出即可得出函数值。

注意不可以剪出一边为 $1$，不然对手直接能赢，所以循环边界条件要注意。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sg[205][205];
int SG(int n,int m){
	if(sg[n][m]!=-1)return sg[n][m];
	int f[205]={};
	for(int i=2;i<=n-2;i++)f[SG(i,m)^SG(n-i,m)]=1;
	for(int i=2;i<=m-2;i++)f[SG(n,i)^SG(n,m-i)]=1;
  	//注意边界
	for(int i=0;i<=200;i++)
	if(!f[i])return sg[n][m]=i;
}
signed main(){
	memset(sg,-1,sizeof sg);
	int n,m;
	while(cin>>n>>m)
	puts(SG(n,m)?"WIN":"LOSE");
	return 0;
}
//最优解 = 打表
//:-(
```

---

瑞平：写分讨写出 $21$ 次[提交](https://www.luogu.com.cn/record/list?pid=P10501&user=754021)，怒挂 $17$ 发，挤占大量评测姬资源，谴责。

---

## 作者：bianshiyang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P10501)

对此题博弈论进行较完整的证明。感觉现有的题解以及蓝书都没仔细解释为什么将 $1\times 1$ 的纸张作为必败边界是错的。

# 分析
写博弈论的题一定要知道每一步操作是在有向图游戏内移动了一条边还是在选择走哪个有向图游戏，简单来讲就是要知道什么时候取 $\operatorname{mex}$，什么时候取 $\operatorname{xor}$。

对于像本题这样不好找贪心策略的博弈论题来说，$\operatorname{SG}$ 函数绝对是最好的选择。显然，将一张纸剪开这个操作就是在这张纸表示的有向图游戏中移动了一步，不同剪的位置所形成的情况之间应该使用 $\operatorname{mex}$ 运算；而剪开一张纸之后选择哪张纸进行下一轮游戏显然是在选择不同的有向图游戏，此时应该用 $\operatorname{xor}$ 运算。

转移已经清楚那么还需要考虑边界情况，一个显然的想法是令 $\operatorname{SG}_{1,1}=0$ 作为边界进行转移（因为面对 $1\times 1$ 的纸说明是上一步对手剪出了 $1\times 1$ 的纸张，那么其实在上一轮对手已经赢了，本轮当然先手必输），然而这样子写会连样例都过不掉。

```cpp
int SG(int x,int y)//错误的写法
{
	if(sg[x][y]!=-1) return sg[x][y];
	if(x==1&&y==1) return 0;
	bool vis[N]={};
	for(int i=1;i<x;i++) vis[SG(i,y)^SG(x-i,y)]=1;
	for(int i=1;i<y;i++) vis[SG(x,i)^SG(x,y-i)]=1;
	for(int i=0;i<N;i++) if(!vis[i]) {sg[x][y]=i;break;}
	return sg[x][y];
}
```

这样的做法为什么不对呢，蓝书上给出的解释是：

>在剪纸游戏中，不能行动的局面，即 $1\times 1$ 的纸张，是一个必胜局面。而有向图要求在不能行动时判负。因此，我们需要做出一些变化。

蓝书上的解释明显有些牵强，因为 $1\times 1$ 的纸张理应是必败局面，或者我们也无法定义这样的一个局面是必败还是必胜，因为这个局面在上一轮就结束了（也就是说根本不会出现这样一个局面，这个局面不在定义域范围内），下文我们默认 $1\times 1$ 的局面是**未定义局面**。

我们现在不妨从原理上来解释一下为什么之前的做法是不对的，我们考虑 $2\times 2$ 的纸张答案为什么会算错，容易发现其只能变成两张 $1\times 2$ 的纸张（这里认为长宽互换是等价的纸张），那么两者的 $\operatorname{xor}$ 值必定是 $0$，所以 $\operatorname{SG}_{2,2}=1$，变成了必胜的，而我们知道答案显然是必败的，所以出现了矛盾。进一步分析矛盾点可以发现，$\operatorname{SG}_{2,2}$ 函数与 $\operatorname{SG}_{1,2}$ 根本无关，因为无论它取什么值，那么 $\operatorname{SG}_{1,2} \operatorname{xor} \operatorname{SG}_{1,2}=0$ 都成立，也就是说出问题的点不在于边界问题而是在于这一步根本**不满足有向图游戏和 $\operatorname{SG}$ 函数**。

回顾有向图游戏为什么可以通过 $\operatorname{mex}$ 和 $\operatorname{xor}$ 运算得出一个局面的 $\operatorname{SG}$ 函数，对于一个局面来说，这个局面的 $\operatorname{SG}$ 函数表示操作一步不能达到的局面的 $\operatorname{SG}$ 函数最小值（$\operatorname{mex}$ 的含义），这意味着操作一步能到达的局面的 $\operatorname{SG}$ 函数一定能取得到**所有**小于当前 $\operatorname{SG}$ 函数的值（这很重要），这样在求解有向图游戏的和的时候才能保证使用 $\operatorname{xor}$ 函数是正确的（因为已经将有向图游戏完全转化为 Nim 博弈）。在本题中 $1\times 1$ 是不能移动的局面，但此时 $\operatorname{SG}$ 函数未定义，所以需要依靠 $\operatorname{SG}_{1,1}$ 求解的 $\operatorname{SG}_{1,2}$ 也就未定义（无法取 $\operatorname{mex}$ 也就**无法知道下一步可以取哪一段合法前缀**），而 $\operatorname{SG}_{1,x}$ 局面是必胜局面无法下定义（只有必败局面才能定义 $\operatorname{SG}$ 函数为 $0$），那么我们就必须再向前推出必败局面作为边界，我们把 $x\le 3\wedge y\le 3$ 的 $x\times y$ 的纸张作为必败局面（这里与蓝书上有一定出入，多了 $3\times 3$ 的纸张，至于为什么是它们下文会解释）。

进一步地，因为作为操作者一定不会主动操作出 $1\times x$ 这样的局面（否则对手直接赢），所以我们每次枚举剪开的位置就不必枚举 $1\times x$ 这样的纸张（如果枚举了则进入了未定义的 $\operatorname{SG}_{1,x}$，这是我们不希望出现的，也是之前犯错的原因）。最后证明一下为什么边界是形如 $x\le 3\wedge y\le 3$ 的 $x\times y$ 的纸张，虽然 $1\times x$ 向前一步会出现所有形如 $y\times x$ 的纸张，也就是所有可能情况。但是我们之前已经说过：作为操作者一定不会主动操作出 $1\times x$ 这样的局面。而若 $x\le 3\wedge y\le 3$ 则无论怎么裁剪必会出现 $1\times x$ 这样的局面，此时这样的局面必败，反之，则一定存在一种操作可以剪出两张纸都不形如 $1\times x$，那么之后就可以利用 $\operatorname{SG}$ 函数递归了，正确性得到了保证。

# 代码实现
其实真正实现代码的时候可以不用特判递归终止条件，因为当 $x\le 3\wedge y\le 3$ 的时候两个 `for` 循环都不会进行（看代码），不会发生递归，且此时一定返回 $\operatorname{SG}_{x,y}=0$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=201;
int n,m,sg[N][N];

int SG(int x,int y)
{
	if(sg[x][y]!=-1) return sg[x][y];
	bool vis[N]={};
	for(int i=2;i<x-1;i++) vis[SG(i,y)^SG(x-i,y)]=1;
	for(int i=2;i<y-1;i++) vis[SG(x,i)^SG(x,y-i)]=1;//x<=3且y<=3的时候不会发生递归
	for(int i=0;i<N;i++) if(!vis[i]) {sg[x][y]=i;break;}
	return sg[x][y];
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(sg,-1,sizeof(sg));
		if(SG(n,m)) printf("WIN\n");
		else printf("LOSE\n");
	}
	return 0;
}
```

---

## 作者：穼柗° (赞：3)

直接 SG 函数，不会的可以看 [OI Wiki](https://oi-wiki.org/math/game-theory/impartial-game/#%E6%9C%89%E5%90%91%E5%9B%BE%E6%B8%B8%E6%88%8F%E4%B8%8E-sg-%E5%87%BD%E6%95%B0)。

设 $SG_{w,h}$ 表示在 $w\times h$ 的矩形纸张中先手的 SG 值，很显然 $SG_{1,1}=0$（因为对方搞出了 $1\times 1$ 纸张）。如果 $w$ 和 $h$ 中只有一个 $1$，那搞成 $1\times 1$ 就赢了。因此当 $w,h>1$ 时绝对不能把纸张搞成 $1\times h$ 或 $w\times 1$。

于是有
$$$
SG_{w,h}=\begin{cases}
0 & w=1,h=1 \\
\operatorname{mex}(\{x|x=SG_{i,h}\oplus SG_{w-i,h}\bigvee x=SG_{w,j}\oplus SG_{w,h-j}\}) & w>1\vee h>1
\end{cases}
$$$
其中 $i\in(1,w-1),j\in(1,h-1)$。

代码 ↓
```cpp
#include <iostream>
#include <tuple>
#include <map>
using namespace std;
int dp[201][201];
int sg(const int w,const int h) {
	if(dp[w][h]>=0) return dp[w][h];
	if(w==1&&h==1) return dp[w][h]=0;
	map<int,bool> mp;
	for(int i=2;i<w-1;i++)
		mp[sg(i,h)^sg(w-i,h)]=1;
	for(int i=2;i<h-1;i++)
		mp[sg(w,i)^sg(w,h-i)]=1;
	for(dp[w][h]=0;;dp[w][h]++)
		if(!mp[dp[w][h]]) return dp[w][h];
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	for(auto &i: dp)
		for(auto &j: i)
			j=-1;
	for(int w,h;cin>>w;) {
		cin>>h;
		cout<<(sg(w,h)?"WIN\n":"LOSE\n");
	}
	return 0;
}
```
禁止抄代码！！！

---

## 作者：rhq2022 (赞：3)

## [题面传送门](https://www.luogu.com.cn/problem/P10501)
## **题目大意**：
给你一张 $n \times m$ 的纸，~Alice 和 Bob~ 两方轮流，每次在纸上剪一刀，使其分为两张纸，已知初始纸张大小，问先手是否必胜。
## **思路**：
#### 一道 [SG函数](https://oi-wiki.org/math/game-theory/impartial-game/#%E6%9C%89%E5%90%91%E5%9B%BE%E6%B8%B8%E6%88%8F%E4%B8%8E-sg-%E5%87%BD%E6%95%B0) 板子题。

首先，在两人 **足够聪明** 的这一前提下，他们一定不会选择将一张纸裁剪成 $1 \times i$ 或 $i \times 1$ 这种长 **或** 宽为一纸张，因为这样的话在下一轮对手就可以直接裁剪出 $1 \times 1$ 的纸张。

\
之后我们继续思考，除了上述情况外，要想得到 $1 \times 1$ 的纸张，必须要通过 $2 \times 2 、 2 \times 3 、3 \times 2$ 大小的纸张裁剪得来。所以双方也当尽可能避免这种情况。略微思考可发现这是符合 [有向图游戏](https://oi-wiki.org/math/game-theory/impartial-game/#%E6%9C%89%E5%90%91%E5%9B%BE%E6%B8%B8%E6%88%8F%E4%B8%8E-sg-%E5%87%BD%E6%95%B0) 的特点的。

\
所以我们只需要求出 $\operatorname{SG}$ 函数值就可以了，将上述三种必败情况判为负，也就是 $\operatorname{SG}(2,2)=\operatorname{SG}(2,3)=\operatorname{SG}(3,2)=0$，其他的地方也就很好转移了，直接求出可以被当前纸张裁剪出的其他大小纸张 $\operatorname{SG}$ 值的 $\operatorname{mex}$，就可以了。

\
$\operatorname{SG}$ **函数**：

$$
\operatorname{SG}(N, M)=\operatorname{mex}(\left \{\operatorname{SG}(i,y) \ xor \ \operatorname{SG}(x-i,y)\right \} \cup  \left \{ \operatorname{SG}(x,i) \ xor \ \operatorname{SG}(x,y-i)\right \})
$$ 

## **Code**:
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=205;
int n,m,sg[N][N];
int SG(int x,int y){
	if (sg[x][y]>=0)	return sg[x][y];
	int mp[N];memset(mp,0,sizeof(mp));
	for (int i=2;i+1<x;i++)	mp[SG(i,y)^SG(x-i,y)]=1;
	for (int i=2;i+1<y;i++)	mp[SG(x,i)^SG(x,y-i)]=1;
	for (int i=0;i<=N-5;i++){
		if (!mp[i]){
			sg[x][y]=i;return i;
		}
	}
}
signed main(){
	memset(sg,-0x3f,sizeof(sg));
	sg[2][2]=0;sg[2][3]=0;sg[3][2]=0;sg[3][3]=0;
	while(cin>>n>>m){
		if (n==1||m==1||SG(n,m))	puts("WIN");
		else	puts("LOSE");
	}
	return 0;
}
~~~
完结撒花

---

## 作者：MoonCake2011 (赞：3)

就是枚举每个状态去推 SG 函数。

其中 $2\times 3$ 的格纸 $2\times2$ 的格纸先手必输。

那定义 $\operatorname{SG}(i,j)$ 为 $i\times j$ 的格纸的策略。

根据算法竞赛进阶指南。

两个子 SG 函数（同时进行）异或起来就是那个状态的 SG 值。

一些在当前状态能取到下一步的情况的 SG 值，当前状态的 SG 值为它们的 $\operatorname{mex}$。（注意这与上一个不同）

$\operatorname{mex}$ 为一个集合中，没有出现的最小的非负整数。

最后 $\operatorname{SG}(W,H)$ 为最终状态，为 $0$ 则先手败。

首先只是一个有向无环的游戏。

那就可以用 dp 的方式计算 SG 的值。

注意横切竖切。

并且每个情况切完都会有两个子问题。

于是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int SG[210][210];
bool f[1010];
void solve(int n,int m){
	memset(SG,0,sizeof SG);
	SG[2][3]=SG[3][2]=SG[2][2]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(i==2 && j==3) continue;
			if(i==3 && j==2) continue;
			if(i==2 && j==2) continue;
			memset(f,0,sizeof f);
			for(int k=2;k+2<=i;k++) f[SG[k][j]^SG[i-k][j]]=1;
			for(int k=2;k+2<=j;k++) f[SG[i][k]^SG[i][j-k]]=1;
			int t=0;
			while(f[t]) t++;
			SG[i][j]=t;
		}
	if(SG[n][m]) cout<<"WIN\n";
	else cout<<"LOSE\n";
}
int main() {
	while(cin>>n>>m) solve(n,m);
	return 0;
}
```

---

## 作者：w9095 (赞：2)

[P10501 Cutting Game](https://www.luogu.com.cn/problem/P10501)

博弈论经典题目，考虑使用 SG 函数解决。

但是这一题和有向图游戏的定义不同，在有向图游戏不能操作者判负，而这一题中操作出某个状态者判胜。因此，我们需要进行转化。经典做法是往前推直到推出必败态作为有向图游戏的终点。

我们考虑什么样的情况可以剪出 $1\times 1$ 的纸条，显然，当且仅当在 $1\times n$ 或 $n\times 1$ 的纸条上可以剪出 $1\times 1$ 的纸条。因此，这种情况下是先手必胜态。

往前推出必败态，就是要找到一个只能剪出 $1\times n$ 或 $n\times 1$ 的纸条的状态。不难发现在 $2\times2,2\times3,3\times2$ 的纸条中都只能剪出 $1\times n$ 或 $n\times 1$ 的纸条，因此它们是必败态。以它们作为有向图游戏的终点，即可按照有向图游戏的方式处理。

我们考虑枚举每个状态在哪一行或者哪一列剪开，之后就是两个剪纸子问题，求出它们的 SG 函数的值后用有向图游戏和异或起来就是当前状态的一个后继状态的 SG 函数值，求 mex 就行了。

注意每一步不会直接剪出 $1\times n$ 或 $n\times 1$ 的纸条，因为会使对手直接获胜，所以代码实现时需要注意边界条件。下面给出转移式。

$$sg(n,m)=\operatorname{mex}\{\{sg(i,m)\oplus sg(n-i,m)\mid 2\le i\lt n-1\}\cup\{sg(n,i)\oplus sg(n,m-i)\mid 2\le i\lt m-1\}\}$$

使用记忆化搜索预处理实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,x[300000],sg[300][300];
bool vis[300][300];
long long dfs(long long n,long long m)
{
	if(n==2&&m==2)return 0;
	if(n==2&&m==3)return 0;
	if(n==3&&m==2)return 0;
	if(vis[n][m])return sg[n][m];
	vis[n][m]=1;
	for(int i=2;i<n-1;i++)x[dfs(i,m)^dfs(n-i,m)]=1;
	for(int i=2;i<m-1;i++)x[dfs(n,i)^dfs(n,m-i)]=1;
	long long mex=0;
	while(x[mex])mex++;
	for(int i=2;i<n-1;i++)x[dfs(i,m)^dfs(n-i,m)]=0;
	for(int i=2;i<m-1;i++)x[dfs(n,i)^dfs(n,m-i)]=0;
	return sg[n][m]=mex;
}
 
int main()
{
	for(int i=2;i<=200;i++)
	    for(int j=2;j<=200;j++)dfs(i,j);
	while(scanf("%lld%lld",&n,&m)!=-1)
	   {
	   	if(sg[n][m])printf("WIN\n");
	   	else printf("LOSE\n");
	   }
	return 0;
} 
```

---

## 作者：粥2414 (赞：1)

# 思路
由于每次剪开纸后都会多一个子游戏，直接把其作为组合型组合游戏不太好分析。于是想到可以枚举其每一种可能的剪法，求出每一个后继局面的 SG 值，然后发现这样就变成了有向图游戏。求一个 $\operatorname{mex}$ 即可。

但是本题不一样的地方在于，将纸剪为 $1\times 1$，也就是到达终止状态的人为胜者，同时只要一个子游戏结束，整个游戏也会结束，这与经典的组合型组合游戏有很大不同，继续考虑转换。

一个显然的结论是两个人都会尽力避免剪出 $1\times x$ 或者 $x \times 1$ 这两种情况，原因下一步对手就可胜利。一旦剪出这两个情况，那么就把必胜态拱手让人了。

观察到只要达到 $2\times 2$、$2\times 3$、$3\times 2$、$3\times 3$ 这四种状态，那么下一步就一定会剪出必胜态。所以这四种状态为必败态。两个人一旦遇到这四种情况，那么就都不会去剪它，也就是无法行动。所以这四种状态可以视为子游戏的终止态。

那么到这里，就可以用常规有向图游戏的 SG 函数求解了。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=209;
ll sg[N][N];
ll w,h;
ll SG(ll n,ll m){
	if(sg[n][m]!=-1)return sg[n][m];
	bool f[N*2]={};
	for(int i=2;i<=n-2;i++)f[SG(i,m)^SG(n-i,m)]=1;
	for(int i=2;i<=m-2;i++)f[SG(n,i)^SG(n,m-i)]=1;
	for(int i=0;i<=400;i++){
		if(!f[i])return sg[n][m]=i;
	}
}
int main(){
	memset(sg,-1,sizeof(sg));
	while(cin>>w>>h){
		puts(SG(w,h)==0?"LOSE":"WIN");
	}
	return 0;
}
```

---

## 作者：Kingna (赞：1)

### [P10501 Cutting Game](https://www.luogu.com.cn/problem/P10501)

#### 题目大意

给定一张 $n\times m$ 的矩形网格纸，双方轮流操作，谁先剪出 $1\times 1$ 的方格获胜。问先手是否有必胜策略。

#### 思路

因为 $\texttt{SG}$ 函数解决的是 **不能走就输** 的问题，所以对于 **走到某个位置赢** 的问题是不能直接解决的。因此，我们需要进行转化。经典做法是往前推直到推出必败态作为有向图游戏的终点。

这道题的必败态就是 $(2,2),(2,3),(3,2)$，因为当先手面对这三个局面时，就是必败状态。

但是必败态有时候并不好找，还有一种处理方法是，如果下一步的状态是必胜态，则下一步不能走。对于这道题，必胜态就是 $(1,n)$ 或 $(n,1)$，即不能给对手剪出 $(1,n)$ 或 $(n,1)$ 的方格。

```cpp
int dfs(int n, int m) {
	if (f[n][m] != -1) return f[n][m];
	vector<int> vec;
	_for(i, 2, n - 2) vec.push_back(dfs(i, m) ^ dfs(n - i, m));
	_for(i, 2, m - 2) vec.push_back(dfs(n, i) ^ dfs(n, m - i));
	return f[n][m] = mex(vec);
}
```

---

## 作者：Chenyichen0420 (赞：1)

同[这题](https://www.acwing.com/problem/content/221/)。

sg 函数模板题。对每一种大小的纸片求出 sg 函数值即可。需要分成横竖两个方向进行分别求值，最后综合起来求 mex。

不知道 sg 函数的人[戳这里](https://answer.baidu.com/answer/land?params=7EdHb4hx0nUr9p2jBoPtT2JwcuI9Ge%2FEK%2Fa7q7e%2FgkfirGJJ%2BbkTdv8aGPJmm83t7IrRVWVIKcxTSWonUkDTUnNYoy3pFRqXVyZ7qtNl6F%2BSpZcsjqso6Y%2FaUPzPa38tQfQWiWH%2BH96b6YAvmiNxOGpItt1sI3hjh9yLtMEpj974lWAGRkdfo0xkytNf1Gji&from=dqa&lid=f9a737b40001bff5&word=sg%E5%87%BD%E6%95%B0)。

代码如下：

```cpp
#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
int n, m, gf[205][205];
inline int sg(int a, int b) {
	if (gf[a][b] != -1) return gf[a][b];
	unordered_set<int>us;
	for (int i = 2; i < a - 1; ++i)
		us.insert(sg(i, b) ^ sg(a - i, b));
	for (int i = 2; i < b - 1; ++i)
		us.insert(sg(a, i) ^ sg(a, b - i));
	for (int i = 0;; ++i) if (!us.count(i)) return gf[a][b] = i;
}
int main(){
	ios::sync_with_stdio(0);
	memset(gf, -1, sizeof gf);
	while (cin >> n >> m) puts(sg(n, m) ? "WIN" : "LOSE");
	return 0;
}
```

---

## 作者：Wilderness_ (赞：1)

## 思路
首先考虑将问题转化成如下问题：
>对于每一名玩家，都不能把网格纸剪到有一维为 $1$（不然对手剪一刀就 `WIN` 了），不能如此做的人必败。

然后我们可以用 [SG 函数](https://oi-wiki.org/math/game-theory/impartial-game/)求解这一类博弈论问题。

为了~~不写 SG 函数的递归形式~~使代码简洁一些，这里先预处理每个状态的 SG 函数值，枚举每一次操作在何处下手，就可以把原问题分成两个独立的子问题，而这个操作进行后所对应状态的 SG 函数值就是分出来的两个子问题的 Nim 和。

然后对于每个输入进来的 $H,W$，判断 SG 函数值是否为 $1$ 即可。

预处理的时间复杂度是 $O(N^3)$ 的，对于每次询问是 $O(1)$，反正 $O(N^3)$ 肯定能过 $H,W\le200$ 的数据的（毕竟预处理完后询问的时间复杂度对于预处理而言肯定是小得多了）。
## Code：
```cpp
#include<bits/stdc++.h>
#define M 214
using namespace std;
int SG[M][M],v[M];
int main()
{
    int n,m;
    memset(SG,-1,sizeof SG);
    for(int i=2;i<M;++i)
		for(int j=2;j<M;++j)
		{
			memset(v,0,sizeof(v));
			for(int k=2;i-k>=2;++k)v[SG[k][j]^SG[i-k][j]]=1;
			for(int k=2;j-k>=2;++k)v[SG[i][k]^SG[i][j-k]]=1;
			for(int k=0;k<M;++k)if(!v[k]){SG[i][j]=k;break;}
		}
    while(~scanf("%d%d",&n,&m))puts(SG[n][m]?"WIN":"LOSE");
    return 0;
}
```

---

## 作者：Iris_Aurora (赞：0)

**SG 函数**模板题。

显然 $1\times 1$ 的纸条是先手必败态，$1\times x,x\times 1$ 是先手必胜态。

可以列出 $sg$ 函数的定义：
$$
\begin{cases}
sg(1,1)=0\\
sg(n,m)=\mathrm{mex}(\{sg(i,m) \oplus sg(n-i,m)|2\le i\le n-2\}\\
\texttt{       }\cup\{sg(n,j) \oplus sg(n,m-j)|2\le j\le m-2\})
\end{cases}
$$
为什么 $i,j$ 的边界一定要保证两边都 $>1$ 呢，不难发现每一步都会尽量避免直接剪出 $1\times x$ 或 $x\times 1$ 的纸条，因为这样会使对手直接获胜。

记忆化搜索即可。

```c++
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 2e2 + 10;
int W,H;
int sg[MAXN][MAXN];
int SG(int n,int m){
	if(sg[n][m]!=-1) return sg[n][m];
	unordered_map<int,bool>vis;
	vis.clear(); 
	FL(i,2,n-2) vis[SG(i,m)^SG(n-i,m)]=1; 
	FL(i,2,m-2) vis[SG(n,i)^SG(n,m-i)]=1;
	FL(i,0,400) if(!vis[i]) return sg[n][m]=i;
}
int main(){
	memset(sg,-1,sizeof(sg));
	while(~scanf("%d%d",&W,&H))
		puts(SG(W,H)?"WIN":"LOSE");
}
```

---

## 作者：Vct14 (赞：0)

[SG 函数](https://oi-wiki.org/math/game-theory/impartial-game/#%E6%9C%89%E5%90%91%E5%9B%BE%E6%B8%B8%E6%88%8F%E4%B8%8E-sg-%E5%87%BD%E6%95%B0)练习题。

对于一张 $w\times h$ 的纸，我们枚举怎样行动，把这张纸剪成两部分，然后递归得出两部分的 SG 函数值并异或起来得到行动后局面的 SG 函数值。取所有合法行动产生的子局面的 SG 函数值的 $\operatorname{mex}$ 即可得到该局面的 SG 函数值。

由于每次都递归可能会超时，而且 SG 函数值是确定的，我们用一个数组来存储下已知的 SG 函数值，这样可以防止重复递归。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=202;
int s[N][N];

int sg(int n,int m){
    if(s[n][m]>=0) return s[n][m];
	int f[N]={0};
	for(int i=2; i<=n-2; i++) f[(s[i][m]==-1?sg(i,m):s[i][m]) xor (s[n-i][m]==-1?sg(n-i,m):s[n-i][m])]=1;
	for(int i=2; i<=m-2; i++) f[(s[n][i]==-1?sg(n,i):s[n][i]) xor (s[n][m-i]==-1?sg(n,m-i):s[n][m-i])]=1;
	for(int i=0; i<=200; i++) if(!f[i]) return s[n][m]=i;
}//sg(1,1)=0

int main(){
	int w,h;memset(s,-1,sizeof s);
	while(cin>>w>>h){
		if(sg(w,h)) cout<<"WIN\n";
		else cout<<"LOSE\n";
	}	
	return 0;
}
```

---

## 作者：lzt415 (赞：0)

## 前置芝士
一道连我这样的蒟蒻都能一眼秒的题，如果来看题解的不是想喝题解不劳而获的话，那么还是先建议看看这个：[SG函数](https://oi-wiki.org/math/game-theory/impartial-game/#%E6%9C%89%E5%90%91%E5%9B%BE%E6%B8%B8%E6%88%8F%E4%B8%8E-sg-%E5%87%BD%E6%95%B0)。
## 思路
知道了上面的前置芝士，这道题就不难想了，直接硬求即可。  
每次分两种情况，一种是竖着剪，一种是横着剪。

```cpp
for(int i=2;i<=n-2;i++)flag[SG(i,m)^SG(n-i,m)]=1;
for(int i=2;i<=m-2;i++)flag[SG(n,i)^SG(n,m-i)]=1;
```
注意：从 $2$ 开始，否则对手直接就赢了。

代码很短，只有十几行。
## code

```cpp
#include<bits/stdc++.h>//只有16行，短小精悍
using namespace std;
#define int long long
int sg[205][205],n,m;
inline int SG(int n,int m){
	if(sg[n][m]!=-1) return sg[n][m];
	int flag[205]={};//千万不要只写个"int f[205];"就完事了，否则只能得 80 points
	for(int i=2;i<=n-2;i++)flag[SG(i,m)^SG(n-i,m)]=1;//从2开始，否则对手直接赢
	for(int i=2;i<=m-2;i++)flag[SG(n,i)^SG(n,m-i)]=1;
	for(int i=0;i<=200;i++) if(!flag[i]) return sg[n][m]=i;
}
signed main(){
	memset(sg,-1,sizeof(sg));
	while(cin>>n>>m) cout<<(SG(n,m)?"WIN":"LOSE")<<endl;
	return 0;
} 
```

---

## 作者：Expert_Dreamer (赞：0)

一眼博弈论。

注意到如果 $n=1$ 或 $m=1$，此时先手必胜。

则如果 $n=2,m\le3$ 或 $m=2,n\le3$，先手只能剪成第一种情况，后手胜。

即上述情况为有向图游戏的终点，按照有向图游戏的方式运算。

设 $\textrm{\textup{SG}}(n,m)$ 为游戏先手的必胜情况，则根据有向图游戏，得：

$$\textrm{\textup{SG}}(n,m)=\operatorname{mex}\{\textrm{\textup{SG}}(i,m)\operatorname{xor}\textrm{\textup{SG}}(n-i,m)(1<i<n),\textrm{\textup{SG}}(n,i)\operatorname{xor}\textrm{\textup{SG}}(n,m-i)(1<i<m)\}$$

前一半式子表示从第 $i$ 列剪开的 $\textrm{\textup{SG}}$ 异或值，后一半为第 $i$ 行的异或值，最后执行 $\operatorname{mex}$ 运算得到答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define N 200
int sg[N+1][N+1];
int soga(int n,int m){
    if(sg[n][m]!=-1) return sg[n][m];
    int f[N+1]={};
    for(int i=2;i<=n-2;i++)f[soga(i,m)^soga(n-i,m)]=1;
    for(int i=2;i<=m-2;i++)f[soga(n,i)^soga(n,m-i)]=1;
    for(int i=0;i<=N;i++) if(!f[i]) return sg[n][m]=i;
}
signed main(){
    memset(sg,-1,sizeof sg);
    int n,m;
    while(cin>>n>>m) puts(soga(n,m)?"WIN":"LOSE");
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：
显然考虑博弈论。

鉴于每次划分都相当于把原本一个较大的剪纸游戏转变为两个较小的剪纸游戏，我们考虑枚举每一个竖划分线和横划分线，对于每次划分将划分后两部分 SG 函数的异或和标记一下，然后全部处理完之后求 $\rm mex$ 即可。

边界条件为当 $n,m$ 均小于等于 $3$ 时先手必败，大家可以手推一下。

基本原理仅在于本题可以看为有向图游戏，具体原理建议大家自行学习博弈论相关内容。

### 代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sg[255][255];
int n,m;

inline int SG(int n,int m){
	if(sg[n][m]!=-1){
		return sg[n][m];
	}
	int vis[255];
	memset(vis,0,sizeof(vis));
	for(int i=2;i<=n-2;i++){
		vis[SG(i,m)^SG(n-i,m)]=1;
	}
	for(int i=2;i<=m-2;i++){
		vis[SG(n,i)^SG(n,m-i)]=1;
	}
	for(int i=0;i<=200;i++){
		if(!vis[i]){
			sg[n][m]=i;
			return i;
		}
	}
}

signed main(){
	memset(sg,-1,sizeof(sg));
	SG(200,200);
	while(cin>>n>>m){
		if (sg[n][m]){
			cout<<"WIN\n";
		}
		else{
			cout<<"LOSE\n";
		}
	}
	return 0;
}
```

---

## 作者：ZinfI_Sh (赞：0)

# update

$2024/8/21$ 教同学做时发现了代码的一个漏洞，但不改也能过。

$2024/10/27$ 重新理解了一遍，那个“漏洞” 确实不用改，改了还会慢一点。

# 题目

[P10501 Cutting Game](https://www.luogu.com.cn/problem/P10501)

# 分析

首先，一眼博弈论，我们就要考虑一下几点：

## 1. 必败局面

注意到胜利条件为切成 $1\times 1$ 的局面，想要到达这个局面，必须先是一个**长或宽中有 $1$ 的局面**，那么能到达这种局面的局面只有 ——

$1\times \text{X},~\text{X}\times 1,~2\times 3,~3\times 2,~ 2\times 2$。

这 $5$ 种局面，其中：

- 当目前到达了 $1\times \text{X}$ 和 $\text{X}\times 1$ 时为**必胜**局面，因为一定能切成 $1\times 1$ 与 $1\times \text{X}-1$ 的局面（另一个同理）。
- 当局面到达了其余 $3$ 种时为**必败**局面，因为一定会切出一条长或宽为 $1$ 的局面，也就是**当我操作后为必胜局面，我必败。**

## 2. SG 函数

针对 $\operatorname{SG}$ 函数，应使用二维参数 $\operatorname{SG}(i,j)$，表示长宽分别为 $i$ 和 $j$ 时的状态。

根据必败局面分析，在 $\operatorname{SG}$ 函数中，**$3$ 种必败局面为 $0$**，也就是 $\operatorname{SG}(2,3)=\operatorname{SG}(3,2)=\operatorname{SG}(2,2)=0$。

## 3. 程序部分

根据有向图游戏的性质，容易发现当 $\operatorname{SG}(n,m)\not=0$ 时，先手**必胜**，否则**必败**，也就是：

```cpp
signed main()
{
    int n, m;
    memset(sg, -1, sizeof(sg));
    sg[2][3] = sg[3][2] = sg[2][2] = 0;
    while (cin >> n >> m) {
        int tmp = query(n, m);
        if (tmp) {
            cout << "WIN\n";
        } else {
            cout << "LOSE\n";
        }
    }
    return 0;
}
```

接下来 $\operatorname{SG}$ 函数，使用记忆化搜索，数组 $sg_{i,j}$ 表示 $\operatorname{SG}(i,j)$ 的值，非必败局面的值初始化为 $-1$ 做为标记，当函数求到一个被求过的 $\operatorname{SG}$ 时，直接返回，否则：

我们分别枚举竖着切和横着切，每次枚举一个断点来标记 $\operatorname{mex}$ 函数，然后按照有向图游戏的模板写一下好了。

# AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
// 以下为防伪部分（划掉）
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define lowbit(x) (x & -x)
using namespace std;
const int DM[8][2] = { 0, 1, 0, -1, 1, 0, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1 };
const int HASHMOD = 212370440130137957;
const int HASHBASE = 131;
const int MOD = 10007;
inline void read(int& res)
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    res = x * f;
}
// 以上为防伪部分（划掉）
int sg[1011][1011];
int query(int n, int m)
{
    if (sg[n][m] != -1) {
        return sg[n][m];
    }
    bool tag[2010]; // 标记，辅助求 mex 函数
    // 由于是记忆化，所以要定义在函数里面互不冲突（当然空间够的话在函数外定义 2 维也行）
    memset(tag, 0, sizeof(tag)); // 定义在函数里面一定要初始化！！！
    for (int i = 2; i <= n / 2; i++) // 枚举竖着切
    // 我们之枚举2~n/2，可以快一点点，因为枚举n/2之后的是重复的
    {
        tag[query(i, m) ^ query(n - i, m)] = 1; // 枚举断点后套板子
    }
    for (int i = 2; i <= m / 2; i++) // 同理
    {
        tag[query(n, i) ^ query(n, m - i)] = 1; // 同理
    }
    int ans = 0;
    while (tag[ans]) // 求 mex
    {
        ans++;
    }
    return sg[n][m] = sg[m][n] = ans;
}
signed main()
{
    int n, m;
    memset(sg, -1, sizeof(sg)); // 放这里其实很好理解，sg[i][j] 是一个定值，不会随着 n 和 m 的改变而改变。
    sg[2][3] = sg[3][2] = sg[2][2] = 0;
    while (cin >> n >> m) {
        int tmp = query(n, m);
        if (tmp) {
            cout << "WIN\n";
        } else {
            cout << "LOSE\n";
        }
    }
    return 0;
}
```

---

## 作者：Charles_with_wkc (赞：0)

# 前置知识：
[SG函数](https://oi-wiki.org/math/game-theory/impartial-game/)/[Nim 游戏相关内容](https://www.cnblogs.com/BigSmall-En/p/nim.html)/[同题](https://www.acwing.com/problem/content/221/)
# 思路：
对于每一个人，都不能把网格纸剪到有一维为 $1$，**不能完成**这个的人**必败**，反之可以**完成这个**的人**不一定**必胜。我们可以想一下其他方法。仔细想想我们可以很容易想到这个其实就是 sg 函数模板，对于每一种纸片求出 sg 函数，最后取 $\max$ 即可。
# 核心代码：
```cpp
memset(f,0,sizeof f);
t=0;
for(int k=2;k+2<=i;k++){
    dp[sg[k][j]^sg[i-k][j]]=1;
}
for(int k=2;k+2<=j;k++){
    dp[sg[i][k]^sg[i][j-k]]=1;
}//循环枚举
while(dp[t]){
    t++;
}//不合法
sg[i][j]=t;//赋值
```

---

## 作者：z_yq (赞：0)

## 1. 前置芝士： [SG函数](https://oi-wiki.org/math/game-theory/impartial-game/)
## 2. 思路：

由于我们知道：两个人不可能切成 $1 \times x$ 或 $x \times 1$ 的情况，所以当我们的 SG 函数递归的时候，不能出现以上两种情况，接下来的就是 SG 的板子了。

## 3. 代码:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=209;
ll a,b,sg[N][N];
inline ll SG(ll x,ll y)
{
    if(sg[x][y]!=-1)
        return sg[x][y];
    ll f[N]={};
    for(int i=2;i<=x-2;i++)
        f[SG(i,y)^SG(x-i,y)]=1;
    for(int i=2;i<=y-2;i++)
        f[SG(x,i)^SG(x,y-i)]=1;
    for(int i=0;i<=200;i++)
        if(!f[i]) return sg[x][y]=i;
}
int main()
{
    memset(sg,-1,sizeof(sg));
    while(cin>>a>>b)
    {
        if(SG(a,b))
            cout<<"WIN\n";
        else cout<<"LOSE\n";
    }
    return 0;
}
```

---

## 作者：Z_AuTwT (赞：0)

其实就是博弈论。

把 $2\times2$、$2\times3$、$3\times3$、$3\times2$ 的状态设成必败状态，然后用 SG 函数来求每个位置是否是必胜状态。

如果一个位置的后继中有必败状态，那么这个位置一定是必胜状态。如果一个位置的后继都是必胜状态，那么这个位置一定是必败状态。

## CODE：

```c++
#include<bits/stdc++.h>
int SG[210][210],flag[210];
main(){
    int n,m;
    while(std::cin>>n>>m){
        memset(SG,0,sizeof(SG));//清空
        for(int i=1;i<=n;i++){//枚举位置
            for(int j=1;j<=m;j++){
                if(i==2&&j==2||i==2&&j==3||i==3&&j==2||i==3&&j==3) continue;
                for(int k=2;k<i-1;k++) flag[SG[k][j]^SG[i-k][j]]=1;//分割行
                for(int k=2;k<j-1;k++) flag[SG[i][k]^SG[i][j-k]]=1;//分割列
                int cnt=0;
                while(flag[cnt]){//求 mex
                    cnt++;
                }
                memset(flag,0,sizeof(flag));
                SG[i][j]=cnt;
            }
        }
        if(SG[n][m]>=1) puts("WIN");
        else puts("LOSE");
    }
}
```

---

