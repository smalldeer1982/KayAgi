# Social Circles

## 题目描述

You invited $ n $ guests to dinner! You plan to arrange one or more circles of chairs. Each chair is going to be either occupied by one guest, or be empty. You can make any number of circles.

Your guests happen to be a little bit shy, so the $ i $ -th guest wants to have a least $ l_i $ free chairs to the left of his chair, and at least $ r_i $ free chairs to the right. The "left" and "right" directions are chosen assuming all guests are going to be seated towards the center of the circle. Note that when a guest is the only one in his circle, the $ l_i $ chairs to his left and $ r_i $ chairs to his right may overlap.

What is smallest total number of chairs you have to use?

## 说明/提示

In the second sample the only optimal answer is to use two circles: a circle with $ 5 $ chairs accomodating guests $ 1 $ and $ 2 $ , and another one with $ 10 $ chairs accomodationg guests $ 3 $ and $ 4 $ .

In the third sample, you have only one circle with one person. The guest should have at least five free chairs to his left, and at least six free chairs to his right to the next person, which is in this case the guest herself. So, overall number of chairs should be at least 6+1=7.

## 样例 #1

### 输入

```
3
1 1
1 1
1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
1 2
2 1
3 5
5 3
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
5 6
```

### 输出

```
7
```

# 题解

## 作者：Itst (赞：5)

### [传送门](http://codeforces.com/problemset/problem/1060/D)
### 没有很好想，但也不难。
### 考虑什么样的人会坐在相邻位置，一定是一个人的左手与另一个人的右手相差较小时较好，因为这样子重复利用的椅子数量更多。那么我们可以由此获得贪心策略：对左手与右手分别排序，然后求$\sum\limits_{i=1}^n max(l_i,r_i)$即可

```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;

int numL[MAXN] , numR[MAXN];

int main(){
	int N;
	cin >> N;
	for(int i = 1 ; i <= N ; i++)
		cin >> numL[i] >> numR[i];
	sort(numL + 1 , numL + N + 1);
	sort(numR + 1 , numR + N + 1);
	long long ans = N;
	for(int i = 1 ; i <= N ; i++)
		ans += max(numL[i] , numR[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：king_xbz (赞：2)

一道还不错的CF的思维题。

将大问题分解成几个子问题是惯用的解题思维。这道题也一样。

设$l[i],r[i]$分别是$i$左右的空椅子

我们思考在什么时候椅子可以公用？对于两个人$i,j$那很显然是在$l[i]=r[j],l[j]=r[i]$的时候.

此时我们只需要$l[i]+r[i]$个椅子。

我们接着思考，什么时候椅子可以重复用？根据样例三，我们可以得知，对于只有一个人时，$ans=max(l[i],r[i])+1$。

转化一下，其实在公用时的答案$l[i]+r[i]$不也正是满足这一条件吗？

这样我们就将全局的问题转化为二元组的问题了

那我们就得到柿子，也就是

$tot=\large min(\{\sum_{i=1,j=1}^nmax(l[i],r[j])\})$

换句话说，我们需要求n对二元组的和最小，其中二元组就是$max(l[i],r[j])$

这样做的复杂度是$O(n^2)$的，显然过不了。

那么我们贪心的去想：

要使满足条件的二元组的和最小，一定就是使每对二元组的$max$值尽量小。

不难想到，我们使用快速排序，然后相对应$l[i],r[i]$的最大值即满足条件。

这样二元组的问题就被解决了。

最后的答案就是$tot+n$(自己也要坐椅子的嘛！)

代码：

```cpp
signed main()
{
	int n;
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>l[i]>>r[i];
	int bas=n;//初始至少有n把椅子
	sort(l+1,l+n+1);
	sort(r+1,r+n+1);
	int ans=0;
	for(fint i=1;i<=n;i++)
	ans+=max(l[i],r[i]);
	cout<<ans+bas;
	return 0;
}
```



---

## 作者：chufuzhe (赞：2)

只要看出这道题是贪心，就很好做了。

当每加入一个人时，有两种选择，要么新构成一个圈，要么利用之前已有的空位。

因为椅子的数量与 $max(l_i,r_i)$ 有关，所以椅子的数量要最少，只需要让 $max(l_i,r_i)$ 的值最小。

因此我们可以将 $l$ 、 $r$ 从小到大排序，每次增加 $max(l_i,r_i)+1$ 就可以了。 $+1$ 是因为客人也要坐一个椅子。

要注意，因为 $l_i$ 、 $r_i$ 的最大值为 $10 ^ 9$ ， $n$ 的最大值为 $10 ^ 5$，答案的最大值就会到 $10 ^ {14}$，显然 $int$ 不够， 要用 $long$ $long$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005]; //定义，a表示l，b表示r
int b[100005];
int main()
{
	ios::sync_with_stdio(false);
	long long ans = 0; //注意用long long
	int n;
	cin >> n; //输入
	for(int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	sort(a + 1, a + n + 1); //排序
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++) //计算
		ans += max(a[i], b[i]) + 1; //注意要+1
	cout << ans << endl; //输出
	return 0;
}
```


---

## 作者：Mine_King (赞：2)

这题很容易想到如果让两个很大的 $l$ 和 $r$ 放在一起就能尽量减少椅子的数量，再仔细想，发现每次把最大的两个 $l$ 和 $r$ 都放在一起即可。  
那如果这两个最大的 $l$ 和 $r$ 都源自同一人呢？那么我们只要让这个人单独坐一圈就行了。  
感性理解一下，可以发现这个贪心是正确的。  

至于实现方法，就是将数组排序，结果为 $\sum\limits_{i=1}^n max(a_i,b_i) + n$  
**code:**
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
long long ans;//记得开ll
int l[100005],r[100005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&l[i],&r[i]);
	sort(l+1,l+n+1);
	sort(r+1,r+n+1);
    //因为要让当前最大和最大抵消，所以要排序
	for(int i=1;i<=n;i++) ans+=max(l[i],r[i]);//可以发现升序和降序排序都是一样的。
	printf("%lld\n",ans+n);
	return 0;
}
```

---

## 作者：mzyc_jx (赞：1)

[Social Circles](https://www.luogu.com.cn/problem/CF1060D)

这是一道非常水的贪心题。

### 思路：
1. 题目要求椅子数最少，就要使两人之间公用的椅子最多。

2. 因为可以自由安排座位,所以就只需要把 $l$ 和 $r$ 排序来找。

3. 因此只需要找排序后的 $l_i$ 和 $r_i$，取 $\max(l_i,r_i)$ 累加。

---

### 注意：
1. $ans$ 还要累加上他们自己坐的椅子数。

2. $ans$ 记得开 $long long$ ！

---

### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int l[100005],r[100005];
int main()
{
	long long n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>l[i]>>r[i];
	sort(l+1,l+n+1);
	sort(r+1,r+n+1);
	for(int i=1;i<=n;i++)
	ans+=max(l[i],r[i]);
	ans+=n;
	cout<<ans;
	return 0;
}
```

---

## 作者：_stellar (赞：1)

[$\texttt{Blog}$](https://yosowang.blog.luogu.org/#)

### 关于如何划分圈，可以那么理解：

对于一个准备加入圈内的人$i$，如果$R_i$和$L_i$**严格包含于之前的人的值域内**，那么他完全可以加入这个圈，否则新开一个圈。

转化过来就是，第$i$个人有没有对$MaxR$和$MaxL$产生影响。

因此问题与$i$无关。也就解释了为什么排序不会影响最优性。

### 贪心过程：

要使椅子数最少，则贪心选择**相邻相差小**的值。
直接对$l,r$排序，求$max(l,r)$，即较大的一个。

$p.s.$注意每个人本来就有一个椅子，因此$ans$+=$n$。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define ll long long
#define rep(i,l,k) for(int i=(l);i<=(k);i++)
int n;ll L[N],R[N],ans;
int ip(){
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
ll IP(){
    ll x=0,w=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int main(){
    n=ip();rep(i,1,n) L[i]=IP(),R[i]=IP();
    sort(L+1,L+1+n);sort(R+1,R+1+n);
    rep(i,1,n) ans+=max(L[i],R[i]);printf("%lld",ans+n);
    return 0;
}
```


---

## 作者：20100202w (赞：0)

这题代码很简单，思维难度却不小 。

贪心原则：


先把左位置数与右位置数分别排升序 。

因为最少有 n 个座位，所以答案初始值为 n 。

排完序后每次加上左位置数与右位置数中较大的一个 。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>//头文件
using namespace std;
int l[100005],r[100005];
int maxn(int a,int b)
{
	return a>b?a:b;//判断 a 与 b 谁大
}
int main()
{
	int n;
	scanf("%d",&n);
	long long ans=n;//要开long long 类型
	for(int i=1;i<=n;i++)
		scanf("%d%d",&l[i],&r[i]);//输入
	sort(l+1,l+n+1);//sort排序      
	sort(r+1,r+n+1);
	for(int i=1;i<=n;i++)//扫描一遍
		ans+=maxn(l[i],r[i]);//加上较大值
	printf("%lld",ans);//输出
	return 0;//养成好习惯
}

```

---

## 作者：mzyc_pzx (赞：0)

[CF1060D Social Circles](https://www.luogu.com.cn/problem/CF1060D)
#### 题型：
简单的贪心。
### 贪心策略：
若要使椅子最少，即公用椅要尽可能多，所以，把 $l$ 和 $r$ 从小到大排序，
然后将 $l_i$ 与 $r_i$ 中的大数累加（代码中 $a$ 数组和 $b$ 数组分别对应 $l$ 数组和 $r$ 数组） 。
### 主要代码：
```cpp
	cin>>n;
	for(int i=1;i<=n;i++) 
	cin>>a[i]>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	sum+=max(a[i],b[i]);
	cout<<sum+n;
```


---

## 作者：Huaji_King (赞：0)

**首先**，既然题目要椅子数最少，只要使两人公用的椅子最多，便可以使题目最优解。
### 贪心思路：公用椅子越多越好。
![](https://cdn.luogu.com.cn/upload/image_hosting/kggewfwb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


------------
**其次**，由于人是可以自由安排位置的,所以只需把 $r$ 和 $l$ 拆开来找即可，无须合起来找。

**所以**，我们只需要找出椅子数尽量合适的 $r$ 和 $l$，取 $\max(r,l)$ 加起来即可。排序正好可以找到最合适的 $r$ 和 $l$,因为第一个 $r$ 与第一个 $l$ 配对最合适。


### 注意:
#### 还要加上他们自己坐的椅子。


------------
# 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l[1000010],r[1000010];
long long bs;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>l[i]>>r[i];
	}
	sort(l+1,l+n+1);
	sort(r+1,r+n+1);
  	//排序后就可以使最合适l和r放在一起，注意并非是最接近的//
	for(int i=1;i<=n;i++)
	{
		bs+=max(l[i],r[i]);//把这一堆椅子加起来。
	}
	bs+=n;//记得加回他们坐的椅子！
	cout<<bs;
	return 0;
}
```


---

## 作者：云浅知处 (赞：0)

一道简单的贪心qwq

------------

由于每个人想让左右手边都放一些椅子，那么我们考虑怎样的两个人坐在一起最优。

显然让一个左手处椅子数量与另一个右手处椅子数量相差最小的两人坐在一起，会 “抵消” 掉很多椅子。

比如，一个人想在他右手边放 $5$ 个椅子，另一个人又想在他左手边放 $5$ 个椅子，那么这俩人坐一起就**一共**只需要 $5$ 个椅子了qwq。

那么我们把 $\{L_n\}$ 与 $\{R_n\}$ 两个数列分别排序，然后求 $\sum\limits_{i=1}^n\max(L_i,R_i)$ 再加上一个 $n$ 即可。

```cpp
#include<cstdio>
#include<algorithm>

#define MAXN 100005
#define int long long

using namespace std;

int l[MAXN],r[MAXN];
int n;

signed main(void){
	
	scanf("%ld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&l[i],&r[i]);
	}
	
	sort(l+1,l+n+1);
	sort(r+1,r+n+1);
	
	int ans=n;
	
	for(int i=1;i<=n;i++){
		ans+=max(l[i],r[i]);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：chufuzhe (赞：0)

只要看出这道题是贪心，就很好做了。

当每加入一个人时，有两种选择，要么新构成一个圈，要么利用之前已有的空位。

因为椅子的数量与 $max(l_i,r_i)$ 有关，所以椅子的数量要最少，只需要让 $max(l_i,r_i)$ 的值最小。

因此我们可以将 $l$ 、 $r$ 从小到大排序，每次增加 $max(l_i,r_i)+1$ 就可以了。 $+1$ 是因为客人也要坐一个椅子。

要注意，因为 $l_i$ 、 $r_i$ 的最大值为 $10 ^ 9$ ， $n$ 的最大值为 $10 ^ 5$，答案的最大值就会到 $10 ^ {14}$，显然 $int$ 不够， 要用 $long$ $long$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005]; //定义，a表示l，b表示r
int b[100005];
int main()
{
	ios::sync_with_stdio(false);
	long long ans = 0; //注意用long long
	int n;
	cin >> n; //输入
	for(int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	sort(a + 1, a + n + 1); //排序
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++) //计算
		ans += max(a[i], b[i]) + 1; //注意要+1
	cout << ans << endl; //输出
	return 0;
}
```


---

## 作者：彭骐飞 (赞：0)

这个题看上去是个神仙题。蒟蒻我当时一头雾水。

然后就开始推性质了qwq。首先，我们可以想到，应该把差距小的$l_i$和$r_j$。

接着，我们就可以想出一个优秀的方法：我们先把每个人当$l_i+r_i+1$算，$ans = \sum\limits_{i=1}^n {l_i+r_i+1}$。

然后把$l$和$r$分别从小到大排序，最后我们认为排序后的$l_i$和$r_i$是共用中间的空位的，所以$ans -= \sum\limits_{i=1}^{n} {max \{ l_i , r_i \}}$。

然后就发现这个能过样例qwq，然后交上去就$Pretest\ Passed$了qwq，然后$System\ testing$时提心吊胆qwq，然后$Final\ standings$时就$Passed\ System\ Test$了qwq。

然后您就可以获得$900$到$1500$不等的好成绩qwq。

为什么这个是对的呢？

我们发现，首先，这个分配肯定是最优的（用调整法是显然的），然后，我们把每个人当成一个点，如果两个人共用中间的空位则连边。

这个图应该有$n$个点和$n$条边，并且每个点的度都为$2$。稍有常识的人都会知道，这个图的形态一定是若干个环。所以这样是对的qwq。

代码：（[43779683](http://codeforces.com/contest/1060/submission/43779683)）

```cpp
#pragma comment (linker,"/STACK:1024000000")
#pragma GCC target(arch=corie7-acx)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define i64 long long
using namespace std;
int n,l[100001],r[100001];
i64 ans;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		ans+=l[i]+r[i]+1;
	}
	sort(l+1,l+1+n);
	sort(r+1,r+1+n);
	for (int i=1;i<=n;i++)
	ans-=min(l[i],r[i]);
	printf("%lld",ans);
	return 0;
}
```

PS:
1. 这个题是要开$long long$的啊qwq，我被$Hacked$了一次啊qwq（[43777905](http://codeforces.com/contest/1060/submission/43777905)）。
1. 至于这玩意儿到底怎么常规推出我认为是不太可能的啊qwq。

---

