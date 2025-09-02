# A/B Problem II

## 题目背景

为了让大家紧张的心情放松一下，这一题题是一道非常简单的题目。


## 题目描述

给出正整数 $N$ 和 $M$，请你计算 $N \div M$（$N / M$ 的下取整）。

## 说明/提示

- 对于 $60 \%$ 的数据：$ N,M \le 750!$，答案 $ \le 7!$。
- 对于 $100 \%$ 的数据：$N,M \le 6250!$，答案 $ \le 13!$。

请注意：上面的两句话并不是感叹句，而是陈述句。标点符号使用没有错误。

## 样例 #1

### 输入

```
1000 
333
```

### 输出

```
3
```

# 题解

## 作者：Adove (赞：100)

我又回来啦，上回的代码过于冗长而且效率不太好，这次代码简洁了很多，而且倍增优化让代码时空效率优秀了不少。

高精度压八位，加减乘除板子都在这里，而且允许读入负数，允许修改压位位数siz

其实相对来说重点在压位不在倍增吧qwq

去年发过一篇题解，但去年那篇太过冗长，于是今年又写了一遍qwq

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1e5;
const int siz=8;
const long long MOD=1e8;//1e siz压位需要取的模数

char ch1[MAXN],ch2[MAXN];
bool f1,f2,f;
long long n;
long long a[MAXN>>2],b[MAXN>>2],s[MAXN>>2];
long long cp[MAXN>>2],lt[MAXN>>2],wsd[MAXN>>2];

void write(long long num[]);//输出函数
void clear(long long num[]);//重置函数
void ry(long long num[]);//>>二进制右移
void ly(long long num[]);//<<二进制左移
void cpy(long long num1[],long long num2[]);//复制函数
int cmp(long long num1[],long long num2[]);//比较函数
void pls(long long a[],long long b[]);//plus加法运算
void mnu(long long a[],long long b[]);//minus减法运算
void mul(long long a[],long long b[]);//multiply乘法运算
void div(long long a[],long long b[]);//divided除法运算

void write(long long num[])
{
	if(f) putchar('-'),f=0;
	printf("%lld",num[num[0]]);
	for(int i=num[0]-1;i;--i) printf("%08lld",num[i]);
	puts("");
}

void clear(long long num[])
{
	for(int i=num[0];i;--i) num[i]=0;
	num[0]=1;
}

void ry(long long num[])
{
	for(int i=num[0];i;--i){
		if((num[i]&1)&&i>1) num[i-1]+=MOD;
		num[i]>>=1;
	}if(!num[num[0]]&&num[0]>1) --num[0];
}

void ly(long long num[])
{
	++num[0];
	for(int i=1;i<=num[0];++i){
		num[i]<<=1;
		if(num[i-1]>=MOD) num[i-1]-=MOD,++num[i];
	}if(!num[num[0]]&&num[0]>1) --num[0];
	return;
}

void cpy(long long num1[],long long num2[])
{
	for(int i=num1[0];i>num2[0];--i) num1[i]=0;
	for(int i=0;i<=num2[0];++i) num1[i]=num2[i];
}

int cmp(long long num1[],long long num2[])
{
	if(num1[0]>num2[0]) return 1;
	if(num1[0]<num2[0]) return -1;
	for(int i=num1[0];i;--i){
		if(num1[i]>num2[i]) return 1;
		if(num1[i]<num2[i]) return -1;
	}return 0;
}

void init()
{
	scanf("%s%s",ch1,ch2);
	if(ch1[0]=='-') ch1[0]='0',f1=1;
	if(ch2[0]=='-') ch2[0]='0',f2=1;//对符号的处理
	int l1=strlen(ch1),l2=strlen(ch2);
	for(int i=l1-1;i>=0;i-=siz){
		long long pw=1;++a[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			a[a[0]]+=(ch1[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}for(int i=l2-1;i>=0;i-=siz){
		long long pw=1;++b[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			b[b[0]]+=(ch2[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}return;
}

void pls(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,mnu(b,a),f1^=1;
		if(f2) f2^=1,mnu(a,b),f2^=1;//加负数等效于减正数
		return;
	}if(f1&f2){
		f1=f2=0,f^=1,pls(a,b);
		f1=f2=1;return;
	}clear(s);s[0]=max(a[0],b[0])+1;
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]+b[i];
		if(s[i]>=MOD) s[i]-=MOD,++s[i+1];
	}if(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mnu(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,f^=1,pls(a,b),f1^=1;
		if(f2) f2^=1,pls(a,b),f2^=1;//减负数等效于加正数
		return;
	}if(f1&f2){
		f1=f2=0,mnu(b,a);
		f1=f2=1;return;
	}if(cmp(a,b)==-1){
		f^=1;mnu(b,a);return;
	}clear(s);s[0]=max(a[0],b[0]);
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]-b[i];
		if(s[i]<0) s[i]+=MOD,--s[i+1];
	}while(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mul(long long a[],long long b[])//模拟竖式乘法
{
	if(f1^f2) f^=1;
	clear(s);s[0]=a[0]+b[0];
	for(int i=1;i<=a[0];++i){
		for(int j=1;j<=b[0];++j){
			s[i+j-1]+=a[i]*b[j];
			if(s[i+j-1]>=MOD) s[i+j]+=s[i+j-1]/MOD,s[i+j-1]%=MOD;
		}
	}if(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void div(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,f^=1,div(a,b),f1^=1;
		if(f2) f2^=1,f^=1,div(a,b),f2^=1;
		return;
	}clear(s);
	clear(cp),cp[1]=1;clear(lt);
	while(cmp(a,b)!=-1) ly(b),ly(cp);//这里试探商的二进制最高位
	while(cp[0]>1||cp[1]){
		if(cmp(a,b)!=-1){
			mnu(a,b),cpy(a,s);
			pls(lt,cp),cpy(lt,s);//倍增减法，算法主体
		}ry(b),ry(cp);
	}cpy(s,lt),cpy(lt,a);//s为商，lt为余数
	return;
}

int main()
{
	init();
	clear(s);
//	pls(a,b);write(s);
//	mnu(a,b);write(s);
//	mul(a,b);write(s);
	div(a,b);write(s);//write(lt);
	return 0;
}
```
然后是去年那篇，自己写了十进制左移右移
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int mec=1e4;
int c[14001],num,d[14001],s[18002],lt[14001],e[14001],f[14001]={1,1};
bool tc,td;
char a[150001],b[150001];
void sum(int c[],int d[]);
void dec(int c[],int d[]);
void mul(int c[],int d[]);
void div(int c[],int d[]);
int tpow(int n)
{
    int m=10;
    while(--n)
        m*=10;
    return m;
}
void ly(int c[],int n)
{
    int m=n%4;
    n/=4;
    c[0]+=n;
    for(int i=c[0];i>n;--i)
        c[i]=c[i-n];
    for(int i=n;i;--i)
        c[i]=0;
    if(m)
    {
        m=tpow(m);
        for(int i=n+1;i<=c[0];++i)
        {
            c[i]*=m;
            if(c[i-1]>=mec)
            {
                c[i]+=c[i-1]/mec;
                c[i-1]%=mec;
            }
        }
    }
    if(c[c[0]]>=mec)
    {
        c[++c[0]]=c[c[0]-1]/mec;
        c[c[0]-1]%=mec;
    }
    while(c[c[0]]==0&&c[0]) --c[0];
}
void ry(int c[],int n)
{
    int m=n%4;
    n/=4;
    c[0]-=n;
    for(int i=1;i<=c[0];++i)
        c[i]=c[i+n];
    for(int i=c[0]+1;i<=c[0]+n;++i)
        c[i]=0;
    if(m)
    {
        m=tpow(m);
        for(int i=1;i<=c[0];++i)
        {
            c[i]/=m;
            if(c[i]<=mec)
                c[i]+=c[i+1]%m*mec/m;
        }
    }
    if(c[c[0]]>=mec)
    {
        c[++c[0]]=c[c[0]-1]/mec;
        c[c[0]-1]%=mec;
    }
    while(c[c[0]]==0&&c[0]) --c[0];
}
int cmp(int c[],int d[])
{
    if(c[0]<d[0]) return -1;
    else if(c[0]>d[0]) return 1;
    else
    {
        for(int i=c[0];i;--i)
            if(c[i]>d[i]) return 1;
            else if(c[i]<d[i]) return -1;
    }
    return 0;
}
void cpy(int c[],int d[])
{
    for(int i=c[0];i>d[0];--i)
        c[i]=0;
    for(int i=0;i<=d[0];++i)
        c[i]=d[i];
}
void cler(int s[])
{
    for(int i=s[0];i;--i) s[i]=0;
    s[0]=1;
}
void check(int c[])
{
    printf("%d",c[c[0]]);
    for(int i=c[0]-1;i;--i)
        printf("%04d",c[i]);
    puts("");
}
void init()
{
    scanf("%s%s",a,b);
    if(a[0]=='-') tc=1;
    if(b[0]=='-') td=1;
    for(int i=strlen(a)-1;i>=0;--i)
    {
        if(num%4==0&&a[i]!='-')
        {
            c[++c[0]]=a[i]-'0';
            int pw=10;
            for(int j=1;j<4&&i-j>=0&&a[i-j]!='-';++j)
            {
                c[c[0]]+=(a[i-j]-'0')*pw;
                pw*=10;
            }
        }
        ++num;
    }
    num=0;
    for(int i=strlen(b)-1;i>=0;--i)
    {
        if(num%4==0&&b[i]!='-')
        {
            d[++d[0]]=b[i]-'0';
            int pw=10;
            for(int j=1;j<4&&i-j>=0&&b[i-j]!='-';++j)
            {
                d[d[0]]+=(b[i-j]-'0')*pw;
                pw*=10;
            }
        }
        ++num;
    }
}
void write(int s[])
{
    printf("%d",s[s[0]]);
    for(int i=s[0]-1;i;--i)
        printf("%04d",s[i]);
    puts("");
}
void sum(int c[],int d[])
{
    if(tc&&td)
    {
        putchar('-');
        tc=td=0;
    }
    else if(tc)
    {
        tc=0;
        dec(d,c);
        return;
    }
    else if(td)
    {
        td=0;
        dec(c,d);
        return;
    }
    cler(s);
    s[0]=max(c[0],d[0]);
    for(int i=1;i<=s[0];++i)
    {
        s[i]=c[i]+d[i];
        if(i>1&&s[i-1]>=mec)
        {
            s[i]+=s[i-1]/mec;
            s[i-1]%=mec;
        }
    }
    if(s[s[0]]>=mec)
    {
        s[++s[0]]=s[s[0]-1]/mec;
        s[s[0]-1]%=mec;
    }
}
void dec(int c[],int d[])
{
    if(tc&&td)
    {
        td=0;
        dec(d,c);
        return;
    }
    else if(td)
    {
        td=0;
        sum(c,d);
        return;
    }
    else if(tc)
    {
        putchar('-');
        tc=0;
        sum(c,d);
        return;
    }
    cler(s);
    s[0]=max(c[0],d[0]);
    if(cmp(c,d)<0)
    {
        swap(c,d);
        putchar('-');
    }
    for(int i=1;i<=s[0];++i)
    {
        s[i]+=c[i]-d[i];
        if(s[i]<0)
        {
            s[i]+=mec;
            --s[i+1];
        }
    }
    while(s[s[0]]==0&&s[0]>1)
        --s[0];
}
void mul(int c[],int d[])
{
    if(tc^td)
    {
        putchar('-');
        tc=td=0;
    }
    cler(s);
    s[0]=c[0]+d[0]-1;;
    for(int i=1;i<=c[0];++i)
    {
        for(int j=1;j<=d[0];++j)
        {
            s[i+j-1]+=c[i]*d[j];
            if(i+j-1>1&&s[i+j-2]>=mec)
            {
                s[i+j-1]+=s[i+j-2]/mec;
                s[i+j-2]%=mec;
            }
        }
        if(s[i+d[0]-1]>=mec)
        {
            s[i+d[0]]=s[i+d[0]-1]/mec;
            s[i+d[0]-1]%=mec;
        }
    }
    if(s[s[0]+1]) ++s[0];
}
void div(int c[],int d[])
{
    if(tc^td)
    {
        putchar('-');
        tc=td=0;
    }
    cpy(e,d);
    int la=strlen(a)-tc,lb=strlen(b)-td;
    if(strlen(a)>strlen(b))
    {
        ly(e,strlen(a)-strlen(b));
        ly(f,strlen(a)-strlen(b));
    }
    while(cmp(c,d)>=0)
    {
        while(cmp(c,e)>=0)
        {
            dec(c,e);
            cpy(c,s);
            sum(lt,f);
            cpy(lt,s);
        }
        ry(e,1);
        ry(f,1);
    }
    if(lt[0]==0) lt[0]=1;
    write(lt);
//	write(c);
}
int main()
{
    init();
    div(c,d);
    return 0;
}
```

---

## 作者：24680esz (赞：42)

裸的高精除高精，直接套版子

```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
string a1,b1;
int a[100001],b[100001],c[100001],t[100001];
int compare(int aa[],int bb[])//判断数组大小
{
    if (aa[0]>bb[0]) return 1;
    if (aa[0]<bb[0]) return -1;
    for (int i=aa[0];i>0;i--)
    {
        if (aa[i]>bb[i]) return 1;
        if (aa[i]<bb[i]) return -1;
    }
    return 0;
}
void numcpy(int aa[],int bb[],int l)//数组复制
{
    for (int i=1;i<=aa[0];i++) bb[i+l-1]=aa[i];
    bb[0]=aa[0]+l-1;
}
int main()
{
    cin>>a1>>b1;a[0]=a1.size();b[0]=b1.size();c[0]=a[0]-b[0]+1;
    for (int i=1;i<=a[0];i++) a[i]=a1[a[0]-i]-48;
    for (int i=1;i<=b[0];i++) b[i]=b1[b[0]-i]-48;
    for (int i=c[0];i>0;i--)
    {
        memset(t,0,sizeof(t));
        numcpy(b,t,i);
        while (compare(a,t)>=0)
        {
            c[i]++;
            if (!compare(a,t)) {a[0]=0;continue;}
            for (int i=1;i<=a[0];i++)
            {
                if (a[i]<t[i]) a[i+1]--,a[i]+=10;
                a[i]-=t[i];
            }
            while (a[0]>0&&!a[a[0]]) a[0]--;
        }
    }
    while (c[0]>0&&!c[c[0]]) c[0]--;
    if (!c[0]) cout<<0<<endl;
      else for (int i=c[0];i>0;i--) cout<<c[i];
    return 0;
}
```

---

## 作者：ji20101333 (赞：26)

~~为什么用python作这么简单的一道题C++就这么麻烦……~~

这道题事实上还是比较简单的，只要一发高精度就能解决的，不过对位什么的我都没有考虑进去，就是靠很简单的一些循环而已，时间、空间限制也没问题。

下面是代码，有注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],b[100001],ans[100001],la,lb,lans,i,j,k;
/*a：被除数；b：除数；ans：商
  la：被除数长度；lb：除数长度；lans：商长度
  i，j，k：循环用*/
string s1,s2;
int main()
{
	cin>>s1>>s2;//读入
	la=s1.size();
	lb=s2.size();
	for(i=1;i<=la;i++)
		a[i]=s1[i-1]-'0';//将字符串转换成数组
	for(i=1;i<=lb;i++)
		b[i]=s2[i-1]-'0';//将字符串转换成数组
	if(la<lb)//如果被除数比除数的长度短，直接输出0
	{
		cout<<0;
		return 0;
	}
	if(la==lb)//如果长度一样，若被除数较小，同样输出0
		for(i=1;i<=la;i++)
			if(a[i]<b[i])
			{
				cout<<0;
				return 0;
			}
			else
				if(a[i]>b[i])
					break;
	lans=la-lb+1;
    //我的做法是把除法转换成减法，不停地减，每减一次，对应位置的答案加一
	for(i=1;i<=lans;i++)//开始除法
	{
		while(1)
		{
			for(j=i,k=1;j<=lb+i-1,k<=lb;j++,k++)
				if(a[j]>b[k])//如果被除数的某位置先比除数大了，则可以做减法，跳出循环
				{
					j=lb+1;
					break;
				}
				else
					if(a[j]<b[k])//如果被除数的某位置先比除数小了，则不可做减法，跳出循环
						break;
                //若两数相同，则继续循环判断
			if(j>lb)//如果可以做减法
			{
				for(j=lb+i-1,k=lb;j>=i,k>=1;j--,k--)
					if(a[j]-b[k]>=0)
						a[j]-=b[k];//减法实现
					else
						a[j]+=10,a[j-1]--,a[j]-=b[k];//如果一个位置上的数小于零，则退位（小学数学内容）
				ans[i]++;
			}
			else//如果不能做减法
			{
				a[i+1]+=a[i]*10;//将最前一位的所有数全部退到下一位置的数上
				a[i]=0;//归零（有木有都无所谓）
				break;//跳出减法循环
			}
		}
	}
	for(i=1;i<=lans;i++)//输出
		if(i==1&&ans[i]==0);//当第一位是零时，不输出
		else
			cout<<ans[i];
	return 0;//华丽丽的结束
}
```
蒟蒻题解求通过

下面贴一段高精度模板：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],b[100001],c[100001],ans[100001],la,lb,lans,i,j,k,flag;
string s1,s2;
char ch;
int main()
{
	cin>>s1>>s2;
	la=s1.size();
	lb=s2.size();
	for(i=1;i<=la;i++)
		a[i]=s1[i-1]-'0';
	for(i=1;i<=lb;i++)
		b[i]=s2[i-1]-'0';
	memset(ans,0,sizeof(ans));//加
	if(la>=lb)
	{
		for(i=2;i<=la+1;i++)
			ans[i]+=a[i-1];
		for(i=la+1,j=lb;i>=la-lb+2,j>=1;i--,j--)
			ans[i]+=b[j];
	}
	else
	{
		for(i=2;i<=lb+1;i++)
			ans[i]+=b[i-1];
		for(i=lb+1,j=la;i>=lb-la+2,j>=1;i--,j--)
			ans[i]+=a[j];
	}
	for(i=max(la,lb)+1;i>=2;i--)
		if(ans[i]>=10)
			ans[i]-=10,ans[i-1]++;
	cout<<"sum=";
	for(i=1;i<=max(la,lb)+1;i++)
		if(i==1&&ans[i]==0);
		else
			cout<<ans[i];
	cout<<endl;
	memset(ans,0,sizeof(ans));//减
	cout<<"difference=";
	if(la<lb)
	{
		for(i=1;i<=lb;i++)
			ans[i]=b[i];
		for(i=lb,j=la;i>=lb-la+1,j>=1;i--,j--)
			ans[i]-=a[j];
		for(i=lb;i>=1;i--)
			if(ans[i]<0)
				ans[i]+=10,ans[i-1]--;
		cout<<'-';
	}
	else
		if(la==lb)
		{
			for(i=1;i<=la;i++)
				if(a[i]>b[i])
					i=la;
				else
					if(a[i]<b[i])
						break;
			if(i>la)
			{
				for(i=1;i<=la;i++)
					ans[i]=a[i];
				for(i=1;i<=la;i++)
					ans[i]-=b[i];
			}
			else
			{
				for(i=1;i<=la;i++)
					ans[i]=b[i];
				for(i=1;i<=la;i++)
					ans[i]-=a[i];
				cout<<'-';
			}
			for(i=la;i>=1;i--)
				if(ans[i]<0)
					ans[i]+=10,ans[i-1]--;
		}
		else
		{
			for(i=1;i<=la;i++)
				ans[i]=a[i];
			for(i=la,j=lb;i>=la-lb+1,j>=1;i--,j--)
				ans[i]-=b[j];
			for(i=la;i>=1;i--)
				if(ans[i]<0)
					ans[i]+=10,ans[i-1]--;
		}
	for(i=1;i<=max(la,lb);i++)
		if(ans[i]||flag)
			cout<<ans[i],flag=1;
	cout<<endl;
	cout<<"product=";
	flag=0;
	memset(ans,0,sizeof(ans));//乘
	for(i=la;i>=1;i--)
	{
		memset(c,0,sizeof(c));
		for(j=1;j<=lb;j++)
			c[j]=a[i]*b[j];
		for(j=i+lb+1,k=lb;j>=i+1,k>=1;j--,k--)
			ans[j]+=c[k];
	}
	for(i=la+lb+1;i>=1;i--)
		if(ans[i]>=10)
			ans[i-1]+=(ans[i]/10)*10,ans[i]=ans[i]%10;
	for(i=1;i<=la+lb+1;i++)
		if(ans[i]||flag)
			cout<<ans[i],flag=1;
	cout<<endl;
	memset(ans,0,sizeof(ans));//除
		ans[i]=0;
	cout<<"quotient=";
	if(la<lb)
	{
		cout<<0;
		return 0;
	}
	if(la==lb)
		for(i=1;i<=la;i++)
			if(a[i]<b[i])
			{
				cout<<0;
				return 0;
			}
			else
				if(a[i]>b[i])
					break;
	lans=la-lb+1;
	for(i=1;i<=lans;i++)
	{
		while(1)
		{
			for(j=i,k=1;j<=lb+i-1,k<=lb;j++,k++)
				if(a[j]>b[k])
				{
					j=lb+1;
					break;
				}
				else
					if(a[j]<b[k])
						break;
			if(j>lb)
			{
				for(j=lb+i-1,k=lb;j>=i,k>=1;j--,k--)
					if(a[j]-b[k]>=0)
						a[j]-=b[k];
					else
						a[j]+=10,a[j-1]--,a[j]-=b[k];
				ans[i]++;
			}
			else
			{
				a[i+1]+=a[i]*10;
				a[i]=0;
				break;
			}
		}
	}
	for(i=1;i<=lans;i++)
		if(i==1&&ans[i]==0);
		else
			cout<<ans[i];
	cout<<endl<<"计算结束！";
	return 0;
}
```
P.S.：最多两数相差40位左右（不然会卡掉）

致管理者：看在我这么好心的份上，就通过一下，谢谢！！！

---

## 作者：Ireliaღ (赞：16)

**在大家都用Python水高精的时候，如果你想来点不一样的，那么ruby是一个很好的选择**  

### 关于ruby稍微说几句  

ruby也是一种解释型语言，也就是不用编译就能运行，甚至可以写一行代码运行一行代码（是不是和Python很像？）。并且，最重要的，它_**自!带!高!精!**_  
   
所以，对于这道高精的$a/b$，我们的ruby语言也可以用一行搞定  

```rb
print gets.to_i / gets.to_i
```  

### 简单解释一下这一行代码的含义

#### print

简单的输出语句，大家都能看出来  

#### gets

和C相似，读一行，直接返回字符串  

#### .to_i  

这是ruby的类型转换，i是int的缩写，所以这个.to_i和Python的int()相似  
### 所以如果不想压到一行，正常写法是这样的

```rb
a = gets
b = gets
a = a.to_i
b = b.to_i
print a / b
```

---

## 作者：yejichen (赞：15)

高精度除法套路之：补“0”法

此法不同于一般的模拟（竖式法），除法操作步数模仿手工除法，而是利用减法操作实现的。

其基本思想是反复做除法，看从被除数里面最多能减去多少个除数，商就是多少。

逐个减显然太慢，要判断一次最多能减少多少个整的10的n次方。

以7546除23为例。

先减去23的100倍，就是2300，可以减3次，余下646。此时商就是300；

然后646减去23的10倍，就是230，可以减2次，余下186。此时商就是320；

然后186减去23，可以减8次，此时商就是328。

从这里不难看出，所谓补“0”只不过是减得快一点罢了，其本质依旧是高精度乘法的逆运算。

代码见下：

```cpp
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<cstring>
using namespace std;
string itos(int x) //将数据转化成字符串，stringstream神器ovo，方便下面按照字符串存起来，好比较
{
    stringstream s;
    s<<x;
    return s.str();
}
bool greater_dif(string x,string y) //字符串大于比较：优先级为符号>位数>大小关系（nc的c++比较字符串是一位一位比ASCII啊......）
{
    if(x[0]!='-'&&y[0]=='-') return true; //先比符号
    if(x[0]=='-'&&y[0]!='-') return false;
    if(x.size()>y.size() || (x.size()==y.size() && x>y)) return true; // 再比位数和大小
    return false; //其它情况直接false
} 
bool smaller_dif(string x,string y) //字符串小于比较，效果同上
{
    if(x[0]=='-'&&y[0]!='-') return true;
    if(x[0]!='-'&&y[0]=='-') return false;
    if(x.size()<y.size() || (x.size()==y.size() && x<y)) return true;
    return false; 
} 
string highmin(string x,string y) //高精度减法运算
{
    int w=0;
    int z=max(x.size(),y.size());
    int tp[z+5];
    memset(tp,0,sizeof(tp)); //数组清零
    string result="";
    if(smaller_dif(x,y)) //支持小数减大数的操作，采取绝对值法，即小数减大数等于大数减小数的绝对值
    {
        swap(x,y);
        result+="-"; 
    }
    reverse(x.begin(),x.end()); //倒序存储
    reverse(y.begin(),y.end());
    for(int i=0;i<z+5;i++) //然后就是直接减
    {
        int p=int(x[i]-'0');
        int q=int(y[i]-'0');
        if(i>=x.size()) p=0;
        if(i>=y.size()) q=0;
        tp[i]=p-q;
    }
    for(int i=0;i<=z;i++) //退位，由于是倒序的所以应当倒着退位
    {
        if(tp[i]<0)
        {
            tp[i+1]-=1; //倒着退位
            tp[i]+=10;
        }
        if(tp[i]!=0) w=i; //记录最靠前的非零位置，方便输出
    }
    for(int i=w;i>=0;i--)
    {
        string z1=itos(tp[i]);
        result+=z1;
    }
    return result;
}
string divide(string x,string y) //高精度除法模块
{
    string result_d=""; 
    int q=max(x.size(),y.size());
    int tmp[q+5];
    memset(tmp,0,sizeof(tmp)); //仍然是先数组存
    int ans=0;
    int w=0;
    string y_l=y; //便于y初始化
    while(greater_dif(x,"0")) //这块参考上面思路
    {
        while(greater_dif(x,y+"0") || x==y+"0") //预先判断防止减完小于0了还要恢复过来
        {
            y+="0"; //补“0”
            ans++;
        }
        tmp[ans]++;
        if(ans>w) w=ans;
        ans=0; //ans初始化
        x=highmin(x,y);
        if(x[0]=='-') 
        {
            tmp[ans]-=1; //防止减多了
            break;
        }
        y=y_l; //y初始化
    }
    for(int i=w;i>=0;i--)
    {
        string z_d=itos(tmp[i]);
        result_d+=z_d;	
    } 
    return result_d;
}
int main()
{
    string a,b;
    cin>>a>>b;
    cout<<divide(a,b)<<endl; //输出除法结果
    return 0;
}
```


---

## 作者：JimmyF (赞：9)

   
看见大佬们打了这么长的程序，本蒟蒻在次大呼一声—— 
## python真的是好语言！ 

### 三行无敌代码：

    a=int(input())  //定义并输入a
    b=int(input())  //定义并输入b
    print(a/b)     //高静输出a/b
    
WA了嘛......不要怪我呦~~逃

---

## 作者：constructor (赞：9)

看了看没人交Java，我提交一波吧（虽然被py吊打但是至少吊打C++）
```java
import java.math.*;

import java.io.*;

import java.util.*;

class Main

{
  public static void main(String[] args)
  {
      Scanner input=new Scanner(System.in);//输入器构造
      BigInteger a=new BigInteger("0");//初始化高精整数对象a，注意高精整数对象不可以直接用int构造。
      BigInteger b=new BigInteger("0");//初始化高精整数对象b
      a=input.nextBigInteger();//输出a
      b=input.nextBigInteger();//输入b
      System.out.println(a.divide(b));//输出方法
  }
};
```

---

## 作者：Dog_Two (赞：7)

看到这一道高精，我面露喜色地打开了我 ~~抄~~ 的高精度模板——

然后发现这一套模板里面并没有重载除法号QwQ

再后来我就想到了我们正高级数学教师的一句话：

对于各种意义上的运算，乘就是除，加就是减！~~当然在高中阶段还是很少有例外的~~

所以这一题我们可以**枚举答案**！

但是显然，朴素的高精度乘法和0...2e10的数据怕是要用神威太湖之光来算\_(:зゝ∠)\_


所以我们可以**二分商**，再反着乘回去验证。


朴素的高精度乘法的复杂度是 O(n^2)，在这一道n可以高达2e4的题目中还是比较可怕的，所以我们要尽可能减少冗余计算！


- 在和标准答案比较前，记录商和被除数的乘积（每次比较可以减少一次乘法）

- 当枚举的商和被除数的乘积达到**临界**的时候（即ans\*N<M&&ans\*N+N>M)跳出循环（可以避免不必要的区间收缩）

- l和r一定要用long long存，否则会因为奇妙的溢出而超时+WA若干个点，导致只有60分。


      
      
    
      
      
        
        
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 20000+10;  
    struct bign{  
      int len, s[maxn];  
      bign() {  
        memset(s, 0, sizeof(s));  
        len = 1;  
      }  
      bign(int num) {  
        *this = num;  
      }  
      bign(const char* num) {  
        *this = num;  
      }  
      bign operator = (int num) {  
        char s[maxn];  
        sprintf(s, "%d", num);  
        *this = s;  
        return *this;  
      }   
      string str() const {  
        string res = "";  
        for(int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;  
        if(res == "") res = "0";  
        return res;  
      }  
      void clean() {  
        while(len > 1 && !s[len-1]) len--;  
      }  
```
/\* 以下是重载操作符 \*/
        
      
      
      
      
      
      
      
      
      
```cpp
      bign operator = (const char* num) {  
        len = strlen(num);  
        for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0';  
        return *this;  
      }  
      bign operator + (const bign& b) const{  
        bign c;  
        c.len = 0;  
        for(int i = 0, g = 0; g || i < max(len, b.len); i++) {  
          int x = g;  
          if(i < len) x += s[i];  
          if(i < b.len) x += b.s[i];  
          c.s[c.len++] = x % 10;  
          g = x / 10;  
        }  
        return c;  
      }  
      bign operator * (const bign& b) {  
        bign c; c.len = len + b.len;  
        for(int i = 0; i < len; i++)  
          for(int j = 0; j < b.len; j++)  
            c.s[i+j] += s[i] * b.s[j];  
        for(int i = 0; i < c.len-1; i++){  
          c.s[i+1] += c.s[i] / 10;  
          c.s[i] %= 10;  
        }  
        c.clean();  
        return c;  
      }  
      bign operator - (const bign& b) {  
        bign c; c.len = 0;  
        for(int i = 0, g = 0; i < len; i++) {  
          int x = s[i] - g;  
          if(i < b.len) x -= b.s[i];  
          if(x >= 0) g = 0;  
          else {  
            g = 1;  
            x += 10;  
          }  
          c.s[c.len++] = x;  
        }  
        c.clean();  
        return c;  
      }  
      bool operator < (const bign& b) const{  
        if(len != b.len) return len < b.len;  
        for(int i = len-1; i >= 0; i--)  
          if(s[i] != b.s[i]) return s[i] < b.s[i];  
        return false;  
      }  
      bool operator > (const bign& b) const{  
        return b < *this;  
      }  
      bool operator <= (const bign& b) {  
        return !(b > *this);  
      }  
      bool operator == (const bign& b) {  
        return !(b < *this) && !(*this < b);  
      }  
      bign operator += (const bign& b) {  
        *this = *this + b;  
        return *this;  
      }  
    };  
    istream& operator >> (istream &in, bign& x) {  
      string s;  
      in >> s;  
      x = s.c_str();  
      return in;  
    }  
    ostream& operator << (ostream &out, const bign& x) {  
      out << x.str();  
      return out;  
    }
int main(){
    bign M,N;
    cin>>M>>N;
    long long l=0,r=2000000000;
    long long mid;
    while(l<r){
        mid=(l+r)/2;
//        cout<<mid<<endl;
        bign ch=mid;
        bign now=ch*N;
        if(now<M&&now+N>M) break;
        if(now>M) r=mid;
        if(now<M) l=mid+1;
    }
    cout<<mid;
    return 0;
}
```

---

## 作者：AuroraIris (赞：7)

两种解法


1.高精除高精 注意不是高精除低精，所以。。。不能直接拷a/b问题（亲测不行，数据强）


2.二分+高精乘法 二分找商，如果这么想就很简单了


二分思想是很简单的 二分乘法看模板

```pas
var x,y,midx:ansistring;
i,mid,l,r:longint;
a:array[0..100000] of longint;
function pd(a1,b1:ansistring):boolean;
var n,i,j,la,lb,lc,ans:longint;
a,b,c:array[0..100000] of longint;
zzt:string;
begin
la:=length(a1);
lb:=length(b1);
for i:=1 to la do
a[la-i+1]:=ord(a1[i])-ord('0');
for i:=1 to lb do
b[lb-i+1]:=ord(b1[i])-ord('0');
for i:=1 to la do
begin
ans:=0;
for j:=1 to lb do
begin
c[i+j-1]:=a[i]*b[j]+ans+c[i+j-1];
ans:=c[i+j-1] div 10;
c[i+j-1]:=c[i+j-1] mod 10;
end;
c[i+j]:=ans;
end;
lc:=i+j;
while (c[lc]=0)and(lc>1) do
lc:=lc-1;//以上是乘法
if lc>length(x) then exit(false);//如果这个mid去乘被除数大了，那么说明mid大了，应缩小r
if lc<length(x) then exit(true);//反之则反
for i:=lc downto 1 do//如果位数相等，那么每个位去比较大小
begin
str(c[i],zzt);
if zzt<x[lc-i+1] then exit(true);//注意x是倒着来的，因为高精乘出来是反的
if zzt>x[lc-i+1] then exit(false);
end;
exit(true);
end;
function chengfa(a1,b1:ansistring):boolean;//纯属搞事
var n,i,j,la,lb,lc,ans:longint;
a,b,c:array[0..100000] of longint;
begin
la:=length(a1);
lb:=length(b1);
for i:=1 to la do
a[la-i+1]:=ord(a1[i])-ord('0');
for i:=1 to lb do
b[lb-i+1]:=ord(b1[i])-ord('0');
for i:=1 to la do
begin
ans:=0;
for j:=1 to lb do
begin
c[i+j-1]:=a[i]*b[j]+ans+c[i+j-1];
ans:=c[i+j-1] div 10;
c[i+j-1]:=c[i+j-1] mod 10;
end;
c[i+j]:=ans;
end;
lc:=i+j;
while (c[lc]=0)and(lc>1) do
lc:=lc-1;
for i:=lc downto 1 do
if c[i]<>a[i] then
exit(false);
exit(true);
end;//忽略上面这个function
begin
readln(x);
readln(y);
for i:=1 to length(x) do
val(x[i],a[i]);
l:=1;
r:=2000000000;
while l<r-1 do
begin
mid:=(l+r) div 2;
str(mid,midx);
{if chengfa(y,midx) then begin write(midx); halt; end;}//加了也没关系
if pd(y,midx) then l:=mid
              else r:=mid;
end;
write(l);
end.
```

---

## 作者：doby (赞：5)

其实这题很简单，根本不用二分……

先上暴力高精代码……

套板子系列……

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int la,lb,lc,a[30001],b[30001],c[30001],tmp[30001],i,x,j,d;
string t,s1,s2;
void print(int a[])//输出
{
    for(int i=a[0];i>0;i--){cout<<a[i];}
    return;
}
int compare(int a[],int b[])  //比大小
{
    if(a[0]>b[0]){return 1;}if(a[0]<b[0]){return -1;}
    for(int i=a[0];i>0;i--){if(a[i]>b[i]){return 1;}if(a[i]<b[i]){return -1;}}
    return 0;
}
void numcpy(int p[],int q[],int det){for(int i=1;i<=p[0];i++){q[i+det-1]=p[i];}q[0]=p[0]+det-1;}
void jian(int a[],int b[])//减法
{ 
    int flag,i; 
    flag=compare(a,b);
    if(flag==0){a[0]=0;return;}
    if(flag==1)
    {
        for(i=1;i<=a[0];i++){if(a[i]<b[i]){a[i+1]--,a[i]=a[i]+10;}a[i]=a[i]-b[i];}
        while(a[0]>0&&a[a[0]]==0){a[0]--;}
        return;
    }
}
void chugao(int a[],int b[],int c[])//除法
{
    c[0]=a[0]-b[0]+1;
    for(int i=c[0];i>0;i--)
    {
        memset(tmp,0,sizeof(tmp));numcpy(b,tmp,i);
        while(compare(a,tmp)>=0){c[i]++;jian(a,tmp);}
    }
    while(c[0]>0&&c[c[0]]==0){c[0]--;}
    return;
}
void adib(string a1,string b1)
{
    memset(a,0,sizeof(a));memset(b,0,sizeof(b));memset(c,0,sizeof(c));
    a[0]=a1.size();for(i=1;i<=a[0];i++){a[i]=a1[a[0]-i]-'0';}
    b[0]=b1.size();for(i=1;i<=b[0];i++){b[i]=b1[b[0]-i]-'0';}
    chugao(a,b,c);
    print(c);
    return;
}
int main()
{
    cin>>s1>>s2;
    adib(s1,s2);
}
```
二分思路也很简单，因为答案完全可以用int或者longlong存下去，然后二分猜答案……
~~其实是猜的，我还没写呢……~~


---

## 作者：Suiseiseki (赞：4)

在CCFoj上意外找到了一个高精模板，有高除高和高膜高的，觉得蛮好，就搬过来了

#并不需要二分答案，一个一个减就行了

用的是重载运算符，这样的话比较方便，但编程复杂度也迅速提高

下面就是代码，一堆注释。

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Wint:vector<int>//用标准库vector做基类，完美解决位数问题，同时更易于实现
{
    //将低精度转高精度的初始化，可以自动被编译器调用
    //因此无需单独写高精度数和低精度数的运算函数，十分方便
    Wint(int n=0)//默认初始化为0，但0的保存形式为空
    {
        push_back(n);
        check();
    }
    Wint& check()//在各类运算中经常用到的进位小函数，不妨内置
    {
        while(!empty()&&!back())pop_back();//去除最高位可能存在的0
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
        return *this;//为使用方便，将进位后的自身返回引用
    }
};
//输入输出
istream& operator>>(istream &is,Wint &n)
{
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}
ostream& operator<<(ostream &os,const Wint &n)
{
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}
//比较，只需要写两个，其他的直接代入即可
//常量引用当参数，避免拷贝更高效
bool operator!=(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return 1;
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return 1;
    return 0;
}
bool operator==(const Wint &a,const Wint &b)
{
    return !(a!=b);
}
bool operator<(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return a.size()<b.size();
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return a[i]<b[i];
    return 0;
}
bool operator>(const Wint &a,const Wint &b)
{
    return b<a;
}
bool operator<=(const Wint &a,const Wint &b)
{
    return !(a>b);
}
bool operator>=(const Wint &a,const Wint &b)
{
    return !(a<b);
}
//加法，先实现+=，这样更简洁高效
Wint& operator+=(Wint &a,const Wint &b)
{
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0; i!=b.size(); ++i)a[i]+=b[i];
    return a.check();
}
Wint operator+(Wint a,const Wint &b)
{
    return a+=b;
}
//减法，返回差的绝对值，由于后面有交换，故参数不用引用
Wint& operator-=(Wint &a,Wint b)
{
    if(a<b)swap(a,b);
    for(int i=0; i!=b.size(); a[i]-=b[i],++i)
        if(a[i]<b[i])//需要借位
        {
            int j=i+1;
            while(!a[j])++j;
            while(j>i)
            {
                --a[j];
                a[--j]+=10;
            }
        }
    return a.check();
}
Wint operator-(Wint a,const Wint &b)
{
    return a-=b;
}
//乘法不能先实现*=，原因自己想
Wint operator*(const Wint &a,const Wint &b)
{
    Wint n;
    n.assign(a.size()+b.size()-1,0);
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
Wint& operator*=(Wint &a,const Wint &b)
{
    return a=a*b;
}
//除法和取模先实现一个带余除法函数
Wint divmod(Wint &a,const Wint &b)
{
    Wint ans;
    for(int t=a.size()-b.size(); a>=b; --t)
    {
        Wint d;
        d.assign(t+1,0);
        d.back()=1;
        Wint c=b*d;
        while(a>=c)
        {
            a-=c;
            ans+=d;
        }
    }
    return ans;
}
Wint operator/(Wint a,const Wint &b)
{
    return divmod(a,b);
}
Wint& operator/=(Wint &a,const Wint &b)
{
    return a=a/b;
}
Wint& operator%=(Wint &a,const Wint &b)
{
    divmod(a,b);
    return a;
}
Wint operator%(Wint a,const Wint &b)
{
    return a%=b;
}
//顺手实现一个快速幂，可以看到和普通快速幂几乎无异
Wint pow(const Wint &n,const Wint &k)
{
    if(k.empty())return 1;
    if(k==2)return n*n;
    if(k.back()%2)return n*pow(n,k-1);
    return pow(pow(n,k/2),2);
}
//通过重载运算符，还可以实现++、--、^、!、逻辑运算符等很多运算，十分简单，此处都不写了
int main()//现在你完全可以像int一般便捷地使用Wint，如下
{
    Wint a,b;
    //可以把b改成int型，仍能正常使用
    cin>>a>>b;
    cout<<a/b<<endl;
}
```
（无意翻到了这题，就水了一下）


---

## 作者：hsfzLZH1 (赞：4)

## 所谓高精度，就是用数组模拟大整数笔算的各种计算。

（由于本人的能力限制，暂时不能为大家提供高精度压位的代码）

存储一个高精度数，我们可以存储他的位数，s[0]是个位，s[1]是十位，以此类推，代码如下：

```cpp
struct bigint
{
    long long s[maxn],l;
    bigint(){memset(s,0,sizeof s);l=1ll;}
    void in(){char c[maxn];scanf("%s",c);l=strlen(c);for(int i=0;i<l;i++)s[i]=(long long)c[l-i-1]-'0';}
}
```
如何计算加法？考虑我们从小学开始就学会的笔算加法，我们从最低位开始，将两个数字上的位置相加，在处理进位，可以设计代码如下：

```cpp
bigint operator+(bigint a)
{
    bigint ans;
    ans.l=max(l,a.l)+1;
    for(int i=0;i<ans.l;i++)
    {
        ans.s[i]=s[i]+a.s[i]+ans.s[i-1]/10ll;
        ans.s[i-1]%=10ll;
    }
    if(!ans.s[ans.l-1ll])ans.l--;
    return ans;
}
```
比较大小就是先比较位数，然后从高位开始，依次比较两位的值。

我们同样可以通过小学学到的笔算乘法，设计出乘法操作（大整数\*小整数）

## 关于二分

因为我们要计算的是n/m的向下取整，所以如果m\*mid<=n，那么就取右区间，否则就取左区间。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20010;//大整数的最大位数
long long l,r=2e18,mid;//l和r是二分区间
struct bigint//大整数结构体
{
    long long s[maxn],l;
    bigint(){memset(s,0,sizeof s);l=1ll;}//定义
    void in(){char c[maxn];scanf("%s",c);l=strlen(c);for(int i=0;i<l;i++)s[i]=(long long)c[l-i-1]-'0';}//输入
    bool operator<(bigint a)//相当于<=号
    {
        if(l!=a.l)return l<a.l;
        for(int i=l-1;i>=0;i--)if(s[i]!=a.s[i])return s[i]<a.s[i];
        return true; 
    }
    bigint operator+(bigint a)//相当于加法
    {
        bigint ans;
        ans.l=max(l,a.l)+1;
        for(int i=0;i<ans.l;i++)
        {
            ans.s[i]=s[i]+a.s[i]+ans.s[i-1]/10ll;
            ans.s[i-1]%=10ll;
        }
        if(!ans.s[ans.l-1ll])ans.l--;
        return ans;
    }
    bigint*operator+=(bigint a){*this=*this+a;return this;}//就是+=
    bigint operator*(long long a)//大整数*小整数
    {
        bigint ans;
        ans.l=l;
        for(int i=0;i<l;i++)ans.s[i]=s[i]*a;
        for(int i=0;i<l;i++)ans.s[i+1]+=ans.s[i]/10ll,ans.s[i]%=10ll;
        while(ans.s[ans.l])ans.l++,ans.s[ans.l]+=ans.s[ans.l-1]/10ll,ans.s[ans.l-1]%=10ll;
        return ans;
    }
}n,m;
int main()
{
    n.in();m.in();//输入
    while(l+1<r)//二分
    {
        mid=(l+r)>>1;
        if(m*mid<n)l=mid;//取右区间
        else r=mid;//取左区间
    }
    printf("%lld\n",l);//答案一定是l，答案的范围一定在[l,r)之间
    return 0;
}
```

---

## 作者：FjswYuzu (赞：3)

~~又可以用我的高精模板水题了~~

$As\text{ }we\text{ }know$，这道题要用高精。既然写高精，vector就是一个KO大多竞争对手的玩意儿，因为它自动逆转，处理会更快一些。下面讲述一下vector的实现方法

```cpp
#include<iostream>
#include<vector>
#include<string>
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
        while(!empty()&&!back())pop_back();//去除前导零
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
        return *this;//处理函数
    }
};
istream& operator>>(istream &is,Wint &n)
{
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}
ostream& operator<<(ostream &os,const Wint &n)
{
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}//输入输出
bool operator!=(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return 1;
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return 1;
    return 0;
}
bool operator==(const Wint &a,const Wint &b)
{
    return !(a!=b);
}
bool operator<(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return a.size()<b.size();
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return a[i]<b[i];
    return 0;
}
bool operator>(const Wint &a,const Wint &b)
{
    return b<a;
}
bool operator<=(const Wint &a,const Wint &b)
{
    return !(a>b);
}
bool operator>=(const Wint &a,const Wint &b)
{
    return !(a<b);
}//关系运算符
Wint& operator+=(Wint &a,const Wint &b)
{
    if(a.size()<b.size())a.resize(b.size());//处理位数
    for(int i=0; i!=b.size(); ++i)a[i]+=b[i];//按位加
    return a.check();
}
Wint operator+(Wint a,const Wint &b)
{
    return a+=b;
}
Wint& operator-=(Wint &a,Wint b)
{
    if(a<b)swap(a,b);//注意，这里不能够处理发生负数的情况
    for(int i=0; i!=b.size(); a[i]-=b[i],++i)
        if(a[i]<b[i])
        {
            int j=i+1;
            while(!a[j])++j;
            while(j>i)
            {
                --a[j];
                a[--j]+=10;
            }//按位减
        }
    return a.check();
}
Wint operator-(Wint a,const Wint &b)
{
    return a-=b;
}
Wint operator*(const Wint &a,const Wint &b)
{
    Wint n;
    n.assign(a.size()+b.size()-1,0);//a*b的最大位数，后面会去除前导0
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
Wint divmod(Wint &a,const Wint &b)
{
    Wint ans;
    for(int t=a.size()-b.size(); a>=b; --t)
    {
        Wint d;
        d.assign(t+1,0);
        d.back()=1;
        Wint c=b*d;
        while(a>=c)
        {
            a-=c;
            ans+=d;//这里是一个一个慢慢减的，但是可以进行优化，比如倍增等
        }
    }
    return ans;
}
Wint operator/(Wint a,const Wint &b)
{
    return divmod(a,b);
}
int main()
{
    Wint n,m;
    cin>>n>>m;
    cout<<n/m;//输入，输出，完成
	return 0;
}
```

请注意：这个模板只适用于没有符号的情况！

---

## 作者：doby (赞：2)

淳朴到预估错误的高精除法，没错，一点区别都没有……

明明难度只有普及的，这标签很清真啊……

不要指望还能用同余定理，这回的位数变长了……

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int la,lb,lc,a[30001],b[30001],c[30001],tmp[30001],i,x,j,d;
string t,s1,s2;
void print(int a[])
{
    for(int i=a[0];i>0;i--){cout<<a[i];}
    return;
}
int compare(int a[],int b[])  
{
    if(a[0]>b[0]){return 1;}if(a[0]<b[0]){return -1;}
    for(int i=a[0];i>0;i--){if(a[i]>b[i]){return 1;}if(a[i]<b[i]){return -1;}}
    return 0;
}
void numcpy(int p[],int q[],int det){for(int i=1;i<=p[0];i++){q[i+det-1]=p[i];}q[0]=p[0]+det-1;}
void jian(int a[],int b[])
{ 
    int flag,i; 
    flag=compare(a,b);
    if(flag==0){a[0]=0;return;}
    if(flag==1)
    {
        for(i=1;i<=a[0];i++){if(a[i]<b[i]){a[i+1]--,a[i]=a[i]+10;}a[i]=a[i]-b[i];}
        while(a[0]>0&&a[a[0]]==0){a[0]--;}
        return;
    }
}
void chugao(int a[],int b[],int c[])
{
    c[0]=a[0]-b[0]+1;
    for(int i=c[0];i>0;i--)
    {
        memset(tmp,0,sizeof(tmp));numcpy(b,tmp,i);
        while(compare(a,tmp)>=0){c[i]++;jian(a,tmp);}
    }
    while(c[0]>0&&c[c[0]]==0){c[0]--;}
    return;
}
void adib(string a1,string b1)
{
    memset(a,0,sizeof(a));memset(b,0,sizeof(b));memset(c,0,sizeof(c));
    a[0]=a1.size();for(i=1;i<=a[0];i++){a[i]=a1[a[0]-i]-'0';}
    b[0]=b1.size();for(i=1;i<=b[0];i++){b[i]=b1[b[0]-i]-'0';}
    chugao(a,b,c);
    print(c);
    return;
}
int main()
{
    cin>>s1>>s2;
    adib(s1,s2);
}
```

---

## 作者：FjswYuzu (赞：2)

机房记：~~又水了一道好题~~

----------

众所周知，这道题要写高精，其中高÷高是最让人头疼的

329ms跑的还是挺快的..

那么现在安利一下教练的vector重载高精模板：

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Wint:vector<int>//写一个结构体
{
    Wint(int n=0)
    {
        push_back(n);
        check();
    }
    Wint& check()
    {
        while(!empty()&&!back())pop_back();//删前导0（虽然可以不要）
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
istream& operator>>(istream &is,Wint &n)
{
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}//用istream写输入
ostream& operator<<(ostream &os,const Wint &n)
{
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}//用ostream写输出
bool operator!=(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return 1;
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return 1;
    return 0;
}
bool operator==(const Wint &a,const Wint &b)
{
    return !(a!=b);
}
bool operator<(const Wint &a,const Wint &b)
{
    if(a.size()!=b.size())return a.size()<b.size();
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return a[i]<b[i];
    return 0;
}
bool operator>(const Wint &a,const Wint &b)
{
    return b<a;
}
bool operator<=(const Wint &a,const Wint &b)
{
    return !(a>b);
}
bool operator>=(const Wint &a,const Wint &b)
{
    return !(a<b);
}//关系运算符
Wint& operator+=(Wint &a,const Wint &b)
{
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0; i!=b.size(); ++i)a[i]+=b[i];
    return a.check();
}
Wint operator+(Wint a,const Wint &b)
{
    return a+=b;
}
Wint& operator-=(Wint &a,Wint b)
{
    if(a<b)swap(a,b);
    for(int i=0; i!=b.size(); a[i]-=b[i],++i)
        if(a[i]<b[i])
        {
            int j=i+1;
            while(!a[j])++j;
            while(j>i)
            {
                --a[j];
                a[--j]+=10;
            }
        }
    return a.check();
}
Wint operator-(Wint a,const Wint &b)
{
    return a-=b;
}
Wint operator*(const Wint &a,const Wint &b)
{
    Wint n;
    n.assign(a.size()+b.size()-1,0);
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
Wint divmod(Wint &a,const Wint &b)
{
    Wint ans;
    for(int t=a.size()-b.size(); a>=b; --t)
    {
        Wint d;
        d.assign(t+1,0);
        d.back()=1;
        Wint c=b*d;
        while(a>=c)
        {
            a-=c;
            ans+=d;
        }
    }
    return ans;
}//divmod除法的核心
Wint operator/(Wint a,const Wint &b)
{
    return divmod(a,b);
}//四则运算
int main()
{
    Wint n,m;
    cin>>n>>m;
    cout<<n/m;
	return 1;//防抄
}
```

by ~~去年十月的我：vector是个什么？？不用~~

---

