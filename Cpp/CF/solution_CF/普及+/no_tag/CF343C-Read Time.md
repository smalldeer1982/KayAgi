# Read Time

## 题目描述

Mad scientist Mike does not use slow hard disks. His modification of a hard drive has not one, but $ n $ different heads that can read data in parallel.

When viewed from the side, Mike's hard drive is an endless array of tracks. The tracks of the array are numbered from left to right with integers, starting with 1. In the initial state the $ i $ -th reading head is above the track number $ h_{i} $ . For each of the reading heads, the hard drive's firmware can move the head exactly one track to the right or to the left, or leave it on the current track. During the operation each head's movement does not affect the movement of the other heads: the heads can change their relative order; there can be multiple reading heads above any of the tracks. A track is considered read if at least one head has visited this track. In particular, all of the tracks numbered $ h_{1} $ , $ h_{2} $ , $ ... $ , $ h_{n} $ have been read at the beginning of the operation.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343C/477411d635199d18d36c6b93ba130f0f6f88e682.png)Mike needs to read the data on $ m $ distinct tracks with numbers $ p_{1} $ , $ p_{2} $ , $ ... $ , $ p_{m} $ . Determine the minimum time the hard drive firmware needs to move the heads and read all the given tracks. Note that an arbitrary number of other tracks can also be read.

## 说明/提示

The first test coincides with the figure. In this case the given tracks can be read in 2 seconds in the following way:

1. during the first second move the 1-st head to the left and let it stay there;
2. move the second head to the left twice;
3. move the third head to the right twice (note that the 6-th track has already been read at the beginning).

One cannot read the tracks in 1 second as the 3-rd head is at distance 2 from the 8-th track.

## 样例 #1

### 输入

```
3 4
2 5 6
1 3 6 8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
1 2 3
1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1 2
165
142 200
```

### 输出

```
81
```

# 题解

## 作者：离散小波变换° (赞：3)

## 题目大意

在一个无限长的数轴上有 $n$ 个指针与 $m$ 个点。指针的位置是 $h_1,h_2,\cdots h_n$，点的位置是 $p_1,p_2,\cdots p_m$。现在每个时刻可以让每个指针向左或者向右移动一个单位，求在最优操作下让指针扫过（到达过）所有点所需要的时间。

## 题解

容易发现答案满足单调性：如果使用 $t_0$ 时间可以满足题设要求，那么对于任意的 $t>t_0$ 时间都可以满足要求。因此考虑二分答案。假设现在二分的答案为 $x$。

注意一个重要结论：最优情况下，**每个指针扫过的区域不重叠**。假设两个指针扫过的区间产生了重叠，那么我们哪怕让某个指针止步在另一个指针扫过区域的边界，都不会使答案更劣。

于是从左到右考虑每个点。当前最左侧的点（位置记为 $p_0$）必须是最左侧的指针（位置记为 $h_0$）扫过，不然指针扫过的区域必然会发生重叠（因为右侧指针必须跨过最左侧指针，这就不可避免重叠），这样会使答案不优。那么如何让最左侧指针扫过当前最左侧的点呢？有两种情况要讨论：

- $h_0<p_0$。那么显然这个指针一路向右扫是最好的。
- $h_0\ge p_0$。那么又要分出两种可能的情况：
  - 第一种情况，该指针先往左扫扫到 $p_0$，再不断地往右扫。那么它向右的最大距离就是 $\max(0,x-2\times (p_0-h_0))$。
  - 第二种情况，该指针先往右扫扫到尽量远的地方，但是要保证此时它往回扫可以扫到 $p_0$。那么它往右扫的最大距离 $s$ 应当满足 $2\times s+h_0-p_0\le x$，解得 $s=\left\lfloor\dfrac{x+p_0-h_0}{2}\right\rfloor$。  
- 这两种情况往右扫的最大距离取 $\max$，得到在最左侧指针扫到 $p_0$ 的情况下，往右最多扫描的距离。

容易发现，我们扫过的区域肯定是从最左侧点开始连续的一个区间。于是在代码实现上，我们记 $l$ 表示当前未扫到的点中，最靠左的点。然后依次枚举每个指针，然后更新 $l$。考虑到 $l$ 会依次扫过每个点不超过一次，因此每次 $\text{check}$ 的时间复杂度为 $\mathcal O(n+m)$ 的。

加上二分，总时间复杂度为 $\mathcal O((n+m)\log v)$。顺带一提，不知道出题人咋想的，坐标范围开到 $10^{10}$，必须要开 $\text{long long}$ 存储。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e6+3;
i64 qread(){
    i64 w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
i64 n,m,H[MAXN],P[MAXN];
bool chk(i64 x){
    int p=1; up(1,n,i){
        if(P[p]<=H[i]){
            if(H[i]-P[p]>x) return false;
            i64 d=H[i]-P[p];
            while(p<=m&&(P[p]-H[i]<=x-2*d||2*(P[p]-H[i])+d<=x)) ++p;
        } else {
            while(p<=m&&P[p]-H[i]<=x) ++p;
        }
        if(p>m) return true;
    }
    return false;
}
i64 ans=-1;
int main(){
    n=qread(),m=qread();
    up(1,n,i) H[i]=qread();
    up(1,m,i) P[i]=qread();
    dn(35,0,i) if(!chk(ans+(1ll<<i))) ans+=1ll<<i;
    printf("%lld\n",ans+1);
    return 0;
}
```

---

## 作者：Guess00 (赞：2)

~~此时是2019.11.16,CSP-J第二试当天.据说考前发题解会rp++~~

先挂一下CF官方题解:
![](https://i.loli.net/2019/11/09/C1gDjyvPaHrEWzo.png)

---
### 本题思路$:$二分答案

本题二分出最小满足要求的$t,$输出$.$

$\mathbb{Q:}$如何判断某个t满足要求呢?

$\mathbb{A:}$枚举每个探头$,$在时间$t$内看TA最左能到哪一个要读的轨道$,$再看TA最右能到哪一个要读的轨道$.$若将$m$个轨道全覆盖了$,$说明满足要求$,$反之$,$不满足要求$.($看代码更好理解一点$)$

时间复杂度$:\Theta\big((n+m)\log_{2}\max(h[i],p[i])\big)$

$\text{注意}:$在判断时复杂度不是$nm,$而是$n+m.$在枚举可读到的轨道时是基于上一次的可到达的轨道$,$所以轨道只枚举了$m$次$.$

---
$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 100005
#define inf 0x3f3f3f3f3f
int n,m,i,l,r=inf,mid,h[MAXN],p[MAXN];
inline void read(int &x)  //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)    //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
inline int abs(int x){return x>0?x:-x;}
inline int min(int x,int y){return x<y?x:y;}
inline bool check(int t)     //本题重点:判断 
{
	int l,r,ans;
	l=r=1;
    for (i=1;i<=n;i++)
    {
        ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
        while (r<=m && ans<=t)  //枚举 
            r++,ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
        l=r;
        if (r>m)   //已经覆盖了所有轨道 
            return true;  //t满足要求 
    }
    return false;
}
signed main(void)
{
	read(n),read(m);   //输入 
	for (i=1;i<=n;i++)
		read(h[i]);
	for (i=1;i<=m;i++)
		read(p[i]); 
	while (l<=r)    //二分答案 
	{
		mid=(l+r)>>1;
		if (check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	print(l);   //愉快地输出 
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
显然时间具有单调性，所以二分时间。

`check` 函数枚举每一个头，因为要最优解，所以每一个指针不能重叠。

所以我们用 $l$ 记录每一次最左端的没扫描的区域。这里一定是由离他最近的读头扫描。接着为了让每一个读头尽可能在当前时间多扫描，我们用循环枚举每一次往右多读取的轨道的下标，判断是否可以取到。

每一次取时，用 `ans` 记录下每个头在对应时间下最多可以扫描的轨道。

也就是：
$$
ans=\left |p_r-p_l\right | +\min(\left |p_l-h_i\right | ,\left |p_r-h_i\right | );
$$

这里取最小值是为了确认先往左扫描还是先往右扫描，减少时间。


### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 1000009
#define inf 20000001000
using namespace std;

int h[maxn],p[maxn],n,m,ls=0,mid,rs=inf;

bool check(int x)
{
	int l=1,r=1,ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
		while(r<=m && ans<=x)		
		{
			r++;
			ans=abs(p[r]-p[l])+min(abs(p[l]-h[i]),abs(p[r]-h[i]));
		}
		l=r;
		if(r>m) return true;
	}
	return false;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=1;i<=m;i++) cin>>p[i];
	
	
	while(ls<=rs)
	{
		mid=(ls+rs)/2;
		if(check(mid)) rs=mid-1;
		else           ls=mid+1;
	}
	
	cout<<ls;
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

先二分答案。

check 的时候每次贪心地把可以选到的区间选了，但是如果先向右再往左要更优的话，别忘了判一下。

```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=1e5+10;
int n,m;
ll p[sz],k[sz];
bool check(ll x){
    int cur=1;
    for(int i=1;i<=n;i++){
        if(cur<=m&&k[cur]<=p[i]){
            if(p[i]-k[cur]>x)return false;
            ll r=std::max({p[i],k[cur]*2+x-p[i],p[i]+(x-p[i]+k[cur])/2});
            cur=std::upper_bound(k+1,k+m+1,r)-k;
        }else cur=std::upper_bound(k+1,k+m+1,p[i]+x)-k;
    }
    return cur>m;
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)std::cin>>p[i];
    for(int i=1;i<=m;i++)std::cin>>k[i];
    ll l=0,r=3e10;
    while(l<r){
        ll mid=l+r>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    std::cout<<l<<"\n";
    return 0;
}
```

---

