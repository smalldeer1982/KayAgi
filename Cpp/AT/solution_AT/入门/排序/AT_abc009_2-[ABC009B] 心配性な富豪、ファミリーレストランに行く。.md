# [ABC009B] 心配性な富豪、ファミリーレストランに行く。

## 题目描述

我是个富豪，甚至可以说是大富豪，拥有着数不尽的钱财。只要我想要的东西，都可以用这笔用不完的钱买到。然而，即便是这取之不尽的钱财，也无法买到人心。无论有多少钱，一旦招致了众多平民的反感，今后的生活也将变得困难。

这次，为了理解平民的心情，我第一次来到了所谓的家庭餐厅。翻开菜单，确认了菜品内容和价格，果然便宜得令人吃惊。每道菜的价格都微不足道，于是我想着干脆点最贵的那道菜吧。

不过仔细一想，我来家庭餐厅的目的是什么呢？既然是为了理解平民的心情，如果不考虑价格直接点最贵的菜，那就毫无意义了。如果我在家庭餐厅还故意点最贵的菜，甚至可能会让我的恶名远扬。

话虽如此，既然来了，还是想尝尝价格较高的菜品的味道。对了，那就点这家店里第二贵的菜吧。这样想着，我把菜品的价格都列了出来，但由于菜品种类太多，找出第二贵的那道菜还真有点麻烦。能不能写个程序来帮我找出来呢？

哦，对了，在写程序之前还有一点需要注意。如果最贵的菜有多道，比如有 $4$ 种菜，价格分别是 $100$ 日元、$200$ 日元、$300$ 日元、$300$ 日元，那么第二贵的菜就是 $200$ 日元的那道。

## 说明/提示

### 样例解释 1

这是题目描述中提到的例子。在这种情况下，最贵的菜是 $300$ 日元，第二贵的菜是 $200$ 日元。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
100
200
300
300```

### 输出

```
200```

## 样例 #2

### 输入

```
5
50
370
819
433
120```

### 输出

```
433```

## 样例 #3

### 输入

```
6
100
100
100
200
200
200```

### 输出

```
100```

# 题解

## 作者：智子·起源 (赞：35)

## 经典的下标计数（统计排序）
### 代码加了注释，更适合新手观看^_^
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,a,b[1000+5],t;
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
    scanf("%d",&a);
    b[a]=1;//下标计数（以数字为下标，记录该数字出现过。用下标计数主要用途是去重）
  }
  for(int i=1000;;i--)
  {
    if(b[i]>0)t++;//如果找到了第一大的，那就记录第一大的已找到。
    if(t==2){printf("%d\n",i);return 0;}//如果这是第二次记录（这是第二大的）那就输出当前的数。
  }
  return 0;
}
```
如果这篇题解帮助了你，帮忙点个赞，谢谢！^_^

---

## 作者：liuzitong (赞：8)

# 日常刷岛国水题
最后换号啥的其他人都说了，我就不强调了（~~好像还是说了~~）

#### 我看其他人都用的什么什么排序，要么是桶排直接算，要么其他排序加计数器，我就发一篇小白专属题解（因为不需要排序）
#### 只要学了if和for就能看懂，（~~好吧，实际上排序函数也都能看懂~~）
###### 对了，此题解小白专属（~~dalao绕道~~）
交代码
```cpp


#include <bits/stdc++.h>
using namespace std;
int a[101];
int main(){
	int n,e1=0,e2=0;//找最大要设成0，为什么呢？？
	cin>>n;
	for(int i=1;i<=n;i++){//输入
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){//找第一大
		if(e1<=a[i]){
			e1=a[i];
		}
	}
	for(int i=1;i<=n;i++){//如果是第一大不要管，找第二大
		if(a[i]!=e1)
		if(e2<=a[i]){
			e2=a[i];
		}
	}
	cout<<e2<<'\n';//别忘了换行
	return 0;
}
```
#### 小白专属 ，dalao勿喷

---

## 作者：Leaved_ (赞：2)

看到还没有人用 set (集合 STL) 做这题，于是来搞一下...

因为 set 自带去重，所以做这题倍爽

翻译有误（倒数第二个数

# ~~STL 大法好~~

~~Ps:代码在注释里（~~

Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

set <int> s;集合 

int main() {
	cin>>n;
	int maxn=INT_MAX;
	for(int i=1;i<=n;i++) {
		int a;
		cin>>a;红题  懒得用快读... 
		s.insert(a);插入集合
		maxn=min(maxn,a);找最小值 
	}
	int ans=maxn;相当于排序完的第一个数 
	for(int i=2;i<s.size();++i) {
		ans=*s.lower_bound(ans+1);找比 ans 大的第一个数 相当于 一步一步往上走， 小于 s.size() 说明找到倒数第二个数 
	}
	cout<<ans<<endl; ATCoder 换行会死... 
}
```

# ~~没加//，直接 Copy 会 CE~~


---

## 作者：Yummy_ (赞：2)

不同于其他题解！
运用了去重的函数，unique（，）；
这里有这个函数的介绍：

https://baike.so.com/doc/8437395-24987996.html
------------

接下来直接：
Code：
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50005];
int main(){
	int n,u;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);//sort排序，相信你会的 
	u=unique(a+1,a+1+n)-a-1;//去重步骤 
	cout<<a[u-1]<<endl;//由于从小到大，所以从后往前找第二大 ,别忘了换行！！ 
	return 0;//功德圆满
} 
```
NOIP2019 RP++
------------




---

## 作者：华恋_韵 (赞：2)

听说各位大佬都在说降序排序，然后去重的工作，我感觉非常麻烦，于是我向大家介绍下面的一个基础算法：
## **集合**
    现在我们来构造一个集合。
C++ 中直接构造一个 set 的语句为：set<T> s 。这样我们定义了一个名为 s 的、储存 T 类型数据的集
合，其中 T 是集合要储存的数据类型。初始的时候 s 是空集合。比如 set<int> aa ， set<string> bbb
等等。
  
##   注意
  C++ 中用 insert() 方法向集合中插入一个新的元素。注意如果集合中已经存在了某个元素，再次插入不会产生任何效果，集合中是不会出现重复元素的。~~自动去重的喂~~
##   并且
  自动降序排列！！！！！
  
  好用到炸
  再介绍一下set的其他函数：
  |方法  | 功能 |
| :----------: | :----------: |
|insert  |插入一个元素 |
| erase  | 删除一个元素 |
| count |判断元素是否在 set 中  |
| clear  | 清空 |
| size  |获取元素个数  |
  
  还有迭代器，因为集合不能直接输出，我们要用一个类似于指针的东西获取地址输出
  
  set<T> s::iterator it=s.end()
  
  T为数据类型，s，it为自定义名s.end()表示获取最后一位地址
  一般循环输出会for（set<T> s::iterator it=s.begin()；it！=s.end()；it++）
  
  下面是AC代码：
  
  
  ```
#include<bits/stdc++.h>//万能头文件
  //也可以加#include<set>函数
using namespace std;
int main()
{
	set<int> sj;//定义一个集合
	int n,sum;
	scanf("%d",&n);//输入n
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&sum);//输入一个数
		sj.insert(sum);//插入到集合里去
	}
	set<int>::iterator it=sj.end();//定义一个迭代器
	it--;//暴力向后到倒数第二个
	it--;
	cout<<(*it)<<endl;输出
	return 0;
}
```
~~蒟蒻题解~~

   

---

## 作者：Yoo_ (赞：2)

这道题看起来很简单，但是实际上。。。也很简单
好了不闹了，这道题其实主要思想就是降序排序，因为升序排序求得就是第二小了
所以代码如下
```
#include<bits/stdc++.h>
#define noiprp 100
using namespace std;
bool jiangxv(int a,int b)
{
  return a>b;//如果是a<b就是升序
}
int a[10001];//被操作的数组
int main()
{
	int n;
	cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
	}
	sort(a+1,a+n+1,jiangxv);//降序排下来找
	int i=2;
	while(1)
	{
		if(a[i]!=a[i-1])//第一个和前面那个数不一样的就是我们要的结果
		{
			cout<<a[i]<<endl;
			return 0;
		}
		i++;
	}
	return 0;
}
```
代码中有一句
```
if(a[i]!=a[i-1])
```
举个例子，如果这个数列是1,1,2,3，3，排完序就是3,3,2,1,1
那么第二个数不是第二大的，所以必须是第一个和前面不一样的数，也就是a[i]!=a[i-1]

再见

---

## 作者：Asura_Arnold (赞：1)

$\color{white}\text{这题既然是入门题，我也不能让入门题这样水下去了！于是}$
$\color{fuchsia}\text{我用了大根堆。}$

### 那么
***步入*** 正题：
这道题容易错的原因在：
## $\color{red}\text{去重}$！
辣么，如何$\color{springgreen}\text{去重}$捏？

直接用一个$\color{aqua}\text{while}$函数排查下去啊！

本来，我写的是这样的东东：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	priority_queue<int> a;
	int n,o;
	cin >> n;
	for(int i = 1;i <= n;i ++)
	{
		cin >> o;
		a.push(o);
	}
	o = a.top();
	a.pop();
	while(o != a.top())
		a.pop();
	cout << a.top();
	return 0;
}
```
## 燃鹅...
好像有问题诶......

#### 于是就有了如下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	priority_queue<int> a;
	int n,o,l=1;
	cin >> n;
	for(int i = 1;i <= n;i ++)
	{
		cin >> o;
		a.push(o);
	}
	o = a.top();
	a.pop();
	while(o == a.top() && l < n-1)
	{
		a.pop();
		l ++;
	}
	cout << a.top() << endl;
	return 0;
}
```
$\color{gold}\text{两个}$错的地方

* 前面那个无法排除n个数都相等的情况
* 坑死人的岛国水题输出后没有换行居然判错了！！！
## $\color{silver}\text{（完）}$

---

## 作者：什么叫中二呀 (赞：1)

## 给大家介绍一种~~奇葩~~的做法！

### 具体复杂度：
#### **时间复杂度:O(N)**
#### **空间复杂度:O(1)**

当然，这数据不需要。

那如果N<1000000,每个数<10^18呢?

~~这题绿了就理所当然了~~

嗯，常规做法就……

[AC记录](https://www.luogu.org/record/show?rid=14829841)

具体原理：

~~和找最大值比较相似，~~不就是找两个吗……

但是我同学讲：那不是要数组存起来吗?

我又想了一下：为什么要数组呢,用两个变量存不就好了吗?

以下是漂亮的代码：(因为教练逼的……)
***
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,x,m1=-1,m2=-2;//m1存最大值，m2存次大值
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&x);
		if(x>m1)m2=m1,m1=x;//如果比最大值大，将最大值和次大值
        				   //同时更新
		if(x<m1&&x>m2)m2=x;//如果比次大值大，将次大值更新
	}
	printf("%d\n",m2);//记住要\n或者endl……
	return 0;
}
```
***

---

## 作者：きりと (赞：1)

**emm……此题略水**

我是用桶排了啦

但是，其实还有更省空间的方法（如模拟）

然而，题目既然已经给出n的范围，那不用桶排简直就是对不起出题者。

so~
```
#include<bits/stdc++.h>
using namespace std;
int n[1000];  //定义1000个桶（1~1000刚好1000个）
int main()
{
	int N,max=0,f=0,s=0;
	cin>>N;
	int a;
	for(int i=0;i<N;i++)
	{
		cin>>a;
		n[a]++;
		if(n[a]==1) s++;
		if(max<a) max=a;
	}
	for(int i=0;i<=max;i++)
	{
		if(n[i]>0) f++;
		if(f==s-1)
		{
			cout<<i<<endl;
			return 0;
		}
	}
}
```
本来还想打一点注释，但是实在太简单了，就不打了（颓废の标志）

---

## 作者：有限光阴 (赞：1)

# 这道题其实还算比较简单的
毕竟这道题不用太难的算法.

而且数据也很小.

如果这都不会做,你可以重新学了.

如果你是 _dalao_ ,你根本不用看题解.

本题解较为易懂,不喜勿喷.

------------
代码呈上
```
#include<bits/stdc++.h>//万能头文件.
using namespace std;
int f[1000001];//定义一个数组,要按照题目来设定,不要学我开这么大
int main(){//主函数
	int a;//定义一个int型的数.
	cin>>a;//输入这个数
	for(int i=1;i<=a;i++)cin>>f[i];//循环输入a个数.
	sort(f+1,f+a+1);//快速排序.
	for(int i=a-1;i>=1;i--){//从大到小寻找
		if(f[i]!=f[a]){
			cout<<f[i]<<endl;//找到就输出
			break;//退出循环.
		}
	}
	return 0;//好习惯.
}
```
至于上面用到的 _sort()_ 函数,不会的可以点击下面的链接学习

[sort()函数](https://baike.baidu.com/item/sort%E5%87%BD%E6%95%B0/11042699?fr=aladdin)

所有东西代码中都讲得很清楚了,我就不再多说.









---

## 作者：BqtMtsZDnlpsT (赞：1)

# AT907题解
传送门[at907](https://www.luogu.org/problemnew/solution/AT907)

at907≈[ 明明的随机数](https://www.luogu.org/problem/P1059)

思想1：桶排（排序+去重）但由于它是第二大的数要通过

```cpp
if(a[i])s++;
if((a[i])&&(s==2)){printf("%d\n",i);return 0;
```

来实现

[记录]( https://www.luogu.org/record/22568045)

代码1：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int n,a[1005],x,s=0;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&x),a[x]++;
	for(int i=1000;i>=0;i--)
	{
		if(a[i])s++;
		if((a[i])&&(s==2)){printf("%d\n",i);return 0;}
	}
	return 0;
}
```
思想2：

先排序
```cpp
sort(a,a+n);
```


再去重
```cpp
for(int i=0;i<n-1;i++)
{
 	if(a[i]==a[i+1])
   {
		for(int j=i;j<n-1;j++)a[j]=a[j+1];
		n--;
	}
}
```
代码2：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int n,a[1005],x,s=0;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
   sort(a,a+n);
	for(int i=0;i<n-1;i++)
	{
 		if(a[i]==a[i+1])
		{
			for(int j=i;j<n-1;j++)a[j]=a[j+1];
			n--;
		}
	}
   printf("%d\n",a[1]);
	return 0;
}

```

---

## 作者：RioBlu (赞：1)

桶排：轻松+愉快

代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,now;
bool c[1005];//一个桶
int main()
{
	cin>>a;
	while(a--)
	{
		cin>>b;
		c[b]=1;
	}
	for(int s=1000;s>=0;s--)
	{
		if(c[s])now++;//c[s]==1 now++
		if(now==2)//第二大的
		{
			cout<<s<<endl;
			return 0;
		}
	}
}
```

---

## 作者：CZQ_King (赞：1)

### 这道题比较水。


------------
思路：
输入数据后排序，从后面查找，如果$a[i]\neq a[i+1]$，输出$a[i]$并结束。


------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b[100];
int main(){
    cin>>a;//输入个数
    for(int i=0;i<a;i++)cin>>b[i];
    sort(b,b+a);//排序
    for(int i=a-2;i>=0;i--){//从后面查找
        if(b[i]!=b[i+1]){//如果不等于
            cout<<b[i]<<endl;//输出
            return 0;//并结束
        }
    }
}
```

---

## 作者：liaokq (赞：0)

# 看完题以后，不由得赞叹：岛国水题多啊

## 这种题目，居然还是绿色的？

### 换成P打头估计就一个入门


闲话少说，言归正传

~~（套用我们班前班主任的话）~~



------------


# 一波桶排走起

先说理论：

桶排序 (Bucket sort)或所谓的箱排序，是一个排序算法，工作的原理是将数组分到有限数量的桶子里。每个桶子再个别排序(有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序)。桶排序是鸽巢排序的一种归纳结果。

~~好像不懂这个也没有关系……~~

——————————     （华丽的分割线）    ———————————

桶排序有一个缺点，就是如果数据很大的话，就非常消耗内存，比如1,10000,10000000
但是这题只有1~1000,所以放心打桶排啦。

桶排核心代码：

```cpp
cin>>t;
a[t]++;
```

我看到楼下很多大佬在叫嚣“去重！去重！”，其实个人认为并不要，只要做以下修改：

```cpp
cin>>t;
a[t]=1;
//a数组改为bool类型
```
——————————  （又一个华丽的分割线）  ———————————

上AC代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;

bool a[1001],p;//因为是第二大，所以引入一个判断变量p
int n,i,t;
int main()
{
	cin>>n;
    //桶排：
	for(i=1;i<=n;i++)
	{
		cin>>t;
		a[t]=1;
	}
	for(i=1000;i>=0;i--)//是从大到小，不要搞反
	{
		if(a[i]==1)
		{
			if(p==0)p=1;//啊？这是最大的？
			  else//这才是答案
			  {
			  	cout<<i<<endl;return 0;//漂亮的结束
			  }
		}
	}
}
```
### 遵守洛谷规定，切勿Ctrl+C

---

## 作者：Frank_R_Z (赞：0)

###
这道题要找第二大的数，直接排序不行，就像这样
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1002];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	cout<<a[n-1]<<endl;
	return 0;
}

```
如果有数字重复的话就会爆零。Emmm

------------
以下是正确代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,h[3000],k,a[1002];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		h[x]++;
		if(h[x]==1)a[++k]=x;//使用桶排去重
	}
	sort(a+1,a+k+1);//sort一遍
	cout<<a[k-1]<<endl;//此时输出就没问题了
	return 0;
}

```


---

## 作者：谷民 (赞：0)

#### 裸的桶排模版

先讲一下大体思路：O（n）桶排去重，然后O（N）查找第二大的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[1005]={0};//按要求定义，注意桶排数组大小是由输入序列最大值决定的
bool temp=0;//去读最大的元素使用的开关
int main(){
    cin>>n;//输入个数
    for(int i=1;i<=n;i++){//循环输入元素
    	cin>>x;//输入元素
    	a[x]=1;//桶排处理，入桶
	}
	for(int i=1000;i>=1;i--){//查找第二大的
		if(a[i]&&temp){//第二大的
			cout<<i<<endl;//输出，注意AT题的换行
			return 0;
		}
		if(a[i]&&!temp){//排除最大元素
			temp=1;
		}
	}
}
```



---

## 作者：伍六七 (赞：0)

## 这道题的基本思路就是去重，然后再找出第二大。
然后就会想到用桶排同时去重和排序，~~这应该是最简单的方法了吧~~大佬勿吐槽

原理是用数组计数存数，这样便可以去重了（特殊判断，无论多少个都当一个）再用个循环把第二大输出。

附上程序：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int big,n,ans,f[10000],a,b[10000];//数组范围1000就够了，本人求稳开得大
string st[10000];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		cin>>a//输入
		b[a]++;//数组计数
		big=max(big,a);//找所有数的上限
	}
	for (int i=1;i<=big;i++)
	{
		if (b[i]>=1&&i!=big) ans=i;//i==big时是最大，这里不取最大就会取第二大
	}
	cout<<ans<<endl;//输出
   return 0;
}
```
本人用的方法可能不是每一个人都懂，以后可能会专门写写桶排的正确用法（逃

---

## 作者：百里亦守约 (赞：0)

                    又是一道“~~愚人节~~”的一题目
看了看下面的大佬都用的是桶排和快排，我随便想想想出了一种既不用桶排也不用快排的做法。。

详细的解读：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,bigg,big,x;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x; //输入第n个数
        if(big<x) //如果目前最大的比这个数小的话
        {
        	bigg=big; //那么目前最大的变成了第二个最大的，所以就将他记在要输出的数上了。
        	big=x; //更新目前最大的数。
        }
        else if(bigg<x && x!=big) bigg=x;//如果遇到了与最大的数重复的数字，我们不要去记住，我们只要记住比第二个最大的数还要大的但是又不是最大的数。
    }
    cout<<bigg<<endl; //做AT的题目都要换行。
    return 0; //结束。
}
```


---

## 作者：Juvenile (赞：0)

#### 这道题我的方法和楼上的都很像


------------
## 但是，（重点来了）
# 一定要输出一个·换行---~~一脸懵逼~~
~~（流泪）~~调了20分钟，结果换行没输

所以，这个悲惨的故事告诉我们

### 换行大法好，大佬们一定不要忘记偶

 //官方版：提示1-6：在算法竞赛中，每行输出均应以回车符结束，包括最后一行。除非特别说明，每行的行首不应有空格，但行末通常可以有多余空格。另外，输出的每两个数或者字符串之间应以单个空格隔开。           （。。。）

#### 即使这样，还是献上代码
```cpp
#include <bits/stdc++.h> 
using namespace std;
int a[100009];
bool cmp(int a,int b)
{
  return a>b;
}
int main()
{
	int n;
	cin>>n; 
	for(int i=1;i<=n;i++)	
		scanf("%d",&a[i]);
	sort(a+1,a+n+1,cmp);
	int i=2; 
	while(1)
	{
		if(a[i]!=a[i-1]) 
		{
			cout<<a[i]<<endl;
			return 0;
		}else i++;
	}
	return 0;	
}
```


---

## 作者：meyi (赞：0)

~~STL大法好！~~

思路：先排序，后去重~~（一切皆由STL完成）~~

上代码：
```cpp
#include<cstdio>
#include<algorithm>	//sort,unique所在头文件
using namespace std;
int a[101],n;
main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",a+i);
    //输入
	sort(a,a+n,[](int x,int y){return x>y;});
    //STL的sort相信大家都知道，第三个参数是C++11的新特性“lambda语句”，可以去了解一下
	n=unique(a,a+n)-a;
    //STL的去重
	printf("%d\n",n?a[1]:a[0]);
    //输出
}
```

---

## 作者：0凌0 (赞：0)

~~做岛国欢乐水题，有助于增强信心~~  
这题可以说是水的可以了，2<=N<=100，N个数字的范围在1~1000，很明显是让你**桶排**  
### 不解释上代码： 
```cpp
//MADE BY ZLZ
#include<iostream>
int n,z=2,a[1005],i; //z用来记第二大的数
int main()
{
	std::cin>>n;
	while(n--)
	{
		cin>>i;
		a[i]=1;
	}
	for(i=1000;z;i--)z-=a[i];
	std::cout<<i+1<<endl; //注意i要加1，别忘了换行
}
```
#### 好吧，我觉得这题看题解没有什么必要，不如自己做吧

---

