# Hossam and Friends

## 题目描述

Hossam makes a big party, and he will invite his friends to the party.

He has $ n $ friends numbered from $ 1 $ to $ n $ . They will be arranged in a queue as follows: $ 1, 2, 3, \ldots, n $ .

Hossam has a list of $ m $ pairs of his friends that don't know each other. Any pair not present in this list are friends.

A subsegment of the queue starting from the friend $ a $ and ending at the friend $ b $ is $ [a, a + 1, a + 2, \ldots, b] $ . A subsegment of the queue is called good when all pairs of that segment are friends.

Hossam wants to know how many pairs $ (a, b) $ there are ( $ 1 \le a \le b \le n $ ), such that the subsegment starting from the friend $ a $ and ending at the friend $ b $ is good.

## 说明/提示

In the first example, the answer is $ 4 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[1, 2\]

In the second example, the answer is $ 5 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[4\]

\[3, 4\]

## 样例 #1

### 输入

```
2
3 2
1 3
2 3
4 2
1 2
2 3```

### 输出

```
4
5```

# 题解

## 作者：cjh20090318 (赞：19)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给定 $n$ 个数和 $m$ 个关系，每个关系的 $x$ 和 $y$ 不能出现在同一段中，请问有多少个连续子段符合要求。

## 分析题目

设 $a_i$ 为以 $i$ 为起点能符合要求的最远的终点，显然每个初始的终点都为 $n$。

当每给出一个关系 $x$ 和 $y$ 时，我们更新 $a_x=\min(a_x,y-1)$。

意思就是以 $x$ 为起点，如果原来的终点比现在的终点远，那么更新，因为终点过了 $y-1$ 就不符合要求了。

处理完 $m$ 个要求之后，**从大到小**枚举 $1 \le i <n$ 更新 $a_i = \min(a_i,a_{i+1})$。因为在 $i$ 之前的值都会受到 $a_i$ 的限制。

所以最终答案为 $\sum\limits_{i=1}^n{a_i-i+1}$，**一定要加一，因为一个数本身也是符合要求的一个段**。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
using namespace std;
int a[100001];
void solve(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) a[i]=n;//能到的最远点设为 n。
	int x,y;
	while(m--){
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);//此操作保证 x<y。
		a[x]=min(a[x],y-1);//更新答案。
	}
	for(int i=n-1;i>=1;i--)//从大到小！
		a[i]=min(a[i],a[i+1]);//更新限制。
	long long ans=0;
	for(int i=1;i<=n;i++)
		ans+=a[i]-i+1;//最远点减起点加一。
	printf("%lld\n",ans);
}
int main(){
	int t;scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：2)

题意：一个长度为 $n$ 的序列，有 $m$ 条边，求有多少对合法的 $l,r$，满足 $\forall l\le i,j\le r,i\ne j$，$i$ 和 $j$ 之间没有连边。

设第 $i$ 条边连的两个点为 $l_i$ 和 $r_i$，其中 $l_i<r_i$，那么对于每一个 $l$，其对应的 $r$ 必须满足：$\forall 1\le i\le m,l_i\ge l$，$r<r_i$。

于是把边离线下来从右往左扫一遍就好了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Std{
void gi(int &x){
	x=0;
	int y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
	x*=y;
}
int T,n,m,l[200010],r[200010],id[200010];
bool cmp(int x,int y){
	return l[x]<l[y];
}
void solve(){
	gi(n);
	gi(m);
	for(int i(1);i<=m;++i){
		gi(l[i]);
		gi(r[i]);
		if(l[i]>r[i])swap(l[i],r[i]);
		id[i]=i;
	}
	sort(id+1,id+1+m,cmp);
	int now(m),rr(n);
	long long ans(0);
	for(int i(n);i;--i){
		while(now&&l[id[now]]==i){
			rr=min(rr,r[id[now]]-1);
			--now;
		}
		ans+=rr-i+1;
	}
	printf("%lld\n",ans);
}
void main(){
	gi(T);
	while(T--)solve();
}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```


---

## 作者：nytyq (赞：0)

## 分析

这道题灵感来源于 [CSP-S 2024 T3](https://www.luogu.com.cn/problem/P11233) 的第一篇题解。

根据灵感，考虑用 $ex_i$ 表示点 $i(1 \le i \le n)$ 能扩展的最远距离，初始时所有的 $ex_i$ 均为 $n$。

因为每次会添加一堆关系，所以一定会有 $ex_i$ 做变动，易得到做变动的式子为 $ex_i=\min(y_i-1,ex_i)$。

接着枚举 $i$ 从 $n-1$ 至 $1$，每一次的 $ex_i$ 都会被 $ex_{i+1}$ 所约束，考虑更新式子如下 $ex_i=\min(ex_i,ex_{i+1})$。

易知最后的答案为：
$$
ans=\sum_{i=1}^{n} ex_i-i+1
$$

## ACcode

```
#include<bits/stdc++.h>

using namespace std;

#define int long long 

const int N=1e5+10; 

int x[N],y[N];

int ex[N]; 

void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		ex[i]=n;
	}	
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		if(x[i]>y[i]) swap(x[i],y[i]);
		ex[x[i]]=min(ex[x[i]],y[i]-1);
	}
	for(int i=n-1;i>=1;i--) ex[i]=min(ex[i],ex[i+1]);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=(ex[i]-i+1);
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve(); 

	return 0;
}

```

---

## 作者：紊莫 (赞：0)

非常好怄火题，使我场上 30min 才切 B。

---

考虑一个点，向右延伸到的区间显然具有单调性。那么一定有一个能延伸到的最大值，我们求出这个值。

首先，对于一个已知的线段左端点 $x_i$，显然右端点最右到 $\min y_i$，多者取其小。然后考虑点 $x_i-1$，显然这个最小值向左具有传递性，那么我们倒着扫一遍就可以了，直接求得答案，时间复杂度 $O(n^2)$。

参考代码就不放了，实现比较简单。

---

## 作者：loser_seele (赞：0)

怎么第二个题就这么难写。

定义符合题目条件的区间为合法区间。

首先看见统计区间个数问题果断上双指针，考虑对于一个 $ l $ 统计 $ r $，每次增加 $ l $ 的时候区间右端点肯定不减，当对于一个 $ r $ 是不符合条件的区间时 $ r+1 $ 一定也不是，符合双指针法的基本条件。

于是每次增加 $ l $ 计算新的 $ r $，扩展右端点 $ r $ 直到不能扩展为止，答案加上 $ r-l+1 $。

问题转化为：已知区间 $ [l,r] $ 是一个合法区间，问 $ [l,r+1] $ 是否是合法区间。

这个问题就简单了，只要判断 $ r+1 $ 是否与 $ [l,r] $ 之间某个数之间有连边即可，可以用二分实现。

时间复杂度 $ \mathcal{O}(n\log{n}) $，因为指针单调不降，$ \log $ 来自于二分，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
#define li inline
#define re register
const int maxn=2e5+10;
vector<int>d[maxn];
bool inrange(int x,int l,int r)
{
int i=x;
auto it1= upper_bound(d[i].begin(),d[i].end(),r);
auto it2= lower_bound(d[i].begin(),d[i].end(),l);
int cntt = it1-it2;
return !cntt;
}
signed main()
{
    int T;
    for(r(T);T;--T)
    {
    	int n,m;
        r(n),r(m);
        for(int i=1;i<=n;i++)
        d[i].clear();
        for(int i=1;i<=m;i++)
        {
        int u,v;
        r(u),r(v);
        d[u].push_back(v);
        d[v].push_back(u);
        }
        for(int i=1;i<=n;i++)
        sort(d[i].begin(),d[i].end());
        int l=1,r=1,ans=0;
        while(l<=n)
        {
        while(r<=n&&inrange(r+1,l,r))
        r++;
        if(r>n)
        r=n;
        ans+=r-l+1;
        l++;
        }
        cout<<ans<<'\n';
    }
}
```


---

## 作者：_Remake_ (赞：0)

## 题目分析
有一个元素为 $1,2,3,4...n$ 的序列，给出 $m$ 对互斥关系，互斥的两个数不能在同一子串中，求合法的不同子串数量。

考虑枚举 $i$ 并计算 $i$ 作为左端点的子串数量，注意到确定左端点时，右端点具有可二分性，所以可以二分求出使子串合法的最远的右端点，当前位置作为左端点的贡献即为以 $i$ 为左端点最长合法子串的长度。

对于每个互斥关系，设 $x_i < y_i$，可以转化为：选择了第 $x_i$ 个位置就不能选择第 $y_i$ 个位置，并且我们会优先选择 $x_i$，所以可以对于每个 $x_i$ 开桶记录每个对应的 $y_i$ 的最小值，使用ST表预处理，二分时直接查询区间最小值，如果最小值小于二分区间则该区间不合法。

时间复杂度：$\mathcal{O}(\sum n\log \sum n)$
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
int read()
{
    int n=0,k=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,t,m;
int lim[100001];
int x,y;
int ST[100001][21];
int lg[100001];
bool check(int now,int mid)
{
	int len=lg[mid-now+1];
	int X=std::min(ST[now][len],ST[mid-(1<<len)+1][len]);
	if(X>mid)
	{
		return 1;
	}
	return 0;
}
namespace qwq
{
    void main()
    {
    	t=read();
    	while(t--)
    	{
    		n=read();
    		m=read();
    		for(int r=1;r<=n;r++)
    		{
    			lim[r]=n+1;
    		}
    		for(int r=1;r<=m;r++)
    		{
    			x=read();
    			y=read();
    			if(x>y)
    			{
    				std::swap(x,y);
    			}
    			lim[x]=std::min(lim[x],y);
    		}
    		for(int r=1;r<=n;r++)
    		{
    			ST[r][0]=lim[r];
    		}
    		for(int r=2;r<=n;r++)
    		{
    			lg[r]=lg[r>>1]+1;
    		}
    		for(int len=1;len<=lg[n];len++)
    		{
    			for(int L=1;L+(1<<len)-1<=n;L++)
    			{
    				ST[L][len]=std::min(ST[L][len-1],ST[L+(1<<(len-1))][len-1]);
    			}
    		}
    		int ans=0;
    		for(int r=1;r<=n;r++)
    		{
    			int idx=r;
    			int L=r,R=n,mid;
    			while(L<=R)
    			{
    				mid=(L+R)>>1;
    				if(check(r,mid))
    				{
    					idx=mid;
    					L=mid+1;
    				}
    				else
    				{
    					R=mid-1;
    				}
    			}
    			ans+=idx-r+1;
    		}
    		std::cout<<ans<<std::endl;
    	}
        return;
    }
}
signed main()
{ 
    //std::cout<<system("diff qwq.out 1.out");
    //freopen("qwq.in","r",stdin);
    //freopen("qwq.out","w",stdout);
    qwq::main();
    return 0;
}
/*
*/

```


---

