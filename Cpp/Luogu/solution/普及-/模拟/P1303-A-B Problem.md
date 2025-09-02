# A*B Problem

## 题目背景

高精度乘法模板题。

## 题目描述

给出两个非负整数，求它们的乘积。

## 说明/提示

每个非负整数不超过 $10^{2000}$。

## 样例 #1

### 输入

```
1 
2```

### 输出

```
2```

# 题解

## 作者：lei_yu (赞：617)

这是一道~~看起来~~很水的题目，这里我来讲一下具体解法给刚开始学的同胞们。

首先讲一讲思路
------------
看一下下面这个乘法的过程

![](https://cdn.luogu.com.cn/upload/pic/69832.png)

~~（非常的大，肯定不是人算的，所以我们需要电脑）~~

我们在计算的时候是**计算2934乘下面的每一位最后加起来**。~~（强颜欢笑）~~

然而需要注意的是，我们在这样计算的时候，最后是加法是**错位**的（如上图），因此我们在计算的时候需要注意这一点。

接下来是具体的计算过程：
------------
首先将两个特别大的数字读入字符串，然后**倒着**放进一维数组 ~~（和高精度加法一样）~~；
```cpp
cin>>a1>>b1;
int lena=strlen(a1);
int lenb=strlen(b1);
for(i=1;i<=lena;i++)a[i]=a1[lena-i]-'0';
for(i=1;i<=lenb;i++)b[i]=b1[lenb-i]-'0';
```
接下来，不难想到，在计算乘法的时候可以使用两个循环进行枚举，以上面的图片为例子：外循环i为3489，内循环j为2934。 ~~(你想想自己怎么算乘法的)~~

数组c作为答案数组，在枚举时令c[i+j-1]+=a[i] * b[j];
```cpp
for(i=1;i<=lenb;i++)
for(j=1;j<=lena;j++)
c[i+j-1]+=a[j]*b[i];
```

在计算乘法的时候先不考虑进位，之后再加上去就行。但是为什么是i+j-1呢，事实上，j是指正常的计算进位（一位一位进行乘法计算），而i就是我们说的错位相加。

在进行枚举计算之后,我们的c数组就成为了没有进位的答案,如下图
![](https://cdn.luogu.com.cn/upload/pic/69841.png)

之后，我们只需要对c数组进行进位操作就好了。
```cpp
for(i=1;i<lena+lenb;i++)//无论数字如何大，数位也不会大于两个乘数的和
if(c[i]>9)//大于9则需要进位
{
	c[i+1]+=c[i]/10;
	c[i]%=10;
}
```
最后,我们还需要一个去除数字首多余的0的操作，同加法。
```cpp
len=lena+lenb;
while(c[len]==0&&len>1)len--;
```
最后的最后,我们只需要将数字输出就好了
```
for(i=len;i>=1;i--)cout<<c[i];
return 0;//华丽的结束
```

那么最后附上AC代码
------------
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
char a1[10001],b1[10001];
int a[10001],b[10001],i,x,len,j,c[10001];
int main ()
{
    cin>>a1>>b1;//不解释，不懂看前面
    int lena=strlen(a1);//每个部分都很清楚
	int lenb=strlen(b1);//这只是方便你们复制
    for(i=1;i<=lena;i++)a[i]=a1[lena-i]-'0';
    for(i=1;i<=lenb;i++)b[i]=b1[lenb-i]-'0';
	for(i=1;i<=lenb;i++)
	for(j=1;j<=lena;j++)
	c[i+j-1]+=a[j]*b[i];
    for(i=1;i<lena+lenb;i++)
	if(c[i]>9)
	{
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	len=lena+lenb;
    while(c[len]==0&&len>1)len--;
    for(i=len;i>=1;i--)cout<<c[i];
    return 0;
}
```

---

## 作者：瞿葩 (赞：503)

简短易懂的代码：

```cpp

#include<iostream>
#include<cstring>
using namespace std;
char a1[50001],b1[50001];
int a[50001],b[50001],i,x,len,j,c[50001];
int main ()
{
    cin >>a1 >>b1;//读入两个数
    a[0]=strlen(a1);b[0]=strlen(b1);//计算长度
    for (i=1;i<=a[0];++i)a[i]=a1[a[0]-i]-'0';//将字符串转换成数字
    for (i=1;i<=b[0];++i)b[i]=b1[b[0]-i]-'0';
    for (i=1;i<=a[0];++i)for (j=1;j<=b[0];++j)c[i+j-1]+=a[i]*b[j];//按乘法
    len=a[0]+b[0];                                       //原理进行高精乘
    for (i=1;i<len;++i)if (c[i]>9){c[i+1]+=c[i]/10;c[i]%=10;}//进位
    while (c[len]==0&&len>1)len--;//判断位数
    for (i=len;i>=1;--i)cout <<c[i];//输出
    return 0;
}

```
```cpp
var a,b:ansistring;
    le:boolean;
    c,d,e:array[0..20000]of longint;
    i,j:longint;
begin
  readln(a);
  readln(b);
  for i:=length(a) downto 1 do
   val(a[i],c[length(a)-i+1]);
  for i:=length(b) downto 1 do
   val(b[i],d[length(b)-i+1]);
  for i:=1 to length(a) do
   for j:=1 to length(b) do
     inc(e[i+j-1],c[i]*d[j]);
  for i:=1 to (length(a)+length(b)) do
   if e[i]>9 then
   begin
     e[i+1]:=e[i+1]+e[i] div 10;
     e[i]:=e[i] mod 10;
   end;
  le:=false;
  for i:=(length(a)+length(b)) downto 1 do
   if le=false then begin if e[i]<>0 then begin le:=true; write(e[i]); end; end
               else write(e[i]);
  if le=false then writeln(0);
end.
```

---

## 作者：lvfh (赞：114)

逆序存储，模拟乘法竖式计算，记得判断0的情况。



```cpp
#include<bits/stdc++.h>
using namespace std;
string a1,b1;
int jw=0,lena,lenb,lenc,a[2005],b[2005],c[4005];//x位数*y位数最多得出x+y位数，给数组留5左右的空间； 
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>a1>>b1;//读入； 
    lena=a1.length();
    lenb=b1.length();
    if(a1[0]=='0' || b1[0]=='0')
    {
        cout<<0;
        return 0;
}
//判断0的情况；
 if(lena<lenb || (lena==lenb&&a1[0]<b1[0]))
   { swap(a1,b1);
    swap(lena,lenb);
}
//把较小的数放在b1，提高效率；
    if(a1[0]=='-'&&b1[0]!='-')
    {
        cout<<"-";
        a1[0]=' ';
        b1=' '+b1;
    }
    if(b1[0]=='-'&&a1[0]!='-')
    {
        cout<<"-";
        b1[0]=' ';
        a1=' '+a1;
    }
    if(a1[0]!='-'&&b1[0]!='-')
    {
        a1=' '+a1;
        b1=' '+b1;
    }
    if(a1[0]=='-'&&b1[0]=='-')
    {
        a1[0]=' ';
        b1[0]=' ';
}
//判断一下负数，a1[0] 和 b1[0]判断，i从1开始 ；
    for(int i=1;i<=lena;i++)
      a[i]=a1[lena-i+1]-'0';
    for(int i=1;i<=lenb;i++)
      b[i]=b1[lenb-i+1]-'0';//逆序存储； 
    /*for(int i=1;i<=lena;i++)
      cout<<a[i]<<" ";
    cout<<endl;  
    for(int i=1;i<=lenb;i++)
      cout<<b[i]<<" ";*/ //调试； 
    for(int i=1;i<=lenb;i++)
      for(int j=1;j<=lena;j++)
    {
     c[i+j-1]=c[i+j-1]+(b[i]*a[j]);
     c[i+j]+=c[i+j-1]/10;
     c[i+j-1]%=10;    
}
//最关键的一步，模拟乘法竖式计算； //b[i]*a[j]应存放在c[i+j]中，由于数组从1开始，所以-1；
    int lenc=lena+lenb;
    while(lenc>0&&c[lenc]==0)
    {
    lenc--;
}
//消去开头的0；
    for(int i=lenc;i>=1;i--)
      cout<<c[i];        
    return 0;
}
第一篇题解，可能不好，见谅，见谅。
```

---

## 作者：Leianha (赞：105)

## 高精度

提供一种不一样的做法(NTT ~~Nationwide Totally TLE~~)。

我们在做高精度的题目的时候，需要用到竖式乘法，即模拟每一位的运算，类似我们的小学乘法，那么我们就可以写出这样的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char x[50010],y[50010];
int a[50010],b[50010],c[50010];
int main()
{
	cin>>x>>y;
	a[0]=strlen(x);b[0]=strlen(y);
	for(int i=1;i<=a[0];++i)a[i]=x[a[0]-i]-'0';
	for(int i=1;i<=b[0];++i)b[i]=y[b[0]-i]-'0';
	for(int i=1;i<=a[0];++i)
	for(int j=1;j<=b[0];++j)
	c[i+j-1]+=a[i]*b[j];
	int len=a[0]+b[0];
	for(int i=1;i<=len-1;++i)
	if(c[i]>9)
	{c[i+1]+=c[i]/10;c[i]%=10;}
	while(c[len]==0&&len>1)len--;
	for(int i=len;i>=1;--i)
	printf("%d",c[i]);
	return 0;
} 
```
其实这样就完全能够A掉这个题了。但是我们是追求完美的人，怎么能够仅仅限于A掉这道题呢？普通的算法时间复杂度为$O(n^2)$我们当然要用最完美的算法解决掉这道题(时间复杂度为$O(nlog(n))$)。考虑到FFT(~~Fast Fast TLE~~)大量的浮点运算和精度损失，我们可以利用原根的特殊性质来完成高精度乘法，因为原根也满足单位根的四条性质，并且精度损失小，当然是做高精度问题的首选啦（~~并且还很好写~~）。下面是NTT部分。

```cpp
void NTT(int limit,LL *l,int opt)
{
    for(int i=0;i<limit;++i)
    if(i<r[i])swap(l[i],l[r[i]]);
    for(int mid=1;mid<limit;mid<<=1)
    {
        LL wn,len=mid<<1;;
        if(opt==1)wn=ksm(G,(mod-1)/len,mod);
        else wn=ksm(Ginv,(mod-1)/len,mod);
        for(int j=0;j<limit;j+=len)
        {
            LL w=1;
            for(int k=j;k<mid+j;++k,(w*=wn)%=mod)
            {
                int x=l[k],y=w*l[k+mid]%mod;
                l[k]=(x+y)%mod;
                l[k+mid]=(x-y+mod)%mod;
            }
        }
    }
    if(opt==-1)
    {
        LL inv=ksm(limit,mod-2,mod);
        for(int i=0;i<=limit;i++) l[i]=l[i]*inv%mod;
    }
}
```


另外，998244353的原根是3，但是我们很明显用不到那么大的模数，40961的原根也是3，我们完全珂以ta来进行我们运算，减小常数。不过模数也不能取得太小，否则会WA（血的教训），所以一定要选择一个适合的模数。

下面提供一下我的高精度模板(利用重载实现)，包含正、负数的加减乘除(高精度除低精度)、输入输出和比较大小，当然也包含这道题的NTT高精度乘法，模板将不定期更新，详情请见[我的博客](https://www.cnblogs.com/wljss/p/11529965.html)


```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#define LL long long
using namespace std;
int m;
const long long mod=40961,G=3,Ginv=(mod+1)/3;
int r[240100];
LL ksm(LL a,LL b,LL mod)
{
    LL ans=1;
    for(;b;b>>=1,a=a*a%mod)
        if(b&1)ans=ans*a%mod;
    return ans;
}
void NTT(int limit,LL *l,int opt)
{
    for(int i=0;i<limit;++i)
    if(i<r[i])swap(l[i],l[r[i]]);
    for(int mid=1;mid<limit;mid<<=1)
    {
        LL wn,len=mid<<1;;
        if(opt==1)wn=ksm(G,(mod-1)/len,mod);
        else wn=ksm(Ginv,(mod-1)/len,mod);
        for(int j=0;j<limit;j+=len)
        {
            LL w=1;
            for(int k=j;k<mid+j;++k,(w*=wn)%=mod)
            {
                int x=l[k],y=w*l[k+mid]%mod;
                l[k]=(x+y)%mod;
                l[k+mid]=(x-y+mod)%mod;
            }
        }
    }
    if(opt==-1)
    {
        LL inv=ksm(limit,mod-2,mod);
        for(int i=0;i<=limit;i++) l[i]=l[i]*inv%mod;
    }
}
/*------以下为重载部分------*/ 
struct gj
{
    int len,zheng;//len：长度 zheng：正负标记0为负1为正 
    LL v[5000];
    gj(){len=0;memset(v,0,sizeof(v));zheng=1;}
    gj(int x)
    {
        if(x>=0)zheng=1;
        else x=-x,zheng=0;
        len=0;memset(v,0,sizeof(v));
        while(x)
        {
            v[++len]=x%10;
            x/=10;
        }
    }
    friend bool operator <(const gj &a,const gj &b)
    {
        if(a.len<b.len)return 1;
        if(a.len>b.len)return 0;
        for(int i=a.len;i>=1;--i)
        {
            if(a.v[i]<b.v[i])return 1;
            if(a.v[i]>b.v[i])return 0;
        }
        return 0;
    }
}n,a,b;
ostream& operator << (ostream &out,const gj &a);
istream& operator >> (istream &in,gj &a);
gj operator -(gj a,gj b);
gj operator +(gj a,gj b);
gj operator *(gj a,gj b);

gj operator +(gj a,gj b)
{
    if(!a.zheng&&!b.zheng)
    {
        a.zheng=b.zheng=1;
        gj c=a+b;
        c.zheng=0;
        return c;
    }
    if(!a.zheng&&b.zheng)
    {
        a.zheng=b.zheng=1;
        return b-a;
    }
    if(a.zheng&&!b.zheng)
    {
        a.zheng=b.zheng=1;
        return a-b;
    }
    int len=a.len+b.len;
    gj c;
    c.len=len;
    for(int i=1;i<=len;++i)c.v[i]=a.v[i]+b.v[i];
    for(int i=1;i<=len;++i)
    {
        if(c.v[i]>=10)
        {
            ++c.v[i+1];
            c.v[i]-=10;
        }
    }
    while(c.len&&!c.v[c.len])c.len--;
    return c;
}
gj operator -(gj a,gj b)
{
    if(!a.zheng&&!b.zheng)
    {
        a.zheng=b.zheng=1;
        return b-a;
    }
    if(!a.zheng&&b.zheng)
    {
        a.zheng=1;
        gj c=a+b;
        c.zheng=0;
        return c;
    }
    if(a.zheng&&!b.zheng)
    {
        b.zheng=1;
        gj c=a+b;
        return c;
    }
    if(a.zheng&&b.zheng&&a<b)
    {
        gj c=b-a;
        c.zheng=0;
        return c;
    }
    int len=max(a.len,b.len);
    gj c;
    for(int i=1;i<=len;++i)c.v[i]=a.v[i]-b.v[i];
    c.len=len;
    for(int i=1;i<=c.len;++i)
    {
        if(c.v[i]<0)
        {
            c.v[i+1]--;
            c.v[i]+=10;
        }
    }
    while(c.len&&!c.v[c.len])c.len--;
    return c;
}
gj operator *(gj a,gj b)
{
    int limit=1,tot,l=0;
    gj c;
    a.len--;b.len--;
    for(int i=0;i<=a.len;++i)a.v[i]=a.v[i+1];a.v[a.len+1]=0;
    for(int i=0;i<=b.len;++i)b.v[i]=b.v[i+1];b.v[b.len+1]=0;
    while(limit<=a.len+b.len)limit<<=1,l++;
    for(int i=0;i<=limit;i++) r[i]=(r[i>>1]>>1) | ((i&1)<<(l-1) );
    NTT(limit,a.v,1);NTT(limit,b.v,1);
    for(int i=0;i<=limit;i++) a.v[i]=a.v[i]*b.v[i]%mod;
    NTT(limit,a.v,-1);
    for(int i=0;i<=limit;i++) c.v[i]=a.v[i];
    for(int i=0;i<=limit;i++)
    {
        if(c.v[i]>=10)
        {
            c.v[i+1]+=c.v[i]/10,c.v[i]%=10;
            if(i+1>limit) limit++;
        }
    }
    for(int i=limit;i>=0;i--)if(c.v[i]==0) limit--;else break;
    c.len=limit+1;
    for(int i=c.len;i>=1;--i)c.v[i]=c.v[i-1];c.v[0]=0;
    for(int i=1;i<=c.len;++i)swap(c.v[i],c.v[c.len-i+1]);
    if(a.zheng!=b.zheng)c.zheng=0;
    else c.zheng=1;
    return c;
}
gj operator /(gj a,long long b)
{
    gj c;int d=0;
    for(int i=a.len;i>=1;--i)
    c.v[++c.len]=((d*10+a.v[i])/b),d=(d*10+a.v[i])%b;
    for(int i=1;i<=c.len/2;++i)swap(c.v[i],c.v[c.len-i+1]);
    if(!a.len||!b||(a.zheng&&b>0)||(!a.zheng&&b<0))c.zheng=1;
    else c.zheng=0;
    while(c.v[c.len]==0&&c.len>1)--c.len;
    return c;
}
istream& operator >> (istream &in,gj &a)//方便使用cin
{
    char lin[5010];int len;
    scanf("%s",lin+1);
    len=a.len=strlen(lin+1);
    if(lin[1]=='-')a.zheng=0,a.len--;
    else a.zheng=1;
    for(int i=1;i<=a.len;++i)a.v[i]=lin[len-i+1]-'0';
    return in;
}
ostream& operator << (ostream &out,const gj &a)//方便使用cout 
{
    if(!a.len)//一定要注意答案是0得情况 
    {
        cout<<"0";
        return out;
    }
    if(!a.zheng)cout<<"-";
    for(int i=a.len;i>=1;i--)printf("%d",a.v[i]);
    return out;
}
/*------以上为重载部分------*/ 
int main()
{
    cin>>a>>b;
    cout<<a*b;
    return 0;
}
```


---

## 作者：yjjr (赞：48)

本题需要使用高精度，在做乘法运算时，类似于加法，同样也有进位。不同的是，需要进行错位相加。

先用字符串读入两串数字，接着进行对字符串的转化存放在两个数组a,b内.

预处理结束后进入核心处理部分，用双重循环枚举两个乘数的任意一位，先进行对本轮的处理：当前乘积+上次进位成绩+原数（即c[i+j-1]:=a[i]\*b[j]+x+c[i+j-1])接着处理下一次进位，并对本次取模。

最后考虑多余的零的问题并进行输出。

```delphi

(var
 st1,st2:ansistring;
 i,j:longint;
 x,lena,lenb,lenc:qword;
 a,b,c:array[0..10000] of qword;

begin 
{读入}
 readln(st1);
 readln(st2);
{预处理} 
 lena:=length(st1);
 lenb:=length(st2);
 for i:=1 to lena do a[lena-i+1]:=ord(st1[i])-48;
 for i:=1 to lenb do b[lenb-i+1]:=ord(st2[i])-48;
{1循环{重置进位} 2循环{{当前乘积+上次进位+原数}{处理进位并取模}} {进位}}
 for i:=1 to lena do begin 
  x:=0;
  for j:=1 to lenb do begin 
   c[i+j-1]:=a[i]*b[j]+x+c[i+j-1];
   x:=c[i+j-1] div 10;
   c[i+j-1]:=c[i+j-1] mod 10;
  end;
  c[i+j]:=x;
 end;
{确定位数并删零}
 lenc:=lena+lenb;
 while (c[lenc]=0)and(lenc>1) do dec(lenc);
{输出}
 for i:=lenc downto 1 do write(c[i]);
end.)

```

---

## 作者：bunH2O (赞：35)

### 看到一群大佬们用c++打几十几百行的高精
### 其实python一行就可以水过
```python
print(int(input())*int(input()))
```
## 呵呵,但是联赛似乎不支持python
### 正常思路：
### 1.（函数）将输入变成字符串，并存进数组
```cpp
int convert(string s,int n[]) 
{
	int length=s.length();
	for(int i=1;i<=length;i++)
	{
		n[i]=s[length-i]-'0';
	}
	n[0]=length;
	return length;
}
```
### 2.（函数）实现加法过程，可先求数，再进位
```cpp
void h_time_2(int a[],int b[],int c[])
{
	int la=a[0];
	int lb=b[0];
	int lc=la+lb;
	for(int i=1;i<=la;i++)
	{
		for(int j=1;j<=lb;j++)
		{
			c[i+j-1]+=a[i]*b[j];//求每一位的数
		}
	}
	for(int i=1;i<=lc;i++)//处理进位
	{
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if(c[lc]==0) 
	{
		lc--;//结果位数确定
	}
	c[0]=lc;
}
```
### 3.（函数）输出 注意从大往小输出
```cpp
void output(int n[])
{
	int length=n[0];
	for(int i=length;i>=1;i--)//要倒着输
	{
		cout<<n[i];
	}
	cout<<endl;
}
```
### 4.main函数，注意特判0
```cpp
#include<iostream>
#include<string>
using namespace std;
const int N=10000;
void h_time_2(int a[],int b[],int c[]);
int convert(string s,int n[]);
void output(int n[]);
int a[N+1];
int b[N+1];
int c1[2*N+2];
int c2[2*N+2];
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	if(s1=="0"||s2=="0")//特判
	{
		cout<<0;
		return 0;
	}
	convert(s1,a);
	convert(s2,b);
	h_time_2(a,b,c1);
	output(c1);
	return 0;
}
```
### 5.最喜欢的完整代码（就没有注释了）
```cpp
#include<iostream>
#include<string>
using namespace std;
const int N=10000;
void h_time_2(int a[],int b[],int c[]);
int convert(string s,int n[]);
void output(int n[]);
int a[N+1];
int b[N+1];
int c1[2*N+2];
int c2[2*N+2];
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	if(s1=="0"||s2=="0")
	{
		cout<<0;
		return 0;
	}
	convert(s1,a);
	convert(s2,b);
	h_time_2(a,b,c1);
	output(c1);
	return 0;
}
void h_time_2(int a[],int b[],int c[])
{
	int la=a[0];
	int lb=b[0];
	int lc=la+lb;
	for(int i=1;i<=la;i++)
	{
		for(int j=1;j<=lb;j++)
		{
			c[i+j-1]+=a[i]*b[j];
		}
	}
	for(int i=1;i<=lc;i++)
	{
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if(c[lc]==0) 
	{
		lc--;
	}
	c[0]=lc;
}
int convert(string s,int n[]) 
{
	int length=s.length();
	for(int i=1;i<=length;i++)
	{
		n[i]=s[length-i]-'0';
	}
	n[0]=length;
	return length;
}
void output(int n[])
{
	int length=n[0];
	for(int i=length;i>=1;i--)
	{
		cout<<n[i];
	}
	cout<<endl;
}
```
第二稿，希望能过

---

## 作者：maple_love (赞：35)

这道题~~并不需要高精度~~高精度很重要,难度一般，来一发python:```python
a=input()
b=input()
print(int(a)*int(b))
```(逃
好吧，下面是正经的AC代码：
```cpp
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int main()
{
	int a[2010],b[2010],c[40100];//数组开大一点，以防RE
	int i,j;
	string s,x;
	cin>>s>>x;
	memset(a,0,sizeof(a)); 
	memset(b,0,sizeof(b)); 
	memset(c,0,sizeof(c)); 
    //清空数组，防止意外
	a[0]=s.length();
	for(i=1;i<=a[0];i++)
	{
		a[i]=s[a[0]-i]-'0';	
	}
	b[0]=x.length();
	for(i=1;i<=b[0];i++)
	{
		b[i]=x[b[0]-i]-'0';	
	}
	c[0]=a[0]+b[0]-1;
	for(j=1;j<=b[0];j++)
	{
		for(i=1;i<=a[0];i++)
		{
			c[i+j-1]+=a[i]*b[j];
			c[i+j]+=c[i+j-1]/10;
			c[i+j-1]%=10;
            //进位处理
		}
	}
	if(c[c[0]+1]>=1) c[0]++;
	while(c[c[0]]==0&&c[0]>1) --c[0];
	for(i=c[0];i>=1;i--) cout<<c[i];
	return 0;
} 
```

---

## 作者：FjswYuzu (赞：26)

#我爱vector##高精度##打死不用万能库##看不懂的模板#

~~我才不会告诉你么这是我们老师给我们的一个高精模板~~

------------

话说vector真是个好东西，现在安利给大家

```cpp
#include<iostream>
#include<vector>
#include<string>
//不推荐使用万能库。一般在洛谷上面做题能行。但是比赛的时候不要用，多了2MB的内存，我就MLE了...
using namespace std;
struct Wint:vector<int>
{
    Wint(int n=0)
    {
        push_back(n);
        check();
    }
    Wint& check()
    {
        while(!empty()&&!back())pop_back();
        if(empty())return *this;
        for(int i=1; i<size(); ++i)
        {
            (*this)[i]+=(*this)[i-1]/10;
            (*this)[i-1]%=10;
        }
        while(back()>=10)
        {
            push_back(back()/10);
            (*this)[size()-2]%=10;
        }
        return *this;
    }
};
istream& operator>>(istream &is,Wint &n)//读入
{
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}
ostream& operator<<(ostream &os,const Wint &n)//输出
{
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}
Wint operator*(const Wint &a,const Wint &b)//乘法
{
    Wint n;
    n.assign(a.size()+b.size()-1,0);
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
/*重载运算*/
int main()
{
    Wint a,b;//b是可以用int类型的，照样可以AC
    cin>>a>>b;//只能用cin cout读入输出
    cout<<a*b;//运行时请忽略那些诡异的警告
    return 0;//拜拜了模板~
}
```
基本代码就是这样。你也可以自己用这个Wint结构体来写一写其他的运算，实现也比较简单（包括关系运算，位运算）。

---

## 作者：空·白 (赞：24)

这道题我一开始很烦恼怎么读入数据，因为数据太大了，后来想到可以用字符串，那么这道题就很简单了（当然还要判断前导0）。

也可以点击链接来看我的博客，不定期发一些题解（可能比较简单）

[题解 P1303 【A*B Problem】](https://www.luogu.org/blog/c1223074598/)

------------
下面是AC代码

------------

```cpp
#include<bits/stdc++.h> //万能头不解释
using namespace std;
string s1,s2;
int a[2010];
int b[2010];
int ans[10000010]; //存储答案
int n,i,m,x,j,k=0;
int main()
{
	cin>>s1>>s2;
	n=s1.length(); //字符串长度
	for(i=1;i<=n;i++)
	{
		a[i]=s1[n-i]-48; //字符转换为数字，下同
	}
	m=s2.length();
	for(i=1;i<=m;i++)
	{
		b[i]=s2[m-i]-48;
	}
	x=n+m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			ans[i+j-1]+=a[i]*b[j];
			if(ans[i+j-1]>=10)
			{
				ans[i+j]+=ans[i+j-1]/10;
				if(i+j-1==x)
				{
					x++; //如果超出最大位数，再扩展位数
				}
				ans[i+j-1]%=10; //一位一位算
			}
		}
	}
	for(i=x;i>=1;i--)
	{
		if(k==0&&ans[i]==0)
		{
			continue; //去除前导0
		}
		else
		{
			cout<<ans[i];
			k++; //k判断最后的值是否为0
		}
	}
	if(k==0)
	{
		cout<<0; //如果值为0，输出0
	}
}
```
刚开始写题解，有说得不清楚的地方请指出。

---

## 作者：Sunshine_cfbsl (赞：20)

我是来试水的。。。


这一道题除了直接$O(n^2)$去算，还可以有更快的方法。

显然这道题可以用FFT过，并且代码要短一些。


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
using namespace std;

const double PI = acos(-1.0);
const int MAXN = 100010;
int n, m, ans[270000];
complex<double> a[270000], b[270000];
char s1[MAXN], s2[MAXN];

void FFT(complex<double> a[], int n, int t) {
    if(n == 1) return;
    int i;
    complex<double> l[n>>1], r[n>>1];
    for(i = 0; i < (n>>1); i++) l[i] = a[2*i], r[i] = a[2*i+1];
    FFT(l, n>>1, t), FFT(r, n>>1, t);
    complex<double> dw(cos(2*PI/n), sin(t*2*PI/n)), w(1, 0), tmp;
    for(i = 0; i < (n>>1); i++, w *= dw) 
        tmp = w*r[i], a[i] = l[i]+tmp, a[i+(n>>1)] = l[i]-tmp;
}

int main() {
    int i;
    scanf("%s%s", s1, s2);
    n = strlen(s1)-1, m = strlen(s2)-1;
    for(i = 0; i <= n; i++) a[i] = s1[n-i]-'0';
    for(i = 0; i <= m; i++) b[i] = s2[m-i]-'0';
    m = n+m;
    for(n = 1; n <= m; ) n <<= 1;
    FFT(a, n, 1), FFT(b, n, 1);
    for(i = 0; i <= n; i++) a[i] = a[i] * b[i];
    FFT(a, n, -1);
    for(i = 0; i <= m; i++) 
        ans[i] = (int)(a[i].real()/n+0.5);
    for(i = 0; i <= m; i++) {
        if(ans[i] >= 10) {
            ans[i+1] += ans[i]/10;
            ans[i] %= 10;
            if(i == m) m++;
        }
    }
    for(i = m; ans[i]==0 && m > 0; i--) m--;
    for(i = 0; i <= m; i++) printf("%d", ans[m-i]);
    printf("\n");
    return 0;
}
```

---

## 作者：封禁用户 (赞：13)

```cpp
sum = 1//初始应是一否则宝铃
s=int(input())//读入
sum = sum * int(n)//乘起来
s=int(input())
sum = sum * int(n)
print(sum)//输出
```

---

## 作者：底层码农 (赞：8)

Java菜鸡来一发
```java
import java.math.BigDecimal;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		String str1, str2;
		Scanner input = new Scanner(System.in);
		str1 = input.next();
		str2 = input.next();
		BigDecimal b1 = new BigDecimal(str1);
		BigDecimal b2 = new BigDecimal(str2);
		System.out.println(b1.multiply(b2));
		
		

	}

}

```

---

## 作者：S_Gloria (赞：7)

#### 我就不多说了，先上AC代码:
```
#include<iostream>
#include<cstring>
using namespace std;
int a1[101100],b1[110001],c[111000];
int main()
{
	string a,b;
	int l=0,s=0;
	cin>>a>>b;
	for(int i=a.length()-1;i>=0;i--)
		a1[l++]=a[i]-'0';   //反转的同时将字符转化成int类型的数字
	for(int i=b.length()-1;i>=0;i--)
		b1[s++]=b[i]-'0';  //同上
	int len=a.length()+b.length();//所得积的最多位数
	for(int i=0;i<a.length();i++)
	{
		for(int j=0;j<b.length();j++)
		{
			c[i+j]+=a1[i]*b1[j];
			c[i+j+1]+=c[i+j]/10;
			c[i+j]%=10;  //进位操作
		}
	}
	while(c[len-1]==0&&len>1)len--;
	for(int i=len-1;i>=0;i--)
		cout<<c[i];
}
```

### 需要注意的几点问题：
- 输入要用cin或者scanf，不要用gets或gentline，因为换行符\n会被误认为你输入的字符串之一。

- 不要直接对字符数组a操作，因为没有被赋值的空间在相加时会出错，所以要将a中数组重新存在int类型的新数组中，此处为a1.

- 最后要把数字前面的0删掉，一定要记得len>1,因为如果不这样做，0+0会被卡。 

（ps:如果还是不太理解，您可以进入我的博客，看一下高精加题解，较为详细。）

~~（全剧终）~~



---

## 作者：初墨 (赞：7)

### 【算法分析】

类似加法，可以用竖式求乘法。在做乘法运算时，同样也有进位，同时对每一位进行运算时，必须进行错位相加。

分析c数组（即答案）下标的变化规律，可以写出如下关系式：c[ i ]=c'[ i ]+c''[ i ]+…。由此可见，c[ i ]和a[ i ] × b[ j ]乘积有关，跟上次的进位有关，还跟原c[ i ]的值有关，分析下标规律，有c[ i + j - 1 ]=a[ i ] × b[ i ] + x + c[ i + j - 1 ] ; x = c[ i + j - 1 ] / 10 ; c[ i + j - 1 ] %= 10。

附AC程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=2005;
char a1[MAX],b1[MAX];
int a[MAX],b[MAX],c[MAX*10],lena,lenb,lenc,i,j,x;//c为最终答案 
int main()
{
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	cin>>a1>>b1;
	lena=strlen(a1);
	lenb=strlen(b1);
	for(i=0;i<=lena-1;i++)
		a[lena-i]=a1[i]-48;
	for(i=0;i<=lenb-1;i++)
		b[lenb-i]=b1[i]-48;
	for(i=1;i<=lena;i++)
	{
		x=0;//存放进位 
		for(j=1;j<=lenb;j++)//对乘数每一位进行处理 
		{
			c[i+j-1]=a[i]*b[j]+x+c[i+j-1];//当前乘积+上次成绩进位+原数
			x=c[i+j-1]/10;
			c[i+j-1]%=10;
		}
		c[i+lenb]=x;//进位 
	}
	lenc=lena+lenb;
	while(c[lenc]==0&&lenc>1)//删除前导0 
		lenc--;
	for(i=lenc;i>=1;i--)
		cout<<c[i];
	cout<<endl;
	return 0;
}
```

---

## 作者：3278075254zwjm (赞：5)

为什么要用C++？？\
还得写高精太TM麻烦 	qwq     
 _ _~~主要还是不会~~\__  
用python岂不是美极了？？\
~~虽说pyhon不能参加竞赛~~   emmmm就当我什么也没说\
好了，奉上代码:~~(不知道为啥用python的请离开。。。)~~\
```python
num1=int(input())       #输入为int类型
num2=int(input())	#不解释
print(num1*num2,end='') #输出结果
```
~~我绝对不会告诉你们,python自带高精！！~~\
我什么也没说，请当我放个屁.



我的博客:[传送门](https://www.luogu.org/blog/zwjm/)

# 管理大大求过         


------------------------无用的内容------------------------
```cpp
#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;
int main()
{
  string print("我还是忠实的C++党！~~管理大大,求过~~");
  for(i=0;;i++)
  {
  	cout<<print[i];
  Sleep(300);
  }
}
```


---

## 作者：蒟蒻CGZ (赞：3)

在讲这道题之前，我有必要先从高精度加/减法来引入一下。

高精度加减法最重要的是什么？当然是对齐数位了！那么，为了达到这一点，我们不惜要先将输入倒序存储，高精乘也是这样。下面，拿一张表格来示意一下高精度加法的运算过程：

|  | 2 | 0 | 0 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| + | 1 | 9 | 0 | 2 | 3 |
| = | 3 | 9 | 0 | 7 | 9 |

那么高精乘呢？他们也需要判定位置关系，只不过关系表达式用坐标表示是这样的：a[i]*b[j]==c[i,j]//乘数 * 乘数=乘积。

我们先上核心代码，你可以在其中看到这个关系表达式的体现。

## 核心代码

```
//这是核心的计算过程
for(int i=1;i<=lena;i++)
    {
        x=0;
        for(int j=1;j<=lenb;j++)
        {
            c[i+j-1]=a[i]*b[j]+x+c[i+j-1];
            	//当前乘积+上次乘积进位+原数（划重点）
            x=c[i+j-1]/10;
            c[i+j-1]%=10;
        }
        c[i+lenb]=x;
    }
```

看到了吗？好的，现在我们来看如何删除前导0，这可是很关键的一步哦。

## 删除前导0

```
while(lenc>1&&c[lenc]==0)
	lenc--;
```
我们通过从最高位开始，逐个检测是否有0，来缩小输出的范围。如：001723(有0) ==> 01723(有0) ==>1723(无0)

## 程序

```
#include<bits/stdc++.h>//万能库
using namespace std;
const int maxn=1e6+7;
char a1[maxn],b1[maxn];
int a[maxn],b[maxn],c[maxn*10],lena,lenb,lenc,x;
int main()
{
    scanf("%s",a1);
    scanf("%s",b1);
    lena=strlen(a1);
    lenb=strlen(b1);
    for(int i=0;i<lena;i++)a[lena-i]=a1[i]-'0';
    for(int i=0;i<lenb;i++)b[lenb-i]=b1[i]-'0';
    for(int i=1;i<=lena;i++)
    {
        x=0;
        for(int j=1;j<=lenb;j++)
        {
            c[i+j-1]=a[i]*b[j]+x+c[i+j-1];
            x=c[i+j-1]/10;
            c[i+j-1]%=10;
        }
        c[i+lenb]=x;
    }
    lenc=lena+lenb;
    while(c[lenc]==0&&lenc>1) lenc--;
    for(int i=lenc;i>=1;i--) cout<<c[i];
    return 0;
}
```
作者其他题解地址：[作者博客](https://www.luogu.org/blog/cgz2006/#)

~~cgz出品，必是精品。~~

---

## 作者：MambaHJ (赞：3)

高精度的模板，思路和大家差不多就是模拟人的竖式计算(概念可以戳这篇[博客: 高精度与压位](https://blog.csdn.net/devillaw_zhc/article/details/7776578))，为了直观我把要点做个引用：

>1.加法 
就是 从个位开始 两个数字相加，如果有进位，就加到十位，再算十位相加。

>2.减法 

>也是从个位开始 两个数字相减，如果得到的数字小于 0，那么就加上 10，并且把被减数的十位减一。

>3.乘法 

>第一个数乘以第二个数的个位，写下来，右边与个位对齐，再与第二个数的十位相乘，右边与十位对齐。

>仔细想一想，会发现其实 第一个数 从右数起的第 i 位，不妨设为 2 乘以 第二个数从右数起的第 j 位，不妨设为 8，就相当于 2*10^(i-1) * 8*10^(j-1)

>这个乘积所贡献的就是 答案从右数起的 第 i+j-1 位， 即 16 *10^(i+j-2) ，把 1 进位到 从右数起的第 i+j 位上，留下 6 即可。

>4.除法 

>除法其实是减法的延伸，打个比方，24723 除以 123 。

>按照人的做法，从高位开始一位一位取出被除数的数字

>先是 2，判断是否小于 123， 小于那答案这一位就置 0

>再取一位，24， 还是小于，答案这一位置0

>再取一位，247，这时候比 123 大了，那就看能减多少个 123， 发现减 2 次之后比 123 小了，那么答案的第 3 位上就是2， 减剩下的数是 1  

>重复那个过程，取一位，12， 小于 123 ，答案这一位置 0

>再取一位， 123， 不小于 123 了， 看能减多少个， 发现能减一个， 那么答案第 5 位就是 1 

>剩下的数为 0 ， 而被除数的数也被取光了，运算结束。
>答案为 00201 ，整理一下即为 201。




- 这里给出c++带**重载**和**压位**的高精度加减乘除**通用模板**。

几个注意点：

1. 减法时要注意先判断哪个大那个小，大的要在前面，用swap函数对换，然后再进行运算 ~~(因为我没把这个步骤写进减法的重载里)~~

2. 乘法时要特判 0 * x的情况，模板里有写

其它的注意点，注释里都有写。


```
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
const int power = 1;	// 压位时的位数
const int base = 10;	// 压位的基数，10的power次方

char a[maxl], b[maxl];

struct HighPercision{
	int a[maxl];	// a[0]存放位数，a[1]开始逆序存放运算数

	HighPercision(){
		memset(a, 0, sizeof(a));
	}

	HighPercision(char *s){
		memset(a, 0, sizeof(a));
		int len = strlen(s);
		a[0] = (len + power - 1) / power;		// 考虑压位时的长度
		for (int i = 0, w, t = 0; i < len; w *= 10, ++i){
			if (i % power == 0){
				w = 1, ++t;
			}
			a[t] += w * (s[i] - '0');
		}
	}
	/* 除法时要正序存放，要把a[0]放到最后 */
	void add(int k){
		if (k || a[0])
			a[++a[0]] = k;
	}
	/* 除法时，要正过来放数字 */
	void re(){
		reverse(a + 1, a + a[0] + 1);
	}

	void print(){
		if (a[a[0]] == 0){		// 特判 0 * x 的情况
			printf("0\n");
			return;
		}
		printf("%d", a[a[0]]);
		for (int i = a[0] - 1; i > 0; --i){
			//这里"%0*d", power的意思是，必须输出power位，不够则前面用0补足
			printf("%0*d", power, a[i]);
		}
		printf("\n");
	}
}p, q, ans;

bool operator < (const HighPercision &p, const HighPercision&q){
	if (p.a[0] < q.a[0])
		return true;
	if (p.a[0] > q.a[0])
		return false;
	for (int i = p.a[0]; i > 0; --i){
		if (p.a[i] != q.a[i])
			return p.a[i] < q.a[i];
	}
	return false;
}

HighPercision operator + (const HighPercision &p, const HighPercision &q){
	HighPercision c;
	c.a[0] = max(p.a[0], q.a[0]);
	for (int i = 1; i <= c.a[0]; ++i){
		c.a[i] += p.a[i] + q.a[i];
		c.a[i + 1] += c.a[i] / base;
		c.a[i] %= base;
 	}
 	if (c.a[a[0] + 1])
 		++c.a[0];
 	return c;
}

HighPercision operator - (const HighPercision &p, const HighPercision &q){
	HighPercision c = p;
	for (int i = 1; i <= c.a[0]; ++i){
		c.a[i] -= q.a[i];
		if (c.a[i] < 0){
			c.a[i] += base;
			--c.a[i + 1];
		}
	}
	while (c.a[0] > 0 && !c.a[c.a[0]])
		--c.a[0];
	return c;
}

HighPercision operator * (const HighPercision &p, const HighPercision &q){
	HighPercision c;
	c.a[0] = p.a[0] + q.a[0] - 1;
	for (int i = 1; i <= p.a[0]; ++i){
		for (int j = 1; j <= q.a[0]; ++j){
			c.a[i + j - 1] += p.a[i] * q.a[j];
			c.a[i + j] += c.a[i + j - 1] / base;
			c.a[i + j - 1] %= base;
		}
	}
	if (c.a[c.a[0] + 1])
 		++c.a[0];
 	return c;
}

HighPercision operator / (const HighPercision &p, const HighPercision &q){
	HighPercision x, y;
	for (int i = p.a[0]; i > 0; --i){
		y.add(p.a[i]);
		y.re();
		while (!(y < q)){	// 因为只重载了 < 所以这里写的有点变扭
			y = y - q;
			++x.a[i];
		}
		y.re();
	}
	x.a[0] = p.a[0];
	while (x.a[0] > 0 && !x.a[x.a[0]])
		--x.a[0];
	return x;
}

int main(int argc, char const *argv[]){
	scanf("%s", a);
	scanf("%s", b);
	reverse(a, a + strlen(a));
	reverse(b, b + strlen(b));
	p = HighPercision(a);
	q = HighPercision(b);
	ans = p * q;
	ans.print();
	return 0;
}
```


---

## 作者：abruce (赞：3)

### 蒟蒻只会模拟，只有靠小学知识算  
~~实际上就是模拟乘法竖式~~  
#### 用图说话（67*43）  
![](https://cdn.luogu.com.cn/upload/pic/32940.png)  
实际上就是高精乘一位+高精度加法  
话不多说，上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string times_gj(string a,char b,int stp)//高精乘一位函数(string)
{
    string s="";
    int i_jw=0,p;//i_jw是进位
    for(int i_t=a.length()-1;i_t>=0;i_t--)
      {
      	p=int(a[i_t]-48)*(int(b)-48)+i_jw;//-48==-'0'
      	i_jw=p/10;//算进位
      	p%=10;//剩余
      	s=char(p+48)+s;//结果加上
      }//乘法
    for(int i_t=1;i_t<=stp;i_t++)s=s+'0';//处理末尾的0（加法要用）
    return s;//让主函数调用
} 
string pls_gj(string a,string b)//加法函数，可参考P1601的题解（虽然我没有发）但一定要是string
{
    int i_jw1=0,s1=0;//i_jw1与i_jw同理
    string x="";//注意是空字符串，不是空格！
    while(b.length()<a.length())
    {
        b='0'+b;
    }
    while(a.length()<b.length())
    {
        a='0'+a;
    }//加法-前面加0
    a='0'+a;
    b='0'+b;
    for(int i_p=a.length()-1;i_p>=0;i_p--)
    {	   
        s1=int(a[i_p])+int(b[i_p])-96+i_jw1;//-96的原因是减2个48，可替换为int(a[i_p])+int(a[i_p])-int('0'+'0')
        i_jw1=s1/10;//算进位
        s1=s1%10;//剩余
        x=char(s1+48)+x;//结果加上		
    }//加法-主运算
    
    int j=x.length()-1;
    while(x[0]=='0'&&x.length()>1)
    {
        x=x.erase(0,1); 
    }//删除0的erase函数，可参考 https://www.cnblogs.com/loda333/p/5229980.html
    s1=0;
    return x; 
}
int nain()//注意看，有没有问题
{
    string a,b,c="",p;//跟第一个空字符串同理
    int j1=0;
    cin>>a>>b;//输入字符串
    a='0'+a;
    for(int i=b.length()-1;i>=0;i--)
    {
        p=times_gj(a,b[i],j1);
        c=pls_gj(c,p);
        j1++;//模拟竖式加法
    }
    cout<<c;
    return 0;//perfect
}
```
时间--752ms（没有用氧气优化）

---

## 作者：darkblue (赞：3)

没有用ruby的吗= =

ruby好像不怎么受欢迎

非常简洁的代码，速度比python还慢
```ruby
puts gets.to_i*gets.to_i
//对比python print(int(input())+int(input()))
```

自带大数字的语言
调用函数不用()

这些优雅的语言似乎都比较慢，还是解释性语言的问题= =？
感觉适合用来开发，不很适合解题

---

## 作者：LightningUZ (赞：3)

在家闲的没事做了一个用结构体封装的小数高精版本

提交上去是可以AC的哦

分享一下我的高精度小数代码
```cpp
#include<bits/stdc++.h>
#define mx 50001
const int dot=-129931;
using namespace std;
struct lld
{
	int n[mx];
	int l=mx;
	void put()
	{
		if (n[0]==dot) cout<<0;
		for(int i=0;i<l;i++)
		{
			if (n[i]==dot)
			{
				cout<<'.';
			}
			else
			{
				cout<<n[i];
			}
		}
		cout<<endl;
	}
	void str_arr(string s)
	{
		for(int i=0;i<s.size();i++)
		{
			n[i]=s[i]-'0';
			if (s[i]=='.') n[i]=dot;
		}
		l=s.size();
	}
	int type()
	{
		for(int i=0;i<l;i++)
		{
			if (n[i]==dot) return -1;
		}
		return 1;
	}
	int dotpos()
	{
		int pos=l;
		for(int i=0;i<l;i++)
		{
			if (n[i]==dot) return i; 
		}
		return pos;
	}
	int ilen()
	{
		int pos=dotpos();
		int tot=0;
		for(int i=0;i<=pos-1;i++)
		{
			tot++;
		} 
		return tot;
	}
	int flen()
	{
		int pos=dotpos();
		int tot=0;
		for(int i=pos+1;i<l;i++)
		{
			tot++;
		} 
		return tot;
	}
	void time_i(int x)
	{
		reverse(n,n+l);
		for(int i=0;i<l;i++)
		{
			if (n[i]!=dot)
			{
				n[i]*=x;
			}
		}
		l+=10;
		for(int i=0;i<l;i++)
		{
			if (n[i]>9)
			{
				if (n[i+1]!=dot)
				{
					n[i+1]+=n[i]/10;
					n[i]%=10;
				}
				else
				{
					n[i+2]+=n[i]/10;
					n[i]%=10;
				}	
			}
		} 
		while(n[l-1]==0) l--;
		reverse(n,n+l);
	} 
};
void read(lld &a)
{
	string s;
	cin>>s;
	a.str_arr(s);
}
bool operator<(lld a,lld b)
{
	int ila,ilb;
	ila=a.ilen();
	ilb=b.ilen();
	if (ila<ilb) return true;
	else if (ila>ilb) return false;
	else
	{
		int la,lb;
		la=a.l;
		lb=b.l;
		int l=max(a.l,b.l);
		int cmp[mx][5];
		memset(cmp,0,sizeof(cmp));
		if (ilb<ila)
		{
			for(int i=0;i<la;i++)
			{
				cmp[i+1][1]=a.n[i];
			}
			int num=ila-ilb;
			for(int i=1;i<=num;i++)
			{
				cmp[i][2]=0;
			}
			for(int i=num+1;i<=la;i++)
			{
				cmp[i][2]=b.n[i-num-1];
			}
		} 
		else if (ilb<=ila)
		{
			for(int i=0;i<lb;i++)
			{
				cmp[i+1][1]=b.n[i];
			}
			int num=ilb-ila;
			for(int i=1;i<=num;i++)
			{
				cmp[i][2]=0;
			}
			for(int i=num+1;i<=la;i++)
			{
				cmp[i][2]=a.n[i-num-1];
			}
		}
		for(int i=1;i<=l;i++)
		{
			if (cmp[i][1]<cmp[i][2]) return false;
			if (cmp[i][1]>cmp[i][2]) return true;
		}
		return false;
	}
}
lld operator+(lld a,lld b)
{
	lld c;
	memset(c.n,0,sizeof(c.n));
	int fla,flb,ila,ilb;
	int la,lb;
	la=a.l;
	lb=b.l;
	fla=a.flen();
	flb=b.flen();
	ila=a.ilen();
	ilb=b.ilen();
	int sum[mx][5];
	memset(sum,0,sizeof(sum));
	int l=max(la,lb);
	if (ilb>ila)
	{
		for(int i=0;i<l;i++)
		{
			sum[i+1][1]=b.n[i];
		}
		int num=ilb-ila;
		for(int i=1;i<=num;i++)
		{
			sum[i][2]=0;
		}
		for(int i=num+1;i<=l;i++)
		{
			sum[i][2]=a.n[i-num-1];
		}
	} 
	else if (ilb<=ila)
	{
		for(int i=0;i<l;i++)
		{
			sum[i+1][1]=a.n[i];
		}
		int num=ila-ilb;
		for(int i=1;i<=num;i++)
		{
			sum[i][2]=0;
		}
		for(int i=num+1;i<=l;i++)
		{
			sum[i][2]=b.n[i-num-1];
		}
	}
	for(int i=l+1;i>=0;i--)
	{
		if (sum[i][2]!=dot)
		{
			sum[i][3]+=sum[i][2]+sum[i][1];
			if (sum[i][3]>9)
			{
				if (sum[i-1][2]!=dot)
				{
					sum[i-1][3]+=1;
					sum[i][3]-=10;
				}
				else if (sum[i-1][2]==dot)
				{
					sum[i-2][3]+=1;
					sum[i-1][3]=dot;
					sum[i][3]-=10;
				}
			}
		}
		else
		{
			sum[i][3]=dot;
		}
	}
	int _l=1,_r=l;
	for(int i=l;i>=0;i--)
	{
		if (sum[i][3]!=0)
		{
			_l=i;
		}
	}
	int d_pos=l;
	for(int i=0;i<=l;i++)
	{
		if (sum[i][3]==dot) 
		{
			d_pos=i;
			break; 
		}
	}
	for(int i=d_pos;i<=l;i++)
	{
		if (sum[i][3]!=0)
		{
			_r=i;
		}
	}
	if (sum[_r][3]==dot) _r--;
	for(int i=_l,t=0;i<=_r;i++,t++)
	{
		c.n[t]=sum[i][3];
	}
	c.l=_r-_l+1;
	return c;
}
lld operator-(lld a,lld b)
{
	lld c;
	memset(c.n,0,sizeof(c.n));
	int fla,flb,ila,ilb;
	int la,lb;
	la=a.l;
	lb=b.l;
	fla=a.flen();
	flb=b.flen();
	ila=a.ilen();
	ilb=b.ilen();
	int sum[mx][5];
	memset(sum,0,sizeof(sum));
	int l=max(la,lb);
	if (ilb<=ila)
	{
		for(int i=0;i<l;i++)
		{
			sum[i+1][1]=a.n[i];
		}
		int num=ila-ilb;
		for(int i=1;i<=num;i++)
		{
			sum[i][2]=0;
		}
		for(int i=num+1;i<=l;i++)
		{
			sum[i][2]=b.n[i-num-1];
		}
	}
	for(int i=l+1;i>=1;i--)
	{
		if (sum[i][2]!=dot)
		{
			sum[i][3]+=sum[i][1]-sum[i][2];
		}
		else
		{
			sum[i][3]=dot;
		} 
	}
	for(int i=l+1;i>=1;i--)
	{
		if (sum[i][3]<0 and sum[i][3]!=dot)
		{
			if (sum[i-1][3]!=dot)
			{
				sum[i-1][3]-=1;
				sum[i][3]+=10;
			}
			else
			{
				sum[i][3]+=10;
				sum[i-2][3]-=1;
			}
		}
	}
	int _l=1,_r=l;
	for(int i=l;i>=0;i--)
	{
		if (sum[i][3]!=0)
		{
			_l=i;
		}
	}
	int d_pos=l;
	for(int i=0;i<=l;i++)
	{
		if (sum[i][3]==dot) 
		{
			d_pos=i;
			break; 
		}
	}
	for(int i=d_pos;i<=l;i++)
	{
		if (sum[i][3]!=0)
		{
			_r=i;
		}
	}
	if (sum[_r][3]==dot) _r--;
	for(int i=_l,t=0;i<=_r;i++,t++)
	{
		c.n[t]=sum[i][3];
	}
	c.l=_r-_l+1;
	return c;
}
lld fuck_dot(lld a)
{
	lld tmp;
	tmp.l=a.l;
	int pos=0;
	for(int i=0;i<a.l;i++)
	{
		if (a.n[i]!=dot)
		{
			tmp.n[pos]=a.n[i];
			pos++;
		}
	}
	tmp.l=pos;
	return tmp;
}
void fan(lld &a)
{
	int l=0,r=a.l-1;
	while(l<=r)
	{
		swap(a.n[l],a.n[r]);
		l++,r--;
	}
}
bool is0(lld a)
{
	if (a.l==1 and a.n[0]==0)return true;
	else return false;
}
lld operator*(lld _a,lld _b)
{
	if (is0(_a) or is0(_b))
	{
		lld c;
		c.n[0]=0;
		c.l=1;
		return c;
	}
	int fl;
	fl=_a.flen()+_b.flen();
	lld a,b;
	a=fuck_dot(_a);
	b=fuck_dot(_b);
	fan(a);
	fan(b);
	lld c;
	int l=a.l+b.l+10;
	c.l=l;
	for(int i=0;i<a.l;i++)
	{
		for(int j=0;j<b.l;j++)
		{
			c.n[i+j]+=a.n[i]*b.n[j];
		}
	}
	for(int i=0;i<l;i++)
	{
		if (c.n[i]>9)
		{
			c.n[i+1]+=c.n[i]/10;
			c.n[i]%=10;
		}
	}
	while(c.n[l-1]==0) l--;
	c.l=l;
	if (c.l<fl)
	{
		for(int i=1;i<=fl;i++)
		{
			c.n[c.l]=0;
			c.l++;
		}
	}
	fan(c);
	lld t=c;
	memset(c.n,0,sizeof(c.n));
	int pos=0;
	for(int i=0;i<t.l;i++)
	{
		c.n[pos]=t.n[i];
		pos++;
		if (i+fl+1==t.l)
		{
			c.n[pos]=dot;
			pos++;
		}
	}
	c.l=pos;
	if (c.n[c.l-1]==dot)
	{
		c.n[c.l-1]=0;
		c.l--;
	}
	fan(c);
	while(c.n[c.l-1]==0) c.l--;
	if (c.n[c.l-1]==dot) c.l++;
	fan(c);
	return c;
} 
struct chu
{
	int num;
	int p;
};
lld operator/(lld a,chu _b)
{
	if (_b.num==0)
	{
		cout<<"\007[ERROR]divisitor cannot be zero"<<endl;
		exit(0);
	}
	int b=_b.num;
	int pct=_b.p;
	lld c=a;
	int fl=c.flen();
	if (fl>pct)
	{
		while(fl>pct)
		{
			c.n[c.l-1]=0;
			fl--;
			c.l--;
		}
	}
	else if (fl<pct)
	{
		if (c.n[c.l-1]!=dot)
		{
			c.n[c.l]=dot;
			c.l++;
		} 
		while(fl<pct)
		{
			c.n[c.l]=0;
			fl++;
			c.l++;
		}
	}
	int pos=c.dotpos();
	for(int i=0;i<pos;i++)
	{
		c.n[i]=0;
	}
	for(int i=pos+1;i<c.l;i++)
	{
		c.n[i]=0;
	}
	for(int i=0;i<c.l;i++)
	{
		if (c.n[i]!=dot)
		{
			c.n[i]=a.n[i]/b;
			if (c.n[i+1]!=dot)
			{
				a.n[i+1]+=a.n[i]%b*10;
			}
			else
			{
				a.n[i+2]+=a.n[i]%b*10;
			}
		}
		else
		{
			a.n[i]=dot;
		}
	}
	fan(c);
	while(c.n[c.l-1]==0) c.l--;
	fan(c);
	return c;
}
lld operator^(lld a,int p)
{
	if (is0(a))
	{
		lld c;
		c.str_arr("0");
		c.l=1;
		return c;
	}
	int fl=a.flen()*p;
	fuck_dot(a);
	int num=0;
	for(int i=0;i<a.l;i++)
	{
		num*=10;
		num+=a.n[i];
	}
	lld t;
	t.str_arr("1");
	for(int i=1;i<=p;i++)
	{
		t.time_i(num);
	}
	lld c;
	int nc=0;
	for(int i=0;i<t.l;i++)
	{
		c.n[nc]=t.n[i];
		nc++;
		if (i+fl+1==t.l)
		{
			c.n[nc]=dot;
			nc++;
		}
	}
	c.l=nc;
	if(c.n[c.l-1]==dot)
	{
		c.n[c.l-1]=0;
		c.l--;
	} 
	return c;
}
lld operator!(lld a)
{
	int num=0;
	for(int i=0;i<a.l;i++)
	{
		num*=10;
		num+=a.n[i];
	}
	lld c;
	c.str_arr("1");
	for(int i=1;i<=num;i++)
	{
		c.time_i(i);
	}
	return c;
}
lld a,b;
lld c;
int main()
{
	memset(a.n,0,sizeof(a.n));
	memset(b.n,0,sizeof(b.n));
	read(a);
	char f;
	f='*'; 
	if (f=='+')
	{
		read(b);
		c=a+b;
		c.put();
		exit(0);
	}
	else if (f=='-')
	{
		read(b);
		if (a<b)
		{
			cout<<'-';
			swap(a,b);
		}
		c=a-b;
		c.put();
		exit(0);
	}
	else if (f=='*')
	{
		read(b);
		c=a*b;
		c.put();
		exit(0);
	}
	else if (f=='/')
	{
		chu _b;
		cin>>_b.num>>_b.p;
		c=a/_b;
		c.put();
		exit(0);
	}
	else if (f=='^')
	{
		int _b;
		cin>>_b;
		lld c=a^_b;
		c.put();
		exit(0);
	}
	else if (f=='!')
	{
		lld c=!a;
		c.put();
		exit(0);
	}
}
```

装完B讲讲这道题

本题就是基础高精

### 只要背代码即可
```cpp
#include<bits/stdc++.h>
#define mx 50001
using namespace std;
struct lld
{
	int n[mx];
	int l=mx;
	void put()//输出
	{
		for(int i=0;i<l;i++)
		{
			cout<<n[i];
		}
		cout<<endl;
	}
	void str_arr(string s)//字符串转数组
	{
		for(int i=0;i<s.size();i++)
		{
			n[i]=s[i]-'0';
		}
		l=s.size();
	}
};
void read(lld &a)//别想了这不是读入挂
{
	string s;
	cin>>s;
	a.str_arr(s);
}
void fan(lld &a)//相当于reverse，但reverse长，干脆自己写
{
	int l=0,r=a.l-1;
	while(l<=r)
	{
		swap(a.n[l],a.n[r]);
		l++,r--;
	}
}
bool is0(lld a)//判断是否为0
{
	if (a.l==1 and a.n[0]==0)return true;
	else return false;
}
lld operator*(lld a,lld b)
{
	if (is0(a) or is0(b))//判0
	{
		lld c;
		c.n[0]=0;
		c.l=1;
		return c;
	}
	fan(a);
	fan(b);
	lld c;
	int l=a.l+b.l+10;
	c.l=l;
	for(int i=0;i<a.l;i++)
	{
		for(int j=0;j<b.l;j++)
		{
			c.n[i+j]+=a.n[i]*b.n[j];//关键
		}
	}
	for(int i=0;i<l;i++)
	{//进位
		if (c.n[i]>9)
		{
			c.n[i+1]+=c.n[i]/10;
			c.n[i]%=10;
		}
	}
	while(c.n[l-1]==0) l--;//去0
	c.l=l;
	fan(c);
	return c;
} 
lld a,b;
lld c;
int main()
{
	memset(a.n,0,sizeof(a.n));
	memset(b.n,0,sizeof(b.n));
	read(a);
	read(b);
	c=a*b;
	c.put();
	exit(0); 
}
```

---

## 作者：哔哩哔哩 (赞：2)

### 【思路】
重载运算符“-”，必须注意的是，特殊处理0与数相乘（第一个数据）  
### 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=10,P=1; 

struct BigNum
{
       int n[20000],l,Y;//最大20000位
       BigNum(){l=1,memset(n,0,sizeof(n));}//初始化
       //----------------------分割线------------
       void init()//读入
       {
            string s;cin>>s;//用字符串的形式来储存
            int now=0,ct=0,c1=1;//初始
            for(int i=s.length()-1;i>=0;i--)//每一位判断
            {
             n[now]+=(s[i]-'0')*c1;c1*=10;ct++;
             if(ct==P&&i!=0){now++;c1=1;ct=0;}        
            }
            l=now+1;     
       }
       //----------------------分割线------------
       void print()//输出
       {
       		if(n[l-1]==0){printf("0");exit(0);}//注意，这里对0特殊处理,exit(0)是退出全部
            printf("%d",n[l-1]);
            for(int i=l-2;i>=0;i--) printf("%0*d",P,n[i]);
            printf("\n");
       }
       //----------------------分割线------------
       /*BigNum operator +(BigNum x)const
       {
              BigNum t=*this;
              if(x.l>t.l)t.l=x.l;
              for(int i=0;i<t.l;i++)
              {
               t.n[i]+=x.n[i];
               if(t.n[i]>=M){t.n[i+1]+=t.n[i]/M;t.n[i]%=M;}       
              }
              while(t.n[t.l])
              {
                  t.n[t.l+1]+=t.n[t.l]/M;
                  t.n[t.l++]%=M;               
              }     
              return t;  
       }
       //----------------------分割线------------
       bool operator < (BigNum x) const
       {
           BigNum t=*this;
           if(t.l!=x.l)return t.l<x.l;
           for(int i=t.l-1;i>=0;i--)
           {
              if(t.n[i]!=x.n[i])return t.n[i]<x.n[i];        
           }
           return 0;       
       }
       BigNum operator -(BigNum x)const
       {
           BigNum t=*this;
           if(t<x){printf("-");swap(t,x);} 
           for(int i=0;i<t.l;i++)
           {
            t.n[i]-=x.n[i];
            if(t.n[i]<0)
            {
                t.n[i]+=M;
                --t.n[i+1];            
            }        
           } 
           while(!t.n[t.l-1]&&t.l>1)t.l--;
           return t;     
       }
       //----------------------分割线------------以上这些事其他运算符号的重载，本题可不用*/
       BigNum operator * (BigNum x) const
       {
              BigNum c,t=*this;
              c.l=t.l+x.l-1;
              for(int i=0;i<t.l;i++)
              for(int j=0;j<x.l;j++)
              {
                  c.n[i+j]+=t.n[i]*x.n[j];
                  if(c.n[i+j]>=M)
                  {
                      c.n[i+j+1]+=c.n[i+j]/M;
                      c.n[i+j]%=M;               
                  }        
              }
              while(c.n[c.l])
              {
                   c.n[c.l+1]+=c.n[c.l]/M;
                   c.n[c.l++]%=M;               
              }       
              return c;
       }
       /*
       //----------------------分割线------------
    void Add(int x){if(x||l)n[l++]=x;}
    void Re(){reverse(n,n+l);}
    BigNum operator /(const BigNum &x)const
    {
        BigNum t=*this,r,y;
        y.l=0,r.l=t.l;
        for(int i=t.l-1;i>=0;--i)
        {
            y.Add(t.n[i]);
            y.Re();
            while(!(y<x))y=y-x,r.n[i]++;
            while(!y.n[y.l-1] && y.l>1)--y.l;
            y.Re();
        }
        while(!r.n[r.l-1] && r.l>1)--r.l;
        return r;
    }
    BigNum operator /(const int &x)const
    {
        BigNum t=*this,r;
        r.l=t.l;
        int tmp=0;
        for(int i=t.l-1;i>=0;--i)
        {
            tmp+=t.n[i];
            if(tmp>=x)
                r.n[i]+=tmp/x,tmp%=x;
            tmp*=M;
        }
        while(!r.n[r.l-1] && r.l>1)--r.l;
        return r;
    }
       //----------------------分割线------------
       */
}a,b,c;//给a,b,c定义
 
int main()//简单的主程序
{
    a.init();
    b.init();
    c=a*b;
    c.print();
    return 0;        
}
```

---

## 作者：Timothy (赞：2)

简短易懂的代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
char a1[50001],b1[50001];
int a[50001],b[50001],i,x,len,j,c[50001];
int main ()
{
    cin >>a1 >>b1;//读入两个数
    a[0]=strlen(a1);b[0]=strlen(b1);//计算长度
    for (i=1;i<=a[0];++i)a[i]=a1[a[0]-i]-'0';//将字符串转换成数字
    for (i=1;i<=b[0];++i)b[i]=b1[b[0]-i]-'0';
    for (i=1;i<=a[0];++i)for (j=1;j<=b[0];++j)c[i+j-1]+=a[i]*b[j];//按乘法
    len=a[0]+b[0];                                       //原理进行高精乘
    for (i=1;i<len;++i)if (c[i]>9){c[i+1]+=c[i]/10;c[i]%=10;}//进位
    while (c[len]==0&&len>1)len--;//判断位数
    for (i=len;i>=1;--i)cout <<c[i];//输出
    return 0;
}

```

---

## 作者：君笙拂兮 (赞：1)

```cpp
#include<bits/stdc++.h>   //万能头文件
#define LL long long
using namespace std;
string x,y;
LL a[100010],b[100010],c[100010],i,j;
int main(){
	cin>>x>>y;
	int x1=x.size(),y1=y.size();
	int xy=x1+y1;
	for(i=0;i<x1;i++) a[i]=x[x1-i-1]-'0';
	for(i=0;i<y1;i++) b[i]=y[y1-i-1]-'0';
	if(a[0]==0 || b[0]==0) return cout<<0,0;//0要特殊判定
	for(i=0;i<x1;i++)
		for(j=0;j<y1;j++)
			c[i+j]+=a[i]*b[j];//乘法计算
	for(i=0;i<xy;i++){
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}//进位
	if(c[xy-1]==0) xy--;//特殊判定
    for(i=xy-1;i>=0;i--) cout<<c[i];//输出
	return 0;
}```

---

## 作者：dashuaibifqw (赞：1)

高精度算法， 每个人都应该掌握！！！！！！！！！！！！

源程序：

```cpp
const   max=200;
var  a,b,c:array[1..max] of 0..9;
       n1,n2:string;
       lena,lenb,lenc,i,j,x:integer;
begin
      readln(n1);  readln(n2);                                                     //读入
     lena:=length(n1); lenb:=length(n2);
     for i:=1 to lena do a[lena-i+1]:=ord(n1[i])-ord('0');
     for i:=1 to lenb do b[lenb-i+1]:=ord(n2[i])-ord('0');
     for i:=1 to lena do
       begin
         x:=0;                                                                  //用于存放进位
         for j:=1 to lenb do
           begin                                                                      //对乘数的每一位进行处理
             c[i+j-1] := a[i]*b[j] + x + c[i+j-1];                             //当前乘积+上次乘积进位+原数
             x:=c[i+j-1] div 10;   c[i+j-1] := c[i+j-1] mod 10;
          end;
         c[i+j]:= x;                                                      //进位
       end;
     lenc:=i+j;
     while (c[lenc]=0) and (lenc>1) do dec(lenc);
     for i:=lenc downto 1 do write(c[i]);
     writeln;                                                            //输出
end.
```

---

## 作者：封禁用户 (赞：1)

此题先将字符串倒序并变成int类型，然后一遍乘，一遍来进位，最后按最高位倒序输出即可。

代码附上


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;
int main()
{
    char a[3000] , b[3000];
    int n[3000]={} , m[3000]={} , result[3000] = {};
    int la , lb , i , j , w = 0;
    int k = w;
    cin  >> a >> b;
    la = strlen(a);
    lb = strlen(b);
    for(i = 0;i < la;i++) n[i] = a[la-i-1] - '0';
    for(i = 0;i < lb;i++) m[i] = b[lb-i-1] - '0';
    for(i = 0;i < la;i++)
       for(j = 0;j < lb;j++)
       {
              result[i + j] += n[i] * m[j];
              if(result[i + j] != 0) w = i + j;
       }
    for(i = 0;i <= w + 5;i++)
    {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
            if(result[i] != 0) k = i;
    }
    for(i = k;i >= 0;i--)   cout << result[i];
    return 0;
}
```

---

## 作者：斯德哥尔摩 (赞：1)

这题除了高精度，还能用FFT（不知道的可以百度一下，看不懂不要找我.......）

没办法，手残党+1.......（只是花的时间长了一丢丢......）

看代码吧（虽丑）：

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<cmath>
#define N (1<<18)//如果不介意，可以开小点
using namespace std;
struct cmpx{//不一样的结构体，运算符重载
    double r,i;
    cmpx operator + (const cmpx &a)const{return (cmpx){r+a.r,i+a.i};}
    cmpx operator - (const cmpx &a)const{return (cmpx){r-a.r,i-a.i};}
    cmpx operator * (const cmpx &a)const{return (cmpx){r*a.r-i*a.i,r*a.i+i*a.r};}
};
int rev[N];
cmpx A[N],a[N],b[N],c[N];
int L,n;
void DFT(cmpx a[],int f){
     int i,j,k;
     for(i=0;i<L;i++)
     A[i]=a[rev[i]];
     for(i=0;i<L;i++)
     a[i]=A[i];
     for(i=2;i<=L;i<<=1){
                         cmpx wi=(cmpx){cos(2.0*M_PI/i),f*sin(2.0*M_PI/i)};
                         for(k=0;k<L;k+=i){
                                           cmpx w=(cmpx){1.0,0.0},x,y;
                                           for(j=0;j<i/2;j++){
                                                              x=a[k+j];
                                                              y=w*a[k+j+i/2];
                                                              a[k+j]=x+y;
                                                              a[k+j+i/2]=x-y;
                                                              w=w*wi;
                                                              }
                                           }
                         }
  if(f==-1)
  for(i=0;i<L;i++)
  a[i].r/=L;
}
void FFT(cmpx a[],cmpx b[],cmpx c[]){
     int i;
     DFT(a,1);
     DFT(b,1);
     for(i=0;i<L;i++)
     c[i]=a[i]*b[i];
     DFT(c,-1);
}
void init(int tmp){
     int i,t,j;
     for(n=0,L=1;L<tmp;L<<=1)
     n++;
     n++;
     L<<=1;
     for(i=0;i<L;i++)
     for(t=i,j=0;j<n;j++){
         rev[i]<<=1;
         rev[i]|=t&1;
         t>>=1;
         }
}
int ans[N];
void DSC(){//开始处理问题，开始处理问题，开始处理问题，重要的事情说3遍！
     int l1=0,l2=0,i;
     char ch=getchar();
     while(ch>'9'||ch<'0')
     ch=getchar();
     while(ch>='0'&&ch<='9'){
                             a[l1].r=ch-'0';
                             a[l1++].i=0.0;
                             ch=getchar();
                             }
     while(ch>'9'||ch<'0')
     ch=getchar();
     while(ch>='0'&&ch<='9'){
                             b[l2].r=ch-'0';
                             b[l2++].i=0.0;
                             ch=getchar();
                             }
    reverse(a,a+l1);
    reverse(b,b+l2);
    init(max(l1,l2));
    FFT(a,b,c);
    for(i=0;i<L;i++)
    ans[i]=(int)(c[i].r+0.5);
    for(i=0;i<L;i++){
                     ans[i+1]+=ans[i]/10;
                     ans[i]%=10;
                     }
    L=l1+l2+1;
    while(!ans[L]&&L>0)
    L--;
    for(i=L;~i;i--)
    putchar(ans[i]+'0');
    putchar('\n');
}
int main(){//主函数so easy
    DSC();
    return 0;
}

```

---

## 作者：ylsoi (赞：1)

暴力方法，一遍来乘，再一遍来进位！！！！

高精度乘法，但是要注意0作为因数的时候，所以就要有一个判定

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int a[10000],b[10000],c[10000];
char aa[10000],bb[10000];
int main()
{
    scanf("%s",aa);
    scanf("%s",bb);
    if(aa[0]=='0'||bb[0]=='0')//如果只要有一个字符串的首字符为0，那么答案输出0就可以了；
    {
        printf("0");
        return 0;
    }
    int lena=strlen(aa),lenb=strlen(bb);
    for(int i=0;i<=lena-1;i++)//将字符倒着存入数组之中
    a[lena-i]=aa[i]-48;将
    for(int i=0;i<=lenb-1;i++)//将字符倒着存入数组之中
    b[lenb-i]=bb[i]-48;
    int len=max(lena,lenb);//取最长的长度
    for(int i=1;i<=lena;i++)
    {
        for(int j=1;j<=lenb;j++)
        {
            c[i+j-1]+=a[i]*b[j];//一遍来相乘
        }
    }
    for(int i=1;i<=lena+lenb-2;i++)//只进位到倒数第2位，最后一位原样输出就可以了；
    {
        if(c[i]>=10)
        {
            c[i+1]+=c[i]/10;//一遍来进位
            c[i]%=10; 
        }
    }
    for(int i=lena+lenb-1;i>=1;i--)
    printf("%d",c[i]);
    return 0;
}
```

---

## 作者：lowww666 (赞：1)

看到一个这样好的模板题怎么能不来水一发呢？

当然不是高精模板而是FFT快速傅里叶变换的板子……

虽然码长稍感人毕竟复数什么的都是手写的……

时间复杂度：O（nlogn）

空间复杂度：O（懒得算了反正不超限制）

代码：



    



    




    
    

    


```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
const double PI=acos(-1.0);
struct fushu
{
    double R,I;
    void set(double r,double i)
    {
        R=r;
        I=i;
    }
};
fushu operator +(const fushu &a,const fushu &b)
{
    fushu tmp;
    tmp.set(a.R+b.R,a.I+b.I);
    return tmp;
}
fushu operator -(const fushu &a,const fushu &b)
{
    fushu tmp;
    tmp.set(a.R-b.R,a.I-b.I);
    return tmp;
}
fushu operator *(const fushu &a,const fushu &b)
{
    fushu tmp;
    tmp.set(a.R*b.R-a.I*b.I,a.I*b.R+a.R*b.I);
    return tmp;
}
char A[200005],B[200005];
fushu a[400005],b[400005];
int ans[400005];
int len=1;
inline void init()
{
    int len1=strlen(A),len2=strlen(B);
    int len3=len1>len2?len1:len2;
    for(;len<(len3<<1);)
        len<<=1;
    for(int i=0;i<len1;i+=4)
    {
        a[i].set(A[len1-i-1]-48,0);
        a[i+1].set(A[len1-i-2]-48,0);
        a[i+2].set(A[len1-i-3]-48,0);
        a[i+3].set(A[len1-i-4]-48,0);
    }
    for(int i=0;i<len2;i+=4)
    {
        b[i].set(B[len2-i-1]-48,0);
        b[i+1].set(B[len2-i-2]-48,0);
        b[i+2].set(B[len2-i-3]-48,0);
        b[i+3].set(B[len2-i-4]-48,0);
    }
    for(int i=len1;i<len;i++)
        a[i].set(0,0);
    for(int i=len2;i<len;i++)
        b[i].set(0,0);
}
inline void read()
{
    int i=1;
    A[0]=getchar();
    for(;A[i-1]>='0'&&A[i-1]<='9';A[i]=getchar(),i++);
    A[i-1]=0;
    i=1;
    B[0]=getchar();
    for(;B[i-1]>='0'&&B[i-1]<='9';B[i]=getchar(),i++);
    B[i-1]=0;
    if(A[0]=='0'||B[0]=='0')
    {
        printf("0");
        exit(0);
    }
}
inline void swap(fushu &a,fushu &b)
{
    fushu tmp=a;
    a=b;
    b=tmp;
}
inline void ra(fushu y[])
{
    for(int i=1,j=len>>1,k;i<len-1;i++)
    {
        if(i<j)
            swap(y[i],y[j]);
        k=len>>1;
        for(;j>=k;)
        {
            j-=k;
            k>>=1;
        }
        if(j<k)
            j+=k;
    }
}
inline void FFT(fushu y[],int t)
{
    ra(y);
    for(int ii=2;ii<=len;ii<<=1)
    {
        fushu wn,w;
        wn.set(cos(2*PI*t/ii),sin(2*PI*t/ii));
        for(int i=0;i<len;i+=ii)
        {
            w.set(1,0);
            for(int j=i;j<i+(ii>>1);j++)
            {
                fushu u=y[j],tt=w*y[j+(ii>>1)];
                y[j]=u+tt;
                y[j+(ii>>1)]=u-tt;
                w=w*wn;
            }
        }
    }
    if(t<0)
        for(int i=0;i<len;i++)
            y[i].R/=len;
}
inline void solve()
{
    FFT(a,1);
    FFT(b,1);
    for(int i=0;i<len;i++)
        a[i]=a[i]*b[i];
    FFT(a,-1);
    for(int i=0;i<len;i++)
        ans[i]=(int)(a[i].R+0.5);
    for(int i=0;i<len;i++)
    {
        ans[i+1]+=ans[i]/10;
        ans[i]=ans[i]%10;
    }
    for(;ans[len]==0;len--);
}
inline void print()
{
    for(;printf("%d",ans[len])&&len;len--);
}
int main()
{
    read();
    init();
    solve();
    print();
}

```

---

## 作者：Spidey (赞：1)

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 5000
char a1[M+1];
char a2[M+1];
int  s1[M+1];
int  s2[M+1];
int  s3[2*M+1];
int main(){
    memset(s1,0,sizeof(s1));
    memset(s2,0,sizeof(s2));
    memset(s3,0,sizeof(s3));
    int i,j;
    scanf("%s",a1);
    scanf("%s",a2);
    int l1=strlen(a1);
    int l2=strlen(a2);
    for(i=l1-1,j=0;i>=0;i--,j++)
        s1[j]=a1[i]-'0';
    for(i=l2-1,j=0;i>=0;i--,j++)
        s2[j]=a2[i]-'0';
```
/\*
19~22将字符数组中的数据倒序存入整形数组中

\*/
```cpp
    for(i=0;i<l1;i++)
        for(j=0;j<l2;j++)
            {
                s3[i+j]+=s1[i]*s2[j];//由于两数可能是多位数乘多位数，所以要将上面的数字加起来 
                if(s3[i+j]>=10){
                    s3[i+j+1]+=s3[i+j]/10;//处理进位问题 
                    s3[i+j]%=10;//将s3中数据的每位元素上的数字都小于10 
                }        
        }
    i=2*M+1;
    while(s3[i]==0){
        i--;
        if(i<0){
            printf("0");
            return 0;
        }
    }
```
/\*
处理关于0的两个问题

\*/
```cpp
    for(;i>=0;i--){
        printf("%d",s3[i]);//倒序输出 
    }
    return 0;
}
```

---

## 作者：天·三玖 (赞：1)

```cpp
#include<bits/stdc++.h>//我不讲这个了
using namespace std;
int max(int a,int b)//返回最大值
{
    return a>b? a:b;
}
struct Biger{                           //结构体
    int a[65537];
    void FZ(char *b)                   //方便赋值比如给s赋值123456 可以这样s.FZ("123456");
    {
        a[0]=strlen(b);
        for(int i=strlen(b);i>=1;i--)//倒序存储 
        {
            if(b[i-1]=='-')//负数情况
            a[a[0]--]=-1;
            else    
            a[strlen(b)-i+1]=b[i-1]-'0';
        }
    }
    void QF()//负变正，正变负
    {
        if(a[a[0]+1]==-1)
        a[a[0]+1]=0;
        else
        a[a[0]+1]=-1;
    }
    int size()//返回数的长度
    {
        return a[0];
    }
    void OUT()//输出
    {    
        if(a[a[0]+1]==-1)
            printf("-");
        for(int i=a[0];i>=1;i--)
            printf("%d",a[i]);
        printf("\n");
    }
    void IN()//输入
    {
        char b[65537];
        scanf("%s",b);
        a[0]=strlen(b);
        for(int i=strlen(b);i>=1;i--)
        {
            if(b[i-1]=='-')
            a[a[0]--]=-1;
            else    
            a[strlen(b)-i+1]=b[i-1]-'0';
        }
    }
    bool is_fu()//判断是否为负
    {
        return a[a[0]+1]==-1? true:false;
    }    
    void clear()//清空
    {
        memset(a,0,sizeof(a));
        a[0]=1;
    }
    Biger()
    {
        memset(a,0,sizeof(a));
        a[0]=1;
    }
};    
bool operator < (Biger &a,Biger &b)//重载比较运算符
{
    if(a.is_fu()&&!b.is_fu())
        return true;
    if(!a.is_fu()&&b.is_fu())
        return false;
    if(a.a[0]<b.a[0])
        return true;
    if(a.a[0]>b.a[0])
        return false;
    for(int i=a.a[0];i>=1;i--){ 
        if(a.a[i]<b.a[i])
            return true;
        if(a.a[i]>b.a[i])//加快速度
            return false; 
    } 
    return false;
}
bool operator > (Biger &a,Biger &b)
{
    return b<a&&(a<b||b<a);
}
bool operator <= (Biger &a,Biger &b)
{
    return a<b||!(a<b||b<a);
}
bool operator >= (Biger &a,Biger &b)
{
    return !(a<b);
}
bool operator == (Biger &a,Biger &b)
{
    return !(a<b||b<a);
}
bool operator != (Biger &a,Biger &b)
{
    return  a<b||b<a;
} 
Biger operator * (Biger &a,Biger &b)
{
    Biger c;
    bool a1=false,b1=false;
    c.a[0]=a.a[0]+b.a[0];
    if(a.is_fu())
        a1=true;
    if(b.is_fu())
        b1=true;
    for(int i=1;i<=b.a[0];i++)
    {
        int x=0;
        for(int j=1;j<=a.a[0];j++)
        {
            c.a[i+j-1]=c.a[i+j-1]+b.a[i]*a.a[j];
            c.a[i+j]+=c.a[i+j-1]/10;
            c.a[i+j-1]%=10;    
        }
    }
    while(!c.a[c.a[0]]&&c.a[0]>1&&c.a[c.size()+1]!=-1)c.a[0]--;
    if(a1!=b1)
    {
        c.a[c.size()+1]=-1;
    }
    while(!c.a[c.a[0]]&&c.a[0]>1&&c.a[c.size()+1]!=-1)c.a[0]--;
    return c;
}
Biger operator *= (Biger &a,Biger &b)
{
    a=a*b;
}
main()
{
    Biger a,b,c;
    a.IN();
    b.IN();
    a*=b;
    a.OUT();
}
```

---

## 作者：「QQ红包」 (赞：1)

高精度乘法，挺简单。来段注释多点的代码。

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
using namespace std;
int a[10010]={0},b[10010]={0},c[20020]={0};//c=a*b，abc都是倒着存的 
int la,lb,lc;//分别存a，b，c
int i,j;//循环控制变量 
string ch;//读入时候用的 
void chengfa(int x[10010],int y[10010],int z[20020],int lx,int ly)//乘法的过程 
{
    for (i=1;i<=lx;i++)//乘的过程 
        for (j=1;j<=ly;j++)
        {
            z[i+j-1]+=x[i]*y[j];//乘进去
            z[i+j]+=z[i+j-1]/10;//进位 
            z[i+j-1]%=10;//进位 
        }
}
int main()
{
/////////////////////读入部分///////////////////////////////////////////////////
    cin>>ch;//读入第一个数
    int haha=ch.size()-1;//求出第一个数的长度
    la=0;
    for (i=haha;i>=0;i--)//倒着存到A数组内 
    {
        la++;//这个也是存位数的 
        a[la]=(int)(ch[i])-48; //存进去 
    } 
    cin>>ch;//读入第二个数
    haha=ch.size()-1;//求出第二个数的长度
    lb=0;
    for (i=haha;i>=0;i--)//倒着存到B数组内 
    {
        lb++;//这个也是存位数的 
        b[lb]=(int)(ch[i])-48; //存进去 
    } 
///////////////////////乘法部分/////////////////////////////////////////////////
    chengfa(a,b,c,la,lb);
///////////////////////输出部分/////////////////////////////////////////////////
    if (a[1]==0&&b[1]==0) cout<<0;//特殊情况 
    lc=la+lb;//c最长就这么长 
    int hehe=0;//标记用 
    for (i=lc;i>=1;i--)//存的时候是倒着存的这时候要倒着输出 
    {
        if (c[i]!=0) hehe=1;//找到第一个不为0的数
        if (hehe==1) printf("%d",c[i]); //输出 
    }
    return 0;
}


```

---

## 作者：lbxx (赞：1)

```cpp
program Project1;
var i,x,y,j,z:integer;
    m,n:ansistring;
    a,b,c:array[1..10000] of int64;
begin
for i:=1 to 10000 do c[i]:=0;           {清零}
readln(m);
read(n);
x:=length(m);
y:=length(n);
for i:=1 to x do
a[i]:=ord(m[x+1-i])-48;
for i:=1 to y do                                     {倒着读入，a[1]为个位，a[2]为十位......}
b[i]:=ord(n[y+1-i])-48;
for i:=(x+1) to 10000 do
a[i]:=0;                                       {清零}
for i:=(y+1) to 10000 do
b[i]:=0;
for i:=1 to y do
for j:=1 to x do
c[i-1+j]:=c[i-1+j]+a[j]*b[i];                  
for i:=1 to 10000 do
if c[i]>9 then
while c[i]>9 do
begin
 c[i+1]:=c[i+1]+c[i] div 10;             {进位}         
 c[i]:=c[i] mod 10;                          
end;
for i:=10000 downto 1 do
if c[i]<>0 then break;
for j:=i downto 1 do              {去零输出}
write(c[j]);
readln;
readln;
end.
```

---

## 作者：Neil1110 (赞：1)

总体来说就是分成两部分。

第一部分是将两个数按列竖式的顺序乘到c里面，

第二部分就是将c一行一行地加到tot里面，

最后判断开头有没有0，然后输出。

代码中有具体注释。

```cpp

#include<iostream>
#include<cstring>
using namespace std;
char a1[10000],b1[10000];
int a[10000]={0},b[10000]={0},c[10000][10000]={0},la,lb,tot[10000],jin=0;
void mult()    //按列竖式顺序一位一位乘出来 
{
    int i,j,k=0,l=0,m=0;
    jin=0;
    for(i=0;i<=la;i++)
    {
        l=m;
        for(j=0;j<=lb;j++)
        {
            c[k][l]=(a[i]*b[j]+jin)%10;
            jin=(a[i]*b[j]+jin)/10;
            l++;
        }
        k++;
        m++;
    }
}
void add()    //将c一行一行的加到tot里面 
{
    int i,j,jin1=0;
    jin=0;
    for(i=0;i<=la;i++)
    {
        for(j=0;j<=la+lb-1;j++)
        {
            jin1=(tot[j]+c[i][j]+jin)/10;
            tot[j]=(tot[j]+c[i][j]+jin)%10;
            jin=jin1;
        }
    }
}
int main()
{
    int i,j=0,ok=0;
    cin>>a1>>b1;
    la=strlen(a1);
    lb=strlen(b1);
    if(a1[0]=='0'||b1[0]=='0')
    {
        cout<<"0";
        return 0;
    }
    for(i=la-1;i>=0;i--)
    {
        a[j]=a1[i]-'0';
        j++;
    }    
    j=0;
    for(i=lb-1;i>=0;i--)
    {
        b[j]=b1[i]-'0';
        j++;
    }    //顺序颠倒，放到数组里 
    mult();
    add();
    if(jin!=0)
        cout<<jin;
    for(i=la+lb-1;i>=0;i--)
    {
        if(ok==1||tot[i]!=0)
        {
            cout<<tot[i];
            ok=1;
        }
    }    //如果开头有0则不输出 
    cout<<endl;
    return 0;
}

```

---

## 作者：shutdown (赞：1)

朴素压位高精。。

注意j循环退出后j的值是lb+1，所以不能c[i+j]=x而应c[i+lb]=x。

```cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;
string s,s1,s2,s3,ans;
int a[10001],b[10001],c[10001];
int i,j,k,l,m,n,p,q,x,y,z,tmp,tmp2=0,tmp3,tmp4,la,lb,lc;
stringstream ss[10001];
void pp(int x)
{
     string aa;
     tmp2++;
     ss[tmp2]<<c[x];
     //cout<<x<<' '<<c[x]<<endl;
     ss[tmp2]>>aa;
     if (c[x]>=1000){ans=ans+aa;} else
     if (c[x]>=100){ans=ans+"0"+aa;} else
     if (c[x]>=10){ans=ans+"00"+aa;} else
     {ans=ans+"000"+aa;};
}
int main()
{
    cin>>s1;
    cin>>s2;
    la=(s1.size()+1)/4; if (la*4<s1.size()){la++;};
    lb=(s2.size()+1)/4; if (lb*4<s2.size()){lb++;};
    x=0; y=0;
    while (s1.size()>0)
    {
          x++; p=s1.size(); q=p; if (q>4){q=4;};
          s3=s1.substr(p-q,q); z=0;
          tmp2++; ss[tmp2]<<s3; ss[tmp2]>>a[x];
          //cout<<x<<' '<<a[x]<<endl;
          s1.erase(p-q,q);
          //for (i=0; i<=q-1; i++){z++; tmp=int(s3[i]); for (j=1; j<=q-z; j++){tmp=tmp*10;}; a[x]+=tmp;};
    }
    x=0; y=0; 
    while (s2.size()>0)
    {
          x++; p=s2.size(); q=p; if (q>4){q=4;};
          s3=s2.substr(p-q,q); z=0;
          tmp2++; ss[tmp2]<<s3; ss[tmp2]>>b[x];
          //cout<<x<<' '<<b[x]<<endl;
          s2.erase(p-q,q);
          //for (i=0; i<=q-1; i++){z++; tmp=int(s3[i]); for (j=1; j<=q-z; j++){tmp=tmp*10;}; b[x]+=tmp;};
    }
    for (i=1; i<=la; i++)
    {
        x=0;
        for (j=1; j<=lb; j++)
        {
            c[i+j-1]=a[i]*b[j]+x+c[i+j-1];
            x=c[i+j-1]/10000;
            c[i+j-1]=c[i+j-1]%10000;
        }
        c[i+lb]=x;
        //cout<<i+j<<' '<<x<<endl;
    }
    lc=la+lb;
    ans=" ";
    for (i=lc; i>=1; i--){pp(i);};
    lc=ans.size(); 
    while ((ans[1]=='0')&&(lc>1)){ans.erase(1,1); lc--;};
    ans.erase(0,1);
    cout<<ans;
    system("pause");
    return 0;
}

```

---

## 作者：Sinwind (赞：1)

# 1.算法

1. 高精度数：有时，要处理的数太大$($还有可能精度要求很高，但本文不讨论$)$，甚至超过了$long\space long$的范围$(2^{63}-1\approx9\times10^{18})$，此时需要用字符串$(string$型或$char$型数组$)$来存储数字。

2. 高精度算法：高精度数运算时需要特殊的算法进行运算，称为高精度算法。高精度算法本质上是**模拟数字的运算**。

3. 高精度加法

原理：模拟加法。

- 先将两数中较小的在前面补足$0$，使得两数的位数相同$(eg:25$与$1236\rightarrow0025$与$1236)$。

- 从后往前，对应的每位相加，再加上进位的数，得出和。

- 和$/10$，得到进位的数；和$\%10$，得到结果对应位置上的数。

- 注意最后有可能还有进位的数，若有，添加上进位的数$(eg:50+50$，加的结果为$00$，最后进位的数是$1$，需要添加在$00$之前，为$100)$。

4. 高精度乘法

原理：模拟乘法。

- 第一个数从后往前分别乘以第二个数的倒数一位，倒数第二位，倒数第三位，$\dots$。

- 每一位计算完后都要乘以权重，第$n$次乘以$10^{n-1}$，即在字符串末尾添上$n-1$个$'0'$。

- 完成前两步后，用$($高精度加法$)$累加。

- 注意：**最后乘积结果可能为$'0'(eg:123\times 0)$，但是用以上算法可能输出多个$'0'(eg:123\times 0=000)$，此时特殊情况特殊讨论，将答案改为$0'$。**
# 2.代码

```cpp
#include <iostream>
#include <string>

using namespace std;

string a,b;         //输入的两个数

//高精度加法
string ADD(string x, string y)
{
	string ans;     	//答案
	//保证长的数赋给x，短的数赋给y
	if(x.length() < y.length())
	{
  		string temp = x;
		x = y;
		y = temp;
	}
	
	//y前面补足0
	int x_len = x.length();
	int y_len = y.length();
	for(int i = 0; i < x_len - y_len; i++)
	{
		y = '0' + y;
	}
	
	//模拟加法
	int num = 0;   		//每位的数
	int up = 0;			//进位的数
	for(int i = x_len - 1; i >= 0; i--)
	{
		num = (char)(x[i] - '0') + (char)(y[i] - '0') + up;
		up = num / 10;
		num %= 10;
		ans = (char)(num + '0') + ans;
	}
	if(up)
	{
		ans = (char)(up + '0') + ans;
	}
	
	return ans;
}

//高精度乘法
string MUL(string x, string y)
{
	//模拟乘法
	string ans;			//最终结果
	int x_len = x.length();
	int y_len = y.length();
	for(int i = x_len - 1; i >= 0; i--)
	{
		string t;   	//每位的乘积
		int num = 0;	//本位的数
		int up = 0; 	//进位的数
		for(int j = y_len - 1; j >= 0; j--)
		{
			num = (x[i] - '0') * (y[j] - '0') + up;
			up = num / 10;
			num %= 10;
			t = (char)(num + '0') + t;
		}
		if(up)
		{
			t = (char)(up + '0') + t;
		}
		
		//乘以权重
		for(int k = 0; k < (x_len - 1) - i; k++)
		{
			t += '0';
		}
		
		ans = ADD(ans, t);
	}

	int ans_len = ans.length();
	bool is_zero = true;//是否为0，true为0，false为非0
    for(int i = 0; i < ans_len; i++)
    {
    	if(ans[i] != '0')
    	{
    		is_zero = false;
    		break;
		}
	}

	if(is_zero)
	{
		ans = '0';
	}

	return ans;
}

int main(void)
{
	cin >> a >> b;
	
	cout << MUL(a, b);
	
	return 0;
}
```


---

## 作者：蒟蒻溴化氢 (赞：1)

蒟蒻花了一上午写了一个高精度
个人认为代码对新手比较友好（包括加减乘）
注释在代码里
（代码参考了林厚从的《信息学奥赛课课通》以及@stone_juice石汁的一篇题解）
```
#include <iostream>
#include <cstdio>
#include <cstring>
#define res register int
using namespace std;
const int N=10010;
char sa[N],sb[N];
//用字符串形式存储数据 
string add(char sa[],char sb[])//高精度加法 
{
	string ans="";
	int a[N],b[N],c[N];
	int la=strlen(sa);//得到sa有多少位 
	int lb=strlen(sb);//得到sb有多少位 
	memset(a,0,sizeof(a));//初始化一下 
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	for(res i=0;i<la;i++) a[la-i-1]=sa[i]-'0';//把字符转化为数字  同时把数字翻转过来 
											  //这样a[i]就表示第i位 
	for(res i=0;i<lb;i++) b[lb-i-1]=sb[i]-'0';
	int lc=max(la,lb);//最后的结果就是两个的最大值 
	for(res i=0;i<lc;i++)
	{
		c[i]+=a[i]+b[i];//加法 
		if(c[i]>=10) c[i+1]=1,c[i]-=10;//处理一下进位的问题 
	}
	if(c[lc]>0) lc++;
	for(res i=lc-1;i>=0;i--)
	{
		char tmp=c[i]+'0';
		ans=ans+tmp;//结果 
	}
	return ans;
}

int _compare(char sa[],char sb[])//比较两个正数的大小 
{//1代sa>sb 0代表相等 -1代表sa<sb 
	int la=strlen(sa),lb=strlen(sb);
	if(la<lb) return -1;//如果长度不同 那么大小就可以确定 
	if(la>lb) return 1;
	for(res i=0;i<la;i++)
	{
		char tmpa=sa[i];
		char tmpb=sb[i];
		if(tmpa>tmpb) return 1;
		if(tmpa<tmpb) return -1;
	}
	return 0;
}



string _minus(char sa[],char sb[],int x)//高精度减法 x代表是否取负号 
{
	string ans="";
	int a[N],b[N],c[N];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int la=strlen(sa);
	int lb=strlen(sb);
	for(res i=0;i<la;i++) a[la-i-1]=sa[i]-'0';
	for(res i=0;i<lb;i++) b[lb-i-1]=sb[i]-'0';//前面有解释 
	int lc=max(la,lb);
	for(res i=0;i<lc;i++)
    {
        if(c[i]+a[i]-b[i]<0)
        {
            c[i+1]--;
            c[i]+=10;
        }//借位处理
        c[i]+=a[i]-b[i];
    }
	while(c[lc-1]==0&&lc>0) lc--;//删除在最开始的0 
	for(res i=lc-1;i>=0;i--)
	{
		char tmp=c[i]+'0';
		ans=ans+tmp;
	} 
	if(x==-1) ans="-"+ans;
	return ans;
}

string _mul(char sa[],char sb[])
{
	if(sa[0]=='0'||sb[0]=='0') return "0";
	string ans="";
	int a[N],b[N],c[N];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int la=strlen(sa);
	int lb=strlen(sb);
	for(res i=0;i<la;i++) a[la-i-1]=sa[i]-'0';
	for(res i=0;i<lb;i++) b[lb-i-1]=sb[i]-'0';
	for(res i=0;i<la;i++)
		for(res j=0;j<lb;j++)
		{
			int f,w,jw;//i和j位相乘存储在答案的i+j位当中 
			f=a[i]*b[j]; jw=f/10; f=f%10;w=i+j;//jw表示进位 f表示进位后剩下的数 
			c[w]=c[w]+f;jw+=c[w]/10;c[w]=c[w]%10;
			c[w+1]=c[w+1]+jw;
		}
	int lc=la+lb;
	while(c[lc-1]==0&&lc>0) lc--;//前面有解释 
	for(res i=lc-1;i>=0;i--)
	{
		char tmp=c[i]+'0';
		ans=ans+tmp;
	}
	return ans;
}


int main()
{
//	freopen("test.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>sa>>sb;
//在做减法之前 要先比较哪一个数更大 
	if(_compare(sa,sb)==1) cout<<_minus(sa,sb,1);
	else if(_compare(sa,sb)==-1) cout<<_minus(sb,sa,-1);
	else cout<<"0";

	cout<<_mul(sa,sb);
	return 0;
} 
```
rp++

---

## 作者：包子入侵 (赞：1)

高精度算法，属于处理大数字的数学计算方法。在一般的科学计算中，会经常算到小数点后几百位或者更多，当然也可能是几千亿几百亿的大数字。一般这类数字我们统称为高精度数，高精度算法是用计算机对于超大数据的一种模拟加，减，乘，除，乘方，阶乘，开方等运算。对于非常庞大的数字无法在计算机中正常存储，于是，将这个数字拆开，拆成一位一位的，或者是四位四位的存储到一个数组中， 用一个数组去表示一个数字，这样这个数字就被称为是高精度数。高精度算法就是能处理高精度数各种运算的算法，但又因其特殊性，故从普通数的算法中分离，自成一家。

```cpp
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int num[10000];
int string_a[10000];
int string_b[10000];
int main()
{
 int t;
 cin>>t;
 while(t--)
 {
  //把数组初始化为0
  memset(num,0,sizeof(num));
  memset(string_a,0,sizeof(string_a));
  memset(string_b,0,sizeof(string_b));
  string a,b;
  cin>>a>>b;
  //若a，b其中一个为0，则输出0
  if(b=="0"||a=="0")
  {
   cout<<0<<endl;
   continue;
  }
  //以1为初始位分别逆向存储a，b的每位数字
  int n=1,m=1;
  for(int i=a.size()-1;i>=0;i--)
   string_a[n++]=a[i]-'0';
  for(int i=b.size()-1;i>=0;i--)
   string_b[m++]=b[i]-'0';
  for(int i=1;i<m;i++)
  {
   int v=0;  //初始化进位为0
   for(int j=1;j<n;j++)
   {
    num[i+j-1]+=string_b[i]*string_a[j];
    v=num[i+j-1]/10;               //进位
    num[i+j]+=v;                   //下一位加上前一位的进位
    num[i+j-1]=num[i+j-1]%10;      //求余即为本位当前数值
   }
  }
  //逆向输出答案
  for(int k=9999;k>=1;k--)
  {
   if(num[k]!=0)
   {
    for(int i=k;i>=1;i--)
    {
     cout<<num[i];
    }
    cout<<endl;
    break;
   }
  }
 }
 return 0;
}
```

---

## 作者：Continue (赞：1)

//吐槽一下：题目中竟然没有数据范围 (╯‵□′)╯︵┻━┻

//思路：高精，模拟竖式计算即可，注意进位问题





```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=2000+1000;
char s1[maxn],s2[maxn];
int a[maxn],b[maxn],c[maxn*maxn];
int main()
{
    scanf("%s%s",s1,s2);//先以字符读入 
    int l1=strlen(s1),l2=strlen(s2);
    for(int i=0;i<l1;i++) a[i]=s1[l1-i-1]-'0';//转存到数组里 
    for(int i=0;i<l2;i++) b[i]=s2[l2-i-1]-'0';//低位放前，高位放后，便于进位 
    for(int i=0;i<l1;i++)
        for(int j=0;j<l2;j++) {
            c[i+j]+=a[i]*b[j];//注意是+= 而非= 否则会覆盖之前进位的数据 
            c[i+j+1]+=c[i+j]/10;//进位，同样注意是+= 而非= 
            c[i+j]%=10;
        }
    int l3=l1+l2;
    while(l3>1&&c[l3-1]==0) l3--;//处理前导零 
    for(int i=l3-1;i>=0;i--) printf("%d",c[i]);
    return 0;
}
```

---

## 作者：ROOToj (赞：1)

高精度乘法，模拟笔算即可，即单精度乘法+高精度加法。

为了删前导0时不会忽略“output:0\n”的情况，在读入两个字符串后立即处理：若有一个为0立刻输出0并退出程序。

附上AC源代码：



```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define MAXN 5000
char a_s[MAXN],b_s[MAXN];
int a_len,b_len,i,c[MAXN][MAXN],k,j,sum[MAXN],a[MAXN],b[MAXN];
int sumlen()
{
    int nu=0;
    for(int ii=a_len+b_len;ii>=1;ii--)
        if(sum[ii])break;
        else nu++;
    return a_len+b_len-nu;
}
int main()
{
    scanf("%s%s",&a_s,&b_s);
    if(!strcmp(a_s,"0")||!strcmp(b_s,"0")){printf("0\n");return 0;}
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    a_len=strlen(a_s);
    b_len=strlen(b_s);
    for(i=0;i<a_len;i++)a[a_len-i]=a_s[i]-'0';
    for(i=0;i<b_len;i++)b[b_len-i]=b_s[i]-'0';
    memset(c,0,sizeof(c));
    for(i=1;i<=b_len;i++)
    {
        k=0;
        for(j=1;j<=a_len;j++)
        {
            c[i][j+i-1]=a[j]*b[i]+k;
            k=c[i][j+i-1]/10;
            c[i][j+i-1]%=10;
        }
        c[i][a_len+i]+=k;
    }
    memset(sum,0,sizeof(sum));
    for(i=1;i<=b_len;i++)
    {
        k=0;
        for(j=1;j<=a_len+b_len;j++)
        {
            sum[j]=sum[j]+c[i][j]+k;
            k=sum[j]/10;
            sum[j]%=10;
        }
        sum[sumlen()+1]+=k;
    }
    for(i=sumlen();i>=1;i--)printf("%d",sum[i]);
    putchar('\n');
    return 0;
}
-------------------------------------------END-------------------------------------------​​​​

```

---

## 作者：sermoon (赞：0)

```cpp
#include<bits/stdc++.h>
//事实上，如果4位4位地计算高精度，会大大提升代码运行速率
using namespace std;
#define LKF 14170//定义全局常量，便于书写
int a[LKF],b[LKF],c[LKF];//用于计算
int a1[LKF],b1[LKF];//压位用品
char bcs[LKF],cs[LKF];//读入的数组（被乘数）和（乘数）
int main()
{
    int lena,lenb,j1=0,j2=0,i1,i2;
    scanf("%s",bcs);
    scanf("%s",cs);
    lena=strlen(bcs);
    lenb=strlen(cs);
    for(i1=lena-1;i1>2;i1-=4)
    {
        if(i1-3>=0)
        a1[j1++]=(bcs[i1-3]-'0')*1000+(bcs[i1-2]-'0')*100+(bcs[i1-1]-'0')*10+(bcs[i1]-'0');
    }
        if(i1==0)
        a1[j1++]=bcs[0]-'0';
        else if(i1==1)
        a1[j1++]=(bcs[0]-'0')*10+(bcs[1]-'0');
        else if(i1==2)
        a1[j1++]=(bcs[0]-'0')*100+(bcs[1]-'0')*10+(bcs[2]-'0');
        while(j1>0&&a1[j1-1]==0)    j1--;//压位
    for(i2=lenb-1;i2>2;i2-=4)
    {
        if(i2-3>=0)
        b1[j2++]=(cs[i2-3]-'0')*1000+(cs[i2-2]-'0')*100+(cs[i2-1]-'0')*10+(cs[i2]-'0');
    }
        if(i2==0)
        b1[j2++]=cs[0]-'0';
        else if(i2==1)
        b1[j2++]=(cs[0]-'0')*10+(cs[1]-'0');
        else if(i2==2)
        b1[j2++]=(cs[0]-'0')*100+(cs[1]-'0')*10+(cs[2]-'0');
        while(j2>0&&b1[j2-1]==0)    j2--;//同上
    for(int j=0;j<j1;++j)
        for(int i=0;i<j2;++i)
        {
            c[i+j]+=a1[j]*b1[i];
            c[i+j+1]+=(c[i+j])/10000;//不妨将c看作万进制数，记录余数
            c[i+j]%=10000;//同上，缩小c范围
        }
    int j3=j1+j2;
    while(c[j3-1]==0&&j3>1) j3--;//去除前导的0
    printf("%d",c[j3-1]);//先打第一位，为了方便后面的添零处理
    for(int i=j3-2;i>=0;--i) printf("%04d",c[i]);//在中间出现了三位数，二位数，1位数时，要添零使其成为4位数
    return 0;
} 
//谢谢观赏
```

---

## 作者：LevenKoko (赞：0)

主要思路就是竖式

为了方便，数组里的内容倒过来存，方便进位什么的

代码：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<iomanip>
#include<stack>
#include<cstring>
#include<ctime>
#include<cstdio>
#include<vector>
using namespace std;
int a[100005],b[100005],c[100005];
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    if(s1[0]=='0' || s2[0]=='0')
    {
        cout<<0;
        return 0;
    }//特判有0的情况；
        int l1=s1.size(),l2=s2.size();
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));//赋初值
    for(int i=0;i<=l1-1;i++)
        a[l1-i]=s1[i]-'0';
    for(int i=0;i<=l2-1;i++)
        b[l2-i]=s2[i]-'0';//把数组倒过来存储
        int i,k=0,d,e,j;//k用来进位什么的。。。
    for(i=1;i<=l2;i++)
    {
        k=0;
        for(j=1;j<=l1;j++)
        {
            c[i+j-1]=a[j]*b[i]+c[i+j-1];
            k=c[i+j-1]/10;
            c[i+j-1]%=10;
            c[i+j]+=k;
        }
    }
    k=l1+l2;//这里的k直接拿来其他用了（结果的长度）；
    for(int j=l1+l2;j>=2;j--)
    if(c[j]!=0)
    break;
    else k--;//去前导0（当然用while更简单，但是懒得改了）
        for(int j=k;j>=1;j--)
    cout<<c[j];//输出
        return 0;
}
```

---

