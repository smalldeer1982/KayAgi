# [APC001] B - Checker

## 题目背景

小 K 正在出公开赛。他有一个 idea，但他担心重题，因此，他需要确认这题是不是重题。不过他还有很多事情要做，因此他把这个任务交给了你。

## 题目描述

题库里共有 $ n $ 道题目，每道题目的名称都是一个**长度不足 $ 10 $** 的字符串。设题目名称长度为 $k$，我们定义两道题为**重题**当且仅当两道题题目名称有 $\ge \left\lceil\frac{k}{2} \right\rceil$ 的相同位置的字符相同。

现在小 K 把这道题交给了你，希望你帮他查重（即，将自己的题目与其他的题目进行一一比对，判断是否为重题）。

## 说明/提示

**【样例解释 #1】**

题目名为 `chachong`，与第一题中的 $ 0 $ 个字符相同，与第二题中的 $ 3 $ 个字符相同，与第三题中的 $0$ 个字符相同，而每题都有 $ 8 $ 个字符，没有与小 K 出的题目有大于等于 $ 8 \times 50\% = 4 $ 个字符相同的题目。

**【样例解释 #2】**

请注意有可能在题库中也包含重题。

**【数据规模】**

对于 $100\%$ 的数据，保证 $ 1 \le n \le 10^4 ,1\le k\le10$，每个字符串长度相同，且不含不可见字符。

## 样例 #1

### 输入

```
3
chachong
abcabcat
chocolat
noiprp++```

### 输出

```
0
Good job!```

## 样例 #2

### 输入

```
10
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b
apc001_b```

### 输出

```
10
Make persistent efforts.```

## 样例 #3

### 输入

```
25
a
b
c
d
e
f
g
h
i
j
k
l
m
n
o
p
q
r
s
t
u
v
w
x
y
z```

### 输出

```
0
Good job!```

# 题解

## 作者：canwen (赞：4)

## 分析
考虑样例三，每个字符串长度为 $1$，我们如果选择统计有多少个位置相同，按照题意将会是 $\left\lceil\frac{1}{2} \right\rceil = 0$ 个相同位置的字符相同即为重题，样例三会错。

用 $|s|$ 表示字符串 $s$ 的长度。

那我们不妨设置变量 $cnt$ 记录相同位置相同的字符数总和，即每次发现相同自增 $2$。当统计完之后如果 $(|s|\cdot2\div 2) \le cnt$，就说明重题了。

为什么是对的？先把 $|s|$ 乘上 $2$ 能避免掉整除带来的尴尬，所以统计相同位置相同的字符数总和是对的，可以想想是为什么。

读者理解正确思路后可以自己实现，毕竟是红题，就不放代码了。

---

## 作者：NTT__int128 (赞：3)

# P11137 [APC001] B - Checker题解
对于每个字符串，依次枚举每个字符，如果字符相同就把相同字符数量 $+1$，如果相同字符数量 $\ge\lceil\frac{k}{2}\rceil$，则重题数 $+1$。最后输出即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a;
string s,t;
int main(){
	cin>>n>>s;
	while(n--){
		cin>>t;
		int c=0;
		for(int i=0;i<s.size();i++)if(s[i]==t[i])c++;
		if(c>=(s.size()+1)/2)a++;
	}
	cout<<a<<'\n'<<(!a?"Good job!":"Make persistent efforts.");
	return 0;
}
```

---

## 作者：__Luna__ (赞：1)

本题暴力比对即可，最大比较次数 $10^5$，够用。   
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char str[10000],str2[10000];
int main()
{
	int n,m=0;
	scanf("%d\n%s",&n,str);
	while(n--)
	{
		scanf("%s",str2);
		for(int i=0,j=0;str[i]!=0&&str2[i]!=0;i++)
		{
			if(str[i]==str2[i])j++;
			if(j*2>=strlen(str))
			{
				m++;
				break;
			}
		}
	}
	printf("%d\n",m);
	if(m==0)puts("Good job!");
	else puts("Make persistent efforts.");
}
```

---

## 作者：ivyjiao (赞：1)

简单模拟，每次把小 K 的题目名称与其他题目名称比较即可。

注意：

- 当两道题题目名称有**大于等于** $\ge \left\lceil\frac{k}{2} \right\rceil$ 的字符相同就叫重题了。
- 输出注意大小写。


```
#include<iostream>
using namespace std;
string a[10001],s;
int n,tar;
int main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++) cin>>a[i];
    tar=0;
    for(int j=1;j<=n;j++){
        int temp=0;
        for(int k=0;k<a[j].size();k++) if(a[j][k]==s[k]) temp++;
        if(temp>=s.size()/2.00) tar++;
    }
    cout<<tar<<endl;
    cout<<(tar? "Make persistent efforts.":"Good job!")<<endl;
}
```

---

## 作者：Luogu_916767 (赞：1)

[in luogu](https://www.luogu.com.cn/problem/P11137)

### 题目大意

给定一个字符串 $s$ 和另外 $n$ 个字符串，判断 $n$ 个字符串中是否有字符串与 $s$ 互为重题。输出两行，第一行输出重题数量，若没有重题则第二行输出 `Good job!`，否则输出 `Make persistent efforts.`。

### 思路分析

直接暴力比较每一个字符串和 $s$ 的相似度，记录重题数量，最后判断是否有重题。

### Code

代码较丑，大佬勿喷。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
string s;
string k;
bool fun(string p){
    int ans = 0;
    for(int i = 0; i < p.size(); i ++ ){
        if(s[i] == p[i]){
            ans ++ ;
        }
    }
    if(ans * 2 >= p.size())return 1;
    return 0;
}

int main(){
    cin>>n>>s;
    int ans = 0;
    for(int i = 1; i <= n; i ++ ){
        cin>>k;
        if(fun(k))ans ++ ;
    }
    cout<<ans<<"\n";
    if(ans == 0){
        cout<<"Good job!";
    }else{
        cout<<"Make persistent efforts.";
    }
}
```

---

## 作者：T_TLucas_Yin (赞：1)

按照题意，比较第一个字符串与后面每个字符串相同字符的数量即可。注意判重的字符数量要用长度**向上取整**。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string c,s[10005];
int main(){
	cin>>n>>c;
	int sum=0,m=c.size();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		int cnt=0;
		for(int j=0;j<m;j++)
			if(s[i][j]==c[j]) cnt++;
		if(cnt>=(m+1)/2) sum++;
	}
	cout<<sum;
	if(sum==0) cout<<"\nGood job!";
	else cout<<"\nMake persistent efforts.";
	return 0;
}
```

---

## 作者：a18981826590 (赞：1)

# [P11137 [APC001] B - Checker](https://www.luogu.com.cn/problem/P11137)
## 解题思路
按题意模拟即可。

将第一个字符串和后面的一一比较，记录相同位置相同字符的个数。

当相同位置相同字符的个数大于等于字符串长度的一半时，两道题就是重题。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,m,n;
string s,t;
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>s;
	while(n--){
		cin>>t;
		l=0;
		for(int i=0;i<min(s.size(),t.size());i++){
			if(s[i]==t[i]) l++;
		}
		if(l*2>=min(s.size(),t.size())) m++;
	}
	cout<<m<<'\n';
	if(m==0) cout<<"Good job!";
	else cout<<"Make persistent efforts.";
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
**模拟题**，跟着题目要求写代码就不会错。  
我们可以定义一个 `check` 函数判断一下是否重题，是则 $ans \gets ans + 1$，最终根据 `ans` 值是否为 $0$ 而分别输出两个字符串。  
`check` 函数思路见代码注释。
## CODE：

```cpp
#include <iostream>
using namespace std;
int n, ans;
string t, s;
bool check(string t, string s)
{
    int num;
    if (t.size() % 2 == 0) num = t.size() / 2;
    else num = t.size() / 2 + 1;//判断多少个字符冲突为重题
    for (int i = 0; i < t.size(); i++)
        if (t[i] == s[i])
            --num;//统计
    return num <= 0;//判断最终是否重题
}
int main()
{
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        if (check(t, s)) 
            ++ans;
    }
    cout << ans << '\n';
    if (ans == 0) cout << "Good job!";
    else cout << "Make persistent efforts.";
    return 0;
}
```

---

## 作者：JoeZYQ (赞：0)

### 思路
枚举每一位判断是否重题，若重题计数器加一，最后按题目意思输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main(){
    int T,cnt=0,tmp=0;
    string s,S;
    cin>>T>>s;
	while(T--){
		tmp=0;
    	cin>>S;
    	for(int i=0;i<S.size();i++)
    		if(S[i]==s[i])
				tmp++;//相同位置的字符相同数量 
		if(tmp>=S.size()/2+S.size()%2)cnt++;//重题则计数器+1 
	}
	cout<<cnt<<"\n";
	if(cnt==0)cout<<"Good job!";
	else cout<<"Make persistent efforts.";//按要求输出 
	return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：0)

### 思路分析

没什么好说的，每次输入时枚举每一位一一比对，统计相同位置的字符相同的数量，看看是否重题，并统计重题数量，最后按要求输出即可，具体看代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    string s;
    cin>>s;
    int a=0;
	while(t--){
    	int x=0;
    	string ss;
    	cin>>ss;
    	for(int i=0;i<ss.size();i++){
    		if(ss[i]==s[i])x++;
		}
		if(x>=ss.size()/2+ss.size()%2)a++;
	}
	cout<<a<<"\n";
	if(a==0){
		cout<<"Good job!";
	}
	else cout<<"Make persistent efforts.";
	return 0;
} 
```

---

## 作者：cly312 (赞：0)

注意到每个字符串长度相同，所以我们可以按照题意逐个遍历小 K 的题目和所有题库里的题目，统计相同位置字符相同的个数，如果大于 $\left\lceil\frac{k}{2} \right\rceil$，这两个题目就是重题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool c(string a,string b){
    int k=ceil(a.length()/2.0);
    int l=a.length();
    int cnt=0;
    for(int i=0;i<l;i++) if(a[i]==b[i]) cnt++;
    return cnt>=k;
}
int main(){ 
    int n;
    int ans=0;
    string s;
    cin>>n>>s;
    while(n--){
        string x;
        cin>>x;
        ans+=c(s,x);
    }
    if(ans==0){
        cout<<"0\nGood job!\n";
    }else{
        cout<<ans<<endl<<"Make persistent efforts.";
    }
}
```

---

## 作者：jiangyunuo (赞：0)

### 题目大意及思路：
当小 K 出的题与题库中的题的名称中有一半及以上的相同位置有相同的字符，则我们认为重题了，我们要求出重题的数量，并输出，输出重题数量后我们还要再根据是否重题输出 `Make persistent efforts.` 或 `Good job!`。本题很简单，我们只需按题目说的一个一个去对比小 K 出的题与题库的题的名称，最后就可以求出答案了。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	string ch,sh[n+1];    //ch 为小 K 的题，sh 为题库的题。
	cin>>ch;
	int len=ch.size();   //求出题目名称的长度。
	int a,b=0,c;       //a 表示小 K 的题与题库的题名称相同位置有相同字符的数量，b 表示重题数量，c 表示重题的界线。
	c=len/2;
	if(len%2)c++;     //求出重题界线。
	for(int i=1;i<=n;i++){
		a=0;            //将 a 清零。
		cin>>sh[i];
		for(int j=0;j<len;j++){    //求出小 K 的题与题库的题名称相同位置有相同字符的数量。
			if(ch[j]==sh[i][j])a++;
		}
		if(a>=c)b++;   //计算重题数量。
	}
	cout<<b<<endl;
	if(b)cout<<"Make persistent efforts."<<endl;
	else cout<<"Good job!"<<endl;
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

这道题是道纯模拟的题目，暴力模拟就可以了。

# 思路

当把小 K 的文章和所有文章输入完成后就用双重循环。如果有相同的字母，就把计数器加一。最后输出计数器，如果计数器为零再输出 `Good job!`，否则输出 `Make persistent efforts.`。

**不用担心超时，因为 $1\le n\le10^4$，字符串长度不超过 $10$，最坏复杂度不会超时。**

# AC code

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int len = s.length();
    int h = (len + 1) / 2;
    string target;
    vector<string> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int cnt = 0;
    for (const string& p : a) {
        int tmp = 0;
        for (int i = 0; i < len; ++i) {
            if (s[i] == p[i]) {
                ++tmp;
            }
        }
        if (tmp >= h) {
            ++cnt;
        }
    }
    cout << cnt << endl;
    if (cnt == 0) {
        cout << "Good job!" << endl;
    } else {
        cout << "Make persistent efforts." << endl;
    }
    return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

按照题意模拟即可。先输入一个 $s_0$ 表示待比较的字符串，再输入 $n$ 行各一个字符串 $s_i$。枚举所有的 $s_1\sim s_n$，枚举与 $s_i$ 在同位置上字符相同的个数，比较与 $\lceil \frac{l}{2}\rceil$ 大小即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int n,ans;
string s[N];
int F(int a,int b){//计算 l/2 上取整
    if(a%b==0) return a/b;
    return a/b+1;
}
int main(){
    cin>>n>>s[0];
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    int l=s[1].size();
    int ll=F(l,2);
    for(int i=1;i<=n;i++){
    	int cnt=0; 
        for(int p=0;p<l;p++){
            if(s[i][p]==s[0][p]) cnt++;
        }
        if(cnt>=ll) ans++;
    }
    if(!ans) cout<<"0\nGood job!";
    else cout<<ans<<'\n'<<"Make persistent efforts.";
    return 0;
}
```

---

## 作者：Soviet_Onion (赞：0)

## [APC001] B - Checker 题解
### Solution
完全不需要长度为 $10^4$ 的字符串数组，我们直接边读入边处理，按位比对两个串，统计相同字符个数，最后判断是否 $\ge \lceil\frac{k}{2} \rceil$ 即可。其中， $k$ 是所有字符串的长度。

#### 注意事项
- 输出时的标点符号。
### [AC](https://www.luogu.com.cn/record/179358554) Code
```cpp
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const int N=1e4+10;
string txt,mode;
int main(){
	int n,ans=0;
	cin>>n>>mode;
	for(int i=1;i<=n;i++){
		int cnt=0;
		cin>>txt;
		for(int i=0;i<mode.size();i++){
			if(txt[i]==mode[i]) cnt++;
		}
		if(cnt>=ceil(mode.size())/2) ans++;
	}
	cout<<ans<<endl;
	cout<<(!ans?"Good job!":"Make persistent efforts.")<<endl;
    return 0;
}

```

---

## 作者：Eason_cyx (赞：0)

直接将小 K 的题目名称和 $n$ 道题目名称一一对比，看有多少题目满足“重题”即可。

**注意输入格式，是先输入小 K 的字符串，不是后输入。**

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[10005];
int main() {
	int n; cin >> n;string t; cin >> t; 
	for(int i = 1;i <= n;i++) cin >> s[i];
	int siz = t.size();
	int ans = 0;
	for(int i = 1;i <= n;i++) {
		int cnt = 0;
		for(int j = 0;j < siz;j++) cnt += (s[i][j] == t[j]);
		if(cnt >= (int)(ceil(siz / 2.0))) ans++;
	}
	cout << ans << endl << (ans == 0 ? "Good job!" : "Make persistent efforts.") << endl;
	return 0;
}
···

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11137)
## 思路
因为 $n \le 10^4$，所以可以暴力枚举。

依次将 $s$ 和其他的串相比，若相同位置的相同字符 $\ge \lceil \frac{|s|}{2} \rceil$，那答案就加一。

最后判断答案按题目要求输出即可。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5; 

int n, ans;
string t;
string s[N];

int cnt(string s1, string s2)
{
	int cnt = 0;
	for (int i = 0; i < s1.size(); i++)
		if (s1[i] == s2[i]) cnt++;
	return (cnt >= ceil(s1.size() / 2.0));
}

int main()
{
	cin >> n;
	cin >> t;
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	for (int i = 1; i <= n; i++)
		if (cnt(s[i], t))
			ans++;
	if (!ans) printf("0\nGood job!\n");
	else printf("%d\nMake persistent efforts.\n", ans);
	return 0;
}

```

---

## 作者：_Jocularly_ (赞：0)

按照题意模拟，每输入一个字符串都直接枚举每一个元素，因为保证长度相等，所以直接对比是否相等即可，相等时累加器加一，最后判断即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s;
int cnt;
signed main(){
    cin >> n;
    cin >> s;
    for(int i=1;i<=n;i++){
        string a;
        cin >> a;
        int res = 0;
        for(int j=0;j<a.size();j++){
            if(s[j] == a[j]) res ++;
        }
        if(res >= ceil(a.size() * 1.0 / 2)) cnt ++;
    }
    cout << cnt << endl;
    if(!cnt) cout << "Good job!";
    else cout << "Make persistent efforts.";
    return 0;
}
```

---

