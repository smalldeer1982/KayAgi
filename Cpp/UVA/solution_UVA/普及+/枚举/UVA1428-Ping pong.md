# Ping pong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4174

[PDF](https://uva.onlinejudge.org/external/14/p1428.pdf)

# 题解

## 作者：x_angelkawaii_x (赞：12)

[原题传送门](http://poj.org/problem?id=3928)

题面
>Description
N(3<=N<=20000) ping pong players live along a west-east street(consider the street as a line segment). Each player has a unique skill rank. To improve their skill rank, they often compete with each other. If two players want to compete, they must choose a referee among other ping pong players and hold the game in the referee's house. For some reason, the contestants can't choose a referee whose skill rank is higher or lower than both of theirs. The contestants have to walk to the referee's house, and because they are lazy, they want to make their total walking distance no more than the distance between their houses. Of course all players live in different houses and the position of their houses are all different. If the referee or any of the two contestants is different, we call two games different. Now is the problem: how many different games can be held in this ping pong street?

大致题意:
给定n个互异整数$a[1]-a[n] $,求

$$\sum_{i=1}^n\sum_{j=i+1}^n\sum_{k=j+1}^n a[j]∈[min(a[i],a[k]),max(a[i],a[k])]$$
(n<=20000)
## 算法一:
考虑暴力，枚举$i,j,k$ 判断是否可行，时间复杂度 $O(n^{3})$，显然是过不去的
## 算法二
设4个数组l_up[i],l_low[i],r_up[i],r_low[i]，表示i位置左侧大于a[i]，小于a[i]，右侧大于a[i]，小于a[i]的数的个数

考虑枚举裁判位置，这时每个裁判i对于答案的贡献为`l_up[i]*r_low[i]+l_low[i]*r_up[i]`

建立权值树状数组从左往右扫描，每次查询比a[i]小的数的个数即query(a[i]-1)，由于元素互异，所以i=l_up[i]+l_low[i]+1，大于a[i]的数的个数可以$O(1)$求出，在求出该点信息后让树状数组中a[i]的权值+1，再从右往左扫一遍就可以得到答案

注意相乘时会爆int，要强制转long long

由于这种水题做起来没有味道，所以我们多考虑一些↓

### 拓展
如果将题目中"整数互异"的条件去除，那么上面的思路就会出现问题

举个例子
> 输入:1 1 1 1 1

首先注意到题目中a[j]的范围在a[i],a[k]闭区间内，所以将四个数组的含义加上等于

`l_up[1]=0,l_up[2]=1,l_up[3]=2,l_up[4]=3,l_up[5]=4

r_low[1]=4,r_low[2]=3,r_low[3]=2,r_low[4]=1,r_low[5]=0`

l_low与l_up完全相同,r_low和r_up完全相同，所以最后答案为
$$(0*4+1*3+2*2+3*1+4*0)*2=20 $$

显然是不正确的，至于为什么，你可以想到a[1],a[2],a[3]既可以存在于a[2]左low右up中，也可以存在于a[2]左up右low中，所以每个答案被重复计算了两次

解决方法:算出每个点i左侧与a[i]相等的点的个数l[i]，右侧点i右侧与a[i]相等的点的个数r[i]，将每个点的答案减去l[i]*r[i]即可

正常版本AC代码
``` cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
int a[20010];
int tree[100010];
inline int lowbit(int x){return x&(-x);}
void update(int x,int k)
{
    while(x<=100000)
    {
        tree[x]+=k;
        x+=lowbit(x);
    }
}
int query(int x)
{
    int sum=0;
    while(x!=0)
    {
        sum+=tree[x];
        x-=lowbit(x);
    }
    return sum;
}
int l_low[20010],l_up[20010],r_low[20010],r_up[20010];
int main()
{
    int T;
    scanf("%d",&T);
    for(int _=1;_<=T;++_)
    {
        long long ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        for(int i=1;i<=n;++i)
        {
            l_low[i]=query(a[i]);
            l_up[i]=query(100000)-query(a[i]-1);
            update(a[i],1);
        }
        for(int i=1;i<=100000;++i)tree[i]=0;
        for(int i=n;i>=1;--i)
        {
            r_low[i]=query(a[i]);
            r_up[i]=query(100000)-query(a[i]-1);
            update(a[i],1);
            ans+=(long long)r_low[i]*(long long)l_up[i];
            ans+=(long long)l_low[i]*(long long)r_up[i];
        }		
        for(int i=1;i<=100000;++i)tree[i]=0;
        printf("%lld\n",ans);
    }
}
```

---

## 作者：Poncirus (赞：4)

接下来，为了方便，我们称位置在左边的选手为 $a$，右边的选手为 $b$，裁判为 $c$。

提一提题目里的 trick：$c$ 的技能值在 $a,b$ 之间，既可以指 $a<b<c$，也可以指 $a>b>c$。

***

### Solution

这里讲一下两种不同的思路：顺推和枚举裁判。

1. 顺推

   整个过程大概如下：

   * 找所有 $a<b<c$ ：

     * 枚举每个 $b$，记录满足其要求的 $a$ 的个数为 $f_b$。（ 1-1 ）
     * 枚举每个 $c$，此时 $ans$ 加上所有满足条件的 $f_b$。（ 1-2 ）

   * 找所有 $a>b>c$ ：

     2-1，2-2 步操作与上述 1-1 与 1-2 步同理。

   看看 1-1 和 2-1 步，我们如何求得对于每个 $b$ 满足 $a<b$ 或 $a>b$ 的 $a$ 的个数？

   不由得联想到了用树状数组求 [顺序对](https://www.luogu.com.cn/problem/P1428) 和 [逆序对](https://www.luogu.com.cn/problem/P1908)。

   1-1 步不就是要求以 $b$ 结尾的顺序对数量吗？2-1 不就是求结尾为 $b$ 的逆序对个数吗？

   这一步不懂的同学可以到上面给的两个题目中查看对应题解。这里不再赘述。

   然后将两个值保存在 $f_b$ 中备用。

   接着，我们枚举 $c$，有了上面的经验，很容易想到求以 $c$ 结尾的顺 / 逆序对。

   但此时 $ans$ 需要累加的不是顺 / 逆序对数量，而是对应的 $f_b$。

   这还不好办吗？求数量时，我们使用 `Update(a[i],1)` 增加当前数所带来的贡献：$1$ 个顺 / 逆序对；那么此时当前数带来的贡献不是 $1$，而是 $f_b$，所以我们 `Update(a[i,f[b]])` 即可。

   最后，把累加了对于所有 $c$，满足条件的 $f_b$ 的和的 $ans$ 作为答案即可。

2. 枚举裁判

   这是这道题下的大多数题解使用的方法，我们也讲一讲。

   过程大致如下：

   * 找所有 $a<b,a>b$。
   * 找所有 $c>b,c<b$。

   对于每个 $b$：

   * 称满足 $a<b$ 的 $a$ 的数量为 $SE_b$。（即以 $b$ 结尾的顺序对数量）
   * 称满足 $c>b$ 的 $c$ 的数量为 $SB_b$。（即以 $b$ 开头的顺序对数量）
   * 称满足 $a>b$ 的 $a$ 的数量为 $NE_b$。（即以 $b$ 结尾的逆序对数量）
   * 称满足 $c<b$ 的 $c$ 的数量为 $NB_b$。（即以 $b$ 开头的逆序对数量）

   通过之前求顺 / 逆序对的方法可以方便的求出 $SE_b$ 和 $NE_b$。

   那么 $SB_b$ 和 $NB_b$ 只需要反过来跑一次就行惹。

   根据乘法原理，最后的总方案数 $ans$ 就是可选 $a$ 的数量与可选 $c$ 的数量的乘积，即 $SE_b\times SB_b+NE_b\times NB_b$。

### Gossip

交到校内 OJ 上，发现 WA 了。一看，原来校内 OJ 的数据里可以有重复技能值。。。

对于每个 $b$，把所有重复计算的 $a\times c$ 减去即可。$(a=b=c)$

即记录 $b$ 左边 $a=b$ 的数量与 $b$ 右边 $c=b$ 的数量，$ans$ 累加 $b$ 即减去其乘积即可。

### Code

均加了重复技能值判断。

已删去不必要成分，在易错点打了标记，请放心食用\~

##### 方法一 顺推

```cpp
#define int long long	//Warning
int a[maxn];
int f[maxn][2];
int T,n,ans,mx;
int Bit[maxn][2],Same[maxn][2],Lst[maxn][2];
inline void Update1(int k,int x){
    for(int i=k;i<=mx;i+=Lowbit(i))	//Warning: 是 mx 而不是 n，因为没有离散化
        Bit[i][0]+=x; 
    return; 
}
inline void Update2(int k,int x){
    for(int i=k;i<=mx;i+=Lowbit(i))	//Warning
        Bit[i][1]+=x; 
    return; 
}
inline int Sum1(int k){
    int ans=0;
    for(int i=k;i;i-=Lowbit(i))
        ans+=Bit[i][0];
    return ans;
}
inline int Sum2(int k){
    int ans=0;
    for(int i=k;i;i-=Lowbit(i))
        ans+=Bit[i][1];
    return ans;
}
inline void init(void){
    mx=ans=0;
    memset(Lst,0,sizeof(Lst));
    memset(Bit,0,sizeof(Bit));
    return;
}
signed main(){
    Same[0][0]=Same[0][1]=-1;	//Warning
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        init();
        for(int i=1;i<=n;++i){
            scanf("%lld",&a[i]);
            mx=max(mx,a[i]);
            Same[i][0]=Same[Lst[a[i]][0]][0]+1;
    		//Same[b][0] 记录 b 左边有多少个相同的 a
            Lst[a[i]][0]=i;
    		//Lst[x][0] 记录 x 这个值从左往右最后一次出现的下标
        }
        for(int i=n;i;--i){
            Same[i][1]=Same[Lst[a[i]][1]][1]+1;
    		//Same[b][0] 记录 b 右边有多少个相同的 c
            Lst[a[i]][1]=i;
    		//Lst[x][0] 记录 x 这个值从右往左最后一次出现的下标
        }
        //正着推
        for(int i=1;i<=n;++i){
            //记录 b=a[i] 时 a 的数量
            f[i][0]=Sum1(a[i]);
            Update1(a[i],1);
            //记录 c=a[i] 时 b 的数量
            ans+=(f[i][1]=Sum2(a[i]));
            //更新 b=a[i] 时对后面 c 的贡献 f[i][0]
            Update2(a[i],f[i][0]);
        }
        //反着推
        memset(Bit,0,sizeof(Bit));	//Warning
        for(int i=n;i;--i){
            //同理
            f[i][0]=Sum1(a[i]);
            Update1(a[i],1);
            ans+=(f[i][1]=Sum2(a[i]));
            Update2(a[i],f[i][0]);
            ans-=Same[i][0]*Same[i][1];	//Warning: 只用减一次
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

##### 方法二 枚举 $b$

```cpp
#define int long long	//Warning
int a[maxn];
int n,ans,mx,T;
int SB[maxn],SE[maxn],NB[maxn],NE[maxn];	//意义同之前定义
int Bit[maxn][2],Same[maxn][2],Lst[maxn][2];
inline void Update1(int k,int x){
	for(int i=k;i<=mx;i+=Lowbit(i))	//Warning
		Bit[i][0]+=x; 
	return; 
}
inline void Update2(int k,int x){
	for(int i=k;i<=mx;i+=Lowbit(i))	//Warning
		Bit[i][1]+=x; 
	return; 
}
inline int Sum1(int k){
	int ans=0;
	for(int i=k;i;i-=Lowbit(i))
		ans+=Bit[i][0];
	return ans;
}
inline int Sum2(int k){
	int ans=0;
	for(int i=k;i;i-=Lowbit(i))
		ans+=Bit[i][1];
	return ans;
}
inline void init(void){
    mx=ans=0;
    memset(Lst,0,sizeof(Lst));
    memset(Bit,0,sizeof(Bit));
    return;
}
signed main(){
    Same[0][0]=Same[0][1]=-1;	//Warning
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=n;++i){
            read(a[i]);
            mx=max(mx,a[i]);
            Same[i][0]=Same[Lst[a[i]][0]][0]+1;
            Lst[a[i]][0]=i;
        }
        for(int i=n;i;--i){
            Same[i][1]=Same[Lst[a[i]][1]][1]+1;
            Lst[a[i]][1]=i;
        }
        for(int i=1;i<=n;++i){
            SE[i]=Sum1(a[i]);
            NE[i]=i-1-Sum1(a[i]-1);
            Update1(a[i],1);
            //同步计算, 此时计算顺序为 n~1
            NB[n-i+1]=Sum2(a[n-i+1]);
            SB[n-i+1]=i-1-Sum2(a[n-i+1]-1);
            Update2(a[n-i+1],1);
        }
        for(int i=1;i<=n;++i)
            ans+=SE[i]*SB[i]+NE[i]*NB[i]-Same[i][0]*Same[i][1];
        printf("%lld\n",ans);
    }
	return 0;
}
```

**end.**



---

## 作者：StormWhip (赞：1)

### 思路
枚举每一位可能的裁判，用平衡树求出在其左边比它小的数的个数和在其右边比它大的数的个数，同理再求出在其左边比它大的数的个数和在其右边比它小的数的个数。运用乘法原理和加法原理统计答案即可。  

### 代码
平衡树使用 pb_ds 实现。
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int N=2e4+5;
int T,n,a[N],ans;
tree <pair<int,int>,null_type,less<pair<int,int> >,rb_tree_tag,tree_order_statistics_node_update> t1,t2;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		ans=0;
		t1.clear();t2.clear();
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		t1.insert(make_pair(a[1],1));
		for(int i=3;i<=n;i++) t2.insert(make_pair(a[i],i));
		for(int i=2;i<n;i++)
		{
			ans+=t1.order_of_key(make_pair(a[i],0))*(t2.size()-t2.order_of_key(make_pair(a[i],n)));
			ans+=(t1.size()-t1.order_of_key(make_pair(a[i],n)))*t2.order_of_key(make_pair(a[i],0));
			t1.insert(make_pair(a[i],i));
			t2.erase(make_pair(a[i+1],i+1));
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：InfiniteRobin (赞：1)

## 简要题意
有 $n$ 个人，每个人都有一个独一无二的技能值 $a_{i}$，要找出三个人，分别是第 $i,j,k$ 三人，使 $i<j<k$，并且 $a_{i}<a_{j}<a_{k}$，或 $a_{i}>a_{j}>a_{k}$。求一共能找出的组数。**本题多测**。
## 思路  
假设当前位于中间的人是 $j$，设在 $j$ 左边且比技能值小的有 $x$ 个人，在 $j$ 右边且比 $j$ 技能值小的有 $y$ 个人。那么，在 $j$ 左边且比技能值**大**的有 $j-1-x$ 个人，在 $j$ 右边且比 $j$ 技能值**大**的有 $n-j-y$ 个人。可以得到能组成的组数为   
$$y(j-1-x)+ x(n-j-y)。$$  
那么只要用树状数组，正反各跑一遍，分别求出 $x$ 和 $y$ 的值，存储在数组中即可。  
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; //相乘会爆 int

const int N=200005;
ll a[N],x[N],y[N]; //a 是树状数组，x y 见前文
ll loc[N]; //位置
int n;
long long ans=0;

int lowbit(int x){
    return x&(-x);
}
void add(int k,int x){
    while(k<=N-2){
        a[k]+=x;
        k+=lowbit(k);
    }
    return;
}
int sum(int k){
    long long p=0;
    while(k>0){
        p+=a[k];
        k-=lowbit(k);
    }
    return p;
}

//以上是模板

int main(){
    int t;
    cin>>t; //多测 
    while(t--){
        ans=0;
        memset(a,0,sizeof(a));
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>loc[i];
        }
      //正着跑求出 x[i]
        for(int i=1;i<=n;i++){
            add(loc[i],1);
            x[i]=sum(loc[i]-1);
        }
      //倒着跑求出 y[i]
        memset(a,0,sizeof(a));
        for(int i=n;i>=1;i--){
            add(loc[i],1);
            y[i]=sum(loc[i]-1);
        }
    
    	//相乘后加到答案里
        for(int i=1;i<=n;i++){
            ans+=(x[i]*(n-i-y[i]));
            ans+=(y[i]*(i-1-x[i]));
        }
        cout<<ans<<endl;
        
    }
    return 0;
}
```

------------

### THE END

---

## 作者：happyZYM (赞：1)

$\color{white} \text{第一次写树状数组，写篇题解纪念一下}$

令$x_i$表示从$a_1$到$a_{i-1}$中比$a_i$小的数的个数，$y_i$表示从$a_{i+1}$到$a_n$中比$a_i$小的数的个数，则答案等于
$\sum_{k=1}^N x[i]*(n-i-y[i])+(i-x[i]-1)*y[i] $

可以用树状数组动态维护。

贴代码：
```cpp
#include<cstdio>
#include<cstring>
const int maxn=100005;
int T,n,r;
int a[maxn],b[maxn];
int lowbit(int x) { return x&-x; }
inline int sum(int x)
{
	int res=0;
	while(x>0)
	{
		res=res+b[x];
		x-=lowbit(x);
	}
	return res;
}
inline void add(int x,int d)
{
	a[x]=a[x]+d;
	while(x<=r)
	{
		b[x]=b[x]+d;
		x+=lowbit(x);
	}
}
inline void set(int x,int d) { add(x,d-a[x]); }
int v[maxn],x[maxn],y[maxn];
long long res;
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	scanf("%d",&T);
	while(T-->0)
	{
		scanf("%d",&n);
		r=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&v[i]);
			if(v[i]>r) r=v[i];
		}
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)
		{
			set(v[i],1);
			x[i]=sum(v[i]-1);
		}
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=n;i>=1;i--)
		{
			set(v[i],1);
			y[i]=sum(v[i]-1);
		}
		res=0;
		for(int i=2;i<=n-1;i++) res=res//小心溢出！
									+(long long)x[i]*(n-i-y[i])
									+(long long)(i-x[i]-1)*y[i];
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：Ferdina_zcjb (赞：0)

题意很简单，在此不再赘述。

# NO.1 暴力解法

$$\sum_{i=1}^n \ \sum_{j=i+1}^n \ \sum_{k = j+1}^n ans+1(a_i < a_j < a_k \ \cup \ a_i>a_j>a_k)$$

显然，$O(n^3)$ 的时间复杂度是过不了的。

那我们就需要用到一个强大的数据结构——线段树（~~树状数组也行~~）。

# NO.2 线段树解法

首先，我们很容易发现：

1. 当第 $i$ 位前有 $k$ 个比 $a_i$ 大的数，故第 $i$ 位前有 $i-1-k$ 个比 $a_i$ 小的数。
2. 当第 $i$ 位后有 $k$ 个比 $a_i$ 大的数，故第 $i$ 位后有 $n-i-k$ 个比 $a_i$ 小的数。
3. 若已知，第 $i$ 位前有 $k$ 个比 $a_i$ 小的数，第 $i$ 位后有 $j$ 个比 $a_i$ 大的数，则以 $i$ 位裁判的情况共有 $k\times j + (i-1-k)\times (n-i-j)$ 种（必须保证数列中无重复元素）。

好了，发现这些后就简单了，只需要用线段树不断存入 $a_i$ 在查询，用 $b_i$ 记录第 $i$ 位后比 $a_i$ 大的数的个数，用 $s_i$ 记录第 $i$ 位前比 $a_i$ 小的数的个数即可。

Q：如何运用线段树构造数组 $b$ 与 $s$？

A：非常简单，将 $a$ 从头到尾遍历一遍，将 $a_i$ 存入线段树中的同时查询 $1 \sim a_i-1$ 的和，这样就构造了 $s$。再清空线段树，将 $a$ 从尾到头遍历一遍，将 $a_i$ 存入线段树的同时查询 $a_i+1 \sim n$ 的和就构造了 $b$（以上“存入”即单点修改 $a_i$，修改方式为 $+1$）。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[300010],maxx,b[300010],s[300010],num;
struct TREE{
	int l,r,sum;
}tree[300010 << 2];
void build(int k,int L,int R){//建树以及清空。
	tree[k].l = L;
	tree[k].r = R;
	tree[k].sum = 0;
	if(L == R)return ;
	int mid = (L+R)>>1;
	build(k<<1,L,mid);
	build(k<<1|1,mid+1,R);
}
void ask(int k,int L,int R){//区间询问和。
	if(L > tree[k].r || R < tree[k].l)return ;
	if(L <= tree[k].l && R >= tree[k].r){
		num += tree[k].sum;
		return ;
	}
	ask(k<<1,L,R);
	ask(k<<1|1,L,R);
}
void change(int k,int d){//单点修改。
	if(d > tree[k].r || d < tree[k].l)return ;
	else tree[k].sum += 1;
	if(tree[k].l == tree[k].r)return ;
	change(k<<1,d);
	change(k<<1|1,d);
}
signed main(){
    int T;
    cin >> T;
    while(T--){
	    cin >> n;
	    for(int i = 1;i <= n;++i){
		    cin >> a[i];
		    maxx = max(a[i],maxx);//为线段树区间的上限。
	    }
	    build(1,1,maxx);
	    for(int i = 1;i <= n;++i){//构造s。
		    if(a[i]!=1)num = 0,ask(1,1,a[i]-1),s[i] = num;
		    change(1,a[i]);
	    }
	    build(1,1,maxx);
	    for(int i = n;i >= 1;--i){//构造b。
		    if(a[i]!=maxx)num = 0,ask(1,a[i]+1,maxx),b[i] = num;
		    change(1,a[i]);
	    }
	    int ans = 0;
	    for(int i = 1;i <= n;++i){//排列组合计算。
		    ans += b[i]*s[i];
		    ans += (i-1-s[i])*(n-i-b[i]);
	    }
	    cout << ans<<endl;
	    memset(b,0,sizeof(b));
	    memset(s,0,sizeof(s));
    }
}
```


---

## 作者：loser_seele (赞：0)

虽然总体思路和别的题解一样，但是使用了全新的做法。

当第 $ i $ 个人当裁判时，左边有 $ c_i $ 个人比 $ a_i $ 大，则就有 $ i-1-c_i $ 人比 $ a_i $ 小。

用一样的方法算出右边比它大，小的数的数量，分别为 $ d_i,n-i-d_i $。

最后答案为 $ c_i \times (n-i-d_i) + d_i \times (n-i-c_i) $。

现在只要考虑 $ c_i $ 的求法，$ d_i $ 用相同的办法就可以算出（枚举顺序变为倒序）。

$ c_i $ 可以通过一次循环遍历求出，具体地，开一个数组 $ pre $，对于每个 $ i $ 令 $ pre_{a_i}=1 $，则答案为 $ \sum\limits_{i=1}^{a_i-1} pre_i $。

这是一个支持单点修改，区间查询的数据结构，虽然可以用树状数组，但是在这里魔改成了 LCT ,使用更加方便。

具体地，对值域内所有点连边，然后每次修改和查询套用 LCT 基本的区间操作即可。

总时间复杂度 $ \mathcal{O}(Tn \log{n}) $，LCT 本身的常数过大，但是时限足够，可以通过。注意每次都要清空所有信息和重新连边。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//保险
const int maxn=2e5+10;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int c[2000020],tag[2000020],n;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]]);
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]]);
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]]),val[ch[x][0]]=(val[ch[x][0]]*mul[x]),sum[ch[x][0]]=(sum[ch[x][0]]*mul[x]),add[ch[x][0]]=(add[ch[x][0]]*mul[x]);
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]]),val[ch[x][1]]=(val[ch[x][1]]*mul[x]),sum[ch[x][1]]=(sum[ch[x][1]]*mul[x]),add[ch[x][1]]=(add[ch[x][1]]*mul[x]);
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x]),val[ch[x][0]]=(val[ch[x][0]]+add[x]),sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]]);
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x]),val[ch[x][1]]=(val[ch[x][1]]+add[x]),sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]]);
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }//前面都是LCT板子部分
    void added(int u,int c)
    {
        int v=u;
        makeroot(u), access(v), splay(v);
      val[u] = (val[v] + c) ;
      sum[v] = (sum[v] + siz[v] * c ) ;
      add[v] = (add[v] + c) ;
        return;
    }//单点加（相当于对区间[u,u]加）
    int query(int u)
    {
        if(u==0)
            return 0;
        int v=1;
        makeroot(u), access(v), splay(v);
        return sum[v];
    }//区间查询（注意特判u=0的情况，在转化前缀和时1-1=0会出问题）
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
}st;
int c1[maxn],d1[maxn],c2[maxn],d2[maxn],a[maxn];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			a[i]=read();
		for(int i=1;i<=maxn/2;i++)
        st.clear(i),st.val[i]=0,st.maintain(i),st.splay(i);
        for(int i=0;i<=100000;++i)
		st.sum[i]=0;
		for(int i=1;i<100000;i++)
			st.link(i,i+1);
		int ans=0;
		 for(int i=1;i<=n;++i)
		 {
			 c1[i]=st.query(a[i]);
			 //c2[i]=st.query(100000)-st.query(a[i]-1);
             st.added(a[i],1);
		 }
		for(int i=1;i<=maxn/2;i++)
        st.clear(i),st.val[i]=0,st.splay(i),st.maintain(i);
        for(int i=0;i<=100000;++i)
		st.sum[i]=0;
		for(int i=1;i<100000;i++)
		st.link(i,i+1);
		for(int i=n;i>=1;--i)
        {
            d1[i]=st.query(a[i]);
            //d2[i]=st.query(100000)-st.query(a[i]-1);
			//cout<<st.query(a[i])<<'\n';
            st.added(a[i],1);
		}
		for(int i=1;i<=n;i++)
		{
			//cout<<ans<<'\n';
			//cout<<st.query(a[i])<<'\n';
            ans+=c1[i]*(n-i-d1[i]);
            ans+=d1[i]*(i-1-c1[i]);
			//cout<<c1[i]<<' '<<c2[i]<<' '<<d1[i]<<' '<<d2[i]<<'\n';
			//cout<<ans<<'\n';
        }
		for(int i=0;i<=100000;++i)
		st.sum[i]=0;
		cout<<ans<<'\n';
	}
}
```


---

## 作者：dbg_8 (赞：0)

~~虽然用的都是树状数组, 但我的方法似乎和其他题解有点不太一样(~~

简化题意, 将题目转化为这个问题:

给定一个数列 $s$, 求在$s$中有多少组数$(a,b,c)$满足$a<b<c$且$s_a<s_b<s_c$或$s_a>s_b>s_c$

对$s_a<s_b<s_c$和$s_a>s_b>s_c$的情况分别讨论.

可以发现, 解决有多少组数$(a,b,c)$满足$s_a>s_b>s_c$这个问题只要把$s$顺序颠倒过来再算满足$s_a<s_b<s_c$的数量就可以了.

而算$s_a<s_b<s_c$的数量, 可以先算满足$a<b$且$s_a<s_b$的数量, 再算满足$b<c$且$s_b<s_c$的数量(程序实践的时候可以在一起计算).这需要用到树状数组, 具体的说明可以参考[这道题](https://www.luogu.com.cn/problem/P1908)的题解, 这里不再赘述.

有一个地方需要注意, 就是 rank 这个名字在 C++ 的某个头文件里被用过, 但洛谷的编译器是不会触发 CE 的, 而在 UVA 中会 CE.

下面贴上代码.

```cpp
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#define ll long long
#define lowbit(x) x & (-x)
using namespace std;
struct NODE {
	int val, id;
} a[20003], b[20003];
inline bool cmp (const NODE &x, const NODE &y) {
	return x.val == y.val ? x.id > y.id : x.val < y.val;
}
int n, ranks[20003], score[20003], c[20003], d[20003];
inline int query(int x, int *c) {
	int ans = 0;
	while (x)
		ans += c[x], x -= lowbit(x);
	return ans;
}
inline void add (int x, int y, int *c) {
	while (x <= n)
		c[x] += y, x += lowbit(x);
	return;
}
inline ll sovle() {
	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	memset(score, 0, sizeof(score)); 
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ranks[b[i].id] = i;		// 第 i 个数的排名 
	for (int i = 1; i <= n; i++) {		// 注意 for 里面用的都是 ranks[i] 
		// 计算 a < b 且 s[a] < s[b] 的情况 
		score[ranks[i]] = query(ranks[i] - 1, c);
		add(ranks[i], 1, c);
		// 计算 b < c 且 s[b] < s[c] 的情况 
		ans += query(ranks[i] - 1, d);
		add(ranks[i], score[ranks[i]], d);
	}
	return ans;
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i].val), a[i].id = i;
		sort(a + 1, a + n + 1, cmp);
		ll ans = 0;
		for (int i = 1; i <= n; i++)
			b[i] = a[i];
		ans += sovle();
		for (int i = 1; i <= n; i++)
			b[i] = a[n - i + 1];
		ans += sovle();		// 反过来再算 
		printf("%lld\n", ans);
	}
	return 0;
}
```

~~语文不好, 表述的可能不是很清楚.~~

---

## 作者：EuphoricStar (赞：0)

## 思路

考虑第 $i$ 个人当裁判的情形。

假设 $a_1$ 到 $a_{i-1}$ 中有 $c_i$ 个比 $a_i$ 小，

那么就有 $i - 1 - c_i$ 个比 $a_i$ 大；

同理，假设 $a_{i+1}$ 到 $a_n$ 中有 $d_i$ 个比 $a_i$ 小，

那么就有 $n - i - d_i$ 个比 $a_i$ 大。

根据乘法原理和加法原理，$i$ 当裁判有 $c_i \times (n - i - d_i) + d_i \times (i - 1 - c_i)$ 种比赛。

这样，问题就转化为求 $c_i$ 和 $d_i$。

------------

$c_i$ 可以这样计算：

从左到右扫描所有的 $a_i$，令 $x\,[\,j\,]$ 表示目前为止已经考虑过的所有的 $a_i$ 中，是否存在一个 $a_i = j$。

$x\,[\,j\,] = 0$ 表示不存在，$x\,[\,j\,] = 1$ 表示存在。

则 $c_i$ 就是前缀和 $x\,[\,1\,] + x\,[\,2\,] + ... + x\,[\,a_i - 1\,]$。

初始时所有 $x\,[\,i\,]$ 等于 $0$，在计算 $c_i$ 时，需要先设 $x\,[\,a_i\,] = 1$，然后求前缀和。

我们需要动态地修改单个元素并求前缀和，因此我们可以使用树状数组。

这样，就可以以 $O(n\ log\ \max{a_i})$ 的时间复杂度计算出所有的 $c_i$。

类似地，可以计算出 $d_i$（从右到左扫描即可），然后以 $O(n)$ 的时间复杂度累加得出最后的答案。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef long long ll;

ll n, c[100050], t, a[20050], cs[20050], ds[20050], ans, maxa;

int lowbit(int x) {
    return x & (-x);
}

int sum(int x) {
    int res = 0;
    while (x > 0) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

void add(int x, int d) {
    while (x <= maxa) {
        c[x] += d;
        x += lowbit(x);
    }
}

int main() {
    scanf("%lld", &t);
    while (t--) {
        memset(c, 0, sizeof(c));
        scanf("%lld", &n);
        maxa = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            maxa = max(maxa, a[i]);
        }
        for (int i = 1; i <= n; ++i) {
            add(a[i], 1);
            cs[i] = sum(a[i] - 1);
        }
        memset(c, 0, sizeof(c));
        for (int i = n; i > 0; --i) {
            add(a[i], 1);
            ds[i] = sum(a[i] - 1);
        }
        ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += cs[i] * (n - i - ds[i]);
            ans += ds[i] * (i - 1 - cs[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```


---

## 作者：Ouaoan (赞：0)

题目：Ping pong


---

[更好阅读体验？](https://blog.csdn.net/rabbit_ZAR/article/details/78769686)

---


思路：

树状数组。

设a[i]是一个人i的数值。

根据乘法原理可以看出，对于每一个人i而言，

以他为裁判一共可以举行的比赛场数 = 在他左边数值比他小的(c[i]) * 在他右边数值比他大的(n-i-d[i]) + 在他左边数值比他大的 (i-1-c[i]) *在他右边数值比他小的 (d[i]) 。

此时，要求c[i]和d[i]，就可以用树状数组。

对于每一个裁判i，先设f[j]=1为i左边有一个人的数值为j，c[i] 就等于 f[1] ~ f[i-1]的值。因为有多个裁判，所以f的值是不定的，所以可以将f构造成树状数组求解了。

同理可以求出d。

---- 

代码:

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <cstring>
#include <map>
using namespace std;
 
int n;
int a[20005]={0};
 
int c[20005]={0};
int d[20005]={0};
 
int f[100005]={0};
 
int lowbit(int x) {
	return x&-x;
}
 
void add(int x,int d){
	while(x<=100005){	//此处不应为x<=n 
		f[x]+=d;
		x+=lowbit(x);
	}
}
 
int sum(int x){
	int y=0; 
	while(x>0){
		y+=f[x];
		x-=lowbit(x);
	}
	return y;
}
 
int main() {
	
	int T;
	scanf("%d",&T);
	while(T--){
		
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));
		memset(d,0,sizeof(d));
		memset(f,0,sizeof(f));
		
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		
		add(a[1],1);
		for(int i=2;i<n;i++){
			c[i]=sum(a[i]-1);	//不计算当前的数，所以-1 
			add(a[i],1);
		}
		memset(f,0,sizeof(f));
		add(a[n],1);
		for(int i=n-1;i>=2;i--){
			d[i]=sum(a[i]-1);
			add(a[i],1);
		}
		
		long long ans=0;
		for(int i=2;i<n;i++){
			ans=ans+c[i]*(n-i-d[i])+(i-1-c[i])*d[i];
		}
		
		printf("%lld\n",ans);
		
	}
	
	return 0;
}
```


---

