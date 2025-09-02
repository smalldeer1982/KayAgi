# [ABC380F] Exchange Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc380/tasks/abc380_f

高橋君と青木君が、数の書かれたカードを使ってゲームをします。

最初、高橋君は $ A_1,\ldots,A_N $ が書かれた $ N $ 枚のカードを、青木君は $ B_1,\ldots,B_M $ が書かれた $ M $ 枚のカードを手札として持っており、場には $ C_1,\ldots,C_L $ が書かれた $ L $ 枚のカードがあります。  
 高橋君と青木君はゲーム中常に、相手の手札も含め、全てのカードに書かれた数を知っている状態にあります。

高橋君と青木君は、高橋君から順に次の行動を交互に行います。

- 自分の手札から $ 1 $ 枚選び場に出す。その後、出したカードに書かれていた数未満の数が書かれたカードが場にあれば、そのうち $ 1 $ 枚を場から自分の手札に移して良い。
 
先に行動が行えなくなった方が負けであり、負けでない方が勝ちです。互いに最適に行動したとき、どちらが勝つか判定してください。

なおこのゲームは必ず有限回の行動で勝敗がつくことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M,L $
- $ N+M+L\ \leq\ 12 $
- $ 1\ \leq\ A_i,B_i,C_i\ \leq\ 10^9 $
- 入力は全て整数である
 
### Sample Explanation 1

ゲームは例えば次のように進行します。(最適な行動とは限りません) - 高橋君が手札から $ 2 $ を場に出し、$ 1 $ を場から自分の手札に移す。高橋君の手札は $ (1) $、青木君の手札は $ (4) $、場札は $ (2,3) $ となる。 - 青木君が手札から $ 4 $ を場に出し、$ 2 $ を場から自分の手札に移す。高橋君の手札は $ (1) $、青木君の手札は $ (2) $、場札は $ (3,4) $ となる。 - 高橋君が手札から $ 1 $ を場に出す。高橋君の手札は $ () $、青木君の手札は $ (2) $、場札は $ (1,3,4) $ となる。 - 青木君が手札から $ 2 $ を場に出す。高橋君の手札は $ () $、青木君の手札は $ () $、場札は $ (1,2,3,4) $ となる。 - 高橋君は行動できないため負けであり、青木君が勝ち。

## 样例 #1

### 输入

```
1 1 2
2
4
1 3```

### 输出

```
Aoki```

## 样例 #2

### 输入

```
4 4 4
98 98765 987654 987654321
987 9876 9876543 98765432
123 12345 1234567 123456789```

### 输出

```
Takahashi```

## 样例 #3

### 输入

```
1 1 8
10
10
1 2 3 4 5 6 7 8```

### 输出

```
Aoki```

# 题解

## 作者：__Allen_123__ (赞：251)

你是某国一名普通的想象学竞赛生。一场由某国想象学学会举办的全国想象学竞赛马上就要开始了。

> 某国的一个省份为了减少考试名额的浪费，决定对该省报名参加的初中生进行线上热身预赛。你是其中需要参加热身赛的一名选手。
>
> 既然是线上预赛，你就需要和想象学学会某省特派员进行心理博弈。具体地，现在有 $10^9$ 道题，每道题的编号（从 $1$ 到 $10^9$）可以代表其难度，编号越大，难度越大。可能有相同难度的题，但我们将其视为不同的题目。
>
> 你在先前打算为可能考察的 $n$ 道题做准备，其编号为 $a_i$。比赛原有 $m$ 道题目，其编号为 $b_i$。另外仍然有可能考察的 $l$ 道题目，其编号为 $c_i$。
>
> 你和特派员轮流换题。每一方在一轮中会进行如下操作：
>
> 1. 不再去准备某一道题，即把 $a_i$ 放入 $c$ 中。
> 2. 可以考虑是否选择另一道题并对其做准备。你和特派员都希望难度尽量简单，并且特派员会一直注意你，所以选择的这道题只能在 $c$ 中，且难度要比刚才放弃的那一道题低，也就是 $c_j<a_i$ 或 $c_j<b_i$。
>
> 无法换题的一方会在这场线上博弈中落败。求哪一方会胜利。

下文假设 $N=n+m+l$，$b$ 和 $c$ 顺次依序插入到 $a$ 后。

这场热身赛的题目是少的，所以你决定把所有可行的状态全部枚举，并进行状压。具体地，设 $S$ 为记录状态的三进制数，从低到高的第 $i$ 位为 $0$ 则在 $c$ 中，为 $1$ 则在 $a$ 中，为 $2$ 则在 $b$ 中。

为了提高效率，你考虑进行记忆化搜索，每次记录轮到哪一方 $id$（轮到你则 $id=1$，轮到特派员则 $id=2$）和当前的 $S$。如果当前这一方必胜，则 $\text{dfs}(id,S)=1$，否则该函数的返回值为 $0$。

显然，如果有一种可以达成的子状态使得 $\text{dfs}(3-id,S')=0$（其中 $S'$ 为你或特派员操作后的新状态），则你就有必胜策略，返回 $1$，如果没有，则返回 $0$。由此可以枚举放弃的题目和重新拿到的题目，并进行处理，就得到了最终的答案。

[你的代码](https://atcoder.jp/contests/abc380/submissions/59930693)。

回看这一过程，你发现了一个很可怕的事实。

你和特派员的全部博弈过程都是在线上举行的，公平性可想而知。在你看不见的地方，可能他们已经完全修改了难度。身为一名普通的选手，你只能按照规则行事，可他们却能打破选手的规则。你的代码看似求出了谁终获胜，可实际上，猎人和猎物的身份在你的背后已悄然转变。从某国的全国名义之上，高层的想象学竞赛虽然免费，可所谓之热身赛却已然又成某省收费之理由。

可面对这一切，你也无法说什么或者做什么。因为你也是想象学竞赛选手。

---

## 作者：coding_goat (赞：5)

$n+m+l\le 12$，一眼搜索剪枝。

如果有一种操作使得之后的情况都可以转换为我胜，那么这就是我的必胜点，反之就是我的必败点。

注意是**可以**从桌上拿起一张牌，不是必须。

然后就是要记忆化搜索，注意要记录此时是谁操作，因为有可能出现两个人手牌一样但是操作方不一样。

```cpp
#include<bits/stdc++.h>

#define mem(a,b) memset((a),(b),sizeof(a))
#define m0(a) memset((a),0,sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
#define For(a,b,c) for(int a=(b);a<=(c);a++)
#define Rep(a,b,c) for(int a=(b);a>=(c);a--)
#define in1(a) a=read()
#define in2(a,b) a=read(), b=read()
#define in3(a,b,c) a=read(), b=read(), c=read()
#define inn(i,n,a) For(i,1,n) a[i]=read();

#define ll long long
#define i128 __int128

using namespace std;
inline int read() {
	int xx= 0;int f= 1;
	char c = getchar();
	while(c<'0'||c>'9') { 
		if(c=='-') f= -1;
		c= getchar();
	}
	while(c>='0'&&c<='9') {
		xx= (xx<<1)+(xx<<3)+(c^48);
		c= getchar();
	}
	return xx*f;
}
#define maxn 15
short f[2][(1<<12)+114][(1<<12)+514];
int a[maxn];
int n,m,l;
int out[maxn],top;
void put(int x) {
	m0(out);
	top=0;
	while(x) out[++top]=x&1,x>>=1;
	For(i,1,13) cout<<out[i]; 
	puts("");
}	
bool dfs(int dep,int s1,int s2) {
//	cout<<dep<<'\n';put(s1); put(s2); puts("---");
	
	bool res=0;
	if(f[dep][s1][s2]!=-1) return f[dep][s1][s2];
	if(dep&1) {
		res=0;
		For(i,0,n+m+l-1) {
			if(!((s1>>i)&1)) continue;
			if((s2>>i)&1) continue;
			For(j,0,n+m+l-1) {
				if(((s1|s2)>>j)&1) continue;
				if(a[i+1]>a[j+1]) 
					if(!dfs((dep^1),(s1^(1<<i))|(1<<j),s2)) res=1;
			}
			if(!dfs((dep^1),(s1^(1<<i)),s2)) res=1;
		}		
	} else {
		res=0;
		For(i,0,n+m+l-1) {
			if(!((s2>>i)&1)) continue;
			if((s1>>i)&1) continue;
			For(j,0,n+m+l-1) {
				if(((s1|s2)>>j)&1) continue;
				if(a[i+1]>a[j+1])
					if(!dfs((dep^1),s1,(s2^(1<<i))|(1<<j))) res=1;
			}
			if(!dfs((dep^1),s1,(s2^(1<<i)))) res=1;
		}		
	}
	f[dep][s1][s2]=res;
	return res;
}
signed main() {
	mem(f,-1);
	in3(n,m,l);
	For(i,1,n+m+l) in1(a[i]);
	cout<<(dfs(1,(1<<(n))-1,(1<<(m+n))-(1<<n))?"Takahashi":"Aoki");
}

---

## 作者：Showball (赞：3)

我们发现 $N+M+L\leq 12$ 数据范围很小，考虑状态压缩。分别存储先手和后手以及桌上的牌型。

然后记忆化搜索即可。**如果一个状态的后继状态中存在一个必败态，那么这个状态一定是必胜态。（因为玩家很聪明，一定会走到这个状态），否则当前状态为必败态。**

具体实现参考代码及注释。

```cpp
#include<bits/stdc++.h>

using namespace std;

using i64=long long;

void Showball(){
    int n,m,l;
    cin>>n>>m>>l;
    int len=n+m+l;
    vector<int> a(len);
    for(int i=0;i<len;i++) cin>>a[i];
    vector<vector<int>> dp(4100,vector<int>(4100));
    
    function<int(int,int)> dfs=[&](int x,int y){
        if(dp[x][y]) return dp[x][y];
        int st=x+y;//当前玩家手上的牌型
        for(int i=0;i<len;i++){//枚举桌上牌型
            if(st>>i&1) continue;//说明这张牌不在桌上
            for(int j=0;j<len;j++){//枚举当前先手牌型
                if(!(x>>j&1)) continue;//说明这张牌不在先手玩家手中
                if(a[j]>a[i]){//可以摸桌上牌
                    int t=x-(1<<j)+(1<<i);
                    int tt=dfs(y,t);
                    //后续存在必败态，当前态必胜
                    if(tt==2) return dp[x][y]=1;
                }else{//不能摸桌上牌
                    int t=x-(1<<j);
                    int tt=dfs(y,t);
                    //后续存在必败态，当前态必胜
                    if(tt==2) return dp[x][y]=1;
                }
            }
        }
        //后续不存在必败态，当前态必败
        return dp[x][y]=2;
    };

    int x=0,y=0;
    for(int i=0;i<n;i++) x|=1<<i;
    for(int i=n;i<n+m;i++) y|=1<<i;

    int ans=dfs(x,y);
    cout<<(ans==1?"Takahashi\n":"Aoki\n");
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    //cin>>t;

    while(t--){
      Showball();
    }

    return 0;
}
```

---

## 作者：TonviaSzt (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc380_f)

**题目大意**

> Takahashi 和 Aoki 在玩一个卡牌游戏，每张卡牌上写有一个数字。
>
> 初始时 Takahashi 有 $N$ 张牌，Aoki 有 $M$ 张牌，桌上还有 $L$ 张牌。游戏规则如下：
>
> - 轮到某个玩家的回合时，该玩家从手中打出一张牌（记作 $k$）置于桌子上，并允许从桌子上拿取不超过一张数值小于 $k$ 的牌。
> - 当一个玩家不能进行上述操作时，对方获胜，游戏结束。
>
> 若 Takahashi 先手，双方都知道所有牌的布局，问最优策略下谁是必胜者。
>
> $N+M+L\le 12$

**思路分析**

令 $N+M+L=|S|$。

赛时一直在想状压，如设 $O(3^{|S|})$ 或者 $O(2^{2\cdot |S|})$ 的状态数，发现转移式并不是很直观。

不是，$|S|\le 12$ 想啥状压呢？记搜模拟一遍就做完了啊（

将牌的布局压缩成一个数，函数 $dfs(i)$ 表示牌的布局为 $i$ 时先手的胜败情况，$|S|^2$ 模拟每一次操作过程即可。

由于状态数有 $3^{|S|}$ 种，故总复杂度 $O(3^{|S|}\cdot |S|^2)$。

[Submission](https://atcoder.jp/contests/abc380/submissions/59929092)

---

## 作者：DengStar (赞：2)

为了方便，下面称 Takahashi（先手）为 A，Aoki（后手）为 B。

看到数据很小，可以接受指数级的时间复杂度，这启示我们往爆搜或状压的方向去想。

总结题意可以发现：一张牌只有三个去处：要么在 A 手上，要么在 B 手上，要么在桌上。因此我们用每张牌的状态来表示一个游戏局面 $S$，代码实现上可以用三进制状压。下面考虑 dp 的具体实现。

记 $f(S)$ 表示游戏局面为 $S$，且轮到 A 时，A 是否必胜。类似地，记 $g(S)$ 表示游戏局面为 $S$，且轮到 B 时，B 是否必胜。这里必须分别设轮到 A 和轮到 B 的状态，因为两人的手牌状态不同，能做的决策也不同。这样 dp 的总状态数为 $2 \times 3^{N + M + L}$，可以接受。

- 初始化：注意到一个玩家会输，当且仅当轮到他时他手上没有牌了，因此初始化“某人手上没有牌且轮到此人”的状态为必败状态。
- 转移：如果当前局面为 $S$，定义玩家操作后的后继局面为 $S'$。我们可以直接暴力枚举出哪张牌以及拿哪张牌，得到所有可能的 $S'$。在这些 $S'$ 中，如果有一个使得轮到对手时对手必输，那么他总可以选择达到这个后继状态，因此对于他来说 $S$ 是必胜状态。反之，$S$ 对他就是必败状态。
- 答案统计：记游戏的初始局面为 $S_0$，若 $f(S) = 1$，则 A 胜，否则 B 胜。

如果你现在就开始兴致冲冲地写代码，你很快会发现一个问题：虽然我们已经有转移方程了，但我们该以什么顺序转移呢？甚至，这样 dp 究竟能否被转移？它有没有可能是有后效性的？可能很多人直接写个记忆化搜索就跑路了，但我认为这个问题还是值得研究的。

（以下分隔线内的内容选读）

---

**一句话概括：每个人手牌上数字的和单调减小，所以每个状态最多被计算一次。**

不妨先想想有的状压 dp 为什么可以转移。[ABC354E](https://www.luogu.com.cn/problem/AT_abc354_e) 是一道和本题类似的打牌问题，但区别在于，玩家只能从桌上拿牌，而不能往桌面上放牌。如果记桌面上牌的集合为 $s$，拿走了牌之后的状态为 $s'$，把它们状压成整数，那么显然有 $s' < s$——因为拿走牌的操作就相当于把 $s$ 的两个二进制位从 $1$ 变成 $0$。这样，我们就可以简单地从小到大枚举状态来转移。

但这样解释没有触及到更本质的东西。如果我们把 dp 中的状态看作图中的节点，而状态之间的依赖关系看作有向边（即，如果状态 $i$ 要从状态 $j$ 转移过来，那么连一条 $j \to i$ 的边）。那么，dp 的无后效性体现在转移图$\ ^{*}$上就是没有环，即**转移图是 DAG**，而 dp 的转移过程就相当于在转移图上做拓扑排序。如果我们要证明 dp 具有无后效性，就相当于要证明转移图上没有环。而在 ABC354E 这道题中，$s'$ 和 $s$ 满足 $s' \sub s$，而真包含关系是不会形成环的，因此可以转移。

$(*)$：《算法导论》中“动态规划”一章也提到了这个概念，书中称为“子问题图”，并且边的方向和本文中的定义相反，但本质上没有区别。

我们有没有办法给本题中的状态找到某种关系呢？题目中提到了关键的一点性质：从桌上拿的牌的数字必须**小于**打出去的牌的数字。这意味着，每次操作后，玩家手上的数字之和**单调减小**。那么我们就可以从手牌数字和从小到大的顺序转移。实际上这还解释了为什么游戏一定会终止：每次操作都会导致手牌的数字和减小，那么一定会减到 $0$，此时游戏就结束了。

严谨地说，我们用三元组 $(S_A, S_B, S_C)$ 来表示一个局面，其中 $S_A$，$S_B$ 和 $S_C$ 分别表示 A 手牌的集合、B 手牌的集合和桌上的牌的集合。定义 $\operatorname{sum}(T)$ 表示牌的集合 $T$ 中，所有牌上面数字的和。定义局面之间的**关系** $<$，若 $S' < S$，则 $\operatorname{sum}(S'_A) < \operatorname{sum}(S_A)$ 且 $\operatorname{sum}(S'_B) = \operatorname{sum}(S_B)$，或 $\operatorname{sum}(S'_B) < \operatorname{sum}(S_B)$ 且 $\operatorname{sum}(S'_A) = \operatorname{sum}(S_A)$。这样我们就成功地找到了一个状态和它的后继状态之间的关系，并且能证明这种关系不会形成环。

（这里用离散数学中“关系”的知识来解释会更好，但本人相关知识的水平相当民科，所以还是算了。）

当然，从代码实现上，真的去找这种状态的关系是很繁琐的，这时可以简单地用**记忆化搜索**实现转移。实际上你会发现即使没有找到这种关系也可以写出代码，但这并不意味着它不重要。如果转移之间有环，用记搜也是会死循环的。换句话说，知道这种关系存在比它具体是什么更重要。

---

关键代码实现：

（和上文中的状态定义略有不同：`f[0/1][s]` 分别表示局面为 `s` 且轮到 A 或 B 时，其是否必胜。）

```cpp
int dfs(int o, int s)
{
    if(f[o][s] != -1) // 记忆化
        return f[o][s];
    if(count(s, o) == 0) // 初始化
        return f[o][s] = 0;
    f[o][s] = 0;
    for(int i = 0; i < N + M + L; i++) // 枚举出哪张牌
    {
        if(get(s, i) != o)
            continue;
        f[o][s] |= !dfs(o ^ 1, s - o * pw[i] + 2 * pw[i]); // 不拿任何牌
        for(int j = 0; j < N + M + L; j++) // 枚举拿哪张牌
        {
            if(get(s, j) != 2 || val[j] >= val[i])
                continue;
            int t = s - o * pw[i] + 2 * pw[i] - 2 * pw[j] + o * pw[j]; // 后继状态
            f[o][s] |= !dfs(o ^ 1, t);
        }
    }
    return f[o][s];
}
```

`get(s, i)` 表示三进制数 `s` 的从低位开始的第 `i` 位，`count(s, o)` 表示三进制数 `s` 中为 `o` 的位数。

局面 `s` 的第 `i` 位为 `0/1/2` 分别表示第 `i` 张牌在 A 手上/在 B 手上/在桌上。

答案为 `f[0][S0]`，其中 `S0` 为初始状态。

[完整代码](

---

## 作者：xixisuper (赞：1)

# AT_abc380_f [ABC380F] Exchange Game 题解

简单题。

## 思路

场上一看，诶！博弈论！不会！仔细一看，诶！$12$！状压，启动！

我们注意到一共不会超过 $12$ 个数，所以总局面数至多只有 $3^{12}$ 个，直接状压后暴力 dp 即可。

我们用一个三进制数来表示一个局面，如果第 $i$ 位为 $0$，表示第 $i$ 个数在先手手中；如果第 $i$ 位为 $1$，表示第 $i$ 个数在后手手中；如果第 $i$ 位为 $0$，表示第 $i$ 个数在桌子上。

我们定义 $f_{S,1/0}$ 表示当前局面是 $S$，$1$ 表示轮到先手行动，$0$ 表示后手行动。如果值为 $1$，表示先手必胜，值为 $-1$ 则表示后手必胜。转移十分显然，如果 $f_{S,1}$ 能够转移到 $f_{T,0}$，且$f_{T,0}=1$，则 $f_{S,0}=1$，否则 $f_{S,0}=-1$，对于后手行动的转移也差不多，就不再赘述。边界条件就是如果轮到某个人进行操作，但是他手里没牌了，那么就是对手必胜。

总时间复杂度约为 $O((n+m+l)^2\cdot 3^{n+m+l})$，可以通过此题。

## 代码

细节略多，不建议阅读。

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=5e5+10;
const ll M=2e6+10;
ll n,m,l,all;
ll a[20],b[20],c[20],pls[20],zhuang[20];
ll pd[M][2];
ll T3(ll *zh){
	ll ret=0,mi3=1;
	for(ll i=1;i<=all;i++){
		ret+=zh[i]*mi3;
		mi3*=3;
	}
	return ret;
}
void RE(ll now,ll *zh){
	ll mi3=1;
	for(ll i=1;i<=all;i++) mi3*=3;
	for(ll i=all;i>=1;i--){
		mi3/=3;
		zh[i]=now/mi3;
		now%=mi3;
	}
}
ll dfs(ll now,ll Tak){
	if(pd[now][Tak]!=0) return pd[now][Tak];
	ll thus[13];
	RE(now,thus);
	ll cnt1=0,cnt2=0,cnt3=0;
	for(ll i=1;i<=all;i++){
		if(thus[i]==0) cnt1++;
		if(thus[i]==1) cnt2++;
		if(thus[i]==2) cnt3++;
	}
	if(Tak&&!cnt1) return pd[now][Tak]=-1;
	if(!Tak&&!cnt2) return pd[now][Tak]=1;
	bool flag=0;
	if(Tak){
		for(ll i=1;i<=all;i++){
			if(thus[i]!=0) continue;
			thus[i]=2;
			if(dfs(T3(thus),Tak^1)==1) return pd[now][Tak]=1;
			thus[i]=0;
			for(ll j=1;j<=all;j++){
				if(thus[j]!=2) continue;
				if(pls[i]<=pls[j]) continue;
				swap(thus[i],thus[j]);
				if(dfs(T3(thus),Tak^1)==1) return pd[now][Tak]=1;
				swap(thus[i],thus[j]);
			}
		}
		return pd[now][Tak]=-1;
	}
	for(ll i=1;i<=all;i++){
		if(thus[i]!=1) continue;
		thus[i]=2;
		if(dfs(T3(thus),Tak^1)==-1)	return pd[now][Tak]=-1;
		thus[i]=1;
		for(ll j=1;j<=all;j++){
			if(thus[j]!=2) continue;
			if(pls[i]<=pls[j]) continue;
			swap(thus[i],thus[j]);
			if(dfs(T3(thus),Tak^1)==-1)	return pd[now][Tak]=-1;
			swap(thus[i],thus[j]);
		}
	}
	return pd[now][Tak]=1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>l;
	all=n+m+l;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		pls[i]=a[i];
		zhuang[i]=0;
	}
	for(ll i=1;i<=m;i++){
		cin>>b[i];
		pls[n+i]=b[i];
		zhuang[n+i]=1; 
	}
	for(ll i=1;i<=l;i++){
		cin>>c[i];
		pls[n+m+i]=c[i];
		zhuang[n+m+i]=2;
	}
	ll ch=dfs(T3(zhuang),1);
	if(ch==1) cout<<"Takahashi";
	else cout<<"Aoki";
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

简单状压题，可以选择 $3^n$ 状压，但是由于二进制更好写，考虑 $dp_{S_1, S_2}$ 表示若当且局面下先手拿的牌是 $S_1$ 集合，后手拿的牌是 $S_2$ 集合时先手能否必胜。

则有状态转移方程：

$$dp_{S_1, S_2} = \bigvee\limits_{i \in S_1, j \not\in S_1 \& j \not\in S_2} \begin{cases} id_j < id_i & [dp_{S_2, S_1 - 2^i + 2^j} = 0] \\ id_j \ge id_i & [dp_{S_2, S_1 - 2^i} = 0] \end{cases}$$

其中 $i$ 是枚举先手出的牌，$j$ 是枚举的换走桌子上的牌；先手必胜当且仅当当且状态后存在一个必败态。

采用记忆化搜索转移即可。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 15, M = 4050;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, l, cnt, S1, S2;
int a[N], b[N], c[N], h[N], _a[N], _b[N], _c[N], id[N];
int dp[M][M];
inline bool dfs(int S1, int S2){
	if(dp[S1][S2] != -1)
	  return dp[S1][S2];
	bool F = 0;
	for(int i = 0; i < cnt; ++i){
		if((S1 >> i) & 1){
			for(int j = 0; j < cnt; ++j){
				if(((S1 >> j) & 1) || ((S2 >> j) & 1))
				  continue;
				if(id[j] < id[i]){
					int nS1 = S1 ^ (1 << i) ^ (1 << j), nS2 = S2;
					if(!dfs(nS2, nS1)){
						F = 1;
						break;
					}
				}
				else{
					int nS1= S1 ^ (1 << i), nS2 = S2;
					if(!dfs(nS2, nS1)){
						F = 1;
						break;
					}					
				}
			}
		}
		if(F)
		  break;
	}
	dp[S1][S2] = F;
	if(F)
	  return 1;
	return 0;
}
bool End;
int main(){
	memset(dp, -1, sizeof(dp));
	n = read(), m = read(), l = read();
	for(int i = 0; i < n; ++i){
		a[i] = read();
		_a[i] = cnt++;
		id[cnt - 1] = a[i];
		S1 |= 1 << _a[i];
	}
	for(int i = 0; i < m; ++i){
		b[i] = read();
		_b[i] = cnt++;
		id[cnt - 1] = b[i];
		S2 |= 1 << _b[i];
	}
	for(int i = 0; i < l; ++i){
		c[i] = read();
		_c[i] = cnt++;
		id[cnt - 1] = c[i];
	}
	if(dfs(S1, S2))
	  puts("Takahashi");
	else
	  puts("Aoki");
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

高桥君、青木君、桌子三个加起来一共有最多 $12$ 张牌。  
从高桥君开始，两人交替出牌到桌子上，然后可以拿回桌子上已有的一张比刚打出的牌更小的牌回手中。  
如果轮到自己打牌但手中没有牌，那么这个人就输了。问最终谁会赢。

由于牌本身是没有区别的，所以我们把所有的牌都存到一起。假设一共有 $P$ 张牌，那么我们设状态 $\text{mask}$ 是一个 $0\sim~3^P$ 之间的整数。把 $\text{mask}$ 写作一个三进制数，从右往左（当然，从左往右也可以）第 $i$ 位代表第 $i$ 张牌目前属于谁。

所以我们可以设计出 dp 状态。我们设 $dp_{\text{mask}, i}$ 表示现在所有牌的状态以及现在轮到谁出牌。

由于正向 dp 有些难以处理，我们按照题意进行模拟，同时更新答案，这样就变成了记忆化搜索。具体实现细节可以参考代码。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 15;

int a[N];
int mi3[N];
int ans[1594323][2]; // 0 = takahashi, 1 = aoki, 2 = table
int n, m, l;

int ask(int mask, int p) {
  if(ans[mask][p]) {
    return ans[mask][p];
  }
  if(p == 0) { // 轮到 Takahashi 出牌
    for(int i = 0; i < n + m + l; i++) {
      int bel = mask / mi3[i] % 3; // 该牌属于谁
      if(bel == 0) {
        ask(mask + 2 * mi3[i], 1); // 将牌打出到桌子上以后，状态该位从 0 变成 2
        if(ans[mask + 2 * mi3[i]][1] == 1) {
          return ans[mask][0] = 1;
        }
        for(int j = 0; j < n + m + l; j++) {
          int bel2 = mask / mi3[j] % 3;
          if(bel2 == 2 && a[j] < a[i]) {
            ask(mask + 2 * mi3[i] - 2 * mi3[j], 1); // 将牌从桌子上收回以后，状态该位从 2 变成 0
            if(ans[mask + 2 * mi3[i] - 2 * mi3[j]][1] == 1) {
              return ans[mask][0] = 1;
            }
          }
        }
      }
    }
    return ans[mask][p] = -1; // 1 代表该情况 Takahashi 必胜，-1 代表该情况 Aoki 必胜。
  } else {
    for(int i = 0; i < n + m + l; i++) {
      int bel = mask / mi3[i] % 3;
      if(bel == 1) {
        ask(mask + 1 * mi3[i], 0);
        if(ans[mask + 1 * mi3[i]][0] == -1) {
          return ans[mask][1] = -1;
        }
        for(int j = 0; j < n + m + l; j++) {
          int bel2 = mask / mi3[j] % 3;
          if(bel2 == 2 && a[j] < a[i]) {
            ask(mask + mi3[i] - mi3[j], 0);
            if(ans[mask + mi3[i] - mi3[j]][0] == -1) {
              return ans[mask][1] = -1;
            }
          }
        }
      }
    }
    return ans[mask][p] = 1;
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  mi3[0] = 1;
  for(int i = 1; i < N; i++) {
    mi3[i] = mi3[i - 1] * 3;
  }
  cin >> n >> m >> l;
  for(int i = 0; i < n + m + l; i++) { // 为了方便三进制位运算从 0 下标开始
    cin >> a[i];
  }
  int st = 0;
  for(int i = n; i < n + m; i++) { // 由于是 0 下标，从第 n 到第 n + m - 1 张牌是 Aoki 的
    st += mi3[i] * 1;
  }
  for(int i = n + m; i < n + m + l; i++) {
    st += mi3[i] * 2;
  }
  ask(st, 0);
  cout << (ans[st][0] > 0 ? "Takahashi" : "Aoki") << '\n';
  return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

三级制状压。

由于 $N+M+L\le 12$，想到状压，又因为每张牌有 $3$ 中状态——在 Takahashi 手中、在 Aoki 手中、在桌上，故用三级制状压。上述三种状态分别对应为为 $1,2,0$。

设 $dp[p][t]$ 为状态为 $p$，操作者为 $t$ 时操作者是否能获胜。$t\in{1,2}$，若 $t=1$ 则 Takahashi 操作否则 Aoki 操作。

转移：

- 打出一张牌后又拿一张：枚举打出的和拿的，若一张在手上一张在桌上，且手上的牌中数字大于桌上的，则可以操作。将状态减打出的牌的权值乘 $t$ 再加拿的牌的权值乘 $t$ 就是最终状态。
- 打出一张牌：枚举打出的，若一张在手上，则可以操作。将状态减打出的牌的权值乘 $t$ 就是最终状态。

若有一种方案可让对手必败，则自己必胜，否则必败。

边界条件：$p$ 转为三级制后不含 $t$，必败。

提前预处理各位权值后 dp 即可。最终若 $dp[S][1]=1$ 则可获胜。$S$ 为初始状态。

```cpp
#include<bits/stdc++.h>
#define int __int128
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int E){
		if(E==0)return;if(E<0){E=-E;putchar('-');}
		Wi(E/10);putchar((E%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int dp[531445][3],n,m,l,a[15],start,pow3[15],A;
	inline bool f(int x,int p){
		int b[15];
		if(dp[x][p]!=-1)return dp[x][p];
		int X=A,cn1=0,cn2=0,P=0,xx=x;
		while(xx){
			if(xx%3==1)++cn1;if(xx%3==2)++cn2;
			b[X]=xx%3;xx/=3;--X;
		}
		while(X)b[X]=0,--X;
		if(p==1){
			if(cn1==0)P=0;
			else{
				for(ri i=1;i<=A;++i)for(ri j=1;j<=A;++j)
				if(b[i]==1&&b[j]==0&&a[i]>a[j]){
					if(f(x-pow3[i]+pow3[j],2)==0){//转移1
						P=1;break;
					}
				}
				for(ri i=1;i<=A;++i)if(b[i]==1){
					if(f(x-pow3[i],2)==0){//转移2
						P=1;break;
					}
				}
			}
		}else{
			if(cn2==0)P=0;
			else{
				for(ri i=1;i<=A;++i)for(ri j=1;j<=A;++j)
				if(b[i]==2&&b[j]==0&&a[i]>a[j]){
					if(f(x-pow3[i]*2+2*pow3[j],1)==0){//转移1
						P=1;break;
					}
				}
				for(ri i=1;i<=A;++i)if(b[i]==2){
					if(f(x-pow3[i]*2,1)==0){//转移2
						P=1;break;
					}
				}
			}
		}
		return dp[x][p]=P;
	}
	inline void zyt(){
		memset(dp,-1,sizeof dp);
		n=r(),m=r(),l=r();
		A=n+m+l;
		pow3[A]=1;for(ri i=A-1;i;--i)pow3[i]=pow3[i+1]*3;
		for(ri i=1;i<=A;++i){
			a[i]=r();start*=3;
			if(i<=n)start+=1;
			else if(i<=n+m)start+=2;
		}
		if(f(start,1))puts("Takahashi");else puts("Aoki");
	}
}
signed main(){
	D1n0::zyt();
}
```

---

## 作者：4041nofoundGeoge (赞：0)

~~前五道题都被写了题解了，好伤心。~~

## 思路

每一个回合，Takahashi 和 Aoki 手中的牌的数量会减少，所以我们不会得到相同的状态。因此，可以通过记忆化搜索的方式来搜索答案。我们从每个状态出发，搜索到哪位玩家会赢。

这种搜索算法有 $O(3^S)$ 种状态和 $O(S^2)$ 种转换，其中 $S=N+M+L\le12$

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAX = 531441;
int n, m, k, dp[MAX * 2], vis[MAX * 2], th[12], v[12];
int getmask(vector<int> &bit)
{
	int r = 0;
	for (int i = 0; i < n + m + k; i++)
		r += th[i] * bit[i];
	return r;
}
int dfs(int Mask)
{
	int mask = Mask;
	if (vis[mask]) return dp[mask];//记忆化
	vis[mask] = 1;
	int f = mask >= MAX;
	if (mask >= MAX) mask -= MAX;
	vector<int> a, b, c, bit(n + m + k);
    //模拟过程
	for (int i = n + m + k - 1; i >= 0; i--)
	{
		bit[i] = mask / th[i];
		mask %= th[i];
	}
	for (int i = 0; i < n + m + k; i++)
		if (bit[i] == 0) a.push_back(i);
		else if (bit[i] == 1) b.push_back(i);
		else c.push_back(i);
	if (f == 0)
	{
		int z = 0;
		for (auto x : a)
		{
			int cnt = 0;
			for (auto y : c) if (v[x] > v[y])
			{
				cnt++;
				bit[x] = 2; bit[y] = 0;
				z += 1 - dfs(getmask(bit) + MAX);
				bit[x] = 0; bit[y] = 2;
			}
			if (!cnt)
			{
				bit[x] = 2;
				z += 1 - dfs(getmask(bit) + MAX);
				bit[x] = 0;
			}
		}
		if (z) dp[Mask] = 0;
		else dp[Mask] = 1;
	}
	else
	{
		int z = 0;
		for (auto x : b)
		{
			int cnt = 0;
			for (auto y : c) if (v[x] > v[y])
			{
				cnt++;
				bit[x] = 2; bit[y] = 1;
				z += dfs(getmask(bit));
				bit[x] = 1; bit[y] = 2;
			}
			if (!cnt)
			{
				bit[x] = 2;
				z += dfs(getmask(bit));
				bit[x] = 1;
			}
		}
		if (z) dp[Mask] = 1;
		else dp[Mask] = 0;
	}
	return dp[Mask];
}
signed main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	th[0] = 1;
	for (int i = 1; i < 12; i++) th[i] = th[i - 1] * 3;
	cin >> n >> m >> k;
	for (int i = 0; i < n + m + k; i++) cin >> v[i];
	vector<int> bit(n + m + k);
	for (int i = 0; i < n; i++) bit[i] = 0;
	for (int i = n; i < n + m; i++) bit[i] = 1;
	for (int i = n + m; i < n + m + k; i++) bit[i] = 2;
	int x = dfs(getmask(bit));
	if (x) cout << "Aoki";
	else cout << "Takahashi";
	return 0;
}
```

---

