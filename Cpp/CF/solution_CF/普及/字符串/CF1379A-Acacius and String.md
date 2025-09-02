# Acacius and String

## 题目描述

Acacius is studying strings theory. Today he came with the following problem.

You are given a string $ s $ of length $ n $ consisting of lowercase English letters and question marks. It is possible to replace question marks with lowercase English letters in such a way that a string "abacaba" occurs as a substring in a resulting string exactly once?

Each question mark should be replaced with exactly one lowercase English letter. For example, string "a?b?c" can be transformed into strings "aabbc" and "azbzc", but can't be transformed into strings "aabc", "a?bbc" and "babbc".

Occurrence of a string $ t $ of length $ m $ in the string $ s $ of length $ n $ as a substring is a index $ i $ ( $ 1       \leq i \leq n - m + 1 $ ) such that string $ s[i..i+m-1] $ consisting of $ m $ consecutive symbols of $ s $ starting from $ i $ -th equals to string $ t $ . For example string "ababa" has two occurrences of a string "aba" as a substring with $ i = 1 $ and $ i = 3 $ , but there are no occurrences of a string "aba" in the string "acba" as a substring.

Please help Acacius to check if it is possible to replace all question marks with lowercase English letters in such a way that a string "abacaba" occurs as a substring in a resulting string exactly once.

## 说明/提示

In first example there is exactly one occurrence of a string "abacaba" in the string "abacaba" as a substring.

In second example seven question marks can be replaced with any seven lowercase English letters and with "abacaba" in particular.

In sixth example there are two occurrences of a string "abacaba" as a substring.

## 样例 #1

### 输入

```
6
7
abacaba
7
???????
11
aba?abacaba
11
abacaba?aba
15
asdf???f???qwer
11
abacabacaba```

### 输出

```
Yes
abacaba
Yes
abacaba
Yes
abadabacaba
Yes
abacabadaba
No
No```

# 题解

## 作者：wmy_goes_to_thu (赞：5)

这道题比赛我只得了 200 多分。。。

这道题应该是最简单的了，首先判断有多少个现成的 abacaba，如果这个数量 $\geq 2$，那么输出 `No`，如果 $=1$，那么就把所有的问号都改成 $z$，输出 `Yes`。如果这个数 $=0$，那么进入下一步：

由于关系比较复杂，所以我们采用暴力 $\mathcal O(t \times n^2)$ 枚举，常熟很小，能过。就是枚举我们选哪个，然后判断是否可行即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[55],s2[55];
char t2[10]="abacaba";
int q[105];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,tt=0,tt2=0,ans=0,ans2=0,tot=0;
		cin>>n;
		scanf("%s",s+1);
		for(int i=1;i<=n-6;i++)
		{
			int flag=1;
			for(int j=i;j<=i+6;j++)
			{
				if(s[j]!='?'&&s[j]!=t2[j-i])
				{
					flag=0;
					break;
				}
				if(s[j]=='?')flag=2;
			}
			if(flag==1)
			{
				tt=i;
				ans++;
			}else if(flag==2)
			{
				ans2++;
				q[++tt2]=i;
			}
		}
		if(ans>=2||ans==0&&ans2==0)cout<<"No"<<endl;
		else if(ans)
		{
			cout<<"Yes"<<endl;
			for(int i=1;i<tt;i++)
			{
				if(s[i]=='?')printf("z");
				else printf("%c",s[i]);
			}
			cout<<t2;
			for(int i=tt+7;i<=n;i++)
			{
				if(s[i]=='?')printf("z");
				else printf("%c",s[i]);
			}
			cout<<endl;
		}else
		{
			int fio=0;
			for(int i=1;i<=tt2;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(j>=q[i]&&j<=q[i]+6)s2[j]=t2[j-q[i]];
					else
					{
						if(s[j]=='?')s2[j]='z';
						else s2[j]=s[j];
					}
				}
				int ans=0;
				for(int j=1;j+6<=n;j++)
				{
					int flag=1;
					for(int k=j;k<=j+6;k++)if(s2[k]!=t2[k-j])
					{
						flag=0;
						break;
					}
					ans+=flag;
				}
				if(ans==1)
				{
					fio=1;
					cout<<"Yes\n";
					for(int j=1;j<=n;j++)cout<<s2[j];
					cout<<endl;
					break;
				}
			}
			if(!fio)cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：Theophania (赞：3)

字符串长度很短，可以用暴力解决：

由于需要匹配的字符串长度为7，那么如果存在符合题意的唯一子串，该子串必然是 $s[0] \cdots s[6]$，$s[1] \cdots s[7]$ 到 $s[n-7]\cdots s[n-1]$ 中的一个（废话）。所以尝试把 $s[0]$ 到 $s[n-7]$ 中的每一个字符当成 `abacaba` 的起点，检查其后面的字符能否形成这样的子串（如果遇到不匹配的字符就必然不行，遇到 `?` 就把它转化成子串中相应的字符）。如果这样的子串成功构造了出来，就把剩下的所有 `?` 变成 `abacaba` 中不存在的字母（比如 `z`），然后对整个字符串匹配一遍检查 `abacaba` 的出现次数，如果是一次就表明找到了答案，否则遍历字符串中下一个字母。

这段话看起来有点绕，看了代码应该很容易理解：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;

const string match = "abacaba";
bool check(string s, int k)
{
    int cnt = 0;
    for (int i = 0; i < 7; ++i)//从s[k]开始构造目标子串
    {
        if (s[k + i] == '?')
            s[k + i] = match[i];
        else if (s[k + i] != match[i])
            return false;
    }
    /*输出的时候不能有问号所以要替换掉*/
    for (int i = 0; i < s.size(); ++i)
        if (s[i] == '?')
            s[i] = 'z';
    /*计算子串个数*/
    for (int i = 0; i < s.size(); ++i)
        if (s.substr(i, 7) == match)
            cnt++;
    if (cnt == 1)
    {
        cout << "Yes\n" << s << '\n';
        return true;
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        string s;
        cin >> n >> s;
        bool flag = false;
        for (int i = 0; i < n - 6; ++i)
            if (check(s, i))
            {
                flag = true;
                break;
            }
        if (!flag)
            cout << "No" << '\n';
    }
    return 0;
}
```



---

## 作者：Otue (赞：2)

细节非常多的一道题。
## 思路
首先，我们可以先找到现成 `abacaba` 的个数，记为 $res$。

* 若 $res>1$，则说明不管怎么变都无法变成只有 $1$ 个 `abacaba` 的情况了，直接输出 `No`。
* 若 $res=1$，则不需要变直接输出 `Yes` 即可，但是因为输出不能带问号，所以把所有问号替换成任意一个小写字母即可。
* 若 $res=0$，直接暴力枚举每一个字符，看以后 $7$ 个字母中是否可以替换成 `abacaba`。如果找到了一个，直接退出，输出答案，否则输出 `No`。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int t, n;
string s;

bool check(int x) {
	string t = "abacaba";
	for (int i = 0; i < 7; i++) {
		if (s[i + x] != '?' && s[i + x] != t[i]) return 0;
	}
	return 1;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> s;
		int lens = s.size();
		int res = 0;
		for (int i = 0; i < lens; i++) {
			if (s.substr(i, 7) == "abacaba") res++;
		}
		if (res >= 2) puts("No");
		else if (res == 1) {
			for (int i = 0; i < lens; i++) if (s[i] == '?') s[i] = 'a';
			cout << "Yes\n" << s << endl;
		}
		else {
			int id = -1e9;
			for (int i = 0; i < lens - 6; i++) {
				if (check(i) != 0) {
					id = i;
					break;
				}
			}
            if (id == -1e9) {
                puts("No");
                continue;
            }
            else puts("Yes");
			for (int i = 0; i < id; i++) {
				if (s[i] == '?') cout << 'a';
				else cout << s[i];
			}
			cout << "abacaba";
			for (int i = id + 7; i < lens; i++) {
				if (s[i] == '?') cout << 'a';
				else cout << s[i];
			}
			puts("");
		}
	}
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1379/A)
我们需要找到一个方法，将包含问号的字符串替换为小写字母，使得生成的字符串中恰好包含一次子串`abacaba`。

## 思路
直接**暴力**。

对于字符串的每个可能的起始位置，检查是否可以将该位置的连续 $7$ 个字符替换为 `abacaba`。

对于每个可行的起始位置，构造一个临时字符串，将当前起始位置的 $7$ 个字符替换为 `abacaba`，其他问号替换为不影响结果的字母（如 `z`）。

检查构造后的临时字符串中 `abacaba` 是否仅出现**一次**。如果是，则输出结果；否则继续检查下一个可能的起始位置。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int T;
	cin >> T;
	string target = "abacaba";
	while (T--) {
		int n;
		string s;
		cin >> n >> s;
		bool found = false;
		string res;
		for (int i = 0; i <= n - 7; ++i) {
			// 检查当前位置i是否可以替换为目标子串
			bool valid = true;
			for (int k = 0; k < 7; ++k) {
				if (s[i + k] != '?' && s[i + k] != target[k]) {
					valid = false;
					break;
				}
			}
			if (!valid) continue;
			// 构造临时字符串
			string temp = s;
			for (int k = 0; k < 7; ++k) {
				temp[i + k] = target[k];
			}
			for (int j = 0; j < n; ++j) {
				if (temp[j] == '?' && (j < i || j >= i + 7)) {
					temp[j] = 'z';
				}
			}
			// 统计目标子串的出现次数
			int cnt = 0;
			for (int j = 0; j <= n - 7; ++j) {
				bool match = true;
				for (int k = 0; k < 7; ++k) {
					if (temp[j + k] != target[k]) {
						match = false;
						break;
					}
				}
				if (match) {
					cnt++;
				}
			}
			if (cnt == 1) {
				found = true;
				res = temp;
				break;
			}
		}
		if (found) {
			cout << "Yes\n" << res << "\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(Tn^2) $，可以通过本题。

---

## 作者：Hutao__ (赞：0)

## 思路

我们直接暴力 $O(t \times n^2)$ 枚举 ，先循环每一个字串的起点，判断这个子串是否满足要求(只出现过一次)，如果满足，把所有 $\texttt{?}$ 替换成 $\texttt{i}$，然后输出，否则继续往下找。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a="abacaba";
int t;
bool ck(string s,int p){
	int cnt=0;
	for(int i=p;i<p+7;i++){
		if(s[i]=='?')s[i]=a[i-p];//如果是?就改成正确的
		if(s[i]!=a[i-p])return 0;//如果不对直接返回
	}
	for(int i=0;i<s.size();i++)if(s[i]=='?')s[i]='i';//不能有?
	for(int i=0;i<s.size();i++){
		if(s.substr(i,7)==a)cnt++;//判断子串个数
	}
	if(cnt==1){
		cout<<"Yes\n"<<s<<'\n';
		return 1;
	}
	return 0;
}
int main(){
	cin>>t;
	while(t--){
		int n;
		string s;
		cin>>n>>s;
		bool f=0;
		for(int i=0;i<n-6;i++){
			if(ck(s,i)){
				f=1;
				break;
			}
		}
		if(!f)cout<<"No\n";
	}
	return 0;//完美收工~
}
```

---

## 作者：CodingOIer (赞：0)

## CF1379A Acacius and String 题解

### 思路分析

在本题中，题目需要我们构造一个字符串，使其包含且仅包含一个 $\texttt{abacaba}$。

下面有 $3$ 中情况：

- 已经有了大于 $2$ 个字符串匹配，我们无法减少，所以直接输出 $\texttt{No}$。
- 已经有了 $1$ 个字符串匹配，将其他的 $\texttt{?}$ 改为 $\texttt{d}$，输出。
- 如果没有任何一个字符串匹配，则尝试构造。

对于构造我们编写两个辅助函数：

> `int find(char *s, char *t);`
>
> 返回 $t$ 在 $s$ 中出现的次数。

> `char *check(int w, char *t);`
>
> 返回期望组成为 $s_w$ 到 $s_{w + 6}$ 组成的 $\texttt{abacaba}$ 的结果，无果则返回 $\texttt{WA}$。

下面是两个函数的实现（本文数组下标从 $1$ 开始）：

```cpp
int find(char *s, char *t)
{
    int res = 0;
    for (int i = 1; i <= n - 6; i++)
    {
        bool accept = true;
        for (int j = 0; j < 7; j++)
        {
            if (s[i + j] != t[j])
            {
                accept = false;
                break;
            }
        }
        if (accept)
        {
            res++;
        }
    }
    return res;
}
char *check(int w, char *t)
{
    strcpy(p + 1, s + 1);
    for (int i = 1; i < w; i++)
    {
        if (p[i] == '?')
        {
            p[i] = 'd';
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (p[w + i] != t[i] && p[w + i] != '?')
        {
            return "WA";
        }
        p[w + i] = t[i];
    }
    for (int i = w + 7; i <= n; i++)
    {
        if (p[i] == '?')
        {
            p[i] = 'd';
        }
    }
    if (find(p, t) == 1)
    {
        return p + 1;
    }
    else
    {
        return "WA";
    }
}
```

### 代码实现

按上文思路编写如下：

```cpp
#include <cstdio>
#include <cstring>
constexpr int MaxN = 1e3 + 5;
int t;
int n;
char s[MaxN];
char p[MaxN];
char res[MaxN];
int find(char *s, char *t)
{
    int res = 0;
    for (int i = 1; i <= n - 6; i++)
    {
        bool accept = true;
        for (int j = 0; j < 7; j++)
        {
            if (s[i + j] != t[j])
            {
                accept = false;
                break;
            }
        }
        if (accept)
        {
            res++;
        }
    }
    return res;
}
char *check(int w, char *t)
{
    strcpy(p + 1, s + 1);
    for (int i = 1; i < w; i++)
    {
        if (p[i] == '?')
        {
            p[i] = 'd';
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (p[w + i] != t[i] && p[w + i] != '?')
        {
            return "WA";
        }
        p[w + i] = t[i];
    }
    for (int i = w + 7; i <= n; i++)
    {
        if (p[i] == '?')
        {
            p[i] = 'd';
        }
    }
    if (find(p, t) == 1)
    {
        return p + 1;
    }
    else
    {
        return "WA";
    }
}
void solve()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    char *to = "abacaba";
    int res_cnt = find(s, to);
    if (res_cnt == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == '?')
            {
                s[i] = 'd';
            }
        }
        printf("Yes\n");
        printf("%s\n", s + 1);
        return;
    }
    if (res_cnt >= 2)
    {
        printf("No\n");
        return;
    }
    for (int i = 1; i <= n - 6; i++)
    {
        strcpy(res + 1, check(i, to));
        if (strcmp(res + 1, "WA") != 0)
        {
            printf("Yes\n");
            printf("%s\n", res + 1);
            return;
        }
    }
    printf("No\n");
    return;
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：enyyyyyyy (赞：0)

统计 `abacaba` 的个数，小于 $0$ 输出 `No`，统计 $s_0,s_1,s_2,\dots,s_{n-8},s_{n-7}$，用每一个 $i$，去判断 $s_i,s_{i+1}\dots s_{i+6},s_{i+7}$ 里有没有 `?` 或 `abacaba`，有的话在去判断。


Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll t,n;
string s;
int main(){
    t=read();
    while(t--){
	    ll flag=0;
		n=read();
		cin>>s;
		string op="abacaba";
		for(ll i=0;i+6<n;i++){
			string a=s;
			for(ll j=0;j<7;j++)
				if(a[i+j]=='?') 
					a[i+j]=op[j];
			for(auto &t:a){
				char t=a[j];
				if(t=='?') 
					t='y';//因为我叫enyyyyyyy 
			}
			ll cnt=0;
		    for(ll j=0;j+6<n;j++)
		    	if(a.substr(j,7)==op) 
					cnt++;
		    if(cnt==1){
		    	printf("Yes\n"),cout<<a,printf("\n");
		    	flag=1;//标记
            break;//注意！
			} 
		}
		if(!flag) printf("No\n");
	}
    return 0; 
}
```


---

