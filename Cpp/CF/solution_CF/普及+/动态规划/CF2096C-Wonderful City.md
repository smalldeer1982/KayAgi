# Wonderful City

## 题目描述

你是古伯兰王国一座城市的骄傲领导者。这座城市有 $n^2$ 栋建筑，排列成 $n$ 行 $n$ 列的网格。位于第 $i$ 行第 $j$ 列的建筑高度为 $h_{i,j}$。

当城市中任意两个相邻建筑的高度都不相同时，这座城市才是美丽的。换句话说，必须满足以下条件：
- 不存在位置 $(i,j)$（$1 \leq i \leq n$，$1 \leq j \leq n-1$）使得 $h_{i,j} = h_{i,j+1}$；
- 不存在位置 $(i,j)$（$1 \leq i \leq n-1$，$1 \leq j \leq n$）使得 $h_{i,j} = h_{i+1,j}$。

A 公司有 $n$ 名工人，B 公司也有 $n$ 名工人。每名工人最多只能被雇佣一次。

雇佣 A 公司的第 $i$ 名工人需要花费 $a_i$ 枚金币。雇佣后，该工人会：
- 将第 $i$ 行所有建筑的高度增加 $1$。即，将 $h_{i,1}, h_{i,2}, \ldots, h_{i,n}$ 都增加 $1$。

雇佣 B 公司的第 $j$ 名工人需要花费 $b_j$ 枚金币。雇佣后，该工人会：
- 将第 $j$ 列所有建筑的高度增加 $1$。即，将 $h_{1,j}, h_{2,j}, \ldots, h_{n,j}$ 都增加 $1$。

请计算使城市变得美丽所需的最少金币数，如果不可能实现则返回 $-1$。

## 说明/提示

对于第一个测试用例，可以看到城市已经是美丽的，因此答案为 $0$。

对于第二个测试用例，我们可以雇佣 A 公司的第 $2$ 名工人、A 公司的第 $4$ 名工人和 B 公司的第 $4$ 名工人：
- 初始状态：
```
1 2 1 2
3 2 1 2
1 2 1 1
1 3 1 2
```
- 雇佣 A 公司第 $2$ 名工人后：
```
1 2 1 2
4 3 2 3
1 2 1 1
1 3 1 2
```
- 雇佣 A 公司第 $4$ 名工人后：
```
1 2 1 2
4 3 2 3
1 2 1 1
2 4 2 3
```
- 雇佣 B 公司第 $4$ 名工人后：
```
1 2 1 3
4 3 2 4
1 2 1 2
2 4 2 4
```

此时城市变得美丽，雇佣工人的总费用为 $2 + 4 + 8 = 14$，这是可能的最小费用。

对于第三个测试用例，无论如何操作都无法使城市变得美丽，因此答案为 $-1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2
1 2
2 1
100 100
100 100
4
1 2 1 2
3 2 1 2
1 2 1 1
1 3 1 2
1 2 3 4
5 6 7 8
3
1 2 2
2 2 1
2 1 1
100 100 100
100 100 100
6
8 7 2 8 4 8
7 7 9 7 1 1
8 3 1 1 8 5
6 8 3 1 1 4
1 4 5 1 9 6
7 1 1 6 8 2
11 23 20 79 30 15
15 83 73 57 34 63```

### 输出

```
0
14
-1
183```

# 题解

## 作者：ZHR100102 (赞：3)

整场卡在这道题上了，我糖丸了。

首先注意到每行每列只能操作一次，并且改变行的时候只会改变纵向相等的数，改变行的时候只会改变横向相等的数。所以我们**可以对行和列分别操作**。同时这个结论也可以通过差分理解。

因为对行和列操作做法是一样的，这里以行为例。

注意到如果某一行和前一行相邻的数存在小 $1$ 的，就不能只操作这一行；如果某一行和前一行相邻的数存在大 $1$ 的，就不能只操作前一行；如果某一行和前一行相邻的数存在相等的，就不能两行同时操作。

所以我们可以发现每一行有操不操作的这个 $0/1$ 状态，于是设计 $dp_{i,0/1}$ 表示考虑前 $i$ 行，第 $i$ 行不操作 / 操作的最小操作次数，规避掉前文所说的不合法情况转移即可。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=1005;
int n;
ll h[N][N],a[N],b[N],dp[N][2],ans=0;

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>h[i][j];
        }
    }
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    memset(dp,0x3f,sizeof(dp));
    dp[1][0]=0;
    ans=0;
    dp[1][1]=a[1];
    for(int i=2;i<=n;i++)
    {
        int x=0,y=0,z=0;
        for(int j=1;j<=n;j++)
        {
            int cz=h[i][j]-h[i-1][j];
            if(cz==1)x=1;
            if(cz==0)y=1;
            if(cz==-1)z=1;
        }
        if(x==0)dp[i][0]=min(dp[i][0],dp[i-1][1]);
        if(y==0)dp[i][0]=min(dp[i][0],dp[i-1][0]);
        if(y==0)dp[i][1]=min(dp[i][1],dp[i-1][1]+a[i]);
        if(z==0)dp[i][1]=min(dp[i][1],dp[i-1][0]+a[i]);
    }
    ans+=min(dp[n][0],dp[n][1]);

    memset(dp,0x3f,sizeof(dp));
    dp[1][0]=0;
    dp[1][1]=b[1];
    for(int i=2;i<=n;i++)
    {
        int x=0,y=0,z=0;
        for(int j=1;j<=n;j++)
        {
            int cz=h[j][i]-h[j][i-1];
            if(cz==1)x=1;
            if(cz==0)y=1;
            if(cz==-1)z=1;
        }
        if(x==0)dp[i][0]=min(dp[i][0],dp[i-1][1]);
        if(y==0)dp[i][0]=min(dp[i][0],dp[i-1][0]);
        if(y==0)dp[i][1]=min(dp[i][1],dp[i-1][1]+b[i]);
        if(z==0)dp[i][1]=min(dp[i][1],dp[i-1][0]+b[i]);
    }
    ans+=min(dp[n][0],dp[n][1]);
    if(ans>=0x3f3f3f3f3f3f3f3f/2)cout<<-1<<'\n';
    else cout<<ans<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：huangxintong (赞：2)

## 题意：
给定一个  $n^2$  的数组，可以对其每行（或每列）进行限一次的加一操作，每一个操作有不同的代价，求代价最小值。
## 思路：
首先要观察到一个性质：**行与列的操作互不影响**。这是显然的，因为如果对一整行（或列）加一，该行（或列）中相邻数字的差值不变。容易想到 dp。因为行与列之间不影响，所以考虑分别对行和列做动态规划。用 $f1[i][0/1]$ 表示第 $i$ 行是否加一之后处理完前 $i$ 行的最小代价。$f2[i][0/1]$ 同理。

转移（以行为例）：  
 $$f1[i][0] = \min(f1[i-1][0],f1[i-1][1])$$。

$$f1[i][1] = \min(f1[i-1][0]+a[i],f1[i-1][1]+a[i])$$。

最后输出行列最小值之和即可。当然还要注意判断转移是否可行还有是否有解。



```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e15;const int N = 1e3+5;
int f1[N][2],f2[N][2];int h[N][N],a[N],b[N];
signed main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i = 1;i<=n;i++)    for(int j = 1;j<=n;j++)    cin>>h[i][j];
	    for(int i = 1;i<=n;i++)    cin>>a[i];
	    for(int i = 1;i<=n;i++)    cin>>b[i];
	    f1[1][0] = 0,f1[1][1] = a[1];f2[1][0] = 0,f2[1][1] = b[1];
	    for(int i = 2;i<=n;i++){
	        f1[i][0] = f1[i][1] = inf;bool flag1 = 1,flag2 = 1,flag3 = 1;
	        for(int j = 1;j<=n;j++){
	            if(h[i][j]==h[i-1][j])    flag1 = 0;
	            if(h[i][j]==h[i-1][j]+1)     flag2 = 0;
	            if(h[i][j]+1==h[i-1][j])     flag3 = 0;
	        }
	        if(flag1)    f1[i][0] = min(f1[i][0],f1[i-1][0]);
	        if(flag2)    f1[i][0] = min(f1[i][0],f1[i-1][1]);
	        if(flag3)    f1[i][1] = min(f1[i][1],f1[i-1][0]+a[i]);
	        if(flag1)    f1[i][1] = min(f1[i][1],f1[i-1][1]+a[i]);
		}
		for(int i = 2;i<=n;i++){
			f2[i][0] = f2[i][1] = inf;bool flag1 = 1,flag2 = 1,flag3 = 1;
			for(int j = 1;j<=n;j++){
				if(h[j][i]==h[j][i-1])     flag1 = 0;
				if(h[j][i]==h[j][i-1]+1)    flag2 = 0;
				if(h[j][i]+1==h[j][i-1])    flag3 = 0;
			}
			if(flag1)    f2[i][0] = min(f2[i][0],f2[i-1][0]);
			if(flag2)    f2[i][0] = min(f2[i][0],f2[i-1][1]);
			if(flag3)    f2[i][1] = min(f2[i][1],f2[i-1][0]+b[i]);
			if(flag1)    f2[i][1] = min(f2[i][1],f2[i-1][1]+b[i]);
		}
		int k1 = min(f1[n][1],f1[n][0]);int k2 = min(f2[n][1],f2[n][0]);
		int ans = k1+k2;if(ans>=inf)    cout<<-1<<endl;
		else    cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：znzryb (赞：1)

## 思路讲解
首先，注意到，行操作和列操作是相互独立的，因为行操作不会影响列之间的差值，反之亦然。

然后让我们来考虑一点稍微复杂一点的情况（以列为例子），就是 $+1$ 本来不相同的变得相同了。这种有的可以处理，有的就不能处理了。

比如下面这个例子，是不能处理的，因为本来就是因为两列相同才 $+1$ 的，结果现在加完了还是相同，那怎么办呢？没办法呀，又不能加好几次。
![](https://cdn.luogu.com.cn/upload/image_hosting/ypii2j8j.png)

下面这个例子就是能处理的例子。注意到，虽然我们需要对第二列操作，但是第二列 $+1$ 以后和第一列相同了怎么办？那我们就对第一列也 $+1$ 不就好了吗。当然，能这么操作也是因为我们给第二列 $+1$ 不是因为第一列。
```
1
4
3 1 1 3    3 2..    4 2..
4 5 4 5 -> 4 6.. -> 5 6..
3 1 3 5    3 2..    4 2..
4 3 2 1    4 4..    5 4..
5 1 5 2
4 9 1 9
```
不难发现，上面这个例子还有可能传递，如第 $n$ 列需要 $+1$ 但是和第 $n-1$ 列相同了，所以第 $n-1$ 列也需要 $+1$，但 $n-1$ 列和第 $n-2$ 列相同了……。

当然，上面说了这么多，其实意思只有一个，就是不能以需要操作的行和列为主体，而应该以所有列为主体，因为操作行和列的操作可能导致其他行和列也需要操作。

不过，我们也发现行和列能怎么操作也只和相邻的行和列相关，那么如果按顺序转移也是可以的。

状态定义如下所列。
```cpp
// dpC[i][0] 表示保留第i列所需的最小花费
// dpC[i][1] 表示对第i列+1所需的最小花费
ll dpC[MAXN][2],dpR[MAXN][2];
```

## AC代码

https://codeforces.com/contest/2096/submission/318683142

```cpp
// Problem: C. Wonderful City
// Contest: Codeforces - Neowise Labs Contest 1 (Codeforces Round 1018, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2096/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// by znzryb
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define all(vec) vec.begin(),vec.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define fi first
#define se second
#define pb push_back
#define SZ(a) ((int) a.size())
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define getFro(vec) (vec.empty()?0:vec.front())
#define getBac(vec) (vec.empty()?0:vec.front())
#define debug(var) cerr << #var <<":"<<var<<"\n";
#define DEBUG(variable) \
    do { \
        std::cerr << #variable << ":"; \
        for (const auto& elem : variable) { \
            std::cerr << elem << " "; \
        } \
        std::cerr << "\n"; \
    } while (0)
#define uniVec(var) \
    do { \
        sort(var.begin(),var.end());\
        var.resize(unique(var.begin(),var.end())-var.begin());\
    } while (0)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<ll,ll> pll;
typedef array<ll,3> arr;
typedef double DB;
typedef pair<DB,DB> pdd;
typedef pair<ll,bool> plb;
constexpr ll MAXN=static_cast<ll>(1e3)+10,INF=static_cast<ll>(1e14)+3;
constexpr ll mod=static_cast<ll>(1e9)+7;
constexpr double eps=1e-8;

ll N,M,K,T,A[MAXN],B[MAXN];
ll H[MAXN][MAXN];
// bool vaC[MAXN],vaR[MAXN];
ll dr[4]={1,0,-1,0};
ll dc[4]={0,-1,0,1};
// dpC[i][0] 表示保留第i列，dpC[i][1] 表示对第i列+1所需的最小花费
ll dpC[MAXN][2],dpR[MAXN][2];

inline void solve(){
	cin>>N;
	FOR(i,0,N+5){
		dpC[i][0]=INF,dpC[i][1]=INF;
		dpR[i][0]=INF,dpR[i][1]=INF;
		FOR(j,0,N+5){
			H[i][j]=INF;
			
		}
	}
	FOR(i,1,N){
		FOR(j,1,N){
			cin>>H[i][j];
		}
	}
	FOR(i,1,N){
		cin>>A[i];
	}
	FOR(i,1,N){
		cin>>B[i];
	}
	dpR[1][0]=0;
	dpR[1][1]=A[1];
	FOR(r,2,N){
		bool zeroTo0=true;
		FOR(c,1,N){
			if(H[r][c]==H[r-1][c]){
				zeroTo0=false;
				break;
			}
		}
		if(zeroTo0){
			dpR[r][0]=min(dpR[r][0],dpR[r-1][0]);
		}
		bool zeroTo1=true;
		FOR(c,1,N){
			if(H[r-1][c]-H[r][c]==1){
				zeroTo1=false;
				break;
			}
		}
		if(zeroTo1){
			dpR[r][1]=min(dpR[r][1],dpR[r-1][0]+A[r]);
		}
		bool oneTo0=true;
		FOR(c,1,N){
			if(H[r-1][c]+1-H[r][c]==0){
				oneTo0=false;
				break;
			}
		}
		if(oneTo0){
			dpR[r][0]=min(dpR[r][0],dpR[r-1][1]);
		}
		bool oneTo1=true;
		FOR(c,1,N){
			if(H[r-1][c]-H[r][c]==0){
				oneTo1=false;
				break;
			}
		}
		if(oneTo1){
			dpR[r][1]=min(dpR[r][1],dpR[r-1][1]+A[r]);
		}
	}
	dpC[1][0]=0;
	dpC[1][1]=B[1];
	FOR(c,2,N){
		bool zeroTo0=true;
		FOR(r,1,N){
			if(H[r][c]==H[r][c-1]){
				zeroTo0=false;
				break;
			}
		}
		if(zeroTo0){
			dpC[c][0]=min(dpC[c][0],dpC[c-1][0]);
		}
		bool zeroTo1=true;
		FOR(r,1,N){
			if(H[r][c-1]-H[r][c]==1){
				zeroTo1=false;
				break;
			}
		}
		if(zeroTo1){
			dpC[c][1]=min(dpC[c][1],dpC[c-1][0]+B[c]);
		}
		bool oneTo0=true;
		FOR(r,1,N){
			if(H[r][c-1]+1-H[r][c]==0){
				oneTo0=false;
				break;
			}
		}
		if(oneTo0){
			dpC[c][0]=min(dpC[c][0],dpC[c-1][1]);
		}
		bool oneTo1=true;
		FOR(r,1,N){
			if(H[r][c-1]-H[r][c]==0){
				oneTo1=false;
				break;
			}
		}
		if(oneTo1){
			dpC[c][1]=min(dpC[c][1],dpC[c-1][1]+B[c]);
		}
	}
	ll ans=min(dpR[N][1],dpR[N][0])+min(dpC[N][1],dpC[N][0]);
	cout<<(ans>=INF?-1:ans)<<"\n";
#ifdef LOCAL
    cerr<<"dpR:\n";
    FOR(i,0,N){
    	cerr<<dpR[i][0]<<" ";
    }
    cerr<<"\n";
    FOR(i,0,N){
    	cerr<<dpR[i][1]<<" ";
    }
    cerr<<"\n";
    cerr<<"dpC:\n";
    FOR(i,0,N){
    	cerr<<dpC[i][0]<<" ";
    }
    cerr<<"\n";
    FOR(i,0,N){
    	cerr<<dpC[i][1]<<" ";
    }
    cerr<<"\n";
    cerr<<"\n";
#endif
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	// solve();
	return 0;
}
/*
AC
https://codeforces.com/contest/2096/submission/318683142
*/
```

---

