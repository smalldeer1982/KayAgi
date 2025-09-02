# Polygons

## 题目描述

给定两个整数 $n$ 和 $k$。

你需要构造 $k$ 个正多边形，这些多边形拥有相同的外接圆，且每个多边形的边数 $l$ 互不相同，满足 $3 \leq l \leq n$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1208G/95991da251ccd37f8f076c85876463789e724ae5.png)  
上图为第一个样例的示意图。你可以通过旋转多边形来最小化圆上不同点的总数。请你求出所需的最小点数。

## 说明/提示

在第一个样例中，$n = 6$，$k = 2$。因此，我们可以从边数为 $3$、$4$、$5$、$6$ 的多边形中任选两个。如果选择三角形和六边形，则可以如题目图片所示进行排列。

因此，所需的最小点数为 $6$，这也是所有可能集合中的最小值。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
200 50
```

### 输出

```
708
```

# 题解

## 作者：L______ (赞：11)

题意：给定两个正整数n和k，询问在一个圆上你最少需要几个点，才能在这些点上构造出k个边数小于等于n的正多边形。

感性分析一波：我们假设我们选取了一个正k边形，那么边数为k的因子的所有正多边形也就全部满足了。设p，满足p|k.那么如果我们选了正k边形，我们相当于已经选择了所有正p边形（比如说我们想要选正六边形，那么必须先选择正三角形），增加的点数即为φ(k)。因此我们对欧拉函数排序，并将前k个累加即可。

至于欧拉筛欧拉函数其实我觉得没有什么可以说的，和筛素数差不多，只要知道欧拉函数是一个积性函数，满足$f[a*b]=f[a]*f[b]$就可以了。

详细来看就是当i%prime[j]==0时：

$phi[i*prime[j]]=phi[i]*prime[j];$

i%prime[j]!=0时，因为一个质数x的欧拉函数φ(x)=x-1;,又因为欧拉函数是一个积性函数

所以：

$phi[i*prime[j]]=phi[i]*(prime[j]-1);$


Code
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define N 1000010
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,k,phi[N],vis[N],prime[N],num;
ll ans;
vector<int> v;

void Euler(){
	phi[1]=1,vis[1]=true;
	for(int i=2;i<=n;i++){
		if(!vis[i]) prime[++num]=i,phi[i]=i-1;
		for(int j=1;j<=num && i*prime[j]<=n;j++){
			vis[prime[j]*i]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

int main(){
	n=read(),k=read();
	if(k==1) return printf("3\n"),0;
	Euler();
	for(int i=3;i<=n;i++) v.push_back(phi[i]);
	sort(v.begin(),v.end());
	for(int i=0;i<k;i++) ans+=v[i];
	printf("%lld\n",ans+2);
	return 0;
}
```


---

## 作者：HenryHuang (赞：4)

# 「CF1208G」 Polygons 

~~似乎我校神犇在很久以前和我提过这题？~~

首先有一点显而易见：这 $k$ 个多边形肯定至少有一个公共的顶点。假设我们将此点定义为起点。

那么对于一个正 $n$ 边形，每一条边所截的短弧所对应的圆心角大小相等，所以我们可以把顶点标记为 $\frac{1}{n},\frac{2}{n},\frac{3}{n},\cdots,\frac{n}{n}$。

那么有结论：对于任意一个正 $n$ 边形的顶点，当且仅当顶点标号为一个最简分数时才会被统计进答案。

证明也很简单，假设存在一个正 $n$ 边形顶点标号为非最简分数被统计进答案，那么将标号化为最简分数后其所对应的正多边形我们一定没有选择。但是显然这个正多边形的点数比我们刚才选择的正 $n$ 边形要少，这与题目要求相悖，故假设不成立。

因为 $n\ge 3$，所以有两个顶点没有被我们统计到：$\frac{1}{2} , \frac{n}{n}$ 。

考虑特判：

+ 当 $k=1$ 时我们一定会选择正三角形，其包含 $\frac{n}{n}$。

+ 当 $k=2$ 时我们可以选择正三角形和正四边形，其包含 $\frac{1}{2} , \frac{n}{n}$。
+ 当 $k\ge 3$ 时由于已经选择了正三角形和正四边形，未统计的两个顶点已经统计，所以不受影响。

考虑对一个正 $n$ 边形统计这样的最简分数，很显然可以发现答案就是 $\varphi(n)$。所以我们选择从 $\varphi(5)$ 开始的前 $k$ 大的欧拉函数值即可。

总时间复杂度为 $O(n\log_2n)$，使用基数排序可优化至 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int p[maxn],pri[maxn],phi[maxn],cnt;
int n,k;
int init(){
	phi[1]=1;
	for(int i=2;i<=n;++i){
		if(!p[i]){
			pri[++cnt]=i,phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&pri[j]*i<=n;++j){
			p[pri[j]*i]=1;
			if(i%pri[j]==0){
				phi[pri[j]*i]=phi[i]*pri[j];
				break;
			} 
			else phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	if(k==1) cout<<3<<'\n',exit(0);
	if(k==2) cout<<6<<'\n',exit(0);
	init();
	sort(phi+5,phi+n+1);
	long long ans=6;
	for(int i=5;i<=5+k-2-1;++i) ans+=phi[i];
	cout<<ans<<'\n';
	return 0;
}
```



---

## 作者：foreverlasting (赞：2)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### G Polygons

题意：给出$n$和$k$，要求在圆上用最少的点数使得能够找到$k$个正多边形而且这$k$个正多边形的长度小于等于$n$，求最少的点数。$1\leq k\leq n-2\leq 10^6$。

做法：考虑如果选择一个数$x$（不考虑$1$和$2$的情况），则显然与它不互质的数都已经选过了（否则选不互质的数会更优），那么这个数的贡献就会是$\phi(x)$。因此给$\phi$排个序，找前$k$个就可以了。时间复杂度$O(nlogn)$。

code:
```cpp
//2019.8.27 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
//#define pc(x) __builtin_popcountll(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
inline int read() {
    res s=0,ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline int read() {
//    res s=0,ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
const int N=1e6+10;
namespace MAIN{
    int n,k;
    int prim[N/10],tot,phi[N];
    bool vis[N];
    inline void MAIN(){
        phi[1]=1,n=read(),k=read();
        for(res i=2;i<=n;i++){
            if(!vis[i])prim[++tot]=i,phi[i]=i-1;
            for(res j=1;j<=tot&&prim[j]*i<=n;j++){
                vis[prim[j]*i]=1;
                if(i%prim[j]==0){phi[prim[j]*i]=phi[i]*prim[j];;break;}
                phi[prim[j]*i]=phi[i]*(prim[j]-1);
            }
        }
        sort(phi+1,phi+n+1);
        RG LL ans=0;
        for(res i=1;i<=k+2;i++)ans+=phi[i];
        printf("%lld\n",ans-(k==1));
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：MisaYuzuki (赞：1)

首先有一个关键但比较简单的观察，即存在一种最优图形，使得所有正多边形有至少一个公共的顶点。可以通过旋转子集的公共点去归纳证明这个东西。

那么可以把这个圆看做周长为 1 的线段，从公共点开始根据比例得到每个点的坐标。比如若存在一个正三角形，则三个点坐标为 $0,\frac{1}{3},\frac{2}{3}$。

接下来是比较关键的推导，也是笔者想了很久才想出来的步骤。

> 性质 1：若最优解中存在正 $x$ 边形，那么在不超过 $k$ 的前提下，$x$ 的因数 $d(d\ge 3)$ 会尽可能地取到。

这个很好理解的。正 $d$ 边形的每一个点必然是正 $x$ 边形上的一个点，所以取正 $d$ 边形会让正多边形个数 $+1$ 同时使得点个数不变。

> 性质 2：对于 $d\mid x$，$\phi(d)\le\phi(x)$。

欧拉函数的性质，不再赘述。

于是可以得到一个比较好用的推论：

> 推论 1：存在一种最优解，使得不存在两个数 $a,b$ 使得正多边形边数集合 $S$ 包含 $a$ 且不包含 $b$，且 $b\mid a$。

反证。如果存在，那么可以将 $a$ 替换成 $b$ 使得贡献尽可能小。$b$ 的贡献（即 $b$ 异于其他的新点）包含于 $a$ 的贡献，所以 $b$ 的贡献相对于 $a$ 的贡献小。

所以只要 $S$ 中存在一个数 $x$，则 $x$ 的所有 $\ge 3$ 因数都会存在于 $S$。由于 $x$ 的因数（可以默认 $1$ 和 $2$ 也存在，只有 $k=1$ 的时候特判一下答案为 $3$）都取到了，所以 $x$ 的贡献为 $\phi(x)$。

那么答案为 $\sum_{x\in S}\phi(x)$。

接下来题解区的统一操作都是将所有数按照 $\phi$ 值升序排序（第二维需要按照原本值排序以保证算法的正确性但没必要，因为只求 $\phi$ 值之和）选前 $k$ 个。这显然能保证答案一定大于这个值。

然后说一下答案合法性。因为对于 $x$ 的所有非本身正倍数的 $\phi$ 值都大于等于 $\phi(x)$，所以一定不会出现。同理，由于 $x$ 的所有因数的 $\phi$ 值都小于等于 $\phi(x)$，所以一定会出现。所以这可以保证统计的 $\phi$ 值之和就是选出的这个集合的答案。可以做到 $\Theta(n\log n)$ 实现。瓶颈在于排序。

给可爱的小妹妹轻轻地点个赞再走吧 qwq

---

## 作者：I_am_Accepted (赞：0)

我的做法要分两类。

和别的题解一样，加入一个 $n$ 边形的代价为 $\varphi(n)$，原因是可以把 $n$ 的真因子边形扣在 $n$ 边形里面，这样新增的点数就是 $[1,n]$ 中与 $n$ 互质的数的个数了。

所以我们的**大体思路**就是找到这 $n-2$ 个 $\varphi$ 中的前 $k$ 小再求和即为答案。

但是这样有**两个问题**：

* 这样保证选了 $n$ 边形一定选了 $\forall d|n,d$ 边形吗？

保证，因为 $\forall d|n,\varphi(d)\le \varphi(n)$，可以用欧拉函数定义证明，或者
$$
\frac{\varphi(ab)}{\varphi(a)}=\frac{\varphi(a)\varphi(b)\gcd(a,b)}{\varphi(a)\varphi(\gcd(a,b))}\ge\frac{\gcd(a,b)}{\varphi(\gcd(a,b))}\ge 1
$$

* 不存在 $1$ 边形和 $2$ 边形咋办？

我们分两类：一类不存在 $2k$ 边形，另一类存在。

对于不存在的，我们初始在圆上随意选一个点作为“一边形”作为基底即可。

对于存在的，我们还需要增加一个“二边形”，即在选的点圆上对峙点再选一个。

[简短的代码](https://codeforces.com/contest/1208/submission/175236017)

---

## 作者：myEnd (赞：0)

## 解题思路

显而易见的一点：这 $k$​ 个多边形肯定至少有一个公共的顶点。假设我们将此点定义为起点。

对于一个正 $n$​ 边形，每条边所截的短弧所对应的圆心角大小相等，所以我们可以把顶点记为这个分数序列： $\frac1n,\frac2n,\frac3n,\cdots,\frac nn$​​。

易得：对于任意一个正 $n$​ 边形的顶点，当且仅当顶点对应的分数是一个既约分数时才会被记录进答案。

反证法证明：假设存在一个正 $n$​ 边形顶点对应的分数不是既约分数却被统计进答案，那么将其对应分数化为既约分数后其所对应的正多边形必没有选择。但显然这个正多边形的点数比刚才选择的正 $n$​ 边形要少，与要求相悖，故假设不成立。

因为 $n\ge3$，所以有两个顶点没有被我们统计到：$\frac12,\frac nn$​ 。

考虑特判：

-   当 $k=1$​ 时我们一定会选择正三角形，其包含 $\frac nn$。
-   当 $k=2$​ 时我们可以选择正三角形和正四边形，其包含 $\frac 12,\frac nn$。
-   当 $k \ge 3$​​ 时由于已经选择了正三角形和正四边形，未统计的两个顶点已经统计，所以不受影响。

考虑对一个正 $n$​​ 边形统计这样的既约分数，很显然可以发现答案就是 $\varphi(n)$​​。所以选择从 $\varphi(5)$​​ 开始的前 $k$​​ 小的欧拉函数的值即可，最后要加上 $6$。

总时间复杂度为 $\mathcal O(n\log_2n)$​​​​（使用快排的复杂度，如果使用基数排序可以优化至 $\mathcal O\left(n\right)$​​）。

## 参考代码

```cpp
#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+5;
int p[maxn],pri[maxn],phi[maxn],cnt;
int n,k;

inline void quick_cppio(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

//模板
int EulerSolvePhi()
{
    phi[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(!p[i])
        {
            pri[++cnt]=i,phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&pri[j]*i<=n;++j)
        {
            p[pri[j]*i]=1;
            if(i%pri[j]==0)
            {
                phi[pri[j]*i]=phi[i]*pri[j];
                break;
            } 
            else phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
}

signed main()
{
    quick_cppio();
    cin >> n >> k;
    if(k==1) return cout << 3 <<'\n', 0;
    if(k==2) return cout << 6 <<'\n', 0;
    
    EulerSolvePhi();
    
    sort(phi+5,phi+n+1);
    long long ans=6;
    for(int i=5; i<=5+k-2-1; ++i) ans+=phi[i];
    cout<<ans<<'\n';
    return 0;
}
```

---

