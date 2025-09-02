# [SDCPC 2023] Matching

## 题目描述

给定长度为 $n$ 的整数序列 $a_1, a_2, \cdots, a_n$，我们将从该序列中构造出一张无向图 $G$。具体来说，对于所有 $1 \le i < j \le n$，若 $i - j = a_i - a_j$，则 $G$ 中将存在一条连接节点 $i$ 与 $j$ 的无向边，其边权为 $(a_i + a_j)$。

求 $G$ 的一个匹配，使得该匹配中所有边的边权之和最大，并输出最大边权之和。

请回忆：无向图的匹配，指的是从该无向图中选出一些边，使得任意两条边都没有公共的节点。特别地，不选任何边也是一个匹配。

## 样例 #1

### 输入

```
3
9
3 -5 5 6 7 -1 9 1 2
3
-5 -4 -3
3
1 10 100
```

### 输出

```
30
0
0
```

# 题解

## 作者：scp020 (赞：8)

# P9562 [SDCPC2023] G-Matching 题解

签到题，是这场比赛第三简单的题。

## 解法

题中说对于 $i - j = a_i - a_j$，我们从 $i$ 到 $j$ 连一条边权为 $a_i + a_j$ 的双向边。

对于这个式子，我们可以变形为 $a_i - i = a_j - j$，而且不难发现如果有一些数它们的 $a_i - i$ 都相同，则这些数互相之间都有连边。整张图会分为若干连通块（或孤立点），每个连通块内都是一个完全图。现在问题转化为求完全图的最大权匹配。

我们考虑在输入 $a_i$ 时将 $a_i$ 转化为 $a_i - i$ 存储，记为 $val_i$，这样 $a_i$ 可表示为 $val_i + i$。然后将所有点将 $val$ 作为第一关键字，将 $i$ 作为第二关键字降序排序。这样一段连续的 $val$ 相同的区间即为一个连通块。如果一个连通块内有奇数个点，我们就舍去 $a_i$ 最小的点，剩下的点两两匹配，如果有偶数个点，我们就两两匹配。注意，如果两两匹配时 $a_i + a_j < 0$，我们就舍弃这两个点。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	快读快写，可忽略。
	*/
};
using namespace fast_IO;
#define int long long
int t,n;
int ans;
struct node
{
	int pos,val;
};
node a[100010];
inline bool cmp(const node &x,const node &y)
{
	if(x.val==y.val) return x.pos>y.pos;
	return x.val>y.val;
}
signed main()
{
	read(t);
	while(t--)
	{
		read(n),ans=0;
		for(int i=1;i<=n;i++) read(a[i].val),a[i].val-=i,a[i].pos=i;
		sort(a+1,a+n+1,cmp);
		for(int i=2,cnt=1;i<=n;i++)
		{
			if(a[i].val!=a[i-1].val)
			{
				cnt=1;
				continue;
			}
			if(cnt&1) ans+=max(a[i].val+a[i-1].val+a[i].pos+a[i-1].pos,0ll);
			cnt++;
		}
		write(ans),Putchar('\n');
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

#### 题目分析
我们首先先移项得 $i - a_i = j - a_j$，然后我们开一个 map 方便后面的操作，这里说一句，多测 map 要清空（我就是不清空挂了一发），我们只要把 $a_i$ 存进 $i - a_i$ 出就行了。

然后我们简单画个图就会发现：
![](https://cdn.luogu.com.cn/upload/image_hosting/7ryz7ng6.png)

所有连通块都能保证互不影响，然后我们接下来就很好办了，一个一个的去，模拟即可。

我们像排个序，然后用一个 $sum$ 记录下连续的两个的和，如果他们小于 $0$，那显然是不合法的，否则我们取最大的就行了。

代码十分简洁，就不给出了。

---

## 作者：寄风 (赞：1)

首先对式子移项，得到 $a_i-i=a_j-j$。

然后可以发现 $a_i-i$ 相同的点形成了一个连通块，不同的连通块互不影响，所以考虑逐块去取最大，最后相加即可。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair <int , int>
priority_queue <int> q;
signed main(){
    int t;
    cin >> t;
    auto read = [&](int &x){cin>>x;};
    while(t--){
        int n;
        cin >> n;
        vector <int> a(n);
        vector <PII> w(n);
        for_each(a.begin() , a.end() , read);
        for(int i = 0;i < n;i++){
            w[i] = make_pair(a[i] - i , i);
        }
        sort(w.begin() , w.end());
        int ans = 0;
        while(q.size()) q.pop();
        for(int i = 0;i < n;i++){
            if(w[i - 1].first == w[i].first || (!i)){
                q.push(a[w[i].second]);
            }
            else{
                while(q.size() >= 2){
                    int f = q.top();
                    int sum = f;
                    q.pop();
                    f = q.top();
                    q.pop();
                    sum += f;
                    if(sum > 0){
                        ans += sum;
                    }
                }
                while(q.size()) q.pop();
                q.push(a[w[i].second]);
            }
        }
        while(q.size() >= 2){
            int f = q.top();
            int sum = f;
            q.pop();
            f = q.top();
            q.pop();
            sum += f;
            if(sum > 0){
                ans += sum;
            }
        }
        cout << ans << endl;
    }
}
```


---

## 作者：hjqhs (赞：1)

移项知当 $i-a_i=j-a_j$ 时才会连边。因此对于所有 $u-a_u$ 值相同的点形成一个完全图。而原图则变成一个含有多个完全图的图。而不同完全图之间没有连边，所以不同完全图的答案可以分别统计。  
每条边的边权之和为这条边两点的点权之和，所以我们需寻找点权最大的两点。排序后计算点权最大两点点权之和，如果 $\le 0$，那么直接跳过。（因为排序过了，所以这个值肯定是这个完全图的最优值。但是不选边的值都是 $0$，所以舍弃这个值是可以的）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n,ans;
unordered_map<int,vector<int> >mp;
void solve(){
	mp.clear();
	n=ans=0;
	cin>>n;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		mp[i-x].emplace_back(x);
	}
	for(auto&p:mp){
		vector<int>vec=p.second;
		reverse(vec.begin(),vec.end());
		for(int i=0;i+2<=vec.size();i+=2){
			int sm=vec[i]+vec[i+1];
			if(sm<=0)break;
			ans+=sm;
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：ScapegoatTree (赞：1)

### 题目思路

对于式子 $i-j=a_i-a_j$，可以变式为 $i-a_i=j-a_j$。

那么对于所有顶点 $u$，只有 $u-a_u$ 相同的才会两两连边。这样整张图就形成了多个联通块。

对于每个联通块，就直接每次找最大值和次大值，把它们包含在答案里即可。
需要注意的是，如果两个点点权之和是负数，就不要选。

### 代码实现
首先将 $a$ 数组按照单调不增的顺序排好序，然后使用 map 来纪录最大值，如果找到次小值，如果和大于 $0$，就把和增加到答案里，在把 map 的那一位清零。

代码：
```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
const int MAXN=1e6+5;
struct node{
    int pos;
    int num;
};
node a[MAXN];
int cmp(node a,node b){
    return a.num>b.num;
}
std::map<int,int> mp1;
int b[MAXN];
void solve(){
    int n;
    std::cin>>n;
    mp1.clear();
    for(int i=1;i<=n;i++){
        std::cin>>a[i].num;
        a[i].pos=i;
    }    
    int ans=0;
    std::sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(mp1[a[i].pos-a[i].num]==0){
            mp1[a[i].pos-a[i].num]=a[i].num;
        }
        else if(mp1[a[i].pos-a[i].num]>0){
            if(mp1[a[i].pos-a[i].num]+a[i].num>=1)ans+=mp1[a[i].pos-a[i].num]+a[i].num;
            mp1[a[i].pos-a[i].num]=0;
        }
    }
    std::cout<<ans<<'\n';
}
int t;
signed main(){
    std::cin>>t;
    while(t--)solve();
    return 0;
}
```


---

## 作者：SXqwq (赞：1)

## Analysis

不妨先忽略图论，考虑在一条链上选多组点使得每一组点 $i,j$ 均满足 $i-j=a_i-a_j$。由于没有规定我们选多少组，因此 $a_i+a_j > 0$ 均对答案产生正贡献，都可以选。

问题是如果一个数可以与多个数匹配，我们该选哪个呢？显然我们贪心地选择贡献最大的。

朴素的做法是将数组从小到大排序，然后倒着搜数组。对于搜到的每个数找它前面有没有可以与其配对的数，如果有多个则取贡献最大的。但是这样复杂度太大，无法接受。

如何优化呢？

不妨换个思路，要求 $i-j=a_i-a_j$，移向得 $a_i-i=a_j-j$。因此 $a_i-i$ 相同的数都可以任意配对。显然我们优先满足较大的两个数配对，然后再考虑小的。我们只需要对于每一组 $a_i-i$ 都对其 $a_i$ 从大到小排序贪心选择即可。

具体实现的时候可以使用 map，排序可以使用 vector。考察 STL 熟练度。

代码如下。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define int long long
using namespace std;
const int N = 500005;
const int INF = 0x3f3f3f3f;
map<int,vector<int> >Edge;
int n;
int a[N];
int T;
bool cmp(int a,int b){return a > b;}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--)
    {
        int ans =  0;
        Edge.clear();
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],Edge[a[i]-i].push_back(a[i]);
        for(auto it:Edge)
        {
            vector <int> v = it.second;
            sort(v.begin(),v.end(),cmp);
            int a = INF,b = INF;
            for(auto i:v)
            {
                if(a == INF) a =i;
                else
                {
                    b = i;
                    if(a+b > 0) 
                    {
                        ans += a+b;
                        a = b = INF;
                    }
                }
            }
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

易发现，如果 $i$ 和 $j$ 可以连边，$j$ 和 $k$ 可以连边，那 $i$ 和 $k$ 也可以连边，如果 $x$ 不能和 $i$ 连边，那 $x$ 同样不能和 $j,k$ 连边。所以我们可以考虑把所有可以连边的放在一起，这样就把所有点分成了若干部分，并且每个部分不可能连边，必然是分割开的。

同时，条件 $i-j=a_i-a_j$ 可以转化为 $a_i-i=a_j-j$，所以我们只需要把所有 $a_i-i$ 一样的放在一起就好了。

然后对于每一部分，我们每次取值最大的两个点，如果和大于 $0$ 就代表有贡献，计入答案，否则就可以推出这个部分了，因为剩下的必定小于 $0$，无法对答案做出贡献。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a;
unordered_map<int,vector<int>>m;//用来存每个部分
long long ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		m.clear(),ans=0;//多组数据记得清零
		for(int i=1;i<=n;++i) scanf("%d",&a),m[i-a].push_back(a);//记录每个部分
		for(auto i:m)//遍历
		{
			vector<int>v=i.second;
			sort(v.begin(),v.end());//排序
			for(int i=v.size()-1;i>=1;i-=2)//注意：这里是i>=1，而非i>=0。因为如果i=0，就代表只剩一个，不能计入答案
			{
				if(v[i]+v[i-1]>0) ans+=v[i]+v[i-1];
				else break;
			}
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：__zfy__ (赞：0)

### 思路
开始通过移项得到式子：

$a_i - i = a_j - j$，对于每个 $u$，只有 $u - a_u$ 才能使每对两两连边。接着就可以直观的看出，整张图构成了由多个连通块组成的图。

然后把每个连通块排序，找到最大和次大的值，需要注意的是判断是否是负数或 $0$，如果是，说明为不合法的，如果不是，直接找最大即可。

证明：多关键字排序后，找到的这两个值一定是图中的最优，因为不选边的值是 $0$，所以把这个值扔掉是可行的。

**注意事项：**

如果发现权重之和 $\le 0$，直接停止，要直接输出累加的权值之和，**需要清零对应的 `map` 的那一位**。

### 代码
代码就不附了，思虑清楚滴很。

---

## 作者：Nancy_Cherry (赞：0)

【题目思路】

给定一个序列 $a_1, a_2, \cdots, a_n$，我们需要构造一个无向图 $G$，并找到一个匹配，使得匹配中所有边的权重之和最大。

我们可以使用一个哈希表 `mp` 来记录每个差值 $i-j$ 对应的节点 $j$ 的集合。具体来说，对于每个节点 $j$，我们将其加入到 $mp_{i-j}$ 中。

然后，我们遍历 `mp` 中的每个键值对，对应于差值 $i-j$ 和节点集合 $j$。我们可以将节点集合 $j$ 按照权重从大到小排序，并逐对取出相邻的两个节点，计算它们的权重之和。如果权重之和小于等于 $0$，则停止计算，否则将权重之和累加到答案中。
最后，输出答案即可。

【代码实现】
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
long long ans;

unordered_map<int, vector<int>> mp;

void solve() {
    scanf("%d", &n);
    mp.clear();
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d", &x);
        mp[i - x].push_back(x);
    }

    ans = 0;
    for (auto &p : mp) {
        vector<int> &vec = p.second;
        reverse(vec.begin(), vec.end());
        for (int i = 0; i + 1 < vec.size(); i += 2) {
            int sm = vec[i] + vec[i + 1];
            if (sm <= 0) break;
            ans += sm;
        }
    }
    printf("%lld\n", ans);
}

int main() {
    int c; 
    scanf("%d", &c);
    while (c--) solve();
    return 0;
}

```

---

## 作者：SakurajiamaMai (赞：0)

## 思路:

将等式两边交换，发现有 $a - i = b - j$。于是利用容器动态存储数据，然后对每一个匹配项进行排序求和，求和的时候注意，若两点相加总和小于 $0$ 需要舍弃。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
string s;
int n,t,a[N],f[N],res,num,ans,m,k;
bool vis[N];
map<int,vector<int>>mp;
void solve()
{
    cin>>n;
    mp.clear(),res=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp[a[i]-i].push_back(a[i]);
    }
    for(auto i:mp){
        sort(i.second.begin(),i.second.end(),greater());
        for(int j=0;j+1<i.second.size();j+=2) res+=max((int)0,i.second[j]+i.second[j+1]);
    }
    cout<<res<<endl;
}
signed main()
{
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```


---

## 作者：Halberd_Cease (赞：0)

前：这道题的思路和 [CF1857D](https://www.luogu.com.cn/problem/CF1857D) 有相似之处，可以拿来一起练手。

题目给出的是一个数列，要求用这个数列生成一个图，当满足 $i-j=a_i-a_j$ 时，存在一条权值为 $a_i+a_j$ 的边。

对于上面式子，朴素来讲要在 $O(n^2)$ 的时间才能找出所有的边（枚举每一个 $i$ 和 $j$），不可行，因此考虑对式子变形，得到如下的式子：

$$i-a_i=j-a_j$$

对于每一个 $i$ 上面式子都是确定的，因此我们只需要花费 $O(n)$ 的时间可以算出每一个 $i-a_i$，值相同的就可以互相连边。

然后我们来看边权，一条边的边权取决于两个端点（$a_i+a_j$），所有连边的边权和取决于选择的点而不是要连哪一条边，因此我们只需要贪心去找点，具体来说，在每一个可以互相连边的集合中（即 $i-a_i$ 的值两两相等），每次选择最大的两个点连边，如果贡献为负就不连边，最后就得到最终的答案。

然后就没有了。

code：

```cpp
void work()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].a;
        a[i].b = a[i].a - i;
    }
    // for (int i = 1; i <= n; i++)
    // cout << a[i].b << ' ';
    sort(a + 1, a + n + 1);
    int now = 0, nowcl = -1145141919810;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (now != 0)
        {
            if (nowcl == a[i].b)
            {
                ans += max(now + a[i].a, 0ll);
                now = 0;
            }
            else
            {
                now = a[i].a;
                nowcl = a[i].b;
            }
        }
        else
        {
            now = a[i].a;
            nowcl = a[i].b;
        }
    }
    cout << ans << endl;
}
```

---

## 作者：unknown_risk (赞：0)

题目简化：在一个序列 $a$ 中，若满足 $i-j=a_{i}-a_{j}$，则可以产生 $a_{i}+a_{j}$ 的贡献，且对于每个 $a_{i}$ 和 $a_{j}$ 仅可贡献一次，当然若不进行贡献操作贡献值则为 $0$，求最大贡献值。

分析：根据 $i-j=a_{i}-a_{j}$，移项可得   $i-a_{i}=j-a_{j}$。所以我们可以先计算当前下标与当前贡献的差值，再通过差值从小到大排序，差值相同的情况下再通过贡献值从小到大排序，再通过循环模拟求得最大值。

注意：当贡献值之和为负数时跳过，不进行操作。

### My code
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int T,n;
struct node
{
	int tot,cha;
}a[N];
bool cmp(node s1,node s2)
{
	if(s1.cha!=s2.cha)return s1.cha<s2.cha;
	else return s1.tot>s2.tot;
}
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].tot;
			a[i].cha=a[i].tot-i;
		}
		int sum=0;
		sort(a+1,a+1+n,cmp);
		for(int i=2;i<=n;)
		{
			if(a[i].cha==a[i-1].cha&&a[i].tot+a[i-1].tot>0)
			{
				//cout<<a[i].tot<<" "<<a[i-1].tot<<endl;
				sum=max(sum,sum+a[i].tot+a[i-1].tot);
				i+=2;
			}
			else i++;
		}
		printf("%lld\n",sum);
	}
	return 0;
} 
```



---

## 作者：Determination_Y (赞：0)

### 题目描述

给定长度为 $n$ 的整数序列 $a_1, a_2, \cdots, a_n$，我们将从该序列中构造出一张无向图 $G$。具体来说，对于所有 $1 \le i < j \le n$，若 $i - j = a_i - a_j$，则 $G$ 中将存在一条连接节点 $i$ 与 $j$ 的无向边，其边权为 $(a_i + a_j)$。

求 $G$ 的一个匹配，使得该匹配中所有边的边权之和最大，并输出最大边权之和。

请回忆：无向图的匹配，指的是从该无向图中选出一些边，使得任意两条边都没有公共的节点。特别地，不选任何边也是一个匹配。

### 思路

首先我们看到题目中的一句话：

> 若 $i - j = a_i - a_j$，则 $G$ 中将存在一条连接节点 $i$ 与 $j$ 的无向边

我们把这个式子两边同时加上 $j$，减去 $a_i$，可以得到如下的式子：

$$ i - a_i = j - a_j $$

因此我们可以把原数组转换一下，第 $i$ 项 $a_i$ 变成 $i - a_i$，所有处理后值相同的点之间都会有一条边，形成一个完全图，我们可以把这些点全部塞进一个 `map` 中。

```cpp
map<int,vector<int> >Edge;

for(int i=1;i<=n;i++){
    scanf("%lld",&a[i]);
    Edge[a[i]-i].push_back(a[i]);
}
```

然后开始分别处理每一个完全子图。由于要我们求无向图的匹配，一个点不会被选超过两次，所以我们可以把所有点按照点权从大到小排序，每一次选择一对点，判断这两个点的和是否为正数，如果是，那么就一定选，否则直接 `break` 即可。

```cpp
for(auto it:Edge){
    vector<int>E=it.second;
    sort(begin(E),end(E),[](int a,int b){return a>b;});
    int a=0x3f3f3f3f,b=0x3f3f3f3f;
    for(auto it:E){
        if(a==0x3f3f3f3f){
            a=it;
        }else{
            b=it;
            if(a+b>0) ans+=a+b,a=b=0x3f3f3f3f;
            else      break;
        }
    }
}
```

### 完整 Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

map<int,vector<int> >Edge;
int T,n,a[500005],ans;

signed main()
{
    scanf("%lld",&T);
    while(T--){
        Edge.clear();ans=0;
        scanf("%lld",&n);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            Edge[a[i]-i].push_back(a[i]);
        }
        for(auto it:Edge){
            vector<int>E=it.second;
            sort(begin(E),end(E),[](int a,int b){return a>b;});
            int a=0x3f3f3f3f,b=0x3f3f3f3f;
            for(auto it:E){
                if(a==0x3f3f3f3f){
                    a=it;
                }else{
                    b=it;
                    if(a+b>0) ans+=a+b,a=b=0x3f3f3f3f;
                    else      break;
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

