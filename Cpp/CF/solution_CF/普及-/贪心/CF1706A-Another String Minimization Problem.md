# Another String Minimization Problem

## 题目描述

You have a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers between $ 1 $ and $ m $ . You also have a string $ s $ , consisting of $ m $ characters B.

You are going to perform the following $ n $ operations.

- At the $ i $ -th ( $ 1 \le i \le n $ ) operation, you replace either the $ a_i $ -th or the $ (m + 1 - a_i) $ -th character of $ s $ with A. You can replace the character at any position multiple times through the operations.

Find the lexicographically smallest string you can get after these operations.

A string $ x $ is lexicographically smaller than a string $ y $ of the same length if and only if in the first position where $ x $ and $ y $ differ, the string $ x $ has a letter that appears earlier in the alphabet than the corresponding letter in $ y $ .

## 说明/提示

In the first test case, the sequence $ a = [1, 1, 3, 1] $ . One of the possible solutions is the following.

- At the $ 1 $ -st operation, you can replace the $ 1 $ -st character of $ s $ with A. After it, $ s $ becomes ABBBB.
- At the $ 2 $ -nd operation, you can replace the $ 5 $ -th character of $ s $ with A (since $ m+1-a_2=5 $ ). After it, $ s $ becomes ABBBA.
- At the $ 3 $ -rd operation, you can replace the $ 3 $ -rd character of $ s $ with A. After it, $ s $ becomes ABABA.
- At the $ 4 $ -th operation, you can replace the $ 1 $ -st character of $ s $ with A. After it, $ s $ remains equal to ABABA.

 The resulting string is ABABA. It is impossible to produce a lexicographically smaller string.In the second test case, you are going to perform only one operation. You can replace either the $ 2 $ -nd character or $ 4 $ -th character of $ s $ with A. You can get strings BABBB and BBBAB after the operation. The string BABBB is the lexicographically smallest among these strings.

In the third test case, the only string you can get is A.

In the fourth test case, you can replace the $ 1 $ -st and $ 2 $ -nd characters of $ s $ with A to get AABB.

In the fifth test case, you can replace the $ 1 $ -st and $ 3 $ -rd characters of $ s $ with A to get ABABBBB.

## 样例 #1

### 输入

```
6
4 5
1 1 3 1
1 5
2
4 1
1 1 1 1
2 4
1 3
2 7
7 5
4 5
5 5 3 5```

### 输出

```
ABABA
BABBB
A
AABB
ABABBBB
ABABA```

# 题解

## 作者：ExplodingKonjac (赞：2)

**[原题链接](https://www.luogu.com.cn/problem/CF1706A)**

## 题目分析

题意：给定一个长度为 $n$ 序列 $a_i$ 以及一个长度为 $m$ 的字符串 $s$，初始时 $s$ 全为 $\mathtt{B}$，第 $i$ 次操作可以把 $s_{a_i}$ 或者 $s_{m-a_i+1}$ 修改为 $\mathtt{A}$。求经过修改后字典序最小的 $s$。

因为我们要使字典序最小，所以要让修改的 $\mathtt{A}$ 尽量靠前。我们依次考虑每个 $a_i$。对于一个 $a_i$，我们可以修改 $a_i$ 或 $m-a_i+1$，我们肯定要优先选择靠前的那个，不妨设靠前的是 $x$。

如果 $s_x=\mathtt{B}$，那么修改这个位置显然是最优的；如果 $s_x=\mathtt{A}$，也就是说这个位置已经被修改过，修改这个位置相当于什么都没做，非常亏，此时选择修改 $m-x+1$ 是一定不会更劣的。那么就做完了。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int T,n,m,a[105];
string s;
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>m;
		s.clear(),s.resize(m,'B');
		for(int i=1;i<=n;i++)
		{
			qin>>a[i],a[i]--;
			if(a[i]>m-a[i]-1) a[i]=m-a[i]-1;
			if(s[a[i]]=='A') a[i]=m-a[i]-1;
			s[a[i]]='A';
		}
		qout.writeln(s);
	}
	return 0;
}
```


---

## 作者：_djc_ (赞：1)

## 题意分析

本题题意是让你求出可以得到的最小字典序。字典序是什么呢？在字典中，单词是按照首字母在字母表中的顺序进行排列的，比如 alpha 在 beta 之前。而第一个字母相同时，会去比较两个单词的第二个字母在字母表中的顺序，依次类推。

由此可见，既然这个字符串只可能由 ```A``` 和 ```B``` 组成，那么想要让字典序尽量小，那么 ```A``` 就要尽量多、尽量排在前面。

那么我们就有了一个贪心策略：将这个序列扫一遍，在 $a_i$ 位置和 $(m + 1 - a_i) $ 位置优先选择一个靠前的，如果这个靠前位置已经选过，那就只能选择另一个位置。

## 代码

贴上代码

```cpp
#include <bits/stdc++.h>
#define maxn 600005
using namespace std;
#define int long long
const int inf = 0x3f3f3f3f;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int T;
signed main() {
	T = read();
	while (T--) {
		int a[100] = {0};
		int c[100] = {0};	//看是否有转成A
		bool vis[100] = { 0 };	//记录此位置是否已经变为A
		int n = read(), m = read();
		for (int i = 1; i <= n; i++) {
			a[i] = read();
        //优先选择位置靠前的
			if (a[i] <= m / 2) {
				if (!vis[a[i]]) vis[a[i]] = 1, c[a[i]] = 1;
				else if (!vis[m + 1 - a[i]]) vis[m + 1 - a[i]] = 1, c[m + 1 - a[i]] = 1;
			}
			else {
				if (!vis[m + 1 - a[i]]) vis[m + 1 - a[i]] = 1, c[m + 1 - a[i]] = 1;
				else if (!vis[a[i]]) vis[a[i]] = 1, c[a[i]] = 1;
			}
		}
		//输出序列
		for (int i = 1; i <= m; i++) {
			if(c[i] == 1) cout << "A";
			else cout << "B";
		}
		cout << endl;
	}
}
```


---

## 作者：Scorilon (赞：0)

### 题意
给定一个长度为 $n$ 的序列 $a$ 以及一个长度为 $m$ 的字符串 $s$，初始 $s$ 均为 $\text{B}$，第 $i$ 次操作可以把 $s_{a_i}$ 或 $s_{m+1-a_i}$ 修改为 $\text{A}$，求修改过后的字典序最小的 $s$。

### 思路
因为要使字典序最小，所以要让 $\text A$ 尽量靠前，所以会出现以下几种情况：

1. 设当前更改位置为第 $i$ 位，若 $s_i$ 和 $s_{m+1-i}$ 位均为 $\text B$，那么 $s_{\min (i,m+1-i)}=\text A$。

2. 设当前更改位置为第 $i$ 位，若 $s_i$ 和 $s_{m+1-i}$ 其中有一位为 $\text A$，那么更改另一位。

那么每次优先考虑 $i$ 和 $m+1-i$ 中更小的那一位进行修改，如果已修改则修改另一位。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
 
using namespace std;
 
int t;
int n,m;
int s[55];
 
int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		memset(s,0,sizeof(s));
		scanf("%d%d",&n,&m);
		int a;
		
		for(register int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			if(s[a]) s[m+1-a]=1;
			else if(s[m+1-a]) s[a]=1;
			else s[min(a,m+1-a)]=1;
		}
		
		for(register int i=1;i<=m;i++)
		{
			if(s[i]==1) printf("A");
			else printf("B");
		}
		
		printf("\n");
	}
	
	return 0;
}
```


---

## 作者：cachejtt (赞：0)

## 题意
给你一个长度为 $m$ 的字符串，初始全为 `B`，再给你一个长度为 $n$ 的序列 $a_i$，每次可以将字符串的正数第 $a_i$ 位或倒数第 $a_i$ 位变为 `A`，问所能得到的字符串中字典序最小的那个。

## 思路
由于 `A` 肯定比 `B` 小，所以 `A` 的位置肯定越靠前越好，所以比较 $a_i$ 与 $m-a_i+1$ 的大小，先取小的那个修改，如果小的位置已经修改过了，就修改后一个位置。

注意到重复修改同一个位置并不会造成问题，因为 `A` 并不会变为 `B`。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
int t,n,m;
int a[55],k,pk;
int main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>m;
    memset(a,0,sizeof(a));
    rep(i,1,n){
      cin>>k;
      pk=min(k,m-k+1);
      if(a[pk]==0)a[pk]=1;
      else a[m-pk+1]=1;
    }
    rep(i,1,m){
      if(a[i])cout<<"A";
      else cout<<"B";
    }
    cout<<"\n";
  }
  return 0;
}
```

---

## 作者：xzy090626 (赞：0)

# CF1706A 题解
## 题意简述
有一个长为 $n$ 的数列 $a$ 和一个长为 $m$，全部为 `B` 的字符串。对于每个 $a_i$，你可以将 $s$ 的第 $a_i$ 位或 $(m+1-a_i)$ 位变为 `A`，求能得到的 $s$ 中字典序最小的一个。
## 题目分析
考虑贪心算法（~~CF 贪心题出得很多~~）。

我们发现，根据字典序的定义，要使 $s$ 的字典序最小，必须要让 `A` 尽可能的多（`A` 肯定排在 `B` 前边），而且由于我们要优先比较最前面的不同的字符，所以要优先修改前面的 `B`。即，修改的越往前越好。

这个贪心思路的正确性是显而易见的，但是有些细节需要考虑。
## 细节
我们能发现，当前面的字符已经被修改为 `A` 后，就没有必要再去修改了。即，不要修改重复的字符。

也就是说，我们每次有两种路径可走，一种是选择修改 $a_i$，一种是修改 $(m+1-a_i)$。

我们可以取出 $\min(a_i,m+1-a_i)$ 和 $\max(a_i,m+1-a_i)$。如果前者还未被修改，那么修改前者。否则，修改后者。这是为了保证修改的机会不被浪费，是很重要的一点。
## 总结方法
遍历 $a$ 数组，每次选出 $\min(a_i,m+1-a_i)$ 和 $\max(a_i,m+1-a_i)$，按照上面的方法进行修改，并开一个 bool 数组进行记录（也可以是 string）。最后按照记录进行输出即可。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define pc putchar
using namespace std;
const int N = 5e5 + 7;
bool s[N];
void solve(){
    memset(s,0,sizeof(s));
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        int a;
        cin>>a;
        int t1 = min(a,m+1-a),t2 = max(a,m+1-a);
        if(s[t1]) s[t2] = 1;
        else s[t1] = 1;
    }
    for(int i=1;i<=m;++i){
        if(s[i]) pc('A');
        else pc('B');
    }
    pc('\n');
}
int main(){
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/80318623)

---
最后，CSP 2022 即将来临，祝我和大家 rp += inf，都能在比赛中取得好的成绩！

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

（呃，我这边视频没挂）

![](bilibili:BV1S94y1Q7zs)

### 2 思路

设 $x=\min(a_i,m-a_i+1)$。很明显，每次操作要么修改 $s_x$ 或 $s_{m-x+1}$。

如果 $s_x$ 还是 `B`，就将其改为 `A`；否则将 $s_{m-x+1}$ 改为 `A`。

因为，字符串的前面的字符对字典序的影响更大，所以应该先改前面的字符。

从贪心的角度来讲，能改前面的就肯定要改前面的字符，如果没必要改前面的，就改后面的字符。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t;
int n;
int m;
int a[52];
char s[52];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1706A_1.in","r",stdin);
	freopen("CF1706A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int i=1;i<=m;++i)s[i]='B';
		for(int i=1,x;i<=n;++i){
			x=min(a[i],m-a[i]+1);
			if(s[x]=='B')s[x]='A';
			else s[m-x+1]='A';
		}
		for(int i=1;i<=m;++i)putchar(s[i]);
		putchar('\n');
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80265552)

By **dengziyue**

---

## 作者：封禁用户 (赞：0)

# 前言

打开 codeforces，仅剩 $30$ 分钟，上来就切掉了这道题。~~（不是我巨，主要是因为太水了）~~

[题目传送门](https://www.luogu.com.cn/problem/CF1706A)

# 正文

本题思路：其实也没啥，就是一个小贪心。我们首先判断一下 $a_i$ 和 $m+1-a_i$ 的最小值，如果这个位置不是 'A'，那么我们就将其设为 'A'，否则我们将上面这两个中的最大值设为 'A'。

以上就是本题的策略，给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int a[N];
int t,n,m;
bool vis[N];
int main(){
	cin>>t;
	while(t--){//多组测试数据
		cin>>n>>m;
		string tmp;
		for(int i=1;i<=m;i++){
			tmp[i]='B';//字符串一开始全是B
		}
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			int mx=max(a[i],m+1-a[i]);//最小值（最优情况）
			int mn=min(a[i],m+1-a[i]);//最大值（次优情况）
			if(!vis[mn]){//如果没有被访问过
				vis[mn]=true;
				tmp[mn]='A';
			}else{//否则只能选择次优方案
				tmp[mx]='A';
			}
		}
		for(int i=1;i<=m;i++){
			cout<<tmp[i];
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：sw2022 (赞：0)

## 题意简析

给定一个序列 $a\ (|a|=n,n>0)$ 和一个长度为 $m$ 的字符串 $s$（全部由 `B` 组成），定义一次操作 $i$ 为选择 $a_i$ 和 $(m+1-a_i)$ 中的一个，把 $s$ 在这个位置上的字符替换成 `A`。问从 $1$ 到 $n$ 进行操作 $i$，能得到字典序最小的字符串。

考虑贪心思想，每次计算出 $a_i$ 和 $(m+1-a_i)$，然后看 $s$ 中小的位置有没有被替换成 `A`。如果没有就替换，否则替换大的位置。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,m,a,i;
    cin>>t;
    while(t--)
    {
        string s="";//初始化字符串为空（srds，好像不初始化也是空的）
        cin>>n>>m;
        for(i=0;i<m;i++)
        s+='B';//赋值字符串
        for(i=0;i<n;i++)
        {
            cin>>a;
            pair<int,int> b=minmax(a-1,m-a);//minmax返回两个数的较小值(.first)和较大值(.second)
            if(s[b.first]=='B')
            s[b.first]='A';//替换较小位置
            else s[b.second]='A';//替换较大位置
        }
        cout<<s<<endl;
    }
    return 0;    
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

可以发现，将一个字符从 `B`  变成 `A`，一定可以使字符串的字典序更小。所以，如果能变，一定要变。

可以发现，每次操作有机会变 $2$ 个字符中的 $1$ 个，而这一个，应该尽量选择更靠前的那个，这样可以让字典序更小。

了解上面两条，就可以写代码了。

### 二、代码

```
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n,m;
char s[55];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			s[i]='B';
		}
		s[m+1]='\0';
		for(int i=1,x;i<=n;i++)
		{
			scanf("%d",&x);
			if(s[min(x,m-x+1)]=='B')//如果最小的那个是B，则变成A。
			{
				s[min(x,m-x+1)]='A';
			}
			else//否则变最大的那个。
			{
				s[max(x,m-x+1)]='A';
			}
		}
		printf("%s\n",s+1);
	}
	return 0;
}

```


---

## 作者：Jeremiahy (赞：0)

## 题意

给你一个长度为 $n$ 的数列 $a$，初始有一个长度为 $m$ 的字符串，初始全为 B，进行 $n$ 次操作，每次操作你可以选择将字符串里第 $a_i$ 位或者第 $m+1-a_i$ 位改为 A，问字典序最小的字符串。

# 分析

很容易想到一种贪心策略：优先改前面的，前面已经改了就该后面的。

证明很容易，字典序是从前往后依次比较的，在前面字典序越小，整个字符串的字典序越小。

在具体实现中，可以用 $c$ 数组记录当前字符种类（$0$ 为 B，$1$ 为 A），每次只读一个 $a$（这样不用开 $a$ 数组了，节省空间），接下来判断 $a_i$ 与 $m+1-a_i$ 是否用过，用过就选另一个，否则 $a_i$ 与 $m+1-a_i$ 哪个小选哪个。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;   
int t, n, m, a, c[1010];
signed main () {
	cin >> t;
	while (t--) {
		memset(c, 0, sizeof(c));//初始化为全 B 
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			cin >> a;
			if (c[a])//如果已经被改了
				c[m + 1 - a] = 1;
			else if (c[m + 1 - a])//同上
				c[a] = 1;
			else {
				if (a > m + 1 - a)//选小的
					c[m + 1 - a] = 1;
				else	
					c[a] = 1;
			}
		}
		for (int i = 1; i <= m; i++)
			cout << ((c[i] == 1) ? 'A' : 'B');
		puts("");
	}
	return 0;
}
```


---

