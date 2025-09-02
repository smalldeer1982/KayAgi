# Monsters And Spells

## 题目描述

Monocarp is playing a computer game once again. He is a wizard apprentice, who only knows a single spell. Luckily, this spell can damage the monsters.

The level he's currently on contains $ n $ monsters. The $ i $ -th of them appears $ k_i $ seconds after the start of the level and has $ h_i $ health points. As an additional constraint, $ h_i \le k_i $ for all $ 1 \le i \le n $ . All $ k_i $ are different.

Monocarp can cast the spell at moments which are positive integer amounts of second after the start of the level: $ 1, 2, 3, \dots $ The damage of the spell is calculated as follows. If he didn't cast the spell at the previous second, the damage is $ 1 $ . Otherwise, let the damage at the previous second be $ x $ . Then he can choose the damage to be either $ x + 1 $ or $ 1 $ . A spell uses mana: casting a spell with damage $ x $ uses $ x $ mana. Mana doesn't regenerate.

To kill the $ i $ -th monster, Monocarp has to cast a spell with damage at least $ h_i $ at the exact moment the monster appears, which is $ k_i $ .

Note that Monocarp can cast the spell even when there is no monster at the current second.

The mana amount required to cast the spells is the sum of mana usages for all cast spells. Calculate the least amount of mana required for Monocarp to kill all monsters.

It can be shown that it's always possible to kill all monsters under the constraints of the problem.

## 说明/提示

In the first testcase of the example, Monocarp can cast spells $ 3, 4, 5 $ and $ 6 $ seconds from the start with damages $ 1, 2, 3 $ and $ 4 $ , respectively. The damage dealt at $ 6 $ seconds is $ 4 $ , which is indeed greater than or equal to the health of the monster that appears.

In the second testcase of the example, Monocarp can cast spells $ 3, 4 $ and $ 5 $ seconds from the start with damages $ 1, 2 $ and $ 3 $ , respectively.

In the third testcase of the example, Monocarp can cast spells $ 4, 5, 7, 8 $ and $ 9 $ seconds from the start with damages $ 1, 2, 1, 1 $ and $ 2 $ , respectively.

## 样例 #1

### 输入

```
3
1
6
4
2
4 5
2 2
3
5 7 9
2 1 2```

### 输出

```
10
6
7```

# 题解

## 作者：feicheng (赞：9)

# CF1626C Solution

## [Description](https://www.luogu.com.cn/problem/CF1626C)

有 $n$ 个怪物，对于第 $i$ 个怪物，你需要在第 $k_i$ 秒打死它，它的血量值为 $h_i$。

第一秒时你的法术攻击力为 $1$，对第 $z$ 秒时，如果在第 $z-1$ 秒你没有释放法术，那么你的攻击力为 $0$，若释放了，假设在 $z-1$ 秒时法术攻击力为 $x$，则这一秒你的法术可以变为 $x+1$ 或 $1$。

释放一个攻击力为 $x$  的法术需要消耗 $x$ 法力，你需要在打死所有怪物的前提下，最小化法力消耗。

多测。

$1\le t\le 10^4$，$1\le n\le 100$，$1\le \sum n\le 10^4$，$1\le h_i\le k_i\le 10^9$。保证 $k_i$ 升序给出。

## Solution

容易发现对于两个怪物之间可以增加的伤害值为 $\Delta k=k_i-k_{i-1}$，如果下一个怪物的生命值 $h_i\le \Delta k$，那么可以直接在这一轮伤害变为 $1$，否则需要保持上一轮的伤害不变。

但是这样子是有缺陷的：

考虑如下数据

```
1000000 1000001 1000002
1000000 1 1000001
```

这样子的话在第二个怪向第三个怪转的时候就没有足够的伤害去打了。

所以我们发现**一个时间点需要达到的法力值是和之后的怪物的生命值相关的**，换言之，设 $f_i$ 表示到第 $i$ 个怪物时需要的法力值，则 $f_i=\max\{h_i,f_{i+1}-\Delta k\}$。

对第 $m$ 个怪物，考虑对 $f_m-d$ 分类讨论（$d$ 为在第 $m-1$ 个怪物时的伤害）。
1. $f_m-d\leq k_m-k_{m-1}$：此时可以将伤害变为 $1$，因为可以增加到 $f_m$，产生了 $\dfrac{f_m\times (f_m+1)}{2}$ 的花费。

2. 反之，这时伤害不能归 $1$，产生了 $\dfrac 1 2(2d+\Delta k)\times \Delta k$ 的花费。

于是我们在 $\Theta\left(\sum n\right)$ 的时间复杂度解决了这个问题。


## Code

```cpp
// Author:Feicheng

/* -------- Main part of the Program--------*/

#include <bits/stdc++.h>

using std::cin;
using std::cout;

constexpr int N = 110;

int n, T;
long long h[N], k[N], f[N];

inline void clear() {
  memset(h, 0, sizeof h);
  memset(k, 0, sizeof k);
  memset(f, 0, sizeof f);
}

inline long long calc(long long st, long long ed, long long num) {
  return  (st + ed) * num / 2ll;
}
inline void solve() {
  clear();
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> k[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> h[i];
  } 
  f[n] = h[n];
  for (int i = n - 1; i >= 1; --i) {
    auto delta = k[i + 1] - k[i];
    f[i] = std::max(f[i + 1] - delta, h[i]);
  }
  long long ans = calc(1, f[1], f[1]), d = f[1];
  // cout << ans << '\n';
  for (int i = 1; i < n; ++i) {
    auto delta = k[i + 1] - k[i];
    if (f[i + 1] <= delta) {
      ans += calc(1, f[i + 1], f[i + 1]);
      d = f[i + 1];
    }
    else {
      ans += calc(d + 1, d + delta, delta);
      d += delta;
    }
  }
  cout << ans <<  '\n';
}

int main(int argc, const char** argv) {
#ifdef Feicheng
  freopen("input.in", "r", stdin);
  freopen("output.ans", "w", stdout);
#endif 
  std::basic_ios<char>::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> T;
  for (; T; --T) {
    solve();
  }
  return 0;
} 
```

---

## 作者：_Diu_ (赞：5)

[luogu 传送门](https://www.luogu.com.cn/problem/CF1626C)

[cf 传送门](https://codeforces.com/contest/1626/problem/C)

## 题目大意

有 $n$ 个怪兽，第 $i$ 个怪兽在第 $k_i$ 秒出现，血量为 $h_i$，你可以在每一秒提升战斗力，假设你上一秒的战斗力是 $x$，那么你这一秒战斗力可以选择 $x+1$ 或 $1$ 或 $0$。你要保证对于每个怪兽，在第 $k_i$ 秒时，战斗力至少是 $h_i$。每一秒消耗的魔力就是那一秒的战斗力，求能够打败所有怪兽所消耗的魔力值最小值。

## 思路

对于一个怪兽，如果要在第 $k_i$ 秒战斗力达到 $h_i$，那么你就至少在第 $k_i-h_i+1$ 秒开始积累战斗值。

这样我们可以记一个怪兽转换为要求占用的区间 $[k_i-h_i+1,k_i]$。

显然对于一个区间 $[l,r]$，这个区间的魔力值消耗就是 $1+2+3+\dots+(r-l+1)=(r-l+1)(r-l+2)/2$。

那么，如果两个区间相交了，会发生什么事呢？

假设两个区间 $[l_1,r_1],[l_2,r_2]$ 有相交。

那么，在第 $r_1$ 秒的时间你的战斗力已经是一个很大的数了，而又无法在此时重新积累战斗力，不然就打败不了第二个怪兽，所以战斗力要继续累积。

因此我们可以这两个区间的魔力值最小消耗就等价于合并成一个大区间。

包含的情况也是一样。

所以我们只需要把这些区间合并成若干个区间，然后再统计每个区间的答案即可。

这一题的 $n$ 奇小，所以每次合并暴力把一个区间删掉都可以。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
int t,n,h[N],k[N];
struct cxk{
	int l,r;
}e[N];
bool cmp(cxk a,cxk b){//保证每次两个有重叠的区间排完序之后是相邻的，当然直接暴力比较好像也可以
	if(a.l^b.l)return a.l<b.l;
	return a.r>b.r;
}
void del(int x){
	for(int i=x;i<n;i++)e[i]=e[i+1];
	--n;
}
signed main(){
	scanf("%lld",&t);
	for(;t--;){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&k[i]);
		for(int i=1;i<=n;i++){
			scanf("%lld",&h[i]);
			e[i]={k[i]-h[i]+1,k[i]};
		}
		sort(e+1,e+n+1,cmp);
		int ans=0,hei=0;
		for(int i=2;i<=n;i++){
			if(e[i].l<=e[i-1].r)e[i-1].r=max(e[i-1].r,e[i].r),del(i),--i;
		}
		for(int i=1;i<=n;i++)ans+=(e[i].r-e[i].l+1)*(e[i].r-e[i].l+2)/2;
		printf("%lld\n",ans);
	}
}
```

---

## 作者：daniEl_lElE (赞：2)

## 题目描述

有 $n$ 个怪兽，第 $i$ 个怪兽出现的时间是 $k_i$，血量 $h_i$。

其中，满足 $h_i\leq k_i$。

每一秒我们的主角可以对怪兽造成 $x$ 点伤害。$x$ 可以是 $0$ 或 $1$，同时若上一秒攻击了且造成了 $y$ 点伤害，$x$ 可以是 $y+1$。

求主角至少攻击多少点伤害才能让每一个怪兽在刚出现的那一秒把它攻击死。

## 解法

首先，我们考虑如果要在 $k_i$ 时间造成 $h_i$ 点伤害，我们必须要从 $k_i-h_i+1$ 秒开始就要连续使得每一秒的伤害比上一秒多 $1$。那么在从 $k_i-h_i+1$ 到 $k_i$ 这整一段时间内都是将  $x$ 变成 $y+1$。

考虑差分，在 $k_i-h_i+1$ 差分值设为 $1$，在  $k_i$ 差分值设为 $-1$，从头 `sort` 一遍（按照点的顺序）。我们每次记录一下开始节点，然后往后差分，直到差分值再一次变为 $0$，将后来这个节点减去开始节点加 $1$，算一个等差数列求和即可。复杂度 $\Theta(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct cf{
	int tp,plc;
};
bool cmp(cf a,cf b){
	if(a.plc!=b.plc) return a.plc<b.plc;
	else return a.tp>b.tp;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1],b[n+1],sum=0;
		cf c[2*n+1];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			c[i].plc=a[i]-b[i]+1; c[i].tp=1;
			c[i+n].plc=a[i]; c[i+n].tp=-1;
		}
		sort(c+1,c+2*n+1,cmp);
		for(int i=1;i<=2*n;i++){
			int now=1;
			int st=c[i].plc;
			while(now>0){
				i++;
				now+=c[i].tp;
			}
			int ed=c[i].plc;
			int dist=ed-st+1;
			sum+=(dist*(dist+1)/2);
		}
		cout<<sum<<endl;
	}
	return 0;
}
/* things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=1,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <= , - or =
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. if you don't know where the bug is , try to clear some parts of the code
 and check each part seperately.
13. ...
*/

```

---

## 作者：Argon_Cube (赞：1)

* **【题目链接】**

[Link:CF1626C](https://www.luogu.com.cn/problem/CF1626C)

* **【解题思路】**

显然如果要击败一个怪物，那么就必须至少在一段区间内连续攻击。如果两个区间有交叠，那么显然在这两个区间的并内要连续攻击。那么，我们把每一个怪物转化成前文所说的区间，然后如果有交叠就合并。

合并完后，里面攻击的总消耗直接用等差数列求和即可。记得开`long long`。

* **【代码实现】**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

array<int,100> timeps,healths;
vector<pair<int,int>> ranges;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		ranges.clear();
		int cnt,last_t=0,last_h=0,cur,cur_t,cur_h;
		long long ans=0;
		cin>>cnt;
		for(int i=0;i<cnt;i++)
			cin>>timeps[i];
		for(int i=0;i<cnt;i++)
			cin>>healths[i];
		for(int i=0;i<cnt;i++)
			ranges.push_back(make_pair(timeps[i]-healths[i]+1,timeps[i]));
		sort(ranges.begin(),ranges.begin()+cnt);
		for(int i=0;i<ranges.size()-1;i++)
			if(ranges[i+1].first<=ranges[i].second)
				ranges[i].second=max(ranges[i+1].second,ranges[i].second),ranges.erase(ranges.begin()+i+1),--i;
		for(int i=0;i<ranges.size();i++)
		{
			long long len=ranges[i].second-ranges[i].first+1;
			ans+=len*(len+1)/2;
		}
		cout<<ans<<'\n';
	}
	return 0;
}


```

---

## 作者：Aw顿顿 (赞：0)

解题核心在于，能不能将朴素的贪心算法转化为在全局适用的策略。空谈有些难懂，不妨先看看朴素做法。

## 朴素做法

对于每两个相邻的怪 $i,j$，如果他们之间的距离 $dis(i,j)=k_j-k_i$ 足够我们从 $1$ 发育到 $h_j$，那此时可以归零，这一段的贡献就是等差数列求和：

$$1+2+3+\cdots+h_j=\dfrac{(1+h_j)h_j}{2}$$

而如果需要继续发育不能从头再来，就进行另一段等差数列求和即可，稍有麻烦这里先不写。

总之，这个方法是有缺陷的，当我们在判断 $i$ 到 $i+1$ 的过程中可以归零，我们不能断定从 $i+1$ 到 $i+2$ 的过程一定能够发育到期望结果，这一点在@\_Alejandro\_ 所举的例子中得到了很好的体现。

如果不采用这种策略，由于题目所给的 $\forall i\in[1,n]\ \exists\ h_i\le k_i$，我们可以保证在不归零的情况下，能够杀死 $h_i$ 就一定能够杀死 $h_j$，易证，此处不表。

## 全局适用

那么对这个式子进行优化，要求我们对于未来多步的情况进行考虑，具体地，对于未来所有的情况进行综合以判断当前是否归零。然而容易发现，顺序处理是 $n^2$ 级别的，难以接受，由于每一个节点都会用到后续所有怪的信息，不妨从后往前处理。因为整个过程都要使用，所以预处理一下好。

$$dp_i=\max\{h_i,dp_{i+1}-(k_{i+1}-k_i)\}$$

解释一下这个式子是什么意思。就是说，每一步都得考虑 $dp_{i+1}$ 能不能打倒，也就是说能否保证杀死之后的所有的怪。正确性显然，考虑贡献：

- 归 $1$ 之后贡献就是 $\frac{1}{2}dp_i(dp_i+1)$
- 保留就是 $\frac{1}{2}(2x+k_{i+1}-k_i)(k_{i+1}-k_i)$

$x$ 就是在 $i-1$ 处的攻击力。很容易发现这是对的。我们接下来考虑如何进行判断。判断也是容易的，考虑一下 $dp_i-x$ 和发育时间的关系就好了。

## 代码

给出代码：https://paste.ubuntu.com/p/8xWTbZBBs3/

---

鉴于有些同学查看 Pastebin 代码不方便，此处给出源码：

```cpp
#include <bits/stdc++.h>
#define N 105
#define int long long
using namespace std;
int n,T,h[N],k[N],dp[N];
void init(int n){
	for(int i=1;i<=n;i++)
		h[i]=k[i]=dp[i]=0;
}signed main(){
	scanf("%lld",&T);
	while(T--){
  		scanf("%lld",&n);init(n);
  		for(int i=1;i<=n;i++)scanf("%lld",k+i);
  		for(int i=1;i<=n;i++)scanf("%lld",h+i);
  		dp[n]=h[n];
		for(int i=n-1;i>0;i--)
			dp[i]=max(h[i],dp[i+1]-(k[i+1]-k[i]));
		int res=(1+dp[1])*dp[1]/2ll,x=dp[1];
		for(int i=1;i<n;i++){
			if(dp[i+1]<=(k[i+1]-k[i])){
				res+=(1+dp[i+1])*dp[i+1]/2ll;
				x=dp[i+1];//已经归零 
			}else{
				res+=(2*x+1+(k[i+1]-k[i]))*(k[i+1]-k[i])/2ll;
				x=x+(k[i+1]-k[i]);//归不动
			}
		}printf("%lld\n",res);
	}return 0;
} 
```


---

## 作者：xia0ji233 (赞：0)

### Problem Description

有 $n$ 个敌人，你需要在第 $k_i$ 秒用至少 $h_i$ 的攻击力打败这个敌人。

攻击力的计算方式如下：

1.  第一秒时，你有 $1$ 攻击力
2.  对于后面的任意一秒，若前一秒你的攻击力为 $x$，则这一秒你的攻击力可以为 $x+1$ 或 $1$

一秒内，如果你的攻击力为 $x$，则你就需要消耗 $x$ 的能量。

请问，在你打败所有敌人的情况下，最少需要消耗多少能量。

## 题目分析

在一秒内，你可以继承之前的攻击力，但是继承攻击力的代价就是你要花费相当于继承之后攻击力的法力值来保存你的攻击力。只有当前攻击力大于当前出现的怪物的血量的时候，你才能杀死他。在任意一秒，你可以选择摆烂，但是摆烂的代价就是会丢失上一秒的攻击力，使你在下一秒的时候无法有之前那么高的攻击，摆烂可以选择从 $0$ 开始或者从 $1$ 开始。显然可以发现，当 $k_i\ge h_i$ 的时候，主角总是有办法杀死所有的怪物的。 

在杀死所有的怪物的怪物下要保证消耗的法力值最少，那就需要我们合理分配增加攻击的时间了。我们不难得出以下结论：

如果在第 $k_i$ 秒遇到了血量为 $h_i$ 的怪物，那么在 $(k_i-h_i,k_i]$ 的时间区间内，我不能出现摆烂的情况，即攻击力不能掉，在 $k_i-h_i$ 的时刻，攻击力不能减为 $0$。

那么第 $i$ 个怪物需要我花费的最少法力值就是从 $1$ 到 $h_i$ 的等差数列，假设我打完怪物之后我都能立刻摆烂，那么不难得出总法力消耗就是 $\sum _{i=1}^{n} \sum _{j=1}^{h_i} j$ 。但是并不是每一次打完怪物我都能摆烂，如果我摆烂到 $0$，剩下的时间不足以我积攒足够的攻击去击杀接下来的怪物那就不能摆烂而是接着蓄力。

对于每一个怪物我们都构造一个区间，区间范围为 $[k_i-h_i+1,k_i]$ ，当区间出现相交，则合并两个区间，最后根据区间长度计算法力值即可。

对于每一个区间我观察我的左端点是否会落在上一个区间内，如果在，则需要合并前面的区间，因为我们默认按照 $k_i$ 排序了，也就是按照区间右端点值排序，所以我可以用 $\text{lower\_bound}$ 来寻找合并的区间。因为如果最后一个怪物它要求我从第一秒开始蓄力的话，那么前面的所有区间我都要合并，所以这里必须考虑合并的区间。对于合并的区间我们修改 $l$ 为其中最小值，$r$ 为其中最大值。然后在计算区间的时候特判一下连续的区间是否相等，达到只计算一次的目的即可。

### 标程

```cpp
#include<bits/stdc++.h>
#define maxn 105
using namespace std;
int h[maxn],k[maxn],l[maxn],r[maxn];
void solve(){
	int n;
	cin>>n;
	memset(l,0,sizeof(l));
	memset(r,0,sizeof(l));
	for(int i=1;i<=n;i++)cin>>k[i];
	for(int i=1;i<=n;i++)cin>>h[i];
	for(int i=1;i<=n;i++){
		l[i]=k[i]-h[i]+1;
		r[i]=k[i];
	}
	
	for(int i=1;i<=n;i++){
		if(l[i]<=r[i-1]){
			int j=i;
			int p=lower_bound(r+1,r+1+i,l[i])-r;
			//if(p==0)p++;
			for(int j=p;j<=i;j++){
				l[j]=min(l[p],l[i]);
				r[j]=r[i];
			}
		}
	}


	long long ans=0;
	for(int i=1;i<=n;i++){
		if(l[i]==l[i-1]&&r[i]==r[i-1])continue;
		int num=r[i]-l[i]+1;
		ans+=1ll*(num+1)*num/2;
		if(l[i]-r[i-1]>1&&l[i-1]!=0){
			;//ans+=l[i]-r[i-1]-1;
		}
	}
	cout<<ans<<endl;
}

int main(){
	//freopen("1.in","r",stdin);
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```



---

## 作者：Land_ER (赞：0)

## 题意简述
- 给定数列 $k_1,k_2,...,k_n$ 和 $h_1,h_2,...,h_n$，并且有 $1 \leqslant h_i \leqslant k_i \leqslant 10^9$。
- 将 $k_1,k_2,...,k_n$ 看做数轴上的点，你可以选定数轴上的一些不重叠的区间 $[l,r]$，使得有 $k_i - l + 1 \geqslant h_i \forall i \in [1,n]$。
- 选取每个区间的代价是 $\sum_{i = 1}^{r-l+1} i$，你要使总代价尽可能小，并输出最小的代价。
- 给出的数据保证有解。

## 解题思路
我们采用贪心的思想。

首先，我们可以得知：对于每个点 $k_i$，必定有区间 $[k_i - h_i + 1,k_i]$ 被选取。

同时我们知道，选取区间的代价只与区间的长度 $(r-l+1)$ 有关，因此，选取的区间越短，总代价越小。

考虑如何使区间的长度更短：
- 当区间没有重叠时，直接选取必须选取的区间。
- 当区间存在重叠时，就把两个区间合并。

这么做的正确性：
- 要求中的 $k_i - l + 1$ 可以看做是区间 $[l,k_i]$ 的长度。
- 开始时对于每个点确定的区间长度就是最短合法的区间长度。
- 合并 $k_i$ 和 $k_{i+1}$ 两个点确定的区间只会增加区间 $[l,k_i]$ 或 $[l,k_{i+1}]$ 的长度（也有可能都不改变），而不能使区间长度减小。

因此这样做是正确的。

## 代码实现
记得开 `long long`

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll max(ll a,ll b){
	return a>b ? a : b;
}
ll sum(ll a,ll b){
	return 1ll * (a+b) * (b-a+1) / 2;
}
int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll t,n,k[105],h[105],m,ans;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1;i <= n;++ i)
			cin >> k[i];
		for(int i = 1;i <= n;++ i)
			cin >> h[i];
		ans = 0,k[0] = 0,m = k[n];
		for(int i = n;i >= 1;-- i){
			if(k[i]-k[i-1] >= h[i]){
				ans += sum(1,m-k[i]+h[i]);//k[i]-h[i]+1 :: m
				m = k[i-1];
			}else
				h[i-1] = max(h[i-1],h[i]-(k[i]-k[i-1]));
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [CF1626C	Monsters And Spells](https://www.luogu.com.cn/problem/CF1626C)

对于每一个怪兽，我们先考虑最优的能量损耗方案，即最晚在哪一时刻开始施法。我们令开始施法的时刻为左端点，怪兽出现的时刻为右端点，这样我们会得到 $n$ 条线段。然后我们求出所有的极长的相交线段。记这样一段线段的左端点为 $l$，右端点为 $r$，每一段极长的相交线段对答案的贡献就是 $(r-l+1) \times (r-l+1+1) / 2$。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=110;
typedef pair<int,int> pii;
int T,n,tot,cnt;
int k[N],h[N];
pii seg[N];
vector<int> a[N];
int l[N],r[N];
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
    scanf("%lld",&T);
    while (T--)
    {
        tot=cnt=0;
        scanf("%lld",&n);
        for (int i=1;i<=n;++i) scanf("%lld",&k[i]);
        for (int i=1;i<=n;++i) scanf("%lld",&h[i]);
        for (int i=1;i<=n;++i) 
        {
            int t=k[i]-h[i]+1;
            seg[++tot]={t,k[i]};
        }
        sort(seg+1,seg+tot+1);
        int last=0;
        for (int i=1;i<=tot;++i)
        {
            if (seg[i].first<=last) a[cnt].push_back(i);
            else 
            {
                r[cnt]=last;
                a[++cnt].push_back(i);
                l[cnt]=seg[i].first;
            }
            last=max(last,seg[i].second);
        }
        r[cnt]=last;
        int ans=0;
        for (int i=1;i<=cnt;++i) ans+=(r[i]-l[i]+1)*(1+r[i]-l[i]+1)/2;
        for (int i=1;i<=cnt;++i) a[i].clear();
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

