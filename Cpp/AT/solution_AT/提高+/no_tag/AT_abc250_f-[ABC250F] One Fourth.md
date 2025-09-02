# [ABC250F] One Fourth

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc250/tasks/abc250_f

ABC250 は、 ABC1000 の開催を目指す高橋くんにとってちょうど $ 1/4 $ となる記念すべき回です。  
 そこで、高橋くんはピザを $ 1 $ 枚買ってきて、そのピザのうちなるべく $ 1/4 $ に近い分量を食べて祝うことにしました。

高橋くんが買ってきたピザは凸 $ N $ 角形 ($ N\ \ge\ 4 $) の平らな形をしており、このピザを $ xy $ 平面上に置いた際、 $ i $ 番目の頂点の座標は $ (X_i,Y_i) $ でした。

高橋くんは、このピザを以下のように切って食べることにしました。

- まず、高橋くんはピザの頂点のうち隣接しない $ 2 $ 頂点を選び、それらを通る直線に沿ってナイフを入れ、ピザを $ 2 $ つに切り分ける。
- その後、 $ 2 $ つのピースのうち好きなものをどちらか $ 1 $ つ選んで食べる。

高橋くんが買ってきたピザの面積の $ 1/4 $ を $ a $ 、高橋くんが食べるピースの面積を $ b $ とした時、 $ 8\ \times\ |a-b| $ としてありえる最小値を求めてください。なお、この値は常に整数となることが示せます。

## 说明/提示

### 制約

- 入力は全て整数
- $ 4\ \le\ N\ \le\ 10^5 $
- $ |X_i|,\ |Y_i|\ \le\ 4\ \times\ 10^8 $
- 入力される頂点は反時計回りに凸 $ N $ 角形をなす。

### Sample Explanation 1

$ 3 $ 番目の頂点と $ 5 $ 番目の頂点を通る直線に沿ってピザを切り分け、 $ 4 $ 番目の頂点を含む側のピースを食べたとします。 このとき、$ a=\frac{33}{2}\ \times\ \frac{1}{4}\ =\ \frac{33}{8} $ 、 $ b=4 $ 、 $ 8\ \times\ |a-b|=1 $ であり、これがありえる最小値です。

## 样例 #1

### 输入

```
5
3 0
2 3
-1 3
-3 1
-1 -1```

### 输出

```
1```

## 样例 #2

### 输入

```
4
400000000 400000000
-400000000 400000000
-400000000 -400000000
400000000 -400000000```

### 输出

```
1280000000000000000```

## 样例 #3

### 输入

```
6
-816 222
-801 -757
-165 -411
733 131
835 711
-374 979```

### 输出

```
157889```

# 题解

## 作者：Rnfmabj (赞：0)

## ABC250F

*2044

### 题意

给你一个凸包，你需要沿着对角线将其 ~~击而破之~~ 切成两部分，然后选择其中的一部分。设原凸包的面积是 $A$，你选择的部分是 $B$ ，你需要最小化 $8 × |A \div4-B|$。可以证明答案是一个整数。

凸包以顶点的形式给出，顶点按逆时针方向排列。

$N \le 10^5$

### 题解

直接运用旋转卡壳的思想，使用双指针。

枚举每一个起刀点 $p$，然后逆时针枚举落刀点 $q$ ，始终选取所切出的线段的左半平面。容易发现这样所得到的面积 $B$ 是随着 $q$ 的移动单调递增的。而当其超过了 $A ÷ 4$ 时显然接着枚举不会更新答案了，所以就可以只计算第一个大于 $A÷4$ 的 $q$（注意这里没必要移动 $q$ 了），然后跳过剩下的点。

那么当我们接着逆时针枚举 $p+1$ 的时候，我们就没必要重置之前的 $q$ 了。因为在固定 $q$ 的情况下，$p ← p+1$ 只会使得面积变小，不会超过 $A ÷ 4$，省去了前面的点，从而避免了重复枚举。然后接着向后枚举 $q$ 即可。

时间复杂度 $O(n)$ 。



---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
要最小化面积，又是个凸包，考虑旋转卡壳。系数不需要考虑，重点在于 $|\frac{a}{4}-b|$，不难发现，在一个切入点固定的情况下，当 $\frac{a}{4}<b$ 时，继续枚举是无意义的，而在 $\frac{a}{4}\geq b$ 这段时间内 $a$ 的值是单调递增的，所以便可以使用双指针维护，只要目前 $\frac{a}{4}\geq b$，就一直向后移，由于凸包也是一个环形的，所以要破环城链，各部分的面积可以预处理。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<int> ci;
typedef complex<double> cd;
int n,x[N],y[N],ans=inf,s[N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
int Cale(int i,int j){return x[i]*y[j]-x[j]*y[i];}
int Cut(int i,int j)
{
	if(i==j) return 0;
	return s[j]-s[i]-Cale(i,j);
}
signed main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	n=read();
	rep1(i,1,n)
	{
		x[i]=read();
		y[i]=read();
		x[i+n]=x[i];
		y[i+n]=y[i];
	}
	x[n<<1|1]=x[1];
	y[n<<1|1]=y[1];
	rep1(i,1,n<<1) s[i+1]=s[i]+Cale(i,i+1);
	int k=1;
	rep1(i,1,n)
	{
		k=max(k,i+2);
		while(k<=(n<<1)&&(Cut(i,k)<<2)<=s[n+1]) ++k;
		ans=min(ans,abs(s[n+1]-(Cut(i,k)<<2)));
		ans=min(ans,abs(s[n+1]-(Cut(i,k-1)<<2)));
	}
	cout<<ans<<endl;
	return 0;
}

```

---

