# [USACO22FEB] Redistributing Gifts G

## 题目描述

Farmer John 有 $N$ 个礼物，编号为 $1 \ldots N$，准备分给他的 $N$ 头奶牛，奶牛也编号为 $1 \ldots N$（$1 \leq N \leq 18$）。每头奶牛有一个愿望清单，清单是 $N$ 个礼物的一个排列，奶牛更喜欢清单中靠前的礼物。

FJ 很懒，直接将礼物 $i$ 分配给了奶牛 $i$。现在，奶牛们聚集在一起，决定重新分配礼物，使得重新分配后，每头奶牛最终得到的礼物要么与原来相同，要么是她更喜欢的礼物。

还有一个额外的限制：一个礼物只能重新分配给与它原主人同类型的奶牛（每头奶牛要么是荷斯坦牛，要么是根西牛）。给定 $Q$（$1 \leq Q \leq \min(10^5, 2^N)$）个长度为 $N$ 的品种字符串，对于每个字符串，计算符合该字符串的重新分配方案的数量。

## 说明/提示

- 对于 $T = 2, \cdots ,13$，测试用例 $T$ 满足 $N = T + 4$。
- 测试用例 14-18 满足 $N = 18$。

## 样例 #1

### 输入

```
4
1 2 3 4
1 3 2 4
1 2 3 4
1 2 3 4
5
HHHH
HHGG
GHGH
HGGG
GHHG```

### 输出

```
2
1
1
2
2```

# 题解

## 作者：7KByte (赞：13)

有个很奇妙的 $\mathcal{O}(n^22^n)$ 的做法。

首先题目等价于将给定图划分成若干个简单环，所以我们可以设计 DP 状态，$f_{x,S}$ 表示以 $x$ 结尾，经过节点为 $S$，以 $S$ 中最小的点出发的路径方案，如果 $x$ 到最小点有边，就更新 $h_{S}$ 表示点集为 $S$ 的环的方案。

然后我们再合并环，$g_{S}$ 表示将集合 $S$ 划分成若干环的方案，然后枚举最小点所在的环 $T$，有转移 $g_{S} = \sum \limits_{T\subseteq S} h_{T}g_{S/T}$，这样就可以做到 $\mathcal{O}(n^22^n + 3^n)$。

我一度认为 $3^n$ 是信息极限了，但是这题还有一些特殊性质。

我们观察到由 $h$ 可以直接推出 $g$，那么我们是否可以跳过 $h$ 这一步，直接由 $f\to g$。

那么我们更新一下状态，$f_{x, S}$ 表示已经 fix 了若干个环，然后当前路径是从 $S$ 中最小的点出发到 $x$ 结束的方案数，这样 $f_{x,S}$ 可以直接转移到 $g_{S}$。

但是这样 $f$ 就需要考虑新开一个环的可能，所以我们再从 $g\to f $，枚举比 $g_{S}$ 中最小的点更小的点 $x$ 作为起点，然后 $g_{S} \to f_{x, S\cup\{x\}}$。为什么要更小的点，因为避免一个划分方案重复统计，以环的最小的点为关键字从大到小依次考虑。

这样时间复杂度是 $\mathcal{O}(n^22^n)$。代码和上面描述有点区别，是以环的最大点作为关键字从小到大考虑，本质相同。

```cpp
#define N 18
int n, a[N][N], e[N][N], bt[1 << N]; char ch[N + 5]; LL f[N][1 << N], g[1 << N];

int main() {
	read(n);
	rep(i, 0, n - 1){
		rep(j, 0, n - 1)read(a[i][j]), a[i][j] --;
		rep(j, 0, n - 1){
			e[i][a[i][j]] = 1;
			if(a[i][j] == i)break;
		}
	}
	int w = (1 << n) - 1;
	bt[0] = ~0; rp(i, w)bt[i] = bt[i >> 1] + 1;
	g[0] = 1;
	rep(s, 0, w){
		int k = bt[s];
		rep(i, 0, k){
			if(e[i][k])g[s] += f[i][s];
			rep(j, 0, k)if(!((s >> j) & 1) && e[i][j])
				f[j][s | (1 << j)] += f[i][s];
		}
		rep(i, k + 1, n - 1)f[i][s | (1 << i)] += g[s];
	}
	int T; read(T);
	while(T--){
		scanf("%s", ch);
		int s = 0;
		rep(i, 0, n - 1)if(ch[i] == 'H')s |= 1 << i;
		printf("%lld\n", g[s] * g[w ^ s]);
	}
	return 0;
}
```

---

## 作者：123zbk (赞：6)

令 $g_S$ 表示连成一个置换环的方案数。然后将环合并，设 $h_S$ 表示将集合 $S$ 分成若干个置换环的方案数，显然有转移 $h_S=\sum\limits_{T\subseteq S}g_Th_{S/T}$。

只需考虑如何求出将其连成一个置换环的方案数。

暴力的 dp 就是设 $dp_{i,j,k}$ 表示集合 $i$，起始点为 $j$，最后一个位置为 $k$ 的方案数。

枚举下一个元素，实时判断能不能转移到以及有没有构成环即可。此时复杂度为 $O(2^nn^3)$，考虑优化。

注意到可以去掉起始点这一维，因为我们可以钦定集合 $i$ 中最小的点当成起始点。

所以设 $dp_{i,j}$ 表示从集合 $i$ 的最小的点出发，到达 $j$ 的方案数。接下来枚举点 $k$，如果 $k$ 不在集合 $i$ 中且从 $j$ 能转移到 $k$，就可以进行转移。

对于每一个集合 $S$，枚举其最后一个到达的点，如果它能够回到起始点，那么就将其计算到 $g_S$ 的贡献中。

复杂度为 $O(2^nn^2+3^n)$。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn=19,maxm=1<<18;
int n,Q,s[maxn];
ll dp[maxm][maxn],g[maxm],h[maxm];
char c[maxn];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        bool flag=0;
        for(int j=0;j<n;j++){
            int x;
            cin>>x;
            x--;
            if(!flag){
                s[i]|=(1<<x); 
            }
            if(x==i) flag=1;
        }
    }
    for(int i=0;i<n;i++){
        dp[1<<i][i]=1;
    }
    for(int i=1;i<(1<<n);i++){
        int p=__lg(i&(-i));
        for(int j=p;j<n;j++){  
            if(dp[i][j]){
                for(int k=p+1;k<n;k++){ 
                    if(!(i&(1<<k)) and s[j]&(1<<k)){
                        dp[i|(1<<k)][k]+=dp[i][j];
                    }
                }
            }
        }
    }
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            int p=__lg(i&(-i));
            if(s[j]&(1<<p)){
                g[i]+=dp[i][j];
            }
        }
    }
    h[0]=1;
    for(int i=1;i<(1<<n);i++){
        for(int j=i;j;j=(j-1)&i){
            if(j&(i&(-i))){
                h[i]+=g[j]*h[i^j];
            }
        }
    }
    cin>>Q;
    while(Q--){
        cin>>c;
        int ans=0;
        for(int i=0;i<n;i++){
            if(c[i]=='H') ans|=(1<<i);
        }
        cout<<h[ans]*h[((1<<n)-1)^ans]<<"\n";
    }
    return 0;
}
```

---

## 作者：Werner_Yin (赞：5)

　　[欢迎到博客中阅读](https://www.cnblogs.com/werner-yin/p/15953779.html)


　　感觉是这次 USACO Gold 里面最有意思也是最难的题目，不过还好，在这个题上花了 $1.5$ 小时终于 AK 晋级了。

　　不难想出 $\mathcal O(3^nn^2)$ 的暴力：

> 对于每个集合 $s$，预处理出钦定这些奶牛同色的方案数 $g(s)$，设 $U$ 代表全集，那么每次的答案就是两种颜色的奶牛的方案的拼接： $g(s)g(U/s)$。
>
> $g(s)$ 可以通过记 $f(s, lst)$ 表示当前被占用的物品的集合为 $s$，然后上一个物品为 $lst$ 的方案数得出。
>
> 复杂度就是所有状态的子集个数 $\times$ $n^2$。
>

　　然后我们发现这中每次枚举一个集合 $s$，然后跑一遍比较浪费，同时又注意到假如我们对于每个 $i$，假设它选了物品 $p_i$，那么就连一条边 $(i, p_i)$，然后我们发现我们每次枚举 $s$，实际上就是将整个集合划分成若干个置换环，于是我们可以先求出 $g(s)$ 表示将 $s$ 连成一个置换环的方案数，$h(s)$ 表示将 $s$ 分成若干置换环的方案数。

　　记 $x$ 为 $s$ 中的一个任意元素（我们枚举这个元素所在置换环的方案，方便起见，可以取 $\log_2 \mathrm{lowbit}(s)$），那么 $h(s)$ 的转移显然：

$$
h(s) = \sum_{s' \subseteq s, x \in s'} g(s') h(s / s')
$$

　　这个的复杂度就是 $3^n$，可以承受。

　　于是重点就是求解 $g(s)$。

　　第一眼，可以有一个略微暴力的想法，记 $f(s, st, ed)$ 表示当前 $s$ 这个集合中的物品已经被占用了，整个置换环的起始点是 $st$，目前上一个元素是 $ed$，每次转移的时候枚举下一个元素 $i$，然后只要 $i$ 没有被占用且 $ed$ 选 $i$ 合法后就可以转移了。特别地，如果 $i = st$，那么就形成环了，于是 $g(s \cup \{i\}) \gets g(s \cup \{i\}) + f(s, st, ed)$。

　　最后，每一个置换环都被算了环长遍，于是将 $g(s)$ 除以环长即可。

　　具体可以看代码：

```cpp
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = (1 << 16) + 10;

ll f[N][17][17], g[N], h[N];
int n, Q;
char s[20];
int p[20][20];
bool avi[20][20];
int lg[N];

int main() {
	n = in;
	rep(i, 0, n - 1) {
		rep(j, 0, n - 1) p[i][j] = in - 1;
		rep(j, 0, n - 1) {
			avi[i][p[i][j]] = true;
			if(p[i][j] == i) break;
		}
	} int U = 1 << n; U--;
	rep(i, 0, n - 1) f[0][i][i] = 1;

	rep(s, 0, U)
		rep(st, 0, n - 1) if(~s >> st & 1)
		rep(ed, 0, n - 1) if(ed == st || s >> ed & 1) if(f[s][st][ed]) {
				rep(i, 0, n - 1)
					if(~s >> i & 1 && avi[ed][i]) {
						if(i == st) g[s | 1 << st] += f[s][st][ed];
						else f[s | 1 << i][st][i] += f[s][st][ed];
					}
			}

	rep(i, 2, U) lg[i] = lg[i >> 1] + 1; h[0] = 1;
	rep(s, 1, U) g[s] /= __builtin_popcount(s);
	rep(s, 1, U) {
		int x = lg[s & -s];
		for(int t = s; t; t = (t - 1) & s) if(t >> x & 1) 
			h[s] = h[s] + g[t] * h[s ^ t];
	} 
	Q = in; 
	while(Q--) {
		scanf("%s", s);
		int stu = 0; rep(i, 0, n - 1) if(s[i] == 'H') stu |= 1 << i;
		ll ans = h[stu] * h[U ^ stu];
		printf("%lld\n", ans);
	}
	return 0;
}
```

　　只要把这个代码交上去，就可以通过 $12 / 18$ 的测试点，瓶颈在于空间，如果要强行卡空间，应该可以通过 $n = 17$。

　　考虑继续优化，我们的瓶颈仍然在于 $f(s, st, ed)$ 上面，如果我们能够删除一维状态，那么就可以完美地通过所有测试点了！

　　$ed$ 是显然很必要的，但是 $st$，我们可以观察它在 DP 中的作用：

* 判断什么时候形成置换环。

　　感觉这个作用比较垃圾，于是我们可以钦定一个置换环中，编号最小的作为 $st$，然后只要我们枚举的 $i$ 是编号最小的点，那么就可以确定形成置换环了！

　　于是复杂度降为了 $\mathcal O(2^n n^2 + 3^n)$，USACO 评测机下，大概每个点 900ms 多。

```cpp
#include <bits/stdc++.h>

#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = (1 << 18) + 10;

ll f[N][19], g[N], h[N];
int n, Q;
char s[20];
int p[20][20];
bool avi[20][20];
int lg[N];

int main() {
	n = in;
	rep(i, 0, n - 1) {
		rep(j, 0, n - 1) p[i][j] = in - 1;
		rep(j, 0, n - 1) {
			avi[i][p[i][j]] = true;
			if(p[i][j] == i) break;
		}
	} int U = 1 << n; U--;
	rep(i, 0, n - 1) f[1 << i][i] = 1;
	rep(i, 2, U) lg[i] = lg[i >> 1] + 1;

	rep(s, 1, U)
		rep(ed, 0, n - 1) if(f[s][ed]) {
		int x = lg[s & -s];
		rep(i, x, n - 1) {
			if(i == x && avi[ed][i]) g[s] += f[s][ed];
			if(~s >> i & 1 && avi[ed][i])
				f[s | 1 << i][i] += f[s][ed];
		}
	}
	h[0] = 1; 
	rep(s, 1, U) {
		int x = lg[s & -s];
		for(int t = s; t; t = (t - 1) & s) if(t >> x & 1) 
			h[s] = h[s] + g[t] * h[s ^ t];
	} 
	Q = in; 
	while(Q--) {
		scanf("%s", s);
		int stu = 0; rep(i, 0, n - 1) if(s[i] == 'H') stu |= 1 << i;
		ll ans = h[stu] * h[U ^ stu];
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：N2MENT (赞：4)

模拟赛题，挺简单的。

知周所众，$n\leq 18$ 大概率是状压（雾）。

首先发现实际上题目的很大一部分都没有用，实际上是在求：

求排列 $b$，每个位置 $i$，限制只能放 $L_i$ 中的数。设 $F(S)$ 表示对于下标集合 $S$，只考虑 $i \in S$ 的位置，$i\in S, b_i\in S,b_i\in L_i$ 的方案数。则答案为 $F(S) \cdot F(\complement_{[1,n]\cap \mathbb{Z}} S )$。

但是直接算 $F$ 有点难，怎么办，注意到合并下标集合 $S$ 和 $\{x\}$ 的答案时，我们可以做两件事情：

- 可以让 $b_x = x$，这样一定合法；

- 在第一种方案的基础上，找到一个数 $y\in S,b_y\in L_x,x\in L_y$，可以进行一次“交换”操作，交换 $b_x$ 和 $b_y$。这样也一定是合法的。

于是可以设计一种状态 $f_{S,x}$ 表示只考虑下标 $i\in S$ 的位置，钦定下标最小位置上 $b_i=x$ 且**这个位置不需要考虑 $x \in L_i$ 的限制**的方案数。 

考虑转移，计算 $S$ 时，枚举要把哪个数 $x$ 放在下标最小的位置上，然后让 $x$ 和最低位进行一次交换即可。

复杂度 $O(2^n n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr inline int bit(const unsigned &x) {
	return 1 << x;
}
constexpr inline int dig(const int &x, const unsigned &k) {
	return (x >> k) & 1;
}
int a[20];
int pos[20];
int ac[20];
ll f[bit(20)][20];
ll g[bit(20)];
int n, q;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[j];
			pos[a[j]] = j;
		}
		for(int j = 1; j <= n; j++) {
			if(pos[j] <= pos[i])
			 	ac[i] |= bit(j - 1);
		}
	}
	g[0] = 1;
	for(int i = 1; i <= n; i++) {
		g[bit(i - 1)] = f[bit(i - 1)][i] = 1;
	}
	for(int S = 1; S < bit(n); S++) {
		if(__builtin_popcount(S) <= 1) continue;
		int cur = __builtin_ctz(S) + 1;
		ll del = g[S ^ bit(cur - 1)];
		f[S][cur] += del;
		g[S] += del;
		for(int i = cur + 1; i <= n; i++) {
			if(!(S & bit(i - 1))) continue;
			int can = ac[i] & (S ^ bit(i - 1));
			for(int j = 1; j <= n; j++) {
				if(!dig(can, j - 1)) continue;
				ll del = f[S ^ bit(i - 1)][j];
				f[S][i] += del;
				if(dig(ac[cur], i - 1)) g[S] += del;
			}
		}
	}
	cin >> q;
	for(int i = 1; i <= q; i++) {
		char s[20];
		cin >> s;
		int S = 0;
		for(int j = 1; j <= n; j++) {
			if(s[j - 1] == 'H') S |=  bit(j - 1);
		}
		cout << (g[S] * g[(bit(n) - 1) ^ S]) << '\n';
	}
}
```

---

## 作者：pengyule (赞：3)

最暴力的：设 $f(s,t)$ 表示奶牛集合为 $s$，礼物集合为 $t$，选法方案数。每次枚举 $\text{lowbit}$ 的奶牛配对转移，$O(4^n)$。

发现反正是顺次给奶牛分配礼物，所以不必大费周章用 bitmask 记录奶牛状态；并且考虑对于所有 $2^n$ 个子集 $\mathfrak S$ 整个算一次 $ans_{\mathfrak S}$ 表示 G 型牛的位置状态为 $\mathfrak S$ 时的答案（两种牛没有本质不同所以最后 $ans_{\mathfrak S_{\tt G}}\cdot ans_{\mathfrak S_{\tt H}}$ 就是答案）：设 $f(i,t)$ 表示考虑了 $p_1,p_2,...,p_i$ 的牛，可供选择的礼物集合为 $t$ 的方案数；其中 $p_1,...,p_{|\mathfrak S|}$ 表示该询问中为 G 的位置的编号。每次考虑给 $p_i$ 分配的礼物转移。单次询问复杂度 $O(|\mathfrak S|2^{|\mathfrak S|})$。  
对于这一部分的总复杂度分析：
$$O\left(\sum_{\mathfrak S}|\mathfrak S|2^{|\mathfrak S|}\right)\le O\left( n\sum_{\mathfrak S} 2^{|\mathfrak S|}\right)=O(n3^n)$$

考虑最开始的暴力的做法，显然，礼物集合的大小等于奶牛集合的大小才有意义，然后这种情况下，奶牛和礼物是配对出现的，对于关联性如此之强的两个集合，我们却用了二次方来存，直觉告诉我们这是冗余的。

考虑将奶牛和礼物之间的关联具体化，可通过建立有向边 $\mathrm {cow\to gift}$ 的方式。$n$ 点 $n$ 边，这是一个由若干个有向环构成的图，则可以次第加点，考虑是加入上次环的开口还是闭上上次环并新开一个环起点接口。

设 $f(s,las)$ 表示所加点集为 $s$，最后加的点为 $las$，有标号图形态的方案数。枚举下一个要加的点进行转移，会发现这样子，一方面，每个环都可以任意一点作为起点了，从而有多重表示方法，产生错误，另一方面，不同环之间的顺序随意了，也产生错误。这是一个让我们去重的问题，考虑钦定，钦定每个环的起点必须是环中最大点，钦定按照环中最大点递增的顺序依次考虑各个环。  
这样，每次枚举下一个要加的点 $j$，并记当前 $s$ 的 $\text{highbit}$ 为 $v$（也即当前正在考虑的环的最大点）：
- $j<v$，表示添加 $las\to j$ 的边，转移到 $f(s\oplus 2^j,j)$
- $j=v$，表示添加 $las\to v$ 的边，将环关闭，不做转移，而将 $ans_s\gets ans_s+f(s,las)$
- $j>v$，表示添加 $las\to v$ 的边，将环关闭，并新开一环，转移到 $f(s\oplus 2^j,j)$

当然了，转移前还要判断所加的边是否满足题目中的配对要求。

至此，我们用 $O(n^22^n+nq)$ 的复杂度解决了问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,q,rk[20][20],aa[1<<18];
ll f[1<<18][20],ans[1<<18];
char str[20];
inline int ppc(int x){int cnt=0;while(x)cnt++,x-=x&-x;return cnt;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1,tmp;j<=n;j++){
			scanf("%d",&tmp);
			rk[i-1][tmp-1]=j;
		}
	}
	for(int i=1,j=0;i<(1<<n);i<<=1,j++)aa[i]=j;
	ans[0]=1;
	for(int s=1;s<(1<<n);s++){
		if(ppc(s)==1)f[s][aa[s]]=ans[s]=1;
		int v;
		for(int j=n-1;~j;j--)if(s>>j&1){v=j;break;}
		for(int las=0;las<n;las++)if(s>>las&1){
			for(int j=0;j<v;j++)if(!(s>>j&1)&&rk[las][j]<=rk[las][las]){
				f[s^(1<<j)][j]+=f[s][las];
			}
			if(rk[las][v]<=rk[las][las]&&ppc(s)>1)ans[s]+=f[s][las];
			for(int j=v+1;j<n;j++)if(!(s>>j&1)&&rk[las][v]<=rk[las][las]){
				f[s^(1<<j)][j]+=f[s][las];
			}
		}
	}
	scanf("%d",&q);
	while(q--){
		scanf("%s",str);
		int st1=0,st2=0;
		for(int i=0;i<n;i++)if(str[i]=='H')st1|=1<<i;else st2|=1<<i;
		printf("%lld\n",ans[st1]*ans[st2]);
	}
}
```

---

## 作者：Purslane (赞：2)

# Solution

省选前一晚上没啥事干，随便写写题解吧。

显然最终的结构是若干置换环。

所以我们可以这样设计状压 DP：设 $dp_{S,s,t}$ 为，使用 $S$ 种的点，能拼成多少种合法的、$s \to t$ 的链。判断 $(t,s)$ 能否连边贡献到 $f_S$ 表示将 $S$ 变成一个环的方案数，然后使用子集卷积（集合幂级数的 $\exp$）得到 $g_S$ 表示使用 $S$ 种的点的答案，复杂度 $O(n^2 2^n)$。

但是这样做挺魔怔的。首先，我们可以不记录 $s$——钦定 $s$ 为 $S$ 中的最小值即可；其次，如果已经拼成了若干个环，我们不需要记录其他的环是怎么处理的。也就是说，我们只需要记录 $dp_{S,t}$ 表示，将 $S$ 中的点搞成若干个环，以及一条 $\min(S) \to t$ 的链的方案数。

那么很容易做到 $O(n^2 2^n)$，但是变得特别好写。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20,MAXM=(1<<18)+10;
int n,q,ok[MAXN][MAXN],res[MAXM],dp[MAXM][MAXN],lb[MAXM];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		int tmp=1;
		ffor(j,1,n) {int id;cin>>id,ok[i][id]=tmp,tmp&=(id!=i);}
	}
	res[0]=1;
	ffor(i,1,n) dp[(1<<i-1)][i]=1,lb[(1<<i-1)]=i;
	ffor(i,1,(1<<n)-1) {
		int s=lb[i&-i];
		ffor(t,s,n) if(ok[s][t]) res[i]+=dp[i][t];
		ffor(t,1,s-1) dp[i+(1<<t-1)][t]+=res[i]; 
		ffor(l,s,n) ffor(t,s+1,n) if(!(i&(1<<t-1))&&ok[t][l]) dp[i+(1<<t-1)][t]+=dp[i][l];
	}
	cin>>q;
	ffor(i,1,q) {
		string S;
		cin>>S;
		int o=0,oo=0;
		ffor(j,1,n) if(S[j-1]=='G') o+=(1<<j-1); else oo+=(1<<j-1);	
		cout<<res[o]*res[oo]<<'\n';
	}
	return 0;
}
```

---

## 作者：Union_of_Britain (赞：0)

写一篇子集卷积 exp 的题解（虽然好像那种方法是更简单的 exp。。）。

如果 $i$ 奶牛对 $j$ 物品的喜欢值低于 $i$ 物品的，那么连边 $i\to j$。考虑置换分解为循环，就是求原图的环划分方案数。

先 dp 求出环的方案数 $g_S$。然后求出 $f=\exp g$（这是 exp 的组合意义；并且 exp 的阶乘是去除无交并的顺序而非 EGF 的重分配标号，所以无需把集合幂级数乘上 $\frac{1}{n!}$ 系数），最后把给出的集合两部分答案相乘即可。

比较麻烦的一点是 exp 过程中会产生分数，而这道题还不是求模意义下的答案，并且答案还比较大（$>2\times 10^9$），所以还得用两个模数 CRT 合并一下答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[19][19],n,p[19],ip[19];
int qp(int a,int b,int mod){
	if(b==0)return 1;
	int T=qp(a,b>>1,mod);T=T*T%mod;
	if(b&1)return a*T%mod;
	return T;
}
struct solver{
	int mod;
	int f[19][(1<<18)+5],g[19][(1<<18)+5],h[19][(1<<18)+5];
	int c[2][2],ic[2][2];
	void fwt(int a[],int tp){
		for(int mid=1;mid<(1<<n);mid<<=1){
			for(int j=0;j<(1<<n);j+=(mid<<1)){
				for(int k=0;k<mid;k++){
					if(tp==1)a[j+k+mid]+=a[j+k];
					else a[j+k+mid]+=mod-a[j+k];
					if(a[j+k+mid]>=mod)a[j+k+mid]-=mod;
				}
			}
		}
	}
	int cur[(1<<18)+5],inv[20],t[(1<<18)+5];
	void Exp(){
		for(int i=0;i<=n;i++)for(int j=0;j<(1<<n);j++)g[i][j]=g[i][j]*i%mod;
		for(int i=0;i<=n;i++){
			if(i)for(int j=0;j<(1<<n);j++)h[i][j]=h[i][j]*inv[i]%mod;
			else for(int j=0;j<(1<<n);j++)h[i][j]=1;
			for(int j=0;j<=n-i;j++)for(int k=0;k<(1<<n);k++)if(g[j][k])(h[i+j][k]+=h[i][k]*g[j][k])%=mod;
		}
	}
	void predo(){
		c[0][0]=1,c[0][1]=0,c[1][0]=1,c[1][1]=1;
		ic[0][0]=1,ic[0][1]=0,ic[1][0]=mod-1,ic[1][1]=1;
		for(int i=1;i<=n;i++)f[i][(1<<i-1)]=1,inv[i]=qp(i,mod-2,mod);
		for(int S=1;S<(1<<n);S++){
			for(int j=1;j<=n;j++){
				if(!f[j][S])continue;
				int p=__lg(S&(-S))+1;
				for(int k=p;k<=n;k++){
					if(a[j][k]&&p==k)g[__builtin_popcount(S)][S]+=f[j][S];
					if(a[j][k]&&!(S&(1<<k-1)))(f[k][S|(1<<k-1)]+=f[j][S]);
				}
			}
		}
		for(int i=1;i<=n;i++)fwt(g[i],1);
		Exp();
		for(int j=0;j<=n;j++)fwt(h[j],-1);
	}
	int getans(string s){
		int S=0,U=(1<<n)-1;
		for(int i=0;i<n;i++)if(s[i]=='H')S+=(1<<i);
		int L=__builtin_popcount(S);
		return h[L][S]*h[n-L][U-S]%mod;
	}
}T1,T2;
#define Int __int128
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)cin>>ip[j];
		for(int j=1;j<=n;j++)p[ip[j]]=j;
		for(int j=1;j<=n;j++)if(p[j]<=p[i])a[i][j]=1;
	}
	T1.mod=998244353,T2.mod=1e9+7;
	T1.predo(),T2.predo();
	int q;cin>>q;
	Int Mod=T1.mod*T2.mod;
	Int K1=T2.mod*qp(T2.mod,T1.mod-2,T1.mod),K2=T1.mod*qp(T1.mod,T2.mod-2,T2.mod);
	while(q--){
		string s;cin>>s;
		int r1=T1.getans(s),r2=T2.getans(s);
		Int ans=(K1*r1%Mod+K2*r2%Mod)%Mod;
		int Ans=ans;
		cout<<Ans<<"\n";
	}
	return 0;
}

```

---

