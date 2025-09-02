# [CERC2013] What does the fox say?

## 题目描述

### 题目大意

森林里面有很多声响，你想知道有哪些声响是由狐狸发出来的。

已知你搜集到了 $n$ 个声响，并且还知道某些其他动物能够发出的声响，已知如果没有哪一个声响是由其他任何一种动物发出来的话，那这个声响绝对是由狐狸发出来的。现在，给定你这 $n$ 个声响，以及某些其他动物能够发出的声响，请你求出狐狸发出的声响。

## 说明/提示

$n\leqslant 100$。  
保证每个字符串的长度不超过 $100$。

Translated by Eason_AC  
2020.10.30

## 样例 #1

### 输入

```
1
toot woof wa ow ow ow pa blub blub pa toot pa blub pa pa ow pow toot
dog goes woof
fish goes blub
elephant goes toot
seal goes ow
what does the fox say?
```

### 输出

```
wa pa pa pa pa pa pow
```

# 题解

## 作者：luobotianle (赞：11)

题意其实很简单：在给出的 $n$ 个字符串中排除一些字符串，输出剩下的字符串；但由于这题没有给出 $n$，所以读入是一个问题。如果你会用 `getline` 和 `stringstream` 的话，输入会变得很简单，但蒟蒻不会，所以这里用了 `getchar` 边读入字符边存储字符串。

由于 `getchar` “什么都吃”的特性，导致这样写要注意很多细节，在代码中将一一展示。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> a;//用来记录出现过的叫声 
map<string,bool> mp;//用来记录是否是狐狸的叫声 
string s,s1,s2;
int main(){
	int T;
	cin>>T;
	char ch=getchar();//将 T 后面的换行 ('\n') 吃掉 
	while(T--){
		mp.clear();//多测清空 
		a.clear();
		s=s1=s2="";
		while(1){
			ch=getchar();
			if(ch=='\n'){//第一段输入是一行，所以遇到换行就说明结束了 
				a.push_back(s); //最后一个词也要加入 
				mp[s]=1;//该叫声出现过，可能是狐狸的叫声 
				break;
			}
			else if(ch==' '){//遇到空格，将此时的 s 加入 
				a.push_back(s);
				mp[s]=1;
				s="";//将用于记录的 s 清空 
			}
			else s+=ch;//更新 s 
		}
		while(cin>>s>>s1>>s2,s1=="goes")mp[s2]=0;//该声音不是狐狸叫声 
		do{ch=getchar();}while(ch!='\n');//这里要用do_while，因为此时的 ch 还是换行符 '\n'
		for(auto &i:a){
			if(mp[i])cout<<i<<" ";//循环每一个出现过的叫声，将狐狸的叫声输出 
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Elaina_0 (赞：9)

# P7008 [CERC2013] What does the fox say?

记得小学英语老师给我们放过一首歌，也叫《What does the fox say》。%%%

## 题意

给我们一些叫声，并告诉我们已知动物的叫声，输出剩余的叫声（也就是狐狸的叫声）。

## 分析

一个很简单的 STL 容器 使用练习题。

通过 [map](https://zh.cppreference.com/w/cpp/container/map) 记录声音；[stringstream](https://zh.cppreference.com/w/cpp/io/basic_stringstream) 做到反复输入。

输出的时候使用 map 的[**迭代器**](https://oi-wiki.org/lang/csl/associative-container/#%E9%81%8D%E5%8E%86%E5%AE%B9%E5%99%A8)遍历。

```cpp
//两种写法
for(auto it=mp.begin();it!=mp.end();it++){
	cout<<it->first<<' '<<it->second<<endl;
}
	
for(auto &x:mp){
	cout<<x.first<<' '<<x.second<<endl;
}
```


但是输入是有序的，而 map 遍历时，是按照 `iterator->first` 的顺序遍历的。

举个例子：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define Elaina 0

map<string,int> mp;
string s;

main(){
	string s;
	
	s='a',mp[s]=1;
	s='b',mp[s]=2;
	s='d',mp[s]=3;
	s='e',mp[s]=4;
	s='c',mp[s]=5;
	
	for(auto it=mp.begin();it!=mp.end();it++){
		cout<<it->first<<' '<<it->second<<endl;
	}
	
	return Elaina;
}
```
对于以上代码，她的输出结果是：
```cpp
a 1
b 2
c 5
d 3
e 4
```
所以我们需要特殊处理一下，记录一下输入顺序就可以了。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Elaina 0
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}

map<string,int> mp;
map<int,string> order;
int n,cnt,len;
stringstream ss;
string s_0,s;

main(){
	int T=read();
	while(T--){
		ss.clear();
		cnt=0;
		getline(cin,s_0);
		ss<<s_0;
		mp.clear();
		while(ss>>s){
			cnt++;
			order[cnt]=s;
			mp[s]++;
		}
		while(getline(cin,s_0)){
			if(s_0=="what does the fox say?") break;
			ss.clear();
			ss<<s_0;
			ss>>s;//动物
			ss>>s;//goes
			ss>>s;//叫声
			mp[s]=0;
		}
		for(auto it=order.begin();it!=order.end();it++){
			if(mp[it->second])
				cout<<it->second<<' ';
		}
		putchar('\n');
	}
	return Elaina;
}
```

谢谢管理大大的审核，

顺便无耻的推一下 [blog](https://www.cnblogs.com/Elaina-0)。

---

## 作者：cheese_iyl (赞：3)

## 题意:
给你一堆字符串，然后排除其中一些字符串，输出剩下的。
## 大致思路：
用一个 vector 来存储所有的字符串，用 map 来记录需要排除的字符串，将需要排除的标记为 ``true``。最后用 for 扫一遍所有的字符串，直接输出未被 map 记录的字符串。
## 难点：
本题难在输入。我用的是 ``getchar()``，这样可以将空格和换行符吞掉，但还是有很多输入的细节要处理，详见代码批注。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string>s;
map<string,bool>m;
int t;
char tem;//临时变量，用来解决getchar的特性问题
int main(){
	scanf("%d",&t);
	tem=getchar();//将第一排的换行符吞掉，防止其影响下面的程序
	while(t--){
		char c;//临时变量，用于输入
		string a;//同上
		m.clear();
		s.clear();
		while(c=getchar()){
			if(c=='\n'){//吞到换行符就结束
				s.push_back(a);//将最后一个叫声录入
				break;
			}
			else if(c==' '){//吞到空格，准备吞下一个字符串
				s.push_back(a);//录入
				a="";//清空
			}
			else{
				a+=c;
			}
		}
		string x,y,z;
		while(cin>>x>>y>>z){
			if(y!="goes"){//最后一句话，y 是等于does的
				for(int i=0;i<10;i++){
					tem=getchar();//吞掉多余的字符，一共十个（包括换行符）
				}
				break;
			}
			m[z]=true;//标记
		}
		for(int i=0;i<s.size();i++){
			if(m[s[i]]==false){
				cout<<s[i]<<" ";//直接输出
			}
		}
		printf("\n");
	}
	return 0;//完结撒花！
}
```  

最后，我列举几个卡住我的坑点：  
1. ``gechar()`` 会将第一行的换行符吞掉，注意处理；  
2. 输入叫声时，吞到换行符后还要再将最后一个字符串录入再 ``break``；  
3. 变量初始化。    

希望这篇题解对你有帮助。

---

## 作者：little_stickman (赞：2)

很明显，这是一道关于字符串的题目。  
解法：首先倒着读入各种动物的叫声，放入一个队列。然后跳过前面已经有的动物声音，得到狐狸的声音。   
然后，我们再把处理好的剩下的动物叫声翻转回正序，输出即可。
```
#include <bits/stdc++.h>
#include <set>
#include <string> 
using namespace std;
char a[10001],s[10001];
set<string> m;
string voice;
int main()
{
	int T;
	cin>>T;
	getchar();
	while(T--)
	{
		fgets(s,sizeof(s),stdin);
		m.clear();
		while(1)
		{
			fgets(a,sizeof(a),stdin);
			if(!strcmp(a,"what does the fox say?"))break;
			voice="";
			for(int i=strlen(a)-1;a[i]!=' ';i--)
				voice=voice+a[i];
			char tmp;
			for(int i=0,len=voice.size();i<=(len-1)/2;i++)
			{
				tmp=voice[i];
				voice[i]=voice[len-1-i];
				voice[len-1-i]=tmp;
			}
			m.insert(voice);
		}
		s[strlen(s)]=' ';
		s[strlen(s)]=0;
		voice="";
		for(int i=0,len=strlen(s);i<len;i++)
		{
			if(s[i]==' ')
			{
				if(m.find(voice)==m.end())
				{
					cout<<voice<<' ';
				}
				voice="";
			}
			else
			{
				voice=voice+s[i];
			}
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：SevenElevenThirteen (赞：2)

这是一道简单的 $\texttt{ stl }$ 练习题。


我们可以把所有声响记录下来，再逐一排除，最后剩下的声音就是狐狸发出的。可以用 $\texttt{ map }$ 记录声音是否被排除。输入时由于不知道有多少个声音，必须要把一整行都读入进来再一个个统计，用 $\texttt{ stringstream }$ 可以轻松解决这个问题。

- $\texttt{ stringstream }$ 用法详解

$\texttt{ stringstream }$ 包含在头文件 $\texttt{ <sstream> }$ 中。它可以存储并重新读取数据，协助类型转换，语法类似 $\texttt{ cin }$ 和 $\texttt{ cout }$ 。
  
成员函数 $\texttt{ clear() }$ 可以清空 $\texttt{ stringstream }$；成员函数 $\texttt{ str() }$ 可以把 $\texttt{ stringstream }$ 中的数据当成字符串来输出。

$\texttt{ stringstream }$ 用法示例：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>
using namespace std;

int main()
{
	string s1 = "1 0",s2 = "a abc";
	stringstream ss;//定义
	ss << s1;//存储
	int a;
	bool b;
	ss >> a >> b;//读取
	cout << ss.str() << endl;//当成字符串输出
	ss.clear();//清空
	ss << s2;
	char c;
	string d;
	ss >> c >> d;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << d << endl;
	return 0;
}


```
输出：
```
1 0
1
0
a
abc
```

有了$\texttt{ stringstream }$的帮助，这道题写起来就容易许多了，下面是[AC](https://www.luogu.com.cn/record/41297323)代码。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<sstream>
#include<string>
#include<cstring>
using namespace std;

string a[105];

int main()
{
	int t;
	cin >> t;
	char c;
	scanf("%c",&c);//第一行末尾换行符
	while (t--)
	{
		for (int i = 0;i <= 100;i++) a[i] = "";
		map<string,bool> m;
		string s;
		getline(cin,s);
		stringstream ss;
		ss << s;
		int n = 0;//声音个数
		while (ss >> s)//逐一统计声响
		{
			a[++n] = s;
			m[a[n]] = true;
		}
		ss.clear();//清空
		while (getline(cin,s))
		{
			if (s == "what does the fox say?") break;
			if (s == "\n") continue;
			ss.clear();
			ss << s;
			ss >> s;//读取动物名称
			ss >> s;//读取 "goes"
			ss >> s;//读取声响
			m[s] = false;//排除
		}
		for (int i = 1;i <= n;i++)
		{
			if (m[a[i]]) cout << a[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
```
希望管理给过

---

## 作者：Eason_AC (赞：2)

## Content
森林里面有很多声响，你想知道有哪些声响是由狐狸发出来的。

已知你搜集到了 $n$ 个声响，并且还知道某些其他动物能够发出的声响，已知如果没有哪一个声响是由其他任何一种动物发出来的话，那这个声响绝对是由狐狸发出来的。现在，给定你这 $n$ 个声响，以及某些其他动物能够发出的声响，请你求出狐狸发出的声响。

其他动物的声响和名字都仅由一个字符串组成。

**数据范围：$t$ 组询问，$n\leqslant 100$，每个字符串的长度不超过 $100$ 个字符且仅由小写字母组成。**
## Solution
简单的字符串模拟。

由于我们输入时不能确定 $n$，我们先把所有的 $n$ 个声响都一个个统计出来，然后再看这 $n$ 个声响都被那些其他种类的动物给占了，这里我们可以开一个 $\texttt{map}$，记录一下每个声响是否已经被占，最后输出所有没有被占的字符串即可。

记得多组询问时要清空数组和变量。
## Code
```cpp
int t;
string s[107], ss[107];

int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(t);
	while(t--) {
		map<string, int> vis;
		int cnt = 1;
		string so;
		getline(cin, so);
		int lenso = so.size();
		_for(i, 0, lenso - 1) {
			if(so[i] == ' ') cnt++;
			else s[cnt] += so[i];
		}
		while(getline(cin, so)) {
			int cntt = 1; lenso = so.size();
			_for(i, 0, lenso - 1) {
				if(so[i] == ' ') cntt++;
				else ss[cntt] += so[i];
			}
			if(cntt > 3) {
				_for(i, 1, cntt) ss[i].clear();
				break;
			}
			else vis[ss[3]] = 1;
			_for(i, 1, cntt) ss[i].clear();
		}
		_for(i, 1, cnt) {
			if(!vis[s[i]]) cout << s[i] << ' ';
			s[i].clear();
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：yanwh1 (赞：2)

# 题面：
给你一行字符串，然后给出需要删除的字符串，最后打印剩余的字符串。

# 思路：
直接用 map 记录需要删除的字符串，接着再跑一遍需要输出的字符串，就做完了。

需要注意的是，本题的输入比较恶心，建议使用 getchar 输入，剩下的细节就看代码吧。


# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=105;
char qwe[N][N],res[N];int cnt;
inline int zfcread(char (&qwq)[N]){
	char c=getchar();int tot=0;
	while(c<'a'||c>'z'){c=getchar();if(c=='\n'){return 0;}}
	while(c>='a'&&c<='z')qwq[tot++]=c,c=getchar();
	if(c=='\n')return 0;
	return 1;
}map<string,int>mp;
signed main(){
	int T=read();
	while(T--){
		for(rint i=0;i<=100;i++)
			for(rint j=0;j<=100;j++)
				qwe[i][j]='\0';
		cnt=0;
		mp.clear();
		while(zfcread(qwe[++cnt]));
		int wre=0;
		while(1){
			while(1){
				int flag=zfcread(res);
				if(!strcmp(res,"what")){
					zfcread(res);
					zfcread(res);
					zfcread(res);
					zfcread(res);
					int len=strlen(res);
					for(rint i=0;i<len;i++)res[i]='\0';
					wre=1;
					break;
				}if(!flag)mp[res]=1;
				int len=strlen(res);
				for(rint i=0;i<len;i++)res[i]='\0';
			}if(wre)break;
		}for(rint i=1;i<=cnt;i++)
			if(!mp[qwe[i]])printf("%s ",qwe[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：1)

先用一个数组记录下所有的声响，再用一个 map 记录把所有其他动物的叫声打上标记，最后再遍历一遍数组，把所有没有打上标记的叫声输出。

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
string s[105];
unordered_map<string,bool>mp;
int main()
{
    int t;cin>>t;
    while(t--)
    {
        memset(s,0,sizeof(s));
        mp.clear();
        string str;
        getline(cin,str);
        getline(cin,str);
        int n=1;
        for(int i=0;i<str.size();i++)
        {
            if(str[i]==' ')n++;
            else if(str[i]=='\n')break;
            else s[n]+=str[i];
        }
        while(1)
        {
            string a,b,c;cin>>a>>b>>c;
            if(b=="does")
            {
                cin>>a;
                cin>>a;
                break;
            }
            mp[c]=true;
        }
        for(int i=1;i<=n;i++)
        if(!mp[s[i]])cout<<s[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：xzy_caiji (赞：1)

简单模拟。

开一个 `map` 统计一下即可。

注意，这题不能用 `cin`，得用 `getline+stringstream`。

~~本人爱用 `STL`~~

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[105];
int main(){
	int t;cin>>t;
	char c;scanf("%c",&c);
	while(t--){
		map<string,bool>m;string s;
		getline(cin,s);stringstream ss;
		ss<<s;int n=0;
		while(ss>>s){
			a[++n]=s;m[a[n]]=1;
		}
		ss.clear();
		while(getline(cin,s)){
			if(s=="what does the fox say?")break;
			if(s=="\n")continue;
			ss.clear();ss<<s;ss>>s;ss>>s;ss>>s;m[s]=0;
		}
		for(int i=1;i<=n;i++)if(m[a[i]])cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Li2021 (赞：1)

## P7008 题解

### 题意

给若干个字符串表示动物叫声，再给出若干个字符串表示非狐狸所发出的叫声，求可能为狐狸发出的声音字符串。

### 解题思路

我们先将一行所有的动物叫声个数统计，将统计出的动物叫声个数设为 $n$，再设一个布尔数组 $flg$，表示该动物叫声是否不是狐狸发出的叫声。每次给出非狐狸发出的叫声的字符串，设为 $s_i$，进行循环，查找它是否是非狐狸发出的声音，如果是，那么 $flg_i$ 就设为 true，即它并不是狐狸发出的叫声。最后循环查找每个动物叫声是否不是狐狸发出的声音，如果不是，进行输出即可。

### 代码

```cpp
#include <iostream>
#include <cstring>
#define N 102
using namespace std;
string tmp,tmp1,tmp2,tmp3,s[N];
bool flg[N];  //是否不是狐狸的叫声
int main(){
	int T;
	cin>>T;
	getline(cin,tmp);
	while(T--){
		memset(flg,0,sizeof flg);
		getline(cin,tmp);
		int len=tmp.length(),cnt=1;
		s[1]="";
		for(int i=0;i<len;i++){
			if(tmp[i]==' ')  cnt++,s[cnt]="";
			else  s[cnt]+=tmp[i];
		}
		while(cin>>tmp1>>tmp2>>tmp3,tmp2=="goes")  for(int i=1;i<=cnt;i++)  if(s[i]==tmp3)  flg[i]=1;
		for(int i=1;i<=cnt;i++)  if(!flg[i])  cout<<s[i]<<" ";
		getline(cin,tmp);
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：东灯 (赞：1)

罕见的 Node.js 题解。

题意理解就是给出一大串动物叫声，排除已知动物的叫声，剩下的均为狐狸叫，输出这些狐狸叫。

考虑使用 Node.js 如何处理直接读入进来的串，去除第一行后对于每组询问的第一行直接采用 `split(' ')` 形成数组 `line`，接下来统计已知动物的声音形成一个屏蔽数组 `shield`，输出时只需要使用 `shield.includes` 检测是否已知即可。

代码如下：

```javascript
const fs=require('fs')
const data=fs.readFileSync('/dev/stdin')
const result=data.toString('ascii').trim().split('\n');
let T=Number(result.shift());
while(T--){
    let line=result.shift().split(' '),shield=[];
    while(true){
        if(result[0]!="what does the fox say?")shield.push(result.shift().split(' ')[2]);
        else{
            result.shift();
            break;
        }
    }
    line.filter(v=>!shield.includes(v)).forEach(v=>process.stdout.write(v+' '))
    process.stdout.write('\n');
}
```


---

