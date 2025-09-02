# Chain Reaction

## 题目描述

There are $ n $ beacons located at distinct positions on a number line. The $ i $ -th beacon has position $ a_{i} $ and power level $ b_{i} $ . When the $ i $ -th beacon is activated, it destroys all beacons to its left (direction of decreasing coordinates) within distance $ b_{i} $ inclusive. The beacon itself is not destroyed however. Saitama will activate the beacons one at a time from right to left. If a beacon is destroyed, it cannot be activated.

Saitama wants Genos to add a beacon strictly to the right of all the existing beacons, with any position and any power level, such that the least possible number of beacons are destroyed. Note that Genos's placement of the beacon means it will be the first beacon activated. Help Genos by finding the minimum number of beacons that could be destroyed.

## 说明/提示

For the first sample case, the minimum number of beacons destroyed is $ 1 $ . One way to achieve this is to place a beacon at position $ 9 $ with power level $ 2 $ .

For the second sample case, the minimum number of beacons destroyed is $ 3 $ . One way to achieve this is to place a beacon at position $ 1337 $ with power level $ 42 $ .

## 样例 #1

### 输入

```
4
1 9
3 1
6 1
7 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
1 1
2 1
3 1
4 1
5 1
6 1
7 1
```

### 输出

```
3
```

# 题解

## 作者：子翮 (赞：12)

[「请在个人博客中查看」](https://zihe.blog.luogu.org/solution-cf607aa)

### 前言


这是一道 Codeforces Round #336 Div.1 的题，只要想到了dp，总体难度不算太高。

### 具体实现

我们设 $dp[i]$ 表示从 $i$ 位置从右到左依次激活激光塔，能够**最多保留**多少个激光塔。这样一来，转移方程就很好推出来：

$$ dp[i]=\left\{
\begin{aligned}
dp[i-1] &   &  \ i \text{位置没有激光塔}  \\
1 & & \ i \text{位置有激光塔 且}\ b[i] \geq i \\
dp[i-b[i]-1]+1 &  &i \text{位置有激光塔 且}\ b[i] < i
\end{aligned}
\right.
$$

由于题目中说明我们可以在最右侧建一个威力任意的激光塔，其实就等价于可以将从右侧开始任意多个激光塔毁掉。记最右侧激光塔位置为 $len$ ，所以答案就是

$$Ans=n- \max \limits_{1 \leq i \leq len}dp[i] $$

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>
#define R register
#define MAXN 1000100
using namespace std;
struct node
{
	int a,b;
	bool operator < (const node &tp) const
	{
		return a<tp.a;
	} 
}w[MAXN];
int n,len,ans;
int dp[MAXN];
map<int,bool> mp;//记录i位置是否是激光塔
map<int,int> power;//记录i位置激光塔威力
int main()
{
	scanf("%d",&n);
	for(R int i=1;i<=n;i++)
		scanf("%d%d",&w[i].a,&w[i].b);
	sort(w+1,w+1+n);//貌似数据不用排序...
	for(R int i=1;i<=n;i++)
	{
		mp[w[i].a]=true;
		power[w[i].a]=w[i].b;
		len=max(len,w[i].a);
	}
	if(mp[0]) dp[0]=1;
	for(R int i=0;i<=len;i++)
	{
		if(mp[i]) 
		{
			int p=power[i];
			if(p>=i) dp[i]=1;
			else dp[i]=dp[i-p-1]+1;
		}
		else dp[i]=dp[i-1];
		ans=max(ans,dp[i]);
	}
	printf("%d\n",n-ans); 
	return 0;
}


```

**update:** 2020/03/27，emmm由于窝太弱了不知道你谷主站  $\LaTeX$ 和个人博客里的不太一样的 feature ,所以如果 $\LaTeX$ 挂了的话请到个人博客里看。

---

## 作者：ListenSnow (赞：4)

## 题意

给定 $n$ 个激光塔，每个激光塔有一个坐标 $a_i$ 和一个威力 $b_i$，当第 $i$ 个激光塔被激活后，坐标 $\geq a_i-b_i$ 的激光塔将被摧毁。现在在所有激光塔的右侧放置一个坐标和威力任意的激光塔，从右到左依次激活没有被摧毁的激光塔，求最少要摧毁多少个激光塔。

## 思路

首先注意，虽然样例中的 $a_i$ 都是升序给出的，但是题目中并未保证 $a_i$ 升序，所以在最开始要进行**排序**。

定义 $f[i]$ 表示以第 $i$ 个激光塔为起点，依次向右激活没被摧毁的激光塔，摧毁的激光塔数量。注意这里**不能**定义为最小值，因为本题中的起点一旦确定，那么摧毁的数量也就确定了。

注意到题目中给出的最右侧的激光塔的威力任意，其实就可以转化为摧毁第 $i+1$ 个到第 $n$ 个激光塔后，再以第 $i$ 个激光塔为起点向右激活。那么最终的答案就是 $\min(f[i]+n-i)$。

接下来考虑状态转移方程。注意到，第 $i$ 个激光塔被激活后，下一个被激活的肯定是第一个坐标**小于** $a_i-b_i$ 的激光塔，同时因为坐标是单调递增的，就可以用**二分**来查找这个激光塔 $j$。那么状态转移方程就是 $f[i]=f[j]+i-j-1$。因为在 $j$ 和 $i$ 之间的激光塔显然被摧毁了。

## code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
const int INF=0x3f3f3f3f;
struct NLC{
	int a,b;
    bool operator <(const NLC &t)const{
	    return a<t.a;
	}
}p[N];
int ans=INF,n,f[N];
int find(int x)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=l+r+1>>1;
		if(p[mid].a<x) l=mid;
		else r=mid-1;
	}
	return p[l].a<x?l:0;
}
int min(int a,int b){return a<b?a:b;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].a,&p[i].b);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
	{
		int j=find(p[i].a-p[i].b);
		f[i]=f[j]+i-j-1;
		ans=min(ans,f[i]+n-i);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Zxsoul (赞：4)

**前言**

感觉又学到了一种DP的思想，无限扩充

**思路**

仔细读题可以知道，我们只需要知道从哪个发射站开始，往左能保留发射塔的最大数目即可，

这么一想DP蛮好推的为：
$$
f[i]=max\{f[k]+1\}\left(k\in[a[i]-a[k]+1>b[i]]\right)
$$
结果WA掉了

发现这压根不存在DP转移式，可以选择的对象太少了，我突然想起了[这个题](https://zxshetzy.blog.luogu.org/yi-ge-hao-ti)

我们不如只把发射塔只当做是一个序列中的几个驿站，然后我们转移的时候就不需要考虑我的前状态是否存在或者是否可表示，因此我们可以这样转移：

当 `b[i]<i` 时
$$
	f[i]=f[i-b[i]-1]+1
$$
这里说明一下为什么要 `-1` ，因为题目要求

（$\texttt{该激光塔距离小于等于bi的激光塔都会被摧毁} $）

`i-b[i]` 仅仅只是到了等于`b[i]` 的位置，但并不符合要求所以`-1`

**其他转移**就轻而易举了：

当 `b[i]=0` 时
$$
f[i]=f[i-1]
$$
当 `b[i]>=i` 时
$$
	f[i]=1
$$

**后言**
其实并不需要 `vector` 去打标记（~~给第一篇题解说的~~）

**代码**
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e7+10;
const int B = 1e6+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int vis[B],len,a[B],b[B],f[B],n;
int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		a[i]=read(),b[a[i]]=read();
		vis[a[i]]=1;
		len=max(a[i],len);
	}
	if (vis[0]) f[0]=1;
	int num=0;
	for (int i=0;i<=len;i++)
	{
		if (!b[i]) f[i]=f[i-1];
		else if (b[i]<i) f[i]=f[i-b[i]-1]+1;
		else f[i]=1;
		num=max(num,f[i]);
	}
	printf("%d\n",n-num);
}
```

---

## 作者：ZTSSSS (赞：4)

先从左往右挨个处理光棱塔，f[i]存的是第i个塔摧毁的塔数。\
设x是i塔所能攻击到的最远塔编号，我们这里用二分查找得到x\
则转移方程为f[i]=f[x-1]+i-x \
最后在枚举一下右起点就能得到最终结果了\
\
代码如下:
```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+100;
const int INF=1e7+100;
struct Node{
	int a,b;
	Node(){}
	Node(int a,int b):a(a),b(b){}
	bool operator<(const Node &x)const{
		return a<x.a;
	}
}node[maxn];
int f[maxn];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&node[i].a,&node[i].b);
	sort(node+1,node+1+n);
	f[1]=f[0]=0;
	for(int i=2;i<=n;i++){
		int d=node[i].a-node[i].b;//摧毁起点位置
		int x=lower_bound(node+1,node+1+n,Node(d,0))-node;//二分查找摧毁位置
		f[i]=f[x-1]+i-x;//更新摧毁数量
	}
	int ans=INF;
	for(int i=n;i;i--)
		ans=min(ans,f[i]+n-i);//计算最小摧毁数
	printf("%d",ans);
    return 0;
}

---

## 作者：strange757 (赞：2)

感觉我的做法不是很像dp。但是思路简洁易懂

对于题中给出的 $n$ 个激光塔,先按照位置排序，对于每一个激光塔 $i$ , 处理出它第一个不能摧毁的激光塔 $j$ ，用 $f$ 数组存储, 转移方程式为
$f[i] = f[j] + 1 $,然后考虑在最右侧增加的一座塔， 对于这座塔，他的作用就相当于清除掉从右往左的一些塔，有了这座塔，整个数列的右端点就可以是任意一个点。所以答案为总塔数减去每一个点往左保留的最多的塔取最小值就是答案,即  $ans = \min(n -f[i], ans)$ 。

时间复杂度为 $O(nlongn) $。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
struct node{
	int a, b;
}x[N];
int ans = 1e9, num[N], now = 1;
int f[N], n, a[N], b[N];
bool cmp(node x, node y){
	return x.a < y.a;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &x[i].a, &x[i].b);
		
	}
	sort(x + 1, x + 1 + n, cmp);
	for(int i = 1; i <= n; i++) a[i] = x[i].a, b[i] = x[i].b;
	for(int i = 1; i <= n; i++){
		if(i > 1)num[i] = lower_bound(a + 1, a + i + 1, a[i] - b[i]) - a;
		if(i > 1)num[i] -= 1; 
		f[i] = f[num[i]] + 1;
		ans = min(n - f[i], ans);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：EDqwq (赞：2)

~~只有我这么暴力的做吗~~

我们观察一下，发现在最后加上一个毁灭装置，能做到的事情就是毁灭原来的装置序列的后缀的装置。

也就是说，我们毁灭了之后会从前面的一个装置继续操作。

那么， dp 状态来了： $dp_i$ 表示从第 i 个装置从右向左操作最少毁灭掉的装置个数。

显然，我们需要分两类讨论：

首先，如果当前的装置无法毁灭任何前面的装置，就不需要管它，直接设为 $dp_{i-1}$ 。（显然可以传递）

如果可以毁灭，那么求出是最多毁灭到哪一个，设那个位置为 $pos$ 。

$$dp_i = dp_{pos-1} + (i - pos)$$

初始状态 $dp_1 = 0$ ，装置需要按照位置排序。

然后，我们还需要求答案，显然求的时候需要加上我们在最后一个毁灭装置毁灭的装置个数，这道题就做完了。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))
#define frein freopen("in.in","r",stdin)
#define freout freopen("out.out","w",stdout)

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int x;
	int y;
}e[1000010];

int n;
int a[1000010];
int dp[1000010];
int ans = 2147483647;

bool cmp(node x,node y){
	return x.x < y.x;
}

signed main(){
	cin>>n;
	for(int i = 1;i <= n;i ++)e[i].x = read(),e[i].y = read();
	sort(e + 1,e + n + 1,cmp);
	for(int i = 1;i <= n;i ++)a[i] = e[i].x;
	dp[1] = 0;
	for(int i = 2;i <= n;i ++){
		int num = e[i].x - e[i].y;
		if(e[i - 1].x < num)dp[i] = dp[i - 1];
		else {
			int pos = lower_bound(a + 1,a + n + 1,num) - a;
			dp[i] = dp[pos - 1] + (i - pos);
		}
	}
	for(int i = 1;i <= n;i ++)ans = min(ans,n - i + dp[i]);
	ans = min(ans,n);
	cout<<ans;
}
```

---

## 作者：LincW (赞：1)

## 题意

有 $n$ 个激光塔排成一行，第 $i$ 个激光塔的位置为 $a_i$ ，威力是 $b_i$ 

当第 $i$ 个激光塔被激活后，对于任意其他激光塔 $j$ ，如果 $0 < a_i-a_j \le b_i$ ，则激光塔 $j$ 被摧毁。

添加一个新激光塔 $k$ ，使 $a_k > \text{max}\{a_1,a_2, ... ,a_n\}$ 

管理员现在开始开始从右到左依次激活每个激光塔，如果一个激光塔被摧毁了，那就不激活。

请调整 $a_k$ 和 $b_k$ ，使被摧毁的激光塔总数最少。

## 分析

因为题目没有保证 $a_i$ 输入时的顺序，所以先 `sort(beacons+1,beacons+n+1,cmp);` 

这样第 $i$ 个激光塔就是从左向右数第 $i$ 个了。

简单分析一下题目：在最右侧放置的这个激光塔的威力（ $b_k$ ）决定了最开始开始会摧毁几个激光塔，也就是（去掉这个激光塔之后）从第几个激光塔开始激活。

所以说我们的任务就是求出：对任意一个激光塔，从它开始激活会摧毁几个激光塔（下文称为 $dp[i]$ ）

求完 $dp$ 数组之后，答案就是 $dp[i]+(n-i)$ 的最小值了（ $n-i$ 代表 $i$ 右侧的被摧毁了的激光塔）

对于任意激光塔 $i$ ，$dp[i]$ 就是这次激活摧毁的激光塔数加上 $dp[j]$ ，其中 $j$ 是最右侧的没被摧毁的（除了 $i$ 之外的）激光塔。

```cpp
beacon find;
find.pos=max(0,beacons[i].pos-beacons[i].power);

int destroy=lower_bound(beacons+1,beacons+n+1,find,cmp)-beacons; //用 lower_bound 查找 j

dp[i]=dp[destroy-1];
dp[i]+=(i-destroy); //摧毁的激光塔数
```

**注意：这里有可能找不到 $j$ （这次激活把所有激光塔都摧毁了）**，我的处理方式是将 $dp[0]$ 置为 $1$ （找不到的话 lower_bound 会返回数组地址）

显然 $j<i$ ，因为 $i$ 右侧的激光塔都已经被激光塔 $k$ 摧毁了，而 $j \neq i$ 

所以只需要先将 $dp[1]$ 初始化为 $0$ ，一个 `for(int i=2;i<=n;++i)` 就可以求出 $dp$ 数组

有了 $dp$ 数组，答案就出来了（前面说了）

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=100000;

struct beacon
{
	int pos;
	int power;
};

int n,ans=2147483647,dp[N+5];
beacon beacons[N+5];

inline bool cmp(beacon a,beacon b)
{
	return a.pos<b.pos;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>beacons[i].pos>>beacons[i].power;
	}
	
	sort(beacons+1,beacons+n+1,cmp);
	
	dp[0]=0;
	dp[1]=0;
	
	for(int i=2;i<=n;++i)
	{
		beacon find;
		find.pos=max(0,beacons[i].pos-beacons[i].power);
		
		int destroy=lower_bound(beacons+1,beacons+n+1,find,cmp)-beacons;
		
		dp[i]=dp[destroy-1];
		dp[i]+=(i-destroy);
	}
	
	for(int i=1;i<=n;++i)
	{
		int destruction=dp[i]+n-i;
		if(destruction<ans) ans=destruction;
	}
	cout<<ans<<endl;
	
	return 0;
}
```



---

## 作者：ttq012 (赞：0)

$\color{blue}\mathscr{Difficutly: *1600}$

## $\mathscr{DESCRIPTION}$

太长了，略。

## $\mathscr{SOLUTION}$

这是一道简单的动态规划。

设 $f_i$ 为激活 $1\sim i$ 的激光塔后最多保留的激光塔的数量。

于是有：

+ 如果 $i$ 位置没有激光塔，那么 $f_i=f_{i-1}$。
+ 如果 $i$ 位置的激光塔可以辐射到上一个激光塔，那么 $f_i = 1$。
+ 否则，一定辐射不到，$f_i = f_{i - a[i] - 1} + 1$。

时间复杂度 $\mathcal O(n)$。

## $\mathscr{CODE}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int a[N], b[N], p[N], s[N], cnt[N], h[N], f[N];
signed main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i] >> b[i], cnt[a[i] + 1]++, p[a[i] + 1] = b[i];
  for (int i = 1; i <= 1e6 + 1; i++)
    s[i] = s[i - 1] + cnt[i];
  if (cnt[1])
    f[1] = 1;
  for (int i = 2; i <= 1e6 + 1; i++)
  {
    if (!cnt[i]) f[i] = f[i - 1];
    else if (p[i] < i) f[i] = f[i - p[i] - 1] + 1;
    else f[i] = 1;
  }
  // for (int i = 1; i <= 10; i++)
  //   cout << f[i] << ' ';
  // cout << '\n';
  cout << n - *max_element(f + 1, f + 1000002) << '\n';
  return 0;
}
```

## $\mathscr{AC\ RECORD}$

[$\mathscr{LINK}$](https://www.luogu.com.cn/record/105586311)

---

## 作者：Kreedy_Ke (赞：0)

## [题目翻译](https://www.luogu.com.cn/paste/u1ku4ioc)

凭感觉来讲，这题应该是 DP，事实上也确实如此。但看了看数据范围，发现是 $10^{6}$ 甚至 $10^{5}$ 的级别，我们需要想出一种近似 $O(n)$ 的算法才行。

可以从两个角度入手：一个基于所有的信标（$10^{5}$），一个基于所有位置（$10^{6}$），这里我选择前者。

既然是 $O(n)$ 算法，那么 DP 数组也应该是一维的。所以设 $dp_{i}$ 为以第 $i$ 个信标为最右端时所摧毁的信标总数。题目中是从右至左激活信标，那么如果也从右至左进行状态转移，就会发现左边的状态很难获得，所以为了方便，我们应当从左往右做状态转移。

首先明确初始情况：当只有一个信标或者根本没有信标时，不会有信标被摧毁，所以 $dp_{0}=dp_{1}=0$。

然后看看如何状态转移：对于第 $i$ 个信标，设其向左共能摧毁 $x$ 个信标，那么就有 $dp_{i}=dp_{i-x-1}+x$。
摧毁了 $x$ 个信标，那么左侧剩下的最右端就应该是第 $i-x-1$ 个信标，所以将第 $i-x-1$ 个信标做最右端的摧毁总数加上新摧毁的 $x$ 个，就得到了第 $i$ 个的数据。

每一个信标的 $x$ 怎么得到？提前预处理一边求出即可。为了快速处理，我使用了二分来辅助。

最后别忘了还有个东西：需要在最右端加上一个信标。题目并没有限定其位置与威力，所以其作用实际上就是摧毁最右端开始的连续若干个信标。那么在最后记录答案时，只需要求得 $\min\limits_{i=1}^{n}{(dp_i+n-i)}$ 即可。
将每个信标都作为一次最右端，右边其它的信标都视作被新信标摧毁，两者的和取最小值就是答案了。

以下为代码：

```
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=1e5+9;
struct node //设置一个结构体是为了方便排序
{
    int a,b;
    friend bool operator < ( node u , node v )
    { return u.a<v.a; }
}d[N];
int n,a[N],b[N],x[N],dp[N];
int main()
{
    scanf("%d",&n);
    for ( int i=1 ; i<=n ; i++ )
        scanf("%d %d",&d[i].a,&d[i].b);
    sort(d+1,d+1+n); //别忘了排序，别被样例骗了
    for ( int i=1 ; i<=n ; i++ )
    {
        a[i]=d[i].a,b[i]=d[i].b; //把a，b的值换回来
        x[i]=i-(lower_bound(a+1,a+1+i,a[i]-b[i])-a); //求得x的值
        dp[i]=dp[i-x[i]-1]+x[i]; //与之后的值无关，所以一并写了
    }
    int Min=999999999;
    for ( int i=1 ; i<=n ; i++ )
        Min=min(Min,dp[i]+n-i); //求得最小值
    printf("%d\n",Min);
    return 0;
}
```

至于基于位置的写法其它题解有，这里就不介绍了。

---

## 作者：出言不逊王子 (赞：0)

观察到“最后一个塔是最右边的”这个性质，我们可以得知：这个塔可以烧掉右边的任何塔。

所以我们可以发现：我们可以从**任何一个塔**开始，从右往左开始燃烧。

因为操作是固定的从右往左烧，所以考虑 DP .

- 以下是**错误算法**，如果愿意可以直接跳过。

我的第一反应是设 `f[i]` 为从 $i$ 开始**从右往左**烧，最多能**烧毁**多少个塔。

那么我们可以通过三个方法来考虑：

- 如果这个位置本来就没有塔，那么它一个都不能烧毁， `f[i]=0` .
- 如果这个位置的塔可以烧穿，也就是 `b[i]>=i` 那么答案就是**除了这个塔的其他塔** 。注意：右边已经**没有**塔了。
- 如果这个位置的塔烧不穿，也就是 `b[i]<i` ，那么答案就是**这个塔从左烧**能碰到的**最左边**的点再**扣掉他自己**。

那么我们可以写出代码：[错误代码](https://www.luogu.com.cn/paste/b0nciz5k)

不难发现，第一个样例就错了。

为什么呢？观察程序，我们可以发现程序写的很对。

那题目中的烧掉 $1$ 个是在哪里烧呢？

答案是开最右边的塔，烧掉第 $7$ 个。

那这个怎么解决呢？可以把 `ans` 的最小值设成 $1$ 。

现在看样例 $2$ 。

我们发现答案匪夷所思，居然是 $1$ 。

这是为什么呢？

烧了位于 $7$ 的塔后位于 $5$ 的塔还会被工作人员继续烧，所以答案还要算上 $5$ 能造成的，以此类推，烧了位于 $5$ 的塔后位于 $3$ 的塔还会被继续烧……

所以对于 `f[i]` ，我们还需要把所有 **不会** 被位于 $i$ 的塔烧毁的塔所造成的伤害算上去，时间复杂度会变的很高。

所以这个算法是错误的。

- 错误算法结束。

---

正难则反。

我们设 `g[i]` 为从 $i$ 开始开始**从右往左**烧，最多能**保住**多少个塔。

参见 `f[i]` 的推导方式，我们可以发现：

- 这个位置没有塔的话，答案是 $0$ 。
- 这个位置的塔可以烧穿的话，也就是 `b[i]>=i` 那么答案就是**自身** ，也就是 $1$ 。
- 如果这个位置的塔烧不穿，也就是 `b[i]<i` ，那么答案就是**这个塔从左烧**能碰到的**最左边**的点能烧掉的塔的个数（现在烧不掉了），再加上**他自己**，也就是 `g[i-b[i]-1]+1` 。

那于是有个小问题：如果 **这个塔从左烧**能碰到的**最左边**的点 是平地，那该怎么办？

那么距这个点**最近**且在这个点**左边**的塔也会烧，留下那个塔能保留的东西。接下来的内容可以递归求解。

也就是说，对于每一块平地，我们可以让它的答案等于 距这个点**最近**且在这个点**左边**的塔 的答案。具体实现起来，可以用 `g[i]=g[i-1]` 表示。

最终答案就是 $n-\max g_i$。

[这里](https://www.luogu.com.cn/paste/dsva4lfq)是最终代码。

---

## 作者：atarashiTLE (赞：0)

#### 难度
Codeforces Div2.B~Div1.A难度,个人觉得评级为绿（普及/提高-）。

### 思路
由题目可以看出我们创建的一个塔就可以摧毁最右侧任意 $t(0 \le t\le n)$ 个塔，所以我们设 $f_i$ 为从 $i$ 位置从右到左依次激活塔，最多保留塔的数量，则可以由此得到状态转移方程（设在 $i$ 点上的塔的攻击范围为 $a_i$，离左侧端点的距离为 $b_i$）：
$$ f_x=\left\{
\begin{aligned}
f_{x-1}\ \ \ &(x\text{位置上没有塔}) \\
1\ \ \ &(a_x\le b_x)\\
f_{x-b_i-1}\ \ \ &(a_x\ge b_x)
\end{aligned}
\right.
$$
所以答案显然为 $\displaystyle\min_{1\le i \le n} n-f_{b_i}$。

code:
```cpp
#include <iostream>
#include <cstdio>
#define re register
using namespace std;
inline int read()//快读
{
	re int t = 0;
	re char ch = getchar();
	while (!('0' <= ch && ch <= '9'))
	{
		if (ch == '-')
			t = -t;
		ch = getchar();
	}
	while (('0' <= ch && ch <= '9'))
	{
		t = ((t << 1) + (t << 3)) + ch - '0';
		ch = getchar();
	}
	return t;
}
int n, dp[100010], a[10000010], N, arr[10010];
signed main()
{
	cin >> n;
	for (re int i = 0; i < n; i++)//读入，稍微压行
		arr[i] = read(), a[arr[i]] = read(), N = max(arr[i], N);
	dp[0] = !!a[0];
	for (re int i = 1; i <= N; i++)//dp
		if (a[i] && a[i] >= i)
			dp[i] = 1;
		else if (!a[i])
			dp[i] = dp[i - 1];
		else
			dp[i] = dp[i - a[i] - 1] + 1;
	re int ans = 1919810;//一个极大（？）值
	for (re int i = 1; i < n; i++)//计算答案
		ans = min(ans, n - dp[arr[i]]);
	cout << (ans == 1919810 ? 0 : ans) << endl;//输出（注意当ans为初始值时输出0）
	return 0;
}
```

---

