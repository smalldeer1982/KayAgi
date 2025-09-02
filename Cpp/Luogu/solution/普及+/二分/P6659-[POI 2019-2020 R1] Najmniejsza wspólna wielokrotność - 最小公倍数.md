# [POI 2019/2020 R1] Najmniejsza wspólna wielokrotność / 最小公倍数

## 题目背景

Byteasar 正在准备他的数学考试。

## 题目描述

老师跟他说考试题目中有关于最小公倍数 $\rm lcm$ 的题目，于是他找到了一道题练练手。

给定一个整数 $M$，求一个区间 $[a,b]$ 使得 $M$ 为这个区间所有数的最小公倍数。

因为您很强，所以 Byteasar 在解出来这道题的同时也想问问您这题的答案。

因为 Byteasar 非常爱问问题，所以他要问您 $z$ 组问题。

## 说明/提示

#### 样例说明

对于样例 $1$ 的第一组数据，$12$ 为区间 $[1,4]$ 的最小公倍数。

另一组附加样例见附加文件的 sample.in 和 sample.out。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（18 pts）：$z \le 10$，$M \le 1000$。
- Subtask 2（20 pts）：$z\le 100$，$M \le 10^9$。
- Subtask 3（20 pts）：$z \le 100$，$M \le 10^{18}$。
- Subtask 4（42 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le z\le 10^4$，$1 \le M \le 10^{18}$。

#### 说明

翻译自 [POI 2019](https://sio2.mimuw.edu.pl/c/oi27-1/dashboard/) A [Najmniejsza wspólna wielokrotność](https://sio2.mimuw.edu.pl/c/oi27-1/p/nww/)。

## 样例 #1

### 输入

```
3
12
504
17```

### 输出

```
1 4
6 9
NIE```

## 样例 #2

### 输入

```
5
5
6
7
8
9```

### 输出

```
NIE
1 3
NIE
NIE
NIE```

## 样例 #3

### 输入

```
1
1000000```

### 输出

```
NIE```

## 样例 #4

### 输入

```
1
99999990000000```

### 输出

```
9999999 10000000```

# 题解

## 作者：一只书虫仔 (赞：18)

[P6659 POI 2019 A](https://www.luogu.com.cn/problem/P6659)

#### Description

> 给定一个整数 $M$，求一个区间 $[a,b]$ 使得 $M$ 为这个区间所有数的最小公倍数。        
> 如果有多组解：

> - 输出 $a$ 最小的
> - 如果还有多组解输出 $b$ 最小的

#### Solution

注：以下的不会很大为不大于 $10^9$。

我们可以从区间的大小来考虑最终的区间 $[a,b]$。

- 如果区间大小为 $2$，我们考虑到 $b$ 不会很大，所以我们可以使用二分找到区间 $[a,b]$。
- 如果区间大小为 $3$，我们可以再次分类得到两个结论：

1. 如果 $a$ 为奇数，$M=a(a+1)(a+2)$，$a$ 不会很大。
2. 如果 $a$ 为偶数，$M=\dfrac{a(a+1)(a+2)}{2}$，$a$ 不会很大。

所以我们可以二分找到 $a$。

- 如果区间大小超过 $3$ 个数，我们可以直接枚举区间，因为我们已知 $M$ 的大小不会超过 $10^{18}$，所以我们只需要在枚举的过程中看 $[a,b]$ 的 $\rm lcm$ 超没超过 $10^{18}$ 即可。

~~根据 std 可知~~，可以用 map 存储。

---

## 作者：Dream__Sky (赞：5)

考虑分类讨论。

对于这道题，首先我们想：由于是一段区间的最小公倍数，那么这个区间的长度不会太大，数也不会太大。若在最差情况下，即 $M$ 只由相邻两个自然数的最小公倍数构成（这两个数一定互质），那么这两个数的范围大约是 $\sqrt{M}$ 左右，虽然减小了很多，但还是不能枚举。

那么我们考虑由多个自然数构成，即区间长度大于二。此时数的范围已经减小了很多。即使区间长度为三，数的大小也在 $\lfloor \sqrt[3]{10^{18}}\rfloor \thickapprox  10^6$ 左右。但需要比这个范围略大一些，因为它们不一定都是互质的。

那此时，我们就可以先枚举一个左端点，向右不断拓展，直到最小公倍数超过 $M$ 的上界，即 $10^{18}$。在不断拓展的过程中，记录下对于每一个最小公倍数，它所能取到的最前区间。由于数过大，可以用 map 储存。此时区间的长度是大于二的。

对于长度为二的区间，我们特殊处理。那现在，我们设这个区间的左端点为 $x$，那么右端点就是 $x+1$，要做到 $x\cdot(x+1)=M$。有两种办法，一种是解一元二次方程，判断有没有正整数解，还有一种就是二分。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define gcd(x,y) __gcd(x,y);
using namespace std;
const int INF=1e18;
int T;
map<int,pair<int,int> > mp;
void init()
{
	for(int l=1;l<=1500000;l++)
	{
		int k=l*(l+1);
		for(int r=l+2;;r++)
		{
			k/=gcd(k,r);
			if(k>=INF/r) break;
			k*=r;
			if(!mp.count(k)) mp[k]=make_pair(l,r);
		} 
	}
}
pair<int,int> check(int x)
{
	int l=1,r=1e9;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(mid*(mid+1)>x) r=mid-1;
		else if(mid*(mid+1)<x) l=mid+1;
		else return make_pair(mid,mid+1);
	}
	return make_pair(0,0);
}
signed main()
{
	init();
	cin>>T;
	while(T--)
	{
		int x;
		cin>>x;
		if(mp.count(x)) cout<<mp[x].first<<" "<<mp[x].second;
		else 
		{
			pair<int,int> daan=check(x);
			if(daan.first==0) cout<<"NIE";
			else cout<<daan.first<<" "<<daan.second;
		}
		cout<<"\n";
	}
	return 0;
}


```


---

## 作者：Leonid (赞：5)

[原题](https://www.luogu.com.cn/problem/P6659)

## 题目大意
给出 $M$ 求区间 $[a,b]$ 使得 $\operatorname{lcm} _ {i=a}^b i=M$ 。

## 题目分析
分类讨论。
### 1. 区间长度为 2
问题转化为求解二次方程 $x(x+1)=M$，二分求解即可。
### 2. 区间长度为 3
依旧是解方程，只不过要考虑到三个数的奇偶性。按照这个思路再次分类。

- 当 $a$ 为奇数时，三个数分别为：奇数、偶数、奇数。于是问题变为求解 $x(x+1)(x+2)=M$。

- 当 $a$ 为偶数时，三个数分别为：偶数、奇数、偶数。于是问题变为求解 $\dfrac{x(x+1)(x+2)}{2}=M$。

得出结论：当区间长度大于等于 $3$ 时使用枚举左端点并向右累乘计算即可。

考虑使用 ```map``` 进行左右端点映射。

 _**Code：**_ 
 
 ```cpp
#include<cstdio>
#include<map>

using namespace std;

#define ll long long //注意long long
#define inf (ll)1e18

ll z;
ll m;
struct node{
	ll l,r;
};
map<ll,node>k; //映射

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

node find(ll x){
	ll l=1,r=1e9;
	while(l<=r){
		ll mid=l+r>>1;
		if(mid*(mid+1)<x)l=mid+1;
		else if(mid*(mid+1)>x)r=mid-1;
		else return (node){mid,mid+1};
	}
	return (node){0,0};
} //二分求解问题1

void init(){
	for(ll l=1;l<=1919810;l++){ //恶臭数字（
		ll res=l*(l+1);
		for(ll r=l+2;;r++){
			res/=gcd(res,r);
			if(res>inf/r)break;
			res*=r;
			if(!k.count(res))k[res]=(node){l,r};
		}
	}
} //预处理

int main(){
	init();
	scanf("%lld",&z);
	while(z--){
		scanf("%lld",&m);
		node ans1,ans2;
		ans1=find(m),ans2=k[m];
//		printf("%lld %lld\n",ans2.l,ans2.r);
		if(!ans1.l&&!ans2.l){
			puts("NIE");
			continue;
		}
		else if(!ans1.l&&ans2.l){
			printf("%lld %lld\n",ans2.l,ans2.r);
			continue;
		}
		else if(ans1.l&&!ans2.l){
			printf("%lld %lld\n",ans1.l,ans1.r);
			continue;
		}
		else {
			if(ans1.l<ans2.l)printf("%lld %lld\n",ans1.l,ans1.r);
			else if(ans1.l>ans2.l)printf("%lld %lld\n",ans2.l,ans2.r);
			else {
				if(ans1.r<ans2.r)printf("%lld %lld\n",ans1.l,ans1.r);
				else printf("%lld %lld\n",ans2.l,ans2.r);
			}
			continue;
		}
	} //分类讨论
	return 0;
}
```


---

## 作者：PengDave (赞：3)

看到这道题，原以为是暴力枚举，一看题目难度和数据范围就明白了，这是道数学题（~~其实我是看标签知道的~~）。

---------

好了，言归正传。
# solution
* 首先，区间长度等于 $1$ 是不可能的，具体可以看[这篇题解](https://www.luogu.com.cn/blog/219869/solution-p6659)。
* 当区间长度为 $2$ 时，由于相邻的两个数互质，所以左端点 $x$ 满足 $x(x+1)=m$ 此时化简方程得 $x^{2}+x-m=0$ 用二次方程求根公式取较大的 $\frac{-b+\sqrt{b^{2}-4ac}}{2a}$ 得 $x=\frac{-1+\sqrt{1+4m}}{2}$ 此时判断是否为整数即可。
* 当区间长度大于 $2$ 时，我可以暴力枚举左端点和右端点预处理存在 map 中。

# code
```cpp
#include<iostream>
#include<map>
#include<cmath>
using namespace std;
typedef unsigned long long ll;
map<ll,pair<ll,ll> > s;
const ll INF=1e18;
ll pgcd(ll x,ll y){//gcd
    if(!y){
        return x;
    }
    return pgcd(y,x%y);
}
inline void pdy(ll m){
    ll x=sqrt(1+4*m);
    if(x*x==1+4*m){//判断
        x--;
        if(!(x&1)){//判断
            s[m]=make_pair(x/2,x/2+1);
        }
    }
    return;
}
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll z;
    cin>>z;
    for(ll i=1;i<=2000000;i++){//预处理 i为左端点
        ll ans=i*(i+1);//求出前两个数的lcm
        for(ll j=i+2;;j++){
            ans/=pgcd(ans,j);//为了避免溢出，先除
            if(ans>INF/j){//是否超出最大值，等价于ans*j>INF,但是避免了溢出
                break;
            }
            ans*=j;
            if(!s.count(ans)){//如果先前没记录
                s[ans]=make_pair(i,j);
            }
        }
    }
    while(z--){
        ll m;
        cin>>m;
        //由于区间长的肯定左端点小，所以先看有没有区间较长的解
        if(s.count(m)){
            cout<<s[m].first<<" "<<s[m].second<<"\n";
        }else{
            //没有考虑长度为2时的解
            pdy(m);
            if(s.count(m)){
                cout<<s[m].first<<" "<<s[m].second<<"\n";
            }else{//如果还没有输出NIE
                cout<<"NIE\n";
            }
        }
    }
    cout<<flush;
    return 0;
}
```

---

## 作者：Computer1828 (赞：3)

考虑到 $M \leq 10^{18}$ 且 $19! < 10^{18} < 20!$，所以如果区间有四个数以上时，区间长度最多只有 $19$。还有，当区间仅有 $4$ 个数时，最小数不到 $2.5\cdot 10^5$。

所以对于区间长度大于等于 $4$ 的，直接暴力开 `map` 存下最优的答案即可。

对于长度为 $2$ 的，可以设小一点的数为 $x$，列方程 $x(x+1) = n$ 求解并判断根是否为整数。也可以二分找这个 $x$。

对于长度为 $3$ 的，~~当然也可以解方程~~，继续考虑二分。此时要注意到三个数的奇偶性：如果三个数是“奇—偶—奇”，三个数的 $lcm$ 就是三数相乘；如果三个数是“偶—奇—偶”，三个数的 $lcm$ 应为三数乘积除以 $2$。

至于预处理：

```cpp
map<ll,pair<int,int> > mp;
for(int l = 1;l<=250000;++l){
	ll res = 1ll*l*(l+1);
	for(ll r = l+2;;++r){
		res /= gcd(res,r);
		if(res > inf/r) break;
		res *= r;
		if(!mp.count(res)) mp[res] = make_pair(l,r);
	}
}
```

---

## 作者：LimpidSlirm (赞：2)

## 题意

给定一个数字 $n$，询问下标最小的区间 $[l,r]$ 使得 $\operatorname{lcm}(l,l+1,\dots,r)=n$。

此处下标较小定义为 
$$
\begin{cases}r\lt r^{\prime},&l=l^{\prime}\\l \lt l^{\prime},& \text{otherwise.} \end{cases}
$$
$n \leq 10^{18},t \leq 10^4$。

## Solution

考虑区间长度为 $1$ 的情况，若 $n$ 为奇数，则必然存在区间 $[\frac{n-1}{2},\frac{n-1}{2}+1]$ 小于区间 $[n,n]$ 使得要求成立。若 $n$ 为偶数，则必然存在区间 $[2,\frac{n}{2}]$ 小于区间 $[n,n]$ 使得要求成立。故答案区间长度不可能为 $1$。

考虑区间长度为 $2$ 的情况，显然地，$l$ 与 $r$ 即 $l+1$ 互质，故 $\operatorname{lcm}(l,r)=l\times(l+1)$ 。可以证明，对于 $n=k\times (k+1),k\in N$，答案区间必然为 $[k,k+1]$。显然地，对于 $n \leq 10^{18},k\leq \sqrt{10^{18}}$，且单调递增，可以二分来找到答案。

考虑区间长度大于等于 $3$ 的情况，发现对于极端数据 $n$ 为 $10^{18}$ 级别时，答案区间内的数不会超过 $10^6$ ，故对于 $10^6$ 以下的左端点暴力枚举以及右端点，并使用 map 维护答案。

时间复杂度为 $\mathcal{O}(T \log n)$ 再加上预处理大概是 $\mathcal{O}(4 \times 10^6)$ 的巨大常数，可以通过本题。 

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
map<long long,pair<int,int> > ans;
long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}
void init()
{
	for(int l=1;l<=1500000;l++)
	{
		long long tmp=1ll*l*(l+1);
		for(long long r=l+2; ;r++)
		{
			tmp/=gcd(tmp,r);
			if(tmp>1e18/r)
				break;
			tmp*=r;
			if(ans.count(tmp)==false)
				ans[tmp]=make_pair(l,r);
		}
	}
	return ;
}
void solve(long long k)
{
	long long left=1,right=1e9;
	while(left<=right)
	{
		long long mid=(left+right)>>1;
		if(mid*(mid+1)==k)
		{
			ans[k]=make_pair(mid,mid+1);
			return ;
		}
		else if(mid*(mid+1)>k)
			right=mid-1;
		else if(mid*(mid+1)<k)
			left=mid+1;
	}
	return ;
}
int main(int argc,const char *argv[])
{
	init();
	int T=read();
	while(T--)
	{
		long long n=read();
		if(ans.count(n)==true)
		{
			printf("%d %d\n",ans[n].first,ans[n].second);
			continue;
		}
		solve(n);
		if(ans.count(n)==true)
		{
			printf("%d %d\n",ans[n].first,ans[n].second);
			continue;
		}
		printf("NIE\n");
	}
	return 0;
}
```

### 写在最后

**三年 OI 一场空，不开 long long 见祖宗**。

---

## 作者：Silence_water (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6659)

---

$Analyse$

看到如此数据范围，必将预处理。

容易发现，$19!<10^{18}<20!$，因此可以暴力进行预处理。

当区间长度为 $2$ 时，有 $x\times (x+1)\le10^{18}$，此时 $x$ 的最大值趋近于 $10^9$，时间复杂度过高，无法接受。因为 $x$ 与 $x+1$ 必然互质，故 $\operatorname{lcm}(x,x+1)=x\times(x+1)$。因此其增长具有单调性，考虑二分。

当区间长度为 $3$ 时，进行分类讨论：当 $x$ 为偶数时，$\gcd(x,x+2)=2$，故 $\operatorname{lcm}(x,x+1,x+2)=x\times (x+1) \times (x+2)/2$。当 $x$ 为奇数时，$\operatorname{lcm}(x,x+1,x+2)=x\times (x+1) \times (x+2)$。此时 $x$ 的最大值为 $1259920$。复杂度可以接受。

因此，当区间长度大于等于 $3$ 时，我们直接枚举区间左端点 $l$，向右进行累乘，直至最小公倍数超过 $10^{18}$。

---

$Solution$

对于区间长度大于等于 $3$ 的部分，考虑用 `map` 将 $M$ 对应的左右端点之间映射。

注意求 $\operatorname{lcm}$ 要先除后乘，比较大小也要选择除法！

```cpp
struct node
{
	int l,r;
};
map<ll,node> mp;
void init()
{
	for(ll l=1;l<=1259920;i++)
	{
		ll pe=l*(l+1);
		for(ll r=l+2;;r++)
		{
			pe/=gcd(pe,r);
			if(pe>inf/r)break;
			pe*=r;
			if(!mp.count(pe))mp[pe]=(node){l,r};
		}
	}
}
```

对于区间长度为 $2$ 的部分，使用二分，符合条件直接 `return` 即可。

```cpp
ll to_2(ll x)
{
	ll l=1,r=1e9;
	while(l<=r)
	{
		ll mid=(l+r)>>1ll;
		if(mid*(mid+1)<x)
			l=mid+1;
		else if(mid*(mid+1)>x)
			r=mid-1;
		else return mid;
	}
	return -1;
}
```

---

$The$ $end$

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：Fislett (赞：2)

# 题意

给定一个整数 $M$，求是否存在一个区间 $[a,b]$ 使得 $M$ 为 $[a,b]$ 这个区间中所有数的最小公倍数。

# 解题方法
## 1. 区间长度 $= 2$。
二分查找 $a$，由于相邻的两个数互质， $\operatorname{lcm}$ 等于 $a(a + 1)$。

## 2. 区间长度 $> 2$
此时，发现 $a$ 和 $b$ 都不是很大，$a$ 最大不超过 $1.5 \times 10^6$，可以接受直接预处理的时间复杂度。

因此，我们枚举左端点 $a$，向右进行累乘，直到最小公倍数大于 $10^{18}$。

可以用 map 进行左右端点的映射。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
int n;
long long m;
map<long long, pair<int, int> > M;
long long gcd(long long x, long long y)
{
	return y ? gcd(y, x % y) : x;
}
void init()
{
	for (long long l = 1; l <= 1500000; l ++)
	{
		long long res = (long long)(l * (l + 1));
		for (int r = l + 2; ; r ++)
		{
			res /= gcd(res, r);
			if (res > inf / r) break;
			res *= r;
			if (!M.count(res)) M[res] = make_pair(l, r);
		}
	}
}
pair<int, int> search(long long x)
{
	int l = 1, r = 1e9;
	while (l <= r)
	{
		long long mid = l + r >> 1;
		if (mid * (mid + 1) > x) r = mid - 1;
		else if (mid * (mid + 1) < x) l = mid + 1;
		else return make_pair(mid, mid + 1);
	}
	return make_pair(0, 0);
}
int main()
{
	init();
	scanf("%d", &n);
	while (n --)
	{
		scanf("%lld", &m);
		pair<int, int> ans = M[m];
		if (ans.first)
		{
			printf("%d %d\n", ans.first, ans.second);
			continue;
		}
		ans = search(m);
		if (ans.first) printf("%d %d\n", ans.first, ans.second);
		else puts("NIE");
	}
}
```


---

## 作者：Xiphi (赞：0)

前言：管理员辛苦了，申了好几次。

考虑分类讨论。若一个数 $z$ 可以表示为 $\operatorname{lcm}(x,y)$，则 $x,y$ 都必然在 $\sqrt{z}$ 附近，枚举前后 $20$ 个数即可。若一个数 $z$ 可以被表示为大于等于 $3$ 个连续自然数的 $\rm  lcm$，则自然数个数不大于 $60$ 左右，设每次枚举次数在 $B$ 上下，且首个自然数小于 $z$ 开立方根的值，设其为 $A$，上节在 $10^6$ 上下。很自然的，想到预处理这个东西，枚举 $l$，然后向后扫，若 $\rm lcm$ 大于 long long 范围，则 break，复杂度在 $O(A \times B )$ 这样子。答案用 map 记录即可。注意要开 __int128。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<stack>
#include<string>
#include<cmath>
#include<cstring>
#include<set>
#include<map>
using namespace std;
int T;
map<long long,pair<long long,long long> > ans; 
__int128 gcd(__int128 a, __int128 b) {
    return !b ? a : gcd(b, a%b);
} 

__int128 lcm(__int128 a, __int128 b) {
    return (__int128)a/gcd(a,b)*b;
}
void write(__int128 x) {
if(x<0) putchar('-'),x=-x;
if(x>9) write(x/10);
putchar(x%10+'0');
}
__int128 read() {
__int128 x=0,f=1;
char c=getchar();
while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
return x*f;
}
int main(){
	cin>>T;
	for(int l=1;l<=1300000;++l){
		__int128 Sum=lcm(l,(l+1));
		for(__int128 r=l+2;r<=1300000;++r){
			Sum=lcm(Sum,r);
			if(Sum>(__int128)1e18||Sum<=0) break;
			else if(ans.count(Sum)==0)ans[Sum]={l,r};
		}
	}
	
	while(T--){
		long long x;
		x=read();
		pair<long long,long long> p=make_pair(0x3f3f3f3f,0x3f3f3f3f);
		__int128 flag=0,px=(__int128)sqrt(x);
		__int128 X=px*(px+1ll);
		if(X==(__int128)x){
			p=make_pair((long long)px,(long long)px+1);
//			cout<<p.first;
		}
		for(__int128 j=max((__int128)0ll,px-20ll);j<=px+20ll;++j){
			__int128 Xx=j*(j+1ll);
			if(Xx==x){
				p=make_pair(j,j+1ll);
				break;
			} 
		}
		if(p<ans[x]||(p.first!=0x3f3f3f3f&&ans[x].first==0)) cout<<p.first<<' '<<p.second<<'\n';
		else if(ans.count(x)&&ans[x]!=make_pair(0ll,0ll))cout<<ans[x].first<<' '<<ans[x].second<<'\n';
		else if(ans[x].first==0) puts("NIE");
	}
	return 0;
}

```

---

## 作者：Crazyouth (赞：0)

**分析**

注意到 $\operatorname{lcm}_{i=1}^{43}>10^{18}$，所以区间长度并不会超过 $45$。接下来判断 $l$ 能到多少。若只判断 $2$ 个数的区间，则开头需要枚举到 $10^9$，显然 TLE，所以对于两个数的区间解方程 $x(x+1)=m$ 即可。因此我们只需要枚举到 $\lfloor \sqrt[3]{10^{18}}\rfloor\approx 10^6$ 就行了。

对于一个区间，求出它的 $\operatorname{lcm}$，若已经大于 $10^{18}$，就直接 `break` 当前的循环。求区间 $\operatorname{lcm}$ 公式是对于每一个数，令当前变量 `l=l/gcd(l,j)*j`，其中 $l$ 是当前的区间 $\operatorname{lcm}$，$j$ 是当前要增加到区间内的数。

我们只需要开一个 `map`，key 为 `unsigned long long`，值为 `pair<unsigned long long,unsigned long long>` 就行了。`mp[i]` 表示输入 $i$ 输出的结果。

---

关于方程 $x(x+1)=m$ 的解法，如果你会可以跳过。$x(x+1)=m,\therefore x^2+x=m,\therefore x^2+x-m=0,\because x>0,\therefore x=\frac{-1+\sqrt{1+4m}}{2}$。判断 $\sqrt{1+4m}$ 是不是整数就能判断 $m$ 能不能表示为两个相邻的自然数的乘积（$\operatorname{lcm}$）。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int inf=1e18;
map<int,pair<int,int> > mp;
auto main(void) ->signed
{
	for(int i=1;i<=2e6;i++)
	{
		int lcmm=1;
		for(int j=i;j<=i+45;j++)
		{
			lcmm=lcmm/__gcd(lcmm,j)*j;
			if(lcmm>inf) break;
			if(j-i>=2)
			{
				if(mp[lcmm].first==0) mp[lcmm]=make_pair(i,j);
				else mp[lcmm]=make_pair(min(mp[lcmm].first,i),max(mp[lcmm].second,j));
			}
		}
	}
	int z,m;
	cin>>z;
	while(z--)
	{
		pair<int,int> pr;
		pr=make_pair(1e18,1e18);
		cin>>m;
		if((int)sqrt(1+4*m)*(int)sqrt(1+4*m)==1+4*m)
		{
			pr=make_pair((-1+sqrt(1+4*m))/2,(-1+sqrt(1+4*m))/2+1);
		}
		if(!mp[m].first&&pr.first==1e18)
		{
			cout<<"NIE"<<endl;
			continue;
		}
		if(!mp[m].first)
		{
			cout<<pr.first<<' '<<pr.second<<endl;
			continue;
		}
		pair<int,int> pr2;
		pr2=make_pair(mp[m].first,mp[m].second);
		pair<int,int> pr3;
		pr3=min(pr,pr2);
		cout<<pr3.first<<' '<<pr3.second<<endl;
	}
	return 0;
}

---

## 作者：船酱魔王 (赞：0)

# P6659 题解

## 题意回顾

构造一个区间 $ [a,b] $，满足 $ \operatorname{lcm}\{i\}(i\in[a,b])=M $，多组解则以 $ a $ 为第一关键字，以 $ b $ 为第二关键字排序，输出最小解，多测，$ z $ 组数据。

$ 1 \le M \le 10^{18}, 1 \le z \le 10^4 $。

## 部分分

### subtask1（18pts）

因为 $ z,M $ 很小，所以暴力枚举区间左右端点，判断最小公倍数是否符合要求即可。

### subtask2（20pts）

分类讨论区间长度，当区间长度为 $ 2 $ 时，因为相邻自然数互质，发现 $ l \times (l+1)=m $，二分法或利用求根公式解方程即可。

当区间长度为 $ 3 $ 及以上时，可以发现 $ l,r $ 不大（最多在 $ 2 \times10^3 $ 左右），直接枚举左右边界即可。

### subtask3（20pts）

这个子任务应该是给一些细节处理不好，实现不好的正解的。

## 正解

发现本题关键性质：因为 $ \operatorname{lcm} $ 随区间长度增大呈指数级增长，所以区间不会太长，因此枚举区间的时间复杂度几乎是线性的。提前预处理出以 $ 1 \sim 1.3 \times 10^{6} $ 为左边界的区间的 $ \operatorname{lcm} $ ，因为 $ \operatorname{lcm} $ 随着区间向右拓展值不减，所以当数值超过 $ 10^{18} $ 时，直接 ```break``` 掉枚举右边界的循环即可。用 ```map<long long, pair>``` 存储当 $ \operatorname{lcm} $ 为 $ m $ 时，最优的区间即可。

当区间长度为 $ 2 $ 时，详见 subtask2。

当区间长度为 $ 3 $ 时，发现这三个数不可能出现至少两个数同时被 $ 3 $ 及以上的数整除，但是当第一个数为偶数时，$ \operatorname{lcm}=l \times (l+1) \times (l+2) \div 2 $，否则为三个数的乘积，分类讨论再二分即可。

当区间长度为 $ 4 $ 时，当 $ l\ \bmod\ 3  = 0 $ 时，$ \operatorname{lcm}=l\ \times (l+1) \times (l+2) \times (l+3) \div 6 $，否则为四数乘积除以二。分类讨论+二分法解方程即可。

当区间长度大于 $ 5 $ 时，可证明当 $ \operatorname{lcm} \le 10^{18} $ 时，左边界不可能超过 $ 1.3 \times 10^6 $，因此答案在 ```map``` 里面。

实现细节较多，详见本人 AC 代码。

## AC 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
const long long inf = 1e18;
int T;
long long n;
struct node {
    int l;
    int r;
};
node make(int l0, int r0) {
    node res;
    res.l = l0;
    res.r = r0;
    return res;
}
bool operator<(node p1, node p2) {
    if(p1.l != p2.l) {
        return p1.l < p2.l;
    }
    return p1.r < p2.r;
}
node findans3(long long l, long long r, long long x, int k) {
    long long mid, tmp;
    //L=3l+k
    while(l + 1 < r) {
        mid = (l + r) >> 1;
        tmp = 3 * mid + k;
        if(tmp * (tmp + 1) * (tmp + 2) * (tmp + 3) <= x) {
            l = mid;
        } else {
            r = mid;
        }
    }
    l = 3 * l + k;
    if(l * (l + 1) * (l + 2) * (l + 3) == x) {
        return make(l, l + 3);
    } else {
        return make(1e9, 1e9 + 1);
    }
}
long long gcd(long long x, long long y) {
    if(y == 0) {
        return x;
    }
    return gcd(y, x % y);
}
bool operator==(node p1, node p2) {
    return p1.l == p2.l && p1.r == p2.r;
}
map<long long, node> mp;
int main() {
    cin >> T;
    node ans;
    long long l, r, mid, tmp;
    long long t1;
    for(int i = 1; i <= 1300000; i++) {
    	t1 = i;
    	for(int j = i + 1; j <= i + 50; j++) {
    		t1 = t1 / gcd(t1, j);
    		if(t1 > inf / j) {
    			break;
			}
			t1 *= j;
			if(j >= i + 3) {
				if(mp.find(t1) == mp.end()) {
					mp[t1] = make(i, j);
				}
			}
		}
	}
    for(int ti = 1; ti <= T; ti++) {
        cin >> n;
        ans = make(1e9, 1e9 + 1);
        //n(n+1)=n
        l = 1;
        r = 1e9;
        while(l + 1 < r) {
            mid = (l + r) >> 1;
            if(mid * (mid + 1) <= n) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if(l * (l + 1) == n) {
            ans = make(l, l + 1);
        }
        //n(n+1)(n+2)=n(n=2k+1)
        //[1,1e6)
        l = 0;
        r = 5e5;
        while(l + 1 < r) {
            mid = (l + r) >> 1;
            tmp = mid * 2 + 1;
            if(tmp * (tmp + 1) * (tmp + 2) <= n) {
                l = mid;
            } else {
                r = mid;
            }
        }
        l = l * 2 + 1;
        if(l * (l + 1) * (l + 2) == n) {
            ans = min(ans, make(l, l + 2));
        }
        //n(n+1)(n+2)/2=n(n=2k)
        //[1,1.3*1e6)
        l = 0;
        r = 6.5 * 1e5;
        while(l + 1 < r) {
            mid = (l + r) >> 1;
            tmp = mid * 2;
            if(tmp * (tmp + 1) * (tmp + 2) / 2 <= n) {
                l = mid;
            } else {
                r = mid;
            }
        }
        l = l * 2;
        if(l * (l + 1) * (l + 2) / 2 == n) {
            ans = min(ans, make(l, l + 2));
        }
        //n(n+1)(n+2)(n+3)/6 (n=3k)
        //[1,50000)
        ans = min(ans, findans3(0, 16667, 6 * n, 0));
        //n=n(n+1)(n+2)(n+3)/2 (n=3k+r)
        //[1,38000)
        ans = min(ans, findans3(0, 13000, 2 * n, 1));
        ans = min(ans, findans3(0, 13000, 2 * n, 2));
        if(mp.find(n) != mp.end()) {
        	ans = min(ans, mp[n]);
		}
        if(ans == make(1e9, 1e9 + 1)) {
            cout << "NIE" << endl;
        } else {
            cout << ans.l << " " << ans.r << endl;
        }
    }
    return 0;
}
```

---

