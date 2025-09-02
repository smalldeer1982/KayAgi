# [USACO5.1] 圈奶牛Fencing the Cows /【模板】二维凸包

## 题目背景

upd: 新增一组 hack 数据。

## 题目描述

农夫约翰想要建造一个围栏用来围住他的奶牛，可是他资金匮乏。他建造的围栏必须包括他的奶牛喜欢吃草的所有地点。对于给出的这些地点的坐标，计算最短的能够围住这些点的围栏的长度。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$-10^6 \leq x_i, y_i \leq 10^6$。小数点后最多有 $2$ 位数字。

## 样例 #1

### 输入

```
4
4 8
4 12
5 9.3
7 8```

### 输出

```
12.00```

# 题解

## 作者：ShineEternal (赞：1247)

### 注：这原本是一篇日报，但由于没通过一怒之下交成题解（大雾



# 0.前言：

本篇文章，是一位 OI 选手无私的馈赠。两道凸包例题，五种凸包算法，涵盖了平面凸包从入门到进阶的大部分套路。作者相信，这篇漂亮的博客，可以给拼搏于 OI 的逐梦之路上的你，提供一个有力的援助。

## 特别鸣谢：

- 画图：主要提供比较细的连线

- 画图3D：主要提供描点及文本框

杜绝网上搜图，图片纯手画~~累死我了~~


# 1.引入：
假设一个操场上有一些小朋友，下面是航拍视角：
![](https://i.loli.net/2019/08/15/XBc1gIyiFqrpbfG.png)

现在他们要围一个球场做游戏。

因为老师比较懒，所以就只能麻烦一些小朋友了（他们自己撑着绳子防止球滚出去）


而小朋友又不动脑子。所以就只能麻烦你来出主意了。

显然，最简单的方法是这样：

![](https://i.loli.net/2019/08/15/QnFIRfp9AkaLE4X.png)

先把一圈大绳子放在外面，然后往里缩，直到：

![](https://i.loli.net/2019/08/15/2P5nKDeSzZpXyxB.png)

最外圈的小朋友撑起了绳子。

此时黑线围成的多边形的顶点就是最外圈小朋友所在的位置。

### 由此，**我们就定义黑线围成的图形为一个平面凸包**

那么，换一种定义方式，我们就定义：

**平面凸包是指覆盖平面上n个点的最小的凸多边形。**

当然，我们发现在程序中却无法模拟此过程，于是有了下文的诞生。

# 2、斜率逼近法

**其实这也是一种容易想到的算法，但是并不常用（代码复杂度高），我们稍作了解**



然后我们可以把这个思路具体化：

![](https://i.loli.net/2019/08/15/9DukMvbVAZ5XglE.png)

![](https://i.loli.net/2019/08/15/Bb7wdgMAnvFOfQU.png)

（k是斜率）

- (1)首先在所有点中找出一个y值最小的点，记为$P_1$
- (2)从$P_1$出发，刚开始k=0，即为水平状态。然后按照上图的示意沿逆时针方向寻找。即开始在$k>0$且$(x_2>x1,y_2>y_1)$中找k最小的点$P_2$，以此类推。


Q:如果过程中有多个点符合要求怎么办？

A:那么就取距离$P_1$最远的点，因为这样能保证划定的范围最大。


- （3）从$P_2$出发，用（2）的方法找$P_3$

- (4)最后直到$P_m=P_1$为止（已形成凸包）。

Q:为什么要刚开始找y值最小的点？

A:结合刚开始的小朋友拉绳子可知，我们在下面的绳子一定会被y值最小的小朋友挡住，即他一定在凸包上，于是就以他为基准来操作。


Q:万一最后没有一个$P_m$使得$P_m=P_1$呢？

A:易证必有，平面凸包总是存在的。


**时间复杂度：O(nm)** 

n为所有小朋友的数量，m为舍己为人的小朋友的数量。


说到这里大家都明白了，一但凸包上的两个点的斜率趋于无穷大，那么就无法解决了。

于是~~窝的日报又能进行下去了~~有人就提出了一种新的方法。

# 3、Jarvis算法

这其实是一种数学构造法

我们还是把那群小朋友~~骗~~聘过来：

![](https://i.loli.net/2019/08/15/XBc1gIyiFqrpbfG.png)

我们考虑让一个小朋友手里拿着一根棒子：

![](https://i.loli.net/2019/08/15/2Yabz8PtJ3TC9Xf.png)


从外往里旋转。


然后会~~撂倒~~碰到另一个小朋友：

![](https://i.loli.net/2019/08/15/rtSldAhkbTmU8gD.png)

然后我们让被棒子碰到的小朋友再取一根棒子~~继续打人~~，重复以上操作。

![](https://i.loli.net/2019/08/16/jXep1bG3nYdsTQv.png)

就是这样。

但如果遇到以下情况：

![](https://i.loli.net/2019/08/16/u7hSdUOgAriNQL3.png)

有的小朋友在旋转棍子时同时碰到了多于一个点（即三点共线），那么显然我们需要选择最远的点。

不难证明，这样下来也可以围成一个平面凸包。

**以上是定向的想象，那么下面就来严谨的说明一下**

描述如下：

![](https://i.loli.net/2019/08/15/6O4tPXh2kYHUBcp.png)



- 首先找到一条直线$l$过其中一点A，使得所有其他的点都在$l$的同一侧。

这种直线显然一定能找到。

由此也易证A一定为凸包上一点。

- 让直线$l$以A为轴点沿顺时针或逆时针方向旋转，直到抡到除A以外的一点B

别忘了上面那个~~形象的~~讲述，在遇到多于一个点时要取最远的。

- 重复以上操作，直到l碰到A点。


在过程中~~受伤~~被碰到的点就构成了平面凸包的顶点序列。


**在此过程中，虽然我们发现上述过程仍然不太好实现，但是我们还是可以通过一系列的玄学转换得到**

我们考虑到B点是最先碰到的，那么新的直线$l'$必然在A和除B及自身以外其他点的连线中与$l$的夹角最小

![](https://i.loli.net/2019/08/15/2clsNh7ZWP3EyCe.png)

即紫∠比红∠大

那么在下图中：
![](https://i.loli.net/2019/08/15/Z61zwH5beDI9fmE.png)


$if(\vec {AP}\times \vec {AP_i})z>0$

则$\vec {AP}$到$\vec {AP_i}$的旋转为逆时针旋转。

显然，$\vec {AP_i}$与l的夹角比$\vec {AP}$的更接近。为更好的答案。

$else$

$if(\vec {AP}\times \vec {AP_i})z=0$

那说明A，P，$P_i$三点共线，自然取最远的。


我们按这个顺序扫描所有的点，就能找到这个凸包上的一条边。

显而易见：此时间复杂度为$O(nm)$，即每次扫n个点，一共m次可构成凸包。

但是。。。这个时间复杂度还是会凉。。。

假设就是[这道题](https://www.luogu.org/problem/P2742),那么我们观察到$n\leq 10000$,这是一道平面凸包的模板题，但是如果数据构造到m=n甚至和n相差不大的情况，那就会轻而易举的超时。

可见，此算法仅仅适用于随机点集，对于刻意构造的数据就会被卡成$O(n^2)$

而毒瘤的OI怎么会不卡呢？

**连模板题都过不了，看来这个算法还是得优化，所以我们还是得用保险的算法，于是**

# 4、Graham算法

本质：

> Graham扫描算法维护一个**凸壳** 通过不断在**凸壳**中加入新的点和去除影响凸性的点 最后形成**凸包**

**至于凸壳：** 就是凸包的一部分

算法主要由两部分构成：

- 排序

- 扫描

## （1）排序

我们的Graham算法的第一步就是对点集进行排序，这样能保证其有序性，从而在后续的处理中达到更高效的效果，这也是Graham算法更优的原因。

开始操作：

- 我们还是选择一个y值最小（如有相同选x最小）的点，记为$P_1$

- 剩下的点集中按照极角的大小逆时针排序，然后编号为$P_2$~$P_m$

![](https://i.loli.net/2019/08/15/HDJxANk8IqrWcE1.png)

~~达成成就：种草达人~~


**另外再介绍一个求极角的黑科技：atan2(a[i].y,a[i].x)**

- 我们按照排序结束时的顺序枚举每一个点，依次连线，这里可以使用一个栈来存储，每次入栈，如果即将入栈的元素与栈顶两个元素所构成了一个类似于凹壳的东西，那么显然处于顶点的那个点一定不在这个点集的凸包上，而他正好在栈顶，所以把它弹出栈，新点入栈。


但是，新来的点有可能既踢走了栈顶，再连接新的栈顶元素后却发现仍然可以踢出，此时就不能忘记判断。

**怎么样，感觉这个算法如何？**

如果您不想纠缠于繁杂的文字描述，那么下面就有精美图片解说献上。

（ps:下列解说中右转左转等是指以上一条连线为铅垂线，新的连线偏移的方位）

---

刚开始，我们的点集是这样的：

![](https://i.loli.net/2019/08/15/Bb7wdgMAnvFOfQU.png)


其中p1为起始点

---

然后p2准备入栈，由于栈中元素过少，所以检验合格，可直接进入。
![](https://i.loli.net/2019/08/15/yr3DfaXxniphWeV.png)

----

之后因为p3仍为向左转，符合凸包条件，所以暂时先让它进去
![](https://i.loli.net/2019/08/15/gClxn32NtVzSmdh.png)

---

p4出现了右转现象，那么我们就把顶点p3舍去，在检查p2的性质，合格

于是p3出栈，p4入栈

![](https://i.loli.net/2019/08/15/oxuORKXyEe9mZJr.png)

---

p5一切正常，入栈。


![](https://i.loli.net/2019/08/15/RklQONoGefSZWtp.png)

----

p6这里就要复杂一些

- 首先他往右转，于是将p5弹出

![](https://i.loli.net/2019/08/15/l1UNp8JOwdzsXjr.png)



- 又发现他相对于$P_2P_4$向右转，于是将p4弹出
![](https://i.loli.net/2019/08/15/Fb1oxSCfUPQAH72.png)

之后p6进栈。


----

p7一切正常（左转），入栈

![](https://i.loli.net/2019/08/15/NgsRaDyeihFAZIU.png)

----

p8一切正常（左转），入栈

![](https://i.loli.net/2019/08/15/1jTXsYq5vgApoWE.png)

---


所以说最后就连到了起点p1。
![](https://i.loli.net/2019/08/15/JOCRuSFGBYeLTEc.png)



由此，我们的Graham算法的全过程就结束了。

凸包形成（即绿线所围的多边形）


扫描的时间复杂度：$O(n)$

但是显然不可能做到这么优秀.

于是还有排序的时间复杂度：$O(nlogn)$


合起来总的时间复杂度：$O(nlogn)$


**可见，我们在排序的帮助下省去了一些盲目的扫描，虽然排序作为一个预处理时间复杂度占据了总时间复杂度，但相比前一个算法还是更为优秀**


现在我们到模板题上来。

[P2742 【模板】二维凸包 / [USACO5.1]圈奶牛Fencing the Cows](https://www.luogu.org/problem/P2742)


### 题意简叙：

求一个点集凸包的边长和。

### 分析：
平面凸包模板题，注意浮点数之类的别弄丢精度就行，其他直接套模板,代码里有注释，我用的是手写栈，（这样能快一些？

### code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
struct ben
{
    double x,y;
}p[10005],s[10005];
double check(ben a1,ben a2,ben b1,ben b2)//检查叉积是否大于0，如果是a就逆时针转到b 
{
    return (a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
}
double d(ben p1,ben p2)//两点间距离。。。 
{
    return sqrt((p2.y-p1.y)*(p2.y-p1.y)+(p2.x-p1.x)*(p2.x-p1.x));
}
bool cmp(ben p1,ben p2)//排序函数，这个函数别写错了，要不然功亏一篑 
{
    double tmp=check(p[1],p1,p[1],p2);
    if(tmp>0) 
		return 1;
    if(tmp==0&&d(p[0],p1)<d(p[0],p2)) 
		return 1;
    return 0;
}
int main()
{
	
    scanf("%d",&n);
    double mid;
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&p[i].x,&p[i].y);
        if(i!=1&&p[i].y<p[1].y)//这是是去重 
        {
            mid=p[1].y;p[1].y=p[i].y;p[i].y=mid;
            mid=p[1].x;p[1].x=p[i].x;p[i].x=mid;
        }
    } 
    sort(p+2,p+1+n,cmp);//系统快排 
    s[1]=p[1];//最低点一定在凸包里 
    int cnt=1;
    for(int i=2;i<=n;i++)
    {
        while(cnt>1&&check(s[cnt-1],s[cnt],s[cnt],p[i])<=0) //判断前面的会不会被踢走，如果被踢走那么出栈
			cnt--;
        cnt++;
        s[cnt]=p[i];
    }
    s[cnt+1]=p[1];//最后一个点回到凸包起点
    double ans=0; 
    for(int i=1;i<=cnt;i++) 
		ans+=d(s[i],s[i+1]);//然后s里存好了凸包序列，只需要把两两距离累加就行
    printf("%.2lf\n",ans);
    return 0;
}
```

# 4、例题：
## 信用卡凸包

[P3829 [SHOI2012]信用卡凸包](https://www.luogu.org/problem/P3829)

是一道上海的省选题，不过并不难。

### 题意简叙：

![](https://cdn.luogu.com.cn/upload/pic/6549.png)

给你一堆如上图所示的卡片，求其凸包周长（凸包可以包含圆弧）

### 分析：
我们可以先来考虑$r=0$的情况。

发现$r=0$即为信用卡为矩形，于是就按照正常的思路将点列出跑Graham算法即可。

---

然后开始想正解


因为样例三是最普遍的情况，所以研究一下：

![](https://i.loli.net/2019/08/15/kVngAqUotbxI4RY.png)

首先带有圆弧的凸包不好处理呢。


于是我们把每一个被磨圆的顶角往圆心里看，再重新构造凸包，然后发现黑色内圈与绿蓝外圈有重叠部分。

再分解一下，如红笔。

**发现恰好多出4个$\frac{1}{4}$圆弧，也就是一个圆**

再验证几个发现也是对的。

于是这个问题就转换为裸的凸包模板了。

#### 这种题目里面都告诉凸包了，关键在于怎么转换，不然生搬硬套，很难得分

# 5、Andrew算法
（评论区里一个大连提出了这个补充，于是添加一下QAQ）



### 主体思路：

- 按照x优先的顺序排序（坐标从小到大）

- 从第一个点开始遍历，如果下一个点在栈顶的两个元素所连成直线的左边，那么就入栈；


- 否则如果在右边，说明凸包有更优的方案，上次的点出栈，并直到新点在栈顶两个点所在的直线的左边为止

显然文字解释仍然是枯燥的，那么下面还是手动绘图感受一下~~我的妈呀累死我了~~

---

以下就是两种算法的排序不同

![](https://i.loli.net/2019/08/15/HDJxANk8IqrWcE1.png)

我来分割一下--------------------------------------------------------------------------------------------------------

![](https://i.loli.net/2019/08/16/oH6QD9cOjePRLKJ.png)

可以看出两种算法的排序不同，Andrew算法排序更简单，按x，y坐标排序，时间复杂度也更低（一般的坐标系中排序方法）。

---

第一步：将前两个点入栈

- 首先p1一定是在凸包顶点上的。

- p2可能在，也可能不在，等着之后判断

~~为了我也不知道什么原因我把黑的坐标轴给去掉了~~

![](https://i.loli.net/2019/08/16/JzgruwljLCMxPtA.png)

---

p3偏左，入栈

![](https://i.loli.net/2019/08/16/NqEmBoKMD8wueH4.png)

---

p4和p3连线，发现偏右，于是p3出栈，检查p2正常，于是p4再入栈

![](https://i.loli.net/2019/08/16/GhHVMy2pEK8t5rN.png)

--- 

和上面的同理；

于是p4出栈，p5入栈


![](https://i.loli.net/2019/08/16/c9JulEn4TbiZGN8.png)

---

p5出栈，p6出栈

![](https://i.loli.net/2019/08/16/xIA8hEbmp4MJsd7.png)


---

p6出栈，p7入栈
![](https://i.loli.net/2019/08/16/uvSw4FJCeVzc1HY.png)

---


p8一马平川的入栈
![](https://i.loli.net/2019/08/16/yxEReiQUKjoP5C2.png)


---

### 然后我们惊讶的发现：
凸包明明还空一半就到头了。

![](https://i.loli.net/2019/08/16/yPMRhSHg1VCZzbk.jpg)

**然鹅这其实是在意料之中的**

我们这种算法必然会只算出一半的凸包。

- 如果你按照本文的方法行动，那就是一个下凸包

然后上凸包我想你已经知道怎么处理了

### 那下面就揭晓答案：

我们再从排序末尾的点（也就是p8）出发，按照一模一样的方式再往前遍历就行。

如图。

从8~1走。

当然走过的节点就没有必要再走了（除了p1）

- 先走到p6

![](https://i.loli.net/2019/08/16/pHo8XGwLM6lY9yE.png)

---

再到p5，发现我们可以把p6给踢掉了。

- p6出栈，p5入栈



![](https://i.loli.net/2019/08/16/6zBI7FOjU1sGZyd.png)


---

然后p5到p4

- 这里可能画的不是很清楚，其实是不共线的

- 如果共线也好处理，直接取最长的哇
![](https://i.loli.net/2019/08/16/wZnWSoljaF569e4.png)

---

出现了p3！！！

- 他首先把p4给请出去了


![](https://i.loli.net/2019/08/16/YrJa9lRGnFT7ket.png)

---

- 然后又把p5给请出去了
![](https://i.loli.net/2019/08/16/PVdyC6vqItiljFO.png)


总结：p4，p5出栈，p3入栈

---

最后p3连到p1，画上了一个圆满的~~句号~~凸包
![](https://i.loli.net/2019/08/16/y56l1aYXexzUNFi.png)


### 以上就是Andrew算法全过程QAQ

扫描的时间复杂度：$O(n)$（已过滤常数）


排序时间复杂度：$O(nlogn)$

#### 总时间复杂度：$O(nlogn)$



## code:

```cpp
double Cross(vec A, vec B)
{
    return A.x*B.y-A.y*B.x; //A->B左转为正 
}
double Side(vec a, vec b, vec p) //次栈顶元素a，栈顶元素b，新增点p 
{
    vec A=vec(b.x-a.x,b.y-a.y); //向量ab
    vec B=vec(p.x-a.x,p.y-a.y); //向量ap
    return Cross(A,B);
}
int Andrew(int top)
{
    sort(p+1,p+n+1);
    if(n<3) 
	{
        printf("-1\n");
        return;
    }
    st[0]=p[1],st[1]=p[2];
    top=1;
    for (int i=3;i<=n;i++)//从p1开始的下凸包 
	{
        while(top&&Side(st[top-1],st[top],p[i])<=0)
            top--;
        st[++top]=p[i];
    }
    st[++top]=p[n-1];
    for(int i=n-2;i>=1;i--)//从pn开始的上凸包 
	{
        while(top&&Side(st[top-1],st[top],p[i])<=0)
            top--;
        st[++top]=p[i];
    }
    return top;
}
```

# 6、后记：

不管怎样，这一篇日报居然写完了，虽然这种算法考察在noip中不常见，但最近风云变幻，谁知道以后会出什么题，但现在把整个算法的各种变形都推得明明白白还不如复习好之前的算法，所以我们到目前把模板掌握，避免考试出板子时却手足无措的情况发生就行。


- 配图十分不易，讲解努力详细，望您不吝赐赞

---

## 作者：Sagittarius (赞：113)

如果你是大牛，请移步下方其他题解orz本题解写给对凸包怀有恐惧的小萌新们【无歧视意】。get到凸包的生成过程后，凸包应该还是很好理解的。

凸包是啥？就是给你一堆点，然后用一根有弹性的橡皮筋包住所有的点，这个橡皮筋就是一个凸包。如图：

![](https://cdn.luogu.com.cn/upload/pic/26590.png)


------------
如何求凸包？我们先将点按照X-Y排序（x为第一关键字，y为第二关键字）

![](https://cdn.luogu.com.cn/upload/pic/26592.png)

ABCDEFG

同时我们搞一个栈，记录在凸包中的点。我们的思路是，求出凸包的下半部（AEG），求出凸包的上半部（GFBA），然后合在一起就是凸包了。

我们先搞下半部分，首先按照刚刚的排序把A和B搞进栈。接下来我们遇到了点C。

![](https://cdn.luogu.com.cn/upload/pic/26596.png)

由于我们正在求凸包的下半部分，我们希望这下半部分越往下越好，反映在图上，也就是，斜率越小越好。AC的斜率小于AB，所以把B踢出这个栈，让C入栈。

此时栈中有A,C。

![](https://cdn.luogu.com.cn/upload/pic/26599.png)

下一个点是D，kAD>kAC，因此AD并不能更新AC，C不踢出栈，D入栈。

此时栈中是A,C,D。

![](https://cdn.luogu.com.cn/upload/pic/26600.png)

下一个点是E，因为kCE<kCD，所以E相较于D更优，把D踢出。

此时栈中是A,C。

![](https://cdn.luogu.com.cn/upload/pic/26602.png)

我们又发现kAE<kAC，E也比C更优，因此把C踢出。

栈里只剩下A,E。

![](https://cdn.luogu.com.cn/upload/pic/26603.png)

同上，kAF>kAE，F并不比E优，因此E不出栈，F入栈。

此时栈中是A,E,F。

![](https://cdn.luogu.com.cn/upload/pic/26605.png)

下一个点是G，kEG<kEF，所以把F踢出栈。

![](https://cdn.luogu.com.cn/upload/pic/26607.png)

不过，kAG>kAE，G并不E更优，因此E不出栈，G入栈。

此时栈中：A,E,G。

![](https://cdn.luogu.com.cn/upload/pic/26610.png)

至此，凸包下半部分已经生成完毕。

我们可以发现这个栈满足栈中相邻两点的斜率递增，这就是一个凸包下半部分的形状嘛（斜率从很小慢慢变大）

可以如法炮制生成凸包的上半部分。

总结一下整个过程：

先把所有点按照X-Y排序。【这保证了生成的时候，最左下角的点和最右上角的点都在栈中

```
inline int cmp(node a,node b){
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}

sort(a+1,a+1+n,cmp);
```

求凸包下半部分。从小到大枚举每个点，将这个点入栈。

```
fsb(i,1,n){
	s[++size]=a[i];
```

如果栈的大小大于等于3，则比较这个点和上一个点与上上个点连线的斜率，看能否更新上一个点，如果可以更新则替换之。直到不能替换，或者栈中只有2个点。

```cpp
	while (size>=3&&getk(s[size-2],s[size])<getk(s[size-2],s[size-1])){s[size-1]=s[size];size--;};
}
```

统计凸包下半部分线段长的和

```cpp
fsb(i,1,size-1)ans+=dis(s[i],s[i+1]);
```

求凸包上半部分。同理。

```cpp
size=0;
fbs(i,n,1){
	s[++size]=a[i];
	while (size>=3&&getk(s[size-2],s[size])<getk(s[size-2],s[size-1])){s[size-1]=s[size];size--;};
}
fsb(i,1,size-1)ans+=dis(s[i],s[i+1]);
```
//可以思考一下为什么除了枚举顺序外，其他都不变，比如，为什么两个getk间的也是<号。【从何时更新的角度思考。

然后你就学会了凸包qwq

---

## 作者：Nemlit (赞：17)

## [原文地址](https://www.cnblogs.com/bcoier/p/10519725.html)

人生第一道计算几何题？ 留作纪念$QAQ$

凸包是什么？下图就是一个~~土~~包
![](https://cdn.luogu.com.cn/upload/pic/53802.png)

我们怎么求出凸包呢

我们先把凸包分成上下两个部分

![](https://cdn.luogu.com.cn/upload/pic/53804.png)

如图，红色部分称为上半部分，黑色部分成为下半部分

然后按照x为第一关键字，y为第二关键字排序

于是第一个就会找到最左边的一个最下面的点，第二个就会找到最右边的一个最上面的点

我们以这两个点为分界线，分出上下两个凸包分别求出周长

我们维护一个栈，栈中的元素即为上（下）凸包所有元素

对于下半部分，我们显然要让斜率尽可能地小

我们先把前两个点（分别为AB）入栈，拓展到第三个点（C），若$K_{AC}<K_{AB}$则把C进栈，否则将B弹出并将C进栈，不断弹出直到$K_{AC}>K_{AB}$

而对于上半部分，我们是要让斜率尽可能大

同理，我们先把后两个点（分别为FE）入栈，拓展到第三个点（D），若$K_{FD}<K_{ED}$则把D进栈，否则将E弹出并将D进栈，不断弹出直到$K_{FD}>K_{ED}$

于是我们就可以得到上下两个凸包的所有点，再用距离公式算就可以了，时间复杂度$O(N)$

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define D double
#define inf 123456789
il int read()
{
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define drep(i, s, t) for(re int i = t; i >= s; -- i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
#define maxn 10005
struct node{D x, y;}e[maxn];
int n, st[maxn], top;
D ans;
//il D ff(int x){return x * x;}
#define ff(x) (x) * (x)
il bool cmp(node a, node b){return a.x == b.x ? a.y < b.y : a.x < b.x;}
il D dis(int x, int y){return sqrt(ff(e[x].x - e[y].x) + ff(e[x].y - e[y].y));}
il D getk(int x, int y){return e[x].x == e[y].x ? inf : (e[x].y - e[y].y) / (e[x].x - e[y].x);}//注意这里一定要判断两个x相等的情况
int main()
{
	n = read();
	rep(i, 1, n) scanf("%lf%lf", &e[i].x, &e[i].y);
	sort(e + 1, e + n + 1, cmp);
	rep(i, 1, n)
	{
		st[++ top] = i;
		while(top > 2 && getk(st[top], st[top - 2]) < getk(st[top - 1], st[top - 2])) 
			st[top - 1] = st[top], -- top;
	}
	rep(i, 1, top - 1) ans += dis(st[i], st[i + 1]);
	top = 0;
	drep(i, 1, n)
	{
		st[++ top] = i;
		while(top > 2 && getk(st[top], st[top - 2]) < getk(st[top - 1], st[top - 2])) 
			st[top - 1] = st[top], -- top;
	}
	rep(i, 1, top - 1) ans += dis(st[i], st[i + 1]);
	printf("%.2lf", ans);
	return 0;
}
```

---

## 作者：Shunpower (赞：3)

提供一个真正意义上的 Graham 算法求解凸包。题解区里目前有的题解都是用 Andrew 算法把上下凸壳分开做，这样太麻烦了。

考虑我们先找出所有点当中 $x$ 坐标最小，其次 $y$ 坐标最小的点 $P$。显然这个 $P$ 是一定在凸包中的。然后我们尝试从 $P$ 开始走凸包上的点。

因为 $P$ 是凸包的最左侧，所以比较显然的性质是：从它开始顺时针遍历凸包上的点，凸包上的点和 $P$ 的连线的斜率一定是逐渐变小的。

于是我们可以按照斜率从大到小排序。如果你对计算几何有所了解，也可以直接使用极角排序。特别地对于共线的点，需要把距离 $P$ 更近的放在前面，因为共线的点如果都在凸包上那么一定是离 $P$ 更近的出现在前面。

极角排序后考虑从左到右扫描点，维护一个单调栈表示现在的凸壳。考虑凸包的等价条件是任何一个内角都小于等于 $\pi$，这意味着对于任意按照顺时针顺序相邻的三个点 $A,B,C$ 总是有 $\overrightarrow{AB}\times \overrightarrow{BC}\le 0$。通俗地说就是 $\overrightarrow{BC}$ 总是在 $\overrightarrow{AB}$ 的顺时针方向，我们沿着凸包顺时针行走是始终“右拐的”。

于是直接考虑加入新点，如果能满足叉积就加入凸壳，否则弹出凸壳中的最后一个点。显然弹出的点不可能在凸壳上，并且必然会被新的凸壳所包含在凸包内。

代码比做两遍要清新不止一点半点。

```cpp
int n;
struct Point{
	double x,y,ang;
} p[N];
double dis(Point a,Point b){
	return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}
int stk[N];
int top;
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n;
	fr1(i,1,n) cin>>p[i].x>>p[i].y;
	fr1(i,2,n){
		if(p[i].x<p[1].x||(p[i].x==p[1].x&&p[i].y<p[1].y)){
			swap(p[i],p[1]);
		}
	}
	fr1(i,2,n){
		p[i].ang=atan2(p[i].y-p[1].y,p[i].x-p[1].x);
	}
	sort(p+2,p+n+1,[](Point &x,Point &y){
		if(x.ang==y.ang) return dis(p[1],x)<dis(p[1],y);
		return x.ang>y.ang;
	});
	stk[1]=1,stk[2]=2;
	top=2;
	fr1(i,3,n){
		while(top>=2&&cross({p[stk[top]].x-p[stk[top-1]].x,p[stk[top]].y-p[stk[top-1]].y},{p[i].x-p[stk[top]].x,p[i].y-p[stk[top]].y})>0) top--;
		top++;
		stk[top]=i;
	}
	int lst=1;
	double ans=0;
	fr2(i,top,1){
		ans+=dis(p[stk[i]],p[lst]);
		lst=stk[i];
	}
	cout.setf(ios::fixed);
	cout<<setprecision(2)<<ans<<'\n';
	ET;
}
```

---

## 作者：Little_Deer_Peach (赞：2)

题意：求出一个凸包并算出它的周长。

首先我们要求凸包，需要知道什么是凸包。凸包就是可以覆盖平面中 $n$ 个点的最小矩形。专业一点的定义就是：在平面上能包含所有给定点的最小凸多边形叫做凸包（选自 OI-WIKI）。

求凸包有两种常用的方法，Graham 扫描法和 Andrew 算法。

先讲 Graham 扫描法（因为作者先学会这个方法）。这个方法的主要思路是先找到纵坐标最小的点 $P$，然后将所有点相对于点 $P$ 的极角从小到大排序。显然的，点 $P$ 一定是凸包中的一点。

如图所示是一个平面上的 $n$ 个点：

![pVElD91.png](https://s21.ax1x.com/2025/06/16/pVElD91.png)

找到点 $P$ 后除点 $P$ 外所有点按极角逆时针排序：

![pVElJXT.png](https://s21.ax1x.com/2025/06/16/pVElJXT.png)

接下来讲实现过程，按照极角排序后的顺序是 $ABCDE$。我们可以用栈存储凸包上的点，越是离栈顶近的点是越后面加入的，依次连接栈顶的点和当前点，如果发现当前连线与栈顶前两个点连线相比是向右转的（可以用叉积），显然最后形成的图形并不是一个凸包（因为按逆时针遍历点，所以向右转最后形成的不是凸包），弹出栈顶点并继续比较，知道连线是向左转或栈内只剩一个点时才加入当前点。开始可以先将点 $P$ 加入栈。

点 $P$ 连点 $A$，因为栈内只有一个点，直接加入点 $A$。

![pVEltnU.png](https://s21.ax1x.com/2025/06/16/pVEltnU.png)

连接点 $A$ 和点 $B$，因为是向左转，所以加入点 $B$。

![pVElU74.png](https://s21.ax1x.com/2025/06/16/pVElU74.png)

连接点 $B$ 和点 $C$，因为向左转，所以加入点 $C$；连接点 $C$ 和点 $D$，因为向右转，所以弹出点 $C$；连接点 $B$ 和点 $D$，因为向左转，加入点 $D$。

![pVElNBF.png](https://s21.ax1x.com/2025/06/16/pVElNBF.png)

连接点 $D$ 和点 $E$，因为向左转，所以加入点 $E$。

![pVEldAJ.png](https://s21.ax1x.com/2025/06/16/pVEldAJ.png)

最后要连接点 $E$ 和点 $P$，因为向右转，所以加入点 $P$。这样依次沿着栈内的点连接就形成了一个凸包。

![pVElwN9.png](https://s21.ax1x.com/2025/06/16/pVElwN9.png)

求周长就简单了，栈内两个相邻的点求距离相加即可。因为最后又加入了点 $P$，所以不用再加上最后一个点与第一个点的距离。

注意：如果有点是共线时，在这道题加入一条线上的多个点是不会影响结果的，但是如果你在做旋转卡壳时，那么这是会影响最终结果的。

总时间复杂度约为 $\mathcal{O(n \log n)}$。

最后完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define endl '\n'
const int N=1e5+5;
const double zero=0;
struct point{
	double x,y;//坐标
	double ang; //极角
}p[N];
int n;
inline double dis(point p1,point p2){
	double xx=p1.x-p2.x;
	double yy=p1.y-p2.y;
	return sqrt(xx*xx+yy*yy);
}
inline bool cmp(point p1,point p2){
	return p1.ang<p2.ang||(p1.ang==p2.ang&&dis(p1,p[1])<dis(p2,p[1]));
}
inline double cross(point p1,point p2){
	return p1.x*p2.y-p1.y*p2.x;
}
signed main(){
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y;
		if(i==1)continue;
		if(p[i].y<p[1].y||(p[i].y==p[1].y&&p[i].x<p[1].x))swap(p[i],p[1]);//找到纵坐标最小的点P
	}
	for(int i=2;i<=n;i++)p[i].ang=atan2(p[i].y-p[1].y,p[i].x-p[1].x);//求极角的函数
	sort(p+2,p+n+1,cmp);//排序
	stack<point>s;
	for(int i=1;i<=n;i++){
		while(s.size()>1){
			point p1=s.top();s.pop();
			point p2=s.top();
			if(cross(point{p1.x-p2.x,p1.y-p2.y},point{p[i].x-p1.x,p[i].y-p1.y})>zero){
				s.push(p1);
				break;
			}
		}
		s.push(p[i]);
	}
	s.push(p[1]);
	double res=0;
	point p1=s.top();s.pop();
	while(!s.empty()){//求凸包周长
		point p2=s.top();s.pop();
		res+=dis(p1,p2);
		p1=p2;
	}
	cout<<fixed<<setprecision(2)<<res<<endl;
	return 0;
}
```

接下来介绍 Andrew 算法。这个方法是按横坐标为第一关键字纵坐标为第二关键字排序的。我们发现，一个凸包的点先是按上述排序升序排序，然后降序排序的。那么这样就把一个凸包分成了上下两部分，也就是上凸壳和下凸壳。那么同样用单调栈，先正着遍历点求出上凸壳，方法和 Graham 扫描法类似，用叉积判断连线方向。然后反着遍历点求出下凸壳。

这是初始点的位置，排序后的顺序是 $ABCDEF$。

![pVEs2tI.png](https://s21.ax1x.com/2025/06/17/pVEs2tI.png)

连接点 $A$ 与点 $B$，因为顺时针遍历，连线向右转，所以加入点 $B$。

![pVEs67d.png](https://s21.ax1x.com/2025/06/17/pVEs67d.png)

连接点 $B$ 和点 $C$，因为向右转，所以加入点 $C$。

![pVEssne.png](https://s21.ax1x.com/2025/06/17/pVEssne.png)

连接点 $C$ 和点 $D$，因为向右转，所以加入点 $D$。

![pVEsy0H.png](https://s21.ax1x.com/2025/06/17/pVEsy0H.png)

连接点 $D$ 和点 $E$，因为向左转，所以弹出点 $D$；连接点 $C$ 和点 $E$，因为向右转，所以加入点 $E$（图没画好导致向右转不明显）。

![pVEsgAA.png](https://s21.ax1x.com/2025/06/17/pVEsgAA.png)]

连接点 $E$ 和点 $F$，因为向左转，所以弹出点 $E$；连接点 $C$ 和点 $F$。

![pVEsRht.png](https://s21.ax1x.com/2025/06/17/pVEsRht.png)

连接点 $C$ 和点 $F$，因为向左转，所以弹出点 $E$；连接点 $B$ 和点 $F$，因为向右转，所以加入点 $F$。

![pVEsf9P.png](https://s21.ax1x.com/2025/06/17/pVEsf9P.png)

现在上凸壳已经求出来了，然后求下凸壳。

连接点 $F$ 和点 $E$，因为向右转，所以加入点 $E$。

![pVElr1x.png](https://s21.ax1x.com/2025/06/16/pVElr1x.png)

连接点 $E$ 和点 $D$，因为向右转，所以加入点 $D$。

![pVEc2N9.png](https://s21.ax1x.com/2025/06/17/pVEc2N9.png)

连接点 $C$ 和点 $D$，因为向右转，所以加入点 $C$。

![pVE4ub6.png](https://s21.ax1x.com/2025/06/17/pVE4ub6.png)

连接点 $C$ 和点 $B$，因为向左转，所以弹出点 $C$；连接点 $D$ 和点 $B$，因为向右转，所以加入点 $B$。

![pVE4QUO.png](https://s21.ax1x.com/2025/06/17/pVE4QUO.png)

连接点 $B$ 和点 $A$，因为向左转，所以弹出点 $B$；连接点 $D$ 和点 $A$，因为向右转，所以加入点 $A$。

![pVE4MVK.png](https://s21.ax1x.com/2025/06/17/pVE4MVK.png)

所有点遍历完了，下凸壳求出来了，整个凸包也求出来了。

![pVEsh1f.png](https://s21.ax1x.com/2025/06/17/pVEsh1f.png)

注意：求下凸壳时，栈内元素大于上凸壳点的数量时才判断连续是否向右转。因为上凸壳已经求出来了，是答案的一部分，不可以再弹出了。

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define endl '\n'
const int N=1e5+5;
const double zero=0;
struct point{
	double x,y;
}p[N];
int n;
inline bool cmp(point p1,point p2){
	return p1.x<p2.x||(p1.x==p2.x&&p1.y<p2.y);
}
inline double cross(point p1,point p2){
	return p1.x*p2.y-p1.y*p2.x;
}
inline double dis(point p1,point p2){
	double xx=p1.x-p2.x;
	double yy=p1.y-p2.y;
	return sqrt(xx*xx+yy*yy);
}
signed main(){
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i].x>>p[i].y;
	sort(p+1,p+n+1,cmp);//横坐标为第一关键字，纵坐标为第二关键字排序
	stack<point>s;
	for(int i=1;i<=n;i++){//求上凸壳
		while(s.size()>1){
			point p1=s.top();s.pop();
			point p2=s.top();
			if(cross(point{p1.x-p2.x,p1.y-p2.y},point{p[i].x-p1.x,p[i].y-p1.y})>=zero){
				s.push(p1);
				break;
			}
		}
		s.push(p[i]);
	}
	int top=s.size();
	for(int i=n-1;i>=1;i--){//求下凸壳，因为点n遍历过了，所以从点n-1开始遍历
		while(s.size()>top){//站内点数量大于上凸壳点的数量
			point p1=s.top();s.pop();
			point p2=s.top();
			if(cross(point{p1.x-p2.x,p1.y-p2.y},point{p[i].x-p1.x,p[i].y-p1.y})>=zero){
				s.push(p1);
				break;
			}
		}
		s.push(p[i]);
	}
	double res=0;
	point p1=s.top();s.pop();
	while(!s.empty()){//求周长
		point p2=s.top();s.pop();
		res+=dis(p1,p2);
		p1=p2;
	}
	cout<<fixed<<setprecision(2)<<res<<endl;
	return 0;
}
  
```

---

## 作者：Dream_poetry (赞：1)

好玩，莫名其妙瞪会了，也不知道是什么算法，

### 思路：

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hmc1pu38.png)

图中有六个点，我们考虑怎么样找出一个凸多边形把所有点围起来，且该多边形周长最小。

显然我们让一些点落在这个多边形上是不劣的，所以我们就考虑用这些点作为顶点的多边形是什么样子的。

显然如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ol2mhpde.png)

考虑为什么这是对的。

如果我们让这四条边往外折，根据三角形不等式，我们容易发现这是使周长变大了；如果向里折，同样会导致周长变大，并且图形不是一个凸多边形了。

由此，我们简单论述了为什么这是对的，还是比较显然的。

接下来考虑怎么做。

找边是困难的，所以我们考虑记录点。

首先我们会发现，所有点中最靠左和最靠右的点必然被选，不然他们就没法被包含在图形中了。

启发我们以极左/右顶点作为分割，把我们期望得到的凸多边形分成上下两部分。

此处有专用名词：上凸壳和下凸壳。

我们先考虑下凸壳。

我们能发现下凸壳是由若干条线段构成的，既然是线段，我们就能表达出它的斜率。

通过简单的思考和初中数学知识，我们会发现若要满足选取的点构成下凸壳，则它们按顺序连出的线段必须斜率单调不降。

这是一个很好玩且比较有趣的性质，具体证明大家可以自行思考，这里简单说一下：其实如果它们不是单调不降的，那它们必然是折线，而折线显然无法构成一个下凸壳。

由此启发我们从左到右挨个枚举点，用一个栈来存储我们需要计入下凸壳的点，不断迭代更新，最终枚举到最右侧时，栈中所有元素桉顺序连线后共同构成了下凸壳。

上凸壳怎么做呢？我们发现如果从右往左做一遍刚才相同的操作，就能找出上凸壳了。

另外，由于每个点（除了极左/右点外）不可能同时出现在上凸壳和下凸壳上，所以记得打个标价，避免直线情况导致错误。

另外，计算斜率时注意考虑 $x$ 坐标相同时斜率记为无限大。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const double inf=1e9;
int n;
struct node{
	double x,y;
}e[1000005];

inline bool cmp(node a,node b){
	if (a.x!=b.x){
		return a.x<b.x;
	}
	return a.y<b.y;
}


int st[1000005];
int tot;
int vis[1000005];
double ans;
inline double jl(node a,node b){
	double x=a.x;
	double y=a.y;
	double xx=b.x;
	double yy=b.y;
	return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}

signed main(){	
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>e[i].x>>e[i].y;
	}
	sort(e+1,e+n+1,cmp);
	st[++tot]=1;
	st[++tot]=2;
	// 下凸壳 
	for (int i=3;i<=n;++i){
		double x=e[i].x;
		double y=e[i].y;
		double k;
		if (x==e[st[tot]].x){
			k=inf;
		}
		else{
			k=(y-e[st[tot]].y)/(x-e[st[tot]].x);
		}
		double kk;
		if (e[st[tot]].x==e[st[tot-1]].x){
			kk=inf;
		}
		else{
			kk=(e[st[tot-1]].y-e[st[tot]].y)/(e[st[tot-1]].x-e[st[tot]].x);
		}
		while (k<kk && tot>=2){
			tot--;
			if (tot==1){
				break;
			}
			if (x==e[st[tot]].x){
				k=inf;
			}
			else{
				k=(y-e[st[tot]].y)/(x-e[st[tot]].x);
			}
			if (e[st[tot]].x==e[st[tot-1]].x){
				kk=inf;
			}
			else{
				kk=(e[st[tot-1]].y-e[st[tot]].y)/(e[st[tot-1]].x-e[st[tot]].x);
			}
		}
		st[++tot]=i;
	}
	for (int i=2;i<=tot;i++){
		ans+=jl(e[st[i-1]],e[st[i]]); 
		vis[st[i]]=1;	
	}
	tot=0;
	st[++tot]=n;
	// 上凸壳 
	for (int i=n-1;i>=1;i--){
		if (vis[i]) continue;
		if (tot==1){
			st[++tot]=i;
			continue;
		}
		double x=e[i].x;
		double y=e[i].y;
		double k;
		if (x==e[st[tot]].x){
			k=inf;
		}
		else{
			k=(y-e[st[tot]].y)/(x-e[st[tot]].x);
		}
		double kk;
		if (e[st[tot]].x==e[st[tot-1]].x){
			kk=inf;
		}
		else{
			kk=(e[st[tot-1]].y-e[st[tot]].y)/(e[st[tot-1]].x-e[st[tot]].x);
		}
		while (k<kk && tot>=2){
			tot--;
			if (tot==1){
				break;
			}
			if (x==e[st[tot]].x){
				k=inf;
			}
			else{
				k=(y-e[st[tot]].y)/(x-e[st[tot]].x);
			}
			if (e[st[tot]].x==e[st[tot-1]].x){
				kk=inf;
			}
			else{
				kk=(e[st[tot-1]].y-e[st[tot]].y)/(e[st[tot-1]].x-e[st[tot]].x);
			}
		}
		st[++tot]=i;
	}
	for (int i=2;i<=tot;i++){
		
		ans+=jl(e[st[i-1]],e[st[i]]); 
	}
	printf("%.2lf",ans);
	return 0;
}
```

---

## 作者：LionBlaze (赞：1)

本文主要介绍二维凸包的 Graham 算法。

> 闲话：显然 Graham 是个人名，翻译过来是[葛立恒](https://baike.baidu.com/item/%E8%91%9B%E7%AB%8B%E6%81%92)，就是葛立恒数那个葛立恒。显然是巨佬。

# 算法介绍

任务：我们要求一个凸多边形（即每个内角均小于 $180^\circ$ 的多边形），包含平面上指定的所有点，并且周长最小。这个图多边形就叫做这个点集的凸包。

算法步骤（可能过于抽象）：

1. 定义一个栈 $T$。$S(T)$ 表示 $T$ 的元素个数。
2. 找出 $y$ 值最小的点 $M$。如果有重复，则找出 $x$ 最小的。如果再有重复，任取一个。
3. 按照点集 $S$ 中所有点与 $M$ 的极角从小到大扫描每个点 $P$。如果有极角相同的，则到 $M$ 的距离更小的优先。如果还有重复，顺序任意。
4. 对于每个点 $P$，然后如果 $S(T)\ge 2$ 则重复进行以下操作：  
   对于栈顶元素 $A$ 和栈顶之前的元素（即如果抛出栈顶元素，新的栈顶元素。$S(T) \ge 2$ 保证了存在这样的元素）$B$，如果 $\angle APB$“下凹”（有很多种定义，比如 $PA \times PB < 0$，其中 $\times$ 代表叉积，或者直接计算极角是否 $< \pi$）则弹出栈顶元素 $A$ 并且如果 $T$ 的元素个数仍然 $\ge 2$ 则重复这个操作。否则停止操作。
5. 将 $P$ 进栈。
6. 最终 $T$ 中所有的点就会构成凸包的所有顶点。

# 算法详解/正确性证明/时间复杂度分析

时间复杂度分析较为简单。每个元素至多被入栈和出栈一次，时间复杂度为 $\Theta(n)$，但是排序时间复杂度为 $\mathcal O(n \log n)$，故总时间复杂度为 $\mathcal O(n \log n)$。

关于正确性证明及算法本质：

首先，我们可以注意到，我们选的 $M$ 点必然在凸包上。这个是显然的。

算法就类似于有一根从 $M$ 点开始的绳子（无限长），刚开始朝着 $\theta=0$（$x$ 轴正方向，正右边）然后不停地往逆时针方向转动，把点视为钉子，绳子碰到之后就会改变旋转中心继续旋转。总共转一圈，最后显然会转回起点，形成凸包，正确性是显然的。类似于[这篇文章](https://www.luogu.com.cn/article/td3ah746)中说的~~打人算法~~ Jarvis 算法。

但是这样代码实现起来不太好。因为每次需要枚举这条绳子会碰到哪个点（以绳子目前的旋转中心为原点，求极角最小的点）。这样时间复杂度是 $\mathcal O(n^2)$ 的。

我们思考如何优化。我们发现以哪个点为原点的极角的相对差别都不是很大，于是我们想到直接让绳子打到极角比目前的点更大中的极角最小的点。显然，这是不对的（样例就可以 hack）。

我们发现这样每个点都会被加入凸包。我们需要去除一些没有必要的点。显然，对于连续的三个点，如果下凹则不仅违反凸包性质，还违反周长最小的限制。我们就可以直接把中间那个点弹出凸包，把线“拉直”。

这样我们发现我们还可以在线处理。建议查看[例子](https://www.desmos.com/calculator/2iqphgrmyg)（食用方法：单击 $t$ 左边的三角形按钮）。拜谢 desmos。

# 代码实现

C++。

工具函数&工具类：

```cpp
class point
{
public:
	long double x, y;
private:
	long double theta;
public:
	point(long double _x = 0, long double _y = 0) : x(_x), y(_y), theta(x == 0 && y == 0 ? 0 : atan2(y, x)) {}
	const point& operator=(const point& right) { x = right.x; y = right.y; theta = right.theta; return *this; }
	friend bool operator<(const point& x, const point& y) { return x.theta < y.theta || x.theta == y.theta && x.x * x.x + x.y * x.y < y.x * y.x + y.y * y.y; }
	long double gett() const { return theta; }
};

long double angle(const point &p1, const point &p2, const point &p3)
{
	return point{ p1.x - p2.x, p1.y - p2.y }.gett() - point{ p3.x - p2.x, p3.y - p2.y }.gett();
}
```

算法：

```cpp
vector<point> Graham_alg(vector<point> pts)
{
	vector<point> res;
	int id = 0;
	for (int i = 0; i < pts.size(); i++)
	{
		if (pts[i].y < pts[id].y || pts[i].y == pts[id].y && pts[i].x < pts[id].x) id = i;
	}
	res.push_back(pts[id]);
	pts.erase(pts.begin() + id);
	for (point& p : pts)
	{
		p = { p.x - res[0].x, p.y - res[0].y };
	}
	sort(pts.begin(), pts.end());
	for (point& p : pts)
	{
		p = { p.x + res[0].x, p.y + res[0].y };
	}
	for (const point& x : pts)
	{
		while (res.size() >= 2)
		{
			point t = res.back();
			point r = res[res.size() - 2];
			long double kk = angle(x, t, r);
			if (kk < 0) kk += numbers::pi_v<long double> * 2;
			if (kk > numbers::pi_v<long double>) break;
			else res.pop_back();
		}
		res.push_back(x);
	}
	return res;
}
```

# 例题

1. P2742 模板题。最终要求周长，我们就把凸包上的所有的相邻点对（多边形是一个环，为了方便我们可以求完凸包之后把凸包的第一个点再次加入到凸包点序列末尾）使用勾股定理求长度，再求和即可。
2. P3829 经典（？）小学奥数题。首先我们对所有信用卡角上四个四分之一圆的圆形求一遍凸包。然后因为凸包是凸的，所以凸包上的每个角贡献的圆弧加起来就会是一整个圆，所以求得的凸包周长在加上圆周长即可。

~~求硬币，求点赞，求收藏，求转发，最重要的是点一个……~~

---

