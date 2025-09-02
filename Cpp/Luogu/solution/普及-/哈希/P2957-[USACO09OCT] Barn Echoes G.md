# [USACO09OCT] Barn Echoes G

## 题目描述

The cows enjoy mooing at the barn because their moos echo back, although sometimes not completely. Bessie, ever the excellent

secretary, has been recording the exact wording of the moo as it goes out and returns. She is curious as to just how much overlap there is.

Given two lines of input (letters from the set a..z, total length in the range 1..80), each of which has the wording of a moo on it, determine the greatest number of characters of overlap between one string and the other. A string is an overlap between two other strings if it is a prefix of one string and a suffix of the other string.

By way of example, consider two moos:

```
moyooyoxyzooo
yzoooqyasdfljkamo
```
The last part of the first string overlaps 'yzooo' with the first part of the second string. The last part of the second string

overlaps 'mo' with the first part of the first string. The largest overlap is 'yzooo' whose length is 5.

POINTS: 50

奶牛们非常享受在牛栏中哞叫，因为她们可以听到她们哞声的回音。虽然有时候并不能完全听到完整的回音。Bessie 曾经是一个出色的秘书，所以她精确地纪录了所有的哞叫声及其回声。她很好奇到底两个声音的重复部份有多长。

输入两个字符串（长度为 $1$ 到 $80$ 个字母），表示两个哞叫声。你要确定最长的重复部份的长度。两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串。

我们通过一个例子来理解题目。考虑下面的两个哞声：

```
moyooyoxyzooo
yzoooqyasdfljkamo
```

第一个串的最后的部份 `yzooo` 跟第二个串的第一部份重复。第二个串的最后的部份 `mo` 跟第一个串的第一部份重复。所以 `yzooo` 跟 `mo` 都是这 $2$ 个串的重复部份。其中，`yzooo` 比较长，所以最长的重复部份的长度就是 $5$。


## 说明/提示

'abcxxxxabcx' is a prefix of the first string and a suffix of the second string.


## 样例 #1

### 输入

```
abcxxxxabcxabcd 
abcdxabcxxxxabcx 
```

### 输出

```
11 
```

# 题解

## 作者：Alex_Wei (赞：57)

2021.3.7 : 修正错解。

---

重点：$\mathrm{string}$ 类成员函数（$\mathrm{find}$ 和 $\mathrm{substr}$）。

```a=s.substr(n,m)```：截取字符串 $s$ 中从第 $n$ 位（位数从 $0$ 开始）开始的长度为 $m$ 的字符串并赋给 $a$。

```s.find(n)```：返回字符串 $n$ 在 $s$ 中第一次出现的位置（开头），如果没有找到，则返回 $-1$。

因为数据范围极小，所以直接枚举回声的长度暴力判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int main(){
	cin>>a>>b; if(a.size()>b.size())swap(a,b);//如果a比b长，先调换位置，避免substr时访问越界
	for(int x=a.size()-1;x>=0;x--){//x代表回声的长度
		string prea=a.substr(0,x),sufa=a.substr(a.size()-x,x);
		string preb=b.substr(0,x),sufb=b.substr(b.size()-x,x);
		if(prea==sufb||preb==sufa)cout<<x<<endl,exit(0);
		//如果一个字符串的前缀等于另一个字符串的后缀，输出答案即可
	} return 0;
}
```

---

## 作者：huayt (赞：35)

刚学完哈希，刷道水题练练手~~~

**思路**

1.先求两个字符串的前缀哈希值

2.枚举两个字符串的重复部分的长度

3.因为题目说“**两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串**”，所以只要判断两种情况：（划重点了）

# one
第一个字符串的前缀的区间哈希值

**和**

第二个字符串的后缀的区间哈希值

# two
第一个字符串的后缀的区间哈希值

**和**

第二个字符串的前缀的区间哈希值



------------
比较一下，取最大值就完了

**废话不多说，看就完了**

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<climits>
#include<cmath>

using namespace std;
const int N=110,base=131;
typedef unsigned long long ULL;
ULL p[N],hl[N],hr[N];
char stra[N],strb[N];
int lena,lenb,lmax;

ULL get(ULL h[],int l,int r)
{
	return h[r]-h[l-1]*p[r-l+1];
}//求l~r的区间哈希值
int main()
{
	int i,j,res=INT_MIN;
	scanf("%s%s",stra+1,strb+1);
	lena=strlen(stra+1);
	lenb=strlen(strb+1);
	lmax=max(lena,lenb);//求最长字符串的长度
	p[0]=1;
	
	for(i=1;i<=lena;i++) hl[i]=hl[i-1]*base+(stra[i]-96);
	for(i=1;i<=lenb;i++) hr[i]=hr[i-1]*base+(strb[i]-96);
	for(i=1;i<=lmax;i++) p[i]=p[i-1]*base;
	//求前缀哈希值
    
	for(i=1;i<=lmax;i++)
	{
		int al,bl;
		if(lena<i||lenb<i) break;//判断边界
		al=get(hl,1,i)!=get(hr,lenb-i+1,lenb)?INT_MIN:i;
        //判断第一个字符串的前缀的区间哈希值和第二个字符串的后缀的区间哈希值是否相等
		bl=get(hl,lena-i+1,lena)!=get(hr,1,i)?INT_MIN:i;
		//判断第一个字符串的后缀的区间哈希值和第二个字符串的前缀的区间哈希值是否相等
		res=max(res,max(al,bl));//求最大值
	}
	printf("%d\n",res);
	return 0;//华丽的结尾~~~
}
```
本~~蒟蒻~~的**第一篇**题解，请多多支持


---

## 作者：Illenium (赞：20)

## ~~真·蒟蒻~~的第一篇题解
#### 其实这只是一道字符串基础题
##### ~~（其实是我太弱了，看不懂大佬们的高级算法）~~
话说C++的string函数真的是很好用的东西，
不仅可以缩短码量，
还能为我这样的蒟蒻减少很多的思考时间
~~（QAQ闲到刷橙题的还在乎什么时间）~~
### 废话不多说，直接贴代码
```
#include<iostream>
using namespace std;
int main()
{	
    int i,j;
    string a,b;
    cin>>a>>b;	//万能的cin输入 
    int n=min(a.size(),b.size());	//size函数返回字符串长度
    for(i=n;i>=1;i--)	//从长到短扫描，找出最长的重复部分，最长不超过两个字符串中较短的那个
    	if(a.substr(0,i)==b.substr(b.size()-i,i))	//substr(x,y)函数返回从x位置开始长度为y的子字符串，这里用来寻找字符串a的前缀和字符串b的后缀的最长重复部分
    		break;	 //一旦找到，立即退出循环 
    for(j=n;j>=1;j--)
    	if(b.substr(0,j)==a.substr(a.size()-j,j))
    		break;	//同上，寻找字符串a的后缀和字符串b的前缀的最长重复部分	
    cout<<max(i,j);  //输出两重复部分中较长那个的长度 
    return 0;
} 
```

---

## 作者：zhangboju (赞：11)


这道题难度“普及-”（橙题），无聊来刷水题的我是真的不理解大佬们是为什么要用那些本蒟蒻听都听不懂的哈希，递归这些高端算法的。

### 给你们来一个：暴力出奇迹

------------

#### first of all：
我先来介绍两个string类（没错，就是那个令P党羡慕的c++独有的字符串类）函数：（不想用的直接看下方解法二）
```cpp
string s//先定义字符串
```
	
   1.s.substr(int a,int b)
   
   2.s.size()
   
   
#### 1.substr函数 

它用于寻找子串 从下标为a的位置提取到下标为b的位置，下为例子：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s="zhe ge ti shi ge shui ti";
int main()
{
   cout<<s.substr(10,21);
   return 0;
}
```
    
运行程序，输出“shi ge shui ti”，想一想为什么。

#### 2.size函数

它用于求字符串的长度，相当于字符数组中的 strlen()函数，下为例子：

 ```cpp
#include <bits/stdc++.h>
using namespace std;
string s="zhe ge ti shi ge shui ti";
int main()
{
   cout<<s.size;
   return 0;
}
```

运行程序，输出24，想一想为什么。



------------
终于进入正题了

#### 解法1：

string类的解法（壮哉我c++，string类为我省了好多功夫）
```cpp
#include <bits/stdc++.h>
using namespace std;
string s1,s2;
int len1=1,len2=1; 
int main()
{
    cin>>s1>>s2;
    for(int i=1;i<=min(s1.size(),s2.size());i++)//比较s1与s2长度，并取最小 
    {
        if(s1.substr(0,i)==s2.substr(s2.size()-i,i))//提取子串 
        {
            len1=i;
        }
        if(s2.substr(0,i)==s1.substr(s1.size()-i,i))
        {
            len2=i;
        }
     }
    if(len1>len2)//比较大小，输出 
    {
        cout<<len1;
    }
    else
    {
       cout<<len2;
    }
}
```
解法2：

我为坚持用字符数组的童鞋提供了第二种解法
```cpp
#include <bits/stdc++.h>
using namespace std;
char s1[10000],s2[10000];
int ans,cnt,ansmax,b;
int main()
{
   cin>>s1>>s2;
   for(int i=0;i<strlen(s1);i++)
   {
       for(int j=i;j>=0;j--)
       {
           if(s1[j]!=s2[strlen(s2)-1-i+j])
           {
                b=1;
                break;
           }
       }
       if(b==0)
       {
            ans=i+1;
            ansmax=max(ansmax,ans);
       }
       b=0;
   }
   for(int i=0;i<strlen(s2);i++)
   {
       for(int j=i;j>=0;j--)
       {
            if(s2[j]!=s1[strlen(s1)-1-i+j])
            {
                 b=1;
                 break;
            }
       }
       if(b==0)
       {
            ans=i+1;
            ansmax=max(ansmax,ans);
       }
       b=0;
   }
   cout<<ansmax;
}
```

我就不解释了 ~~（但明显比上一个难看）~~

#### 两个代码都是AC的，请组织放心！！








---

## 作者：子夜葵 (赞：10)

看到有人直接暴力，有人用STL，并没有看到有人用KMP。
这一题很明显就是一道字符串匹配的问题。

KMP在匹配的时候，当子串去匹配主串的时候，当主串匹配完的时候，那么此时子串匹配的长度就是主串的后缀和子串的前缀的最长重复值。

见下图：

![](https://img-blog.csdnimg.cn/20190830231023810.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x6eXdzNzM5MzA3NDUz,size_16,color_FFFFFF,t_70)

此时j就是最长的重复值，两个串一个当主串，一个当子串，取最大值就是答案。
```cpp
/* 
 * @Author: lzyws739307453 
 * @Language: C++ 
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int nex[MAXN];
char sa[MAXN], sb[MAXN];
void Next(char str[], int len) {
    int i = 0, j = -1;
    nex[0] = -1;
    while (i < len) {
        if (~j && str[i] != str[j])
            j = nex[j];
        else nex[++i] = ++j;
    }
}
int KMP(char sa[], int la, char sb[], int lb) {
    Next(sb, lb);
    int i = 0, j = 0;
    while (i < la) {
        if (~j && sa[i] != sb[j])
            j = nex[j];
        else i++, j++;
    }
    return j;
}
int main() {
    scanf("%s%s", sa, sb);
    int la = strlen(sa);
    int lb = strlen(sb);
    int cnta = KMP(sa, la, sb, lb);
    int cntb = KMP(sb, lb, sa, la);
    printf("%d\n", max(cnta, cntb));
    return 0;
}
```

---

## 作者：张亦弛 (赞：10)

### 题目大意

给两个字符串，找出最大重复长度（两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串）

### 分析

比如两个字符串a、b，因为有可能是a的头和b的尾、b的头和a的尾两种情况，那么我们就处理出a的头、a的尾、b的头、b的尾，然后再for一遍找最大值即可。

对于这两个字符串的头和尾，我们就可以用到字符串hash，front[i]、back[i]分别表示：前i个字符的hash值和后i个字符的hash值，其实就是一个类似于前缀和和后缀和的东西（前缀后缀和与本题无关）。

最后我们再取fronta和backb、frontb、backa分别扫一遍，找出hash值相同的最大位置，就是最长的重复部分。

### 代码（详细注释）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define mod 192**817//咳咳
#define ins 11111
using namespace std;
char a[85];//字符串a 
char b[85];//字符串b 
int lena,lenb;//两个字符串的长度 
int fronta[85],backa[85];//a的前缀、后缀hash值 
int frontb[85],backb[85];//b的前缀、后缀hash值 
int ans;//记录覆盖长度 
int maxx;//记录最大覆盖长度 
int front_insert_hash(char s[],int len)//计算前缀hash值 
{
	ll sum=0;//初始化hash值 
	for(int i=0;i<len;i++)
		sum=(sum*ins+(ll)s[i])%mod;//计算hash值 
	return sum;//返回hash值 
}
int back_insert_hash(char s[],int len)//计算后缀hash值 
{
	ll sum=0;//初始化hash值 
	int lenn=strlen(s);//lenn是字符串总长度 
	for(int i=lenn-len;i<lenn;i++)//注意这里的len是从后往前数的第几位 
		sum=(sum*ins+(ll)s[i])%mod;//计算哈市值 
	return sum;//返回hash值 
}
int main()
{
	scanf("%s",a);//读入第一个字符串 
	scanf("%s",b);//读入第二个字符串 
	lena=strlen(a);//第一个字符串的长度 
	lenb=strlen(b);//第二个字符串的长度 
	for(int i=0;i<lena;i++)
		fronta[i]=front_insert_hash(a,i);//字符串a的前缀hash值 
	for(int i=0;i<lenb;i++)
		backb[i]=back_insert_hash(b,i);//字符串b的后缀hash值
	for(int i=0;i<lenb;i++)
		frontb[i]=front_insert_hash(b,i);//字符串b的前缀hash值 
	for(int i=0;i<lena;i++)
		backa[i]=back_insert_hash(a,i);//字符串a的后缀hash值  
	int minlen=min(lena,lenb);//取最短长度 
	ans=0;//重复长度清0 
	for(int i=0;i<minlen;i++)//a的头和b的尾 
		if(fronta[i]==backb[i])//hash值相等说明字符子串相同 
			ans=i;
	maxx=max(ans,maxx);//取最大值 
	ans=0;//重复长度清0 
	for(int i=0;i<minlen;i++)//a的尾和b的头 
		if(frontb[i]==backa[i])//hash值相等说明字符子串相同 
			ans=i;
	maxx=max(ans,maxx);//取最大值
	cout<<maxx;//输出最大覆盖长度 
	return 0;
}
```

---

## 作者：太阳之神2015 (赞：10)

我不太明白为什么要用那些高大上的算法，居然还有用哈希、动归的。感觉这道题很简单啊。就是简单的两次从前往后扫一遍，符合要求就求最大值就行了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ans=0;
int main()
{
    string s1,s2;
    cin >> s1 >> s2;
    int l1=s1.size(),l2=s2.size();
    string s="";
    for (int i=0; i < l1; i++)
    {
        s+=s1[i];
        int k=s2.find(s);
        if (k!=string::npos)
            if (l2-k==i+1)
                ans=l2-k;
    }
    s="";
    for (int i=0; i < l2; i++)
    {
        s+=s2[i];
        int k=s1.find(s);
        if (k!=string::npos)
            if (l1-k==i+1)
                ans=max(ans,l1-k);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Ofnoname (赞：9)

普通的哈希题。最开始我想的是预处理字符串的哈希前缀和来做，后来才发现远远没有这么复杂。直接每次枚举字符串的哈希值就可以了。由于会重复计算所以效率稍稍偏低。但方法简单易懂，通过此题已经足够。

```cpp
#include <bits/stdc++.h>
#define long unsigned long long
#define MAX 100
using namespace std;

char s1[MAX],s2[MAX];
int i,j,size1,size2,ans;

inline long hash(char s[],int L,int R)
{
	//计算字符串s从L到R的哈希值
	register long ans=0;
	for (register int i=L; i<=R; i++)
		ans=ans*131+s[i];//自然溢出
	return ans;
}

int main()
{
	scanf("%s",s1+1); size1=strlen(s1+1);//我用1开始做下表
	scanf("\n%s",s2+1); size2=strlen(s2+1);
	for (i=1,j=size2; i<=size1&&j>=1; i++,j--)//s1从前向后，s2从后向前
		if (hash(s1,1,i)==hash(s2,j,size2))//判断字符串相等
			ans=(ans>i)?ans:i;//更新答案，i就是当前的字符串的长度
	for (i=size1,j=1; i>=1&&j<=size2; i--,j++)//s2从前向后，s1从后向前
		if (hash(s1,i,size1)==hash(s2,1,j))//同上
			ans=(ans>j)?ans:j;
	printf("%d",ans);
	return 0;
}
```



---

## 作者：syszs (赞：5)

由于本人比较蒻,所以只能用模拟做这道题... 



------------我只是一条分割线------------

下面说正题.

题目中的第一段全是~~精髓~~废话
题目的意思非常明朗,就是给出两个字符串,让你求出这两个字符串当中的最大连续重叠部分.

好的,读完了题,就可以开始解题了,不难想到,把字符串1和字符串2的字符一个一个扫描,只要发现相等就用while语句往后搜,
求出连续字符串的长度,与max相比较(max刚开始要清0)

但这样做,非常浪费时间,会不会超时呢?

只要看到字符串长度的数据范围,惊奇的发现小于等于~~8000~~
 80,而按照我们的思路,时间复杂度最大为
#  $O(n^3)$
 所以,不会超时,可以放心大胆的做了.
 下面附上代码
 ```pascal
var
  s1,s2:string;//因为字符串长度最大为80，所以不用ansistring
  i,j,d,t1,t2,max,s:longint;
begin
  readln(s1);//读入字符串1
  readln(s2);//读入字符串2
  max:=0;//最大值初始化
  for i:=1 to length(s1) do//线性扫描字符串1
   for j:=1 to length(s2) do if s1[i]=s2[j]  then begin //判断字符是否相同
   s:=1;
   t1:=i+1;
   t2:=j+1;
   while (s1[t1]=s2[t2])and(t1<=length(s1))and(t2<=length(s2)) do begin //开始寻找连续相同字符串
   inc(s);
   inc(t1);
   inc(t2);
   end;
   if s>max then max:=s;//如果大于,则更新max
   end;
   writeln(max);//输出最终值
end.//程序结束


```





---

## 作者：Kwork (赞：3)

贴一个滚动哈希。用到了long long溢出取模的黑科技。

思路就是暴力做，两遍overlap得到最长的相同部分。然后就没了。


```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
//
using namespace std;
//
typedef unsigned long long ull;
//
const ull B=100******;//和谐
//
string a,b;
//
inline void read_string(string &s){
    s="";
    char ch=getchar();
    while(ch<'a' || ch>'z') ch=getchar();
    do{
        s+=ch;
        ch=getchar();
    }while(ch>='a' && ch<='z');
    return;
}
void in_data(){
    read_string(a);
    read_string(b);
    return;
}
int over_lap(string a,string b){
    int ans=0;
    int al=a.length(),bl=b.length();
    ull ah=0,bh=0,t=1;
    for(int i=1;i<=min(al,bl);i++){
        ah=ah+a[al-i]*t;
        bh=bh*B+b[i-1];
        t*=B;
        if(ah==bh) ans=i;
    }
    return ans;
}
void solve_query(){
    int ans=over_lap(a,b);
    ans=max(ans,over_lap(b,a));
    printf("%d\n",ans);
    return;
}
int main(){
    in_data();
    solve_query();
    return 0;
}
```

---

## 作者：Youngsc (赞：3)

[Youngsc](http://youngscc.github.io/)


天哪为什么要哈希什么的，这不是个赤裸裸的DP嘛？？

f[i][j]表示分别以a[i],b[j]结尾的最长的相同部分的子串的长度。

n2地枚举i，j，若a[i] = b[j],f[i][j] = f[i-1][j-1]+1,否则,f[i][j] = f[i-1][j-1]。

一定要从1开始记，否则可能会由于i-1而访问负内存。


```cpp
# include <algorithm>
# include <cstring>
# include <iostream>
# include <cstdio>
# include <cmath>
# include <queue>
# include <map>
# define R register
# define LL long long

using namespace std;

char a[100],b[100];
int f[100][100],ans;

inline void maxx(R int &a,const int b){a>b? :a=b;}

inline int yg(){
    scanf("%s%s",a+1,b+1);
    R int la = strlen(a+1),lb = strlen(b+1);
    for(R int i=1; i<=la; ++i)
        for(R int j=1; j<=lb; ++j)
        {
            if(a[i]!=b[j]) f[i][j]=f[i-1][j-1];
            else f[i][j] = f[i-1][j-1]+1;
            maxx(ans,f[i][j]);
        }
    cout << ans;
    return 0;
}

int youngsc = yg();
int main(){;}
```

---

## 作者：syf2008 (赞：2)

话不多说,上代码:
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int maxn=-1;
    string a,b;//定义字符串
    cin>>a>>b;
    for(int i=0;i<a.size();i++)
    for(int j=0;j<=a.size()-i;j++)
   if(b.find(a.substr(i,j))!=-1)//在b里找a的截取部分
    if(j>maxn)//如果找到的比之前的大
    maxn=j;
    cout<<maxn<<endl;
    return 0;
}
```

---

## 作者：衡屿睿 (赞：2)

map容器属于C++的STL内容，它的思想——不同或相同数据类型之间的映射，是应该谙熟的。

通过下面的分析，我们来了解一下这道题的简单框架：

(假定，第一组声音是abcdefg....xyz,第二组声音是！@#￥%....)\_+)

1,将a ab abc ...存入map容器a中，对应的值为1 2 3 ...(声音长度)

2,处理完毕后，再将第二组声音的尾部一一拿来比较:

(1)存在两个声音重复，此时map容器a[此声音]的值大于0；

(2)不存在，a等于零；

3,通过上述分析，以sum作为最长的重复部份的长度，则sum=max(sum,a[此声音]);

4,最后，将前缀和后缀的情况都模拟一遍cout<<sum即可。

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
map<string,int>a,k;
string b,c,d,e,jyx,jyx1;
int main()
{
    int sum=0;
    cin>>b>>c;
    int lenb=b.size(),lenc=c.size();
    for(int i=0;i<lenb;++i)
    {
        d+=b[i];
        a[d]=i+1;
    }
    for(int i=lenb-1;i>=0;--i)
    {
        e=b[i]+e;
        k[e]=lenb-i;
    }
    for(int i=lenc-1;i>=0;--i)
    {    
        jyx=c[i]+jyx;
        sum=max(sum,a[jyx]);
    }
    for(int i=0;i<lenc;++i)
    {    
        jyx1+=c[i];
        sum=max(sum,k[jyx1]);
    }
    cout<<sum;
    return 0;
}
```

---

## 作者：swl3992 (赞：1)

本蒟蒻实在不懂为什么大佬们都写得那么腐炸。

# 此题在本蒟蒻眼里就是个暴力。

# 重点就是string的substr函数

substr的作用是从某一个字符串里取出字串，有两个参数,第一

个是起始下标(取出时包含这个下标)第二个是长度，记住一定是长度！！！不是结束下标！！！

```cpp
#include <bits/stdc++.h>	//懒人福利：万能库
using namespace std;
int main ()
{
	ios::sync_with_stdio(0);	//cin,cout的加速
	string str1,str2;
	cin>>str1>>str2;	//输入
	int len1=str1.size();
	int len2=str2.size();	//获取长度
	int maxn=0;	//ans,初始化为0
	for(int i=min(len1,len2);i>=1;i--)	//枚举重复部分字串的长度，最长是长度较短的那个字符串的长度,注意，此循环倒着跑，一旦成功就break
	{
		string temp1=str1.substr(0,i);	//从第一个字符串里取出0~0+i位置的字串
		string temp2=str2.substr(len2-i,i);	//从第二个字符串里取出末尾~末尾-i位置的字串
		if(temp1==temp2)
		{
			maxn=i;	//匹配成功
			break;
		}
		temp1=str1.substr(len1-i,i);	//这两个前面解释过了
		temp2=str2.substr(0,i);
		if(temp1==temp2)
		{
			maxn=i;	//同理
			break;
		}
	}
	cout<<maxn<<endl;	//输出maxn
	return 0;
}

```




---

## 作者：SUNCHAOYI (赞：1)

**枚举判断截取的字符串是否在回声串中**

**如果是计算长度，比较,取最大值即可**
```
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string n,m,s;
	int ans=0;
	cin>>n>>m;
	for(int i=0;i<n.size();i++)
	{
		for(int j=0;j<=i;j++)
		{
			s="";
			for(int k=j;k<=i;k++)s=s+n[k];//范围i-j时的字符串 
			if(m.find(s)!=-1)ans=max(ans,i-j+1);//如果包含，判断长度，并保存最大值 
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Derpy (赞：1)

本蒟蒻目前还不是很懂哈希

就写了一个最暴力的枚举，枚举第一个字符串可能出现的字符串然后再找出最长的相同字符串就行了，代码简单易懂，最基础地用到了map而已

```cpp
#include<iostream>
#include<map>
using namespace std;
map<string,bool>m;
string a,b,s;
int main()
{
    int ans=0;
    cin>>a>>b;//输入 
    int l1=a.length(),l2=b.length();
    for(int i=0;i<=l1-1;i++)
    {
        for(int j=0;j<=i;j++)
        {
            for(int k=j;k<=i;k++)//i和j表示字符串的开头和结尾，通过循环加起来组成字符串s 
            s+=a[k];
            m[s]=1;//将a中可以构成的字符串标记为可用 
            s="";//清零以便下次累加 
        }
    }
    for(int i=0;i<=l2-1;i++)
    {
        s="";
        for(int j=0;j<=i;j++)
        {
            for(int k=j;k<=i;k++)//同样i,j表示开头结尾,s累加枚举所有b中可能出现的字符串 
            s+=b[k];
            if(m[s])//如果a中有这个字符串的话更新答案 
            {
                ans=ans<(i-j+1)?(i-j+1):ans;
            }
            s="";//清零以便下次累加 
        }
    }
    cout<<ans;//输出 
    return 0;
}
```

---

## 作者：Biscuit46 (赞：1)

# 题面
[原题](https://www.lydsy.com/JudgeOnline/problem.php?id=2957)

# Solution
想一想线段树怎么更新答案:对于线段树,维护两个值,一个是区间内的最大斜率,一个是区间内的答案.

最大斜率很好更新,但是如何更新答案?

想一想,对于一个节点,它左子树的答案是必然可以更新到当前节点的.对吧!

那么右子树怎么考虑?

如果右子树的左子树的最大值<=左子树的最大值,那么显然右子树的左子树都会被挡住,就不需要计算.

但是如果右子树的左子树的最大值>左子树的最大值,那么就递归查找左子树,然后加上右子树不会被左子树挡住的答案(节点-左子树答案)
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
inline int gi(){
    int f=1,sum=0;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
struct node{
    double val;
    int ans;
}tree[400010];
int n,m;
void build(int o,int l,int r){
    if(l==r){
        tree[o].val=0;tree[o].ans=1;return;
    }
    int mid=(l+r)>>1;
    build(o<<1,l,mid);build(o<<1|1,mid+1,r);
}
int calc(int o,int l,int r,double val){
    if(l==r)return tree[o].val>val;
    int mid=(l+r)>>1;
    if(tree[o<<1].val<=val)return calc(o<<1|1,mid+1,r,val);
    else return calc(o<<1,l,mid,val)+tree[o].ans-tree[o<<1].ans;
}
void update(int o,int l,int r,int pos,double val){
    if(l==r){tree[o].val=val;tree[o].ans=1;return;}
    int mid=(l+r)>>1;
    if(pos<=mid)update(o<<1,l,mid,pos,val);
    else update(o<<1|1,mid+1,r,pos,val);
    tree[o].val=max(tree[o<<1].val,tree[o<<1|1].val);
    tree[o].ans=tree[o<<1].ans+calc(o<<1|1,mid+1,r,tree[o<<1].val);
}
int main(){
    n=gi();m=gi();//build(1,1,n);
    while(m--){
        int x=gi(),y=gi();
        double v=y*1./x;
        update(1,1,n,x,v);
        printf("%d\n",tree[1].ans);
    }
    return 0;
}
```

---

## 作者：野生蒟蒻 (赞：1)

算是一道字符串模拟

看大佬们的各种算法我就用上了最直接的copy不需要双重枚举

求前缀：从1开始取i个则为：copy（一个字符串，1，i）；

求后缀：以length（一个字符串）-i+1为初值（意为取后面第几个坐标）开始取i个

则为：copy（一个字符串，length（这个字符串）-i+1，i）；

然后两两比较如果相等则进入打擂台

注意这个操作需要进行两次！

代码：

```cpp
var
 s,c,st,ct:string;
 i,j,x,y,n,m,k,t:longint;
begin
 readln(s);
 readln(c);
 for i:=1 to length(s) do//第一次操作
  begin
   st:=copy(s,1,i);//求前缀
   ct:=copy(c,length(c)-i+1,i);//求后缀
   if (st=ct) then if (i>k) then k:=i;//打擂台
  end;
 st:='';
 ct:='';
 for i:=1 to length(c) do//注意这里一定要再次执行一次操作因为题目并没说是第一个字符串的前缀第二个字符串的后缀否则第3个点会WA
  begin
   st:=copy(c,1,i);//求前缀
   ct:=copy(s,length(s)-i+1,i);//求后缀
   if (st=ct) then if (i>k) then k:=i;//打擂台
  end;
 writeln(k);
end.

```

---

## 作者：zxy_hhhh (赞：0)

一串中一段一段截出来，在另一段里搜索是否存在，

如果存在就与最大值比较长度

pascal爆搜来一份


```cpp
var i,j,n,max,l1,max1:longint;
s,t,k:string;
begin
readln(s);
readln(t);  {读入}
l1:=length(s);
for i:=1 to l1 do 
for j:=i to l1 do begin
k:=copy(s,i,j);   {截取字串}
if pos(k,t)>0 then max1:=j-i+1;  {比对}
if max1>max then max:=max1;  {保存最大值}
end;
writeln(max);  {输出}
end.

```

---

