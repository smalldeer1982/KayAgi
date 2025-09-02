# Second Order Statistics

## 题目描述

### 题面描述

给定一个数组，输出其中第二小的整数（相等的整数只计算一次）。

## 样例 #1

### 输入

```
4
1 2 2 -4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 3 1 1
```

### 输出

```
2
```

# 题解

## 作者：zr太弱了 (赞：6)

看到第2小整数这个题目，果断使用sort从小到大排序，然后输出数组里的第二个数，然后n<2时特判输出NO，过了样例，以为能AC，结果……

[珂怕の评测记录](https://www.luogu.org/recordnew/show/23549653)


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n+1],i;
    for (i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
	if(n<2)
		cout<<"NO"; 
    else
    	cout<<a[2];
    return 0;
}
```

后来，我又看了一遍样例，发现第一小的整,是可以重复的，所以我们输出的不一定是数组中的第二个数，而且不一定只有在n<2时无解，整个数组相同也无解；

优化后的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n+1],i;
    for (i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
	for(i=1;i<=n;i++)
    {
        if(a[i]>a[1])
        {
        	cout<<a[i];
        	return 0;
		}
	}
	cout<<"NO"; 
    return 0;
}
```

本蒟蒻的第二篇题解，希望管理大大能通过！


---

## 作者：ACE_ZY (赞：3)

什么 居然没有pascal桶排的题解 那只好由本蒟蒻来一篇了

题意理解简单:输入一串数字 放入数组 输出其中**第二小**的整数

要注意的是他会出现负数 可是最大不超过100 所以用桶排做应该是最方便的

PS:**相等的整数只计算一次**

附上pascal代码
```pascal
var
  i,n,s,x:longint;
  a:array[-100..100] of longint;//定义-100到100的数组 不用太大
begin
  readln(n);//n个数
  for i:=1 to n do begin read(x);a[x]:=1;end;//输入一个数 统计(统计的不是个数 而是是否出现)
  for i:=-100 to 100 do//从-100到100找数
  begin
    if a[i]=1 then//如果有则做
    begin
      s:=s+1;//进来一次则出现一次
      if s=2 then begin write(i);exit;end;//如果个数等于2(相当于第二小的数字) 输出那个数 直接退出
    end;
  end;
  writeln('NO');//因为之前有退出 所以只有没满足 才不退出 相当于只有1个数
end.
```

桶排这么好用 为什么没这个pascal的题解呢

望通过 谢谢

---

## 作者：AntaresQAQ (赞：3)

STL大法好，这里说个stl的简单做法。

首先了解一下set容器，set是stl模板库里面的不可重复集合容器，它的后台封装采用的是二叉搜索树，根据二叉搜索树的性质，插入set的第一个元素是最小的。

那么这道题，就可以利用这个性质，插入所有的元素，把set里面的第一个元素（最小的元素）删除，然后输出当前最小的元素就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,x;
set<int> s;//不可重集合容器，插入元素后满足元素互异性 

int main ()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		s.insert(x);//插入元素 
	}
    s.erase(s.begin());//删除第一个也是最小的元素 
    if(s.empty())
		puts("NO");
	else
    	cout<<*s.begin()<<endl;//输出当前第一个也是当前最小的元素 
    return 0;
}
```

---

## 作者：_Qer (赞：3)

~~水一手题解~~ 

直接一遍循环

因为只求第二小的，所以可以不存数组  

边输入边判断是否是第二小的数  

最后输出即可
  
```cpp
#include<iostream>  
using namespace std;  
int n,x,ans=101,minn=101;//分别为数组长，元素，第二小，最小    
int main(){  
	cin>>n;    
	for(int i=0;i<n;++i){  
	    cin>>x;//输入一个元素  
	    if(x==minn||x==ans){//如果重复了就跳过  
	        continue;  
	    }  
	    if(x<minn){//如果是当前最小   
	        ans=minn;//把上一个最小的变成第二小的  
	        minn=x;//现在最小的换掉  
	    }else if(x<ans){//如果是第二小的   
	        ans=x;   
	    }  
	}   
	if(ans==101){//101是初始值，如果第二小的数是初始值就代表没有第二小的数   
	    cout<<"NO";  
	}else{  
	    cout<<ans;  
	}  
	return 0;  
} 
```

---

## 作者：Siyuan (赞：2)

## 发一个桶排题解！

### 本题思路：

1. 以 O(1) 的空间读入数据，在此过程中进行桶排思想的统计。（考虑到有负数，故将所有数统计前加上100，输出时再减去100）

2. 将0~200的范围进行一次搜索，如果某个数出现过，则将cnr加1（初始为0），如果cnr等于2则输出此时的数（注意减去100）。

3. 如果该范围全部搜索完后，cnr的值依旧没有等于2，则输出“NO”。

上代码！（代码中注释不加了，上方思路很清楚）

```cpp
#include<iostream>
using namespace std;
int n,a,cnr=0,p[201];
//此处的p[201]完全可以写成bool类型！本人写代码时没考虑到压空间……
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    while(n--)
    {
        cin>>a;
        p[a+100]++;
    }
    for(int i=0;i<=200;i++)
    {
        if(p[i])  cnr++;
        if(cnr==2)  {cout<<i-100;return 0;}
    }
    cout<<"NO";
    return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：1)

题意：给定一个数组，输出其中第二小的整数（相等的整数只计算一次）

此题n只到100，可以模拟。时间复杂度O(n)，空间复杂度O(n)。

详见代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n+1],i;
	for (i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);//将a数组从小到大排序
	i=1;//此处往下是本段程序的核心，即找到数组内第二小的元素
	int fxt;
	fxt=a[1];//fxt一直存放数组内最小的元素
	while (i<n)//如果i=n了还没有与fxt不同的元素，输出NO
	{
		i++;//由于数组已经按从小到大排序，i从2开始遍历数组，只要找到与fxt不同的元素即第二小的元素
		if (a[i]!=fxt)
		{
			cout<<a[i]<<endl;
			return 0;
		}
	}
	cout<<"NO"<<endl;//输出NO
	return 0;
}
```

---

## 作者：不到前10不改名 (赞：1)

//这题看到那些c++党的大佬什么去重集都震惊了qwq（作为c党我太弱了）  
//说说思路，其实一开始当我看到题目时想的是桶排，但是有负数不太想处理（其实也可以做）   
//于是就肯定是排序记录了！
```
#include<stdio.h>
int n,srx[1001],sry,t,i,j;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d",&srx[i]);
    for(i=1;i<=n;i++)
    for(j=i+1;j<=n;j++)//冒泡优化版本
    if(srx[i]>srx[j])
    {t=srx[i];
    srx[i]=srx[j];
    srx[j]=t;}//swap
    for(i=1;i<=n;i++)
    {if(sry==0)
    sry=srx[i];//记录第一个数
    else if(sry&&sry!=srx[i])//判断是否重复
    {printf("%d",srx[i]);
    return 0;}}//输出并结束
    printf("NO");//只有同1个数
    return 0;
    }
```

---

## 作者：_newbie_ (赞：1)

与其他题解不同，我做时没有去重，而是利用两数不等输出。
不要忘记边界。


------------

```c
#include<iostream>
#include<cstdio>
#include<cmath>
int b[101];
using namespace std;
int main()  
{
    int a;cin>>a;
    for(int i=1;i<=a;i++)
    cin>>b[i];
    if(a==1)  //为1时的特判 
	{
		cout<<"NO";
		return 0;
	} 
    for(int i=a-1;i>=1;i--)  //冒泡排序 
    {
       for(int j=1;j<=i;j++)
       {
       	  if(b[j]>b[j+1])  //从小到大排序 
       	  swap(b[j],b[j+1]);
       }	
    }
    for(int i=1;i<=a;i++)
    {
    	if(i==a)
    	{
    		if(b[i]!=b[i-1])  //判断最后的边界。由于b[a+1]==0,所以要特判 
    		{
    			cout<<b[i];
    		    return 0;
    		}
    		else
    		break;
    	}   	
        if(b[i]!=b[i+1]&&i<a)  //没到边界，看看是不是第二小
        {
        	cout<<b[i+1];
        	return 0;
        }			
    }
    cout<<"NO";  //没有结束程序，说明无解  	  
    return 0;
} 
```

---

## 作者：Andysun06 (赞：1)

## 一道简单的题
### 可怜的我把“第二小整数”看成“第二大整数”
#### 身为pascal的一员，没看见pascal的题解，就来一个：
    var n,m,i,j,f,t:longint;
    x:array[1..100]of longint;
    begin
    readln(n);//输入n
    for i:=1 to n do//输入n个数
     read(x[i]);
    for i:=1 to n-1 do//冒泡排序
     for j:=i+1 to n do
      if x[i]>x[j] then//注意：从小到大
       begin
        f:=x[i];
        x[i]:=x[j];
        x[j]:=f;
       end;
    for i:=2 to n do
     if x[i]>x[1] then//判断第二小整数
      begin
       writeln(x[i]);//找到就输出x【i】
       t:=1;
       break;//跳出
      end;
    if t<>1 then//没找到就输出‘NO’   NO要大写！！
     writeln('NO');
    end.//结束
# 严禁抄袭！！！

---

## 作者：Playnext (赞：1)

题意是求**第二小**的整数。


把这个数列排序一遍，取**第一个数**跟**剩下的数**比较。


若不同就说明找到了，但要是扫描一遍都没找到就是说明整个数列没有第二小的整数，直接输出NO。


代码1：


```cpp
#include <bits/stdc++.h>
using namespace std;    //BY Playnext
#define REG register
#define FOR(X,Y,Z) for (REG int X=Y; X<Z; X++)
const int MAXN=1e2+1;

int F[MAXN];

int main () {
//    freopen ("Input.txt", "r", stdin);
//    freopen ("Output.txt", "w",stdout);
    REG int n;        scanf ("%d", &n);
    FOR (i,0,n)        scanf ("%d", &F[i]);
    sort (F, F+n);        //排序
    REG int Smallest = F[0];    //取最小值
    FOR (i,0,n)
        if (F[i] != Smallest) {
            printf ("%d\n",F[i]);
            return 0;                //找到了的话输出后直接结束程序
        }
    printf ("NO\n");        //否则输出NO
    return 0;
}
```

或者去重后直接判定**第一个数**和**第二个数**是否相等。


代码2：


```cpp
#include <bits/stdc++.h>
using namespace std;    //BY Playnext
#define REG register
#define FOR(X,Y,Z) for (REG int X=Y; X<Z; X++)
const int MAXN=1e2+1;

int F[MAXN];

int main () {
//    freopen ("Input.txt", "r", stdin);
//    freopen ("Output.txt", "w",stdout);
    REG int n;
    scanf ("%d", &n);
    FOR (i,0,n)        scanf ("%d", &F[i]);
    sort (F, F+n);     
    unique (F, F+n);        //排序+去重
    if (F[0] == F[1] || n == 1) 
        printf ("NO\n");        //如果第一个数和第二个数或长度小于2相等输出NO
     else
         printf ("%d\n", F[1]);    //否则输出第二个数
    return 0;
}
```

---

## 作者：览遍千秋 (赞：1)

~~日常水题解~~


-----

这道题很简单，先sort一遍，再令k=a[1]，从前往后扫到的第一个不是k的就是解


----

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 107
int n,a[maxn],l;


inline void Init()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
}
inline void Work()
{
    sort(a+1,a+n+1);
    l=a[1];
    for(register int i=1;i<=n;i++)
    {
        if(a[i]!=l){
            printf("%d\n",a[i]);
            return;
        }
    }
    printf("NO\n");
}
int main()
{
    Init();
    Work();
    return 0;
}
```

---

## 作者：蒟蒻取不来名 (赞：1)

 $$QwQ$$

这是一道世界级水题

可我还是错了一次QwQ

有什么（水题）是一个sort不能解决的呢

```
#include<iostream>
#include<algorithm>
using namespace std;
int n, a[101], i;
int main()
{
	cin >> n;
	for(i = 0;i < n; i ++)
	{
		cin >> a[i];
	}
	sort(a, a + n);//排序快乐多
	for(i = 1; i < n; i ++)//个人觉得从第二个开始查找更简单
	{
		if(a[i] != a[i - 1]) {
		cout << a[i] << endl;
		return 0;//找到之后就可直接结束循环了
		}
	}
	return 0;
}
```

然后交上去美滋滋的等绿绿的100出现

结果却发现......为什么只A了两个点啊啊啊啊啊啊啊

吓得我回去看了一眼题目

## 如果不存在，则输出NO.

QwQ

又看了眼我的代码

果然是忘了判断不存在的结果

加一句“cout << "NO" << endl;” 就A了QwQ

下面AC代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n, a[101], i;
int main()
{
	cin >> n;
	for(i = 0;i < n; i ++)
	{
		cin >> a[i];
	}
	sort(a, a + n);
	for(i = 1; i < n; i ++)
	{
		if(a[i] != a[i - 1]) {
		cout << a[i] << endl;
		return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}
```

---

## 作者：Hola_chen (赞：1)

# 非喜勿喷~
```cpp
#include<bits/stdc++.h>//万能头~
using namespace std;
int main()
{
	//本题思路：开个数组直接搞定，sort~~~，最后判断 
	int a[1005];//int一个数组
	int n;//int一个n
	cin>>n;//输入n; 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//一个for循环输入这些数组 
	} 
	//以下判断是否输出NO
    int sum=0;//计数 
	int k=1;//充当数组 
	int hh=a[1];//对比 
	while(k=n) //while 
	{
		k++;
		if(a[k]==hh)
		{
			sum++;//比对，计数 
		}
	    k++;//k++	
	}
	if(sum+1==n)//判断每个数是否相等 
	{
		cout<<"NO";//输出
		return 0; 
	}
	if(n==1||n==0)//判断数组是否只有一个数 
	{
		cout<<"NO";//输出
		return 0; 
	}
	else
	{
		sort(a+1,a+1+n);//sort
	    cout<<a[2];//输出 
	} 
    return 0;
}
```
# 水过了~

---

## 作者：紫金依旧 (赞：0)

这道题其实是一道较水的题.

为什么呢?

其实可以直接排序+判断.

上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100+5],num;
int mian() 
{
	cin>>n;
	fro(itn i=1;i<=n;i++)
		cin>>a[i];//读入
	sort(a+1,a+1+n);//快排
	for(int i=1;i<=n-1;i++)//遍历
	{
		if(a[i]!=a[i+1])//如果发现了第二小的值
		{
			cout<<a[i+1];//输出
			return 0;
		}
      num=i;
	}
	if(num==n)//没有找到(全等或无数值)
		cout<<"NO";
	return 0;
}
```

# 打造文明洛谷

---

## 作者：CZQ_King (赞：0)

你们说有负数，但是没想过用$map$？

------------
做法：

类似于桶排，但是由于$a_i$有可能是负数，那么这里用了一个$map$。然后直接访问第二个小的元素。

记得要先判断$map$的长度是否为$1$，这说明只有一个数，那么不存在第二个大的数字，此时应该输出$NO$。

------------
代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a;
map<int,bool>t;//后面不必int
int main(){
	cin>>n;
	while(n--){
		cin>>a;
		t[a]=1;//map也可以像数组一样存入
	}
	if(t.size()==1){puts("NO");return 0;}//如果只有一个数
	map<int,bool>::iterator it=t.begin();//迭代器指向第一个数
	printf("%d",*++it);//输出第二个
}
```

---

## 作者：开心的猪 (赞：0)

这道题可以使用桶排序的思想做。
观察发现数据范围是-100到100，而c++只支持数组的下标是自然数，于是开了一个大小为201的数组，接下来每读入一个就下标为这个数字加100的那个数组元素变成1，最后找到数组中出现的第二个1，把他的下标减去100后输出就好了。

下面是代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n, ans=0;
	scanf("%d", &n);
	int alpha[n];
	for(int i=0; i<n; i++)
	{
		scanf("%d", &alpha[i]);
	}
	int alp[202]={0};
	for(int i=0; i<n; i++)
	{
		alp[alpha[i]+100]++;
	}
	for(int i=0; i<202; i++)
	{
		if(alp[i]!=0)
		{
			if(ans==1)
			{
				printf("%d", i-100);
				return 0;
			}
			ans++;
		}
	}
	printf("NO");
	return 0;
}
```


---

## 作者：MIN__2500 (赞：0)

本蒟蒻第一次发题解。~~路过可否一赞而过~~，感谢！
```cpp
#include <bits/stdc++.h>
using namespace std;
set<int>s;//stl库，大佬经常用s
set<int>::iterator it;//这个程序没用到，是set的迭代器
int main()
{
    int n,a[10000];
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        s.insert(a[i]);//推入元素
    }
    s.erase(s.begin());//删除开头
    if(s.empty())//判一下是否为空
        cout<<"NO";//如果为空就输出NO
    else
        cout<<*s.begin()<<endl;//*是取s.begin的地址。
    return 0;
}
```
set有一个好处，set会自动排序+去重。
以上是AC代码。
还有一种方法。


------------
**注意**
这个代码只能得两个点。
```
#include <bits/stdc++.h>
using namespace std;
set<int>s;
set<int>::iterator it;//set的迭代器
int main()
{
    int n,a[10000];
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        s.insert(a[i]);
    }
    it=s.begin();//迭代器指向s的开头
    it++;//it指向第二大的数
    cout<<*it<<endl;//输出取it的地址
    return 0;
}

```
~~路过点个赞，用赞报平安。~~
感谢！


---

## 作者：呵呵侠 (赞：0)

我的思路：

先用sort排序，然后从头遍历，第一项与前一项不相等的就是答案

AC代码：
```
#include <iostream>//本人不喜欢万能头文件
#include <algorithm>//sort必备
using namespace std;
int main()
{
    int a;
    cin>>a;
    int b[a];
    for(int i=0;i<a;i++)
        cin>>b[i];//前面都平淡无奇
    sort(b,b+a);//排序，STL大法好
    for(int i=1;i<a;i++)//遍历数组
        if(b[i]!=b[i-1])//第一项与前一项不相等
        {
            cout<<b[i];//输出
            return 0;//然后就可以bye bye了
        }
    cout<<"NO";//如果没出结果（没return 0;），就是都一样大，输出NO
    return 0;//好习惯养成
}
```

---

## 作者：开心的猪 (赞：0)

这题可以使用桶排序的算法思想做。

桶排序：创建一个数组，如果读入的数字是n，这个数组的第n项+1.（典型的空间换时间。）特别地，由于这题的数据范围涉及到了负数，而c++不支持数组下标是负数，所以可以把原来的第n项+1改成第n+100项+1.

下面是代码。

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n, ans=0;
	scanf("%d", &n);
	int alpha[n];
	for(int i=0; i<n; i++)
	{
		scanf("%d", &alpha[i]);
	}
	int alp[202]={0};
	for(int i=0; i<n; i++)
	{
		alp[alpha[i]+100]++;
	}
	for(int i=0; i<202; i++)
	{
		if(alp[i]!=0)
		{
			if(ans==1)
			{
				printf("%d", i-100);
				return 0;
			}
			ans++;
		}
	}
	printf("NO");
	return 0;
```


---

## 作者：Obito (赞：0)

# 排序

看到大家都是用排序做的，蒟蒻自然也来一发排序，不过我的思路是快排，并且不要做特殊判断。

具体详见代码
```
#include<bits/stdc++.h>//万能头
using namespace std;
int a[10001],i,j,k,n,m,s; //无脑定义，有用的只有a，i，s，n
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);niop用的文件
	cin>>n;//输入数字总数
	for(i=1;i<=n;i++)//输入数字
	scanf("%d",&a[i]);
	sort(a+1,a+1+n);//快排，默认从小到大
	s=1;//s用来记录到第几小，先从1开始
	for(i=2;i<=n;i++){//循环从2开始
		if(a[i]!=a[i-1])s++;//与之前的比较，如果不同，就证明这是一种新数字。
		if(s==2){//如果是第二小的直接输出结束。
			cout<<a[i];
		return 0;
	}
	}
	cout<<"NO";//如果没有第二小的，就出no
	return 0;//完美结束
}

```

谢谢各位dalao观看，不对的地方欢迎斧正

---

## 作者：康娜卡姆依 (赞：0)

### 其实它的考点是排序，略带去重的技巧。
**一份较长（跟楼下的dalao们比就相形见绌）而神奇的代码：**
```pascal
var n,i:integer;
    a:array[0..100] of longint;

procedure qsort(l,r:longint);//快排，其实长就长在这儿。。。
 var i,j,min,x:longint;
 begin
 i:=l;j:=r;min:=a[(l+r) div 2];
 repeat
 while a[i]<min do inc(i);
 while a[j]>min do dec(j);
 if i<=j then begin
 x:=a[i];a[i]:=a[j];a[j]:=x;
 inc(i);dec(j);
 end;
 until i>j;
 if i<r then qsort(i,r);
 if j>l then qsort(l,j);
 end;
begin
  read(n);
  for i:=1 to n do
  read(a[i]);
  qsort(1,n);
  a[0]:=a[1];//这一步主要是为了后面去重方便而设的。
  for i:=1 to n do
  if a[i]<>a[i-1] then begin write(a[i]); break; end;//这是精髓，在从小到大找到与前面数字大小不一样的就打出+退出。
  if a[n]=a[1] then write('NO');//如果整个数列就一个数字那么按题意输出
end.
  
   
    
```

---

