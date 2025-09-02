# Facer的工厂

## 题目描述

Facer 是一个工厂里的兼职工人，这回他碰到了一个问题。

有 $N$ 根钢管，每根长度是 $a_i$。

有一个钢管加工器，每秒钟可以加工 $k$ 长度的钢管。

Facer 需要按顺序加工这些钢管。

不过呢，机器的最大等待长度是 $h$，即等待加工（已经塞入机器却还没有加工的钢管）的钢管长度不能超过 $h$（保证 $a_i \le h$）。

Facer 只能在整数秒的时候塞入钢管。

求 Facer 处理完这些钢管最少要多久呢？

## 说明/提示

样例 1 解释：只有 $1$ 根钢管，加工时间为 $\lceil 5/3\rceil= 2$。

样例 2 解释：

第一秒塞入 $5$，等待长度 $5$，机器处理了 $3$，等待长度 $2$。

第二秒塞入 $4$，等待长度 $6$，机器处理了 $3$，等待长度 $3$。

第三秒塞入 $3$，等待长度 $6$，机器处理了 $3$，等待长度 $3$。

第四秒塞入了 $1,2$，等待长度 $6$，机器处理了 $3$，等待长度 $3$。

第五秒无塞入，等待长度 $3$，机器处理了 $3$，处理完毕。

$N \le 100000$，$h,a_i \le 10^9$。

本题 by zhouyonglong


## 样例 #1

### 输入

```
1 5 3
5```

### 输出

```
2```

## 样例 #2

### 输入

```
5 6 3
5 4 3 2 1```

### 输出

```
5```

# 题解

## 作者：Blue_wonders (赞：13)

### AC,附详细解释
这个题解也是我RE#19后看了下大佬的代码，然后改进了自己的，也感谢下讨论区的大佬
#### 这个题#19 特别大，RE了好几遍，TLE了好几遍
	cin>>,cout<<不能用，RE的可以换一换输入输出
#### 思路
	模拟吧，详解在注释，代码不长，就不拿出来单独解思路了
#### AC代码
[AC详情](https://www.luogu.org/recordnew/show/17242014)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a,o;
long long s=0;
int main(){
    scanf("%d%d%d",&n,&m,&k);//输入，要用scanf，不然#19 RE 
    for(int i=1;i<=n;i++){//对于每一个物品都判断一次 
        scanf("%d",&a);//同样 
        if(o+a>m){//如果这个加上上一个剩余的长度最大等待长度 
            s++;//这一秒不能放，所以让机器先处理一次，s++进入下一秒 
            //在处理的这一秒会把之前剩余的处理完(因为后面是%运算，所以剩下一定系＜机器处理一秒的) 
            o=a;//剩余的没有了，把新的杆子放到等待处 
        }
        else o+=a;//如果这个杆子加上剩余的不大于等待的，就一块算 
        s+=o/k;//时间加上机器最大处理的时间 
        o%=k;//o记录剩下的有多长(o一定小于机器一秒处理的长度) 
    }
    if(o!=0)s++;//最后如果o还有数，就得画上一秒去处理剩余的 
    printf("%lld\n",s);//输出 
    return 0;
}
```
感谢大家能看我的题解!~

---

## 作者：Jinyeke (赞：4)

### P2793 Pascal题解
#### 这道题目相信大家都可以看懂，就是纯粹的模拟，不过要注意题目说得按顺序处理这些钢管（这样明显简单很多）。
#### 在模拟的时候，只需判断两个地方：
 1. 当这段钢管可以放进去时，即这段钢管加上一秒剩余钢管<=最大等待长度，很明显，直接加上去；
 2. 当这段钢管不可以放进去时，即这段这段加上一秒剩余钢管>最大等待长度，那么就秒数+1，剩余钢管数为当前钢管。

 当然，在判断完后，要进行模拟，
 #### 即总时间加上当前需要的时间，并且把上一次剩余的钢管长度进行求余。

#### 要注意这道题所要求的数据范围比较玄学，pascal中数组最好开longint（开int64不知道为什么会WA或RE），总时间开int64或qword（因为一个时间最多为10^9，最多有10^5个数），其余的随意。


如果你只拿了部分分，而错的地方是WA，那么就请参考以下程序的定义：

定义部分（WA的大多都是因为定义出了问题，因为题目本身是比较简单的）：

sum为总时间

shengyu为上一次剩余钢管数

n，h，k如题目

### 部分分：
59分定义：
```pascal
var
 n,h,k,i,j,shengyu,sum:longint;
 a:array[0..100005] of longint;
```
![59](https://cdn.luogu.com.cn/upload/image_hosting/m28b9hm4.png)



79分定义：
```pascal
var
 shengyu,sum:qword;
 n,h,k,i,j:longint;
 a:array[0..100005] of qword;
```
![79](https://cdn.luogu.com.cn/upload/image_hosting/amy1hxzq.png)



94分定义：
```pascal
var
 sum:qword;
 n,h,k,i,j,shengyu:longint;
 a:array[0..100005] of qword;
```

![94](https://cdn.luogu.com.cn/upload/image_hosting/7343gxse.png)

最后直接上满分代码（附带解释）

Code：pacal

```pascal
var //注意定义！！！
 sum:qword;
 n,h,k,i,j,shengyu:longint;
 a:array[0..100005] of longint;
begin
 readln(n,h,k);
 for i:=1 to n do read(a[i]);
 for i:=1 to n do 
  begin
  if a[i]+shengyu>h then //判断是否超过最大等待长度
   begin
    inc(sum); //秒数加1，这1秒内把上一次剩余的加工完（因为上一次已经求过余了，所以1秒一定能处理完）
    shengyu:=a[i]; //剩余长度变为当前长度
   end
  else shengyu:=shengyu+a[i]; //不超过就直接加
  sum:=sum+shengyu div k; //加上加工的时间
  shengyu:=shengyu mod k; //求余
 end;
 if shengyu<>0 then inc(sum); //如果还有剩余的没处理完，加时间
 write(sum); 
end.
```




---

## 作者：qwaszx (赞：4)

居然没有题解那我来发一篇好啦

一开始看错题以为不需要按顺序处理然后26

后来模拟遇到各种坑......果然还是太菜了

首先注意到一段钢管什么时候处理都是一样的（零头留着）

不管接不接后面一段这一段能处理的总是要处理

所以我们可以每次直接加上当前长度再%k

然后注意一下如果超过总长度的话，那么需要先处理掉前面的

因为%k了所以只会处理一次，直接把长度变成当前长度即可

代码非常好写
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#define getchar gc
using namespace std;
int n,h,k,a,t;
long long ans;//不开long long会炸掉
char gc()//正常的读入优化，scanf也跑得很快
{
	static char BB[1000001],*S=BB,*T=BB;
	return S==T&&(T=(S=BB)+fread(BB,1,1000000,stdin),S==T)?EOF:*S++;
}
int getin()
{
	int x=0,f=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int main()
{
	n=getin(),h=getin(),k=getin();
	for(int i=1;i<=n;i++)
	{
		a=getin();
		if(t+a>h)ans++,t=a;//处理剩余
		else t+=a;//直接加
		ans+=t/k;//统计答案
		t%=k;//零头
	}
	ans+=t>0;//最后剩下的一点
	cout<<ans<<endl;
}
```
~~其实这都是在看了其他dalao的代码之后写出来的~~

---

## 作者：tzl_Dedicatus545 (赞：3)

这道题的思路是：

先输入当前钢管的长度$a_i$，然后分两种情况(设当前等待处的长度为$o$,y答案为$ans$）：

 $\begin{cases}o+a_i>m:ans++,o\gets a_i\\o+a_i \le m:
 o \gets o+a ,
 ans \gets ans+o\div k ,o \gets o\bmod k
 \end{cases}$ 
 
 输入完成后，如果$o \ne 0$，$ans$还要再加$1$。
 
注意这题第$19$个数据点如果用 $\texttt{cin/cout}$会$\texttt{RE}$，要用$\texttt{scanf/printf}$(麻烦管理大大看一下第$19$个数据点有没有问题)

## AC Code:

```cpp
//By: Luogu@wangdemao(308854)
#include <iostream>

using namespace std;

int main()
{
    //ios::sync_with_stdio(false);
	int n,h,k;
	
	scanf("%d%d%d",&n,&h,&k);
	
	int dengdaichu=0;
	long long time=0;
	
	for(int i=1;i<=n;i++)
	{
	    int t;
		scanf("%d",&t);
		
		if(dengdaichu+t>h)
		{
			time++;
			dengdaichu=t;
		}
		else
		{
			dengdaichu+=t;
		}
		time+=dengdaichu/k;
		dengdaichu%=k;
	}
	
	if(dengdaichu!=0)
		time++;
	
	printf("%lld",time);
	
	return 0;
}

```

---

## 作者：AmadeusSG (赞：3)


[题面](https://www.luogu.org/problemnew/show/P2793)

这道题#19简直有毒。

先发代码：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a,n,h,k,nowlen;
ll Time;
/*
Time：当前耗费的时间。
a：每根管子长度。
n：管子数量。
h：最大等待长度。
k：机器每秒处理管子长度。
nowlen：管子里当前剩余长度。
*/
int main()
{
	scanf("%d%d%d",&n,&h,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a);
		if(nowlen+a<=h)nowlen+=a;
		else
		{
			++Time;
			nowlen=a;
		}
		Time+=nowlen/k;
		nowlen%=k;
	}
	Time+=nowlen>0;
	printf("%lld\n",Time);
	return 0;
}
```

首先，根据数据范围，n,a,h都是**int类型**的。Time当然要开long long。(不然re，wa，tle你任选一个)

同时a不能开数组，开不下。

接下来理解一下代码。

这道题就是模拟，按顺序一个一个放进去就可以了。

首先
```
if(nowlen+a<=h)nowlen+=a;
意思是如果当前机器剩余长度与新加进来的长度小于总等待长度，就直接加进去处理。
```

```
else
{
	++Time;
	nowlen=a;
}
如果塞不下了，就先处理完当前还剩余的长度，再塞进去。
为什么Time只加1呢，后面会讲到。
```

```
Time+=nowlen/k;
nowlen%=k

更新完nowlen后，nowlen/k即为机器处理完nowlen所需的时间。
当然nowlen还有可能不能整除k，意思是处理完后可能还有剩余。
注意，这里剩余的长度一定小于k，应该很容易证明：一个数/k的余数<k。


所以只前time只加1，是因为如果有剩余一定小于k，所以最多一秒就能处理完。
```

当然还要注意，如果最终处理完还有剩余，那就还要Time++。
最终就可以出答案了。
```
Time+=nowlen>0;
printf("%lld\n",Time);
```

---

## 作者：hylong (赞：2)

**题意分析:**

    本题是模拟题，思想难度普及-，但代码实现难度普及/提高-。
**得分历程：**

    我开始按题目描述模拟，结果5分，经修改，10分。
    后来，我用了另一种方法模拟（by Albert_ljy 的题解），结果94分，最后一个点TLE。
    再后来，我用快读，开O2，依旧94分。
    最后我看了看讨论区，发现要用int而不用long long......
**注**

   1.我把注释放在100分代码内。
   
   2.前置知识点是快读（手打），不懂我帮你[百度一下](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&tn=02003390_23_hao_pg&wd=C%2B%2B%E6%89%8B%E5%86%99%E5%BF%AB%E8%AF%BB&oq=%2526lt%253B%252B%252B%25E5%25BF%25AB%25E8%25AF%25BB&rsv_pq=c6eef1b4000f3fdb&rsv_t=5f16gfS0o0o1PpAQaG7MZghvnKCYt7eXke%2F%2BJl9UimM3xts5Kv7LLtjYbm0ygp%2BtVbb3Vljk70IB&rqlang=cn&rsv_enter=1&inputT=9449&rsv_sug3=21&rsv_sug1=8&rsv_sug7=100&rsv_sug2=0&rsv_sug4=10556)
   
**代码实现：**
    94分代码：
```cpp
    
#include<bits/stdc++.h>
using namespace std;
long long read()
{ 
    char a=getchar();
    long long x=0;
    while(a<'0' || a>'9')
     a=getchar();
    while(a>='0' && a<='9')
    {
     x=x*10+(long long)(a-'0');
 	 a=getchar();
    }
    return x;
}
int main()
{
    long long i,n,h,k,num=0,time=0,q;
    n=read();h=read();k=read();
    for(i=1;i<=n;i++)
    {
     q=read();
     if(num+q>h)
      time++,num=q;
     else
      num=num+q;
     time=time+num/k;
     num=num%k;
    }
    time+=num>0;
    printf("%lld\n",time);
    return 0;
}
```
    100分代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{ 
    char a=getchar();
    int x=0;
    while(a<'0' || a>'9')
     a=getchar();
    while(a>='0' && a<='9')
    {
     x=x*10+(int)(a-'0');
 	 a=getchar();
    }
    return x;
}//按个人习惯的手打快读，其实可以用scanf(我纯属自找麻烦)。
int main()
{
    int i,n,h,k,num=0,q;//注意不要把int改为long long，否则第十九个点会TLE
    long long time=0;
    n=read();h=read();k=read();
    for(i=1;i<=n;i++)
    {
     q=read();
     if(num+q>h)
      time++,num=q;//这一秒放不进去，让机器处理一次,在处理的这一秒能把以前剩下的处理完；后面有求余运算，故剩下的一定小于机器处理一秒的长度。
     else
      num=num+q;//如果能放进去，那么把这一份放进等待长度中。
     time=time+num/k;//把所需的时间加进time中。
     num=num%k;//去除运算过的长度。
    }//模拟
    if(num>0)
     time++;//如果还有一部分没有处理完的，那么时间加1.理由同上。
    printf("%lld\n",time);//输出。
    return 0;
}
```


---

