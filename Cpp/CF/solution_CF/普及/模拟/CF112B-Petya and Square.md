# Petya and Square

## 题目描述

Little Petya loves playing with squares. Mum bought him a square $ 2n×2n $ in size. Petya marked a cell inside the square and now he is solving the following task.

The task is to draw a broken line that would go along the grid lines and that would cut the square into two equal parts. The cutting line should not have any common points with the marked cell and the resulting two parts should be equal up to rotation.

Petya wants to determine whether it is possible to cut the square in the required manner given the sizes of the square side and the coordinates of the marked cell. Help him.

## 说明/提示

A sample test from the statement and one of the possible ways of cutting the square are shown in the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF112B/73a8bd680c4d33b060b29ddcf134c8221469d9f6.png)

## 样例 #1

### 输入

```
4 1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2 2
```

### 输出

```
NO
```

# 题解

## 作者：simonG (赞：4)

### 前言
![](https://cdn.luogu.com.cn/upload/image_hosting/jzhlx57g.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)
一个长方形，只有四种方法平分。
### 详解
因为，根据上图，一个长方形，必定会有四种切割方法，即沿着4条线，做小调整。  
但看下图

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF112B/73a8bd680c4d33b060b29ddcf134c8221469d9f6.png)

是可以的。  
再看下图![](https://cdn.luogu.com.cn/upload/image_hosting/7s8pk261.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如果那个东西在中间4格，无论红线怎么切割，都会使绿色所在面积大于一半。  
再看下图
![](https://cdn.luogu.com.cn/upload/image_hosting/t8ldxdhj.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

**即想切成相等的两部分，必须经过中间4格。**  
所以这题就很简单了，看代码。
### 代码

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
#define ll long long
#define maxn 100001
#define INF 0x7f7f7f7f
#define fre {freopen(".in","r",stdin);freopen(".out","w",stdout);}
using namespace std;

il void read(int &t)
{
	re int x=0,f=1;
	re char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	t=x*f;
}
int k,n,m;
int main()
{
	read(k),read(n),read(m);
	if((n-k/2==0||n-k/2==1)&&(m-k/2==0||m-k/2==1))
		puts("NO");
	else
		puts("YES");
	return 0;
}
```

### 后记
做题记得分析。

---

## 作者：FCB_Yiyang2006✈ (赞：3)

# 这道题...
### 对本蒟蒻很有难度
### 对各位大佬 切水题

### 1.解题说明：
此题是给定一个大正方形中的一个单位块，要求找出一条不与这个单位块有任何公共点的线把该正方形等分为两个形状一样的块。我们都知道如果要二等分一个三角形，无论这条分割线是什么样子的，它肯定会经过正方形的重心，于是这里只要判断这个单位块是不是与重心有公共点即可，也就是判断此块是不是围绕重心的四个小块。

### 2.实现方法
从红色区域 往外扩展，红色区域的上下左右，加上左上、右上、左下、右下，总共8块区域（前提是 最多存在8个），这些区域最重要划分到两个大区域中的一个。
现在如果红色块在版图的中间线上下，肯定不能划分开的。

## 上代码（蒟蒻代码，仅供参考）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main() 
{
	cin>>n>>x>>y;
	if((x==n/2||x==n/2+1)&&(y==n/2||y==n/2+1))
	{
		cout<<"NO";
	}
	else
	{
		cout<<"YES";
	}
	return 0;
}
```
本蒟蒻一向
## 心地善良

这篇题解复制提交可以直接AC.

但是......
# 非紧急情况请勿使用此特殊功能！


---

## 作者：Pkixzx (赞：2)

这道题只要用O（1）的方法就可以解决了。


------------


我看到这道题目，首先先手动模拟几种情况，得出结论，同时，我又按理论推了一次：


当这个点**不**在**横线边**，就可以沿着**横线**切，输出“YES”。

当这个点**不**在**竖线边**，就可以沿着**竖线**切，输出“YES”。

当这个点为**最中间几个点**时，无论怎么切，都**无果**，输出“NO”。（如下图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/zndjl4bn.png)


结果很显然，判断是不是中间几个点。
代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int k,n,m;
	scanf("%d%d%d",&k,&n,&m);
	if((n-k/2==0||n-k/2==1)&&(m-k/2==0||m-k/2==1))//判断如果是中间几个点
	cout<<"NO"<<endl;
	else
	cout<<"YES"<<endl;
        return 0;
}
```

---

## 作者：Stephen_Curry (赞：1)

感觉各位神犇们的题解都有点长啊……

本蒟蒻来发一个稍短的题解

首先理解一下题意：

有一块2n \* 2n的地板，在地板上有一个东西，给出坐标和地板的边长。如今要将地板切成相等的两部分，且不能切到那个东西，问能不能切成功。

由于无论你怎么切都会经过正方形的中心，所以判断会不会切到这个东西，只需要判断这个东西是否在中间。

理解完了，代码其实就比较简单了:

```cpp
#include <iostream>
using namespace std; int n, x, y; int main()  {
    cin >> n >> x >> y;
    cout << ((x == n / 2|| x == n / 2 + 1) && (y == n / 2 || y == n / 2 + 1) ? "NO" : "YES");
}
```

这里使用了三目运算符，就不需要写一个if语句了，省去了很多无用功。

最后，也希望大家能帮忙点个赞，毕竟人家写题解也是不易的啊～

---

## 作者：哔哩哔哩 (赞：1)

评分建议：红

题意：有一块2n*2n的地板，在地板上有一个东西，给出坐标和地板的边长。如今要将地板切成相等的两部分，且不能切到那个东西，问能不能切成功。

所以，只要判断东西（红色）是不是在中间即可

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF112B/73a8bd680c4d33b060b29ddcf134c8221469d9f6.png)

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, x, y;
	scanf("%d%d%d", &n, &x, &y);
	int tx = n / 2, ty = n / 2;
	if ((tx == x || tx + 1 == x) && (ty == y || ty + 1 == y)) puts("NO");
	else puts("YES");
	return 0;
}
```

---

## 作者：爱瑶瑶公主 (赞：0)

~~emm……，这道题貌似没有黄色难度……~~

好的，我也不多唧唧歪歪，直接开始讲解：

由于后来真个地板的边长要乘2，所以说对半切的那条线在那个那个东西的边
边就算切到了。贴两张图，来证明我所说的。

样例2看似是这样的：![](https://cdn.luogu.com.cn/upload/image_hosting/qvvvild3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

实际上是这样的：![](https://cdn.luogu.com.cn/upload/image_hosting/jmcl7rcu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
所以，这样证明了在长度为n的地板上切割，只要碰到了那个东西的边边就切到它了。

好了，证明了这么多，总算珂以帖代码了：
```
#include<bits/stdc++.h>
using namespace std;
long long x,y,n;
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	if((n/2==x||n/2+1==x)&&(n/2==y||n/2+1==y)){//还带有特判，以为n有可能开始是奇数
		printf("NO\n");
		return 0;
	}
	else{
		printf("YES\n");
		return 0;
	}
}
```

---

## 作者：SqrtSecond (赞：0)

## 题意
给定一个$2n\times2n$的地板和一个地板上方格的坐标

求能否不切到方格的前提下将地板分成完全相同的两部分
## 分析
一个$2n\times2n$的地板，最重要的是如图两根线：

![](https://cdn.luogu.com.cn/upload/image_hosting/5axp3igv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果地板上的方格不在上图中心的横线旁，那么只需要沿着横线切割就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/xwt1kmk4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

同理，如果不在中心竖线上，那么沿着竖线切割就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/h7615e1z.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以唯一不能切割的呢？

中间的四个。

![](https://cdn.luogu.com.cn/upload/image_hosting/mtk7fsdr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因为怎么切割都要经过中心点，所以上图的四个方格无解，而其他有解。

证毕。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main()
{
	cin>>n>>x>>y;
	if((x==n/2||x==n/2+1)&&(y==n/2||y==n/2+1))//在中心
  cout<<"NO";
	else cout<<"YES";
  return 0;
}
```


---

## 作者：W_churchill (赞：0)

### 这题为何感觉不为黄题
###### ~~虽然对本蒟蒻很有难度~~

------------
其实翻译已经说得很明白了，题目给n(2n*2n的地板),x(东西的坐标)，y(地板的边长)。如今要将地板切成相等的两部分，且不能切到那个东西，问能不能切成功。     
#### 我们稍加分析就可以得知：要切成相等的两部分，无论怎么切，都必定经过终点。
![](https://cdn.luogu.com.cn/upload/image_hosting/r3dhaoi8.png)
经过这张图，应该就很容易理解了。

------------
经过分析，我们发现题目只要判读一下这个东西在不在中间即可。   
#### 上代码！！！！！
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x,y;
	cin>>n>>x>>y;
	if((x-n/2==0||x-n/2==1)&&(y-n/2==0||y-n/2==1))	cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
	return 0;
} 
```
>if((x-n/2==0||x-n/2==1)&&(y-n/2==0||y-n/2==1)) 即为判读x,y与n/2之间的距离，如果等于1或0，即输出“YES”。


------------
###### 没有更多了
#### 大家再见！

---

## 作者：hensier (赞：0)

很多题目都是有简便的方法的，本题同样如此。我们先来证明：

> 任何经过正方形几何中心的直线，都能够将正方形分成面积相等的两部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/onsi9hdz.png)

如上图，我们作正方形$ABCD$，并在正方形其中一条边（以$CD$为例）上任取一点$E$。然后连接对角线$AC,BD$交于点$O$。$O$就是正方形的几何中心（同时也是对称中心）。延长$EO$交$AB$于$F$。根据正方形的性质可知，正方形对角线互相平分，即$CO=AO$。由于正方形对边平行，所以$∠ACD=∠CAB,∠CEF=AFE$。因此$\triangle CEO$≌$\triangle AFO(AAS)$（~~初中数学~~）。这个时候，我们发现，$CE+BF=AF+DE=AB=CD$。因此四边形$CEBF$和四边形$AFDE$都是梯形，它们的上底和下底之和为正方形边长，高也为正方形边长，所以面积必定相等。

~~当然，还有更简单的证明方法：~~

由于正方形是中心对称图形，所以经过它的对称中心的直线的两边在绕对称中心后能重合，因此两部分必定是面积相等的，事实上还是全等的。

我们回到这道题上面来。这道题说有一个边长为$2n$的正方形。这时我们需要通过一条直线来分割（必须经过中间的格子），因此问题就转化为——这个方块是不是在正方形的中间。

因此我们可以得到代码：

```cpp
#include<cstdio>
int n,x,y;
int main()
{
    scanf("%d%d%d",&n,&x,&y);
    puts((x==(n>>1)||x==(n>>1)+1)&&((y==(n>>1))||(y==(n>>1)+1))?"NO":"YES");//a>>1等同于a/2，而且前者是位运算，速度比后者快得多
}
```


---

## 作者：kirky_wang (赞：0)

### 图解

举一个 $4 * 4$ 的例子



只要在红色区域内，就不可分割：

![](https://cdn.luogu.com.cn/upload/image_hosting/7j1z5624.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


#### 结论 
 
只要在正方形的重心区域内，就不可分割，其他情况均可分割


### 算法分析：

此题是给定一个大正方形中的一个单位块，要求找出一条不与这个单位块有任何公共点的线把该正方形等分为两个形状一样的块。我们都知道如果要二等分一个三角形，无论这条分割线是什么样子的，它肯定会经过正方形的重心，于是这里只要判断这个单位块是不是与重心有公共点即可，也就是判断此块是不是围绕重心的四个小块。
从红色区域 往外扩展，红色区域的上下左右，加上左上、右上、左下、右下，总共8块区域（前提是 最多存在8个），这些区域最重要划分到两个大区域中的一个。
现在如果红色块在版图的中间线上下，肯定不能划分开的。
### 代码

```cpp
#include <bits/stdc+++.h>
using namespace std;
 
int main()
{
    int n,x,y;
    int i, j;
    while( cin>>n>>x>>y )
    {
        int dd=n/2;
        if( (x==dd||x==dd+1)&&(y==dd||y==dd+1) )
        	cout<<"NO\n";
        else
        	cout<<"YES\n";
    }
    return 0;
}
```


---

