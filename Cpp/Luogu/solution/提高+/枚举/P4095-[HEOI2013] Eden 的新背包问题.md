# [HEOI2013] Eden 的新背包问题

## 题目背景

“ 寄 没 有 地 址 的 信 ，这 样 的 情 绪 有 种 距 离 ，你 放 着 谁 的 歌 曲 ，是 怎 样 的 心 情 。 能 不 能 说 给 我 听 。”

## 题目描述

失忆的 Eden 总想努力地回忆起过去，然而总是只能清晰地记得那种思念的感觉，却不能回忆起她的音容笑貌。

记忆中，她总是喜欢给 Eden 出谜题：在 valentine's day 的夜晚，两人在闹市中闲逛时，望着礼品店里精巧玲珑的各式玩偶，她突发奇想，问了 Eden 这样的一个问题：有 $n$ 个玩偶，每个玩偶有对应的价值、价钱，每个玩偶都可以被买有限次，在携带的价钱 $m$ 固定的情况下，如何选择买哪些玩偶以及每个玩偶买多少个，才能使得选择的玩偶总价钱不超过 $m$，且价值和最大。

众所周知的，这是一个很经典的多重背包问题，Eden 很快解决了，不过她似乎因为自己的问题被飞快解决感到了一丝不高兴，于是她希望把问题加难：多次询问，每次询问都将给出新的总价钱，并且会去掉某个玩偶（即这个玩偶不能被选择），再问此时的多重背包的答案（即前一段所叙述的问题）。

这下 Eden 犯难了，不过 Eden 不希望自己被难住，你能帮帮他么？

## 说明/提示

#### 样例解释

一共五种玩偶，分别的价钱价值和限购次数为 $(2,3,4)$， $(1,2,1)$， $(4,1,2)$， $(2,1,1)$， $(3,2,3)$。

五个询问，以第一个询问为例。

第一个询问表示的是去掉编号为 $1$ 的玩偶， 且拥有的钱数为 $10$ 时可以获得的最大价值，则此时剩余玩偶为 $(2,3,4$)，$(4,1,2)$， $(2,1,1)$，$(3,2,3)$，若把编号为 $0$ 的玩偶买 $4$ 个（即全买了），然后编号为 $3$ 的玩偶 买一个，则刚好把 $10$ 元全部花完，且总价值为 $13$。可以证明没有更优的方案了。

注意买某种玩偶不一定要买光。

---

#### 数据规模与约定

- 对于 $10\%$ 的数据，保证 $n \leq 10$。
- 另外存在 $20\%$ 的数据，保证  $n \leq 100$，$c_i = 1$，$q \leq 100$。
- 另外存在 $20\%$ 的数据，保证 $n \leq 100$，$q \leq 100$。
- 另外存在 $30\%$ 的数据，保证 $c_i = 1$。
- 对于 $100\%$ 的数据，保证  $1 \leq n \leq 1000$，$1 \leq q \leq 3\times 10^5$， $1 \leq a_i,b_i,c_i \leq 100$，$0 \leq d_i < n$，$0 \leq e_i \leq 1000$。



## 样例 #1

### 输入

```
5 
2 3 4 
1 2 1 
4 1 2 
2 1 1 
3 2 3 
5 
1 10 
2 7 
3 4 
4 8 
0 5```

### 输出

```
13 
11 
6 
12 
4 
```

# 题解

## 作者：lqhsr (赞：53)

# 保证你能懂&&无脑坑点揭示

这题一看显然是个**多重背包二进制拆分转成01背包**

## 然而这样只有50pts

暴力就不解释啦，具体看100pts的解释吧

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c,ji,f[100005];
struct node{
	int s,id;
}w[100000],v[100000];
inline int read(){
	register int x=0;
	register char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int main(){
	cin>>n;
	for(register int i=1;i<=n;++i){
		register int cw=read(),cv=read(),c=read();
		register int now=1;
		while(now<=c){
			w[++ji].s=cw*now,v[ji].s=cv*now;
			w[ji].id=i,v[ji].id=i;
			c-=now,now*=2;
		}
		if(c){
			w[++ji].s=cw*c,v[ji].s=cv*c;
			w[ji].id=i,v[ji].id=i;
		}
	}
	cin>>m;n=ji;
	for(register int l=1;l<=m;++l){
		register int cn=read()+1,V=read();
		for(register int i=1;i<=n;++i){
			if(w[i].id!=cn){
				for(register int j=V;j>=w[i].s;--j){
					f[j]=max(f[j],f[j-w[i].s]+v[i].s);
				}
			}
		}
		printf("%d\n",f[V]);
		memset(f,0,sizeof(f));
	}
}
```

## 100pts:

考虑怎么优化

我们知道背包其实就是把每一种放法都考虑一遍，我们设的状态是**f[i][j]表示考虑到第i个总体积为j的最大价值**

**而我们要求的是不考虑第i种物品时的最大价值**

诶 这不就是f[i-1][V]么～～～

不对其实这样后面的物品就没有被考虑到

那怎么办呢

于是我们可以**从后往前再DP一次表示从后面往前面考虑的最大价值**

**把两个背包的结果合并**就是所求啦

## 然而还有一个恶心的地方

由于搬运题目的人的疏忽

```
1 ≤ q ≤ 3*105
```
其实是
```
1 ≤ q ≤ 3*1e5
```
我在这上面WA了整整10次。。。~~(所以我才来写题解纪念纪念)~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,c,ji;
ll f1[100005][1005],f2[100005][1005];
struct node{
    int id;ll s;
}w[300005],v[300005];
inline int read(){
	register int x=0;
	register char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int main(){
	cin>>n;
	for(register int i=1;i<=n;++i){
		register int cw=read(),cv=read(),c=read();
		register int now=1;
		while(now<=c){//二进制拆分，不懂的可以记住
			w[++ji].s=cw*now,v[ji].s=cv*now;
            w[ji].id=i,v[ji].id=i;
			c-=now,now*=2;
		}
		if(c){
			w[++ji].s=cw*c,v[ji].s=cv*c;
            w[ji].id=i,v[ji].id=i;
		}//拆分结束
	}
	cin>>m;
	n=ji;//更新物品数量
	for(int i=1;i<=n;i++){//正向01背包
		for(int j=0;j<=1000;j++)f1[i][j]=f1[i-1][j];
		for(int j=1000;j>=w[i].s;j--){
			f1[i][j]=max(f1[i][j],f1[i-1][j-w[i].s]+v[i].s);
		}
		
	}
	for(int i=n;i>=1;i--){//反向01背包
		for(int j=0;j<=1000;j++)f2[i][j]=f2[i+1][j];
		for(int j=1000;j>=w[i].s;j--){
			f2[i][j]=max(f2[i][j],f2[i+1][j-w[i].s]+v[i].s);
		}
		
	}
	for(int k=1;k<=m;k++){
		int cn=read()+1,V=read();
		ll ans=0;
        int l=0,r=0;//因为同一种物品可能已被拆成多件物品而这种物品都不能被考虑于是我们要找到不包括这种物品的f1和f2
        while(w[l+1].id<cn&&l<n)++l;
        r=l;
        while(w[r+1].id<=cn&&r<n)++r;
		for(int j=0;j<=V;j++){//这是枚举分配给该种物品之前的物品多少空间
			ans=max(ans,f1[l][j]+f2[r+1][V-j]);//不懂的可以拿样例模拟一下，温馨提示：样例可被拆分成9件物品
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Gu_Pigeon (赞：33)

注：本人是在[这篇博文](https://blog.csdn.net/MirrorGray/article/details/51056604)懂了这道题的，可以去康康哦qwq。

# 为了信仰发一篇正解！（雾）
发现目前的所有题解都是从前往后和从后往前跑dp然后每次枚举前后的钱数时间复杂度$\large\text O(NV\log c_i + q\times e_i)$，可以被某些不怀好意的数据卡掉？（可能数据略水），所以在此发一篇cdq分治题解。

> "考虑cdq分治，`solve(l,r)`表示删掉`[l,r]`这段区间的物品后的背包数组，那么`solve(l,mid)`这个背包数组一定包含`(mid+1,r)`里的所有物品，所以只需用`(mid+1,r)`这些物品更新`solve(l,r)`这个背包后传入`solve(l,mid)`即可。 `solve(mid+1,r)`时同理，用`(l,mid)`的物品更新`solve(l,r)`这个背包，然后传入`solve(mid+1,r)`即可。"
>
> ————————————————
>
> 版权声明：本文为CSDN博主「MirrorGray」的原创文章，遵循CC 4.0 by-sa版权协议，转载请附上原文出处链接及本声明。
>
> 原文链接：https://blog.csdn.net/mirrorgray/article/details/51056604

（上面是$\text {Ctrl+C}\ \&\ \text {Ctrl+V}$出现的，就不删了~~懒得删~~）

可能~~雾~~悟到了什么？再来分析一波：

处理物品的区间，解决去掉一个物品之后的dp值，很明显没有直接通过算出完整的dp值然后删去一个物品的方法，所以某些同学想到了记录$1\sim i-1\ \&\ i+1\sim n$ 的dp值然后相加就好了~~可惜会被卡~~，所以……cdq分治出现！

cdq分治的主要思想是将问题的区间分为两部分，处理完左半部分后处理左边对右边的影响，然后再完成右半部分的更新。

但是这题不大一样，由于删去物品 `i` 的结果是受其他所有物品影响的，所以左半部分同时也受右半部分影响，所以要跑两趟，具体步骤如下：

1. 更新右半部分dp值
2. 递归处理左半部分
3. 还原（maybe回溯？）
4. 更新左半部分dp值
5. 递归处理右半部分

cdq分治(?)的代码如下：
```cpp
void cdq(int d, int l, int r)//d是递归深度，l & r 是左右端点
{
    if (l == r)//边界判断
    {
        for (int i = head[l]; i; i = nxt[i]) ans[pos[i]] = f[d - 1][money[i]];//得到答案
        return;
    }
    int mid = (l + r) >> 1;
    memcpy(f[d], f[d - 1], sizeof(f[d]));//从上一层转移
    for (int i = mid + 1; i <= r; i++) dp(d, i);//处理右半部分
    cdq(d + 1, l, mid);//递归左半部分
    memcpy(f[d], f[d - 1], sizeof(f[d]));//还原
    for (int i = l; i <= mid; i++) dp(d, i);//处理右半部分
    cdq(d + 1, mid + 1, r);//递归右半部分
}
```

似乎有一些迷？~~嗯我也是~~

还有另外一种思路叫做：

# $ \Huge\textbf{线段树分治} $

~~虽然字这么大其实写出来的代码跟上面一毛一样~~

那就先来一棵线段树：

![](https://cdn.luogu.com.cn/upload/pic/75429.png)

（AD:本图由[visualgo.net](https://visualgo.net/en/segmenttree)友情提供）

**注意：因为这个图上是从0开始的，所以这一部分也是按0开始讨论，其他地方都从1开始（个人习惯）**

对于物品0，在除了删掉0物品的其他询问中物品0都是有用的，所以我们给删去$1 \sim n-1$的这些操作加上一个数值0。

![](https://cdn.luogu.com.cn/upload/pic/75432.png)

（线段树的区间修改，很简单吧）

然后对于每一个数 `i`，对其所影响的区间`[0,i-1] & [i+1,n-1]`，进行修改，最后得出：

![](https://cdn.luogu.com.cn/upload/pic/75437.png)

有没有什么发现？

“对于删除某一个物品`i`，只需要将区间`[i,i]`的节点到根节点上的所有集合合并然后就可以得出答案！”

没有问题，我们只需要遍历一下这个线段树，然后在上一层的基础上再加入新的集合，更新dp值，到达叶子节点`[i,i]`时，就计算出了删去物品`i`的结果！

那么如何存储每一个节点被覆盖的集合呢？用`std::set`?~~那不就树套树了吗~~

继续观察每一个节点对应的集合与区间，有没有什么新发现？

$\large\texttt {对于每一个节点，其受到修改的集合的区间，就等于其兄弟节点所代表的区间!}$

~~喵啊喵~~

那么我们再考虑一下其具体步骤：

### 对于左儿子：

1. 处理需要添加的物品（也就是那个集合），相当于更新右半部分dp值
2. 递归到下一层，处理左半部分

### 然后记得要：

3. 还原，使dp数组回到原状态……

### 对于右儿子：

4. 更新左半部分的dp值
5. 深入一层，处理右半部分

emmm…看起来没什么问题…等等！

来对比一下上面cdq分治的过程：

>1. 更新右半部分dp值
>2. 递归处理左半部分
>3. 还原（maybe回溯？）
>4. 更新左半部分dp值
>5. 递归处理右半部分

~~没错，其实基本上可以是同一段代码~~

个人认为，换一种方式理解（或许）会更加深入……

咳咳，所以分治的部分也就是这样差不多了，那么来大致计算一下复杂度：

$\text{input \& output:O(n+q)}$，基本无影响

那么分治的时间复杂度：

$\text {T(n) = T(n/2) + O(dp)}$

因此我们需要一个尽量快的方法解决多重背包问题，考虑使用[**单调队列(戳我)**](https://blog.csdn.net/flyinghearts/article/details/5898183)

所以最后的时间复杂度为$\text O(nlognV)$

(V是背包容量，即钱数，$Max\{e_i\}$)

然后我们就偷税的AC了此题！

$\LARGE Code\ Below$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 333333
#define id first
#define val second

int f[12][1024], ans[N], c[N], lim[N], w[N], tot, head[N], nxt[N], pos[N], money[N], n, q;

void addques(int x, int y, int z)
{
    pos[++tot] = z;
    money[tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}//奇 怪的链式存储询问，秒啊

void dp(int d, int x)
{
    for (int i = 0; i < c[x]; i++)
    {
        deque<pair<int, int>> q{ make_pair(0, f[d][i]) };
        for (int j = 1; j * c[x] + i <= 1000; j++)
        {
            while (!q.empty() && q.back().val <= f[d][j * c[x] + i] - j * w[x]) q.pop_back();
            q.push_back(make_pair(j, f[d][j * c[x] + i] - j * w[x]));
            while (!q.empty() && q.front().id < j - lim[x]) q.pop_front();
            f[d][j * c[x] + i] = max(f[d][j * c[x] + i], q.front().val + j * w[x]);
        }
    }
}//在O(NV)时间内使用单调队列完成多重背包

void cdq(int d, int l, int r)
{
    if (l == r)
    {
        for (int i = head[l]; i; i = nxt[i]) ans[pos[i]] = f[d - 1][money[i]];
        return;
    }
    int mid = (l + r) >> 1;
    memcpy(f[d], f[d - 1], sizeof(f[d]));
    for (int i = mid + 1; i <= r; i++) dp(d, i);//加入右半部分dp值
    cdq(d + 1, l, mid);//递归处理左半部分
    memcpy(f[d], f[d - 1], sizeof(f[d]));//还原
    for (int i = l; i <= mid; i++) dp(d, i);//加入左半部分dp值
    cdq(d + 1, mid + 1, r);//递归处理右半部分
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d%d", c + i, w + i, lim + i);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        addques(a + 1, b, i);
    }
    cdq(1, 1, n);
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
```


---

## 作者：cyy233 (赞：17)

   这道题有个难点就是**多重背包**，普通做法的复杂度杂度太大了，
   
   虽说单调队列复杂度是O（VN），但~~我不会~~，所以有二进制做法O(NVlogci)
   
 我做过一道奥数题，把1000分成10份，使可以表示出1~1000的任何数，解法很简单
 {1,2,4,8,16,32,64,128,256,489}，
 
 就是把它们**分成2的0~n-1次方，剩下部分n-2的n次方+1**，100就可以表示为1,2,4,8,16,32,37,就这样，每次分解都当01背包解。
 
 最后可能有剩余，就是例子中的489和37，要再做一遍。
        

推荐例题：鬼谷子的钱袋P2320，不过要反着想.
    
  还有个问题，拆玩偶？
	不妨把每个问题分为两部分，di-1和di+1。
    
    
定义dp[i][j]为从**前往后拿，前i个数价格为j是最大价值。** 

定义dp1[i][j]为**从后往前拿，后i个数价格为j是最大价值。**

公式：
ans=max{dp[di-1][j]+dp[di+1][ei-j]}

j为0~n-1任意自然数。

因为di那走了所以少了1。

还有状态转移方程：

dp[i][j]=max(dp[i][j-bi*p]+ai * p,dp[i][j]);

# 程序参考了前面的大佬，因为老师用他的程序教我们的
程序如下

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL V=1000,n,q;
LL dp[1010][1010],dp1[1010][1010];
struct CCFS{
	LL x,y,z;
}a[1010];
int rd()
{
    int res=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar());
    for(;isdigit(ch);ch=getchar())
        res=(res<<3)+(res<<1)+ch-'0';
    return res;
}
void CCF(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=V;j++)dp[i][j]=dp[i-1][j];
		LL re=a[i].z,p=1;
		while(re>=p){
			for(int j=V;j>=a[i].x*p;j--)
				dp[i][j]=max(dp[i][j],dp[i][j-a[i].x*p]+a[i].y*p);
				re-=p;p=p<<1;
		}
		if(re){
			for(int j=V;j>=a[i].x*re;j--)
				dp[i][j]=max(dp[i][j],dp[i][j-a[i].x*re]+a[i].y*re);
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=V;j++)dp1[i][j]=dp1[i+1][j];
		LL re=a[i].z,p=1;
		while(re>=p){
			for(int j=V;j>=a[i].x*p;j--)
				dp1[i][j]=max(dp1[i][j],dp1[i][j-a[i].x*p]+a[i].y*p);
				re-=p;p=p<<1;
		}
		if(re){
			for(int j=V;j>=a[i].x*re;j--)
				dp1[i][j]=max(dp1[i][j],dp1[i][j-a[i].x*re]+a[i].y*re);
		}
	}
}
int main()
{
	n=rd();
	for(int i=1;i<=n;i++){
		a[i].x=rd();a[i].y=rd();a[i].z=rd();
	}
	CCF();
	q=rd();
	while(q--){
		LL ans=0,c=rd()+1,f=rd();
		for(int i=0;i<=f;i++)
			ans=max(ans,dp[c-1][i]+dp1[c+1][f-i]);
		cout<<ans<<endl;
	}
	return 0;
}
```




---

## 作者：UltiMadow (赞：9)

分治大法吼啊

之前有大佬讲分治讲的很清楚了，但是他是用的是单调队列

所以我来写一篇用二进制拆分的分治题解

思路和那位大佬差不多，这里就不细讲了

我就来提供一种更加简便的写法

代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 1010
using namespace std;
int n,q;
int f[MAXN],mem[12][MAXN],ans[MAXN][MAXN];
//f为背包数组，mem记录每一层转移时的状态，ans[i]表示不取i物品时的背包数组
int le[MAXN],ri[MAXN],cnt;
//le[i]表示二进制拆分后i类物品的左端点编号
//ri[i]表示二进制拆分后i类物品的右端点编号
int c[MAXN<<4],w[MAXN<<4];
//c，w为二进制拆分后物品的价值，体积
void dp(int l,int r)//背包转移编号为l到r的物品
{
	for(int i=le[l];i<=ri[r];i++)//l到r物品二进制拆分后所包含物品区间
		for(int j=1000;j>=w[i];j--)
			f[j]=max(f[j],f[j-w[i]]+c[i]);
}
void cdq(int dep,int l,int r)
//dep记录当前深度，方便还原背包数组
{
	if(l==r){memcpy(ans[l],f,sizeof(f));return;}
	//当l=r时说明除了l其他的都转移到背包数组里了，直接把背包数组复制到ans[l]里
	int mid=l+r>>1;
	memcpy(mem[dep],f,sizeof(f));
	//转移之前先把原来的背包数组存下来，方便等会还原背包数组
	dp(mid+1,r);cdq(dep+1,l,mid);
	memcpy(f,mem[dep],sizeof(f));
	//在转移左区间的背包数组时一定要还原
	dp(l,mid);cdq(dep+1,mid+1,r);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{//谔进制拆分
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		int bin=1;z--;
		le[i]=++cnt;//记录左端点
		w[cnt]=x;c[cnt]=y;
		bin<<=1;
		while(bin<=z)
		{
			z-=bin;w[++cnt]=x*bin;
			c[cnt]=y*bin;bin<<=1;
		}
		if(z)w[++cnt]=z*x,c[cnt]=z*y;
		ri[i]=cnt;//记录右端点
	}
	cdq(1,1,n);
	scanf("%d",&q);
	while(q--)
	{
		int x,y;scanf("%d%d",&x,&y);x++;//注意题目物品从0开始
		printf("%d\n",ans[x][y]);//直接输出答案
	}
	return 0;
}
```

---

## 作者：－｜－ (赞：8)

### 前置芝士：多重背包及其优化，单调队列，二进制拆分（巨佬请忽略）
模型：给定$N$种物品，其中第$i$种物品的体积为$V_i$,价值为$W_i$，并且有$C_i$个。有一个容积为$M$的背包，要求选择若干个物品放入背包，使得物品总体积不超过$M$的前提下，物品的价值总和最大。

直接拆分法：把每种物品看作独立的$C_i$个物品，转化为做$\sum_{i=1}^N C_i$个物品的$0/1$背包问题，时间复杂度$O(M*\sum_{i=1}^N C_i)$,效率太低，舍弃;

二进制拆分法：$O(NMlogC_i)$

​	易知从$2^0,2^1...2^{k-1}$这$k$个2的整数次幂中选出若干个相加，可以表示出0~$2^k-1$之间任意的整数。易知$C_i\geq \sum_{i=0}^{p}2^i$；然后设$R_i=C_i-\sum_{i=0}^{p}2^i$；

​	有:$2^{p+1}>R_i$,所有可以表示出0~$R_i$之间的任何整数。在$2^0,2^1...2^{p}$及$R_i$中取出若干个元素相加，可以表示出$R_i$~$R_i+2^{p+1}-1$之间的任何整数，又因为$C_i=R_i+2^{p+1}-1$，所以可以表示出$R_i$~$C_i$中的任意整数。

​	综上，我们可以把数量为$C_i$的第$i$种物品拆成$p+2$个物品，体积分别为$2^0*V_i,2^1*V_i...2^p*V_i,R_i*V_i$.

单调队列：$O(NM)$

​	忽略阶段这一维，$F[j]$表示从前$i$个物品选出若干个放入背包，体积之和为$j$时，价值之和的$max $，**倒序循环$j$**状态转移时，考虑选取第$i$个物品的个数$cnt$。

$F[j]=max_{1\leq cnt\leq C_i} $ {$F[j-cnt*V_i]+cnt*W_i$}
考虑把状态$j$按除以$V_i$的余数分组，对每一组进行计算，不同组在同一阶段互不干扰.

​	对于每个余数$0\leq u\leq V_i-1$,倒序循环$p=(m-u)/V_i$~0，对应的$j=u+p*V_i(p-C_i\leq k\leq p-1)$
$F(u+p*V_i)=max_{p-C_i\leq k\leq p-1}${ $F(u+k*V_i)+(p-k)*W_i$}=$max${$F(u+k*V_i)+k*W_i$}$+W_i*p$

操作：1.检查对头合法性，把大于$p-1$的决策点出队。

​	2.取对头为最优决策，更新$F[u+p*V_i]$。

​	3.把决策$k=p-C_i-1$插入队尾，入对时检查队尾单调性，弹出无用决策；

###  然后...我们来看题
法一:二进制拆分($O(NVlogc_i)$)

不妨把每个问题分为两部分，$d_i-1$和$d_i+1$。

定义$dp[i][j]$为从前往后拿，前i个数价格为j是最大价值。

定义$dp1[i][j]$为从后往前拿，后i个数价格为j是最大价值。

公式：$ ans=max${$dp[d_i-1][j]+dp[d_i+1][e_i-j]$}

$j$为0~$n-1$任意自然数，因为$d_i$被拿走了所以少了$d_i$。

状态转移方程：$dp[i][j]=max$($dp[i][j-b_ip]+a_i p,dp[i][j]$);

由于带有修改，所以要维护一个前缀和后缀，初始化为不取第$i$个物品。

```c++
#include<bits/stdc++.h>
#define ll long long
#define re register int
#define il inline
#define f(a,b,c) for(register int a=b;a<=c;a++)
using namespace std;
struct node{   ll x,y,z;}a[1010];
ll dp[1010][10100],dp1[1010][10100];//考试数据
// ll dp[1010][1010],dp1[1010][1010];luogu数据
ll v=10000,n,q;
il int read(){
    re x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
il void cz(){
	f(i,1,n){
		f(j,1,v)dp[i][j]=dp[i-1][j];//初始化为不选第i个物品，从前往中间转移求前缀
       register  ll reg=a[i].z,p=1;
        while(reg>=p){
            for(re j=v;j>=a[i].x*p;j--)
                dp[i][j]=max(dp[i][j],dp[i][j-a[i].x*p]+a[i].y*p);
                reg-=p;p=p<<1;
        }
        if(reg){
		for(re j=v;j>=a[i].x*reg;j--)
                dp[i][j]=max(dp[i][j],dp[i][j-a[i].x*reg]+a[i].y*reg);
        }
    }
    for(re i=n;i>=1;i--){
        for(re j=1;j<=v;j++)dp1[i][j]=dp1[i+1][j];//初始化为不选第i个物品，从后往中间转移求后缀缀
       ll reg=a[i].z,p=1;
        while(reg>=p){
            for(re j=v;j>=a[i].x*p;j--)
                dp1[i][j]=max(dp1[i][j],dp1[i][j-a[i].x*p]+a[i].y*p);
                reg-=p;p=p<<1;
        }
        if(reg){
            for(re j=v;j>=a[i].x*reg;j--)
                dp1[i][j]=max(dp1[i][j],dp1[i][j-a[i].x*reg]+a[i].y*reg);
        }
    }
}
int main()
{
//	freopen("package.in","r",stdin);
//	freopen("package.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++){
        a[i].x=read();a[i].y=read();a[i].z=read();
    }
    cz();
    q=read();
    while(q--){
        ll ans=0,c=read()+1,f=read();
        for(re i=0;i<=f;i++)
            ans=max(ans,dp[c-1][i]+dp1[c+1][f-i]);
        cout<<ans<<endl;
    }
    return 0;

}
```

法二：单调队列

q[i]存的是价格，$\frac{q[x]}{a[i]}*b[i]$求的是价值

```c++
#include<bits/stdc++.h>
#define ll long long
#define reg register int
#define il inline
#define f(a,b,c) for(register int a=b;a<=c;a++)
using namespace std;
il int read(){
    reg x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
const int N=1005;
const int M=10005;
int n,m,a[N],b[N],c[N],dp[N][M],dp1[N][M],q[M],hd,tl;
int main(){
//	freopen("package.in","r",stdin);
//	freopen("package.out","w",stdout);
	n=gi();
	f(i,1,n)a[i]=gi(),b[i]=gi(),c[i]=gi();
	f(i,1,n) f(j,0,a[i]-1)//从前往中间转移求前缀
    {
		hd=1,tl=0;
		for(re k=j;k<M;k+=a[i]){
			while(hd<=tl&&k-q[hd]>c[i]*a[i])++hd;
            //如果取的i的个数已经大于c[i],出队.
			while(hd<=tl&&dp[i-1][q[tl]]-q[tl]/a[i]*b[i]<dp[i-1][k]-k/a[i]*b[i])--tl;
            //队首至队尾,体积递增，价格递减，如果队尾的价格小于枚举到的价格，弹出；
				q[++tl]=k;
            dp[i][k]=dp[i-1][q[hd]]+(k-q[hd])/a[i]*b[i];
            //转移，用队尾更新当前状态，(k-q[hd])是差值
			}
		}
	for(re i=n;i;--i) f(j,0,a[i]-1)//从后往中间转移求后缀,以下同理
    {
		hd=1,tl=0;
		for (re k=j;k<M;k+=a[i]){
			while(hd<=tl&&k-q[hd]>c[i]*a[i])++hd;
			while(hd<=tl&&dp1[i+1][q[tl]]-q[tl]/a[i]*b[i]<dp1[i+1][k]-k/a[i]*b[i])--tl;
				q[++tl]=k;dp1[i][k]=dp1[i+1][q[hd]]+(k-q[hd])/a[i]*b[i];
			}
		}
	m=read();while(m--){
		re x=read()+1,y=read(),ans=0;
		f(i,0,y)ans=max(ans,dp[x-1][i]+dp1[x+1][y-i]);
		printf("%d\n",ans);
	}
	return 0;
}
```




---

## 作者：XiaoX (赞：6)

多重背包的练手好题。   
$45pts:$暴力将多重背包拆成$0/1$背包，每次询问跑一遍$0/1$背包
 _**Code:**_ 
 ```
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100005
using namespace std;
int cnt,n,q;
int dp[1005];
int rd()
{
    int res=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar());
    for(;isdigit(ch);ch=getchar())
        res=(res<<3)+(res<<1)+ch-'0';
    return res;0
}
struct bag{
    int a,b,id;
}eden[N];
int main()
{
    n=rd();
    for(int i=1;i<=n;i++)
    {
        int as=rd(),bs=rd(),c=rd();
        for(int j=1;j<=c;j++)
            eden[++cnt].a=as,eden[cnt].b=bs,eden[cnt].id=i-1;
    }
    q=rd();
    while(q--)
    {
        int del=rd(),m=rd();
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=cnt;i++)
        {
            if(eden[i].id!=del)
            for(int j=m;j>=eden[i].a;j--)
                dp[j]=max(dp[j],dp[j-eden[i].a]+eden[i].b);	
        }
        printf("%d\n",dp[m]);	
    }
}
```
$100pts:$
询问删去一个物品后的答案，只需预处理出$1\sim i-1$和$i+1\sim n$的答案，枚举背包容量合并即可。所以关键在于预处理部分。  
暴力枚举每个物品选的个数会$TLE$（实测$35pts$~~（我选择暴力qwq）~~）  
显然**枚举物品**和**背包容量**两维无法继续优化，我们考虑枚举**每个物品选的个数**这部分的优化。

### 重点：二进制拆分
有一个很显然的事情就是$1\sim 2^n-1$的数都可以被$2^{0\sim n-1}$中的数相加拼成。而对于超过$2^n$的物品，再用$x-2^n$（$x$为物品个数）即可拼成$x$以内的所有数。所以枚举**数量**转化为枚举**次幂**，复杂度降为$O(logc_i)$级别。

 _**Code:**_ 
 ```
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1005
#define re register 
using namespace std;
int pre[1005][1005],sub[1005][1005];
int a[N],b[N],c[N];
int q,n;
int rd()
{
	int res=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);ch=getchar())
		res=(res<<3)+(res<<1)+ch-'0';
	return res;
}
void prework()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=N-5;j++) pre[i][j]=pre[i-1][j];
        //前i个物品容量为j的答案
		int res=c[i],pw=1;
		while(res>=pw)
		{
			for(int j=N-5;j>=a[i]*pw;j--) pre[i][j]=max(pre[i][j],pre[i][j-a[i]*pw]+b[i]*pw);
			res-=pw;pw<<=1;
		}
		if(res) for(int j=N-5;j>=a[i]*res;j--) pre[i][j]=max(pre[i][j],pre[i][j-a[i]*res]+b[i]*res);
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j<=N-5;j++) sub[i][j]=sub[i+1][j];
        //i~n的物品容量为j的答案
		int res=c[i],pw=1;
		while(res>=pw)
		{
			for(int j=N-5;j>=a[i]*pw;j--) sub[i][j]=max(sub[i][j],sub[i][j-a[i]*pw]+b[i]*pw);
			res-=pw;pw<<=1;
		}
		if(res) for(int j=N-5;j>=a[i]*res;j--) sub[i][j]=max(sub[i][j],sub[i][j-a[i]*res]+b[i]*res);	
	}
}
int main()
{
	n=rd();
	for(re int i=1;i<=n;i++){
		a[i]=rd(),b[i]=rd(),c[i]=rd();
	}
	prework();
	q=rd();
	while(q--)
	{
		int del=rd()+1,m=rd();
		int ans=0;
		for(re int cut=0;cut<=m;cut++) 
			ans=max(ans,pre[del-1][cut]+sub[del+1][m-cut]);
        //枚举前后各分多少合并
		printf("%d\n",ans);
	}
}
```

---

## 作者：tcl_tcl_tcl (赞：5)

# 1.分析

这道题上面的大佬已经说的十分清楚了，不再赘述为什么要正向与逆向同时遍历所有物品，这篇题解的目的在于一段与平常思维不同的代码(只知套模板的同学~~比如我~~可能会掉进坑中),熟悉01背包问题的同学可能会发现，代码中存在这样的一段

```cpp
for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 1000; j++)
			f1[i][j] = f1[i - 1][j];	
		for (int j = 1000; j >= w[i].s; j--) {
			f1[i][j] = max(f1[i][j], f1[i - 1][j - w[i].s] + v[i].s);
		}

	}
```
此处引用自@lqshr大佬的题解。

中间的

```cpp
		for (int j = 0; j <= 1000; j++)
			f1[i][j] = f1[i - 1][j];	
```

这一段代码看起来无用，但实际上对于本题的解题思路而言，是不可或缺的。
由于

         
   $ans = max(ans, f1[l][j] + f2[r + 1][V - j])$

用到的不是$f1[n][V]$和$f2[n][V]$，而是$f1[n][v]$和$f2[n][v],v<V$。平常之所以可以不用去更新,直接将下界写为$j>=w[i]$,是因为我们需要的结果仅仅是$f[n][V]$。因此对于此题而言,在对背包容量的遍历过程中，即使$j < w[i].s$,同样需要更新dp数组的值，另一种常数较小的写法：
```cpp
for(int i=1;i<=cnt;i++){
        for(int j=1000;j>=0;j--){
            if(j>=p[i])f[i][j]=max(f[i-1][j],f[i-1][j-p[i]]+v[i]);
            else f[i][j]=f[i-1][j];
        }
    }
    for(int i=cnt;i>=1;i--){
        for(int j=1000;j>=0;j--){
            if(j>=p[i])g[i][j]=max(g[i+1][j],g[i+1][j-p[i]]+v[i]);
            else g[i][j]=g[i+1][j];
        }
    }
```

# 2.代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 1E5;
int a, b, c, e, d, n, q;
//a表示买一个玩偶的价钱，b表示获得的价值，c表示限购次数
//d表示去掉的玩偶编号，e表示总价钱
int f1[100007][1007], f2[100007][1007];
struct node {
	int id;
	int cost;
	int value;
};
vector<node> arr;
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	arr.push_back(node{ 0,0,0 });	//这项蜜汁操作是为了编号从1开始
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b >> c;
		int bit = 1;
		while (bit <= c) {
			arr.push_back(node{ i,bit*a,bit*b });
			c -= bit; bit <<= 1;
		}
		if (c) {
			arr.push_back(node{ i,c*a,c*b });
		}
	}
	for (int i = 1; i <= arr.size() - 1; i++)
	{
		for (int j = 1000; j >= 0; j--)
		{
			if (j >= arr[i].cost)
				f1[i][j] = max(f1[i - 1][j], f1[i - 1][j - arr[i].cost] + arr[i].value);
			else
				f1[i][j] = f1[i - 1][j];
		}
	}
	for (int i = arr.size() - 1; i >= 1; i--)
	{
		for (int j = 1000; j >= 0; j--)
		{
			if (j >= arr[i].cost)
				f2[i][j] = max(f2[i + 1][j], f2[i + 1][j - arr[i].cost] + arr[i].value);
			else
				f2[i][j] = f2[i + 1][j];
		}
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> d >> e;
		d++;
		int ans = 0;
		int l = 0, r = 0;
		while (arr[l + 1].id < d&&l < arr.size() - 1) l++;	
		r = arr.size() - 1;
		while (arr[r].id > d && r >0) r--;
		for (int j = 0; j <= e; j++)
			ans = max(ans, f1[l][j] + f2[r + 1][e - j]);
		cout << ans << endl;
	}
	return 0;
}
```
数组一定要开大一点，十个RE的教训。


完结。

---

## 作者：MloVtry (赞：3)

dp。

空一个玩具不选那就空开它呗。

f[i][]表示用1~i号玩具更新的背包值，p[i][]表示用i~n号玩具更新的背包值，询问的时候在做一边背包就好。

代码
```cpp
#include<bits/stdc++.h>
#define N 1010
using namespace std;
int f[N][N],p[N][N],q,ans;
int a[N],b[N],c[N],n,d,e;
void MloVtry()
{
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<=1000;++j) f[i][j]=f[i-1][j];
	
		int it=c[i],nu=1;
		while(nu<=it)
		{
			for(int j=1000;j>=nu*a[i];--j) f[i][j]=max(f[i][j],f[i][j-a[i]*nu]+b[i]*nu);
			it-=nu;nu*=2;
		}
		if(it) for(int j=1000;j>=it*a[i];--j) f[i][j]=max(f[i][j],f[i][j-a[i]*it]+b[i]*it);
	}
	
	for(int i=n;i;--i)
	{
		for(int j=0;j<=1000;++j) p[i][j]=p[i+1][j];
	
		int it=c[i],nu=1;
		while(nu<=it)
		{
			for(int j=1000;j>=nu*a[i];--j) p[i][j]=max(p[i][j],p[i][j-a[i]*nu]+b[i]*nu);
			it-=nu;nu*=2;
		}
		if(it) for(int j=1000;j>=it*a[i];--j) p[i][j]=max(p[i][j],p[i][j-a[i]*it]+b[i]*it);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d%d",&a[i],&b[i],&c[i]);
	MloVtry();
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d",&d,&e);ans=0;
		for(int i=0;i<=e;++i) ans=max(ans,f[d][i]+p[d+2][e-i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

