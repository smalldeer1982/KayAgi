# [AGC018B] Sports Festival

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc018/tasks/agc018_b

高橋君は、スポーツ大会を開こうと考えています。 スポーツ大会に参加するのは、$ 1 $ から $ N $ までの番号のついた $ N $ 人の人です。 また、大会で行うスポーツとして、$ 1 $ から $ M $ までの番号のついた $ M $ 個のスポーツが候補に上がっています。 高橋君は、これらの中から $ 1 $ つ以上（全てでもよい）のスポーツを選んで、スポーツ大会で実施します。

高橋君は、人 $ i $ が、$ j $ 番目に好きなスポーツが $ A_{ij} $ であることを知っています。 それぞれの人は、スポーツ大会で実施されるスポーツのうち、自分が最も好きなスポーツだけに参加し、他のスポーツには参加しません。

高橋君は、一つのスポーツにたくさんの人が集まり過ぎることを懸念しています。 そこで高橋君は、スポーツ大会で実施するスポーツをうまく選んで、最も多くの人が参加しているスポーツの参加人数を最小化したくなりました。 最も多くの人が参加しているスポーツの参加人数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ M\ \leq\ 300 $
- $ A_{i1} $ , $ A_{i2} $ , $ ... $ , $ A_{iM} $ は、$ 1 $ から $ M $ の順列である。

### Sample Explanation 1

スポーツ $ 1 $,$ 3 $,$ 4 $ を実施することにすると、人 $ 1 $ はスポーツ $ 1 $ に、人 $ 2 $ はスポーツ $ 3 $ に、 人 $ 3 $ はスポーツ $ 3 $ に、人 $ 4 $ はスポーツ $ 4 $ に参加します。 このとき、参加人数が最大のスポーツはスポーツ $ 3 $ で、その参加人数 $ 2 $ 人です。 また、参加人数が最大のスポーツの参加人数が $ 1 $ 人になるような方法は存在しないので、この例の答えは $ 2 $ になります。

### Sample Explanation 2

全員の好みが一致しているので、どうやっても一つのスポーツに $ 3 $ 人集まってしまいます。 よってこの例の答えは $ 3 $ です。

## 样例 #1

### 输入

```
4 5
5 1 3 4 2
2 5 3 1 4
2 3 1 4 5
2 5 4 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
2 1 3
2 1 3
2 1 3```

### 输出

```
3```

# 题解

## 作者：Ebola (赞：6)

直接考虑贪心

首先假设全选，然后统计答案。然后找到对答案造成贡献的罪魁祸首，把它删掉，再统计答案，直到全部删干净为止

删的过程中，每一行选择的元素必然是单调右移的，所以可以对每行维护一个指针，以便更快速地统计答案

证明显然。复杂度O(nm)

楼下那位没有维护每行的指针，复杂度比我多一个n

```cpp
#include<bits/stdc++.h>
using namespace std;


const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=310;
int A[N][N],n,m;
int pos[N],cnt[N];
bool vis[N];

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            A[i][j]=read();
    for(int i=1;i<=n;i++) pos[i]=1;
    int ans=INT_MAX;
    while(true)
    {
        int mx=0,cc=0;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            while(vis[A[i][pos[i]]]) pos[i]++;
            if(!A[i][pos[i]]) continue;
            cnt[A[i][pos[i]]]++;
            if(cnt[A[i][pos[i]]]>mx)
                cc=A[i][pos[i]],mx=cnt[cc];
        }
        if(!mx) break;
        ans=min(ans,mx);
        vis[cc]=1;
        for(int i=1;i<=n;i++)
            if(A[i][pos[i]]==cc) pos[i]++;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：4)

考虑贪心。

我们先假设所有项目都要举行，然后逐步调整。

如何调整呢？大胆猜想：**每次不举行目前参加人数最多的比赛，然后更新答案**。

事实上这个猜想是正确的，证明如下：

使用数学归纳法，显然第 $1$ 次删除是必要的（不然参加这场比赛的人不可能去参加别的比赛，参加人数不会变少）。考虑如果 $1$ 到 $k-1$ 次删除都是必要的，则如果答案不是当前状态，必然还要删去一些比赛。如果不删当前参加人数最多的比赛，则参加人数的最大值不会减少，因此第 $k$ 次删除是必要的。

然后很容易写出代码（用一个数组记录每个人参加他排名列表里的第几场比赛）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[305][305];
int now[305];
int cnt[305];
int vis[305];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)vis[i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
		now[i]=1;cnt[a[i][1]]++;
	}
	int ans=n;
	for(int fsz=1;fsz<=m;fsz++){
		int maxx=-1,x=0;
		for(int i=1;i<=m;i++)if(vis[i]&&cnt[i]>maxx)maxx=cnt[i],x=i;
		ans=min(ans,maxx);
		vis[x]=0;
		for(int i=1;i<=n;i++)
			if(a[i][now[i]]==x){
				while(now[i]<m&&!vis[a[i][now[i]]])now[i]++;
				cnt[a[i][now[i]]]++;
			}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Autream (赞：3)

~~好水的蓝题~~

#### 题意简述

一场运动会有 $M$ 个项目，$N$ 个人参加，你可以关闭至多 $M-1$ 项目使其不能被参加，其中第 $i$ 个人会优先参加第 $a_{i,j}$ 个项目（如果第 $a_{i,j}$ 个项目被关闭了，那么就参加第 $a_{i,j+1}$ 个，$j$ 从 $1$ 开始）。

现求使参加人数最多的项目的人数最少的关闭方案，输出最少人数。

---

#### 题目分析

这道题首先不要被题目中的“最多的最少” 给迷惑了，其实观察数据范围就可以发现，该题目支持 $O(N^3)$ 的算法，所以根本不需要什么二分答案。

对于 $1 \leq N,M \leq 300$，直接考虑暴力枚举，首先假设不删除任何比赛，此时就必定有一个参加人数最多的项目，那么就删除这个项目。

重复这个过程即可，最多删除 $M-1$ 次。

---

#### AC Code

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=305;
int n,m,ans=LLONG_MAX,a[N][N],b[N],vis[N];
signed main() {
    std::cin>>n>>m;
    rep(i,1,n) {
        rep(j,1,m) {
            std::cin>>a[i][j];
        }
    }
    int t=m;
    while(t--) {
        mem(b,0);
        rep(i,1,n) {
            rep(j,1,m) {
                if(!vis[a[i][j]]) {//记录第i个选手参加哪一场比赛
                    b[a[i][j]]++;
                    break;
                }
            }
        }
        int max=0,idx=0;//max: 人数最多的比赛的人数, idx: 人数最多的比赛的编号
        rep(j,1,m) {
            if(max<b[j]) {
                max=b[j];
                idx=j;
            }
        }
        ans=std::min(ans,max);
        vis[idx]=1;//删除这个比赛
    }
    std::cout<<ans;
    return 0;
}
```

---

## 作者：SegmentTree_ (赞：2)

贪心。  
考虑先全部选完，然后一个一个删掉。  
删的时候，为了让当前答案更小，肯定要贪心地选择对当前答案贡献最大的那个项目删。  
code:  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define ui unsigned int
#define i128 __int128
#define lid (id << 1)
#define rid (id << 1 | 1)
const int N = 2e5+5;
namespace tianyu{
    int n, m;
    int a[305][305];
    int cnt[305];
    bool vis[305];
    int ans = 114514;
	void awa(){
        cin >> n >> m;
        for (int i = 1;i <= n;i++){
            for (int j = 1;j <= m;j++) cin >> a[i][j];
        }
        while(1){
            memset(cnt, 0, sizeof cnt);
            for (int i = 1;i <= n;i++){
                for (int j = 1;j <= m;j++){
                    if (!vis[a[i][j]]){
                        ++cnt[a[i][j]];
                        break;
                    }
                }
            }
            int mx = 0, p = 0;
            for (int i = 1;i <= m;i++){
                if (cnt[i] > mx){
                    p = i;
                    mx = cnt[i];
                }
            }
            if (!mx) break;
            ans = min(ans, mx);
            vis[p] = 1;
        }
        cout <<ans;
	}
}
signed main(){
	int T = 1;
	while (T--) tianyu::awa();
	return 0;
}
```

---

## 作者：wjr_jok (赞：2)

因为 $n,m$ 都很小，所以考虑直接模拟过程来贪心。

每个人都只会参加一个活动，所以每次只需要删掉参加人数最多的活动就可以保证最多人数的活动人数最小。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,wz,bj,minn=INT_MAX;
int jz[301][301],tj[301],flag[301];
int main(){ 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>jz[i][j];
		}
	}
	for(int i=1;i<=m;i++){//模拟过程
		bj=wz=0;
		memset(tj,0,sizeof tj);
		for(int j=1;j<=n;j++){//每个人会参加的活动
			for(int k=1;k<=m;k++){
				if(!flag[jz[j][k]]){
					tj[jz[j][k]]++;
					break;
				}
			}
		}
		for(int j=1;j<=m;j++){
			if(tj[j]>=bj){//选出人数最多的
				bj=tj[j];
				wz=j;
			}
		}
		minn=min(minn,bj);
		flag[wz]=1;//鸽掉
	}
	cout<<minn;
	return 0;
} 
```

---

## 作者：tony0530 (赞：1)

### 做法

这题很有意思。

我们其实可以考虑贪心，我们先假设全选，统计出答案，此时就一定会有一个参加项目参加的人数最多，删除这个参加的人数最多的项目，再重新统计答案，直到最后求出最大值的最小值。

这个贪心是正确的，我们用**数学归纳法来证明**第 $1$ 次删除一定是有必要的，若 $n=k$ 时前 $n$ 个都是有必要的，则考虑 $n = k + 1$ 时，则答案若不是此状态，则还要删若干比赛。如果不删当前参加人数最多的比赛，则参加人数的最大值不会减少，因此当 $n = k + 1$ 时，前 $n$ 个都是有必要的，因此这个贪心是正确的。

-----

### 代码

蒟蒻码风丑，请见谅。

~~~cpp
for(int i = 1 ; i <= n ; i ++ ) count2[i] = 1;
int ans = 1e18;

while(true)
{
  int max_ = 0, res = 0;
  memset(count1, 0, sizeof count1);
  for(int i = 1 ; i <= n ; i ++ )
  {
    while(st[a[i][count2[i]]]) count2[i] ++ ;
    if(a[i][count2[i]] == 0) continue;
    count1[a[i][count2[i]]] ++ ;
    if(count1[a[i][count2[i]]] > max_) res = a[i][count2[i]], max_ = count1[res];
  }
  if(max_ == 0) break;
  ans = min(ans, max_);
  st[res] = true;
  for(int i = 1 ; i <= n ; i ++ )
    if(a[i][count2[i]] == res)
      count2[i] ++ ;
}
~~~

---

## 作者：do_it_tomorrow (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/agc018b-sports-festival/)
## 题目大意
有 $n$ 个人 $m$ 个活动，告诉你每一个人对于活动喜欢程度的排序，你可以鸽掉一些活动。如果一个最喜欢的活动被鸽了，那么他就会参加次喜欢的，依次类推直到参加为止。

求参加人数最多的那个项目，参加人数最少是多少。

## 思路
**做法**：

首先模拟出每一个活动的参加人数，依次将人数最多的活动鸽掉，一遍鸽一遍统计最小值。

**理由**：

假设你已经鸽掉了一些活动，你么现在总能找到一个参加人数最多的项目，假设这个项目是第 $x$ 个项目。如果将非 $x$ 的项目鸽掉，那么参加第 $x$ 个项目的人就并不会减少反而还会增加，这对将整体的最大值减小是没有任何效果的。

假设你鸽掉了第 $x$ 个项目，那么你肯定就又可以找到一个参加人数是最多的项目，假设是第 $y$ 个项目。那么如果不鸽掉第 $y$ 个项目与前面鸽掉第 $x$ 个项目的效果其实是一样的。所以在这次操作就只能将 $y$ 鸽掉，否则就没有意义。
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305;
int n,m,a[N][N],s[N],top[N],ans=1e18;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			top[i]=1;
		}
	}
	for(int i=1;i<=n;i++){
		s[a[i][1]]++;
	}
	for(int i=1,p,mmax;i<=m;i++){
		mmax=0;
		for(int j=1;j<=m;j++){
			if(s[j]>mmax){
				mmax=s[j];
				p=j;
			}
		}
		ans=min(ans,mmax);
		s[p]=-1;
		for(int j=1;j<=n;j++){
			bool flag=0;
			while(s[a[j][top[j]]]==-1){
				top[j]++;
				flag=1;
			}
			if(flag){
				s[a[j][top[j]]]++;
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Tokai__Teio (赞：1)

# [[AGC018B] Sports Festival](https://www.luogu.com.cn/problem/AT_agc018_b)

[更好的阅读体验](https://undead-fire-ace.github.io/2023/09/24/AGC018B/)

## 题面翻译

Takahashi 举办了一场运动会，这场运动会有 $M$ 个项目，有 $N$ 个人来参加。

给你一个 $N \times M$ 的二维数组 $a$ ，其中 $a_{i,j}$ 表示第 $i$ 个人，她心目中排名第 $j$ 的项目是哪个。

这 $M$ 个项目不一定全都要进行，可以选其中一些项目进行，剩下的都鸽掉，当然肯定不能鸽掉所有 $M$ 个项目。

每个人会在所有开展的项目当中，选择她心目中排名最高的那个项目参加。

因此，如果开展全部项目的话，可能某个项目的人数会爆多无比，所以 Takahashi 决定，只开展其中的一部分项目，使得参加人数最多的那个项目，参加人数尽量少。

请输出这个值。  

———from[@__stdcall](https://www.luogu.org/space/show?uid=8212)

## 分析

首先对于这 $m$ 个赛事，我们可以一开始都选上，然后我们考虑怎么会让答案变的更优，既然我们要满足最大值最小，那么一个比较显然的想法就是我们每次删去参加人数最多的比赛，然后这个答案一定是不会变的更劣的，因为我们只改动了一个项目，只会发生两种情况

一：对于所有的涉及到改动的人在删掉当前的活动后，如果下一个优先级的活动都一样，那么答案是跟删之前相等的。

二：如果他们的下一个优先级的活动不一样，那么最大值一定是比之前小。

所以这么贪心一定是对的，同时我们对于每个活动删还是不删，一定都是删去的是当前位置之后的位置，那么每个人选择的活动一定是往后走的，然后按照上面的贪心策略删就行了。

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

namespace read_write
{
    template <typename T>
    inline void read(T &x)
    {
        x = 0;
        T f = 1;
        char ch = getchar();
        while (ch > '9' || ch < '0')
        {
            if (ch == '-')
                f = -1;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - '0', ch = getchar();
        x *= f;
        return;
    }

    template <typename T, typename... Args>
    inline void read(T &first, Args &...args)
    {
        read(first);
        read(args...);
    }

    template <typename T>
    inline void write(T x)
    {
        if (x < 0)
        {
            x = -x;
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }

    template <typename T>
    T max(T x, T y)
    {
        return x > y ? x : y;
    }

    template <typename T>
    T min(T x, T y)
    {
        return x > y ? y : x;
    }

    template <typename T>
    void swap(T &a, T &b)
    {
        T tem = b;
        b = a;
        a = tem;
    }
}

namespace Solve
{
    using namespace read_write;

    const int N = 520;

    int n, m, ans;
    int a[N][N];
    int cnt[N], cur[N];
    bool st[N];

    void solve()
    {
        read(n, m);

        for(int i = 1 ; i <= m ; ++ i)  //一开始将所有的活动选上
            st[i] = true;
        for(int i = 1 ; i <= n ; ++ i)
        {
            for(int j = 1 ; j <= m ; ++ j)
                read(a[i][j]);
            cur[i] = 1;
            ++ cnt[a[i][1]];   //记录每个活动参加的人数
        }

        ans = n;
        for(int k = 1 ; k <= m ; ++ k)
        {
            int mx = -1, pos = 0;
            for(int i = 1 ; i <= m ; ++ i)    //找到当前的最大值和是哪个活动
                if(st[i] && cnt[i] > mx)
                    mx = cnt[i], pos = i;
            ans = min(ans, mx);   //更新一下答案
            st[pos] = false;   //删去这个活动
            for(int i = 1 ; i <= n ; ++ i)  //更新有影响的人的选择的活动
            {
                if(a[i][cur[i]] == pos)
                {
                    while(cur[i] < m && !st[a[i][cur[i]]])
                        ++ cur[i];
                    ++ cnt[a[i][cur[i]]];
                }
            }
        }

        write(ans);
    }
}

int main()
{
    Solve :: solve();

    return 0;
}
```

---

## 作者：Zhao_daodao (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_agc018_b)
# 题目分析
### 贪心。
统计当前最受欢迎的，把它删掉。重复到删掉后最大值的最小值增加。
### 证明
反推，显然第 $1$ 次删除是必须的（否则参加这场比赛的人不可能去参加别的比赛，参加人数不会变少）。

对于第 $k$ 次删除，如果答案不是当前状态，必然还要删去一些比赛。如果不删当前参加人数最多的比赛，则参加人数的最大值不会减少，因此第 $k$ 次删除是必要的。
### 方法
每一次的项目人数通过数组 $s$ 记录。$c$ 判断是否停止。

# 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=3e2+5;
int n,m;
int ans=1e17,tot;
int a[MAXN][MAXN];
int s[MAXN];
int c[MAXN];
bool used[MAXN];
signed main(){   
    cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)s[i]=1;
	for(int i=1;i<=m;i++){
		int cnt=0;
		memset(c,0,sizeof c);
		for(int j=1;j<=n;j++){
			c[a[j][s[j]]]++;
			if(c[a[j][s[j]]]>cnt)cnt=c[a[j][s[j]]],tot=a[j][s[j]];
	    }
        used[tot]=1;
        ans=min(ans,cnt);
        for(int j=1;j<=n;j++)while(used[a[j][s[j]]])s[j]++;
	}
	cout<<ans;
} 
```

---

## 作者：Forward_Star (赞：1)

大意：n个人，m种体育项目，A(i,j)表示第i个人对第j项目喜爱程度排名；选出一些体育项目，每个人会参加这些体育项目中排名最小（最前）的体育项目；求出一种方案，保证此方案中参加人数最多的体育项目参加人数最少（相比于其它方案），并输出这个最小值。

 

法0：枚举子集，时间复杂度O(n*2^m)，超时；

正解：贪心，先全选体育项目，每次删去人数最多的体育项目，得到不同的方案，记录这些方案中参加人数最多的体育项目的人数，取最小值；共能得到m种方案，每种方案需要先统计每种体育项目的参加人数，枚举n*m次次，并取最大值，枚举n次（虽然我代码用了排序，但其实是不需要的），故时间复杂度为O(mn+m^2*n)。

代码：
```cpp
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
    struct newdata
    {
        int label,cnt;
    };
    int n,m;
    int a[301][301];
    newdata rankm[301];
    bool used[301];
bool cmp(newdata i,newdata j)
{
    return (i.cnt>j.cnt);
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            if (j==1) rankm[a[i][j]].cnt++;
        }
    int now=0;
    for (int i=1;i<=m;i++)
        rankm[i].label=i;
    int ans=2147483647;
    while (now<m)
    {
        sort(rankm+1,rankm+m+1,cmp);
        ans=min(ans,rankm[1].cnt);
        used[rankm[1].label]=true;
        memset(rankm,0,sizeof(rankm));
        for (int i=1;i<=m;i++)
            rankm[i].label=i;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
            	if (!used[a[i][j]])
            	{
					rankm[a[i][j]].cnt++;
					break;
				}
        now++;
    }
    printf("%d",ans);
}

```
顺便宣传下我的博客：https://blog.csdn.net/weixin_39872717/article/details/81117431

---

## 作者：Chenaknoip (赞：0)

一道贪心题。

假设当前已经关闭了 $x$ 个项目，设人数最多的项目为 $k$。如果关闭除 $k$ 外的项目，原本就选 $k$ 的人一定还会选 $k$，而其他人反而有可能转变成选 $k$，所以一定不会使 $k$ 的人数减少。这样一定是不优的。

因此，每次关闭时直接选出人数最多的那个项目删除即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[1001][1001], cnt[1001];
bool clo[1001]; // 是否被关闭
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 0x7f7f7f7f;
    for (int t = 1; t <= m; t++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!clo[a[i][j]]) {
                    cnt[a[i][j]]++; // 统计人数
                    break;
                }
            }
        }
        int maxn = 1;
        for (int i = 2; i <= m; i++) {
            if (cnt[i] > cnt[maxn]) maxn = i;
        }
        ans = min(ans, cnt[maxn]); // 更新答案
        clo[maxn] = true;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：I_LOVE_MATH (赞：0)

### 题目大意

举办一场运动会，有 $N$ 人，$M$ 个项目，每个人所有项目都有一个排名，会选择参加排名最高且开设的项目，现在要开设若干项目使得人数最多的项目人数尽可能小，求这个最小值。

### 解题思路

考虑**贪心**。

一开始，我们不妨开设所有项目，设人数最多的项目为 $x$。

如果我们不关闭项目 $x$，最大值就不会变，因此我们考虑关闭项目 $x$，将原来参加 $x$ 的人分配到他们排名次高的项目（可以用 `vector` 存储参加这个项目的人）。

于是，又会有新的人数最多的项目，我们重复这个过程，直到只剩下一个项目，期间最大值的最小值即为答案。

注意：在重新分配项目时，不仅要根据次高排名，还要判断这个项目现在是否开设，不开设还要再往后。

### 代码
```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

const int N = 310;

int n, m, ans = INT_MAX;
int a[N][N], b[N][N], sz[N];
vector<int> e[N];
bool vis[N];

struct SGT
{
	#define ls x << 1
	#define rs x << 1 | 1
	int lc[N << 2], rc[N << 2], dat[N << 2], id[N << 2];
	
	inline void push_up(int x)
	{
		if (dat[ls] >= dat[rs])
		{
			dat[x] = dat[ls];
			id[x] = id[ls];
		}
		else
		{
			dat[x] = dat[rs];
			id[x] = id[rs];
		}
	}
	
	void build(int x, int l, int r)
	{
		lc[x] = l, rc[x] = r;
		if (l == r)
		{
			dat[x] = sz[l];
			id[x] = l;
			return;
		}
		int mid = (l + r) / 2;
		build(ls, l, mid);
		build(rs, mid + 1, r);
		push_up(x);
		return;
	}
	
	void add(int x, int p, int k)
	{
		if (p > rc[x] || p < lc[x])
		{
			return;
		}
		if (lc[x] == rc[x])
		{
			dat[x] += k;
			return;
		}
		add(ls, p, k);
		add(rs, p, k);
		push_up(x);
		return;
	}
} t;

inline void add(int u, int v)
{
	e[u].push_back(v);
	sz[u]++;
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> a[i][j];
			b[i][a[i][j]] = j;
			if (j == 1)
			{
				e[a[i][j]].push_back(i);
				sz[a[i][j]]++;
			}
		}
	}
	t.build(1, 1, m);
	for (int i = 1; i < m; i++)
	{
		int x = t.id[1];
		ans = min(ans, t.dat[1]);
		for (auto it : e[x])
		{
			int v = b[it][x] + 1;
			while (vis[a[it][v]])
			{
				v++;
			}
			e[a[it][v]].push_back(it);
			t.add(1, a[it][v], 1);
		}
		t.add(1, x, -t.dat[1]);
		e[x].clear();
		vis[x] = 1;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：M_WC1S_M0 (赞：0)

### B - Sports Festival

#### 题目大意 

有 $N$ 个人参加 $M$ 个项目的运动会，这 $M$ 可以至多被删去 $M-1$ 个。

第 $i$ 个人会参加序列 $a_i$ 中第一个可以被参加的项目 $a_{i,j}$。

现在要使参加人数最多的项目人数最少，求这个最小人数。

#### 解题思路

$N$ 和 $M$ 都比较小，考虑直接贪心并模拟：

- 最开始假设所有的 $M$ 个项目全部设立。
- 求出每个项目的人数，然后将人数最多的项目删去，知道只剩一个项目位置。

这样的策略显然是最优的。

时间复杂度 $O(N \times M)$，直接按照该策略模拟即可。

```cpp
int n,m;
cin>>n>>m;

vector<int> rk(n+5); //每个人当前会参加的项目
vector<vector<int> > a(n+5,vector<int>(m+5));
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        cin>>a[i][j];
    }
    rk[i]=1; //最开始一个都没有删除
}

int ans=1<<30;
vector<bool> deleted(m+5);

while(114514){
    int loc=0,maxn=0;
    vector<int> cnt(m+5,0);

    for(int i=1;i<=n;i++){
        while(deleted[a[i][rk[i]]])rk[i]++; //更新 rk
        if(a[i][rk[i]]==0)continue; 

        cnt[a[i][rk[i]]]++; //贡献人数加一
        if(cnt[a[i][rk[i]]]>maxn){ //更新人数最多的项目
            maxn=cnt[a[i][rk[i]]];
            loc=a[i][rk[i]];
        }
    }
    if(!maxn)break; //如果 maxn 为0，代表删的一个项目不剩了

    deleted[loc]=1;
    ans=min(ans,maxn);
    for(int i=1;i<=n;i++){
        if(a[i][rk[i]]==loc)rk[i]++;
    }
}

cout<<ans<<"\n";
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
翻译可能是我目前见到的最亲切的话语。

算法是贪心。
## 分析。
求最大人数，并且要尽可能少，同时还可以进行删减操作，具有后效性，所以很明显是贪心。

我们首先可以假设所有活动都举办，然后每次贪心求出当前最优解。就是删除一些项目，但是如何删去这些项目呢？再每一次进行操作时，我们在此前终止举办的活动的人数会转移到其它活动，此时一定存在一个活动，在所有活动人数中最多，我们为了让参与人数最多的人尽可能少，所以我们不能保留这个人数最多的活动，所以解散它，然后这个活动的人会跑到别的活动中，就会出现一个新的人数最多的活动，随后再解散它，如此反复。

为什么这样最优？如果不删当前参加人数最多的活动，则参加人数的当前**最大值**不会减少，仍会成为最大值，我们记这个最大值为 $a_0$ 则解散后这些人就会分布到其它活动中，那此时解散后的活动中的最大人数一定小于或等于 $a_0$ 因此这是减少最多人数的有效方式。

关于上述的小于等于。如果下一个的每人的优先级的活动都一样，那么都会到那个活动中，那么答案是跟删之前相等的。否则一定小。

标记一下这个项目，记录人数，然后模拟即可。

代码如下，仅供参考：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#define MAXX 0x3f3f3f3f
using namespace std;
int n,m,a[305][305];
int vis[305];
int sum,reid,ans=MAXX,t[305],id[305]={1};
int main(){
	cin>>n>>m;
	//memset(id,1,sizeof(id));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
		    cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;i++){
		sum=0;
		memset(t,0,sizeof(t));
		for(int j=1;j<=n;j++){
			t[a[j][id[j]]]++;
			int tot=t[a[j][id[j]]];
			if(tot>sum){
	            sum=tot;
				reid=a[j][id[j]];
				//cout<<"pd:"<<tot<<" "<<reid<<"\n";
			}
	    }
	    ans=min(ans,sum);
        vis[reid]=1;
        for(int j=1;j<=n;j++){
		    for(;vis[a[j][id[j]]];){
			    id[j]++;
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
} 
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：ncwzdlsd (赞：0)

显然，这是一道贪心题。我们先大胆假设所有的活动都要举行，然后在贪心的过程中不断更新出最优答案。显然我们要从这些比赛中删除一些活动达到目的。考虑我们该删除哪些比赛，经过一些小小的分析之后，我们可以得到一个很显然的结论，就是对于当前状态，我们取消当前参与人数最少的活动。

为什么这样是正确的？考虑对于一场人数最多的比赛，我们让它取消，那么喜欢这场活动的人就一定会跑去参加其他活动，这样就可以降低人数最大值，达到减少参加人数最多的活动的人数的目的。

具体代码实现也很简单，不停地扫即可，注意一个细节，如果某一活动的参加人数最多，在让参与该活动的人更换目标活动时，应该不停地跳找到下一个还没有被标记的活动：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int a[305][305],id[305],cnt[305];//cnt[i]表示选第i个项目的人数 
bool vis[305];

signed main()
{
	int N,M;cin>>N>>M;
	int ans=0x3f3f3f,pos=0;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++) cin>>a[i][j];
	for(int i=1;i<=N;i++) id[i]=1;
	for(int i=1;i<=M;i++)
	{
		int tmp=0;
		memset(cnt,0,sizeof cnt);
		for(int j=1;j<=N;j++)
		{
			cnt[a[j][id[j]]]++;
			if(cnt[a[j][id[j]]]>tmp)
	            tmp=cnt[a[j][id[j]]],pos=a[j][id[j]];
	    }
        vis[pos]=1;
        ans=min(ans,tmp);
        for(int j=1;j<=N;j++) while(vis[a[j][id[j]]]) id[j]++;

	}
	cout<<ans<<endl;
	return 0;
} 
```

[通过记录](https://atcoder.jp/contests/agc018/submissions/39687428)

---

## 作者：Yldar (赞：0)

  ~~突然第一个A题~~开心。   
  这是一道模拟题，用数组把每个人喜爱的项目排名。然后一遍一遍扫，然后找到最多人参加的项目，并且记录有多少人，然后把这个项目标记，用num[i]记录每个人现在参加的是哪个项目，如果每个人当前喜爱的项目被标记，num[i]++，当然可能num[i]++后还是被标记，所以用一个while，然后每次循环找到当前项目最多的，然后一一删除，必须删除最大的，否则不会对答案产生影响。详细解释在代码里面吧。
  ```
#include<bits/stdc++.h>
 
using namespace std;

inline int read(){
    int w=1,s=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if (ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') {s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}

int a[400][400],f[400],vis[400],num[4100];
//a记录每个人的喜好，f记录每一次每个项目有多少人选，vis记录每个项目是否被标记(删除)，num表示每个人选到第几个
int main(){
    int n=read(),m=read();
    int ans=999999;
    int maxx=0,pos;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++) a[i][j]=read();
    for(int i=1;i<=n;i++) num[i]=1;//肯定每个人先选自己最喜爱的
    for(int i=1;i<=m;i++){
        maxx=0;
        memset(f,0,sizeof(f));//每次删，数组清0
          for(int j=1;j<=n;j++) {
              f[a[j][num[j]]]++;
              if (f[a[j][num[j]]]>maxx) {
                  maxx=f[a[j][num[j]]];
                  pos=a[j][num[j]];
              }
          }
         vis[pos]=1;//标记这个项目
         ans=min(ans,maxx);//更新答案
         for(int j=1;j<=n;j++){
         while(vis[a[j][num[j]]]==1) {num[j]++;}
         //如果这个人喜欢的项目被标记，只能不得以选下一个，知道当前的没被标记。
         }
    }
    cout<<ans;//输出
    return 0;
}
```

---

