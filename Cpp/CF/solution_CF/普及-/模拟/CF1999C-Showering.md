# Showering

## 题目描述

作为一名中学生，jmsyang0808需要每天洗澡，但悲剧的是，因为Ta还要登~~臭名昭著的~~洛谷，AK CF赛，面基等等做一些琐碎的事导致Ta没有空。因为Ta太忙了，所以Ta请你写个程序来解决这个问题。

Ta有 $m$ 单位的时间，而Ta需要用 $s$ 单位的时间来洗澡。Ta有 $n$ 件事要做，第 $i$ 件事的开始与结束时间分别为 $l_i$ 和 $r_i$ ，期间Ta无法洗澡。没有两项任务重叠。

现在jmsyang0808问你，Ta有时间洗澡吗？如果能，输出 `YES` ，否则只能输出 `NO` 了QAQ~。

## 说明/提示

下面是对于用例一的解释。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1999C/f37c16ccee56dc0e812638d809cb1411cb80cf1b.png)

Translated By @jmsyang0808.

## 样例 #1

### 输入

```
4
3 3 10
3 5
6 8
9 10
3 3 10
1 2
3 5
6 7
3 3 10
1 2
3 5
6 8
3 4 10
1 2
6 7
8 9```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：WsW_ (赞：4)

简单小模拟。

---
## 思路
注意到 $\forall i>1,l_i>r_{i-1}$，题目难度骤降。  

原题意就是：一根 $0\sim m$ 的线段，上面扣掉 $l_i\sim r_i$ 的部分，问剩余的线段中是否有一条线段长度大于 $s$。  
直接考虑剩余的部分，显然剩余的部分是 $0\sim l_1,r_1\sim l_2\dots r_n\sim m$。  
直接枚举即可。

---
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;

void work(){
	int n,s,m; cin>>n>>s>>m;
	int r=0,l;
	bool f=0;
	while(n--){
		cin>>l;
		if(l-r>=s)f=1;
		cin>>r;
	}
	if(m-r>=s)f=1;
	if(f)cout<<"Yes\n";
	else cout<<"No\n";
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：xxxalq (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/CF1999C) & [CF链接](http://codeforces.com/problemset/problem/1999/C)

# 思路

注意到题目保证 $l_i>r_{i-1}$，所以我们可以用一个变量记录上一个区间右端点的位置，每次的 $l_i-r_{i-1}$ 就是当前可以连续洗澡的时间，答案取最大值即可，别忘了还有 $m-r_n$。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read(){
	int x=0;
	bool flag=false;
	char ch=getchar();
	while(ch<48||ch>57){
		if(ch==45){
			flag=true;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<3)+(x<<1)+(ch-48);
		ch=getchar();
	}
	return flag?-x:x;
}
int T,n,s,m,l,r,last;
int main(){
	T=read();
	while(T--){
		last=0;
		int maxx=0;
		n=read(),s=read(),m=read();
		while(n--){
			l=read(),r=read();
			maxx=max(maxx,l-last);
			last=r;
		}
		maxx=max(maxx,m-last);
		if(maxx>=s){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
}

```

---

## 作者：Pink_Cut_Tree (赞：2)

# CF1999C Showering 题解

[Luogu Link](https://www.luogu.com.cn/problem/CF1999C)|[CF Link](https://codeforces.com/contest/1999/problem/C)|[My AC submission](https://codeforces.com/contest/1999/submission/274743838)。

简单题，一发 AC。

### 解析

我们发现只有在 $r_i\sim l_{i+1}$ 时间内是空闲的，我们只需要判断在这些空闲时间的长度是否够主人公洗个澡。

注意 $0\sim l_1$ 和 $r_n\sim m$ 也是合法的时间。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T;
int n,s,m;
int l[N],r[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>s>>m;
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
		}
		l[n+1]=m;
		bool flag=0;
		for(int i=0;i<=n;i++){
			if(l[i+1]-r[i]>=s){
				cout<<"Yes\n"; flag=1; break;
			}
		}
		if(flag==0){
			cout<<"No\n";
		}
	}
return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[CF1999C Showering](https://www.luogu.com.cn/problem/CF1999C)

题上说没有两个任务时间上是重叠的，所以考虑按左端点排序，第 $i$ 个任务和第 $i-1$ 个任务之间的时间即为 $l_i-r_{i-1}$，判断这个时间是否大于等于 $s$ 即可。

最后别忘了判断 $m-r_n$ 是否大于等于 $s$。

单组数据时间复杂度 $\mathcal O(n\log n)$，瓶颈在于排序。

**UPD：由于题上保证了 $l_i>r_{i-1}$，所以无需排序，时间复杂度 $\mathcal O(n)$。**
```cpp
struct Node { int l, r; } a[N];
bool operator < (Node a, Node b) {
	return a.l < b.l;
}
void solve () {
	cin >> n >> s >> m;
	for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i].l - a[i - 1].r >= s) return cout << "YES\n", void (0);
	}
	if (m - a[n].r >= s) return cout << "YES\n", void (0);
	cout << "NO\n";
}
```

---

## 作者：Archy_ (赞：1)

## 题目翻译
[传送门](https://www.luogu.com.cn/problem/CF1999C)

对于每组数据，有 $n$ 个区间，区间 $(l_i,r_i)$ 覆盖在一个 $0 \sim m$ 的大区间上，保证小区间之间不重叠。

求是否能在大区间上找到一个长度 $\ge s$ 的未覆盖区间。
## 题目思路
考虑用一个变量 $lastr$ 记录上一个区间的 $r$ 端点位置，则当前空区间长度即为当前 $l$ 端点位置减 $lastr$，$lastr$ 初始为 $0$。

不断取最大值最后比较即可。
## CODE
```cpp
#include <iostream>
using namespace std;
int main() {
	cin.tie(0) -> ios :: sync_with_stdio(0);
	int q; cin >> q;
	while(q--) {
		int n, s, m, lastr = 0, time = 0;
		cin >> n >> s >> m;
		for(int i = 1; i <= n; i++) {
			int l, r; cin >> l >> r;
			time = max(time, l - lastr);
			lastr = r;
		}
		time = max(time, m - lastr);
		if(time >= s) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
} 
```

---

## 作者：lcy0506 (赞：1)

# 题解：CF1999C Showering

这道题刚开始我没看到做事的时间单调不降，还想着去排序，最后喜提 TLE。

现在我们来讲正解，因为做事的时间单调不降，所以我们将每件事的开始时间减去上一件事的结束时间，如果其值大于或等于 $s$，那么就可以洗澡。

注意事项：最后一件任务结束需要特判。

# 代码如下

```
#include <bits/stdc++.h>
using namespace std;
int a[1000001],b[1000001];
int main()
{
	int T;
	b[0]=0;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		int n,s,m,flag=0;
		cin>>n>>s>>m;
		for(int j=1;j<=n;j++)
		{
			scanf("%d%d",&a[j],&b[j]);
			if(a[j]-b[j-1]>=s&&flag==0)
			{ 
				flag=1;
				printf("YES\n");
			}
		}
		if(m-b[n]>=s&&flag==0)//特判
		{
			flag=1;
			printf("YES\n");
			continue;
		}
		if(flag==0)
		printf("NO\n");
	}
}
```

---

## 作者：Specthraimn (赞：1)

# Showering 题解
### 题目大意
在总长为 $m$ 的时间内，给 $n$ 个区间，求是否存在一个未被覆盖且长度大于 $s$ 的时间段。
### 解题思路
用结构体存区间，直接枚举每个未被覆盖的时间段，求出最大值，判断是否满足要求。如果最大值不满足，则所有间隔都不满足。
### AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
struct node
{
	int l, r;
} a[N];
void work()
{
	int n, s, m, maxn = 0;
	cin >> n >> s >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i].l >> a[i].r;
	}
	a[n+1].l = m;
	for(int i = 0; i <= n; i++)
	{
		maxn = max(maxn, a[i+1].l - a[i].r);
	}
	if(maxn >= s) cout << "YES\n";
	else cout << "NO\n";
}
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		work();
	}
	return 0;
}
```
**完结撒花✿✿ヽ(°▽°)ノ✿**

---

## 作者：So_noSlack (赞：1)

## 题目简述

有 $T$ 组数据，每组数据给出 $n, s, m$，和 $n$ 个 $l_i, r_i$。

在 $[1, m]$ 的区间内，$[l_i, r_i]$ 已经被覆盖，求是否存在长度大于等于 $s$ 的区间没被覆盖。

## 思路

可以直接 $O(n)$ 求每两个区间之间的间隙长度，如果大于等于 $s$ 就直接输出 `YES`。

需要注意的是，$[r_n, m]$ 这个区间需要特判一下。

代码如下：


```cpp
#include<iostream>
using namespace std;
#define MAXN 200005

long long read() {
	long long x = 0, f = 1; char ch = getchar();
	while(ch < 48 || ch > 57) { if(ch == 45) f = -1; ch = getchar(); }
	while(ch >= 48 && ch <= 57) { x = (x << 3) + (x << 1) + (ch - 48); ch = getchar(); }
	return x * f;
}

long long T, n, s, m, l[MAXN], r[MAXN];

int main() {
	T = read();
	while(T --) {
		bool f = false;
		n = read(); s = read(); m = read();
		for(int i = 1; i <= n; i ++) {
			l[i] = read(), r[i] = read();
			if(l[i] - r[i - 1] >= s) f = true;
		}
		if(f || m - r[n] >= s) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
```

[$\text{Submission}$](https://codeforces.com/contest/1999/submission/274750144)

---

## 作者：ICU152_lowa_IS8 (赞：1)

本来拿到这题想着区间合并的，然后再看题目有一行：

$i>1$ 时，$l_i>r_{i-1}$。

连区间合并也不是，直接模拟。

判断两个区间之间的空隙能否满足条件即可。

注意不要忘了从 $0$ 到 $l_1$ 和从 $r_n$ 到 $m$ 的空隙。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int l,r;
}a[1000005];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,s,m;
		cin>>n>>s>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i].l>>a[i].r;
		}
		int ans=a[1].l;
		for(int i=2;i<=n;i++){
			ans=max(ans,a[i].l-a[i-1].r);
		}
		ans=max(ans,m-a[n].r);
		cout<<(ans>=s?"YES":"NO")<<endl;
	}
	return 0;
}

```

---

## 作者：InfiniteRobin (赞：1)

### 简要题意 

---
一天有 $m$ 分钟，有 $n$ 项任务，每一项任务都有一个起止时间，任务不会重叠。问是否能在这一天中找出长度为 $s$ 的空闲时间段。  

---
### 分析
---
直接模拟即可，由于题目中任务起止时间段是排好序的，因此我们只需要记录上一个任务的结束时间，设为 $last$，当前任务的起始时间，设为 $l$。若 $l-last\ge s$，则有时间洗澡。$last$ 初始值应设为 $0$。

最后，别忘了判断一下在最后一个任务结束后，是否有时间洗澡。即判断 $m-l\ge s$。

---
### Code

---
代码很好写。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int t,n,m,s;
    
    cin>>t;
    while(t--){
        cin>>n>>s>>m;
        
        int l,r,last=0; //任务的时间段 l 至 r ，last记录前一个 r
        bool f=0; //记录可不可以洗澡
        while(n--){
            cin>>l>>r;
            if(l-last>=s){ //计算空出的时间
                f=1;
            }
            last=r;
        }
        if(m-r>=s){ //最后也要判断
            f=1;
        }
        if(f){
            cout<<"yeS"<<endl;
        }
        else{
            cout<<"nO"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：GeXiaoWei (赞：1)

# CF1999C Showering
## 解析
通过题目可知，每到 $l_i$ 至 $r_i$ 的时间，他就无法洗澡。所以只需要看间隔时间是否大于等于 $s$ 分钟即可，即判断 $l_i-r_{i-1}\ge s$，成立他就有时间洗澡。

注意还有判断刚开始到 $l_1$ 的时间与最后 $r_n$ 到 $m$ 的时间。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,m,l[200005],r[200005],z;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&s,&m);z=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&l[i],&r[i]);
			if(l[i]-r[i-1]>=s) z=1;
		}
		if(m-r[n]>=s) z=1;
		if(z) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

可用的区间就是 $\forall i\in[2,n],[r_{i-1},l_i]$ 以及 $[0,l_1]$ 和 $[r_n,m]$。我们只需要看这些区间中有没有长度大于等于 $s-1$ 的就行了。

代码如下：

```cpp
#include<iostream>
using namespace std;
int t,n,s,m,l,r,ltr; bool cn;
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>s>>m; 
		ltr=0; cn=0; s--;
		for(int i=1;i<=n;++i)
			cin>>l>>r,cn|=(l-ltr)>s,ltr=r;
		cn|=(m-ltr)>s;
		puts(cn?"YES":"NO");
	}
	return 0;
}
//私は猫です
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

一天有 $m$ 分钟（每一分钟视为数轴上的一个点），$n$ 个任务 $(l_i,r_i)$，代表 $l_i$ 至 $r_i$ 的时间内不空闲，询问这一天内是否有连续的至少 $s$ 分钟的空闲时间。任务之间不重叠，且输入时已按 $l$ 升序排序。

## 解题思路

对于相邻的两个任务 $(l_i,r_i)$ 和 $(l_{i+1},r_{i+1})$，若 $l_{i+1}-r_i\ge s$，则意味着找到了长度至少为 $s$ 的空闲时间。对于 $0$ 到 $l_1$ 和 $r_n$ 到 $m$ 的时间，可以进行特判，也可以加入 $(0,0)$ 和 $(m,m)$ 两个任务。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, s, m, ed, st1, ed1;
int main() {
    cin >> t;
    while (t--) {
        bool flag = false;
        cin >> n >> s >> m;
        ed = 0;
        for (int i = 1; i <= n; i++) {
            cin >> st1 >> ed1;
            if (st1 - ed >= s)
                flag = true;
            ed = ed1;
        }
        if (flag || m - ed >= s) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

---

## 作者：_O_w_O_ (赞：0)

在此，我们设 $r_0=0,l_{n+1}=m$，那么我们只用检查有没有 $1\le i\le n+1$ 满足 $l_i-r_{i-1}\ge s$ 即可。

由于所有的 $i$ 都满足 $l_i>r_{i-1}$，所以这样肯定是对的。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int T;
int n,s,m;
int l,r;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		bool fg=0;
		cin>>n>>m>>s;
		int j=0;
		for(int i=1;i<=n;i++){
			cin>>l>>r;
			if(l-j>=m) fg=1;
			j=r;
		}
		if(s-j>=m) fg=1;
		if(fg) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# CF1999C Showering
## 题意概括
亚历克斯为一天安排了 $n$ 项任务，给出每项任务的起始时间 $l_{i}$ 和结束时间 $r_{i}$、每天的总时长 $m$ 和他洗澡所需的时间 $s$，求亚历克斯当天能否洗澡。保证在 $i>1$ 时，所有的 $l_{i}>r_{i-1}$。
## 思路分析
简单的模拟题。  
亚历克斯的空闲时间是两项任务的间隔，即当前任务的开始时间减前一个任务的结束时间。  
因此，遍历所有的空闲时间，判断是否有空闲时间大于 $s$ 即可。  
需要注意的是，第一项任务开始前的时间和最后一项任务结束后的时间也属于空闲时间，需要进行特判。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,m,l,r;
int main(){
	cin>>t;
	while (t--){
	    bool flag=0;
	    int lastr=0;  //上一次的结束时间，初始时一定要设为0，特判第一项任务开始前的时间
		cin>>n>>s>>m;  //时间间隔数量，洗澡时间，每天的分钟数
		for (int i=1;i<=n;i++){
			cin>>l>>r;
			if (l-lastr>=s) flag=1;
			lastr=r;  //更新
		}
		if (m-lastr>=s) flag=1;  //判断最后一项任务结束后的时间
		if (flag==1) cout<<"YES"<<'\n';
		else cout<<"NO"<<'\n';
	}
	return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

## Solution

使用 $lst$ 记录上一次的 $r$，$lst$ 初值为 $0$，如果 $l - lst \ge s$ 或者输入完之后 $m - lst \ge s$，那么输出 `YES`，否则输出 `NO`。

## Code

```cpp
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using db = double;

const int kMaxN = 2e5 + 1;

int t, n, l, r, lst, s, m;

int main() { 
  for (cin >> t; t; t--) {
    bool f = 0;
    lst = 0;
    cin >> n >> s >> m;
    for (int i = 1; i <= n; i++) {
      cin >> l >> r;
      f |= (l - lst >= s);
      lst = r;
    }
    f |= (m - lst >= s);
    cout << (f ? "YES" : "NO") << '\n';
  }
  return 0; 
}
```

---

## 作者：O_v_O (赞：0)

# CF1999C Showering 题解

## 题意

给定 $n$ 个区间，区间总长度为 $m$，每个区间会给定一个 $l$ 和 $r$，表示区间 $l$、$r$ 被覆盖，问你有没有存在一个长度为 $s$ 的区间没有被任何的 $l$、$r$ 覆盖，如果有输出 `Yes` 否则输出 `No`。

## 思路

很明显，题目保证了区间不会重叠，所以，我们只需要按照右端点排序，然后直接计算这个区间的 $r$ 和下个区间的 $l$ 之间的距离就行。但这里还有个特殊的地方，就是最小的那个区间的 $l$ 并不是 $1$，最大区间的 $r$ 并不是 $m$，所以我们还要特殊计算一下头和尾。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int t, n, m, s;

struct node{
  int x, y;
}a[200010];

bool cmp(node a, node b) {
  return a.x < b.x;
}

bool solve() {
  cin >> n >> s >> m;
  for (int i = 1; i <= n; i++) { // 读入
    cin >> a[i].x >> a[i].y;
  }
  sort(a + 1, a + n + 1, cmp); // 按照右端点排序
  if (a[1].x >= s || m - a[n].y >= s) { // 特殊计算头和尾
    return true;
  }
  for (int i = 1; i < n; i++) {
    if (a[i + 1].x - a[i].y >= s) { // 计算距离是否大于等于 s
      return true;
    }
  }
  return false;
}

int main() {
  cin >> t;
  while (t--) {
    cout << (solve() ? "Yes\n" : "No\n");
  }
  return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# CF1999C 题解
### 题目大意
有 $t$ 组数据，每组给出任务数 $n$，洗澡所需时间 $s$，一天的时间 $m$。接下来给出任务的开始时间 $l_i$ 和结束时间 $r_i$。求是否有空闲时间不少于 $s$ 使主人公可以完整洗一次澡。保证在 $i>1$ 时，$l_i > r_{i-1}$。
### 大致思路
直接模拟，用任务开始时间减去前一轮任务结束时间。若没有前一轮任务，则不用减。判断结果是否大于 $s$。记得末尾要用 $m$ 减去 $r_n$ 进行判断。
### 核心代码
```cpp
void solve() {
  // 输入
  int n, s, m;
  std::cin >> n >> s >> m;
  bool flag = 0;
  int br=0, li, ri; // br 指上一个任务结束时间
  for(int i = 0; i < n; ++i) {
    std::cin >> li >> ri;
    if(li - br >= s) flag = 1; // 判断
    br = ri;
  }
  if(m - br >= s) flag = 1; // 末尾再判断
  // 输出
  if(flag) std::cout << "YES\n";
  else std::cout << "NO\n";
}

```
### [RESULT](https://codeforces.com/contest/1999/submission/274767485)

---

## 作者：呼吸之野 (赞：0)

## Solution

计算第一个任务与 $0$ 时刻的时间间隔、每个任务之间的时间间隔、最后一个任务与 $m$ 时刻的时间间隔，判断是否有一段时间间隔不小于 $s$ 即可。

 ## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int n,s,m,l1[maxn],r1[maxn];
void solve(){
	cin>>n>>s>>m;
	for(int i=1;i<=n;i++){
		cin>>l1[i]>>r1[i];
	} 
	l1[n+1] = m; 
	for(int i=1;i<=n+1;i++){
		if(l1[i]-r1[i-1] >= s){
			cout<<"YES"<<endl;
			return ;
		}
	}
	cout<<"NO"<<endl;
	return ;
}
int main(){
	int T;cin>>T;
	while(T--) solve(); 
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## CF1999C Showering

将所有时间点（含 $0, m, l_i, r_i$）存入一个 `vector`，那么最后存储了一个 $\{0,l_1,r_1,l_2,\dots,r_n,m\}$ 的长度为 $2n+2$ 的序列，发现 $(0,1),(2,3)$ 这些 $(2i,2i+1),i\in\Z$ 位置之间的间隔是没有工作的。计算每个间隔和 $s$ 比较即可。

代码：

```cpp
void Main() {
  n = read(), s = read(), m = read();
  vector<int> t;
  t.push_back(0);
  for (int i = 1; i <= n; ++i) t.push_back(read()), t.push_back(read());
  t.push_back(m);
  for (unsigned i = 1; i < t.size(); i += 2)
    if (t[i] - t[i - 1] >= s) return void(puts("YES"));
  puts("NO");
}
```

---

## 作者：cfkk (赞：0)

思路：对于每个工作时间 $(l_i,r_i)$，我们可以通过枚举当前工作的起始时间与上一个工作的结束时间之差是否大于等于 $s$（即 $l_i-r_{i-1}$ 是否大于等于 $s$）。

时间复杂度 $O(Tn)$。

代码如下：

```cpp
#define maxn 222222
int l[maxn],r[maxn];
signed main()
{
    int T=read();
    while(T--)
    {
        int n=read(),s=read(),m=read();
        for(int i=1;i<=n;i++)l[i]=read(),r[i]=read();
        r[0]=0;
        bool vis=0;
        for(int i=1;i<=n;i++)
        {
            if(l[i]-r[i-1]>=s)vis=1;
            if(vis)break;
        }
        if(m-r[n]>=s)vis=1;
        if(vis)puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

## 作者：xuduang (赞：0)

### 题意

给出 $n$ 个区间和总长 $s$，问是否可以找到一个区间外的一个长度为 $m$ 的连续区间。

### 分析

注意这里是计算时长，即长度，不是点，所以 $l,r$ 两点距离计算为 $r-l$。

接下来就不难了，我们记录下来上一个区间的右端点，与当前的左端点计算长度，如果大于等于 $m$ 就是合法的。但是要注意 $s$ 处也有一个端点，最后也要计算。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, m, s;
void solve()
{
    cin >> n >> m >> s;
    bool fl = 0;
    int ls = 0;//上一个的右端点
    for(int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        if(l - ls >= m) fl = 1;//距离合法
        ls = r;
    }
    if(fl || s - ls >= m/*最后一个端点*/) cout << "Yes\n";
    else cout << "No\n";
}
signed main()
{
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：GreenMelon (赞：0)

## 分析

其实并不需要去关注什么时候要工作，只需去关注什么时候是空闲时间。最初设定空闲时间的起始时间 $x$ 为 $0$，结束时间 $y$ 为第一次工作的起始时间，后面每次定义 $x$ 为前一次工作的结束时间，$y$ 为后一次工作的起始时间，就能算出某个空闲时间的总时长为 $y-x$，最后只要判断总时长最长的空闲时间是否大于等于 $s$ 即可。

注意有可能在每天的最后几分钟是空闲的，所以还要特判，要不然会 WA。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n, s, m;
		int maxn=0;
		int x=0, y=0;
		cin>>n>>s>>m;
		for(int i=0;i<n;i++){
			int l, r;
			cin>>l>>r;
			y=l;
			maxn=max(maxn, y-x);
			x=r;
		}
		y=m;
		maxn=max(maxn, y-x);
		if(maxn>=s) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
} 
```

---

## 作者：donnieguo (赞：0)

## 题意简述

在 $[1,m]$ 中有 $n$ 个区间 $[l_i,r_i]$，求在不覆盖到这 $n$ 个区间的能不能情况下找到**连续**的 $s$ 个点。

## 思路

首先判断一下从 $1\sim l_1$ 和 $r_n\sim m$ 有没有连续的 $s$ 个点，然后枚举从 $1\sim n-1$，判断一下 $r_i \sim l_{i+1}$ 有没有连续的 $s$ 个点即可。

## AC code

```cpp
#include <iostream>
#define N 200010
using namespace std;

int T, n, s, m;
struct jiange {
	int l, r;
} a[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> s >> m;
		m++;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].l >> a[i].r;
			a[i].l++, a[i].r++;
		}
		if (a[1].l - 1 >= s || m - a[n].r >= s) {cout << "YES" << '\n';continue;}
		bool flag = 0;
		for (int i = 1; i < n; i++)
			if (a[i + 1].l - a[i].r >= s) {flag = 1;break;}
		flag ? cout << "YES" << '\n' : cout << "NO" << '\n';
	}
	return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 思路
这道题只能使用每组数据 $O(n)$ 的做法通过。不难发现，其实只要每次把的上一个的 $r$ 存起来，和当前的 $l$ 求差，如果差大于等于 $s$ 则继续。一开始 $lastl$ 的值为 $0$。记得最后再判断一下 $m$ 和最后一个 $r$ 的差值，如果大于等于 $s$ 也算可以洗澡。
### 代码

```
#include<bits/stdc++.h>
using namespace std;
 
int main(){
	int t;
	cin >> t;
	while(t--){
		int n, lastl = 0, s, m;
		bool if_s = false;
		cin >> n >> s >> m;
		for(int i = 1; i <= n; i++){
			int l, r;
			cin >> l >> r;
			// cout << l << " " << r << endl;
			// cout << lastl << " " << l << endl;
			if(l - lastl >= s && if_s == false){
				cout << "YES" << endl;
				if_s = true;
			}
			lastl = r;
		}
		if(if_s == false){
			if(m - lastl >= s){
				cout << "YES" << endl;
			}
			else{
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}

```

---

## 作者：ToastBread (赞：0)

## 题目思路
本题数据范围的 $m$ 过大，显然枚举每一个洗澡的时间段不可行。

于是考虑枚举每一个工程的间隔，若这个间隔有足够的时间洗澡，就洗澡。

需要特别注意的是**记得枚举开头到 $l_1$ 和 $r_n$ 到结尾的时间**。

具体的实现可以参考我的代码。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,s,l[200005],r[200005];
int main()
{
	cin>>t;
	while(t--)//多组数据 
	{
		cin>>n>>s>>m;//输入 
		for(int i = 1; i <= n; i++)
		{
			cin>>l[i]>>r[i];
		}
		bool ans=0;//能洗澡吗 
		if(l[1]>=s) ans=1;//从 0 到第一个工程开始能洗澡吗 
		for(int i = 2; i <= n; i++)
		{
			if(l[i]-r[i-1]>=s) ans=1;//每一个工程的间隔能洗澡吗 
		}
		if(m-r[n]>=s) ans=1;//最后一个工程到时间结束能洗澡吗 
		if(ans) cout<<"YES"<<endl;//能 
		else cout<<"NO"<<endl;//不能 
	}
	return 0; 
 } 
```

---

## 作者：wwwidk1234 (赞：0)

简单模拟。空闲时间为夹在两个任务中的那一小段，为 $[0,l_1],[r_1,l_2],...,[r_{n-1},l_n],[r_n,m]$。为了方便计算，令 $r_0=0,l_{n+1}=m$，`for` 循环查找是否存在一个区间 $[l,r)$ 的长度大于等于洗澡所花费的时间即可（注意前闭后开）。

代码：

```cpp
// Problem: Showering
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1999/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=2e5+3;
int l[N],r[N];
inline bool solve()
{
	int n,s,m;
	cin>>n>>s>>m;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
	r[0]=0;
	l[n+1]=m;
	for(int i=1;i<=n+1;i++)
	{
		int a=r[i-1];
		int b=l[i];
		if(b-a>=s) return 1;
	}
	return 0;
}
int main()
{
	int T;
	cin>>T;
	while(T--) puts(solve()?"YES":"NO");
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
每次记录上一件事结束的时间，将这个值设为 $p$，初始时 $p=0$。输入 $l$ 和 $r$，如果 $l-p \geq s$，说明有一个长度大于等于 $s$ 的时间间隔，这样 Alex 就有时间可以洗澡，我们做个标记。将 $p$ 设为 $r$。

注意：最后一件事的结束时间到一天剩余的时间这段时间并不是消失了，所以我们还要判断一下，如果 $m-p \geq s$，那么 Alex 同样可以洗澡。

如果 Alex 可以洗澡，输出 `Yes`，否则输出 `No`。
### 代码
```cpp
#include<iostream>
#define int long long
void solve(int T){
	if(T==0)return;
	int n,s,m;
	std::cin>>n>>s>>m;
	int p=0;
	bool f=0;
	for(int i=1;i<=n;i++){
		int l,r;
		std::cin>>l>>r;
		if(l-p>=s)f=1;
		p=r;
	}
	if(m-p>=s)f=1;
	if(f)puts("Yes");
	else puts("No");
	solve(T-1);
}
signed main(){
	int T;
	std::cin>>T;
	solve(T);
}
```

---

## 作者：qifan_maker (赞：0)

用 `pair` 存储任务的左端点和右端点，排序后比较每个任务的间隔，若 ${a_{i+1}}_l-{a_i}_r\geq s$，则答案为 `YES`。

注意处理开头和结尾的情况，可以增加首尾两个端点。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353;
const int MAXN = 200100,hsb=1045141919;
const ll Inf = 1000000000000000000ll;
#define PI pair<ll,ll>
#define PII pair<ll,pair<ll,ll>>
PI a[MAXN];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int Tcs=1;
    cin >> Tcs;
    while (Tcs--){
        int n,s,m;
        cin >> n >> s >> m;
        for (int i=1;i<=n;i++){
            cin >> a[i].first >> a[i].second;
        }
        a[n+1] = {m,hsb};
        a[n+2] = {-hsb,0};
        sort(a+1,a+n+2+1);
        bool flag=1;
        for (int i=1;i<=n+1;i++){
            if (a[i+1].first - a[i].second >= s){
                cout << "YES\n";
                flag=0;
                break;
            }
        }
        if (flag) cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999C](https://www.luogu.com.cn/problem/CF1999C)

# 解题思路

我们发现一共有 $m$ 个不空闲的区间，而根据题意，这些区间**互不重叠**，因此我们肯定是在一个区间的结尾和下一个区间的开头来完成任务。

直接排序后算出两两区间相距长度即可。

注意特判开头和结尾的情况。

时间复杂度 $O(n \log n)$，瓶颈在于排序。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
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
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
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
ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
struct node{
	ll l,r;
}a[200010];
ll n,m,k;
bool cmp(node x,node y){
	return x.l<y.l;
}
ll maxn;
void solve()
{
	maxn=0;
	_clear();
	cin>>n>>m>>k;
	forl(i,1,n)
		cin>>a[i].l>>a[i].r;
	sort(a+1,a+1+n,cmp);
	forl(i,1,n)
		Max(maxn,a[i].l-a[i-1].r);
	Max(maxn,k-a[n].r);
	printcf(maxn>=m);
}
int main()
{
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}

```

---

