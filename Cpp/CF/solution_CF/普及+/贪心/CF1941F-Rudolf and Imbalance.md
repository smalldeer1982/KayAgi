# Rudolf and Imbalance

## 题目描述

Rudolf has prepared a set of $ n $ problems with complexities $ a_1 < a_2 < a_3 < \dots < a_n $ . He is not entirely satisfied with the balance, so he wants to add at most one problem to fix it.

For this, Rudolf came up with $ m $ models of problems and $ k $ functions. The complexity of the $ i $ -th model is $ d_i $ , and the complexity of the $ j $ -th function is $ f_j $ . To create a problem, he selects values $ i $ and $ j $ ( $ 1 \le i \le m $ , $ 1 \le j \le k $ ) and by combining the $ i $ -th model with the $ j $ -th function, he obtains a new problem with complexity $ d_i + f_j $ (a new element is inserted into the array $ a $ ).

To determine the imbalance of the set, Rudolf sorts the complexities of the problems in ascending order and finds the largest value of $ a_i - a_{i - 1} $ ( $ i > 1 $ ).

What is the minimum value of imbalance that Rudolf can achieve by adding at most one problem, created according to the described rules?

## 样例 #1

### 输入

```
7
5 5 5
5 10 15 20 26
11 14 16 13 8
16 4 5 3 1
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 9 3 2
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 13 3 2
5 6 3
2 10 13 20 25
11 6 10 16 14 5
6 17 15
4 2 2
11 12 14 15
19 14
10 6
8 4 2
3 10 16 18 21 22 29 30
9 13 16 15
4 2
2 4 7
4 21
4 15 14 5
20 1 15 1 12 5 11```

### 输出

```
5
4
5
8
2
7
11```

# 题解

## 作者：luobotianle (赞：8)

## 思路

我们要找出一个 $f[i]$ 和一个 $g[i]$ ， 使得将 $f[i] + g[i]$ 插入原序列 $a$ 后使得最大值最小。但是直接暴力的话时间复杂度是 $O(T \cdot mk)$ 的，显然超时，考虑二分。

首先对原序列的“不平衡值”也就是 $a[i] - a[i-1]$ 进行求解，如果最大值的个数大于一个，那么无论如何也无法减少这个最大值，直接输出即可；如果只有一个最大值，那么我们一定会把新造好的数放在**造成这个最大值的两个数之间**，以减小这个“不平衡值”。

所以问题就被转化成了：对于 $a$ 数组中的两个数 $a[i] , a[j]\ (a[j] > a[i])$ ，找到一个 $f[x]$ 和一个 $d[y]$ ，使 $\max (f[x]+d[y]-a[i] , a[j]-f[x]-d[y])$ 最小。

显然，当 $f[x]+d[y] = \frac{a[j]-a[i]}{2}$ 时，上式的值最小。

所以我们枚举 $f[x]$ ，并二分查找**大于**和**小于** $\frac{a[j]-a[i]}{2}$ 的两个 $f[x] + d[y]$ 的值，并比较它们对结果的贡献即可。

时间复杂度 $O(T \ \cdot \ (\log m)  k )$ ，记得开 `long long` 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//记得开 long long ，不开会 Wrong answer on test 3
const int N=2e5+5;
int n,m,k,T,cnt;
ll a[N],d[N],f[N];
ll maxn=-1;
int ml,mr;
ll merge1(int l,int r,int i,ll x){//二分大于 x 的第一个数 
	if(r<=l)return l;
	int mid=(l+r)>>1;
	if(d[i]+f[mid]>=x)return merge1(l,mid,i,x);
	//注意这两个二分判定条件的不同 
	else return merge1(mid+1,r,i,x);
}
ll merge2(int l,int r,int i,ll x){//二分小于 x 的第一个数 
	if(r<=l)return l-1;
	int mid=(l+r)>>1;
	if(d[i]+f[mid]>x)return merge2(l,mid,i,x);
	//   求小于的 ↑这里是 > ，另一边是 >= 
	else return merge2(mid+1,r,i,x);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		maxn=-1;
		cin>>n>>m>>k;
		cin>>a[1];
		for(int i=2;i<=n;i++){
			cin>>a[i];
			if(a[i]-a[i-1]>maxn){//寻找目前的最大不平衡值 
				maxn=a[i]-a[i-1];
				ml=i-1,mr=i;//造成最大不平衡值的左端点和右端点 
				cnt=1;
			}
			else if(a[i]-a[i-1]==maxn)cnt++;
		}
		for(int i=1;i<=m;i++)cin>>d[i];
		for(int i=1;i<=k;i++)cin>>f[i];
		sort(d+1,d+1+m);
		sort(f+1,f+1+k);
		if(cnt>1){//等到全输入完再特判，别急 
			cout<<maxn<<endl;
			continue;
		}
		ll ans=0,tar=(a[ml]+a[mr])>>1;
		for(int i=1;i<=m;i++){
			ll now=merge1(1,k+1,i,tar);
			if(now>=1&&now<=k){//用小于 maxn 的第一个值更新答案 
				int t=d[i]+f[now];
				if(t>=a[ml]&&t<=a[mr]){
					if(ans==0)ans=t;
					else if(max(ans-a[ml],a[mr]-ans)>max(t-a[ml],a[mr]-t))
						ans=t;
				}
			}
			now=merge2(1,k+1,i,tar);
			if(now>=1&&now<=k){//大于 maxn 的第一个值 
				int t=d[i]+f[now];
				if(t>=a[ml]&&t<=a[mr]){
					if(ans==0)ans=t;
					else if(max(ans-a[ml],a[mr]-ans)>max(t-a[ml],a[mr]-t))
						ans=t;
				}
			}
		}
		if(ans==0)cout<<maxn<<endl;//发现没有能够放在 a[j] 和 a[i] 之间的 f[x] + d[y] ，直接输出最大值 
		else{
			a[0]=ans;//否则将答案插入并重新排序，
			/*不要直接输出 min(ans-a[ml],a[mr]-ans)，插入 ans 后的最小值不一定在这里*/ 
			sort(a,a+1+n);
			maxn=-1;
			for(int i=1;i<=n;i++){
				maxn=max(maxn,a[i]-a[i-1]);
			}
			cout<<maxn<<endl;
		}
	}
	return 0;//AC
}
```

---

## 作者：Ratio_Y (赞：7)

# F - Rudolf and Imbalance

## 关于 set
众所周知 ~~（其实我T了好久才想起来~~ set 的特性是维护一个严格单调递增的数列，拥有自动去重的特性，所以在处理严格数据具有单调性的题目中非常好用。

而这道题，数据严格单增，完美契合 set。

有关 set 的更详细知识请移步至我的[博客](https://www.cnblogs.com/Ratio-Yinyue1007/p/18186604)。

## 思路

一开始直接找初始 $a_{n}$ 数组的中最大差和次大差，并将它们置入 set 数组中；

然后对最大差进行操作，用给的 f 和 d 操作将它分成两个尽量大的差，因为这样才能保证它们中较大的差更小，更满足题意；

然后注意数据范围，要开 `long long`；

关于其他注意事项，我在代码中加入了部分注释，仅供参考。

## code:
```
#include<bits/stdc++.h>
#define fo(x,y,z) for(int (x)=(y);(x)<=(z);(x)++)
#define fu(x,y,z) for(int (x)=(y);(x)>=(z);(x)--)
typedef long long ll;
inline ll qr()
{
	char ch=getchar();ll x=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
#define qr qr()
using namespace std;
const int Ratio=0;
const int N=200005;
const int maxint=INT_MAX;
const ll  maxll=1e18;
int n,m,k;
ll a[N];
ll deta,detaa,lb,rb,ans;
set<ll>f,d;
int main()
{
	// freopen("1.inll","r",stdin);
	// freopen("1.out","w",stdout);
	int T=qr;
    while(T--)
    {
        n=qr,m=qr,k=qr;
        f.clear(),d.clear();
        deta=0,detaa=0;
        fo(i,1,n)
        {
            a[i]=qr;
            if(i!=1)//输入时直接寻找最大差和次小差
                if(deta<a[i]-a[i-1])
                {
                    detaa=deta;
                    deta=a[i]-a[i-1];
                    lb=a[i-1],rb=a[i];
                    //由于单增排序 左边界为小
                }
                else if(detaa<a[i]-a[i-1])
                    detaa=a[i]-a[i-1];
        }
        fo(i,1,m)
        {
            ll dd=qr;
            d.insert(dd);
        }
        fo(i,1,k)
        {
            ll ff=qr;
            f.insert(ff);
        }
        ans=deta;
        for(auto i:f)
		{
            auto dh=d.lower_bound((lb+rb)/2-i),yy=dh;
            //找最接近中间的 分开后两差大的尽量小
            ll dh1=*dh,yy1=*yy;
            //lower_bound值是指针类型无法运算 加*
            ans=min(ans,max(dh1+i-lb,rb-i-dh1));
            if(yy!=d.begin())
            //不是队首 指针需向上取 保证答案最优
            {
                yy--;
                yy1=*yy;
                ans=min(ans,max(yy1+i-lb,rb-i-yy1));
            }
        }
		cout<<max(detaa,ans)<<endl;
        //此时再次比较次大值和更改后最大值
    }
	return Ratio;
}
```
完结撒花~

---

## 作者：MrPython (赞：6)

~~会 G 不会 F 是不是没救了~~
>Rudolf sorts the complexities of the problems in ascending order and finds the largest value of $a_i-a_{i-1}(i>1)$.
>
> What is the minimum value of imbalance that Rudolf can achieve by adding at most one problem, created according to the described rules?

最大值最小化，是经典二分答案问题。直接二分所要求的最大值即可。

我们可以初始排序好 $a$。每次 check 时，枚举相邻两个元素间的差。记当前要 check 的值为 $x$。若 $a_i-a_{i-1}>x$，说明我们需要插入一个元素。

我们只能插入一个问题，即只能将一个段变小。因此遇到过长段时打上一个 flag，下次遇到过长段且有 flag 可以直接返回 `false`。

而判断某个段内是否可以通过插入一道题的方式让区间变小，这就是“求是否可以在两个序列中各取出一个数使其和在某范围”的经典问题。枚举 $d$ 中元素，求出若把段分成两个合法段需要的 $f$ 中元素最小/最大是多少，再按照这个范围在 $f$ 中二分就好了。

设二分的值域为 $w$。每次 check 需要遍历 $a$ 一次，最多会遍历 $d$ 一次。遍历 $d$ 时还需要在 $f$ 内二分查找，因此 check 函数的时间复杂度为 $O\left(n+m\log k\right)$，总时间复杂度为 $O\left(\left(n+m\log k\right)\log w\right)$。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n,m,k;cin>>n>>m>>k;
        vector<ui> a(n),d(m),f(k);
        for (ui& i:a) cin>>i;
        for (ui& i:d) cin>>i;
        for (ui& i:f) cin>>i;
        sort(a.begin(),a.end()),sort(d.begin(),d.end()),sort(f.begin(),f.end());
        ui l=0,r=2e9+1;
        auto check=[&](ui mid){
            bool flag=false;
            for (size_t i=1;i<n;++i) if (a[i]-a[i-1]>mid){
                if (flag) return false;
                flag=true;
                for (ui j:d){
                    vector<ui>::const_iterator it=a[i]-mid>=j?lower_bound(f.cbegin(),f.cend(),a[i]-mid-j):f.cbegin(),
                                               jt=a[i-1]+mid>=j?upper_bound(f.cbegin(),f.cend(),a[i-1]+mid-j):f.cbegin();
                    if (it<jt) goto getit;
                }
                return false;
                getit:;
            }
            return true;
        };
        while (l<r){
            ui mid=(l+r)/2;
            check(mid)?r=mid:l=mid+1;
        }
        cout<<l<<'\n';
    }
    return 0;
}
```

---

## 作者：luqyou (赞：4)

# 思路

直接考虑插入什么位置是最优的。

显然，我们需要插入的点必须是 $a_i - a_{i-1}$ 最大的地方（记该位置为 $pos$），否则答案不会发生变化。

那么我们把 $f$ 去重排序，然后枚举每个 $d_i$。对于每个 $d_i$，二分一个区间 $[l,r]$ 使得所有 $j \in [l,r]$ 都有 $a_{i-1} \le d_i + f_j \le a_i$。直接用区间内所有数更新答案即可。

但是这个复杂度最劣是 $O(mk \log k)$ 的，考虑优化。

不难发现我们还是可以缩短区间，因为显然当 $d_i + f_j = a_{pos} + \lfloor \dfrac{a_{pos}-a_{pos-1}}{2} \rfloor$ 时答案是尽量小的。所以根据这个二分，再用二分到的位置和左右两边更新一下答案就可以了。注意答案要与差值次大值取 $\max$。

时间复杂度 $O(n +(m+k) \log k)$。

# code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=2e5+10;
int n,m,k,a[maxn],d[maxn],f[maxn],g[maxn],maxx,maxi,max2,ans;
void work(int &res,int p1,int p2){
	if(p1<=0||p2<=0||p1>m||p2>k) return ;
//	cout<<p1<<" "<<p2<<" "<<max(a[maxi]-d[p1]-f[p2],d[p1]+f[p2]-a[maxi-1])<<endl;
	res=min(res,max(a[maxi]-d[p1]-f[p2],d[p1]+f[p2]-a[maxi-1]));
}
void solve(){
	maxx=0;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>d[i];
	}
	for(int i=1;i<=k;i++){
		cin>>g[i];
	}
	int ck=0;
	for(int i=1;i<=k;i++){
		if(g[i]!=g[i-1]) f[++ck]=g[i];
	}
	k=ck;
	sort(f+1,f+k+1);
	for(int i=2;i<=n;i++){
		if(a[i]-a[i-1]>maxx){
			max2=maxx,maxx=a[i]-a[i-1],maxi=i;
		}
		else if(a[i]-a[i-1]>max2){
			max2=a[i]-a[i-1];
		}
	}
	ans=maxx;
	int tmp=a[maxi-1]+(a[maxi]-a[maxi-1])/2;
	for(int i=1;i<=m;i++){
		int p1=lower_bound(f+1,f+k+1,tmp-d[i])-f;
		work(ans,i,p1),work(ans,i,p1-1),work(ans,i,p1+1);
	}
	cout<<max(ans,max2)<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：littlebug (赞：1)

## Solution

先排个序，因为要使最大值最小，所以二分，找到 $a_i-a_{i-1}$ 的最大值和次大值，设最大值两边的元素分别为 $l,r$。问题就转化为求一个 $l \le d_i+f_j \le r$ 使得 $\max((d_i+f_j)-l,r-(d_i+f_j))$ 最小。

考虑 $O(m)$ 枚举 $d_i$，然后二分 $f_j$。对于每个 $d_i$，求一个 $f_j$ 使得 $d_i+f_j$ 最接近 $mid=\frac {l+r}{2}$，于是分别二分找第一个 $\ge mid-d_i$ 的和第一个 $\le mid-d_i$ 的 $f_j$，若存在这样的 $f_j$ 且 $l \le d_i+f_j \le r$，计入答案。

特别地，若 $d_i \ge mid$，则 $j=1$。最后如果 $ans$ 无解（即不存在 $i,j$ 使得 $l \le d_i+f_j \le r$），输出区间最大值。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define il inline
#define ll long long
#define inf (ll)(9e18)
using namespace std;
const int MAXN=2e5+5;
int n,m,k;
ll a[MAXN],d[MAXN],f[MAXN];
il ll check(int i,int j,ll l,ll r)
{
	if(j>0 && j<=k && d[i]+f[j]>=l && d[i]+f[j]<=r)
		return max((d[i]+f[j])-l,r-(d[i]+f[j]));
	return inf;
}
il void solve()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;++i) cin>>d[i];
	for(int i=1;i<=k;++i) cin>>f[i];
	sort(a+1,a+n+1);
	sort(d+1,d+m+1);
	sort(f+1,f+k+1);
	m=unique(d+1,d+m+1)-d-1;
	k=unique(f+1,f+k+1)-f-1;
	ll mx=-inf,mx2=-inf,now,l,r;
	for(int i=2;i<=n;++i)
	{
		now=a[i]-a[i-1];
		if(now>=mx) mx2=mx,mx=now,l=a[i-1],r=a[i];
		else if(now>=mx2) mx2=now;
	}
	if(mx==mx2)
	{
		cout<<mx<<'\n';
		return;
	}
	ll ans=inf,j,mid=(l+r)>>1;
	for(int i=1;i<=m;++i)
	{
		if(d[i]>r || d[i]+f[k]<l) continue;
		now=inf;
		if(d[i]>=mid)
		{
			now=check(i,1,l,r);
			ans=min(ans,now);
			continue;
		}
		j=upper_bound(f+1,f+k+1,mid-d[i])-f-1;
		now=min(check(i,j+1,l,r),check(i,j,l,r));
		ans=min(ans,now);
		if(ans<=mx2)
		{
			cout<<mx2<<'\n';
			return;
		}
	}
	if(ans==inf) cout<<mx<<'\n';
	else cout<<max(ans,mx2)<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：_yi_ (赞：1)

# Rudolf and Imbalance
## 题意简述

鲁道夫准备了一系列问题，并希望通过添加至多一个问题来最小化问题集合的不平衡性。不平衡性定义为问题复杂度的最大差值。他可以通过结合问题模型和函数来创建新问题，目标是找到添加新问题后可以达到的最小不平衡值。

## 题目分析

本题是一道双指针问题。首先，我们需要找到当前问题集合中最大的差值 $a_{i+1} - a_i$。新插入的问题的复杂度必须位于 $a_i$ 和 $a_{i+1}$ 之间，以确保不会增加不平衡性。

1. **确定初始不平衡值**：遍历问题集合，找出最大的差值，记为 $t2 - t1$，记 $\text{mid}=\frac{t1+t2}{2}$。
2. **双指针寻找最优解**：
   - 初始化两个指针，分别指向问题模型数组的第 $1$ 位和函数数组的第 $k$ 位。 
   - 计算当前指针指向的两个数的和，判断与 $\text{mid}$ 的大小。
   - 如果和大于 $\text{mid}$，移动函数数组的指针向前；如果小于 $\text{mid}$，移动问题模型数组的指针向后。
   - 更新最小不平衡值。
   
正确性很显然，若我们已知当前的 $d _ 1 + f _ k$ 和偏大，则对于$d _ 2 \dots d _ m + f _ k$，答案都不会更优，所以我们只需向前移动 $f$ 的指针即可。反之亦然。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5;
ll a[N+1],d[N+1],f[N+1];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=m;i++){
            cin>>d[i];
        }
        for(int i=1;i<=k;i++){
            cin>>f[i];
        }
        sort(a+1,a+n+1);
        sort(d+1,d+m+1);
        sort(f+1,f+k+1);
        ll t1=0,t2=0;
        ll temp=0;
        for(int i=1;i<n;i++){
            if(a[i+1]-a[i]>t2-t1){
                temp=t2-t1;
                t1=a[i];
                t2=a[i+1];
            }
            else{
                temp=max(temp,a[i+1]-a[i]);
            }
        }
        ll l=1,r=k;
        ll ans=t2-t1;
        while(l<=m&&r>=1){
            ll t=d[l]+f[r];
            if(t>=t1&&t<=t2) ans=min(ans,max(t-t1,t2-t));
            if(t*2>t1+t2){
                r--;
            }
            else{
                l++;
            }
        }
        while(l<=m){
            int t=d[l]+f[1];
            if(t>=t1&&t<=t2) ans=min(ans,max(t-t1,t2-t));
            l++;
        }
        while(r>=1){
            int t=d[m]+f[r];
            if(t>=t1&&t<=t2) ans=min(ans,max(t-t1,t2-t));
            r--;
        }
        cout<<max(temp,ans)<<endl;
    }
    return 0;
}
```
## 时间复杂度分析

- 时间复杂度主要取决于排序，为 $O(n \log n)$。
- 双指针遍历的时间复杂度为 $O(m + k)$。
- 因此，总的时间复杂度为 $O(n \log n + m + k)$。

## 总结

本题通过双指针技巧有效地解决了在限定范围内寻找最优解的问题。这种方法在处理类似问题时非常有效，尤其是当需要在一个有序数组中找到满足特定条件的元素对时。

---

## 作者：haokee (赞：1)

我们发现答案具有单调性，因为尝试的答案越大满足条件的概率就越高，因此考虑二分。那么，如何判断 $x$ 能不能成为一个正确的答案呢？首先，$a_i-a_{i-1}$ 不能大于 $2x$，因为我们这里只允许添加一个 $d_i+f_j$。然后，不能有两个 $i$ 满足 $a_i-a_{i-1}>x$，原因跟上一个一样。然后就是判断的部分了，如果 $a_i-a_{i-1}$ 不满足条件，那么答案就一定区间 $[a_i-x,a_{i-1}+x]$ 里面，因此我们枚举 $d_i$，然后再二分一个满足条件的 $f_j$ 就行了。注意 $f$ 需要排序。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 2e5 + 5;

int a[kMaxN], d[kMaxN], f[kMaxN], t, n, m, k, ans;

bool check(int x) {
  int cnt = 0, mn, mx, b = 0;
  for (int i = 2; i <= n; i++) {
    if (a[i] - a[i - 1] > x) {
      mn = a[i] - x;
      mx = a[i - 1] + x;
      b |= a[i] - a[i - 1] > x * 2;
      cnt++;
    }
  }
  if (cnt > 1 || b) {
    return 0;
  } else if (!cnt) {
    return 1;
  }
  for (int i = 1; i <= m; i++) {
    int p = lower_bound(f + 1, f + k + 1, mn - d[i]) - f;
    if (p != k + 1 && d[i] + f[p] >= mn && d[i] + f[p] <= mx) {
      return 1;
    }
  }
  return 0;
}

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
      cin >> d[i];
    }
    for (int i = 1; i <= k; i++) {
      cin >> f[i];
    }
    sort(f + 1, f + k + 1);
    for (int l = 0, r = 2e9; l <= r;) {
      int mid = (l + r) >> 1;
      if (check(mid)) {
        ans = mid, r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：__vector__ (赞：1)

赛时没开 ```long long``` 吃了 5 个罚时在这题。 
### 做法  
先计算出 $a_{i+1}-a_i$ 的最大值，如果这个最大值多次出现，那么显然答案无法改变，直接把最大值输出就行。  

然后，考虑如何搭配 $f,d$ 使得插入后的值能更好的减少最大值。  

显然，设最优方案为 $f_i+d_j$，另设 $a_{p+1}-a_p$ 是 $a$ 相邻元素差值的最大值。那么 $f_i+d_j$ 应尽可能均分 $a_{p+1}-a_p$，也就是说 $f_i+d_j$ 应尽可能接近 $\frac{a_{p+1}-a_p}{2}$。   

此时解决方案已经很明显了。  

枚举 $f_i$，并二分 $d_j$，找出使得 $f_i+d_j$ 能达到的最大的小于 $\frac{a_{p+1}-a_p}{2}$ 的值对应的 $d_j$，以及使得 $f_i+d_j$ 能达到的最小的大于 $\frac{a_{p+1}-a_p}{2}$ 的值对应的 $d_j$。以上操作用 ```lower_bound``` 就可以解决。  

注意计算 $\frac{a_{i}+a_{i+1}}{2}$ 如果先加后除，那么会爆 ```int```，我赛时因此吃了 5 个罚时。

---

## 作者：nothing__ (赞：0)

对于这一题，实际上可以优雅的暴力草过。

思路：先扫一遍，找出差值最大的位置 $p$。

考虑枚举 $d_i$，每一次二分查找出最大的 $j$，使得 $a_{p-1} \le d_i+f_j \le a_p$，然后往后扫直到 $d_i+f_j \le a_{p-1}$。

关键：先将 $f$ 和 $d$ 数组排序，并**去重**。

如果不去重的话会卡不过去。

具体实现：

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read() {
	int x=0, w=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') w=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+(ch-'0'); ch=getchar();}
	return x*w;
}
const int N=2e5+10;
const int inf=0x3f3f3f3f;
int n, m, k;
int a[N], d[N], f[N];
signed main() {
	int T; T=read();
	while(T--) {
		n=read(), m=read(), k=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=m;i++) d[i]=read();
		for(int i=1;i<=k;i++) f[i]=read();
		sort(d+1, d+1+m);
		m=unique(d+1, d+1+m)-d-1;
		sort(f+1, f+1+k);
		k=unique(f+1, f+1+k)-f-1;
		int mx=0, j;
		for(int i=2;i<=n;i++) {
			if(a[i]-a[i-1]>mx) {
				mx=a[i]-a[i-1];
				j=i;
			}
		}
		for(int i=1;i<=m;i++) {
			int now=a[j]-d[i];
			int p=lower_bound(f+1, f+1+k, now)-f;
			if(p<=1) continue;
			for(int x=p-1;x>=1;x--) {
				int s=d[i]+f[x];
				if(s<=a[j-1]) break;
				if(abs(a[j]-s-(s-a[j-1]))<mx) {
					mx=min(mx, max(a[j]-s, s-a[j-1]));
				}
			}
		}
		for(int i=2;i<=n;i++) {
			if(i==j) continue;
			mx=max(a[i]-a[i-1], mx);
		}
		printf("%lld\n", mx);
	}
	return 0;
}
```

---

## 作者：OPEC (赞：0)

# [CF1941F Rudolf and Imbalance](https://www.luogu.com.cn/problem/CF1941F)
这道题一看就是~~暴力~~二分，因为暴力会超时，只能考虑二分。

只需要二分，当 $f_i+d_i=\frac{a_j-a_i}{2}$ 时是最优的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int n,m,k;
int a[N];
int d[N];
int f[N];
void solve()
{
	cin>>n>>m>>k;
	int m1=0,m2=0;
	int cnt=0;
	int l,r;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(i>=2)
		{
			int t=a[i]-a[i-1];
			if(t>m1)
			{
				m2=m1;
				m1=t;
				cnt=1;
				l=a[i-1];
				r=a[i];
			}
			else if(t==m1)
			{
				cnt++;
			}
			else if(t>m2)
			{
				m2=t;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		cin>>d[i];
	}
	for(int i=1;i<=k;i++)
	{
		cin>>f[i];
	}
	if(cnt>1)
	{
		cout<<m1<<'\n';
		return;
	}
	sort(d+1,d+m+1);
	sort(f+1,f+k+1);
	int mid=(l+r)/2;
	int ans=m1; 
	for(int i=1,j=k;i<=m;i++)
	{
		int t=d[i]+f[j];
		if(t>l&&t<r)
		{
			ans=min(ans,max(t-l,r-t));
			while(j>1&&t>=mid)
			{
				j--;
				t=d[i]+f[j];
				if(t>l&&t<r)
				{
					ans=min(ans,max(t-l,r-t));
				}
				else
				{
					break;
				}
			}
		}
		else if(j>1&&t>=r)
		{
			j--;
			i--;
		}
	}
	ans=max(ans,m2);
	cout<<ans<<'\n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve(); 
	}
	return 0;
}
```

---

## 作者：Day_Tao (赞：0)

### 题目大意

给定长度分别为 $n,m,k$ 的数组 $a,d,f$，其中保证 $a$ 升序。现在你要在 $d,f$ 两个数组中分别选出一个数，相加后加入到 $a$ 数组中，再按升序排序。求怎样操作能使最终的 $a$ 数组相邻的两个数之差最大值最小。

### Sol

首先考虑 $a$ 数组。要插入的数一定在原来 $a$ 数组相邻两个数之差最大的两数之间。记这两数的位置分别为 $i,i+1$，则要插入大小最接近 $\frac{a_i+a_{i+1}}{2}$ 的数，这样才能尽可能地缩小最终 $a$ 数组最大的两数之差。由于只需要找到一个数，就可以直接枚举 $d$ 数组，再对 $f$ 数组进行二分，找到最接近 $\frac{a_i+a_{i+1}}{2}-d_i$ 的数，用 $res$ 记录最小的 $|f_{mid}-\frac{a_i+a_{i+1}}{2}-d_i|$，最后将 $res+\frac{a_i+a_{i+1}}{2}$ 插入 $a$ 数组进行处理，就可以得出答案啦。由于 $\frac{a_i+a_{i+1}}{2}+res$ 与 $\frac{a_i+a_{i+1}}{2}-res$ 的贡献是一样的，所以就不需要考虑这个了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 2e5 + 5;
const int INF = 0x7fffffff;
const int mod = 998244353;
int n,m,k,a[MAX],b[MAX],c[MAX],p1,p2,maxx,T;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&n,&m,&k);
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        for(int i=1;i<=m;i++)
            scanf("%lld",&b[i]);
        for(int i=1;i<=k;i++)
            scanf("%lld",&c[i]);
        maxx=0;
        for(int i=1;i<n;i++)
            if(a[i+1]-a[i]>maxx)
                maxx=a[i+1]-a[i],p1=i,p2=i+1;
        sort(c+1,c+k+1);
        double res=INF;
        for(int i=1;i<=m;i++)
        {
            int l=1,r=k,mid;
            double x=(a[p2]+a[p1])*1.0/2-b[i];
            while(l<=r)
            {
                mid = (l+r)>>1;
                res=min(res,abs(c[mid]-x));
                if((double)c[mid]==x)
                {
                    res=0;
                    break;
                }
                if((double)c[mid]>x)
                r=mid-1;
                else l=mid+1;
            }
        }
        if(res+(a[p2]+a[p1])*1.0/2<(double)a[n])
            a[++n]=res+(a[p2]+a[p1])*1.0/2;
        sort(a+1,a+n+1);
        int ans=-1;
        for(int i=1;i<n;i++)
            ans=max(ans,a[i+1]-a[i]);
        printf("%lld\n",ans);
    }
    // system("pause");
    return 0;
}
```

---

### END

---

## 作者：hhce2012 (赞：0)

省流：贪心+二分（

# 题意

我们有三个数组，现在要从第二个数组和第三个数组中各选取一个数（不取出），将选的两个数加起来加入第一个数组，最后混乱值为将第一个数组排序后相邻两个数的差的最大值，求最小混乱值。

# 思路

一看 $n \le 10^5, 1 \le m, k \le 2 \cdot 10^5$，考虑线性对数级算法。

显然的我们必须精准插入最大的空隙里面，然后要尽量平均。

所以最理想的情况是刚好插到中间，但是这种情况可能完不成，导致我们只能找到离中间最近的地方插入。

所以二分找到可能的比较理想的情况，更新答案即可。

别忘了其他的空隙也是空隙。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, n, m, k, arr[100010], brr[200020], crr[200020];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  for(cin >> t; t--; ) {
    cin >> n >> m >> k;
    int tmp = 0, rtmp = 0;
    for(int i = 1; i <= n; i++) {
      cin >> arr[i];
      if(i > 1 && (!tmp || arr[i] - arr[i - 1] > arr[tmp + 1] - arr[tmp])) {
        rtmp = tmp;
        tmp = i - 1;
      }else {
        if(i > 1 && (!rtmp || arr[i] - arr[i - 1] > arr[rtmp + 1] - arr[rtmp])) {
          rtmp = i - 1;
        }
      }
    }
    for(int i = 1; i <= m; i++) {
      cin >> brr[i];
    }
    for(int i = 1; i <= k; i++) {
      cin >> crr[i];
    }
    sort(crr + 1, crr + k + 1);
    int ans = arr[tmp + 1] - arr[tmp];
    for(int i = 1; i <= m; i++) {
      int tmp2 = upper_bound(crr + 1, crr + k + 1, (arr[tmp + 1] + arr[tmp]) / 2 - brr[i]) - crr;
      if(tmp2 != k + 1 && arr[tmp] <= crr[tmp2] + brr[i] && arr[tmp + 1] >= crr[tmp2] + brr[i]) { // 注意插不插得到这个空隙里面，否则 WA
        ans = min(ans, max(arr[tmp + 1] - (brr[i] + crr[tmp2]), (brr[i] + crr[tmp2]) - arr[tmp]));
      }
      if(tmp2 > 1 && arr[tmp] <= crr[tmp2 - 1] + brr[i] && arr[tmp + 1] >= crr[tmp2 - 1] + brr[i]) {
        ans = min(ans, max(arr[tmp + 1] - (brr[i] + crr[tmp2 - 1]), (brr[i] + crr[tmp2 - 1]) - arr[tmp]));
      }
    }
    cout << max(ans, (rtmp? arr[rtmp + 1] - arr[rtmp] : -1)) << '\n'; // 其他的空隙也是空隙
  }
  return 0;
}
```

---

