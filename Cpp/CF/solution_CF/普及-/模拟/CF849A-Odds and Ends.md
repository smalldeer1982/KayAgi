# Odds and Ends

## 题目描述

Where do odds begin, and where do they end? Where does hope emerge, and will they ever break?

Given an integer sequence $ a_{1},a_{2},...,a_{n} $ of length $ n $ . Decide whether it is possible to divide it into an odd number of non-empty subsegments, the each of which has an odd length and begins and ends with odd numbers.

A subsegment is a contiguous slice of the whole sequence. For example, $ {3,4,5} $ and $ {1} $ are subsegments of sequence $ {1,2,3,4,5,6} $ , while $ {1,2,4} $ and $ {7} $ are not.

## 说明/提示

In the first example, divide the sequence into $ 1 $ subsegment: $ {1,3,5} $ and the requirements will be met.

In the second example, divide the sequence into $ 3 $ subsegments: $ {1,0,1} $ , $ {5} $ , $ {1} $ .

In the third example, one of the subsegments must start with $ 4 $ which is an even number, thus the requirements cannot be met.

In the fourth example, the sequence can be divided into $ 2 $ subsegments: $ {3,9,9} $ , $ {3} $ , but this is not a valid solution because $ 2 $ is an even number.

## 样例 #1

### 输入

```
3
1 3 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
1 0 1 5 1
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
3
4 3 1
```

### 输出

```
No
```

## 样例 #4

### 输入

```
4
3 9 9 3
```

### 输出

```
No
```

# 题解

## 作者：Karry5307 (赞：3)

### 题意

给定一个长度为 $n$ 的序列，询问是否有一种方案将这个序列划分成奇数个子段使得每个子段的首尾都是奇数并且长度也是奇数。

$\texttt{Data Range:}1\leq n\leq 10^5$

### 题解

有些题目需要利用到一些显而易见的结论比如说奇数不等于偶数，这些结论很显然，但一做题就很容易忘记，于是写篇题解放这里提醒自己。

首先如果存在一种方案的话，注意到第一个位置一定是第一个子段的第一个位置，最后一个位置一定是最后一个子序列的最后一个位置，所以说这两个位置一定要是奇数。

其次，奇数个奇数的和是奇数，所以 $n$ 必须要是奇数。

如果满足这两个条件，由于 **$1$ 是奇数**，直接构造整个序列即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n;
ll x[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	puts((n&1)&&(x[1]&1)&&(x[n]&1)?"Yes":"No");
}
```

---

## 作者：DPair (赞：1)

## 本题难度不大，用位运算会更优秀
简单讲一下思路，由于要分成奇数个有奇数个数的子序列，根据小学数学，可以得到：

### 奇数 * 奇数 = 奇数

所以总长度一定要是奇数。

然后再判断一下首尾是不是奇数即可，用位运算$x~and~1 = x~mod~2$即可优化。
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int a[1000010], n;
int main()
{
    cin >> n;
    if(!(n & 1))
    {
        printf("No");
        return 0;
    }
    for (register int i = 1;i <= n;i ++)
    {
        cin >> a[i];
    }
    if(!(a[1] & 1) || !(a[n] & 1))
    {
        printf("No");
        return 0;
    }
    printf("Yes");
}
```

---

## 作者：lhjy666 (赞：1)

### 这题表面上看起来很难其实只要将总数量和首尾特判一下即可
### 废话不说奉上代码
```cpp
#include<cstdio>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	int a[n+10];//这样可以保证不开太小 
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	if(n%2==0)//位数特判
	{
		printf("No");
		return 0;
	}
	if(a[1]%2==0||a[n]%2==0)//首尾特判
	{
		printf("No");
		return 0;
	}
	printf("Yes");//其他直接输出Yes
	return 0;
}
```

---

## 作者：Indulge_myself (赞：0)

# 题目大意：
给你一个数列要求将它分为长度为奇数的奇数个数列，并且首尾都要为奇数。
## 题目分析：
解决这个问题其实还是需要我们的一点小学数学知识的：

1. 奇数乘奇数还是奇数。

1. 奇数个奇数相加是奇数。

1. 偶数个奇数相加是偶数。


------------
根据题目，我们知道，如果这个数列的长度是偶数的话，那么直接输出不可以即可。因为如果为偶数，那么无论怎么分，分出来的子数列数量也终将为偶数。（详情见知识 2 和 3 .）

好了，你以为这样就完了吗？

请看下面一个例子：

```
2 1 5 3 7
```
这种情况我们应该怎么办？数量为奇数，但是分不完！因为**第一个数是一个偶数**！

我们想一想，如果遇到首或尾是偶数的情况怎么办？特判！

```
if(a[0]%2==0||a[n-1]%2==0)
{
	cout<<"No"<<endl;
   return 0;
}
```
只需要加一个这样的判断就可以了。


------------
话说到这里，是不是有的小朋友又在担心：万一中间被我分成了偶数段怎么办？是不是要模拟一下？

其实，**完全不需要**。我们再来看一下题目。


------------
现在要求你把这个数列分成奇数个子数列，每个子数列都有奇数个数字，且每个数列的第一个与最后一个必须是奇数。

问你能不能做到，能做到输出是，不能则输出否。


------------
那么我们想：它自己算不算一段呢？

- 第一，1是奇数。

- 第二，只要首尾是奇数就行。

- 第三，看看长度是不是奇数。

如果上面三个条件都满足，那么直接输出不就可以了吗？


------------
## 代码：
```
#include <iostream>
#include <algorithm>
#include <cstring>
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    cin>>a[i];
    if(n%2==0)
    {
    	cout<<"NO"<<endl;
    	return 0;
	}
	if(a[0]%2==0||a[n-1]%2==0)
	{
		cout<<"NO"<<endl;
    	return 0;
	}
	cout<<"YES"<<endl;
	return 0;
}
```
码字不易，点个赞吧！

---

## 作者：Phoenix_chaser (赞：0)

## 核心：转化思想
在第一次拿到本题时其实我并没有思路，但后来一想，这是一道很好的思维题

如果可以把一个序列分成奇数个有奇数个数字的序列

那么序列总数肯定是 

**奇数×奇数**

等一等，我们发现了什么

**既然序列总数肯定是奇数，那我们如果不分它，那么分成的序列会是1个，不也是满足要求的吗？**

这也就意味着，如果一个序列满足条件，那么他的个数一定为奇数，并且前后都为奇数，如果满足不了，那么一定满足条件

所以满足的答案都是在这个条件基础上的，所以可以由此来判断本题

下面是代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
int n,a[1332341];
inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{	n=read();
	for(int i=1;i<=n;i++)	
	a[i]=read();
	if(n&1==1&&a[1]&1==1&&a[n]&1==1)
	printf("Yes");
	else 
	printf("No"); 
	return 0;
}
```

谢谢观看



---

## 作者：_cmh (赞：0)

这题是我独立思考秒切的一道题。

看到题目，说要分成奇数个子序列，我的第一反应：哦西，$1$ 就是奇数，所以不管。

而且子序列要有奇数个数，我的第一反应：哟，只要判断 $n$ 是否为奇数不久得了？

且每个数列的第一个与最后一个必须是奇数，我的第一反应：嗯，水题，切了！

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,a[101];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n%2==0||a[1]%2==0||a[n]%2==0) cout<<"No";
	else cout<<"Yes";
    return 0;
}
```

求赞！

---

## 作者：JimmyF (赞：0)

这题不难，但方法有多种，其他题解都是讲判断
$No$
的情况，我就来讲讲判断
$Yes$
的吧。

题目写得很清晰：给你一个数列
$a_1$
,
$a_2$
,
$a_3$
$……$
$a_n$
 现在要求你把这个数列分成奇数个子数列，每个子数列都有奇数个数字，且每个数列的第一个与最后一个必须是奇数。
问你能不能做到，能做到输出
$Yes$
，不能则输出
$No$
。

对于条件①：我们得知这个数列(也就是
$n$
)
的个数为奇数
$\times$
奇数
$=$
奇数。
所以说满足条件①只需要判断
$n$
是否为奇数。

对于条件②：直接判断
$a_1$
和
$a_n$
是否为奇数。

满足以上两个条件的输出
$Yes$
，
否则输出
$No$
。

所以代码如下：

```cpp
#include<bits/stdc++.h>   //万能头文件
using namespace std;
int n;
int a[100+10];  //定义
int main()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    cin>>a[i];   //读入
    if(n%2==1&&a[1]%2==1&&a[n]%2==1)  //判断是否符合两个条件
        cout<<"Yes";  //是则输出Yes
    else
        cout<<"No";   //否则输出No
    return 0; 
}
```


---

