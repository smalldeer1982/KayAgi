# [USACO24OPEN] Activating Robots P

## 题目描述

你和一个机器人初始时位于周长为 $L$（$1\le L\le 10^9$）的圆上的点 $0$ 处。你可以以每秒 $1$ 
单位的速度沿圆周顺时针或逆时针移动。本题中的所有移动都是连续的。

你的目标是放置恰好 $R-1$ 个机器人，使得最终每两个相邻的机器人彼此相距 $L/R$（$2\le R\le 20$，$R$ 整除 $L$）。有 $N$（$1\le N\le 10^5$）个激活点，其中第 $i$ 个激活点位于距点 $0$ 逆时针方向 $a_i$ 距离处（$0\le a_i<L$）处。如果你当前位于一个激活点，你可以立刻在该点放置一个机器人。所有机器人（包括初始的）均以每 $K$ 秒 $1$ 单位的速度逆时针移动（$1\le K\le 10^6$）。

计算达到目标所需要的最小时间。 

## 说明/提示

### 样例解释 1

我们可以通过顺时针移动在 $4$ 秒内到达点 $6$ 的激活点。此时，初始的机器人将位于点 $2$。再等待 $18$ 秒直到初始机器人位于点 $1$。现在我们可以放置一个机器人以立即获胜。 

### 样例解释 2

我们可以通过顺时针移动在 $3$ 秒内到达点 $7$ 的激活点。此时，初始的机器人将位于点 $1.5$。再等待一秒直到初始机器人位于点 $2$。现在我们可以放置一个机器人以立即获胜。 

### 测试点性质

- 测试点 $5-6$：$R=2$。
- 测试点 $7-12$：$R\le 10,N\le 80$。
- 测试点 $13-20$：$R\le 16$。
- 测试点 $21-24$：没有额外限制。

## 样例 #1

### 输入

```
10 2 1 2
6```

### 输出

```
22```

## 样例 #2

### 输入

```
10 2 1 2
7```

### 输出

```
4```

## 样例 #3

### 输入

```
32 4 5 2
0 23 12 5 11```

### 输出

```
48```

## 样例 #4

### 输入

```
24 3 1 2
16```

### 输出

```
48```

# 题解

## 作者：EnofTaiPeople (赞：6)

如果你通关铂金组了，那么你就没有**贝提拔**的机会了。

难道这道题就我需要卡常吗？虽然我知道有复杂度更优的做法。

考虑将状态压缩到极致，设 $f_{S,x}$ 表示集合 $S$ 的位置被放置了，最后一个放置的位置是 $x$ 的最早时间。

这个状态也压缩了当前的人的位置，这样之所以不会漏情况，是因为人不比 robotto 慢，所以能在一个较早的时刻达到该状态就一定能在较晚的时刻到达。

每次考虑新放置的 robotto，这是有两种情况，也就是小学奥数中的相遇问题和追及问题，我们可以暂时忽略关键点的限制，从相遇和追及的角度找到该 robotto 和人的最早相遇时间，然后 `std::lower_bound` 求出相遇后碰到的第一个关键点即可。

这里时间复杂度 $O(R^22^R\log n)$，理论上擦边能过，但我刚开始写的代码常数太大，于是考虑如何卡常。

发现比最终答案早的状态（一般只能卡到）$O(2^R)$ 个，考虑使用优先队列维护 dp，这样一般数据的复杂度是 $O(R2^R(R+\log n))$ 的，可以通过。

欢迎 Hack，不过后面卡了常所以直接转移也能过：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=(1<<19)+100;
int n,L,R,a[N],f[N*23],K,ans,v1,v2,cntt;
int dst(int l,int r){
    l=abs(l-r);
    return min(l,L-l);
}
priority_queue<pair<int,int>>q1;
bitset<N*23>vs;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,p,q;
    cin>>L>>R>>n>>K;
    for(x=1;x<=n;++x)cin>>a[x];
    sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
    a[n+1]=a[1]+L;
    for(k=0;k<(1<<R-1);++k)
        for(x=0;x<R;++x)f[k*R+x]=L+L+1;
    q1.emplace(f[0]=0,0);
    ans=L+L+1;
    while(1){
        x=q1.top().second,q1.pop();
        if(vs[x])continue;
        vs[x]=1,v1=f[x],k=x/R,x%=R;
        p=(v1+x*(L/R))%L;
        if(k==(1<<R-1)-1){
            printf("%lld\n",1ll*v1*K);
            return 0;
        }
        for(y=1;y<R;++y){
            if((k>>y-1)&1)continue;
            q=(v1+y*(L/R))%L;
            v2=((p-q+L)%L+K)/(K+1);
            if(K>1){
                if(q<p)q+=L;
                v2=min(v2,(q-p-1)/(K-1)+1);
            }
            r=(k|(1<<y-1))*R+y,v2+=v1;
            q=(v2+y*(L/R))%L;
            v2+=*lower_bound(a+1,a+n+1,q)-q;
            if(f[r]>v2)q1.emplace(-(f[r]=v2),r);
        }
    }
}
```

---

## 作者：daiyulong20120222 (赞：3)

此题解为 USACO 官方[题解](https://usaco.org/current/data/sol_prob3_platinum_open24.html)。

## Subtask 1

我们只需要激活一个机器人。让我们对所有可能的激活点进行迭代。如果激活点是 $x$，那么我们花费 $\min(x,L-x)$ 时间来达到该点。然后我们需要等待原始机器人到达圆上的点 $y=x+\Large\frac{L}{2}$。假设 $0≤y<L$（必要时取模），则原始机器人在 $Ky$ 首次到达 $y$。如果在到达 $x$ 之前发生这种情况，则我们需要等待另一个周期的时间 $K(y+L)$。所有激活点的最小值就是答案。

```C++
#include <bits/stdc++.h>
using namespace std;

const int64_t INF = numeric_limits<int64_t>::max();

void chmin(int64_t& x, int64_t y) {
  x = min(x, y);
}

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int l, r, n, k;
  cin >> l >> r >> n >> k;
  vector<int> a(n);
  for (int& x: a) cin >> x;
  int64_t ans = INF;
  for (int x: a) {
    int t = min(x, l-x);
    int opposite_position = (x + l/2) % l;
    int64_t time_to_reach = 1LL * opposite_position * k;
    if (time_to_reach < t) time_to_reach += 1LL * l * k; // definitely >= t now
    chmin(ans, time_to_reach);
  }
  cout << ans << '\n';
}
```
## Subtask 2

我们需要激活 $R-1$ 机器人。标记这些额外的机器人 $0,1,…,R-2$，使机器人 $i$ 与原始机器人的距离为逆时针 $\Large\frac{L}{R}$ $(i+1)$。对于子集 $S⊆\{0,1,…,R-2\}$ 和 $1≤i≤n$，设 $dp[S][i]$ 是到达激活点 $a_i$ 的最短时间，并激活 $S$ 中的所有机器人。转换如下：从状态 $(S,i)$，我们可以为下一步选择激活点 $a_j$ 和机器人 $k$。我们尽可能快地从 $a_i$ 走到 $a_j$，然后下次发现机器人k应该在的位置与 $a_j$ 对齐。然后我们可以转换到状态 $(S∪\{k\},j)$。基本情况的实现略有不同，因为原始位置 $0$ 不一定是激活点。

时间复杂度为 $O(2^RRN^2)$。

```C++
#include <bits/stdc++.h>
using namespace std;

const int64_t INF = numeric_limits<int64_t>::max();

void chmin(int64_t& x, int64_t y) {
  x = min(x, y);
}

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int l, r, n, k;
  cin >> l >> r >> n >> k;
  vector<int> a(n);
  for (int& x: a) cin >> x;
  const int64_t ROBOT_PERIOD = 1LL*l*k;

  auto dist = [&] (int x, int y) {
    return min(abs(x - y), l - abs(x - y));
  };
  auto get_next_time = [&] (int i, int j, int64_t t) {
    // given the ith robot after the initial robot, find the next time >= t
    // when it lines up with activiation point j

    // the time must be congruent to k*(a[j] - (l/r) * (i+1)) modulo l*k
    int64_t residue = 1LL * k * (a[j] - (l/r) * (i+1)) % ROBOT_PERIOD;
    if (residue < 0) residue += ROBOT_PERIOD;
    int64_t z = ROBOT_PERIOD * (t/ROBOT_PERIOD) + residue;
    if (z >= t) return z;
    else return z + ROBOT_PERIOD;
  };

  vector<vector<int64_t>> dp(1<<(r-1), vector<int64_t>(n, INF));
  // dp[mask][i] = shortest amount of time to be at a[i] and
  // have all the robots in the set represented by mask placed
  for (int i = 0; i < r-1; i++) {
    for (int j = 0; j < n; j++) {
      dp[1<<i][j] = get_next_time(i, j, dist(0, a[j]));
    }
  }
  for (int mask = 1; mask < (1<<(r-1)); mask++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < r-1; k++) {
          if (mask & (1<<k)) continue;
          chmin(
            dp[mask|1<<k][j],
            get_next_time(k, j, dp[mask][i] + dist(a[i], a[j]))
          );
        }
      }
    }
  }
  int64_t ans = INF;
  for (int i = 0; i < n; i++) {
    chmin(ans, dp[(1<<(r-1))-1][i]);
  }
  cout << ans << '\n';
}
```

## Subtask 3

处理这一部分的一种方法是将 $\Large\frac1K$ 的顺时针速度应用于问题中的所有内容，这样机器人就不会移动。然后激活点以 $\Large\frac1K$ 的速度顺时针移动，我们可以以 $\Large\frac{K-1}{K}$ 逆时针或 $\Large\frac{K+1}{K}$ 顺时针的速度移动。现在的关键观察结果是，以前我们要去一个激活点，等待激活下一个机器人，而现在我们应该做的是去机器人的位置，等待下一个激活点通过。（注意，$K≥1$ 很重要，否则我们将始终顺时针移动，无法选择在机器人的位置等待。）

设 $dp[S][i]$ 表示使S中的所有机器人被激活并处于机器人i的位置的最短时间。从状态 $(S,i)$，我们选择下一个要激活的机器人 $j$，并尽可能快地从机器人 $i$ 的位置走到机器人 $j$ 的位置（记住，我们以逆时针和顺时针不同的速度走）。然后我们找到下一个激活点经过的时间。这可以通过对激活点进行二进制搜索来完成。

时间复杂度为 $O(N\log N+2^RR^2\log N)$，用于对初始激活点进行排序，然后将转换次数乘以二进制搜索步骤的 $\log N$ 因子。

```C++
#include <bits/stdc++.h>
using namespace std;

const int64_t INF = numeric_limits<int64_t>::max();

void chmin(int64_t& x, int64_t y) {
  x = min(x, y);
}

int64_t ceil(int64_t x, int64_t y) {
  return (x + y - 1) / y;
}

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int l, r, n, k;
  cin >> l >> r >> n >> k;
  vector<int> a(n);
  for (int& x: a) cin >> x;
  sort(a.begin(), a.end());

  auto dist = [&] (int x, int y) {
    int cw_dist = (x - y + l) % l;
    int64_t ans = ceil(1LL*k*cw_dist, k+1);
    if (k > 1) chmin(ans, ceil(1LL*k*(l-cw_dist), k-1));
    return ans;
  };
  vector<int> diff_to_dist(r);
  for (int i = 0; i < r; i++) diff_to_dist[i] = dist(0, (l/r)*i);
  auto get_next_time = [&] (int i, int64_t t) {
    // given the ith robot after the initial robot, find the next time >= t
    // when it lines up with some activation point

    // robot is at position (l/r) * (i+1) + t/k on the circle, we are looking for the next activation point after that
    int residue = ((l/r) * (i+1) + ceil(t, k)) % l;
    auto it = lower_bound(a.begin(), a.end(), residue);
    int dist_to_next = (it == a.end() ? l + a[0] : *it) - residue;
    return 1LL * k * (dist_to_next + ceil(t, k));
  };

  vector<vector<int64_t>> dp(1<<(r-1), vector<int64_t>(r-1, INF));
  // dp[mask][i] = shortest amount of time to have robots in the set represented by mask placed
  // and be aligned with the ith robot after the original
  for (int i = 0; i < r-1; i++) {
    dp[1<<i][i] = get_next_time(i, dist(0, (l/r)*(i+1)));
  }

  for (int mask = 0; mask < (1<<(r-1)); mask++) {
    for (int i = 0; i < r-1; i++) {
      if (!(mask & (1<<i))) continue;
      for (int j = 0; j < r-1; j++) {
        if (mask & (1<<j)) continue;
        chmin(
          dp[mask|1<<j][j],
          get_next_time(j, dp[mask][i] + diff_to_dist[(j-i+r)%r])
        );
      }
    }
  }
  cout << *min_element(dp.back().begin(), dp.back().end()) << '\n';
}
```

请注意，此实现预先计算阵列 $\tt diff\_to\_list$ 中机器人位置之间的移动时间，这是相对于执行每个转换的计算而言相当显著的常数因子改进。

## 完整解决方案

我们只需要对子任务 $3$ 的解决方案进行一点改进。对于给定的状态 $(S,i)$，达到该状态的时间是从过渡到该状态的最小时间。对于每个过渡，我们必须计算一个时间，然后进行二进制搜索，将其增加到下一个激活点到达的时间。相反，我们可以重新排序这些步骤：在没有等待下一个激活点的步骤的情况下找到最短时间，然后只执行一次二进制搜索步骤来等待下一激活点。时间复杂度为 $O(N\log N+2^RR(R+\log N))$。

为了便于说明，我们将仅显示与子任务 $3$ 解决方案（即主循环）相比的差异：

```C++
...
  for (int mask = 0; mask < (1<<(r-1)); mask++) {
    for (int i = 0; i < r-1; i++) {
      if (!(mask & (1<<i))) continue;
      dp[mask][i] = get_next_time(i, dp[mask][i]);
      for (int j = 0; j < r-1; j++) {
        if (mask & (1<<j)) continue;
        chmin(
          dp[mask|1<<j][j],
          dp[mask][i] + diff_to_dist[(j-i+r)%r]
        );
      }
    }
  }
...
```

## 总体时间复杂度

尝试在 $O(N\log N+(N+2^R)R)$ 时间复杂度内解决这个问题。

---

## 作者：Larunatrecy (赞：3)

首先有个 naive 的 $O(R2^RN^2)$ 做法，设 $dp_{S,i}$ 表示激活了 $S$ 内的机器人，当前在第 $i$ 个激活点的最小时间，转移枚举下一个激活点即可。

考虑转化一下，给所有东西加一个顺时针的，$\frac{1}{K}$ 单位每秒的速度，那么现在，机器人就不会动了，激活点会以该速度移动，人也还可以移动，只是顺时针和逆时针移动速度不一样。

假设我们想要在某个点放一个机器人，因为此时是激活点在动，所以我们的最优策略显然是等到第一个转过来的激活点然后操作，这个可以二分得到。

设 $dp_{S,i}$ 为激活了 $S$ 内的机器人，上一次激活的是 $i$，转移时枚举下一个激活的机器人，并二分算一下时间，复杂度 $O(2^RR^2\log n)$。

注意到我们可以先不二分，我们对于每个状态，先算出**不考虑等待时间的最小时刻**，等到计算完成后，再对着这个最小时刻二分得到 $dp_{S,i}$。

复杂度 $O(2^RR(R+\log n))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+7;
typedef long long LL;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
    x=(f?-x:x);
}
const int M = (1<<20)+7;
LL dp[M][22];
LL L,K,D;
int n,m;
LL a[N];
void ckmin(LL &x,LL v){x=min(x,v);}
LL ceil(LL x,LL y)
{
    return (x+y-1)/y;
}
LL dist(LL x,LL y)
{
    LL d=(x-y+L)%L;
    LL ans=ceil(K*d,K+1);
    if(K>1)ans=min(ans,ceil(K*(L-d),K-1));
    return ans;
}
LL solve(int i,LL t)
{
    LL P=(D*(i+1)+ceil(t,K))%L;
    int p=lower_bound(a+1,a+n+1,P)-a;
    LL d=a[p]-P;
    return K*(d+ceil(t,K));
}
LL dis[N];
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.ans","w",stdout);
    read(L);read(m);read(n);read(K);D=L/m;
    for(int i=1;i<=n;i++)read(a[i]);
    sort(a+1,a+n+1);a[++n]=a[1]+L;
    for(int S=0;S<(1<<(m-1));S++)for(int i=0;i<m-1;i++)dp[S][i]=1e18;
    for(int i=0;i<m-1;i++)dp[(1<<i)][i]=dist(0,D*(i+1));
    for(int i=0;i<m;i++)dis[i]=dist(0,D*i);
    for(int S=0;S<(1<<(m-1));S++)
    for(int i=0;i<m-1;i++)if((S>>i)&1)
    {
        dp[S][i]=solve(i,dp[S][i]);
        for(int j=0;j<m-1;j++)if(!((S>>j)&1))
        ckmin(dp[S^(1<<j)][j],dp[S][i]+dis[(j-i+m)%m]);
    }
    LL mn=1e18;
    for(int i=0;i<m-1;i++)mn=min(mn,dp[(1<<(m-1))-1][i]);
    cout<<mn;
    return 0;
}
```

---

## 作者：Caiest_Oier (赞：1)

# [P10285](https://www.luogu.com.cn/problem/P10285)    

数据范围一眼状压。考虑要记录的状态，记当前哪些机器人被放置了（第一个机器人必须被放置），然后再记录一下当前和哪个机器人在一起。状态数是 $O(R\times2^R)$ 的。记录到达这样的状态，所需要的最短时间。这个状态显然是根据新的机器人的放置来转移的。因为记录了最短时间，与当前所在的机器人位置，于是可以算出当前在哪个激活点上。     

对于转移，枚举下一个激活的机器人位置，最优的操作显然是先走到那个机器人的预定位置上，然后和机器人圈一起旋转，直到转到一个激活点，放置机器人。走过去所需要的最短时间可以 $O(1)$ 计算，但是要计算下一个激活点的位置的话，需要一个二分，复杂度就变成 $O(2^RR^2\log n)$ 了，不是很能过的样子。       

为了降低复杂度，我们预处理一点东西。上述的情况相当于，当前自身在一个激活点 $i$ 上，需要走到顺时针第 $j$ 个机器人的预定位置后，跟着转到激活点上。发现状态数是 $O(nR)$ 的，于是可以 $O(nR\log n)$ 预处理，所以复杂度就降到了 $O(nR\log n+2^RR^2)$。      

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int L,R,n,k,a[300003],dis[100003][21],dp[(1<<20)][21],lft,rgt,mid,wz,k1,k2,k3,k4,k5,ans;
double tim;
int sqz(int X,int Y){
    if(X%Y!=0)return (X/Y)+1;
    return (X/Y);
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>L>>R>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    for(int i=n+1;i<=3*n;i++)a[i]=a[i-n]+L;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=R;j++){
            if(k!=1)wz=a[i]+j*(L/R)+min(sqz((R-j)*(L/R),k+1),sqz(j*(L/R),k-1));
            else wz=a[i]+j*(L/R)+sqz((R-j)*(L/R),k+1);
            lft=1;
            rgt=3*n;
            while(lft<rgt){
                mid=((lft+rgt)>>1);
                if(a[mid]>=wz)rgt=mid;
                else lft=mid+1;
            }
            dis[i][j]=k*(a[lft]-(a[i]+j*(L/R)));
        }
    }
    memset(dp,-1,sizeof(dp));
    dp[1][1]=0;
    for(int i=1;i<(1<<R)-1;i+=2){
        for(int j=1;j<=R;j++){
            if((i&(1<<j-1))==0)continue;
            if(dp[i][j]==-1)continue;
            wz=(L/R)*(j-1)+dp[i][j]/k;
            while(wz>=L)wz-=L;
            lft=1;
            rgt=n+1;
            while(lft<rgt){
                mid=((lft+rgt)>>1);
                if(a[mid]>=wz)rgt=mid;
                else lft=mid+1;
            }
            wz=lft;
            if(wz>n)wz-=n;
            if(i==1&&j==1)wz=0;
            for(int u=1;u<=R;u++){
                if((i&(1<<(u-1)))!=0)continue;
                if(u>j)k1=u-j;
                else k1=(u+R-j);
                if(dp[i+(1<<(u-1))][u]==-1||dp[i+(1<<(u-1))][u]>dp[i][j]+dis[wz][k1])dp[i+(1<<(u-1))][u]=dp[i][j]+dis[wz][k1];
            }
        }
    }
    ans=dp[(1<<R)-1][1];
    for(int i=2;i<=R;i++){
        if(dp[(1<<R)-1][i]==-1)continue;
        if(ans==-1||dp[(1<<R)-1][i]<ans)ans=dp[(1<<R)-1][i];
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Shui_Dream (赞：0)

分享一个无脑的做法。
看到数据范围猜测是指数级算法。考虑记录 $f[S][i]$ 表示激活了集合 $S$ 内的机器人，最后一个机器人是第 $i$ 个。这里的第i个指的是第 $0$ 秒时逆时针第 $i$ 个机器人。机器人每 $K$ 秒移动一格，但是编号不变。那么这样设状态显然状态值越小越好，正确性无误。

考虑贪心策略，先让人花最少的时间和想要激活的机器人重合，然后再以 $K$ 秒一步的速度走到激活点。

转移时可以算出来重合的时间，可以得到机器人位置，二分得到最近的激活点。

考虑转移到 $j$，由定义，第 $i$ 个机器人第 $f[S][i]$ 秒时一定在某一个激活点，用 map 去存，所以转移可以统一表示成 $g[k][j]$，从第 $k$ 个激活点出发，让第 $k$ 激活点逆时针第 $j$ 个机器人走到激活点并激活的最小时间。

转移有 $f[S | 2^j][j]\leftarrow f[S][i]+g[k][j-i \bmod R]$。

总复杂度为 $O(nR+2^RR(R+\log n))$

```cpp
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
inline int read(){
    char ch=getchar();
    while(!isdigit(ch) && ch!='-') ch=getchar();
    int x=0,ff=1; if(ch=='-') ff=-1,ch=getchar();
    while(isdigit(ch)) x=(x<<3) + (x<<1) + (ch^48),ch=getchar();
    return x*ff;
}
const int N=22,N2=1e5+5,M=(1<<20)+5; const LL inf=1e18;
LL ceil(LL x,LL y){ return y?(x+y-1)/y:inf; }
int L,m,D,n,K,S,a[N2]; LL f[M][N],g[N2][N],zd[N]; map<int,int> mp;
LL gwt(int x){
	int z=lower_bound(a+1,a+n+1,x)-a;
	return 1ll*(a[z]-x)*K;
}
int main(){
	L=read(); m=read(); n=read(); K=read(); D=L/m;
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1); a[n+1]=a[1]+L; --m; S=1<<m; 
	for(int i=1;i<=m;i++){ int d=i*D;
		zd[i]= min(ceil(d,K-1),ceil(L-d,K+1))*K; }
	for(int i=1;i<=n;i++){ mp[a[i]]=i;
		for(int j=1;j<=m;j++) g[i][j]=zd[j]+gwt((a[i]+j*D+zd[j]/K)%L);
	}
	for(int i=1;i<S;i++) for(int j=0;j<m;j++) f[i][j]=inf;
	for(int i=1;i<=m;i++) f[1<<(i-1)][i-1]=zd[i]+gwt((i*D+zd[i]/K)%L);
	for(int s=1;s<S-1;s++) 
		for(int i=0;i<m;i++) if((s>>i) & 1){
			int sx=mp[((i+1)*D+f[s][i]/K)%L];
			for(int j=0;j<m;j++) if(!((s>>j) & 1))
				f[s | (1<<j)][j] = min(f[s | (1<<j)][j],f[s][i]+g[sx][(j-i+m+1)%(m+1)]);
		}
	LL ans=inf; for(int i=0;i<m;i++) ans=min(ans,f[S-1][i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

