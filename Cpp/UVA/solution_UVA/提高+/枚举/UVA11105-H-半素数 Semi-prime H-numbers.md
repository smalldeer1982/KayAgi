# H-半素数 Semi-prime H-numbers

## 题目描述

# 【问题描述】

形如$4n+1$的数被称为“H数”，乘法在“H数”组成的集合内是封闭的。在这个集合中只能被1和本身整除的数叫做“H-素数”（不包括1），其余的数被称为“H-合数”。一个“H-合成数”是一个能且只能分解成两个“H-素数”乘积的“H-合数”（可能有多种分解方案）。比如$441=21*21=9*49$,所以$441$是“H-合成数”。$125=5*5*5$,所以125不是“H-合成数”。

求$0$~$h$范围内“H-合成数”的个数。

## 样例 #1

### 输入

```
21
85
789
0```

### 输出

```
21 0
85 5
789 62```

# 题解

## 作者：andysk (赞：12)

# POJ3292/UVA11105 H-半素数 Semi-prime H-numbers



 [Luogu RemoteJudge](https://www.luogu.org/problem/UVA11105)

[POJ-Vjudge](https://vjudge.net/problem/POJ-3292#author=0)

[UVA-Vjugde](https://vjudge.net/problem/UVA-11105)


[Blog](https://tony102.xyz/index.php/2019/10/30/poj3292-uva11105-h-%e5%8d%8a%e7%b4%a0%e6%95%b0-semi-prime-h-numbers/)阅读效果更佳

### 题意

给你一个由 $4n+1$ 的数组成的集合，该集合中的数被称为 $H$ 数，集合中的素数是 $H-$ 素数， 两个  $H-$ 素数的乘积组成的数被称为$H-$ 合成数，现在给定一些 $h$ ，求 $[0,h]$ 中的 $H-$ 合成数的个数。



### 题解

在数学一本通里面看到的这题，觉得那个写的太差了啥都没看懂，决定写一发题解。（就是自己太菜了

首先可以想到最朴素的做法就是直接预处理一个 $[1,10^6]$ 的质数表，然后爆找既是两个质数的乘积又满足是 $4n+1$ 组成的数，然后处理一个前缀和。

据说这样是可以过的，但是我也不知道。

可以优化的地方就在找质数这个地方。考虑埃氏筛的过程，我们可以把每次枚举的数改一改，从``i++`` 变为```i+=4```，这样我们每次就枚举的都是 $H$ 数。

据说这样也是可以过的，但是我还是不知道。

引理：若 $i$ 是一个 $H-$ 素数，则 $5i + 4i * x$ 是 $H$ 数但不是$H-$ 素数

证明：设 $i = 4p+1$

由原式可得：$(5(4p+1) + 4(4p+1)*x) \ mod\ 4= 1$

观察后面 $4(4p+1)*x\ mod\ 4 = 1$ ，由同余性质可得：$(4(4p+1)\ mod \ 4) * (x\ mod\ 4)\ mod\ 4 = 1$

显然：$4(4p+1)\ mod \ 4$ 必然等于 $1$ ，根据算术结果，可知 $x\ mod \ 4 = 1$

将$(5(4p+1) + 4(4p+1)*x) \ mod\ 4= 1$ 拆开得到：$(20p+5+x(16p+4))\ mod\ 4 = 1$ , 可知$5i + 4i * x$ 是 $H$ 数。

又因为$5i + 4i * x$ 可以写成：$i(4x+5)$ ，所以$5i + 4i * x$ 不是$H-$ 素数。

证毕。

所以可以再次修改埃氏筛除合数的过程，将范围修改为：$[i*5, 10^6]$ ，并将每次找的数从```j++```修改为```j+=i*4``` 



### Code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int SIZE = 1e6 + 5;

int h, cnt;
int h_prime[SIZE], h_semi[SIZE], vis[SIZE], sum[SIZE];

inline int read()
{
    char ch = getchar();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
    return x * f;
}

inline void init()
{
    for (int i = 5; i <= SIZE - 5; i += 4) {
        if (vis[i]) continue;
        h_prime[++cnt] = i;
        for (int j = i * 5; j < SIZE; j += i * 4) vis[j] = 1;
    }
    for (int i = 1; i <= cnt; i++) 
        for (int j = 1; j <= i && h_prime[i] * h_prime[j] < SIZE; j++) h_semi[h_prime[i] * h_prime[j]] = 1;
    for (int i = 1; i < SIZE; i++) sum[i] = sum[i - 1] + h_semi[i];
}

int main()
{
    init();
    h = read();
    while (h) {
        printf("%d %d\n", h, sum[h]);
        h = read();
    }
    return 0;
}
```

写了介么详细不妨给个赞？



 

---

## 作者：EarthGiao (赞：3)

做这道题之前首先要掌握的是线性筛的模板

附上题目链接
## [这里](https://www.luogu.org/problem/P3383)

首先这道题目的范围有些特殊必须是% 4 == 1的数才行

所以可以这样

直接把线性筛的模板拿过来将里面的每个数挨个枚举，每一次的++i
或者++j可以改为 += 4

这样每一次枚举的就都是“H数 ”了

然后不考虑“H数 ”之外的数，用这里面的数进行素数筛选
将H-素数都筛出来

在最后的时候两重循环枚举素数将他们的乘积标注出来最后
剩下的H数就都会是H-合数了 

完整代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;
const int Max = 1000005;
const int M = 1000001;
int ans[Max];
bool use[Max];
bool vis[Max];
int prime[Max];
int a[Max];
int js = 0;
int main()
{
	int tot = 0;
	for(int i = 5;i <= M;i += 4)
	{
		if(use[i] == true)continue; 
		prime[++ tot] = i;
		for(int j = 1;j * i <= M;j += 4)//线性筛模板晒出H-素数 
			use[i * j] = true;
	}
	for(int i = 1;i <= tot;i ++)
	{
		for(int j = 1;j <= tot;j ++)//双重循环枚举 
		{
			if(prime[i] * prime[j] > M)break;//大于最大的范围break掉这一层循环 
			vis[prime[i] * prime[j]] = 1;//标记出来 
		}
	}
	for(int i = 1;i <= M;++ i)
	{
		ans[i] += ans[i - 1];//先继承前面H-合数的个数 
		if(vis[i] == true)//如果当前的数也是H-合数 
		ans[i] ++;//计数器累加 
	}
	int n;
	while(scanf("%d",&n))
	{
		if(n == 0)break;
		else
		cout<<n<<" "<<ans[n]<<endl;
	}
	return 0;
}
```


---

## 作者：tyr_04 (赞：1)

[传送门](https://www.luogu.com.cn/problem/UVA11105)

题目很容易理解，只需要打表找出所有的 $H$ 素数，然后打表枚举出所有满足条件的 $H$ 合成数，最后用类似前缀和的方式进行累加，就可以得到答案了。

千万要注意 $H$ 素数的最终个数大约为 $20000$ 个左右（本人亲测），所以在枚举满足条件的 $H$ 合成数时要进行优化。由于枚举 $H$ 素数时是由小到大依次枚举的，所以可以在两个 $H$ 素数的积大于 $1000001$ 时停止继续枚举。

注意最后的循环一旦输入到 $0$ 就要停止程序，避免死循环。

这种做法比较极限，不建议按照此思路做，不过这种做法更容易理解。

## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[1000005]={0},a[20005];
int main()
{
    int t,l=0;
    for(int i=5;i*5<=1000001;i+=4)
    {
        bool z=0;
        for(int j=5;j*j<=i;j+=4)
        {
            if(i%j==0&&(i/j)%4==1&&i/j!=1)
            {
                z=1;
                break;
            }
        }
        if(z==0)
        {
            l++;
            a[l]=i;
        }
    }
    for(int i=1;i<=l;i++)
    {
        for(int j=1;j<=l;j++)
        {
            if(a[i]*a[j]>1000001)
            {
                break;
            }
            else
            {
                ans[a[i]*a[j]]=1;
            }
        }
    }
    for(int i=1;i<=1000001;i++)
    {
        ans[i]=ans[i-1]+ans[i];
    }
    int n;
    while(cin>>n)
    {
    	if(n==0)
		{
			break;
		}
        printf("%d %d\n",n,ans[n]);
    }
    return 0;
}
```

---

## 作者：Milthm (赞：1)

## UVA11105 题解

### 前置知识

- 埃氏筛

### 题目解法

首先，我们把题目分解成几个步骤。

#### 一、筛出 “H 素数”

这个地方呢，我们采用了埃氏筛的变形（其实只用把开始值设为 $5$，每次加 $4$ 就可以了，其它按照埃氏筛写）：

```cpp

int n=1000000;
//埃氏筛板子
for(int i=5;i<=n;i+=4){//注意这里每次加 4
	if(a[i]==0)p[++t]=i;
	for(int j=i*2;j<=n;j+=i){
		a[j]=1;
	} 
}
	
```

#### 二、筛出 “H 合成数”

筛好 H 素数发现其实只有 $9\times10^4$ 左右个，那么我们可以放心的枚举两个 H 素数，把它们乘起来，再顺手做一个和欧拉筛差不多的优化，就好了。

```cpp

for(int i=1;i<=t;++i){
	for(int j=1;j<=t&&p[i]*p[j]<=n;++j){
		h[p[i]*p[j]]=1;//标记这个数成为 H 合成数
	}
}
```

#### 三、处理答案

直接枚举答案肯定会爆炸，我们使用前缀和的思想，预处理出每一个答案。最后一个一个输出即可。

这块代码不放了，看完整代码。

### AC 代码

```cpp
#include<iostream>
using namespace std;
int p[1000005],t,T,ans[1000005];
bool a[2000005],h[2000005];
int main(){
	int n=1000000;
	for(int i=5;i<=n;i+=4){//第一步
		if(a[i]==0)p[++t]=i;
		for(int j=i*2;j<=n;j+=i){
			a[j]=1;
		} 
	}
	for(int i=1;i<=t;++i){//第二步
		for(int j=1;j<=t&&p[i]*p[j]<=n;++j){
			h[p[i]*p[j]]=1;
		}
	}
	for(int i=1;i<=n;++i){//第三步
		ans[i]=ans[i-1]+h[i];
	}
	int x;
	while(cin>>x){
		if(x==0)break;
		cout<<x<<" "<<ans[x]<<endl; //输出，别忘了换行
	}
	return 0;
}
```





---

## 作者：ysj1173886760 (赞：1)

emm看到这个没有人写题解我就写一篇吧

题目就是说形如4n+1的数叫h数，所谓的h-semi-prime就是只能被两个h素数乘出来。
让求给出的区间中h-semi-prime数的个数，看到多组数据我们可以想到预处理，然后O(1)查询即可。那么要怎么处理呢？？

这道题毋庸置疑首先先筛出素数，埃式筛即可。具体一点，其实我们要筛的实际上是h数中的素数，那么就不用一个一个枚举了，我们4个4个的枚举就好。

比如5 9 13，这都是h数，然后判断就行了，但是对于这个筛法的核心思想，我们是要筛出h数中的素数的，当然你全筛也无所谓。原本的筛法中，我们是将这个素数的倍数全都筛去，这里我们加了一个限制条件就是在H数中筛。那么应该怎么枚举呢？

实际上H数就是一个同余等价类，所有的H数都满足对于一个H数i，有i mod 4 =1；
也就是 i≡1(mod4),很熟悉吧。那么我们对于一个新数i的倍数ki 要满足ki在这个类中，也就是ki≡1(mod4),根据模运算的性质我们可以得到：ki mod 4 =1 ->
(k mod 4)*(i mod 4)=1

又因为i本身就是H数，也就是i mod 4 =1，那么我们需要的就是 k mod 4 =1,也就是说我们i的倍数k也是一个H数。  那么我们枚举H数 把k*i在表中删去即可。

即5i 9i 13i....  

再提一点就是不用担心素数枚举的复杂度，因为素数个数大约是n/logn,在H数这个集合中会更小。而且如果要满足相乘小于maxn，才几百个而已。

那么我们的代码也就有了
```cpp
#include<iostream>
using namespace std;
const int maxn=1000050;
int prime[maxn],tot,sum[maxn];//prime 记录的是质数表， sum[i]表示从1到i有多少semiprime ，tot即为总素数个数。 
bool isprime[maxn],iscomposite[maxn];//isprime记录的是当前数是否为素数，如果是素数 就为false，iscomposite记录当前数是否为 semiprime。 
int main()
{
	for(int i=5;i<=maxn;i+=4)	//枚举H数 
		if(!isprime[i])
		{
			prime[++tot]=i;
			for(int j=i*5;j<=maxn;j+=4*i)isprime[j]=true;//按照上面说的，枚举H数，也就是i的倍数 
		}
	for(int i=1;i<=tot;i++)	//把所有的H素数乘一遍找出semiprime 
		for(int j=1;j<=i&&prime[i]*prime[j]<=maxn;j++)
			iscomposite[prime[i]*prime[j]]=true;
	for(int i=1;i<=maxn;i++)sum[i]=sum[i-1]+iscomposite[i];//前缀和的预处理 
	int temp=0;
	cin>>temp;
	while(temp)
	{
		cout<<temp<<" "<<sum[temp]<<endl;//回答询问即可。 
		cin>>temp;
	}
	return 0;
}
```

---

## 作者：冒泡ioa (赞：1)

安利下[自己的博客](http://bubbleioa.top/archives/600)

# 题目大意
形如4n+1的数被称为“H数”，乘法在“H数”组成的集合内是封闭的。在这个集合中只能被1和本身整除的数叫做“H素数”（不包括1），其余的数被称为“H合数”。一个“H合成数”是一个能且只能分解成两个“H素数”乘积的“H合数”（可能由多种分解方案）。比如441=21*21=9*49，所以411是“H合成数”，125=5*5*5，所以125不是“H合成数”。
求0~h范围内“H合成数”的个数。

# 题解
思路其实很简单，既然只有两个“H素数”的乘积是一个“H合成数”的话，那么我们把所有的“H素数”筛出来再来组合不就是“H合成数”了吗？



筛法我们可以直接在埃式筛法上改一下，也就是标记合数的方法。

也就是我们要标记的数其实是满足：

1. 是4n+1的倍数
2. mod4余1

于是我们可以得到下面的式子：

$$k(4n+1)\%4=1$$

$$4kn\%4+k\%4=1$$

$$k\%4=1$$

就可以得到k其实是下面这组数：

$$\{k|k\in 4i+1,i\ge1\}$$

筛出H素数后枚举两两相乘（超过了1000001就break啦，不要再作没意义的事），开个桶s（0和1，顺便起到去重的作用），然后算桶的前缀和，s[i]就是0~i范围内的H合成数

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000004;
bool p[MAXN];
int prime[MAXN],cnt;
int s[MAXN];
int n;

void primes(int n){
    for(int i=5;i<=n;i+=4){
        if(p[i])continue;
        prime[++cnt]=i;
        for(int k=1;k*i<=n;k+=4){
            p[k*i]=1;
        }
    }
}

int main(){
    primes(1000001);
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=i&&prime[i]*prime[j]<MAXN;j++){
            s[prime[i]*prime[j]]=1;
        }
    }
    for(int i=1;i<=1000001;i++)s[i]+=s[i-1];
    while(scanf("%d",&n)){
        if(n==0)break;
        printf("%d %d\n",n,s[n]);
    }
    return 0;
}
```



---

## 作者：unsigned_XB (赞：1)

这是一道数论题...

素数筛AC
## 思路+代码：
先用筛法：
注意：这里素数的定义是仅在集合内的“素数”，不需要涉及集合外的数
```
for(int i=5;i<=n;i+=4)
{
	if(p[i]==0)
	{
		b[++sum]=i;
		for(int j=i*5;j<=n;j+=i*4)
			p[j]=-1;
	}	
}
```
下一步：直接乘，算出“合成数”
这里要注意两个点：

（1）注意乘积的大小，不要超过1000000

（2）注意第二层循环的上限，小心超时
```
for(int i=1;i<=sum;i++)
	for(int j=1;j<=i&&b[i]*b[j]<=n;j++) 
		a[b[i]*b[j]]=1;
```
最后一步：前缀和+输出

没什么可说的
```
int x;
for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
while(cin>>x&&x!=0) cout<<x<<' '<<s[x]<<endl;
```
上代码~
```
#include<bits/stdc++.h>
using namespace std;
int n=1000001;
int a[1000005],p[1000005]={0},ans;
int s[1000005],b[1000005];
int sum;
int main()
{
	for(int i=5;i<=n;i+=4)
	{
		if(p[i]==0)
		{
			b[++sum]=i;
			for(int j=i*5;j<=n;j+=i*4)
				p[j]=-1;
		}	
	}
	for(int i=1;i<=sum;i++)
		for(int j=1;j<=i&&b[i]*b[j]<=n;j++) 
			a[b[i]*b[j]]=1;
	int x;
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	while(cin>>x&&x!=0) cout<<x<<' '<<s[x]<<endl;
	return 0;
}
```
~~数论有毒~~


---

## 作者：Swirl (赞：0)

本题我觉得是真不难，建议降绿。

# 题意简述

本题基本只考查了类埃氏筛算法。

埃氏筛是一种快捷的选质数的方法，时间复杂度约为 $O(n\times \log_2{\log_2n})$，其中两个 $\log$ 是一个嵌套关系；在本题的数据下其时间复杂度与 $O(n)$ 几乎没有什么区别。

其算法原理就是找到第一个没有被标记过的数，这个数就是质数；接着标记剩下的数中此数的倍数。

可以证明，没有被前面的数标记过的数可以理解为这个数不是前面任意一个数的倍数，其正好符合质数的定义。

算法正确性证明完结。

那么我们用类埃氏筛筛完 H-Prime 数之后可以打表求出所有的 H-Semi-prime 用布尔数组存储。

不过在通过及答案之前需要进行一次前缀和，否则就会超时（绝对不会告诉你我这样错过）。

思路部分完结。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
// #pragma GCC optimize(2)
#define int long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
using namespace std;

int n;
int vis[10000005];
vector<int> p;

il void init() {
    memset(vis, 0, sizeof(vis));
    for (register int i = 5; i <= 1000000; i += 4) {
        if (vis[i] == 1) {
            continue;
        }
        p.push_back(i);
        for (int j = i * 2; j <= 1000000; j += i) {
            vis[j] = 1;
        }
    }
    memset(vis, 0, sizeof(vis));
    for (register int i = 0; i < p.size(); i++) {
        for (register int j = i; j < p.size(); j++) {
            if (p[i] * p[j] > 1000000) break;
            vis[p[i] * p[j]] = 1;
        }
    }
    for (register int i = 1; i <= 1000000; i++) {
        vis[i] += vis[i - 1];
    }
}

signed main() {
    ios; 
    init();
    while (cin >> n) {
        if (n == 0) break;
        cout << n << " " << vis[n] << endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析

一个筛“素”数模板加一个预处理就行了。

根据题意，我们可以将筛素数的模板改成这样，使得每一个筛出来的素数都能变成 $4k+1$ 的形式：

```cpp
int h_pre[N],idx,h_vis[N];//存H-素数，筛出来H-素数的个数，判断是不是H-素数 
void find_h(){//模板
	//第一个H-素数就是4*1+1，以后每次+4就能使k+1 
	for(int i=4+1;i<=1000005;i+=4){//询问上界是1000001 
		if(h_vis[i]) continue;//不是H-素数 
		h_vis[i]=1;
		h_pre[++idx]=i;
		for(int j=2;j*h_pre[idx]<=1000005;j++){//把H-合数筛掉 
			h_vis[j*h_pre[idx]]=1;
		}
	}
}
```
得到小于 $10^6+1$ 的“H-素数”之后，我们就能考虑预处理。枚举筛出来的任意两个“H-素数”，只要这两个的乘积所得的“H-合成数”不大于询问上界，我们就可以把这个“H-合成数”标记一下。最后求一个前缀和就能知道 $0$ 到 $h$ 中“H-合成数”的数量了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+100;
int h_pre[N],idx,h_vis[N];
void find_h(){//筛H-素数 
	for(int i=4+1;i<=1000005;i+=4){
		if(h_vis[i]) continue;
		h_vis[i]=1;
		h_pre[++idx]=i;
		for(int j=2;j*h_pre[idx]<=1000005;j++){
			h_vis[j*h_pre[idx]]=1;
		}
	}
}
int s[N];//前缀和 
bool if_h[N];//判断是不是H-合成数 
int h;
signed main(){
	find_h();
	for(int h1=1;h1<=idx;h1++){
		for(int h2=h1;h_pre[h1]*h_pre[h2]<=1000005;h2++){
			if_h[h_pre[h1]*h_pre[h2]]=1;//标记 
		}
	}
	for(int i=1;i<=1000005;i++){//前缀和 
		if(if_h[i]){
			s[i]=s[i-1]+1;
		}
		else{
			s[i]=s[i-1];
		}
	}
	while(cin>>h&&h){
		cout<<h<<" "<<s[h]<<endl;
	}
	return 0;
}
```


---

## 作者：myyyIisq2R (赞：0)

### [UVA11105 $and$ POJ3292](https://www.luogu.com.cn/problem/UVA11105)
## **分析**
利用同余结论，拓展一下筛选法求素数。如果一个数 $i$ 是 $H-$ 素数，那么 $5i+4i×x$ 一定是 $H-$ 素数，因为 $(5i+4i×x)$ $\bmod$ $4 = 5i$ $\bmod$ $4 = (5 $ $\bmod$ $4)× (i$ $\bmod$ $4) = 1 × 1 = 1$ ，且 $5i+4i×x = i(4x+5)$ 。
## **参考程序**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX 1000016
bool is_H_prime[MAX], is_H_semiprime[MAX];
int H_prime[MAX];
int accumu[MAX];
int n;
int main()
{
	for (int i{ 5 }; i < MAX; i += 4)
	{
		if (is_H_prime[i])continue;
		H_prime[++n] = i;
		for (int j{ i * 5 }; j < MAX; j += i * 4)
		{
			is_H_prime[j] = true;
		}
	}
	for (int i{ 1 }; i <= n; i++)
		for (int j{ 1 }; j <= i && H_prime[i] * H_prime[j] < MAX; j++)
		{
			is_H_semiprime[H_prime[i] * H_prime[j]] = true;
		}
	for (int i{ 1 }; i < MAX; i++)
	{
		accumu[i] = accumu[i - 1] + is_H_semiprime[i];
	}
	int h;
	cin >> h;
	while (h)
	{
		cout << h<<" "<<accumu[h] << endl;
		cin >> h;
	}
	return 0;
}

```

---

## 作者：ForeverCC (赞：0)

这题用到了同余的结论

我们可以用筛选法判断H数是否是H-素数

模拟样例可以发现，如果数 $i$ 为H-素数，则 $4*i*x+ 5*i$ 一定不是H-素数。所以可得出以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool hp[1000020],hsp[1000020];
int hpr[1000020],sum[1000020],n,t;

int main(){
	for(int i=5;i<1000020;i+=4){
		if(hp[i])continue;//若i不是H-素数，则不讨论
		hpr[++n]=i;
		for(int j=i*5;j<1000020;j+=i*4)hp[j]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i&&hpr[i]*hpr[j]<1000020;j++)
			hsp[hpr[i]*hpr[j]]=1;//H-合成数
	for(int i=1;i<1000020;i++)sum[i]=sum[i-1]+hsp[i];//计算H-合成数的个数
	while(1){
		scanf("%d",&t);
		if(t==0)break;
		printf("%d %d\n",t,sum[t]);
	}
	return 0;
}
```


---

## 作者：banned_gutongxing (赞：0)

## 题目简述
[题目传送门](https://www.luogu.com.cn/problem/UVA11105)

有三类数的定义如下

$H$ 数：所有可以表示为  $4\times k+1 (0\le k)+1$ 的数。

$H$ 素数：所有 $H$ 数中，非平凡约数中无 $H$ 数。

$Semi−primeH$ 数：所有能表示成两个 $H$ 素数积的数。

问：$1$  到 $n$ 之间有多少个 $Semi−primeH$ 数。


## 思路
首先设两个 $H$ 素数分别是 $4a+1,4b+1$ 。

两个数相乘， $16ab+4a+4b+1 = 4(4ab+a+b)+1$，所以两个 $H$ 素数想成仍为 $H$ 素数。

所以只用求出 $H$ 素数然后相乘就行了。

这里我们可以用类埃氏筛来做。


---

## 作者：封禁用户 (赞：0)

### 分析
利用同于结论，拓展一下筛选法求质数，我们会发现如果一个数 $i$ 是 H 素数，则 $5\times i+4\times i \times x$ 一定是 H 数但不是 H 素数。因为 $(5\times i+4\times i \times x) \bmod 4 = 5 \times i \bmod 4 = (5 \bmod 4) \times (i \bmod 4) = 1$，且 $5\times i+4\times i \times x = i(4 \times x + 5)$。所以，我们就做完了。

## AC 代码
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN = 1e6 + 10;
const int INF = 0x3f;
bool prime[MAXN],semiprime[MAXN];
int hprime[MAXN];
int ans[MAXN];
int n;
void getPrime(){
	for(int i = 5;i < MAXN; i += 4){
		if(prime[i])continue;
		hprime[++n]=i;
		for(int j = i * 5;j < MAXN; j+= i * 4)prime[i] = true;
	}
} 
int main()
{
	getPrime();
	for(int i = 1;i <= n; i++){
		for(int j = 1;j <= i && hprime[i] * hprime[j] < MAXN; j++){
			semiprime[hprime[i] * hprime[j]] = true;
		}
	}
	for(int i = 1;i < MAXN; i++){
		ans[i] = ans[i - 1] + semiprime[i];
	}
	int h;
	cin >> h;
	while(h){
		cout << ans[h];
		cout << endl;
		cin >> h;
	} 
    return 0;
}

```

---

