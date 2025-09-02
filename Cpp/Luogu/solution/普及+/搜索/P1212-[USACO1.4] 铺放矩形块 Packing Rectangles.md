# [USACO1.4] 铺放矩形块 Packing Rectangles

## 题目描述

给定 $4$ 个矩形块，找出一个最小的封闭矩形将这 $4$ 个矩形块放入，但不得相互重叠。所谓最小矩形指该矩形面积最小。

![](https://cdn.luogu.com.cn/upload/image_hosting/gu39gbyb.png)

$4$ 个矩形块中任一个矩形的边都与封闭矩形的边相平行，上图显示出了铺放 $4$ 个矩形块的 $6$ 种方案。  

这 $6$ 种方案是唯一可能的基本铺放方案。因为其它方案能由基本方案通过旋转和镜像反射得到。

可能存在满足条件且有着同样面积的各种不同的封闭矩形，你应该输出所有这些封闭矩形的边长。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，输入的所有数在 $[1,50]$ 内。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
1 2
2 3
3 4
4 5
```

### 输出

```
40
4 10
5 8
```

# 题解

## 作者：七喜 (赞：19)

首先，这是一道~~很简单~~很麻烦的模拟题，具体摆放方式题目已经给出了，于是就根据题目来写就好了;

其次，看见前面的dalao使用for循环找排列，我用了dfs的方式(苣蒻标配);

放代码(代码里标了一些容易出错的地方以及解释，大概能看懂吧...)
```c
#include<bits/stdc++.h>
using namespace std;

int x[5],y[5],ans=10000,tot,tmpx[5],tmpy[5];
bool vis[5],c[1005];

void alter(int x,int y)
{
	if(x*y<ans)//更新值
	{
		ans=x*y;
		memset(c,0,sizeof(c));
	}
	if(x*y==ans) c[x]=c[y]=1;
}

void check()//x表示宽//就是横着的线，y表示高//就是竖着的线咯;
{
	int x,y;
	/*
		编号顺序：
		1 2 3 4
		1 2 3 4
	*/
	x=tmpx[1]+tmpx[2]+tmpx[3]+tmpx[4];
	y=max(max(tmpy[1],tmpy[2]),max(tmpy[3],tmpy[4]));
	alter(x,y);
	/*
		编号顺序：
		1 2 3
		4 4 4
	*/
	x=max(tmpx[1]+tmpx[2]+tmpx[3],tmpx[4]);
	y=max(tmpy[1],max(tmpy[2],tmpy[3]))+tmpy[4];
	alter(x,y);
	/*
		编号顺序：
		1 2 4
		3 3 4
	*/
	x=max(tmpx[1]+tmpx[2],tmpx[3])+tmpx[4];
	y=max(max(tmpy[1],tmpy[2])+tmpy[3],tmpy[4]);
	alter(x,y);
	/*
		编号顺序：//然后发现4,5种情况没有什么实质性的差别，于是合并它们;
		1 2 4
		1 3 4
	*/
	x=tmpx[1]+max(tmpx[2],tmpx[3])+tmpx[4];
	y=max(tmpy[1],max(tmpy[2]+tmpy[3],tmpy[4]));
	alter(x,y);
	/*将矩形按照如下编号：
		1 2
		3 4
	  然后?...然后自己画图分析吧
	*/
	y=max(tmpy[1]+tmpy[3],tmpy[2]+tmpy[4]);
	if(tmpy[1]+tmpy[3]<=tmpy[4])	x=max(tmpx[2],max(tmpx[1],tmpx[3])+tmpx[4]);
	else if(tmpy[3]<=tmpy[4]&&tmpy[1]+tmpy[3]>=tmpy[4]) x=max(tmpx[1]+tmpx[2],max(tmpx[1],tmpx[3])+tmpx[4]);
		 else if(tmpy[3]>=tmpy[4]&&tmpy[3]<=tmpy[2]+tmpy[4]) x=max(tmpx[1]+tmpx[2],max(tmpx[2],tmpx[4])+tmpx[3]);
			  else if(tmpy[3]>=tmpy[2]+tmpy[4]) x=max(tmpx[1],max(tmpx[2],tmpx[4])+tmpx[3]);
	alter(x,y);//恩，注意考虑等于号的临界状态;
}

void dfs(int yj)//dfs生成排列
{
	if(yj==4)
	{
		check();return ;
	}
	for(int i=1;i<5;i++)
		if(!vis[i])
		{
			tmpx[yj+1]=x[i],tmpy[yj+1]=y[i],vis[i]=1;
			dfs(yj+1);
			tmpx[yj+1]=y[i],tmpy[yj+1]=x[i];
			dfs(yj+1);
			vis[i]=tmpx[yj+1]=tmpy[yj+1]=0;
		}
}

int main(){
	for(int i=1;i<5;i++) scanf("%d%d",&x[i],&y[i]);
	dfs(0);
	printf("%d\n",ans);
	for(int i=1;i<=sqrt(ans);i++)
		if(c[i]) printf("%d %d\n",i,ans/i);
	return 0;
}
```
附：编号排序是我对矩形编的号，有助于代码理解;

---

## 作者：HFUUZY (赞：14)

    
            
             
```cpp
#include<iostream>
#include<memory.h>
#include<cstring>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
void swap(int *a,int *b){//交换函数，貌似algorithm库里面的函数不能处理以数组名的交换，如swap(a,a+2),a为数组名。
    int t;
    t=*a;
    *a=*b;
    *b=t;
}
int h[10],w[10];//定义全局变量，从而简便程序。
int ans[1000]={0};
int m=10000;
void update(int x,int y)
{
   if(x*y<m) 
   {
       m=x*y;
       memset(ans,0,sizeof(ans) );//一旦找到更小的面积，就立即让ans数组清零。
   }
   if(x*y==m){
       ans[x]=ans[y]=1;//记录长和宽的位置以便输出方便。
      }
} 
int calc(int w1,int h1,int w2,int h2,int w3,int h3,int w4,int h4)//计算五种情况下的面积。。。
{
   int x,y;
   //case 1:
   x=w1+w2+w3+w4;
   y=max( max(h1,h2) ,max(h3,h4) );
   update(x,y);
   //case 2:
   x=max(w1+w2+w3,w4);
   y=max(max(h1,h2),h3)+h4;
   update(x,y);
   //case 3:
   x=max(w1+w2,w3)+w4;
   y=max(max(h1+h3,h2+h3) ,h4);
   update(x,y);
   //case 4:
   x=w1+w2+max(w3,w4);
   y=max(max(h1,h3+h4),h2);
   update(x,y);
   //case 5:
   y=max(h1+h3,h2+h4);
   if(h3>=h2+h4) x=max( max(w1,w3+w2),w3+w4);
   else if( h3>h4 && h3<h2+h4 ) x=max( max(w1+w2,w2+w3),w3+w4);
   else if( h4>h3 && h4<h1+h3 ) x=max( max(w1+w2,w1+w4),w3+w4);
   else if( h4>=h1+h3)  x=max( max(w2,w1+w4) ,w3+w4);
   else if(h3==h4) x=max(w1+w2,w3+w4);
   update(x,y);
}
void change()//首先四个的矩形的位置可以相互交换，那么就一共有4*3*2*1种情况，然后每一种情况下，每个矩形的长和宽都能够交换，
             //就又有2*2*2*2=16种情况，因此全部枚举即可。
{
   for(int a=0;a<4;a++){//交换四个矩形的相互位置共4*3*2*1种情况。
        swap(w+1,w+1+a);
        swap(h+1,h+1+a);
        for(int b=1;b<4;b++){
            swap(w+2,w+1+b);
            swap(h+2,h+1+b);
            for(int c=2;c<4;c++){
                swap(w+3,w+1+c);
                swap(h+3,h+1+c);
                for(int d=3;d<4;d++){
                    swap(w+4,w+1+d);
                    swap(h+4,h+1+d);
   for(int g=1;g<=3;g++)//交换每个矩形的长和宽 共2*2*2*种情况
   { 
       swap(w[1],h[1]);
       for(int i=1;i<=3;i++)
       {
         swap(w[2],h[2]);
         for(int j=1;j<=3;j++)
         {
           swap(w[3],h[3]);
           for(int k=1;k<=3;k++)
           {
              swap(w[4],h[4]);
              calc(w[1],h[1],w[2],h[2],w[3],h[3],w[4],h[4]);
           }   
         }
       }
```
}//长和宽的交换循环结束
```cpp
   swap(w+4,w+1+d);
   swap(h+4,h+1+d);
   }//for d
   swap(w+3,w+1+c);
   swap(h+3,h+1+c);
   }//for c
   swap(w+2,w+1+b);
   swap(h+2,h+1+b);
   }//for b
   swap(w+1,w+1+a);
   swap(h+1,h+1+a); 
   }//for a
}
int main()
{
    for(int i=1;i<=4;i++)
        cin>>w[i]>>h[i];
    change();
    cout<<m<<endl;
    for(int i=0;i<=(int)sqrt(m);i++)
       if(ans[i])  cout<<i<<" "<<m/i<<endl;
  // system("pause");
    return 0;
}
```

---

## 作者：Chiesl (赞：7)

# 解法&思路
这道题就是暴力搜索题，写一个 DFS 就可以完美解决了，主要是对于各种情况的处理，本蒟蒻将一一讲解。

其实本蒟蒻想不出来这些摆放的情况，但是题目画了图啊 awa。

几种情况的图片：
![](https://cdn.luogu.com.cn/upload/pic/57.png)

接下来我们用 $a,b$ 来表示封闭矩阵的宽和长，$x1, x2, x3, x4$ 分别表示四个矩阵的宽，$y1, y2, y3, y4$ 分别表示四个矩阵的长。

不管这个矩阵怎么歪，我们只把对 $a$ 的值有贡献的边记作 $x_{i}$，对 $b$ 有贡献的记作 $y_{i}$。$(1 \le i \le 4)$。
### 第一种情况
四种并排放。
很容易可以看出：$a = x1 + x2 + x3 + x4$。

$b$ 的值就为他们中的最大值，所以 $b = \max(\max(y1, y2), \max(y3, y4))$。
### 第二种情况
三个并排，一个躺平。
也可以得出：$a = \max(x1 + x2 + x3, x4)$。

以及：$b = \max(y1,\max(y2,y3)) + y4 $。
### 第三种情况
显然：$a = \max(x1 + x2, x3) + x4$。

$b = \max(\max(y1, y2) + y3, y4)$。
### 第四种情况
看似更复杂，其实就是堆在一起的 2，3 号矩阵难以处理。但细想想也不难，堆在上面的那个的 $x$ 值一定小于等于下面那个，所以这两个矩阵对于 $a$ 的值的贡献为：$\max(x2, x3)$。

由此可得：$a = x1 + \max(x2, x3) + x4$。

$b = \max(y1, \max(y2 + y3, y4))$。
### 第五种情况
与第四种基本相同，区别在于第四种堆叠的矩阵位于中间，第五种位于旁边

显然：$a = \max(x1, x2) + x3 + x4$。

$b = \max(y1 + y2, \max(y3, y4))$。
### 第六种情况
最复杂的情况，看似复杂实则也很容易懂，要分情况讨论，想必各位神犇做数学题时没少遇到。

我们统一一下编号：右上角，左上角，右下角，左下角，按照这个顺序从 1 到 4 编号。
#### 情况一：$y4 + y2 \le y3$
各位不妨画个图，立刻就可以得出：$a = \max(\max(x1, x3 + x2), x3 + x4)$。
#### 情况二：在不满足情况一的条件下，$y4 < y3$
依然可以轻松得出：$a = \max(x1 + x2, \max(x2, x4) + x3)$。
#### 情况三：$y3 = y4$
这是所有情况中最直观的：$a = \max(x1 + x2, x3 + x4)$。
#### 情况四：$y3 < y4$，且不满足情况五
依然是画了图以后就可以轻松得出：$a = \max(x1 + x2, \max(x1, x3) + x4)$。
#### 情况五：$y1 + y3 \le y4$
动手画图后可以得出：$a = \max(x2, \max(x1, x3) + x4)$。

看到这可能有神犇会好奇，$b$ 咋求？

画图啊，画图一下子就出来了：$b = \max(y1 + y3, y2 + y4)$。
## 代码
具体应该怎么做呢？
先深搜枚举位置（也就是上文中编号），然后调用计算就行了。

非常的简单，就是很肝。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5][2], num[5]; //分别储存每个矩阵的长宽，顺序
int cnt, Min = INT_MAX;
bool vis[5], flag[402][402];
struct node {
	int p, q;
} ans[2050];//结构体排序完成子任务
void answer (int sx, int sy) {
	if (sx > sy) swap(sx, sy);//也是子任务	
	if (flag[sx][sy]) return;//防止重复
	flag[sx][sy] = true;
	if (sx * sy < Min) {
		Min = sx * sy;
		cnt = 1;
		ans[cnt].p = sx, ans[cnt].q = sy;
	} else if (sx * sy == Min) {
		ans[++cnt].p = sx;
		ans[cnt].q = sy;
	}
}
void f (int s1, int s2, int s3, int s4) {
	int x, y;
	x = a[s1][1] + a[s2][1] + a[s3][1] + a[s4][1], y = max(max(a[s1][0], a[s2][0]), max(a[s3][0], a[s4][0]));
	answer(x, y);
	x = max(a[s1][1] + a[s2][1] + a[s3][1], a[s4][1]), y = max(a[s1][0], max(a[s2][0], a[s3][0])) + a[s4][0];
	answer(x, y);
	x = max(a[s1][1] + a[s2][1], a[s3][1]) + a[s4][1], y = max(a[s4][0], max(a[s1][0], a[s2][0]) + a[s3][0]);
	answer(x, y);
	x = a[s1][1] + max(a[s2][1], a[s3][1]) + a[s4][1], y = max(a[s4][0], max(a[s1][0], a[s2][0] + a[s3][0]));
	answer(x, y);
	x = max(a[s1][1], a[s2][1]) + a[s3][1] + a[s4][1], y = max(max(a[s1][0] + a[s2][0], a[s3][0]), a[s4][0]);
	answer(x, y);
	if (a[s3][0] >= a[s2][0] + a[s4][0]) x = max(max(a[s1][1], a[s3][1] + a[s2][1]), a[s3][1] + a[s4][1]);
	else if (a[s4][0] < a[s3][0]) x = max(a[s1][1] + a[s2][1], max(a[s2][1], a[s4][1]) + a[s3][1]);
	else if (a[s3][0] == a[s4][0]) x = max(a[s1][1] + a[s2][1], a[s3][1] + a[s4][1]);
	else if (a[s3][0] < a[s4][0] && a[s4][0] < a[s3][0] + a[s1][0]) x = max(a[s1][1] + a[s2][1], max(a[s1][1], a[s3][1]) + a[s4][1]);
	else if (a[s4][0] >= a[s1][0] + a[s3][0]) x = max(a[s2][1], max(a[s1][1], a[s3][1]) + a[s4][1]);
	y = max(a[s1][0] + a[s3][0], a[s2][0] + a[s4][0]);
	answer(x, y);
}//上文有详细讲，这里不再赘述
void dfs (int k) {
	if (k == 5) {
		f(num[1], num[2], num[3], num[4]);
		return;
	}
	for (int i = 1; i <= 4; i++) {
		if (vis[i]) continue;
		vis[i] = true;
		num[k] = i;
		dfs(k + 1);
		swap(a[i][0], a[i][1]);//把矩阵转90°再搜
		dfs(k + 1);
		swap(a[i][0], a[i][1]);
		vis[i] = false;//回溯
	}
}
bool cmp (node a, node b) {return a.p < b.p;}
int main () {
	for (int i = 1; i <= 4; i++) scanf("%d%d", &a[i][0], &a[i][1]);
	dfs(1);
	sort(ans + 1, ans + 1 + cnt, cmp);
	printf("%d\n", Min);
	for (int i = 1; i <= cnt; i++) printf("%d %d\n", ans[i].p, ans[i].q);//完美的输出
	return 0;
}
```
这道题算是绿题中比较简单的了，而且还是一次水两道 awa。

[双倍经验传送门](https://www.luogu.com.cn/problem/P5917)。

---

## 作者：Fijian_Bus (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P1212)

### 题意

给定 $4$ 个矩形块，找出一个最小的封闭矩形将这 $4$ 个矩形块放入，但不得相互重叠。所有 $4$ 个矩形块的边都与封闭矩形的边相平行，图示铺放 $4$ 个矩形块的 $6$ 种方案，这 $6$ 种方案仅只是可能的基本铺放方案。

因为其它方案能由基本方案通过旋转和镜像反射得到。可能存在满足条件且有着同样面积的各种不同的封闭矩形，你输出所有这些封闭矩形的边长。


### 思路

枚举。

题目描述中很明确：只有 $6$ 种基本的铺放方式。我们可以把这 $6$ 种铺放情况都枚举出来，把所有 $4$ 个矩形全排列。然后，对于 case $1-5$ 就迎刃而解了，其中 $4,5$ 其实是一种情况。而 case $6$ 就需要我们仔细考虑各种接触情况了！

注意：矩形有两个方向，全排时还要考虑方向问题。

### 实现

设 $w1,w2,w3,w4$ 表示 $4$ 个方块的横长，$h1,h2,h3,h4$ 表示 $4$ 个方块的纵长。$w,h$ 表示最小的。

1. `w=w1+w2+w3+w4, h=max(h1,h2,h3,h4)`

2. `w=max(w1+w2+w3,w4), h=max(h1,h2,h3)+h4`

3. `w=max(w1+w2,w3)+w4, h=max(h1+h3,h2+h3,h4)`

4. `w=w1+w2+max(w3,w4), h=max(h1,h3+h4,h2)`

5. `h=max(h1+h3,h2+h4)`

细分 $w$ 的伪代码：

```
1. if h3>=h2+h4, w=max(w1,w3+w2,w3+w4)
2. if h3>h4 and h3<h2+h4, w=max(w1+w2,w2+w3,w3+w4) 
3. if h4>h3 and h4<h1+h3, w=max(w1+w2,w1+w4,w3+w4)
4. if h4>=h1+h3, w=max(w2,w1+w4,w3+w4)
5. if h3=h4, w=max(w1+w2,w3+w4)
```

### AC CODE

```cpp
#include <bits/stdc++.h>
#define INF 1<<25
#define next dffff
using namespace std;
struct node {
    int x, y;
}e[10];
int mn = INF, h, w, next[10] = {0}, inx = 0;
#define maxn 1005
node in[10], tmp, out[maxn];
bool cmp(node s, node v) {
    return s.x < v.x;
}
void pack1() {
    h = 0, w = 0;
    for (int i = 0; i < 4; i++) {
        h = max(h, in[i].y);
        w += in[i].x;
    }
    tmp.x = min(w, h);
    tmp.y = max(w, h);
    if (w * h < mn) {
        inx = 0;
        out[inx++] = tmp;
        mn = w * h;
    }
    else if (w * h == mn) {
        out[inx++] = tmp;
    }
}
void pack2() {
    h = w = 0;
    for (int i = 0; i < 3; i++) {
        h = max(h, in[i].y);
        w += in[i].x;
    }
    h += in[3].y;
    w = max(w, in[3].x);
    tmp.x = min(w, h);
    tmp.y = max(w, h);
    if (w * h < mn) {
        inx = 0;
        out[inx++] = tmp;
        mn = w * h;
    }
    else if (w * h == mn) {
        out[inx++] = tmp;
    }
}
void pack3() {
    h = w = 0;
    h = max(max(in[0].y, in[1].y) + in[3].y, in[2].y);
    w = max(in[0].x + in[1].x, in[3].x) + in[2].x;
    tmp.x = min(w, h);
    tmp.y = max(w, h);
    if (w * h < mn) {
        inx = 0;
        out[inx++] = tmp;
        mn = w * h;
    }
    else if (w * h == mn) {
        out[inx++] = tmp;
    }
}
void pack4() {
    h = w = 0;
    h = max(max(in[0].y + in[1].y, in[2].y), in[3].y);
    w = max(in[0].x, in[1].x) + in[2].x + in[3].x;
    tmp.x = min(w, h);
    tmp.y = max(w, h);
    if (w * h < mn) {
        inx = 0;
        out[inx++] = tmp;
        mn = w * h;
    }
    else if (w * h == mn) {
        out[inx++] = tmp;
    }
}
void pack5() {
    h = max(in[0].y + in[1].y, in[2].y + in[3].y);
    if (in[1].y >= in[2].y + in[3].y) w = max(max(in[2].x, in[3].x) + in[1].x, in[0].x);
    if (in[1].y > in[3].y && in[1].y < in[2].y + in[3].y) w = max(max(in[0].x + in[2].x, in[2].x + in[1].x), in[1].x + in[3].x);
    if (in[0].y + in[1].y >= in[3].y && in[1].y < in[3].y) w = max(max(in[0].x + in[2].x, in[0].x + in[3].x), in[1].x + in[3].x);
    if (in[0].y + in[1].y <= in[3].y) w = max(max(in[0].x, in[1].x) + in[3].x, in[2].x);
    if (in[1].y == in[3].y) w = max(in[0].x + in[2].x, in[1].x + in[3].x);
    tmp.x = min(w, h);
    tmp.y = max(w, h);
    if (w * h < mn) {
        inx = 0;
        out[inx++] = tmp;
        mn = w * h;
    }
    else if (w * h == mn) {
        out[inx++] = tmp;
    }
}
int main ()
{
    for (int i = 0; i < 4; i++) {
        scanf("%d%d", &e[i].x, &e[i].y);
        e[i + 4].x = e[i].y;
        e[i + 4].y = e[i].x;
        next[i] = i;
    }
    do {
        int tot = 1 << 4;
        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < 4; j++) {
                if ((i >> j) & 1) in[j] = e[next[j]];
                else in[j] = e[next[j] + 4];
            }
            pack1();
            pack2();
            pack3();
            pack4();
            pack5();
        }
    } while(next_permutation(next, next + 4));
    cout << mn << endl;
    sort(out, out + inx, cmp);
    cout << out[0].x << " " << out[0].y << endl;
    for (int i = 1; i < inx; i++)
    	if (out[i].x != out[i - 1].x)
        	cout << out[i].x << " " << out[i].y << endl;
    return 0;
}
```

---

## 作者：HongzheLi (赞：2)

这是一道恶心的巨模拟
=
# 分析
>分为6种情况：
>
>![](https://cdn.luogu.com.cn/upload/image_hosting/gu39gbyb.png)
>
>善良的USACO把6种情况都列出来了
>
>不然怎么会是绿题
# 思路

>模拟每种情况，推出每种情况封闭矩形的边长
# AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int n, m, x[10], y[10], id[10], res = 1e9;
bool st[5];
set<pair<int, int> > v;

void get(int X, int Y){
	if(X > Y) swap(X, Y);
	if(X * Y < res){
		v.clear();
		res = X * Y;
		v.insert({X, Y});
	}
	else if(X * Y == res) v.insert({X, Y});
}

void check(){
	
	int X, Y;
	// 1 2 3 4
	X = x[id[1]] + x[id[2]] + x[id[3]] + x[id[4]];
	Y = max(y[id[1]], max(y[id[2]], max(y[id[3]], y[id[4]])));
	get(X, Y);
	// 1 2 3
	// 4 4 4
	X = max(x[id[1]] + x[id[2]] + x[id[3]], x[id[4]]);
	Y = y[id[4]] + max(y[id[1]], max(y[id[2]], y[id[3]])); 
	get(X, Y);
	// 1 2 3
	// 4 4 3
	X = x[id[3]] + max(x[id[4]], x[id[1]] + x[id[2]]);
	Y = max(y[id[3]], y[id[4]] + max(y[id[1]], y[id[2]]));
	get(X, Y);
	//1 2 4
	//1 3 4
	X = x[id[1]] + max(x[id[2]], x[id[3]]) + x[id[4]];
	Y = max(y[id[1]], max(y[id[2]] + y[id[3]], y[id[4]]));
	get(X, Y);
	// 1 3 4
	// 2 3 4
	X = max(x[id[1]], x[id[2]]) + x[id[3]] + x[id[4]];
	Y = max(y[id[3]], max(y[id[4]], y[id[1]] + y[id[2]]));
	get(X, Y);
	// 1 2
	// 3 4
	Y = max(y[id[1]] + y[id[3]], y[id[2]] + y[id[4]]);
	X = max(x[id[1]] + x[id[2]], x[id[3]] + x[id[4]]);
	if(y[id[3]]>y[id[4]])X=max(X,x[id[3]]+x[id[2]]);
	else X=max(X,x[id[4]]+x[id[1]]);
	get(X, Y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	for(int i = 1; i <= 4; i ++) cin >> x[i] >> y[i], id[i] = i;
	
	check();
	for(ll i=0;i<=1;i++){
		swap(x[1],y[1]);
		for(ll j=0;j<=1;j++){
			swap(x[2],y[2]);
			for(ll k=0;k<=1;k++){
				swap(x[3],y[3]);
				for(ll r=0;r<=1;r++){
					swap(x[4],y[4]);
					check();
				}
			}
		}
	}
	while(next_permutation(id + 1, id + 5)){
		check();
		for(ll i=0;i<=1;i++){
			swap(x[1],y[1]);
			for(ll j=0;j<=1;j++){
				swap(x[2],y[2]);
				for(ll k=0;k<=1;k++){
					swap(x[3],y[3]);
					for(ll r=0;r<=1;r++){
						swap(x[4],y[4]);
						check();
					}
				}
			}
		}
	}
	cout << res << endl;
	for(auto c: v) cout << c.first << ' ' << c.second << endl;
	return 0;
}
```
>本蒟蒻的第一篇题解,不喜勿喷QWQ

---

## 作者：luuia (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P1212)

## 题意

有 $4$ 个长方形，$6$ 种不同的摆法，求所有的摆法中，能够覆盖 $4$ 个长方形的矩形的最小面积及对应的长宽，按照长宽中的较小值升序排列输出。

## 分析

下面对于每一种情况，给出对应的图和分析：

我们记 $i$ 号矩形的长为 $x_i$，宽为 $y_i$ ($1 \leq i \leq 4$)，最大矩形的长为 $x$，宽为 $y$，不论大小，横向为长，纵向为宽。

- ### 第一种情况

![图1](https://cdn.luogu.com.cn/upload/image_hosting/6phns4jd.png)

可以见得，因为 $4$ 个矩形是并列放置，总长 $x = x_1 + x_2 + x_3 + x_4$，总宽 $y = \max(y_1,\max(\max(y_2,y_3),y_4))$。

- ### 第二种情况

![图2](https://cdn.luogu.com.cn/upload/image_hosting/mnrcfakt.png)

我们将这个图形分为上下两部分看，上半部分的长为 $3$ 个之和，宽为 $3$ 个中的最大值，下半部分长为 $x_4$，宽为 $y_4$，总长为 $x = \max(x_1+x_2+x_3,x_4)$，总宽为 $y = \max(y_1,\max(y_2,y_3)) + y_4$。

- ### 第三种情况

![图3](https://cdn.luogu.com.cn/upload/image_hosting/3h9gu0md.png)

我们将这个图形分为左右两部分看，左半部分的长为 $\max(x_1+x_2,x_3)$，宽为 $\max(x_1,x_2)+x_3$，右半部分长为 $x_4$，宽为 $y_4$，总长为 $x = \max(x_1+x_2,x_3)+x_4$，总宽为 $y = \max(\max(x_1,x_2)+x_3,x_4)$。

- ### 第四种情况

![图4](https://cdn.luogu.com.cn/upload/image_hosting/y1fa5wr8.png)

我们将这个图形分为左、中、右三部分来看。

左半部分：长为 $x_1$，宽为 $y_1$；

中间部分：长为 $\max(x_2,x_3)$，宽为 $y_2+y_3$；

右半部分：长为 $x_4$，宽为 $y_4$。

总长为三部分之和，总宽为三部分的最大值。

总长 $x = x_1+\max(x_2,x_3)+x_4$，总宽 $y = \max(\max(y_1,y_2+y_3),y_4)$。

- ### 第五种情况

![图5](https://cdn.luogu.com.cn/upload/image_hosting/7s29mywe.png)

同样的，我们将这个图形分为左、中、右三部分来看。

左半部分：长为 $\max(x_1,x_2)$，宽为 $y_1+y_2$；

中间部分：长为 $x_3$，宽为 $y_3$；

右半部分：长为 $x_4$，宽为 $y_4$。

总长为三部分之和，总宽为三部分的最大值。

总长 $x = \max(x_1,x_2)+x_3+x_4$，总宽 $y = \max(\max(y_1+y_2,y_3),y_4)$。

- ### 第六种情况

这是最复杂的一种，这里主要分以下几种情况讨论，每种情况皆在不满足以上所有情况的前提下实现。

![图6](https://cdn.luogu.com.cn/upload/image_hosting/z27dfxzn.png)

- $y_1 + y_3 \leq y_4$

![图7](https://cdn.luogu.com.cn/upload/image_hosting/ivwyffaw.png)

总长 $x = \max(\max(x_1,x_3)+x_4,x_2)$

- $y_3 \leq y_4 $ 且 $y_4 < y_1 + y_3$

![图8](https://cdn.luogu.com.cn/upload/image_hosting/45t233t6.png)

总长 $x = \max(\max(x_1,x_3)+x_4,x_2)$

- $y_4 \leq y_3$ 且 $y_3 \leq y_2+y_4$

![图9](https://cdn.luogu.com.cn/upload/image_hosting/ewctt9jz.png)

总长 $x = \max(x_1+x_2,\max(x_2,x_4)+x_3)$

- $y_2+y_4 \leq y_3$

![图10](https://cdn.luogu.com.cn/upload/image_hosting/vjhn6alp.png)

总长 $x = \max(\max(x_2,x_4)+x_3,x_1)$

以上，我们就完成了每种情况的分析。

## 代码

我们考虑用一个数组 $\text{s}$ 表示答案，一个计数器 $\text{cnt}$ 表示答案的个数，一个变量 $\text{ans}$ 表示最小的面积，对于每一种可能的排列情况进行计算，如果结果小于最小面积，那么将数组清零，答案更新并存入此时的长和宽，最终升序排列输出即可。

看到很多大佬都用了 dfs，那么因为这个题只有四个矩形，可以直接暴力循环解决。

[AC 代码](https://www.luogu.com.cn/paste/64aails4)

[我的 AC 记录](https://www.luogu.com.cn/record/139450432)

---

## 作者：cwocw (赞：2)

这一题对于我来说真是一波三折：

![心脏病患者勿看](https://cdn.luogu.com.cn/upload/image_hosting/d94mzni7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)![心脏病患者勿看](https://cdn.luogu.com.cn/upload/image_hosting/1jit6rmv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

~~不过还是被我做出来啦。~~

废话少说，我们直接进入正题：

题意就是让我们照着题目给的6种方案打出代码。

![题意](https://cdn.luogu.com.cn/upload/pic/57.png)

我们先设一个 $a(5,2)$，$a(i,0)$ 代表第 $i$ 个长方形的长，$a(i,1)$ 代表第 $i$ 个长方形的宽。设一个结构体 $T$ 和 $min1$。
```cpp
struct T{
	ll x,y;
}s[1010];//表示所有答案的长与宽。
ll min1=INT_MAX;//表示最终矩形面积。
ll a[5][2];
```
我们还要设一个 $t$ 和 $f(5)$。
```cpp
ll t;//代表不同长宽的个数。
ll f[5];//f[i] 代表第 i 个长方体当前的方向。
```
接下来我们要引入一个 $4$ 重循环，枚举它们的方向：
```cpp
for(f[1]=0;f[1]<=1;f[1]++){
	for(f[2]=0;f[2]<=1;f[2]++){
		for(f[3]=0;f[3]<=1;f[3]++){
			for(f[4]=0;f[4]<=1;f[4]++){
				ll s1,s2,s3;//s1 表示当前的面积，s2 表示当前的长，s3 当前的宽。
			}
		}
	}
}

```
为了记录所有答案的长与宽，我们需要一个队列，也就是上面的结构体 $T$ 中的 $s(1010)$。接下来就是如何使用这个队列，这里面我用了一些技巧。因为它是求最小值，所以一旦遇到最小的，就会重新清空整个队列，$t=1$ 就是为了清空队列，$s_1.x=\min(s2,s3)$ 和 $s(1).y=\max(s2,s3)$ 是把 $s2$ 和 $s3$ 加入队列。一旦 $s1=min1$, 那么也把它的 $s2$ 和 $s3$ 加入队列。
```cpp
if(s1<min1){
	min1=s1;
	s[1].x=min(s2,s3);
	s[1].y=max(s2,s3);
	t=1;
}
if(s1==min1){
	s[++t].x=min(s2,s3);
	s[t].y=max(s2,s3);
}
```
下面开始讲 $6$ 种方案。

1.
![1](https://cdn.luogu.com.cn/upload/image_hosting/3650u1ji.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

它的长为 $4$ 个长方体的横长的总和，宽为 $4$ 个长方体的竖长中的最大值。

```cpp
s2=a[1][f[1]]+a[2][f[2]]+a[3][f[3]]+a[4][f[4]];
s3=max(max(max(a[1][(f[1]+1)%2],a[2][(f[2]+1)%2]),a[3][(f[3]+1)%2]),a[4][(f[4]+1)%2]);//a[i][(f[i]+1)%2] 是为了找另一方向的边。
s1=s2*s3;
```
2.
![2](https://cdn.luogu.com.cn/upload/image_hosting/4aj1f11q.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们设最底下的为 $h1$。

它的长为 $h1$ 的横长与其他 $3$ 个的横长之和最大的长，宽为 $h1$ 的竖长加上其它 $3$ 个的竖长中最大的长。
```cpp
s2=max(a[h1][f[h1]],a[1][f[1]]+a[2][f[2]]+a[3][f[3]]+a[4][f[4]]-a[h1][f[h1]]);
s3=a[h1][(f[h1]+1)%2];
if(h1==1) s3+=max(max(a[2][(f[2]+1)%2],a[3][(f[3]+1)%2]),a[4][(f[4]+1)%2]);
if(h1==2) s3+=max(max(a[1][(f[1]+1)%2],a[3][(f[3]+1)%2]),a[4][(f[4]+1)%2]);
if(h1==3) s3+=max(max(a[1][(f[1]+1)%2],a[2][(f[2]+1)%2]),a[4][(f[4]+1)%2]);
if(h1==4) s3+=max(max(a[2][(f[2]+1)%2],a[3][(f[3]+1)%2]),a[1][(f[1]+1)%2]);
```
3.
![3](https://cdn.luogu.com.cn/upload/image_hosting/d3heqq0t.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

看图，我们分别设 $4$ 个长方形为 $h1$、$h2$、$h3$和$h4$，当然我们需要特判如果 $h1=h2$ 或 $h1=h3$ 或 $h1=h4$ 或 $h2=h3$ 或 $h2=h4$ 或 $h3=h4$ 那么我们要 $continue$。

它的长为 $h2$ 的横长与 $h3$ 的横长加上 $h4$ 的横长比较最大的长加上 $h1$ 的横长，宽为 $h1$ 的竖长与 $h3$ 的竖长和 $h4$ 的竖长的最大值加上 $h2$ 的竖长与 $h1$ 的竖长比较的最大值。
```cpp
if(h1==h2||h1==h3||h1==h4||h2==h3||h2==h4||h3==h4) continue;
s2=max(a[h1][f[h1]],a[h2][f[h2]]+max(a[h3][f[h3]],a[h4][f[h4]]));
s3=a[h1][(f[h1]+1)%2]+max(a[h2][(f[h2]+1)%2],a[h3][(f[h3]+1)%2]+a[h4][(f[h4]+1)%2]);
s1=s2*s3;
```
4.
![4](https://cdn.luogu.com.cn/upload/image_hosting/np5if2fz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

看图，我们分别设 $4$ 个长方形为 $h1$、$h2$、$h3$和$h4$，当然我们需要特判同上。

它的长为 $h2$ 的横长与 $h1$ 的横长的和加上 $h3$ 的横长和 $h4$ 的横长中最大的长，宽为 $h1$ 的竖长与 $h3$ 的竖长和 $h4$ 的竖长的和比较 $h2$ 的竖长三者中的最大值。
```cpp
s2=a[h1][f[h1]]+a[h2][f[h2]]+max(a[h3][f[h3]],a[h4][f[h4]]);
s3=max(a[h1][(f[h1]+1)%2],max(a[h2][(f[h2]+1)%2],a[h3][(f[h3]+1)%2]+a[h4][(f[h4]+1)%2]));
s1=s2*s3;
```
5.
![5](https://cdn.luogu.com.cn/upload/image_hosting/w3v50q7w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

看图，我们分别设 $4$ 个长方形为 $h1$、$h2$、$h3$和$h4$，当然我们需要特判同上。

它的长为 $h2$ 的横长与 $h1$ 的横长的和加上 $h3$ 的横长和 $h4$ 的横长中最大的长，宽为 $h1$ 的竖长与 $h3$ 的竖长和 $h4$ 的竖长的和比较 $h2$ 的竖长三者中的最大值。

此时我们发现它的方案与图 $4$ 一样，所以我们可以舍去。

6.

![6](https://cdn.luogu.com.cn/upload/image_hosting/v6igzdat.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

看图，我们分别设 $4$ 个长方形为 $h1$、$h2$、$h3$和$h4$，当然我们需要特判同上。

它的宽为 $h1$ 的竖长加上 $h3$ 的竖长比较 $h2$ 的竖长加上 $h4$ 的竖长的最大值。

它的长分成好几种情况。

当 $h1$ 的竖长加上 $h3$ 的竖长小于 $h4$ 的竖长时，它的长为 $h3$ 的横长加上 h4 的横长和 h1 的横长的最大值比较 h2 的横长的最大值。

![6.1](https://cdn.luogu.com.cn/upload/image_hosting/8q2tn0dl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当 $h1$ 的竖长加上 $h3$ 的竖长大于 $h4$ 的竖长且 $h3$ 的竖长小于 $h4$ 的竖长时，它的长为 $h1$ 的横长与 $h3$ 的横长加上 $h4$ 的横长的最大值比较 $h2$ 的横长加上 $h1$ 的横长的最大值。

![6.2](https://cdn.luogu.com.cn/upload/image_hosting/etuas23a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当 $h3$ 的竖长大于 $h4$ 的竖长且 $h3$ 的竖长小于 $h4$ 的竖长加上 $h2$ 的竖长时，它的长为 $h2$ 的横长与 $h3$ 的横长加上 $h4$ 的横长的最大值比较 $h2$ 的横长加上 $h1$ 的横长的最大值。

![6.3](https://cdn.luogu.com.cn/upload/image_hosting/z96vrrrw.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当 $h3$ 的竖长大于 $h4$ 的竖长加上 $h2$ 的竖长时，它的长为 $h3$ 的横长加上 $h4$ 的横长和 $h2$ 的横长的最大值比较 $h1$ 的横长的最大值。

![6.4](https://cdn.luogu.com.cn/upload/image_hosting/q0srr7p2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
```cpp
s2=max(a[h1][f[h1]]+a[h3][f[h3]],a[h2][f[h2]]+a[h4][f[h4]]);
if(a[h1][f[h1]]+a[h3][f[h3]]<=a[h4][f[h4]]){
s3=max(a[h2][(f[h2]+1)%2],max(a[h1][(f[h1]+1)%2],a[h3][(f[h3]+1)%2])+a[h4][(f[h4]+1)%2]);
}
else if(a[h3][f[h3]]<=a[h4][f[h4]]&&a[h1][f[h1]]+a[h3][f[h3]]>=a[h4][f[h4]]){
s3=max(a[h2][(f[h2]+1)%2]+a[h1][(f[h1]+1)%2],max(a[h1][(f[h1]+1)%2],a[h3][(f[h3]+1)%2])+a[h4][(f[h4]+1)%2]);
}
else if(a[h3][f[h3]]>a[h4][f[h4]]&&a[h3][f[h3]]<=a[h2][f[h2]]+a[h4][f[h4]]){
s3=max(a[h1][(f[h1]+1)%2]+a[h2][(f[h2]+1)%2],max(a[h2][(f[h2]+1)%2],a[h4][(f[h4]+1)%2])+a[h3][(f[h3]+1)%2]);
}
else if(a[h3][f[h3]]>=a[h2][f[h2]]+a[h4][f[h4]]){
s3=max(a[h1][(f[h1]+1)%2],max(a[h2][(f[h2]+1)%2],a[h4][(f[h4]+1)%2])+a[h3][(f[h3]+1)%2]);
}
s1=s2*s3;
```
分析完毕。

---

## 作者：ChampionCyan (赞：1)

# P1212 题解

## 前言

[闲话](https://www.luogu.com/paste/p11xf7jb)。

[更美观清晰的体验](https://www.luogu.com/paste/3qxsr1g1)，必看！

[双倍经验](https://www.luogu.com.cn/problem/P5917)，题目完全一样，所以与[这篇题解](https://www.luogu.com.cn/article/e8ztn55q/)内容几乎一样。

## 思路与做法大纲

这题有 $6$ 种排列方式，题目已经给出：

![](https://cdn.luogu.com.cn/upload/image_hosting/gu39gbyb.png)

为了接下来的操作，我们先定义一些东西：

```cpp
/*<==============函数定义==============>*/
inline void init();//输入
inline void part1();//排列方案1
inline void part2();//排列方案2
inline void part3();//排列方案3
inline void part4();//排列方案4
inline void part5();//排列方案5
inline void part6();//排列方案6
inline void update(int, int);//更新答案
inline void do_it();//工作
inline void work(int);//工作
inline void solve();//解答
```
主函数代码很简单了：

```cpp
/*<==============主函数==============>*/
int main() {
    init();
    solve();
    return 0;
}
```

然后我们用之前定义的 mp 判断输入是否重复，这样我们就得到了 update 函数的代码：

```cpp
inline void update(int length, int width) {
    if (length > width)
        swap(length, width);
    if (length * width > ans || mp.count(make_pair(length, width)) > 0)
        return;
    /*<================以上情况不用更新！================>*/
    //更新
    mp.insert(make_pair(length, width));
    if (length * width < ans) {
        ans = length * width;
        res.clear();
        mp.insert(make_pair(length, width));
    }
    res.push_back(make_pair(length, width));
}
```

再将工作的三个函数框架写出来：

```cpp
inline void do_it() {
    part1();
    part2();
    part3();
    part4();
    part5();
    part6();
}

inline void work(int depth) {
    if (depth == 5) {
        do_it();
        return;
    }
    for (int i = 0; i < 4; i++) {
        swap(rec[order[i]].length, rec[order[i]].width);//旋转
        work(depth + 1);//下一种排列
        swap(rec[order[i]].length, rec[order[i]].width);//回溯
        work(depth + 1);//下一种排列
    }
}

inline void solve() {
    do
        work(1);
    while (next_permutation(order, order + 4));
    printf("%d\n", ans);
    sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++)
        printf("%d %d\n", res[i].first, res[i].second);
}
```

框架就写好了，然后就是最难的 part1~part6 函数了！

请读者看以下内容时先思考一会儿！

### Part1

$4$ 个并排放。

很简单，画图理解一下，长是和，宽是最短的宽。

```cpp
inline void part1() {
    update(rl(0) + rl(1) + rl(2) + rl(3), max(max(rw(0), rw(1)), max(rw(2), rw(3))));
}
```

### Part2

三竖一横。

```cpp
inline void part2() {
    update(max(rl(0) + rl(1) + rl(2), rl(3)), max(rw(0), max(rw(1), rw(2))) + rw(3));
}
```

### Part3

有些复杂，但也不难想。

```cpp
inline void part3() {
    update(max(rl(0) + rl(1), rl(2)) + rl(3), max(rw(3), max(rw(0), rw(1)) + rw(2)));
}
```

### Part4

两个夹两个。

```cpp
inline void part4() {
    update(rl(0) + max(rl(1), rl(2)) + rl(3), max(rw(3), max(rw(0), rw(1) + rw(2))));
}
```



### Part5

与第四种很像，区别在于第四种夹心，第五种两个矩形位于旁边。

```cpp
inline void part5() {
    update(max(rl(0), rl(1)) + rl(2) + rl(3), max(max(rw(0) + rw(1), rw(2)), rw(3)));
}
```

### Part6

有点像奥数题，仔细画图想想！

`length` 要分情况讨论，`width` 就是左边两个长的和与右边两个长的和的最小值。

```cpp
inline void part6() {
    //比较复杂，慢慢来
    int length;
    if (rw(2) >= rw(1) + rw(3))
        length = max(max(rl(0), rl(1) + rl(2)), rl(2) + rl(3));
    else if (rw(3) < rw(2))
        length = max(rl(0) + rl(1), max(rl(1), rl(3)) + rl(2));
    else if (rw(2) == rw(3))
        length = max(rl(0) + rl(1), rl(2) + rl(3));
    else if (rw(2) < rw(3) && rw(3) < rw(2) + rw(0))
        length = max(rl(0) + rl(1), max(rl(0), rl(2)) + rl(3));
    else if (rw(3) >= rw(0) + rw(2))
        length = max(rl(1), max(rl(0), rl(2)) + rl(3));
    update(length, max(rw(0) + rw(2), rw(1) + rw(3)));
}
```

这样就写完了。

## Code

```cpp
/*<=====头文件，命名空间和宏定义=====>*/
#include <bits/stdc++.h>
#define rl(i) rec[order[i]].length
#define rw(i) rec[order[i]].width
using namespace std;

/*<==============基础定义==============>*/
struct rectangle {
    int length, width;
} rec[4];//长方形们

int order[4] = {0, 1, 2, 3};//排列顺序，初始时有序
int ans = 2e9;//答案，初始时设为极大值
set<pair<int, int> > mp;
vector<pair<int, int> > res;

/*<==============函数定义==============>*/
inline void init();//输入
inline void part1();//排列方案1
inline void part2();//排列方案2
inline void part3();//排列方案3
inline void part4();//排列方案4
inline void part5();//排列方案5
inline void part6();//排列方案6
inline void update(int, int);//更新答案
inline void do_it();//工作
inline void work(int);//工作
inline void solve();//解答

/*<==============主函数==============>*/
int main() {
    init();
    solve();
    return 0;
}

inline void init() {
    for (int i = 0; i < 4; i++)
        scanf("%d%d", &rec[i].length, &rec[i].width);
}

inline void update(int length, int width) {
    if (length > width)
        swap(length, width);
    if (length * width > ans || mp.count(make_pair(length, width)) > 0)
        return;
    /*<================以上情况不用更新！================>*/
    //更新
    mp.insert(make_pair(length, width));
    if (length * width < ans) {
        ans = length * width;
        res.clear();
        mp.insert(make_pair(length, width));
    }
    res.push_back(make_pair(length, width));
}

inline void part1() {
    update(rl(0) + rl(1) + rl(2) + rl(3), max(max(rw(0), rw(1)), max(rw(2), rw(3))));
}

inline void part2() {
    update(max(rl(0) + rl(1) + rl(2), rl(3)), max(rw(0), max(rw(1), rw(2))) + rw(3));
}

inline void part3() {
    update(max(rl(0) + rl(1), rl(2)) + rl(3), max(rw(3), max(rw(0), rw(1)) + rw(2)));
}

inline void part4() {
    update(rl(0) + max(rl(1), rl(2)) + rl(3), max(rw(3), max(rw(0), rw(1) + rw(2))));
}

inline void part5() {
    update(max(rl(0), rl(1)) + rl(2) + rl(3), max(max(rw(0) + rw(1), rw(2)), rw(3)));
}

inline void part6() {
    //比较复杂，慢慢来
    int length;
    if (rw(2) >= rw(1) + rw(3))
        length = max(max(rl(0), rl(1) + rl(2)), rl(2) + rl(3));
    else if (rw(3) < rw(2))
        length = max(rl(0) + rl(1), max(rl(1), rl(3)) + rl(2));
    else if (rw(2) == rw(3))
        length = max(rl(0) + rl(1), rl(2) + rl(3));
    else if (rw(2) < rw(3) && rw(3) < rw(2) + rw(0))
        length = max(rl(0) + rl(1), max(rl(0), rl(2)) + rl(3));
    else if (rw(3) >= rw(0) + rw(2))
        length = max(rl(1), max(rl(0), rl(2)) + rl(3));
    update(length, max(rw(0) + rw(2), rw(1) + rw(3)));
}

inline void do_it() {
    part1();
    part2();
    part3();
    part4();
    part5();
    part6();
}

inline void work(int depth) {
    if (depth == 5) {
        do_it();
        return;
    }
    for (int i = 0; i < 4; i++) {
        swap(rec[order[i]].length, rec[order[i]].width);//旋转
        work(depth + 1);//下一种排列
        swap(rec[order[i]].length, rec[order[i]].width);//回溯
        work(depth + 1);//下一种排列
    }
}

inline void solve() {
    do
        work(1);
    while (next_permutation(order, order + 4));
    printf("%d\n", ans);
    sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++)
        printf("%d %d\n", res[i].first, res[i].second);
}
```

---

## 作者：封禁用户 (赞：1)

**题目大意**：给定 $4$ 个矩形块，找出一个最小的封闭矩形将这 $4$ 个矩形块放入，但不得相互重叠。所有 $4$ 个矩形块的边都与封闭矩形的边相平行，图示铺放 $4$ 个矩形块的 $6$ 种方案，这 $6$ 种方案仅只是可能的基本铺放方案。因为其它方案能由基本方案通过旋转和镜像反射得到。可能存在满足条件且有着同样面积的各种不同的封闭矩形，你输出所有这些封闭矩形的边长。

**思路**：我们分类讨论，大致有 $6$ 种情况。

![分类讨论情况](https://cdn.luogu.com.cn/upload/image_hosting/gu39gbyb.png)

这是题目上的图，大致就是这几种情况。然后我们再观察这些图，去推**封闭矩阵的宽和长**和**四个矩阵的宽、长**之间的关系即可。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[5];int y[5];int tmpx[5];int tmpy[5];int ans = INT_MAX;int s[1005];
bool vis[15];
void get_ans(int x,int y){
	if (x * y < ans){
		memset(s, 0, sizeof(s));
		ans = x * y;
	}
	if (x * y == ans){
		s[x] = 1;
		s[y] = 1;
	}
}
void check(){
	int x, y;
	x = tmpx[1] + tmpx[2] + tmpx[3] + tmpx[4];
	y = max(max(tmpy[1], tmpy[2]), max(tmpy[3], tmpy[4]));
	get_ans(x,y);
	x = max(tmpx[1] + tmpx[2] + tmpx[3], tmpx[4]);
	y = max(tmpy[1], max(tmpy[2], tmpy[3])) + tmpy[4];
	get_ans(x,y);
	x = max(tmpx[1] + tmpx[2], tmpx[3]) + tmpx[4];
	y = max(max(tmpy[1], tmpy[2]) + tmpy[3], tmpy[4]);
	get_ans(x,y);
	x = tmpx[1] + max(tmpx[2], tmpx[3]) + tmpx[4];
	y = max(tmpy[1], max(tmpy[2] + tmpy[3], tmpy[4]));
	get_ans(x,y);
	y = max(tmpy[1] + tmpy[3], tmpy[2] + tmpy[4]);
	if (tmpy[1] + tmpy[3] <= tmpy[4])x = max(tmpx[2], max(tmpx[1], tmpx[3]) + tmpx[4]);
	else if (tmpy[3] <= tmpy[4] && tmpy[1] + tmpy[3] >= tmpy[4])x = max(tmpx[1] + tmpx[2], max(tmpx[1], tmpx[3]) + tmpx[4]);
	else if (tmpy[3] >= tmpy[4] && tmpy[3] <= tmpy[2] + tmpy[4])x = max(tmpx[1] + tmpx[2], max(tmpx[2], tmpx[4]) + tmpx[3]);
	else if (tmpy[3] >= tmpy[2] + tmpy[4])x = max(tmpx[1], max(tmpx[2], tmpx[4]) + tmpx[3]);
	get_ans(x,y);
}
void dfs(int ceng){
	if(ceng == 4){
		check();
		return ;
	}
	for (int i = 1; i < 5; i ++ ){
		if(!vis[i]){
			tmpx[ceng + 1] = x[i];
			tmpy[ceng + 1] = y[i];
			vis[i] = true;
			dfs(ceng + 1);
			tmpx[ceng + 1] = y[i]; 
			tmpy[ceng + 1] = x[i];
			dfs(ceng + 1);
			vis[i] = false;
			tmpx[ceng + 1] = 0;
			tmpy[ceng + 1] = 0;
		}
	}
}
int main(){
	for (int i = 1; i < 5; i ++ )cin >> x[i] >> y[i];
	dfs(0);cout << ans << endl;
	int k = sqrt(ans);
	for (int i = 1; i <= k; i ++ )
		if(s[i])cout << i << " " << ans / i << endl;
	return 0;
}
```


---

## 作者：legend_cn (赞：1)

这是一道不太复杂的模拟，按着题目说的做就行。可以用**深搜**的方式实现。

首先，需要使用**dfs生成排列**，当触碰到了边界就运行**check函数**。

check函数就是在获取和更新答案的。

因为还要输出方案，那么更新答案时需要记录方案。
最后先输出面积最小值，判断如果该方案被标记过，就输出该方案

代码里关键，易错的地方加了**少量注释**


**AC CODE**
```cpp
#include<bits/stdc++.h>
using namespace std;

int x[5];
int y[5];
int tmpx[5];
int tmpy[5];

int ans = INT_MAX;
int s[1005];

bool vis[5];


void get_ans(int x,int y)
{
	if (x * y < ans)
	{
		memset(s, 0, sizeof(s));
		ans = x * y;
	}
	
	if (x * y == ans)
	{
		s[x] = 1;
		s[y] = 1;
	}
}

void check()
{
	int x, y;
	
	/*
		顺序： 
		1 2 3 4
		1 2 3 4
	*/
	x = tmpx[1] + tmpx[2] + tmpx[3] + tmpx[4];
	y = max(max(tmpy[1], tmpy[2]), max(tmpy[3], tmpy[4]));
	
	get_ans(x,y);
	
	
	
	/*
		顺序:
		1 2 3
		4 4 4
	*/
	x = max(tmpx[1] + tmpx[2] + tmpx[3], tmpx[4]);
	y = max(tmpy[1], max(tmpy[2], tmpy[3])) + tmpy[4];
	
	get_ans(x,y);
	
	
	
	/*
		顺序:
		1 2 4
		3 3 4
	*/
	x = max(tmpx[1] + tmpx[2], tmpx[3]) + tmpx[4];
	y = max(max(tmpy[1], tmpy[2]) + tmpy[3], tmpy[4]);
	
	get_ans(x,y);
	
	
	
	/*
		顺序:
		1 2 4
		1 3 4
	*/
	x = tmpx[1] + max(tmpx[2], tmpx[3]) + tmpx[4];
	y = max(tmpy[1], max(tmpy[2] + tmpy[3], tmpy[4]));
	
	get_ans(x,y);
	
	
	
	/*
		顺序:
		1 2
		3 4
	*/
	y = max(tmpy[1] + tmpy[3], tmpy[2] + tmpy[4]);
	//x在不同情况有多种值，需要特判
	 
	if (tmpy[1] + tmpy[3] <= tmpy[4])
	{
		x = max(tmpx[2], max(tmpx[1], tmpx[3]) + tmpx[4]);
	}
	else if (tmpy[3] <= tmpy[4] && tmpy[1] + tmpy[3] >= tmpy[4])
	{
		x = max(tmpx[1] + tmpx[2], max(tmpx[1], tmpx[3]) + tmpx[4]);
	}
	else if (tmpy[3] >= tmpy[4] && tmpy[3] <= tmpy[2] + tmpy[4])
	{
		x = max(tmpx[1] + tmpx[2], max(tmpx[2], tmpx[4]) + tmpx[3]);
	}
	else if (tmpy[3] >= tmpy[2] + tmpy[4])
	{
		x = max(tmpx[1], max(tmpx[2], tmpx[4]) + tmpx[3]);
	}
	
	get_ans(x,y);
}

void dfs(int ceng)/生成/排列 
{
	if(ceng == 4)
	{
		check();
		return ;
	}
	
	for (int i = 1; i < 5; i ++ )
	{
		if(!vis[i])
		{
			tmpx[ceng + 1] = x[i];
			tmpy[ceng + 1] = y[i];
			vis[i] = true;
			
			dfs(ceng + 1);
			
			tmpx[ceng + 1] = y[i];//这里不是tmpx存x了！下一次做的时候 x,y需要反过来 
			tmpy[ceng + 1] = x[i];//这里不是tmpy存y了！下一次做的时候 x,y需要反过来 
			
			dfs(ceng + 1);
			
			vis[i] = false;
			tmpx[ceng + 1] = 0;
			tmpy[ceng + 1] = 0;
		}
	}
}


int main()
{
	for (int i = 1; i < 5; i ++ )
	{
		cin >> x[i] >> y[i];
	}
	
	dfs(0);
	
	cout << ans << endl;
	
	int k = sqrt(ans);
	
	for (int i = 1; i <= k; i ++ )
	{
		if(s[i])
		{
			cout << i << " " << ans / i << endl;
		}
	}
	return 0;
}
```

---

## 作者：wuenzi (赞：1)

可以把每个矩形标上号，然后对这几个矩形进行全排列。最后，计算出排列好的矩形面积就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct no {
	int a, b;
} p[10], q[10];
vector<no> a;//长和宽
bool v[10];
int mi = INT_MAX;//答案

void bj(int x, int y) {//比较长、宽、面积，并作记录
//	cout << x << ' ' << y << endl;
	if (x * y < mi) {
		a.clear();//舍去所有记录
		mi = x * y;
		no p1;
		p1.a = x, p1.b = y;
		a.push_back(p1);//记录
	} else if (x * y == mi) {
		no p1;
		p1.a = x, p1.b = y;
		a.push_back(p1);//记录
	}
}

void mj() {
	int c1 = max(q[0].a, max(q[1].a, max(q[2].a, q[3].a)));
	int k1 = q[0].b + q[1].b + q[2].b + q[3].b;
	bj(min(c1, k1), max(c1, k1));//第一种情况
	int c2 = max(q[0].b + q[1].b + q[2].b, q[3].a);
	int k2 = max(q[0].a, max(q[1].a, q[2].a)) + q[3].b;
	bj(min(c2, k2), max(c2, k2));//第二种情况
	int c3 = max(q[2].a + q[3].b, q[0].b + q[1].b + q[3].b);
	int k3 = max(q[3].a, max(q[0].a, q[1].a) + q[2].b);
	bj(min(c3, k3), max(c3, k3));//第三种情况
	int c4 = max(q[0].a, max(q[1].a + q[2].a, q[3].a));
	int k4 = max(q[0].b + q[1].b + q[3].b, q[0].b + q[2].b + q[3].b);
	bj(min(c4, k4), max(c4, k4));//第四种情况
	int c5 = max(q[0].a + q[1].a, max(q[2].a, q[3].a));
	int k5 = max(q[0].b + q[2].b + q[3].b, q[1].b + q[2].b + q[3].b);
	bj(min(c5, k5), max(c5, k5));//第五种情况
	int c6 = max(q[0].a + q[2].a, q[1].a + q[3].a);
	int k6;
	if(q[0].a+q[2].a<=q[4].a){
		k6=max(q[1].b,max(q[0].b,q[2].b)+q[3].b);
	}else if(q[2].a<=q[3].a&&q[0].a+q[2].a>=q[4].a){
		k6=max(q[0].b+q[1].b,max(q[0].b,q[2].b)+q[3].b);
	}else if(q[2].a>=q[3].a&&q[2].a<=q[1].a+q[3].a){
		k6=max(q[0].b+q[1].b,max(q[1].b,q[3].b)+q[2].b);
	}else{
		k6=max(q[0].b,max(q[1].b,q[3].b)+q[2].b);
	}
	bj(min(c6,k6),max(c6,k6));//第六种情况，这种情况有很多子情况，需要逐一去判断
}

void dfs(int d) {//搜索
	if (d == 4) {
		mj();//计算面积
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (v[i] == 0) {
			q[d].a = p[i].a, q[d].b = p[i].b;//长宽不交换
			v[i] = 1;
			dfs(d + 1);
			swap(q[d].a, q[d].b);//长宽交换
			dfs(d + 1);
			v[i] = 0;
		}
	}
}

bool cmp(no x, no y) {
	return x.a < y.a;
}

int main() {
	for (int i = 0; i < 4; i++) {
		cin >> p[i].a >> p[i].b;
	}
	dfs(0);
	sort(a.begin(), a.end(), cmp);//排序
	cout << mi << endl;
	cout<<a[0].a<<" "<<a[0].b<<endl;
	for (int i = 1; i < a.size(); i++) {
		if(a[i].a==a[i-1].a&&a[i].b==a[i-1].b){//去重
			continue;
		}
		cout << a[i].a << " " << a[i].b << endl;//输出
	}
	return 0;//结束
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

思路：DFS 枚举四个矩形的顺序和方向，分别计算构成的大矩形面积。

实现：

`ch` 记录按顺序选择的四个矩形在横向和纵向上的长度，`ans` 记录最小面积的组成中大矩形的宽的可能的取值，输出答案时只需输出这些值和最小面积与它们的比。

```cpp
const ll n=4,inf=1e9,S=2e3;
pll a[n+10],ch[n+10];
ll min1=inf;
bool ans[S],used[n+10];
```

`upd` 函数用于对于已知的大矩形面积更新答案。

```cpp
void upd(ll x,ll y) {
	if(x*y==min1) ans[min(x,y)]=1;
	elif(x*y<min1) {
		min1=x*y;
		memset(ans,0,sizeof(ans));
		ans[min(x,y)]=1;
	}
}
```

`check()` 函数用于对于当前的摆放顺序计算大矩形长宽。本来这个部分挺复杂的，但题面已经把所有需要考虑的情况都告诉你了。

第 $1$ 种情况：

```cpp
x=max(max(ch[1].fi,ch[2].fi),max(ch[3].fi,ch[4].fi));
	y=ch[1].se+ch[2].se+ch[3].se+ch[4].se;
```

第 $2$ 种情况：

```cpp
x=max(max(ch[1].fi,ch[2].fi),ch[3].fi)+ch[4].fi;
	y=max(ch[1].se+ch[2].se+ch[3].se,ch[4].se);
```

第 $3$ 种情况：

```cpp
x=max(max(ch[1].fi,ch[2].fi)+ch[3].fi,ch[4].fi);
	y=max(ch[1].se+ch[2].se,ch[3].se)+ch[4].se;
```

第 $4$ 种情况和第 $5$ 种情况：

```cpp
x=max(max(ch[1].fi,ch[2].fi+ch[3].fi),ch[4].fi);
	y=ch[1].se+max(ch[2].se,ch[3].se)+ch[4].se;
```

第 $6$ 种情况：

比较复杂，需要再分 $4$ 种子情况。可以想象把两堆矩形放在地上，其中一堆逐渐升高。

```cpp
y=max(ch[1].fi+ch[3].fi,ch[2].fi+ch[4].fi);
	
	if(ch[1].fi+ch[3].fi<=ch[4].fi)	x=max(ch[2].se,max(ch[1].se,ch[3].se)+ch[4].se);
	else if(ch[3].fi<=ch[4].fi&&ch[1].fi+ch[3].fi>=ch[4].fi) 
		x=max(ch[1].se+ch[2].se,max(ch[1].se,ch[3].se)+ch[4].se);
	else if(ch[3].fi>=ch[4].fi&&ch[3].fi<=ch[2].fi+ch[4].fi) 
		x=max(ch[1].se+ch[2].se,max(ch[2].se,ch[4].se)+ch[3].se);
	else if(ch[3].fi>=ch[2].fi+ch[4].fi) x=max(ch[1].se,max(ch[2].se,ch[4].se)+ch[3].se);
```

DFS 以及主函数：

```cpp
void dfs(ll no) {
	if(no==5) check();
	else {
		rep(i,1,4) {
			if(used[i]==0) {
				used[i]=1;
				ch[no]=a[i];
				dfs(no+1);
				ch[no]= {a[i].se,a[i].fi};
				dfs(no+1);
				used[i]=0;
			}
		}
	}
}

int main() {
	rep(i,1,4) cin>>a[i].fi>>a[i].se;

	dfs(1);
	cout<<min1<<'\n';

	rep(i,1,S-1) {
		if(min1/i<i) return 0;

		if(ans[i]) cout<<i<<' '<<min1/i<<'\n';
	}
}
```

---

