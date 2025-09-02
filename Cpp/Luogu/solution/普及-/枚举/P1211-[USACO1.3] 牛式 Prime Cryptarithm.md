# [USACO1.3] 牛式 Prime Cryptarithm

## 题目描述

下面是一个乘法竖式，如果用我们给定的那 $n$ 个数字来取代 `*`，可以使式子成立的话，我们就叫这个式子为牛式。

```cpp
          ***
    x      **
   ----------
         ***
        ***
   ----------
        ****
```

数字只能取代 `*`，当然第一位不能为 $0$，况且给定的数字里不包括 $0$。


注意一下在美国的学校中教的“部分乘积”，第一部分乘积是第二个数的个位和第一个数的积，第二部分乘积是第二个数的十位和第一个数的乘积。

请计算出牛式的数量。



## 说明/提示

### 样例解释

```
          222
    x      22
   ----------
         444
        444
   ----------
        4884
```

不需要别的数，严格符合上图的数位情况，可以证明没有其他情况。



不加入样例解释：做题人如果理解错题意会进入误区

比如不用填中间的数，位数没有要求 `34*2=68` 符合要求等误区。

### 数据规模  
对于 $100\%$ 的数据，$1\le n \le 9$，$a_i \in [1,9] \cap \mathbb Z$ 且 $a_i$ 不重复。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
5
2 3 4 6 8
```

### 输出

```
1
```

# 题解

## 作者：bits (赞：50)

其实这题就是暴力枚举

小学就学的三位数乘两位数，要求“**部分乘积**”为三位，结果四位

别想复杂了，没有坑！！！

代码：

```cpp
#include <cstdio>//简洁的头文件
using namespace std;
bool p[15];//桶，标记是否出现
bool f(int n)//养成写子程序的好习惯，代码就不会很长
{
    while(n)
    {
        if(p[n%10]==0)
            return 0;//不包含--直接跳出
        n/=10;
    }
    return 1;
}
bool check(int x,int y)
{
    int a=x*(y%10),b=x*(y/10),test=x*y;//所谓的“部分乘积”
    if(a>999 || b>999 || test>9999)//节约时间，跳过连位数都不符合的
        return 0;
    if(f(x)==1 && f(y)==1 && f(a)==1 && f(b)==1 && f(test)==1)//根据“开关特性”，只要有一为假就结束判断，因此并不耗时
        return 1;
    else
        return 0;
}
int main()
{
    int n,key,ans=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&key);
        p[key]=true;//桶的精华，标记一下
    }
    for(int i=100;i<1000;i++)
    {
        for(int j=10;j<100;j++)//真正的暴力在这儿！
        {
            if(check(i,j)==1)
                ans++;//方案数++；
        }
    }
    printf("%d\n",ans);//输出
    return 0;
}
```

---

## 作者：逢题必过 (赞：13)

其实这道题很简单，各位小朋友不要想多了！

枚举第一个三位数100~999，第二个两位数10~99

然后判断这两个数是不是能用n个数中的一个数表示

以及他们的部分乘积是不是三位数（x/1000==0），且能用n个数中的一个数表示.

and部分乘积相加（个位乘积+十位乘积\*10）是否是四位数（x/10000==0），且能用n个数中的一个数表示.

end
建议小伙伴们不要抄袭，顺着我的思路来写就行了。


参考代码如下：


```cpp
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int n,w[1000],ans=0,_pow(int);;
bool check1(int,int),check2(int,int);
int main() {
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%d",&w[i]);
    for(int i=100; i<=999; i++) {
        if(check2(i,3)) continue;
        //cout<<i<<" ";
        for(int j=10; j<=99; j++) {
            if(check2(j,2)) continue;
            if(check1(i,j)) ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
bool check1(int a,int b) {
    int m=b%10,n=b/10%10;
    int x=m*a,y=n*a;
    int z=x+y*10;
    if(x/1000!=0||y/1000!=0||z/10000!=0) return false;
    if(check2(x,3)||check2(y,3)||check2(z,4)) return false;
    return true;
}
bool check2(int a,int b){
    int s=0;
    for(int i=0;i<b;i++){
        for(int j=0;j<n;j++){
            if(a/_pow(i)%10==w[j]){
                s++;
                break;
            }
        }
    }
    if(s<b) return true;
    return false;
}
int _pow(int i){
    int s=1;
    for(int j=0;j<i;j++) s*=10;
    return s;
}
```
/\*
5
2 3 4 6 8

-----------

1
\*/

---

## 作者：Sino_E (赞：10)

其实很简单啊....

枚举两个乘数。第一个乘数是3位数，因此枚100-999.第二乘数以此类推。前两乘数能推出后三个数。

同时，第三、第四、第五乘数的位数都已经固定，因此首先判断位数合不合法，再看看这些数里是不是由题目给的数字组成的。就计数加一。

给个简单代码吧（请不要直接复制代码=、=）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
bool can[N];


int check(int num){
    while(num){
        if(can[num%10]==0)return 0;
        num/=10;
    }
    return 1;
}//判断数字合法的函数 

int main(){
    int n;
    cin>>n;
    int a;
    for(int i=0;i<n;i++){
        cin>>a;
        can[a]=1;
    }
    int ans=0;
    for(int i=100;i<=999;i++){
        for(int j=10;j<=99;j++){
                //枚举两个乘数 
            if(i*(j/10)<=999&&i*(j%10)<=999&&i*j<=9999){    //判断位数 
                if(check(i)&&check(j)&&check(i*(j%10))&&check(i*(j/10))&&check(i*j)){    //判断数字 
                    ans++;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：7)

此题其实并不难，只要一个搜索，把每种情况枚举一遍，只要求出总情况数即可。

搜索有几个可以剪枝的地方：

S1  S4  S5

×    S2  S3

约束条件只有3个：第3、4行是3位数，第5行是4位数。我们按S1到S5的顺序搜索。

如果S1×S2>10或者S1×S3>10，则3、4行肯定不是3位数，剪枝。

即S1\*S2+S4\*S2/10>=10 || S1\*S3+S4\*S3/10>=10 剪枝

我怕有些人抄程序，所以留出几个空，自己想哦！！！

```cpp
var
  n,i,x,k,sum:longint;
  ops,s:string;
  a:array[0..1000] of longint;
procedure sc;
var
  f,ff,fff:boolean;
  i,j,s1,s2,s3,s4,s5,p1,p2,l:longint;
  sl,ss1,ss2,ss3,ss4,ss5,po1,po2,sss:string;
begin
  for i:=100 to 999 do          //把所有三位数枚举过来
  begin
    s1:=i div 100;        str(s1,ss1);
    s4:=i div 10 mod 10;  str(s4,ss4);
    s5:=i mod 10;         str(s5,ss5);
    if (pos(ss1,s)>0) and (pos(ss4,s)>0) and (pos(ss5,s)>0) then         //这些数都在读入的数中
    begin
      for j:=10 to 99 do
      begin
        s2:=j div 10;     str(s2,ss2);
        s3:=j mod 10;     str(s3,ss3);
        if (pos(ss2,s)>0) and (        ) then
        begin
          if (s1*s2<10) and (s1*s3<10) then               
          begin
            p1:=s1*100+s4*10+s5;
            p2:=s2*10+s3;
            if (p1*s2<1000) and (p1*s3<1000) then        //优化，剪枝
            begin
              str(p1*s2,po1);
              str(p1*s3,po2);
              ff:=false;
              for k:=1 to 3 do
              begin
                if (pos(po1[k],s)=0) then begin ff:=true;break; end;
                if (pos(po2[k],s)=0) then begin ff:=true;break; end;
              end;
                if ff=false then
                begin
                  if (     ) and (      ) then
                  begin
                    str(p1*p2,sss);
                    fff:=false;
                    for l:=1 to 4 do
                    if (pos(sss[l],s)=0) then
                    begin
                      fff:=true;
                      break;
                    end;
                    if fff=false then
                    begin
                      sum:=sum+1;
                    end;
                  end;
                end;
            end;
          end;
        end;
      end;
    end;
  end;
end;
begin
  readln(n);
  for i:=1 to n do
  begin
    read(x);
    str(x,ops);       //这里我把所有数转换成了字符串。
    s:=s+ops;
  end;
  k:=0;                  
  sc;                    //搜索 
  writeln(sum);        //输出总方案数
end.
```

---

## 作者：恶灬心 (赞：5)

题解思路都十分类似 就是爆搜。但我看题解大部分都是直接搜索数字，并不按位搜索。 于是我来发一个类似于高精度的搜索。
```
#include <bits/stdc++.h>
using namespace std;
inline int read() //快读 不用管
{
	int w=1,d=0; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')d=d*10+ch-'0',ch=getchar();
	return w*d;
}
int n,a[15],b[15];
int ans[10],sum[2][10],num[10],za;
/*
	ans存最后的结果
    sum[0]和sum[1] 分别存两次乘法的值
    num存3位数
*/
void init() //读入函数 模块化 比较清晰
{
	n=read();
	for(int i=1;i<=n;i++) 
	{
		a[i]=read();
		b[a[i]]=1;
	}
}
int cheng(int l,int t) //乘法 分部来乘
{
	memset(sum[t],0,sizeof(sum[t]));
	int x=0;
	sum[t][0]=3+2;
	for(int i=1;i<=sum[t][0];i++)
	{
		sum[t][i]=num[i]*l+x;
		x=sum[t][i]/10;
		sum[t][i]%=10;
	}
	while(sum[t][sum[t][0]]==0) sum[t][0]--;
	if(sum[t][0]>3) return 0;
	for(int i=1;i<=sum[t][0];i++)
	if(!b[sum[t][i]]) return 0;
	return 1;
}
void dfs_sum(int deep) //枚举两位数
{
	if(deep>2)
	{
		memset(ans,0,sizeof(ans));
		ans[0]=max(sum[1][0],sum[0][0])+2;
		int x=0,flag=0;
		for(int i=1;i<=ans[0];i++)
		{
			ans[i]=sum[0][i]+sum[1][(i-1==0?9:i-1)]+x;
			x=ans[i]/10;
			ans[i]%=10;
		}
		while(ans[ans[0]]==0) ans[0]--; 
		for(int i=1;i<=ans[0];i++)
		if(!b[ans[i]]) return ;
		za++;
		return ;
	}
	for(int i=1;i<=n;i++)
	if(cheng(a[i],deep-1))
	dfs_sum(deep+1);
}
void dfs_num(int deep) //枚举三位数
{
	if(deep>3)
	{
		dfs_sum(1);
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		num[deep]=a[i];
		dfs_num(deep+1);
	}
}
void solve()
{
	dfs_num(1);
	cout<<za;
}
int main()
{
	init();
	solve(); 
}
```
回顾这道题，坑点就只有要严格按照数位罢了。所以这就是一道水题。

---

## 作者：Chaos1018 (赞：5)

###首先我的具体思路是枚举,就枚两个数,一个枚十位,一个枚百位.这里和楼下用枚举的dalao一毛一样.

##然后再输入时弄一个桶,把所有的数字存起来,再枚举时一一算出牛式的每个式子-----

```cpp
         ***
    x     **
   ----------
         ***
        ***
   ----------
        ****
```
##就是把上面每一个由\*组成的式子算出来，最后再一一判断每一位即可

###具体上代码

```cpp
/*
ID: czj20052
LANG: C++
TASK: crypt1
*///别在意，USACO上要的
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int a[10];//一个桶，代表输入了那些数字，由于最大只能到9所以只要开10
int ss(int i,int j)//判断是否为牛式的函数，0代表不是，1代表是
{
    int a1=i*(j%10);
    int b=i*(j/10);
    int c=i*j;
    if(a1>999) return 0;
    if(b>999) return 0;
    if(c>9999) return 0;//注意这三行！！！如果不判断的话就会多出原本不要的式子了！！！
    while(i!=0)
    {
        if(a[i%10]==0)
        {
            return 0;
        }
        i/=10;
    }
    while(j!=0)
    {
        if(a[j%10]==0)  return 0;j/=10;}
    while(a1!=0)
    {
        if(a[a1%10]==0) return 0;a1/=10;
    }
    while(b!=0)
    {
        if(a[b%10]==0) return 0;b/=10;
    }
    while(c!=0)
    {
        if(a[c%10]==0) return 0;c/=10;
    }//这几个while循环就是判断每一位是否在桶子里
    return 1;
}
int main()
{
    freopen("crypt1.in","r",stdin);
    freopen("crypt1.out","w",stdout);
    int n,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        a[x]++;//输入，进桶
    }
    int s1=0;
    for(int i=100;i<=999;i++)
    {
        for(int j=10;j<=99;j++)
        {
            if((i*j)>9999)
            {
                continue;
            }
            if(ss(i,j)==1)
             {
                 s1++;
             }
        }//枚举所有的三位数和二位数，如果是，计数器加一
    }
    cout<<s1<<endl;//输出
    return 0;
}
```
最后，让我们膜拜一下桶吧！！ ！

music
~~我才不会告诉你复制时要把freopen注释掉呢！~~


---

## 作者：mod998244353 (赞：3)

本题只是一个暴力枚举的题，只需要满足：

- 位数要求：两个部分乘积是三位数，最终乘积是四位数。
- 数字要求：只能用给出的 $n$（$1≤n≤9$）个数字。

**思路：**

枚举两个乘数即可：
```cpp
for(int i=100; i<1000; ++i)
  {
    for(int j=10; j<100; ++j)
    {
      if(判断)
      {
        ++cnt;
      }
    }
  }
```
**优化：**

设上面的乘数百位为$9$，因为每个数字都不能为$0$，又因为“部分乘积”是三位数，所以下面的乘数必须是$11$：
```cpp
        9**
   x     11
   --------
        9**
       9a*
   --------
       ****
```
我标记的位置 $a$,因为每个数字都不是$0$,所以百位就会进位，千位也会进位，就不符合位数要求。

设下面的乘数十位为$9$，因为每个数字都不能为$0$，又因为“部分乘积”是三位数，所以上面的乘数必须是$111$：
```cpp
         111
   x      9*
   ---------
         a**
        999
   ---------
        ****
```
我标记的位置 $a$,因为每个数字都不是$0$,所以百位就会进位，千位也会进位，就不符合位数要求。

所以，两个乘数的首位都不能为$9$。

但是，还能优化，举个例子，当 $i=125$ 时，因为与$10000$的差$<i$ 了，再枚举就五位数了，枚举至 $j=80$ 即可，所以 $j$ 只要枚至 $\frac{10000}{i}$即可。

综上所述，$i$ 只用枚至$899$，$j$ 只用枚至$\frac{10000}{i}$。
```cpp
#include <bits/stdc++.h>
#define R register
using namespace std;
int n,num,cnt=0;
bool p[10];
inline int read()
{
  R int x=0;
  R char c=getchar();
  for(; c<'0'  || c>'9';  c=getchar());
  for(; c<='9' && c>='0'; c=getchar())
    x=(x<<3)+(x<<1)+c-'0';
  return x;
}
bool numcheck(int n)
{
  for(; n; n/=10)
  {
    if(!p[n%10])//每位判断
    {
      return false;
    }
  }
  return true;
}
bool check(int x,int y)
{
  R int part1=x*(y%10),part2=x*(y/10),cj=x*y;
  if(part1>999
      ||part2>999
      ||cj>9999)return false;//位数要求
  if(numcheck(x)
      &&numcheck(y)
      &&numcheck(part1)
      &&numcheck(part2)
      &&numcheck(cj))
    return true;//数字要求
  return false;
}
int main()
{
  for(memset(p,false,sizeof(p)),n=read(); n; --n)//输入
  {
    num=read();
    p[num]=true;
  }
  for(R int i=111; i<900; ++i)//暴力，++i稍快
  {
    for(R int j=11,p=10000/i; j<=p; ++j)
    {
      if(check(i,j))
      {
        ++cnt;
      }
    }
  }
  return printf("%d",cnt),putchar('\n'),0;
}
```
只有自己敲的程序才是最好的，不要抄题解哦！

---

## 作者：封禁用户 (赞：3)

模拟＋搜索

```cpp
var
    a:array[0..9] of longint;
    b,c,d:array[1..5] of longint;
    i,ans:longint;
function ver2(v:longint):boolean;
    var
        i:longint;
    begin
        ver2:=true;
        for i:=1 to a[0] do
            if v=a[i] then ver2:=false;
    end;
procedure ver;   //验证好复杂哦
    var
        i,j,cc:longint;
    begin
        fillchar(c,sizeof(c),0);
        for i:=1 to 3 do begin   //用高精度思想模拟计算出2个中间数和结果数
            inc(c[i],b[i]*b[4]);
            inc(c[i+1],c[i] div 10);
            c[i]:=c[i] mod 10;
            if ver2(c[i]) then exit;    //是不是给出数中的数？
        end;
        if c[4]>0 then exit;    //位数也要注意
        fillchar(d,sizeof(d),0);
        for i:=1 to 3 do begin
            inc(d[i+1],b[i]*b[5]);
            inc(d[i+2],d[i+1] div 10);
            d[i+1]:=d[i+1] mod 10;
            if ver2(d[i+1]) then exit;
        end;
        if d[5]>0 then exit;
        for i:=1 to 4 do begin
            inc(d[i],c[i]);
            inc(d[i+1],d[i] div 10);
            d[i]:=d[i] mod 10;
            if ver2(d[i]) then exit;
        end;
        if d[5]>0 then exit;   //你懂的，供大牛鄙视中......
        inc(ans);
    end;
procedure dg(v:longint);
    var
        i:longint;
    begin
        if v>5 then ver  //ver=verify
        else
             for i:=1 to a[0] do begin
                 b[v]:=a[i];
                 dg(v+1);   //加数字
             end;
    end;
begin
    assign(input,'crypt1.in');reset(input);
    assign(output,'crypt1.out');rewrite(output);
    readln(a[0]);
    for i:=1 to a[0] do read(a[i]);
    readln;
    ans:=0;
    dg(1);   //暴搜，从这里开始......
    writeln(ans);
    close(input);close(output);
end.
```

---

## 作者：ShineEternal (赞：2)

这题也调了好久，记录一下收获，顺便提醒一下后人。。。

# 分析：

这道题思路是枚举每一种竖式，这个没什么，主要是里面的判断：

- 刚开始要判断循环到的i，j在不在给定数列里（好吧这个我知道）
- 然后要判断乘出来的所有数在不在给定数列里（这个我忘考虑了，最后观察输出才想起来，检查过程详见注释）
- 还要判断乘出来的数字位数与原题对不对应（这个显然）

**下面就可以上代码了，check函数是判断在不在给定数列的，然鹅刚开始的第一步判断因为没有想到第二步，所以就没有写到函数里，最后就不想改了QAQ**


> code:

```cpp
#include<cstdio>
using namespace std;
int a[105],tmp[10],ls[105];
int n;
int check(int x)
{
	int cnt=0;
	while(x)
	{
		ls[++cnt]=x%10;
		x=x/10;
	}
	for(int i=1;i<=cnt;i++)
	{
		int flag=0;
		for(int j=1;j<=n;j++)
		{
			if(ls[i]==a[j])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)return 0;
	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int ans=0;
	for(int i=100;i<=999;i++)
	{
		for(int j=10;j<=99;j++)
		{
			int k=i,upf=0,cnt=0,flag;
			while(k)
			{
				tmp[++cnt]=k%10;
				k/=10;
			}
			for(int k=1;k<=cnt;k++)
			{
				flag=0;
				for(int h=1;h<=n;h++)
				{
					if(tmp[k]==a[h])
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					upf=1;
					break;
				}
			} 
			if(upf==1)
			continue;
			k=j,upf=0,cnt=0;
			while(k)
			{
				flag=0;
				tmp[++cnt]=k%10;
				k/=10;
			}
			for(int k=1;k<=cnt;k++)
			{
				flag=0;
				for(int h=1;h<=n;h++)
				{
					if(tmp[k]==a[h])
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					upf=1;
					break;
				}
			} 
			if(upf==1)
			continue;
			int x=j%10;
			int y=(j/10)%10;
			int xx=i*x;
			int yy=i*y;
			int z=xx+yy*10;
			//printf("%d %d %d %d %d\n",i,j,xx,yy,z);
			cnt=0;
			if(check(xx)==0)continue;
			while(xx)
			{
				cnt++;
				xx=xx/10;
			}
			if(cnt!=3)
			continue;
			
			cnt=0;
			if(check(yy)==0)continue;
			while(yy)
			{
				cnt++;
				yy=yy/10;
			}
			if(cnt!=3)
			continue;
			
			cnt=0;
			if(check(z)==0)continue;
			while(z)
			{
				cnt++;
				z=z/10;
			}
			if(cnt!=4)
			continue;
			//printf("ds\n");
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：kkkk0369 (赞：2)

好像还没有和我一样用如此暴力的方法……

---------------------------------------------------------------

---------------------------------------------------------------

就是直接用5个变量不断循环找，时间复杂度O(n^5)。谁让n这么小呢……

判断的话，开个10的桶就好，楼下的题解也已经讲了。

下面是**AC**代码：

```cpp
#include<cstdio>
using namespace std;
long long ans;
int a[10];
int b[10];
bool pd1(int x)
{
    int y1=x%10,y2=x/10%10,y3=x/100;
    if ((b[y1])&&(b[y2])&&(b[y3])) return true;
    else return false;
}
bool pd2(int x)
{
    int y1=x%10,y2=x/10%10,y3=x/100%10,y4=x/1000;
    if ((b[y1])&&(b[y2])&&(b[y3])&&(b[y4])) return true;
    else return false;
}
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);b[a[i]]=1;
    }
    int i1,i2,i3,i4,i5;
    for(i1=1;i1<=n;i1++)
    for(i2=1;i2<=n;i2++)
    for(i3=1;i3<=n;i3++)
    for(i4=1;i4<=n;i4++)
    for(i5=1;i5<=n;i5++)
    {
        int x1=a[i1]*100+a[i2]*10+a[i3],x2=a[i4]*10+a[i5];
        int fir=x1*a[i5],sec=x1*a[i4],last=x1*x2;
        if ((fir<1000)&&(sec<1000))
        if ((pd1(fir))&&(pd1(sec))&&(pd2(last))) ans++;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：COPPERTHIC (赞：1)

~~做这题你需要小学数学基础~~


被题目坑了我也对我的语文很无奈

其实暴力就好，你看三位乘一个两位怎么算都不会超时对吧……

强行枚举每一种可能情况，分别判断，可行方案数++

以下代码



------------





```cpp
#include <cstdio>
using namespace std;
bool book[11];
int n,ans=0;
int judge(int n)
{
    while(n)
    {
        if(!book[n%10])
            return 0;
        n/=10;
    }
    return 1;
```
}//用于判断当前数的每一位在不在给定的范围内

```cpp
int check(int a,int b)
{
    if((!(judge(a)))||(!judge(b)))
        return 0;//你的乘数不合法就不算了
    int part1=a*(b%10);
    int part2=a*(b/10);//部分积
    int res=a*b;//正经的结果
    if(part1>999||part2>999||res>9999)
        return 0;//如果你位数都超了就不用算了
    if(judge(part1)&&judge(part2)&&judge(res))
        return 1;
    return 0;
```
}//用于判断当前情况是否合乎要求

```cpp
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        book[x]=true;
    }
    for(int i=100;i<1000;i++)
    {
        for(int j=10;j<100;j++)
        {
            if(check(i,j))
                ans++;
        }
```
}//暴力
    printf("%d",ans);

    return 0;

}

---

## 作者：「QQ红包」 (赞：1)

题解by:redbag

枚举，只需要枚举两个因数就好，记得判断一些不符合条件的情况

ac记录：http://www.luogu.org/record/show?rid=701727

原文链接：http://redbag.duapp.com/?p=1009

/\*
ID: ylx14274

PROG: crypt1

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
int n,haa;/*读入用*/
int aa[10]={0},bb[10]={0},i,j,k,f,sum=0; //aa存可以用的数字，bb存这种情况,i,j,k循环控制变量 
void biaoji(int bj)//标记此牛式的此部分用了哪些数字 
{
    int a[10],hh,bbjj=bj;
    while (true)
    {
        hh=bbjj%10;//取出目前最后一位
        bb[hh]=1;//标记这一位 
        bbjj=bbjj/10;//删除目前最后一位 
        if (bbjj==0) return;//如过没了就退出 
    } 
}
int main() 
{
    freopen("crypt1.in","r",stdin);
    freopen("crypt1.out","w",stdout);
    scanf("%d",&n);//读入n 
    for (i=1;i<=n;i++)//读入n个数，存起来。 
    {
        scanf("%d",&haa);//读入 
        aa[haa]=1;//标记 
    } 
    for (i=100;i<999;i++)//疯狂的枚举
        for (j=10;j<=99;j++)
        {
            f=1;//初始化 
            if (i*j>10000) continue;//如过结果不是4位就拉倒
            if (((i*(j%10))<100)||((i*(j%10))>=1000)) continue;//如果i*j的个位不是三位数也拉倒
            if (((i*(j/10))<100)||((i*(j/10))>=1000)) continue;//如果i*j的十位不是三位数也拉倒 
            for (k=0;k<10;k++){bb[k]=0;}//bb数组初始化
            biaoji(i);//标记第一个因数 
            biaoji(j);//标记第二个因数
            biaoji(i*(j%10));//标记i*j的个位反正j是两位数 
            biaoji(i*(j/10));//标记i*j的十位 
            biaoji(i*j);//标记i*j的集，终于都标记了
            for (k=0;k<10;k++)//然后就是判断了
            {
                if (bb[k]==1)//牛式中出现了这个数字
                {
                    if (aa[k]!=1)//然而并没有允许使用这个数字 
                    f=0;
                }
            } 
            if (f==1)//如过牛式中有的都是可以用的数字，那么就统计
                sum++; 
        }
    cout<<sum<<endl;
    return 0;
}

```

---

## 作者：远航之曲 (赞：1)

S1  S4  S5

×       S2  S3

约束条件只有3个：第3、4行是3位数，第5行是4位数。我们按S1到S5的顺序搜索。

如果S1×S2>10或者S1×S3>10，则3、4行肯定不是3位数，剪枝。

即S1\*S2+S4\*S2/10>=10 || S1\*S3+S4\*S3/10>=10 剪枝
补充: 从高位到低位，从小到大填数据，如果发现乘积超过999就剪枝。


上代码

（减少代码复制，共创美好洛谷）

```cpp
#  include<iostream>
#include <cstdio>
using  namespace  std;
int  a[10],n,t;
void  init()
{
      int i,j;
      scanf("%d",&n);
      for  (i=1;i<=n;i++)
           scanf("%d",&a[i]);
}
bool  check(int b)
{
      int i,j;
      bool tt;
      while  (b>0)
      {
          j=b%10;
          tt=false;
          for  (i=1;i<=n;i++)
               if  (j==a[i])    tt=true;  
          if  (!tt)  return  false; 
          b/=10;   
      }   
      return  true;   
}
void  work()
{
      int l1,l2,l3,r1,r2,s1,s2,s3;
      for  (l1=1;l1<=n;l1++)
        for  (l2=1;l2<=n;l2++)
          for  (l3=1;l3<=n;l3++)
            for  (r1=1;r1<=n;r1++)
            {
                 s1=a[r1]*(a[l1]*100+a[l2]*10+a[l3]);
                 if  (s1>999||!check(s1))  continue;
                 for  (r2=1;r2<=n;r2++)
                 {
                      s2=a[r2]*(a[l1]*100+a[l2]*10+a[l3]);
                      if  (s2>999||!check(s2))  continue;
                      s3=s1+s2*10;
                      if  (!check(s3))  continue;
                      t++;     
                 }       
            }
void  out()
{
      printf("%d\n",t);     
}
int  main()
{
     init();     
     work();
     out();
     return 0;
}
```

---

## 作者：yz0414 (赞：1)

这题思路就是把两个乘数暴力枚举一遍，把其余数算出来后依次判断是否可行，可行就累加，最后输出

附上暴力代码：
```pascal
var n,i,j,i1,i2,i3,i4,i5,x,y,x1,y1,z,s:longint;
    a,b:array[1..10]of longint; ff,f:boolean;
begin
   readln(n);
   for i:=1 to n do read(a[i]);
   for i1:=1 to n do if a[i1]<>0 then
     for i2:=1 to n do
       for i3:=1 to n do
         for i4:=1 to n do if a[i4]<>0 then
           for i5:=1 to n do
             begin
                x:=a[i1]*100+a[i2]*10+a[i3];
                y:=a[i4]*10+a[i5];
                x1:=x*a[i5]; if x1>=1000 then continue;
                y1:=x*a[i4]; if y1>=1000 then continue;
                z:=x*y; if y>=10000 then continue;
                b[1]:=x1 div 100;
                b[2]:=x1 mod 100 div 10;
                b[3]:=x1 mod 10;
                b[4]:=y1 div 100;
                b[5]:=y1 mod 100 div 10;
                b[6]:=y1 mod 10;
                b[7]:=z div 1000;
                b[8]:=z mod 1000 div 100;
                b[9]:=z mod 100 div 10;
                b[10]:=z mod 10;
                ff:=true;
                for i:=1 to 10 do
                  begin
                     f:=false;
                     for j:=1 to n do
                       if b[i]=a[j] then
                        f:=true;
                     if not(f) then ff:=false;
                  end;
                if ff then inc(s);
             end;
   writeln(s);
end.
```


---

## 作者：maorui_cow (赞：1)

这道题的意思是：每个‘'*'号都代表着n个数中的一个。只要能满足式子就可以了。
楼下的各位把题都想难了，这道题用哈希将为指标及后用循环暴力枚举就可以了。
```
#include<bits/stdc++.h>
using namespace std;
int a[10010],ans=0,b[11],c[11];
int pd1(int n)
{
	int i,k=0;
	memset(b,0,sizeof(b));
	while(1)
	{
		k++;
		b[k]=n%10;//记下每个数字
		n/=10;
		if(n==0)
		{
			break;
		}
	}
	for(i=1;i<=k;i++)
	{
		if(c[b[i]]!=1)//查看标记
		{
			return 0;
		}
	}
	return 1;
}
int pd(int i,int j,int k,int u,int v)
{
	int a1,a2,a3;
	a1=(i*100+j*10+k)*(u*10+v);//将各个数求出来
	a2=(i*100+j*10+k)*v;
	a3=(i*100+j*10+k)*u;
	if(!(a1<=9999&&a2<=999&&a3<=999))//判断是否大于目标
	{
		return 0;
	}
	if(pd1(a1)==0||pd1(a2)==0||pd1(a3)==0)//判断是否有没有多余数字
	{
		return 0;
	}
	return 1;
}
int main()
{
	int i,j,k,u,v,n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//输入数据
		c[a[i]]=1;//进行标记
	}
	for(i=1;i<=n;i++)//五重循环（身为蒟蒻的我觉得这样很方便）我试过了，不会超时
	{
		for(j=1;j<=n;j++)
		{
			for(k=1;k<=n;k++)
			{
				for(u=1;u<=n;u++)
				{
					for(v=1;v<=n;v++)
					{
						if(pd(a[i],a[j],a[k],a[u],a[v])==1)//判断函数
						{
							ans++;//结果+1
						}
					}
				}
			}
		}
	}
	printf("%d\n",ans);//输出结果
	return 0;
}

```

---

## 作者：Salamander (赞：1)

用暴力枚举，枚举两个乘数的每一位可以减少判断和循环次数。

```cpp
#include<cstdio>
int i,j,k,l,p;
int n,a[10];
bool f1()//判断第二个数的个位乘上第一个数
{
    bool z1=0,z2=0,z3=0;
    int z=(a[i]*100+a[j]*10+a[k])*a[p];
    for(int q=1;q<=n;q++)
    {
        if(z/100==a[q])z1=1;
        if(z%10==a[q])z3=1;
        if(z/10%10==a[q])z2=1;
    }
    if(z1&&z2&&z3)return true;
    return false;
}
bool f2()//判断第二个数的十位乘第一个数
{
    bool z1=0,z2=0,z3=0;
    int z=(a[i]*100+a[j]*10+a[k])*a[l];
    for(int q=1;q<=n;q++)
    {
        if(z/100==a[q])z1=1;
        if(z%10==a[q])z3=1;
        if(z/10%10==a[q])z2=1;
    }
    if(z1&&z2&&z3)return true;
    return false;
}
bool f3()//判断积是否合法
{
    bool z1=0,z2=0,z3=0,z4=0;
    int z=(a[i]*100+a[j]*10+a[k])*(a[l]*10+a[p]);
    for(int q=1;q<=n;q++)
    {
        if(z/1000==a[q])z1=1;
        if(z/100%10==a[q])z2=1;
        if(z/10%10==a[q])z3=1;
        if(z%10==a[q])z4=1;
    }
    if(z1&&z2&&z3&&z4)return true;
    return false;
}
int main()
{
    int ans=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            for(k=1;k<=n;k++)
                for(l=1;l<=n;l++)
                    for(p=1;p<=n;p++)
                        if((a[i]*100+a[j]*10+a[k])*a[p]<=999&&(a[i]*100+a[j]*10+a[k])*(a[l]*10+a[p])<=9999&&f1()&&f2()&&f3())//满足条件
                        {
                            ans++;
                        }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Saberlve (赞：0)

# 纯暴力

我看大多数题解都是算出了3位4位数，而我就直接把每一位上的数暴力算出来，很好理解。不过要注意细节，每一次枚举前都要把数清零，并且是+=处理进位，否则就会无限WA

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int sign[100],r[100];
int a1=0,a2=0,a3=0,b1=0,b2=0,b3=0,c1=0,c2=0,c3=0,c4=0;
int main()
{
	int n,x,ans=0,tmp;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		r[i]=x;
		sign[x]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				for(int a=1;a<=n;a++)
					for(int b=1;b<=n;b++)
					{
						a1=0,a2=0,a3=0,b1=0,b2=0,b3=0,c1=0,c2=0,c3=0,c4=0;
						a3+=r[k]*r[b];if(a3>=10){a2+=a3/10; a3%=10;	}     
						a2+=r[j]*r[b];if(a2>=10){a1+=a2/10; a2%=10;	} 
						a1+=r[i]*r[b];if(a1>=10){continue;	} 
						if(!sign[a1]||!sign[a2]||!sign[a3])continue;
						b3+=r[k]*r[a];if(b3>=10){b2+=b3/10; b3%=10;  };
						b2+=r[j]*r[a];if(b2>=10){b1+=b2/10; b2%=10;  };
						b1+=r[i]*r[a];if(b1>=10){continue;  };
						if(!sign[b1]||!sign[b2]||!sign[b3])continue;
						c4+=a3;
						c3+=a2+b3; if(c3>=10){c2+=c3/10; c3%=10;  };
						c2+=a1+b2; if(c2>=10){c1+=c2/10; c2%=10;  };
						c1+=b1; if(c1>=10)continue;
						if(!sign[c1]||!sign[c2]||!sign[c3]||!sign[c4])continue;
//						if(sign[a1]||sign[a2]||sign[a3]||sign[b1]||sign[b2]||sign[b3]||
//						sign[c1]||sign[c2]||sign[c3]||sign[c4])
						ans++;
//						cout<<"  "<<a1<<" "<<a2<<" "<<a3<<endl;
//						cout<<b1<<" "<<b2<<" "<<b3<<endl;
//						cout<<c1<<" "<<c2<<" "<<c3<<" "<<c4<<endl;
					}
					
	cout<<ans;
}	

```


---

## 作者：I_Am_Danny (赞：0)

本蒟蒻第一次写题解，如果嫌啰嗦请跳到分割线以下

看到好多大佬用暴力跑的贼快，感觉没多少用搜索的c，就写了这么个玩意

这道题比较水，用了一个搜索就可以完美卡了过去[一脸坏笑]

（事实上，这题的数据太弱，强一点的话搜索反而占优势）

个人这道题可以用来练搜索

---------------

以下是我的思路：

1.从0，0开始搜索

2.每次在两个数后面分别加一个数，继续搜索

3.判重，剪枝见程序

4.如果可以，就把这个数对压到一个set里去，当然大佬们也可以手动判重，用vector或数组来装

~~个人比较喜欢STL这个东西，当然~~不用STL的我也会给

献上完整代码：
```cpp
/*              //USACO Training 模板 
ID: I_Am_Danny  //比较皮的昵称 
LANG: C++
PROB:
*/
#include <bits/stdc++.h>//我是黄色的注释！
using namespace std;
const int inf=1e9+7;
vector<int> g;//存储可以用的数字 
set<pair<int,int> > st;//因为搜索会有重复，所以可以用set去重。当然一些大佬也可以用数学方法解决 
int m;//可以用的数字个数 
bool find(int p)//看这个数字(划重点：数字！)是否可以用 
{
	for(int i=0;i<(int)g.size();i++)//搜索整张图 
	if(g[i]==p) return true;//找到就返回真 
	return false;//走到这里一定是没找到 
}
bool check(int q)//检查这个数能不能用 
{
	while(q>=10)//逐位检查数字 
	{
		if(!find(q%10)) return false;//不可以用就返回不是 
		q/=10;//每次q都删掉最后一位 
	}
	return find(q);//最后一位可以直接返回 
}
void run(int x,int y)//搜索开始，x代表第一个数，y代表第二个数，策略是逐个添加末位数，直到位数符合为止 
{
	if(x>999 || y>99) return;//因为x是三位数，y是两位数 
//	if(st.count(make_pair(x,y))) return;//剪枝 
	if(x>=100 && x<=999 && y>=10 && y<=99)//位数条件符合 
	{
		int xx=x,yy=y;//临时存储 
		int tt;//临时存储当前位的运算结果 
		tt=xx*yy;//先从最后得到的结果检查起 
		if(!check(tt) || tt<1000 || tt>9999) return;
		while(yy>=10)//逐位检查数字 
		{
			tt=xx*(yy%10);//检查每一个部分的乘积 
			if(!check(tt) || tt<100 || tt>999) return;//位数不符或者有不应该存在的数 
			yy/=10;//每次yy都删掉最后一位 
		}
		if(!check(xx*yy)) return;//检查最后一位 
		st.insert(make_pair(x,y));//插入答案 
		
//		cout<<x<<" "<<y<<endl; //本蒟蒻用来自测的 

		return;//因为两个数位数都符合了，所以不可以再添加位数了 ，返回 
	}
	//构造下一组数 
	for(int i=0;i<(int)g.size();i++)//循环添加每一个可以用到的数字，也保证了x和y的正确性 
	{
		run(x*10+g[i],y);//给x添加一位 
		run(x,y*10+g[i]);//给y添加一位 
	}
}
//主函数 
int main()
{
//	freopen(".in","r",stdin);  //freopen模板 
//	freopen(".out","w",stdout);

    cin>>m;//输入可用的数字个数 
    for(int i=0;i<m;i++)//循环输入数字 
    {
    	int t;
    	cin>>t;//不解释 
    	g.push_back(t);//把数字塞到一个vector里去，一会搜索用 
	}
	run(0,0);//开始搜索，一开始两个数都是零 
	
	//本蒟蒻用来检查的部分 
//	set<pair<int,int> >::iterator it=st.begin();
//	for(;it!=st.end();it++) cout<<it->first<<" "<<it->second<<endl;
	
	cout<<st.size()<<endl;//输出答案个数 
	return 0;//结束程序 
}
```

不用STL：
```cpp
int index=0;
int used[1000000][2];
bool panchong(int x,int y)
{
	for(int i=0;i<index;i++)
	if(used[i][0]==x && used[i][1]==y) return true;
	return false;
}

void cunchu(int x,int y)
{
	used[index][0]=x;
	used[index++][1]=y;
}

void out()
{
	cout<<index<<endl;
}
```

---

## 作者：knight9 (赞：0)

    
    
```cpp
//crypt
#include<cstdio>
int n,m,x,q,i,j,p,pi,a,b,c,s,y,sum,mi[10001],su[11],at[1001],t;//mi用来存数据，su用来数组查重，at用来建立三位数的数据
bool fi(int v)//判断各个数是否在给定数范围内
{
    int v1,v2,v3,v4,v5;
    v1=v/10000;
    v2=v%10000/1000;
    v3=v%1000/100;
    v4=v%100/10;
    v5=v%10;
    if(v1>0)  return false;
    if (v1==0)
    {
        if (v2==0)
        {
            if ((su[v3]==1)&&(su[v4]==1)&&(su[v5]==1)) return true;
        }
        else if ((su[v2]==1)&&(su[v3]==1)&&(su[v4]==1)&&(su[v5]==1)) return true;
    }
    else if ((su[v1]==1)&&(su[v2]==1)&&(su[v3]==1)&&(su[v4]==1)&&(su[v5]==1)) return true;
}
int main()
{
    freopen("crypt.in","r",stdin);
    freopen("crypt.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        scanf("%d",&m);
        mi[i]=m;
        su[m]=1;
    }
    for(i=1;i<=n;i++)/排序可有可无
     for (j=i+1;j<=n-1;j++)
     {
         if (mi[i]>mi[j]) {
             t=mi[j];
             mi[j]=mi[i];
             mi[i]=t;
         }
     }
    i=0;
    for (a=1;a<=n;a++)
        for (b=1;b<=n;b++)
            for (c=1;c<=n;c++)
            {
                i++;
                at[i]=mi[a]*100+mi[b]*10+mi[c];//生成三位数的数据
            }
    s=i;
    for (i=1;i<=s;i++)//生成第一因数 
        for (j=1;j<=n;j++)//生成第二因数个位 
        {
            x=at[i]*mi[j];//第一部分乘积 
            if (fi(x)&&(x<1000))//判断x是否在给定范围内以及是否在规定格式限制内
            {
                for (q=1;q<=n;q++)//生成第二因数十位 
                {
                    y=at[i]*mi[q];//第二部分乘积 
                    if (fi(y)&&(y<1000))//判断y是否在给定范围内以及是否在规定格式限制内
                    {
                        pi=x+y*10;//建立最后的积
                        if(fi(pi)) sum++;//计数                
                    }
                }
            }
         } 
    printf("%d",sum);
    return 0;
}
```

---

