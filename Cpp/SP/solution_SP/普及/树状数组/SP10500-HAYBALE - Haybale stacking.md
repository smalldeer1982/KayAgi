# HAYBALE - Haybale stacking

## 题目描述

Feeling sorry for all the mischief she has caused around the farm recently,

# 题解

## 作者：封禁用户 (赞：4)

### 前言

想了好久树状数组啥的，后来想想写打个差分再说，结果写完一遍AC了……

[强烈安利](https://www.luogu.com.cn/blog/CM0/chafen-qianzhuihe)

[更好的阅读体验](https://www.cnblogs.com/CM-0728/p/13534774.html)

### 题意

一个由 $n$ 个元素组成的序列，给出 $k$ 个操作，每次将 $a\sim b$ 加上 $1$ ，求这个序列的中位数。

### $\sf Solution$

~~想用树状数组的直接可以停了。~~

差分。

差分是什么，前面的blog已经讲得很清楚了。

对于每次操作，区间修改 $a\sim b$ 。

修改后，查询区间值，再将数组排序，最终答案就是 $a_{n/2+1}$ 。


### $\sf Code$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,x,y,w[1000005],a[1000005];
int main()
{
	scanf("%d%d",&n,&k);
	while(k--)
	{
		scanf("%d%d",&x,&y);
		w[x]++;
		w[y+1]--;//区间加
	}
	for(int i=1;i<=n;++i)
		a[i]=a[i-1]+w[i];//查询
	sort(a+1,a+n+1);//排序
	printf("%d",a[n/2+1]);//输出
	return 0;
}
```

---

## 作者：云浅知处 (赞：4)

此题大概就是维护一个序列，支持两个操作：

1. 区间加
2. 区间取中位数（在此题中已经确定取的是所有数的中位数）

显然此题要求在线，所以莫队萎了。~~所以为什么要用莫队呢？~~

咳咳，不说那么多，进入正题。

------------

1.区间加操作

当然可以打个暴力。

```cpp
int l,r;
scanf("%d%d",&l,&r);	//表示将区间 [l,r] 内的所有数加上1。
for(int i=l;i<=r;i++){
	a[i]++;				//a[] 是原数组
}
```

不过单次修改复杂度已经达到了恐怖的 $O(n)$ ，$k$ 次修改就成了 $O(nk)$ 。

再看看 $1\le n \le 1000000\ ,\ 1\le k \le 25000$ 的数据范围，复杂度立马爆炸。

好吧，考虑优化。

各位大佬可以写一个线段树/树状数组/分块 等~~搞♂基~~高级数据结构，不过此题最简单的做法，还是**差分**。

~~此时才算真正进入正题~~

------------

差分基本思想：对于原数组 $A$ ，我们定义一个新数组 $d$ 表示数组 $A$ 的差分数组，且有 $d[i]=A[i]-A[i-1]$ 。

那么，如果我们将 $d[i]$ 加上 $k$ ，根据差分数组的定义，我们有 $d[i]+A[i-1]=A[i]$ 。

而此时 $d[i]$ 加上了 $k$ ，所以，相应地，$A[i]$ 也加上了 $k$ 。

同样是根据差分数组的定义，$A[i+1]=A[i]+d[i+1]$，而此时 $A[i]$ 加上了 $k$ ，所以，相应地，$A[i+1]$ 也加上了 $k$ 。

依此类推，只要将 $d[i]$ 加上 $k$ ，我们就能将 $A[i],A[i+1],A[i+2],\dots\dots,A[n-1],A[n]$ 全部加上 $k$ 。（此处 $n$ 指数组大小）

不过，题目中要求的是将区间 $[l,r]$ 加上一个值诶，这一下子往后多加了很多个数，怎么办呢![/yiw](https://cdn.luogu.com.cn/upload/pic/62243.png)![/yiw](https://cdn.luogu.com.cn/upload/pic/62243.png)![/yiw](https://cdn.luogu.com.cn/upload/pic/62243.png)？

其实，只要把 $d[r+1]$ 减去 $k$ ，那么区间 $[l,n]$ 全部加上了 $k$ ，区间 $[r+1,n]$ 全部减去了 $k$ ，

其中，区间 $[r+1,n]$ 先加上了 $k$ ，又减去了 $k$ ，刚好抵消，因此不会变。

所以，用这种方法，我们就能做到 $O(1)$ 修改啦\\(^o^)/！

当然，最后查询的时候，还是要 $O(n)$ 恢复一下原数组。

代码实现：

```cpp
scanf("%d%d",&n,&p);        //n 是数组大小，p 是操作次数
while(p--){
    int l,r;
    scanf("%d%d",&l,&r);
    d[l]++,d[r+1]--;        //刚才说过的差分
}
for(int i=1;i<=n;i++){
    a[i]=a[i-1]+d[i];       //还原数组
}
```

------------

2.查询所有数的中位数

当然可以一个`sort`排序之后，输出最中间的那个数。

不过这么做复杂度是 $O(n \log n)$ ，虽然可以过(?)，但是爱学习的我们怎么会止步于此呢？当然要继续优化啦！

一种方法是用桶排，期望复杂度 $\Theta(n)$ ，不过这里不展开说明。

其实，此题就是要求在一个数组里面查询第1 $(n\div2+1)$ 大的数啦。

而线性找第 $k$ 大的数是完全可以做到的。

我们使用类似快速排序的「分治」思想，在使用快速排序「划分」后，把数组 $A_l\dots A_r$ 划分成 $A_l\dots A_{mid}$ 与 $A_{mid+1}\dots A_r$。

此时比较左边元素数量（即 $mid-l+1$）与 $k$ 的大小关系，然后判断在左边还是右边递归求解。

代码实现：

```cpp
int ans,k;
void find_kth(int a[],int l,int r){
    if(l==r){				//如果找到了，记录答案
        ans=a[l];
        return;
    }
    int i=l,j=r,f=a[(l+r)/2];
    do{
        while(a[i]<f){		//从左边找比哨兵大的值
            i++;
        }
        while(a[j]>f){		//从右边找比哨兵大的值
            j--;
        }
        if(i<=j){			//如果 i<=j
            swap(i,j);		//就交换
            i++,j--;
        }
    }while(i<=j);
    if(k<=j){				//在左区间
        find_kth(a,l,j);
    }
    else if(i<=k){			//在右区间
        find_kth(a,i,r);
    }
    else{					//既不在左区间，也不在右区间
        find_kth(a,j+1,i-1);
    }
}
```

当然，`STL` 中有一个好用的 `nth_element` ，其参数为：`nth_element(数组名,数组名+第k小元素,数组名+元素个数)`。

作用就是把数组中的第 `k` 个元素换成这个数组中第 `k` 小的元素。期望复杂度 $O(n)$ 。

```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 1000005
using namespace std;
int a[MAXN],d[MAXN];
int n,p;
int main(){
    scanf("%d%d",&n,&p);                //n 是数组大小，p 是操作次数
    while(p--){
        int l,r;
        scanf("%d%d",&l,&r);
        d[l]++,d[r+1]--;                //刚才说过的差分
    }
    for(int i=1;i<=n;i++){
        a[i]=a[i-1]+d[i];               //还原数组
    }
    nth_element(a+1,a+n/2+1,a+n+1);     //STL 大法好！
    printf("%d\n",a[n/2+1]);
    return 0;
}
```

[顺利AC！](https://www.luogu.com.cn/record/34401015)

~~话说为什么 SP 的题在洛谷上都只显示一个测试点呢？~~

---

## 作者：Xposed (赞：3)


	
##   	   运用差分思想
在数学中，差分法（difference methods，简称DM），是一种微分方程数值方法，是通过有限差分来近似导数，从而寻求微分方程的近似解。

“差分法”是在比较两个分数大小时，用“直除法”或者“化同法”等其他速算方式难以解决时可以采取的一种速算方式。
差分法是微分方程的一种近似数值解法。具体地讲，差分法就是把微分用有限差分代替，把导数用有限差商代替，从而把基本方程和边界条件（一般均为微分方程）近似地改用差分方程（代数方程）来表示，把求解微分方程的问题改换成为求解代数方程的问题。
### 开始题解
	往为 [a, b] 干草堆中各
  	添加一包干草，相当于把 [a,n] 都添加一包干草，然后减去
    [b + 1, n] 多添加的干草。于是只需要在
    数组的第 rap 项 +1 ，第 b + 1 项 -1 ，求前缀和
###      再排序，最后输出中位数就可以了。（已知 N 一定是奇数）
  #### 没有输入输出样例....所以自信的交码就好了
  ## ~~WA声一片~~

------------
# ~~本蒟蒻的AC码~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxx 1000002
int rap[maxx], s[maxx];
long long n, k, a, b;

int main() 
{	
	cin>>n>>k;
	for (int  i = 0; i < k; ++i) {
		cin>>a>>b;
		++rap[a], --rap[b + 1];
	}
	
	for (int  i = 1; i <= n; ++i) 
		 s[i] = s[i - 1] + rap[i]; 
	
	sort(s + 1, s + 1 + n);
	cout<<s[n / 2 + 1];
	return 0;
}

```


---

## 作者：monstersqwq (赞：2)

一看到这道题，就高高兴兴地去交了个暴力模拟添加干草。

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
int a[1000005],n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		int l,r;
		cin>>l>>r;
		for(int j=l;j<=r;j++)
			a[j]++;
	}
	sort(a+1,a+n+1);
	cout<<a[(n+1)/2]<<endl;
    return 0;
}
```
然后就得到了一个方方正正的 TLE [戳我](https://www.luogu.com.cn/record/31683152)。

显然，这个暴力的算法时间复杂度高达 $\Theta(nk+n \log n)$，在 $n\le10^6,k\le 2.5\times10^4$ 的情况下会大大超时。

但我们观察到，题目中每次操作对区间内的数字都进行了同样的操作，区间中的第一项比前面的数字添加的多1，最后一项比后面的数字添加的多1，区间内部添加的是相同的。

于是，我们观察到，在进行一次操作后，整个数组中只有两处的差值发生了变化，这样就使得原本需要 $\Theta(r-l)$ 的一次操作变成了仅仅需要修改两次差值，速度大大加快。（为了看起来更加符合实际，我把题目中的 A、B 改为了 l、r）

我建立了一个差分数组 s，$s_i=a_i-a_{i-1}$ 每次操作只需 $s_l \gets s_l+1,s_{r+1} \gets s_{r+1}-1$ 便可结束。

然后，用一个类似 dp 的式子 $a_i=a_{i-1}+s_i$ 就可用少到几乎可以忽略不计的 $\Theta(n)$ 的时间来构架出整个 a 数组。

最后使用 sort 排序，输出 $a_{\frac{n+1}{2}}$ 就可结束程序

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
int a[1000005],n,k,s[1000005];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		int l,r;
		cin>>l>>r;
		s[l]++;
		s[r+1]--;
	}
	for(int i=1;i<=n;i++)
	{
		a[i]=a[i-1]+s[i];//因为定义时a[0]就为0，所以不用担心当i=1时有问题 
	}
	sort(a+1,a+n+1);
	cout<<a[(n+1)/2]<<endl;
    return 0;
}
```



---

## 作者：Hzq11_ (赞：1)

# 废话少说,上代码
```cpp
//SP10500     C++
#include <iostream>
const int MAXN=int (1e6)+1;
int a[MAXN],f[MAXN];
#include <algorithm>
int main(){
	int n,k;
    using namespace std;
	ios::sync_with_stdio (false);
	cin>>n>>k;
	for (int i=0,A,B;i<k;i++)
		cin>>A>>B,f[A]++,f[B+1]--;
	int Sum=0;
	for (int i=1;i<=n;i++)
		Sum+=f[i],a[i]+=Sum;
	sort (a,a+n);
	return (cout<<a[n>>1]<<endl)&&0;
}
```
只需要一个标记数组

---

## 作者：yxy666 (赞：0)

这道题我有一个树状数组的想法。。。（很奇怪，但是 $AC$ 了）

下列是推理过程：

设原数组第 $i$ 位的值为 $Ai$ ，令 $D[i]=A[i]-A[i-1]$ ，则有(这里认为 $A[0]=0$ )：

$D[1]=A[1]-A[0]$

$D[2]=A[2]-A[1]$

$D[3]=A[3]-A[2]$

$D[4]=A[4]-A[3]$
...

$D[x]=A[x]-A[x-1]$

$A[x]=D[1]+D[2]+D[3]+...+D[x]$

        x
$A[x] = ∑(D[i])$

           i=1

$A[1]=D[1]$

$A[2]=D[1]+D[2]$

$A[3]=D[1]+D[2]+D[3]$

$A[4]=D[1]+D[2]+D[3]+D[4]$

$A[5]=D[1]+D[2]+D[3]+D[4]+D[5]$

$A[6]=D[1]+D[2]+D[3]+D[4]+D[5]+D[6]$

$A[7]=D[1]+D[2]+D[3]+D[4]+D[5]+D[6]+D[7]$

于是我们得到了：

$x$          $x$      $x$

$∑A[i]=(x+1)∑D[i] - ∑D[i]×i$

$i=1$ 	———————      $i=1$ ———   $i=1$

一个维护 $Di$ ，一个维护 $Di ×i$ 

$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,Q,a[maxn],c1[maxn],c2[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void add(int x,int date){
	int i=x;
	while (i<=n) c1[i]+=date,c2[i]+=x*date,i+=i&-i;
}
int get(int x){
	int sum=0,i=x;
	while (i) sum+=(x+1)*c1[i]-c2[i],i-=i&-i;
	return sum;
}
int main(){
	n=read(),Q=read();
	while (Q--){
		int x=read(),y=read();
		add(x,1),add(y+1,-1);
	}
	for (int i=1;i<=n;i++) a[i]=get(i)-get(i-1);
	sort(a+1,a+1+n);
	printf("%d\n",a[n/2+1]);
	return 0;
}




```



---

## 作者：james1BadCreeper (赞：0)

若直接暴力模拟的话，程序是这样的：
```cpp
int a[1000005];
int main(void)
{
    int n,k,l,r;
    scanf("%d%d",&n,&k);
    while(k--)
    {
        scanf("%d%d",&l,&r);
        for(register int i=l;i<=r;i++) 
            a[i]++;
    }
    sort(a+1,a+n+1);
    printf("%d",a[n/2+1]);//也可以写成(n+1)/2
    return 0;
}
```

但是这显然过不了，因为最坏情况下修改整个序列，单次修改时间复杂度 $O(n)$ ，总时,排序时间复杂度 $O(n \log n)$ ，总时间复杂度大于 $O(nk)$ ，在$n=10^{6},k=2.5\times10^4$的极限数据下：

$~~~~T(nk+n \log n)$   
$\approx O(10^6\times10^4+10^6 \log 10^6)$   
$\approx O(10^{10})$

---

程序的速度瓶颈在于修改操作，如何加快修改操作呢？

有一种快速查询区间和的操作叫做前缀和，即令$S_i=\sum\limits_{k=1}^nA_i$（$\sum$是求和符号，$\sum\limits_{i=a}^bA_i=A_a+A_{a+1}+...+A_{b-1}+A_b$），则$\sum\limits_{i=l}^rA_i=S_r-S_{l-1}$（想一想，为什么是`S[r]-S[l-1]`）,我们称 $S$ 是序列 $A$ 的前缀和。

---

再来看一个好玩的东西：我们有一个序列$A$：`1 2 1 1 5`，它的前缀和是`1 3 4 5 10`，若我们把原序列的第三项加上 $1$ ，则前缀和就变成了```1 3 5 6 11```，后三项都加上了 $1$ 。 

嘻嘻，真好玩！

**等等！**若在把原序列的第 $5$ 项加上 $-1$（想一想为什么是 $-1$ ），那么前缀和变成了`1 3 5 6 10`，正好是将原前缀和的$[3,4]$区间加上了 $1$ ,所以我们得到了一个单次修改复杂度 $O(1)$ 的维护方式！

**这种思想被称之为差分**，由于我们只需在最后还原一次原序列，所以总时间复杂度 $O(n+k)$ ，可以完成本题！

---

那么如何实现程序呢？

首先要求出一序列 $C$ ，保证 $C$ 的前缀和是原序列，这里称 $C$ 是原序列的差分。   
接下来进行维护，每次将 $[l,r]$ 区间加上 $x$ 就将 $C_l+x,C_r-x$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>

//请见https://www.luogu.com.cn/paste/a3732se5

using namespace The_Future_Diary;

int n,k;
int A[1000005],C[1000005];

int main(void)
{
    register int n,k;
    n=read(),k=read();
    while(k--)
    {
        C[read()]++;
        C[read()+1]--;
    }
    for(register int i=1;i<=n;i++)
        A[i]=A[i-1]+C[i];
    nth_element(A+1,A+n/2+1,A+n+1);//?
    printf("%d",A[(n>>1)+1]);
    return 0;
}
```

这里的`nth_element`是什么东西?

看大多数人用的都是`sort`，当 $n\geq10^7$ 时，它们必死无疑，虽然 $STL$ 的`sort`非常厉害，但平均时间复杂度是 $O(n\log n)$ ,所以这里使用 $O(n)$ 的`nth_element`，用法是：（可查看[这里](https://zh.cppreference.com/w/cpp/algorithm/nth_element)）
`nth_element(左元素指针(闭),指定第k小元素指针，右元素指针(开))`使得第 $k$ 小的元素出现在第 $k$ 个位置上，不保证其它元素的顺序。

---

## 作者：LechX (赞：0)

~~这是树状数组的模板题吗？~~

根据要添加一包新的干草到范围为A..B的干草堆顶，很容易想到用数据结构来维护进行区间修改，然后对每一堆干草进行单点查询，然后排序，求中位数

因为数据范围达到了10^6，树状数组相对线段树来说常数小，还好写，所以采用了树状数组，运用差分思想来实现

上代码：

```pascal
var
 a,tree:array[0..1000005]of longint;
 n,k,i,l,r,id:longint;
function lowbit(x:longint):longint;
//树状数组的核心lowbit
begin
 exit(x and (-x));
end;
procedure addsum(x,y:longint);//修改操作
begin
 while x<=n do
 begin
  tree[x]:=tree[x]+y;
  x:=x+lowbit(x);
 end;
end;
function getsum(x:longint):longint;//查询操作
begin
 getsum:=0;
 while x>0 do
 begin
  getsum:=getsum+tree[x];
  x:=x-lowbit(x);
 end;
 exit(getsum);
end;
procedure qsort(l,r:longint);//快排。。。
var
 t,mid,i,j:longint;
begin
 i:=l;j:=r;
 mid:=a[(l+r)div 2];
 repeat
  while a[i]<mid do inc(i);
  while a[j]>mid do dec(j);
  if i<=j then
  begin
   t:=a[i];a[i]:=a[j];a[j]:=t;
   inc(i);dec(j);
  end;
 until i>j;
 if l<j then qsort(l,j);
 if i<r then qsort(i,r);
end;
begin
 read(n,k);
 for i:=1 to k do
 begin
  read(l,r);//读入
  addsum(l,1);
  addsum(r+1,-1);//通过差分来对[l..r]加上1
 end;
 for i:=1 to n do
  a[i]:=getsum(i);
 //统计每一堆干草的高度
 qsort(1,n);
 id:=(n+1)>>1;//求出中位数的下标
 write(a[id]);
end.
```

---

