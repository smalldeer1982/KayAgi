# Nastya and a Game

## 题目描述

$Nastya$  在生日那天收到了一个大小为  $n$  的数组，她想知道数组存放的序列中，有多少的子串满足其中所有的数的乘积是数的总和的  $k$  倍。请帮她得到答案。

## 说明/提示

- 第  $1$  组样例的解释：

只有  $1$  子串  $\{1\}$ ，因为  $\frac{1}{1}=k=1$ ，所以它恰好是符合条件的。

- 第  $2$  组样例的解释：

 $\{6,\ 3\}$  中所有数的乘积是  $18$ ，总和是  $9$ ，因为  $\frac{18}{9}=k=2$ ，所以它符合条件。

 $\{3,\ 8,\ 1\}$ 中所有数的乘积是  $24$ ，总和是  $12$ ，因为  $\frac{24}{12} = k = 2$ ，所以它也符合条件。

综上所述，共有  $2$  个子串符合条件。

感谢@Sooke 提供翻译以及@ZqlwMatt 修正

## 样例 #1

### 输入

```
1 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
6 3 8 1
```

### 输出

```
2
```

# 题解

## 作者：zhlzt (赞：4)

### 题解

经验告诉我们，涉及到序列乘积的题往往可以从数据范围入手。

我们发现一个子串的和最多为 $2\times 10^5\times 10^8 = 2\times 10^{13}$，易知满足条件的子串的积最多为 $2\times 10^{13}\times 10^5=2\times 10^{18}<2^{61}$，故该字串含有不超过 $60$ 个大于 $1$ 的数。

我们可以暴力枚举子串左右端点，积大于 $2\times 10^{18}$ 直接退出循环。以及右端点遍历一段连续的 $1$ 时把其当成一个点，不过需要注意此时积不变但和会变。

显然对于一个左端点最多会遍历到 $2\times 60=120$ 个右端点，故复杂度为 $O(nv)$，其中 $v$ 表示一个左端点遍历到的右端点数的期望值，极限数据下 $v$ 能取到将近 $120$。

### 代码实现

代码中 $suc_{i}$ 表示 $i$ 之后第一个大于 $1$ 的数，不包括 $i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxv=2e18;
const int maxn=2e5+10;
ll a[maxn],pre[maxn];
int suc[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n;ll k;cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i>=1;i--){
		if(a[i+1]!=1) suc[i]=i+1;
		else suc[i]=suc[i+1];
	}
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]+a[i];
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ll mul=1ll,sum;
		for(int j=i;j<=n;j++){
			if(a[j]>maxv/mul) break;
			mul*=a[j];
			sum=k*(pre[j]-pre[i-1]);
			if(mul==sum) ans++;
			if(a[j]==1ll and sum<mul and mul%k==0){
				ans+=(sum+(suc[j]-j-1)*k>=mul);
			}
			if(a[j]==1ll) j=suc[j]-1;
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：4)

最多只会跳log次，中间是一大段1，暴力统计答案。

```cpp
#include<cstdio>
using namespace std;
const int N=2e5+5;
typedef long long ll;
const ll inf=(ll)1e19;
int n,k,a[N],las[N];
inline void init(){
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		las[i]=(a[i-1]!=1)?i-1:las[i-1];
	}
}
ll ans;
inline void solve(){
	for (int i=1;i<=n;i++){
		ll sum,mul; sum=mul=a[i];
		ans+=(k==1);
		for (ll pre=i,now=las[i];;pre=now,now=las[now]){
			ll tmp=mul-sum*(ll)k;
			if (tmp>0&&tmp%k==0&&tmp/k<pre-now) ans++;
			if (!now||inf/a[now]<mul) break;
			mul*=(ll)a[now],sum+=(ll)a[now]+pre-now-1;
			ans+=(mul==sum*(ll)k);
		}
	}
	printf("%I64d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：Patrickpwq (赞：3)

子序列肯定不可能是无限长的

由于amax=1e8 nmax=2e5 kmax=1e5

则summax=1e82e51e5=2e18 而longlong刚好能hold住

那也就是说一个子序列里面非1的个数不超过64个（longlong范围是2^64）

那我们可以把连续的1缩成一坨 然后枚举每个点 暴力地往后找

具体的实现：记le[i]记录每个数左边第一个不是1的数在哪儿 然后用类似链表的方法遍历 如果乘积马上就要爆longlong了 就马上break

这样复杂度O(64*n)

```cpp
#include<bits/stdc++.h>
#define N 200005
#define ll long long
using namespace std;
template<class T>
inline void read(T &x)
{
    x=0;
    static char ch=getchar();
    while(ch<'0'||ch>'9')   ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
}
int n,le[N],ans;
ll k,a[N];
inline bool Overflow(ll mul,ll x)
{
    if(mul>LLONG_MAX/x) return true;
    return false;
}
int main()
{
    read(n);    read(k);
    for(int i=1;i<=n;i++)   read(a[i]);
    for(int i=1;i<=n;i++)
    {
        if(a[i-1]!=1) le[i]=i-1;
        else le[i]=le[i-1]; //记录每个数左边第一个不是1的数在哪儿 
    }
    for(int i=1;i<=n;i++)
    {
        ll sum=a[i],mul=a[i];
        if(mul==sum*k)  ans++;
        for(int pre=i,now=le[i];;pre=now,now=le[now])
        {
            ll del=mul-sum*k;
            if(del>0&&del%k==0&&del/k<pre-now)  ans++;      //判断跳过的这段1 能否更新答案 
            if(!now||Overflow(mul,a[now]))  break;  
            mul*=a[now]; sum+=a[now]+(pre-now-1);
            if(mul==sum*k)  ans++;  
        }
    }
    cout<<ans<<endl;;
    return 0; 
}
```

---

## 作者：A2_Zenith (赞：0)

VP 做到这个题，场切了后就赶快来写了篇题解。

一句话题意：给定长 $n$ 序列 $a$ 以及正整数 $k$，求有多少个子段满足子段之积比子段之和为 $k$。

不妨设 $S(i,j)=\sum\limits_{i=l}^ra_i,P(i,j)=\prod\limits_{i=l}^ra_i$。

首先，注意到整个序列的和不超过 $n \times \max a_i \leq 2 \times 10^{13}$，所以符合条件的 $s \leq n \times \max a_i \times k \leq 2 \times 10^{18}$。这说明你所选的子段所包含的非一元素至多只有大概 $60$ 个左右。

那么，你不妨设 $nxt_i$ 为 $[i+1,n]$ 中最靠左的非 $1$ 元素并枚举子段的左端点 $l$ 。于是从 $l$ 开始的前缀积便被 $nxt_i$ 划成了若干段：$[l,nxt_l-1]$，$[nxt_l,nxt_{nxt_l}-1]\cdots$，你最多只会跳 $60$ 个段，原因上面已经证明过了。

观察到每个段都满足这样一个性质：开头是一个任意正整数，后面是一连串的 $1$。

所以，对于一个按照前缀积划出来的段 $[i,j]$，$S(i,p)(p \in [i,j])$ 是可以取到任意的 $[S(l,i),S(l,j)]$ 间的正整数的。

那么，只要这个段满足 $S(l,i)\leq \frac{P(l,i)}{k} \leq S(l,j)$ (前提是 $k|P(l,i)$ )，那么在这个区间内就一定存在 $p$ 使得 $S(l,p)=\frac{P(l,i)}{k} = \frac{P(l,p)}{k}$。容易证明在同一个段内满足题目性质的右端点唯一。

所以这个题就做完了，复杂度是 $n \log P$。

码风较为丑陋，不喜勿喷捏。


```cpp
#include<bits/stdc++.h>
#define int long long
#define doub long double
#define PDI pair<doub,int>
#define fir first
#define sec second
#define mp make_pair
using namespace std;
const doub eps=1e-18;
const int maxn=5e5+7;
const int mod=1e9+7;

const int B=2e18;
int n,k;
int a[maxn];
int sum[maxn];
int nxt[maxn];//the subscript of the next element which is not 1
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
    int lst=n+1;
    for(int i=n;i>=1;i--){
        nxt[i]=lst;
        if(a[i]>1)lst=i;
    }
    a[n+1]=B+1;
    int ans=0;
    for(int i=1;i<=n;i++){
        int P=1,S=0;
        int j=i;
        while(j<=n){
            P*=a[j],S=sum[j]-sum[i-1];
            int c=nxt[j];
            if(P%k==0){
                if(S<=P/k&&P/k<=S+sum[c-1]-sum[j])ans++;
            }
            if(P>=B/a[c])break;
            j=c;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：nb_jzy (赞：0)

# 题意
让你求出满足一下条件的子串个数：

$$
\sum_{i=1}^{n}\sum_{j=i}^{n}[\frac{ \prod_{z=i}^{j} }{\sum_{z=i}^{j}}=k]
$$

# 分析
看到这个式子，我们可以感觉到乘法“乘多了之后”值会变得很大，难道我们要用高精度吗？

但是，注意到：

$$
0\le\sum_{z=i}^{j}\le 2\times 10^{13}
$$

那么根据等式，又有：

$$
1\le\prod_{z=i}^{j} \le 2\times 10^{18}
$$

我们可以发现，乘积的可行值域实际上很小，假设排除 $1$ 的存在，容易发现，我们**最多只需要有 $\log{2\times10^{18}}$ 个数就可以达到理论上界**。

这说明了什么？暴力就行了啊！确定一个左端点后，我们只需要**判断最多 $64$ 个右端点**就可以统计出**当前左端点可行的答案**。

但是现在有 $1$ 的存在。那么很明显，我们将 $1$ 先排除就行了，我们可以将一段连续的 $1$ 压缩就行了。

那么考虑如何**统计 $1$ 加入的答案**。假设当前的乘积为 $x$，和为 $y$，下一个连续 $1$ 的长度为 $len$，我们只需要判断是否存在 $\Delta \le len$ 且 $\frac{x}{y+\Delta}=k$ 就行了。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e5+10;
int n,m,num[maxn],ne[maxn],ans,inf=2e18+7,a[maxn];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		num[i]=num[i-1];
		cin>>a[i];
		if(a[i]==1){
			num[i]++;
		}
	}
	num[n+1]=num[n];
	ne[n+1]=n+1;
	for(int i=n;i>=1;i--){
		if(a[i]!=1){
			ne[i-1]=i;
		}
		if(ne[i]!=0){
			continue;
		}
		ne[i]=ne[i+1];
	}
	for(int i=1;i<=n;i++){
		int sum=a[i];
		int j=i,pro=a[i];
		while(1){
			int now=pro-m*sum;
			if(now>=0&&now%m==0&&(num[ne[j]-1]-num[j])>=now/m){
				ans++;
			}
			if(ne[j]==n+1){
				break;
			}
			if(pro>=inf/a[ne[j]]+(inf%a[ne[j]]!=0)){
				break;
			}
			pro*=a[ne[j]];
			sum+=num[ne[j]-1]-num[j]+a[ne[j]];
			j=ne[j];
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Y2y7m (赞：0)

题目简述：

给你 $n$, $k$ 和一个包含 $n$ 个元素的数组。

问你有多少个子序列其中这个子序列中的所有数之积为所有数字和的 $k$ 倍。

简单思考过后发现只有 $1$ 会使积与和之比减小。

每多一个 $1$，和乘以 $k$ 与乘积之差就会减少 $k$。

建立一个链表：

定义 $nxt$ 数组为当前这个数往后的第一个不是 $1$ 的数。

枚举每一个整数，计算以这个整数为开头的子序列满足要求的有多少个，如果下一个数不是 $1$，就先加进来；如果是 $1$，则看看加上这一段 $1$ 有没有可能可以产生一种情况。

还有一个需要关注的点：

当乘积大于 $2 \times {10}^{18}$  时就可以 break 了。

在这种情况下你不管后面又多少个一都不可能可以。

代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
int n,k;
int a[200010],nxt[200010];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	nxt[n]=n+1; 
	for(int i=n-1;i>=1;i--)
	{
		if(a[i+1]==1)
		{
			nxt[i]=nxt[i+1];
		}
		else
			nxt[i]=i+1;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int mul=a[i],sum=a[i];
		int lst=i,pos=nxt[lst];
		if(k==1)//k等于1时只有一个数也行 
			ans++;
		while(1)
		{
			int d=mul-sum*k;
			if(d>0/*乘积达到基本要求*/&&d%k==0/*不是k的倍数加多少个一也没用*/&&d/k<=pos-lst-1/*1的数量足够你用*/)
				ans++;
			if(pos==n+1/*到头啦*/||2e18/a[pos]<mul/*太大了再怎么多的1也没用*/)
				break;
			mul*=a[pos];
			sum+=a[pos]+pos-lst-1;
			if(mul==sum*k)
				ans++;
			lst=pos;pos=nxt[lst]; 
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

