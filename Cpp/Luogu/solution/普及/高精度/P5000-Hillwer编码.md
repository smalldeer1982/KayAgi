# Hillwer编码

## 题目背景

在Z国的高科技研究中心，科研人员使用的都是最“先进”的Hillwer编码（毕竟这里可是国家机密库，储存着最重要的机密资料~~QwQ）。

## 题目描述

Z国的科技十分发达，一直是各国觊觎的目标，Y国就是其中之一。经过Y国黑客夜以继日的奋斗，终于获得了Z国**Hillwer**编码的转换方式，并且截获了n条原码。 BUT（总是有那么多但是~），Y国的黑客们呕心沥血研究**Hillwer**，都累得趴下了……所以，转换**Hillwer**编码的任务他们就无法完成。

Y国元首听说在遥远的东方国度，有一群才华横溢的少年——就是坐在电脑前的你们！元首希望你能够帮助Y国转换编码，他将赠予你**NOIP_AK荣耀桂冠**！

**Hillwer**编码的转换规则如下： 对于每一条原码$ S $，保证仅由26个大写字母组成。将每个字母后移R位，得到中转码$ S1 $（当$ S $=‘XYZ’,R=2时，$ S1 $=‘ZAB’。即变成当前字母后$ R $个字母，超过 ‘Z’则从‘A’开始）。接着，将中转码进行“符转数”操作，将$ S1 $每一位的ACS码（即ASCLL码）相乘，得到数串$ Q $。转换后的编码即为$ Q $。

元首为了检查你是不是偷懒，还要求你把中转码$ S1 $也输出。

## 说明/提示

对于 $ 30\% $ 的数据，$ 1 \leq n \leq 10 ,1 \leq R \leq 10 $；

对于 $ 50\% $ 的数据，$ 1 \leq n \leq 500 ,1 \leq R \leq 10^3 $；

对于 $ 100\% $ 的数据，$ 1 \leq n \leq 500 ,1 \leq R \leq 10^5 $。

另外保证 原码长度小于600

## 样例 #1

### 输入

```
2 6
HELLOWORLD
LETUSGO```

### 输出

```
NKRRUCUXRJ
10167740864629920000
RKZAYMU
20957073637500
```

# 题解

## 作者：Kevin_Wa (赞：11)

在此再发布上毒瘤验题人的程序，不知道为什么跑的比标算快。高精+字符串模拟是最裸的提示了。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define N 1111111
#define reg register
using namespace std;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        x=x*10+ch-'0';ch=getchar();
    }
    return x*f;
}
int n,m;
string s;
int f[N];
void times(int p){ 简单的高精
    int x=0;
    for (int i=1;i<=f[0];++i){
        f[i]=f[i]*p+x;
        x=f[i]/10;
        f[i]=f[i]%10;	
    }
    while (x>0){
        f[0]++;
        f[f[0]]=x%10;
        x=x/10;
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i){
        cin>>s;  //读入
        f[0]=1;f[1]=1;
        for (int j=0;j<s.size();++j){
            s[j]=(s[j]+m-65)%26+65;//字符串处理
            times(s[j]);//高精
        }
        cout<<s<<endl;
        for (int j=f[0];j>=1;--j) printf("%d",f[j]);
        printf("\n");
    } 
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：Kevin_Wa (赞：10)

## 出题人的题解
#### 真的不想说什么，在比赛本题为颂纷题，如果这都送不进的话，建议再学习一下[高精度模板](https://www.luogu.org/problemnew/show/P1009)。可在比赛中，还是有人打不出高精。现在普及选手可以用来加深高精的印象，但为何此题的难度是提高+/省选-。难道是错误率高导致的???

### 简单题意：

将字符串移位，在将其ASCLL码相乘（ord（pascal），（int）（C++））高精。

### 部分分获取：

打暴力30分。（开long long(C++) int64(pascal)）

高精满分

### 高精

不多说，实在不行自己背板去吧。我也帮不了你。

### 总结

很好奇这个标签是怎么计算的。但我为洛谷的P5000感到高兴，为大家的支持高兴。

### 代码（跑得慢，作者懒得打更快的）
```pascal
var n,r,i,j,k,t,j1,lb,len,x,y:longint;s:ansistring;
a,b,c:array[0..10000] of longint;
begin
  assign(input,'hillwer.in');reset(input);
  assign(output,'hillwer.out');rewrite(output);
  readln(n,r);r:=r mod 26;
  for i:=1 to n do
  begin
    readln(s);
    for j:=1 to length(s) do
    begin
      for k:=1 to r do//这里可以优化直接((ord(s[j])-64)+r-1)mod 26+1
       if s[j]='Z' then s[j]:='A' else s[j]:=succ(s[j]);
      write(s[j]);
    end;writeln;
    fillchar(a,sizeof(a),0);
    lb:=2;len:=1;a[1]:=1;
    for j:=1 to length(s) do//高精乘
    begin
      y:=ord(s[j]);
      b[1]:=y mod 10;
      b[2]:=y div 10;
      fillchar(c,sizeof(c),0);
      for k:=1 to len do
      begin
        x:=0;
        for t:=1 to lb do
        begin
          c[k+t-1]:=a[k]*b[t]+x+c[k+t-1];
          x:=c[k+t-1] div 10;
          c[k+t-1]:=c[k+t-1] mod 10;
        end;
        c[k+t]:=x;
      end;
      len:=len+lb;a:=c;
      while (c[len]=0)and(len>0) do dec(len);
    end;
    for j:=len downto 1 do write(c[j]);writeln;
  end;
  close(input);
  close(output);
end.

```

---

## 作者：zombie462 (赞：6)

## 这样的高精度题，怎么没有一篇python题解呢

~~顺便我们来学习一下$python$的一些基本入门操作，这样以后就可以虐高精度的模板题了~~

这道题的题意很简单，就是把字符串的每个位往后推$R$位，然后再把各个位上的$Ascii$码乘起来

~~话说我是比赛前这题第一个验题的人诶$qwq$，当时我高精度半个小时没调出来~~

```
# python的注释是用#号的
n,m=input().split() #读入部分，用这样的方式在同一行读入多个字符，但是都是字符串形式的
t=int(n)
r=int(m)%26 #必须用int，这里的int不是指换为ascii码，而是直接转为数字，就和pascal的val相似；对26取模，因为26个字母一循环
while (t>0): #while语句是这么打的
    s=input()
    t=t-1
    ans=1 #答案在这里哟
    s1="" #python不支持简单的字符串其中一位的修改操作，所以我们新开一个列表
    for i in range(0,len(s)-1): #for循环是这么打的，len函数等于pascal中的length，这里如果右边范围取len(s)的话会多出一个奇奇怪怪的字符
        x=chr(ord(s[i])+r) #往后推r位，ord和chr这两个函数P党都懂吧
        if (x>'Z'): #if语句是这么打的
            x=chr(ord(x)-26) #如果超出Z了就取模
        ans*=ord(x)
        s1=s1+x #把答案存入列表
    print(s1) #愉快输出
    print(ans)
```

这种方式应该不是最短的，但已经是很短了$qwq$

---

## 作者：JMercury (赞：6)

这题不是很简单吗？？？怎么被评成蓝色的？？？？

首先第一个偏移处理，由于R比较大，可以先取模

第二个处理不就是裸的高精吗？？

AC代码

```cpp
#include<bits/stdc++.h>
const int mod=26;
const int maxl=610;
using namespace std;

int n,r;
string s;
int ans[maxl<<1];

void init()
{
    memset(ans,0,sizeof(ans));
    ans[0]=1;
}

int main()
{
    scanf("%d%d",&n,&r);r%=mod;
    for(int i=1;i<=n;i++)
    {
        init();
        cin>>s;
        for(int j=0;j<s.size();j++) s[j]=((s[j]-'A')+r)%mod+'A';
        cout<<s<<endl;
        for(int j=0;j<s.size();j++)
        {
            for(int k=0;k<=1210;k++) ans[k]*=s[j];
            for(int k=0;k<=1210;k++) ans[k+1]+=ans[k]/10,ans[k]%=10;
        }
        int p=1215;
        while(!ans[p] && p) p--;
        for(p;p>=0;p--) cout<<ans[p];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：流逝丶 (赞：5)

这题也没啥，主要是高精乘低精

对于$R$先$%26$，然后加一遍，超过$90$的就$-26$，然后输出字符串

开始乘

答案为$ans$数组，$ans[0]$表示位数，因为是乘法，所以初值$ans[0]=ans[1]=1$

每次乘法先对$ans$中每一位乘上低精的那个，然后进位就行了。

最后倒序输出。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=605;
int n,r,len,g,now;
char ch[maxn];
int ans[maxn<<2];
inline void mul(int a1[],int x){
	for(int i=1;i<=a1[0];++i)
		a1[i]*=x;
	g=0;
	for(int i=1;i<=a1[0];++i){
		now=g;
		g=(a1[i]+g)/10;
		a1[i]=(a1[i]+now)%10;
	}
	while(g){
		a1[++a1[0]]=g%10;
		g/=10;
	}
    if(a1[a1[0]+1]>=1) a1[0]++;
    while(a1[a1[0]]==0&&a1[0]>1)--a1[0];
}
int main(){
	scanf("%d%d",&n,&r);
	r%=26;
	for(int i=1;i<=n;i++){
		memset(ans,0,sizeof(ans));
		ans[0]=ans[1]=1;
		scanf("%s",ch+1);
		len=strlen(ch+1);
		for(int j=1;j<=len;++j)
			ch[j]=(ch[j]+r)>90?ch[j]+r-26:ch[j]+r;
		printf("%s\n",ch+1);
		for(int i=1;i<=len;++i)
			mul(ans,ch[i]);
		for(int i=ans[0];i>=1;--i)
			printf("%d",ans[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Alarm5854 (赞：3)

这道题其实难度也不大，我一次就过了，我有点不理解为什么是蓝题~~(其实我也评了蓝题难度)~~，可能是没看清$R$的最大值高达$10^5$，而不是$26$。  
### 解题思路:
1. 这道题目不仅仅考了字符串的转换，还考了高精，可能没看清楚的人就开了$long\ long$，就完美的$WA$了，开高精也不用开的特别大，最多就$1173$位，所以省空间的人可以开$294$(万进制)位。
1. 在进行字符串转换时，一定要注意r的大小，建议一开始就对$26$取模，不容易出错。
1. 这是一个高精乘低精，每一位先乘一遍，再进位就可以了，当然也可以化低精位高精。
1. 千万别忘记输出之后把这个高精数的值初始化位1，否则$WA$和$RE$等着你。
### 完整代码如下：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  struct ll{//我喜欢把高精数定义成结构体，这样好操作一点
      int a[1222];//我用了10进制，你们也可以用别的进制，如万进制
      void start()//初始化
      {
          memset(a,0,4888);//4888=1222*sizeof(int)
          a[0]=a[1]=1;//用a[0]储存数组位数，并初始化为1，同时a[1]也要为1
      }
      ll& operator *=(int x)//重载运算符，高精乘以低精
      {
          for(int i=1;i<=a[0];i++)
              a[i]*=x;//先每一位乘一遍
          for(int i=1;i<=a[0];i++)
              a[i+1]+=a[i]/10,a[i]%=10,a[0]+=(i==a[0]&&a[i+1]);//接着进位
              /*这个不需要去前导0，想一下为什么*/
          return *this;//这个不用管
      }
      void out()//输出
      {
          for(int i=a[0];i>0;i--)
              printf("%d",a[i]);
          puts("");//别忘记换行
      }
  };
  ll a;
  int n,r,len;
  char str[666];
  void work(char *s,int len,int x)//中转字符串
  {
      x%=26;//一开始就对26取模，避免溢出导致WA
      for(int i=0;i<len;i++)
          s[i]+=x,s[i]-=26*(s[i]>90);//用了假值为0，真值为1的特性，使得代码简单明了
  }
  int main()
  {
      scanf("%d%d",&n,&r);
      /*当然你也可以直接把r对26取模*/
      while(getchar()!='\n');//这个不能少，用于吃换行符，少掉后果自负
      for(int i=1;i<=n;i++)
      {
          a.start();//初始化
          scanf("%s",str);//不建议用gets，否则警告一大串
          len=strlen(str);
          work(str,len,r);
          puts(str);//puts可以用，这个不会导致警告一大串
          for(int i=0;i<len;i++)//下标要从0开始
              a*=str[i];//一位一位乘
          a.out();//输出
      }
      return 0;
  }
```
这个程序的时间复杂度也许不是最优，但是这个代码相对来说比较友好，最后希望大家支持我，我接下来会写更多的题解，谢谢！

---

## 作者：pushinl (赞：3)

**听说考前发题解可以RP++**

**模拟+高精乘**

显然直接在每个字符位加上(R%26)即可。考虑爆到'Z'以上的情况，加个判断就行了。

数串显然要用高精乘。用ans存结果，处理每一位的时候顺便加进去。

代码非常丑 佬爷们凑活着看qwq

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, r;
char s[601];
int ans[10001];
int a[10001];
int main(){
    scanf("%d%d", &n, &r);
    while(n--){
        memset(a, 0, sizeof a);
        a[0]=a[1]=1;
        scanf("%s", s);
        int len=strlen(s);
        for(int i=0; i<len; i++){
            memset(ans, 0, sizeof ans);
            s[i]=s[i]+(r%26);
            if(s[i]>'Z')s[i]=s[i]-'Z'+'A'-1;
            cout<<s[i];
            
            int len=a[0];
            for(int j=1; j<=len; j++){
                int k=j;
                ans[j]+=a[j]*s[i];
                while(ans[k]>9){
                    ans[k+1]+=ans[k]/10;
                    ans[k]%=10;
                    k++;
                }
                if(k>a[0])a[0]=k;
            }
            for(int j=1; j<=a[0]; j++)
                a[j]=ans[j];
        }
        printf("\n");
        for(int i=a[0]; i>0; i--)
            printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：qwerta (赞：2)

**压位高精，当前最优解**

出题人已经说过了这道题不值蓝qwq

就是把每个字母移一下然后ASCII乘起来就好了。

然后把4位压到一个int里面，其实可以多压几位还能更快的qwq

权当压位高精练手题了qwq

~~/*后排表白社会出题人*/~~

```
/*
qwerta 
P5000 Hillwer编码 Accepted 
100
代码 C++，0.84KB
提交时间 2018-11-06 08:22:36
耗时/内存 183ms, 812KB
*/
// luogu-judger-enable-o2
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
char s[503];
int a[303];//高精数组
int toa;
void mult(int x)//乘上x
{
    for(int i=1;i<=toa;++i)
      a[i]*=x;
    for(int i=1;i<=toa;++i)
    if(a[i]>9999)//处理多于4位的
    {
        a[i+1]+=a[i]/10000;
        a[i]%=10000;
        toa=max(toa,i+1);
    }
    return;
}
void write(int x)//快(慢)写
{
    if(x>9)write(x/10);
    putchar(x%10+'0');
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    int n,R;
    cin>>n>>R;
    R%=26;
    while(n--)
    {
        cin>>s;
        int lens=strlen(s);
        memset(a,0,sizeof(a));
        toa=1;
        a[1]=1;
        for(int i=0;i<lens;++i)
        {
            int x=s[i]+R;//移位
            if(x>'Z')x-=26;//减一下
            putchar(x);//输出
            mult(x);//乘起来
        }
        putchar('\n');//cout<<endl
        write(a[toa]);//先输出第一个
        for(int i=toa-1;i;--i)
        {
            if(a[i]<1000)putchar('0');
            if(a[i]<100)putchar('0');
            if(a[i]<10)putchar('0');
            write(a[i]);
        }
        putchar('\n');
    }
    return 0;
}

```

---

## 作者：zybnxy (赞：1)

感觉这道题很简单啊，~~为什么被评上蓝色了~~

算法：高精+字符串处理。

* 1：关于字符串的处理

题目要求让我们把字符像后移$R$个字符。

我们发现题目没有说明$R<=26$

然而发现每$26$次是一个周期。

所以我们只需把$R\%26$即可。

对于字符串边界的处理。

* 如果发现每个字符$s[i]+R<=Z$
我们可以直接变换

* 如果一个字符$s[i]+R<=26$

我们需要把这个字符的$ascll$码在减去$A$的$asc$值。

只要处理完字符串，剩下的乘就是模板的事了~~不会自行背高精模板~~

再次$LZ$为大家准备了高精模板~~防止NOIP的毒瘤~~

代码+很久之前高精

```cpp
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#define ri register int
#define maxn 1001
using namespace std;
inline int read()
{
    int res=0,flag=1;
    char ch;
    for(;!isdigit(ch);ch=getchar())
        if(ch=='-')flag=-1;
    for(;isdigit(ch);ch=getchar())
        res=res*10+ch-'0';
    return res*flag;
}
struct bign{  
    int d[maxn], len;  
    void clean() { while(len > 1 && !d[len-1]) len--; }  
    bign()          { memset(d, 0, sizeof(d)); len = 1; }  
    bign(int num)   { *this = num; }   
    bign(char* num) { *this = num; }  
    bign operator = (const char* num){  
        memset(d, 0, sizeof(d)); len = strlen(num);  
        for(int i = 0; i < len; i++) d[i] = num[len-1-i] - '0';  
        clean();  
        return *this;  
    }  
    bign operator = (int num){  
        char s[20]; sprintf(s, "%d", num);  
        *this = s;  
        return *this;  
    }  
    bign operator + (const bign& b){  
        bign c = *this; int i;  
        for (i = 0; i < b.len; i++){  
            c.d[i] += b.d[i];  
            if (c.d[i] > 9) c.d[i]%=10, c.d[i+1]++;  
        }  
        while (c.d[i] > 9) c.d[i++]%=10, c.d[i]++;  
        c.len = max(len, b.len);  
        if (c.d[i] && c.len <= i) c.len = i+1;  
        return c;  
    }  
    bign operator - (const bign& b){  
        bign c = *this; int i;  
        for (i = 0; i < b.len; i++){  
            c.d[i] -= b.d[i];  
            if (c.d[i] < 0) c.d[i]+=10, c.d[i+1]--;  
        }  
        while (c.d[i] < 0) c.d[i++]+=10, c.d[i]--;  
        c.clean();  
        return c;  
    }  
    bign operator * (const bign& b)const{  
        int i, j; bign c; c.len = len + b.len;   
        for(j = 0; j < b.len; j++) for(i = 0; i < len; i++)   
            c.d[i+j] += d[i] * b.d[j];  
        for(i = 0; i < c.len-1; i++)  
            c.d[i+1] += c.d[i]/10, c.d[i] %= 10;  
        c.clean();  
        return c;  
    }  
    bign operator / (const bign& b){  
        int i, j;  
        bign c = *this, a = 0;  
        for (i = len - 1; i >= 0; i--)  
        {  
            a = a*10 + d[i];  
            for (j = 0; j < 10; j++) if (a < b*(j+1)) break;  
            c.d[i] = j;  
            a = a - b*j;  
        }  
        c.clean();  
        return c;  
    }  
    bign operator % (const bign& b){  
        int i, j;  
        bign a = 0;  
        for (i = len - 1; i >= 0; i--)  
        {  
            a = a*10 + d[i];  
            for (j = 0; j < 10; j++) if (a < b*(j+1)) break;  
            a = a - b*j;  
        }  
        return a;  
    }  
    bign operator += (const bign& b){  
        *this = *this + b;  
        return *this;  
    }  
  
    bool operator <(const bign& b) const{  
        if(len != b.len) return len < b.len;  
        for(int i = len-1; i >= 0; i--)  
            if(d[i] != b.d[i]) return d[i] < b.d[i];  
        return false;  
    }  
    bool operator >(const bign& b) const{return b < *this;}  
    bool operator<=(const bign& b) const{return !(b < *this);}  
    bool operator>=(const bign& b) const{return !(*this < b);}  
    bool operator!=(const bign& b) const{return b < *this || *this < b;}  
    bool operator==(const bign& b) const{return !(b < *this) && !(b > *this);}  
    string str() const{  
        char s[maxn]={};  
        for(int i = 0; i < len; i++) s[len-1-i] = d[i]+'0';  
        return s;  
    }  
};  
istream& operator >> (istream& in, bign& x)  
{  
    string s;  
    in >> s;  
    x = s.c_str();  
    return in;  
}  
ostream& operator << (ostream& out, const bign& x)  
{  
    out << x.str();  
    return out;  
}
int n,r;
bign q;
inline void work(string s)
{
    r%=26;
    for(ri i=0;i<s.size();i++)
    {
        if(s[i]+r<='Z')s[i]=s[i]+r;
        else s[i]=s[i]+r-('Z'-'A'+1);
    }
    q=1;
    for(ri i=0;i<s.size();i++)
        q=q*s[i];
    cout<<s<<endl;
    cout<<q<<endl;
}
int main()
{
    n=read();r=read();
    string s;
    for(ri i=1;i<=n;i++)
    {
    	cin>>s;
    	work(s);
    }
    return 0;
}
```

---

## 作者：瓜皮少年 (赞：1)

### 读题，显而易见是个字符串的模拟
那为什么难度那么高呢，看看数据范围应该是高精，所以说

简单的模拟+高精就过了
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
struct bign:vector<int> {
    bign(int n=0) {
        push_back(n);
        check();
    }
    bign& check() {
        while(!empty()&&!back())pop_back();
        if(empty())return *this;
        for(int i=1; i<size(); ++i) {
            (*this)[i]+=(*this)[i-1]/10;
            (*this)[i-1]%=10;
        }
        while(back()>=10) {
            push_back(back()/10);
            (*this)[size()-2]%=10;
        }
        return *this;
    }
};
istream& operator >> (istream &is,bign &n) {
    string s;
    is>>s;
    n.clear();
    for(int i=s.size()-1; i>=0; --i)n.push_back(s[i]-'0');
    return is;
}
ostream& operator << (ostream &os,const bign &n) {
    if(n.empty())os<<0;
    for(int i=n.size()-1; i>=0; --i)os<<n[i];
    return os;
}
bool operator != (const bign &a,const bign &b) {
    if(a.size()!=b.size())return 1;
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return 1;
    return 0;
}
bool operator == (const bign &a,const bign &b) {
    return !(a!=b);
}
bool operator < (const bign &a,const bign &b) {
    if(a.size()!=b.size())return a.size()<b.size();
    for(int i=a.size()-1; i>=0; --i)
        if(a[i]!=b[i])return a[i]<b[i];
    return 0;
}
bool operator > (const bign &a,const bign &b) {
    return b<a;
}
bool operator <= (const bign &a,const bign &b) {
    return !(a>b);
}
bool operator >= (const bign &a,const bign &b) {
    return !(a<b);
}
bign& operator += (bign &a,const bign &b) {
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0; i!=b.size(); ++i)a[i]+=b[i];
    return a.check();
}
bign operator + (bign a,const bign &b) {
    return a+=b;
}
bign& operator -= (bign &a,bign b) {
    if(a<b)swap(a,b);
    for(int i=0; i!=b.size(); a[i]-=b[i],++i)
        if(a[i]<b[i]) {
            int j=i+1;
            while(!a[j])++j;
            while(j>i) {
                --a[j];
                a[--j]+=10;
            }
        }
    return a.check();
}
bign operator - (bign a,const bign &b) {
    return a-=b;
}
bign operator * (const bign &a,const bign &b) {
    bign n;
    n.assign(a.size()+b.size()-1,0);
    for(int i=0; i!=a.size(); ++i)
        for(int j=0; j!=b.size(); ++j)
            n[i+j]+=a[i]*b[j];
    return n.check();
}
bign& operator *= (bign &a,const bign &b) {
    return a=a*b;
}
bign divmod(bign &a,const bign &b) {
    bign ans;
    for(int t=a.size()-b.size(); a>=b; --t) {
        bign d;
        d.assign(t+1,0);
        d.back()=1;
        bign c=b*d;
        while(a>=c) {
            a-=c;
            ans+=d;
        }
    }
    return ans;
}
bign operator / (bign a,const bign &b) {
    return divmod(a,b);
}
bign& operator /= (bign &a,const bign &b) {
    return a=a/b;
}
bign& operator %= (bign &a,const bign &b) {
    divmod(a,b);
    return a;
}
bign operator % (bign a,const bign &b) {
    return a%=b;
}
bign pow(const bign &n,const bign &k) {
    if(k.empty())return 1;
    if(k==2)return n*n;
    if(k.back()%2)return n*pow(n,k-1);
    return pow(pow(n,k/2),2);
}//高精
int n,k;
string c;
int main(){
	cin>>n>>k;//输入
	k%=26;//先%一下，因为超过26没意思
	for(int i=1;i<=n;i++){
		cin>>c;
		for(int j=0;j<c.size();j++){
			c[j]=((c[j]-'A')+k)%26+'A';
			cout<<c[j];//处理并输出
		}
		cout<<endl;
		bign sum=1;//用高精才能
		for(int j=0;j<c.size();j++){
			int s;
			s=c[j]-'A'+65;
			sum*=s;//将 S1 S1每一位的ACS码（即ASCLL码）相乘
		}
		cout<<sum<<endl;//输出
	}
	return 0;
}

```

---

