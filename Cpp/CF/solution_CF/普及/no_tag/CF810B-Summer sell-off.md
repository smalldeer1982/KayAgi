# Summer sell-off

## 题目描述

商店在n天中出售商品。对于第i天，出售ki件商品，会有有li个顾客购买商品。每个顾客买且只买一件商品。

商店的老板会选择f天。在这f天中，每天出售的商品数量为原来出售商品数量的两倍。老板想知道，如何选择这f天，能使出售的商品最多

## 样例 #1

### 输入

```
4 2
2 1
3 5
2 3
1 5
```

### 输出

```
10```

## 样例 #2

### 输入

```
4 1
0 2
0 3
3 5
0 6
```

### 输出

```
5```

# 题解

## 作者：skyskyCCC (赞：2)

## 前言。
一道贪心题。
## 分析。
首先我们可以想到，因为 $f$ 是一定的，而 $l_i$ 也是一定的，所以我们可以考虑通过排序，让尽可能多的 $k_i$ 满足 $l_i$ 从而实现卖出的最多。

所以我刚开始用 $l_i$ 从小到大排序，但我发现样例一中，最大化的利益是使第三天乘二，这样可以满足 $3$ 个人的需求，而如果用较大的 $l_i$ 进行运算，第四天则只能满足 $2$ 个人，所以这个思路不严谨，但是给了我们一个启发。

我们既然要考虑全部，所以我们可以让每个 $k_i$ 都乘二，然后计算可以比原来多出售多少商品，为了使利益最大化，我们就要将多售出的商品从大到小排序，然后选择最大的 $f$ 个，从而实现利益最大化。

那我们如何进行预处理呢。

首先考虑 $k_i$ 大于等于 $l_i$ 的情况：因为商品数能够满足所有消费者，所以对答案的贡献就为 $l_i$ 个，此时再乘二没有意义。

其次考虑 $k_i$ 小于 $l_i$ 的情况：
- 首先，如果出现 $k_i \times 2$ 的结果**仍**小于或等于 $l_i$ 的情况，那么如果它乘二，对于答案就贡献了它乘过之后的又一个 $k_i$ 个。
- 其次，如果出现 $k_i \times 2$ 的结果大于 $l_i$ 的情况，因为 $l_i$ 是一定的且每个人都可以买到，原先可以售出 $k_i$ 个，所以我们就可以预处理出它的多售商品数为 $l_i - k_i$ 个。

然后因为我们一定在每天，无论乘不乘二，都会售出 $k_i$ 个，所以每天加上即可。最后加上多售商品数最多的 $f$ 天的总数量。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,f;
//int k[100005],l[100005];
long long ans;//注意开long long。
struct node{
	int k,l,sum;
}bc[100005];
bool cmp(node x,node y){
	 return x.sum>y.sum;
}
int main(){
	cin>>n>>f;
	for (int i=1;i<=n;i++){
		//cin>>k[i]>>l[i];
		cin>>bc[i].k>>bc[i].l;
		if(bc[i].l>bc[i].k){
			if(bc[i].k*2>bc[i].l){
				bc[i].sum=bc[i].l-bc[i].k;
			}
			else bc[i].sum=bc[i].k;
			ans+=(long long)bc[i].k;
		}
		else ans+=(long long)bc[i].l;
	}
	sort(bc+1,bc+n+1,cmp);
	//for (int i=1;i<=n;i++){
		//cout<<bc[i].k<<" "<<bc[i].l<<"\n";
	//}
	sort(bc+1,bc+1+n,cmp);
	for (int i=1;i<=f;i++){
		ans+=(long long)bc[i].sum;
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：mxxby (赞：0)

# 题目介绍

[题目传送门](https://www.luogu.com.cn/problem/CF810B)

商店在 $n$ 天中出售商品。对于第 $i$ 天，出售 $k_i$ 件商品，会有有 $l_i$ 个顾客购买商品。每个顾客买且只买一件商品。

商店的老板会选择 $f$ 天。在这 $f$ 天中，每天出售的商品数量为原来出售商品数量的两倍。老板想知道，如何选择这 $f$ 天，能使出售的商品最多。

注意：是选 $f$ 天，**不是连续的** $f$ 天。（我就被坑了。）

# 思路

计算每天商品翻倍所能多提供的利益，再选取最大的 $f$ 天的值，即：

```
ly[i]=min(js[i]*2,rs[i])-min(js[i],rs[i]);
```

因为商品再多，但顾客少，也只能买 $l_i$ 件，顾客多，商品少，则只能买 $k_i$ 件，也就是两者的较小值，商品翻倍同理。两者相减即多出来的利益。

# 代码

```c++
#include<bits/stdc++.h>
#define lon long long//开long long保险
using namespace std;
lon n,k,js[100010],rs[100010],ly[100010],l;//n天，k天翻倍，每天js[i]件商品，rs[i]个顾客，翻倍能多获得ly[i]的利益，总共最多l的利益
bool cmp(lon a,lon b){return a>b;}//从大到小将利益排序
int main(){
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld %lld",&js[i],&rs[i]);
		ly[i]=min(js[i]*2,rs[i])-min(js[i],rs[i]);//计算当天翻倍能赚到的多利益
	}
	sort(ly+1,ly+1+n,cmp);排序
	for(int i=1;i<=k;i++) l+=ly[i];//计算多出的利益
	for(int i=1;i<=n;i++) l+=min(js[i],rs[i]);//计算原本不翻倍能得到的利益
	printf("%lld",l);//输出
	return 0;//收拾残局
}
```

~~蒟蒻的第五篇题解一审，求过 qwq。~~

---

## 作者：2012zxt (赞：0)


# 1.思路

本题是一道**贪心**题。

我们可以发现，第 $i$ 天可以卖的货物个数是 $h_i$ 和 $l_i$ 的较小值。

而如果决定了今天卖双倍的份的话，那第 $i$ 天可以卖的货物个数是 $h_i \times 2$ 和 $l_i$ 的较小值了。

所以如果我们贪心**卖双份比卖一份多的量**而不是**卖双份的量**的话，就可以得到最大值了。

所以喜闻乐见的代码就出来力！

# 2.代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,f,k[100005],l[100005];
bool vis[100005];
struct node{
	int ans,m;
}a[100005];
bool cmp(node x,node y){
	return x.m>y.m;
}
signed main(){
	cin>>n>>f;
	int sum=0;
	for(int i=1;i<=n;i++){
		cin>>k[i]>>l[i];
		sum+=min(k[i],l[i]);//直接加就好了
		a[i].m=min(k[i]*2,l[i])-min(k[i],l[i]);//增加的值
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=f;i++)//增加的加入答案
		sum+=a[i].m;
	cout<<sum;
	return 0;
}
```

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF810B)

**本题坑点：**

留心数据范围，要开 ````long long````，否则第 $9$ 个测试点过不去。

有可能当日顾客的需求会比当日库存要多。

有可能当日顾客的需求的两倍比当日库存要多。

**思路：贪心**

观察题目，我们可以发现，一天销售数量是 $k_i$ 与 $l_i$ 之间的最小值（要么没人买，要么没货卖）,那么同理，当选择 $f$ 天库存增加 $1$ 倍，那么当天增加的售货量就是 $k_i\times2$ 与 $l_i$ 之间的最小值减去原本一天的销量（$k_i$ 与 $l_i$ 之间的最小值）。找出最大的 $f$ 个增加的售货量并且累计进本来售货量的总和中即可。


**代码部分：**

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	long long a[100001],l[100001],f[100001],n,ans=0,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
	cin>>a[i]>>l[i];
	f[i]=min(l[i],a[i]*2)-min(a[i],l[i]);//增加的销量
	ans+=min(a[i],l[i]);//原来的销量总和
	}
	sort(f,f+n);//排序
	for(int i=n-1;i>n-m-1;i--) ans+=f[i]//计入总和中;
	cout<<ans;
	return 0;
}
```




---

## 作者：Orange_Sky_Fish (赞：0)

## 思路
这道题可以用贪心做。

我们先求出每天翻倍能多卖多少商品，然后降序排序。

前几天要加上多卖出去的，然后把所有商品原本能卖出的再加上，这道题就可以 AC 了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(long long a,long long b){
	return a<b;
}
long long k[100001],l[100001],ans[100001],n,f,i,ansb=0;
int main(){
	scanf("%lld%lld",&n,&f);
	for(i=1;i<=n;i++){
		scanf("%lld%lld",&k[i],&l[i]);
	    ans[i]=min(k[i]*2,l[i])-min(k[i],l[i]);
		ansb+=min(k[i],l[i]);
	}
	sort(ans+1,ans+1+n,cmp);
	for(i=1;i<=f;i++){
		ansb+=ans[i];
	}
	printf("%lld",ansb);
	return 0;
}//拒绝ctj,从你我做起！！！
```


---

## 作者：晨·曦 (赞：0)

### -分析
$\because$ 每个顾客都**买且只买一个**商品，
$\therefore$ 每天卖出的商品数量即为 $min (k_i,l_i)$ 。

然后把每天卖出的商品数量都累加到 $ans$ 里，再存每天如果翻倍增加了多少销售量，即 $min (k_i\times2,l_i)-(k_i,l_i) $ ，用 `sort` 排出增加的销售量最多的前 $f$ 天，累加到 $ans$ 里即可。

这里提供结构体的做法，其实差不多。

### -代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long c;
	long long p;
}a[100010];
bool cmp(node x,node y) { //结构体从大到小排序
	return x.c>y.c;
}
long long ans;
int main(){
	long long n,f;
	cin>>n>>f;
	for(long long i=1;i<=n;i++) {
		long long x,y;
		cin>>x>>y;
		a[i].p=min(x,y); // p是每天的销售量
		a[i].c=min(x*2,y)-a[i].p; // c是每天如果翻倍增加的销售量
		ans+=a[i].p;
	}
	sort(a+1,a+n+1,cmp);
	for(long long i=1;i<=n;i++) { // 累加前f天
		if(i<=f) ans+=a[i].c; 
		else break;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：_HiKou_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF810B)

很简单的一道题目，直接模拟即可。

思路：

1. 输入。先把目前可以售出的商品，即 $min(k[i],l[i])$ 加到答案里。
2. 把这天的商品数量翻倍可以售出 $min(k[i]×2,l[i])$ 的商品，定义一个 $w$ 数组用来存：翻倍后可以增加多少售出的商品，列出式子为： 
$$w[i]=min(k[i]×2,l[i])-min(k[i],l[i])$$
3. 把 $w$ 数组从小到大排序。把前 $f$ 个数据加到答案里。
4. 输出。

唯一一个要注意的是因为 $0≤ki,li≤10^9$ 且 $1≤n≤10^5,0≤f≤n$，会爆 int，所以要开 long long。

~~不开 long long 见祖先~~

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k[114514],l[114514],w[114514];//恶臭数组
bool cmp(long long a,long long b){//从大到小排序
	return a>b;
}
int main(){
	long long n,f,i,ans=0;
	scanf("%lld%lld",&n,&f);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&k[i],&l[i]);
		w[i]=min(k[i]*2,l[i])-min(k[i],l[i]);//计算 w 数组
		ans+=min(k[i],l[i]);
		
	}
	
	sort(w+1,w+1+n,cmp);
	for(i=1;i<=f;i++)ans+=w[i];
	printf("%lld",ans);
	
	
	
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

### 思路

很明显，每天的售货量由当天的存货量和顾客数量的最小值决定。如果没有那两倍商品的 $f$ 天，总售货量肯定是个定值。所以，从商店的角度考虑，就必须得要让这 $f$ 天售货量的 **增加值** 最多，这样才能够带来最终最大的总售货量。

这是一个 **贪心** 的过程，可以利用排序来选出售货量增加最多的前 $f$ 天，让那几天的存货量翻倍，再计算出最后的结果即可。时间复杂度 $O(n\log n)$ 。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Maxn=1e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m; ll ans;
struct Node{int k,l;} t[Maxn+5];
bool operator<(Node x,Node y) // 重载运算符来排序
{return min(x.k*2,x.l)-min(x.k,x.l)>min(y.k*2,y.l)-min(y.k,y.l);}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i) t[i].k=read(),t[i].l=read();
    sort(t+1,t+n+1);
    for(int i=1;i<=n;++i)
    {
        if(i<=m) ans+=min(t[i].k*2,t[i].l);
        else ans+=min(t[i].k,t[i].l);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：yxy666 (赞：0)

这道题应该是贪心的题目吧。我们先求出如果我在这天翻倍能多卖多少商品，然后从大到小排序，前 $f$个要加上这多卖出去的商品，然后所有商品原本能卖出的量都要加上。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long ans;
struct yan{
	int x,y,z;bool operator<(const yan b)const{return z>b.z;}
}a[100005]; //重载小于号
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read(),a[i].z=min(a[i].x*2,a[i].y)-min(a[i].y,a[i].x);//求出多卖的量
	sort(a+1,a+1+n);
	for(int i=1;i<=m;i++)ans+=a[i].z;//加前f个
	for(int i=1;i<=n;i++){
		ans+=min(a[i].y,a[i].x);
	}//全都加上
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：锦瑟，华年 (赞：0)

# _本题思路：贪心 +排序_ 

好了，我们来讲讲怎么贪心吧。

首先，对输入的每组数据进行预处理，即计算商品数乘二的话，最多可以比原来多出售多少商品。然后对预处理完的值进行排序，当然了，要从大到小进行排序。最后，先加上原来商品数不变的情况下可以卖出的商品数，再加上前 $f$ 个排序后的预处理的值，最后输出即可。

那么，怎么预处理呢？这里，我们要分类讨论：

1.如果商品数大于销售数，则预处理的值计0；

2.如果商品数小于销售数的话，那么我们判断：(1)如果商品数乘二后大于销售数，则预处理的值是销售数减去原来的商品数；（2）如果商品数乘二后小于销售数，则预处理的值计原来的商品数。（因为比之前多出来了一个原来的商品数）。

好了，废话不多说，上代码：

	#include<stdio.h>
	#include<algorithm>
	using namespace std;
	struct thing{//结构体
		int a,b,c;
	}f[100005];
	bool cmp(thing x,thing y){//cmp函数，从大到小排
		return x.c>y.c;
	}
	int main(){
		int n,m,i;
		long long ans=0;
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++){
			scanf("%d%d",&f[i].a,&f[i].b);
			if(f[i].b>f[i].a){//预处理+计原来最多卖出的商品数
				if(2*f[i].a>f[i].b)f[i].c=f[i].b-f[i].a;
				else f[i].c=f[i].a;
				ans=ans+1ll*f[i].a;
			}
			else{
				ans=ans+1ll*f[i].b;//由于全局变量初值为0，所以无需预处理值，只需计原来最多卖出的商品数即可
			}
		}
		sort(f+1,f+1+n,cmp);//排序
		for(i=1;i<=m;i++){
			ans=ans+1ll*f[i].c;//再加上多可以销售出的商品数
		}
		printf("%lld",ans);//输出
		return 0;
	}
    
好了，大家应该都看明白了吧。题解over~~, byebye , (^_^) 。

---

