# [ABC358G] AtCoder Tour

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc358/tasks/abc358_g

AtCoder Land は $ H $ 行 $ W $ 列のグリッドで表されます。上から $ i $ 番目、左から $ j $ 番目のマスを $ (i,\ j) $ と表記します。

高橋君ははじめマス $ (S_i,\ S_j) $ におり、以下の行動を $ K $ 回繰り返します。

- 高橋君は現在いるマスに留まるか、隣のマスに移動する。その後の時点で高橋君がいるマスを $ (i,\ j) $ として $ A_{i,\ j} $ の楽しさを得る。
 
高橋君が得ることのできる楽しさの合計の最大値を求めてください。

ただし、マス $ (x',\ y') $ がマス $ (x,\ y) $ の隣のマスであるとは $ |x\ -\ x'|\ +\ |y\ -\ y'|\ =\ 1 $ であることを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 50 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ S_i\ \leq\ H $
- $ 1\ \leq\ S_j\ \leq\ W $
- $ 1\ \leq\ A_{i,\ j}\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

高橋君は以下のように行動することで楽しさの合計を $ 14 $ にすることができます。 - はじめ、高橋君は $ (1,\ 2) $ にいる。 - 高橋君はマス $ (2,\ 2) $ に移動する。その後、$ A_{2,\ 2}\ =\ 4 $ の楽しさを得る。 - 高橋君はマス $ (2,\ 3) $ に移動する。その後、$ A_{2,\ 3}\ =\ 5 $ の楽しさを得る。 - 高橋君はマス $ (2,\ 3) $ に留まる。その後、$ A_{2,\ 3}\ =\ 5 $ の楽しさを得る。 高橋君は楽しさの合計を $ 14 $ より大きくすることはできないため、$ 14 $ を出力します。

## 样例 #1

### 输入

```
2 3 3
1 2
2 1 2
3 4 5```

### 输出

```
14```

## 样例 #2

### 输入

```
2 2 1000000000
2 1
100 100
100 99```

### 输出

```
100000000000```

# 题解

## 作者：沉石鱼惊旋 (赞：14)

# 题目翻译

给定 $n\times m$ 的网格，每个格子里有一个正整数 $a_{i,j}$。你需要在从 $(sx,sy)$ 开始，执行 $k$ 次操作。每一操作可以选择不动或者走到任意一个四联通（上下左右）的格子。操作之后，可以获得所在格子的 $a_{i,j}$ 的收益。

$1\leq n,m\leq 50$

# 题目思路

可以证明，选择的路线一定是，移动若干步（可以是 $0$ 步）然后一直停留在一个格子获得收益。假设你选定了一条路径作为答案，那么你走到这条路径上的最大值后一直停留，一定是不比继续往后走差的。也不会出现在一个格子停一会儿转下一个更大的格子，因为这样不如把之前停留的步数留给后面更大的格子。

---

做法一：

考虑到停留在一个格子获得收益部分与你移动所花步数相关，因此，我们不妨枚举『行走步数』。设 $f_{i,x,y}$ 表示走了 $i$ 步停留在 $(x,y)$ 的收益最大路径所得到的收益。

转移枚举『行走步数』$i$，『起始点』$(x,y)$，『方向』，通过『起始点』和『方向』可以得到『目标点』$(tx,ty)$，转移即为 $f_{i+1,tx,ty}\gets \max f_{i,x,y}+a_{tx,ty}$。

但是，『行走步数』很大。可是稍微想一下就可以发现至多 $\mathcal O(n^2)$ 步就能到达。虽然说用 $\mathcal O(n)$ 步一定能从任意一点出发，到达网格任意一点。但是收益会有区别。例如下面这组数据：

```cpp
6 3 1000000000
6 1
100 100 100
100 1 100
100 1 100
100 1 100
100 1 100
100 1 101
```

虽然可以从 $(6,1)$ 两步到 $(6,3)$，但是经过 $1$ 收益太差了。我们必须要绕过 $1$ 走。

因此形如上方的网格，构造一个大数填充，小数做墙的网格，就可以强制走 $\mathcal O(n^2)$ 步。

因此状态是 $\mathcal O(n^4)$ 的，转移是 $\mathcal O(1)$ 的。

$n,m$ 同阶，时间复杂度 $\mathcal O(n^4)$。

---

做法二：

考虑枚举『最后停在哪一个格子』$(ex,ey)$。

那么你每次移动到 $(tx,ty)$ 的代价相较于待在 $(ex,ey)$，代价就是 $a_{ex,ey}-a_{tx,ty}$。

之后直接建图跑最短路。

负数边权可以直接忽略，因为你走到大的没有必要继续走下去，而显然这个更大的点之后会被枚举到。从而将图转化为非负权图，可以使用 Dijkstra 求解。

那么答案即为 $a_{ex,ey}\times k-dis((sx,sy),(ex,ey))$。也就是停在一直最后格子的收益减去赶路时间。

$n,m$ 同阶，时间复杂度 $\mathcal O(n^4\log n)$。

# 部分代码

[Code by @cayaxi09](https://atcoder.jp/contests/abc358/submissions/54574838)

这是我自己的代码。赛时看了一眼就会了，关键结论有点典，DP 部分也比较基础。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
typedef long long ll;
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
int n, m, k;
ll a[55][55];
int x, y;
ll dis[2520][55][55];
ll ans;
int main()
{
    cin >> n >> m >> k >> x >> y;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    ans = a[x][y] * k;
    auto in = [&](int x, int y)
    { return 1 <= x && x <= n && 1 <= y && y <= m; };
    memset(dis, 128, sizeof(dis));
    dis[0][x][y] = 0;
    for (int i = 1; i <= min(n * m, k); i++)
    {
        for (int x = 1; x <= n; x++)
        {
            for (int y = 1; y <= m; y++)
            {
                for (int _ = 0; _ < 4; _++)
                {
                    int tx = x + dx[_];
                    int ty = y + dy[_];
                    if (!in(tx, ty))
                        continue;
                    chkmx(dis[i][tx][ty], dis[i - 1][x][y] + a[tx][ty]);
                }
            }
        }
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= m; y++)
                chkmx(ans, dis[i][x][y] + a[x][y] * (k - i));
    }
    cout << ans << endl;
    return 0;
}
```

[Code by @hitoare](https://atcoder.jp/contests/abc358/submissions/54586348)

滚动数组写法，空间复杂度更优，时间复杂度无差别。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double

int main() {
    ll H, W, K;
    cin >> H >> W >> K;
    ll sx, sy;
    cin >> sx >> sy;
    sx--;sy--;
    vector<vector<ll>> A(H, vector<ll>(W, 0));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> A[i][j];
    }

    vector<vector<ll>> from(H, vector<ll>(W, -2e18));
    from[sx][sy] = 0;
    for (int z = 0; z < 5000; z++) {
        if (K == 0) break;
        K--;
        vector<vector<ll>> to = from;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (i > 0) to[i][j] = max(from[i-1][j], to[i][j]);
                if (i < H-1) to[i][j] = max(from[i+1][j], to[i][j]);
                if (j > 0) to[i][j] = max(from[i][j-1], to[i][j]);
                if (j < W-1) to[i][j] = max(from[i][j+1], to[i][j]);
                to[i][j] += A[i][j];
            }
        }
        swap(from, to);
    }
    ll ans = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ans = max(ans, from[i][j]+K*A[i][j]);
        }
    }
    cout << ans << endl;

    return 0;
}
```

[Code by PCTprobability](https://atcoder.jp/contests/abc358/submissions/54570824)

写的是第二种做法。

```cpp
void dijkstra(ll s){
  for(int i=0;i<v;i++){
    d[i]=inf;
  }
  d[s]=0;
  priority_queue<P,vector<P>,greater<P>> que;
  que.push(P(0,s));
  while(!que.empty()){
    P p=que.top();
    que.pop();
    ll V=p.second;
    if(d[V]<p.first) continue;
    for(auto e:g[V]){
      if(d[e.to]>d[V]+e.cost){
        d[e.to]=d[V]+e.cost;
        que.push(P(d[e.to],e.to));
      }
    }
  }
}

int main(){
  cincout();
  ll n,m,v;
  cin>>n>>m>>v;
  ll p,q;
  cin>>p>>q;
  p--;
  q--;
  vector<vector<ll>> a(n,vector<ll>(m));
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++) cin>>a[i][j];
  }
  ll ans=-inf;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      graph g(n*m);
      vector<int> px={0,1,0,-1},py={1,0,-1,0};
      for(int x=0;x<n;x++){
        for(int y=0;y<m;y++){
          for(int k=0;k<4;k++){
            int nx=x+px[k],ny=y+py[k];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(a[nx][ny]>a[i][j]) continue;
            g.add_edge(x*m+y,nx*m+ny,a[i][j]-a[nx][ny]);
          }
        }
      }
      g.dijkstra(p*m+q);
      ll d=g.d[i*m+j];
      chmax(ans,a[i][j]*v-d);
    }
  }
  cout<<ans<<endl;
}
```

---

## 作者：kkxacj (赞：8)

#### 前言

因为我非常喜欢 `spfa`，所以我赛时用朴素的 `spfa` 通过了此题。

但建议打 `spfa` 的时候一定要加优先队列优化，不然会被卡。

#### 思路

很明显，如果高桥初始位置是值最大的，那么高桥会一直呆在这里。

否则，高桥会考虑移动到值比当前位置大的数去，但注意，**不一定是去最大的**，原因也很简单，随便举个例子：

最大的和次大的相差值为一，最大值为 $100$，次大为 $99$，其它位置值都是 $1$，当前位置到最大值的位置至少要花 $50$ 的时间，但到次大的只需要 $1$ 秒的时间，$k=60$，显然去次大的更优。

那怎么办呢？发现点只有 $2500$ 个，直接对于每个点都跑一遍就行了，但发现还有个时间限制，所以设 $sum_{i,j,z}$ 为从高桥开始站的的点 $s_1,s_2$ 到 $i,j$ 这个点用了 $z$ 秒最大值为多少。

这个时间 $z$ 不会超过 $2500$，因为我最多把每一个点都走一遍在到那里去。

那么最后算答案就好算了，直接枚举一下到 $i,j$ 点用 $z$ 秒最大值加上剩下的时间全呆在这的值，去最大值就行了。

如果你不想像我一样罚时的话，记得特判如果到不了就不算这次贡献。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int h,w,k,a[110][110],x,y,ans,sum[53][53][6200],l,r,c[10000010],d[10000010],e[10000010];
int fx[10]={-1,1,0,0};
int fy[10]={0,0,-1,1};
inline void bfs()
{
	while(l <= r)
	{
		for(int i = 0;i < 4;i++)
		{
			int x2 = c[l]+fx[i],y2 = d[l]+fy[i];
			if(x2 < 1 || y2 < 1 || x2 > h || y2 > w || e[l] == min(2500ll,k)) continue;
			if(sum[c[l]][d[l]][e[l]]+a[x2][y2]>sum[x2][y2][e[l]+1])
			{
				sum[x2][y2][e[l]+1] = sum[c[l]][d[l]][e[l]]+a[x2][y2];
				c[++r] = x2,d[r] = y2,e[r] = e[l]+1;
			}
		}
		l++;
	}
}
signed main()
{
	read(h),read(w),read(k),read(x),read(y);
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++)
			read(a[i][j]);
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++)
			for(int z = 0;z <= min(2500ll,k);z++)
				sum[i][j][z] = -1e17;
	sum[x][y][0] = 0;
	l = 1,r = 1,c[l] = x,d[l] = y,e[l] = 0;
	bfs();
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++)
			for(int z = 0;z <= min(2500ll,k);z++)
				if(sum[i][j][z] != -1e17)ans = max(ans,sum[i][j][z]+(k-z)*a[i][j]);
	print(ans); flush();
	return 0;
}

```

---

## 作者：Starrykiller (赞：5)

很显然，我们只需要走到数字最大的格子上，然后一直停留在那里就可以了。这样显然答案是最优的。

那么，只需要找到前往数字最大格子的路径。这个可以用类似 Dijkstra 的方法。

我们记状态为 $(x,y,k,w)$，表示当前在格子 $(x,y)$，走了 $k$ 步，最大权值为 $w$。在每个状态遍历到的时候，我们用“之后一直停留在这个格子”的答案尝试更新最大答案。

每个状态显然最多可以更新五个后继状态。从当前格子到达数字最大的格子最多只需要 $\Theta(nm)$ 步，所以我们的 $k$ 只需要搜到 $nm$。这样状态数是 $\Theta((nm)^2)$ 的。

[My submission](https://atcoder.jp/contests/abc358/submissions/54589393).

---

## 作者：ttq012 (赞：3)

### G

实际上 CF57E 也有一个（有点）类似的结论。

容易发现 $n\times m$ 步之后一定可以到达任意的一个结点。因此 $n\times m$ 步之后一定是停在某一个结点攒贡献。所以设 $f_{i,j,k}$ 表示当前走了 $i$ 步，目前位于结点 $(j,k)$ 的最大收益。很显然每一个 $f_{i,j,k}$ 都可以从 $(j,k)$ 结点本身和 $(j,k)$ 结点四连通的结点转移而来。

此时若 $k\le n\times m$ 则答案已经求出，$k>n\times m$ 则枚举最后到达的每一个结点 $(i,j)$，这个结点的最大贡献就是 $f_{n\times m,i,j}+(n\times m-k)\times a_{i,j}$。可能这个贡献并不一定是最大贡献，但是最大贡献一定可以通过这种方式得到。

时间复杂度为 $O(n^2m^2)$。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000100,mod=998244353;
int a[55][55],f[55*55][55][55];
//设f[i][j][k]表示现在是第i个操作, 当前位于(j,k)
signed main(){
    int n,m,k;
    cin>>n>>m>>k;
    int si,sj;
    cin>>si>>sj;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    cin>>a[i][j];
    memset(f,-0x3f,sizeof f);
    f[0][si][sj]=0;
    for(int i=1;i<=min(n*m,k);i++){
    for(int j=1;j<=n;j++)
        for(int k=1;k<=m;k++)
            f[i][j][k]=f[i-1][j][k]+a[j][k];
    for(int j=1;j<=n;j++)
        for(int k=1;k<=m;k++){
            const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
            for(int d=0;d<4;d++){
                int x=j+dx[d],y=k+dy[d];
                if(x>=1&&x<=n&&y>=1&&y<=m)
                    f[i][x][y]=max(f[i][x][y],f[i-1][j][k]+a[x][y]);
            }
        }
    }
    if(k<=n*m){
        int res=0;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        res=max(res,f[k][i][j]);
        cout<<res<<'\n';
    }else{
        int res=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                int now=f[n*m][i][j]+(k-n*m)*a[i][j];
                res=max(res,now);
            }
        cout<<res<<'\n';
    }
}
```

---

## 作者：_determination_ (赞：3)

史上最简单 G。

考虑 dp，有一个显然的 dp 状态是 $f_{i,j,k}$ 表示你现在在 $(i,j)$ 的位置走了 $k$ 步的最优解。这样因为 $k$ 是 $10^9$ 肯定会爆。

考虑优化。显然最优答案一定是走到一个地方之后一直停留。同时注意到走环一定是不优的。所以步数最多是 $n^2$ 即大约 2500 左右，直接 dp 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define debug cout << "114514" << endl
int n,m,w;
int x,y;
int xx[4]={0,1,0,-1},yy[4]={1,0,-1,0};
int a[60][60];
int f[60][60][4000];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m >> w;
    cin >> x >> y;
    for ( int i = 1 ; i <= n ; i++ )
    {
        for ( int j = 1 ; j <= m ; j++ )
        {
            cin >> a[i][j];
            for ( int k = 0 ; k <= n*m ; k++ )
            {
                f[i][j][k]=-inf;
            }
        }
    }
    f[x][y][0]=0;
    int ans=0;
    for ( int k = 1 ; k <= min(n*m,w) ; k++ )
    {
        for ( int i = 1 ; i <= n ; i++ )
        {
            for ( int j = 1 ; j <= m ; j++ )
            {
                f[i][j][k]=f[i][j][k-1];
                for ( int l = 0 ; l < 4 ; l++ )
                {
                    int nx=i+xx[l],ny=j+yy[l];
                    if(nx<1||ny<1||nx>n||ny>m)continue;
                    f[i][j][k]=max(f[i][j][k],f[nx][ny][k-1]);
                }
                f[i][j][k]+=a[i][j];
                ans=max(ans,(w-k)*a[i][j]+f[i][j][k]);
                // cout << f[i][j][k] << " ";
            }
            // cout << endl;
        }
        // cout << endl;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：lxyt_415x (赞：2)

## 题意

给定一个 $H$ 行 $W$ 列的矩阵，$S_i$ 和 $S_j$ 分别表示起点的横纵坐标，每个点都有分数 $A_{i,j}$，每次行动能走向当前相邻的点或停在原地，行动结束后获得所在点的分数，一共行动 $K$ 次，求最多能得到多少分数。

## 思路

考虑答案一定是走一条不重复的路径到一个点，然后一直停留在这里。那么可能对答案造成影响的就是停留的点和选择的路径，我们要做的就是枚举到达所有点的不重复路径。

设 $f_{t,i,j}$ 表示第 $t$ 次行动到第 $i$ 行 $j$ 列的的点最大路径，然后假设剩下的行动全都停留，对所有的假设取 $\max$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int fx[4]={1,-1,0,0},fy[4]={0,0,1,-1};
int n,m,k,si,sj,mp[55][55];
int f[3333][55][55],ans;
signed main()
{
	cin>>n>>m>>k;
	cin>>si>>sj;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&mp[i][j]);
	ans=k*mp[si][sj]+1;
	f[0][si][sj]=1;
	int mi=min(3000ll,k);
	for(int T=1;T<=mi;T++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				for(int k=0;k<4;k++)
					f[T][i][j]=max(f[T][i][j],f[T-1][i+fx[k]][j+fy[k]]);
				if(!f[T][i][j])
					continue;
				f[T][i][j]+=mp[i][j];
				ans=max(ans,f[T][i][j]+(k-T)*mp[i][j]);
			}
	cout<<ans-1;
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

笑点解析：$G\lt F$。

## 解题思路

注意到 $K$ 很大，考虑到最终的答案一定形如移动到某个点然后一直停留。

记 $f_{i,j,k}$ 表示走 $i$ 步到达 $j,k$ 的路上最大权值和。

转移显然是 $f_{i,j,k}\leftarrow a_{j,k}+f_{i-1,x,y},|x-j|+|y-k|\leq 1$。

我们每次计算得到这个值之后用 $f_{i,j,k}+(K-i)\times a_{j,k}$ 更新答案，表示走到这一步就停下了。

因为走到全图的极大值一定会停下，所以只需要转移 $\min(nm,K)$ 次即可。

时间复杂度 $O(n^2m^2)$。

---

## 作者：M1saka16I72 (赞：1)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc358-g.html)

## 思路

思路是简单的，使用分层图的思想递推地求出对于每个格子走了 $k\leq n\times m$ 步之后最大的价值（记为 $val_{x,y,k}$，递推式为 $val_{x,y,k}=\max\{val_{x',y',k-1}+a_{x,y}\},|x'-x|+|y'-y|\leq 1$），记 $mk=\min(k,n\times m)$，最后答案则是 $\max\{val_{x,y,mk}+a_{x,y}\times (k-mk)\}$，时间复杂度 $\mathcal{O}(n^2m^2)$。

这里证明一下“至多走 $n\times m$ 步之后就会停留在一个格子里”这个结论。

考虑反证法，假设用上文的方法求出来的答案为 $ans_0$，最后停在 $a_{x,y}$。有一条路径 $p$ 已经把所有 $n\times m$ 个格子都走过一遍了，却还在继续移动，没有停在一个格子里，最后得到的价值为 $ans_1$，且 $ans_1>ans_0$。

沿用上文的定义，则 $ans_1-\sum{a}>ans_0-\sum{a}$ 即 $ans_1-\sum{a}>a_{x,y}\times (k-mk)$。

这意味着 $p$ 经过的之后的格子里的价值总和的平均值一定高于 $a_{x,y}$，也就是一定 $\exist a_{x',y'}\in p,a_{x',y'}>a_{x,y}$；那么把所有格子走一遍然后停在 $a_{x',y'}$ 最后得到的价值一定高于原来的 $ans_0$，与一开始 $ans_0$ 为最优解的条件矛盾，于是结论得证。

## 代码

一些神必错误可能会使你 WA on #9，每个人的情况都不同，于是贴出代码供参考。

[link](https://atcoder.jp/contests/abc358/submissions/54617597)

---

## 作者：incra (赞：0)

### Solution
不难得出一个性质：路径一定是先移动到某一个位置，并在之后的路径中不变。

性质感觉挺显然的~~但是我不会证~~。

然后就设 $f_{l,x,y}$ 表示移动了 $l$ 步到达了 $(x,y)$ 时所有路径权值和的最大值，状态转移方程：$f_{l+1,x,y}=\max\{f_{l,i,j}\}+a_{i,j}$ 其中 $(i,j)$ 为 $(x,y)$ 的四联通的点之一。

那么答案也就出来了，为 $\displaystyle\max_{l\le k}\{f_{l,i,j}+(k-l)\times a_{i,j}\}$。

注意 DP 的初始状态是 $f_{0,sx,sy} = 0$。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define puts(s) cout << s << endl
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
const int N = 60,M = 2510;
int n,m,k;
int sx,sy;
int a[N][N];
LL f[M][N][N];
int main () {
	cin >> n >> m >> k >> sx >> sy;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) cin >> a[i][j];
	}
	memset (f,-0x3f,sizeof (f));
	f[0][sx][sy] = 0;
	LL ans = 0;
	for (int s = 0;s <= min (n * m,k);s++) {
		for (int i = 1;i <= n;i++) {
			for (int j = 1;j <= m;j++) {
				for (int d = 0;d < 4;d++) {
					int ni = i + dx[d],nj = j + dy[d];
					tomax (f[s + 1][ni][nj],f[s][i][j] + a[ni][nj]);
				}
				tomax (ans,f[s][i][j] + (LL)(k - s) * a[i][j]);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：yegengghost (赞：0)

最简单的一次，不过也是听别人说才做的。

见到该题，首先血脉觉醒：**直接 BFS 搜索好吧！**

但是面对着输入的 $k$，我又迟疑了，貌似是 dp。

可以用 $dp_{i,j}$ 来表示当前第 $i$ 行、第 $j$ 列中的位置对答案最大贡献。但由于不方便写状态转移方程式，便修改成 $dp_{pth,i,j}$ 来实现。

具体方程式为：

$$dp_{pth,i,j}\gets \max(dp_{pth,i,j},dp_{pth-1,exi,exj}+a_{i,j})$$

其中 $exi$ 与 $exj$ 分别表示搜索过程中当前处于的横纵坐标，$pth$ 表示在当前这个格子走了几步。

最后看下答案。

我们需要在每一个答案中找到最大值，同时对剩下的步数处理，具体见代码。

```cpp
//啊忘说了，别忘了先memset一下，不然过不了！！！ 
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w,k;
int si,sj;
int dp[2510][60][60],a[50][50];
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int ans;
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
	h=read();
	w=read();
	k=read();
	si=read();
	sj=read();
	memset(dp, -0x3f, sizeof(dp));
	//忘记加死磕了好久 
	dp[0][si][sj]=0;//特殊处理下 
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			a[i][j]=read();
	for(int pth=1;pth<=2500;pth++)
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)
				for(int bol=0;bol<=4;bol++)
				{
					int exi=i+dx[bol];
					int exj=j+dy[bol];
					if(exi<1||exi>h||exj<1||exj>w)
						continue;
					dp[pth][i][j]=max(dp[pth][i][j],dp[pth-1][exi][exj]+a[i][j]);
				}//dp状态转移，整体上是BFS操作。 
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			ans=max(ans,dp[min(k,2500ll)][i][j]+(k-min(k,2500ll))*a[i][j]);
	//这部分就是答案的计算。 
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：wly09 (赞：0)

~~这集 ABC 好水啊，后悔没去打了~~

首先，$K$ 较小的时候，暴力 dp 即可，复杂度 $O(HWK)$；

其次，若一个格子的值不小于所有与他相邻的格子，那么接下来始终不动显然不劣。那么，当 dp 足够多的轮次后，高桥君的最优方案显然就是停在原地。

听同学说有一个坑是随便取了一个最大的格子；正解需要枚举每个格子，因为最大值可能不唯一。

[AC 记录](https://atcoder.jp/contests/abc358/submissions/54626866)

---

关于 $K$ 的分界值的选取：

保守一点可以卡时，考虑到每秒大约 $10^8$，我们可以取 $\dfrac{10^8}{HW}=40000$；

不过，按照我们的分析，$HW=2500$ 足矣，那么时间复杂度是 $O((HW)^2)$。

以上 $H,W$ 取其最大值。你当然也可以动态算，但是我认为没有必要。

---

## 作者：zhlzt (赞：0)

### 题解

在最优解中，显然会且只会在同一个方格（路径上权值最大的方格）停留，并且一直停留直到无法再进行操作，正确性很好说明：若停留在其他方格，不如在最后用这些操作数停留在路径上权值最大的方格贡献更大；若路径上权值最大的方格不是路径的终点，那么遍历剩下的点的操作数还不如停留在这个方格。

设 $dp_{k,i,j}$ 表示经过 $k$ 个操作并到达 $(i,j)$ 能得到的最大贡献，其中 $k\le \min\{h\times w,v\}$（$v$ 就是题面中的 $K$），跑完 $dp$ 后再处理停留的问题即可。复杂度为 $O(h^2w^2)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=55;
const int maxm=2510;
int a[maxn][maxn];
ll dp[maxm][maxn][maxn];
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int check(int ux,int uy,int vx,int vy){
	return abs(ux-vx)+abs(uy-vy);
}
int main(){
	int h,w,v;scanf("%d%d%d",&h,&w,&v);
	int stx,sty;scanf("%d%d",&stx,&sty);
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++) scanf("%d",&a[i][j]);
	}
	ll ans=0;
	for(int k=1;k<=min(v,h*w);k++){
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				if(check(i,j,stx,sty)<=1){
					ll temp=dp[k-1][stx][sty];
					dp[k][i][j]=max(dp[k][i][j],temp+a[i][j]);
				}
				if(dp[k-1][i][j]){
					ll temp=dp[k-1][i][j];
					dp[k][i][j]=max(dp[k][i][j],temp+a[i][j]);
				}
				for(int c=0;c<4;c++){
					int vx=i+dx[c],vy=j+dy[c];
					if(dp[k-1][vx][vy]){
						ll temp=dp[k-1][vx][vy];
						dp[k][i][j]=max(dp[k][i][j],temp+a[i][j]);
					}
				}
			}
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			int dis=check(i,j,stx,sty);
			if(dis<=v){
				for(int k=1;k<=min(v,h*w);k++){
					if(dp[k][i][j]){
						ans=max(ans,dp[k][i][j]+1ll*(v-k)*a[i][j]);
					}
				}
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

