# Coder

## 题目描述

Iahub 很喜欢下棋。他甚至发明了一种棋子叫做 "Coder"。

一个 Coder 可以攻击与它相邻的格子中的棋子（水平和竖直方向）。如果一个 Coder 在坐标 $(x,y)$上，它可以攻击 $(x+1,y)$ , $(x-1,y)$ , $(x,y+1)$ , $(x,y-1)$ 这四个格子。

Iahub 想要知道有多少个 Coder 可以被放在 $n*n$
 的棋盘中，使得任意两个 Coder 都不能互相攻击。

## 样例 #1

### 输入

```
2
```

### 输出

```
2
C.
.C
```

# 题解

## 作者：清小秋ovo (赞：6)

# CF384A

[洛谷传送门](https://www.luogu.com.cn/problem/CF384A)

[原题传送门](https://codeforces.com/problemset/problem/384/A)

本菜鸡的第 $99$ 道橙题，心血来潮写一篇题解。

## 题意

一种棋的规则是：在一个棋盘中，与该棋子相邻的上，下，左，右，$4$ 个格子中不能有棋子出现。

给出一个 $n \times n$ 的棋盘，首先输出在这个棋盘中最多能放多少个棋子，并输出一种最大的可行的摆放方案。

## 解法$1$ 纯暴力模拟

通过画图观察规律。

$$n=2$$

```
C.
.C
```

$$n=3$$

```
C.C
.C.
C.C
```

$$n=4$$
```
C.C.
.C.C
C.C.
.C.C
```
$$n=5$$
```
C.C.C
.C.C.
C.C.C
.C.C.
C.C.C
```
我们发现，当坐标为第偶数行，偶数列时落子，或者在第奇数行，第奇数列落子，得到的一定是最优解。

那么就可以根据这个思路通过创建一个二维字符组模拟棋子摆放的过程。
因为 $n$ 的数据范围很小，所以这样的方法虽然时间复杂度较高，但是也是可行的。

### 第一种解法代码

```cpp
#include<bits/stdc++.h>

using namespace std;

char board[2000][2000];//存储棋盘状态 
int cnt;
int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   int n;
   cin>>n;
   //i代表行,j代表列
   for(int i=1;i<=n;i++){
       for(int j=1;j<=n;j++){
           if((i%2&&j%2)||!(i%2^j%2))board[i][j]='C',cnt++; //判断是否可以落子
           else board[i][j]='.';//否则不下子
       }
   }
   cout<<cnt<<endl;
   for(int i=1;i<=n;i++){
       for(int j=1;j<=n;j++){
           cout<<board[i][j]; //输出棋盘
       }
       cout<<endl;
   }
}

```
## 解法 $2$ 优化暴力

但是刚刚的解法需要先存储，再输出一遍，比较浪费时间，还是有可以优化的空间。

可以直接读入并输出。

首先，给出 $n$ 的时候，就可以直接求出总数了。

分类讨论 $n$ 为奇数和偶数的两种情况：

1. 奇数时，总数为 $(n\times n+1)\div 2$
2. 偶数时，总数为 $n\times n \div 2$

随后就可以根据奇数行和偶数行来进行输出了，大大缩小了时间复杂度。

### 第二种解法代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   int n;
   cin>>n;
   if(n%2==0){//如果n为偶数
       cout<<n*n/2<<endl;
       for(int i=1;i<=n;i++){
           if(i%2==1){
               for(int i=1;i<=n/2;i++) cout<<"C.";//奇数行
           }else{
               for(int i=1;i<=n/2;i++) cout<<".C";//偶数行
           }
           cout<<endl;
       }
    }else{//如果n为奇数
       cout<<(n*n+1)/2<<endl;
       for(int i=1;i<=n;i++){
           if(i%2==1){//奇数行
               for(int i=1;i<=n/2;i++) cout<<"C.";
               cout<<"C";
           }else{
               for(int i=1;i<=n/2;i++) cout<<".C";//偶数行
               cout<<".";
           }
           cout<<endl;
       }
   }
}

```


当然，还存在有更优的解，这里因为本人能力有限，就不进行列举了。

~~（数据这么小做别的题它不香吗，干嘛非要优化）~~

码字不易，求点赞






---

## 作者：米奇奇米 (赞：2)

## 找规律好题啊！

### $1.1$理解题目意思
就是当你在$(x,y)$放了$Coder$，就不能在$(x+1,y),(x-1,y),(x,y+1),(x,y-1)$的地方放置$Coder$，让你画出在$n*n$的棋盘中最多可以放多少个$Coder$

### $2.1$画图找规律
当$n=3$时：![](https://cdn.luogu.com.cn/upload/pic/61398.png)

红点的坐标为$(1,1),(1,3),(2,2),(3,3),(3,1)$时是不会被攻击到的。
大力找规律：当 $(x+y)$为偶数时可以放置的$Coder$最多。所以$O(n^2)$统计答案就可以了。


---

## 作者：syanoeclipse (赞：1)

[个人博客体验更佳](https://www.luogu.com.cn/blog/andrew-zhong/solution-cf384a)

今天我发个题解，带大家了解一下本题的思维。

首先，分类：他的奇偶性。

```cpp
int coder(int i)
{
	if(i%2==0)
	if(i%2==1)
}
```

如果输入了个偶数的话，最好是这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/ah5vxc54.png)

我详细解释一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/7qpmsyze.png)

这个的原因很简单，因为每连续两个只可以取一个。

那对于$2a$就是$\dfrac{(2a)^2}{2}=\dfrac{4a^2}{2}=2a^2$。

```cpp
int coder(int i)
{
	if(i%2==0)return (i*i)/2;
	if(i%2==1)
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/gsbrww9u.png)

在给奇数配对的时候，会有一点麻烦。

首先给前面$2n\times(2n+1)$个配对之后最后还会。。。剩一个

那就把它取了吧，所以最好对于$2a+1$有$\dfrac{(2a+1)^2+1}{2}=\dfrac{4a^2+4a+2}{2}=2a^2+2a+1$。

```cpp
int coder(int i)
{
	if(i%2==0)return (i*i)/2;
	if(i%2==1)return (i*i+1)/2;
}
```

于是可以有

```cpp
int main()
{
	int a;
	cin>>a;
	cout<<coder(a);
	return 0;
}
```
然后输出会很有意思。

输出也分奇偶。。。

干脆？

将`coder()`带入到`main`里，这样好判断。。

```cpp
int main()
{
    int k;
    cin>>k;
    if(k%2==0)
    {
        int d=k/2;
        cout<<d*k;
        for(int i=0;i<d;i++)
        {
            cout<<'\n';
            for(int i=0;i<d;i++)
            {
                cout<<"C.";
            }
            cout<<'\n';
            for(int i=0;i<d;i++)
            {
                cout<<".C";
            }
        }
    }
    if(k%2==1)
    {
        cout<<(k*k+1)/2;
        int d=k/2;
        for(int i=0;i<d;i++)
        {
            cout<<'\n';
            for(int j=0;j<d;j++)
            {
                cout<<"C.";
            }
            cout<<"C";
            cout<<'\n';
            for(int j=0;j<d;j++)
            {
                cout<<".C";
            }
            cout<<".";
        }
        cout<<'\n';
        for(int i=0;i<d;i++)
        {
            cout<<"C.";
        }
        cout<<"C";
    }
    return 0;
}
```

这里我详细解读一下，如果是偶数的话，

```
C.
.C
```

一个循环两行，每两行内两个循环，第一个是循环`C.`，第二个是循环`.C`，很无聊。

但是如果是奇数的话就很有意思了。

```
C.C
.C.
C.C
```

一个循环两行，每两行内两个循环，第一个是循环`C.`（外加输出一个`C`），第二个是循环`.C`（外加输出一个`.`），最后循环`C.`（外加输出一个`C`）。

于是完整代码上了。。。

```cpp
#include<iostream>
using namespace std;
int main()
{
    int k;
    cin>>k;
    if(k%2==0)
    {
        int d=k/2;
        cout<<d*k;
        for(int i=0;i<d;i++)
        {
            cout<<'\n';
            for(int i=0;i<d;i++)
            {
                cout<<"C.";
            }
            cout<<'\n';
            for(int i=0;i<d;i++)
            {
                cout<<".C";
            }
        }
    }
    if(k%2==1)
    {
        cout<<(k*k+1)/2;
        int d=k/2;
        for(int i=0;i<d;i++)
        {
            cout<<'\n';
            for(int j=0;j<d;j++)
            {
                cout<<"C.";
            }
            cout<<"C";
            cout<<'\n';
            for(int j=0;j<d;j++)
            {
                cout<<".C";
            }
            cout<<".";
        }
        cout<<'\n';
        for(int i=0;i<d;i++)
        {
            cout<<"C.";
        }
        cout<<"C";
    }
    return 0;
}
```

---

## 作者：Tenshi (赞：1)

~~原来还可以交题解吗~~

这题挺简单的，其实就是将棋盘进行黑白相间的染色嘛（像国际象棋盘一样），然后把coder放在全部白格子或者黑格子，而且不难得到这就是coder最多的摆放方法了，我们记coder最多为k个。

（证明：假设有比k更多的摆放方法，我们对棋盘进行上述二染色，必然存在一个棋子使得自身所在格子颜色与其他不同，且必定存在与该棋子相邻的棋子，矛盾）

于是我们就按照上述方法实现即可。

接下来上代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iomanip>
#include <stdlib.h>  
using namespace std;

int main(){
	int n;
	cin>>n;
	if(n%2==0){
		cout<<n*n/2<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
			{
				if(j%2==0&&i%2==0)cout<<'C';
				else if(j%2==1&&i%2==0)cout<<'.';
				else if(j%2==1&&i%2==1)cout<<'C';
				else if(j%2==0&&i%2==1)cout<<'.';
			}
			cout<<endl;
		}
		}
			
		else{
		cout<<(n+1)/2*(n/2+1)+(n/2)*(n-1)/2<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
			{
				if(j%2==0&&i%2==0)cout<<'C';
				else if(j%2==1&&i%2==0)cout<<'.';
				else if(j%2==1&&i%2==1)cout<<'C';
				else if(j%2==0&&i%2==1)cout<<'.';
			}
			cout<<endl;		
		}
		
		}	

	return 0;
}
```


---

## 作者：YLWang (赞：1)

qwq

不明白各位大佬们为什么要写这么复杂

手玩一下

发现把所有(x + y) % 2 == 0 的点放上就是最大值啦

代码简洁

```
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num = 0, flag = 1;
    char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num * flag;
}
int n;
int main()
{
    cin >> n;
    printf("%d\n", (n * n + 1) / 2);
    For(i, 1, n) {
    	For(j, 1, n) {
    		if(i + j & 1) {
    			printf(".");
			} else {
				printf("C");
			}
		}
		printf("\n");
	}
    return 0;
}



```


---

## 作者：CobaltChloride (赞：1)

```
直接放代码!
#include<bits/stdc++.h>
using namespace std;
int n,i,j;
bool flag;//1表示放Coder,0表示不放 
int main(){
	cin>>n;
	cout<<(n*n+1)/2<<endl;
	/*
	方案应总是填满棋盘中的同一颜色格
	n%2==0时:(Ex:n=4)
	C.C.
	.C.C
	C.C.
	.C.C
	可得可放n*n/2(对于偶数的n等同于(n*n+1)/2)个
	n%2!=0时:(Ex:n=5)
	C.C.C
	.C.C.
	C.C.C
	.C.C.
	C.C.C
	可得可放(n*n+1)/2个
	所有情况皆如此 
	*/
	//接下来打印
	flag=true;//先打C
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(flag) putchar('C');
			else putchar('.');
			flag=!flag;
		}
		if(n%2==0) flag=!flag;//n为偶数时要再变一次 
		cout<<endl;//别忘换行
	}
	return 0;
}
```

---

## 作者：CSPJ10pts (赞：0)

## 题目描述
Iahub 很喜欢下棋。他甚至发明了一种棋子叫做 "Coder"。

一个 Coder 可以攻击与它相邻的格子中的棋子（水平和竖直方向）。如果一个 Coder 在坐标 $(x,y)$上，它可以攻击 $(x+1,y)$ , $(x-1,y)$ , $(x,y+1)$ , $(x,y-1)$ 这四个格子。

Iahub 想要知道有多少个 Coder 可以被放在 $n \times n$ 的棋盘中，使得任意两个 Coder 都不能互相攻击。

## 分析

由于一个 Coder 可以攻击它上下左右的四个格子，我们只要像围棋棋盘一样间隔放置 Coder 就可以使他们不互相攻击了。

那么最多放几个 Coder 呢？根据我们的上面的推断，每个 $2 \times 2$ 的格子里最多放 $2$ 个 Coder，那么我们把棋盘每 $2 \times 2$ 个格子分为一组，就可以快速统计出最多可以放多少个 Coder 了。

+ 当 $n$ 为偶数的时候，Coder 总数为：$n \times n \div 4 \times 2 = n \times n \div 2$；

+ 当 $n$ 为奇数的时候，Coder 总数为：$(n - 1) \times (n - 1) \div 4 \times 2 + n $，简化一下就是：$(n \times n + 1) \div 2$；

至于输出，当 $i + j$ 是奇数就输出 $\tt{C}$，不然输出 $\tt{.}$。

## 代码

（混乱的三目运算）

```
#include <iostream>
using namespace std;
long long n;
int main() {
    cin >> n;
    if (n % 2 == 0) {
    	cout << n * n / 2 << endl;
    	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cout << ((i + j) % 2 ? "." : "C") << (j == n ? "\n" : "");
    }
    else {
    	cout << (n * n + 1) / 2 << endl;
    	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cout << ((i + j) % 2 ? "." : "C") << (j == n ? "\n" : "");
    }
    return 0;
}
```

[通过记录~](https://www.luogu.com.cn/record/103300331) 

---

## 作者：DANIEL_x_ (赞：0)

## 思路：
构造题

我们可以找规律：分奇数和偶数两种情况。

奇数：我们摆的方式是第一行 $\frac{(n+1)}{2}$，第二行 $\frac{(n-1)}{2}$，以此类推，一共能放 $\frac{n \times n+1}{2}$。

偶数：同理，每行都是有 $\frac{n}{2}$ 个，所以一共是 $\frac{n \times n}{2}$。

要注意输出格式，不要输出成 $0,1$。

## code:
```cpp
include<bits/stdc++.h>
using namespace std;
int main()
{
   int n;
   cin>>n;
   if(n%2==0){
       cout<<n*n/2<<endl;
       for(int i=1;i<=n;i++){
           if(i%2==1){
               for(int i=1;i<=n/2;i++) cout<<".C";
           }
           else{
               for(int i=1;i<=n/2;i++) cout<<"C.";
           }
           cout<<endl;
       }
    }
    else{
       cout<<(n*n+1)/2<<endl;
       for(int i=1;i<=n;i++){
           if(i%2==1){
               for(int i=1;i<=n/2;i++) cout<<"C.";
               cout<<"C";
           }
           else{
               for(int i=1;i<=n/2;i++) cout<<".C";
               cout<<".";
           }
           cout<<endl;
       }
   }
   return 0;//华丽结束
}//禁止抄袭

```


---

## 作者：HuZHUNZHUN (赞：0)

**本蒟蒻的第四篇题解QAQ**

本题思路：

既然任意两个棋子不能相邻，那么斜着放显然是最好的方法。

显然：

当 $n$ 为奇数时，最多放置棋子 $(n \times n+1)/2$ 个。

当 $n$ 为偶数时，最多放置棋子 $(n \times n)/2$ 个。

最后：

由于最优方案是奇数行奇数个和偶数行偶数个放置，因此如果行列模二同余，就摆放一颗棋子。

无注释代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	cout<<(n*n+1)/2<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i%2==j%2) cout<<"C";
			else cout<<".";
		}
		cout<<endl;
	 } 
	return 0;
}
```


---

## 作者：零殇 (赞：0)

暴力解决一切（雾）

首先，我们要判断怎么让$n*n$的$Coder$的总数最大。

我们先分成奇数与偶数的情况。



------------


### 奇数的情况（例：$n==3$）

| C | . |  C|
| -----------: | -----------: | -----------: |
| . |  C|  .|
|  C|  .|  C|

### 或

|  .| C |  .|
| -----------: | -----------: | -----------: |
| C | . | C |
| . | C | . |

明显是上面的总和最大，因此奇数情况下我们选择$(1,1)$为开头。



------------


### 偶数的情况（例子：$n==2$）
| C | . |
| -----------: | -----------: |
| . | C |

### 或

| . | C |
| -----------: | -----------: |
| C | . |

明显两个总和没有区别，因此我们也可以选择$(1,1)$为开头。



------------


综合起来，不论奇偶，我们都可以以$(1,1)$为开头。

也就是坐标为$(奇,奇)$或$(偶,偶)$的地方放$Coder$。

所以，设当前坐标$(x,y)$，则$x+y$为偶数时可以放置$Coder$。

快乐地开始我们的暴力吧！（雾）

上代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
	int n;
	cin>>n;
	if(n%2==0)//n为偶数时 
		cout<<n/2*n<<endl;
	else//n为奇数时 
		cout<<(n/2+1)+n/2*n<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)%2==0)//判断能否放置 
				cout<<'C';
			else
				cout<<'.';
		}
		cout<<endl;
	}
	return 0;
}
```

完结撒花~

---

