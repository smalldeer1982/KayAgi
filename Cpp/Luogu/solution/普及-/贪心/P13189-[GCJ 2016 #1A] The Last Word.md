# [GCJ 2016 #1A] The Last Word

## 题目描述

在综艺节目 **The Last Word** 中，主持人会在一轮游戏开始时向选手展示一个由大写英文字母组成的字符串 $\mathbf{S}$。选手面前有一块最初为空的白板。接着，主持人会依次按照 $\mathbf{S}$ 中的顺序，将每个字母逐一呈现给选手。当主持人给出第一个字母时，选手需要把它写在白板上；这时白板上的内容就构成了游戏中的第一个单词（虽然它只有一个字母）。之后，每当主持人给出一个新字母，选手必须选择将其写在当前白板单词的开头或末尾，然后主持人再给出下一个字母（或游戏结束，如果没有更多字母）。

例如，对于 $\mathbf{S} = \text{CAB}$，选手在白板上写下 C 之后，可以有如下四种决策路径：

- 将 A 写在 C 前面，得到 AC，再将 B 写在 AC 前面，得到 $\text{BAC}$
- 将 A 写在 C 前面，得到 AC，再将 B 写在 AC 后面，得到 $\text{ACB}$
- 将 A 写在 C 后面，得到 CA，再将 B 写在 CA 前面，得到 $\text{BCA}$
- 将 A 写在 C 后面，得到 CA，再将 B 写在 CA 后面，得到 $\text{CAB}$

当选手按规则写完 $\mathbf{S}$ 的所有字母后，白板上的单词就称为 **last word**。如果选手最终得到的单词，在所有可能得到的 last word 的按字典序排序后的列表中排在最后，则选手获胜。对于上面的例子，获胜的 last word 是 $\text{CAB}$（恰好与原始字符串相同）。对于 $\mathbf{S} = \text{JAM}$，获胜的 last word 是 $\text{MJA}$。

你是下一个参赛选手，主持人刚刚向你展示了字符串 $\mathbf{S}$。请问，你应当如何操作，才能获得获胜的 last word？


## 说明/提示

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 100$。

**小数据集（9 分，测试集 1 - 可见）**

- $1 \leqslant \mathbf{S}$ 的长度 $\leqslant 15$。

**大数据集（11 分，测试集 2 - 隐藏）**

- $1 \leqslant \mathbf{S}$ 的长度 $\leqslant 1000$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
7
CAB
JAM
CODE
ABAAB
CABCBBABC
ABCABCABC
ZXCASDQWE```

### 输出

```
Case #1: CAB
Case #2: MJA
Case #3: OCDE
Case #4: BBAAA
Case #5: CCCABBBAB
Case #6: CCCBAABAB
Case #7: ZXCASDQWE```

# 题解

## 作者：Gongyujie123 (赞：4)

## [P13189 [GCJ 2016 #1A] The Last Word](https://www.luogu.com.cn/problem/P13189) 题解
### 1. 题目大意
给定一个字符串 $S$，我们有一个空的字符串 $W$，从头到尾依次将 $S$ 的每个字符选择加入 $W$ 的开头或末尾，求字典序最大的 $W$。
### 2. 思路分析
很容易想到，这道题是**贪心**。

题中要求字典序最大，我们很容易想到一个贪心方案：将字典序大的插入开头，将字典序小的插入结尾。具体地，设 $n$ 为字符串 $S$ 的长度，对于 $S_i(i \in [1, n])$，如果它的字典序**大于或等于** $W_1$（$W$ 的第一个字符），就将它插入 $W$ 的开头，否则将它插入 $W$ 的末尾。

$W$ 可以是普通的 `string` 类型，每次插入的代码如下：
```cpp
if (s[i] >= w[i]) {
	w = s[i] + w;
} else {
	w = w + s[i];
}
```

但是，我在这里介绍一种不一样的方法，用 STL 中的双端队列 `deque`。它的特点也正如它的名字，可以在队列的开头和末尾插入或删除元素。这里只介绍下需要的几个成员函数：  
`dq.clear()` 清空 `dq`；  
`dq.push_back(x)` 在 `dq` 末尾加入 `x`；  
`dq.push_front(x)` 在 `dq` 开头加入 `x`；  
`dq.front()` 返回 `dq` 的第一个元素。

所以，双端队列的代码就出来了：

```cpp
if (a[i] >= dq.front()) {
	dq.push_front(a[i]);
} else {
	dq.push_back(a[i]);
}
```
### 3. AC 代码

[AC 记录](https://www.luogu.com.cn/record/223595467)。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
deque<char> dq;
signed main() {
	int n;
	cin >> n;
	for (int t = 1; t <= n; t++) {
		dq.clear();  // 清空 dq
		string a;
		cin >> a;
		dq.push_back(a[0]);
		for (int i = 1; i < a.size(); i++) {
			if (a[i] >= dq.front()) {  // 判断 a[i] 是否大于或等于 dq 的第一个字符，是的话就将它插入 dq 的开头，否则将它插入 dq 的末尾
				dq.push_front(a[i]);
			} else {
				dq.push_back(a[i]);
			}
		}
		cout << "Case #" << t <<": ";  // 输出
		for (auto i : dq) {
			cout << i;
		}
		cout << endl;
	}
	return 0;
}
// - [P13189 [GCJ 2016 #1A] The Last Word](https://www.luogu.com.cn/problem/P13189)
```

---

## 作者：Chenyuze24 (赞：2)

### 前置知识与题意
首先做这道题之前我们需要了解什么是字典序。字典序是以第 $i$ 个字符作为第 $i$ 关键字进行大小比较，得到的一个顺序。这就足够解这道题了，这道题中是求字典序最大的排列，那么比如 $\text{ABC}$ 的最大字典序排列就是 $\text{CBA}$。那么这道题就是一个一个字符读进来，可以放到字符串的前面或后面，让字典序最大。
### 分析
首先记答案为 $ans$，读入的字符串为 $str$，那么第一个进来的字符就是 $str_0$，所以```ans=str[0]```。然后就从 $1$ 开始遍历 $str$，如果 $str_i<ans_0$，那么就把 $str_i$ 加如 $ans$ 末端，否则就放到最前面。
### 细节
- 有多组数据。
- 记得初始化 $ans$。
- 从 $1$ 开始遍历 $str$。
- 看清输出的格式。
### 代码
以下是完整代码。

```cpp
#include<bits/stdc++.h>//万能头。
using namespace std;
int t;
string str;//读入的字符串。
string ans;//操作的字符串，也就是字典序最大的排列。
void solve()
{
	cin>>t;//多组数据。
	for(int j=1;j<=t;++j)
	{
		ans="";//清空。
		cin>>str;//读入。
		ans=str[0];
		for(int i=1;i<str.size();++i)//从1开始遍历。
		{
			if(ans[0]>str[i])//判断。
			{
				ans+=str[i];
			}
			else if(ans[0]<=str[i])
			{
				ans=str[i]+ans;
			}
		}
		cout<<"Case #"<<j<<": "<<ans<<'\n';//输出。
	}
}
int main()
{
	solve();
	return 0;
}
```

---

## 作者：ELSIA (赞：2)

# 思路：
当新一个字母大于或等于第一个字母时就把这个字母时就把这个字母放到第一个字母前面，就变成了新的第一个字母。如果小于第一个字母，就把它放到后面。
# 代码实现：

```cpp
#include <bits/stdc++.h>//万能头万岁\^o^/ 
using namespace std;
string cmp (string n){//定义一个函数，用来处理第 i 个字符串。 
	string m = "";
	m = n[0] + m;
	for(int i = 1 ; i < n.size() ; i++){
		if(n[i] > m[0]){ 
			m = n[i] + m;//如果大于或等于第一个字母,就把它放到前面。 
		}else{
			m = m + n[i];//如果小于第一个字母，就把它放到后面。
		}
	}
	return m ;
}
int main(){
	int n;
	cin >> n;
	for(int i = 1 ; i <= n ; i++){
		string a;
		cin >> a;
		cout << "Case #"<< i << ':' << " " << cmp(a) << endl;//注意要有空格。 
	}
	return 0;//完美结束O(∩_∩)O！ 
}
```
完结撒花。

---

## 作者：Hkb150429 (赞：2)

## 题意

每当主持人给出一个新字母，选手必须选择将其写在当前白板单词的开头或末尾，然后主持人再给出下一个字母（或游戏结束，如果没有更多字母）。

## 思路
用一个字符组把新的字符串存起来，如果新的字符大于首字符，则放到首字符前面，否则放到末字符后面。

## 思路

```
#include<bits/stdc++.h>
using namespace std;
char a[2005];
int main(){
    int t,kai,jie;
    string s;
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>s;
        cout<<"Case #"<<i<<": ";
        kai=1002,jie=1002;
        a[1002]=s[0];
        for(int j=1;j<s.size();j++){
            if(s[j]>=a[kai])a[--kai]=s[j];
            else a[++jie]=s[j];
        }
        for(int j=kai;j<=jie;j++){
            cout<<a[j];
        }
        cout<<endl;
    }
}
```

---

## 作者：LG086 (赞：2)

你有一个空的字符串 $s$。现在依次给出若干个字母，每个字母只能放到字符串 $s$ 的头或尾，让你搞出一个字典序最大的字符串。

显然，要想字典序大，那么字典序大的字母就放前头，小的放后头。记当前给出的字母是 $ch_i$。若此时 $s$ 为空，填入 $ch_i$；若 $s_0 \le ch_i$，则将 $ch_i$ 放到 $s$ 的前头；若 $s_0 \gt ch_i$，把 $ch_i$ 弄到 $s$ 末尾就行了。

下给出核心代码。

```cpp
string s;cin>>s;
string ans="";
ans=ans+s[0];
for(int i = 1;i < s.size();i ++){
 if(s[i]>=ans[0])ans=s[i]+ans;
 else ans=ans+s[i];
}
```

---

## 作者：__szh_DNCB__ (赞：1)

蒟蒻的第五篇题解。

### 正文

注意到要使字典序尽量大，所以只需要让字典序大的往最前面放，不够大的都往最后面放。这个“大”和“不大”取决于是否大于等于答案字符串的首位字符。

用公式表达为，如果令答案字符串的首位为 $ans_0$，新插入字符为 $c$，则如果 $c \ge ans_0$ 则把 $c$ 插入答案字符串的开头，否则插入答案字符串的末尾。

特别地，由于空字符串不能取开头，所以第一个字符应当手动插入，即代码中后有注释的一行。

老规矩，请注意 GCJ 题目的输出格式，建议使用 `printf` 输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(int Time){
	string s;
	cin >> s;
	string ans = "";
	ans += s[0]; // 手动插入
	for (int i=1;i<=s.length();i++){
		if (s[i] >= ans[0])ans = s[i] + ans;
		else ans += s[i];
	}
	cout << "Case #" << Time << ": " << ans << '\n';
}
int main(){
	int T;
	cin >> T;
	for (int i=1;i<=T;i++){
		solve(i);
	}
	return 0;
}
```

### 吐槽
有没有眼睛好的看看这是哪里测出来 WA 了。反正交上去能过。
![](https://cdn.luogu.com.cn/upload/image_hosting/hwnwvn6x.png)

---

## 作者：yangdezuo (赞：1)

## 解析
### 题目大意
我们要根据输入顺序，拼接出一个字典序最大的字符串。

### 方法
[**~~如果不知道字典序可以重开了（点这里）。~~**](https://baike.baidu.com/item/%E5%AD%97%E5%85%B8%E5%BA%8F/7786229)

正题：我们可以准备一个新的空字符串 $T$ ，先把读入的字符串 $S$ 的第一位放进去，对于接下来的每一位，如果比 $T$ 的第一位小，就放到最后；反之，若大于或等于则放到最前面。

考虑到要在前后合并，用 string 类型定义可以直接进行比较与合并操作。

## 参考代码

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
int t;
string s,k;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>s;
		k=s[0];
//		k=s.substr(1);
		for(int i=1;i<s.size();i++)
			if(s[i]>=k[0]) k=s[i]+k;
			else k+=s[i];
		cout<<"Case #"<<o<<": "<<k<<'\n';
	}
}
/*
*/
```

---

## 作者：LiJunze0501 (赞：1)

# 简化题意
首先给你若干个字母和一个空字符串，将这些字母按顺序插入字符串，每次可以放在最前面或最后面，求最后字典序最大的字符串。
# 分析
要求字典序最大，就在每次插入时判断，如果是空的，直接放；如果比第一个字母大或该字母是第一个字母，那么放在最前面会使字典序变大，就放最前面；如果比第一个字母小，那么放在最前面会使字典序变小，就放最后面。  
我们拿 `ABCABCABC` 来举例：  
* A：字符串为空，直接插入，字符串为 `A`。  
* B：比 A 大，放最前面，字符串为 `BA`。  
* C：比 B 大，放最前面，字符串为 `CBA`。  
* A：比 C 小，放最后面，字符串为 `CBAA`。  
* B：比 C 小，放最后面，字符串为 `CBAAB`。  
* C：和 C 相同，放最前面，字符串为 `CCBAAB`。  
* A：比 C 小，放最后面，字符串为 `CCBAABA`。  
* B：比 C 小，放最后面，字符串为 `CCBAABAB`。  
* C：和 C 相同，放最前面，字符串为 `CCCBAABAB`。

~~肉眼可见，和样例输出相同。~~ 
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s,ans;
        cin>>s;
        ans+=s[0];
        for(int j=1;j<s.size();j++)
            if(s[j]>=ans[0]) ans=s[j]+ans;
            else ans+=s[j];
        cout<<"Case #"<<i<<": "<<ans<<"\n";
    }
}
```

---

## 作者：封禁用户 (赞：1)

# [P13189 [GCJ 2016 #1A] The Last Word](https://www.luogu.com.cn/problem/P13189)
## 题目介绍：
在综艺节目 **The Last Word** 中，给定一个由大写字母组成的字符串 $\mathbf{S}$，选手需要通过以下规则构造最终字符串：
1. 初始白板为空。

2. 逐个处理 $\mathbf{S}$ 的字符，对于每个新字符，第一个字符必须直接写在白板上，后续字符可以选择添加到当前字符串的开头或末尾。

3. 目标是在所有可能的构造方式中，获得字典序最大的最终字符串。

## 分析做法：
很简单的一道**贪心**题。

因为要求字典序最大，也就是说越往前的字符要越大。

因此，策略如下：
1. 对于当前字符 $c$ 和当前字符串 $T$。

2. 若 $c \geq T[0]$，将 $c$ 加到开头。

3. 否则加到末尾。

代码实现：
```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
string gw(const string& s) {
    string s2;
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (s2.empty()) {
            s2 += c;
        } else {
            if (c >= s2[0]) {
                s2 = c + s2;
            } else {
                s2 += c;
            }
        }
    }
    return s2;
}

signed main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        string s;
        cin >> s;
        string w = gw(s);
        cout << "Case #" << t << ": " << w << endl;
    }
    return 0;
}
```

谢谢观看，求过求赞。

---

## 作者：Little_d (赞：0)

## 思路
先向答案字符串中添加输入的第一个字符，然后遍历剩下的字符，如果这个字符比答案字符串的第一个字符要大，那么将这个字符插入到答案的最前面，这样可以让字典序更大，否则加到后面，让损失尽量小。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        string ans="";
        ans+=s[0];
        for(int j=1;j<s.size();j++){
            if(s[j]>=ans[0])ans=s[j]+ans;
            else ans+=s[j];
        }
        cout<<"Case #"<<i<<": "<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：_ByTT_ (赞：0)

# 题解：P13189 [GCJ 2016 #1A] The Last Word
### 题意
一个字符串，但每次只给你一个字符。你要保证你的字符串永远是所有可能的排序中字典序最大的。
### 思路
因为要求字典序最大，那么我们可以在每次输入时将字典序大的尽可能放在最前面，否则放后面。

需要注意的是**大于等于**就放前面，否则放后面。而不是**大于**放前面，否则放后面。因为是字典序最大的。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;cin>>T;
	for(int Tt=1;Tt<=T;Tt++){
		string s,ans;cin>>s;
		ans=s[0];
		for(int i=1;i<s.length();i++){
			if(s[i]>=ans[0]) ans=s[i]+ans;
			else ans=ans+s[i];
		}
		cout<<"Case #"<<Tt<<": "<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Zqx_Vector_2014 (赞：0)

## 题意：

给出字符串 $S$，现在依次给出若干个字母，每个字母只能放到字符串 $S$ 的头或尾，让你构造出一个字典序最大的字符串。

## 思路：

首先看时限。嗯……五秒，所以直接暴力解题。

弄一个函数 $\operatorname{str}$ 来得出合法字符串。做法就是：

- 定义 $ss$ 和 $sstr$。

- 将 $sstr$ 变为 $ss$ 的第一个字符。

- 然后循环遍历 $ss$，每次遍历时判断一下 $ss_i$（即 ss 的第 $i-1$ 个字符） 是否**大于等于**（一定要有等于，不然和开头相等的会被刷到后面） $sstr_0$（即 $sstr$ 的第一个字符）。若 $ss_i \ge sstr_0$，则 $sstr$ 的开头加上 $ss_i$；否则 $sstr$ 的末尾加上 $ss_i$。

```cpp
string str(string ss){
	string sstr;sstr+=ss[0];
	for(int i=1;i<ss.size();i++){
		if(ss[i]>=sstr[0]) sstr=ss[i]+sstr;
		else sstr=sstr+ss[i];
	}return sstr;
}
```

接下来循环输入调用函数 $\operatorname{str}$ 在输出就做完了。

# Code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define _n "\n"
#define _t "\t" 
const int mod=1e9+7;
const int inf=1e13;
const int bze=16;
using namespace std;
int max(int A,int B){return (A>B)?A:B;}
int min(int A,int B){return (A<B)?A:B;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int lcm(int a,int b){return a*b/gcd(a,b);}
string str(string ss){
	string sstr;sstr+=ss[0];
	for(int i=1;i<ss.size();i++){
		if(ss[i]>=sstr[0]) sstr=ss[i]+sstr;
		else sstr=sstr+ss[i];
	}return sstr;
}signed main(){
	ios::sync_with_stdio(0),
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for(int i=0;i<n;i++){
		string ss;
		cin>>ss;
		ss=str(ss);
		printf("Case #%lld: %s\n",i+1,ss.c_str());
	}
}
```

---

## 作者：shiziyu111 (赞：0)

# 题目大意

从字符串第 $1$ 位到最后一位依次填入白板中字符串的前或后方，构成一个新字符串，使得最后的字符串在所有可构成的字符串中字典序最大，求最大的字符串。

# 分析

我们来模拟一下这个过程：假如你有一个字母和一个字符串，你会怎么做？

很显然，为了使最大的字符在较前的位置，我们要比较一下字符与字符串第一位的关系，如果字符跟字符串比较大或相同，那么我们把它放在靠前的位置，不断重复此操作，最后得到答案。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		string s;
		cin>>s;
		int a[2001],hh=1000,tt=1000;
		a[hh]=s[0]-'A'+1;;
		for(int i=1;i<s.size();i++)
		{
			if(s[i]-'A'+1>=a[hh])
			{
				hh--;
				a[hh]=s[i]-'A'+1;
			}
			else
			{
				tt++;
				a[tt]=s[i]-'A'+1;	
			}
		}
		cout<<"Case #"<<t<<": ";
		for(int i=hh;i<=tt;i++)
		{
			cout<<(char)(a[i]-1+'A');
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Zjb13927701829 (赞：0)

# P13189 The Last Word 题解

[题目传送门](https://www.luogu.com.cn/problem/P13189)

## 题意：
题目给我们一个字符串，让我们把这个字符串**逐个**存入另一个答案字符串，每次添加只能添加在答案字符串的开头与结尾，使这个字符串的字典序**尽量靠后**。
## 思路：
由于每次添加只能添加在答案字符串的开头与结尾，所以还是挺简单的。只要判断当前原串字符与答案串首字符的字典序大小就能决定放在开头还是结尾。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>s;
		string lw="";//这里不能直接写string lw=s[0];
		lw=lw+s[0]; 
        for(int j=1;j<s.size();j++)
            if(s[j]>=lw[0]) lw=s[j]+lw;//注意对比的是 Last Word的第一个字符
            else lw=lw+s[j];
        cout<<"Case #"<<i<<": "<<lw<<endl;
    }
    return 0;
}//完结撒花
```
`如果有错请各位大佬指出，虚心才是好习惯！`

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13189)

### 思路

这道题考察的是思维与模拟。

首先我们定义一个答案字符串，接着按照题目说的，先把第一个字符放进答案字符串，然后我们从第二个字符开始，如果它比答案字符串的第一个字符要大或者是等于，那么就把它放在第一个字符前面，否则就放在第一个字符后面。

最后输出答案字符串即可。

记得多测清空还有输出格式。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s,s1;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>s;
		cout<<"Case #"<<i<<": ";//注意输出格式
		s1=s[0];//注意清空
		for(int j=1;j<s.size();j++)
		{
			if(s[j]>=s1[0])  s1=s[j]+s1;
			else  s1+=s[j];//策略
		}
		cout<<s1<<endl;//输出，记得换行
	}
	return 0;
} 
```

---

