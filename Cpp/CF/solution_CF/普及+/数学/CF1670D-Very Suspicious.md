# Very Suspicious

## 题目描述

Sehr Sus is an infinite hexagonal grid as pictured below, controlled by MennaFadali, ZerooCool and Hosssam.

They love equilateral triangles and want to create $ n $ equilateral triangles on the grid by adding some straight lines. The triangles must all be empty from the inside (in other words, no straight line or hexagon edge should pass through any of the triangles).

You are allowed to add straight lines parallel to the edges of the hexagons. Given $ n $ , what is the minimum number of lines you need to add to create at least $ n $ equilateral triangles as described?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/5491a1c977b08c3202f038f487f2a32d813abedc.png)Adding two red lines results in two new yellow equilateral triangles.

## 说明/提示

In the first and second test cases only 2 lines are needed. After adding the first line, no equilateral triangles will be created no matter where it is added. But after adding the second line, two more triangles will be created at once.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/22d6faf1616d600d29aaaff5a040ccd6f3af5678.png)In the third test case, the minimum needed is 3 lines as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/2b991947c4bc515f58f281666fad74ef0d33ed67.png)

## 样例 #1

### 输入

```
4
1
2
3
4567```

### 输出

```
2
2
3
83```

# 题解

## 作者：JCLinux (赞：5)

### 思路：

这个题目让我们通过画直线来构造正三角形

题目说这个平面无穷大，但是样例图片给的好像不算太大，那我就提供一张比较大的图片吧。

![空白蜂巢](https://cdn.luogu.com.cn/upload/image_hosting/8aomys7e.png)

现在让我们开始画线。

有一点要注意的是：只能沿着正六边形的边画线，也就是说，**直线的方向只有三种**：水平、60°、120°

这是我想出这个题的解的关键。

现在考虑画一条线：

![一条线](https://cdn.luogu.com.cn/upload/image_hosting/zdxrpiv5.png)

很显然，没办法构成任何三角形。

但是，此时水平方向的线的数量由 $0$ 变成了 $1$

接着，第二条线

![两条线](https://cdn.luogu.com.cn/upload/image_hosting/z5euu6fe.png)

第二条线，为了能产生三角形，我们肯定不能平行画，因为这样他们不能相交，情况就和一条线一样了，没办法构成三角形。

那我们就斜着画，方向无所谓，因为这个图片可以看成是**对称的**。

斜着画我们使两条线相交于六边形内部，这样的话就形成了两个黄色的正三角形，如图。

接下来就是三条线的情况了

如图：

![三条边](https://cdn.luogu.com.cn/upload/image_hosting/1vc1sna7.png)

水平方向我们在第一次的时候画过了，120°的线我们在第二次的时候画了，那么60°的线我们就在第三次画。

这样的话，**它能够与我们先前画的两条线都相交**。

还是让这两个交点分别落在两个不同的正六边形里面，于是，对于每一个交点，都**分别产生了两个三角形**，也就是图中的紫色和橙色三角形。

我们发现一个规律：

### 一条直线，每与另外一条直线产生交点时，就会多生成两个三角形

因为蜂巢是无穷大的，因此，我们能够保证每个交点都能位于六边形之内。

为什么要是交点位于六边形之内呢？

因为交点如果在六边形的顶点上，构不成三角形，我们就是在做无用功。

还有一种情况是三个直线相交在六边形里面一点（中心），其实和两个交点的情况是一样的，都是增加了 $4$ 个三角形，因此我们只考虑两两相交的情况。

那么一条线，可以与多少条其他的线相交呢？

**图中已有的且与之不平行的线**

因此三个方向我们轮流划线，这样的话总的交点数最多。

严格证明的数学方法我不是很懂，欢迎补充，但是我们可以通过列举前几次的样例来确保我们的构造方式的正确性。

这样的话，我们就可以预处理出画 $n$ 条线能产生的最多三角形，随着 $n$ 的增大，三角形必定是增多的，因此我们可以二分找出答案。

### 代码实现：

用三个数代表三个方向的直线数量，每次画都从直线数量最少的那个方向画，这样的话，对于当前这一轮能产生的交点数最多，也能保证三个方向的数量只差不超过 $1$ ，三个方向的数量尽量平均，保证了交点总数也是最大的。

也就是说，其实就是贪心地最大化当前步骤的交点数，总体的交点数量就是最大的。

知道了每个方向的直线数量就能很方便的计算出新生的交点数，那么新生成的三角形的个数就是新生成的交点数乘以 $2$

### 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mmax = 1e9+7;
vector<int>tar;
int t,n;
void init()
{
    priority_queue<int,vector<int>,greater<int> >q;
    for(int i=0;i<3;i++) q.push(0);
    int x = 0;
    int sum = 0;
    while(x<mmax)
    {
        tar.push_back(x);
        int mmin = q.top();
        q.pop();
        x += 2*(sum-mmin);
        sum++;
        mmin++;
        q.push(mmin);
    }
}
signed main()
{
    cin.sync_with_stdio(false);
    init();
    cin >> t;
    cin.tie(0);
    while(t--)
    {
        cin >> n;
        cout << lower_bound( tar.begin() , tar.end() , n ) - tar.begin()  << '\n';
    }
    return 0;
}

```


---

## 作者：daniEl_lElE (赞：5)

## 思路

首先，我们会发现，你分的线数越多分得三角形越多，即满足单调性（简单证明一下，就是如果这个数量你用 $i$ 条线能形成，剩下一条线就算不和他们交叉也能做到这个数量）。

那么，我们可以考虑二分答案，二分至少需要的线的数量。

考虑我们现在已经得到 $mid$ 即线的数量，现在我们计算可以得到的三角形的数量。

首先，我们先考虑 $3\lfloor \frac{mid}{3}\rfloor$ 条线有多少的三角形满足要求。我们考虑分成两部分计算，一类是成功将一个六边形分成 $6$ 个三角形的六边形数。考虑先列举出来找找规律：$1,3,7,12,19\dots$，差为 $1,2,4,5,7\dots$，我们会发现差是以 $1,2,1,2\dots$ 的方式递增的，那么成功将一个六边形分成 $6$ 个三角形的六边形数就可以用等差数列来计算，以下定义 $p=\lfloor \frac{mid}{3}\rfloor$。那么对于 $p$ 是 $2$ 的倍数的情况，方案数就是 $\dfrac{\dfrac{p}{2}(1+(1+3\times(\dfrac{p}{2}-1)))}{2}+\dfrac{\dfrac{p}{2}(2+(2+3\times(\dfrac{p}{2}-1)))}{2}$；对于 $p$ 不是 $2$ 的倍数的情况，方案数就是$\dfrac{\lceil\dfrac{p}{2}\rceil(1+(1+3\times\lfloor\dfrac{p}{2}\rfloor))}{2}+\dfrac{\lfloor\dfrac{p}{2}\rfloor(2+(2+3\times(\lfloor\dfrac{p}{2}\rfloor-1)))}{2}$。

接下来，我们考虑另一类将一个六边形分成两个等腰三角形的方案数。依然适用原来的方法：$0,3,6,9,12\dots$，这个规律就很好找了，就是 $\dfrac{p(0+(0+(p-1)\times3))}{2}$。最后得到的式子就是将前一种方案乘 $6$，将下面这种乘 $2$ 后的结果。

在这之后，我们还要考虑添加 $1,2$ 条线所得的方案数。当添加一条线时，你会多获得 $\lfloor \frac{p}{2}\rfloor$ 个六边形由原来 $2$ 个三角形变成 $6$ 个三角形，$\lceil\frac{p}{2}\rceil\times2$ 个原来没有三角形的变成 $2$ 个三角形。当你再添加一条线时，你会多获得 $\lceil\frac{p}{2}\rceil$ 个六边形由原来 $2$ 个三角形变成 $6$ 个三角形，$\lfloor\frac{p}{2}\rfloor\times2+1$ 个原来没有三角形的变成 $2$ 个三角形。特判一下即可。

最终复杂度 $O(t\log n)$，即可通过本题。

个人感想：在比赛时不大喜欢碰到这种纯数学类题目。

## 代码

~~数学题就是，推倒不容易，代码很简单。~~

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(n<=2){
			cout<<2<<endl;
			continue;
		}
		int L=3,R=n;
		while(L<R){
			int mid=(L+R)>>1;
			int p=mid/3;
			int tri=0,tri2=0;
			if(p%2==0){
				tri=(1+1+(p/2-1)*3)*p/4+(2+2+(p/2-1)*3)*p/4;
				tri2=((p/2)*(p/2+1)/2+(p/2)*(p/2-1)/2)*3;
			}
			else{
				tri=(1+1+(p/2)*3)*(p+1)/4+(2+2+(p/2-1)*3)*(p/2)/2;
				tri2=(p/2)*(p/2+1)/2*6;
			}
			int tmp=tri*6+tri2*2;
			if(mid%3==1){
				tmp+=p/2*4+(p+1)/2*2*2;
			}
			if(mid%3==2){
				tmp+=p/2*4+(p+1)/2*2*2;
				tmp+=(p+1)/2*4+(p/2*2+1)*2;
			}
			if(tmp>=n){
				R=mid;
			}
			else{
				L=mid+1;
			}
		}
		cout<<L<<endl;
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

教皇在群里提到了这个结论，可以做到更优秀的复杂度。题解都是二分，这题可以 $ \mathcal{O}(1) $ 复杂度求解。

结论：答案为满足 $ \frac{2x^2}{3} \geq n $ 的最小整数 $ x $。

证明：根据 [这篇题解](https://www.luogu.com.cn/blog/ShaoJia/solution-cf1670d) 的结论，不难得到每个数应该都等于 $ \frac{x}{3} $ 的时候取到最优答案，则显然有 $ 2(xy+xz+yz)=2\times 3 \times \frac{x^2}{9}=\frac{2x^2}{3} $。

所以转化式子为 $ x^2 \geq \frac{3n}{2} $，解得 $ x \geq \sqrt{\frac{3n}{2}} $，于是可以直接 $ \mathcal{O}(1) $ 计算。

时间复杂度 $ \mathcal{O}(T) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f(double a)
{
if(a==(int)(a))
return a;
return a+1;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
    {
		int n;
		cin>>n;
		cout<<f(sqrt(n*3/2.0))<<'\n';
	}
}
```


---

## 作者：I_am_Accepted (赞：1)

### Analysis

发现每两条相交的线就会新增两个满足题意的正三角形。

我们转化成对偶命题：**给定 $a$ 条线，求最大的交点数量。**

注意这里的交点数量为两两交点的数量，即如果三线交于一点，则算有 $3$ 个交点。

我们只需要快速算出这个问题的答案，就可以对原问题二分答案求解。

发现六边形网格中有三种斜率，我们设斜率为这三种的直线条数分别为 $x,y,z(x+y+z=a)$。

这样两两交点数量为 $xy+yz+zx$，我们要最大化这个数。

------------

**结论：** $x,y,z$ 尽可能相近可使得 $xy+yz+zx$ 最大。

**证明：**

$$\begin{aligned}
xy+yz+zx&=\frac{1}{2}(2xy+2yz+2zx)
\\
&=\frac{1}{2}\left((x+y+z)^2-x^2-y^2-z^2\right)
\\
&=\frac{1}{2}\left(a^2-x^2-y^2-z^2\right)
\end{aligned}$$

我们让 $x^2+y^2+z^2$ 最小即可。

反证法，若最优的方案存在 $x<y-1$，则重新分配成 $\{x+1,y-1,z\}$ 将是更优解，因为：

$$\begin{aligned}
(x+1)^2+(y-1)^2+z^2&=x^2+2x+1+y^2-2y+1+z^2
\\
&=x^2+y^2+z^2+2(x-y+1)
\\
&<x^2+y^2+z^2
\end{aligned}$$

同理后得到 $\max\{x,y,z\}-\min\{x,y,z\}\le 1$，得证。

------------

由于 $a$ 条线的交点数是 $a^2$ 级别的，所以原问题的答案是 $\sqrt{n}$ 级别的，所以时间复杂度 $O(\log \sqrt{n})$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
inline int check(int x){
	int a=x/3+(x%3>0),b=x/3+(x%3>1),c=x/3;
	return 2*(a*b+b*c+c*a);
}
signed main(){IOS;
	int T,n;cin>>T;
	while(T--){
		cin>>n;
		int l=1,r=39000,mid,res;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid)>=n) res=mid,r=mid-1;
			else l=mid+1;
		} 
		cout<<res<<endl;
	}
return 0;}
```

---

## 作者：chl090410 (赞：0)

## The Solution to CF1670D Very Suspicious

### Description

你可以在在一个无穷大的平面蜂巢中画平行于六边形的一条边的直线，你画的直线与六边形的边可以构成正三角形，求构成至少 $n$ 个正三角形所需的最少直线数。

### Solution

若两条直线在六边形内相交（如题目中的图所示），那么就会产生两个正三角形，所以 $n$ 条直线所能构成的正三角形数的最大值为这 $n$ 条直线的最大交点数。

由于直线要和边平行，所以只会出现三种直线：水平的、$60^\circ$ 的、$120^\circ$ 的，我们若新画一条直线，必定只会和其中两种直线有交点，因为交点数要最多，所以，该直线要与直线数最少的那种直线平行。

我们按照上述方法依次画直线并将所构成的正三角形数存入一个数组中，直到该数大于 $n$ 的最大值 $10^9$ 为止。之后，对于每一个 $n$，二分查找最少直线数即可。

### AC code 如下：

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int qs,x,y,p,k=2,l,g,t,n;
queue<int> q; 
int a[100005]; 
signed main(){
	cin>>l;
	while(!q.empty()) q.pop();
	q.push(1);q.push(1);q.push(1);
	a[1]=2;a[2]=6;
	qs=6;x=3;y=3;
	while(qs<1000000000){
		g=q.front();
		q.pop();
		qs+=(y-g)*2;
		a[++k]=qs;
		y++;
		x++;
		q.push(g+1);
	}
	a[++k]=qs;
	for(int i=1;i<=l;i++){
		cin>>n;
		cout<<lower_bound(a+1,a+k+1,n)-a+1<<endl;
	}
	return 0;
}

---

