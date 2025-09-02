# Rotate, Flip and Zoom

## 题目描述

Polycarp is writing the prototype of a graphic editor. He has already made up his mind that the basic image transformations in his editor will be: rotate the image 90 degrees clockwise, flip the image horizontally (symmetry relative to the vertical line, that is, the right part of the image moves to the left, and vice versa) and zooming on the image. He is sure that that there is a large number of transformations that can be expressed through these three.

He has recently stopped implementing all three transformations for monochrome images. To test this feature, he asked you to write a code that will consecutively perform three actions with a monochrome image: first it will rotate the image 90 degrees clockwise, then it will flip the image horizontally and finally, it will zoom in twice on the image (that is, it will double all the linear sizes).

Implement this feature to help Polycarp test his editor.

## 样例 #1

### 输入

```
3 2
.*.
.*.
```

### 输出

```
....
....
****
****
....
....
```

## 样例 #2

### 输入

```
9 20
**.......
****.....
******...
*******..
..******.
....****.
......***
*.....***
*********
*********
*********
*********
....**...
...****..
..******.
.********
****..***
***...***
**.....**
*.......*
```

### 输出

```
********......**********........********
********......**********........********
********........********......********..
********........********......********..
..********......********....********....
..********......********....********....
..********......********..********......
..********......********..********......
....********....****************........
....********....****************........
....********....****************........
....********....****************........
......******************..**********....
......******************..**********....
........****************....**********..
........****************....**********..
............************......**********
............************......**********
```

# 题解

## 作者：ResidualNight (赞：7)

相对于前一篇题解，个人觉得我这份要容易理解一些

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h;
char a[1000][1000];
int main()
{
    cin>>w>>h; //读入数据
    for(int i=1; i<=h; i++)
        for(int k=1; k<=w; k++)
            cin>>a[i][k];
    for(int i=1; i<=w; i++)
    {
        for(int j=1; j<=2; j++)
        {
            for(int k=1; k<=h; k++)
            {
                cout<<a[k][i]<<a[k][i];//把一列的字符打出，乘两倍放大
            }
            cout<<endl; //回车
        }
    }
    return 0;//完美结束
}
```

---

## 作者：PC_DOS (赞：1)

这是一道字符串模拟题，请注意，旋转、翻转、缩放这三个过程是可以互相调换位置的。

观察样例可以发现，如果我们按照列从上到下遍历字符串，那么得到的就是顺时针旋转了90度并水平翻转的图像。接下来我们需要考虑放大的问题，可以发现，所谓放大两倍事实上就是一个字符变成了田字形排列的4个同样的字符(口 -> 田)，因此我们只需要在遍历列时，每个字符添加两遍，每列输出两遍就可以了。

代码:
```
#include <iostream>
#include <string>
#include <vector>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput; //输入和输出的缓冲
	vector<string> arrInput; //存放输入的字符串
	int iHeight, iLength; //iHeight-字符串个数；iLength-长度
	register int i,j; //循环计数器
	cin >> iLength >> iHeight; //读入长度和个数
	for (i = 1; i <= iHeight; ++i){ //读入字符串
		cin >> sInput; //读入串
		arrInput.push_back(sInput); //放入数组
	}
	for (i = 0; i < iLength; ++i){ //纵向遍历并输出
		sInput = ""; //清空缓冲区
		for (j = 0; j < iHeight; ++j){ //遍历列
			sInput += arrInput[j][i]; 
			sInput += arrInput[j][i]; //每个字符添加两遍
		}
		cout << sInput << endl << sInput<<endl; //每一列数出两遍，别忘了换行
	}
	return 0;
}
```

---

## 作者：woai__Accepted (赞：0)

## 题目描述

给定一个字符矩阵，把矩阵顺时针旋转 $90$ 度，再放大两倍输出。

## 解题思路

要将原矩阵 $A$ 顺时针旋转 $90$ 度变成矩阵 $B$，可以把原矩阵 $A$ 的行数变成矩阵 $B$ 的列数，$A$ 的列数变成 $B$ 的行数，所以把输入的双重循环的内外循环调换一下再放大两倍就完成了。

**代码实现**

```cpp
f(i,1,w){
	int now=1;
	while(now<=2){//放大2倍
		f(j,1,h) printf("%c%c",s[j][i],s[j][i]);
		cout<<endl;
		now++;
	}
}
```
## 完整 $\texttt{AC}$ 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=105;
int w,h;
char s[maxn<<1][maxn<<1];
#define f(i,a,b) for(int i=a;i<=b;i++)
int main(){
	scanf("%d%d",&w,&h);
	f(i,1,h) f(j,1,w) cin>>s[i][j];
	f(i,1,w){
		int now=1;
		while(now<=2){
			f(j,1,h) printf("%c%c",s[j][i],s[j][i]);
			cout<<endl;
			now++;
		}
	}
	return 0;
}
```


---

## 作者：LYqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF523A)

# 题目大意

给定一个字符矩阵，将其顺时针旋转 $90^{\circ}$，水平翻转并放大两倍后的矩阵。

# 思路

先不管题目咋说的，来照着样例找规律。

输入：

```
3 2
.*.
.*.
```

输出：

```
....
....
****
****
....
....
```

可以发现，我们可以一列一列遍历矩阵，每一个字符输出两次，输出完一列后再输出一边刚刚输出的东西，就可以得到答案了。

再尝试模拟一下样例 $2$，发现也是如此。

# 代码

```cpp
#include <iostream>
using namespace std;
const int N=1e2+5;
int n,m;
char a[N][N];

int main(){
    cin >> m >> n; // 先输入的是列数，后输入的是行数
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> a[i][j];
        }
    }
    for(int i=1; i<=m; i++){
        for(int j=1; j<=2; j++){
            for(int k=1; k<=n; k++){
                cout << a[k][i] << a[k][i];
            }
            puts("");
        }
    }
    return 0;
}
```



---

## 作者：Noby_Glds (赞：0)

最优解前来报到！

经过我的找规律，发现输出的结果只是把横坐标和纵坐标调换，然后放大两倍输出而已。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[110][110];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) cin>>a[j][i];   //把横，纵坐标换过来输入。
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<a[i][j]<<a[i][j];    //保证纵列两倍输出。
		cout<<endl;
		for(int j=1;j<=m;j++) cout<<a[i][j]<<a[i][j];
		cout<<endl;
	}   //两个for循环保证横排两倍输出。
    return 0;
}
```
代码简单易懂。

---

## 作者：thomas_zjl (赞：0)

~~这道题别被样例吓到啊~~

这道题分$3$步。

1. 把这个矩形顺时针旋转$90$°。
1. 把这个矩形水平翻转。
1. 放大$2$倍。

让我们一步一步来分析一下吧。

第$1$步+第$2$步可以连用。
特地写了个代码。
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    char a[m][n];
    for(int i=0;i<m;i++)//原本应该是i<n,应改成i<m。
    {
    	for(int j=0;j<n;j++)//原本应该是i<m,应改成i<n。
    	{
    		cin>>a[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cout<<a[j][i];//按原顺序输出。
		} 
		cout<<endl; //换行。
	}
    return 0;
}
```
第$3$步更加简单。

输出$2$次就可以了。

重点来看看输出部分的代码吧。

```
for(int i=0;i<n;i++)
{
	for(int j=0;j<2;j++)//竖的一列要2倍输出。
	{
		for(int k=0;k<m;k++)
		{
			cout<<a[k][i]<<a[k][i];//横的一列也是2倍输出。
		} 
		cout<<endl; 
	}
}
```
代码分步讲完了，就贴一下代码吧（不加注释）。
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	char a[m][n];
	for(int i=0;i<m;i++)//原本应该是i<n,应改成i<m。
	{
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];//原本应该是i<m,应改成i<n。
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<2;j++)//2倍输出竖的一列的图形
		{
			for(int k=0;k<m;k++)
			{
				cout<<a[k][i]<<a[k][i];//2倍输出横的一列的图形。
			} 
			cout<<endl;//换行。
		}
	}
	return 0;
}
```


---

## 作者：RBI_GL (赞：0)

**题目要求：**

输入一个矩形，输出它顺时针旋转90度，然后水平翻转，最后放大两倍的图像

**要求实现：**

1.“顺时针旋转90度，然后水平翻转”的操作**只要控制内外循环顺序即可实现。**

2.“放大两倍”**只要输出两遍即可。**

----

**Code:**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
char a[105][105];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	 for(int j=1;j<=n;j++)
	    cin>>a[i][j];  //读入数据
	for(int i=1;i<=n;i++)
		for(int w=1;w<=2;w++)
		{
		    for(int j=1;j<=m;j++)   //调整内外循环变量来实现：顺时针旋转90度，然后水平翻转 
		    {
			cout<<a[j][i]<<a[j][i];   //放大两倍输出 
		    }
		    cout<<endl;  //换行，注意这行代码放的位置  
		}
	return 0;
} 
```






---

## 作者：AlwaysForward (赞：0)

代码可能是最短的了……

思路：输入后反转，输出时将字符输出两次，每行输出两次。

注：

1.不可使用 $string$ 类型，最好使用 $char$ ,因为 $string$ 会将一行视为一个字符串

2.题目的 $m$ ，$n$ 给的是反的，输入时要反过来

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int m,n,i,j,k;
	cin>>n>>m;
	char a[m+1][n+1];
	for(i=1;i<=m;i++)
	   for(j=1;j<=n;j++)
	      cin>>a[i][j];
	for(i=1;i<=n;i++)
		for(k=1;k<=2;k++){
		    for(j=1;j<=m;j++)
			    cout<<a[j][i]<<a[j][i];
		    cout<<endl;
		}
} 
```


---

## 作者：luosw (赞：0)

### 题意简述

观察样例我们可以得到我们要做的是：

- 将输入的长方形旋转$90^o$后放大$2$倍输出。

好，题意真是言简意赅，开始分析。

---

### 题目分析

看到这道题，我们就想到：要定义两个$char$型的二维数组，一个用于输入，一个用于输出，输入后进行一系列的变换就可以了，这里变换最重要的就是旋转90°和放大2倍，这一串代码就非常重要了。

```cpp
b[2*j][2*i]=b[2*j][2*i+1]=b[2*j+1][2*i]=b[2*j+1][2*i+1]=a[i][j];
```
上述代码就是一个变换的过程，把$a$数组的数字按照要求赋值到$b$数组，就不用建立$tmp$来进行交换了

---

### $Code$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include <map>
#include <queue>
using namespace std;
 
 
//523A
int n,m;
char a[100][100];	//一个输入
char b[200][200];	//一个输出
 
int main()
{
while(true)		//永远循环
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>a[i][j];
            b[2*j][2*i]=b[2*j][2*i+1]=b[2*j+1][2*i]=b[2*j+1][2*i+1]=a[i][j];	//变换（特别重要）
        }
 
    }
 
    for(int i=0;i<=2*n-1;i++)
    {
        for(int j=0;j<=2*m-1;j++)
        {
            cout<<b[i][j];
        }
        cout<<endl;	//输出
    }
 
 
 
}
    return 0;
}

```

请勿抄袭！！！

---

## 作者：BearBig (赞：0)

### 题目分析
水题一道。题解没有发满，我来一波。    
这道题，给你两个整数 $w$，$h$，现在要求把它顺时针旋转 90 度，水平翻转，并且将矩形扩大两倍输出。
### 样例分析
样例输入：
```cpp
3 2 
.*.
.*.
```
* 第一步，顺时针旋转 90 度，变成了
```cpp
..
**
..
```
* 第二步，水平翻转。
```cpp
..
..
**
```
* 第三步，扩大二倍输出。
```cpp
....
....
****
****
....
....
```
### 思路分析
首先输入两个整数 $w$，$h$
```python
w,h=input().split()
w,h=int(w),int(h)
```
接下来声明一个二维列表 $pat$，用来存储图形。并且输入图形。
```python
eha=w 
#注意，这一条语句是将 w 的值存储起来，后面有用。
pat=[]
while w:
		w=w-1
        ds=input().split('')
        pat.append(ds)
```
然后就是循环输出！
```python
for i in range(1,eha+1):
		for j in range(1,3):
        	for k in range(1,1+h):
            	print("{ar}{ar}".format(ar=a[k][i]))
```
### 代码展示
根据以上步骤，无注释代码如下。
```python
w,h=input().split()
w,h=int(w),int(h)
eha=w 
pat=[]
while w:
		w=w-1
        ds=input().split('')
        pat.append(ds)
for i in range(1,eha+1):
		for j in range(1,3):
        	for k in range(1,1+h):
            	print("{ar}{ar}".format(ar=a[k][i]))
```
**珍爱生命，远离抄袭！**

---

