# [USACO21OPEN] Acowdemia S

## 题目描述

由于对计算机科学的热爱，以及有朝一日成为 「Bessie 博士」的诱惑，奶牛 Bessie 开始攻读计算机科学博士学位。经过一段时间的学术研究，她已经发表了 $N$ 篇论文（$1 \leq N \leq 10^5$），并且她的第 $i$ 篇论文得到了来自其他研究文献的 $c_i$ 次引用（$0 \leq c_i \leq 10^5$）。

Bessie 听说学术成就可以用 $h$ 指数来衡量。$h$ 指数等于使得研究员有至少 $h$ 篇引用次数不少于 $h$ 的论文的最大整数 $h$。例如，如果一名研究员有 $4$ 篇论文，引用次数分别为 $(1,100,2,3)$，则 $h$ 指数为 $2$，然而若引用次数为 $(1,100,3,3)$ 则 $h$ 指数将会是 $3$。

为了提升她的 $h$ 指数，Bessie 计划写至多 $K$ 篇综述（$0 \leq K \leq 10^5$），并在每篇综述中引用许多她曾经写过的论文。然而，由于页数限制，她至多可以在一篇综述中引用 $L$ 篇论文（$0 \leq L \leq 10^5$）。当然，一篇综述中她只能引用一篇论文至多一次（但是一篇论文可以在多篇综述中被引用）。

请帮助 Bessie 求出在写完这些综述后她可以达到的最大 $h$ 指数。Bessie 不可以在一篇综述中引用她写的其他综述。

注意 Bessie 的导师可能会告知她纯粹为了提升 $h$ 指数而写综述存在违反学术道德的嫌疑；我们不建议其他学者模仿 Bessie 的行为。

## 说明/提示

#### 样例说明

在这个样例中，Bessie 可以写至多一篇综述。如果 Bessie 引用她的第一、第三、第四篇论文中的任意一篇，她的 $h$ 指数会变为 $2$。

#### 测试点性质：

- 测试点 $1 \sim 6$ 满足 $N\le 100$。
- 测试点 $7 \sim 16$ 没有额外限制。

#### 说明

供题：Dhruv Rohatgi

## 样例 #1

### 输入

```
4 4 1
1 100 1 1```

### 输出

```
3```

# 题解

## 作者：fangzirui1 (赞：9)

### 题意分析：
首先，本题要求的是 $h$ 指数，可以用二分答案来做，最大里找最小。
当然在二分之前，先要把题中的 $c$ 数组排序。


------------

### 现在关键就是 check 函数的问题。
 1. 我们可以定义一个变量 $s$，来表示需要引用的论文数量；
 2. 循环 $1$ 到 $n$，计算还需引用几次第 $i$ 篇论文几次；
 3. 若引用次数大于题目中的 $K$，则直接返回 $0$，说明该答案不可行；
 4. 循环结束后判断 $s$ 是否大于论文引用次数上限，若大于，返回 $0$，若小于或等于，返回 $1$。
 

------------

### 本人代码：
```cpp
#include<bits/stdc++.h>
using namespace std; 
long long n,m,k,a[100010];//最好用 long long,反正内存不会超

bool check(int x)
{
    long long s=0;
    for(int i=1;i<=n;i++){
        if(a[i]<x){
            s+=x-a[i];
            if(x-a[i]>m) return 0;
        }
        if(s>m*k) return 0;
        if(i==x) return 1;
    }
}//判断函数，二分中最关键的部分

bool cmp(const int &x,const int &y)
{
    return x>y;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n,cmp);//快排函数
    int l=0,r=n;
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid)) l=mid;
        else r=mid-1;
    }//二分模板
    cout<<l<<"\n";
    return 0;
}
```


---

## 作者：tiger2005 (赞：8)

### 题意简述

有一个序列 $a$，你可以操作 $K$ 次，每次将不超过 $L$ 个位置上的数字加上 $1$，求出最大的 $h$，使得有至少 $h$ 个 $a_i \geq h$。

### 分析

这一题是铜组 T1 的加强版。我们还是使用二分的方法，但是这一次我们将 $[mid-K,mid-1]$ 范围中的数字取出，问题转换为可以在这些数字中总共加上 $K*L$，求出最多的到达 $mid$ 的数字数量。此时直接从大到小加即可。

关于正确性：我们并不可以保证这样加是正确的，因为有一个数可能在一轮中加了两次。下面提供一种证法。将 $K$ 次的选择排成 $K*L$ 的表格，然后从左到右从上到下填入选择的数字：

```
\---L---
| 1 2
| 1 |
K 2 v
| 2
| 2
```

由于一个数字被填进去的次数不超过 $K$ 次，所以没有两个数字出现在同一行内，证明完毕。

关于方法：可以使用 `map` 记录差距，每次取出差距为 $i$ 的有 $j$ 个后，直接进行判断即可（具体来讲就是判断 $curr$ 和 $i*j$ 的大小，详见代码）。由于最劣方案就是 `1,2,3,...`，但是总数不超过 $\sqrt K$，所以速度是相当可观的。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;
int N,K,L;
int C[100010];
map<int,int> mp;
bool check(int m){
	int x=0,y=0;
	for(int i=1;i<=N;i++)
		if(C[i]>=m)	++x;
		else if(C[i]>=m-K)	mp[m-C[i]]++;
	long long cnt=1ll*K*L;
	for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++){
		if(cnt<=1ll*(it->first)*(it->second)){
			y+=cnt/(it->first);
			break;
		}
		cnt-=1ll*(it->first)*(it->second);
		y+=(it->second);
	}
	mp.clear();
	return x+y>=m;
}
int main(){
	scanf("%d%d%d",&N,&K,&L);
	for(int i=1;i<=N;i++)	scanf("%d",&C[i]);
	int l=0,r=N+1,m;
	while(l<r-1){
		m=(l+r)>>1;
		if(check(m))	l=m;
		else	r=m;
	}
	printf("%d",l);
	return 0;
}
```

---

## 作者：huangboming (赞：7)

### 前言
我有一个不用二分，极其简单的方法。

### 题意
给一个序列 $a$，你可以操作 $K$ 次，每次将至多 $L$ 个数字 $+1$ ，求最大的 $h$ 指数，$h$ 指数为有至少 $h$ 个 $a_i \leq h$。如 `1 1 2 2 3` 这里最大的 $h$ 指数为 $2$。因为有 $3$ 个大于等于的数，分别为 `2 2 3`，而且 $3>2$，所以成立。而 $3$ 不行因为只有 $1$ 个大于等于的数 `3`，而且 $1<3$，所以 $h$ 为 $3$ 不行。

### 分析
首先，我们观察题意。

我们不难发现，题目想我们这么做：

1. 当 $\ge h$ 的数的个数不 $\ge h$ 个时。
2. 先算出在序列中小于 $h$ 的同时最大的 $h-o$ 个数（$o$ 为大于 $h$ 的数的个数）。
3. 将这 $h-o$ 个数的数字大小加起来，叫做 $sum$。
4. 算出 $h \times (h-o)$ 即所需大小的总和减 $sum$ 的值，叫做 $sumi$。
5. 最后比较 $sumi$ 与 $k$，$l$ 大小关系，看一下操作数量够不够。

那么如何用最短的时间求最大的 $h$ 呢?

1. 我们可以先 `sort` 排序数列保证有单调性。（从小到大）
2. 后算出前缀和。
3. 从小到大枚举 $h$ 指数，当 $a_i\ge i$ 时代表这个大小的 $h$ 合法，相反则代表需要进行操作使这 $h-o$ 个数加上 $sumi$。$o$ 在第一次 $a_i<i$ 时使其等于 $i$。而后每次向前遍历 $o$ 直到 $a_o>i$。注意这里的 $o$ 无需更改，因为 `sort` 后的数列有单调性。
4. 最后判断，当 $k$ 要大于等于 $h-o$ 中的最小值，且 $\min(l,n)\times k\ge h\times(h-o)$。如果成立更新 $ans=i$ 即 $h$ 指数。最最后输出 $ans$ 即可。

于是，我们不难调出如下代码。但是，需要注意的是！要特判 $o$ 不为 $0$ 即当我们查找大于当前的 $h$ 的数字的个数（向前遍历）,且要写当 $h$ 指数不变的情况。一般就是 $l=0$ 或是 $k=0$ 即 $k$ 乘上 $l$ 太小了的情况，所以要每次记录更新 $ans$ 即最大的 $h$ 指数。

### 时间复杂度及其证明

时间复杂度：$O(n \log n)$

证明：用到了 `sort` 所以极限情况是 $O(n \log n)$，遍历 h 和前缀和只用 $O(n)$，求 $o$ 时每次循环 $o$ 的大小是不定义循环初始值的，一直遍历下去，所以只用 $O(n)$。
### 本人代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[2000005],x,ans,k,l,qzh[200005],m,o;
bool cmp(ll ai,ll bi){
	return ai>bi;
}
int main(){
	cin>>n>>k>>l;
	if(l>n)l=n;//特判l大于n时则多余的为无意义要舍去
	m=k*l;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n,cmp);//排序数列保证其有单调性（从小到大）
	for(int i=1;i<=n;i++){
		qzh[i]=qzh[i-1]+a[i];
	}//求前缀和
	for(int i=1;i<=n;i++){//从小到大枚举h
		if(a[i]<i){
			for(;a[o]<i&&o;o--){} //求大于h的数有哪些
			if(i*(i-o)-qzh[i]+qzh[o]<=m&&i-a[i]<=k){//判断操作是否够
				ans=i;//更新ans即最大的h指数。
			}
		}
		else {
			ans=i;//更新ans在无需操作时最大的h指数。
			o=i;//记录>h的个数
		}
	} 
	cout<<ans;
	return 0;
}
```

---

## 作者：foryou_ (赞：2)

基本思路：考虑对 $c$ 数组二分答案求解。

## 初始化部分

读入数据。考虑贪心的思想，题目中要求最大的 $h$，因此将 $c$ 数组降序排序即可开始二分。

## 主体部分

二分 $c$ 数组。这里提供一个通用的二分模板：

```cpp
int l=0,r=MAXN;
while(l<=r){
	int mid=(l+r)>>1;
   if(check(mid)) ans=mid,l=mid+1;
   else r=mid-1;
}
```

重点是 $\texttt{check(int x)}$ 函数的设计：

- 定义一个变量 $ans$，记录引用次数。

- 遍历 $c$ 数组，若引用次数还未达到 $x$，则将 $ans$ 加上 $c_i-x$；若 $c_i - x$ 超过了单篇引用次数的上限 $k$，则直接返回 $\texttt{false}$。

- 在循环中，若 $ans > $ 引用次数上限 $k \times l$，则同样也直接返回 $\texttt{false}$。

- 在循环中，若引用次数满足条件的文章数达到了 $x$（$i = x$），则直接返回 $\texttt{true}$。

## 注意事项

- 最好所有变量都开 $\texttt{long long}$，以备不时之需。

## 代码

注释全都为英文，请见谅。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k,l,h;
int c[100031];
bool cmp(int &x,int &y){ return x>y; }

bool check(int x){ //check function
    int ans=0; //the number of citations
    for(int i=1;i<=n;i++){
        if(c[i]<x){
            ans+=(x-c[i]);
            if((x-c[i])>k) return false;
        }
        if(ans>k*l) return false;
        if(i==x) return true;
    }
}

signed main(){
    //init
    scanf("%lld%lld%lld",&n,&k,&l);
    for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
    sort(c+1,c+n+1,cmp); //Sort the C array in descending order
    
    //work
    int l=0,r=n;
    while(l<=r){ //binary search
        int mid=(l+r)>>1;
        if(check(mid)) h=mid,l=mid+1;
        else r=mid-1;
    }
    
    //output
    printf("%lld\n",h);
    return 0;
}
```

---

## 作者：haotian1234 (赞：2)

## 题意暗示
- 你至多能引用一篇综述 $K$ 次，因为每篇综述只能引用一种论文一次。
- 你总共引用的论文不能超过 $K \times L$ 篇，因为每篇综述至多只能引用 $L$ 篇论文。
## 题目分析
这是一道明显的二分答案，主要的心思应该花在判断上面。

首先，你先要把不用在综述中引用就能达到 $h$ 值的论文通通去掉，再把剩下的论文做个判断：

- 需要引用的数量是否超过了 $K$ 篇
- 加上这些需要引用的论文后，总共引用的论文篇数是否超过 $K \times L$ 篇

如果都没有超过，就把这种论文也算进可以达到 $h$ 值的论文

最后，把可以达到 $h$ 值的论文总数与 $h$ 值比较，如果比它大，这个 $h$ 值是满足的。

## 题目坑点
- 需要用 long long，否则最后几个点会炸掉！
- 数组需要排序（从大到小），否则你先把小的几个算进去了到后来就不够用了！（~~本人就被这个坑点坑过，记忆犹新啊~~）

下面就上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,i,a[100100],t,w,bao;//开long long
int pd(int x){
    long long t=0,h=0;
    for (long long i=n;i>=1;i--)
        if (a[i]>=x) t++;//先把不用在综述中引用就能达到$h$值的论文通通去掉
    for (long long i=n;i>=1;i--)
        if (a[i]<x&&x-a[i]<=m&&h+x-a[i]<=m*k) t++,h+=x-a[i];//剩下的论文做个判断
    return (t>=x);
}
int main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for (i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+1+n);//数组需要排序（从大到小）
    t=1;w=n;
    while (t<=w){//二分答案
        int mid=(t+w)/2;
        if (pd(mid)) bao=mid,t=mid+1;
        else w=mid-1;
    }
    printf("%lld\n",bao);
    return 0;
}
```

第一次写题解请大家多多支持

---

## 作者：loliygh (赞：2)

## **思路**

------------

首先考虑暴力，从小到大枚举 $ans$ 并判断是否合法。时间复杂度 $O ( n^2 )$，考虑优化。

### 二分+贪心

#### 1. 二分：

打出暴力之后发现 $ans$ 具有单调性且要求输出最大值，数据范围 $( ans \leqslant 10^5 )$ $( 1 \leqslant n \leqslant 10^5 )$ ，时间复杂度 $O ( n \log n )$，**二分答案适用**。

#### 2. 贪心：

将 $c_{i}$ 从大到小排序，显然越靠前的，在没有达到 $mid$ 的情况下，需要被综述（ $K$ ）引用的次数越少。考虑引用次数，总次数为 $K \times L$ ，**每篇论文最多再被引用 $K$ 次**。

（第一次写题解 qwq）

------------
### 代码
------------

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll n,k,l,a[100005],ans;
bool cmp(ll x,ll y)
{
	return x>y;
}
bool cheak(ll i)
{
	ll cnt=0,tot=k*l;
	//cnt表示符合条件的论文个数，tot表示一共可以引用论文的次数。 
	for(ll j=1;j<=n;j++)
	{
		if(tot<i-a[j]||k<i-a[j]) return false;
		if(a[j]>=i) cnt++;
		else if(tot>=i-a[j]&&k>=i-a[j])//每篇论文被引用的次数最多为K次； 
		{
			cnt++;
			tot-=i-a[j];
		}
		if(cnt>=i)//已经达到要求；
			return true;
	}
	return false;
}
int main()
{
	scanf("%lld%lld%lld",&n,&k,&l);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1,cmp);//从大到小排序（**贪心**） 
	ll l=0,r=n,mid=0;
	while(l<=r)//**二分答案 **
	{
		mid=(l+r)/2;
		if(cheak(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：wangyibo201026 (赞：2)

## 一道二分答案的水题

首先，你必须知道二分答案是什么（否则你来做这题干什么）。

其次，这题目有些坑。

## 坑点

1. 必须排序，因为你综述引用的被引用的文章次数（简称输入的数）越大，那么 $h$ 指数**可能**就会越大，如果不排序，会错几个点。

2. 题目说明最多有 $k$ 篇综述，而每篇综述只能引用 $l$ 篇论文，而且每篇论文只能引用**一次**，但是，每一篇综述都可以引用一篇文章一次，所以你可以看成有一篇综述，能引用 $k * l$ 篇文章，每篇文章能够引用 $k$ 次（题目简化版）。

3. 题目说明 $k ≤ 10 ^ 5$，并且 $l ≤ 10 ^ 5$，所以要开长整型。

## 设计

1. 其中，最小值设为 $-1$，最大值设为$n + 1$。因为最小可能是 $0$，最大可能是 $n$，而最小值要减 $1$，最大值也要加 $1$，所以如上。

2. 检查函数的设计。检查函数，只需判断如果 $c_i$ 大于 $x$，答案加 $1$， 然后如果 $c_i$ 加上 $k$ 大于 $x$ 并且这时的综述可引用次数大于**等于** $k$，答案加 $1$，并将综述可引用次数减去 $x - c_i$。

3. 由于是求最大值，所以如果答案可行，应该是 $l = mid$，并且最后的输出是 $l$。

## 代码

你们最想要的，代码来喽：

```cpp
#include<bits/stdc++.h>

using namespace std;

long long n, l, c[100005], k;   //开long long

bool check(int x){
	long long sum = 0, L = l * k;
	for(long long i = 1; i <= n; i++){
		if(c[i] >= x){     //如果不需要综述引用
			sum++;    //答案++
		}
		else if(c[i] >= x - k && L >= x - c[i]){    //如果可以引用综述
			sum++;
			L -= (x - c[i]);   //综述次数-=(x - c[i])
		}
	}
	return sum >= x;    //如果sum >= x 为真，返回true，否则返回false
}

bool cmp(int x, int y){    //cmp排序函数
	return x > y;
}

int main(){
	cin >> n >> k >> l;
	for(int i = 1; i <= n; i++){
		cin >> c[i];
	}
	sort(c + 1, c + 1 + n, cmp);   //排序
	int l = -1, r = n + 1;    //l和r要设清楚
	while(l + 1 < r){
		int mid = (l + r) / 2;
		if(check(mid)){   //如果可行
			l = mid;
		}
		else{
			r = mid;
		}
	}
	cout << l;    //是输出l
	return 0;
}
```


---

## 作者：_szs9601 (赞：1)

#### 题目大意
题目只要看懂了就很简单，一道很水的二分（但是我看了半个小时）。

有 $N$ 个数，一共有 $k \times L$ 次操作，但每个数字最多只能进行 $K$ 次操作。求出最大的 $h$，使得有至少 $h$ 个 $ai \geq h$。
#### 思路
用二分的方法，直接二分答案 $h$。

我们将原先的数字从大到小排序，若当前数字不到 $h$，则直接将当前数字变成 $h$，同时总操作数减少。

### 注意
**每个数字最多只能进行 $K$ 次操作！**

当总操作数不够时，进行判断。

#### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,k,m,t,w,mid,i,ans,a[100100]; //懒，全改LL
bool cmp(LL x,LL y){return x>y;}
bool check(LL x){ //h
    LL s=0,sum=k*m;
    for(LL i=1;i<=n;i++)
        if(a[i]>=x) s++;
        else if(x-a[i]<=sum&&x-a[i]<=k) s++,sum-=x-a[i]; //当前数到 x 的操作次数符合标准
    return s>=x;
}
int main(){
    scanf("%lld%lld%lld",&n,&k,&m);
    for(i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1,cmp);t=0;w=n+1;
    while(t<=w){
        mid=(t+w)>>1;
        if(check(mid)) t=mid+1,ans=mid;
        else w=mid-1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：best_brain (赞：0)

$\qquad$[题面](https://www.luogu.com.cn/problem/P7557)

$\qquad$读完题后，我们可以发现，随着 $h$ 的增加，有限的增加量内满足要求的论文数就会减少，答案满足**单调性**，所以我们可以进行二分答案求解。

$\qquad$想到了二分 $h$，接下来该怎么判断当前 $h$ 是否合法呢？

$\qquad$首先，为了减少增加次数，肯定要选**引用次数最多**的前 $h$ 篇来满足要求；然后，对于每一篇论文，如果想让它的引用次数达到 $h$ 需要增加的引用次数 $>k$，那么一定达不到要求。因为他同时只能对同一篇论文**至多增加 $k$ 次**；最后，将所有论文的增长次数累加起来，与 $k\times l$ 比较判断能否完成增加即可。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
typedef long long LL;
int n, k, l;
int a[maxn];

inline bool check(int x) {
    int num;
    for(int i = 1; i <= n; i ++) {
        if(a[i] < x) {
            num = i - 1;//找到当前满足的论文数
            break;
        }
    }
    if(num >= x) return 1;//满足的论文数已经达到要求
    LL res = 0;
    for(int i = num + 1; i <= x; i ++) {
        if(x - a[i] > k) return 0;//次数超过 k，必然不满足
        res += x - a[i];
    }
    return res <= 1LL * k * l;
}

int main() {
    scanf("%d%d%d", &n, &k, &l);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    int l = 0, r = n, ans;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}
```


---

## 作者：Usada_Pekora (赞：0)

题意分析：有一个数组 $ c $ ，你可以操作 $ K $  次，每次最多将  $ L $ 个位置上的数字加上 1 ，求出最大的 $ h $ ，使得有至少 $ h $  个 $ c_i \geq h 
 $ 。
 
显然，对于每个 $ c_i $ 有一个累计的操作次数 $ add_i $  ， 且 $0 \leq add_i \leq K  $ ，$ \sum_{i=1}^n add_i \leq L × K $ ， 不满足条件的数列是不合法的 。

考虑贪心的策略，先将 $ c $ 数组排序  ， 从大到小枚举 $ x $ 个 $add_i$ 。取最大的 $ x $ 作为答案 。 时间复杂度为 $ O( n^2 ) $ 。

考虑到答案具有单调性 （如果 $x$ 是可行的 ，则 $x-1$ 也可行 ） 进行二分的优化。复杂度为 $ O(n\log n) $ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,c[100005];
inline bool cmp(int x,int y) {
	return x>y;
}
inline bool check(int x) {
	long long res=0;
	for(int i=1; i<=x; i++) {
		if(c[i]>=x)continue;
		if(x-c[i]>k)return false;
		res+=x-c[i];
		if(res>(long long)l*(long long)k)return false;
	}
	return true;
}
int main() {
	ios::sync_with_stdio(false);
//	freopen("acowdemia.in","r",stdin);
//	freopen("acowdemia.out","w",stdout);
	cin>>n>>k>>l;
	for(int i=1; i<=n; i++)
		cin>>c[i];
	sort(c+1,c+n+1,cmp);
	int L=0,R=n,mid;
	while(L<=R) {
		mid=(L+R)/2;
		if(check(mid))L=mid+1;
		else R=mid-1;
	}
	cout<<L-1;
	return 0;
}
```


---

## 作者：NDFS (赞：0)

以贪心的思想来看可以发现把 $c_i$ 从大到小排序肯定是最优的，排序后可观察出性质：一个合法的 $h$ 指数满足前 $h$ 个 $c_i$ 都不少于 $h$。

根据这个性质考虑二分求解 $h$。对于二分出的 $mid$，把前 $mid$ 个补齐至 $mid$ 所需的代价总和需不大于 $K*L$，单个补齐至 $mid$ 需不大于 $K$。

总的时间复杂度 $O(N \log N)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,l,a[100005];
bool cmp(int a,int b)
{
	return a>b;
}
bool pd(int num)
{
	long long sum=0;
	for(int i=1;i<=num;i++)
	{
		if(a[i]<num)
		{
			if(num-a[i]>k)return 0;
			sum+=num-a[i];
			if(sum>(long long)k*(long long)l)return 0;
		}
	}
	return 1;
}
int main()
{
	scanf("%d%d%d",&n,&k,&l);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	int l=0,r=n,mid,ans=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(pd(mid))l=mid+1;
		else r=mid-1;
	}
	printf("%d",l-1);
	return 0;
}
```



---

## 作者：CrTsIr400 (赞：0)

https://blog.csdn.net/STJqwq/article/details/119718575

考虑二分。

二分一个最大的 mid 值，使 C 数组**经过合法次数的引用**之后能使 $C[mid]\ge mid$ 。  
于是发现一个性质：$C$ 数组**从大到小排序一定是最优的**，引用文章次数一定是最少的。  
从大到小排序显然在判定 mid 时只用找到 $[1,mid]$ 区间内所有小于 $mid$ 的应用几次不就好了吗，花费也是最小的。  
于是考虑如何判定引用次数合法。按照题目定义，单次次数小于等于 $K$ ，多次次数总和小于等于 $K\times L$ 即可。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int inf=1073741823;typedef long long LL;int FL;char CH;template<typename T>bool in(T&a){if(CH==EOF)return 0;for(FL=1,CH=getchar(),a=0;(CH<'0'||CH>'9')&&CH!=EOF;CH=getchar())if(CH=='-')FL=-1;for(;CH>='0'&&CH<='9'&&CH!=EOF;CH=getchar())a=a*10+CH-'0';return a*=FL,1;}template<typename T,typename...Args>int in(T&a,Args&...args){return in(a)+in(args...);}
const int maxn=1e5+5;
int n,k,l,c[maxn];
bool pd(int mid){
	LL res=0;
	for(RI i=mid;i;--i){
		if(c[i]>=mid)break;
		if(mid-c[i]>k)return 0;
		res+=mid-c[i];
	}return res<=1ll*k*l;
}
int main(){
	in(n,k,l);
	for(RI i=1;i<=n;++i)in(c[i]);
	sort(c+1,c+n+1);reverse(c+1,c+n+1);
	int l=1,r=n,mid,ans=-1;
	while(l<=r){
		mid=l+r>>1;
		if(pd(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

有一个序列 $a$，你可以操作 $K$ 次，每次将不超过 $L$ 个位置上的数字加上 $1$，求出最大的 $h$，使得有至少 $h$ 个 $a_i \geq h$。

# 题目分析

答案显然满足单调性，即若 $h+1$ 个 $a_i\ge h+1$ 也能满足 $h$ 个 $a_i\ge h$，又观察到其实就是求最大化最小值，我们可以考虑二分答案。

将 $a$ **降序排列**，这里运用了贪心的思想。理性证明，我们如果不这样就会将操作的次数用在小的身上，很明显是比较亏的。

我们二分一个 $mid$，表示当前序列满不满足操作后有至少 $mid$ 个 $a_i\ge mid$，只考虑排序后的前 $mid$ 个数即可。最后的总操作次数必然小于 $K\times L$，可根据这一点来判断。

注意要开 `long long`。

# 代码

```cpp
// Problem: P7557 [USACO21OPEN] Acowdemia S
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7557
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Date:2022-06-05 21:45
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define int long long
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 1e5 + 5;
int a[N];
int n,m,k;
inline bool check(int now) {
	int sum = 0;
	for (register int i = 1;i <= now; ++ i) {
		if (a[i] < now) {
			sum += now - a[i];
			if (now - a[i] > m) return false;
		}
	}
	return sum <= m * k;
}
signed main(void) {
	n = read(),m = read(),k = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	std::sort(a + 1,a + n + 1,[&](int x,int y)mutable {
		return x > y;
	});//C++11 Lambda
	int l = 0,r = n,ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) l = mid + 1,ans = mid;
		else r = mid - 1;
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

