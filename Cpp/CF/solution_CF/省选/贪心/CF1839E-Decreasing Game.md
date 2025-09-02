# Decreasing Game

## 题目描述

This is an interactive problem.

Consider the following game for two players:

- Initially, an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ is written on blackboard.
- Game consists of rounds. On each round, the following happens: 
  - The first player selects any $ i $ such that $ a_i \gt 0 $ . If there is no such $ i $ , the first player loses the game (the second player wins) and game ends.
  - The second player selects any $ j \neq i $ such that $ a_j \gt 0 $ . If there is no such $ j $ , the second player loses the game (the first player wins) and game ends.
  - Let $ d = \min(a_i, a_j) $ . The values of $ a_i $ and $ a_j $ are simultaneously decreased by $ d $ and the next round starts.

It can be shown that game always ends after the finite number of rounds.

You have to select which player you will play for (first or second) and win the game.

## 说明/提示

In the first example $ n = 4 $ and array $ a $ is $ [\, 10, 4, 6, 3 \,] $ . The game goes as follows:

- After reading array $ a $ contestant's program chooses to play as the first player and prints "First".
- First round: the first player chooses $ i = 1 $ , the second player chooses $ j = 3 $ . $ d = \min(a_1, a_3) = \min(10, 6) = 6 $ is calculated. Elements $ a_1 $ and $ a_3 $ are decreased by $ 6 $ . Array $ a $ becomes equal to $ [\, 4, 4, 0, 3 \,] $ .
- Second round: the first player chooses $ i = 2 $ , the second player chooses $ j = 1 $ . $ d = \min(a_2, a_1) = \min(4, 4) = 4 $ is calculated. Elements $ a_2 $ and $ a_1 $ are decreased by $ 4 $ . Array $ a $ becomes equal to $ [\, 0, 0, 0, 3 \,] $ .
- Third round: the first player chooses $ i = 4 $ . There is no $ j \neq 4 $ such that $ a_j > 0 $ , so the second player can't make a correct move and the first player wins. Jury's program prints $ j = 0 $ . After reading it, contestant's program terminates.

In the second example $ n = 6 $ and array $ a $ is $ [\, 4, 5, 5, 11, 3, 2 \,] $ . The game goes as follows:

- Contestant's program chooses to play as the second player and prints "Second".
- First round: $ i = 2 $ , $ j = 4 $ , $ a = [\, 4, 0, 5, 6, 3, 2 \,] $ .
- Second round: $ i = 5 $ , $ j = 4 $ , $ a = [\, 4, 0, 5, 3, 0, 2 \,] $ .
- Third round: $ i = 4 $ , $ j = 3 $ , $ a = [\, 4, 0, 2, 0, 0, 2 \,] $ .
- Fourth round: $ i = 6 $ , $ j = 1 $ , $ a = [\, 2, 0, 2, 0, 0, 0 \,] $ .
- Fifth round: $ i = 1 $ , $ j = 3 $ , $ a = [\, 0, 0, 0, 0, 0, 0 \,] $ .
- Sixth round: the first player can't make a correct move and the second player wins. Jury's program prints $ i = 0 $ . After reading it, contestant's program terminates.

Note that the example interaction contains extra empty lines so that it's easier to read. The real interaction doesn't contain any empty lines and you shouldn't print any extra empty lines as well.

## 样例 #1

### 输入

```
4
10 4 6 3


3

1

0```

### 输出

```
First
1

2

4```

## 样例 #2

### 输入

```
6
4 5 5 11 3 2

2

5

4

6

1

0```

### 输出

```
Second 

4

4

3

1

3```

# 题解

## 作者：Lucky_Xiang (赞：5)

# 题目

[CF1839E](https://www.luogu.com.cn/problem/CF1839E)

# 思路

不妨假设一个数变成 $0$ 以后将它删去。

考虑以下几种情况：

1. 如果只有一个数，则先手必胜。
2. 如果只有两个数，
   - 如果两个数相同，则后手必胜。
   - 如果两个数不同，则先手必胜。

而对于每次操作，两个数**减少量相同**。

因此只要能够把原序列划分为两个**总和相同**的子序列，**后手**就能使每个回合结束后得到的两个子序列**总和也相同**（保证他选择的数与先手选的数所属子序列不同即可），一直删除到只剩两个相同的数，从而保证必胜。

那么，如果原序列**不能**被划分为两个总和相同的子序列，是不是在若干次操作后，得到的序列**也不能**被划分为两个总和相同的子序列呢？答案是肯定的，下证明：

> 证明：
>
> 若原序列不能被划分为两个总和相同的子序列，而两人选择了 $x$ 和 $y$（不妨设 $x\leqslant y$），假设操作结束后的序列能够被划分为两个总和相同的子序列，其中 $y-x$ 所在的子序列中其他数之和为 $s_1$，另一个子序列总和为 $s_2$，即 $(y-x)+s_1=s_2$，则在原序列中 $y+s_1=x+s_2$，也可以找出两个总和相同的子序列，与假设矛盾，证毕。

也就是说，如果原序列不能被划分为两个总和相同的子序列，**先手**无论怎么操作都能把序列删除至只剩一个数或两个不同的数，从而保证必胜。

至于如何判断原序列能不能被划分为两个总和相同的子序列，就是一个背包问题了，复杂度 $O(n^3)$。

# 代码

[code](https://codeforces.com/contest/1839/submission/208380092)

---

## 作者：Leasier (赞：2)

- **寻找一方获胜的必要条件。**

注意到每一回合中 $a_i, a_j$ 减少的数是一样的，则后手获胜的一个**必要**条件为初始 $\displaystyle\sum_{i = 1}^n a_i$ 为**偶数**。

- **分析整体过程以获得更强的条件。**

由于我们上面得出来点条件与后手有关，考虑后手获胜时双方的操作序列。

设第 $i$ 轮先手选择 $x_i$，后手选择 $y_i$，则 $\displaystyle\sum x_i = \sum y_i = \dfrac{\displaystyle\sum_{i = 1}^n a_i}{2}$。

由此，我们可以得出后手必胜的一个更强的**必要**条件为存在 $a$ 的子序列 $x'$ 使得 $\displaystyle\sum x'_i = \dfrac{\displaystyle\sum_{i = 1}^n a_i}{2}$。

证明可以考虑把 $x, y$ 中来自同一 $a_i$ 的项放到同一边。

- **尝试说明必要条件是充分的。**

令 $y' = a - x'$，我们可以将 $a$ 中的元素分为在 $x'$ 中的和在 $y'$ 中的，则当前先手所取的元素只可能在 $x', y'$ 之一中。

套路地，考虑策略的对称性。假设先手所取的元素来自 $x'$，若后手所取的元素也来自 $x'$，此后 $\sum x'_i \neq \sum y'_i$，后手必败；否则，此后 $\sum x'_i = \sum y'_i$。

后手这样操作的最终结果是 $x', y'$ 中全是 $0$，此时后手获胜，于是该条件**充分**。

结合必要性，我们得出此为后手获胜的充要条件。

- **考虑先手必胜时的策略。**

不难发现我们可以直接进行任意合法操作直到后手认输。

- **考虑实现。**

对于先手必胜的情况，每次选任意合法项即可。

对于后手必胜的情况，直接背包并记录方案，每次根据先手选的数是否在我们选出的方案中选方案内外的合法项即可。

综上，时间复杂度为 $O(n^2 w)$，其中 $w$ 为值域 $300$。

代码：
```cpp
#include <iostream>
#include <bitset>

using namespace std;

int a[307];
bool dp[90007];
bitset<307> bs[90007];

int main(){
	int n, sum = 0;
	cin >> n;
	dp[0] = true;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		for (int j = sum; j >= 0; j--){
			int t = j + a[i];
			if (dp[j] && !dp[t]){
				dp[t] = true;
				bs[t] = bs[j];
				bs[t][i] = true;
			}
		}
		sum += a[i];
	}
	if (sum % 2 == 0 && dp[sum / 2]){
		sum /= 2;
		cout << "Second" << endl;
		cout.flush();
		while (true){
			int x;
			cin >> x;
			if (x == 0) break;
			for (int i = 1; i <= n; i++){
				if (a[i] > 0 && bs[sum][x] != bs[sum][i]){
					int d = min(a[x], a[i]);
					cout << i << endl;
					cout.flush();
					a[i] -= d;
					a[x] -= d;
					break;
				}
			}
		}
	} else {
		cout << "First" << endl;
		cout.flush();
		while (true){
			int pos, x;
			for (int i = 1; i <= n; i++){
				if (a[i] > 0){
					cout << i << endl;
					cout.flush();
					pos = i;
					break;
				}
			}
			cin >> x;
			if (x == 0) break;
			int d = min(a[pos], a[x]);
			a[pos] -= d;
			a[x] -= d;
		}
	}
	return 0;
}
```

---

## 作者：xs_siqi (赞：1)

首先发现结论：除非存在一种方式，使得序列中所有数相减（绝对值）为 $0$，则后手必胜。否则先手怎么取都必胜。

证明：如果存在一种方式使得上述成立，则当先手选择一个数，我必然能选择另一个数，引导它往我的决策走。

否则无解的情况，我无论如何引导我都不可能赢。

复杂度 $O(n^n)$。

但是考虑到你可以把括号拆掉，得到加号和减号组成的式子。结论变成了：

除非存在一种方式，使得序列中所有数相减或相加（必须存在一个减号）为 $0$，则后手必胜。否则先手怎么取都必胜。

考虑到交换律，爆搜复杂度 $O(2^n)$。

然后可以发现这样一个结论，要使两个最终得到 $0$，则最后必然存在两个数，且相等。

因此可以把它分为两堆。然后你会发现，减法对这两堆是否相等没有影响。

证明：两边减的数一致，无影响。

然后结论变成了：

除非存在一种方式，使得序列中所有数相加后存在两堆相等的数，则后手必胜。否则先手怎么取都必胜。

是不是很熟悉？变成背包了。复杂度 $O(n^3)$。

当然这不是随便背包一下就行了，还要记录如何划分成两个的方案。`bitset` 记录方案即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=305;
bitset<305> st[90005];
int n,a[maxn],f[90005],sum,x,y;
bool vis[maxn];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),sum+=a[i];	
	for(int i=1;i<=n;i++)
		for(int j=sum;j>=a[i];j--){
			if(f[j-a[i]]+a[i]>f[j]){
				f[j]=f[j-a[i]]+a[i];
				st[j].reset();
				st[j]|=st[j-a[i]];
				st[j].flip(i);}}
	if(f[sum/2]==sum/2&&!(sum%2)){
		cout<<"Second\n";
		cout.flush();
		scanf("%lld",&x);
		while(x){
			if(x==-1)return 0;
			if(st[sum/2][x]){
				for(int i=1;i<=n;i++)
					if(!vis[i]&&!st[sum/2][i]){
						y=i;
						cout<<i<<"\n";
						cout.flush();
						break;}}
			else{
				for(int i=1;i<=n;i++)
					if(!vis[i]&&st[sum/2][i]){
						y=i;
						cout<<i<<"\n";
						cout.flush();
						break;}}
			if(a[x]<a[y])a[y]-=a[x],a[x]=0,vis[x]=1;
			else if(a[x]==a[y])a[x]=a[y]=0,vis[x]=vis[y]=1;
			else a[x]-=a[y],a[y]=0,vis[y]=1;
			scanf("%lld",&x);}}
	else{
		cout<<"First\n";
		cout.flush();
		cout<<1<<"\n";y=1;
		cout.flush();
		scanf("%lld",&x);
		while(x){
			if(a[x]<a[y])a[y]-=a[x],a[x]=0,vis[x]=1;
			else if(a[x]==a[y])a[x]=a[y]=0,vis[x]=vis[y]=1;
			else a[x]-=a[y],a[y]=0,vis[y]=1;
			if(x==-1)return 0;
			for(int i=1;i<=n;i++)
				if(!vis[i]){
					y=i;
					cout<<i<<"\n";
					cout.flush();
					break;}
		scanf("%lld",&x);}}
	return 0;}
```


---

## 作者：honglan0301 (赞：1)

## 题目分析

实质上是让你找必胜策略的简单博弈题。题意转化一下是让你每次选两个数换成它们的差，问最后会不会剩下一个数，根据样例和手玩从 $n=2$ 开始向大推广，容易得出以下结论：

* 若能分成两组和相等的数则后手必胜，策略是每次选与先手选的数不同组的数；若不能则先手必胜，策略是随便选。

猜到之后很好证明：

* 前者：显然每次后手按照策略选完后都不会改变“能分成两组相等的数”这一性质（操作前后分组方法是不变的），所以若先手能选则后手一定也能选，后手必胜。

* 后者：事实上不管怎么选都不改变“不能分成两组相等的数”这一性质（因为一次操作仅会把 $a,b$ 变成 $|a-b|$，若操作后能分，则操作前把 $\min (a,b)$ 放到另一组也就能分），所以数的个数每次减少一或二，最终一定会 只剩下一个数 或者 剩下两个不等的数（此时在操作一轮就只剩一个数了），那么先手必胜。

所以做完了，随便写个背包判胜负即可。

## 代码

```cpp
int n,a[305],sum,dp[305][90005],zt[305];

signed main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	dp[0][0]=1;
	for(int i=1;i<=n;i++) {for(int j=a[i];j<=sum;j++) dp[i][j]|=dp[i-1][j-a[i]]; for(int j=0;j<=sum;j++) dp[i][j]|=dp[i-1][j];}
	if(sum&1||!dp[n][sum/2])
	{
		cout<<"First"<<endl; int na=0,nb=0;
		while(1)
		{
			for(int i=1;i<=n;i++) if(a[i]) {na=i; break;}
			cout<<na<<endl; cin>>nb; if(nb==0) return 0; 
			int kk=min(a[na],a[nb]); a[na]-=kk; a[nb]-=kk;
		}
	}
	cout<<"Second"<<endl;
	int na=n,nb=sum/2;
	while(na)
	{
		if(nb>=a[na]&&dp[na-1][nb-a[na]]) zt[na]=1,nb-=a[na]; na--;
	}
	while(1)
	{
		cin>>na; if(na==0) return 0;
		for(int i=1;i<=n;i++) if(a[i]&&zt[i]!=zt[na]) {nb=i; break;}
		cout<<nb<<endl; int kk=min(a[na],a[nb]); a[na]-=kk; a[nb]-=kk;
	}
}
```


---

## 作者：Priestess_SLG (赞：0)

容易观察得出后手必胜的充要条件是 $a$ 序列存在一个子序列 $b$ 使得 $2\sum b_i=\sum a_i$。这个部分可以直接 $O(n^3)$ 暴力求解。

证明的话：如果可以划分出这样的一个子序列 $b$ 那么后手可以和先手对称选取，因为两组中减去的数的和相同，而两组的和也相同，所以最终两组的和必然一起被减到 $0$。此时后手必胜。

否则用同样的思想可以得到，若不满足条件则最终序列必然只剩下一个数（不可能最后所有的数被消除），此时先手必胜。而若初始不满足条件则执行多少次操作都不会满足条件，所以这样的情况必然是先手获胜。因此结论得证。

那么分类讨论，若先（后）手必胜，则她们的策略分别是什么。

I. 若先手必胜。

此时先手随便选就行了。总有一步后手会无路可走然后先手获胜。

II. 若后手必胜

在 $O(n^3)$ 背包的时候记录一下每一个数在哪一组，然后若先手选了一组中的数，后手在另一组中任意选取非 $0$ 数即可。

代码，十分容易实现。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f[310 * 310], a[310], pre[310 * 310], bel[310];
signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    f[0] = 1;
    int all = accumulate(a + 1, a + n + 1, 0ll);
    for (int i = 1; i <= n; ++i)
        for (int j = all; j >= a[i]; --j)
            if (f[j - a[i]] && !f[j]) f[j] = 1, pre[j] = i;
    if (all % 2 == 1 || !f[all / 2]) {
        cout << "First" << endl;
        int cnt = n;
        while (1) {
            for (int i = 1; i <= n; ++i)
                if (a[i] > 0) {
                    cout << i << endl;
                    int o; cin >> o;
                    if (!o) return 0;
                    int v = min(a[i], a[o]);
                    a[i] -= v, a[o] -= v;
                    break;
                }
        }
    } else {
        cout << "Second" << endl;
        int now = all / 2;
        while (now) {
            int key = pre[now];
            now -= a[key];
            bel[key] = 1;
        }
        while (1) {
            int o; cin >> o;
            if (!o) return 0;
            if (bel[o] == 1) {
                for (int i = 1; i <= n; ++i)
                    if (bel[i] != 1 && a[i]) {
                        cout << i << endl;
                        int v = min(a[i], a[o]);
                        a[i] -= v, a[o] -= v;
                        break;
                    }
            } else {
                for (int i = 1; i <= n; ++i)
                    if (bel[i] != 0 && a[i]) {
                        cout << i << endl;
                        int v = min(a[i], a[o]);
                        a[i] -= v, a[o] -= v;
                        break;
                    }
            }
        }
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1839E Decreasing Game(*2400)](https://www.luogu.com.cn/problem/CF1839E)

# 解题思路

首先我们可以发现一个性质，那就是我们如果可以将这个序列拆分成两组，使得这两组数字的和相同，则我们此时扮演后手**一定可以获胜**，具体的，若先手取了其中一组数字中的一个，那我们只需要取另一组数字中的任意一个目前不为 $0$ 的数字即可，因为两组数字的和**一致**且两组减去的数**一致**，因此按照此种方案，**后手一定取胜**。

接下来我们考虑**初始**无法拆分成两组和相等的数字的情况。

那么我们怎么去保证剩下的数字经过操作后仍然不能拆分成和相等的两组数字呢？

我们设删除的两个数字为 $a,b(a \le b)$。

那么要想两组数字的和相等，就需要满足 $sum1 + (b - a) = sum2$ 的条件。

移项可得 $sum1 + b = sum2 + a$，因此**不满足**一开始不能拆分的性质。

因此此时我们可以作为先手，删除一个任意此时可以删除的数字即可。

关于找出是否可以拆分成两组和相同的数字及其构造方案可以使用背包解决，时间复杂度 $O(nV^2)$，其中 $V$ 为值域。

# 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
#define bug cout<<"---------------------------------------\n";
//ll pw(ll x,ll y,ll mod){if(y==0)return 1;if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n;
ll a[310];
ll dp[310*310];
ll sum;
ll last[310*310];
ll vis[310];
ll ask(ll x)
{
	cout<<x<<endl;
	ll y;
	cin>>y;
	return y;
}
void solve()
{
    _clear();
	cin>>n;
	forl(i,1,n)
		cin>>a[i],sum+=a[i];
	dp[0]=1;
	forl(i,1,n)
		forr(j,301*301,a[i])
			if(!dp[j] && dp[j-a[i]])
				dp[j]|=dp[j-a[i]],
				last[j]=j-a[i];
	if(sum%2 || !dp[sum/2])
	{
		cout<<"First"<<endl;
		while(1)
		{
			forl(i,1,n)
				if(a[i])
				{
					ll qu=ask(i);
					if(qu==0)
						return ;
					ll sub=min(a[i],a[qu]);
					a[i]-=sub;
					a[qu]-=sub;
				}
		}
		return ;
	}
	ll num=sum/2;
	while(num)
	{
		ll now=last[num];
		ll need=num-now;
		ll pd=0;
		forl(i,1,n)
			if(!vis[i] && a[i]==need)
			{
				vis[i]=1;
				pd=1;
				break;
			}
		if(!pd)
			exit(-1);
		num=last[num];
	}
//	forl(i,1,n)
//		cout<<vis[i]<<" ";
//	cout<<endl;
	cout<<"Second"<<endl;
	while(1)
	{
		ll x;
		cin>>x;
		if(x==0)
			return ;
		ll bot=vis[x];
		forl(i,1,n)
			if(a[i]!=0 && vis[i]!=bot)
			{
				cout<<i<<endl;
				ll sub=min(a[i],a[x]);
				a[i]-=sub,
				a[x]-=sub;
				break;
			}
	}
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
  //  IOS;
    _t_=1;
 //   cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

