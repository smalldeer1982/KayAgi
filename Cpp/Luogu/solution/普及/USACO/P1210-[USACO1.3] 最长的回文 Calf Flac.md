# [USACO1.3] 最长的回文 Calf Flac

## 题目描述

据说如果你给无限只母牛和无限台巨型便携式电脑（有非常大的键盘 ), 那么母牛们会制造出世上最棒的回文。你的工作就是去寻找这些牛制造的奇观（最棒的回文）。

在寻找回文时不用理睬那些标点符号、空格（但应该保留下来以便做为答案输出）, 只用考虑字母 ${\tt A}\sim {\tt Z}$ 和 ${\tt a}\sim {\tt z}$。要你寻找的最长的回文的文章是一个不超过 $20{,}000$ 个字符的字符串。我们将保证最长的回文不会超过 $2{,}000$ 个字符（在除去标点符号、空格之前）。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 1.3


## 样例 #1

### 输入

```
Confucius say: Madam, I'm Adam. ```

### 输出

```
11
Madam, I'm Adam```

# 题解

## 作者：HJY202three (赞：89)

题目传送门：[P1210 [USACO1.3]最长的回文 Calf Flac](https://www.luogu.com.cn/problem/P1210)

这道题就是找一段话中最长的回文

首先，我们可以看一下样例：

输入：
```
Confucius say: Madam, I'm Adam.
```

输出：
```
11
Madam, I'm Adam
```

## 前置知识：

### 1：字符串基本

在c++中，字符串有两种
### 1.c数组
c数组是c语言中的字符串，也可以在c++中用
例
```cpp
#include<iostream>
using namespace std;
int main()
{
	char a[200];//定义一个c字符串，名为a 
	cin>>a;//输入 
	//scanf("%s",a);
	cout<<a;//输出 
	//printf("%s",a);
	return 0;
 } 
```
注意：在用scanf读入时，没有取地址符
c数组不用加任何多余的头文件，但有个
叫“cstring”的头文件，有更多关于c数组
的函数
```cpp
#include<cstring>
#include<cstdio>
using namespace std;
char a[100],b[100];
int main()
{
	strcpy(a,"I Ak IOI");//将"I AK IOI"拷贝到a中 
	printf("%s,len=%d\n",a,strlen(a));//输出a和a的长度
	scanf("%s",b);
	if(strcmp(a,b)==0)//比较a和b的字典序,a>b返回1,a=b返回0,a<b返回-1
		printf("%s=%s",a,b);
	if(strstr(a,b)!=NULL)//查找字串
		printf("%s is a substr of %s\n",b,a) ;
	return 0;	
 } 
```
### 2.string
c++由于类的存在，引入了string类，需要“string”头文件
例：
```cpp
#include<cstdio>
#include<string>
using namespace std;
int main()
{
	string a;//定义了一个字符串a
	scanf("%s",a) ;//不读空格
   getline(cin,a);//正行读入,可读入空格
	a+="AK IOI";//在a后面接入“AK IOI”
	printf("%d",a.size())//输出a的长度
	printf("%c",a[1])//输出a[1]
	return 0; 
}
```
### 3.如何遍历字符串
由于字符串都是以'\0'结尾，所以可以这样遍历：
```cpp
#include<cstdio>
using namespace std;
char a[]={'I',' ','A','K',' ','I','O','I','\0'};//字符串以\0结尾
int main()
{
	printf("%s",a);
	for(int i=0;a[i]!='\0';i++)//当a[i]不是\0，也就是a没结束 
	{
		/*相关操作*/ 
	}
	return 0;
 } 
```
>选自原来的题解：<https://www.luogu.com.cn/blog/huangjinyang2019/solution-uva1585>

## 2.字符串回文

假设有一个字符串：
```
chenzheakIoIkaehznehc
```
那如何判断这个字符串是不是回文串呢？

首先找到中间值，为length/2
```
chenzheakI|oIkaehznehc
```
然后，我们可以找一下对应关系：
```
c h e n z h e a k I  |  o   I   k    a e h z n e h c
1 2 3 4 5 6 7 8 9 10   1+10 2+10 3+10...
```
于是我们可以发现，第i个元素对应着第i+length/2个元素，假如发现一个不相等的，就return false；

示例代码：
```cpp
bool hui(char[] pur,int length)
{
    for(int i=0;i<length/2;i++)
    {
        if(pur[i+st]!=pur[st+length-i-1])
            return false;
    }
    return true;
}
```
然后有了这些，就可以切题了

# 题目

我们可以分成几个部分

1.读入

我们不知道这个奶牛打的文章有多长，所以可以用大家熟知的while循环+cin.getline读入发。这样遇到EFO~~AFO UFO~~的时候就能停止读入。

但是我们在输出时，换行也要输出。那我们就可以手动加上

例：
```cpp
while(cin.getline(line,88))
{
    strcat(org,line);
    strcat(org,"\n");
}
```
2.处理

题目中说要把除了大小写字母之外的都删除，但输出时又要输出原文，所以我们可以用一个pos数组记录变化前的位置，输出时用它就可以了

例：
```
    int length=strlen(org),pl=0;
    for(int i=0;i<length;i++)
    {
        if(org[i]>='a'&&org[i]<='z')
        {
            pur[pl]=org[i];
            pos[pl]=i;
            pl++;
        }
        if(org[i]>='A'&&org[i]<='Z')
        {
            pur[pl]=org[i]+32;
            pos[pl]=i;
            pl++;
        }
    }
```
3.找回文头和长度

这个我就不详细说了，用两层for循环即可

```
bool chk(int st,int length)
{
    if(st+length>pl)return false;
    for(int i=0;i<length/2;i++)
    {
        if(pur[i+st]!=pur[st+length-i-1])
            return false;
    }
    return true;
}
int maxn=-1,st=0;
for(int i=0;i<pl;i++)//回文头
{
    for(int j=maxn+1;j<=2010;j++)//长度
    {
        if(chk(i,j)&&j>maxn)
        {
            maxn=j;
            st=i;
        }
    }
}
```
4.输出

还记得之前的pos么？现在找出回文头和尾在原始串里的位置，然后输出这一段即可
```
cout<<maxn<<endl;
for(int i=pos[st];i<=pos[st+maxn-1];i++)
{
    cout<<org[i];
}
```
最后上完整程序：
```
#include<iostream>
#include<cstring>
using namespace std;
char org[200001];
char line[90];
int pos[200001];
char pur[200001];
int pl=0;
bool chk(int st,int length)
{
    if(st+length>pl)return false;
    for(int i=0;i<length/2;i++)
    {
        if(pur[i+st]!=pur[st+length-i-1])
            return false;
    }
    return true;
}
int main()
{
    while(cin.getline(line,88))
    {
        strcat(org,line);
        strcat(org,"\n");
    }
    int length=strlen(org);
    for(int i=0;i<length;i++)
    {
        if(org[i]>='a'&&org[i]<='z')
        {
            pur[pl]=org[i];
            pos[pl]=i;
            pl++;
        }
        if(org[i]>='A'&&org[i]<='Z')
        {
            pur[pl]=org[i]+32;
            pos[pl]=i;
            pl++;
        }
    }
    int maxn=-1,st=0;
    for(int i=0;i<pl;i++)
    {
        for(int j=maxn+1;j<=2010;j++)
        {
            if(chk(i,j)&&j>maxn)
            {
                maxn=j;
                st=i;
            }
        }
    }
    cout<<maxn<<endl;
    for(int i=pos[st];i<=pos[st+maxn-1];i++)
    {
        cout<<org[i];
    }
    return 0;
}
```
bye~~

---

## 作者：zqy1018 (赞：38)

c版题解 比较简短

实际上就是枚举从某一个字符开始向两边扩展可得到的回文长度

```cpp
#include <stdio.h>   
#include <ctype.h>
#define N 20005
int at[N],i,n=0,l=0,able(int o),max=0,ls,t;
char k[N]={0},m[N]={0};//k为原字符串，m为新字符串
int able(int o){  //计算回文串长度
    int i,j,a1=1,a2=0;
    for(i=o,j=1;i-j>=0&&i+j<l&&m[i-j]==m[i+j];j++)a1+=2;//取中间一个，奇数长度回文
    for(i=o,j=0;i-j>=0&&i+j+1<l&&m[i-j]==m[i+j+1];j++)a2+=2;//取中间2个，偶数长度回文
    return (a1>a2)?a1:a2;//取最大值
}int main(){
    while((k[n]=getchar())!=EOF)n++;//读取文章
    for(i=0;i<n;i++)if(isalpha(k[i])){
        m[l]=tolower(k[i]);at[l++]=i;//将英文字母转化为小写更好比较，at保存新字符串向原字符串的映射位置
    }for(i=0;i<l;i++){t=able(i);
        if(t>max){max=t;ls=i+(t/2);}//保存回文最后位置
    }k[at[ls]+1]='\0';
    printf("%d\n%s\n",max,&k[at[ls-max+1]]);
    return 0;
}
```

---

## 作者：Raymond_lei (赞：20)

# 洛谷P1210最长的回文 
首先，我刚学C++没多久。其次我不会马拉车。最后我只是一个六年级小学生。所以大佬们可以直接无视

来看这一题，~~他说难也不难，说简单也不简单~~（经典开头）

它第一眼看上去只是一个简单的找回文的题。可是如果再仔细一看你就会发现↓↓

1. 输入的字符串会包括标点符号和空格
1. 判断回文串时又不管标点符号和空格
1. 输出的字符串又包括标点符号和空格

那这题要怎么做呢
## 输入
我们可以用cin.getline()，它可以用来输入整行。不过也有一个问题，它不能输入换行，也就是"/n。所以要加上换行符
## 处理
我们可以定义两个char的字符串，一个来存输入的字符串，一个用来存只有字母的字符串，再定义一个int的数组，来存每个字母的位置。然后在判断回文
## 输出
不解释   ~~自己动动脑子~~

# 然后就是代码
```cpp

#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

char line[105];
char yuan[20005];
char del[20005];
int pos[20005];
int mx = 0;
int t;
int len_y;
int len_d;

bool huiwen(int x,int y)
{
	if(x + y - 1 >= len_d)	return 0;
	for(int i = 0;i < y;i++)
	{
		if(del[i + x] != del[x + y - i - 1]) return 0;
	}
	return 1;
}

int main()
{
	while(cin.getline(line,85))
	{
		strcat(yuan,line);
		strcat(yuan,"\n");
	}
	len_y = strlen(yuan);
	
	len_d = 0;
	for(int i = 0;i < len_y;i++)
	{
		if(yuan[i] >= 'a' && yuan[i] <= 'z')
		{
			del[len_d] = yuan[i];
			pos[len_d] = i;
			len_d++;
		}
		if(yuan[i] >= 'A' && yuan[i] <= 'Z')
		{
			del[len_d] = yuan[i] - 'A' + 'a';
			pos[len_d] = i;
			len_d++;
		}		
	}
	
	

	for(int i = 0;i < len_d;i++)
	{
		for(int j = mx + 1;j < 2005;j++)
		{
			if(huiwen(i,j))
			{
				mx = j;
				t = i;
			}
		}
	}
	cout << mx << endl;
	for(int i = pos[t];i <= pos[t + mx - 1];i++)
		printf("%c",yuan[i]);
	return 0;	
}
```
别抄啊

---

## 作者：逆时针的记忆 (赞：12)

你是否也和我一样在寻找不是暴力的题解，可惜没有，那我就来一篇。  
如果能做到这题，后缀数组一定也有了一定的接触，我看了一下这题题解，都是暴力求解，所以我这里将提供暴力（更简洁）和正解（后缀数组）

#### 暴力出奇迹
```cpp
//这个暴力像多位大佬所说，用两个指针l，r处理，暴力以每个字符为中心，向两边扩展，只不过看了一下，我这篇更好理解（对我来说z
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
char str[200005],c[20005];
int s[20005],anslen=1,ansst,ansen;
int main()
{
	int i=-1,j,len,L=-1,l,r;
	while (scanf ("%c",&str[++i])!=EOF)
	{
		if (str[i]>='A'&&str[i]<='Z') c[++L]=str[i]+32,s[L]=i;
		else if (str[i]>='a'&&str[i]<='z') c[++L]=str[i],s[L]=i;
	}//将输入换成小写统一，s[]用来记录换成小写后字符在原字符串中的位置
	for (i=1; i<L; i++)//L为处理后字符串，全部为小写
	{
		bool flag=true;
		int tmp=1;
		l=i; r=i;
		while (true)
		{
			if (l<0||r>L) break;
			if (c[l-1]==c[r+1]) tmp+=2,l--,r++;
			else if (c[l-1]==c[r]&&flag) tmp++,l--;
			else if (c[l]==c[r+1]&&flag) tmp++,r++;
			else break;//如果不是回文串就break；
			flag=false;
		}//这里的flag很巧妙，主要是特判一种例如aa这种形式的回文串，自己想想为什么flag控制的两个if语句只能在第一次使用
		if (tmp>anslen) anslen=tmp，ansst=s[l]，ansen=s[r];
		}
	}
	printf ("%d\n",anslen);
	for (i=ansst; i<=ansen; i++) printf ("%c",str[i]);
	printf ("\n");
	return 0;
}
```
#### 正解史无前例

```cpp
//如果所学没有涉及，就忽略此篇
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int ans,height[100010],sa[100010],rank[100010],c[100010],tmp[100010],n,x[100010];
char s[100010],str[100010];
void makesa()//后缀数组
{
	int i,j,na,len;
	na=max(256,n);
	memset(c,0,na*sizeof(int));
	for (i=0; i<n; i++) rank[i]=s[i]&0xff,c[rank[i]]++;
	for (i=1; i<na; i++) c[i]+=c[i-1];
	for (i=0; i<n; i++) sa[--c[rank[i]]]=i;
	for (len=1; len<n; len<<=1)
	{
		for (i=0; i<n; i++)
		{
			j=sa[i]-len;
			if (j<0) j+=n;
			tmp[c[rank[j]]++]=j;
		}
		sa[tmp[c[0]=0]]=j=0;
		for (i=1; i<n; i++)
		{
			if (rank[tmp[i]]!=rank[tmp[i-1]]||rank[tmp[i]+len]!=rank[tmp[i-1]+len]) c[++j]=i;
			sa[tmp[i]]=j;
		}
		memcpy(rank,sa,n*sizeof(int));
		memcpy(sa,tmp,n*sizeof(int));
		if (j>=n-1) break;
	}
}//sa[i]排名为i的后缀开始字符的下标
//rank[i]开始字符下标为i的后缀的排名
//这里排名为从小到大，还有rank最好换成其他名字，否则可能会 compile error
void lcp()//最长公共前缀，自己了解
{
	int k=0,i,j;
	for (i=0; i<n; i++)
	{
		if (k) k--;
		j=sa[rank[i]-1];
		while (s[i+k]==s[j+k]) k++;
		height[rank[i]]=k;
	}
}

int main()
{
	int i=-1,j,st,en,L=-1,len;
	while (scanf ("%c",&str[++i])!=EOF)
	{
		if (str[i]>='A'&&str[i]<='Z') s[++L]=str[i]+32,x[L]=i;
		else if (str[i]>='a'&&str[i]<='z') s[++L]=str[i],x[L]=i;
	}//作用同上
	s[++L]='$'; len=j=L;//在这里$为akcii较小的一个字符，改为空格也可以，或者其他
	for (i=L; i<=2*L; i++) s[i]=s[j--];//将处理后的字符串反着接到处理后的数组上
	s[2*L+1]=' ';//注意，这里空格是因为不能和上面的$重复，否则会影响到结果。
	n=strlen(s);
	makesa(); lcp();
	for (i=1; i<n; i++)
		if ((sa[i]<len&&sa[i-1]>len)||(sa[i]>len&&sa[i-1]<len))
        //加上接上的那部分s数组可以分为two parts。最长的公共前缀将一个回文串也分为两个部分，如果最长公共前缀在同一部分，得出的答案例如abcabc电脑都会当作一个回文串，所以不能在一个部分，否则得出来的答案不是正解，纸短话多，说不完，在纸上推一下就ok
		{
			if (height[i]>ans||(height[i]==ans&&x[min(sa[i],sa[i-1])]<st)) ans=height[i],st=x[min(sa[i],sa[i-1])],en=x[min(sa[i-1],sa[i])+ans-1];
		}//在这里之所以要取最小值是因为sa记录，你不知道谁在前，谁在后，min(sa[i-1],sa[i])+ans-1就是长度为ans的字符串的终点坐标
        //还有if语句的第二个判断依据是如果长度相同，就优先输出前面的一个字符串
	printf ("%d\n",ans);
	for (i=st; i<=en; i++) printf ("%c",str[i]);//st en 记录同上
	printf ("\n");
	return 0;
}
```



---

## 作者：Godのfather (赞：9)

## C++版  （二分答案）
----
我看很多DALAO都是由单个字符向两边拓展来枚举最长回文，现在发一篇二分答案的题解，希望对大家有帮助！

我看到这道题的第一想法是枚举答案 ~~（长度）~~ 

但是很显然会超时，怎样优化枚举是关键

我想到了二分答案。但是二分答案要求答案具有单调性。

乍一看，似乎回文子串没什么单调性。但是如果我们将答案分为奇偶两种，答案的单调性就出来了

1.当最长回文串长度是奇数时：

不妨假设长度为9，那么我们就会发现，9以下的奇数长度 ~~（1,3,5,7）~~ 都是存在回文串的，奇数的单调性我们找到了

2.当回文串为偶数时
同理，设长度为6，6以下的偶数长度 ~~（2,4）~~ 也都是可以的。

~~然后我们就可以开始二分了~~

相信写程序对各位DALAO不是问题，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=20005;
string s,t;int len1;
int begin,end;
int ans;
struct node
{
    char S;
    int start;
}st[maxn];
bool ok(int x,int y)
{
    int rt=x,lt=y;
    while(rt<=lt)
    {
        if(st[rt].S!=st[lt].S) return false;
        rt++,lt--; 
    }
    return true;
}
bool add(int x)
{
    int head=1,tail=x;
    while(tail<=len1)
    {
        if(ok(head,tail))
        {
           begin=st[head].start;
           end=st[tail].start;
           return true;
        }
        head++,tail++;
    }
    return false;
}
int main()
{
    while(getline(cin,t))//注意读入数据的处理 
    {
        s+=t+'\n';
    };
    s=' '+s;
    int len=s.size()-1;
    for(int i=1;i<=len;i++)
    {
        if(s[i]>='A'&&s[i]<='Z') st[++len1].S=s[i]-'A'+'a',st[len1].start=i;//改小写 
        else if(s[i]>='a'&&s[i]<='z') st[++len1].S=s[i],st[len1].start=i; 
    }
    int lt=0,rt;
    if(len1%2==0) rt=len1;
    else rt=len1+1;
    while(lt+2<rt)//二分奇数  特别注意 lt+2 
    {
        int mid=(lt+rt)/2;
        if(mid%2==0) mid++;
        if(add(mid)) lt=mid;
        else rt=mid;
    }
    int b=begin,e=end;
    ans=lt;
    lt=1;
    if(len1%2==0) rt=len1+1;
    else rt=len1;
    while(lt+2<rt)//二分偶数  
    {
        int mid=(lt+rt)/2;
        if(mid%2==1) mid++;
        if(add(mid)) lt=mid;
        else rt=mid;
    }
    if(ans>lt)//比较大小 
    {
        cout<<ans<<endl;
        for(int i=b;i<=e;i++)
           cout<<s[i];
    }
    else 
    {
        cout<<lt<<endl;
        for(int i=begin;i<=end;i++)
           cout<<s[i];
    }
    return 0;
}
```

---

## 作者：顾z (赞：8)

题目描述--->[P1210 回文检测](https://www.luogu.org/problemnew/show/P1210)

## 广告： [安利blog](https://www.luogu.org/blog/RPdreamer/#)
## 分析:

看到回文显然想到了**manacher算法**(**线性求解**回文串问题

如果不了解还是去敲一下板子,学习一下比较好.-->[manacher](https://www.luogu.org/problemnew/show/P3805)

题目要求我们求出只包含字母的回文串的长度.

如果你会manacher,这很简单.

只需要**在输入之后处理一下我们得到的串**即可.

**这题的难点在于,如何输出原串**

---

**吐槽**

本来以为求出我们的最长回文半径的最中间的位置的字符,判断其左右两侧遇到的第一个字符是否相等,如果相等我们就可以一直扩展过去,直至无法匹配.

感觉这种被卡的概率还是很低的...

兴冲冲地码了100多行.然而还是被卡了,绝望地很.

---

## 解决

**首先明确：**
	
    s数组为我们的原字符数组.
    str数组为我们只含有大写(小写)字母的字符数组
    ss数组为我们用于跑manacher的字符数组

**因此考虑去记录字符在原数组中的位置.**

很容易将我们转化后的数组记录.
这样记录↓
```cpp
for(RI i=0;i<l;i++)//l为我们原串长度,从l=0开始记录.
    {
        if((s[i]>='a' and s[i]<='z') or (s[i]>='A' and s[i]<='Z'))
        str[len]=s[i],pos[len]=i,len++;
        //我们只存储为字母的情况.
    }
```

**处理**我们得到的数组↓

```cpp
for(RI i=0;i<len;i++)
    {
        if(str[i]>='a' and str[i]<='z')
            str[i]-=32;
    }//在这里将小写转为大写.
    //也可以将大写转为小写
    //视个人爱好而定.
```

此时我们已经记录了某一位置对应的原串位置.

接下来就是我们的manacher操作了!

**处理**我们用于manacher的数组↓
```cpp
for(RI i=0;i<len;i++)ss[2*i+1]=str[i];
    ll=2*len+1;//这里记得变换长度.
//这里我并没有进行插入字符的操作
//是因为我们的字符数组默认为空.
//这样的处理操作会使得中间空出一些位置.从而达到插入字符的效果.
```

我们现在需要考虑的是**如何对我们用于manacher操作的数组进行标记操作**,即对应原串位置.

因为我们用于manacher的数组ss[2*i+1]对应str[i],
所以我们的数组poss[2*i+1]也会对应pos[i].

所以我们的答案就很明显了.

	最左端位置就是le=i-(RL[i]-1)+1
	最右端位置就是ri=i+(RL[i]-1)-1
    其中RL[i]-1代表以i为对称轴的回文子串长度
    
所以我们**枚举poss[le]到poss[ri]输出答案**即可.

--------------------代码--------------------

```cpp
#include<bits/stdc++.h>
#define IL inline
#define RI register int
char s[200008],str[200008],ss[400008];
int l,len,pos[200008],RL[200008],ll,ans,le,ri,poss[200008];
int main()
{
    while(~(s[l]=getchar())){l++;}//输入还是看了其他人的 emmmm,自己写的一个炸了 emmm
    for(RI i=0;i<l;i++)
    {
        if((s[i]>='a' and s[i]<='z') or (s[i]>='A' and s[i]<='Z'))
        str[len]=s[i],pos[len]=i,len++;
    }
    for(RI i=0;i<len;i++)
    {
        if(str[i]>='a' and str[i]<='z')
            str[i]-=32;
    }
    int MaxRight=0,center=0;RL[0]=1;
    for(RI i=0;i<len;i++)ss[2*i+1]=str[i],poss[2*i+1]=pos[i];//这里的对应操作.
    ll=2*len+1;
    for(RI i=1;i<ll;i++)
    {
        if(i<=MaxRight)
            RL[i]=std::min(RL[2*center-i],MaxRight-i);
        else RL[i]=1;
        while(i-RL[i]>=0 and i+RL[i]<ll and ss[i+RL[i]]==ss[i-RL[i]])
            RL[i]++;
        if(i+RL[i]-1>MaxRight)MaxRight=i+RL[i]-1,center=i;
        if(RL[i]-1>ans)
        {
        	ans=RL[i]-1;
        	le=i-RL[i]+2;
        	ri=i+RL[i]-2;
        }
    }
    printf("%d\n",ans);
    for(RI i=poss[le];i<=poss[ri];i++)std::cout<<s[i];
}
```

---

## 作者：OItby (赞：7)

$PS:$
- 更好的浏览效果[[Luogu1210] 回文检测](https://www.cnblogs.com/hihocoder/p/12209301.html)

- $Q$:咋都不用**后缀数组**？？？

------

后缀数组模板中的$Lcp$可以求出$Height[]$，由此可以知道两个相邻名次的最长公共前缀，好像这题和这个有点沾边……

我们可以把原串化为**大小写统一的的字母串**，然后在末尾加一个奇特字符或**赋一个特殊值**，最后将它反转赋值到末尾，按照后缀模板加**另一个特殊值**

求出经过上述处理后的串的$height[]$，在求出最长前缀即可

$PS:$关于$id$数组的技巧请读者另行思考

------

$My~code$(自认为代码简单)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N=50000;
int n,ln,id[N],sa[N],rk[N],tmp[N],c[N],height[N];
string ss;
char s[N];

void Read()//读入加反转
{
	string str;
	for(getline(cin,ss);getline(cin,str);ss+='\n'+str);
	int len=ss.length();
	n=0;
	for(int i=0;i<len;++i)
	{
		if(ss[i]>='a'&&ss[i]<='z')
			s[n]=ss[i],id[n]=i,++n;
		if(ss[i]>='A'&&ss[i]<='Z')//字符要统一大小写
			s[n]=ss[i]+'a'-'A',id[n]=i,++n;
	}
	for(int i=0;i<n;++i) s[n+n-i]=s[i];
	s[n]=2,s[n+n+1]=1;
	ln=n,n=n+n+2;
}

void Make_Sa()//后缀数组的模板——求sa[]与rank[]
{
	int i,j,len,na;
	na=256;
	memset(c,0,na*sizeof(int));
	for(i=0;i<n;++i)
	{
		rk[i]=s[i]&0xff,
		++c[rk[i]];
	}
	for(i=1;i<na;++i) c[i]+=c[i-1];
	for(i=0;i<n;++i)
	{
		--c[rk[i]],
		sa[c[rk[i]]]=i;
	}
	for(len=1;len<n;len<<=1)
	{
		for(i=0;i<n;++i)
		{
			j=sa[i]-len;
			if(j<0) j+=n;
			tmp[c[rk[j]]++]=j;
		}
		c[0]=0,j=0,
		sa[tmp[0]]=0;
		for(i=1;i<n;++i)
		{
			if(rk[tmp[i]]!=rk[tmp[i-1]]
			||rk[tmp[i]+len]!=rk[tmp[i-1]+len])
				c[++j]=i;
			sa[tmp[i]]=j;
		}
		memcpy(rk,sa,n*sizeof(int)),
		memcpy(sa,tmp,n*sizeof(int));
		if(j>=n-1) break;
	}
}

void Lcp()//后缀数组的模板——求Height[]
{
	int i=0,j,k=0;
	height[0]=0;
	for(j=rk[0];i<n-1;++i,++k)
		for(;k>=0&&s[i]!=s[sa[j-1]+k];)
		{
			height[j]=k, --k;
			j=rk[sa[j]+1];
		}
}

void PutAns()
{
	int ID=0,Ans=0;
	for(int i=1;i<n;++i)
	{
		if(sa[i]<ln&&sa[i-1]>ln)//必须一个为原字母串，另一个为反转字母串
			if((height[i]>Ans)
			||(height[i]==Ans&&sa[i]<ID))//坑点：还有字母最靠前
				Ans=height[i],ID=sa[i];
		if(sa[i]>ln&&sa[i-1]<ln)
			if(height[i]>Ans
			||(height[i]==Ans&&sa[i-1]<ID))
				Ans=height[i],ID=sa[i-1];
	}
	printf("%d\n",Ans);
	for(int i=id[ID];i<=id[ID+Ans-1];++i)//id的巧处
		printf("%c",ss[i]);
}

int main()
{
	Read(),Make_Sa(),Lcp(),PutAns();
	return 0;
}
```

---

## 作者：ghj1222 (赞：7)

# Manacher

正确读法：抹内A撤(马拉车)

(跟着假硕学英语)

我们把原来的字符串，通过玄学处理，变成只留下字母，且每两个字母之间有一个奇怪的字符的那种Manacher专用字符串。

建立双射关系`f[i]`表示`a[i]`在b中的位置（如果`a[i]`是字母），`f_[i]`表示`b[i]`在a中的位置（如果`b[i]`是字母）

然后对b数组跑Manacher

然后找最长回文子串回文中心的位置，通过这个位置直接在b数组中先找左右端点，然后在找到a数组中对应位置输出

数组要开到四万（下面的代码开了两万RE一个点，想抄题解的自己改一下）：

```cpp
#include <bits/stdc++.h>
using namespace std;

char a[20010], b[20010];
int f[20010], f_[20010], res[20010];

int main()
{
    int p = 0;
    while((a[p] = getchar())!=EOF)p++;
    a[p]=0;
    int len = strlen(a), j = 1;
    memset(b, 0x25, sizeof(b));
    for (int i = 0; i < len; i++)
    {
        if(isalpha(a[i]))
        {
            f[i] = j;
            f_[j] = i;
            b[j] = a[i];
            if(islower(b[j]))
                b[j] -= 32;
            j+=2;
        }
    }
    //从[0,j)跑马拉车
    int more = 0, pos = 0;
    for (int i = 0; i < j; i++)
    {
        if (more > i)
            res[i] = min(res[2 * pos - i], more - i);
        else
            res[i] = 1;
        while (i + res[i] < j && i - res[i] >= 0 && b[i+res[i]] == b[i-res[i]])
            res[i]++;
        if (i + res[i] - 1 > more)
        {
            more = i + res[i] - 1;
            pos = i;
        }
    }
    int maxLengthPos = 0;
    for (int i = 1; i < j; i++)
        if(res[i] > res[maxLengthPos])
            maxLengthPos = i;
    int r = maxLengthPos + res[maxLengthPos] - 2, l = maxLengthPos - res[maxLengthPos] + 2;
    int L = f_[l], R = f_[r];
    //printf("%d %d %d %d\n", l, r, L, R);
    printf("%d\n", 1 + (r - l) / 2);
    for (int i = L; i <= R; i++)
        printf("%c", a[i]);
    return 0;
}
```

让我们一起膜拜大佬林瑞堂@[olinr](https://www.luogu.org/space/show?uid=88460)


---

## 作者：童年如作业 (赞：7)

#### 题目正解之 优化枚举
这道题的意思就是：给你一 ~~坨~~ 堆字符串，其中包括各种奇葩符号，甚至还有空串（纯换行）的可能，当然，我们只需记住那些字母（不区分大小写），然后在其中找最长的回文字串。
对于如何读入，详情看程序，一定要用in、out文件，不然就会无限读入。我试过判断空串停止，会WA一个点。
#### 进入正题 解题思路
首先看到找最长回文字串，你会想到枚举这个算法。但是我们看看：字符文章长度20000，枚举需要优化！！！
仔细看，题目中有个 **最长的回文不会超过2,000个字符** 为什么要提供这个看似没用的提示呢？于是，我们可以从这个看出来：枚举优化的突入口就在这里!!!长度只有两千，我们可以枚举中间点，分奇偶两种情况讨论，奇数：12**3**21，偶数1**3**31。（3为中间点）
#### 程序
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
int x[20002],y[20002];//记录p字符串里面每个字符对应s字符串数组的位置，便于输出
string s[20002],p;
int main()
{
    //freopen("calfflac.in","r",stdin);
    //freopen("calfflac.out","w",stdout);
    int k=-1,ans=0,ansx1=0,ansy1=0,ansx2=0,ansy2=0;
    for(int i=1;getline(cin,s[i]);i++)//读入加字符串缩减处理
    {
        for(int j=0;j<s[i].size();j++)
        {
            if(s[i][j]>='a'&&s[i][j]<='z')
            {
                p+=s[i][j];
                k++;
                x[k]=i;
                y[k]=j;//记录位置，以下一样
            }
            if(s[i][j]>='A'&&s[i][j]<='Z')
            {
                p+=s[i][j]-'A'+'a';//全部转小写
                k++;
                x[k]=i;
                y[k]=j;
            }
        }
    }//注意，我这个答案测试得用in、out文件，不然……无限输入
    for(int i=0;i<p.size();i++)
    {
        int l=i,r=i,sum=1,tx1=x[i],tx2=x[i],ty1=y[i],ty2=y[i];
        for(;l>=0&&r<p.size();l--,r++,sum+=2)//第一种情况，奇数：中间不用判断，绝对自身回文，有一个
        {
            if(p[l-1]!=p[r+1])
            {
                tx1=x[l];
                ty1=y[l];
                tx2=x[r];
                ty2=y[r];
                break;
            }//不是回文就退出
        }
        if(sum>ans)//比较，看哪个大
        {
            ans=sum;
            ansx1=tx1,ansx2=tx2;
            ansy1=ty1,ansy2=ty2;//记录方位及大小
        }
        if(p[i]==p[i+1])//偶数需要特判，可能下一个无法构成回文
        {
            l=i,r=i+1,sum=2,tx1=x[i],tx2=x[i+1],ty1=y[i],ty2=y[i+1];
            for(;l>=0&&r<p.size();l--,r++,sum+=2)//看这个回文字符串有多长
            {
                if(p[l-1]!=p[r+1])
                {
                    tx1=x[l];
                    ty1=y[l];
                    tx2=x[r];
                    ty2=y[r];
                    break;
                }
            }
            if(sum>ans)
            {
                ans=sum;
                ansx1=tx1,ansx2=tx2;
                ansy1=ty1,ansy2=ty2;
            }
        }
    }
    printf("%d\n",ans);
    for(int i=ansx1;i<=ansx2;i++)//分多种情况输出
    {
        if(i==ansx1&&ansx1==ansx2)//在同一行的话，直接从头输到记录的尾
        {
            for(int j=ansy1;j<=ansy2;j++)
            {
                cout<<s[i][j];
            }
        }
        else if(i==ansx1)//第一行需要输出头到这一行的尾
        {
            for(int j=ansy1;j<s[i].size();j++)
            {
                cout<<s[i][j];
            }
        }
        else if(i==ansx2)//尾行要输出这一行的头到记录的尾
        {
            for(int j=0;j<=ansy2;j++)
            {
                cout<<s[i][j];
            }
        }
        else//既不是头，也不是尾，直接输出这一行
        {
            cout<<s[i];
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：ShineEternal (赞：2)

看到其他解法都是dp，马拉车等等，虽然有一篇和我的思路差不多，但是代码实现上有些差别，所以来分享一下。

# 分析：
如果我们枚举左右端点的话，时间复杂度就接近立方级别，于是我们利用回文串的性质，可以根据它的对称中心了枚举，大体能降到平方级别。

> code
```cpp
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
struct ben
{
	char cha;
	int num;
}a[20100];
int main()
{
	string line;
	string s;
	while(getline(cin,line))
	{
		s+=line;
		s+="\n";
	}
	int cnt=0;
	for(int i=0;i<s.length();i++)
	{
		if(isalpha(s[i]))
		{
			a[cnt].cha=toupper(s[i]);
			a[cnt].num=i;
			cnt++;
		}
	}
	int ans=0,l,r;
	for(int i=0;i<cnt;i++)
	{
		int j=1,sum=1;
		while(i>=j&&i+j<cnt)
		{
			if(a[i-j].cha==a[i+j].cha)
			{
				sum+=2;
				if(sum>ans)
				{
					ans=sum;
					l=i-j;
					r=i+j;
				}
			}
			else
			break;
			j++;
		}
		j=0,sum=0;
		while(i>=j&&i+j+1<cnt)
		{
			if(a[i-j].cha==a[i+j+1].cha)
			{
				sum+=2;
				if(sum>ans)
				{
					ans=sum;
					l=i-j;
					r=i+j+1;
				}
			}
			else
			break;
			j++;
		}
	}
	int last=0; 
	for(int i=a[l].num;i<=a[r].num;i++)
	{
		if(isalpha(s[i]))last++;
	}
	printf("%d\n",ans);
	for(int i=a[l].num;i<=a[r].num;i++)cout<<s[i];
	return 0;
} 
```

**关于读入输出的代码优化借鉴了网上一篇blog，在此orz一下**

---

## 作者：_gjm2005_ (赞：2)

先把回文字符分一下类，当长度是奇数时，该串是由中间一个向外扩展的，例如gjmjg。当长度是偶数时，该串是由中间两个向外扩展的，例如gjmmjg。我们这题的思路就是给一个位置，向外扩展。

在work函数中我们分了两类来扩展，看看长度是多少，j为扩展出去了几个。
讲一下本蒟蒻在减少代码量下的功夫：a数组可用的字母的序号（1-26）。储存答案串时只储存了开头和结尾的位置（在a数组中）最后输出时有个num看看它之前有几个可用的字符，这是为了配合储存串的方式。
```cpp
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
using namespace std;

const int NR = 20010;

char c[NR];
int a[NR],t = 0;
int ans = 0;
int pos,pos2;
void work(int i)
{
  if(a[i] == a[i - 1])
  {
  	int sum = 2,temp = 0;
  	for(int j = 1;i + j  <= t && i - 1 - j >= 1;j++)
  	{
	  if(a[i + j] != a[i - 1 - j]) break;
	  temp = j,sum += 2;	
	}
	if(sum > ans) ans = sum,pos = i - temp - 1,pos2 = i + temp;
  }
  int sum = 1,temp = 0;
  for(int j = 1;i + j <= t && i - j >= 1;j++)
  {
  	if(a[i + j] != a[i - j]) break;
  	temp = j,sum += 2;
  }
  if(sum > ans) ans = sum,pos = i - temp,pos2 = i + temp;
}

int main()
{
  //freopen("test.in","r",stdin);
  //freopen("test.out","w",stdout);
  int t1 = 0;
  while(scanf("%c",&c[++t1]) != EOF)
  {
  	if(c[t1] >= 'a' && c[t1] <= 'z') a[++t] = c[t1] - 'a'+ 1;
  	if(c[t1] >= 'A' && c[t1] <= 'Z') a[++t] = c[t1] - 'A' + 1;
  }
  for(int i = 2;i <= t;i++) work(i);
  int num = 0;
  printf("%d\n",ans);
  for(int i = 1;i <= t1;i++)
  {
  	if((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z'))
	  num++;
  	if(num >= pos && num <= pos2) printf("%c",c[i]);
  	if(num == pos2) break;
  }
  return 0;
}

```

---

## 作者：汇文客 (赞：2)

这是一道简单的字符串处理题，把字母一个个筛出来即可。求回文，注意奇数长度与偶数长度两种情况。

```delphi

type node=record
     c:char;
     w:longint;
end;
var st,s:ansistring;
    a:array[1..20000]of node;
    i,m,n,l,r,ans:longint;
    ch:char;
begin
  st:='';i:=0;n:=0;
  while not eof do
  begin
    read(ch);inc(n);
    st:=st+ch;
    if(ch>='A')and(ch<='Z')then
    begin
      inc(i);
      a[i].c:=ch;
      a[i].w:=n;
    end else
    if(ch>='a')and(ch<='z')then
    begin
      inc(i);
      a[i].c:=chr(ord(ch)-32);
      a[i].w:=n;
    end;       //IF CH='1' THEN BREAK;
  end;
  m:=i;ans:=0;
  for i:=1 to m do
  begin
    l:=i;r:=i;
    while(l>1)and(r<m)and(a[l-1].c=a[r+1].c)and(l>1)and(r<m)do
    begin inc(r);dec(l);end;
    if ans<r-l+1 then
    begin s:=copy(st,a[l].w,a[r].w-a[l].w+1);ans:=r-l+1;end;
    if(i<>m)and(a[i].c=a[i+1].c)then
    begin
      l:=i;r:=i+1;
      while(l>1)and(r<m)and(a[l-1].c=a[r+1].c)and(l>1)and(r<m)do
      begin inc(r);dec(l);end;
      if ans<r-l+1 then
      begin s:=copy(st,a[l].w,a[r].w-a[l].w+1);ans:=r-l+1;end;
    end;
  end;
  writeln(ans);
  writeln(s);
end.

```

---

## 作者：hovny (赞：1)

## [题面](https://www.luogu.org/problemnew/show/P1210)

~~这是一道诡异的黄题~~

居然让你求一串吧啦吧啦的东西中 字母（大小写）最长的回文串的长度，还要输出完整的串  ~~吐血~~

## 思路：

保持淡定，我们啥都不会，就会Manacher，那就用**Manacher**大法！

1、把字符串处理成只有字母（去皮）

2、把字符串中插入`#`号（掺假）

3、Manacher跑一跑最长回文串长度（市场检查）

4、求出最长长度后再重新代入原来的字符串（打回原形！妖孽！）

然后，就完了~

就是`去皮`的时候，顺便记录一下字符的位置，这样重新代入时就比较方便

并且由于字符串有很多行，读入时就要用`getchar()`，直到`EOF`为止

~~似乎Noip2018普及T1有人因为这个WA？~~

Code：

```cpp
#include<bits/stdc++.h>
#define M 20010
using namespace std;
struct node{
	char c;
	int id;
}a[M<<1];
char st[M],s[M<<1];
int l1,l2,len,ans,res;
int p[M<<1];
bool check(char c)
{
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}
void init()
{
	int i;
	for(i=0;i<l1;i++)
		if(check(st[i]))
		{
			a[l2].c=(st[i]>='a'&&st[i]<='z')? st[i]:st[i]-'A'+'a';
			a[l2++].id=i;//记录编号（位置）
		}
	s[0]='!';
	s[1]='#';
	for(i=0;i<l2;i++)
	{
		s[i*2+2]=a[i].c;
		s[i*2+3]='#';
	}
	len=l2*2+2;
	s[len]='?';
	return;
}
void manacher()//大法不解释
{
	int id=0,mx=0;
	for(int i=0;i<len;i++)
	{
		if(i<mx)
			p[i]=min(p[id*2-i],mx-i);
		else
			p[i]=1;
		while(s[i-p[i]]==s[i+p[i]])
            	p[i]++;
		if(i+p[i]>mx)
		{
			id=i;
			mx=i+p[i];
		}
	}
	return;
}
void Print(int l,int r)
{
	if(l&1)//由扩展后的s数组变回a数组
		l=(l-3)/2;
	else
		l=(l-2)/2;
	if(r&1)
		r=(r-3)/2;
	else
		r=(r-2)/2;
	for(int k=a[l].id;k<=a[r].id;k++)
		printf("%c",st[k]);
	return;
}
int main()
{
	int i;
	char c=getchar();//读入
	while(c!=EOF)
	{
		st[l1++]=c;
		c=getchar();
	}
	init();//初始化
	manacher();//大法
	for(i=0;i<len;i++)//求最长
		ans=max(ans,p[i]);
	for(i=0;i<len;i++)//求第一次出现的位置
		if(p[i]==ans)
			break;
	ans--;
	printf("%d\n",ans);
	Print(i-ans+1,i+ans-1);//重新代入
	return 0;
}
```



---

## 作者：q1293274675 (赞：1)

基本就是裸的Manacher,我看题解中好像暴力搜也可以过（什么！！）但是我还是写了个很快的Manacher= =。大家感受下，可能比较难懂，但是绝对很快。（当然，感谢楼下的读取方法，好像用scanf不太行的样子（一定是我太弱了qwq））



```cpp
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int Min(int a,int b){return a<b?a:b;}
const int N=20005;
char st[N],st2[N],s_new[2*N];
int p[2*N],pos[N],pos2[2*N],t,t2,lf,ri;
int query(){
    int j=2;
    s_new[0]='$';s_new[1]='#';
    for(int i=0;i<=t2;i++){
        s_new[j]=st2[i];pos2[j]=pos[i];j++;
        s_new[j++]='#';
    }
    s_new[j]='\0';
    return j;
}
int Manacher(){
    int len=query();
    int maxx=0,maxlen=-1,id;
    for(int i=1;i<len;i++){
        if(i<maxx)p[i]=Min(p[2*id-i],maxx-i);
        else p[i]=1;
        while(s_new[i-p[i]]==s_new[i+p[i]])p[i]++;
        if(maxx<i+p[i])maxx=i+p[i],id=i;
        if(maxlen<p[i]-1){
            maxlen=p[i]-1;
            lf=i-p[i]+2;
            ri=i+p[i]-2;
        }
    }
    //for(int i=1;i<len;i++)printf("%c ",s_new[i]);printf("\n");
    //for(int i=1;i<len;i++)printf("%d ",pos2[i]);printf("\n");
    return maxlen;
}
int main()
{
    while((st[t]=getchar())!=EOF)t++;t--;
    for(int i=0;i<=t;i++)if((st[i]<='z'&&st[i]>='a')||(st[i]<='Z'&&st[i]>='A'))st2[t2]=st[i],pos[t2]=i,t2++;t2--;
    for(int i=0;i<=t2;i++)if(st2[i]<='Z'&&st2[i]>='A')st2[i]=st2[i]-'A'+'a';
    printf("%d\n",Manacher());
    //printf("%c %c\n",s_new[lf+1],s_new[ri-1]);printf("%d %d\n",pos2[lf],pos2[ri]);
    for(int i=pos2[lf];i<=pos2[ri];i++)printf("%c",st[i]);printf("\n");
    return 0;
}
```
/\*
Confucius say: Madam, I'm Adam.

\*/

---

