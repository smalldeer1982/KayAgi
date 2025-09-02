# Triangle

## 题目描述

At a geometry lesson Bob learnt that a triangle is called right-angled if it is nondegenerate and one of its angles is right. Bob decided to draw such a triangle immediately: on a sheet of paper he drew three points with integer coordinates, and joined them with segments of straight lines, then he showed the triangle to Peter. Peter said that Bob's triangle is not right-angled, but is almost right-angled: the triangle itself is not right-angled, but it is possible to move one of the points exactly by distance 1 so, that all the coordinates remain integer, and the triangle become right-angled. Bob asks you to help him and find out if Peter tricks him. By the given coordinates of the triangle you should find out if it is right-angled, almost right-angled, or neither of these.

## 样例 #1

### 输入

```
0 0 2 0 0 1
```

### 输出

```
RIGHT
```

## 样例 #2

### 输入

```
2 3 4 5 6 6
```

### 输出

```
NEITHER
```

## 样例 #3

### 输入

```
-1 0 2 0 0 1
```

### 输出

```
ALMOST
```

# 题解

## 作者：yzh_Error404 (赞：8)

这道题的难点在于细节。

首先，我们可以用勾股定理判断一个三角形是否为直角三角形，若是，则输出 `RIGHT` （因为求距离时用平方根会出现精度问题，而且在勾股时也要再次平方，所以我在求距离时没有用平方根。）

然后，手动将三角形的三个点上下左右平移，用之前的判直角三角形的函数判断现在是否成立，若成立，则输出 `ALMOST`。

最后，若这个三角形不满足上面两种情况，则输出 `NEITHER`

注意：在判断是否为直角三角形的函数中，需要判断有没有两点实际为同一点

放代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;
}e[10];
int dis[10],cnt;
inline int dist(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);//因精度问题没有平方根
}
inline bool cmp(int x,int y)
{
	return x<y;
}
inline bool check()
{
	memset(dis,0x3f,sizeof(dis));
	cnt=0;
	for(register int i=1;i<=3;i++)
		for(register int j=i;j<=3;j++)
			if(i!=j&&e[i].x==e[j].x&&e[i].y==e[j].y)return false;//判断两点是否为同一点
	for(register int i=1;i<=3;i++)
		for(register int j=i;j<=3;j++)
			if(i!=j)dis[++cnt]=dist(e[i].x,e[i].y,e[j].x,e[j].y);//求三角形三边长
	sort(dis+1,dis+4,cmp);
	if((dis[1]+dis[2])==dis[3])return true;//因求边长时没有平方根，所以这里没有平方
	return false;
}
int main()
{
	for(register int i=1;i<=3;i++)
		scanf("%d %d",&e[i].x,&e[i].y);
	if(check())//最开始就是直角三角形
	{
		puts("RIGHT");
		return 0;
	}
	for(register int i=1;i<=3;i++)//手动平移
	{
		e[i].x++;
		if(check())
		{
			puts("ALMOST");
			return 0;
		}
		e[i].x--;
		e[i].x--;
		if(check())
		{
			puts("ALMOST");
			return 0;
		}
		e[i].x++;
		e[i].y++;
		if(check())
		{
			puts("ALMOST");
			return 0;
		}
		e[i].y--;
		e[i].y--;
		if(check())
		{
			puts("ALMOST");
			return 0;
		}
		e[i].y++;
	}
	puts("NEITHER");
	return 0;
}

```

---

## 作者：codemap (赞：5)

不得不说这道题简直是我见过最恶心的题，代码量极大（~~复制粘贴大法吼~~）

但思路还是很简单的

直接按照题意判断

因为两点之间距离公式是sqrt(（横坐标1-横坐标2）^2+(纵坐标1-纵坐标2)^2)

勾股定理是a^2+b^2=c^2

所以可以直接将（横坐标1-横坐标2）^2+(纵坐标1-纵坐标2)^2看成a，将勾股定理看成a+b=c

RIGHT直接用两点之间距离公式

ALMOST将每个横/纵坐标+1/-1 共12种可能

NEITHER都不是

最后需要注意要判断a,b,c均非0

然后就是代码的事了

~~上我极其长的丑陋的代码~~

```c
#include<iostream>
using namespace std;
bool zhijiao(int a,int b,int c)//判断直角
{
	return (a+b==c||b+c==a||c+a==b)&&a>0&&b>0&&c>0;//勾股定理的变形和a,b,c非0
}
int pingfang(int n)//平方函数
{
	return n*n;
}
int main()
{
	int x1,y1,x2,y2,x3,y3;//三个坐标
	cin>>x1>>y1>>x2>>y2>>x3>>y3;
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2),pingfang(x2-x3)+pingfang(y2-y3),pingfang(x3-x1)+pingfang(y3-y1)))//直接用两点之间距离公式
	{
		cout<<"RIGHT";
		return 0;
	}
	if(zhijiao(pingfang(x1+1-x2)+pingfang(y1-y2),pingfang(x2-x3)+pingfang(y2-y3),pingfang(x3-x1-1)+pingfang(y3-y1)))//x1+1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-1-x2)+pingfang(y1-y2),pingfang(x2-x3)+pingfang(y2-y3),pingfang(x3-x1+1)+pingfang(y3-y1)))//x1-1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2-1)+pingfang(y1-y2),pingfang(x2+1-x3)+pingfang(y2-y3),pingfang(x3-x1)+pingfang(y3-y1)))//x2+1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2+1)+pingfang(y1-y2),pingfang(x2-1-x3)+pingfang(y2-y3),pingfang(x3-x1)+pingfang(y3-y1)))//x2-1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2),pingfang(x2-x3-1)+pingfang(y2-y3),pingfang(x3+1-x1)+pingfang(y3-y1)))/x3+1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2),pingfang(x2-x3+1)+pingfang(y2-y3),pingfang(x3-1-x1)+pingfang(y3-y1)))//x3-1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1+1-y2),pingfang(x2-x3)+pingfang(y2-y3),pingfang(x3-x1)+pingfang(y3-y1-1)))//y1+1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-1-y2),pingfang(x2-x3)+pingfang(y2-y3),pingfang(x3-x1)+pingfang(y3-y1+1)))//y1-1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2-1),pingfang(x2-x3)+pingfang(y2+1-y3),pingfang(x3-x1)+pingfang(y3-y1)))//y2+1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2+1),pingfang(x2-x3)+pingfang(y2-1-y3),pingfang(x3-x1)+pingfang(y3-y1)))//y2-1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2),pingfang(x2-x3)+pingfang(y2-y3-1),pingfang(x3-x1)+pingfang(y3+1-y1)))//y3+1
	{
		cout<<"ALMOST";
		return 0;
	}
	if(zhijiao(pingfang(x1-x2)+pingfang(y1-y2),pingfang(x2-x3)+pingfang(y2-y3+1),pingfang(x3-x1)+pingfang(y3-1-y1)))//y3-1
	{
		cout<<"ALMOST";
		return 0;
	}
	cout<<"NEITHER";//都不是
	return 0;
}
```

---

## 作者：Sophon (赞：3)

用向量点积为零判断三角形是否为直角三角形，前提是边向量不为零向量。使用方向数组（类似搜索中的操作）控制点的移动。详见代码注释。~~pair表示点和向量、大括号换行勿喷~~。
```cpp
#include <iostream>

using namespace std;
using pii = pair<int, int>;//C++11 using 可代替typedef

inline int calc(const pair<int, int>& vec1, const pair<int, int>& vec2)//计算向量点积
{
	return vec1.first * vec2.first + vec1.second * vec2.second;
}

inline bool zero(const pair<int, int>& vec)//判断零向量
{
	return !(vec.first || vec.second);
}

bool xhl(const pair<int, int>& a, const pair<int, int>& b, const pair<int, int>& c)//判断是否为直角三角形
{
	//边向量
	pii v1 = { b.first - a.first, b.second - a.second };
	pii v2 = { c.first - a.first, c.second - a.second };
	pii v3 = { c.first - b.first, c.second - b.second };

	if (zero(v1) || zero(v2) || zero(v3))//排除零向量
	{
		return false;
	}

	if (calc(v1, v2) == 0 || calc(v1, v3) == 0 || calc(v3, v2) == 0)//如果三边边向量中有两个点积为0
	{
		return true;
	}
	return false;
}

int main()
{
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;

	pii point[4];//顶点
	point[1] = { a,b }, point[2] = { c,d }, point[3] = { e,f };
	
    //判断本身是否为直角三角形
	if (xhl(point[1], point[2], point[3]))
	{
		cout << "RIGHT" << endl;
		return 0;
	}
	//方向数组
	const int dx[] = { 1, 0, -1, 0 };
	const int dy[] = { 0, 1, 0, -1 };
	//枚举三个点
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)//枚举四个方向
		{
			point[i] = { point[i].first + dx[j],point[i].second + dy[j] };//更新点坐标
			if (xhl(point[1], point[2], point[3]))//新三角形为直角三角形
			{
				cout << "ALMOST" << endl;
				return 0;
			}
			point[i] = { point[i].first - dx[j],point[i].second - dy[j] };//返回现场
		}
	}
	
	cout << "NEITHER" << endl;
	return 0;
}
```

---

## 作者：Argon_Cube (赞：1)


* **【题目链接】**

[Link:CF18A](https://www.luogu.com.cn/problem/CF18A)

* **【解题思路】**

如何判断一个三角形是否是直角三角形？

我第一眼看到时，想到的是勾股定理。

有了这个勾股定理，判断就好写了。

我选择将判断放在一个单独的`check`函数里。

于是我们可以很轻易地写出判断$RIGHT$的代码。

接下来，是判断$ALMOST$。

只要暴力枚举每个数加一或减一后是否是一个直角三角形。

这里即使常数再大，因为只有三个点，所以永远不会超时。

如果两个判断都没成功，输出$NEITHER$。



* **【代码】**

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

bool check(vector<pair<int,int>> points)
{
	int fst=(points[0].first-points[1].first)*(points[0].first-points[1].first)+(points[0].second-points[1].second)*(points[0].second-points[1].second);
	int scd=(points[1].first-points[2].first)*(points[1].first-points[2].first)+(points[1].second-points[2].second)*(points[1].second-points[2].second);
	int trd=(points[2].first-points[0].first)*(points[2].first-points[0].first)+(points[2].second-points[0].second)*(points[2].second-points[0].second);
	if((fst+scd==trd||scd+trd==fst||trd+fst==scd)&&fst>0&&scd>0&&trd>0)
		return true;
	return false;
}

int main(int argc,char *argv[],char *env[])
{
	vector<pair<int,int>> points(3),temp;
	for(int i=0;i<3;i++)
		cin>>points[i].first>>points[i].second;
	if(check(points))
	{
		cout<<"RIGHT";
		return 0;
	}
	for(int i=0;i<3;i++)
	{
		temp=points;
		temp[i].first++;
		if(check(temp))
		{
			cout<<"ALMOST";
			return 0;
		}
		temp=points;
		temp[i].first--;
		if(check(temp))
		{
			cout<<"ALMOST";
			return 0;
		}
		temp=points;
		temp[i].second++;
		if(check(temp))
		{
			cout<<"ALMOST";
			return 0;
		}
		temp=points;
		temp[i].second--;
		if(check(temp))
		{
			cout<<"ALMOST";
			return 0;
		}
	}
	cout<<"NEITHER";
 	return 0;
}

```

---

## 作者：Asexual (赞：0)

暴力枚举移动方式，看代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,1,-1};
int x[4],y[4];
double dis[4];
bool check(int a,int b){return x[a]==x[b]&&y[a]==y[b];}//判断两个点位置是否相等 
void dist()
{
	dis[1]=((x[1]-x[2])*(x[1]-x[2])+(y[1]-y[2])*(y[1]-y[2]));
	dis[2]=((x[1]-x[3])*(x[1]-x[3])+(y[1]-y[3])*(y[1]-y[3]));
	dis[3]=((x[3]-x[2])*(x[3]-x[2])+(y[3]-y[2])*(y[3]-y[2]));//计算两点间的距离（不用浮点） 
	sort(dis+1,dis+4);//排序 
}
void move(int num,int id)
{
	x[num]+=dx[id];y[num]+=dy[id];//枚举移动方式 
	dist();
	if(dis[1]+dis[2]==dis[3])//条件成立 
	{
		if(check(1,2)||check(1,3)||check(2,3));//有点的位置相同 
		else 
		{
			cout<<"ALMOST";
			exit(0);
		}	
	}
	x[num]-=dx[id];y[num]-=dy[id];//还原原状态 
}
int main()
{
	for(int i=1;i<=3;i++)
		cin>>x[i]>>y[i];
	dist();
	if(dis[1]+dis[2]==dis[3])//直接可以组成直角三角形 
	{
		cout<<"RIGHT";
		return 0;
	}
	for(int i=1;i<=3;i++)
		for(int j=1;j<=4;j++)
			move(i,j);//枚举移动方式 
	cout<<"NEITHER";
}
```


---

