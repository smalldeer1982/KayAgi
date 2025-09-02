# Dead Pixel

## 题目描述

Screen resolution of Polycarp's monitor is $ a \times b $ pixels. Unfortunately, there is one dead pixel at his screen. It has coordinates $ (x, y) $ ( $ 0 \le x < a, 0 \le y < b $ ). You can consider columns of pixels to be numbered from $ 0 $ to $ a-1 $ , and rows — from $ 0 $ to $ b-1 $ .

Polycarp wants to open a rectangular window of maximal size, which doesn't contain the dead pixel. The boundaries of the window should be parallel to the sides of the screen.

Print the maximal area (in pixels) of a window that doesn't contain the dead pixel inside itself.

## 说明/提示

In the first test case, the screen resolution is $ 8 \times 8 $ , and the upper left pixel is a dead pixel. Here you can see one of two possible layouts of the maximal window.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1315A/cb58b5325ebfab8c891df37e110ee05ad36ccf9e.png)

## 样例 #1

### 输入

```
6
8 8 0 0
1 10 0 3
17 31 10 4
2 1 0 0
5 10 3 9
10 10 4 8```

### 输出

```
56
6
442
1
45
80```

# 题解

## 作者：dingcx (赞：3)

作为一道 A 题，显而易见很水。

## 思路

先画一个图：（中间那个黑的是坏的）

![](https://cdn.luogu.com.cn/upload/image_hosting/lniv64vc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

根据贪心，很容易得到：可能的解**只有**我在图上框出的**四个区域**。

也就是说只需要比较这些区域的大小就好了。下面来表示这些区域。

注意坐标是**从 $0$ 开始**的。

于是我又画了一个图：（高度为 $n$，宽度为 $m$）

![](https://cdn.luogu.com.cn/upload/image_hosting/eop6x0ra.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

容易计算出上图中的结果：高度分别为 $x$ 和 $n-x-1$，宽度分别为 $y$ 和 $m-y-1$。

所以答案就是 $\max(\max(x,n-x-1)\times m,\max(y,m-y-1)\times n)$。

## 代码

其实根据上面的完全可以把代码写出来，不过考虑到完整性我还是贴上代码吧。

```cpp
#include<cstdio>
#include<algorithm> //用到 max
using namespace std;
int read(){ //没啥用的快读
	int num=0,sign=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
int main(){ //主函数
	int T=read(); //数据组数
	while(T--){
		int n=read(),m=read(),x=read(),y=read();
		printf("%d\n",max(max(x,n-x-1)*m,max(y,m-y-1)*n)); //直接套公式
	}
	return 0; //华丽结束
}
```
看我这么辛苦画的图，总得点个赞再走呀~

---

## 作者：sycqwq (赞：1)

思路：

根据每组数据，一共有四种情况：

死像素上边的，$(y-1)*a$

死像素下边的，$(b-y)*a$

死像素左边的，$(x-1)*b$

死像素右边的，$(a-x)*b$

那最大面积的是多少呢？就是这四种情况最大的。

代码：
```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int a,b,x,y;
        cin>>a>>b>>x>>y;
        x+=1;//注意是从0开始，所以要+1
        y+=1;
        int s1=(y-1)*a;//四种情况
        int s2=(b-y)*a;
        int s3=(x-1)*b;
        int s4=(a-x)*b;
        cout<<max(max(max(s1,s2),s3),s4)<<endl;//最大的
    }
    return 0;
}
```

---

## 作者：流绪 (赞：1)

结论题！

画个图，取普通情况点在中央，会发现可能出现的情况有四种，点下面的构成矩形，点左边的构成矩形，点右边的构成矩形，点上面的构成矩形。四种情况算出面积，然后取最大值即可。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int a,b,x,y;
		cin >> a >> b >> x >> y;
		ll s1 = (a-x-1)*(b);
		ll s2 = (a)*(b-y-1);
		ll s3 = (a)*(y);
		ll s4 = (x)*b;
		s1 = max(s1,max(s2,max(s3,s4)));
		cout << s1 << endl;  
	}
	return 0;
}
```


---

## 作者：Xdl_rp (赞：0)

明显是一道数学题，~~我最爱虐数学题了~~

进入正题
------------
不含坏点（坐标设为 $(x, y)$）的矩阵，具备以下条件：

1. 整个矩阵在坏点的上方（宽的最大坐标小于 $x$）。
2. 整个矩阵在坏点的下方（宽的最小坐标大于 $x$）。
3. 整个矩阵在坏点的左边（长的最小坐标大于 $y$）。
4. 整个矩阵在坏点的右边（长的最大坐标小于 $y$）。

取其中的最大值即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
static char buf[1000000], *p1 = buf, *p2 = buf;
#define Rg register
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
inline int read() {
	Rg int g = 0;
	Rg char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') g = (g << 1) + (g << 3) + (c ^ 48), c = getchar();
	return g;
}
inline void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
	return;
}
int main() {
	int n;
	cin >> n;
	while (n--) {
		int a, b, x, y;
		cin >> a >> b >> x >> y;
		int ans1 = (a - x - 1) * b;
		int ans2 = x * b;
		int ans3 = (b - y - 1) * a;
		int ans4 = y * a;
		int ans = max({ans1, ans2, ans3, ans4});
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：zyk7 (赞：0)

#### 题目要求在矩阵中找到 **不包含坏点** 的矩形的面积，总体上来说我用到了 **贪心** 思路。

我们仔细思考一下，对于矩阵上的点 $A$，不包含 $A$ 的矩形可以在 $A$ 的上下

左右四个方向；并且要让矩形面积最大，则它的 **长和宽** 必须尽可能大,所以

有以下四种可能的情况：

- 长为 $b$，宽为 $a-x-1$
- 长为 $b$，宽为 $x-1+1$
- 长为 $a$，宽为 $b-y-1$
- 长为 $a$，宽为 $y-1+1$

#### 最后只需要输出它们乘积的最大值就可以了

**PS：** 以上 $x,y,a,b$ 与题目描述相同； 并且由于数组下标是从零开始的，
所以宽要 $+1$ 或 $-1$。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int a,b,x,y;
		scanf("%d%d%d%d",&a,&b,&x,&y);
		int p1=a-x-1,q1=b-y-1,p2=x-1+1,q2=y-1+1;
		int f1=p1*b,f2=q1*a,f3=p2*b,f4=q2*a;
		printf("%d\n",max(f1,max(f2,max(f3,f4))));
	}
	return 0;
}
```


---

## 作者：123456zmy (赞：0)

题意：  
你需要在一块 $a\times b$ 的区域内选出一个最大的不包含 $(x,y)$ 的区域（坐标从 $(0,0)$ 到 $(a-1,b-1)$）。
___
因为要不包含 $(x,y)$ 并且面积最大，所以选出来的矩形一定是贴着 $(x,y)$ 的，枚举在 $(x,y)$ 的哪个方向然后取最大值输出。

代码：（~~如果你看了题，没贴出来的你肯定会写~~）
```
printf("%d\n",max(max((a-1-x)*b,x*b),max(a*(b-1-y),a*y)));
```

---

