# Distance

## 题目描述

Let's denote the Manhattan distance between two points $ p_1 $ (with coordinates $ (x_1, y_1) $ ) and $ p_2 $ (with coordinates $ (x_2, y_2) $ ) as $ d(p_1, p_2) = |x_1 - x_2| + |y_1 - y_2| $ . For example, the distance between two points with coordinates $ (1, 3) $ and $ (4, 2) $ is $ |1 - 4| + |3 - 2| = 4 $ .

You are given two points, $ A $ and $ B $ . The point $ A $ has coordinates $ (0, 0) $ , the point $ B $ has coordinates $ (x, y) $ .

Your goal is to find a point $ C $ such that:

- both coordinates of $ C $ are non-negative integers;
- $ d(A, C) = \dfrac{d(A, B)}{2} $ (without any rounding);
- $ d(B, C) = \dfrac{d(A, B)}{2} $ (without any rounding).

Find any point $ C $ that meets these constraints, or report that no such point exists.

## 说明/提示

Explanations for some of the test cases from the example:

- In the first test case, the point $ B $ has coordinates $ (49, 3) $ . If the point $ C $ has coordinates $ (23, 3) $ , then the distance from $ A $ to $ B $ is $ |49 - 0| + |3 - 0| = 52 $ , the distance from $ A $ to $ C $ is $ |23 - 0| + |3 - 0| = 26 $ , and the distance from $ B $ to $ C $ is $ |23 - 49| + |3 - 3| = 26 $ .
- In the second test case, the point $ B $ has coordinates $ (2, 50) $ . If the point $ C $ has coordinates $ (1, 25) $ , then the distance from $ A $ to $ B $ is $ |2 - 0| + |50 - 0| = 52 $ , the distance from $ A $ to $ C $ is $ |1 - 0| + |25 - 0| = 26 $ , and the distance from $ B $ to $ C $ is $ |1 - 2| + |25 - 50| = 26 $ .
- In the third and the fourth test cases, it can be shown that no point with integer coordinates meets the constraints.
- In the fifth test case, the point $ B $ has coordinates $ (42, 0) $ . If the point $ C $ has coordinates $ (21, 0) $ , then the distance from $ A $ to $ B $ is $ |42 - 0| + |0 - 0| = 42 $ , the distance from $ A $ to $ C $ is $ |21 - 0| + |0 - 0| = 21 $ , and the distance from $ B $ to $ C $ is $ |21 - 42| + |0 - 0| = 21 $ .

## 样例 #1

### 输入

```
10
49 3
2 50
13 0
0 41
42 0
0 36
13 37
42 16
42 13
0 0```

### 输出

```
23 3
1 25
-1 -1
-1 -1
21 0
0 18
13 12
25 4
-1 -1
0 0```

# 题解

## 作者：tzl_Dedicatus545 (赞：2)

**1.题目分析**

让我们观察以下两个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/g73ar3g4.png)

对于 $1$ 号例子，我们可以发现，$C$ 点的坐标为 $(3,2)$ ，是点 $A$ 和 $B$ 的 $x,y$ 值的算术平均数。

对于 $2$ 号例子，因为他的 $x,y$ 值之和为奇数，所以不行。

到此，思路应该很明显了：

**AC Code:**

```
//By: Luogu@⚡炭治郎⚡(308854)
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	
	cin>>n;

	for(int i=1;i<=n;i++)
	{
		int a,b;
	
		cin>>a>>b;
		
		if((a+b)%2==1)
			cout<<"-1 -1"<<endl;
		
		else if(a%2==0&&b%2==0)
			cout<<a/2<<" "<<b/2<<endl;
		else
			cout<<a/2<<" "<<b/2+1<<endl;
	}
	
 	return 0;
}
```

---

## 作者：LYqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1612A) 

# 题目大意

定义两个点 $p_1$ (坐标为 $(x_1,y_1)$) 和 $p_2$ (坐标为 $(x_2,y_2)$) 之间的距离为 $d(p_1,p_2)=|x_1-x_2|+|y_1-y_2|$。

给定两个点 $A(0,0),B(x,y)$ 的坐标，求一个点 $C$ 的坐标，满足 $d(A,C)=d(B,C)=\dfrac{d(A,B)}{2}$ (不考虑取整)。若没有合法的 $C$ 输出 $(-1,-1)$。

# 思路

题目定义的距离就是曼哈顿距离，也就是两点间的距离。

由条件 $d(A,C)=d(B,C)=\dfrac{d(A,B)}{2}$ 可得知，$C$ 点一定在 $A$ 点和 $B$ 点正中间，因为 $A \rightarrow C=B \rightarrow C$。可以得到：$d(A,B)=d(A,C) \times 2=d(B,C) \times 2$。

观察下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hkjhzcym.png)

分情况讨论：

- 如果两条边奇偶性不同：通过题目中的**不考虑取整**可以想到，这种情况无解。

- 如果两条边都是偶数：容易想到，答案就是 $(\dfrac{x}{2},\dfrac{y}{2})$。
- 若两条边都是奇数：还是**不考虑取整**，我们就取最近的一个点，答案为 $(\dfrac{x}{2},\dfrac{y}{2}+1)$。

可以发现，图中的几个例子和样例都满足这些答案。

算出这几种情况的答案后，就没什么可说的了。

# 代码

~~(好像我代码里一个 `=` 都没有/jk)~~

```cpp
#include <iostream>
using namespace std;
int n,a,b;

int main(){
	cin >> n;
	while(n--){
		cin >> a >> b;
		if((a+b)&1){
			puts("-1 -1");
		}else if(!(a%2) && !(b%2)){
			cout << a/2 << " " << b/2 << endl;
		}else{
			cout << a/2 << " " << b/2+1 << endl;
		}
	}
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：1)

这道题的距离 $d(p_1,p_2)$ 其实就是两点横坐标差与纵坐标差之和（直角距离）。

而题目中的 $d(A,B)$ 就是点 $B$ 的横纵坐标之和。我们要找一点使得 $d(A,C)=d(C,B)$，那么点 $C$ 其实就是就是三角形两直角边长之和的中间位置。

那么，什么时候会没有合法的整数点呢？

显而易见，$d(A,B)$ 必须是偶数时，才可能找到坐标为整数的 $C$ 点。若为偶数则不然。

若有疑问详见参考代码：

```cpp
#include<iostream>
using namespace std;
int n,x,y;
int main(){
    cin>>n;
    while(n--){
        cin>>x>>y;
        if((x+y)&1){//若d(A,B)为偶数，则没有合法的整数点
            cout<<"-1 -1\n";
            continue;
        }
        int mid=(x+y)/2;//算出d(A,C)
        if(x<mid){
            cout<<x<<" "<<mid-x<<endl;
        }
        else cout<<mid<<" 0\n";
    }
    return 0;
}
```


---

## 作者：miao5 (赞：0)

这道题是一个简单的分情况讨论。

我们考虑在坐标轴中建立一个长方形，使得长方形的一个角是点 $A$，点 $A$ 的相对点是点 $B$。

这时我们要求求的点 $C$ 就变成了这个长方形两条对角线的交点。

但是我们注意到题目中说**不考虑取整**，这时如果一条边是偶数长度，但是另一条边是奇数长度，那么是不合法的，答案就是 $(-1,-1)$。

如果两条边的长度都是偶数的话，那么答案显然是 $(\frac{x}{2},\frac{y}{2})$。

还有一种情况就是两条边的长度都是奇数，这时我们不能准确地取到交点，于是我们就可以取靠近交点的整数点，答案为 $(\frac{x}{2},\frac{y}{2}+1)$。

```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int x,y;
		cin>>x>>y;
		if(x%2==0&&y%2==0) cout<<x/2<<' '<<y/2<<endl;
		else if((x+y)%2==1) cout<<-1<<' '<<-1<<endl;
		else cout<<x/2<<' '<<y/2+1<<endl;
	}
} 
```

---

## 作者：yinhy09 (赞：0)

## 思路分析：
首先，我们可以构造一个根据坐标构造一个正方形，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/oi8dbcl3.png)

因为`C`到`A`和`B`的距离一样，且为`A`到`B`的距离。所以d(A,B)=d(A,C)$\times 2$=d(B,C)$\times 2$ 。因为d(A,B)等于B点横纵坐标之和，且一定为2的倍数。

情况一：如果`B`点横纵坐标之和为奇数，则直接输出两个-1即可。

情况二：如果`B`点横纵坐标都为偶数，`C`点在上图正方形中心点（坐标为`B`点横纵坐标的一半）即可。

情况三：如果`B`点横纵坐标都为奇数，则`C`点需要在正方形中心点附近找一个坐标为整数的点。（只需将除以二运算适当向上或向下取整即可）


## 附上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;//数据组数
	int a,b;//图示中的B点坐标
	int x,y;//图示中C点坐标（所求的点）
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		if((a+b)%2==1)//情况一
			cout<<-1<<" "<<-1<<endl;
		else if(a%2==0&&b%2==0)//情况二
		{
			x=a/2;
			y=b/2;
			cout<<x<<" "<<y<<endl;
		} 
		else//情况三
		{
			x=a/2;
			y=b/2+1;//在附近找一个坐标为整数的点
			cout<<x<<" "<<y<<endl;
		}
	}
 	return 0;
}

```


---

## 作者：MeowScore (赞：0)

题意很清晰，不做描述。

由于 `A` 和 `C` 两点之间的距离要等于 `B` 和 `C` 两点之间的距离，还要等于 `A` 和 `B` 两点之间的距离**的一半**，且要求输出 `C` 的坐标为整数，因此如果 `A` 和 `B` 两点之间的距离是奇数，一定无解，这里特判一下。

这道题我们显然可以 $O(1)$ 做掉，但是，这么简单的题为什么不暴力一些呢……

那我们枚举做吧。暴力从 $1$ 到 $1000000$（题目要求 `C` 的横纵坐标的最大值）枚举横坐标，纵坐标显然每次可以根据限制直接求出来。然后判断是否合法，输出方案即可。可以用一个布尔变量记录是否找到解了，如果枚举一遍下来发现无解，那就输出 `-1 -1`。虽然如果 `A` 和 `B` 两点之间的距离是偶数时必定有解，但我在做的是无脑暴力，不想去证明有解，所以写上了这个没用的判断……


代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int x,y;
		cin>>x>>y;
		int dis=x+y;
		if(dis%2){
			puts("-1 -1");
			continue; 
		}
		bool flag=0;
		for(int i=0;i<=1000000;i++){
			int j=dis/2-i;
			if(i+j==abs(x-i)+abs(y-j)){
				cout<<i<<' '<<j<<endl;
				flag=1;
				break;
			}
		}
		if(!flag)
			puts("-1 -1");
	}
	return 0;
}








```






---

## 作者：Kris_hukr (赞：0)

### 题目大意

给你一个点 $A(x_1,y_1)$，令原点为 $O$。 试求出点 $B(x_2,y_2)$ 使：

- $A,B$ 的曼哈顿距离与 $B,O$ 的曼哈顿距离相等；
- $B,O$ 的曼哈顿距离应恰好等于 $\dfrac{x_1+y_1}{2}$，注意**不进行任何取整**；
- $x_2,y_2 \in \mathbb{N}$。

### 分析

注意到当 $x_1+y_1$ 为奇数时，显然无法在 $\mathbb{N}$ 内找到一组合法解。

更显然地，$x_1, y_1$ 均为偶数，$\left(\dfrac{x_1}{2}, \dfrac{x_2}{2} \right)$ 是合法解。

剩下的可以考虑构造：

- 当 $x_1 > y_1$ 时，可以注意到 $\left(\dfrac{x_1 - y_1}{2} , y_1 \right)$ 是合法解；
- 当 $y_1 \geq x_1$ 时，可以注意到 $\left( x_1 , \dfrac{y_1 - x_1}{2}\right)$ 是合法解。

当然，由于本题数据范围极小，也可以暴力搜索所有的点。

### 代码

```c++
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int x = read<int>(), y = read<int>();
        if ((x + y) & 1) {
            std::cout << "-1 -1\n";
            continue;
        }
        if (!(x & 1) and !(y & 1)) {
            std::cout << x / 2 << ' ' << y / 2 << '\n';
            continue;
        }

        if (x > y) {
            std::cout << (x - y) / 2 << ' ' << y << '\n';
        } else {
            std::cout << x << ' ' << (y - x) / 2 << '\n';
        }
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
```



---

## 作者：BFSDFS123 (赞：0)

**题目大意**

在坐标系上有个三节点 $A,B,C$ ，其中 $A$ 的坐标为 $(0,0)$， $B$ 的坐标为输入，求点 $C$ 的坐标，使 $d(A,C)=\dfrac{d(A,B)}{2},d(B,C)=\dfrac{d(A,B)}{2}$  ，其中 $D(A,B)=|A_x-B_x|+|A_y+B_y|$ 。

**解法**

有一种解法是直接算。

然而我不会，所以我用了简单粗暴的打表方式。

把 $(0,0)$ ，$(X,Y)$ 看成一个矩形的左下角和右上角。显然，如果有答案，则一定在这个矩形中，否则一定不存在。

那么直接暴力打表出每个答案，然后输出就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,pair<int,int> > mp;
void calc(int x,int y)
{
	for(int a=0;a<=100;a++)
	{
		for(int b=0;b<=100;b++)
		{
			if(a+b==abs(a-x)+abs(b-y))
			{
				mp[make_pair(x,y)]=make_pair(a,b);
				return ;
			}
		}
	}
	mp[make_pair(x,y)]=make_pair(-1,-1);
} 
int main()
{
	

	for(int i=0;i<=50;i++)
	{
		for(int j=0;j<=50;j++)
		{
			calc(i,j);
		}
	}
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d %d\n",mp[make_pair(a,b)].first,mp[make_pair(a,b)].second);
	}
	return 0;
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
给两个点 $A(0,0),B(x,y)$ ，求一个点 $C$ ，使得 $C$ 到 $A$ 和 $B$ 的曼哈顿距离都等于 $A$ 和 $B$ 的曼哈顿距离的一半。
## 2 思路
很明显，要求的点一定在线段 $AB$ 的垂直平分线上。  
首先，如果 $x,y$ 中有奇数，那么垂直平分线上就不存在整数点，输出 $-1$ 。  
如果 $x,y$ 都为偶数，那么答案就为 $AB$ 的中点 $C(x/2,y/2)$ 。  
否则答案就为 $C(x/2+1,y/2)$ 或者 $C(x/2+1,y/2)$ 。  
输出即可。    
时间复杂度 $O(T)$ 。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,x,y;
int main(){
	cin>>T;
	while(T--){
		cin>>x>>y;
		if((x+y)%2==1){//不存在
			cout<<"-1 -1";
		}else{
			if(x%2==0){//中点
				cout<<x/2<<" "<<y/2;
			}else{//垂直平分线上
				if(x>=y) cout<<x/2<<" "<<y/2+1;
				else cout<<x/2+1<<" "<<y/2;
			}
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Star_Route (赞：0)

这是一道签到题，考察的是曼哈顿距离的中点公式。  
我们对它分类讨论。  
 1. 由于要求整数点，所以显然，如果 $A(x,y)$ 中 $x,y$ 奇偶性不同，则中点是一个小数，故
```cpp
puts("-1 -1")
```  
 2. 先讨论偶数情况，这很简单，在此时欧氏距离中点与曼哈顿距离中点重合，均为 $(\frac{x}{2},\frac{y}{2})$。  
 3. 考虑奇数情况，先看横坐标大于纵坐标的情况，我们在纵坐标不变的情形下去构造，解方程可得 $(\frac{x-y}{2},y)$。再看纵坐标大于横坐标的情况，我们在横坐标不变的情形下去构造，解方程可得 $(x,\frac{y-x}{2})$。  
 
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y;
inline int read()
{
	int sum=0,x=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if (ch=='-')
			x=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9')
	{
		sum=sum*10+ch-'0';
		ch=getchar();
	}
	return sum*x;
}
inline void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
int main()
{
	t=read();
	while (t--)
	{
		x=read();y=read();
		if ((x&1)!=(y&1))
		{
			puts("-1 -1");
			continue;
		}
		if (!(x&1))
		{
			write(x/2);
			putchar(' ');
			write(y/2);
			putchar('\n');
		}else
		{
			if (x>y)
			{
				write((x-y)/2);
				putchar(' ');
				write(y);
			}else
			{
				write(x);
				putchar(' ');
				write((y-x)/2);
			}
			putchar('\n');
		}
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# $CF1612A\;Distance$ 题解

## 题目大意

定义函数 $d(A,B)=\left|A.x-B.x\right|+\left|A.y-B.y\right|$ 表示平面上两点 $A$，$B$ 之间的距离

给定点 $A$，$B$，求一个点 $C$ 满足：

$\begin{cases}\quad d(A,C)=\dfrac{d(A,B)}{2}\\\quad d(B,C)=\dfrac{d(A,B)}{2}\end{cases}$

其中点 $A$ 固定为 $(0,0)$

点 $B$ 的 $x$，$y$ 坐标均 $\geq0$ 且 $\leq50$ 

点 $C$ 的 $x$，$y$ 坐标均 $\geq 0$ 且为整数

无解时输出 $-1\,-1$

## 思路分析

$\because A.x=(0,0)$ 且 $d(A,C)=\dfrac{d(A,B)}{2}$

$\therefore C.x+C.y=\dfrac{B.x+B.y}{2}$

枚举每一对可能的 $C.x$，$C.y$，然后用 $d(B,C)=\dfrac{d(A,B)}{2}$ 验证即可

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
struct point {
	int x,y;
};
inline int d(const point &a,const point &b) {
	//题目中的d函数 
	return abs(a.x-b.x)+abs(a.y-b.y);
}
inline bool judge(const point &a,const point &b,const point &c) {
	//判断点a,b,c是否满足题目中的条件 
	return 2*d(a,c)==d(a,b)&&2*d(b,c)==d(a,b);
}
inline void solve(const point &a,const point &b) {
	int sum=b.x+b.y;
	if(sum&1) {
		//如果点c坐标不为整数，直接无解 
		puts("-1 -1");
		return ;
	}
	sum=sum>>1;
	point c=(point){0,sum};
	for(;c.y>=0;++c.x,--c.y) {
		//枚举所有可能的c 
		if(judge(a,b,c)) {
			//如果可以直接输出 
			printf("%d %d\n",c.x,c.y);
			return ;
		}
	}
	//没有可能的解 
	puts("-1 -1");
	return ;
}
signed main() {
	point a;
	a.x=a.y=0;
	//A:(0,0) 
	int t;
	scanf("%d",&t);
	while(t--) {
		point b;
		scanf("%d %d",&b.x,&b.y);
		solve(a,b);
	}
	return 0;
}
```



---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1612A)

诈骗！！！

题意是给定 $A(0,0)$ 和 $B(x,y)$，$0 \le x,y \le 50$，求是否有坐标均为非负整数的点 $C$，满足 $d(A,C)=d(B,C)=\dfrac{d(A,B)}{2}$。（$d(x,y)$ 表示 $x,y$ 之间的**曼哈顿距离**）

这种一眼数学题本来以为放在 A 必有高论，然后想了半天发现数据范围 $0 \le x,y \le 50$，自闭了。

考虑设 $C(i,j)$，显然有 $0 \le i \le x,0 \le j \le y$，于是直接暴力枚举 $i,j$ 即可。

时间复杂度 $O(txy)$。

---

