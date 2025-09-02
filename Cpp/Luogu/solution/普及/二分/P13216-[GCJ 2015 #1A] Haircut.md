# [GCJ 2015 #1A] Haircut

## 题目描述

你正在一家时尚理发店排长队等着理发。店里有 $B$ 位理发师，编号为 $1$ 到 $B$。第 $k$ 位理发师理一个顾客的头发恰好需要 $M_k$ 分钟，并且每位理发师一次只能为一位顾客服务。当理发师完成理发后，会立即空闲，可以为下一位顾客服务。

在理发店营业期间，队首的顾客总是会选择编号最小的空闲理发师。如果没有理发师空闲，该顾客会等待，直到至少有一位理发师空闲。

你是队伍中的第 $N$ 位顾客，理发店刚刚开门。请问哪位理发师会为你理发？

## 说明/提示

**样例解释**

在第 1 组样例中，你是队伍中的第 4 位顾客，理发师 $1$ 和 $2$ 理发分别需要 $10$ 分钟和 $5$ 分钟。当理发店开门时，第一位顾客可以选择理发师 $1$ 或 $2$，她会选择编号最小的理发师 $1$。第二位顾客会立即由理发师 $2$ 服务。第三位顾客需要等待，因为没有空闲理发师。5 分钟后，理发师 $2$ 完成第二位顾客的理发，并为第三位顾客服务。10 分钟后，理发师 $1$ 和 $2$ 都完成了理发，你是下一个顾客，可以选择理发师 $1$ 或 $2$，你会选择 $1$。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq N \leq 10^9$。

**小数据集（11 分）**

- 时间限制：5 秒。
- $1 \leq B \leq 5$。
- $1 \leq M_k \leq 25$。

**大数据集**

- 时间限制：10 秒。
- $1 \leq B \leq 1000$。
- $1 \leq M_k \leq 100000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 4
10 5
3 12
7 7 7
3 8
4 2 1```

### 输出

```
Case #1: 1
Case #2: 3
Case #3: 1```

# 题解

## 作者：chenzefan (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P13216)
## 前言
嗯？时限 $5.00s \sim 10.00s$？
## 思路
显然，这题不需要这么多的时限。我们来说 $1s$ 内的做法。

**二分**思路不难想吧，$N \le 10^9$，显然不带根号，那肯定带 $\log$，不用猜了，二分。

直接上二分答案模板。二分第 $N$ 位顾客开始理发的时间。

模板如下。
```cpp
while(l<=r){
    int mid=l+r>>1;
    if(check(mid)) ans=mid,r=mid-1;
    else l=mid+1;
}
```
考虑 check 函数的写法。

假设第 $N$ 位顾客开始理发的时间为 $mid$，看看能否在前 $mid$ 的时间内理发理到第 $N$ 位顾客。

check 函数如下。
```cpp
bool check(int mid){
	int cnt=0;
	for(int i=1;i<=b;i++){
		cnt+=mid/m[i];
		if(mid%m[i]) cnt++;
	}return cnt>=n;
}
```
二分完后，假设这个时间前理发顾客数为 $cnt$，答案即为第 $N-cnt$ 位空闲无事的理发师。
## 代码
未卡常版：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
int b,n,m[N],a[N];
bool check(int mid){
	int cnt=0;
	for(int i=1;i<=b;i++){
		cnt+=mid/m[i];
		if(mid%m[i]) cnt++;
	}return cnt>=n;
}
signed main(){
	int t;scanf("%lld",&t);
	for(int q=1;q<=t;q++){
		scanf("%lld%lld",&b,&n);
		for(int i=1;i<=b;i++) scanf("%lld",m+i);
		int l=0,r=1e12,ans;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		int cnt1=0,cnt2=0;
		for(int i=1;i<=b;i++){
			cnt2+=(ans-1)/m[i];
			if((ans-1)%m[i]) cnt2++;
			else a[++cnt1]=i;
		}
		printf("Case #%lld: %lld\n",q,a[n-cnt2]);
	}return 0;
}
```
也是轻松 $41$ms。

卡个常，卡过 $35$ms，轻松拿下目前最优解。

~~顺便夸赞一下这题的满分分数。（$33$ 分？）~~

[记录。](https://www.luogu.com.cn/record/225268746)

啊哈？只有 $2$ 个测试点？

---

## 作者：4041nofoundGeoge (赞：2)

~~时限留到孙子都用不完。~~

## 思路

先不说 10s 的时限能不能过一些奇怪的代码。

正常情况下这题时限应该为 1s。

下面是 1s 的做法：

一道非常~~不~~经典的二分问题，抽象一下题目内容：
> 最少的时间内服务 $N$ 名顾客。

这个时间可以是刚开始 $0$ 秒，也可以是 $N\times \max M_i$（想象一下，客人爆火），这就可以二分了，每一次寻找中间的值，求出这个时间能服务多少名客人，还没到我（即 $N$），说明时间不够，左边界赋值之。反之，如果能服务 $N$ 个人甚至还有多余，右边界赋值之，并标记答案。

这还没完，我们只是知道最少时间，但不知道我们的理发师是谁，于是还要求现在哪一位理发师刚好结束理发，放进一个数组里，最后还要计算你是哪批次顾客，毕竟先来的人要先选。

至于如何求解第 $x$ 秒理发师们一共解决多少顾客。用一个求和即可：

$$
\sum^B_{i=1}x\div m_i +1
$$

意思就是每个理发师每一个人用时 $m_i$，$x$ 秒当然是 $x\div m_i$ 个客人，理发师第 $0$ 秒就可以接客人，最后还要加一。

**请不要不听的提示：务必一定不要不开 long long。**
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int m[1005];
int b,n;
int cul(int time){
    if(time<0)return 0;
    int sum=0;
    for(int i=1;i<=b;i++){
        sum+=time/m[i]+1;
    }
    return sum;
}
signed main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        cin>>b>>n;
        cout<<"Case #"<<q-t<<": ";
        int l=0,r=-1;
        for(int i=1;i<=b;i++){
            cin>>m[i];
            r=max(m[i],r);
        }
        r*=n;
        int ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            int now=cul(mid);
            if(now<n)l=mid+1;
            else {
                ans=mid;
                r=mid-1;
            }
        }
        int last=n-cul(ans-1);
        vector<int>anss;
        for(int i=1;i<=b;i++){
            if(!(ans%m[i]))anss.push_back(i);
        }
        sort(anss.begin(),anss.end());
        cout<<anss[last-1]<<endl;
    }
    return 0;
}
```

---

## 作者：zzr1105 (赞：2)

## 前言
这是蒟蒻的第一篇题解，如有错误，欢迎各位大佬指出
## 思路
看到这题，肯定有很多人想暴力模拟，但 $N \le 10^9$,一定会超时。

看到这么大的数据范围，第一反应就是二分。我们可以二分出第 $N$ 位顾客开始理发的时间，再求出这个时刻之前理发的顾客数 $S$，那么答案便是第 $N-S$ 位空闲的理发师。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b,n,t;
int m[1005],a[1005];
bool check(int time){//判断能否在时间t中理到顾客N
	int shu=0;
	for(int i=1;i<=b;i++){
		shu+=time/m[i];
		if(time%m[i]) shu++;
	}
	return shu>=n;
}
void solve(){
	cin>>b>>n;
	for(int i=1;i<=b;i++) cin>>m[i];
	int l=0,r=100000000000000,ans;//二分
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	int cnt=0,shu=0;
	for(int i=1;i<=b;i++){ //统计顾客数
		shu+=(ans-1)/m[i];
		if((ans-1)%m[i]) shu++;
		else a[++cnt]=i; //统计空闲的理发师
	}
	cout<<"Case #"<<t<<": "<<a[n-shu]<<endl; //输出
}
signed main(){
	int _;
	cin>>_;
	for(t=1;t<=_;t++){
		solve();
	}
}
```

---

## 作者：Luojt95 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13216)。

### 思路
带着神秘时间限制的好奇心来到了此题。

一眼看认为是道贪心，后来怎么想怎么不对劲，知道看到 $N \le 10^9$ 才恍然大悟： $O(TN)$ 以上过不去呀，只能使用 $O(TB\log N)$ 的算法：二分！

二分找什么呢？找出理 $N$ 个人发的最短时间，设其为 $ans$ 分钟。而为你理发的理发师编号是多少关键就在于第 $ans-1$ 分钟理完了多少顾客，设其为 $cnt$ 名，然后，第 $cnt+1 \sim N$ 名顾客对号入座，而你是最后选择的那个人，第 $cnt+1 \sim N$ 名顾客中一共有 $N-cnt$ 名顾客，你就自然对应了第 $N-cnt$ 名理发师。
### 代码实现
check 函数如下：（ $check(x)$ 表示理 $x$ 个人发的最短时间）
```cpp
int check(int x)
{
    int res=0;
    for(int i=1;i<=n;i++) res+=x/a[i]+1;//+1 表示理发时间从 0 开始
    return res;
}
```
二分代码如下：
```cpp
int l=0,r=1e18,ans=-1;// 其实 r 不需要开那么大，纯属个人习惯
while(l<=r)
{
    int mid=l+r>>1;
    if(check(mid)>=k)
    {
        r=mid-1;
        ans=mid;
    }
    else
    {
        l=mid+1;
    }
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long // 一定要开 long long ！
using namespace std;
int t,n,k;
int a[1010];
vector<int> e;
int check(int x)
{
    int res=0;
    for(int i=1;i<=n;i++) res+=x/a[i]+1;
    return res;
}
signed main()
{
    cin>>t;
    for(int Case=1;Case<=t;Case++)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        int l=0,r=1e18,ans=-1;
        while(l<=r)
        {
            int mid=l+r>>1;
            if(check(mid)>=k)
            {
                r=mid-1;
                ans=mid;
            }
            else
            {
                l=mid+1;
            }
        }
        int pos=k-check(ans-1)-1; //记得 -1 ，时间从 0 开始
        e.clear();
        for(int i=1;i<=n;i++)
            if(!(ans%a[i])) //表示恰巧在 ans-1 时刻理完顾客发的理发师可以给你理发
                e.push_back(i);
        cout<<"Case #"<<Case<<": "<<e[pos]<<'\n';
    }
    return 0;
}
```

---

## 作者：koukou (赞：1)

~~时间限制大的离谱。~~

显然是满足单调性的，如果你在 $x$ 分钟内能剪完 $y$ 个人，那么 $x$ 分钟之后也一定至少能剪 $y$ 个人，于是我们可以二分出剪完 $n$ 个人的最小时间。具体的，该怎么计算 $x$ 分钟内能剪多少人呢？不用一个个模拟，直接粗略除以 $M_i$ 再加 $1$ 即可， 因为一有空闲就会立刻又顾客上去理发，所以这样计算是可行的。

但是还有一个问题，二分出来的答案只是最短的时间，该怎么求是第几个理发师呢？\
很简单，首先求出 $x - 1$ 时还差多少个人，然后一个一个填进当前空闲的理发师即可。

代码：
```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e3 + 1;
int T, b, n, l, r, a[N];
int work(int x)
{
	int sum = 0;
	for(int i = 1; i <= b; i++) sum += x / a[i] + 1;//计算能剪完多少个人
	return sum;
}
signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> T;
	for(int id = 1; id <= T; id++)
	{
		cin >> b >> n;
		l = r = 0;
		for(int i = 1; i <= b; i++)
		{
			cin >> a[i];
			r = max(a[i], r);
		}
		r *= n;
		while(l <= r)
		{
			int mid = (l + r) / 2;
			if(work(mid) < n) l = mid + 1;//如果剪不到你
			else r = mid - 1;//剪得到你
        }
		int cnt = n - work(r), i;//计算还差多少人
		for(i = 1; i <= n; i++)
		{
			if(l % a[i] == 0)//如果这个理发师空闲
			{
				cnt--;//填进去
				if(cnt == 0) break;
			}
		}
		cout << "Case #" << id << ": " << i << "\n";
	}
    return 0;
}
```

---

## 作者：I_AM_TLEer (赞：1)

# P13216 [GCJ 2015 #1A] Haircut

## 题意概括：

理发店里有 $B$ 位理发师。顾客排起了长队，你是队伍中的第 $N$ 位。之后给定序列 $M$，第 $k$ 个理发师服务一位需要 $M_k$ 分钟。

若每位理发师一次只能为一位顾客服务。当理发师完成理发后，会立即空闲。如有空闲，顾客会选择编号最小的那位，否则该顾客会等待。

求为你理发的理发师编号。

## 思考过程：

通过查看算法标签可知是一道二分题。或理解题面，注意到随着时间的增加，人数只增不减，这就很二分。

计算二分的上下界。假设从一个理发师出发，人数不断加入，答案只会越来越小。理想状态下，答案最大值为 $M_{min}\times n$，比较容易地，最小值为 $0$。二分得出轮到你选的时间点。

至于如何求解第 $mid$ 秒理发师们一共解决多少顾客，用一个求和即可：

$$f= \sum^{b}_{i=0} (mid \div M_{i} +1)$$

意思就是每个理发师每一个人用时 $M_{i}$，第 $mid$ 秒自然是 $mid\div M_{i}$ 个客人，由于理发师第 $0$ 秒就可以接客人，最后还要加一。

这还没完，我们只是知道最少时间，但不知道我们的理发师是谁，于是还要求现在哪一位理发师刚好结束理发，放进一个数组里，最后还要计算你是哪批次顾客，毕竟先来的人要先选。

最后，由于 $1\le N\le10^{9}$，$1\le M_{k}\le 10^{5}$，有极大概率超出 int 范围，应使用 `#define int long long`。

根据以上思路，可以得到以下复杂度为 $O(n \log{n})$ 的代码。

## AC code:

[提交记录](https://www.luogu.com.cn/record/224897371)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int T, b, n;
int m[1005];

signed main () {
	scanf("%lld", &T);
	for (int t = 1; t <= T; t ++) {
		int minn = 1e9 +5;
		scanf("%lld %lld", &b, &n);
		for (int i1 = 0; i1 < b; i1 ++) {
			scanf("%lld", &m[i1]);
			minn = min(minn, m[i1]);
		}
		int l = 0, r = minn *n +5;
		while (l <= r) {
			int mid = (l +r) /2, f = 0;
			for (int i1 = 0; i1 < b; i1 ++)
				f += mid /m[i1] +1;
			if (f >= n) r = mid -1;
			else l = mid +1;
		}
		//cout << l << endl;
		int xp = n;
		for (int i1 = 0; i1 < b; i1 ++)
			xp -= r /m[i1] +1;
		vector<int> ans;
        for(int i1 = 0; i1 < b; i1 ++)
            if (!(l %m[i1])) ans.push_back(i1);
        sort(ans.begin(), ans.end());
		printf("Case #%lld: %lld\n", t, ans[xp -1] +1);
	}
    return 0;
}
```

## 后记：

$39ms$ 成功拿下最优解。

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
我们需要找到一个时间点 $t$，使得在时间 $t$ 之前能够服务的顾客总数刚好大于等于 $N$,然后在这个时间点找出哪个理发师会为你服务。

### 方法
我们可以观察到顾客的数量随着时间单调递增。随着时间 $t$ 的增加，能够被服务的顾客数量只会增加或保持不变，不会减少。

由上，这一特点满足了二分的单调性，可以通过二分来寻找最小的 $t$。

每次找到一个时间 $t$，计算在 $t - 1$ 已经服务的顾客数，同时计算剩余需要服务的顾客数 $p$，找出在 $t$ 时刻刚好完成服务的理发师，即 $t \bmod M_i = 0$ 的理发师。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005;
int t,n,b,a[N],k;
int calc(int x){//关键代码，计算顾客数量 
	int cnt=0;
	for(int i=1;i<=b;i++) cnt+=x/a[i]+1;
	return cnt;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
	for(int o=1;o<=t;o++){
    	cin>>b>>n;
    	for(int i=1;i<=b;i++) cin>>a[i];
    	if(n<=b){
        	cout<<"Case #"<<o<<": "<<n<<'\n';
    		continue;
		}
		int l=1,r=*max_element(1+a,1+a+b)*n;//r=最慢理发师服务时间*b
		while(l<=r){//二分
			int mid=l+r>>1;
			if(calc(mid)<n) l=mid+1;
			else r=mid-1;
		}
		int p=n-calc(l-1);
		for(int i=1;i<=n;i++)
			if(l%a[i]==0&&--p==0){
        		cout<<"Case #"<<o<<": "<<i<<'\n';
				break;
			}
    }
}
```

---

