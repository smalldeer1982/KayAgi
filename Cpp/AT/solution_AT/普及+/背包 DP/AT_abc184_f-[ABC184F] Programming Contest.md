# [ABC184F] Programming Contest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc184/tasks/abc184_f

高橋くんはプログラミングコンテストに参加します。 このコンテストのコンテスト時間は $ T $ 分間で、 $ N $ 問の問題が出題されます。  
 高橋くんは超能力者なので、 $ i $ 番目の問題が $ A_i $ 分で解けることが分かっています。  
 高橋くんは $ N $ 問の中から $ 0 $ 問以上を、解くのにかかる時間の総和が $ T $ 分以下になるように選び、それらの問題を解きます。  
 選んだ問題を解くのにかかる時間の総和の最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 40 $
- $ 1\ \le\ T\ \le\ 10^9 $
- $ 1\ \le\ A_i\ \le\ 10^9 $

### Sample Explanation 1

$ 1,2,3,4 $ 問目を選ぶと、解くのにかかる時間の総和が $ 2+3+5+7=17 $ 分となり、 $ T=17 $ 分以下での最大になります。

### Sample Explanation 2

全ての問題を解くのが最適です。

### Sample Explanation 3

どの問題も解くことができません。

### Sample Explanation 4

$ 2,3,7 $ 問目を選ぶと、解くのにかかる時間の総和が $ 273555143 $ 分になります。

## 样例 #1

### 输入

```
5 17
2 3 5 7 11```

### 输出

```
17```

## 样例 #2

### 输入

```
6 100
1 2 7 5 8 10```

### 输出

```
33```

## 样例 #3

### 输入

```
6 100
101 102 103 104 105 106```

### 输出

```
0```

## 样例 #4

### 输入

```
7 273599681
6706927 91566569 89131517 71069699 75200339 98298649 92857057```

### 输出

```
273555143```

# 题解

## 作者：zibenlun (赞：7)

一定要通过啊！


# 歪解

看到题解里都是折半（或叫双端）搜索，那我就来发一个~~随便乱搞~~ 模拟退火。
### 考场利器
[模拟退火](https://baike.baidu.com/item/%E6%A8%A1%E6%8B%9F%E9%80%80%E7%81%AB%E7%AE%97%E6%B3%95/355508?fr=ge_ala)

由于我们不知道选几个数，所以直接暴力出选择的长度，再来跑上几遍 SA。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long a[1000005];
long long ans;
long long check(int len){
	long long cnt=0;
	for(int i=1;i<=len;i++){
		cnt+=a[i];
	}
	if(cnt<=m) return cnt;
	else return 0;
}
void SA(int len){
	double t=rand()%6000,x=0.682755;
	while(t>1e-15){
		int l=rand()%(len)+1,r=min(rand()%(n-len+1)+len,n);
		swap(a[l],a[r]);
		long long sum=check(len);
		if(sum>ans){
			ans=sum;
		}
		else {
			if(rand()*pow(x,100)>t) swap(a[l],a[r]);
		}
		t*=x;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10000;j++) SA(i);
	}
	cout<<ans;
	return 0;
}
```
# 正解
没什么讲的必要，纯纯模版题，双端搜完再二分拼合就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1100005],b[1100005],s[55],ans,m,cntt,cnt,n;
void dfs1(int x,long long sum){
	if(sum>m) return;
	if(x>n/2){
		a[++cnt]=sum;
		return;
	}
	dfs1(x+1,sum+s[x]);
	dfs1(x+1,sum);
}
void dfs2(int x,long long sum){
	if(sum>m) return;
	if(x>n){
		b[++cntt]=sum;
		return;
	}
	dfs2(x+1,sum+s[x]);
	dfs2(x+1,sum);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i];
	dfs1(1,0);
	dfs2(n/2+1,0);
	sort(a+1,a+cnt+1);
	sort(b+1,b+cntt+1);
	for(int i=1;i<=cnt;i++) ans=max(ans,b[upper_bound(b+1,b+cntt+1,m-a[i])-b-1]+a[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：4)

## 分析

其实这道题剪剪枝就能过了。

我们统计一个前缀和。如果当前 DFS 到的这一位所得的价值加上后面所有的值都比现在搜索到的最大价值小，则无需继续搜索；如果当前搜索到的值刚好等于上限（即不可能有更大的），则直接将最大价值变成上限；如果在搜索时最大价值已经无法再高，则无需继续搜索；如果加上当前搜索到的这一位就会超过上限，则不需要再考虑加上这一位的情况。

加上上面的剪枝优化，我们就可以将这道题的单个测试点最大的运行时间搞到一秒以内啦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50;
long long n,m;
long long a[N],s[N];
long long ans;
void dfs(int now_where,long long now_ans){
	if(now_ans==m){//剪枝 
		ans=m;
		return ;
	}
	if(ans>=m){
		return ;
	}
	if(now_ans+(s[n]-s[now_where])<=ans){
		return ;
	}
	if(now_where>n){
		ans=max(ans,now_ans);
		return ;
	}
	dfs(now_where+1,now_ans);//不加这一位 
	if(now_ans+a[now_where+1]<=m){
		ans=max(ans,now_ans);//可以加这一位 
		dfs(now_where+1,now_ans+a[now_where+1]);//加上 
	} 
	else{
		ans=max(ans,now_ans);
	}	
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){//前缀和 
		s[i]=s[i-1]+a[i];
	}
	dfs(0,0);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Suan_CY (赞：2)

# ABC184F题解：
## [题目传送门](https://www.luogu.com.cn/problem/AT_abc184_f)
### 题目重现：

> 给定 $N$ 个数，在数组中选任意个数，使得它们的总和不超过 $T$ 且最大。

---


## 思路1：DFS

根据这个思路，我们很容易就能写出代码：但我们会发现，这个代码的时间复杂度为 $O(2^{n})$，$n\leq40$ 这个数据量还是太大了。估算一下，当 $n = 40$ 时，最坏要执行 $10^{12}$。

但是，我们可以选择 **分成两部分搜索**，**第一次搜索前半段**，**第二次搜索后半段**，那么两次搜索，每次的时间复杂度为 $O (2^{\frac{n}{2}})$，也就是每次搜索最坏情况大概要执行 $10^6$ 次，这是完全可以接受的。于是考虑此算法。

## 思路2：折半搜索

就像上文中提到过的，折半搜索就是把将要搜索的问题分成两半，分别进行搜索，这样原本 $O (2^{n})$ 的时间复杂度就能降到 $O (2^{\frac{n}{2}})$ 。

不过，分别搜索很简单，但是我们两次搜索都只是获得了一半的信息。难点在于如何将这两部分合并起来。

在本题中，我们可以将问题分解为：

> 1、在前 $\frac{n}{2}$ 个数中选择的数的总和。
>
> 2、在后 $\frac{n}{2}$ 个数中选择的数的总和。

这两部分的方案组合起来，就是 **在 $N$ 个数中选择要选的数的方案的和**。考虑如何合并。

对于 $B$ 组中的一个方案，如果总和为 $K$，则 $A$ 组中所花费 $\leq M - K$ 的方案都能与其合并为一个合法方案。

因此，对于每个 $B$ 组方案，可以通过二分快速统计 $A$ 组方案中和为 $\leq M - K$ 的方案的最大值，从而方便的统计合法方案的最大值。

搜索 $A$ 组方案和 $B$ 组方案的复杂度分别为 $O (n^{\frac{n}{2}})$，搜索 $A$ 组方案和 $B$ 组方案的复杂度分别为 $O (2^{\frac{n}{2}})$，考虑到二分的花销，总时间复杂度降为 $ O(2^{\frac{n}{2}} \log (2^{\frac{n}{2}}))$，也就是 $ O(\frac{n}{2} \times 2^{\frac{n}{2}})$。

当然，二分的前提是有序，所以对 $A$ 组的方案从小到大排好序之后，再对 $B$ 组进行搜索。

## 最终代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define CLOSE ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
using namespace std;
int n,m,a[45],damn,b[1500000],cnt,maxx;
void dfs(int pos,int lim,int sum,bool flag){
    if(sum>m) return ;
    if(pos>lim){
        if(flag){
            int tmp=(upper_bound(b+1,b+1+cnt,m-sum)-b);
            damn+=tmp-1;
            tmp--;
            maxx=max(maxx,sum+b[tmp]);
        }
        else b[++cnt]=sum;
        return;
    }
    dfs(pos+1,lim,sum,flag);
    dfs(pos+1,lim,sum+a[pos],flag);
}
signed main(){
	CLOSE
	cin>>n>>m;
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	}
	dfs(1,n/2,0,0);
	sort(b+1,b+cnt+1);
	dfs(n/2+1,n,0,1);
	cout<<maxx;
	return 0;
}
```

---

## 作者：mlvx (赞：1)

### 题意

在 $n$ 个数中选出若干数，使得它们的和最大且不超过 $T$。

### 分析

注意到 $n\le40$，可以折半搜索。

搜索都会写，主要说后面的合并。

记得搜索的时候可以加个剪枝。

直接枚举一个存和的数组，然后二分查找和第一个数组相加的和小于等于 $T$ 的最大元素即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int w,n,c1,c2,a[47];ll ans,b1[8388609],b2[8388609];
void dfs1(int x,ll sum=0){
    if(sum>w)return;
    if(x>n/2)return b1[++c1]=sum,void();
    dfs1(x+1,sum),dfs1(x+1,sum+a[x]);
}void dfs2(int x,ll sum=0){
    if(sum>w)return;
    if(x>n)return b2[++c2]=sum,void();
    dfs2(x+1,sum),dfs2(x+1,sum+a[x]);
}int main(){
    cin>>n>>w;
    for(int i=1;i<=n;i++)cin>>a[i];
    dfs1(1),dfs2(n/2+1);
    sort(b2+1,b2+c2+1);
    for(int i=1;i<=c1;i++)ans=max(ans,b1[i]+b2[upper_bound(b2+1,b2+c2+1,w-b1[i])-b2-1]);
    cout<<ans;
    return 0;
}
```

---

## 作者：cppcppcpp3 (赞：1)

## Solution

$n \le 40$，暴搜 $2^n$ 超时，可以用**折半搜索**做到 $O(2^{\frac{n}{2}})$。

折半搜索，就是先分别搜出左半部分、右半部分的答案，并将其存下来，再通过枚举，在满足题目限制的前提下，合成全局的答案。

这道题里，分别搜左半部分和右半部分不大于 $T$ 的所有可能选出的和。对左半部分的所有和排序。再对每个右边的答案，二分出左边可匹配的最大值，最终答案取 $\max$ 即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=41;

inline int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,m,ans,a[N];
vector<int> v[2]; //存左右两边的答案

void dfs(int s,int t,int tot,int o){
	if(tot>m) return;
	if(s>t) return v[o].push_back(tot),void();
	dfs(s+1,t,tot,o),dfs(s+1,t,tot+a[s],o);
}

signed main(){
	n=wrd(),m=wrd();
	for(int i=1;i<=n;++i) a[i]=wrd();
	if(n==1) return printf("%lld",a[1]>m?0:a[1]),0;
	
	int mid=(1+n)>>1;
dfs(1,mid,0,0),sort(v[0].begin(),v[0].end()),dfs(mid+1,n,0,1); //搜索
	
	for(int i=0;i<(int)v[1].size();++i){
		int l=0,r=v[0].size()-1,pos=0;
		while(l<=r){
			int x=(l+r)>>1;
			if(v[0][x]+v[1][i]<=m) pos=x,l=x+1;
			else r=x-1;
		}
		ans=max(ans,v[0][pos]+v[1][i]); //合并
	}
	return printf("%lld",ans),0;
} 
```

同样是折半搜索的题：[P4799](https://www.luogu.com.cn/problem/P4799)。

---

## 作者：I_Like_Play_Genshin (赞：0)

大家好我是口胡大师，我来口胡一下这一题的做法。

## Solution

首先，~~根据大眼观察法~~我们可以得出应该是一道折半搜索题，看看这道题的话复杂度大概在 $\mathcal O(2 \times 2^{\frac{n}{2}}\times \log_2 2^{\frac{n}{2}})$，应该是能过的。

先前半部分搜索，存进一个 set 里面，然后后半部分搜索，搜到交汇点之后就用二分，设当前和为 $x$，则你需要在 set 里面二分出一个最大的不超过 $T-x$ 的数，然后搞个 $ans$ 记录一下最大值即可。

## Code

代码实现应该没有难度吧？

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
折半搜索板子题。

观察到 $n$ 很小，考虑将其拆分成两半，分别暴力枚举可能的答案最后再合并。

主要讲一下合并的过程：在前一半中去一个可能的和，在后一半二分查找一个最大的且两数之和不超过 $T$ 的数字，取最大值即可。

### Code:

```python
#include<bits/stdc++.h> 
#define ll long long
#define N 5000005
#define M 45
using namespace std;
ll n,k,a[M],s[N],cnt=0,ans=0,s1[N],cnt1=0;
map<ll,ll> m;
void dfs(int l,int r,ll sum){
	if(l>r){
		if(r==n/2) s[++cnt]=sum;
		else{
			s1[++cnt1]=sum;
		} 
		return ;
	}
	dfs(l+1,r,sum+a[l]);
	dfs(l+1,r,sum);
}
int main(){
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	dfs(1,n/2,0);
	dfs(n/2+1,n,0);
	sort(s1+1,s1+cnt1+1);
	for (int i=1;i<=cnt;i++){
		ll x=s1[upper_bound(s1+1,s1+cnt1+1,k-s[i])-s1-1]+s[i];
		if(x<=k) ans=max(ans,x);
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：huangruiheng0217 (赞：0)

### 题意

给定 $N$ 个数，在数组中选任意个数，使得它们的总和不超过 $T$ 且最大。

$1 \le N \le 40$。

### 分析

观察到 $N$ 很小，但直接搜索容易超时，符合双向搜索的数据特征，故考虑使用双向搜索解决本题。具体做法如下：

对数据的前一半进行深搜，将所有结果存入一个新的数组内。然后对数据的后一半进行深搜，与前一半搜索结果进行匹配。

剪枝：由于数据都是正数，深搜过程中如果已经出现了大于限制 $T$ 的值，不必继续搜索。

匹配考虑采用二分，具体实现可以使用 `upper_bound` 函数（找到数组中第一个大于目标值的元素的下标，减 $1$ 就是要求的值）。

注意事项：使用 `upper_bound` 要先对数组排序。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,lim;
int a[45];
int ans[2000005];
int maxn=0;
int cur=0;
void dfs1(int step,int t){
    if(t>lim)
        return;
    if(step>n/2){
        ans[++cur]=t;
        return;
    }
    dfs1(step+1,t);
    dfs1(step+1,t+a[step]);
}
void dfs2(int step,int t){
    if(t>lim)
        return;
    if(step>n){
        int ret=t+ans[upper_bound(ans+1,ans+cur+1,lim-t)-ans-1];
        maxn=max(maxn,ret);
        return;
    }
    dfs2(step+1,t);
    dfs2(step+1,t+a[step]);
}
signed main(){
    cin>>n>>lim;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    dfs1(1,0);
    sort(ans+1,ans+cur+1);
    dfs2(n/2+1,0);
    cout<<maxn<<endl;
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

折半搜索板子。

暴力搜索 $[1,\lfloor \frac{n}{2} \rfloor]$ 所有可能的情况，放入集合 $S$ 中，

然后在暴力搜索 $[\lfloor \frac{n}{2} \rfloor+1,n]$ 所有的情况时，设当前和为 $sum$，需要找出 $S$ 中小于等于 $T-sum$ 的最大值来更新答案，二分即可。

时间复杂度为 $O(\frac{n}{2} \times 2^{\frac{n}{2}})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=41;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,ans;
ll a[N];
set<ll> S;
void dfs(ll x,ll n,ll sum,bool f){
	if(sum>m)
	  return ;
	if(x==n+1){
		if(f)
		  S.insert(sum);
		else{
			auto it=S.upper_bound(m-sum);
			if(it==S.begin())
			  return ;
			it--;
			ans=max(ans,(*it)+sum);
		}
		return ;
	}
	dfs(x+1,n,sum,f);
	dfs(x+1,n,sum+a[x],f);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	dfs(1,n/2,0,1);
	dfs(n/2+1,n,0,0);
	write(ans);
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc184_f)

## 前置知识

[Meet in the middle](https://oi-wiki.org/search/bidirectional/#meet-in-the-middle)

## 解法
  - 非正解
    - 当成超大背包来做，暴力枚举每个数是否进行相加。
    - 时间复杂度为 $O(2^{n})$。
	```cpp
	ll p[50],ans=0;
	void dfs(ll x,ll n,ll m,ll worth)
	{
		if(x==n+1)
		{
			if(worth<=m)
			{
				ans=max(ans,worth);
			}
		}
		else
		{
			if(worth+p[x]<=m)
			{
				dfs(x+1,n,m,worth+p[x],worth+p[x]);
			}
			dfs(x+1,n,m,worth);
		}
	}
	int main()
	{
		ll n,m,i;
		cin>>n>>m;
		for(i=1;i<=n;i++)
		{
			cin>>p[i];
		}
		dfs(1,n,m,0);
		cout<<ans<<endl;
		return 0;
	}
	```
  - 正解
    - 考虑优化搜索过程，使用双向搜索。具体地，对于 $1 \sim \left\lfloor \frac{n}{2}\right\rfloor$ 进行第一遍搜索，对于得到的价值存到一个 ``set`` 里面。对于 $\left\lfloor \frac{n}{2}\right\rfloor+1 \sim n$ 进行第二遍搜索，对于得到的总和在 ``set`` 里面找到满足 $\le T$ 减去当前总和的最大总和，进行转移即可。
    - 时间复杂度为 $O(2^{\frac{n}{2}}n)$ 。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
set<ll>vis;
ll p[50],ans=0;
void dfsl(ll x,ll n,ll m,ll worth)
{
    if(x==n+1)
    {
        if(worth<=m)
        {
            vis.insert(worth);
        }
    }
    else
    {
        if(worth+p[x]<=m)
        {
            dfsl(x+1,n,m,worth+p[x]);
        }
        dfsl(x+1,n,m,worth);
    }
}
void dfsr(ll x,ll n,ll m,ll worth)
{
    if(x==n+1)
    {
        if(worth<=m)
        {
            ans=max(ans,worth+(*(--vis.upper_bound(m-worth))));
        }
    }
    else
    {
        if(worth+p[x]<=m)
        {
            dfsr(x+1,n,m,worth+p[x]);
        }
        dfsr(x+1,n,m,worth);
    }
}
int main()
{
    ll n,m,i;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>p[i];
    }
    dfsl(1,n/2,m,0);
    dfsr(n/2+1,n,m,0);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

看一眼数据范围看到 $n=40$，其实这个范围的算法不多的，要么某些逆天 $O(n^5)$ 做法，但是其实更多的还是 $O(2^{\frac{n}{2}})$ 的折半搜。

然后就可以分为前 $\frac{n}{2}$ 个和后 $\frac{n}{2}$ 分别爆搜，前面部分存入输出，后面部分二分一个最大的值使得和最大且 $\leq T$ 即可。

复杂度 $O(2^{\frac{n}{2}} \log 2^{\frac{n}{2}})=O(2^{\frac{n}{2}}\frac{n}{2})$。

```cpp
int a[2010101], len;
int x[41], n, t, ans=0;
void dfs(int u, int up, int type, int sum) {
	if (t < sum) return ; 
	if (u == up+1) {
		if (!type) a[++len]=sum;
		else {
			auto x=upper_bound(a+1,a+1+len,t-sum);
			--x;
			ans=max(ans,*x+sum);
		}
		return ;
	}
	dfs(u+1,up,type,sum);
	dfs(u+1,up,type,sum+x[u]);
}
signed main() {
	read(n, t);
	for (int i=1;i<=n;++i) read(x[i]);
	dfs(1,n/2,0,0);
	sort(a+1,a+1+len);
	dfs(n/2+1,n,1,0);
	write(ans,'\n');
	return 0;
}
```

---

## 作者：Lyccrius (赞：0)

注意到 $n$ 很小，考虑搜索。

可以考虑从大往小搜，并使用后缀和优化。

```cpp
    std::sort(a + 1, a + n + 1);
    std::reverse(a + 1, a + n + 1);
    for (int i = n; i >= 1; i--) s[i] = s[i + 1] + a[i];
    DFS(0, 1);
```

```cpp
void DFS(lxl now, int cur) {
    if (now > t) return;
    if (now + s[cur] <= ans) return;
    ans = std::max(ans, now);
    if (cur > n) return;
    DFS(now + a[cur], cur + 1);
    DFS(now, cur + 1);
    return;
}
```

TLE 一个点。

使用折半搜索加二分优化 $\mathcal O(2^n)$ 为 $\mathcal O(2^{\frac{n}{2}} \log 2^{\frac{n}{2}})$。

```cpp
void DFS(vlc &res, lxl now, int cur) {
    if (now > t) return;
    res.push_back(now);
    if (cur > n) return;
    DFS(res, now + a[cur], cur + 2);
    DFS(res, now, cur + 2);
    return;
}
```

```cpp
    DFS(resl, 0, 1);
    DFS(resr, 0, 2);
    std::sort(resl.begin(), resl.end());
    std::sort(resr.begin(), resr.end());
    resl.erase(std::unique(resl.begin(), resl.end()), resl.end());
    resr.erase(std::unique(resr.begin(), resr.end()), resr.end());
    for (int i = 0; i < resl.size(); i++) {
        int j = std::upper_bound(resr.begin(), resr.end(), t - resl[i]) - resr.begin() - 1;
        if (j >= 0) ans = std::max(ans, resl[i] + resr[j]);
    }
```

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/15388501.html)

题意：有 $n$ 个物品，你可以选择若干个物品，使他们的价值之和 $\leq t$，求他们价值之和的最大值。$n \leq 40, t\leq 10^9$。

首先看到这个 $n$ 非常小，但是暴力的 $O(2^n)$ 跑不过去。

这时我们就要想双端搜索。双端搜索的主要方法是：先搜一半，把这一半搜到的所有答案记录下来，再搜另一半，对于搜出的每个答案，在前一半的所有答案中找到最优的和他匹配。
那么我们先 $O(2^n)$ 去搜索前一半，把搜到的所有答案拍到一个数组里，然后再搜后半段，同样的拍到一个数组里。然后对于后半段的每一个数，我用 lower_bound 函数来算出前半段里最优的那个匹配。答案就是每一组匹配中两个数之和的最大值。

[代码](https://paste.ubuntu.com/p/zm2TMQXb54/)

---

## 作者：__Cby___ (赞：0)

## 思路
典型的折半搜索。暴搜复杂度为 $O(2^n)$，用折半搜索可以将复杂度降为 $O(2^{\frac{n}{2}})$，可以通过此题。   
具体思路是先暴搜出左右两半可能的小于 $T$ 的和，存在两个数组里，最后二分取最大值。  
## 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
long long int n, t;
long long int a[2000025];
long long int s1[2000025];
long long int s2[2000025];
long long int cnt1, cnt2;
int dfs1(long long int x, long long int s) {
	if (s > t)return 0;
	if (x == n / 2 + 1) {
		s1[++cnt1] = s;
		return 0;
	}
	dfs1(x + 1, s + a[x]);
	dfs1(x + 1, s);
	return 0;
}
int dfs2(long long int x, long long int s) {
	if (s > t)return 0;
	if (x == n + 1) {
		s2[++cnt2] = s;
		return 0;
	}
	dfs2(x + 1, s + a[x]);
	dfs2(x + 1, s);
	return 0;
}
int main() {
	cin >> n >> t;
	for (int i = 1; i <= n; i++) cin >> a[i];
	dfs1(1, 0);
	dfs2(n / 2 + 1, 0);
	sort(s1 + 1, s1 + 1 + cnt1);
	sort(s2 + 1, s2 + 1 + cnt2);
	long long int ss = 0;
	for (int i = 1; i <= cnt1; i++) {
		ss = max(ss, s1[i] + s2[upper_bound(s2 + 1, s2 + cnt2 + 1, t - s1[i]) - s2 - 1]);
	}
	cout << ss << endl;
	return 0;
}
```

---

