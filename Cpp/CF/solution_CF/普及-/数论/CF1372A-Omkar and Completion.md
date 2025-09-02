# Omkar and Completion

## 题目描述

You have been blessed as a child of Omkar. To express your gratitude, please solve this problem for Omkar!

An array $ a $ of length $ n $ is called complete if all elements are positive and don't exceed $ 1000 $ , and for all indices $ x $ , $ y $ , $ z $ ( $ 1 \leq x,y,z \leq n $ ), $ a_{x}+a_{y} \neq a_{z} $ (not necessarily distinct).

You are given one integer $ n $ . Please find any complete array of length $ n $ . It is guaranteed that under given constraints such array exists.

## 说明/提示

It can be shown that the outputs above are valid for each test case. For example, $ 44+44 \neq 384 $ .

Below are some examples of arrays that are NOT complete for the 1st test case:

 $ [1,2,3,4,5] $

Notice that $ a_{1}+a_{2} = a_{3} $ .

 $ [1,3000,1,300,1] $

Notice that $ a_{2} = 3000 > 1000 $ .

## 样例 #1

### 输入

```
2
5
4```

### 输出

```
1 5 3 77 12
384 384 44 44```

# 题解

## 作者：Vct14 (赞：2)

### 题意

构造一个由 $n$ 个整数组成的数列 $A$，使得对于所有 $i,j,k$，$A_i+A_j\neq A_k$。有多组测试数据。

### 思路

#### 思路 $1$

因为奇数加奇数等于偶数，所以输出任意奇数即可。

但是注意，从「说明/提示」中的第 $2$ 个错误示范中，可以知道 $A_i\le1000$，因此若 $n>500$，输出 $2$ 次即可。

#### 思路 $2$

因为 $1+1=2$，且 $2\neq1$，所以全部输出 $1$ 即可。

#### 思路 $2.5$

再深入思考一下，因为 $a+a=2a\neq a$，所以只用输出一个不大于 $1000$ 且不为 $0$ 的随机数即可。

### 代码

#### 思路 $1$

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		if(n>500){
			for(int i=1,j=1; i<=500; i++,j+=2) cout<<j<<" ";;
			n-=500;
		}
		for(int i=1,j=1; i<=n; i++,j+=2) cout<<j<<" ";
		cout<<"\n";
	}
	return 0;
}
```

#### 思路 $2$

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1; i<=n; i++) cout<<"1 ";
		cout<<"\n";
	}
	return 0;
}
```

#### 思路 $2.5$

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int out=rand()%1000+1;
        for(int i=1; i<=n; i++) cout<<out<<" ";
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：chenwenda316 (赞：1)

#### 思路
第一题明显是一道~~水题~~基础题，首先题目中说
$a_x+a_y\ne a_z$ 也就是说数组中任何两个数相加不等于任何一个数。   

于是，我们就可以输出 $n$ 个 $1$ 就可以了。  

但是，由于我~~闲的~~善于思考，就有了另一个思路：

众所周知，任何两个奇数相加都等于偶数，所以，如果数列里只有奇数就不会有 $a_x+a_y\ne a_z$ 的情况。

题目中的范围是 $n\le 1000$ ，$a_i \le 1000$ ,所以每个奇数都输出两遍就可以了。

#### 代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		int j=1;
		while(1){
			
			if(n){
				printf("%d ",j);
			}else{
				break;
			} 
			n--;
			if(n){
				printf("%d ",j);
			}else{
				break;
			}
			n--;
			j+=2;
		}
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：fisheep (赞：1)

## 想法:

首先题目中$a_x+a_y \neq a_z$ 表示数组中任意两数的和相加比不等于任何一个数组中的数，然后题中又说到数组中可以有**相同**的数出现，想法就是只要数组中相同的数尽可能的多，那么就越容易满足题目要求。

所以只需要满足：输出相同的数($1$)即可。

## Code:
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1e5+7;

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int t,n;
int main() {
   t=read();
	for(int i=1;i<=t;i++){
          n=read();
		for(int i = 1; i <= n; i++)
			printf("1 ");
				puts("");
	}
}
```

---

## 作者：xrdrsp (赞：1)

# Main Idea

给你一个整数 $n$，尝试找出任意一个长度为 $n$ 的”完整“的数组 $a$。如果一个数组所有的元素都是整数、都不超过 $1000$，而且对于下标 $x, y, z$，满足：

$$
a_x + a_y \neq a_z
$$

则这个数组被称为”完整“的数组。

# Analysis

我们很容易地发现，暴力地枚举所有可能是不可行的。而 CF div.2 的第一题一般不考察算法。对于这一题，您可以找到通过某种方法找到的满足任何条件的解。这样比较方便且省时间。

若 $a$ 中所有元素都相等， 即 $a_1 = a_2 = \cdots = a_n$。这时，对于任意三个下标 $p, q, r$，$a_p + a_q = 2a_p = 2a_q \neq a_r$。（正整数）

所以如果我们把数组中所有数都赋值成不大于 $1000$ 的数，问题解决了！

# Code

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    int x = 0;
    while (t--) {
        std::cin >> x;                  // 输入
        while (x--) {
            std::cout << "1 ";          // 输出同样的值可以保证满足条件。
        }
        std::cout << std::endl;
    }
    return 0;
}
```

---

## 作者：yzm0325 (赞：0)

Python 七行搞定，太简便了……

很明显，要想让任意的 $a_x + a_y \neq a_z$，只要让数列里的所有数相等就可以了。也就是对于每组数据，输出 $n$ 个相等的数（代码中使用随机数）就可以了。

证明一下：假设数列里的每个数都是 $a$，那么任意的两个数一定都是 $a$，而 $a+a=2a \neq a$，所以结论是成立的。

代码：

```
import random # 随机数 randint 的库。
t = int(input())
for i in range(t): # 循环 t 次。
    n = int(input())
    rand = random.randint(1, 1000) # 抽一个随机数。
    for i in range(n): print(rand, end = ' ') # 注意 end 参数的设置！
    print() # 最后输出换行。
```


---

## 作者：Hughpig (赞：0)

来个不一样的解法。

为了让任意 $a_x+a_y\neq a_z$，我们可以用三进制的思想。

我们预处理出 $3$ 所有不超过 $1000$ 的幂。

这样做可以保证任意的两个数，假设一个是 $3^x$ ，另一个是 $3^y$，两者的和必然小于 $3^{\max(x,y)+1}$。

证明：

不妨设 $x\le y$。因此 $\max(x,y)+1=y+1$。

因为 $3^{y+1}=3\times 3^y>3^x+3^y$，因此该结论正确。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int a[7]={1,3,9,27,81,273,819};
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<n;i++)cout<<a[i%7]<<" ";
        cout<<'\n';
    }
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现当输出 $n$ 个相同的正整数时，一定满足对于任意正整数 $x$，$y$，$z$，有 $a_x+a_y \neq a_z$。  

证明过程：对于任意正整数 $k$，一定有 $k+k>k$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cout<<1<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：__LiChangChao__ (赞：0)

## 思路

题目要求一个数组 $a$，使得对于任意的 $x,y,z$（可以是一样的）有 $a_x+a_y\not=a_z$。

那么显然，当对于任意的 $i,j$ 有 $a_i=a_j$，则总有 $a_x+a_y=a_z\times 2$，符合题目要求。

说白了就是 $a$ 的**每一个元素相同**。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		while(n--)printf("1 ");\\构造a
		printf("\n"); 
	}
} 
```

---

## 作者：Microperson (赞：0)

### [题目](https://www.luogu.com.cn/problem/CF1372A)
### 解题思路：
题目中说$a_x + a_y$ $\neq$ $ a_z$ 那么我开始想到的就是**奇数加奇数等于偶数**,这样就保证了上述条件，又因为不能超过一千，输出两遍奇数就可以了。
### 新鲜出炉的code：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int T,n,a[1010];

int main(){
	scanf("%d",&T);
	while(T--){
		int cnt=0;
		int cmt=0;
		scanf("%d",&n);
		int tmp=n;
		while(n--){
			cout<<2*cnt+1<<" ";
			cmt++;
			if(cmt==tmp) break;
			cout<<2*cnt+1<<" ";
			cmt++;
			if(cmt==tmp) break;
			cnt++;
		}
		cout<<endl;
	}
	return 0;
}
```
有不当之处还请指正

---

## 作者：Midoria7 (赞：0)

只要让每个数都相同且不是零，那么结果就一定是合法的。

这道题的 SPJ 好像有点问题，同一份代码交上去一会 AC 一会 WA，如果觉得自己代码没错可以多交几遍。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++)
            printf("114514 ");
        puts("");
    }
    return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：0)

思维能力直线下降，来刷 CF 题了。

简单构造题，要求找到一个长度为 n 的数列满足 $a_i + a_j \not= a_k$ ，看起来不是很轻松，其实乱搞就行了。

最简单的做法，输出 n 个相同的数（不为 0）。这样一定有 $a_i + a_j = 2a_i \not = a_k = a_i$。

我的做法：其实跟上面差不多，输出一大堆相同的数，然后最后来个极大值。显然满足条件。

```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
const int N = 3e5;
int main() {
	int t;scanf("%d" , &t);
	while(t--) {
		int n;scanf("%d" , &n);
		for(int i = 1; i <= n; i++)
			printf("1 ");//输出 n 个相同的数
		puts("");
	}
}
```


---

## 作者：Werner_Yin (赞：0)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/13286914.html)
# 题目
[传送门](https://codeforces.com/contest/1372/problem/A)
## 题意

构造一个长度为```n```的数组，对于数组中的元素```a```,```b```,```c```,满足$a+b\neq c$。

# 思路
直接让数组中的数全部变成```1```就可以了（其他数也行）。

# 代码
```cpp
/* 
	* Author :Werner_Yin 
	* Time: 2020-07-11 23:13:36
	* I believe I can AC !
*/ 
#include <bits/stdc++.h>
#define lol long long
#define GDB(x) cout<<"DATA "<<#x<<" :"<<x<<endl; 
#define mes(x) memset(x,0,sizeof(x))
using namespace std;
template <typename T>
void re(T &x){
	#define ge getchar() 
	x = 0;int sgn = 1;char ch = ge;
	for(;!isdigit(ch);ch = ge) if(ch == '-') sgn = -1;
	for(;isdigit(ch);ch = ge) x = (x<<1)+(x<<3)+(ch^48);
	x *= sgn;
}
template <typename T>
void write(T x){
	if(x == 0) putchar(48);
	else if(x < 0) putchar('-');
	int k = 0,que[20];
	while(x > 0){
		que[++k]=x % 10;
		x /= 10;
	}
	for(int i = k;i > 0;i--) putchar(que[i] + 48);
	return;
}
int main (){
	int T;
	re(T);
	while(T--){
		int n;
		re(n);
		for(int i = 0;i < n;i++) cout<<1<<" ";
		cout<<endl; 
	}
	return 0;
}
```

---

## 作者：expnoi (赞：0)

因为要使任意数的和不为另一个数，那么只要输出 $n$ 个相同的正整数，和一定不同。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cout<<"114 ";
		}
		puts("");
	}
}
```

---

