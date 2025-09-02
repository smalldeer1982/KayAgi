# LIS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_h

数列 $ a $ から好きな整数を好きなだけ取り除き、単調増加な数列を作るとき、その数列の長さの最大値を求めなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
2```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
6```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
1```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
6```

# 题解

## 作者：花里心爱 (赞：45)

本题的数据范围为$1 \leq N \leq 10^6$

所以要用$O(nlogn)$算法

不然会超时 && 爆空间

算法说明：

我们用DP思想来维护一个栈。如果$a[i] > a[i-1]$,则将$a[i]$放入栈$s$中。否则，二分查找$s$中大于等于$a[i]$的最小的数，并将它替换。

<algorithm>库中提供了一个二分查找的函数：lower_bound
  用它可以实现二分查找一个数组中大于等于$key$的最小的数。

下面上代码：

```cpp
#include<cstdio>//不解释的头文件
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){//神奇的读优
    int f=1,d=0;char t=getchar();
    while(t<'0' || t>'9'){if(t=='-')f=-1;t=getchar();}
    while(t>='0' && t<='9'){d=d*10+t-'0';t=getchar();}return f*d;
}
int n,a[100010];
int s[100010],tot;//s为栈
int tmp;
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    s[++tot]=a[1];//先将a[1]放入栈中
    for(int i=2;i<=n;i++){
        if(a[i]>s[tot])s[++tot]=a[i];//如果a[i]>a[i-1],则将a[i]放入栈中
        else{
            tmp=lower_bound(s+1,s+tot+1,a[i])-s;//二分查找s中大于等于a[i]的最小的数
            s[tmp]=a[i];//替换
        }
    }
    printf("%d\n",tot);//最后栈中元素的数量即为答案
    return 0;
}
```

---

## 作者：灯芯糕 (赞：42)

## 求最长上升子序列的三种经典方案：

给定一个长度为 $N$ 的数列，求它数值单调递增的子序列长度最大为多少。即已知有数列 $A$ ， $A=\{A_1,A_2....A_n\}$ ，求 $A$  的任意子序列 $B$ （ $B=\{A_{k_1},A_{k_2}....A_{k_p}\}$ ），使 $B$ 满足 $k_1<k_2<....<k_p$ 且 $B=\{A_{k_1}<A_{k_2}<....<A_{k_p}\}$ 。求 $p$ 的最大值。 



------

------

### $solution\quad 1:$

先说一种最普遍的方法，因为这道题很容易想到一种动态规划。我们要求最长上升子序列，而如果我们要将这个问题分阶段，那么我们肯定要知道我们当前阶段最后一个元素为多少，还有当前我们的序列有多长。我们可以用前者来充当第一维描述：设 $F[i]$ 表示以 $A[i]$ 为结尾的最长上身子序列的长度，而我们肯定只能从 $i$ 前面的且末尾元素比 $A[i]$ 小的状态转移过来：

### $F[i]=^{max}_{0\leq j<i,A[j]<a[i]}\{F[j]+1\}$

初始值为 $F[0]=0$ ，而答案可以是任何阶段中只要长度最长的那一个，所以我们边转移边统计答案。 

复杂度： $O(n^2)$ 

### $code\quad 1:$

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rg register int
using namespace std;

int n,ans;
int a[10005];
int f[10005];

int main(){ cin>>n;
	for(rg i=1;i<=n;++i) cin>>a[i];
	for(rg i=1;i<=n;++i){
		for(rg j=1;j<i;++j)
			if(a[j]<a[i])f[i]=max(f[i],f[j]);
		++f[i]; ans=max(ans,f[i]);
	}cout<<ans<<endl;
	return 0;
}
```



------



### $solution\quad 2:$

然后我们先对上一种方法进行优化，我们将转移方程列一下：

### $F[i]=^{max}_{0\leq j<i,A[j]<a[i]}\{F[j]+1\}$

我们发现大括号中的1与 $j$ 似乎没有半毛钱关系，所以我们将它提取出来：

### $F[i]=^{max}_{0\leq j<i,A[j]<a[i]}\{F[j]\}+1$

然后我们发现我们只需要将比 $i$ 小的所有的符合 $A[j]<A[i]$ 的 $F[j]$ 的最大值求出来，但是这个条件 $A[j]<A[i]$ 实在是太麻烦了，所以我们换一种方法：我们将 $A$ 数组的每一个元素先记下他现在的标号，然后按照权值从小到大排序，接着我们按从大到小的顺序枚举 $A$ 数组，这时我们需要从之前的标号比它小的状态转移过来，这个我们只需要建立一个与编号为下标维护长度的最大值的树桩数组即可，枚举 $A$ 数组时按元素的序号找到它之前序号比他小的长度最大的状态更新，然后将它也加入树状数组中。 复杂度： $O(nlog(n))$ 

### $code\quad 2:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rg register int
using namespace std;

int n;
int s[200005];

struct su{
    int v,id;
    inline bool operator <(su x){return v<x.v;}
}a[200005];

inline void add(int x,int y){
    for(;x<=n;x+=x&-x) s[x]=max(s[x],y);
}

inline int ask(int x){
    rg res=0;
    for(;x>=1;x-=x&-x) res=max(s[x],res);
    return res;
}

int main(){
    cin>>n;
    for(rg i=1;i<=n;++i)
        cin>>a[i].v,a[i].id=i;
    sort(a+1,a+n+1);
    for(rg i=1;i<=n;++i)
        if(i==1||a[i].v!=a[i-1].v)// 这一步是去重，如果没有这个if就是求最长不下降子序列！
            add(a[i].id,ask(a[i].id)+1);
    cout<<ask(n)<<endl; 
    return 0;
}

```



------



### $solution\quad 3:$

这是最快的方法：贪心加二分查找

我们之前说过：我们肯定要知道我们当前阶段最后一个元素为多少，还有当前我们的序列有多长。前两种方法都是用前者做状态，我们为什么不可以用后做状态呢？：设 $F[i]$ 表示长度为 $i$ 的最长上升子序列的末尾元素的最小值，我们发现这个数组的权值一定单调不降（仔细想一想，这就是我们贪心的来由）。于是我们按顺序枚举数组 $ A$ ，每一次对 $F[]$ 数组二分查找，找到小于 $A[i]$ 的最大的 $F[j] $ ，并用它将 $F[j+1]$更新。    

复杂度： $O(nlogn)$ 

### $code\quad 3:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rg register int
using namespace std;

int n;
int a[200005];
int f[200005];

int main(){
	cin>>n;
	for(rg i=1;i<=n;++i) cin>>a[i];
	rg ans=1; f[1]=a[1];
	for(rg i=2;i<=n;++i){
		rg l=1,r=ans,mid;
		while(l<=r){
			mid=(l+r)>>1;
			if(a[i]<=f[mid])r=mid-1;
			else l=mid+1;
		}f[l]=a[i];
		if(l>ans)++ans;
	}cout<<ans<<endl;
	return 0;
}
```



------



---

## 作者：星爵 (赞：37)

## 题目[AT2827 LIS](https://www.luogu.org/problemnew/show/AT2827)
#### 大家都用dp写的
#### 但是我dp太菜
#### 于是写了个树状数组
#### ~~代码都在注释里~~ 注释都在代码里
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int rd(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-fl;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*fl;
}
int n,b[100100],a[100100];
ll c[100100],f[100100];
void upd(int x,ll v){
	for(;x<=n;x+=x&-x)
		c[x]=max(c[x],v);                          //前x个数中的维护最大值
}
ll ask(int x){
	ll cnt=0;
	for(;x>=1;x-=x&-x)
		cnt=max(cnt,c[x]);
	return cnt;
}
void init(){
	n=rd();ll ans=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)b[i]=a[i]=rd();
	sort(b+1,b+n+1);
	unique(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;//离散化，这题好像用不到...
}
void work(){
	for(int i=1;i<=n;i++){
		f[i]=ask(a[i])+1;                             //每次更新最大值
		upd(a[i],f[i]);
	}
}
void outt(){
	ll ans=1;
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i]);
	printf("%lld",ans);
}
int main(){
	init();
	work();
	outt();
	return 0;
}
```
是不是感觉有点玄学

这里给出一个证明 ~~可惜Lougu太小我写不下~~

举一个简单的栗子：

对于 1 4 2 3 5这个序列

显然他的LIS是4也就是 1 2 3 5

#### 然后我们设 f[i]表示以a[i]结尾的LIS
### 有f[i]=max{f[j]+1 | j<i&&a[i]<a[j]};(这个写成集合的形式应该能懂吧

~~很显然~~可以使用树状数组优化

由于插入n次，每次询问代价是logn

总复杂的就是O(nlogn).

emmm...

还没看懂？

# 上图！


#### 首先我们先把**1**放入树状数组

发现**1**前并无数或者说f[0]=0;

则将f[1]赋值为**f[0]+1=1**，且树状数组中1位置赋值为1；
![](https://s1.ax1x.com/2018/10/27/i6jgb9.png)

#### 然后插入**4**

发现**4**前fmax=f[1]=1;

则将f[4]赋值为**f[1]+1=2**，且树状数组中4位置赋值为2；
![](https://s1.ax1x.com/2018/10/27/i6j4C6.png)：

#### 然后插入**2**

发现**2**前fmax=f[1]=1;

则将f[2]赋值为**f[1]+1=2**，且树状数组中2位置赋值为2；
![](https://s1.ax1x.com/2018/10/27/i6j58K.png)

#### 然后插入**3**

发现**3**前fmax=f[2]=2;

则将f[3]赋值为**f[2]+1=3**，且树状数组中3位置赋值为3；
![](https://s1.ax1x.com/2018/10/27/i6jIgO.png)

#### 然后插入**5**

发现**5**前fmax=f[3]=3;

则将f[5]赋值为**f[3]+1=4**，且树状数组中5位置赋值为4；

![](https://s1.ax1x.com/2018/10/27/i6jovD.png)

emmmm

差不多了吧
附上精简版代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,x,b[100100],a[100100];
ll c[100100],f[100100];
void upd(int x,ll v){
	for(;x<=n;x+=x&-x)
		c[x]=max(c[x],v);
}
ll ask(int x){
	ll cnt=0;
	for(;x>=1;x-=x&-x)
		cnt=max(cnt,c[x]);
	return cnt;
}

int main(){
	scanf("%d",&n);
	ll ans=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		f[i]=ask(x)+1;
		upd(x,f[i]);
	}
	
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i]);
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：GossWandering (赞：34)

hello，大家好
~~，我是库里的球迷~~

Emm..别闹了，开始说正题吧

列位看官留意，LIS（Longest  Increasing Subsequence，最长上升子序列）是dp（也就是动态规划）算法的非常经典也非常常见，常考的应用。

下面我们来了解一下LIS：
> 最长上升子序列（Longest  Increasing Subsequence），简称LIS，也有些情况求的是最长非降序子序列，二者区别就是序列中是否可以有相等的数。假设我们有一个序列 b i，当b1 < b2 < … < bS的时候，我们称这个序列是上升的。对于给定的一个序列(a1, a2, …, aN)，我们也可以从中得到一些上升的子序列(ai1, ai2, …, aiK)，这里1 <= i1 < i2 < … < iK <= N，但必须按照从前到后的顺序。比如，对于序列(1, 7, 3, 5, 9, 4, 8)，我们就会得到一些上升的子序列，如(1, 7, 9), (3, 4, 8), (1, 3, 5, 8)等等，而这些子序列中最长的（如子序列(1, 3, 5, 8) ），它的长度为4，因此该序列的最长上升子序列长度为4。

额，真抽象，我给你们解释一下

首先需要知道，**子串**和**子序列**的概念，我们以字符子串和字符子序列为例，更为形象，也能顺带着理解字符的子串和子序列：

1. 字符子串指的是字符串中连续的n个字符，如abcdefg中，ab，cde，fg等都属于它的字串。
1. 字符子序列指的是字符串中不一定连续但先后顺序一致的n个字符，即可以去掉字符串中的部分字符，但不可改变其前后顺序。如abcdefg中，acdg，bdf属于它的子序列，而bac，dbfg则不是，因为它们与字符串的字符顺序不一致。

知道了这个，数值的子序列就很好明白了，即用数组成的子序列。这样的话，最长上升子序列也很容易明白了，归根结底还是子序列，然后子序列中，按照上升顺序排列的最长的就是我们最长上升子序列了，这样听来是不是就很容易明白啦～

 还有一个非常重要的问题：请大家用集合的观点来理解这些概念，子序列、公共子序列以及最长公共子序列都不唯一，但很显然，对于固定的数组，虽然LIS序列不一定唯一，但LIS的长度是唯一的。再拿我们刚刚举的栗子来讲，给出序列 ( 1, 7, 3, 5, 9, 4, 8)，易得最长上升子序列长度为4,这是确定的，但序列可以为 ( 1, 3, 5, 8 ), 也可以为 ( 1, 3, 5, 9 )。
 
> 说了半天，到底应该怎么求LIS的长度呢？
 
这里详细介绍一下求LIS的三种方法，分别是O(n^2)的DP，O(nlogn)的二分+贪心法，以及O(nlogn)的树状数组优化的DP。

一、算法一【动态规划】

我们都知道，动态规划的一个特点就是当前解可以由上一个阶段的解推出， 由此，把我们要求的问题简化成一个更小的子问题。子问题具有相同的求解方式，只不过是规模小了而已。最长上升子序列就符合这一特性。我们要求n个数的最长上升子序列，可以求前n-1个数的最长上升子序列，再跟第n个数进行判断。求前n-1个数的最长上升子序列，可以通过求前n-2个数的最长上升子序列……直到求前1个数的最长上升子序列，此时LIS当然为1。

让我们举个例子：求 2 7 1 5 6 4 3 8 9 的最长上升子序列。我们定义d(i) (i∈[1,n])来表示前i个数以A[i]结尾的最长上升子序列长度。

- 前1个数 d(1)=1 子序列为2；

- 前2个数 7前面有2小于7 d(2)=d(1)+1=2 子序列为2 7
- 前3个数 在1前面没有比1更小的，1自身组成长度为1的子序列 d(3)=1 子序列为1
- 前4个数 5前面有2小于5 d(4)=d(1)+1=2 子序列为2 5

- 前5个数 6前面有2 5小于6 d(5)=d(4)+1=3 子序列为2 5 6

- 前6个数 4前面有2小于4 d(6)=d(1)+1=2 子序列为2 4

- 前7个数 3前面有2小于3 d(3)=d(1)+1=2 子序列为2 3

- 前8个数 8前面有2 5 6小于8 d(8)=d(5)+1=4 子序列为2 5 6 8

- 前9个数 9前面有2 5 6 8小于9 d(9)=d(8)+1=5 子序列为2 5 6 8 9

> d(i)=max{d(1),d(2),……,d(i)}
我们可以看出这9个数的LIS为d(9)=5

总结一下，d(i)就是找以A[i]结尾的，在A[i]之前的最长上升子序列+1，当A[i]之前没有比A[i]更小的数时，d(i)=1。所有的d(i)里面最大**的那个就是最长上升子序列。其实说的通俗点，就是每次都向前找比它小的数和比它大的数的位置，将第一个比它大的替换掉，这样操作虽然LIS序列的具体数字可能会变，但是很明显LIS长度还是不变的**，因为只是把数替换掉了，并没有改变增加或者减少长度。但是我们通过这种方式是无法求出最长上升子序列具体是什么的，这点和最长公共子序列不同。

明白了？尝试程序表达一下吧，要注意初始化。
> 思考完后再看呦

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,ans;
int a[200010],dp[200010]={1}; //初始化
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=1; i<=n; i++) {
		dp[i]=1;
		for(int j=1; j<i; j++)
			if(a[i]>a[j] && dp[i]<dp[j]+1)  //判断
				dp[i]=dp[j]+1;
		ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}
```
O(n^2),太大，100000数据有点吃力。。。

二、【算法二】 贪心+二分

新建一个 low 数组，low [ i ]表示长度为i的LIS结尾元素的最小值。**对于一个上升子序列，显然其结尾元素越小，越有利于在后面接其他的元素，也就越可能变得更长。** 因此，我们只需要维护 low 数组，对于每一个a[ i ]，如果a[ i ] > low [当前最长的LIS长度]，就把 a [ i ]接到当前最长的LIS后面，即low [++当前最长的LIS长度] = a [ i ]。 

那么，怎么维护 low 数组呢？

对于每一个a [ i ]，如果a [ i ]能接到 LIS 后面，就接上去；否则，就用 a [ i ] 取更新 low 数组。具体方法是，在low数组中找到第一个大于等于a [ i ]的元素low [ j ]，用a [ i ]去更新 low [ j ]。如果从头到尾扫一遍 low 数组的话，时间复杂度仍是O(n^2)。我们注意到 low 数组内部一定是单调不降的，所有我们可以二分 low 数组，找出第一个大于等于a[ i ]的元素。二分一次 low 数组的时间复杂度的O(lgn)，所以总的时间复杂度是O(nlogn)。

> 我们再举一个例子：有以下序列A[ ] = 3 1 2 6 4 5 10 7，求LIS长度。

我们定义一个B[ i ]来储存可能的排序序列，len 为LIS长度。我们依次把A[ i ]有序地放进B[ i ]里。

（为了方便，i的范围就从1~n表示第i个数）

- A[1] = 3，把3放进B[1]，此时B[1] = 3，此时len = 1，最小末尾是3

- A[2] = 1，因为1比3小，所以可以把B[1]中的3替换为1，此时B[1] = 1，此时len = 1，最小末尾是1

- A[3] = 2，2大于1，就把2放进B[2] = 2，此时B[ ]={1,2}，len = 2

- A[4]=6，把6放进B[3] = 6，B[ ]={1,2,6}，len = 3

- A[5]=4，4在2和6之间，比6小，可以把B[3]替换为4，B[ ] = {1,2,4}，len = 3

- A[6] = 5，B[4] = 5，B[ ] = {1,2,4,5}，len = 4 

- A[7] = 10，B[5] = 10，B[ ] = {1,2,4,5,10}，len = 5

- A[8] = 7，7在5和10之间，比10小，可以把B[5]替换为7，B[ ] = {1,2,4,5,7}，len = 5

最终我们得出LIS长度为5，**但是，但是！！！B[ ] 中的序列并不一定是正确的最长上升子序列。** 在这个例子中，我们得到的1 2 4 5 7 恰好是正确的最长上升子序列，下面我们再举一个例子：
> 有以下序列A[ ] = 1 4 7 2 5 9 10 3，求LIS长度。

- A[1] = 1，把1放进B[1]，此时B[1] = 1，B[ ] = {1}，len = 1

- A[2] = 4，把4放进B[2]，此时B[2] = 4，B[ ] = {1,4}，len = 2

- A[3] = 7，把7放进B[3]，此时B[3] = 7，B[ ] = {1,4,7}，len = 3

- A[4] = 2，因为2比4小，所以把B[2]中的4替换为2，此时B[ ] = {1,2,7}，len = 3

- A[5] = 5，因为5比7小，所以把B[3]中的7替换为5，此时B[ ] = {1,2,5}，len = 3

- A[6] = 9，把9放进B[4]，此时B[4] = 9，B[ ] = {1,2,5,9}，len = 4

- A[7] = 10，把10放进B[5]，此时B[5] = 10，B[ ] = {1,2,5,9,10}，len = 5

- A[8] = 3，因为3比5小，所以把B[3]中的5替换为3，此时B[ ] = {1,2,3,9,10}，len = 5

最终我们得出LIS长度为5。但是，但是！！这里的1 2 3 9 10很明显并不是正确的最长上升子序列。因此，B序列并不一定表示最长上升子序列，它只表示相应最长子序列长度的排好序的最小序列。这有什么用呢？我们最后一步3替换5并没有增加最长子序列的长度，而这一步的意义，在于记录最小序列，代表了一种“最可能性”，只是此种算法为计算LIS而进行的一种替换。假如后面还有两个数据12和15，那么B[ ]将继续更新。

因为在B中插入的数据是有序的，不需要移动，只需要替换，所以可以用二分查找插入的位置，那么插入n个数的时间复杂度为〇(logn)，这样我们会把这个求LIS长度的算法复杂度降为了〇(nlogn)。

如果还有些迷迷糊糊，一起来看代码吧！
```cpp

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int maxn =100010, INF = 0x7f7f7f7f;
int low[maxn], a[maxn];
int n, ans;
 
int binary_search(int *a, int R, int x)
//二分查找，返回a数组中第一个>=x的位置 
{
    int L = 1, mid;
    while(L <= R){
        mid = (L+R) >> 1;
        if(a[mid] <= x)
            L = mid + 1;
        else 
            R = mid - 1;
    }
    return L;
}
 
int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++) 
    {
        scanf("%d", &a[i]); 
        low[i] = INF;   //由于low中存的是最小值，所以low初始化为INF 
    }
    low[1] = a[1]; 
    ans = 1;   //初始时LIS长度为1 
    for(int i=2; i<=n; i++)
    {
        if(a[i] > low[ans])    //若a[i]>=low[ans]，直接把a[i]接到后面 
            low[++ans] = a[i];
        else       //否则，找到low中第一个>=a[i]的位置low[j]，用a[i]更新low[j] 
            low[binary_search(low, ans, a[i])] = a[i];
    }
    printf("%d\n", ans);   //输出答案 
    return 0;
}
```
这其中用到了二分查找第一个大于等于的，其实C++里面的有一个函数可用代替二分，那就是 —— low_bound( )函数。

下面是使用lower_bound优化最长上升子序列。由于长度相同的上升子序列只需要保存结尾最小的那个，而长度递增时，结尾数字的大小也是递增的。最长上升子序列就是找出比他大的第一个数。前面的数都比他小，所以他和这个数的长度相同。然后由于他比较然后小，更新找到的那个值。

```
#include<bits/stdc++.h>
using namespace std;
int n, ans;
int a[200010];
int f[200010]={-0x7f7f7f7f};

int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) {
		int temp=lower_bound(f,f+ans+1,a[i])-f;
		f[temp]=a[i];
		if(ans<temp) ans=temp;
	}
	cout<<ans;
	return 0;
}
  
/*这个算法其实已经不是DP了，有点像贪心。至于复杂度降低其实是因为这个算法里面用到了二分搜索。
本来有N个数要处理是O(n)，每次计算要查找N次还是O(n)，一共就是O(n^2)；
现在搜索换成了O(logn)的二分搜索，总的复杂度就变为O(nlogn)了。
这里主要注意一下lower_bound函数的应用，注意减去的g是地址。
地址 - 地址 = 下标 。*/
```
三、【算法三】 树状数组维护
我们再来回顾O(n^2)DP的状态转移方程：
> F [ i ] = max { F [ j ] + 1 ，F [ i ] }  (1 <= j <  i，A[ j ] < A[ i ])

我们在递推F数组的时候，每次都要把F数组扫一遍求F[ j ]的最大值，时间开销比较大。我们可以借助数据结构来优化这个过程。用树状数组来维护F数组（据说分块也是可以的，但是分块是O(n*sqrt(n)）的时间复杂度，不如树状数组跑得快），首先把A数组从小到大排序，同时把A[ i ]在排序之前的序号记录下来。然后从小到大枚举A[ i ]，每次用编号小于等于A[i]编号的元素的LIS长度+1来更新答案，同时把编号小于等于A[ i ]编号元素的LIS长度+1。因为A数组已经是有序的，所以可以直接更新。有点绕，具体看代码。

**还有一点需要注意：树状数组求LIS不去重的话就变成了最长不下降子序列了。**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
const int maxn =103,INF=0x7f7f7f7f;
struct Node{
    int val,num;
}z[maxn]; 
int T[maxn];
int n;
bool cmp(Node a,Node b)
{
    return a.val==b.val?a.num<b.num:a.val<b.val;
}
void modify(int x,int y)//把val[x]替换为val[x]和y中较大的数 
{
    for(;x<=n;x+=x&(-x)) T[x]=max(T[x],y);
}
int query(int x)//返回val[1]~val[x]中的最大值 
{
    int res=-INF;
    for(;x;x-=x&(-x)) res=max(res,T[x]);
    return res;
}
int main()
{
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&z[i].val);
        z[i].num=i;//记住val[i]的编号，有点类似于离散化的处理，但没有去重 
    }
    sort(z+1,z+n+1,cmp);//以权值为第一关键字从小到大排序 
    for(int i=1;i<=n;i++)//按权值从小到大枚举 
    {
        int maxx=query(z[i].num);//查询编号小于等于num[i]的LIS最大长度
        modify(z[i].num,++maxx);//把长度+1，再去更新前面的LIS长度
        ans=max(ans,maxx);//更新答案
    }
    printf("%d\n",ans);
    return 0;
}
```
**注意，不要复制，我只是让大家看一下思路，提交上去会RE的！！你可以试试看**

好了，讲了这么多，LIS也讲透了，如果喜欢的话点个赞吧！

---

## 作者：哦哟筷子 (赞：5)

## 1.$LIS$

$LIS$ ($Longest$ $Increasing$ $Subsequence)$即是最长上升子序列 ~~意思自己百度~~ 子序列其实是对于给定的一个数列，挑出其中任意个，要求按照在原数列的顺序排列 最长上升就是对于这样一个子序列，要求单调递增，然后最长
~~（怎么感觉在说废话（逃~~

$LIS$在李煜东的《算法竞赛进阶指南》中有概述，然而书中将其称为$DP$的入门题，却在讲解中仅仅提到$O(n^2)$的算法，这样的复杂度是不能被接受的

$O(n^2)$算法：暴力$DP$ 

- 状态定义：$f[i]$ 表示第$i$个数(第$i$个数记为$a_i$)结尾的$LIS$的长度
- 初状态：$f[0] = 0$
- 末状态：$max \{ f[i] \} (1 \le i \le n)$
- 状态转移方程： $f[i] = max \{ f[j]\} +1  (0 \le j < i,a_j < a_i)$

~~（是不是非常好理解呢）~~

初状态是显然的；末状态是任意数都可以作为结尾，只比较长度；转移方程每一个状态是从所有前一个状态中最大值加上$a_i$

~~代码咕咕咕（大雾~~


显然，这样的复杂度是不够优秀的，所以就有了一部分的优化。我们观察状态转移方程，发现需要我们计算前$i - 1$项的最大值，而这可以用一些奇奇怪怪的数据结构来维护，这里就不多介绍了 ~~（我才不会说是我不会）~~

然而事实上还有更优的做法，用二分（$lowerbound$）$+$贪心的做法
显然对于同样位置，结尾数字越小，结果越优。
首先我们维护一个$b$数组，对于每一个$a_i$ 我们判断如果$a_i$大于当前的数组尾端的数，就把$a_i$加到数组末端，如果小于，就用$a_i$替换当前$b$数组中第一个比$a_i$大的数。

这个做法显然如果暴力查找，复杂度仍然是$O(n^2)$ 但是$b$数组是一个单调递增的，我们可以用二分查找或者$STL$库中的$lowerbound$~~(这个同样自行百度233)~~ 复杂度可以降低到$O(nlogn)$

但是如果有兴趣自行举例，可以发现$b$数组中存的并不是我们求的$LIS$,只是可以确保自学列的长度相同
~~（正确性自行证明吧）~~


~~咕咕咕~~的代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int N;
int a[MAXN],b[MAXN];
int p;

int main() {
	scanf("%d",&N);
	for (register int i = 1; i <= N; i++) {
		scanf("%d",&a[i]);
	}
	for (register int i = 1; i <= N; i++) {
		if (a[i] > b[p]) {
			b[++p] = a[i];
		}
		else {
			b[lower_bound(b + 1,b + p + 1,a[i]) - b] = a[i];
		}
	}
	printf("%d",p);
	return 0;
}
```
[例题（模板）](https://www.luogu.org/problem/AT2827)
## 2.$LCS$
~~咕咕咕咕咕咕咕咕咕咕咕~~

$LCS$ ($Longest$ $Common$ $Subsequence$)最长公共子序列，顾名思义，也就是两个序列的最长的公共的子序列 ~~（又是废话（逃））~~

那么让我们再次康一康李煜东《算法竞赛进阶指南》同样是$DP$入门题，但同样只有$O(n^2)$复杂度的算法，实在是让像我这样的$DP$萌新难以接受哇。

暴力$DP$

- 状态定义：$f[i][j]$ 表示$a_1$到$a_i$和$b_1$到$b_j$的$LCS$
- 初状态：$f[i][0]=f[0][j] =0(0 \le i \le |a|,0 \le j \le |b|)$ 其中$|a|,|b|$表示$a,b$数组的长度
- 末状态：$f[|a|][|b|]$
- 状态转移方程：$f[i][j] = max \{ f[i][j - 1],f[i -1][j],f[i-1][j-1] +1(a_i = b_j)\}$

~~同样非常好理解吧$QWQ$~~
注意一下$a_i=b_j$只是第三个选项的条件，其他的真的挺好理解的哇。


正如刚才所说$O(n^2)$的复杂度是不够优秀的，而更优秀的做法就要联系当我们之前所用的$LIS$了
我们举个例子

```
3 1 2 4 5
1 4 5 2 3
```
我们对着上面一行对下面进行离散化（不会的去~~面壁~~百度）
得到
```
2 4 5 3 1
```
也就是每一位存的是第二行这一位在第一行对应的位置，然后我们通过我们某种巧妙的玄学方法看出来，这里相当于求一个$LIS$嘛（这里感性理解一下，~~因为我不会证明，反正$OI$不需要证明~~）
然后我们做一遍$LIS$就做完啦！！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int N;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
int f[MAXN],p = 0;

int main() {
	scanf("%d",&N);
	for (register int i = 1; i <= N; i++) {
		scanf("%d",&a[i]);
	}
	for (register int i = 1; i <= N; i++) {
		scanf("%d",&b[i]);
	}
	for (register int i = 1; i <= N; i++) {
		c[a[i]] = i;
	}
	for (register int i = 1; i <= N; i++) {
		d[i] = c[b[i]];
	}
	for (register int i = 1; i <= N; i++) {
		if (d[i] > f[p]) {
			f[++p] = d[i];
		}
		else{
			f[lower_bound(f + 1,f + p + 1,d[i]) - f] = d[i];
		}
	}
	printf("%d",p);
	return 0;
}

```


[例题模板](https://www.luogu.org/problem/P1439)

完结撒花！！






---

## 作者：___I_AK_IOI (赞：5)

这道题是道LIS的板子题没有什么可多说的，不会LIS的可以看我博客[传送门](https://54520.blog.luogu.org/lis-hu-lcs)后期还会更新，还望大家多多关注咯~~卖萌~~

上AC代码~~由于LIS的知识我都在blog里讲了所以没注释~~
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<cmath>
using namespace std;
const int inf=1000000;
int a[100010],f[100010],c[100010];
int upper_bound(int l,int r,int key)//用STl库也可以哦
{
	while(l!=r)
	{
		int mid=(l+r)>>1;
		if(c[mid]<=key)l=mid+1;
		else r=mid;
	}
	return l;
}
int main()
{
	int n,i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)
		c[i]=inf;
	f[1]=1;
	c[1]=a[1];
	int maxn=0;
	for(i=2;i<=n;i++)
	{
		int u=upper_bound(1,i,a[i]);
		f[i]=u;
		if(c[f[i]]>a[i])c[f[i]]=a[i];
		maxn=max(f[i],maxn);
	}
	cout<<maxn<<endl; 
	return 0;
}
```

---

## 作者：Sparda (赞：4)

一道比较简单的LIS板子题

~~虽然我是在查阅各种资料后写出来的~~

我们可以用一个low数组，记录这个数组到第i位最大的值。

如样例：

5

3 1 5 4 2

记录出来的low数组如下：

1 2

这里的low数组是记录这个数组当前最长上升子序列长度为i时，最小的那个数值。

（仔细理解上面这句话，我思考了半天才写出这句话，~~可能描述有问题嘤嘤嘤~~）

所以，low数组的长度就是整个数组的最长上升子序列

下面附上~~嘤嘤嘤~~代码



```cpp
/*The Bone Of My Sword*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 100005
#define inf 9999999
using namespace std;
int n;
int a[MAXN],b[MAXN];
int low[MAXN];
int find(int r,int x){
    int l = 1;
    while(l <= r){
        int mid = (l+r) >> 1;
        if(low[mid] <= x)
            l = mid+1;
        else
            r = mid-1;
    }
    return l;
}
int main(void){
    cin >> n;
    for(int i = 1;i <= n;i ++)
        scanf("%d",&a[i]),low[i] = inf;
    int k = 1;
    low[1] = a[1];
    for(int i = 2;i <= n;++ i){
        if(a[i] >= low[k])
            low[++k] = a[i];
        else{
            low[find(k,a[i])] = a[i];
        }
    } 
    cout << k << endl;
    /*for(int i = 1;i <= k;i ++)
		cout << low[i] <<" "; */
    return 0;
} 
```

对了，上面用到二分插入替换值。。。。




---

## 作者：zsc2003 (赞：4)

>∵本题的数据范围为1 <= N <= 10^6 

>∴显然不能使用O(N^2)的算法，要使用O(N log N)的算法
 
大家应该都会n log n的lis

但是本人发现没有人手写二分。。。

所以就来一个手写的二分的代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//读入优化
{
    int r=0,s,c;
    for(;!isdigit(c=getchar());s=c);
    for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
    return s^45?r:-r;
}
const int N=110000;
int n,len,l,r,mid;
int a[N],b[N];
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    b[++len]=a[1];
    for(int i=2;i<=n;i++)
    {
        if(a[i]>b[len])
            b[++len]=a[i];
        else
        {
            l=1,r=len;
            while(l<r)
            {
                mid=l+r>>1;
                if(b[mid]<a[i])//二分查找s中大于等于a[i]的最小的数
                    l=mid+1;
                else
                    r=mid;
            }
            b[l]=a[i];
        }
    }
    printf("%d\n",len);
    return 0;
}
```

---

## 作者：WOWHandsome (赞：3)

## **获得更好的阅读体验？前往 [My Blog](https://www.cnblogs.com/baoyihan/p/luogu-at2827.html)**

这道题大家都是用 $O(nlogn)$ 的方法做的，然而题解区好像并没有讲述这个算法是怎么得到的，然后蒟蒻就来讲一下推导过程。

## 尝试一下暴力枚举？

首先很容易想到用二进制暴力来做。每一个元素都用0或1来表示不取或取，再进行一遍验证，最后记录答案。则时间复杂度为 $O(2^n·n)$，显然，美丽的OJ会给你一个无情的TLE。

## O(n^2) 动态规划方法

这里摘自 $Xuanwo$ 的博客。地址：[https://xuanwo.io/2015/07/31/dp-lis/](https://xuanwo.io/2015/07/31/dp-lis/)

$dp[i]$ 表示以 $i$ 结尾的子序列中 $LIS$ 的长度。然后我用   $dp[j] $ $(0<=j<i)$ 来表示在 $i$ 之前的 $LIS$ 的长度。然后我们可以看到，只有当 $a[i]>a[j]$ 的时候，我们需要进行判断，是否将 $a[i]$ 加入到 $dp[j]$ 当中。为了保证我们每次加入都是得到一个最优的 $LIS$ ，有两点需要注意：第一，每一次， $a[i]$ 都应当加入最大的那个 $dp[j]$ ，保证局部性质最优，也就是我们需要找到 $max(dp[j](0<=j<i))$ ；第二，每一次加入之后，我们都应当更新 $dp[j]$ 的值，显然， $dp[i]=dp[j]+1$ 。 如果写成递推公式，我们可以得到 $dp[i]=max(dp[j](0<=j<i))+(a[i]>a[j]?1:0)$ 。 于是我们就能够得到 $O(n^2)$ 的动态规划方法的实现：

```cpp
const int MAXN = 1010;
int n;
int a[MAXN];
int dp[MAXN];

int LIS()
{
    memset(dp, 0, sizeof(dp));
    int Max;
    for (int i = 0; i < n; ++i)
    {
        Max = 0;
        for (int j = 0; j < i; ++j)
        {
            if (a[i] > a[j])
            {
                Max = max(Max, dp[j]);
            }
        }
        dp[i] = Max + 1;
    }
    Max = 0;
    for (int i = 0; i < n; ++i)
    {
        if (dp[i] > Max)    Max = dp[i];
    }
    return Max;
}
```

## 上推导过程

emm我建议你先思考一下啦~

我们在 $O(n^2)$ 的dp算法的基础上优化（拿出我可怜的Excel）

![](https://ae01.alicdn.com/kf/H51bc061ef71748ce9e4648626230da40Y.jpg)

**以上，CORE IDEA，建议大图消化！**

**建议，在纸上一步步模拟s的值，深入理解这个算法的精髓所在！！！否则，你也不会写出代码、理解代码**

## 最后是可爱的代码

这里给出核心代码。

```cpp
    tot = 0;
    s[++tot] = a[1]; //边界条件，a[1]肯定能构成长度为1的LIS，所以存入s[1]。
    for (int i = 2; i <= n; i++) {
        if (a[i] <= s[tot])  //如果a[i]小于s的最后一个值，那么说明a[i]可以替换掉s数组的某一个值
            *lower_bound(s + 1, s + 1 + tot, a[i]) = a[i]; //指针写法，替换s[i]，lower_bound 是 STL 的二分查找函数，不懂的可以 Google 搜索一下。
        else s[++tot] = a[i]; //否则，tot++，将a[i]写入
    }
```

最后的ans自然是tot。

**一定要模拟！模拟！模拟！动态规划的精髓就是填表，在纸上模拟过了，才有信心一遍写出 AC 代码！**

---

## 作者：维迭生 (赞：3)

树状数组。   
　虽然很多大佬也用树状数组，但不知是不是我太菜，看不懂他们的题解，所以我决定解释得详细一点。  
　　//做完这道题就可以去做导弹拦截了。  
假设给的数字代表高度，我们就是要往上爬最长的格子。  
我们用下标表示高度，f(i)表示不超过高度i的LIS。  
我先上代码，下面解释：（为防止抄袭，也为确保你能更好地理解LIS，我放的是导弹拦截第一问的代码）
```
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int MAXH = 100000;
const int MAXN = 1e5 + 5;
int f[MAXH], l[MAXN], maxh, ans;
int n;

inline int max(int a,int b){
    if(a>b) return a;
    return b;
}

inline int lowbit (int k){
    return ((k)&(-k));
}

inline void add(int x, int newh){			//以p修改、维护数组 
    for (int i = x; i <= maxh; i +=lowbit(i) ){
        f[i] = max(f[i],newh);
    }
    return ;
}

inline int ask (int x){				//查最长 
    int ret = 0;
    for (int i = x; i >= 1; i -= lowbit(i) ){
        ret = max(ret, f[i]);	//记得求区间和的树状数组吗？
    }
    return ret;
}

inline int quest(int x)
{
    int r=0;
    for(int i=x;i<=maxh;i+=lowbit(i))
        r=max(r,f[i]);			//这里只是把+= 换成了 max()而已
    return r;
}
inline void push(int x,int v)
{
    for(int i=x;i>0;i-=lowbit(i))
        f[i]=max(f[i],v);
}

int main(){	
    cin >> n;
    
    for(int i = 1; i <= n; ++i){
        cin >> l[i];
        maxh = max(maxh, l[i]);
    }
//	for(int i=1;i<=n;i++)
//    {
//        int x=quest(l[i])+1;
//        ans=max(ans,x);
//        push(l[i],x);
//    }
//	
//	cout << ans <<endl;
//	memset ( f, 0 , sizeof(f));	
//	ans = 0;
    
    for(int i = 1; i <= n; ++ i){
        int x = ask(l[i]) + 1;	//找出当前LIS
        ans = max(ans, x);
        add(l[i] + 1, x); 	//严格上升，所以加一
    }
    
    cout << ans <<endl;

    return 0;
}
```

---

## 作者：RoRoyyy (赞：2)

这题原来一直用的~~线段树~~， 原因是我不会树状数组求最值， 我也不会二分解这道题...

```cpp
//RoRoyyy
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
const int N = 1e5 + 5;
int n = 0;
int a[N];
struct smt {
    int l, r, maxn;
    #define ls p << 1
    #define rs p << 1 | 1
}t[N << 2];
void pushup(int p) {
    t[p].maxn = max(t[ls].maxn, t[rs].maxn);
}
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if(l == r) {t[p].maxn = 0; return;}
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(p);
}
void add(int p, int pos, int k) {
    if(t[p].l == t[p].r) {t[p].maxn = k; return;}
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) add(ls, pos, k);
    else add(rs, pos, k);
    pushup(p);
}
int ask(int p, int l, int r) {
    if(t[p].l >= l && t[p].r <= r) return t[p].maxn;
    int mid  = t[p].l + t[p].r >> 1;
    int val = 0;
    if(l <= mid) val = max(val, ask(ls, l, r));
    if(r > mid) val = max(val, ask(rs, l, r));
    return val; 
}
int main() {
    while(scanf("%d", &a[++n]) != EOF);
    n--;
    build(1, 1, N);
    int ans1 = 0, ans2 = 0;
    for(int i = 1; i <= n; i++) {//最长不上升子序列 需要找i之前大于等于a[i] 的dp的最大值
        int tep = ask(1, a[i], N) + 1;
        add(1, a[i], tep);
        ans1 = max(ans1, tep);
    }
    build(1, 1, N);
    for(int i = 1; i <= n; i++) {//最长上升子序列 需要找i之前小于a[i]的dp的最大值
        int tep = ask(1, 1, a[i] - 1) + 1;
        add(1, a[i], tep);
        ans2 = max(ans2, tep);
    }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}
```

这里把两种序列的线段树代码都集合了。


这次我学习了一下二分怎么优化这道题。

首先我们可以证明：对于原序列两个数$a[i],a[j]$ ,$dp[i] == dp[j]$，即结尾的答案相等， 而且$a[i] > a[j]$， 那么这时候选$i$一定不会比选$j$更优。（这个是显然的
那么我们设$s[i]$表示以$i$作为答案的最小结尾。

那么根据上面的证明， 我们知道$s[i]$一定是单调递增的， 而且可以按照如下来递推：

如果$a[i]$大于$s[tot]$， 那么显然此时$a[i]$会使答案增加， 同时我们已经保证$s[tot]$是到目前为止答案为$tot$的最小结尾， 而且我们当前的$a[i]$也只能接$i$之前的数， 所以我们就更新当前答案。

如果小于了， 就不能更新答案了， 但我们为了维护最优性质， 我们需要在$s$序列查询大于$a[i]$的最小数， 替换就行了， 因为如果大于$a[i]$的最小数$a[k]$能满足当前答案， 而且$a[k]$的答案一定在$k$之前就计算完毕， 不需要用到$k$之后的数了， 所以我用$i$去替换也一定能保证此时的答案和$k$是一样的， 因为$k-1$的数一定小于$i$的数。
因为$s$是有序的， 那么二分查找就可以了。


```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e5 + 5;
int a[N], tot = 0, s[N];//栈中存放的是以i为答案的最小数是多少 
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    s[++tot] = a[1];
    for(int i = 2; i <= n; i++) {
        if(a[i] > s[tot]) s[++tot] = a[i];//如果答案能继续往上累加，就累加
        else {
            //此处查找大于a[i]的最小数的下标即答案 用更优的选项替换原来较大的数
            int tep = lower_bound(s + 1, s + 1 + tot, a[i]) -  s;
            s[tep] = a[i];
        }
    }
    printf("%d\n", tot);
    return 0;
}
```



---

## 作者：Capitalism_Gao (赞：2)

## 前言：这是道LIS模板题，这里介绍O(NlogN)算法
### 一.算法思想
**我们开一个ans[]数组，ans[i]表示长度为i的LIS中的最小末尾,用一个变量len来记录现在LIS的最长长度**

下面我们看一组样例：

a[8]=1,9,2,6,0,8,1,7

1. 处理a[1]，令ans[1]=a[1]=1,就是说当只有a[1]这个数字1的时候，长度为1的LIS的最小末尾是1,这时len=1;
         
      ans[1]=1; len=1;
2. 处理a[2]，因a[2]>ans[len=1],则ans[++len]=ans[2]=9;

      ans[1,2]=1,9; len=2;
3. 处理a[3]，ans[1]<a[3]=2<ans[2]。
   
      - 现在我们想一下ans[1]表示的是LIS长度为1的最小末尾是1，而a[3]=2>1,故不能用a[3]刷新ans[1]。     
     - 那么何时才能用a[3]去刷新ans[]呢
     - 答案是：**在ans[]中找到第一个>=a[3]的数ans[pos]，因ans[pos]>a[3]并且a[3]>ans[1~pos-1]**,则此时长度为pos的LIS最小结尾应该是min(ans[pos],a[3])=a[3];
     
      ans[1,2]=1,2; len=2;   
4. 处理a[4],因a[4]=6>ans[len=2],则ans[++len]=ans[3]=6;
    
      ans[1,2,3]=1,2,6; len=3;
5. 处理a[5]，在ans中找第一个>=a[5]的数ans[1],所以ans[1]=a[5]=0;
    
      ans[1,2,3]=0,2,6; len=3;
6. 处理a[6]，因a[6]=8>ans[len=3]=6,所以ans[++len]=a[6]=8;

      ans[1,2,3,4]=0,2,6,8; len=4;
7. 处理a[7]，在ans中找第一个>=a[7]的数ans[2],所以ans[2]=a[7]=1;

      ans[1,2,3,4]=0,1,6,8; len=4;
8. 处理a[8], 在ans中找第一个>=a[8]的数ans[4],所以ans[4]=a[7]=1;
    
      ans[1,2,3,4]=0,1,6,7; len=4;

最后输出len即可。     
在此过程中ans一直是有序的(从定义也可推知)，所以单次查找可选用二分，或STL里的lower_bound(),将时间复杂度降为O(logN),所以总时间复杂度为O(NlogN)。

### 二.分享源码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6;
int n,a[maxn],ans[maxn],len;

int lbound(int x[],int lenx,int goal){
	int l=1,r=lenx;
	while(l<r){
		int mid=(l+r)>>1;
		if(x[mid]>=goal) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	ans[len=1]=a[1];
	for(int i=2;i<=n;i++){
		if(a[i]>ans[len]) ans[++len]=a[i];
		else {
			int pos=lbound(ans,len,a[i]);
			ans[pos]=a[i];
		} 
	}
	printf("%d",len);
	
	return 0;
} 
```

      





---

## 作者：peterwuyihong (赞：2)

## 这道题正解是$DP$，思路是贪心
新建一个序列，每次读入一个数，大于序列顶则加入序列，小于则在序列中找到一个比自己小的数，由于序列肯定是有序的，那么替换的复杂度就是$ \log(n) $，我们可以用$ lover \_bound() \ STL$，这样就方便了后面的数进来。答案就是序列的长度。
### 真正的贪心是有$ \log $的，贴上14行代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,f[100010],cnt;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&x);
    	if(x>f[cnt])f[++cnt]=x;
    	else *lower_bound(f+1,f+cnt+1,x)=x;
	}
	printf("%d",cnt);
}
```


---

## 作者：lukzia (赞：1)

# 题目大意

## 【题目描述】
一个数的序列bi，当b1<b2<...<bS的时候，我们称这个序列是上升的。对于给定的一个序列(a1,a2,...,aN)，我们可以得到一些上升的子序列(ai1,ai2,...,aiK)，这里1≤i1<i2<...<iK≤N。比如，对于序列(1,7,3,5,9,4,8)，有它的一些上升子序列，如(1,7),(3,4,8)等等。这些子序列中最长的长度是4，比如子序列(1,3,5,8)。

你的任务，就是对于给定的序列，求出最长上升子序列的长度。

## 【输入】
输入的第一行是序列的长度N(1≤N≤1000)。第二行给出序列中的N个整数，这些整数的取值范围都在0到10000。

## 【输出】
最长上升子序列的长度。



# 思考

我们的目标是求出最长的不连续的上升数列,那么我们开一个数组f[i],存以i结尾的数列长度;

那么,对于每一个数i,我们从她前面找一个比她小的数字j,判断和她连接后长度是否比当前长度长,是的话则替换fi的值.

方程式大致如下

fi = max(fj+1,fi) | fi > fj

# code （TLE 15个点）

```cpp

#include <iostream>
#include <algorithm>
#define maxn 100005
using namespace std;

int n, a[maxn] = {};

int f[maxn] = {};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        f[i] = 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j])
            {
                f[i] = max(f[j] + 1, f[i]);
            }
        }
    cout << *std::max_element(f + 1, f + n + 1) << endl;
    return 0;
}


```

# 优化

LIS其实可以优化到O(nlogn)

有这么一个串：

3 1 5 2 7 6

我们考虑开一个数组记录最长子串而不是记录以i结尾的串长度。

```cpp
for (register int i = 1; i <= n; i++)
{
    if(....)
        .....
    else
        .....
}
```

我们每添加一个数，比较他与我们记录最长子串的数组最后一个数大还是小，如果大就直接加入数组末尾。

```cpp
for (register int i = 1; i <= n; i++)
{
    if(a[i] > s[len])
        s[++len] = a[i];
    else
        .....
}
```

不然我们就二分找一个比a[i]大的最小元素，然后替换，如果它不会更新答案，那么它也就不会更新到末尾，也就不会影响答案。还有我们求的是长度，和里面的元素无关。

```cpp
int lower_bound(int x)
{
    int l = 1, r = len;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (s[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

for (register int i = 1; i <= n; i++)
{
    if(a[i] > s[len])
        s[++len] = a[i];
    else
        s[lower_bound(a[i])] = a[i];
}

cout << len;
```

# AC代码

```cpp
#include <iostream>

using namespace std;

const int maxn = 100005;
int n, a[maxn], f[maxn], s[maxn], len;

int lower_bound(int x)
{
    int l = 1, r = len;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (s[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (register int i = 1; i <= n; i++)
        cin >> a[i];

    for (register int i = 1; i <= n; i++)
    {
        if (s[len] < a[i])
            s[++len] = a[i];
        else
            s[lower_bound(a[i])] = a[i];
    }
    cout << len << endl;
    return 0;
}
```

---

## 作者：BeyondStars (赞：1)

那么多大佬都是单调栈+二分或者树状数组，而本蒟蒻太菜了，只会写权值线段树了Orz。关于权值线段树，就是把所有的数全部离散化，然后决策完成以后，就把当前点的值加入到线段树里面去。这样线段树里面的值一定都是当前出现过的点。
代码很丑：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int MAXN = (int)1e5+10;
int dp[MAXN],a[MAXN];
deque<int> q;
struct SGT {
	struct node {
		int mx;
	} tree[MAXN<<2];
	void pushup(int k) {
		tree[k].mx = max(tree[k<<1].mx,tree[k<<1|1].mx);
	}
	int query(int k,int l,int r,int x,int y) {
		if(l>=x&&r<=y)return tree[k].mx;
		int mid = l+r>>1,ret = 0;
		if(x<=mid)ret = query(k<<1,l,mid,x,y);
		if(y>mid)ret = max(ret,query(k<<1|1,mid+1,r,x,y));
		return ret;
	}
	void modify(int k,int l,int r,int pos,int v) {
		if(l==r) {
			tree[k].mx = v;
			return;
		}
		int mid = l+r>>1;
		if(pos<=mid)modify(k<<1,l,mid,pos,v);
		else modify(k<<1|1,mid+1,r,pos,v);
		pushup(k);
	}
}T;
int HASH[MAXN];
int len;
inline int getid(int x){return lower_bound(HASH+1,HASH+len+1,x)-HASH;}
int main() {
	int n;
	scanf("%d",&n);
	for(int i = 1; i<=n; i++)scanf("%d",&a[i]);
	int tot = n;
	for(int i = 1;i<=tot;i++)HASH[i] = a[i];
	sort(HASH+1,HASH+n+1);
	len = unique(HASH+1,HASH+1+n)-HASH;
	dp[1] = 1;
	T.modify(1,1,n,getid(a[1]),1);
	for(int i = 2; i<=tot; i++) {
		int id = getid(a[i]);
		if(id==1) {
			dp[i] = 1;
			T.modify(1,1,n,id,1);
			continue;
		}
		dp[i] = T.query(1,1,n,1,id-1)+1;
		T.modify(1,1,n,id,dp[i]);
	}
	int ans = 0;
	for(int i = 1; i<=tot; i++) {
		ans = max(ans,dp[i]);
	}
	printf("%d",ans);
	return 0;
}
```
~~还有就是众所周知，线段树的复杂度是$O(nlog^2n)$，其中$O(nlogn)$是渐进复杂度，$O(logn)$是这玩意天生的常数~~

---

## 作者：Corrine (赞：1)

这是一道较简单的LIS的题，求的就是最长上升子序列。~~（虽然我用了很久才写粗来）~~

本题有三种解法）：DP，离散化+树状数组，离散化+线段树 ，下面我一一为您讲解。

## **DP大法（AC四个点）：**
首先，这是一道求最长上升子序列的题（zzj大佬：废话！）所以，很容易想到用DP来做。我们可以设f[i]为以a[i]为结尾的最长上升子序列的长度，很容易就列出：
f[i]=max(f[j]+1,f[i])**（当a[i]>a[j]时)**否则f[i]=1

上代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n;
int a[100010],f[100010];//a[i]是
int main()
{
	memset(f,0,sizeof(f));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	f[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
			if(a[i]>a[j])f[i]=max(f[j]+1,f[i]);
		if(!f[i])f[i]=1;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,f[i]);
	 } 
	 printf("%d",ans);
} 
```
## **离散化+树状数组**
相信很多小伙伴们都听过离散化这一高（di）端（ji）的词汇，那这到底指什么呢？

离散化本质上可以看成是一种哈希，其保证数据在哈希以后仍然保持原来的全/偏序关系。

通俗地讲就是当有些数据因为本身很大或者类型不支持，自身无法作为数组的下标来方便地处理，而影响最终结果的只有元素之间的相对大小关系时，我们可以将原来的数据按照从大到小编号来处理问题，即离散化。

用来离散化的可以是大整数、浮点数、字符串……等等。

无（du）良（liu）的数据告诉我们：这柠（ti）檬（mu）要用离散化！
首先，开一个结构体：
```cpp
	struct nod1{int x,t;}a[100010];
```
其中，a[i].x存输入，a[i].t表示这个数是在那一个位置。
输入完了以后，sort一下（注意：从小到大排）
```cpp
bool cmp(nod1 x,nod1 y)
{
	return x.x<y.x;
}
sort(a+1,a+1+n,cmp);
```
再开一个数组b[i],用来存离散化以后的数组。
于是
```cpp
   int h=1;//自行理解一下，不然就废了
	for(int i=1;i<=n;i++)
	{
        if(a[i].x!=a[i-1].x&&i!=1)h++;
		b[a[i].t]=h;
	}
```
随后，就可以用树状数组做啦！（[不会树状数组的，出门左转](https://www.luogu.org/problem/P3374)）
树状数组核心代码：
```cpp
int lowbit(int k)
{
    return k & (-k);
}
void add(int x,int k)
{
    while(x<=n){tree[x]=max(k,tree[x]);x+=lowbit(x);}
    return ;
}

int sum(int x)
{
    int ans=0;
    while(x)
    {
        ans=max(tree[x],ans);//注意，这个tree数组存的就是以a[i]为结尾的最长上升子序列的长度，所以要求max
        x-=lowbit(x);
    }
    return ans;
}
```
上代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct nod1{int x,t;}a[100010];
bool cmp(nod1 x,nod1 y)
{
	return x.x<y.x;
}
int n,m,tree[2000010]//树状数组;
int b[100010];  
int lowbit(int k)
{
    return k & (-k);
}
void add(int x,int k)
{
    while(x<=n){tree[x]=max(k,tree[x]);x+=lowbit(x);}
    return ;
}
int sum(int x)
{
    int ans=0;
    while(x)
    {
        ans=max(tree[x],ans);
        x-=lowbit(x);
    }
    return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].x);
		a[i].t=i;
	}
	sort(a+1,a+1+n,cmp);
    int h=1;
	for(int i=1;i<=n;i++)
	{
        if(a[i].x!=a[i-1].x&&i!=1)h++;
		b[a[i].t]=h;
	}
	for(int i=1;i<=n;i++)
	{
		int t=sum(b[i]-1)+1;//求出前一个f[i]的最大值，再加上自己
		add(b[i],t);//加入树状数组中
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,tree[i]);
	}
	printf("%d",ans);
	return 0;
}
```
## **线段树+离散化**
当我还是六年级时，我坐在师兄们的中间，听他们讲解线段树，当然，我啥也没听懂。

现在，我知道这是什么东西了，就是在这个东西上进行删改和询问（很经典的一个二分）![选自luogu日报第46期](https://cdn.luogu.com.cn/upload/pic/65968.png)
就是不停的二分，二分，再二分！！！！(如不懂，出门右转），随后，思路和树状数组一样，就不细说了。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
struct nod2{int v,t;}b[1000010];
int c[1000010];
struct nod1{int l,r,ls,rs,c=0;}a[1000010];
int len,n,m;
bool cmp(nod2 x,nod2 y)
{
	return x.v<y.v;
}
void bt(int l,int r)
{
	len++;int x=len;
	a[x].l=l;a[x].r=r;
	int m=(r+l)/2;
	if(l!=r)
	{
		a[x].ls=len+1;bt(l,m);
		a[x].rs=len+1;bt(m+1,r);
	}
}
void change(int x,int k,int c)
{
	a[x].c=max(a[x].c,c);
	if(a[x].l==a[x].r&&a[x].l==k)return ;
	int m=(a[x].l+a[x].r)/2;
	if(k<=m)change(a[x].ls,k,c);
	else change(a[x].rs,k,c);
}
int find1(int x,int l,int r)
{
	if(l>r)return 0;
	if(a[x].l==l&&a[x].r==r)return a[x].c;
	int m=(a[x].l+a[x].r)/2;
	if(l>m)return find1(a[x].rs,l,r);
	else if(r<=m)return find1(a[x].ls,l,r);
	else return max(find1(a[x].ls,l,m),find1(a[x].rs,m+1,r));
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%lld",&n);
	bt(1,n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i].v);
		b[i].t=i; 
		//change(1,i,x);
	}
	sort(b+1,b+n+1,cmp);
	int h=0;
	for(int i=1;i<=n;i++)
	{
		if(b[i].v!=b[i-1].v)h++;
		c[b[i].t]=h;
	}
	for(int i=1;i<=n;i++)
	{
		int t=find1(1,1,c[i]-1)+1;
		change(1,c[i],t);
	}
	printf("%lld",find1(1,1,n));
}
```


---

## 作者：MSM2004 (赞：1)

优化算法：用的是贪心策略
       数组up[i]的意义是， up[i]中保存的是长度为i的上升子序列中结束元素最小的那个元素的值，比如长度为3的上升子序列有2个，一个最后一个元素为800，另一个最后一个元素为799，那么up[3]=799。up[i]中的元素都尽可能的小，这样才有潜力接上更多大的数。
      贪心策略：我们总是希望新的元素能加入到长度最长且最后一个元素最小的序列中，这样构成的上升序列才会更有“潜力”接上更多的元素。
       up[ ]数组的长度为所求
   ```c
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010],up[100010];
int main()
{
	int m;
	cin>>m;
	for(int i=1;i<=m;i++)
	cin>>a[i];
	up[1]=a[1];
	int ans=1;
	for(int i=2;i<=m;i++)
	{
		int pos=lower_bound(up+1,up+ans+1,a[i])-(up+1)+1;//lower_bound() 返回一个迭代器，指向键值<= a[i]的第一个元素
		up[pos]=a[i];
		ans=max(ans,pos);
	}
	cout<<ans;
	return 0;
}

```   


---

## 作者：__DICS (赞：0)

正在补cf gym 101915的I，发现要用树状数组求LIS，然而本菜鸡树状数组学得一塌糊涂，LIS也只写过$\mathcal{O}(n^2)$的标准dp解...本着一步步踏实前进的原则，还是先来把这题过了再去切那题。

翻了一圈题解貌似没有人拿非递归线段树过，就贴一下自己写的版本:

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct SegmentTree {
    vector<int> tree;
    int len;

    explicit SegmentTree(): len(0) {}

    void pushup(int i) {
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void build(int n) {
        len = n;
        tree.assign(len << 1, 0);
        for (int i = len - 1; i; --i) pushup(i);
    }
    
    void update(int pos, int val) {
        for (pos += len - 1; pos; pos >>= 1) tree[pos] = max(tree[pos], val);
    }

    int query(int l, int r) const {
        int ans = 0;
        for (l += len - 1, r += len; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = max(tree[l++], ans);
            if (r & 1) ans = max(tree[--r], ans);
        }
        return ans;
    }

    void debug() const {
        for (auto it : tree) printf("%d ", it);
        putchar('\n');
    }
};

int main() {
    int n, temp, res;
    int ans = 0;
    SegmentTree st;
    scanf("%d", &n);
    st.build(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &temp);
        res = st.query(1, temp - 1) + 1;
        st.update(temp, res);
        ans = max(ans, res);
        // st.debug();
    }
    printf("%d\n", ans);
    return 0;
}
```

取消`st.debug()`的注释，输入`5 1 2 3 4 5`可以获得以下输出:

```
5
1 4 2 3 5
0 1 1 0 0 1 0 0 0 0
0 2 2 0 2 1 0 0 2 0
0 2 2 2 2 1 2 0 2 0
0 3 2 3 2 1 2 3 2 0
0 4 4 3 4 1 2 3 2 4
4
```

由于非递归线段树的实现一共需要原数组的两倍大小的内存空间，所以最后n位其实就是原数组的变化过程。

具体思想的话题解里面其他老哥已经写的很明白了，其实我上面用的样例也是某个老哥用来举例的例子，这样可能看起来更好理解一点。

也算是除去`lower_bound`的另一种$\mathcal{O}(n\log n)$的实现方法了，唯一的缺点可能就是有时需要离散化。

---

## 作者：JackcreaM (赞：0)

### LIS（Longest Increasing Subsequence）最长上升子序列 或者 最长不下降子序列。
#### 很基础的题目，有两种算法，复杂度分别为O(n*logn)和O(n^2) 。

#### 安利原地址[https://blog.csdn.net/zhangyx_xyz/article/details/50949957](https://blog.csdn.net/zhangyx_xyz/article/details/50949957)


先回顾经典的


O(n^2)
的动态规划算法:

设a[t]表示序列中的第t个数，dp[t]表示从1到t这一段中以t结尾的最长上升子序列的长度，初始时设dp[t] = 0(t = 1, 2, ..., len(A))。则有动态规划方程：dp[t] = max{1, dp[j] + 1} (j = 1, 2, ..., t - 1, 且a[j] < a[t])。

一般若从a[t]开始，此时最长不下降子序列应该是按下列方法求出的： 在a[t+1],a[t+2],...a[n]中，找出一个比a[t]大的且最长的不下降子序列，作为它的后继。

代码实现如下：
```

#include<iostream>
using namespace std;
#define max(a,b) a>b?a:b
int main()
{
    int n, i, j, dp[101], x[101], max_len;
    while (cin >> n)
    {
        for (i = 0; i < n; i++)
            cin >> x[i];
        dp[0] = 1;//表示以x[0]为子序列最右边的长度位1
        for (i = 1; i < n; i++)
        {
            dp[i] = 1;//初始化每种情况最小值为1
            for (j = 0; j < i; j++)
            {
                if (x[i]>x[j] && dp[j] + 1>dp[i])//从0-i进行扫描,查找边界小于当前最优解长度相等的解优化最优解
                    dp[i] = dp[j] + 1;//如果允许子序列相邻元素相同  x[i]>=x[j]&&dp[j]+1>dp[i];
            }
        }
        for (i = max_len = 0; i < n; i++)
            max_len = max(max_len, dp[i]);//等到最大子序列长度
        cout << max_len << endl;
    }
    return 0;
}
```
最长上升子序列

O(nlogn)
解法

在一列数中寻找一些数，这些数满足：任意两个数a[i]和a[j]，若i<j，必有a[i]<a[j]，这样最长的子序列称为最长递增子序列。

设dp[i]表示以i为结尾的最长递增子序列的长度，则状态转移方程为：

dp[i] = max{dp[j]+1}, 1<=j<i,a[j]<a[i].

考虑两个数a[x]和a[y]，x<y且a[x]<a[y],且dp[x]=dp[y]，当a[t]要选择时，到底取哪一个构成最优的呢？显然选取a[x]更有潜力，因为可能存在a[x]<a[z]<a[y]，这样a[t]可以获得更优的值。在这里给我们一个启示，当dp[t]一样时，尽量选择更小的a[x].

按dp[t]=k来分类，只需保留dp[t]=k的所有a[t]中的最小值，设g[k]记录这个值，g[k]=min{a[t],dp[t]=k}。

这时注意到g的两个特点（重点）：

g[k]在计算过程中单调不升；

g数组是有序的，g[1]<g[2]<..g[n]。

利用这两个性质，可以很方便的求解：

(1).设当前已求出的最长上升子序列的长度为len（初始时为1），每次读入一个新元素x：

(2).若x>g[len]，则直接加入到d的末尾，且len++；（利用性质2）

否则，在g中二分查找，找到第一个比x小的数g[k]，并g[k+1]=x，在这里x<=g[k+1]一定成立（性质1,2）。

代码实现如下：
```
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 50001;
int binary_search(int key, int *g, int low, int high)
{
    while (low < high)
    {
        int mid = (low + high) >> 1;
        if (key >= g[mid])
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
int main()
{
    int i, j, a[maxn], g[maxn], n, len;
    while (cin >> n)
    {
        memset(g, 0, sizeof(g));
        for (i = 0; i < n; i++)
            cin >> a[i];
        g[1] = a[0], len = 1;//初始化子序列长度为1，最小右边界
        for (i = 1; i < n; i++)
        {
            if (g[len] < a[i])//(如果允许子序列相邻元素相同 g[len]<=a[i],默认为不等）
                j = ++len; //a[i]>g[len],直接加入到g的末尾,且len++
            else
                j = binary_search(a[i], g, 1, len + 1);
            g[j] = a[i];//二分查找,找到第一个比a[i]小的数g[k],并g[k+1]=a[i]
        }
        cout << len << endl;
    }
    return 0;
}
  ```
例题[https://www.luogu.org/problemnew/show/P1108](https://www.luogu.org/problemnew/show/P1108)

---

