# Peter 的烟

## 题目背景

**温馨提醒：吸烟有害健康，请勿尝试吸烟！**

## 题目描述

Peter 有 $n$ 根烟，他每吸完一根烟就把烟蒂保存起来，$k$（$k>1$）个烟蒂可以换一个新的烟，那么 Peter 最终能吸到多少根烟呢？

与某些脑筋急转弯不同的是，Peter 并不能从异次元借到烟蒂，抽完后再还回去。

## 说明/提示

对于 $100\%$ 的数据，$1<n, k \le 10^8$。


## 样例 #1

### 输入

```
4 3
```

### 输出

```
5```

## 样例 #2

### 输入

```
10 3```

### 输出

```
14```

# 题解

## 作者：WuYongxuan (赞：860)

# 题解 P1150

因为k个烟蒂=1根烟+1个烟蒂

所以k-1个烟蒂=1根烟

注意减掉最后一根烟的烟蒂

(因这题并没有借烟蒂换烟再还回这一说)

此解法为小学4~6年级水平


```cpp
     #include <bits/stdc++.h>
     using namespace std;
     int main(){
         int n,k;
         cin>>n>>k;
         cout<<n+(n-1)/(k-1);
         return 0;
     } 

```

---

## 作者：fifnmar (赞：349)

目前最高赞的答案讲解过略。知道这种题的人自然知道，不知道这种题的人还是不知道。所以我在这里为不知道这种类型题的同学讲一下具体细节。

设最终Peter抽到了$x$根烟，则其中$(x-n)$根烟都是用烟蒂换来的，而由于Peter最终能抽$x$根烟，所以他自始至终共拥有过$x$个烟蒂。能明白不？

明白了这一点，再想一个细节：实际上Peter抽到的最后一根烟的烟蒂是不能用来换烟的——所以实际可能用来换烟的烟蒂只有$(x-1)$个。

列出关于换来的烟的数量的方程：

$$x-n=\frac{x-1}{k}$$

为了解出$x$的值，我们解这个方程（这个你应该会叭！）；这才得到了结果式：

$$kx-kn=x-1$$
$$x=\frac{nk-1}{k-1}=\frac{nk-n+n-1}{k-1}=n+\frac{n-1}{k-1}$$

之所以化成了最后的形式单纯是因为三次加法和一次除法比两次加法、一次乘法和一次除法要省那么一丢丢时间。

下面是程序：

```cpp
#include <iostream>

int main() {
    unsigned n, k;
    std::cin >> n >> k;
    std::cout << n + (n - 1) / (k - 1) << '\n';
}
```

---

## 作者：bigju (赞：140)

# 这道题我要带来一个很~~弱~~高大上的写法以及一种新思想~~（神犇应该都会吧QWQ）~~
话不多说看代码
```
#include<cstdio>
using namespace std;
int ans7(int yd1,int n1,int k1)
{
    int ans1=0;
    ans1+=n1;
    yd1+=n1;
    while(yd1>=k1)
    {
        yd1-=k1;
        ans1++;
        yd1++;
    }
    return ans1;
}
int main()
{
    int ans=0,n,k,yd=0;
    scanf("%d",&n);
    scanf("%d",&k);
    ans=ans7(yd,n,k);
    printf("%d",ans);
    return 0;
}
```

现在咱我来详细讲一下第一个大括号里的语句
```
int ans7(int yd1,int n1,int k1)/*这是自己手写一个函数，第一个int表示该函数适用的数据类型，也可以是char，bool等。ans7是指这个函数的名称，打个比方比如max（最大值）函数，他的名字就是max（所以说ans7并不影响结果），括号里的东西是指这个函数的作用对象（比如max就是对两个整形起作用），这个ans7的函数括号里的意思就是这个函数对3个整形变量起作用。*/
{
    int ans1=0;//定义答案
    ans1+=n1;//先吸完烟再说
    yd1+=n1;//吸完多少只就有多少烟蒂
    while(yd1>=k1)//只要还能凑齐一根烟
    {
        yd1-=k1;//烟蒂数量减少k1根
        ans1++;//多吸一根
        yd1++;//吸完了又多一个烟蒂
    }
    return ans1;//这里的return是指返回的意思。就像max函数，比如c=max（a，b），求出来a与b中较大的你总得回来赋值给c吧，所以说就要用return，return后面的数代表返回谁的值。

```
```
int main()
{
    int ans=0,n,k,yd=0;//虽然在自创函数中定义了，但不能用。因为你总不能一个变量不定义就用max或min吧
    scanf("%d",&n);//输入
    scanf("%d",&k);//同上
    ans=ans7(yd,n,k);//这里唯一注意的就是一定要和函数里的数一一对应，就是说烟蒂的变量与烟蒂的变量在函数的（）中的位置对应
    printf("%d",ans);//因为已经返回了答案的值，直接输出就好了
    return 0;
}
```
完整代码
```
#include<cstdio>
using namespace std;
int ans7(int yd1,int n1,int k1)
{
    int ans1=0;
    ans1+=n1;
    yd1+=n1;
    while(yd1>=k1)
    {
        yd1-=k1;
        ans1++;
        yd1++;
    }
    return ans1;
}
int main()
{
    int ans=0,n,k,yd=0;
    scanf("%d",&n);
    scanf("%d",&k);
    ans=ans7(yd,n,k);
    printf("%d",ans);
    cout<<"lllll";//防抄袭
    return 0;
}
```
第一次发题解，还是有点紧张,可能有些地方说的不太清楚，请海涵一下QWQ
有错误请大佬指出QWQ
拜拜~~


---

## 作者：6M鹿M6 (赞：102)

#这道题的意思是peter有n根烟，，他每吸一个就有一个烟头，他只要有k个烟头就可以换一根烟 
###这道题可以用模拟
#程序大大：
```cpp
#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
long long n,k,gs,yt;
int main()
{
	cin>>n>>k;//输入原本有的根数和兑换要求 
	while(n!=0)
	{
		n--;//吸烟 
		yt++;//烟头增加 
		if(yt==k)n++,yt=0;//换烟 
		gs++;//吸的根数加 
	}
	cout<<gs;//输出根数 
	return 0;
}
```

---

## 作者：Drug__Lover (赞：50)

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,k,nonu;  //n烟的数量，k需要多少根烟头换一支烟，nonu记录烟头的个数 
    cin>>n>>k;
    int sum=n;    //一开始就能吸n支烟 
    nonu=sum;     //烟头初始数目 
    while(nonu-k>=0) //当烟头数目足够换一只烟的时候 
    {
        nonu=nonu-k;  //换一支烟 
        sum++;         //可以多吸一支烟 
        nonu++;        //得到一个烟头 
    }
    cout<<sum;      //输出吸的烟的个数 
    return 0;
}
```

---

## 作者：NicodeX (赞：49)

//这是一道小学1~2年级的“奥数”题（真的不夸张）



```cpp
//直接模拟即可。程序如下：
//头文件不解释：
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int i,j,k,m,n,s;//定义变量。其中i、j为循环变量（j没有使用），n、k为输入用变量，s作为累加器使用，m为吸一次烟所产生的烟蒂。同时，n也作为烟蒂总累加器。
int main(){
    scanf("%d%d",&n,&k);//输入两个量
    s+=n;//先累加一次吸过的烟
    while(n>=k){//当n比k大时进入循环，循环效果：产生并累加烟
        m=n%k;//获得m个烟蒂
        n/=k;//获得n个烟
        s+=n;//累加烟
        n+=m;//累加烟蒂
    }
    printf("%d",s);//输出
    return 0;//～(￣▽￣～)(～￣▽￣)～
}
```

---

## 作者：John_Nash (赞：21)

这题实际上还有O(1)的做法。

初看这题，第一反应应该是有2种情况：允许借烟或者不允许借烟。比如说，如果n=2，k=3，如果允许借烟的话，可以借一根烟，抽完3根烟之后用3个烟蒂去还一根烟，这样答案为3，如果不允许借烟则为2。好在第二个样例告诉我们是不允许借烟的，否则答案应为15。

不难发现，即使是一道数学题，不借助计算机，在n，k都不大的情况下也能算出答案。我们可以设最终能抽x根烟，则x-n为额外抽的烟数，(x-1)/k为用烟蒂能换到的烟数（因为不允许借，否则是x/k），易知x-n<=(x-1)/k，化简后可得到x<=(kn-1)/(k-1)，则[(kn-1)/(k-1)]则为答案。

以下是代码：

```cpp
#include<cstdio>
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    printf("%d\n",((long long)n*k-1)/(k-1)); //n,k<=10^8，所以用long long 
    return 0;
}

```

---

## 作者：北北北北 (赞：15)

有N支烟，那么就有N个烟蒂，又因为K个烟蒂可以换一支烟，所以最多可换N/K支烟，这里的余数可以看成是剩余烟蒂的数量，当然这里也可以把最多可换烟的数量也给看成是烟蒂数量，因此就可以求出下一轮的烟蒂数量，即(N/K)+(N%K)，然后判断N<K，成立则得到结果，反之则继续重复上述步骤。

PS:不要忘记把中间结果给累加起来。

再啰嗦一句，这题可以直接算，我是真没想到QWQ



------------
```c
#include <stdio.h>

int main(void)
{
	int n,k,sum;
	
	scanf("%d %d", &n,&k);
	sum = n;
	while(n >= k)
	{
		sum += n/k;
		n = (n/k)+(n%k);
	}
	printf("%d", sum);
	
	return 0;
} 
```


---

## 作者：Linune_Gump (赞：15)

# P1150 Peter的烟 题解
### 题目链接：[P1150 Peter的烟](https://www.luogu.org/problemnew/show/P1150)
已经第三次了，我好好排排版吧[笑哭]

毫不夸张的说，这题真的挺简单的。。我这个蒟蒻都会。。

不过看到各位奆佬用的都是循环，就想再写一种递归的解法

~~(吐槽一下)其实，我对递归有这样一种认识。我们知道，函数是一种解决问题的方法，对于每个函数而言，他都有自己的功能。同时，我们在使用函数的时候并不需要知道他的内部是怎么运行的。~~

~~我见过很多老师讲递归讲回溯的时候都把他们当作一个模板，这样其实是不好的。当认为函数是一个功能去使用的时候递归其实就比较好理解了。~~

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int tot,k;//tot表示他一共抽了多少烟，k表示多少烟换一根烟 
void f(int n)//x表示这一轮抽了多少烟，n表示他还有多少烟 
{
    int x;
    if(n/k==0)//不够抽了，把剩下的抽完
    {
        tot+=n;//剩下的n根抽完
        return ;
    } 
    x=n/k,n=n%k+x,tot+=x*k;//抽完一部分烟之后重新统计还有多少烟以及一共抽了多少烟
    f(n);//现在，Peter拥有了重新统计的n根烟，又可以愉快的抽烟了
} 
int main()
{
    int n;
    scanf("%d%d",&n,&k);
    f(n);//函数f(n)表示有n根烟能抽几根
    printf("%d1\n",tot);//总抽烟量在tot中
    return 0;//请不要抄袭我的代码，不然可能会WA哦
}
```
Peter抽烟 流程：

有n根烟，开始抽烟

step 0:-->如果peter本来就没有k根，意味着他只能抽n根，没办法换烟了，总烟量加上n，就不抽了

step 1:-->尽量多抽，不足k根为止

（因为C++整数除法会向下取整，所以抽掉（n/k*k）根）

step 2:-->统计到总抽烟数量中去

step 3:-->换到烟x根，加到总数目n中去

step 4:-->下一轮抽烟，这次他有n根，

回到step 0 重新开始一轮递归

（但是n的数目变化了）

~~求管理员过~~

~~抽烟是不良行为，小朋友不要模仿哦！~~

---

## 作者：沧海无雨 (赞：13)

【题目分析】

用题目给的样例进行简单模拟一下，一开始有4根烟，然后每收集3个烟蒂就可以换1根烟。一开始是4根，抽掉3根后，剩下1根，然后用烟蒂换烟，烟就增加了1根，烟变成了2根，然后在抽完这2根，不够3个烟蒂，无法再换新的烟，因此总共抽到烟是4+1=5根。用如下表格来表示：(n=4,k=3)

烟的数量n    烟蒂d    烟的总数（抽的烟）ans

（一开始）   4    0    0

3    1    1

2    2    2

1    3    3

（换烟）1+1    0    3

1    1    4

0    2    5

用样例2来再模拟一次，会更加清晰（n=10,k=3）

烟的数量n    烟蒂d    烟的总数（抽的烟）ans

10    0    0

9    1    1

8    2    2

7    3    3

8    0    3

7    1    4

6    2    5

5    3    6

6    0    6

5    1    7

4    2    8

3    3    9

4    0    9

3    1    10

2    2    11

1    3    12

2    0    12

1    1    13

0    2    14

规律很明显：抽过的烟，其实就是烟的总数，每凑够k个烟蒂，就能增加1根烟，然后继续抽，直到烟的数量为0。因此可以用while循环来解决。

【程序框架】

```cpp
    while(n>0){
        if(d==k){//凑够烟蒂数量，换烟
            n++;
            d=0;
        }
        n--;//抽1根
        ans++;//烟数增加1
        d++;//烟蒂增加1
}
```
【查考代码】
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    int num=n,ans=0,t=0;//num表示烟的数量，ans是抽烟的数量，t是烟蒂数量
    while(num>0){//当还有烟时
        num--;//抽1根，数量减少1
        ans++;//抽过的烟数量增加1
        t++;//烟蒂增加1
        if(t==k){//如果凑够了
            num++;//烟的数量增加1
            t=0;//烟蒂又重新变成0
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
 

---

## 作者：封禁用户 (赞：6)

题解：


```cpp
var
n,m,t: qword;  开大一点
begin
readln(n,m);
t:=t+n;        先把现有的烟加上
repeat 
if (n div m>0) then begin t:=t+(n div m); n:=(n mod m)+(n div m); end;  // (n div m) 是加上奖励的烟，有些人忘了加这一步
until n<m; //如果兑换不了了，则结束
write(t);
readln;
end.
```

---

## 作者：Riddle (赞：3)

这可能是最简洁的代码了吧！

```cpp
#include<iostream>

using namespace std;

int
main()
{
    int s, k;
    cin >> s >> k;
    int a = s;  //a记录目前Peter剩下多少烟没有吸
    
    for(; a / k > 0; s += a / k, a -= a / k * (k - 1));  //假设每次都能一次吸完所有烟，兑换完之后再吸，如此循环
    
    cout << s;
    
    return 0;
}
```

---

## 作者：tryrtj (赞：2)

题目描述

Peter有n根烟，他每吸完一根烟就把烟蒂保存起来，k(k>1)k(k>1)个烟蒂可以换一个新的烟，那么Peter最终能吸到多少根烟呢？

输入输出格式

输入格式：
每组测试数据一行包括两个整数n,k(1<n,k<=10^8n,k(1<n,k≤10^ 
8
 )。

输出格式：
对于每组测试数据，输出一行包括一个整数表示最终烟的根数。

输入输出样例

输入样例#1： 

4 3

输出样例#1： 

5

输入样例#2： 

10 3

输出样例#2： 

14

说明

1<n,k <= 10^81<n,k≤10^8

```
#include<iostream>
using namespace std;
int main(){
	long long n,k,zong=0;
	cin>>n>>k;
	zong+=n;
	long long o;
	while(n>=k){
		o=n/k;
		zong+=n/k;
		n=n%k;
		n+=o;
	}
	cout<<zong;
	return 0;
}
```

---

## 作者：wyw666 (赞：2)

这题事实上很简单，主要把握好烟与烟蒂之间的关系就好了。

上题解：
```cpp
#include<iostream>
using namespace std;
int main(){
	int n,k;
    int m=0,sum=0;  //烟蒂的数量与烟的总数量
	cin>>n>>k;  //输入烟的数量与多少根烟能换一根烟
	while(n>0){ //当不能换时停止循环
		sum+=n;  //加上当时的烟数
		m+=n;  //烟蒂的数量加上烟的数量
		n=m/k;  //换烟
		m%=k;  //减去烟蒂的数量
	}
	cout<<sum;  //输出总烟数
	return 0;  //完美地结束
}
```

---

## 作者：伍六七 (赞：2)

这道题很水，属于入门难度。

```cpp
var a,n,s,k,t:longint;
begin
  read(a,k);
  s:=a;  //记原本可以吸的烟
  repeat
   a:=a-k+1;  //拿抽完的烟蒂，还一条新烟
   s:=s+1;  //把新烟记入s
  until a<k;
  write(s);
end.
```

---

## 作者：LIUBOWEN (赞：2)

唉，这题我愁了五分钟。。。

先别看答案

这其实是不断求烟蒂和烟的值，直到烟蒂不足为止。。。

----------------------------答案隔离------------------------------------











----------------------------------------------------------------------

不会？


```cpp
var
n,i,k,m,s,l,mm:longint;//mm是摄像头，专门监视他吸了几支烟
begin
read(n,k);//买了多少烟，几个烟蒂换一个
m:=n;
mm:=n;
l:=0;
while m>=k do begin//直到烟蒂不足
mm:=mm+m div k;//烟蒂换了烟
m:=(m div k)+l;//烟烧成了烟蒂
l:=m mod k;//三以外的烟蒂
end;
write(mm);//妻子：让你吸烟，被我逮到了吧，让我看看你吸了多少烟！！！
end.
懂了吧。。。
```

---

## 作者：ROOToj (赞：2)

非常简单的模拟题，只要在烟抽完前（n>0）每抽一支烟n--、m（烟头数）++、如果m==k（烟头数够换一支烟）就n++、m清零即可。


附上AC源代码：


















```cpp
#include
using namespace std;
int n,k,m=0,tot;
int main()
{
    scanf("%d%d",&n,&k);
    tot=n;
    while(n)
    {
        n--;
        m++;
        if(m==k){n++;m=0;tot++;}
    }
    printf("%d\n",tot);
    return 0;
}
```
​

-------------------------------------------END-------------------------------------------


---

## 作者：野菜汤 (赞：2)

题解：

这一题虽然已经有大神写过题解了，可是个人觉得他们的题解虽然看起来已经是非常简洁了，可我觉得还是太慢了。那么我这个题解就是在对烟数量的处理上加以了改进，使之更快捷。此标程仅供参考。

```delphi
var k,n,sum:longint;
begin
  read(n,k);
  sum:=n;{先将所有烟都抽了，sum用于记录总烟数所以也就等于n了}
  while n>=k do{直到烟头数不能再换烟了为止}
    begin
      n:=n-k+1;{烟头数减去k个需换烟蒂，因为又有一个烟抽了，所以再加一个烟头数}
      inc(sum);{抽的总烟数加一}
    end;
  write(sum);
end.
```
先说一下我这个题解的详细内容解释。我先是将sum记录成当前已经有的烟的数量，因为这些烟必定是会抽的，所以现在n个烟已经全部变成烟头了，然后在用个循环，第七行的意思就是烟头的总数减去能换的k个，然后就会又有一支烟了，所以烟头数再加一，然后抽的烟的总数加一。

就是这么简单，这样子写出的程序快了不只是一星半点，所以请大家要好好理解呀。


---

## 作者：于婷楚 (赞：2)

因为k个烟蒂换的烟就包括本身的一个烟蒂，
如果换的烟蒂能够和之前的烟蒂加起来再换一根烟的话，
就可以将又换的这根烟加上之前抽的烟，
如果剩的这个烟蒂不够换的话就要将这根烟蒂减去，
那么k就要减一，
因为k减去了一个烟蒂也就等于减去了一根烟，
所以n也要减一，
代码如下：
```cpp
#include<iostream>//标准头文件
using namespace std;//标准命名空间
int main()//主函数
{
  int a,n,k;//定义整型
  cin>>n>>k;//输入
  a=n+(n-1)/(k-1);//赋值
  cout<<a;//输出
  return 0;
} 
```

---

## 作者：我叫小明0_0 (赞：2)

数学思维，憋缩话，看代码。

```cpp
#include<stdio.h>
#include<stdlib.h>
int n;   //初始烟数
int m;   //烟蒂数
int k;   //换
int ans;   //能抽
int main()
{
    scanf("%d",&n);
    scanf("%d",&k);
    ans=n;   //全抽了
    m=n;     //全部烟蒂
    while(m>=k)   //能换
    {
       ans+=m/k;   //全换调
       m=m%k+m/k;   //烟蒂为没换的与刚抽完之和
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：oreimo_eromanga (赞：2)

```cpp

#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<string>
#include<cstdio>
#include<cmath> //头文件库很好，copy下来，以后有用！
using namespace std;
int main()
{
    int n,k,yan,a=0,s=0;
    cin>>n>>k;yan=n;
    a=n/k;yan+=a;
    for(int i=1;i<=1000000;i++)
    {
            s=a%k;a=a/k;yan+=a;a+=s; //烟蒂不能清零，否则会有测试点过不去！
            if(a<k){cout<<yan<<endl;return 0;}
    }
    return 0;
}

```

---

## 作者：⚡皮卡丘⚡ (赞：1)

#  这道题...
#### 其实就是一道纯暴力，模拟题
## 思路：
	用 for循环模拟
    由题可知k个烟蒂可以换一个新的烟
    知道这些这道题就迎刃而解了
## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,t,s; //定义n,k,t,s
int main()
{
	cin>>n>>k; //输入
	for(int i=1;i<=n;i++) //模拟n轮
	{
		s++; //s总吸烟个数
		t++; //t为目前可换取新的烟的烟蒂个数
		if(t>=k) //当t达到k了烟蒂便可换取新的烟
		{
			t-=k; //t减去k并将n++
			n++;
		}
	}
	cout<<s<<endl; //输出总吸烟个数
	return 0; //完美结束
}

```
###### 请求支持，~~大佬勿喷~~

---

## 作者：jeffyang (赞：1)


~~看到还没有人发perl题解，所以就发一个~~


## 下面ac100分代码；~~思路并不是很特别~~

------------

```
#!/usr/bin/perl -w
($sum,$k)=split /\s+/,<>
#k是换一支烟的烟头数，nonu记录烟头的个数
#sum是最后的答案
for($nonu=$sum;++$sum,++$nonu){$nonu-=$k}
print $sum;		
#输出烟的个数 
```


------------



## 大概解释一下

实际上就是直接模拟，烟头数目足够换一只烟时就换烟，也就是烟头数加一，到换不了烟的时候就输出烟的个数。
```
k是换一支烟的烟头数，nonu记录烟头的个数
sum是最后的答案

$nonu=$sum；  烟头初始数目;
$nonu-$k>=0； 烟头数目足够换一只烟时;
$nonu-=$k；   换烟
++$sum；      多一个烟;
++$nonu；     吸烟之后多一个烟头;

print $sum;   
输出烟的个数 
```


---

## 作者：Warriors_Cat (赞：1)

## 这道题其实就是一道简单的模拟题。

不说废话，直接上代码：

```
#include<bits/stdc++.h>
using namespace std;
int n, k;
int s;//表示可用烟蒂换烟的个数 
int main(){
	scanf("%d%d", &n, &k);
	int m = n;//一开始可以吸的烟 
	while(n >= k){
		n = n - k + 1;//每次还剩多少个烟 
		s++;//每一次多吸的烟 
	}
	printf("%d", m + s);//原来的烟 + 用烟蒂换的烟
	system("pause"); //防伪代码 
	return 0;
}
```

然而,下列这段代码
```
while(n >= k){
		n = n - k + 1;//每次还剩多少个烟 
		s++;//每一次多吸的烟 
	}
```
可用
```
s = (n - 1) / (k - 1)
```
来实现。

但为了新手的理解，所以还是用while要好一些。

谢谢各位读者。



---

## 作者：LaUwCaK (赞：1)

//这道题，本蒟蒻用了模拟来做的，如果有什么可以改进的，在评论区留下您宝贵的意见，谢谢。   
这道题只要一边数烟，一边数烟蒂就OK了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,sum;
int main()
{
	cin>>n>>k;//输入烟的个数以及换一根新烟所需烟蒂的个数。
	for(int i=n;i>0;i/=k)
	{
		ans+=i;//累加每次能换多少根烟。
		sum+=i%k;//累加烟蒂的个数。
		if(sum%k==0)//判断每一次所剩的烟蒂是否够换多根新烟。
		{//本蒟蒻第一次没有发现这个问题，只有90分。
			ans+=sum/k;//必须这样写，不能写ans++;
			sum=sum%k;//烟蒂减少
		}
	}
	cout<<ans;//输出答案
	return 0;//华丽结束
}
```

---

## 作者：__一氧化二氢__ (赞：1)


我看了其他dalao的题解，短得一批，自己心中感觉~~我真弱~~
##### **很明显，这就是小学数学的空瓶换饮料！！！（3~4年级的）**
话不多说，上代码
```
#include<bits/stdc++.h>//万能头文件，好用
using namespace std;
int n,k,ni=0,ans=0;
int main()
{
    cin>>n>>k;
    ni+=n;//烟抽完，烟蒂留着
    ans+=n;//开始就抽了n根烟
    while(ni>=k)//能换就疯狂换
    {
        ni-=k;//换了一根烟
        ans++;//抽了
        ni++;//一个烟蒂
    }
    cout<<ans;
    return 0;//完美结束
}
```

---

## 作者：Xsy123456 (赞：1)

###简单的模拟，小学数学

```cpp
#include <cstdio>
using namespace std;

int n,k,t=0;

int main(){
    
    scanf ("%d%d",&n,&k);
    
    if (n<k)  printf ("%d",n);//防止较坑的数据点坑人
    else{
        for (int i=n;i>=0;i-=k){//直接模拟每吸K根烟领一根，最后不能兑了再加上
            if (i<k){
                t+=i;
                printf ("%d",t);
                return 0;
            }
            t+=k;
            i++;
        }
    }
} 
```

---

## 作者：Ufowoqqqo (赞：1)

按照题意模拟即可。

```delphi

var
 n,k,ans:longint;
begin
 read(n,k);
 ans:=n;//将所有烟都抽了
 while n>=k do//能换就换
 begin
  inc(ans,n div k);//忽略余数
  n:=n div k+n mod k//换来的烟加上余数即为新的烟数
 end;
 write(ans)
end.

```

---

## 作者：Sh1no (赞：1)

挺简单的。如下：

```cpp
#include <iostream> （调用库）
using namespace std; （调用名次空间std）
int main() （过程开始）
{
    long long n,k,sum; （定义变量）
    cin>>n>>k; （输入数量）
    sum=n;   （先把烟全部抽完）
    while (n>=k)  （只要烟蒂还能换烟，就继续换下去。）
    {
        n=n-k+1; （减去烟蒂数量。因为又多了一根烟，所以烟蒂+1）
        sum++; （又抽了一根烟）
    }
    cout<<sum;（输出结果）
    return 0; （结束）
}
```

---

## 作者：fadeAwayLi (赞：1)

这题挺简单吧……

```delphi

var n,k,y,s:int64;
begin
     readln(n,k);
     s:=n;
     y:=n;
     while y>=k do
     begin
          inc(s,y div k);
          y:=(y div k)+(y mod k);
     end;
     writeln(s);
end.  

```
如上文，n,k变量作用如题目叙述，然后y记录剩余的烟蒂数量，s记录能吸的总数。

当剩余烟蒂数量大于兑换要求数量时增加s并减小y，其余的不多赘述。


---

## 作者：KesdiaelKen (赞：1)

只需要简单模拟一下就行了。

注意的是，一支烟迟早是要吸的，所以一次循环中直接可模拟为把所有烟都吸完。

模拟的技巧还是注意一下。

代码如下：

```cpp
#include <iostream>
#include <cmath>
using namespace std; 
int main()
{
    int yd=0,y;//记录烟蒂数量和烟数量
    int kx=0;//记录总共吸的烟的数量
    int k;
    cin>>y>>k;
    do
    {
        yd+=y;//全部烟吸完，烟蒂增加
        kx+=y;
        y=yd/k;//加上可回收的烟
        yd-=y*k;//减去已回收的烟蒂
    }while(y!=0);
    cout<<kx;
    return 0;
}
```

---

## 作者：LGG_ (赞：0)

# 简单，易理解

#### 就是~~很水~~一道模拟题

###### 真的简单

	！不要纠结于烟和烟头
    ！烟除以k就是一个新的烟=烟头
    	可以理解为——烟/k=烟头
    ！余下的也是烟头
###### 注意：烟头要除了k余下的才可以加上

然后就可以加一个while循环求答就OK了~~循环条件看心情~~

```c
#include<iostream>
using namespace std;
int n,m,k,ans;
int main()
{
	cin>>n>>k;
	int t=1;ans=n;
	while(t==1){//个人习惯
		if(n>=k){
			m=n/k;
			ans+=m;//计数
			m+=n%k;
			n=m;
		}
		else t=0;
	}
	cout<<ans;
}
```
当然，while那里可以改为
```c
while(n>=k)
```
那if肯定就不能加了~~多嘴~~

~~2019csp加油~~![](https://cdn.luogu.com.cn/upload/pic/1436.png)

---

## 作者：毛梁智洲666 (赞：0)

**这题好水啊！**

只要把公式求出就OK了！

$ 公式：最后烟的数量=原有烟的数量+换到烟的数量。$

所以这道题可以用 while 来把换到烟的数量求出来。只要满了k个烟蒂，最后烟的数量+1，烟蒂的数量-（k-1）。

上代码:
```
#include <bits/stdc++.h> //万能头
using namespace std; //声明姓名空间

int main() {
    int n, k, a = 0, f = 0; //a是最后烟的数量，f是烟蒂的数量
    cin >> n >> k;
    a += n;
    f += n;
    while (f >= k) { //只要可以换，就执行
        f -= k; //减k只烟蒂
        a++; //最后烟的数量+1
        f++; //吸完以后烟蒂数有+1
    }
    cout << a << endl; //输出
    return 0;
}
```
就是这样！求过啊！

---

## 作者：DengTJ (赞：0)

一道水题

```cpp
#include<cstdio>
using namespace std;
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);         //输入n,k
    int sum=0;
    if(n<k)                   //判断：如果n小于k，直接输出n
      {
        printf("%d",n);
        return 0;
      }
    while(n>=k)            //当n大于k时
    {
      n-=k;                     
      sum+=k;
      n+=1;               //烟蒂换烟
    }
    sum+=n;
    printf("%d",sum);         //输出
    return 0;
}
```

---

## 作者：Dr_殇 (赞：0)


 
```cpp
#include<cmath>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<iostream>
#include<algorithm>//头文件准备
using namespace std;
int k,n,ans;
int main (){
    scanf ("%d %d",&n,&k);//输入
    ans+=n;
    while (n>0){
        if (n>=k){//求可以换多少只烟
            ans++;
            n++;
        }
        n-=k;
    }
    printf ("%d\n",ans);//输出
    while (1);//防盗代码
    return 0;
}

```

---

## 作者：CraZYali (赞：0)

之前看了看题解，发现效率不高，加一个快一点的

```cpp
#include<iostream>
using namespace std;
int main(){
    unsigned long long yan,huan,gen=0,di=0;
    cin>>yan>>huan;
    while(yan){//有烟就循环
        gen+=yan;//一次吸完（这个猛）
        di+=yan;
        yan=0;
        while(di>=huan)di-=huan,yan++;//换呀换
    }
    cout<<gen;
    return 0;
}
```

---

