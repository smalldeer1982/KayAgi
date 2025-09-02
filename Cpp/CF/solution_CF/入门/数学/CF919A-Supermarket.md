# Supermarket

## 题目描述

We often go to supermarkets to buy some fruits or vegetables, and on the tag there prints the price for a kilo. But in some supermarkets, when asked how much the items are, the clerk will say that $ a $ yuan for $ b $ kilos (You don't need to care about what "yuan" is), the same as $ a/b $ yuan for a kilo.

Now imagine you'd like to buy $ m $ kilos of apples. You've asked $ n $ supermarkets and got the prices. Find the minimum cost for those apples.

You can assume that there are enough apples in all supermarkets.

## 说明/提示

In the first sample, you are supposed to buy $ 5 $ kilos of apples in supermarket $ 3 $ . The cost is $ 5/3 $ yuan.

In the second sample, you are supposed to buy $ 1 $ kilo of apples in supermarket $ 2 $ . The cost is $ 98/99 $ yuan.

## 样例 #1

### 输入

```
3 5
1 2
3 4
1 3
```

### 输出

```
1.66666667
```

## 样例 #2

### 输入

```
2 1
99 100
98 99
```

### 输出

```
0.98989899
```

# 题解

## 作者：Register (赞：6)

这道题好像输入格式写错了，是先输m再输n

这题真的是奆水

看大佬们都要把n代入比较，我觉得最后把n乘进去要方便一点
```cpp
#include <iostream>//输入输出流库
#include <cstdio>//printf库（格式化）
using namespace std;
int main(){
	double a,b,n/*好像可以小数吧*/,minn=999999999/*真小~~*/;
	int m;
	cin>>m>>n;
	while(m--)//m家店
	{
		cin>>a>>b;
		if(a/b<minn) minn=a/b;//比较
	}
	printf("%.8lf"/*样例好像是保留八位*/,minn*n/*把n乘进去*/);
	return 0;
}
```

---

## 作者：Reywmp (赞：3)

 _**巨水的题目** _~~（然而我交了好几次）~~

其实思路没有什么好讲的，因为无限量买apple那么只需要找到一个单价最便宜的超市使劲买就行了，很简单的 _**贪心** _ 想法。

------------

楼下dalao很强，ta的方法我一开始没有想到，用了 _**min()**_ 函数。效率比我的code不知道高多少。而我的做法，也很好理解，我用的同是 _**algorithm**_ 中的函数， **_sort()_** 。

------------

思路：
用 _**double**_ 形变量 _**tmp**_ 存储a/b也就是单价。然后在存入数组 _**num**_ 时乘上 **_n_** 也就是如果在这家买要花多少钱！然后呢用sort排序， _**num[1]**_ 也就是最少花的价钱。

------------

by a way，题目翻译有些问题，楼下dalao说了一个“先输入m不是n”；不过还有一个就是m和n的数据范围弄反了。我就因为以为 _**m<=100**_ RE了好多次。。。反正应该是 **_(1<=m<=5000,1<=n<=100)_** ！！！


------------

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
double num[100005];//m<=5000不是100！
bool cmp(double x,double y)//由于不是int是double，我自己写了一个升序的cmp
{
    return x<y;
}
int main()
{
    int m,n;
    int a,b;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        double tmp=((double)a/b);//最好用下强制转换
        //printf("%.10lf %d %d\n",tmp,a,b);
        num[i]=tmp*n*1.0;
    }
    sort(num+1,num+1+m,cmp);
    printf("%.10lf",num[1]);//保留小数点后10位用"%.10lf"
    return 0;
}
```
~~emmmm，我好菜~~

---

## 作者：serverkiller (赞：1)

# CF919A 【Supermarket】
---
看到很多题解介绍了printf保留小数的写法 还没有介绍cout的方法
```
cout<<setiosflags(ios::fixed)<<setprecision(8);
```

上面那句话就是核心 这句话写完之后的所有输出都变成了保留8位

如果只想要单次输出把那个控制输出流的关掉就可以了

最后把AC代码奉上

```
#include <bits/stdc++.h>
using namespace std;

long double s,a,b,m;
int n,i;

int main(){
	cin>>n>>m;
	s=1234567;
	for(i=1;i<=n;i++) {
      cin>>a>>b;
      s=min(s,a/b);
	}
   cout<<setiosflags(ios::fixed)<<setprecision(8);
   cout << s*m << endl;
   return 0;
}
```

---

## 作者：FutureThx (赞：0)

## 目录

  ### 目录

  ### 1.题目大意
  
  ### 2.思路
  
  ### 3.代码
  
  ### 后记

 $ $
## 1.题目大意
$ $ 题面：[传送门](https://www.luogu.com.cn/problem/CF919A)

$ $

## 2.思路

这一题主要就是对于 $a ,b$ 两个数所组成的 $M$ 个元素中找每个元素中 $\frac{a}{b}$ 的最小值，然后再把这个值乘上 $N$ ，并输出，即可通过本题。

刚看到题面就立马想到手写对于结构体的快排，但本人太懒了就放弃了此思路，那我们就可以采用“打擂台”的方式进行筛选。

$ $

## 3.代码

思路清晰了以后我们就可以开始敲代码了
$   $ 
#### $O(N) \ 100pts$:
 
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int m,n;
    double min_x;
    cin >> m >> n;
    for(int i = 1;i <= m;i++){
        double a,b;
        cin >> a >> b;
        if(i == 1)min_x = a / b;//如果是第一次比较则为min_x初值
        else//否则将a与b的比值与min_x进行比较
            if((double)(a / b) < min_x)//若a:b比min_x还小则替换min_x
                 min_x = double(a/b);
    }
    printf("%.10f",min_x * n);
    return 0;
}
```
$ $

#### $O(nlogn)$ ~ $O(N^2)$ $ \ 100pts$:
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
struct sp
{
    int a,b
    double acb;
}bz[5001];//存储数据
void kp(int l,int r){//快排模板
    int i = l,j = r;double mid = bz[(l+r)/2].acb;
    do{
        while(bz[i].acb < mid)i++;
        while(bz[j].acb > mid)j--;
        if(i <= j){
            swap(bz[i],bz[j]);
            i++;
            j--;
        }
    }while(i <= j);
    if(i < r)kp(i,r);
    if(l < j)kp(l,j);
}
int main()
{
    int n,m;
    cin >> m >> n;
    for(int i = 1;i <= m;i++){
        cin >> bz[i].a >> bz[i].b;
        bz[i].acb = (double)bz[i].a / (double)bz[i].b;//读入a和b后处理数据
    }
    kp(1,m);//调用快排（升序操作）
    printf("%.10f",bz[1].acb * n);//输出
    return 0;
}
```

## 后记
这是本蒟蒻的第二篇题解，求管理员通过

---

## 作者：YUYGFGG (赞：0)

思路：贪心，找单价最便宜的超市买即可

用set从小到大排序
```cpp
#include<bits/stdc++.h>
using namespace std;
set<long double> c;//自动从小到大排序
int main(){
    int m,n;
    int a,b;
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        long double tmp=((long double)a/b);
        c.insert(tmp*n*1.0);//插入（*1.0用来强制类型转换，否则插入set的数是向下取整的int）
    }
    set<long double>::iterator it=c.begin();//最便宜超市的单价
    cout<<fixed<<setprecision(10)<<*it<<endl;//保留十位
    return 0;
}
```


---

## 作者：Arghariza (赞：0)

首先不扯别的，我们来看一下怎么存储价钱与重量。

我们可以定义两个数组：

```double money[100001], weight[100001]```

- 但是我懒。

**结构体大法好！**

我们可以定义一个结构体，里面存3个参数，一个money，一个kg，一个per表示他的“价性”比（也就是价格/重量）：

```
struct node {double mon, kg, per;} a[100001];
```

那么```a[i].per = a[i].mon / a[i].kg```（看着这句想想为什么mon和kg都是double类型？如果是int类型会发生什么事？）

然后我们可以通过STL中的**sort()**函数来按照per从小到达排序，则a[1].per就是最便宜的价格。

排序函数：

```
bool cmp(node x, node y) {
    return x.per < y.per;
}
```

排序语句：

```
sort(a + 1, a + n + 1, cmp);
```

最后我们按照8位四舍五入来输出（别忘记乘上m）：

```
cout << fixed << setprecision(8) << a[1].per * m;
```

所以整体代码出来啦：

```
#include <iomanip>//setprecision必须函数
#include <iostream>//输出流必须函数
#include <algorithm>//sort必须函数
using namespace std;//命名空间

struct node {double mon, kg, per;} a[100001];//定义结构体

int n, m;//定义种类与价格

bool cmp(node x, node y) {//按照“价性”比来从小到大排序（其实性价比从大到小也是可以的）
    return x.per < y.per;
}

int main() {
    cin >> n >> m;//输入
    for(int i = 1; i <= n; i++) {//输入
        cin >> a[i].mon >> a[i].kg;
        a[i].per = a[i].mon / a[i].kg;//求出“价性”比
    }
    sort(a + 1, a + n + 1, cmp);//排序
    cout << fixed << setprecision(8) << a[1].per * m;//保留8位小数输出
}
```

---

## 作者：Andysun06 (赞：0)

# 题解 CF919A


------------
## 一道做的容易说的难的题。。。
## 只要把每个超市买一kg苹果要多少钱算出来乘n就可以了。。。
### pascal题解：
    var f:real;//因为f要做交换的变量，所以要用小数
        i,j,n,m:longint;
        x,v,z:array[1..5000]of real;//因为z要有8位小数，所以用real（不是read！！！）还要是1..5000不然第四个点RE或TLE！！
    begin
    readln(n,m);//输入n，m
    for i:=1 to n do
    begin
    readln(x[i],v[i]);//输入x【i】，v【i】
    z[i]:=x[i]/v[i]*m;//计算在各个超市要多少钱
    end;
    for i:=1 to n-1 do
    for j:=i+1 to n do
    if z[i]>z[j] then//从小到大排序
    begin
     f:=z[i];//交换
     z[i]:=z[j];
     z[j]:=f;
    end;
    writeln(z[1]:0:8);//因为从小到大排序z【1】一定是最小的，所以直接输出z【1】（要保留八位小数：0：8！！！）
    end.



---

## 作者：_Qer (赞：0)

~~大水，为什么没有人发题解呢？~~  

题目翻译有点问题，先输入m再是n

看看样例就能分辨了

进入正题

用一个double类型的变量存当前最小的花费

每次输入a,b都判断一下是否是最便宜的

如果是就更新当前的最小化花费

最后输出即可

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a,b;//各变量用途见题面
double spend=99999;//当前最小花费，要初始化为一个很大的值
int main(){
    cin>>m>>n;//注意是先输入m，再输入n
    for(int i=0;i<m;++i){//边输入边判，不用都存下来
        cin>>a>>b;
        spend=min(spend,((double)a/b)*n);//取最小的花费
    }
    printf("%.10f",spend);//这里不要用cout，精度不够（血的教训）
    return 0;
}
```

---

