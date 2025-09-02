# Choosing flowers

## 题目描述

有 $m$ 种物品，每种物品有无限个，你可以购买 $n$ 个物品。

对于第 $i$ 种物品：

第一次买时的贡献是 $a_i$ ,接下来每购买一个的贡献都是 $b_i$。即当你买了 $x_i$ 个第 $i$ 种物品时，贡献是 $a_i+b_i \times (x_i-1)$

现在要你求出最大贡献。

## 样例 #1

### 输入

```
2
4 3
5 0
1 4
2 2

5 3
5 2
4 2
3 1```

### 输出

```
14
16```

# 题解

## 作者：__phiu (赞：7)

## Pro

$n$ 种物品选 $m$ 个，一种物品选 $k$ 个的贡献是 $a_i+(k-1)\times b_i$，求最大贡献。

## Sol

首先发现一个基本事实是：我们至多让一种物品选很多次。

证：因为如果两个物品同时选多次，那么一定是两个都被选过一次，那么用 $b_i$ 更大的去替换另一个一定不劣。

那么我们可以直接枚举被选多次的那个物品 $k$，那么考虑其它物品，如果它们被选一次，那么一定是 $a_i > b_k$，这样做是 $O(n^2)$ 的，考虑按 $a_i$ 进行排序，二分找到第一个比当前枚举位置小的，那么前面的全部选择，用前缀和简单维护就好了。

## Code

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define For(i,a,b,c) for(int i=a;i<=b;i+=c)
#define Rof(i,a,b,c) for(int i=a;i>=b;i-=c)
#define pb push_back
#define pii pair<int,int>
using namespace std;
inline int read(){
	char c=getchar();
	int x=0,f=1;
	while(c<'0' or c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0' and c<='9')
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=1e5+50;
struct node {
	int a,b;
	bool operator < (const node &p ) const {
		return a>p.a ;
	}
}a[N];
int t;
long long sum[N] ;
signed main(){
	t = read() ;
	while(t--) {
		int m = read() ;
		int n = read() ;
		for(int i=1;i<=n;i++) {
			a[i].a = read() , a[i].b = read() ;
		}
		sort(a+1,a+n+1) ;
		for(int i=1;i<=n;i++) sum[i] = sum[i-1] + a[i].a;
		long long ans = 0 ;
		for(int i=1;i<=n;i++) {
			int l = 1, r = n;
			while(l<=r) {
				int mid = l+r >>1 ;
				if(a[mid].a>=a[i].b)
					l=mid+1;
				else
					r=mid-1;
			}
			l--;//第一个小的，选的是 1 ~ l-1
			if(l>=m)
				ans=max(ans,sum[m]);//如果比它大的超过选的个数，就不选它了
			else if(l >= i ) ans = max(ans,sum[l]+1ll*(m-l)*a[i].b) ;//如果自己的第一次已经选了就不用额外选一次
			else ans = max(ans,sum[l]+a[i].a+1ll*(m-l-1)*a[i].b);//第一次没被选先选一次再累加其他贡献
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：feecle6418 (赞：7)

把每一种价格从大到小排序，扫描。

若当前是第一次买的价格，直接买。

否则，分类讨论：

- 若第一次已经买过了，则将所有剩余的全部用来买这种就行。
- 否则有两种选择：
  -  先亏一点，低价买第一次，然后剩余的全部买这种；
  -  往后买，走着瞧。假如能买到第一次，则停下来，剩余的全部买这种。

哪一种更好呢？我们不知道，所以都试试，反正总决策数是 $O(n)$ 的。具体地，我们用一个递归函数 `int f(int i,int n)`，它返回买到第 $i$ 个价格，还可以买 $n$ 枝花的最大费用，这样就可以方便地处理两种情况。

总复杂度 $O(n\log n)$，瓶颈在排序，采用基数排序可以做到 $O(n)$。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,m,f[200005],p[200005],g[200005][2];
struct Thing{
	ll id,x,tp;
	bool operator <(const Thing p) const {
		return x>p.x;
	}
}a[200005];
ll calc(int i,int n){
	if(i>2*m||n<=0)return 0;
	ll ans=0;
	if(a[i].tp==1){
		ans+=a[i].x,n--;
		if(p[a[i].id])return ans+a[p[a[i].id]].x*n;
		else {
			f[a[i].id]=1;
			return ans+calc(i+1,n);
		}
	}
	if(a[i].tp==2){
		if(f[a[i].id]){
			ans+=n*a[i].x,n=0;
			return ans;
		}
		else {
			ll tmp=ans+g[a[i].id][0]+(n-1)*g[a[i].id][1];
			p[a[i].id]=i;
			return max(tmp,ans+calc(i+1,n));
		}
	}
	//cout<<i<<' '<<a[i].id<<' '<<a[i].x<<' '<<ans<<endl;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>N>>m;
		for(int i=1;i<=m;i++){
			cin>>g[i][0]>>g[i][1];
			a[i]={i,g[i][0],1},a[i+m]={i,g[i][1],2};
		}
		sort(a+1,a+2*m+1);
		cout<<calc(1,N)<<endl;
		for(int i=1;i<=2*m;i++)f[i]=p[i]=0;
	}
} 
```

---

## 作者：QQH08 (赞：5)

~~感觉难度虚高~~

首先很显然的，我们把每一种物品拆成 $2$ 个，一个贡献是 $a_i$，一个贡献是 $b_i$。然后按贡献排序（显然尽量取贡献大的）。

我们再设 $solve(t,nn)$ 表示从下标为 $t$ 的物品往后取，还能取 $nn$ 个。在遍历的时候分 $3$ 种情况。

- 如果 $i$ 是第一次买的贡献，那很显然 $ans$ 直接加贡献, $nn$ 减一。
- 如果 $i$ 是第二次买的贡献且第一次买过了，那剩下 $nn$ 个肯定都买这个了。
- 如果 $i$ 是第二次买的贡献且第一次没有买，那么我们先算买这种的贡献，然后和不买这种的（即 $solve(i+1,nn)$）取最大值。

具体第一次是否买过了可以用数组标记。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
struct node{
    ll x;
    int y,id;
}p[N*2];
int T,m,tot;
ll n,a[N][2];
bool flag[N];
bool cmp(node a,node b){return a.x>b.x;}
ll solve(int t,int nn){
    ll res=0;
    for(int i=t;i<=tot&&nn;i++){
        if(p[i].id==0){
            res+=p[i].x;nn--;
            flag[p[i].y]=1;
        }
        else{
            if(flag[p[i].y]){
                res+=nn*p[i].x;
                break;
            }
            else{
                ll val=a[p[i].y][0]+(nn-1)*p[i].x;
                res+=max(val,solve(i+1,nn));
                break;
            }
        }
    }
    return res;
}
int main(){
    scanf("%d",&T);
    while(T--){
        tot=0;
        scanf("%lld%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%lld%lld",&a[i][0],&a[i][1]);
            flag[i]=0;
            p[++tot]=(node){a[i][0],i,0};
            p[++tot]=(node){a[i][1],i,1};
        }
        sort(p+1,p+tot+1,cmp);
        printf("%lld\n",solve(1,n));
    }
    return 0;
}
```


---

## 作者：strcmp (赞：4)

NOIP 模拟赛的 T3，赛时切了，看见没有相同的做法，故记之。

------------

**题目大意：** 给定 $m$ 种无穷多个物品，可以拿取 $n$ 次，每个物品有两个属性 $(a_i,\,b_i)$，若选取第 $i$ 个物品 $p$ 次，则贡献为 $a_i + (p - 1) \times b_i$，求最大的总贡献。

------------

注意到，选取次数大于 $1$ 的物品只可能有一种。否则，考虑两个选取次数大于 $1$ 的物品 $(a_i,\,b_i)$，$(a_j,\,b_j)$。若前者选取 $k$ 次，后者选取 $p$ 次。考虑 $b_i \le b_j$，则选取 $1$ 次 $(a_i,\,b_i)$，$k + p - 1$ 次 $(a_j,\,b_j)$，答案一定不劣。$b_i > b_j$ 同理。

枚举每一种物品，考虑当前物品 $(a_i,\,b_i)$ 选择 $k$ 次之后的贡献。因为选取次数大于 $1$ 的物品只可能有一种，所以剩下的都是 $a_i$ 的贡献。

根据贪心的想法，我们一定是选取 $k$ 次 $b_i$ 之后尽量选择最大的 $a_i$ 集合。于是将物品按 $a_i$ 降序排序。

设 $s_i$ 为 $\sum\limits_{j = 1}^{i} a_i$，若 $i > m$，则钦定 $a_i \leftarrow 0$。

考虑 $f(x,\,k)$ 为 $(a_x,\,b_x)$ 选取 $k$ 次之后的总贡献。表示分两种情况：

- $n - k < i$，则贡献为 $b_x \times (k - 1) + s_{n - k} + a_x$。

- $n - k \ge i$，则贡献为 $b_x \times (k - 1) + s_{n - k + 1}$。

注意到，移动 $k$，则每次增加的贡献为 $b_k - a_k$，而分界点上的贡献相同。所以 $f(x,\,k)$ 对于 $k$ 是一个斜率单调不增的凸函数，我们求的在 $x$ 上的最大答案是这个凸函数的极值。

注意到，我们可以在 $\Theta(1)$ 的时间内求出 $f(x,\,k)$。所以求这个凸函数的极值我们可以直接使用三分法解决。

时间复杂度 $\Theta(m \log n)$，可以通过。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 2e5 + 10;
const ll mod = 1000000007LL;
pll a[maxn]; int t; ll n, m; ll sum[maxn];
ll solve(int now, ll p) {
    //b，选 p 个得到的答案
    ll w = n - p; ll pre = 0, b = a[now].y;
    if (w > m) w = m;
    //连带着 a[now] 选了 p 个
    if (w >= now) { pre = sum[min(w + 1, m)] - a[now].x; }
    else pre = sum[w];
    return b * (p - 1) + pre + a[now].x;
}
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        for (int i = 1; i <= m; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
        sort(a + 1, a + m + 1, greater<pll>());
        for (int i = 1; i <= m + 1; i++) sum[i] = sum[i - 1] + a[i].x; ll ans = 0;
        for (int i = 1; i <= m; i++) {
            ll l = 1, r = n;
            while (l + 1 < r) {
                ll mid = l + r >> 1;
                ll a1 = solve(i, mid - 1), a2 = solve(i, mid + 1);
                if (a1 >= a2) ans = max(ans, a1), r = mid;
                else ans = max(ans, a2), l = mid;
            }
            ans = max(ans, solve(i, l));
            ans = max(ans, solve(i, r));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```


---

## 作者：This_Rrhar (赞：2)

引理：至多存在一种物品会被选超过一次。

证：设最优解存在两件物品 $\{a_i,b_i\}$ 和 $\{a_j,b_j\}$ 被选超过一次且 $b_i\le b_j$，那么显然放弃 $b_i$ 选择 $b_j$ 不劣于最优解。超过两件同理。$\blacksquare$

则可以将物品按 $a$ 从大到小排序，枚举第 $i$ 件物品被选超过一次，再二分求出最大的 $j$ 使得 $a_j>b_i$。将 $1\sim j$ 各选一次，剩余的选择次数全部用于物品 $i$。对 $n$ 次枚举的答案取 $\max$ 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
#define _r return*this
#define _o &operator
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		char getchar(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		input _o>>(char&num){do num=getchar();while(num==' '||num=='\n'||num=='\r'||num=='\t');_r;}
		template<typename T>input _o>>(T&x)
		{
			char c=getchar();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=getchar();
			while(isdigit(c))x=(x*10)+(c^48),c=getchar();
			x*=f;_r;
		}
		input(){}
	}in;
	long long read(){long long x;return in>>x,x;}
	struct output
	{
		void putchar(char num){*pp++=num;if(pp-pb==_S)fl();}
		output _o<<(char num){putchar(num);_r;}
		template<typename T>output _o<<(T x)
		{
			if(!x){putchar(48);_r;}
			if(x<0)putchar('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)putchar(s[t--]+48);
			_r;
		}
		output _o<<(const char*s2){int num=0;while(s2[num])putchar(s2[num++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
}
using IO::in;
using IO::out;
using IO::read;
using ll=long long;

#define M 100001ll

ll T,n,m;

struct node
{
	ll x,y;
	bool operator<(const node&B)const{return x>B.x;}
}a[M];

ll s[M];

ll l,r,mid;

ll ans;

int main()
{
	in>>T;
	while(T--)
	{
		in>>n>>m,ans=0;
		for(int i=1;i<=m;i++)in>>a[i].x>>a[i].y;
		sort(a+1,a+1+m);
		for(int i=1;i<=m;i++)s[i]=s[i-1]+a[i].x;
		for(int i=1;i<=m;i++)
		{
			l=1,r=m;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(a[mid].x>=a[i].y)l=mid+1;
				else r=mid-1;
			}
			l--;
			if(l>=n)ans=max(ans,s[n]);
			else if(l>=i)ans=max(ans,s[l]+a[i].y*(n-l));
			else ans=max(ans,s[l]+a[i].x+a[i].y*(n-l-1));
		}
		out<<ans<<"\n";
	}
}
```

---

## 作者：Sktic (赞：2)

二分水题。


可以推出，对于一个最优方案，只有不选 $b_i$ 与选一种 $b_i$ 两个选择，又设 $a_j>b_i$ ,那么 $a_j$ 也必定要选。

当使用以上方法复杂度为 $O(n^2)$，显然会超时，于是我们考虑二分优化。
将 $a_i$ 数组进行升序排列，然后二分，总复杂度为 $O(n log n)$

温馨提示：十年OI一场空，不开long long见祖宗

这里只放部分代码，完整代码留给读者思考。

$Code$ :

```C++
int q=lower_bound(a+1,a+m+1,ud(a[i].y))-(a+1);
if(q<i)
	if(q<(n-1))
		ans=max(ans,v[q]+a[i].x+((long long)(n-(q+1))*a[i].y));
else
	if(q<n)
		ans=max(ans,v[q]+((long long)(n-q)*a[i].y));
```

感谢阅读！


---

## 作者：wmy_goes_to_thu (赞：2)

这是一道二分的水题。

首先，我们证明一个事：如果买的个数一定，那么两个都买 $\geq 2$ 个不如就一个买 $\geq 2$ 个好。如果我们设 $b_i \geq b_j$，那么：

都多买的价值是：$(a_i+(x_i-1) \times b_i)+(a_j+(x_j-1) \times b_j)$

就多买一个的价值是：$(a_i+(x_i+x_j-2) \times b_i)+a_j$

又因为 $b_i \geq b_j$，所以就多买一个的方案更优。

那么我们就可以枚举多买的是哪个，这里设为 $i$，然后处理剩下的：

其实从剩下的挑出一个买相当于总价值要 $a_j-b_i$，显然只有 $a_j \gt b_i$ 的情况才会更优，所以二分 $a$ 即可。当然有一堆特判，可以参考一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct apple
{
	int a,b;
	bool operator<(const apple &other)const
	{
		return a<other.a;
	}
}f[100005];
long long z[100005],l[100005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++)scanf("%d%d",&f[i].a,&f[i].b);
		sort(f+1,f+m+1);
		z[m+1]=0;
		for(int i=m;i>=1;i--)z[i]=z[i+1]+(l[i]=f[i].a);
		long long ans=0;
		for(int i=1;i<=m;i++)
		{
			int wz=upper_bound(l+1,l+m+1,f[i].b)-l;
			int gs=m-wz+1;
			if(f[i].a>f[i].b)gs--;
			if(n<=gs)gs=n-1;
			long long anss=f[i].a+1ll*(n-gs-1)*f[i].b;
			wz=m-gs+1;
			int flag=0;
			if(i>=wz)wz--,flag=1;
			anss+=z[wz]-flag*f[i].a;
			ans=max(ans,anss);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：RyexAwl (赞：1)

首先有个显然的结论：

在最优解中，至多只有一种物品会被选多个。

因为如果当有多种物品被选多个时，用$b$值最大的去替换$b$值较小的物品，一定更优。

那么就可以得出一种朴素的做法：

枚举选多个的物品，计算出当前物品选多个时的最大收益。

对于每种物品，依次枚举选$2,3,4,5...n$个，其选$i$个物品的最大值，显然是从除了当前物品的物品组里选出前$n-i$大的物品收益加上选$i$个物品的收益。

反着思考：

将物品按$a$值递减排序得到序列$c[]$。我们考虑从$n$往前枚举，考虑选$i$个是否比选$i+1$个要更优，选$i$个比选$i+1$个更优当且仅当$c[i]>b,c[i]\ne a$，即依次用$c[i]$替换$b$。

复杂度$O(m^2)$

但是因为我们按$a$值递减排序，所以物品组的价值是单调的。

考虑倍增，我们可以发现我们可以直接倍增或二分到大于$b$的最小值的位置。


特判以下其前缀是否包括$a$即可

复杂度$O(m\log m)$

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

namespace wxy{
    const int N = 1e5 + 5;
    typedef long long ll;
    ll b[N],c[N],s[N];
    int pp[N];
    std::pair<ll,int> a[N];
    inline void main(){
        int t;
        std::cin >> t;
        while (t--){
            int n,m;
            scanf("%d%d",&n,&m);
            for (int i = 1; i <= m; i++){
                scanf("%lld%lld",&a[i].first,&b[i]);
                c[i] = a[i].first;
                a[i].second = i;
            } 
            std::sort(a + 1,a + 1 + m);
            std::reverse(a + 1,a + 1 + m);
            for (int i = 1; i <= m; i++) pp[a[i].second] = i;
            ll ans = 0;
            s[0] = 0;
            for (int i = 1; i <= m; i++){
                s[i] = s[i - 1] + a[i].first;
                if (i <= n) ans += a[i].first;
            }
            int p = std::min(m,n-1);
            int k = 0;
            for (;(1 << k) <= p; k++);
            k++;
            for (int i = 1; i <= m; i++){
                ll pos = c[i] + b[i] * (n - 1);
                int loc = 0;
                for (int j = k; j >= 0; j--){
                    if (((loc + (1 << j)) <= p) && a[loc + (1 << j)].first > b[i]) loc += 1 << j;
                }
                if (loc >= pp[i]){
                    pos = pos - c[i] + s[loc];
                    loc--;
                    pos -= loc * b[i];
                }else{
                    pos = pos - loc * b[i] + s[loc];
                }
                ans = std::max(pos,ans);
            }
            printf("%lld\n",ans);
        }
    }
}signed main(){wxy::main();return 0;}
```




---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1379C)

---

贪心题，很容易 duang 出来，最优方案中要么不选 $\operatorname b$，要么只选一种 $\operatorname b$，

所以我们可以得到一个简单的思想，二分比当前这个 $\operatorname b$，大的 $\operatorname a$，选这些 $\operatorname a$，

再看还可以选吗，可以选就选剩下的选 $b$。

但有许多特判，因为可能当前这个 $\operatorname a$已经选了，所以要特判，还要开 $\text{long long}$。


```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 1e5 + 5;
int n,m,b[maxn],sum[maxn];
int ans,times;

struct node {
	int x,y;
}a[maxn];

bool cmp(node x,node y) {
	return x.x < y.x;
}

signed main () {
	read(times);
	while (times --) {
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		memset(sum,0,sizeof sum);
		read(n);read(m);
		for (int i = 1 ; i <= m ; ++ i) {
			read(a[i].x);read(a[i].y);
		}
		sort(a + 1,a + 1 + m,cmp);
		sum[m + 1] = 0;
		for (int i = m ; i >= 1 ; -- i) b[i] = a[i].x,sum[i] = sum[i + 1] + b[i];
		ans = sum[max(m - n + 1,0ll)];
		for (int i = 1 ; i <= m ; ++ i) {
			int k = lower_bound(b + 1,b + 1 + m,a[i].y) - b;
			int p = m - k + 1,q = n;
			if (p >= q) ans = max(ans,sum[m - n + 1]);
			else {
				int flag = 0;
				if (i < k) flag = 1;
				if (flag) ans = max(ans,(q - p - 1) * a[i].y + a[i].x + sum[k]);
				else ans = max(ans,(q - p) * a[i].y + sum[k]);
			}
		}
		print(ans),putchar('\n');
	}
	return 0;
}
```

---

## 作者：RockyYue (赞：0)

### 1379C

$m$ 种物品，第 $i$ 种第一次买时价值为 $a_i$，后面可以买无限次，每次价值 $b_i$，所有物品共可以买 $n$ 次，求最大价值，$O(m\log m)$。

### Sol

- 不妨换一种方式思考：$2n$ 种物品，其中 $n$ 种一件，$n$ 中无穷件，这两组物品一一对应，选了第一组的物品才有权限选第二组的对应物品。
- 若现存物品中价值最大的在第一组中或第二组且已经解锁，必选；否则看是否选择其对应的第一组物品后选择。
- 分析后续选择，发现若最大价值在第二组则以后只会选择这一种。在此之前，第二组中一定没有解锁过更大，也没有必要选择更小，故选择的只有更大的第一组，第二组中枚举主要选择的这种物品，二分得出更大的第一组价值和即个数即可。

---

## 作者：UncleSam_Died (赞：0)

### 解题思路

不是那么显然的，当只选一种 $b_i$ 或全选 $a_i$ 时最优。那么我们可以先对 $a_i$ 从大到小排序，枚举每一个 $b_i$，然后二分找到第一个大于等于 $b_i$ 的 $a_j$，判断 $a_1\sim a_j$ 中是否包含 $a_i$，如果包含，当前的答案为 $\displaystyle \left(\sum_{k=1}^{j} a_k\right)+b_i\times (n-j)$，否则当前答案为 $\displaystyle \left(\sum_{k=1}^{j} a_k\right)+a_i+b_i\times (n-j-1)$，最后对于所有答案取最大值即可。

对于只选一种 $b_i$ 最优证明如下：
- 若当前 $b_i$ 最大，若 $\exists a_j>b_i$，那么 $a_j$ 一定位于前缀和中，此时若选择 $b_i$ 且选择 $b_j$，那么可以看作用 $b_j$ 替换了一个 $b_i$，又有 $b_i>b_j$，那么答案一定小于只选一种的答案；若 $a_j<b_i$，那么一定不会选择用更小的 $a_j$ 替换更大的 $b_i$；
- 若当前 $b_i$ 不为最大，若 $\exists a_j>b_i$，在 $b_j$ 大于 $b_i$ 时，全选 $b_i$ 更优，在 $b_j<b_i$ 时，同上；若 $a_j<b_i$，那么若 $b_j>b_i$，则答案一定会在全选 $b_j$ 或全选 $b_i$ 中取，证明如上，若 $b_j<b_i$，则一定不优；
- 有 $a_j=b_i$ 或 $b_j=b_i$ 情况均同上。

综上，只选一种 $b_i$ 或全选 $a_i$ 为最优决策，因此可以枚举找到答案。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#define N 100005
#define ll long long
int n,m;
struct Flower{
    int a,b;
}a[N];ll sum[N];
inline bool cmp(Flower x,Flower y){
    if(x.a!=y.a)
        return x.a>y.a;
    return x.b>y.b;
}
inline int Upper(int x){
    int l=1,r=m,res=0,mid;
    while(l<=r){
        mid=(l+r+1)>>1;
        if(a[mid].a>=x){
            res=mid;
            l=mid+1;
        }else r=mid-1;
    }return res;
}
inline void work(){
    scanf("%d%d",&n,&m);int k=m;
    int maxt=-1, maxi=0;ll ans=0;
    for(register int i=1;i<=m;++i){
        scanf("%d",&a[i].a);
        scanf("%d",&a[i].b);
        if(a[i].b>maxt) maxt=a[i].b;
    }std::sort(a+1,a+m+1,cmp);
    for(register int i=1;i<=m;++i)
        sum[i]=sum[i-1]+a[i].a;
    if(n<=m) ans=sum[n];
    else ans=sum[m]+1ll*(n-m)*maxt;
    for(register int i=1;i<=m;++i){
        int x=Upper(a[i].b);
        if(x>n) continue;
        ll now=sum[x],res;
        if(x>=i) res=1ll*a[i].b*(n-x);
        else res=a[i].a+1ll*(n-1-x)*a[i].b;
        if(now+res>ans) ans=now+res;
    }printf("%lld\n",ans);
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

