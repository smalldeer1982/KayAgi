# Same Parity Summands

## 题目描述

You are given two positive integers $ n $ ( $ 1 \le n \le       10^9 $ ) and $ k $ ( $ 1 \le k \le 100 $ ). Represent the number $ n $ as the sum of $ k $ positive integers of the same parity (have the same remainder when divided by $ 2 $ ).

In other words, find $ a_1, a_2, \ldots, a_k $ such that all $ a_i>0 $ , $ n = a_1 + a_2 + \ldots + a_k $ and either all $ a_i $ are even or all $ a_i $ are odd at the same time.

If such a representation does not exist, then report it.

## 样例 #1

### 输入

```
8
10 3
100 4
8 7
97 2
8 8
3 10
5 3
1000000000 9```

### 输出

```
YES
4 2 4
YES
55 5 5 35
NO
NO
YES
1 1 1 1 1 1 1 1
NO
YES
3 1 1
YES
111111110 111111110 111111110 111111110 111111110 111111110 111111110 111111110 111111120```

# 题解

## 作者：ADay (赞：6)

这题无疑就是分几个类，如下：
### Case1
可以分成$k$个奇数  
那么我们就可以把$n$分成$\begin{matrix}\underbrace{1+1+\cdots+1}\\k\text{个1}\\+(n-k+1)\end{matrix}$ ,
判断$n-k+1$的奇偶性即可  
### Case2
可以分成$k$个偶数  
那么我们就可以把$n$分成$\begin{matrix}\underbrace{2+2+\cdots+2}\\k\text{个2}\\+(n-2k+2)\end{matrix}$ ,
判断$n-2k+2$的奇偶性即可 
### Case3
上述情况都不符合，输出$\mathcal{NO}$  
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

inline void readint(int &x)
{
    int f=1;x=0;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    x*=f;
}

int t,n,k;

int main()
{
    readint(t);
    while(t--)
    {
        readint(n),readint(k);
        if(((n-k+1)&1)&&n>=k)
        {//Case1
            puts("YES");
            for(int i=1;i<k;i++)printf("1 ");输出k-1个1
            printf("%d\n",n-k+1);
            continue;
        }
        if(((n-2*k+2)&1)||n<=2*k-2)//判断不能执行Case2
        {
            puts("NO");//输出NO
            continue;
        }
        puts("YES");
        for(int i=1;i<k;i++)printf("2 ");//输出k个2
        printf("%d\n",n-2*k+2);
    }
    return 0;
}
```
### ~~奇~~技~~淫~~巧
判断$\bmod 2$我们可以使用`&1`位运算，即判断二进制下$n$的最后一位是否为$1$，本质和奇偶性是一样的

---

## 作者：chenyilai (赞：3)

根据题意，我们有两种选择：

1. 把 $n$ 拆分成 $k$ 个奇数。
1. 把 $n$ 拆分成 $k$ 个偶数。

我们一个个进行分析：

选择1有两个条件：
1.  $n>k$
1. 我们将前面的 $k-1$ 个数都设置为 $1$，则最后一个数肯定是 $n-(k-1)$，且这个数是奇数。

代码：
```cpp
if (n>=k&&(n-(k-1))%2==1){
	printf("YES\n");
	for (int i=0;i<k-1;i++) printf("1 ");
	printf("%lld\n",n-(k-1));
}
```

选择2和选择1类似：
1. $n>2k$（因为偶数最小是 $2$）
1. 我们将前面的 $k-1$ 个数都设置为 $2$，则最后一个数肯定是 $n-2(k-1)$，且这个数是偶数。

代码：
```
if (n>=k*2&&(n-2*(k-1))%2==0){
	printf("YES\n");
	for (int i=0;i<k-1;i++) printf("2 ");
	printf("%lld\n",n-2*(k-1));
}
```
如果两个选择都不符合条件，则输出`NO`，这里建议大家使用if语句的嵌套。

---

## 作者：船医 (赞：2)

是随便输的话

就想到
### 输出k-1个1或2，再判断剩下数是奇数还是偶数。

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,a,b,c;
int main() {
	cin>>t;
	for(int i=1; i<=t; i++) {
		cin>>n>>k;
		if(n%k==0) {
			a=n/k;
			cout<<"YES"<<endl;
			for(int j=1; j<=k; j++) {
				cout<<a<<" ";
			}
			cout<<endl;
		}//特判，其实没必要，只是没删之前的
		else {
			if((n-((k-1)*2))%2==0&&n-((k-1)*2)>0) {
				cout<<"YES"<<endl;
				for(int j=1; j<=k-1; j++) {
					cout<<2<<" ";
				}
				cout<<n-((k-1)*2)<<endl;//全偶
			}
			else {
				if((n-(k-1))%2!=0&&n-(k-1)>0) {
					cout<<"YES"<<endl;
					for(int j=1; j<=k-1; j++) {
						cout<<1<<" ";
					}
					cout<<n-(k-1)<<endl;//全奇
				}
				else
				{
					cout<<"NO"<<endl;//都不符合
				}
			}
		}
	}
	return 0;
}
```
大家加油！

---

## 作者：小恐 (赞：2)

这是史上第一次Div.4!

~~话说好像好水的样子啊~~

------------
说正事：

题意：求出能否将$n$分成$k$个奇偶性相同的正整数，如果能，输出任意一种方法。

按$n$与$k$的奇偶性分类：

+ 当$n\equiv1\pmod{2}$且$k\equiv0\pmod{2}$时，不管是$k$个奇数还是$k$个偶数和都是偶数。所以输出$-1$。

+ 当$n\equiv0\pmod{2}$且$k\equiv0\pmod{2}$时，都是奇数或都是偶数都可以。因为奇数也就是全是$1$最小，所以取奇数。如果$n<k$，则无论如何满足不了，输出$-1$，否则先把$k$个数都设为$1$，这是和一定是偶数，每次如果不够就在最后加$2$，直到和为$k$时为止。其实就可以先把前$(k-1)$个数设成$1$，最后一个数为$(n-k+1)$。

+ 当$n\equiv1\pmod{2}$且$k\equiv1\pmod{2}$时，这时必须所有数取奇数。同样的，如果$n<k$，则无论如何满足不了，输出$-1$，否则先把前$(k-1)$个数设成$1$，最后一个数为$(n-k+1)$。

+ 当$n\equiv0\pmod{2}$且$k\equiv1\pmod{2}$时，此时必须所有数取偶数，如果$n<2\times k$，则无论如何满足不了，输出$-1$，否则先把前$(k-1)$个数设成$2$，最后一个数为$(n-2\times k+2)$。

说完了，上代码：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
void read(int &x)
{
	x=0;
	int bei=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			bei=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=bei;
}
int main()
{
	int t,n,k;
	read(t);
	while(t--)
	{
		read(n),read(k);
		if(n%2==1&&k%2==0)
		{
			puts("NO");
			continue;
		}
		if(n%2==1&&n<k)
		{
			puts("NO");
			continue;
		}
		if(n%2==0&&k%2==0&&n<k)
		{
			puts("NO");
			continue;
		}
		if(n%2==0&&k%2==1&&n<k*2)
		{
			puts("NO");
			continue;
		}
		puts("YES");
		if(n%2==0&&k%2==1)
		{
			for(int i=1;i<k;++i)
				printf("2 ");
			printf("%d\n",n-2*(k-1));
		}
		else
		{
			for(int i=1;i<k;++i)
				printf("1 ");
			printf("%d\n",n-(k-1));
		}
	}
	return 0;
}
```
感谢阅读！~~点个赞再走呗~~

---

## 作者：cherish_ (赞：2)

主体思路：对于n能由k个奇数相加得到的情况，输出 k-1 个 1 和 n-k+1 即可；对于n能由k个偶数相加得到的情况，输出 k-1 个 2 和 n-2*（k-1） 即可。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t, n, k;
int read() {
	char c = getchar();
	int x = 0, f = 1;
	for (; !isdigit(c); c = getchar())
		if (c == '-')
			f = -1;
	for (; isdigit(c); c = getchar())
		x = x * 10 + c - 48;
	return x * f;
}
int main() {
	t = read();
	while (t--) {
		n = read(), k = read();
		if (n < k)//n<k时显然不能
			printf("NO\n");
		else if (n == k) {//n=k时，k个1相加得到n
			printf("YES\n");
			for (int i = 1; i <= k; ++i)//输出k个1即可
				printf("1 ");
			printf("\n");
		}
		else if (n % 2 == 0) {//n为偶数
			if (n >= k*2) {//如果2*k<=n，则输出k-1个2和n-2*（k-1）即可
				printf("YES\n");
				for (int i = 1; i <= k - 1; ++i)
					printf("2 ");
				printf("%d\n", n - 2 * (k - 1));
			}
			else {//对于2*k>n
				if (k & 1)//如果k是奇数，则不能（奇数个奇数的和只能为奇数）
					printf("NO\n");
				else {//k为偶数，偶数个奇数的和为偶数
					printf("YES\n");
					for (int i = 1; i <= k - 1; ++i)
						printf("1 ");
					printf("%d\n", n - k+1);
				}
			}
		}
		else {//n为奇数
			if (k%2== 0)//k为偶数显然不能
				printf("NO\n");
			else {//k为奇数，输出k-1个1和n-k+1即可
				printf("YES\n");
				for (int i = 1; i <= k - 1; ++i)
					printf("1 ");
				printf("%d\n", n - k + 1);
			}
		}
	}
	return 0;
}
```

---

## 作者：Tiago (赞：1)

## 题意简述

给你两个数 $n,k$，问：能否把 $n$ 分解为 $k$ 个奇偶性相同的**正整数**的和。

共 $T$ 组数据。

## 题目分析

分类讨论。

**情况 $1$：$n<k$**

没啥可讲的，毕竟输出的数最小为 $1$，所以直接输出 `NO` 即可。

**情况 $2$：$n \ge k$**

这里又分奇偶两种。

**全是奇数：**

既然全是奇数，那就不妨假设前 $k-1$ 个数全是 $1$，然后判最后一个数的奇偶性即可。

**全是偶数：**

同奇数的方法一样，假设前 $k-1$ 个数全是 $2$，然后判最后一个数的奇偶性即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
void print_YES(int x,int k,int n)//输出YES
{
	puts("YES");
	for(int i=1;i<k;i++)cout<<x<<" ";
	cout<<n<<endl;
}
void print_NO()//输出NO
{
	puts("NO");
}
inline int read()
{
	register int x=0,f=0;register char ch=getchar();
	while(ch<'0' || ch>'9')f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
void work()
{
	n=read(),k=read();
	if(n<k)//情况1
	{
		print_NO();
		return ;
	}
	//情况2
	if((n-k+1)%2==1 && (n-k+1)>0)//奇数
	{
		print_YES(1,k,n-k+1);
		return ;
	}
	if((n-(k-1)*2)%2==0 && (n-(k-1)*2)>0)//偶数
	{
		print_YES(2,k,n-(k-1)*2);
		return ;
	}
	print_NO();
}
int main()
{
	int t=read();
	while(t--)work();

	return 0;
}
```

---

## 作者：do_while_true (赞：1)

![兔队原话](https://s1.ax1x.com/2020/05/10/Y1LUaV.png)

如果 $n$ 和 $k$ 奇偶性相同，则输出 $1,1,1,1,1...x$，共 $k-1$ 个 $1$ ，$x=n-(k-1)$，因为 $n,k$ 奇偶性相同，则 $x=n-(k-1)$ 一定为奇数，如果 $n<k$ （$x\leq 0$）就无解

如果 $n$ 和 $k$ 奇偶性不同，则输出 $2,2,2,2,2...x$，共 $k-1$ 个 $2$ ，$x=n-(k-1)*2$，因为 $n,k$ 奇偶性不同，则 $x=n-(k-1)*2$ 一定为偶数，如果 $n<k*2$ （$x\leq 0$）则无解。

特别注意，因为偶数个数加起来一定是偶数，所以 $n$ 为奇数并且 $k$ 为偶数则无解。

[$\mathcal{Code}$](https://codeforces.com/contest/1352/submission/79510127)

---

## 作者：b6e0_ (赞：1)

打完CF又来写题解啦~求兹磁qwq（第一次AK CF比赛）

[CF题面传送门](https://codeforces.com/contest/1352/problem/B) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1352B) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1352B)

仍然感觉有点复杂。。。欢迎大佬爆踩

分情况讨论。
## 一.如果$n$为奇数

此时可以通过输出$k-1$个$1$和一个$n-k+1$来构造。特判$n<k$，输出NO。

## 二.如果$n$为偶数

此时仍然可以输出$k-1$个$1$和一个$n-k+1$来构造，但是$k$必须要为偶数且$n\ge k$（读者自证不难）。如果$k$为奇数，可以输出$k-1$个$2$和一个$n-(k+1)\times2$，特判$n<k\times2$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,k,i;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(n&1)//n为奇数，位运算更快
			if((k&1)&&n>=k)//注意要判n>=k
			{
				cout<<"YES\n";
				for(i=1;i<k;i++)//这里是循环k-1次
					cout<<"1 ";
				cout<<n-k+1<<endl;
			}
			else
				cout<<"NO\n";
		else//n为偶数
			if(n>=k&&!(k&1))//注意要判n>=k
			{
				cout<<"YES\n";
				for(i=1;i<k;i++)
					cout<<"1 ";//这里是循环k-1次
				cout<<n-k+1<<endl;
			}
			else
				if(n>=k*2)//注意要判n>=k*2
				{
					cout<<"YES\n";
					for(i=1;i<k;i++)//这里是循环k-1次
						cout<<"2 ";
					cout<<n-(k-1)*2<<endl;
				}
				else
					cout<<"NO\n";
	}
	return 0;
}
```
时间复杂度为$O(tk)$。

---

## 作者：james1BadCreeper (赞：0)

因为要求这 $k$ 个数要么都被 $2$ 整除，要么都不被 $2$ 整除，所以我们可以分别试这两种情况，但如何构造这 $k$ 个数呢？

在此以奇数举例，偶数同理。  
先假定 $2 \nmid a_i$，若 $a_u$ 加上 $m(2\mid m)$，则可将 $a_v(u\not=v)$ 减掉 $m$，不会对结果造成任何影响。所以可以令前 $k-1$ 个数为最小正奇数 $1$（这样做可以最大程度避免最后一个数变成负的），计算最后一个数是否可以成立。

code：
```cpp
#include<iostream>
#include<cstdio>
 
using namespace std;
 
int main(void)
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        if(k>n) puts("NO");//直接特判
        else
        {
			//偶数
            int ans=((k-1)<<1);
            int last=n-ans;
            if(last>0&&(last&1)==0)
            {
                puts("YES");
                for(register int i=1;i<k;++i)
                    printf("2 ");
                printf("%d\n",last);
            }
            else
            {
            	//奇数
                ans=k-1;
                int last=n-ans;
                if(last>0&&(last&1))
                {
                    puts("YES");
                    for(register int i=1;i<k;++i)
                        printf("1 ");
                    printf("%d\n",last);
                }
                else puts("NO");   
            }
        }
    }
    return 0;
}
```

---

