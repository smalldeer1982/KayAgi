# Add Odd or Subtract Even

## 题目描述

You are given two positive integers $ a $ and $ b $ .

In one move, you can change $ a $ in the following way:

- Choose any positive odd integer $ x $ ( $ x > 0 $ ) and replace $ a $ with $ a+x $ ;
- choose any positive even integer $ y $ ( $ y > 0 $ ) and replace $ a $ with $ a-y $ .

You can perform as many such operations as you want. You can choose the same numbers $ x $ and $ y $ in different moves.

Your task is to find the minimum number of moves required to obtain $ b $ from $ a $ . It is guaranteed that you can always obtain $ b $ from $ a $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case, you can just add $ 1 $ .

In the second test case, you don't need to do anything.

In the third test case, you can add $ 1 $ two times.

In the fourth test case, you can subtract $ 4 $ and add $ 1 $ .

In the fifth test case, you can just subtract $ 6 $ .

## 样例 #1

### 输入

```
5
2 3
10 10
2 4
7 4
9 3```

### 输出

```
1
0
2
2
1```

# 题解

## 作者：ShineEternal (赞：4)

[更佳的阅读效果。](https://blog.csdn.net/kkkksc03/article/details/104504066)

## description：
- 给定两个整数 $a,b$。
- 每次你可以将 $a$ 加上一个奇数或者减去一个偶数。
- 问你将 $a$ 变成 $b$ 的最少次数。
- **多组数据**，数据组数不多于 $10^4$， $1\le a,b\le 10^9$。
- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：
我们发现，最多进行两次操作即可达成目标，我们分别讨论 $0,1,2$ 三种情况：

- $0:$ 两个数相等。
- $1:a$ 加上一个奇数为 $b$ 或者 $a$ 减去一个偶数为 $b$。
- $2:$ 剩下的情况，因为我们总能通过一次预备操作转换为上面 $1$ 那种模型。
## code：
```cpp
#include<cstdio>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		long long a,b;
		scanf("%lld%lld",&a,&b);
		long long c=b-a;
		if(c==0)
		{
			printf("0\n");
			continue;
		}
		if(c<0)
		{
			c=-c;
			if(c%2==1)
			{
				printf("2\n");
			}
			else
			{
				printf("1\n"); 
			}
		}
		else
		{
			if(c%2==1)
			{
				printf("1\n");
			}
			else
			{
				printf("2\n");
			}
		}
	}
	return 0;
} 
```

---

## 作者：CBW2007 (赞：1)

在我的博客食用效果更佳！<https://www.cbw2007.tk/articles/CF-624-div3-A-sol/>

咱们先稍微转一下，加上正奇数就改变了一个数的奇偶性，反之不变；而差为奇数说明两个数之间奇偶性不同，反之相同；另外，由于每次操作数字不限制，要多少有多少，所以我们的问题只剩下奇偶性问题。

再理一下情况：（有个typo，请见谅）

![](https://cdn.luogu.com.cn/upload/image_hosting/rbfx9ai7.png)

1. 这还用说嘛
2. 因为减法操作不会改变奇偶性，然而两数奇偶性不同，就要先把a减到$b-1$（$b-1$与a奇偶性相同，其实不一定减1，减任意一个奇数都行），再加个1（减多少，加多少）
3. 因为减法操作不会改变奇偶性，而且两数奇偶性相同，就直接把a减到b
4. 因为加法操作会改变奇偶性，而且两数奇偶性不同，就直接把a加到b
5. 因为加法操作会改变奇偶性，而加到b以上后两数之差为奇数，可是只能减偶数，无解

怎么样，是不是像极了数学里令人~~作呕~~着迷的分类讨论呢？

最后，上核心代码！

```cpp
if (a==b)
	cout<<0;
else if (a<b)
{
	if ((b-a)%2==0)
//		cout<<2; 这里一开始没考虑到无解，但是AC了o_O，大家自己改一改吧
	else
		cout<<1;
}
else /*(a>b)*/
{
	if ((b-a)%2==0)
		cout<<1;
	else
		cout<<2;
}
cout<<endl;//最后统一换行，减少码量
```

---

## 作者：huayucaiji (赞：1)

## [A. Add Odd or Subtract Even](https://codeforces.com/contest/1311/problem/A)

我们考虑对于任意两个数 $a,b$

1.如果 $a> b$ 且 $(a-b)\mod 2=0$ ，那么输出 $1$  
2.如果 $a> b$ 且 $(a-b)\mod 2=1$ ，那么输出 $2$  
3.如果 $a< b$ 且 $(b-a)\mod 2=0$ ，那么无解  
4.如果 $a< b$ 且 $(b-a)\mod 2=1$ ，那么输出 $1$  
5.如果 $a=b$，输出 $0$  

这就是一道非常水的奇偶性讨论问题，是一道基础数论题，还是非常水的

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a,b;

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	cin>>n;
	while(n--) {
		cin>>a>>b;
		if(a==b) {
			cout<<0<<endl;
		}
		else if(a>b) {
			if((a-b)%2==0) {
				cout<<1<<endl;
			}
			else {
				cout<<2<<endl;
			}
		}
		else if(a<b) {
			if((b-a)%2==1) {
				cout<<1<<endl;
			}
			else {
				cout<<2<<endl;
			}
		}
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```

---

## 作者：xgwpp6710 (赞：0)

我们分析一下题目。

如果 $a=b$ ，直接结束。

如果 $a>b$ 且 $a-b$ 为偶数， $1$ 次即可（$a
<b$ 且 $b-a$ 为奇数同样）

如果 $a>b$ 且 $a-b$ 为奇数，则将 $a$ 加上一个奇数再减一次偶数就行了，两次。

如果 $a<b$ 且 $b-a$ 为偶数，则加两次奇数。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,m;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		if(a==b) cout<<0<<endl;
		else if((a>b&&(a-b)%2==0)||(a<b&&(b-a)%2)) cout<<1<<endl;
		else cout<<2<<endl;
	}
	return 0;
}
```

---

## 作者：Lates (赞：0)

题意就是有数字$a$和$b$，每次可以给$a$加上一个奇数或减一个偶数。求把$a$变成$b$的最小步数。

- 分类讨论

1. $a$ < $b$ ：

若$b-a$为奇数，则只需要加上一个奇数，即可变成$b$，答案为1

若$b-a$为偶数，则只需要加上一个比$b$大2的数（这个数必为奇数）,再减去2，答案为2

2. $a$ > $b$ ：

类似的，可以推出：

若$b-a$为奇数，答案为2

蒟蒻$b-a$为偶数，答案为1

3. $a$ = $b$ :

此时$a=b$，则答案为0

综上，便可以写出$Code$ ：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline int read(){
	register int x=0,v=1,ch=getchar();
	while(!isdigit(ch)){if(ch=='-')v=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return x*v;
}
int t,a,b;
int main(){
	t=read();
	while(t--){
		a=read(),b=read();
		if(a==b)printf("0");
		else if(a<b){
			if(b-a&1)printf("1");
			else printf("2");
		}else{
			if(a-b&1)printf("2");
			else printf("1");
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Cult_style (赞：0)

这道题的思路无非是枚举

有三种情况

1. 要么是a=b

1. 要么是a>b

1. 要么是a<b

如果a=b的话，那答案肯定就是0，因为它根本不用动

如果a>b或a<b的话,就还要进行以下操作
                      
如果a>b，看看它们的差是奇数还是偶数
  
像a=5，b=2,5-2=3,3是奇数那样的话，就至少需要两次操作
  
  当然不能直接让5-3=2,3是奇数，不能相减
  
  不过，我们可以：
  - 先让5-4=1（4是偶数，只能用来相减）
  - 再让1+1=2（1是奇数，只能用来相加）
  
 再举个例子：a=7，b=5,7-5=2，2是偶数，那就直接用7-2就行了，只要进行一次操作
  
接下来就只剩a<b了，如果你可以举一反三，就不用了再看下去了
                               
如果a=2,b=6,因为题目说只能+a或-a，所以这也要进行两次操作
- 先让2+3=5（3是奇数，只能用来相加）
- 再让5+1=6（1是奇数，只能用来相加）
                               
不然的话，a=3，b=8，让a+5，只用一次操作
                               
那我们就得出了结论

a=b,要零次操作                               
a>b的，差如果是奇数，要两次操作
  
差是偶数，要一次操作

a<b的，差如果是奇数，要一次操作

差是偶数，要两次操作
                  
接着，贴上代码：
```
#include<bits/stdc++.h>
using namespace std;
int t,a,b; 
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
	    scanf("%d%d",&a,&b);
	    if(a==b){
	        printf("%d\n",0);
		continue;
	    }
	    if(a>b){
	        int x=a-b;
		if(x%2==1)printf("%d\n",2);
		if(x%2==0)printf("%d\n",1);
		continue;
	    }
	    int y=b-a;
	    if(y%2==0) printf("%d\n",2);
	    else printf("%d\n",1);
	}
	
	return 0;
}
```


---

## 作者：gyh20 (赞：0)

做一点简单的分类讨论。

如果 $a=b$ 则输出 $0$。（已经相等）

如果 $a<b$ 且 $b-a \equiv 0 \pmod 2$ 众所周知，一个大于 $0$ 的偶数可以拆为两个奇数的和，所以需要两次。

如果 $a<b$ 且 $b-a \equiv 1 \pmod 2$ 只要给 $a$ 加上 $b-a$ 即可。

如果 $a>b$ 且 $a-b \equiv 0 \pmod 2$ 只要给 $a$ 减去 $a-b$ 即可。

如果 $a>b$ 且 $a-b \equiv 1 \pmod 2$ 只要给 $a$ 减去 $a-b-1$ 再加上 $1$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int t,n,a,b,c,d;
int main(){
	t=read();
	while(t--){
		a=read();b=read();
		if(b>a){
			if((b-a)%2==1)puts("1");
			else puts("2");
		}
		else if(b==a)puts("0");
		else{
			if((b-a)%2==0)puts("1");
			else puts("2");
		}
	}
}
```


---

## 作者：leoair (赞：0)

# Add Odd or Subtract Even

题目大意:给定整数$a$和$b$，然后你可以对$a$进行$2$种修改:

​				$choose 1$:把$a$加上一个任意的奇数$x(x \geq 0)$。

​				$choose2$:把$a$减去一个任意的偶数$y(y \geq 0)$。

​				请问，把$a$转换成$b$需要进行多少次修改？

这道题其实就是找规律。

我们先研究一组样例:

```
输入:
5
2 3
10 10
2 4
7 4
9 3
```

```
输出:
1
0
2
2
1
```

这个样例有$5$个测试数据。

第$1$个测试数据:$a=2,b=3$,$a$和$b$只需要进行$1$次第$1$种修改即可。

第$2$个测试数据:$a=10,b=10$,$a$和$b$相等，不需要修改。

第$3$个测试数据:$a=2,b=4$,$a$和$b$差值为偶数，因此要进行$2$次第$1$种修改。

第$4$个测试数据:$a=7,b=4$,$a$比$b$大，并且$a$和$b$差值为奇数，因此要进行$1$次第$1$种修改和$1$次第$2$种修改。

第$5$个测试数据:$a=9,b=3$,$a$比$b$大，并且$a$和$b$差值为偶数，因此只需要进行$1$次第$2$种修改即可。

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define ll long long
using namespace std;

ll t;

inline ll read(){
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

inline void work(){
	t = read();								//有t组测试数据 
	for (; t; t--){							//等同于while(t--) 
		ll a = read(), b = read();			//输入a和b 
		if (a == b){						//特判，如果相等输出0 
			puts("0");
			continue;						//跳过此循环 
		}
		if (b > a){							//如果b > a 
			if ((b - a) % 2 == 1) puts("1");//如果差为奇数，表示可以直接使用第1种修改，只需要用1次 
			else puts("2");					//否则就得使用2次第1种修改
		} else {							//如果a < b 
			if ((a - b) % 2 == 0) puts("1");//如果差为偶数，表示可以直接使用第2种修改，只需要用1次
			else puts("2");					//否则就得使用1次第1种修改和1次第2种修改 
		}
	}
}

int main(){
	work();
	return 0;
}
```



---

## 作者：Ludo (赞：0)

## Part 0. 一句话题解

根据样例分**大小**，**奇偶性**讨论即可。

## Part 1. 思考

**奇偶性**分析？ 为什么能这样想。

先把特例想了。 当 $a=b$ 时，肯定答案是 $0$，不用改变。

再看样例输出，把 $0$ 排除后，剩下 $1,2$。 嗯，奇偶性开始浮现。

分类讨论。

```
变换规则：

- 将一个正奇数 x 加到 a 上。

- 把 a 减去一个正偶数 y。

```


当 $a>b$ 时，如果 $a-b$ 是偶数，那么直接用第一条加 $2$ 次就好；相反地，如果 $a-b$ 是奇数，那么同样用第一条直接加 $1$ 次就好。样例解释可以说明。

当 $a<b$ 时，如果 $a-b$ 是偶数，那么直接用第二条减 $1$ 次就好；相反地，如果 $a-b$ 是奇数，那么加 $1$ 次，减 $1$ 次就好。样例解释同样可以说明。

## Part 2. 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int t,a,b;
int main()
{
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d",&a,&b);
		if (a==b) {printf("0\n"); continue;} //把相等判掉
		if (a<b) //看上面结论
		{
			if ((b-a)%2==1) {printf("1\n");continue;}
			else {printf("2\n");continue;} 
		}
		else //看上面结论
		{
			if ((a-b)%2==1) {printf("2\n");continue;}
			else {printf("1\n");continue;} 
		}
	}
}
```


---

