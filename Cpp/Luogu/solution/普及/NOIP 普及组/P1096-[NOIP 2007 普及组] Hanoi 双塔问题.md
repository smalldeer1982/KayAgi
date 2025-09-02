# [NOIP 2007 普及组] Hanoi 双塔问题

## 题目描述

给定 A、B、C 三根足够长的细柱，在 A 柱上放有 $2n$ 个中间有孔的圆盘，共有 $n$ 个不同的尺寸，每个尺寸都有两个相同的圆盘，注意这两个圆盘是不加区分的（下图为 $n=3$ 的情形）。

![](https://cdn.luogu.com.cn/upload/image_hosting/mq2iklbv.png)

现要将这些圆盘移到 C 柱上，在移动过程中可放在 B 柱上暂存。要求：

1. 每次只能移动一个圆盘；
2. A、B、C 三根细柱上的圆盘都要保持上小下大的顺序。

任务：设 $A_n$ 为 $2n$ 个圆盘完成上述任务所需的最少移动次数，对于输入的 $n$，输出 $A_n$。



## 说明/提示

**限制**

- 对于 $50\%$ 的数据，$1  \le  n  \le  25$；
- 对于 $100\%$ 的数据，$1  \le  n  \le  200$。

**提示**

设法建立 $A_n$ 与 $A_{n-1}$ 的递推关系式。


## 样例 #1

### 输入

```
1```

### 输出

```
2```

## 样例 #2

### 输入

```
2```

### 输出

```
6```

# 题解

## 作者：违规用户名3(kd,e$A (赞：912)

哈喽，大家好，我又来了（虽然你可能不认识我），但我还是要把我的开场白说一说，好啦，言归正传。

今天，我来给大家讲一讲Hanoi 双塔问题这道题。

我们先来理解一下题意，题目是说，用最少的次数，把那三个圆柱给移到指定的C柱上，然后把次数输出（**要最少的**）

首先，容易得到a[n] = 2*b[n]（也即2个同样的圆盘一起移肯定最好）

然后，如图，当A柱上有n个盘时，先移n-1个到B，再移1个到C，再将B上的n-1个移到C

可以得到 **b[n] = 2*b[n-1] + 1**

下面我给大家分段来分析，首先

定义一个L，一个N;L表示每次去的方法次数，N表示有2N个圆盘。

然后在定义二个数组，分别表示A柱移到C柱的移动过程的储存，因为题目只确定了范围为200，所以我们也不需要定太大，两百足以搞定。

```
#include<cstdio>
using namespace std;
int l,n;
int a[201],b[201];
```
第二个部分，GJC函数，这个部分求的是移动过程是的一个操作，具体方法如下

```cpp
void gjc()
{
    int t=0;//求每次移完后剩下哟多少可以移动的。
    for (int j=200;j>0;j--)
     {
         l=b[j]*2+t;//每次加上b数组的得数乘上二，这里很关键，因为N等于2N个圆盘，所以要把B[J]乘上二，然后再加上剩下的多少才可求出一共有多少个可移动的。
         b[j]=l%10;//每次B【J】要进行递除，不然结果不变
         t=l/10;//每次t要进行递除，不然结果不变
     }
}
```
可能大家会发现两个函数基本相同，只有一个不同，那就是循环里的第一句话，大家可能会问这个程序段和上个程序段有什么不同，为什么要这样做，这样做作的目的是什么，下面我来给大家解答。

```cpp
void gjc()
{
    int t=0;
    for (int j=200;j>0;j--)
     {
         l=b[j]*2+t;
         b[j]=l%10;
         t=l/10;
     }
}
```
```cpp
void gjj()
{
    int t=0;
    for (int j=200;j>0;j--)
     {
         l=a[j]+b[j]+t;
         a[j]=l%10;
         t=l/10;
     }
}
```
这个的原因是：因为你移动的过程还可能会发生一些其他问题比如说![](https://cdn.luogu.com.cn/upload/image_hosting/m2xzpjst.png)

你要把第二个柱的大的，把它移到第三个柱，你就需要把哪两个给移走，所以说，你要有一个新的函数，来存储你的移动的过程，第三个的作用就是这些。

这一段，也就是主程序，解释在程序中，望见谅。

```cpp
int main()
{
    
    scanf("%d",&n);//输入圆盘的个数。
    b[200]=1;//把B数组的第二百位存为1，
    因为本身在一个位置，也要进行判断,否则
    答案会有误差
    for (int i=1;i<=n;
     {gjc();gjj();}//进入函数判断。
    int k=1;
    while (a[k]==0&&k<200)//判断运行次数，并进行累加。
     k++;
    for (int i=k;i<=200;i++)//从k次执行到200次
     printf("%d",a[i]);//输出数量。
    
}


```
下面进行程序展示，不再进行解释，望见谅。

```cpp
#include<cstdio>
using namespace std;
int l,n;
int a[201],b[201];
void gjc()
{
    int t=0;
    for (int j=200;j>0;j--)
     {
         l=b[j]*2+t;
         b[j]=l%10;
         t=l/10;
     }
}
void gjj()
{
    int t=0;
    for (int j=200;j>0;j--)
     {
         l=a[j]+b[j]+t;
         a[j]=l%10;
         t=l/10;
     }
}
int main()
{
    
    scanf("%d",&n);
    b[200]=1;
    for (int i=1;i<=n;i++)
     {gjc();gjj();}
    int k=1;
    while (a[k]==0&&k<200)
     k++;
    for (int i=k;i<=200;i++)
     printf("%d",a[i]);
     return 0;
}

```
写的这么长，就给过了吧，如果过了，麻烦拿拿你们皇帝搬的纤纤玉手帮我点点赞（爱你么么哒）。

---

## 作者：da32s1da (赞：180)

c++还有简单的做法

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    stringstream s;
    s.precision(0);
    s<<fixed<<pow(2.0L,n+1);  //将pow后存进去
    string a=s.str();    //放到a中，这里个位数只能是2,4,8,6
    a[a.length()-1]--;
    a[a.length()-1]--;   //减去2，不会影响上一行
    cout<<a<<endl;
    return 0;
}
```
太神奇了，这个只能做到2^16383,4ms


---

## 作者：fzj2007 (赞：42)

看到没有用压位存储高精的啊，来水一发————
//直接把模板扔上来了。。

现在，我讲一下位压存储

这个东西很（du）~~简~~（liu）~~单~~

有的时候，数字会大到连long long都不能承受的程度。这时，我们可以自己模拟大数的各种运算。
所谓压位存储，就是在高精度数内部采用10000进制（即每四位放到一个数中）进行存储。它与10进制（即一个数位对应一个数）相比速度要快一些。
高精度数内部也可以采用100000000进制，但是这样就不容易计算乘除法了。

### **(1) 定义**
编程时这样做——假设hp是高精度类型。

```cpp
const int MAX=1001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    //一下运算符根据需要定义哈
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
```
**### (2) 赋值和初始化**
```
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。
```
### **(3) 比较运算符**

小学时候学过怎么比较两个数的大小吧？~~现在，小学知识却从未过时……~~

```
// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
```
```
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
```


### **(4) 四则运算**

如果没学过竖式，或者忘了怎么用竖式算数，你就很悲剧了……

#### 1.   加法和减法
```
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
```
#### 2. 乘法
```
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
hp&hp::operator*=(const hp &b){return *this=*this*b;}
//同上 
```

#### 3. 二分优化的除法&&取余运算
使用二分优化，速度更快！
```
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
```


------------
# 这里是重点！认真听讲！~~（敲黑板）~~
## **(5) 输入/输出**
#### 输入，输出！
### 输入，输出！！
## 输入，输出！！！
~~重要的事情说三遍~~

```
ostream&operator<<(ostream &o,hp &n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
istream & operator>>(istream &in, hp &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
```

```
#include<bits/stdc++.h>
using namespace std;
const int MAX=1001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。

// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
// 注意：最高位的位置和位数要匹配。
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
//同上 
hp&hp::operator*=(const hp &b){return *this=*this*b;}
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
ostream&operator<<(ostream &o,hp &n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
istream & operator>>(istream &in, hp &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
inline long long read(){
	long long ans,flag=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-'){
		ch=getchar();
		flag=-1;
	} 
	while(ch<='9'&&ch>='0') ans=ans*10+ch-'0',ch=getchar();
	return ans*flag; 
}
hp n,x=1;
int main(){
	n=read();
	if(n==1){
	    cout<<2<<endl;
	    return 0;
	}
	for(hp i=1;i<=n;i+=1)
		x*=2;
	x-=1;
	x*=2;
	cout<<x<<endl;
	return 0;
}
```
写代码不易，点个赞再走啊！

---

## 作者：wyw666 (赞：36)

众所周知这是NOIP PJ 2007的第四题

如果时间不足以让你打高精度怎么办？

但是NOIP又不能提交Python的代码怎么办？

于是想到一种折中的办法，就是用Python打表

不难发现步数的递推式为$f(n)=2(2^{n+1}-1)$

于是乎我们可以这么写：

```python
a=2
b=[0]*201
b[1]=2
while a<=200:
    b[a]=b[a-1]*2+2
    a=a+1
for i in range(201):
    print("\"",b[i],"\",",sep='')
    #输出'"'是方便复制粘贴
    
```
然后我们把输出结果扔进c++里，一个~~很水~~的打表程序就出来了：
```cpp
#include<iostream>
#include<string>
using namespace std;
string str[201]={"0",
"2",
"6",
"14",
"30",
/*********
...
删掉免得太长QWQ 
...
*********/
"401734511064747568885490523085290650630550748445698208825342",
"803469022129495137770981046170581301261101496891396417650686",
"1606938044258990275541962092341162602522202993782792835301374",
"3213876088517980551083924184682325205044405987565585670602750"};
int n;
int main(){
	cin>>n;
	cout<<str[n]<<endl;
	return 0;
}
```


---

## 作者：Undefined_R (赞：20)

## 本蒟蒻第一次发题解，经验较少，不喜勿喷……  


------------

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先来分析下这个题，我们暂时先不考虑有2n个有孔圆盘，当作只有n个圆盘，我们用A'(n)来表示将n个圆盘全部从A柱移到C柱上的最少移动次数。于是，  

1.当n=1时，我们可以直接把这一个圆盘从A柱移到C柱上，就有A'(1)=1。**这样就完成了把1个圆盘从A柱移到C柱上的最简过程，共1次操作。**

2.当n=2时，我们可以先将最上方第一个圆盘移到B柱上**（可以理解成将n=1时的终点从C换成B，进行一次n=1时的操作）**，然后再将第二个圆盘移到C，最后把第一个圆盘从B柱移到C柱上**（可以理解成将n=1时的起点换成B，终点换成C，进行一次n=1时的操作），这样就完成了把2个圆盘从A柱移到C柱上的最简过程，共3次操作。其中第一次操作和最后一次操作可以理解为重复当n=1时的操作（只不过换了起点或者终点而已）**，就有A'(2)=A'(1)*2+1=3。

3.当n=3时，我们可以先将第一个圆盘移到C柱上，第二个圆盘移到B柱上，再把第一个圆盘移到B柱上**（至此，前三步可以理解为将n=2时的终点从C换成B，进行一次n=2时的操作）**，然后我们将第三个圆盘移到C柱上，紧接着又把第一个圆盘移到A柱，把第二个圆盘移到C柱，最后再把第一个圆盘移到C柱，**（这最后三步又能理解成将n=2时的起点换成B，终点换成C，进行一次n=2时的操作），这样就完成了把3个圆盘从A柱移到C柱上的最简过程，共7次操作。其中第前三次操作和后三次操作可以理解为重复n=2时的操作（只不过换了起点或者终点）**，就有A'(3)=A'(2)*2+1=(A'(1)×2+1)×2+1=7。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是，综上可以得出：**把n个圆盘从A柱移到C柱上的最简过程就是先做一轮移动n-1个圆盘的过程，借助C柱使前n-1个圆盘移动到B柱上，再将第n个圆盘移到C柱，最后再做一轮移动n-1个圆盘的过程，借助A柱使前n-1个圆盘从B柱移到C柱上，就可以推出递归公式A'(n)=A'(n-1)*2+1(n≥2）**，由于A'(1）=1，又可以推得![](https://cdn.luogu.com.cn/upload/pic/47207.png ),最后利用等比数列求和公式化简得**A'(n)=2^n-1**。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于题目所要求我们求的是2n个圆盘从A柱移到C柱，因此**A(n)=2A'(n)=2*(2^n-1)=2^(n+1)-2**。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;至此公式推导完毕。如果就开始这么写的话，只有50分-70分（用int存50分，用long long的话也只有70分），先贴出50分的代码：
```cpp
#include<cstdio>
#include<cmath>
int main(){
    int n;
    scanf("%d",&n);
    int ans=pow(2,n*1.0+1)-2;//注意这里n要*1.0转成浮点类型再加上1，因为pow函数传入的两个数必须是浮点类型
    printf("%d",ans);
    return 0;
}
```

------------
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;为什么只有50分呢？把光标移到后面那五个红的点一看，发现全是read 0，肯定是数据范围没考虑周全的问题。赶紧看看讨论/题解发现原来要使用高精度，于是我按照高精度的方法重新写了一遍。不过我和楼上的高精的思路不太一样，我定义了一个函数专门算乘法，然后循环n次计算乘法（因为是要算2^(n+1)嘛，乘当然只要乘n次），可能这样有点复杂吧：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
string mul(string a,string b){//这里读进来的是两个string类型，在函数内再转int数组
	int lena=a.size(),lenb=b.size(),x;//获取两个串长度
	int m[100000]={0},n[100000]={0},c[100000]={0};//m数组存a的每一位，n数组存b的每一位，c数组存结果的每一位，注意都必须初始化为0，即使声明在了函数外边，因为每调用一次这个函数就要刷新一次
	for(int i=1;i<=lena;i++)
		m[i]=a[lena-i]-48;//逆序存a的每一位
	for(int i=1;i<=lenb;i++)
		n[i]=b[lenb-i]-48;//逆序存b的每一位
	for(int i=1;i<=lenb;i++){
		x=0;//x是需要进到下一位的数，记得每进来一次循环就要清零一次
		for(int j=1;j<=lena;j++){
			c[i+j-1]+=m[j]*n[i]+x;//模拟竖式乘法过程，用m的第j位乘以n的第i位是因为默认m是第一个因数，n是第二个因数，因此j放在内循环，i放外循环。
			x=c[i+j-1]/10;//x的值刷新为要进到下一位的数
			c[i+j-1]%=10;//保证结果的每一位不超过10
		}
		c[i+lena]=x;//最后一次计算出来的x要记得保存到已算出的最高位的后面那一位
	}
	string k;//存结果
	bool p=0;//标记k是否为空串
	for(int i=lena+lenb;i>0;i--)//乘法的结果的位数最多不会超过两个因数的位数之和
		if(c[i]!=0){//不输出前导0
			for(int j=i;j>0;j--){
				k+=c[j]+48;//不要忘记加上0的ASCII值48
			}
			p=1;//标记k串已经存了值
			break;//不要丢了break
		}
	if(p==0)//如果k现在还是空串，说明结果为0（当然这一题乘法的结果不可能为0），就返回0
		return "0";
	return k;//否则就返回这个结果，此处不用else，因为如果满足p=0的话那就已经return掉这个函数了
}
int main(){
    int n;
    scanf("%d",&n);
    string ans="2";
    for(int i=1;i<=n;i++)//注意是乘n次，因为是要求2^(n+1)
    	ans=mul(ans,"2");
	ans[ans.size()-1]-=2;//这里不用考虑个位是否≥2，因为2的幂的个位不可能小于2
	cout<<ans;//注意这里如果使用的string的话最好别用printf输出，因为printf只能输出c语言的内置数据，而string的话是C++STL库里的，要使用printf的话只能使用传指针的方式输出，即printf("%s",ans.c_str());
	return 0;//不要忘记
}
```
当然，也用一般性的做法写了一遍（这个在时间上好像快很多）：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
string pow(int n){//如果使用了万能头或者cmath、math.h的库的话函数名不建议叫pow
	int len=1,x=0;//len表示得到的结果的位数，x表示要进到下一位的数
	int a[1000]={0};
	a[1]=1;//注意a[1]要赋成1，因为后面乘了n次
	for(int i=0;i<n;i++){
		for(int j=1;j<=len;j++){
			a[j]=a[j]*2+x;//乘以2再加上要进到这一位的数
			x=a[j]/10;
			a[j]%=10;//保证每一位大小不超过10
		if(x!=0&&j==len)//如果到了最后一位还有余数，就要再多开一位
			len++;
		}
	}
	string k;//储存结果
	for(int i=len;i>0;i--){
		k+=a[i]+48;//不要忘记加上0的ASCII值48
	}
	return k;
}
int main(){
    int n;
    scanf("%d",&n);
    string ans=pow(n+1);
    ans[ans.size()-1]-=2;
    //这里不用考虑个位是否≥2，因为2的幂的个位不可能小于2
    cout<<ans;
	return 0;
}
```

---

## 作者：2011hym (赞：10)

第一眼看到这个题目（汉诺塔），应该一眼能看出来是**递推**吧。

那让我们来模拟一下整体的过程。

* 在 $n=1$ 时，要挪两次（一眼解）；
* 在 $n>1$ 时，可以将问题进行拆分：

  1. 设 $A_n$ 为 $2n$ 个圆盘的最少挪动次数，
  2. 可知先挪 $2(n-1)$ 个圆盘至B柱需要 $A_{n-1}$  次，
  3. 将剩下的两个扔到C柱需要 $2$ 次，
  4. 将B柱的盘挪过来又需要 $A_{n-1}$ 次。

所以，  
公式为： 
$$
A_n=2\times A_{n-1}+2
$$

**然鹅，**

只有 70pts。

Why?

**不开 long long 见祖宗，开了 long long 照样见祖宗。**

看数据范围，发现 $A_n$ 有可能到达 $2^{200}$，所以我们还需要高精度。

这就不用再写了吧，直接上代码（~~其实我想用 Python 糊弄一下的~~）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string add(string a,string b){//高精加，对照公式里的加法。
    string res;
    int flag=0;
    int i=a.size()-1,j=b.size()-1;
    while(i>=0||j>=0||flag){
        int sum=flag;
        if(i>=0)sum+=a[i--]-'0';
        if(j>=0)sum+=b[j--]-'0';
        res.push_back(sum%10+'0');
        flag=sum/10;
    }
    reverse(res.begin(),res.end());
    return res;
}
string cheng(string a){//高精乘同理。
    string res;
    int flag=0;
    for(int i=a.size()-1;i>=0;i--){
        int product=(a[i]-'0')*2+flag;
        res.push_back(product%10+'0');
        flag=product/10;
    }
    if(flag)res.push_back(flag+'0');
    reverse(res.begin(),res.end());
    return res;
}
int n;
signed main(){
    cin>>n;
    string A="2"; 
    for(int i=2;i<=n;i++){
        A=cheng(A);
        A=add(A,"2");
    }
    cout<<A;
    return 0;
}
```

Good!

---

## 作者：yedalong (赞：4)

## 思路

看到题目，很容易想到一次移两个是最优解，因此后文的递推都是讨论只有 $n$ 个圆盘的情况。\
我们设移动 $n-1$ 个圆盘需要 $k_{n-1}$ 步，那么我们该怎么移动 $n$ 个圆盘呢？首先先将 $n-1$ 个圆盘移动至 B 柱，花费了 $k_{n-1}$ 步，再将剩下的一个移动至 C 柱，花费了 $1$ 步，最后只要将 B 柱上的 $n-1$ 个圆盘移动到 C 柱就好了，这里同样也是花费 $k_{n-1}$ 步，这时候我们又发现，$k_n$ 其实就等于 $2k_{n-1}+1$。\
我们再将这个递推式化简，得到移动 $n$ 个圆盘需要 $2^n-1$，那么移动 $2n$ 个圆盘就是 $2(2^n-1)$ 了，去掉括号变为 $2^{n+1}-2$，最后用高精度即可算出。\
这里高精度就不多说了，不懂的同学可以去学习一下高精度。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans[205],now=1;
int main(){
    cin>>n;
    ans[1]=1;
    n++;
    while(n--){
        for(int i = now;i>=1;i--) ans[i]+=ans[i];
        if(ans[now]>9) now++;
        for(int i = now-1;i>=1;i--) if(ans[i]>9) ans[i]%=10,ans[i+1]++;
    }
    ans[1]-=2;
    for(int i = 1;i<=now;i++){
        if(ans[i]<0) ans[i]+=10,ans[i+1]--;
        else break;
    }
    for(int i = now;i>=1;i--) cout<<ans[i];
    return 0;
}
```

---

## 作者：IMGCsir (赞：4)

## 题目描述
本题就是一般汉诺塔的升级变式（所有圆盘变为 $2$ 个）。其中，每次只能移动一个圆盘，圆盘要保持下面的比上面的大。
## 前置知识
高精度和递推
## 代码结构与功能
### 1. 初始化部分

```cpp
   int a[1000], c[1000], n;
   int main(){
       cin >> n;
       a[1] = 2, c[1] = 2; // 初始赋值, c[1]=2用于特判1
       int len = 1;

```
 $a$ 和 $c$ 是两个数组，用于存储高精度计算的结果。  
 $n$ 是从用户输入读取的整数，表示 $2$ 的 $n$ 次方。  
 $a[1]$ 和 $c[1]$ 初始化为 $2$ ，表示 $2$ 的 $0$ 次方和 $1$ 次方的结果。  
 $len$ 用于记录当前结果的位数，初始为 $1$ 。
### 2. 递推计算部分

```cpp
   for(int k = 2; k <= n; k++){ // 递推求出后面的第n项 数据范围很大
       memset(c, 0, sizeof(c));
       c[1] = 2; // 每次结果的个位先加上2
       // 再乘2
       for(int i = 1; i <= len; i++){ // 高精度部分，将a数组乘2存入c数组
           c[i] += a[i] * 2;
           c[i + 1] = c[i] / 10;
           c[i] %= 10;
       }
       memcpy(a, c, sizeof(c)); // 本次结果是下一次的乘数, memcpy就是复制函数
       len++;
   }

```
使用一个循环从 $2$ 计算到 $n$ 次方。  
每次循环中，首先将数组 $c$ 清零，节省空间。  
然后将 $c[1]$ 初始化为 $2$ ，表示当前结果的个位数。  
接下来，通过一个内层循环将数组 $a$ 中的每一位乘以 $2$ ，并处理进位。  
最后，将数组 $c$ 的内容复制到数组a中，作为下一次计算的基础。  
 $len$ 记录当前结果的位数，并在每次循环后增加。
### 3. 去除前导零

```cpp
   while(c[len] == 0 && len > 1) len--; // 去除前导零

```
在计算完成后，可能会有多余的前导零，通过这个循环去除这些前导零。
### 输出结果

```cpp
   for(int i = len; i >= 1; i--) cout << c[i]; // 输出
   return 0; // 完结撒花

```
最后，从最高位到最低位输出数组 $c$ 中的每一位，得到最终结果。
## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000],c[1000],n;
int main(){
    cin>>n;
    a[1]=2,c[1]=2;//初始赋值,c[1]=2用于特判1
    int len=1;
    for(int k=2;k<=n;k++){//递推求出后面的第n项 数据范围很大
        memset(c,0,sizeof(c));
        c[1]=2;//每次结果的个位先加上2
        //再乘2
        for(int i=1;i<=len;i++){//高精度部分，将a数组乘2存入c数组
            c[i]+=a[i]*2;
            c[i+1]=c[i]/10;
            c[i]%=10;
        }
        memcpy(a,c,sizeof(c));//本次结果是下一次的乘数,memcpy就是复制函数
        len++;
    }
    while(c[len]==0 && len>1)len--;//去除前导零
    for(int i=len;i>=1;i--)cout<<c[i];//输出
    return 0;//完结撒花
}
```
## 附加代码
```cpp
#include<bits/stdc++.h>
using namespace std;
void hnt(int n,char a,char c,char b){
    if(n==1){
        cout<<a<<"->"<<n<<"->"<<b<<endl;
    }else{
        hnt(n-1,a,b,c);
        cout<<a<<"->"<<n<<"->"<<b<<endl;
        hnt(n-1,c,a,b);
    }
}                                                               
int main (){
	int n;
    char a,b,c;
    cin>>n>>a>>b>>c;
	hnt(n,a,c,b); 	
	return 0;
}
```
完整汉诺塔，先输入 $N$ 代表盘的个数，然后输入三个字符，代表塔的名称，输出若干行，先输出原塔的名称，再输出盘的编号，最后输出移动后塔的名称。

---

## 作者：GLr137 (赞：3)

难度大约为橙。

众所周知，汉诺塔问题的公式是 $ 2 ^ n - 1 $，而汉诺双塔问题也一样，相当于汉诺塔每次移动两个，不影响其他操作。所以答案就是 $ 2 (2 ^ n - 1)  $。化简：$ 2 ^ n \times 2 - 2 $，即 $ 2 ^ {(n + 1)} - 2 $。

但是本题数据很大，所以我们可以想到高精度乘法。什么？~~抱歉，我从来不用高精度乘法……~~ 不过我们可以想到一个巧妙的办法，就是 $ 2 ^ x $ 相当于 $ x $ 个 $ 2 $ 相乘，所以我们可以把每一次乘 $ 2 $ 的操作改成它的本质——相加本身。所以最终我们计算 $ n + 1 $ 次，每一次都让答案变成答案加答案的值，由于 $ 2 ^ x $ 的末尾只能是 $ 2 $、$ 4 $、$ 6 $、$ 8 $，所以我们直接将答案的最后一位减 $ 2 $，再输出即可。这使得原本复杂的高精度乘法可以变成高精度加法了。

### Code

```cpp
# include <iostream>
using namespace std;
string ans = "1";
int x, y, z, k1[1000005], k2[1000005], k3[2000005];
string hs (string s1, string s2){
    y = 0;
    string s3 = "";
    for (int i = 0; i < s1.size(); i++){
        k1[i] = s1[s1.size() - i - 1] - 48;
    }
    for (int i = 0; i < s2.size(); i++){
        k2[i] = s2[s2.size() - i - 1] - 48;
    }
    z = max(s1.size(), s2.size());
    for (int i = 0; i < z; i++){
        k3[i] = k1[i] + k2[i] + y;
        y = k3[i] / 10;
        k3[i] %= 10;
    }
    if (y == 1){
        s3 += '1';
    }
    for (int i = z - 1; i >= 0; i--){
        s3 += (k3[i] + 48);
    }
    return s3;
}
int main (){
    cin >> x;
    for (int i = 1; i <= x + 1; i++){
        ans = hs(ans, ans);
    }
    ans[ans.size() - 1] -= 2;
    cout << ans;
    return 0;
}
```

[记录](https://www.luogu.com.cn/record/201277802)

---

## 作者：ZZA000HAH (赞：3)

题目提示用递推，这理所当然，这道题的关键就在于找到递推式。那我们分析一下这道题，我们知道 $a_{0}=0$，$a_{1}=2$，$a_{2}=6$，$a_{3}=14$，那我们就不难发现 $a_{i}=2\times a_{i-1}+2$ 这个递推表达式。当然这是正确的，那我们用逻辑分析来推理一下：

上述式子是我们以 $2n$ 的角度来看的，当然两个相同大小的塔肯定是被连续移动的，可以看作整体，只不过在移动的数量上是 $2$ 倍而已。

当 $n=1$ 时，移动方式（题目所说求最小移动步数，这个移动步数就是正常移动的步数，不允许重复移动而已）为直接将两个塔移动到 $C$ 柱，步数为 $2$；

当 $n=2$ 时，移动方式为先将两个小塔移动到 $B$ 柱，再将两个大塔移动到 $C$ 柱，最后将两个小塔移动到 $C$ 柱，步数为 $6$；

我们发现，在 $n$ 时，除去相比 $n-1$ 时多的那两个塔，其余的塔在那两个塔不动前的最终状态为全部放在 $B$ 柱上，然而这些塔最终还要全部转移到 $C$ 柱上，故 $2\times a_{i-1}$，再加上相比 $n-1$ 时多的那两个塔移动所需的步数，则 $a_{i}=2\times a_{i-1}+2$。

当然这个题还需要高精度，这里不在过多阐述。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int NUM=1e4+10;
int a[NUM+10];
//a[i]=a[i-1]*2+1(2)--n/(2n)
int main()
{
	int n,fl=0;
	scanf("%d",&n);
	for (int i=0; i<n; i++)
	{
		for (int j=NUM; j>=0; j--) a[j]*=2;//递推步骤(1)
		for (int j=NUM; j>=0; j--)
			if (a[j+1]>=10)
			{
				a[j+1]-=10;
				a[j]++;
			}
		a[NUM]+=2;//递推步骤(2)
		a[NUM-2]+=a[NUM]/100;
		a[NUM]%=100;
		a[NUM-1]+=a[NUM]/10;
		a[NUM]%=10;//高精度
	}
	for (int i=0; i<=NUM; i++)
	{
		if (a[i]!=0) fl=1;//从第一个不为0的数开始输出
		if (fl==1) printf("%d",a[i]);
	}
	return 0;
}
```
如果用Python就简单得多了。
# Python Code

```python
a=[]
a.append(0)
n=int(input())
for i in range(1,n+1):
        a.append(a[i-1]*2+2)
print(a[n])
```
## End

---

## 作者：Haohao123coding (赞：1)

[【原题】](https://www.luogu.com.cn/problem/P1096)
[【代码剪贴板】](https://www.luogu.com.cn/paste/xdai1tik)
## 主要题意
本题就是一般汉诺塔的翻倍版本（所有圆盘变为 $2$ 个）。其中，每次只能移动一个圆盘，圆盘要保持下面的比上面的大。
## 题目分析
不难发现，两个相同大小的圆盘应一起移动，才能使总次数尽可能小。

我们可以用递推算法解决本题，递推需要初始条件和递推式。题目提示我们可以设法建立 $A_n$ 与 $A_{n-1}$ 的递推关系式。所以初始条件应为 $A_1$。很明显，$A_1 = 2$，也就是把两个圆盘从 A 移到 C。

而 $n = 2$ 时，我们可以：
1. 先把两个小的圆盘从 A 移到 B，花费 $A_1$ 步；
2. 再把下面两个最大的圆盘从 A 移到 C，花费 $2$ 步；
3. 最后把两个小的圆盘从 B 移到 C，花费 $A_1$ 步；

共计 $2 \times A_1 + 2$ 步。因此，$A_n = 2 \times A_{n-1} + 2$。

## 代码实现
我们可以用以上思路编写出以下程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n, a[222];
	cin >> n;
	a[1] = 2;
	for(int i = 2; i <= n; i++){
		a[i] = a[i-1] * 2 + 2; // 递推式
	}
	cout << a[n];
}
```
（此代码 $70$ 分）

但是，如果我们分析一下数据范围，$2^{200}$ 很大（本题中 $1 \le n \le 200$），而 `long long` 最大只有 $2^{63} - 1$。因此需要使用高精度，大概可以把数组开到 $100$ 项。

代码主要部分：

```cpp
a[1][0] = 2; len[1] = 1; // 设置递推初始条件
for(int i = 2; i <= n; i++){
  a[i][0] += 2;          // 先给个位加 2
  len[i] = len[i-1];     // 继承上一个数的位数
  for(int j = 0; j < len[i-1]; j++){ // 高精度，反着存数
    a[i][j] += 2 * a[i-1][j];
    if(j == len[i] - 1 && a[i][j] >= 10){
      len[i]++;    // 进位可能导致位数增加，需要判断
    }              // 本题只是乘 2 再加 2，无需多次进位，因此只判断一次
    a[i][j+1] += a[i][j] / 10;
    a[i][j] %= 10; // 进位处理
  }
}
```

（全部代码见剪贴板中，此代码 $100$ 分。）

---

## 作者：mairuisheng (赞：1)

[P1096 [NOIP2007 普及组] Hanoi 双塔问题](https://www.luogu.com.cn/problem/P1096)

算法：数学，高精度

分析：经过反复推敲，得到单塔 $A_n=2^n-1$，但由于是双塔，所以又得到 $A_n=2(2^n-1)=2^{n+1}-2$。但看到题目范围 $2^{100}$ 会爆，所以要用高精度。

单塔公式解析：

先把 $n\le4$ 的单塔情况列出来看看：
$$1,3,7,15$$
好像很难发现规律，但我们把它们加个一看看：
$$2,4,8,16$$
这不就是：
$$2^1,2^2,2^3,2^4$$
最后再把加上的一减去得到：
$$A_n=2^n-1$$

过程：
假如每次 $A$ 柱有 $i$ 个圆盘，每次将 $i-1$ 个圆盘移到 $B$ 柱，将 $A$ 柱剩下的一个圆盘移到 $C$ 柱，再把 $B$ 柱的 $i-1$ 个圆盘移回 $A$ 柱，这时 $A$ 柱还有 $i-1$ 个圆盘。后面就重复此过程。所以是 $A_n=2\times A_{n-1}+1$，（即两次移动 $i-1$ 个圆盘，一次移动第 $i$ 个圆盘），又知 $A_1=1$，所以 $A_n=2^n-1$。

代码：

```cpp
#include<cstdio>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char s;
	s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')f=-f;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<3)+(x<<1)+(s-48);
		s=getchar();
	}
	return x*f;
}
int n;
int len;
int ans[201];
void times(int n)
{
	if(n==0)return;
	int i;
	bool fl=false;
	for(i=1;i<=len;++i)ans[i]<<=1;
	for(i=1;i<=len;++i)
	{
		if(ans[i]>9)
		{
			if(i==len)fl=true;
			ans[i+1]+=ans[i]/10;
			ans[i]%=10;
		}
	}
	if(fl)++len;
	times(n-1);
}
int main()
{
	int i;
	n=read();
	ans[1]=1;
	len=1;
	times(n+1);
	ans[1]-=2;
	for(i=len;i>0;--i)printf("%d",ans[i]);
	return 0;
}
```

---

## 作者：GSQ0829 (赞：1)

### 思路：
这题分享 C++ 里很简单的字符串做法。

首先，我们可以算出递推式 $n = 2(2^{n+1} - 1)$。

那么，如果按照这个递推式，你能拿到不错的 $50$ 分。
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	cin >> n;
	n--;
	printf("%d\n", 2 * ((int)pow(2, n + 1) - 1));
	return 0;
}
```
作为第四题能拿到这样的成绩其实也不错了，但是想拿满分也很简单。

只要用到 C++ 里的字符串库就可以了。

```cpp
s << fixed << pow(2.0L, n + 1)
```
这一句，是根据递推式 $n = 2(2^{n+1} - 1)$ 来写的。

```cpp
a = s.str()
```
这一句，是将算出的 $s$ 存进 $a$ 中，才得输出。

```cpp
a[a.length() - 1] -= 2;
```
这一句是把相对应的汉诺塔个数的那一个，减掉多余的 $2$，这样才能对应我们的递推式。


---
### code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string a;
stringstream s; 

int main() {
	cin >> n;
	s.precision(0);
	s << fixed << pow(2.0L, n + 1);
	a = s.str();
	a[a.length() - 1] -= 2;
	cout << a << endl;
	return 0;
}
```

---

## 作者：qhr2023 (赞：1)

## solution

本题考察高精度和递推。

经典的汉诺塔问题。若三个柱子分别是 $A,B,C$，假设现在有 $n$ 个盘子在 $A$ 柱，要把它们移到 $C$ 柱上，就需要先把上面 $n-1$ 个盘子移到 $B$ 柱上，再把第 $n$ 个盘子移到 $C$ 柱，最后把 $n-1$ 个盘子移到 $C$，对于这 $n-1$ 个盘子是怎么移的，又是一个子问题。

所以这是个递归的过程，设 $H_i$ 表示 $i$ 个盘子的移动次数，容易得到递推式 $H_i=H_{i-1}+1+H_{i-1}$，即 $H_i=2 \times H_{i-1}+1$。

若只有一个盘子则只需移动一次，即 $H_1=1$，那么 $H_2=3$，$H_3=7$，所以得到通项公式 $H_i=2^i-1$。

现在每种盘子都有两个，所以操作次数翻倍，即 $H_i=2^{i+1}-2$。实现需要高精乘低精及高精减低精。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> mul(vector<int> a){
	vector<int> c;
	for(int i=0, t=0; i<a.size()||t; i++){
		if(i<a.size()) t+=a[i]*2;
		c.push_back(t%10), t/=10;
	} 
	return c;
}
int main(){
	long long n; cin >> n; 
	vector<int> a; a.push_back(1); n++;
	while(n--) a=mul(a); 
	for(int i=0; i<a.size()-1; i++){
		if(a[i]<0) a[i]=0, a[i+1]--;
		if(a[i]>1){a[i]-=2; break;}
		else{a[i]+=8; a[i+1]--;}
	}
	for(int i=a.size()-1; i>=0; i--) 
        cout << a[i];
	return 0; 
}
```

---

## 作者：cwxcplh (赞：0)

很简单的一道题，我就简单说一下。

题目中的汉诺塔是双塔，所以我第一反应是找规律。

结果规律还没找出来，我就发现了一个事：每次按照汉诺塔的顺序移盘子，大小相同的两个盘要算两次。所以我就有了一个很简单的思路：把两个盘看做一个盘，然后用经典的汉诺塔方法去解开。

题目中要求求方案数，想必大家都知道 $n$ 个盘的汉诺塔的方案数是 $2^n-1$，而在这个问题中，一个盘的移动算两次，所以只需要把方案数乘以 $2$ 就行了。

所以最终的答案就是 $2^{n+1}-2$。注意：数很大，要使用高精度来计算。

[提交记录，完美 AC](https://www.luogu.com.cn/record/201385975)

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct bign{
	int len,x[206];
	bign();
};
bign::bign()
{
	memset(x,0,sizeof(x));
	len=0;
}
int n;
bign fix(bign a)
{
	for(int i=1;i<a.len;i++)
	{
		if(a.x[i]>9)
		{
			a.x[i+1]+=a.x[i]/10;
			a.x[i]%=10;
		}
		if(a.x[i]<0)
		{
			a.x[i+1]--;
			a.x[i]+=10;
		}
	}
	while(a.x[a.len]>9)
	{
		a.x[a.len+1]+=a.x[a.len]/10;
		a.x[a.len]%=10;
		a.len++;
	}
	while(a.x[a.len]==0&&a.len>1)
	{
		a.len--;
	}
	return a;
}
bign operator * (bign a,int b)
{
	for(int i=1;i<=a.len;i++)
	{
		a.x[i]*=b;
	}
	return fix(a);
}
bign operator - (bign a,int b)
{
	a.x[1]-=b;
	return fix(a);
}
signed main()
{
	bign a;//高精度
	a.len=1;
	a.x[1]=1;
	cin>>n;
	for(int i=1;i<=n+1;i++)//公式前半部分
	{
		a=a*2;
	}
	a=a-2;//后半部分
	for(int i=a.len;i>=1;i--)
	{
		cout<<a.x[i];
	}
	return 0;
}
```

---

## 作者：3_14 (赞：0)

[**题目传送门**](https://www.luogu.com.cn/problem/P1096)

# 思路

这是一个汉诺塔问题的变式。在标准的汉诺塔问题中，我们有 $n$ 个不同大小的圆盘，需要将它们从 A 柱移动到 C 柱，借助 B 柱作为辅助柱。每次只能移动一个圆盘，且任何时候都不能将较大的圆盘放在较小的圆盘上。

在本题中，我们有 $2\times n$ 个圆盘，其中每个尺寸的圆盘有两个，且这两个圆盘是不可区分的。我们需要计算将 $2\times n$ 个圆盘从 A 柱移动到 C 柱所需的最少移动次数。

对于标准的汉诺塔问题，移动 $n$ 个圆盘的最少移动次数为 $2^n - 1$。对于本题，由于每个尺寸的圆盘有两个，且它们是不可区分的，因此移动 $2\times n$ 个圆盘的最少移动次数可以推导如下：

1.  **移动 $2\times n$ 个圆盘的步骤**：
    *   首先将 $2\times n-2$ 个圆盘从 A 柱移动到 B 柱，需要 $A_{n-1}$ 次移动。
    *   然后将剩下的两个相同尺寸的圆盘从 A 柱移动到 C 柱，需要 $2$ 次移动。
    *   最后将 $2\times n-2$ 个圆盘从 B 柱移动到 C 柱，需要 $A_{n-1}$ 次移动。
2.  **递推公式**：
    *   $A_n = 2 \times A_{n-1} + 2$
3.  **初始条件**：
    *   当 $n = 1$ 时，$A_1 = 2$（因为有两个相同的圆盘，需要移动两次）。

# 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
string add(string a, string b) {// 高精加
    string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }
    reverse(result.begin(), result.end());
    return result;
}
string mb(string a) {// 高精度乘法（乘以 2）
    string result;
    int carry = 0;
    for (int i = a.length() - 1; i >= 0; --i) {
        int product = (a[i] - '0') * 2 + carry;
        carry = product / 10;
        result.push_back((product % 10) + '0');
    }
    if (carry) result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return result;
}
// 计算 A_n
string hnt(int n) {
    if (n == 1) return "2";
    return add(mb(hnt(n - 1)), "2");
}
int main() {
    int n;
    cin >> n;
    cout << hnt(n) << endl;
    return 0;
}
```

[**AC 记录**](https://www.luogu.com.cn/record/200204122)

---

## 作者：Jerry_zpl (赞：0)

本题其实就是从汉诺塔问题的基础上改了一点，其实本质还是不变的。我们先回顾汉诺塔问题的几个细节：
- 每次只能移动一个圆盘；
- 三根细柱上的圆盘都要保持上小下大的顺序。    
本题在模拟时会有 $2n$ 次操作和圆盘之间呼唤位置的操作，因为我们最终的圆盘时要保持上小下大的顺序，如果不符合这个条件，就需要借助别的柱子来调整圆盘。那么我们要求的答案就是 $2^{n+1}-2$。为啥是这个答案捏？因为每一次操作都会重复两次上一次操作，还会有最大的和次大圆盘借助其它两个柱子交换位置的操作。需要注意本题如果用 c++ 做会存在精度问题，但是 Python 自带高精，所以不用高精模拟。

```python
a=int(input())
print(2**(a+1)-2)
```

---

## 作者：Eason0324 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1096)

## 思路
这题说要找规律，我们先来前几个数看看。
$$2,6,14,30$$
还是没有规律，除以 $2$ 看看。
$$1,3,7,15$$
此时应该能看出来，第 $i$ 项是 $2^{i+1}-2$。
## 证明
我们如何证明这件事呢？

首先，当 $n$ 为 $1$ 时，显然成立。

我们设当 $n$ 为 $k$ 时成立，当 $n$ 为 $k+1$ 时，我们会重复两遍 $n$ 为 $k$ 时的操作，以及底下两个圆盘的换位，则答案为 $2 \times (2^{k+1}-2)+2$ 也就是 $2^{k+2}-2$。

## 代码
注意到数据范围，用 Python 即可。

```python
a=int(input())
print((2**a-1)*2)
```

---

## 作者：judgejudge (赞：0)

# 数学递推+高精度
对于这种数论题目，我们可以推一下规律。
| 1 | 2 | 2^(1+1)-2 |
| -----------: | -----------: | -----------: |
| 2 | 6 | 2^(2+1)-2 |
|  3| 14 | 2^(3+1)-2 |
| n | 2^(n+1)-2 |2^(n+1)-2  |
所以总结出来规律：

### 对于每一个输入的n，输出2^（n+1)-2。

但我们一看数据范围：n<=200

所以用**高精度算法**。

我的思路是把高精度算法分解成两大块:

1. 2的n次方（用循环，每次乘2）
1. -2（高精度减法）



------------
### 一、2的n次方
```cpp
inline void f1(ll x){
	register int i;
	ll k=0;
	for(i=1;i<=l+1;i++){
		a[i]=(a[i]*2)+k;//先把每一位上全部乘2
		if(a[i]>=10){//判断位数超出10的情况
			k=(a[i]/10);
			a[i]%=10;
		}
		else k=0;//如果没有超出，就不用在下一位++
	}
	if(a[l+1]>0)l++;//判断最高位是否有进位
}
```


------------
### 二、高精度减法
```cpp
inline void f2(){
	ll p=1;
	if(a[p]>=2){//如果可以直接减2
		a[p]=a[p]-(1<<1);//听说二进制会快一点
		return;
	}
	else{//不可以直接减
		a[p]=a[p]+(1<<3);//往前面一位推
		p++;
		while(a[p]==0)a[p]=9,p++;//判断是否可以向前一位借1
		a[p]--;
		if(a[l]==0)l--;//如果前一位被减了，那么就往后挪一位
	}
}
```
贴一下main函数：
```cpp
int main(){
	register int i;
	n=read();
	a[1]=1;
	for(i=1;i<=n+1;i++)//2的n次方
	f1(2);
	f2();//高精度减法
	for(i=l;i>=1;i--)printf("%lld",a[i]);
	printf("\n");//最好换行
	return 0;
}
```




---

## 作者：J_coder (赞：0)

- 经典JAVA大数类问题。
- 众所周知汉诺塔问题的通解为 an = (2^n) - 1。
- 那么换成双塔当然就是 2 * an。
- 很显然 200次乘2操作在c++中要写的东西会多一些。
- 但是JAVA提供了一个封装类来帮助我们完成高精度的运算。

```java
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		BigInteger ans = new BigInteger("1");
		BigInteger two = new BigInteger("2");
		BigInteger one = new BigInteger("1");
		int n = sc.nextInt();
		for(int i = 0;i < n;i ++){
			ans = ans.multiply(two);
		}
		ans = ans.subtract(one);
		ans = ans.multiply(two);
		System.out.println(ans);
	}	
}

```

---

