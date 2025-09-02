# z-sort

## 题目描述

z学校的一位学生发现了一种叫做z排序的排序方法。如果数组a满足以下两个条件，那么称它为z排序后的:

1.对所有的偶数i，$a_i$>=$a_{i-1}$；

2.对所有的奇数i，$a_i$<=$a_{i-1}$。

例如，数组【1,2,1,2】和【1,1,1,1】是z排序过的，而数组【1,2,3,4】不是。

你能对一个数组进行z排序吗？

## 样例 #1

### 输入

```
4
1 2 2 1
```

### 输出

```
1 2 1 2
```

## 样例 #2

### 输入

```
5
1 3 2 2 5
```

### 输出

```
1 5 2 3 2
```

# 题解

## 作者：千反田 (赞：9)

~~这题绝对恶意评分~~

题目意思很清楚，每次输出一个最大的和最小的数

看上面的代码都比较复杂

写一个简易懂的（蒟蒻的迷之自信）
## 祭上代码
```cpp
#include<bits/stdc++.h>//万能库，压行
int n,num[1000001];
void print(){
	int head=1,tail=n;//头指针 尾指针
	while(head<tail)
	 printf("%d %d ",num[head++],num[tail--]);//核心代码，从两侧向中间输出
    //因为已经排序过
    //所以能保证每次都输出剩下的数中最大的和最小的
	if(head==tail)
	 printf("%d",num[head]);//最后一个特判
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	 scanf("%d",&num[i]);
	sort(num+1,num+n+1);//快排
	print();
    return ~~(0-0);//卖萌求通过
} 
```



---

## 作者：BMTXLRC (赞：3)

### 分析题意：

给定一个序列，能否使原序列满足 $a_{i-1}\leq a_i(i\mod 2=0)$ 且 $a_i\leq a_{i-1}(i\mod 2=1)$。

很显然，我们先对原序列进行排序，然后每次取最大和最小的两个数，先输出最大后输出最小值，构造出来的显然是满足题意的序列。

但是要注意的是，如果序列长度为奇数，我们还要输出最中间的一个数。

另外不可能存在 $\texttt{Impossible}$ 的情况，因此不用考虑，你排序后肯定会是不下降的。

### 无比丑陋的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
ll a[1005],n;
using namespace std;
int main(){
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(register int i=1;i<=n/2;i++) printf("%lld %lld ",a[i],a[n-i+1]);
    if(n%2==1) printf("%lld",a[n/2+1]);
}
```


---

## 作者：封禁用户 (赞：2)

题目传送>>[CF652B](https://www.luogu.com.cn/problem/CF652B)  
### 题意简述：  
规定一种对数组排列后结果满足以下条件的 z 排序：  
- $a_i \ge a_{i-1}$（$i$ 为偶数）；  
- $a_i \le a_{i-1}$（$i$ 为奇数）；  

现欲求所给定的含 $n$ 个元素的数组的 z 排序结果。  
（数据范围:$1 \le n \le 1000$，$1 \le a_i \le 10^9$。）  
### 题目分析:  
依据题意 z 排序结果所满足的条件可知，偶数位总是比其左右两个数（奇数位）都大或等，那么来考虑如何排才能达此目标呢？第一个数当然是奇数位数，它要小于等于第二个数（偶数位数），而与此同时第二个数还要大于等于第三个数（奇数位数），所以第二个数肯定是一个较大数，第一、三个数是较小数，依次类推同。由此，我们可以考虑在偶数位上放较大数，奇数位上放较小数，我们直接对原数组按大小排序即可将其从中间划分为较大数和较小数两部分，然后按顺序――奇数位递增、偶数位递减一个个安放数即可达到 z 排序得效果，即分别从按大小排序结果两头一一安放。  
#### 注意：  
当 $n$ 为偶数时当然可以两两安放至尽，而当 $n$ 为奇数时毫无疑问会一个大小居中的数落单，而它刚好大于或等于较小数部分最大数且小于或等于较大数部分最小数，所以此时我们只需在最后将其输出即可。  
### Code：  
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;   //类型定义long long为ll，避免频繁使用long long时累手
ll n;   //定义数组元素数
ll a[1001];   //开数组
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	cin >> n;
	for (ll i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort(a, a + n);   //按大小递增排序
	for (ll i = 0; i < n / 2; i++)
	{
		cout << a[i] << " " << a[n - i - 1] << " ";   //分别从按大小排序结果两头一一安放，注意空格
	}
	if (n % 2 == 1)   //特判n为奇数
	{
		cout << a[n / 2];   //输出大小居中落单的数
	}
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/yqmfa4nl.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：绝顶我为峰 (赞：2)

首先这一题应该是开了$SPJ$的~~当然还有恶意评分~~，因为显然$z-sort$不止一种，我测样例$2$输出了另一个合法解，但是同样$AC$。$qwq^{qwq}_{qwq}$

显然排序是必须的（~~直觉？~~），然后我们对于每一个数对$(x,x+1)$，$x$为偶数时，将$a_x$和$a_{x+1}$交换位置后就可以同时满足条件$1,2$，因为除了$(a_x,a_{x+1})$成为逆序对之外，不影响其他位置的相对大小。

卖个萌$=ω=$

代码接好：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[1001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);//排序
	cout<<a[1];//第一个不动
	for(int i=3;i<=n;i+=2)//两个两个输出
		cout<<" "<<a[i]<<" "<<a[i-1];//构造逆序对
	if(n%2==0)
		cout<<" "<<a[n];//特殊处理最后一个
	cout<<endl;
	return 0;//qwq
}
```

---

## 作者：Steve_Zhu (赞：2)

十分简单的排序。STL的sort函数一遍过。

（但是要注意输出顺序...应该输出一个最大值后直接输出一个最小值。n为奇数和n为偶数的时候也要分别考虑输出。

下面直接贴出AC代码：
```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
ll a[1005];
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    sort(a, a + n);
    for(int i = 0; i < n / 2; i++)
        printf("%lld %lld ", a[i], a[n - i - 1]);
    if(n % 2 == 1) printf("%lld", a[n / 2]);
    return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
定义一个数组是 $\text{Z}$ 排序过的，当且仅当：

- 对于所有的 $i=2k+1(k\in\mathbb Z)$，$a_i\leqslant a_{i-1}$。
- 对于所有的 $i=2k(k\in\mathbb Z)$，$a_i\geqslant a_{i-1}$。

现在给出一个长度为 $n$ 的数组 $A$，请你对它进行 $\text{Z}$ 排序。

**数据范围：$1\leqslant n\leqslant 10^3$，$1\leqslant A_i\leqslant 10^9$。**
## Solution
很容易的一道题目，不知道为什么，感觉题解里面都想复杂了，于是我来给一个比较简单易懂的题解吧。qwq

我们先找所有为奇数的 $i$，看看是否有 $a_i>a_{i-1}$，如果是的话将它们两个交换，否则不变，使得 $a_i\leqslant a_{i-1}$。再找所有为偶数的 $i$，看看是否有 $a_i<a_{i-1}$，如果是的话将它们两个交换，否则不变，使得 $a_i\geqslant a_{i-1}$。最终得到的数组就是 $\text Z$ 排序过的了。
## Code
```cpp
const int N = 1e3 + 7;
int n, a[N];

int main() {
    n = Rint;
    F(i, 1, n) a[i] = Rint;
    for(int i = 3; i <= n; i += 2) if(a[i] > a[i - 1]) swap(a[i], a[i - 1]);
    for(int i = 2; i <= n; i += 2) if(a[i] < a[i - 1]) swap(a[i], a[i - 1]);
    F(i, 1, n) write(a[i]), putchar(' ');
	return 0;
}
```

---

## 作者：q779 (赞：1)

题意要求奇数位递增，偶数位递减

那每次只要输出最小值和最大值就可以了

这里给出了**优先队列**的写法

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define int long long
priority_queue<int> q1;//大根堆
priority_queue< int,vector<int>,greater<int> > q2;//小根堆
int n;
signed main()
{
    scanf("%lld",&n);
    for(R int i=0,t; i<n; i++)
    {
        scanf("%lld",&t);
        q1.push(t);
        q2.push(t);
    }
    for(R int i=1; i<=n/2; i++)
    {
        printf("%lld %lld ",q2.top(),q1.top());
        q1.pop();q2.pop();
    }
    if(n&1)printf("%lld",q1.top());//n为奇数
    return 0;
}
```

---

## 作者：北冥之子 (赞：1)

# 我们应该坚决反对恶意评分！
其实这应该是一道 普及- 的题目，让我们好好看一下——
[重新看题目](https://www.luogu.org/problemnew/show/CF652B)

1.对所有的偶数 i，a_i >= a_i-1 ;

2.对所有的奇数 i，a_i <= a_i-1 ;

其实如果有注意到的童鞋会发现，按照这个方法，输入样例#2：
```cpp
5
1 3 2 2 5
```
可以变成：
```cpp
1. 1 3 2 5 2
2. 1 5 2 3 2
```
是不是很神奇？
所以这道题一定还有别的意思！

仔细一看，输出样例#2就是输出一个最小一个最大轮流来！

也难怪这道题叫 sort 了。

但是——我们为什么要用排序呢？
这道题桶排会被卡，冒泡看不惯，快排又难码。

于是，我想出了一个暴力解法——

直接查找最大最小！
```cpp
#include<iostream>//这段代码有问题噢，错误示范！
#include<cstdio>
using namespace std;
int a[1010];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);//输入
    printf("%d",a[1]);
    a[1]=0;//不要问我在干什么，这是错误的！
    for(int i=1;i<=n;i++)//开始查找！
    {
    	int maxn=0,minn=2e9;
    	int ma,mi;
    	for(int j=1;j<=n;j++)
    	{
    		if(a[j]>maxn)//最大判断
    		{
    			maxn=max(maxn,a[j]);
    			ma=j;
            	}
            	if(a[j]<minn&&a[j]!=0)//最小判断
    		{
    			minn=min(minn,a[j]);
    			mi=j;
            	}
        }
        if(maxn!=0)//输出最大
        {
            printf(" %d",maxn);
            [ma]=0;//0不会在最大最小的考虑范围内，这是防止重复！
        }
        if(minn!=2e9)//输出最小
        {
            printf(" %d",minn);
            a[mi]=0;
        }
    }
}
```
当然这样第七个点就会被卡了，原因是：
1.刚开始我以为第一个数最小T_T
2.当数组中只剩一个数时， maxn 和 minn 都会是它！

所以我们要防止这样的事发生！
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1010];
int n;
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int maxn=0,minn=2e9;
    int ma=0,mi=0;
    for(int j=1;j<=n;j++)
    {
    	if(a[j]<minn&&a[j]!=0)
    	{
    		minn=min(minn,a[j]);
    		mi=j;
		}
	}
	printf("%d",minn);//输出第一个数
	a[mi]=0;//重定义
	mi=0,minn=2e9;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		if(a[j]>maxn)
    		{
    			maxn=max(maxn,a[j]);
    			ma=j;
			}
			if(a[j]<minn&&a[j]!=0)
    		{
    			minn=min(minn,a[j]);
    			mi=j;
			}
		}
		if(maxn!=0)
		{
			printf(" %d",maxn);
			a[ma]=0;
		}
		if(minn!=2e9&&ma!=mi)//ma!=mi 防止最大最小重复
		{
			printf(" %d",minn);
			a[mi]=0;
		}
		maxn=0;//重定义
		ma=0;
		minn=2e9;
		mi=0;
	}
}
```
这样就较好地防止了上面提到的事情发生！然后就能AC了！
加油↖(^ω^)↗！

---

## 作者：豌豆射手皮0608 (赞：1)

~~这是我这种蒟蒻见过除了[这题](https://www.luogu.org/problemnew/show/CF409F)以外最水的紫题了~~

~~恶意评分233~~

题意很简单，给你n个数，输出一个小值再输出一个大值

作为爱思（~~zuo~~）考（~~si~~）的蒟蒻，第一个想到的就是桶排（~~sort:我的脸面何在~~）

看数据 n<=1000,a[i]<=1e9。。。~~这数据冒泡都能过~~ 这不就是专门卡桶排吗？

在这时，就要祭上我们的神器map了！！！（~~然而这并不能让牛战士摘下他的面具~~）

附上蒟蒻AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> m;//map桶嘻嘻
int a[10000],f,n,sum;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        m[a[i]]++;
    }
    map<int,int>::iterator k=m.end();//神奇的迭代器
    k--;
    for(map<int,int>::iterator i=m.begin();i!=m.end();i++)//遍历QWQ
    {
    	for(int j=1;j<=i->second;j++)
    	{
    		if(f==0)
    		{
    			f=1;
    		    cout<<i->first;
    	    }
    	    else cout<<' '<<i->first;
    	    sum++;
    	    if(sum>=n)
            {
        	cout<<endl;
        	return 0;
            }
    	    if(k->second>=1)
    	    {
    	    	k->second--;
    	    	cout<<' '<<k->first;
            }
            else {
                k--;
                k->second--;
                cout<<' '<<k->first; 
            }
            sum++;
            if(sum>=n)
            {
        	cout<<endl;
        	return 0;
            }
        }
        if(sum>=n)
        {
        	cout<<endl;
        	return 0;
        }
    }

}
```
~~迭代器真是个好东西~~

---

## 作者：lxgw (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF652B)
## 题意
输出一个序列满足:

1. 对所有的偶数 i，$a_i \geqslant a_{i-1}$ ；
1. 对所有的奇数 i，$a_i \leqslant a_{i-1}$ 。

## 思路
因为要求奇数位递增，偶数位递减，所以只用把原数列排序后每次输出一个最大数和最小数（奇数位由最小值到中间值，偶数位由最大值到中间值）就好了。

## 代码
```cpp
#include<iostream>
#include<algorithm>
int a[1005];
using namespace std;
inline int read()//快读
{
    int x = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * w;
}
int main()
{
    int n=read();
    for(register int i = 0; i < n;++ i)
        a[i]=read();
    sort(a,a+n);//把原数组排序
    for(register int i = 0; i < n>>1; ++i)
        printf("%d %d ", a[i], a[n - i - 1]);//每次输出一个最大值和最小值
    if(n%2) printf("%d", a[n>>1]);//判断 n 为偶数的情况
    return 0;
}
```

完结撒花~

谢谢 qwq .

---

## 作者：第二小题 (赞：0)

[AC记录](https://www.luogu.com.cn/record/34200263)

这道题我们动动脑筋就行了
### 方法：


------------
先把数组排序，从新数组第二个开始在新数组里放原数组里最大的数，然后在后面第两个放第二大的数，以此类推，在$b_i$放置$a$数组第$i/2$大的数（$b$是新数组，$a$是原数组，$i+=2$）

接着，从新数组第一个开始在新数组里放原数组里第一小的数，然后在后面第两个放第二小的数，以此类推，在$b_i$放置$a$数组第$（i+1）/2$小的数（$b$是新数组，$a$是原数组，$i+=2$）

输出新数组
### 原因：


------------
其实这题不用想太复杂，题目需要我们偶数$i$大于等于$a_{i-1}$，那就把大的放在偶数位，小的放在奇数位，如何也能保证题目的要求

~~反正我是怎么也没想到Impossible的可能，且数据也没有，那就不管它了）~~
### 举例：


------------
就拿样例二举例吧

原数组（a）：
![](https://cdn.luogu.com.cn/upload/image_hosting/kpl98h1p.png)

经过排序后：
![](https://cdn.luogu.com.cn/upload/image_hosting/munupbj0.png)

把较大的数放入新数组（b）：
![](https://cdn.luogu.com.cn/upload/image_hosting/my7t6x70.png)

（这里先放小的也可以）

把较小的数放入新数据（b）：
![](https://cdn.luogu.com.cn/upload/image_hosting/0ylbn1z8.png)

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long n,a[1010],b[1010],s;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i+=2)
	{
		b[i]=a[n-s];
		s++;
	}
	s=0;
	for(int i=1;i<=n;i+=2)
	{
		s++;
		b[i]=a[s];
	}
	for(int i=1;i<=n;i++) cout<<b[i]<<" ";
}
```


---

## 作者：Peter0701 (赞：0)

写在前面：
虽然$CF$的题目存在恶意评分现象，但是题目本身还是很有意义的，尤其是一题多解，能够很好地训练我们的思维啦～

观察题目条件，

$1.$对所有的偶数$i$，$a_i >= a_{i-1}$；

$2$.对所有的奇数$i$，$a_i <= a_{i-1}$。

那么，对于一个偶数位$i$，它比左边$i-1$和右边$i+1$两个奇数位的值都要大或者相同。

由数学归纳法可得，所有偶数位上的数均大于等于奇数位上的数。

因此，对于一个给定的数列，我们可以将其从小到大排序，前面一半分给各个奇数位，后面一半分给各个偶数位。

对于“一半”这个说法，为了思路清晰可以对$n$的值进行分类讨论，分别赋值即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int ret=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        ret=(ret<<1)+(ret<<3)+ch-'0';
        ch=getchar();
    }
    return ret*f;
}
int n,a[1005],ans[1005];
int main()
{
    n=read();
    for(register int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+n+1);
    if(n%2==0)
    {
        for(register int i=1;i<n;i+=2)
            ans[i]=a[i/2+1];
        for(register int i=2;i<=n;i+=2)
            ans[i]=a[n-i/2+1];
    }
    else
    {
        for(register int i=1;i<=n;i+=2)
            ans[i]=a[i/2+1];
        for(register int i=2;i<n;i+=2)
            ans[i]=a[n-i/2+1];
    }
    for(register int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    return 0;
}
```
如有疑问，评论区见，感谢资瓷！

---

## 作者：Cubaner (赞：0)

### 这题真的恶意评分啊啊啊！
基本算法就是排序+模（暴）拟（搜）

先看题面：对于一个无序数组a，对其进行调整，使其：

1.对所有的偶数i：a[ i ]>=a[ i - 1 ] ;

2.对所有的奇数i：a[ i ]<=a[ i - 1 ]；

所以，排序啊，小fo伙伴们！

```for(int i=1;i<=b;i++)
        for(int j=1;j<=b-1;j++)
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }//冒泡万岁！！！
```
对数组a进行从小到大排序后，偶数i的条件就满足啦，所以我们要对奇数i进行调整；

对于有序数组a，其满足

a[ 1 ]<=a[ 2 ]<=a[ 3 ]<=......<=a[ n ]

对所有奇数i进行调整，得：

a[ 1 ]，a[ 3 ]，a[ 2 ]，a[ 5 ]，a[ 4 ].....

~~找规律万岁！~~

若n为偶数，则答案为：

a[ 1 ]，a[ 3 ]，a[ 2 ]......a[ n - 1 ]，a[ n - 2 ]，a[ n ]

得输出代码

```int ii=3;
    cout<<a[1]<<" ";
    if(n%2==0)
    {
        for(int i=1;i<=((n/2)-1);i++)//?
        {
            cout<<a[ii]<<" "<<a[ii-1]<<" ";
            ii+=2;
        }
        cout<<a[n];
    }
```

若n为奇数，则答案为：

a[ 1 ]，a[ 3 ]，a[ 2 ].......a[ n ]，a[ n - 1 ]

得输出代码
```else if(n%2==1)
    {
        for(int i=1;i<=((n-1)/2);i++)//?
        {
            cout<<a[ii]<<" "<<a[ii-1]<<" ";
            ii+=2;
        }
    }
```
然后就A了这道题吧！

上代码！

    #include<iostream>
    using namespace std;
    int a[1010];
    int main()
    {
        int n,temp;
        cin>>n;
        for(int i=1;i<=n;i++)
        cin>>a[i];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n-i;j++)
                if(a[j]>a[j+1])
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
        int ii=3;
        cout<<a[1]<<" ";
        if(n%2==0)
        { 
            for(int i=1;i<=((n/2)-1);i++)//?
            {
                cout<<a[ii]<<" "<<a[ii-1]<<" ";
                ii+=2;
            }
            cout<<a[n];
        }
        else if(n%2==1)
        { 
            for(int i=1;i<=((n-1)/2);i++)//?
            {
                cout<<a[ii]<<" "<<a[ii-1]<<" ";
                ii+=2;
            }
        }
        while（1）
        cout<<" ";//反抄袭
        return 0;
    }

---

