# non hates math

## 题目背景

non习惯将分数化成小数，但在数学中要以分数形式写，不能化成小数

因此non找到了会编程的你，帮助他将小数化回分数


## 题目描述

给出一个小数，将它化成假分数的形式


小数的类型有2种：（不考虑无限不循环小数）

普通小数

循环小数（会给出循环节）

（循环节用( )表示）


## 说明/提示

输入小数的数据范围

0至1000


对于50%的数据保证没有循环节

对于20%的数据需要读入优化


## 样例 #1

### 输入

```
1.32```

### 输出

```
33/25```

## 样例 #2

### 输入

```
1.(3)```

### 输出

```
4/3```

## 样例 #3

### 输入

```
1.0```

### 输出

```
1/1```

# 题解

## 作者：FCB_Yiyang2006✈ (赞：17)

# 蒟蒻我编程一窍不通，数学却略知一二
还是能用哪一丢丢数学知识来招架此题。（也许吧）

#### 1.有限小数（没有循环节）：1.125
小数点后的/小数点后的位数*10 。
#### 2.纯循环小数：1.（3)
循环节/有几位写几个9
#### 3.混循环小数:1.1(6)
小数点后所有-不循环部分/循环节有几位写几个9，不循环部分有几位添几个0。

### 最后还有很重要的一项：
## 约分！！！
上代码（终于.......）

蒟蒻代码，极其冗长，敬请谅解。

```cpp
#include<bits/stdc++.h>//万能脑袋
using namespace std;
int t,k;
char s[1005];//小数点和小数点后用CHAR读入
int a[1005];//把CHAR化为INT
int ys(int m,int n)//约分，就是求最大公因数
{
   int r;
   r = m%n;  
   while(r!=0)
   {        
	m = n;
        n = r;
        r = m%n;
   }
   //辗转相除
   return n;
}
bool yx()//判断是否有循环节
{
	for(int i=1;i<=strlen(s);i++)
	{
		if(s[i]=='(')
		{
			return false;
		}
	}
	return true;
}
int main()//低调的主晗二叉树
{
	cin>>t;	//整数部分
	cin>>s;//小数部分
	for(int i=1;i<=strlen(s);i++)
	{
		if(s[i]>='0'&&s[i]<='9')
		{
			k++;
			a[k]=s[i]-'0';//将小数点后变成INT
		}
	}
	if(yx()==true)//没有循环节
		int fm=pow(10,k);
		int fz=a[1];
		for(int i=2;i<=k;i++)
		{
			fz=fz*10+a[i];
		}//分子用INT
		fz=fz+t*fm;//带分数化成假分数
		cout<<fz/ys(fz,fm)<<'/'<<fm/ys(fz,fm);
	}
	if(yx()==false)//有循环节
	{
		if(s[1]=='(')//纯循环
		{
			int sum=0;//循环节的位数
			for(int i=2;;i++)
			{
				if(s[i]==')')
				{
					break;
				}
				sum++;
			}
			int fm=pow(10,sum)-1;
			int fz=a[1];
			for(int i=2;i<=sum;i++)
			{
				fz=fz*10+a[i];
			}
			fz=fz+t*fm;
			cout<<fz/ys(fz,fm)<<'/'<<fm/ys(fz,fm);
		}
		else//混循环
		{
			int p;//记录循环节的起始
			int sum1=0;//不循环位数
			int sum2=0;//循环位数
			for(int i=1;;i++)
			{
				if(s[i]=='(')
				{
					p=i;
					break;
				}
				sum1++;
			}
			for(int i=p;;i++)
			{
				if(s[i]==')')
				{
					break;
				}
				sum2++;
			}
			sum2-=1;
			int fm=(pow(10,sum2)-1)*(pow(10,sum1));
			int fz=a[1];//整体
			int fz1=a[1];//不循环部分
			for(int i=2;i<=sum2+sum1;i++)
			{
				fz=fz*10+a[i];
			}
			for(int i=2;i<=sum1;i++)
			{
				fz1=fz1*10+a[i];
			}
			fz=fz-fz1;//减去不循环部分
			fz=fz+t*fm;
			cout<<fz/ys(fz,fm)<<'/'<<fm/ys(fz,fm);
		}
	}
	return 0;//结束了，结束了，结束了！
}
```
本蒟蒻心地善良，代码中没有任何错误，复制提交可以直接AC,但蒟蒻建议：
## 非紧急情况不要用此功能！

---

## 作者：111l (赞：10)

先介绍一个原理：0.(n)=n  /  循环节位数个9;

我的思路是利用上述原理求无限循环小数，其他就是~~数论~~模拟了

上代码
```cpp
#include<iostream>
#include<iomanip>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
const char _9[21]={'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'};//原理实现
int lx,rx=0,fm,fz;
char s[21];
int add_0(int n){
	int sum=1;
	for(int i=1;i<=n;i++){
		sum*=10;
	}
	return sum;
}//填零
int gcd(int a,int b){
    if(a%b==0){
        return b;
    }
    else return gcd(b,a%b);
}//约分
int main(){
    scanf("%d.",&lx);
    scanf("%s",&s);
    int l=strlen(s),f=0;
    for(int i=0;i<l;i++){
        if(s[i]=='('){
            f=i;//找括号，如果有则是无限循环小数
            break;
        }
    }
    if(s[f]=='('){//循环小数处理
    	int ss=0;
    	for(int i=0;i<f;i++){
    		ss=ss*10+(int)s[i]-'0';
		}
		if(!ss){//是纯循环小数
        	if(s[f+1]=='9'&&s[f+2]==')'){
            	cout<<lx+1<<"/1";//0.(9)=1
         	   	return 0;
        	}
        	for(int i=f+1;i<l;i++){
        	    if(s[i]>='0'&&s[i]<='9'){
        	        rx=rx*10+(int)s[i]-48;
         	   	}
        	}
        	int tmp=rx,ii=0;
        	while(tmp){
        	    ii++;
        	    tmp/=10;
        	}
        	fz=rx;
        	fm=0;
        	for(int i=0;i<ii;i++){
        	    fm=fm*10+(int)_9[i]-'0';//给分母加9
        	}
        	tmp=rx;
        	fz/=gcd(fz,fm);
        	fm/=gcd(tmp,fm);
        	fz+=lx*fm;//整数部分处理
        	printf("%d/%d",fz,fm);
        	return 0;
		}
		else if(ss&&lx==0){//部分循环小数处理
        //先将普通小数部分分离出来，再在答案中处理
			for(int i=f+1;i<l;i++){
            	if(s[i]>='0'&&s[i]<='9'){
             	   rx=rx*10+int(s[i]-48);
            	}
        	}
        	int tmp=rx,ii=0;
        	while(tmp){
           		ii++;
            	tmp/=10;
        	}
        	fz=rx;
        	fm=0;
        	for(int i=0;i<ii;i++){
            	fm=fm*10+(int)_9[i]-'0';
        	}
        	tmp=rx;
        	fz/=gcd(fz,fm);
        	fm/=gcd(tmp,fm);
        	int _tmp=ss,cnt=0;
        	while(_tmp){
        		cnt++;
        		_tmp/=10;
			}
			_tmp=add_0(cnt);
        	printf("%d/%d",ss*fm+rx,fm*_tmp);
        	return 0;
		}//都差不多
    }
    else{
    //普通小数直接模拟就好了，分母填零再约分
        int k=l;
        while(s[k]=='0'){
            k--;
        }
        int ll=strlen(s);
        fm=1;
        for(int i=0;i<=k;i++){
            if(s[i]>='0'&&s[i]<='9'){
                rx=rx*10+int(s[i]-48);
            }
        }
        fz=rx;
        int temp=rx,ii=0;
        while(temp){
            ii++;
            temp/=10;
        }
        for(int i=1;i<=k;i++){
            fm*=10;
        }
        int f=gcd(fz,fm);
        temp=rx;
        fz/=f;
        fm/=f;
        fz+=lx*fm;
        printf("%d/%d",fz,fm);
    }
}
//圆满结束
```

---

## 作者：Nemlit (赞：8)

具体思路楼下降得很清楚了，
~~使这道题从数论便成了一道模拟~~，
这道题是很久以前写的，
自己都觉得代码有点丑，
不过将就一下吧，
毕竟90几行的代码也不容易。
由于没有c/c++代码，
我就来此水一发：
```
#include<bits/stdc++.h>
using namespace std;
int m1,m2,m3,w1,i,k,l,temp,temp1,temp2,temp3,temp4,temp5,num,num1,a;//定义一大堆变量
char s[100005];
bool bb;
inline int mi(int a,int b){
    int sum=1;
    for(int i=1;i<=b;i++)
        sum*=a;
    return sum;
}//用于取10的n次方
inline int gcd(int a,int b){
    if(a%b==0)
        return b;
    return gcd(b,a%b);
}//用于约分
int main(){
    cin>>s;
    for(int i=0;i<strlen(s);i++){
        if(s[i]=='('){
            bb=1;
            w1=i;
            break;
        }
    }//先看看是不是循环小数
    if(!bb){
 		k=l=strlen(s)-1,temp4=temp5=i;
        while(s[i]!='.'){
            m1*=10;
            m1+=s[i++]-'0';
        }
        while(s[k--]=='0')
            l--;
        bb=1;
        for(int j=i+1;j<=l;j++){
            if(s[j]=='0'&&bb)
                temp4=j;
            else
                bb=0;
            m2*=10;
            m2+=s[j]-'0';
        }
        num=0,temp3=m2;
        while(temp3){
            temp3/=10;
            num++;
        }
        num+=temp4-temp5;
        temp=mi(10,num);
        a=m1*temp+m2;
        temp2=gcd(a,temp);
        cout<<a/temp2<<'/'<<temp/temp2<<endl;
        return 0;
    }//有限小数思路比较简单，这里就不多说了，主要思路是：乘n个10使其成为整数，然后再约分就可以了
    i=0;
    while(s[i]!='.'){
        m1*=10;
        m1+=s[i++]-'0';
    }
    for(int j=i+1;j<w1;j++){
        m2*=10;
        m2+=s[j]-'0';
    }
    for(i=w1+1;i<strlen(s)-1;i++){
        m3*=10;
        m3+=s[i]-'0';
    }
    num=0,temp3=m2;
    while(temp3){
        temp3/=10;
        num++;
    }
    temp=mi(10,num);
    a=m1*temp+m2;
    temp3=m3;
    num1=0;
    while(temp3){
        temp3/=10;
        num1++;
    }
    temp=mi(10,num1);
    temp4=a*temp+m3;
    temp4-=a;
    temp=mi(10,num);
    temp3=mi(10,num1+num);
    temp2=gcd(temp4,temp3-temp);
    cout<<temp4/temp2<<'/'<<(temp3-temp)/temp2<<endl;
    return 0;
}//无限循环小数的话，先把它乘上一个10的幂次，再把原数乘上一个10更小的幂次，再将它们相减，用它和两个10的幂次的差约分就可以了。
```

---

## 作者：神阈小杰 (赞：6)

介绍一个原理：0.(n)=n/999... (循环的数的位数个9)；  
（1）循环小数分为：纯循环小数和混循环小数.  
（2）纯循环小数的化法是：
如,0.（ab）=ab/99,最后化简.  
举例如下：  
	0.（3）=3/9=1/3；  
	0.（7）=7/9；  
	0.（81）=81/99=9/11；  
	1.（206）=1+206/999=1205/999.  
（3）非纯循环小数的化法是：  
如,0.a（bc）=a/10+bc/99=（abc－a）/990.最后化简.  
举例如下：  
0.5（1）=（51－5）/90=46/90=23/45；  
0.29（54）=（2954－29）/9900=13/44；  
1.4（189）=1+（4189－4）/9990=1+4185/9990=105/74.

上代码
```cpp
# include <cstdio>
# include <cstring>
# include <iostream>
using namespace std;
char shu[1000];
int s[5],a;//s[1]为整数,s[2]为小数 
long long z;//分子 
long long zzz;//分母 
int l;//总长 
int ji;//普通小数整数的位数
int sss;//循环小数的循环的数
int jiu;//999...
int _ji;//小数点到循环节中间的数的个数&&判断是否为纯循环小数 
bool pan;//判断是否为循环小数;
long long yue;//最大公约数 
long long gcd(long long a,long long b)//求最大公约数 
{
	if(a%b==0) return b;
	else return gcd(b,a%b);
}
int main()
{
	a=1;//记录整数
	zzz=1;//初始化
	pan=false;
	cin.getline(shu,sizeof(shu));
	l=strlen(shu);
	for(int i=0;i<l;i++)
	{
		if(shu[i]=='.')
		{
			ji=i;
			a++;//记录小数
			continue;
		}
		if(shu[i]=='(')//如果为循环小数 
		{
			pan=true;//循环小数 
			_ji=i-ji-1;//是否为纯循环小数 
			z=s[2];
			for(int j=i+1;j<l-1;j++)
			{
				sss=sss*10+(shu[j]-'0');
				jiu=jiu*10+9;
				z*=10;
			}
		}
		if(pan==true) break;
		s[a]=s[a]*10+(shu[i]-'0');
	}
	if(pan==false)//如果为普通小数 
	{
		if(s[2]!=0)//小数部分不为0 
		{
			z=s[2];//分子
			for(int i=1;i<(l-ji);i++) zzz*=10;//分母 
			yue=gcd(zzz,z);//最大公约数 
			z/=yue;
			zzz/=yue;
			z+=zzz*s[1];
		}
		else z=s[1];//分子
	}
	else//如果为循环小数 
	{
		if(_ji==0)//如果为纯循环小数 
		{
			z=sss;//分子
			zzz=jiu;//分母 
			yue=gcd(zzz,z);
			z/=yue;
			zzz/=yue;
			z+=zzz*s[1];
		}
		else//如果为非纯循环小数 
		{
			z=z+sss-s[2];//分子
			zzz=jiu;
			for(int i=1;i<=_ji;i++) zzz*=10;//分母 
			yue=gcd(zzz,z);
			z/=yue;
			zzz/=yue;
			z+=zzz*s[1];
		}
	}
	printf("%lld/%lld",z,zzz);
	return 0;
}
```
第一次发题解，可能质量不太高。

---

## 作者：LZY151114 (赞：5)

##### 蒟蒻第二发题解~~（第三发）~~
##### 本蒟蒻对数学略知一二，所以萌生了写题解的想法。。。
##### 以上皆为瞎扯淡，接下来我们来讲正事~~~
##### 题目传送门：[P2399 non hates math](https://www.luogu.org/problem/P2399)
##### 题目大意：小数化假分数（无限不循环忽略）。
##### 然后我们来一步步分析
##### 首先，分析最简单的情况：有限不循环小数：
##### 对于有限不循环小数，我们假设小数为a.b，那么0.b就化为b/10(b的位数个0)，约分后将整数部分乘上分母再加上原分子得到答案。
##### eg：1.3,0.3化为3/10，然后1*10+3得13为分子，所以答案是13/10。
##### 第二步，有限纯循环小数：
##### 对于有限纯循环小数，我们设它为a.(b)，根据数学知识可知0.(b)可化为b/9（b的位数个9），约分后整数部分如法炮制。
##### eg：1.(3)，0.(3)可化为3/9=1/3，然后1*3+1=4得分子，得到答案4/3。
##### 最后一步，有限非纯循环小数：
##### 对于有限非纯循环小数，我们设它为a.b(c)，根据数学原理，它的小数部分0.b(c)应该化为(bc-b)/90(b的位数个0，c的位数个9)，约分后整数部分如法炮制。
##### eg：1.3(2)，0.3(2)化为(32-3)/90=29/90，然后1*90+29=119，得到答案119/90。
#### 最后强调别忘了约分！！！
##### 上代码（码风奇特勿喷）
```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register
#define il inline
using namespace std;
il ll gcd(ll a,ll b){return (b==0)?a:gcd(b,a%b);}  //三目gcd约分
ll a,lena,fm,fz,dfz,lend,lenfz;
char s[1005];
bool flag=false;
int main(void){
	fgets(s,1005,stdin);   //读入
	for(re int i=0;s[i]!='.';++i)lena=i;   //记录整数部分长度
	if(s[lena+2]=='('){     //有限纯循环小数
		sscanf(s,"%lld.(%lld)",&a,&fz);    //读取整数和循环节
		for(re int i=lena+2;s[i+1]!=')';++i)fm=fm*10+9;   //得到分母
		int x=gcd(fz,fm);fz/=x,fm/=x;
		fz+=a*fm;                  //求得分子并化简
		printf("%lld/%lld\n",fz,fm);
	}
	else{    //另两种情况
		for(re int i=lena;i<strlen(s);++i)if(s[i]=='(')flag=true,lend=strlen(s)-i-2,lenfz=i-lena-2;   //判断是不是有限非纯循环小数
		if(flag){     //是有限非纯循环小数
			sscanf(s,"%lld.%lld(%lld)",&a,&fz,&dfz);  //读入a.b(c)
			ll y=fz;
			for(re int i=1;i<=lend;++i)fm=fm*10+9,fz*=10;  //求分母
			for(re int i=1;i<=lenfz;++i)fm*=10;
			fz+=dfz,fz-=y;y=gcd(fz,fm);fz/=y,fm/=y;
			fz+=a*fm;   //化简得分子
			printf("%lld/%lld\n",fz,fm);
		}
		else{   //有限不循环小数
			sscanf(s,"%lld.%lld",&a,&fz);  //读入
			fm=1;
			for(re int i=lena+2;i<strlen(s);++i)fm*=10;  //求分母
			ll x=gcd(fz,fm);fz/=x,fm/=x;
			fz+=a*fm;  //化简得答案
			printf("%lld/%lld\n",fz,fm);
		}
	}
	return 0;
}
```
##### emmmmmm，代码41行。恭喜你又过了一道~~绿绿的~~题目

---

## 作者：Minecraft万岁 (赞：4)

首先看到这题 明显分类讨论 一个是没有循环节的 另一个是有循环节的 ~~废话~~ 


### 没有循环节的  
拿样例来说吧 比如 $1.32$  
我们令  
$$x=1.32$$ 
则有  
$$100x=132$$ 
所以说 
$$x=132\div100$$ 
然后就可以快乐的 $gcd$ 了  
 
~~看出了规律~~ 如果令 $y$ 为小数点后的数字位数  
则数字可以这样做  
$1.$ 讲原来的小数化成最小的正整数  
$2.$ 将这个正整数和 $10^y$ 约分输出

------------ 
### 有循环节的  
在拿 $1.1(3)$ 来说  
老样子 令   
$$x=1.1(3)$$
我们想到要消去循环节部分 就变成了没有循环的套路 
写出两个式子 
$$10x=11.(3)$$ 
$$100x=113.(3)$$ 
我们不难发现 只要两个式子减一下 循环节就消掉了 ~~好轻松的~~  
的到 
$$100x-10x=113.(3)-11.(3)$$
$$90x=102$$  
$$x=102/90$$ 
最后 $gcd$ 一下   
知道计算过程 大概就知道怎么写了   
如果不懂对着代码看一下应该就懂了 


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long ull; 
ull fz,fm;
char x[20];//读入的小数变成char  
int lenx;//小数长度 
bool kh; 
inline void read(int &x)//快读 然而没什么用
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)
{
	if(_x<0) return -_x;
	else return _x;
}
inline ull gcd(ull xa,ull xb)//gcd 
{
	return xb?gcd(xb,xa%xb):xa;
}
int main()
{
	scanf("%s",x);//读入 
	lenx=strlen(x);//算长度 
	for(int i=0;i<lenx;i++)//将有没有括号做为区分有没有循环节的依据 
	{
		if(x[i]=='('||x[i]==')')
		{
			kh=true;//有就不做了 
			break;
		}
	} 
	if(!kh)//没有循环节 
	{
		fz=1;
		bool kpw=false;//这里的 10 的幂次方是从小数点后开始的 不能一开始就算 
		for(int i=0;i<lenx;i++)
		{
			if(x[i]=='.') kpw=true;//遇到小数点了 
			else
			{
				if(kpw) fz*=10;//已经是小数点以后了 
				fm=fm*10+(x[i]-'0');//算整数 
			}
		}
		ull tmp=gcd(fz,fm);//gcd 
		cout<<fm/tmp<<"/"<<fz/tmp;//输出就好了 
		puts("");
	}
	else
	{
		ull x1=0;//包括循环节的整数  
		ull x2=0;//不包括循环节的整数 
		ull cnt1=0;//小数点后包括循环节的数字位数 
		ull cnt2=0;//小数点后 不包括循环节的数字位数 
		ull k1=1;//两个计算10的幂次方 也就是x的系数 
		ull k2=1;
		ull tmp=0;//暂存gcd 
		int i=0;
		while(x[i]!=')')//求包括循环节的整数 
		{
			if(x[i]!='.'&&x[i]!='(') x1=x1*10+(x[i]-'0');
			i++;
		}
		i=0;
		while(x[i]!='(')//求不包括循环节的整数  
		{
			if(x[i]!='.') x2=x2*10+(x[i]-'0');
			i++;
		}
		for(int j=0;x[j];j++)//求cnt1 
		{
			if(x[j]=='.')//要从小数点后开始 
			{
				i=j+1;
				while(x[i]!=')')
				{
					if(x[i]!='(')cnt1++;
					i++;
				}
				break;
			}
		}
		for(int j=0;x[j];j++)//求cnt2 
		{
			if(x[j]=='.')//要从小数点后开始 
			{
				i=j+1;
				while(x[i]!='(')
				{
					cnt2++;
					i++;
				}
				break;
			}
		}
		for(int i=1;i<=cnt1;i++)//计算两个x的系数 
			k1*=10;
		for(int i=1;i<=cnt2;i++)
			k2*=10;
		tmp=gcd(x1-x2,k1-k2);//这一步相减消去无穷无尽的循环节 并 求出gcd 
		cout<<(x1-x2)/tmp<<"/"<<(k1-k2)/tmp;//输出就好了 
		puts("");
	}
	return 0;
}


```


---

## 作者：Soledad_S (赞：4)

简单的字符串模拟，楼下的大佬们写的代码都偏长，我来发一波短些的

---
我们无视整数部分，只剩下三种情况，在讲解三种情况之前，我先定义些东西。

设a为整数部分，b为小数点后非循环节部分，c为循环节部分，blen是b的长度，clen同理，tot是整个小数部分。

举个栗子，对于小数13.092(0723)，a=13，b=92，c=723，blen=3，clen=4，tot=920723。**注意，前面的0在b，c中没体现，但blen,clen中要占位。**

---
~~开始愉快的分类吧。~~

### 1.没有循环节（即c==0）
 答案是$\frac{b}{pow(10,blen)}$，
 此处没写整数

### 2.只有循环节（即c!=0&&b==0）
 答案是$\frac{c}{\begin{matrix}\underbrace{9\cdots9}\\clen\end{matrix}}$

### 3.混循环（即c!=0&&b!=0）
 答案是$\frac{tot-b}{\begin{matrix}\underbrace{9...9}\\clen\end{matrix} \begin{matrix}\underbrace{0...0}\\blen\end{matrix}}$
 
代码实现很容易了吧
```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int a,b,c,blen,clen,l,r,tot;
char s[1005];
int main(){
	int x;
	scanf("%s",&s);
	for(int i=0;i<strlen(s);i++)
	  if(!isdigit(s[i])){
	  	x=i+1;//找到a与b（或c）的分界点 
	  	break;
	  }
	    else a=(a<<1)+(a<<3)+s[i]-'0';//计算a，(a<<1)+(a<<3)等同与a*10 
	for(int i=x;i<strlen(s);i++)//从分界点开始计算tot 
	  if(isdigit(s[i]))tot=(tot<<1)+(tot<<3)+s[i]-'0';
	int bj=0;//标记是否有循环节 
	for(int i=x;i<strlen(s);i++)
	  if(s[i]=='('){
	  	bj=1; 
	  	x=i+1;//找到b与c的分界点 
	  	break;
	  }
	  else b=(b<<1)+(b<<3)+s[i]-'0',blen++;//计算b及blen 
	if(bj)for(int i=x;i<strlen(s);i++)//如果有循环节就计算c及clen 
	        if(isdigit(s[i]))c=(c<<1)+(c<<3)+s[i]-'0',clen++;
    if(!c){//case 1 
    	r=pow(10,blen);
    	l=b;
    	x=__gcd(l,r);//__gcd是自带函数，NOIp不能用啊QWQ 
    	l/=x;
    	r/=x;
    	printf("%d/%d\n",a*r+l,r);
	}
	else if(!b){//case 2 
	    r=0;
		for(int i=1;i<=clen;i++)r=(r<<1)+(r<<3)+9;
		l=c;
    	x=__gcd(l,r);//__gcd是自带函数，NOIp不能用啊QWQ 
    	l/=x;
    	r/=x;
    	printf("%d/%d\n",a*r+l,r);
	}
	else {//case 3
		for(int i=1;i<=clen;i++)r=(r<<1)+(r<<3)+9;
		for(int i=1;i<=blen;i++)r=(r<<1)+(r<<3);
		l=tot-b;
    	x=__gcd(l,r);//__gcd是自带函数，NOIp不能用啊QWQ （重要的事情说三遍） 
    	l/=x;
    	r/=x;
    	printf("%d/%d\n",a*r+l,r);
	}
	return 0;
}
```


---

## 作者：CSP_Sept (赞：3)

这里介绍小数化分数的快捷方法（以下仍使用 $()$ 表示循环节）：

#### 1. 有限小数

令 $a$ 表示此小数的整数部分，$b$ 表示此小数的小数部分，$l_1$ 表示 $a$ 的位数，$l_2$ 表示 $b$ 的位数。i.e. 若该小数为 $1.2$，则 $a=1,b=2,l_1=1,l_2=1$。

这个小数 $=\dfrac{al_2+b}{10l_2}$

比如将小数 $n=1.2$ 代入，得 $n=\dfrac{1\times 10+2}{10\times 1}=\dfrac{6}{5}$。

#### 2. 无限循环小数 —— 纯循环小数

设 $n=\overline{a}.(\overline{b})$，$l_1,l_2$ 分别代表 $a,b$ 的位数，则有：

$$
n=a+\dfrac{b}{\begin{matrix}\underbrace{99\cdots99}\\\small l_2\text{ 个 }9\end{matrix}}
$$

#### 3. 无限循环小数 —— 混循环小数

设 $n=\overline{a}.\overline{b}(\overline{c})$，$l_1,l_2,l_3$ 分别代表 $a,b,c$ 的位数，则有：

$$
n=a+\dfrac{c}{\begin{matrix}\underbrace{99\cdots99}\\\small l_3\text{ 个 }9\end{matrix}\begin{matrix}\underbrace{00\cdots00}\\\small b\text{ 个 }0\end{matrix}}
$$
___
在这个程序中，我们用 $f_1,f_2,f_3$ 分别表示 $n$ 是有限小数，纯循环小数还是混循环小数。

$num_1,num_2,num_3$ 分别表示 $a,b,c$，$l_1,l_2,l_3$ 分别代表 $a,b,c$ 的位数，`make_0(int n)` 函数用来构造 $10^n$，`make_9(int n)` 函数用来构造 $10^{n+1}-1$。

我们知道，$\gcd(a,b)$ 表示 $a$ 和 $b$ 的最大公约数，化简分数有一个通用的公式（令 $f(\dfrac{x}{y})$ 函数为分数 $\dfrac{x}{y}$ 的最简分数形式）：

$$
f\left(\dfrac{x}{y}\right)=\dfrac{x\div \gcd(x,y)}{y\div \gcd(x,y)}
$$

#### 程序：

```cpp
#include <cstring>
#include <iostream>

using namespace std;
#define int unsigned long long
int gcd(int a,int b){return b?gcd(b,a%b):a;}
string s;
int num[4];
int cnt=1;
int make_0(int l){
    int i=1;
    if(!l) return 1;
    while(l--) i*=10;
    return i;
}
int make_9(int l){
    int i=0;
    while(l--){i*=10;i+=9;}
    return i;
}
bool f1,f2,f3;
bool is_p;
int l[4];
int a,b;
signed main(){
    std::ios::sync_with_stdio(false);
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='.'){
            if(s[i+1]=='('){f2=1;cnt=3;}
            else{f3=1;cnt=2;}
        }
        if(s[i]=='('){is_p=1;cnt=3;}
        if(s[i]>='0'&&s[i]<='9'){
            num[cnt]*=10,num[cnt]+=(s[i]-'0');
            l[cnt]++;
        }
    }
    f1=(!is_p);
    if(f1){
        a=num[1]*make_0(l[2])+num[2];
        b=make_0(l[2]);
    }
    else if(f2){
        a=num[3];
        b=make_9(l[3]);
        a=a+num[1]*b;
    }
    else if(f3){
        a=num[2]*make_0(l[3])+num[3]-num[2];
        b=make_9(l[3])*make_0(l[2]);
        a=a+num[1]*b;
    }
    cout<<a/gcd(a,b)<<'/'<<b/gcd(a,b);
    return 0;
}
```

---

## 作者：圣光天子 (赞：2)

这道题的话，就是单纯的小数转分数

分两种情况讨论，有限小数和无限循环小数

首先是有限小数，我们可以采用把它乘上一个10的幂次使其成为整数，

然后再把它和那个10的倍数约分就可以了、

而无限循环小数比较麻烦

思路就是先把它乘上一个10的幂次，再把原数乘上一个10更小的幂次，再将它们相减，

我们就会惊奇地发现，后面的无限循环被减掉了

这样就只用处理前面处理过的整数部分

用它和两个10的幂次的差约分

就可以得出答案了

比如说23.（45）

现将它乘上10^2（循环节前面的小数位数加循环节的长度的幂次。。。）

得到2345.（45）

再乘上10^0（循环节前面的小数位数幂次。。。）

得到23.（45）

用上面的减去下面的

得到2322

再用10^2减去10^0

得到99

用2322和99约分

就是答案了！

Pascal 代码~~~~




```cpp
program P2399;
var
  s,s1:ansistring;
  i,j,k:longint;  a,b,kl,gl,hi,hg,lg,n,l,r,c:int64; 
function gcd(aa,bb:int64):int64;
begin
    if bb<>0 then
    gcd:=gcd(bb,aa mod bb)
    else gcd:=aa;
end;
begin
  readln(s);
  i:=1; n:=length(s);
  while s[i]<>'.' do inc(i);
  dec(i); hi:=i+2;
  s1:=copy(s,1,i);
  val(s1,a);
  inc(i,2);
  l:=pos('(',s);
  if l=0 then begin
    gl:=1;
    s1:=copy(s,hi,n-hi+1);
    val(s1,b);
    for i:=hi to n do
      gl:=gl*10;
    hg:=a*gl+b;
    kl:=gcd(hg,gl);
    writeln(hg div kl,'/',gl div kl);
  end
  else begin
    i:=l+1;
    s1:=copy(s,hi,l-hi);
    val(s1,c);
    r:=pos(')',s);
    dec(r);
    s1:=copy(s,i,r-i+1);
    val(s1,b,i);
    kl:=1; gl:=1;
    for j:=hi to l-1 do kl:=kl*10;
    for j:=l+1 to r do gl:=gl*10;
    for j:=hi to l-1 do gl:=gl*10;
    hg:=a*gl-a*kl+c*(gl div kl)-c+b;
    lg:=gl-kl;
    k:=gcd(hg,lg);
    writeln(hg div k,'/',lg div k);
  end;
end.

```

---

## 作者：DrunkXT (赞：1)

小数转分数

分两种情况讨论，有限小数和无限循环小数

**有限小数**：

小数点后几位就用不带小数点的原数除以n的几次方

如1.32=132/(10^2)

**无限循环小数:**

以1.（3）为例

设x=1.(3)

10x=13.(3)

10x-x=13.(3)-1.(3)

9x=12

x=12/9=4/3

再以0.99997(8)为例

设x=0.99997(8)

1000000x=999978.(8)

1000000x-100000x=999978.(8)-99997.(8)

900000x=899981

x=899981/900000

代码这样模拟就行了：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1005;
char a[MAXN];
int gcd(int a,int b)
{
    if(a%b==0)
        return b;
    return gcd(b,a%b);
}
int main()
{
	freopen("non hates math.in","r",stdin);
	freopen("non hates math.out","w",stdout);
	gets(a+1);
	int l=strlen(a+1);
    int f=0;
	for(int i=1;i<=l;i++)
	    if(a[i]=='(')
	    {
	    	f=1;
	    	break;
	    }
	if(f==0)
	{
		int n=0;
		int m=1;
		int t=0;
		for(int i=1;i<=l;i++)
		{
		    if(a[i]>='0'&&a[i]<='9')
		    {
		        n*=10;
		        n+=a[i]-'0';
		    }
		    if(a[i]=='.')
		        t=1;
		    if(t==1)
		        m*=10;
		}
		m/=10;
		int p=gcd(n,m);
		printf("%d/%d",n/p,m/p);
	}
	else
	{
		int m=0;
		for(int i=1;i<=l;i++)
			if(a[i]=='(')
			    break;
			else if(a[i]!='.')
			{
				m*=10;
				m+=a[i]-'0';
			}
		int n=0;
		int k=1;
		for(int i=1;i<=l;i++)
		    if(a[i]>='0'&&a[i]<='9')
		    {
		        n*=10;
		        k*=10;
		        n+=a[i]-'0';
		    }
		int b=1;
		for(int i=1;i<=l;i++)
		    if(a[i]=='(')
		        break;
		    else if(a[i]!='.')
		        b*=10;
		b/=10;
		k/=10;
		k-=b;
		n-=m;
		int p=gcd(n,k);
		printf("%d/%d",n/p,k/p);
	}
	return 0;
}
```
**~~我写的非常繁琐，大家可自行优化（就是懒）~~**

---

## 作者：骗分过样例 (赞：0)

~~明天就要期中考试了，现在还是多积德行善吧~~

[blog 观看效果更佳](https://www.luogu.com.cn/blog/215723/solution-p2399)

**分析**：

这题实际上是数学题，分小互化。就是在实现上有些困难。

------------

先来讲讲分数、小数互化的规则:

1. 整数部分不说了，最后在把它加上去。

2. 重点看小数部分：

- 1. 如果是有限小数，就是 小数部分/$10$^小数位数

- 2. 如果是无限循环小数，就是 小数部分/$99...9$（小数位数个$9$）

举几个例子：

1. $0.25=\frac{25}{100}=\frac{1}{4}$

2. $0.33...=\frac{3}{9}=\frac{1}{3}$

### 最后，千万别忘了 约分！！！

------------

下面就来分析一下到底该怎么写代码吧。

1. 先输入吧

2. 删去后面的$0$

3. 再分离整数部分，存在$s_1$

4. 接着判断是否循环，并分离小数部分，存在$s_2$

5. 然后计算分母、分子，并约分

6. 最后输出结果

7. 以```return 0```华丽结尾

------------

注意事项：

1. 因为输入时，可能出现括号，所以一定要用**字符串**进行输入。

2. 输入后，要注意判断是否有**循环节**。

3. 处理时，一定要把整数与小数部**分开**处理，不然难免会炸。

4. 老话再说一遍，一定要**约分**。

5. 对于那种$0.050000000$一样的数据，要记得删$0$，而$1.0$这种，也要**特判**输出。

6. 要再补充一种，就是$0.11(1)$这样的，要记得把前面非循环节的当作整数处理，最后再添加乘上的$10$。

------------

好了，说了挺多了，大家应该也把这题理解了一些了。下面就是代码,附有详细解析，大家如果没看懂可以在下面再看看：

```cpp
#include<iostream>
#include<cmath>
using namespace std;

long long k1; //对于那些类似于0.111(1)类的判别变量 
long long k; //对于循环、非循环的判别变量 
long long s1,s2; //分别用来存储整数、小数部分 
string a; //输入字符串 
long long fm,fz; //分母、分子 
long long extra=1; //需要再分母上额外添加的变量 
long long stop; //在分离小数时，对小数点后的0是否添加的控制变量 

long long dig(long long x){ //求一个数的位数，对于后面也是有用的 
	long long cnt=0;
	while(x){
		cnt++;
		x/=10;
	}
	return cnt;
}

long long gys(long long a,long long b){ //辗转相除法求最大公约数 
	if(a%b==0){
		return b;
	}
	return gys(b,a%b);
}

int main(){
	long long pos; //标记小数点的位置 
	long long pos2; //再应对0.111(1)中标记小数点的 
	cin>>a; //输入 
	while(a[a.size()-1]=='0'){ //记得删去0 
		a.erase(a.end()-1); //记得不能直接删end，否则会运行错误 
	}
	for(long long i=0;i<a.size();i++){
		if(a[i]=='.'){
			pos2=i;
			break;
		}
	}
	if(a[pos2+1]!='('&&a.find("(")!=string::npos){ //对于0.111(1)的判断 
		k1=1;
		while(a[pos2+1]!='('){ //移动小数点 
			char c1=a[pos2];
			char c2=a[pos2+1];
			a[pos2]=c2;
			a[pos2+1]=c1;
			pos2++;
			extra*=10;
		}
	}
	for(long long i=0;i<a.size();i++){ //分离整数位 
		if(a[i]!='.'){
			s1*=10;
			s1+=(a[i]-'0');
		}
		else{
			pos=i;
			break;
		}
	}
	if(a[pos+1]=='('){ //对于循环小数的判定 
		k=1;
		for(long long i=pos+2;i<a.size()-1;i++){
			if(a[i]=='0'&&!stop){ //对于前导零的处理 
				extra*=10;
			}
			if(a[i]!='0'){
				stop=1;
			}
			s2*=10;
			s2+=(a[i]-'0'); //分离小数位 
		}
	}
	else{
		k=0;
		for(long long i=pos+1;i<a.size();i++){
			if(a[i]=='0'&&!stop){
				extra*=10;
			}
			if(a[i]!='0'){
				stop=1;
			}
			s2*=10;
			s2+=(a[i]-'0');
		}
	}
	if(s2==0){ //对于1.0类型的特判 
		cout<<s1<<"/"<<1<<endl;
		return 0;
	}
	if(k1==1){ //对于0.111(1)类型的特判 
		fm=(pow(10,dig(s2))-1)*extra;
		fz=s2+s1*(pow(10,dig(s2))-1);
		long long ys=gys(fm,fz);
		fm/=ys,fz/=ys;
		cout<<fz<<"/"<<fm<<endl;
		return 0;
	}
	if(k==1){ //循环小数 
		fm=(pow(10,dig(s2))-1)*extra;
		fz=s2+s1*fm;
		long long ys=gys(fm,fz);
		fm/=ys,fz/=ys;
	}
	else{ //普通小数 
		fm=pow(10,dig(s2))*extra;
		fz=s2+s1*fm;
		long long ys=gys(fm,fz); //记得约分！！！ 
		fm/=ys,fz/=ys;
	}
	cout<<fz<<"/"<<fm; //输出 
	cout<<endl;
	return 0; //完美地结尾！！！ 
}

```

---

## 作者：Mine_King (赞：0)

先安利下[我的博客](https://www.luogu.com.cn/blog/195331/)~  
若题解界面的$\LaTeX$炸了，请点击“在 Ta 的博客查看”。

这题模拟。  
首先讲一下如何小数化分数：  
**注：以下所说的小数部分、循环节之类的皆指化成整数后（例如：$0.1$化成整数后就是$1$）**

**有限小数：** $\frac{\text{小数部分}}{10^{\text{小数位数}}}$  
**纯循环小数：** $\frac{\text{循环节}}{\text{循环节位数个9}}$  
**混循环小数：** $\frac{\text{小数部分-不循环部分}}{\text{循环节位数个9，后面跟不循环部分位数个0}}$  
至于读入的整数部分$n$的处理，直接在分子里加上$n\times\text{分母}$就好了。

接下来是具体实现。  
对于整数部分，我们直接用`int`读入。而对于小数部分，由于会出现`'('`和`')'`，所以用`string`读入。  
读入后怎么把他转换成整数呢？简单只要这么写：
```cpp
//读入的字符串用s存储
int k=0;
for(int i=0;i<s.length();i++)
	k=(k*10)+(s[i]-'0');
```
像这样一位位加上去即可。  
那么在具体操作中只要注意处理`'('`和`')'`即可。  
注意约分哦！  
约分其实就是分子分母同时除以$gcd(\text{分子},\text{分母})$啦！

**code：**
```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
int n,k,m;//n存储整数部分，k存储分子，m存储分母
string s;//s存储小数点和小数部分
int xh()//判断是有限小数还是纯循环小数还是混循环小数
{
	if(s[1]=='(') return 2;//一开头就是(就是纯循环小数
	for(int i=2;i<(int)s.length();i++)
		if(s[i]=='(') return 3;//其他的有出现(就是混循环小数
	return 1;//否则就是有限小数
}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}//求gcd
int main()
{
	scanf("%d",&n);
	cin>>s;
	int opt=xh();
	if(opt==1)//有限小数
	{
		m=1;
		for(int i=1;i<(int)s.length();i++)
		{
			m*=10;//更新分母
			k=k*10+(s[i]-'0');//记录分子
		}
		n=n*(m/gcd(k,m));
		printf("%d/%d",n+k/gcd(k,m),m/gcd(k,m));
	}
	else if(opt==2)//纯循环小数
	{
		for(int i=2;i<(int)s.length()-1;i++)
		{
			m=m*10+9;//更新分母
			k=k*10+(s[i]-'0');//更新分子
		}
		n=n*(m/gcd(k,m));
		printf("%d/%d",n+k/gcd(k,m),m/gcd(k,m));
	}
	else if(opt==3)
	{
		int no=0,i;//no记录不循环部分
		for(i=1;i<(int)s.length();i++)//记录不循环部分
			if(s[i]!='(')
			{
				no=no*10+(s[i]-'0');
				k=k*10+(s[i]-'0');//同时更新整个小数部分
			}
			else break;
		int j=i-1;//记录不循环部分的长度
		for(i=i+1;i<(int)s.length()-1;i++)
		{
			k=k*10+(s[i]-'0');//更新分子
			m=m*10+9;//更新分母
		}
		for(i=1;i<=j;i++) m=m*10;//在后面添0
		k-=no;//更新分子
		n=n*(m/gcd(k,m));
		printf("%d/%d",n+k/gcd(k,m),m/gcd(k,m));
	}
	return 0;
}
```

---

## 作者：Laser_Crystal (赞：0)

## 这题其实不难，只要注意细节即可

公式：

有限小数（记小数位数为n）：小数整个儿做分子，分母是10^n

纯循环小数（记小数位数为n）：小数整个儿做分子，分母是999……9（共有n个9）

混循环小数（记循环节位数为n1，非循环节位数为n2）：分子等于非循环节的数和循环节的数组合起来，再减去非循环节的数，分母是99……900……0（n1个9，n2个0）

例如：

（1） 0.12345=12345/100000

（2） 0.（6）=6/9=2/3

（3） 0.1（6）=（16-1）/90=1/6

边上代码边讲：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long n,long long m)
{
	long long r;
	do
	{
		r=n%m;
		n=m;
		m=r;
	}while(m!=0);
	return n;
}//最大公因数，用来约分
int main()
{
	char s[5000];
	bool p=true;
	int t=0;
	scanf("%s",s);//字符串读入
	int l=0;
	long long integer=0;
	for(;s[l]!='.';l++)
		integer=integer*10+s[l]-48;//取出整数部分
	for(int i=0;i<strlen(s);i++) 
	if(s[i]=='(')//找到循环节
	{
		p=false;//是否为非循环小数
		t=i;//标记
		break;
	}
	if(s[l+1]=='(')//如果是纯循环小数
	{
		int len=strlen(s);
		long long a=0,b=0;
		l+=2;
		for(int i=l;i<len-1;i++) 
		{
			b=b*10+9;
			a=a*10+s[i]-48;
		}//公式计算
		a+=integer*b;
		cout<<a/gcd(a,b)<<"/"<<b/gcd(a,b);
	}
	else if(s[l+1]>='0'&&s[l+1]<='9'&&p)//如果是有限小数
	{
		int len=strlen(s);
		long long a=0,b=1;
		l++;
		for(int i=l;i<len;i++) 
		{
			b*=10;
			a=a*10+s[i]-48;
		}//公式计算
		a+=integer*b;
		cout<<a/gcd(a,b)<<"/"<<b/gcd(a,b);
	}
	else//如果是混循环小数
	{
		int len=strlen(s);
		long long a=0,b=0,c=0;
		l++;
		for(int i=l;i<len;i++) 
		if(s[i]>='0'&&s[i]<='9')
			a=a*10+s[i]-48;
		for(int i=l;i<t;i++)
		if(s[i]>='0'&&s[i]<='9')
			c=c*10+s[i]-48;
		for(int i=t+1;i<len-1;i++)
		b=b*10+9;
		for(int i=l;i<t;i++) b*=10;
		a=a-c;//公式计算（有点ma复杂）
		a+=integer*b;
		cout<<a/gcd(a,b)<<"/"<<b/gcd(a,b);
	}
	return 0;
}
```
各位886~

---

