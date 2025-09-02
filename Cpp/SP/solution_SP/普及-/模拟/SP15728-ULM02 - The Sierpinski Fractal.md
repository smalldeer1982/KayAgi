# ULM02 - The Sierpinski Fractal

## 题目描述

Consider a regular triangular area, divide it into four equal triangles of half height and remove the one in the middle. Apply the same operation recursively to each of the three remaining triangles. If we repeated this procedure infinite times, we'd obtain something with an area of zero. The fractal that evolves this way is called the Sierpinski Triangle. Although its topological dimension is _2_, its Hausdorff-Besicovitch dimension is_log(3)/log(2)~1.58_, a fractional value (that's why it is called a fractal). By the way, the Hausdorff-Besicovitch dimension of the Norwegian coast is approximately _1.52_, its topological dimension being _1_.

For this problem, you are to outline the Sierpinski Triangle up to a certain recursion depth, using just ASCII characters. Since the drawing resolution is thus fixed, you'll need to grow the picture appropriately. Draw the smallest triangle (that is not divided any further) with two slashes, to backslashes and two underscores like this:

 /\\

# 题解

## 作者：wjk2020 (赞：2)

~~不就是南蛮图腾吗……~~

$len[x] $表示询问为x时的答案有几行。 有递推式： $len[x] = len[x - 1] * 2$

递归分形裸题（分治）。设初始图形(k = 1)为：
```cpp
   " /\ "
   "/__\"
```
则有接下来的 k > 1 ： 对于k而言， $len[k]$ 前 $len[k - 1]$ 行由 $ans[k - 1]$ 加上一些空格组成的， 而这些空格的数目就是 $2^{(k-1)}$
 。只需要在每行回溯更新答案的过程中在前后加入空格即可。对于后 $len[k - 1]$ 行，只需要复制两次 $ans[k - 1]$ 就行了。
 ```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int n;
string ans[15][1000];
int len[15];
void cacl(int k) {
    if(k == 1) {
        len[k] = 2;
        ans[k][1] = " /\\ ";
        ans[k][2] = "/__\\";
        return;
    }
    cacl(k - 1);
    len[k] = len[k - 1] * 2;
    for(int i = 1; i <= len[k - 1]; i++) {
        for(int j = 1; j <= (1 << (k - 1)); j++) ans[k][i] = ' ' + ans[k][i];
        ans[k][i] = ans[k][i] + ans[k - 1][i];
        for(int j = 1; j <= (1 << (k - 1)); j++) ans[k][i] = ans[k][i] + ' ';
    }
    for(int i = len[k - 1] + 1; i <= 2 * len[k - 1]; i++) {
        ans[k][i] = ans[k - 1][i - len[k - 1]];
    }
    for(int i = len[k - 1] + 1; i <= 2 * len[k - 1]; i++) {
        ans[k][i] = ans[k][i] + ans[k - 1][i - len[k - 1]];
    }
}
int main() {
    cin >> n;
    cacl(n);
    for(int i = 1; i <= len[n]; i++) {
        cout << ans[n][i] << endl;
    }
    return 0;
}
```


---

## 作者：konyakest (赞：2)

~~用Python水个题解~~

## 讲解

首先，这题很经典的递归，具体想法是：

- 对于递归函数 $ fx $ ，传入三个参数，分别为大小（此处的大小，我用行数\*2表示）和位置

- 对于 $ fx(a,x,y) $ ，如果a为1，则直接上色，否则递归

- 最后输出图形即可(^_^)

## 代码

```python
one=[[' ','/','\\',' '],['/','_','_','\\']]#单个图形打表，便于赋值
ans=[['1' for i in range(1025)] for j in range(1025)]#创建全为1的1024*1024图形
def fx(a,x,y):
    if a==1:
        for i in range(0,2):
            for j in range(0,4):
                ans[i+x][j+y]=one[i][j]
        return
    #最小情况，进行赋值
    '''
下面的递归比较难理解，我们以例子说明：
   /\   
  /__\  
 /\  /\ 
/__\/__\
首先，上方的坐标（即图形最左上角的点）为第1行第3列，
可以发现，第几行就是大图形的x，而第几列为y+a（此时a为2）
而左下角的坐标为第x+a行，第y列；
右下角的坐标为第x+a行，第y+a*2列；
    '''

    fx(a//2,x,y+a)
    fx(a//2,a+x,y)
    fx(a//2,a+x,y+a*2)
    #递归
n=0
while True:
    n=int(input())
    if n==0:break
    n=1<<(n-1)#将n转换成行数/2
    fx(n,1,1);#进行操作
    for i in range(1,n*2+1):
        for j in range(1,n*4+1):#循环输出
            if ans[i][j]=='1':
                print(' ',end='')#如果没变，输出空格
            else:
                print(ans[i][j],end='')#输出图形
        print('')#换行

```


---

## 作者：zeekliu (赞：1)

这道题是一个很经典的递归，打印图形系列题之一。

我们设 $ n $ 为当前图形的分型次数。

我们观察到样例：$ n=1 $ 时，图形如下：

```
 /\
/__\
```
再看 $ n=2 $ 时：
```
   /\   
  /__\  
 /\  /\ 
/__\/__\
```
$ n=3 $ 时：
```
       /\       
      /__\      
     /\  /\     
    /__\/__\    
   /\      /\   
  /__\    /__\  
 /\  /\  /\  /\ 
/__\/__\/__\/__\
```

很明显：第 $ n $ 次分型均为第 $ n-1 $ 分型的图形堆叠 3 次。

因此，考虑递归。

---

由于上方三角形在上方的中间，所以相对原来的三角，仅列改变为 $ c+2^{n-1} $。

左边三角形由于位于下方偏左，所以行改变为 $ r+2^{n-1} $，列不变。

右边三角形行与列均有改变，为：$ (r+2^{n-1},c+2^{n}) $ 。

---

所以，可得一下结论：

对于上面的三角，它的每个字符的位置在： $ (r,c+2^{n-1}) $

对于左面的三角，它的每个字符的位置在： $ (r+2^{n-1},c) $

对于右面的三角，它的每个字符的位置在： $ (r+2^{n-1},c+2^{n}) $

其中：$ r $ 和 $ c $ 表示 $ n-1 $ 三角形的每个字符的位置（ $ r $ =row 行，$ c $ = column 列，为方便各位阅读，先行再列），$ n $ 为当前图形的分型次数。

---

因此每次只需按位将数据从 $ n-1 $ 次图形拷贝至 $ n $ 次图形即可。

所以下面愉快递归，上代码： 

```cpp

#include <bits/stdc++.h>
using namespace std;
char a[11][3001][3001]; //存储每个的情况数，开这么大空间差不多了
int ro,co; 
  
void make(int n) //r,c为开始打印的位置
{
    int p=pow(2,n-1),q=pow(2,n-2),r=pow(2,n);
    for (int i=1;i<=p;i++)
        for (int j=1;j<=r;j++)
            a[n][i][j+p]=a[n-1][i][j]; //上方三角形
    for (int i=1;i<=p;i++)
        for (int j=1;j<=r;j++)
            a[n][i+p][j]=a[n-1][i][j]; //左面三角形
    for (int i=1;i<=p;i++)
        for (int j=1;j<=r;j++)
            a[n][i+p][j+r]=a[n-1][i][j]; //右面三角形
      
    return;
}
  
int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    for (int i=1;i<=10;i++)
        for (int j=1;j<=2500;j++)
            for (int k=1;k<=2500;k++)
                a[i][j][k]=' ';
    a[1][1][2]='/';a[1][1][3]=92;
    a[1][2][1]='/';a[1][2][2]='_';a[1][2][3]='_';a[1][2][4]=92; // n=1 的方案，用于后面的递归
    for (int i=2;i<=10;i++)
    {
        make(i); //预处理生成图案
    }
    while (cin>>n)
    {
        if (n==0) exit(0); // n=0 时退出
        for (int i=1;i<=pow(2,n);i++) 
        { //直接打印
            for (int j=1;j<=pow(2,n+1);j++)
                cout<<a[n][i][j];
            cout<<endl; //别忘了要换行!
        }
    }
    return 0;
}

```

\* : 注意：为防止转义字符（即' \ '）造成不必要的麻烦（因为 \ ' 有其他含义），此处赋值使用 ASCII 92 代替。

---

## 作者：jxbe6666 (赞：1)

吐槽一下这道题的输入格式，洛谷里翻译的与原来的截然不同，原意如下↓：

输入包含多个测试用例。每个都由整数 $n$ 指定。输入终止于 $n=0$。否则，$1≤n≤10$ 表示递归深度。

 下图是 SPOJ 上的输入输出样例 ↓ ：
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/nkd16wm6.png)
 
  如果你做过 [P1498 南蛮图腾](https://www.luogu.com.cn/problem/P1498)，就会对此题十分熟悉，~~（你完全可以把代码修改一下，直接上传）~~。而对于没做过此题的人也可以欣赏接下来的方法，非常容易 AC 。
  

------------

  ### 思路：
  只需采用分治的方法，每次向下复制一次，向右复制一次，再向上复制一次。
  
  原来 ↓：
  ```cpp
     /\
    /__\
   /\  /\
/__\/__\
```
向下和向右 ↓：
```cpp
   /\      /\
  /__\    /__\
 /\  /\  /\  /\
/__\/__\/__\/__\

```
最后一次向上 ↓：
```cpp
       /\
      /__\
     /\  /\
    /__\/__\
   /\      /\
  /__\    /__\
 /\  /\  /\  /\
/__\/__\/__\/__\

```
这样就 OK 了，废话不多说，直接上代码，代码里还有更多注意事项。
###### 坑点：c++ 中 \ 是转义字符，要打 \\\ 才可以。

------------
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
using namespace std;
int n = 1;
char a[3000][3000]; //开大亿点点
int h = 2, w = 4;   // h是高,w是宽
int main()
{
    while (n != 0)
    {
        h = 2,
        w = 4; // 记得初始化
        cin >> n;
        if (n == 0)
        {
            I AK IOI //数据为0时直接退出
        }
        memset(a, ' ', sizeof(a)); //全部初始化为空格
        a[1][1] = a[1][4] = ' ';
        a[1][2] = a[2][1] = '/';
        a[1][3] = a[2][4] = '\\'; // '\'是转义符，所以要'\\'才会是'\'
        a[2][2] = a[2][3] = '_';
        for (int i = 1; i < n; i++)
        {
            //向下和向右
            for (int j = 1; j <= h; j++)
            {
                for (int k = 1; k <= w; k++)
                {
                    a[j + h][k] = a[j + h][k + w] = a[j][k];
                    a[j][k] = ' '; //把上面的清掉
                }
            }
            //向上
            for (int j = 1; j <= h; j++)
            {
                for (int k = 1; k <= w; k++)
                {
                    a[j][k + w / 2] = a[j + h][k];
                }
            }
            w *= 2, h *= 2;
            //刷新完成一次
        }
        for (int i = 1; i <= h; i++)
        {
            for (int j = 1; j <= w; j++)
            {
                cout << a[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    I AK IOI
}

```



  

---

## 作者：jinyijiang (赞：1)

这道题中等难度，如果大家做过南蛮图腾，~~可以直接复制~~
（逃

----
首先，n=1时

	 /\
   	/__\
n=2时：
		
        /\
       /__\
      /\  /\
     /__\/__\
不就是一个分治嘛

-----
思路：

	     1.这道题一个想法是倒着赋值

         2.n=1时要自己赋值

好的，直接上代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include<cstring>
using namespace std;
const int N=3000; 
int n;
char c[N+100][N+100];   //开大点
void t_time(int &h)     //其实就是平移三次，不过位置要注意，不要像本蒟蒻一样搞一个错位的三角形来
{
	int k=1;
	while(k<n)
	{
		for(int i=0;i<h/2;i++)
		{
			for(int j=h;j<2*h;j++)
			{
				c[i][j]=c[i][j-h];
			}
		}
		for(int i=h/2;i<h;i++)
		{
			for(int j=h/2;j<h/2*3;j++)
			{
				c[i][j]=c[i-h/2][j-h/2];
			}
		}
		h*=2;
		k++;
	}
}
void tuteng()
{
	int h=4;
	c[0][0]=c[1][1]='/';
	c[0][1]=c[0][2]='_';
	c[0][3]=c[1][2]='\\';   //C++中'\'是转义字符，要写'\\' 才是真正的 \
	t_time(h);
	for(int i=h/2-1;i>=0;i--)   //逆序输出，i的值很重要
	{
		for(int j=0;j<h;j++)   
		{
			cout<<c[i][j];
		}
		cout<<endl;
	}
}
int main()
{
    while(cin>>n && n)  //当n!=0就输入
    {
        memset(c,' ',sizeof(c));  //全设为空格，不然会。。。。。。
        tuteng();  
    }
    return 0;
}
```

最后，这是蒟蒻第一次写题解，求给过！

**不过，抄题解确实不是好习惯。**

---

## 作者：DengDuck (赞：0)

事实上，本题可以用异或杨辉三角完成，可以查看大佬在南蛮图腾留下的题解 [This](https://www.luogu.com.cn/blog/treer/solution-p1498)

本篇题解事实上与该题解做法无异，由衷感谢大佬提供做法

异或杨辉三角公式

$$
a_{i,j}=a_{i-1,j} \oplus a_{i-1,j-1}  
$$

---

P.S：南蛮图腾指题面中的三角形

证明异或杨辉三角 就是南蛮图腾

首先异或杨辉三角可以构成一级南蛮图腾

设 $n-1$ 级南蛮图腾可以构成，只要证明出 $n$ 级南蛮图腾可以构成,就证明了异或杨辉三角 就是南蛮图腾

第 $2^{n-1}$ 层 应该是 $2^n$ 个 $1$

第 $2^{n-1}+1$ 层 应该是 $1\;0\;1\;0\;0\;0...0\;0\; 0\;1\;0\;1$

由于中间留了足够的 $0$ ，所以下面又成了两个 $n-1$ 级南蛮图腾

中间都是 $0$ ，往下不断缩小，形成题目要求的倒三角

所以 $n$ 级南蛮图腾可以构成,证毕

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[114514];
int main()
{
	while(cin>>n && n)
	{
		memset(a,0,sizeof(a));
		a[1]=1;
	    for(int i=0;i<(1<<n);i++)
		{
	        for(int j=1;j<=(1<<n)-i-1;j++)
			{
				cout<<" ";
			}
			for(int j=i+1;j>=1;j--)
			{
				a[j]=a[j-1]^a[j];
			}
			if(!(i&1))
			{
				for(int j=1;j<=i+1;j++)
				{
					cout<<(a[j]?"/\\":"  ");
				}
			}
			else 
			{
				for(int j=1;j<=i+1;j+=2)
				{
					cout<<(a[j]?"/__\\":"    ");
				}
			}
			cout<<endl;
	    }		
	}
}
```

---

## 作者：xieyikai2333 (赞：0)

# 递归~~水~~题

- [题目传送门](https://www.luogu.com.cn/problem/SP15728)

---

- 由样例可知，输出的 $n$ 阶三角形是由 $3$ 个 $n-1$ 阶的三角形组成的。

例如：

```
1 阶
 /\ 
/__\

```

```
2 阶
   /\   
  /__\  
 /\  /\ 
/__\/__\

```

```
3 阶
       /\       
      /__\      
     /\  /\     
    /__\/__\    
   /\      /\   
  /__\    /__\  
 /\  /\  /\  /\ 
/__\/__\/__\/__\

```

很容易想到递归算法。一直将大三角形分成 $3$ 个小三角形，直到分成若干 $1$ 阶三角形为止后输出即可。

不多说了，上代码！！！

---

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[10005][10005];
void T(int x,int y,int step)
{
	if(step==1)
	{
		a[x][y+1]='/';
		a[x][y+2]='\\';
		a[x+1][y]='/';
		a[x+1][y+1]='_';
		a[x+1][y+2]='_';
		a[x+1][y+3]='\\';
		return;
	}
	int tmp=(1<<(step-1));
	T(x,y+tmp,step-1);
	T(x+tmp,y,step-1);
	T(x+tmp,y+2*tmp,step-1);
	return;
}
int main()
{
	int n; 
	while(cin>>n&&n!=0)
	{
		T(1,1,n);
		int k=(1<<n);
		for(int i=1;i<=k;i++)
		{
			for(int j=1;j<=2*k;j++)
			{
				if(a[i][j]!=0)printf("%c",a[i][j]);
				else printf(" ");
			}
			printf("\n");
		}
		printf("\n");
		memset(a,0,sizeof(a));
	}
	return 0;
}
```

---

附上 [AC记录](https://www.luogu.com.cn/record/57481082)

---

## 作者：胡金梁 (赞：0)

本题可见[南蛮图腾](https://www.luogu.com.cn/problem/P1498)

其实这两题各个方面都是一样的。可以把整体分成上、左下、右下三个部分，而每个部分又能分成三个部分。总共能分成 $3^{(n-1)}$ 个部分，输出的三角形底是 $2^{(n+1)}$ ，高是 $2^n$ ，这两个数量可以用位运算。递归时要注意边界，当当前的部分是三角形时，就把字符填入当中，否则就继续分。下面是我的代码，供大家参考：
```cpp
#include<bits/stdc++.h>
int n;
char a[3000+5][3000+5];
const char CX='/',CY='\\',CZ='_';//借鉴了其他大佬
void digui(int s,int sx,int sy)
{
    if(s==1)
    {
        a[sx][sy+1]=CX;
        a[sx][sy+2]=CY;
        a[sx+1][sy]=CX;
        a[sx+1][sy+1]=CZ;
        a[sx+1][sy+2]=CZ;
        a[sx+1][sy+3]=CY;
    }
    else
    {
        int k=(1<<(s-1));
        digui(s-1,sx,sy+k);
        digui(s-1,sx+k,sy);
        digui(s-1,sx+k,sy+2*k);
    }
    return;
}
signed main()
{
    while(std::cin>>n&&n)
    {
        memset(a,' ',sizeof(a));
        digui(n,1,1);
        for(int i=1;i<=(1<<n);i++)
        {
            for(int j=1;j<=(2<<n);j++)
            {
                printf("%c",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
```
谢谢。

---

## 作者：海之眷恋8 (赞：0)

~~居然没有人写题解?~~

~~来,我写一篇。~~



------------

~~(前面怎么那么多废话?)~~

这道题虽然尚未评分,预计难度为普及/提高-,还挺简单的.

说下思路:行数是2的n次方，以这个数组为基础，奇数行遇1输出"/\",偶数行遇连续两个1输出"/__\"，遇0补上相应的空格即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
char mymap[5000][5000];
int leftdot=100000000,rightdot=-100000000,topdot=100000000,bottomdot=-100000000;
//递归函数,实际上是用来给mymap赋值的.
void a(int x,int y,int deep)
{
	if(deep==1)
	{
	  	mymap[x][y]='/';
	  	mymap[x][y+1]='_';
	  	mymap[x][y+2]='_';
	  	mymap[x][y+3]='\\';//一定要输2个,因为\是转义'关键字',\\表示'\' 
	 	mymap[x-1][y+1]='/';
	 	mymap[x-1][y+2]='\\';
	}
	else
	{
		int dis=(int)pow((double)2,deep);
		//递归 
		a(x,y,deep-1);
		a(x,y+dis,deep-1);
		a(x-dis/2,y+dis/2,deep-1);
	}
}
int main ()
{
	int n,i,j;
	memset(mymap,' ',sizeof(mymap));
	a(2500,2500,10);
	while(cin>>n)//就是只要输入,就循环。这样做可以避免一个数组,而用一个变量搞定,特别省空间
	{
		if(n==0) break;
		topdot=2500-(int)pow((double)2,10)+1;
		bottomdot=topdot+(int)pow((double)2,n)-1;
		leftdot=2500+(int)pow((double)2,10)-(int)pow((double)2,n);
		rightdot=leftdot+(int)pow((double)2,n+1)-1;
		for(i=topdot;i<=bottomdot;i++)
		{
			for(j=leftdot;j<=rightdot;j++) cout<<mymap[i][j];//O(N^3)
			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}
```

---

