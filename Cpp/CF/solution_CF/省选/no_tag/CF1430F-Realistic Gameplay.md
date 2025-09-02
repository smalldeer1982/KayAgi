# Realistic Gameplay

## 题目描述

Recently you've discovered a new shooter. They say it has realistic game mechanics.

Your character has a gun with magazine size equal to $ k $ and should exterminate $ n $ waves of monsters. The $ i $ -th wave consists of $ a_i $ monsters and happens from the $ l_i $ -th moment of time up to the $ r_i $ -th moments of time. All $ a_i $ monsters spawn at moment $ l_i $ and you have to exterminate all of them before the moment $ r_i $ ends (you can kill monsters right at moment $ r_i $ ). For every two consecutive waves, the second wave starts not earlier than the first wave ends (though the second wave can start at the same moment when the first wave ends) — formally, the condition $ r_i \le l_{i + 1} $ holds. Take a look at the notes for the examples to understand the process better.

You are confident in yours and your character's skills so you can assume that aiming and shooting are instant and you need exactly one bullet to kill one monster. But reloading takes exactly $ 1 $ unit of time.

One of the realistic mechanics is a mechanic of reloading: when you reload you throw away the old magazine with all remaining bullets in it. That's why constant reloads may cost you excessive amounts of spent bullets.

You've taken a liking to this mechanic so now you are wondering: what is the minimum possible number of bullets you need to spend (both used and thrown) to exterminate all waves.

Note that you don't throw the remaining bullets away after eradicating all monsters, and you start with a full magazine.

## 说明/提示

In the first example:

- At the moment $ 2 $ , the first wave occurs and $ 6 $ monsters spawn. You kill $ 3 $ monsters and start reloading.
- At the moment $ 3 $ , the second wave occurs and $ 3 $ more monsters spawn. You kill remaining $ 3 $ monsters from the first wave and start reloading.
- At the moment $ 4 $ , you kill remaining $ 3 $ monsters from the second wave.

 In total, you'll spend $ 9 $ bullets.In the second example:

- At moment $ 3 $ , the first wave occurs and $ 11 $ monsters spawn. You kill $ 5 $ monsters and start reloading.
- At moment $ 4 $ , you kill $ 5 $ more monsters and start reloading.
- At moment $ 5 $ , you kill the last monster and start reloading throwing away old magazine with $ 4 $ bullets.
- At moment $ 10 $ , the second wave occurs and $ 15 $ monsters spawn. You kill $ 5 $ monsters and start reloading.
- At moment $ 11 $ , you kill $ 5 $ more monsters and start reloading.
- At moment $ 12 $ , you kill last $ 5 $ monsters.

 In total, you'll spend $ 30 $ bullets.

## 样例 #1

### 输入

```
2 3
2 3 6
3 4 3```

### 输出

```
9```

## 样例 #2

### 输入

```
2 5
3 7 11
10 12 15```

### 输出

```
30```

## 样例 #3

### 输入

```
5 42
42 42 42
42 43 42
43 44 42
44 45 42
45 45 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
1 10
100 111 1```

### 输出

```
1```

# 题解

## 作者：王鲲鹏 (赞：9)

贪心。

* 首先，如果有解，那所有 $a_i$ 都要算上，所以只要考虑换弹夹所带来的额外消耗。
* 尽量不换是最优的。考虑什么时候必须换弹夹。
* 需不需要换弹夹由后面决定。因为后面如果特别紧，这个时候就必须换。如果后面不是那么紧张，就可以打完子弹再换。
* 受这种启发，考虑尽量靠后地射击。如果这一波人数特别多，但是上一波也挺多的，并且 $r_{i-1}=l_i$ ，如果我们安排了过多在 $l_i$ 时间射击，就可能导致前一段无法消灭敌人。所以尽可能安排在 $(l_i,r_i]$ 去射击。
* 设 $dp[i]$ 表示第 $i$ 波敌人来时的必要射击次数。
* 如果 $i$ 段和 $i+1$ 段重叠，那么在 $i$ 的时间段内要多设 $dp_{i+1}$个。
* 从后向前DP即可

复杂度 $O(n)$。

代码
```cpp
#include <cstdio>
typedef long long ll;
int n = 0;
ll k = 0;
ll l[2003], r[2003], a[2003];
ll dp[2003];
int main() {
	scanf("%d %lld", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%lld %lld %lld", l + i, r + i, a + i);
	for (int i = n; i >= 1; --i) {
		ll need = a[i] + (i < n && r[i] == l[i + 1] ? dp[i + 1] : 0);
		if ((r[i] - l[i] + 1) * k < need) {
			puts("-1");
			return 0;
		}
		dp[i] = need - (r[i] - l[i]) * k;
		if (dp[i] < 0) dp[i] = 0;
	}
	ll ans = 0, cur = k;
	for (int i = 1; i <= n; ++i) {
		if (cur < dp[i]) { // 必须换弹夹了
			ans += cur;
			cur = k;
		}
		ans += a[i];
		cur = ((cur - a[i]) % k + k) % k;
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：睿智的憨憨 (赞：4)

## CF1430F 解题报告

### 原题链接

http://codeforces.com/problemset/problem/1430/F

### 题目大意

你有一把枪，这把枪的弹夹量为 $k$ 发，并且刚开始弹夹是满的。每次换弹都需要 $1$ 单位时间，丢弃目前弹夹里的全部子弹并将弹夹装满。你的射击技术十分高超，可以不耗费任何时间射出 $1$ 发子弹并消灭一个敌人。现在有 $n$ 波攻势，第 $i$ 波有 $a_i$ 个敌人，出现时间为 $[l_i, r_i](r_i \le l_{i+1})$。你需要在保证消灭所有敌人的条件下，让使用的子弹最少（使用的子弹数 $=$ 消灭敌人的子弹数 $+$ 丢弃的子弹数）。注意，在最后一波攻势结束后，不丢弃弹夹中剩余的子弹。

### 解法分析

消灭敌人的子弹数是确定的，所以我们只需让丢弃的子弹数尽可能小。那么我们就可以得结论 $1$。

结论 $1$：当我们 **没必要** 换弹夹时，不换弹夹比换弹夹更优。

问题来了，"没必要"的含义是什么呢？

假设你在第 $i$ 波攻势开始时弹夹中有 $p$ 发子弹，并且可以在第 $i \sim n$ 波中消灭所有的敌人，那么就称这种情况为 **没必要换弹** 。

这时我们贪心算法的大致思路就出来了：用 $ans$ 记录已经使用的子弹，$now$ 记录现在弹夹里还有多少子弹。如果必须换弹就换弹，然后更新 $now$ 和 $ans$ 的值。到这里，我们只需解决在某个回合开始前是否必须换弹即可。

注意到在每个回合开始前都应该有一个对子弹数的最低要求。不妨设当第 $i$ 波攻势开始时，弹夹中要有至少 $dp_i$ 发子弹，才能消灭之后所有敌人。有一个很关键的条件：$r_i \le l_{i+1}$，接下来我们将围绕这个条件分类讨论。

若 $r_i < l_{i+1}$：则 $dp_i$ 与 $dp_{i+1}$ 无关（你可以在 $ (r_i,l_{i+1}]$ 内做好充分的准备）。那么根据 $a_i$ 就能算出 $dp_i$ 的值。

若 $r_i = l_{i+1}$：这时 $dp_i$ 就和 $dp_{i+1}$ 息息相关了。产生瓜葛的原因在于两个区间有重复的时间点 $r_i$。我们的获胜条件是 **每波敌人都必须在出现时间内被全部消灭**，这意味着我们两波敌人都不能放弃。如果第 $i$ 波敌人能在 $[l_i,r_i)$ 内消灭，那么问题就等价于上面的讨论。如果第 $i$ 波敌人必须到 $r_i$ 才能被全部消灭，由于这两波是连在一起的，所以没有任何准备时间，我们必须在 $r_i$ 消灭完第 $i$ 波敌人后弹夹中仍然留有 $dp_{i+1}$ 发子弹才能保证胜利。

由于 $dp_i$ 只可能与 $dp_{i+1}$ 的特性，我们从后到前 DP。然后再从前往后按照上面的方法贪心一遍，就可以求出答案。（注意刚开始弹夹是满的，但并不意味着需要全部使用，即样例 4）。

最后贴上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, K, l[2010], r[2010], a[2010], dp[2010], now, ans;
signed main(){
	cin >> n >> K;
	for (int i = 1; i <= n; i++)
		cin >> l[i] >> r[i] >> a[i];
	for (int i = n; i >= 1; i--){
		int need = a[i] + (r[i] == l[i + 1] ? dp[i + 1] : 0);
		if (K * (r[i] - l[i] + 1) < need){
			cout << "-1\n";
			return 0;
		}
		dp[i] = max(0ll, need - K * (r[i] - l[i]));
	}
	now = K, ans = 0;
	for (int i = 1; i <= n; i++){
		if (now < dp[i]){
			ans += now;
			now = K;
		}
		ans += a[i];
		now -= a[i] % K;
		if (now < 0)
			now += K;
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：syzf2222 (赞：4)

这篇题解其实是对 @ 王鲲鹏 大佬的题解做注解。

你考虑若不必要则重新装弹一定不优，如果我们已知每次开始时至少需要多少子弹，我们就可以一遍扫得出答案。

现在我们定义 $dp_i$ 为第 $i$ 个往后能成功至少需要的子弹数量。

你发现我们在这段时间内最多打出 $dp_i+(r_i-l_i)k$ 这么多个子弹（$l_i$ 时要用来打 $dp_i$），但是我们要打 $a_i$ 个怪物，如果 $r_i=l_{i+1}$ 我们还要负责提供下一次需要的子弹（没有时间换弹） $dp_{i+1}$，于是就有 $dp_i=\max(a_i+[r_i=l_{i+1}]dp_{i+1}-(r_i-l_i)k,0)$

然后我们扫一遍，该换弹夹时换就好了。时间复杂度 $O(n)$

代码借鉴了上述那位大佬，请多包涵。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,l[maxn],r[maxn],a[maxn],dp[maxn];
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		l[i]=read(),r[i]=read(),a[i]=read();
	for(int i=n;i>=1;i--){
		int nd=a[i]+(l[i+1]==r[i]?dp[i+1]:0);
		if(nd>(r[i]-l[i]+1)*m)return puts("-1")&0;
		dp[i]=max(0ll,nd-(r[i]-l[i])*m);
	}
	int ans=0,cur=m;
	for(int i=1;i<=n;i++){
		if(cur<dp[i])ans+=cur,cur=m;
		ans+=a[i];cur=(cur-a[i]%m+m)%m;
	}printf("%lld\n",ans);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：Thaumaturge (赞：3)

这题似乎是有$O(n)$做法的。。。当然$O(n^2)$也能过就是了。

贪心不太好做。

~~其实是不会贪心~~

考虑一个最暴力的$dp$。设$f[n][m]$表示递推到第$n$项，剩余$m$颗子弹所需要耗费的子弹，与已经丢弃掉的子弹。

这个$dp$看似有$O(nk)$项，但是仔细分析一下，可以发现：对于一个状态$f[i][j]$，转移只有两种可能。要么用这$j$个子弹打完第$i$波怪物后，重新装弹；要么不重新装弹，继续使用剩下的子弹攻击。这样只会转移到$f[i+1][J]$与$f[i+1][K]$。$J$可以方便地计算出来。

所以每次递推只会多产生$1$种状态，总状态就是$O(n^2)$，复杂度$O(n^2logn)$。

```cpp
/*************************************************************************
	> File Name: f.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年10月11日 星期日 16时52分34秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 2010
#define int long long
#define fi first
#define se second

using namespace std;

const int inf=0x1f3f3f3f3f3f3f3f;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,K,cnt,pre,fans;

struct data{
	int l,r,val;
	data(const int X=0,const int Y=0,const int Z=0):l(X),r(Y),val(Z){}
}a[N],B;

map<int,int> f[N],Q;

bool cmp(const data &x,const data &y){return x.l==y.l?x.r<y.r:x.l<y.l;}

inline void Input(){
	n=read(),K=read();
	for(re int i=1;i<=n;++i){
		B.l=read(),B.r=read(),B.val=read();
		if(B.l==B.r)	Q[B.l]+=B.val;
		else			a[++cnt]=B;
	}
	for(auto i:Q){
		a[++cnt]=data(i.fi,i.fi,Q[i.fi]);
	}
	sort(a+1,a+cnt+1,cmp);
	n=cnt;
	return;
}

inline void solve(){
	f[0][K]=0;
	int now;
	for(re int i=1;i<=n;++i){
		pre=i-1;
		f[i][K]=inf;
		for(auto J:f[pre]){
			int j=J.fi,V=J.se;
			if(V==inf) continue;
			if(j+(a[i].r-a[i].l)*K<a[i].val) continue;
			if(j>=a[i].val){
				if(f[i].find(j-a[i].val)==f[i].end())
				f[i][j-a[i].val]=inf;
				f[i][j-a[i].val]=min(f[i][j-a[i].val],V+a[i].val);
				if(a[i+1].l!=a[i].l)
				f[i][K]=min(f[i][K],V+j);
				continue;
			}
			now=(K-(a[i].val-j)%K)%K;
			if(f[i].find(now)==f[i].end()) f[i][now]=inf;
			if(j+max(0ll,a[i].r-a[i].l-1)*K>=a[i].val || a[i+1].l!=a[i].r){
				if(a[i+1].l!=a[i].l)
				f[i][K]=min(f[i][K],V+now+a[i].val);
				f[i][now]=min(f[i][now],V+a[i].val);
			}
			else{
				f[i][now]=min(f[i][now],V+a[i].val);
			}
		}

		/*printf("%lld\n",i);
		for(auto J:f[i]) printf("%lld %lld\n",J.fi,J.se);*/
		if(f[i].empty()) return puts("-1"),void();
		pre=i;
	}

	fans=inf;
	for(auto i:f[n])	fans=min(fans,f[n][i.fi]);
	if(fans==inf)		return puts("-1"),void();
	cout<<fans<<endl;
	return;
}

signed main(){
	//freopen("data.in","r",stdin);
	Input();
	solve();
	return 0;
}
```


---

## 作者：_YangZJ_ (赞：2)

考虑暴力 $\text{dp}$，设 $f_{i,j}$ 表示打完了前 $i$ 波怪物，目前弹匣剩余 $j$ 发子弹的最少子弹数。

状态数 $O(nk)$ 的，转移可以做到 $O(1)$，无法通过。

考虑优化状态，我们发现假设进入第 $i$ 段的时候子弹数为 $0$，需要 $x$ 个弹匣正好干完怪物。那么 **在任何状态中，在第 $i$ 段换弹次数 $\in[x-1,x+1]$**（之前剩余了一些子弹，可以少打一次或者可以加满子弹进入下一段）。

有了这个性质，我们发现只考虑满弹进入的哪些段，因为中间其余段的换弹次数固定了。

设 $f_i$ 表示满弹进入 $i$ 的最小代价，转移从小到大枚举下一个满弹进入的段 $j$，那么 $[i,j)$ 这一段的换弹次数容易计算，复杂度 $O(n^2)$。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 2005, P = 1e9+7;
const ll inf = 0x3f3f3f3f3f3f3f3f;

inline int read() {
	int x = 0, w = 0; char ch = getchar(); while(!isdigit(ch)) w |= (ch=='-'), ch = getchar();
	while(isdigit(ch)) x = (x*10)+(ch^48), ch=getchar(); return w?-x:x;
}

int n, k, a[N], l[N], r[N];
ll f[N], ans = inf;

signed main() {
	n = read(); k = read();
	for(int i = 0; i <= n + 1; i++) f[i] = inf;
	f[0] = 0; l[0] = r[0] = -1; a[0] = k;
	for(int i = 1; i <= n; i++) l[i] = read(), r[i] = read(), a[i] = read();
	for(int i = 0; i <= n; i++) if(f[i] < inf) {
		ll res = k, sum = 0, c;
		for(int j = i, c; j <= n; j++) {
			c = a[j] > res ? (a[j] - res - 1) / k + 1 : 0;
			if(c > r[j] - l[j]) break; 
			sum += c; res = res + 1ll * c * k - a[j];
			if(j == n) ans = min(ans, 1ll * k * (f[i] + sum) - res);
			if(c + l[j] < l[j + 1]) f[j + 1] = min(f[j + 1], 1 + f[i] + sum);
		}
	}
	cout << (ans == inf ? -1 : ans) << endl;
	return 0;
}
```



---

## 作者：ifffer_2137 (赞：1)

感动，很难在 \*2600 找到这么小清新的 DP 了。
### 题意
一把枪弹夹容量为 $k$，处理 $n$ 组怪，第 $i$ 组在时间轴 $[l_i,r_i]$ 出现，有 $a_i$ 只。一发子弹可击杀一怪，不耗时间；换弹需把弹夹和里面所有子弹扔掉，装上一个装满 $k$ 发子弹的弹夹，耗时 $1$ 单位。求在击杀所有怪的前提下最少耗弹量（打出去的加上扔掉的），或报告无解。
### 分析
容易发现的是在当前场上有怪且有子弹的时候我们再换弹是不优的，要么先把里面的打完，要么提前扔掉残缺的弹夹换满。这个感性理解一下就好。

观察数据范围提示设计 $O(n^2)$ 的算法，可以想到是 DP。

发现一直把枪里子弹打完再换的情况是可以暴力模拟的，于是我们考虑将丢弃残缺弹夹换成满弹夹的情况设进 DP 状态里。设 $dp_i$ 表示满弹夹进入第 $i$ 组怪，一直打到结束的最少耗弹量，注意这样需要倒过来转移。然后直接枚举下一个满弹夹进入的位置，两者中间的部分暴力模拟即可求出剩下多少残弹，然后直接转移。

注意组与组之间是有可能边界重合的，于是在转移的时候判断一下新一组之前有没有时间扔掉残弹换弹夹。
### 代码
代码非常短，~~就像今年 CSP-S 上把我干爆了的 T3 一样~~。

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e3+5;
int n,k;
int l[maxn],r[maxn],a[maxn];
int dp[maxn];
signed main(){
	#ifndef ONLINE_JUDGE
		assert(freopen("data.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	memset(dp,0x3f,sizeof(dp));
	n=read(),k=read();
	for(int i=1;i<=n;i++) l[i]=read(),r[i]=read(),a[i]=read();
	l[n+1]=inf;
	for(int i=n;i>=1;i--){
		int val=0,cur=k;
		for(int j=i;j<=n;j++){
			int cnt=(a[j]-cur+k-1)/k+1;
			if(cnt>r[j]-l[j]+1) break;
			val+=a[j];
			cur=(cur-a[j]%k+k)%k;
			if(r[j]<l[j+1]||cnt<r[j]-l[j]+1){
				if(j<n) dp[i]=min(dp[i],dp[j+1]+val+cur);
				else dp[i]=min(dp[i],val);
			}
		}
	}
	if(dp[1]<inf) cout<<dp[1]<<'\n';
	else cout<<-1<<'\n';
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

主打一个 DP 和贪心。

# First 有解

有解的话，每只怪都要打，所以 $ans$ 先加上 $a_i$。那么其他的就是换弹带来的附加值，所以能不换弹就不换。

考虑什么时候一定要换弹。我们可以 DP 一下每一波要至少花费多少弹药。可以发现，每一波的怪都和后一波有关，所以从后往前推，一共花费了多少弹药。

```cpp
for (int i = n; i >= 1; i--){
	ll p = a[i];
	if (r[i] == l[i + 1]) p += f[i + 1];
	if ((r[i] - l[i] + 1) * k < p) return 0 & puts("-1");
	f[i] = max(0ll, p - (r[i] - l[i]) * k);
}
```

在这里，我们就直接处理了无解。

然后贪心，能不换就不换，如果当前弹药不够支持这一波打完，就换。

# Second 无解

上面代码中的 $p$ 就是这一波要用多少弹药，如果就算装满弹夹也不够用，就无解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, k, a[2005], l[2005], r[2005], ans, f[2005], ok;
int main(){
	scanf ("%lld %lld", &n, &k);
	for (int i = 1; i <= n; i++){
		scanf ("%lld %lld %lld", &l[i], &r[i], &a[i]);
		ans += a[i];
	}
	for (int i = n; i >= 1; i--){
		ll p = a[i];
		if (r[i] == l[i + 1]) p += f[i + 1];
		if ((r[i] - l[i] + 1) * k < p) return 0 & puts("-1");
		f[i] = max(0ll, p - (r[i] - l[i]) * k);
	}
	ok = k;
	for (int i = 1; i <= n; i++){
		if (ok < f[i]) ans += ok, ok = k;
		ok = ((ok - a[i]) % k + k) % k;
		
	}
	printf ("%lld", ans);
	return 0;
}

```

---

