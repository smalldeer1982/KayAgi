# Fractal

## 题目描述

分形是在各种尺度上以某种技术意义上显示自相似性的对象或数量。对象不需要在所有尺度上展现完全相同的结构，但在所有尺度上必须出现相同的“类型”结构。

盒子分形定义如下：

- 度为 $1$ 的盒子分形简单地是 X
- 度为 $2$ 的盒子分形是
```
X X
 X
X X
```
- 如果用 $B(n - 1)$ 表示度为 $n - 1$ 的盒子分形，那么度为 $n$ 的盒子分形可以递归地定义如下
```
B(n - 1) B(n - 1)
     B(n - 1)
B(n - 1) B(n - 1)
```
你的任务是绘制度为 $n$ 的盒子分形。

## 样例 #1

### 输入

```
1
2
3 
4 
-1```

### 输出

```
X
-
X X
 X 
X X
-
X X   X X
 X     X 
X X   X X
   X X   
    X    
   X X   
X X   X X
 X     X 
X X   X X
-
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
   X X               X X   
    X                 X    
   X X               X X   
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
         X X   X X         
          X     X          
         X X   X X         
            X X            
             X             
            X X            
         X X   X X         
          X     X          
         X X   X X         
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
   X X               X X   
    X                 X    
   X X               X X   
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
-
```

# 题解

## 作者：sillation (赞：19)

[题目传送门](https://www.luogu.com.cn/problem/P10458)


------------
### 思路：
根据输出样例我们可以知道 $n$ 度的盒分形图为一个长宽为 $3^{n-1}$ 的正方形。

设置递归函数 ${f(n,x,y)}$ 生成以坐标 $x,y$ 为左上角的 $n$ 度盒分形。

1. 递归边界： 若 $n=1$，则在 $x,y$ 输出 $X$。

2. 若 $n > 1$,则计算 $n - 1$ 度的盒子的规模 $m = 3^{n-2}$,分别在左上方，右上方，中间，左下方和右下方 $5$ 个 $n-1$ 度的盒子。

- 对于左上方的 $n-1$ 度的盒子，左上角的坐标为 $x,y$。递归函数为 ${f(n - 1,x + 2m , y)}$。

- 对于右上方的 $n-1$ 度的盒子， 右上方的坐标为 $x + 2m,y$。递归函数为 ${f( n - 1,x + 2m,y)}$。

- 对于中间的 $n-1$ 度的盒子，中间的坐标为 $x + m,y + m$。递归函数为 ${f(n-1,x+m,y+m)}$。

- 对于左下方的 $n-1$ 度的盒子，左下方的坐标为 $x,y+2m$。递归函数为 ${f (n-1,x,y+2m)}$ 。

- 对于右上方的 $n-1$ 度的盒子，右下方的坐标为 $x+2m,y+2m$。递归函数为 ${f(n-1,x+2m,y+2m)}$。


------------
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[730][730];
void f(int n, int x, int y) {
	//递归边界
	if (n == 1) {
		mp[x][y]='X';
	} else {
		int m = pow(3, n - 2);
		//递归5个位置 
		f(n - 1, x, y);
		f(n-1, x+2*m, y);
		f(n - 1, x , y + 2 * m);
		f(n - 1, x + m, y + m);
		f(n-1,x+2*m,y+2*m);
	}
}
int main() {
	int n ;
	while (1) {
		cin >> n;
		if(n==-1) return 0;
		int c=pow(3, n - 1);
		 //初始化
		memset(mp,' ',sizeof(mp));
		f(n, 0, 0);
		for (int i = 0; i < c; i++) {
			for(int j=0; j< c; j++) printf("%c",mp[i][j]);
			cout<<endl;
		}
		cout <<'-'<<endl;
	}
	return 0;
}
```
笔者文风不好，请见谅。

---

## 作者：abc1856896 (赞：4)

# solution
可以发现，第 $n$ 个图形是由 $5$ 个第 $n-1$ 个图形组成的。

其中，右上角的图形的 $x$ 坐标被向右平移了 $3 \times (n-2) \times 2$ 个单位。

同理，左下角的图形的 $y$ 坐标被向右平移了 $3 \times (n-2) \times 2$ 个单位。

而中间的图形的 $x$ 坐标被向右平移了 $3 \times (n-2)$ 个单位，$y$ 坐标被向下平移了 $3 \times (n-2)$ 个单位。

右下角的图形的 $x$ 坐标被向右平移了 $3 \times (n-2) \times 2$ 个单位，$y$ 坐标被向下平移了 $3 \times (n-2) \times 2$ 个单位。

这样一层一层的递归即可。

---

## 作者：huangyuze114514 (赞：2)

# 思路
**算法：递归**

把 $n$ 度的图像分成 $5$ 个单位，分别为：左上，右上，中间，坐下，右下。第 $n$ 度的每个单位即 $n-1$ 度的图像。创建递归函数 $sc(a,b,az)$，表示坐标为 $(a,b)$ 的度数为 $az$ 的图像。当 $az>1$ 时，递归坐标为每个单位的 $az-1$ 度的图像，当 $az = 1$ 时，把 $1$ 度的图像的五个单位全填上 X。

## 每个单位的坐标
我们可以发现 $n$ 度的图像的宽即为 $3^{n-1}$；  
又因为 $n$ 度的图像的宽由 $3$ 个 $n-1$ 度的图像组成；  
那么设变量 $s$，使 `s=pow(3,az-1)/3;` 得出来的数即为 $n-1$ 度的图像的宽度。如果左上的单位的坐标为 `(a,b)`，右上的单位的坐标即为 `(a+(2*s),b)`，中间的单位的坐标即为 `(a+s,b+s)`，左下的单位的坐标即为 `(a,b+(2*s))`，右的下单位的坐标即为 `(a+(2*s),b+(2*s))`。

# 代码如下:
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
char aa[800][800];//最大的图像的宽为七百多，设数组用800
void sc(int a,int b,int az){//递归函数
	int s=pow(3,az-1)/3;//n-1度的图像的宽度
	if(az>1){
		sc(a,b,az-1);//递归左上的单位
		sc(a+(2*s),b,az-1);//递归右上的单位
		sc(a+s,b+s,az-1);//递归中间的单位
		sc(a,b+(2*s),az-1);//递归左下的单位
		sc(a+(2*s),b+(2*s),az-1);//递归右下的单位
	}
	if(az==1){
		aa[a][b]='X';//该单位填充字符X
		return;
	}
}
void co(int a){//输出函数,a表示输出的图像的宽
	for(int i=1;i<=a;i++){
		for(int j=1;j<=a;j++){
			cout<<aa[i][j];
		}
		cout<<endl;//换行
	}
	cout<<'-'<<endl;//输出'-'并换行
}
int main(){
	int z;//指图像的度数
	while(cin>>z){//循环输入
		if(z==-1)return 0;//如果输入的数为-1,结束程序
		memset(aa,' ',sizeof(aa));//使用memset清空数组,使数组内除X外全是空格
		int man=pow(3,z-1);//man表示输出的图像的宽
		sc(1,1,z);//递归函数求解
		co(man);//输出
	}
	return 0;
}
```

---

## 作者：zhoujunchen (赞：1)

根据输出样例我们可以知道 $ n $ 度的盒分形图为一个长宽 $ 3n-1 $ 的正方形。     
递归函数 $ f(x,y,len) $ 生成以坐标 
$ x $ , $ y $ 为左上角的 $ len $ 度盒分形。  

1.递归边界： 若 $ len  = 1 $ ，则在 $ x,y $ 输出 $ X $。  
2.若 $ len > 1 $，则填充5个 $ n−1 $ 度的盒子。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000][1000];//答案数组
void f(int x,int y,int len){//X的横坐标、竖坐标和大小
    if(len==1){a[x][y]='X';return;}
    f(x,y,len/3);//左上
    f(x,y+2*len/3,len/3);//右上
    f(x+len/3,y+len/3,len/3);//中间
    f(x+2*len/3,y,len/3);//左下
    f(x+2*len/3,y+2*len/3,len/3);//右下
}
int main(){    
    int n;
    while(cin>>n){
    	if(n==-1)return 0;//如果是-1就结束程序
    	memset(a,' ',sizeof(a));//清空数组
    	int len=pow(3,n-1);//长度
    	f(1,1,len);//递归
    	for(int i=1;i<=len;i++){//输出
        	for(int j=1;j<=len;j++)cout<<a[i][j];
        	cout<<"\n";
    	}
    	cout<<"-\n";//单个破折号隔开
	}
    return 0;
}
```

---

## 作者：LG086 (赞：1)

### 分析

输入多个整数 $n$，对于每个 $n$，输出一个对应的分形图。


使用递归。每次执行 `draw(x,y,size)`，其中 $x$ 和 $y$ 是指当前字符的坐标，$size$ 代表了此时分形图的大小。  
当 $size=1$ 时，$a_{i,j}$ 就是一个字符 `X`。

那么 $size$ 最大为多少？根据样例，可以得出最大的 $size=3^{n-1}$，分形每降一级，$size$ 就变为 $size \div 3$。

设当前分形图**左上角部分**的坐标为 $x,y$，$size \to size \div 3$ 那么分形图的 $5$ 个部分的坐标就是：  
$x,y$；  
$x+size,y+size$；  
$x,y+2\times size$；  
$x+2\times size,y$；  
$x+2\times size,y+2\times size$。
  

完整的递归代码就是：  
```cpp
void draw(int x,int y,int size){
    if(size==1)
        {a[x][y]='X';return;}
    size/=3;
    draw(x,y,size);
    draw(x,y+2*size,size);
    draw(x+size,y+size,size);
    draw(x+2*size,y,size);
    draw(x+2*size,y+2*size,size);
}
```

接下来，主函数里每次要初始化存分形图的字符数组。算出最大的 $size$ 的大小，从最左上角开始递归。

递归后输出分形图，不忘行末一个 `-`。

------------
### 代码

```cpp
#include"bits/stdc++.h"
using namespace std;

char a[1145][1145]={};
void draw(int x,int y,int size){
    if(size==1)
        {a[x][y]='X';return;}
    size/=3;
    draw(x,y,size);
    draw(x,y+2*size,size);
    draw(x+size,y+size,size);
    draw(x+2*size,y,size);
    draw(x+2*size,y+2*size,size);
}
int n;
signed main(){
    while(cin>>n and n!=-1){
        int l = pow(3,n-1);
        for(int i(0);i<=l;i++)
            for(int j(0);j<=l;j++)
                a[i][j]=' ';
        draw(1,1,l);
        for(int i(1);i<=l;i++)
            {for(int j(1);j<=l;j++)
                cout<<a[i][j];
            cout<<"\n";}
        cout<<"-\n";
    }
}
```

---

## 作者：GoodLuckCat (赞：1)

递归好题 ~~，但是我用的循环预处理~~。

因为输出中只含有 `X`，`-`，还有空格和换行的字符，而 `-` 和换行都是可以在 `main` 函数里面直接输出的，存储分形图案时只有 `X` 和 ` ` 两种字符，为了节省空间，我使用 `bool` 类型的、大小为 $2188\times2188$ 的数组。具体为什么是 $2188$，是因为找规律发现每次输出图案的“边长”都比前一个“等级”多两倍，而题目中 $n\le7$，所以数组的大小应为 $3^7+1=2188$。

然后我的思路是先计算出左上角的图案，然后再“复制”过去，就成了分形图案。因为每次输入都计算会超时，所以我们应该先预处理出图案，输入数据时直接输出图案即可。注意事项没啥好说的，就是每组数据输出后要有一个减号（不知道为啥翻译写的是破折号，不过看样例应该都知道了吧）

代码如下：

```cpp
//Made in China
#include<iostream>
using namespace std;
bool a[2188][2188];
void copy(int t)
{
    for(int i=2*t+1;i<=3*t;i++)for(int j=1;j<=t;j++)a[i][j]=a[i-2*t][j];
    for(int i=t+1;i<=2*t;i++)for(int j=t+1;j<=2*t;j++)a[i][j]=a[i-t][j-t];
    for(int i=1;i<=t;i++)for(int j=2*t+1;j<=3*t;j++)a[i][j]=a[i][j-2*t];
    for(int i=2*t+1;i<=3*t;i++)for(int j=2*t+1;j<=3*t;j++)a[i][j]=a[i-2*t][j-2*t];
}
int main()
{
    int n,s=1;
    a[1][1]=1;
    for(int i=1;i<=7;i++)copy(s),s*=3;
    while(1)
    {
        cin>>n;
        if(n==-1)return 0;
        n--;
        s=1;
        while(n--)s*=3;
        for(int i=1;i<=s;i++)
        {
            for(int j=1;j<=s;j++)cout<<(a[i][j]?'X':' ');
            cout<<'\n';
        }
        cout<<"-\n";
    }
    return 0;
}
```

AC 记录：[$783B$，$150ms$，$5MB$](https://www.luogu.com.cn/record/159494692)。

---

## 作者：Happy_mouse (赞：1)

# [P10458 Fractal](https://www.luogu.com.cn/problem/P10458) 题解
[AC证明](https://www.luogu.com.cn/record/161715712)

~~什么玩意儿啊，才普及。~~

## 看完题目，分析一下：
首先，这是一道妥妥的递归——$5$ 个度数低的排布得到 $1$ 个高一度的。

其次，细节上：

1. 递归出口为度数为 $1$ 时，该位置为 $X$；
2. 递归内部输出不好操作，放入 $a$ 数组，递归结束后再输出；
3. 每次输入，$a$ 数组都要初始化一遍；
4. $3$ 的幂次需预处理，否则容易超时（[血的教训啊](https://www.luogu.com.cn/record/161715374)）。

## 递归部分
```c
// bool 或 char a数组，存输出
// int mc数组，存3的幂次（需预处理）
void dg(int n,int x,int y){//度数与左上角坐标
	//递归出口 
	if(n==1){
		a[x][y]=1;//如果是 char 数组就是‘a[x][y]='X';’
		return ;
	}
	//降度，分各个区域。
	int c=mc[n-2];//大的图形分为九宫格区域，只有下面五个区域内有图案，c为每宫格的边长。
	dg(n-1,x,y);//左上角区域
	dg(n-1,x+c*2,y);//右上角区域
	dg(n-1,x+c,y+c);//中间区域
	dg(n-1,x,y+c*2);//左下角区域
	dg(n-1,x+c*2,y+c*2);//右下角区域
}
```
为防止抄袭，就不放完整代码了欧。

---

## 作者：_dbq_ (赞：0)

## 前言
还没有读题的同学们可以点击[这里](https://www.luogu.com.cn/problem/P10458)先读题。

## 思路
所输出的答案是可以分解成许多结构一样的小图形，因此考虑递归。

我们所要考虑的主要问题是每一个小图形放在哪里。我们发现每一个图形的长宽相等，因此为正方形。我们定义 $a_i$ 为 $n=i$ 时答案的边长，我们发现 $a_i=a_{i-1}\times3$ 且 $a_1=1$，这样就可以算出每一个图形的边长，小图形放的位置我们也可以表示出来了。

## 代码
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
bool c[3000][3000];//存我们构造的图形
int a[10];//图形的边长
inline auto read(){//快读
    auto x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(cint n,cint x,cint y)//递归函数
{
    //n表示构造度为n的图形
    //x,y表示图形的起始位置
    if(n==1)//度为1的图形就是X
    {
        c[x][y]=true;
        return ;
    }
    else
    {
        //整个图形有五部分，可以用上文中的方法表示出起始点
        solve(n-1,x,y);
        solve(n-1,x,y+2*a[n-1]);
        solve(n-1,x+a[n-1],y+a[n-1]);
        solve(n-1,x+2*a[n-1],y);
        solve(n-1,x+2*a[n-1],y+2*a[n-1]);
    }
}
int main()
{
    #ifdef dbq
    freopen("P10458.in","r",stdin);
    freopen("P10458.out","w",stdout);
    #endif
    a[1]=1;//度为1的图形边长为1
    for(int i=2;i<=7;i++)//预处理a
        a[i]=a[i-1]*3;
    while(1)
    {
        cint n=read();
        if(n==-1) return 0;
        solve(n,1,1);//构造度为n的图形，从(1,1)开始构造
        for(int i=1;i<=a[n];i++)
        {
            for(int j=1;j<=a[n];j++)
            {
                if(c[i][j]==true) putchar('X');//输出
                else putchar(' ');
            }
            putchar('\n');
        }
        //用putchar会更快
        //不用putchar且开O2的情况下，总用时：172ms
        //加了putchar且开O2的情况下，总用时：31ms
        cout<<"-"<<'\n';//别忘了输出破折号
    }
    return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10458)
## 解题思路
递归。

- 如果递归层数 $n$ 为 $1$，记录，$a_{l,r}\gets 1$；
- 否则，递归五次，分别是：（$x$ 为当前宽度）
	- 左上角，$l$ 和 $r$ 不变，就是 $l,r$；
   - 右上角，$r$ 要加两个 $\dfrac{x}{3}$，就是 $l,r+\dfrac{2}{3}x$；
	- 中间，$l,r$ 都要加一个 $\dfrac{x}{3}$，就是 $l+\dfrac{1}{3}x,r+\dfrac{1}{3}x$；
	- 左下角，$l$ 要加两个 $\dfrac{x}{3}$，就是 $l+\dfrac{2}{3}x,r$；
	- 右下角，$l,r$ 都要加两个 $\dfrac{x}{3}$，就是 $l+\dfrac{2}{3}x,r+\dfrac{2}{3}x$；
    
最后，输出，当 $a_{l,r}=1$ 时，输出 `X`，否则输出空格。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool a[2200][2200];//pow(3,7)=2187
void dg(int n,int l,int r,int x)
{
	if(n==1)a[l][r]=1;
	else
	{
		dg(n-1,l,r,x/3);
		dg(n-1,l,r+x/3*2,x/3);
		dg(n-1,l+x/3,r+x/3,x/3);
		dg(n-1,l+x/3*2,r,x/3);
		dg(n-1,l+x/3*2,r+x/3*2,x/3);
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(cin>>n)
	{
		memset(a,0,sizeof a);
		if(n==-1)break;
		int now=pow(3,n-1);
		dg(n,1,1,now);
		for(int i=1;i<=now;i++)
		{
			for(int j=1;j<=now;j++)
				cout<<(a[i][j]?'X':' ');
			cout<<'\n';
		}
		cout<<"-\n";
	}
	return 0;
}

```

---

