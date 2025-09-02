# Nick and Array

## 题目描述

Nick had received an awesome array of integers $ a=[a_1, a_2, \dots, a_n] $ as a gift for his $ 5 $ birthday from his mother. He was already going to explore its various properties but after unpacking he was disappointed a lot because the product $ a_1 \cdot a_2 \cdot \dots a_n $ of its elements seemed to him not large enough.

He was ready to throw out the array, but his mother reassured him. She told him, that array would not be spoiled after the following operation: choose any index $ i $ ( $ 1 \le i \le n $ ) and do $ a_i := -a_i - 1 $ .

For example, he can change array $ [3, -1, -4, 1] $ to an array $ [-4, -1, 3, 1] $ after applying this operation to elements with indices $ i=1 $ and $ i=3 $ .

Kolya had immediately understood that sometimes it's possible to increase the product of integers of the array a lot. Now he has decided that he wants to get an array with the maximal possible product of integers using only this operation with its elements (possibly zero, one or more times, as many as he wants), it is not forbidden to do this operation several times for the same index.

Help Kolya and print the array with the maximal possible product of elements $ a_1 \cdot a_2 \cdot \dots a_n $ which can be received using only this operation in some order.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
2 2 2 2
```

### 输出

```
-3 -3 -3 -3 ```

## 样例 #2

### 输入

```
1
0
```

### 输出

```
0 ```

## 样例 #3

### 输入

```
3
-3 -3 2
```

### 输出

```
-3 -3 2 ```

# 题解

## 作者：wucstdio (赞：6)

## 题意

你有一个长度为$n$的数组$a$，每次你可以让$a_i=-a_i-1$，求最后整个数组的乘积最大是多少。

## 题解

首先我们发现一个数操作两次就变成了自己：$-(-a_i-1)-1=a_i$。所以问题就转化为给你$n$个数，让你选择每一个数是$a_i$还是$-a_i-1$，使得总乘积最大。

发现负数的绝对值是比正数大的，所以为了让答案的绝对值最大，我们可以首先让所有的数都变成负数。

接下来查看这个序列的乘积，如果乘积小于$0$，那么就把绝对值最大的一个负数变成正数。

时间复杂度$O(n)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,a[100005],maxx;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]>=0)a[i]=-a[i]-1;
		maxx=min(maxx,a[i]);
	}
	if(n&1)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]==maxx)
			{
				a[i]=-a[i]-1;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：Fislett (赞：2)

# 题意

给定一个长度为 $n$ 的序列 $a$，你可以进行任意次操作使其中一个数 $i$ 使 $a_i$ 变为 $-a[i] - 1$。

求构成序列乘积的最大值的方案。

# 题解

考虑贪心，每次选择一个正数对其进行操作，显然能让它的绝对值更大，而如果对负数进行操作，就只能让其绝对值变小。故考虑将所有数变为负数，若乘积为负数（即 $n$ 为奇数），则将其中绝对值最大的数变为正数。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100005], minn;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		scanf("%d", &a[i]);
		if (a[i] >= 0) a[i] = -a[i] - 1;
		minn = min(minn, a[i]);
	}
	if (n & 1)
	{
		for (int i = 1; i <= n; i ++)
			if (a[i] == minn)
			{
				a[i] = -a[i] - 1;
				break;
			}
	}
	for (int i = 1; i <= n; i ++) printf("%d ", a[i]);
	return 0;
}
```

---

## 作者：skyskyCCC (赞：2)

**前言。**

数学题与贪心的结合。

**分析。**

[题意传送门](https://www.luogu.com.cn/problem/CF1180B)。

这个题要用到绝对值。绝对值的基本情况：
- 绝对值的定义：一个实数在数轴上离原点的距离
- 绝对值的规律：当该数是正数时，绝对值等于该数，是负数时，是其相反数。

详情请看[这里](https://baike.so.com/doc/5332105-5567407.html)。

如果一个数操作两次，那么仍是原数。

就是说每次选择每一个数是 $a_i$ 还是 $-a_i-1$ 的操作，使得总乘积最大。

证明过程：

已知正数 $a_i$ 的绝对值为 $|a_i|=a_i$，负数 $a_i$ 的绝对值为 $|a_i|=-a_i$。

那么，对于正数来说的 $|-a_i-1|$ 一定大于 $|a_i|=a_i$。

反之，对于负数来说的 $|-a_i-1|$ 一定小于 $|a_i|=-a_i$。

又因偶数个负数之积为正数，所以我们将偶数个负数相乘会使总价值最大。

很显然，我们将正数转换为负数，总价值最大。

当 $n$ 为偶数个时，只要将正数化为负数，将负数一一相乘就行了。但是，当 $n$ 为奇数个时，要使总价值最大，只能将其中绝对值最大的数不变，使其它的数与其相乘最大。

证毕。

详细过程请见代码。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>//min函数在里面。
using namespace std;
int n,a[100005],minn=0;
int ans=0x3f3f3f3f;//要设的尽可能大。
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]>=0) a[i]=-a[i]-1;//如果是正数，就将其转换成负数，使数组中都是负数。
        minn=min(minn,a[i]);//找最大值。
        if(minn==a[i]) ans=i;//找到绝对值最大的数的下标。
    }
    if(n%2==1){//当n为奇数的情况。
        for(int i=1;i<=n;i++){
            if(ans==i) cout<<-a[i]-1<<" ";
            //找到绝对值最大的数，将其再转化成正数。
            else cout<<a[i]<<" ";//其它负数直接输出。
        }
        return 0;//阶段性结束。
    }
    if(n%2==0){//当n为偶数的情况。
        for(int i=1;i<=n;i++){
            cout<<a[i]<<" "；//输出数组即可。
        }
    }
    return 0;//真正的终结。
}//by zzy
```
**后记。**

无。

---

## 作者：Stars_visitor_tyw (赞：2)

## CF1180B Nick and Array 题解
### 思路：
这一题就是选择是否把 $a_i$ 变成 $-a_i-1$，由于负数的绝对值是它的反数，也就是把负号去掉，而正数的绝对值只是它本身。所以我们可以得知负数的绝对值要大一些。所以为了让答案的绝对值更大，我们可以先把所有 $a$ 数组里的数全变为负数，也就是 $-a_i-1$，然后如果乘积是负数（即 $n$ 为奇数时），就把绝对值最大的负数（也就是最小的负数）变成正数即可让乘积最大。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],mini;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>=0)
		{
		    a[i]=-a[i]-1;
		}
		mini=min(mini,a[i]);
	}
	if(n%2==1)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]==mini)
			{
				a[i]=-a[i]-1;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
	    cout<<a[i]<<" ";
	}
	return 0;
}

---

## 作者：yanxingyu0910 (赞：2)

**题目链接**

[CF1180B](https://www.luogu.com.cn/problem/CF1180B)

**题意描述**


你有一个长度为 $n$ 的数组 $a$，定义这个数组的价值为 $a_1\times a_2\cdots \times a_n$。

你可以进行任意次操作，每一次可以选择一个数 $a_i$，并让 $a_i\times \left(-1 \right)-1$。

你的目标是使得总价值最大，输出这个最大的价值。

**简化题意和思路**

把每个正数元素无脑 $a_i\times \left( -1 \right)-1$。

这样所有的都是负数了，而且绝对值的乘积一定是最大。

然后如果**输入个数**是**偶数**乘积就是最大（偶数个负数相乘是正的）。

反之如果**输入个数**是**奇数**，乘积的绝对值虽然是最大的但是结果一定是**负数**，就不是最大了。

所以需要把一个负数元素变成正的。

同时要使结果最大就要把最小的**负数**元素（**绝对值最大的那个**）变回正的就可以使结果最大（样例三就是个例子）。


**代码实现**

```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
LL a[1000100],b=1000000000,n,i,sum; 
inline LL read(){//快读 
    register LL x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
void write(int x){//快写 
	x==0?putchar('0'):1;
	if(x<0) putchar('-'),x=-x;
	char buf[32];
	int cnt(0);
	while(x) buf[++cnt]=x%10+48,x/=10;
	while(cnt) putchar(buf[cnt--]);
}
signed main(){
	n=read();
	for(i=1;i<=n;i++){
		a[i]=read();
		if(a[i]>=0){
			a[i]=a[i]*(-1)-1;
			sum++;
		}
		b=min(a[i],b);//把最小值保存记录
	}
	if(n%2==0){
		for(i=1;i<=n;i++){
			write(a[i]);//如果n是偶数直接全部输出因为偶数个负数乘积是正数 
			printf(" ");
		}
		return 0;
	}
	else{
		for(i=1;i<=n;i++){
			if(a[i]==b){
				a[i]=a[i]*(-1)-1;//把最大的偶数变成正的这样也是偶数个负数乘积是正的 
				b=103213342132;//就一个够了把b换成一个离谱的数防止多改 
			}
			write(a[i]);
			printf(" ");
		}
		return 0;
	}
}
```
好早之前写的今天翻到了写篇题解巩固一下~

---

## 作者：_Album_ (赞：1)

更好的阅读：[传送门](https://payphone-x.top/2019/10/21/CF1180B/)

----------------------------------

## 分析

一道简单贪心题。

手推几组样例后不难看出，一个数如果操作两次之后等于没操作。则题目就变成了对于每一个$a_i$，让你选择是否进行操作，使得乘积最大。

可以注意到，若$a_i$是一个正数，则$|- a_i - 1|$一定大于$n$。

又根据初中数学可得，偶数个负数的乘积一定是正数。

因此，对于$n$是偶数的情况我们直接全部变成负数即可。

而对于$n$为奇数的情况，不难看出，奇数减$1$一定是偶数。因此，我们只需要选择一个数不进行操作即可。

显然，我们要选择的是绝对值最大的数。

时间复杂度为$O(n)$，跑过$10^5$的数据绰绰有余。

剩下的见代码注释。

--------------------------------------

## Code[Accepted]

```Cpp
#include <bits/stdc++.h>

#define ll long long
#define I inline
#define N 100001

using namespace std;

ll n , a[N];
ll maxn = 0;
ll p = 0x3f3f3f3f;

int main(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        if(a[i] >= 0){          //输入时将所有的数都变成负数
            a[i] = -a[i] - 1;
        }
        maxn = min(maxn , a[i]);
        if(maxn == a[i]){       //记录绝对值最大的数的位置
            p = i;
        }
    }
    if(n % 2 == 0){     //如果n为偶数，直接输出序列即可。
        for(int i = 1; i <= n; i ++){
            cout << a[i] << " ";
        }
        return 0;
    }
    else{
        for(int i = 1; i <= n; i ++){   //否则的话，修改绝对值最大的数。
            if(p == i){
                cout << -a[i] - 1 << " ";
            }
            else{
                cout << a[i] << " ";
            }
        }
    }
    return 0;
}
```

------------------------------------

# THE END



---

## 作者：幽界の冥神 (赞：1)

很好奇本题是怎么被评为蓝题的。。。

实际很简单，对于一个数$x$ ： 

如果它大于零，那么$|-x-1|>|x|$

而如果小于零，那么$|-x-1|<|x|$

那么很显然我们将每个正数改变，负数不变即可，但要注意：如果数的个数小于零，则要将绝对值最大的数变为$-x-1$，显然对答案影响最小

上代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 100005

using namespace std;

int n, a[N], mn = 0x3f3f3f3f, ret;

int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf ("%d", a + i);
		if (a[i] >= 0) a[i] = -a[i] - 1;//正数改为-x-1
		if (a[i] < mn) {
			ret = i;//记录绝对值最大的数的编号
			mn = a[i];
		}
	}
	if (n & 1) a[ret] = -a[ret] - 1;//将绝对值最大的数再次改变
	for (int i = 1; i <= n; ++i) printf ("%d ", a[i]);
	return 0;
}
```

完结撒花~~~

---

## 作者：yyz_100110 (赞：0)

## [Nick and Array](https://www.luogu.com.cn/problem/CF1180B)

### 观察题面：

你拥有一个长度为 $n$ 的数组 $A$,定义这个数组的价值为 $∏ a_i = a_1*a_2*\cdots*a_n$。

求最终这个数组的最大乘积是多少，要求要价值最高。

### 思路分析

- 时间复杂度 $O (n) $。

看到价值最高几个字，我们都会想到我们的[贪心算法](https://baike.baidu.com/item/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95/5411800?fr=aladdin)在贪心算法的基础上，我们还需要用到 [绝对值](https://baike.baidu.com/item/%E7%BB%9D%E5%AF%B9%E5%80%BC/3995097?fr=ge_ala) 及一个数在数轴上所对应点到原点的距离，通常使用符号 $||$ 来表示，$|b-a|$ 或 $|a-b|$ 同常表示数轴上表示 $a$ 点和表示 $b$ 点的距离。详细请见网址解析，我在这里只讲述最主要的两个点。

我们可以套上一个从题面推导出的公式 $ a_i * (-1)-1 $。
不断去重复推这个公式，这样子我们可以做到所有的数都是负数了。因为我们是贪心，输出是要是结果**最大**，就要把**最小**的**负数**，同时也是绝对值最大的那一个，变回正数元素，输出，任务就完成了，详见代码。

### AcCode:

~~~cpp
#include<bits/stdc++.h>
#define MAXN 1000010
using namespace std;
int a[MAXN],mini;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]>=0) 
            a[i]=-a[i]-1;
        mini=min(a[i],mini);
    }
    for(int i=0;n%2&&i<n;i++) 
        if(a[i]==mini){
            a[i]=-a[i]-1;
            break;
    }
    for(int i=0;i<n;i++) cout<<a[i]<<' ';
return 0;
}
~~~
奉上 [AC 记录](https://www.luogu.com.cn/record/113990966)


如果有出现 `UKE` 的话多数是因为没有注册账号，或者同样代码多次提交。
可详见 [OJ 提交机制](https://www.luogu.com.cn/blog/luogu/remotejudge) 洛谷博客说明。


---

## 作者：yyyymh (赞：0)

题目意思

给定一个长度为 $n$ 的数组 $a$，每次操作可以让其中一个数变为他的相反数再减一，求最后数组每个数相乘的乘积最大值。

思路

由于在这道题中的每个数的负数情况下绝对值比正数情况下大，而偶数个负数相乘可以变成一个整数，所以我们尽可能让更多的且是偶数个负数相乘，于是我们可以判断 $n$ 是奇数还是偶数，如果为偶则忽略，如果为奇则将绝对值最大的一个负数变为偶数，此时乘积最大。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
signed main(){
	int n,p,sum=1,t=1e9,m=1e9;
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]>=0)  a[i]=(a[i]+1)*-1;
		m=min(m,a[i]);
	}
	if(n&1){
		for(int i=1;i<=n;i++){
			if(a[i]==m){
				a[i]=(a[i]+1)*-1;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}
```


---

