# Pashmak and Garden

## 题目描述

Pashmak在一年前和一个叫Parmida的妹子相爱...

今天，Pashmak准备在一个浪漫的花园约会，但他忘记了花园的位置。他记得花园看起来像一个平行于坐标轴的正方形，正方形的每一个顶点上都有一棵树。现在，他只知道其中两棵树的位置。帮助他找到剩下两个的位置。

## 样例 #1

### 输入

```
0 0 0 1
```

### 输出

```
1 0 1 1
```

## 样例 #2

### 输入

```
0 0 1 1
```

### 输出

```
0 1 1 0
```

## 样例 #3

### 输入

```
0 0 1 2
```

### 输出

```
-1
```

# 题解

## 作者：RE_Prince (赞：2)

# Pashmak and Garden 



[link](https://www.luogu.com.cn/problem/CF459A)


## Sol

一道超水的 CF div2 A 题。


我们考虑利用平面直角坐标系来进行两棵树的位置的分类讨论。


## 同一行

我们可以将剩下两棵树构造在原先的树的上面，也就是算出已给出的两棵树的欧几里得（或曼哈顿）距离后，直接将 $y$ 轴增加对应的值。

代码：

```cpp
if(x==a) cout<<x+dy<<" "<<y<<" "<<a+dy<<" "<<b;
```

注：以下为了方便起见，将 $\left|x_1-x_2\right|$ 定义为 $dx$，将 $\left|y_1-y_2\right|$ 定义为 $dy$。$x,y,a,b$ 分别为题目中的 $x_1,y_1,x_2,y_2$。

那么上面的代码就不用解释了吧，很显然这种构造方法是对的。


## 同一列


和行一样，只是将 $x$ 轴增加对应值就好了。

代码：

```cpp
else if(y==b) cout<<x<<" "<<y+dx<<" "<<a<<" "<<b+dx;
```


## 对角线


不太好处理，我们画个图，发现两个点的坐标不管怎样，都是 $(x_2,y_1),(x_1,y_2)$。也就是将四个值进行了一下全排列，剩下的两种情况就是答案。

这里的代码很简单，不用加任何量：

```cpp
else cout<<x<<" "<<b<<" "<<a<<" "<<y;
```


## 无解

当然，不是上面三种情况的一定无解：

```cpp
if(x!=a&&y!=b&&dx!=dy)
/*
不在同一行
不在同一列
间距不相等

如果都满足，直接无解。
*/
{
	puts("-1");
	return 0;
}
```

整体代码不给了，大家自行组合一下。


---

## 作者：封禁用户 (赞：1)

#### 题目分析
这两棵树的坐标只可能有四种情况：

1. 横坐标相等，也就是 $x1=x2$，答案为 $x1+|y1-y2|$，$y1$，$x2+|y1-y2|$，$y2$。
2. 纵坐标相等，也就是 $y1=y2$，答案为 $x1$，$y1+|x1-x2|$，$x2$，$y2+|x1-x2|$。
3. 对角线相等，也就是 $|x1-x2|=|y1-y2|$，答案为 $x1$，$y2$，$x2$，$y1$。
4. 不是以上三种情况，输出 $-1$。
#### 代码
```cpp
#include<iostream>
using namespace std;
long long x1,y1,x2,y2;
long long f(long long s)
{
	if(s<0)s=-s;
	return s;
}
int main()
{
	cin>>x1>>y1>>x2>>y2;
	if(x1==x2)cout<<x1+f(y1-y2)<<" "<<y1<<" "<<x2+f(y1-y2)<<" "<<y2;
	else if(y1==y2)cout<<x1<<" "<<y1+f(x1-x2)<<" "<<x2<<" "<<y2+f(x1-x2);
	else if(f(x1-x2)==f(y1-y2))cout<<x1<<" "<<y2<<" "<<x2<<" "<<y1;
	else cout<<-1;
	return 0;
}
```

---

## 作者：Rainsleep (赞：1)


## ProblemLink : [CF459A Pashmak and Garden](https://www.luogu.com.cn/problem/CF459A)


### 题目并不难，不过需要细心一点，共三种情况。

- 两棵树的横坐标相等，有如下两种情况
![](https://cdn.luogu.com.cn/upload/image_hosting/hpi2xdox.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/p0w7iphv.png)

~~不会有人不知道正方形边长相等吧~~

由此我们通过 $|y2-y|$ 求出边长，再计算两外两棵树的坐标。

代码如下：
```cpp
if(x==x2)
{
   dist=abs(y-y2);
        
   node_ax=x+dist,node_ay=y;
   node_bx=x2+dist,node_by=y2;
   
}
```
- 两棵树的纵坐标相等，有如下两种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/zrsjf1t9.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/svp9ud2c.png)

通过 $|x2-x|$ 求出边长，计算坐标。

代码如下：
```cpp
if(y==y2)
{
   dist=abs(x-x2);
        
   node_ax=x,node_ay=y+dist;
   node_bx=x2,node_by=y2+dist;
        
}
```

- 两棵树在对方对角线上，有如下两种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/c063ckze.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/3on9uf45.png)

此时我们无需求出边长，仔细观察发现，其余两点的坐标可以由已有两点坐标$x,y,x2,y2$组合而成。
代码如下：
```cpp
if(abs(x-x2)==abs(y-y2))
{

   node_ax=x,node_ay=y2;
   node_bx=x2,node_by=y;

}
``` 
- 最后，若不符合上述三种情况，则无解，输出 $-1$  .

代码如下：
```
if(node_ax==inf or node_ay==inf or node_bx==inf or node_by==inf)
        puts("-1");
```

#### 完整代码如下，仅供参考，抄袭可耻。
```cpp
#include<bits/stdc++.h>

using namespace std;

int x,y,x2,y2;

const int inf=-INT_MAX;

//初始化
int node_ax=inf,node_ay=inf;
int node_bx=inf,node_by=inf;

int main()
{
    scanf("%d %d %d %d",&x,&y,&x2,&y2);
    int dist;
    if(y==y2)
    {
        dist=abs(x-x2);
        
        node_ax=x,node_ay=y+dist;
        node_bx=x2,node_by=y2+dist;
        
    }
    else if(abs(x-x2)==abs(y-y2))
    {

        node_ax=x,node_ay=y2;
        node_bx=x2,node_by=y;

    }
    else if(x==x2)
    {
        dist=abs(y-y2);
        
        node_ax=x+dist,node_ay=y;
        node_bx=x2+dist,node_by=y2;
    }
//若有点为inf则说明不符合情况
    if(node_ax==inf or node_ay==inf or node_bx==inf or node_by==inf)
        puts("-1");
    else
        printf("%d %d %d %d",node_ax,node_ay,node_bx,node_by);
        
    return 0;
}
```

**Update 2022/6/22： 添加题目链接。**







---

## 作者：Steven_Meng (赞：1)

题目不难，不过要仔细地分类讨论。
```cpp
#include <cstdio>
using namespace std;
bool ok(int a,int b){
    if (a<=1000&&a>=-1000&&b<=1000&&b>=-1000){
        return 1;
    }
    return 0;
}
int abs(int a,int b){
    return (a<b?b-a:a-b);
}
int main(){
    int x1,y1,x2,y2,cnt=0;
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    if (x1==x2||y1==y2){//为正方形一条边上的两个顶点
        if (x1==x2){
            int l=abs(y1,y2);
            if (ok(x2+l,y2)&&ok(x1+l,y1)){
                printf("%d %d %d %d\n",x1+l,y1,x2+l,y2);
                return 0;
            }
            if (ok(x2-l,y2)&&ok(x1-l,y1)){
                printf("%d %d %d %d\n",x1-l,y1,x2-l,y2);
                return 0;
            }
            printf("-1\n");
        }
        else{
            int l=abs(x1,x2);
            if (ok(x2,y2+l)&&ok(x1,y1+l)){
                printf("%d %d %d %d\n",x1,y1+l,x2,y2+l);
                return 0;
            }
            if (ok(x2,y2-l)&&ok(x1,y1-l)){
                printf("%d %d %d %d\n",x1,y1-l,x2,y2-l);
                return 0;
            }
            printf("-1\n");
        }
    }
    else {//正方形对角线上的顶点
        if (abs(x1,x2)==abs(y1,y2)){
            printf("%d %d %d %d",x1,y2,x2,y1);
            return 0;
        }
        else {
            printf("-1\n");
            return 0;
        }
    }
} 
```

---

## 作者：封禁用户 (赞：0)

# 题意(重点部分)

他记得花园看起来像一个平行于坐标轴的正方形，正方形的每一个顶点上都有一棵树。现在，他只知道其中两棵树的位置。帮助他找到剩下两个的位置。

# 思路

因为是正方形形状，所以有四种情况：

情况一：横坐标相等

情况二：纵坐标相等

情况三：对角线相等

情况四：不是以上情况

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20],b[20]; 
int main()
{
	cin>>a[1]>>b[1]>>a[2]>>b[2];//a[1]=x1,a[2]=x2,b[1]=y1,b[2]=y2
	if(a[1]==a[2]) cout<<a[1]+abs(b[1]-b[2])<<" "<<b[1]<<" "<<a[2]+abs(b[1]-b[2])<<" "<<b[2];//情况一
	else if(b[1]==b[2]) cout<<a[1]<<" "<<b[1]+abs(a[1]-a[2])<<" "<<a[2]<<" "<<b[2]+abs(a[1]-a[2]);//情况二
	else if(abs(a[1]-a[2])==abs(b[1]-b[2]))  cout<<a[1]<<" "<<b[2]<<" "<<a[2]<<" "<<b[1];//情况三
	else cout<<"-1";//情况四
	return 0;
}
```

---

## 作者：alex_liu (赞：0)

[题目转送门](https://www.luogu.com.cn/problem/CF459A)

# 思路：

因为花园的形状是正方形，所以分四种情况讨论（ Y 代表当前坐标上有树， N 代表没有）。

**1：两个横坐标相等（ $x_1=x_2$ ）：**

| Y | Y |
| :----------: | :----------: |
| N | N |

或者：

| N | N |
| :----------: | :----------: |
| Y | Y |

**2：两个纵坐标相等（ $y_1=y_2$ ）:**

| Y | N |
| :----------: | :----------: |
| Y | N |

或者：

| N | Y |
| :----------: | :----------: |
| N | Y |

**3：对角线（ $|x_1-x_2|=|y_1-y_2|$ ）:**

| Y | N |
| :----------: | :----------: |
| N | Y |

或者：

| N | Y |
| :----------: | :----------: |
| Y | N |


**4：以上情况都不是，输出“ $-1$ ”**

理完了思路，就来看代码吧！

# AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int x[3],y[3];//定义 
	cin>>x[1]>>y[1]>>x[2]>>y[2];//输入 
	if(x[1]==x[2])cout<<x[1]+abs(y[1]-y[2])<<" "<<y[1]<<" "<<x[2]+abs(y[1]-y[2])<<" "<<y[2]<<endl;//第一种情况（横坐标相等） 
	else if(y[1]==y[2])cout<<x[1]<<" "<<y[1]+abs(x[1]-x[2])<<" "<<x[2]<<" "<<y[2]+abs(x[1]-x[2])<<endl;//第二种情况（纵坐标相等） 
	else if(abs(x[1]-x[2])==abs(y[1]-y[2])) cout<<x[1]<<" "<<y[2]<<" "<<x[2]<<" "<<y[1]<<endl;//第三种情况（对角线） 
	else cout<<"-1"<<endl;//第四种情况（啥都不是） 
	return 0;//完美结束 
}
```


---

## 作者：ylinxin2010 (赞：0)

## CF459A题解
这题输入我们分四种情况讨论。

1. 输入的两个横坐标相等( $x_1=x_2$ )。

2. 输入的两个纵坐标相等( $y_1=y_2$ )。

3. 输入的两个横坐标与纵坐标的差的绝对值相等( $ \left | x_1-y_1 \right | = \left | x_2-y_2 \right |$ )。

4. 不是以上所有情况。

输出同上，也分四种情况讨论。

1. 输出 $x_1 + \left | y_1-y_2 \right |,\ y_1,\ x_2+\left | y_1-y_2 \right |,\ y_2$ 。

2. 输出 $x_1,\ y_1+ \left | x_1-x_2 \right |,\ x_2,\ y_2+\left | x_1-x_2 \right |$ 。

3. 输出 $x_1,\ y_2,\ x_2,\ y_1$ 。

4. 输出-1。

接下来——上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x[10], y[10];
	cin>>x[1]>>y[1]>>x[2]>>y[2];
	if(x[1]==x[2])
		cout<<x[1]+abs(y[1]-y[2])<<" "<<y[1]<<" "<<x[2]+abs(y[1]-y[2])<<" "<<y[2];
	else if(y[1]==y[2])
		cout<<x[1]<<" "<<y[1]+abs(x[1]-x[2])<<" "<<x[2]<<" "<<y[2]+abs(x[1]-x[2]);
	else if(abs(x[1]-x[2])==abs(y[1]-y[2])) 
		cout<<x[1]<<" "<<y[2]<<" "<<x[2]<<" "<<y[1];
	else
	 	cout<<"-1";
	return 0;
}
```

---

## 作者：oimaster (赞：0)

这道题和最近一场比赛的题几乎一致，所以题解的很多公式也是从原来我写的题解抄来的 QAQ![youl](https://cdn.luogu.com.cn/upload/pic/69020.png)![youl](https://cdn.luogu.com.cn/upload/pic/69020.png)

原题解：<https://www.luogu.com.cn/blog/oimaster/solution-cf1512b>

---

分几种情况讨论。

1. $(x_1=x_2)\land(y_1\not=y_2)$，那么另外两棵树肯定在 $y_1$ 和 $y_2$ 列上。为了保证我们的花园是正方形，我们可以算出 $y_1$ 和 $y_2$ 的差，然后让两个 $x$ 加上就可以了。
2. $(x_1\not=x_2)\land(y_1=y_2)$ 和 $(x_1=x_2)\land(y_1\not=y_2)$ 同理。我们可以算出 $x_1$ 和 $x_2$的差，然后用两个 $y$ 加上这个差。
3. $(x_1\not=x_2)\land(y_1\not=y_2)$，我们需要判断 $x_1$ 和 $x_2$ 的差是不是等于 $y_1$ 和 $y_2$ 的差。如果一样，剩下的两个点在 $(x_1,y_2),(x_2,y_1)$。否则，就无解。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdlib>
#define int long long
using namespace std;
void output(int x3,int y3,int x4,int y4,bool ok=true){
	if(ok==false){
		cout<<-1<<endl;
		exit(0);
	}
	cout<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<endl;
	exit(0);
}
signed main(){
	int x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	if(x1==x2){
		int d=max(y1,y2)-min(y1,y2);
		output(x1+d,y1,x1+d,y2);
	}
	if(y1==y2){
		int d=max(x1,x2)-min(x1,x2);
		output(x1,y1+d,x2,y1+d);
	}
	int d1=max(x1,x2)-min(x1,x2);
	int d2=max(y1,y2)-min(y1,y2);
	if(d1!=d2)
		output(0,0,0,0,false);
	output(x1,y2,x2,y1);
}
```

---

## 作者：sysu_yzc (赞：0)

## 思路
① $x1!=x2$且$y1!=y2$

如果$|x1-x2|==|y1-y2|$，则输出$x1,y2,x2,y1$

② $x1==x2$，输出$x1+(y1-y2),y1,x1+(y1-y2),y2$

③ $y1==y2$，输出$x1,y1+(x1-x2),x2,y1+(x1-x2)$
## 上代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int abs(int a){return a<0?-a:a;}
int main(){
    int x1,x2,y1,y2;
    cin>>x1>>y1>>x2>>y2;
    if(x1!=x2&&y1!=y2){
        if(abs(x1-x2)==abs(y1-y2)) printf("%d %d %d %d",x1,y2,x2,y1);
        else cout<<-1;
        return 0;
    }
    if(x1==x2) printf("%d %d %d %d",x1+(y1-y2),y1,x1+(y1-y2),y2);
    else printf("%d %d %d %d",x1,y1+(x1-x2),x2,y1+(x1-x2));
    return 0;
}
```

---

