# Qingshan Loves Strings

## 题目描述

Qingshan has a string $ s $ , while Daniel has a string $ t $ . Both strings only contain $ \texttt{0} $ and $ \texttt{1} $ .

A string $ a $ of length $ k $ is good if and only if

- $ a_i \ne a_{i+1} $ for all $ i=1,2,\ldots,k-1 $ .

For example, $ \texttt{1} $ , $ \texttt{101} $ , $ \texttt{0101} $ are good, while $ \texttt{11} $ , $ \texttt{1001} $ , $ \texttt{001100} $ are not good.

Qingshan wants to make $ s $ good. To do this, she can do the following operation any number of times (possibly, zero):

- insert $ t $ to any position of $ s $ (getting a new $ s $ ).

Please tell Qingshan if it is possible to make $ s $ good.

## 说明/提示

In the first test case, $ s $ is good initially, so you can get a good $ s $ by doing zero operations.

In the second test case, you can do the following two operations (the inserted string $ t $ is underlined):

1. $ \texttt{1}\underline{\texttt{010}}\texttt{11} $
2. $ \texttt{10101}\underline{\texttt{010}}\texttt{1} $

and get $ s = \texttt{101010101} $ , which is good.

In the third test case, there is no way to make $ s $ good after any number of operations.

## 样例 #1

### 输入

```
5
1 1
1
0
3 3
111
010
3 2
111
00
6 7
101100
1010101
10 2
1001001000
10```

### 输出

```
Yes
Yes
No
No
No```

# 题解

## 作者：No_Rest (赞：2)

# 思路

这道题我们可以来分类讨论：

- 当 $S_1$ 是好的，显然输出 `Yes`。
- 当 $S_1$ 是不是好的，且 $S_2$ 也不是好的，那么显然输出 `No`。

接下来是比较复杂的部分：$S_1$ 不是好的，但 $S_2$ 是好的。

可以发现，我们必须要在 $S_1$ 中所有相邻且相等的两个字符中间插入 $S_2$，否则 $S_1$ 总不是好的。

而如果插入 $S_2$ 后，$S_1$ 变成好的了，当且仅当 $S_1$ 被插入的两个字符之间与 $S_2$ 的两端不一样。比如说 $S_1$ = `00101`，那么 $S_2$ 的两端必须都是 `1`，比如 `101`。

所以，当 $S_1$ 相邻且相同的字符中又有 `0`，又有 `1` 时，是永远不可能成为好的字符串的。

综上：

- 当 $S_1$ 不是好的，但 $S_2$ 是好的时：
>> - 若 $S_1$ 相邻且相同的字符中又有 `0`，又有 `1` ，输出 `No`。
>> - 若 $S_1$ 相邻且相同的字符中只有 `0`，且 $S_2$ 的两端都是 `1`，输出 `Yes`。
>> - 若 $S_1$ 相邻且相同的字符中只有 `1`，且 $S_2$ 的两端都是 `0`，输出 `Yes`。
>> - 对于其他情况，输出 `No`。

# 实现

使用两个变量 $flag0, flag1$ 来保存两个字符串是否为好的。

再使用两个变量 $f0, f1$ 来保存 $S_1$ 相邻且相同的字符中，是否有 `0` 或 `1`。

然后直接按上面所述的来判断即可。

# Code

``` cpp
#include<iostream>
#include<cstring>
using namespace std;
int T, n, m;
string s, t;
bool flag0, flag1, f0, f1;
int main(){
	scanf("%d", &T);
	while(T--){
		flag0 = flag1 = f0 = f1 = 0;
		scanf("%d%d", &n, &m);
		cin >> s >> t;
		for(int i = 0; i < s.size() - 1; ++i)
			if(s[i] == s[i + 1] && s[i] == '0') flag0 = f0 = 1;//如果这个字符和下一个字符一样且都是0
			else if(s[i] == s[i + 1]) flag0 = f1 = 1;//如果这个字符和下一个字符一样且都是1
		for(int i = 0; i < t.size() - 1; ++i)
			if(t[i] == t[i + 1]) flag1 = 1;//如果这个字符和下一个字符一样
		if(!flag0) puts("yes");//如果 S1 本来就是好的
		else if(f0 && f1) puts("no");//如果两个字符串都不是好的
		else if(flag0 && flag1) puts("no");//如果 S1 相邻且相同的字符中即有 0 也有 1
		else if(f0 && t[0] == '1' && t[t.size() - 1] == '1') puts("yes");//如果 S1 相邻且相同的字符中只有 0，且 S2 的两端都是 1
		else if(f1 && t[0] == '0' && t[t.size() - 1] == '0') puts("yes");//如果 S1 相邻且相同的字符中只有 1，且 S2 的两端都是 0
		else puts("no");//其他情况
	}
    return 0;
}
```

---

## 作者：lowbit (赞：1)

如果 $S_2$ 不是好的，那无论如何插入都无法使 $S_1$ 变成好的。

否则，对于 $S_1$ 中每一对相等的相邻位置，直接判断在中间插入 $S_2$ 能否合法即可。

注意特判一下 $S_1$ 本身就合法的情况。

```cpp
cin >> n >> m;
scanf("%s%s", s+1, t+1);
int fl=1, p=1;
rep(i, 2, m) fl &= t[i] != t[i-1];
rep(i, 2, n) {
   if(s[i] == s[i-1]) fl &= t[1]!=s[i-1] && t[m]!=s[i], p=0;
}
printf(fl|p ? "Yes":"No");
```

---

## 作者：dyyzy (赞：1)

## 题目描述

一个序列是好的，当且仅当这个序列中 $0$ 和 $1$ 交替出现，给你两个仅包含 $0$ 和 $1$ 的字符串 $S_1$ 和 $S_2$ ，询问能否通过在 $S_1$ 中插入若干个 $S_2$ 的方式使得 $S_1$ 变成好的序列。

## 思路

考虑以下几种情况：

- 如果 $S_1$ 本身是一个好的序列，自然不用插入 $S_2$。

- 如果 $S_2$ 本身不是好的，插入 $S_2$ 无法使 $S_1$ 变好。

- 在不违反上一条的情况下，$S_2$ 首尾全为 $0$ 即可使仅包含连续的 $1$ 的 $S_1$ 变成好的，$S_2$ 首尾全为 $1$ 同理。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define int long long
inline int read(){
	int x=0,flag=1;char ch=getchar();
	while(ch<'0' || ch>'9'){flag=(ch=='-')?-1:1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*flag;
}
const int N=200005;
string s1,s2;
int n1,n2;
inline bool pd(int x){
	return (s2[1]==x+'0' && s2[n2]==x+'0');
}
inline bool pd1(){
	for(int i=1;i<=n2;++i) if((s2[i]=='0' && s2[i-1]=='0') || (s2[i]=='1' && s2[i-1]=='1')) return true;
	return false;
}
signed main(){
	int T=read();
	while(T--){
		n1=read(),n2=read();
		s1,s2;cin>>s1>>s2;
		s1="-"+s1;s2="-"+s2;
		bool flag0=false,flag1=false;
		for(int i=1;i<=n1;++i){
			if(s1[i]=='0' && s1[i-1]=='0') flag0=true;
			if(s1[i]=='1' && s1[i-1]=='1') flag1=true;
		}
		if(flag0 && flag1) {cout<<"No\n";continue;}
		if(!flag0 && !flag1) {cout<<"Yes\n";continue;}
		if(pd1()) {cout<<"No\n";continue;}
		if(flag0 && pd(1)) {cout<<"Yes\n";continue;}
		if(flag1 && pd(0)) {cout<<"Yes\n";continue;}
		cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：BugGod (赞：0)

首先如果 $s$ 本身合法，那么就是 `Yes`。

如果 $s$ 不合法，我们就需要在相邻两个相同的字符间插入 $t$，如果 $t$ 本身不合法，那么不合法的地方只会更多，所以是 `No`。

现在确认 $t$ 是合法的，我们考虑找出所有字符相同的地方，我们设 $t$ 为 $t_1t_2\cdots t_m$，相同的字符为 $s_k,s_{k+1}$，显然，插入 $t$ 后这个地方为 $s_kt_1t_2\cdots t_ms_{k+1}$，如果这个地方合法，那么要求 $s_k$ 与 $t_1$ 不同，$t_m$ 与 $s_{k+1}$ 不同（$t$ 内部都不同），如果该条件不成立，就是 `No`，否则为 `Yes`。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int check(string s)//判断字符串是否合法
{
    for(int i=1;i<s.size();i++)
    {
        if(s[i-1]==s[i])return 0;
    }
    return 1;
}
int n,m,tt;
string s,t;
signed main()
{
    cin>>tt;
    while(tt--)
    {
        cin>>n>>m>>s>>t;
        if(check(s)){cout<<"Yes"<<endl;continue;}//原字符串合法
        if(!check(t)){cout<<"No"<<endl;continue;}//s不合法且t不合法
        int flag=1;
        for(int i=1;i<n;i++)
        {
            if(s[i-1]==s[i])
            {
                if(s[i-1]==t[0]||s[i]==t[m-1])
                {
                    flag=0;
                    break;
                }
            }
        }
        if(flag)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
```

---

## 作者：myyyIisq2R (赞：0)

 [CF1890B Qingshan Loves Strings 题解](https://www.luogu.com.cn/problem/CF1890B)
## 题意
对于两个 `01` 串 $s$ 和 $t$，输出能否使得将 $t$ 插入 $s$ 中 $k$（$0\le k$）次使得 $s$ 相邻位置元素不相等。

## Solution
一、对于 $t$，如果本身就已经出现了两相邻位置相等的子串（即 `00` 和 `11`），那么将其插入 $s$，也必然不可能避免出现，该情况输出 `NO`。

二、对于一般情况，记录 $s$ 中含有 `00` 和 `11` 的情况，我在程序中用 $cosit_1$ 与 $cosit_2$ 分别表示 $s$ 中含有 `00` 和 `11` 的情况，如果都没有则说明不需要插入，直接输出 `YES`。

对于需要插入的情况，我用 $sit_1$ 和 $sit_2$ 表示 $t$ 左右两端组合情况。由于需要插入 $s$ 中使得相邻相等两位分开，则应当取 $cosit$ 数组中相反的情况。

举个例子，当 $cosit_1$ 为真时，说明 $s$ 中有 `11` 串，当且仅当 $t$ 的最左端为 $0$，最右端为 $0$ 时，可以将 $s$ 拆开，那么此时便将 $sit_1$ 设为真。

若 $cosit_i$ 和 $sit_i$ 同时为真，我们认为 $s$ 是可拆的，输出 `YES`；一旦有一个为真且一个为假，该情况便不可拆，输出 `NO`。

细节见代码。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	
	int T;
	cin >> T;
	while (T--)
	{
		bool sit[3]{};
		//00 11 
		bool cosit[3]{};
		//11 00 
		int a, b;
		cin >> a >> b;
		string s1, s2;
		cin >> s1 >> s2;
		bool oktag = true;
		
		for (int i{}; i < s1.length() - 1; i++)
		{
			if (s1[i] == '1' && s1[i + 1] == '1') cosit[1] = true;
			if (s1[i] == '0' && s1[i + 1] == '0') cosit[2] = true;
			
			
		}
		
		if(!cosit[1] && !cosit[2])  //该情况不需要拆s
		{
			cout<<"Yes\n";
			continue;
		}
		for (int i{}; i < s2.length()-1; i++)
		{
			if (s2[i] == s2[i + 1])
			{
				oktag = false;
				cout << "No\n";
				break;
			}
		}
		if (!oktag)
			continue;
		
		if (s2[0] == '0' && s2[b - 1] == '0')sit[1] = true; //t首尾情况
		if (s2[0] == '1' && s2[b - 1] == '1')sit[2] = true;
		

		bool tag = false;
		for (int i{ 1 }; i <= 2; i++)
		{
			//cout << sit[i] << " " << cosit[i] << endl;
			if ((sit[i] && !cosit[i])||(!sit[i]&&cosit[i])) //若一个为真一个为假 不可拆
			{
				cout << "No\n";
				tag = true;
				break;
			}
		}
		if (!tag) //可拆
		{
			cout << "Yes\n";
		}
	}
}
```

---

## 作者：hikariyo_ (赞：0)

题意是判断能否通过在 $s$ 中插入 $t$ 使得 $s$ 中没有连续的 $0$ 或 $1$。

首先有一个思路，就是 $t$ 只会插在连续的 $0$ 或者连续的 $1$ 之间，否则是没有意义的。

其次，我们先看 $t$ 它能否让整个子串去掉连续的 $0$ 或 $1$，用 $A[0/1]$ 统计贡献。如果 $t$ 的开头和结尾都是 $0$，那么在插入后会先去掉一个连续的 $1$，也就是 $A[1]=-1$，对于 $0$ 同理。

然后，我们还要观察 $t$ 本身带来了什么影响。如果 $t$ 里面就存在连续的 $0$ 或者 $1$，我们就要改动对应的 $A[0/1]$。

最后分类讨论：

1. 如果 $s$ 中含有连续的 $0$ 和连续的 $1$，需要 $A[0]<0\text{ and }A[1] < 0$（当然这是一定不可能的）。

2. 如果 $s$ 中只含有连续的 $0$，那么需要 $A[0]<0 \text{ and } A[1] = 0$。

3. 如果 $s$ 中只含有连续的 $1$，那么需要 $A[1]<0 \text{ and } A[0]=0$。

4. 如果都不是，本来就没有连续的 $0,1$，直接返回 $\text{true}$。

赛后意识到我把题目变复杂了，求大佬们轻喷/kk

```cpp
#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    // A[0] 统计对连续的 0 贡献, A[1] 对连续的 1 贡献
    int A[2] = {0, 0};
    if (t[0] == '0' && t[m-1] == '0') A[1]--;
    if (t[0] == '1' && t[m-1] == '1') A[0]--;

    for (int i = 0; i < m-1; i++) {
        int j = i+1;
        if (t[i] == t[j]) A[t[i]^48]++;
    }

    int cnt[2] = {0, 0};
    for (int i = 0; i < n-1; i++) {
        int j = i+1;
        if (s[i] == s[j]) cnt[s[i]^48]++;
    }
    
    if (cnt[0] && cnt[1]) return A[0] < 0 && A[1] < 0;
    if (cnt[0]) return A[0] < 0 && A[1] == 0;
    if (cnt[1]) return A[1] < 0 && A[0] == 0;
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) printf("%s\n", solve() ? "YES" : "NO");
    return 0;
}

```


---

