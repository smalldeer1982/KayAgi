# [NWRRC 2014] Grave

## 题目描述

Gerard 开发了一款万圣节电脑游戏。游戏在一个矩形墓地上进行，墓地中有一个矩形教堂。在游戏中，玩家需要在墓地上放置新的矩形墓碑。墓碑必须完全放置在墓地范围内，并且不能与教堂重叠。墓碑可以接触墓地或教堂的边界。

Gerard 要求你编写一个程序，判断是否可以放置给定大小的新墓碑，或者是否没有足够的空间。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1 1 11 8
2 3 8 6
3 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 1 11 8
2 3 8 6
4 3
```

### 输出

```
No
```

# 题解

## 作者：ztjp13 (赞：31)

刷题时无意看到这道题，~~似乎墓地墓碑的不太吉利……~~

不过这题本身还是比较水，就是教堂的上下左右四个方向判断一下，没什么特别的注意点，所以直接上代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a,b,c,d,e,f,g,h,x,y;
//空行，注意码风
int main(){
	cin>>a>>b>>c>>d>>e>>f>>g>>h>>x>>y;
	if(c-g>=x&&d-b>=y){
		cout<<"Yes"<<endl;
		return 0;
	}
	else if(e-a>=x&&d-b>=y){
		cout<<"Yes"<<endl;
		return 0;
	}
	else if(c-a>=x&&f-b>=y){
		cout<<"Yes"<<endl;
		return 0;
	}
	else if(c-a>=x&&d-h>=y){
		cout<<"Yes"<<endl;
		return 0;
	}//注意相减关系以及比较对象，容易错
	cout<<"No"<<endl;//注意Yes和No的大小写
	return 0;
} 
```
顺手给个赞吧！

---

## 作者：赵悦岑 (赞：7)

没想到居然能首A，那也发个题解吧

题目其实指的就是一块回形的空地，能不能放下一个矩形。

如果放得下，只有四种情况：放在教堂的上、下、左、右。

首先如果整个墓地都放不下墓碑，就不可能放得下。

其次，如果墓地边缘与教堂的距离比墓碑对应边大，那么在这一边就放得下墓碑

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int main()
{
	int a1,b1,c1,d1,a2,b2,c2,d2,x,y;
	cin>>a1>>b1>>c1>>d1>>a2>>b2>>c2>>d2>>x>>y;
	if(a2-a1>=x&&d1-b1>=y)
	{
		printf("Yes");
		return 0;
	}
	if(c1-c2>=x&&d1-b1>=y)
	{
		printf("Yes");
		return 0;
	}
	if(b2-b1>=y&&c1-a1>=x)
	{
		printf("Yes");
		return 0;
	}
	if(d1-d2>=y&&c1-a1>=x)
	{
		printf("Yes");
		return 0;
	}
	printf("No");
	return 0;
}
```


---

## 作者：CpppRCG (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7066)

# 题意：
在一块长方形的墓地上，有一个长方形的教堂，现在给出一块墓碑，墓碑不能与教堂重叠，已知两者的坐标与墓碑的长宽，询问这块墓地上能否放下这块墓碑。

# 思路：
目的很明确，就是要判断墓地上能否放下这块墓碑。如果墓碑的长宽大于墓地的长宽，那肯定放不下；因为墓地不能与教堂重叠，所以要判断教堂上、下、左、右四个方向上能否放下墓碑，用坐标值相减来判断。

# 代码实现：

非常简短的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int q,w,e,r,t,y,u,i,o,p;//定义10个变量
	cin>>q>>w>>e>>r>>t>>y>>u>>i>>o>>p;//读入
	if(t-q>=o&&r-w>=p) cout<<"Yes";//上方向判断
	else if(e-u>=o&&r-w>=p) cout<<"Yes";//下方向判断
	else if(y-w>=p&&e-q>=o) cout<<"Yes";//左方向判断
	else if(r-i>=p&&e-q>=o) cout<<"Yes";//右方向判断
	else cout<<"No";//如果都放不下，输出No
	return 0;//完美结束
} 
```

跪求管理大大过审！

---

