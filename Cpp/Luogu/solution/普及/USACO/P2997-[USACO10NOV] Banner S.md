# [USACO10NOV] Banner S

## 题目背景

题目大意(by:曹彦臣)：


平面上有(0,0)到(n,m)的(n+1)\*(m+1)个点。问有多少点对所连的线段不过其他点，且长度在[l,h]范围内。


## 题目描述

Bessie is returning from a long trip abroad, and Farmer John wants to erect a nice 'Welcome Home' banner in her pasture for her arrival. The banner will hang between two poles on a wire whose length is in the range L1..L2 (1 <= L1 <= L2; L1 <= L2 <= 1,500).

The pasture's size is W x H (1 <= W <= 1,000; 1 <= H <= 1,000), and Farmer John has installed a post at every point with integer

coordinates. Of these (W + 1) \* (H + 1) points, Farmer John must pick just two that will hold either end of the wire from which he will hang the banner.

FJ wants no interference with his banner as it hangs and requires that no post be directly under the tight wire he stretches between the two chosen posts.

Farmer John needs your help to figure out how many possible ways he can hang the banner. He knows the number is large and that a 32-bit integer might not be sufficient to compute the answer.

Consider the example pasture below, with W = 2 and H = 1: 

\* \* \*
\* \* \*
The banner size is in the range 2..3. This pasture contains (2+1) \* (1+1) = 6 points and has (6 take 2) = (6\*5)/(2\*1) = 15 different potential pairs of points between which the banner-holding wire might stretch:

```cpp
(0,0)-(0,1)   (0,0)-(2,1)   (0,1)-(2,1)   (1,1)-(2,0) 
(0,0)-(1,0)   (0,1)-(1,0)   (1,0)-(1,1)   (1,1)-(2,1) 
(0,0)-(1,1)   (0,1)-(1,1)   (1,0)-(2,0)   (2,0)-(2,1) 
(0,0)-(2,0)   (0,1)-(2,0)   (1,0)-(2,1) 
```
Of these pairs, only four have a length in the range 2..3:
Len                       Len

(0,0)-(2,0) 2.00          (0,1)-(2,0) 2.24 

(0,0)-(2,1) 2.24          (0,1)-(2,1) 2.00 

Of these four, the pairs (0,0)-(2,0) and (0,1)-(2,1) both have a post directly on the line between the endpoints, and thus are 

unsuitable.

So, just two pairs of points out of 15 are acceptable candidates for hanging the banner wire.


## 样例 #1

### 输入

```
2 1 2 3 
```

### 输出

```
2 
```

# 题解

## 作者：fyx_Catherine (赞：5)

### 这道题直接暴力枚举
因为这个图的左右是对称的，我们可以只考虑所有斜率>0的线段：根据这条，我们可以分出当线段与水平/竖直方向平行的情况来。显然，只有全部长度为1的线段满足要求，此时如果1在[L,R][L,R]内，则需要加上这些情况。

我们还可以算出**一个格点图内与当前枚举的线段相同的线段个数**：将这条线段视作与横竖直线构成了一个Rt△Rt△，那么问题可以转化为求在格点图中与该Rt△Rt△相同的个数，这个只需要O(1)O(1)即可完成（对于直角边分别为x,y的Rt△Rt△，在纵方向上有(n-x+1)种可能性，在横方向上有(m-y+1)种可能性，根据乘法原理得到个数），所以重点是在枚举不同的Rt△Rt△。

通过分析两个条件，我们可以知道一个符合要求的Rt△Rt△（设直角边分别为x,y）必须满足：          **L2≤x2+y2≤R2，gcd(x,y)=1。**
### Code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
int read(){
    long long a=0,k=1;char c=getchar();
    while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
    while (isdigit(c)){a=a*10+c-'0';c=getchar();}
    return a*k;
}
long long ans,n,m,l,r;
int gcd(int a,int b){ 
    if (a==0)return b;
    return gcd(b%a,a);
}
int main(){
    n=read();m=read();l=read();r=read();
    if(l==1){ans=ans+(n+1)*m+(m+1)*n; }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            double now=sqrt(i*i+j*j);
            if(now<l||now>r||gcd(i,j)!=1)continue;
            ans=ans+2*(n-i+1)*(m-j+1);
        }
    }
    printf ("%lld\n",ans);
}

```
求管理员通过（QWQ）


---

## 作者：do_while_false (赞：4)

~~这题做的时候忘了特判，卡了半天~~

【大概思路】

我的思路和@CR_Raphael 的思路差不多，但还是细微有点区别的。

枚举点 $(0,0)$ 到其他点的可能性，再将该线段翻折，再统计所有的条数。

当线段为 $(1,0)$ 或 $(0,1)$ 时不需要翻折。为什么呢？

我们设两个横坐标分别为为 $x_1,x_2$ ，纵坐标为 $y_1,y_2$。

很容易发现，只有当 $\gcd(|x_1-x_2|,|y_1-y_2|)=1$ 时，线段上没有点。

因此，当线段为 $(1,0)$ 或 $(0,1)$ 时不需要翻折。

其它的根据代码模拟即可。

【具体代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r;
long long ans;
int gcd(int a,int b) {
	return a%b==0?b:gcd(b,a% b);
}
int main(void) {
	scanf("%d%d%d%d",&n,&m,&l,&r); 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(gcd(i,j)==1&&i*i+j*j>=l*l&&i*i+j*j<=r*r)
				ans+=2*(n-i+1)*(m-j+1);
	if(l==1) ans+=n*(m+1)+(n+1)*m;
	printf("%lld\n",ans);
	return 0;
}
```

应该是最短代码了吧。

---

## 作者：CR_Raphael (赞：3)

本来以为是道水题，结果忘特判了，GG

枚举点（0，0）到其他点的线段的可行性，再将该线段翻折，统计总条数

当线段为（1，0）或（0，1）时不需要翻折

```c++
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int dist(int x,int y){
    int a=x*x+y*y;
    return a;
}

int gcd(int a,int b){
    if(a>b)swap(a,b);
    
    if(a==0)return b;
    
    return gcd(b%a,a);
}

int main(){
    int n,m,l,r;
    long long int ans=0;
    int t;
    cin>>n>>m>>l>>r;
    
    int i,j;
    
    for(i=0;i<=n;i++){
        for(j=0;j<=m;j++){
            t=dist(i,j);
            if(t>=l*l && t<=r*r){
                if(gcd(i,j)==1)
                    if((j+i)!=1)ans=ans+(n-i+1)*(m-j+1)*2;
                    else ans=ans+(n-i+1)*(m-j+1)
            }
        }
    }
    
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：2)

# P2997 [USACO10NOV] Banner S 题解
## 算法
思维题
## 思路分析
题目要求所连线段不经过其他点，其实就是要求你连的线段每种斜率只能有一个单位的长度。换人话就是线段**长和宽要互质**。可以转换为枚举的这个点阵内的矩形的对角线数量。

所以我们**枚举矩形的长宽**即可，需要注意的是线段是可以垂直或者水平连的，所以长和宽从零开始枚举。但是长和宽不能同时为零，那是一个点，要排除。而且如果长和宽有一个为零的话，这条线段为了不经过其他点长度就只能为一。记得判断对角线长度。

在经过以上判断找到一个正确的矩形之后，我们可以把这个矩形放到点阵中的任何位置。如图，我们可以只看它右上的节点，就是有 $(W-i+1)\times(H-j+1)$ 个符合要求的线段。

![](https://pic.imgdb.cn/item/65d6b7669f345e8d03bd4dc5.png)

然后，每条线段还可以进行翻转，所以要给答案乘 $2$。但是水平的和竖直的不用翻转，所以要把多翻的这些减去。

![](https://pic.imgdb.cn/item/65d6b87e9f345e8d03bfd18c.png)

记得开 `long long`。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Raiden
{
    signed work()
    {
        int ans=0;
        int w,h,l1,l2;
        cin>>w>>h>>l1>>l2;
        int sum=0;
        for(int i=0;i<=w;i++)
        {
            for(int j=0;j<=h;j++)
            {
                double l=sqrt(i*i+j*j);
                if(__gcd(i,j)==1&&l1<=l&&l<=l2&&(i||j))
                    if(!((i==0&&j>1)||(j==0&&i>1)))
                    {
                        ans+=(w-i+1)*(h-j+1);
                        if(i==0||j==0)
                            sum+=(w-i+1)*(h-j+1);
                    }
            }
        }
        cout<<ans*2-sum<<endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：owlAlice (赞：1)

前面的大佬实在是太厉害啦，他的题解我没有看懂

这是蒟蒻的第一份题解，管理员大大给过呗

好了，个人认为这一题一点也不水，用到了一些数学上的知识

首先我们要解决一个大问题：如何判断这个线段上有没有点

我参考了某大佬的博客：

（如果我侵权了，请私信我）[dalao's blog](https://blog.csdn.net/lyjvactor/article/details/38728051)

总之，就是 纵坐标距离/（纵坐标距离/纵坐标距离和横坐标距离的最大公约数）+1 是**包含两端点**的整数点个数，如果不包含呢，就再减掉两个就好啦

所以我们推出来，只有横、纵坐标距离的最大公约数为1时，线段上才没有点

（这个我觉得很难啊，可能是我数学太差了）

然后就好办啦

先从（0,0）为一个端点，枚举另一个端点的坐标，然后判断这条线段是否符合要求，如果符合的话，利用数学知识，把其他所有符合的方案都加上

特判是：当线段为（1，0）或（0，1）时不需要翻折

放上丑陋的代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int w,h,l1,l2;
LL ans=0;
int dis(int x,int y)//dsitance from (0,0) to (x,y)
{
    int a;
    a=x*x+y*y;
    return a;
}
int Gcd(int a,int b)
{
	if(a>b)
		swap(a,b);
    if(a==0)
		return b;
    return Gcd(b%a,a);
}
int main()
{
    scanf("%d%d%d%d",&w,&h,&l1,&l2);
    for(int i=0;i<=w;i++)
        for(int j=0;j<=h;j++)
        {
            int res=dis(i,j);
            if(res<l1*l1 || res>l2*l2)
                continue;
            //判断线段上是否有点，如没有，通过平移线段累加答案
            /*Solution 1
            int chk,t;
            chk=Gcd(i,j);
            t=j/(j/chk)+1;
            t-=2;
            此时t=0意味着线段上没有整数点，也就是j/(j/chk)+1=2
            so chk=1
            */
            int chk;
            chk=Gcd(i,j);
            if(chk!=1)
                continue;
            if((j+i)!=1)
                ans=ans+(w-i+1)*(h-j+1)*2;
            else
                ans=ans+(w-i+1)*(h-j+1);
        }
    printf("%lld\n",ans);
    return 0;
}

```

完美结束！撒花！

---

