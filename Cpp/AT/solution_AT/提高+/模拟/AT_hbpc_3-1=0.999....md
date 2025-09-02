# 1=0.999...

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hbpc2012/tasks/hbpc_3

1 と 0.999... がまったく同じ実数を表すということは、 ネット上でもしばしば議論される話題です。  
 この問題は、そんな小数に関する問題です。 入力は以下の形式に従う。

> $ N $ $ a_1 $ $ a_2 $ : $ a_N $

 1行目には、与えられる小数の数 $ N $ が与えられる。 2行目から続く $ N $ 行では、実数 $ a_i $ が与えられる。  
 $ a_i $ は有限小数または循環小数であり、実数の集合 $ A\ =\ {a_i} $ のすべての要素を表す。 $ 1 $ つの実数が異なる表記で与えられる場合がある。  
 有限小数および循環小数は以下のBNFに従う。 循環小数において括弧で囲まれた部分は循環節を表し、 例えば `0.(01)` は $ 0.010101... $ を表現する。  
```
<pre style="font-family: monospace;letter-spacing:0;">
 ::=  "." 
 ::=  "."  "("  ")"
   ::= "0" |  
      ::= "" | 
      ::=  
    ::= "0" | 
    ::= "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

- $ 1\ ≦\ N\ ≦\ 300 $
- $ a_i $ の文字列長は $ 300 $ 以下
 
 実数の集合 $ A $ の要素数を求めよ。 ```
<pre class="prettyprint linenums">
2
1.0
0.(9)
```

 ```
<pre class="prettyprint linenums">
1
```

 ```
<pre class="prettyprint linenums">
3
3.(142857)
3.1(428571)
3.14(285714)
```

 ```
<pre class="prettyprint linenums">
1
```

# 题解

## 作者：Rigel (赞：12)

水蓝，建议降黄。

## 思路

对于每个输入的实数，开一个数组存储每一位的值，其中 $1$ 至 $300$ 位存储小数点前的数位，$301$ 至 $600$ 位存储小数点后的数位。处理循环节后，处理最后若干位都是 $9$ 的情况。

处理完毕后，对每个数组进行如下操作：

```cpp
int ret=0;
for(int i=1;i<=600;i++)ret=(ret*10%TT+a[i])%TT;
```

然后将 $ret$ 加入集合中去重。最后集合的大小就是答案。

时间复杂度为 $O(sn)$，其中 $s=600$，为新开数组的大小。

## 代码

```cpp
#include<bits/stdc++.h>
#define TT 998244353 
#define maxn 310 
using namespace std;
int n,a[maxn][maxn<<1],ans;
string s;
set<int>st;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		cin>>s;
		int d=0,l=0,r=0;
		for(int j=0;j^s.size();j++){
			if(s[j]=='.')d=j;
			if(s[j]=='(')l=j;
			if(s[j]==')')r=j;
		}
		int p=d-1;
		for(int j=300;p>=0;j--,p--)a[i][j]=s[p]&15;
		p=d+1;
		if(l){
			int j=301;
			for(;p^l;j++,p++)a[i][j]=s[p]&15;
			for(p=l+1;p^r;j++,p++){
				int k=0;
				int w=j+(r-l-1)*k;
				while(w<=600)a[i][w]=s[p]&15,w=j+(r-l-1)*(++k);
			}
		}else{
			for(int j=301;p^s.size();j++,p++)a[i][j]=s[p]&15;
		}
		if(a[i][600]==9){
			int w=599;
			for(;w>=1;w--)if(a[i][w]!=9)break;
			a[i][w]++;
			for(int j=w+1;j<=600;j++)a[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++){
		int ret=0;
		for(int j=1;j<=600;j++)ret=(ret*10%TT+a[i][j])%TT;
		st.insert(ret);
	}
	printf("%d\n",st.size());
	return 0;
}
```

---

## 作者：谷民 (赞：11)

### 题解 AT182 【1=0.999...】

Perl一行切（两行压一行）

>Perl借取了C、sed、awk、shell脚本语言以及很多其他程序语言的特性，其中最重要的特性是它内部集成了正则表达式的功能，以及巨大的第三方代码库CPAN。简而言之，Perl像C一样强大，像awk、sed等脚本描述语言一样方便，被Perl语言爱好者称之为“一种拥有各种语言功能的梦幻脚本语言”、“Unix中的王牌工具”。——百度百科

一行完成了输入，输出，操作，累加

注：substr为Perl中的截取函数(截取一个字符串中的部分内容)

>substr(待截取字符串,截取起始位置,截取终了位置);

perl use bignum a,600 为定义变量

代码：

```
use bignum a,600;print~-grep(!$h{/\((\d*)|$//2+substr$`.$1x700,0,700}++,<>),$/

```


---

## 作者：奆奆的蒟蒻 (赞：3)

最EASY代码评选！  

#### [配合博客食用更加](https://www.luogu.com.cn/blog/Iamveryscan/)
### 看了楼下的代码，写的Very Good，只不过有点复杂。 
  
#### C++太长了！！  
### 看到没人用Perl，感到~~终身的~~遗憾  
```perl
use bignum a,600;
print~-grep(!$h{/\((\d*)|$//2+substr$`.$1x$<,0,$<}++,<>),$/
```
## 小蒟蒻解释一下：  
- ### bignum是Perl中32位整数  
 ####  所以 `use bignum a,600` 和C++中 `long long a=600` 差不多
- ### print是输出，不用说了
- ### 最有趣的是第二行包括了输入+输出  
  
## 提交以后得到
![](https://cdn.luogu.com.cn/upload/image_hosting/emibr0zw.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
### 十分不建议复制粘贴！

---

## 作者：CZQ_King (赞：3)

这里提供一个~~别致~~的思路。

## 把循环小数转成分数！再去重！

但是，你可能会问：

循环小数怎么转分数啊！

没事，让这篇题解来告诉你。


------------
我们拿$3.14(15)$为例。
$$3.14(15)$$
$$=3.14+0.00(15)$$

接下来让$a=0.00(15)$
$$a=0.00(15)$$
$$100a=0.(15)$$
$$100a\times100=15.(15)$$
接下来，神奇的时刻到了，看到上面的$100a=0.(15)$了吗，替换一下：
$$100a\times100=15+100a$$
$$a=\frac{15}{9900}$$
就这样可以把循环小数变成分数了。
然后$3.14(15)=3.14+\frac{15}{9900}=\frac{31101}{9900}=\frac{10367}{3300}$

掏起计算器算一下，你会发现$\frac{10367}{3300}$真的等于$3.14(15)$！

但是题目里说$1=0.(9)$，怎么办？

仍然用刚刚的方法，你会算出$a=0.(9)=1$。其实它们本来就是相等的，这涉及到一个“数学公理化”的知识：[0.999…=1？数到底是什么？李永乐老师讲数学公理化](https://www.bilibili.com/video/av44942988)

当然，用这种方法要记得约分。

最后把所有的分数塞进$set$或者$sort$一下，去个重，再统计个数就可以了。

---

## 作者：TensorFlow_js (赞：2)

好题。

### 0. 题意简述

给定 $N$，$1\le N\le 300$，以某种方式给你 $N$ 个有理数，去重后输出元素个数。

### 1. 题目分析

由于 $N\le300$，我们可以直接将数补到 $\ge600$ 位然后用 `unique` 去重统计个数输出。

可是怎么补呢？分为两种。

#### 1) 有限小数

直接补 $0$，将小数点后补到固定长度即可。

#### 2) 循环小数

直接补循环节，将小数点后补到固定长度即可。

但是，由于 $1=0.999...$，所以还要判断循环节是否全为 $9$，如果是则在前一位 $+1$ 变为有限小数即可。

下面介绍一些东西：

1. `string.find(string/char);` 字符串查找函数，找到返回一个 int，为在字符串中的位置，没找到返回 `string::npos`。
	
	代码中一共有 $27$ 个。
	
1. `string.substr(int pos,int n);`字符串截取函数，从第 $pos$ 个字符向后截取 $n$ 位。
	
	代码中一共有 $9$ 个。
	
1. `string(int n,char ch);` 字符串初值函数，将字符串赋初值为 $n$ 个 $ch$。
	
    代码中一共有 $5$ 个。
    
1. `fill_n(class::iterator iter,int n,class val);` 该函数从 $iter$ 指向的元素开始，将$n$ 个元素设置为 $val$。
	
    代码中一共有 $1$ 个。
    
1. `for_each(class::iterator beg, class::iterator end, Function f);` 对从 $beg$ 到 $end$ 指向的所有元素都执行函数 $f$。
	
    代码中一共有 $1$ 个。
    
1. `unique(class::iterator beg,class::iterator end);` 元素去重，删除从 $beg$ 到 $end$ 指向的所有元素中所有相邻的重复元素(只保留一个)。
	
    代码中一共有 $1$ 个。
    
1. `ostringstream` 这是个好东西， 是一个字符集操作模板类，通常用于串流的输出操作或格式化字符串，避免申请大量的缓冲区，代替了`snprintf`。
	
    代码中一共有 $1$ 个。
    
### 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int sz=1145;//补的位数
string change(string num){//补的函数
	ostringstream os;bool flag=true;
	if(num.find('.')==string::npos)return num+"."+string(sz,'0');//整数的情况
	if(num.find('(')==string::npos)return num+string(sz-num.size()+num.find('.')+1,'0');//有限小数的情况
	if(num.substr(num.find('(')+1,num.find(')')-num.find('(')-1)==string(num.substr(num.find('(')+1,num.find(')')-num.find('(')-1).size(),'9'))return num=num.substr(0,num.find('(')),for_each(num.rbegin(),num.rend(),[&](char &ch){if(flag)if(ch!='.'){if(ch+1!=':')ch++,flag=false;else ch='0';}}),(flag?(num="1"+num):""),change(num);//循环节全为9的情况
	return num.substr(0,num.find('('))+(fill_n(ostream_iterator<string>(os),(sz-num.find('(')+num.find('.'))/num.substr(num.find('(')+1,num.find(')')-num.find('(')-1).size(),num.substr(num.find('(')+1,num.find(')')-num.find('(')-1)),os.str())+(num.substr(num.find('(')+1,num.find(')')-num.find('(')-1)).substr(0,(sz-num.find('(')+num.find('.'))%num.substr(num.find('(')+1,num.find(')')-num.find('(')-1).size()+1);//其余循环小数的情况
}
vector<string> v;//去重序列
int main(){
	string s;int n;cin>>n;
	for(int i=0;i<n;i++)cin>>s,v.push_back(change(s));
	cout<<(sort(v.begin(),v.end()),unique(v.begin(),v.end())-v.begin())<<endl;
}
```

---

## 作者：HYdroKomide (赞：1)

### 题意：

给定 $n$ 个有理数，对于循环小数，循环节可能以不同方式表示。对它进行去重。

### 思路：

不会~~懒得~~分数化小数怎么办？模拟！

由于 $n$ 和字符串长度较小，我们可以暴力将每一个字符串补齐到同一个更大的长度 $s$，方便排序后去重。

细节比较多，具体地：

- 如果读入了整数，即读入的的数不含 `.`，直接在其后面补充一个 `.` 并补满 `0`；
- 如果读入的数没有循环节，在后面补齐 `0` 即可；
- 如果含有普通的循环节，按照循环节依次向后补齐；
- 最特别的，如果循环节全部为 `9`，需要向前不断进位。每一次如果需要进位，就将前面一个数字增加 $1$ 并将这个数字自身赋值为 `0`（注意跳过小数点）。如果首位也需要进位，还需要另加特判。

总体时间复杂度 $\Theta (sn\log n)$，保险起见取 $s=1000$。

### 程序如下：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int N=305,M=1e3+5;
int n;
string a[N];
vector<string>v;
string fill(string s,int st,int ed){
	int l=s.size();
	string ret;
	if(st==0){//如果没有循环节，直接补0
		for(int i=0;i<1000;i++){
			if(i<s.size())ret.push_back(s[i]);
			else ret.push_back('0');
		}
		return ret;
	}
	string tmp,comp;
	for(int i=st+1;i<ed;i++)tmp.push_back(s[i]),comp.push_back('9');//comp用来比较是否全为9，tmp暂存循环节
	for(int i=st;i<=ed;i++)s.pop_back();//先把原字符串里循环节去掉，方便后面操作
	if(tmp==comp){//特判全为9的情况，细节比较多
		if(s[s.size()-1]!='.')s[s.size()-1]++;//需要特判倒数第二位就是小数点的情况
		else s[s.size()-2]++;
		for(int i=s.size()-1;i>0;i--){
			if(s[i]=='.')continue;
			if(s[i]=='9'+1){//向前进位
				s[i]='0';
				if(s[i-1]=='.')s[i-2]++;
				else s[i-1]++;
			}
		}
		if(s[0]=='9'+1){//特判首位进位
			ret.push_back('1');
			s[0]='0';
		}
		for(int i=0;i<s.size();i++)ret.push_back(s[i]);
		while(ret.size()!=1000)ret.push_back('0');//补齐0
		return ret;
	}
	for(int i=0,j=0;i<1000;i++){
		if(i<s.size())ret.push_back(s[i]);
		else{
			ret.push_back(tmp[j]);//直接向后补全，简单粗暴
			j++;
			if(j==tmp.size())j=0;
		}
	}
	return ret;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int st=0,ed,dot=0;
		cin>>a[i];
		for(int j=0;j<a[i].size();j++){
			if(a[i][j]=='(')st=j;
			if(a[i][j]==')')ed=j;
			if(a[i][j]=='.')dot=j;//找到循环节和小数点位置
		}
		if(dot==0)a[i]+='.';//特判整数情况
		a[i]=fill(a[i],st,ed);
		v.push_back(a[i]);//压入vector方便排序
	}
	sort(v.begin(),v.end());
	cout<<unique(v.begin(),v.end())-v.begin()<<"\n";//排序后去重输出
    return 0;
}
```

### THE END

---

## 作者：CrTsIr400 (赞：1)

小数化分数模板题。

分类讨论。

对于有限小数，直接化成 $3.141= \frac{3141}{1000}$ 的形式。

对于无限循环小数，考虑拆成两部分：循环节部分和非循环节部分。

即 $3.14(159)=3.14+0.00(159)$ 。

非循环节直接乘上去就好了，现在考虑循环节部分。

先不管前面的几位0，讨论简单的情况例如 $0.(159)$ ，之后直接在分母上乘上十的几次方即可。

就设这个分数为 $x$ 了awa

我们需要再弄一个 $1000x$ ，两个柿子相减的结果即为 $999x=159$

然后约分即可，把之前的小数点位数乘上，即可得 $159/99900$ ,再加上前面的非循环节部分，再约分即可得结果。

似乎要ll还是double，注意精度。

---

## 作者：豌豆射手皮0608 (赞：1)

一道~~简单的~~模拟

思路:把这些小数补充到一定位数然后比较

不难看出，输入的必定都是小数，都带有小数点（实数当然有小数点啦$qwq$

所以一共可以分为两种情况：

**①：有限小数**

这个最简单了$qwq$

在后面加$0$就可以了

**②：循环小数**

这个也不难$qwq$

不断根据循环节在后面补位就可以了

要注意循环节如果全是$9$的话要变成$0$，前面加$1$(如果满$10$要进位哦

$qwq$

那补完位后怎么办呢$qwq?$

开个map记录一下不同的就可以了$qwq$

这里取的补的位数是600,稍微少一点也是可以的

复杂度O($600*n+nlogn$),可以通过此题

```
#include<bits/stdc++.h>
using namespace std;
string solve(string s)
{
    string st="";
    int l=-1,r=-1;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(')l=i;
        if(s[i]==')')r=i;
    }
    if(l==-1||r==-1)
    {
        for(int i=0;i<599;i++)
        {
            if(i<s.size())st+=s[i];
            else st+='0';
        }
    }
    else
    {
        for(int i=0;i<599;i++)
        {
            if(i<l)st+=s[i];
            else 
            {
                st+=s[l+(i-l)%(r-l-1)+1];
            }
        }
        for(int i=l+1;i<r;i++)
        {
            if(s[i]!='9')return st;
		}
		int f=0;
		for(int i=0;i<599;i++)
		{
			if(st[i]!='9')
			{
				f=0;
			}
			else
			{
				if(!f)
				f=i;
			}
		}
		int L=1;
		for(int i=f-1;i>=0;i--)
		{
			if(isdigit(st[i]))
			{
			int q=st[i]-'0';
			q+=L;
			if(q<10)L=0;else q%=10;
			st[i]=char(q+48);
			if(L==0)break;
			}
			
		}
		for(int i=f;i<599;i++)
		{
			st[i]='0';
		}
    }
    return st;
}
int n;string s;map<string,int> m;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        m[solve(s)]++;
    }
    cout<<m.size()<<endl;
    return 0;
}
```

---

