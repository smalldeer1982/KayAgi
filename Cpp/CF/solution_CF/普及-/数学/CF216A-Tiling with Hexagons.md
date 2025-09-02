# Tiling with Hexagons

## 题目描述

Several ages ago Berland was a kingdom. The King of Berland adored math. That's why, when he first visited one of his many palaces, he first of all paid attention to the floor in one hall. The floor was tiled with hexagonal tiles.

The hall also turned out hexagonal in its shape. The King walked along the perimeter of the hall and concluded that each of the six sides has $ a $ , $ b $ , $ c $ , $ a $ , $ b $ and $ c $ adjacent tiles, correspondingly.

To better visualize the situation, look at the picture showing a similar hexagon for $ a=2 $ , $ b=3 $ and $ c=4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF216A/3f981143d696c9bb68234ae6ba7b4116d86bd7a4.png)According to the legend, as the King of Berland obtained the values $ a $ , $ b $ and $ c $ , he almost immediately calculated the total number of tiles on the hall floor. Can you do the same?

## 样例 #1

### 输入

```
2 3 4
```

### 输出

```
18```

# 题解

## 作者：zhangyuhao9 (赞：4)

题目大意
---
给定一个由正六边形拼成的不规则六边形的边长 $a,b,c$ ，输出该新六边形是由多少个正六边形构成的。

题目分析
---
根据题意，我们可以将六边形分割成如下图进行计算。

![](https://cdn.luogu.com.cn/upload/image_hosting/zntgrjcy.png?x-oss-process=image/resize,m_lfit,h_150,w_150)

不难推得公式 $S=ab+bc+ca-a-b-c+1$ 。此时再计算就不难了

代码如下

CODE
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	cout<<a*b+b*c+a*c-a-b-c+1<<endl; //公式
	return 0;
}
```
管理员求过。

---

## 作者：chlchl (赞：3)

## 题意
给定一个六边形的三边长度 $a,b,c$，求这个六边形是由几个基础六边形组成的（基础六边形：各边长度为 $1$ 的六边形）。

## 思路
本题是一道思维题，只要想通了，代码连只做过 P1001 的萌新都知道怎么打了。

观察题干中的图，因为不保证是正六边形，所以面积不可直接求解。考虑**分割**，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ztc0y5z4.png?x-oss-process=image/resize,m_lfit,h_400,w_310)

为什么要沿着绿色线而不是其他线分割呢？因为沿着绿色线分割，刚好可以将整个六边形分割成 $3$ 个平行四边形，而平行四边形的面积各位都是知道的：$S=ah$，而 $a,b,c$ 均已给出，所以答案就出来了。

理论上，答案为 $ab+ac+bc$。

### 但是！

![](https://cdn.luogu.com.cn/upload/image_hosting/zntgrjcy.png?x-oss-process=image/resize,m_lfit,h_400,w_310)

正如上图所示，分割后涂了两种颜色的六边形是被算了两次的！要减去分割线上的六边形个数，即 $a+b+c$ 个。减掉后发现中间涂了三种颜色的六边形原本被算了三次，但是减掉了三次，就等于没算，还要加上 $1$。

综上所述，本题答案为 $ab+ac+bc-a-b-c+1$。

~~其实聪明的你早已发现这就是大名鼎鼎的**容斥原理**。~~

## 代码
我觉得各位不用看代码了，不过还是放一下。珍爱生命，原理抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int a, b, c; 

int main(){
	scanf("%d%d%d", &a, &b, &c);
	printf("%d\n", a * (b - 1) + c * (a - 1) + b * (c - 1) + 1);//上式提取公因数后的结果 
	return 0;
}
```
如果觉得本题解对你有帮助，记得点个赞哦！

---

## 作者：KSToki (赞：3)

这道题并不难，用一个简单的容斥即可。先看看样例：
![](https://cdn.luogu.com.cn/upload/image_hosting/0vcjwsdz.png)

发现紫色的线将六边形分为三个平行四边形，先将三个平行四边形的面积加起来，为 $ab+ac+bc$。但线上的点被重复计算，减去即可。此时线的交点（即中间那个点）被算了三次又减了三次，相当于没有算，所以再将结果加一即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	printf("%d\n",a*b+b*c+a*c-a-b-c+1);
	return 0;
}
```


---

## 作者：REAL_曼巴 (赞：2)

 此题可根据三量容斥原理推出公式。我们可以先把总量加起来，但发现三条边有重复，减去即可。但中心点被加了三次又减了三次，抵消了，最后加一补上。公式如下:
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/p21gps8k.png)


附：三量容斥解析。


![](https://cdn.luogu.com.cn/upload/image_hosting/6fptrna2.png)


```cpp
#include<cstdio>
#include<iostream>
int a,b,c;
int main(){
    scanf("%d%d%d",&a,&b,&c);
    printf("%d",a*b+b*c+c*a-a-b-c+1);
    return 0;
}
```


---

## 作者：da32s1da (赞：2)

大眼观察可知，答案为$ab+bc+ca-a-b-c+1$
```
#include<cstdio>
int a,b,c;
int main(){
	scanf("%d%d%d",&a,&b,&c);
	printf("%d\n",a*b+b*c+c*a-a-b-c+1);
}
```

---

## 作者：封禁用户 (赞：2)

## CF216A Tiling with Hexagons

[原题链接](https://www.luogu.com.cn/problem/CF216A)

## 分析

将每个正六边形看做单位面积，对于求不规则图形面积的问题，考虑将其分割为规则图形求解。图和一篇题解相同：
![](https://cdn.luogu.com.cn/upload/image_hosting/7q10mrzh.png)

六边形被分割成三个平行四边形。第一个面积为 $4\times3=12$，第二个为 $4\times2=8$，第三个为 $3\times2=6$，这时除三条线交点外每条线上的点被重复计算一次，减去 $(4+3+2)$，再加上三条线的交点。根据三量容斥原理，得出公式 $ab+bc+ca-(a+b+c)+1$。

## Code
```cpp
#include<iostream>
using namespace std;
int main(){
	int a,b,c;cin>>a>>b>>c;
	cout<<a*b+b*c+a*c-(a+b+c)+1;
	return 0;
}
```


---

## 作者：Burnside (赞：2)

**可以考虑割补法。**

因为是六边形，考虑是一个大三角形减去三个小三角形构成的。

设$f_i$代表$i$层的正三角形的正六边形个数。

然后割补就可以了。

结果为$f_{a+b+c-2}-f_{a-1}-f_{b-1}-f_{c-1}$，就可以了。

下面是代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
template<typename sp>
inline void qread(sp &x){
	char ch=getchar(),lst=' ';
	while(ch<'0'||ch>'9') lst=ch,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	if(lst=='-') x=-x;
}
int a,b,c;
int f[3005];
int main(){
	for(register int i=1;i<=3000;i++) f[i]=f[i-1]+i;
	a=b=c=0;
	qread(a);qread(b);qread(c);
	printf("%d\n",f[a+b+c-2]-f[a-1]-f[b-1]-f[c-1]);
	return 0;
}
```

快读是因为设置为了新建的时候自动补全，不是刻意写的。

~~其实输入三个数也不需要快读~~

---

## 作者：皮卡丘最萌 (赞：1)

蒟蒻发一个新的解法。

考虑到这个不规则六边形具有多层，所以可以分别计算每一层的数量再求和。

例如样例2,3,4，最外面一层就有12个，个数为(a+b+c)×2-6。

这个公式就是把6个边的个数都加起来再减去角上重复的6个。

但是这个公式在a,b,c中有1个为1时就不适用了，这个时候需要特判，把这一圈看做一个长方形。假设此时A=1，那么直接加上b×c即可。

值得注意的是这里每一次计算时a,b,c只需要减1，而不是减2.

这样这个算法的时间复杂度就为O(min(a,b,c))，虽然没有O(1)来的快，但是更加易懂。

放代码：
```pascal
var s,a,b,c:longint;
begin
readln(a,b,c);
while (a>0)and(b>0)and(c>0) do
  begin
  if (a=1) then begin s:=s+b*c; break; end;
  if (b=1) then begin s:=s+a*c; break; end;
  if (c=1) then begin s:=s+a*b; break; end;
  s:=s+(a+b+c)*2-6;
  dec(a); dec(b); dec(c);
  end;
writeln(s);
end.
```


---

## 作者：Lish_Xizse (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF216A)

这是不错的一道题。

------------
这题不是很难，关键是在于怎么想。

单看图形求它的面积是求不出来的，因为不保证是正六边形。那我们就得换一个思路。

我们可以采用**分割**这种方法。但问题在于：怎么割？

我们可以先想想看，题目样例给了三个数据，那我们是不是可以利用这三个数据将六边形分成三份呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/xt6so122.png)

可以采取这样的分。这样分的话就可以使整个正六边形分成三个平行四边形，也正好可以利用 ```a``` 、 ```b``` 、 ```c``` 这三个数据求解。

接下来我们来计算每一个平行四边形的面积。根据小学学过的平行四边形面积公式，很容易得出三个平行四边形的面积分别为 ```a*b``` 、```a*c``` 、```b*c``` 。

然后你以为这样就完了吗？

***并没有！***

经过仔细的观察，每个平行四边形与另外两个平行四边形都有共同的一个边，我们不能重复的将这一些边算上，而必须得减去这些边的长度，所以还要减去 ```a```      、```b``` 、```c``` 。不只是这样，我们发现这三个平行四边形中含有共同的交点，因为不能重复，所以还要减去一。

综上所述，我们得到了：

```cout << a*b+b*c+a*c-a-b-c+1 << endl;```

这就应该很好理解了吧？



------------
### 完整 ```AC``` 代码:

```
#include<iostream>
using namespace std;
int a,b,c;
int main(){
    cin >> a >> b >> c;
    cout << a*b+b*c+a*c-a-b-c+1 << endl;
    return 0;
}
```


---

