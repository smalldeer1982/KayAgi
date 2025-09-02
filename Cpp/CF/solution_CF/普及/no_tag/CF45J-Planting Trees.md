# Planting Trees

## 题目描述

Vasya is a Greencode wildlife preservation society proponent. One day he found an empty field nobody owned, divided it into $ n×m $ squares and decided to plant a forest there. Vasya will plant $ nm $ trees of all different heights from $ 1 $ to $ nm $ . For his forest to look more natural he wants any two trees growing in the side neighbouring squares to have the absolute value of difference in heights to be strictly more than 1. Help Vasya: make the plan of the forest planting for which this condition is fulfilled.

## 样例 #1

### 输入

```
2 3
```

### 输出

```
3 6 2
5 1 4
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
-1
```

# 题解

## 作者：zct_sky (赞：5)

### Solution:
-----
如果总数不足 5 个（不包括 $n=m=1$ 的情况），一定是无法放的，输出 $-1$。

否则，就将大数和小数交叉放即可（大数范围为 $\dfrac{n\times m}{2}+1\to n\times m$，小数范围为 $1\to \dfrac{n\times m}{2}$）。

### Code:
-----
```c++
#include<bits/stdc++.h>
using namespace std;
int n,m; 
int main(){
    cin>>n>>m;
	if(n+m<5&&(n!=1||m!=1)){
		cout<<-1;
		return 0;
	}
	int l=1,b=n*m/2+1;
	for(int i=0;i<n;i++,puts(""))
	    for(int j=0;j<m;j++,putchar(' '))
	        if((i+j)%2) cout<<l++;
	        else cout<<b++;
    return 0;
}

```

---

## 作者：DecemberFox (赞：2)

# CF45J Planting Trees 题解

## 题目分析

本题的大致意思就是将 $1$ 至 $n\times m$ 放入一个 $n\times m$ 的矩阵中，使任意两格四联通相邻的数字的差的绝对值大于 $1$，如果无法满足则输出 $-1$。

## 解法分析

依次将 $1$ 至 $n\times m$ 放入矩阵中，因为绝对值大于 $1$ 的限制，放置数字时需要每次隔开 $1$ 格。

将数字分为两组，第一组从 $1$ 至 $\lfloor\frac{n\times m}{2}\rfloor$，第二组从 $\lfloor\frac{n\times m}{2}\rfloor+1$ 至 $n\times m$，这样就不用将构造的矩阵存下来再输出了。

如果我们将数字 $1$ 放在矩阵的第 $1$ 行，第 $1$ 列，就会发现连样例都无法通过，因为不能与数字 $1$ 相邻的数字只有 $2$，将 $1$ 放在中间显然比除了 $n\times m$ 的其他数字更优。

接下来考虑什么时候无法满足条件，不难发现当 $l+r<5$ 时，以最优方式构造也无法满足条件，因此输出 $-1$，不过需要特判当 $n=m=1$ 时也可以满足条件。

## 代码

```cpp
#include<iostream>
#include<cstdio>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int n(1);
		now=0;
#define isdigit(c) ((c)>='0'&&(c)<='9')
		while(!isdigit(c)){if(c=='-') n=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
#undef isdigit
		now*=n;
		read(next...);
	}
	template<typename type>
	inline void write(type num,char end='\n')
	{
		unsigned long long unum(0);
		if(num<0)
		{
			putchar('-');
			unum=-num;
		}
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
}
//以上部分为快读和快写
namespace SOLVE
{
	void solve()
	{
		int i,j,k(0),n,m,a,b;
		io::read(n,m);
		b=(n*m)/2+1;//将放入矩阵的数分为两组，第一组从 1 开始，第二组从 (n*m)/2+1 开始
		a=1;
		if(n==1&&m==1) io::write(1);           //特判
		else if(n+m<5) io::write(-1);
		else
		{
			for(i=1;i<=n;++i)
			{
				for(j=1;j<=m;++j)
				{
					if((i+j)%2) io::write(a++,' ');//判断该位置应该放那一组的数
					else io::write(b++,' ');
				}
				putchar('\n');
			}
		}
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

## 作者：xiaozeyu (赞：2)

上面的是pas的dfs卡着范围解得，不太友好

反正这道题目只要输出符合要求就行了
、

什么时候-1？

总共小于5个，没办法做到

当1 $\times $ 1时，输出1

正常情况，通过奇偶性将最大最小的数交叉填写

1. : 1 $\to$ $ \dfrac{n*m}{2} $

2. ：$ \dfrac{n*m}{2} +1$   $\to$  n $ \times $ m
 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=109;
int n,m,t1,t2=1;//t1为大数，t2 为小的数
int main()
{
	cin>>n>>m;
	if (n==m && n==1) return cout<<1,0;//特判
	if (m+n<5) return cout<<-1,0;//无法完成时
	t1=n*m/2+1;//用一半的值调大t1 
	for (int i=0;i<n;i++,cout<<'\n')
		for (int j=0;j<m;j++)
			if ((i+j)%2==0)	//通过奇偶性分开种
				cout<<t1<<" ",t1++;
			else 
				cout<<t2<<" ",t2++;
}
```


---

## 作者：naroto2022 (赞：1)

# CF45J 题解

### 原题链接：[Planting Trees](https://www.luogu.com.cn/problem/CF45J)
### 题目分析：
1. 当 $n=m=1$ 时，直接输出 $1$。

2. 当 $(n+m)>5$ 时，就将大数和小数交叉放即可。

3. 当 $(n+m)<5$ 时，是肯定是不行的，输出 $-1$。

这时就会有人问第二种情况的大小数分别是什么？

大数：$(n+m)/2\sim n\times m$。

小数：$1\sim(n+m)/2$。

也不多说了，上代码！

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m; 
int main(){
    cin>>n>>m;
	if(n+m<5&&(n!=1||m!=1)){
		cout<<-1;
		return 0;
	}
	int l=1,b=n*m/2+1;
	for(int i=0; i<n; i++){
	    for(int j=0; j<m; j++)
	        if((i+j)%2==1) cout<<l++<<' ';
	        else cout<<b++<<' ';
	    cout<<endl;//别忘了换行 
	}
    return 0;
}
//P上水印
//┭┮﹏┭┮ 
```


---

## 作者：正负君 (赞：1)


# CF45J Planting Trees 题解

# 分析
~~我提交了好几次才通过……~~  

可以根据它的奇偶性判断输出。
- 如果 $n$ 和 $m$ 都为 $1$ 的情况下，只能是 $1$，所以直接输出 $1$。
- 否则如果 $n+m>5$，也就是总数不足 $5$ 个，一定是不能放的，直接输出 $-1$。
- 否则只需要根据奇偶性来交叉输出最大和最小的数。

# 代码
接下来附上~~你们最爱的~~完整代码：
```cpp
#include<iostream>//不建议使用万能头，因为有些头文件用不到，还有可能变量名冲突，比如max、y1。
using namespace std;
int n,m,tree1,tree2;
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);     //关闭同步流以加速cin，cout输入输出速度
  cin>>n>>m;      //输入
  if(n==1&&m==1)  //第1种情况，直接输出1，退出。
  {
    cout<<1<<endl;
    exit(0);
  }
  if(n+m<5)       //第2种情况，也就是无解，直接输出-1，退出。
  {
    cout<<-1<<endl;
    exit(0);
  }
  tree1=(n*m>>1)+1;//用一半的值调大tree1，由于“>>”的优先级小，所以要用小括号括起来。
  tree2=1;
  for(int i=1; i<=n; i++)
  {
    for(int j=1; j<=m; j++)
    {
      if((i+j)%2) //第2种情况，将大数和小数交叉放即可
      {
        cout<<tree2++<<' ';
      }
      else
      {
        cout<<tree1++<<' ';
      }
    }
    cout<<endl;    //一个大循环过后，记得要换行哦！
  }
  return 0;        //完美地结束啦~记得养成好习惯~
}
```
管理大大审核辛苦啦！

---

## 作者：jxbe6666 (赞：1)

这道水题不难，跟着我的脚步慢慢来

------------
**题目分析：** 这道题我们可以不用数组，根据它的奇偶性来输出。但是我们需要两个特判：第一个就是在 n 和 m 都为一的情况下，输出一。第二个在第一个除外的情况下 $n+m<5$ 的情况下输出 -1。而在其他情况下就只要根据奇偶性来交叉填写最大最小的数。

这是一道 $\text{Special Judge}$ 的题，答案和样例不一样没关系，只要符合条件就好了。
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
int n, m;
inline int read()
{ // 快读
    int number = 0, check = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        check = ch == 45 ? -1 : 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
    {
        number = (number << 1) + (number << 3) + (ch ^ 48);
        ch = getchar();
    }
    return number * check;
}
inline void write(int X)
{ // 快输
    if (X < 0)
    {
        X = ~(X - 1);
        putchar('-');
    }
    if (X > 9)
        write(X / 10);
    putchar(X % 10 + '0');
}
int main()
{
    n = read(), m = read();
    if (n == 1 && m == 1)
    {
        putchar('1');
        I AK IOI
    }
    if (n + m < 5)
    {
        puts("-1");
        I AK IOI
    }
    int tree1 = (n * m) / 2 + 1, tree2 = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if ((i + j) % 2 == 0)
            {
                write(tree1++);
                putchar(' ');
            }else{
                write(tree2++);
                putchar(' ');
            }
        }
        putchar('\n');
    }
    I AK IOI
}

```


---

## 作者：kirky_wang (赞：1)



## 解析
我们先从最小的数字开始，比如说：$n=1$，$m=1$ 时：

显然，答案是 $1$。

根据题意，我们可以模拟出不符合条件的情况：

 $n=1$ $m=2$

 $n=1$ $m=3$

 $n=2$ $m=2$

 $n=2$ $m=1$
 
 $n=3$ $m=1$


根据观察，这 $5$ 种情况都有一个共同的特点，就是 $(n+m)<5$。

那么我们可以特判这几种情况：
```cpp

if(n==1 && m==1)
{
	cout<<1
	return 0;
}
if(n+m<5)
{
	cout<<-1;
	return 0;
}
```
剩下的情况呢，我们可以通过奇偶性将最大最小的数交叉填写。

因为题目中说任意两颗四联通相邻的树高度差的绝对值严格大于 $1$ 那么我们尽可能让相邻的数同为奇数（或偶数）。也就是通过奇偶性来分开种树。
在此，我们可以找两个数。一个为较小的数 $l$，另一个为较大的数 $r$。

答案中每个数的范围在 $1$ 到 $m \times n$ 中。
为了让答案分配得更合理，我们可以取一个中间值放在答案中矩阵的左上角。把这个值赋给大数 $(r)$。

 $r=n+m2+1$

 $n \times m2+1$

然后交叉填写：

前半部分：

 $1→n \times m2$

后半部分：

 $n \times m 2+1→n \times m$

交叉填写代码：

```cpp
r=n*m/2 + 1;
for (int i=0;i<n;i++)
{
	for (int j=0;j<m;j++)
	{
		if((i+j)%2==0)	
		{
			printf("%lld ",r);
			r++;	
		}
		else 
		{
			printf("%lld ",l);
			l++;
		}
	}		
	printf("\n");
}
```


## AC 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int ll read(){
	ll f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
ll n,m,l=1,r;
ll a[100][100];
int main()
{
	scanf("%lld%lld",&n,&m);
	if(n==1 && m==1)
	{
		cout<<1;
		return 0;
	}
	if(n+m<5)
	{
		cout<<-1;
		return 0;
	}
	r=n*m/2 + 1;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			if((i+j)%2==0)	
			{
				cout<<r<<' ';
				r++;	
			}
			else 
			{
				cout<<l<<' ';
				l++;
			}
		}		
		cout<<endl;
	}
		
	return 0;
}
```



---

