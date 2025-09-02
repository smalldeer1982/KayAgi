# Tournament

## 题目描述

你正在组织一场拳击锦标赛，共有 $n$ 名拳击手参加（$n$ 是 $2$ 的幂次），其中一位是你的朋友。所有拳击手的实力各不相同，范围从 $1$ 到 $n$，拳击手 $i$ 在与拳击手 $j$ 的比赛中获胜当且仅当 $i$ 的实力强于 $j$。

锦标赛的组织方式如下：$n$ 名拳击手将被分成若干对；每对中的败者离开比赛，而 $\frac{n}{2}$ 名胜者晋级到下一轮，再次分成若干对，所有对中的胜者继续晋级，依此类推，直到仅剩一名拳击手（被宣布为冠军）。

你的朋友非常想赢得比赛，但他可能不是最强的拳击手。为了帮助你的朋友获胜，你可以贿赂他的对手：如果你的朋友与你已贿赂的拳击手对战，即使他的实力较低，他也会获胜。

此外，在每一轮中，你可以自由分配拳击手的配对。

实力为 $i$ 的拳击手可以被贿赂，但需要支付 $a_i$ 美元。请问为了让你的朋友赢得比赛，你最少需要花费多少美元？假设在每一轮中你可以自由安排拳击手的配对。

## 说明/提示

在第一个测试用例中，无论你如何分配拳击手的配对，你的朋友都是最强的拳击手，无论如何都会获胜。

在第二个测试用例中，你可以按如下方式分配拳击手（你的朋友是 $2$ 号）：

$1 : 2, 8 : 5, 7 : 3, 6 : 4$（拳击手 $2, 8, 7$ 和 $6$ 晋级到下一轮）；

$2 : 6, 8 : 7$（拳击手 $2$ 和 $8$ 晋级到下一轮，你需要贿赂实力为 $6$ 的拳击手）；

$2 : 8$（你需要贿赂实力为 $8$ 的拳击手）。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 9 1 -1
```

### 输出

```
0```

## 样例 #2

### 输入

```
8
11 -1 13 19 24 7 17 5
```

### 输出

```
12```

# 题解

## 作者：Dovе (赞：5)

## 题目大意

&#8195;&#8195;有 $n$ 个人，贿赂他的代价为 $a[i]$。这些人中，贿赂代价为 $-1$ 的是你的朋友。现在，你可以两两配对，使得编号小的被淘汰，但是，如果你贿赂了编号大的，那么编号大的被淘汰，而编号小的留下。问：使得你朋友夺得冠军的最小代价

## 大致思路

&#8195;&#8195;考虑贪心。

&#8195;&#8195;首先，我们可以发现，如果说朋友不是最后一个，也就是说，必然需要贿赂第 $n$ 个人。那么，在我们贿赂完第 $n$ 个人后，他可以帮助我们最多解决掉 $n / 2$ 个人。同时，对于那些排名小于朋友的，不需要考虑。

&#8195;&#8195;如果，朋友的排名小于 $n / 2$，也就是说，我们必须要再贿赂一个人。为了使得代价最小，则贿赂 $[n / 2,~n]$ 中代价最小的。

&#8195;&#8195;同理，如果朋友的排名小于 $n / 4$。就需要再贿赂 $[n / 4,~n]$ 中代价最小的

&#8195;&#8195;那么，综上，我们需要贿赂 $\log n$ 个人，用一个小根堆记录最小代价，在每次访问到 $2$ 的幂次个人时，取出小根堆中的第一个。直到访问到朋友。


## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int maxn = 4e5 + 50;

int n;
int a[maxn];

priority_queue<int, vector<int>, greater<int> > q;

int ans;

signed main()
{
    ios::sync_with_stdio (false);

    cin >> n;

    for (register int i = 1; i <= n; ++i) cin >> a[i];

    for (register int i = n; a[i] != -1; --i)
    {
        q.push (a[i]);

        if (! (i & (i - 1))) // 判断是否是 2 的幂次
        {
            ans += q.top();
            q.pop();
        }
    }

    return cout << ans << endl, 0;
}
```

---

## 作者：installb (赞：5)

这题思路真的巧妙啊..  

提供一个贪心思路 和官方题解不同  

首先最后一个人如果不是自己一定是要付钱的 因为没有人能打败他 他一定会留到最后一局  
然后在那个$-1$这个点(后面记为$x$)前面的人打了也不用付钱 所以全当作付0块钱  

这里感觉用$n$说太抽象了 举个具体的例子好了 比如有$16$个人  
如果有$\leq \dfrac{n}{2}=8$个在$x$右边的数 可以视为用左边的$0$补满$8$个数(因为价格为0无所谓了) 然后组成一个完全二叉树结构 然后那么这些人经过$(log_2 n)-1=3$轮后一定只剩下一个人 就是最右边的数   

然后让这个人**在最后一轮**和$x$比  
```cpp
0 1 2 3 4 5 6 x 8 9 A B C D E F
8 - 9 , A - B , C - D , E - F
9 - B , D - F
B - F

// 最后一轮为 x - F
```

如果不止$8$个数呢  
这样我们只给一个人付钱就不行了 先假设只需要给两个人付钱  
不过我们还是可以挑出来$8$个人 让他们只剩下最右边那一个数  

然后在剩下的人中继续做 这些人里选出来一个给钱 那么这个人在**倒数第二轮**就需要和$x$比 于是'这些人'只能比两轮 所以最多只能有$4$个人   
同样不满4个可以把左边的0拉到右边去 这一步只是方便理解 实际实现没有必要  
![](https://cdn.luogu.com.cn/upload/image_hosting/0gjdsey5.png)  
蓝圈里是$x$  
我们需要最小化两个红圈里数的和

如果给两个人付钱还不够  
于是我们需要在 同时满足 最后$8$个数中选出一个 在最后$12$个数中选出两个 在最后$8+4+2=14$个数中选出三个 ...  

可以当成选完$8$个后 去掉选的那个 然后在最后$12$个里剩下的$11$个里找个最小的 后面依次类推  
最小化花钱数 可以直接贪心 用堆实现  

我们倒序从大到小加入数 观察到加入第$i$个数后 如果$i=2^k$则取出目前还没选过的人中花钱最小的那个  
碰到$x$就可以结束了 因为再往后一定不会花钱了


代码非常短
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL; // 不开LL见祖宗

LL n,val[400005];
LL ans = 0;
priority_queue <LL,vector<LL>,greater<LL> > q; // 小根堆
LL pw2[400005] = {0}; // pw2[i]记录i是不是2^k

int main(){
	cin >> n;
	for(LL i = 1;i <= n;i ++) cin >> val[i];
	for(LL i = 1;i <= 18;i ++) pw2[(1 << i)] = 1;
	for(LL i = n;i >= 1;i --){
		if(val[i] == -1) break;
		q.push(val[i]);
		if(ot[i]){
			ans += q.top();
			q.pop();
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：3)

# 前言

学校里有人随机跳题跳到的，看到是水紫赶紧写题解。

# 正文

考虑朋友不是第 $N$ 位。首先显然让朋友之前的人自生自灭，考虑朋友能撑几轮（设朋友为第 $pos$ 位）。

~~大概是一个什么 $\log_2$，~~ 接下来考虑贿赂这一局必须贿赂的是谁，显然要贿赂最小的。但是这样考虑不清楚具体贿赂完之后是什么情况，于是考虑倒着思考这个问题。

显然第 $N$ 位肯定要被贿赂，因为没有人打得过。接下来发现第 $N$ 位一路上可以帮我们杀了 $\dfrac{N}{2}$ 个人。但是发现朋友不一定活到最后一轮。

那么按照分治思想，我们为了让朋友活到最后一轮，必须找一个**不经过贿赂就有可能活到倒数第二轮**的选手，也就是编号为 $[\dfrac{N}{2}, N]$ 内的选手。这样我们需要贪心的选择代价最小的一位。

但是朋友有可能连倒数第二轮都活不到，于是考虑这一轮的一个**不经过贿赂就有可能活到倒数第三轮**的选手，也就是编号为 $[\dfrac{N}{4}, N]$ 内的选手。

以此类推，我们结合最开始的思路，可以考虑令 $i$ 从 $N$ 开始倒着遍历，用一个小根堆维护 $[i, N]$ 内的最小值，然后每当 $i$ 为 $2$ 的幂次就让答案加上当前维护的最小值。只要找到朋友就不再统计答案。

# 代码

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll N, ans;
ll arr[1 << 20];

priority_queue< ll, vector<ll>, greater<ll> > heap;

signed main()
{
	cin >> N;
	for(ll i = 1; i <= N; ++ i)
		cin >> arr[i];
	
	for(ll i = N; i >= 1; -- i)
	{
		if(arr[i] == -1) break;
		heap.push(arr[i]);
		if(!(i & (i - 1))) ans += heap.top(), heap.pop();
	}
	
	cout << ans << endl;
	return 0;
}
```

# 后言

吐槽一下题目翻译未体现原文中 "$n$ is a power of 2" 这句话。

---

## 作者：hh20080501hh (赞：1)

# 题目
[题目在这里](https://www.luogu.com.cn/problem/CF1260E)

题意简述：给你 $n$ 个人，每个人有一个贿赂代价，你可以贿赂一些人。这 $n$ 个人会打 $\log_2 n$ 轮比赛，实力强的获胜。现在你要让某个人（你的朋友）获得冠军，如果这个人打被贿赂的人，那么他一定获胜。求最小贿赂代价。
# 分析
容易发现比朋友弱一定可以被朋友搞死，不需要贿赂。而最强的如果不是朋友，那么他一定需要被贿赂，不然朋友不可能是冠军。

比赛要打 $\log n$ 轮，记比朋友弱的人数为 $cnt$ 那么朋友就会打 $cnt/2$ 轮比自己弱的，也就是说这几轮不需要贿赂。所以我们要贿赂 $\log n-cnt/2$ 个人，这里 $cnt/2$ 向上取整。

但是取比朋友强的且代价最小的 $\log n-cnt/2$ 个人是错误的。因为可能有代价小的但是比较弱，活不到跟朋友打的那一轮。

我们发现一个性质：若有 $x$ 个人存活，那么这一轮一定要死 $x/2$ 个人，而这 $x$ 个人中朋友要占一个，所以还会有一个人被朋友搞死，那我们让这个被搞死的人贿赂代价最小就行了。

所以我们在 $2$ 的整数次幂的地方更新一下要贿赂的人就可以了，因为这个时候这段区间里贿赂代价最小的一定是存活的，可以跟朋友打。

那这应该是从 $n$ 开始选还是从 $1$ 开始选呢？我们发现与 $1$ 相比，越靠近 $n$ 的人与朋友打的轮数就越少，所以要贿赂的也就越少，那么我们从 $1$ 开始标记是否选择才是对的。当然，记录最小代价的要从 $n$ 开始。

# 代码
可以预处理一下 $2$ 的整数次幂，就不用每次都计算了，代码比较简单，主要是想怎么选比较困难。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5+10;

int n;
int a[N];
bool mi[N];
int res;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> n;
	for (int i=1 ; i<=n ; i++)
	{
		cin >> a[i];
	}
	for (int i=1 ; i<=n ; i*=2) mi[i] = 1;
	priority_queue<int , vector<int> , greater<int> > q;
	for (int i=n ; i>=1 ; i--)
	{
		if (a[i]==-1) break;
		q.push(a[i]);
		if (mi[i]) 
		{
			res += q.top();
			q.pop();
		}
	}
	cout << res << '\n';
	return 0;
}
```

---

## 作者：tai_chi (赞：1)

题目中给定 $n$ 是 $2$ 的次幂。

贪心地，可以让实力强的人打败比朋友强的选手，比朋友弱的无需考虑。

考虑如何贪心最贪心：让 $n$ 号选手干掉后一半的选手，如果朋友干不掉前一半就让一个人再干掉前一半的一半。

实现只需要维护一个小根堆，记录路径上便宜的人，每到 $2$ 的次幂就贿赂一个最便宜的，代码非常短。

```cpp
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int ans = 0;
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = n; a[i] != -1; i--)
	{
		q.push(a[i]);
		if ((1 << (int)log2(i)) == i)
			ans += q.top(), q.pop();
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Soulist (赞：1)

考虑贪心，显然对于答案有影响的只有在$-1$这个点身后的点

然后考虑最大的那个人，显然他是必须要被贿赂的，根据贪心的想法，我们肯定要使得此人去打败尽量多的人

其次，可以注意到我们最多贿赂$\log n$个人，而这个人假设是第$i$个被贿赂的，则其可以打败的人数应该依次是$\frac{n}{2}-1,\frac{n}{4}-1$依次类推，这是因为一个人要和此人对战必然会先打一些人啥的，可以自行推理得到（

考虑$dp$，即从后往前考虑，考虑到第$i$个人，此时我们已经贿赂了$k$个人，那么这$k$个人可以消灭的人数总数(包括他本身)应该为$\frac{n}{2}+\frac{n}{4}+...$当然到第$i$个人的时候，你应当把不合法的$dp$值设成$inf$

这样就可以了qwq

这道题咋说吧，挺好的

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 4e5 + 5 ; 
const int inf = 123456789000 ; 
int n, m, t, a[N], Inv[30], dp[N][30], Ans ; 
signed main()
{
	n = gi() ; rep( i, 1, n ) {
		a[i] = gi() ; if( a[i] == -1 ) m = i, a[i] = 0 ; 
	} Inv[0] = n ; 
	if( m == n ) { puts("0") ; exit(0) ; }
	rep( i, 1, 19 ) Inv[i] = Inv[i - 1] / 2 ; 
	rep( i, 2, 19 ) Inv[i] = Inv[i] + Inv[i - 1] ;
	memset( dp, 63, sizeof(dp) ), dp[n][1] = a[n] ;  
	for( re int i = n - 1; i > m; -- i ) {
		for( re int j = 1; j <= 19; ++ j ) {
			dp[i][j] = min( dp[i + 1][j], dp[i + 1][j - 1] + a[i] ) ;
			if( Inv[j] < n - i + 1 ) dp[i][j] = inf ; 
		}
	} Ans = inf ; 
	rep( j, 1, 19 ) Ans = min( Ans, dp[m + 1][j] ) ;
	printf("%lld\n", Ans ) ;
	return 0 ;
}
```

---

## 作者：李承轩 (赞：0)

**思路：**

如果不干涉，第 $n$ 个会赢。

如果第 $n$ 个不是你朋友，就必须贿赂第 $n$ 个。

但在贿赂第 $n$ 个前，第 $n$ 个可以帮你干掉 $\log_2n-1$ 个人。

只要干掉编号比你大的就行了。

接着，就要贿赂当前没被干掉编号最大的，然后一直重复此过程。

但刚才干掉的 $\log_2n-1$ 个人，要使现在的编号最大的人代价最小。

用小根堆维护即可。

**做法：**

$i$ 从 $n$ 开始往前遍历。

把遍历到的数都加到堆里面。

对于当前 $i$，假如 $i$ 是 $2$ 的幂，说明这时候要买一个人打假球了。

从堆里取一个最小的出来，买他打假球。

答案就加上买他的花费。

直到们遍历到喜欢的国家。

**代码：**

```cpp
// Problem: Tournament
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1260E
// Time: 2023-12-15 15:52:44
// Author: Licheng(756336)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,a[N],pos,cnt,ans;
int lowbit(int x){return x&(-x);}
priority_queue<int,vector<int>,greater<int> > q;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),pos=(a[i]==-1?i:pos);
	for(int i=n;i>pos;i--)
	{
		q.push(a[i]);
		if(i==lowbit(i))
		{
			ans+=q.top();
			q.pop();
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：hellolin (赞：0)

# CF1260E Tournament 题解

如果不贿赂任何人，最强的人一定夺冠。所以除非朋友最强，否则我们需要打至少一次假赛。

最强的人可以帮忙干掉 $\frac{n}{2} - 1$ 个人。但如果朋友太菜了，还是有打不过的，就需要贿赂另一个人，这个人又可以干掉 $\frac{n}{4} - 1$ 个人，以此类推，直到比朋友强的只剩下我们贿赂的人。

我们从强到弱遍历选手，并存储目前为止每个人的贿赂价值，人手不足的时候我们找到最便宜的那个就行了。

``` cpp
static constexpr int N = (1 << 18) + 5;
int n, a[N];
multiset<int> st;
i64 ans;
void main() {
  io.read(n);
  for (int i = 1; i <= n; ++i)
    io.read(a[i]);
  for (int i = n; ~a[i]; --i) {
    st.insert(a[i]);
    if (popcount((unsigned) i) == 1) { // 2 的整数次幂
      ans += *st.begin();
      st.erase(st.begin());
    }
  }
  io.writeln(ans);
}
```

---

## 作者：MortisM (赞：0)

妙妙题，但是感觉评不到紫。

[题目链接](https://www.luogu.com.cn/problem/CF1260E)。

## 题意

luogu 题意。

> 有 $n$ 个人，贿赂第 $i$ 个人的代价为 $a_i$。这些人中，贿赂代价为 $-1$ 的是你的朋友。现在，你可以两两配对，使得编号小的被淘汰，但是，如果你贿赂了编号大的，那么编号大的被淘汰，而编号小的留下。问：使得你朋友夺得冠军的最小代价。

## 题解

如果你的朋友不是第 $n$ 个人，则必然要贿赂第 $n$ 个人。

此时若你的朋友编号 $\ge \frac{n}{2}$，则完成。否则需要取 $\frac{n}{2}\sim n-1$ 的最小贿赂代价。

容易发现规律，即每 $2^k$ 分一段，每一段取 $a_i$ 最小值，直到 $a_i=-1$ 停止。

时间复杂度 $O(n)$。

## 总结

巨大妙妙。但是手算一下应该不难看出。

## 代码

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) (int)x.size()
#define ll long long
#define pii pair<int,int>
using namespace std;
inline void chmin(int &x,int y){x=min(x,y);}
inline void chmax(int &x,int y){x=max(x,y);}
const int N=(1<<18)+5;
int n;
ll a[N];
priority_queue<ll,vector<ll>,greater<ll>> pq;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	ll ans=0;
	for(int i=n;i>=1;i--){
		if(a[i]==-1) break;
		pq.push(a[i]);
		if(__builtin_popcount(i)==1){
			ans+=pq.top();
			pq.pop();
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
Basic:
1. int or long long?
2. freopen?
3. memory limits?
Advanced:
1. use more functions
2. write carefully and check
3. think twice before writing
4. debug quickly
5. never copy others' codes
*/
```

---

