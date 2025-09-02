# Datatypes

## 题目描述

Tattah's youngest brother, Tuftuf, is new to programming.

Since his older brother is such a good programmer, his biggest dream is to outshine him. Tuftuf is a student at the German University in Cairo (GUC) where he learns to write programs in Gava.

Today, Tuftuf was introduced to Gava's unsigned integer datatypes. Gava has $ n $ unsigned integer datatypes of sizes (in bits) $ a_{1},a_{2},...\ a_{n} $ . The $ i $ -th datatype have size $ a_{i} $ bits, so it can represent every integer between $ 0 $ and $ 2^{a_{i}}-1 $ inclusive.

Tuftuf is thinking of learning a better programming language. If there exists an integer $ x $ , such that $ x $ fits in some type $ i $ (in $ a_{i} $ bits) and $ x·x $ does not fit in some other type $ j $ (in $ a_{j} $ bits) where $ a_{i}&lt;a_{j} $ , then Tuftuf will stop using Gava.

Your task is to determine Tuftuf's destiny.

## 说明/提示

In the second example, $ x=7 $ $ (111_{2}) $ fits in $ 3 $ bits, but $ x^{2}=49 $ $ (110001_{2}) $ does not fit in $ 4 $ bits.

## 样例 #1

### 输入

```
3
64 16 32
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
4
4 2 1 3
```

### 输出

```
YES
```

# 题解

## 作者：yydfj (赞：4)

**这是本蒟蒻第十六次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你一个正整数 $n$ 和长度为 $n$ 的 $a$ 数组，问 $a$ 数组中是否有存在 $a_i$ 小于 $a_j$ 且 $a_i$ 的两倍大于 $a_j$ 的可能。

## 解法综述

因为直接暴力枚举可能会导致时间超限，所以我们可以先给 $a$ 数组进行排序。

给 $a$ 数组从小到大排好序后，我们就会发现当 $a[i]*2$ 小于 $a[i+1]$ 时，那么 $a[i]*2$ 也会小于 $a[i+1]$ 及后面的数，于是我们只需要依次判断 $a[i]$ 小于 $a[i+1]$ 且 $a[i]*2$ 大于 $a[i+1]$ 是否合法即可。

## 代码描述
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100005];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    stable_sort(a+1,a+n+1);//先给a数组进行排序
    for(int i=1;i<n;i++)
    if(a[i]<a[i+1]&&a[i]*2>a[i+1])//判断a[i]小于a[i+1]且a[i]*2大于a[i+1]是否合法
    {
        printf("YES");//如果合法则输出YES
        return 0;
    }
    printf("NO");//全部不合法则输出NO
    return 0;
}
```

---

## 作者：Larryyu (赞：3)

## _Description_
给定 $n$ 个数，问是否存在自然数 $x$，使其满足：

- $x<2^{a_i}$
- $x^2>2^{a_j}-1$
- $a_i<a_j$
## _Solution_
一道~~简单~~数学题。

设 $y \le 2^{a_i}$

$\because y^2>2^{a_j}-1$

$\therefore 2^{a_i+a_i}>2^{a_j}-1$

$\therefore a_i\times 2\geq a_j$

$\because $ 当 $a_i\times 2=a_j$ 时， $x^2 \ngeq 2^{a_i}-1 $

又 $\because x\neq a_i$

$\therefore a_i\times2\gneq a_j$

代码实现不难。

暴力枚举 $a_i,a_j$ 肯定跑不过去，先排一次序，一遍就可以枚举完。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100100];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1;i<n;i++){
        if(a[i]<a[i+1]&&a[i]*2>a[i+1]){//不要忘了条件3
            cout<<"YES";
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}
```

#### 完结撒花！！

---

## 作者：CheerJustice (赞：2)

# [点我传送](https://www.luogu.com.cn/problem/CF108B)

# solution
本题考查七下不等式知识的运用。~~数学什么的最棒了！~~

我们解原题给出的三个不等式：

> $$ x<2^{a_{i}} $$

> $$ x^{2}>2^{a_{j}}-1 $$

> $$ a_{i}<a_{j} $$

$ x $ 可以是任何自然数，不好研究，所以将一式两边平方，代入二式中消元化简，得：

> $$ 2^{2a_{i}}>x^{2}>2^{a_{j}}-1 $$

看到了吗，$ x $ 成为了一式二式连接的桥梁，我们得到了 $ a_{i} $ 与 $ a_{j} $ 之间的关系。我们移去 $ x $ 继续化简，常数 $ 1 $ 不太好看，我们使用放缩法，易证：

> $$ 2^{2a_{i}}>2^{a_{j}} $$

即：

> $$ 2a_{i}>a_{j} $$

记作四式，联立三，四两式，得： $ a_{i} <a_{j}$ 且 $ 2a_{i}>a_{j} $

这就是 $ a_{i} $ 和 $ a_{j} $ 的最终关系。如果这是数学题还要再多化简一步，但我们只要结论就好了。程序极其好写，将 $ a $ 数组升序排序，判断四式是否成立即可。

# Code:
``` c++
#include <bits/stdc++.h>
using namespace std;
inline int in(){
	char c=getchar();int f=1;int x;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
template <typename T>
inline void in(T &x){
	char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
const int N=1e5+5;
int a[N];
int main(){
    int n=in();
    for(int i=1;i<=n;in(a[i++]));
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++)
		if(a[i-1]*2>a[i]&&a[i-1]!=a[i]){
        	printf("YES\n");return 0;
    	}
    printf("NO\n");
    return 0;
}

```

---

## 作者：ZM____ML (赞：2)

因为我看其他题解对为什么只要比较 $a_i$ 和 $a_{i+1}$ 都讲的不大清楚 ~~应该是因为我太蒻了~~ 所以再来写一篇。
## 题意

给定 $n$ 个数 $a_1,a_2,...,a_n$，问是否存在自然数$x$使得满足以下条件：

$$x < 2^{a_i}$$
$$x^2 > 2^{a_j}-1$$
$$a_i < a_j$$

啊什么？这是题目翻译，让我们来简化一下。

## 题目分析

把 $x < 2^{a_i}$ 这个式子带进 $x^2 > 2^{a_j}-1$ 这个式子，我们可以得到:

$$2^{a_i+a_i} > 2^{a_j}-1$$

也就是：

$$2\cdot a_i \ge a_j$$

然后我们把 $2\cdot a_i = a_j$ 这种情况带入一下，可以发现不成立。

最后答案就是：

$$2\cdot a_i > a_j$$

式子推导出来之后，下面步骤就简单了许多。

但是，你先别急~~让我先急~~我们看一下数据范围，嗯... $n \le 10^5$。

那么我们一定是没法双重循环暴力了，那么我们可以先进行一个排序，然后将 $a_i$ 与 $a_{i+1}$ 进行比较。

根据我们推出来的式子，那么只需要判断一下 $2 \cdot a_i$ 是不是大于 $a_{i+1}$ 即可。（事实上还有一条 $a_i < a_{i+1}$ 但是我们已经排序了，所以可以不判断。）

## 代码
```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,a[N];

int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);
    for(int i=1;i<n;i++)
        if(a[i]*2>a[i+1])
            return printf("YES")&0;
    printf("NO");
    return 0;
}
```


---

## 作者：Katsura_Hinagiku (赞：2)

算是数学题吧。。

题意：给你$n$个正整数，$a_1,a_2,...,a_n$

问有没有一个数$x$使得$x < 2^{a_i}$且$x^2≥2^{a_j}$同时$a_i<a_j$

有则输出$YES$，否则输出$NO$

显然在满足$x<2^{a_i}$时，$x$越大越可能满足大于等于$2^{a_j}$的条件

当$a_i=1$时，能表示的数只有$1$,

$$1\times1=1$$

找不到满足条件的数

当$a_i>1$时，$x$最大为$2^{a_i}-1$

可利用作差比较法得出x最大时:
$$ 2 ^{2\cdot a_i-1} < x ^ 2 < 2 ^ {2 \cdot a_i}$$

因此，只要在$a_i$和$2 \cdot a_i$之间可以找到数，则可以满足条件

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;++i)
	{
		if(a[i]==1)continue;
		int pos=lower_bound(a+1,a+n+1,2*a[i])-a;
		--pos;
		if(a[pos]>a[i])//可满足条件
		{
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```
> markdown made by @serverkiller.

---

## 作者：MsgNotFound (赞：0)

# 题目思路：
给定
$$\begin{cases} x < 2^{a_i}\\x^2 > 2^{a_j}-1\\a_i < a_j\end{cases}$$
这三个条件，求满足条件的 $x$。

这里说明：我们按照从上到下给式子排序。

可以看出，将 $1$ 式子代入进 $2$ 式子，可以得到：
$ 2\times a_i\ge a_j $。

当然，我们会发现 $2\times a_i=a_j$ 不成立，所以最终的答案就是：
$$2\times a_i>a_j$$

推导完成后，我们来尝试写代码。结果发现，$2\le n \le 10^5$，不能双重枚举了，不过我们可以换一种思路，使用 `sort` 排序后，将 $a_i$ 和 $a_{i+1}$ 进行比较即可。根据我们算出来的式子，直接判断 $2\times a_i$ 是否大于 $a_{i+1}$ 就行了！ 
# code:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100005];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);//先给a数组进行排序
    for(int i=1;i<n;i++){
        if(a[i]<a[i+1]&&a[i]*2>a[i+1]){
         printf("YES");//判断正确就输出YES
         return 0;//直接结束程序，可以节约时间
         }
    }
    printf("NO");//当循环结束仍未找到合适答案则输出NO
    return 0;
}
```

---

## 作者：IkunTeddy (赞：0)

# 思路分析
这个题是个三维偏序。第三维可以直接排序优化掉，可以不看了。

第一和第二维移移项就可以推出 $2\times a_i >a_{i+1}$。

然后这个题就直接秒了。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n);
	for(int i=1;i<n;i++){
		if(a[i]<a[i+1]&&a[i]*2>a[i+1]){
			puts("YES");
			return 0;
		}
	}
	puts("NO");

	return 0;
}


```



---

## 作者：__CrossBow_EXE__ (赞：0)

一道简单的数学结论题。
# 题意
给出序列 $a$，问有没有一个数 $x$ 满足如下条件：

$\begin{Bmatrix}x < 2^{a_i} \\x^2 > 2^{a_j} -1 \\a_i < a_j\end{Bmatrix}$

# 思路
只需要将以上 3 个式子进行**化简、合并**，就能让这道题迎刃而解啦！

为了更加直观，我们按从上到下的顺序给予这 3 个式子编号。

第一步，将算式一与算式二合并：

$$({2^{a_i}})^2 > 2^{a_j}-1$$

也就是

$$2^{(2\times {a_i})}$$

第二步，对刚才的式子进一步化简，我们最终的式子就出来了：

$$2 \times a_i \ge a_j$$

不过注意一点，$2 \times a_i = a_j$ 这种情况是无法成立的，所以式子就变成了：

$$2 \times a_i < a_j$$

有了这个式子，下面就简单了——

**吗？**

# 优化
题面中，$2 \le n \le 10^5$，直接暴力寻找肯定是不行的。所以，我们肯定需要优化一下。

怎么优化呢？我们可以用排序算法实现，这样公式中的 $a_j$ 就变成了 $a_{i+1}$。

# 代码
整个题目唯一的难点就是上面的式子了，代码还是很简单的。

AC代码：

```cpp
#include<iostream>
#include<algorithm>//sort
using namespace std;
int a[100005];

bool math(int num[],int x){
	if(a[x]<a[x+1]&&num[x]*2>num[x+1]) return 1;//这是整个代码最核心的部分，公式上面已经推导过了 
	else return 0;
}

int main(){
	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	
	sort(a+1,a+n+1);//排序，为保证速度最快，用sort是最优选择
	
	for(int i=1;i<=n-1;i++){//这里的循环条件一定是i<=n-1或i<n！ 
		if(math(a,i)){
			cout<<"YES"<<endl;
			return 0;//提前结束程序 
		} 
	} 
	cout<<"NO"<<endl;//如果上面没有结束程序，说明该序列不符合条件 
	return 0;
} 
```
AC记录图片：

![](https://i.postimg.cc/fRJnwJgb/1.png)

---

