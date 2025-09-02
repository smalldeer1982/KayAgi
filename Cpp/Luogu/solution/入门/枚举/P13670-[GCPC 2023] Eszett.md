# [GCPC 2023] Eszett

## 题目描述

对于正在学习德语的人来说，字母“ß”（称为 *Eszett* 或 *sharp S*）通常会让人感到非常困惑。
这个字母是德语独有的，看起来类似于“b”，但发音像“s”。

![](https://cdn.luogu.com.cn/upload/image_hosting/u376ek1e.png)

:::align{center}
Python 中 $\texttt{upper}$ 函数的演示
:::

更让人困惑的是，直到几年前，标准德语正字法中只存在小写的“ß”。
在需要大写“ß”的场合，例如法律文件和商店招牌中，
它通常（现在也常常如此）被大写双字母“SS”所替代。
2017 年，德语正式引入了大写“ẞ”，从此可以在这些场合中使用。

除了让外国人困惑之外，用“SS”替代“ß”的做法还会引入一些歧义，因为一个包含一个或多个“SS”的大写单词，
可能对应多个不同的小写单词，具体取决于每个“SS”究竟是大写的“ß”还是“ss”。

给定一个大写单词，找出所有可能由它转换而来的小写单词。
由于字母“ß”不属于 ASCII 范围，请用大写字母“B”来代替。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
AUFREISSEN```

### 输出

```
aufreissen
aufreiBen```

## 样例 #2

### 输入

```
MASSSTAB```

### 输出

```
massstab
maBstab
masBtab```

## 样例 #3

### 输入

```
EINDEUTIG```

### 输出

```
eindeutig```

## 样例 #4

### 输入

```
S```

### 输出

```
s```

## 样例 #5

### 输入

```
STRASSE```

### 输出

```
strasse
straBe```

# 题解

## 作者：volatile (赞：5)

# 题目大意

先将 $s$ 转小写，然后输出，然后你可以将两个连续的 $\texttt{S}$ 转换成一个 $\texttt{B}$，由于最多只有 $3$ 个 $\texttt{S}$，所以每次只需要考虑一个相邻的 $\texttt{S}$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
        cout<<s[i];
    }
    cout<<endl;
    for(int i=1;i<s.size();i++){
        if(s[i]==s[i-1]&&s[i]=='s'){
            for(int j=0;j<i-1;j++) cout<<s[j];
            cout<<'B';
            for(int j=i+1;j<s.size();j++) cout<<s[j];
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：yeziling (赞：3)

### 题解: P13670 [GCPC 2023] Eszett

[传送门](https://www.luogu.com.cn/problem/P13670)
### 题目分析：
我们对于字符连续的 $SS$ 可以有两种解释：

解释 $1$：将其当做单独的 $S$。

解释 $2$：将其当做 $B$。

### 思路：
我们遍历过去，一但遇到 $S$ 我们就进行判断，否则就转换成小写字符，在过程中我们进行去重操作。

### Code:

```cpp
#include<bits/stdc++.h>
#define QwQ return 0;
#define ll long long
#define endl '\n'
using namespace std;
string s1[200]; //保存答案
int main(){
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        s[i]=s[i]+32; //将字符转换成小写
    }
    int len=s.size();
    int k=0;
    for(int i=0;i<(1<<len);i++){
        string word="";
        for(int j=0;j<len;){
            //判断是否转换成“B”
            if((i&(1<<j))&&s[j]=='s'&&s[j+1]=='s'&&j+1<len){
                word+='B'; //将连续的“SS”转换成“B”
                j+=2;
            }else{
                word+=s[j];
                j+=1;
            }
        }
        bool flag=true; //去重操作
        for(int i=1;i<=k;i++){
            if(s1[i]==word){
                flag=false;
                break;
            }
        }
        if(flag){ //如果没出现过就加进去
            k++;
            s1[k]=word;
        }
    }
    for(int i=1;i<=k;i++){
        cout<<s1[i]<<endl;
    }
    QwQ;
}
```

---

## 作者：_Emperorpenguin_ (赞：2)

## 题意简介

将输入的字符串大写转小写。字符串中的字串  ```ss``` 可以替换为 ```B```。试求出替换后所有可能的字符串。

## 分析

很水的一道题。最大的难点是翻译。

首先当然要大写转小写。

将字符串遍历一遍。每找到一个 ```ss``` 串就将其替换，然后输出替换后的字符串，然后复原。

由于题目保证 ```s``` 出现的次数不超过 $3$ 次，即替换次数最多一次，所以替换后直接输出是可行的。

## Code

```cpp

#include <bits/stdc++.h>
using namespace std;

string s;
int n;

int main(){
	cin>>s;
	n=s.length();
	for(int i=0;i<n;i++)
		s[i]+='a'-'A';
	cout<<s<<endl;
	for(int i=1;i<n;i++)
		if((s[i]==s[i-1])&&(s[i]=='s'))
			cout<<s.substr(0,i-1)+"B"+s.substr(i+1,n-1)<<endl;
	return 0;
}

```

---

## 作者：_WCW_ (赞：1)

## 题目大意
输出字符串 $s$ 的所有字符转换为小写字母后的字符串，之后寻找 $s$ 中所有相邻的两个字母 ```S```，并将两个 ```S``` 替换为字母 ```B``` 后输出替换后的小写字母形式的字符串。
## 解题思路
循环遍历字符串 $s$，当找到相邻的两个 ```S``` 后遍历输出原串，当遇到之前找到字母的 ```S``` 时输出 ```B```，然后跳过一位继续输出。
## [AC](https://www.luogu.com.cn/record/229885362) 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
    cin>>s;
    for(char c:s) putchar(c+32);//输出一遍小写形式的字符串
    putchar('\n');
    for(int i=0;i<s.size()-1;i++)//遍历字符串
    {
        if(s[i]=='S' && s[i+1]=='S')//找到相邻的两个S
        {
            for(int j=0;j<s.size();j++)//遍历输出
            {
                if(j==i)//如果当前位置正好是找到的S
                {
                    putchar('B');//输出B
                    j++;//跳过一位
                }
                else putchar(s[j]+32);//否则转小写正常输出
            }
            putchar('\n');
        }
    }

    return 0;
}
```

---

## 作者：TLE_qwq (赞：1)

### 题目大意 

本题让你处理德语中特殊字母 Eszett（用 `B`表示）的大小写转换歧义。在德语中：
- 一个包含 `SS` 的大写单词中，`SS` 可能来源于两种形式：
  - 对应 `ss`。
  - 对应 `B`。

我们需要找出给定单词可能对应的所有形式。

### 解题思路

因为数据范围比较小，所以可以用递归，遍历字符串的每个位置并处理所有可能的转换：
- 对于非 `S` 字符，不用犹豫，直接转换为小写。
- 对于 `S` 字符：
   - 可以单独转换为 `s`。
   - 若下一个字符也是 `S`，则可以将这两个 `S` 一起转换为 `B`。

注意，输出的顺序无所谓。 

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
void f(const string& s, int i, string ji, vector<string>& res) {
    if (i == s.size()) {
        res.push_back(ji);
        return;
    }
    if (s[i] != 'S') {
        f(s, i + 1, ji + (char)/*转换为小写*/tolower(s[i]), res);
    } else {
        f(s, i + 1, ji + 's', res);//递归
        if (i + 1 < s.size() && s[i + 1] == 'S') {
            f(s, i + 2, ji + 'B'/*变成 B*/, res);
        }
    }
}
int main() {
    string s;
    cin >> s;
    vector<string> res;
    f(s, 0, "", res);//开始字符串为空 
    for (string str : res) {
        cout << str << endl;
    }
    return 0;
}

```

---

## 作者：Clouds_dream (赞：1)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13670)

### 题目分析
我们遍历字符串，如果遇到 `S`，我们有两种选择：
1. 将这一位换成 `s`。
2. 检查下一位，如果是 `S`，我们可以换成 `B`。
::::warning[注意]
不要忘了将原字符串变为小写后再处理，还要输出小写的原字符串。
::::
### 代码实现
```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

string s;

signed main()
{
	fst
	cin>>s;
    for(int i=0;i<s.size();i++)s[i]+=32;
    cout<<s<<endl;
    for(int i=0;i<s.size();i++){
        if(i<s.size()-1&&s[i]=='s'&&s[i+1]=='s'){
            cout<<s.substr(0,i)<<'B'<<s.substr(i+2)<<endl;
        }
    }
	return 0;
}
```

---

## 作者：wangziyang202511036 (赞：1)

# 题解：P13670 [GCPC 2023] Eszett  
## 题目大意  
给定一个字符串 $s$，保证所有字母均为大写。当有两个大写字母 `S` 相邻时，它们两个就可以被替换成一个大写字母 `B`，求所有可能对应的小写字符串。
## 思路  
首先需要输出 $s$ 的全小写形式，可以使用 `tolower` 函数，同时将这个小写字符串保存在另一个字符串 $lower$ 中。

接着枚举 $s$，如果发现两个相邻的字母 `S` 就创建一个新的字符串 $cur$。因为最终要输出小写单词，所以先将小写字符串赋值给 $cur$，再把字母 `B` 换上去，最后输出就行了。
## 完整代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    string lower=s;//保存小写字符串
    for(int i=0;i<s.size();i++)
    {
        cout<<(char)tolower(s[i]);//注意要输出字符
        lower[i]=tolower(s[i]);
    }
    cout<<'\n';
    for(int i=0;i<s.size()-1;i++)
    {
        if(s[i]=='S'&&s[i+1]=='S')
        {
            string cur=lower;
            cur[i]='B';
            cur.erase(i+1,1);//i+1这个位置没有字符了要去掉
            cout<<cur<<'\n';//别忘了换行
        }
    }
    return 0;
}
```

---

## 作者：alice_c (赞：1)

## 题意

给你一个大写字符串 $s$，求 $s$ 肯能是从那些小写字符串转大写的。小写字符 $\tt{ß}$ 转大写后会变成 $\tt{SS}$。输出时用 $\tt{B}$ 代替 $\tt{ß}$。

## 思路

注意，题目中说字母 $\tt{S}$ 在字符串 $s$ 中最多出现 $3$ 次。如果 $s$ 中包含 $\tt{SSS}$，有三种选择，就是把 $\tt{SSS}$ 变成 $\tt{sss}$，$\tt{sB}$ 或 $\tt{Bs}$；否则，如果 $s$ 中包含 $\tt{SS}$，可以把它变成 $\tt{ss}$ 或 $\tt{B}$；否则，唯一一个选择就是把它转小写。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int main()
{
    cin >> s;
    n=s.size();
    for(int i=0;i<n;i++)
        s[i]=tolower(s[i]);//转小写
    if(s.find("sss")!=-1){
        int pos=s.find("sss");
        string s1=s,s2=s;
        cout << s1.replace(pos,3,"sB") << '\n';
        cout << s2.replace(pos,3,"Bs") << '\n';
    }
    else if(s.find("ss")!=-1){
        int pos=s.find("ss");
        string s1=s;
        cout << s1.replace(pos,2,"B") << '\n';
    }
    cout << s;
}
``````

---

## 作者：SXY83296647 (赞：0)

## 思路：
题目要求我们把一个全是大写字母的字符串转换成相应可能的小写字符串。根据题意，当发现字符串中有相邻的 `SS` 时，就把它换成大写字母 `B`，否则不更改。因为字符串中最多出现 3 次 `S`，于是我们可以先将大写字符串转换成小写字符串，然后遍历字符串进行判断，最后输出相应的字符串。
## AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
    cin>>s;
    for(int i=0;i<s.length();i++) s[i]+=32;//转换成小写字符串
    cout<<s<<'\n';//先输出小写字符串
    for(int i=0;i<s.length();i++){
        if(i<s.length()-1&&s[i]=='s'&&s[i+1]=='s'){
            cout<<s.substr(0,i)<<'B'<<s.substr(i+2)<<'\n';//若字符串中含有相邻的ss时改为B，再输出字符串
        }
    }
    return 0;
}
```

---

## 作者：_aszxqw_ (赞：0)

一道字符串操作的题。大概意思就是让我们先输出字符串的小写形式，再把字符串 `ss` 替换成 `B` 就可以了。       
### AC 代码
```
#include<bits/stdc++.h>  
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);  
    string s;  
    cin>>s;   
    int len=s.size(); 
    transform(s.begin(), s.end(), s.begin(), ::tolower);// 将字符串中的所有字符转换为小写
    cout<<s<<'\n';
    for(int i=0;i<len;i++){
        if(i+1<len){
            if(s[i]=='s'&&s[i+1]=='s'){  
                s[i]='B';// 将第一个s改为B
                s.erase(i+1, 1);// 删除第二个s
                cout<<s<<'\n';
                s[i]='s';// 将B改回s
                s.insert(i+1, "s");// 插入s
            }    
        }
    }
    return 0;  
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13670)
## 题目分析
希望审核大大给过。

这是一道考**字符串**的题，这道题是让我们先将这个字符串先改成小写字母并输出。并且把字符串中连续的两个 `s` 换成 `B`，如果有多种方法就输出多行即可。

由于数据非常小，所以可以 for 循环暴力查找两个相连的 `s`，并改成 `B`，输出并换行即可。

下面是本题代码。
## 题目[代码](https://www.luogu.com.cn/record/229795110)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
#define fre(s,s1) freopen(s,"r",stdin),freopen(s1,"w",stdout)
string s;
signed main() {
	speed
	cin>>s;
	for(int i=0;i<s.size();i++)s[i]=s[i]-'A'+'a';
	cout<<s<<'\n';
	for(int i=0;i<s.size()-1;i++){
		if(s[i]=='s'&&s[i+1]=='s'){
			for(int j=0;j<i;j++)cout<<s[j];
			cout<<"B";
			for(int j=i+2;j<s.size();j++)cout<<s[j];
			cout<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：mike_LYH (赞：0)

## 题目大意
给定一个使用大写字母组成的单词，需要把字母全部变成小写的。

但是，如果这个单词中含有两个相邻的 `S`（即 `SS`），那么这两个字母就有两种变法：
- 可以按照原来的方法变成小写的 `ss`。
- 可以变成**一个大写**的字母 `B`（两个变成一个）。

要求你输出所有可能对应的变化后的单词。
## 解题思路
对于这种会产生不同分支的题，我们可以使用搜索来做。

首先，遍历字符串，如果找到 `SS`，就产生两种分支，一种是把它变成 `ss`，另一种是把它变成 `B`；如果不是 `SS`，就把这个字母变成小写字母。

最后输出所有结果就行了。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int len;
string s;
void dfs(int k,string st){
	if(k==len){
		cout<<st<<endl;
		return ;
	}
	dfs(k+1,st+char(s[k]+32));//把当前字母变为小写的
	if(k+2<=len/*越界判断*/&&s.substr(k,2)=="SS"/*是否为SS*/)
	    dfs(k+2,st+'B');//把当前字母与下一个字母改成B
}
int main(){
    cin>>s;
    len=s.size();
    dfs(0/*字符串下标从0开始*/,""/*一开始啥也没有，是空串*/);
	return 0;
}
```

---

## 作者：yueyan_WZF (赞：0)

## 题意

给你一个字符串，首先需要将字符串转换为小写并输出。

接下来，你要对于转换后字符串中未更改过的 `ss` 更改为 `B`，每改完一次就输出，并恢复到原来的小写字符串。

## 做法

直接模拟即可，对于每次的 `ss` 如果未更改过，就更改并打上记号，避免重复。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int vis[1000004];
signed main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]<='Z'&&s[i]>='A') {
			s[i]=s[i]-'A'+'a';
		}
		cout<<s[i];
	}
	cout<<endl; 
	while(1){
		bool flag=0;
		int x;
		for(int i=0;i<s.size();i++){
			if(i<s.size()-1&&s[i]=='s'&&s[i+1]=='s'&&!vis[i]){
				vis[i]=1;
				x=i;
				flag=1;
				i++;
				
			}
		}
		if(flag){
			for(int i=0;i<s.size();i++){
				if(i==x)
					cout<<"B";
					i++;
				}
				else{
					cout<<s[i];
				}
			}
			cout<<"\n";
		}
		else break;
	}
}	

```

---

