# [USACO1.2] 回文平方数 Palindromic Squares

## 题目描述

回文数是指从左向右念和从右向左念都一样的数。如 $12321$ 就是一个典型的回文数。

给定一个用十进制表示的正整数 $B$，输出所有 $[1,300]$ 中，它的平方用 $B$ 进制表示时是回文数的数。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$2 \le B \le 20$

题目翻译来自NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
10
```

### 输出

```
1 1
2 4
3 9
11 121
22 484
26 676
101 10201
111 12321
121 14641
202 40804
212 44944
264 69696
```

# 题解

## 作者：hsfzLZH1 (赞：37)

给大家介绍一种C++11特有的方法：构造函数。

构造函数，就是在初始化结构体的过程中，通过调用node name(data)的方法来初始化一个结构体。虽然有重载=运算符大法，但是本人更加偏向于构造函数，因为这样便于编写和理解。

构造一个node结构体存储B进制数，我们只需要编写node的构造函数（就是将10进制整数转化为B进制数字的函数），一个输出函数，还有判断这个进制数是否是回文数的函数。

代码如下（请留意代码中的注释）：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int b;
inline char c(int x){if(x>=0&&x<=9)return x+'0';return x-10+'A';}
struct node
{
    int l,a[20];//进制数最大长度为17
    node(int x){for(l=0;x;l++)a[l]=x%b,x/=b;}//转换进制数，其中a[l-1]是最高位，a[0]是最低位
    void out(){for(int i=l-1;i>=0;i--)printf("%c",c(a[i]));}//从高到低依次输出
    bool tf(){for(int i=0;i<l;i++)if(a[i]!=a[l-i-1])return false;return true;}//判断这个数字是否是回文数，注意可以通过i<=l/2来加速，减少冗余运算
};
int main()
{
    scanf("%d",&b);
    for(int i=1;i<=300;i++)//从1到300暴力枚举
    {
        node n(i*i);//将i*i转化为进制为b的整数
        if(n.tf()){node m(i);m.out();putchar(' ');n.out();putchar('\n');}//如果n是一个b进制下的回文数，输出答案
    }
    return 0;
}
```

---

## 作者：dsjkafdsaf (赞：29)

## 二话不说，先贴代码，如下。。

 ```cpp
#include<bits/stdc++.h>
using namespace std;
char a1[10000000],a[10000000];
int jz(int b,int a) {
    int j=0;
    while(a!=0) {
        j++;
        a1[j]=a%b+'0';
        if(a1[j]>'9')a1[j]=a1[j]-'10'+'A';
        a/=b;
    }
    int l=1,r=j;
    while(l<r) {
        if(a1[l]!=a1[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}
int jzz(int b,int a) {
    int j=0;
    while(a!=0) {
        j++;
        a1[j]=a%b+'0';
        if(a1[j]>'9'||a1[j]<'0')a1[j]=a1[j]-'9'+'A'-1;
        a/=b;
    }
    for(int i=j;i>=1;i--)cout<<a1[i];
}
int main() {
    int a;
    cin>>a;
    for(int i=1; i<=300; i++) {
        if(jz(a,i*i)==true){
        jzz(a,i);
        cout<<" ";
        jzz(a,i*i);
        cout<<endl;
        }
    }
    return 0;
}
```
### 首先，函数jz是用来判断数a转换为b进制下是否为回文数的，这可以用while循环来解决
```cpp
int jz(int b,int a) {
    int j=0;
    while(a!=0) {
        j++;
        a1[j]=a%b+'0';
        if(a1[j]>'9')a1[j]=a1[j]-'10'+'A';
        a/=b;
    }
    int l=1,r=j;
    while(l<r) {
        if(a1[l]!=a1[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}
```
### 其次jzz是用来输出的，把十进制数转换为a进制数输出的；
```cpp
int jzz(int b,int a) {
    int j=0;
    while(a!=0) {
        j++;
        a1[j]=a%b+'0';
        if(a1[j]>'9'||a1[j]<'0')a1[j]=a1[j]-'9'+'A'-1;
        a/=b;
    }
    for(int i=j;i>=1;i--)cout<<a1[i];
}
```
## 最后自然是从1-300进行枚举了qwq...

---

## 作者：Violette (赞：18)

## 首先，给大家介绍一种方法：转换进制

把a转化为b进制：

把a不断去模b，直到a=0，每次模完以后a除以b。

最后，把所有算出的余数倒过来写，就是a的b进制。

#### 如果b>10，则用A表示10，B表示11等等。

然后再看这道题目，大体思路是这样的：

编写三个函数（让主程序尽可能短），分别转换进制并存储长度、

判断回文数：判断数组以i为下标的数是否等于它所对应数、

判断s[i]与s[s[0]+1-i]是否相等以及控制打印的函数print：

如果此数小于等于9，则直接输出即可。

否则输出它所对应的字母（减去10，再加上字符A）。

主函数中，从1-300进行循环，调用三个函数，分别输出i和i

乘i。

最后，贴上AC代码：

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int n;
int s[301];
void jz(int a,int b)//转换进制 
{
    int r=0;
    while(a){
        s[++r]=a%b;
        a/=b;
    }
    s[0]=r;
}
bool change(){//判断s[i]与s[s[0]+1-i]是否相等
    for(int i=1;i<=s[0];i++)
	{
    	if(s[i]!=s[s[0]+1-i]) return false;
    }
    return true;
}
void print(){//打印 
    for(int i=s[0];i>=1;i--)
	{
        if(s[i]<=9) cout<<s[i];
        else cout<<(char)(s[i]-10+'A');
    }
} 
int main() 
	{
	cin>>n;
	for(int i=1;i<=300;i++)
	{//从1-300进行循环 
    	jz(i*i,n);//调用函数 
    	if(change()){
        	jz(i,n);
	        print();
	        cout<<' ';
	        jz(i*i,n);
	        print();
	        puts("");
		}
	}
    return 0;
}

```


---

## 作者：罗旅洲 (赞：11)

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int a[100],w;//a存储余数，w计算数位 
int b[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};//暴力的转换 
bool change(int n,int k){//除k取余法 
    int flag=1;
    while(n!=0){
        a[++w]=n%k;
        n/=k;
    }
    for(int u=1;u<=w/2+1;u++)//检验回文 
        if(a[u]!=a[w-u+1]){
            flag=0;break;
}
    return flag;
}
int main(){
    int i,j,k,m,n;
    scanf("%d",&n);
    for(i=1;i<=300;i++){ 
        j=i*i;w=0; //w要随时清空，数位会时刻变化 
    if(change(j,n)==1){
        w=0;change(i,n);
        for(int u=w;u>=1;u--){        //注意u要从 w枚举到 1，除k取余法要倒着数 
        if(a[u]<10)printf("%d",a[u]);
        else printf("%c",b[a[u]-10]);
    }
        printf(" ");
        //输出原数
        w=0;change(j,n);
        for(int u=1;u<=w;u++){        //回文数从1枚举到w输出都无所谓 
        if(a[u]<10)printf("%d",a[u]);
        else printf("%c",b[a[u]-10]);
        }
        printf("\n");
    }    
}
    return 0;
}
```

---

## 作者：未来miss (赞：10)

# 若不是你有着回文的平方，我怎会把死守的AC放任了~
不想AC都是假的，毕竟我的心也是肉做的   

**转进制**时我心里的for，就变成**while**  

不想AC都是假的，如果我有学过**case**语句  

用着**while和case**的人，**转进制**杠杠的  

若不是你有着回文的平方，我怎会把死守的的AC放任了~  

WA的话你都说，AC的话你不说  

我却把**for到300**当作你转进制的躯壳   

————(进制色)by.未来
## 正经发题解
没错就是这样编    

用for语句控制要判断是否回文的$\color{red}\text{原数}$  

注意！！！！！然后用一个变量保存$\color{red}\text{i的平方}$       

一层while转进制放进一个字符串s里      

判断回文后，输出回文数和原数        

注意！！！！！$\color{red}\text{原数倒序输出}$      

上代码(代码很丑，别嫌弃)：
```pascal
var n,m,i,l,x,a,j:longint;
s,t,st:string;
b:boolean;
begin
  read(n);
  for i:=1 to 300 do
    begin
      b:=true;
      s:='';
      m:=i*i;
      while m<>0 do
        begin
          a:=m mod n;
          m:=m div n;
          case a of
            0,1,2,3,4,5,6,7,8,9:str(a,t);
            10:t:='A';
            11:t:='B';
            12:t:='C';
            13:t:='D';
            14:t:='E';
            15:t:='F';
            16:t:='G';
            17:t:='H';
            18:t:='I';
            19:t:='J';
            20:t:='K';
          end;
          s:=s+t;
        end;
      for j:=1 to length(s) div 2 do
        if s[j]<>s[length(s)-j+1] then b:=false;
      if not b then continue;
      x:=i;
      t:='';
      st:='';
      while x<>0 do
        begin
          a:=x mod n;
          x:=x div n;
          case a of
            0,1,2,3,4,5,6,7,8,9:str(a,t);
            10:t:='A';
            11:t:='B';
            12:t:='C';
            13:t:='D';
            14:t:='E';
            15:t:='F';
            16:t:='G';
            17:t:='H';
            18:t:='I';
            19:t:='J';
            20:t:='K';
          end; 
          st:=st+t;
        end;
      for j:=length(st) downto 1 do
        write(st[j]);
      writeln(' ',s);
    end;
end.

```


---

## 作者：DrMao (赞：8)

这道题还是比较简单滴，首先，我们从一至三百一个一个枚举，通过judge函数判断。先用a数组进行进制转换，tail是标记位置用的。进制转换完成之后，在两端进行比较，取一终点(tail+1)/2，两端向中间靠拢，如果说发现不一样则stop=0弹出。


------------

对于print阶段也是一样的先进制转换，然后在倒序输出，因为进制转换的时候它是反的！当它要输出10以上的数时用char类型的g数组即可

这是本人第一次发题解，~~请大佬见谅~~
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
int b;
int a[1000];
char g[12]={'A','B','C','D','E','F','G','H','I','J','K','L'};//标出这些字母
bool judge(int x)
{
   int stop=1,tail=1;
   while(x!=0)//进制转换
   {
   	  a[tail]=x%b;
   	  x=x/b;
   	  tail++;
   }
   tail--;
   for(int i=1;i<=(tail+1)/2;i++)
   	  if(a[i]!=a[tail+1-i])
   	  {
   	     stop=0;//判断是否为回文
		 break;	
	  }
	if(stop==1)
	  return 1;
	else 
	  return 0;
}
void print(int x)
{
   int tail=1;
   while(x!=0)//照例进制转换
   {
   	  a[tail]=x%b;
   	  x=x/b;
   	  tail++;
   }
   tail--;
   for(int i=tail;i>=1;i--)//倒叙输出
   {
   	  if(a[i]<=9)
   	    printf("%d",a[i]);
   	  else
   	    printf("%c",g[a[i]-10]);
   	  
   }
} 
int main() 
{
	scanf("%d",&b);
	for(int i=1;i<=300;i++)
	{
		if(judge(i*i)==1)
		{
		  	print(i);//打印这个数
		    printf(" ");
			print(i*i);//打印这个数的平方
			printf("\n");  	
		}
	}/**/
	return 0;
}
```

---

## 作者：嚯呀嚯呀 (赞：5)

P党的题解来咯

非常水的一道模拟题 枚举1到300 先判断平方数是不是回文数即可

下面亮代码

```cpp
var
  bi:boolean;
  a1:longint;
  i,j,m,n,k,p,tot:longint;
  a,b:array[0..10]of char;
  s:string;
begin
  readln(n);
  for i:=1 to 300 do  //枚举
    begin
      a1:=i*i; tot:=0; s:=''; //先把平方数换成B进制
      while a1<>0 do
        begin
          k:=a1 mod n; inc(tot);
          if (k>=0)and(k<=9) then
            a[tot]:=chr(k+48) //如果是0到9就是数字 反之是字母
          else
            a[tot]:=chr(k-10+65);
          a1:=a1 div n;  s:=s+a[tot];//用来记录顺序的情况是什么
        end;
      bi:=true;
      for j:=1 to tot do
        if s[j]<>a[tot-j+1] then
          begin
            bi:=false; break;
          end;
      if bi=true then//如果平方数是回文数的话
        begin
          a1:=i; p:=0;
          while a1<>0 do  //再把原数换成B进制
            begin
              k:=a1 mod n; inc(p);
              if (k>=0)and(k<=9) then
                b[p]:=chr(k+48)
              else
                b[p]:=chr(k-10+65);
              a1:=a1 div n;
            end;
          for j:=p downto 1 do write(b[j]); write(' ');
          for j:=tot downto 1 do write(a[j]); writeln; 
        end;
    end;
end.//是不是非常的简单？

```

---

## 作者：ww3113306 (赞：4)


```cpp
#include<bits/stdc++.h>
using namespace std;
int i,m,n,k,t,j,len,l,ll,sum,cl,kkk;char ans[20]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'},answer[100]={'l'},c[100]={'l'};
void change(int a)
{
    int k;
    k=a%m;
    a=a/m;
    if (a>0)
        change(a);
    answer[t]=ans[k],t++;    
}
int  main()
{
    cin>>m;
    for(i=1;i<=300;i++)
    {    
        kkk=0;
        t=1;
        sum=i*i;
        change(sum);//将这个数的平方转换为指定进制 
        len=strlen(answer)-1;
    //    cout<<endl;    
        for(j=1,l=len;j<=len,l>0;j++,l--)
            if(answer[l]!=answer[j]) kkk=1;//判断是否为回文数 
        //cout<<kkk;    
            if(kkk==0)//如果这个数的平方是回文数 
            {
                for(ll=1;ll<=len;ll++)
                    c[ll]=answer[ll];//将这个数的平方的指定进制转存进c数组 
                t=1;    
                for(ll=1;ll<=100;ll++)
                    answer[ll]='\0';//初始化answer数组（前面因为i在不断增大，所以后面的数的平方的位数一定大于等于前面的数，所以之前的结果会被覆盖，因此不用初始化） 
                change(i);//将i转换为指定进制 
                cl=strlen(answer)-1;//因为answer[0]赋了值，所以长度要减去1才是真实的长度 
                //cout<<i<<' ';
                for(ll=1;ll<=cl;ll++)    
                    printf("%c",answer[ll]);//输出i （B进制） 
                cout<<' ';    
                for(ll=1;ll<=len;ll++)    
                    printf("%c",c[ll]);//输出 i的平方（B进制） 
                cout<<endl;    
            }
    }
    change(n);
    return 0;    
}
```

---

## 作者：Thaumaturge (赞：3)

啥也不说，一个转换进制位的题目而已，代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

int i,j,k,n,m[310],m1[310],a0[310][30],a[310],ak[310],a1[310][30],o[310],pp;
char hb;

int main(){
	cin>>n;
	for(i=1;i<=300;i++)
	{
		a[i]=i;
		ak[i]=i*i;
	}
	for(j=1;j<=300;j++)
	{
		while(ak[j]>=1)
		{
			m[j]++;
			a0[j][m[j]]=ak[j]%n;
			ak[j]/=n;
		}
	}

	for(j=1;j<=300;j++)
	{
		while(a[j]>=1)
		{
			m1[j]++;

			a1[j][m1[j]]=a[j]%n;

			a[j]=a[j]/n;
		}
	}
	
	for(i=1;i<=300;i++)
	{
		pp=0;
		for(j=1;j<=m[i];j++)
		{
			if(a0[i][j]!=a0[i][m[i]-j+1])
			{pp=1;break;}
		}
		if(pp==0) o[i]=1;
	}
	
	for(i=1;i<=300;i++)
	{
		if(o[i]==1)
		{
		if(n<=10)
		{
			for(j=m1[i];j>=1;j--)
			cout<<a1[i][j];
			
			cout<<" ";
			for(j=m[i];j>=1;j--)
			cout<<a0[i][j];
			cout<<"\n";
		}

		else
		{
			for(j=m1[i];j>=1;j--)
			{
				if(a1[i][j]<10)
				cout<<a1[i][j];
				else
				{
				hb=a1[i][j]-10+'A';
				cout<<hb;
				}
			}
			
			cout<<" ";

			for(j=m[i];j>=1;j--)
			{
				if(a0[i][j]<10)
				cout<<a0[i][j];
				else
				{
					hb=a0[i][j]-10+'A';
					cout<<hb;
				}
			}
			cout<<"\n";
		}
		}
	}
	return 0;
}
```
哦，对了，还要换行

---

## 作者：「QQ红包」 (赞：2)

题解 by：redbag

好像没有正常的c++题解？来一发。

AC记录：http://www.luogu.org/record/show?rid=683927

/\*
ID: ylx14274

PROG: palsquare

LANG: C++

\*/
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
int a[30];//存n进制数转的结果， 
int b[30];//各种用途 
int i,j,n,k,kk;//n存进制 
int nf,ny;
void he(int nn)//转成n进制 
{
```
。。。。int ha,yu,shang;
。。。。for(j=1;j<=29;j++)

。。。。。。。。a[j]=0;

。。。。k=0;

。。。。shang=nn;

。。。。while (true)

。。。。{

。。。。。。。。yu=shang%n;

。。。。。。。。shang=shang/n;

。。。。。。。。++k;

。。。。。。。。a[k]=yu;

。。。。。。。。if (shang==0) break;

。。。。}

} 
void haa(int nn)//转成n进制 

{
。。。。int ha,yu,shang;

。。。。for(j=1;j<=29;j++)

。。。。。。。。b[j]=0;

。。。。kk=0;

。。。。shang=nn;

。。。。while (true)

。。。。{

。。。。。。。。yu=shang%n;

。。。。。。。。shang=shang/n;

。。。。。。。。++kk;

。。。。。。。。b[kk]=yu;

。。。。    if (shang==0) break;

。。。。}

} 
int main() 

{
。。。。freopen("palsquare.in","r",stdin);//友情提示：抄题解的小朋友

。。。。freopen("palsquare.out","w",stdout); //记得去掉文件哦，这可不是未AC的代码

。。。。cin>>n;

。。。。for (i=1;i<=300;i++)//枚举

。。。。{

。。。。。。。。int biaoji=1;//标记用

。。。。。。。。he(i);//还是要转成n进制，因为需要输出。

。。。。。。。。nf=i\*i;//求出平方

。。。。。。。。haa(nf);//转成n进制

。。。。。。。。for (j=1;j<=kk;j++)//判断i的平方是否为回文数

。。。。。。。。{

。。。。。。。。。。。。if (b[j]!=b[kk-j+1])//如果其中一位不满足就标记。

。。。。。。。。。。。。{

。。。。。。。。。。。。。。。。biaoji=0;//标记

。。。。。。。。。。。。。。。。break;

。。。。。。。。。。。。}

。。。。。。。。}

。。。。。。。。if (biaoji==1)

。。。。。。。。{

。。。。。。。。。。。。for (j=k;j>=1;j--)

。。。。。。。。。。。。{

。。。。。。。。。。。。。。。。if (a[j]<10) printf("%d",a[j]);//大于10的话就要输出字母

。。。。。。。。。。。。。。。。else{

。。。。。。。。。。。。。。。。。。。。    char cha=char(a[j]-10+65);//10对应A，A的askii码是65，找规律

。。。。。。。。。。。。。。。。。。。。。。。。printf("%c",cha);

。。。。。。。。。。。。。。。。。。。。}

。。。。。。。。。。。。}。。。。。。。。。。。。

。。。。。。。。。。。。cout<<" ";//分割

//因为是回文数，就算是倒着存的但是输出也不影响，

。。。。。。。。。。。。for (j=1;j<=kk;j++)

。。。。。。。。。。。。。。。。if (b[j]<10) printf("%d",b[j]);

。。。。。。。。。。。。。。。。else{

。。。。。。。。。。。。。。。。。。。。    char cha=char(b[j]-10+65);

。。。。。。。。。。。。。。。。。。。。。。。。printf("%c",cha);

。。。。。。。。。。。。。。。。。。。。}

。。。。。。。。。。。。cout<<endl;

。。。。。。。。}

。。。。}


    return 0;

}
一堆句号是防止缩进被吞的


---

## 作者：buickboy (赞：1)

基本思路分三步。一是i从1到300枚举，将i的平方转换为b进制字符串s；二是判断s是否为回文。三是根据第二步结果，输出i的b进制字符串和i*i的b进制字符串。

因此，要设计判断字符串是否为回文的函数，以及将10进制int型转为b进制下string型的函数。

判断字符串是否回文，只要从两头向中间依次比较，发现左右两边对应位置的字符不同，就返回false，然后最终函数返回为true，意味着循环结束也没有不同。比较的对应位置，是string里从s[0]与s[len-1]、s[1]与s[len-1-1]，即s[i]与s[len-1-i]，总的比较次数是len/2次，从0计起就是len/2-1次。

从10进制转b进制，方法是短除法连续取余，比如42转为2进制，就是从上往下短除法，依次得余数010101，直到被除数为0止，再从下往上排出，得101010。再在换一个方法，每次求得的余数，依次排在最前面，就可以直接得到最后的结果。如果是16进制下余数是10，就要将余数赋为A，这样可预先做出一个字符串字典，余数求出是多少，直接对应下标10找到这个A。找到后，直接加到结果字符串前面。

本题有3处优化代码之处。一是x=dic[n%b]+x进行查表转进制，省去大量if…else或switch…case。二是由于要反复进行10进制转b进制，设计子函数，方便重复调用。三是由于需要判断的数是从1到300非常规律，直接将生成10进制平方数、平方数转b进制字符串、判断回文并输出b进制下的数及平方数，这三步都可在一次循环中完成。

本题数据是[1,300]区间，int即可，无数据坑。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool hw(string s)//判断字符串回文 
{
	int i,len=s.size();//假设len=4 
	for(i=0;i<len/2;++i)//奇数长度最中间字符不参加比较
	{//偶数长度只比较1-len/2次，次数从0计起就要减1 
		if(s[i]!=s[len-1-i])//s[1]!=s[4-1-1]
			return false;
	}	
	return true;
}
string ten2b(int n,int b)//10进制整型n转b进制字符串x 
{	
	string x,dic="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while(n)
	{
		x=dic[n%b]+x;
		n/=b;
	}
	return x;
}
int main()
{
    int i,m,b;
    string s;
    cin>>b;
    for(i=1;i<=300;++i)
    {
    	m=i*i;//生成10进制平方数
    	s=ten2b(m,b);
    	if(hw(s)) 
			cout<<ten2b(i,b)<<" "<<s<<endl;
	}
    return 0;
}

```

---

## 作者：functionendless (赞：1)

完全枚举。turn转进制，judge判回文，search枚举，print输出每行的第一个数


```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int w,a[20];
int turn(int n)
{
    memset(a,0,sizeof(a)); 
    int i=0,j;
    while(n>0)
    {
        a[++i]=n%w;
        n/=w;
    }
    return i;    
}
bool judge(int x)
{
    int i=1,j=x;
    while(i<j)
    {
        if(a[i++]!=a[j--]) return false;
    }
    return true;
}
void print(int n)
{
    int b[20],i=0,j;
    while(n>0)
    {
        b[++i]=n%w;
        n/=w;
    }
    for(j=i;j>=1;j--)
    {
        if(b[j]>=10) printf("%c",'A'+b[j]-10);
        else printf("%d",b[j]);
    }
    printf(" ");
}
void search()
{
    int i,j;
    for(i=1;i<=300;i++)
    {
        int x=turn(pow(i,2));
        //printf("%d %d ",i,pow(i,2));
        //for(j=x;j>=1;j--)
        //    printf("%d",a[j]);
        //printf("\n");
        if(judge(x))
        {
            print(i);
            for(j=x;j>=1;j--)
            {
                if(a[j]>=10) printf("%c",'A'+a[j]-10);
                else printf("%d",a[j]);
            }
            printf("\n");
        }
    }    
}
int main()
{
    int i,j;
    scanf("%d",&w);
    search();
    return 0;
}
```

---

## 作者：liuzitong (赞：1)

虽然题目中看不出来
## 但这个题考的是进制转换吧
判断回文数谁不会

(蒟蒻的自己见解,觉得不对的话可以当做放p)

**好像**回文数的平方都是回文数
(瞎说的)

我来讲一下进制转换吧,

如果数不是很大,可以用这种方法

如果是任意进制转换就先转成10进制,这个初中就学了了吧
我就不说了,主要说10进制转成n进制

我们建立一个数组a[1001];

将a[1]设成待转换的数字

然后n进一,慢慢弄就好了,

具体就是下面的代码
```cpp
		int ss = 1;
		while(a[ss] >= n){//jk也是
			a[ss + 1] += a[ss] / n;
			a[ss] %= n;
			ss ++;
		}
```
这样的话就可以了,有字母怎么办呢?

我们又不需要字母比较,输出的时候在转换就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001],b[1001];//a储存回文数的平方,b储存它本身
int main() {
	int n,ss,s;//ss是回文数平方的长度,s是它本身的长度
	cin>>n;
	for (int i = 1; i < 301; ++i)
	{
		int jk = i * i;	//jk是i的平方,是待判断的回文数
		ss = 1;//初始化
		b[1] = i;
		s = 1;
		a[1] = jk;
		while(b[s] >= n){//将i变成字符串,
			b[s + 1] += b[s] / n;
			b[s] %= n;
			s ++;
		}
		while(a[ss] >= n){//jk也是
			a[ss + 1] += a[ss] / n;
			a[ss] %= n;
			ss ++;
		}
		for (int j = 1; j <= ss / 2; ++j)//判断jk是否是回文数,循环到ss / 2即可
			if (a[j] != a[ss - j + 1])//如果有一个不对称,直接试下一个
				goto aa;
			for (int j = s; j >= 1; --j){//如果是10进制以上需要转化成字母
				if(b[j] < 10)
					cout<<b[j];
				else
					cout<<char(55 + b[j]);
			}
			cout<<" ";
			for (int j = 1; j <= ss; ++j){//回文数也是
				if(a[j] < 10)
					cout<<a[j];
				else
					cout<<char(55 + a[j]);
			}
			cout<<endl;
			aa:;
			memset(a,0,sizeof a);//一定要清空
			memset(b,0,sizeof b);
		}
		return 0;
	}

```


---

## 作者：Harry_hcx (赞：1)

肥肠清晰的代码，送给珍贵的P党们
```pascal
var
  i,n:longint;  k:string;
  function huiwen(s:string):boolean;//判断是否是回文数
  var
    i:longint;
  begin
    for i:=1 to length(s) div 2 do
      if s[i]<>s[length(s)-i+1] then
        exit(false);
    exit(true);
  end;
  function jinzhi(x,k:int64):string;//将x转换成k进制
  var s:string; c:int64;
  begin
    s:='';//切记别忘赋初值，在函数与过程中定义的变量不会自动归0或者归为空串
    while x>0 do begin
      c:=x mod k;
      if c>9 then
        s:=chr(x mod k +55)+s//处理字母
      else
        s:=chr(x mod k +48)+s;//处理数字
      x:=x div k;
    end;
    exit(s);
  end;
begin
  readln(n);//n相当于b
  for i:=1 to 300 do begin
    k:=jinzhi(i*i,n);//保存平方后的数
    if huiwen(k) then//判断回文
      writeln(jinzhi(i,n),' ',k);//注意：输出的是b进制后的数，不是原数
  end;
  readln
end.

```

---

## 作者：ZhYic (赞：0)

整体思路：穷举1-300数，依次按位转换到目标进制，输出时再以字符型输出为A-K的位

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
int n,ans,change[20],jinzhi,base[20];
void** display**(int x,int y)//输出找到的回文数
{
    for(int i=x;i>=1;i--)
    {
        if(base[i]>=10)printf("%c",base[i]+55);
        else printf("%d",base[i]);
    }printf(" ");
    for(int i=1;i<=y;i++)
    {
        if(change[i]>=10)printf("%c",change[i]+55);
        else printf("%d",change[i]);
    }
    printf("\n");
}
void** judge**(int x)//判断是否是n进制下回文数
{
    int i=0;
    while(x>0)//进制转换通用结构
    {
        change[++i]=x%n;
        x=x/n;
    }
    for(int j=1;j<=i;j++)
        if(change[j]!=change[i+1-j])return;
    int j=0;
    while(ans>0)//如果是回文数，再将原数转换
    {
        base[++j]=ans%n;
        ans=ans/n;
    }
    display(j,i);
}
int main()
{
    cin>>n;
    for(int i=1;i<=300;i++)
        {ans=i;judge(ans*ans);}
    return 0;
}

```

---

## 作者：Creeper_LKF (赞：0)

###一开始不知道处理A、B、C，然后又看了看题...

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;//要求用ABCD来表示10、11、12.。。。。。。
inline string change(int decs){//输入十进制数
    string x;
    x.clear();
    stack<short> ns;//翻转一下结果
    while(decs){
        ns.push(decs%n);
        decs/=n;
    }
    short ws=ns.size();
    for(short i=1;i<=ws;i++){
        short y=ns.top();
        ns.pop();
        if(y<10) x+=(y+'0');
        else x+=(y-10+'A');//方便直接输出
    }
    return x;
}
inline bool check(const string &x){//加上const和&更保险
    short i=0,j=x.size()-1;
    while(i<j)
        if(x[i++]!=x[j--])
                       return false;//判断回文
    return true;
}
int main (){
    scanf("%d",&n);
    for(int i=1;i<=300;i++){
        int inp=i*i;//直接算平方
        string outp=change(inp);//转换
        if(check(outp))//检查
            cout<<change(i)<<" "<<outp<<endl;
    }
    return 0;
}

```

---

## 作者：hutao (赞：0)

/\*
请勿复制,创建美好题解

\*/
```cpp
#include<bits/stdc++.h>
int n,a[1000010],b[100010],i,l1,l2;  
using namespace std;  
int hw(void)//判断回文 
{
    for (int i=1;i<=l1/2;i++)//因为用的不是字符串,所以可以从一开始 
        if (a[i]!=a[l1-i+1])//数组是整型的,即使是A,B在判断回文的时候可以省略,只需要比较是否相等 
            return 0;
    return 1;
}
int pd(int k)
{
    l1=0;
    do
    {
        a[++l1]=k%n;//这里可以直接转换,即使是A,B,C,只要在最后面输出判断一下就可以了 
        k/=n;
    } while (k!=0);
    return 0;
}
int pd2(int k)
{
    l2=0;
    do
    {
        b[++l2]=k%n;//这里可以直接转换,即使是A,B,C,只要在最后面输出判断一下就可以了 
        k/=n;
    } while (k!=0);
    return 0;
}
int main()  
{  
    scanf("%d",&n);  
    for (i=1;i<=300;i++)//题目说了只要1~300以内 
    {   
        int k=i*i;//平方 
        pd(k);//判断在B进制下是否满足 
        if (hw())  
        {  
            k=i;
            pd2(k);
            for (int l=l2;l>0;l--) 
                if (b[l]>=10) //输出判定是否需要转换成字母 
                    printf("%c",b[l]+'A'-10);
                else 
                    printf("%d",b[l]);  
            printf(" ");  
            for (int l=l1;l>0;l--) 
                if (a[l]>=10) //输出判定是否需要转换成字母 
                    printf("%c",a[l]+'A'-10);
                else 
                    printf("%d",a[l]);  
            printf("\n"); //格式需要  
        }  
    }     
    return 0;   
}
```

---

## 作者：远航之曲 (赞：0)

好像没什么难的，主要就是考进制转换,以及回文数的判断。这里要注意，最大的20进制中20表示为J，不要只CASE到15哦！

穷举1——300的所有平方数，转进制，比较，OK了~除非你不会怎么转进制。短除，然后逆序输出。

参考进制转换伪代码

C/C++
[/color]```cpp

      int 位数=0;
      while(j != 0)
        {
          b[位数]=j % 进制 ;
          j = j / 进制;
         位数=位数+1;
        }

```
PASCAL
[/color]```delphi

      位数:integer;
      while j<>0 do begin
         b[位数]:=j mod 进制;
         j:=j/进制;
         位数:=位数+1;
      end;

```

参考代码

[/color]```cpp

#include<iostream>
using namespace std;
int B;
const
  int MAX=300;
  char CH[20]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};
 
void printdata(int x)
{
  int a[30],i=0;
  while (x>0) a[++i]=x%B,x/=B;
  for (;i;cout<<CH[ a[i--] ]);
}
 
void handle( int x )
{
  int a[30],n=0,xx=x*x;
  while (xx>0)  a[++n]=xx%B,xx/=B;
  int t=n;
  for (;(n>0)&&(a[n]==a[t-n+1]);--n);
  if (n==0) printdata(x),cout<<' ',printdata(x*x),cout<<endl;
}
 
int main()
{ 
  cin>>B;
  for (int i=1;i<=MAX;i++) handle(i);
  return 0;
}

```

---

## 作者：lych (赞：0)

本题为一道较为容易的基础题，唯一较难点就是进制的转化

首先通过读题可知，所求的对象为1~300内的所有数，同时转化需要的时间为log i(1≤i≤300)，因此所用时间为O（300\*log2i(1≤i≤300)），也就是O(1)；

接下来讲述算法：

首先大循环i控制所求对象1-300

接下来将i^2转化为b进制，保存在数组中

由于题目中没有要求对象须要是回文数，所以也就省了一步，只需要判断i^2是

否是回文数即可

还有就是输出，如果<9，那么就直接输出，否则须要转化

接下来给出标程：

```cpp
var
  f:array[0..100000] of longint;
  n,i,j,k,s:longint;
function huiwen:boolean;
var i:longint;
begin
  for i:=1 to k div 2 do
    if f[i]<>f[k-i+1] then exit(false);
  exit(true);
end;//回文数的判断，用函数较为简单，但不要忘了如果符合需要返回true
procedure njinzhi(ss:longint);
begin
  if ss=0 then exit;
  njinzhi(ss div n);
  if ss mod n<10 then write(ss mod n) else write(chr(ss mod n+55));{也可以使用+ord（'A')-10}
end;//对10进制的数s的转化n进制，并输出，注意大于10的进制，还有就是因为输出是从后往前的所以需要先递归再输出
procedure print(x:longint);
var i:longint;
begin
  njinzhi(x);
  write(' ');
  for i:=k downto 1 do//从后往前输出
    if f[i]<10 then write(f[i]) else write(chr(f[i]+55));
  writeln;
end;//打印输出，不多解释
procedure work;
begin
  for i:=1 to 300 do
    begin
      k:=0;
      fillchar(f,sizeof(f),0);
      s:=sqr(i);//求平方
      while s>0 do
        begin
          inc(k);
          f[k]:=s mod n;
          s:=s div n;
        end;//转化为n进制，并保存数组
      if huiwen then print(i);//如果符合，输出
    end;
end;
begin
  read(n);
  work;//开始工作
end.
```

---

## 作者：YczSS (赞：0)

短小精悍

```cpp
var
    i,n:longint;
function tentok(n,m:longint):string;
    var
        i:longint;
    function nts(n:longint):string;
        begin
            *********         //自行脑补，过于简单
        end;
    begin
        tentok:='';
        repeat
            if (m>10) and (n mod m>9) then tentok:=chr((n mod m)+55)+tentok
            else tentok:=nts(n mod m)+tentok;
            n:=n div m;
        until n=0;
    end;
function ispalind(s:string):boolean;
    var
        i:longint;
    begin
        ispalind:=true;
        for i:=1 to length(s) div 2 do
            if s[i]<>s[length(s)-i+1] then begin ispalind:=false; break; end;
    end;
begin
    readln(n);
    for i:=1 to 300 do    //还用说，死枚举
        if ispalind(tentok(sqr(i),n)) then writeln(tentok(i,n),' ',tentok(sqr(i),n)); //学点英语~~tentok（十进制转K进制）；ispalind（是不是回文）
end.   //By-LYP
```

---

