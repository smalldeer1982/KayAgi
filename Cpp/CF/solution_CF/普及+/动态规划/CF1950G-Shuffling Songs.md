# Shuffling Songs

## 题目描述

Vladislav 有一个由 $n$ 首歌组成的播放列表，编号从 $1$ 到 $n$。歌曲 $i$ 属于流派 $g_i$ 并由作者 $w_i$ 创作。他希望以这样一种方式制作播放列表：每对相邻的歌曲要么有相同的作者，要么属于相同的流派（或两者兼有）。他称这样的播放列表为激动人心的。 $g_i$ 和 $w_i$ 都是长度不超过 $10^4$ 的字符串。

但是有可能不总是能使用所有歌曲制作出激动人心的播放列表，因此洗牌过程分为两步。首先，移除一些数量（可能为零）的歌曲，然后重新排列剩余的歌曲使播放列表激动人心。

由于 Vladislav 不喜欢从他的播放列表中移除歌曲，他希望尽可能少地进行移除。帮助他找出为了能重新排列剩余歌曲使播放列表激动人心而需要进行的最少移除数量。

## 样例 #1

### 输入

```
4
1
pop taylorswift
4
electronic themotans
electronic carlasdreams
pop themotans
pop irinarimes
7
rap eminem
rap drdre
rap kanyewest
pop taylorswift
indierock arcticmonkeys
indierock arcticmonkeys
punkrock theoffspring
4
a b
c d
e f
g h```

### 输出

```
0
0
4
3```

# 题解

## 作者：spire001 (赞：4)

## CF1950G题解

我第一眼以为这个题是什么欧拉回路。。。

结果发现数据范围。。。

好，确定为状态压缩。

如果你不会的话，[P1433](https://www.luogu.com.cn/problem/P1433) 是学习状态压缩的不错选择。

很基础的状态压缩啦，但是再基础也要认真对待，用哈希表替代字符串比较可以减小常数，同时状态转移数组可以使用又快又省空间的 `bool` 型数组。

详细地说一下状态转移方程。。。。。



$dp_{i,j}$ 表示在 $j$ 状态下，最右边的歌曲为 $i$ 时是否能够满足条件。

其中 $j$ 的二进制表达指明了歌曲是否已经被放置，可以表示当前状态。

从 $0$ 到 $2^n-1$ 枚举状态 $j$，可以发现这个状态 $j$ 必然被所有能到 $j$ 的状态转移过。

因为放置的次序是无关紧要的，有用的信息只是还有什么可放，以及本题目中的相邻歌曲的关系。

对于每一个状态 $j$ ，假设此时最右边的歌曲为 $i$，枚举每一个未放置过的歌曲 $p$（需要注意要满足二进制的约束，即二进制为 $0$ 的没被拿过，为 $1$ 的则反之，就是说 $i$ 所对应的二进制位为 $1$，而 $p$ 对应的二进制位则为 $0$）。

如果 $a_i=a_p$ 或者 $b_i=b_p$，即满足题目中的相邻歌曲放置的要求，那么说明可以在 $i$ 的右边放一个 $p$ 歌曲。

二进制状态则可以由 $j$ 转移为 $j\cap p$。在代码中表现为 ```j | (1 << (p - 1))```。

所以状态转移方程为：

$$
dp_{p,j \cap p}=dp_{p,j\cap p} \operatorname{or} ~(dp_{i,j} \operatorname{and}~ (a_i=a_p\operatorname{or} b_i=b_p))
$$

因为只需有一种摆放方式下满足即可，所以要做或运算。

体现在代码中直接赋值 `true` 就行了。

代码上大部分与吃奶酪一题相同，那么这个题就可以实现了。

```cpp
# include <iostream>
# include <climits>
# include <cstring>
# include <algorithm>
# include <vector>
# include <cmath>
# include <ext/pb_ds/assoc_container.hpp> // 拓展库哈希表
# include <ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

gp_hash_table <string, int> hs;
constexpr int N = 17;

bool dp[N][1 << N];
int n, tot;

inline int getid(string &s) // 获得字符的哈希编号
{
	return hs[s] ? hs[s] : hs[s] = ++tot;
}

int a[N], b[N];

void solve()
{
	hs.clear();
	
	memset(dp, 0, sizeof dp); // 多测记得清空
	
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string x, y;
		cin >> x >> y;
		
		a[i] = getid(x);
		b[i] = getid(y);
	}
	
	const int x = 1 << n;
	
	for(int i = 1; i <= n; i++) dp[i][1 << (i - 1)] = true; // 初始化，只拿一个必然满足条件。
	
	for(int i = 0; i != x; i++) // 所有状态
		for(int j = 1; j <= n; j++) // 枚举最右边的歌曲
			if(i & (1 << (j - 1)) && dp[j][i]) // 已经放置过了，并且这个值为 true
				for(int p = 1; p <= n; p++) // 枚举，尝试放置新的歌曲
					if(!(i & (1 << (p - 1)))) // 没有被放置过
						if(a[p] == a[j] || b[p] == b[j]) // 满足题目放置条件
							dp[p][i | (1 << (p - 1))] = true;
	
	int ans = n;
	
	for(int i = 0; i != x; i++)
		for(int j = 1; j <= n; j++)
			if(dp[j][i])
				ans = min(ans, n - __builtin_popcount(i)); // __builtin_popcount(int) 函数求二进制一的个数。
	
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T; cin >> T;
	
	while(T--) solve();
	
	return 0;
}

/*
begin: 05/05/24 18:33
debug: 
enddebug: 05/05/24 20:14
*/

```

---

## 作者：zhuweiqi (赞：4)

状压 dp 好题。

观察到本题特殊的数据范围：$n\leq 16$，基本确定为状压 dp。

由于字符串处理过于麻烦，所以我们可以用 map 先将字符串离散化成整数方便进行比较。

然后，将已选择歌曲的集合压缩成一个状态（即如果选了第 $k$ 首歌，那么这个状态转为二进制数的第 $k$ 位为 $1$，反之亦然）（请注意，为了方便实现，此处第 $k$ 位是从低到高反数的，且最低位默认为第 $0$ 位），$f_{i,j}$ 表示当前状态为 $i$ 且点的最后一首歌为 $j$ 时所能选择的歌曲的最大数量，转移时选择一首尚未点过的歌，如果其两个参数中有任意一个和 $j$ 的相等，则可以取最大值转移。注意，初始化时需将所有不合法状态及未转移到的状态赋值为极小值，将只点了一首歌的合法状态赋值为 $1$，最后输出拿 $n$ 减一减即可。

Std（仅供参考）：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int> p;
int a[20],b[20];
int f[1<<16][16];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,cnt=0,ans=1;
		cin>>n;
		p.clear();
		for(int i=0;i<n;i++){
			string x,y;
			cin>>x>>y;
			if(!p[x]) p[x]=++cnt;
			if(!p[y]) p[y]=++cnt;
			a[i]=p[x],b[i]=p[y];
		}
		for(int i=0;i<(1<<n);i++){
			for(int j=0;j<n;j++){
				if(((i>>j)&1)==0) f[i][j]=-1e9;
				else if((i&(i-1))==0) f[i][j]=1;
				else f[i][j]=-1e9;
			}
		}
		for(int i=0;i<(1<<n);i++){
			for(int j=0;j<n;j++){
				if(f[i][j]<0) continue;
				ans=max(ans,f[i][j]);
				for(int k=0;k<n;k++){
					if(((i>>k)&1)==0 && (a[k]==a[j] || b[k]==b[j])){
						f[i|(1<<k)][k]=max(f[i|(1<<k)][k],f[i][j]+1);
					}
				}
			}
		}
		cout<<n-ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Believe_in_dreams (赞：1)

# SOLVE
很多人看见 $ 1\le n \le 16$ 就写了一个状压 dp ，却没人发图论的题解，我就来水一波。
## 思路
我们可以抽象地把每一首歌曲看成一个节点，歌曲 A 与歌曲 B 能接在一起就相当于节点 A 和节点 B 之间有一条连边。注意，图是无向的（若歌曲 A 能接在歌曲 B 的后面，则歌曲 B 必能接在歌曲 A 的后面）。  

题目让我们求最少去掉多少首歌，其实就是求最少去掉多少个节点能让图变成链，归根到底是求最长路。  

这熟悉多了，我们把最短路的定义修改为最长路，然后在图上跑 Dijkstra 就好了啊。
## 可行性证明
对于每组数据，枚举起始点 i 进行 Dijkstra ，时间复杂度 $O(n^3)$ 。  

总时间复杂度 $O(n^3T)$ ，绰绰有余。
## 核心代码
```cpp
//...
struct node{
	int x,dis;
	bool operator<(const node &p){
		return dis>p.dis;//从大到小排序
	}
};
//...
void dijkstra(int st){
	_max=0;
	memset(dis,0,sizeof dis);
	memset(vis,0,sizeof vis);
	dis[st]=1;
	priority_queue<node> q;
	q.push({st,0});
	while(!q.empty()){
		int x=q.top().x;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=ne[i]){
			int y=to[i];
			if(dis[x]+w[i]>dis[y]){
				dis[y]=dis[x]+w[i];
				_max=max(_max,dis[y]);
				q.push({y,dis[y]});
			}
		}
	}
}
//...
```
### 补充
 dalao @lr1799322 提出了一个值得思考的问题。  
如果我们遇到了一个环有应该怎样处理呢？  
试想一下，如果遇到了很多的歌曲可以连续点最后点会第一首选择的歌曲，那么根据题意，我们也不能选择第一首歌曲了。  
所以我们应该在结构体里面多记录每一种方案，也就是一个二进制压缩之后在 $2^{16}$ 以内的数字。  
这样做不会使得 dijkstra 算法的正确性出现问题，因为我们仍然保证当前最优解一定在队顶，而最后一次弹出当前最优解就是全局最优解。  
这样问题就解决了，我们只需要一个变量记录节点的访问情况，在更新新的节点的时候进行检查即可。

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**状态压缩动态规划**和**模拟**的思路：

- 我们可以设计状态 $dp_{i,j}$ ，$i$ 代表歌曲选择状态**状压**后的值，$j$ 代表当前状态的**最后一首**的编号，此状态是否可行。

- 这样我们很容易推出转移方式：枚举从**少了哪首歌**的状态转移，再枚举上一个状态的最后一首歌**是否匹配**少的那首,若匹配直接转移，此时时间复杂度为 $O(2^n \times n^2 \times |s|)$，超时。

- 由此我们可以使用**哈希字符串**优化，**预处理**每个字符串的哈希值，时间复杂度变为 $O(2^n \times n^2)$。

- 最后找出歌曲数量**最多**且合法的情况输出即可。

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20,mod=1145141919810;
//会卡ull的自然溢出
int t,n,ans,sum,val,hg[N],hw[N];
bool dp[1<<N][N],vis[N];
string g[N],w[N];
inline void Hash(int id)
{//标准哈希
	hg[id]=1;
	hw[id]=1;
	for(int i=0;i<g[id].size();i++)
	{
		hg[id]=hg[id]*31+(g[id][i]-'a');
		hg[id]%=mod;
	}
	for(int i=0;i<w[id].size();i++)
	{
		hw[id]=hw[id]*31+(w[id][i]-'a');
		hw[id]%=mod;
	}
	return;
}
inline int f(int x)
{//有几首歌
	int res=0;
	for(;x;res++)
	{
		x&=x-1;
	}
	return res;
}
inline bool check(int a,int b)
{
	return hg[a]==hg[b]||hw[a]==hw[b];
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for(cin>>t;t;t--)
	{
		memset(dp,false,sizeof dp);
		ans=0x3f;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>g[i]>>w[i];
			Hash(i);//预处理
		}
		for(int i=0;i<(1<<n);i++)
		{
			if(f(i)==0)
			{
				continue;
			}
			if(f(i)==1)
			{
				for(int j=0;j<n;j++)
				{
					if((i>>j)&1)
					{//一首歌则全有解
						dp[i][j+1]=true;
						break;
					}
				}
				continue;
			}//特判一个、没有歌曲的情况
			sum=f(i);
			memset(vis,false,sizeof vis);
			for(int j=0;j<n;j++)
			{
				if((i>>j)&1)
				{
					vis[j]=true;//记录有哪首歌
				}
			}
			for(int j=0;j<n;j++)
			{//上种情况少哪首
				if(!vis[j])
				{
					continue;
				}
				val=i-(1<<j);
				for(int k=0;k<n;k++)
				{//上种情况的最后一首
					if(k==j||!vis[k])
					{
						continue;
					}
					if(check(j+1,k+1))//合法
					{//转移
						dp[i][j+1]|=dp[val][k+1];
					}
				}
			}
		}
		for(int i=0;i<(1<<n);i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(dp[i][j])
				{//找答案
					ans=min(ans,n-f(i));
				}
			}
		}
		cout<<ans<<"\n";
	}
	exit(0);
}
```

---

## 作者：Gapple (赞：0)

首先发现 $n \le 16$，考虑状压 DP。

设 $f_{S, i}$ 为当前选择了集合 $S$ 且最后选择的是 $i$ 时最多能选择的个数。则转移方程为

$$
f_{S \cup \{ j \}, j} = \max_{i \in S}(f_{S \cup \{ j \}, j}, f_{S, i} + 1) \quad (j \not \in S)
$$

实现时可以用 $n$ 位二进制位表示 $S$，其中第 $i$ 位表示第 $i$ 首歌是否被选。这 $n$ 位二进制位可以用 1 个 `int` 表示，使用 `S & (1 << i)` 判断 $i$ 是否在集合 $S$ 内，使用 `S | (1 << i)` 表示 $S \cup \{ i \}$。同时可以将输入的字符串离散化成整数，这样就不用处理字符串比较的细节。

答案为 $n - \max f_{S, i}$。

```cpp
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
using i64 = long long;

struct Song {
    size_t genre, singer;

    Song() = default;
    Song(int genre, int singer)
        : genre(genre)
        , singer(singer)
    {
    }

    Song(const string& genre, const string& singer)
        : genre(H(genre))
        , singer(H(singer))
    {
    }

    bool operator==(const Song& other) const
    {
        return genre == other.genre || singer == other.singer;
    }

    bool operator!=(const Song& other) const
    {
        return !(other == *this);
    }

private:
    hash<string> H;
};

void solve_test()
{
    int n;
    vector<Song> songs;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        string genre, singer;
        cin >> genre >> singer;
        songs.emplace_back(genre, singer);
    }

    vector<vector<int>> dp(1 << n, vector(n, 0));

    for (int i = 0; i < n; ++i)
        dp[1 << i][i] = 1;

    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i & (1 << j)) == 0)
                continue;

            for (int k = 0; k < n; ++k) {
                if (i & (1 << k) || songs[j] != songs[k])
                    continue;

                dp[i | (1 << k)][k] = max(dp[i | (1 << k)][k], dp[i][j] + 1);
            }
        }
    }

    int ans = n - 1;

    for (const auto& each : dp)
        ans = min(ans, n - reduce(each.begin(), each.end(), 0, [](int x, int y) { return max(x, y); }));

    cout << ans << '\n';
}

int main()
{
    int t;
    cin >> t;

    while (t-- > 0)
        solve_test();

    return 0;
}

```

---

## 作者：OPEC (赞：0)

# [CF1950G Shuffling Songs](https://www.luogu.com.cn/problem/CF1950G)
当你看到 $n\le 16$ 时，那一定是状压 dp。

设 $f_{i,j}$ 表示得到集合 $i$，最后一个是 $j$ 的保留数量。

经过亿点时间推出了状态转移方程，$f_{i\cup\{k\},k}=\max(f_{i\cup\{k\},k},f_{i,j}+1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e1+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t,n;
map<string,int> ma;
map<string,int> mb;
int ca,cb;
int f[1<<N][N];
int da[N];
int db[N];
void solve()
{
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
		{
			f[i][j]=0; 
		}
	}
	cin>>n;
	ma.clear();
	mb.clear();
	ca=0;
	cb=0;
	for(int i=0;i<n;i++)
	{
		string s1,s2;
		cin>>s1>>s2;
		if(ma.find(s1)==ma.end())
			ma[s1]=ca++;
		if(mb.find(s2)==mb.end())
			mb[s2]=cb++;
		da[i]=ma[s1];
		db[i]=mb[s2];
	}
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
		{
			f[i][j]=-INF; 
		}
	}
	for(int i=0;i<n;i++)
	{
		f[1<<i][i]=1;
	}
	int ans=1;
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
		{
			if(f[i][j]<0||(i>>j&1)==0)
			{
				continue;
			}
			for(int k=0;k<n;k++)
			{
				if(j==k||(i>>k&1))
				{
					continue;
				}
				if(da[j]==da[k]||db[j]==db[k])
				{
					f[i|(1<<k)][k]=max(f[i|(1<<k)][k],f[i][j]+1);
					ans=max(ans,f[i|(1<<k)][k]);
				}
			}
		}
	}
	cout<<n-ans<<'\n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF1950G)

## 思路

看到数据范围，想到状压 `dp`。

首先你要知道状压 `dp` 的定义。

先把所有字符串离散化。令 $dp_{i,j}$ 为当前状态为 $i$，最后一首歌是 $j$，能否满足条件。

然后如果满足条件，就转移为 $1$。答案即为满足条件的所有状态中 $1$ 的数量的最大值。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 17, kMaxL = 1 << 17;

int t, n, dp[kMaxL][kMaxN], a[kMaxN], b[kMaxN], ans;
string tx, ty, l[kMaxN], r[kMaxN];
vector<string> lsh;

int Calc(int x) {
  int c = 0;
  for (; x; x >>= 1) {
    c += x & 1;
  }
  return c;
}

int main() {
  for (cin >> t; t; t--, lsh.clear(), ans = 0) {
    cin >> n;
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
      cin >> l[i] >> r[i], lsh.push_back(l[i]), lsh.push_back(r[i]);
    }
    sort(lsh.begin(), lsh.end()), lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    for (int i = 0; i < n; i++) {
      a[i] = lower_bound(lsh.begin(), lsh.end(), l[i]) - lsh.begin();
      b[i] = lower_bound(lsh.begin(), lsh.end(), r[i]) - lsh.begin();
    }
    for (int i = 0; i < n; i++) {
      dp[1 << i][i] = 1;
    }
    for (int i = 0; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        if (dp[i][j] != 0) {
          for (int k = 0; k < n; k++) {
            if (!((i >> k) & 1) && (a[j] == a[k] || b[j] == b[k])) {
              dp[i | (1 << k)][k] |= dp[i][j];
            }
          }
        }
      }
    }
    for (int i = 0; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        (dp[i][j]) && (ans = max(ans, Calc(i)));
      }
    }
    cout << n - ans << '\n';
  }
  return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

观察到 $n$ 的范围极小，本题应该是要 $O(2^n\times n)$ 左右的复杂度，不难想到状压 dp。定义 $dp_{i,j}=0/1$ 表示达到 $i$ 这个状态（一个二进制数，第 $i$ 首歌选那么状态的第 $i$ 位为 $1$，否则为 $0$，$0\le i<n$）并以第 $j$ 首歌结尾是否可能。有了状态，自然推出转移即某一个状态 $i$ 中选择一个未被选择的歌并且能与第 $j$ 首歌接上，那么假设该歌曲编号为 $k$，那么 $dp_{i+2^k,k}\leftarrow 1$。初始值的设置也易得：对于每个 $0\le x<n$，$dp_{2^x,x}\leftarrow 1$。答案自然就是满足 $dp_{i,j}=1$ 的 $n-\operatorname{popcount}(i)$ 的最小值。

这题有点卡常，需要注意一些事情，否则就会如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/c5khnq67.png?x)

要注意的几点：

- popcount 提前处理好，最好是在多测开始前就把 $0\sim 2^{16}$ 的每个数的 popcount 处理好。

- 关闭同步流或使用 scanf 读入或开快读。

- 歌曲流派与作者先离散化，否则常数很大。

- 记录一个 $vis_{i,j}$ 表示是否计算过 $dp_{i,j}$，如果搜索到状态 $i,j$ 时 $vis_{i,j}=1$ 就直接退出本次搜索。

- 多测清空。

祝各位 AC。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
string g[20],w[20];
int g2[20],w2[20],cl[1<<17];
int dp[1<<17][20],n,cnt=0,vis[1<<17][20];
map<string,int> mp;
void dfs(int sta,int lst)
{
	if(vis[sta][lst]) return;
	vis[sta][lst]=1;
	dp[sta][lst]=1;
	for(int i=0;i<n;i++)
	{
		if((sta>>i&1)||(g2[i]!=g2[lst]&&w2[i]!=w2[lst]))
		{
			vis[sta+(1<<i)][i]=1;
			continue;
		}
		dfs(sta+(1<<i),i);
	}
}
int calc(int k)
{
	int ret=0;
	for(int i=0;i<16;i++) ret+=k>>i&1;
	return ret;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	for(int i=0;i<(1<<16);i++) cl[i]=calc(i);
	while(t--)
	{
		mp.clear();
		int ans=0;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>g[i]>>w[i];
			if(!mp[g[i]]) mp[g[i]]=++cnt;
			if(!mp[w[i]]) mp[w[i]]=++cnt;
			g2[i]=mp[g[i]];
			w2[i]=mp[w[i]];
		}
		for(int i=0;i<(1<<n);i++)
		for(int j=0;j<n;j++)
		dp[i][j]=vis[i][j]=0;
		for(int i=0;i<n;i++) dfs(1<<i,i);
		for(int i=0;i<(1<<n);i++)
		for(int j=0;j<n;j++)
		ans=max(ans,dp[i][j]*cl[i]);
		cout<<n-ans<<'\n';
	}
}

---

