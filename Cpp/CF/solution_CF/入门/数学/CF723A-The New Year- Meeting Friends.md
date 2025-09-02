# The New Year: Meeting Friends

## 题目描述

有三个朋友在一条笔直的岛上生活着，我们将其看做一条直线（数轴）。第一个人的家在点$x_1$​ 处，第二个人的家在点$x_2$处，第三个人的家在点$x_3$处。他们计划一起庆祝新年，所以他们需要在直线上的任一某点见面。请你帮他们找出一个点，使得他们走的总距离最短，并求出这个总距离。

## 说明/提示

在第一个样例中，朋友们应在点4见面。因此，第一个朋友必须走3个单位距离（从点7到点4），第二个朋友也要走3个单位距离（从点1到点4），而第三位朋友不用去任何地方，因为他住在点4。

感谢@cplus 提供的翻译

## 样例 #1

### 输入

```
7 1 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
30 20 10
```

### 输出

```
20
```

# 题解

## 作者：引领天下 (赞：8)

这题非常简单，就是一个数论

首先，我们考虑最大和最小的两个数：

如果要他们的差最小，那么集合点必须在他们之间（绝对值的几何意义）

而这个点又可以设在中间值的点上，所以中间点的距离=0

所以此题的答案=

$ max(a,b,c)-min(a,b,c)$

代码：

```cpp
#include <cstdio>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
int main(void){
    int a,b,c;
    scanf ("%d%d%d",&a,&b,&c);
    printf ("%d",max(max(a,b),c)-min(min(a,b),c));
}
```

---

## 作者：panlin (赞：3)

易知三者中间值为最佳位置

则用最大值减去最小值即为所求总距离

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int a[3];
	for(int i = 0; i < 3; i++) {
		cin >> a[i];
	}
	sort(a, a + 3);
	cout << a[2] - a[0] << endl;
	return 0;
}
```


---

## 作者：666yuchen (赞：3)

# 简单模拟：
```cpp
//666yuchen
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>//文件头
#define ii int
using namespace std;
ii a,b,c,minz=2100000000;//定义
int main()
{
  cin>>a>>b>>c;//输入。
  if(a>b)swap(a,b);
  if(a>c)swap(a,c);
  if(b>c)swap(b,c);//首先保证这三个数有序（为了下面的优化做铺垫）
  for(int i=a;i<=c;i++)//优化:不用从1到最大值循环，直接从最小值到最大值循环，优化了一定的时间
    minz=min(minz,abs(a-i)+abs(b-i)+abs(c-i));//算出每个人到这个位置的距离总和，和最小值比较，找出新的最小值。
  cout<<minz<<endl;//输出
  return 0;//程序拜拜
}
```
### 为了营造美好的洛谷，请不要抄袭!!!

---

## 作者：bym666 (赞：0)

# CF723A 【The New Year: Meeting Friends】
这道题我用的方法是枚举，从最小值枚举到最大值，在枚举的时候求最小距离。

详细注释请见代码↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
int x,y,z,a,b,c,ans=0x3f3f3f3f;//ans记得赋值为int最大值 
int main()
{
	cin>>x>>y>>z;//输入 
	a=x;b=y;c=z; 
	x=min(a,min(b,c));//求最小值 
	z=max(a,max(b,c));//求最大值
	//友情提示，min和max只能有两个参数 
	for(int i=x;i<=z;i++)//从最小值到最大值枚举 
	{
		if(ans>(abs(x-i)+abs(y-i)+abs(z-i))) ans=abs(x-i)+abs(y-i)+abs(z-i);
		//如果ans比求出的距离大，则ans赋值为求出的距离 
	}
	cout<<ans;//输出 
	return 0;//结束程序 
}
```
我一开始把第18行的if语句写错了，不小心把大于号写成了小于号（悲催????）。

---

## 作者：OdtreePrince (赞：0)

# -数论-

根据所学的数学知识，可得中间值是最优的地点，那么，两边到中间的距离为(max-middle)+(middle-min)=max-min.

既然如此，只需求出最大值和最小值就可以了。

上代码

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c,maxx,minn;
    scanf("%d%d%d",&a,&b,&c);
    maxx=max(a,max(b,c));
    minn=min(a,min(b,c));
    cout<<maxx-minn;
    return 0;
}
~~~

---

