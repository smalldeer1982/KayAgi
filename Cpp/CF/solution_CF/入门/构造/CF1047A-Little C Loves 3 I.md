# Little C Loves 3 I

## 题目描述

**题目大意：**
找三个数$a,b,c$，使得$a+b+c==n$且$a,b,c$都不能被$3$整除

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 1```

## 样例 #2

### 输入

```
233```

### 输出

```
77 77 79
```

# 题解

## 作者：Marsrayd (赞：11)

$\texttt{UPD 2021.10.10}$：添加了一些 $\LaTeX$。

大家好！

今天我们来看 $\text{CF1047A Little C Loves 3 I}$ 这道大水题（如果这句话伤到了你，我表示深深的歉意）。

接下来，步入正题。

[题目传送门](https://www.luogu.com.cn/problem/CF1047A)

## 题意简述：

输出任意一组三个数 $a,b,c$，使得 $a+b+c==n$ 且 $a,b,c$ 都不能被 $3$ 整除

## $\texttt{SOLUTION}$

看到题目后，我们第一眼想到了：这不是暴力吗？太简单了！于是，我们直接枚举三个数字，符合就输出。

### 代码1.1
```
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		for(int j=1;j<n;j++)
			for(int k=1;k<n;k++)
				if(i+j+k==n&&i%3!=0&&j%3!=0&&k%3!=0)
				{
					printf("%d %d %d",i,j,k);
					return 0;
				}
}
```

什么，竟然就这么 [$\color{green}\texttt{AC}$](https://www.luogu.com.cn/record/32480374) 了？！！！

不过，我是个追求完美的人。

优化：我们发现只枚举两个数字就够了，而第三个数一定是 $n-$【前两个数】，于是我们以一个更优的代码再次 $\color{green}\texttt{AC}$ 了。

### 代码1.2
```
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	for(int j=1;j<=n;j++) 
		for(int i=1;i<=n;i++)
			if((n-j-i)%3!=0&&i%3!=0&&j%3!=0)
			{
				printf("%d %d %d",i,j,n-j-i);
				return 0;
			}
}
```

$\texttt{BUT}$，这还是太慢，~~我是个追求完美的人~~，再想想

突然，我注意到了题面所写的“任意一组”。

任意一组？

我真是智商感人啊！这不是小学数学题难度吗？

让我们继续我们的征程吧！

只需按照 $n\mod3$ 的值分类讨论即可。

第一种情况：$n\mod3=0$
```
printf("%d %d %d",1,1,n-2);
```
第二种情况：$n\mod3=1$

```
printf("%d %d %d",1,2,n-3);
```

第三种情况：$n\mod3=2$
```
printf("%d %d %d",2,2,n-4)
```
### 代码2.0
```
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	if(n%3==0)
	{
		printf("%d %d %d",1,1,n-2);
	}
	else if(n%3==1)
	{
		printf("%d %d %d",1,2,n-3);
	}
	else
	{
		printf("%d %d %d",2,2,n-4)
	}
	return 0;
} 
```

这道题终于完成了，代码改了又改，不得不说我真是一个完~~爱~~美~~慕~~主~~虚~~义~~荣~~的人啊！！！

等等，还没结束。

每题一结呢？

(⊙o⊙)？对呀。

## 每题一结

1. 此题非常考察学生的分支结构程序设计能力

2. 失败乃成功之母

3. 要追求完美，写代码要优之又优

4. 十年 $\texttt{OI}$ 一场空，不开 $\texttt{int}$ 见祖宗

5. $\color{white}\colorbox{#FAB000}{普及-}$ 难度的题不一定比 $\color{white}\colorbox{#E74C3C}{入门}$ 难



---

## 作者：Aw顿顿 (赞：2)

## 题意简述

输出三个合为 $n$ 的数：$a,b,c$。

满足以下条件：三者都不可以被 $3$ 整除。


## 分类讨论

如果 $n-2\not\equiv 0(\bmod\ 3)$，那么以下条件即可满足

$$\{a=1,b=1,c=n-2\}\in V_{sol}$$

那么我们可以判断并输出。

如果 $n-2\equiv 0(\bmod\ 3)$ ，那么必然有 $n-3\not\equiv 0(\bmod\ 3)$，所以有：

$$\{a=1,b=2,c=n-3\}\in V_{sol}$$


## 代码实现

所以就有了程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x;
int main(){
    cin>>x;
    if((x-2)%3)cout<<"1 1 "<<x-2;
    else cout<<"1 2 "<<x-3;
    putchar('\n');
    return 0;
}
```

谢谢大家。

---

## 作者：GossWandering (赞：2)

大家好
~~，我是库里的球迷~~

额。说正题，**说正题**！！

题意简述：随意输出一组$a$,$b$,$c$使$a+b+c=n$

最好想到的一组应该是$(1,1,n-2)$.

飞快打一下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<1<<" "<<1<<" "<<n-2;
}
```
哇，不愧是道入门题啊。

提交？额，瞬间打脸。第一个点就挂了。错在哪儿？

> 请思考一下，再继续往下看

不得不重新审一下题，啊，题目还有一个条件：
> $a,b,c \bmod 3≠1$

呵呵，原来是错在这啊。

那当$n-2 \bmod 3=1$ 或$n-2 \bmod 3=2$时输出$(1,2,n-2)$是没问题的。

注意此处不必化简，虽然化简也不麻烦

让我们继续我们的征程吧！

剩下一种情况，$n-2 \bmod 3=0$即$n \bmod 3=2$时，我们不得不请出我们的~~品性~~好朋友：$2$

我们也只好请$1$搬家了，突然，一个2飞过来，砸走了一。于是我们的三个数变成了$(1,2,n-3)$
此时$n-3 \bmod 3=2$,满足条件！

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    if((n-2)%3==1 || (n-2)%3==2) cout<<1<<" "<<1<<" "<<n-2;//第一种情况 
    else cout<<1<<" "<<2<<" "<<n-3;//第二种情况
}
```
$AC$！不得不承认我们很严（虚）谨（伪）

好了，总结一下：
- 此题非常考察学生的分支结构程序设计能力

- 挺好的理论分析题目（因为实现没有什么难度），建议同学们自己实践一下，分析一下

- 其实失败并不是什么坏事，只是大家不要像我这样子，提交之后才知道自己是错的，先认真读题目，拿个小本子记录一下关键句

- 随时提醒自己，需不需要开$LongLong$??尽管此题不需要，$n≤10^9int$足够应付，但你还记得2018年普及组[龙虎斗](https://www.luogu.com.cn/problem/P5016)的血案吗。

---

## 作者：moqizhu2005 (赞：0)

# 一道数论题，模拟可过
## 首先先用一个循环找a的值（a最多到n-2，因为b和c总和至少为2）
## 再用一个循环找b的值（b最多到n-a的值-1，因为c至少为1）
## 当达到要求时，就可以输出退出
#### 代码为下
```cpp
#include<iostream>
using namespace std;
long long a,b,c,n,s=0;
int main()
{
	cin>>n;
	for(int j=1;j<=n-2;j++)
	{
		for(int i=1;i<=n-j-1;i++)
			if((n-j-i)%3!=0&&i%3!=0&&j%3!=0) {a=j,b=i,c=n-j-i,s=1;break;}
		if(s==1) break;
	}
	cout<<a<<" "<<b<<" "<<c;
	return 0;
}
```


---

## 作者：lhjy666 (赞：0)

先输个1然后再凑
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	long long n;
	scanf("%lld",&n);
	printf("1 ");
	if((n-1)%3==1) printf("2 %lld",n-3);
	else printf("1 %lld",n-2);
	return 0;
}

```

---

## 作者：CZQ_King (赞：0)

### 暴力大法好
直接找三个数字，符合就输出。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){//找第一个数字
		for(int j=1;j<n;j++){//第二个
			for(int k=1;k<n;k++){//第三个
				if(i+j+k==n&&i%3!=0&&j%3!=0&&k%3!=0){//判断是否符合条件
					cout<<i<<" "<<j<<" "<<k<<endl;//符合就输出
					return 0;//别忘了输出完要结束
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：yfct (赞：0)

## 题意
给定正整数n，要求将n拆分为3个正整数的和，使得每个正整数都不是3的倍数。

输出任意一组解即可。
## 解题思路
只需按照n%3的值分类讨论即可。签到题。
```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;
int n;
int main() {
	cin>>n;
	if(n%3==0) {
		cout<<1<<' '<<1<<' '<<n-2;
	}
	else if(n%3==1) {
		cout<<1<<' '<<2<<' '<<n-3;
	}
	else cout<<2<<' '<<2<<' '<<n-4;
	return 0;
} 
```

---

