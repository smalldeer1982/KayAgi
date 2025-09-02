# Sharky Surfing

## 题目描述

Mualani 喜欢在她的大鲨鱼冲浪板上冲浪！

Mualani 的冲浪路径可以用一个数轴来表示。她从位置 $1$ 开始，路径的终点是位置 $L$。当她处于位置 $x$ 且跳跃能力为 $k$ 时，她可以跳到区间 $[x, x+k]$ 内的任意整数位置。最初，她的跳跃能力为 $1$。

然而，她的冲浪路径并不完全平坦。她的路径上有 $n$ 个障碍物。每个障碍物由一个区间 $[l, r]$ 表示，意味着她不能跳到区间 $[l, r]$ 内的任何位置。

在路径上还有 $m$ 个能量提升点。第 $i$ 个能量提升点位于位置 $x_i$，其值为 $v_i$。当 Mualani 处于位置 $x_i$ 时，她可以选择收集该能量提升点，将她的跳跃能力增加 $v_i$。在同一个位置可能有多个能量提升点。当她处于有多个能量提升点的位置时，她可以选择收集或忽略每个单独的能量提升点。没有能量提升点位于任何障碍物的区间内。

Mualani 必须收集最少的能量提升点数才能到达位置 $L$ 完成冲浪路径。如果无法完成冲浪路径，则输出 $-1$。

## 样例 #1

### 输入

```
4
2 5 50
7 14
30 40
2 2
3 1
3 5
18 2
22 32
4 3 50
4 6
15 18
20 26
34 38
1 2
8 2
10 2
1 4 17
10 14
1 6
1 2
1 2
16 9
1 2 10
5 9
2 3
2 2```

### 输出

```
4
-1
1
2```

# 题解

## 作者：cqbzhzf (赞：3)

### 思路
要找到收集的最少能量提升数量，思路很清晰，可以把 $V_i$ 和 $X_i$ 放进优先队列。遍历每一次障碍的区间，如果 $X_i<l_i$ 那么加上当前 $V_i$；如果 $X_i>l_i$ 那么用一个栈或队列存储下来，遍历完优先队列再存进去。如果遍历完优先队列后仍不能越过当前障碍，无解输出 $-1$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,m,L;
struct node1
{
	int l,r;
}a[N];
struct node2
{
	int x,v;
}b[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		priority_queue<pair<int,int>,vector<pair<int,int>>,less<pair<int,int>> > q;
		int tt=1,ans=0;
		cin>>n>>m>>L;
		for(int i=1;i<=n;i++)
			cin>>a[i].l>>a[i].r;
		for(int i=1;i<=m;i++)
			cin>>b[i].x>>b[i].v,q.push({b[i].v,b[i].x});//一定要先push(v[i]),优先队列默认以第一关键字排序
		bool pd=false;
		for(int i=1;i<=n;i++)
		{
			stack<pair<int,int> > s;
			while(!q.empty())
			{
				if(tt>=a[i].r-a[i].l+2)
					break;				
				if(q.top().second>a[i].l)
					s.push(q.top()),q.pop();
				else
				{
					tt+=q.top().first;
					ans++;
					q.pop();					
				}
			}
			if(tt<a[i].r-a[i].l+2)
			{
				pd=true;
				cout<<"-1\n";
				break;
			}			
			while(!s.empty())
			{
				q.push(s.top());
				s.pop();
			}
		}
		if(pd==true)
			continue;
		cout<<ans<<"\n";
	}
	return 0;
}

---

## 作者：_mi_ka_ (赞：3)

~~是漂亮的玛拉妮耶！！！~~

## 题目大意

在数轴 $1 \sim L$ 上跳跃，定义位于 $x$ 时跳跃能力为 $k$ 时可跳到区间 $[x,x+k]$ 的任意位置，起初跳跃能力为 $1$。在数轴上有 $n$ 个障碍物，每个障碍物（**不重叠**）占用的 $[l_i,r_i]$ 不可到达；在数轴上还有 $m$ 个增强道具，第 $i$ 个增强道具位于 $x_i$ 处（不会有障碍物但**多个道具地方可能重叠**），增强效果为跳跃能力提高 $v_i$。问至少捡多少增强道具能保证到达 $L$ 处，若无法到达，输出 $-1$。

## 解题思路

考虑**贪心**：从前往后走的时候，如果遇到障碍物，则从当前遇到的所有道具里面选**尽量大的**肯定最优，因为这样能使得选的道具尽量少。

基于以上贪心，考虑用优先队列大根堆存下当前所遇到的所有增强道具，每遇到障碍物，从大往小选，直到当前的跳跃能力能够跳过当前障碍物（即如果障碍物的长度为 $len_i$，则此时的跳跃能力 $v\ge len+1$）。

>$3\le L\le 10^9$

由于当前的数轴长度 $L$ 过长，考虑只选取我们有用的数轴上的数字进行**离散化**，即道具的位置和障碍物的左端点。道具的效果和障碍物的长度可以通过结构体和离散化后的位置存在一起。从而就可以实现上述贪心。

离散化时间复杂度 $O((n+m)\log(n+m))$，贪心时间复杂度 $O((n+m)\log m)$，总时间复杂度 $O((n+m)\log(n+m))$。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
#define N 400005//注意离散化数组范围 
using namespace std;
int T,n,m,L,cnt;
struct obs//obstacle 障碍物 
{
	int l,r,len;
}o[N];
struct tols//tools 增强道具 
{
	int x,v;
}t[N];
int bok[N],bl[N];//离散化数组 
priority_queue<int>q;//默认大根堆 
int re()//防止作弊不放快读快写
void wr(int x)
signed main()
{
	T=re();
	while(T--)
	{
		n=re(),m=re(),L=re();
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			o[i].l=re(),o[i].r=re();
			o[i].len=o[i].r-o[i].l+1;
			bok[++cnt]=o[i].l;//离散化左端点 
		}
		for(int i=1;i<=m;i++)
		{
			t[i].x=re(),t[i].v=re();
			bok[++cnt]=t[i].x;//离散化道具位置 
		}
		sort(bok+1,bok+cnt+1);
		int boks=unique(bok+1,bok+cnt+1)-bok-1;
		for(int i=1;i<=n;i++)
			o[i].l=lower_bound(bok+1,bok+boks+1,o[i].l)-bok;
		for(int i=1;i<=m;i++)
			t[i].x=lower_bound(bok+1,bok+boks+1,t[i].x)-bok;//朴素的离散化 
		int nowo=0,nowt=0,ans=0,nowv=1,flag=0;
		//当前第几个障碍物，第几个道具，当前答案（捡的道具个数），当前跳跃能力，是否中途因跳跃能力不够而直接输出 -1 
		for(int i=1;i<=boks;i++)//遍历离散化后的位置 
		{
			while(i==t[nowt+1].x&&nowt<m)//下个位置有道具 
			{
				nowt++;
				q.push(t[nowt].v);//存入优先队列 
			}
			if(i==o[nowo+1].l&&nowo<n)//下个位置有障碍 
			{
				nowo++;
				int bas=o[nowo].len;
				while(q.size()!=0&&nowv<=bas)//拿道具 
				{
					nowv+=q.top();
					q.pop(),ans++;
				}
				if(!q.size()&&nowv<=bas)//道具拿满也不够跳过障碍 
				{
					puts("-1");
					flag=1;
					break;
				}
			}
		}
		while(q.size())
			q.pop();//多测清空 
		if(!flag)
			wr(ans),putchar('\n');
	}
	return 0;
}
```

---

## 作者：WRT_Partisan (赞：2)

# 题解：CF2037D Sharky Surfing

[题目链接](https://www.luogu.com.cn/problem/CF2037D)

## 题目大意

在一个数轴上从 $1$ 到 $L$ 需要跃过 $n$ 个障碍，障碍之间不会相交且两障碍之间有空隙。位于 $x$ 跳跃能力为 $k$ 时可以跳到区间 $[x,x+k]$ 的任意位置，初始跳跃能力为 $1$。在数轴上有 $m$ 个道具，第 $i$ 个道具位于 $x_i$，可以使跳跃能力增加 $v_i$。求跳到 $L$ 所需要使用的最少道具数，若无法跳到则输出 $-1$。

## 解题思路

对于每个障碍，将前面捡到的还未使用的道具从大到小使用直到跳跃能力大于障碍长度加 $1$，可以用优先队列，并记录使用次数。若某一时刻队列为空且当前跳跃能力小于等于障碍长度，则输出 $-1$。

## 代码

```cpp
/*
 * @FilePath: \c++\CF2037D.cpp
 * @Author: WRT_Partisan
 * @Date: 2024-11-23 20:52:44
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
struct Node
{
    int l, r;
} a[2000005], b[200005];
int t, n, m, l, x, v, ans, num;
priority_queue<int> q;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        while (!q.empty())
            q.pop();
        ans = 0;
        num = 1;
        scanf("%lld%lld%lld", &n, &m, &l);
        for (int i = 1; i <= n; i++)
            scanf("%lld%lld", &b[i].l, &b[i].r);
        for (int i = 1; i <= m; i++)
            scanf("%lld%lld", &a[i].l, &a[i].r);
        int it = 1;
        bool temp = 1;
        for (int i = 1; i <= n; i++)
        {
            while (it <= m && a[it].l < b[i].l)
                q.push(a[it].r), ++it;
            while (num <= b[i].r - b[i].l + 1)
            {
                if (q.empty())
                {
                    temp = 0;
                    break;
                }
                num += q.top();
                q.pop();
                ans++;
            }
            if (temp == 0)
                break;
        }
        if (temp == 0)
            printf("-1\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：ccjjxx (赞：1)

vp 的时候看错题了，以为是要求获取的 $v$ 最小，然后发现是要求获取的次数最小……

考虑获取的加成是可累加的，并且没有跳跃次数的限制，那问题就可以转化成对于 $\forall i \in [1,n]$，最少获取多少次区间 $[1,l_i)$ 的加成才能使马拉尼跳跃能力大于 $r_i-l_i+1$。

从前往后想，若要获取**最少次数**的加成，那就一定要使每次加成尽可能的大。这样就有了一个很简单的贪心策略：

使用一个优先队列，枚举到 $i$ 时把全部 $x_j<l_i$ 的 $val_j$ 加入队列中，每次取队头，直到马拉尼的跳跃能力 $v>r_i-l_i+1$。

若队列清空，$v$ 仍然小于 $r_i-l_i+1$，则输出 $-1$。

代码：

```cpp
include<bits/stdc++.h>
using namespace std;
int t;
const int N=2e5+5;
int l[N],r[N];
int n,m,len;
struct node{
	int x,val;
}a[N];
priority_queue<int>q;
void Q()
{
	cin>>n>>m>>len;
	int ans=0,mxlen=0;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
	int pos=0,sum=0;bool flag=0;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].val;
	}	
	pos=1,sum=1;
	while(!q.empty())q.pop();//多测一定要清空，不然收获更多 debug 时间
	for(int i=1;i<=n;i++)
	{
		while(pos<=m&&a[pos].x<l[i]) q.push(a[pos++].val);
		while(sum<=(r[i]-l[i]+1)&&!q.empty()) ++ans,sum+=q.top(),q.pop();
//		cout<<"s: "<<l[i]<<" "<<a[pos].x<<" "<<sum<<" "<<ans<<"\n";
		if(sum<=(r[i]-l[i]+1))
		{
			cout<<"-1\n";return ;
		}
	}
	cout<<ans<<"\n";
}
signed main()
{
	int T;cin>>T;
	while(T--) Q();
}
```

彩蛋：

DeepL 翻译的 `power-ups` 在**题目描述**中叫做**加成**，在**输入格式**中叫做**炸弹**。

讯飞听见的翻译则自始至终叫做**加电**。

---

## 作者：sccc_ (赞：0)

## Solution

因为要求获取最少能量，所以我们必然需要每次获取能量利益最大化。

不需要跳跃时，我们可以使用优先队列维护能量最大值，需要跳跃时，我们就累加队首，直到可以跳过障碍。如果累加到队列为空，依然无法跳过，则输出 `-1`。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 2e5 + 10;
int t, n, m, l;

struct barrier {
    int l, r;
} a[kMaxN];

struct node {
    int x, v;
} b[200005];

void work() {
    priority_queue<int> q;
    cin >> n >> m >> l;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i].x >> b[i].v;
    }
    int j = 1;
    int jump = 1;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for ( ; j <= m && b[j].x <= a[i].l; j ++)
            q.push(b[j].v);
        while (jump <= a[i].r - a[i].l + 1) {
            if (!q.empty()) {
                jump += q.top();
                q.pop();
                cnt ++;
            } else {
                cout << "-1\n";
                return ;
            }
        }
    }
    cout << cnt << '\n';
    return ;
}

int main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(false);
    cin >> t;
    while (t --)
        work();
    return 0;
} 
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

对于每个障碍，将还未使用的道具从大到小使用直到跳跃能力大于障碍长度加 $1$。若某一时刻队列为空且当前跳跃能力小于等于障碍长度，则输出 $-1$。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
void read ();
struct Node {
    ll l, r;
}a[2000005], b[200005];
ll T, n, m, l, x, v, ans, num, cnt = 1;
bool flag = true;
priority_queue <ll> q;
void read () {
    while (!q.empty()) q.pop();
    ans = 0; num = 1;
    cin >> n >> m >> l;
    for (ll i = 1; i <= n; i ++) cin >> a[i].l >> a[i].r;
    for (ll i = 1; i <= m; i ++) cin >> b[i].l >> b[i].r;
    cnt = 1; flag = true;
    for (int i = 1; i <= n; i ++) {
        while (cnt <= m && b[cnt].l < a[i].l) {
			q.push (b[cnt].r);
			cnt ++;
		}
        while (num <= a[i].r - a[i].l + 1) {
            if (q.empty ()) {
                flag = false;
                break;
            }
            num += q.top ();
            q.pop ();
            ans ++;
        }
        if (flag == false) break;
    }
    if (flag == false) cout << -1 << endl;
    else cout << ans << endl;
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：O_v_O (赞：0)

## 题意

有 $n$ 个障碍区间，你不可以跳到障碍区间的任意一个点上（区间不会重叠），有 $m$ 个跳跃提升药水，每个药水在 $x_i$ 上，你喝了这瓶药水会获得 $v_i$  的跳跃提升（你可以不喝），初始跳跃能力为 $1$，你需要求出你最少要喝多少瓶药水才能跨过所有的障碍区间。

## 思路

如果本体只有一个障碍区间，从贪心角度来看，我们肯定喝那些对跳跃能力提升大的药水，然后在喝小些的，直到跳跃能力可以跳过这个障碍区间为止。

再看这道题，由于有多个障碍区间，那么我们就用一个优先队列来维护药水值，然后在每次遇到障碍时，我们就判断当前的跳跃能力是否可以跳过去，如果不可以，就从优先队列里去最大的药水喝，直到能力够了为止，如果所有药水都喝了还跳不过去，那么就无法抵达终点，输出 $-1$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int t, n, m, l;
pair<int, int> a[N], b[N];

void solve() {
  cin >> n >> m >> l;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i].first >> b[i].second;
  }
  priority_queue<int> q;
  int sum = 1, cnt = 0;
  for (int i = 1, j = 1; i <= n; i++) {
    while (j <= m && b[j].first < a[i].first) {
      q.push(b[j++].second);
    }
    while (!q.empty() && sum <= a[i].second - a[i].first + 1) {
      sum += q.top();
      cnt++;
      q.pop();
    }
    if (sum <= a[i].second - a[i].first + 1) {
      cout << -1 << '\n';
      return;
    }
  }
  cout << cnt << '\n';
}

int main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## CF2037D Sharky Surfing

### Pre story

把清空队列写成了 `pq.empty()`，硬控 $114514$ 小时。

### Sol

显而易见的贪心。

首先，要越过一个障碍物如果 $k$ 不够的话，肯定往从能量大的点加。因为他要求能量点的个数最少，所以优先加大的最优。

有了结论，解法一呼而出。那个优先队列存坐标小于当前障碍物的左端点的能量点，每次条跳障碍物都更新队列。然后就把队列里的能量值从大往小了加，加到一定程度够了，继续循环下一个。如果队列都空了还不成功，输出 $-1$。

**清空队列！**

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int kMaxN = 2e5 + 20;
const ll kMod = 998244353;

int n, m, l;
priority_queue<int> pq;

struct node {
  int a, b;
} s[kMaxN], p[kMaxN];

int main() {  
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    for (; !pq.empty(); pq.pop());
    cin >> n >> m >> l;
    for (int i = 1; i <= n; ++ i) {
      cin >> s[i].a >> s[i].b;
    }
    for (int i = 1; i <= m; ++ i) {
      cin >> p[i].a >> p[i].b;
    }
    int ans = 0, k = 1;
    for (int pi = 1, si = 1; si <= n; ++ si) {
      for (; p[pi].a < s[si].a && pi <= m; pq.push(p[pi].b), ++ pi);
      for (; s[si].a + k <= s[si].b + 1 && !pq.empty(); k += pq.top(), ++ ans, pq.pop());
      if (s[si].a + k <= s[si].b + 1) {
        cout << "-1\n";
        k = 0;
        break;
      }
    }
    if (k) {
      cout << ans << '\n';
    }
  }
  return 0;
}
```

---

