# Arithmetic Progression

## 题目描述

这是一个交互题！

等差数列是指这样一个整数序列：每个元素与其前一个元素的差（$x_i - x_{i-1}$，其中 $i \ge 2$）是一个常数，这个常数称为该序列的公差。

也就是说，等差数列的形式为 $x_i = x_1 + (i - 1)d$，其中 $d$ 是该序列的公差。

现在有一个长度为 $n$ 的秘密整数列表 $a_1, a_2, \ldots, a_n$。

保证所有元素 $a_1, a_2, \ldots, a_n$ 都在 $0$ 到 $10^9$ 之间（包含端点）。

这个列表有一个特殊性质：将其升序排列后，会形成一个公差为正数（$d > 0$）的等差数列。例如，列表 $[14, 24, 9, 19]$ 满足这一要求，排序后为 $[9, 14, 19, 24]$，可以表示为 $x_n = 9 + 5 \cdot (n - 1)$。

你还拥有一个设备，但电量不足，因此你最多只能进行 $60$ 次如下两种类型的查询：

- 给定一个值 $i$（$1 \le i \le n$），设备会显示 $a_i$ 的值。
- 给定一个值 $x$（$0 \le x \le 10^9$），设备会返回 $1$，如果存在严格大于 $x$ 的元素，否则返回 $0$。

你最多只能使用这台特殊设备进行 $60$ 次查询。你能否找出该等差数列的最小元素和公差？即，找出等差数列定义中的 $x_1$ 和 $d$。注意，数组 $a$ 并不是有序的。

## 说明/提示

请注意，示例交互中包含了额外的空行以便于阅读。实际交互中不会有任何空行，你也不应输出任何额外的空行。

示例测试中的列表为 $[14, 24, 9, 19]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4

0

1

14

24

9

19

```

### 输出

```

> 25

> 15

? 1

? 2

? 3

? 4

! 9 5```

# 题解

## 作者：Spasmodic (赞：8)

似乎并没有人证明随机算法的概率（只是引用了官方题解），所以闲着就算一下。

所求概率即为
$$
\frac{1}{n^{30}}\sum_{i_1\dots i_{30}\in\{0,n-1\}}[(i_1,\dots,i_{30})=1]
$$

考虑枚举最大公约数，根据莫比乌斯反演，这就是
$$
\frac{1}{n^{30}}\sum_d\mu(d)\left\lceil\frac{n}{d}\right\rceil^{30}
$$
这样我们可以在 $O(n)$ 的时间内把这个东西算出来。不过我们想要一个纯数学的东西，对上面这个做一个比较准确的估算。

我们考虑计算上式当 $n\to \infty$ 的极限，这就是
$$
\sum_d\mu(d)\frac{1}{d^{30}}=\sum_{d=p_1\dots p_k}(-1)^k\frac{1}{(p_1\dots p_k)^{30}}=\prod_p\left(1-\frac{1}{p^{30}}\right)
$$
熟知上式即为 $\dfrac{1}{\zeta(30)}$，再根据 $\zeta$ 的通项，$\zeta(2n)=\dfrac{(2\pi)^{2n}B_{2n}}{2(2n)!}$

查表得 $B_{30}=\dfrac{8615841276005}{14322}$，代入计算得 $\zeta(30)=\dfrac{6892673020804\pi^{30}}{5660878804669082674070015625}$

因此正确概率的极限即为
$$
p=\dfrac{5660878804669082674070015625}{6892673020804\pi^{30}}
$$
错误概率约 $9.3132\times 10^{-10}$.

---

事实上我们有一种枚举方式的优化：令每次查询的数互不相同，这样得到的新概率是
$$
\frac{1}{n^{\underline{30}}}\sum_d\mu(d)\left\lceil\frac{n}{d}\right\rceil^{\underline{30}}
$$
但是仔细想一想，会意识到这件事情极限上并没有优化：考虑将 $\left[\dfrac{n}{d}\right]^{\underline{30}}$ 展开，注意到除了首项以外其余极限皆为 $0$，故当 $n\to \infty$ 时极限不变。

以上。

---

## 作者：AThousandSuns (赞：8)

在我的博客上看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10362096.html)

看，第二个操作，明显暗示我们要二分最大值。（除了这个也没啥用了吧？）

用掉 $\log 10^9=30$ 个操作。

令 $mx$ 为我们二分出的最大值。

设公差为 $d$，那么 $\forall 1\le i\le n,d|(mx-a_i)$。

也就是如果我们知道的 $a_i$ 有 $x_1,x_2,x_3\dots,x_k$，那么 $d|\gcd(mx-x_1,mx-x_2,mx-x_3\dots,mx-x_k)$。

但这样就有一个严峻的问题：如果 $k$ 不够大，直接 $\gcd$ 得到的可能不是答案！

无路可走了，只有一个想法：随机！

我们随机 $30$ 个 $i$，询问这些 $a_i$ 的值。（为什么要随机呢？因为如果直接取前 $30$ 个 $a_i$ 很可能会被毒瘤卡掉）

$d$ 就是所有 $mx-a_i$ 的 $\gcd$ 了。

？？？这样不会错吗？

分析一下，我们设 $a_1=mx-k_1d,a_2=mx-k_2d\dots a_n=mx-k_nd$。那么我们求出的 $\gcd$ 就是随机出的 $30$ 个 $k_i$ 的 $\gcd$。

在 $10^6$ 中随机选 $30$ 个数，$\gcd$ 不为 $1$ 的概率就是出错的概率。

大致估算一下：

选出的 $k$ 都是 $2$ 的倍数的概率是 $\frac{1}{2^{30}}$。

选出的 $k$ 都是 $3$ 的倍数的概率是 $\frac{1}{3^{30}}$。

等等等等……

这样估算的话，出错概率是不会超过 $10^{-8}$ 的。

其实有更准确的求法，就是莫比乌斯反演，但由于我们只是来证明正确性的，就不讲了。

直接引用官方题解：

By some maths, we can find out the probability of our solution to fail being relatively small — approximately $1.86185\times 10^{-9}$.

直接上rand()就做完了……

了吗？

![](https://img2018.cnblogs.com/blog/1418922/201902/1418922-20190211160716776-296734885.png)

对了，这就是出题人恶毒所在了……

rand()和random_shuffle()的上界都是32767，访问不到后面大部分的元素。

于是出题人就把恶毒的数放在了前面……

那就用自己的rand()啊！写过treap吗？把那个rand搬过来就能用了！

**（注：这样在CF容易被卡掉，最近发现了一个叫做mt19937的东西，可以在[这里](http://codeforces.com/blog/entry/61587)看）**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=1000100;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
    char ch=getchar();int x=0,f=0;
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int n,cnt,pt[maxn];
inline int rnd(){    //自己的rand
    static int seed=2333;
    return seed=(((seed*666666ll+20050818)%998244353)^1000000007)%1004535809;
}
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
int main(){
    n=read();
    if(n<=60){    //n<=60，随便玩
        int mx=0,mn=INT_MAX;
        FOR(i,1,n){
            printf("? %d\n",i);
            fflush(stdout);
            int x=read();
            mx=max(mx,x);
            mn=min(mn,x);
        }
        printf("! %d %d\n",mn,(mx-mn)/(n-1));
        fflush(stdout);
        return 0;
    }
    int l=0,r=1e9;
    while(l<r){    //二分最大值
        int mid=(l+r)>>1;
        printf("> %d\n",mid);
        cnt++;
        fflush(stdout);
        int ver=read();
        if(ver) l=mid+1;
        else r=mid;
    }
    int mx=r,ans=0;
    FOR(i,1,n) pt[i]=i;
    FOR(i,1,n) swap(pt[i],pt[rnd()%n+1]);
    FOR(i,1,min(n,60-cnt)){    //随机60-cnt个元素
        printf("? %d\n",pt[i]);
        fflush(stdout);
        int x=read();
        ans=gcd(ans,mx-x);    //取gcd
    }
    printf("! %d %d\n",mx-(n-1)*ans,ans);    //首项=末项-(项数-1)*公差
    fflush(stdout);
}
```

---

## 作者：ImmortalWatcher (赞：2)

首先观察题目给的两个操作有什么用。

第一个操作能完成的事情就是求出整个等差数列的最大值，可以在 30 次询问内解决。

设最大值为 mx。

第二个询问直接了当，直接用。**随机**询问三十个数。

然后我们发现，直接把排序后的数相邻作差得到的所有数的 $\text{gcd}$ 就是答案。

为什么呢？

可以设我们询问的数得到的数列为 $A$。那么可以表示为：

$A_1=mx-k_1d,A_2=mx-k_2d,……,A_{30}=mx-k_{30}d$。

发现出错的情况就是所有 k 的 $\text{gcd}$ 不为 1 的时候。

也就是从 n 个数中选 30 个数，它们的 $\text{gcd}$ 不为 1 的概率。

可以证明这个概率是非常小的，所以可以通过本题。

我们现在考虑如何证明这个结论：

1. $n\le10^6$ ，问题转化为从 $1\sim10^6$ 随机选取 30 个数，$\text{gcd}$ 不为 1 的概率。

1. $\text{gcd}=2$ 时，即 30 个数都是 2 的倍数，概率大约为 $\dfrac{1}{2^{30}}$，同理 $\text{gcd}=k$ 时，概率大约为 $\dfrac{1}{k^{30}}$。

1. 即总概率大约为 $\sum\limits_{k=1}^n\dfrac{1}{k^{30}}$。

由于我们只是要证明这个概率很小，所以一些关于边界的问题暂且忽略不计。

到现在为止，你可以用你高超的数学技巧继续化解，但我觉得化成这样，你就完全可以用暴力来计算啦！~~写一个分数模板+高精度~~

~~也可以感性理解一下这个式子的值很小~~

官方题解也同样给出这种随机的策略出错的概率大约为 $1.86185\times{10^{-9}}$，证毕。

一个值得注意的地方就是 rand() 上界有限，所以直接用 rand() 会被出题人用特殊数据卡掉，建议自写 rand 函数。

**code**
```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
const int x=1e9+7,y=1e9+9;
int n,a[31],mx,d,p[1000010];
bool check(int x)
{
	printf("> %d\n",x);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
int random()
{
	return ((1ll*rand()*x+y+rand())&1048575)%n+1;
}
int ask(int x)
{
	printf("? %d\n",x);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
int main()
{
	srand(time(0));
	scanf("%d",&n);
	int l=0,r=1e9;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) l=mid+1;
		else r=mid-1,mx=mid;
	}
	for (int i=1;i<=n;i++) p[i]=i;
	for (int i=1;i<=n;i++) swap(p[i],p[random()]);
	for (int i=1;i<=min(n,30);i++) a[i]=ask(p[i]);
	sort(a+1,a+min(n,30)+1);
	d=a[2]-a[1];
	for (int i=2;i<min(n,30);i++)
		d=gcd(d,a[i+1]-a[i]);
	printf("! %d %d\n",mx-d*(n-1),d);
	fflush(stdout);
	return 0;
}
```


---

## 作者：TKXZ133 (赞：1)

[Arithmetic Progression](https://www.luogu.com.cn/problem/CF1114E)

### 题目大意

存在一个打乱了顺序的等差数列 $a$，你可以询问不超过 $60$ 次，每次可以以以下两种方式之一进行询问：

- 查询 $a$ 中是否有严格大于 $x$ 的数。

- 查询 $a_i$ 的值。

你需要求出这个等差数列的首项和公差。

### 思路分析

比较有意思的题。

看到第一种询问，首先想到二分，我们可以用 $O(\log V)$ 次询问查询出 $a$ 中的最大值。

那么公差怎么求呢？

考虑**随机化**，我们在 $a$ 中随机询问若干个位置的值（把剩下的询问次数全部询问掉），然后将这些得到的值排序，求相邻两数之间的差，再求出所有差的最大公约数作为 $a$ 的公差，这样有极大概率是对的。

证明可以参考[官方题解](https://codeforces.com/blog/entry/65136)，用莫反可以得出出错的概率约为 $1.86185\times 10^{-9}$。~~证明我也不会。~~

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
const int V=1000000000,N=100,M=60;

int n,times,tot,in1;
int a[N],d[N];

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

std::mt19937 defaultRNG(std::chrono::steady_clock::now().time_since_epoch().count());
int defaultRandInt(int l,int r){
    int out=defaultRNG()%(r-l+1)+l;
    return out>=l?out:out+r-l+1; 
}
int (*randint)(int,int)=defaultRandInt;

int main(){
    scanf("%d",&n);
    int l=0,r=V,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        cout<<"> "<<mid<<endl;
        times++;
        scanf("%d",&in1);
        if(in1) l=mid+1,ans=mid;
        else r=mid-1;
    }  
    for(int i=times;i<M;i++){
        cout<<"? "<<randint(1,n)<<endl;
        scanf("%d",&a[++tot]);
    }
    sort(a+1,a+tot+1);
    for(int i=2;i<=tot;i++)
        d[i-1]=a[i]-a[i-1];
    int D=d[1];
    for(int i=2;i<tot;i++)
        D=gcd(D,d[i]);
    cout<<"! "<<ans+1-D*(n-1)<<' '<<D<<endl;
    return 0;
}
```

---

## 作者：decoqwq (赞：1)

一道交互题，思路比较简单

先二分找出序列最大值，大概需要$30$次

剩下的$30$次随机询问某个位置，将$30$个数存入数组中，排序后，求出两两间差值的$gcd$即可得到公差

不能用$rand$，$windows$里$rand$最大为$32767$，要改成$rand()<<15|rand()\%n$

```cpp
#include <bits/stdc++.h>
using namespace std;
int now[37],cnt,p[4000010];
int gcd(int a,int b)
{
	return a==0?b:gcd(b%a,a);
}
int main()
{
    srand(19260817);
	int n;
	cin>>n;
	int l=0,r=1e9;
	while(l<r)
	{
		int mid=(l+r)>>1;
		cout<<"> "<<mid<<endl;fflush(stdout);
		int x;
		cin>>x;
		if(x==0)
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	} 
	cout<<"> "<<l<<endl;fflush(stdout);
	int x;
	cin>>x;
	if(x==0)
	{
		l--;
	} 
	for(int i=1;i<=min(29,n);i++)
	{
		int x=(rand()<<15|rand())%n+1;
		while(p[x])
		{
			x=(rand()<<15|rand())%n+1;
		}
		p[x]=1;
		cout<<"? "<<x<<endl;fflush(stdout);
		int pwp;
		cin>>pwp;
		now[++cnt]=pwp;
	}
	sort(now+1,now+cnt+1);
	int d=now[2]-now[1];
	for(int i=3;i<=cnt;i++)
	{
		d=gcd(d,abs(now[i]-now[i-1]));
	}
	l=l-(n-1)*d;
	cout<<"! "<<l+1<<" "<<d<<endl;fflush(stdout);
}
```
[这一场cf的题解，打个广告](https://decorationqwq.com/archives/324/)

---

## 作者：Eznibuil (赞：0)

紫？？？

首先看到可以用大概一半操作次数问出最大值，接下来随机问某个地方的值。

然后依次和最大值作差取 gcd 即可得到公差。最坏的话差不多是随机两个正整数看互质的概率，根据常识是 $\frac6{\pi^2}$，所以出错概率还蛮小的。

最后用最大值减去公差的 $(n-1)$ 倍即为最小值。
```cpp
#include<chrono>
#include<iostream>
#include<numeric>
#include<random>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int main()
{
	std::cin.tie(0)->sync_with_stdio(0);
	int n;
	std::cin>>n;
	int max=0;
	for(int i=29;~i;i--)
		if((max|1<<i)<1000000001)
		{
			std::cout<<"> "<<(max|1<<i)-1<<std::endl;
			bool f;
			std::cin>>f,f?max|=1<<i:0;
		}
	int g=0;
	std::uniform_int_distribution d(1,n);
	for(int i=0;i<30;i++)
	{
		std::cout<<"? "<<d(rng)<<std::endl;
		int x;
		std::cin>>x,g=std::gcd(g,max-x);
	}
	std::cout<<"! "<<max-(n-1)*g<<' '<<g;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

题意：

　　交互题。

　　有一个等差序列，现已打乱顺序，最多询问 $60$ 次来确定首项和公差。每次可以询问是否有严格大于 $x$ 的数，和查看一个位置的数。

分析：

　　首先可以二分找到序列的最大值，然后考虑如何求公差。

　　随机选 $30$ 个数，然后对任意两个求一遍 $\gcd$ 即可。
 [正确性证明](https://codeforces.com/blog/entry/65136)
 ```
 #include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
#include<cctype>
#include<set>
#include<queue>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;


inline int query(int ty,LL x) {
    int y;
    if (ty == 1) printf("> %I64d\n", x);
    else printf("? %I64d\n", x);
    fflush(stdout);
    cin >> y;
    if (y == -1) exit(0);
    return y;
}

vector<LL> vec;
int Rand() { return (rand() << 15) | rand(); }
int id[1000005];

int main() {
    srand(1114);
    int n; cin >> n;
    LL l = -1e9, r = 1e9, ans = 0, cnt = 60, tot = n;
    while (l <= r) {
        LL mid = (l + r) >> 1;
        cnt --;
        if (query(1, mid) == 0) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    for (int i = 1; i <= tot; ++i) id[i] = i;
    while (cnt > 0 && tot > 0) {
        int x = Rand() % tot + 1;
        vec.push_back(query(0, id[x]));
        swap(id[x], id[tot]);
        tot --;    cnt --;    
    }
    sort(vec.begin(), vec.end());
    if (vec.back() != ans) vec.push_back(ans);
    LL d = vec[1] - vec[0];
    for (int i = 0; i < (int)vec.size() - 1; ++i) d = __gcd(d, vec[i + 1] - vec[i]);
    printf("! %I64d %I64d\n", ans - (n - 1) * d, d);
    return 0;
}
```

---

## 作者：FyFive (赞：0)

# CF1114E

猜数游戏，简单 IO 交互，一眼题。

## Solution

题目暗含了一个条件，那就是交互库非自适应。这个条件很重要，没有这个条件随机化算法的正确性将大幅降低。

### Step 1

首先考虑两种询问方式分别能有什么用。

#### 第一种

询问某个位置的值，由于序列是乱的，只保证了排序之后的性质，所以直接询问相当于从一个集合中随机另一个数出来，这里的“随机”是在第一次询问意义下的随机。

既然是从一个集合中返回数，那么就不需要费心思想“位置的二进制”相关的传统艺能了。如果做法要基于这一种询问，那么必然需要选取随机的若干个位置。

但是直接询问前若干个想必是会被卡的，具体来说就是虽然直接选取前缀或后缀不会影响出错概率，但是基于人为因素挑取前缀这一做法将变得不那么“随机”，这将导致实际正确率下降。同理，理论上常见种子也是有一定概率会被卡的，所以需要一个基于随机种子的随机函数来确保正确率不会降得太多。不过实际情况却没有谁这么无聊把各个地方的常见种子卡个遍。

#### 第二种

询问集合中是否存在大于某个数的值，如果能询问 $\infty$ 次，考虑从 $-\infty$ 到 $+\infty$ 全部顺序询问一遍，那么必然是一段前缀 $0$ 和一段后缀 $1$，找到 $0$ 和 $1$ 的分界处就能获得这个询问所能获得的可能的所以信息。这个简单，二分就好，花费 $\lceil \log V \rceil \leq 30$ 次询问即可。

### Step 2

接下来考虑结合两种可能得到的信息。

首先是这个第二种询问的分界处有什么用。不难知道这个分界处（如要返回 $0$ 所需的询问的最小的数）即为 $\max\limits_{i=1}^{n} a_i$（后文将 $\max\limits_{i=1}^{n} a_i$ 记作 $mx$，将 $\min\limits_{i=1}^{n} a_i$ 记作 $mi$）。

由于 $mx=mi+(n-1) \times d$，知道了 $mx$ 之后只要知道了 $d$ 就能求出 $mi$。

考虑怎么求 $d$。

由于将 $a$ 排序之后是一个公差为 $d$ 的等差数列，任意两个元素的差值必然是 $d$ 的倍数，那么任意两个差值的 $\gcd$ 也是 $d$ 的倍数，经此启发我们得到了一个做法：随机选取若干个数，将其两两的差值全部列出来，对这些差值求 $gcd$，其出错概率小于这些数两两不互质的概率。

直观感觉这个概率非常低，当然这个做法的朴素实现如果要确保错误率为 $0$ 的话还是需要取至少 $\left\lceil \frac{n+2}{2} \right\rceil$ 个数。

只要不干一些特别笨的事情，时间完全是够用的，这里就不分析时间复杂度了。

## Code

这种题肯定没办法对拍，故仅放出核心代码以供理解。

```cpp
cin>>n; a1=aw(1),a2=aw(2); if(a1>a2) swap(a1,a2);
if(n==2) {cout<<"! "<<a1<<' '<<a2-a1; cout.flush(); return 0;}
a3=aw(3); if(a2>a3) swap(a2,a3); if(a1>a2) swap(a1,a2);
int d=__gcd(a2-a1,a3-a2); yt[1]=yt[2]=yt[3]=1;
int l=a3-1,r=1e9; nw.push_back(a1),nw.push_back(a2),nw.push_back(a3);
while(l<r)
{
    int mid=l+r+1>>1;
    if(ad(mid)) l=mid;
    else r=mid-1;
    --sx;
}
++l;
sx=min(sx,n-3);
while(sx--)
{
    int ns=rnd()%n+1;
    while(yt[ns]) ns=ns%n+1; yt[ns]=1;
    ns=aw(ns);
    for(int x:nw) d=__gcd(d,abs(ns-x)); nw.push_back(ns);
}
cout<<"! "<<l-d*(n-1)*(n==-343665?0:1)<<' '<<d<<'\n'; cout.flush();
```

---

## 作者：daniEl_lElE (赞：0)

容易发现第二个操作很适合查找序列中的最大值，可以用 $O(\log V)$ 次询问解决。

剩下还有 $30$ 次，我们要寻找公差。考虑随机取出若干个位置，将他们两两相减并取 $\gcd$，有足够大的概率使得 $\gcd=d$。

最后计算一下首项即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(time(0));
bool vis[1000005];
int s[35];
signed main(){
	int n; cin>>n;
	int l=1,r=1e9;
	while(l<r){
		int mid=(l+r)>>1;
		cout<<"> "<<mid<<"\n";
		fflush(stdout);
		int ret; cin>>ret;
		if(ret==1) l=mid+1;
		else r=mid;
	}
	//last=l
	s[0]=l;
	int gcd=0;
	for(int i=1;i<=min(n,30);i++){
		int p;
		while(vis[p=rng()%n+1]) ;
		vis[p]=1;
		cout<<"? "<<p<<"\n";
		fflush(stdout);
		cin>>s[i];
		gcd=__gcd(abs(s[i]-s[i-1]),gcd);
	}
	cout<<"! "<<l-gcd*(n-1)<<" "<<gcd;
	return 0;
}
```

---

## 作者：EXODUS (赞：0)

# Part 1：前言
补充一个侧重于正确性证明的题解。但证明是口胡的，有问题还请指出/kt。

# Part 2：正文
首先第二个操作一眼二分，那我们先花 30 次询问搞到最大值 $x$。考虑接下来怎么做。我们要求等差数列的公差，一个直观的感受是去找到一些数，然后算出这些数和最大值的差值。由于每个数都可以被表示为 $x-pd$，那么我们的差值集合就是 $\{p_1d,p_2d,...,p_nd\}$。这个集合里所有数的最大公约数便是公差。

但是我们不能直接找 $n$ 项。考虑随机化，那么现在得到的集合就是 $\{p_1d,p_2d,...,p_Bd\}$，我们现在考虑计算这个集合里数的最大公约数得到的结果恰为公差的可能性是多少，那么是在 $n$ 个数中随机 $B$ 个数让其最大公约数为 1 的概率。容斥一下变成 $\sum\limits_{i=1}^n \mu(i)\dfrac{1}{2^B}$。上点放缩科技我能把他变成 $1-\sum\limits_{i=1}^{\log_2{n}} \dfrac{2^i}{{2^i}^B}=1-\sum\limits_{i=1}^{\log_2{n}} \dfrac{1}{{2^i}^{B-1}}$。由于我们有 $B\ge30$，那么后面这堆东西大小不会超过 $\dfrac{\log_2 n}{2^{29}}$。这个东西不是很大，并且还经过了特别宽松的放缩，所以正确性是有保证的。
# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=1e6+7,B=60;
int n,a[N],T;
int askp(int x){T++;printf("? %d\n",x);fflush(stdout);return read();}
bool askv(int x){T++;printf("> %d\n",x);fflush(stdout);return read();}
mt19937 g(time(0));
vector<int>pos,val;
int main(){
	read(n);
	int l=1,r=1e9,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(askv(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	res++;
	rep(i,1,n)pos.eb(i);
	shuffle(pos.begin(),pos.end(),g);
	for(auto x:pos){val.eb(askp(x));if(T==B)break;}
	int d=0;
	for(auto x:val)d=__gcd(d,res-x);
	printf("! %d %d\n",res-(n-1)*d,d);
	return 0;
}
```

# Part 4：后文

~~经检验，出题人没有卡一些固定的随机数种子（比如 0），素质有待降低。~~

---

## 作者：spacebar (赞：0)

一道适合我这样的菜鸡练手的较水紫题。

先利用查大于操作二分查找最大值，然后利用剩下的操作次数随机取数，利用最大数与这些数的差取最大公约数即可求公差，但要注意的是传统的随机数生成会被卡掉，要另寻他法，另外如果太非酋可能不过（真的有那么非的人吗）。

上代码

这里的随机函数来自 [ImmortalWatcher](https://www.luogu.com.cn/user/157857) 的题解，按照题解审核及反馈要求，附上[链接](https://www.luogu.com.cn/blog/me-immortal/solution-cf1114e)，侵权请联系管理员删除。


```
#include <bits/stdc++.h>
using namespace std;
//114514秒终于搞好了 
long long n,maxn,r=1e9,l=0,a,times=59,val;
const int x=1e9+7,y=1e9+9;
int randa(){
	return ((1ll*rand()*x+y+rand())&1048575)%n+1;
}
int main(){
	cin>>n;
	while(l<r){//二分取最大值
		cout<<"> "<<(l+r)/2<<"\n";fflush(stdout);
		cin>>a;
//		if(a==114514){
//			l=24;
//			break;
//		}
     //测试时可以加一个判定以直接跳过繁琐的二分运行
     //但我这个菜鸡在加入后找不到代码问题修改了二分内容却忘了重新调导致判定跳过可以得解正式运行不行，寄。
		if(a==0){
			r=(l+r)/2;
		}else{
			l=(l+r)/2+1;
		}
		times--;
	}
	maxn=r;
	val=0;
	while(times){//随机找公差
		times--;
		cout<<"? "<<randa()%n+1<<"\n";
		fflush(stdout);
		cin>>a;
		val=__gcd(val,maxn-a);
	}
	cout<<"! "<<maxn-val*n+val<<" "<<val<<"\n";
	fflush(stdout);
	return 0;
} 
```


---

## 作者：DPair (赞：0)

表示蒟蒻没想到 $\gcd$ 。。。

提供一种不需要 $\gcd$ 的解法，然而事实上更劣，~~而且正确性我自己也没严格证出来~~。

## 【思路】
我们有两种询问。

对于第一种询问，显然我们是随机获取了原序列中的一些数，而且不是我们想要什么就有什么的。我们可以认为就是随机。

对于第二种询问，显然是拿过来二分用的，而且限制了只能求出来末项。

那我们就相信一次出题人，对 $10^9$ 二分，求出末项

反正我们要求公差，我们可以通过末项得出首项。

然而二分似乎就需要 $30$ 次询问，这要求我们在 $30$ 次询问以内求出公差。

我是这么做的：

把等差数列表示成一个一次函数的形式。

设
$$
f(x)=kx+b
$$
而这个 $k$ 即是公差， $f(1)$ 即是首项。

考虑怎么利用这个式子。

由于我们 $f(n)$ 已知，于是我们已知一个定点 
$$
f(n)=kn+b
$$
于是我们考虑枚举这个 $k$ ，然后就可以算出唯一确定的 $b$ ，再考虑它是否合法。

这一部分我们要枚举 $f(n)/n$ 个 $k$ ，若 $n$ 比较小时间会炸，所以我们考虑 $n\le 60$ 时暴力询问每一个点（显然可以得出正解），$n>60$ 时再用这种方法。

接下来考虑如何检验这一组 $(k, b)$ 。

显然，我们可以通过剩下 $30$ 次询问知道 $30$ 个 $f(x)$ 。

我们可以姑且认为它们分布均匀，这里建议随机取点防止被 $\text{hack}$ ，用了 $\text{C++}$ 自带的 `rand()` 不过没被卡掉一遍 $\text A$ 了。

那么对于这一些 $f(x)$ 都应该要能找到一个正整数 $x\in[1, n]$ ，满足 $f(x)=kx+b$

这个 $x$ 显然是唯一确定的，判断 $x$ 是否是整数以及 $x$ 是否在 $[1, n]$ 之内即可，若不满足直接返回不可行。

我是采用了看对 $k$ 取模后模数是否与 $b$ 模数相同的方式，事实上直接解出来似乎更直观。

那么这样子为什么是正确的呢？我自己也不会证（大雾）。

感性理解一下。（下面全是口胡）

我们有一个平面直角坐标系，上面有一个定点，我们有一条直线过这个定点，而且还与 $30$ 条平行与 $x$ 轴的直线有横坐标也为整数的交点。

毛估估一下，这条直线基本上就是唯一确定的了。

~~有严格证明的请务必告诉我~~

~~而且实测随机15个点都能过~~ 

## 【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[65];
int main(){
    scanf("%d", &n);
    if(n <= 60){
        for (register int i = 1;i <= n;i ++){
            printf("? %d\n", i);
            fflush(stdout);
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        printf("! %d %d\n", a[1], a[2] - a[1]);
        fflush(stdout);
        return 0;
    }
    int l = 0, r = 1000000000;
    int tot = 60, ans = 1000000000;
    while(l <= r){
        int mid = (l + r) >> 1;
        printf("> %d\n", mid);
        tot --;
        fflush(stdout);
        int res;scanf("%d", &res);
        if(!res) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    srand(time(NULL));
    tot = 15;
    for (register int i = 1;i <= tot;i ++){
        printf("? %d\n", rand() % n + 1);
        fflush(stdout);
        scanf("%d", &a[i]);
    }
    if(a[1] == a[2] && a[2] == a[3] && a[3] == a[6] && a[6] == a[11]){
        printf("! 0 %d\n", ans);
        fflush(stdout);
        return 0;
    }
    for (register int i = 1;i <= ans / (n - 1);i ++){
        int b = ans - (i * n);
        int c = (b % i + i) % i;
        bool ck = 1;
        for (register int j = 1;j <= tot;j ++){
            if(a[j] % i != c || ((a[j] - b) / i) <= 0){
                ck = 0;
                break;
            }
        }
        if(ck){
            printf("! %d %d\n", i + b, i);
            fflush(stdout);
            return 0;
        }
    }
}
```

---

## 作者：ttq012 (赞：0)

**Solution**

神题。

可以通过询问 $30$ 次左右二分求出等差数列的最大值。

剩下的 $30$ 次询问随机选择 $30$ 个位置求出这些位置的值，然后用最大值减去这些位置的值，求 $\gcd$ 即可。

看起来很玄学。

证明：二分的次数是 $\log$ 级别的，询问的次数一定不会超过 $30$ 次。剩下的随机选，也就是在这 $10^6$ 个数中随机选择 $30$ 个，$\gcd = 1$ 的概率。这个其他题解已经讲过了，这里不证明。（实际上是我不会）

但是如何随机？

`rand()` 是一个随机函数。

但是 `rand()` 每一次运行程序，返回的值都是一样的。

所以这样很容易被卡。

可以使用 `srand(time(0))` 来初始化种子，这样每一次运行程序返回的值都是不一样的。

但是，`rand()` 在 `windows` 系统下值域为 $[0, 32767]$，在 `linux` 系统下值域为 $[0, 2148473647]$。经过测试，`codeforces` 的评测环境是 `windows`。

也就是说，在 $10^6$ 个数中，`rand()` 函数只能随机前 $32768$ 个数。

那么也是很容易被卡的。

所以应该使用黑科技 `mt19937` 来随机，这个函数可以随机任意的值域。具体看[这里](https://codeforces.com/blog/entry/61587)。

不会交互题？[这里](https://codeforces.com/blog/entry/45307)。

那么这个题就可以很容易的解决了！

**Code**

```cpp
// Think twice, code once.
#include <bits/stdc++.h>

using namespace std;

signed main() {
    mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
    int n;
    cin >> n;
    uniform_int_distribution <int> rnd(1, n);
    vector <int> a;
    int l = 0, r = 1e9;
    int best = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        cout << "> " << mid << '\n';
        cout.flush();
        int x;
        cin >> x;
        if (x == 0)
            r = mid - 1, best = mid;
        else
            l = mid + 1;
    }
    for (int i = 1; i <= 400000; i ++)
        a.emplace_back(rnd(gen));
    auto it = unique(begin(a), end(a));
    a.erase(it, end(a));
    vector <int> b;
    for (int i = 0; i < 30; i ++) {
        int p = a[i];
        cout << "? " << p << '\n';
        cout.flush();
        int x;
        cin >> x;
        b.emplace_back(x);
    }
    sort (begin(b), end(b));
    auto it2 = unique(begin(b), end(b));
    b.erase(it2, end(b));
    int g = b[1] - b[0];
    for (int i = 1; i < 29; i ++)
        g = __gcd(g, b[i + 1] - b[i]);
    int mi = best - (n - 1) * g;
    cout << "! " << mi << ' ' << g << '\n';
    cout.flush();
    return 0;
}

```





---

