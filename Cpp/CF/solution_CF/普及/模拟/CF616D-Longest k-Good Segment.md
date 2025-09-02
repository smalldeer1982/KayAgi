# Longest k-Good Segment

## 题目描述

The array $ a $ with $ n $ integers is given. Let's call the sequence of one or more consecutive elements in $ a $ segment. Also let's call the segment k-good if it contains no more than $ k $ different values.

Find any longest k-good segment.

As the input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
```

### 输出

```
1 5
```

## 样例 #2

### 输入

```
9 3
6 5 1 2 3 2 1 4 5
```

### 输出

```
3 7
```

## 样例 #3

### 输入

```
3 1
1 2 3
```

### 输出

```
1 1
```

# 题解

## 作者：b6e0_ (赞：6)

[CF题面传送门](https://codeforces.com/contest/616/problem/D) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF616D) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF616D)

这题为什么评紫啊，只有黄题难度吧。

对于左端点 $i$，最远的右端点 $j$ 是单调递增的，这样就可以用双指针快速找出右端点。

注意到值域只有 $10^6$（其实大点也好办，离散化一下就行了），我们可以开桶记录每个数出现的次数，当$i$或$j$ 增加时，判断这个数有没有出现过就行了。

代码还有一点小细节，要注意边界问题，这点在代码中会解释。

代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
int a[500010],buc[1000010];//buc为桶
inline int read()//快读
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x;
}
int main()
{
	int n=read(),k=read(),i,j=1,tot=0,maxl=-1,maxi,maxj;
	for(i=1;i<=n;i++)
		a[i]=read();
	for(i=1;i<=n;i++)
	{
		while(j<n+2&&tot<=k)//这里j的上界是n+1，因为我是循环到个数大于限制时结束，否则当j=n成立时会忽略掉这种情况
		{
			if(!buc[a[j]])//如果未出现过
				tot++;//个数就加1
			buc[a[j++]]++;
		}
		if(j-i>maxl)
		{
			maxl=j-i;
			maxi=i;
			maxj=j-2;//这里要-2
		}
		buc[a[i]]--;
		if(!buc[a[i]])//如果这个数没有了
			tot--;//个数就减1
	}
	printf("%d %d",maxi,maxj);
	return 0;
}
```
时间复杂度为 $\mathcal O(n)$，空间复杂度为 $\mathcal O(a_i)$。

---

## 作者：hxhhxh (赞：4)

## 大意

给你一个长度为 $ n $ 的数组 $ a $ 和正整数 $ k $ ，求最长的线段 $ [l,r] $ ，使得 $ [l,r] $ 中有不超过 $ k $ 种不同的元素。

## 思路

易知随着线段的右端点向右移动，左端点单调不减，所以可以用一个双指针模拟线段，用一个桶和一个记录当前线段里的情况。

当线段里有超过 $ k $ 种不同值时，将左端点不断向右移直到减少一种元素。

用两个变量统计答案。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,T,cnt[1000006],a[500005],ansl=1,ansr=1;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,l=1,r=1;i<=n;i++){
		r=i;
		cnt[a[i]]++;
		if(cnt[a[i]]==1) t++;
		while(t>m){
			cnt[a[l]]--;
			if(cnt[a[l]]==0) t--;
			l++;
		}
		if(r-l>ansr-ansl) ansr=r,ansl=l;
	}
	cout<<ansl<<" "<<ansr;
	return 0;
}
```

---

## 作者：King丨帝御威 (赞：4)

直接用map来做就行，挺简单的一道字符串模拟题，就不必多说了，光看代码也能看懂。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#define maxn 1000007
using namespace std;
map <int,int> mp;
int a[maxn],l,len,cyh,zrj;
void del(int x)
{
    mp[x]--;
    if(mp[x]==0) mp.erase(x);
}
int main() {
  int n,k;
  scanf("%d%d",&n,&k);
  for(int i=0;i<n;++i) scanf("%d",&a[i]);
  for(int i=0;i<n;++i) {
    mp[a[i]]++;
    if(mp.size()>k) {
      for(;l<n&&mp.size()>k;++l)
        del(a[l]);
    }
    int ll=i-l+1;
    if(ll>len) {
      len=ll;
      cyh=l;
      zrj=i;
    }
  }
  printf("%d %d\n",cyh+1,zrj+1);
  return 0;
}
```

---

## 作者：He_Ren (赞：2)

# 算法1： two pointers（尺取法）

这种方法比较明显，也非常好调，比赛时就是用的这种方法

复杂度$O(n)$

```cpp
#include<cstdio>
const int MAXN = 5e5 + 5;
const int MAXA = 1e6 + 5;

int a[MAXN];
int t[MAXA];

int main(void)
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	
	int al=0,ar=0;
	t[a[1]]=1;
	for(int l=1,r=1,cnt=1; r<=n;)
	{
		while(cnt<=m && r<=n)
		{
			++r;
			if(!t[a[r]]) ++cnt;
			++t[a[r]];
		}
		
		if(r-l > ar-al)
			al=l, ar=r;
		
		--t[a[l]];
		if(!t[a[l]]) --cnt;
		++l;
	}
	printf("%d %d",al,ar-1);
	return 0;
}
```

# 算法2： 线段树

这种方法比较难想，思路和尺取法其实差不多，对于每个$l$，找到最大的满足条件$r$（程序中是最小的，**不满足条件**的$r$； _想一想，为什么这两种方法等价？_)

用线段树标记每种颜色第一次出现的位置，查询就是查询最小的，$ans>k$的位置，有点类似于二分

```cpp
int query(int u,int l,int r,int k)
{
	if(l==r) return l;
	
	int mid=(l+r)>>1;
	if(t[ls(u)]>k) return query(ls(u),l,mid, k);
	else return query(rs(u),mid+1,r, k-t[ls(u)]);
}
```

如何由$i$到$i+1$？

因为$i$这个点已经没有用了，所以就把这种颜色转到下一次出现的位置

```cpp
update(1,1,n+1, i,0);
if(nxt[i]<=n) update(1,1,n+1, nxt[i],1);
```

查询是这样的：

```cpp
int j=query(1,1,n+1, m);
```

直接查询$[1,n]$而不是$[i,n]$

**这里需要仔细理解**

修改只修改叶子，所以不用$\text{lazy\_tag}$

其实看代码更好理解

复杂度$O(n \log n)$

```cpp
#include<cstdio>
const int MAXN = 5e5 + 5;
const int MAXC = 1e6 + 5;

inline void chk_max(int &a,int b){ if(a<b) a=b;}

int a[MAXN],fst[MAXC],nxt[MAXN];

int t[MAXN<<2];
#define ls(u) ((u)<<1)
#define rs(u) ((u)<<1 | 1)

inline void push_up(int u){ t[u]=t[ls(u)]+t[rs(u)];}

void update(int u,int l,int r,int p,int k)
{
	if(l==r){ t[u]=k; return;}
	
	int mid=(l+r)>>1;
	if(mid>=p) update(ls(u),l,mid,p,k);
	else update(rs(u),mid+1,r,p,k);
	push_up(u);
}

int query(int u,int l,int r,int k)
{
	if(l==r) return l;
	
	int mid=(l+r)>>1;
	if(t[ls(u)]>k) return query(ls(u),l,mid, k);
	else return query(rs(u),mid+1,r, k-t[ls(u)]);
}

int main(void)
{
	int n,m;
	scanf("%d%d",&n,&m);
	int c=0;
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]), chk_max(c,a[i]);
	
	for(int i=0; i<=c; ++i) fst[i]=n+1;
	for(int i=n; i>=1; --i)
		nxt[i] = fst[a[i]],
		fst[a[i]]=i;
	
	for(int i=0; i<=c; ++i)
		if(fst[i]<=n) update(1,1,n+1, fst[i],1);
	
	int r=0,l=0;
	for(int i=1; i<=n; ++i)
	{
		int j=query(1,1,n+1, m);
		if(r-l < j-i)
			l=i, r=j;
		if(j>n) break;
		
		update(1,1,n+1, i,0);
		if(nxt[i]<=n) update(1,1,n+1, nxt[i],1);
	}
	
	printf("%d %d",l,r-1);
	return 0;
}
```


---

## 作者：kevin1616 (赞：1)

### 审题
给定一个包含 $n$ 个整数的序列 $a$，询问不重复数字个数 $\le k$ 的任意最长区间的左右端点。
***
### 方法
- 【暴力】一个双重暴力循环，每次看该区间是否合法，统计最长的区间，再输出左端点和右端点即可。但是时间复杂度是 $O(n^2)$，所以不可行。
- 【尺取法】每次加入右边，如果不符合条件，则退出左边，每次统计最长长度，最后输出最长区间的左端点和右端点。由于时间复杂度是 $O(n)$，所以该方法可行。

***
### 思路
有两个指针 $l$ 和 $r$，初始都指向 $1$，每次 $r$ 向右移动一格。然后判断此时不同数字个数是否 $\le k$，如果不是，那么每次 $l$ 向右移动一格，直到此时不同数字个数 $\le k$。

这里的加入和退出可以用 map 容器来实现。如果该数未出现过，则将当前不同数字个数自增 $1$。如果该数已经没了，则将当前不同数字个数自增 $-1$。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n;
int a[5000005];
int ans;
int cnt,ansl = 1,ansr = 1;
map <int,int> mp;
int main(){
    scanf("%d %d",&n,&k);
    for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
    int l = 1,r = 1; //初始化
    while(r <= n){ //持续条件
        if(!mp[a[r]]){
            while(cnt >= k){ //退出左端元素
                if(mp[a[l]] == l){
                    cnt--;
                    mp[a[l]] = 0;
                }
                l++; //左指针右移
            }
        }
        if(!mp[a[r]]) cnt++; //加入右端元素
        mp[a[r]] = r;
        if(ans < r - l + 1){ //统计答案
            ans = r - l + 1;
            ansl = l;
            ansr = r;
        }
        r++; //右指针右移
    }
    cout << ansl << " " << ansr << endl; //输出答案
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：Light_az (赞：0)

适合练手的双指针模板题目。

我们定义 $l,r$ 代表目前区间，由于题目要求数字出现次数 $cnt \leq k$，因此我们不断移动 $r$，不断更新答案，直到 $cnt >k$ 时，我们移动 $l$ 使得 $cnt$ 减少，然后继续移动 $r$ 即可。

接下来处理统计目前出现数字的种类，首先我们记 $num_x$ 为数字 $x$ 出现的个数，如果添加某个数字 $k$，如果 $num_k$ 的个数为 $0$，那么意味着 $k$ 是新出现的数字，此时 $cnt$ 加一，如果删除某个数字 $k$，如果 $num_k$ 的个数为 $1$，那么意味着数字 $k$ 是唯一一个，删除后就没有 $k$ 了，此时 $cnt$ 减一， 细节在代码中有讲述：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define ps push_back
#define sz(x) ((ll)x.size())
#define mem(f,x) memset(f,x,sizeof(f))
#define all(x) x.begin(),x.end()
#define lc id*2
#define rc id*2+1
#define V vector<ll>
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
char ch;
ll a[N],cnt[N];
int main(){
	cin>>n>>k;
	F(i,1,n) cin>>a[i];
	l=1,r=0;
	while(r<=n){//右指针不能越界
		if(ans>k){//超过限制，移动左指针
			if(cnt[a[l]]==1) ans--;//种类减少
			cnt[a[l++]]--;//cnt个数减少，左指针移动
		} 
		if(r-l+1>len){//取最大值
			len=r-l+1;
			x=l,y=r;
		}
		cnt[a[++r]]++;//移动右指针，增加出现次数
		if(cnt[a[r]]==1) ans++;//新出现数字，答案增加
	}
	cout<<x<<" "<<y;//输出
	return 0;
}

```


---

## 作者：zzy_zhouzhiyuan (赞：0)

#### 题目大意
给定一个长度为 $n$ 的序列，求出现的不同数字个数为 $k$ 的最长区间的左右端点。
#### 思路分析
使用尺取法，开一个桶维护当前出现的不同数字个数，右指针向右移时加上新出现的数的个数，左指针向右移时判断原来左指针位置的数在左指针向右移后是否还会存在。每次更新一下最大长度和答案区间左右端点。
#### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[500005],f[1000005];
int len,ll,rr;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=1,r=1,k=1;
	f[a[1]]++;//先记录第一个位置的数
	while(l<=r&&r<=n){
		while(r<=n&&k<=m){
			r++,f[a[r]]++;//右移右端点
			if(f[a[r]]==1)k++;//判断是否是新出现的数
		}
		if(len<r-l+1)len=r-l+1,ll=l,rr=r;//更新答案区间的左右端点
		f[a[l]]--;
		if(f[a[l]]==0)k--;//判断左端点
		l++;
	}
	cout<<ll<<' '<<rr-1;
}
```


---

## 作者：沉石鱼惊旋 (赞：0)

[更好的阅读体验](http://blog.cyx2009.top/archives/162/)

# 题目翻译

> 有一个长度为 $n$ 的序列 $a$，找出最长的 $[l,r]$ 使得 $a_l,a_{l+1},a_{l+2},\dots a_{r-1},a_r$ 不重复的数字个数 $\leq k$。
> $1\leq k \leq n\leq 5\times 10^5,a_i\leq 10^6$

# 题目思路

分析一下复杂度，$n$ 的级别显然告诉我们要做到 $n^2$ 以下。

观察到固定左端点 $l$，随着 $r$ 往右推，不重复数字的个数也是单调不降的。考虑双指针。

我们先让 $r$ 往右挪动，每一步检查一下当前的不重复数字个数，如果不满足题意那么挪动左端点 $l$ 把不重复的数字个数控制在 $k$ 以内。

时间复杂度 $\mathcal O(n)$。

# 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[500020];
int cnt[1000020],sum;
int ansl=1,ansr;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    int l=1,r=0;
    while(r<n)
    {
        sum+=((++cnt[a[++r]])==1);
        while(sum>k)sum-=(!(--cnt[a[l++]]));
        if(r-l+1>ansr-ansl+1)ansr=r,ansl=l;
    }
    cout<<ansl<<" "<<ansr<<endl;
    return 0;
}
```

---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF616D)

# 解法

由于这题**越往后越有可能挂掉（单调性）**。

所以，越大的 $l$ 拉出的 $r$ 一定更大。

所以我们采用双指针扫一遍。

每次固定左端点，找到对应的右端点，计算答案。

记录答案即可，不会双指针的~~出门左拐~~自己去学一下，不难理解。

时间复杂度 $\Theta(n)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000010],box[1000010];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    int l=1,r=1,L=0,R=0,cnt=1;box[a[1]]=1;//初始化
    while(r<=n){
        while(r<=n&&cnt<=k){//判断是否满足
        	++r;
            if(!box[a[r]]) ++cnt;//更新个数
            ++box[a[r]];
        }
        if(R-L<r-l) L=l,R=r;//更新
        box[a[l]]--;//删除l
        if(!box[a[l]]) --cnt;
        ++l;
    }
    cout<<L<<" "<<R-1;
    return 0;
}
```

[通过记录。](https://www.luogu.com.cn/record/108249002)

---

## 作者：koobee (赞：0)

简单的单调问题。

很明显，$10^6$ 的数据不是 $O(n^2)$ 的，考虑 $O(N)$，想到了双指针。开个 $cnt$ 数组统计没中暑的出现次数，枚举右端点，每到一个新的右端点，左端点增大，$cnt$ 保持更新，直到目前的区间内不同值的个数 $\le k$ 为止，此时答案更新。算出最大值即可。详见代码。

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N = 1e6+5;
int n, k, a[N], l=1, sum, cnt[N], ansl, ansr, ans;
int main(){
	cin>>n>>k;
	for(int i = 1; i <= n; i++) cin>>a[i];
	for(int i = 1; i <= n; i++){
		if(++cnt[a[i]] == 1) sum++;//先将新数算进去
		while(sum > k)
            if(--cnt[a[l++]] == 0) sum--;//更新左端点
		if(sum <= k && ans < i - l + 1) ans = i - l + 1, ansl = l, ansr = i;//更新答案
	}
	cout<<ansl<<" "<<ansr;
	return 0;
}

```


---

## 作者：HMZHMZHMZ (赞：0)

### 题意

给定 $ n , m $，求出最大的区间使得区间内不同元素个数 $ \leq m $。

### 思路

先考虑如何暴力。

最朴素的写法就是枚举两端，在判断是否可行即可，复杂度 $  O (n^3) $。

显然对于 $ l $，$ r $ 是单调递增的，所以我们可以枚举右端点，然后移动左端点即可。

因为左端点最多移动 $ n $ 次，所以时间复杂度 $ O ( n ) $。

### 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
using namespace std;
const int N=1e6+10;
ll ans;
int n,m,T,used[N],a[N],ml,mr;
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
int main(){
	n=read(),m=read();
	int l=1,r;
	for(register int i=1,x;i<=n;++i){
		x=read(),a[i]=x;
		r=i;//r表示当前最右端的数
		if(!used[x]) ++ans;//如果没有出现过就将计数器加1
		used[x]++;
		if(ans>m){//如果不同的数超过m个
			while(1){//右移左端点
				used[a[l]]--;
				l++;
				if(used[a[l-1]]==0) break;
			}
			ans--;
		}
		if(r-l+1>=mr-ml+1) mr=r,ml=l;//找最大区间
	}
	cout<<ml<<" "<<mr;
	return 0;
}

```

---

## 作者：wind_whisper (赞：0)

[更糟的阅读体验](https://blog.csdn.net/BUG_Creater_jie/article/details/122254012)
## $\text{Descripion}$
给定一个包含 $n$ 个整数的序列 $a$，$0\le a_i \le 10^6$，询问不重复数字个数 $\le k$ 的最长区间的左右端点。如果有多解输出任意一组。  
$n\le 5\times10^5$
## $\text{Solution}$
开一个桶维护各种数字的数量维护当前区间不重复数字个数，双指针取区间最大值即可。

## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

const int N=1e6+100;

int n,m;
int a[N],bac[N],now,ans,L,R;

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<=n;i++) a[i]=read();
  int l=1,r=0;
  while(r<n){
    now+=(++bac[a[++r]]==1);
    while(now>m) now-=(--bac[a[l++]]==0);
    if(r-l+1>ans){
      ans=r-l+1;L=l;R=r;
    }
  }
  printf("%d %d\n",L,R);
  return 0;
}
/*
 */

```

---

## 作者：揽月摘星辰 (赞：0)

第一眼看见这道题，就觉得和[P1972 HH的项链](https://www.luogu.org/problem/P1972)很像。便可以想到和HH的项链相似的做法。

首先我们可以看出问题答案具有单调性，所以显然可以二分答案。

再来思考如何判定答案可行。我们用树状数组来维护区间内的不同数字个数和，和树状数组维护前缀和相似，只是多了一步操作：

我们用a[i]来表示第i个数字的值，b[a[i]]表示a[i]上一次出现的位置。在加入第i个数时，减去第b[a[i]]个数就可以了。

每当我们二分长度，枚举终点，每当找到一段不同数个数小于k的段落，就返回真即可。



------------


------------
代码如下:
```
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
int a[1000005],sum[1000005],n,m,b[1000005],ans1,ans2;
void add(int x,int k)
{
	for(int i=x;i<=n&&i;i+=lowbit(i))
	{
		sum[i]+=k;
	}
}
int get(int x)
{
	int i,res=0;
	for(i=x;i;i-=lowbit(i))
	{
		res+=sum[i];
	}
	return res;
}
int get_sum(int l,int r)
{
	return get(r)-get(l-1);
}
bool check(int len)
{
	int res,i,j,l=0,r=0;
	for(i=1;i<=n;i++)b[a[i]]=0;
	for(i=1;i<=n;i++)sum[i]=0;
	for(i=1;i<=len;i++)
	{
		add(i,1);
		add(b[a[i]],-1);
		b[a[i]]=i;
	}
	res=get_sum(1,len);
//	for(i=1;i<=n;i++)cout<<sum[i]<<" "; cout<<endl;
//	cout<<get(len)<<" "<<get(0)<<endl;
  //  cout<<res<<endl;
	if(res<=m){
		ans1=1;ans2=len;
		return 1;
	}
//	cout<<res<<" ";
	for(i=len+1;i<=n;i++)
	{
		add(i,1);
		add(b[a[i]],-1);
		b[a[i]]=i;
		res=get_sum(i-len+1,i);
//		cout<<res<<" ";
		if(res<=m)
		{
			ans1=i-len+1;
			ans2=i;
			return 1;
		}
	}
//	cout<<endl;
	return 0;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int l=m-1,r=n;
	while(l<r)
	{
       
		int mid=l+r+1>>1;
		if(check(mid))
		{
			l=mid;
		}
		else r=mid-1;
//		cout<<endl;
//		cout<<mid<<endl;
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
```


---

