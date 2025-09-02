# [USACO2.2] 序言页码 Preface Numbering

## 题目描述

给定 $n$，求 $1 \sim n$ 的 **罗马数字** 表示中，各个字符出现了多少次。

比如 $n = 5$，表示为  I, II, III, IV, V。总共有 $7$ 个 I 出现，$2$ 个 V 出现。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 3500$。

翻译来自NOCOW

USACO 2.2


## 样例 #1

### 输入

```
5
```

### 输出

```
I 7
V 2```

# 题解

## 作者：dph754132771 (赞：16)

/\*
\* P:1465

\* Au:Small\_Ash

\* 本题本人采用的是一个罗马数字的快速生成法...(自己随便取的,[一本正经的胡说八道])

\* 首先,我们需要一个表(可以手推,别问我为什么怎么清楚)

\* 1 I
\* 4 IV
\* 5 V
\* 9 IX
\* 10 X
\* 40 XL

\* 50 L
\* 90 XC

\* 100 C

\* 400 CD

\* 500 D

\* 900 CM

\* 1000 M

\* (没错,就是1,4,5,9及其全部的10^n次方倍[然而罗马数字最大到3500])

\* 为什么要这个表呢,规律我不会证(都说是我乱想想出来的),但是确实可以用

\* 比如一个数 2333 大于1000 2倍 所以是 MM

\* 余数 333 大于100 3倍 所以是CCC

\* 余数 33 大于10 3倍 所以是XXX

\* 余数 3 大于1 3倍 所以是III

\* 所以2333=MMCCCXXXIII (我真的乱选的,不是正好这么奇怪)

\* 又比如 834->334->34->4->0

\*          500  100 10  4

\*           D   CCC XXX IV

\* 所以是DCCCXXXIV,所以,利用这个表,我们就能快速求出一个罗马数字的字母个数,然后再累加就行了

\* 下面是代码.

\*/
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n;
int i[20],v[20],x[20],l[20],c[20],d[20],m[20],A[20];
int ansi,ansv,ansx,ansl,ansc,ansd,ansm;
void mem(){
    A[1]=1;i[1]=1;
    A[2]=4;i[2]=1;v[2]=1;
    A[3]=5;v[3]=1;
    A[4]=9;i[4]=1;x[4]=1;
    A[5]=10;x[5]=1;
    A[6]=40;x[6]=1;l[6]=1;
    A[7]=50;l[7]=1;
    A[8]=90;x[8]=1;c[8]=1;
    A[9]=100;c[9]=1;
    A[10]=400;c[10]=1;d[10]=1;
    A[11]=500;d[11]=1;
    A[12]=900;c[12]=1;m[12]=1;
    A[13]=1000;m[13]=1;
}
void add(int b,int num){
    ansi+=i[b]*num;
    ansv+=v[b]*num;
    ansx+=x[b]*num;
    ansl+=l[b]*num;
    ansc+=c[b]*num;
    ansd+=d[b]*num;
    ansm+=m[b]*num;
    return;
}
int main()
{
    scanf("%d",&n);
    mem();
    for (int j=1;j<=n;j++){
        int temp=j,now=13;
        while (temp){
            while (temp<A[now]) now--;
            add(now,temp/A[now]);
            temp%=A[now];
        }
    }
    if (ansi!=0) printf("I %d\n",ansi);
    if (ansv!=0) printf("V %d\n",ansv);
    if (ansx!=0) printf("X %d\n",ansx);
    if (ansl!=0) printf("L %d\n",ansl);
    if (ansc!=0) printf("C %d\n",ansc);
    if (ansd!=0) printf("D %d\n",ansd);
    if (ansm!=0) printf("M %d\n",ansm);
    return 0;
}

```

---

## 作者：RiverHamster (赞：12)

楼下的打表不太好理解，来一发好写又好理解的打表方法。

[推荐使用此Markdown链接，获取更好的阅读效果，获取完整代码](https://www.zybuluo.com/RiverHamster/note/953278)

##罗马数字的构造方法：

**每一位之间没有关系，可以分别处理，直接把千位、百位、十位、个位按顺序放就可以。0直接跳过**

例如：123：CXXIII

每一位上的数字的表示方法：

**“表示方法”列中以个位为例，1=I，5=V，10=X，n表示这一位上的数字，十位百位以此类推。**

|类别|表示方法|示例1|示例2|
|:--:|:------:|:---:|:---:|
|1~3 |n个I    |2=II|30=LLL|
|4   |IV      |4=IV    |400=CD |
|5~8 |V和(n-5)个I     |5=V|70=LXX|
|9   |IX     |9=IX|900=CM|
##打表关键代码

s[i][j]表示右数第i位（个位i=1）上的j的表示方法，注意数组赋初值的格式。

```cpp
string s[5][11]={ //注意每一位上的0都给出空字符串，方便操作
    {},    //空出第0行
    {"","I","II","III","IV","V","VI","VII","VIII","IX"}, //个位
    {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"}, //十位
    {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"}, //百位
    {"","M","MM","MMM"}  //千位（打3个就可以满足题目要求）
};
```
对每一个数进行计数：（uint是unsigned int）

```cpp
void Calc(int n){
    int now=1; //当前的数位
    while(n>0){
        Count(s[now][n%10]); //将字符串计数
        now++,n/=10;         //下一位
    }
}
```
[完整代码请访问Markdown链接](https://www.zybuluo.com/RiverHamster/note/953278)


---

## 作者：Sino_E (赞：8)

考虑每个十进制数每位对罗马数字出现次数互相独立，那么就可以独立算。

考虑个位和十位和百位的一些共同点，如4为IV，而40为XL，可以发现在每个位，能够产生贡献的罗马数字都不同。如个位是IVX，十位是XLC。

再考虑每位数字能够产生的贡献具体数值。

打表枚举即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int id[][3]={{1, 2, 3}, {3, 4 ,5}, {5, 6 ,7}, {7, 0, 0}};
int cnt[10];
char str[]=" IVXLCDM";
int w[][3]={{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, // 0~4
                       {1, 1, 0}, {0, 1, 0}, {1, 1, 0}, {2, 1, 0}, {3, 1, 0}, // 5~8
                       {1, 0, 1}}; // 9

void add(int x) {
    for(int i=0;x;i++, x/=10) {
        int j=x%10;
        for(int k=0;k<3;k++)
            cnt[id[i][k]]+=w[j][k];
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) add(i);
    for(int i=1;i<=7;i++)
        if(cnt[i]) cout<<str[i]<<' '<<cnt[i]<<endl;
    return 0;
}

```

---

## 作者：Magi_karp (赞：7)

只有我不是暴力做的嘛……

纯自创的递推解法，也可以说是

##数位dp

时间复杂度O(十进制的位数×给定的罗马字母数）

觉得还是很难理解的

但是写出来对数位dp的水平提升很有帮助啊

首要依据就是：

#罗马表示法中的个位、十位、百位……都具有独立性

就是说不管是3456还是4456还是5456后面的456表示都是一样的

下面的f数组，f[i][j]表示在0~10^i-1里面第j位罗马字母的出现次数

a数组是预处理啦，a[i][j]表示个位数字i的表示里第j个罗马字母的次数

由于0~9的罗马表示里面只有I,V,X，所以只开了三个单位

```cpp
#include<cstdio>
using namespace std;
int f[4][9],ans[9],n;
int a[10][3]={{0,0,0},{1,0,0},{2,0,0},{3,0,0},{1,1,0},{0,1,0},{1,1,0},{2,1,0},{3,1,0},{1,0,1}};
char c[10]={"0IVXLCDM"}; //前面那个0是占位用的
int pw(int k)//实际上是10^(k-1)
{
        int ans=1;
    for (int i=1;i<k;i++)
        ans*=10;
    return ans;
}
int main()
{
    for (int i=1;i<=3;i++)//预处理出f
    {//比如0~99可以拆成在个位0~9各十个和在十位的0~9各一个
        for (int k=1;k<=7;k++)//“在个位0~9各十个”，而个位0~9各一个的和是上一次算的f[i-1]
            f[i][k]=10*f[i-1][k];
        for (int j=0;j<=9;j++)//“在十位的0~9各一个”
            for (int k=i*2-1,w=0;w<3;k++,w++)//k为什么是2*i-1呢……？能想通就好，想不通就待定系数法解吧^.^
                f[i][k]+=a[j][w]*pw(i);
    }
    scanf("%d",&n);
    for (int i=3,j=1000;i>=1;i--,j/=10)//因为n最大3000多没有上万，所以最大单位为千
        if (n>=j)
        {
            int sa=n/j,sb=n%j;//十进制里第i位是sa，剩下的余数是sb（不要吐槽这个名字……）
         /*还是举例子比如n=2451吧，一共有sa=2次完整的0~999的循环（这句话中忽略千位）和剩下的451*/
            for (int k=1;k<=7;k++)//sa=2次完整的0~999的循环
                ans[k]+=f[i][k]*sa;//每个罗马字母都要计数（不可以写什么2*i+1啥的！每一位都要记！）
            for (int e=1;e<sa;e++)//0~999的循环时之前忽略的千位每位要加1000遍；e应该从0开始但是因为0啥也没有就扔了
                for (int k=i*2+1,w=0;w<3;w++,k++)
                    ans[k]+=a[e][w]*j;
            for (int k=i*2+1,w=0;w<3;w++,k++)//剩下的451前面的千位数是sa
                ans[k]+=a[sa][w]*(sb+1);//sb要加一是因为0~sb有sb+1个数，每个数都有千位数sa
            n=sb;//n的千位都搞定了就可以扔掉啦
        }
    for (int i=1;i<=n;i++)//到这里的时候n应该已经<10了
        for (int j=1;j<=3;j++)//完全用a数组枚举就可以
            ans[j]+=a[i][j-1];
    for (int i=1;i<=7;i++)
        if (ans[i])
            printf("%c %d\n",c[i],ans[i]);
}
```
（这里的+1-1都特别混乱……想不通就用待定系数法解吧，代两个值解二元一次组就好……)

（（如果待定系数不太明白再私信叭(-^〇^-)））


---

## 作者：ABCDXYZ (赞：4)

无聊来一发<<map>>(简便了一点，就算练练吧)


很容易发现每个数位上的数字出现都是有规律的（例如对于8=VIII 与 80=LXXX 与 800=DCCC）


另外，各个数位上的数字不会互相影响，所以只要简单地模拟一下就行了


```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>//完美的头文件
using namespace std;
map<char,int>mp;
int n;
void get_char_num(int x){
    int cnt=0;
    while(x>0){
        cnt++;char c1,c2,c3;
        if(cnt==1)//个位时 
            c1='I',c2='V',c3='X';
        else if(cnt==2)//十位时 
            c1='X',c2='L',c3='C';
        else if(cnt==3)//百位时 
            c1='C',c2='D',c3='M';
        else 
            c1='M';//千位时 
        int p=x%10;
        if(p<=3)mp[c1]+=p;
        else if(p==4)mp[c1]++,mp[c2]++;
        else if(p>=5 && p<=8)mp[c1]+=p-5,mp[c2]++;
        else if(p==9)mp[c1]++,mp[c3]++;
        x/=10;
    }
}
int main( ){
    int m,n,j,k,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        get_char_num(i);    
    }
    if(mp['I'])printf("I %d\n",mp['I']);
    if(mp['V'])printf("V %d\n",mp['V']);
    if(mp['X'])printf("X %d\n",mp['X']);
    if(mp['L'])printf("L %d\n",mp['L']);
    if(mp['C'])printf("C %d\n",mp['C']);
    if(mp['D'])printf("D %d\n",mp['D']);
    if(mp['M'])printf("M %d\n",mp['M']);
    return 0;
}
逃））
```

---

## 作者：nbqdd_2003 (赞：4)

[/color][codep ]

```cpp
var
  i,v,x,l,c,d,m,n,k,rp:longint;//i,v,x,l,c,d,m分别记录各自出现的次数
begin
  i:=0;
  v:=0;
  x:=0;
  c:=0;
  d:=0;//初始化
  readln(n);//读入n
  for rp:=1 to n do//枚举1-n所有的数字
    begin
      k:=rp;//将rp的值赋给k，方便下一步计算
      while k>0 do//当k还大于0时循环
        begin
          if k>=1000 then begin k:=k-1000;m:=m+1;end;//就利用的上面所说的规律
          if (k<1000) and (k>=900) then begin k:=k-900;m:=m+1;c:=c+1;end;
          if (k<900) and(k>=500) then begin k:=k-500;d:=d+1;end;
          if (k<500) and (k>=400) then begin k:=k-400;d:=d+1;c:=c+1;end;
          if (k<400) and (k>=100) then begin k:=k-100;c:=c+1;end;
          if (k<100) and (k>=90) then begin k:=k-90;x:=x+1;c:=c+1;end;
          if (k<90) and (k>=50) then begin k:=k-50;l:=l+1;end;
          if (k<50) and (k>=40) then begin k:=k-40;l:=l+1;x:=x+1;end;
          if (k<40) and (k>=10) then begin k:=k-10;x:=x+1;end;
          if (k<10) and (k>=9) then begin k:=k-9;i:=i+1;x:=x+1;end;
          if (k<9) and (k>=5)then begin k:=k-5;v:=v+1;end;
          if (k<5) and (k>=4) then begin k:=k-4;i:=i+1;v:=v+1;end;
          if (k<4)and(k>=1) then begin i:=i+1;k:=k-1;end;
        end;
    end;
  if i<>0 then writeln('I ',i);//输出结果
  if v<>0 then writeln('V ',v);
  if x<>0 then writeln('X ',x);
  if l<>0 then writeln('L ',l);
  if c<>0 then writeln('C ',c);
  if d<>0 then writeln('D ',d);
  if m<>0 then writeln('M ',m);
end.
[/codep ]
```

---

## 作者：陈晋衍 (赞：4)


这道题要求我们把十进制阿拉伯数字转成罗马数字

对着题目看了半天，我才发现罗马数字其实是有规律的。

### 罗马数字的十进制每一位都各自独立！

换句话说，你可以把罗马数字当成十进制数字，但个个位都被换成了其他的数字。

比如：

| 阿拉伯数字 | 罗马数字 |
| :----------: | :----------: |
| 1 |  I|
| 2 | II |
|3|III|
|4|IV|
|5|V|
|6|VI|
|9|IX|
|10|X|
|14|XIV|
|99|XCIX|
|100|C|
|999|CMXCIX|
就是这样

拿999距离，他不是IC，而是CMXCIX。

翻译成人话就是

|百位|十位|个位|
|:---:|:---:|:----:|
|CM|XC|IX|
|900|90|9|

所以在代码里，要把各个位分开处理。

```
#include<iostream>
using namespace std;
int a[1001];
void kkk(int x)//处理函数
{
	if(x/1000!=0)//处理千位
	{
		a['M']+=x/1000;
	}
	if(x%1000/100!=0)//百位
	{
		int t=x%1000/100;
		if(t==9)//9要特殊处理
		{
        //他是上一位的1减去这一位的1
			a['C']++;
			a['M']++;
		}
		else if(t>=5)//这一位的5加上这一位的1
		{
			a['D']++;
			a['C']+=t-5;
		}
		else if(t==4)//4也要特殊处理
       	//这一位的5减去这一位的1
		{
			a['C']++;
			a['D']++;
		}
		else {//全是这一位的1
			a['C']+=t;
		}
	}
    //其他几位同上
	if(x%100/10!=0)//十位
	{
		int t=x%100/10;
		if(t==9)
		{
			a['X']++;
			a['C']++;
		}
		else if(t>=5)
		{
			a['L']++;
			a['X']+=t-5;
		}
		else if(t==4)
		{
			a['X']++;
			a['L']++;
		}
		else {
			a['X']+=t;
		}
	}
	if(x%10!=0)//个位
	{
		int t=x%10;
		if(t==9)
		{
			a['I']++;
			a['X']++;
		}
		else if(t>=5)
		{
			a['V']++;
			a['I']+=t-5;
		}
		else if(t==4)
		{
			a['I']++;
			a['V']++;
		}
		else {
			a['I']+=t;
		}
	}
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)//从1到n
	{
		kkk(i);//转换
	}
    //输出
	if(a['I']!=0)cout<<'I'<<" "<<a['I']<<endl;
	if(a['V']!=0)cout<<'V'<<" "<<a['V']<<endl;
	if(a['X']!=0)cout<<'X'<<" "<<a['X']<<endl;
	if(a['L']!=0)cout<<'L'<<" "<<a['L']<<endl;
	if(a['C']!=0)cout<<'C'<<" "<<a['C']<<endl;
	if(a['D']!=0)cout<<'D'<<" "<<a['D']<<endl;
	if(a['M']!=0)cout<<'M'<<" "<<a['M']<<endl;
	return 0;
}
```

---

## 作者：VCVCVCFop_zz (赞：3)

暴力模拟。。没什么可以优化的，唯一可以优化的只有代码复杂度..

计数时可以做一些规律而不是按顺序IVX..

5开头的分在一类，1开头的分在一类

这样做的时候只需要分为9和4和其他三类，代码大大缩短

CODE：


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int cnt[10];
inline void doit(int x)
{
    int t=0;
    while(x)
    {
        t++;
        int tmp=x%10;
        if(tmp==9)
        {
            cnt[t+4]++;
            cnt[t+3]++;    
        }else
        {
        if(tmp>=5)
        {
            cnt[t]++;
            tmp-=5;
        }
        if(tmp==4)    
        {
            cnt[t]++;
            cnt[t+3]++;
        }else
        cnt[t+3]+=tmp;
        }
        x/=10;
    }
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        doit(i);
    if(cnt[4])    printf("I %d\n",cnt[4]);
    if(cnt[1])    printf("V %d\n",cnt[1]);
    if(cnt[5])    printf("X %d\n",cnt[5]);
    if(cnt[2])    printf("L %d\n",cnt[2]);
    if(cnt[6])    printf("C %d\n",cnt[6]);
    if(cnt[3])    printf("D %d\n",cnt[3]);
    if(cnt[7])    printf("M %d\n",cnt[7]);
}
```

---

## 作者：Celebrate (赞：2)

对于每个数字计算罗马字母的个数的过程吧。可以手推下，其实也很简单。

我是把数一位一位模过去判断的。

若数还大于1000就算一下相应的字母个数，然后数%1000。

若数还大于100就算一下相应的字母个数，然后数%100。

若数还大于10就算一下相应的字母个数，然后数%10。

若数还大于1就算一下相应的字母个数，然后没了。

代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const char f[7]={'I','V','X','L','C','D','M'};
int a[7];
inline void lookfor(int k)//模拟算转成罗马字母后的相应字母的增加个数
{
	int t;
	//这些东西都没有什么难度 
	if(k/1000>0)
	{
		a[6]+=k/1000;
		k%=1000;
	}
	if(k/100>0)
	{
		t=k/100;
		if(t<4) a[4]+=t;
		if(t==4) a[5]++,a[4]++;
		if(t>=5 && t<9) a[5]++,a[4]+=t-5;
		if(t==9) a[4]++,a[6]++;
		k%=100;
	}
	if(k/10>0)
	{
		t=k/10;
		if(t<4)a[2]+=t;
		if(t==4)a[3]++,a[2]++;
		if(t>=5 && t<9)a[3]++,a[2]+=t-5;
		if(t==9)a[2]++,a[4]++;
		k%=10;
	}
	if(k>0)
	{
		t=k;
		if(t<4)a[0]+=t;
		if(t==4)a[1]++,a[0]++;
		if(t>=5 && t<9)a[1]++,a[0]+=t-5;
		if(t==9)a[0]++,a[2]++;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) lookfor(i);//枚举大法
	for(int i=0;i<7;i++) if(a[i]>0) printf("%c %d\n",f[i],a[i]);//输出 
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)

题解by:redbag

原题地址：http://www.luogu.org/problem/show?pid=1465

http://train.usaco.org/usacoprob2?a=1pqwef1HnE6&S=preface

AC记录：http://www.luogu.org/record/show?rid=781721

原题解地址：http://redbag.duapp.com/?p=1188

我的小屋：http://redbag.duapp.com

欢迎来踩！

其实，这题只要读懂题，

而且不要怕麻烦，就能AC？打表是正解？

总的来说，还是

######**暴力出奇迹**

```cpp
#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#define LL unsigned long long   
using namespace std;
char c[31][5]={
```
" ","I","II","III","IV","V","VI","VII","VIII","IX","X",
"XX","XXX","XL","L","LX","LXX","LXXX","XC","C","CC",

```cpp
"CCC","CD","D","DC","DCC","DCCC","CM","M","MM","MMM"};
int num[31]={0,1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,
80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000};//每个字母对应的数字
int n;
int a[26];//26个字母，大雾，其实是存那几个字母的数量
void find(int nn)//nn转成罗马数字然后统计？ 
{
    int j=30;
    char s[30];
    while (num[j]>nn) j--;//找到第一个<=n的数 
    for (;j>=1;j--)
    {
        if (nn>=num[j])//如果nn比这个数大或者等于这个数
```
{/\*其实是不用担心40被强行分成XXX和X的，因为40在表中\*/
     
```cpp
            nn-=num[j];//减掉 
            for (int x=0;x<strlen(c[j]);x++)//统计各个字母的个数 
            a[int(c[j][x])-65]++; 
        } 
        if (nn==0) return; //节约时间。已经搜完了 
    }
} 
int main() 
{
    freopen("preface.in","r",stdin);
    freopen("preface.out","w",stdout); 
    scanf("%d",&n);//读入 
    for (int i=1;i<=n;i++) 
    find(i);
    //输出，因为是按照这个顺序所以我找不到什么好办法输出了 
    if (a[int('I')-65]!=0) printf("I %d\n",a[int('I')-65]);
    if (a[int('V')-65]!=0) printf("V %d\n",a[int('V')-65]);
    if (a[int('X')-65]!=0) printf("X %d\n",a[int('X')-65]);
    if (a[int('L')-65]!=0) printf("L %d\n",a[int('L')-65]);
    if (a[int('C')-65]!=0) printf("C %d\n",a[int('C')-65]);
    if (a[int('D')-65]!=0) printf("D %d\n",a[int('D')-65]);
    if (a[int('M')-65]!=0) printf("M %d\n",a[int('M')-65]);
    return 0;
}
祝你好运。
```

---

## 作者：LYFer (赞：1)

1 A
2 AA
3 AAA
4 AB
5 B
6 BA
7 BAA
8 BAAA
9 AC
无论个位十位百位千位 上面的数字总是会出现这样的规律

那么这道题就是暴力模拟题目~


举个例子

255 CC L    V

268 CC LX   VIII

278 CC LXX  VIII

289 CC LXXX IX

299 CC XC   IX

发现了规律了没有？

9是一类 4是一类 5-8一类 1-3一类 那么思路就出现了

先判断个位上面的数 如果是九 那么一定是IX 这时有个问题就是不能直接 ans[1]++ ans[3]++ 因为十位上的9就是XC了

所以要加个 t 作为标志值 判断是在个位(t=1)还是十位(t=2)还是百位(t=3)还是千位(t=4)（暂时看不懂继续往下看）


先讨论下  （假设数组大小为7 当然你可以100 200）

5的情况:  个位是5 那么一定是V

十位是5 那么一定是L

百位是5 那么一定是D

在没有千位是5的情况下，V L D 只会在是5的情况出现 其余都不可能（多写几个数字去看）

所以 个位的5 就是 num[1] 十位的5就是num[2] 百位的5就是num[3]  即num[t]  当然你也可以写num[t+100] num[t+200] 只要没有矛盾情况随便写


9的情况: 个位是9 那么一定是IX

十位是9 那么是 XC

百位是9 那么是 CM

这里只剩下 4 5 6 7可以取  这里为了方便 因为 IX XC CM 是相邻的两个数 所以 num[t+3] num[t+4]

这里看一下 因为个位9 囊括了 I 所以I就是num[t+3] t=1  I就是num[4]

当然你也可以num[t+6] num[t+7] 这些都无所谓 只要不与前面的num矛盾随便你怎么取

 
4的情况: 个位4 IV

十位4 XL

百位4 CD

因为 4的情况就是 5-1 50-10 500-100

5 50 500 已经确定  1 10 100也已经确定填上就OK了


其余的 1 2 3 6 7 8 这些情况

直接 num[t+3]+= 情况

比如 个位的3 III num[4]+=3  十位的三 XXX num[5]+=3  百位的三 CCC num[6]+=3  千位的三 MMM num[7]+=3


终于讲完了  好累~ 如果还没有听懂 欢迎私信我


---

## 作者：syfufo (赞：1)

//我表示这道题标算确实是打表，只需要按照从大到小的顺序考虑1000,900，500,400,100，90,50,40,10,9,5,4,1即可，如果想太多就走偏了。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 4096
int n;
int hx[MAXN];
void input(){
    cin>>n;
}
void sz(int x){
    if(x>=1000){
        int g=0;
        for(int i=1;i<4;++i){
            if(i*1000>x) break;
            g=i;
        }
        hx[7]+=g;
        x-=g*1000;
    }
    if(x>=900){
        x-=900;
        hx[7]++;
        hx[5]++;
    }
    if(x>=500){
        x-=500;
        hx[6]++;
    }
    if(x>=400){
        x-=400;
        hx[5]++;
        hx[6]++;
    }
    if(x>=100){
        int g=0;
        for(int i=1;i<4;++i){
            if(i*100>x) break;
            g=i;
        }
        hx[5]+=g;
        x-=g*100;
    }
    if(x>=90){
        x-=90;
        hx[5]++;
        hx[3]++;
    }
    if(x>=50){
        x-=50;
        hx[4]++;
    }
    if(x>=40){
        x-=40;
        hx[4]++;
        hx[3]++;
    }
    if(x>=10){
        int g=0;
        for(int i=0;i<4;++i){
            if(i*10>x) break;
            g=i;
        }
        hx[3]+=g;
        x-=g*10;
    }
    if(x>=9){
        x-=9;
        hx[1]++;
        hx[3]++;
    }
    if(x>=5){
        x-=5;
        hx[2]++;
    }
    if(x>=4){
        x-=4;
        hx[2]++;
        hx[1]++;
    }
    if(x>=1){
        int g=0;
        for(int i=1;i<4;++i){
            if(i>x) break;
            g=i;
        }
        hx[1]+=g;
        x-=g;
    }
}
void syf(){
    for(int i=1;i<=n;++i){
        sz(i);
    }
    if(hx[1]!=0) cout<<"I"<<" "<<hx[1]<<endl;
    if(hx[2]!=0) cout<<"V"<<" "<<hx[2]<<endl;
    if(hx[3]!=0) cout<<"X"<<" "<<hx[3]<<endl;
    if(hx[4]!=0) cout<<"L"<<" "<<hx[4]<<endl;
    if(hx[5]!=0) cout<<"C"<<" "<<hx[5]<<endl;
    if(hx[6]!=0) cout<<"D"<<" "<<hx[6]<<endl;
    if(hx[7]!=0) cout<<"M"<<" "<<hx[7]<<endl;
}
int main(){
    input();
    syf();
    return 0;
}
```

---

## 作者：九指客 (赞：1)

```cpp
//枚举得我手都残了
#include<stdio.h>//头文件
int i,v,x,l,c,d,m,n,k,rp;//变量
int main()
{
    i=0;v=0;x=0;c=0;d=0;
      scanf("%d",&n);//输入
      for(rp=1;rp<=n;rp++)
      {
          k=rp;//枚举
          while(k>0)//疯狂的判断
          {
              if(k>=1000)//一堆的累和；
            {
                  k=k-1000;
                m=m+1;
            }
            else if(k<1000&&k>=900)
            {
                k=k-900;
                m=m+1;
                c=c+1;
            }
            else if(k<900&&k>=500)
            {
                k=k-500;
                d=d+1;
            }
              else if(k<500&&k>=400)
            {
                  k=k-400;
                d=d+1;
                c=c+1;
            }
              else if(k<400&&k>=100)
            {
                  k=k-100;
                c=c+1;
            }
              else if(k<100&&k>=90)
            {
                  k=k-90;
                x=x+1;
                c=c+1;
            }
              else if(k<90&&k>=50)
            {
                  k=k-50;
                l=l+1;
            }
              else if(k<50&&k>=40)
            {
                k=k-40;
                l=l+1;
                x=x+1;
            }
              else if(k<40&&k>=10)
            {
                k=k-10;
                x=x+1;
            }
              else if(k<10&&k>=9)
            {
                  k=k-9;
                i=i+1;
                x=x+1;
            }
              else if(k<9&&k>=5)
            {
                k=k-5;
                v=v+1;
            }
              else if(k<5&&k>=4)
            {
                  k=k-4;
                i=i+1;
                v=v+1;
            }
              else if(k<4&&k>=1)
            {
                i=i+1;
                k=k-1;
            }
          }
      }
      if(i>0)printf("I %d\n",i);//判断是否输出
      if(v>0)printf("V %d\n",v);
    if(x>0)printf("X %d\n",x);
    if(l>0)printf("L %d\n",l);
    if(c>0)printf("C %d\n",c);
    if(d>0)printf("D %d\n",d);
    if(m>0)printf("M %d\n",m);
    return 0;//结束
}
```

---

## 作者：fy0123 (赞：1)

暴力枚举，模拟= =（貌似没什么好说的）


说一下对于每个数字计算罗马字母的个数的过程吧。可以手推下，其实也很简单。

我是把数一位一位模过去判断的。

1. 若数还大于1000就算一下相应的字母个数，然后数%1000。

2. 若数还大于100就算一下相应的字母个数，然后数%100。

3. 若数还大于10就算一下相应的字母个数，然后数%10。

4. 若数还大于1就算一下相应的字母个数，然后没了。

算个数的过程还需仔细考虑一下下，就没啦~~


然后就枚举1~n累加一下就完成了。


代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
 
const char c[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int ans[7];
 
void count(int k)   //模拟算转成罗马字母后的相应字母的增加个数
{
    if (k / 1000 > 0){
        ans[6] += k / 1000;
        k %= 1000;
    }
    if (k / 100 > 0){
        int t = k / 100;
        if (t < 4) ans[4] += t;
        if (t == 4) ans[5] ++, ans[4] ++;
        if (t >= 5 && t < 9) ans[5] ++, ans[4] += t - 5;
        if (t == 9) ans[4] ++, ans[6] ++;
        k %= 100;
    }
    if (k / 10 > 0){
        int t = k / 10;
        if (t < 4) ans[2] += t;
        if (t == 4) ans[3] ++, ans[2] ++;
        if (t >= 5 && t < 9) ans[3] ++, ans[2] += t - 5;
        if (t == 9) ans[2] ++, ans[4] ++;
        k %= 10;
    }
    if (k > 0){
        int t = k;
        if (t < 4) ans[0] += t;
        if (t == 4) ans[1] ++, ans[0] ++;
        if (t >= 5 && t < 9) ans[1] ++, ans[0] += t - 5;
        if (t == 9) ans[0] ++, ans[2] ++;
    }
}
 
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) count(i);   //枚举大法
    for (int i = 0; i < 7; i ++)
        if (ans[i]) printf("%c %d\n", c[i], ans[i]);
    return 0;
}
```

---

## 作者：Hilda_2022 (赞：0)

//就把罗马数字当成十进制做
```c
#include<bits/stdc++.h>
using namespace std;
//1对应A，2对应AA，3对应AAA，4对应AB，
//5对应B，6对应BA，7对应BAA，8对应BAAA，9对应AC。
//个位 I V X 
//十位 X L C 
//百位 C D M 
//千位 M 
//字母 A B C 
string a1[10]={"","A","AA","AAA","AB","B","BA","BAA","BAAA","AC"};
int a2[10]={0,1,2,3,2,1,2,3,4,2};//位数 
string b[3]={"IXCM","VLD","XCM"};//ABC对应的数
//I 1 V 5 X 10 L 50 C 100 D 500 M 1000
char c[8]={' ','I','V','X','L','C','D','M'};
map<char,int> m;
void num(int x){
	int sum=0,w=0;
	while(x){
		string s=a1[x%10];
		for(int i=0;i<a2[x%10];i++){
			string s2=b[s[i]-'A'];
			m[s2[w]]++;
		}
		x/=10;w++;
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		num(i);
	for(int i=1;i<=7;i++)
		if(m[c[i]])
			printf("%c %d\n",c[i],m[c[i]]);
	return 0;
}
```

---

## 作者：wayne_lee (赞：0)

这道题其实也不难啦。。

可以发现，对于一个一位数，他最多涉及三个字母，而且也就0-9这十个数所以我们手动附上值就好了

而这毕竟不是万全之策，对于那些两位及以上的数，我么就不能手动搞了。。

但是！！！我们发现，对于两位及以上的数，是可以拆成一个个一位数来看的（自己手玩一下）。

所以对于每一个数字，先把上一个数字的字母组成加上，再按位来添加字母。而对于第i位数（从右往左）它会用到[（i-1）\*2，（i-1）\*2+2]

这几个字母（即每多一位数就往后偏两个字母），所以我们用一个变量来控制当前位置，就可以把多位数分成一位数操作了！

顺带放上前二十的数字：

I  II  III  IV  V  VI  VII  VIII  IX  X

XI  XII  XIII  XIV  XV  XVI  XVII  XVIII  XIX  XX


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int dp[4000][7],shu[10][3];
int n;
char sz[7];
void set()
{
      shu[1][0]=1;
      shu[2][0]=2;
      shu[3][0]=3;
      shu[4][0]=1;
      shu[4][1]=1;
      shu[5][1]=1;
      shu[6][0]=1;
      shu[6][1]=1;
      shu[7][0]=2;
      shu[7][1]=1;
      shu[8][0]=3;
      shu[8][1]=1;
      shu[9][0]=1;
      shu[9][2]=1;
      sz[0]='I';  sz[1]='V';  sz[2]='X';  sz[3]='L';  sz[4]='C';  sz[5]='D';  sz[6]='M';
}
void work1(int i)
{
      for(int j=0;j<=7;j++)
          {
                if(!dp[i-1][j])
                 break;
                dp[i][j]=dp[i-1][j];
          }
}
void work2(int i)
{
       int sum,sum1,sum2;
       sum1=i;
           sum=sum2=0;
           while(sum1)
           {
                 sum=sum1%10;
                 sum1/=10;
                 dp[i][sum2]+=shu[sum][0];
                 dp[i][sum2+1]+=shu[sum][1];
                 dp[i][sum2+2]+=shu[sum][2];
                 sum2+=2;
           }
}
int main()
{
    scanf("%d",&n);
    set();
    for(int i=1;i<=n;i++)
    {
          work1(i);
          work2(i);
    }
    for(int i=0;i<=6;i++)
    {
        if(!dp[n][i])
        return 0;
        printf("%c %d\n",sz[i],dp[n][i]);
    }
}
```

---

## 作者：Bzy_temp (赞：0)

###偌大一道简单题，直接分解各位数字，打表（也可直接每回平移两位【这里为了直观就没写】求）相加即可.

~~表示其他方法太长了懒得写~~



```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
//各位打表
int a_1[10][10]={{0,0,0,0,0,0,0},{1,0,0,0,0,0,0},{2,0,0,0,0,0,0},{3,0,0,0,0,0,0},{1,1,0,0,0,0,0},{0,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,0},{2,1,0,0,0,0,0},{3,1,0,0,0,0,0},{1,0,1,0,0,0,0}};
int a_2[10][10]={{0,0,0,0,0,0,0},{0,0,1,0,0,0,0},{0,0,2,0,0,0,0},{0,0,3,0,0,0,0},{0,0,1,1,0,0,0},{0,0,0,1,0,0,0,0},{0,0,1,1,0,0,0,0},{0,0,2,1,0,0,0},{0,0,3,1,0,0,0},{0,0,1,0,1,0,0}};
int a_3[10][10]={{0,0,0,0,0,0,0},{0,0,0,0,1,0,0},{0,0,0,0,2,0,0},{0,0,0,0,3,0,0},{0,0,0,0,1,1,0},{0,0,0,0,0,1,0,0},{0,0,0,0,1,1,0,0},{0,0,0,0,2,1,0},{0,0,0,0,3,1,0},{0,0,0,0,1,0,1}};
int a_4[4][10]= {{0,0,0,0,0,0,0},{0,0,0,0,0,0,1},{0,0,0,0,0,0,2},{0,0,0,0,0,0,3}};
int all[7];char lett[7]={'I','V','X','L','C','D','M'};//字母表
int main(){
    int a;cin>>a;//输入
    for(int i=1;i<=a;i++){
//取出各位
        int a4=i/1000;
        int a3=(i/100)%10;
        int a2=(i/10)%10;
        int a1=i%10;
        for(int j=0;j<=6;j++)all[j]+=a_1[a1][j]+a_2[a2][j]+a_3[a3][j]+a_4[a4][j];//循环相加
    }
    for(int i=0;i<=6;i++)if(all[i])cout<<lett[i]<<" "<<all[i]<<'\n';//输出
    return 0;
}
```

---

## 作者：Seas0 (赞：0)

打表。。。。

每位的各个数字对应符号全打出来。。。



```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
//I 1 V 5 X 10 L 50 C 100 D 500 M 1000
        //  1     5     10    50    100   500  1000
const char I=1,V=2,X=3,L=4,C=5,D=6,M=7;
using namespace std;    //0     1      2         3       4      5      6        7           8        9
int gTable[10][10]={{0},{1,I},{2,I,I},{3,I,I,I},{2,I,V},{1,V},{2,V,I},{3,V,I,I},{4,V,I,I,I},{2,I,X}};
int hTable[10][10]={{0},{1,X},{2,X,X},{3,X,X,X},{2,X,L},{1,L},{2,L,X},{3,L,X,X},{4,L,X,X,X},{2,X,C}};
int uTable[10][10]={{0},{1,C},{2,C,C},{3,C,C,C},{2,C,D},{1,D},{2,D,C},{3,D,C,C},{4,D,C,C,C},{2,C,M}};
int tTable[4][10] ={{0},{1,M},{2,M,M},{3,M,M,M}};
const char cra[8]={'\0','I','V','X','L','C','D','M'};
int cnt[8];
int main()
{
    int n,t,u,h,g;cin >> n;
    for (int i = 1;i<=n;++i)
    {
        t=tTable[i/1000][0],u=uTable[i/100%10][0],h=hTable[i/10%10][0],g=gTable[i%10][0];
        for (int j=1;j<=t;++j)cnt[tTable[i/1000][j]]++;//统计千位
        for (int j=1;j<=u;++j)cnt[uTable[i/100%10][j]]++;//百位
        for (int j=1;j<=h;++j)cnt[hTable[i/10%10][j]]++;//十位
        for (int j=1;j<=g;++j)cnt[gTable[i%10][j]]++;//个位
    }
    for (int i = 1;i<=7;++i)if(cnt[i])cout << cra[i] <<' '<< cnt[i] << endl;
    return 0;
}
```

---

