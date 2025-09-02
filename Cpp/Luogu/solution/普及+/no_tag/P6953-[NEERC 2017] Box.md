# [NEERC 2017] Box

## 题目描述

Bella 在一家生产盒子的工厂工作。所有盒子都是长方体形状。对应长方体的展开图是从一个大小为 $w \times h$ 的平面矩形纸板上裁剪出来的。这个展开图是一个多边形，其边与纸板矩形的边平行。展开图沿着几条线折叠，并沿着最终长方体的边缘连接形成一个盒子。展开图仅沿着最终盒子的边缘折叠。

![](https://cdn.luogu.com.cn/upload/image_hosting/oxlybr7q.png)

第一组样例

![](https://cdn.luogu.com.cn/upload/image_hosting/vk9knsg7.png)


第三组样例

Bella 是一名软件开发人员，她的任务是检查是否可以用一个大小为 $w \times h$ 的纸板制作一个大小为 $a \times b \times c$ 的盒子。Bella 编写了一个程序，盒子正在生产。你能做到吗？

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1 2 3
6 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 2 3
5 5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1 1 1
10 2
```

### 输出

```
Yes
```

# 题解

## 作者：Avocadooo (赞：5)

# 正经教学
## 1.题目类型判断

给定一个长方体长宽高。

又给出一个平面。

问能否在平面上裁出该长方体展开图。（亲测，这道题是不需要考虑斜着的情况的 ~~，真是良心好题~~ ）

很明显，这是一道**平面几何**类型的题目。

## 2.基本思路

既然已经判断出了题目类型，那么这道题的方法就很简单了——画图，分析。

### 情况1：1-4-1型

如图，看是否满足 $ 2 \times a+2 \times b \leq x $ 且 $ 2 \times b+c \leq y $ 即可。

![](https://z3.ax1x.com/2021/09/28/4f6VKI.png)

![](https://z3.ax1x.com/2021/09/28/4fc0Tf.png)

![](https://z3.ax1x.com/2021/09/28/4fcrtS.png)

### 情况2：3-3型

如图，看是否满足 $ 3 \times c+a+b \leq x $ 且 $ a+b \leq y $ 即可。

![](https://z3.ax1x.com/2021/09/29/44e6s0.png)

### 情况3：2-2-2型

如图，看是否满足 $ 2 \times a+b+c \leq x $ 且 $ a+b+c \leq y $ 即可。
![](https://z3.ax1x.com/2021/09/29/44mFw8.png)

以上呢，就是总结出的三种长方体的展开图，我们也**可以通过交换 $ a,b,c $ 的值来放置，同样可以将纸张旋转**（即交换 $ x,y $ 的值）。那么我们只需要将 $ a,b,c $ 存入一个数组，用系统函数帮我们进行**全排列**，就可以得出正确的答案了。

## 3.std代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int a[4];
int x,y;
bool test()
{
	for(int i=1;i<=6;i++)
	{
		for(int i=1;i<=2;i++)
		{ 
			if(2*a[1]+2*a[2]<=x&&2*a[2]+a[3]<=y) return true;//情况1
			if(3*a[3]+a[1]+a[2]<=x&&a[1]+a[2]<=y) return true;//情况2
			if(2*a[1]+a[2]+a[3]<=x&&a[1]+a[2]+a[3]<=y) return true;//情况3
			swap(x,y);//旋转纸张 
		}
		next_permutation(a+1,a+4);
	}
	return false;
}
int main()
{
	scanf("%d %d %d",&a[1],&a[2],&a[3]);
	scanf("%d %d",&x,&y);
	bool flag=test();
	if(flag) printf("Yes");
	else printf("No");
}
```

---

## 作者：Harry27182 (赞：5)

思路是枚举哪个分别是长，宽，高，也就是枚举3的全排列。然后对于每一种情况，判断可不可以放在$w*h$的长方形。那么关键就是长方形的展开图所占矩形面积有哪几种。本蒟蒻通过半个小时的画图，发现展开图的长和宽只有以下五种：

$1$:长：$3a+b+c$,宽：$b+c$.

$2$:长：$2a+2b$ ,宽：$2a+c$.

$3$:长：$2a+2b$ ,宽：$2b+c$.

$4$:长：$2a+2b$ ,宽：$a+b+c$.

$5$:长：$a+b+2c$,宽：$a+b+c$.

特别注意:
这里的$a,b,c$并不是输入的$a,b,c$,而是经过重新排列后的$a,b,c$.

所以，我们就对每种排列，去枚举每种展开图，就可以完美的$ac$了！

最后，献上蒟蒻的巨丑代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],ww,hh;
bool pd(int u,int v,int w)//枚举每种展开图 
{
	if(3*u+v+w<=ww&&w+v<=hh)return true;//如果满足这种情况，就返回真 
	if(2*w+v+u<=ww&&u+v+w<=hh)return true;//同上 
	if((2*u+2*v<=ww&&2*u+w<=hh)||(2*u+2*v<=hh&&2*u+w<=ww))return true;//同上
	if((2*u+2*v<=ww&&2*v+w<=hh)||(2*u+2*v<=hh&&2*v+w<=ww))return true;//同上
	if((2*u+2*v<=ww&&u+v+w<=hh)||(2*u+2*v<=hh&&u+v+w<=ww))return true;//同上
	return false;//否则返回假 
}
int main()
{
	cin>>a[1]>>a[2]>>a[3];
	cin>>ww>>hh;
	if(ww<hh) //把较大的放到前面，能省去一些枚举 
	{
		int k=ww;
		ww=hh;
		hh=k;
	}
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			if(i==j)continue;//如果有一个边长被选了两次，就退出本层循环 
			for(int k=1;k<=3;k++)
			{
				if(i==k||j==k)continue;//同上 
				if(pd(a[i],a[j],a[k]))//如果为真，输出"Yes" 
				{
					cout<<"Yes";
					return 0;
				}
			}
		}
	}
	cout<<"No";//否则输出"No" 
	return 0;
} 
```



---

## 作者：Iam1789 (赞：5)

这道题很明显，是一道小小的结论题qwq。

------------
这道题并不用上面那位老哥一样那么复杂。
首先，我们将$a,b,c$和$w,h$进行排序，使短的边对上长方形较短的一段，而不是长的一部分对上较短的一段，可以省去很多枚举。

我们借用一下这位老哥的图来看一看：![](https://cdn.luogu.com.cn/upload/image_hosting/y1bi8ot4.png)

实际上，我们不必枚举每种展开图情况，展开图的所需要的长度和宽度如下所示：
1. 如第一张展开图所示它所需要的长度为$3\timesa+b+a$，宽度为$b+a$，如果这种情况，可能会出现宽度够了但长度不够的情况，因此需要将a,b,c代入三次判断，得到如下判断：
2. 如第2、3、4、5、7、9张展开图所示，它所需要的长度为$ 2\times a+2\times b $，宽度为$b+2\times c$。自然，我们不会让最长的b,c成为a和b，这样在上面就判出来了。可以得到如下判断。
3. 如剩下的图所示，长度为$2\times a+b+c$，宽度为$a+b+c$，宽度是固定的，所以我们自然想让长更短，所以不可能让较大的两个数来当乘2的那个数，所以让最短的那个乘2进行判断。

完整代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c,w,h;
int main()
{
	scanf("%d%d%d%d%d",&a,&b,&c,&w,&h);
	if(w>h)
	swap(w,h);	
	if(a>b)
	swap(a,b);
	if(b>c)
	swap(b,c);
	if(a>b)
	swap(a,b);//排序
	if((a+b<=w&&3*c+b+a<=h)||(a+c<=w&&3*b+c+a<=h)||(b+c<=w&&3*a+b+c<=h))    
	cout<<"Yes";
	else if((a*2+b*2<=h&&c+a*2<=w)||(a*2+c*2<=h&&b+a*2<=w))
	cout<<"Yes";
	else if(a+b+c<=w&&2*a+b+c<=h)
	cout<<"Yes";
	else
	cout<<"No";
	return 0;
}
```
~~谢谢朋友们~~


---

## 作者：Loser_Syx (赞：2)

手玩样例，发现满足条件的展开图仅可能是：

![](https://cdn.luogu.com.cn/upload/image_hosting/154nmsxw.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/6z68g38c.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/9hsylcl7.png)

（上图中 $a,b,c$ 自定）

然后对于每一种情况，进行一个判断，其中具体的长宽高使用全排列枚举所有的情况。

然后发现 $w,h$ 对答案也会有影响，所以 $w,h$ 的位置也要枚举一下。

```cpp
signed main() {
	int a[4];
	int w, h;
	read(a[1], a[2], a[3], w, h);
	sort(a + 1, a + 4);
	do {
		for (int i = 2; i; --i, swap(w, h)) {
			if (a[1] * 2 + a[2] * 2 <= w && a[1] * 2 + a[3] <= h) return puts("Yes"), 0;
			if (a[1] * 3 + a[2] + a[3] <= w && a[2] + a[3] <= h) return puts("Yes"), 0;
			if (a[1] * 2 + a[2] + a[3] <= w && a[1] + a[2] + a[3] <= h) return puts("Yes"), 0;
		}
	} while (next_permutation(a + 1, a + 4));
	puts("No");
	return 0;
}
```

---

## 作者：Hope2075 (赞：2)

# 题意

给出一个长方体的长、宽、高（分别是$a,b,c$），问：能否在一张长为$w$，宽为$h$的纸上裁出这个长方体的任何一个侧面展开图。

# 题解

很显然的思路就是枚举可能的展开图，关键是如何枚举。

首先思考一下正方体的展开图（如下图，一共是11种）。

![](https://cdn.luogu.com.cn/upload/image_hosting/y1bi8ot4.png)

可以想到，长方体展开图和正方体的区别就是边的长度不同（图中不同颜色就表示不同长度的边）。

所以枚举边的排列，再枚举展开图的种类即可。

另外可以注意到展开图占据的矩形区域一共只有5种情况，只考虑这5种情况即可。

# 代码

我先列出了所有排列，然后定义一个结构体来求值。

个人感觉难度是橙或黄，算法标签可以贴模拟或者枚举。

```cpp
#include<cstdio>
int a[3],w,h;
int o[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
struct p{
    int a1,a2,b1,b2,c1,c2;
    p(){}
    p(int _a1,int _b1,int _c1,int _a2,int _b2,int _c2){a1=_a1;b1=_b1;c1=_c1;a2=_a2;b2=_b2;c2=_c2;}
    void cal(int a,int b,int c,int &wx,int &hx){
        wx=a*a1+b*b1+c*c1;
        hx=a*a2+b*b2+c*c2;
    }
};
p list[5]={
    p(3,1,1,0,1,1),
    p(0,2,2,1,1,1),
    p(0,2,2,1,2,0),
    p(1,2,1,1,0,2),
    p(1,2,1,1,1,1)
};
int main(){
    scanf("%d%d%d%d%d",a,a+1,a+2,&w,&h);
    for(int i=0;i<6;i++){
        for(int j=0;j<5;j++){
            int wx,hx;
            list[j].cal(a[o[i][0]],a[o[i][1]],a[o[i][2]],wx,hx);
            if(w>=wx && h>=hx){
                printf("Yes\n");
                return 0;
            }
            if(w>=hx && h>=wx){
                printf("Yes\n");
                return 0;
            }
        }
    }
    printf("No\n");
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

## 题目描述

[[NEERC2017] Box](https://www.luogu.com.cn/problem/P6953)

## 算法思路

可以将长方形的侧面展开图分为以下几种：

- 第一行有一个，第二行有四个，第三行有一个。只要判断 $a \times 2 + b \times 2 \le w$ 并且 $b \times 2 + c \le h$ 就行了。长方形侧面展开图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5068qnb8.png)

- 第一行有三个，第二行有三个。只要判断 $a + b + c \times 3 \le w$ 并且 $a + b \le h$ 就行了。长方形侧面展开图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/rniba4an.png)

- 第一行有二个，第二行有二个，第三行有二个。只要判断 $a \times 2 + b + c \le w$ 并且 $a + b + c \le h$ 就行了。长方形侧面展开图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/tyxygjdb.png)

最后只要判断一下这些方案成不成立就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=10;
ll a[N],w,h;//a[1]表示a，a[2]表示b，a[3]表示c 
bool flag;//flag表示可不可以 
void solve()
{
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=2;j++)
		{
			if(a[1]*2+a[2]*2<=w&&a[2]*2+a[3]<=h)//如果符合第一种情况 
			{
				flag=true;//可以 
				return;
			}
			if(a[1]+a[2]+a[3]*3<=w&&a[1]+a[2]<=h)//如果符合第二种情况 
			{
				flag=true;//可以 
				return;
			}
			if(a[1]*2+a[2]+a[3]<=w&&a[1]+a[2]+a[3]<=h)//如果符合第三种情况 
			{
				flag=true;//可以 
				return;
			}
			swap(w,h);//翻转 
		}
		next_permutation(a+1,a+4);
	}
	flag=false;//不可以 
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>a[1]>>a[2]>>a[3];
	cin>>w>>h;
	solve();
	if(flag)//可以 
	{
		cout<<"Yes\n";//输出Yes 
	}
	else//不可以 
	{
		cout<<"No\n";//输出No 
	}
	return 0;
}
```

---

## 作者：Iratis (赞：1)

**极水绿题**

# 题目简介
给出一个长方体的长、宽和高，以及一张纸片的长和宽，求长方体的展开图能否在此纸片中放下。
# 题目分析
我们知道，长方体的展开图有三种情况，如图：

第一种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/84vbltwc.png)

显然只需要判断 $ a \times 2+c \leq x $ 且 $ a \times 2+b \times 2 \leq y $ 是否成立即可。

第二种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/ft8smwfa.png)

显然只需要判断 $ a \times 2+b+c \leq x $ 且 $ a+b+c \leq y $ 是否成立即可。

第三种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/bhhymm7t.png)

显然只需要判断 $ a \times 3+b \times 2 \leq x $ 且 $ c \times 2 \leq y $ 是否成立即可。

所以最后只需要再加上转纸片和展开图的情况，就完成了。

代码如下：
```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int p[4];
int x,y;
bool check(int a,int b,int c,int x,int y)
{
	if(2*a+2*b<=x&&2*b+c<=y)return true;
	if(a+b+3*c<=x&&a+b<=y)return true;
	if(2*a+b+c<=x&&a+b+c<=y)return true;
	return false;
}
int main()
{
	cin>>p[1]>>p[2]>>p[3];
	cin>>x>>y;
	bool ans=false;
	for(int i=1;i<=6;i++)
	{
		if((check(p[1],p[2],p[3],x,y)==true)||(check(p[1],p[2],p[3],y,x)==true))
		{
			flag=true;
			break;
		}
		next_permutation(p+1,p+4);
	}
	if(flag==true)cout<<"Yes";
	else cout<<"No";
	return 0;
}
```


---

## 作者：niuzh (赞：0)

### 思路

可将长方形的展开图按照 **长 $\times$ 宽** 分为以下几类：

![](https://cdn.luogu.com.cn/upload/image_hosting/l1k7th2v.png)

长为 $a \times 2 + c \times 2$，宽为 $b + c \times 2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwqh08sc.png)

长为 $a + b$，宽为 $a+b+c \times 3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/rf5or4se.png)

长为 $a + b + c$，宽为 $a \times 2 + b + c$。

然后只用分别枚举每个是 $a$，每个是 $b$，每个是 $c$，在判断即可。

### 代码

```cpp
/*
 * @FilePath: test.cpp
 * @Author: niu-zh
 */
#include<bits/stdc++.h>
using namespace std;
int a[4];
int main()
{
	int x,y;
	cin>>a[1]>>a[2]>>a[3]>>x>>y;
	sort(a+1,a+4);
	do
	{
		for (int i=1; i<=2; i++)
		{
			if (2*a[1]+2*a[2]<=x&&2*a[2]+a[3]<=y)
			{
				cout<<"Yes";
				return 0;
			}
			if (3*a[3]+a[1]+a[2]<=x&&a[1]+a[2]<=y)
			{
				cout<<"Yes";
				return 0;
			}
			if (2*a[1]+a[2]+a[3]<=x&&a[1]+a[2]+a[3]<=y)
			{
				cout<<"Yes";
				return 0;
			}
			swap(x,y);
		}
	}
	while (next_permutation(a+1,a+4));
	cout<<"No";
	return 0;
}
```

---

## 作者：TYxxj (赞：0)

**题意：**

给出一个长方体或者立方体的三边长和一张纸的长和宽，问能不能通过裁剪这张纸，组成一个想要的长方体。

**题解：**

给出的11种组成的方式中，长和宽只有三种情况，34，43，52,

通过把这三种方式画出来可以得到三种方式的长和宽分别为：

$2a+b，2a+2c$

$a+b+c，2a+b+c$

$3a+b+c，b+c$

所以暴力这三条边，找是否比纸张的长和宽小就可以了。

代码：
```cpp
#include<iostream>
using namespace std;
#define ll long long
const int mod=1e9+7;
const int M=1e5 + 10;
int check(ll a,ll b,ll c,ll w,ll h) {
	if(3*a+b+c <= w && b+c <= h || 3*a+b+c <= h && b+c <= w)return 1;
	if(2*a+b <= w && 2*a+2*c <=h || 2*a+b <=h && 2*a+2*c <= w)return 1;
	if(a+b+c <= w && 2*a+b+c <=h || a+b+c <=h && 2*a+b+c <= w)return 1;
	return 0;
}
int main() {
	ll a,b,c,n,m;
	while(cin>>a>>b>>c>>n>>m) {
		if(a==b&&b==c) {
			if(m>=a*3&&n>=a*4||m>=a*4&&n>=a*3||m>=a*2&&n>=a*5||m>=a*5&&n>=2*a)cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		} else {
			if(check(a,b,c,n,m)|| check(a,c,b,n,m) || check(b,a,c,n,m) || check(b,c,a,n,m) || check(c,a,b,n,m) || check(c,b,a,n,m))cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
}
```

---

