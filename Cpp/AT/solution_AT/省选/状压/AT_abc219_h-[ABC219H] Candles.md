# [ABC219H] Candles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc219/tasks/abc219_h

無限に伸びる数直線の上に $ N $ 本のろうそくが置かれています。 $ i $ 番目のろうそくは座標 $ X_i $ にあり、時刻 $ 0 $ には長さは $ A_i $ で、火がついています。 火のついたろうそくは $ 1 $ 分あたり長さが $ 1 $ 短くなり、長さが $ 0 $ になると燃え尽きてそれ以降長さは変わりません。また、火を消されたろうそくの長さは変わりません。

高橋君は時刻 $ 0 $ に座標 $ 0 $ にいて、毎分 $ 1 $ 以下の距離を移動することができます。高橋君は自分がいる座標と同じ座標にろうそくがある場合、そのろうそくの火を消すことができます。（同じ座標に複数ある場合はまとめて消すことができます。）ここで、ろうそくの火を消すのにかかる時間は無視できます。

高橋君が適切に行動したとき、時刻 $ 0 $ から $ 10^{100} $ 分後に残っているろうそくの長さの総和としてあり得る最大の値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ -10^9\ \leq\ X_i\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

$ 3 $ 番目のろうそくは座標 $ 12 $ にあるため、高橋君の行動に関わらず火を消すより先に燃え尽きてしまいます。 残りの $ 2 $ 本について、まず座標 $ -2 $ へ $ 2 $ 分かけて移動して $ 1 $ 本目のろうそくの火を消し、その後 $ 5 $ 分かけて座標 $ 3 $ へ移動して $ 2 $ 本目のろうそくの火を消すと、これ以降ろうそくの長さが変化することはありません。 それぞれのろうそくの長さは $ 10-2=8 $ と $ 10-2-5=3 $ 残り、このとき残った長さの総和は $ 8+3=11 $ となって、このときが最大です。 よって、 $ 11 $ を出力します。

### Sample Explanation 2

同じ座標に $ 2 $ つ以上のろうそくが存在する可能性があること、答えが $ 32 $ bit整数に収まらないことがあることに注意してください。

## 样例 #1

### 输入

```
3
-2 10
3 10
12 10```

### 输出

```
11```

## 样例 #2

### 输入

```
5
0 1000000000
0 1000000000
1 1000000000
2 1000000000
3 1000000000```

### 输出

```
4999999994```

# 题解

## 作者：EuphoricStar (赞：14)

套路化了。

比较显然的[关路灯](https://www.luogu.com.cn/problem/P1220)型区间 dp。考虑你 $t$ 时刻熄灭一个初始长度为 $a$ 的蜡烛，得分是 $\max(a - t, 0)$，所以尝试把时间塞进状态。设 $f_{i, j, k, 0/1}$ 表示，熄灭完区间 $[i, j]$ 的蜡烛，当前时间是 $t$，在左端点还是右端点的最大得分。转移考虑走的路径即可。

发现时间可能很大，并且已经没有优化的余地了。考虑换种思路，假设我一开始得了 $\sum\limits_{i = 1}^n a_i$ 分，然后我每走一个单位距离，得分减少 $k$，$k$ 是还剩下的蜡烛数量。但是你发现一个很麻烦的事情是，熄灭蜡烛时得分要与 $0$ 取 $\max$，但是你到这个蜡烛的时候它的得分已经是负数了。

考虑直接钦定每个蜡烛的长度是否计入最后得分，称这样的蜡烛是**有效**的，这样如果遇到负数得分的蜡烛，最优解一定是不把它当成有效。状态添加一维 $k$ 表示熄灭区间 $[i, j]$ 的蜡烛后还剩下 $k$ 个有效蜡烛。转移就根据关路灯的基础上再讨论当前熄灭的这个蜡烛是否有效即可。

没了？

代码很好写。时间复杂度 $O(n^3)$。

[code](https://atcoder.jp/contests/abc219/submissions/42259796)

---

## 作者：BINYU (赞：4)

## 题意

在一根数轴上有 $n$ 根蜡烛，第 $i$ 根位于 $x_i$，长度为 $a_i$，初始时你在原点，每秒可以移动单位 $1$，当你移动到一根蜡烛所在的坐标时，你可以**瞬间**将其熄灭，但每秒钟每根未被熄灭且**还未燃烧完**的蜡烛长度都会减一，问 $10^{100}$ 秒后所有蜡烛总长度的最大值。

## 思路

因为熄灭蜡烛不耗费时间，所以我们如果经过了一个蜡烛就一定会立马将其熄灭，所以我们熄灭的蜡烛是一个区间，这启发我们考虑区间 DP（~~做过关路灯的应该都能想到吧~~）

考虑设 $dp_{i,j,t,0/1}$ 表示现在时间为 $t$，已经熄灭了从左到右第 $i$ 至第 $j$ 个蜡烛，最后停在 $i/j$，转移方程如下：

$$dp_{i,j,t,0} = \max(dp_{i+1,j,t-(x_{i+1}-x_i),0},dp_{i+1,j,t-(x_j-x_i),1})+\max(0,a_i-t)$$

$$dp_{i,j,t,1} = \max(dp_{i,j-1,t-(x_j-x_i),0},dp_{i,j-1,t-(x_j-x_{j-1}),1})+\max(0,a_j-t)$$

发现时空都爆了，考虑优化。

发现这里算法的瓶颈在于枚举 $t$，我们尝试用一个值域更小得变量去代替它。

考虑费用提前计算，先把所有蜡烛的长度计入答案，如果当前有 $k$ 个蜡烛未熄灭，则答案减 $k$。

发现这样还是无法优化掉 $t$，但至少已经找到了一个有用的变量。

发现如果一个蜡烛在我们熄灭它之前它自己就烧完了，我们可以不用考虑它，即：既不把他的长度加入初始答案，在过程中也不考虑该蜡烛。那么我们的 DP 状态就可以简化了：用 $dp_{i,j,k,0/1}$ 表示现在现在已经熄灭了从左到右第 $i$ 至第 $j$ 个蜡烛，最后停在 $i/j$，之后还要去熄灭 $k$ 个蜡烛。

转移时要考虑熄不熄灭当前的蜡烛，转移方程如下：

$$dp_{i,j,k,0} = \max(dp_{i+1,j,k,0}-k\times(x_{i+1}-x_i),dp_{i+1,j,k,1}-k\times(x_j-x_i),dp_{i+1,j,k+1,0}-(k+1)\times(x_{i+1}-x_i)+a_i,dp_{i+1,j,k,1}-(k+1)\times(x_j-x_i)+a_i)$$

$$dp_{i,j,k,1} = \max(dp_{i,j-1,k,0}-k\times(x_j-x_i),dp_{i,j-1,k,1}-k\times(x_j-x_{j-1}),dp_{i,j-1,k+1,0}-(k+1)\times(x_j-x_i)+a_i,dp_{i,j-1,k,1}-(k+1)\times(x_j-x_{j-1})+a_i)$$

设我们新加在 $0$ 的蜡烛编号为 $p$，初始时我们设 $dp_{p,p,k,0/1} = 0$，其中 $0 \le k \le n$，代表我们一共要熄灭 $k$ 个蜡烛。

答案就是 $\max(dp_{1,n+1,0,0},dp_{1,n+1,0,1})$。

时空复杂度都是 $O(n^3)$ 的，可过。

---

## 作者：Petit_Souris (赞：3)

比较经典的技巧。

容易发现这是个加强版的关路灯问题，我们立刻开始考虑区间 dp。那么设 $f_{l,r,t,0/1}$ 表示 $[l,r]$ 区间，时刻为 $t$，在左端点 / 右端点的最大收益，转移是容易的。但是由于时间这个维度太大了，我们需要优化掉这个维度。

那就很自然地联想到费用提前计算。这很有道理，你立刻就想到每走一单位长度就将收益减去还没熄灭的蜡烛数量。那么我们只要记录区间外的未熄灭蜡烛数量就行了。设 $f_{l,r,c,0/1}$ 表示 $[l,r]$ 区间，区间外有 $c$ 个未熄灭蜡烛，在左端点 / 右端点的最大收益。转移的时候，我们可以向左或者向右扩展，并决定是否熄灭对应的蜡烛。时间复杂度 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=305,INF=1e16;
ll n,pos,f[N][N][N],g[N][N][N];
pii p[N];
void Upd(ll&x,ll y){
    x=max(x,y);
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)p[i].first=read(),p[i].second=read();
    n++;
    sort(p+1,p+n+1);
    rep(i,1,n){
        if(p[i].first==0&&p[i].second==0){
            pos=i;
            break;
        }
    }
    rep(i,0,n){
        rep(j,0,n){
            rep(k,0,n)f[i][j][k]=g[i][j][k]=-INF;
        }
    }
    rep(k,0,n-1)f[pos][pos][k]=g[pos][pos][k]=0;
    rep(len,1,n){
        rep(l,1,n-len+1){
            ll r=l+len-1;
            if(l>pos||r<pos)continue;
            ll lft=l-1+n-r;
            rep(i,0,lft){
                if(l>1){
                    if(i){
                        Upd(f[l-1][r][i-1],f[l][r][i]+p[l-1].second-i*(p[l].first-p[l-1].first));
                        Upd(f[l-1][r][i-1],g[l][r][i]+p[l-1].second-i*(p[r].first-p[l-1].first));
                    }
                    Upd(f[l-1][r][i],f[l][r][i]-i*(p[l].first-p[l-1].first));
                    Upd(f[l-1][r][i],g[l][r][i]-i*(p[r].first-p[l-1].first));
                }
                if(r<n){
                    if(i){
                        Upd(g[l][r+1][i-1],g[l][r][i]+p[r+1].second-i*(p[r+1].first-p[r].first));
                        Upd(g[l][r+1][i-1],f[l][r][i]+p[r+1].second-i*(p[r+1].first-p[l].first));
                    }
                    Upd(g[l][r+1][i],g[l][r][i]-i*(p[r+1].first-p[r].first));
                    Upd(g[l][r+1][i],f[l][r][i]-i*(p[r+1].first-p[l].first));
                }
            }
        }
    }
    ll ans=max(f[1][n][0],g[1][n][0]);
    write(ans);
    return 0;
}
```

---

## 作者：Phartial (赞：3)

# [ABC219H] Candles

首先将蜡烛按 $X_i$ 排序。有一个显然的区间 dp 状态设计 $f_{l,r,t,0/1}$ 表示 $t$ 时刻熄灭了下标范围 $[l,r]$ 之间的蜡烛，且现在位于该区间的左端/右端时的最大收益。显然 $t$ 时刻时熄灭第 $i$ 支蜡烛的收益是 $\max(0,a_i-t)$，于是简单的分讨一下即可转移。但是 $t$ 这一维很大，考虑优化。

一个经典的套路是我们考虑计算最小损失而非最大收益，但注意到收益的式子中有个 $\max$，很难受。考虑通过额外决策每根蜡烛是否被忽略来规避掉 $\max$（因为显然最优策略中我们必然会忽略掉所有负收益的蜡烛，而不会忽略所有正收益的蜡烛）。假设我们还剩 $k$ 支蜡烛没被忽略且没被熄灭，过一时刻后就会损失 $k$ 的收益。

设 $f_{l,r,k,0/1}$ 表示我们熄灭了下标范围 $[l,r]$ 之间的蜡烛，现在位于该区间的左端/右端，且还有 $k$ 支蜡烛需要被熄灭时的最大收益。分讨一下当前所在位置上的蜡烛要不要忽略即可。为方便，我们可以新增一支长度为 $0$ 且位于坐标 $0$ 上的蜡烛 $p$，初始状态即为 $f_{p,p,k,0/1}=0$，答案即为 $\max(f_{1,n+1,0,0},f_{1,n+1,0,1})$。

时间复杂度 $\mathcal{O}(n^3)$。代码相当好写。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;
using Pll = pair<LL, LL>;

const int kN = 302;

int n;
Pll a[kN];
LL f[kN][kN][kN][2];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].first >> a[i].second;
  }
  a[++n] = {0, 0};
  sort(a + 1, a + n + 1);
  int p = find(a + 1, a + n + 1, Pll(0, 0)) - a;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int k = 0; k <= n; ++k) {
        f[i][j][k][0] = f[i][j][k][1] = -1e18;
      }
    }
  }
  for (int k = 0; k <= n; ++k) {
    f[p][p][k][0] = f[p][p][k][1] = 0;
  }
  for (int l = 1; l < n; ++l) {
    for (int i = 1, j; (j = i + l - 1) <= n; ++i) {
      for (int k = 0; k <= n; ++k) {
        if (i > 1) {
          f[i - 1][j][k][0] = max({f[i - 1][j][k][0], f[i][j][k][0] - k * (a[i].first - a[i - 1].first), f[i][j][k][1] - k * (a[j].first - a[i - 1].first)});
          if (k) {
            f[i - 1][j][k - 1][0] = max({f[i - 1][j][k - 1][0], f[i][j][k][0] - k * (a[i].first - a[i - 1].first) + a[i - 1].second, f[i][j][k][1] - k * (a[j].first - a[i - 1].first) + a[i - 1].second});
          }
        }
        if (j < n) {
          f[i][j + 1][k][1] = max({f[i][j + 1][k][1], f[i][j][k][0] - k * (a[j + 1].first - a[i].first), f[i][j][k][1] - k * (a[j + 1].first - a[j].first)});
          if (k) {
            f[i][j + 1][k - 1][1] = max({f[i][j + 1][k - 1][1], f[i][j][k][0] - k * (a[j + 1].first - a[i].first) + a[j + 1].second, f[i][j][k][1] - k * (a[j + 1].first - a[j].first) + a[j + 1].second});
          }
        }
      }
    }
  }
  cout << max(f[1][n][0][0], f[1][n][0][1]);
  return 0;
}
```


---

## 作者：shinzanmono (赞：3)

首先考慮如果蠟燭允許燒成負數長度的做法。

設 $f_{l,r,0/1}$ 為 $[l,r]$ 區間蠟燭全部被熄滅時的最大長度和 $-$ 未熄滅的蠟燭個數 $\times$ 已經經過的時間，且最後一只熄滅的蠟燭為 $l/r$，轉移顯然。

考慮枚舉最終被燒沒得蠟燭的個數，在狀態中新增加一維 $k$，$f_{l,r,k,0/1}$ 表示 $[l,r]$ 區間蠟燭全部被熄滅時，還餘下 $k$ 個有效蠟燭，當前已經熄滅的蠟燭長度和 $-$ 未熄滅的**有效**的蠟燭個數 $\times$ 已經經過的時間。轉移時枚舉每次前往的蠟燭是否有效即可。答案即為 $f$ 數組的最大值，時間複雜度 $O(n^3)$。

```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=310;
ll a[sz],f[sz][sz][sz][2],len[sz];
std::pair<ll,ll>c[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++)std::cin>>a[i]>>len[i],c[i]=std::make_pair(a[i],len[i]);
    c[++n]=std::make_pair(0,0);
    std::sort(c+1,c+n+1);
    for(int i=1;i<=n;i++)a[i]=c[i].first,len[i]=c[i].second;
    for(int l=1;l<=n;l++)
        for(int r=l;r<=n;r++)
            for(int k=0;k<=n+1;k++)
                f[l][r][k][0]=f[l][r][k][1]=-1e18;
    for(int i=1;i<=n;i++){
        if(len[i]!=0)continue;
        for(int k=0;k<=n;k++)f[i][i][k][0]=f[i][i][k][1]=0;
        break;
    }
    for(int p=2;p<=n;p++){
        for(int l=1,r=p;r<=n;l++,r++){
            for(int k=0;k<=n;k++){
                f[l][r][k][0]=std::max({f[l+1][r][k][0]-k*(a[l+1]-a[l]),f[l+1][r][k][1]-k*(a[r]-a[l]),f[l+1][r][k+1][0]-(k+1)*(a[l+1]-a[l])+len[l],f[l+1][r][k+1][1]-(k+1)*(a[r]-a[l])+len[l]});
                f[l][r][k][1]=std::max({f[l][r-1][k][0]-k*(a[r]-a[l]),f[l][r-1][k][1]-k*(a[r]-a[r-1]),f[l][r-1][k+1][0]-(k+1)*(a[r]-a[l])+len[r],f[l][r-1][k+1][1]-(k+1)*(a[r]-a[r-1])+len[r]});
            }
        }
    }
    ll ans=0;
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++)
			for(int k=0;k<=n;k++)
				ans=std::max({ans,f[l][r][k][0],f[l][r][k][1]});
    std::cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：123456xwd (赞：2)

感觉是一个 dp，显然，吹掉的蜡烛是一个区间，发现 $n$ 十分小，按套路区间 dp ，设 $dp_{l,r,0/1}$ 表示吹掉了区间 $[l,r]$，在左或右端点的时候的最大蜡烛长度。

至于每移动一个单位，蜡烛就下降 1，考虑费用提前算。

可是蜡烛已经燃烧完毕了怎么办呢？

我们发现，相当于选择一些蜡烛不去选择，最优情况下一定是都选择会产生正贡献的蜡烛，错解不优。

设 $dp_{l,r,k,0/1}$，其余的同上，$k$ 表示还有 $k$ 个需要选择，最后答案为 $dp_{1,n,0,0/1}$。

转移显然从 $[l+1,r]$ 或者 $[l,r-1]$ 转移，我们先枚举区间再枚举 $k$ 即可。

时间为 $\mathcal{O}(n^3)$，不要忘记一开始在原点。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define val first
#define id second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
#define popcount __builtin_popcount
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=300+5,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n;
struct node{
	int a,x;
}a[N];
bool cmp(node x,node y){
	return x.x<y.x;
}
int dp[N][N][N][2];
int dis(int l,int r,int tag,int L,int R,int Tag){
	int x=tag?r:l,y=Tag?R:L;
	return abs(a[x].x-a[y].x);
}
signed main(){
	n=rd();
	for(int i=1;i<=n;i++)a[i].x=rd(),a[i].a=rd();
	a[++n]={0,0};
	sort(a+1,a+1+n,cmp);
	memset(dp,-0x3f,sizeof(dp));
	for(int i=1;i<=n;++i){
		if(!a[i].a&&!a[i].x){
			for(int j=0;j<=n;++j) dp[i][i][j][0]=dp[i][i][j][1]=0;
		}
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l<=n-len+1;l++){
			int r=l+len-1;
			for(int k=0;k<=n;k++){
				for(int t=0;t<=1;t++){
					int ll=l,rr=r;
					if(t&1) rr--;
					else ll++;
					for(int i=0;i<=1;i++){
						for(int j=0;j<=1;j++){
							//不花费：
							dp[l][r][k][i]=max(dp[l][r][k][i],dp[ll][rr][k][j]-dis(l,r,i,ll,rr,j)*k);
							//花费：
							if(t&1) dp[l][r][k][i]=max(dp[l][r][k][i],dp[ll][rr][k+1][j]+a[r].a-(k+1)*dis(r,r,i,ll,rr,j)-k*dis(r,r,i,l,r,i));
							else dp[l][r][k][i]=max(dp[l][r][k][i],dp[ll][rr][k+1][j]+a[l].a-(k+1)*dis(l,l,i,ll,rr,j)-k*dis(l,l,i,l,r,i));
						}
					}
				}				
			}
		}
	}
	printf("%lld",max(dp[1][n][0][0],dp[1][n][0][1]));
    return 0;
}
```

---

## 作者：WDY_Hodur (赞：1)

# 题目描述
给你 $n$ 个蜡烛，蜡烛 $i$ 在 $x_i$ 上，长度为 $a_i$，以每秒减一的速度燃烧，烧完熄灭。初始时你在原点，每次移动一个单位长度，在蜡烛 $i$ 时可以将蜡烛 $i$ 熄灭，并且不耗费时间，熄灭后的蜡烛不再减短。求最终留下的蜡烛总长度最长是多少。

# 解题思路
因为熄灭蜡烛不需要时间，所以只要经过蜡烛 $i$，就可以直接将其熄灭，所以熄灭的蜡烛一定是一个区间，我们考虑区间 DP。

设 $f_{i,j,t,0/1}$ 表示已经熄灭了 $i$ 到 $j$ 的区间，花费了 $t$ 的时间，最后停在在 $i$ 或 $j$ 的最大值。转移方程为：
$$
f_{i,j,t,0}=\max(f_{i+1,j,t-x_{i+1}+x_i,0},f_{i+1,j,t-x_{j}+x_i,1})+\max(a_i-t,0)
$$
$$
f_{i,j,t,1}=\max(f_{i,j-1,t-x_j+x_{j-1},1},f_{i,j-1,t-x_j+x_i,0})+\max(a_j-t,0)
$$

但我们发现 $t$ 这一维会很大，时间空间都会炸，所以把它换一下，变成 $f_{i,j,k,0/1}$ 表示已经熄灭了 $i$ 到 $j$ 的区间，还剩 $k$ 个正在燃烧，最后停在在 $i$ 或 $j$ 的最大值。

我们给 $n$ 加一在原点处加一个没有长度的蜡烛，设它的编号为 $s$，则 $f_{s,s,k,0/1}=0(0\le k< n)$，其余都初始化为极小值。

那么 $k$ 这一维是如何转移的呢？分为两种情况：
1. 当前要熄灭的蜡烛已经灭了，也就是直接由 $k$ 转移。
2. 当前要熄灭的蜡烛还在燃烧，而就是从 $k+1$ 转移。

转移方程如下：
$$
f_{i,j,k,0}=\max(f_{i+1,j,k,0}-k\times (x_{i+1}-x_i),f_{i+1,j,k,1}-k\times (x_j-x_i),a_i+f_{i+1,j,k+1,0}-(k+1)\times (x_{i+1}-x_i),a_i+f_{i+1,j,k,1}-(k+1)\times (x_j-x_i))
$$

$$
f_{i,j,k,1}=\max(f_{i+1,j,k,1}-k\times (x_j-x_{j-1}),f_{i+1,j,k,0}-k\times (x_j-x_i),a_j+f_{i,j-1,k+1,1}-(k+1)\times (x_j-x_{j-1}),a_j+f_{i,j-1,k,0}-(k+1)\times (x_j-x_i))
$$

最终答案为 $\max(f_{1,n,0,0},f_{1,n,0,1})$。

# 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 305
using namespace std;
int n,f1[N][N][N],f2[N][N][N],ans;
struct node{int x,l;}a[N];
int cmp(node a,node b){return a.x<b.x;}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].l;
		if(abs(a[i].x)>=a[i].l)a[i].l=0;
	}
	++n;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=0;k<=n;k++)f1[i][j][k]=f2[i][j][k]=-0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=n;i++){
		if(!a[i].x&&!a[i].l){
			for(int k=0;k<n;k++)f1[i][i][k]=f2[i][i][k]=0;
			break;
		}
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			for(int k=0;k<=n-len;k++){
				f1[i][j][k]=max(f1[i][j][k],f1[i+1][j][k]-k*(a[i+1].x-a[i].x));//i 已经熄灭 
				f1[i][j][k]=max(f1[i][j][k],f2[i+1][j][k]-k*(a[j].x-a[i].x));
				f1[i][j][k]=max(f1[i][j][k],a[i].l+f1[i+1][j][k+1]-(k+1)*(a[i+1].x-a[i].x));//i 还未熄灭
				f1[i][j][k]=max(f1[i][j][k],a[i].l+f2[i+1][j][k+1]-(k+1)*(a[j].x-a[i].x));
				
				f2[i][j][k]=max(f2[i][j][k],f2[i][j-1][k]-k*(a[j].x-a[j-1].x));//j 已经熄灭
				f2[i][j][k]=max(f2[i][j][k],f1[i][j-1][k]-k*(a[j].x-a[i].x));
				f2[i][j][k]=max(f2[i][j][k],a[j].l+f2[i][j-1][k+1]-(k+1)*(a[j].x-a[j-1].x));//j 还未熄灭
				f2[i][j][k]=max(f2[i][j][k],a[j].l+f1[i][j-1][k+1]-(k+1)*(a[j].x-a[i].x));
			}
		}
	}
	cout<<max(f1[1][n][0],f2[1][n][0]);
	return 0;
}

```

---

## 作者：Gmt丶FFF (赞：1)

可以很明显的看出来是区间 dp。

一个很暴力的状态就是设 $f_{i,j,k,l}$ 为第 $k$ 时刻，遍历完 $\left[l,r\right]$ 的区间，当前位置在最左或最右的蜡烛的位置，所得到的长度和最大值。

但是 $k$ 由于过大，所以这个暴力状态肯定过不了。

这时我们就得优化 dp 方程了。

因为为了获取长度和最大值，我们很有可能舍弃一些蜡烛不选（也就是长度会变为 $0$），而选择一些蜡烛。

那么假设我们选取蜡烛的顺序为 $a_1,a_2,...a_n$，那么我们在途径 $a_1$ 到 $a_2$ 的过程中，我们所有后面选择的蜡烛的长度都会减去 $dis(a_1,a_2)$，由此我们可知：

若第 $a_i$ 蜡烛是倒数第 $j$ 个选择的，那么它对全局的影响为 $dis(a_i-a_{i-1})\times j$，那么其造成的贡献值就为 $length(a_i)-dis(a_i-a_{i-1})\times j$，其中 $length(a_i)$ 表示 $a_i$ 的初始长度。

所以我们重新设 $f_{i,j,k,l}$ 为已选择区间 $\left[l,r\right]$，其中这个区间最后一个选择的蜡烛是倒数第 $k$ 个选择的蜡烛，当前位置在最左或最右的蜡烛的位置所得到的长度和最大值。

如果我们要选这个区间的最左边的蜡烛，那么：

$f_{i,j,k,0}=length(i)+\max(f_{i+1,j,k+1,0}-dis(a_{i+1},a_i)\times k,f_{i+1,j,k+1,1}-dis(a_j,a_i)\times k)$

不选就继承：

$f_{i,j,k,0}=\max(f_{i+1,j,k,0}-(dis(a_{i+1},a_i))\times(k-1),f_{i+1,j,k,1}-dis(a_j,a_i)\times(k-1))$

注意这里乘的是 $k-1$ ，因为区间里最后选的是第 $k$ 大的，说明下一个选择的是 $k-1$ 大的，根据上述陈述，那么系数就应该为 $k-1$。

选（或不选）右边同理。


时间复杂度：$O(n^3)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
#define int long long
using namespace std;
const int N=305;
int n,m,f[N][N][N][2];
struct node
{
	int name,data;
}a[N];
inline bool cmp(node x,node y)
{
	return x.name<y.name;
}
signed main()
{
	freopen("1.in","r",stdin); 
	freopen("1.out","w",stdout); 
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].name,&a[i].data);
	a[++n]={0,0};
	sort(a+1,a+1+n,cmp);
	memset(f,-0x3f,sizeof(f));
	for(int i=1;i<=n;i++)for(int j=0;j<=n;j++)if(a[i].name==0&&a[i].data==0)f[i][i][j][0]=f[i][i][j][1]=0;
	int ans=0;
	for(int len=2;len<=n;len++)
	{
		for(int i=1;i+len-1<=n;i++)
		{
			int j=i+len-1;
			for(int k=1;k<=n;k++)
			{
				f[i][j][k][0]=max(f[i+1][j][k][0]-(k-1)*(a[i+1].name-a[i].name),f[i+1][j][k][1]-(k-1)*(a[j].name-a[i].name));
				f[i][j][k][0]=max(f[i][j][k][0],max(f[i+1][j][k+1][0]-k*(a[i+1].name-a[i].name)+a[i].data,f[i+1][j][k+1][1]-k*(a[j].name-a[i].name)+a[i].data));
				f[i][j][k][1]=max(f[i][j-1][k][0]-(k-1)*(a[j].name-a[i].name),f[i][j-1][k][1]-(k-1)*(a[j].name-a[j-1].name));
				f[i][j][k][1]=max(f[i][j][k][1],max(f[i][j-1][k+1][0]-k*(a[j].name-a[i].name)+a[j].data,f[i][j-1][k+1][1]-k*(a[j].name-a[j-1].name)+a[j].data));
//				cout<<i<<" "<<j<<" "<<k<<" "<<f[i][j-1][k][0]+a[j].data<<" "<<f[i][j][k][0]<<" "<<f[i][j][k][1]<<endl;
				ans=max(ans,max(f[i][j][k][1],f[i][j][k][0]));
			}			
		}
	
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：shinkuu (赞：1)

做起来真的没有想象中的那么难（？）感谢 @zltqwq 讲的好题/bx

首先考虑蜡烛可以烧到负数长度怎么做。发现这题等同于关路灯。设个状态：$dp_{i,j,0/1}$ 表示当前 $[i,j]$ 范围内的蜡烛都已熄灭，现在人在左/右端点的最大答案。枚举从 $[i+1,j]$ 或 $[i,j-1]$ 转移即可。

然后加入只能烧到 $0$ 长度怎么做。看起来变得非常麻烦，但是会发现一个性质：此时问题的答案不会比上面问题的答案更小。因为相对于上面的问题，此时长度 $<0$ 的蜡烛相当于是被我们删去了。

此时就可以将这个问题转化一下：你可以在这些蜡烛中选任意多个删去，并根据上面的方式计算，并将所有结果取 $\max$。**因为在最优情况中，有正贡献的蜡烛一定会被选，否则一定不会。所以这两个问题是等价的！**

现在是不是就变得明朗了呢？

所以可以直接把选了多少个塞进状态。设 $dp_{i,j,k,0/1}$ 表示当前 $[i,j]$ 范围内的蜡烛都已熄灭，还有 $k$ 个蜡烛会产生贡献，现在人在左/右端点的最大答案。枚举从 $[i+1,j]$ 或 $[i,j-1]$ 转移及当前蜡烛有没有被删去即可。时间复杂度 $O(n^3)$。

code：

```cpp
int n,m;
ll dp[N][N][N][2];
struct node{
	ll c,p;
}e[N];
inline ll cost(int l,int r,int p,int k,int op){
	return max(dp[l][r][k][op]-(op?abs(e[r].p-e[p].p):abs(e[l].p-e[p].p))*k,dp[l][r][k+1][op]-(op?abs(e[r].p-e[p].p):abs(e[l].p-e[p].p))*(k+1)+e[p].c);
}
inline bool cmp(node x,node y){
	return x.p!=y.p?x.p<y.p:x.c>y.c;
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%lld%lld",&e[i].p,&e[i].c);
	}
	e[++n]={-inf,0};
	sort(e+1,e+n+1,cmp);
	int s=0;
	rep(i,1,n){
		if(!e[i].p)
			s=i;
	}
	mems(dp,-0x3f);
	rep(i,0,n){
		dp[s][s][i][0]=dp[s][s][i][1]=0;
	}
	ll ans=0;
	drep(i,s,1){
		rep(j,s,n){
			if(i==j)
				continue;
			rep(k,0,n){
				dp[i][j][k][0]=max(cost(i+1,j,i,k,0),cost(i+1,j,i,k,1));
				dp[i][j][k][1]=max(cost(i,j-1,j,k,0),cost(i,j-1,j,k,1));
				ans=max(ans,max(dp[i][j][k][0],dp[i][j][k][1]));
			}
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Leasier (赞：1)

费用提前计算这样的东西对我来说还是太困难了 /ll

------------

考虑在将蜡烛排序后加入一个 $x = a = 0$ 的蜡烛，钦定我们先熄灭这根蜡烛。

注意到我们向左右移动时一定会熄灭沿途的蜡烛，且熄灭每一根蜡烛后的状态都可以表示为：$[l, r]$ 内的蜡烛已被熄灭，刚刚熄灭了第 $l / r$ 根蜡烛。

遂考虑 dp。设 $f_{l, r}, g_{l, r}$ 分别表示 $[l, r]$ 内的蜡烛已被熄灭，现在位于最左 / 右处的最大剩余总长度。

但是这样有一个致命的问题：我们无法得知到达某一个状态时的时间 /ng

注意到某一段时间 $t$ 的贡献只与后面还有几根蜡烛会在燃尽前被熄灭有关，考虑**费用提前计算**——即将后面还有几根蜡烛需要被熄灭加入状态。

具体地，将状态改为 $f_{l, r, i}, g_{l, r, i}$，进而可以讨论下一步向左还是向右以及我们是否会去熄灭它来做到 $O(1)$ 转移。

时间复杂度为 $O(n^3)$。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef struct {
	int x;
	int a;
} Node;

ll dp1[307][307][307], dp2[307][307][307];
Node candle[307];

bool operator <(const Node a, const Node b){
	if (a.x != b.x) return a.x < b.x;
	return a.a < b.a;
}

int main(){
	int n, mid = 1;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> candle[i].x >> candle[i].a;
	}
	n++;
	sort(candle + 1, candle + n + 1);
	while (candle[mid].x < 0) mid++;
	for (int i = 1; i <= mid; i++){
		for (int j = mid; j <= n; j++){
			int cnt = (i - 1) + (n - j);
			for (int k = 0; k <= cnt; k++){
				dp1[i][j][k] = dp2[i][j][k] = -8e18;
			}
		}
	}
	for (int i = 0; i < n; i++){
		dp1[mid][mid][i] = dp2[mid][mid][i] = 0;
	}
	for (int i = mid; i >= 1; i--){
		for (int j = mid; j <= n; j++){
			int cnt = (i - 1) + (n - j);
			for (int k = 0; k <= cnt; k++){
				if (i > 1){
					if (k > 0) dp1[i - 1][j][k - 1] = max(dp1[i - 1][j][k - 1], dp1[i][j][k] + candle[i - 1].a - (ll)k * (candle[i].x - candle[i - 1].x));
					dp1[i - 1][j][k] = max(dp1[i - 1][j][k], dp1[i][j][k] - (ll)k * (candle[i].x - candle[i - 1].x));
					if (k > 0) dp1[i - 1][j][k - 1] = max(dp1[i - 1][j][k - 1], dp2[i][j][k] + candle[i - 1].a - (ll)k * (candle[j].x - candle[i - 1].x));
					dp1[i - 1][j][k] = max(dp1[i - 1][j][k], dp2[i][j][k] - (ll)k * (candle[j].x - candle[i - 1].x));
				}
				if (j < n){
					if (k > 0) dp2[i][j + 1][k - 1] = max(dp2[i][j + 1][k - 1], dp1[i][j][k] + candle[j + 1].a - (ll)k * (candle[j + 1].x - candle[i].x));
					dp2[i][j + 1][k] = max(dp2[i][j + 1][k], dp1[i][j][k] - (ll)k * (candle[j + 1].x - candle[i].x));
					if (k > 0) dp2[i][j + 1][k - 1] = max(dp2[i][j + 1][k - 1], dp2[i][j][k] + candle[j + 1].a - (ll)k * (candle[j + 1].x - candle[j].x));
					dp2[i][j + 1][k] = max(dp2[i][j + 1][k], dp2[i][j][k] - (ll)k * (candle[j + 1].x - candle[j].x));
				}
			}
		}
	}
	cout << max(dp1[1][n][0], dp2[1][n][0]);
	return 0;
}
```

---

## 作者：Sunrise_beforeglow (赞：0)

感觉和关路灯类似。

我们定义 $dp_{i,j,k,0/1}$ 表示已经熄灭了 $[i,j]$ 范围的若干蜡烛，还要继续熄灭 $k$ 个蜡烛，且当前停留在左边或右边所能获得的最大收益。

初始状态，设 $0$ 处也有一个点，权值为 $0$，设它按位置排在 $p$ 处，那么 $dp_{p,p,k,0/1}=0,k\in[0,n]$。

最后结果肯定是 $\max(dp_{1,n,0,0},dp_{1,n,0,1})$。

考虑转移，由对称性，这里只考虑转移 $dp_{i,j,k,0}$。

又由对称性，可以只考虑由 $[i+1,j]$ 的区间且停留在最左边转移而来。

1. 如果吹灭 $i$ 处的蜡烛，$[i+1,j]$ 要继续吹灭 $k+1$ 个蜡烛，这 $k+1$ 根蜡烛总共会消耗 $(k+1)\times (X_{i+1}-X_{i})$ 的长度，且会获得 $A_i$ 的蜡烛长度，所以 $dp_{i,j,k,0}\gets \max(dp_{i,j,k,0},dp_{i+1,j,k+1,0}-(k+1)\times(X_{i+1}-X_i)+A_i)$。
2. 如果不吹灭 $i$ 处的蜡烛，$[i+1,j]$ 要继续吹灭 $k$ 个蜡烛，这 $k$ 个蜡烛总共会消耗 $k\times (X_{i+1}-X_i)$ 的长度，所以 $dp_{i,j,k,0}\gets \max(dp_{i,j,k,0},dp_{i+1,j,k,0}-k\times (X_{i+1}-X_i))$。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int x,a;
}u[305];
bool cmp(node a,node b)
{
	return a.x<b.x;
}
int n,dp[2][305][305][305];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>u[i].x>>u[i].a;
		if(abs(u[i].x)>=u[i].a)u[i].a=0;
	}
	n++;
	sort(u+1,u+n+1,cmp);
	memset(dp[1],-0x3f,sizeof(dp[1]));
	memset(dp[0],-0x3f,sizeof(dp[0]));
	int s=-1;
	for(int i=1;i<=n;i++)
	{
		if(!u[i].x&&!u[i].a)
		{
			s=i;
			break;
		}
	}
	for(int k=0;k<n;k++)dp[1][s][s][k]=dp[0][s][s][k]=0;
	for(int len=2;len<=n;len++)
	{
		for(int i=1;i+len-1<=n;i++)
		{
			int j=i+len-1;
			for(int k=0;k<=n-len;k++)
			{
				dp[1][i][j][k]=max({dp[1][i][j-1][k]-k*(u[j].x-u[j-1].x),dp[1][i][j-1][k+1]-(k+1)*(u[j].x-u[j-1].x)+u[j].a,dp[0][i][j-1][k]-k*(u[j].x-u[i].x),dp[0][i][j-1][k+1]-(k+1)*(u[j].x-u[i].x)+u[j].a});
				dp[0][i][j][k]=max({dp[1][i+1][j][k]-k*(u[j].x-u[i].x),dp[1][i+1][j][k+1]-(k+1)*(u[j].x-u[i].x)+u[i].a,dp[0][i+1][j][k]-k*(u[i+1].x-u[i].x),dp[0][i+1][j][k+1]-(k+1)*(u[i+1].x-u[i].x)+u[i].a});
			}
		}
	}
	cout<<max(dp[1][1][n][0],dp[0][1][n][0]);
	return 0;
}
```

---

## 作者：cqbzlzm (赞：0)

### Description

有 $n$ 根蜡烛，位置 $p_i$，长度 $l_i$。每秒每根蜡烛长度减 $1$，蜡烛减到 $0$ 就不变了。

你在原点，每秒可以水平地走长度 $1$，每个时刻，你可以吹灭与你横坐标相同的蜡烛（无需消耗时间）。求 $10^{100}$ 秒后剩余蜡烛长度之和最大值。

### Solution

发现一个状态和**时间**、**蜡烛剩余长度**等都有关系。

容易想到一些和 $t$ 有关的 dp，难以优化。

想到可以费用提前算，维护的是剩余的蜡烛数量。对当前剩下的 $k$ 根蜡烛，$t$ 时刻后蜡烛总长度就减少了 $k\times t$。

但是我们可能在从 $r\rightarrow r+1$ 时，有其他的蜡烛在途中熄灭了，那么这一段时间的贡献就难以计算。

难算的是那些**自然熄灭的蜡烛**，注意到他们**对最终答案是没有影响的**（即提前钦定某些特殊的部分）。

所以 $dp_{l,r,k,0/1}$ 表示已经吹灭了 $[l,r]$ 的蜡烛，现在还剩 $k$ 根蜡烛（*），在   $l$ 还是 $r$，当前剩余蜡烛的长度之和最大值。

*注意这里的 $k$ 不包括自然熄灭的蜡烛。

转移时要讨论下这根蜡烛是自然熄灭还是被我吹灭。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 300;
int n;
struct candle {
    int x, y;
} a[MAXN + 5];
int f[MAXN + 5][MAXN + 5][MAXN + 5][2];
signed main() {
    scanf("%lld", &n);
    int sum = 0;
    for (int i = 1; i <= n; i ++)
        scanf("%lld%lld", &a[i].x, &a[i].y);
    n ++; a[n].x = 0, a[n].y = 0;
    sort(a + 1, a + 1 + n, [](candle a, candle b) {return a.x < b.x;});
    int p = -1;
	for (int i = 1; i <= n; ++i) {
		if (!a[i].y) {
			p = i;
			break;
		}
	}
    memset(f, -0x3f3f3f3f, sizeof(f));
    for (int i = 0; i <= n; i ++)
		f[p][p][i][0] = f[p][p][i][1] = 0;
	for (int len = 2; len <= n; len ++) {
        for (int i = 1, j = len; j <= n; i ++, j ++) {
            for (int k = 0; k <= n; k ++) {
                f[i][j][k][0] = max({f[i + 1][j][k][0] - (a[i + 1].x - a[i].x) * k, f[i + 1][j][k + 1][0] - (a[i + 1].x - a[i].x) * (k + 1) + a[i].y, f[i + 1][j][k][1] - (a[j].x - a[i].x) * k, f[i + 1][j][k + 1][1] - (a[j].x - a[i].x) * (k + 1) + a[i].y});
				f[i][j][k][1] = max({f[i][j - 1][k][0] - (a[j].x - a[i].x) * k, f[i][j - 1][k + 1][0] - (a[j].x - a[i].x) * (k + 1) + a[j].y, f[i][j - 1][k][1] - (a[j].x - a[j - 1].x) * k, f[i][j - 1][k + 1][1] - (a[j].x - a[j - 1].x) * (k + 1) + a[j].y});
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = i; j <= n; j ++) {
            for (int k = 0; k <= n; k ++) {
                ans = max({ans, f[i][j][k][0], f[i][j][k][1]});
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

好题。

考虑建立在关路灯的基础上，但是我们很难计入时间变量。

注意到一个烧成负数的蜡烛我们肯定不要它。所有我们额外计入是否要一个蜡烛的变量，这样我们就可以**通过扩大解的数量**来贪心的解决这个难点。

接下来只需要设计 $f_{i,j,k}$ 表示关掉 $i\sim j$ 的灯且里面有效蜡烛的数量是 $k$ 的最大价值即可。

---

## 作者：Jerrywang09 (赞：0)

区间 DP。需要知道哪些蜡烛还在燃烧，但时间高达 $10^9$，状态中不能带有时间，怎么设计状态？有一个很巧妙的状态设计：$f(l,r,k,0/1)$ 表示区间 $[l,r]$ 之外、熄灭后还有长度的蜡烛个数为 $k$，现在走到了 $l/r$，最大剩余长度。

转移类似于[关路灯](https://www.luogu.com.cn/problem/P1220)，涉及了“费用提前计算”的思想。

```cpp
// Title:  Candles
// Source: ABC219H
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>
#define F first
#define S second
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=310;
using namespace std;

int n; ll f[N][N][N][2]; pii a[N];

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d", &n);
	rep(i, 1, n) scanf("%lld%lld", &a[i].F, &a[i].S);
	n++; sort(a+1, a+n+1); // 加入初始位置0
	memset(f, -0x3f, sizeof f);
	rep(i, 1, n) if(a[i].F==0)
		rep(k, 0, n-1) f[i][i][k][0]=f[i][i][k][1]=0;
	rep(len, 2, n) rep(l, 1, n-len+1) rep(k, 0, n-1) // 区间外还有k个有效蜡烛
	{
		int r=l+len-1;
		f[l][r][k][0]=max({f[l][r][k][0],
		    f[l+1][r][k][0]-k*(a[l+1].F-a[l].F),
			f[l+1][r][k+1][0]-(k+1)*(a[l+1].F-a[l].F)+a[l].S,
			f[l+1][r][k][1]-k*(a[r].F-a[l].F),
			f[l+1][r][k+1][1]-(k+1)*(a[r].F-a[l].F)+a[l].S});
		f[l][r][k][1]=max({f[l][r][k][1],
			f[l][r-1][k][0]-k*(a[r].F-a[l].F),
			f[l][r-1][k+1][0]-(k+1)*(a[r].F-a[l].F)+a[r].S,
			f[l][r-1][k][1]-k*(a[r].F-a[r-1].F),
			f[l][r-1][k+1][1]-(k+1)*(a[r].F-a[r-1].F)+a[r].S});
	}
	printf("%lld", max(f[1][n][0][0], f[1][n][0][1]));
	
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](https://atcoder.jp/contests/abc219/tasks/abc219_h)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc219_h)

## 分析

考虑最基础的区间 dp，$dp[l][r]$ 表示处理完区间 $[l, r]$ 的蜡烛之后这区间内剩余的最大长度。然后由于处理完之后位置要么在左端点要么在右端点，就再加一维 $0 / 1$ 记录一下当前位置。

先考虑蜡烛能被减成负数的情况。此时我们的转移就是每次往左往右扩，看是从哪个端点走到哪个端点。但是这样不能知道时间，所以考虑进行**费用提前计算**，每次走向下一支蜡烛时把这一次行走花费的时间给所有区间之外的（尚未处理的）蜡烛造成的减少量先算进当前的 dp 值里面，然后走到一支蜡烛之后直接把它的长度加进 dp 值。

但是实际上蜡烛不能被减成负数。

由于剩负数的蜡烛不被算进答案，我们走到这个蜡烛时就不把它的长度加入 dp 值了。由于不把它算进答案，消耗时间也就不会给它的贡献带来减少量。所以走向一个蜡烛并且提前计算费用时，还需要知道这个区间之外有多少个蜡烛到最后剩下正数长度。我们考虑直接把这玩意也扔进状态里，于是状态变成 $dp[l][r][0 / 1][k]$ 表示已经处理完了区间 $[l, r]$ 的蜡烛，当前在左 / 右端点，$[l, r]$ 之外有多少蜡烛我们要求它剩下正数。转移的时候考虑走向的这个蜡烛最后要不要留成正数，然后就可以转移了。具体的方程比较复杂，可以看代码。

另外请不要把同一个位置上的蜡烛压到一起，因为同一个位置上的蜡烛并不是都会被算进答案。

还有就是这样可能会钦定一个减成负数的蜡烛算进答案，但是由于此处求最优解，而最优解一定不会把负数的蜡烛算进答案，所以不会错。

在实现上，可以在 $0$ 位置加一根空蜡烛，不然不好赋初值。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
#include <map>
#define int long long
using namespace std;
const int inf = 448509071590753727;
int n;
int a[305];
map<int, int> id;
struct Pos {
    int p, len;
} p[305];
int dp[305][305][305][2];
void Cmax(int& x, int y) { x = max(x, y); }
signed main() {
    memset(dp, -63, sizeof dp);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].p >> p[i].len;
    p[++n] = (Pos) { 0, 0 };
    sort(p + 1, p + n + 1, [](Pos a, Pos b) { return a.p < b.p; });
    int pos = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i].p == 0 && p[i].len == 0) 
            pos = i;
    }
    for (int i = 1; i <= n; i++) id[p[i].p] = i;
    for (int i = 1; i <= n; i++) dp[pos][pos][i][0] = dp[pos][pos][i][1] = 0;
    for (int d = 1; d <= n; d++) {
        for (int l = 1; l + d - 1 <= n; l++) {
            int r = l + d - 1;
            for (int k = 0; k <= n; k++) {
                int t;
                if (l != 1) {
                    t = p[l].p - p[l - 1].p;
                    k ? Cmax(dp[l - 1][r][k - 1][0], dp[l][r][k][0] + p[l - 1].len - k * t) : void();
                    Cmax(dp[l - 1][r][k][0], dp[l][r][k][0] - k * t);

                    t = p[r].p - p[l - 1].p;
                    k ? Cmax(dp[l - 1][r][k - 1][0], dp[l][r][k][1] + p[l - 1].len - k * t) : void();
                    Cmax(dp[l - 1][r][k][0], dp[l][r][k][1] - k * t);
                }
                if (r != n) {
                    t = p[r + 1].p - p[l].p;
                    k ? Cmax(dp[l][r + 1][k - 1][1], dp[l][r][k][0] + p[r + 1].len - k * t) : void();
                    Cmax(dp[l][r + 1][k][1], dp[l][r][k][0] - k * t);

                    t = p[r + 1].p - p[r].p;
                    k ? Cmax(dp[l][r + 1][k - 1][1], dp[l][r][k][1] + p[r + 1].len - k * t) : void();
                    Cmax(dp[l][r + 1][k][1], dp[l][r][k][1] - k * t);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) Cmax(ans, max(dp[1][n][i][0], dp[1][n][i][1]));
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：2017gdgzoi999 (赞：0)

贪心分析可知任意时刻被熄灭的蜡烛一定是连续的区间，且包括原点。设熄灭的区间为 $[l,r]$，则下一步操作可以将该区间扩展到 $[l',r]$ 或 $[l,r']$（$l'<l,r<r'$）。换句话说，对于原点同一侧的点，离原点近的点一定比离原点远的点早熄灭。

经过 $t$ 时间后，蜡烛 $i$ 的长度是 $\max(0,a_i-t)$，考虑去除最大值操作。

设 $d$ 支蜡烛在烧尽前被熄灭了，那么剩下的 $n-d$ 支蜡烛最终长度为 $0$，对答案没有贡献，可忽略。

对于我们关心的 $d$ 支蜡烛，设按熄灭的顺序排序，它们位置为 $p_1,\dots p_d$、初始长度为 $l_1,\dots l_d$，为方便另设 $p_0=0$。因为选中的蜡烛不会被燃尽，因此剩余的长度为 $\sum_{i=1}^d(l_i-(d-i+1)(|p_i-p_{i-1}|))$，感性理解即为：

- 从起点到第 $1$ 支蜡烛的路程，每跑一单位长度，所有 $d$ 支蜡烛长度都减少了 $1$。

- 从第 $1$ 支蜡烛到第 $2$ 支蜡烛的路程，每跑一单位长度，$d-1$ 支未熄灭的蜡烛长度都减少了 $1$......

- 从第 $d-1$ 支蜡烛到第 $d$ 支蜡烛的路程，每跑一单位长度，最后 $1$ 支未熄灭的蜡烛长度减少了 $1$。

枚举 $d$，结合上述区间的贪心结论，设 $f_{l,r,k,0/1}$ 表示当前熄灭了 $[l,r]$ 区间的 $k$ 支蜡烛（并且不会再熄灭该区间其它蜡烛），当前在 $l/r$ 位置时，这 $k$ 支蜡烛剩余长度总和的最大可能值。实际上选中的蜡烛是否真未燃尽无需考虑，因为不再选中燃尽的蜡烛后答案一定更优。

时间复杂度 $\Theta(n^4)$，不足以通过。考虑将熄灭的过程反转处理。

- 倒数第 $1$ 段路程，每跑一单位长度，$1$ 支蜡烛长度减少了 $1$。

- 倒数第 $2$ 段路程，每跑一单位长度，$2$ 支蜡烛长度减少了 $1$......

- 倒数第 $d$ 段路程，每跑一单位长度，$d$ 支蜡烛长度减少了 $1$。

反转后的转移方程只和 $k$ 有关，无需枚举 $d$，时间复杂度降至 $\Theta(n^3)$，可以通过。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MAXN = 310;
const ll INF = 1000000000000000000LL;

struct node {
	int p; ll l;
} pa[MAXN], pb[MAXN];
ll dp[MAXN][MAXN][MAXN][2];

bool comp1(node a, node b) {
	return a.p<b.p;
}
bool comp2(node a, node b) {
	return a.p>b.p;
}
int main() {
	int n, na=0, nb=0; scanf("%d",&n);
	ll mv = 0LL;
	while (n--) {
		int x; ll l; scanf("%d%lld",&x,&l);
		if (ll(abs(x))>l) continue;
		if (x>0) pa[++na]=(node){x,l};
		else if (x<0) pb[++nb]=(node){x,l};
		else mv+=l; // 特判原点的蜡烛
	}
	sort(pa+1,pa+na+1,comp1); sort(pb+1,pb+nb+1,comp2); n=na+nb;
	pa[++na]=(node){1000000001,0LL}; pb[++nb]=(node){-1000000001,0LL}; // 镶边，防止边缘的蜡烛被忽略
	for (int i=0; i<=na; ++i) {
		for (int j=0; j<=nb; ++j) {
			dp[1][i][j][0]=pa[i].l; dp[1][i][j][1]=pb[j].l;
		}
	}
	ll res = 0LL;
	for (int d=1; d<=n; ++d) { // 考虑倒数第 d 支熄灭的蜡烛
		for (int i=0; i<=na; ++i) {
			for (int j=0; j<=nb; ++j) dp[d+1][i][j][0]=dp[d+1][i][j][1]=-INF;
		}
		for (int i=na; i>=0; --i) {
			for (int j=nb; j>=0; --j) {
				if (i) {
					ll tmp = dp[d][i][j][0]-ll(d)*ll(pa[i].p-pa[i-1].p);
					dp[d][i-1][j][0] = max(dp[d][i-1][j][0],tmp); // 不选蜡烛 i-1，总和不变
					dp[d+1][i-1][j][0] = max(dp[d+1][i-1][j][0],tmp+pa[i-1].l); // 选蜡烛 i-1，总和加上该蜡烛原长减路程上的损失
					dp[d+1][i-1][j][0] = max(dp[d+1][i-1][j][0],dp[d][i][j][1]-ll(d)*ll(pa[i-1].p-pb[j].p)+pa[i-1].l);
				}
				if (j) {
					ll tmp = dp[d][i][j][1]-ll(d)*ll(pb[j-1].p-pb[j].p);
					dp[d][i][j-1][1] = max(dp[d][i][j-1][1],tmp);
					dp[d+1][i][j-1][1] = max(dp[d+1][i][j-1][1],tmp+pb[j-1].l);
					dp[d+1][i][j-1][1] = max(dp[d+1][i][j-1][1],dp[d][i][j][0]-ll(d)*ll(pa[i].p-pb[j-1].p)+pb[j-1].l);
				}
				res = max(res,max(dp[d][i][j][0]-ll(d)*ll(pa[i].p),dp[d][i][j][1]+ll(d)*ll(pb[j].p))); // 计算原点到第一支蜡烛路程上的损失
			}
		}
	}
	printf("%lld", res+mv);
	return 0;
}
```

---

