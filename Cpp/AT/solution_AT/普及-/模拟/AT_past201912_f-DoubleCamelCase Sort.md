# DoubleCamelCase Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/past201912-open/tasks/past201912_f

文字列 $ S $ が与えられる。これは、$ 1 $ つ以上の単語を (間に空白などを挟まずに) 連結したものである。ここで、各単語は $ 2 $ 文字以上であり、最初の文字と最後の文字のみが英大文字、それ以外の文字は全て英小文字である。

これらの単語を辞書順に並べ (大文字小文字の違いは無視する)、同様に連結して出力するプログラムを作成せよ。

例えば、$ S\ = $ `FisHDoGCaTAAAaAAbCAC` とする。これは `FisH`, `DoG`, `CaT`, `AA`, `AaA`, `AbC`, `AC` の $ 7 $ つの単語を連結したものである。これらを辞書順に並べると `AA`, `AaA`, `AbC`, `AC`, `CaT`, `DoG`, `FisH` となるため、`AAAaAAbCACCaTDoGFisH` と出力すればよい。

## 说明/提示

### 注意

この問題に対する言及は、2019年12月29日 05:00 JST まで禁止されています。言及がなされた場合、賠償が請求される可能性があります。

試験後に総合得点や認定級を公表するのは構いませんが、どの問題が解けたかなどの情報は発信しないようにお願いします。

### 制約

- $ S $ は長さ $ 2 $ 以上 $ 100,000 $ 以下の文字列である。
- $ S $ の各文字は英大文字または英小文字である。
- $ S $ は問題文で述べたような単語の連結である。

### Sample Explanation 1

問題文で用いた例である。

### Sample Explanation 2

同じ単語が複数個存在する可能性があることに注意せよ。

## 样例 #1

### 输入

```
FisHDoGCaTAAAaAAbCAC```

### 输出

```
AAAaAAbCACCaTDoGFisH```

## 样例 #2

### 输入

```
AAAAAjhfgaBCsahdfakGZsZGdEAA```

### 输出

```
AAAAAAAjhfgaBCsahdfakGGdEZsZ```

# 题解

## 作者：无钩七不改名 (赞：4)

### 题目大意：

给出一个字符串，里面含有一些单词。

每个单词由 $2$ 个大写字母夹 $0$ 个或 $0$ 个以上的小写字母组成。

把这些单词重新按照字典序排列，组合成一个新的字符串。


### 思路：

+ 设置一个 `bool` 标记 `bo`；
+ 遇到开头大写字母标记成 $1$，遇到结尾大写字母标记为 $0$，将其计入一个新的字符串；
+ 最后对这些得到的字符串进行自定义的 `sort` 排序，进行输出即可。

---

## 作者：Ja50nY0un9_as_AgNO3 (赞：3)

[更糟心的阅读体验。](https://www.luogu.com.cn/blog/363302/solution-at-past201912-f)

**AtCoder 不愧盛产水题。**

这属于是我见过的最水的 F 题了（确信）。

## 题意
给你一个字符串，其由单词组成。每个单词长度均不小于 $2$，其开头及结尾字符为大写，其余为小写。

请将**单词**按字典序排列后输出，中间不带空格。

**注意：此处对大小写不敏感。**

## 解法
首先我们要把每个单词分离出来。

可以用一个这样的循环：

```cpp
string s;
cin >> s;
int n = s.length();
int cnt = 1;
//单词数目
bool flag = false;
//false表示在两个单词之间
//true表示在单词内部
for (int i = 0; i < n; i++){
    x[cnt] += s[i];
    if (upr(s[i])){
        if (flag == true) cnt++;//到了单词末尾
        flag = !flag;//切换状态
    }
}
cnt--;//前面多算了一个
```

当然也可以将 $flag$ 换成一个计数器，写法大致相同。

此时我们处理完单词，接下来是排序。

~~于是您自信地直接 `sort` 一遍，WA。~~

这是因为，`string` 中的小于比较是先比较字符串长度，再比较每个字符的字典序。

而依照题意，比较字典序则要将这个优先级反过来，先比较字符，后比较长度。

于是我们可以手写一个 `cmp` 函数来进行比较。其代码如下：

```cpp
inline bool cmp(string x, string y){
    int len = min(x.length(), y.length());
    for (int i = 0; i < len; i++){
        if (utl(x[i]) != utl(y[i])) return utl(x[i]) < utl(y[i]);
    }
    return x.length() < y.length();
}
```

由于题目要求忽略大小写，所以 `utl` 函数的作用是将大写的字母转为小写。

接着就是输出了，一个简单的循环就好。

完整代码稍微增添一点东西就可以，就不放了。

记得加上 `string` 和 `algorithm`
 这两个头文件，否则会CE。

------------
 
11/14 Update：发现了一处明显错误并修复。

---

## 作者：G__G (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_past201912_f)

## 题目大意

简单来说，这道题就是将一个字符串 ```S``` 按以下规则拆成若干个小字符串：

1. 每个小字符串的长度不小于 $2$ 。

2. 每个小字符串的第一个和最后一个字符必须是大写字母。

拆好以后，再讲这些小字符串按照字典序排列，最后输出。

观察样例后，我们还能得到两个要求：

- 两个字符串之间没有空格或换行。

- 排序时对大小写不敏感。

## 解题思路

先来看一下样例：

$\texttt{AAAAAjhfgaBCsahdfakGZsZGdEAA}$

按照要求，我们可以把它拆成以下 $7$ 个小字符串。

1. $\texttt{AA}$

2. $\texttt{AA}$

3. $\texttt{AjhfgaB}$

4. $\texttt{CsahdfakG}$

5. $\texttt{ZsZ}$

6. $\texttt{GdE}$

7. $\texttt{AA}$

我们可以从前往后遍历字符串 ```S``` ，当遇到大写字母时，判断它是否是第偶数个，如果是，则进行分裂。

接着，我们对这 $7$ 个字符串进行排序（因为要比较字符串长度，所以要自定义 ```cmp``` 函数），得出结果：

$\texttt{AAAAAAAjhfgaBCsahdfakGGdEZsZ}$

## 代码实现
```
#include<bits/stdc++.h>
using namespace std;
string s,a[100000];
int cnt=1;
int fl=0;
int fun(char c){
	if(c>='a'&&c<='z'){
		return (int)(c-'a'+1);
	}
	return (int)(c-'A'+1);
}
bool cmp(string x,string y){
	for(int i=0;i<min(x.size(),y.size());i++){
		if(fun(x[i])!=fun(y[i])){
			return fun(x[i])<fun(y[i]);
		}
	}
	return x.size()<y.size();
}
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		a[cnt]+=s[i];
		if(s[i]>='A'&&s[i]<='Z'){
			fl++;
			if(fl%2==0){
				cnt++;
			}
		}
	}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		cout<<a[i];
	}
	return 0;
}

```


---

## 作者：qwertim (赞：0)

按照题意直接模拟即可。

定义一个变量 $tmp$，在一个「单词」开始的地方（$tmp = -1$）将 $tmp$ 变为当前的位置，在一个「单词」结束的地方（$tmp ≠ -1$）截取 $tmp$ 至现在的位置为一个「单词」，并将 $tmp$ 变为 $-1$。最后将所有「单词」排序即可。

注意：`sort` 排序字符串是先比较长度在按字典序排序，并且区分大小写，而题目要求是先按字典序排序在比较长度，并且不区分大小写，所以我们要手写 $cmp$ 比较函数。
# 代码
```cpp
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int tmp=-1,cnt;
string s,str[100005];
bool cmp(string a,string b){
    int k=min(a.size(),b.size())-1;
    fo(i,0,k)if(tolower(a[i])!=tolower(b[i]))return tolower(a[i])<tolower(b[i]);//均变成小写
    return a.size()<b.size();//判断长度
}
int main(){
    cin>>s;
    fo(i,0,s.size()-1){
        if(isupper(s[i])){//是否是大写字母
            if(tmp==-1)tmp=i;
            else str[++cnt]=s.substr(tmp,i-tmp+1),tmp=-1;//截取tmp~i
        }
    }
    sort(str+1,str+1+cnt,cmp);
    fo(i,1,cnt)cout<<str[i];
    return 0;
}
```


---

## 作者：STARSczy (赞：0)

# 思路
输入后，直接按题意进行分割。定义一个标记变量 $p$，最开始为 $0$。当碰到一次大写字母后标记为 $1$，且其字符子串加上这个变量。然后对这些分割出来的字符串进行排序，排序的条件需要手动定义，即字典序。最后，依次输出即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,p;
char a[1000000];
string s[1000000];
char down(char c){
	if(c>='a') return c-'a'+'A';
	return c;
}
bool cmp(string a,string b){
	for(int i=0;a[i]&&b[i];++i) if(down(a[i])!=down(b[i])) return down(a[i])<down(b[i]);
	return a.size()<b.size();
}//手动定义排序的程序

signed main(){
	cin>>a;
	for(int i=0;a[i];++i){
		if(a[i]<='Z') if(p) p=0;
		else p=1,++n;
		char cmp[5]={a[i]};
		s[n]=s[n]+string(cmp);
	}//分割
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;++i) cout<<s[i];//输出
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

[Double CamelCase Sort の 传送门](https://www.luogu.com.cn/problem/AT_past201912_f)

因为每个单词的首尾都是大写字母，所以可以用一个标记变量 $f$。

在一个单词开始时，将 $f$ 标记为 $1$，在结束时标记为 $0$。

当 $f$ 为 $1$ 且当前的 $S_i$ 为大写，那么就将这期间所有的字符用数组存起来。

最后对这个数组排序即可。

注意 $2$ 点。

1. 排序时对大小写不敏感；

2. 因为 `string` 的比较先比较字符串的长度，所以要自定义 `cmp` 排序。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,d[100005];
int n,ch,f;
inline char zh(char v) {return (v<'a'?v-'A'+'a':v);}
inline bool SORT(string a,string b) {
	for(int i=0;i<min(a.size(),b.size());++i)
		if(zh(a[i])!=zh(b[i]))	return zh(a[i])<zh(b[i]);
	return a.size()<b.size();
}
signed main() {
	cin>>s;
	n=s.size(),++ch;
	for(int i=0;i<n;++i) {
		d[ch]+=s[i];
		if(s[i]<'a') {
			if(f)	++ch,f=0;
			else	f=1;
		}
	}
	sort(d,d+ch,SORT);
	for(int i=0;i<ch;++i)	cout<<d[i];
	return 0;
}
```

---

## 作者：Wind_Smiled (赞：0)

## 题意

给定由两个大写字母夹若干小写字母的「单词」首尾相连构成的字符串。

要求按照字典序对这些单词排序并首尾相连输出新的字符串。

## 分析

需要从大字符串之中分离出来这若干个「单词」，并且进行排序。最后输出即可。

### 分离
假设我们有一个结构体储存一个字符串以及该字符串的长度及对应词数指针和位数指针，如下：
```cpp
struct node{
    int lens;
    string s;
}a[20005];
string str;//原字符串
int len,cnt=1,p=1;//len 指原字符串长度，cnt 是指下一个词语，p 是指结构体所存储字符串中的指针
```
一个记录大小写（是否在单词内部）的 `bool` 变量：
```cpp
bool f;//0 为不在一个单词中，否则为在
```
并且读入了原字符串并且获取了其长度：
```cpp
cin>>str;
len=str.length();
```
那么就可以进行一下对其的分离操作：
```cpp
for(int i=0;i<len;i++){//字符串从 0~n-1 位进行枚举
	if(f==0){//不在单词内部
		if(str[i]>='A'&&str[i]<='Z'){//出现了大写字母
			f=!f;//标记为在
			a[cnt].s[p]=str[i];//该位记录为当前单词的第一位
			p++;//当前单词指针后移一位
		}
	}
	else{//在单词内部
		if(str[i]>='A'&&str[i]<='Z'){//出现大写字母
			f=!f;//标记为不在
			a[cnt].s[p]=str[i];//当前位是本单词的最后一位
			a[cnt].lens=p;//标记长度
			cnt++;//下一个单词
			p=1;//单词指针归为 1
		}
		else{//小写字母
			a[cnt].s[p]=str[i];//记录
			p++;//下一位
		}
	}
}
```
进行了分离的处理之后，我们就可以进行排序。

当然，这道题所要求的字典序需要我们手写 `cmp` 函数进行排序，需要先比较每一位的字典序，最后再返回长度大小，是不能按照字符串本身所判定的大于小于的。

完整代码就不放了。

---

## 作者：Back_Stuff (赞：0)

## 题目大意

输入一个字符串 $s$，这个字符串由若干个【单词】组成。

【单词】的定义是：字符串两端是大写字母，中间是若干个小写字母。

按照一定排序后输出所有【单词】。

## 思路

遍历 $s$。

- 如果当前字符是大写字母而且没有左端点 $l$，将 $l$ 置为当前下标。

- 如果 $l$ 有值但不是当前字符，而且当前字符是大写字母，将右端点 $r$ 置为当前下标。同时将【单词】字符串数组多增加一个字符串，将 $l$ 置为无值。

贴上代码。

```cpp
cin>>s;
for(int i=0;i<s.size();i++){
	if(l==-1&&b(s[i]))
		l=i;
	if(l!=-1&&l!=i&&b(s[i])){
		r=i;
		x[++cnt]=s.substr(l,r-l+1);
		l=-1;
	}
}
```

之后是排序部分，按照题意排序即可。

```cpp
bool b(char a){
    return a>='A'&&a<='Z';
}
bool transfer(char s){
    if(b(s))
        s+=32;
}
bool cmp(string a,string b){
    for(int i=0;i<min(a.size(),b.size());i++)
        if(transfer(a[i])!=transfer(b[i]))
            return transfer(a[i])<transfer(b[i]);
    return a.size()<b.size();
}
```

---

## 作者：Convergent_Series (赞：0)

## 题意：
分离字符串中每两个大写字母之间的串（包括首尾字母），排序后输出。
+ 分离：
	+ 使用结构体存储每一段的首字母和尾字母的位置。
+ 排序： 观察~~混乱的~~样例可知，比较规则如下：
	+ 不区分大小写字母。
   + 先按字母大小排，再按长度排。
   + 与字典序不同，需手写比较函数。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct word{int l=-1,r=-1;}a[100010]; 
string s;
bool cmp(word a,word b){
	int i;
	int lna=a.r-a.l+1,lnb=b.r-b.l+1;
	char ta,tb;
	for(i=0;i<lna&&i<lnb;i++){
		if(s[a.l+i]<='Z') ta=s[a.l+i]-'A'+'a';else ta=s[a.l+i];
		if(s[b.l+i]<='Z') tb=s[b.l+i]-'A'+'a';else tb=s[b.l+i];
		if(ta!=tb) return ta<tb;
	}
	return lna<lnb;
}
int ln,cnt=1;
int main(){
    cin>>s;
    ln=s.length();
    int i,j;
    for(i=0;i<ln;i++){
    	if(s[i]>='A'&&s[i]<='Z'){
    		if(a[cnt].l==-1) a[cnt].l=i;
    		else a[cnt].r=i,cnt++;
		}
	}
	sort(a+1,a+cnt,cmp);
    //for循环处理后cnt指向最后一个单词的下一个位置，所以不用加一
	for(i=1;i<cnt;i++){//注意是<而不是<=，理由同上。
		for(j=a[i].l;j<=a[i].r;j++) cout<<s[j];
	}
	cout<<"\n";
	return 0;
}
```

[22ms，次优解。](https://www.luogu.com.cn/record/list?pid=AT_past201912_f&orderBy=1&status=&page=1)

---

