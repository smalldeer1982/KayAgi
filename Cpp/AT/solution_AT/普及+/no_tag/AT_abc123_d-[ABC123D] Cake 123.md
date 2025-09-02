# [ABC123D] Cake 123

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc123/tasks/abc123_d

AtCoder 洋菓子店は数字の形をしたキャンドルがついたケーキを販売しています。  
 ここには $ 1,\ 2,\ 3 $ の形をしたキャンドルがついたケーキがそれぞれ $ X $ 種類、$ Y $ 種類、$ Z $ 種類あります。  
 それぞれのケーキには「美味しさ」という整数の値が以下のように割り当てられています。

- $ 1 $ の形のキャンドルがついたケーキの美味しさはそれぞれ $ A_1,\ A_2,\ ...,\ A_X $
- $ 2 $ の形のキャンドルがついたケーキの美味しさはそれぞれ $ B_1,\ B_2,\ ...,\ B_Y $
- $ 3 $ の形のキャンドルがついたケーキの美味しさはそれぞれ $ C_1,\ C_2,\ ...,\ C_Z $

高橋君は ABC 123 を記念するために、$ 1,\ 2,\ 3 $ の形のキャンドルがついたケーキを $ 1 $ つずつ買うことにしました。  
 そのようにケーキを買う方法は $ X\ \times\ Y\ \times\ Z $ 通りあります。

これらの選び方を $ 3 $ つのケーキの美味しさの合計が大きい順に並べたとき、$ 1,\ 2,\ ...,\ K $ 番目の選び方でのケーキの美味しさの合計をそれぞれ出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ 1\ 000 $
- $ 1\ \leq\ Y\ \leq\ 1\ 000 $
- $ 1\ \leq\ Z\ \leq\ 1\ 000 $
- $ 1\ \leq\ K\ \leq\ \min(3\ 000,\ X\ \times\ Y\ \times\ Z) $
- $ 1\ \leq\ A_i\ \leq\ 10\ 000\ 000\ 000 $
- $ 1\ \leq\ B_i\ \leq\ 10\ 000\ 000\ 000 $
- $ 1\ \leq\ C_i\ \leq\ 10\ 000\ 000\ 000 $
- 入力中の値はすべて整数である。

### Sample Explanation 1

$ 3 $ つのケーキの選び方は $ 2\ \times\ 2\ \times\ 2\ =\ 8 $ 通りあり、それらをケーキの美味しさの合計が大きい順に並べると以下の通りです。 - $ (A_2,\ B_2,\ C_2) $: $ 6\ +\ 5\ +\ 8\ =\ 19 $ - $ (A_1,\ B_2,\ C_2) $: $ 4\ +\ 5\ +\ 8\ =\ 17 $ - $ (A_2,\ B_1,\ C_2) $: $ 6\ +\ 1\ +\ 8\ =\ 15 $ - $ (A_2,\ B_2,\ C_1) $: $ 6\ +\ 5\ +\ 3\ =\ 14 $ - $ (A_1,\ B_1,\ C_2) $: $ 4\ +\ 1\ +\ 8\ =\ 13 $ - $ (A_1,\ B_2,\ C_1) $: $ 4\ +\ 5\ +\ 3\ =\ 12 $ - $ (A_2,\ B_1,\ C_1) $: $ 6\ +\ 1\ +\ 3\ =\ 10 $ - $ (A_1,\ B_1,\ C_1) $: $ 4\ +\ 1\ +\ 3\ =\ 8 $

### Sample Explanation 2

美味しさの合計が同じになる組み合わせが複数ある可能性もあります。例えば、このテストケースで $ (A_1,\ B_3,\ C_3) $ を選ぶときと $ (A_3,\ B_3,\ C_1) $ を選ぶときはともに、美味しさの合計が $ 301 $ となります。 しかし、これらは異なる選び方であるため、出力には $ 301 $ が $ 2 $ 回出現します。

### Sample Explanation 3

入力・出力は $ 32 $ ビット整数に収まらない可能性があることに注意してください。

## 样例 #1

### 输入

```
2 2 2 8
4 6
1 5
3 8```

### 输出

```
19
17
15
14
13
12
10
8```

## 样例 #2

### 输入

```
3 3 3 5
1 10 100
2 20 200
1 10 100```

### 输出

```
400
310
310
301
301```

## 样例 #3

### 输入

```
10 10 10 20
7467038376 5724769290 292794712 2843504496 3381970101 8402252870 249131806 6310293640 6690322794 6082257488
1873977926 2576529623 1144842195 1379118507 6003234687 4925540914 3902539811 3326692703 484657758 2877436338
4975681328 8974383988 2882263257 7690203955 514305523 6679823484 4263279310 585966808 3752282379 620585736```

### 输出

```
23379871545
22444657051
22302177772
22095691512
21667941469
21366963278
21287912315
21279176669
21160477018
21085311041
21059876163
21017997739
20703329561
20702387965
20590247696
20383761436
20343962175
20254073196
20210218542
20150096547```

# 题解

## 作者：龙潜月十五 (赞：10)

## 一、前言

本题是贪心中的一种题型 **堆优化贪心** 的一种模型，本文将介绍其 **证明** 与 **实现**。

## 二、题意

有三行序列，每次都要从每一行中选一个数，将所选的三个数相加，得到一个新数。如此操作，输出所得的前 $K$ 大的数。

## 三、思路

既然要选前 $K$ 大的数，我们先将三个序列从大到小排序，那么显然最大的显然是 $a_1+b_1+c_1$。那么第二大的呢？我们有三个选择：$a_2+b_1+c_1$ 、 $a_1+b_2+c_1$ 与 $a_1+b_1+c_2$，不可能有其他选择。

**证明**：

~~显然~~。首先三个序列都是从大到小排列的，排在越前的数显然越大。$a_1,b_1,c_1$ 都是最大值，想要获得三个数的和的次小值肯定是 **将一个最大值变成次大值**，不可能将两个最大值变为次大值。假设修改两个数，即 $a_2+b_2+c_1$， 其一定不可能是次大值，因为一定有 
$$a_2+b_2+c_1\leq a_2+b_1+c_1\leq a_1+b_1+c_1$$ 

$a_2+b_1+c_1$ 一定比它更有可能是次大值。因此得证。

之后每次都面临相同的选择，因此我们考虑将它们都丢进 **大根堆** 里。若当前队首为 $a_i+b_j+c_k$，就把 $a_{i+1}+b_j+c_k$、$a_i+b_{j+1}+c_k$、  $a_i+b_j+c_{k+1}$ 都丢进堆里，$k$ 次操作后的队首就是第 $k$ 小的情况。


还要考虑到 **重复** 的情况。$a_{i-1}+b_j+c_k$ 会产生 $a_i+b_j+c_k$，$a_i+b_{j-1}+c_k$ 和 $a_i+b_j+c_{k-1}$ 也会产生 $a_i+b_j+c_k$，$a_i+b_j+c_k$ 会重复出现，这是我们不愿意看到的。因此我们要考虑 **去重**。我是用 `map` 来做的，不知道有没有别的方法。

## 四、代码

```cpp
#include<bits/stdc++.h>
#define ri register int
using namespace std;
typedef long long ll;

const int N=1e3+7;
int x,y,z,k;
ll a[N],b[N],c[N];
struct node
{
	int x,y,z;
	
	bool operator < (const node &oth) const
	{
		return a[x]+b[y]+c[z]<a[oth.x]+b[oth.y]+c[oth.z];
	}//重载运算符
};
priority_queue<node>q;//大根堆
map<pair<pair<int,int>,int>,bool>mp;//标记

bool cmp(ll a,ll b)
{
	return a>b;
}

inline ll read()
{
	ll sum=0,ff=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
			ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

int main()
{
	x=read(),y=read(),z=read(),k=read();
	for(ri i=1;i<=x;i++)
		a[i]=read();
	for(ri i=1;i<=y;i++)
		b[i]=read();
	for(ri i=1;i<=z;i++)
		c[i]=read();
	
	sort(a+1,a+1+x,cmp);
	sort(b+1,b+1+y,cmp);
	sort(c+1,c+1+z,cmp);
	
	q.push((node){1,1,1});
	mp[make_pair(make_pair(1,1),1)]=true;
	
	for(ri i=1;i<=k;i++)
	{
		node now=q.top();
		q.pop();
		printf("%lld\n",a[now.x]+b[now.y]+c[now.z]);
		
		if(!mp.count(make_pair(make_pair(now.x+1,now.y),now.z))&&now.x<x)
		{
			mp[make_pair(make_pair(now.x+1,now.y),now.z)]=true;
			q.push((node){now.x+1,now.y,now.z});
		}
		if(!mp.count(make_pair(make_pair(now.x,now.y+1),now.z))&&now.y<y)
		{
			mp[make_pair(make_pair(now.x,now.y+1),now.z)]=true;
			q.push((node){now.x,now.y+1,now.z});
		}
		if(!mp.count(make_pair(make_pair(now.x,now.y),now.z+1))&&now.z<z)
		{
			mp[make_pair(make_pair(now.x,now.y),now.z+1)]=true;
			q.push((node){now.x,now.y,now.z+1});
		}
	}

	return 0;
}
```


---

## 作者：きりと (赞：8)

**[题目传送门](https://www.luogu.com.cn/problem/AT4720)**

### 题目大意

见中文翻译。

### 解题思路

数据范围题，一开始完全没思路，直到看到数据范围里有 $k\le min(3000,x\times y\times z)$。

也就是说，最后要求的方案数不会超过 $3000$，那么我们只需要先暴力枚举，算出 $a,b$ 组合出来的所有情况，然后拿这里的前 $k$ 种和剩下的 $c$ 再去组合，然后`sort`一遍求前 $k$ 个就完了，时间复杂度和空间复杂度都刚好卡进限制（可以试着自己分析一下），卡个常啥的就稳稳地过题了，但是因为一些原因，我没卡。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define forr(i,l,r) for(int i=l;i<=r;i++)
#define ffor(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
const int N=1e3+10;
int a[N],b[N],c[N],d[N*N],ans[3*N*N];
bool cmp(int q,int p)
{
    return q>p;
}
signed main()
{
    int x,y,z,k;
    cin>>x>>y>>z>>k;
    forr(i,1,x)
    {
        cin>>a[i];
    }
    forr(i,1,y)
    {
        cin>>b[i];
    }
    forr(i,1,z)
    {
        cin>>c[i];
    }
    int c1=0;
    forr(i,1,x)
    {
        forr(j,1,y)
        {
            d[++c1]=a[i]+b[j];
        }
    }
    sort(d+1,d+c1+1,cmp);
    int c2=0;
    forr(i,1,k)
    {
        forr(j,1,z)
        {
            ans[++c2]=d[i]+c[j];
        }
    }
    sort(ans+1,ans+c2+1,cmp);
    forr(i,1,k)
    {
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

时间复杂度：$O(n^2logn)$ 带常数。

---

## 作者：Otomachi_Una_ (赞：2)

实际上，这道题可以先求 $a_i+b_j$ 的前 $k$ 小(如果当 $ x \times y <k$ 直接求前$x \times y$ 即可)，然后记录在 $num$ 数组内，然后再计算 $c_i+num_j$ 的前 $k$ 小即可。

## _code_
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
int x,y,z,k;
const ll INF=-1e17;
const int MAXN=1e3+5;
const int MR=3e3+5;
ll a[MAXN],b[MAXN],c[MAXN];
priority_queue< pair<ll,int> > q;
ll num[MR];//记录a[i]+b[j]前k小
int p_c[MR];//当前c[i]使用的num[p[i]]
int p_b[MR];
bool cmp(ll x,ll y){
	return x>y;
}
int main(){
	cin>>x>>y>>z>>k;
	for(int i=1;i<=x;i++)
		cin>>a[i];
	for(int i=1;i<=y;i++)
		cin>>b[i];
	for(int i=1;i<=z;i++)
		cin>>c[i];
	sort(a+1,a+x+1,cmp);
	for(int i=1;i<=y;i++){
		q.push(make_pair(b[i]+a[1],i));
		p_b[i]=1;
	}
	for(int i=1;i<=k&&i<=x*y;i++){
		int bh=q.top().second;
		num[i]=q.top().first;
		q.pop();
		q.push(make_pair(a[++p_b[bh]]+b[bh],bh));
	}//计算num_c
	while(!q.empty())
		q.pop();//清空q
	for(int i=1;i<=z;i++){
		q.push(make_pair(c[i]+num[1],i));
		p_c[i]=1;
	}
	for(int i=1;i<=k;i++){
		int bh=q.top().second;
		cout<<q.top().first<<endl;
		q.pop();
		q.push(make_pair(num[++p_c[bh]]+c[bh],bh));
	}
	return 0;
}
}
```


---

## 作者：Anaxagoras (赞：1)

[题目传送门](https://www.bilibili.com/video/BV1Wp4y1H7A4/?spm_id_from=333.788.recommend_more_video.1)

### 0x01 思路

由于最近我在学动态规划，所以我看到这题第一反应就是动态规划，知道我设数组范围时看到了 $1\le K\le \min \left (3000,X\times Y\times Z\right )$ 这一句话就立马想到了暴力枚举。

首先用一个数组（我用的是 `olkieler`，没错就是我的用户名）存下 `a` 数组每一个与 `b` 数组每一个两两配对的每一种可能，从大到小排一遍序（一位输出的是前 `k` 大的），再用一个数组（我用的是 `dpkajj`，这是一位大佬，可以去膜拜他）存下 `olkieler` 前 `k` 个与 `c` 数组每一个两两配对的结果，接着再从大到小排一遍序（理由同上），输出 `dpkajj` 数组的前 `k` 个就行了。

这里给大家介绍一个东西：`greater<int>()`，它可以把 `sort` 的从小到大排序变为从大到小，用法为 `sort(a+1,a+n+1,greater<int>())`，也可以把 `lower_bound`（或`upper_bound`）的在一个不下降序列中找出第一个大于或等于（大于）`value` 的数，变为在一个不上升序列中找出第一个小于或等于（小于）`value` 的数。

### 0x02 AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1005
using namespace std;
int a[N];
int b[N];
int c[N];
int olkieler[N*N];
int dpkajj[3*N*N];
signed main()
{
 ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int x,y,z,k,rp=0,ak=0;//rp 是控制 olkieler 下标的，ak 是控制 dpkajj 下标的
  cin>>x>>y>>z>>k;
  for(int i=1;i<=x;i++)
    {
      cin>>a[i];
    }
  for(int i=1;i<=y;i++)
    {
      cin>>b[i];
    }
  for(int i=1;i<=z;i++)
    {
      cin>>c[i];
    }
  for(int i=1;i<=x;i++)
    {
      for(int j=1;j<=y;j++)//枚举每一种可能
	{
	  olkieler[++rp]=a[i]+b[j];//olkieler 又加了 rp（逃
	}
    }
  sort(olkieler+1,olkieler+rp+1,greater<int>());//排序
  for(int i=1;i<=k;i++)//只选前 k 个就行了
    {
      for(int j=1;j<=z;j++)//同上
	{
	  dpkajj[++ak]=olkieler[i]+c[j];//dpkajj 又 ak 了（光速逃
	}
    }
  sort(dpkajj+1,dpkajj+ak+1,greater<int>());//同上
  for(int i=1;i<=k;i++)
    {
      cout<<dpkajj[i]<<'\n';
    }
}
```

---Bye---

---

## 作者：Nightingale_OI (赞：1)

### 大意

给你三个长度为 $ x $ ， $ y $ ， $ z $ 的数组 $ a $ ， $ b $ ， $ c $ 。

在 $ a $ ， $ b $ ， $ c $ 中各选择一个元素求和，结果构成 $ d $ 。

问你把 $ d $ 排序后的前 $ k $ 个元素。

### 思路

我们发现 $ k \leq 3000 $ ，只需要枚举选 $ a $ 中选的元素，找出前 $ k $ 个，一共就是 $ 3000000 $ 个元素，排序即可。

我们先使 $ c $ 数组降序。

记录选择 $ b $ 中某个元素后没有被计入答案的和的最大值、对应选择的 $ c $ 数组的下标。

用优先队列维护一个结构体，每次取出和最大的。

设最大的为 $ (i , j) $ ，则记录后加入 $ (i - c_j + c_{j + 1} , j + 1) $ 即可（ $ j = z $ 时不必）。

注意初始优先队列中元素是对于 $ 1 \leq i \leq y $ 的所有 $ (b_i+c_1,1) $ 。

复杂度 $ O(xk \log_{2}{xk} + xk \log_{2}{y}) $。

PS ：写的时候没看题，以为是和最小，所以代码维护的全部反了过来。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
struct xy{
    long long x;
    int y;
}ls;
bool operator < (xy a,xy b){
    return a.x>b.x;
}
long long a[1010];
long long b[1010];
long long c[1010];
priority_queue<xy>d;
int main(){
    cin>>n>>m>>s>>l;
    f(i,1,n)scanf("%lld",&a[i]),a[i]=-a[i];sort(a+1,a+n+1);
    f(i,1,m)scanf("%lld",&b[i]),b[i]=-b[i];sort(b+1,b+m+1);
    f(i,1,s)scanf("%lld",&c[i]),c[i]=-c[i];sort(c+1,c+s+1);
    f(i,1,n){
        int cy=l;
        priority_queue<xy>e;
        f(j,1,m)e.push((xy){b[j]+c[1],1});
        while(cy-- && e.size()){
            ls=e.top();
            e.pop();
            d.push((xy){ls.x+a[i],0});
            if(ls.y<s)e.push((xy){ls.x-c[ls.y]+c[ls.y+1],ls.y+1});
        }
    }
    while(l--){
        printf("%lld\n",-d.top().x);
        d.pop();
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定三个序列，长度分别为 $x, y, z$，你需要在三个序列里每个序列选一个数求和，有 $x \cdot y \cdot z$ 种和，求从大到小前 $k$ 个和。
 
## 解法

最暴力的做法是枚举每一种和，然后排序求前 $k$ 个，复杂度 $O(xyz \log (xyz))$。

注意到 $1 \leq x, y, z \leq 10^3$，考虑低于三次方的做法。

可以考虑先枚举前两个序列的所有和，共 $xy$ 个，接下来排序后取前 $k$ 个和剩下的序列求和。

这个复杂度看起来也是平方的，显然当 $k=xy$ 时，枚举的和仍然是 $xyz$ 个。

但是注意 $k \leq \min\{3000, xyz\}$，所以 $k$ 的上限为 $3000$。可以接受。

复杂度为 $O(xy \log (xy))$ 左右，可以通过。


---

## 作者：BigJoker (赞：0)

# 0x00 前言

此题调了我好久，先开始方法有问题，后来是数组越界，然后是没开 long long，做了好久......

# 0x01 思路

* **暴力**

首先想到一种很暴力的方法，从 a 数组和 b 数组和 c 数组中，每个数组中选择一个出来加，然后放在一个数组中，然后从大到小排序，前 $k$ 个就是答案。我们来分析一下数据：

$x,y,z\le10^3$

如果按照我们上面的一种方法，我们考虑极端情况 $x,y,z$ 都是 $10^3$，那么数组就要开 $10^9$，明显会炸。

* **优化**

这时候需要优化，我们来看一下优化方式。先开始只取 a 数组和 b 数组中的数然后用一个数组存它们的和，然后从大到小排序，然后因为要求取前 $k$ 大，所以答案根本不可能从刚才这个数组中的 $k+1$ 个数及其以后产生，所以我们只取刚才这个数组中的前 $k$ 个数，然后和 c 数组的每个数加起来，用一个新数组存储，最后这个新数组从大到小排序后的的前 $k$ 个数就是答案。

# 0x02 细节

* **数组**

我们来分析一下优化后的数组的大小。

$x,y\le10^3$

那么第一个数组只需要开 $10^6$ 就可以了。

第二个数组需要看 $k$。

$k\le3\times10^3$

$c\le10^3$

那么需要开 $3\times10^6$，根本不会炸，所以优化是可行的。

* **范围**

注意此题需要开 long long，不然会炸。

# 0x03 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
int x,y,z,k,tot,a[1005],b[1005],c[1005],q[1000005],p[3000005],po;
bool cmp(int l,int r){return l>r;}
signed main(){
	scanf("%lld %lld %lld %lld",&x,&y,&z,&k);
	rep(i,1,x) scanf("%lld",&a[i]);
	rep(i,1,y) scanf("%lld",&b[i]);
	rep(i,1,z) scanf("%lld",&c[i]);
	rep(i,1,x)
		rep(j,1,y)
			q[++tot]=a[i]+b[j];
	sort(q+1,q+1+tot,cmp);
	rep(i,1,z){
		rep(j,1,k){
			p[++po]=q[j]+c[i];
		}
	}
	sort(p+1,p+1+po,cmp);
	rep(i,1,k) printf("%lld\n",p[i]);
	return 0;
}
```


---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4720)

### 思路

**贪心**

题目意思就是说在三个序列里面每个序列列中都选择一个数，让你求出在选择的数中输出最大的 $k$ 个总和。

由于他有三个序列,所以我们可以先求出 $a$，$b$ 序列中最大的 $k$ 个两个数之和，并存入 $ans1$ 数组。再来求出 $ans1$ 和 $c$ 这两个序列中最大的 $k$ 两个数之和，最后直接输出即可。

**证明**

接下来给大家证明一下这个结论。

假设 $a$，$b$ 序列中第 $k$ 大的两个数之和为 $w1$，第 $k+1$ 大的两个数之和为 $w2$。 那么很显然 $w1+c_i$ 一定大于 $w2+c_i$ 。

也就是说前 $k$ 大的三个数之和一定是 $ans1$ 和 $c$ 这两个序列中前 $k$ 大的两个数之和。 

所以，结论成立。

### 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long ans1[1000005],ans2[3000005];
int x,y,z,k;
long long a[3005],b[3005],c[3005];
int cnt1,cnt2;
//不开 long long 见祖宗
int main()
{
    cin>>x>>y>>z>>k;
    for(int i=1;i<=x;++i)
    cin>>a[i];
    for(int i=1;i<=y;++i)
    cin>>b[i];
    for(int i=1;i<=z;++i)
    cin>>c[i];
    //输入
    for(int i=1;i<=x;++i)
    {
        for(int j=1;j<=y;++j)
        {
            ans1[++cnt1]=a[i]+b[j];
        }
    }
    sort(ans1+1,ans1+cnt1+1);
    //求出a,b两个序列前k大的两个数之和
    for(int i=cnt1;i>=max(cnt1-k+1,1);--i)//由于sort从小到大排序,所以倒着枚举。
    {
        for(int j=1;j<=z;++j)
        {
            ans2[++cnt2]=ans1[i]+c[j];
        }
    }
    sort(ans2+1,ans2+cnt2+1);
    //求出ans1,c两个序列前k大的两个数之和
    for(int i=cnt2;i>=cnt2-k+1;--i)
    {
        cout<<ans2[i]<<endl;//输出
    }
}
```

---

