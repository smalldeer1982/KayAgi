# [AGC029D] Grid game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc029/tasks/agc029_d

高橋君と青木君は $ H $ 行 $ W $ 列のマス目を使ってゲームをします。 このマス目上には $ N $ 個の障害物があり、$ i $ 番目の障害物は $ (X_i,Y_i) $ にあります。 ただし、$ i $ 行 $ j $ 列目 $ (1\ \leq\ i\ \leq\ H,\ 1\ \leq\ j\ \leq\ W) $ にあるマスを $ (i,j) $ で表すことにします。 また、どの障害物も $ (1,1) $ にはなく、$ (1,1) $ には $ 1 $ つの駒が置いてあります。

そこで、高橋君と青木君は高橋君から始めて、交互に以下の行動のいずれかを行います。

- 駒を隣り合うマスに動かす。 ただし、駒の位置を $ (x,y) $ としたとき、高橋君は $ (x+1,y) $ にのみ、青木君は $ (x,y+1) $ にのみ駒を動かすことができる。 また、動かすことのできるマスが存在しない、もしくは、動かす予定のマス目に障害物がある場合はこの行動をとることはできない。
- 駒を動かさず、マス目を元の状態のまま行動を終える。

$ 2 $ 回連続で駒が動かされなかった場合、そこでゲームを終了します。

高橋君はできるだけ多くの回数の行動 (駒を動かさないのも含む) を行ってゲームを終えたいですが、 青木君はできるだけ少ない回数の行動を行ってゲームを終えたいです。 このとき、高橋君が行うことになる行動の回数は何回か求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X_i\ \leq\ H $
- $ 1\ \leq\ Y_i\ \leq\ W $
- $ i\ \neq\ j $ のとき $ (X_i,Y_i)\ \neq\ (X_j,Y_j) $
- $ (X_i,Y_i)\ \neq\ (1,1) $
- $ X_i,Y_i $ は整数

### Sample Explanation 1

ゲームの一例は以下のようになります。 - 高橋君が駒を (2,1) に動かす。 - 青木君が駒を動かさない。 - 高橋君が駒を (3,1) に動かす。 - 青木君が駒を動かさない。 - 高橋君が駒を動かさない。 この場合は高橋君は $ 3 $ 回の行動を行いますが、 両者が最適に行動すれば $ 2 $ 回しか高橋君は行動せずにゲームが終了します。

## 样例 #1

### 输入

```
3 3 1
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
10 10 14
4 3
2 2
7 3
9 10
7 7
8 1
10 10
5 4
3 4
2 8
6 4
4 4
5 8
9 2```

### 输出

```
6```

## 样例 #3

### 输入

```
100000 100000 0```

### 输出

```
100000```

# 题解

## 作者：Acheron_RBM (赞：4)

这题很显然可以用贪心来解。

由于先手不动一定会让局数更少，所以先手要能动就动。

而后手一定是希望他的石子可以撞到一个障碍物上，这样先手就无法移动了，后手就可以让局数更少。

因为先手一定会能动就动，所以后手只能走到横坐标大于纵坐标的障碍物上方。那就很简单了，我们只需要统计符合特点的障碍物即可。


```cpp
bool mp[200001][200001];//存图 
pair<long long,long long> a[555555];//一个结构体，有两个元素，一个叫first，一个叫second 
long long col[555555]={0,1};//第i行有几个可到达的列
long long ret;
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	ret=n;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i].first>>a[i].second;//障碍物的位置 
		mp[a[i].first][a[i].second]=true;
	}
	long long sum=1;
	for(int i=2;i<=n;i++)
	{
		if(!mp[i][sum+1]&&sum<m)//高木最优策略 
		{
			sum++;
		}
		col[i]=sum;
	}
	for(int i=1;i<=k;i++)
	{
		if(col[a[i].first]>=a[i].second)
		{
			ret=min(ret,a[i].first-1);//统计答案 
		}
	}
	cout<<ret;
	return 0;
}
```

---

## 作者：Krimson (赞：3)

安利个人[blog](https://www.cnblogs.com/Guts/p/14688782.html)  
非常一眼的题目。  
首先可以发现，每一回合高木都会向右移动一个单位，否则的话青木可以选择不动，游戏结束。  
也就是说，高木的行动是确定的，剩下的只剩下青木了。  
于是，有一个比较naive的贪心，即先将所有障碍物按照 $x$ 排序，再依次扫过去。  
假设当前枚举道的障碍物是 $(x,y)$ ，那么如果青木可以到达 $(x-1,y)$ ，则答案就是 $x-1$ 。  
考虑如何判断青木在 $x-1$ 的时候纵坐标可以到达 $y$ 。  
不难发现，在 $x$ 固定的时候且没有碰到障碍物的时候，青木能到达的范围都是一个区间 $[1,up]$，每次 $x+1$ 都会让 $up++$ 。  
当出现障碍物的时候，设其坐标为 $(x+1,lim)$ ，需要分三类讨论：  
1. $lim>up+1$  
这个障碍物对 $up$ 没有影响。  
2. $lim=up+1$  
$up$ 不能加一了。  
3. $lim \leq up$  
此时已经得到答案为 $x$，可以直接 `break` 。  

至此，该如何得到答案已经非常简单了，这里就不再赘述了。  



_Code_
------------
```cpp

#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
/*
可以发现每次能到达的地方都是一段区间。

*/
#define pii pair<int,int>  
set<pii > s;
int up;
const int MAXN=2e5+7;
pii p[MAXN];
int h,w,n;
int main(){
    h=read(),w=read(),n=read();
    for(ri i=1;i<=n;++i) p[i].first=read(),p[i].second=read();
    p[++n]=(pii){h+1,1};
    sort(p+1,p+n+1);
    up=1;
    for(ri i=1,j=1;i<=n;++i){
        while(j+1<p[i].first){
            ++j;
            if(s.find((pii){j,up+1})==s.end()) ++up;
        }
        if(up>=p[i].second&&s.find((pii){j,up})==s.end()){
            print(j);
            return 0;
        }
        s.insert(p[i]);
    }
    return 0;
}
```

---

## 作者：Acheron_Styx (赞：2)

这题一眼贪心。

如先手不动，那局数一定会更少，那么先手的最优策略就是能动就动。

后手则是要把自己引到障碍物上面，让自己动不了，以减少局数。

因为先手一定会能动就动，所以后手只可能走到横坐标大于纵坐标的障碍物上方。接下来就很明了了，直接模拟即可。

```cpp
#define pll pair<int,int>
#define ll int
pll a[555555];//相当于一个struct 
ll col[555555]={0,1};
ll ret;
bool mp[200001][200001];
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	ret=n;
	ll cnt=1;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i].first>>a[i].second;
		mp[a[i].first][a[i].second]=true;
	}
	for(int i=2;i<=n;i++)
	{
		if(!mp[i][cnt+1]&&cnt<m)//模拟最优策略 
		{
			cnt++;
		}
		col[i]=cnt;
	}
	for(int i=1;i<=k;i++)
	{
		if(col[a[i].first]>=a[i].second)
		{
			ret=min(ret,a[i].first-1);//统计答案 
		}
	}
	cout<<ret;
	return 0;
}
```

---

## 作者：ningago (赞：0)

暴力做法。

容易发现如果先手不走，那么后手一定跟着不走，停止游戏。

所以先手只能一直走，直到后手把他勾引到一个障碍（边界）上方，设这个点为 $(x,y)$，此时的操作次数即为 $x,y$ 的最大值。

维护当前在第 $i$ 行，当前能到达的点有哪些。

不难把每一段连续的 $1$ 都看做一个区间，则每次进行的操作有：

1. 遇到障碍，挖去其中一个区间中的一个点（分裂成至多两个区间），如果该点存在则更新答案。
2. 把每个区间向右延伸一格。

用珂朵莉树维护，在执行操作 $2$ 时若两区间相连则合并成一个区间。由于操作是交替出现的，复杂度是均摊的。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <vector>
#include <queue>
#include <numeric>
#include <map>
#include <set>

char ST;
//#define int long long
#define ll long long
#define inf 0x3f3f3f3f
//#define inf 0x3f3f3f3f3f3f3f3f
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int readstr(char *str, int base)
{
	int len = base - 1;
	char c = getchar();
	for(; !isalpha(c) && !isdigit(c) && c != '.' && c != '*' && c != '#'; c = getchar());
	for(;  isalpha(c) ||  isdigit(c) || c == '.' || c == '*' || c == '#'; c = getchar()) str[++len] = c;
	return len - base + 1;
}

void write(int x, char c)
{
	if(c) putchar(c);
	if(x >= 10) write(x / 10, 0);
	putchar(x % 10 + 48);
}

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second
#define pb push_back 

template <typename T> void ckmax(T &x, T y) { x = x > y ? x : y; }
template <typename T> void ckmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> T max(T x, T y) { return x > y ? x : y; }
template <typename T> T min(T x, T y) { return x < y ? x : y; }
#define mod 998244353
//#define mod 1000000007

void plus_(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b)
{
	int res = 1;
	for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(res, a);
	return res;
}

#define N 200010

int n, m, K, x_[N], y_[N];
struct node
{
	int l, r;
	bool operator < (const node &B) const { return l < B.l; }
};
std::set <node> s;
std::vector <int> vec[N];
#define sit std::set <node> :: iterator 

bool del(int x)
{
	if(s.empty() || (--s.end()) -> r < x || x < s.begin() -> l) return 0;
	sit it = s.upper_bound((node){x, 0}); it--;
	if(it -> r < x) return 0;
	int l = it -> l, r = it -> r;
	s.erase(it);
	if(l != x) s.insert((node){l, x - 1});
	if(r != x) s.insert((node){x + 1, r});
	return 1;
}

void solve()
{
	n = read(), m = read(), K = read();
	for(int i = 1; i <= K; i++) x_[i] = read(), y_[i] = read(), vec[x_[i]].push_back(y_[i]);
	int ans = n;
	for(int i = 1; i <= n; i++)
	{
		for(int t : vec[i]) 
			if(del(t))
				ckmin(ans, std::max(i - 1, t));
		for(sit it = s.begin(), nxt; it != s.end(); it = nxt)
		{
			nxt = next(it);
			while(nxt != s.end() && it -> r + 1 == nxt -> l - 1)
			{
				int l = it -> l, r = nxt -> r;
				s.erase(it);
				s.erase(nxt);
				it = s.insert((node){l, r}).fi;
				nxt = next(it);
			}
			int l = it -> l, r = it -> r;
			s.erase(it);
			it = s.insert((node){l, r + 1}).fi;
			nxt = next(it);
		}
		if(s.empty() || s.begin() -> l != 1)
		{
			if(!s.empty() && s.begin() -> l == 2)
			{
				int r = s.begin() -> r;
				s.erase(s.begin());
				s.insert((node){1, r});
			}
			else
				s.insert((node){1, 1});
		}
		for(int t : vec[i]) 
			del(t); 
	}
	printf("%d\n", ans);
}

char ED;
signed main()
{
	for(int T = 1; T; solve(), T--);
	return 0;
}
```

---

## 作者：Texas_the_Omertosa (赞：0)

[题目传送门](/problem/AT4503)

### 0x01 思路

刚看到这题时，我还以为是博弈论，分析了一下才失望地发现原来是贪心。

因为先手是希望回合数更多的，所以先手不可能主动不懂，因为这样的话后手可以立刻结束，综上所述，先手是被动的。

所以我们只需要分析后手。后手如果希望回合数尽量少，则一定会让棋子往一个障碍物上方引，这样先手就动不了了。

由于先手一定会尽量往下走，所以后手只能走到横坐标大于纵坐标的障碍物上方。但是，中途可能有障碍物让后手无法向右移动，所以不能排完序输出。

剩下的在代码的注释中。

### 0x02 AC Code

```cpp
//by olkieler
#include <bits/stdc++.h>
#define int long long
#define linf LLONG_MAX
#define iinf INT_MAX
#define ios ios::sync_with_stdio(0);cin.tie(0);
#define N 500005
#define M 300005
#define mod 1000000007
#define pint pair<int, int>
#define mp make_pair
using namespace std;
map<int, bool>ma[N];//记录障碍物
struct point
{
	int x;
	int y;
};
point a[N];
int col[N] = {0, 1};//col[i] 表示到第 i 行最多可到达的列数。
signed main()
{
	ios;
	int n, m, k, ans, c = 1;
	cin >> n >> m >> k;
	ans = n;
	for (int i = 1; i <= k; i ++)
	{
		cin >> a[i].x >> a[i].y;
		ma[a[i].x][a[i].y] = 1;//标记障碍物
	}
	for (int i = 2; i <= n; i ++)
	{
		if (c < m && !ma[i][c + 1])//如果可以往右走
		{
			c ++;
		}
		col[i] = c;
	}
	for (int i = 1; i <= k; i ++)
	{
		if (col[a[i].x] >= a[i].y)//如果到了这一行刚好到或超过这一列
		{
			ans = min(ans, a[i].x - 1);//可以到达，记录答案。
		}
	}
	cout << ans << '\n';
	return 0;
}
```

还有疑问可以私信或评论。

---

## 作者：lgswdn_SA (赞：0)

不同之处在于不需要对各种障碍点进行判断。所以可能会更加简单。

先手一定不能主动不动，不然后手不动就直接结束。所以先手是完全被动的。考虑后手的游戏策略，肯定是把棋子带到一个障碍点的上方，这样先手就没法动了。我们现在要判断的是，后手能不能不经过障碍点到达一个障碍点的上方。

后手唯一的问题在于可能他没有足够的步数来移到那个障碍点的 $y$ 坐标，而不需要担心走过了。所以我们就让后手尽量走。维护出一个折线，代表**仅限制不能横向走到障碍点**，后手尽量向右边走，能走到的最靠右的折线。

可以这样的原因是显然的。因为折线下方的点如果不可达，那么必然意味着它有上面的点可达。那必然这个点会更劣，不会计入答案。所以折线下方的点要么必然不是最优解（有可达障碍点在其上方），要么一定是可达的。直接用这些点更新答案即可。

直接用了 map 表示出所有点。可能比较暴力，但是本质上也没啥问题就是。

```cpp
int n,m,k,p[N],ans;
map<int,int>mp[N];
pii b[N];
signed main() {
    n=read(), m=read(), k=read();
    rep(i,1,k) {
        int x=read(), y=read();
        mp[x][y]=1; b[i]=pii(x,y);
    }
    int pos=1; p[1]=1;
    rep(i,2,n) {
        if(pos<m&&!mp[i][pos+1]) ++pos;
        p[i]=pos;
    }
    ans=n;
    rep(i,1,k) {
        int x=b[i].fi-1, y=b[i].se;
        if(p[x]>=y) ans=min(ans,x);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Presentation_Emitter (赞：0)

一道比较水的 `AGC D` 题。

显然 Takahashi 要一直前进直到不能前进为止，所以我们把 Akio 的策略最优的情况下，能到达的地方全部预处理出来。

首先将每一列的障碍物按 $x$ 排序丢到对应列的 `vector` 中。为了避免某些边界特判，再丢进去一个 $h+1$。

然后，设第 $i$ 列能到达的 $x$ 最小的位置为 $lim_i$：

1. 初始 $lim_i \leftarrow lim_{i-1}+1$。
2. 如果 $(lim_i,i)$ 有障碍，$lim_i \leftarrow lim_i+1$，重复步骤 2 直至该位置无障碍。
3. 检验是否能从 $i-1$ 列转移到第 $i$ 列。

$O(HW)$ 的空间复杂度是不能接受的，所以用前面提到的 `vector` 外加一个 $cur$ 数组检验是否有障碍。具体见代码。

处理完 $lim$ 后，直接对于每一个可达的障碍物更新答案即可。

Code:

```cpp
ll h,w,n,x[200005],y[200005],ans,lim[200005],cur[200005];vector<ll>q[200005];
int main()
{
	h=rd();w=rd();n=rd();ans=h;for(int i=1;i<=n;++i)x[i]=rd(),y[i]=rd(),q[y[i]].pb(x[i]);
	for(int i=0;i<=w;++i)q[i].pb(h+1),sort(q[i].begin(),q[i].end());
	lim[0]=1;
	for(int i=1;i<=w;++i)
	{
		lim[i]=lim[i-1]+1;
		while(cur[i]<q[i].size()&&q[i][cur[i]]<lim[i]-1)++cur[i];
		while(cur[i]<q[i].size()&&q[i][cur[i]]==lim[i]-1)++cur[i],++lim[i];
		if(lim[i]>=q[i-1][cur[i-1]]){lim[i]=0;break;}
	}
	//for(int i=1;i<=w;++i)cerr<<cur[i]<<' '<<lim[i]<<endl;
	for(int i=1;i<=n;++i)
	{
		if(!lim[y[i]]||x[i]<lim[y[i]])continue;
		tomin(ans,x[i]-1);
	}
	prt(ans);
	ret 0;
}
```

---

