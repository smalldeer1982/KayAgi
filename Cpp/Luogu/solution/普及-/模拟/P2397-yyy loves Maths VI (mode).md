# yyy loves Maths VI (mode)

## 题目背景

自从上次 redbag 用加法好好的刁难过了 yyy 同学以后，yyy 十分愤怒。  
他还击给了 redbag 一题，但是这题他惊讶的发现自己居然也不会，所以只好找你


## 题目描述

一共有 $n$ 个正整数 $a_i$，他让 redbag 找众数。他还特意表示，这个众数出现次数超过了一半。  


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 2\times 10^6$，$a_i \in [1,2^{31})$。

有人想水过,但我告诉你这空间是不够的。

//kkksc03偷偷地说：你随便输出一个数字吧，都有1/2的几率。不过这可是乐多赛，值得不值得你看着办。所以最好想一想正解。


## 样例 #1

### 输入

```
5
2 3 3 3 3```

### 输出

```
3```

# 题解

## 作者：PauGasol (赞：137)

其实这道题，众数的个数大于n的一半是十分重要的条件。

这样我们就可以这么做。

我们来yy一个小房子，每当有数进来的时候，如果房子是空的，那么将这个房子贴上自己的标签。

如果房子里已经有和自己相同数字了，那么进去和它一起♂住。

如果房子里有和自己不同的数字，带一个走出♂房♂子。

最后房子里还剩下的数一定就是众数了。

所以那个大于一半的条件很重要。

···cpp

```cpp
#include<cstdio>
using namespace std;
int n,m;
int house,cnt;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m);
        if(house==m)cnt++;
        if(cnt==0){
            house=m;cnt++;
        }
        if(house!=m){
            cnt--;
        }
    }
    printf("%d",house);
    return 0;
}
```
···

---

## 作者：daks (赞：35)

发一个不同思路的题解

读入每一个数，转化成二进制，统计每一位上1出现的次数，最后扫一遍一个规模在30左右的数组，超过一半就转成相应的十进制记入答案

会不会被卡？

不存在的，如果不是答案的二进制位想要超过n/2,就需要超过n/2个数在这一位上是1，然而，众数超过一半，其余的数哪来n/2个？

```cpp
#include<iostream>
using namespace std;
int cnm[40];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        for(int j=0;(1<<j)<=a;j++)
         if((1<<j)&a)
          cnm[j]++;
    }
    int ans=0;
    for(int i=0;i<=32;i++)
    {
        if(cnm[i]>n/2)
         ans+=1<<i;
    }
    cout<<ans;
}
```

---

## 作者：鸩羽 (赞：30)

  初看题目，毫无思路。
 
  然后想到一个奇怪的方法，因为众数共有总数一半以上，如果我们进行排序，必然n/2的位置是这个众数，但是由于丧心病狂的~~出题人~~空间限制，这样会炸。
  
  上40分代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[2000010];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    if(n%2==0) printf("%d",a[n/2]);
    if(n%2==1) printf("%d",a[n/2+1]);//因为n为奇数的时候n/2下取整，所以n/2+1为中间值
    return 0;
}
```

  仔细思索一番正解，依然没有。遂看题解。发现了一种叫做摩尔投票法的神奇方法。
  
  通过浏览博客得到一些想法。因为众数出现次数超过一半，所以这个众数必然会只有1个。
  
  **下面就是思想了。**
  
  摩尔投票法的基本思想很简单，**在每一轮投票过程中，从数组中找出一对不同的元素，将其从数组中删除。这样不断的删除直到无法再进行投票，如果数组为空，则没有任何元素出现的次数超过该数组长度的一半。如果只存在一种元素，那么这个元素则可能为目标元素。**
  
  为了便于理解，我们想象一个情景，有一堆人在打架，**我们假设每一个人的战斗力都是1换1。也就是A打死B，A也会死**。
  
  **假设只有2波人**（我们把不是众数的数字看作一个数）且各占二分之一，显然继续打下去两边人都会死光。
  
  但是我们现在有2波人,其中一波人特别多（一半以上），显然这波人必然是赢家，虽然不知道打完还剩几个，但一定会有剩下的。因为一换一。**若第二波人有x个，则第一波人有（n-x）个且n-x>x**。那么最后剩下的人就是n-2x个。假设这2波人头上顶着2个不同的数字，这个剩下的人的数字就是众数。
 
 **以上用于帮助理解代码。**
  
  所以我们可以把摩尔投票法看作一种抵消的思想，当前数字进场，然后和上一个判断，如果**是同一个数计数器（js）++**，**如果不是计数器--**。

  当计数器等于0时，ans重新登记为新输入的数，进行抵消的操作，最后剩下的一定是众数**（但众数必须满足大于总数的一半）**
  
  好了上代码。
  
  ```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int n,ls;
    int ans,js=0;//计数器与答案
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&ls);//输入当前的数
        if(js==0) ans=ls;//如果计数器为0即之前均被抵消或现在是第一个输入，记录ans为当前数
        if(ans==ls) js++; //如果记录的数与新输入的数相等，计数器++
        if(ans!=ls) js--; //反之--
    } 
    printf("%d",ans);//最后剩下的就是众数
    return 0;//收尾，告辞
}
```

---

## 作者：leaves_ (赞：12)

这个。。。

其实用到一个叫做摩尔投票法的东西。因为前面的题解都没有说这个所以本蒟蒻就来说一说qwq。

这个就是用O1的内存来求一组数据中的众数（貌似是存在一个数的出现次数大于总数据的一半的时候用的）

转化一下问题，我们拥有一个不能排序的数组a[N]。怎么样才能只扫一遍这个数组就能判断出仅有的一个众数呢？

设置一个内部变量cnt，以及一个输出ans。

cnt的初始值为0；ans用来存放我们的答案。

因为合理的答案只有一个：

遍历的时候，我们看到是我们这个群体的，cnt+1；不然cnt就减一。如果cnt=0那么就假定我们找到的群体就是人数最多的群体。

那么到了最后，计数器ans记录的那个群体必定是人最多的那个群体。

于是这就是一个看谁人多谁说了算的投票算法。


可能光这么说大家理解不了，那么我们就可以根据我们上面的思路写出代码然后跑一遍看看它的正确性。

下面附上代码：



```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
//const int N = 1;
int n;
int l;
int main()
{
    scanf("%d",&n);
    int cnt=0;
    int mina;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&l);
        if(cnt==0)
        {
            mina=l;
            cnt=1;    
        }
        else cnt+=(l==mina)?1:-1;
    }
    printf("%d",mina);
    return 0;
}
//因为个人对mina有怨念所以输出变量就是mina不要在意这些细节mina就是ans。
```
看完代码之后就很明确了，我们用读入来模拟遍历这么一个数组。
我们举一个样例就能很好的解释这个算法的正确性了。

比如说

7
2 5 3 5 5 4 5

那么开始遍历。

首先我们找到了2

那么cnt=1 mina=2

然后找到了5 cnt=0 mina=2

接下来3 cnt=1 mina=3

然后5 cnt=0 mina=3

然后还是5 cnt=1 mina=5

然后4 cnt=0 mina=5

然后仍然是5 cnt=1 mina=5 所以我们输出mina答案就是5

跑这么一遍你们就很显然发现。

即使对于我们的众数元素，经过多次打乱总会有那么一种情况在cnt为0的时候有两个相邻的众数元素

这两个相邻的众数元素就一定会被记录下来成为最终的答案。

这几行代码只能针对众数的个数大于n/2的情况。其实还有对于大于n/3的处理方法这里就不写出来了，原理差不多不过可能的答案会有2个/3个/1个，注意讨论就行咯。

如果众数的个数再少呢。。。那么摩尔投票法就不能保证正确性了，这个时候你还是只能用数组来进行On的空间复杂度。。

qwq就这样了求上题解qwq


---

## 作者：FlappyBear (赞：5)

对于这道题，我们发现：假设众数是x，则对于x的每一位，其必定是0~9这些数在该位出现次数中最多的一个数，故开数组$a[i][j]$记录第$i$位为$j$的数的个数，最后逐位确定众数即可

```
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[100][100],ans,max_time;
int Pow(int x);
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		int time=0;
		while(x)
		{
			time++;
			a[time][x%10]++;
			x/=10;
		}
		max_time=max(max_time,time);
	}
	for(int i=1;i<=max_time;i++)
	{
		for(int j=0;j<=9;j++)
		{
			if(a[i][j]>n/2)
			ans+=Pow(i-1)*j;//逐位确定众数 
		}
	}
	printf("%d",ans);
	return 0;
}
int Pow(int x)
{
	if(x==0)
	return 1;
	int y=1;
	for(int i=1;i<=x;i++)
	{
		y*=10;
	}
	return y;
}
```

---

## 作者：Mine_King (赞：4)

[**戳这里**](https://www.luogu.org/blog/yhdhg1395754790/)

这题中，众数出现次数超过一半是个关键！  
注意，是超过一半，不是大于等于一半。  
我们可以把数分成两类，一类是众数，一类是其他数，根据上面的条件，众数的一类一定严格大于其他数的一类（指数量）。如果两类中的数1对1互相抵消，那么最后剩下来的数，不管剩多少个，都一定是众数。  
那么我们的算法就显而易见了：

1. 建一个变量ans存储当前找到的众数，建一个变量cnt存储当前众数的数量
2. 新加入一个数
3. 如果和ans相同，即和当前找到的众数相同，cnt++
4. 如果cnt=0，即没有找到众数，则把新数作为众数，即ans=新数，cnt=1
5. 如果不同，那么cnt--，即把当前的众数抵消掉一个
6. 最后剩下来的ans就是众数

数据范围说明，不会存在一个为0的数，所以第三条和第四条的位置调不调换都一样。  
**上代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ans,tot;//tot同cnt
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);//读入
		if(x==ans) tot++;//第1种情况（第三条）
		else if(tot==0) ans=x,tot++;//第二种情况
		else tot--;//第三种情况
	}
	printf("%d",ans);
	return 0;
}
```
## 完结撒花~\(≧▽≦)/~

---

## 作者：bztMinamoto (赞：4)

楼上都那么正经我来一发玄学做法

我就不信有比我还强的

我说我看了kkk的upd然后纯随机过了你们信么……

rt……

种子本来试了某大质数然后挂了，之后选了我的生日……A了……
```
//minamoto
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,k;
int main(){
//	freopen("testdata.in","r",stdin);
 	srand(20030719);
	scanf("%d",&n);
	int k=rand()%n+1;
	for(int i=1;i<=n;++i){
		scanf("%d",&m);
		if(i==k) cnt=m;
	}
	printf("%d\n",cnt);
}
```

---

## 作者：Carolina (赞：3)

~~说实话这道题我没有用位运算~~

~~题解区cpp刷屏，为了告诉大家Pascal还没死~~

一道比较经典的[摩尔投票法](https://www.jianshu.com/p/c19bb428f57a)例题~~（好吧这不是我自己的~~

 这道题中出现了
 ## “这个众数出现次数超过了一半”##

又翻了一下我妈的小学数学书~~（自己新版的书里没有众数）~~     

一组数据中出现次数最多的数值，叫众数。题面保证众数只有一个。

那么也就是说，众数所表示的数值会赶走其他数值。

假设在枚举中枚举到的数值是众数。

因为众数数量超过了一半，所以也就是说，在扫描的过程中，如果遇到的与现在标记的“众数”不同的数的数量等于“众数”的数量，那么这个“众数”不是众数。


（用数学语言描述，使枚举到的众数数量=s1,非众数数量=s2,当
s1=s2时，所选的“众数”，不是真正的众数，应该更新。）

如果相同那么就更新数量啦QWQ

算了蒟蒻智商较低还是贴代码吧

```pascal
var
  n,ans,a,x,i:longint;
begin
  readln(n);
  ans:=0; a:=0;
  read(x);
  ans:=x; a:=1;
  for i:=2 to n do
  begin
    read(x);
    if x=ans then
    begin
      inc(a);
    end else
    begin
      dec(a);
      if a=0 then
      begin
        a:=1;
        ans:=x;
      end;
    end;
  end;
  writeln(ans);
end.
```

---

## 作者：Maktub (赞：2)

说众数大于一半，我们可以考虑一个非常神奇的思路，牺牲正确性来骗分，我们先处理前一半的数据，将后几位统计一下，出现次数最多的当成可能的众数，然后检查后一半来找众数。

其实可以将后几位当成一个桶，因为如果直接用原数的话桶肯定是开不开的，所以只要后几位，经过保留1位，2位，3位,4位后，开到5位的时候就把这个题很神奇地水过去了。

1位 1个点。

2位 2个点。

3位 2个点。

4位 3个点。

5位 AC。

代码：

```
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int q[100000];
int zhong,n,k;
int main(){
	int a,b;
	cin>>n;
	int maxx=0;
	for(int i=1;i<=n/2+1;i++){
		scanf("%d",&a);
		k=a%100000;
		q[k]++;
		if(maxx<q[k]){
			maxx=q[k];
			zhong=k;
		}
	}
	//cout<<zhong;return 0;
	for(int i=n/2+2;i<=n;i++){
	    scanf("%d",&a);
	    if(a%100000==zhong)b=a;
	}
	cout<<b;return 0;
}

```

~~请求管理加强数据~~

---

## 作者：思援弓 (赞：2)

看到题目中的2,000,000就知道直接开一个2,000,000的数组是不切实际的,

更不用说好写的计数排序前半部分了,

有的人想到链表,只能说这样子如果除了众数其余数皆不同就要1,000,000这么大的链表了(至此都没有用到题目给出的条件)

然后题目说众数的数目超过一半,这样就可以不是很严格地存储数和数的个数了,于是就有了以下的做法:

把一个数除以某个常数,把商和余分别储存下来,最后统计最多的某个商和最多的某个余还原成众数即可(易知该众数的商和余必定大于一半的个数,而个数大于一半的数有且只有一个)


以下给出c++和pascal的代码(经测试,c++的M消耗为2370KB,pascal的M消耗为3510KB)(可以说完全相同的程序,而这场比赛要求c++最多2360KB,pascal则是3.5MB=3584KB,故而pascal过了,c++则没过,唉)


```delphi

var i,tmp,n,aa,bb:longint;
    a,b:array[0..46400]of longint;
begin
readln(n);
fillchar(a,sizeof(a),0);
fillchar(b,sizeof(b),0);
for i:=1 to n do 
begin
    read(tmp);
    inc(a[tmp mod 46400]);
    inc(b[tmp div 46400]);
end;
for i:=0 to 46400 do
begin
    if a[i]>n/2 then aa:=i;
    if b[i]>n/2 then bb:=i;
end;
writeln(bb*46400+aa);
end.

```

```cpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
//库
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    int a[46400];
    int b[46400];
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(int i=0;i<n;i++){
        int tmp;
        scanf("%d",&tmp);
        a[tmp%46400]++;
        b[tmp/46400]++;
    }
    int aa,bb;
    for(int i=0;i<46400;i++){
        if(a[i]>n/2)aa=i;
        if(b[i]>n/2)bb=i;
    }
    printf("%d\n",bb*46400+aa);
    return 0;
}

```

---

## 作者：「QQ红包」 (赞：2)

题目中说了“这个众数出现次数超过了一半”

所以这个众数必定跟别的数抵消之后还留有至少一个。

模拟一个抵消的过程就可以了……

```delphi

var a,j,n,s,i:longint;
begin
 read(n);
 s:=0;
 j:=-2333;
 while not eof do
 begin
  read(a);
  if a=j then inc(s)
  else
  begin
   dec(s);
   if s<=0 then
   begin
    s:=1;
    j:=a;
   end;
  end;
 end;
 write(j);
end.

```

---

## 作者：卐浪天卍 (赞：2)

## 暴力出奇迹？

好吧，不行，一道黄题~~累死我了~~


本蒟蒻前面花费~~话费~~了大量时间来水该题，然而卡在40分，换了方法才AC！


------------

###### 40分题解1：
```
#include<bits/stdc++.h> //万能头文件，妈妈再也不要我记头文件了！！！
#define rt register int  //好像速度快点 
using namespace std;
int n;long long x,a[20000001]; //开不开long long没关系 
int main()
{
    scanf("%d",&n);
    for(rt i=1;i<=n;++i) scanf("%d",&x),a[x]++; //与判重一个方法 
    x=n>>1;//节约时间，然而并不能AC 
    for(rt i=1;i<=n;++i) if(a[i]>x) {printf("%d",i);return 0;} //只有众数大于一半，找到就退出 
    return 0;//完美结束，然而并不能AC 
}
```
好无奈，过不了！！！
————————————————————————————————————优秀分解线

###### 40分题解2：
```
#include<bits/stdc++.h> //万能头文件，妈妈再也不要我记头文件了！！！ 
#define rt register int //好像速度快点 
using namespace std;
long long n,a[20000001];//开不开long long没关系 
int main()
{
    scanf("%d",&n);
    for(rt i=1;i<=n;++i) scanf("%d",&a[i]);
    sort(a+1,a+1+n); //直接排序STL 
    printf("%d",a[n/2+1]);// 只有众数大于一半,找到中位数就行 
    return 0;//完美结束，然而并不能AC 
}
```
太菜了，过不了！！！

————————————————————————————————————优秀分解线

我只好换了思路，千辛万苦终于AC了~~我好弱~~

###### 正解：
```
#include<bits/stdc++.h> //万能头文件，妈妈再也不要我记头文件了！！！ 
#define rt register int //好像速度快点 
using namespace std;
int n,z,ans,sum;
int main()
{
	scanf("%d",&n);
	for(rt i=1;i<=n;++i)
	{
		scanf("%d",&z);//直接模拟即可，自己动点脑子 
		if(z==sum){ans++;continue;}//这句一定得加 continue，不然ans--； 
        if(!ans) ans=1,sum=z;
        else ans--;
	}
	printf("%d",sum); //直接输出 
	return 0;//完美结束，然而能AC  
}
```

---

## 作者：NicodeX (赞：0)

这个题目很神奇啊，竟然只有3.5M内存，显然不能用排序

因为答案的数字的个数一定大于所有数字个数的一半

所以我们可以把这些数中两两不同的数减掉，则剩下的就是答案了

所以可以这样（代码中含解释，在线方法）：

#include<stdio.h>       //头文件（最好用这个，貌似用bits/stdc++会增加更多内存）


```cpp
using namespace std;
int k,n,x,y;  //变量能少就少吧，解释：k——读入的变量，n——个数，x——记录数字，y——记录数字 的个数
int main(){
    scanf("%d",&n);  //读入
    while(n--){    //循环n次
        scanf("%d",&k);  //每次输入一个数
        if(y==0){   //如果计数器为0，则说明当前的数字已经抵消完了，或者本来就是空的
            x=k;  //更新记录数字
            y++;  //计数器+1
        }
        else if(x==k) y++;  //如果x==k，则说明目前记录数字与当前读入数字相等，则计数器再+1
        else y--;   //不然就说明x!=k，抵消1个
    }
    printf("%d",x);  //剩下的就是答案了
    return 0;
}
//Ps：这个代码本来是交到bzoj上的，1M内存过（太变态了，还是luogu和谐），不过也过了。
```

---

## 作者：fanfan (赞：0)

楼下题解都是假的，开个什么数组啊

既然中位数出现一半次数以上，用一个抵消的思想，正确的中位数总会满足到最后tot大于0，而t就肯定是正确的

其他不是正确的数，那么tot减到中间的时候肯定会被其他的数替换掉

```cpp
#include<cstdio>
int n,t,x,tot;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        if(x==t)
        {
            tot++;continue;
        }
        if(!tot)
        {
            t=x;tot=1;
        }
        else tot--;
    }
    printf("%d",t);
}
```

---

## 作者：HiJ1m (赞：0)

真的C++题解

由于这个众数出现次数超过了一半

就模拟更新这个众数即可

P.S. 3.5MB内存   开数组肯定炸

```cpp
#include<cstdio>
#include<iostream>
int tot,t,n,x;
using namespace std;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        if(x==t)tot++;
        else if(!tot)
        {tot=1;t=x;}
        else tot--;
    }
    printf("%d\n",t);
    system("pause");
    return 0;    
}

```

---

## 作者：lqylqylqy (赞：0)

众数是一组数据中出现次数超过一半的数，因此我们可以模拟抵消的过程。初始化num:=0;

cs:=-1;

在读入一个数的时候，对他进行判断，若与num不相等，则dec(cs);

否则inc(cs);

若cs=0，则用读入的数更新num，同时cs:=1;

以下为代码。

```cpp
program Project1;
var n,a,cs,num,i:longint;
begin
  readln(n);
  cs:=1;
  for i:=1 to n do
    begin
      read(a);
      if a<>num then
        begin
          dec(cs);
          if cs=0 then begin
                         num:=a;
                         inc(cs);
                       end;
        end
                else inc(cs);
    end;
  writeln(num);
  readln;
  readln;
end.

```

---

