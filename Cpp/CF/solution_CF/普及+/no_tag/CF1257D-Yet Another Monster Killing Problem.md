# Yet Another Monster Killing Problem

## 题目描述

你需要操作 $m$ 个英雄去打败 $n$ 只怪物，每个英雄的力量值为 $p_i$，可以打败 $s_i$ 只怪物；每只怪物的力量值为 $a_i$。

当新的一天开始时，你可以选择其中 $1$ 个英雄去打怪（一个英雄可以选择多次）。若在之前已有 $k$ 只怪物被打败，这个英雄将挑战第 $k+1$ 只怪物，此时有两种情况：

1、英雄力量 $<$ 怪物力量，则英雄撤退，这一天结束。

2、英雄力量 $\geqslant$ 怪物力量，怪物被打败。继续挑战下一只怪物。当 $n$ 只怪物全部被打败，或该英雄已打败的怪物数量为 $s_i$ 时，这一天结束。

你的任务是计算出打败所有怪物所需要的最小天数。



------------

## 样例 #1

### 输入

```
2
6
2 3 11 14 1 8
2
3 2
100 1
5
3 5 100 2 3
2
30 5
90 1
```

### 输出

```
5
-1
```

# 题解

## 作者：F_Mu (赞：6)

**题意**：

有$n$个怪物，每个怪物有攻击力$a_i$点；有$m$个英雄，每个英雄有攻击力$p_i$点，耐力$s_{i}$点。

怪物需要被依次杀死(按输入顺序)。

每一天可以挑选一个英雄去杀怪物，他可以杀死的怪物攻击力小于等于他本身(即$a\leq p$)，每天最多可以杀死$s$个怪物。(每个英雄可以使用任意次)

问最少需要多少天可以杀死所有怪物(不能则输出$-1$)。

**分析**：

$(1)$我们找到怪物的最大攻击力和英雄的最大攻击力，判断是否要输出$-1$。

$(2)$将英雄按攻击力$p$值排序，我们可以发现对于英雄$b[i]$而言，如果对于$i<j\leq m$，且有$b[i].s<b[j].s$，我们可以选择英雄$j$，而不是英雄$i$，那么我们可以把$b[i].s$替换为$b[j].s$（意思为选择英雄$i$时选择英雄$j$）。

$(3)$因此我们进行后缀操作将$b[i].s$改为英雄$i$~$n$中最大的耐力值，以便进行下一步。

$(4)$对于某个怪物而言，我们可以找到一个英雄，他的攻击力刚好大于等于该怪物（二分）。我们上一步将该英雄的耐力改为了后缀最大值，那么我们便选择这个英雄。

$(5)$我们从第一天开始，枚举每一个怪物，找到当前天我们可以杀死最多怪物的英雄，如果对于某个怪物而言，杀死他的人的耐力（我们进行了后缀操作）不足以支撑该天，我们将该怪物放到下一天，并重复操作，直至杀死所有怪物。因此我们需要保存的量有：当前的天数$k$，昨天杀死的最后一只怪物的编号$last$，今天所能杀死的最多怪物数（表现为所需要的最小耐力）$minn$。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
using namespace std;
const int maxn = (ll) 2e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;

struct node {
    int p, s;

    bool operator<(const node &b) {//用做排序
        return p < b.p;
    }
} b[maxn];

bool cmp(const node &x, int y) {//用做二分
    return x.p < y;
}

int a[maxn];

int main() {
    start;
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int maxa = 0, maxs = 0;//用做判-1
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            maxa = max(maxa, a[i]);
        }
        int m;
        cin >> m;
        for (int i = 1; i <= m; ++i) {
            cin >> b[i].p >> b[i].s;
            maxs = max(maxs, b[i].p);
        }
        if (maxa > maxs) {
            cout << -1 << '\n';
            continue;
        }
        sort(b + 1, b + m + 1);
        for (int i = m - 1; i >= 1; --i)//后缀操作
            b[i].s = max(b[i].s, b[i + 1].s);
        int k = 1;
        int last = 0;
        int minn = inf;
        for (int i = 1; i <= n; ++i) {
            int t = lower_bound(b + 1, b + m + 1, a[i], cmp) - b;//刚好能杀死该怪物的英雄编号
            minn = min(b[t].s, minn);//今天所需要的最小耐力
            if (minn + last < i) {//将这只怪物放到明天杀
                minn = b[t].s;
                ++k;
                last = i - 1;
            }
        }
        cout << k << '\n';
    }
    return 0;
}
```

 本场比赛$D$和$E$惨痛教训：玩后缀一定要注意边界！！！ 

---

## 作者：thjkhdf12 (赞：2)

思路为贪心+二分，每天选择能打死最多怪的英雄进入地牢，而为了击败最多怪，枚举所有怪物，对于每个怪物二分查找耐力高于或等于当天计划击败数量的战斗力最强的英雄，如果无法找到，说明今天已经无法击败这个怪物，重置天数开始查找

如果遇到重置天数后也找不到能击败它的英雄的怪物，说明没有英雄可以战胜它，输出-$1$，当然也可以开始先扫一遍来确认一下有没有怪的战斗力高到没有英雄打得过

其它具体实现见代码及注释

用时92ms，相对较快，手写二分，不用vector和pair，手写最大值查询应该能更快

都9102年了，cin/cout sync+tie了还420ms呢，早就死了

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
 
const int INF = 0x3f3f3f3f;
const int maxn = 200010;
int a[maxn];
int mon[maxn];
int ed[maxn];
int maxh[maxn];
int n, m;
vector<pair<int, int> >temp;
 
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        temp.clear();
        scanf("%d",&n);
        for (int i = 1; i <= n; i++)
        {
           scanf("%d",&mon[i]);
        }
        scanf("%d",&m);
        for (int i = 1; i <= m; i++)
        {
            int a, b;
            scanf("%d%d",&a,&b);
            temp.push_back(pair<int, int>(b, a));
            //因为要按耐力值排序，所以反过来做pair
        }
        sort(temp.begin(), temp.end());
        for (int i = 0; i < m; i++)
        {
            a[i + 1] = temp[i].second;
            ed[i + 1] = temp[i].first;
        }
        {
        int maxh = *max_element(a + 1, a + 1 + m);
        int maxm = *max_element(mon + 1, mon + n + 1);
        if (maxh < maxm)
        {
            //有怪谁也打不过，AK无望
            printf("-1\n");
            continue;
        }
        }
        maxh[m]=a[m];
        for(int i=m-1;i>0;i--)
        {
            maxh[i]=max(maxh[i+1],a[i]);
            //预处理的前缀和，maxh[i]表示i到m中战斗力最强的英雄的战斗力
        }
        int d = 0;    //当天击败数量
        int ans = 1;
        int maxp = -INF;	//每天计划中最强的怪
        for (int i = 1; i <= n; i++)
        {
            d++;
            maxp = max(maxp, mon[i]);    //目前为止今天计划中最强的怪
            int val = lower_bound(ed + 1, ed + 1 + m, d) - ed;    //当前耐力还能继续打下去的英雄
            //lower_bound自带二分
            int maxq = -INF;
            if (val < m + 1) maxq = maxh[val];    //耐力值足够，在当前耐力值足够的英雄里找最能打的
            if (val == m + 1 || maxq < maxp)
            {    //没有耐力足够的英雄打的过计划今天要打的怪里最强的
                ans++;
                d = 1;    //用战力比这个怪强的英雄K掉这个怪
                maxp = mon[i];    //这个怪安排到下一天
                //进入下一天
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Lyccrius (赞：1)

判断能否杀死所有怪兽很简单，比较怪兽的最大力量值 $\max a_i$ 和英雄的最大力量值 $\max p_i$ 即可。

注意，英雄的选择决策权在你手中，而怪兽需按输入顺序依次被杀。

为了方便决策，我们将所有英雄按力量值 $p$ 从小到达排序。对于两个英雄 $i, j (i \lt j)$，若 $p_i \lt p_j$ 且 $s_i \lt s_j$，则所有与 $i$ 有关的决策都可以被 $j$ 替换。这是利用了单调队列的思想。

> 当一个人比你小 ~~（持久）~~ 还比你强时，那你就打不过他了。

因此在排序过后，我们将每个英雄的耐力 $s_i$ 更新为其后缀的最大值，即 $\max_{i \le j \le m} s_j$。

对于一个怪物 $i$，我们找到能够杀死该怪物的第一个英雄，即 $\min_{a_i \le p_j} j$。根据单调性，$j \sim m$ 任意一名英雄都能够杀死该怪物。在上一步中，我们已经将 $s_j$ 更新为 $j \sim m$ 英雄中 $s$ 的最大值，那么耐力为 $s_j$ 的英雄就是对于当前怪物的最优决策。

由于问题的重点在于杀死所有怪物的天数，所以每个怪物具体是哪个英雄杀的并不重要，因此不需要根据上一步的 $s_j$ 还原英雄。

枚举每个怪物，重复上面的操作，并维护当前天能够杀死怪兽的最大数量，即当前天每次找到英雄的耐久度最小值。直至当前天能够杀死的数量与当前天之前已经杀死的数量之和将当前怪兽排除在外时，跳转到下一天。

```
#include <cstdio>
#include <algorithm>

const int inf = 0x3f3f3f3f;
const int mod = 1000000007;
const int maxN = 2e5 + 10;

int t;
int n;
int a[maxN];
int m;

struct Hero {
    int p, s;

    bool operator<(Hero other) const {
        return p < other.p;
    }

	bool operator<(int other) const {
		return p < other;
	}
} hero[maxN];


int main() {
    scanf("%d", &t);
    while (t--) {
        int maxA = 0, maxP = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            maxA = std::max(maxA, a[i]);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &hero[i].p, &hero[i].s);
            maxP = std::max(maxP, hero[i].p);
        }
        if (maxA > maxP) {
            printf("-1\n");
            continue;
        }
        std::sort(hero + 1, hero + m + 1);
		for (int i = m - 1; i >= 1; i--) hero[i].s = std::max(hero[i].s, hero[i + 1].s);
        int date = 1;
        int killed = 0;
        int minS = inf;
        for (int i = 1; i <= n; ++i) {
            int fight = std::lower_bound(hero + 1, hero + m + 1, a[i]) - hero;
            minS = std::min(minS, hero[fight].s);
            if (minS + killed < i) {
                minS = hero[fight].s;
                date++;
                killed = i - 1;
            }
        }
       printf("%d\n", date);
    }
    return 0;
}
```

---

## 作者：YGB_XU (赞：1)

看到楼下都用二分的做法，那我就来分享一个离散化~~巨大码量~~的做法吧~

这个做法的时间复杂度主要是卡在了快排上。

我们在对所有怪物以及英雄的能力值进行离散化后，维护一个数组 $maxs_i$ 表示能打能力值为 $i$ 怪物的英雄中，耐力最大的那个耐力值。

那么就可以用贪心的思路从头到尾扫描怪物，并记录这一天累计打到的怪物中能力值最大的那个能力值，以及累计打了多少怪物，如果打的怪物数要大于刚才预处理的耐力值，则说明没人能打这么多，进入下一天。

详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int NR=2e5+5;
int n,m;
int maxs[NR];
struct Monster{
	int p,id,lsh;
}a[NR];
struct Hero{
	int p,s,id,lsh;
}h[NR];

inline bool cmpm1(Monster x,Monster y){//第一遍排序怪物按能力值
	if(x.p!=y.p) return x.p<y.p;
	return x.id<y.id;
}

inline bool cmpm2(Monster x,Monster y){//离散化后还要按输入顺序还原怪物
	return x.id<y.id;
}

inline bool cmph(Hero x,Hero y){
	if(x.p!=y.p) return x.p<y.p;
	if(x.s!=y.s) return x.s>y.s;
	return x.id<y.id;
}

int sz;
inline void lisanhua(){
	sz=0;//多组数据要清零
	sort(a+1,a+n+1,cmpm1);
	sort(h+1,h+m+1,cmph);
	int posm=1,posh=1,last=-2e9;
	while(posm<=n||posh<=m){//同时去比较两方剩下的中能力的最小值
		if(posm>n){
			if(h[posh].p!=last){
				last=h[posh].p;
				h[posh].lsh=++sz;
			}else{
				h[posh].lsh=sz;
			}
			posh++;
		}else if(posh>m){
			if(a[posm].p!=last){
				last=a[posm].p;
				a[posm].lsh=++sz;
			}else{
				a[posm].lsh=sz;
			}
			posm++;
		}else{
			if(a[posm].p<h[posh].p){
				if(a[posm].p!=last){
					last=a[posm].p;
					a[posm].lsh=++sz;
				}else{
					a[posm].lsh=sz;
				}
				posm++;
			}else{
				if(h[posh].p!=last){
					last=h[posh].p;
					h[posh].lsh=++sz;
				}else{
					h[posh].lsh=sz;
				}
				posh++;
			}
		}
	}
	sort(a+1,a+n+1,cmpm2);
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].p);
			a[i].id=i;
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&h[i].p,&h[i].s);
			h[i].id=i;
		}
		lisanhua();
		int pos=1;
		bool flag=false;
		for(int i=1;i<=sz;i++){//预处理maxs
			while(h[pos].lsh<i) pos++;
			if(pos>m){//有无法打败的怪物则直接退出，输出-1
				printf("-1\n");//可以思考这里为什么不用另外全扫一遍来特判
				flag=true;
				break;
			}
			maxs[i]=h[pos].s;
		}
		for(int i=sz-1;i>=1;i--) maxs[i]=max(maxs[i],maxs[i+1]);//这里是关键，有能力值和耐力都更大的英雄当然首选
		if(flag) continue;
		int now=-2e9,len=0,ans=1;//now表示记录的能力最大值，len表示打的怪物数
		for(int i=1;i<=n;i++){//开始贪心处理怪物
			now=max(now,a[i].lsh);
			len++;
			if(maxs[now]>=len) continue;
			ans++;
			now=a[i].lsh,len=1;//新一天的初始化
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：B_Qu1e7 (赞：1)

思路：枚举$/$二分每天最多能杀多少怪

用$hur$数组记录连续杀$X$只怪时每只怪兽的最大血量。注意倒序更新$hur[i]=max(hur[i],hur[i+1])$。

枚举做法：（较容易，实测较慢）
```
#include<cctype>
#include<cstdio>
#include<algorithm>
#define R register
using namespace std;
int T,N,A[200005],M,P,S,k,hur[200005],ans,now,mx;
template<class T>inline void read(R T &m)
{
	m=0;
	R char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(T);
	while(T--)
	{
		read(N);
		k=1,ans=0;
		for(R int i=1; i<=N; ++i)
		{
			hur[i]=0,
			read(A[i]);
		}
		read(M);
		for(R int i=1,tmp; i<=M; ++i)
		{
			read(P),read(S),
			hur[S]=max(hur[S],P);
		}
		for(R int i=N-1; i; --i)
		{
			hur[i]=max(hur[i],hur[i+1]);//更新hur
		}
		while(k<=N)
		{
			now=k,mx=0;
			while(now<=N&&hur[now-k+1]>=max(A[now],mx))
			{
				mx=max(A[now],mx),
				++now;
			}
			if(k^now)k=now,++ans;//这一天有杀怪
			else//杀不动，不行
			{
				puts("-1");
				break;
			}
		}
		if(k>N)//杀完了
		{
			printf("%d\n",ans);
		}
	}
}
```
二分做法：（较复杂，但实测较快
```
#include<cctype>
#include<cstdio>
#define R register
int T,N,A[200005],M,P,S,k,hur[200005],ans,am,pm,l,r,mid;
template<class T>inline void read(R T &m)
{
	m=0;
	R char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
inline bool check(R int kill)
{
	for(R int i=k; i<=k+kill-1; ++i)
	{
		if(A[i]>hur[kill])//有一个怪的血量超过了连续杀kill个怪能承受的最大血量
		{
			return 0;//不行
		}
	}
	return 1;
}
int main()
{
	read(T);
	while(T--)
	{
		read(N);
		k=1,ans=am=pm=0;
		for(R int i=1; i<=N; ++i)
		{
			hur[i]=0,
			read(A[i]),
			am=A[i]>am?A[i]:am;
		}
		read(M);
		for(R int i=1,tmp; i<=M; ++i)
		{
			read(P),read(S),
			pm=P>pm?P:pm,
			hur[S]=P>hur[S]?P:hur[S];
		}
		if(am>pm)//怪最大血量>最大承受量
		{
			puts("-1");
			continue;
		}
		for(R int i=N,mx=0; i; --i)
		{
			if(mx<hur[i])mx=hur[i];
			hur[i]=mx;
		}
		while(k<=N)
		{
			l=1,r=N-k+1;
			while(l<r)
			{
				mid=(l+r>>1)+1;
				if(check(mid))
				{
					l=mid;
				}
				else
				{
					r=mid-1;
				}
			}
			k+=l;//加上这一天的杀怪数
			++ans;
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：chiyanfeng (赞：0)

首先贪心预处理，用 $b_i$ 记录一天内可以消灭 $i$ 只怪兽的最大力量。

我们可以考虑：力量 $5$ 可以消灭 $3$，力量 $8$ 可以消灭 $3$，那么 $8$ 更好，力量 $5$ 消灭 $3$ 没有存在的意义了；另外力量 $6$ 可以消灭 $2$，力量 $8$ 可以消灭 $3$，那么 $b=8$ 更好，力量 $6$ 消灭 $2$ 没有存在的意义了。

综上所述，预处理是要记录能消灭 $i$ 只怪兽英雄的最大力量是多少。显而易见，这个 $b$ 数组非严格下降。

之后线性扫描，每一轮扫描尽最大力量在 $b$ 范围内的最大天数，即 $b[j]\geq \max \limits_{i+1 \le k \le i+j} \{ a_k \}$, 意味着从 $i+1$ 开始的连续 $j$ 只怪兽可以一天内打掉，答案加 $1$。

如果某个怪兽打不了，就设置答案为 $-1$ 并 `break`。  

复杂度为 $O(\sum{n}+\sum{m})$。

程序如下：
```cpp
// Problem: Yet Another Monster Killing Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1257D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, a[N], p[N], s[N];
int b[N];  // b[i]表示，一天内可以消灭i只怪兽的最大力量
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  cin >> m;
  memset(b + 1, 0, sizeof(int) * n);
  for (int i = 1; i <= m; i++)
    cin >> p[i] >> s[i], b[s[i]] = max(b[s[i]], p[i]);
  for (int i = n - 1; i >= 1; i--) b[i] = max(b[i], b[i + 1]);  // b数组单调不升
  int ans = 0, i = 0;
  while (i <= n) {
    ans++;
    int j = 1, t = 0;
    while (i + j <= n) {
      t = max(t, a[i + j]);
      if (b[j] >= t)
        j++;
      else
        break;
    }
    if (j == 1) {
      ans = -1;
      break;
    }
    i = i + j - 1;
    if (i == n) break;
  }
  cout << ans << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) solve();
  return 0;
}
```



[AC记录](https://codeforces.com/problemset/submission/1257/286680583)

---

