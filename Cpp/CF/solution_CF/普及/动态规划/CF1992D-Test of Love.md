# Test of Love

## 题目描述

ErnKor is ready to do anything for Julen, even to swim through crocodile-infested swamps. We decided to test this love. ErnKor will have to swim across a river with a width of $ 1 $ meter and a length of $ n $ meters.

The river is very cold. Therefore, in total (that is, throughout the entire swim from $ 0 $ to $ n+1 $ ) ErnKor can swim in the water for no more than $ k $ meters. For the sake of humanity, we have added not only crocodiles to the river, but also logs on which he can jump. Our test is as follows:

Initially, ErnKor is on the left bank and needs to reach the right bank. They are located at the $ 0 $ and $ n+1 $ meters respectively. The river can be represented as $ n $ segments, each with a length of $ 1 $ meter. Each segment contains either a log 'L', a crocodile 'C', or just water 'W'. ErnKor can move as follows:

- If he is on the surface (i.e., on the bank or on a log), he can jump forward for no more than $ m $ ( $ 1 \le m \le 10 $ ) meters (he can jump on the bank, on a log, or in the water).
- If he is in the water, he can only swim to the next river segment (or to the bank if he is at the $ n $ -th meter).
- ErnKor cannot land in a segment with a crocodile in any way.

Determine if ErnKor can reach the right bank.

## 说明/提示

Let's consider examples:

- First example: We jump from the shore to the first log ( $ 0 \rightarrow 1 $ ), from the first log to the second ( $ 1 \rightarrow 3 $ ), from the second to the fourth ( $ 3 \rightarrow 5 $ ), and from the last log to the shore ( $ 5 \rightarrow 7 $ ). So, we have $ 0 \rightarrow 1 \rightarrow 3 \rightarrow 5 \rightarrow 7 $ . Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».
- Second example: $ 0 \rightarrow 1 $ , we jump into the water from the first log ( $ 1 \rightarrow 2 $ ), swim a cell to the log ( $ 2 \leadsto 3 $ ), $ 3 \rightarrow 4 \rightarrow 5 \rightarrow 6 \rightarrow 7 $ . Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».
- In the third example, ErnKor needs to swim two cells 'W', but can only swim one. Therefore, the answer is «NO».
- Sixth example: We jump from the shore into the water ( $ 0 \rightarrow 6 $ ) and swim one cell in the water ( $ 6 \leadsto 7 $ ). Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».

## 样例 #1

### 输入

```
6
6 2 0
LWLLLW
6 1 1
LWLLLL
6 1 1
LWLLWL
6 2 15
LWLLCC
6 10 0
CCCCCC
6 6 1
WCCCCW```

### 输出

```
YES
YES
NO
NO
YES
YES```

# 题解

## 作者：Garry_HJR (赞：6)

## 题目大意

有一个长 $n$ 米的河流，你站在 $0$ 号点上，想要去 $n+1$ 号点。

$1$ 号点到 $n$ 号点有 $3$ 种情况。

1. `W` 表示水，允许经过。

1. `L` 表示木头，允许经过。

1. `C` 表示鳄鱼，不允许经过。

这个人可以经过不超过 $k$ 个水点。

运动的方式有 $2$ 种。

1. 站在木点 $i$ 上，你可以跳到 $\min(n+1,i+j(0\le j \le m))$ 上，可以跳入水中或者另一个木头，但是不能跳到鳄鱼上。

2. 在水 $i$ 上，你能且仅能到达 $i+1$ 号点。如果 $i+1$ 是鳄鱼，不可以走。

不能走回头路。

如果这两种运动方式都无法到达 $n+1$ 号点，或是经过了超过 $k$ 个水点，则失败，反之成功。

判断能不能成功。

## 思路分析

我们考虑设 $f(i)$ 表示当前走到 $i$ 这个位置之前还能最多走多少个水点。

然后我们可以进行讨论转移了。

对于 $f(i)$，如果是非鳄鱼点，可以从木点转过来，也可以从水点转过来。

如果从木点或者转过来，那么不消耗水点剩余个数，于是有 `f[i]=f[i-j]`，注意这里 $1\le j \le m$。

还有一种可能就是从水点转移过来，由于水点只能挨着走，于是有 `f[i]=f[i-1]-1`。

两种情况取最大。

注意这里有一个边界情况就是 `f[0]=k+1`。

这个点可谓是“可盐可甜”。因为你从岸边跳到水点需要 $-1$，所以你最好设 `f[0]=k+1`。当然，如果第 $1$ 个点是木点，那是不能直接 `f[1]=f[0]` 的，因为这样的话会导致可以游过的水点多了 $1$，因此我们应做个特判。

得解。

## 代码欢送
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int k,n,m;
char ch[200005];
int rem[200005];
bool flg[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		scanf("%s",ch+1);
		ch[0]='L';//我们先设它是木点 
		rem[0]=k+1;//边界情况 
		for(int i=1;i<=n+1;i++){
			rem[i]=-114514;//一开始暂定这个点无解 
			if(ch[i]=='C'){//如果是鳄鱼点，直接跳过 
				rem[i]=-114514;
				continue;
			}
			int fr=max(0,i-m);//最远从哪个木点转移过来 
			for(int j=fr;j<i;j++){
				if(ch[j]=='L'){
					if(min(k,rem[j])>rem[i]){
						rem[i]=min(k,rem[j]);//特判掉 k+1 的情况，和 k 取min 
					}
				}
			}
			if(ch[i-1]=='W'||i-1==0){//从水点或者岸边转移过来 
				if(rem[i-1]-1>rem[i]){
					rem[i]=rem[i-1]-1;
				}
			}
		}
		if(rem[n+1]<0){//注意要游到对岸去，所以不是n是n+1 
			cout<<"No"<<endl;
		}
		else cout<<"Yes"<<endl;
		for(int i=0;i<=n+1;i++)rem[i]=0;
	}
}
```

---

## 作者：Kindershiuo (赞：6)

# 前言
这题我一上手我是想到最短路，但是其实我估计用最短路是个歪解，而且这题应该只是个橙，但是我这里还是提供一个最短路的思路。
# 解题思路
我们跑最短路，最重要的就是建图，这里的图怎么建呢，很简单，首先我们可以先预处理一下，就是我们在字符串末尾以及开头加一个木头，也就是我们把两岸当成木头。
然后我们再循环遍历建图：
1. 当我们遍历到一个字符是木头时，我们可以根据我们跳跃的格子来建边，如果跳到木头上，边权是 $0$，如果跳到水里，边权就是 $1$，如果是鳄鱼，我们不建边。
2. 最关键的就是在水里的情况怎么建图，其实就是分情况，在一个水格子游向下一个水格子时，边权是是 $1$，当我们从一个水格子游到木头上时，边权就是 $0$。

那么我们的图建好了接下来就简单了，直接调出最短路的板子跑一下就能过了，最后判断一下到岸边的总花费是否大于 $k$ 就行了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
const int inf=0x3f3f3f3f3f3f3f3f;
int T;
struct edge{
	int v;
	int w;
};
vector<edge>e[N];
int n,m,k;
string s;
int d[N];
int vis[N];
priority_queue<pair<int,int>>q;

void dijkstra(int s){
	for(int i=0;i<=n+1;i++){
		d[i]=inf;
		vis[i]=0;
	}
	q.push({0,s});
	d[s]=0;
	while(q.size()){
		auto t=q.top();
		q.pop();
		int u=t.second;
		if(vis[u])continue;
		vis[u]=1;
		for (auto ed : e[u]) {
			int v = ed.v, w = ed.w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
//				pre[v] = u; //记录前驱点
				q.push({-d[v], v}); //把邻点push进去，继续更新其他的点
			}
		}
	}
}

void solve() {
	cin>>n>>m>>k;
	cin>>s;
	s='L'+s;
	s=s+'L';
	//0到n+1//
	for(int i=0;i<=n+1;i++){
		if(s[i]=='L'){
			for(int j=1;j<=m;j++){
				if(s[i+j]=='W'){
					e[i].push_back({i+j,1});
				}
				else if(s[i+j]=='L'){
					e[i].push_back({i+j,0});
				}
			}
		}
	}
	for(int i=0;i<=n+1;i++){
		if(s[i+1]=='W'){
			e[i].push_back({i+1,1});
		}
	}
	for(int i=0;i<=n+1;i++){
		if(s[i]=='W'&&s[i+1]=='L'){
			e[i].push_back({i+1,0});
		}
	}
	dijkstra(0);
//	for(int i=0;i<=n+1;i++){
//		cout<<d[i]<<" ";
//	}
	if(d[n+1]>k)cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
	for(int i=0;i<=n+1;i++)e[i].clear();
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：3)

### [中文题面](https://vjudge.net.cn/problem/CodeForces-1992D#author=GPT_zh)
### 思路分析
直接模拟即可。

- 如果当前在水面上（陆地和岸边）：跳到离自己最近的那个木头上。
- 如果当前在水中：向前移一格。
- 如果当前在鳄鱼身上：直接输出无解。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[100005],ans=0;
void w(){
    int n,m,k,cnt=0;
    cin>>n>>m>>k;
	string s;
	cin>>s;
	s="S"+s;
	for(int i=0;i<=n;){
//		cout<<"Y";
		if(s[i]=='C'){
				cout<<"NO\n";
				return;
		} 
		if(s[i]=='W'){
			i++;
			cnt++;
			if(cnt>k){
				cout<<"NO\n";
				return;
			}
			continue;
		}
		if(i+m>n)break;
		int j,f=false,l=-1;
		for(j=1;j<=m&&i+j<=n;j++){
			if(s[j+i]=='L'){
				f=true;
				break;
			}
			if(s[j+i]=='W')l=j;
		}
		if(f==true)i+=j;
		else if(l!=-1)i+=l;
		else{
			cout<<"NO\n";
			return;
		}
		if(cnt>k){
			cout<<"NO\n";
			return;
		}
	}
	cout<<"YES\n";
	return;
} 
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
  	int T;
	cin>>T;
	while(T--){
		w();
	} 
	return 0;
} 
```

---

## 作者：ZhaoV1 (赞：3)

解析：

依靠简单模拟可知，只能在每一个木桩上跳跃 $1$ 到 $m$ 的距离（起始点和终点也看作木桩就好），那么在每两个相邻木桩之间：如果能一次性从当前木桩跳到下一个木桩，那么将不会损耗游泳机会，并且不会被鳄鱼阻拦。如果跳最远距离 $m$ 也没能跳到下一个木桩，那么就要考虑跳最远距离 $m$ 后，距离下一个木桩的途中有没有鳄鱼，若有则不可能到达对岸，若没有则消耗途中所有游泳次数。

我们用 $a_{i}$ 存所有木桩的下标位置，$cnt$ 记录木桩个数。
```cpp
	for(int i=1;i<=n;i++){
		if(s[i] == 'L') a[++cnt] = i;
	}
	a[0] = 0; a[cnt+1] = n+1;
```

前缀和维护鳄鱼的位置及个数。
```cpp
	for(int i=0;i<=n+1;i++){
		if(s[i] == 'C') sum[i] = sum[i-1] + 1;
		else sum[i] = sum[i-1];
	}
```


完整代码
------------

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int t,n,m,k;
int a[N], sum[N];
string s;

void solve(){
	int cnt = 0;
	int res = 0;
	cin >> n >> m >> k;
	cin >> s;
	s = " " + s;
	sum[0] = 'L';
	s += 'L';
	for(int i=0;i<=n+1;i++){
		if(s[i] == 'C') sum[i] = sum[i-1] + 1;
		else sum[i] = sum[i-1];
	}
	for(int i=1;i<=n;i++){
		if(s[i] == 'L') a[++cnt] = i;
	}
	a[0] = 0; a[cnt+1] = n+1;
	for(int i=0;i<=cnt;i++){//保留一个终点
		if(m >= a[i+1] - a[i]) continue;
		if(sum[a[i+1]] - sum[a[i]+m-1] > 0){
			cout << "NO" << '\n';
			return;
		}else{
			res += a[i+1] - (a[i]+m);
		}
	}
	if(res <= k) cout << "YES" << '\n';
	else cout << "NO" << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：chatoudp (赞：1)

dp 题。

$dp_i$ 表示到达位置 $i$ 最少要游多少米。

可以考虑把两岸当成木桩。

那么若位置 $i$ 有鳄鱼，则 $dp_i$ 为无穷大。

若位置 $i$ 为木桩 $dp_i$ 可以继承在 $m$ 米之内的木桩，和若前一位置为水，则可继承 $dp_{i-1}+1$。

我们可以发现若这一位为水，继承方式与为木桩相同。

这样就可以 AC 了，时间复杂度 $O(nm)$：
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
int dp[200005],n,m,k,t;
char s[200005];
int main(){//'_' T_T ^_^
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		scanf("%s",s+1);
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		s[0]='L';
		for(int i=1;i<=n+1;i++){
			for(int j=1;j<=min(i,m);j++) if(s[i-j]=='L') dp[i]=min(dp[i],dp[i-j]);
			if(s[i-1]=='W')dp[i]=min(dp[i],dp[i-1]+1);
		}
		printf("%d %d\n",dp[n+1],k);
		if(dp[n+1]<=k) printf("yEs\n");
		else printf("No\n");	
	}
	return 0;
}

```

虽然这样可以 AC，但仍可以优化，那就是单调队列优化。

时间复杂度 $O(n)$。

队列中存为木桩的位置，所队首跳不到当前位置，则队首出队。每次继承队首位置。若该位置是木桩，则弹出队尾所有 $dp$ 值大于等于当前位置 $dp$ 值的值，再将当前位置入队。

优化后的 AC 代码：
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
int dp[200005],n,m,k,t;
char s[200005];
int main(){//'_' T_T ^_^
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		scanf("%s",s+1);
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		s[0]='L';
		deque<int> q; 
		q.push_back(0); 
		for(int i=1;i<=n+1;i++){
			if(s[i]=='C') continue;
			while(!q.empty()&&i-m>q.front()) q.pop_front();
			if(!q.empty())dp[i]=dp[q.front()];
			if(s[i-1]=='W')dp[i]=min(dp[i],dp[i-1]+1);
			if(s[i]=='L'){
				while(!q.empty()&&dp[q.back()]>=dp[i]) q.pop_back();
				q.push_back(i);
			}
		}
		if(dp[n+1]<=k) printf("yEs\n");
		else printf("No\n");	
	}
	return 0;
}

```

---

## 作者：Pursuewind (赞：1)

# 题意简述

有一个长度为 $n$ 的河流，可以看作 $n$ 段，每一段有三种情况：水（`W`），木头（`L`）或鳄鱼（`C`）。点 $0$ 和 $n+1$ 看作木头。用一个字符串 $s$ 表示河道的情况。

一个人从点 $0$ 出发，如果他在木头上，那么他可以向前走 **最多** $m$ 步，否则，他只能向前走一步。走到有鳄鱼的河段就死了。他最多能在 $k$ 段中停留，请问他是否能到达点 $n+1$。

数据范围：$n,k \le 2 \times 10^5$，$m \le 10$。

# 做法

$m$ 很小，考虑 DP。

设 $dp_{i,0/1}$ 表示从点 $0$ 到点 $i$，最少的经过水中的数量。第二维中 $0$ 表示该点为木头，$1$ 表示该点为水。

显然的转移，看代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int dp[N][2]; //在岸上/水里 
int n, m, k;
void solve()
{
	cin >> n >> m >> k;
	string s; cin >> s; s = "L" + s + "L";
	for (int i = 0; i <= n + 1; i ++){
		dp[i][0] = dp[i][1] = 1e18;
	} 
	dp[0][0] = 0;
	for (int i = 1; i <= n + 1; i ++){
		if (s[i] == 'C'){
			continue;
		}
		if (s[i] == 'L'){ //是木头，从前面的水里上来：WL或LL
			dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
		}
		else{ //是水，不管前面是什么，花费+1：WW或LW
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
		for (int j = i - 1; j >= max(0ll, i - m); j --){ //枚举前驱
			if (s[j] == 'C'){ //是鳄鱼，无法转移
				continue;
			}
			if (s[i] == 'W'){ //是水
				if (s[j] == 'L'){ //从木头上跳过来，花费+1
					dp[i][1] = min(dp[i][1], dp[j][0]) + 1;
				}
              //我们不需要考虑从水里过来的情况，因为这已经在上面讨论过了
			}
			else{ //是木头
				if (s[j] == 'L'){ //从木头上跳过来，花费不变
					dp[i][0] = min(dp[i][0], dp[j][0]);
				}
              //我们不需要考虑从水里上来的情况，因为这已经在上面讨论过了
			}
		}
	}
	if (dp[n + 1][0] > k) cout << "NO\n"; //需要 >k 次入水
	else cout << "YES\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
```

---

## 作者：SnapYust (赞：0)

### 更好的阅读体验

[这里](https://www.cnblogs.com/snapyust/p/18300198)

### 题目传送门

[Test of Love](https://www.luogu.com.cn/problem/CF1992D)

### 思路

模拟贪心，好像很多 Div3 的题都是这样。

先来个分类讨论，假设当前为 $i$，假设输入的字符串为 $c$，那么：

* $c_i=$`L`，那么他可以向前跳最多 $m$ 格，因为他最多只能游 $k$ 格，所以我们可以贪心地尽量选择圆木。如果往后的 $m$ 格都没有圆木，那么就跳进离 $i$ 最远的水里。如果连水都没有，只有鳄鱼，那么输出 `NO`。

* $c_i=$`W`，那么操作就很简单了，直接从 $i$ 开始向后枚举，如果可以到达圆木，那么就站在圆木上，如果到达不了，那么输出 `NO`。

我们可以把 $c_0$ 和 $c_{n+1}$ 看作是个圆木。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
char c[200005];
void solve(){
	memset(c,0,sizeof(c));
    cin>>n>>m>>k;c[0]='L',c[n+1]='L';
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=0;i<=n+1;){
        bool b=0;
        if(i==n+1){cout<<"YES"<<endl;return;}
        if(c[i]=='W'){
            for(int j=i+1,l=1;j<=n+1;l++,j++){
                if(c[j]=='C'){cout<<"NO"<<endl;return;}
                if(c[j]=='L'){
                    k-=l;
                    if(k<0){cout<<"NO"<<endl;return;}
                    i=j;break;
                }
            }
            continue;
        }
        for(int j=min(i+m,n+1);j>=i+1;j--)if(c[j]=='L'){i=j;b=1;break;}
        if(b)continue;
        for(int j=min(i+m,n+1);j>=i+1;j--)if(c[j]=='W'){i=j;b=1;break;}
        if(b)continue;
        cout<<"NO"<<endl;return;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;while(t--)solve();
    return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑 DP。

### 状态设计

$f_i$ 是第 $i$ 个地方能不能走到。

### 初始状态

把 $0,n+1$ 标为陆地（起点、终点）。

$f_0=1$ 是初始状态。

### 转移

游是可消耗的，能不用就不用（小贪心）。

如果从上一块路地可以跳过来就跳，否则从上一个位置游过来。

并且把可以游的次数减 $1$，显然这样不会白费游的次数。

这样陆地枚举是 $O(n)$，暴力转移时间会爆炸。

考虑预处理 $t_i$，表示上一个陆地的位置，来方便跳。

### 答案

最后结果是 $f_{n+1}$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k,t[200001];
bool f[200001];
string s;
int main(){
    for(cin>>T;T;--T){
        cin>>n>>m>>k>>s;
        s="L"+s+"L";
        memset(f,0,sizeof(f));
        f[0]=1;
        for(int i=1,las=0;i<s.size();i++){
            if(s[i]!='L')
                t[i]=las;
            else
                t[i]=las,las=i;
        }
        for(int i=1;i<=n+1;i++){
            if(s[i]=='C')
                continue;
            if(i-t[i]<=m){
                f[i]|=f[t[i]];
                if(f[i])
                    continue;
            }
            if(k)
            	k--,f[i]|=f[i-1];
        }
        cout<<(f[n+1]?"yEs":"nO")<<'\n';
    }
    return 0;
}
```

---

## 作者：Wind_love (赞：0)

## 思路
本题使用模拟实现。

如果当前位置为岸边或木头上，则可以跳跃。选择可跳跃范围内最远的木头，若没有，则选择最远的水面。若都没有，则直接输出 NO 即可。

如果当前位置为水面，则直接向前一格即可。

如果当前位置有鳄鱼，则输出 NO 并跳出循环。

重复以上步骤，若可以到达终点，则输出 YES。
## 代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,m,k;
        string s;
        cin>>n>>m>>k;
        cin>>s;
        int p=-1,cnt=0,f=0;
        while(p<n){
        	if(s[p]=='L'||p==-1){
				int maxp=-1,maxp2=-1;
	        	for(int i=p+1;i<=p+m;i++){
	        		if(i>n-1){
	        			maxp=1e9;
	        			maxp2=1e9;
	        			break;
	        		}
	        		if(s[i]=='L'){
	        			maxp=max(maxp,i);
					}
					if(s[i]=='W'){
						maxp2=max(maxp2,i);
					}
				}
				if(maxp!=-1)p=maxp;
				else if(maxp2!=-1) p=maxp2;	
				else{
					cout<<"NO";
					f=1;
					break;
				}
			}
        	else{
        		p++;
        		cnt++;
        		if(s[p]=='C'){
        			cout<<"NO";
        			f=1;
        			break;
				}
			}
			if(cnt>k){
				cout<<"NO";
				f=1;
				break;
			}
		}
		if(!f)cout<<"YES";
        cout<<"\n";
    }
    return 0;
}

---

## 作者：__int127 (赞：0)

# 题解：CF1992D Test of Love

[**题目传送门**](https://www.luogu.com.cn/problem/CF1992D)

## 题目大意

本题有 $t$ 组测试样例。

有一条长 $n$ 米的河流 $s$ 表示为 $n$ 个 $1m$ 的河段，第 $i$ 个河段表示为 $s_i$，$s_i\in\{$`L`$,$`C`$,$`W`$\}$，分别为 “原木”、“鳄鱼”和“水”河段。你最开始在 $s_0$，希望到达 $s_{n+1}$。

移动规则如下：

- 如果在 $s_0$ 或原木上，你可以移动不超过 $m$ 米。

- 如果在水中，只能游到下一个河段（特别地，如果在 $s_n$ 则直接登岸）。

- 在水中次数不能超过 $k$ 次。

- 不能在鳄鱼河段登陆。

问是否能到达 $s_{n+1}$，能输出 `YES`，否则输出 `NO`。

### 数据范围

$1\le t\le10^4$，$1\le n\le2\cdot10^5$，$1\le m\le10$，$0\le k\le2\cdot10^5$，$s_i\in\{$`L`$,$`C`$,$`W`$\}$。

## 思路

可以使用 $vis$ 数组记录每个河段的登陆情况（$1$ 为可以登陆，$0$ 为不可登陆），其中 $vis_0=1$。对于 $vis_i$，如果有 $vis_j=1(j<i)$，则可以到达 $s_i$。因为题目要求水中只能移动 $1m$，且对“下水”次数有要求，所以当 $j=i-1$ 时要特判。另外，如果 $s_{i-1}$（偏移量）是 `C`，直接将 $vis_i$ 赋值成 $0$ 就行了。（鳄鱼河段不可登陆！）

接下来判断是否能到达 $s_{n+1}$ 就比较简单了，如果 $vis_{n+1}=1$ 则可以到达。

不能到达有两种情况：

1. 存在一最小的 $i$，使得 $vis_{\max{0,i-m}}\sim vis_{i-1}$ 均 $\ne1$。

1. “下水”次数 $>k$。

循环代码（以下使用了快读快写）：

```cpp
int vis[N] = {}, wt = 0, flag = 0;
vis[0] = 1;
for (int i = 1; i <= n + 1; ++i){
	if (s[i - 1] == 'C'){
		continue;
	}
	int ans = -1;
	for (int j = i - 1; j >= max(i - m, 0ll); --j){
		if (vis[j] != 0 && (s[j - 1] != 'W' || j == i - 1)){
			ans = j;
		}
	}
	if (ans == -1 || wt > k){
		if (wt > k){
			flag = 1;
		}
		write_string("NO");
		break;
	}
	if (ans == i - 1 && s[ans - 1] == 'W'){
		++wt;
		vis[i] = 1;
	} else {
		vis[i] = 1;
	}
	
}
if (wt > k && !flag){
	write_string("NO");
	continue;
}
if (vis[n + 1] == 1){
	write_string("YES");
}
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl putchar('\n')
inline int read(){
    char ch, c;int res;
    while (ch = getchar(), !isdigit(ch))c = ch;
    res = ch - 48;
    while (ch = getchar(), isdigit(ch))res = (res << 3) + (res << 1) + ch - 48;
    if (c == '-')res = (res ^ -1) + 1;
    return res;
}
inline string read_string(char p = ' '){
	string str = "";
	char ch = getchar();
	while (ch == ' ' || ch == '\n' || ch == '\r')ch = getchar();
	if (p == ' ')
		while (ch != ' ' && ch != '\n' && ch != '\r')str += ch, ch = getchar();
	else
		while (ch != p)str += ch, ch = getchar();
	return str;
}
inline void write_string(string str, int p = 0, int len = 0, char ch = '\n'){
	len = str.size();
	for (int i = p; i < len; i++)putchar(str[i]);
	if (ch != '!')putchar(ch);
	return;
}
const int N = 2e5 + 5;
int T = 1, n, m, k;
signed main(){
	T = read();
	while (T--){
		n = read(), m = read(), k = read();
		string s;
		s = read_string();
		int vis[N] = {}, wt = 0, flag = 0;
		vis[0] = 1;
		for (int i = 1; i <= n + 1; ++i){
			if (s[i - 1] == 'C'){
				continue;
			}
			int ans = -1;
			for (int j = i - 1; j >= max(i - m, 0ll); --j){
				if (vis[j] != 0 && (s[j - 1] != 'W' || j == i - 1)){
					ans = j;
				}
			}
			if (ans == -1 || wt > k){
				if (wt > k){
					flag = 1;
				}
				write_string("NO");
				break;
			}
			if (ans == i - 1 && s[ans - 1] == 'W'){
				++wt;
				vis[i] = 1;
			} else {
				vis[i] = 1;
			}
			
		}
		if (wt > k && !flag){
			write_string("NO");
			continue;
		}
		if (vis[n + 1] == 1){
			write_string("YES");
		}
    }
	return 0;
}
```

---

## 作者：tallnut (赞：0)

# 思路
考虑贪心。
- 如果当前格子是水：只能游。
- 是鳄鱼：只能到鳄鱼格说明无解。
- 是木头：如果在这个木头之后 $m$ 格内还有木桩，容易证明跳到水里或较近的木桩上一定不优，因此跳到最远木桩上；如果只有水和鳄鱼，就跳到最远的水上。
  
然后模拟就完了。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/166418472)。
```cpp
// NOTE: "[EDIT]" means you should edit this part by yourself
#include <bits/stdc++.h>
// [EDIT] please enable this line if there are many tests
#define MULTITEST
using namespace std;
// [EDIT] if you want to copy some templates, please paste them here

typedef long long ll;
#define rep1(i,x,y) for (int i = (x);i <= (y);i++)
#define rep2(i,x,y) for (int i = (x);i >= (y);i--)
#define rep3(i,x,y,z) for (int i = (x);i <= (y);i += (z))
#define rep4(i,x,y,z) for (int i = (x);i >= (y);i -= (z))
#define cl(a) memset(a,0,sizeof(a))
// [EDIT] define some constants here

// [EDIT] define some variables, arrays, etc here
int n,m,k,pos,swim;
string s;
// [EDIT] a function to solve the problem
void solve()
{
    //input
    cin >> n >> m >> k >> s;
    //solve
    s = 'L' + s;
    pos = 0;
    swim = 0;
    while (pos <= n)
    {
        //如果当前格为鳄鱼：不行
        if (s[pos] == 'C')
        {
            cout << "NO\n";
            return;
        }
        //如果当前格为水：只能游泳
        else if (s[pos] == 'W')
        {
            pos++;
            swim++;
        }
        else
        {
            //否则为木桩
            //跳到离当前位置最远的木桩
            int searchpos = pos + m;
            //如果已经到达河对岸
            if (searchpos > n) break;
            //如果不是木桩
            while (s[searchpos] != 'L' && searchpos > pos)
                searchpos--;
            //如果前面还有木头
            if (searchpos > pos) pos = searchpos;
            else
            {
                //已经没有木头了，找水
                searchpos = pos + m;
                while (s[searchpos] != 'W' && searchpos > pos)
                    searchpos--;
                //如果前面还有水
                if (searchpos > pos) pos = searchpos;
                else
                {
                    //全是鳄鱼，过不去
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    //output
    if (swim <= k)
        cout << "YES\n";
    else
        cout << "NO\n";
    //clear
    
}
int main()
{
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif
    int t;
#ifdef MULTITEST
    cin >> t;
#else
    t = 1;
#endif
    while (t--)
        solve();
#ifndef ONLINE_JUDGE
    cout << "\n---------------\n";
    system("pause");
#endif
}
```

---

## 作者：GavinCQTD (赞：0)

# 题解：CF1992D Test of Love

## 思路

我们可以模拟过河过程解决问题。令 $river_i$ 表示河流中的第 $i$ 个元素，之后维护一个变量 $now$，代表当前 ErnKor 所在的位置。由于 ErnKor 需要从左岸到达右岸，所以我们需要令 $river_0 = river_{n+1} = L$，之后使用 while 循环判断是否到达右岸进行模拟。每次模拟无非两种情况。

- $river_{now} = L$
  
- $river_{now} = W$
  
在第一种情况下，我们应优先枚举**最远的木头落脚点**，若没有，再枚举最远的水域。

在第二种情况下，我们只需要模拟往前游一格即可。

## 核心代码

```cpp
while(now<=n){
    if(river[now]=='L'){
        bool hasWood=0;
        for(int i=now+m;i>=now+1;i--){
            if(river[i]=='L'){now=i;hasWood=1;break;}
        } // 枚举最远木头
        if(hasWood==0){
            for(int i=now+m;i>=now+1;i--){
                if(river[i]!='C'){now=i;hasWood=1;break;}
            } // 枚举最远水域
            if(hasWood==0){can=0;break;}
        }
    } // 当前位置为木头
    else if(river[now]=='W'){
        if(river[now+1]=='C'){can=0;break;}
        if(k==0){can=0;break;}
        now++;
        k--;
    } // 当前位置为水域
}
```

---

