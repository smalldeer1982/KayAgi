# 眼红的Medusa

## 题目描述

虽然 Miss Medusa 到了北京，领了科技创新奖，但是她还是觉得不满意。原因是：他发现很多人都和她一样获了科技创新奖，特别是其中的某些人，还获得了另一个奖项——特殊贡献奖。而越多的人获得了两个奖项，Miss Medusa就会越眼红。于是她决定统计有哪些人获得了两个奖项，来知道自己有多眼红。

## 说明/提示

对于 $60\%$ 的数据，$0 \leq n, m \leq 1000$，获得奖项的人的编号 $\lt 2 \times 10^9$；

对于 $100\%$ 的数据，$0 \leq n, m \leq 10^5$，获得奖项的人的编号 $\lt 2 \times 10^9$。

输入数据保证第二行任意两个数不同，第三行任意两个数不同。

## 样例 #1

### 输入

```
4 3
2 15 6 8
8 9 2
```

### 输出

```
2 8```

# 题解

## 作者：Christopher_Yan (赞：84)

虽说这道题标签里写明了二分，然而我还是首先想到了map......毕竟map真的是简单好写。

###  map做法
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
map<int,bool> v;
int a[101000],b[101000];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {scanf("%d",&a[i]);}
	for(int i=1;i<=m;i++) {scanf("%d",&b[i]);v[b[i]]=true;}//建立映射关系
	for(int i=1;i<=n;i++) if(v[a[i]]) cout<<a[i]<<" ";//如果出现过直接输出
}
return 0;
   ```


不过言归正传，我还是冲着二分来写这道题的，这个二分思路不难想，就是将第二个数组排序（第一个数组与输出顺序有关，不能排序），然后挨个二分第一个数组里的数是否存在于第二个数组就好了，时间复杂度O(nlogn)，n<100000，那就不超时啦。


### 枚举＋二分

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[101000],b[101000];
bool binary_search(int x)
{
	int l=1,r=m;
    while (l<=r)
	{
        int mid=(l+r)>>1;
        if (b[mid]==a[x])return 1;
        if (b[mid-1]<a[x]&&b[mid+1]>a[x])return 0;
        if (b[mid]>a[x])r=mid;
        else l=mid+1;
    }
    return 0;   
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	sort(b+1,b+1+m);
	for(int i=1;i<=n;i++) if(binary_search(i)) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：引领天下 (赞：36)

看到楼下好多神奇的算法，觉得我这个简简单单的方法也挺好的。

我是什么算法？

说白了就是：

# 暴搜！

但是，纯暴搜是肯定要超时的，所以我们要加一个小小的优化：

规则是这样的：

设a为科技创新奖，b为特殊贡献奖。

如果a[i]>b[j],那么a[i+1]也必定大于b[j]（我用的是升序排序），之后同理。

所以，出现这种情况时，j可以毫不犹豫地向后加，一直加到b[j]不小于a[i]为止。

然后判断一不一样就可以了。

这就是一个很简单，却很实用的优化，可以AC。

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,b[100005];//b的含义已经解释过
struct Node{
    int s,id;//s为选手编号，id为出现位置
}a[100005];//a见上面
//由于最后的输出顺序很坑（被坑了2次20分QAQ），所以要保留原顺序，开结构体。
inline bool cmp1(Node a,Node b){return a.s<b.s;}//排序依据1：按编号升序排
inline bool cmp2(Node a,Node b){return a.id<b.id;}//排序依据2：按在a中出现位置升序排
int main(){
    scanf ("%d%d",&n,&m);
    for (int i=0;i<n;i++)scanf ("%d",&a[i].s),a[i].id=i;//读入，标记好位置
    for (int i=0;i<m;i++)scanf ("%d",&b[i]);
    sort (a,a+n,cmp1);//排序
    sort (b,b+m);
    int i=0,j=0;
    for (;i<n;i++){
        while (b[j]<a[i].s&&j<m)j++;//优化，找最小的不比a[i]小的b[i]
        if (b[j]!=a[i].s)a[i].s=0;//不一样就标记一下不是双奖
    }
    sort (a,a+n,cmp2);//排回去
    for (i=0;i<n;i++)if (a[i].s)printf ("%d ",a[i].s);//有值才输出
    return 0;
}
```
~~ PS：已经被莫名禁言3个多月了，那个路过的管理员能不能解一下啊QAQ ~~


---

## 作者：封禁用户 (赞：35)

#数据量如此之大，毅然决然地用了二分查找。

#这是我的程序：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,a[100005],b[100005],shu,s1,s2,gs,to;
int main()
{
   scanf("%d%d",&n,&k);//n个人获得科技创新奖，m个人获得特殊贡献奖
   for(int i=1;i<=n;i++)scanf("%d",&a[i]);//科技创新奖的人的编号
   for(int i=1;i<=k;i++)scanf("%d",&b[i]);//特殊贡献奖的人的编号
   sort(b+1,b+1+k);//用特殊贡献奖的人的编号排序
   for(int i=1;i<=n;i++)//用科技创新奖的人的编号去寻找特殊贡献奖的人的编号有无相同
   {
       int low=1,high=k;
        while(low<=high)//二分，看看有无相同
        {
            int mid=(low+high)/2;//中间值
            if(b[mid]==a[i])//有无相同？
            {
                cout<<a[i]<<" ";
                break;
```
}//有就输出，并打断
```cpp
            else if(b[mid]<a[i])low=mid+1;//在右区间找
            else high=mid-1;//在左区间找
        }
   }
   return 0;  
}
#最后，AC了！！！
```

---

## 作者：Starlight237 (赞：14)

P.S.本题解主要写给刚学二分的人，其实您用$\text{binary\_search()}$库函数可能会更方便。（[$\text{binary\_search()}$使用指南](http://www.cnblogs.com/aiguona/p/7281856.html)）

这是一道很好的二分入门题。所以这里顺便讲一下二分算法：

二分查找又称折半查找。对于一个有序数列$a_i,i=0,1,2,...,n$且$a_{i+1}>=a_i$，要在区间$[l,r]$中查找$key$。设其下标为$ans$。

那么我们取$a[l,r]$的中间数$a[(l+r)/2]$（下面写为$a[mid]$）。  
- 情况0：$l>r$此时区间显然是无效的，结束程序
- 情况1：$a[mid]=key$此时直接执行$ans=mid,r=-1$，这样就会使$l>r$，从而结束。
- 情况2：$a[mid]<key$此时显然key值所在的位置在mid右边的区间。所以可以进一步缩小区间到$[mid+1,r]$。
- 情况3：$a[mid]>key$类似的，可缩小区间到$[l,mid-1]$。

对于新区间，再次执行操作直到结束。$ans$初始化为-1，表示没找到。

不难理解，这样的算法是$O(\log n)$的。

对于这道题，我们定义两个数组：$a,b$分别表示两种奖项的获奖者。对于所有的$1<=i<=n$，在$b$中二分查找$a_i$。如果能找到，则$a_i$同时获得了两个奖项。当然，别忘了先排序$b_i$！

总时间复杂度：$O(m\log m+n\log m)=O(n\log m)$

一些题解的代码是400+ms，我加上了一些指针方法，将其优化至208ms。

最后代码奉上：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define reg register
static int n,m,a[100001],b[100001];
int main(){
	scanf("%d%d",&n,&m);
	reg int *q=a+n,*p=a;
	for(;p<q;++p)scanf("%d",p);
	q=b+m,p=b;
	for(;p<q;++p)scanf("%d",p);
	sort(b,p);
	for(reg int i=0;i<n;++i){
		int k=0,l=0,r=m-1,mid,x=a[i];
		while(l<=r)
			mid=l+r>>1,b[mid]<=x?(b[mid]==x?k=1,r=-1:l=mid+1):r=mid-1;//这里的三目可能会有些难以理解，但充其量就是两个嵌套if语句。
		if(k)printf("%d ",a[i]);
	}
	return 0;
}

```
顺便附上一些二分模板：

查找最后一个小于key的数和第一个大于key的数（q次询问）：
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
static int n,q,x,a[100000];
inline int bfindl(int l,int r,int key){
    int ans=-1,mid;
    while(l<=r){
        mid=l+r>>1;
        if(a[mid]<key)ans=mid,l=mid+1;
        else r=mid-1;
    }return ans;
}
inline int bfindm(int l,int r,int key){
    int ans=-1,mid;
    while(l<=r){
        mid=l+r>>1;
        if(a[mid]>key)ans=mid,r=mid-1;
        else l=mid+1;
    }return ans;
}
int main(){
    scanf("%d",&n);
    for(reg int i=0;i<n;++i)
        scanf("%d",a+i);
    scanf("%d",&q);
    while(q--)scanf("%d",&x),printf("%d %d\n",a[bfindl(0,n-1,x)],a[bfindm(0,n-1,x)]);
    return 0;
}
```
查找最后一个小于等于key的数及其位置（q次询问）：
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
static int n,q,x,a[100000];
inline int bfind(int l,int r,int key){
    int ans=-1,mid;
    while(l<=r){
        mid=l+r>>1;
        if(a[mid]<=key)ans=mid,l=mid+1;
        else r=mid-1;
    }return ans;
}
int main(){
    int k;
    scanf("%d",&n);
    for(reg int i=1;i<=n;++i)
        scanf("%d",a+i);
    scanf("%d",&q);
    while(q--)scanf("%d",&x),printf("%d %d\n",a[k=bfind(1,n,x)],k);
    return 0;
}
```

---

## 作者：雄鹰展翅 (赞：10)

//c++的题解好像有一点点少，顺便吐槽一下美杜莎（“他”？“她”？）。

看到题目的第一眼以为要排序,结果发现只要把b数组排序就行了。

首先发现数据量如此之大，毅然决然地用了二分。

然后发现：**输入数据中有0！！！**

于是加了一个if。

PS：穷举不是万能的（60分），但不用穷举是万万不能的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100001],b[100001];
void read()//习惯
{
    int i,l,r,mid,midt;
    cin>>n>>m;
    if(n==0||m==0){//输入优化
        return ;
        }
    for(i=1;i<=n;i++)
    cin>>a[i];
    for(i=1;i<=m;i++)
    cin>>b[i];
    sort(b+1,b+m+1);//只要排b数组
    for(i=1;i<=n;i++){
        l=1,r=m;//每一次都要重新赋值
            while(1){//我习惯用循环，像二楼那样用函数也行
            mid=(l+r)/2;
            if(b[mid]==a[i]){//判断是否满足条件：当前的b[mid]
                cout<<a[i]<<" ";
                break;//跳出当前循环
                }
                if(l>=r) break;//把条件改到里面就对了(也许)
                if(b[mid]<a[i])
                l=mid+1;//向左
                else r=mid-1;//向右
            }
        }
}
int main()
{
        read();
        return 0;
}
```

---

## 作者：Dfox (赞：10)

## P1571 【眼红的Medusa】


**#### 第二次写题解**


------------

### 题目描述
虽然Miss Medusa到了北京，领了科技创新奖，但是他还是觉得不满意。原因是，他发现很多人都和他一样获了科技创新奖，特别是其中的某些人，还获得了另一个奖项——特殊贡献奖。而越多的人获得了两个奖项，Miss Medusa就会越眼红。于是她决定统计有哪些人获得了两个奖项，来知道自己有多眼红。

### 输入格式
输入第一行，有两个数n,m，表示有n个人获得科技创新奖，m个人获得特殊贡献奖。

第二行，n个正整数，表示获得科技创新奖的人的编号

第三行，m个正整数，表示获得特殊贡献奖的人的编号

### 输出格式
输出一行，为获得两个奖项的人的编号，按在科技创新奖获奖名单中的先后次序输出。

### 输入输出样例
#### 输入 
4 3
2 15 6 8
8 9 2
#### 输出 
2 8
### 说明/提示
对于60%的数据，n<=1000，m<=1000
对于100%的数据，n<=100000，m<=100000，获得奖项的人的编号在2*10^9以内
输入数据保证第二行任意两个数不同，第三行任意两个数不同。



------------
其实吧这道题不是很难，先输入获奖选手的序号，然后排序，然后二分查找一下就好



------------



```cpp
#include <bits/stdc++.h>  //可爱的万能头文件
using namespace std;
int main(){
    int a[10001],b[10001],c,d;
    cin>>c>>d;
    for(int i=1;i<=c;i++){
        cin>>a[i];//获得科技创新奖的人的编号
    } 
    for(int i=1;i<=d;i++){
        cin>>b[i]; //获得特殊贡献奖的人的编号
    } 
    sort(b+1,b+d+1);  //二分查找前先排序呦！
    for(int i=1;i<=c;i++){  //核心代码
        if(binary_search(b+1,b+d+1,a[i])){  //二分查找的函数
            cout<<a[i]<<' ';
        } 
    }
    cout<<endl; 
    return 0;
}
```
~~想看更多题解记得要来我的博客欧~~

---

## 作者：Register (赞：9)

## STL千千万万，为什么就不用binary_search呢？
（map好像的确好一些。。。）

简单介绍一下binary_search吧：
	
    binary_search有4个参数
    1.查找的数组下标开始（是地址）
    2.查找的数组下标结束（是地址）
    3.要查找的对象（要和数组一个类型）
    4.comp；即自定义的比较方式。初始都是默认升序，同sort，不知道怎么写的自行在网上借鉴sort的写法，我在这里不过多阐述
    如果查找到了，返回bool值true，没找到返回bool值false
    二分查找无论何时都要用顺序，STL也一样，顺序方式就在comp里写！！！
code：
```cpp
#include <iostream>
#include <algorithm>//binary_search、sort
using namespace std;
int a[100001],b[100001],n,m;
int main(){
    cin>>n>>m;
    for(register int i=1;i<=n;i++) cin>>a[i];
    for(register int i=1;i<=m;i++) cin>>b[i];
    sort(b+1,b+m+1);//升序排列
    for(register int i=1;i<=n;i++)
        if(binary_search(b+1,b+m+1,a[i])) cout<<a[i]<<' ';//查找、输出
    cout<<endl;	
    return 0;
}
```

---

## 作者：Perseis (赞：7)

嗯，，看了一下题解里都是用的二分啊，map啊，set啊什么的，，

那么就来一发也算好理解的
，，对没错就是结构体排序

将两个奖项读入统一数组进行排序，若相邻位置的编号相同，啧该编号一定同时获得了两个奖项，再对该奖在科技创新奖中的位置进行标记，再输出对应位置的编号就可以了

详情可看代码与注释

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#define N 2000007

using namespace std;
int n,m;
struct node
{
    int v;//编号
    int loc;//获“科技创新奖”的位置
}a[N];
bool cmp(node s,node t)
{
    return s.v<t.v;//编号从小到大排序
}
int f[N],b[N],ans;
int main()
{
    cin>>n>>m;
    for(register int i=1;i<=n;i++)
        {
            cin>>a[i].v;
            b[i]=a[i].v;//b数组存下“科技创新奖”
            a[i].loc=i;
        }
    for(register int i=1;i<=m;i++)
    {
        cin>>a[n+i].v;
        a[n+i].loc=-1;
    }//将两个奖读入同一数组
    sort(a+1,a+1+n+m,cmp);
    for(register int i=2;i<=n+m;i++)
    {
        if(a[i].v==a[i-1].v)
          {
              if(a[i].loc!=-1)f[a[i].loc]=1;
              else f[a[i-1].loc]=1;
          }
          /*
            若相邻两位置的编号相同，则该编号一定同时获得两个奖项
            若a[i].loc为-1，则a[i]位置指“特殊贡献奖”，则a[i-1]必为“创新科技奖”
            反之，若a[i].loc不为-1，则a[i]位置为“科技创新奖”
            用f数组将重复编号位置进行标记
          */
    }
    for(register int i=1;i<=n;i++)if(f[i])cout<<b[i]<<' ';//将科技创新奖中被标记了的位置的编号输出
    return 0;
}

```

---

## 作者：易燃易爆炸丶 (赞：7)

首先我们看数据范围 发现都是1\*10^5级别 那么我们首先要想的就是二分了

然后呢 C++的STL库中有一个函数为lower\_bound 形参为lower\_bound(a，a+n,x) 其中a为数组 x为你要查找的数 它会返回a数组中>=x的第一个数的下标

实际使用：int y=lower\_bound(a+1,a+n+1,x)-a;//注意一定要-a

然后我们又发现 题目要求根据第一个数组输出 那么第一个数组的顺序肯定是不能变的

因此我们将第二个数组sort一下 然后枚举第一个数组中的数 查找一下第二个数组中有没有 这个题的整体思路就出来了

AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
int  m,n,x,y;
int  a[100010],b[100010];
using namespace std;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
    scanf("%d",&b[i]);
    sort(b+1,b+m+1);
    for(int i=1;i<=n;i++)
    {
        y=lower_bound(b+1,b+m+1,a[i])-b;
        if(b[y]==a[i])
        cout<<a[i]<<" ";
    }
    return 0;
}
```

---

## 作者：唔啊唔 (赞：5)

初看此题，以为是用桶排，看到2*10^9后，就知道会爆。

所以我就想了另外一种跟归并排序思想相似的方法，也就建立在分治法的基础上。

请看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int bh,cx;
}a[100010],ans[100010];
int b[100010],cnt;
int v(Node x,Node y){
	return x.bh<y.bh;
}
int f(Node x,Node y){
	return x.cx<y.cx;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].bh;
		a[i].cx=i;
	}
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(a+1,a+1+n,v);
	sort(b+1,b+1+m);
	int x=1,y=1;
	while(x<=n&&y<=m){	//这就是代码的核心部分 
		if(a[x].bh==b[y]){//通过x,y的累加来得到相同的数 
			cnt++;	
			ans[cnt].bh=a[x].bh;
			ans[cnt].cx=a[x].cx;
			x++;
			y++;
		}
		else if(a[x].bh>b[y])y++;
		else x++;
	}
	sort(ans+1,ans+1+cnt,f);
	for(int i=1;i<=cnt;i++)cout<<ans[i].bh<<" ";
	return 0;
}
```


---

## 作者：fighter_OI (赞：3)

为什么没有人用set呢……stl大法好

先把第一组存下，查第一组的元素有没有在第二组出现，就使输出为第一组顺序

```cpp
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
int n,m,ans=0,k,a[100010];
set<int> SET;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);//读入第一组数据
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&k);
        SET.insert(k);//将第二组数据加入集合
    }
    for(int i=1;i<=n;i++)
    {
        if(SET.count(a[i]))printf("%d ",a[i]);//若第一组数据在第二组中出现了就输出
    }
    return 0;
}
```

---

## 作者：TRZ_2007 (赞：2)

### 首先看到这道题，第一个反应就是用桶排序来解决，然而认真一想还是觉得$map$好写一点，毕竟$STL$就是好用。
### $map$操作指南：
- 1：首先需要$STL$头文件$map$如下：
```
#include <map>//map头文件
using namespace std;//STL必不可少
```
- 2：定义好头文件之后，就可以开始应用了，比如说
```
map<int,int>
```
$map$标准用法就是$map(a,b)$,$a$和$b$都是变量类型也就是说上面的类型是一个$int$的形参，就像数组中的$a[int]$，中括号中的类型是$map$括号中的前一个，数组的类型是$map$括号中的后一个。
- 3：接下来就把它当成数组来用啦！注意$map$有无穷大个变量哦！

$20$分代码，$9780ms$，$65768KB$，$TLE$。
```
#include <stdio.h>
#include <map>
using namespace std;
map<int,int>book;
int main()
{
    int n,m,i,max=0,a;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a);
        book[a]++;
        max=max<a?a:max;
    }
    for(i=1;i<=m;i++)
    {
        scanf("%d",&a);
        book[a]++;
        max=max<a?a:max;
    }
    for(i=1;i<=max;i++)
        if(book[i]==2)
            printf("%d ",i);
}
```
### 原因在于：变量$max$的值最大是在$2*10^9$之内，这样子$O(max)$的算法会超时。

### 解决办法：利用数组，将时间降低为$O(n)$
$100$分代码，$882ms$，$10184KB$
```
#include <stdio.h>
#include <map>
using namespace std;
#define N 100001
int a[N],b[N];
map<int,int>book;
int main()
{
    int n,m,i,max=0;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        book[a[i]]++;
    }
    for(i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
        book[b[i]]++;
    }
    for(i=1;i<=n;i++)
        if(book[a[i]]==2)
            printf("%d ",a[i]);
}
```
时间复杂度和空间复杂度都是$O(n)$

---

## 作者：shenyi1343395317 (赞：2)

提供一种新解法，既然要查询的话，用hash最快

hash（哈希）基本套路就是通过取模来查找，唯一不足就是会产生地址冲突，解决方法是挂链法

取模的hash一般来说是用大素数的，这里为了方便用了2的17次方+位运算

以下是代码，用hash切记要开好数组的大小

```cpp
program sss;
  type hash=record
       num:0..1;
       last:array[0..100] of longint;
       count:longint;
       end;
  var a:array[0..131072] of hash;
      c:array[0..100000] of longint;
      i,j,m,n,k,x:longint;
  begin
  read(n,m);
  readln;
  for i:=1 to n do read(c[i]);
  readln;
  for i:=1 to m do               //读入数并取模保存
   begin
   read(k);
   x:=k mod 131072;
   a[x].num:=1;                    //标记
   inc(a[x].count);              //标记长度
   a[x].last[a[x].count]:=k shr 17;  //挂链下去
   end;
   for i:=1 to n do
    begin                        //取模查询
    x:=c[i] mod 131072;
    m:=c[i] shr 17;
    if a[x].num=1 then
     for j:=1 to a[x].count do
      if a[x].last[j]=m then
       begin
       write(c[i],' ');
       break;
       end;
    end;
end.
```

---

## 作者：AFOier (赞：2)

这题如果用暴力找的话只有60分，不要试图用暴力过哦~

这题主要的解法是二分查找，将数组b从小到大排序后从中间数开始找

如果a[i]>中间数，就找中间数的下一个数到最后一个数

反之，如果a[i]<中间数，就找第一个数到中间数的前一个数

这样会比从头找到尾快很多

[codec]

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[1000001],b[1000001]; 
int pd(int s,int l,int r)
{
    int mid=b[(l+r)/2]; //中间数字 
    int mid1=(l+r)/2; //中间位置 
    if(mid==s)return 1; //如果找到，返回1 
    if(l>=r)return 0; //条件出错，返回0 
    else if(mid<s){pd(s,mid1+1,r);} //如果中间数字比要找的小，就找中间+1到最后一个 
    else if(mid>s){pd(s,l,mid1-1);} //与上行相反 
}
int main()
{
    long long int n,m;
    cin>>n>>m;
    if(n==0||m==0)return 0; //如果有一个为0，直接返回 
    for(int i=1;i<=n;i++)
    cin>>a[i];
    for(int i=1;i<=m;i++)
    cin>>b[i];
    sort(b+1,b+m+1); //排序 
    for(int i=1;i<=n;i++)
    {
        if(pd(a[i],1,m)==1){cout<<a[i]<<" ";} //如果找到，输出 
    }
}
[/codec]
```

---

## 作者：香风智乃 (赞：2)

和 BackCloud dalao一样，看到这题我第一反应居然是用map

然而我真的用了map（好吧这里最好用二分）

（不过STL是真的方便）

```cpp
#include<bits/stdc++.h>
using namespace std;
map <int,int> q; 
int a[100002];
int main()
{
    int n,m,i,p;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=m;i++)
    {
        scanf("%d",&p);
        q[p]++;
    }
    for(i=1;i<=n;i++)
        if(q[a[i]])
            printf("%d ",a[i]);
    return 0;
}
```

---

## 作者：rainygame (赞：1)

本题还有一种神奇的做法。

先考虑暴力做法，也就是对于每个 $a_i$，枚举每一个 $b_i$，然后判断是否相等。时间复杂度是 $O(n^2)$ 的。

我们可以发现，如果 $a$ 和 $b$ 均有序，那么就不需要每次都从开头枚举，只需要维护一个决策点 $j$ 即可。具体地，对于 $b_j < a_i$，都 $j +1 \rightarrow j$，如果最后得到 $j$ 使得 $b_j = a_i$，就找到了一组匹配的，否则 $a_i$ 无法匹配。然后进入下一个 $a_i$。正确性显然。

所以我们可以考虑先排序，然后再按上述方法求解，时间复杂度 $O((n+m) \log (n+m))$。~~明显劣于其它的很多题解。~~

但是我们还需要按名单上的顺序对答案进行排序，所以我们把顺序和具体的值封装到一个结构体里再排序。我们已知了位置还需要求具体值，所以我们还需要一个数组的值未排序的 $a$ 数组，然后在用里面的数求出具体的值。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

int n, m, j;
int b[MAXN], tmp[MAXN];
vector<int> vec;

struct Node{
	int id, val;
}a[MAXN];

bool cmp(Node a, Node b){
	return a.val < b.val;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for (int i(1); i<=n; ++i){
		cin >> a[i].val;
		a[i].id = i;
		tmp[i] = a[i].val;
	}
	for (int i(1); i<=m; ++i) cin >> b[i];
	sort(a+1, a+n+1, cmp);
	sort(b+1, b+m+1);
	
	for (int i(1); i<=n; ++i){
		while (b[j] < a[i].val && j <= m) ++j;
		if (j > m) break;
		if (b[j] == a[i].val) vec.push_back(a[i].id);
	}
	
	sort(vec.begin(), vec.end());
	for (auto i: vec) cout << tmp[i] << ' ';
	
	return 0;
}

```


---

## 作者：rainygame (赞：1)

本题大部分都是 $O(m \log m+n)$ 的，这里给出一个期望 $O(n\times\frac{n}{mod})$ 的解法，其中我设 $mod = 10^5+7$。

好吧，这就是哈希做法。

哈希其实就是一种更省空间的映射，因为本题的编号 $\le 2\times10^9$，所以我们无法直接映射 $x$，只能映射 $x \bmod mod$ 的值，而哈希就是通过取模来用更小的空间实现接近 $O(1)$ 的查询。

但是可能会出现冲突，也就是两个数取模这个数相同的情况。这个时候我们就可以使用拉链法，也就是在每个取模后的值那里拉一个链表，插入对于相同的就在链表后直接插入，查询时就枚举这个链表的每一个元素。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001
#define MOD 100007

int n, m, x;
int a[MAXN];

struct Hash{
	list<int> li[MOD];
	void insert(int x){
		li[x % MOD].push_back(x);
	}
	
	bool find(int x){
		for (auto i: li[x % MOD]){
			if (i == x) return true;
		}
		return false;
	}
}ha;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for (int i(1); i<=n; ++i) cin >> a[i];
	while (m--){
		cin >> x;
		ha.insert(x);
	}
	
	for (int i(1); i<=n; ++i){
		if (ha.find(a[i])) cout << a[i] << ' ';
	}
	
	return 0;
}

```


---

## 作者：Phykyer (赞：1)

好像题解julao里没有用平衡树做这道题的(~~大概是julao不会像我一样这么闲~~)  
简单讲一下用平衡树解这道题的思路：就是把获得贡献奖的人插入到树中，然后跑一边科技奖的人在树中找是否存在该值即可，其实会写平衡树的人一看就明白。(不会平衡树的童鞋可以转到P3369学习一下,当然洛谷日报中也有平衡树的内容)  
然后上代码就完事了
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
using namespace std;

int n,m,a[100010];
int x,root=0,size=0;

struct Splay
{
	int son[2],value,same_cnt,size,fa;//左右儿子,值,重复数,大小,父节点  
}t[100010];//只用开到100000因为只要把贡献奖的人插入进来即可 

bool relate(int x)//判断x是他父亲的左儿子还是右儿子 
{
	return t[t[x].fa].son[1]==x;//等式成立为真即为右儿子否则为左儿子 
}

void connect(int x,int fa,bool which)//建立父子关系不解释 
{
	t[x].fa=fa;
	if(fa) t[fa].son[which]=x;
}

void update(int x)//更新节点大小 
{
	t[x].size=t[t[x].son[0]].size+t[t[x].son[1]].size+t[x].same_cnt;
}

void rotate(int x)//旋转 
{
	int y=t[x].fa;
	bool z=relate(x);
	connect(x,t[y].fa,relate(y));
    connect(t[x].son[z^1],y,z);
    connect(y,x,z^1);
	update(y); update(x);
}

void splay(int x,int goal)//双旋和单旋判定 
{
	for(int fa;(fa=t[x].fa)!=goal;rotate(x))
	{
		if(t[fa].fa!=goal)
		{
			rotate(relate(x)==relate(fa)?fa:x);
		}
	}
	if(!goal) root=x;
}

void insert(int x)//插入 
{
	if(!root)
	{
		t[root=++size].same_cnt=1;
		t[root].size=1;
		t[root].value=x;
		return;
	}
	int now=root;
	while(1)
	{
		if(x==t[now].value)
		{
			update(now);
			update(t[now].fa);
			splay(now,0);
			return;
		}
		int ff=now;
		bool which=t[ff].value<x;
		now=t[ff].son[which];
		if(!now)
		{
			t[now=++size].same_cnt=1;
			t[now].size=1;
			t[now].value=x;
			connect(now,ff,which);
			update(ff);
			splay(now,0);
			return;
		}
	}
}

int find(int x)//这里find需要返回值，也是解题精髓所在 
{
	if(!root) return -1;
//找到节点并把它旋转至根 
	int now=root;
	while(t[now].son[x>t[now].value]&&x!=t[now].value)
	{
		now=t[now].son[x>t[now].value];
	}
	splay(now,0);
}

int main()
{
	insert(INT_MIN);insert(INT_MAX);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	//因为题目要求按科技奖顺序输出，所以要先插入贡献奖的人再用科技奖比对 
	for(int i=1;i<=m;i++)
	{
		cin>>x;
		insert(x);
	}
	for(int i=1;i<=n;i++)
	{
		if(find(a[i])==-1) continue;
		else if(t[root].value==a[i]) printf("%d ",a[i]);//找到就输出 
	}
	return 0;
}
```


---

## 作者：Ar_HomeTree (赞：1)

### 第三次题解，谢谢；
本题就是二分找数；
读入排序后一个个送入比较，
复杂度就是
$n log n$
``` cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],b[1000010];
int n,m;
int f(int p)
{
    int left=0,right=m,mid;
    while(left<=right)
    {
        mid=(left+right)/2;
        if(p==b[mid]) return 1;
        if(b[mid-1]<p && b[mid+1]>p)return 0;
        if(p>b[mid])left=mid+1;
        else right=mid;
    }
    return 0;
}
int main()
{
    //freopen("c.in","r",stdin);
    //freopen("c.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    for(int i=0;i<m;i++) scanf("%d",&b[i]);
    sort(b,b+m);
    for(int i=0;i<n;i++)
        if(f(a[i]))
            printf("%d ",a[i]);
    return 0; 
} 
```

---

## 作者：Dr_殇 (赞：1)

#一道裸的二分查找，cpp有两种做法，可以用algorithm库里的函数做，也可以自己写二分查找，这里为了让大家理解，就用了二分查找

#题目解析

这道题一看到，就知道是搜索，不过n和m小于等于100000，所以爆搜肯定超时。用二分就是一个很好的方法。

对于输入输出样例

4 3
2 15 6 8

8 9 2
因为二分查找需要有序性，所以我们先将得到特殊贡献奖的排序一遍（注：科学创新奖不要排序，否则会错），得

2 8 9
然后模拟每一个科学创新奖的人是否得到特殊贡献奖就行了。

##代码如下：





```cpp
//--新阶梯工作室防伪水印-- 
//--By新阶梯工作室 闪现--
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
#define in freopen (".in","r",stdin)
#define out freopen (".out","w",stdout)
#define INF 2147483647
#define UNINF -2147483648ll
#define ch char
#define bo bool
#define ui unsigned int
#define ll long long//闪现为了少打几个字符，弄了好多好多宏定义
using namespace std;
int n,m,a[100005],b[100005];//数组千万不要开错，考试就完蛋了
inline bo midfind(int x);
inline void work();
int main(){
    //in;out;
    work();
    return 0;
}
inline bo midfind(int x){//二分查找函数
    int l=1,r=m;
    while (l<=r){
        int mid=(l+r)/2;
        if (b[mid]==a[x])return 1;//如果这个得到科学创新奖的人又得到了特殊贡献奖，那么就返回1
        if (b[mid-1]<a[x]&&b[mid+1]>a[x])return 0;//否则没得到，就返回0
        if (b[mid]>a[x])r=mid;
        else l=mid+1;
    }
    return 0;
}
inline void work(){
    scanf ("%d %d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf ("%d",&a[i]);
    }
    for (int i=1;i<=m;i++){
        scanf ("%d",&b[i]);
    }
    sort (b+1,b+1+m);//排序，注：不要把a也排序了
    for (int i=1;i<=n;i++){
        if (midfind(i))printf ("%d ",a[i]);//然后如果又得到科学创新奖，又得到特殊贡献奖的人就输出
    }
}
```

---

## 作者：Yoshinow2001 (赞：1)

（前言——看到这题我第一反应居然是用map（雾x

（如果有什么问题or错误也随时欢迎私信指出来啦xd

（嗯蓝后下面用a[1..n]表示第二行输入的数组，b[1..m]表示第三行输入的数组

然后说说我的大概思路：因为要求按照在a[1..n]中的次序输出于是我们就先对b[1..m]排序，然后对每个a[i]在b[1..m]中查找

空间复杂度O(n+m)时间复杂度O（nlog\_2 mn)

贴代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,m,l,r,mid,a[maxn],b[maxn];
inline int read()
{
    int s=0;char c;while((c=getchar())<'0'||c>'9');
    do{s=s*10+c-'0';}while((c=getchar())>='0'&&c<='9');return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)b[i]=read();
    sort(b,b+m+1);
    for(int i=1;i<=n;i++)
    {
        l=1;r=m;
        while(l<r)
        {
            mid=(l+r)>>1;
            if(b[mid]<a[i])l=mid+1;
            else r=mid;
        }if(a[i]==b[l])printf("%d ",a[i]);
    }
    return 0;
}
```
/\*后面没事写了个读入优化好像没有快多少orz
以及有个点居然只有一个数据0…\*/


---

## 作者：Ape_epA (赞：1)

非常简单，只要排第二个数组就可以了，因为第一个不排就是按顺序的。然后用一个循环i从1到n，一个一个二分查找，有就输出。就OK，愉快地AC了

```cpp
var a,b:array[0..100001] of longint;
    n,m,i:longint;
function sc(x:longint):boolean;     //二分查找
var t,w,mid:longint;
begin
  t:=1;
  w:=m;
  while t<=w do
    begin
    mid:=(t+w) div 2;
    if b[mid]=x then
      exit(true)
    else if b[mid]<x then
      t:=mid+1
    else w:=mid-1;
    end;
  exit(false);
end;
procedure sort(l,r: longint);
var i,j,x,y: longint;
begin
  i:=l; j:=r;
  x:=b[(l+r) div 2];
  repeat
    while b[i]<x do
      inc(i);
    while x<b[j] do
      dec(j);
    if not(i>j) then
      begin
      y:=b[i];
      b[i]:=b[j];
      b[j]:=y;
      inc(i);
      j:=j-1;
      end;
  until i>j;
  if l<j then
    sort(l,j);
  if i<r then
    sort(i,r);    //快排
end;
begin
  readln(n,m);     
  for i:=1 to n do
    read(a[i]);
  readln;
  for i:=1 to m do
    read(b[i]);      //读入
  sort(1,m);     //排第二个数组
  for i:=1 to n do
    if sc(a[i]) then
      write(a[i],' ');     //按我刚刚说的一个一个找过来，有就输出。
  writeln;
end.
```

---

## 作者：lych (赞：1)

看到题目之后，首先分别对两组数据进行排序，得到有序的两组数据。

接下来，首先对指向两个数组的指针都赋为1。

现在是重点中的重点，设i为指向第一组数据的指针，j为第二组，那么，若a[i]=b[j]，则这就是一个获得两个奖项的人，将他的编号和输入时的序号（注意，两者不同！！），保存在另外的数组当中。更重要的是，若a[i]<b[j]，那么我们需要将i+1，为什么呢？因为若有a[k]=b[j],则k一定大于i，因为b[j]>a[i]，且a数组是有序单调递增的！若有a[x]=b[y]，那么a[x],b[y]一定大于a[i]！因为，i，j是只增不减的，那么b[y]一定大于b[j]，那么也一定大于a[i]！a[i]<b[j]是如此，反之亦然。

接下来给出标程，希望在标称中自己体会。

```delphi
type
  arr=array[0..100000] of longint;
var
  x,y,z,x1,y1,z1:arr;
  i,j,k,m,n:longint;
procedure qsort(r,l:longint; var a,b:arr);//a为关键字，在交换a的时候，也同时交换b
var
  i,j,t,mid:longint;
begin
  i:=r; j:=l;
  mid:=a[random(j-i+1)+i];
  repeat
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
      begin
        t:=a[i]; a[i]:=a[j]; a[j]:=t;
        t:=b[i]; b[i]:=b[j]; b[j]:=t;
        inc(i); dec(j);
      end;
  until i>j;
  if i<l then qsort(i,l,a,b);
  if r<j then qsort(r,j,a,b);
end;
begin
  randomize;//随机化快排
  read(m,n);
  for i:=1 to m do begin read(x[i]); x1[i]:=i; end;
  for i:=1 to n do begin read(y[i]); y1[i]:=i; end;//读入两组数据，将读入时的序号保存下来
  qsort(1,m,x,x1);
  qsort(1,n,y,y1);//排序
  i:=1;
  j:=1;
  while (i<=m) and (j<=n) do//还有元素
    begin
      if x[i]=y[j] then begin inc(k); z[k]:=x[i]; z1[k]:=x1[i];
                        inc(i); inc(j); end else//相等，记入另外的数组
        if x[i]<y[j] then inc(i)//x[i]较小，i+1
                     else inc(j);
    end;
  qsort(1,k,z1,z);//根据编号将新的数组排序，注意是z1在z之前，因为z1是关键字
  for i:=1 to k do write(z[i],' ');
end.[codep/]


---

## 作者：5ab_juruo (赞：1)

# STL大法吼啊！

---

本蒟蒻发现了一个很好玩的函数（在<$algorithm$>库里，~~万能头文件请无视~~）：

set_intersection();

# 这是干什么的？

答案：求两个（有序）区间的交集。

那么，答案就很明了了。。。吗？

并不是！It Says：按照输入顺序输出。

So。。。再加上一重排序，就好啦！

~~（抱歉，我真的太弱了，只会这么暴力的方法，望巨佬见谅QAQ）~~

```cpp
struct num
{
	int ord, val;
};
num a[100000] = {}, b[100000] = {}, c[100001];

bool cmp1(const num &n1, const num &n2)
{
	return n1.val < n2.val;
}

bool cmp2(const num &n1, const num &n2)
{
	return n1.ord < n2.ord;
}

int main()
{
	int a_c, b_c;
	memset(c, -1, sizeof(c));
	
	cin >> a_c >> b_c;
	if (a_c == 0 || b_c == 0)
		return 0;
	
	for (int i = 0; i < a_c; i++)
	{
		cin >> a[i].val;
		a[i].ord = i;
	}
	for (int i = 0; i < b_c; i++)
	{
		cin >> b[i].val;
		b[i].ord = i;
	}
	
	sort(a, a + a_c, cmp1);
	sort(b, b + b_c, cmp1);
	set_intersection(a, a + a_c, b, b + b_c, c, cmp1);
	
	int i = 0;
	while (c[i].val != -1)
		i++;
	
	sort(c, c + i, cmp2);
	
	for (int ss = 0; ss < i; ss++)
		cout << c[ss].val << " ";
	
	return 0;
}
```

> 日常安利[Blog](https://5ab-juruo.blog.luogu.org/#)。

---

