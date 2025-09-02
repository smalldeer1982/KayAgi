# Laser

## 题目描述

佩娅是科研学员中最负责任的科技工作者。所以她的上司叫她去用她们学院最先进的激光仪去做一个很智障的任务：去融化一块巧克力。

我们的激光仪包含了一个$ n * m $的网格和一个机械臂。机械臂上固定有两束垂直于网格的激光。这两束激光总是射♂向任意两个格子的中心。既然这两束激光被固定在了机械臂上，它们的运动都是有规律的。如果一束激光向一个方向运动，那么令一束激光也会和第一束激光进行一样的运动。

已知有这些条件：

- 一开始，整个网格都被$ n * m $的巧克力完全覆盖，而且两束激光从一开始就在网格的上方，且它们都是打开的。
- 一旦一束激光射向了一小块巧克力，它就会立即融化掉
- 每一次机械臂的矢量运动都和网格的边缘平行，而且每一次运动结束后，激光束都会指向一小块巧克力的中心。
- 无论任何时候，激光束都不能出巧克力的边缘。佩娅才不想成为第二个戈登·弗里曼博士（在半条命游戏系列里被射线射中变异了的游戏角色）呢。
- 一开始，题目会给你n和m，还有一开始被激光指着的巧克力网格（$ x1, y1 $）和（$ x2, y2 $），$ x $是行数，$ y $是列数。列和行号都从1开始计数。你的任务就是找出有多少点不能被激光融化。（激光可以随便运动）

## 样例 #1

### 输入

```
2
4 4 1 1 3 3
4 3 1 1 2 2
```

### 输出

```
8
2
```

# 题解

## 作者：Mistybranch (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF15B)

题目大概意思是：有一个 $n \times m$ 的巧克力，还有两个点 $(x1,y1)$ 和 $(x2,y2)$，两个点只能同时移动，并且移动方向必须相同，两个点的位置的巧克力会被融化，问至少有多少点不被融化。

这道题是一道模拟题，思路可以说很清晰了，因为 $(x1,y1)$ 和 $(x2,y2)$ 与 $(x1,y2)$ 和 $(x2,y1)$ 效果是一样的，所以不妨把两点变为“左下右上”的形式。

```cpp
if (x_1 > x_2) {
	swap(x_1, x_2);
}

if (y_1 > y_2) {
	swap(y_1, y_2);
}
```

下面以样栗为栗说思路：

```
4 4 1 1 3 3
```
- 先看这一组数据，是一个 $4 \times 4$ 的巧克力。

![](https://cdn.luogu.com.cn/upload/image_hosting/m8yyhw4h.png)

- 两个点坐标分别为 $(1,1)$ 和 $(3, 3)$（到此为止都是废话）：

![](https://cdn.luogu.com.cn/upload/image_hosting/u45dd8g4.png)

- 现在我们要计算出这两点最多能走到多少个位置。

1. 我们会发现左下角的点的下限为 $(1,1)$，也就是这个巧克力的左下角，那么这两个点可以往下走 $0$ 格，往左走 $0$ 格。

2. 同理，右上角的点的上限为 $(4,4)$，也就是这个巧克力的右上角，那么这两个点可以往上走 $1$ 格，往右走 $1$ 格。

3. 那么最后的长宽分别为 $x_1 + n - x_2$ 和 $y_1 + n - y_2$，记为 $a$ 和 $b$。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lzreim17.png)

```cpp
a = x_1 + n - x_2;
b = y_1 + m - y_2;
```

- 最后没被融化的点有 $8$ 个，也就是 $n \times m - 2 \times a \times b$ 个。

```cpp
res = (long long)n * m - 2 * a * b;
```

结束了？**并没有！**

我们来看下一组数据：
```
4 3 1 1 2 2
```
在这一组数据下，我们发现两个点所走的路径**有重叠**。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/xptvkms3.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/z0lcbfub.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/rqk8c3jn.png)

这种情况下我们就要加上重叠的部分，即为 $(a \times 2 - n) \times (b \times 2 - m)$。

```cpp
if (a * 2 > n && b * 2 > m) {
	 res += (a * 2 - n) * (b* 2 - m);
}
```
完整代码：
```cpp


#include <bits/stdc++.h>

int n, m, x_1, y_1, x_2, y_2;
long long a, b, res;

void swap (int &a, int &b) {
	int t;
	
	t = a;
	a = b;
	b = t;
}

int main () {
	int T;
	
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d %d %d %d", &n, &m, &x_1, &y_1, &x_2, &y_2);
        
        if (x_1 > x_2) {
        	swap(x_1, x_2);
		}
		
		if (y_1 > y_2) {
			swap(y_1, y_2);
		}
        
        a = x_1 + n - x_2;
        b = y_1 + m - y_2;
        res = (long long)n * m - 2 * a * b;
        
        if (a * 2 > n && b * 2 > m) {
            res += (a * 2 - n) * (b* 2 - m);
        }
        
        printf("%lld\n", res);
    }
    
	return 0;
} 
```


---

## 作者：ttq012 (赞：1)

**Solution**

现在将 $(x_1, y_1)$ 设为左上的点，$(x_2, y_2)$ 设为右下的点。

可以发现，这两个点中的任意一个点可以走的点的数量都是 $[n - (x_2 - x_1)] \times [m - (y_2 - y_1)]$。那么答案就是 $n \times m - 2\times [n - (x_2 - x_1)]\times [m - (y_2 - y_1)]$，化简之后是 $n \times m - 2\times (n - x_2 + x_1)\times (m - y_2 + y_1)$。

但是两个点可以走的地方有可能有重叠。重叠的部分经过画图可以发现为 $\lbrace \lbrack 2\times (n - x_2 + x_1) - n \rbrack\times \lbrack 2\times (m - y_2 + y_1) - m \rbrack \rbrace$。

然后容斥原理即可。

**Code**

```cpp
// Think twice, code once.

#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n, m;
        cin >> n >> m;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) x1 ^= x2 ^= x1 ^= x2;
        if (y1 > y2) y1 ^= y2 ^= y1 ^= y2;
        int _1 = x1 + n - x2, _2 = y1 + m - y2;
        if (a * 2 > n && b * 2 > m)
            cout << n * m - 2 * a * b + (a * 2 - n) * (b * 2 - m);
        else
            cout << n * m - 2 * a * b << '\n';
    }
    return 0;
}

```



---

## 作者：YNH_QAQ (赞：0)

[传送门](https://www.luogu.com.cn/problem/solution/CF15B)
### 题目意思
有一块巧克力，有两个移动方向相同并同时移动的点。两个点位置的巧克力会被融化，求所有位置走遍后**最少**还剩多少块，能融化的一定要融化。

### 思路
计算能走到多少个位置，分相交于不相交两种情况。

$(x1,y1)$ $(x1,y1)$ 和 $(x2,y2)$ $(x2,y2)$ 与 $(x1,y2)$ $(x1,y2)$ 和 $(x2,y1)$ $(x2,y1)$ 效果是一样的，把两点变成左上一个，右下一个。

### 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/9m3pal7s.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/pxk3c0ou.png)

~~~cpp
//ACcode
#include<bits/stdc++.h>
using namespace std;
long long t;
int main(){
	cin>>t;
	while(t--){
		long long n,m,x1,x2,y1,y2;
		cin>>n>>m>>x1>>y1>>x2>>y2;
      if(x1>x2) swap(x1,x2);
	   if(y1>y2) swap(y1,y2);
        //计算长和宽
        long long a=x1+n-x2;
        long long b=y1+m-y2;
        long long sum=n*m-2ll*a*b;
        if(a*2>n&&b*2>m) sum+=(a*2-n)*(b*2-m);
        cout<<sum<<endl;
    }
	return 0;
} 
~~~

---

## 作者：ncwzdlsd (赞：0)

### 题意简述

有一块 $n\times m$ 的巧克力，两点只能同时移动，两点所占位置巧克力会融化，求所有位置走遍后还有几块巧克力。

### 思路

给定两个矩形，然后要计算两点所走位置的并集相对于全集的补集。每一个点都可以变成左上方的点或右下方的点。这里又到了~~喜闻乐见的~~分情况讨论时间：

- 两个所走的矩形不相交

- 两个所走的矩形有相交，需要处理重叠部分

处理很简单，浅浅地用一下基本的容斥原理即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T,n,m,x1,x2,y1,y2;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>x1>>y1>>x2>>y2;
        x2=abs(x2-x1);y2=abs(y2-y1);
        x1=0,y1=0;
        int x3=n-x2-1,x4=x3+x2,y3=m-y2-1,y4=y3+y2;
        long long ans=(long long)(x3-x1+1)*(y3-y1+1)+(long long)(x4-x2+1)*(y4-y2+1);
        if(x3>=x2 && y3>=y2) ans-=(long long)(x3-x2+1)*(y3-y2+1);
        printf("%lld\n",(long long)n*m-ans);
    }
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1800}$
---
### 解题思路：

简单容斥。

其实我们关心的是两个机械臂之间位移向量，可以直接通过 $|x_1-x_2|$ 和 $|y_1-y_2|$ 计算出来。

然后用这个向量，可以在左下角和右上角圈出两块大小为 $(n-|x_1-x_2|)(m-|y_1-y_2|)$ 的地。

但是这两块地当 $x\ge \left\lfloor\dfrac{n}{2}\right\rfloor$ 且 $y\ge \left\lfloor\dfrac{m}{2}\right\rfloor$ 的时候可能会重合，这时候重合的面积为 $(2x-n)(2y-m)$，从之前算出的面积减去这个面积就得到了能融化的面积，最后用总面积减一下就好了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int T,x1,y1,x2,y2,x,y,n,m,ans;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d%I64d%I64d%I64d%I64d",&n,&m,&x1,&y1,&x2,&y2);
		x=n-abs(x1-x2);y=m-abs(y1-y2);
		ans=2*x*y;
		if(2*x>n&&2*y>m)ans-=(2*x-n)*(2*y-m);
		printf("%I64d\n",n*m-ans);
	}
	return 0;
}
```


---

## 作者：shao0320 (赞：0)

教练拿去给初一$van♂$的题，临时起意拿过来考了考我们。

这题还蛮有意思的。

首先考虑这两个机械臂的可涂范围，一定是两个矩形，那么问题就转化为了这两个矩形的并。

考虑容斥。

其他情况是旋转对称的，因此只需考虑第一个在第二个的左下方的情况。

考虑这两个矩形实际上是一个以右上角为顶点的矩形和一个以左下角为顶点的矩形。

对着样例手玩一下很容易推出结论。

注意，当矩形边长大于$n/2$和$m/2$时需要减掉中间的矩形。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int T,n,m,x1,x2,y1,y2;
int abss(int x)
{
	if(x<0)return -x;
	return x;
}
signed main()
{
	T=read();
	while(T--)
	{
		m=read();n=read();x1=read();y1=read();x2=read();y2=read();
		int a=abss(x1-x2)+1,b=abss(y1-y2)+1,ans=2*(m-a+1)*(n-b+1);
		//cout<<a<<" "<<b<<" "<<ans<<endl;
		int aa=(m-a+1),bb=(n-b+1);
		//cout<<aa<<" "<<bb<<" "<<ans<<endl;
		if(aa*2>=m&&bb*2>=n)ans-=(m-2*(a-1))*(n-2*(b-1));
		//cout<<ans<<endl;
		printf("%lld\n",n*m-ans);
	}
	return 0;
}
/*
1
3 3 3 2 1 1
1
9 6 6 5 3 1
wait a minute
*/
```



---

## 作者：叶枫 (赞：0)

### 题意
给出$n\times m$的一块巧克力，再给出两个点，两点只能同时移动，两点所占位置巧克力会融化，问所有能走位置走遍之后还剩下几块巧克力。
### $Idea$
题目就是给两个矩形，然后算两个点所走位置的并集对于全集的补集。点都可以变成左上方一个点和右下方，然后可以分成两种情况。第一种是两个所走矩形不相交，第二种是相交。

如图
![0.001.jpg](https://img.langlangago.xyz/2019/09/09/5d762ca2319e8.jpg)
求蓝色部分的面积
### $Code$
```cpp
//n,m<=le9->m*n<=1e18，要开long long
signed main(){ 
	int T=read();
	while(T--){
		int n=read(),m=read(),x1=read(),yy=read(),x2=read(),y2=read();
		int a,b,sum;
		if(yy>y2) swap(yy,y2);
		if(x1>x2) swap(x1,x2);
		a=abs(x2-x1); b=abs(y2-yy);
		a=x1+n-x2; b=yy+m-y2;
		sum=a*b*2;
		if(a*2>n&&b*2>m) sum-=(a*2-n)*(b*2-m);
		sum=n*m-sum;
		printf("%I64d\n",sum);
	} 
	return 0;
}
```

---

