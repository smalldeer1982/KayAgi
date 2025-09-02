# Ilya and Sticks

## 题目描述

In the evening, after the contest Ilya was bored, and he really felt like maximizing. He remembered that he had a set of $ n $ sticks and an instrument. Each stick is characterized by its length $ l_{i} $ .

Ilya decided to make a rectangle from the sticks. And due to his whim, he decided to make rectangles in such a way that maximizes their total area. Each stick is used in making at most one rectangle, it is possible that some of sticks remain unused. Bending sticks is not allowed.

Sticks with lengths $ a_{1} $ , $ a_{2} $ , $ a_{3} $ and $ a_{4} $ can make a rectangle if the following properties are observed:

- $ a_{1}<=a_{2}<=a_{3}<=a_{4} $
- $ a_{1}=a_{2} $
- $ a_{3}=a_{4} $

A rectangle can be made of sticks with lengths of, for example, $ 3 3 3 3 $ or $ 2 2 4 4 $ . A rectangle cannot be made of, for example, sticks $ 5 5 5 7 $ .

Ilya also has an instrument which can reduce the length of the sticks. The sticks are made of a special material, so the length of each stick can be reduced by at most one. For example, a stick with length $ 5 $ can either stay at this length or be transformed into a stick of length $ 4 $ .

You have to answer the question — what maximum total area of the rectangles can Ilya get with a file if makes rectangles from the available sticks?

## 样例 #1

### 输入

```
4
2 4 4 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
2 2 3 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
100003 100004 100005 100006
```

### 输出

```
10000800015
```

# 题解

## 作者：G2_NIKO (赞：4)

# 大概题意
有 $n$ 个木棍，每个木根可以砍掉 $1$ 个单位长度的木棍或者是保持原本的长度，看看可不可以拿着这些木棍拼成若干个长方形，可以输出最后拼出所有长方形最大面积之和。

# 分析时间到

首先我们要知道这是一个~~不~~ 很好发现的贪心问题。

怎么个贪心法呢？     诶，这问题问的好。~~我不会~~

怎么个贪心法就是整道题目的重中之重。学过乘法的~~小~~朋友来说（举个例子）：

有 $4$ 个数，$a,b,c,d$。

假如 $a>b>c>d$ 那么 $a\times b+c\times d > a\times c+b\times d$。

由此我们可以得出尽可能大的边做长方形面积就尽可能大。

# 思路时间到

将数组从大到小排序，从前往后找，相邻两个数如果相差值在 $1$ 以内，就可以当作长方形的其中两条边，否则就拼不成长方形（因为这样就会有至少一条边没用到）。最后相乘加起来就可以啦。

# code


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],b[100010],m,s;
bool cmp(long long o,long long p)
{
	return o>p;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<n;i++)
	{
		if(a[i]==a[i+1]||a[i]-1==a[i+1])
		{
			b[++m]=a[i+1];
			i++;
		}
		else
		{
			cout<<0;
			return 0;
		}
	}
	if(m%2==1)
	{
		cout<<0;
		return 0;
	}
	for(int i=1;i<=m;i+=2)
	{
		s+=(b[i]*b[i+1]);
	}
	cout<<s;
	return 0;
} 
```

点赞（实在不行收个藏？）（球求拉）。

---

## 作者：OIerJiang_1017 (赞：1)

## [CF525C 题目传送门](https://www.luogu.com.cn/problem/CF525C)

## 题目大意
给定 $n$ 根木棍，第 $i$ 根木棍的长度为 $f_i$ ，木棍长度可以根据需要，削减 $1$ 个单位，现在要在 $n$ 根木棍中选出一些木棍，拼成若干个长方形，求这些长方形面积总和的最大值。

## 解决思路
题目中已经说了一根木棍只能削掉 $1$ 个单位，说明组成长方形时两根木棍如果想配对（让两根木棍长度相等），它们的差就只能是 $0$ 或者 $1$ 。为了方便对木棒进行配对，我们需要对木棍的长度进行排序。同时要让面积尽量大，所以要从大到小排序。

### 分析样例
接下来就需要进行模拟。此处给一个样例方便理解。假设排完序后所有木棍的长度如下：$\{13,12,10,9,7,6,5,3,2\}$。很明显，为了配对，我们需要把 $13$ 削成 $12$，两个 $12$ 可以配对。把 $10$ 削成 $12$，两个 $9$，可以配对。把 $7$ 削成 $6$，两个 $6$，可以配对。$5$ 只能削 $1$ 单位，削成 $4$，无法与其他进行配对。$3$ 可以削成 $2$，两个 $2$，可以配对。配对完一共有 $4$ 个配对，长度分别为 $\{12,9,6,2\}$。第一个长方形长为 $12$，宽为 $9$；第二个长方形长为 $6$，宽为 $2$。

### 发现规律
分析完样例就容易发现规律：大到小排序后，从 $f_2$ 到 $f_n$ 进行枚举，如果相邻两根的长度差小于 $1$，就可以把它作为长，注意这两根已经选的不能再选，接下来再遇到相邻两根长度差小于 $1$ 的就作为宽，算出这个长方形的面积并加入结果中，将长与宽都清 $0$，方便接下来统计。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
#define ll long long
//不开long long见祖宗
using namespace std;

const int N = 1e5 + 10;
ll n, f[N], a, b;
bool cmp(ll x, ll y)
{
	return x > y;
}

int main()
{
	scanf("%lld", &n);//建议scanf,更快
	for(int i = 1; i <= n; i++)
		scanf("%lld", &f[i]);
	sort(f + 1, f + n + 1, cmp);
	for(int i = 2; i <= n; i++)
		if(f[i - 1] - f[i] <= 1)
			if(a != 0)
			{
				b += a * f[i];
				a = 0;
				i++;
			}
			else
			{
				a = f[i];
				i++;
			}
	printf("%lld\n", b);//建议printf,更快
	return 0;
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF525C)

这其实就是一道贪心题，我们要使面积和最大，就要从大的数据下手，于是我们从大到小排序，然后依次去判断是否符合条件，符合就把长和宽相乘。

例如：    
$2$ $5$ $3$ $8$ $6$ $9$    
我们先把它排序，变成：    
$9$ $8$ $6$ $5$ $3$ $2$    
接着我们判断 $9-8$ 是否小于等于 $1$，可见是符合的，所以我们就用一个变量存储长 $8$，接下来再依次往下推 就可以得到 $40$ 的结果了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100000],s=0,ss=0;
inline bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	scanf("%lld",&n);
	for(register int i=0;i<n;i++) scanf("%lld",&a[i]);
	sort(a,a+n,cmp);
	for(register int i=1;i<n;i++)
		if(a[i-1]-a[i]<=1)
			if(!ss) ss=a[i],i++;else s+=ss*a[i],i++,ss=0;
	printf("%lld",s);
	return 0;
}
```


---

## 作者：czh___ (赞：0)

题意：

给出 $n$ 条线段构造矩形面积最大。每条线段可以减掉一个单位长度。

题解：

先排序，从大到小处理来保证面积最大，将所有可以做长和宽的两条线段找出来，要使矩形面积最大，则长和宽尽量差别小，于是就可以用相邻的满足可以做长和宽的线段组成矩形。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+1;
long long a[maxn];
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++)
            scanf("%I64d",&a[i]);
        sort(a,a+n);
        long long l=0,ans=0;
        for(int i=n-1;i>=0;){
            if((a[i]-a[i-1]==1)||(a[i]==a[i-1])){
                if(l==0)
                    l=a[i-1];
                else
                    ans=ans+l*a[i-1],
                    l=0;
                i=i-2;
            }
            else
            	i--;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

[改编于](https://blog.csdn.net/caduca/article/details/44678881?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522BCA45469-6692-416C-87C0-7482CFE8C57D%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=BCA45469-6692-416C-87C0-7482CFE8C57D&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-44678881-null-null.142^v100^pc_search_result_base5&utm_term=Ilya%20and%20Sticks&spm=1018.2226.3001.4187)

---

## 作者：__Octhyccc__ (赞：0)

我们要求最大值，长方形面积为 $a\times b$，我们要对每根木棍的长度进行排序。还可以对任意一根木棍 $f_i$ 砍掉 $1$ 个单位长度，所以我们需要看第 $f_{i-1}$ 根木棍是否满足 $f_{i-1}-f_{i}\le 1$，是的话令 $thx$ 为 $f_i$（因为木棍长度是降序的），若 $thx$ 不为 $0$，说明找到了 $2$ 组长和宽，可以组成长方形。

证明：因为木棍的长短是降序，$thx$ 一定为没找过的元素中最大的，现在又找到了一个第二大的 $f_i$ 可以与它结合，因此得证：当 $thx$ 不为 $0$，且找到了一个 $f_i$ 与它可以结合时，可以使组成的长方形的面积和尽可能的大。

因此令计数器 $cnt$ 加上 $thx\times f_i$，**一定不要忘记清空 $thx$！**

**无论 $thx$ 是否为 $0$，只要满足 $f_{i-1}-f_{i}\le 1$，$i$ 就应该等于 $i+1$！**

然后就上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long read() {
    register long long x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}
void write(long long x){
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);putchar(x%10+'0');}
	else putchar(x+'0');
	return; 
}
long long n,f[100010],j=0;
long long cnt=0,thx;
int main(){
	n=read();
	for(int i=0;i<n;++i)f[i]=read();
	sort(f,f+n,greater<int>());
	for(int i=1;i<n;i++){
		if(f[i-1]-f[i]<=1){
			if(thx==0)thx=f[i],i++;
			else cnt+=(thx*f[i]),thx=0,i++;
		}
	}
	write(cnt);
	return 0;
}
```

---

## 作者：lrmlrm_ (赞：0)

## 题意

给定 $n$ 根木棍，长度为 $f_i$，木棍长度可以根据需要，削减 $1$ 个单位。现在要在 $n$ 根木棍选一些，拼成若干个长方形，问所有长方形面积和的最大值。

## 思路

题目中已经说了一根木棍只能削掉 $1$ 个单位，说明组成长方形时两根木棍如果想配对（让两根木棍长度相等），它们的差就只能是 $0$ 或者 $1$。为了方便对木棒进行配对，我们需要对木棍的长度进行排序。同时要让面积尽量大，所以要从大到小排序。

接下来就需要进行模拟。此处给一个样例方便理解。假设排完序后所有木棍的长度如下：

`13 12 10 9 7 6 5 3 2`

很明显，为了配对，我们需要把 $13$ 削成 $12$，两个 $12$ 可以配对。把 $10$ 削成 $9$，两个 $9$，可以配对。把 $7$ 削成 $6$，两个 $6$，可以配对。$5$ 只能削 $1$ 单位，削成 $4$，无法与其他进行配对。$3$ 可以削成 $2$，两个 $2$，可以配对。

配对完一共有 $4$ 个配对，长度分别为 $12,9,6,2$。第一个长方形长为 $12$，宽为 $9$。第二个长方形长为 $6$，宽为 $2$。

分析完样例就容易发现规律：大到小排序后，从 $f_2$ 到 $f_n$ 进行枚举，如果相邻两根的长度差小于 $1$，就可以把它作为长（注意这两根已经选的不能再选），接下来再遇到相邻两根长度差小于 $1$ 的就作为宽，算出这个长方形的面积并加入 `sum` 中，将长与宽都清 $0$，方便接下来统计。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool cmp(int ma,int mi){
	return ma>mi;
}
int n,x,y;
int f[100010];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&f[i]);
	sort(f+1,f+n+1,cmp);
	for(int i=2;i<=n;i++)
		if(f[i-1]-f[i]<=1){
			if(x==0)x=f[i],i++;
			else y+=x*f[i],i++,x=0;
		}
	printf("%lld",y);
	return 0;
} 
```

---

## 作者：wimg6_ (赞：0)

## CF525C 题解

仔细读题，找到突破口。

> 木棍可以根据需要，削减 $1$ 个单位。

突破口正在于这句话的后半句：只能削减 $1$ 个单位长度！

于是我们想到对题目所给的数据 $a_i$ 进行排序，大的在前，排完序后成对操作。

考虑从 $a_{n-1}$ 枚举到 $a_{1}$，对于**相邻**$^{1}$的两对木棍，如果其相差比 $2$ 小，我们即可对其进行处理。

接下来考虑贪心策略：通常只有一个木棍可以与另一个木棍形成配对，直接模拟即可。

若有两个木棍可以与之配对，那么首选是大的那根，这样可以使面积和最大。如果大的那根被其他木棍挑走了，那就只能选小的那根。

可以通过本题所有测试数据。

------------

**问题一**

为何是相邻？

栗子在他的文章中已经告诉我们答案了：

设 $a< b< c< d$，则必有$a\times b+c\times d< a\times d+b\times c$。

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF525C)

## 题意
给定 $n$ 根木棍，第 $i$ 根木棍的长度为 $a_i$，木棍长度可以削减 $1$，现在要在 $n$ 根木棍中选出几根木棍，拼成**若干个矩形**，要长方形面积总和的最大值。

## 思路
我可以先看一下第三个样例：

> $4$\
$100006\ 100005\ 100004\ 100003$

我们可以先用 sort 来排序，变为：$100006\ 100005\ 100004\ 100003$

这时候我们发现可以让 $100006$ 和 $100004$ 减一变成总共两个 $100005$ 和 $100003$。所以结果是 $10000800015$。\
这题可以考虑贪心，我们先用 sort 函数来排序，这里可以使用 $\operatorname{cmp}$ 函数来从大到小，然后开始枚举。
- 先判断是否有一样的，如果有就可以构成一个对边
- 否则搞一个备份查看他减一与他后面的那一个是否一样，如果一样的就把这个与他后面的那个构成了一条边。
  
我们这里可以考虑制作一个计数器，**初始化为** $0$ 如果出现一组对边，则计数器加一。因为长和宽共同大的结果是更高的，所以不需要考虑大的与小的组合。我们可以找到对边存下来之后两两组合即可。

---

## 作者：Alexxu2024 (赞：0)

# CF525C 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF525C)

应该很容易想到每次把两组最大的边结合，能得到最大值。

比如，有 $4$ 组边，设其长为 $2,3,4,5$。发现有多种组合方法，但 $5 \times 4\ +\ 3 \times 2 = 26$ 最大。

其实，这就是差小积大。注意到边的总和一定，所以结合长度相邻 $2$ 组边（差最小）能得到最大值。假如有偶数组边，直接计算即可；假如有奇数组边，忽略最小的一组就可得到最大值。

根据上面的推论，当有 $\ge 2$ 组合法边时，应先结合最大的 $2$ 组，再结合次大的 $2$ 组，以此类推，直到边的组数 $\le 1$，无法再继续围成长方形。

于是，考虑对数组进行从大到小排序，最后遍历数组，求和即可。

**代码很好写，但有几点要注意：**

- **可以将边长 $-1$；**
- 要开 ```long long``` ；
- 在发现 $1$ 组边可行时要掠过与之结合的边，否则会出错。对此不明白的可以去看看样例 $2$。
- 每次加完 ```sum``` 要清空临时存储的边。

## 代码
```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
long long a[1000010];//long long哦
bool cmp(long long x,long long y){//自定义从大到小排序的函数
    return x>y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];//输入
    }
    sort(a+1,a+1+n,cmp);//排序
    long long sum=0,chang=0;//chang存储临时的边
    for(int i=1;i<=n;i++){
        if(a[i]==a[i+1]||a[i]==a[i+1]+1){//如果符合条件
            if(chang==0){
                chang=a[i+1];
                i++;//加1，防止重复加与之前结合的边（注意的第二点）
            }
            else{
                sum+=a[i+1]*chang;
                chang=0;//清空长（注意的第三点）
                i++;//与上面的作用相同
            }
        }
    }
    cout << sum;//输出
    return 0;
}
```

---

## 作者：XL4453 (赞：0)



------------
题目分析：

首先可以发现，只有当两根木棍相差小于一时才有可能成为构成矩形的边长，否则可以直接扔掉。

那么就先把所有能用的边长处理出来。

对于绝大多数木棍，只有一个能与之搭配，那么直接选。而对于另一些木棍，既可以向上搭配，又可以向下搭配时，若可以向上选，那么选择比他大一的肯定更优。这个贪心是显然的。

处理出边长后，考虑如何排布这些边长才能使得总面积最大。

这里还是用贪心，假设有 $a<b<c<d$，四个边长，排序不等式告诉我们：$a  \times  b+c \times d < a \times d+b \times c$。

那么，从大到小选择相邻边长相乘成为必然选择。


实现上，其实可以将两步操作合为一起。也就是在从后往前处理可行边长时直接将其与上一个可行边长相乘，加到答案即可。

---

## 作者：Trimsteanima (赞：0)

有$n$根木条，要用他们来摆矩形。
四根长度为$a_1$、$a_2$、$a_3$、$a_4$需要满足$a_1<=a_2<=a_3<=a_4$，$a_1 = a_2$，$a_3=a_4$
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[100100], i, m, s;
int main() {
	scanf("%lld", &n);
	for (long long i = 0 ; i < n; i ++)
		scanf("%lld", &a[i]);
	std :: sort(a, a + n);
	for (long long i = n - 2; i >= 0; i --)
		if (a[i + 1] - a[i] < 2) {
			if (m) s += m * a[i], m = 0; else m = a[i];
			i --;
		}
	printf("%lld\n", s);
	return 0;
}
```


---

