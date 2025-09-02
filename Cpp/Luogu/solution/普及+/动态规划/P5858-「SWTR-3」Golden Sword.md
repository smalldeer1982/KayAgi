# 「SWTR-3」Golden Sword

## 题目背景

小 E 不幸在一场战斗中失去了他的金宝剑。

## 题目描述

制造一把金宝剑需要 $n$ 种原料，编号为 $1$ 到 $n$，编号为 $i$ 的原料的坚固值为 $a_i$。

炼金是很讲究放入原料的顺序的，因此小 E 必须**按照 $1$ 到 $n$ 的顺序**依次将这些原料放入炼金锅。

但是，炼金锅的容量非常有限，它**最多只能容纳 $w$ 个原料**。

所幸的是，**每放入一个原料之前**，小 E 可以从中取出一些原料，数量不能超过 $s$ 个。

- 我们定义第 $i$ 种原料的耐久度为：放入第 $i$ 种原料时锅内的原料总数（包括正在放入的原料） $\times\ a_i$，则宝剑的耐久度为**所有原料**的耐久度之和。

小 E 当然想让他的宝剑的耐久度尽可能得大，这样他就可以带着它进行更多的战斗，请求出耐久度的最大值。

注：这里的“放入第 $i$ 种原料时锅内的原料总数**包括正在放入锅中的原料**，详细信息请见样例。

## 说明/提示

#### 「样例说明」

- **对于样例 1**，一种可行的**最优**方案为：
首先放进原料 1，此时锅内有 $1$ 种原料，耐久度为 $1\times a_1=1\times 1=1$。  
再放进原料 2，此时锅内有 $2$ 种原料，耐久度为 $2\times a_2=2\times 3=6$。  
再放进原料 3，此时锅内有 $3$ 种原料，耐久度为 $3\times a_3=3\times 2=6$。  
取出原料 1，再放进原料 4，此时锅内有 $3$ 种原料，耐久度为 $3\times a_4=3\times 4=12$。  
取出原料 4，再放进原料 5，此时锅内有 $3$ 种原料，耐久度为 $3\times a_5=3\times 5=15$。  
最终答案为 $1+6+6+12+15=40$。  
- **对于样例 2**，一种可行的**最优**方案为：  
放进原料 1，耐久度为 $1\times 1=1$。  
取出原料 1，放进原料 2，耐久度为 $1\times (-3)=-3$。  
放进原料 3，耐久度为 $2\times (-2)=-4$。  
放进原料 4，耐久度为 $3\times 4=12$。  
取出原料 2，放进原料 5，耐久度为 $3\times 5=15$。  
最终答案为 $1+(-3)+(-4)+12+15=21$。  
- **对于样例 3**，一种可行的**最优**方案为：  
  $a_1+2a_2+2a_3+3a_4+4a_5+3a_6+4a_7=17$。 
- **对于样例 4**，一种可行的**最优**方案为：  
$a_1+a_2+a_3+a_4+a_5=-15$。

#### 「数据范围与约定」

**本题使用捆绑测试。**

- Subtask #1（15 points）：$n\leq 10$。
- Subtask #2（5 points）：$n\leq 100$，$a_i\geq0$。
- Subtask #3（15 points）：$n\leq 300$。
- Subtask #4（15 points）：$s=w=n$。
- Subtask #5（5 points）：$a_i\geq 0$。
- Subtask #6（10 points）：$n\leq 2\times 10^3$。
- Subtask #7（10 points）：$s=1$。
- Subtask #8（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \leq s \leq w \leq n \leq 5\times 10^3$，$|a_i| \leq 10^9$。对于 Subtask $i$ 有 $|a_i|\leq 10^{i+1}$。

#### 「帮助/说明」

本题下发大样例，具体输入输出见 [**Big Sample**](https://pan.baidu.com/s/1erVDllDlvNlEShxh3U42gA) 中的 gold01-08.in/gold01-08.out。提取码：757d。  
**文件名与 Subtask 编号一一对应。**

#### 「来源」

[Sweet Round 03 D](https://www.luogu.com.cn/contest/24755)。  
idea & solution：ET2006。

## 样例 #1

### 输入

```
5 3 3
1 3 2 4 5
```

### 输出

```
40```

## 样例 #2

### 输入

```
5 3 3
1 -3 -2 4 5
```

### 输出

```
21```

## 样例 #3

### 输入

```
7 4 2
-5 3 -1 -4 7 -6 5
```

### 输出

```
17```

## 样例 #4

### 输入

```
5 3 1
-1 -3 -2 -4 -5
```

### 输出

```
-15```

# 题解

## 作者：pomelo_nene (赞：53)

$\ \ \ \ \ \ \ $一道套路 dp 题，做法应该是显然，难度还不如 T3。

$\ \ \ \ \ \ \ $考虑到要顺序放置，贡献与当前锅内的原料有关，所以我们考虑将这两个东西加入我们的 dp 式。

$\ \ \ \ \ \ \ $设 $dp_{i,j}$ 为放进 $i$ 原料，且当时正有 $j$ 个原料所得到的最大耐久度。有 dp 方程：

$$dp_{i,j}=\max \{dp_{i-1,k}+a_i \times j\}$$

$\ \ \ \ \ \ \ $其中$j-1 \leq k \leq \min \{m,j+s-1\}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,s,a[5505],dp[5505][5505];
int main(){
	scanf("%lld %lld %lld",&n,&m,&s);
	for(long long i=1;i<=n;++i)	scanf("%lld",&a[i]);
	for(long long i=0;i<=n;++i)	for(long long j=0;j<=m;++j)	dp[i][j]=-1008600110086001;
	dp[0][0]=0;
	for(long long i=1;i<=n;++i)
	{
		for(long long j=m;j;--j)
		{
			for(long long k=min(m,j+s-1);k>=j-1;--k)
			{
//				i-1 k j*a;
				dp[i][j]=max(dp[i][j],dp[i-1][k]+j*a[i]);
			}
		}
	}
	long long ans=-1008600110086001;
	for(long long i=0;i<=m;++i)	ans=max(ans,dp[n][i]);
	printf("%lld",ans);
	return 0;
}
```
$\ \ \ \ \ \ \ $因为这个代码实际上是 $O(nm^2)$ 的。实际因为数据过于水，得到 85。差评。

$\ \ \ \ \ \ \ $考虑到我们枚举 $j \times a_i$ 是一个定值。所以说我们的 dp 方程简化为：

$$dp_{i,j}=\max \{dp_{i-1,k}\}+a_i \times j$$

$\ \ \ \ \ \ \ $其中$j-1 \leq k \leq \min \{m,j+s-1\}$。

$\ \ \ \ \ \ \ $我们惊奇地发现，中间 $\max$ 的一坨是可以单调队列优化的！

$\ \ \ \ \ \ \ $~~（当然你也可以用线段树，我调爆了）~~

$\ \ \ \ \ \ \ $实际上这就是一道单调队列的板子题吧。。。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,s,a[5505],dp[5505][5505],q[5505],pos[5505];
int main(){
	scanf("%lld %lld %lld",&n,&m,&s);
	for(long long i=1;i<=n;++i)	scanf("%lld",&a[i]);
	for(long long i=0;i<=n;++i)	for(long long j=0;j<=m;++j)	dp[i][j]=-1008600110086001;
	dp[0][0]=0;
	for(long long i=1;i<=n;++i)
	{
		int l=1,r=1;
		q[l]=dp[i-1][m];
		pos[l]=m;
		for(long long j=m;j;--j)
		{
			while(pos[l]>j+s-1 && l<=r)	++l;
			while(q[r]<dp[i-1][j-1] && l<=r)	--r;
			pos[++r]=j-1;
			q[r]=dp[i-1][j-1];
			dp[i][j]=q[l]+j*a[i];
		}
	}
	long long ans=-1008600110086001;
	for(long long i=0;i<=m;++i)	ans=max(ans,dp[n][i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：35)

$\color{#00BFFF}\mathrm{This\ is\ Sweet\ Round\ 03.}$

[$\color{#00BFFF}\mathrm{Link:T4\ Golden\ Sword}$](https://www.luogu.com.cn/problem/T112463)

基础单调队列优化 $\mathrm{DP}$。

**本题解对 $\mathrm{Subtask}$ 单独讨论。**

---

对于 $\mathrm{Subtask}\ 1:$

直接爆搜即可。

期望得分：$15\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,w,s,a[15],ans=-1e9;
void dfs(int i,ll cos,int siz){
	cos+=(++siz)*a[i];
	if(i==n){ans=max(ans,cos);return;}
	for(int j=0;j<min(w,siz+1ll);j++)if(siz-j<=s)dfs(i+1,cos,j);
}
int main(){
	cin>>n>>w>>s;
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1,0,0);cout<<ans<<endl;
    return 0;
}
```


---

对于 $\mathrm{Subtask}\ 2,5:$

由于 $a_i\ge0$，所以贪心即可，答案为：

$$\sum_{i=1}^{i\leq n}\min(i,n)\times a_i$$

时间复杂度：$\mathcal O(n)$。

期望得分：$10\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,w,s,a[5555],ans;
int main(){
	cin>>n>>w>>s;
	for(ll i=1;i<=n;i++)cin>>a[i],ans+=a[i]*min(i,w);
	cout<<ans<<endl;
    return 0;
}
```


---

对于 $\mathrm{Subtask}\ 3,7:$

容易想到一种 $\mathrm{DP}$ 算法：$f_{i,j}$ 表示**放完第 $i$ 种原料，锅内共有 $j$ 种原料时**，前 $i$ 个原料耐久度之和的最大值，其中 $1\leq i\leq n,1\leq j\leq \min(i,n)$。

也很容易想到其转移方程：$f_{i,j}=\max_{k=j-1}^{k\leq \min(w,j+s-1)}f_{i-1,k}+j\times a_i$。

$\max_{k=1}^{k\leq w}f_{n,k}$ 即为答案。

时间复杂度：$\mathcal O(nws)$。

期望得分：$25\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,w,s,a[5555],dp[5555][5555];
int main(){
	cin>>n>>w>>s;
	memset(dp,0x9f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=min(i,w);j++)
			for(ll k=j-1;k<=min(w,j+s-1);k++)
				dp[i][j]=max(dp[i][j],dp[i-1][k]+j*a[i]);
	ll ans=-1e18;
	for(int i=1;i<=w;i++)ans=max(ans,dp[n][i]);
	cout<<ans<<endl;
    return 0;
}
```


---

对于 $\mathrm{Subtask}\ 4:$

由于 $n=w=s$，所以 $\mathrm{DP}$ 时维护一下后缀最大值即可，还可以将第一维省略掉。

- 该算法还可以通过 $\mathrm{Subtask}\ 2,5$。

时间复杂度：$\mathcal O(nw)$。

期望得分：$15\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,w,s,a[5555],dp[5555],mx[5555];
int main(){
	cin>>n>>w>>s;
	memset(dp,0x9f,sizeof(dp));
	memset(mx,0x9f,sizeof(mx));
	mx[0]=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=min(i,w);j++)dp[j]=mx[j-1]+a[i]*j;
		for(int j=min(i,w);j>=0;j--)mx[j]=max(mx[j+1],dp[j]);
	}
	ll ans=-1e18;
	for(int i=1;i<=w;i++)ans=max(ans,dp[i]);
	cout<<ans<<endl;
    return 0;
}
```


---

对于 $\mathrm{Subtask}\ 6:$

注意到 $n=3000$，时限被放到了 $1.5s$。

考虑用线段树维护 $f_{i-1,1}$ 到 $f_{i-1,w}$ 的区间最大值。

如果开 $3000$ 个线段树，空间存放不下，可以每次加入原料时清空线段树并重新建树。

时间复杂度：$\mathcal O(nw\log n)$。

期望得分：$10\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5555;
ll n,w,s,a[N],dp[N];
struct Seg_Tree{
	ll v[N<<2];
	void build(int l,int r,int x){
		if(l==r){v[x]=dp[l];return;}
		int m=l+r>>1;
		build(l,m,x<<1);
		build(m+1,r,x<<1|1);
		v[x]=max(v[x<<1],v[x<<1|1]);
	}
	ll query(ll l,ll r,ll ql,ll qr,ll x){
		if(ql<=l&&r<=qr)return v[x];
		ll m=l+r>>1,ans=-1e18;
		if(ql<=m)ans=max(ans,query(l,m,ql,qr,x<<1));
		if(m<qr)ans=max(ans,query(m+1,r,ql,qr,x<<1|1));
		return ans;
	}
}t;
int main(){
	cin>>n>>w>>s;
	memset(dp,0x9f,sizeof(dp));
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[1]=a[1];
	for(ll i=2;i<=n;i++){
		t.build(1,w,1);
		for(ll j=1;j<=min(i,w);j++)
			dp[j]=t.query(1,w,max(1ll,j-1),min(w,j+s-1),1)+a[i]*j;
	}
	ll ans=-1e18;
	for(int i=1;i<=w;i++)ans=max(ans,dp[i]);
	cout<<ans<<endl;
    return 0;
}
```


---

对于 $\mathrm{Subtask}\ 8:$

再放一下状态转移方程：$f_{i,j}=\max_{k=j-1}^{k\leq \min(w,j+s-1)}f_{i-1,k}+j\times a_i$。

对于上面的状态转移方程，我们**从 $f_{i,w}$ 往 $f_{i,1}$ 更新答案**。

如果 $f_{i-1,j}\ge f_{i-1,k}$ 且 $j<k$，那么**前者无论如何都比后者更优。**

我们考虑用单调队列优化上面的转移方程。

- 如果 $j>1$，我们在单调队列里插入 $f_{i-1,j-1}$。**插入时，如果队尾 $f_{i-1,k}<f_{i-1,j-1}$**，那么就弹出队尾。

- 计算到 $f_{i,j}(i>1,j>1)$ 时，**如果单调队列的队头 $f_{i-1,k}$ 已经超过范围**，即 $k>\min(j+s-1)$，那么就将 $f_{i-1,k}$ 弹出单调队列。

- 此时，单调队列的队头即为 $\max_{k=j-1}^{k\leq \min(w,j+s-1)}f_{i-1,k}$。

这样我们就实现了 $\mathcal O(1)$ 转移。

时间复杂度：$\mathcal O(nw)$。

期望得分：$25\%$。

- 由于出题人太菜，忘记有滚动数组这个优化了，所以空间放了 $256\mathrm{MB}$。（能想到单调队列的一定会滚动数组吧）

---

$\mathrm{std:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){//快读
	int x=0,sign=1;char s=getchar();
	while(!isdigit(s)){
		if(s=='-')sign=-1;
		s=getchar();
	}
	while(isdigit(s)){
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar();
	}
	return x*sign;
}
const int N=5555;
const ll inf=1ll<<60;
int n,w,s;
ll ans=-inf,a[N],dp[N][N];
struct monotone_queue{//单调队列
	int head,tail,id[N];
	ll d[N];
	inline void init(){
		head=1,tail=0;
	}
	inline void push(ll v,int x){//第一个参数为dp[i][x]
		while(head<=tail&&d[tail]<=v)tail--;
		d[++tail]=v;
		id[tail]=x;
	}
	inline void pop(int x){//弹出
		while(head<=tail&&id[head]-x>=s)head++;
	}
}q;
int main()
{
	n=read(),w=read(),s=read();
	for(int i=1;i<=n;i++)a[i]=read();
	dp[1][1]=a[1];
	for(int i=2;i<=n;i++){
		q.init();
		if(i>w)q.push(dp[i-1][w],w);//注意特判细节
		for(int j=min(w,i);j>=1;j--){
			if(j>1)q.push(dp[i-1][j-1],j-1);//先插入
			q.pop(j);//再弹出
			dp[i][j]=q.d[q.head]+1ll*a[i]*j;//O(1)转移 
		}
	}
	for(int j=1;j<=w;j++)ans=max(ans,dp[n][j]);//求答案
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Bosun (赞：20)

## 思路
其实这道题目一眼就能够写出转移方程：
f[p][j]=f[p^1][k]+a[i]*j;（j-1≤k≤min(j+s-1,w)）（此处我用了滚动数组）

然后就有35分，开个longlong 85分;

接下来我们来考虑如何优化：
观察到后面一坨都是a[i]*j,可以提出来；

前面就是在f[p^1]中找到一个长度为s+1的区间最小值（边界先别管）。

可以用一个单调队列，倒序插入，第一步把f[p^1][w]插入，后面每次都先将f[p^1][j-1]加入，然后删除下标＞min(j+s-1,w)的点，这样每次对头就是最优值。（其实不会影响到边界，无脑码过去就可以了）

## code:
85pts:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,s;
const int N=5501; 
typedef long long ll;
ll a[N],f[2][N];
int main(){
	cin>>n>>w>>s;
	int i,j,k;
	for(i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(i=0;i<=1;i++)for(j=0;j<=w;j++)f[i][j]=-1e15; 
	f[0][0]=0;
	int p=1;
	for(i=1;i<=n;i++){
		for(j=0;j<=w;j++)f[p][j]=-1e15;
		for(j=1;j<=min(i,w);j++){
			for(k=j-1;k<=min(j+s-1,w);k++)
			f[p][j]=max(f[p][j],1ll*f[p^1][k]+1ll*a[i]*j);
		}
		p^=1;
	}
	ll ans=-1e15;
	for(i=0;i<=w;i++)ans=max(ans,f[n&1][i]);
	cout<<ans<<endl;
	return 0;
}
```
100pts:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5501; 
int n,w,s,q[N];
typedef long long ll;
ll a[N],f[2][N];
int main(){
	cin>>n>>w>>s;
	int i,j,k;
	for(i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(i=0;i<=1;i++)for(j=0;j<=w;j++)f[i][j]=-1e15; 
	f[0][0]=0;
	int p=1;
	for(i=1;i<=n;i++){
		for(j=0;j<=w;j++)f[p][j]=-1e15;
		int h=1,t=1;
		q[h]=w;
		for(j=w;j>=1;j--){
			while(h<=t&&q[h]>min(j+s-1,w))h++;
			while(h<=t&&f[p^1][q[t]]<f[p^1][j-1])t--;
			q[++t]=j-1;
			f[p][j]=f[p^1][q[h]]+1ll*a[i]*j;
		}
		p^=1;
	}
	ll ans=-1e15;
	for(i=0;i<=w;i++)ans=max(ans,f[n&1][i]);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：KrOX (赞：12)

## 动态规划
因为选物品必须按次序，所以考虑动规。这道题转移方程应该还是蛮好想的。

$f[i][j]=max(f[i-1][j+k]+a[i] \times j),k=-1...j+s-1$

其中$f[i][j]$代表放入$i$种原料后炼熔缸中原料数目为$j$时得到的最大耐久度之和。

## 单调队列优化
显然这道题作为T4不会让你这么轻松AC，上述做法时间复杂度明显为$O(nw^2)$，不符合题意。
~~通过打表~~可以看出其满足单调性，我们考虑用单调队列优化。

## 注意点
有一个点卡了我不久（可能因为我太蒻了），就是初始值的设定问题，由于出题人给的“良心”绝对值，我们要将初始值设定成很小的数～

------------
下面放代码（用deque用习惯了）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,s;
long long f[5508][5508],a[5508],ans=LONG_LONG_MIN;
deque<int> q;
int main(){
	scanf("%d%d%d",&n,&w,&s);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=0;i<=n;i++) for(int j=0;j<=w;j++) f[i][j]=LONG_LONG_MIN;
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		while(q.size()) q.pop_back();
		for(int j=1;j<=min(w,s-1);j++){
			while(q.size()&&f[i-1][j]>=f[i-1][q.back()]) q.pop_back();
			q.push_back(j);
		}
		for(int j=1;j<=min(i,w);j++){
			if(f[i-1][j-1]!=LONG_LONG_MIN) f[i][j]=f[i-1][j-1]+a[i]*j;
			while(q.size()&&q.front()<j) q.pop_front();
			if(j+s-1<=w){
				while(q.size()&&f[i-1][j+s-1]>=f[i-1][q.back()]) q.pop_back();
				q.push_back(j+s-1);
			}
			if(f[i-1][q.front()]!=LONG_LONG_MIN) f[i][j]=max(f[i][j],f[i-1][q.front()]+a[i]*j);
		}
	}
	for(int i=1;i<=w;i++) ans=max(ans,f[n][i]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：chenxinyang2006 (赞：10)

就是一个很套路的$dp$题，感觉上是 摆渡车 + 划分，恰好这两个题我都做过

* $solution\ 1$

肉眼可见$dp$题

因为是要按顺序放，而且贡献还和锅内的原料总数有关，为了防止出现后效性，设$dp[i][j]$表示放入第$i$个原料，锅中共有$j$个原料，的最大宝剑的耐久度

然后每次转移的时候，枚举一个$k$，从$dp[i - 1][k]$转移

状态转移方程：

$dp[i][j] = max(dp[i][j],dp[i - 1][k] + a[i] \times j)$

注意这里是有一个限制的，$j - 1 \le k \le j + s - 1$（可以拿走$0 - w$个原料，但是一定要放入一个，要留位置）

最后枚举一下$j$，取个$max$

~~没错，这就是摆渡车的思路~~

$code : $

```cpp
#include <cstdio>
#include <cstring>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
int n,w,s;
ll dp[5505][5505],a[5505],ans = -inf;

inline ll min(ll a,ll b){
	if(a < b) return a;
	return b;
}

inline ll max(ll a,ll b){
	if(a > b) return a;
	return b;
}

int main(){
	register int i,j,k;
	scanf("%d%d%d",&n,&w,&s);
	for(i = 1;i <= n;++i){
		scanf("%lld",&a[i]);

	}
	memset(dp,0xcf,sizeof(dp));
	dp[0][0] = 0;
	for(i = 1;i <= n;++i){
		for(j = 1;j <= w;++j){
			for(k = j - 1;k <= min(j + s - 1,w);++k){
				dp[i][j] = max(dp[i][j],dp[i - 1][k] + a[i] * j);
			}
		}
	}
	for(j = 1;j <= w;++j){
		ans = max(ans,dp[n][j]);

	}
	printf("%lld\n",ans);
	return 0;
}
```

期望得分：$35pts$

实际得分：$85pts$

~~不要问，问就是数据水~~

* $solution\ 2$

你会发现上面那个式子超级简单

由于$a[i] \times j$是一个定值，所以只要考虑前面那个$dp[i - 1][k]$

其实这就是一个区间最大值的问题

每一次更新值就是单点修改

不用说了，上线段树

$code:$

没有，告辞

~~谁会去写这种没用的东西，线段树常数那么大，肯定会卡成暴力分~~

* $solution\ 3$

如果你做过划分的$88pts$或者$100pts$的话，你肯定知道怎么维护了

这题反而是个弱化版

如果不考虑撞边界的问题，闭区间$(j - 1,j + s - 1)$长度固定为$s$

固定长度，多次查询一段的最值

不用说了，单调队列

如果你不会这个的话，做[这个](https://www.luogu.com.cn/problem/P3957)

不过我们事实上是在一个矩阵上进行操作，只不过每次询问的都是不会修改的部分，并且固定宽为1罢了

所以每次还要清空一下

$code:$

```cpp
#include <cstdio>
#include <cstring>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
int n,w,s;
ll dp[5505][5505],a[5505],ans = -inf;

inline ll min(ll a,ll b){
	if(a < b) return a;
	return b;
}

inline ll max(ll a,ll b){
	if(a > b) return a;
	return b;
}

int h,r;//这里是开区间[h,r)
struct node{
	ll val,id;
}q[5505];

void push(ll val,int id){
	while(h != r){
		if(q[r - 1].val <= val){
			r--;
		}else{
			break;
		}
	}
	q[r].val = val;
	q[r].id = id;
	r++;
}

void pop(int id){
	while(h != r){
		if(q[h].id < id){
			h++;
		}else{
			return;
		}
	}
}

int main(){
	register int i,j,k;
	scanf("%d%d%d",&n,&w,&s);
	for(i = 1;i <= n;++i){
		scanf("%lld",&a[i]);
	}
	memset(dp,0xcf,sizeof(dp));
	dp[0][0] = 0;
	for(i = 1;i <= n;++i){
		h = 1,r = 1;
		for(j = 0;j <= min(s,w) - 1;j++){
			push(dp[i - 1][j],j);
		}
		for(j = 1;j <= w;++j){
			pop(j - 1);
			if(j + s - 1 <= w){
				push(dp[i - 1][j + s - 1],j + s - 1);
			}
			if(h != r){
				dp[i][j] = q[h].val + a[i] * j;
			}
		}
	}
	for(j = 1;j <= w;++j){
		ans = max(ans,dp[n][j]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

但是本代码常数表现极其不优秀 ~~一些测试点跑不过我的暴力~~

滚动数组版：

~~~cpp
#include <cstdio>
#include <cstring>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) < (b) ? (a) : (b)
int n,w,s;
ll dp[5505],a[5505],ans = -inf;

int h,r;
struct node{
	ll val,id;
}q[5505];

inline void push(ll val,int id){
	while(h != r){
		if(q[r - 1].val <= val){
			r--;
		}else{
			break;
		}
	}
	q[r].val = val;
	q[r].id = id;
	r++;
}

inline void pop(int id){
	while(h != r){
		if(q[h].id < id){
			h++;
		}else{
			return;
		}
	}
}

int main(){
	register int i,j,k;
	scanf("%d%d%d",&n,&w,&s);
	for(i = 1;i <= n;++i){
		scanf("%lld",&a[i]);
	}
	memset(dp,0xcf,sizeof(dp));
	dp[0] = 0;
	for(i = 1;i <= n;++i){
		if(i != 1){
			dp[0] = -inf;
	    }
		h = r = 1;
		for(j = 0;j <= (min(s,w) - 1);++j){
			push(dp[j],j);
		}
		for(j = 1;j <= w;++j){
		    if(j + s - 1 <= w){
				push(dp[j + s - 1],j + s - 1);
			}
		    dp[j] = -inf;
			pop(j - 1);
			if(h != r){
				dp[j] = q[h].val + a[i] * j;
	    	}
		}
	}
	for(j = 1;j <= w;++j){
		ans = max(ans,dp[j]);
	}
	printf("%lld\n",ans);
	return 0;
}
~~~

由于内存连续优势，这份跑得很快

---

