# Slavic's Exam

## 题目描述

Slavic has a very tough exam and needs your help in order to pass it. Here is the question he is struggling with:

There exists a string $ s $ , which consists of lowercase English letters and possibly zero or more "?".

Slavic is asked to change each "?" to a lowercase English letter such that string $ t $ becomes a subsequence (not necessarily continuous) of the string $ s $ .

Output any such string, or say that it is impossible in case no string that respects the conditions exists.

## 样例 #1

### 输入

```
5
?????
xbx
ab??e
abcde
ayy?x
a
ab??e
dac
paiu
mom```

### 输出

```
YES
xabax
YES
abcde
YES
ayyyx
NO
NO```

# 题解

## 作者：block_in_mc (赞：6)

## 题目大意

给定一个只包含小写字母和字符 `?` 的字符串 $s$ 以及一个只包含小写字母的字符串 $t$，询问能否通过将 $s$ 中的 `?` 改为任意小写字母使得 $t$ 是 $s$ 的子串（可以不连续），若可以，输出任意一个合法的更改过的 $s$。

## 解题思路

考虑贪心。利用双指针 $i,j$ 确定目前匹配到字符串 $s$ 和 $t$ 的位置（即 $s$ 的前 $i-1$ 个字符能够使得 $t$ 的前 $j=1$ 个字符成为其字串），显然能匹配就匹配更优，具体地：若 $s_i$ 是 `?` 或者 $s_i=t_j$，则 $i,j$ 加上 $1$。最后，若 $j=|t|$（$|t|$ 代表字符串 $t$ 的长度），则答案为 `YES`，否则答案为 `NO`。

匹配时同时更改 $s$，若是通过 $s_i$ 为 `?` 匹配的，则将 $s_i$ 改为 $t_j$。最后再扫一遍 $s$，若 $s$ 中含有未用到的 `?`，则将其改为任意字符。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s, t;
int main() {
    cin >> n;
    while (n--) {
        cin >> s >> t;
        int i = 0, j = 0;
        while(i < s.length() && j < t.length()) {
            if (s[i] == '?') s[i]=t[j], i++, j++;
            else if (s[i] == t[j]) i++,j++;
            else i++;
        }
        for(int k = 0; k < s.length(); k++)
            if (s[k] == '?')
                s[k] = 'a';
        if(j==t.length()) cout<<"YES\n"<<s<<endl;
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：2)

# CF1999D Slavic's Exam 题解

[Luogu Link](https://www.luogu.com.cn/problem/CF1999D)|[CF Link](https://codeforces.com/contest/1999/problem/D)|[My AC submission](https://codeforces.com/contest/1999/submission/274843223)。

其实这个题也不难，但我卡了好几回。

### 解析

考虑到本题要求的是**子序列**而不是子串，我们维护一个指针，指 $t$ 下一位要匹配的字符。在 $s$ 中遍历，若 $s$ 的这一位刚好是 $t$ 指针指向的字符，则指针右移（即这一位匹配过了），若是问好也可以直接替换。可以证明，这样的替换一定不劣。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T;
string s,t;
int cnt;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>s>>t;
		cnt=0;
		for(int i=0;i<s.size();i++){
			if(s[i]==t[cnt]||s[i]=='?'){
				cnt++;
			}
		}
		if(cnt>=t.size()){ //t 遍历完了
			cout<<"Yes\n";
			cnt=0; //注意这里清零
			for(int i=0;i<s.size();i++){
				if(s[i]=='?'){
					if(cnt>=t.size()){ //如果 t 的字符全都匹配完了全都输出 a 补位，当然你输出 x 也是没问题的
						cout<<"a";
					}
					else{
						cout<<t[cnt++]; //指针右移
					}
				}
				else{
					cout<<s[i];
					if(s[i]==t[cnt]){ //不是问好也要判一下
						cnt++;
					}
				}
			}
			cout<<"\n";
		}
		else{
			cout<<"No\n";
		}
	}
return 0;
}
```

---

## 作者：Heldivis (赞：2)

## CF1999D Slavic's Exam

贪心。

将 $t$ 和 $s$ 双指针比较，若 $s$ 串当前位是 `?`，那么将这一位直接赋值为 $t$ 的当前位一定不劣。因为如果之后再匹配，那么 $s$ 中间的一段距离，可能可以继续和 $t$ 的下一位比较，同时 `?` 也没有价值。

之后，判断 $t$ 是否全部匹配，如果匹配成功，将 $s$ 中剩余的 `?` 换成任意小写字母输出即可。

代码：

``` cpp
void Main() {
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1), m = strlen(t + 1);
  for (int i = 1, j = 1; i <= n; ++i) {
    if (s[i] == t[j] || s[i] == '?') s[i] = t[j++];
    if (j > m) {
      puts("YES");
      for (int i = 1; i <= n; ++i) putchar(s[i] == '?' ? 'x' : s[i]);
      putchar('\n');
      return;
    }
  }
  puts("NO");
}
```

---

## 作者：WsW_ (赞：2)

贪心。

---
## 思路
逐位匹配，能匹配就匹配。  

从前往后循环遍历字符串 $s$，并在字符串 $t$ 上维护一个指针 $p$。$p$ 表示 $t$ 上应该匹配哪一位了。  

如果 $s_i=t_p$，那么就让这两位匹配上，一定最优。如果不匹配上，那么和 $t_p$ 匹配的 $i$ 一定会变大，可能导致 $t$ 之后的某一位错过了它应该匹配的 $s_i$。  
如果 $s_i=\mathtt{?}$，那么就直接让 $s_i,t_p$ 匹配上，一定最优。和上一种情况是一样的。  

---
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void work(){
	string s,t; cin>>s>>t;
	int p=0;
	bool f=0;
	for(int i=0;i<s.length();i++){
		if(s[i]==t[p]||s[i]=='?'){
			s[i]=t[p];
			p++;
		}
		if(t.length()==p){
			f=1;
			break;
		}
	}
	if(f){
		cout<<"YES\n";
		for(int i=0;i<s.length();i++){
			if(s[i]=='?')cout<<'a';
			else cout<<s[i];
		}
		cout<<"\n";
	}
	else cout<<"NO\n";
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：qifan_maker (赞：2)

考虑贪心，由于是子序列，所以先取一定不会比后取更劣。

用两个指针 $i$、$j$ 分别指向 $s$ 和 $t$，若 $s_i$ 能取 $t_j$（即 $s_i=\texttt?$ 或 $s_i=t_j$），则 $j$ 右移，若 $j>m$，则答案为 `YES`，否则为 `NO`。

注意将多余的 `?` 填充为别的小写字母。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353;
const int MAXN = 200100,hsb=1045141919;
const ll Inf = 1000000000000000000ll;
#define PI pair<ll,ll>
#define PII pair<ll,pair<ll,ll>>
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int Tcs=1;
    cin >> Tcs;
    while (Tcs--){
        string s,t;
        cin >> s >> t;
        int n=s.size(),m=t.size();
        s = ' '+s,t = ' '+t;
        int j=1;
        for (int i=1;i<=n&&j<=m;i++){
            if (s[i] == t[j] or s[i] == '?') s[i]=t[j++];
        }
        for (int i=1;i<=n;i++) if (s[i] == '?') s[i] = 'a';
        if (j > m) cout << "YES\n" << s.substr(1,n) << "\n";
        else cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：InfiniteRobin (赞：1)

### 简要题意 

---
给你两个仅包含小写字母和问号的字符串 $s,t$。问是否可以通过将 $s$ 中的 ```?``` 替换为任意小写字母的方式，使 $t$ 成为 $s$ 的子串。

---
### 分析
---
直接模拟即可，搞一个指针 $j$ 指向 $t$，然后遍历 $s$ 的每一位，若是 $s_{i}=t_{j}$ 或 $s_{i}$ 为问号，则 $j \leftarrow j+1$。   

最后判断 $j$ 是否等于 $t$ 的长度即可。

别忘了将 $s$ 中的问号替换掉。

---
### Code

---
代码很好写。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int t;
    string a,b;
    cin>>t;
    while(t--){
        cin>>a>>b; //分别对应 s 和 t
        int pos=0; //指向 b 的指针
        for(int i=0;i<a.length();i++){  //遍历 s
            if((a[i]==b[pos]||a[i]=='?')&&pos<b.length()){如果出现相同的或是遇到问号（前提是 pos 没超界）
                a[i]=b[pos]; //别忘了替换！
                pos++; 
            }
            if(a[i]=='?'){ //如果 b 已经是 s 子串，随便替换一个即可
                a[i]='a';
            }
        }
        if(pos==b.length()){ 
            cout<<"YEs"<<endl<<a<<endl;
        }
        else{
            cout<<"nO"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

子序列的常用方法挨个匹配就行了。两个指针，一个指 $s$，一个指 $t$，匹配上了就移动 $t$ 的指针。注意这里出现问号也算匹配成功。记得覆盖。匹配完剩余的的问号可以随便换。

代码如下：

```cpp
#include<iostream>
using namespace std;
int t,ptr; string s1,s2;
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>s1>>s2; ptr=0;
		for(int i=0;i!=s1.size()&&ptr!=s2.size();++i)
			if(s1[i]==s2[ptr]||s1[i]=='?') 
				s1[i]=s2[ptr],ptr++;
		if(ptr==s2.size()){
			for(int i=0;i!=s1.size();++i)
				if(s1[i]=='?') s1[i]='a';
			cout<<"YES\n"<<s1<<endl;
		}
		else cout<<"NO\n";
	}
	return 0;
}
//私は猫です
```

---

## 作者：GavinCQTD (赞：1)

# 题解：CF1999D Slavic's Exam

## 思路

根据题意，不难发现这道题的本质为字符串子序列，只是 `?` 可以被任意匹配。因此我们可以在普通的子序列匹配中加一个判断即可。但是，题目要求同时输出补全的 S。所以，我们需要格外开一个数组记录 S 中缺失的字母。

## 代码

```cpp
#include <iostream>
using namespace std;
inline void pass(){return;}
int tt;
char bj[200005];
string s,t;

bool isSubsequence(string x,string y){
    int i=0,j=0;
    while(i<x.length()&&j<y.length()){
        if(x[i]==y[j]) j++;
        else if(x[i]=='?'){
            bj[i] = y[j];
            j++;
        }
        i++;
    }
    return j==y.length();
}


int main(){
    cin >> tt;
    for(int ran=0;ran<tt;ran++){
        for(int i=0;i<200005;i++) bj[i]='a';
        cin >> s >> t;
        if(isSubsequence(s,t)){
            cout << "YES" << endl;
            for(int i=0;i<s.length();i++){
                if(s[i]!='?') cout<<s[i];
                else cout<<bj[i];
            }
            cout << endl;
        }
        else cout<<"NO"<<endl;
    }
    return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

拿到题目一开始以为是别的算法，然后仔细看题目发现是子**序列**，那么就不需要考虑那么多了。

简单贪心：如果在这里能选就选，一定不会有另一个选择更优。证明显然。

至于如何填充 $s$ 字符串的问题，选上的填上相应的字母，剩下的乱填即可（具体见代码）。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		string t;
		cin>>t;
		int len=s.length();
		int cnt=0;
		for(int i=0;i<len;i++){
			if(cnt==t.length()){
				if(s[i]=='?')s[i]='a';
				continue;
			}
			if(t[cnt]==s[i]||s[i]=='?'){
				s[i]=t[cnt];
				cnt++;
			}
		}
		if(cnt==t.length()){
			cout<<"YES\n"<<s<<endl;
		}
		else{
			cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：Archy_ (赞：0)

## 题目翻译
有字符串 $s$，$t$。$s$ 由小写字母和 $\texttt{?}$ 组成。问号可修改为任意小写字母。

问，操作或不操作后的 $s$，是否有 $t$ 为 $s$ 的子序列，不一定连续。如果有输出 `YES` 并输出 $s$，反之输出 `NO`。
## 题目思路
循环进行比对，用 $t_{now}$ 表示目前比对的字符，$now$ 初始为 $0$。

1. 若有 $t_{now} = s_i$，$now$ 加一，进行下一个比对。

2. 若有 $s_i = \texttt{?}$，$now$ 加一，并将 $s_i$ 赋值为当前比对字符。

如此操作，若有 $now \ge |t|$，即为全部比对完毕，但未比对的后面可能还有问号未赋值，在循环完后面就行了。
## Code
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int main() {
	cin.tie(0) -> ios::sync_with_stdio(0);
	int q; cin >> q;
	while(q--) {
		string s, t;
		cin >> s >> t;
		int now = 0;
		for(int i = 0; i < s.size(); i++) {
			if(s[i] == t[now] || s[i] == '?') {
				s[i] = t[now];
				now ++; 
			}
			if(now >= t.size()) {
				for(int j = now; j < s.size(); j++)
					if(s[j] == '?') s[j] = 'a';
				break;
			}
		}
		if(now >= t.size()) cout <<"Yes\n"<< s << "\n";
		else cout <<"No\n";
	}
	return 0;
} 
```

---

## 作者：donnieguo (赞：0)

## 题意简述

给定两个字符串 $s$ 和 $t$，其中字符串 $s$ 有若干个 `?`，这些 `?` 可以变成任何小写字母。现在要求你找到一种变换 `?` 的方法，使得 $t$ 是 $s$ 的子序列。

若可以使得 $t$ 是 $s$ 的子序列，那么第一行输出 `YES`，第二行输出你构造的 $s$。

如果有多种满足条件的方案，输入其中一种即可。

若不能使得 $t$ 是 $s$ 的子序列，那么输出 `NO`。

$1 \leq |t| \leq |s| \leq 2 \times 10^5$。

## 思路

维护两个指针 $tpos$ 和 $spos$，$tpos$ 从 $0\sim |t|-1$，然后 $\forall t_{tpos}$ 从 $spos$ 往后找，如果找到 `?` 或者与 $t_{tpos}$ 相同的字符就继续。如果出现 $spos = |s|$ 的情况，说明当前的 $spos$ 之后没有 `?` 或者与 $t_{tpos}$ 相同的字符，那么就 `break` 掉，输出 `NO`，否则输出 `YES`。

### 注意

- 本蒟蒻最开始的思路是优先找到相同的字符，没有再考虑 `?`。但是被自己 Hack 了。

  Hack 数据：
  ```
  ab??b
  bbb
  ```
  ~~估计没有人跟我错一样的吧？~~

- 有可能 $s$ 中 `?` 的数量比 $|t|$ 要多，或者还剩余有 `?` 没有被填上，那么这里将其填上任意一个字符即可。

## AC code

```cpp
#include <iostream>
using namespace std;

int T;
string s1, s2;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--)
	{
		cin >> s1 >> s2;
		int len1 = s1.length(), len2 = s2.length();
		int pos1 = 0, pos2 = 0;
		bool flag = 1;
		while (pos2 < len2)
		{			
			while (s1[pos1] != s2[pos2] && s1[pos1] != '?' && pos1 < len1) pos1++;
			if (pos1 == len1) {flag = 0; break;}
			if (s1[pos1] == '?') s1[pos1] = s2[pos2];
//			cout << pos1 << ' ' << pos2 << '\n';
			pos1++, pos2++;
		}
		if (flag)
		{
			cout << "YES" << '\n';
			for (int i = 0; i < len1; i++) if (s1[i] == '?') s1[i] = 'e';
			cout << s1 << '\n';
		}
		else cout << "NO" << '\n';
	}
	return 0;
}
```

---

## 作者：xuduang (赞：0)

### 题意

给出两个字符串 $s,t$，其中 $s$ 中的 `?` 可以变成任意字符，问存不存在一种方案使得 $t$ 可以成为 $s$ 中的一个子序列。

### 分析

先要明确一点，子序列不一定要连续。

既然 $t$ 最后会变成 $s$ 的子序列，那 $t_i$ 一定顺序的一一对应 $s$ 中的顺序字符。

因为只有 `?` 有变字符的功能，所以其他字符匹配不上下一个 $t$ 中的字符就没有用了，这就需要 `?` 变成下一个字符。

总结来说，固定字符能匹配的上就匹配，匹配不上就用 `?`，最后多出来的乱填就可以了。

### 代码

```cpp
/*
write from : xuduang
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
char s[N], t[N];
void solve()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    int j = 1;//t中还未匹配的字符下标
    bool fl = 0;
    int tlen = strlen(t + 1), slen = strlen(s + 1);
    for(int i = 1; i <= slen; i++)
    {
        if(s[i] == '?') s[i] = t[j];//用 ? 来填
        if(s[i] == t[j]) j++;//直接可以匹配或者用了 ?
        if(j == tlen + 1) fl = 1, j--;//匹配完之后乱填
    }
    if(!fl) return printf("NO\n"), void();
    printf("YES\n");
    printf("%s\n", s + 1);
}
signed main()
{
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# CF1999D 题解
### 题目大意
有 $t$ 组数据，每组给出两个字符串 $s$ 和 $t$。问是否可以通过将 $s$ 中的问号替换成任意小写字母使得 $t$ 变成 $s$ 的子序列。若可以，输出 `YES` 和替换后的 $s$，否则输出 `NO`。
### 大致思路
遍历 $s$，并创建一个 $t$ 的下标 $index$，初始为 $0$。若遍历到问号，则替换为 $t_{index}$ 并将 $index$ 加一，否则判断遍历到的字符与 $t_{index}$ 是否相等，若相等，也将 $index$ 加一。最后判断 $index$ 是否到达 $t$ 的长度即可。记得要把 $s$ 中还未替换的问号替换掉。
### 核心代码
```cpp
void solve() {
  // 输入
  std::string s, t;
  std::cin >> s >> t;
  int n = s.size(), m = t.size(), cnt = 0;
  // 遍历
  for(int i = 0; i < n && cnt < m; ++i) {
    if(s[i] == '?') {
      s[i] = t[cnt++];
    }
    else {
      if(s[i] == t[cnt]) {
        ++cnt;
      }
    }
  }
  // 替换还未替换的问号
  for(int i = 0; i < n; ++i) {
    if(s[i] == '?') s[i] = 'a';
  }
  // 判断并输出
  if(cnt == m) {
    std::cout << "YES\n" << s << '\n';
  }
  else {
    std::cout << "NO\n";
  }
}

```
### [RESULT](https://codeforces.com/contest/1999/submission/274797156)

---

## 作者：__O__o__ (赞：0)

## 前言
多测不清空，爆零两行泪。
## 思路简述
开一个存每个字母所在下标的队列，**顺序存放**。然后再开一个用来存前一个字母所在地址的变量 $addr$，把队列里所有小于等于 $addr$ 的变量清除掉，在更新 $addr$ 的值即可。

详细过程请看代码。
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
string s1,s2,neww;
queue<int> add[27];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		cin>>s1>>s2;
		for(int i=0;i<s1.size();i++)
		{
			if(s1[i]=='?') add[26].push(i);
			else add[s1[i]-'a'].push(i); 
		}
		int addr=-1;
		int fl=1;
		for(int i=0;i<s2.size();i++)
		{
			while(add[s2[i]-'a'].front()<=addr&&add[s2[i]-'a'].size()>0)
			{
				add[s2[i]-'a'].pop();
			}
			while(add[26].front()<=addr&&add[26].size()>0)
			{
				add[26].pop();
			}
			if(add[s2[i]-'a'].size()==0&&add[26].size()==0)
			{
				fl=0;break;
			}
			else
			{
				if(add[s2[i]-'a'].size()>0&&add[26].size()>0)
				{
					addr=min(add[26].front(),add[s2[i]-'a'].front());
					s1[addr]=s2[i];
				}
				else
				{
					if(add[s2[i]-'a'].size()==0) addr=add[26].front(),s1[addr]=s2[i];
					else addr=add[s2[i]-'a'].front(),s1[addr]=s2[i];
				}
			}
		}
		if(fl) 
		{
			printf("Yes\n");
			for(int i=0;i<s1.size();i++) if(s1[i]=='?') s1[i]='a';
			cout<<s1<<'\n';
		}
		else printf("No\n");
		
	    s1.clear();
		s2.clear();
		for(int i=0;i<27;i++) 
		{
			while(!add[i].empty()) add[i].pop();
		}
	}
	return 0;
}
```

---

## 作者：ToastBread (赞：0)

## 题目思路

和判断一个字符串是否为另一个串的子序列的方法差不多，都是贪心。

考虑使用一个辅助指针 $r$ 来贪心，初始时指向 $t$ 的开头。

从前往后遍历字符串 $s$。
- 如果 $s$ 的当前位是 $t$ 的第 $r$ 位，则指针 $r$ 向后移一位。
- 如果 $s$ 的当前位是 `?`，则将这一位替换成 $t$ 的第 $r$ 位，指针 $r$ 向后移一位。

如果遍历完 $s$ 后 $t$ 也被遍历完了，那么就有合法解，否则就没有。

具体实现坑还是比较多的，可以参考我的代码作为辅助。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string a,b;
int main()
{
	cin>>t;
	while(t--)//多组数据 
	{
		cin>>a>>b;//输入 
		int p=0,la=a.size(),lb=b.size();//防止重复调用大小，节约时间 
		for(int i = 0; i < la; i++)
		{
			if(p<lb&&a[i]==b[p])//如果一样 
			{
				p++;//还没遍历完，指针向后
				//遍历完了就不需要向后了 
			}
			if(a[i]=='?')
			{
				if(p<lb) a[i]=b[p];//还没遍历完，更改 
				else a[i]='a';//遍历完，想改啥就改啥 
				if(p<lb) p++;// 还没遍历完，指针向后
			}
		}
		if(p==lb) cout<<"YES"<<endl<<a<<endl;//有解 
		else cout<<"NO"<<endl;//无解 
	}
	return 0; 
 }
```

---

## 作者：PineappleSummer (赞：0)

[CF1999D Slavic's Exam](https://www.luogu.com.cn/problem/CF1999D)

贪心。由于是让匹配一个子序列，所以能匹配就匹配一定不劣。

维护一个双指针 $i,j$ 表示字符串 $s$ 的前 $i$ 位能匹配好字符串 $t$ 的前 $j$ 位。

如果 $s_{i+1}=t_{j+1}$ 或者 $s_{i+1}$ 为 `?`，说明 $s$ 的第 ${i+1}$ 位可以与 $t$ 的第 ${j+1}$ 位匹配上，让 $j$ 加 $1$。

如果 $j$ 变为了 $m$，说明可以匹配 $t$，输出 `YES`，否则输出 `NO`。

单组数据时间复杂度 $\mathcal O(|s|)$，$|s|$ 为字符串 $s$ 的长度。

```cpp
void solve () {
	cin >> s >> t;
	int n = s.size (), m = t.size ();
	s = " " + s, t = " " + t;
	for (int i = 0, j = 0; i <= n && j <= m; i++) {
		if (s[i + 1] == t[j + 1] || s[i + 1] == '?') {
			if (s[i + 1] == '?') s[i + 1] = t[j + 1];
			j++;
		}
		if (j == m) { // 匹配完成
			cout << "YES\n";
			for (int i = 1; i <= n; i++) cout << (s[i] == '?' ? 'a' : s[i]);
			return cout << '\n', void (0);
		}
	}
	cout << "NO\n"; // 无法匹配
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
读入字符串 $s$ 和 $t$，设 $j$ 表示当前枚举到 $t$ 的第几个字符。我们将答案字符串 $ans$ 初始化为 $s$。设 $i$ 从 $0$ 到 $|s| - 1$。如果 $s_i=t_j$ 或者 $s_i$ 是问号，并且 $j < |t|$，那么我们就可以将 $ans_i$ 变为 $t_j$，同时 $j$ 也要 $+1$，否则如果 $ans_i$ 是问号，那么将 $ans_i$ 设为任意一个小写字母即可。

循环结束，如果 $j = |t|$，说明已经做到了 $t$ 的最后一个字符，那么输出 `YES`，并且输出 $ans$。否则输出 `No`。
### 代码
```cpp
#include<iostream>
void solve(int T){
	if(T==0)return;
	std::string s,t;
	int j=0;
	std::cin>>s>>t;
	std::string ans=s;
	for(int i=0;i<s.size();i++){
		if(j<t.size()&&(s[i]==t[j]||s[i]=='?'))ans[i]=t[j++];
		else if(ans[i]=='?')ans[i]='q';
	}
	if(j==t.size()){
		puts("YES");
		puts(ans.c_str());
	}else{
		puts("NO");
	}
	solve(T-1);
}
signed main(){
	int T;
	std::cin>>T;
	solve(T);
}

```

---

## 作者：So_noSlack (赞：0)

## 题目简述

有 $T$ 组数据，每组数据给出两个字符串 $s, t$。

你需要判断是否存在一种方式使得将 $s$ 中的 `?` 替换成任意小写字母，使得 $t$ 是修改后 $s$ 的子序列$^1$。

- 若存在一种方式则输出 `YES`，并输出一种满足情况的修改后的 $s$。
- 否则输出 `NO`。

$^1$：子序列不一定连续。

## 思路

因为子序列不一定连续，所以考虑直接贪心的模拟，遇到 `?` 就换成我们当前需要的字母。

可以证明这种贪心策略是最优的，因为我们让当前的字母提前匹配总是比后面匹配优的。

因此考虑用两个指针 $l, r$，分别表示当前 $s, t$ 匹配的哪一位，那么操作过程如下：

- 若 $s_l$ 为 `?` 则 $s_l := t_r$。
- 若操作后 $s_l = t_r$，右指针 $r$ 右移。
- 左指针 $l$ 右移。

操作完之后输出 $s$ 就好。

需要注意的是 $r$ 不要大于 $|t|$，大于的话直接让 $s$ 中剩下的 `?` 变成 `a` 即可。

代码如下：


```cpp
#include<iostream>
using namespace std;
#define MAXN 200005

long long read() {
	long long x = 0, f = 1; char ch = getchar();
	while(ch < 48 || ch > 57) { if(ch == 45) f = -1; ch = getchar(); }
	while(ch >= 48 && ch <= 57) { x = (x << 3) + (x << 1) + (ch - 48); ch = getchar(); }
	return x * f;
}

long long T, p[MAXN];
string s, t;

int main() {
	T = read();
	while(T --) {
		cin >> s >> t;
		long long ls = s.size(), lt = t.size(), tp = 0;
		bool f = false;
		for(int i = 0; i < ls; i ++) 
			if(tp == lt) break;
			else if(s[i] == '?') s[i] = t[tp ++];
			else tp += (s[i] == t[tp]);
		if(tp != lt) cout << "NO\n";
		else {
			cout << "YES\n";
			for(int i = 0; i < ls; i ++) 
				if(s[i] == '?') cout << "a";
				else cout << s[i];
			cout << "\n";
		}
	}
	return 0;
}
```

[$\text{Submission}$](https://codeforces.com/contest/1999/submission/274828345)

---

## 作者：GeXiaoWei (赞：0)

# CF1999D Slavic's Exam
## 解析
因为题目让我们让字符串 $t$ 变为字符串 $s$ 的子串，所以我们只需要凑出子串 $t$ 即可。先遍历字符串 $s$，如果与字符串 $d$ 的第一位相同，或者那一位是问号，那么就继续判断第二位，直到字符串 $d$ 每一位都能找到。

注意如果在字符串 $s$ 找字符串 $d$ 的 $i$ 位找到了问号，还要把字符串 $s$ 里的那位问号改为字符串 $d$ 的第 $i$ 位。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,z,l;
string s,d;
int main(){
	scanf("%d",&t);
	while(t--){
		cin>>s>>d;z=l=0;
		for(int i=0;i<s.size();i++){
			if((s[i]==d[l]||s[i]=='?')&&l<d.size()) s[i]=d[l++];
			if(l>=d.size()&&s[i]=='?') s[i]='a';
			if(l==d.size()) z=1;
		}
		if(z) cout<<"YES\n"<<s<<"\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999D](https://www.luogu.com.cn/problem/CF1999D)

# 解题思路

因为我们最终所需要的是子序列，因此我们直接用一个指针来指向需要匹配的下一个字符，如果有了，那么将指针向右移动，在指针移动的同时可以顺便求出答案。

时间复杂度线性。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
string s1,s2;
ll n,m,L;
void solve()
{
	L=1;
	_clear();
	cin>>s1>>s2;
	n=s1.size(),m=s2.size();
	s1=' '+s1,s2=' '+s2;
	forl(i,1,n)
	{
		if(s1[i]=='?')
		{
			if(L!=m+1)
				s1[i]=s2[L++];
			else
				s1[i]='a';
		}
		else
		{
			if(L<=m && s1[i]==s2[L])
				L++;
		}
	}
	if(L==m+1)
	{
		cfy;
		for(auto i:s1)
			if(i!=' ')
				cout<<i;
		cout<<endl;
	}
	else
		cfn;
}
int main()
{
	IOS;
	_t_=1;
	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

