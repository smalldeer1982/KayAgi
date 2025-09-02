# Non-Substring Subsequence

## 题目描述

Hr0d1y has $ q $ queries on a binary string $ s $ of length $ n $ . A binary string is a string containing only characters '0' and '1'.

A query is described by a pair of integers $ l_i $ , $ r_i $ $ (1 \leq l_i \lt r_i \leq n) $ .

For each query, he has to determine whether there exists a good subsequence in $ s $ that is equal to the substring $ s[l_i\ldots r_i] $ .

- A substring $ s[i\ldots j] $ of a string $ s $ is the string formed by characters $ s_i s_{i+1} \ldots s_j $ .
- String $ a $ is said to be a subsequence of string $ b $ if $ a $ can be obtained from $ b $ by deleting some characters without changing the order of the remaining characters.
- A subsequence is said to be good if it is not contiguous and has length $ \ge 2 $ . For example, if $ s $ is "1100110", then the subsequences $ s_1s_2s_4 $ ("1100110") and $ s_1s_5s_7 $ ("1100110") are good, while $ s_1s_2s_3 $ ("1100110") is not good.

Can you help Hr0d1y answer each query?

## 说明/提示

In the first test case,

- $ s[2\ldots 4] =  $ "010". In this case $ s_1s_3s_5 $ ("001000") and $ s_2s_3s_6 $ ("001000") are good suitable subsequences, while $ s_2s_3s_4 $ ("001000") is not good.
- $ s[1\ldots 3] =  $ "001". No suitable good subsequence exists.
- $ s[3\ldots 5] =  $ "100". Here $ s_3s_5s_6 $ ("001000") is a suitable good subsequence.

## 样例 #1

### 输入

```
2
6 3
001000
2 4
1 3
3 5
4 2
1111
1 4
2 3```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：Kohakuwu (赞：5)

## 题意

给定一个01串 $\text{s}$，若干询问。要求询问的区间 $\text{s}_{l...r}$ 必须能被拆分成若干连续区间。

#### 注意！$\text{s}$ 的下标从1开始哦！

## 解题时的想法

由此我想到了最优原则，中间的部分 $\text{s}_2$ 至 $\text{s}_{n-1}$ 部分不动，只向左移动 $\text{s}_1$ 并且向右移动 $\text{s}_n$ 即可！

那么代码大致思路就是读入区间，将 $\text{s}$ 左侧部分判断是否有与 $\text{s}_1$ 相同的，右侧亦然。

## AC CODE

```cpp
#include<iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int m,n;
		cin>>m>>n;
		string str;
		cin>>str;
		for(int i=1;i<=n;i++)
		{
			int a,b;
			cin>>a>>b;
			a--;b--;
			bool aif=false,bif=false;
			for(int i=0;i<str.length();i++)
			{
				if(str[i]==str[a]&&i<a)aif=true;
				if(str[i]==str[b]&&i>b)bif=true;
			}
			if(!aif&&!bif)cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}
}
```


---

## 作者：henrytb (赞：1)

$s_{l\ldots r}$ 这么长一段能匹配，但是连续，可惜了。

于是我们可以考虑对这一段的首位往左移，末位往右移。

设当前首位往左移到了 $s_x$。

则若 $s_x=s_l$，那么 $s_xs_{l+1\ldots r}$ 这个子序列就是符合要求的。

末位向右移也类似。

最后只要有符合要求的，就可以输出 `YES`，否则输出 `NO`。

详细见代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,q;
char s[105];
int main(){
    for(scanf("%d",&_);_;--_) {
        scanf("%d%d",&n,&q);
        scanf("%s",s+1);
        int i,j;
        rep(__,1,q) {
            int l,r;
            scanf("%d%d",&l,&r);
            bool flg=0,flg2=0;
            per(i,l-1,1) if(s[l]==s[i]) flg=1;
            rep(i,r+1,n) if(s[r]==s[i]) flg2=1;
            if(flg||flg2) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题目描述

[Non-Substring Subsequence](https://www.luogu.com.cn/problem/CF1451B)

## 题意

问你是否有一个不同的子序列和给定的子序列相同。

# 算法思路

我们只要把第 $l$ 位往左移，或者把第 $r$ 为往右移。

因为如果第 $l$ 位往左移首位移到了第 $i$ 位，而且 $s_i = s_l$，那么 $s_xs_{l+1} \ldots s_r$ 是合法的。

第 $r$ 为往右移也是如此。

最后只要有符合要求的，就输出 ```YES```，否则就输出 ```NO```。

### 时间复杂度：$O(t \times q \times n)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=110;
ll t,n,q,a[N],x,y;
bool flag;//flag表示有没有 
string s;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>t;
	while(t--)//t组数据 
	{
		cin>>n>>q;
		cin>>s;
		for(int i=1;i<=q;i++)//q个询问 
		{
			cin>>x>>y;
			x--;
			y--;
			flag=false;//初始设为不行 
			for(int i=0;i<n;i++)
			{
				if(s[x]==s[i]&&i<x||s[y]==s[i]&&i>y)//如果前面有和s[x]一样的数或者后面有和s[y]一样的数
				{
					flag=true;//可以 
					break;
				}
			}
			if(flag)
			{
				cout<<"YES\n";//有 
			}
			else
			{
				cout<<"NO\n";//没有 
			}
		}
	}
	return 0;
}
```


---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1451B)

### [题意解析]
给你 $n$ 个 二进制序列 $s$，其实就是一个字符串 $s$。有 $q$ 次询问，求是否存在不同的子序列 $s[l_i,r_i]$ 相同。
+ 存在输出 $\verb!YES!$。
+ 否则输出 $\verb!NO!$。

### [思路分析]
题目的意思十分清晰，就是要求子序列 $s[l_i,r_i]$ 是否相同，不存在什么~~高深的算法~~，我们只接按题目说的模拟就好了，我们只用 $q$ 次循环查找每次的 $l∼ r$ 就好了。

### [贴上代码]
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,q,l,r;
char s[100010];
int main()
{
	cin>>T;
	while(T--){
		cin>>n>>q>>(s + 1);
		for(int i= 1; i<= q; i++){
			/*q 次询问*/
			cin>>l>>r;
			bool flag = 0;/*标记*/
			for(int j= 1; j< l; j++)
				if(s[j] == s[l])flag = 1;
			/*l的区间*/
			for(int j= r+1; j<= n; j++)
				if(s[j] == s[r])flag = 1;
			/*r的区间*/
			if(flag)cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```


---

## 作者：Ybocean_s (赞：0)

重新翻译题目：给定数目的样例，给出字符串长度，查询次数，和字符串内容，每次查询输入两个数为查询的字符串在这两个数区间中两个边。

查询规则：查找一个序列和查询信息的首尾相同的子序列。

方法：为保证不与查询信息重合，从序列两个边往外查询，即从左查询是否存在首元素或往右查询是否存在尾元素。

```cpp
#include<iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--){//样例。
		string s;
		int a,b,l,r;
		cin>>a>>b>>s;//每组信息。
		s=" "+s;//从1开始找。
		while(b--){
			cin>>l>>r;
			int f=0;
			for(int i=1;i<l;i++){//区间寻找。
				if(s[i]==s[l]){
					f=1;
				}
			}
			for(int i=r+1;i<=a;i++){//区间寻找。
				if(s[i]==s[r]){
					f=1;
				}
			}
			if(f){
				cout<<"YES"<<endl;
			}else{
				cout<<"NO"<<endl;
			}//判断输出。
		}
	}
	return 0;
}
```
撒花。

---

## 作者：wsyhb (赞：0)

## 题意简述

共 $t$ 组数据，每组数据给出一个长度为 $n$ 的 01 字符串 $s$，以及 $q$ 个询问，每个询问形如 `l r`，表示求是否存在一个子序列同时满足下列两个条件：

1. 该子序列不连续，也就是不为子串

2. 该子序列与子串 $s[l]s[l+1] \cdots s[r]$ 完全相同

**数据范围**：$1 \le t \le 100$，$2 \le n \le 100$，$1 \le q \le 100$

## 解法一

首先，如果没有要求子序列不连续，我们可以贪心解决——

只需从左到右逐一匹配，只要相同就进行匹配，看最后是否匹配完即可。

由此我们可以得出一个较为朴素的暴力做法——

枚举哪两个字符不连续，相当于在这之间加上一个通配符（可匹配 `0`，也可匹配 `1`），再按照上述贪心策略实现即可。时间复杂度 $O(tqn^2)$。

## 解法二

换一种思路，先考虑一些简单的构造：

1. 若存在 $i$ 使得 $1 \le i<l$ 且 $s[i]=s[l]$，那么 $s[i],s[l+1],s[l+2],\cdots,s[r]$ 是一个满足题意的子序列。
2. 类似地，若存在 $i$ 使得 $r<i \le n$ 且 $s[i]=s[r]$，那么 $s[l],\cdots,s[r-2],s[r-1],s[i]$ 是一个满足题意的子序列。

如果没有上述两种情况呢？手玩几组发现似乎怎么都不存在满足题意的子序列。**下面就证明，当上述两个条件均不成立时，没有满足题意的子序列。**

（反证）在上述两个条件均不成立的前提下，假设存在满足题意的子序列，其首个元素的下标为 $a$，最后一个元素的下标为 $b$。由上述两个条件不成立知，$a \ge l$ 且 $b \le r$；由子序列长度与子串长度 $r-l+1$ 相等知，$b-a+1 \ge r-l+1$。因此，$a=l$ 且 $b=r$，即该子序列就是子串 $[l,r]$，矛盾，证毕。

所以判断一下就好啦~ 时间复杂度 $O(tqn)$。

## 代码

### 解法一

该代码中搜索的本质即为解法一。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
const int max_n=100+5;
char s[max_n];
vector<int> now;
bool flag_ans;
void dfs(int x,int k,int tot)
{
	if(k==now.size())
	{
		if(tot>0)
			flag_ans=true;
		return;
	}
	if(x>n||k+(n-x+1)<now.size())
		return;
	if(s[x]==now[k])
	{
		dfs(x+1,k+1,tot);
		if(flag_ans)
			return;
		if(tot==0)
			dfs(x+1,k,tot+1);
	}
	else
		dfs(x+1,k,tot+(k>0?1:0));
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%s",&n,&q,s+1);
		while(q--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			now.clear();
			for(int i=l;i<=r;++i)
				now.push_back(s[i]);
			flag_ans=false;
			dfs(1,0,0);
			if(flag_ans)
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}
```

### 解法二

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=100+5;
char s[max_n];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,q;
		scanf("%d%d%s",&n,&q,s+1);
		while(q--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			bool flag=false;
			for(int i=1;i<l&&!flag;++i)
			{
				if(s[i]==s[l])
					flag=true;
			}
			for(int i=r+1;i<=n&&!flag;++i)
			{
				if(s[i]==s[r])
					flag=true;
			}
			puts(flag?"YES":"NO");
		}
	}
	return 0;
}
```


---

## 作者：shihoghmean (赞：0)

## 题意

给定一个$01$串$s$，以及$q$组$l$和$r$。

问在$01$串是否存在一个不同的子串与$s$[$l_i$,$r_i$]相同。

## 思路

不同的子串只需要有一个位置不同即可。对于$s$[$l_i$,$r_i$]，只考虑这个连续子串的左右端点，如果在$l_i$左边有等于$s$[$j_i$]的位置，则将$j_i$移到那个位置即可。扫右端点也是一样。

若完全没有一个子串与$s$[$l_i$,$r_i$]相同，仅且仅当左右都没搜不到相等的点。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,q;
int sum[101]; 
char s[101];
inline int read(){
	int x=0,k=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') k=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*=k;
}
int main(){
	t=read();
	while(t--){
		n=read();q=read();
		cin>>(s+1);
		int len=strlen(s+1);
		while(q--){
			int b=0;
			int l=read(),r=read();
			if(l==r){
				printf("NO\n");
				continue;
			}
			for(int i=1;i<l;i++){//扫左侧
				if(s[i]==s[l]){//若有，直接输出YES
					printf("YES\n");
					b=1;
					break;
				}
			}
			if(b) continue;
			for(int i=r+1;i<=n;i++){//扫右侧
				if(s[i]==s[r]){
					printf("YES\n");
					b=1;
					break;
				}
			}
			if(b) continue;
			printf("NO\n"); //若两边都没有，则输出NO
		}
	}
	return 0;
}

---

## 作者：stdout (赞：0)

~~蒟蒻第二次打cf，讲的不清楚的地方欢迎提出~~      
$\large\texttt{Statement}$    
给您一个长度为$n$二进制序列$s$，有$q$次询问，第$i$组询问包含两个数$l_i$和$r_i$   
求是否存在一个不同的子序列和子序列$s[l_i,r_i]$相同    
$t$组数据  
$1\leq t\leq 1000 \quad 2\leq n\leq 100 \quad 1\leq q \leq 100 \quad 1\leq l_i < r_i \leq n$

$\large\texttt{Solution}$   
经过观察就可以发现，只需要满足以下**任一**条件即可：

- $s[1,l_i-1]$中任一元素和$s[l_i]$相同
- $s[r_i+1,n]$中任一元素和$s[r_i]$相同

注意下标是从1开始的

$\large\texttt{Code}$      
```cpp
//Author: stdout_cout 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define debug(x) cerr<<#x<<" = "<<x<<"\n";
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
#define lowbit(x) ((x)&-(x))
const int inf=0x3f3f3f3f;
const double eps=1e-9;
//const double pi=acos(-1.0); 
//const int maxn=1e5+5;
void solve() {
	int n,q;
	string s;
	cin>>n>>q>>s;
	for(int i=1;i<=q;++i) {
		int l,r;
		cin>>l>>r;
		--l,--r;
		for(int i=r+1;i<s.size();++i)
			if(s[i]==s[r]) {
				cout<<"YES\n";
				goto end;
			}
		for(int i=0;i<l;++i)
			if(s[i]==s[l]) {
				cout<<"YES\n";
				goto end;
			}
		cout<<"NO\n";
		end: ;
	}
}
int main() {
	ios::sync_with_stdio(false);
	//cin.tie(nullptr);cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--) {
		solve();
	} 
	return 0;
} 


```


---

## 作者：Tarsal (赞：0)

## 题目大意

给你一个长度为 $n$ $0/1$ 字符串，以及 $m$ 个询问。

每个询问会告诉你一个 $l, r$。

问你在原字符串中有没有一个子序列和子串 $s_l \to s_r$ 一样。

## 题解

你考虑只改变首或者尾，看能不能找到符合要求的子序列。

我们来验证，如果首 & 尾都无法找到一样的替代。

那么你也不能找到和首/尾 $2$ 位一样的去替代，因为第一位都没有一样的了。

反之，如果你可以找到一个字符去代替首/尾，那么他已经是一个和原串相同的子序列了。

至于怎么找，就只要记录下前面第一次出现 $0/1$ 的位置，记录下后面第一次出现 $0/1$ 的位置。

然后判断下就行了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i; i = edge[i].nxt)
int read() {
    char c = getchar(); int f = 1, x = 0;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
char s[101];
signed main() {
	int T = read();
	while(T --) {
		int n = read(), q = read(), pla = 0, pla2 = 0, Pla = 0, Pla2 = 0;
		Rep(i, 1, n) {
			scanf("%c", &s[i]);
			if(s[i] == '0' && pla == 0) pla = i;
			else if(s[i] == '1' && pla2 == 0) pla2 = i;
		}
		Dep(i, n, 1) {
			if(s[i] == '0' && Pla == 0) Pla = i;
			else if(s[i] == '1' && Pla2 == 0) Pla2 = i;
		}
		Rep(i, 1, q) {
			int flag = 0, l = read(), r = read();
			if(s[l] == '0' && pla < l) flag = 1;
			if(s[r] == '0' && Pla > r) flag = 1;
			if(s[r] == '1' && Pla2 > r) flag = 1;
			if(s[l] == '1' && pla2 < l) flag = 1;
			if(flag) puts("YES"); else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：LRL65 (赞：0)

这题还是比较良心的。

#### 题意：
在字符串 $S$ 中，给两个数 $l,r$ ，问 是否有不连续的字串等于$S_l,S_{l+1},……S_r$。

#### 思路：

算是一个贪心吧，他只要不连续就行，那么我们只要动第一个或者最后一个。那么预处理从前面和后面分别扫是否有0，1。然后只需判断 $l$ 前是否有和 $S_l$ 一样的字符，或者 $r$ 后是否有和 $S_r$ 一样的字符即可。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,q,l,r;
int main() {
    cin>>t;
    while(t--) {
        string s;
        cin>>n>>q;
        cin>>s;
        bool flag1[2][105],flag2[2][105];//flag1从前面扫,flag2从后面扫
        memset(flag1,0,sizeof(flag1));//记得初始化
        memset(flag2,0,sizeof(flag2));
        for(int i=1;i<=n;i++) {
            flag1[0][i]=flag1[0][i-1];flag1[1][i]=flag1[1][i-1];
            if(s[i-1]=='0')flag1[0][i]=1;
            else flag1[1][i]=1;
        }
        for(int i=n;i>=1;i--) {
            flag2[0][i]=flag2[0][i+1];flag2[1][i]=flag2[1][i+1];
            if(s[i-1]=='0')flag2[0][i]=1;
            else flag2[1][i]=1;
        }
        for(int i=1;i<=q;i++) {
            cin>>l>>r;
            if(flag1[s[l-1]-'0'][l-1]==1||flag2[s[r-1]-'0'][r+1]==1)cout<<"YES"<<endl;//直接判断
            else cout<<"NO"<<endl;
        }
    }
}
```


---

## 作者：PvbeLLN (赞：0)

## CF1451B
### 分析
注意到数据范围很小，所以暴力枚举是可行的。

由于子序列不要求连续，所以可以借鉴“贪心”的思路，即每次判断是否存在与 $s[l]\sim s[r]$ 相同的子序列时，假设存在满足要求的子序列 $X$，则可以将 $X$ 的后 $r-l$ 项（即除了 $X[0]$ 以外的项）看作与 $s[l+1]\sim s[r]$ 重叠，那么只需要在 $s[0]\sim s[l-1]$ 中寻找是否存在与 $X[0]$ 相同的字符即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,l,r,T;
string s;
bool f;    //标记是否找到符合要求的子序列 

int main()
{
	cin>>T;
	while (T--)
	{
		cin>>n>>q>>s;
		while (q--)
		{
			cin>>l>>r;
			l--;r--;     //题目中的s的下标是从1开始的 
			f=0;
			for (int i=0;i<l;i++) if (s[i]==s[l]) {f=1; break; }     //其实不加break优化也能过 
			if (!f)
				for (int i=r+1;i<n;i++) if (s[i]==s[r]) {f=1; break; }
			if (f) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```


---

