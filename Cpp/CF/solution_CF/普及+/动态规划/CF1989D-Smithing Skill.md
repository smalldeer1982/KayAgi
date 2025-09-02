# Smithing Skill

## 题目描述

你在玩一款可以运行的著名电脑游戏，游戏中，你有许多能升级的技能。今天，你着重于铸造这个技能。你的策略是显然的：用材料锻造武器，并将其熔毁以返还部分材料。具体地，每次锻造和熔毁都可以提供 $1$ 点经验值。

有 $n$ 种可供锻造的武器，$m$ 种材料。

若要锻造第 $i$ 种武器，需耗费 $a_i$ 个 **同种** 材料，熔毁这把武器则返还 $b_i$ 个 **制作所用的** 材料。

初始你每种材料有 $c_i$ 个，你可以无限次的锻造和熔毁，每把武器均可以用任一种材料。

求你能获得的最大经验值。

## 样例 #1

### 输入

```
5 3
9 6 7 5 5
8 4 5 1 2
10 4 7```

### 输出

```
12```

## 样例 #2

### 输入

```
3 4
10 20 20
0 0 0
9 10 19 20```

### 输出

```
8```

## 样例 #3

### 输入

```
1 5
3
1
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
4999999990```

# 题解

## 作者：w9095 (赞：20)

[CF1989D Smithing Skill](https://www.luogu.com.cn/problem/CF1989D)

这篇题解是我在赛场上的真实思路，所以可能会比较冗长。但是相较于其他题解，读者可以在这篇题解中理解为什么会想到使用动态规划。我认为，授人以鱼不如授人以渔，理解为什么想到使用动态规划，比知道使用动态规划更重要。

首先，有一个比较显然的贪心。每次合成之后立即融掉，可以获得 $2$ 点技能点，并失去材料 $a_i-b_i$ 个。因此，我们把所有合成方式按照 $a_i-b_i$ 升序排序，先合成消耗少的合成方式，再合成消耗多的合成方式。

考虑到需要 $a_i$ 个材料才能合成，若 $a_i-b_i$ 相等，我们采用 $a_i$ 较小的合成方式，这样就可以合成更多次。不难发现如果一种合成方式 $a_i-b_i$ 大于等于其他合成方式，并且 $a_i$ 大于等于其他合成方式，这种合成方式一定不优，可以舍去。于是，现在的合成方式序列满足若 $i\lt j$，则 $a_i-b_i\lt a_j-b_j$ 且 $a_i\gt a_j$。对于某种数量 $c$，最优的合成方式显然是满足 $a_i\le c$ 的编号最小的位置。

每种材料互相独立，分别处理。首先考虑如何使用最优的一种合成方式进行合成。我们先留下 $a_i$ 个材料，并对于剩下的材料进行合成，每次消耗 $a_i-b_i$ 个，利用除法直接算出。这样就保证了至少有 $a_i$ 个材料，一定可以合成。之后，我们求出合成后的余数，加到留下的 $a_i$ 个中，然后暴力计算。显然，这个计算的次数不会太多，大概 $0\sim1$ 次，可以看作常数。

根据数据范围，使用最优的一种合成方式进行合成后，剩余的材料数量不会超过 $10^6$，考虑预处理。设 $f[i]$ 表示剩余 $i$ 个材料可以合成并融化的最多次数，我们发现，无论对于哪一个 $i$，进行一部分操作之后，$i$ 只会变小而不会变大。也就是说，如果从小到大枚举 $i$，$f[i]$ 的求解仅依赖于之前的状态，可以动态规划。

从小到大枚举 $i$，我们发现，经过第一步的处理后，可以使用的最优的一种合成方式也在从编号大到编号小单调递减，可以直接维护。使用最优的一种合成方式进行合成，就可以直接将剩余的材料数量可以合成并融化的最多次数通过状态累加过来。于是，我们就在线性时间内预处理出了 $f[i]$。

最后，思维变得很明朗。如果 $c\le10^6$，直接查表得到 $f[c]$。否则，使用最优的一种合成方式进行合成后，再查表累加进答案。

使用桶排序，时间复杂度为 $O(n)$，非常优秀。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m,c,a[1500000],b[1500000],s[1500000],q[1500000],p[1500000],f[1500000],cnt=0,now=0,ans=0;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	for(int i=0;i<=1000000;i++)s[i]=1e9;
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)s[a[i]-b[i]]=min(s[a[i]-b[i]],a[i]);
	cnt=0,q[cnt]=1e9,p[cnt]=0;
	for(int i=1;i<=1000000;i++)
	   	if(s[i]<q[cnt])q[++cnt]=s[i],p[cnt]=i;
	now=cnt;
	for(int i=1;i<=1000000;i++)
	    {
	    	while(q[now]<=i&&now>0)now--;
	    	if(now<cnt)now++;
	    	else continue;
	    	c=i,f[i]+=(c-q[now])/p[now];
		   	c=(c-q[now])%p[now]+q[now];
		   	while(c>=q[now])c-=p[now],f[i]++;
		   	f[i]+=f[c];
		}
	for(int i=1;i<=m;i++)
	   	{
		c=read();
		if(c<q[1])
		   {
		   ans+=f[c];
		   continue;
	       }
		ans+=(c-q[1])/p[1];
		c=(c-q[1])%p[1]+q[1];
		while(c>=q[1])c-=p[1],ans++;
		ans+=f[c];
		}
	printf("%lld\n",ans*2);
	return 0;
} 
```

---

## 作者：Watersphere (赞：10)

## 题意

给你 $n$ 个武器的方案，制造一把 $i$ 种武器需要相同的的金属锭 $a_i$ 块，销毁一把 $i$ 种的武器可以返还 $b_i$ 块制造它时使用的金属锭。

给你 $m$ 种金属锭，第 $i$ 种金属锭有 $c_i$ 块。

问你用这 $m$ 种金属锭能进行锻造与融化操作最多多少次。

## 题解

不难看出，每锻造了一把武器后肯定融毁更优。所以对于第 $i$ 种武器，每次锻造和融毁会消耗 $a_i-b_i$ 块金属锭。又因为相同情况下取用消耗少的武器方案比消耗多的方案更优，于是我们以 $a_i-b_i$ 为关键字从小到大给武器方案排序，$a_i-b_i$ 相同时则以 $a_i$ 为关键字从小到大排序。

对于排完序之后的数组，如果后面的武器的 $a_i$ 比前面的 $a_i$ 还要大，那么后面的武器方案就被淘汰了（因为他的消耗多，门槛又高）。所以这里可以将数组用单调栈以 $a_i$ 为关键字优化为使 $a_i$ 递减的序列。

接下来用 DP 求出 $x$ 块金属锭可以进行的最多操作数 $dp_x$ 并且记录小于 $x$ 块金属锭能进行的最大操作数 $mdp_x$。具体地，找到序列从后往前最大的小于 $x$ 的 $a_i$，此时用这个方案损耗最小，为 $a_i-b_i$。于是转移方程为  
$dp_x=mdp_{x-(a_i-b_i)}+1$  
$mdp_x= \max (mdp_{i-1},dp_i)$  
DP 上界为 $10^6$。

最后，对于 $1 \le c_i \le 10^6$，答案为 $dp_{c_i}$。对于 $10^6 \le c_i \le 10^9$，由于当前用序列第一个方案最优，于是用变量 $ans$ 表示能用第一个方案最多几次，则答案为 $ans+dp_{c_i-(a_1-b_1) \times ans}$。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int ti,n,m,c,dp[1000100],mdp[1000100];
struct node{
	int a,b;
}t[1000100],l[1000100];
bool cmp(node x,node y){
	if(x.a-x.b!=y.a-y.b) return x.a-x.b<y.a-y.b;//以ai-bi为第一关键字 
	else return x.a<y.a;//以ai为第二关键字 
}
signed main(){
	for(int o=1;o<=1;o++){
		long long ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			scanf("%lld",&t[i].a);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&t[i].b);
		}
		sort(t+1,t+n+1,cmp);
		int rol=0;
		l[0]={10000000,10000000};
		for(int i=1;i<=n;i++){
			if(t[i].a<l[rol].a){
				l[++rol]=t[i];//数组模拟单调栈 
			}
		}
		int mn=l[rol].a;
		int mx=l[1].a;
		rol++;
		int cha=0;
		for(int i=mn;i<=mx;i++){
			if(i==l[rol-1].a){
				rol--;
				cha=l[rol].a-l[rol].b;
			}
			dp[i]=mdp[i-cha]+1;
			mdp[i]=max(mdp[i-1],dp[i]);//DP转移 
		}
		for(int i=1;i<=m;i++){
			scanf("%lld",&c);
			if(c>mx){
				int ned=(c-l[1].b)/cha;//最多能使用第一个方案几次 
				c-=ned*cha; ans+=ned;
			}
			ans+=dp[c];
		}
		cout<<ans*2;
	}
}
```

顺便提一嘴，这题赛时 CodeForces 数据过水甚至连我用错数组名都过了导致赛后我被hack数据叉掉，~~CodeForces赔我分！！~~

---

## 作者：旻偲 (赞：5)

## 题号：CF1989D
### 题意：  

你有 $n$ 种武器和 $m$ 种金属，每一种金属初始有 $c_j$ 的数量。  
你有两种操作： 

- 锻造：任意选定一种金属，花费这一种金属的 $a_i$ 个来制造这个武器。
- 销毁：用第 $i$ 种金属锻造的这个武器，经过销毁后，增加 $b_i$ 个第$i$种金属。  

求最大的操作次数。

### 思路：
对于第 $i$ 种金属，若要对第 $j$ 种武器，进行一次锻造操作，再进行一次销毁操作 $(a_j \leq c_i)$，那么数量的变化是 $c_i - a_j + b_j$，即 $c_i - (a_j - b_j)$ 那么我们就可以发现，经过这两次操作后，我们金属真正减少的数量是 $a_j - b_j$。  

那么一个贪心思路就呼之欲出了：  

**若是我们想让操作次数尽可能的多，那么每次金属减少的数量就应该尽可能地少。对于一种金属来说，一直对 $a_i - b_i$ 尽可能小的武器进行操作，是最优的**。  

之所以是**尽可能**是因为我们要考虑当前金属数量是否大于 $a_i$。

 接下来本文对操作的定义如下：  

>用当前的金属数量不断去与当前的武器进行锻造和销毁操作，直到金属的数量不足以进行新的锻造操作。  
形式化地说：当前是第 $j$ 种武器和第 $i$ 种金属，让 $c_i$ 不断地减去 $a_j - b_j$ 直到 $c_i' < a_j$。

### 做法：
于是首先将 $(a_j,b_j)$ 按照 $a_j - b_j$ 从小到大排序。

然后枚举每一种金属，对于第 $i$ 种金属，我们去枚举排序后的武器，若当前枚举到了第 $j$ 种武器，若满足 $a_j \leq c_i$ 则我们一定会对这种武器进行操作，（因为这是可以进行操作的武器中，$a_j - b_j$ 最小的，所以对它进行操作一定是最优的），然后继续往后枚举找到 $a_j' \leq c_i'$，重复上面的操作，直到枚举完所有的武器。  

这个算法是 $O(n \log n + n \times m)$ 的复杂度，显然是通不过这个题目的。  

### 优化：

上面的算法存在的一个问题是，出现的很多的重复枚举：对于每一种金属我们都会去枚举一遍所有的武器，所以就会导致复杂度较高。  

那么我们怎么去减少重复枚举呢？ 

考虑单调性：**一个 $c_j$ 经过操作后，一定是变小的** 。

用一个优先队列 $q$ 去维护金属的数量。  

对于第 $i$ 种武器，在优先队列中，$a_i \leq q_j$ 的金属都是可以对第 $i$ 种武器进行操作的。所以我们不断从 $q$ 取出最大值，去与当前武器进行操作，同时将操作之后的值放回 $q$ 中，直到 $q_j < a_i$，就继续枚举 $a_i$，直到 $a_i \leq q_j$，然后重复上述操作，直到枚举完所有的武器。

这样保证每一种武器只会被枚举一遍。 
 
但是上述的优化加入之后，还是无法通过此题。  

原因：$q$ 中的值，在经过金属和武器的操作之后，可能会出现很多一样的值，这样也会导致重复枚举。

那怎么优化金属值的重复枚举呢？ 

我们考虑用一个 map 代替优先队列，这样就不需要重复枚举一个相同值，只用在统计答案的时候乘上这个值的数量就好了。

若我们直接从 $c_j$ 的上界 $10^9$ 枚举每一个可能的金属值，显然这个也是不行的。但是我们注意到 $c_j \leq 10^9$ 而 $a_i \leq 10^6$，也就是说，所有的 $c_j$ 经过一次操作后，一定会小于 $10^6$。

所以，我们对所有 $ > 10^6$ 的 $c_j$ 进行预处理，对它先进行一次操作。让所有的 $c_j \leq 10^6$。这样从 $10^6$ 开始枚举金属可能的值，就可以顺利的通过这题了。

### code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开ll不能过这个题
const int maxn = 1000010;
int c[maxn];
map<int,int> d;//统计每一个值出现的个数
struct node
{
    int a,b,cha;
} q[maxn];
bool cmp(node a,node b)
{
    if(a.cha == b.cha)
    {
        return a.a < b.a;
    }
    else return a.cha < b.cha;
}//排序，若 ai - bi的值相同，那么就a小的排在前面。
signed main
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);//注意解绑，map常数较大，不开这个会被卡常
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> q[i].a;
    for(int i = 1;i <= n;i++) cin >> q[i].b,q[i].cha = q[i].a - q[i].b;
    int ji = -1;
    for(int i = 1;i <= m;i++) cin >> c[i],ji = max(ji,c[i]),d[c[i]]++;
    sort(q + 1,q + n + 1,cmp);
    int ans = 0;
    for(int i = 1;i <= m;i++)
    {
        if(c[i] > 1000000)
        {
            int ho = (c[i] - q[1].a)/q[1].cha;
            int ji = q[1].cha * ho;
            if(ji <= c[i] - q[1].a)
            {
                ji += q[1].cha;
                ho++;
                d[c[i] - ji]++;
            }
            else d[c[i] - ji]++;
            ans += ho*2;
        }//预处理 > 1000000 的 cj
    }
    int l = 1;
    for(int i = 1000000;i >= 0;i--)//利用单调性开始枚举。
    {
        if(!d[i]) continue;
        while(q[l].a > i && l <= n)
        {
            l++;
        }//若当前枚举的金属的值已经无法锻造这个武器了，就往后枚举武器。
        if(l > n) break;//枚举完所有的武器就退出。
        int ho = (i - q[l].a)/q[l].cha;//计算操作次数，每次减少ai - bi，可以减少多少次，就是可以操作的次数。
        if(q[i].cha * ho <= i - q[l].a)
        {
            ho++;
            d[i - q[l].cha*ho] += d[i];//当前操作之后变成值的数量要加上当前值的数量。
        }
        else d[i - q[l].cha*ho] += d[i];
        ans += ho*2*d[i];//因为一次操作包含了锻造和销毁两种所以要乘2，同时乘上这个值的个数。
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Louis_lxy (赞：4)

一个贪心加 dp 的题目。

首先考虑贪心，显然我们发现我们一定是制作后立马融化，因为后面再融化并没有区别，因此我们可以通过除法直接得到能制作融化的次数。

接着，我们考虑处理顺序，我们发现，处理的数量与 $a_i-b_i$ 有关（算能处理的数量的除式），接着我们按 $a_i$ 排序，因为如果 $a_i-b_i$ 相同说明可以处理的数量相同，但是如果 $c_i<a_i$ 显然无法造成贡献。

然后我们发现，这样会有一个问题，就是如果剩下一些，有可能可以用别的方法造成贡献，此时贪心很难计算。

考虑 dp。我们设 $f_i$ 表示 $i$ 个金属锭可以进行的最大操作次数，$g_i$ 表示小于等于 $i$ 个金属锭可以进行的最大操作次数。我们令 $j$ 表示从后往前第一个最大的小于 $i$ 的 $a_j$ 的编号。此时 dp 方程是：

$f_i=g_{i-(a_j-b_j)}+1\\$
$g_i=\max(g_{i-1},f_i)$

处理第一个最大的小于 $a_i$ 的 $a_j$ 可以用单调栈实现，我们只需要维护一个单调下降的栈即可。

然后考虑计算答案，首先我们发现，我们可以假定一定是选择最优的方案，剩下的才用 $f$ 数组得到答案，此时最多能使用的次数是 $(c_i-b_{s_1})/(a_{s_1}-b_{s_1})$，$s$ 数组是维护的单调栈，$s_1$ 即整个栈中第一个小于维护范围的数。

考虑维护范围，显然要维护到 $10^6$，因此将 $a_0\gets10^6+1$。

AC 记录：https://www.luogu.com.cn/record/168302077

---

## 作者：鸡枞_ (赞：4)

# CF1989D Smithing Skill
[传送门](https://www.luogu.com.cn/problem/CF1989D)
## 思路
基于一个贪心的思想，应该先用 $a_i-b_i$ 大的武器，当有多个武器 $a_i-b_i$ 相同时，只取其中 $a_i$ 最小的来用。

另外注意到，当考虑完一个武器后，他消耗过的某一种金属锭剩下的数量 $x$ 满足 $b_i \leq x < a_i$，其他没有消耗过的金属锭数量满足 $c_i < a_i$。所以每次考虑完一个武器之后，$\max c_i < a_i$，上界是在不断缩小的。于是我们只需在值域上枚举一遍即可，详见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

const int MAXN = 1e6 + 10, N = 1e6;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

random_device seed;
mt19937 rnd(seed());
mt19937_64 rnd_64(seed());

ll n, m;
ll a[MAXN], b[MAXN], c[MAXN];
ll cnt[MAXN];
map<ll, ll> cost;
ll ans = 0, last = INF;
bool f = 0;

void solve () {
    cin >> n >> m;
    for(ll i = 1; i <= n; ++i) cin >> a[i];
    for(ll i = 1; i <= n; ++i) cin >> b[i];

    for(ll i = 1; i <= m; ++i) cin >> c[i];

    for(ll i = 1; i <= n; ++i) {
        if(cost.count(a[i] - b[i])) cost[a[i] - b[i]] = min(cost[a[i] - b[i]], a[i]);
        else cost[a[i] - b[i]] = a[i];
    }

    sort(c + 1, c + 1 + m);
    for(auto [x, y] : cost) {
        if(!f) {
            ll p = lower_bound(c + 1, c + 1 + m, y) - c;
            if(p == m + 1) continue;
            for(ll i = m; i >= p; --i) {
                ll t = (c[i] - y) / x + 1;
                ans += t * 2;
                c[i] = c[i] - x * t;
                cnt[c[i]] += 1;
            }
            for(ll i = p - 1; i >= 1; --i) {
                cnt[c[i]] += 1;
            }
            last = y;
            f = 1;
        } else {
            if(y > last - 1) continue;
            for(ll i = last - 1; i >= y; --i) {
                if(cnt[i]) {
                    ll t = (i - y) / x + 1;
                    ans += cnt[i] * t * 2;
                    cnt[i - x * t] += cnt[i];
                    cnt[i] = 0;
                }
            }
            last = y;
        }
    }

    cout << ans << "\n";
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int Task = 1;
    // cin >> Task;
    while (Task--) {
        solve();
    }

    return 0;
}
```

---

## 作者：Halberd_Cease (赞：3)

简要观察一下，可以发现一定是将同种铁锭铸成剑，然后熔掉，以此类推，直到不能铸成任何一把剑。

因此题目等价于：每次选择 $i,j$ 使得 $a_i\le c_j$，将 $c_j\gets c_j-a_i+b_i$，问最多可以操作多少次（答案当然还要再乘上一个 $2$）。

注意到题目限制了 $a_i$ 的值域为 $a_i\le10^6$，考虑处理出所有当前种类锭的数量 $\le10^6$ 时，还能加多少经验。

显然，当 $c_i>10^6$ 时，一定可以铸任意一把剑，我们直接用 $a_i-b_i$ 最小的去重复这个过程直到 $c_i\le10^6$，这一步可以 $O(1)$。

对于剩下的情况，考虑先设一个 dp 数组 $down_i$ 表示在当前还有 $i$ 块锭的情况下，进行一次操作需要的花费（也就是 $\min \limits_{a_j\le i}a_j-b_j$）。

考虑转移，首先对于每一个 $a_i$，我们令 $down_{a_i}=\min(down_{a_i},a_i-b_i)$，然后再从 $1$ 到 $10^6$ 类似前缀最小值的方式转移（$down_{i}=\min(down_i,down_{i-1})$）。

预处理出这个数组，我们再来处理所有 $c_i\le10^6$ 时的答案。

令 $res_i$ 表示当前有 $i$ 块锭时最大能获得的经验值，显然有转移方程 $res_i=res_{i-down_i}+2$，注意边界情况，初始 $down$ 数组全为极大值，下标可能出现负数。

然后直接调用答案数组就可以了。

[submission](https://codeforces.com/contest/1989/submission/268086326)

---

## 作者：Mirage_Insane (赞：2)

## 大致题意

有 $n$ 对数，第 $i$ 对数表示为 $(a_i,b_i)$。再给定 $m$ 个数，第 $i$ 个数为 $c_i$。对于 $\forall j$，若有 $c_i \geq a_j$，则可将 $c_i$ 变为 $c_i - (a_j - b_j)$ 并获得 2 点代价。问这 $m$ 个数能得到的最大代价。

## 题解

先考虑一个简单的贪心。我们肯定希望多选择 $a_i - b_i$ 尽可能小的，这样造成的损失也一定小。若 $a_i - b_i = a_j - b_j$，那在这两对数中，$a$ 更小的一定用得更多。因此，我们维护一个 $g$ 数组，$g_i$ 表示差为 $i$ 的数对中 $a$ 的最小值。

接下来的事情就好办了。假如我们手上有数字 $c$，考虑用 $g_i$ 去修改它，令 $k = \lfloor\frac{c - g_i}{i} \rfloor + 1$，显然能得到的最大代价为 $2 \times k$，这次操作后 $c$ 会变为 $c - i \times k$。这个应该很好推。那么选择哪个 $g_i$ 最优呢？显然，在 $c \geq g_i$ 的前提下选择 $i$ 最小的最优。用 pair 处理一下二分即可。

由于 $a_i \leq 10^6$，所以无论多大的数，通过上述操作都可以在 1 步之内变成一个小于 $10^6$ 的数。记忆化搜索一下就完了。

### Code:

```cpp
#define Vanishment return
#define This 0
#define World ;
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
int g[1000005], a[1000005], dp[1000005], len;
pair<int, int> s[1000005];
bool cmp(int a, int b) {
	return a > b;
}
int dfs(int x) {
	if(x <= 1e6) {
		if(dp[x]) return dp[x];
	}
	int l = 1, r = len;
	while(l < r) {
		int mid = l + r >> 1;
		if(s[mid].second <= x) r = mid;
		else l = mid + 1;
	}
	int sum = l;
	if(s[sum].second > x) return 0;
	int k = (x - s[sum].second) / s[sum].first + 1;
	int ans = 2 * k + dfs(x - k * s[sum].first);
	if(x <= 1e6) dp[x] = ans;
	return ans;
}
signed main() {
	memset(g, 0x3f, sizeof(g));
	int n, m, x, ans = 0;
	SF("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++) SF("%lld", &a[i]);
	for(int i = 1; i <= n; i++) SF("%lld", &x), g[a[i] - x] = min(g[a[i] - x], a[i]);
	int now = 0x3f3f3f3f;
	for(int i = 1; i <= 1e6; i++) {
		if(g[i] < now) s[++len] = make_pair(i, g[i]), now = g[i];
	}
	for(int i = 1; i <= m; i++) SF("%lld", &a[i]);
	sort(a + 1, a + 1 + m, cmp);
	for(int i = 1; i <= m; i++) ans += dfs(a[i]);
	PF("%lld", ans);
	Vanishment This World
}
```

---

## 作者：__Louis__ (赞：1)

## 题解：CF1989D Smithing Skill

### 题目大意

你有 $m$ 种不同的材料，每种材料都有 $C_i$ 种。

现在有 $n$ 种制作不同工具的方法，对于每一种方案，每一次制作工具都会消耗 $A_i$ 个同种材料，同时，你还能把所有的工具复原，并取回 $B_i$ 的原材料。

问最大的操作次数。操作次数包含制作和复原。

$n,m\le 10^6$

### 思路

如果 $m$ 为 $1$ 就极为好做，很明显这是一个贪心，因为用 $A_i-B_i$ 小的方案去锻造一定不会比多的亏。所以直接按照差排序即可，且差相同的时候把 $B_i$ 较小的放前面。

最终可以使用的方案就是从 $1$ 开始的以 $A_i$ 下降一个序列。

按照贪心的方法排序以后，发现每一种有用的制作方案，都会导致 dp 答案之间的距离缩小。

设 $dis$ 为现在开始最小往上 $dis$ 才能使答案加一。

首先从 $B_i$ 最小的开始 dp，每一次向上加 $dis$ 直到其总和大于某一个 $A_i$，然后把 $dis$ 改成 $\min(A_i-B_i,dis)$。


但是 $m$ 很大，我们需要考虑每一次找答案的优化。

如果说每一次都做一遍贪心和 dp，是很麻烦的，于是我们希望把 dp 的结果存下来。



如果预处理出每一个方案开始的位置（指的是从这个位置开始就会以 $A_i-B_i$ 的距离把答案增大）。就可以二分整个序列，根据算出来的值求出答案了。

复杂度 $O(m\log n)$。

### [AC 记录](https://codeforces.com/contest/1989/submission/286373966)

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
struct node{
	int x,y,da,dis;
}arr[maxn],ans[maxn];
bool cmp(node a,node b){
	if(a.y+b.x==a.x+b.y){
		return a.x<b.x;
	}else{
		return a.y+b.x<a.x+b.y;
	}
}
int cnt=0;
signed main(){
	int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&arr[i].y);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&arr[i].x);
		arr[i].dis=arr[i].y-arr[i].x;
	}
	sort(arr+1,arr+1+n,cmp);
	int mn=0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=n;i++){
		if(arr[i].y<mn){
			mn=arr[i].y;
			ans[++cnt]=arr[i];
		}
	} 
	ans[cnt].da=0;
	for(int i=cnt-1;i>=1;i--){
		int f=(ans[i].y-ans[i+1].x)/ans[i+1].dis;
		ans[i].da=ans[i+1].da+f;
		ans[i].x=max(ans[i].x,ans[i+1].x+f*ans[i+1].dis); 
	}
	int sum=0,a;
	int l=1,r=cnt+1;
	for(int i=1;i<=m;i++){
		scanf("%lld",&a);
		l=1,r=cnt+1;
		while(l<r){
			int mid=(l+r)>>1;
			if(a>=ans[mid].x) r=mid;
			else l=mid+1; 
		}
		if(l==cnt+1) continue;
		sum+=(ans[l].da+(a-ans[l].x)/(ans[l].dis)); 
	}
	printf("%lld",sum*2);
	return 0;
}
```

---

## 作者：_qingshu_ (赞：1)

# 题意：

你有 $n$ 种武器，$m$ 种金属，你可以选择用 $a_i(i\le n)$ 个同种金属合成一个 $i$ 类武器，然后将其溶掉获得 $b_i$ 个该种金属，期间你将获得 $2$ 点经验。在最开始，你的第 $i(i\le m)$ 种金属有 $c_i$ 个。询问最大经验。

# 思路：

可以先写出一个简单的暴力。发现存在一个明显的贪心，我选择的武器一定是当前可以合成的武器中 $a_i-b_i$ 最小的，因为合成任意武器的答案贡献相等，那么这个贪心的正确性也是显然的。

有了这个贪心，你就可以想到 $c_i\le 10^9$ 的值域其实在 $[10^9,\max\limits_{i=1}^{n}a_i]$ 时的选择是完全相同的，那么我们完全可以预处理出当 $c_i\le 10^6$ 时的答案（当然，你也可以求 $c\le \max\limits_{i=1}^{n}a_i$）。下面我们来考虑转移方程。

首先 $f_{i}\ge f_{i-1}$ 是显然的，你可以理解为剩下的一个不予理会。然后考虑打造武器，还是上面的贪心，定义 $it$ 为满足不存在有 $j\ne it\land j\le n\land a_j-b_j<a_{it}-b_{it}$ 且满足 $a_{it}\le i$ 的一个解，那么 $f_i$ 可以被 $2+f_{i-(a_{it}-b_{it})}$ 转移。

综上，$f_{i}=\max(f_{i-1},2+f_{i-(a_{it}-b_{it})})$。

再来考虑答案，显然需要分类讨论，分为 $c_i\le 10^6$ 与 $c_i>10^6$（您也可以将 $10^6$ 替换为 $\max\limits_{i=1}^{n}a_i$）。答案为：

$$
ans=ans+\left\{
\begin{array}{c}
f_{c_i}      &      & {c_i\le 10^6}\\
2\times\lceil\frac{c_i-10^6}{a_{it}-b_{it}}\rceil+f_{c_i-\lceil\frac{c_i-10^6}{a_{it}-b_{it}}\rceil\times (a_{it}-b_{it})}&      & {c_i>10^6}
\end{array} \right. 
$$

# Code：

```cpp
#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
long long n,m,f[1000010],tot,it;
pair<int,int>sp[5200010];
inline solve(long long ans=0){
	cin>>n>>m;for(int i=1;i<=n;i++)scanf("%d",&sp[i].F);
	for(int i=1,x;i<=n;i++){scanf("%d",&x);sp[i].S=sp[i].F-x;}
	stable_sort(sp+1,sp+n+1);
	for(int i=1;i<=1e6;i++){
		while(sp[tot+1].F==i){tot++;if(it==0||sp[it].S>sp[tot].S)it=tot;}
		f[i]=f[i-1];if(it)f[i]=max(f[i],2+f[i-sp[it].S]);
	}
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);if(x<=1e6)ans+=f[x];
		else ans+=2*((x-1000000+sp[it].S-1)/sp[it].S)+
					f[x-(x-1000000+sp[it].S-1)/sp[it].S*sp[it].S];
	}cout<<ans<<"\n";
}
int main(){
	int T=1;//cin>>T;
	while(T--)solve();
}
```

update：

- 修改了运算符。

---

## 作者：xiezheyuan (赞：1)

## 简要题意

有 $n$ 种武器，铸造第 $i$ 把武器需要 $a_i$ 个同类金属锭，获得 $1$ 点经验。熔化第 $i$ 把武器可以获得 $b_i$ 个与原先合成的金属锭类型相同的金属锭，获得 $1$ 点经验。

金属共有 $m$ 种。你有 $c_i$ 个 $i$ 种金属。

求你可以获得的最大的经验值总和。

## 思路

首先贪心地，我们肯定是取 $a-b$ 尽可能小的武器进行合成。但是这样子会有问题，就是 $a$ 可能比现在的金属锭总数大。

我们可以 dp，设 $f(i)$ 表示 $i$ 个同类金属锭可以获得的最大经验值总和。转移是容易的。

然后我们枚举每一种金属，将对应 $f(i)$ 加起来即可。

但是我们发现 $c_i$ 有 $10^9$ 级别。线性 dp 无法承受，但是发现 $a_i\leq 10^6$，也就是我们可以不停地铸造和熔炼最好的武器，直到小于 $10^6$，然后再用 dp 的结果。

于是我们就做完了。注意细节一堆。可以参考一下官方题解（是 Kotlin 的，可以凑合着看看）是如何处理的，我感觉比我一开始写的好得多。

代码丑，就不放了。

---

## 作者：No_Rest (赞：0)

# 思路

首先可以贪心。锻造出的武器一定可以熔掉。多种材料互相独立，可以分别算完加在一起。每次一定选择 $a_i - b_i$ 最小（锻造然后熔掉损失最少）的武器进行锻造然后熔掉。

但是直接贪心可能会被卡成 $\mathcal O(n^2)$。

注意到 $a_i \le 10^6$。故可以预处理出 $10^6$ 以内的所有答案。这样对于 $> 10^6$ 的所有 $c_i$，贪心地选择 $a_i - b_i$ 最小的武器进行锻造熔掉，直到 $c_i \le 10^6$，再加上预处理出的答案即可。

贪心的过程可以 $\mathcal O(1)$ 解决，考虑如何线性预处理 $10^6$ 内的答案。考虑 dp。设 $d_i$ 表示在有 $i$ 个材料的情况下能选择锻造熔掉的武器当中最小的 $a_i - b_i$。这个数组可以在输入的时候先预处理成 $d_{a_i} = \min (d_{a_i}, a_i - b_i)$，然后再前缀 $\min$ 一下，就可以算出来了。这样 dp 时的转移方程就是 $f_i = f_{i - d_i} + 2$。

然后就做完了。

# 代码

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const ll maxn = 1e6 + 5;
const ll inf = 1e18;
const ll N = 1e6;
ll n, m, a[maxn], b[maxn], c[maxn], f[maxn], d[maxn], ans;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	f[0] = 0;
	for(ll i = 0; i <= N; ++i) d[i] = inf;//初始化 
	for(ll i = 1; i <= n; ++i) cin >> a[i];
	for(ll i = 1; i <= n; ++i) cin >> b[i], d[a[i]] = min(d[a[i]], a[i] - b[i]); 
	for(ll i = 1; i <= N; ++i) d[i] = min(d[i], d[i - 1]);//前缀 min 处理 d 数组 
	for(ll i = 1; i <= N; ++i)
		if(i >= d[i]) f[i] = f[i - d[i]] + 2;//dp
	for(ll i = 1; i <= m; ++i){
		cin >> c[i];
		if(c[i] <= N) ans += f[c[i]];
		else {
			ans += (c[i] - N) / d[N] * 2;
			c[i] = c[i] - (c[i] - N) / d[N] * d[N];
			if(c[i] > N) c[i] -= d[N], ans += 2;//贪心 
			ans += f[c[i]];
		}
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：lfxxx (赞：0)

考虑贪心。

题目等价于每次可以用 $a_i - b_i$ 换来两个贡献，但是少于 $a_i$ 时就不能换贡献，那么我们发现把花在 $a_i - b_i$ 大的换贡献方式上的金属花在 $a_i - b_i$ 小的上一定不劣，于是考虑把所有数按照 $a_i - b_i$ 升序排序，从前往后考虑。

不难发现每种金属之间是独立的，我们只需要计算其贡献系数即可。

考虑维护 $sz_i$ 表示当前状态下还剩 $i$ 块金属的金属种类有多少，那么对于每个 $a_i - b_i$ 而言。我们会把所有大于等于 $a_i$ 的 $sz$ 状态算贡献并将这些状态合并到比 $a_i$ 小的状态上，考虑维护当前最大非空状态 $top$，那么每次回花费 $top - a_i$ 的时间使得 $top \gets a_i$，又因为考虑第一个物品后 $top \leq a_1$，所以时间复杂度 $O(n + m + \max(a_i))$，可以通过。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
struct node{
    int a,b;
}c[maxn];
int sz[maxn];
int ans;
pair<int,int> cost(int v,int a,int b){
    int g=a-b;
    if(v<a) return make_pair(0,v);
    v-=a;
    int cnt=v/g;
    int w=v%g;
    return make_pair(cnt+1,a-(g-w));
}//cnt w
int n,m;
int maxv = 1e6;
bool cmp(node x,node y){
    return x.a-x.b<y.a-y.b;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i].a;
    for(int i=1;i<=n;i++) cin>>c[i].b;
    sort(c+1,c+n+1,cmp);
    for(int i=1;i<=m;i++){
        int v;
        cin>>v;
        pair<int,int> val=cost(v,c[1].a,c[1].b);
        ans+=val.first*2;
        sz[val.second]++;
    }
    for(int i=2;i<=n;i++){
        for(int j=maxv;j>=c[i].a;j--){
            if(sz[j]==0) continue;
            pair<int,int> val=cost(j,c[i].a,c[i].b);
            ans+=2*sz[j]*val.first;
            sz[val.second]+=sz[j];
            sz[j]=0;
        }
        maxv=min(maxv,c[i].a-1);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

首先这里有几个很明显的贪心：
+ 每次锻造武器后，一定要熔炼它；
+ 每次实际消耗的铸锭数量为锻造所需减熔炼所得，所以 $(a_i-b_i)$ 小的优先选择；
+ $(a_i-b_i)$ 同样的情况下，$a_i$ 小的一定比 $a_i$ 大的更优，因为消耗相同，它所需下限更低。

由此，当要锻造武器 $i$，锻造所需 $a_i$ 块铸锭，熔炼所得 $b_i$ 块铸锭，现有 $c_j$ 块铸锭时，最大操作（一次锻造加一次熔炼算一次操作）次数为：

$$\left\lceil \frac{c_i-a_i+1}{a_i-b_i} \right\rceil$$

这样可以对于每种铸锭，按照 $(a_i-b_i)$ 从小到大依次尝试操作，时间复杂度 $O(NM)$，会超时。

考虑记忆化，记 $min\_cost_i$ 为当前有 $i$ 块铸锭时，可以进行操作的最小 $(a_i-b_i)$，也就是当前可操作的最小消耗，然后每次 `while` 累计总操作次数，可以减小遍历所有武器的可能。

这样可以优化部分时间复杂度，但是极限仍然是 $O(NM)$，只能算是卡常技巧。

但是，上面可以启发我们加深记忆化程度，设 $f_i$ 为有 $i$ 块铸锭时的最大经验值。设它操作一次以后还剩 $i'$ 块铸锭，若 $f_{i'}$ 已知，那么就可以直接推出 $f_i$ ，而因为 $i' < i$ 所以 $f$ 可以顺序递推。

当有 $i$ 块铸锭时，设 $spend$ 为最小消耗，$addr$ 为达到最小消耗时所需的最小铸锭数量（即对应的 $a$），那么可操作的次数 $cnt$ 就为：

$$\left\lceil \frac{i-adddr+1}{spend} \right\rceil$$

转移方程也可以出来了：

$$f_i = 2 \times cnt + f_{i - cnt \times spend}$$

最后若 $c_i \le 10^6$，直接查询 $f_{c_i}$ 即可；否则经过一次操作以后，$c_i$ 一定小于等于 $10^6$，此时再查询 $f_{c_i}$ 即可。

-----

代码中赛事为了卡 $O(NM)$ 的时间，用了下去重卡常：
+ `pair` 类型的 $c$ 数组的 `first` 和 `second` 分别表示原数据和出现的次数；
+ `pair` 类型的 $cost$ 数组的 `first` 和 `second` 分别表示消耗和这个消耗所需铸锭下限；
+ $min\_cost$ 和 $f$ 等的含义如上文。

代码：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=1e6+5,MAXA=1e6;
int n,m; //weapon, metal
int a[N],b[N]; //weapon[i] need a[i] and return b[i]
int c_raw[N]; //the starter metal

pair<int,int> c[N]; //{number,times}
pair<int,int> cost_raw[N],cost[N]; //{cost,floor}
int cost_idx,c_idx;
pair<int,int> min_cost[MAXA+5]; //the lowest cost per each when have i ingots
long long f[MAXA+5]; //answer

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=m;i++) scanf("%d",&c_raw[i]);
	
	for(int i=1;i<=n;i++) cost_raw[i]={a[i]-b[i],a[i]};
	sort(cost_raw+1,cost_raw+n+1);
	for(int i=1;i<=n;i++)
		if(cost_raw[i].first!=cost_raw[i-1].first)
			cost[++cost_idx]=cost_raw[i]; 
	for(int i=0;i<=MAXA;i++)
		min_cost[i]={0x3f3f3f3f,0};
	int max_a=0;
	for(int i=1;i<=cost_idx;i++)
	{
		min_cost[cost[i].second]=min(min_cost[cost[i].second],{cost[i].first,cost[i].second});
		max_a=max(max_a,cost[i].second);
	}
	for(int i=1;i<=MAXA;i++)
		min_cost[i]=min(min_cost[i],min_cost[i-1]);
	sort(c_raw+1,c_raw+m+1);
	for(int i=1;i<=m;i++)
	{
		if(c_raw[i]==c_raw[i-1]) c[c_idx].second++;
		else c[++c_idx]={c_raw[i],1};
	}
	
	for(int i=1;i<=MAXA;i++)
	{
		int spend=min_cost[i].first,addr=min_cost[i].second;
		if(!addr) continue;
		long long cnt=ceil((double)(i-addr+1)/spend);
		f[i]=(cnt<<1)+f[i-cnt*spend];
	}
	long long ans=0;
	for(int i=1;i<=c_idx;i++)
	{
		int rest=c[i].first,mul=c[i].second;
		if(rest>MAXA)
		{
			int spend=min_cost[MAXA].first,addr=min_cost[MAXA].second;
			long long cnt=ceil((double)(rest-addr+1)/spend);
			rest-=cnt*spend;
			ans+=(cnt*mul)<<1;
		}
		ans+=f[rest]*mul;
	}
	
	printf("%lld\n",ans);
	return 0;
}
```

---

