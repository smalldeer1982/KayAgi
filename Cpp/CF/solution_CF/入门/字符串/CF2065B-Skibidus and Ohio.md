# Skibidus and Ohio

## 题目描述

斯基比德斯得到一个由小写拉丁字母组成的字符串 $s$ 。如果 $s$ 包含的字母多于 $1$ ，他就可以：

- 选择一个索引 $i$ ( $1 \leq i \leq |s| - 1$ ， $|s|$ 表示 $s$ 的当前长度)，使得 $s_i = s_{i+1}$ .用任意一个小写拉丁字母替换 $s_i$ 。从字符串中删除 $s _{i+1}$。

斯基比达斯必须确定他通过任意操作所能达到的最小长度。

## 说明/提示

在第一个测试案例中，Skibidus 可以

- 对 $i = 2$ 执行操作。他将 $s_2$ 替换为 b，并从字符串中删除 $s_3$ 。然后， $s$ 就变成了 bb。
- 对 $i = 1$ 进行操作。他将 $s_1$ 替换为 b，并从字符串中删除 $s_2$ 。然后， $s$ 就变成了 b。
- 因为 $s$ 只包含 $1$ 个字母，所以斯基比达斯无法进行更多运算。

因此，第一个测试用例的答案是 $1$ 。

在第二个测试案例中，他无法对任何索引进行操作。因此，答案仍然是初始字符串的长度 $8$ 。

## 样例 #1

### 输入

```
4
baa
skibidus
cc
ohio```

### 输出

```
1
8
1
4```

# 题解

## 作者：zjinyi (赞：2)

# 题解：CF2065B
## 题目大意
有一个由小写字母组成的字符串 $s$，可以选择一个索引 $i$（$1 \le i \le |s|−1$，$|s|$ 表示字符串 $s$ 的长度），且 $s_i = s_{i+1}$。将 $s_i$ 替换为他选择的任意小写拉丁字母，并从字符串中删除 $s_{i+1}$。求：字符串 $s$ 通过任意次操作可以达到的最小长度。

## 题目分析
如果字符串中有两个相邻且相同的字母 $s_i$ 和 $s_{i+1}$，它们就会被会被替换成 $s_{i-1}$，再替换成 $s_{i-2}$，以此类推直到 $s_1$ 到 $s_{i+1}$ 之间只剩下 $2$ 个字母。

接着，这 $2$ 个字母可以被替换成 $s_{i+2}$，继续向后替换，直到整个字符串只剩下一个字母。

所以，如果字符串中有两个相邻且相同的字母，字符串的最小长度就是 $1$，否则，最小长度就是 $|s|$。

## 代码
杜绝抄袭，从我做起！
```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
	long long t;
	cin >> t;
	while (t--) // 多组数据 
	{
		string s;
		cin >> s;
		bool flag = false;
		for (int i = 0; i < s.size() - 1; ++i) // 注意下标从 0 开始 
		{
			if (s[i] == s[i + 1]) // 如果字符串中有两个相邻且相同的字母，做标记 
			{
				flag = true; 
			}
		}
		if (flag == true) // 判断并输出答案 
		{
			cout << 1 << endl;
		}
		else
		{
			cout << s.size() << endl;
		}
	}
	
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：2)

题意：

给出一个字符串，如果在字符串中有相邻两个字符相同，则删除其中一个字符，并将另一个字符改为任意字符，使操作后字符串长度最短，求操作后最短的长度。

思路：

不难证明，如果一个字符串有相邻两个字符相同，则一定能使字符串长度为 $1$。因为操作时把一个字符删掉后，另一个字符可以改为任意字符，将这个字符改为相邻的字符，可以继续操作，直到字符串长度为 $1$ 结束。如果字符串中没有任何两个相邻字符相同，则无法操作。所以如果字符串中有相邻两个字符相同则输出 $1$，否则输出原字符串长度。

代码很简单就不放了。

---

## 作者：NEKO_Daze (赞：1)

[洛谷CF2065B](https://www.luogu.com.cn/problem/CF2065B) || [CodeForces 2065 B](https://codeforces.com/contest/2065/problem/B)

### 简要题意
给出一个字符串 $s$ 并对其若干次操作，每次操作选择相邻且字母相同的两项，即索引 $i$ 满足 $1 \leq i \leq |s| - 1$，同时 $s_i = s_{i+1}$,将前者即 $s_i$ 替换为任意小写拉丁字母,并将后者 $s_{i+1}$ 从字符串中删除。直到无法进行操作时停止操作。求最小化字符串长度。

### 思路
一开始通过观察仅有的样例发现，如果字符串中存在相邻且字母相同的两项，那么答案为 $1$，否则为 $|s|$。在手搓了若干个样例后，我得到了同样的结果，于是提出了如下猜想：

* 若对于字符串 $s$ 中 $\exists s_i=s_{i+1}$，那么答案为 $1$，否则为 $|s|$。

按理来说至此我们已经可以编写代码来尝试验证猜想了，不过为了~~满足读者需求~~科学严谨的态度，我们可以简单进行证明：

通过思考不难发现，只要我们能够进行第一次操作，我们就可以将 $s_i$ 替换为 $s_{i-1}$ 或 $s_{i+2}$，以进行下一次操作，重复此过程直至只剩 $1$ 个字符为止。因此猜想是正确的。

好了，终于可以编写代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> s;
        bool flag = false;
        for (int i=0;i<s.length()-1;i++)
            if (s[i] == s[i+1]) {flag=true;break;}
        if (flag) cout << 1 << endl;
        else cout << s.length() << endl;
    }
}
```

时间复杂度 $O(t\times \max|s|)$，足以通过此题。

---

## 作者：Pyrf_uqcat (赞：1)

思维题。当有两个字母相同时，可以删去一个并且改变一个。这个字母改变是关键。它可以改变成它旁边的另一个字母，然后继续删除，继续改变。

所以只要有两个字母相同，以上操作成立，可以把串删到只剩一个字母为止。否则字符串长度无法改变。

赛时已过代码。


```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

string s;

signed main()
{
	int t;cin>>t;
	while(t--)
	{
		cin>>s;
		bool flag=0;
		for(int i=0;i<s.size()-1;i++)
		{
			if(s[i]==s[i+1]) flag=1;
		}
		cout<<(flag?1:s.size())<<endl;
	}
    return 0;
}
```

---

## 作者：Lele_Programmer (赞：1)

# CF2065B 题解

## 思路

两种情况。

1. 如果不存在相邻两个字母相同，则显然无法进行任何操作，答案为原串长。

2. 如果存在相邻两个字母相同，即 $S_i = S_{i+1}$，那么将 $S_i$ 设为 $S_{i+2}$，并删除 $S_{i+1}$，此时又可以进行操作，直到将右边的都删完，然后同理，左边的也全删完，剩下最后 $1$ 个字符，因此答案为 $1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

int T;

int main() {
    read(T);
    while (T--) {
        string s;
        cin>>s;
        bool ok=false;
        _rep(i,0,(int)s.size()-2) {
            if (s[i]==s[i+1]) {
                ok=true;
                break;
            }
        }
        if (!ok) writeln(s.size());
        else writeln(1);
    }
    return 0;
}
```

---

## 作者：cjx_AK (赞：1)

题目说给你一个字符串，可以把相邻两个相同字符变成任意一个字符，求操作后字符串最小长度。

不难发现，只要有一个满足条件可以合并，那么你就可以把这两个字符变成第三个字符，直到不能合并，也就是只有一个字符。

code：

```
#include <iostream>
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000001],sum[1000001],m;
char s[1001][1001];
string t;
signed main(){
	cin>>n;
while(n--){
	cin>>t;
	for(int i=0;i<t.size();i++){
		if(t[i]==t[i+1]){cout<<1<<endl;break;
		}
		else if(i==t.size()-1){
			cout<<t.size()<<endl;
			break;
		}
	}
}
	return 0;
}
```

---

## 作者：thedyingkai (赞：0)

### 理解题意
- 对于一个长度大于 $1$ 的字符串 $s$，如果有两个相邻字母相同，可以把们两个换成任意字母，求处理多次后字符串的最短长度。
- 如果有两个字母相同，把他们两个换成紧邻的一个字母，这样就全部换掉了，例如：
  > $s_1=\texttt{dhhkd}$，```hh``` 更换为 ```d```；
  > 
  > $s_2=\texttt{ddkd}$，```dd``` 更换为 ```k```；
  > 
  > $s_3=\texttt{kkd}$，```kk``` 更换为 ```d```；
  > 
  > $s_4=\texttt{dd}$，```dd``` 更换为 ```d```；
  > 
  > $s_5=\texttt{d}$，$s$ 达到最短。
- 其实就是相邻字母全不相同结果就是字符串长度，有相邻字母相同最后就只剩 $1$。
### 代码
```cpp
#include "iostream"
#include "cstring"
using namespace std;
int t;
char s[101];
int main(){
    cin>>t;
    while(t--){
        cin>>s;
        bool x=0;
        for(int i=1;i<strlen(s);i++) if(s[i]==s[i-1]) x=1;
        if(x) cout<<1<<endl;
        else cout<<strlen(s)<<endl;
    }
}
```

---

## 作者：Programming_Konjac (赞：0)

博客正在撰写中。

更新在：[这个 CSDN 账号上](https://blog.csdn.net/ainiyoung?type=blog)。
# 思路
设字符串为 $s$。

如果当前的下标为 $i$（从 $1$ 开始），并且 $s_i=s_{i+1}$，则可以将 $s_{i+1}$ 消除，然后 $s_i$ 变为 $s_{i-1}$，然后继续删，直到第二个字符，此时 $s_2=s_1$，则此时让 $s_1=s_3$，然后删掉 $s_2$，然后继续，到最后，只会剩下 $s_1$。

结论：如果存在 $s_i=s_{i+1}$，则输出 $1$，否则输出字符串长度。
# 代码
[代码](https://codeforces.com/contest/2065/submission/305170429)

---

## 作者：M1__ (赞：0)

# 题解：CF2065B Skibidus and Ohio
[题目传送门](https://www.luogu.com.cn/problem/CF2065B)
## 题目大意
对于一个字符串 $S$，进行如下操作：
- 选定一个 $i$，满足 $1 \le i \le |S|-1$，如果 $S_i=S_{i+1}$，那么删除 $S_{i+1}$，将 $S_i$ 改为任意小写字母。
- $|S|$ 尽可能小。
## 题目思路
为了使 $|S|$ 尽可能小，我们要使 $S_i=S_{i+1}$ 出现次数更多。                    
对于一个字符串 $\left \{ S_1,S_2,S_3,S_4,\cdots,S_n \right \} $，显然如下操作：
- 如果有两项相等那么经过操作后长度为 $1$。
- 如果相邻两项互不相等那么无法进行操作，结果为 $|S|$。
## 代码实现


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,len; string s;
int main() {
    cin>>t;
    while(t--){
    	cin>>s;
    	len=s.size();
    	bool flag=0;
    	for(int i=0;i<len-1;i++){
			if(s[i]==s[i+1]){
				flag=1; 
				break;
			}
		}
		(flag)?cout<<1<<'\n':cout<<len<<'\n';
	}
	return 0;
}

```

---

## 作者：SecuritySetting (赞：0)

题意：给出一个字符串，如果有相邻两个字符相同则将两个字符改为一个任意字符，求操作后字符串最短变为多少长。

思路：每一次操作都会使两个相邻且相同的字符改为一个任意字符，所以很容易想到，如果一个字符串中任意两个相邻的字符串都不相同，则无法操作，长度为原来的长度；否则，操作一次可以将这两个相同的字符改为与它们相邻的其中一个字符，这样可以一直操作，直到剩下一个字符。

所以最后答案就是：当字符串中不存在相邻两个字符相同输出原字符串长度，否则输出 $1$。

代码：多组数据加并入答案即可。

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2065B)

可以发现当有两个相邻字符相同时，它们就可以先合并成与前一个字符相同的字符，然后不断往前合并直到前面没有字符，然后再相同地往后合并，最后合并到只剩一个字符。

于是可以发现当字符串中有相邻的两个字符相同时答案为 $1$，否则为字符串的长度。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
char s[110];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cin>>s,n=strlen(s);
		int ans=n;
		for(register int i=0;i<n-1;i++) if(s[i]==s[i+1]){ans=1;break;}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：EternalLabyrinth (赞：0)

### 题意：

$T$ 组数据，每组一个字符串 $s$。可以重复执行以下操作直到不可执行：

如果存在 $i$ 使得 $s_i=s_{i+1}$，那么可以删除位置 $i$ 上的字符并把 $i+1$ 换成任意字符，每次操作后，字符串的长度显然减一。

### 解法：

观察到一个结论：若存在 $s_i=s_{i+1}$，一定可以消成一个字符，否则直接输出原串长度。

考虑构造证明，即每次消完一个字符后我们可以把当前字符改成和其前面或后面相同的字符，这样我们又可以消掉一组，以此类推，消掉 $len-1$ 个字符即可。

举个例子：如 `baacd`。消掉 `a` 把其中一个 `a` 变为前面的 `b`，字符串变为 `bbcd`。消掉 `b`，把其中一个 `b` 换为后面的 `c`，字符串变为 `ccd`。最后把 `c` 消掉换为 `d`。字符串变为 `dd`，消掉变为任意一个字符就好了。

于是我们就做完了。

---

## 作者：_Star_Universe_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2065B)
### 题意
小 S 有一个由小写拉丁字母组成的字符串 $s$。如果 $s$ 包含超过 $1$ 个字母，他可以： 

- 选择一个索引 $i$（保证 $1\leq i\leq |s|-1$，注意这里的 $|s|$ 表示 $s$ 的当前长度） 使得 $s_i=s_{i+1}$。将 $s_i$ 替换为他选择的任何小写拉丁字母。从字符串中删除 $s_{i+1}$。

请你确定小 S 通过任意数量的操作后字符串达到的最小可能长度。

### 思路
注意本题多测。

读懂题目后我们发现，一个字符串无非两种情况：
1. 有两个相邻字符一致。
2. 没有一致且相邻的字符。

那么对于第一种情况，显然可以先从两个相邻且相同的字符中删去一个，再把剩下一个字符改成左侧字符或右侧字符，然后继续消去……循环往复，每次减少一个字符，必定能将 $|s|$ 变成 $1$，因此输出 $1$。

对于第二种情况，很显然找不到操作的位置，自然无法进行任何操作使得字符串变短，直接将 $|s|$ 输出即可。

代码中遍历字符串判断是否有相邻字符一致，然后写两条分支语句判断即可。

---

## 作者：Besheep (赞：0)

## 题目大意
给定一个字符串 $s$，对于一次操作：

- 你可以选择第 $i$ 个位置 $(1 \leq i \leq |s|-1)$，如果 $s_{i}=s_{i+1}$，则可以删除 $s_{i+1}$，并将 $s_{i}$ 改为任意小写字母。

求经过任意次操作后，字符串 $s$ 的最小长度。

多测。$1 \leq T \leq 100,1 \leq |s| \leq 100$。

## 思路
**考虑到要使字符串 $s$ 的长度最小，所以要多进行删除操作，所以要让尽可能多的 $s_{i}=s_{i+1}$。**

我们不妨设一个字符串 $s_{1}s_{2}s_{3}s_{4}s_{5}$，其中 $s_{2}=s_{3}$。

第一次操作，可以选择 $i=2$，随后删除 $s_{3}$，因为「要让尽可能多的 $s_{i}=s_{i+1}$」，我们选择将 $s_{2}$ 改为 $s_1$，此时字符串为 $s_{1}s_{1}s_{4}s_{5}$。

下面的操作同理，我们发现，经过如上操作后，字符串 $s$ 的最小长度最终为 $1$。

---

当字符串内的字符互不相等时，无法选择第 $i$ 个位置，所以，字符串 $s$ 的最小长度最终为 $|s|$。

---

显而易见：
- 若对于任意 $s_{i}=s_{i+1},(1 \leq i \leq |s|-1)$ 成立，输出 $1$。
- 否则输出 $|s|$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n;
string s;
int main() {
    cin>>T;
    while(T--){
    	cin>>s;
    	n=s.size();
    	bool f=0;
    	for(int i=0;i<n-1;i++)if(s[i]==s[i+1]){
    		f=1;	
    		break;
		}
		if(f) cout<<1<<'\n';
    	else cout<<n<<'\n';
	}
	return 0;
}

```

---

## 作者：Wide_Master (赞：0)

## 正言

容易发现，如果这个字符串中有一个相邻且相同的字符，那么答案为 $1$，因为它可以变为自己左边或者右边的字符。

否则答案为 $n$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,T,r;
int main()
{
	cin>>T;
	while(T--){
		cin>>s;
		s=" "+s;
		r=-1;
		n=s.length();
		for(int i=n;i>=2;i--){
			if(s[i]==s[i-1]){
				r=i;
				break;
			}
		}
		if(r!=-1)cout<<1<<endl;
		else cout<<n-1<<endl;
	}
	return 0;
}
``````

---

## 作者：Lfz312g (赞：0)

# 题解：CF2065B Skibidus and Ohio
## 题意简析
如果对于 $s$ 序列，可以进行以下若干次操作，如果有 $s_i = s_{i-1}$，可以将 $s_i$ 修改成任意小写字母，并将 $s_{i+1}$ 删除，问最后序列最短长度。
## 题目分析
分类讨论题。  
如果 $s$ 中的相邻元素两两互不相等，无法进行操作，直接输出原序列长度即可。  
如果有 $s_i = s_{i+1}$，我们可以将 $s_i$ 置为 $s_{i-1}$ 或 $s_{i+2}$，对于 $s_{i-1}$ 或 $s_{i+2}$ 和 $s_i$ 再进行一次这样的操作，最后剩下一个单独的数无法进行操作。  
既如果 $s$ 中的元素，相邻元素两两互不相等,输出 `s.size()`，否则输出 `1`。  
## 代码实现

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
void solve()
{
	string s;
	cin>>s;
	for (int i=1;i<s.size();i++) {
		if (s[i]==s[i-1]) {
			cout<<1<<'\n';
			return;
		}
	}
	cout<<s.size()<<'\n';
}
int main()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	int T;
	cin>>T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：JZJR_A_0 (赞：0)

## 前置知识

* 贪心
* 构造

## 题意

给你一个仅有小写字母组成的字符串 $s$，你每次可以选择相邻的两个相同字母将其变为任意一个字母，问经过若干次操作后 $s$ 的最小长度。

## 思路

发现如果不存在两个相邻的相同字母，无法进行操作，长度不变。

当存在可操作的相邻相同字符，那将变换的字符改为其后面相同的字符，继续进行操作，直至长度为 $1$。

## 解决

从前往后扫一遍，存在可操作字符答案为 $1$，否则为 $|s|$。

### AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q,a[N];
inline void solve(){
	string s;
	cin>>s;
	n=s.size();
	if(n==1){
		cout<<"1\n";
		return ;
	}
	else {
		bool pd=0;
		for(int i=0;i<n-1;i++){
			if(s[i]==s[i+1])pd=1;
		}
		if(pd)cout<<"1\n";
		else cout<<n<<'\n';
	}
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
} 
```

---

## 作者：StormWhip (赞：0)

### 思路 
不难发现，若 $\exists i\in [1,\lvert s\rvert-1]$，使得 $s_i=s_{i+1}$，则可以将其替换成 $s_{i-1}$ 或 $s_{i+2}$，然后可以循环以上过程，直到字符串长度为 $1$。因此可以判断字符串中是否有相邻两字符相同，如果有则答案为 $1$，否则答案为字符串的长度。  

### 代码 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
signed main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	while(n--)
	{
		cin>>s;
		bool f=1;
		for(int i=0;i<s.size()-1;i++)
			if(s[i]==s[i+1])
			{
				cout<<"1\n";
				f=0;
				break;
			}
		if(f) cout<<s.size()<<"\n";
	}
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### Analysis
结论：对于字符串 $S$，如果存在 $S_i = S_{i+1}$ 且 $1 \leq i \leq |S| - 1$，则答案为 $1$，否则答案为 $|S|$。

分析：对于每一个 $i$，如果 $S_i = S_{i+1}$，则可以将 $S_i$ 设为 $S_i$ 的前一个字符，或者 $S_{i + 1}$ 的后一个字符。这样，只要字符串中存在 $S_i = S_{i+1}$，则 $S$ 总能只剩下一个字符，故答案为 $1$。否则，字符串 $S$ 不可进行操作，故答案为 $|S|$。
### Code
```cpp
#include <bits/stdc++.h>
int main() {
    int T;
    std::cin >> T;
    while (T --) {
        std::string s;
        std::cin >> s;
        int n = s.size();
        bool f = 0;
        for (int i = 0; i < n - 1; i ++) {
            if (s[i] == s[i + 1]) {
                f = 1;
                break;
            }
        }
        if (f) std::cout << 1 << std::endl;
        else std::cout << n << std::endl;
    }
}
```

---

