# [ARC129B] Range Point Distance

## 题目描述

对于一组整数 $l,r,x$，其中 $l \le r$，定义 $dist(l,r,x)$ 为：

- 若 $x < l$，则 $dist(l,r,x) = l - x$
- 若 $l \le x \le r$，则 $dist(l,r,x) = 0$
- 若 $x >r$，则 $dist(l,r,x) = x - r$ 

可以简要理解为 $x$ 在数轴上到区间 $[l,r]$ 的距离。

现在给定 $N$ 对整数，第 $i$ 对整数形如 $(L_i, R_i)$。对于 $k=1,2,\dots,N$，分别求解下面的问题：

- 自由选择一个整数 $x$，计算 $max_{i=1}^k dist(L_i,R_i,x)$，求其可能的最小值。

## 说明/提示

- $1 \le N \le 2 \times 10^5$
- $1 \le L_i \le R_i \le 10^9$
- 所有输入均为整数。

## 样例 #1

### 输入

```
3
1 3
2 4
5 6```

### 输出

```
0
0
1```

## 样例 #2

### 输入

```
10
64 96
30 78
52 61
18 28
9 34
42 86
11 49
1 79
13 59
70 95```

### 输出

```
0
0
2
18
18
18
18
18
18
21```

# 题解

## 作者：chinazhanghaoxun (赞：5)

## 题意

给定 $N$ 个区间，要求出 $\max^k_{i=1} dist(L_i,R_i,x)$ 的最小值。
## 分析

因为求前 $k$ 个数，所以只有最大和最小值会影响答案，也就是最右边的左端点以及最左边的右端点，我们分别记为 $L$ 和 $R$。

接下来还要分类讨论，如果 $L\le R$，那么输出 0。否则，答案就应该在左边和右边的中间，为 $(L-R+1)\div2$。步骤就这两步，代码也是非常简洁的。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,L,R=INT_MAX; //R要定成极大值，我一开始被这个点坑惨了
int main(){
    cin>>n;
    for(int i=1,l,r;i<=n;i++){
		cin>>l>>r;
        //处理出左端点和右端点 
        L=max(L,l);
        R=min(R,r);
        if(L<=R) //第一种情况 
			cout<<"0\n";
        else //第二种情况 
			cout<<(L-R+1)/2<<endl;
    }
    return 0;
}
```

---

## 作者：Zhl2010 (赞：1)

## 题目概括
请问在前 $n$ 组 $l$ 和 $r$ 中，对于每一个 $x$，最小的距离是多少（求距离公式在题面上）？

## 思路
因为是前 $k$ 个数，所以只有极值能影响答案。

记录下左端点最大的数，记为 $ma$。  
记录下右端点最小的数，记为 $mi$。

分类讨论，如果 $ma$ 小于 $mi$，就代表 $x$ 能在 $l$ 和 $r$ 中间，答案照题意说就是 $0$。

如果 $ma$ 大于 $mi$，就代表 $x$ 要么在左端点左边，要么在右端点右边，而且只有 $ma$ 和 $mi$ 能影响最终答案（$x$ 会在其它 $l$ 和 $r$ 中间），所以答案应在 $ma$ 和 $mi$ 的最中间，为 $(ma-mi+1)/2$。

## 代码（很简洁）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mi=INT_MAX,ma=INT_MIN;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		ma=max(ma,a);//左端点最大的数
		mi=min(mi,b);//右端点最小的数
		if(ma<=mi){//在 l 和 r 中间
			cout<<0<<endl;
		}else{//在左端点左边或在右端点右边
			cout<<(ma-mi+1)/2<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Red_river (赞：1)

### 题目大意
给你一个 $N$ 个区间，使得 $\operatorname {max_{i=1}^k dist}(L_i,R_i,x)$ 的值最小。
### 分析
其实既然是求一个数的最大值最小，我们就必定要将每个数变得最小。于是不难想到，我们只需要让右端点最小，左端点最大就行了。

对于一组整数 $\operatorname {(l, r, x)}$，其中 $l \leq r$，定义 $\operatorname {dist}(l, r, x)$ 如下：

如果 $x < l$，则 $\operatorname {dist}(l, r, x) = l - x$。
如果 $l \leq x \leq r$，则 $\operatorname {dist}(l, r, x) = 0$。
如果 $x > r$，则 $\operatorname {dist}(l, r, x) = x - r$。
可以理解为 $x$ 在数轴上到区间 $[l, r]$ 的距离。

现在假设我们有 $N$ 对整数 $(L_i,R_i)$，对于 $k = 1, 2, \dots, N$，我们分别要求解下面的问题：

自由选择一个整数 $x$，计算 $\operatorname {max_{i=1}^k dist}(L_i, R_i, x)$ 的可能的最小值。

以下是解决方案的步骤：

观察到对于每个区间 $(L_i, R_i)$，只有三种情况：$x < L_i$，$L_i \leq x \leq R_i$，$x > R_i$。因此，对于每个区间，我们只需考虑这三种情况下的距离。

1. 当 $x < L_i$ 时，距离为 $L_i - x$。我们可以选择 $x = L_i - 1$，这样距离为 1。

1. 当 $L_i \leq x \leq R_i$ 时，距离为 0。我们可以选择 $x = L_i$，这样距离为 0。

1. 当 $x > R_i$ 时，距离为 $x - R_i$。我们可以选择 $x = R_i + 1$，这样距离为 1。

1. 对于每个区间 $(L_i, R_i)$，选择 $x = L_i - 1$ 或 $x = R_i + 1$ 可以得到最小的距离。

1. 因此，问题就转化为找到所有区间的最大 $L_i - 1$ 和最小 $R_i + 1$，然后计算这两个值之间的距离。

### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 1000005
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int dis[N],vis[N],wis[N],f[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	} 
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
	num=INF;
	read(jk);while(jk--){
		read(n),read(m);
		sum=max(sum,n);
		num=min(num,m);
		if(sum<=num) wh(0);
		else wh((sum-num+1)/2);
	}
	return 0;
}
```

---

## 作者：YangXiaopei (赞：1)

## Solution:

我们可以发现，每加一个区间，答案不可能变小。

而能对答案产生影响的只有最右边的左端点和最左边的右端点，只要它满足了这两个，其他一定都满足。

那记录最左的右端点和最右的左端点的地方，分类输出即可。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, l, r, maxn, minn;
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> l >> r;
        maxn = max(maxn, l);
		minn = min(minn, r);
		if(maxn <= minn){
		    cout << "0\n";
		}
		else{
		    cout << (maxn - minn + 1) / 2 << "\n";
		}
	}
}

```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_arc129_b)

$ma$ 是 $l$ 此时的最大值。$mi$ 是 $r$ 此时的最小值。

分类讨论:

- 如果 $ma$ 小于等于 $mi$，就代表 $x$ 能在 $l$ 和 $r$ 中间，答案就是 $0$。

- 如果 $ma$ 大于 $mi$，就代表 $x$ 要么在 $l$ 的左边，要么在 $r$ 的右边，因为只有 $ma$ 和 $mi$ 能影响最终答案，所以答案应在 $ma$ 和 $mi$ 的最中间，就是 $(ma-mi+1)\div2$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;
	cin >>n;
	int mi=1e9+7,ma=-1;//定义最小值和最大值，最小值初值要大，最大值初值要小 
	while(n--){//循环n次 
		int a,b; 
		cin >>a>>b;
		ma=max(ma,a);//取之前的ma和a的最大值，赋给ma 
		mi=min(mi,b);//取之前的mi和b的最小值，赋给mi
		if(ma<=mi){//小于等于 
			cout<<"0"<<endl;//输出0 
		}else{//大于 
			cout<<(ma-mi+1)/2<<endl;//输出(ma-mi+1)/2
		}
	}
	return 0;
}
```

---

## 作者：shenbairui (赞：0)

### [题目传送门](luogu.com.cn/problem/AT_arc129_b)

### 题目意思
请问在前 $n$ 组 $l$ 和 $r$ 中，对于每一个 $x$，最小的距离是多少。

### 题目范围
先看数据范围，只能用线性的算法。首先这道题不需要预处理，因为它的 $k$ 是直接根据输入的数来逐渐增大的，所以可以直接一边输入一遍处理。

因为求前 $k$ 个数，所以只有最大和最小值会影响答案，也就是最右边的左端点以及最左边的右端点，我们分别记为 $L$ 和 $R$。

代码为：
```cpp
maxx=max(maxx,l);
minn=min(minn,r);
```


另外我们可以发现所有答案排列起来一定是一个单调不减的序列，因为你加入一个范围只能让你的 $x$ 变大。

具体也可以看 @nkrqzjc_zzz 大佬已经讲得非常清楚了

综上所述我们可知：

$dist=\left \lfloor\frac{L+R}{2}   \right \rfloor $

输出:

```cpp
cout<<(maxx-minn+1)/2<<"\n";
```


### 上代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,i,maxx,minn=2e9;
int main(){
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>l>>r;
        maxx=max(maxx,l);
        minn=min(minn,r);
        if(maxx<=minn) cout<<"0\n";
        else cout<<(maxx-minn+1)/2<<"\n";
    }
    return 0;
}
```
下次见！拜拜！

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_arc129_b)

## 题意
给定 $n$ 个区间，求 $\max^{k}_{i=1}  dist(L_i,R_i,x)$ 的最小值。
## 思路
可发现所有答案排列起来一定是一个单调不减的序列，只有左右端点会影响答案，记录两端位置即可。

-  $dist= \lceil \frac{L+R}{2} \rceil$

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,i,ma,mi=2e9;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>l>>r;
        ma=max(ma,l);
        mi=min(mi,r);
        //更新L与R
        if(ma<=mi) cout<<"0\n";//R小于L时最小值为0
        else cout<<(ma-mi+1)/2<<"\n";
        //分类输出
    }
    return 0;
}
```

---

## 作者：A2244 (赞：0)

## 题解

### 题意
对于每个 $k$，找出一个 $x$ 来最小化 $\max_{i=1}^k dist(L_i,R_i,x)$。

### 思路
首先观察到，如果某个 $x$ 落在所有区间的公共部分，那么 $\max_{i=1}^k dist(L_i,R_i,x)=0$。如果没有这种共同部分，我们假设最小值出现在 $l$ 的某个位置 $x$ 附近。

假设这样的 $x$ 存在于区间 $[l,r]$，那么必然有 $r-l$ 个区间包含 $x$。那么现在要做的就是让这 $r-l$ 个区间的边界尽量靠近 $x$，也就是选择一个 $x$ 使得 $dist(l,x)$ 的最大值等于 $dist(x,r)$ 的最大值。

根据初中数学可得 $x=\frac{l+r}{2}$，所以最小值为 $dist(l,r,x)=\frac{r-l+1}{2}$。

时间复杂度线性。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define VI vector<int>
#define pb push_back
#define endl '\n'
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repp(i,a,b) for(int i=a;i<b;i++)
#define il inline
#define per(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
namespace IO{
	template<typename T> inline void read(T &x){
		bool f=1;x=0;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
		while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
		x=f?x:-x;
	}
	template<typename T> inline void write(T x){
		if(x<0) putchar('-'),x=-x;
	   	if(x>9) write(x/10);
	   	putchar(('0'+x%10));
	}
	template <typename T,typename ...Args> inline
	void read(T &x,Args &...args){read(x);read(args...);}
	template<typename T> inline void write(T x,char c){write(x),putchar(c);}
}
using namespace IO;

const int inf=1e9+7;
int n,l,r,rr=-inf,ll=inf;
signed main(){
	read(n);
	while(n--){
		read(l,r);
        rr=max(rr,l);
		ll=min(ll,r);
		if(rr<=ll){
		    write(0,'\n');
		}
		else{
		    write((rr-ll+1)/2,'\n');
		}
	}
	return 0;
}


```

---

## 作者：nkrqzjc_zzz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc129_b)


------------

### 题目概述：

给定 $k$ （$1\leq k\leq N$）个区间，找一 $x$ 使得 $x$ 到离它最远区间的距离最小。

### 思路：

$N$ 都 $2\times 10^5$ 了，这不得是个 $O(N)$ 呀？显然这道题就是这样。对于一个数学蒟蒻来说，这道题居然毫无压力的通过了！

首先这道题不需要预处理，因为它的 $k$ 是直接根据输入的数来逐渐增大的，所以可以直接一边输入一遍处理。

另外，你可以发现所有答案排列起来一定是一个单调不减的序列，因为你加入一个范围只有可能使你的 $x$ 变大。

那么所有的 $L$ 和 $R$ 都能对答案产生影响吗？不不不，你简单推理一下就可以知道，非最左边的 $R$ 和非最右边的 $L$ 就无法对 $x$ 产生半毛钱影响，因为 $x$ 在满足最左边的 $R$ 和最右边的 $L$ 时，就已经满足了其他的条件。

那么问题就简单明了起来了：

若最左边的 $R$ 大于最右边的 $L$，那 $x$ 距离两端的最小的最大值就为两头的中间值，直接使用初一的数轴基础知识：$\left(L+R\right)\div 2$ 即可。

若最左边的 $R$ 小于等于最右边的 $L$，证明 $x$ 在所有区间内，答案自然为 $0$。

### 代码

更多详情请看代码

```cpp
#include<bits/stdc++.h>//万能头 
long long n,l,r,xi=-1e9,da=1e9;
//n,l,r如题意。xi为最右边的L的位置，da为最左边的R的位置 
main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&l,&r);
		xi=std::max(xi,l);//更新最右边的L
		da=std::min(da,r);//更新最左边的R
		if(xi>da)printf("%lld\n",(xi-da+1)/2);//若最左边的R大于最右边的L 
		else puts("0");//若最左边的R小于等于最右边的L 
		//puts自带换行，不用手写
	}
}
```

//

---

## 作者：NightmareAlita (赞：0)

## 简要题意

给定 $N$ 对 $L_i, R_i$，然后在每次给出后都要选一个 $x$ 使得 $x$ 到之前给出的所有区间的距离 $dist$ 的最大值最小。一个 $x$ 到区间 $l,r$ 的距离定义为 $dist=\max(0, l - x, x - r)$。

## 策略分析

既然我们每次都要输出答案，那我们不妨从 $dist$ 的定义入手，我们发现在这个定义中，当其结果不为 $0$ 时只有两种情况，要么 $l$ 在 $x$ 右边，要么 $r$ 在 $x$ 左边。那么我们考虑现在有一堆区间，因为我们求的是 $x$ 到所有区间距离的最大值，所以其实我们需要关心的，能够对我们答案造成影响的值就是最靠右的 $L$ 和最靠左的 $R$。得到这个结论后剩下的就比较简单了，我们只需要每次输入一个区间都更新一下这个关键的 $L$ 和 $R$ 即可。

我们现在知道了能够对我们答案造成影响的两个关键点，那么答案如何求解呢，我们进行分类讨论。

- 当 $L \le R$ 时，意味着之前输入的所有区间都有一个共同的交集 $[L,R]$，这个结论直接从 $L,R$ 的定义得出，那么我们随便在 $L,R$ 里怎么选都是 $0$，所以要找的最小值就是 $0$。
- 当 $L >R$ 时，以 $L$ 为左端点的区间和以 $R$ 为右端点的区间一定是之前输入的所有区间里距离最远的一组，只有这一对区间才会产生到 $x$ 的最大值。那么这个最大值最小当且仅当 $x$ 取在 $L,R$ 正中间，又因为要去最大值所以此时 $dist = \left \lceil \frac{L + R}{2}  \right \rceil$。

分析出这两条以后直接在线做就好了，时间复杂度是线性的。

## 参考代码

``` cpp
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;

namespace SHAWN {
    const LL INF = 1e9 + 7;
    LL n, sl = -INF, sr = INF;
    signed work()
    {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            LL l, r; cin >> l >> r;
            sl = max(sl, l), sr = min(sr, r);
            // 更新两个关键点
            if (sr >= sl) { cout << "0\n"; }
            else cout << ((sl - sr + 1) >> 1) << '\n';
            // 按照刚刚的分类讨论进行输出
        }
        return 0;
    }
}

signed main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：loser_seele (赞：0)

首先有 $ dist(l,r,x)=\max(0,l-x,x-r) $，这个是显然的。

于是实际上我们要最小化 $ \max(0,L_1-x,x-R_1,L_2-x,x-R_2,...) $ 的值。

设前缀最大 $ L $ 值为 $ A_k $，前缀最小 $ R $ 值为 $ B_k $，则上式显然等于 $ \max(0,A_k-x,x-B_k) $。

如果 $ A_k \leq B_k $，则令 $ x=A_k $，取到最小值 $ 0 $。

否则显然我们应该取得 $ A_k $ 和 $ B_k $ 的中点位置最优，答案为 $ \lceil \frac{A_k-B_k}{2} \rceil $。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int f(int a) 
{
	return a/2+a%2;
}
int main() 
{
	int n,nowl=-2e9,nowr=2e9;
	cin>>n;
	while(n--) 
	{
		int l,r;
		cin>>l>>r;
		nowl=max(nowl,l);
		nowr=min(nowr,r);
		if(nowl<=nowr)
		cout<<0<<'\n'; 
		else
		cout<<f(nowl-nowr)<<'\n';
	}
}
```


---

## 作者：rq_kyz (赞：0)

# 【题解】 [ARC129B] Range Point Distance

### 传送门

[[ARC129B] Range Point Distance](https://www.luogu.com.cn/problem/AT_arc129_b)

---

### 题意

给定 $n$ 个区间，每次对于前 $k$ 个区间（$1\le k\le n$），有任意的一个整数 $x$，问哪一个 $x$ 会使 $x$ 到离它最远区间的距离最小，求这个最小值。

---

### 分析

我们可以考虑去掉部分区间。如果前 $k$ 个区间有交集，那么 $x$ 一定在这个交集中，这样计算出来的最大值为 $0$，最小。如果前 $k$ 个区间没有交集，我们可以想到，答案只与 $L_i$ 最大的那个区间和 $R_i$ 最小的那个区间有关。假设第 $i$ 个区间 $L_i$ 最大，第 $j$ 个区间 $R_j$ 最小，那么 $x$ 一定在 $[L_i,R_j]$ 这段区间中，因为在这其中可以忽略其他区间造成的影响，相当于减少区间了。再进一步，既然 $x$ 一定在 $[L_i,R_j]$ 这段区间中，那么 $x=\left\lceil\frac{L_i-R_i}{2}\right\rceil$。

化为一个公式，我们在输入过程中记录 $L_i$ 最大的区间 $i$ 与 $L_j$ 最小的区间 $j$，则答案为：$\max(0,\left\lceil\frac{L_i-R_i}{2}\right\rceil)$。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll n,l0=-1e9,r0=1e9;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll l,r;
		scanf("%lld%lld",&l,&r);
		l0=max(l0,l);
		r0=min(r0,r);
		printf("%lld\n",max(0ll,(l0-r0+1)/2));
	}
	return 0;
}
```

---

