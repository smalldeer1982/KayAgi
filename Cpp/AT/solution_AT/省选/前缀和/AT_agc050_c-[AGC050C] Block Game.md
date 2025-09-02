# [AGC050C] Block Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc050/tasks/agc050_c

左右に無限に続くマスの列があります。 これを用いて、あなたとすぬけ君は以下のゲームをプレイします。

- 審判が、`B` と `S` からなる「ターン文字列」$ t $ を作り、二人に見せる。
- まず、すぬけ君がマスのうち $ 1 $ つの上に立つ。
- そして、各 $ i\ =\ 1,\ ...,\ |t| $ について、この順番に以下が行われる。
  - $ t $ の $ i $ 文字目が `B` のとき、あなたのターンである。あなたは、他のブロックやすぬけ君を含まないマスを $ 1 $ つ選び、ブロックを置く。設置後、すぬけ君の両隣のマスにともにブロックが置かれている場合、あなたの勝利でゲームが終了する。
  - $ t $ の $ i $ 文字目が `S` のとき、すぬけ君のターンである。すぬけ君は、隣の空きマスに移動するか、何もしない。
- この時点でゲームが終了していない場合、すぬけ君の勝利でゲームが終了する。

`B`, `S`, `?` からなる文字列 $ s $ が与えられます。 $ s $ に含まれる `?` の個数が $ Q $ であるとき、`?` をそれぞれ `B` または `S` で置き換えてターン文字列とする方法は $ 2^Q $ 通り存在します。 これらの $ 2^Q $ 個のターン文字列のうち、両プレイヤーが最適に行動したときにあなたが勝利するようなものは何個あるでしょうか。 この答えを $ 998,244,353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |s|\ \leq\ 10^6 $
- $ s $ は `B`, `S`, `?` からなる。

### Sample Explanation 1

$ 1,\ 4 $ ターン目があなたのターンで、$ 2,\ 3,\ 5 $ ターン目がすぬけ君のターンです。 この場合、両者が最適に行動するとすぬけ君が勝つことがわかります。

## 样例 #1

### 输入

```
BSSBS```

### 输出

```
0```

## 样例 #2

### 输入

```
?S?B????S????????B??????B??S??```

### 输出

```
16777197```

# 题解

## 作者：joke3579 (赞：8)

## $\text{statement}$

有一个由房间组成的序列，其向左右两端无限延伸。你和 Snuke 在玩下面的游戏：
- 裁判给出一个由 `B` 和 `S` 组成的字符串 $t$，名为回合决定串，并将它展示给两名玩家。
- 首先，Snuke 站在其中一个房间里。
- 随后，对于每个 $i = 1,2,\dots,|t|$，发生如下的事件：
  - 如果 $t$ 中第 $i$ 个字母为 `B`，则这是你的回合。你会选择一个其中没有障碍或 Snuke 的房间，在其中放置一个障碍。这之后，如果 Snuke 所在房间左右两侧的房间均放置有障碍，则你胜利，游戏结束。
  - 如果 $t$ 中第 $i$ 个字母为 `S`，则这是 Snuke 的回合。他可以移动到与当前所在房间相邻且无障碍的房间，或什么都不做。
- 如果 $|t|$ 轮后游戏仍未结束，则 Snuke 胜利，游戏结束。

给定字符串 $s$，其中仅含有 `B`、`S` 与 `?` 三种字符。设 $s$ 中含有 $q$ 个 `?`，有 $2^q$ 种填法将 $s$ 中的 `?` 替换为 `B` 或 `S`，得到一个回合决定串。假设两名玩家都按最优策略操作，在这 $2^q$ 个串中，有多少种填法使得你能胜利呢？

请输出答案模 $998244353$ 的值。

$1\le |s|\le 10^6$。

## $\text{solution}$

记 $(L,R)$ 为 Snuke 可能面对的一个局面，其中 $L$ 为 Snuke 向左可以走入的房间数，$R$ 为 Snuke 向右可以走入的房间数。有 $(L,R)$ 等价于 $(R,L)$。

容易发现你操作的最优策略是将 Snuke 的一侧堵死，令其在这一侧可以走入的房间数为 $0$。重新陈述游戏：   
Snuke 的初始局面为 $(\infty, \infty)$。在 Snuke 的回合，他可以将 $(L,R)$ 的局面转移为 $(L\pm 1, R\mp 1)$ 或不变。在你的回合，你会将 $(L,R)$ 的局面转移为 $(\min\{L,R\},0)$。

可以发现，你进行的每次操作都会至少将 Snuke 的可达范围缩小至原来的二分之一。因此你只需要操作 $O(\log |s|)$ 次就可以胜利。   
这个条件不好计数你胜利的串，但便于计数 Snuke 胜利的串。考虑首先求得在这 $2^q$ 个串中 Snuke 胜利的串的数量，再用 $2^q$ 减去其就是答案。

考虑倒序枚举。我们发现，当位置 $i$ 的字符为 `B` 且其为倒数第 $k$ 个时，必须保证 $i$ 到下一个 `B` 之间存在至少 $2^{k-1}$ 个 `S`。只有这样才能使得 Snuke 在当前情况下不败。   
这引出了 dp 的解法。

由于 dp 方程的第二维取值范围为 $O(\log n)$，总时间复杂度 $O(n\log n)$。

$\text{code : }$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
const int N = 1e6 + 10, mod = 998244353;
int add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
int n, ans = 1, lgv, f[N][24], cnt[N], len;
char s[N];

signed main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> s + 1; n = strlen(s + 1), lgv = __lg(n) + 1;
	reverse(s + 1, s + 1 + n);
	rep(i,1,n) {
		if (s[i] == 'B') cnt[i + 1] = cnt[i] + 1;
		else cnt[i + 1] = cnt[i];
		if (s[i] == '?') ans = add(ans, ans);
	} f[0][0] = 1;
	rep(i,1,n) {
		if (s[i] == 'S' or s[i] == '?') {
			memcpy(f[i], f[i - 1], sizeof f[i]);
		}
		if (s[i] == 'B' or s[i] == '?') {
			rep(j,1,lgv) {
				len = 0; if (j > 1) len = 1 << j - 2;
				int from = max(0, i - len - 1); len = min(len, i);
				if (len == 0 or cnt[i] == cnt[i - len]) 
					f[i][j] = add(f[i][j], f[from][j - 1]);
			}
		} 
	} 
  	rep(i,0,lgv) ans = add(ans, mod - f[n][i]);
	cout << ans << '\n';
}
```


---

## 作者：2008verser (赞：1)

你仔细感受这个游戏，Snuke 有一个活动区间，只要能动他就会向当前区间的中心靠。设两个变量表示他左右边的空位数量。

考虑此时一个 $B$ 对这两个变量的影响，是较大的变量会变为零。

设 $B$ 割开的长度为 $(B),a_1,(B),a_2,(B),\dots,(B),a_m,(B)$，由于游戏性质，不计算最前和最后的段。

$\text{You win}$ 的充要条件是，某次 $B$ 以后 Snuke 另一侧空位是 $0$。

设 $x$ 是某次 $B$ 以后 Snuke 另一侧的空位数，经过一个长为 $a_i$ 以后 $x\leftarrow\min(a_i,\lfloor\frac{x}{2}\rfloor)$。

对每个 $a_i$ 的贡献一起考虑。在把整个序列翻过来情况下，$\text{You win}\Longleftrightarrow\min\left(\lfloor\frac{a_i}{2^{i-1}}\rfloor\right)=0$。

立刻发现当段数超过 $O(\log n)$ 必然是 $\text{You win}$。求出 $\min\left(\lfloor\frac{a_i}{2^{i-1}}\rfloor\right)\gt 0$ 的数量，用总数减去即可。

接下来的 dp 很简单：设 $f_{i,j}$ 填完 $1\sim i$，$i$ 是 $B$，已经有 $j$ 段方案数。

$$
f_{i,j}\to f_{k,j+1},\lfloor\frac{k-i-1}{2^j}\rfloor\gt 0
$$

进行前缀和优化，时间复杂度 $O(n\log n)$。

[AC 链接](https://atcoder.jp/contests/agc050/submissions/61041578)

---

## 作者：skyskyCCC (赞：1)

## 前言。
较远古 AGC 题选做。让你求填法并取模，而且都按最优策略，还要考虑每一个空可以填什么，这个被操作序列还是个无限延伸的，那么显然可以考虑动态规划。
## 分析。
这个动态规划有一种一眼的美感，大体上是很好想的。而且不需要什么大的优化，所以我们直接考虑最暴力的转移方程，我们从最基本的状态开始定义。因为我们考虑的是逃亡方向，所以我们考虑一个状态定义为 $\left(l,r\right)$ 表示 Snuke 的左边有 $l$ 个连续的空位，右侧有 $r$ 个连续的空位。显然遇到第一个 $B$ 之前均是 $\left(+\infty,+\infty\right)$ 而遇见第一个 $B$ 以后，按照最佳策略，我们肯定要在 Snuke 旁边的空位放一个障碍从而使 Snuke 只能有一个固定的逃亡方向，那么此时状态可以退化为 $\left(0,+\infty\right)$。那么我们可以退出规律。设当前状态为 $\left(0,r\right)$ 则经过 $m$ 个 $S$ 和一个 $B$ 后，状态就会退化到 $\left(0,\min\left(m,\dfrac{r}{2}\right)\right)$ 的形式。由此归纳可以得出：若 Snuke 要赢则到倒数第 $i$ 段中 $S$ 的长度至少是 $2^{i-2}\left(i>1\right)$。

此时状态方程就很好设了。设 $dp\left[i\right]\left[j\right]$ 表示第 $i$ 个位置可以为 $B$ 且右侧的 $S$ 为倒数第 $j$ 段，设 $i$ 右边第一个 $B$ 的位置为 $b$ 并且有 $i+2^{j-1}<b$ 存在。这个限制情况是因为 $j\leq\log n$ 存在。从而得出转移方程：
$$dp\left[i\right]\left[j\right]=\sum_{k=i+1}^bdp\left[k\right]\left[j-1\right]$$

一个很明显的前缀和优化动态转移。再考虑第一个 $B$ 所在的位置，设该位置为 $b_2$ 并且 ```?``` 的个数为 $X$ 的话，就有答案的形式：
$$ans=2^X-\sum_{i=1}^{b_2}\sum_{j=1}^{19}dp\left[i\right]\left[j\right]$$

但是有一点需要注意，就是如果你不能操作的情况，这种情况下需要在原基础上减去一。然后稍微处理一下边界情况即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
const int mod=998244353;
string s;
int len,ans=1,l;
int flag=1;
int sum[1000005][50],dp[1000005][50];
int work(int x,int y){
	x+=y;
	return (x<mod)?x:x-mod;
}
int main(){
	cin>>s;
	l=s.length();
	for(int i=s.length()-1;i>=0;i--){
		//cout<<"yep!";
		if(s[i]=='?'){
			ans<<=1;
			if(ans>mod){
				ans-=mod;
			}
		}
		if(s[i]!='S'){
			if(l==s.length()){
				dp[i][0]=1;
			}
			for(int j=0;j<=18;j++){
				if(i+(1<<j)<l){
					dp[i][j+1]=work(sum[i+(1<<j)+1][j],mod-sum[l+1][j]);
				}
			}
		}
		if(s[i]=='B'){
			l=i;
			flag=0;
		}
		for(int j=0;j<=19;j++){
			sum[i][j]=work(dp[i][j],sum[i+1][j]);
		}
	}
	//cout<<"yep!";
	if(flag==1){
		ans--;
	}
	for (int i=0;i<=l;i++){
		for (int j=0;j<=19;j++){
			ans=work(ans,mod-dp[i][j]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

