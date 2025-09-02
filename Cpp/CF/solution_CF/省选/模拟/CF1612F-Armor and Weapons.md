# Armor and Weapons

## 题目描述

Monocarp plays a computer game. There are $ n $ different sets of armor and $ m $ different weapons in this game. If a character equips the $ i $ -th set of armor and wields the $ j $ -th weapon, their power is usually equal to $ i + j $ ; but some combinations of armor and weapons synergize well. Formally, there is a list of $ q $ ordered pairs, and if the pair $ (i, j) $ belongs to this list, the power of the character equipped with the $ i $ -th set of armor and wielding the $ j $ -th weapon is not $ i + j $ , but $ i + j + 1 $ .

Initially, Monocarp's character has got only the $ 1 $ -st armor set and the $ 1 $ -st weapon. Monocarp can obtain a new weapon or a new set of armor in one hour. If he wants to obtain the $ k $ -th armor set or the $ k $ -th weapon, he must possess a combination of an armor set and a weapon that gets his power to $ k $ or greater. Of course, after Monocarp obtains a weapon or an armor set, he can use it to obtain new armor sets or weapons, but he can go with any of the older armor sets and/or weapons as well.

Monocarp wants to obtain the $ n $ -th armor set and the $ m $ -th weapon. What is the minimum number of hours he has to spend on it?

## 说明/提示

In the first example, Monocarp can obtain the strongest armor set and the strongest weapon as follows:

1. Obtain the $ 2 $ -nd weapon using the $ 1 $ -st armor set and the $ 1 $ -st weapon;
2. Obtain the $ 3 $ -rd armor set using the $ 1 $ -st armor set and the $ 2 $ -nd weapon;
3. Obtain the $ 4 $ -th weapon using the $ 3 $ -rd armor set and the $ 2 $ -nd weapon.

In the second example, Monocarp can obtain the strongest armor set and the strongest weapon as follows:

1. Obtain the $ 3 $ -rd armor set using the $ 1 $ -st armor set and the $ 1 $ -st weapon (they synergize well, so Monocarp's power is not $ 2 $ but $ 3 $ );
2. Obtain the $ 4 $ -th weapon using the $ 3 $ -rd armor set and the $ 1 $ -st weapon.

## 样例 #1

### 输入

```
3 4
0```

### 输出

```
3```

## 样例 #2

### 输入

```
3 4
2
1 1
1 3```

### 输出

```
2```

# 题解

## 作者：do_while_true (赞：7)

首先可以不管套件，假定 $n<m$，那么答案不超过 $\mathcal{O}(\log n+\frac{m}{n})$，也就是先倍增把 $n$ 造出来，然后一步步造 $m$．

答案这么小，那么常见的套路就是把答案放进复杂度里。

然后考虑一个 dp，假设当且在第 $o$ 轮，令 $f_i$ 为手中最牛逼的盔甲是 $i$，能够拿到最牛逼的武器是 $f_i$，想要 dp 出第 $(o+1)$ 轮的 $f'$．

不用套件的转移，购买盔甲是 $f'_j\gets f_i,i\leq j\leq i+f_i$，购买武器是 $f'_i\gets f_i+i$．

用套件的话，那么一定是用 $i$ 和 $f_i$，要不然不会更优，所以也能类似转移。

通过打 tag 然后从后往前取 max 可以做到单次 $\mathcal{O}(n)$ 转移，那么时间复杂度就是 $\mathcal{O}(n\log n+m)$．

```cpp
const int N=200010;

int n,m,q,x,y,ans,f[N],g[N],fl;
map<int,int>vis[N];

void solve(){
	read(n,m,q);
	if(n>m)swap(n,m),fl=1;
	while(q--)read(x,y),fl?swap(x,y),0:0,vis[x][y]=1;
	f[1]=1;
	for(;f[n]<m;++ans){
		for(int i=1;i<=n;i++)if(f[i]){
			int k=vis[i][f[i]];
			cmax(g[min(n,i+f[i]+k)],f[i]);
			cmax(g[i],min(m,i+f[i]+k));
		}
		for(int i=n;i>=1;i--)f[i]=max(g[i],f[i+1]),g[i]=0;
	}
	cout << ans << '\n';
}
```

---

## 作者：Lynkcat (赞：7)

牛子题。

设 $f_{i,j}$ 为 $(i,j)$ 是否在列表里。$dp_{i,j}$ 为第 $i$ 步时，盔甲为 $j$ 的时候能得到的武器最大值，转移很容易 $dp_{i+1,j}=\max(\min(m,dp_{i,j}+j+f_{j,dp_{i,j}}),dp_{i+1,j}),dp_{i+1,\min(n,dp_{i,j}+j+f_{j,dp_{i,j}})}=\max(dp_{i+1,\min(n,dp_{i,j}+j+f_{j,dp_{i,j}})},dp_{i,j})$。

暴力转移是 $\text{ans}\times n$ 的。注意到当 $n\leq m$ 时，答案上界近似是 $\log+\frac{m}{n}$ 的，所以总复杂度不超过 $n\log n+m$。

```c++
//The Hunting Party - Keys To The Kingdom
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 200005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m;
unordered_map<int,int>Mp;
int f[2][N];
int ans;
void LYC_music()
{
	n=read(),m=read();
	bool bl=0;
	if (n>m) swap(n,m),bl=1;
	int q=read();
	for (int i=1;i<=q;i++)
	{
		int x=read(),y=read();
		if (bl) Mp[y*(m)+x]=1;
		else
		Mp[x*(m)+y]=1;
	}
	ans=inf;
		for (int j=1;j<=n;j++)
			f[0][j]=-inf;
	f[0][1]=1;
	for (int i=1;i;i++)
	{
		for (int j=1;j<=n;j++)
			f[i%2][j]=-inf;
		for (int j=1;j<=n;j++)
			if (f[(i-1)%2][j]>=1)
				f[i%2][j]=max(f[i%2][j],min(m,f[(i-1)%2][j]+j+Mp[j*m+f[(i-1)%2][j]])),f[i%2][min(n,j+(f[(i-1)%2][j])+Mp[j*m+f[(i-1)%2][j]])]=max(f[i%2][min(n,j+(f[(i-1)%2][j])+Mp[j*m+f[(i-1)%2][j]])],f[(i-1)%2][j]);
		if (f[i%2][n]==m)
		{
			writeln(i);
			return;
		}
	}
	writeln(ans);
}
signed main()
{
	int T=1;
	while (T--)
	{
		LYC_music();
	}
}
/*

*/



---

## 作者：qzilr (赞：7)

#### 前言
这篇题解主要记录了我做这题的思考历程，外加看完题解后的一些总结，因为是看了[这篇题解](https://www.luogu.com.cn/blog/Lynkcat/solution-cf1612f)会的，可能会有些相似，但我尽可能写出我的思考。
#### 题目描述
有 $n$ 个盾、$m$ 个矛，给出 $q$ 个装备列表形如 $(i,j)$，若装备 $(i,j)$ 在列表中，则它的 power 为 $i+j+1$，否则为 $i+j$，假设手上有装备的 power 为 $k$，则可以花一个小时获得一个小于 $k$ 的矛或盾，最初手上有装备 $(1,1)$ 求获得装备 $(n,m)$ 的最短时间。
#### 题目分析
意识到这题是 dp 后，我的第一反应是设 $dp_{i,j}$ 表示获得装备 $(i,j)$ 时最小花费的时间，但看了一眼数据范围 $n,m≤2×10^5$， 当即放弃了这种想法，后来我又想到设 $dp_i$ 表示第 $i$ 个时刻手上装备的 power 最大值，但是因为 dp 数组记录的信息不够，很难转移。
#### 思路遇阻
我从两个角度设计了 dp 数组，一个是因为时间复杂度过大，一个是因为记录信息过少，都无法做下去。这题题目给的条件就这么多，我们也挖不出别的信息。而且这题也不像一个 dp 优化，这时我显得有些束手无策。
#### 思路转换
其实，方法就在眼前。两种思路都是各有缺点又各有优点，仔细对比一下就会发现第一个记录信息多，但时间慢，第二个记录信息少，但时间快，两种方法恰好优势互补，不妨把两种思路结合起来，设 $dp_{i,j}$ 表示第 $i$ 个小时有第 $j$ 个矛时获得的最大的盾，这时就会忽然发现茅塞顿开，转移方程比较容易推，先考虑盾：
$$dp_{i,j}=\max(\min(dp_{i-1,j}+j+0/1,n),dp_{i,j})$$
再考虑矛：
$$dp_{i,j+dp_{i-1,j}+0/1}=\max(\min(dp_{i-1,j},m),dp_{i,j+dp_{i-1,j}+0/1})$$
转移方程推出来后，就只剩下时间复杂度还不确定。
#### 复杂度分析
这一部分我不太会算，就直接放[题解](https://www.luogu.com.cn/blog/Lynkcat/solution-cf1612f)中的时间复杂度了，暴力转移是 $ans⋅n$ 的，不妨设 $n≤m$ 此时答案的上界近似是 $\log n+\frac{m}{n}$ ，所以时间复杂度近似是 $n\log n+m$。
#### 代码
因为矛和盾只是 $(i,j)$ 的题目背景，本质上只是数值不同，所以代码中为了保证 $n≤m$ 和简化实现，淡化了 $(i,j)$ 具体的类别，仅仅将它们看作一类、另一类。
```cpp
#include<bits/stdc++.h>
#define rg register
#define int long long
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++;}
inline int read(){
	rg int res=0,sgn=0;char ch=getc();
	while(!isdigit(ch)){if(ch==EOF) exit(0);if(ch=='-') sgn=1;ch=getc();}
	while(isdigit(ch)) res=res*10+ch-48,ch=getc();
	return sgn?-res:res;
}
using namespace std;
const int N=4e5+5,inf=1e16;
unordered_map<int,int> mp;
int dp[2][N];
signed main(){
	int n=read(),m=read(),tag=0,q=read();
	if(n>m) swap(n,m),tag=1;
	while(q--){
		int i=read(),j=read();
		if(tag) mp[i*m+j]=1;else mp[j*m+i]=1;
	}
	for(rg int i=1;i<=n;++i) dp[0][i]=-inf;
	dp[0][1]=1;
	for(rg int i=1;i;++i){
		for(rg int j=1;j<=n;++j) dp[i%2][j]=-inf;
		for(rg int j=1;j<=n;++j)
			if(dp[(i-1)%2][j]>=1){
			int c=mp[dp[(i-1)%2][j]*m+j];
			dp[i%2][j]=max(min(dp[(i-1)%2][j]+j+c,m),dp[i%2][j]);
			dp[i%2][min(j+dp[(i-1)%2][j]+c,n)]=max(dp[(i-1)%2][j],dp[i%2][min(j+dp[(i-1)%2][j]+c,n)]);
		}
		if(dp[i%2][n]==m) return cout<<i<<endl,0;
	}
}
```
#### 总结
其实当一道 dp 题做了很长时间，想了很多方向时，题目有用的信息大多都发现了，这时不妨回过头重新看自己的思路，每一次思考方向的转变都是条件的深挖，或许把它们综合起来就挖出了整道题，那时解法就不在话下了。

---

## 作者：panyf (赞：4)

upd：修改了 $n=1$ 时的错误。

随便翻了翻题解区和 CF 提交记录发现都是 $O(n\log n)$ 或者 $O(n\log^2 n)$ dp，这里提供一个神秘 $O(n)$ 贪心~~欢迎 hack~~。

首先，每次合成下一个装备，一定是用当前最强的武器和最强的盾，原因是加成的效果只有 $1$。

设当前最强的武器强度是 $i$，盾是 $j$，则合成的下一个装备强度至多是 $i+j$ 或 $i+j+1$。

然后第二次合成的强度至多是 $i+i+j+c$ 或者 $i+j+j+c$，取决于第一次合成武器还是盾，其中 $c\in[0,2]$。

不妨设 $i<j$，则 $i+i+j+c<i+j+j+c$，所以当 $i<j$ 时合成武器较优，否则合成盾较优。所以最优的策略一定是武器、盾、武器、盾……这样交替合成。

但是我们不能一直按这种策略。不妨设 $n<m$，若某一时刻 $i+j+c\geq n$，即只需要一步就能合成最强的武器，则我们会先合成一个强度为 $n$ 的武器，然后一直合成盾直到合成出强度为 $m$ 的盾。

但这样还是有问题。考虑以下数据：

```
9 5
1
2 1

```
只需要四步：$(1,1)\to(2,1)\to(4,1)\to(4,5)\to(9,5)$。

错误的做法需要五步：$(1,1)\to(2,1)\to(2,4)\to(2,5)\to(7,5)\to(9,5)$。

容易发现，若 $i+j+j+c_1+c_2\geq n$，即只需要两步就能合成最强的武器，则最优策略是先合成强度为 $i+j+c_1$ 的盾，然后合成强度为 $n$ 的武器，这样能保证合成出最强武器时盾尽可能强。

然后就做完了，贪心的不同策略只有两种（第一步合成武器还是盾），所以复杂度 $O(n)$（大部分情况是 $O(\log n)$ 的，只有 $n,m$ 中有一个很小另一个很大时达到上界，时间瓶颈实际上是读入）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
unordered_set<int>s[N];
int ans=1e9,n,m;
void dfs(int x,int y,bool a,bool b,int w){
//x,y分别表示当前最强的武器和盾的级别
//a表示当前应该合成武器还是盾
//b表示当前最强的武器是否已经达到n（不妨设n<=m）
//w表示当前合成的次数
	int z=x+y+s[x].count(y);
	if(z>=n&&!b)return dfs(n,y,0,1,w+1);
	if(x+z>=n&&!b)return dfs(x,z,0,0,w+1);
	if(z>=m){ans=min(ans,w);return;}
	if(x==n)return dfs(n,z,0,1,w+1);
	if(a)dfs(z,y,!a,b,w+1);else dfs(x,z,!a,b,w+1);
}
int main(){ios::sync_with_stdio(0),cin.tie(0);
	int q,i,j,k;
	for(i=1,cin>>n>>m>>q;i<=q;++i){
		if(cin>>j>>k,n>m)swap(j,k);
		s[j].insert(k);
	}
	if(n>m)swap(n,m);
	dfs(1,1,0,n==1,0),dfs(1,1,1,n==1,0),cout<<ans+1;
	return 0;
}
```


---

## 作者：FZzzz (赞：2)

首先发现每次一定是使用两边最大的两个，因为小的就算加上加成也不会比这优。

假定 $n\le m$，估计一下答案的上界。首先我们一左一右操作两次可以让两边最大的都近似乘以二，$O(\log n)$ 次可以拿到 $n$，再 $O(\dfrac mn)$ 次把 $m$ 也拿到。那么如果我们对于每个操作次数可以 $O(n)$ 或者带个 log 地判断这么多次操作能不能达到目标，就可以 $O(n\log n+m)$ 求解。

那么记 $f_i$ 为左边最大的是 $i$ 时，右边最大的最大能是多少，转移是容易的。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n,m,q,f[maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	q=readint();
	set<pair<int,int>> s;
	for(int i=1;i<=q;i++){
		int a,b;
		a=readint();
		b=readint();
		if(n>m) swap(a,b);
		s.insert({a,b});
	}
	if(n>m) swap(n,m);
	f[1]=1;
	int ans=0;
	for(;f[n]<m;ans++) for(int i=n;i>0;i--) if(f[i]){
		int k=i+f[i]+s.count({i,f[i]});
		f[min(k,n)]=max(f[min(k,n)],f[i]);
		f[i]=min(k,m);
	}
	printf("%d\n",ans);
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```

---

## 作者：ln001 (赞：1)

## 题意
给出两类物品称为 A 和 B，A 的编号 $\in [1, n]$，B 的编号 $\in [1, m]$。任意两个 A 和 B 均可以匹配，若其编号为 $(i, j)$ 则匹配的权值为 $i + j$，特别的，对于给定的 $q$ 种匹配，其权为 $i + j + 1$。初始时你有编号为 $1$ 的 A 类物品和 B 类物品各一件，每次你可以从你拥有的物品中选出一组匹配，并决定得到编号**不超过**该匹配权值的 A 或 B，求同时拥有权值为 $n$ 的 A 和权值为 $m$ 的 B 需要的最少操作次数。

## 做法
新合成物品的编号和合成它所使用的匹配的权值是不等关系，所以可以使用编号最大的 A 与 B 来描述当前局面，下文将其与物品匹配均表达为 $(i, j)$。

先分三种情况讨论出答案的上界：

- 考虑 $n, m$ 相等且 $q = 0$ 的情况，此时的最优操作方式为左脚踩右脚螺旋上天，即交替把当前局面 $(i, j)$ 改变为 $(i + j, j)$ 与 $(i, i + j)$，不难发现，若进行 $k$ 次合成，则此时 $\max(i, j) = Fib(k - 2)$，又因为 $Fib(x)$ 近似为幂函数，所以在本段落所述情况中的操作次数为 $O(\log_2 n)$。

- 考虑 $n, m$ 相等且 $q \not= 0$ 的情况，由于特殊匹配的权值和非特殊匹配的权值仅差 $1$，对答案的影响不大，操作次数也为 $O(\log_2 n)$。

- 考虑 $n, m$ 不相等且 $q \not= 0$ 的情况，不妨设 $n < m$，可以先通过 $O(\log_2 n)$ 次操作达到上文所属情况，再通过不断合并出 B 达到想要的结果，总的操作次数为 $O(\log_2 n + \frac{m - n}{n})$，近似为 $O(\log_2 n + \frac{m}{n})$。

接下来考虑 dp 做法，最最最朴素的想法为设 $f_{i, j}$ 表示达到局面 $(i, j)$ 所需要的最少操作次数，时空复杂度直接炸了。上文刚刚讨论出答案的值域较小，所以参考常见 trick 交换 dp 下标和答案，即设 $f_{k, i} = j$ 表示操作 $k$ 步达到局面 $(i, j)$，且最大化 $j$，转移不难，暴力转移即可。

答案为最小的 $k$ 满足 $f_{k, n} = m$。

---

## 作者：Rem_CandleFire (赞：1)

在本题中，一个最关键的性质：对于任意给定的 $n,m$，$ans\le \log n +\lceil \frac{m}{n} \rceil$，对此式的理解为：倍增造出盔甲 $n$，然后以 $n$ 为跳板造 $m$。或许存在误差，但是误差对于时间的影响可以忽略不计。

相对于 $n,m\le2\times 10^5$，$ans$ 较小。且我们状态转移时记录的信息应该同时包含**盔甲、武器和时间**三项，否则难以转移。

总体考虑后，我们把答案“放入”时间复杂度内，即设 **$f_{i,j}$ 表示第 $i$ 个小时，当前造出来的盔甲/武器最高级别为 $j$ 时，另一项的最高级别为** $f_{i,j}$。
考虑转移，即对于第 $i$ 个小时，造盔甲或是造武器。同时还要记录 $(i,j)$ 是否在列表中，使用 `map<pair<int,int>,int> M` 即可。

首先，无论选什么，能够达到的最高级别均为 $t=j+f_{i,j}+M(i,j)$

如果造盔甲，有：
$$f_{i+1,\min(t,n)}=\max\{ f_{i,j}\}$$
如果造武器，有：
$$f_{i+1,j}=\max\{\min(m,t)\}$$

为了能够开出 $f$ 数组，且 $f_{i+1,\dots}$ 只和 $i$ 有关，所以使用滚动数组优化空间。同时为了保证时间复杂度的正确性，当 $n\ge m$ 时我们交换 $n,m$，注意此时列表内也要对换。

[AC code](https://www.luogu.com.cn/paste/t12n8v1b)

---

## 作者：lightup37 (赞：1)

## 前言

发现自己 vp 时候的做法和题解区里的做法都不太一样，所以来发篇题解求叉。

## 题意

你穿越到了异世界玩原神。这个世界的原神有 $n$ 种角色和 $m$ 种武器，你一开始有第 $1$ 种角色和第 $1$ 种武器。假设你将第 $i$ 种角色和第 $j$ 种武器搭配，那么你的基础战斗力是 $i+j$。这个世界的原神中，也有些角色有对应的专武，如果第 $j$ 种武器是第 $i$ 种角色的专武，那么你把第 $i$ 种角色和第 $j$ 种武器搭配时，你的战斗力会额外上升 $1$。你可以花 $1$ 单位时间获得第 $k$ 种角色或者第 $k$ 种武器（$k$ 是不大于你当前战斗力的最大值的任意一个整数）。如果你想要获得第 $n$ 种角色和第 $m$ 种武器，那么你至少需要多少单位时间。

## 解法

用有序二元组 $(i, j)$ 代表当前拥有的唯一达到最大战斗力的角色和武器的搭配是把第 $i$ 种角色和第 $j$ 种武器搭配。容易证明所有可能出现在最优解中的状态可以用某个二元组代表。容易证明如果通过 $k$ 步可以到达 $(a, b)$ 和 $(c, d)$，且 $a\leq c, b\leq d$，那么 $(a, b)$ 是不优的。记 $T(i, j)$ 为第 $i$ 种角色和第 $j$ 种武器搭配的战斗力。

如果没有专武，通过上面的原则排除不优的解，那么我们的刷本线路一定是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/du3fjhs3.png)

猜测当前 $(i, j)$ 都很大且都不顶到上界的时候（这个时候 $|i-j|$ 也应该很大），我们不会刻意去刷专武，只会在我们当前应该走的路径（用 $T(i, j)$ 替代 $i$, $j$ 中的较小值）上有专武的时候顺便用一下。

$(i, j)$ 较小时，暴力建出所有边，从 $(1, 1)$ 开始 bfs 求出达到所有 $x, y\leq lim$ 的 $(x, y)$ 需要的最小单位时间。枚举这些 $(x, y)$，考虑对于这些 $(x, y)$，我们一直像前面提到的 $(i , j)$ 都很大的时候的方法走来统计答案。

仍然需要考虑边界情况：$i$ 将要达到 $n$ 或者 $j$ 将要达到 $m$ 时，此时我们可能不会用 $T(i, j)$ 替换 $i$, $j$ 中的较小值，而是直接让 $i$ 或 $j$ 中的一个顶到上限，比如这种情况。

$n=6, m=8$

$\cdots \rightarrow (4, 2) \rightarrow (6, 2) \rightarrow (6, 8)$

$\cdots \rightarrow (4, 2) \rightarrow (4, 6) \rightarrow (6, 6) \rightarrow (6, 8)$

此时下面的走法严格劣于上面的，证明了考虑这种情况的必要性。

这种情况在一个 $(x, y)$ 上只会出现 $\mathcal O(1)$ 次。此时行动路线也几乎固定的，只需要考虑路径上正好有专武的情况，预处理即可。

## 代码与提交记录

<https://codeforces.com/contest/1612/submission/188966485>

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define uf(i,x,y) for(int i=x, i##end=y; i<i##end; ++i)
#define ll long long
#define pir pair<int, int>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back 
char ch;
int rd() {
	int f=1, x=0; ch=getchar();
	while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
	while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
const int lim = 200;
vector< pir > edge[lim+10][lim+10];
int n, m, q; map<pir, int> ok; int g[lim+10][lim+10];
int dis[lim+10][lim+10]; pir Q[(lim+10) * (lim+10)]; int l=1, r=0;
int Mans[200005], Nans[200005];

int _ans = 0x3f3f3f3f;
void bfs() {
	memset(dis, 0x3f, sizeof(dis));
	Q[++r] = mp(1, 1); dis[1][1] = 0;
	while(r >= l) {
		int u = Q[l].fir, v = Q[l].sec; ++l;
		// cerr << "at " << u << ' ' << v << endl;
		for(auto [x, y]:edge[u][v]) {
			if(dis[x][y] == 0x3f3f3f3f) { dis[x][y] = dis[u][v]+1; Q[++r] = mp(x, y); }
		}
	}
}
void solve(int i, int j) {
	int oi = i, oj = j;
	int ans = dis[i][j];
	while(!(i == n || j == m)) {
		++ans;
		int R = i+j; if(ok.find(mp(i, j)) != ok.end()) ++R;
		if(R >= n) {
			_ans = min(_ans, ans+Mans[j]);
			// if(ans+(m-j+n-1)/n == 99966) cerr << oi << ' ' << oj << endl;
		}
		if(R >= m) {
			_ans = min(_ans, ans+Nans[i]);
			// if(ans+(n-i+m-1)/m == 99966) cerr << oi << ' ' << oj << endl;
		}
		if(i < j) i = min(R, n); else j = min(R, m);
	}
	if(i == n) ans += (m-j+n-1)/n;
	if(j == m) ans += (n-i+m-1)/m;
	_ans = min(_ans, ans);
	// if(ans == 99966) cerr << oi << ' ' << oj << ' ' << dis[oi][oj] << endl;
}
int main() {
	rd(n); rd(m); rd(q); f(i,1,q) { int x=rd(), y=rd(); ok[mp(x, y)] = 1; if(x<=lim&&y<=lim) g[x][y]=1; }
	f(i,1,min(lim,n)) f(j,1,min(lim,m)) {
		f(k,1,min(lim,i+j+g[i][j])) edge[i][j].pb(mp(min(k,n), j)), edge[i][j].pb(mp(i, min(k,m)));
	}
	Mans[m] = 0;
	d(j,1,m-1) {
		int R = n+j; if(ok.find(mp(n, j)) != ok.end()) ++R;
		Mans[j] = 1+Mans[min(R, m)];
	}
	Nans[m] = 0;
	d(i,1,n-1) {
		int R = i+m; if(ok.find(mp(i, m)) != ok.end()) ++R;
		Nans[i] = 1+Nans[min(R, n)];
	}
	bfs();
	f(i,1,lim) f(j,1,lim) if(i<=n && j<=m) solve(i, j);
	cout << _ans << endl;
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

一种乱搞做法。

首先容易观察到如果 $n$ 和 $m$ 差距不是特别大，答案会比较小，具体地，答案大约是 $\Theta(\log n+\frac{n}{m})$ 级别的。

我们考虑一个暴力：设 $dp_{i,j}$ 表示从 $(1,1)$ 到达 $(i,j)$ 的最小时间，然后计算出 $(i,j)$ 可以产生多少 power，设为 $p$，那么 $dp_{i,j}$ 可以转移到 $dp_{k,j}/dp_{i,l}$，其中要满足 $|k-i| \le p/|l-j| \le p$。

这样直接做复杂度是 $\Theta(nm\max(n,m))$，优化的话可以上线段树，不过稍微剪剪枝就足够通过我们需要它跑的范围了。

考虑 $nm$ 比较大的时候怎么办，此时答案比较小，因此将上面的暴力状态和答案互换，设 $dp_{i,j}$ 表示从 $(1,1)$ 走到第 $i$ 行，花费 $\le j$ 的代价最大能走到的纵坐标，转移也跟上面的暴力差不多，直接做复杂度大概是 $\Theta(n^2ans)$ 的，同样可以线段树优化，不过我随便加了点乱搞就过了。

## 代码

[Link](https://codeforces.com/contest/1612/submission/291134094)

---

## 作者：hater (赞：0)

一句话题解：枚举答案，每次 $O(n)$ dp。

先考虑 $n$ 和 $m$ 相等，那么答案大概 $\log$ 级别的（斐波那契）。

dp 部分基于一个简单贪心，我们要换肯定会选当前最大的武器或者是盔甲。

原因很简单，因为最多的额外增益是加一，为了增益而选小一点的玩意，在本身的价值上肯定就会亏损大于一的收益。

$f_{i}$ 表示手中是第 $i$ 个盔甲能拿最大的武器 。转移非常简单可以直接看 code。

细想一下还会有点小问题，我们转移的第二种不是连续的（tp 转移的），中间有空隙按理来说要取后缀 $\max$。

但是我们基于上面的贪心就容易知道：如果要选空隙中的，肯定不如选后面的 。

之后，如果 $n$ 很大 $m$ 很小，每次只能加一个 $m$ 上去答案还是会很大。

之后认真分析一波，在 $m \leq n$ 时，答案级别是 $\frac{n}{m}+\log{m}$ 。

那我们枚举小的那个就完事了。

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define i60 long long 
#define dou double  
#define ls k<<1 
#define rs k<<1|1 
using namespace std ; 
const int N = 2e5+10 ; 
int f[N] , n , m , tp[N] ;   
vector <int> v[N] ; 
int qy( int x  , int y ) { 
  return ( *lower_bound( v[x].begin() , v[x].end() , y ) ) == y ; 
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  memset( f , -1 , sizeof(f) ) ; 
  cin >> n >> m ; int q , x , y , flag=0 ; cin >> q ; 
  if( n > m ) swap( n , m ) , flag=1 ; 
  while( q -- ) { 
    cin >> x >> y ; 
	if( flag ) swap( x , y ) ; v[x].push_back(y) ; 
  } 
  fp( i , 1 , n ) v[i].push_back(0) , sort( v[i].begin() , v[i].end() ) ; 
  int ans , vl ; f[1] = 1 ; 
  for( ans=0 ; ; ans++ ) { 
	if( f[n] == m ) break ; 
    fp( i , 1 , n ) tp[i] = -1 ; 
    fp( i , 1 , n ) { 
      if( f[i] == -1 ) continue ; 
      vl = i + f[i] + qy( i , f[i] ) ; vl = min( vl , m ) ; 
      tp[min(n,vl)] = max( tp[min(vl,n)] , f[i] ) ; f[i] = vl ; 
	} 
	fp( i , 1 , n ) f[i] = max( f[i] , tp[i] ) ; 
  } 
  cout << ans << '\n' ; 
  return 0 ; 
}  

/*

9 5
1
2 1

*/

```


---

