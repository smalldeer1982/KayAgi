# [ABC139E] League

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc139/tasks/abc139_e

$ N $ 人の選手がテニスの大会に参加します。彼らを選手 $ 1 $、選手 $ 2 $、$ \ldots $、選手 $ N $ と呼びます。

大会は総当たり戦で、合計 $ N(N-1)/2 $ 試合が行われます。 これらの試合の日程を、以下の条件をすべて満たすように決めることは可能でしょうか。可能である場合、必要な最小の日数も求めてください。

- 各選手は一日に最大で一試合を行う。
- 各選手 $ i $ $ (1\ \leq\ i\ \leq\ N) $ は、選手 $ A_{i,\ 1},\ A_{i,\ 2},\ \ldots,\ A_{i,\ N-1} $ とこの順に一度ずつ試合を行う。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ A_{i,\ j}\ \leq\ N $
- $ A_{i,\ j}\ \neq\ i $
- $ A_{i,\ 1},\ A_{i,\ 2},\ \ldots,\ A_{i,\ N-1} $ はすべて異なる。

### Sample Explanation 1

$ 3 $ 日間で次のように試合を行えばすべての条件を満たせます。 - $ 1 $ 日目: 選手 $ 1 $ 対 選手 $ 2 $ - $ 2 $ 日目: 選手 $ 1 $ 対 選手 $ 3 $ - $ 3 $ 日目: 選手 $ 2 $ 対 選手 $ 3 $ これが必要な最小日数です。

### Sample Explanation 2

$ 4 $ 日間で次のように試合を行えばすべての条件を満たせます。 - $ 1 $ 日目: 選手 $ 1 $ 対 選手 $ 2 $、選手 $ 3 $ 対 選手 $ 4 $ - $ 2 $ 日目: 選手 $ 1 $ 対 選手 $ 3 $ - $ 3 $ 日目: 選手 $ 1 $ 対 選手 $ 4 $、選手 $ 2 $ 対 選手 $ 3 $ - $ 4 $ 日目: 選手 $ 2 $ 対 選手 $ 4 $ これが必要な最小日数です。

### Sample Explanation 3

どのような日程で試合を行っても何らかの条件に違反します。

## 样例 #1

### 输入

```
3
2 3
1 3
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
4
2 3 4
1 3 4
4 1 2
3 1 2```

### 输出

```
4```

## 样例 #3

### 输入

```
3
2 3
3 1
1 2```

### 输出

```
-1```

# 题解

## 作者：Lskkkno1 (赞：7)

- [AT4893 [ABC139E] League](https://www.luogu.com.cn/problem/AT4893)

### 题意简述

$n$ 个人进行 $\frac {n(n -1)} {2}$ 场比赛，每个人都要以一个特定的顺序（以一个 $n \times (n - 1)$ 的矩阵的形式给出）与其他人比赛。

且每个人每天只可以比一场比赛，问最少比赛的天数为多少，无解输出 -1。

### 正解

发现一个人假如可以和另外一个打比赛时，和他打比赛肯定是最优的。

因为另外那个人此时肯定也只可以和他打比赛，对除了这两人之外的其他人没有影响。

每一场比赛都可以用一个二元组表示 $(x, y)$ 成一个节点，节点向节点连边表示限制。

比如说第一个人要先后和第二个人和第三个人打比赛， 那么 $(1, 2) \to (1,3)$。

这样的话只有入度为 $0$ 的点（比赛）才可以进行，用 topo 排序做一下。

给出结论：有环的话肯定无解，没环的话答案就是最长链。

前一个很好证明，关键是后面一个怎么证明。

其实也挺好证，因为当前入度为 $0$ 的节点（比赛）肯定都可以在同一天进行完。

具体一点 ：$(1,2)$ 和 $(1,3)$ 肯定不会同时可以进行比赛（同时入度为 $0$）。

**Code :**

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#define N 1003

using namespace std;

struct edge{
	int to, nxt;
}e[N * N * 3];

int n, cnt;
int ins[N * N], mp[N][N], fir[N * N], t[N * N];

queue < int > Q;

int id(int ,int);
void add(int ,int);

int main(){
	scanf("%d", &n); int ans = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < n; ++j)
			scanf("%d", mp[i] + j);
	for(int i = 1; i <= n; ++i)
		for(int j = 2; j < n; ++j)
			add(id(i, mp[i][j - 1]), id(i, mp[i][j]));
	for(int i = 1; i <= n * n; ++i){
		if(!ins[i]) Q.push(i);
		t[i] = 1;
	}
	while(!Q.empty()){
		int u = Q.front(); Q.pop(); ans = max(ans, t[u]);
		for(int i = fir[u]; i; i = e[i].nxt){
			int v = e[i].to;
			--ins[v];
			if(!ins[v])
				Q.push(v), t[v] = t[u] + 1;
		}
	}
	for(int i = 1; i <= n * n; ++i) 
		if(ins[i]) ans = -1;
	cout << ans << endl;
	return 0;
}

int id(int x,int y){
	if(x > y) swap(x, y);
	return (x - 1) * n + y;
}

void add(int u,int v){
	e[++cnt] = (edge){v, fir[u]}; fir[u] = cnt; ++ins[v];
	return ;
}

```

---

## 作者：蒟酱 (赞：5)

似乎都是用拓扑排序做的？这里给出一个暴力做法但是复杂度正确。  
注意到 $n\le 1000$，考虑一种最暴力的写法，每一次对所有人进行查找比赛是否能进行，如果每次都可以所有人进行比赛，要进行 $n$ 次，复杂度是$\mathcal O(n)$，但是要是每天只有两个人能够进行比赛，复杂度是 $\mathcal O(n\times\dfrac{n\times(n-1)}2)$ 也就是 $\mathcal O(n^3)$ 的可以被构造特殊数据卡掉，所以要考虑复杂度正确的暴力。  
考虑这么一个性质，如果目前是第 $i$ 天，那么第 $i$ 天参加比赛的人一定至少有一个人在第 $i-1$ 天参加了比赛。证明：如果没有表示这两天的比赛是互不干扰的，互不干扰表示可以在同一天进行，所以在暴力枚举是会在第 $i-1$ 天处理掉的。  
也就是说可以在每次记录昨天参加比赛的人，在今天枚举的时候只需要枚举昨天参加比赛的人就可以了。至于判断一个人是否可行，只需要记录这个人指向的目标指向的目标是不是自己就可以了，写指针很方便而且很快，但是可能两个人都互相枚举到了，所以要去重。  
关于时间复杂度：考虑每次能解决 $w$ 次比赛，总共要进行 $\dfrac{n^2}w$ 天的比赛，每天比赛计算的复杂度是 $\mathcal O(w)$，那么复杂度是 $\mathcal O(\dfrac{n^2}w w)$ 也就是 $\mathcal O(n^2)$，不过我用了快速排序去重所以复杂度是 $\mathcal O(n^2\log w)$，实测因为常数小比用 `unordered_set` 写的去重快。  

~~快读很长所以放链接里了~~ code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define autque(a) std::sort(a.begin(),a.end());a.erase(std::unique(a.begin(),a.end()),a.end())
// 快读在 https://www.cnblogs.com/bxjz/p/piper_add.html
constexpr int kN=1e3+1;
int n,k,cnt,f[kN][kN],*nw[kN];
using pii=std::pair<int,int>;
std::basic_string<int>lt;
std::vector<pii>wl;
signed main(){
//	freopen("plan.in","r",stdin);
//	freopen("plan.out","w",stdout);
	fio>>n;cnt=n*(n-1)/2;
	for(int i=1;i<=n;i++){
		lt+=i;
		for(int j=1;j<n;j++)fio>>f[i][j];
		nw[i]=f[i]+1;
	}
	for(k=0;cnt;k++){
		if(lt.empty())return fio<<"-1",0;
		for(int i:lt)if(i==*nw[*nw[i]])wl.emplace_back(std::minmax(i,*nw[i]));
		lt.clear();autque(wl);
		for(pii it:wl){
			int i=it.first,j=it.second;
			nw[i]++,nw[j]++;
			if(nw[i]<f[i]+n)lt+=i;
			if(nw[j]<f[j]+n)lt+=j;
			cnt--;
		}
		wl.clear();
	}
	fio<<k;
	return 0;
}
```
介绍一个函数：`std::minmax`，后面放两个参数或者 `std::initializer_list`，返回值是一个 `std::pair`，`.first` 表示较小的数，`.second` 表示较大的数。程序里使用是防止 $(3,1)(1,3)$ 这种情况不被去重。

---

## 作者：洛璟 (赞：5)

这道题目属实把我逼疯了……我就这样做了一个下午qwq

## Translation：

有 $N$ 个人打比赛，每个人都要和其他 $N-1$ 个人打一场，但每天只能打一场比赛，每个人按照给定顺序和对应的选手打比赛，求最少多少天能打完比赛？

如果没法打，输出-1.

## Solution：

那么我们看一眼题目，发现要按顺序打架，还要一个一个打，~~很难~~想到拓扑排序……

好吧其实很难说清楚到底是怎么想到拓扑的，反正灵光一闪就想到了。（确信

~~写多了自然就有感觉了（逃~~

那么假设我们~~灵光一闪~~想到了拓扑，不难发现……这个存图……非常毒瘤……是的，这东西会把一个人存到精神失常。

对，如果你愿意用奇怪的邻接表、前向星捣鼓半天怎么插入，或者开四维数组直接暴力插，显然很简单。

~~但也很繁琐，捣鼓半天你甚至很难搞懂这玩意到底代表了甚么~~

但是，我们可以对给出的一组数据，像哈希一样进行“加密”，也就是用一个特别的算式去换算这个数对，使其变成一个数字，也就是给他们一个独一无二的编号，重新标号，方便存图。

那么直接上代码，更多详情请咨询代码注释：

```cpp
#include<bits/stdc++.h>
#define re register 
using namespace std;
vector<int> v[1500000];//由于换算最高能到达1000*1001+1000，故开这么大，但不会炸
queue<int> q;
queue<int> t;
int n, a[1010][1010], r[1500000], ans;
bool fg[1500000];
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int hs(int x, int y)//对，这就是那个奇怪的换算，这样换算可以保证每一组数据两两不同，且易证。
{
    return x * (n + 1) + y;
}
int main()
{
    n = read();
    for (re int i = 1;i <= n;++i)
    {
        for (re int j = 1;j < n;++j)
        {
            a[i][j] = read();
        }
        for (re int j = 1;j < n - 1;++j)
        {
            int x = a[i][j];
            int y = i;
            int c = i;
            int d = a[i][j + 1];
            if (x > y) swap(x, y);
            if (c > d) swap(c, d);
            v[hs(x, y)].push_back(hs(c, d));//存图
            r[hs(c, d)]++;//存储 入度
        }
    }
    for (re int i = 1;i <= n;++i)
    {
        for (re int j = 1;j < n;++j)
        {
            int x = a[i][j];
            int y = i;
            if (x > y) swap(x, y);
            if (r[hs(x, y)] == 0 && fg[hs(x,y)]==0) q.push(hs(x, y)), t.push(1),fg[hs(x,y)]=1;
        }//这里的if是为了避免重复加入同一个节点
    }
    int tot = 0;
    while (!q.empty())//普通的拓扑排序
    {
        int tmp = q.front();
        q.pop();
        int tm = t.front();
        t.pop();
        tot++;
        ans = max(ans, tm);
        for (int i = 0;i < v[tmp].size();i++)
        {
            r[v[tmp][i]]--;
            if (r[v[tmp][i]] == 0)
            {
                q.push(v[tmp][i]);
                t.push(tm + 1);
            }
        }

    }
    if (tot != n * (n - 1) / 2)//这是判断是否达到标准，正常情况下应该打n*(n-1)/2场
    {
        printf("-1");
    }
    else
    {
        printf("%d", ans);
    }
    return 0;
}
```


---

## 作者：small_john (赞：3)

## 思路

我们可以把题目转换一下。

由于有比赛顺序的约束，我们记录当前第 $i$ 个人该和 $f_i$ 中的第 $now_i$ 个人打比赛。

两个人 $i,j$ 可以打比赛当且仅当 $f_{j,f_{i,now_i}}=i$。

如果没有人可以打比赛就输出 `-1`。

值得注意的是每个人每天只能打一场比赛，所以再开一个数组 $v$，$v_i$ 表示第 $i$ 个人是否打过比赛。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int n,a[N][N],now[N],ans,v[N];
bool ok()
{
	for(int i = 1;i<=n;i++)
		if(now[i]<n)
			return 1;
	return 0;
}
signed main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1,x;j<n;j++)
			cin>>a[i][j];
		now[i] = 1;
	}
	while(ok())
	{
		bool vis = 1;
		memset(v,0,sizeof v);
		for(int i = 1;i<=n;i++)
		{
			int op = a[i][now[i]];
			if(a[op][now[op]]==i&&!v[op]&&!v[i])
				now[i]++,now[op]++,vis = 0,v[i] = 1,v[op] = 1;
		}
		if(vis)//没找到
			return cout<<-1,0;
		ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happy_zero (赞：2)

[题目传送门。](https://www.luogu.com.cn/problem/AT_abc139_e)

来个最简单的做法。拿个“指针”记录一下每个人都比到第几个（希望的比赛顺序）了，然后一天天模拟并枚举 $i$，若当前 $i$ 希望和 $j$ 比，$j$ 也希望和 $i$ 比那么他俩就一定能比，对数加一，直到对数等于总轮数就跳出循环。

但是这样会被卡到 $O(n^3)$，考虑优化。由于只有前一轮“指针”被更新这一轮才会产生新的答案，不然之前早贡献了，所以可以拿个队列记录下上一轮哪几个被更新了，这次才遍历，因为这样 $a$ 数组的一个位置只会进队一次，所以时间复杂度是 $O(n^2)$。

记得特判一下无解（没配对完但队列为空）。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
inline int read() {
    int w = 1, q = 0;
    char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-')
        w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
    return w * q;
}
int n, a[N][N], st[N], e[N][N];
//st[i] 表示第 i 个人当前需要配对的位置
//e[i][j] = 1 则说明 i 想要和 j 配对，反之亦然
int head = 1, tail, q[N * N * 2];
//这里要遍历队列所以我手写队列了
int main() {
	n = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < n; j++)
			a[i][j] = read();
	for (int i = 1; i <= n; i++)
		st[i] = 1, q[++tail] = i;//第一轮所有人都可以被更新
	int cnt = 0, day = 0;//cnt 表示配对数（比赛场数）
	for (; cnt * 2 < n * (n - 1) && head <= tail; day++) {
		int ttail = tail;//只更新上一轮的
		//要先把所有设为一，因为有可能正好是上一轮更新过的两两配对就错了
		for (int t = head; t <= tail; t++) {
			int i = q[t];
			int j = a[i][st[i]];
			e[i][j] = 1;
		}
		for (int t = head; t <= ttail; t++){
			int i = q[t]; head++;
			int j = a[i][st[i]];
			if (e[j][i] == 1 && e[i][j] == 1) {
				e[i][j] = e[j][i] = 0;
				cnt++;
				st[j]++, st[i]++;//指向下一个人
				if (st[i] < n) q[++tail] = i;
				if (st[j] < n) q[++tail] = j;
			}
		}
	}
	cout << (cnt * 2 == n * (n - 1) ? day : -1);//记得特判无解
	return 0;
}
```

---

## 作者：RoyWu1207 (赞：2)

# Description

每个人都要以一个特定的顺序与其他人比赛，且每个人每天只可以比一场比赛，问最少比赛的天数为多少，无解输出 $-1$；

# Solution

发现每一组会面都有依赖条件（除第一组外），容易想到拓扑排序。

每一组的依赖条件向本组作一条有向边，通过二维邻接表存储每一组的依赖情况，容易实现。

至于时间复杂度方面，每一组至多 $2$ 条边，共不超过 $2 \times n^2$ 条边，因此拓扑排序部分复杂度是 $O(n^2)$，没有问题。

# AC Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct peo {
    int x, y;
};

vector<peo> V[1001][1001];

int n;
int a[1001][1001], rd[1001][1001], vis[1001][1001];

struct node {
    int x, y;
    long long st;
};

queue<node> q;

long long step = 0;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= n; j++) {
            scanf("%d", &a[i][j]);
            int mini = min(i, a[i][j]), maxi = max(i, a[i][j]);
            int minj = min(i, a[i][j - 1]), maxj = max(i, a[i][j - 1]);
            if (j > 2)
                V[minj][maxj].push_back({ mini, maxi }), rd[mini][maxi]++;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!rd[i][j] && i < j)
                vis[i][j] = 1, q.push({ i, j, 1 });
    while (!q.empty()) {
        node u = q.front();
        q.pop();
        step = max(step, u.st);
        for (peo i : V[u.x][u.y]) {
            int x = i.x, y = i.y;
            rd[x][y]--;
            if (!rd[x][y] && !vis[x][y])
                vis[x][y] = 1, q.push({ x, y, u.st + 1 });
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!vis[i][j] && i < j) {
                printf("-1");
                return 0;
            }
    printf("%d", step);
    return 0;
}
```


---

## 作者：L_zaa_L (赞：2)

## 分析：
用贪心。每次只进行肯定合法的比赛，也就是某两个人正好按顺序都是对方。如果在一轮中找不到这样的比赛，就输出 ```−1```，如果所有玩家该进行的比赛都打完了就输出答案。实现过程中，我们可以用一个数组来记录每个人按顺序应该比的下一个人，假设这个数组是 $now$，那么只要 $a_{a_{i,now_i},now_{a_{i,now_{i}}}}= i$（意思就是 $i$ 按顺序应该比的人也是 $i$ 应该比的人的应该比的人），那么这场比赛一定可以举办，就先举办，并且这两个人今天不能再和其他人比。

## Code
```
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define modj(x) ((x)-=((x)>=MOD)?MOD:0)
#define qmin(x,y) ((x)=min((x),(y)))
#define qmax(x,y) ((x)=max((x),(y)))
using namespace std;
inline ll read(){
	ll t=0,f=0;char v=getchar();
	while(!isdigit(v))f|=(v=='-'),v=getchar();
	while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
inline void write(ll x){
	if(x<0){x*=-1; putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
string s[114514];
int a[1145][1419];
int now[114514];//记录第i个人按顺序应该比的人
int ans;
bool book[114514];
signed main() {
	int n=read();
	FOR(i,1,n){
	now[i]=1;
		FOR(j,1,n-1){
			cin>>a[i][j];
		}
	}
	while(ans<=n*(n-1)/2){//最多n*（n-1）/2 天，否则是不行的
		bool flag=0;
		FOR(i,1,n) book[i]=0;
		FOR(i,1,n){
			if(now[i]!=n){
				flag=1;
				break;
			}
		}//如果每个人都比完了，就直接退出
		if(flag==0){
			cout<<ans;
			return 0;
		}
		ans++;
		FOR(i,1,n){
			if(book[i]==1) continue;
			if(book[a[i][now[i]]]==1) continue;//不能今天比过
			if(a[a[i][now[i]]][now[a[i][now[i]]]]==i){//同上问
				book[i]=1;
				book[a[i][now[i]]]=1;//标记这两个今天不能和其他人比了
				now[a[i][now[i]]]++;
				now[i]++;//按顺序往后延
				continue;
			}
		}
	}
	bool flag=0;
	FOR(i,1,n){//判断无解的
		if(now[i]!=n){
			flag=1;
			break;
		}
	}
	if(flag==1){
		cout<<-1;
		return 0;
	}
	cout<<ans;
   return 0;
}
```

---

## 作者：best_brain (赞：2)

$\qquad$dalao 们写的都是 topsort，本蒟蒻来~~水一篇离谱的模拟~~

$\qquad$很显然，如果当前 $j$ 的对手是 $i$，$i$ 的对手也是 $j$，况且两人在本轮都未进行比赛，那么他们就会相互比赛。我们只需要另开数组记录每个人当前的对手是谁即可，如果可以进行比赛就记录一下。当本轮没有记录，且仍有人还有对手，那么就可判定为无解；否则说明比赛结束。

$\qquad$最坏时间复杂度：$\mathcal{O}(n^2)$

$\qquad$代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1010;
int n;
int mp[maxn][maxn];
int s[maxn];//记录每头牛此时的对手序号
bool f[maxn];//记录每头牛本轮是否进行了比赛

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j < n; j ++) {
            scanf("%d", &mp[i][j]);
        }
        s[i] = 1;
      }
    int ans = 0;
    while(1) {
        memset(f, 0, sizeof f);
        ans ++;
        bool flag = 0;
        for(int i = 1; i <= n; i ++) {
            //mp[i][s[i]]即为i本轮的对手，s[mp[i][s[i]]]为mp[i][s[i]]本轮的对手序号
            if(mp[mp[i][s[i]]][s[mp[i][s[i]]]] == i && !f[i] && !f[mp[i][s[i]]]) {//两头牛互相是对手，且本回合未进行比赛
                f[i] = 1;
                f[mp[i][s[i]]] = 1;
                s[mp[i][s[i]]] ++;
                s[i] ++;//对手序号往后延伸
                flag = 1;
            }
        }
        bool ff = 0;
        for(int i = 1; i <= n; i ++) {
            if(s[i] < n) {
                ff = 1;//还有牛未打完比赛
                break;
            }
        }
        if(!flag && ff) {//无法更新且还有牛未打完，无解
            puts("-1");
            break;
        }
        if(!ff) {//所有牛都打完比赛了
            printf("%d", ans);
            break;
        }
    }
    return 0;
}
```


---

## 作者：_7Mr (赞：1)

# 思路
我们记一个 $sum$ 数组，用来存储第 $i$ 个人打到哪里了，$sum$ 初始化全部为 $1$ 因为都还在打第 $1$ 个人。

对于每一天，我们先检查一下，看看 $sum$ 数组是否全部为 $n$。如果全部为 $n$ 说明比赛全部已经打完了，那么直接输出答案。如果，没有那么我们枚举每一个人。如果这个人这天已经打过比赛或者已经打完比赛了，那么我们就暂时不需要这个人了。

如果，这个人没有上述的两种情况，就看他的 $sum_i$ 打到哪里了，如果打到的这个人，当前要打的不是我，那么就说明我和这个人打的时间在后面，退出此次循环。如果是，那么就将他们要打的人全部往后移。

现在我们就差怎么判断不行了，如果此次的循环，我们一次操作的没有执行，说明全部不符合，输出 $-1$ 结束程序。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
const int maxn=1e3+5;
int n;
int a[maxn][maxn],sum[maxn];
bool Inspect() {//检查，判断是否打完比赛
	bool flag=0;
	for(int i=1; i<=n; i++) {
		if(sum[i]==n) flag=1;
		else {
			flag=0;
			break;
		}
	}
	if(flag) return 1;
	else return 0;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1; i<=n; i++) {
		sum[i]=1;//初始化，都还在打第一个人
		for(int j=1; j<n; j++) {
			cin>>a[i][j];
		}
	}
	int ans=0;
	while(true) {
		if(Inspect()) {//判断
			cout<<ans<<endl;
			return 0;
		}
		int flag[maxn];//今天是否打过比赛
		memset(flag,0,sizeof(flag));
		int flagg=0;
		for(int i=1; i<=n; i++) {
			int q=a[i][sum[i]];
			int p=a[q][sum[q]];
			if(p!=i) continue;//这个人当前要打的人不是我
			if(flag[i]) continue;//今天已经打过比赛
			if(flag[q]) continue;
			if(sum[i]==n) continue;//我已经打完比赛了
			if(sum[q]==n) continue;
			sum[i]++;//都没有，要打的人全部往后移
			sum[q]++;
			flag[i]=1;//标记今天打过比赛了
			flag[q]=1;
			flagg=1;//这次循环是否操作
		}
		if(!flagg){//一次操作都没执行
			cout<<-1<<endl;
			return 0;
		}
		ans++;//天数加1
	}
	return 0;
}

```

---

## 作者：joyslog (赞：0)

[ABC139E](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc139_e)

$n$ 个人，每两个人之间都有一场比赛，故共 $\frac {n(n -1)} {2}$ 场比赛。

每个人都有自己想要的比赛顺序。例如 $x$ 要求按顺序与 $a_{x,1},a_{x,2},\cdots a_{x,n-1}$ 比赛。而且每个人每天只可以比一场比赛。

问最少比赛的天数为多少。若无解，输出 $-1$ 。

$n \leq 1000$

### 题解

因为每个人都只能取当前的对手进行比赛，所以要让每一天都减少至少一场比赛，我们必须让每一天能安排的比赛都安排上。

所以暴力枚举每一天，考察每个元素是否满足比赛条件，即当前其对手的对手是自己。时间复杂度 $\mathcal{O}(n^3)$ 。

考虑优化。我们枚举到第 $i$ 天时，不需要枚举所有元素。这是因为考虑第 $i-1$ 天已经把能安排的比赛全安排完了，那现在能安排的比赛，必然要从前一天安排过的人中产生，因为只有他们的当前对手更新了。

这样，设每一轮安排了 $p$ 场比赛，则共有 $\mathcal{O}(\frac{n^2}{p})$ 轮。每一场的枚举也只有 $\mathcal{O}(p)$ 的复杂度。则时间复杂度为 $\mathcal{O}(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {...}
char buf[50];
inline void write(ll x) {...}

const int MAX_N = 1005;
int n, cnt, cntt, a[MAX_N][MAX_N], lst[MAX_N], p[MAX_N];
bool ban[MAX_N];

int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i][0] = 1;
		for(int j = 1; j <= n - 1; j++)
			a[i][j] = read();
		p[++cntt] = i;
	}
	for(int k = 1; k <= n * (n - 1) / 2; k++) {
		cnt = 0;
		bool flag = false;
		for(int c = 1; c <= cntt; c++)
			ban[p[c]] = false;
		for(int c = 1; c <= cntt; c++) {
			int i = p[c];
			int aim = a[i][a[i][0]];
			if(a[i][0] >= n || a[aim][0] >= n || ban[i] || ban[aim])	continue;
			if(a[aim][a[aim][0]] == i) {
				a[aim][0]++;
				a[i][0]++;
				lst[++cnt] = i;
				lst[++cnt] = aim;
				ban[i] = ban[aim] = flag = true; 
			}
		}
		cntt = cnt;
		for(int c = 1; c <= cnt; c++) 
			p[c] = lst[c];
		if(!flag) {
			for(int i = 1; i <= n; i++)
				if(a[i][0] != n) {
					write(-1), putchar('\n');
					return 0;
				}
			write(k - 1), putchar('\n');
			return 0;
		}
	}
	write(n * (n - 1) / 2), putchar('\n');
	return 0;
}
```



---

## 作者：Erica_N_Contina (赞：0)

# [ABC139E] League

## 题面翻译

$n\ (3\ \leq\ n\ \leq\ 1000)$ 个人进行 $\frac {n(n -1)} {2}$ 场比赛，每个人都要以一个特定的顺序与其他人比赛。

且每个人每天只可以比一场比赛，问最少比赛的天数为多少，无解输出 $-1$ 。

$A_{i,\ j} \ (1\ \leq\ A_{i,\ j}\ \leq\ n,A_{i,\ j}\ \neq\ i)$ 表示选手 $i$ 的第 $j$ 次比赛的对手。


## 算法解说：拓扑排序

在图论中，拓扑排序（Topological Sorting）是一个有向无环图（DAG, Directed Acyclic Graph）的所有顶点的线性序列。且该序列必须满足下面两个条件：

- 每个顶点出现且只出现一次。

- 若存在一条从顶点 A 到顶点 B 的路径，那么在序列中顶点 A 出现在顶点 B 的前面。

**有向无环图（DAG）才有拓扑排序**，非 DAG 图没有拓扑排序一说。

一个 DAG 图，那么如何写出它的拓扑排序呢？这里说一种比较常用的方法：

1. 从 DAG 图中选择一个入度为 $0$ 的点并输出。
2. 从图中删除该点和所有以它为起点的有向边。

重复 1 和 2 直到当前的 DAG 图为空或当前图中不存在无前驱的点为止。后一种情况说明有向图中**必然存在环**。



## 解题思路

我们假设i选手和其他选手比赛的顺序是 $i_1,i_2,i_3,i_4$，那么当 $i$ 要和 $i_3$ 选手比赛时，要求 $i$ 已经和 $i_1,i_2$ 比赛过了。

所以我们考虑一件事情：如果**我们把比赛顺序看作有向图**，如果图中**有环的话肯定无解**。这个很显然。

我们沿着这个思路考虑下去——我们将比赛顺序用有向图存起来，每一场比赛都可以用一个二元组表示 $(x, y)$ 成一个节点，节点向节点连边表示顺序。

对于节点，我们用二元组肯定是不行的，毕竟下标不可能是一个二元组对吧，所以我们建立一个 hash（或者说是二元组与整数之间的一个一一映射），用映射值作为下标。

```C++
int has(int a,int b){
	if(a>b)swap(a,b);//将a,b和b,a作为一种情况考虑
	return a*n+b;
}
```




当每次要进行比赛时，只有入度为 $0$ 的点（比赛）才可以进行，因为入度为 $0$，结合之前的存图方式，就说明这个点 $i$（假设节点在映射之前是 $<i,i_j>$）已经和 $i_1\sim i_{j-1}$ 比赛过了，可以与 $i_j$ 比赛。

在仔细观察一下，可以发现答案就是最长链的长度（当然无解时除外）。

证明很简单，我们把有向图里的每一条链都拎出来，头部对齐，因为入度为 $0$ 的节点（比赛）肯定都可以在同一天进行完，所以我们就假设所有链同时进行。那么在最长链走完之前，其他链都走完了。当最长链走完了，那么 $\frac {n(n -1)} {2}$ 场比赛也就结束了。

## Code

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=1e6+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

vector<int> e[N];
queue<int> q;
int n,ans,cnt[N],t[N],to,pre;

void add(int a,int b){
	e[a].push_back(b);
	cnt[b]++;
}
int has(int a,int b){
	if(a>b)swap(a,b);//将a,b和b,a作为一种情况考虑
	return a*n+b;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=2;j<=n;j++){
			pre=to;
			cin>>to;
			if(j>2)add(has(i,to),has(i,pre));
		}
	}
	for(int i=1;i<=n*n;i++){
		if(!cnt[i])q.push(i);
		t[i]=1;
	}
	while(q.size()){
		int u=q.front();q.pop();
		//ans=max(ans,t[u]);
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			cnt[v]--;
			if(!cnt[v]){
				q.push(v);
				t[v]=t[u]+1;
				
			}
		}
	}
	for(int i=1;i<=n*n;i++){
		if(cnt[i]){
			cout<<-1<<endl;return 0;
		}
		ans=max(ans,t[i]);
	}
	cout<<ans<<endl;
	
	return 0;
}

```




---

## 作者：watcher_YBH (赞：0)

# 思路：
由于本题的数据较小，时限宽裕，所以我们可以考虑使用暴力过掉。

先将第 $i$ 个人需要对战的人存入第 $i$ 个队列，在依次枚举每一个时间，如果可以组建多组比赛，则在求解过程中对应的比赛个数增加，大于最大比赛数就退出循环，如果没有，就直接输出 $-1$。
# 代码：
```
#include<bits/stdc++.h>
#define int long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e3+5;
int n,z;
int t[MAX];
int a[MAX][MAX];
queue<int> p[MAX];
signed main(){
	cin>>n;
	for(int i = 1; i<=n; i++)
		for(int j = 1; j<n; j++)
			cin>>a[i][j],p[i].push(a[i][j]);//存入队列
	for(int i = 1; i<=n*(n-1); i++){//时间
		int k = 0;//比赛数
		memset(t,0,sizeof(t));
		for(int j = 1; j<=n; j++){
			int x = p[j].front();
			if(p[x].front() == j && !t[j] && !t[x])//不相同，并且双方空闲
				t[j] = t[x] = 1,k+=2,p[j].pop(),p[x].pop();//比赛总数增加
		}
		if(k == 0){cout<<-1; return 0;}//没有比赛输出-1
		i += k-1,z++;
	}
	cout<<z;
	return 0;
}


```


---

## 作者：_segmenttree (赞：0)

### 思路

我们可以把每场比赛当作一个点。而每一个人的所有比赛就是一条链，依他所
希望的比赛顺序的顺序建链。所有链建好后便形成一张图，完成这场比赛的最
小时间就是从入度为零的点到任意点的最长路。至于不能构建便是有环的情况，因为那样分不清谁先谁后。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ch,cnt,js,c[1010][1010],jl,h[1000010],rd[1000010],dp[1000010],ans=-1;
queue<int>q;
struct lj {
	int nx,v;
} a[1000010];
void add(int u,int v) {
	cnt++;
	a[cnt].nx=h[u],a[cnt].v=v;
	h[u]=cnt;
	rd[v]++;
}
void pd() {
	for(int i=1; i<=js; i++)
		if(rd[i]==0) 
			q.push(i);
	while(!q.empty()) {
		int nx=q.front();
		q.pop();
		for(int i=h[nx]; i; i=a[i].nx) {
			int v=a[i].v;
			dp[v]=max(dp[v],dp[nx]+1);
			rd[v]--;
			if(rd[v]==0) {
				q.push(v);
				ans=max(ans,dp[v]);
			}
		}
	}
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		jl=0;
		for(int j=1; j<n; j++) {
			scanf("%d",&ch);
			if(c[i][ch]==0)
				c[i][ch]=c[ch][i]=++js;
			if(jl!=0) add(jl,c[i][ch]);
			jl=c[i][ch];
			dp[jl]=1;
		}
	}
	pd();
	for(int i=1;i<=js;i++)
		if(rd[i]!=0){
			cout<<-1;
			return 0;
		}
	cout<<ans;
	return 0;
}
```

---

