# Fire and Big

## 题目描述

小 F 要和其他人玩游戏，但他不想输，所以来找你帮他研究策略。

有 $m$ 个石子，小 F 和小 B 轮流取石子，小 F 先开始取，不能取的人输。

给定正整数 $n$，每次取石子的个数 $k$（$k$ 是正整数） 必须满足如下两个条件**之一**：

- $k$ 是 $n$ 的倍数。
- $k$ 是 $<n$ 的完全平方数。

他们要玩 $T$ 局游戏，不过每一局游戏的 $n$ 不变，只有石子个数 $m$ 会变。

对于每一局，假设两人足够聪明，问谁有必胜策略。

## 说明/提示

### 样例解释

以下将说明当 $n = 2, m = 3$ 时，后手必胜。对先手第一次取走的石子的数量进行讨论：

- 若先手取走 $1$ 个石子，则后手可以取完剩下 $2$ 个石子；
- 若先手取走 $2$ 个石子，则后手可以取完剩下 $1$ 个石子。

因此无论如何，后手总会赢得胜利。

### 数据范围

| 测试点编号 | $n$ | $T,m\le$ |
| :----------: | :----------: | :----------: |
| $1$ | $\le 5\times 10^5$ | $1$ |
| $2\sim 3$ | $\le 5$ | $5$ |
| $4\sim 6$ | $\le 10^5$ | $n$ |
| $7\sim 8$ | $=2$ | $10^9$ |
| $9\sim 11$ | $\le 5$ | $10^9$ |
| $12\sim 14$ | $\le 10^3$ | $10^9$ |
| $15\sim 17$ | $\le 10^5$ | $10^9$ |
| $18\sim 20$ | $\le 5\times 10^5$ | $10^9$ |

对于所有数据，保证 $1\le T,n\le 5\times 10^5$，$1\le m\le 10^9$。

**对于奇数编号测试点，内存限制为 $512\ \text{MB}$；对于偶数编号测试点，内存限制为 $64\ \text{MB}$。**

## 样例 #1

### 输入

```
5 2
1 2 3 4 5```

### 输出

```
FFBFF```

# 题解

## 作者：zhouyuhang (赞：9)

一些与正解无关的暴力略去不提（如暴力 dp，找规律等），这些大致有 40 分。

### Hint 1

考虑所有后手必胜点，不难发现，如果 $x, y$ 同为后手必胜点，则必有 $x \not\equiv y \pmod n$。否则不妨设 $x < y$，$y$ 个石子时只需取 $y - x$ 个石子即可从一个后手必胜点到达另一个后手必胜点，这无疑导出了矛盾。

换言之，在所有 $x \bmod n = r$，只会有一个 $x$ 是后手必胜点。因此，我们在 dp 时无需枚举每一个 $n$ 的倍数去转移，只需记录对每个 $r \in [0, n)$ 记录此前是否有 $x \equiv r \pmod n$ 的后手必胜点 $x$。这样即有 $O(m \sqrt n)$ 的复杂度，结合暴力有 55 分。

### Hint 2

以下证明：后手必胜点的最大值不超过 $n (\sqrt n + 1)$。

考虑一个后手必胜点 $x$ 满足 $\forall p < x \land p \equiv x \pmod n$ 均为先手必胜点，则对每一个这样的 $p$，记 $\{ p - k ^ 2 \mid k \in \mathbb Z^+, k ^ 2 \le \min(n, p)\}$ 中的后手必胜点数为 $r(p)$，则有 $r(p) \ge 1$。而根据 Hint 1，对于每个 $k ^ 2 \le n$，$\{p - k ^ 2 \mid p \equiv x \pmod n, k ^ 2 \le p < x\}$ 至多有一个后手必胜点，从而有 $\sum _ {p < x, p \equiv x \pmod n} r(p) \le \sqrt n$，因而这样的 $p$ 的数量不超过 $\sqrt n$，从而有 $x < n (\sqrt n + 1)$。

应用这一结论，上文中 $O(m \sqrt n)$ 的 dp 复杂度降至 $O(n ^ 2)$。实际测试可以发现，这个上界很松，实际在 $n \le 10 ^ 5$ 时，最大值不超过 $10 ^ 7$，进行一定卡常后一共可以得到 85 分。

### 正解

注意到，后手必胜点最多只有 $n$ 个。因此，我们只需将转移改为从后手必胜点开始的主动转移即可做到 $O(n \sqrt n)$。

---

## 作者：Cute_M (赞：8)

前面忘了，但是不如 HOI，后面忘了。

打比赛纯粹是因为没玩原神。

按照博弈论中关于出边状态决定当前状态的思想写一个记忆化搜索，其中空间 $10^8$ 能满足，$10^9$ 则时空均稳炸。

写完记忆化搜索之后发现有 [$30$ 分](https://www.luogu.com.cn/record/177061593)。

接下来考虑手玩 $n\le 5$ 的部分分，把对应的状态数组打出来可以发现只有很少几个 $m$ 是 $0$ 态（后手必胜），打表即可，有 [$55$ 分](https://www.luogu.com.cn/record/177064425)。

这时候发现当 $m$ 很大时基本上全是 $1$ 态。于是充分利用赛时能查看提交情况的优势，当 $m\ge 11451490$ 时直接返回 $1$ 态。拿到了 [$85$ 分](https://www.luogu.com.cn/record/177065460)。剩下几个点时间炸了。

打一个表，发现在某一个特定的值后均为先手必胜，且后手必胜的状态最多有 $n$ 个。这是因为如果一个值后手必胜，则在其之后和其同余（对于 $n$）的值都能对其有出边，则该状态自然为 $1$ 态。有结论：至多有 $n$ 个 $0$ 态。

赛时止步于此，赛后反复提交发现这个 $0$ 态的上界设定为 $6\times 10^7$ 能过。

又因为最多有 $n$ 个 $0$ 态，直接对于每一个 $0$ 态向上标记另一种情况 $+i^2$ 即可。对于超过 $6\times 10^7$ 的值直接返回先手必胜（此时不存在 $0$ 态）。

复杂度未知但能过。

---

## 作者：dyc2022 (赞：6)

首先，我们注意到所有后手必胜点一定对 $n$ 不同余。原因是若存在 $x$ 是后手必胜点，那么对于任何 $x+kn$ 的点，即所有 $>x$ 且在模 $n$ 的意义下与 $x$ 同余的决策点都可以通过先手取走 $kn$ 达到先手必胜。

这样一来，先手必败点就严格只剩下 $n$ 个。且由于相同余数的点我们只选择一个，因此我们只需要考虑取走完全平方数个的情况。

  这是好处理的。首先，我们会注意到，当 $m$ 大于一个特定值时，所有的询问都是先手必胜。因此我们可以进行打表，发现所有可能成为后手必胜点的全部集中在 $\le 140n$ 范围，这是 $O(n)$ 量级的。因此，我们设置 $f_x$ 表示 $x$ 是否为可行的先手必胜决策点，然后用类似埃氏筛的操作，若遇到先手必败决策点 $i$，就把所有满足 $j^2 < n$ 的所有 $f_{i+j^2}$ 赋值为必胜。

因此，易得 AC 代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int n,T;
bitset<70000007> f;
bitset<500006> vis;
main()
{
	scanf("%d%d",&T,&n);
	for(int i=0;i<=n*140;i++)
    {
        if(vis[i%n]){f[i]=1;continue;}
        if(!f[i])
        {
            for(int j=1;j*j<n&&i+j*j<=n*140;j++)
                f[i+j*j]=1;
            vis[i%n]=1;
        }
    }
	while(T--)
	{
		int x;
		scanf("%d",&x);
		if(x>140*n)putchar('F');
		else putchar(f[x]?'F':'B');
	}
	return 0;
}
```

---

## 作者：Milthm (赞：4)

这个题其实不是很难，~~但是赛时的时候我写挂了，而且写挂的地方很离谱~~。

首先这种博弈论直接 dp，设 $dp_i$ 表示 $m=i$ 时先手能否必胜，按照题目转移即可，可以获得一部分分数。

然后你都有暴力了，为什么不打表呢？打了一下表，哎，怎么大多数都是先手赢啊。

好吧这是肯定的，因为如果两个后手必胜点模 $n$ 是同余的，那么它们就可以通过减若干个 $n$ 到达，这是矛盾的。这告诉我们后手必胜点是稀疏的。

然后可以通过这个优化一下枚举 $n$ 的倍数的过程，但是还是过不去。所以我们再打表看看：

$n=100$ 时，后手必胜点最大为 $789$；

$n=1000$ 时，后手必胜点最大为 $17658$；

$n=10000$ 时，后手必胜点最大为 $368170$；

$n=100000$ 时，后手必胜点最大为 $6295780$。

我们发现这个后手必胜点最大值并不是很大，且其量级为 $O(n\sqrt n)$。

于是我们只要在原本的暴力 dp 后面加一个特判：如果大于一定的值先手必胜。这样就可以通过本题，时间复杂度 $O(n\sqrt n)$。


```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int T,n,rr[N];
bitset<N*230>dp;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T>>n;
	for(int i=0;i<N*230;++i){
		if(rr[i%n])dp[i]=1;
		if(!dp[i]){
			for(int j=1;j*j<n&&i+j*j<N*230;++j)dp[i+j*j]=1;
			rr[i%n]=1;
		}
	}
	while(T--){
		int m;cin>>m;
		if(m>=N*230||dp[m])cout<<"F";
		else cout<<"B";
	}
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：3)

犯罪式的把这题写了。。。
该做法当然存在被卡点的情况，但是赛场上能 AC 即为胜利。

## 题面
[P11056 Fire and Big](https://www.luogu.com.cn/problem/P11056)
## 分析
打了一个表，发现当 $m \gt 10^8$ 的时候只有 $1$ 个是后手赢。于是当 $m \gt 10^8$ 的时候直接输出先手必胜。

$m \le 10^8$ 的时候直接暴力预处理就行了。从所有状态为必输的转移一下就行了。

一开始的时候还以为是根号分治，顺着思路打了一个表就秒了，挺有趣的。
## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
namespace fasthys{
	inline int read()
	{
		int x(0),f(0);
		char c(getchar());
		while(!isdigit(c))
		{
			f|=c=='-';
			c=getchar(); 
		}
		while(isdigit(c))
		{
			x=(x<<3)+(x<<1)+(c^48);
			c=getchar();
		}
		return f?-x:x;
	}
	inline void write(int x)
	{
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+'0');
	}
}
using namespace fasthys; 
bitset<100000001>dp;
int T,n;
int main()
{
	scanf("%d%d",&T,&n);
	for(int i=0;i<=100000000;i++)
	{
//		cout<<i<<' '<<dp[i]<<endl;
		if(dp[i])continue;
		
		for(int j=n;i+j<=100000000;j+=n)
		{
//			if(i+j<n)
//			cout<<i<<' '<<j<<endl;
			dp[i+j]=1;
		}
		for(int j=1;j*j<n&&i+j*j<=100000000;j++)
		{
//			if(i+j*j<n)	
//			cout<<i<<' '<<j<<endl;	
			dp[i+j*j]=1;
//			if(dp[i+j]==1)
		}
	}
	for(int i=1;i<=T;i++)
	{
		int m;
		scanf("%d",&m);
		if(m>1e8)
		{
			putchar('F');
		}
		else if(dp[m])
		{
			putchar('F');	
		}
		else putchar('B');
	}
	return 0;
}
```

---

## 作者：xiaoliebao1115 (赞：1)

非常好题目，使我大脑旋转。

定义 $f_i$ 为石子个数为 $i$ 的时候是先手赢还是先手输，对应 $1$ 和 $0$。

因为一个数只能变成比他小的数，所以也只能从较小数转移过来，考虑两个转移方式。

- 如果有和 $i\bmod n$ 同余的 $j$，并且 $f_j=0$，那么必须有 $f_i=1$。因为 $i$ 能够减去一个 $n$ 的倍数到达 $j$，能够到达先手必输点的必然是先手必胜点。

- 如果有 $j+k\times k=i$，并且 $f_j=0$，那么也必须有 $f_i=1$。

- 其他情况到不了任何先手必输点，那么必然也是先手必输点，$f_i=0$。

可以对于 $f$ 进行打表，打表后发现当 $i>n \times 120$ 的时候必然全都是 $f_i=1$，十分简单。

后手必胜点最多 $n$ 个，因为不会有两个模 $n$ 同余的。总共 $f_i$ 的状态数是 $n\times 120$ 个，这个肯定不会超时。每个后手必胜点向后进行 $j+k\times k=i$ 这样的转移，由于 $k\times k<n$，所以时间复杂度 $O(n\sqrt n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int nn=5e5+5;
int t,n,maxx,m;
bool f[nn*120],mod[nn];
inline int read(){
	int x=0,f=0;
	char c=getchar();
	while(!isdigit(c)){
		f|=c=='-';
		c=getchar(); 
	}
	while(isdigit(c)){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return f?-x:x;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	t=read(),n=read();
	for(int i=0;i<nn*120;i++){
		if(mod[i%n]) f[i]=1;
		if(!f[i]){
			mod[i%n]=1;
			for(int j=1;j*j<n&&i+j*j<=nn*120;j++) f[i+j*j]=1;
		}
	}
	while(t--){
		m=read();
		if(m>120*n) putchar('F');
		else if(f[m]) putchar('F');
		else putchar('B');
	}
	return 0;
}
```
代码很好懂捏。

完结撒花！

---

## 作者：晴空一鹤 (赞：1)

好题！

首先明显的暴力是直接预处理出 SG 函数的值。根据直觉，我们把所有的 SG 值按余数分为 $n-1$ 列，打一个小小的表。容易发现一列中只有一个先手必败。原因也很容易理解，因为同一列之间可以相互转移，第一个必败后就全是必胜了。

我们开一个数组 $cnt_i$ 表式余数为 $i$ 的 SG 值中是否出现了必败点，仍旧和暴力一样跑，不过在第一次所有 $cnt_i$ 都为 $1$ 时即可退出循环。

交一发上去可以得到 80pts，合理限制最大循环次数可以得到 85pts。

后面的优化参考了 [Yanami_Anna 的题解](https://www.luogu.com.cn/article/4536u0jx)。容易发现我们的瓶颈在于求 SG 值。我们可以发现能使当前 SG 变为 $1$ 的点都是 SG 为 $0$ 的点，而这种点数量只有 $n$ 个，因此我们在每找到一个这样的点的时候让它主动向后面转移即可。

[代码放在云剪贴板。](https://www.luogu.com.cn/paste/4c8yczmh)

---

## 作者：takanashi_mifuru (赞：1)

首先容易发现，对 $n$ 取模了之后相同的点只能有一个后手必胜，因为假设有两个，那个大的就可以通过直接导成小的来达成先手必胜。

然后给 SG 函数打个表，你发现如果 $m>120n$，最后就一定会获胜，你就把这个范围内的 SG 函数处理出来就行了。

然后爆了，因为每次都要花根号回去找，但是你发现把同余数的判掉之后我只需要让这个先手必败点往后找点给他们标记成必胜就可以把他打成 $n\sqrt n$，然后就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n;
bool SG[60000005];
bool done[500005];
int main(){
    scanf("%d%d",&q,&n);

    int lim=n;
    SG[0]=false;
    done[0]=true;
    for(int j=1;j*j<=lim;j++){
        SG[j*j]=true;
    }
    int pos=0;
    for(int i=1;i<=120*lim;i++){
        pos++;
        if(pos==lim)pos=0;
        if(done[pos]){
            SG[i]=true;
            continue;
        }
        if(!SG[i]){
            done[pos]=true;
            for(int j=1;j*j<=lim;j++){
                SG[i+j*j]=true;
            }
            continue;
        }
    }
    while(q--){
        int tmp;
        scanf("%d",&tmp);
        if(tmp>120*lim){
            putchar('F');
        }
        else{
            if(SG[tmp])putchar('F');
            else putchar('B');
        }
    }
    return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

对于每一位的暴力博弈 dp 是极好做的。

打表发现必败点很少，于是你决定思考必败点的性质。

于是你注意到如果任意两个必败点模 $n$ 意义下不可能同余，因为模 $n$ 意义下同余的两个点一定是可以一步到达的。

由此可以发现必败点数量最多就 $n$ 个。

所以我们把暴力 dp 改成由必败点转移就行。

但这个前提是对每个必败点进行转移，而必败点的上界我们不知道。

于是你发现把上界设定为 $10^8$ 过了。

打表可以证明这个界小于 $10^8$，严格的不会算，就这样。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100000000
using namespace std;
bitset<N>ans,flc;
int t,n;
void csh(){
    ans[0]=0;
    for(int i=0;i<=N;i++){
        if(flc[i%n])ans[i]=1;
        if(ans[i])continue;
        for(int j=1;j*j<n&&i+j*j<N;j++)
            ans[i+j*j]=1;
        flc[i%n]=1;
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(),cout.tie();
    cin>>t>>n;
    csh();
    while(t--){
        int x;
        cin>>x;
        if(x>N||ans[x])printf("F");
        else printf("B");
    }
    return 0;
}
```

---

### 后记

出题人说：

> 一些与正解无关的暴力略去不提（如暴力 dp，找规律等），这些大致有 40 分。

然而注意到 @[CarrotMeow](/user/912750) 的这句话：

> 来自同学：设 $dp_i$ 为 $1$ 表示先手必胜，首先注意到当 $m < n$ 时输出 $dp_m$ 对应结果，$m > 3n$ 时输出 `F`，$dp_{m\bmod n}$ 为 $1$ 输出 `B`，否则输出 `F`，可以获得 $55\text{pts}$ 的高分。/qd

上述文段来自[出题人题解](https://www.luogu.com.cn/article/buytikhn)及评论区。

你说得对，但这个糖批同学就是我 /qd

场上一个性质都没发现，但是赞美抽象[数据](https://www.luogu.com.cn/record/177069789)！！

这实在太好笑了。

---

## 作者：_Lazy_whr_ (赞：0)

首先看到题目，很明显是一道博弈论。那么看到博弈论就能想到 $DP$ ，所以想到状态：令 $dp_i$ 表示 $m=i$ 时，先手能不能赢，能赢为 $1$ ，否则为 $0$ 。

那么这样是会超时的……

考虑优化：我们可以打表找规律，发现后手必胜点并不是很大，大约在 $\sqrt{n}$ 的范围。

于是我们只要在原本的暴力 $dp$ 后面加一个特判：如果大于一定的值先手必胜，这样就可以通过本题，时间复杂度 $O(n\sqrt{n})$ 。

注意坑点：不用 `bitset` 优化会喜提 $MLE$ 。

开防抄袭了……
```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC target("avx")
#pragma GCC optimize(3,"Ofast","inline")
namespace FastIO
{
	inline int read()
	{
		int x = 0, f = 1;
		char ch = getchar();
		while(ch < '0' || ch > '9')
		{
			if(ch == '-')
			{
				f = -1;
			}
			ch = getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<typename T> inline void read(T &x)
	{
		x = read();
		return;
	}
	template<typename T,typename... Args> inline void read(T &x, Args &...x_)
	{
		read(x);
		read(x_...);
		return;
	}
}
namespace Constants
{
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-6;
	const double PI = 3.14159265358979323;
}
using namespace std;
using namespace FastIO;
using namespace Constants;
inline void CLOSE()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	return;
}
const int N = 5e5 + 10;
int f[N];
bitset<N * 230> dp;

signed main()
{
	CLOSE();
	int t = read(), n = read();
	for(int i = 0; i < N * 230; i++)
	{
		if(f[i % n] == 1)
		{
			dp[i] = 1;
		}
		if(dp[i] == 0)
		{
			for(int j = 1; j * j <= n && i + j * j < N * 230; j++)
			{
				dp[i + j * j] = 1;
			}
			f[i % n] = 1;
		}
	}
	while(t--)
	{
		int m = read();
		if(m >= N * 230)
		{
			cout << "F";
		}
		else if(dp[m] == 1)
		{
			cout << "F";
		}
		else
		{
			cout << "B";
		}
	}
	return 0;
}

```

---

## 作者：Redshift_Shine (赞：0)

好题，让我感受到了场切蓝题的快感。

首先看到题的时候一头雾水，但很快想到了不久前在 HDUOJ 打的打表找规律题，遂决定打表。

通过打表，可以得到两种用时显著不同的解法。

第一种，注意到当 $m$ 达到一定数量级后先手必胜，所以选取一个可以接受的数据范围暴力算出所有范围内的 $m$ 的先手必胜性。

同时也是赛时代码。

```c++
#include <bitset>
#include <cstdio>
using namespace std;
const int N = 1e8, M = 5e5 + 10;
int t, n, x, rel[M];
bitset<N> mp;
int main()
{
	scanf("%d%d", &t, &n);
	for (int i = 0; i < N; i++)
	{
		if (mp[i])
			continue;
		rel[i % n] = i;
		for (int j = 1; i + j * j < N and j * j < n; j++)
		{
			mp[i + j * j] = true;
		}
		for (int j = 1; i + j * n < N; j++)
		{
			mp[i + j * n] = true;
		}
	}
	mp[0] = mp[n];
	for (int i = 1; i <= t; i++)
	{
		scanf("%d", &x);
		putchar(rel[x % n] < x or mp[x] ? 'F' : 'B');
	}
}
```

第二种，通过进一步的观察可以发现对于模 $n$ 的每个余数有且仅有一个 $m$ 使得先手必败，可以在计算必胜性时进一步优化。

```c++
#include <bitset>
#include <cstdio>
using namespace std;
const int N = 1e8, M = 5e5 + 10;
int t, n, x, rel[M];
bitset<N> mp;
int main()
{
	scanf("%d%d", &t, &n);
	for (int i = 0; x < n; i++)
	{
		if (mp[i] or rel[i % n])
			continue;
		rel[i % n] = i + 1;
		x++;
		for (int j = 1; j * j < n; j++)
		{
			mp[i + j * j] = true;
		}
	}
	mp[0] = mp[n];
	for (int i = 1; i <= t; i++)
	{
		scanf("%d", &x);
		putchar(rel[x % n] == x + 1 ? 'B' : 'F');
	}
}
```

时间复杂度 $O(n\sqrt n)$。

---

