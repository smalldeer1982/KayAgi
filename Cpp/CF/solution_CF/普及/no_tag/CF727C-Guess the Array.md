# Guess the Array

## 题目描述

This is an interactive problem. You should use flush operation after each printed line. For example, in C++ you should use fflush(stdout), in Java you should use System.out.flush(), and in Pascal — flush(output).

In this problem you should guess an array $ a $ which is unknown for you. The only information you have initially is the length $ n $ of the array $ a $ .

The only allowed action is to ask the sum of two elements by their indices. Formally, you can print two indices $ i $ and $ j $ (the indices should be distinct). Then your program should read the response: the single integer equals to $ a_{i}+a_{j} $ .

It is easy to prove that it is always possible to guess the array using at most $ n $ requests.

Write a program that will guess the array $ a $ by making at most $ n $ requests.

## 说明/提示

The format of a test to make a hack is:

- The first line contains an integer number $ n $ ( $ 3<=n<=5000 $ ) — the length of the array.
- The second line contains $ n $ numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — the elements of the array to guess.

## 样例 #1

### 输入

```
5
 
9
 
7
 
9
 
11
 
6
 ```

### 输出

```
 
? 1 5
 
? 2 3
 
? 4 1
 
? 5 2
 
? 3 4
 
! 4 6 1 5 5```

# 题解

## 作者：rsdbk_husky (赞：4)

**注：本文含交互题 endl 与 fflush 不同种类的配合使用效果的 测试（见 “四”）**

## 零. 安利：

[安利一下我的博客。](https://rsdbkhusky.github.io/)

## 一. 审题：

#### 1. 前提条件：

- 一个数 $n$ 代表数组中数的个数。

#### 2. 询问 & 输入：

- 询问：

	输出两个数 $x$，$y$ 。代表询问 $a_x$ 和 $a_y$ 的和。
	
	格式：```? x y```
	
- 输入：

	读入一个数代表这两个数的和。

#### 3. 输出：

- 数组中所有数的值。格式：```! a[1] a[2] a[3] ... a[n]```

## 二. 思路

#### 1. 思考解法

我们可以不一口气把 $n$ 次都询问完（当然最后肯定是都要询问完的），既然 $n$ 个数询问 $n$ 次一定有解，那么我们可以先询问 $a_1+a_2$ ， $a_2+a_3$ 以及 $a_3+a_1$ 。这样就能先计算出 $a_1$，$a_2$ 以及 $a_3$。

只要有了一个数的具体值，我们每询问一次就可以算出一个数的具体值，这样一气呵成，避免了一口气询问完后堆积过多条件无从下手的情况。

#### 2. 具体实现

1. 前三个数：

    解法有很多，如

	$$\ \ \ \ \begin{cases}x+y=a\\y+z=b\\z+x=c\end{cases}$$
	$$\Longrightarrow 2x+2y+2z=a+b+c$$
	$$\Longrightarrow x+y+z=\dfrac{a+b+c}{2} $$
	$$\Longrightarrow x=\dfrac{a+b+c}{2}-b $$
    

	$y$，$z$ 同理。 

2. 剩下的数：

    接下来询问$a_1+a_4$，$a_1+a_5$ . . . $a_1+a_n$。

## 三. 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXn = 5000;

int n;
int add12,add13,add23;	//addxy:第x个和第y个数的和
int add[MAXn + 10];	//add[x]:第1个和第x个数的和
int first;	//第一个数的值

int main() {
    scanf("%d", &n);
    cout << "? 1 2" << endl;	scanf("%d", &add12);
    cout << "? 2 3" << endl;    scanf("%d", &add23);
    cout << "? 1 3" << endl;	scanf("%d", &add13);//这里用了endl就不需要fflush(stdout)了
    first = (add13 - add23 + add12) >> 1;//读入前三个数间两两值得和，并计算第一个数
    for (int i = 4 ; i <= n; ++i) {
        cout << "? 1 " << i << endl;
        scanf("%d", &add[i]);
    }//读入第1个数和第4-n个数间两两的值
    cout << "! " << first;					fflush(stdout);
    cout << ' ' << add12 - first;			fflush(stdout);
    cout << ' ' << add23 - add12 + first;	fflush(stdout);
    for(int i = 4; i <= n; ++i) {
        cout << ' ' << add[i] - first;
    }
}
```

## 四. endl 与 fflush

对交互题来说，弄清楚 ```endl``` 和 ```fflush``` 怎么用格外重要。不多废话了，直接摆上测试结果：

![测试结果](https://cdn.luogu.com.cn/upload/image_hosting/89vyrcgk.png)

**结论：**```endl``` 后面 不用跟 ```fflush```，但如果没有 ```endl``` （或是用 ```printf```）要加上 ```fflush(stdout)```。

---

## 作者：沉石鱼惊旋 (赞：2)

### 题目翻译

一个长度为 $n$ 的数组，最多 $n$ 次询问，输出数组元素。

询问：每次输出 `? x y`，返回 $x+y$ 的值。

输出：输出 ` !` 之后空一格，正常输出数组元素。  

### 题目思路

小学数学知识。

我们先询问 $x+y$ 的值，在询问 $x+z$ 的值，最后询问 $y+z$ 的值。

恰好每个数出现两次，把总和除以二，得到 $x+y+z$。

知道三数总和，知道两两之和，相减求 $3$ 个数的值。

接着处理余下的数。

整除 $3$，输出。

余 $2$，查询两个数的和，在随机找一个数搭配算出来。

余 $1$，随便找数搭配算。

### AC 代码

```cpp
void solve()
{
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n-n%3;i+=3)//先3个一组解决
	{
		int x,y,z;
		cout<<"? "<<i<<" "<<i+2<<endl;
		fflush(stdout);
		cin>>x;
		cout<<"? "<<i<<" "<<i+1<<endl;
		fflush(stdout);
		cin>>y;
		cout<<"? "<<i+1<<" "<<i+2<<endl;
		fflush(stdout);
		cin>>z;
		int sum=x+y+z;
		sum/=2;
		a[i+1]=sum-x;
		a[i+2]=sum-y;
		a[i]=sum-z;
	}
    //解决剩下的
	if(n%3==2)
	{
		cout<<"? "<<n-1<<" "<<n<<endl;
		fflush(stdout);
		int x,y;
		cin>>x;
		cout<<"? "<<1<<" "<<n<<endl;
		fflush(stdout);
		cin>>y;
		a[n]=y-a[1];
		a[n-1]=x-a[n];
	}
	if(n%3==1)
	{
		cout<<"? 1 "<<n<<endl;
		fflush(stdout);
		int x;
		cin>>x;
		a[n]=x-a[1];
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<" ";
	}
}
```

不知道交互题怎么解决，看[P1947](https://www.luogu.com.cn/problem/P1947)和[P1733](https://www.luogu.com.cn/problem/P1733)。

---

## 作者：Little_Cabbage (赞：1)

# 题目大意

题目会先给你一个 $n$ 表示未知数的数量，然后你可以通过输出 `? x y` 来询问第 $x$ 个未知数与第 $y$ 个未知数的和。最后输出每个未知数的值。

# 解题思路

对于前 $3$ 个数，可以利用小学知识直接求出来。

方程为：

$$
\begin{cases}
a_1 + a_2 = x \\ 
a_1 + a_3 = y \\
a_2 + a_3 = z
\end{cases}
$$

它的解为：

$$
\begin{cases}
a_1 = \frac{x + y - z}{2}\\
a_2 = \frac{x - y + z}{2}\\
a_3 = \frac{-x + y - z}{2}
\end{cases}
$$

剩下的 $n - 3$ 个数可以直接询问与 $a_1$ 的和，再用返回的和 $add$ 减去 $a_1$ 即可。

---

## 作者：codeLJH114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF727C)

# 题目大意

有一个长度为 $n$ 的数组 $a$，你需要通过 `? x y` 的方式来获取 $a_x + a_y$，你最多能问 $n$ 次，要你还原整个数组。

# 思路

我们可以先问 `? 1 2`, `? 2 3` 和 `? 1 3`，这样就可以求出 $a_1, a_2, a_3$ (有公式，接下来会讲。)，然后循环剩下的所有元素，问 `? 1 i`，因为 $a_1$ 已知，所以这样就可以求出整个数组了，相当于每个元素正好问一次。

## 解方程

$$\begin{cases}x + y = a\\y + z =  b\\x + z = c\end{cases}$$

$$2x + 2y + 2z = a + b + c$$
$$x + y + z = \frac{a + b + c}{2}$$
$$x + (a - x) + (c - x) = \frac{a + b + c}{2}$$
$$a + c - x = \frac{a + b + c}{2}$$
$$2a + 2c - 2x = a + b + c$$
$$-2x = b - a - c$$
$$x = \frac{a + c - b}{2}$$
$$y = a - x$$
$$z = c - x$$

这样我们就算出了 $a_1, a_2, a_3$，进而可以推算出整个数组了!

说了这么多，上代码!

```cpp
#include <iostream>
#define maxn 8192
using namespace std;
int n;
int a[maxn];
int main() {
    cin >> n;
    cout << "? 1 2" << "\n";
    int a1, b1, c1;
    cin >> a1;
    cout << "? 2 3" << "\n";
    cin >> b1;
    cout << "? 1 3" << "\n";
    cin >> c1;
    int x, y, z;
    x = (a1 + c1 - b1) / 2;
    y = a1 - x;
    z = c1 - x;
    a[1] = x;
    a[2] = y;
    a[3] = z; // 问出a[1], a[2], a[3]
    for (int i = 4; i <= n; i++) {
        int temp_sum;
        cout << "? 1 " << i << "\n";
        cin >> temp_sum;
        a[i] = temp_sum - a[1];
    } // 计算出a[4 ... n]
    cout << "! ";
    for (int i = 1; i <= n; i++)
        cout << a[i] << " "; // 输出结果
    return 0;
}
// 1. x + y = a;
// 2. y + z = b;
// 3. x + z = c;
// 1. + 2. + 3.
// 2x + 2y + 2z = a + b + c
// x + y + z = (a + b + c) / 2
// y = a - x
// z = c - x
// => x + (a - x) + (c - x) = (a + b + c) / 2
// => a + c - x = (a + b + c) / 2
// => x = (a + c - b) / 2;
// So, 
// x = (a + c - b) / 2
// y = a - x
// z = c - x
```

---

## 作者：MorsLin (赞：1)

长度为$n$的数组，询问$n$次来求出数组中每一个数的值

我们可以先询问三次

1. $a[1]+a[2]$

1. $a[1]+a[3]$

1. $a[2]+a[3]$

然后根据这三次询问的结果，我们可以求出$a[1]$、$a[2]$、$a[3]$的值，然后我们就可以通过询问$a[3]+a[4]$、$a[4]+a[5]$、$a[5]+a[6]$……来求出$a[4]$、$a[5]$、$a[6]$……

代码:

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int read(){
    int k=0; char c=getchar();
    for(;c<'0'||c>'9';) c=getchar();
    for(;c>='0'&&c<='9';c=getchar())
      k=(k<<3)+(k<<1)+c-48;
    return k;
}
int a[5010];
int main(){
	int n=read();
	cout<<"? "<<1<<" "<<2<<endl; fflush(stdout);
	int x1=read();
	cout<<"? "<<2<<" "<<3<<endl; fflush(stdout);
	int x2=read();
	cout<<"? "<<1<<" "<<3<<endl; fflush(stdout);
	int x3=read();
	a[1]=(x1+x2+x3)/2-x2;
	a[2]=(x1+x2+x3)/2-x3;
	a[3]=(x1+x2+x3)/2-x1;
	for(int i=3;i<=n-1;i++){
		cout<<"? "<<i<<" "<<i+1<<endl;
		fflush(stdout); int x=read();
		a[i+1]=x-a[i];
	}
	printf("! ");
	for(int i=1;i<=n;i++)
	  printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：_zqh_ (赞：0)

感觉是道橙呢。

### 思路简述

考虑询问是给两数和，形如：
$$
a_x+a_y=z
$$
那么我们只要知道 $a_x,a_y$ 中任意一项即可推出剩下的项。

假设我们得到了：
$$
\begin{cases}
a_1+a_2=x\\
a_1+a_3=y\\
a_2+a_3=z
\end{cases}
$$
根据我们小学二年级就学过的方程知识，可得：
$$
2\times a_1 + 2\times a_2 + 2\times a_3=x+y+z\\
$$

两边除以一个 $2$：
$$
a_1+a_2+a_3=\frac{x+y+z}{2}
$$
带入原方程，解得：
$$
\begin{cases}
a_1=\frac{x+y-z}{2}\\
a_2=\frac{x-y+z}{2}\\
a_3=\frac{-x+y+z}{2}
\end{cases}
$$
既然知道了 $a_1,a_2,a_3$ 那么根据上文推导的，即可求出剩下的 $n-3$ 个数，详情见代码。

（好像详细了点）。

[code](https://codeforces.com/contest/727/submission/259882349)。

---

## 作者：qw1234321 (赞：0)

### 前置知识：for 循环 / 交互题如何清空缓冲区（题目里已经说了）

根据小学奥数，若：

$$\ \ \ \ \begin{cases}x+y=a\\y+z=b\\z+x=c\end{cases}$$

又设 $p = \frac{a + b + c}{2}$，则不难得出：

$$\ \ \ \ \begin{cases}x=p-b\\y=p-c\\z=p-a\end{cases}$$

代入此题，即：

$$\ \ \ \ \begin{cases}a_1=p-b\\a_2=p-c\\a_3=p-a\end{cases}$$

其中 $a,b,c$ 为询问 $3$ 次后得到的值，分别为 $a_1+a_2,a_2+a_3,a_3+a_1$。

那么知道了前三个数的值，后面的数就好做了。

对于每个大于 $3$ 的 $i$，先询问一次 $a_1+a_i$ 的值，设为 $q$，那么 $a_i = q - a_1$。

于是便做完了。

提一句，刷新缓冲区可以使用 `endl` 换行自动刷新。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5005;
int n, sum12, sum23, sum13, sum123, sum1i;
int a[N];

void work(){
	cin >> n;
	cout << "? 1 2" << endl, cin >> sum12;
	cout << "? 1 3" << endl, cin >> sum13;
	cout << "? 2 3" << endl, cin >> sum23;
	sum123 = (sum12 + sum23 + sum13) / 2;
	a[1] = sum123 - sum23, a[2] = sum123 - sum13, a[3] = sum123 - sum12;
	for (int i = 4; i <= n; i++){
		cout << "? 1 " << i << endl, cin >> sum1i;
		a[i] = sum1i - a[1];
	}
	cout << "! ";
	for (int i = 1; i < n; i++) cout << a[i] << " ";
	cout << a[n];
	fflush(stdout);
}

signed main(){
	int t = 1;
	//  cin >> t;
	while(t--) work();
	return 0;
}
```

---

## 作者：LBYYSM_123 (赞：0)

### 思路
设询问如下：    

$\begin{cases}q[1]=a[1]+a[2]\\q[2]=a[1]+a[3]\\q[3]=a[2]+a[3]\\q[n-1]=a[1]+a[n]\\q[n]=a[2]+a[n]\end{cases}$   

联立这些式子便可解得： $ a[1]=(q[1]+q[n-1]-q[n])/2 $  。  
将其带入可知： $a[i]=q[i-1]-a[1]$  。       

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q[20000],a;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		printf("? %d %d\n",1,i+1);
		fflush(stdout);
		scanf("%d",&q[i]);
	}
	printf("? %d %d\n",2,n);
	fflush(stdout);
	scanf("%d",&q[n]);
	a=(q[1]+q[n-1]-q[n])/2;
	printf("! %d",a);
	fflush(stdout);
	for(int i=1;i<n;i++) 
		printf(" %d",q[i]-a);
	fflush(stdout);
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：0)

不是很难得，而且是人生第一道交互 awa！而且貌似是七下第一弹题解。

~~都这么大了才写交互的 SX 是屑~~

闲话少说，切入正题

----
把样例输出查询的 $i$ 与 $j$ 之间连一条边，会得到一个长度为 $n$ 的简单环。

那么思路应该很明了了，问 $a_1 + a_2$、$a_2 + a_3$、$a_3+ a_4$……$a_{n - 1}+ a_n$、$a_1+a_n$。

然后我们就可以愉快的解方程，但是事实上还有更加优（li）美（pu）的解法。
~~事实上是解方程的时候果断高斯消元然后发现我忘了高斯消元。。。感谢这道题让我再看了一遍~~

我们都知道 $x,y,z$ 如果能知道 $\begin{cases}x+y = a_1\\y+z = a_2\\ x+z = a_3\end{cases}$ 那么 $\begin{cases}x = \dfrac{a_1 - a_2 + a_3}{2}\\y = \dfrac{a_1 + a_2 - a_3}{2}\\z = \dfrac{-a_1 + a_2 + a_3}{2}\end{cases}$。


也就是说我们可以依次每三个数为一组查询它们互相的和，得到一个三元一次方程，按照上面的式子解。

剩下的数字我们可以询问与之前求得的数字的和，这样也能解决。

由于我的语文不好，具体细节看代码。

```cpp
//SIXIANG
#include <iostream> 
#define MAXN 100000
#define QWQ cout << "QWQ" << endl;
using namespace std;
int a[MAXN + 10];
int main() {
	int n; cin >> n;
	char opt; int a1, a2, a3;
	for(int i = 1; i <= n / 3; i++) {
		int p = (i - 1) * 3 + 1;
		cout << "? " << p << ' ' << p + 1 << endl; cin >> a1;
		cout << "? " << p + 1 << ' ' << p + 2 << endl; cin >> a2;
		cout << "? " << p + 2 << ' ' << p << endl; cin >> a3;//每三个数为一组
		a[p] = (a1 + a3 - a2) / 2;//解方程，式子在上面
		a[p + 1] = (a1 - a3 + a2) / 2;
		a[p + 2] = (a2 + a3 - a1) / 2;
	}
	for(int p = 1; p <= n % 3; p++) {//可能还有剩下的数字
		cout << "? " << n / 3 * 3 + p << ' ' << 1 << endl; cin >> a1;//得到与 a[1] 的和，a[1] 的值是知道的
		a[n / 3 * 3 + p] = a1 - a[1];//直接减去就行了
	}
	cout << "! ";
	for(int p = 1; p <= n; p++)
		cout << a[p] << ' ';
	cout << endl;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

一看数据范围，$3\le n\le5000$，心里就有底了。

首先，我们询问三次，并设三个数：

$$\begin{cases}x_1=a[1]+a[2]\\x_2=a[1]+a[3]\\x_3=a[2]+a[3]\end{cases}$$

然后计算数组 $a$ 的前三个数：

$$\begin{cases}a[1]=(x_1+x_2+x_3)\div2-x3\\a[2]=(x_1+x_2+x_3)\div2-x2\\a[3]=(x_1+x_2+x_3)\div2-x1\end{cases}$$

接下来，我们可以根据以下公式，循环求后面的数：

$$a[i]=(a[i-1]+a[i])-a[i-1]$$

最后输出即可。

由此我们得出完整代码。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int n,x1,x2,x3;
int a[5005];
int main()
{
	scanf("%d",&n);//输入n。
	printf("? 1 2\n");//询问前三个数。
	fflush(stdout);//记得清空缓冲区！
	scanf("%d",&x1);
	printf("? 1 3\n");
	fflush(stdout);
	scanf("%d",&x2);
	printf("? 2 3\n");
	fflush(stdout);
	scanf("%d",&x3);
	a[1]=(x1+x2+x3)/2-x3;//计算前三个数。
	a[2]=(x1+x2+x3)/2-x2;
	a[3]=(x1+x2+x3)/2-x1;
	for(int i=4;i<=n;i++)
	{
		printf("? %d %d\n",i-1,i);//循环求后面的数。
		fflush(stdout);
		int input;
		scanf("%d",&input);
		a[i]=input-a[i-1];//计算后面的数。
	}
	printf("! ");//输出。
	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	fflush(stdout);
	return 0;//完结撒花！
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/51821057>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：Weak_Konjak (赞：0)

## 思路

### 解方程

为方便，询问如下:

q[1]=a[1]+a[2],	~~~~			~~~~1

q[2]=a[1]+a[3],

q[3]=a[1]+a[4]....

q[n-1]=a[1]+a[n]~~~~					~~~~2

最后询问q[n]=a[2]+a[n]~~~~			~~~~3

那么，联立1、2、3三式，可解得a[1]=(q[1]+q[n-1]-q[n])/2
再将a[1]代入其他式子，可解得数组a，a[i]=q[i-1]-a[1]



## 代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,q[20000],a;
int main()
{
	cin>>n;
	fflush(stdout);
	for(int i=1;i<n;i++){
		cout<<'?'<<' '<<1<<' '<<i+1<<'\n';
		cin>>q[i];
	}
	cout<<'?'<<' '<<2<<' '<<n<<'\n';cin>>q[n];
	a=(q[1]+q[n-1]-q[n])/2;
	cout<<'!'<<' '<<a;
	for(int i=1;i<n;i++) cout<<' '<<q[i]-a;
}
```


---

## 作者：rui_er (赞：0)

这是我第二道交互题。

首先，有n个未知数，n次询问，是一个n元1次方程组。

如何构造方程？

我们知道，对于方程组

$$\begin{cases}
x+y=a&\\
y+z=b&\\
z+x=c\\
\end{cases}$$

一定有唯一解。

所以前三个询问就可以这样询问：

```
? 1 2
? 2 3
? 1 3
```

解方程组方法：

```cpp
sum123 = (sum12 + sum23 + sum13) / 2;
a[1] = sum123 - sum23;
a[2] = sum123 - sum13;
a[3] = sum123 - sum12;
```

之后的第i次询问如下：

```
? 1 i
```

可解出整个数组。

完整代码：

```cpp
#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

int a[5001];

int main()
{
    int n, sum12, sum13, sum23, sum, sum123;
    cin>>n;
    cout<<"? 1 2"<<endl;
    fflush(stdout);
    cin>>sum12;
    cout<<"? 1 3"<<endl;
    fflush(stdout);
    cin>>sum13;
    cout<<"? 2 3"<<endl;
    fflush(stdout);
    cin>>sum23;
    sum123 = (sum12 + sum23 + sum13) / 2;
    a[1] = sum123 - sum23;
    a[2] = sum123 - sum13;
    a[3] = sum123 - sum12;
    for(int i=4;i<=n;i++)
    {
        cout<<"? 1 "<<i<<endl;
        fflush(stdout);
        cin>>sum;
        a[i] = sum - a[1];
    }
    cout<<"! ";
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

