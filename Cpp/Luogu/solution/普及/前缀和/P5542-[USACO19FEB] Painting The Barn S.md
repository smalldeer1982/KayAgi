# [USACO19FEB] Painting The Barn S

## 题目描述

农夫约翰不擅长多任务处理。他经常分心，很难完成长的项目。目前，他正试图在谷仓的一侧上漆，但他一直在画小矩形区域，然后由于照料奶牛的需要而偏离了方向，使得谷仓的某些部分上漆的涂料比其他部分多。

我们可以将谷仓的一侧描述为一个二维 $x-y$ 平面，农夫约翰在该平面上绘制 $n$ 个矩形，每个矩形的边都与坐标轴平行，每个矩形由谷仓的左下角和右上角点的坐标描述。

农夫约翰想在谷仓上涂几层油漆，这样在不久的将来就不需要再重新粉刷了。但是，他不想浪费时间涂太多的油漆。结果表明，$K$ 涂层是最佳用量。请在他画完所有的长方形后，帮他确定谷仓有多少面积被 $K$ 层油漆覆盖。

## 说明/提示

$1\le K\le n\le 10^5$。

USACO 2019 二月月赛银牌组第二题。

## 样例 #1

### 输入

```
3 2
1 1 5 5
4 4 7 6
3 3 8 7```

### 输出

```
8```

# 题解

## 作者：liangsheng (赞：65)

#### 看了一下题解,没有讲的非常详细的,第一次接触二维差分不画图的话挺难理解的
#### ~~所以我来一发详细一点的题解,给像我一样的蒟蒻一点温暖~~

#### 废话不多,进入正题


#### 1. 二维前缀和 (这里引用一下别人的图,实现画不出来)

首先我们学习二维差分的之前需要先了解二维前缀和

如图:

![](https://ftp.bmp.ovh/imgs/2019/09/eb4e2fc7d31000de.png)

因为是从左到右，从上到下的遍历，当要求红色部分，(0,0) 到（i, j）处的前缀和时，我们黄色部分和蓝色部分已经是已知的了，而它们重叠的部分就是绿色部分，所以把黄色和蓝色部分的结果加起来，再减去绿色部分，最后加上 (i, j) 处的值就是（i, j）位置的前缀和了。

所以，二维前缀和就是:

`sum[i][j]=a[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]`



而我们要求左上角是(x1,y1),右下角是(x2,y2)的矩形区间内的值处理出前缀和后也可以O(1)时间内求出来。

如图:

![](https://ftp.bmp.ovh/imgs/2019/09/5b0dcfa9f83b66c2.png)

我们要求紫色部分的值，我们已知的是黄色部分的值，但它多了两个蓝色部分的值，而两个蓝色部分有重叠了个绿色部分

所以要求的区间内的值就是:

```sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][x2-1]```



#### 2. 二维差分 
(下面是自己画的图,画的不好,将就一下)

我们以这题的样例来解释什么是二维差分



首先给出结论:

    
    若想在点(x1,y1)到点(x2,y2)围成的矩形的每个位置增加1
    则我们要进行以下操作:
    
    设vis[i][j]:原点到点(i,j)围成的矩形的总和
    
 ```
	vis[x1 + 1][y1 + 1]++;
    vis[x2 + 1][y2 + 1]++;
    vis[x1 + 1][y2 + 1]--;
    vis[x2 + 1][y1 + 1]--;
```


我们给出根据样例的三组数据实现后的坐标轴:

![](https://ftp.bmp.ovh/imgs/2019/09/3753ef488437db85.png)

黑色线段围成的矩形就是每次要加1的矩形



下面我们解释为什么要这样做:

![](https://ftp.bmp.ovh/imgs/2019/09/afe11ca0fc3cce47.png)

我们就以 点(1,1) 和 点(5,5)为例讲解

```
首先 vis[2][2]++;

而 vis[2][2] 的值改变,谁的值会受影响呢?

很明显: i >= 2 && j >= 2的vis[i][j]的值全部都会收到影响

我们先来看 i = 2,j >= 2的情况  也就是点(1,1)到点(2,6)橙色长方形

我们令 vis[2][6]--  进行此操作后 我们会发现 
vis[2][j >= 5]的值又不会受到影响了
    
很简单,我们来证明一下: 令 j=7

     想象一下点(0,0)和点(2,7)围成的矩形	
     我们会发现 点(2,2)加的1 和点(2,6)减的1 抵消了
     故不会受影响了
     证毕
        				
这里明白后其他两处加1和减1就也能明白了
```


不明白的话多看几遍,深度理解

而之后的操作我在这里也给出:

    int ans = 0;
    for(int i = 1; i <= 1000; i++) {
       for(int j = 1; j <= 1000; j++) {
       	    vis[i][j] += vis[i - 1][j] + vis[i][j - 1] - vis[i - 1][j - 1];
            if(vis[i][j] == k) ans++;
       }
    }
    cout << ans << endl;


然后我给出最终 vis 数组中的值,方便加深理解

![](https://ftp.bmp.ovh/imgs/2019/09/b7fe76441539135d.png)

最后,给出本题的AC代码:
```cpp
#include <iostream>
#include <cstring>

using namespace std;

int n, k;
int vis[1005][1005];

int main() {
    cin >> n >> k;
    int x1, y1, x2, y2;
    for(int i = 1; i <= n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        vis[x1 + 1][y1 + 1]++;
        vis[x2 + 1][y2 + 1]++;
        vis[x1 + 1][y2 + 1]--;
        vis[x2 + 1][y1 + 1]--;
    }
    int ans = 0;
    for(int i = 1; i <= 1000; i++) {
        for(int j = 1; j <= 1000; j++) {
            vis[i][j] += vis[i - 1][j] + vis[i][j - 1] - vis[i - 1][j - 1];
            if(vis[i][j] == k) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}

```


---

## 作者：zhy137036 (赞：14)

从一维差分到二维差分超详细题解，并严格遵守题解审核要求。
# 一、题意简述
- 给你 $n$ 个第一象限的矩形。
- 第$i$个矩形的左下角的坐标为 $(x1_i,y1_i)$，右上角的坐标为 $(x2_i,y2_i)$，均是整数。
- 求正好被 $k$ 个矩形覆盖的面积。
- $1\leqslant k\leqslant n\leqslant10^5$，$0\leqslant x1_i,x2_i,y1_i,y2_i\leqslant10^3$。
# 二、题目分析
## 1.基本思路
首先我们把第一象限拆成 $1000\!\times \!1000$ 个格子，每个格子的坐标是它的左下角的坐标，再建立一个数组，保存每个方格被多少个矩形覆盖，比如样例是这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/ungo9id1.png)

每个格子被覆盖的次数用格子颜色的深浅直观地表现了出来。

只要数一数有多少个格子刚好被 $k$ 个矩形覆盖，就能求出答案。
## 2.较慢的方法
怎么求出每个格子被多少矩形覆盖了呢？最基本的思路是对每个矩形，将它覆盖的格子全都加上1。这种方法最坏情况复杂度是 $O(x2y2n)$，大约需要 $10^{11}$ 次操作，显然会超时。代码就不贴了。
## 3.一维差分前缀和
如果变成一维数组区间加，应该就能想到办法：~~线段树~~ 差分+前缀和。（会的同学可直接跳至“5.二维差分前缀和”）

比如下面这张图，黑色和红色组成的柱子表示原数组，其中红色部分就是它的差分数组：

![](https://cdn.luogu.com.cn/upload/image_hosting/zb0rmmo5.png)

用公式表示就是：（差分简称 $c$，前缀和简称 $q$）

$$c_1=a_1$$

$$c_{i}=a_{i}-a_{i-1}(i>1)$$

$$q_{1}=a_1$$

$$q_{i}=\sum_{k=1}^{i} a_{k}=q_{i-1}+a_{i}(i>1)$$

显然，差分与前缀和互为逆运算。
## 4.一维区间加
比如我们知道了一个数组 $a$ 的差分数组 $b$，怎么才能快速地操作数组 $b$，使数组 $a$ 的区间 $[x,y]$ 加上 $v$ 呢？

我们可以先区间加，再差分，找到规律。比如第二行是第一行的差分数组，第三行是将第一行第3-5项都加上v，第四行是第三行的差分。

$$[a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8]$$
$$[a_1,a_2-a_1,a_3-a_2,a_4-a_3,a_5-a_4,a_6-a_5,a_7-a_6,a_8-a_7]$$
$$[a_1,a_2,a_3+v,a_4+v,a_5+v,a_6,a_7,a_8]$$
$$[a_1,a_2-a_1,a_3-a_2+v,a_4-a_3,a_5-a_4,a_6-a_5-v,a_7-a_6,a_8-a_7]$$
可以看到，第四行与第二行的区别只在第3个数和第6个数，于是能得到这样的算法：

```cpp
c[left]+=v;
c[right+1]-=v;
```

所以需要进行大量的区间加时，可以先进行差分，$O(1)$ 的区间加，再前缀和回来。
## 5.二维差分前缀和
二维前缀和也很好定义。

$$q_{i,j}=\sum_{k=1}^i\sum_{l=1}^j a_{k,l}$$

但是差分显得不很直观，所以需要用差分是前缀和的逆运算的特点推。

![](https://cdn.luogu.com.cn/upload/image_hosting/1s4e3ka8.png)

$$\because \text{红}+\text{橙}+\text{黄}+\text{灰}=(\text{红}+\text{橙})+(\text{橙}+\text{黄})-\text{橙}+\text{灰}$$

$$\text{即}q_{i,j}=q_{i-1,j}+q_{i,j-1}-q_{i-1,j-1}+a_{i,j}$$

$$\therefore a_{i,j}=q_{i,j}+q_{i-1,j-1}-q_{i,j-1}-q_{i-1,j}$$

$$\therefore c_{i,j}=a_{i,j}+a_{i-1,j-1}-a_{i,j-1}-a_{i-1,j}\text{（此处用到了差分和前缀和互为逆运算的特点）}$$

由第三个式子顺便得到前缀和的递推式：

$$q_{i,j}=q_{i,j-1}+q_{i-1,j}-q_{i-1,j-1}+a_{i,j}$$
## 6.二维区间加
二维区间加我们仍然按照上面的方法推，但是用字母太麻烦，所以下面用数字。一下四个矩阵意义仍与上同，第三个的红色部分为 $[(1,1),(2,2)]$ 加上5的部分，第四个的红色部分为与第二个不同的数。

$$\begin{bmatrix}8&9&10&5&7\\5&4&9&4&5\\6&3&3&3&3\\9&8&8&5&4\\5&10&4&3&2\end{bmatrix}$$

$$\begin{bmatrix}3&2&-4&0&1\\-1&2&5&-5&1\\-3&-2&0&3&1\\4&-6&6&-2&0\\5&5&-6&-1&-1\end{bmatrix}$$

$$\begin{bmatrix}8&9&10&5&7\\5&4&9&4&5\\6&\color{red}8&\color{red}8&3&3\\9&\color{red}13&\color{red}13&5&4\\5&10&4&3&2\end{bmatrix}$$

$$\begin{bmatrix}3&2&-4&0&1\\-1&\color{red}-3&5&\color{red}0&1\\-3&-2&0&3&1\\4&\color{red}-1&6&\color{red}-7&0\\5&5&-6&-1&-1\end{bmatrix}$$

可以看到，上面矩阵的-1和0是由1-和-5加5得到的，-3和-7是由2和-2减5得到的，所以可以得到如下算法：（$x_1,x_2,y_1,y_2$ 意义如题）

```cpp
c[x1][y1]+=v;
c[x2][y2]+=v;
c[x1][y2]-=v;
c[x2][y2]-=v;
```
## 7.最终做法
建立一个差分数组，一个原数组，读入每个矩形，用上述方法对差分数组操作实现区间加1。最后将差分数组进行前缀和得到原数组，统计 $k$ 的个数，得到答案。
# 三、代码
```cpp
#include<iostream>
using namespace std;
int n,k,ans,c[1010][1010],a[1010][1010];
//n,k意义如题，ans是答案，c是差分数组，a是原数组
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		c[x1][y1]++;//二维差分区间加
		c[x2][y2]++;//
		c[x1][y2]--;//
		c[x2][y1]--;//
	}
	for(int i=0;i<=1005;i++)
		for(int j=0;j<=1005;j++)
		{
			a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+c[i][j];//前缀和的递推式
			if(a[i][j]==k)ans++;//恰被覆盖k次，统计
		}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hater (赞：11)

啊 题目真的不错 

二维差分一眼就看出来了

之后窝就尴尬了 ~~只会一维~~

在苦思冥想了20分钟后 

发现数据并不强 于是思路来了

一维差分 一维暴力 

不论在理论上 还是在实际上都不会超时

代码简短友好 

```cpp
#include <bits/stdc++.h>
#define SIZE 1055
#define R register
using namespace std ;
int n , a[SIZE][SIZE] , k ,  ans = 0 ;
int main() 
{
	int x1 , y1 ,x2, y2 ;
	cin >> n >> k  ;
	for(R int i=1; i<=n; i++) 
	{
		cin >> x1 >> y1 >> x2 >> y2 ;
		for(R int j=x1; j<x2; j++)
			a[j][y1]++ , a[j][y2]-- ;
    }
	for(R int i=0; i<SIZE-50 ; i++)
	{
		R int t = 0 ;
		for(R int j=0; j<SIZE-50; j++)
		{
			t += a[i][j] ;
			if( t == k ) ans++ ;
		}
	}
	cout << ans << endl; 
	return 0 ; 
}
```

实测900ms多

---

## 作者：ReZHUI (赞：10)

## 正解：二维差分

~~（写题解是因为写题时忘了二维差分怎么写，现在复习下）~~



 _对于一维差分，实现[a,b]区间加上val_ 
 
c[a]+=val;

//从c[a]开始，往后的每一个数都+val

c[b+1]-=val;

//相当于在c[b+1]处终止了+val的操作



------------


拓展到二维差分

 _实现矩形（左上角（x1,y1) ,右下角(x2,y2))内加上val;_ 

c[x1][y1]+=val;  //  开始+val的操作

c[x1+1][y2]-=val; // 在该行终止

c[x1][y2+1]-=val; // 在该列终止


(要注意的是：对于c[x2+1][y2+1]这个，被终止了两次，即多减了一个val，所以要补回来)

c[x2+1][y2+1]+=val;



------------

差分和前缀和是互逆操作，还原成原数组，维护个前缀和就好了

------------
### 注意点：

 1、题目给的是二维坐标系的左下角和右上角，实际上就是我们平常使用差分或前缀和时，用行列表示的左上角和右下角（相当于把坐标系转一下）,所以直接拿来用就好了，不需要进行转化
 

2、题目告知的是点的坐标，而差分和前缀和都是在格子上实现的，所以要把点转化成格子,即左上角的点横坐标和纵坐标都+1（不会的话可以画个图模拟下）

------------
下面贴代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,k,a,b,x,y,ans;
int f[N][N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a>>b>>x>>y;
		a++;b++;
		f[a][b]++;
		f[a][y+1]--;
		f[x+1][b]--;
		f[x+1][y+1]++;
	}
	for(int i=1;i<=1000;i++)
		for(int j=1;j<=1000;j++){
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
			if(f[i][j]==k)ans++;
		}
	cout<<ans;	
	return 0;
}
```
~~逃了~~~


---

## 作者：小柯 (赞：8)

这篇题解适用于~~不懂二维拆分的OIers.~~

# 思路

如果你不记得一些小学学的的东西，那我来给你回忆一下：

>点动成线；线动成面；面动成体
![](http://img.mp.itc.cn/upload/20170314/dd1bf37ea69b40aa85faa4aba30d11f6_th.gif)

既然我们要利用前缀和将几个点刷成一个面，那么就可以先将点刷成一条线，再利用这些线刷成一个面。

$(red:+1;blue:-1;yellow:+2)$

![](https://cdn.luogu.com.cn/upload/image_hosting/a82wztpf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

横着扫一遍前缀和

![](https://cdn.luogu.com.cn/upload/image_hosting/i8akfd01.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

竖着扫一遍前缀和

![](https://cdn.luogu.com.cn/upload/image_hosting/j6isks4f.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

成功刷上！

# 代码

```cpp
#include<iostream>
using namespace std;
int n,k;
int a[1005][1005];
int x1,y1,x2,y2;
int ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>x1>>y1>>x2>>y2;
		x1++,y1++,x2++,y2++;
		a[x1][y1]++;
		a[x1][y2]--;
		a[x2][y1]--;
		a[x2][y2]++;
	}
	for(int i=1;i<=1001;i++)for(int j=1;j<=1001;j++)a[i][j]+=a[i][j-1];
	for(int i=1;i<=1001;i++)for(int j=1;j<=1001;j++)a[i][j]+=a[i-1][j];
	for(int i=1;i<=1001;i++)for(int j=1;j<=1001;j++)ans+=(a[i][j]==k);
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：ziiidan (赞：5)

这道题几乎是二维差分的模板题。

这道题的坑点：

1.从 0 开始编号

2.所给的矩形为点，而询问的是面积

**本人所认为二维差分的实质：
打正标记和负标记，用前缀和的方式消标记以保证标记的有效区间**

在这道题中，还有如下的处理小技巧：

我们让左上角的点的横纵坐标都加 1 ，这样的话，我们就从给点打标记直接变成了对1 * 1 的小方格打标记，统计的时候更加方便，其次我们在求差分数组的前缀和来求出实际数组的时候，不会出现负下标，处理的时候更加方便，一举两得。

代码如下：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

const int maxn = 1005;

int n, k, ans;
int fx, tx, fy, ty;
int a[maxn][maxn], sum[maxn][maxn];

inline int read(void)
{
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') w = -1;
	for(; ch <= '9' && ch >= '0'; ch = getchar()) s = s * 10 + ch - '0';
	return s * w;
}

int main()
{
	n = read(); k = read();
	for(register int i = 1; i <= n; i++)
	{
		fx = read() + 1; fy = read() + 1; tx = read(); ty = read();
		a[fx][fy]++;
		a[tx + 1][ty + 1]++;
		a[fx][ty + 1]--;
		a[tx + 1][fy]--;
	}
	for(register int i = 1; i <= 1001; i++)
	{
		for(register int j = 1; j <= 1001; j++)
		{
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
			if(sum[i][j] == k) ans++;
		}
	}
	cout << ans << '\n';
	return 0;
}
```

对本题有什么疑问的话直接在讨论区发或者洛谷私信都可以，本人看到后会及时回复。

谢谢阅读。


---

## 作者：一只书虫仔 (赞：3)

二维区间覆盖板子。

#### Description

> 给定 $n$ 个矩阵，求被覆盖 $k$ 层的格子有多少个。

#### Solution

我们都知道区间覆盖怎么做，用差分。对于区间 $[l,r]$，在 $l$ 打标记，在 $r+1$ 撤标记，然后卷一下序列即可。

那对于二维，如果矩阵用 $(x_1,y_1)$ 到 $(x_2,y_2)$（左下到右上）描述的话，那么可以在 $(x_1+1,y_1+1)$ 打标记，在 $(x_2+1,y_1+1)$ 和 $(x_1+1,y_2+1)$ 撤标记，但你会发现，在 $(x_2+1,y_2+1)$ 和后面会撤两次，所以在 $(x_2+1,y_2+1)$ 再打一次就可以了。

然后卷一下矩阵（二维前缀和）即可。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[1005][1005];
int sum[1005][1005];

int main () {
	int n, k;
	int xmax = 0, ymax = 0;
	scanf("%d%d", &n, &k);
	while (n--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1++, y1++, x2++, y2++;
		a[x1][y1]++;
		a[x2][y1]--;
		a[x1][y2]--;
		a[x2][y2]++;
		xmax = max(xmax, max(x1 - 1, x2 - 1));
		ymax = max(ymax, max(y1 - 1, y2 - 1));
	}
	for (int i = 0; i <= xmax; i++)
		for (int j = 0; j <= ymax; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	int cnt = 0;
	for (int i = 0; i <= xmax; i++)
		for (int j = 0; j <= ymax; j++)
			if (sum[i][j] == k)
				cnt++;
	printf("%d\n", cnt);
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：3)

前置知识：[差分](http://baidu.physton.com/?q=%E5%B7%AE%E5%88%86)和[前缀和](http://baidu.physton.com/?q=%E5%89%8D%E7%BC%80%E5%92%8C)。众所周知，差分和前缀和互为逆运算

读题可知，正解是二维差分，最后前缀和扫一遍

然而窝钛蒻了，不会二维差分，就开了$\huge\texttt{一千个一维差分}$

要是有极限数据，应该能正好卡过pwp

然鹅没有qwq

```cpp
#include<stdio.h>
inline void read(int&x)//快读
{
	x=0;register char c=getchar();for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());
}
int n,k,a[1003][1003],b[1003][1003],ans;
main()
{
	read(n);read(k);//输入
	for(register int w,x,y,z;n--;)
	{
		read(w);read(x);read(y);read(z);//输入
		++w;++x;++y;++z;//全部+1，防止后面前缀和的时候访问负下标
		for(register int i=w;i<y;++i)++a[i][x],--a[i][z];
	}
	for(register int i=1;i<1002;++i)for(register int j=1;j<1002;++j)
	{
		b[i][j]=b[i][j-1]+a[i][j];//前缀和
		if(b[i][j]==k)++ans;//统计答案
	}
	printf("%d",ans);//输出
}/**/
```

---

## 作者：Saliеri (赞：2)

### 直接进入正题吧
___

直接观察有此题是一道**极其典型的二维题**

那么

暴力 **二维差分&前缀和** 走起
___

首先，每读进一个矩形，用差分思想
```cpp
++sum[a+1][b+1],++sum[c+1][d+1],--sum[a+1][d+1],--sum[c+1][b+1];
```

注：加 1 是因为下文需要前缀和递推，防止数组出现负数下标

又因为

差分与前缀和是作用于 序列* 上的一组互逆运算

所以

差分的前缀和就是原序列

$\Theta(10^6)$搞一搞就好了

___

#### code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,ans,sum[1005][1005];
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1,a,b,c,d;i<=n;++i)scanf("%d %d %d %d",&a,&b,&c,&d),++sum[a+1][b+1],++sum[c+1][d+1],--sum[a+1][d+1],--sum[c+1][b+1];
	for(int i=1;i<=1000;++i)
		for(int j=1;j<=1000;++j)
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1],sum[i][j]==k?++ans:ans += 0;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

在二维中加矩形，自然可以使用二维差分。

如果输入b,c,d,e
则
```
   	        a[d][e]++;
		a[b-1][c-1]++;
		a[d][c-1]--;
		a[b-1][e]--;
```
## 注意：给出的是点坐标，应该d--,e--因为有0可以不这样做，改为b++,c++.
代码如下：
```c
#include<bits/stdc++.h>
using namespace std;
int n,a[1002][1002],m,b,c,d,e,ans,p,q;
inline int read(){
	int t=0;
	char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+v-'0';
		v=getchar();
	}
	return t;
}
int main(){
	n=read();m=read();
	for(register int i=1;i<=n;++i){
		b=read();
		c=read();
		d=read();
		e=read();
		b++;
		c++;
		a[d][e]++;
		a[b-1][c-1]++;
		a[d][c-1]--;
		a[b-1][e]--;
		p=max(p,d);
		q=max(q,e);	
	}//cout<<a[p][q]<<endl;
	for(register int i=p;i>=1;--i){
		for(register int j=q;j>=1;--j){
			if(a[i][j]==m)ans++;
			a[i-1][j]+=a[i][j];
			a[i][j-1]+=a[i][j];
			a[i-1][j-1]-=a[i][j];
		}
	}
	/*for(register int i=1;i<=p;++i){
		for(register int j=1;j<=q;++j){
			cout<<a[i][j]<<" ";
		}cout<<endl;
	}*/
	printf("%d",ans);
} 

```


---

## 作者：VioletIsMyLove (赞：1)

笨蛋的方法就是模拟呗，每次都涂上，最后扫一趟就好了，但是这效率最慢是 $n*1000000$,明显是超时滴。
但我们看，每次是涂一个方块，整个方块内颜色都会 $+1$，那就果断造前缀和然后二维容斥啊，对与 $x1,y1,x2,y2$,我们把造前缀和的二维数组 $F[x1][y1]+1,F[x2][y1]-1,F[x1][y2]-1,F[x2][y2]+1;$
咦？为什么是x2,y2而不是x2+1,y2+1呢？因为题目给的是点而不是边，x个点中间只有 $x-1$ 条边，所以x2其实就是x2-1+1。
最后造前缀和 $F[i][j]+=F[i-1][j]+F[i][j-1]-F[i-1][j-1];$
只要 $F[i][j]==k$ ,那 $ans$ 就 $++$，最后输出结果就完了。
但是，数据给的范围是 $0-1000$，也就是说当 $x=0$ 或 $y=0$ 的时候,$i,j$ 也是从 $0$ 开始跑的，那么 $i-1,j-1$ 就小于 $0$ 了，F数组就会越界，那么该怎么处理呢？
在读数据的时候把给的坐标都+1就完了，最后造前缀和刷答案的时候从 $1-1001$ 就ok了。

Code:
```cpp
#include<bits/stdc++.h>
#define maxh 1005
using namespace std;
int N,K,Ans,F[maxh][maxh];
int read(){
	int ret=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
    N=read(),K=read();
    while (N--){
    	int a=read()+1,b=read()+1,c=read()+1,d=read()+1;
    	F[a][b]++,F[a][d]--,F[c][b]--,F[c][d]++;
    }
    for (int i=1;i<=1001;i++)
    for (int j=1;j<=1001;j++){
    	F[i][j]+=F[i-1][j]+F[i][j-1]-F[i-1][j-1];
    	Ans+=F[i][j]==K;
    }
    printf("%d\n",Ans);
    return 0;
}
```


---

