# Almost Ternary Matrix

## 题目描述

给定偶数 $ n $ 和 $ m $，构造一个 $ n $ 行 $m $ 列只有0和1的方格矩阵，使得任意一个方格 $ (i,j) $ 正好有两个邻居方格的值不同与自己的值 $ a_{i,j} $ 。

公用一条边的两个方格视为邻居，准确为：方格 $ (x,y) $ 的邻居位置为 $ (x-1,y) $ ， $ (x+1,y) $ ， $ (x,y-1) $ ， $ (x,y+1) $ 。

## 说明/提示

白代表0，黑代表1。

三张图分别表示样例的三个测试用例。

## 样例 #1

### 输入

```
3
2 4
2 2
4 4```

### 输出

```
1 0 0 1
0 1 1 0
1 0
0 1
1 0 1 0
0 0 1 1
1 1 0 0
0 1 0 1```

# 题解

## 作者：Otue (赞：7)

## 思路
整个答案矩阵只需要由一些子矩阵构造而成。

可以想到一个 $4\times 4$ 的子矩阵构造方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/ousuc126.png)

则 $n\times m$ 的矩阵只需要若干个 $4\times 4$ 子矩阵构成即可。

举个例子，$n=6,m=8$，矩阵构造如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/4cajeb4a.png)
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int t, n, m;
int a[5] = {1, 0, 0, 1}, b[5] = {0, 1, 1, 0};

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (i % 4 <= 1) cout << a[(j - 1) % 4] << ' ';
				else cout << b[(j - 1) % 4] << ' ';
			}
			puts("");    //构造矩阵
		}
	}
}
```
## 总结
我们可以看到，CF 构造题第一眼似乎无从下手，但是构造方案却极其优美而简单。

此题解仅展示一种合法的构造方案，怎么构造则看灵感...

---

## 作者：cjlak1o1 (赞：7)

面对构造题，我们往往遵循**特殊性质**或者**从一到无穷大的**原则。

这里的样例二给了一个很好的“一”，我们顺延它的模块，利用题目条件试着构造下去，会发现这是一个完美的基础图形。

初始“一”：  

![](https://cdn.luogu.com.cn/upload/image_hosting/3ik011nf.png)

我们从小到大，先试试 $2\times 4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/el3b3m2v.png)

那么 $4 \times 2$ 是同样的道理。

然后是：  

![](https://cdn.luogu.com.cn/upload/image_hosting/2ghuoc4u.png)

当我们继续以这个方式构造合法矩形，就会发现所有的大矩形都是由初始的第一个矩形，或者它的对称图形构成的，且都可以合法，那么我们就可以无限的构造了。

构造方法：

- 每四行为一个整体，开头以 $1001$ 循环。

- 每一行也四个为一个整体，$1$ 开头则 $1001$，$0$ 开头则 $0110$。

最后，附上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=0;
 
inline int read()
{
	int res=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}
 
int T,n,m;
 
int main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i%4==1||i%4==0)
				{
					if(j%4==1||j%4==0) printf("1 ");
					else printf("0 ");
				}
				if(i%4==2||i%4==3)
				{
					if(j%4==1||j%4==0) printf("0 ");
					else printf("1 ");
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
```
**蒟蒻拙见，请指教。**

---

## 作者：_djc_ (赞：2)

# 背景

这一天是期末考试前的 2 天，趁着他们自由复习来了机房，决定先写一场之前的比赛练练手，然后就发现全是构造……

# 题目分析

本蒟蒻觉得本题最难的地方就在于读题 ~~（本蒟蒻一开始就没读懂错了两次……）~~，他是什么意思呢，意思就是让你所打印出的表格中，对于每个元素，其邻居恰有两个与其颜色不同（**注意是只有两个**）。

样例中给的输出看起来没有什么规律可循，我们可以自己想一想怎样构造出一个表格满足其要求。

对于样例，其实我们可以这样构造：

第一组：

```
 0  1  1  0
 1  0  0  1
```

第二组：
```

 0  1  1  0 
 1  0  0  1
 1  0  0  1
 0  1  1  0 
```
大家到这里或许可以发现：其实这样构造出的表格其实都是由
```
 0  1  
 1  0   
```
旋转复制而来。

由于 $n$ 和 $m$ 都是偶数，说明我们这样将小表格旋转复制成大表格的做法是正确的！

# 代码实现

可以发现其实每组解都是由
```
 0  1  1  0  0  ……
 1  0  0  1  1  ……
 1  0  0  1  1  …… 
 0  1  1  0  0  …… 
 1  0  0  1  1  …… 
 … …  … …  …  … 
 ```  
这个表格截取而来，所以我们可以先预处理出来一个大表格：

```cpp
for(int j = 1, i = 1; j <= 50; j += 4) a[i][j] = 0, a[i][j+1] = 1, a[i][j+2] = 1, a[i][j + 3] = 0; 
for(int i = 2; i <= 50; i+=2){  //n、m范围都是到50
	for(int j = 1; j <= 50; j+=4){
		if(i%4 == 0){
			a[i][j] = 0, a[i][j+1] = 1, a[i][j+2] = 1, a[i][j + 3] = 0;
			a[i+1][j] = 0, a[i+1][j+1] = 1, a[i+1][j+2] = 1, a[i+1][j + 3] = 0;
			}
		else{
			a[i][j] = 1, a[i][j+1] = 0, a[i][j+2] = 0, a[i][j + 3] = 1;
			a[i+1][j] = 1, a[i+1][j+1] = 0, a[i+1][j+2] = 0, a[i+1][j + 3] = 1;
		}
	}
}
```

然后在输入数据时截取输出就行了：

```cpp
while(T--){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++){	//截取表格输出
		for(int j = 1; j <= m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
```
~~应该就不用附完整代码了吧……~~


于是，这道题就做完咯！

**完**






---

## 作者：Murasoishi (赞：0)

# 分析
运用局部到整体的思想，将目标矩阵拆分成若干子矩阵。

首先， $2\times2$ 的矩阵只有唯一一种（黑白翻转归为一种），如下

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1699B/7ff6e4e6c9a559b0e10cdc230a583d5a3442d4ca.png)

利用 $2\times2$ 的矩阵拓展出 $4\times4$ 的矩阵（利用此矩阵只能构造唯一合法矩阵），如图

![](https://cdn.luogu.com.cn/upload/image_hosting/xve77haq.png)

利用该矩阵即可构造所有类型的矩阵

# 注意
对于 $4\times 4$ 矩阵填充后仍有剩余的矩阵，即在原来矩阵的基础上“切割”出对应部分，如 $6\times 6$ 的矩阵表示如下

![](https://cdn.luogu.com.cn/upload/image_hosting/0pdzrqv4.png)

可以理解为构造 $8\times8$ 矩阵后截取出其中 $6\times6$ 的部分

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;cin>>T;
	while(T--){
		int n,m;cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i%4==1 or i%4==0){
					if(j%4==1 or j%4==0)cout<<"1 ";
					else cout<<"0 ";
				}
				if(i%4==2 or i%4==3){
					if(j%4==2 or j%4==3)cout<<"1 ";
					else cout<<"0 ";
				}
			}
			cout<<endl;
		}
	}
}
```

---

## 作者：tian_jun_cheng (赞：0)

这道题有很多方法，这里给出一种。

通过样例的前两个，我们发现一种共同出现的矩阵。

$ \begin {pmatrix}
  0&1  \\
  1&0
\end {pmatrix} $

以这个矩阵为一单位，对于相邻的两个矩阵，我们要进行旋转。


$ \begin {pmatrix}
  1&0  \\
  0&1
\end {pmatrix} $

注意判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[60][60];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		int sub=1;
		int l=1;
		for(int i=1;i<=n;i+=2)
		{
			for(int j=1;j<=m;j+=2)
			{

				if(sub%2==1)
				{
					a[i][j]=1;
					a[i][j+1]=0;
					a[i+1][j]=0;
					a[i+1][j+1]=1;
				}
				else
				{
					a[i][j]=0;
					a[i][j+1]=1;
					a[i+1][j]=1;
					a[i+1][j+1]=0;
				}
				sub++;
			}
			sub++;
			if(m%4!=0)
				sub++;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}
	}
	return 0;
}

```


---

## 作者：The_BJX (赞：0)

## 题意翻译

给定偶数 $m$ 和 $n$， 要求构造 $m$ 行 $n$ 列由 $0$ 和 $1$ 构成的矩阵，使得矩阵的每一个位置都有两个与这个位置的值不同的邻居。

## 思路分析

按照构造题的常用思路，我们应该从小的情况看起。首先观察样例2.如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1699B/7ff6e4e6c9a559b0e10cdc230a583d5a3442d4ca.png)

如果白色代表 $0$，黑色代表 $1$, 可以发现这个矩阵（本来就）符合题意。我们要做的就是拼合这个矩阵。为了保持其正确性，我们需要让每一个位置相邻的另外两个位置的值与这个位置的值相同（因为已经有两个不同了）。因此显然我们应将拼合的相邻矩阵旋转九十度。当 $m=2$, $n=4$ 时构造结果如下图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1699B/e45c6cba9610d92a23c09f683cadfcf138054d1b.png)

接下来的步骤便十分显然，如上分析即可。

但是为了实现方便，我们如上分析便不够适用。继续找规律我们发现构造出来的结果总是如下矩阵的拼接。

```
1 0 0 1
0 1 1 0
0 1 1 0
1 0 0 1
```

因此我们只需要输出由此矩阵镶嵌得到的大矩阵即可。

## 代码

更加花招的实现方法请见代码。

```cpp
#include <iostream>
using namespace std;

int n, m;

int a[4]={1,0,0,1};

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cout << (a[i%4]+a[j%4])%2 << " ";//异或也行
            }
            cout << endl;
        }
    }
}
```


---

## 作者：yeshubo_qwq (赞：0)

## Description

要求构造一个 $n \times m$ 的 01 矩阵，需要符合每个位置的上下左右恰好有两个位置与其值相反。

## Solution

题目中保证了一个非常有用的性质：**$n,m$ 均为偶数！**

这提示我们可以通过放置若干个 $2 \times 2$ 的小矩阵求解。

首先找出可行的 $2 \times 2$ 小矩阵有哪些？

可行矩阵 A：

```
10
01
```

可行矩阵 B：

```
01
10
```

有了矩阵 A/B，就可以考虑放置问题了。

观察一下，发现：仅当两个矩阵 A 或者两个矩阵 B 相邻（上下左右）不符合题意。

放置方法显然：

```
ABABA...
BABAB...
ABABA...
...
```
## Code

```cpp
//仅提供核心代码
for (i=1,h=0;i<=n;i+=2){
	if ((++h)&1) fl=0; else fl=1;
	for (j=1;j<=m;j+=2){
		if (fl==0)//A
			a[i][j]=1,a[i][j+1]=0,a[i+1][j]=0,a[i+1][j+1]=1;
		else//B
			a[i][j]=0,a[i][j+1]=1,a[i+1][j]=1,a[i+1][j+1]=0;
		fl^=1;
	}
}
```


---

## 作者：_Remake_ (赞：0)

## 题意简述
多组数据，每组数据给定两个偶数 $n$ 和 $m$，要求构造一个 $n$ 行 $m$ 列的01矩阵满足对矩阵内任意的方格 $(i,j)$，都有且仅有两个相邻的方格的值与 $(i,j)$ 的值不同。
## 题目分析
很显然这是一道**构造题**，不难发现，当 $m$，$n$ 都为 $2$ 时，

$\begin{bmatrix}
 0&1 \\
  1&0
\end{bmatrix}$


显然是一种合法的方案，我们称为01矩阵A，而

$\begin{bmatrix}
 1&0 \\
  0&1
\end{bmatrix}$

则是另外一种合法的方案，我们称为01矩阵B。我们观察样例一，可以发现该样例的答案可以通过矩阵A和矩阵B拼接而成，这就给了我们一些启发。

而仔细观察样例三，如下图，样例三的另一种答案也可以通过矩阵A和矩阵B拼接而成。

$\begin{bmatrix}
  1& 0 &0 &1 \\
  0& 1 &1  &0 \\
  0& 1& 1 & 0\\
  1&0  &0  &1
\end{bmatrix}$

这时，我们想到，是否可以只使用矩阵A和矩阵B就可以拼成满足答案的矩阵？

我们从特殊到一般，先考虑只有 $n$ 等于 $2$ 的情况(只有 $m$ 等于 $2$ 的情况和这是等价的)

当 $m$ 等于 $6$ （ $m$ 等于 $4$ 的情况为样例一），我们发现：

$\begin{bmatrix}
  0&1  & 1 &0&0&1 \\
  1& 0 &0  &1&1&0
\end{bmatrix}$

是合法的一种答案，它也可以被矩阵A和矩阵B拼成。当 $m$ 继续增大，我们只需要继续往右拼接矩阵A和矩阵B就可以满足题目要求。

现在考虑 $n$， $m$ 都大于 $2$ 的情况，以 $m$ 等于 $6$， $n$ 等于 $4$ 为例，

$\begin{bmatrix}
  1&0  & 0 &1  &  1& 0\\
  0&  1&  1& 0 &  0& 1\\
  0& 1 &  1& 0 &0  & 1\\
 1 & 0 &0  &1  &1  &0
\end{bmatrix}$

为一个合法答案，显然它可以被矩阵A和矩阵B拼成，而当 $n$， $m$ 继续增加时，我们只需要继续往矩阵上拼接矩阵A和B，即可构造出对应的答案。

还有一个问题：如何修改答案矩阵的元素并输出？

我们发现：构成答案的01矩阵的顺序也是有规律的，如下图对应 $m$ 等于 $6$，$n$ 等于 $4$ 的情况：

$\begin{bmatrix}
  B&A  &B \\
  A& B &A
\end{bmatrix}$

我们可以把答案矩阵分割为一个个 $2$ $\times$ $2$ 的小矩阵，我们只需要枚举每个小矩阵的左上角坐标，并修改该小矩阵内方格的值，最后输出。

至此，本题得到完美解决。
## 代码
注：代码中快读已省略。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int matrix1[3][3];//矩阵A
int matrix2[3][3];//矩阵B
int M[51][51];//答案矩阵
int main()
{
    //---------------初始化矩阵
	matrix1[1][1]=0;
	matrix2[1][1]=1;
	matrix1[1][2]=1;
	matrix2[1][2]=0;
	matrix1[2][1]=1;
	matrix2[2][1]=0;
	matrix1[2][2]=0;
	matrix2[2][2]=1;
    //---------------
	int T;
	T=read();
	while(T--)
	{
		a=read();
		b=read();
		a/=2;
		b/=2;
		for(int r=1,x=1;r<=a;r++,x+=2)//坐标变换
		{
			for(int f=1,y=1;f<=b;f++,y+=2)
			{
				if((r+f)&1)//修改答案矩阵
				{
					M[x][y]=matrix1[1][1];
					M[x+1][y]=matrix1[2][1];
					M[x][y+1]=matrix1[1][2];
					M[x+1][y+1]=matrix1[2][2];
				}
				else
				{
					M[x][y]=matrix2[1][1];
					M[x+1][y]=matrix2[2][1];
					M[x][y+1]=matrix2[1][2];
					M[x+1][y+1]=matrix2[2][2];
				}
			}
		}
		for(int r=1;r<=a*2;r++)
		{
			for(int f=1;f<=b*2;f++)
			{
				cout<<M[r][f]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}

```


---

