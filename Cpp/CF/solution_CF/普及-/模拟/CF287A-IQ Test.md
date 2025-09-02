# IQ Test

## 题目描述

In the city of Ultima Thule job applicants are often offered an IQ test.

The test is as follows: the person gets a piece of squared paper with a $ 4×4 $ square painted on it. Some of the square's cells are painted black and others are painted white. Your task is to repaint at most one cell the other color so that the picture has a $ 2×2 $ square, completely consisting of cells of the same color. If the initial picture already has such a square, the person should just say so and the test will be completed.

Your task is to write a program that determines whether it is possible to pass the test. You cannot pass the test if either repainting any cell or no action doesn't result in a $ 2×2 $ square, consisting of cells of the same color.

## 说明/提示

In the first test sample it is enough to repaint the first cell in the second row. After such repainting the required $ 2×2 $ square is on the intersection of the $ 1 $ -st and $ 2 $ -nd row with the $ 1 $ -st and $ 2 $ -nd column.

## 样例 #1

### 输入

```
####
.#..
####
....
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
####
....
####
....
```

### 输出

```
NO
```

# 题解

## 作者：MornEveGlow (赞：3)

先来看看一个2x2的格子会出现什么情况。
1. 4B0W（B指黑、W指白，下同）：
显然符合条件，此时黑白数量之差为4。
2. 3B1W：
将白改为黑即可，此时黑白数量之差为2。
3. 2B2W：
易知不能通过最多一次将其改为同色，此时黑白数量之差为0。
4. 1B3W：
同2、符合条件，此时黑白数量之差为-2。
5. 0B4W：
显然符合条件，此时黑白数量之差为-4。

所以**只有当差为0时不符合条件**。只要其中任何一个2x2的矩阵差不为零、大矩阵就符合条件。

 _下附核心枚举代码。_ 
```
int Z(char ch){return ch=='.'?-1:1;}
...
int main(){
	...
	for(int i=0;i<3;++i)
	for(int j=0,tmp;j<3;++j)
		flag|=Z(A[i][j])+Z(A[i][j+1])+Z(A[i+1][j])+Z(A[i+1][j+1]);
```

---

## 作者：hensier (赞：2)

$\red{\text{暴力出奇迹。——某大佬}}$

本蒟蒻这道题暴力的原因：

- 矩阵大小确定。
- 矩阵边长极小。
- 考虑情况极少。

我们可以把$4\times 4$的矩阵进行$2\times 2$的拆分，即：

|$\red{\text{RED}}$|$\red{\text{RED}}$|$\blue{\text{BLUE}}$|$\blue{\text{BLUE}}$|
| :----------: | :----------: | :----------: | :----------: |
|$\red{\text{RED}}$|$\red{\text{COMMON}}$|$\blue{\text{COMMON}}$|$\blue{\text{BLUE}}$|
|$\green{\text{GREEN}}$|$\green{\text{COMMON}}$|$\purple{\text{COMMON}}$|$\purple{\text{PURPLE}}$|
|$\green{\text{GREEN}}$|$\green{\text{GREEN}}$|$\purple{\text{PURPLE}}$|$\purple{\text{PURPLE}}$|

上表可以呈现$2\times 2$的分布，其中$3$个颜色块$+1$个公共块可以组成$4$个$2\times 2$，而$4$个公共块也可以再形成一个。

为了方便，我们可以把一个$2\times 2$存入一个数组。

即：

```cpp
group[0][0]=c[0][0];
group[0][1]=c[0][1];
group[0][2]=c[1][0];
group[0][3]=c[1][1];
group[1][0]=c[0][2];
group[1][1]=c[0][3];
group[1][2]=c[1][2];
group[1][3]=c[1][3];
group[2][0]=c[2][0];
group[2][1]=c[2][1];
group[2][2]=c[3][0];
group[2][3]=c[3][1];
group[3][0]=c[2][2];
group[3][1]=c[2][3];
group[3][2]=c[3][2];
group[3][3]=c[3][3];
/*先存入3个颜色块+1个公共块的情况，group[i][j]表示第i个2*2的第j个元素*/
```

依题意可知，对于每一个$i$，如果要输出$YES$，就必定要满足：

$$\sum_{j=0}^{3}group[i][j]≠2$$

意思就是，"$.$"（或者"$\#$"）的数量不为2的时候，就能够满足条件。

最后需要判断$4$个公共块的情况，只要五个区域有一个满足就输出$YES$。

$AC$代码：

```cpp
#include<cstdio>
#define f()for(int i=0;i<4;i++)//宏定义for循环，极其方便
char c[5][5],group[5][5];//定义矩阵
int n;//保存'.'的数量（用来保存'#'也可以）
int main()
{
    f()gets(c[i]);//循环输入
    group[0][0]=c[0][0];
    group[0][1]=c[0][1];
    group[0][2]=c[1][0];
    group[0][3]=c[1][1];
    group[1][0]=c[0][2];
    group[1][1]=c[0][3];
    group[1][2]=c[1][2];
    group[1][3]=c[1][3];
    group[2][0]=c[2][0];
    group[2][1]=c[2][1];
    group[2][2]=c[3][0];
    group[2][3]=c[3][1];
    group[3][0]=c[2][2];
    group[3][1]=c[2][3];
    group[3][2]=c[3][2];
    group[3][3]=c[3][3];//存储
    f()
    {
        n=0;//一开始初始化为0
        for(int j=0;j<4;j++)n+=group[i][j]=='.';//无需if，只需用bool的定义累加
        if(n-2)
        {
            printf("YES");
            return 0;//不等于2就输出并结束程序
        }
    }
    n=0;//初始化很重要！！！
    n+=c[1][1]=='.';
    n+=c[1][2]=='.';
    n+=c[2][1]=='.';
    n+=c[2][2]=='.';
    if(n-2)printf("YES");//如果n≠2就输出YES
    else printf("NO");//否则输出NO
}
```

~~暴力来之不易，大佬勿喷。~~

---

## 作者：zhanghengrui (赞：1)

思路：

读入，然后判断有没有满足条件的$2\times2$矩形，如果有就直接输出“YES”；如果没有，枚举每一个点，判断如果改变它是否会满足条件

------------

代码：

```cpp
#include<cstdio>
char pic[4][4];
inline bool ck(int row,int col)//判断以(row,col)为左上角的2*2的矩形是否颜色相同
{
	return pic[row][col]==pic[row][col+1]&&pic[row][col]==pic[row+1][col]&&pic[row][col]==pic[row+1][col+1];
}
inline bool ck()//判断4*4大矩形中是否有满足条件的小矩形
{
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
		{
			if(ck(i,j)) return true;
		}
	}
	return false;
}
int main()
{
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j) scanf(" %c",pic[i]+j);//读入
	}
	if(ck()) printf("YES");//如果不用改就有
	else
	{
		for(int i=0;i<4;++i)
		{
			for(int j=0;j<4;++j)//枚举每一个点
			{
				switch(pic[i][j])
				{
					case '.'://是白
						pic[i][j]='#';//变黑
						if(ck())//判断
						{
							printf("YES");
							goto END;
						}
						pic[i][j]='.';//变回白
						break;
					case '#'://是黑
						pic[i][j]='.';//变白
						if(ck())//判断
						{
							printf("YES");
							goto END;
						}
						pic[i][j]='#';//变回黑
						break;
				}
			}
		}
		printf("NO");
	}
	END:return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：0)

既然4 * 4  的规模不太大，那我们就试试超级暴力。

思路：枚举每个2 * 2的格子是不是有三个一样的格子，一共枚举九次。

外面要再套个循环吗？不用。（所以行数有……）

 **前方高能！！！！！**
 ```
#include<bits/stdc++.h>
using namespace std; 
 char a[5][5];
 int c=0,b=0;
int main()
{   
     for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)cin>>a[i][j];//输入
   
        for(int i=1;i<=2;i++)//从1 2开始，枚举2* 2矩阵
           for(int j=1;j<=2;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   		if(c==3||b==3||c==4||b==4)//注意c和b的只
            如果是4，也是对的，我就被坑了。
            {cout<<"YES"<<endl;return 0;}
	   		c=0;b=0;
	   //后面同上。
	    for(int i=1;i<=2;i++)
           for(int j=2;j<=3;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   		if(c==3||b==3||c==4||b==4)
            {cout<<"YES"<<endl;return 0;}
	   	    c=0;b=0;
	
		for(int i=1;i<=2;i++)
           for(int j=3;j<=4;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   		if(c==3||b==3)
            {cout<<"YES"<<endl;return 0;}
	   	    c=0;b=0;
	   	for(int i=2;i<=3;i++)
           for(int j=1;j<=2;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   		if(c==3||b==3||c==4||b==4)
            {cout<<"YES"<<endl;return 0;}
	   		c=0;b=0;
	   	for(int i=2;i<=3;i++)
           for(int j=2;j<=3;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   		if(c==3||b==3||c==4||b==4)
            {cout<<"YES"<<endl;return 0;}
	   		c=0;b=0;
	   	for(int i=2;i<=3;i++)
           for(int j=3;j<=4;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   	if(c==3||b==3||c==4||b==4)
        {cout<<"YES"<<endl;return 0;}
	   		c=0;b=0;
	   	for(int i=3;i<=4;i++)
           for(int j=1;j<=2;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   	if(c==3||b==3||c==4||b==4)
        {cout<<"YES"<<endl;return 0;}
	   		c=0;b=0;
	   	for(int i=3;i<=4;i++)
           for(int j=2;j<=3;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   	if(c==3||b==3||c==4||b==4)
        {cout<<"YES"<<endl;return 0;}	   	
	   		c=0;b=0;
	   	for(int i=3;i<=4;i++)
           for(int j=3;j<=4;j++)
           {
            if(a[i][j]=='#')c++;
	        else b++;
	   		}
	   	if(c==3||b==3||c==4||b==4)
        {cout<<"YES"<<endl;return 0;}
	cout<<"NO"<<endl;//如果没有return 0输出NO；
    return 0;
}


```
虽然繁琐，但对我这样的初学者来说，竟然让做题速度变快了

~~我竟然不会再它的外面套一个循环 因为总是出错~~，

而且也不难理解


---

## 作者：周子衡 (赞：0)

思路：模拟

对于每个$2\times 2$的正方形，可以发现：只要其中黑格数量不为$2$，那么必定可以通过改一个格子满足条件

模拟即可（自认为跑的还是蛮快的）

附上代码：

```cpp
#include<cstdio>

using namespace std;

char c[4][4]={};

int main()
{
    for(int i=0;i<4;i++)
    {
        scanf("%s",c[i]);
    }
    int ans=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            ans=0;
            if(c[i][j]=='#')
            {
                ans++;
            }
            if(c[i+1][j]=='#')
            {
                ans++;
            }
            if(c[i][j+1]=='#')
            {
                ans++;
            }
            if(c[i+1][j+1]=='#')
            {
                ans++;
            }
            if(ans!=2)
            {
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
    return 0;
}
```

---

## 作者：Kuriyama_Mirai (赞：0)

### 看到我们学校好多学~~姐~~长发了好多神仙解法……
#### 鄙人不才，来发一个最容易想的做法。

思考部分
---

首先看到数据只有$4\times4$，是不是十分激动？

第一步，当然是先看看是不是本来已经满足条件了。如果不这样，你会发现有这样一种珂怕的数据能够让你$\color{red}{\mathcal{WA}}$：

```
.##.
#..#
#..#
.##.
```

~~哈哈哈~~

于是乎先判断。先写一个函数```judge(int x, int y)```，判断以$(x,y)$为左上角的$2 \times 2$方格是否符合条件。

函数如下：

```cpp
bool judge(int x, int y) {
    if (x < 0 or y < 0 or x > 3 or y > 3)
        return false; //越界返回false，后面有用
    return map[x][y] and map[x][y + 1] and map[x + 1][y] and map[x + 1][y + 1] or
        not map[x][y] and not map[x][y + 1] and not map[x + 1][y] and not map[x + 1][y + 1];
}
```

然后先把每一个格子全都judge一遍，一旦返回true就直接输出YES，```return 0```.

第二步，把每一个格子都改变颜色，再judge一遍，**记得把颜色改回来！**（如果judge返回true那么直接YES）

接下来附上蒟蒻的代码（时间复杂度可是$O(1)$哦）

```cpp
#include <cstdio>
using namespace std;

bool map[4][4];

bool judge(int x, int y) {
    if (x < 0 or y < 0 or x > 3 or y > 3)
        return false;
    return map[x][y] and map[x][y + 1] and map[x + 1][y] and map[x + 1][y + 1] or
        not map[x][y] and not map[x][y + 1] and not map[x + 1][y] and not map[x + 1][y + 1];
}

int main() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++)
            map[i][j] = getchar() == '#';
        getchar();
    }
    
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j ++)
            if (judge(i, j)) {
                printf("YES");
                return 0;
            }
    
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j ++) {
            map[i][j] = not map[i][j];
            
            if (judge(i, j) or judge(i - 1, j) or judge(i, j - 1) or judge(i - 1, j - 1)) {
                printf("YES");
                return 0;
            }
            
            map[i][j] = not map[i][j];
        }
    
    printf("NO");
    return 0;
} 
```

---

