# New Year and Ascent Sequence

## 题目描述

### 题意简述

给定 $n$ 个整数序列 $s_1,s_2,...,s_n$。

我们可以把两个长分别为 $lx$ 和 $ly$ 的序列 $s_a,s_b$ 拼接起来，拼接后的序列是 $[s_{a,1},s_{a,2},...,s_{a,lx},s_{b,1},s_{b,2},...,s_{b,ly}]$。

容易发现，如果在 $n$ 个序列中任选两个拼起来，一共有 $n^2$ 种拼法。

现在问你在 $n^2$ 种拼法拼成的序列中有多少个拼成的长度为 $l$ 的序列 $a$，使得存在 $(i,j)$ 满足 $1\leq i<j \leq l$ 且 $a_i<a_j$ 。

## 样例 #1

### 输入

```
5
1 1
1 1
1 2
1 4
1 3```

### 输出

```
9```

## 样例 #2

### 输入

```
3
4 2 0 2 0
6 9 9 8 8 7 7
1 6```

### 输出

```
7```

## 样例 #3

### 输入

```
10
3 62 24 39
1 17
1 99
1 60
1 64
1 30
2 79 29
2 20 73
2 85 37
1 100```

### 输出

```
72```

# 题解

## 作者：nalemy (赞：6)

### CF1284B题解

~~蒟蒻的第二篇题解~~

我们考虑以下几点：

1. 如果一个数列**本身就符合要求**，那么它跟谁拼起来都**符合要求**，我们就不用考虑它（后面几点默认不是这种情况）
2. 两个数列$a,b$符合要求的**充要条件**是$a_{min}<b_{max}$，所以我们对于一个数列$a$只用存下$a_{min},a_{max}$即可
3. 所以对于一个数列$a$，**不能接在**$a$后面的个数实际上就是满足$a_{min}\ge b_{max}$的$b$的个数（这里我们考虑**不能满足**$a$的数列个数是因为有第一点~~这样恶心的存在~~，如果考虑**满足**$a$的数列个数的话不好计算）

顺便说一声： 

## STL大法好！

我们可以用`upper_bound`来计算数列里面小于某个定值的数（因为它返回的是第一个大于它的数的位置，把起始位置一减就是小于等于它的个数了）

下面给AC代码：

```C++
#include<algorithm>
#include<iostream>
#include<climits>
#define Inf INT_MAX
#define N 100000
using namespace std;
typedef long long ll;

int mx[N], mn[N];
int main() {
    bool flg;
    ll n, l = 0, cnt = 0; cin >> n;
    for (int i=0, m, x; i<n; i++) {
        cin >> m, mx[l] = 0, mn[l] = Inf, flg = false;
        for (int j=0; j<m; j++) {
            cin >> x, mn[l] = min(mn[l], x), mx[l] = max(mx[l], x);
            if (x > mn[l]) flg = true;  // 验证是不是第一种情况
        }
        if (!flg) l++;  // 如果是第一种情况就不记录它了，否则记录上
    }
    sort(mx, mx+l);  // 排完序upper_bound才能用
    for (int i=0; i<l; i++)
        cnt += upper_bound(mx, mx+l, mn[i]) - mx;  // 加上不能满足数列s_i的个数
    cout << n * n - cnt;  // 用总方案数减去不可行的方案数（容斥原理）
    return 0;
}
```

---

## 作者：Mint_Flipped (赞：3)

### **题意：为两个序列经过拼凑组合后，只要存在前后有一对元素递增关系，问有多少对这样的序列。**

### **思路：我是反向来做的，就是先从所给序列中找出非严格递减序列，两两组合，继续找非严格递减序列，因为只要不是非严格递减序列，就存在前后有一对元素递增关系。利用结构记录非严格递减序列的开头，结尾，排序后利用二分两两组合（两个for循环会超时），找非严格递减序列，记录个数sum，最后答案就是n方-sum。**

### **代码如下：**
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
    int s,e;
} num[100005];
bool cmp(node a,node b)
{
    return a.s>b.s;
}
int bf(int i,int j,int k)
{
    int l=i,r=j;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(num[k].e<num[mid].s)
            l=mid+1;
        else
            r=mid-1;
    }
    return l;
}
int main()
{
    int ans,id=1,st,ed,te,flag,temp;
    ll n,sum=0;
    scanf("%lld",&n);
    for(int i=1; i<=n; ++i)
    {
        flag=0;
        scanf("%d",&ans);
        scanf("%d",&st);
        temp=st;
        if(ans!=1)
        {
            for(int j=2; j<=ans-1; ++j)
            {
                scanf("%d",&te);
                if(flag==0&&te>st)
                    flag=1;
                st=te;
            }
            scanf("%d",&ed);
            if(!flag)
            {
                if(st>=ed)
                    num[id].s=temp,num[id++].e=ed;
            }
        }
        else
            num[id].s=st,num[id++].e=st;
    }
    sort(num+1,num+id,cmp);
    for(int i=1; i<id; ++i)
        sum+=id-bf(1,id-1,i);
    cout<<n*n-sum<<endl;
    return 0;
}
```



---

## 作者：gyh20 (赞：2)

如果一个序列符合要求，那么将它和任何一个其他的序列放在一起都满足要求。

如果序列$a$，$b$都不符合要求，那么$a+b$符合要求当且仅当$max(b[j])>min(a[i])$

可以用前缀和/树状数组等记录下每个不符合要求的序列的最小值。

最后将每个序列扫一遍，再统计答案即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
long long n,m,l[100002],a[100002],v[100002],num[1000002],mn[100002],mx[100002],pp;
long long ans;
int main(){
n=pp=read();
memset(mn,127,sizeof(mn));
for(re int i=1;i<=n;++i){
	l[i]=read();
	for(re int j=1;j<=l[i];++j){
		a[j]=read();
		if(a[j]>mx[i])mx[i]=a[j];
		if(a[j]<mn[i])mn[i]=a[j];
		if(j!=1&&a[j]>a[j-1]){
			v[i]=1;
		}
	}
	if(v[i])ans+=pp+pp-1,--pp;
	else ++num[mn[i]];
}
for(re int i=1;i<=1000000;++i)num[i]+=num[i-1];
for(re int i=1;i<=n;++i){
	if(!v[i]){
//		cout<<i<<" "<<num[mx[i]-1]<<endl;
		ans+=num[mx[i]-1];
	}
}
printf("%lld",ans);
}

```


---

## 作者：run_away (赞：1)

## 题意

给 $n$ 个序列，在其中选择可以相同的两个首尾相连，可以得到 $n^2$ 种方案。

问其中多少至少有一个顺序对。

## 分析

考虑用总数减去不合法的数量，即求不含有顺序对的数量。

这种序列就是单调不增序列，要求两个子序列也是单调不增，这在输入时就可以 $O(len)$ 判断。

因为大序列单调不增，那么就要求前面小序列的最后一项大于等于后面小序列的第一项。

我们只需要根据一个小序列的最后一项来找比它还小的就可以了。

用值域线段树维护，把每个不增小序列的第一项放进去就可以了。

复杂度 $O(n\log V)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
#define usetime() printf("time: %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
    const ll maxn=1e6+5,mod=998244353;
	ll n,lst[maxn],len[maxn];
	vector<ll>a;
	bool vis[maxn];
	struct node{
		ll l,r,val;
	}t[maxn<<2];
	#define ls (x<<1)
	#define rs (x<<1|1)
	#define mid ((t[x].l+t[x].r)>>1)
	inline void pushup(ll x){t[x].val=t[ls].val+t[rs].val;}
	inline void build(ll x,ll l,ll r){
		t[x].l=l,t[x].r=r;
		if(l==r)return;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	inline void update(ll x,ll pos,ll k){
		if(t[x].l==t[x].r)return t[x].val+=k,void();
		if(pos<=mid)update(ls,pos,k);
		else update(rs,pos,k);
		pushup(x);
	}
	inline ll query(ll x,ll l,ll r){
		if(l<=t[x].l&&t[x].r<=r)return t[x].val;
		ll res=0;
		if(l<=mid)res+=query(ls,l,r);
		if(r>mid)res+=query(rs,l,r);
		return res;
	}
    inline void mian(){
		n=read();
		build(1,0,1e6);
		for(ll i=1;i<=n;++i){
			len[i]=read(),a.clear();
			for(ll j=1;j<=len[i];++j){
				a.push_back(read());
			}lst[i]=a.back();
			vis[i]=1;
			for(ll j=1;j<len[i];++j){
				if(a[j-1]<a[j])vis[i]=0;
			}
			if(!vis[i])continue;
			update(1,a[0],1);
		}
		ll ans=n*n;
		for(ll i=1;i<=n;++i){
			if(vis[i]){
				ans-=query(1,0,lst[i]);
			}
		}write(ans);
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ll t=1;
    while(t--)tobe::mian();
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：liuyz11 (赞：1)

# 题解 CF1284B 【New Year and Ascent Sequence】

[本场比赛的题解](https://www.cnblogs.com/nblyz2003/p/12151883.html)
题目大意：给你n个序列，每次取任意两个序列（可以取同一个，并且交换前后顺序算不同种）接起来（比如说‘11’和‘22’就是‘1122’）。问这n2个接成序列中共有多少个序列中存在顺序对。

不难看出，如果一个序列中本身存在顺序对，接成的序列也肯定存在顺序对。

判断方法

if(x > minx) flag = 1;

 将它们找出来后直接统计入答案，套上一个小学学的容斥原理

ans = 1ll * 2 * cnt1 * n - 1ll * cnt1 * cnt1;

 然后主要问题就是这些剩下的没有顺序对的序列。

很显然凡是最大值比这个序列最小值大的，就可以和这个序列接起来。

将最大值排序后二分一下最小的最大值就好。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 100005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

vi a, b;

int main(){
	int n;
	scanf("%d", &n);
	int cnt1 = 0, cnt2 = 0;
	rep(i, 1, n){
		int k;
		scanf("%d", &k);
		int minx = INF, maxx = -INF;
		bool flag = 0;
		rep(j, 1, k){
			int x;
			scanf("%d", &x);
			if(x > minx) flag = 1;
			minx = min(minx, x);
			maxx = max(maxx, x);
		}
		if(flag) cnt1++;
		else{
			cnt2++;
			a.pb(minx);
			b.pb(maxx);
		}
	}	
	sort(all(b));
	ll ans = 1ll * 2 * cnt1 * n - 1ll * cnt1 * cnt1;
	rep(i, 0, SZ(b) - 1){
		ans += cnt2 - (upper_bound(all(b), a[i]) - b.begin());
	}
	printf("%I64d\n", ans);
    return 0;
}

```


---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1284B)

反面考虑。

题目对拼起来合法的序列是对于有一对 $(i,j)$ 满足 $a_i<a_j$，显然反过来就是对于全部的 $(i,j)$，都有 $a_i \ge a_j$，那就是，单调不升的序列，我们考虑统计这样的序列。

首先我们必须满足要拼的两个序列单调不升，然后根据 $p$ 序列的末尾和 $q$ 序列的开头来决定拼起来（默认 $p$ 在前。）的是否合法。

观察到值域不大，所以我们直接考虑枚举 $p$ 序列的末尾 $x$，然后我们所有的 $q$ 序列开头满足 $\le x$ 即可，这个我们直接对原始的单调不升的序列进行预处理即可。（就，前缀和）。

然后答案就是 $n^2$ 减去我们统计的（拼出来的单调不升的序列个数）。


时间复杂度是 $O(V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
vector<int> g[N];
int t[N],n,len[N];
bool Flag[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>len[i];
		bool f=false;
		for(int j=1,x;j<=len[i];j++){
			cin>>x,g[i].push_back(x); if(j>1&&g[i][j-1]>g[i][j-2])	f=true;
		}
		if(f==false)	Flag[i]=true,t[g[i][0]]++;
	} 
	for(int i=1;i<=1e6;i++)	t[i]+=t[i-1];
	int ans=n*n;
	for(int i=1;i<=n;i++){
		if(Flag[i]==false)	continue;
		bool f=true;
		ans-=t[g[i][len[i]-1]];
	}
	cout<<ans<<endl;
	return 0;
}

```

---

