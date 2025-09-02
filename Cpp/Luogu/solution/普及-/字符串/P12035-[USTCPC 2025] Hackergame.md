# [USTCPC 2025] Hackergame

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/s9gnt6kl.png)

## 题目描述

hackergame 是 USTC 特色比赛之一，也是克露丝卡尔酱心心念念的比赛之一。

克露丝卡尔酱的同学小 H 在打 hackergame 时，发现当复制一个 flag 时，会将一些其它的内容（如感叹号、句号等）一同复制，从而上传答案时造成错误。

克露丝卡尔酱打算编写一个程序来解决该问题，该程序会读取一个字符串，在当中选择一个连续的子串，满足是一个合法的 flag，并将其输出。如果所有子串都不是合法的，输出 `NOT FOUND`。

一个字符串为一个合法的 flag，当且仅当满足以下性质：

+ 该字符串以 `flag{` 开头，以字符 `}` 结尾。
+ 在 `flag{` 和 `}` 之间，不存在字符 `{` 和字符 `}`，可以存在任何其它可见字符。

克露丝卡尔酱想要尽快帮助她的同学，但她的同学想要朴素的代码。请帮她完成这个程序！

## 说明/提示

第一个样例中，设字符串的下标位置从 $0$ 开始，则输出的字符串的第一个字符下标位置为 $1$，最后一个字符下标位置为 $34$。输出的字符串满足合法的 flag 所有的要求。

## 样例 #1

### 输入

```
{flag{y0u_ar3_g0od_at_constructi0n}{}}```

### 输出

```
flag{y0u_ar3_g0od_at_constructi0n}```

## 样例 #2

### 输入

```
flag{flag{{}}}}}}```

### 输出

```
NOT FOUND```

# 题解

## 作者：_____Elysia_____ (赞：3)

字符串的入门题。

根据题目要求一个 flag 的长度至少是 $6$，如果这个字符串长度小于 $6$ 可以直接忽略掉。

然后我们枚举字符串从第 $1$ 个字符到倒数第 $5$ 个字符，如果从这个字符开始连续 $5$ 个字符依次是 `flag{`，就进入下一层判断。

下一层判断是从 `flag{` 右边一个字符开始，如果找到一个 `{` 就说明后面不可能有合法的 flag 了，直接跳过。如果找到 `}`，就说明这是一个合法的 flag，输出就行。

最后如果没有合法的 flag，输出 `NOT FOUND`。


```cpp
#include<iostream>
using namespace std;
int main(){
    string s;
    cin>>s;
    if(s.size()<6){
        cout<<"NOT FOUND";
        return 0;
    }
    for(int i=0;i<=s.size()-5;i++){
        if(s.substr(i,5)=="flag{"){
            for(int j=i+5;j<s.size();j++){
                if(s[j]=='{')break;
                if(s[j]=='}'){
                    cout<<s.substr(i,j-i+1);
                    return 0;
                }
            }
        }
    }
    cout<<"NOT FOUND";
}
```

---

## 作者：zyr2011 (赞：2)

一道简单的字符串题，这里我用了一种更适合萌新的**循环遍历字符串**的方法来解决。
### 详细解法
首先读题，我们容易发现，当出现```flag{```后，只要**中间没有**```{```这个字符，**且**后面有一个```}```来结尾，这个 flag 就**一定合法**，反之则**不合法**。   
为什么不用考虑中间出现```}```的情况呢？因为**当前面没有```{```的情况下**，只要有一个```}```结尾，我们就可以把它视为一个**完整的** flag，而不是判定为不合法。  
综上所述，我们可以发现，只要将 $s$ 遍历一遍，在遍历到```flag{```时，用另一个循环（即循环嵌套）从```flag{```开始遍历 $s$，如果**当前遍历的字符为```{```**，那么**停止循环**，将```｛```作为第一重循环的起点，继续遍历 $s$，如果**当前遍历的字符为```}```**，那么**停止循环**，将**记录的答案**（即第一个合法的 flag）**输出**，**否则**记录当前的遍历到的字符。如果遍历完  $s$ 仍没有找到合法的 flag，那么输出```NOT FOUND```。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
	string s,ans;cin>>s;
	bool flag=false;
	int len=s.size();//获取s的长度 
	for(register int i=0;i<len;++i){//遍历字符串s 
		if(s[i]=='f' and s[i+1]=='l' and s[i+2]=='a' and s[i+3]=='g' and s[i+4]=='{'){//满足第一个合法条件 
			ans+="flag{";//记录初始答案 
			for(register int j=i+5;j<len;++j){//从{后面的一个字符开始遍历 
				if(s[j]=='{'){//遍历到{ 
					i=i+j-i;//继续第一重循环 
					ans="";//重置答案 
					break;
				}
				if(s[j]=='}' and !flag){//遍历到}，且是第一个合法字符串 
					flag=true; 
					ans+=s[j];//记录} 
					break;
				}
				ans+=s[j];//记录当前字符 
			}
		}
		if(flag){//有标记 
			cout<<ans<<endl;break;//输出记录的答案 
		}
	}
	if(!flag){//s没有合法答案 
		cout<<"NOT FOUND"<<endl;//输出 NOT FOUND
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：2)

赛时就过了这一道题，被队友带飞成为 rk9。在此处拜谢 @int_stl。

这题很显然可以判断找出所有相邻的左右括号，在判断左括号的左边是否合法即可。由于找的是相邻的左右括号，所以括号之间不可能存在其他括号了，写起来很简单。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;
	int lz = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '{')
			lz = i;
		else if (s[i] == '}' && lz) {
			if (lz - 4 >= 1 && s[lz - 4] == 'f' && s[lz - 3] == 'l' && s[lz - 2] == 'a' && s[lz - 1] == 'g') {
				for (int j = lz - 4; j <= i; j++)
					cout << s[j];
				return 0;
			}
		}
	}
	cout << "NOT FOUND";
}
```

---

## 作者：hgckythgcfhk (赞：1)

广告：[USTCPC2025 题解汇总（部分）](https://www.luogu.com.cn/article/xl8dsc9j)。

对于每个 `flag{` 找到下一个 `}` 随便找一组使得中间没有 `{` 直接模拟即可。

以下是线下选手 $42$ 队提供的赛时代码，非常感谢 $42$ 队。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+10;
char a[N];
bool f=false;
int v=0,t=0;
int main(){
	cin>>a;
	int len=strlen(a);
	//cout<<len<<endl;
	for(int i=4;i<len;i++){
		if(a[i]=='{'){
			v=0;
			if(a[i-4]=='f' && a[i-3]=='l'&&a[i-2]=='a'&&a[i-1]=='g'){
				v=i-3;
			}
		}else if(a[i]=='}'){
			if(v){
				f=true;
				t=i;
				break;
			}
		}
	}
	if(!f){
		printf("NOT FOUND");
	}else{
		for(int i=v-1;i<=t;i++)cout<<a[i];
	}
	return 0;
}
```

---

## 作者：easy42 (赞：1)

首先有字符串的 $find$ 函数，它可以快速找到字符串所在位置，需要提供字符串和字符串的下标（起始位置）。

这样子，就可以快速找到每一个 `flag{` 所在的位置。

注意到：
- 在 `flag{` 和 `}` 之间，不存在字符 `{` 和字符 `}`，可以存在任何其它可见字符。

于是想到，可以预处理出每个离下标最近的 `}`，是 $O(n)$ 的。

然后最后可以用前缀和就可以预处理出每个区间 $[l,r]$ 中出现了多少个 `{`，也是 $O(n)$ 的。

于是就做完了。赛时两发罚时。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a[200005],b[200005];
signed main(){
    cin>>s;
    for(int i=0;i<s.size();i++){
    	if(s[i]=='{') a[i]=a[i-1]+1;
    	else a[i]=a[i-1];
	}
	int st=-1;
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='}') b[i]=i,st=i;
		else b[i]=st;
	}
    int t=s.find("flag{",0);
    while(t!=-1){
        bool flag=true;
        if(b[t]!=-1){
            if(a[b[t]]-a[t+4]<=0){
                for(int i=t;i<=s.find("}",t);i++){
                    cout<<s[i];
                }
                exit(0);
            }
        }
        else{
            cout<<"NOT FOUND",exit(0);
        }
        //cout<<s.find("}",t)<<endl;
        t=s.find("flag{",t+1);
    }
    cout<<"NOT FOUND";
    return 0;
}
```

---

## 作者：H3PO4 (赞：1)

一个看起来是 $O(|s|^2)$ 的做法，但其实是对的，而且比官方题解的所有做法都简单。

思路：从左往右扫，每次遇到一个 `flag{` 就判断是否合法，即右边第一个 `}` 之前是否没有 `{`。

```cpp
#include<bits/stdc++.h>
using I=int;using str=std::string;
int main(){
  std::cin.tie(0)->sync_with_stdio(0);
  str s;std::cin>>s;
  for(I i=0;i+5<s.size();i++)
    if(s.substr(i,5)=="flag{")
      for(I j=i+5;j<s.size();j++){
        if(s[j]=='{')break;
        if(s[j]=='}')return std::cout<<s.substr(i,j-i+1)<<'\n',0;
      }
  return std::cout<<"NOT FOUND\n",0;
}
```

设一共有 $m$ 个 `{`，分别位于第 $a_1,a_2,\dots,a_m$ 个字符，那么循环的最内层最多只会运行 $a_2-a_1 + a_3 - a_2 + \dots + a_m - a_{m-1}=a_m-a_1<|s|$ 次，外层的比较显然也不会超过 $|s|$ 次，所以时间复杂度为 $O(|s|)$。

---

## 作者：hyc42 (赞：1)

## 前置
[题目传送门](https://www.luogu.com.cn/problem/P12035)

[赛事 AC 记录](https://www.luogu.com.cn/record/211984606)

## 题意
一个字符串 $s$，如果有一个子串 $t$ 以 `flag{` 开头，且以字符 `}` 结尾（中间不能有 `{` 或 `}`），就任意输出一个，若没有，就输出 `NOT FOUND`。

## 思路
一个很简单的模拟。

从头开始一个一个判断，若有一个子串 `flag{`，则判断：

- 中间是否有 `{`，有，则跳过（就是 `coutinue`）；
- 若没有，则看后面有没有 `}`，若有，则输出这个子串 $t$。

## 代码
```cpp
#include<bits/stdc++.h>
#define ri register int
#define F(i,a,b) for(ri i=a;i<=b;i++)
#define R(i,a,b) for(ri i=a;i>=b;i--)
using namespace std;
string s;
int main(){
	cin>>s;
	F(i,0,(int)s.size()-6){
		if(s[i]=='f'&&s[i+1]=='l'&&s[i+2]=='a'&&s[i+3]=='g'&&s[i+4]=='{'){
			string t="flag{";
			int j=i+5;
			bool ok=0;
			while(j<(int)s.size()&&s[j]!='}'){
				if(s[j]=='{'){
					ok=1;break;
				}
				t+=s[j],j++;
			}
			t+='}';
			if(ok)continue;
			cout<<t<<'\n',exit(0);
		}
	}
	cout<<"NOT FOUND\n";
	return 0;
}
```

---

## 作者：Grand_Dawn (赞：1)

来自出题人最开始的想法，基本只有语言基础的做法。这篇题解可能有非常多的证明，可以跳过。

合法的 flag，可以将条件转化为以下性质而和原条件等价：

- 该字符串以 `flag{` 开头，以 `}` 结尾。

-  `{` 和 `}` 各只出现一次。

条件一是比较显然的判断，以下只考虑条件二：

首先有一种 $\Theta(n^2)$ 的做法，就是先枚举子串的左端点 $l$，然后逐渐增加子串的右端点 $r$，动态记录 `{` 和 `}` 出现的次数。在判断条件一是否合法后，可以根据`{`和`}` 出现的次数判断该子串是否合法。

这样的做法可以查询到所有的子串，不会有遗漏。考虑继续优化该算法：

显然增加子串的右端点 $r$ 过程中，字符串只会增加字符，即 `{`和`}` 出现的次数是随着右端点增加的过程是单调不减的。

因此，当 `{` 的次数大于 $1$ 后，右端点 $r$ 继续增加不会出现合法的 flag，可以直接退出循环。

考虑另一个优化：将条件一的两个部分拆开，若字符串不以 `flag{` 开头则也不再枚举 右端点 $r$。正确性是显然的。 

同时考虑两种优化之后，时间复杂度即为 $\Theta(n)$ ，以下给出证明：

右端点 $r$ 能够枚举的必要条件是字符串 $s_{l+4}$ 为 `{`，而 $r$ 会在下一次出现 `{` 停止循环。对于任意数 $x$，当 $x=r$ 时必然有 $l$ 为 $x$ 之前一个 `{` 的位置 $-4$，是唯一的。

故处于循环中的数对 $(l,r)$ 是 $\Theta(n)$，证明了时间复杂度。

```cpp
#include<bits/stdc++.h>
#define N 100009
using namespace std;
int n;
char s[N];
int main(){
	freopen("15.in","r",stdin);
	freopen("15.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	assert(n<=100000);
	for(int i=1;i<=n;i++){
		if(s[i]=='f'&&s[i+1]=='l'&&s[i+2]=='a'&&s[i+3]=='g'&&s[i+4]=='{'){
			for(int j=i+5;j<=n;j++){
				if(s[j]=='{')break;
				if(s[j]=='}'){
					for(int k=i;k<=j;k++)putchar(s[k]);
					return 0;
				}
			}
		} 
	}
	cout<<"NOT FOUND";
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

给定一个字符串 $s$，要求找出其中符合特定格式的合法子串。
- 合法的子串必须以 `flag{` 开头，以 `}` 结尾。
- 且 $s$ 中间不能包含 `{` 或 `}`。如果存在多个合法子串，输出任意一个即可。

若不合法输出 `NOT FOUND`。

---

水题，模拟题意即可。

先逐个字符检查是否存在以当前字符开头的 `flag{`，
找到 `flag{` 后，继续检查后续字符，直到遇到 `}`。若中间出现 `{` 或 `}`，则当前子串非法。

找到第一个合法的子串后立即输出并结束程序；若遍历完仍未找到，输出 `NOT FOUND`。

## Code
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.length();
    for (int i = 0; i < n; ++i) {
        // 检查是否以 "flag{" 开头
        if (i + 4 <= n && s.substr(i, 5) == "flag{") {
            int j = i + 5; // 跳过 "flag{" 的5个字符
            bool valid = true;
            // 遍历后续字符，直到遇到 '}' 或字符串结束
            while (j < n && s[j] != '}') {
                if (s[j] == '{' || s[j] == '}') {
                    valid = false;
                    break;
                }
                ++j;
            }
            // 找到合法闭合且中间无非法字符
            if (valid && j < n) {
                cout << s.substr(i, j - i + 1);
                return 0;
            }
        }
    }

    cout << "NOT FOUND";
    return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：[P12035 [USTCPC 2025] Hackergame](https://www.luogu.com.cn/problem/P12035)

更佳的阅读体验：[洛谷 P12035 题解](https://blog.ryanli.top/index.php/archives/271/)

---

**简要题意**：给定字符串 $s$，找出 $s$ 中第一个以 $\texttt{flag\{}$ 开头、以 $\texttt{\}}$ 结尾且中间不含 $\texttt{\{}$ 和 $\texttt{\}}$ 的连续子串，存在则输出该子串，否则输出 $\texttt{NOT FOUND}$。

我们可以使用字符串函数 `s.find()`，从头开始一直寻找以 $\texttt{flag\{}$ 开头的子串。如果发现一个，那么就寻找后面**最近的** $\texttt{\}}$。如果可以找到，那么就判断从 $\texttt{flag\{}$ 到 $\texttt{\}}$ 中间有没有 $\texttt{\{}$，有的话说明这个子串是不合法的，继续向后寻找下一个 $\texttt{flag\{}$，直到找到一个合法的为止。

如果已经找到合法的子串，就直接输出，并结束程序。如果找不到，在程序最后输出 $\texttt{NOT FOUND}$ 即可。

```cpp
#include <iostream>
using namespace std;

string s;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> s;
    auto pos = s.find("flag{");
    while (pos != s.npos) {
        auto end = s.find('}', pos);
        if (end == s.npos) break;
        bool fail = false;
        for (int i = pos + 5; i < end && i < s.size(); ++i) if (s[i] == '{') {
            fail = true;
            break;
        } if (!fail) {
            cout << s.substr(pos, end - pos + 1) << '\n';
        	return 0;
        } pos = s.find("flag{", pos + 1);
    } cout << "NOT FOUND\n";
    return 0;
}
```

---

## 作者：canwen (赞：0)

去找每个子串 `flag{`，然后去找 `}`，若中间出现 `{` 则回溯到之前进行扫描即可，否则直接输出答案。

[通过记录](https://www.luogu.com.cn/record/212084105)。

遍历字符串不是入门题嘛。

---

## 作者：XiaoHongChong (赞：0)

我们可以每把字符串分一下，`{` 为一段，`}`也为一段，`{` 和 `}` 中间和旁边的字符各为一段。$ss_i$ 表示第 $i$ 段。  
如果一个 flag 合格，那么可以用 $ss_i + ss_{i + 1} + ss_{i + 2} + ss_{i + 3}$ 来表示（$ss_i$ 为 `flag`，$ss_{i + 1}$ 为 `{`， $ss_{i + 2}$ 为中间的部分，$ss_{i + 3}$ 为 `}`）。  
但是还有一种特殊情况，就是 flag 中间没有字符，即 $ss_i + ss_{i + 1} + ss_{i + 2}$ 为 `flag{}`。
### 代码

```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int len;
string s, ans = "NOT FOUND", ss[N];
//判断i开头的flag合格吗
bool flag(int i)
{
	if (ss[i] != "flag") return false;
	if (ss[i + 1] != "{") return false;
	if (ss[i + 3] != "}") return false;
	if (ss[i + 2] == "{") return false;
	if (ss[i + 2] == "}") return false;
	return true;
}
int main()
{
	cin >> s;
  //分段
	string S = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '{' || s[i] == '}')
		{
			if (S == "");
			else ss[++len] = S;
			S = "";
			ss[++len] = string(1, s[i]);
		}
		else S += s[i];
	}
	if (S != "") ss[++len] = S;
  //循环判断flag合不合格
	for (int i = 1; i <= len - 3; i++)
		if (flag(i))
		{
			ans = ss[i] + ss[i + 1] + ss[i + 2] + ss[i + 3];
			break;
		}
		else if (ss[i] + ss[i + 1] + ss[i + 2] == "flag{}")
		{
			ans = "flag{}";
			break;
		}
	if (len >= 3 && ss[len - 2] + ss[len - 1] + ss[len] == "flag{}")
		ans = "flag{}";
	cout << ans << endl;
	return 0;
}
```

---

