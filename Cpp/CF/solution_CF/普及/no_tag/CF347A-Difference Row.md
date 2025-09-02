# Difference Row

## 题目描述

You want to arrange $ n $ integers $ a_{1},a_{2},...,a_{n} $ in some order in a row. Let's define the value of an arrangement as the sum of differences between all pairs of adjacent integers.

More formally, let's denote some arrangement as a sequence of integers $ x_{1},x_{2},...,x_{n} $ , where sequence $ x $ is a permutation of sequence $ a $ . The value of such an arrangement is $ (x_{1}-x_{2})+(x_{2}-x_{3})+...+(x_{n-1}-x_{n}) $ .

Find the largest possible value of an arrangement. Then, output the lexicographically smallest sequence $ x $ that corresponds to an arrangement of the largest possible value.

## 说明/提示

In the sample test case, the value of the output arrangement is $ (100-(-50))+((-50)-0)+(0-50)+(50-(-100))=200 $ . No other arrangement has a larger value, and among all arrangements with the value of $ 200 $ , the output arrangement is the lexicographically smallest one.

Sequence $ x_{1},x_{2},...\ ,x_{p} $ is lexicographically smaller than sequence $ y_{1},y_{2},...\ ,y_{p} $ if there exists an integer $ r $ $ (0<=r&lt;p) $ such that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ .

## 样例 #1

### 输入

```
5
100 -100 50 0 -50
```

### 输出

```
100 -50 0 50 -100 
```

# 题解

## 作者：Ryan_Yu (赞：6)

此题化简一下公式即可：

$(x[1]-x[2])+(x[2]-x[3])+···+(x[n-1]-x[n])$

$=x[1]-x[2]+x[2]-x[3]+···+x[n-1]-x[n]$

$=x[1]-x[n]$

公式化简后，题目就变为：

先输出数列中的最大值，然后输出 $n-2$ 个数从小到大排列后的数列，最后输出数列的最小值。


代码：

```latex
#include<bits/stdc++.h>
using namespace std;
long long a[1000],i,n;
int main()
{
    scanf("%lld",&n);
    for(i=1; i<=n; i++)
        scanf("%lld",&a[i]);
    sort(a+1,a+1+n);
    printf("%lld ",a[n]);
    for(i=2; i<n; i++)
     printf("%lld ",a[i]);
    printf("%lld\n",a[1]);
    return 0;
}
```


---

## 作者：JJA_ (赞：2)

## 题目大意

给定序列 $x$，它含有 $n$ 个数。序列的顺序可以改变，求序列的最大价值。

价值的定义 $val = ( x_1 - x_ 2 ) + ( x_2 - x_3 ) + ... + ( x_{n-1} - x_n )$。

## 思路

把括号打开后能发现

$$val = x_1 - x_2 + x_2 - x_3 +...+ x_{n-1} - x_n$$

合并一下，发现

$$val = x_1 - x_n $$

易证，当 $x_1$ 最大， $x_n$ 最小时，$val$ 最大。

因此，只需对序列 $x$ 排序，输出最大值，剩下按字典序输出，再输出最小值即可。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<sstream>
#include<queue>
//#include<map>
#include<vector>
#include<math.h>
using namespace std;
//#define int long long
#define forr(i,a,b) for(int i=a;i<=b;i++)
#define repp(i,a,b) for(int i=a;i>=b;i--)
#define INF 1e9
#define ll long long
#define MAXN 200005
const int _x[]={0,1,0,-1,0},_y[]={0,0,1,0,-1};
#define mem(a,n) memset(a,n,sizeof(a));
#define chkmax(a,b) a=a>b?a:b;
#define chkmin(a,b) a=a<b?a:b;
#include<set>
#include<stack>
#define DE puts("check");
int a[MAXN];
int n;
int main(){
	scanf("%d",&n);
	forr(i,1,n){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	printf("%d ",a[n]);
	forr(i,2,n-1){
		printf("%d ",a[i]);
	}
	printf("%d",a[1]);
} 
```

---

## 作者：呵呵侠 (赞：1)

为了方便表述，我将价格命名为 $price$ 。

那么可知： $price = a_1 - a_2 + a_2 - a_3 + a_3 - …… -a_{n - 1} + a_{n - 1} - a_n$

此时我们发现，从 $a_2$ 到 $a_{n - 1}$ 的所有的数值都被一加一减抵消了，类似于整数裂项，结果就变成了第一项减去最后一项。

那么如果我希望结果尽可能地大，就必须要让最大的数放在最前面，最小的数放在最后面。

所以可以用 $\operatorname{sort}$ 函数来排序。

排序之后，先输出最后的数值，最后输出最前面的数值（ $\operatorname{sort}$ 是从小到大排序）。

那中间呢？

实际上，按照字典序排序，其实就是从小到大排序。

所以代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[110];
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i = i + 1)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    cout << a[n] << " ";
    for(int i = 2; i < n; i = i + 1)
        cout << a[i] << " ";
    cout << a[1] << endl;
    return 0;
}
```

当然，也可以从大到小排序，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[110];

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i = i + 1)
        cin >> a[i];
    sort(a + 1, a + 1 + n, cmp);
    cout << a[1] << " ";
    for(int i = n - 1; i > 1; i = i - 1)
        cout << a[i] << " ";
    cout << a[n] << endl;
    return 0;
}
```

$\mathtt{end}$

$\mathtt{Thank\ you\ for\ watching.}$

---

## 作者：_Fatalis_ (赞：0)

观察原序列，
$$
(x_1-x_2)+(x_2-x_3)+\cdots+(x_{n-1}-x_n)
$$

可以化简得到

$$
x_1-x_2+x_2-x_3+\cdots+x_{n-1}-x_n
$$

所以，抵消中间的项，可以得到最终式子为

$$
x_1-x_n
$$

要让这个最大，直接让 $x_1=\max\{x_i\},x_n=\min\{x_i\}$ 即可。

又要求按照字典序排列，那么排一遍序，最后交换首尾两个数字，就 ok 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10001];

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);swap(a[1],a[n]);
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    return 0;
}
```

---

## 作者：yinhy09 (赞：0)

### 这道题是贪心题，本以为很水，后来发现有坑！
我们首先化简公式；

 `value=(x[1]-x[2])+(x[2]-x[3])+···+(x[n-1]-x[n])`
 展开括号并消去相同的项可变为`x[1]-x[n]`，这下瞬间解决！
 
化简后贪心策略也很简单，只需要将最大数存为`x[n]`，同理，最小数存为`x[1]`，这样差最大，因为是字典序，所以中间`n-2`个从小到大输出即可。看似简单，但是如果直接暴力用`sort`会TLE!
~~（至少我TLE了）~~

于是想到了大顶堆和小顶堆，时间效率更高，所以会比`sort`快。

定义一个数组`ans`用来存从大到小排序结果，最后先输出最大的，再输出由小到大的中间`n-2`个，最后输出最小的。

## AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){ 
	priority_queue<int> q;//大顶堆
	int n;
	cin>>n;//数字个数
	int a;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		q.push(a);//放入堆中
	}
	int ans[102];
	for(int i=1;i<=n;i++)
	{
		ans[i]=q.top();//把最大的存进去
		q.pop();//清除最大的
	}
	cout<<ans[1]<<" ";//先输出最大的
	for(int i=n-1;i>1;i--) cout<<ans[i]<<" ";//由小到大输出中间部分
	cout<<ans[n];//输出最小的
	return 0;
}

```


---

## 作者：hyc1026 (赞：0)

首先，我们看到这个公式，是一定要化简滴！

原公式：

$(x_1-x_2)+(x_2-x_3)+\cdots+(x_{n-1}-x_n)$

化简为：

$x_1-x_2+x_2-x_3+\cdots+x_{n-1}-x_n$

进一步化简：

$x_1-x_n$

有了公式就好办了，利用 sort 排序就可以解决啦！

先求最大最小，然后将第 $2$ 个数到第 $n-1$ 个数从小到大排序即可。

### AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[101];

bool cmp(int x,int y) //cmp函数帮助sort实现效果
{
    return x > y;
}

int main()
{
    int n;
    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i];
    sort(a+1,a+n+1,cmp); //求最大最小
    sort(a+2,a+n); //其它数从小到大排序
    for(int i=1; i<=n; i++) cout << a[i] << " ";
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

根据题意，首先将表示价值的公式化简
$(x[1]-x[2])+(x[2]-x[3])+···+(x[n-1]-x[n])$
$=x[1]-x[2]+x[2]-x[3]+···+x[n-1]-x[n]$
$=x[1]-x[n]$

可以得到，这串数的“价值”其实就相当于第一个数减去最后一个数。

想要得到最大的价值，就需要第一个数尽可能大，最后一个数尽可能小。

利用c++的sort函数，即可对这串数进行排序，排序后数组的第一个元素就是最小数，最后一个就是最大数。

中间的数要求按照字典序输出，其实就是从小到大输出。

$Code:$
```
#include<bits/stdc++.h>
using namespace std;
int main (){
	int n,a[109]={0};
	cin>>n;
	for (int i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+1+n);//从小到大进行排序
	cout<<a[n]<<" ";//输出最大数以及一个空格
	for (int i=2;i<=n-1;i++)//从中间的最小数开始循环到中间的最大数
	cout<<a[i]<<" ";//输出
	cout<<a[1]<<endl;//输出最小数
	return 0;
}
```


---

## 作者：yf最qhhh (赞：0)

我们可以对原序列进行一些变形：

$\qquad(x[1]-x[2])+(x[2]-x[3])+···+(x[n-1]-x[n])$

$=x[1]-x[2]+x[2]-x[3]+···+x[n-1]-x[n]$

$=x[1]-x[n]$

所以原式想要最大，$x[1]$ 要取序列的**最大值**，$x[n]$ 要取序列的**最小值**。

中间的部分因为要使**字典序最小**，所以只需从小到大排列。

$Code:$
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rll register long long
using namespace std;
ll arr[1000005];
int main(){
	rll n,i;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&arr[i]);
	}//输入
	sort(arr+1,arr+1+n);//排序
	printf("%lld ",arr[n]);//先输出最大值即x[1]
	for(i=2;i<n;++i){
		printf("%lld ",arr[i]);//中间的部分直接输出就好了
	}
	printf("%lld",arr[1]);//最后输出最小值即x[n]
	//system("pause");
	return 0;
}

```
请勿抄袭！！！！！！！！！
------------


---

## 作者：happybob (赞：0)

仔细观察，其实这个价格是可以抵消的

看：

价格 = (x1 - x2) + (x2 - x3) + (x3 - x4) + (x(n - 1) - xn)

所以会发现，x2和x2抵消，x3和x3抵消……其实最后就是x1 - xn

所以具体代码如下，用的是STL的vector，一会会讲到vector的使用：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector <int> vec;

bool cmp(int x, int y)
{
    return x > y;
}

int main()
{
    int n;
    cin >> n;
    vec.resize(n);
    vector <int>::iterator it;
    for(it = vec.begin(); it != vec.end(); it++)
    {
        cin >> *it;
    }
    sort(vec.begin(), vec.end(), cmp);
    cout << vec.at(0) << " ";
    for(it = vec.end() - 2; it != vec.begin(); it--)
    {
        cout << *it << " ";
    }
    cout << vec.at(n - 1);
    cout << endl;
    return 0;
}
```

vector是c++STL库的一种容器，常被称为动态数组，可以动态赋值，出示定义可以写大小，也可以不写，定义方式如下：

```cpp
vector <数据类型> 名称;
```

vector还有很多函数等，需要包含头文件 #include <vector>

---

## 作者：Eason_AC (赞：0)

## Content
对于一个有 $n$ 个数的数列$\{x_1,x_2,x_3,...,x_n\}$，它的价值 $S=(x_1-x_2)+(x_2-x_3)+(x_3-x_4)+...+(x_{n-1}-x_n)$。现在给定 $n$ 个数，让你通过重新排序使得 $S$ 最大。

数据范围：$2\leqslant n\leqslant 100, |x_i|\leqslant 1000$。

## Solution
看上去这个 $S$ 的表达式很复杂，但是，我们尝试化简一下：

$S=x_1-x_2+x_2-x_3+x_3-x_4+...+x_{n-1}+x_n=x_1-x_n$

这就说明，要使 $S$ 最大，就要使第一个数和第 $n$ 个数的差最大，也就是要使 $x_1$ 最大， $x_n$ 最小。也就是说， $S$ 和 $x_2,x_3,...,x_{n-1}$无关！所以，我们就直接将其变成升序序列（主要是因为要使字典序最小），然后将第一个数和第 $n$ 个数调换顺序，最终的序列就是我们要求的序列。

## Code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, a[100007];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)	scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	printf("%d ", a[n]);
	for(int i = 2; i < n; ++i)	printf("%d ", a[i]);
	printf("%d", a[1]);
	return 0;
}
```

---

## 作者：Mysterious_bird (赞：0)

~~**大大大大大大大水题**~~

略加思考一下就行了

这个式子不要看它很复杂，把他去一下括号就知道了

（x[1]-x[2])+(x[2]-x[3])+....+(x[n-1]-x[n])

=x[1]-x[2]+x[2]-x[3]+x[3]-……+x[n-1]-x[n]（然后抵消）

=x[1]-x[n]

所以，我们只要从小到大排一遍序，然后交换首项和末项（刚刚化简过了，看出中间怎么加减都是0，不会改变。要结果最大，就要拿最大的减最小的）

### 直接上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[10005];   //开个数组
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);       //从小到大排序，注意，sort是左闭右开
    cout<<a[n]<<" ";    //输出最大的
    for(int i=2;i<n;i++)    //输出中间的数
    {
        cout<<a[i]<<" ";
    }
    cout<<a[1]<<'\n';   //输出最小的
    return 0;   //结束
}
```



---

## 作者：两年打铁 (赞：0)

（x[1]-x[2])+(x[2]-x[3])+....+(x[n-1]-x[n])

我们把它展开来，发现这个式子就是x[1]-x[n]。（~~是不是很难啊~~）

那么就变成了这个序列的头尾分别是最大和最小值。

按字典序排序，那么什么是字典序呢，就是按题目里的说的那样（~~废话~~）

那这个只需要排一遍序，交换头尾就行了啦。



------------


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000020];
void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')pd=-pd;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
void write(const int &x)
{
	char f[1000001];
	int tmp=x;
	if(tmp==0)
	{
		putchar('0');
		return;
	}
	int s=0;
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		f[s++]=tmp%10+'0';
		tmp/=10;
	}
	while(s>0)
	{
		putchar(f[--s]);
	}
}
signed main()
{
	read(n);
	for(register int i=1;i<=n;++i)
	{
		read(a[i]);
	}
	sort(a+1,a+n+1);
	swap(a[1],a[n]);
	for(register int i=1;i<=n;++i)
	{
		write(a[i]);
		putchar(' ');
	}
	return 0;
}
```

------------


---

## 作者：WLR__jr (赞：0)

## 怎么说呢？
#### 这是一道除了排序还是排序的~~难~~题
有什么是一次排序不能解决的问题呢？如果有，那就两次······

废话不多说，直接上代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[110];
int main()
{
    int n;scanf ("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    sort(a,a+n);
    printf("%d ",a[n-1]);
    for(int i=1;i<n-1;i++){printf("%d ",a[i]);}
    printf("%d\n",a[0]);
    return 0;
}
```

---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF347A)

### 化简及思路
我们先来观察一下有趣的公式，不难看出，算到最后的结果为 ``` x [1] − x [n] ``` 于是这道题就由原来复杂的公式变为了一道简洁明了的题。


------------

通过化简公式，我们来看一下：
1. 输出数列中的最大值。
1. 接着再输出排列后的数列。
1. 最后输出数列的最小值。

还要注意一下第二步的 ```for``` 语句。因为不包括最后一项以及第一项，所以 ```i``` 是从 ```2``` 开始循环，过了  ```n-1``` 才能结束。



------------
### 完整 ```AC``` 代码:

```
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int n,a[101];
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    sort(a+1,a+1+n);
    cout << a[n] << " ";
    for(int i=2;i<=n-1;i++)cout << a[i] << " ";
    cout << a[1] << endl;
    return 0;
}
```


---

## 作者：qfpjm (赞：0)

# 题意

- 给一个序列 $x$，这个序列里的数是可以随意调换位置的，求当序列为什么顺序时， $(x_1-x_2)+(x_2-x_3)+···+(x_{n-1}-x_n)$ 最大。

# 题解

- 题目给的式子有点复杂，我们将其化简一下：

	$(x_1-x_2)+(x_2-x_3)+···+(x_{n-1}-x_n)$
   
   $=x_1-x_2+x_2-x_3+···+x_{n-1}-x_n$
   
- 化简到这里可以发现，中间的数一加一减，刚好抵消，最后剩下：

	$x_1-x_n$
    
- 那么，我们很容易可以看出，一头一尾，分别是序列中的最大最小值，便可以使式子结果最大，中间的数顺便字典序就好了。

- 把样例输入模拟，发现与样例输出一致，本题圆满解决。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[10001];

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
	}
	sort (a + 1, a + 1 + n);
	cout << a[n] << " ";
	for (int i = 2 ; i < n ; i ++)
	{
		cout << a[i] << " ";
	}
	cout << a[1];
	return 0;
}

```


---

