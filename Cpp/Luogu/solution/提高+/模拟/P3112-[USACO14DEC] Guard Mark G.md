# [USACO14DEC] Guard Mark G

## 题目描述

农夫约翰和他的牛群正在玩飞盘。贝茜将飞盘扔向场地，但它正好飞向对方队伍的场地工马克！马克的身高为 $H$（$1 \leq H \leq 1,000,000,000$），但贝茜队伍中有 $N$ 头牛围在马克周围（$2 \leq N \leq 20$）。只有当它们堆叠起来的高度至少和马克一样高时，它们才能接住飞盘。每头牛都有一个高度、重量和力量。牛的力量表示可以堆叠在她上面的牛的总重量的最大值。

在这些限制条件下，贝茜想知道她的队伍是否可以搭建一个足够高的堆叠来接住飞盘，如果可以，那么这种堆叠的最大安全系数是多少。堆叠的安全系数是指在不超过任何牛的力量的情况下，可以添加到堆叠顶部的重量。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 10 
9 4 1 
3 3 5 
5 5 10 
4 4 5 ```

### 输出

```
2 ```

# 题解

## 作者：communist (赞：16)

### 看到没有完整的贪心题解，本蒟蒻决定来补充一发（~~没有完整证明的贪心是不圆满的~~）

不知道大家做过$NOIP2012$国王游戏没，这两道题思路相似

进入正题，看着就像贪心的一道题

怎么贪，按$height,strength,weight$排序好像都不合适

试图分析相邻两项交换的影响

一个$\text{\red{位置}}$的承重量可以这样表示$Rest_i=Strength_i-\sum{Weight_j}(j>i)$

同理，它的下一项可以如下表示$Rest_{i+1}=Strength_{i+1}-\sum{Weight_j}(j>i+1)$

相邻两项交换后是这样的

$Rest_i=Strength_{i+1}-Weight_i-\sum{Weigth_j}(j>i+1)$

$Rest_{i+1}=Strength_i-\sum{Weight_j}(j>i+1)$

我们要使稳定强度最大，即最大化$Min(Rest_i)$

还是考虑这相邻两项，我们考虑是否交换就转化为了判断这个东西

$max(min(PreRest_i,PreRest_{i+1}),min(NextRest_i,NextRest_{i+1}))$

为了简化式子

我们给上述每项同加$\sum{Weight_j}(j>i+1)$

上式化简为

$max((Pre)min(Strength_i-Weight_{i+1},Strength_{i+1}),(Next)min(Strength_{i+1}-Weight_i,Strength_i))$

观察到

$Strength_i>=Strength_i-Weight_{i+1},Strength_{i+1}>Strength_{i+1}-Weight_i$

如果

$Strength_{i+1}-Weight_i<=Strength_i-Weight_{i+1}<=Strength_i$

那么$Next$中$min$的一定是$Strength_{i+1}-Weight_i$，而$Pre$中每一项都大于它，即交换前总优于交换后

反之，交换后优于交换前

移项得，

$Strength_i+Weight_i>=Strength_{i+1}+Weight_{i+1}$

时，交换前更优

所以我们按照$Strength+Weight$从大到小排序即可

然后$2^n$枚举选择哪些牛，对于每种情况，求出$Rest$的最小值，然后在其中取最大即可

上代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
    int h,w,s;
}a[30];
int n,h;
bool c[30];
long long ans=-1;
bool cmp(const node &x,const node &y)
{
    return x.w+x.s>y.w+y.s;
}
void dfs(int x,int ch)
{
    c[x]=ch;
    if(x==n)
    {
        long long tmp=1e9,len=0;
        for(int i=1;i<=n;i++)
            if(c[i])
            {
                len+=a[i].h;
                long long sum=0;
                for(int j=i+1;j<=n;j++)
                    sum+=c[j]?a[j].w:0;
                tmp=min(tmp,a[i].s-sum);
            }
        if(len>=h)
            ans=max(ans,tmp);
        return;
    }
    dfs(x+1,1);
    dfs(x+1,0);
}
int main()
{
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i].h,&a[i].w,&a[i].s);
    sort(a+1,a+n+1,cmp);
    dfs(0,0);
    
    if(ans==-1)
        printf("Mark is too tall\n");
    else
        printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：漠寒 (赞：6)

## 分析

看到数据范围就直接想状压。对于每一种状态，它的高度是一定的，你更改上下次序只会影响上面还能放多少重量，所以用 $H[i]$ 预处理 $i$ 这个状态总高度多少，用 $f[i]$ 表示 $i$ 这个状态最多上面还能放多少重量，转移应是新放的牛的承重量和被转移的 $f$ 值减去该牛重量，最后找答案时，取最大的满足 $H[i]$ 大于等于所需高度的 $i$ 的 $f[i]$ 就行了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m;
int N;
int h[25],w[25],s[25];
int f[1100005];
int H[1100005];
int zy[25];
signed main()
{
	read(n);read(m);
	N=(1<<n)-1;
	for(int i=1;i<=n;i++){
		zy[i]=(1<<(i-1));
		read(h[i]);read(w[i]);read(s[i]);
	}
	for(int i=0;i<=N;i++){
		f[i]=-1e9;
		for(int j=1;j<=n;j++){
			if(i&zy[j])H[i]+=h[j];//预处理状态高度和 
		}
	}
	for(int i=1;i<=n;i++){
		f[zy[i]]=s[i];//预处理，先放一头 
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=n;j++){
			if(!(i&zy[j])){
				f[i|zy[j]]=max(f[i|zy[j]],min(f[i]-w[j],s[j]));
			}
		}
	}
	int ans=-1;
	for(int i=1;i<=N;i++){
		if(H[i]>=m&&f[i]>=0){
			ans=max(ans,f[i]);
		}
	}
	if(ans<0)puts("Mark is too tall");
	else cout<<ans;
	return 0;
}

```


---

## 作者：大菜鸡fks (赞：5)

贪心我没怎么想过，或者说是不会。这题n=20的范围状压还是很好写的。一开始傻了。设计了二维的数组，后来才发现高度并不用计入dp数组，取的牛都知道了总高度还不唯一？？（当然如果你闲的蛋疼用map存dp数组暴力更新复杂度也是没问题的。）

dp[S]=max(dp[S],min(dp[S^(1<<(i-1))]-w[i],s[i]));

tip：dp[0]初始化为inf,各数组开long long 

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=21;
int n,m,h[maxn],w[maxn],s[maxn];
inline void init(){
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&h[i],&w[i],&s[i]);
	}
}
const int inf=1e18;
int dp[1<<maxn],ans;
inline void solve(){
	ans=-inf; dp[0]=inf;
	for (int S=1;S<(1<<n);S++){
		dp[S]=-inf; int now=0;
		for (int i=1;i<=n;i++){
			if (S&(1<<(i-1))){
				dp[S]=max(dp[S],min(dp[S^(1<<(i-1))]-w[i],s[i]));
				now+=h[i];
			}
		}
		if (now>=m&&dp[S]>=0) ans=max(dp[S],ans);
	}
	if (ans<0) puts("Mark is too tall"); else printf("%lld\n",ans);
}
signed main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：fengenrong (赞：3)

我用的方法是贪心，我们只需要将所有的奶牛按照 $heavy+strong$ 从大到小进行排序，用深搜枚举所有种选奶牛的方案。对于每一只奶牛，我们只有选或不选。到最后的时候，我们再按题目求出 $ans$ 即可。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,h,ans[50005],ansa=-1,cnt;
struct op{
	int tall,heavy,strong;//分别表示高度，重量，载重量
}cow[505];
bool cmp(op a,op b)
{
	return (a.heavy+a.strong)>(b.heavy+b.strong);//按heavy+strong由大到小排
}
void dfs(int step,int tall)
{
	if(step>n)//到尽头
	{
		if(tall>=h)//符合题意
		{
			int sum=cow[ans[cnt]].heavy,sheng=cow[ans[cnt]].strong;//分别表示每头奶牛上方的总重量和还能够在牛塔最上方添加的最大重量
			for(register int i=cnt-1;i>=1;i--)//寻找载重量剩下的最小值
			{
				sheng=min(sheng,cow[ans[i]].strong-sum);//更新
				sum+=cow[ans[i]].heavy;//加上当前重量
			}
			if(sheng>ansa)//更新答案
			{
				ansa=sheng;
			}
		}
		return;
	}
	cnt++;
	ans[cnt]=step;
	dfs(step+1,tall+cow[step].tall);//选
	ans[cnt]=0;
	cnt--;
	dfs(step+1,tall);//不选
}
int main()
{
	cin>>n>>h;
	for(register int i=1;i<=n;i++)
	{
		cin>>cow[i].tall>>cow[i].heavy>>cow[i].strong;//输入
	}
	sort(cow+1,cow+n+1,cmp);//排序
	dfs(1,0); //深搜
	if(ansa==-1)
	{
		cout<<"Mark is too tall";//无解
	}
	else
	{
		cout<<ansa;
	}
	return 0;
} 
```

---

## 作者：JoyJoyGang (赞：2)

虽然标签里是贪心，但是我即想不到也不会证明 

而这个数据范围就很状压，因此我们选择状压 DP。

$dp[i]$ 状态 $i$ 表示时候的最大载重，$hi[i]$ 负责记录这个状态时候的高度，判断是否大于等于 $h$。

转移方程

```cpp
dp[i]=max(dp[i],min(dp[k]-a[j+1].y,a[j+1].z));
```

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int MA=10000005;
int n,h,maxn=0,hi[MA],dp[MA];
struct zh{
	int x,y,z,nu;
}a[MA];
signed main()
{
	scanf("%lld%lld",&n,&h);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].z);a[i].nu=a[i].z+a[i].y;
	}
	dp[0]=10000000000;
	for(int i=0;i<(1<<n);i++){
		int x=i,wei=0,pan=0,lu;
		for(int j=0;j<n;j++){
			int he=i&(1<<j);
			if(he!=0){
				int k=i-(1<<j);
				hi[i]+=a[j+1].x;dp[i]=max(dp[i],min(dp[k]-a[j+1].y,a[j+1].z));
			}
		}
		if(hi[i]>=h){
			maxn=max(maxn,dp[i]);
		}
	}
	if(maxn!=0){
		printf("%lld",maxn);
		return 0;
	}
	printf("Mark is too tall");
	return 0;
}
```


---

## 作者：ueettttuj (赞：2)

**贪心**

将奶牛按照$strength+weight$ , 从大到小排序。枚举所有种选奶牛的方案，将$strength+weight$ 值大的尽可能排到底部。如果方案满足要求，则更新当前的答案。

代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,h;
struct node{
	long long height,weight,strength,minus;
};
node a[21];
bool cmp(const node &qw,const node &we){
	return qw.minus>we.minus;
}
long long fa[21];
int main(){
	scanf("%lld %lld",&n,&h);
	for(long long i=1;i<=n;i++){
		scanf("%lld %lld %lld",&a[i].height,&a[i].weight,&a[i].strength);
		a[i].minus=a[i].weight+a[i].strength;
	}
	sort(a+1,a+n+1,cmp);
	long long mxx1;
	long long ans=0;
	long long pos=0;
	for(long long i=1;i<(1<<n);i++){       //枚举方案 
		long long t;
		t=i;
		long long op=0;
		pos=1;
		long long hh=0;
		bool s=0;
		while(t){
			mxx1=0;
			if(t%2==1){
				hh+=a[pos].height;
				mxx1=a[pos].weight;
				for(long long i=op;i>=1;i--){
					if(a[fa[i]].strength<mxx1){
						s=1;
						break;
					}
					mxx1+=a[fa[i]].weight;
				}
				if(s==1) break;
				fa[++op]=pos;
			} 
			t>>=1;
			pos++;
		}
		long long anss=1000000000;
		if(s==0 && hh>=h){
			mxx1=a[fa[op]].weight;
			anss=a[fa[op]].strength;
			for(long long i=op-1;i>=1;i--){
				anss=min(anss,a[fa[i]].strength-mxx1);
				mxx1+=a[fa[i]].weight;
			}
		}
		if(anss>ans && anss!=1000000000) ans=anss;
	}
	if(ans==0) printf("Mark is too tall\n");
	else printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_Kenma_ (赞：1)

# P3112 解题报告

## 前言

比较经典的邻项微扰模型，感觉是好题。

## 思路分析

发现直接贪心因为限制太多不可做。

注意到 $n$ 的范围很小，考虑二进制枚举每一头牛选或不选，这样只需要决策奶牛的顺序。

观察到这个问题有两个特点：

1. 答案大小只和奶牛的顺序有关；

2. 每一头奶牛只会受到它前面的奶牛的影响。

不难发现这是一个经典邻项微扰模型。

具体地，设 $i$ 和 $j$ 是相邻的两头奶牛。$w_i,w_j,s_i,s_j$ 和题面中含义保持一致。则有：

$i$ 在 $j$ 前：$ans_1=\min(s_i,s_j-w_i)$；

$i$ 在 $j$ 后：$ans_2=\min(s_j,s_i-w_j)$。

考虑设 $ans1 \le ans2$，反推 $i$ 和 $j$ 应当满足的限制。

- 当 $s_i \le s_j-w_i$ 时，不难发现 $ans_1 \le ans2$ 恒成立；

- 当 $s_j-w_i \le s_i$ 时，想要令 $ans_1 \le ans_2$，需要满足:$s_j-w_i \le s_i-w_j$，即 $w_j+s_j \le w_i+s_i$。

所以，将奶牛按 $s_i+w_i$ 为关键词升序排序，就是我们安排奶牛的最优次序。

这样就做完了，总体复杂度为 $O(n2^n)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
int n,m,ans,b[25],cnt;
struct node{
	int h,w,s;
}a[25];
bool cmp(node a,node b){
	return a.s+a.w<b.s+b.w;
}
int check(){
	int sumh=0,sumw=0,sums=0,ans=inf;
	for(int i=1;i<=cnt;i++){
		sumh+=a[b[i]].h;
	}
	if(sumh<m) return -1;
	for(int i=1;i<=cnt;i++){
		ans=min(ans,a[b[i]].s-sumw);
		sumw+=a[b[i]].w;
	}
	if(ans<0) return -1;
	else return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].h>>a[i].w>>a[i].s;
	}
	sort(a+1,a+1+n,cmp);
	ans=-1;
	for(int s=1;s<(1<<n);s++){
		cnt=0;
		for(int i=1;i<=n;i++){
			if(s&(1<<(i-1))) b[++cnt]=i;
		}
		ans=max(ans,check());
	}
	if(ans>=0) cout<<ans;
	else cout<<"Mark is too tall";
	return 0;
}
```

## 后记

要提升对经典模型的敏感程度。

---

## 作者：lzy20091001 (赞：1)

[洛谷 P3112 [USACO14DEC] Guard Mark G](https://www.luogu.com.cn/problem/P3112)

我们记 $w_i, h_i, s_i$ 分别为第 $i$ 头牛的重量、高度和力量。

## 状压 DP

注意到 $N \le 20$，考虑枚举每一头牛是否放入牛塔，将枚举的 $2 ^ N$ 种可能作为 DP 的阶段。具体地，设 $f_S$ 表示放入牛塔的牛的集合为 $S$ 时的可支持载重。显然，对于给定的 $S$，$f _ S$ 的值唯一依赖于牛的顺序，而题目要求的牛塔高度与顺序是无关的。所以我们不妨求解出所有 $f$ 的值，再选取高度达标的 $f$ 更新答案。

我们有以下状态转移方程：
$$
f_S = \max_{j \in S} \{\min \{f_{S \setminus \{ j \}} - w_j, s_j \} \}
$$
其中 $S \setminus \{ j \}$ 表示 $S$ 中除 $j$ 以外的元素构成的集合。

若 $j$ 是 $S$ 放在塔顶的牛，那么 $j$ 以下的 $S \setminus \{ j \}$ 的可支持载重被 $j$ 消耗掉了 $w _ j$，所以牛塔除了塔顶的可支持载重是 $f_{S \setminus \{ j \}} - w_j$；而整座牛塔的可支持载重是每一头牛的可支持载重中的最小值，因此最终整座牛塔的可支持载重是塔顶以下和塔顶取小，也就是 $\min \{f_{S \setminus \{ j \}} - w_j, s_j \}$。

由于转移依赖于子集，所以我们应按照放入的牛的数量即 $S$ 的元素个数从小到大计算 $f_S$。初始化 $f _ \varnothing = \infty$，这是因为在平地上放多重的牛都没关系；对于其他 $f$ 则初始化为 $-\infty$，这是因为可能存在某些牛无论如何安排顺序也无法组成可行的牛塔，为防止其他状态由这样非法的的状态转移而来，将其初始化为 $-\infty$。

此外注意答案可能为 $0$，因为可能牛塔刚好够高。因此 `ans` 应初始化为负数而非 $0$。

时间复杂度为 $\operatorname{O}(n \cdot 2 ^ n)$[^1]，空间复杂度为 $\operatorname{O}(2 ^ n)$。

```cpp
#include <cstring>
#include <iostream>

struct Cow
{
    int w, h, s;
} cow[25];

int f[(1 << 20) + 5];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, h, ans = -1;

    std::cin >> n >> h;
    for (int i = 0; i < n; i++)
        std::cin >> cow[i].h >> cow[i].w >> cow[i].s;

    // 初始化
    memset(f, -1, sizeof(f));
    f[0] = 1e9;

    // DP
    for (int i = 0; i < (1 << n); i++)
    {
        int hight = 0;
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
            {
                hight += cow[j].h;
                f[i] = std::max(f[i], std::min(f[i ^ (1 << j)] - cow[j].w, cow[j].s));
            }
        if (hight >= h) // 高度达标则更新答案
            ans = std::max(ans, f[i]);
    }

    if (ans > -1)
        std::cout << ans << "\n";
    else
        std::cout << "Mark is too tall" << "\n";

    return 0;
}
```

## 贪心优化

在上文的状压 DP 中，对于每个 $S$ 我们都枚举了塔顶元素，而我们希望塔顶元素可以不用枚举而通过其他方法 $\operatorname{O}(1)$ 得出。

结论是：对于给定的 $S$，取 $S$ 的元素中 $s + w$ 最小的作为塔顶，这样一定是最优的。

### 证明

由于最优子结构的性质，这个命题与 **对于给定的 $S$，将 $S$ 的元素按 $s + w$ 从小到大排序，小的靠上，大的靠下** 是等价的，我们证明后者。

利用贪心常用的证明策略「微扰」，只要我们证明 **交换任意两个符合我们的策略的元素是使得答案不劣的充要条件**，我们的策略就是正确的。

我们不妨设当前牛塔有 $t$ 头牛，第 $1$ 头为塔顶，第 $t$ 头为塔底。为了简化问题，我们可以将证明「任意两个」改为「相邻两个」，因为两者是同理的，而后者更方便考虑。形式化地，我们要证明：当且仅当 $s _ i + w _ i \ge s _ {i + 1} + w _ {i + 1}$，交换第 $i$ 头和第 $i + 1$ 头牛可以使答案不劣。

显然，我们只需要考虑第 $i$ 头和第 $i + 1$ 头牛，因为其他牛没有改变。

第 $i$ 头牛交换前的载重是 $s _ i - \sum _ {j = 1} ^ {i - 1} w _ j$，第 $i + 1$ 头牛交换前的载重是 $s _ {i + 1} - \sum _ {j = 1} ^ i w _ j$，两者对答案的贡献为 $\min \{s _ i - \sum _ {j = 1} ^ {i - 1} w _ j, s _ {i + 1} - \sum _ {j = 1} ^ i w _ j \}$（记作 $(1)$ 式。同理，交换后两头牛对答案的贡献为 $\min \{s _ i - (\sum _ {j = 1} ^ {i - 1} w _ j + w _ {i + 1}), s _ {i + 1} - \sum _ {j = 1} ^ {i - 1} w _ j \}$（记作 $(2)$ 式）。为方便观察我们给两式都加上 $\sum _ {j = 1} ^ {i + 1} w _ j$，于是 $(1) = \min \{ s _ i + w _ i + w _ {i + 1}, s _ {i + 1} + w _ {i + 1} \}, (2) = \min \{ s _ i + w _ i, s _ {i + 1} + w _ i + w _ {i + 1} \}$。

#### 必要性

交换使答案不劣即 $(1) \le (2)$。我们分类讨论两式中分别取了哪一个数。

1. $(1) = s _ i + w _ i + w _ {i + 1}, (2) =  s _ i + w _ i$，与 $(1) \le (2)$ 矛盾，舍去。
2. $(1) = s _ i + w _ i + w _ {i + 1}, (2) = s _ {i + 1} + w _ i + w _ {i + 1}$。则在 $(2)$ 式中有 $s _ {i + 1} + w _ i + w _ {i + 1} \le  s _ i + w _ i \Rightarrow s _ i + w _ i \ge s _ {i + 1} + w _ {i + 1} $。
3. $(1) = s _ {i + 1} + w _ {i + 1}, (2) =  s _ i + w _ i$，则因为 $(1) \le (2)$ 所以 $s _ i + w _ i \ge s _ {i + 1} + w _ {i + 1}$。
4. $(1) = s _ {i + 1} + w _ {i + 1}, (2) =  s _ {i + 1} + w _ i + w _ {i + 1}$，与第二种情况同理。

综上，$(1) \le (2) \Rightarrow s _ i + w _ i \ge s _ {i + 1} + w _ {i + 1}$。必要性得证。

#### 充分性

若已知 $s _ i + w _ i \ge s _ {i + 1} + w _ {i + 1}$，则 $(1) = s _ {i + 1} + w _ {i + 1}$。显然，$(2)$ 式无论取哪一个，结果都不小于 $s _ {i + 1} + w _ {i + 1}$。

综上，$s _ i + w _ i \ge s _ {i + 1} + w _ {i + 1} \Rightarrow (1) \le (2)$。充分性得证。

贪心策略正确性证毕。

### 应用

在 DP 前对所有牛按 $s + w$ 从小到大排序。在 DP 时，我们不枚举塔顶元素，而是直接找到 $S$ 中序号最小的元素作为塔顶，这样就完成了优化，时间复杂度优化至 $\operatorname{O}(2 ^ n)$。

找序号最小的元素可以用 GCC 内建函数 `int __builtin_ffs(int x)`[^2] $\operatorname{O}(1)$ 实现。

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

struct Cow
{
    int h, w, s;
};

Cow cow[25];
long long hight[(1 << 20) + 5], f[(1 << 20) + 5];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, h;
    long long ans = -1;

    std::cin >> n >> h;
    for (int i = 1; i <= n; i++)
        std::cin >> cow[i].h >> cow[i].w >> cow[i].s;

    std::sort(cow + 1, cow + n + 1, [](Cow a, Cow b)
              { return a.s + a.w < b.s + b.w; }); // C++11 开始支持 Lambda 表达式，OI 中用于结构体排序十分方便
    memset(f, -0x3f, sizeof(f));
    f[0] = 2e9;
    for (int i = 1; i < (1 << n); i++)
    {
        int j = __builtin_ffs(i); // 塔顶
        hight[i] = hight[i ^ (1 << (j - 1))] + cow[j].h;
        f[i] = std::max(f[i], std::min(f[i ^ (1 << (j - 1))] - cow[j].w, 1ll * cow[j].s));
        if (hight[i] >= h)
            ans = std::max(ans, f[i]);
    }

    if (ans != -1)
        std::cout << ans << "\n";
    else
        std::cout << "Mark is too tall" << "\n";

    return 0;
}
```

## 参考资料及注释

[^1]: [$\operatorname{O}(n \cdot 2 ^ n)$ 不是上界而是确切的时间复杂度。](https://www.luogu.com.cn/paste/lx0u7ewq)

[^2]: [位运算 - OI Wiki](https://oiwiki.org/math/bit/#内建函数)

---

## 作者：CR_Raphael (赞：1)

优质题~~(虽然我第一次打挂了)~~

- 法1：状压dp

dp[i]表示状态为i时的最优解，枚举最下面的那位，然后把该状态中其他牛堆叠的最优解放在最下面那位身上~~(好悲伤的感觉)~~

要记录每种状态的重量和高度。

例：当i = 二进制下的11001，有三头牛，1、2、5

枚举到第1头牛，就用01001的状态堆在1身上去更新；

枚举到第2头牛，就用10001的状态堆在2身上去更新；

枚举到第5头牛，就用11000的状态堆在5身上去更新。

复杂度O(2^n\*n)，可以过

- 法2：贪心

~~本着珍惜时间，节约社会资源，促进科学发展的伟大人道主义精神，~~ 我们来看看如何贪心：

设现在要堆的牛的总重为Ws，则最下面一头牛a1满足：

Sa1 >= Ws - Wa1

变形得:

Sa1 + Wa1 >= W

看到这里，我们可以猜测：答案与Sa1 + Wa1的大小有关 ~~(反正我猜到了)~~ 于是下面我们试着证明

设按Sa1 + Wa1从大向小堆叠的答案为ans1，ans就是当前所有牛的承载余额的最小值

把 Sa1 + Wa1 第二大的牛a2与a1交换，它还能承载的就是Sa1 + Wa2 - Ws 这玩意必然小于 Sa1 + Wa1 - Ws，对答案没有优化。

此时a1能承载的量显然大于a2的，所以也不会影响当前最小值。

所以有结论：**a1与a2交换不优于原序列**

类似的，**任意相邻的牛交换不优于原序列**

所以，**任意两头牛交换不优于原序列**

所以：**对于任意牛的搭配，原序列，按Sa1 + Wa1从大向小堆叠，为该搭配的最优答案**

所以进制枚举一下，在按Sa1 + Wa1大向小堆叠即可

复杂度O(2^n + n*log n), 撒花~

贪心AC代码如下：

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 20;
int n, hi;
int p;
int maxh=0;
long long int sum;

struct cow{
	int h;
	int w;
	int s;
} c[maxn];

bool cmp(cow a, cow b) {
	return a.s + a.w > b.s + b.w;
}

int main() {
	//freopen("guard.in", "r", stdin);
	//freopen("guard.out", "w", stdout);
	
	int i, t, j, z, ans=-1;
	
	scanf("%d%d", &n, &hi);
	
	p=(1<<n)-1;
	
	for(i=1; i <= n; i++) {
		scanf("%d%d%d", &c[i].h, &c[i].w, &c[i].s);
		sum+=c[i].h;
	}
	
	if(sum < hi){
		cout<<"Mark is too tall"<<endl;
		return 0;
	}
	
	sort(c+1, c+1+n, cmp);
	
	for(i=0; i <= p; i++) {
		t=i;
		sum=0;
		j=0;
		z=0x3f3f3f3f;
		while(t != 0) {
			j++;
			if(t % 2 == 0) {t=t>>1; continue;}
			
			sum+=c[j].h;
			
			z=min(z-c[j].w, c[j].s);
			
			if(z < 0) break;
			
			t=t>>1;
		}
		if(t != 0 || sum < hi) continue;
		if(z > ans) ans = z;
	}
	
	if(ans == -1) cout<<"Mark is too tall"<<endl;
	else cout<<ans<<endl;
	return 0;
}
```


---

## 作者：mengbierr (赞：1)

可以发现，下面牛的承重量与上面牛的顺序无关。从下往上安排牛的位置，那么一个牛的承重量就是未安排的其他牛的重量之和。

考虑如何安排牛的顺序，我们按照牛的重量+牛的承重量从大到小排序，这样贪心一定是最优的。（可以理解为这个牛在承受其他牛的基础上还能承受自己的重量）。统计答案随便记录一下即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
int read()
{
    char ch=getchar();int f=0,x=1;
    while(ch<'0'||ch>'9'){if(ch=='-') x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){f=(f<<1)+(f<<3)+ch-'0';ch=getchar();}
    return f*x;
}
struct data
{
    int val;
    int maxx;
    int weight;
}a[55];
bool operator < (const data &x,const data &y)
{
    return x.maxx+x.weight<y.maxx+y.weight;
}
int n,m,ans=0;
bool vis[55],flag;
priority_queue<data> q;
void dfs(int x)
{
    for(int i=0;i<=1;i++)
    {
        vis[x]=i;
        if(x==n)
        {
            int tot=0,sum=0,sweight=0,tempans=2000000000;
            for(int j=1;j<=n;j++)
            {
                if(vis[j])
                {
                    q.push(a[j]);
                    sum+=a[j].val;
                    tot++;
                    sweight+=a[j].weight;
                }
            }bool ac=1;
            if(sum<m) ac=0;
            
            while(!q.empty())
            {
                data temp=q.top();
                q.pop();
                sweight-=temp.weight;
                if(sweight>temp.maxx)
                {
                    ac=0;
                }
                else tempans=min(tempans,temp.maxx-sweight);
            }
            if(ac)
            {
                ans=max(ans,tempans);
                flag=1;
            }
        }
        else dfs(x+1);
    }
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        a[i].val=read();
        a[i].weight=read();
        a[i].maxx=read();
    }
    dfs(1);
    if(!flag) puts("Mark is too tall");
    else cout<<ans;
}

```

---

## 作者：Fractured_Angel (赞：0)

看题解大部分都是填表状压，来一篇刷表的。

#### Part 1 思路启发
第一眼看到的时候感觉是一个贪心，感觉应该是下面放耐力大的，上面放重量轻的，然后尽量选高一些的。但是相信你也看得出来，我上边对于贪心的这些修饰量词 **都是模糊的**。也就是在三个量的限制下，我们 **不太好进行贪心**。

我们又发现 $n \leq 20$ 这个条件。这个就很强的指向了 **搜索** 和 **状态压缩动态规划** 这两个算法。考虑实现难度，我们采取了后者。

#### Part 2 状态定义
按照题目所问来定义即可。定义 $dp_i$ 为在 $i$ 状态下耗能在牛塔上方添加的最大重量即可。

#### Part 3 转移方式
我们先来考虑怎么思考这个动态规划。

如果我们 **从下往上** 考虑，就会发现一个很严重的问题。就是我们不知道如果加上 $j$ 这个物品的重量，下面的物品是否承受得住。换言之，我们并不知道转移的顺序，不方便我们判断。

于是我们 **从上往下** 考虑，我们每次在最底下插入方块，计算已有的重量和 $sum$，判断 $j$ 物品的承受力是否大于等于 $sum$ 即可。这样我们天然有了顺序，不用再做其他考虑了。

#### Part 4 状态转移
我们先考虑怎样刻画 **在上方添加重量** 这一问题。我们考虑有一个塔，把塔中的每个方块的承受力记为 $m_k$，记其上方重量为 $s_k$。那么能在上方添加的最大重量一定就是 $\min\{m_k-s_k\}$。这很好理解，因为你要在上方添加重量的话，**必须满足每一个方块的要求**。

于是我们枚举当前状态 $i$，枚举当前要选的方块 $j$。如果 $j$ 的承受力小于 $sum$，那么就不能转移。

否则按照定义转移：
$$dp_{i|2^j}= \max(dp_{i|2^j},\min(dp_i,u-sum))$$

$u$ 代表 $j$ 方块的承受力。

简单来说就是 $i|2^j$ 这个状态还可以最大承受的重量就是 $i$ 状态的最大承受力和 $j$ 方块承受力减 $sum$ 这个限制取个最小值。

#### Part 5 计算答案
可以看到，我们上边根本就没有管 **身高** 这个限制。但为了满足题意，我们在求答案的时候，必须将其刻画出来。很简单，如果状态 $i$ 的身高和小于 $h$，那么就不计算在答案里就可以了。

最后的答案 $ans$ 就是所有符合条件的 $i$ 取个最大值。

#### Part 6 初始化
这东西有点坑其实。首先因为你要取最大值，所以你最好把所有状态都赋为负无穷。但是状态 $0$ 要赋为正无穷，因为状态 $0$ 没有任何限制。

并且转移时从 $0$ 开始，因为这是刷表法。

#### Part 7 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int INF = 1e9 + 5;
int n, h, DP[(1 << MAXN)];
struct Cow
{
	int a, b, c;
} A[MAXN];
int main()
{
	scanf("%d%d", &n, &h);
	for(int i = 0; i < n; i ++) scanf("%d%d%d", &A[i].a, &A[i].b, &A[i].c);
	memset(DP, -0x3f, sizeof(DP));
	DP[0] = INF;
	for(int i = 0; i < (1 << n); i ++)
	{
		int sum = 0;
		for(int j = 0; j < n; j ++)
			if(i & (1 << j)) sum += A[j].b; // the sum of weight 
		for(int j = 0; j < n; j ++)
		{
			if(i & (1 << j) || A[j].c < sum) continue;
			DP[i | (1 << j)] = max(DP[i | (1 << j)], min(DP[i], A[j].c - sum));
		}
	}
	int ans = -1;
	for(int i = 0; i < (1 << n); i ++)
	{
		int sum = 0;
		for(int j = 0; j < n; j ++)
			if(i & (1 << j)) sum += A[j].a;
		if(sum < h) continue;
		ans = max(ans, DP[i]);
	}
	if(ans != -1) printf("%d\n", ans);
	else puts("Mark is too tall");
	return 0;
} 
```

---

## 作者：GGapa (赞：0)

可以发现题目中的 $n$ 非常小，而且这个状态转移是有后效性的，应当使用状态压缩。

但是普通的状态压缩并不能满足这道题的条件，不仅是塔的构成，最顶上的牛也会对状态产生影响。增加一维，按照状态转移的思路转移即可。

先与处理一下每种集合的高度可能要方便一些。处理完之后按照经典的状压转移就足够了。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
typedef long long ll;
using VI = vector<int>;
const int N = 21;

bool solve() {
    int n, h; cin >> n >> h;
    int tp  =(1 << n) - 1;
    vector<VI> F(tp + 1, VI(n + 1, -1)); 
    vector<int> H(tp + 1);
    vector<array<int, 3>> A(n + 1);
    rep(i, 0, n - 1) rep(j, 0, 2) cin >> A[i][j];
    rep(c, 0, tp) rep(i, 0, n - 1) if((c >> i) & 1) H[c] += A[i][0];
    rep(i, 0, n - 1) F[(1 << i)][i] = A[i][2];
    int ans = -1;
    rep(c, 0, tp) {
        rep(i, 0, n - 1) if((c >> i) & 1) {
            rep(j, 0, n - 1) if(((c >> j) & 1) == 0) {
                auto &f = F[c | (1 << j)][j];
                f = max(f, min(F[c][i] - A[j][1], A[j][2])) ;
            }
        }
        if(H[c] >= h) 
            ans = max(ans, *max_element(F[c].begin(), F[c].end()));
    }
    if(ans == -1) return false;
    cout << ans << '\n';
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(!solve()) cout << "Mark is too tall\n";

    return 0;
}
```

---

## 作者：QSWei (赞：0)

  
我的第二道状压dp


基础部分楼下有了，我就发代码主体吧


/\*Miroerwf\_Q\*/

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define LL long long
using namespace std;
int n,height,h[21],w[212],v[21];
int f[(1<<20)+1];/*某个状态的耐力值;*/int g[(1<<20)+1];/*高度*/;
int b[21];/*每只奶牛的状态*/int maxx,ans=-1;
int main()
{
    cin>>n>>height;
    for(int i=1;i<=n;i++)
        cin>>h[i]>>w[i]>>v[i];
    b[1]=1;
    for(int i=2;i<=n;i++)
        b[i]=b[i-1]<<1;/*预处理每只奶牛状态*/
    maxx=(1<<n)-1;
    f[0]=0x7fffffff;/*由于需要判断耐力值是否足够,所以要赋一个较大值;*/
    for(int x=0;x<=maxx;x++)
        for(int i=1;i<=n;i++){
            if(x&b[i])
                continue;/*如果选过了,继续.*/
            int tmp=x|b[i];/*把第i只奶牛选上*/
            if(f[x]<w[i])
                continue;/*判断没选当前奶牛时的状态的耐力值在选上当前奶牛后是否满足需求,若不满足,继续.*/
            int cnt=min(f[x]-w[i],v[i]);/*影响奶牛选择的耐力值其实是耐力值最小的那只奶牛,f[x]-w[i]是上一个状态的耐力值减去当前重量,*/
```
/\*                 即从上个状态推出的最小耐力值,把它和当前奶牛的耐力值进行比较,得到最小耐力值.\*/
            
```cpp
            f[tmp]=max(f[tmp],cnt);/*更新最小耐力.*/
            g[tmp]=g[x]+h[i];/*高度可以更新.*/
            if(g[tmp]>=height)
                ans=max(f[tmp],ans);/*判断高度是否满足,若满足,更新答案.*/
        }
    if(ans<0)
        printf("Mark is too tall");
    else
        cout<<ans;
    return 0;
}

```

---

## 作者：NewErA (赞：0)

****第一次写状压DP，写个题解纪念一下


初看题时，感觉要用dp，但维度较多，不好写出迭代式


题中提及到共N头牛(2 <= N <= 20)，从而联想到可以用状压来解决。将所有牛选或是不选这个状态用一个十进制数表示，而非数组，从而成功降低维度。


如果n过大，会导致state值过大，从而无法将所有状态用十进制表示。


状压的几个基本位运算：


1.判断一个数字x二进制下第i位是不是等于1。


方法：if ( ( ( 1 << ( i - 1 ) ) & x ) > 0)


2.将一个数字x二进制下第i位更改成1。


方法：x = x | ( 1<<(i-1) )


3.把一个数字二进制下最靠右的第一个1去掉。


方法：x=x&(x-1)


****这里res=0这个结果要好好考虑一下，看了不少ac代码，不少其实都有问题，只是数据太弱了┑(￣Д ￣)┍


附上代码

```cpp
#include<bits/stdc++.h>

using namespace std;
int n,h;
int dp[1100000];

struct cow
{
    int height,weight,strength;
}a[22];

int main()
{
    cin >> n >> h;
    memset(dp,-1,sizeof(dp)); //ÕâÀï³õÊ¼»¯Îª-1·Ç³£±ØÒª
                              //dp[i]=0±íÊ¾ÉÏÃæÎÞ·¨ÔÙ·Å£¬¶ødp[i]=-1±íÊ¾ÕâÖÖÇéÐÎ²»´æÔÚ¡£·ÀÖ¹resÓëdp[i]±È½ÏÊ±½«res¸³Öµ³É0¡£ 
    for(int i=1;i<=n;i++) cin >> a[i].height >> a[i].weight >> a[i].strength;
    for(int i=0;i<=n-1;i++) dp[1 << i]=a[i+1].strength;
    
    int res=-1; //res=0±íÊ¾ÉÏÃæÎÞ·¨ÔÙ·ÅÁË¡£¶øres=-1±íÊ¾ÎÞ·¨´ïµ½¹æ¶¨¸ß¶È¡£ 
                //ÒªÌØ±ðÐ¡ÐÄÌØÊâÇé¿öÏÂÌØÊâÖµµÄÑ¡È¡£¡£¡£¡ 
    for(int i=1;i<=((1<<n) -1);i++) //ËãÊõÔËËã·û±ÈÎ»ÔËËã·ûÓÅÏÈ¼¶¸ß£¡£¡£¡ 
    {
        for(int j=1;j<=n;j++)
            if(!(i & 1<<(j-1)) && a[j].weight<=dp[i]) 
                dp[i | 1<<(j-1)]=max(dp[i | 1<<(j-1)],min(dp[i]-a[j].weight,a[j].strength));    
        
        int sum=0;
        for(int j=1;j<=n;j++) if(i & 1<<j-1) sum+=a[j].height; //ÕâÀïÆäÊµ¿ÉÒÔ¸ÄÎªÒ»¸öÊý×é×¨ÃÅ´æ´¢¸ß¶È 
        if (sum>=h) res=max(res,dp[i]);

    }
    
    if(res>=0) cout << res; //Í¬ÉÏ,µ±res=0Ê±Í¬ÑùÊÇÒªÊä³öµÄ 
    else cout << "Mark is too tall";
    
    return 0;
}
```
最后看到了几个比较好的学习状压的博客：http://blog.csdn.net/lmyclever/article/details/6671923

http://blog.csdn.net/u011077606/article/details/43487421


---

## 作者：zx2003 (赞：0)

状压dp好题，O(n2^n)裸做即可。

f[i]表示集合i的奶牛最大的剩余耐力值。

f[i]=max(min(f[i-j]-w[j],w[j])),j属于I,此处减为集合操作，意为除去，可用xor实现

(即尝试枚举哪头奶牛在最上面)

```cpp
const ma=1 shl 20-1;
const maxi=1 shl 30;
var
 f,hh:array[0..ma] of longint;
 h,w,s:array[1..20] of longint;
 i,n,hi,j,k,a,l,ans:longint;
function max(x,y:longint):longint;
begin
 if x>y then exit(x)
  else exit(y)
end;
function min(x,y:longint):longint;
begin
 if x>y then exit(y);
 exit(x)
end;
begin
 f[0]:=maxi;
 readln(n,hi);
 for i:=1 to n do
 begin
  readln(h[i],w[i],s[i]);
  f[1 shl (i-1)]:=s[i];
  hh[1 shl (i-1)]:=h[i]
 end;
 ans:=-1;
 for i:=1 to 1 shl n-1 do
 begin
  if i=4 then
  begin
   j:=j
  end;
  j:=i;
  k:=0;
  a:=-1;
  while j>0 do
  begin
   inc(k);
   if j xor (j shr 1 shl 1)=1 then
   begin
    l:=i xor (1 shl (k-1));
    hh[i]:=hh[l]+h[k];
if w[k]<=f[l] then a:=max(a,min(f[l]-w[k],s[k]))
end;
   j:=j shr 1
  end;
  f[i]:=a;
  if hh[i]>=hi then
   if a>ans then
    ans:=a
 end;
 if ans=-1 then writeln('Mark is too tall')
  else writeln(ans)
end.
```
搜索应该也可以，但这么好的状压dp题，还是拿来练练手吧

---

## 作者：Ray662 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P3112)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-p3112)

---

### 分析

这里记身高、体重、耐力值分别为：$h_i, w_i, t_i$。

$n$ 规模很小，容易想到状压。

定义 $f_{s}$：子集 $s$ 中的奶牛能形成的堆叠的最大安全系数。

显然有：$f_{\{\}} = {}+ \infty$（空集的安全系数显然无穷大）。

则易得答案为：

$$
\max_{s \subseteq \{1, 2 \cdots n\}} f_{s}
$$

上式中 $s$ 需要满足：

$$
\sum_{i \in s}h_i \le H
$$

状态转移方程（这里是将牛 $i$ 放在最顶端，并且要求 $f_{s - \{i\}} \ge w_i$）：

$$
f_{s} = \max_{i \in s}\{\min(f_{s - \{i\}} - w_i, t_i)\}
$$

直接递推实现，时间 $(n \times 2^n)$。

---

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 22;
int n, H;
long long ans = -1, f[1 << N];
struct cow { int h, w, t; } C[N];
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> H;
	for (int i = 0; i < n; i ++ )  cin >> C[i].h >> C[i].w >> C[i].t;
	f[0] = 9e18;
	for (int s = 1; s < (1 << n); s ++ ) {
		long long hs = 0;
		f[s] = -1;
		for (int i = 0; i < n; i ++ )
			if ((1 << i) & s) {
				const cow & c = C[i];
				long long nd = f[s ^ (1 << i)];
				hs += c.h;
				if (nd >= c.w)  f[s] = max(f[s], min(nd - c.w, (long long)c.t));
			}
		if (hs >= H)  ans = max(ans, f[s]);
	}
	if (ans == -1)  puts("Mark is too tall");
	else  printf("%lld\n", ans);
	return 0;
}
```

---

