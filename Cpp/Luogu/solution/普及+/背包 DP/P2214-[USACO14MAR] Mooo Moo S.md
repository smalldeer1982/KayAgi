# [USACO14MAR] Mooo Moo S

## 题目背景

农夫约翰完全忘了他有多少头牛了！他不好意思到牧场里去数牛，因为他不想让牛意识到他的健忘。取而代之的是，他决定在奶牛聚集的牧场里安装麦克风，秘密计算出他能从中听到的所有牛叫声的总音量，以便以此确定奶牛的数量。

## 题目描述

FJ 的 $N(1\le N\le100)$ 个牧场都是沿着一条笔直的道路分布的。每一个牧场可能有许多种品种的奶牛；FJ 拥有 $B(1\le B\le20)$ 个不同品种的奶牛，而第 $i$ 种奶牛的叫声音量为 $V_i(1\le V_i\le100)$。此外，有一股强风沿着道路吹来，将牛的叫声从左往右传递，如果某个牧场的总音量是 $x$，那么它将传递 $x-1$ 的音量到右边的下一个牧场。这就意味着，一个牧场里的总音量是处在该牧场的奶牛所发出的音量加上左边前一个牧场的总音量 $-1$。数据保证，每一个牧场内由该牧场所有奶牛所发出的总音量最多为 $10^5$。

## 说明/提示

#### 输入说明：
FJ 拥有 $5$ 个牧场，每个牧场总音量从左到右分别为为 $0$、$17$、$16$、$20$、$19$。FJ 有两种不同品种的奶牛；第一种奶牛的叫声音量是 $5$，第二种奶牛的叫声音量是 $7$。
#### 输出说明：
$2$ 号牧场场有 $2$ 头 $1$ 号品种的奶牛，$1$ 头 $2$ 号品种奶牛；还有一头牛在 $4$ 号牧场，共 $4$ 头奶牛。

## 样例 #1

### 输入

```
5 2
5
7
0
17
16
20
19```

### 输出

```
4
```

# 题解

## 作者：Nuyoah_awa (赞：11)

### 题目大意

有 $B$ 种牛，每种牛的叫声为 $V_i$，每个农场听到的声音为 $x$，求 FarmerJohn 的农场里最少有几头奶牛。

### 题目分析

看到 $B$ 种奶牛，$n$ 个农场，就想到很像完全背包。所以这道题可以用 DP 做。

我们定义 $dp[i]$ 为 农场中有 $i$ 的声音，最少的奶牛数。

对于每种叫声为 $v[j]$ 的奶牛，声音为 $i$ 的农场的转移方程为：

$$dp[i] = \min(dp[i], dp[i-v[j]]+1)(i \in [1, N])$$

知道声音为 $i$ 的农场中最少的奶牛数后，我们就可以贪心求解了。

### code
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N = 1e5, INF = 1e9;
int f[N + 5], v[N + 5], n, b, u, now, ans;
int main()
{
	scanf("%d %d", &n, &b);
	for(int i = 0;i <= N;i++)
		f[i] = INF;
	f[0] = 0;
	for(int i = 1;i <= b;i++)
	{
		scanf("%d", &v[i]);
		for(int j = v[i];j <= N;j++)
			f[j] = min(f[j], f[j - v[i]] + 1);
	}
	for(int i = 1, x;i <= n;i++)
	{
		scanf("%d", &x);
		x -= now, now += x;
		now -= now ? 1 : 0;
		if(x < 0)
		{
			printf("-1");
			return 0;
		}
		if(f[x] == INF)
		{
			printf("-1");
			return 0;
		}
		ans += f[x];
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：_anll_ (赞：5)

做教练拉的题单居然还能看见可以发题解的题，这不得来写一波。
## 题目思路
先说大体：我们先将每个牧场的实际音量分离出来，然后再 dp 一下把每个音量对应的**最小**奶牛数求出来，最后将每个牧场的实际音量对应的奶牛数输出就好啦。

下面我详细讲讲每一步具体怎么操作。

### 分离音量
显然易见，对于第 $i$ 个牧场，它的实际音量应为第 $i-1$ 个牧场的总音量值减一。但如果上一个牧场的音量为 $0$ 就不能再减一了，所以得到公式：
$$
R_i=C_i-\max(0,C_{i-1}-1)
$$

但再考虑一种情况：$C_{i-1}=17$，$C_i=10$。显然，这是**不成立**的。因为音量只会在传播的过程中减一，不会突然锐减七。这种情况说明有负牛的存在，而显然是不被允许的。所以我们还需要特判一下这种情况。

### 状态转移

其实本蒟蒻一开始敲状态转移的时候没有看出来是完全背包，但听同学提出这个词之后也后知后觉的反应了过来。

考虑将每种音量作为背包，每种牛作为物品，因为牛可以无限取。因为求的是最小值，所以我们先初始化一个极大值，如果最后的值还是极大值，那就说明该音量不可达。状态转移方程如下：
$$
dp_j=\min(dp_j,dp_{j-cow_i}+dp_{cow_i})
$$

当然，因为本题的最高音量不大，我们完全可以先预处理完了再去进行 $O(1)$ 的回答。

## 代码展示
剩下的一些细节都在代码里了。马蜂自认为良好，凑合着看吧。
```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int n,m,ans,dp[1000005],cows[20005],c[10005],r[10005];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=1000000;i++) dp[i]=2147483647;
	for(int i=1;i<=m;i++){
		cin>>cows[i];
		dp[cows[i]]=1;
	}
	for(int i=1;i<=n;i++){
		cin>>c[i];
		if(c[i]<c[i-1]-1){//如果存在负牛 
			cout<<-1;
			return 0;
		}
		r[i]=c[i]-max((long long)0,c[i-1]-1);
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=100000;j++){
			if(j<=cows[i]) continue;//音量j比奶牛i对应的音量还要小就不能被更新 
			dp[j]=min(dp[j],dp[j-cows[i]]+dp[cows[i]]);
		}
	}
	for(int i=1;i<=n;i++){
		if(r[i]==0) continue;
		if(dp[r[i]]==2147483647){//音量不可达 
			cout<<-1;
			return 0;
		}
		ans+=dp[r[i]];
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：pearchen (赞：4)

## 题目分析

本题意思大概就是给出各种牛所发出音量的权值，求出最少可能的牛的数量。

***

## 题目思路

其实观察一下题面，最开始我个人的想法是用贪心，每次都尽量把每个牧场放尽量大的牛的音量的权值，那么进一步考虑，我们可以从动态规划入手，我们不难想到背包问题。

### 那么我们就不难有以下解法

***我们先预处理出每个牧场原本所有的音量的权值，然后找出最大的一个音量值对其跑一遍背包，然后这个时候你就得到了一个包含不同音量权值所可能包含最少牛数量的动态规划数组，然后最后统计个数即可。***

***

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+10;
const int INF=1e9;
int n,b;
int v[MAXN];
int f[MAXN];
int rf[MAXN];
int dp[MAXN];
int maxn=-1;
int ans=0;

int main()
{
    scanf("%d%d",&n,&b);
    for(int i=1;i<=b;++i)
    {
        scanf("%d",&v[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&f[i]);
    }
    rf[1]=f[1];
    for(int i=2;i<=n;++i)
    {
        if(f[i-1]==0)
        {
            rf[i]=f[i];
        }
        else
        {
            rf[i]=f[i]-f[i-1]+1;
            if(rf[i]<0)
            {
                puts("-1");
                return 0;
            }
        }
        maxn=max(maxn,rf[i]);
    }
    for(int i=1;i<=maxn+100;++i)
    {
        dp[i]=INF;
    }
    for(int i=1;i<=maxn;++i)
    {
        for(int j=1;j<=b;++j)
        {
            if(i-v[j]>=0)
            {
               dp[i]=min(dp[i],dp[i-v[j]]+1);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(dp[rf[i]]<INF)
        {
            ans+=dp[rf[i]];
        }
        else
        {
            puts("-1");
            return 0;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

***

## 写在最后

第一次写题解，还请各位大佬多关照。

MADE BY - pearchen



---

## 作者：kczw (赞：2)

# 题意简述
给定 $B$ 种数值和一个经过一定修改的长度为 $N$ 的数列。

问原本的、未被修改数列的每一个元素是否能由 $B$ 种数值组合得到。
# 思路
首先，根据题目可以知道如何还原长度为 $N$ 的数列。

其次，$N$ 数列的每个元素都小于 $10^5$，我们可以用完全背包出 $10^5$ 内每一个数值是否能够由 $B$ 种数值组合而成，以及它最多能够由多少个数值组成。

最后，判断 $N$ 数列和是否合法即可。

# 实现
```cpp
#include<iostream>
#define int long long
using namespace std;
int ans,n,b,m,so[1005],s[1005],k[205],dp[100005];
signed main(){s[0]=1;	 
	scanf("%lld%lld",&n,&b);
	for(int i=1;i<=b;i++)scanf("%lld",&k[i]);
	for(int i=1;i<=n;i++){
		scanf("%lld",&so[i]);
		if(so[i-1]!=0)s[i]=so[i]-so[i-1]+1;
		else s[i]=so[i];
		m=max(m,s[i]);
	}for(int i=1;i<=m;i++)dp[i]=1e9;dp[0]=0; 
	for(int i=1;i<=b;i++)
	for(int j=k[i];j<=m;j++)
		dp[j]=min(dp[j],dp[j-k[i]]+1);
	for(int i=1;i<=n;i++){
		if(s[i]<0)printf("-1"),exit(0);
        if(dp[s[i]]==(int)1e9)printf("-1"),exit(0);
		ans+=dp[s[i]];
	}printf("%lld",ans>=1e9?-1:ans); 
	return 0;
}
```

---

## 作者：Gumbo (赞：2)

本题做法：预处理完全背包并简单模拟。

首先，我们很容易得到每个农场单独的声音总量，而每个农场之间的牛个数是互不影响的，因此我们可以利用贪心的思想，每次将每个农场取最优方法，则最终总数必然最小。

然后是如何找最优。

我们类似完全背包，得到如下的转移：

如果这个状态可以由前面的一个状态加上这种牛一头来得到，并且答案更优，那么进行转移。

由于每种牛可以有无限只，我们类似完全背包，从前到后顺次转移即可。

下面是稍加优化的代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int f[110000];//DP数组，f[i]=j表示i的声音最少需要j头牛
vector<int>anss;
int main(){
    memset(f,0x3f,sizeof f);//初始化
    f[0]=0;
    int n,b;
    scanf("%d%d",&n,&b);
    int u;
    while(b--){//由于选的顺序不重要，我们可以直接边读入边依次加入DP的考虑
        scanf("%d",&u);
        for(int i=0;i<=100000;++i){
            f[i+u]=min(f[i+u],f[i]+1);//上面提到的转移
        }
    }
    int nw=0;
    int ans=0;
    while(n--){
        scanf("%d",&u);
        u-=nw;//将前面的影响减去
        nw+=u;//添加这次的影响
        if(nw)--nw;//如果声音还有，则衰减
        if(u<0){
            printf("-1");
            return 0;
        }//不可能出现负数，否则无解
        if(f[u]==0x3f3f3f3f){
            printf("-1");
            return 0;
        }//没办法正好匹配
        ans+=f[u];
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：__HHX__ (赞：1)

# 思路
根据题意我们可以得知每个农场实际发出 $X_i - \max(X_{i - 1} - 1, 0)$ 的声音。

这样每个农场所发出的声音就完全独立了。

因为一个农场可以拥有多头奶牛，对于每个农场所以我们可以做一个完全背包，方程如下：

$$dp_i = \min(dp_{i - v_j} + 1, dp_i)$$

因为每个农场所用的奶牛种类是一样的，所以我们可以做一个**预处理**，范围是 $0 \sim 10^5$。

我们就可以做到 $O(1)$ 的回答了。

最终时间复杂度 $O(10^5 \times B + N)$。

# 最终代码
```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

const int MaxN = 1e5 + 3;

int dp[MaxN] = {1}, v[MaxN], n, b, ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> b;
  fill(dp + 1, dp + MaxN - 1, MaxN + 1);
  for (int i = 1; i <= b; i++) {
    cin >> v[i];
  }
  for (int i = 1; i <= MaxN - 3; i++) {
    for (int j = 1; j <= b; j++) {
      if (i - v[j] >= 0) {
        dp[i] = min(dp[i - v[j]] + 1, dp[i]);
      }
    }
  }
  for (int i = 1, x, sum = 0; i <= n; i++) {
    cin >> x;
    if (x - sum < 0 || dp[x - sum] == MaxN + 1) {
      ans = -1;
      break;
    }
    ans += dp[x - sum] - 1, sum = max(x - 1, 0);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：1)

这道题是一道细节题，如果不算万恶的 hack 数据，就不难。


------------



## 1.分析

这道题是一道背包题，由于牛的量没有限定，所以是一道完全背包。

假如不了解背包，[背包九讲](https://oi-wiki.org/dp/knapsack/)。

定义 $dp_j$ 为 $j$ 的声音最少有几头牛。

那么核心代码就可以套用完全背包的模板，状态转移方程为 $dp_j=\min(dp_j,dp_{j-v_i}+w_i)$。


------------
## 2.初始化

注意一个点，为什么我不用 memset。如果用 memset，第三个 
hack 会过不去。我也不知道为什么，如果有知道的大佬请在评论区回复，感谢。

dp 数组初始附极大值。

由我们的状态定义得 $dp_0=0$。

------------

## 3.输入输出

由于作者不想改变完全背包模板，所以要加一个 $w_i=1$。

然后输入的时候如果牛叫声出现负数就输出 $-1$。

假如 $b_i$ 不可被表示，我们也输出 $-1$。

剩余按照题意模拟就行，具体看代码。



## 4.code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[1000010],v[10010],w[10010];//dp[j]表示j的音量最少有几头牛。 
int b[100010];
int sum;
int d[100010];
signed main(){
	int m,B;//可能各位读者看的不是很舒服，B是原题中的N，m是原题中的B 
	cin>>B>>m;
	for(int i=1;i<=1000010;i++)
		dp[i]=1e9;//初始化1 
	for(int i=1;i<=m;i++){
		cin>>v[i];
		w[i]=1;//这里也可以不加，下面方程改为dp[j]=min(dp[j],dp[j-v[i]]+1)
	}
	int now=0;
	for(int i=1;i<=B;i++){
		cin>>d[i];
		d[i]-=now;//减去上一个带来的影响 
		now+=d[i];//加上这一个的影响 
		if(now!=0)
			now--;
		if(d[i]<0){//特判，不然数组越界 
			cout<<"-1";
			return 0;
		}
	}
	dp[0]=0;//初始化2，dp边界 
	for(int i=1;i<=m;i++)
		for(int j=v[i];j<=1e5;j++)
			dp[j]=min(dp[j],dp[j-v[i]]+w[i]);//完全背包状态转移方程 
	int sum=0;
	for(int i=1;i<=B;i++){
		if(dp[d[i]]==1e9){//不可被表示 
			cout<<"-1";
			return 0;
		}
		sum+=dp[d[i]];//累加 
	}
	cout<<sum;
	return 0;
}
```

这篇题解就到此结束啦。

---

## 作者：i_love_tym (赞：1)

由于每个农场可以有多头相同品种的奶牛，所以考虑完全背包，设 $f_i$ 为音量 $i$ 时最少有几头奶牛。则

$$
	 f_i=\min(f_i-v_i+1,f_i)
$$

其中 $v_i$ 表示第 $i$ 种奶牛的音量~~其实就是题目的意思~~。

然后由于按照上面的方程转移可能会出现 $f_i-v_i < 0$ 的情况，所以可以将方程变成:

$$
f_{i+v_i}=\min(f_{i+v_i},f_i+1)
$$

又由于其实每次转移我们只需要用到 $v_i$，所以我们连数组都不用开，直接用一个变量$x$存储每次输入的 $v_i$。

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[10000005];
signed main(){	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	int n,b,x,ans=0,y=0;
	cin>>n>>b;
	for(int i=1;i<=b;i++) {
		cin>>x;
        for(int j=0;j<=100000;++j) f[j+x]=min(f[j+x],f[j]+1);
	}
	for(int i=1;i<=n;i++){
		cin>>x;
		x-=y;
		y+=x;
		if(y) y--;
		if(f[x]==0x3f3f3f3f||x<0){cout<<-1;return 0;}
		ans+=f[x];
	}
	cout<<ans;
}
```

---

## 作者：ztntonny (赞：1)

关于完全背包前面的大佬已经讲得比较清楚了，我主要说一下这题的坑。

1. 关于无方案的情况，当有些农场的总音量 $<0$ 时无方案，需要注意，这里还可能因为没有注意到出现越界 RE。
2. 关于更新时的注意事项，要保证更新对象的可取性，即已经出现过。

后面的表准完全背包，一维即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n , b , cow[25] , farm[105] , fa[105] , f[100005] , ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL) , cout.tie(NULL);
	cin >> n >> b;
	for ( int i = 1; i <= b; i++ )	cin >> cow[i];
	for ( int i = 1; i <= n; i++ )	cin >> fa[i] , farm[i] = fa[i] - max( fa[i - 1] - 1 , 0ll );
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j < 100005; j++ )	f[j] = 1e18;
		for ( int j = 0; j <= farm[i]; j++ )
			for ( int k = 1; k <= b; k++ )
				if ( j - cow[k] >= 0 && f[j - cow[k]] < 1e18 )
					f[j] = min( f[j] , f[j - cow[k]] + 1 );
		if ( farm[i] < 0 || farm[i] >= 0 && f[farm[i]] == 1e18 )
		{
			cout << -1 << endl;
			return 0;
		}
		ans += f[farm[i]];
	}
	cout << ans << endl;
	return 0;
}
```


---

