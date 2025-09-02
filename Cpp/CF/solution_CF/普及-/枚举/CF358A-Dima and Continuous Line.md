# Dima and Continuous Line

## 题目描述

在 $x$ 轴上存在 $n$ 个点 $(x_1,0),(x_2,0),(x_3,0),\dots ,(x_n,0)$，以相邻两点 $(x_i,0)$ 与 $(x_{i+1},0)$ 的连线作为直径向上作半圆，问是否有除 $x$ 轴上的交点。

## 说明/提示

$1 \le n \le 10^3, -10^6 \le x_i \le 10^6$。

## 样例 #1

### 输入

```
4
0 10 5 15
```

### 输出

```
yes
```

## 样例 #2

### 输入

```
4
0 15 5 10
```

### 输出

```
no
```

# 题解

## 作者：muyang_233 (赞：5)

[原题传送门](https://www.luogu.com.cn/problem/CF358A)  
  
根据初中平面几何知识或高中解析几何知识，我们可以知道，两个圆有交点有**三**种情况：  
 1. 内切  
 2. 相交  
 3. 外切
 
我们知道，若两圆**相切**，那么**切点**与**两圆圆心**这三点共线。  
放到本题中，若两圆**相切**，那么**切点**在**两圆圆心连线**上，即在 $x$ 轴上，与题目不符。故我们只需考虑**相交**即可。  
我们又知道，相交两圆的半径 $r_1$，$r_2$ 与两圆心之间的距离 $d$ 有如下关系：  
$$\left | r_1 - r_2 \right | < d < r_1 + r_2$$  
而我们又知道直径两端点的坐标，从而根据中点公式，圆心是易求的，这样半径和距离都易求。不在赘述。  
而 $n \le 10^3$，故我们可以直接采用 $O(n^2)$ 复杂度的算法进行计算。  
代码如下：  
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
double a[1005];
inline void input(int &x){
	x=0;char ch=getchar();int p=1;
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if (ch=='-') p=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();x*=p;
}
inline bool check(int _1,int _2){//判断两圆是否相交
	double O1=(a[_1]+a[_1+1])/2.0;//计算第一个圆的圆心
	double O2=(a[_2]+a[_2+1])/2.0;//计算第二个圆的圆心
	double R1=abs(a[_1]-O1);//计算第一个圆的半径
	double R2=abs(a[_2]-O2);//计算第二个圆的半径
	return abs(O1-O2)<R1+R2&&abs(O1-O2)>abs(R1-R2);//判断
}
int main(){
	while(scanf("%d",&n)==1){
		for (int i=1;i<=n;i++) scanf("%lf",&a[i]);
		bool ok=false;
		for (int i=1;i<n-1;i++){//枚举第一个圆
			for (int j=i+1;j<n;j++){//枚举第二个圆
				ok|=check(i,j);//判断两圆是否相交
				if (ok) {i=n;break;}
			}
		}
		puts(ok?"yes":"no");
	}
	return 0;
}
```

---

## 作者：lizhengdong (赞：2)

## 1.题目分析
题目意思就是让我们判断有没有两个半圆有除 $x$ 轴上的交点，有输出 yes，没有输出 no。

我们考虑圆有怎样的情况会有交点，显然只有三种情况：内切，相交，外切。因为相切时交点一定在 $x$ 轴上，所以不用考虑。

## 2.解题思路
那我们怎样判断相交呢?

我们先求出圆心和半径，两个圆互相比较，第一个圆的半径为 $r1$，第二个圆的半径为 $r2$，圆心的距离为 $d$。

然后我们会发现：
- 当 $\vert r1-r2\vert=d$ 为内切。
- 当 $r1+r2=d$ 为外切。

而相交就在两者之间，所以我们只要判断:
$$
\vert r1-r2\vert<d<r1+r2
$$
## 3.AC代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j;
double d1,d2,r1,r2,d,a[1010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(i=1;i<=n;i++)cin>>a[i];
    for(i=1;i<n;i++)
        for(j=i+1;j<n;j++){//两重for枚举
            d1=1.0*(a[i]+a[i+1])/2;//求圆心
            d2=1.0*(a[j]+a[j+1])/2;
            r1=abs(a[i]-d1);//求半径
            r2=abs(a[j]-d2);
            d=abs(d1-d2);//求圆心之间的距离
            if(abs(r1-r2)<d&&d<r1+r2){//判断
                cout<<"yes";
                return 0;
            }
        }
    cout<<"no";
}
```

---

## 作者：WhiteSunFlower (赞：2)

不多BB，直接开始。

~~学过数学的都知道~~，若两圆有交点，那么肯定满足两圆圆心的距离小于两圆半径和，我们假设两个半圆的端点为 $l,r,L,R$  $(l<r ; L<R)$ ，即：

$ {\LARGE \left | \frac{l+r}{2} - \frac{L+R}{2} \right | <  \frac{r-l}{2} - \frac{R-L}{2}} $

化简得出：

$ {\large L<l<R<r}$  或者 ${\large l<L<r<R}$

由于 $n \leq 1000$ 我们可以暴力 $O(n^{2})$ 解决。

## $AC$ $code $

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,u[1003],v[1003];
int main(){
	while(cin >> n){
		for(int i=0;i<=1000;i++)u[i]=v[i]=0;
		cin >> u[1];
		for(int i=1;i<=n-1;i++){
			cin >> v[i];
			u[i+1]=v[i];
		}//简单处理出端点
		bool check=1;//是否找到交点
		for(int i=1;i<=n-1&&check;i++){
			int l=u[i],r=v[i];
			if(l>r)swap(l,r);
			for(int j=1;j<=n-1&&check;j++){
				if(i==j)continue;
				int L=u[j],R=v[j];
				if(L>R)swap(L,R);
				if(L<l&&l<R&&R<r||l<L&&L<r&&r<R){
					check=0;//找到直接退出
				}
			}
		}
		if(check)puts("no");
		else puts("yes");
	}
	return 0;
}
```


---

## 作者：conti123 (赞：1)

### 思路
因为 $1\le{n}\le{10^3}$

所以我们直接暴力枚举。
### 分析
根据数学书的某一页，两个圆一共有 $5$ 种状态，分别是外离，外切，内切，相交，内含。其中有交点的是外切，内切，相交。它们的图像如下所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/trmdb2zp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

~~再根据数学书的某一页~~，若两圆相切，则切点在两圆连心线上，而两圆圆心都在 $x$ 轴上，所以其连心线也一定和 $x$ 轴重合，显然不为所求。所以我们就是要判断是否有两圆相交。

设两圆半径分别为 $R$ 和 $r$，两圆的圆心距为 $d$，若两圆相交，满足:
$R-r<d<R+r$

由于我们知道了直径，所以圆心的位置是可以算出来的，所以圆心距也能算出来。其具体公式为：

$O=x_{1}+r$

所以我们就可以开始暴力出奇迹了。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[10001];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    	scanf("%lld",&a[i]);
    for(int i=1;i<n;i++)
    	for(int j=1;j<n;j++)
    		if(i!=j)
    		{
		    	double r1=abs(a[i+1]-((a[i+1]+a[i]))/2.0),r2=abs(a[j+1]-((a[j+1]+a[j]))/2.0),d=abs((a[j+1]+a[j])/2.0-(a[i+1]+a[i])/2.0);
		    	if(d<abs(r2+r1)&&d>abs(r2-r1))
		    		puts("yes"),exit(0);
		    }
	puts("no");
}
```

---

## 作者：czyczyczyczyczy (赞：1)

## 废话

这里提供一个稍微简单一些的解法。~~我看别的题解都好长啊~~

## 题目大意

就是给出一系列在一根数轴上的点，以相邻两个点为直径向上做一个半圆，问是否存在两个半圆在数轴上方有相交的情况。

## 题目分析

要想在数轴上方相交，那么两个区间一定在数轴上是有交集的（显然）。

所以在处理的时候我们把相邻的两个点放进结构体存储，然后直接暴力枚举两个半圆，判断它们在数轴上的区间有没有相交即可。

具体在判断的时候的过程如下：

首先第一维循环$i$从$1$到$n$，接着第二位$j$也是从$1$到$n$，这两个变量$i,j$分别枚举两个半圆，也就是四个点，在判断是否相交的时候方法是：我们设$u_i(左端点),v_i(右端点)$代表的是由变量$i$枚举到的点对，$u_j,v_j$同理，既然是要相交，那么肯定某一个点对中的右端点要大于另一个点对中的左端点，**但是这样还不够，有可能一个区间整个在另一个区间的左侧或右侧或者两个区间存在包含关系**，知道了特例情况，我们就可以写出限制条件：$u_i<u_j$并且$v_i>u_j$前两个条件保证了两个区间一定有交集，但是存在包含关系还无法处理，这是再加一个条件：$u_i<v_j$这样就保证了没有包含的情况。

## 放一下我丑陋的代码，码风奇丑，大佬勿喷

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int l,r;
}a[100010];
int main(){
    int n;
    while(cin>>n){
        int x,last,cnt = 0;
        cin>>x;
        if(n == 1){//特盘如果只有一个点对（半圆）则肯定没有交集
            cout<<"no"<<endl;
            continue;
        }
        last = x;
        for(int i = 2;i <= n;i++){//输入
            cin>>x;
            a[++cnt].l = min(last,x);//防止题目挖坑，保证左端点一定小于右端点
            a[cnt].r = max(x,last);
            last = x;
        }
        bool flag = 0;
        for(int i = 1;i <= cnt;i++){//枚举点对
            for(int j = 1;j <= cnt;j++){
                if(a[i].l < a[j].l && a[i].r < a[j].r && a[i].r > a[j].l){//如果枚举到两个点对有交集就直接输出
                    cout<<"yes"<<endl;
                    flag = true;
                    break;
                }
            }
            if(flag)break;
        }
        if(!flag){//如果把所有的点对都枚举完了还没有出现有交集的情况，则认定为没有交集
            cout<<"no"<<endl;
        }
    }
    return 0;
}
```



---

## 作者：yutong_Seafloor (赞：0)

# [题目在这里 ·CF358A Dima and Continuous Line ](https://www.luogu.com.cn/problem/CF358A) 

### 题目简要：
$x$ 轴上有 $n$ 个点，$x$ 轴上会有 $n-1$ 个圆，每个圆会以点 $i$ 和右边的点 $i+1$ 之间的距离为直径画圆（隐含圆心为直径的中点），求半圆和半圆直接在除 $x$ 轴以外的地方有没有交点。

------------
### 题意分析

其实就是圆和圆直接相不相交的问题，就是两个圆之间有没有重合的部分，在这个题里 $x$ 轴上的相交不计数，也就是圆和圆必须有非边重合的部分，然后结合一下初三学的知识：

设圆心之间距离为 $d$，半径为 $r1$，$r2$。

下三张图片中大圆半径为 $2$，小圆半径为 $1$。

相切：$d=r1+r2$   
![](https://cdn.luogu.com.cn/upload/image_hosting/kkxg55e9.png)

相交：$d<r1+r2$  
![](https://cdn.luogu.com.cn/upload/image_hosting/weerb4mn.png)
相离：$d>r1+r2$  
![](https://cdn.luogu.com.cn/upload/image_hosting/sog27pgt.png)

然后只需要算一下圆心的位置算出 $d$，求一下半径，套个公式就可以了。

另外，相交的话还需要园新居里大于两个半径相减，一个比一个大也是不可以的。

![](https://cdn.luogu.com.cn/upload/image_hosting/2w8ea3wl.png)


------------

圆心的计算是两个点之间的中点（以两点之间的距离为直径），半径就是一个点的坐标减去圆心的坐标。

注意取绝对值，因为题目没说这几个点是按照顺序输入的，而且点的坐标可能取负。

------------
## 代码 
```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,a[1010],i,j;
double o1,o2,r1,r2,d;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	cin>>a[i];
	for(i=1;i<=n-1;i++)//一共是n-1个圆，所以一个只要枚举到n-1就行了
	for(j=i+1;j<=n;j++)
	{
		o1=(a[i]+a[i+1])/2.0,o2=(a[j]+a[j+1])/2.0;//圆心可能是带有小数的
		r1=abs(a[i]-o1),r2=abs(a[j]-o2);
		d=abs(o1-o2)*1.0;
		if(abs(r1-r2)<d && d<r1+r2)//条件成立
		{
			cout<<"yes";
			return 0;
		}
	}
	cout<<"no";
	return 0;
}//by·yutong_Seafloor
```

---

## 作者：Last_kiss_Snow_Dog6 (赞：0)

# [题目](https://www.luogu.com.cn/problem/CF358A)
# 分情况

可以大致分为两种情况（其实就是一种）：一种是样例中的 $ x_{1} < x_{3} < x_{2} < x_{4} $， 另一种是 $ x_{3} < x_{1} < x_{4} < x_{2} $。分别可以画出两个图：

情况1：

![](https://cdn.luogu.com.cn/upload/image_hosting/18cs0xq8.png)

情况2：

![](https://cdn.luogu.com.cn/upload/image_hosting/iebwn6q1.png)

# 分析

不难看出来这两种情况的本质就是让每个半圆的两个交点互相隔开，但是要注意题目中点的顺序不是排序好的，而且如果当点为一个时，那么就相当于组不生一个半圆。如果当点为两个时，只有一个半圆或者看成两个半圆重合。如果点数为三个，那么就相当于一个半圆里套了另一个半圆所以不可能有交点或者是两个圆一个向右可以找到这个半圆的另一个交点一个向左可以找到这个半圆的另一个交点。所以当 $ n\le 3 $ 时不可能满足题意（需要特判）。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int maxn = 1000 + 10;
int a[maxn], tmp1[5], tmp2[5];

int main()
{
    int i, j, n, flag;
    cin>>n;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    if (n <= 3)
    {
        printf("no\n");
    }
    else
    {
        flag = 0;
        for (i = 2; i < n-1; i++)
        {
            if (a[i] > a[i+1])
            {
                tmp1[0] = a[i+1];
                tmp1[1] = a[i];
            }
            else
            {
                tmp1[0] = a[i];
                tmp1[1] = a[i+1];
            }
            for (j = 0; j < n-1; j++)
            {
                if (a[j] > a[j+1])
                {
                    tmp2[0] = a[j+1];
                    tmp2[1] = a[j];
                }
                else
                {
                    tmp2[0] = a[j];
                    tmp2[1] = a[j+1];
                }
                if ((tmp1[0] > tmp2[0] && tmp1[0] < tmp2[1] && tmp1[1] > tmp2[1]) || (tmp1[0] < tmp2[0] && tmp1[1] > tmp2[0] && tmp1[1] < tmp2[1]))
                {
                    flag = 1;
                    goto h;
                }
            }
        }
h:      if (!flag)
            printf("no\n");
        else
            printf("yes\n");
    }
    return 0;                                                                                                                                
}
//QAQ                                                                                                                                                   
```

---

## 作者：GuoJZ2010 (赞：0)

先看数据范围，$1 \le n \le 10^3$，直接暴力枚举每个点。

运用数学知识，可知平面内的圆有交点的情况为**相切与相交**，而相切可视为交点在 $x$ 轴上的情况，故求相交。

看下面这张相交的例图，我们发现：

![相交](https://cdn.luogu.com.cn/upload/image_hosting/04zx9z34.png)

- $|r1-r2|<d<r1+r2$。

至于相切：

![相切](https://cdn.luogu.com.cn/upload/image_hosting/wpm8xb9a.png)

- $r1+r2=d$。

没有交点：

![](https://cdn.luogu.com.cn/upload/image_hosting/uoj609j3.png)

- $r1+r2<d$。

而我们知道圆两端点的坐标，**圆心即为 $\frac{\lvert i-j \rvert}{2}$，如此便可以求半径 $ \lvert i-r \rvert$，$d$ 为 $ \lvert o1-o2 \rvert$**。题目便迎刃而解。

最后贴上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long//不建议#define int long long，因为现在要求主函数的返回类型必须是int
#define ull unsighed long long
#define N 5100
#define M 510000
#define inf 2147483647
using namespace std;
int n,a[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n-2;i++){
		for(int j=i+1;j<=n-1;j++){
			double o1=(a[i]+a[i+1])/2.0*1.0;//第一个圆的圆心
			double o2=(a[j]+a[j+1])/2.0*1.0;//第二个圆的圆心
			double r1=abs(a[i]-o1);//第一个圆的半径
			double r2=abs(a[j]-o2);//第二个圆的半径
			double d=abs(o1-o2)*1.0;//求两圆心之间的距离
			if(r1+r2>d&&abs(r1-r2)<d) {
				cout<<"yes"<<endl;
				return 0;
			}
		}
	}
	cout<<"no"<<endl;
	return 0;
}

```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF358A)

------------
# 题意：
在横坐标上给出 $n$ 个不同的点，需要把前一个点跟后一个点（这两个点的顺序是紧挨着的）用一个半圆弧来连接。现在要判断的是这些符合条件的点连接以后，圆弧之间是否相交了。是则输出 ```yes```，否则输出 ```no```。

------------
# 思路：
假设序列是 ```x[1],x[2],x[3],x[4]......x[n]```。相交其实只有两种情况，第一种就是样例已经给出了的：即 ```x[1]<x[3]<x[2]``` 且 ```x[2]<x[4]```。另外一种情况就是第一种情况的对称位置 ```x[3]<x[1]``` 且 ```x[1]<x[4]<x[2]```。

要特别注意的是，由于序列中前后两个数不是按从小到大的顺序排好的，因此要先确保前一个数要大于后一个数。另外，当 $n \le 3$ 时，是绝对不会发生交叉的。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N=1e6+10;
int n,flag,a[N],tmp1[N],tmp2[N];
signed main(){
    cin>>n;
	for(int i=0;i<n;i++){
        cin>>a[i];
    }
    if(n<=3){
        cout<<"no"<<endl;
    }else{
        flag=0;
        for(int i=2;i<n-1;i++){
            if(a[i]>a[i+1]){
                tmp1[0]=a[i+1];
                tmp1[1]=a[i];
            }else{
                tmp1[0]=a[i];
                tmp1[1]=a[i+1];
            }
            for(int j=0;j<n-1;j++){
                if(a[j]>a[j+1]){
                    tmp2[0]=a[j+1];
                    tmp2[1]=a[j];
                }else{
                    tmp2[0]=a[j];
                    tmp2[1]=a[j+1];
                }
                if((tmp1[0]>tmp2[0]&&tmp1[0]<tmp2[1]&&tmp1[1]>tmp2[1])||(tmp1[0]<tmp2[0]&&tmp1[1]>tmp2[0]&&tmp1[1]<tmp2[1])){
                        flag=1;
                    }
                }
        }
    	if(!flag){
			cout<<"no"<<endl;
		}else{
	        cout<<"yes"<<endl;
		}
    }
    return 0;
}
```

---

## 作者：Moon_Traveller (赞：0)

[>> 传送门 <<](/problem/CF358A)

[>> 原 OJ 传送门 <<](https://codeforces.com/problemset/problem/358/A/)

感觉其他题解的方法都有点麻烦，于是诞生了这篇「线段法」题解。

~~才不是为了咕值。~~

### 题目大意

给出坐标轴上的 $n$ 个点 $x_1,x_2,\dots,x_n$，以相邻的点 $x_i$ 与 $x_{i+1}$ 所连线段为直径，在坐标轴上方画半圆。

如果在坐标轴的上方，有半圆的交点，输出 `yes`；否则输出 `no`。

注意：「相邻」的点是按输入的顺序，而不是坐标轴上的顺序。

### 思路

将半圆压扁，看作线段。

然后将输入的线段，按坐标轴上的顺序排序。

然后两层循环枚举线段，判断是否有（除端点外的）交点。

### 实现

使用结构体 struct 存储线段，分别用 $u,v$ 存储左右两个端点。

排序：

1. 左端点小的在前面。
2. 若左端点相同，则右端点小的在前面。

判断交点：

因为先前已经将线段排序，所以只需要判断（设靠左的线段为 $x$，靠右的线段为 $y$）：

1. $x_u \lt y_u \lt x_v$（$y$ 的左端点在 $x$ 的两个端点之间）
2. $y_v \gt x_v$（$y$ 的右端点在 $x$ 的右端点的右面）

可能稍微有一点点绕，可以自己画一个图辅助理解。

### 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int u; // 左端点
    int v; // 右端点
};

int n;
int x[1003]; // 存储每个点的坐标
Node l[1003]; // 结构体存线段

bool cmp(Node a, Node b)
{
    if(a.u == b.u)
    {
        return a.v < b.v;
    }
    return a.u < b.u;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for(int i = 1; i < n; i++)
    {
        l[i].u = min(x[i], x[i + 1]); // 判断大小，区分左右端点
        l[i].v = max(x[i], x[i + 1]);
    }
    sort(l + 1, l + n, cmp); // 排序
    for(int i = 2; i < n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(l[i].u > l[j].u && l[i].u < l[j].v && l[i].v > l[j].v)
            {
                cout << "yes" << endl; // 有交点，直接输出，并结束程序
                return 0;
            }
        }
    }
    cout << "no" << endl; // 运行到了这里，说明没有交点
    return 0;
}
```

---

## 作者：Floating_Trees (赞：0)

#### 花了我~~11451秒~~一个小时才调出来的一道题

[题目传送门](https://www.luogu.com.cn/problem/CF358A)

# 题目大意
给你 $x$ 轴上的 $n$ 个点，以 $(x_i,0)$和$(x_{i+1},0)$ 为直径做半圆，问有没有不在 $x$ 轴上的交点

# 题目分析
如果要使有交点，第一个半圆的两个顶点形成的区间，和第二个半圆的两个顶点形成的区间要有交集，所以可以用一个 vector 来记录所有的区间。
因为 $n \le 1000$ 所以直接暴力枚举所有的区间，在进行判断即可。
# AC 代码
``` cpp
#include "bits/stdc++.h"

using namespace std;

const int maxn = 1010;
int n,a[maxn];

struct range //用结构体记录区间

{
	int u,v;
};
vector<range> v; //vector记录所有区间

bool judge(range a,range b) //判断两个半圆有没有交点
{
	/* 如果区间的两个点在同一位置，
           则肯定不行，返回false */
	if (a.u == a.v || b.u == b.v)
		return false;
        /* 判断两个区间是否有相交，如果
           两个左端点相同，或两个区间的
           左端点和右端点相同，则只有一
           个在x轴上的交点 */
	return a.u > b.u && a.u < b.v && a.v > b.v || 
               b.u > a.u && b.u < a.v && b.v > a.v;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	for (int i = 1;i <= n;i++)
		cin >> a[i];
	
	for (int i = 1;i < n;i++)
	{
		range temp;
		// 将所有区间加入到的vector
		if (a[i] < a[i+1])
			temp.u = a[i],temp.v = a[i+1];
		else
			temp.u = a[i+1],temp.v = a[i];
		v.push_back(temp);
	}
	
	for (int i = 0;i < v.size();i++)
		for (int j = 0;j < v.size();j++)
			if (i != j)
				if (judge(v[i],v[j]))
                                {
                                    cout << "yes";
                                    return 0;
                                }
	cout << "no";
	
	
	
	return 0;
}


```

---

## 作者：Muruski (赞：0)

### 看没有C++的代码，过来水一发



题意不说了


假设n个点中 x1 和 x2之间有半圆弧，x3 和 x4 之间有半圆弧。

则当满足 程序注释中8种情况时相交。

这个思路极其暴力...但是我没有脑子去思考更多的解答了...

```cpp
#include <bits/stdc++.h>

using namespace std;
 
int t[1010];
 
int main()
{
    int n,flag;
    while(scanf("%d",&n)!=EOF)
    {
        flag=0;
        for(int i=0;i<n;i++)
            scanf("%d",&t[i]);
        for(int i=0;i<n-1;i++)
        {
            for(int j=i+1;j<n-1;j++)
            {
                if(t[i]<t[j] && t[j]<t[i+1] && t[i+1]<t[j+1])  //1<3<2<4
                {
                    puts("yes");
                    flag=1;
                    break;
 
                }
                if(t[i+1]<t[j] && t[j]<t[i] && t[i]<t[j+1])  //2<3<1<4
                {
                    puts("yes");
                    flag=1;
                    break;
 
                }
                if(t[i]<t[j+1] && t[j+1]<t[i+1] && t[i+1]<t[j]) //1<4<2<3
                {
                    puts("yes");
                    flag=1;
                    break;
 
                }
 
                if(t[i+1]<t[j+1] && t[j+1]<t[i] && t[i]<t[j]) //2<4<1<3
                {
                    puts("yes");
                    flag=1;
                    break;
 
                }
 
                if(t[j+1]<t[i+1] && t[i+1]<t[j] && t[j]<t[i]) //4<2<3<1
                {
                    puts("yes");
                    flag=1;
                    break;
 
                }
                if(t[j+1]<t[i] && t[i]<t[j] && t[j]<t[i+1]) //4<1<3<2
                {
                    puts("yes");
                    flag=1;
                    break;
 
                }
                if(t[j]<t[i] && t[i]<t[j+1] && t[j+1]<t[i+1]) //3<1<4<2
                {
                    puts("yes");
                    flag=1;
                    break;
                }
                if(t[j]<t[i+1] && t[i+1]<t[j+1] && t[j+1]<t[i]) //3<2<4<1
                {
                    puts("yes");
                    flag=1;
                    break;
                }
            }
            if(flag) break;
        }
        if(!flag)
            puts("no");
    }
    return 0;
}

```


---

