# [JOIST 2023] 曲奇 / Cookies

## 题目描述

莉婕喜欢做饼干。她制作了 $N$ 种饼干。第 $i$ 种饼干有 $A_i$ 个。为了出售她制作的饼干，她将它们装入盒子中。但是，应该满足以下条件。

+ 对于每个盒子，其中的饼干种类应不同。

+ 对于每个盒子，其中的饼干数量应等于以下 $M$ 个数字之一：$B_1,B_2,⋯ ,B_M$。

编写一个程序，给出莉婕制作的饼干信息和将饼干装箱的条件，确定是否可能将所有饼干包装到盒子中。此外，如果可以将所有饼干包装在盒子中，则您的程序应输出最少的盒子数量。

## 说明/提示

#### 【样例解释 #1】

对于该样例输入，可以按照以下方式将 $7$ 个饼干装入 $3$ 个盒子中满足条件：

+ 将第 $1$ 类和第 $7$ 类的饼干装入第一个盒子中。每种类型放 $1$ 个。
+ 将第 $2$ 类和第 $6$ 类的饼干装入第二个盒子中。每种类型放 $1$ 个。
+ 将第 $3$ 类、第 $4$ 类和第 $5$ 类的饼干装入第三个盒子中。每种类型放 $1$ 个。

因为不能用少于或等于 $2$ 个盒子来包装 $7$ 个饼干，所以以上方法是正确的。判断为正确答案。还有其他正确方法。

**【数据范围】**

对于所有测试数据，满足 $1 \leq N \leq 15 000$，$A _ i \geq 1$（$1 \leq i \leq n$），$A _ 1 + A _ 2 + \cdots + A _ N \leq 15 000$，$1 \leq M \leq N$，$1 \leq B _ j \leq N$（$1 \leq j \leq M$），$B _ j < B _ {j + 1}$（$1 \leq j \leq M - 1$），保证所有输入均为整数。

| **子任务编号** | **分值** | **限制** |
| :----------: | :----------: | :----------: |
| $1$ | $6$ | $N \leq 500$，$A _ i = 1$（$1 \leq i \leq N$） |
| $2$ | $7$ | $N \leq 500$，$M = 1$ |
| $3$ | $12$ | $A _ 1 + A _ 2 + \cdots + A _ N \leq 15$ |
| $4$ | $45$ | $A _ 1 + A _ 2 + \cdots + A _ N \leq 500$ |
| $5$ | $15$ | $A _ 1 + A _ 2 + \cdots + A _ N \leq 3000$ |
| $6$ | $15$ | 没有额外的限制 |

Translate by @[ZeXic_B](https://www.luogu.com.cn/user/661274)

## 样例 #1

### 输入

```
7
1 1 1 1 1 1 1
3
1 2 3```

### 输出

```
3
2 1 7
2 2 6
3 3 4 5```

## 样例 #2

### 输入

```
5
5 3 1 2 4
1
4```

### 输出

```
-1```

## 样例 #3

### 输入

```
7
5 4 4 2 1 1 1
2
2 6```

### 输出

```
7
6 1 2 3 4 5 6
2 2 1
2 3 1
2 4 1
2 7 1
2 3 2
2 3 2```

# 题解

## 作者：ღꦿ࿐ (赞：10)

upd:2023/9/20 补充了基于霍尔婚配定理的证明。

首先观察前面两档部分分，很显然——第一档直接背包，第二档给我们一个思想就是基于桶去找饼干，直接贪心地选数量尽可能多的饼干种类就行，正确性显然。

也就是说我们找到一组确定的尽可能少的桶后直接贪心地选择饼干就行了。

接下来问题是 如何找到一组合法的桶。

最大的桶 $C_1$ 需要被所有不同的饼干装满，需要 至少有 $C_1$ 种不同的饼干。

次大的桶 $C_2$ 需要被所有不同的饼干装满，需要在装满 $C_1$ 后至少有 $C_2$ 种不同的饼干，而有两块或更多的饼干可以同时用于装两个桶。

再次大的桶 $C_3$ 需要被所有不同的饼干装满，需要在装满 $C_1,C_2$ 后至少有 $C_3$ 种不同的饼干，而有两块的饼干可以同时用于装两个桶，有三块或更多的饼干可以拿来同时装三个桶。

……

$$
\sum_{i=1}^j C_i\leq\sum \min\{a_i,j\}
$$

这个条件显然是必要的。其充分性可以归纳证明，也可以使用霍尔定理证明：

构造一个二分图，每个左部点是桶，右边是饼干，每个左部点向右边连一条容量为 $1$ 的边，使用霍尔定理，对于集合 $S$ 能匹配 $f(S)=\sum \min\{a_i,j\}$，右侧的 $a_i$ 每个就可以匹配不超过 $k$ 个，所以 $f(S)$ 的大小只和 $|S|$ 相关，所以对于每个 $k$，选择前 $k$ 大的 $C_i$ 作为 $S$ 中的左部点，那么就有了上面的式子。

取上界 $\sum_{i=1}^j C_i=cir_i$。

现在就变成了，从大到小选 尽可能少的桶，使得前 $i$ 大的和不超过 $cir_i$，且和为 $n$。

首先有 $n^3$ 的 dp，让 $f_{i,j,k}$ 表示前 $i$ 大的桶，目前选了 $j$ 个，和为 $k$ 是否可行。

转移就枚举这个桶是否选，个数从小到大做完全背包即可。

考虑优化，因为是前 $j$ 大的桶，所以  $ siz_i \times j \leq \sum_{x_\leq j} C_x \leq m$，故有 $siz_i \times j \leq m$，所以第二维只用开到 $\frac m {siz_i}$，复杂度是调和级数 $O(n^2\log n)$。

注意到 dp 值是 boolean 的，所以可以压位，时空均为 $O(\frac {n^2\log n}w)$，空间约 400M 可以通过。


代码
```cpp
/*
君は瞬きと共に過ぎてく時間も
遠くから見てると微笑んで
 */
/*author::ღꦿ࿐(DeepSea.) */
const int N = 15002 ;
int n , a[N + 10] , b[N + 10] , m;
int cir[N + 10] ;
int val[N + 10] ;
int cnt[N + 10] , sum[N + 10] ; 
using state = bitset<N + 2>;
vector < state > dp[N + 2] ;
bitset<N + 2> px[N + 2];
vi C;
void go(int i,int j,int s) {
    if(i == 1) {
        C.emplace_back(j) ;
        return ;
    }
    for(int pre = 1 ; pre <= m && b[pre] * (i - 1) <= N ; ++ pre) {
        if(b[pre] >= j && dp[i - 1][b[pre]][s - j]) {go(i - 1,b[pre],s - j) ; C.emplace_back(j); return ;}   
    }
}
signed main()
{
    read(n) ;
    rep(i,1,n) read(a[i]) , cnt[a[i] + 1] ++ , sum[a[i] + 1] += a[i]; 
    read(m);
    rep(i,1,m) read(b[i]);
    int c = n , s = 0;
    rep(i,1,N) {
        c -= cnt[i] ;
        s += sum[i] ;
        cir[i] = c * i + s ;
    }
    rep(i,1,N) dp[i].resize(N / i + 2);
    rep(i,1,m) {
        if(b[i] <= cir[1]) dp[1][b[i]][b[i]] = 1 ;
    }
    px[0][0] = 1;
    rep(i,1,N) px[i] = px[i - 1] << 1 , px[i][0] = 1 ;
    int ptr = m ;
    rep(i,1,N - 1) {
        state s ;
        while(i * b[ptr] > N) ptr -- ;
        for(int j = ptr ; j >= 1 ; -- j) {
            s |= dp[i][b[j]] ; 
            if((i + 1) * b[j] <= N) {
                dp[i + 1][b[j]] |= s << b[j] ;
                dp[i + 1][b[j]] &= px[cir[i + 1]];
            } 
        }
    }

    rep(i,1,N) {
        for(int j = 1 ; j <= m && b[j] * i <= N ; ++ j) {
            if(dp[i][b[j]][s]) {
                go(i,b[j],s); 
                goto Construct;
            }
        }
    }       

    puts("-1") ;
    exit(0) ;

    Construct:{
        priority_queue< pi > h ;
        vector<vi> ans;
        rep(i,1,n) h.emplace(a[i] , i);
        for(int p:C) {
            vector< pi > tmp ;
            vi ths;
            while(p -- ) {
                auto [c,num] = h.top( ) ;h.pop( );
                if(c > 1) tmp.emplace_back(c - 1 , num);
                ths.emplace_back(num) ;
            }
            ans.emplace_back(ths);
            for(auto x:tmp) h.push(x);
        }
        wrt( C.size( ) , '\n');
        for(auto vec:ans) {
            wrt(vec.size( ) , ' ');
            wrt(vec, ' ') ;
            nxtl;
        }
        exit(0) ; 
    }

    return 0;   
}
```





---

## 作者：Leasier (赞：5)

设 $cnt_i$ 表示我们最终选的第 $i$ 个盒子的容量为 $cnt_i$，考虑如何判断一组 $cnt_i$ 是否合法：

- “饼干匹配盒子”让我们想到**二分图匹配**。
- 左部点 $i$ 表示第 $i$ 种饼干，右部点 $i'$ 表示第 $i$ 种盒子。
- 连边 $S \to^{a_i} i$，表示第 $i$ 种饼干有 $a_i$ 个。
- 连边 $i' \to^{cnt_i} T$，表示第 $i$ 个盒子的容量为 $cnt_i$。
- 连边 $i \to^1 j$，表示把饼干放入盒子。
- 若 $\displaystyle\sum_{i = 1}^n a_i = \sum_i cnt_i$ 且存在完美匹配，则合法。

考虑写出 Hall 定理：

- 枚举右部点的子集 $S$，有 $\displaystyle\sum_{i \in S} cnt_i \leq \sum_i \min(a_i, |S|)$。

不难发现最紧的限制在 $S$ 为 $cnt_i$ 的前 $|S|$ 大时取到，于是不难 bitset 优化背包求出一组合法的 $cnt_i$。

最后贪心构造方案即可。时间复杂度为 $O(\frac{(\sum a_i)^2 \log \sum a_i}{w})$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

int a[15007], suf[15007], val[15007], b[15007], ansc[15007];
pair<int, int> save[15007];
priority_queue<pair<int, int> > q;
bitset<15007> temp, bs[15007];
vector<bitset<15007> > v[15007];

int main(){
	int n, max_val = 0, sum = 0, m, ansx = -1;
	cin >> n;
	for (register int i = 1; i <= n; i++){
		cin >> a[i];
		suf[a[i]]++;
		max_val = max(max_val, a[i]);
		sum += a[i];
	}
	for (register int i = max_val; i >= 1; i--){
		suf[i] += suf[i + 1];
	}
	for (register int i = 1; i <= max_val; i++){
		val[i] = val[i - 1] + suf[i];
	}
	for (register int i = max_val + 1; i <= sum; i++){
		val[i] = sum;
	}
	bs[0][0] = true;
	for (register int i = 1; i <= sum; i++){
		bs[i] = bs[i - 1];
		for (register int j = val[i - 1] + 1; j <= val[i]; j++){
			bs[i][j] = true;
		}
	}
	cin >> m;
	for (register int i = 1; i <= m; i++){
		cin >> b[i];
	}
	v[m + 1].resize(1);
	v[m + 1][0][0] = true;
	for (register int i = m; i >= 1; i--){
		int size = v[i + 1].size();
		v[i].resize(sum / b[i] + 1);
		for (register int j = 0; b[i] * j <= sum; j++){
			if (j < size) v[i][j] = v[i + 1][j];
			if (j > 0){
				temp = v[i][j - 1];
				temp <<= b[i];
				v[i][j] |= temp;
			}
			v[i][j] &= bs[j];
		}
	}
	for (register int i = 0; i * b[1] <= sum; i++){
		if (v[1][i][sum]){
			ansx = i;
			break;
		}
	}
	if (ansx == -1){
		cout << -1;
		return 0;
	}
	cout << ansx << endl;
	for (register int i = ansx, j = sum, k = 1; i >= 1; i--, j -= b[k]){
		while (!v[k][i][j] || !v[k][i - 1][j - b[k]]) k++;
		ansc[i] = b[k];
	}
	for (register int i = 1; i <= n; i++){
		q.push(make_pair(a[i], i));
	}
	for (register int i = 1; i <= ansx; i++){
		cout << ansc[i] << " ";
		for (register int j = 1; j <= ansc[i]; j++){
			save[j] = q.top();
			q.pop();
			cout << save[j].second << " ";
		}
		cout << endl;
		for (register int j = 1; j <= ansc[i]; j++){
			if (--save[j].first > 0) q.push(save[j]);
		}
	}
	return 0;
}
```

---

## 作者：Twig_K (赞：4)

[cnblogs](https://www.cnblogs.com/wanggk/p/-/CF1740F)

### 题意

有 $K$ 种颜色的球，第 $i$ 种颜色的球有 $A_i$ 个。另外给定一个集合 $B$，里面有 $M$ 个数 $B_1,B_2,\cdots,B_M$。

现在要把球堆成若干堆，要求：

- 每堆不能有重复颜色；
- 每堆的大小是 $B_1,B_2,\cdots,B_M$ 中的一个数。

请你最小化堆数，并输出方案。

### 题解

设最终有 $n$ 堆，高度为 $H_1,H_2,\cdots,H_n$。交换堆的顺序肯定是没有影响的，为了方便，对于下文（包括后文移动完之后），**我们不妨设 $H$ 不增**。

考虑如何判定这样一个序列合法。这也是我们得出答案序列后，求颜色方案的方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/o0gspj18.png)

我们要求每一堆没有相同颜色，那么按照**出现次数**从大到小加入颜色。

对于每种颜色，从左往右，将离目标高度 $H_i$ 最远的堆叠高一层。因为是优先叠那些最拖后腿的堆，这样的贪心是最优的。如果高度序列可能被达到，那么该最终状态合法。

因为我们是贪心地向上叠（先消耗出现次数多的颜色，先消耗比较高的堆，最可能合法），所以我们发现，**对于一个合法局面，把前面堆的元素移到后面，也一定是合法的，如下图。**

![](https://cdn.luogu.com.cn/upload/image_hosting/obvsh710.png)

这是很好理解的，因为“拖后腿”的堆变矮了，颜色不重复的限制就变松了。

于是我们只需要**限制最紧（找到前面的堆最多）的合法状态，再统计不超过这个的局面数量**，就可以了。这个非常简单，只需要所有颜色都放一个前缀：

![](https://cdn.luogu.com.cn/upload/image_hosting/74vp1urh.png)

我们得到了尽可能最靠前放的序列，记其前缀和为 $Sum$（如图），合法序列 $H_n$ 一定满足：

- 单调不增排序后，$\forall i \in [1,n],\sum_{j \leq i} \leq Sum_i$

最小堆数看起来不是很好转移，那就设计一个可行性 DP：设 $f_{i,j,k}$ 表示，考虑完了前 $i$ 大的高度，用了 $j$ 堆，目前前缀和为 $k$，是否可行。转移有两种，继承前一层 $i-1$ 的值，和在本层中拿一个（相当于完全背包）：

$$f_{i,j,k} \leftarrow f_{i-1,j,k} \vee f_{i,j-1,k-B_i} (k \leq Sum_j)$$

括号内表示转移条件，另外我们已经将 $B$ 降序排序，即 $B_1 > B_2> \cdots > B_n$。

同时由于前缀和不超过 $k$，则 $j \leq \frac{k}{B_i}$，所以 $j$ 是 $\log$ 级别的，再用 `bitset` 优化可行性 DP（优化完全背包的部分），复杂度就降到了 $O(\frac{n^2 \log n}{w})$，就可以通过了。

### 代码

看起来挺可读的。

```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(int i=(il);i<=(ir);++i)
#define Rof(i,ir,il) for(int i=(ir);i>=(il);--i)
using namespace std;
typedef pair<int,int> pii;
const int maxn=15005;

int n,m,V;
int a[maxn],b[maxn],sum[maxn];

bitset<maxn> pw[maxn];
vector<bitset<maxn> > f[maxn];

void prework()
{
    scanf("%d",&n);
    For(i,1,n){
        scanf("%d",&a[i]); V+=a[i];
        For(j,1,a[i]) sum[j]++;
    }
    pw[0].set(0);
    For(i,1,V){
        sum[i]+=sum[i-1];
        pw[i]=pw[i-1]<<1,pw[i].set(0);
    }
    scanf("%d",&m);
    For(i,1,m) scanf("%d",&b[i]);
    reverse(b+1,b+1+m);
}

int res[maxn];
vector<int> sol[maxn];
void dfs(int i,int j,int k){
    if(!i||!j||!k) return;
    if(k>=b[i] && f[i][j-1][k-b[i]]) res[j]=b[i],dfs(i,j-1,k-b[i]);
    else dfs(i-1,j,k);
}
signed main()
{
    prework();
    bitset<maxn> tmp; tmp.set(0);
    f[0].push_back(tmp),b[0]=V+1;
    For(i,1,m) For(j,0,V/b[i])
    {
        bitset<maxn> dp;
        if(j) dp|=(f[i][j-1]<<b[i]);
        if(b[i-1]*j<=V) dp|=f[i-1][j];
        dp&=pw[sum[j]];
        f[i].push_back(dp);
    }
    
    int ans=-1;
    For(j,0,V/b[m]) if(f[m][j][V]){ ans=j; break; }
    printf("%d\n",ans);
    if(ans==-1) return 0;
    else dfs(m,ans,V);

    priority_queue<pii> q,q2;
    For(i,1,n) q.push(make_pair(a[i],i));
    For(i,1,ans)
    {
        printf("%d ",res[i]);
        while(res[i]--){
            pii x=q.top(); q.pop();
            printf("%d ",x.second);
            if(--x.first); q2.push(x);
        }printf("\n");
        while(!q2.empty()) q.push(q2.top()),q2.pop();
    }
    return 0;
}
```

---

## 作者：Nangu (赞：2)

考虑子任务 2，有一个贪心：我们每次都选择 $a_i$ 最大的 $b_1$ 个数输出，并把这些 $a_i$ 减去 $1$。

为什么这样是对的呢？如果我们挑了 $a_i$ 更小的数，那么就有可能让后面几次操作后提前让 $a_i=0$，那么可操作的种类就会减少，有可能就构造不出方案了。

由此，对于一种方案序列 $c_x$，把 $a_i$ 丢进堆贪心即可求得最后答案。

于是我们转而思考怎样的 $c_x$ 是合法的。

考虑霍尔婚配定理：任意取 $j$ 个 $c$ 中的元素，设这个集合为 $b$，则其邻域即为 $\sum \min(a_i, j)$，这个数必须大于 $\sum b_i$。

这个条件即是充要的，然后就可以愉快的 dp 啦。

代码：
```cpp
#include<bits/stdc++.h>
#define rep(i, j, k) for(int i=(j); i<=(k); ++i)
#define per(i, j, k) for(int i=(j); i>=(k); --i)
#define aprint(a, len) cout<<#a<<"="; rep(i, 0, len-1) cout<<(a)[i]<<' '; cout<<endl
using namespace std;
namespace DEBUG{
  template<class T> void _debug(const char *s, T x) {cout<<s<<'='<<x<<endl;}
  template<class F, class... Nxt> void _debug(const char *s, F x, Nxt... nxt){
  int d=0;
  while(*s!=',' || d) d+=*s=='(', d-=*s==')', cout<<*s++;
    cout<<'='<<x<<',';
    _debug(s+1, nxt...);
  }
  #define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
} using namespace DEBUG;
const int N=1.5e4+3;
using pa=pair<int, int>;
using Bit=bitset<N>;
int n, maxn, a[N], m, b[N], lim[N], cnt[N], sum[N];
vector<Bit> f[N];
Bit pre[N];
vector<int> res;
priority_queue<pa> q;
vector<pa> buc;

void dfs(int i, int j, int k){
  if(!i) return;
  if(j<f[i-1].size() && f[i-1][j][k]) return dfs(i-1, j, k);
  if(f[i][j-1][k-b[i]]){
    res.emplace_back(b[i]);
    return dfs(i, j-1, k-b[i]);
  }
}

signed main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  rep(i, 1, n){
    cin>>a[i], maxn=max(maxn, a[i]);
    ++cnt[1], --cnt[a[i]], sum[a[i]]+=a[i];
  }
  rep(i, 1, maxn) cnt[i]+=cnt[i-1], sum[i]+=sum[i-1], lim[i]=cnt[i]*i+sum[i];
  rep(i, maxn+1, lim[maxn]) lim[i]=lim[maxn];
  cin>>m;
  rep(i, 1, m) cin>>b[i];
  reverse(b+1, b+m+1);  
  f[0].resize(1), f[0][0][0]=1;
  rep(i, 1, m) f[i].resize(lim[maxn]/b[i]+1);
  pre[0][0]=1;
  rep(i, 1, lim[maxn]) pre[i]=pre[i-1], pre[i][i]=1;
  rep(i, 1, m){
    f[i][0]=f[i-1][0];
    rep(j, 1, lim[maxn]/b[i]){
      f[i][j]=f[i][j-1]<<b[i];
      if(f[i-1].size()>j) f[i][j]|=f[i-1][j];
      f[i][j]&=pre[lim[j]];
    }
  }
  bool flag=1;
  rep(j, 1, lim[maxn]/b[m]) 
    if(f[m][j][lim[maxn]]){
      dfs(m, j, lim[maxn]);
      flag=0;
      break;
    }
  if(flag) return cout<<-1, 0;
  reverse(res.begin(), res.end());
  rep(i, 1, n) q.emplace(a[i], i);
  cout<<res.size()<<'\n';
  for(auto x:res){
    cout<<x<<' ';
    rep(_, 1, x){
      pa y=q.top(); q.pop();
      cout<<y.second<<' ';
      if(y.first) buc.emplace_back(pa(y.first-1, y.second));
    }
    cout<<'\n';
    for(auto x:buc) q.emplace(x);
    buc.clear();
  }
}

---

## 作者：Idtwtei (赞：1)

> 有 $n$ 种物品，每种物品有 $a_i$ 个，给你 $m$ 个数 $b_i$，你需要将物品分成尽可能少的组，使得
>
> * 每组物品的种类两两不同。
> * 每组物品的个数为 $b_i$ 之一。
>
> 若不可行输出 $-1$，否则给出最小的组数和方案。
>
> $1 \le n,m,\sum a\le 15000$，$1 \le b_i \le n$。

先考虑，给你每组物品的个数后，怎样构造方案。发现相当于二分图匹配，记第 $i$ 组有 $c_i$ 个物品，那么存在方案当且仅当 $\sum a_i = \sum c_i$ 且存在完美匹配。第一条限制是好满足的，对于第二条限制，考虑 hall 定理。

记物品的个数组为左部点，有结论，若任意左部点的子集 $S$，都有
$$
\sum_{i \in S} c_i \le \sum_{i \in N(S)} \min(|S|,a_i)
$$
那么存在左部点的完美匹配。

> **证明**
>
> 数学归纳法，记 $a_i$ 为右部点 $i$ 匹配后剩余的流量，对于左部点 $i$，选择前 $c_i$ 大的进行匹配，然后将 $i$ 删去。发现剩余的点仍满足上述限制。

若 $S \ne \emptyset$，那么 $N(S)=\{1,2,..,n\}$。从大到小依次选 $c_i$ 可使限制最紧。考虑 DP 求 $c$，将 $b$ 从大到小排序，记 $f_{i,j,k}$ 为考虑了前 $i$ 种个数，选择了 $j$ 组，总和为 $k$ 是否合法。转移就是完全背包。发现第二维需要 $\le \frac{\sum  a}{b_i}$，那么时空复杂度均为 $O(n^2\log n)$（需要求方案所以不能压第一维）。用 `bitset` 优化，时空复杂度均为 $O(\frac{n^2\log n}{\omega})$。

构造方案按证明构造即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define U(x) ((int)x.size())
#define pb push_back
const int N=15e3+10,INF=1e9;
#define gc getchar()
#define rd read()
inline int read(){
	int x=0,f=0; char c=gc;
	for(;c<'0'||c>'9';c=gc) f|=(c=='-');
	for(;c>='0'&&c<='9';c=gc) x=(x<<1)+(x<<3)+(c^48);
	return f?-x:x;
}

int n,m,sum=0,ans=-1,a[N],b[N],s[N],cnt[N],c[N];
vector<bitset<N>> f[N]; vector<int> vc; bitset<N> pre[N];
struct cmp{ bool operator()(int x,int y){ return a[x]<a[y]; } };
priority_queue<int,vector<int>,cmp> q;

int main(){

	n=rd; for(int i=1;i<=n;++i) sum+=(a[i]=rd),++s[1],--s[a[i]+1];
	for(int i=1;i<=sum;++i) s[i]+=s[i-1];
	for(int i=1;i<=sum;++i) s[i]+=s[i-1];
	m=rd; for(int i=1;i<=m;++i) b[i]=rd;
	sort(b+1,b+m+1,[&](int x,int y){ return x>y; });


	f[0].resize(1),f[0][0][0]=1;
	for(int i=0;i<=sum;++i) for(int j=0;j<=s[i];++j) pre[i][j]=1;
	for(int i=1,lim;i<=m;++i){
		lim=sum/b[i],f[i].resize(lim+1),f[i][0]=f[i-1][0];
		for(int j=0;j<=lim;++j){
			if(j<U(f[i-1])) f[i][j]=f[i-1][j];
			if(j>0) f[i][j]|=(f[i][j-1]<<b[i]);
			f[i][j]&=pre[j];
		}
	}
	for(int i=0;ans==-1&&i<=sum/b[m];++i) if(f[m][i][sum]==1) ans=i;

	if(ans==-1) return printf("-1\n"),0;

	for(int i=m,j=ans,k=sum;j;){
		for(;!f[i][j][k]||!f[i][j-1][k-b[i]];--i);
		c[j]=b[i],--j,k-=b[i];
	}

	printf("%d\n", ans);
	for(int i=1;i<=n;++i) q.push(i);
	for(int i=1;i<=ans;++i){
		printf("%d ", c[i]); vc={};
		for(int j=1;j<=c[i];++j){
			int u=q.top(); q.pop(),vc.pb(u);
			printf("%d ", u);
		}
		for(int v:vc) if(--a[v]) q.push(v);
		puts("");
	}

	return 0;
}
```

---

## 作者：KSCD_ (赞：1)

以下设 $\sum a_i=s$，同时认为 $n,m,s$ 同级。

首先发现盒子和饼干之间是类似匹配的关系，因此我们以盒子为左部点，每种饼干为右部点，连边即为完全二分图，代表每种饼干只能装到每个盒子中一个。题目所求即为最少的左部点数量使得该图有完美匹配，输出方案。

完美匹配考虑霍尔定理，首先要 $\sum b=\sum a$，然后要求对于所有左部点集合 $S$，都满足 $\sum_{i\in S}b_i\le\sum_{j=1}^n\min(a_j,\left|S\right|)$，这里要对 $a_j$ 取最小值是因为这种饼干最多只能贡献 $a_j$ 的出度。

我们注意到等式右边的取值只与集合大小有关，可以对 $a$ 排序后预处理固定集合大小下的上界 $c$。此时只要 $b$ 最大的若干个的和不超过上界，则更小的一定也不超过，必然合法。问题转化为在 $b$ 中可重复地选尽可能少的数，要求和为 $s$，同时保证前 $i$ 大之和不超过 $c_i$。

直接使用背包，先对 $b$ 排序，设 $f_{i,j,k}$ 表示考虑了前 $i$ 大的 $b$，选了 $j$ 个，总和为 $k$   是否可行，对所有 $k>c_j$ 的状态强制赋成 $0$ 即可保证限制，转移是完全背包，为 $f_{i,j,k}=f_{i-1,j,k} \vee f_{i,j-1,k-b_i}$，这样就是 $O(n^3)$ 的。

但是我们注意到在 $f_{i,j,k}$ 中使用的 $b$ 至少是 $b_i$，因此 $j\le \lfloor\frac s {b_i}\rfloor$。又因为 $b_i$ 两两不同，所以所有 $j$ 的个数和不超过 $O(n\ln n)$，复杂度降为 $O(n^2\ln n)$。又注意到 DP 值是 $0$ 或 $1$，同时 $f_{i,j}$ 只会从 $f_{i-1,j}$ 和 $f_{i,j-1}$ 在 $k$ 这一维以相同的偏移量转移，因此可以把 $f_{i,j}$ 在 $k$ 这一维的 $s$ 个状态压到 bitset 里优化转移，最终复杂度为 $O(\frac{n^2\ln n}w)$。

至于输出方案，先在 DP 数组上倒着把 $b$ 的方案找出来，然后每次贪心地把 $a$ 最大的若干种各放一个在该盒子里并减 $1$，用堆维护这个过程即可，具体看下面代码。值得一提的是，如果没有方案要求，上面的 DP 其实是可以滚动数组优化的。

~~~ c++
#include<iostream>
#include<algorithm>
#include<bitset>
#include<queue>
#define bs bitset <N>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=15000+10;
int n,m,s,r=-1,a[N],b[N],p[N],c[N],w[N];
bool cmpa(int x,int y) {return a[x]<a[y];}
bool cmp(int x,int y) {return x>y;}
bs lm[N];
vector <bs> f[N];
vector <pii> tv;
priority_queue <pii> q;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],s+=a[i],p[i]=i;
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(p+1,p+1+n,cmpa),sort(b+1,b+1+m,cmp);
	int tp=0,ts=0;
	for(int i=1;i<=s;i++)
	{
		while(tp<n&&a[p[tp+1]]<=i) tp++,ts+=a[p[tp]];
		c[i]=ts+(n-tp)*i;
	}
	b[0]=s+1,lm[0][0]=1;
	for(int i=1;i<=s;i++) lm[i]=lm[i-1],lm[i][i]=1;
	for(int i=0;i<=m;i++) f[i].resize(s/b[i]+1);
	f[0][0][0]=1;
	for(int i=1;i<=m;i++) for(int j=0;j<=s/b[i];j++)
	{
		if(j<=s/b[i-1]) f[i][j]=f[i-1][j];
		if(j) f[i][j]|=(f[i][j-1]<<b[i]);
		f[i][j]&=lm[c[j]];
	}
	for(int i=1;i<=s/b[m];i++) if(f[m][i][s]) {r=i; break;}
	cout<<r<<'\n';
	if(r==-1) return 0;
	int cur=s,tw=m;
	for(int i=1;i<=r;i++) for(int j=tw;j>=1;j--) 
		if(f[j][r-i+1][cur]&&f[j][r-i][cur-b[j]])
			{w[i]=b[j],cur-=b[j],tw=j; break;}
	for(int i=1;i<=n;i++) q.push({a[i],i});
	for(int i=1;i<=r;i++)
	{
		cout<<w[i]<<' ',tv.clear();
		for(int j=0;j<w[i];j++)
		{
			pii te=q.top(); q.pop();
			te.fi--,cout<<te.se<<' ';
			if(te.fi) tv.push_back(te);
		}
		for(pii te:tv) q.push(te);
		cout<<'\n';
	}
	return 0;
}
~~~

---

## 作者：_fairytale_ (赞：1)

先假装我们知道了盒子有 $k$ 个和对应的容量 $c_1\dots c_k$，建立一个类似网络流的二分图：对于第 $i$ 种饼干，建边 $S\xrightarrow{a_i}i$；对于第 $i$ 个盒子，建边 $i\xrightarrow{c_i}T$；每个饼干向每个盒子连容量为 $1$ 的边。

考虑 Hall 定理，有一种合法方案当且仅当 $\sum a=\sum c$ 并且对于每个盒子集合 $S$，$\sum_{i\in S}c_i\le \sum_{i=1}^n\min(a_i,|S|)$，这个取 $\min$ 是因为如果某个 $a_i>|S|$ 的话，这个点集大小是假的，根本不可能。

然后考虑某一个盒子集合 $S$，把 $S$ 中的所有数换成 $c$ 的前 $|S|$ 大变成 $S'$，显然 $S'$ 的限制是更强的，即如果 $S'$ 的限制被满足，那么 $S$ 就会被满足，因此在把盒子从大到小排序之后，我们只需满足这个序列每个前缀的限制。

于是转化为，找到存在满足条件的序列 $c$ 的最小长度 $k$：$c$ 中的元素递减，$c_i\in B$，对于 $c$ 的每个长 $j$ 的前缀，都要满足 $\sum_{i=1}^jc_i\le \sum_{i=1}^n\min(a_i,j)$，$\sum c=\sum a$。

把 $B$ 从大到小排序，设 $f_{i,j,k}$ 表示考虑 $B$ 中前 $i$ 个元素，已经选了 $j$ 个，$\sum c=k$ 是否可行。

$$\begin{cases}
f_{i,j,k}\to f_{i,j+1,k+b_i}\\
f_{i,j,k}\to f_{i+1,j,k}
\end{cases}$$

$j$ 那一维最多开到 $\dfrac{\sum a}{B_i}$，所以状态总数是调和级数，`bitset` 优化一下做到 $\mathcal O(\dfrac{n^2\log n}{w})$。

对于构造方案，首先找出所有箱子的容量 $c_1\dots c_k$，考虑从大往小删除然后归纳，每次让限制尽可能松，发现需要让 $\sum\min(a_i,j)$ 尽可能大，所以每次匹配一些最大的 $a$ 即可。

```cpp
#define maxn 15010
int n,m;
int a[maxn],b[maxn],c[maxn];
vector<bitset<maxn>>f[maxn];
int cf[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,1,n)cin>>a[i];
	rep(i,1,n)cf[a[i]+1]+=1;
	cin>>m;
	rep(i,1,m)cin>>b[i];
	int sum=accumulate(a+1,a+n+1,0);
	sort(b+1,b+m+1,greater<int>());
	f[0].resize(1);
	f[0][0][0]=1;
	int ans=inf;
	bitset<maxn>tmp;
	d(sum),ce;
	rep(i,1,m) {
		int lim=sum/b[i]+1;
		f[i].resize(lim+2);
		int lst=f[i-1].size();
		rep(j,0,lst-1)f[i][j]=f[i-1][j]; 
		int C=n,pre=0;
		tmp.reset();tmp[0]=1;
		auto &F=f[i];
		rep(j,0,lim) {
			C-=cf[j+1];
			rep(t,pre+1,pre+C)tmp[t]=1;
			pre+=C;
			F[j+1]|=(F[j]<<b[i]);
			F[j+1]&=tmp;
		}
		rep(j,0,lim+1)if(F[j][sum])ckmin(ans,j);
	}
	if(ans==inf){
		cout<<"-1\n";
		return 0;
	}
	cout<<ans<<'\n';
	per(i,m,1){
		if((int)f[i].size()>ans&&f[i][ans][sum]){
			auto dfs=[&](auto&self,int i,int j,int s)->void{
				if(i==0)return;
				c[j]=b[i];
				if(j>=0&&s>=b[i]&&f[i][j-1][s-b[i]])self(self,i,j-1,s-b[i]);
				else self(self,i-1,j,s);
			};
			dfs(dfs,i,ans,sum);
			break;
		}
	}
	priority_queue<pii>p;
	rep(i,1,n)p.push({a[i],i});
	rep(i,1,ans){
		cout<<c[i]<<" ";
		vector<pii>vec;
		rep(j,1,c[i]){
			pii t=p.top();p.pop();
			cout<<t.se<<" ";
			if(t.fi>1)vec.push_back({t.fi-1,t.se});
		}
		for(pii t:vec)p.push(t);
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

考虑如果已经钦定了盒子大小分别是 $C_1,C_2,\dots,C_m$ 那么是否能装得下。

结论是对任意的 $1\leq i\leq m$ 都有 $\sum \min(i,a_j)\leq C_1+C_2+\dots+C_i$。

证明可以考虑霍尔定理，搞个什么二分图，左边是盒子右边是各种类型，然后连个边就能用霍尔去证明了。

然后就能考虑 dp，定义 $f_{i,j,k}$ 表示只考虑大小 $\geq i$ 的盒子，当前用了 $j$ 个能否使得总和为 $k$。

注意到 $ij\leq \sum a_i$，于是 $j$ 只要开到 $\dfrac{\sum a_t}{i}$。然后这个 $f$ 还是 bool 左移右移啥的，直接上个 `bitset` 就行了。

时间复杂度：$\mathcal O(\dfrac{nm\log n}{\omega})$。

---

