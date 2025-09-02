# 「HGOI-1」Number

## 题目背景

$\text{bh1234666}$ 正在学习乘法！

## 题目描述

$\text{bh1234666}$ 有一定数量的数字 $0 \sim 9$，现在他想让你寻找一种分配方案，将它们分成两个整数，使得他们的乘积 $p$ 最大。
 
由于 $\text{bh1234666}$ 不喜欢太大的数，所以你只需要输出**两个非负整数**，使它们的乘积**等于**最大乘积 $p$，但是这两个整数 $0 \sim 9$ 的数量不能等于给定的数量（任意一个数字数量不相等即可，**不考虑前导零**）。

$\text{bh1234666}$ 是很善良的，如果 $0 \sim 9$ 的数量等于给定的数量了，你依旧可以得到的一半的分。

## 说明/提示

#### 样例解释
最大可能乘积为 $97643210 \times 88653221=13949030 \times 620572547=8656385075279410$。

若输出 $97643210 \times 88653221$ 则只能得到一半的分，因为 $0\sim 9$ 出现的次数与给定的相同。

#### 数据范围及约定
本题采用**捆绑测试**，共有 $5$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \sum c_i\le \cr\hline
1 & 10 & 20 \cr\hline
2 & 20 & 100 \cr\hline
3 & 20 & 5000 \cr\hline
4 & 20 & 10^6 \cr\hline
5 & 30 & 10^7 \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，保证 $1 \le c_i$，$\sum c_i \le 10^7$。

#### 说明

本题有 $\text{spj}$，两数乘积正确得一半的分，数量与给出的不同且乘积正确得全部分数。故每一 $\text{subtask}$ 的得分为其中所有数据点得分的**最小值**。


## 样例 #1

### 输入

```
1 2 3 2 1 1 2 1 2 1```

### 输出

```
13949030
620572547```

# 题解

## 作者：bh1234666 (赞：15)

首先考虑使两数乘积最大。

为便于描述，将两个数前均加上 $0.$ ，使其变为小数。

经过这样的变化后，有几个显然的性质：两数均在 $0.8$ 到 $1$ 之间，两数末尾的 $0$ 可以忽略，因此接下来我们可以忽略题目给出的 $0$。

设 $k=\sum c_i$，显然在变化之后的乘积是变化之前的 $10^{-k}$，与如何分配数字及如何排列无关。

假设将两数中在高位且值较大的数字跟另一数中在低位且值较小的数字交换。

设两数分别为 $a,b(0.1<a,b<1)$ 其中需要交换的两位置的值为 $x,y(0\le x < y \le 9)$,权为 $n,m(0\le n\times 10 \le m \le 0.1)$。

则交换 $x,y$ 前两数乘积为 $a\times b$。

交换 $x,y$ 后两数乘积为：

$(a-x\times n+y\times n)\times (b-y\times m+x\times m)$

$=a\times b+2\times x\times y\times n\times m-x^2\times n\times m-y^2\times n\times m+a\times m\times(x-y)-b\times n\times (x-y)$

$=a\times b - n\times m\times (x-y)^2-(x-y)\times(a\times m-b\times n)$

设 $x-y=t(-9\le t\le -1)$

则变化量（修改后减去修改前）为：

$-n\times m\times t^2-t\times(a\times m-b\times n)$

$=-t\times(n\times m\times t+a\times m-b\times n)$

其中：

$n\times m\times t+a\times m-b\times n$

$< n\times m \times (-1)+1\times m-0.1\times n$

$< m-0.1\times n$

$\le 0$

因为 $-t>0$，所以最终变化量小于。即将高位的较大的数与低位的较小的数互换结果一定更劣，所以大数必定在高位。

因此两数长度差至多为 $1$，否则违反了上述原则（存在 $0$ 所在位高于其他数）。当两数长度不等时，在短的数末尾补 $0$ 使得两数长度相同。

由于相同的权对应的能填的位置只有两个，因此我们可以确定每个数字对应的权，因此两数的和就被固定下来了。

显然，两数和一定，差越小，积越大，因此我们要分配两组数使得两数差最小。

假设两数分别为 $A$,$B$。

从高位开始分配，第一次两数分配到的数不同后，假设 $A$ 分配到了较大的数，那么由于 $A$ 高位存在大数，因此之后无论如何 $A$ 都大于 $B$，因此接下来每一组中的大的数均分配给 $B$ 。

接下来考虑如何让两数 $0 \sim 9$ 的数量不等于给定的数量。

做个卷积把两数乘起来，输出乘积和 $1$ 即可获得 70 分~~不会吧不会吧不会真的有人 T2 写卷积吧~~。

100 分:由于给定的数每个数至少有一个，因此两数必有一数以 $0$ 结尾，把它除以二另一个乘二即可。

由于两数开头一定为 $8,9$ 或 $9,9$，因此一数乘二一数除以二必定会导致一数长度加一一数长度不变，数字总数量与给定的个数不等，必定有数数量与原先不一样。

代码:

```
#include<stdio.h>
char s1[1000005],s2[1000005];int l1,l2;
void half(char *s,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		s[i]-='0';
		if(s[i]&1) s[i+1]+=10;
		s[i]>>=1;
		s[i]+='0';
	}
	if(s[0]=='0') puts(s+1);
	else puts(s);
}
void dble(char *s,int len)
{
	int i;_Bool fl=0;
	for(i=len-1;i>=0;i--)
	{
		s[i]-='0';
		if(s[i]>4) s[i]<<=1,s[i]-=10,s[i]+=fl,fl=1;
		else s[i]<<=1,s[i]+=fl,fl=0;
		s[i]+='0';
	}
	if(fl) putchar('1');
	puts(s);
}
int main()
{
	int i,j,a[10];_Bool flag=0;
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);
	for(j=0,i=9;j<2;j++)
	{
		for(;j&&i>=0;i--)
			if(a[i])
			{
				a[i]--;
				s2[l2++]='0'+i;
				break;
			}
		for(;i>=0;i--)
		{
			while(a[i])
			{
				a[i]--;
				if(!flag) s1[l1++]='0'+i;
				else s2[l2++]='0'+i;
				flag=!flag;
			}
			if(flag&&!j) break;
		}		
	}
	if(s1[l1-1]=='0')
	{
		half(s1,l1);
		dble(s2,l2);
	}
	else
	{
		half(s2,l2);
		dble(s1,l1);
	}
	return 0;
}
```


---

## 作者：linyuhao (赞：7)

# 乘积最大
要让两个数的乘积最大，就要让更大的数字占在更高的位置，产生更大的贡献。也就是从最高位开始，放入大的数字。按这种方法，不论放入哪一个数串里，这个数字产生的贡献是一样的，也就是两个数串的**和**是**一定**的。  
设两个数串和为 $X$，差为 $Y$，两个数串分别为 $\frac{X+Y}{2}$,$\frac{X-Y}{2}$。那么积为 $\frac{X^2-Y^2}{4}$。**和一定**，**差越小**，**积越大**。                 
**结论**，从大到小依次放入数字，让两个数串的差值最小。
## 放法
 
从大到小存入数字。

```
for(int i=0;i<=9;i++){
	aa[i]=read();
	ans+=aa[i];
}
for(int i=9;i>=0;i--){
	for(int j=1;j<=aa[i];j++){
		s+=(i+'0');
	}
}
```
**情况一** 要放入的两个数字一样，则都放入。  
**情况二** 不一样，则将大的数字放入更小的数串后面。  
**特判** 如果只有奇数个数，最后只放一个数字。

```
for(int i=0;i<s.size();i+=2){
	if(i==s.size()-1){
		if(s1<s2)s1+=s[i];
		else s2+=s[i];
		break;
	}//特判
	else if(s[i]==s[i+1]){
		s1+=s[i];
		s2+=s[i+1];
	}//相同
	else{
		if(s1<s2)s1+=s[i],s2+=s[i+1];
		else s2+=s[i],s1+=s[i+1];
	}//不相同，大数给小串
}
```

# 数串不同
由于必有一个零，就可以去掉一个末尾零，第一个数串乘上 $2$，第二个数串乘上 $5$，问题就转换为低精乘高精。最后输出的时候，少输出一个零就可以了。
```
void sh(string x,int y){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int s11=x.length();
   	for(int i=0;i<s11;i++) 
	   a[i]=x[s11-i-1]-'0';
   	for(int i=0;i<s11;i++){
   		c[i]=a[i]*y;	
   	}
   	int s3=s11+1;
	for(int i=0;i<s3;i++){
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	for(;!c[s3]&&s3>0;){
		s3--;
	}
	for(int j=s3;j>=0;j--){
		if(j==0&&c[j]==0&&pd==0)pd=1;
		else cout<<c[j];
	}
}
sh(s1,2);
cout<<endl;
sh(s2,5);
```
$pd$ 用来判断是否只去掉一个零。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[10000001]={0},a[10000001]={0},b[10000001]={0};
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
string s1,s2,s;
int pd=0;
void sh(string x,int y){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int s11=x.length();
   	for(int i=0;i<s11;i++) 
	   a[i]=x[s11-i-1]-'0';
   	for(int i=0;i<s11;i++){
   		c[i]=a[i]*y;	
   	}
   	int s3=s11+1;
	for(int i=0;i<s3;i++){
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	for(;!c[s3]&&s3>0;){
		s3--;
	}
	for(int j=s3;j>=0;j--){
		if(j==0&&c[j]==0&&pd==0)pd=1;
		else cout<<c[j];
	}
}
long long aa[10];
int main(){
	
	int ans=0;
	for(int i=0;i<=9;i++){
		aa[i]=read();
		ans+=aa[i];
	}
	for(int i=9;i>=0;i--){
		for(int j=1;j<=aa[i];j++){
			s+=(i+'0');
		}
	}
	for(int i=0;i<s.size();i+=2){
		if(i==s.size()-1){
			if(s1<s2)s1+=s[i];
			else s2+=s[i];
			break;
		}
		else if(s[i]==s[i+1]){
			s1+=s[i];
			s2+=s[i+1];
		}
		else{
			if(s1<s2)s1+=s[i],s2+=s[i+1];
			else s2+=s[i],s1+=s[i+1];
		}
	}
	sh(s1,2);
	cout<<endl;
	sh(s2,5);
	return 0;
}
```


---

## 作者：VIOLET__FOREVER (赞：3)

题目[传送门](https://www.luogu.com.cn/problem/P8482)
## 思路提供
首先我们可以从题目给出的部分分入手，先拿到 $50$ 分，这个我们可以通过贪心的手段保证两个数字的总和相同(因为只要保持相同就可以使得两个数的乘积最大)，所以每次将数字加在总分较少的字符串上就可以保证两个字符串表示的数字的乘积最大，如果出现两个两个字符串内所有数字的总和相同的情况，就默认加在第一个的字符串里，这样就可以列举出两个保证最大乘积的字符串，而我们看到题目中保证会有一个 $0$ 的出现，而我们要使乘积不变，而改变两个数，所以我们考虑一个 $0$(可以拆成一个 $2$ 和一个 $5$ 的乘积)这样的话，我们只要去掉一个末尾的 $0$(即除去一个 $10$)，再将剩下的数一个乘上 $2$，一个乘上 $5$ 就能保证总乘积不变，而考虑本题的数据范围过大，所以我们需要加上一个高精乘低精的高精度运算即可(可借鉴[模板题](https://www.luogu.com.cn/problem/P1303))。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
string ans1,ans2;//分别记录答案，string十分方便
int num[15];
int tot,a[100000005];
int al[10000005],b[10000005],c[10000005];//数组要开大一些
void sh(string x,int y){//高精乘低精的模板
	memset(a,0,sizeof(al));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	int s11=x.length();
   	for(int i=0;i<s11;i++) 
	   al[i]=x[s11-i-1]-'0';
   	for(int i=0;i<s11;i++){
   		c[i]=al[i]*y;	
   	}
   	int s3=s11+1;
	for(int i=0;i<s3;i++){
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	for(;!c[s3]&&s3>0;){
		s3--;
	}
    while(c[s3]==0&&s3>=1) s3--;//去除前导零
    for(int j=s3;j>=0;j--){
        cout<<c[j];
	}
    cout<<endl;
}
signed main(){
	for(int i=0;i<=9;i++){
		cin>>num[i];
		for(int j=1;j<=num[i];j++){
			tot++;
			a[tot]=i;
		}
	}
	ans1+=a[tot]+'0';
	ans2+=a[tot-1]+'0';//各自先加上一个数
	int tot1=a[tot],tot2=a[tot-1],flag=1;
	if(tot1==tot2) flag=0;
	for(int i=tot-2;i>1;i--){
		if(i-1>1){
			if(tot1<tot2){
				ans1+=a[i]+'0';
				ans2+=a[i-1]+'0';
			}
			else if(tot1>tot2){
				ans1+=a[i-1]+'0';
				ans2+=a[i]+'0';
			}//考虑总分不同
			else{
				if(flag==0 && a[i]!=a[i-1]){
					tot1=a[i];
					tot2=a[i-1];
					flag=1;
				}//相同的情况进行考虑
				ans1+=a[i]+'0';
				ans2+=a[i-1]+'0';
			}
			i--;
		}
		else{
			if(tot1<=tot2){
				ans1+=a[i]+'0';
				tot1+=a[i];
			}
			else{
				ans2+=a[i]+'0';
				tot2+=a[i];
			}
		}
	}
   sh(ans1,2);
	sh(ans2,5);//最后的输出
	return 0;
}
```



---

## 作者：bh1234666 (赞：2)

贪心的方法已经有很多题解提出了，这里给出一种无需利用条件 $C_i\ge1$ 的求出答案的方法。

显然，直接将两数相乘输出然后再输出 $1$ 是符合要求的，你可以通过卡常在时限内完成高精度乘法（[是可以实现的](https://bh1234666.blog.luogu.org/ab-problem-ka-chang)，实际上，spj 甚至在时限内完成了 $2$ 轮高精度乘法），或者使用技巧快速乘出。

根据贪心策略，我们会发现两数的格式都形如 $99\dots988\dots8\dots00\dots0$，一段连续的数可以表示为 $\dfrac{((10^a-1)/9)\times b\times 10^c}9(11\dots100\dots0\times b)$ 的形式，因此我们可以将它们表示为 $\dfrac{\sum ((10^a-1)/9)\times b\times 10^c}9$ 即 $\dfrac{\sum b\times 10^{a+c}-b\times 10^c}9$。

先不考虑 $\dfrac 1 9$。

显然，每个数最终会被拆分成 $20$ 项形如 $n\times 10^m$ 的形式，暴力两两相乘，任意两项相乘都可以 $O(1)$ 处理，最终会产生 $400$ 项，500ms 绰绰有余，得到结果后除 $81$ 即可。

于是我们可以快速的得到两数相乘的结果，那么输出这个结果和 $1$ 就可以通过此题。

~~要是出题的时候就想到这种方法就直接让输出一个数了。~~

代码：

```
#include<stdio.h>
int a[11];
struct num{
	int a,b;//一个形如 a*10^b 的数
	num operator * (num x)
	{
		return {a*x.a,b+x.b};
	}
}num1[21],num2[21],num3[401];
char s1[10000005],s2[10000005];
int l1,l2;bool flag=0;
int ans[10000005];
int main()
{
	for(int i=0;i<10;i++)
		scanf("%d",&a[i]);
	for(int j=0,i=9;j<2;j++)
	{
		for(;j&&i>=0;i--)
			if(a[i])
			{
				a[i]--;
				s2[l2++]=i;
				break;
			}
		for(;i>=0;i--)
		{
			while(a[i])
			{
				a[i]--;
				if(!flag) s1[l1++]=i;
				else s2[l2++]=i;
				flag=!flag;
			}
			if(flag&&!j) break;
		}		
	}//得到两数(s1,s2) 
	for(int i=9,j=0;i>=1;i--)
	{
		num1[i<<1]={i,l1-j};
		for(;s1[j]==i;j++);
		num1[(i<<1)+1]={-i,l1-j};
	}
	for(int i=9,j=0;i>=1;i--)
	{
		num2[i<<1]={i,l2-j};
		for(;s2[j]==i;j++);
		num2[(i<<1)+1]={-i,l2-j};
	}//将两数分解 
	for(int i=0;i<20;i++)
		for(int j=0;j<20;j++)
			num3[i*20+j]=num1[i]*num2[j];//暴力相乘 
	for(int i=0;i<400;i++)
		ans[num3[i].b]+=num3[i].a;
	for(int i=0;i<10000000;i++)//处理进位
		if(ans[i]>=10)
		{
			ans[i+1]+=ans[i]/10;
			ans[i]%=10;
		}
		else if(ans[i]<0)
		{
			ans[i+1]-=(-ans[i]+9)/10;
			ans[i]+=(-ans[i]+9)/10*10;
		}
	int now=0,hd=-1;
	for(int i=9999999;i>=0;i--)//除81 
	{
		now=now*10+ans[i];
		ans[i]=now/81;
		now%=81;
		if(hd==-1&&ans[i]) hd=i;
	}
	for(int i=hd;i>=0;i--)
		putchar('0'+ans[i]);
	printf("\n1");
	return 0;
}
```

---

## 作者：Full_Speed (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8482)

## 题意
给出 $0 ∼ 9$ 的数字个数且数字个数**不小于一**，求两个非负整数，使它们的乘积等于最大乘积，但是这两个整数 $0 ∼ 9$ 的数量不能等于给定的数量。
## 分析
如果我们想求出这两个整数，就需要先求出它们的最大乘积。要使它们的乘积最大，就要让最高位更大，且让两个数字相差最小，然后我们就可以求出乘积了。

然后我们考虑如何使它们的数字数量不同，因为数字个数**不小于一**，所以必定有一个偶数，我们只需要将两数中任意偶数除以二，另一个数乘二就可以了。因为任意组成的一个数乘二比原来位数多一位，任意组成的一个数除以二位数不变，所以它们的数字数量一定不同。

最后附上 AC 代码：
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long c[10];
int a[5000010],b[5000010];
using namespace std;
struct bigint{			//高精模板 
	int a[5000010],len,ff;
	bigint(){memset(a,0,sizeof(a));len=0;ff=0;}
    friend void putb(bigint Z)
    {
        if(Z.len==0)putchar('0');
        else 
        {
            if(Z.ff==1)putchar('-');
            for(register int i=Z.len;i>=1;i--)putchar(Z.a[i]+'0');
        }
        return;
    }
	friend bigint operator * (const bigint &A,const int &b)
	{
		bigint C;C.len=A.len;
		for(register int i=1;i<=A.len;i++)
		{
			C.a[i]+=A.a[i]*b;
			C.a[i+1]+=C.a[i]/10;
			C.a[i]%=10;
		}
		while(C.a[C.len+1])
		{
			C.len++;
			C.a[C.len+1]+=C.a[C.len]/10;
			C.a[C.len]%=10;
		}
        while(C.a[C.len]==0&&C.len>0)C.len--;
		return C;
	}
	friend bigint operator / (const bigint &Z,const int &b)
    {
    	bigint C=Z;
        int m=Z.len;
        for(register int i=m;i>=1;i--)
        {
        	if(i>1)C.a[i-1]+=C.a[i]%b*10;
            C.a[i]=C.a[i]/b;
        }
        while(C.a[m]==0&&m>0)m--;
        C.len=m;
        return C;
    }
};
int main()
{
	bigint x,y;
	for(int i=0;i<=9;i++)scanf("%d",&c[i]);
	int top=0,top2=0;
	for(int i=9;i>=0;i--)		//使乘积最大 
	{
		while(c[i]>0)			//首先让一个数的高位大于另一个数 
		{
			if(top==top2&&c[i]>0)a[++top]=i,c[i]--;
			if(top2<top&&c[i]>0)b[++top2]=i,c[i]--;
			if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
		}
		if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
	}
	for(int i=9;i>=0;i--)		//然后使较小的数低位更大 
	{
		while(c[i]>0)
		{
			if(top2==top&&c[i]>0){b[++top2]=i;c[i]--;}
			if(top<top2&&c[i]>0){a[++top]=i;c[i]--;}
		}
	}							//a*b即为最大乘积 
	x.len=top;y.len=top2;
	for(int i=1;i<=top;i++)x.a[top+1-i]=a[i];
	for(int i=1;i<=top2;i++)y.a[top2+1-i]=b[i];
	if(x.a[1]%2==0)				//判断奇偶 
	{
		putb(x/2);putchar('\n');
		putb(y*2);
	}
	else
	{
		putb(y/2);putchar('\n');
		putb(x*2);
	}
	return 0;
}
```


---

## 作者：the___ (赞：0)

# 知识
当 $a+b$ 为定值时，$|a-b|$ 越小，$ab$ 越大。

证明：

设 $a+b=x$，$a-b=y$。

则前式加后式得 $2a=x+y$，前式减后式得 $2b=x-y$，

两式相乘得 $2a·2b=(x+y)(x-y)$，

即 $4ab=x^2-y^2$。

$∴$ $y^2$ 越小，$ab$ 越大，

即 $|a-b|$ 越小，$ab$ 越大。
# 思路
本题可分为两步：1. 选数确定乘积。 2. 找数输出。
1. 贪心思想：保证两数和最大，并使两数差尽可能小。

   设两数为 $a$、$b$。数字从大到小判断。
   
   若 $a$ 大，则存入 $b$，否则存入 $a$。
   
   但此法不够优，会有两组超时，可优化为：若两数位数不一，则将少者补齐，之后小数后面插入 ⌈$c_i/2$⌉ 个数，大数后面插入 ⌊$c_i/2$⌋ 个数。
1. 该部分似乎并不好求，但注意数据范围 $1≤c_i$，两数中必有一数以 $0$ 结尾，可将其除以 $2$，并将另一数乘 $2$ 即符合要求。

   原因：
   
   $∵$ $1≤c_i$，
   
   $∴$ 两数必分别以 $9$、$8$ 开头。
   
   不妨设 $a$ 以 $0$ 结尾，
   
   则 $a$ 应除以 $2$，$b$ 应乘 $2$，
   
   此时 $a$ 位数不变，而 $b$ 位数会加 $1$。
   
   若 $0-8$ 的数字总个数均相同，则 $9$ 的总个数必不同，
   
   若 $0-8$ 的数字总个数有不同，则不同。
   
   故此法得到的两数与原两数 $0-9$ 的个数必有不同。
# 代码
奉上代码
```cpp
#include<iostream>                                   //简洁的头文件
using namespace std;
int main(){
        int c[10];
        string a="",b="";
        for(int i=0;i<=9;i++)
            cin>>c[i];
        for(int i=9;i>=0;i--){
            if(a.length()<b.length()){                      //补全
                a+=i+'0';
                c[i]--;
            }
            if(b.length()<a.length()){
                b+=i+'0';
                c[i]--;
            }
            for(int j=1;j<=c[i]/2;j++){                     //插入
                a+=i+'0';
                b+=i+'0';
            }
            if(c[i]>>1<<1!=c[i]){
                if(a<b)
                    a+=i+'0';
                else
                    b+=i+'0';
            }
        }
        if(a[a.length()-1]==0){                             //转化
            for(int i=0;i<a.length();i++){
                if((a[i]-'0')>>1<<1!=a[i]-'0'){
                    a[i+1]+=10;
                    a[i]--;
                }
                a[i]=(a[i]-'0')/2+'0';
            }
            for(int i=b.length()-1;i>=0;i--){
                a[i]=(a[i]-'0')*2+'0';
                if(i+1<b.length()){
                    if(b[i+1]>=10+'0'){
                        b[i+1]-=10;
                        b[i]++;
                    }
                }
            }
            if(b[0]>=10){
                b[0]-=10;
                b="1"+b;
            }
        }
        else{
            for(int i=0;i<b.length();i++){
                if((b[i]-'0')>>1<<1!=b[i]-'0'){
                    b[i+1]+=10;
                    b[i]--;
                }
                b[i]=(b[i]-'0')/2+'0';
            }
            for(int i=a.length()-1;i>=0;i--){
                a[i]=(a[i]-'0')*2+'0';
                if(i+1<a.length()){
                    if(a[i+1]>=10+'0'){
                        a[i+1]-=10;
                        a[i]++;
                    }
                }
            }
            if(a[0]>=10){
                a[0]-=10;
                a="1"+a;
            }
        }
        cout<<a<<endl<<b;
        return 0;
} 
```
注：本人高精可能比较怪异（用字符串且乘法未倒置），请谅解。

若有疏漏、不详之处，恳请大佬指点。

---

## 作者：紊莫 (赞：0)

感觉没有这么复杂。  

## 思路

显然的，对于两个数中任意一个数，每个数位都应该从大到小排列才能使得乘积最大。  

我们根据小学二年级学过的知识，两个和一定的数，差越小积越大。  

因此，我们可以来分配每一位上应该出现的两个数，很明显，就是从大到小每次选择两个数字，至此，两数之和已经确定。  

接下来讨论一下如何分配，不妨设每一位上可选的数为 $a$ 和 $b$，答案为 $A$ 和 $B$，且有 $A>B$。  

首先，对于这一位上两者相等的情况，直接赋值即可。  
对于第一次 $a\ne b$ 的情况，因为有 $A>B$，所以大者给 $A$。  
之后的每一次 $a\ne b$ 的情况，为了 使得两者的差最小，就把大者给 $B$。  

至此，已经完成了构造。  

最后的一步处理，有一个十分暴力的做法，那就是直接输出 $1$ 和两者的乘积。  
~~然而 FFT 也救不了这样的暴力。~~  
注意到题中数据范围保证了 $1\le c_i$，那么按照上述的策略，必然会有至少一个数的末尾为 $0$，这样我们就可以直接将这个数除以 $2$，另一个乘 $2$来得到答案。  

这种方法也很好证，还是根据数据范围，$A$ 和 $B$ 的开头一定是九或者八，乘二后会多出一位，除以二后位数不变，那么多出来的一位就保证了题中的要求。  
## 代码  

基于以上思路，不难写出两种代码，一种是不断的去对每一位操作，另一种是不断的去对每种数字操作。  

前者个人亲测略卡，建议写后者（参考出题人题解）。

---

## 作者：吴思诚 (赞：0)

## P8482 Number 题解
[题目传送门](https://www.luogu.com.cn/problem/P8482)

### 思路
首先大数应在高位，应从 $9$ 到 $0$ 遍历给定的数，交替选择两数中的一个把当前遍历到的数插入到它的末尾。根据等周长的正方形和长方形中正方形的面积大于长方形，可以得出两正数和一定，差的绝对值越小，则乘积最大，即 $a>0,b>0,a+b=c$，则另 $\left| a-b \right|$ 越小，则 $ab$ 越大。从高位分配值时，如果一种数的个数为奇数，则分配完后，会出现一个数比另一个数小了 $1$。因为高位已经小了，根据分配原则，因此接下来较小数永远小于较大数。而根据刚才证明的结论，所以接下来遍历到的较大数均优先分给较小数。而要求 $0 \sim 9$ 的数量不等于给定的数量，因为数据保证至少有 $1$ 个 $0$，可以另末尾为 $0$ 的一个数 $\times 2$，另一个 $\div 2$。又因为开头都是 $9,8$，所以一定有一个数位数增加 $1$，另外一个数位数不变，数字总个数增加了 $1$，一定满足要求。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[10],len1,len2,res1[10000001],res2[10000001];
int main(){
	for(int i=0;i<10;++i)cin>>c[i];
	bool f=0;
	int cnt=0;
	for(int i=9;~i;--i){
		for(int j=0;j<c[i];++j){
			++cnt;
			if(!f){
				if(cnt&1)res1[++len1]=i;
				else res2[++len2]=i;
			}
			else{
				if(cnt&1)res2[++len2]=i;
				else res1[++len1]=i;
			}
			if(!f&&len1==len2&&res1[len1]>res2[len2])
				f=1;
		}
	}
	int l1=1,l2=1;
	if(res1[len1]==0){
		for(int i=1;i<=len1;++i){
			if(res1[i]&1)res1[i+1]+=10;
			res1[i]/=2;
		}
		if(!res1[1])l1=2;
		for(int i=1;i<=len2;++i)res2[i]+=res2[i];
		for(int i=len2;i;--i)res2[i-1]+=res2[i]/10,res2[i]%=10;
		if(res2[0])l2=0;
	}
	else if(res2[len2]==0){
		for(int i=1;i<=len2;++i){
			if(res2[i]&1)res2[i+1]+=10;
			res2[i]/=2;
		}
		if(!res2[1])l2=2;
		for(int i=1;i<=len1;++i)res1[i]+=res1[i];
		for(int i=1;i<=len1;++i)res1[i+1]+=res1[i]/10,res1[i]%=10;
		if(res1[len1+1])l1=0;
	}
	for(int i=l1;i<=len1;++i)putchar(res1[i]+48);
	putchar('\n');
	for(int i=l2;i<=len2;++i)putchar(res2[i]+48);
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

T3, 时间浪费太多赛时没写出来。

~~其实是推出来了，只不过等号忘记考虑了 QwQ.~~

# 正文

直接上证明呗。考虑加入一位对乘积的影响。

设 $a'$ 为 $A$ 的前 $i - 1$ 位, $b'$ 为 $B$ 的前 $i - 1$ 位。

令 $a = 10a', b = 10b'$. 设 $c, d$ 为准备加入第 $i$ 位的数，考虑让 $c$ 加入 $A$, $d$ 加入 $B$ 的乘积大于等于交换加入后的乘积。

将结论列成不等式并变换：

$$
\begin{aligned} 
(a + c)(b + d) & \ge (a + d)(b + c) \\ 
ad + bc & \ge ac + bd \\ 
a(d - c) & \ge b(d - c) \\ 
(a - b)(d - c) & \ge 0 
\end{aligned}
$$
 
然后发现条件为 $a - b \ge 0, d - c \ge 0$.

因为每一位都是加上去的，所以 $a, b$ 的大小关系一旦确定就始终不变，那就钦定 $a > b$。

为了最优，就得使得 $d \ge c$. 结论就是：首位 A 大，其余位 B 大。

注意上面的 $a > b$ 没有考虑等号（会有以多个 $9$ 开始的情况）。

那不妨扩展一下结论：当第一次遇到不同时大的放在 $A$, 之后都放在 $B$.

这样就有 50pts, 再观察到 $c_i > 0$, 所以两数之积必为 $10$ 的倍数，也是 $2$ 的倍数，那就上一个高精乘除，能拿到 100pts.

复杂度 $\mathcal{O}(\sum_{i=0}^9{c_i})$, 可以通过。

--- 

另一种证明（太多人写这种辣）：

易证：当 $a + b$ 为定值时，则 $|a - b|$ 越小, $ab$ 越大。

那么不妨钦定 $a \ge b$. 那么根据贪心思想，第一位 $a$ 放大的，第二位 $a$ 就要放小的，使得差值最小，从而使得乘积最大。

那么就证明了结论。注意上述证明并没有考虑 $a, b$ 相同位上数相同的情况，所以要稍微改一下结论（同上，这里不再赘述）。

# 代码

C++ 代码（调试用）：

``` cpp
int c[15];
string str[2];

main()
{
    for(int i = 0; i <= 9; ++ i)
        cin >> c[i];

    int pos = 9;
    bool flag = false;
    while(pos >= 0)
    {
        int a, b;
        a = b = INT_MAX;
        while(!c[pos] && pos >= 0) -- pos;
        if(pos >= 0) a = pos, -- c[pos];
        while(!c[pos] && pos >= 0) -- pos;
        if(pos >= 0) b = pos, -- c[pos];
        if(a == INT_MAX && b == INT_MAX) break;
        if(b == INT_MAX) str[1] += a;
        else if(flag || a == b) str[0] += min(a, b), str[1] += max(a, b);
        else if(a != b && flag == false) flag = true, str[0] += max(a, b), str[1] += min(a, b);
    }

    int who = -1;
    if(str[0][str[0].length() - 1] == 0) who = 0;
    else                                 who = 1;

    for(int i = 0; i < str[who].length(); ++ i)
    {
        if(str[who][i] % 2 == 1) str[who][i + 1] += 10;
        str[who][i] /= 2;
    }

    reverse(str[!who].begin(), str[!who].end());
    int jw = 0;
    for(int i = 0; i <= str[!who].length(); ++ i)
    {
        str[!who][i] = str[!who][i] * 2 + jw;
        jw = str[!who][i] / 10;
        str[!who][i] %= 10;
    }
    
    if(str[!who][str[!who].length()])
        str[!who] += str[!who][str[!who].length()];

    reverse(str[!who].begin(), str[!who].end());
    for(int i = 0; i < str[0].length(); ++ i)
        str[0][i] += '0';

    for(int i = 0; i < str[1].length(); ++ i)
        str[1][i] += '0';

    cout << str[0] << endl << str[1] << endl;
}
```

流程（建议对着自己写）：

1 读入

2 从大到小寻找两个数并删去。

2.1 若找不到，转至 4.

2.2 若找到一个，放在数 $B$ 的末尾

2.3 若找到两个，

2.3.1 若两数相等，随意放。

2.3.2 若两数第一次不等，大的放数 $A$ 的末尾，小的放数 $B$ 的末尾。

2.3.3 若两数不是第一次不等，大的放数 $B$ 的末尾，小的放数 $A$ 的末尾。

3 转至 2.

4 令 $X$ 为两数中末尾为 $0$ 者, $Y$ 为剩者。

5 输出 $\dfrac{X}{2}, 2Y$.

6 结束。

# 后言

赛时白痴犯了错，下次要注意符号问题。

---

