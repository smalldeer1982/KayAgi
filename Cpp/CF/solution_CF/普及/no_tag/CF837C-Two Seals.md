# Two Seals

## 题目描述

One very important person has a piece of paper in the form of a rectangle $ a×b $ .

Also, he has $ n $ seals. Each seal leaves an impression on the paper in the form of a rectangle of the size $ x_{i}×y_{i} $ . Each impression must be parallel to the sides of the piece of paper (but seal can be rotated by 90 degrees).

A very important person wants to choose two different seals and put them two impressions. Each of the selected seals puts exactly one impression. Impressions should not overlap (but they can touch sides), and the total area occupied by them should be the largest possible. What is the largest area that can be occupied by two seals?

## 说明/提示

In the first example you can rotate the second seal by 90 degrees. Then put impression of it right under the impression of the first seal. This will occupy all the piece of paper.

In the second example you can't choose the last seal because it doesn't fit. By choosing the first and the third seals you occupy the largest area.

In the third example there is no such pair of seals that they both can fit on a piece of paper.

## 样例 #1

### 输入

```
2 2 2
1 2
2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 10 9
2 3
1 1
5 10
9 11
```

### 输出

```
56
```

## 样例 #3

### 输入

```
3 10 10
6 6
7 7
20 5
```

### 输出

```
0
```

# 题解

## 作者：Cute__yhb (赞：1)

## 题意
有一个 $a\times b$ 的网格，有 $n$ 个 $x_{i}\times y_{i}$ 的矩形，每个矩形可以翻转，选择两个使得覆盖面积最大。
## 做法
对于两个长为 $x_{1},x_{2}$ 宽为 $y_{1},y_{2}$ 的矩形，靠着放最优。

横着放如

![](https://cdn.luogu.com.cn/upload/image_hosting/jqyu61ek.png)

应满足 $x_{1}+x_{2}\le a$ 且 $\max(y_{1},y_{2})\le b$。

竖着放如

![](https://cdn.luogu.com.cn/upload/image_hosting/iks9f1u8.png)

应满足 $y_{1}+y_{2}\le b$ 且 $\max(x_{1},x_{2})\le a$。

$n\le100$ 可以枚举两个矩形，时间复杂度为 $O(n^{2})$ 不会超时.
 
对于翻转，可以枚举每个矩形的长和宽。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,x[105][5];
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){//输入
		cin>>x[i][1]>>x[i][2];//x[i][1]为x[i],x[i][2]为y[i]
	}
	int maxx=0;
	for(int i=1;i<=n;i++){//第一个
		for(int j=i+1;j<=n;j++){//第二个
        //翻转
			for(int xi=1;xi<=2;xi++){//第一个的长
				int x1=x[i][xi],y1=x[i][3-xi];//长的下标为xi，则宽的下标为3-xi
				for(int yi=1;yi<=2;yi++){//第二个的长
					int x2=x[j][yi],y2=x[j][3-yi];
					if(x1+x2<=a&&max(y1,y2)<=b/*横着放*/||y1+y2<=b&&max(x1,x2)<=a/*竖着放*/){//可行
						maxx=max(maxx,x1*y1+x2*y2);//更新答案
					}
				}
			}
		}
	}
	cout<<maxx;
    return 0;
}
```


---

## 作者：___cjy__ (赞：1)

# CF837C Two Seals 题解

[题目传送门](https://www.luogu.com.cn/problem/CF837C)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf837c)

### 题目大意：

有 $n$ 个印章，大小分别为 $x_i\times y_i$，现有一张 $a\times b$ 的纸，选择两个印章使得他们的覆盖面积最大, 求这个最大值。（印章可以旋转但不可重叠或超出纸的范围）

### 正文：

因为 $1\le n\le 100$，直接枚举复杂度 $O(n^2)$ 即可。

考虑任意一对印章 $x_i\times y_i$ 和 $x_j\times y_j$，显然两个印章紧挨着放可以使利益最大化。那么印章组合所占用的矩形范围就是 $\max(x_i,x_j)\times (y_i+y_j)$。

至于旋转，交换一个矩形中的 $x$ 与 $y$ 就可以做到。因此，选择印章 $x_i\times y_i$ 和 $x_j\times y_j$ 所占用的矩形范围共有 $4$ 种情况：

- $\max(x_i, x_j)\times (y_i+y_j)$

- $\max(y_i, y_j)\times (x_i+x_j)$

- $\max(x_i, y_j)\times (y_i+x_j)$

- $\max(y_i, x_j)\times (x_i+y_j)$

### AC Code：

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 205
#define INF 0x3f3f3f3f
#define bug printf(".....bug!.....\n");

using namespace std;

int n, a, b, ans = 0;
int x[N], y[N];

int check(int x, int y){//矩形 x*y 是否能放到 a*b 中 
	if((x <= a && y <= b) || (x <= b && y <= a))
		return 1;
	else 
		return 0;
}

signed main(){
	cin >> n >> a >> b;
	for(int i=1; i<=n; i++){
		cin >> x[i] >> y[i];
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i == j) continue;
			if(check(max(x[i], x[j]), y[i] + y[j])) 
				ans = max(ans, x[i] * y[i] + x[j] * y[j]);
			if(check(max(y[i], y[j]), x[i] + x[j])) 
				ans = max(ans, x[i] * y[i] + x[j] * y[j]);
			if(check(max(x[i], y[j]), y[i] + x[j])) 
				ans = max(ans, x[i] * y[i] + x[j] * y[j]);
			if(check(max(y[i], x[j]), x[i] + y[j])) 
				ans = max(ans, x[i] * y[i] + x[j] * y[j]);
		}
	}
	cout << ans;
	
	return 0;
} 
```

---

## 作者：lutaoquan2012 (赞：0)

### 题意：
给定一个 $a\times b$ 的网格，还有 $n$ 个 $x_i\times y_i$ 个矩形，矩形可以旋转，在这 $n$ 个矩形里选择两个矩形，让这两个矩形的面积最大并且不重合。

### 思路：
对于两个矩形，靠在一起放显然是最优的。

看到 $n\le100$，枚举即可。
```cpp
//
// Created by 55062 on 2024/11/9.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n,a,b,ans;
struct node{
    ll x,y;
}g[110];
int main() {
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++) cin>>g[i].x>>g[i].y;
    for(int i=1;i<=n;i++){//枚举
        for(int j=1;j<=n;j++){
            if(i==j)continue;//一定要判断，不然不对
            if(g[i].x+g[j].x<=a&&max(g[i].y,g[j].y)<=b||max(g[i].x,g[j].x)<=a&&g[i].y+g[j].y<=b) ans=max(ans,g[i].x*g[i].y+g[j].x*g[j].y);//判断能不能挨着放
            swap(g[i].x,g[i].y);//旋转 x
            if(g[i].x+g[j].x<=a&&max(g[i].y,g[j].y)<=b||max(g[i].x,g[j].x)<=a&&g[i].y+g[j].y<=b) ans=max(ans,g[i].x*g[i].y+g[j].x*g[j].y);
            swap(g[i].x,g[i].y);
            swap(g[j].x,g[j].y);//旋转 y
            if(g[i].x+g[j].x<=a&&max(g[i].y,g[j].y)<=b||max(g[i].x,g[j].x)<=a&&g[i].y+g[j].y<=b) ans=max(ans,g[i].x*g[i].y+g[j].x*g[j].y);
            swap(g[i].x,g[i].y);//旋转 x 和 y
            if(g[i].x+g[j].x<=a&&max(g[i].y,g[j].y)<=b||max(g[i].x,g[j].x)<=a&&g[i].y+g[j].y<=b) ans=max(ans,g[i].x*g[i].y+g[j].x*g[j].y);
            swap(g[i].x,g[i].y);
            swap(g[j].x,g[j].y);//恢复
        }
    }cout<<ans;
    return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF837C)
## 思路&做法
由于 $n$ 很小，所以可以枚举矩形（文中称为 $A$，$B$），然后判断再更新答案。
判断的方法可以用分类讨论。

摆放：
* 两个矩形都不变方向。
* 矩形 $A$ 变方向，$B$ 不变。
* 矩形 $B$ 变方向，$A$ 不变。
* 两个矩形都变方向。

位置：
* $A$ 的宽与 $B$ 的宽对齐，长取最大值。
* $A$ 的长与 $B$ 的长对齐，宽取最大值。
* $A$ 的长与宽与 $B$ 的长与宽对齐。

但这样的讨论量太大了，我们可以在摆放中只讨论 $1$ 与 $3$，因为 $2$ 与 $4$ 只需要把拼出来的图形变换方向就能算出。但摆放的讨论不可避免。
## AC Code
```cpp
// LUOGU_RID: 168656490
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
I n,ans;
struct Info{
	I a,b;
}a[110],A;
bool cmp(I a1,I a2,I b1,I b2){
	return (a1 + a2 <= A.a && b1 + b2 <= A.b) || (a1 + a2 <= A.b && b1 + b2 <= A.a);//1与4类可以同时讨论，2与3类也是 
}
bool check(Info x,Info y){
	return cmp(x.a,y.a,x.b,y.b)//讨论1类 
		|| cmp(max(x.a,y.a),0,x.b,y.b)
		|| cmp(x.a,y.a,max(x.b,y.b),0)
		|| cmp(x.a,y.b,x.b,y.a)//讨论3类 
		|| cmp(max(x.a,y.b),0,x.b,y.a)
		|| cmp(x.a,y.b,max(x.b,y.a),0);		
}
I main(){
	scanf("%d%d%d",&n,&A.a,&A.b);
	for(I i = 1;i <= n;i++){
		scanf("%d%d",&a[i].a,&a[i].b);
	}
	for(I i = 1;i <= n;i++){
		for(I j = 1;j < i;j++){//枚举矩形 
			if(check(a[i],a[j])){
				ans = max(ans,a[i].a * a[i].b + a[j].a * a[j].b);//更新答案 
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：TainityAnle (赞：0)

### 题意分析：

有 $n$ 个 $x_i\times y_i$ 的矩形，找到两个长之和小于等于给定值，宽的最大值小于等于给定值或宽之和小于等于给定值，长的最大值小于等于给定值，且面积和最大。只找两个，所以直接两层循环枚举每一种情况。第一个从 $1$ 枚举到 $n$，为了防止重复，第二个只应从 $i+1$ 枚举到 $n$。

考虑旋转的情况：

1. 两个都不转；

1. 第一个转，第二个不转；

1. 两个都转；

1. 第一个不转，第二个转。

如果转，就交换 $x$ 和 $y$。

到这里就处理完了。

### 思路：

根据上文分析，我们枚举每一种情况。对于每一种情况，当横着放（如图 1），两个 $y$ 的最大值小于 $b$ 且两个 $x$ 的和小于 $a$，或竖着放（如图 2）,两个 $y$ 的和小于 $b$ 且两个 $x$ 的最大值小于 $a$ 时就能放得下，就能计算。

![](https://cdn.luogu.com.cn/upload/image_hosting/19ai95kw.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/e64wb7de.png)

把上面的话转换一下就是 $x_i+x_j\le a$ 且 $\max(y_i,y_j\le b)$ 或 $y_i+y_j\le a$ 且 $\max(x_i,x_j\le b)$。

维护一个变量统计面积最大值就行了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,x[105],y[105],maxx=0;
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if((x[i]+x[j]<=a&&max(y[i],y[j])<=b)||(y[i]+y[j]<=b&&max(x[i],x[j])<=a)) maxx=max(maxx,x[i]*y[i]+x[j]*y[j]);//两个都不转
			swap(x[i],y[i]);//第一个转，第二个不转 
			if((x[i]+x[j]<=a&&max(y[i],y[j])<=b)||(y[i]+y[j]<=b&&max(x[i],x[j])<=a)) maxx=max(maxx,x[i]*y[i]+x[j]*y[j]);
			swap(x[j],y[j]);//两个都转 
			if((x[i]+x[j]<=a&&max(y[i],y[j])<=b)||(y[i]+y[j]<=b&&max(x[i],x[j])<=a)) maxx=max(maxx,x[i]*y[i]+x[j]*y[j]);
			swap(x[i],y[i]);//第一个不转，第二个转
			if((x[i]+x[j]<=a&&max(y[i],y[j])<=b)||(y[i]+y[j]<=b&&max(x[i],x[j])<=a)) maxx=max(maxx,x[i]*y[i]+x[j]*y[j]);
		}
	}
	cout<<maxx;
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

有一张大小为 $a\times b(1\le a,b\le 100)$ 的纸。你有 $n(1\le n\le 100)$ 个印章，大小为 $x_i\times y_i(1\le x_i,y_i\le 100)$。你需要选两个印章盖在纸上，要求不能有公共部分。求印章盖住的面积之和的最大值。印章需要和纸的边界平行，你可以将印章旋转 90 度。

## 思路

这题数据范围很小，直接暴力解就行。时间复杂度 $O(n^2)$。

由于不能重叠，因此放印章其实一共有 2 种可能，要么横着放，要么竖着放。(大家可以自行画图理解)

假设选定的两枚印章为 $i,j(1\le i,j\le n)$。如果横着放则需要满足 $y_i+y_j\le b$ 且 $max(x_i,x_j)\le a$。同样的，如果竖着放则需要满足 $x_i+x_j\le a$ 且 $max(y_i,y_j)\le b$。

注意，由于可以将印章旋转 90 度，即可以把一个印章 $i$ 的 $x_i$ 与 $y_i$ 互换。

## 代码

接下来放上我的代码，最里面两层循环旋转印章，可以很好地避免重复代码的出现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,x[105],y[105],ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>a>>b;
    for(int i=0;i<n;i++)cin>>x[i]>>y[i];
    for(int i=0;i<n;i++){
	for(int j=i+1;j<n;j++){
	    for(int c1=0;c1<2;c1++,swap(x[i],y[i])){
		for(int c2=0;c2<2;c2++,swap(x[j],y[j])){
		    if(x[i]+x[j]<=a&&max(y[i],y[j])<=b)ans=max(ans,x[i]*y[i]+x[j]*y[j]);
            	    if(x[i]+x[j]<=b&&max(y[i],y[j])<=a)ans=max(ans,x[i]*y[i]+x[j]*y[j]);
		}
	    }
	}
    }
    cout<<ans<<endl;
    return 0;
}
```


---

