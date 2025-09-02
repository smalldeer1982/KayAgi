# Castle Defense

## 题目描述

Today you are going to lead a group of elven archers to defend the castle that is attacked by an army of angry orcs. Three sides of the castle are protected by impassable mountains and the remaining side is occupied by a long wall that is split into $ n $ sections. At this moment there are exactly $ a_{i} $ archers located at the $ i $ -th section of this wall. You know that archer who stands at section $ i $ can shoot orcs that attack section located at distance not exceeding $ r $ , that is all such sections $ j $ that $ |i-j|<=r $ . In particular, $ r=0 $ means that archers are only capable of shooting at orcs who attack section $ i $ .

Denote as defense level of section $ i $ the total number of archers who can shoot at the orcs attacking this section. Reliability of the defense plan is the minimum value of defense level of individual wall section.

There is a little time left till the attack so you can't redistribute archers that are already located at the wall. However, there is a reserve of $ k $ archers that you can distribute among wall sections in arbitrary way. You would like to achieve maximum possible reliability of the defence plan.

## 样例 #1

### 输入

```
5 0 6
5 4 3 4 9
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 2 0
1 2 3 4
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5 1 1
2 1 2 1 2
```

### 输出

```
3
```

# 题解

## 作者：linxiaoyu四 (赞：4)

*******************************************
    （感觉这题很水）

看到这题先想到二分答案（求最大的最小值）；
  
  对于每个城墙i 都有ai个弓箭手，可以守卫左右各r的范围，
  其实就是在（i-r）——（i+r）这段区间内都有ai个守备力量，就是在其间每个点+ai；
  
  
  再去思考如何验证一个答案X；
  
  从左到右遍历，若一个点i的值（bi）不足X，就将以i为起点向右的一段长度为2*r的区间都加上（x-bi）；
  （因为左边已满足条件，贡献给右边）；
  
  若需要加的值超过k（可用的弓箭手），则答案不行；
  
  然后是怎么维护区间的加值；
  
  开始用线段树，结果GG；（时间复杂度有大佬证过了）
  
  那么就用点更简单的；
  
  用差分与前缀和之类的去考虑，这样区间加值就是在区间首+x，区间尾后面-x；
  其它不说了；
  
  代码：（有点丑，第一份题解）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,r,k,x,max1;
int a[5000001],b[5000001],c[5000001];
void add(int l,int r,int x)
{
	b[l]+=x;b[r+1]-=x;//区间加值
}
bool che(int x)
{
	int sum=0;
	for(int i=1;i<=n;i++) b[i]=c[i];
	for(int i=1;i<=n;i++)
	{
	    b[i]+=b[i-1];//用前缀和查询
		if(b[i]<x)
		{
		   sum+=x-b[i],add(i,i+2*r,x-b[i]);if(sum>k)return 0;
		}
	}
	return 1;
}
signed main()
{
	cin>>n>>r>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		c[i]+=a[i],c[i+r+1]-=a[i];
		int z=i-r;
		if(z<1) z=1;
		c[z]+=a[i];c[i]-=a[i];
		max1+=a[i]+k;
	}
	int l=0,rr=max1;
	while(l<=rr)
	{
		int mid=(l+rr)>>1;
		if(che(mid))l=mid+1;
		else rr=mid-1;
	}
	cout<<rr;
}
```

  

---

## 作者：Adolfo_North (赞：1)

你需要最大化被数量最少的弓箭手保护的墙被弓箭手保护的数量。想到什么，对了，二分答案。

对 $check$ 函数进行思考。

令答案为 $m$。

如果一个点的值小于 $m$，则考虑将其变成 $m$，那么将这一段加在哪里呢？

设位置为：$x$，要加的值为 $y$。贪心一下很显然要将以 $x$ 为起点向右的一段长度为 $2r$ 的区间都加上 $y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/dhrwtb7v.png)

那么如何维护当前的值呢？看到单点查询，和区间加，相信很多人会想到线段树，但其实不用，差分数组即可维护。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n,r,k;
const int N=(5e5+7)*2;
int a[N],b[N],c[N];
int max(int a,int b){
	return (a>b?a:b);
}
bool check(int k2){
	int sum=0;
	for(int i=1;i<=n;i++) c[i]=b[i];
	for(int i=1;i<=n;i++){
		c[i]+=c[i-1];
		if(c[i]<k2){
			//将以x为起点向右的一段长度为2r的区间都加上y.代码中i是x，x是y。
			int x=k2-c[i];
			sum+=x;
			c[i]+=x;
			c[i+2*r+1]-=x;
			if(sum>k) return 0;
		}
	}
	return 1;
}
signed main() {
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int l=0,r2=0,mid,ans;
	cin>>n>>r>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i+r+1]-=a[i];
		b[max(1,i-r)]+=a[i];
		r2+=a[i]+k;
	}
	while(l<=r2){
		mid=(l+r2)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r2=mid-1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Dino_chx (赞：1)

## Part 1. 思路部分

### 1.1

看到类似 **最大的最小** 或 **最小的最大** 光速想到二分答案的。

所以我们来考虑怎么二分答案。

就想二分一个题目里所讲的 **最大化被数量最少的弓箭手保护的墙被弓箭手保护的数量**。 （虽然看起来又臭又长）

### 1.2

在 $i$ 位置的弓箭手可以保护 $|i-j| \le r$ 的墙，所以我们将 $[i-r,i+r]$ 区间加上 $a_i$ 即可。这个第一个初始差分数组，我们叫它 $d1$。

### 1.3

二分最重要的就是 $check$ 函数了，引用我编程教练的一句话就是“二分就是假设”。

在 $check$ 的过程中，你 **假设** 当前想要检查的值为 $x$，将其代入进你的想法，最后看看行不行即可。

我们先约定在 $check$ 函数中进行差分的数组为 $d2$，检测的 **最大化被数量最少的弓箭手保护的墙被弓箭手保护的数量** 为 $x$

我们每次 $check$ 的时候先将 $d2=d1$，也就是恢复一开始的状态。

在每一步操作时先还原 $d2_i$，即 $d2_i=d2_i+d2_{i-1}$；

若当前的 $d2_i<x$，就要增加了呀！因为 `for` 循环是从左到右扫的，则左边的必定是符合了条件的；

我们的代价要先加上 $x-d2_i$，因为我们在 $i$ 这个位置补了 $x-d2_i$ 位弓箭手。相应的，左边已经有序了，右边就有了两个 $r$ 的距离了，所以我们要给 $d2$ 的 $[i,i+r+r]$ 这个区间加上 $x-d2_i$ 的值。（这也是从左到右差分扫的一个好处）

但是这里有个特判：如果当前的代价已经大于 $k$ 了，则必定不可能。（代价只增不减）

最后我们看看代价是否小于等于 $k$ 即可。（直接返回真也是可以的）

### 1.4

如果你仔细看了数据，则你会发现二分的右边界最保险的值应该是 $\sum\limits_{i=1}^{n}a_i+k$。但是其值约等于 $2 \times 10^{18}$，则直接写 $2 \times 10^{18}$ 是绝对没问题的！

左边界正常为 $0$

## Part 2. 代码部分

2.1

```cpp
#include<bits/stdc++.h> //没有注释的代码不是好代码
#define int long long 
using namespace std;
const int N=5e5+7;
int n,r,k,a[N],d1[N],d2[N];
void update1(int L,int R,int P) //区间加 
{
	d1[L]+=P;
	d1[R+1]-=P;
	return;
}
void update2(int L,int R,int P)
{
	d2[L]+=P;
	d2[R+1]-=P;
	return;
}
bool check(int x)
{
	for(int i=1;i<=n;i++)     //copy过来，给它覆盖了 
	{
		d2[i]=d1[i];
	}
	int res=0;
	for(int i=1;i<=n;i++)
	{
		d2[i]+=d2[i-1];        //渐渐还原回去 
		if(d2[i]<x)       
		{
			res+=x-d2[i];
			update2(i,min(n,i+r+r),x-d2[i]);  //加上，但是不是i+2*r-1，因为守卫当前城堡不消耗距离的 
			if(res>k)
				return false;
		}
	}
	return res<=k;
} 
signed main()
{
	scanf("%lld%lld%lld",&n,&r,&k);  //读入要求的n,r,k 
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		update1(max(1ll,i-r),min(n,i+r),a[i]); 
	}
	int L=0,R=2e18,ans=-1;      //右边界整我2.5年 
	while(L<=R)
	{
		int mid=L+((R-L)>>1);
		if(check(mid))
		{
			L=mid+1;
			ans=mid;
		}
		else
			R=mid-1;
	}
	printf("%lld",ans);
    return 0;
}
```

### 2.2

在上述代码中，会发现取左边界我用了 $\max(1,i-r)$，右边界我用了 $\min(n,i+r)$ 和 $\min(n,i+r+r)$ 这就防止了越界。

## 3. 致谢

感谢您的观看，不妨点个赞！

抄题解可不是一个好习惯……


---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF954G)
## 思路
给出一种不需要差分的二分方法，目前是最优解。

首先这个题目显然是个二分，这个大家应该都知道。

设我们当前要 $\verb!check!$ 的值是 $x$，我们可以维护一个队列 $q$，类似于滑动窗口，当队头的编号已经小于 $i-r$ 时，弹出队头，然后每次加入 $i+r$，动态维护队列的和即可。

若遇到某一个时刻 $i$ 不满足条件，则在 $i+r$ 处加上当前缺少的值，因为反正这个位置需要加，而前面的位置已经满足条件，不妨把加的位置移到最后面，因为这样可以覆盖尽可能多的点。

时间复杂度 $O(n \log k)$。
## 代码
```cpp
/*
A tree without skin will surely die. 
A man without face is invincible.
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=5e5+10;
int a[N],n,r,k,q[N],b[N];
inline bool check(int x){
    for (int i=1;i<=n;++i) b[i]=a[i];
    int l=1,rr=0,summ=0,now=0;
    for (int i=1;i<=r;++i) q[++rr]=i,summ+=a[i];
    for (int i=1;i<=n;++i){
        while (q[l]<i-r && l<=rr) summ-=a[q[l++]];
        if (i+r<=n) q[++rr]=i+r,summ+=a[i+r];
        if (summ>=x) continue;
        int delta=x-summ;
        a[min(i+r,n)]+=delta;summ+=delta;
        now+=delta;
        if (now>k){
            for (int i=1;i<=n;++i) a[i]=b[i];
            return 0;
        }
    }
    for (int i=1;i<=n;++i) a[i]=b[i];
    return now<=k;
}
signed main(){
    //读入
    int l=0,rr=2e18;
    while (l<rr){
        if (l+1==rr){if (check(rr)) l=rr;break;}
        int mid=(l+rr)>>1;
        if (check(mid)) l=mid;else rr=mid-1;
    }
    //输出
    return 0;
}
```


---

## 作者：VenusM1nT (赞：1)

非常清真的二分答案。  
![](https://t1.picb.cc/uploads/2020/10/26/tYAt1r.png)

看到“最小值的最大值”，考虑二分答案 $\text{mid}$。记 $a_i$ 为每个点的权值，考虑对于每个 $a_i<\text{mid}$ 贪心，对于当前点，它前面的点全部已经满足条件，那么这个区间肯定越右边越优，于是对 $[i-r,i+r]$ 这个区间的权值 $+(\text{mid}-a_i)$，最后判断 $k$ 个 archer 还有没有得剩就可以了。  
![](https://t1.picb.cc/uploads/2020/10/26/tY898y.png)

```cpp
#include<bits/stdc++.h>
#define N 500000
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,r,k,sum[N+5],a[N+5],c[N+5];
inl bool Check(reg int mid)
{
	memcpy(c,a,sizeof(a));
	reg int x=k;
	for(reg int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+c[i];
		if(sum[i]<mid)
		{
			reg int y=mid-sum[i];
			c[i]+=y;
			c[min(i+r*2+1,n+1)]-=y;
			x-=y;
			sum[i]+=y;
			if(x<0) return 0;
		}
	}
	return 1;
}
signed main()
{
	scanf("%lld %lld %lld",&n,&r,&k);
	for(reg int i=1;i<=n;i++)
	{
		reg int x;
		scanf("%lld",&x);
		a[max(i-r,1ll)]+=x;
		a[min(i+r+1,n+1)]-=x;
	}
	reg int l=0,r=1ll<<62,ans;
	while(l<=r)
	{
		reg int mid=(l+r)>>1;
		if(Check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：开始新的记忆 (赞：1)

题目大意：现在有n个城墙，第i个城墙上有ai个弓箭手，每个弓箭手的防御半径为r，也就是说当ai在x号城墙时，ai可以防御(x-r)到(x+r)号城墙，现在你有k个弓箭手可以增派，问你被数量最少的弓箭手保护的墙被弓箭手保护的数量最大是多少。

大致思路：看到最小的最大（最大的最小），想到二分答案，注意边界的大小，应该是所有弓箭手总和+k（我一开始开1e18WA了）于是乎我们发现每个弓箭手的影响都是一个区间，想到可以用差分O(1)修改，对于每个弓箭手，我们可以利用一个数组（我这里用ans），来表示差分情况（差分：c[i]=a[i]-c[i-1]，每次修改l到r的区间都加上x我们只需要将c[l]+=x，c[r+1]-=x即可）。对于每个答案，我们从第一个城墙开始判断，记得把差分的情况加上，如果不够当前二分的答案，那么判断可不可以用弓箭手增援，因为之前的城墙都已经OK，所以我们可以贪心，不妨令当前的弓箭手使得他的边缘处于这个点即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,ans[1000010],an[1500010];
int n,r;

bool check(long long x)
{
	long long anss=0,num=0;
	memset(an,0,sizeof(an));
	for(int i=1;i<=n;++i)
	{
		anss+=an[i]+ans[i];
		if(anss<x)
		{
			long long t=x-anss;
			if(num+t>k)
				return false;
			num+=t;
			anss+=t;
			an[i+2*r+1]-=t;
		}
	}
	return true;
}

int main()
{	cin>>n>>r>>k;
	long long le=0,ri=k,mid;
	for(int i=1;i<=n;++i)
	{
		long long x;
		cin>>x;
		ri+=x;
		ans[max(1,i-r)]+=x;
		ans[i+r+1]-=x;
	}
	while(le<=ri)
	{
		mid=(le+ri)>>1;
		if(check(mid))
			le=mid+1;
		else
			ri=mid-1;
	}
	cout<<ri<<endl;
	return 0;
}
```


---

## 作者：Priestess_SLG (赞：0)

考虑二分答案 $p$，然后计算每一个位置被覆盖的次数 $c$：

+ $c\ge p$，则此时这个位置符合条件，不需要执行操作。
+ $c<p$，则此时这个位置需要执行操作：
  + 因为当前位置之前的所有位置已经通过执行操作，得到了 $\ge c$ 的覆盖次数，所以如果再覆盖前面的地方就相对浪费。考虑贪心的在弓箭手能够覆盖到当前位置的前提下尽可能贪心的右移，容易证明这是正确的。
 
使用 BIT 后差分等 ds 在线维护，时间复杂度为 $O(n\log^2n)$，可以通过该问题。

---

