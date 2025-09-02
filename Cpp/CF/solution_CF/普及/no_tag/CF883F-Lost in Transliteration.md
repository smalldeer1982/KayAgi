# Lost in Transliteration

## 题目描述

There are some ambiguities when one writes Berland names with the letters of the Latin alphabet.

For example, the Berland sound u can be written in the Latin alphabet as "u", and can be written as "oo". For this reason, two words "ulyana" and "oolyana" denote the same name.

The second ambiguity is about the Berland sound h: one can use both "h" and "kh" to write it. For example, the words "mihail" and "mikhail" denote the same name.

There are $ n $ users registered on the Polycarp's website. Each of them indicated a name represented by the Latin letters. How many distinct names are there among them, if two ambiguities described above are taken into account?

Formally, we assume that two words denote the same name, if using the replacements "u" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/77b2db707b29a82aec640f23cbd1fafe4293bbb0.png) "oo" and "h" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/77b2db707b29a82aec640f23cbd1fafe4293bbb0.png) "kh", you can make the words equal. One can make replacements in both directions, in any of the two words an arbitrary number of times. A letter that resulted from the previous replacement can participate in the next replacements.

For example, the following pairs of words denote the same name:

- "koouper" and "kuooper". Making the replacements described above, you can make both words to be equal: "koouper" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kuuper" and "kuooper" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kuuper".
- "khun" and "kkkhoon". With the replacements described above you can make both words to be equal: "khun" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "khoon" and "kkkhoon" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kkhoon" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "khoon".

For a given list of words, find the minimal number of groups where the words in each group denote the same name.

## 说明/提示

There are four groups of words in the first example. Words in each group denote same name:

1. "mihail", "mikhail"
2. "oolyana", "ulyana"
3. "kooooper", "koouper"
4. "hoon", "khun", "kkkhoon"

There are five groups of words in the second example. Words in each group denote same name:

1. "hariton", "kkkhariton", "khariton"
2. "hkariton"
3. "buoi", "boooi", "boui"
4. "bui"
5. "boi"

In the third example the words are equal, so they denote the same name.

## 样例 #1

### 输入

```
10
mihail
oolyana
kooooper
hoon
ulyana
koouper
mikhail
khun
kuooper
kkkhoon
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
hariton
hkariton
buoi
kkkhariton
boooi
bui
khariton
boui
boi
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2
alex
alex
```

### 输出

```
1
```

# 题解

## 作者：LKY928261 (赞：2)

## 题目分析

首先，`kh` 与 `h` 可以相互替换，所以 `kk...kkh` 通过多次替换亦可转换为 `h` 。因此可以从后往前查找字符串中的 `h` ，找到 `h` 后，将其前面的所有 `k` 删去。单次循环即可处理完 `kh` 与 `h` 之间的替换。

又因为 `C/C++` 中的 `erase` 函数使用起来时间复杂度较高，所以可以将删除掉的 `k` 暂时以空格代替，最后在统一处理。

至于 `oo` 和 `u` 之间的替换，则比较特殊。`oo` 是由两个相同的字符组成的，当出现大串的 `o` 和 `u` 时，会有非常多的变化。

例如：`oou`，`uoo`，`ouo`。以上三个字符串本质相同，但如果统一把 `oo` 替换为 `u` ，会将其判别为两种不同的字符串。

所以，把 `oo` 替换为 `u` 是不可取的。而将 `u` 替换为 `oo` 则可以规避这种错误。

综上所述，对于每一个字符串，需要把每个 `kk...kkh` 转换为 `h` ，把 `u` 转换为 `oo` 。

最后在开一个 `map` 统计即可。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

~~（请不要在意我奇丑无比的码风）~~

```cpp
#include<bits/stdc++.h>
#define st string
using namespace std;
int n,k,i,j;st s,a[405];map<st,bool>b;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=0;i<n;i++){
		cin>>s;
		for(j=s.size()-1;j>0;j--)if(s[j]=='h'){//从后往前查找h
			for(j--;j>=0&&s[j]=='k';j--)s[j]=' ';//去掉多余的k
			j++;
		}
		for(j=0;j<s.size();j++)if(s[j]!=' ')
			if(s[j]=='u')a[i]=a[i]+"oo";//将u替换为oo
			else a[i]=a[i]+s[j];
		b[a[i]]=1;//计入map
	}
	for(i=0;i<n;i++)k+=b[a[i]],b[a[i]]=0;
	cout<<k<<"\n";
}
```

---

## 作者：King_duck (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF883F)

首先对题目进行一波分析。

先看 `kk` 和 `h` 可以互相替换的信息，根据这条信息我们就可以知道 `kkk...kk` 都可以被替换为 `h`，那么我们可以将字符串中所有的 `kkk...kh` 都替换成 `h`。

再来看第二种。对于第二种替换方法，我们可以发现这种方法在不重复的情况下仅能替换一次，所以我们选择将所有的 `u` 都替换为 `oo`。

直接上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string st;
set<string> se;
string foo(string st) 
{
    for(long long i=0;i<st.size();i++) 
	{
        if(st[i]=='h') 
		{
            int j=i-1;
            while(j>=0&&st[j]=='k')
            {
                j-=1;
			}
            st.erase(j+1,i-j-1);
            i=j+1;
        } 
		else if(st[i]=='u')
		{
            st.replace(i, 1, "oo");			
		}
    }
    return st;
}
int main() 
{
    cin>>n;
    for(long long i=1;i<=n;i++)
    {
        cin>>st;
        se.insert(foo(st));    	
	}
    cout<<se.size();
    return 0;
}
```

---

## 作者：czh___ (赞：0)

### 题意：

$u$ 和 $oo$ 可以相互转化，$kh$ 和 $h$ 也可以相互转换。问经过转换后有多少个 string 是同一组。

### 题解：

用 string 的 replace 来做很简单，把 $kh$ 都转换成 $h$，$u$ 转换成 $oo$ 就很容易区分开了，最后放进集合 set 里（set 里面没有相同的东西，自动去重了），输出 set 的长度即可。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    while(cin>>n){
        string s;
        set<string> st;
        while(n--){
            cin>>s;
            for(int i=s.length();i>=0;i--){
                if(s[i]=='u')
                    s.replace(i,1,"oo");
                else 
					if(s[i+1]=='h'&&s[i]=='k')
                    	s.replace(i,2,"h");
            }
            st.insert(s);
        }
        cout<<st.size();
    }
    return 0;
}
```

拜拜！

---

## 作者：PigJokerYellow (赞：0)

## 题意

给定 $ n $ 个字符串，字符串中，`oo` 和 `u` 可互换，`kh` 和 `h` 可互换，问有多少类不同的字符串。

## 思路

我们发现字符串中所有 `u` 都可变成 `oo` ，所以我们把所有的 `u` 换成 `oo` 。

对于 `kh` 与 `h` 的交换，易得 `kh` 等于 `h` ，`kkh` 等于 `h` ，`kkkh` 也等于 `h` ，所以 `kk...h` 都等于 `h` ，所以我们把所有的 `kk...h` 都转化为 `h` 。

综上，把所有的 `u` 换成 `oo` ，所有的 `kk...h` 换为 `h` ，得到最终的字符串，再用 `map` 存储并记录这一类字符串。

## 细节

在转化过程中，可以用一个函数来得出最终转化结果，此方式可能比其他方法简单一些，具体见代码中的注释。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;

ll n,cnt;
string str;
map<string,bool> mp;
//用map存储转换后的字符串是否已存在 

string solve(string str){
	//转换的过程 
	string ans="";
	//要返回的值 
	for(ll i=0;i<=str.size()-1;i++){
		//扫一遍字符串 
		if(str[i]=='u') ans+="oo";
		//是u则转换成oo 
		else if(str[i]=='k'){
			ll tmp=i;
			//记录原来的i的位置 
			while(str[i]=='k') i++;
			//找到最后一个k 
			if(str[i]=='h'){
				ans+="h";
			} 
			//如果后面是h就在ans后面加上h		 
			else{
				i=tmp;
				ans+=str[i];
			}
			//否则i还是在原来的位置 
		}
		else ans+=str[i];
		//不是u也不是kk...h就还是原字符串 
	}
	return ans;
}

int main(){
	cin>>n;
	while(n--){
		cin>>str;
		str=solve(str);
		if(mp[str]) continue;
		//如果已经有一类的字符串就不计答案 
		cnt++;
		mp[str]=1;
		//否则记录答案并记此字符串为已出现过的 
	}
	cout<<cnt;
	return 0;
} 
```

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF883F)
## 题意：
给出 $N$ 个单词，字符串中的 ```kh``` 和 ```h``` 或 ```oo``` 和 ```u``` 可以相互转换，如果一个字符串可以转换为另一个字符串则称为这两个字符串本质相同，请问有多少种本质不同的字符串？
## 思路：
那么对于每种替换方法，我们可以分类讨论：

1. 对于第一种替换方法，我们不难发现：所有的 ```k...kkkh``` 都可以被替换为 ```h```，那么我们可以将原字符串的所有 ```k...kkkh``` 都替换为 ```h```。

2. 对于第二种替换方法，我们可以发现这个不同于第一种，这种方法在不重复的情况下仅能替换一次，所以我们选择将所有的 ```u``` 都替换为 ```oo```。

那解法就出来了，对于每个字符串都处理出字符串的基本串再扔进 那解法就出来了,```set```，最后输出 ```set``` 大小。

```set``` 就是一个不可重集合，所以这步相当于去重的大小。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
set<string> sett;
string m(string a){
    for(int i=0;i<a.size();i++){
        if(a[i]=='h'){//如果找到'h'，则向前搜索'k'，并删去'k' 
            int j=i-1;
            while(j>=0&&a[j]=='k'){
                j--;
			}
            a.erase(j+1,i-j-1);
            i=j+1;
        }else if(a[i]=='u'){//如果找到'h'，则改为"oo" 
            a.replace(i,1,"oo");
        }
    }
    return a;
}
int main() {
    cin>>n;
    while(n--){
    	cin>>s;
        sett.insert(m(s));
	}
    cout<<sett.size();
    return 0;
}
```

---

## 作者：fangyicheng1216 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF883F)

# 思路

首先这道题让我们求有多少个本质相同的字符串，并有几种变换方法。

- 将 ```kh``` 和 ```h``` 互相替换。

- 将 ```u``` 和 ```oo``` 互相替换。

那么对于每种替换方法，我们可以分类讨论：

- 对于第一种替换方法，我们不难发现：所有的 ```k...kh``` 都可以被替换为 ```h```，那么我们可以将原字符串的所有 ```k...kh``` 都替换为 ```h```，然后进入下一种。

- 对于第二种替换方法，我们可以发现这个不同于第一种，这种方法在不重复的情况下仅能替换一次，所以我们选择将所有的 ```u``` 都替换为 ```oo```。

此时对于所有的字符串，由于使用的是同一种替换方法，所以只要两个字符串本质相同，在经过这样处理后得出来的字符串一定相同。那么我们可以使用一个 ```map``` 来对字符串进行判重。

# 代码

知道你们都想看（chao）这个。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rd read()
using namespace std;
inline int read(){//快读 
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        f=ch!='-';
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return f?x:-x;
}
inline void write(int x){//快写 
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar(x%10+48);
}
map <string,bool> m;
int ans;
inline string make(string s){//对字符串s做处理 
	int n=s.size();
	for(int i=n-1;i>=0;i--){//初步将k...kh改为h 
		if(s[i]=='h'){
			for(int j=i-1;j>=0;j--){
				if(s[j]=='k') s[j]=' ';
				else break;
				i=j;
			}
		} 
	}
	for(int i=0;i<n;i++){
		if(s[i]=='u'){//将u改为oo 
			s=s.substr(0,i)+"oo"+s.substr(i+1,114514);
			i++;n++;//一定要移动i和n 
		}
		else if(s[i]==' '){//彻底将k...kh改为h 
			s=s.substr(0,i)+s.substr(i+1,114514);
			i--;n--;//同上 
		}
	}
	return s;
}
int T;
string s;
signed main(){
	T=rd;
	while(T--){
		cin>>s;
		s=make(s);
		if(m[s]==0){//判重 
			ans++;
		}
		m[s]=1; 
	}
	write(ans);
	return 0;
}
```


---

## 作者：__polar_ice (赞：0)

[题目传送框](https://www.luogu.com.cn/problem/CF883F)

这道题的操作十分良心，一遍**线形替换**就可以过。

思路（伪代码）：

```
读入n;
while(n--)
{
    将字符串中的"u"替换成"oo"，将"kh"替换成"h";
    /*如果能找到就替换，替换完后又从头开始查找*/
    标记修改后的字符串是否出现过，若没有出现过，则单词数++，把单词所在的map数组标记为1;
}
输出结果;
```

这样就AC啦！

那么，要用到哪些S ~~（sao）~~ T ~~（cao）~~ L ~~（zuo）~~ 函数呢？

___

**关于<algorithm>的那些函数**

- `p.length()`：返回字符串$p$的长度。
  
- `p.find(n)`：返回字符串$p$中找到字符串$n$的结果，用`size_t`存储。
  
- `p.replace(p.find(n),p.length(),m)`：将字符串$p$中**第一个**字符串$n$替换成$m$。

我们用自定义函数`Replace_str(string fx,string fy)`函数来把字符串$t$中所有字符串$fx$替换成$fy$。

因为这道题的替换操作很水，所以我们可以**直接**进行替换。
  
**关于<map>的那些函数**
  
如`map<{类型一},{类型二}>a;`的意思是“数组”和“数组”的值的类型分别为类型一和类型二。
  
举个例子：
```cpp
map<int,string>a;
map<string,int>b;
void tmp()
{
    a[1]="I Love ACing";
    b["I love ACing"]=5;
}
```

---

于是……这道题的伪代码：

```cpp
void Replace_str(string,string)
{
    while(1)
    {
        if(找得到fx)
        {
            把字符串中的fx全部替换成fy;
        } 
        else 退出循环;
    }
}
```
  
等等！还有问题！
  
关于fx和fy**不能替换**的问题：
  
1. `"u"`和`"oo"`

我们来看一下下面的数据：

```plain
3
qooot
quot
qout
```
本质上这$3$个字符串是相同的（都可以化成`qooot`）。
但如果我们的函数是`Replace_str("oo","u")`（和正确代码**相反**），那么根据**先找先换**的原理，这些字符串会先后变成`quot quot qout`，于是你神奇地发现，原来的单词变成了两种不同的单词。

$\therefore$有结论：对于**一个字符和N个字符互换**的数据，我们应该把所有**一个字符的字符串**替换成**N个字符的字符串**而不能反向操作。

2. `kh`和`h`

这个很容易理解，如果我们是用`hh`来替换`kh`，则数据`hi`会变成$\underbrace {k...k}_{\infty\times k}hi$，即**死循环**，所以我们是用`kh`来换`hh`。

因为这道题没有**多个字符替换多个字符**的**重叠字符串**这种麻烦操作，所以这样提交就可以AC。

正确代码 - $\huge c_{o_{d_e}}$

```
#include<map>
/*要用函数map*/
#include<iostream>
#include<string>
/*要用函数string和length*/
#include<algorithm>
/*要用函数find,size_t,replace和自带的常量npos*/
using namespace std;
map<string,int>arr;
string t;
int n,cnt=0;
void Replace_str(string fx,string fy)//替换函数
{
    while(1)//见上面的伪代码
    {
        size_t repos=t.find(fx);
        if(repos!=string::npos)
            t=t.replace(repos,fx.length(),fy);
        else break;
    }
}
int main()
{
    cin>>n;//读入n
    while(n--)//同for(i=1;i<=n;i++)
    {
        cin>>t;//读入字符串t
        Replace_str("u","oo");//把"u"换成"oo"
        Replace_str("kh","h");//把"kh"换成"h"
//      cout<<"t:  "<<t<<endl;
        if(arr[t]==0)arr[t]=1,cnt++;
        /*如果字符串t没有出现过，则标记t出现过，并让不重复的单词个数+1*/
    }
    cout<<cnt<<endl;
    return 0;
}
```


---

（第二次提交题解，把格式改了一下，求过~）

---

## 作者：codeLJH114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF883F)

# $\textbf{Problem}$

给出 $N$ 个单词，字符串中的 `kh` 和 `h`、`oo` 和 `u` 可以相互转换，如果一个字符串可以转换为另一个字符串则称为这两个字符串**本质相同**，请问有多少种**本质不同**的字符串？

# $\textbf{Analysis}$

定义一个字符串的**基本串** $=$ 原字符串中把 `u` 替换成 `oo`，`kkkk...kkkh` 替换成 `h`。

**基本串**相当于这个字符串的“根”，也就是这个字符串是从哪个字符串转化过来的。

结论：两个字符串的**基本串**相同等同于这两个字符串**本质相同**。

这个结论很好理解吧，两个字符串的**基本串**相同 $\to$ 这两个字符串都是从字符串 $B$ 转换过来的 $\to$ **本质相同**。

那解法就出来了，对于每个字符串都处理出字符串的基本串再扔进 `set`，最后输出 `set` 大小。

`set` 就是一个**不可重集合**，所以这步相当于去重的大小。

# $\textbf{Code}$

```cpp
#include <iostream>
#include <set>
int N;
std::string S;
std::set<std::string> Set;
std::string Mission(std::string S) {
// 返回 s 的基本串
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'h') {
            int j = i - 1;
            while (j >= 0 and S[j] == 'k')
                j -= 1;
            S.erase(j + 1, i - j - 1);
            i = j + 1;
        } else if (S[i] == 'u')
            S.replace(i, 1, "oo");
    }
    return S;
}
int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++)
        std::cin >> S,
        Set.insert(Mission(S));
    std::cout << Set.size();
    return 0;
}
```

---

