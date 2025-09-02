# [ABC334B] Christmas Trees

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc334/tasks/abc334_b

東西に無限に伸びる道路があり、この道路上のある基準となる地点から東に $ x\mathrm{\,m} $ のところにある地点の**座標**は $ x $ と定められています。 特に、基準となる地点から西に $ x\mathrm{\,m} $ のところにある地点の座標は $ -x $ です。

すぬけ君は今から、座標が $ A $ である地点を基点にして $ M\mathrm{\,m} $ おきにクリスマスツリーを立てます。 すなわち、座標がある整数 $ k $ を用いて $ A+kM $ と表されるような地点それぞれにクリスマスツリーを立てます。

高橋君と青木君はそれぞれ座標が $ L,R\ (L\leq\ R) $ である地点に立っています。 高橋君と青木君の間（高橋君と青木君が立っている地点を含む）に立てられるクリスマスツリーの本数を求めてください。

## 说明/提示

### 制約

- $ -10^{18}\leq\ A\ \leq\ 10^{18} $
- $ 1\leq\ M\ \leq\ 10^9 $
- $ -10^{18}\leq\ L\leq\ R\ \leq\ 10^{18} $
- 入力は全て整数

### Sample Explanation 1

すぬけ君は、座標が $ \dots,-4,-1,2,5,8,11,14\dots $ である地点にクリスマスツリーを立てます。 これらのうち高橋君と青木君の間にあるのは、座標が $ -1,2,5 $ である地点に立てられる $ 3 $ 本です。

### Sample Explanation 2

高橋君と青木君が同じ地点に立っていることもあります。

## 样例 #1

### 输入

```
5 3 -1 6```

### 输出

```
3```

## 样例 #2

### 输入

```
-2 2 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
-177018739841739480 2436426 -80154573737296504 585335723211047198```

### 输出

```
273142010859```

# 题解

## 作者：Little_x_starTYJ (赞：7)

### 解题思路

我们只需要仔细想想，就可以想到找到第一个整数 $n\geq l$ 的数，并且找到第一个整数 $k\le r$，然后特判 $n = k$ 的情况和 $k < n$ 的情况即可。

AC CODE:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	ll a, m, l, r;
	cin >> a >> m >> l >> r;
	ll l2 = l, r2 = r;
	/*只用找到第一个>=l的满足条件的数与
	第一个>=r的满足条件的数即可*/
	if (a > r) {
		ll k = (a - r) / m;
		k = a - k * m;
		while (k > r)
			k -= m;
		r = k;
	} else {
		ll k = (r - a) / m;
		k = a + k * m + m;
		while (k > r)
			k -= m;
		r = k;
	}
	if (l > a) {
		ll k = (l - a) / m;
		k = a + k * m;
		while (l > k)
			k += m;
		l = k;
	} else {
		ll k = (a - l) / m;
		k = a - k * m;
		while (l > k)
			k -= m;
		l = k;
	}
	if (l >= l2 && l <= r2 && r >= l && r <= r2 && r >= l2)
	cout << (r - l) / m + 1;
	else
		cout << 0;
	return 0;
}
```

---

## 作者：yydfj (赞：5)

这是本蒟蒻第四十七次写的题解，如有错误点请好心指出！

讲一个很好想也很好写的做法，从位置 $A$ 开始一次跳 $M$ 格，一直跳到位置 $L$ 的右侧（包括 $L$）且尽可能往左靠，记跳到的位置为 $X$，这样，答案就是位置 $X$ 往右跳或不跳的位置且在 $R$ 的左侧（包括 $R$）的个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ll A,M,L,R;
	cin>>A>>M>>L>>R;
	ll X=A+(L-A)/M*M;//从位置A开始一次跳M格，一直跳到位置L的右侧（包括L）且尽可能往左靠
	cout<<(R-X)/M+(X>=L&&X<=R);//位置X往右跳或不跳的位置且在R的左侧（包括R）的个数
	return 0;
}
```

---

## 作者：FL_sleake (赞：5)

### 题意简述

小 F 要摆放圣诞树。他先在 $A$ 点摆一棵树。随后从 $A$ 点开始，向左每隔 $k$ 个单位长度摆一棵树，向右每隔 $k$ 个单位长度摆一棵树。他想问你，$l$ 和 $r$ 之间一共有几棵圣诞（包含 $l,r$）。

### 解题思路

$A$ 在 $l,r$ 中间则查询 $l,A$ 之间有多少棵，加上 $A,r$ 之间有多少棵，再减一即可。

$A$ 在 $l$ 左边则查询 $A,r$ 之间有多少棵，减去 $A,l-1$ 之间的棵数。

$A$ 在 $r$ 右边则查询 $l,A$ 之间有多少棵，减去 $r+1,A$ 之间的棵树。

注意到我们这样定义的话，查询的一个端点一定是 $A$，那么就很好计算了。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define max(a,b) (a>b?a:b)
int A,k,l,r,ans=0;
int getans(int L,int to){
	return (to-L)/k+1;
}
signed main(){
	cin>>A>>k>>l>>r;
	if(l<=A&&A<=r) ans=getans(l,A)+getans(A,r)-1;
	else if(A<l) ans=getans(A,r)-getans(A,l-1);
	else ans=getans(l,A)-getans(r+1,A);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Down_syndrome (赞：2)

## 题意
在一条左右延伸的路上，点 $x$ 处有一棵圣诞树。此外，与点 $x$ 的距离为 $y$ 的倍数的点也有一棵圣诞树。求点 $l$ 到 $r$ 有多少棵圣诞树。
## 思路
非常抽象的 B 题。虽然说是红（后面好像变橙了），但我相信还是有很多人被卡的，比如说我。先转换一下问题，想象一下，把所有点往左移动 $x$ 的距离，这样问题就变成了所有位置为 $y$ 的倍数的点有一棵圣诞树，求点 $l-x$ 到 $r-x$ 有多少棵圣诞树。这样的好处是从 $1$ 到 $x$ 共有 $\left\lfloor\dfrac{x}{y}\right\rfloor$ 个 $y$ 的倍数（这点读者可以自己试着推一推），可以直接算出来。以下分析都让 $l\gets l-x,r\gets r-x$。

**分类讨论一下（灵魂画手上线）**

1. 如果 $l\le0$ and $r\ge0$
![](https://cdn.luogu.com.cn/upload/image_hosting/53w85yhh.png)

答案就为绿色区间与蓝色区间相加，记得把 $0$ 加上。虽然绿色的区间在 $0$ 的左边，都是负数，不能直接用除法的方式算出来，但是正负是对应的，即 $l$ 到 $-1$ 的圣诞树的数量等于 $1$ 到 $-l$ 的圣诞树的数量，即为 $\left\lfloor\dfrac{-l}{y}\right\rfloor$，所以最后的答案为 $\left\lfloor\dfrac{-l}{y}\right\rfloor+\left\lfloor\dfrac{r}{y}\right\rfloor+1$。

2. 如果 $l>0$ and $r>0$
![](https://cdn.luogu.com.cn/upload/image_hosting/2d9u48qw.png)

答案就为蓝色区间与绿色区间相减。记得 $l$ 和 $r$ 两个点上也是要算的，所以为 $\left\lfloor\dfrac{r}{y}\right\rfloor -\left\lfloor\dfrac{l-1}{y}\right\rfloor$。

3. 如果 $l<0$ and $r<0$
![](https://cdn.luogu.com.cn/upload/image_hosting/b5wzg97k.png)

和第二种情况相似，只是把 $l$ 和 $r$ 都取反就行了。答案为 $\left\lfloor\dfrac{-l}{y}\right\rfloor-\left\lfloor\dfrac{-r-1}{y}\right\rfloor$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y,l,r,numl;
int main(){
	scanf("%lld%lld%lld%lld",&x,&y,&l,&r);
	l-=x;
	r-=x;
	if(l<=0&&0<=r) printf("%lld",-l/y+r/y+1);
	else if(0<l&&0<r) printf("%lld",r/y-(l-1)/y);
	else printf("%lld",-l/y-(-r-1)/y);
	return 0;
}
```

---

## 作者：yang2_0 (赞：2)

# 题目

[题目传送门](https://www.luogu.com.cn/problem/AT_abc334_b)

# 思路

这一次的 $B$ 题比较难，但讨论一下也可以了。讨论 $A$ 在 $L$ 和 $R$ 之间，$A$ 在 $L$ 左侧，$A$ 在 $R$ 右侧三种情况即可。注意一下点算两遍的问题。现在的问题就变成了：如何计算两个点之间种的树的数量？

我们可以循环遍历来找到种树的点，但是这样显然会超时。但是我们可以用后面的点减去前面开始种树的点，除以两棵树之间的间隙，再加上 $1$（开始种树的点也要种上树），就可以算出两个点之间种的树的数量了。

如何理解呢？除以两棵树之间的间隙 $b$，可以看作把两棵树之间的区间分成 $(r-l)/b+1$ 个长度为 $b$ 的区间，每个区间有一棵树，那么自然就有 $(r-l)/b+1$ 棵树了。

# 代码

自认为代码还是比其他题解的要简单的。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,d;
signed main(){
	cin>>a>>b>>c>>d;
	if(a>=c&&a<=d)
	{
		int t1=(a-c)/b+1;
		int t2=(d-a)/b+1;
		cout<<t1+t2-1;//减一是因为A点算了两遍。
	}
	else if(a<c)
	{
		int t1=(d-a)/b+1;
		int t2=(c-a)/b+1;
		if((c-a)%b==0)cout<<t1-t2+1;//L点算了两次。
		else cout<<t1-t2;
	}
	else if(a>d)
	{
		
		int t1=(a-d)/b+1;
		int t2=(a-c)/b+1;
		if((a-d)%b==0)cout<<t2-t1+1;//R点算了两次
		else cout<<t2-t1;
	}
	
	return 0;
} 
```

---

## 作者：BenRheinz (赞：1)

忽然想到的奇妙做法。

该做法的核心在于平移区间。

我们首先令 $l_1=l-A,r_1=r-A$，这样相对于 $l_1,r_1$ 而言圣诞树就分布在 $kM$ 的位置上。

不过此时 $l_1$ 仍然有可能是负数，不便于我们处理。这时我们再将 $l_1,r_1$ 整体加上 $(-\frac{l}{M}+1)\times M$，得到 $l_2,r_2$，容易发现它们一定都是正数，且此时问题与原问题等价。

答案即为 $\lfloor\frac{r_2}{M}\rfloor-\lfloor\frac{l_2-1}{M}\rfloor$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ll a,m,l,r;
	cin>>a>>m>>l>>r;
	l-=a,r-=a;
	if(l<0){
		ll d=(-l)/m+1;
		l+=d*m,r+=d*m;
	}
	printf("%lld",r/m-(l-1)/m);
	return 0;
}
```

---

## 作者：Expert_Dream (赞：1)

最难了，我切了很久啊。换了很多种方法。

[link](https://atcoder.jp/contests/abc334/submissions/48791025)。

核心代码：

```cpp
int a,m,l,r;
cin >> a >>  m >> l >> r;
l-=a,r-=a;
if(l>0) cout<<(r/m-l/m+(l%m==0));
else if(r>0) cout<<(r/m+(-l)/m+1);
else cout<<((-l)/m-(-r)/m+((-r)%m==0));
```
我们可以通过取模的性质。然后知道一个数模 $m$ 等于 $a$ 模 $m$ 的地方有树。首先我们不妨先将 $a$ 的位置看成 $0$ 点。我们可以抽象的理解，利用 $m$ 分了很多个区间，每一个区间都是长度为 $m$，然后算出 $l$ 和 $r$ 分别属于什么区间，然后两个区间编号一减，其实就是他们中间树的个数。如果左端点在树上，还要再加一。因为涉及到正负性的关系。所以需要稍微分类讨论一下，然后注意细节即可。罚时3次。

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)，AtCoder 题解复盘集合。

---

