# Elections

## 题目描述

Berland地区的腐败现象非常常见。

马上有一场选举，你事先知道了选民和政党的数量，分别为  $n$  和  $m$  ，对于每一位选民，你知道他将要选举哪一个政党，不过，每一位选民都会在接受一定数额的金钱之后改变他的主意。如果你给第  $i$  位选民  $c_i$  数额的比特币，他就会选举任何你希望他选举的政党。

你的目的是让Berland的联合党赢得这场选举，联合党必须拥有比其它政党都多的选票，在此基础之上，你希望花费的比特币尽可能少。

## 样例 #1

### 输入

```
1 2
1 100
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5 5
2 100
3 200
4 300
5 400
5 900
```

### 输出

```
500
```

## 样例 #3

### 输入

```
5 5
2 100
3 200
4 300
5 800
5 900
```

### 输出

```
600
```

# 题解

## 作者：易极feng (赞：5)

真是神奇的一题。

比赛时贪心想错，之后又想了好久无解于是去睡觉了。

因为自己的选票与其他党派相关，所以直接贪心稍微有点复杂。（然而大佬们应该想出来了）

第二天突然想到，如果枚举自己的最终选票，贪心似乎就变得清晰明了了。

设枚举值为$i$,对每个选票比$i$大的党派，从小到大买~~（py）~~下它的选民直到它的选票恰等于$i-1$，并累计自己的选票数。如果清理完这些竞争对手后自己的选票数还小于$i$，就按所有选民从小到大的顺序买下那些还没有被买的选民。

复杂度$O(N^2)$。

这个故事告诉我们，~~西方的政治真黑暗~~逆向思维很重要。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

struct person{
	int p,c;
}s[3005];

bool operator <(person a,person b){
	return a.c<b.c;
}

int n,m;
long long ans;
int p[3005];
bool v[3005];

int main(){
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d%d",&s[i].p,&s[i].c);
		p[s[i].p]++;
	}
	
	int mv=p[1];
	sort(s+1,s+n+1);
	
	int t[3005];
	long long cnt,vote;
	ans=0x7fffffffffffffff;
	for(i=mv;i<=n;i++){
		memset(v,0,sizeof(v));
		memset(t,0,sizeof(t));
		cnt=vote=0;
		for(j=1;j<=n;j++){
			if(s[j].p==1){
				vote++,v[j]=1;
				continue;
			}
			if(p[s[j].p]-t[s[j].p]>=i){
				cnt+=s[j].c,v[j]=1,t[s[j].p]++,vote++;
			}
		}
		j=1;
		while(vote<i){
			if(!v[j])cnt+=s[j].c,vote++;
			j++;
		}
		ans=min(ans,cnt);
	}
	
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：KingPowers (赞：3)

## CF1019A Elections

[题目链接](https://www.luogu.com.cn/problem/CF1019A)

刚看到题目会有一种无从下手的感觉，因为鬼知道最后他要得几票。

但是观察数据发现 $n,m\le 3000$，那么 $nm$ 级别的复杂度甚至再来个 $\log$ 都是可以接受的。

于是我们直接取枚举最后的得票数，记为 $x$，那么接下来的任务也就有两项：判断这个得票数最后是否能赢得选举，若能，最少的花费是多少。

$m$ 最大只有 $3000$，为了方便处理直接把投给相同政党的人的贿赂金扔到 vector 里，并挨个排序。

然后对于第一个问题，如果任意一个其他政党的选票大于等于 $x$，那么肯定要贿赂几个投给这个政党的人，直到这个政党最后选票小于 $x$。贿赂谁？肯定谁便宜就贿赂谁，正好上面排过序。当所有其他政党的得票数都被贿赂到小于 $x$ 时，我们统计一下此时已经贿赂了多少人，记为 $p_{cnt}$，显然如果 $p_{cnt}>x$ 就说明当前的票数不够。

解决了第一个问题，第二个问题也就好解决了，记总花费为 $cost$，首先 $cost$ 肯定要加上上面为了保证赢得选举花的钱，然后如果 $p_{cnt}=x$ 的话显然此时 $cost$ 就是最后花的钱了。如果 $p_{cnt}<x$ 呢？那就从还没贿赂的人中抽出来 $x-p_{cnt}$ 个最便宜的贿赂上，注意别贿赂自己人，也就是别贿赂投给 $1$ 号政党的。

至此这个问题就彻底解决了，复杂度粗略地算下来大概是 $O(n(m+n+n\log n))$，能过。

```cpp
struct node{
	int p,c;
}a[N];
int n,m,ans=inf,t[N];
vector<int>v[N];
int check(int x){
	int tot=0,cost=0,cnt=0;
	for(int i=2;i<=m;i++){  //枚举其他政党 
		int j=0;
		if(v[i].size()>=x) j=v[i].size()-x+1;  //如果不贿赂就赢不了 
		for(int k=0;k<j;k++) cost+=v[i][k];
		for(;j<v[i].size();j++) t[++tot]=v[i][j];  //没贿赂的临时存一下 
	}
	int pnt=n-tot;
	if(pnt>x) return -1;  //票数不够
	sort(t+1,t+tot+1);
	for(int i=1;i<=x-pnt;i++) cost+=t[i];  //从还没贿赂的中挑几个直到选票够 
	return cost;
}
void Main(){
	n=read(),m=read();
	int beg=0;
	for(int i=1;i<=n;i++){
		a[i].p=read(),a[i].c=read();
		v[a[i].p].push_back(a[i].c);  //投给相同政党的都仍一块 
		if(a[i].p==1) beg++;
	}
	if(beg==n){
		printf("0");
		return;
	}
	for(int i=1;i<=m;i++) sort(v[i].begin(),v[i].end());
	for(int i=max(beg,1ll);i<=n;i++){
		int tmp=check(i);
		if(tmp!=-1) ans=min(ans,tmp);
	}
	printf("%lld",ans);
}
```

---

## 作者：Computer1828 (赞：3)

你可以去[CF457C](https://www.luogu.com.cn/problem/CF457C)双倍经验。

考虑贪心、二分，我们可以二分需要多少张票，然后问题就会转化成已知要多少张票，然后求花费的最小值。会发现票数和花费会形成一个抛物线，所以要注意二分时左端点和右端点的修改（纠正一下自己[CF457C](https://www.luogu.com.cn/problem/CF457C)的题解的错误）。

然后考虑怎么买票超过自己的对手：假设我需要 $x$ 张票，那么，所有票数大于等于 $x$ 的人的票都得买走；其次，我肯定要尽量买便宜的；最后，如果我买了这些票数大于等于 $x$ 的人的票后还不够 $x$ 张，那我就不得不从剩下的票池里买了，而且也一定会去买便宜的。

因为题目中说你自己是一号，所以所有投给你的票都不用买，那也就是说花费为 $0$；一定要开 `long long`。

时间复杂度大约是 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100000
#define ll long long
using namespace std;
int n,m;
vector<int> a[N+5];
inline ll check(ll u){
	ll ans = 0;
	int tot = a[0].size();
	vector<ll> nti;
	for(int i = 1;i<=N;++i){
		int j = 0,k = a[i].size();
		while(k>=u) ans += a[i][j++],--k,++tot;
		while(j<a[i].size()) nti.push_back(a[i][j++]);
	}
	sort(nti.begin(),nti.end());
	for(int i = 0;i<nti.size();++i){
		if(tot>=u) break;
		ans += nti[i],++tot;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i = 1;i<=n;++i){
		scanf("%d%d",&u,&v);
		if(u == 1) v = 0;
		a[u].push_back(v);
	}
	for(int i = 1;i<=N;++i) sort(a[i].begin(),a[i].end());
	ll l = 1,r = n;
	while(l<=r){
		int mid = (l+r)/2;
		if(check(mid) < check(mid+1)) r = mid-1;
		else l = mid+1;
	}
	printf("%lld",check(l));
	return 0;
}
```

---

## 作者：Frozencode (赞：3)

qwq这题想了好久，在大佬的点拨下才恍然大悟。

##### 果然我还是太菜

这场~~手速场~~，A、B的AC数都有4500，而这道C题不到1000...

------------

一开始以为是dp...但是后来发现好像想复杂了...

话不多说，上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=3e4+5;
const ll INF=1e15;//注意会爆int，所以要开大一点。
ll n,m;
vector<int> c[maxn];//用来存放每个选民的数据。
vector<int> rest;//存放还没有贿赂的选民，稍后会用。
ll rc[maxn],ch[maxn],vc[maxn],tot,p,cur,val;//vc数组表示当前每个党有多少支持的选民，ch数组存放贿赂每个党多少人。
int main()
{
	cin>>n>>m;
	tot=INF;//初始化最优解。
	for(int i=1;i<=n;i++)
	{
		cin>>p>>val;
		c[p].push_back(val);
		rc[p]++;
	}
	for(int i=1;i<=m;i++)sort(c[i].begin(),c[i].end());//对选民的金额进行排序，方便操作。
	for(int i=1;i<=n;i++)//关键代码 枚举1号党最终的票数。
	{
		cur=0;//获得至少i票时所需的金额。
		for(int j=1;j<=m;j++)vc[j]=rc[j],ch[j]=0;//初始化。
		for(int j=2;j<=m;j++)
		{
			for(;vc[j]>=i;ch[j]++)//如果该党票数>i，那我们就贿赂该党选民直到其票数<i。
			{
				vc[1]++;
				vc[j]--;
				cur+=c[j][ch[j]];
			}
		}
		if(vc[1]<i)//我们很容易发现，如果处理后1号党票数>i，那肯定不是最优解，现在只要处理票数不够的情况。
		{
			rest.clear();//初始化。
			for(int j=2;j<=m;j++)
			{
				for(int k=ch[j];k<c[j].size();k++)

				{
					rest.push_back(c[j][k]);//我们将除1号党外每个党还可贿赂的选民放入rest数组中。
				}
			}
			sort(rest.begin(),rest.end());//对rest数组排序。
			for(int j=0;vc[1]<i;j++,vc[1]++)
			{
				cur+=rest[j];//不断贿赂选民直到1号党票数=i。
			}
		}
		tot=min(tot,cur);//不断更新最优解。
	}
	cout<<tot<<endl;
	return 0;
}
```

---

## 作者：Dementor (赞：3)

# 题解（CF1019A）

原题链接（洛谷）：[CF1019A](https://www.luogu.com.cn/problem/CF1019A)

首先，看到这种题，不要想复杂（比方说我，刚开始想的还很简单，就是一个贪心，当测到第二个样例的时候就发现了我那个异常简单的问题，这也正是为什么我的那个贪心异常简单，于是我开始蒙了，想了一大堆奇奇妙妙的数据结构比如说最基本的线段树之类的，但是都用不到的 $……$）

所以思维很重要，不要将简单的事情想复杂，不要在复杂的事情中头脑简单。

这道题我们要知道，**如果我们正向枚举，贪心地“将目前能加进去的最优的加入”，那么我们可能需要一个数据结构，导致时间复杂度不正常**，再看看数据范围： $n, m \leq 3000$ ，让你想到什么？

没错，这题的时间复杂度就是 $O (nm)$ ，好了，现在我们的前期思想工作已经做好了，开始我们的硬核实现部分：

我们非常容易可以发现，最后 $1$ 得到的选票，一定在一个范围之间，我们将 $size_i$ 称为初始状态下第 $i$ 个政党有多少个支持者，那么这个范围就是 $[size_1, n]$ ，我们在这里用掉一个复杂度里面的 $n$ ，枚举一下这个范围里面所有的可能出现的最终结果。

然后我们这个时候看看在最终状态 $1$ 的票数是 $x$ 的情况下，$1$ 的政敌要被捞多少个人才能满足条件：

我们称 $need_i$ 表示对于一个 $x$ ，第 $i$ 个政党需要被捞多少个人才能满足题目条件。那么这个 $need_i$ 的计算公式我们很容易知道是：

$$need_i = (x \leq size_i) ? (size_i - x + 1) : 0$$

表示如果 $x$ 不足当前这个政党的原始支持人数，那肯定要捞人来，并且要捞 $size_i - x + 1$ 这么多个人。那么我们在这个政党的捞人花费是贪心算出来的，预处理的时候先排个序，然后处理第 $i$ 个政党的花费前缀和，查的时候直接用就好了。

现在我们称 $sum = \sum\limits_{x = 2}^{m}{need_i}$ 那么最终其实是会有两种情况：

* $sum \geq x$ 这种直接更新答案就好了

* $sum < x$ 这种说明 $1$ 的票还不够，还要捞人。那么就全局贪心，将那些已经捞过来的人和本来就支持 $1$ 的人不要算进去，知道满足 $sum \geq x$ 为止，捞完最后这一波后更新答案。

~~我的题解已经够详细甚至可以说太详细了吧，如果还有什么问题参见代码~~

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m;
struct voter {
	long long p, c;
	bool operator < (const voter & a) const {
		return a.c > c;
	}
}v[3010];
long long size[3010];
long long sum[3010][3010];
long long need[3010], bj[3010];
vector <long long> pr[3010];
long long pi, ci;
long long ans = 1e18;
int main () {
	cin >> n >> m;
	for (long long i=1;i<=n;i++) {
		scanf ("%lld %lld", &v[i].p, &v[i].c);
		pr[v[i].p].push_back (v[i].c);
		size[v[i].p] ++;
	}
	for (long long i=2;i<=m;i++) {
		sort (pr[i].begin (), pr[i].end ());
		for (long long j=0;j<pr[i].size ();j++) {
			sum[i][j] = sum[i][j - 1] + pr[i][j];
		}
	}
	sort (v + 1, v + n + 1);
	for (long long x=size[1];x<=n;x++) {
		memset (need, 0, sizeof need); memset (bj, 0, sizeof bj);
		long long summ = size[1], cost = 0; bj[1] = size[1];
		for (long long i=2;i<=m;i++) {
			need[i] = (x <= size[i]) ? (size[i] - x + 1) : 0;
			need[i] = min (need[i], size[i]);
			cost += sum[i][need[i] - 1]; bj[i] = need[i];
			summ += need[i];
		}
		if (summ >= x) {
			ans = min (ans, cost);
		} else {
			long long tongji = 0;
			for (long long i=1;i<=n;i++) {
				bj[v[i].p] --;
				if (bj[v[i].p] < 0) {
					cost += v[i].c;
					tongji ++;
					if (tongji + summ >= x) break;
				}
			}
			ans = min (ans, cost);
		}
	}
	cout << ans << endl;
}
```

去掉了调试的那些注释部分，~~保持代码清洁不浪费空间人人有责~~。

**望通过哟~~~**

---

## 作者：Mickey_snow (赞：2)

这题乍一看好像是一道图论难题。

我在考试时的思考方向是从选民下手，这样很容易想到贪心，尽可能选需要金币少的，但是有可能你选择一个相对需要金币较多的人，拉低了敌对政党的总票数，这样有可能比选择两个人只提升自己的票数更划算，而且，我们很难知道某一位选民到底能对我们做出多大贡献，因为有可能有多个政党票数比联合党多，再加上每位选民需要的金币不同，题目就显得更加复杂了。

这时我看到我校某位大佬也没有做出来这道题，于是就放弃了。

正确的思路应该是从政党入手。我们假设一个最终的结局，联合党的票数一定是最多的，所以我们只用枚举一下票数第二的政党获得的选票数量 $i$ ，随后的贪心就非常好想了。

首先，对于所有选票数大于 $i$ 的政党，我们必须从中拉一部分选民，先让这些政党票数都变为 $i$.

之后，有可能联合党票数还是少于 $i$, 这种情况下就可以用之前的贪心，每次尽可能选择需要金币最少的选民，将票数累加之 $i+1$ 即可。

可以发现如果联合党获得一半以上的选票就可以立即成为执政党，所以枚举 $i$ 的范围并不会很大。时间复杂度 $O(N^2)$.

另外还需要注意一下细节，判断一下选民是否已经被我们拉过票，否则有可能从一位选民手上拉两张选票导致错误。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Voter {
	int ID, needCoin;
	bool operator () (Voter a, Voter comp)const {
		return a.needCoin < comp.needCoin;
	}
};

vector<Voter> partyVote[3001];
vector<Voter> que;
bool vis[3001]; int Rank[3001];

int main()
{
	int totVoter, totParty, voteTarg, $;
	int votesGet = 0, nowVotes, siz = 0, Left;
	long long _min = 9223372036854775807LL, _count;

	cin >> totVoter >> totParty;
	for (int i = 0; i < totVoter; i++) {
		cin >> voteTarg >> $;
		if (--voteTarg == 0)votesGet++;
		else {
			partyVote[voteTarg].push_back({ i,$ });
			que.push_back({ i,$ });
		}
	}

	for (int i = 0; i < totParty; i++)Rank[i] = i;
	sort(Rank, Rank + totParty, [](int a, int comp) {return partyVote[a].size() > partyVote[comp].size(); });
	for (int i = 0; i < totParty; i++)
		sort(partyVote[i].begin(), partyVote[i].end(), Voter());
	sort(que.begin(), que.end(), Voter());

	siz = totVoter >> 1;
	for (int minNeeds = 0; minNeeds <= siz; minNeeds++) {
		nowVotes = votesGet; _count = 0;

		memset(vis, false, sizeof(vis));
		for (int i = 0; partyVote[Rank[i]].size() > minNeeds; i++)
			for (int j = 0; j < partyVote[Rank[i]].size() - minNeeds; j++) {
				_count += partyVote[Rank[i]][j].needCoin;
				nowVotes++; vis[partyVote[Rank[i]][j].ID] = true;
			}

		for (int i = 0; nowVotes <= minNeeds; i++) {
			if (vis[que[i].ID])continue;
			nowVotes++;
			_count += que[i].needCoin;
		}

		if (_count < _min)_min = _count;
	}

	cout << _min << endl;
	//system("pause");
	return 0;
}
```

---

## 作者：傅思维666 (赞：1)

## 题解：

一眼看出来贪心。

数据范围300，可以随便搞。N^2预定。

咋贪呢？发现如果正向考虑买票，并不是买价格最小的选民就最优，因为其他党派比你票多，如果你在削弱大党的同时给自己买票，有可能会更优。

所以考虑逆向贪心。

直接枚举自己最终胜选的票数是多少票，假设是$x$张。然后显然，高于这些票数的党派都需要被砍成$x-1$张才能保证让联合党胜出。在砍这些党派的过程中，肯定要从小到大买。

在砍完这些党派之后，如果1党还是没有等于x，那只好从剩下的所有党派中从小到大买。

然后发现这整个算法流程就是一枚举+判断。

所以完全可以用二分进行优化，把N优化成logN。

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=3003;
int n,m;
vector<int> v[maxn];
ll check(int x)//买x张选票能否更优
{
	ll ret=0;
	int tot=0;
	vector<int> tmp;
	for(int i=1;i<=m;++i)
	{
		int j=0,k=v[i].size();
		while(k>=x) 
			ret+=v[i][j++],--k,++tot;
		while(j<v[i].size()) 
			tmp.push_back(v[i][j++]);
	}
	sort(tmp.begin(),tmp.end());
	for(int i=0;i<tmp.size();++i)
	{
		if(tot>=x) 
			break;
		ret+=tmp[i],++tot;
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int p,c;
		scanf("%d%d",&p,&c);
		v[p].push_back(c);
	}
	for(int i=1;i<=m;i++)
		sort(v[i].begin(),v[i].end());
	for(int i=0;i<v[1].size();i++)
		v[1][i]=0;
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)<check(mid+1))
			r=mid-1;
		else
			l=mid+1;
	}
	printf("%lld\n",check(l));
	return 0;
}
```



---

## 作者：Silence_World (赞：0)

# 思路。

不太好想的一道题，因为谁汤姆知道自己需要多少票啊，这个票又不是固定的，想动态维护一下发现复杂度直接炸掉。想了一会又发现了一个新的思路，如果维护自己的选票，那这道题看起来就很简单了，看看达到这个选票是否比所有的帮派票都多，每次从最小值去买票，这样就很好写了，码量也不是太大。

# 代码。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int t,r;
}a[3005];
bool cmp(node a,node b){
	return a.r<b.r;
}
int b[300005];
bool fl[300005];
int t[300005];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].t>>a[i].r;
		b[a[i].t]++;
	}
	sort(a+1,a+n+1,cmp);
	int min1=0x7ffffffffffffff;
	for(int i=b[1];i<=n;i++){
		int x;
		memset(fl,0,sizeof(fl));
		memset(t,0,sizeof(t));
		int cnt=0;
		int y=0;
		for(int j=1;j<=n;j++){
			if(a[j].t==1){
				y++;
				fl[j]=1;
				continue;
			}
			if(b[a[j].t]-t[a[j].t]>=i){
				fl[j]=1;
				y++;
				t[a[j].t]++;
				cnt+=a[j].r;
			}
		}
		int q=1;
		while(y<i){
			if(!fl[q])cnt+=a[q].r,y++;
			q++;
		}
		min1=min(min1,cnt);
	}
	cout<<min1<<endl;
	return 0;
}
```


---

## 作者：BeyondStars (赞：0)

#题面
Berland地区的腐败现象非常常见。

马上有一场选举，你事先知道了选民和政党的数量，分别为  $n$  和  $m$  ，对于每一位选民，你知道他将要选举哪一个政党，不过，每一位选民都会在接受一定数额的金钱之后改变他的主意。如果你给第  $i$  位选民  $c_i$  数额的比特币，他就会选举任何你希望他选举的政党。

你的目的是让Berland的联合党赢得这场选举，联合党必须拥有比其它政党都多的选票，在此基础之上，你希望花费的比特币尽可能少。

输入格式

第一行包含两个整数  $n$  和  $m$ .

接下来  $n$  行每一行两个整数——  $p_i$  和  $c_i$  ，这一位选民将会选举政党的编号，和使他改变主意的最少比特币数额。

特别地，联合党的编号是1.

输出格式

一个整数，使联合党赢得选举所需花费的最少比特币数额。

#输入输出样例
```
输入样例#1： 
1 2
1 100
输出样例#1： 
0
输入样例#2： 
5 5
2 100
3 200
4 300
5 400
5 900
输出样例#2： 
500
输入样例#3： 
5 5
2 100
3 200
4 300
5 800
5 900
输出样例#3： 
600
```
#解答
其实这个题很明显是个贪心的题~~动态规划我不会~~。但是这个题的贪心非常有意思，体现了**正难则反**的思想。一开始，我的贪心策略是用一个堆存所有的党派，每个党派里面又用堆来存支持者，然后从支持者人数多的党派里面选取价格最小的来行贿。很明显，这样的贪心策略是不正确的！那么什么是正确的贪心策略呢？首先我们可以发现如果从投票者作为出发点，来进行贪心，这样似乎很有难度。那么我们考虑从答案出发，枚举最后的答案。假设目前枚举的答案是A，除了1号党派以外，其他所有党派的支持人数都应该**严格小于**1号党派。也就是说，我们必须把其它所有支持人数大于A的党派里面价格最小的几个行贿了。如果最后1号党派的支持人数仍然没有达到A,那么我们就应该从小到大，把可以行贿(可以行贿的意思是之前没有行贿过)的人全部行贿了，直到最后支持者人数为A。我们只需要从1...n/2来枚举每个答案就行了。
但是要注意一个个坑：
1.如果只有1号党派，那么最后应该判断一下cost是否被更改过，如果没有，应该输出0.
以下是AC代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int,int> voter;//第一个表示价格，第二个表示id
vector<voter> parties[3010];
int used[3010];
voter voters[3010];
inline long long min(long long a,long long b){return a>b?b:a;}
int main(void){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int pi,ci;
    for(int i = 1;i<=n;i++){
        cin>>pi>>ci;
        parties[pi].push_back(make_pair(ci,i));
        voters[i] = make_pair(ci,i);
    }
    sort(voters+1,voters+n+1);
    for(int i = 1;i<=m;i++){
        sort(parties[i].begin(),parties[i].end());
    }
    long long cost = 0x7fffffffffff;
    for(int supporter = parties[1].size();supporter<=n+1>>1;supporter++){//枚举每一个最后的支持者
        long long current_cost = 0;
        int current_supporter = parties[1].size();
        memset(used,false,sizeof(used));
        for(int i = 0;i<parties[1].size();i++){
            used[parties[1][i].second] = true;
        }
        for(int i = 2;i<=m;i++){
            if(parties[i].size()>=supporter){
                for(int k = 0;k<parties[i].size();k++){//把多出的部分的人必须行贿
                    current_cost+=parties[i][k].first;
                    used[parties[i][k].second] = true;
                    current_supporter++;
                    if(parties[i].size()-k-1<supporter){
                        break;
                    }
                }
            }
        }
        if(current_supporter<=supporter){//就是说把多出来的人全部行贿以后，还是不够，那么就要从小到大来行贿了
            for(int i = 1;i<=n&&current_supporter<supporter;i++){
                if(!used[voters[i].second]){//从小到大排序，把对应编号的voter标记为使用过
					current_supporter++;
                    current_cost+=voters[i].first;
                    used[voters[i].second] = true;
                }
            }
        }
        cost = min(cost,current_cost);
    }
    cout<<(cost==0x7fffffffffff?0:cost);
    return 0;
}
```


---

