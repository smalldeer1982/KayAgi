# 「yyOI R1」youyou 的篡改（Easy Ver.）

## 题目背景

**Easy Version 与 Hard Version 仅最后所求内容不同，其他描述均一致。**

## 题目描述

youyou 准备举办一场比赛，这场比赛有 $n$ 道题，每一道题都有一个难度值 $v_i$。

youyou 给出一个计数分量 $k(k\le n)$，他认为，第 $x(x \geq k)$ 道题的可做性 $a_x$ 应当是第 $1\sim x$ 题所有题目中将难度值从小到大排序后难度较大的 $k$ 道题目难度值之和。

由于第 $1 \sim k-1$ 题难度过于简单，youyou 不想考虑这些题目的可做性。

那么这场比赛的总可做性即为第 $k$ 道题至第 $n$ 道题可做性之和，即 $\sum^{n}_{i=k}a_i$
 的值。

youyou 可以篡改题目 $m$ 的难度为任意正整数，但是他并不希望这场比赛过难或者过简单，所以他要求总可做性必须介于 $[l,r]$ 之间。

youyou 想知道，他通过篡改题目 $m$ 的难度，可以将总可做性最大篡改为多少？

特别的，如不存在一组解请输出 $-1$。

## 说明/提示

### 样例解释#1

因为 $m=1$，因此 $a_1$ 是可以被篡改的，当 $a_1=2$ 时，总可做性为 $2+2+2+2+2=10$，因为 $10 \in [5,10]$，因此可以将总可做性最大篡改为 $10$。

## 数据范围

本题启用 **Subtask**，对于每一个 **Subtask**，你需要通过全部测试点才能得到该部分的分数。

| 子任务编号 | $n$ | 分数 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $\le10$ | $15$ |
| $2$ | $\le10^3$ | $15$ |
| $3$ | $\le10^5$ | $70$ |


对于 $100\%$ 的数据，$1\le k,t \le n \le 10^5$，$1 \le l \le r \le 10^{9}$，$0\le v_i\le10^9$。

## 样例 #1

### 输入

```
5 1 1 5 10
1 2 2 2 2```

### 输出

```
10```

# 题解

## 作者：metrixgo (赞：5)

## 题意

题意是给定五个正整数 $n,m,k,l,r$，然后输入长度为 $n$ 的数组，对于任意的 $i\geq k$，该题目的可做性为 $1\sim i$ 题难度值从大到小排序后难度最大的 $k$ 道题目难度之和。然后你可以篡改第 $m$ 道题的难度，尝试使所有题目的可做性之和控制在 $l\sim r$ 之间。试求满足该条件下，最大的所有题目的可做性之和。若无法满足，输出 $-1$。

## 思路

看上去像是二分，只需二分第 $m$ 道题的难度，然后计算出这种情况下所有题目的可做性之和是否满足条件即可。但是问题在于计算每一道题的可做性。如果按照题意来，枚举出所有题目，则需 $O(n^2)$ 的时间复杂度，乘上二分的 $O(\log n)$，肯定爆。

其实我们可以借用第 $i$ 道题目的可做性来推导第 $i+1$ 道题目的可做性。如果第 $i+1$ 道题目的难度比之前的所有题目难度都低，那只能是前一道题目的可做性，因为最难的 $k$ 道题不变。如果不是，那么只需要踢掉前面题目中最简单的那个，然后把这题的难度加上，就是最难的 $k$ 道题。对于记录前面最简单的题，可以用[优先队列](https://oi-wiki.org/lang/csl/container-adapter/#优先队列)维护，对于可做性和难度，可以用数组维护。时间复杂度大约为 $O(n\log n\log V)$，足以通过本题。

**注意**：数据有些大，需要开 $64$ 位。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=100005;
ll i,j,n,m,k,r,l,cur,all,nandu[N],kezuoxing[N];
priority_queue<ll,vector<ll>,greater<ll> > q;

ll build(){
	ll i,cnt=0,all=0;
	for(i=1;i<=k;i++){
		cnt+=nandu[i];
		q.push(nandu[i]);
	}
	kezuoxing[k]=cnt;
	all+=cnt;
	for(i=k+1;i<=n;i++)
	{
		if(nandu[i]>q.top()){
			cnt-=q.top();
			q.pop();
			cnt+=nandu[i];
			q.push(nandu[i]);
		}
		kezuoxing[i]=cnt;
		all+=cnt;
	}
	return all;
}

ll binsch(){//二分查找 
	ll lastpos=-1;
	long long right=100000005,left=1,mid;
		while(left<=right)
		{
			mid=right-(right-left)/2;
			while(!q.empty()) q.pop();//清空优先队列
		    nandu[m]=mid;//篡改数据
		    ll tri=build();//生成可做性 
			if(l<=tri&&r>=tri){
				lastpos=max(lastpos,tri);
				left=mid+1;
			}
			else if(l>tri) left=mid+1;
			else right=mid-1;
		}
	return lastpos;
}
int main(){
    
    cin>>n>>m>>k>>l>>r;
    for(i=1;i<=n;i++) cin>>nandu[i];//输入数据 
    cout<<binsch();
    return 0;
}
```


---

## 作者：what_else (赞：4)

# Solution
## Easy Version
这题其实可能比 T1 略简单。

考虑怎么处理在已知所有难度值的情况下求出每道题的可做性。

一种想法是，在求第 $x$ 道题的可做性的时候，将前面几题难度值排个序并加和较大的 $k$ 个数。

不过这是暴力，最坏时间复杂度能达到 $O(n^2\log n)$。

但是我们可以考虑，如果我们已经求出了第 $x$ 题的可做性 $a_x$，那么我们求下一道题也就是第 $x+1$ 题的可做性 $a_{x+1}$ 该怎么处理呢？

不妨这样想，第 $x$ 道题的可做性 $a_x$ 是由第 $1 \sim x-1$ 题较大的 $k$ 个难度值加和得来的，那么第 $x+1$ 题的可做性只需要考虑第 $x+1$ 题的难度值就好了。

不妨比较第 $1 \sim x-1$ 题较大的 $k$ 个难度值中的最小值与第 $x$ 题的难度值，如果第 $x$ 题的难度值比第 $1 \sim x-1$ 题较大的 $k$ 个难度值中的最小值还大，那么就可以剔除第 $1 \sim x-1$ 题较大的 $k$ 个难度值中的最小值，加入第 $x$ 题的难度值了，很容易想到用优先队列维护，这样时间复杂度来到 $O(n \log n)$。

然后二分 $a_m$ 就可以了。

总时间复杂度为 $O(n \log n \log V)$。

这样可以通过本题简单的版本，可以获得 $50$ 分。


---

## 作者：HanazomeMana (赞：2)

素一个二分题。二分第 $m$ 题的难度即可。

容易想到枚举每题的可做性的和是否满足条件，但是显然 $O(n^2)$ 的 `chk` 会超时。

我们可以用第 $i$ 题的可做性推导第 $i+1$ 题的可做性。如果是前 $k$ 题，不需要处理，从 $k+1$ 开始才需要判断可做性。我们可以用一个优先队列维护最大的 $k$ 个数，然后累加可做性判断即可。

注意开 `long long`。

贴个代码 qwq。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
lint n,m,k,l,r,a[100010],ans;
lint chk(int x){
	priority_queue<lint,vector<lint>,greater<lint>>q;
	lint tmp=a[m],res=0,sum=0;a[m]=x;
	for(int i=1;i<=k;++i)res=sum+=a[i],q.push(a[i]);
	for(int i=k+1;i<=n;++i)q.push(a[i]),sum+=a[i]-q.top(),q.pop(),res+=sum;
	a[m]=tmp;
	return res;
}
int main(){
	cin>>n>>m>>k>>l>>r;
	for(int i=1;i<=n;++i)cin>>a[i];
	lint L=1,R=1e9;
	while(L<=R){
		lint mid=L+(R-L)/2,res=chk(mid);
		if(res>=l&&res<=r)ans=res,L=mid+1;
		else if(res<l)L=mid+1;
		else R=mid-1;
	}cout<<(!ans?-1:ans);
	return 0;
}
```

---

## 作者：Caged_Bird (赞：1)

# P9636 解题报告
## 题意简述
有 $n$ 道题，给出每道题的难度，定义一题的可做度为它前面的题和它中难度最大的 $k$ 道题的难度之和，现在可以对第 $m$ 题任意改变难度，使可做度总和在 $[l,r]$ 之间且尽量大，求这个尽量大的可做度总和。
## 思路
因为在其他题难度不变的情况下，第 $m$ 题难度越大，可做度总和也越大，具有单调性。所以考虑二分第 $m$ 题难度，对当前情况求出可做度并判断是否合法。  
求可做度时，可以对前 $k$ 大的难度进行动态维护。建一个小根堆，堆中一开始只有第 $1$ 题至第 $k$ 题的难度。遍历难度数组，如果当前难度大于堆中最小的数，也就是第 $k$ 大的难度，那么就用当前难度来替换掉。同时维护堆中数的和，当前题目的可做度就是堆中数字的和。这样就可以以 $\mathcal{O}(n\log V)$ 的复杂度得出可做度数组。  
复杂度分析：二分 $\mathcal{O}(\log n)$，判断 $\mathcal{O}(n\log V)$，总复杂度 $\mathcal{O}(n\log n\log V)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void print(int n){if(n<0){putchar('-');print(-n);return;}if(n>9)print(n/10);putchar(n%10+'0');}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
int n,m,k,l,r,v[100005],a[100005],sum,ans=-1;
bool check(){
    sum=0;
    priority_queue<int,vector<int>,greater<int> >q;
    while(!q.empty())q.pop();
    for(int i=1;i<=k;i++){
        q.push(v[i]);
        sum+=v[i];
    }
    a[k]=sum;
    for(int i=k+1;i<=n;i++){
        q.push(v[i]);//当前难度入堆
        sum+=v[i]-q.top();//维护堆中数字和
        q.pop();//维护前k个数，这里如果当前难度并非前k大就会被pop掉，否则pop掉的就是被替换掉的数
        a[i]=sum;
    }//求可做度数组
    sum=0;
    for(int i=k;i<=n;i++)sum+=a[i];//求可做度和
    if(sum>r)return false;
    if(l<=sum&&sum<=r)ans=max(ans,sum);//符合条件，更新答案
    return true;
}
signed main(){
    cin>>n>>m>>k>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    int left=1,right=1000000000000;
    while(left<=right){
        int mid=(left+right)/2;
        v[m]=mid;
        if(check())left=mid+1;
        else right=mid-1;
    }//二分
    cout<<ans;
    return 0;
}
```

---

## 作者：_d_h_f (赞：1)

本题解首次分析时间复杂度的时候有误，感谢 lovely_hyzhuo 的反馈

### Solution
看到这题数据范围的第一眼，我便察觉到这道题复杂度大概率是 $O(n\log^2 n)$ 的写法，可想到二分答案，定义 $\operatorname{chk}$ 函数用于线性搜索，那么 $\operatorname{chk}$  是如何实现线性扫描的呢，不难联想到优先队列，对于 $a_1,a_2,a_3,\ldots,a_{k-1},a_k$，我们不需要对其进行可做性操作，只需要对 $a_{k+1},a_{k+2},\ldots,a_n$ 进行可做性操作，所以可以用一个变量来存储当前第 $i(i\geq k)$ 道题的可做性，用优先队列存储前 $i$ 个数中最大的 $k$ 个数，用计数器对前 $i$ 道题的可做性进行累加，最后判断输出即可，别忘了每次操作后清空优先队列。

### Code

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll L,R;
ll n,m,k,ans;
ll a[100001];
priority_queue<ll,vector<ll>,greater<ll> > q;
ll chk(ll x){
	while(!q.empty())
		q.pop();
	ll t=a[m],sum=0,now=0;
	a[m]=x;
	for(int i=1;i<=k;++i)
		now+=a[i],q.push(a[i]);
	for(int i=k;i<=n;++i){
		if(i==k){
			sum+=now;continue;
		}
		q.push(a[i]);
		now+=a[i]-q.top();
		q.pop();
		sum+=now;
	}
	a[m]=t;
	return sum;
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&n,&m,&k,&L,&R);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	ll l=1,r=2e9;
	while(l<=r){
		ll mid=l+r>>1;
		if(chk(mid)>=L&&chk(mid)<=R)
			ans=chk(mid),l=mid+1;
		else if(chk(mid)<L)
			l=mid+1;
		else	
			r=mid-1;
	}
	if(!ans){
		printf("-1\n");
		return 0;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：sbno333 (赞：1)

考试时找到某个神奇的方法，但关于这个方法思路极其不清晰，因此敲不出来，表有了下面的方法。

这里我们规定 $u$ 为各题难度值，我们可以发现当 $u_m$ 的值确定时，整个序列就确定了，此时求总可做性的方法如下。

建立优先队列，里面装的是为对每次题目给予贡献的难度值的 $k$ 个数。

建立一个计数器，记录当前题目的总可做性，即优先队列所有元素的和，答案为所有题目总可做性的和。

对于每个题目 $x$，维护优先队列，可以将新的题目加入优先队列，将计数器增加这个难度值，然后删除优先队列中最小的值，计数器减去减的这个难度值即可。
```cpp
long long w(long long x){//此时u[m]=x
	long long ans,sum;//答案，计数器
	ans=sum=0;
	u[m]=x;
	while(q.size()){
		q.pop();
	}
	for(long long i=1;i<=k;i++){//先建立，第一个要算的是第k个题的可做性，为u数组第1到k个值的和
		q.push(u[i]);
		sum+=u[i];
	}
	ans+=sum;
	for(long long i=k+1;i<=n;i++){
		q.push(u[i]);
		sum+=u[i];
		sum-=q.top();
		q.pop();
		ans+=sum;
	}
	return ans;
}
```

我们发现，随着 $a_m$ 的上升，答案是单调不降的。

因此可以二分 $u_m$。

不难发现，我们要确保答案小于 $r$，再此基础上尽量大，如果最后的得数小于 $l$ 则无解，否则答案为这个值。
```cpp
int main(){
	cin>>n>>m>>k>>l>>r;
	for(long long i=1;i<=n;i++)
		cin>>u[i];
	long long l1,r1;
	r1=1e9;
	l1=0;
	while(l1<r1){
		long long mid;
		mid=(l1+r1+1)/2;
		if(w(mid)<=r){
			l1=mid;
		}else{
			r1=mid-1;
		}
	}
	long long z;
	z=w(l1);
	if(l<=z&&z<=r){
		cout<<z<<endl;
	}else{
		cout<<-1<<endl;
	}
	return 0;
}
```
我们设二分的值域大小为 $V$。

最后时间复杂度为二分的 $O(\log{V})$，单次函数的优先队列的 $O(\log{n})\times n=O(n\log{n})$，总时间复杂度为 $O(n\log{n}\log{V})$，最坏情况计算 $10^5\times\log{10^5}\times\log{10^9}\approx5\times10^6$次，不会超时。

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
- 有 $n$ 道题。对于任意 $i≥k$，它的可做性为 $1∼i$题中**难度值最大的k道题**的难度和。
- 你可以修改第 $m$ 道题的难度值。
- 求最大的所有题目的可做性之和，且在 $l∼r$ 之间。若无法满足，输出 $-1$。

# 思路
**二分枚举**第 $m$ 题的难度，计算在当前情况下所有题目的可做性之和是否满足条件即可。

下面重点解释`check`部分。

~~百分百包懂哈！~~

先想暴力，肯定会超时的。

再想如何优化，我们可以通过 $i$ 的可做性得到 $i+1$ 的可做性。

那么我们就可以用优先队列来维护 $1∼i$ 中前 $k$ 大的难度值，再用`sum`维护前 $k$ 大的难度值之和。

先将`sum`初始化为 $1∼k$ 的难度值之和，也就是第 $k$ 题的可做性。题目中也说了，第$1∼k-1$ 题无需计算。

接下来遍历第 $k+1∼n$ 题。

如果第 $i$ 题的难度值 $<$ 前 $k$ 大的难度值中最小的，也就是队头，那么第 $i$ 题的可做性 $=$ 第 $i+1$ 题的可做性，`sum`无需变动。

否则第 $i$ 题的可做性就会抵掉前 $k$ 大的难度值中最小的，也就是删除队头，更新`sum`的值。

# 代码
为了让代码简短，在`check`中使用了一点点技巧。

按原思路写也没有任何问题。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=1e5+10;
int n,m,k,L,R,a[N],ans;
int check(int x){
	priority_queue<int,vector<int>,greater<int>> q;
	int sum=0,t=a[m],s;
	a[m]=x;
	//s先算上k的 
	for(int i=1;i<=k;i++)s=sum+=a[i],q.push(a[i]);
	//通过i得到i+1 
	for(int i=k+1;i<=n;i++){
		/*a[i]小于q.top：被弹出
		否则抵掉最小的*/
		q.push(a[i]);
		sum+=a[i]-q.top();
		q.pop();
		s+=sum;
	}
	a[m]=t;
	return s;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m>>k>>L>>R;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=1,r=1e9;
	while(l<=r){
		int mid=l+r>>1,j=check(mid);
		if(L<=j&&j<=R)ans=j,l=mid+1;
		else if(j<L)l=mid+1;
		else r=mid-1;
	}
	if(!ans)cout<<-1;
	else cout<<ans;
	return 0;
}



```
### 谢谢！

---

## 作者：rainbow_cat (赞：0)

显然难度值越大，可做性越高，所以考虑二分答案。   
二分本体好想，难点在计算可行性上。维护一个优先队列以及其和，每次加入后缩小大小至 $k$ 即可，初始要提前推入前 $k$ 个数，总复杂度 $O(n \log ^2 n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,m,l,r,ans,a[200010];
priority_queue<int,vector<int>,greater<int>>q;
int check(int x)
{
	int res=0,sum=0,las=a[p];
	q=priority_queue<int,vector<int>,greater<int>>();
	a[p]=x;
	for(int i=1;i<m;i++)q.push(a[i]),sum+=a[i];
	for(int i=m;i<=n;i++)
	{
		q.push(a[i]),sum+=a[i];
		if(q.size()>m)sum-=q.top(),q.pop();
		res+=sum;
	}
	a[p]=las;
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>p>>m>>l>>r;
	for(int i=1;i<=n;i++)cin>>a[i];
	int al=1,ar=1000000000;
	while(al<ar)
	{
		int mid=(al+ar+1)/2;
		int tmp=check(mid);
		if(tmp>r)ar=mid-1;
		else al=mid;
	}
	ans=check(al);
	if(l<=ans&&ans<=r)cout<<check(al);
	else cout<<-1;
	return 0;
}
```

---

## 作者：DFM_O (赞：0)

## [P9636题目](https://www.luogu.com.cn/problem/P9636)

### 解题思路
我们很容易就能发现，$v_m$ 越大，可做性之和就越大，二分 $v_m$ 即可。

但如果直接枚举出 $a_1,a_2,…,a_n$，就需要 $O(n^2)$ 的复杂度，肯定会超限。

当 $i\ge k$ 时，$a_i$ 为 $v_1∼v_i$ 中较难的 $k$ 道题目的难度值之和，$a_{i+1}$ 为 $v_1∼v_{i+1}$ 中较难的 $k$ 道题目的难度值之和。

设 $v_1∼v_i$ 中第 $k$ 难的题目的难度为 $q$。不难发现，如果 $v_{i+1}\le q$，则 $a_{i+1}=a_i$，否则将 $v_1∼v_i$ 中第 $k$ 难的题目换成第 $i+1$ 道题目就是较难的 $k$ 道题目，即 $a_{i+1}=a_i-q+v_{i+1}$。

我们可以用优先队列来存取较难的 $k$ 道题目，并二分 $v_m$ 即可，时间复杂度为 $O(n \operatorname{log} n \operatorname{log} V)$。

### Code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
#define int long long//记得开long long
priority_queue<int,vector<int>,greater<int> > c;//优先队列
int v[100001];
int n,k,m,l,r;
int kz()//计算可做性之和
{
	int zs=0,s=0;
	for(int i=1;i<=c.size();)//清空队列
		c.pop();
	for(int i=1;i<=k;++i)
		c.push(v[i]),s+=v[i];
	zs+=s;
	for(int i=k+1;i<=n;++i)
	{
		if(v[i]>c.top())
		{
			s=s+v[i]-c.top(),zs+=s;
			c.pop(),c.push(v[i]);
		}
		else
			zs+=s;
	}
	return zs;
}
int ef()//二分就不说了
{
	int ll=0,rr=1000000000,mid,maxx=-1;//maxx用来可做性之和的记录最大值
	while(ll<=rr)
	{
		mid=rr-(rr-ll)/2,v[m]=mid;
		int zzs=kz();
		if(zzs>=l&&zzs<=r)
			maxx=max(zzs,maxx),ll=mid+1;
		else
		{
			if(zzs<l)
				ll=mid+1;
			if(zzs>r)
				rr=mid-1;	
		}
	}
	return maxx;
}
signed main()//这里要用signed
{
	scanf("%lld%lld%lld%lld%lld",&n,&m,&k,&l,&r);
	for(int i=1;i<=n;++i)
		scanf("%lld",&v[i]);
	int zs=ef();
	printf("%lld\n",zs);
    return 0;
}
```

---

## 作者：WxjzKK (赞：0)

发现自己好久没有给社区做贡献所以水了一道 tj。

题意就那样，好好看下应该就能懂了，这里讲下思路和细节。

一般呢，看到这种满足单调性的且输出要求为某一值的题，我们考虑用二分答案。而对于修改后的可做性总和，我们可以直接上优先队列暴力求解，时间复杂度 $O(n\ \log n\ \log V)$，这里的 $V$ 代表值域。

细节：

1. 在判断答案是否可行时，先判断答案是否在给定值域范围内，如果在，我们取右区间（因为要求最大），其他的就是简单的二分模板了。

2. 二分答案的 $l$，$r$ 和题目输入的 $l$，$r$ 千万别混淆了（这里卡了好久，还以为是别的问题）。

3. 要开 long  long，这边还是建议直接 define。
```cpp
#define int long long
...
signed main(){
}
```

Code

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define int long long
using namespace std;
inline void read(int &n){
	int s=0,t=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') t=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<3)+(s<<1)+(c^48);c=getchar();
	}
	n=s*t;
}
inline void put(int n){
	if(n<0){
		putchar('-');n=-n;
	}
	if(n<10){
		putchar(n+48);return;
	}
	put(n/10);
	putchar(n%10+48);
}
int n,k,tot=-1,sum,a[MAXN];
inline int getans(){
	priority_queue<int,vector<int>,greater<int> >q;
	int cnt=0,ans;
	for(register int i=1;i<=k;++i){
		q.push(a[i]);cnt+=a[i];
	}
	ans=cnt;
	for(register int i=k+1;i<=n;++i){
		if(a[i]>q.top()){
			cnt-=q.top();q.pop();
			q.push(a[i]);cnt+=a[i];
		}
		ans+=cnt;
	}
	return ans;
}
signed main(){
	int m,left,right,l,r;
	read(n);read(m);read(k);read(left);read(right);
	for(register int i=1;i<=n;++i) read(a[i]);
	l=0;r=2*right;
	while(l<r){
		int mid=(l+r)>>1,t;
		t=a[m];a[m]=mid;sum=getans();a[m]=t;
		if(sum>=left&&sum<=right){
			tot=sum;l=mid+1;
		}
		else if(sum<l) l=mid+1;
		else r=mid;
	}
	put(tot);putchar('\n');
	return 0;
}

```

简单水过。

---

