# Cupboard and Balloons

## 题目描述

一个名叫 Xenia 的女孩有一个从前面看起来像弧形的橱柜。这个弧形由一个半圆形顶部（半径为 $r$）和两个高度为 $h$ 的侧壁构成。橱柜的深度为 $r$，也就是说，从侧面看起来像一个底边为 $r$，高度为 $h+r$ 的矩形。下图显示了橱柜的外观（左侧是前视图，右侧是侧视图）。

Xenia 在她的生日上得到了很多气球。这个女孩讨厌凌乱，所以她想把气球存放在橱柜里。幸运的是，每个气球都是半径为 $\frac{r}{2}$ 的球体。帮助 Xenia 计算她可以放入橱柜的最大气球数量。

如果在左侧或右侧视图中看不到气球的任何部分，可以说一个气球在橱柜里。橱柜里的气球可以彼此接触。不允许挤压气球或以任何方式变形气球。可以假设橱柜的墙壁非常薄，可以忽略不计。

## 样例 #1

### 输入

```
1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 1
```

### 输出

```
2
```

# 题解

## 作者：MagicLyney_06 (赞：3)

### 前言

这道题的中文题面是我翻译的>_<。

### 分析

首先，显而易见这个图形的宽只能让你塞一个进去。所以我们可以把这个问题变成在一个半圆加长方形的平面图形上塞圆。

我们将其拆分为两部分（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/fhqwmg34.png)

下面的长方形部分的长为 $a = \lfloor h \div r\rfloor \times r$。显然，直接往里面塞 $a\div r \times 2$ 即可。重点是上面的不规则图形。首先，我们易得，上半部分最少塞下 $1$ 个圆，最多只能塞下 $3$ 个圆。我们来看看塞三个圆的最低要求(图为手画，丑请见谅)：

![](https://cdn.luogu.com.cn/upload/image_hosting/bty2loen.png)

可以得知上半部分的最低高度也应该为 $\frac{\sqrt{3}}{2}r+r$。同理可得，放两个圆的情况下，最小两个并排圆的圆心都应该在长方形的上边上，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/41q0dm35.png)

同样可以得出，上半部分的高度最低也应为 $\frac{3}{2}r$ $(\text{半圆 }r+\text{残余长方形 }\frac{r}{2})$。

至此，我们已经得出了关于不规则部分的计算方法。令其高度减掉半圆部分(相当于不等式两边同时减掉 $r$)为 $h'$:

- 若 $h'\ge \frac{\sqrt{3}}{2}r$，则 `ans+=3`。
- 若 $h'<\frac{\sqrt{3}}{2}r\text{ 且 }h'\ge \frac{1}{2}r$，则 `ans+=2`。
- 否则，直接 `ans+=1`。

最后答案再加上最开始长方形中的答案即为最终答案。

### 代码

```cpp
//
// Created by lndff on 2023/11/03
//
#include <bits/stdc++.h>
using namespace std;
int r, h, ans = 1;\\ans初始化为1，因为无论如何至少都塞一个
int main(){
	cin >> r >> h;
	ans += (h / r) << 1;\\长方形中的答案
	if (h % r * 2.00 >= 1.00 * r * sqrt(3)) ans += 2;\\塞三个。同时变除为乘，避免失精
	else if (h % r * 2 >= r) ans += 1;\\塞两个
	cout << ans;
}
```



---

## 作者：lukelin (赞：3)

### 前言
**安利一下我的cnblog:**  
[更好的阅读体验](https://www.cnblogs.com/linzhengmin/p/11180938.html)
### 题解
这道题目是一个简单的贪心。  
首先毋庸置疑，柜子的下半部分是要放满的。  
于是我们很容易想到，分以下三种情况考虑:  
![](https://i.loli.net/2019/07/13/5d298596850e139376.bmp)  
$$\small\text{请不要盗图，如需使用联系博主}$$  
我们考虑如何辨别情况，不妨设$m\ \%\ r$为$\ left$，如果$left < \frac{r}{2}$，那么显然当前的情况是1；如果$\frac{r}{2} \leq left<\frac{\sqrt{3}r}{2}$，那么显然当前的情况是2；如果$\frac{\sqrt{3}r}{2} \leq left$那么显然当前的情况是情况3。  
那么实现起来就很简单了。  
首先计算$\frac{m}{r}$，然后对于情况几就加上几。  
### 代码
```cpp
#include <cstdio>
#include <cmath>

int main(){
	int r, h; scanf("%d %d", &r, &h);
	int lft = h % r, ans = (h / r) * 2 + 1;
	if (lft >= (double)(r) / 2.0 * sqrt(3)) ans += 2;
	else if (lft >= (double)(r) / 2) ++ans;
	printf("%d", ans);
	return 0;
}
```

---

## 作者：lilong (赞：1)

显然，每一层恰好能放下两个球（事实上这也是最优的方案），那么下面一共可以放 $\lfloor \frac{h}{r} \rfloor \times 2$ 个球，剩余 $h - \lfloor \frac{h}{r} \rfloor \times r+r$ 的高度，记 $h'=h-\lfloor \frac{h}{r} \rfloor\times r$ 为立方体部分剩余高度。最上面至少能放 $1$ 个球，至多 $3$ 个。分类讨论：

- 如果放 $3$ 个，则必须满足 $\frac{\sqrt{3}}{2}r+r\le h'+r$，即 $\frac{\sqrt{3}}{2}r\le h'$。此时三个球的球心构成等边三角形。
- 如果放 $2$ 个，则两个球的球心必须在半圆形直径以下，即 $\frac{r}{2}\le h'$。
- 否则只能且一定放 $1$ 个球（半圆形完全没有占用，肯定放得下）。


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    int h,r,ans=0;
    cin>>r>>h;
    ans=h/r;
    h-=ans*r;
    ans*=2;
    if((double)h*h>=(double)0.75*r*r)ans+=3;
    else if((double)h>=(double)0.5*r)ans+=2;
    else ans++;
    cout<<ans;
    return 0;
}
```

---

## 作者：丧黑福造 (赞：0)

题意：给定一个$r$和$h$，$r$是半圆的半径，$h$是圆柱的高度，然后有一些，问最多能放多少个半径为$r/2$的气球。

分析：贪心的思路，先从下往上放，两个两个放，放到不能放时，再计算上面是不是还能再放一个。这样是最多的，关键是计算上面那能不能放上，用到几何中的两圆的位置关系。

后面的内容题解已有详细说明了，这里不再赘述（~~其实是我不懂~~

---

## 作者：泠小毒 (赞：0)

# Cupboard and Balloons
给定r和h，有一个立体图形

下部为宽r，长2r，高h的矩形

上部为宽r，正面为半径为r的半圆的立体图形

具体就看下面的图啦
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/luogu-cf342c/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/luogu-cf342c.html)
## 解法
![](https://muronglin.yes1.cn//wp-content/uploads/p.png)

如图，我们可以看到，一种情况是下面都两个两个填，最上面能填两个

还有一种是下面填不到两个，只能上面填一个

最后一种是最上面填了三个

那怎么判断呢

首先，最上面的部分，至少能填一个在正中间的

然后我们判断一下是否可以从一个变成两个，这样明显优一点

我们考虑到当最底下的都填完之后，会剩下一部分，多余的```mo=h-h/r*r```

当mo>r/2的时候，就可以在中间填两个

如果能填两个，再考虑能否在中间加入第三个

我们看第三幅图，当AB>=r时，就可以填入第三个

即AC^2+BC^2>=r^2

AC=r/2,BC=mo

全部带进去，化简过程在代码底部也有

就可以求出来了
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int r,h,ans,mo;
int main()
{
	scanf("%d%d",&r,&h);
	ans=h/r*2+1;
	mo=h-h/r*r;
	if(mo*2>=r)
	{
		ans++;
		if(1ll*4*mo*mo>=1ll*3*r*r)ans++;
	}
	printf("%d\n",ans);
    return 0;
}
/*
mo^2+(r/2)^2>=r
4*mo^2+r^2>=4*r^2
4*mo^2>=3*r^2
*/
```

---

