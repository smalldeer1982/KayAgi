# Triangle Construction

## 题目描述

You are given a regular $ N $ -sided polygon. Label one arbitrary side as side $ 1 $ , then label the next sides in clockwise order as side $ 2 $ , $ 3 $ , $ \dots $ , $ N $ . There are $ A_i $ special points on side $ i $ . These points are positioned such that side $ i $ is divided into $ A_i + 1 $ segments with equal length.

For instance, suppose that you have a regular $ 4 $ -sided polygon, i.e., a square. The following illustration shows how the special points are located within each side when $ A = [3, 1, 4, 6] $ . The uppermost side is labelled as side $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/e59a9e9dcf5329e7eff8711f30517212fd26fdbd.png)You want to create as many non-degenerate triangles as possible while satisfying the following requirements. Each triangle consists of $ 3 $ distinct special points (not necessarily from different sides) as its corners. Each special point can only become the corner of at most $ 1 $ triangle. All triangles must not intersect with each other.

Determine the maximum number of non-degenerate triangles that you can create.

A triangle is non-degenerate if it has a positive area.

## 说明/提示

Explanation for the sample input/output #1

One possible construction which achieves maximum number of non-degenerate triangles can be seen in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/42eede39a9359517d4b7c742aaa8551dfcdfbb8c.png)Explanation for the sample input/output #2

One possible construction which achieves maximum number of non-degenerate triangles can be seen in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/fc47dcb22d8f025c4d1e0997698a6023ed22d7f5.png)

## 样例 #1

### 输入

```
4
3 1 4 6```

### 输出

```
4```

## 样例 #2

### 输入

```
6
1 2 1 2 1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
3
1 1 1```

### 输出

```
1```

# 题解

## 作者：_Violet_Evergarden (赞：11)

看到题解有点空缺，来发一发。

# 思路：

第一眼就会想到结论，答案为总点数除以 $3$。

然而考虑一种特殊情况，就是如果一条边上的点大于其他所有边上的点之和的两倍，那么我们此时便无法达到总数除以 $3$ 的最优情况，因为三角形的三点不可以在同一条直线上。此时的答案就应该是其他所有边上的点的总数。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a;
int maxx;
long long sum;
int  main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		sum+=a;
		maxx=max(maxx,a);
	}
	if((sum-maxx)*2<maxx){
		cout<<(sum-maxx)<<endl;
		return 0;
	}
	else{
		cout<<sum/3;
	}
	return 0;
}
```


---

## 作者：zhangqiuyanAFOon2024 (赞：2)

~~这道题很水。~~

我们先读题，题意让你在满足以下条件的前提下构造尽量多的三角形。

点不能重复，这不就是所有点加除以 $3$ 吗？

哦，$a_i<2\times10^9$，要开 long long。

~~信心满满交上去，然后 WA 了。~~

我们还要考虑一种情况，就是点数最多的一条边的点数比其它边的点数乘 $2$ 还要多，就输出其它边的点数。

下面看代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,a,maxn=-2e9,sum=0; 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		sum+=a;
		maxn=max(maxn,a);//最大的
	}
	if((sum-maxn)*2<maxn){ //点数最多的一条边的点数比其它边的点数乘 2 还要多
		cout<<(sum-maxn)<<endl;//其它点
		return 0;
	}
	else cout<<sum/3;//所有点除以 3
	return 0;
}
```

---

## 作者：Darling_ZX (赞：2)

# 前言
看到同机房大佬的题解，来解释一下这里他没讲的为什么是两倍，以及另一种解法：
# 补充证明
- 我们知道三角形有三个顶点，所以这里总点数除以 $3$ 应该是没有问题的。

- 那这里为什么是两倍呢？这里其实也不难想到。

这里可能有人会和我刚开始一样有个疑问。

就是难道不是三个不同边上的点构成一个三角形吗？

这样子应该是两个点对一个点才对吧。

但其实实际上还有另外一种更优的方法

就是只需要两条不同边，一条边贡献一个点，另一条边贡献两个点即可。

举个例子：

```
4
3 4 5 30
```

答案就应该是 $(3+4+5)=12$ 个。

而如果是：

```
4
3 4 5 23
```

答案就应该是 $(3+4+4)=11$ 个。

所以这里最大边点数大于等于两倍时，答案是其它边数之和。

代码这里就不放了，同机房大佬那贴了。

# 模拟

观察到范围很小，所以我们可以全部读入完，排一边序后，最小的跟最大的匹配即可。

这里需注意如果可以一条边贡献一个点，另一条边贡献两个点时，优先使用此方案。

这里就不贴代码了，本人比较懒。

---

## 作者：_txb_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1906M)

## 思路：
第一眼直接所有数相加再除以 $3$，但会错第 $16$ 个点，然后我们想一种特殊情况，如果一种点比其他点的两倍还要多，这样就不可以直接除以 $3$，因为三个点在一条线时，不可以凑成一个三角形，所以此时就输出其他所有点的值。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,n,a,maxn=INT_MIN;
int  main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		sum+=a;
		maxn=max(maxn,a);
	}
	if(sum*2-maxn*2<maxn) cout<<sum-maxn<<endl;
	else cout<<sum/3;
	return 0;
}
```


---

## 作者：lichenzhen (赞：0)

## 题目大意
一个正 $n$ 边形，其中第 $i$ 边上有 $a_i$ 个的特殊点。

求以这些特殊点为顶点，能组成不重合三角形个数的最大值。

## 题目解法
为了后面的讲解，我这里把特殊点之和定义为 $A$，特殊点个数最大的那条边的特殊点个数定义为 $a_{max}$。

通过观察图片、研究样例，可以很容易得出来一个方法：结果就是 $A \div 3$。

但是，这种方法忽略了一些的特殊情况。如果其中一条边特殊点的个数大于一定的值，可能会使组成三角形的三个顶点在一条直线上，这种情况就不能组成三角形。

通过仔细思考，我们可以发现，当 $a_{max} = A \times \frac{2}{3}$ 时，特殊点个数最多的那条边中每两个顶点刚好可以与其他边上的每个顶点组成一个三角形。那么，若 $a_{max} > A \times \frac{2}{3}$，按照上面的方法组成三角形就是最优方案，此时特殊点最多的那条边就会剩下几个特殊点，答案就是除了这条边以外，所有特殊点的个数之和，即 $A-a_{max}$。

最后注意：$A$ 的值可能会爆 `int`，要开 `long long`。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long maxn,a,A,n;
int main()
{
    cin>>n;
    while(n--){
        cin>>a;
        A+=a;
        maxn=max(a,maxn);
    }
    printf("%lld",(maxn*3>A*2)?A-maxn:A/3);
    return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

## 思路

求出一共有多少个特殊点，由于每个三角形有 $3$ 个顶点，因此，用特殊点总数除以 $3$ 就好了。

## Code1

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	long long sm=0;
	int N,x,mx=0;
	cin>>N;
	for(int i=1;i<=N;++i){
	    cin>>x;
	    sm+=x;
	}
	cout<<sm/3<<endl;
	return 0;
}
```

交上去你就会发现[会这样](https://www.luogu.com.cn/record/140634117)。

## 反思

造成这种情况的原因是什么呢？让我们将目光放到样例一，有一条边存在 $6$ 个特殊点，很容易发现存在多个点在一个三角形的同一条边，这样的话一个三角形就可能拥有 $4$ 个或更多的特殊点，那么我们的三角形将会少于上述思路中的三角形个数，这种情况怎么处理呢？

## 正确思路

很容易发现，这种情况的我们只需要比较一下所有的 $a_i$，求出 $a_i$ 中的最大值，用特殊点的总数减去这个最大值，即其他边上的点的总数，最后再与初始思路中理论上能构成的三角形个数取个最小值，就是能构成的三角形的最大个数。

## Code2

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	long long sm=0;
	int N,x,mx=0;
	cin>>N;
	for(int i=1;i<=N;++i){
	    cin>>x;
	    sm+=x;
	    mx=max(mx,x);
	}
	cout<<min(sm/3,sm-mx)<<endl;
	return 0;
}
```



---

## 作者：xh001 (赞：0)

# 题意
给定一个一个数 $n$ 和一个序列 $a$ 来描述一个第 $i$ 条边上有 $a_i$ 个特殊点的正多边形，求这些特殊点所构成的互不相交的三角形最多能有多少个。
# 思路
一般来讲，玩过样例后第一反应肯定是总点数除以 $3$ 就是答案，**但是**，还有特殊情况我们没有考虑到，当剩下的点都在同一条边上的时候，它们并不能构成合法的三角形，所以我们需要尽可能地把点最多的边上的点先用完，当这条边上的点数大于剩余所有点的 $2$ 倍的时候，我们就无论如何都不能把最多的边上的点用完，此时答案就为剩余所有点的个数。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
const ll mn=2e18;
ll n,a[200001],ans,m;
inline ll read()
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	n=read();
	for(ll i=1;i<=n;i++)
	{
		a[i]=read();
		ans+=a[i];
		m=(a[i]>m)?a[i]:m;//记录最大值。 
	}
	if(m>2*(ans-m))//特判。 
	{
		cout<<ans-m;
		return 0;
	}
	cout<<ans/3;
	return 0;
}
```


---

## 作者：L_shadow (赞：0)

# 做法一

## 思路：
先审题，然后就看到了最关键的东西：一个特殊点最多成为一个三角形的顶点。

先不考虑其他东东，就根据这一条，就想出了我们的主要解题步骤：将所有点统计一遍，然后除以 $3$ 就能得到最多的三角形的数量。

## code :
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,sum; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		sum+=a;
	}
	cout<<sum/3;
	return 0;
}
```
高高兴兴的交上去，然后呢，没过。

然后进行了一系列反思，想出了做法二。
# 做法二（正解）
## 思路：
在做法一的基础上，多加一条判断。

判断来源：由于三点共线没法产生三角形，如果题目中有一大堆特殊点聚集在一条边上，只有极少数的点不在这条边上。这个时候，做法一的代码相当于把一条线上的特殊点连成三角形，这显然是不符合逻辑的。于是乎，我们需要进行特判，将以上这种情况再进行求解。

判断过程：先求出以上情况的临界点：易知，当一条边上的点的数量（令其为 $a_{\max}$）超过所有点的数量（令其为 $sum$）的 $\frac{2}{3}$ 倍时，会出现这种情况。此时，决定三角形的个数的因素就等于 $sum-a_{\max}$（即除掉那条边，其他边上的点的数量）。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long sum,maxx,a; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		maxx=max(maxx,a);//拥有特殊点数量最多的边
		sum+=a;
	}
	if(maxx*3>sum*2) cout<<sum-maxx; //特殊情况
	else cout<<sum/3;
	return 0;
}

```


---

## 作者：2021zjhs005 (赞：0)

一道数学结论题。

Despiction
------------
给定 $n$ 边形每条边上的点数 $a_i$，求以这些点为顶点，所能构成的不相交的三角形的最多个数。

Solution
------------
三角形有 $3$ 个顶点，因此我们可以构造 $\lfloor\frac{\sum_{i=1}^n a_i}{3}\rfloor$不相交的三角形。

但是，这样会 `WA #16`。

仔细想一想，如果一条边的点数实在是太多了，那么其余不相交的三角形构造完后，这条边剩下的 $x$ 个点数就作废了（不可能三角形的 $3$ 个顶点在同一条边上）。

比如：

```
3
1 2 100
```

答案明显是 $1$。

再如：

```
4
1 2 3 100
```

答案明显是 $6$，$1,2,3$ 个点的边上的每一个顶点和 $100$ 个点的边上的每 $2$ 个顶点都成 $6$ 个不相交的三角形。

也就是说，我们尽可能要用点数最多的那一条边贡献 $2$ 个顶点，其余的不同边贡献 $1$ 个顶点。

设 $k=\max_{i=1}^n a_i$，$sum=\sum_{i=1}^n a_i$，若 $k>\left(sum-k\right)\times 2$ 时，明显这条最多点数的边用不完，因此答案为除了该边的其它点数之和。

Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define repq(i,x,y,z) for(int i=x;i<=y;i+=z)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int n,sum,maxn;

signed main(){
    n=read();
    rep(i,1,n){
        int x=read();
        maxn=max(maxn,x);
        sum+=x;
    }
    if(maxn>(sum-maxn)*2) pr("%lld\n",sum-maxn);//如果是这样，答案就是取余点数的和，即 sum-maxn。
    else pr("%lld\n",sum/3);//否则，即使 sum/3 啦。
	return 0;
}
```

---

