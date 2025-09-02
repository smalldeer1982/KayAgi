# [NERC 2018] Lazyland

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) L 题。

## 题目描述

一个城市里有 $n$ 个人，和 $k$ 种职业，其中，每个人都有一个现在正在从事的职业 $a_i$，但是很遗憾，由于某些职业的空缺，使得这个城市根本无法继续正常生存下去。

你作为一城之主，自然不希望看到自己的城市这样子下去，你决定说服其中的某些人，使得每种职业都有人在做，对于每个人 $i$，你需要耗费 $b_i$ 的时间去说服。

你需要求出你去说服的时间的最小值。

## 说明/提示

对于所有的数据，保证 $1 \leq k \leq n \leq 10^5$，$1 \leq a_i \leq k$，$1 \leq b_i \leq 10^9$。

对于样例一，分别令 $1$，$6$，$8$ 号市民去从事 $2$，$4$，$6$ 号职业。

## 样例 #1

### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2```

### 输出

```
10```

## 样例 #2

### 输入

```
3 3
3 1 2
5 3 4```

### 输出

```
0```

# 题解

## 作者：佬头 (赞：3)

~~进了最优解第一，不得交发题解庆祝一下。~~
## Description
现有 $n$ 个人和 $k$ 种职业，其中第 $i$ 个人正在从事职业 $a_i$。但是某些职业被空缺出来了，请你说服其中的某些人，使得每种职业都有人在做，对于第 $i$ 个人，你需要耗费 $b_i$ 的时间去说服。求出[**说服时间的最小值**](https://www.luogu.com.cn/problem/P9802)。

## Solution
显然若职业 $j$ 正有 $w_j$ 个人在从事，我们肯定优先说服 $b$ 较小的人去从事其他职业，并且说服的人数不能多于 $w_j-1$。记这 $w_j$ 个人中 $b$ 最大的人的说服时间为 $maxx_j$，显然我们将 $w_j$ 个人全部说服去别的职业后仍然还要说服一个人回来，那么不如直接不动 $maxx_j$，考虑将剩下 $w_j-1$ 个人说服去空缺的职业。

若题目给定的 $a_i$ 有 $A$ 种，则显然我们只需要说服 $k-A$ 个人去从事空缺职业即可，并且我们有 $n-A$ 个人可以说服（不能说服的就是 $maxx_j$）。接下来思路就显得十分清晰了，我们只需要从这 $n-A$ 个人里面选出 $k-A$ 个 $b$ 最小的求个和就行了。

时间复杂度 $\mathcal O(n\log n)$。~~排序的 log 显然躲不掉。~~

## Code
排序的方法有很多种，既然其他题解都是直接 `sort()`，那我就来一发优先队列 ~~（带点小常数）~~。
```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N = 100005;
int n, k, a[N], b, maxx[N];
long long ans;
priority_queue <int, vector <int>, greater <int>> q;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(long long x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	n = read(), k = read();
	for(int i = 1; i <= n; ++ i) a[i] = read();
	for(int i = 1; i <= n; ++ i){
		b = read();
		if(!maxx[a[i]]) maxx[a[i]] = b, k --;
		else if(maxx[a[i]] < b) q.push(maxx[a[i]]), maxx[a[i]] = b;
		else q.push(b);
	}
	while(k --) ans += q.top(), q.pop();
	write(ans);
	return 0;
}
```
## Similar
[**CF1089L Lazyland**](https://www.luogu.com.cn/problem/CF1089L)

---

## 作者：Nazale_ (赞：2)

思路：
------------
考虑**贪心**。观察样例会发现职业有空缺，正是因为有**多人重复同一职业**。由此出发，我们使**更容易劝服的**跳槽，去填补空缺即可，最终得到说服时间的最小值。


## 实现：
1. **排序**没的说，利用结构体存储每个人本身的职业与说服时间，重载运算符或者搞个函数。
2. 再用一个**桶**记录每个职业原本有多少人，用于在后面进行判断（由排序易知，我们肯定会让每个职业留下至少一个最难说服的人）。
3. **map 做映射**还是很好用的，这里 $mp[i]$ 存储 $i$ 职业是否有人从事，类似一个 $vis[i]$。


------------
## 防止 T 的优化：
1. 最后枚举的过程事实上我们并不关注哪个职业没被选，**只关注几个职业还有空缺需要去顶上**所以提前处理出 $sum$。
2. 枚举需要说服哪个人时可以**记录上一次说服的人的位置 $lst$**，下次从他的下一个开始判断可否满足要求。

### 具体细节见代码：
##### 550ms，还是比较快的。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,k,ans,sum,lst;
int cnt[maxn];
struct per{
	int job;
	int t;
	friend bool operator<(per x,per y){
		return x.t<y.t;
	}
}a[maxn];
map<int,bool> mp;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i].job;
		cnt[a[i].job]++;
		mp[a[i].job]=true;
	}
	for (int i=1;i<=n;i++){
		cin>>a[i].t;
	}
	sort(a+1,a+1+n);
	for (int i=1;i<=k;i++){
		if(!mp[i]) sum++;
	}
	while(sum--){
		for (int j=lst+1;j<=n;j++){
			if(cnt[a[j].job]>=2){
				ans+=a[j].t;
				cnt[a[j].job]--;
				lst=j;
				break;
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：mbzdf (赞：1)

# P9802 题解

[传送门](https://www.luogu.com.cn/problem/P9802)

## 题目大意
> 有 $n$ 个元素与 $k$ 个集合，给出每个元素所属的集合与这个元素改变所属集合的代价，求使所有集合不为空集的最小总代价。

## 分析一下
> ~~我教练曾说过：“ 当你在一道简单题中发现了求最值，那这题不是 **DP** 就是**贪心**”~~

容易发现，这道题是一道贪心。
#### 那么具体思路呢

首先，我们贪的是什么？是代价。那么我们肯定是从代价最小的元素入手，所以考虑排序。

然后，因为代价不为负数，所以我们能不改则不改，即如果目前代价最小的是一个集合的唯一一个元素，那么我们不能改动它，直接跳过它寻找下一个代价最小的元素。

### 一个需要注意的事情

>$1 \leq b_i \leq 10^9$。

总代价有可能爆 int，需要开 long long。

## AC 代码 ~~（抄题解的不是好孩子）~~
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, k;
struct people
{
	int a;
	int b;
}p[100005];
bool cmp(people x, people y)
{
	return x.b < y.b;
}
int last[100005];
int main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; ++i)
		cin >> p[i].a;
	for(int i = 1; i <= n; ++i)
		cin >> p[i].b;
	sort(p + 1, p + n + 1, cmp);
	for(int i = 1; i <= n; ++i)
		last[p[i].a] = i;
	int sum = 0;
	for(int i = 1; i <= k; ++i)
		if(last[i] == 0)
			++sum;
	long long int ans = 0;
	for(int i = 1; i <= sum; ++i)
	{
		if(last[p[i].a] == i)
		{
			++sum;
			continue;
		}
		ans += p[i].b;
	}
	cout << ans << endl;
}
```

---

## 作者：过氧化氢_syq0057 (赞：1)

## Solution

非常简单的贪心题。

考虑每种职业多出来的人，假设目前有 $cnt$ 种职业，那么显然我们需要说服 $k-cnt$ 个人去干别的职业，显然答案即为在多出来的人中选 $k-cnt$ 个说服代价最小的，求和即为答案。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cmath>
#include <queue>
#include <map>
using namespace std;
const int N = 100005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
inline int read() {
	int x = 0, f = 1; char ch;
	ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}
int n, k;
int a[N];
int t[N];
vector<int> tt[N];
ll b[N];
ll c[N];
int op;
ll ans;
int main() {
	scanf("%d%d", &n, &k);
	for (int i=1; i<=n; i++)
		scanf("%d", &a[i]), t[a[i]]++, tt[a[i]].push_back(i);//开桶记录多出来的人和他们的编号
	for (int i=1; i<=n; i++)
		scanf("%lld", &b[i]);
	int cnt = 0, maxn = 0, maxid = 0;
	for (int i=1; i<=k; i++) {
		if (t[i]) cnt++;
		if (t[i] <= 1) continue;
		maxn = 0, maxid = 0;
		for (int j=0; j<(int)tt[i].size(); j++) {
			if (b[tt[i][j]] > maxn) {
				maxn = b[tt[i][j]];
				maxid = tt[i][j];//这里最大代价留下来干当前职业
			}
		}
		for (int j=0; j<(int)tt[i].size(); j++) {
			if (tt[i][j] != maxid) {
				c[++op] = b[tt[i][j]];//待选择的人
			}
		}
	}
	sort(c + 1, c + 1 + op);//从小到大排序方便选择
	for (int i=1; i<=k-cnt; i++)//选k-cnt个人
		ans += c[i];
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：_sun_ (赞：1)

# P9802	[NERC2018] Lazyland

## 贪心

### 思路

记录没有人做的工作的数量，按照说服时间依次说服，如果说服后出现新的没有人做的工作就不进行说服。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
struct citizens
{
    int a,b;  
} m[100010]; // 记录每个市民的工作和说服时间
bool cmp(citizens x,citizens y)
{
    return x.b<y.b; // 按照说服时间从小到大排序
}
int job[100010]; // 记录做每个工作的人的数量
int main()
{
    int n,k;
    cin >> n >> k;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> m[i].a;
        job[m[i].a]++;
    }
    int sum=0;
    for (int i = 1; i <= k; i ++ )
        if(job[i]==0)
            sum++; // 记录没人做的工作的数量
    for (int i = 1; i <= n; i ++ )
        cin >> m[i].b;
    sort(m+1,m+n+1,cmp); // 排序
    long long ans=0;
    for (int i = 1; i <= n; i ++ )
    {
        if(sum==0)
        {
            cout << ans;
            return 0;
        }
        if(job[m[i].a]>1) // 只有一个人做就不进行说服
        {
            ans+=m[i].b;
            sum--;
            job[m[i].a]--;
        }
    }
}
```


---

## 作者：BugGod (赞：1)

考虑贪心。显然的，我们尽量使那些容易被说服的人转职。但是，我们要注意，不能让某个职业所有人都转职。比如说，$i$ 职业剩下一个说服时间为 $b_k$ 的人，如果让他转职，耗费 $b_k$，再让一个人 $x$ 转来，耗费 $b_x$。

$$\because b_i\ge 1(i\in \mathbb{N}^*)$$

$$\therefore b_k+b_x>b_x$$

即直接让 $x$ 转去更省时间。

具体实现看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[100010],b[100010],cnt,ans;
map<int,int>m;//统计哪些职业没有人
vector<int>job[100010];//统计每个职业的人耗时
vector<int>jo;//统计所有人耗时（从小到大且每个原来有人的职业剩余一个）
signed main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	cin>>n>>k;
	cnt=k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)
	{
		m[a[i]]=1;
		job[a[i]].push_back(b[i]);
	}
	for(int i=1;i<=k;i++)if(job[i].size())sort(job[i].begin(),job[i].end();
	//cout<<(*job[1].end())<<endl;
	//job[1].erase(job[1].end());
	for(int i=1;i<=k;i++)if(job[i].size())job[i].erase(job[i].end()-1);//剩余一个人留守岗位，留下最“顽固”的，尽量说服容易接受的
	//cout<<1;
	for(auto i:m)cnt--;//统计缺人的职业数量
	for(int i=1;i<=k;i++)
	{
		for(int j=0;j<job[i].size();j++)jo.push_back(job[i][j]);
	}
	sort(jo.begin(),jo.end());
	for(int i=0;i<jo.size()&&cnt>0;i++)ans+=jo[i],cnt--;
	cout<<ans;
	return 0;
}
```

---

## 作者：fangjianan (赞：1)

## 解法说明  
这是一道贪心题。  
首先，如果某个职位有多个人同时工作，那么只能留一个人。题目要求用最短的时间转变职业，那么就留下说服时间最长的一个人。  
创建一个数组 $a$，存放每个人的职业和说服时间，按说服时间对每个人进行升序排序。再创建一个数组 $cnt$，$cnt_i$ 表示第 $i$ 种职业正在工作的人数。  
从头开始检索 $a$ 数组。如果当前检索的人的职业有至少两个人在工作，那么这个人就要转变职业了，同时 $cnt$ 数组中对应的一项也要减一。  
## 注意事项  
注意数据范围，存放结果的变量一定要开 long long！  
(感谢仁慈的出题人没有改成高精度)
## 奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,cnt[100001],now; //cnt已经解释过，now表示当前有人干活的职位。 
long long ans; //存放结果的变量 
struct people{ //每个人的信息 
	int job,time;
}a[100001];
bool cmp(people x,people y){ //按说服时间排序 
	return x.time<y.time;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].job;
		if(cnt[a[i].job]==0) now++; //初始化now 
		cnt[a[i].job]++;
	}
	for(int i=1;i<=n;i++) cin>>a[i].time;
	sort(a+1,a+n+1,cmp);
	int i=1;
	while(now<k){ //当还有职业没有人干的时候，继续检索 
		if(cnt[a[i].job]>1){ //如果该职业至少有2人干 
			cnt[a[i].job]--;
			now++;
			ans+=a[i].time;
		}
		i++; //检索下一个人 
	}
	cout<<ans<<endl;

	return 0;
}

```


---

## 作者：xhx_0215 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9802)

## 题意
有 $n$ 个人和 $k$ 种职业，输入 $n$ 个数字，第 $i$ 个数字 $a_{i} $ 代表第 $i$ 个人的现在职业, 然后再输入 $n$ 个数字，第 $i$ 个数字 $b_{i} $ 代表第 $i$ 个人要改变现在的职业的时间，求第 1 个到 $n$ 个每个职业都有人的干的最小时间。

## 解法
首先，很明显这是一道贪心题。
如果某个职位有多个人，那么就留下说服时间最长的一个人。如果某个职位有多个人，那么就留下说服时间最长的一个人。
$sum_{i}$  数组表示第 $i$ 个职业正在工作的人数
# CODE:
```c
#include <iostream>
#include <algorithm>
using namespace std;
int n,k,sum[100005]={0},cnt; //cnt表示现在有人干的职位数量 
long long ans=0;//存放答案 
struct p //每个人的信息 
{
	int work;
	int time;
}a[100005];
bool cmp(p p1,p p2)
{
	return p1.time<p2.time;
}
int main()
{
	cin>>n>>k;
	for (int i=1; i<=n; i++){
		cin>>a[i].work;
		if (sum[a[i].work]==0){
			cnt++;//cnt的初始化 
		}
		sum[a[i].work]++;
	}
	for (int i=1; i<=n; i++){
		cin>>a[i].time;
	}
	sort (a+1,a+n+1,cmp);
	int j=1;
	while(cnt<k){ //当还有职业没有人干的时候,就继续检索,一直搜到有为止. 
		if(sum[a[j].work]>1){ //如果该职业至少有 2 人干 
			sum[a[j].work]--; //就把时间最短的改掉 
			cnt++;
			ans+=a[j].time;
		}
		j++; //搜下一个人 
	}
	cout<<ans;
	return 0;
}


```
## 注意：
ans 一定要开 long long,

ans 一定要开 long long,


ans 一定要开 long long

重要的事情说三遍

---

## 作者：Weijiameng (赞：0)

# P9802 [NERC2018] Lazyland 题解
## 思路分析：
本题是简单**贪心**，贪心策略：按照时间从小到大遍历，如果这个人可以干别的工作，那么就替换工作，直到所有人的工作数之和大于等于要求工作数。
## 代码分析：
### 1. 个人信息：
用一个结构体存储个人信息（原始工作和劝说时间），接着按照**劝说时间**由小到大排序。
### 2. 工作信息：
读入每个人的工作时，用 map 映射出每种工作的人数，`map.size()` 即为目前所有人的工作数之和。
### 3. 贪心：
设 $t$ 为目前所有人工作数之和，初始化 `t=map.size()`，然后遍历个人信息结构体，如果**干这个人工作的人不止他一个**，那么他就可以被他换掉，干一种与所有人都不同的工作，即 `t++`，同时让总时间加上劝说这个人的时间，如果总工作数大于等于要求的工作数，即 `t>=k` 贪心结束
**最后记得开 long long，不开 long long 见祖宗**。
## AC代码
```cpp
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
struct node{
    ll job,time;
}person[maxn]; //定义结构体
bool cmp(node a,node b){
    return a.time<b.time;
} //排序用比较函数
map <ll,ll> mp;
int main(){
    ll n,k,ans=0,t;
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;i++) scanf("%lld",&person[i].job),mp[person[i].job]++;
    for(ll i=1;i<=n;i++) scanf("%lld",&person[i].time);
    t=mp.size();
    if(t>=k){
        printf("0");
        return 0;
    } //特判：如果工作数已经够了，直接输出0，结束程序
    sort(person+1,person+n+1,cmp); //排序
    for(ll i=1;t<k;i++)
        if(mp[person[i].job]>1){
            ans+=person[i].time;
            mp[person[i].job]--;
            t++;
        } //贪心过程
    printf("%lld\n",ans);
    return 0;
}

---

## 作者：违规用户名U1075140 (赞：0)

# P9802 [NERC2018] Lazyland

[题目传送门](https://www.luogu.com.cn/problem/P9802)

### 题意
有 $n$ 个人和 $k$ 种职业，输入每个人的现在职业 $a_i$ 和改变职业所用的代价 $b_i$，求要让每种职业都有人干的最小代价。

### 思路
因为 $k \le n$，所以恒有解。可以考虑贪心，先对代价进行排序，再在保证当前职业至少有一人的前提下将这个人改变职业。

### 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int n,k,zhiye[100001]={0},quede=0;long long zuihou=0;
struct ren{
	short congshi;
	int shuofu;
}a[100001];//用结构体定义每个人的当前职业和所用时间 
bool cmp(ren p,ren q){
	return p.shuofu<q.shuofu;
}
int main(){
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>a[i].congshi;
		zhiye[a[i].congshi]++;
	}
	for(int i=0;i<n;i++){
		cin>>a[i].shuofu;
	}
	sort(a,a+n,cmp);//根据时间排序 
	for(int i=1;i<=k;i++){
		if(zhiye[i]==0){
			quede++;
		}
	}
	quede=k-quede;
	for(int j=0;j<n;j++)
	{
		if(quede>=k){
			break;
		}
		if(zhiye[a[j].congshi]>1){
			quede++;
			zhiye[a[j].congshi]--;
			zuihou+=a[j].shuofu;
		}//挨个说服
	}
	cout<<zuihou;
}
``````

---

## 作者：UniGravity (赞：0)

## P9802 [NERC2018] Lazyland

### 思路分析
这道题可以用**贪心**做法。

首先可以发现对于每一种职业，都需要**至少**一个人完成。  
那么显然可以想到让 $b_i$（耗费时间）**最大**的人不转职，其他的人加入**待转职**列表 $c$。

统计一下没人做的职业数量 $need$，那么最后的答案就是 $c$ 中最小的 $need$ 个数。

至于具体做法，扫一遍得出每个职业 $b_i$ 最大的人，其他加入 $c$，最后直接对 $c$ 进行排序即可。

### 完整代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100005;

int n, k;
int job[N];
vector< int > a[N];

int can[N], cnt = 0;
int need = 0;

signed main() {
	scanf("%lld %lld", &n, &k);
	
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &job[i]);
	}
	int t;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &t);
		a[job[i]].push_back(t);
	}
	
	for (int i = 1; i <= k; i++) {
		if (a[i].size() == 0) {
			need++;
		} else if (a[i].size() > 1) {
			int maxa = -1;
			for (int j = 0; j < a[i].size(); j++) {
				if (maxa == -1 || a[i][j] > a[i][maxa]) {
					maxa = j;
				}
			}
			for (int j = 0; j < a[i].size(); j++) {
				if (j != maxa) {
					can[++cnt] = a[i][j];
//					printf("job %d %d\n", i, a[i][j]);
				}
			}
		}
	}
	
	sort(can + 1, can + cnt + 1);
	int ans = 0;
	for (int i = 1; i <= need; i++) {
		ans += can[i];
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：linyukun (赞：0)

## 1. 前言
本文的分析会比较通俗，自己要多去思考，麻烦一定 _仔细全部看完_，有异议、不懂或认为可以优化请私信反馈呢。  

## 2. 题目解析：
首先，这是一道贪心题。我们来分析一下怎么去贪。
+ 显而易见的，每次去劝说那个时间更小的人是最优的方案。
+ 我们就考虑排序并从小到大进行选取。
+ 并且，对劝说的分配没有要求，我们就可以统计一下 $k$ 个职业没出现的有多少，只需要这个数量的人被劝说即可。

但是，这思路有一个小问题。每个工作可能所有人都被劝说导致没人干了。  
所以，我们需要一个数组来存储那个时间最长的人，让他成为最后留下干活的。
众所周知的是，快排是不稳定的，无法保证我们记录的最长人在有重复时间的情况下是最后被遍历到的。  
严谨起见，我们最好还是处理一下。  
我们存储最长时间相同的人中最靠后那位的编号，然后排序的第二关键字为输入顺序，就可以保证这个留下的人最好被遍历到了。

## 3. 提示要点：
* 处理最大值时，使用 $\ge$ 来保证留守人的输入次序最靠后。

## 4. 代码写作：
理论存在，实践开始。  

代码理有详细的注释幺
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,maxb[100005],maxid[100005],cnt;
bool b[100005];
struct aaa{
	int a,b,id;
}a[100005];
bool cmp(aaa a,aaa b){
	if(a.b==b.b)return a.id<b.id;
	return a.b<b.b;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		maxb[i]=-1;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].a;
		a[i].id=i;
		if(b[a[i].a]==0){
			k--;
			b[a[i].a]=1;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].b;
		if(a[i].b>=maxb[a[i].a]){
			maxb[a[i].a]=a[i].b;
			maxid[a[i].a]=a[i].id;
		}
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;k>0;i++){
		if(a[i].id!=maxid[a[i].a]){
			cnt+=a[i].b;
			k--;
		}
	}
	cout<<cnt;
	return 0;
}
```

## 5. 总结鸣谢：
**本题是一道考验思维和排序技巧的贪心，难度适中。**  
**另：还有感谢管理大大的的审核。**

---

