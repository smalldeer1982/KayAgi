# Color with Occurrences

## 题目描述

You are given some text $ t $ and a set of $ n $ strings $ s_1, s_2, \dots, s_n $ .

In one step, you can choose any occurrence of any string $ s_i $ in the text $ t $ and color the corresponding characters of the text in red. For example, if $ t=\texttt{bababa} $ and $ s_1=\texttt{ba} $ , $ s_2=\texttt{aba} $ , you can get $ t=\color{red}{\texttt{ba}}\texttt{baba} $ , $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ or $ t=\texttt{bab}\color{red}{\texttt{aba}} $ in one step.

You want to color all the letters of the text $ t $ in red. When you color a letter in red again, it stays red.

In the example above, three steps are enough:

- Let's color $ t[2 \dots 4]=s_2=\texttt{aba} $ in red, we get $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ ;
- Let's color $ t[1 \dots 2]=s_1=\texttt{ba} $ in red, we get $ t=\color{red}{\texttt{baba}}\texttt{ba} $ ;
- Let's color $ t[4 \dots 6]=s_2=\texttt{aba} $ in red, we get $ t=\color{red}{\texttt{bababa}} $ .

Each string $ s_i $ can be applied any number of times (or not at all). Occurrences for coloring can intersect arbitrarily.

Determine the minimum number of steps needed to color all letters $ t $ in red and how to do it. If it is impossible to color all letters of the text $ t $ in red, output -1.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is impossible to color all the letters of the text in red.

## 样例 #1

### 输入

```
6
bababa
2
ba
aba
caba
2
bac
acab
abacabaca
3
aba
bac
aca
baca
3
a
c
b
codeforces
4
def
code
efo
forces
aaaabbbbcccceeee
4
eeee
cccc
aaaa
bbbb```

### 输出

```
3
2 2
1 1
2 4
-1
4
1 1
2 6
3 3
3 7
4
3 1
1 2
2 3
1 4
2
4 5
2 1
4
3 1
4 5
2 9
1 13```

# 题解

## 作者：Tx_Lcy (赞：14)

[题目传送门](https://www.luogu.com.cn/problem/CF1714D)
## 思路
这是一道基础的 $\verb!DP!$，不妨设 $f_i$ 为把前 $i$ 个字符染成红色所需的最小代价，转移就直接找一个字符串接到 $i$ 前面，然后暴力枚举转移。又因为题目要求记录方案，所以在转移的时候要记录一个 $pre_i$ 数组表示 $i$ 是从 $pre_i$ 转移过来的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e2+10;
int f[N],pre[N];
string t[N];
pair<int,int>a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while (T--){
		string s;cin>>s;
		int n=s.length();s=" "+s;
		int k;cin>>k;
		for (int i=1;i<=k;++i) cin>>t[i];
	    memset(f,0x3f,sizeof(f));
		f[0]=0;int maxn=f[1];
		for (int i=1;i<=n;++i)
			for (int j=1;j<=k;++j)
			    if (i>=t[j].length()){
			    	if (s.substr(i-t[j].length()+1,t[j].length())==t[j])
						for (int l=(int)(i-t[j].length());l<i;++l)
							if (f[l]+1<f[i]){
								f[i]=f[l]+1;
								pre[i]=l;
								a[i]={i-t[j].length()+1,j};
							}
				}
		if (f[n]==maxn) cout<<"-1\n";
		else{
			cout<<f[n]<<'\n';
			int now=n;
			while (now) cout<<a[now].second<<' '<<a[now].first<<'\n',now=pre[now];
		}
	}
	return 0;
}
```


---

## 作者：__KrNalty__ (赞：5)

看不懂其他几位巨佬讲的，于是想要把自己的方法分享给大家，思路可能比较清晰。

### 题意简述：

给定一段黑色字符串 $t$ 和其他 $n$ 个字符串 $s_1,s_2,\dots,s_n$。

一次操作可以将 $t$ 中任意一个与任意 $s$ 相等的子串涂成红色。两次涂红的字母仍然是红色。$s$ 没有使用次数限制。求全涂成红色最小次数和方案，如果有多种可能的方案，任意输出一种。

### 思路分析：

不会 dp，但是赛时一秒想出思路。

很简单，因为所有的 $s$ 没有使用次数限制，所以可以直接对所有的 $s$ 跑一遍 $t$，记录所有 $t$ 中能放每一个 $s$ 的位置。最后就是一个区间覆盖问题（即求最少使用多少条线段可以将整个区间完全覆盖），因为刚学过 [P1514 引水入城](https://www.luogu.com.cn/problem/P1514) 的区间覆盖，所以很快就写出来了。

#### 对于区间覆盖问题的解题方法：

需要最少的线段进行覆盖，那么选取的线段必然要尽量长，而已经覆盖到的区域之前的地方已经无所谓了，（可以理解成所有的可以覆盖的左端点都是已经覆盖到的地方），那么真正能够使得线段更成的是右端点，左端点没有太大的意义，所以选择右端点来覆盖。

### 完整代码供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e4 + 5;
int n, l[maxn], r[maxn], use[maxn];
string t, s;
signed main() {
	int T = 1;
	cin >> T;
	while (T--) {
		cin >> t >> n;
		int len = t.size();
		t = " " + t;
		memset(l, 0, sizeof l);
		memset(r, 0, sizeof r);
		memset(use, 0, sizeof use);
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			cin >> s;
			for (int j = 1; j <= len - s.size() + 1; j++) {
				string tmp = t.substr(j, s.size());
				if (tmp == s) {
					l[++cnt] = j;
					r[cnt] = j + s.size() - 1;
					use[cnt] = i; // 记录
				}
			}
		}
		int left = 1, right = 0, ans = 0, flag = 0;
		vector<int> anss;
		while (left <= len) { // 区间覆盖
			int pos = 0;
			for (int i = 1; i <= cnt; i++) {
				if (l[i] <= left) {
					if (r[i] > right) {
						right = r[i];
						pos = i;
					}
				}
			}
			anss.push_back(pos);
			left = right + 1;
			ans++;
			if (ans >= cnt + 100) { // 这里想了很久，如果当前的数量已经比线段的条数大的多，就说明当前已经陷入死循环了，直接输出 -1 跳出即可
				flag = 1;
				cout << -1 << endl;
				break;
			}
		}
		if (!flag) {
			cout << ans << endl;
			for (int i = 0; i < anss.size(); i++) {
				cout << use[anss[i]] << " " << l[anss[i]] << endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：蒟蒻炒扇贝 (赞：4)

~~感觉这题的 dp 解法比贪心好想多了。~~

------------

设 $f_i$ 为将 $t_0$ 至 $t_{i-1}$ 这一段子串全部染成红色的最小步数。

边界条件便是 $f_0=0$，当 $t$ 中的字符都没有被染色时，所需的步数为 $0$。

如果我们设 $i$ 为起点，$to$ 为我们可以从 $i$ 转移到的终点的话，那么状态转移方程如下。

$f_{to}=\min(f_{to},f_i+1)$

问题就在于我们如何找到合法的几对 $i$ 和 $to$。

我们可以先枚举 $i$，再枚举出所有可以以 $t_{i}$ 为左端点，可以匹配到右端点的字符串 $s_j$。设 $s_j$ 的长度为 $|s_j|$，那么上文中的 $to$ 的取值便为 $[i+1,i+|s_j|]$。因为如果我们在这里取到 $s_j$ 的话，那么 $t_{i}$ 至 $t_{i+|s_j|-1}$ 的所有字符便都能被染色。

枚举 $i$ 的复杂度为 $\mathop{O(|t|)}$，枚举 $s_j$ 的复杂度为 $\mathop{O(n)}$，判断能否匹配的复杂度为 $\mathop{O(|s|)}$，转移的复杂度为 $\mathop{O(|s|)}$，对于每组讯问，总时间复杂度为 $\mathop{O(n|t||s|^2)}$，可以通过本题。

然而这一道题还让我们输出方案，我们可以考虑开一个前驱数组 $lst$，记录目前的状态是从哪里转移过来的，在 dp 之后我们便可以利用这个前驱数组来找到方案。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pir pair<int,int>
#define fs first
#define sc second
string s[105],t;
int T,n,f[105];//f_i表示将t_0~i-1全部染色的最小步数
pir lst[105];
int check(int i,int j)//i为t的左端，j为要进行判断的字符串编号 
{
	for(int k=0;k<s[j].size();k++)if(s[j][k]!=t[i+k])return false;
	return true;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>t;
		cin>>n;
		getchar();
		for(int i=1;i<=n;i++)cin>>s[i];
		for(int i=1;i<=t.size();i++)f[i]=1e9,lst[i].fs=lst[i].sc=0;
		f[0]=0;
		for(int i=0;i<t.size();i++)
		 for(int j=1;j<=n;j++)
		 	if(check(i,j))
		 	{
		 		for(int k=1;k<=s[j].size();k++)if(f[i+k]>=f[i]+1)
				 {
				 	f[i+k]=min(f[i+k],f[i]+1);
				 	lst[i+k].sc=i;
				 	lst[i+k].fs=j;
				 }
			}
		if(f[t.size()]==1e9)
		{
			cout<<-1<<endl;
			continue;
		}
		int now=t.size();
		vector<pir>ans;
		while(now)
		{
			ans.push_back(pir(lst[now].fs,lst[now].sc));
			now=lst[now].sc;
		}
		cout<<ans.size()<<endl;
		for(auto x:ans)cout<<x.fs<<" "<<x.sc+1<<endl;
	}
}
```
感谢阅读！

---

## 作者：3a51_ (赞：3)

赛时很多人暴力乱搞过的，所以来一发 dp 题解。

----

设 $dp_{i,j}$ 表示 最后一次用 $s_j$ 去覆盖 $t$ 的前 $i$ 个字符的最小次数。（$s_j$ 必须从末尾往前覆盖）

不难发现，再上一次的覆盖的末尾必须是这次覆盖的任意位置 $-1$。

举个例子：

原串为：$\texttt{ababaa}$

当前字符串为：$\texttt{aba}$

假设当前从位置 $3$ 开始覆盖，那么原串覆盖位置就是（用红色标出）：

$\texttt{ab\color{red}aba}\texttt{a}$

那么上一次的末尾位置可能为（用绿色标出）：

$\texttt{a\color{lightgreen}bab}\texttt{aa}$

所以做转移时去枚举上次的末尾、上次用哪个字符串，总共时间复杂度 $O(n^2|t|^2)$。

注意最后还要记录一下答案路径。此题就做完了。

赛时代码：[link](https://codeforces.com/contest/1714/submission/166571632)

---

## 作者：Dr_Gilbert (赞：2)

# CF1714D Color with Occurrences

【题目大意】给定一个字符串 $t$ 和 $n$ 个模板串 $s_i$，若 $s_i$ 和 $t$ 的某个子串 $t[l\ldots r]$ 相等，则可以花费 $1$ 的代价将这个子串染色，同一段可以被染色多次。求最小代价和方案，或者报告无解。

$q(q\le 100)$ 组数据，对于每组数据 $|t|\le 100$，$n\le 10$，$|s_i|\le 10$。

---

由于同一段可以被染色多次，所以最小代价和顺序无关。可以想到动态规划，设 $dp[i]$ 为将 $t$ 的前 $i$ 个字符都染色的最小代价。考虑如何进行转移，不妨预处理出 $len_j$ 表示 $s_j$ 的长度， $match[i][j]$ 表示 $s_j$ 能否匹配字符串 $t$ 中以位置 $i$ 结尾，长度为 $len_{j}$ 的子串。这样就很好转移，对于每个位置 $i$，考虑每个能够匹配的 $s_j$，对于每个 $s_j$，从 $[i-len_j,i]$ 区间内转移。注意：由于染色区间可以不交，所以左端点为 $i-len_j$ 而不是 $i-len_j+1$。由此得到状态转移方程如下：
$$
dp[i]=\min_{match[i][j]=1} \{\min_{k=i-len_j}^i dp[k]+1\}
$$
在转移的同时记录 $from[i]$ 和 $type[i]$ 数组，记录转移到 $i$ 的状态的染色终点（即方程中的 $k$）和染色时使用的模板串编号（即方程中的 $j$）。

注意 $dp$ 数组初值应为正无穷，若转移完后 $dp[n]=\infty$，则报告无解，否则使用记录的 $from[i]$ 和 $type[i]$ 递归输出方案即可。单组数据时间复杂度 $\mathcal O(|t|\sum|s_i|)$，可以通过。参考代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int dp[N],from[N],ok[N][N];
int len[N],type[N];string s;
void print(int n){
    if (n==0) return;print(from[n]);
    cout<<type[n]<<' '<<n-len[type[n]]+1<<endl;
    return;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);cout.tie(nullptr);
    int t;cin>>t;
    while (t--){
        cin>>s;int n=s.length();
        s='0'+s;memset(dp,0x3f,sizeof(dp));
        memset(from,0,sizeof(from));
        memset(ok,0,sizeof(ok));
        int m;cin>>m;
        for (int i=1;i<=m;i++){
            string q;cin>>q;len[i]=q.length();
            for (int j=len[i];j<=n;j++){
                if (s.substr(j-len[i]+1,len[i])==q){
                    ok[j][i]=1;
                }
            }
        }dp[0]=0;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
                if (!ok[i][j]) continue;
                for (int k=i-len[j];k<i;k++){
                    if (dp[k]+1<dp[i]){
                        from[i]=k;type[i]=j;
                        dp[i]=dp[k]+1;
                    }
                }
            }
        }
        if (dp[n]==0x3f3f3f3f) cout<<-1<<endl;
        else{
            cout<<dp[n]<<endl;print(n);
        }
    }
    return 0;
}
```

---

## 作者：Error_Eric (赞：2)

#### 题意

给定一段黑色文本 $t$ 和多个字符串 $s_1,s_2...s_n$。

一次操作可以将 $t$ 中任意一个与任意 $s$ 相等的子串涂成红色。两次涂红的字母仍然是红色。$s$ 没有使用次数限制。求全涂成红色最小次数和方案，任意输出一种解。

一共有 $q$ 组测试数据。

举例：

 $ t=\texttt{bababa} \ \  s_1=\texttt{ba} $ , $ s_2=\texttt{aba} $ 
 
 一步可以得到 $ t=\color{red}{\texttt{ba}}\color{black}\texttt{baba} $ , $ t=\texttt{b}\color{red}{\texttt{aba}}\color{black}\texttt{ba} $ or $ t=\texttt{bab}\color{red}{\texttt{aba}} $ 中的一个。
 
 全部涂黑所需 $3$ 步如下：
 
 - 涂红 $ t[2 \dots 4]=s_2=\texttt{aba} $ 得 $ t=\texttt{b}\color{red}\texttt{aba}\color{black}\texttt{ba} $ ;
- 涂红 $ t[1 \dots 2]=s_1=\texttt{ba} $ 得 $ t=\color{red}\texttt{baba}\color{black}\texttt{ba} $ ;
- 涂红 $ t[4 \dots 6]=s_2=\texttt{aba} $ 得 $ t=\color{red}{\texttt{bababa}} $ .


#### 解法

首先将 $s$ 匹配到 $t$ 中。

理论上是要用 $\texttt{KMP}$ 算法的，但是仅仅把单次复杂度从 $O( |t|\times\sum_{i=1}^{n} |s_i|)$ 降低到 $O(\sum_{i=1}^{n} (|s_i|+|t|))$ 显得完全没有必要所以直接暴力就可以。

然后开始贪心。

举个例子：

> $t=\texttt{abacbabc}$

> $\color{black} s_1=\color{red}\texttt{ab} 
\color{black}, s_2=\color{red}\texttt{abac} 
\color{black}, s_3=\color{red}\texttt{cb}
\color{black}, s_4=\color{red}\texttt{c}$

第一个字母必须要涂。可以选择涂 $s_1,s_2$。显然由于 $|s_2|>|s_1|$，选 $s2$ 永远不劣于 $s1$。

因此只需存储该位开始最长可能涂的长度。

接下来可以遍历 $[1...4]$ ，找到涂里面一个可能到达的最远位置。

以此类推。

无解判定显然，就是涂完了 $[1...n](n<|t|)$ 但是在 $[1...n]$ 中不存在一位开始最长可能涂到的位置大于 $n$ 。

单测时间复杂度为 $O( |t|\times\sum_{i=1}^{n} |s_i|+|t|)$，其中 $|t|$ 可以忽略。

#### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<cstring>
using namespace std;
#define il inline
#define rei register int
il const void readln(int &I){
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))I=I*10+C-'0',C=getchar();
}
string t,s[15];
int q,n,l,f[105],g[105];
vector<int>ans;
int main(){
	readln(q);
	while(q--){
		for(rei i=0;i<105;i++)f[i]=g[i]=0;
		cin>>t,l=t.length(),readln(n);
		for(rei i=1;i<=n;i++){
			cin>>s[i];
			for(rei j=0;j+s[i].length()<=l;j++){
				if(s[i]==t.substr(j,s[i].length()) and f[j]<(int)s[i].length())
                    f[j]=(int)s[i].length(),g[j]=i;
			}
		}
		int c=-1,o=0;bool ok=1;
		for(rei i=0;i<l and ok;i++){
			if(f[i]+i>f[o]+o)o=i;
			if(c<=i){
				if(f[o]+o<=i){ok=0;break;}
				else ans.push_back(o),c=f[o]+o;
			}
		}
		if(ok==0) {while(ans.size())ans.pop_back();puts("-1");}
		else {
			printf("%d\n",ans.size());
        	while(ans.size()){
        	    printf("%d %d\n",g[ans.back()],ans.back()+1),ans.pop_back();//输出顺序不影响
        	}
		}
	}

}
```

---

## 作者：linyihdfj (赞：2)

## D.Color with Occurrences
### 题目描述：
[原题面](https://codeforc.es/contest/1714/problem/D)
### 题目分析：
因为 $|s|,|t|$ 都很小，所以我们可以考虑直接暴力处理出 $t$ 中能放每一个 $s$ 的位置，这样假设我们在 $x$ 位置放置一个 $s_i$，那么就相当于这一个 $s_i$ 能完全覆盖 $[x,x + |s_i| - 1]$。

那么这个问题就显然地转化为了一个最少线段覆盖的问题，而且显然线段最多只有 $1000$ 条。

对于这个问题我们可以动态维护 $[l,r]$ 代表我们现在已经覆盖的区间，然后每次选择左端点在 $[l,r]$ 内的线段，对他们的右端点取一个最大值，这样直到所有的符合条件的线段都考虑了之后，我们得到的最大值就是当前能放置的最优的一条线段。
### 代码详解：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000;
struct node{
	int l,r,pos;
	node(){}
	node(int _l,int _r,int _pos){
		l = _l,r = _r,pos = _pos;
	}
}a[MAXN],ans[MAXN];
int sz_t,cnt,sz_s[11]; 
char t[MAXN],s[11][MAXN];
bool cmp(node l,node r){
	return l.l < r.l;
}
void work(){  //求解最小线段覆盖 
	sort(a+1,a+cnt+1,cmp);   
	int now_r = 0;
	int tmp_r = 0;
	int sum = 0; 
	int tot = 0;
	bool tag = true;
	node now_ans;
	for(int i=1; i<=cnt; i++){
		if(a[i].l <= now_r + 1)	{
			if(a[i].r > tmp_r){
				tmp_r = a[i].r;
				now_ans = a[i];
			}
		}
		else{
			sum++;
			ans[++tot] = now_ans; 
			now_r = tmp_r;
			if(a[i].l > now_r + 1){
				tag = false;
				break;
			}
			else{
				if(a[i].r > tmp_r){
					tmp_r = a[i].r;
					now_ans = a[i];
				}
			}
		}
	}
	if(!tag){
		printf("-1\n");
		return;
	}
	else{
		if(now_r < sz_t){	 //注意这种情况 
			now_r = max(now_r,tmp_r);
			sum++;
			ans[++tot] = now_ans;
		}
		if(now_r < sz_t){
			printf("-1\n");
			return;
		}
		printf("%d\n",sum);
		for(int i=1; i<=tot; i++){
			printf("%d %d\n",ans[i].pos,ans[i].l);
		}
	}
}
bool check(int pos,int j){  //判断能否在 pos 的位置放置 s[j] 
	for(int i = pos; i<=pos + sz_s[j]-1; i++){
		if(t[i] != s[j][i - pos + 1])	return false;
	}
	return true;
}
int main(){
	int q;
	cin>>q;
	while(q--){
		cnt = 0;
		scanf("%s",t+1); 
		sz_t = strlen(t + 1);
		int n;
		cin>>n;
		for(int i=1; i<=n; i++){
			scanf("%s",s[i] + 1);
			sz_s[i] = strlen(s[i] + 1);
		}
		for(int i=1; i<=sz_t; i++){  //将所有的线段摘出来 
			for(int j=1; j<=n; j++){
				if(i + sz_s[j] - 1 <= sz_t && check(i,j))
					a[++cnt] = node(i,i + sz_s[j] - 1,j);
			}
		}
		work();
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

我们可以看到，数据范围特别小。所以我们可以采用动态规划解决。

我们可以设 $dp[i]$ 为从 $1$ 到 $i$ 全部完成涂色需要多少次涂色。

我们可以枚举，右端点匹配到 $t_i$ 的字符串 $s_j$。如果 $s_j$ 右端点重合到 $t_i$ 上后能够匹配，那么 $dp[i]$ 就可以更新，具体更新为 $\min[dp[i],\min_{j=i-|s|}^{i-1}(dp[j]+1)]$。

更新的时候记得记录一下，右端点覆盖到 $t_i$ 的字符串 $s_j$ 和这个字符串涂色完毕后应该涂哪里。

根据 $dp[|t|]$ 判断是否有解即可。

具体请参阅下方代码。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define inf 0x3f3f3f3f
int t;
char s[120];
int len;
int n;
char a[12][12];
int ai[12];
int dp[120];
int cov[120];
int pos[120];
bool check(int x,int t){
	if(ai[t]>x)return false;
	for(int i=x,j=ai[t];j>=1;--i,--j){
		if(s[i]!=a[t][j])return false;
	}
	return true;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714D_1.in","r",stdin);
	freopen("CF1714D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%s",s+1);
		len=strlen(s+1);
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%s",a[i]+1);
			ai[i]=strlen(a[i]+1);
		}
		dp[0]=0;
		for(int i=1;i<=len;++i){
			dp[i]=inf;
			cov[i]=pos[i]=0;
		}
		for(int i=1;i<=len;++i){
			for(int j=1;j<=n;++j){
				if(check(i,j)){
					for(int k=i-ai[j];k<=i-1;++k){
						if(dp[k]+1<dp[i]){
							dp[i]=dp[k]+1;
							cov[i]=j;
							pos[i]=k;
						}
					}
				}
			}
		}
		if(dp[len]>=inf)printf("-1\n");
		else{
			printf("%d\n",dp[len]);
			for(int i=len;i;i=pos[i]){
				printf("%d %d\n",cov[i],i-ai[cov[i]]+1);
			}
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82204045)

By **dengziyue**

---

## 作者：zhou_ziyi (赞：0)

### Description

给定一个字符串 $t$ 和 $n$ 个模板串 $s_i$，若 $s_i$ 和 $t$ 的某个子串 $t[l\ldots r]$ 相等，则可以花费 $1$ 的代价将这个子串染色，同一段可以被染色多次。求最小代价和方案，或者输出无解。

### Solution

由于同一段可以被染色多次，所以最小代价和顺序无关，由于 $1 \leq \vert t \vert \leq 100$，$1 \leq \vert s_i \vert \leq 100$ 而且 $1 \leq n \leq 10$ 可以考虑 $dp$。我们可以定义状态 $dp_{i, j}$ 为将 $t$ 的前 $i$ 个字符都染色的最小代价。接下来考虑转移，为了提高效率，我们可以先预处理出 $len_j$ 表示 $s_j$ 的长度， $flag_{i, j}$ 表示 $s_j$ 能否匹配字符串 $t$ 中以位置 $i$ 结尾，长度为 $len_{j}$ 的子串。这样就可以较轻松地写出状态转移方程，对于每个位置 $i$，考虑每个能够匹配的$s_j$，对于每个 $s_j$，从 $i - len_j \to i$ 区间内转移。所以状态转移方程如下：
$dp_{i, j} = \min_{i - len_j} ^ i dp_k + 1$

而记录答案就用 $pre$ 数组和 $ans$ 数组记录即可。

### Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
const int MAXN = 105;
int T;
int n, m;
string s;
int dp[MAXN], pre[MAXN];
int flag[MAXN][MAXN];
int len[MAXN], ans[MAXN];
void print(int k) {
    if (!k)
        return;
    print(pre[k]);
    printf("%d %d\n", ans[k], k - len[ans[k]] + 1);
    return;
}
int main() {
	scanf("%d", &T);
    while (T--) {
        cin >> s;
        n = s.length();
        s = '0' + s;
        memset(dp, 0x3f, sizeof(dp));
        memset(pre, 0, sizeof(pre));
        memset(flag, 0, sizeof(flag));
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            string t;
            cin >> t;
            len[i] = t.length();
            for (int j = len[i]; j <= n; j++)
                if (s.substr(j - len[i] + 1, len[i]) == t)
                    flag[j][i] = 1;
        }
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!flag[i][j])
                    continue;
                for (int k = i - len[j]; k < i; k++) {
                    if (dp[k] + 1 < dp[i]) {
                        pre[i] = k;
                        ans[i] = j;
                        dp[i] = dp[k] + 1;
                    }
                }
            }
        }
        if (dp[n] == 0x3f3f3f3f)
            printf("-1\n");
        else {
            printf("%d\n", dp[n]);
            print(n);
        }
    }
    return 0;
}
```

---

## 作者：panyanppyy (赞：0)

赛时十分痛苦地写了 dp 做法，中间一些东西想了好久，所以来写个题解。
## Problem
就是给你一个文本串 $t$，然后每次可以涂红其一个模式串 $s_i$（可以重复涂），问最少的涂抹次数和方案。
## Solution
首先可以想到可以直接从左往右做，这样就没有后效性了。

$|t|$ 和 $n,|s_i|$ 都很小，考虑直接暴力 dp。

设 $f_i$ 表示 $1\sim i$ 全部涂红的最少次数。

转移：
$$ f_i=f_k+1[t_{i-|s_j|+1\sim i}=s_j,i-|s_j|\le k<i,1\le j\le n] $$

转移条件前半段很显然，要从前面一段和模式串相同的。

重点是中间那段，考虑红色可以重复涂多次，所以可以从能匹配的一段中任意一个位置转移。

记录路径的时候只要记录转移点和转移用的区间就可以了。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
const int M=12,N=233;
int T,n,m,f[N];
pair<int,int>pre[N];
string t,s[M];
inline void work(){
	cin>>t>>n,m=t.size(),t=' '+t;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=0;i<=m;i++)pre[i]={-1,-1};
	memset(f,0x3f,sizeof(f)),f[0]=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)if(i>=(int)s[j].size())
			if(t.substr(i-s[j].size()+1,s[j].size())==s[j]){
				for(int k=i-s[j].size();k<i;k++)
					if(f[i]>f[k]+1)f[i]=f[k]+1,pre[i]={k,j};
			}
	}
	int x=m;
	if(f[m]==0x3f3f3f3f)return cout<<"-1\n",void();
	cout<<f[m]<<'\n';
	while(~pre[x].first){
		cout<<pre[x].second<<' '<<x-s[pre[x].second].size()+1<<'\n';
		x=pre[x].first;
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：YCSluogu (赞：0)

## CF1714D 题解

### 翻译

给定一个字符串 $t$ 和 n 个字符串 $s_{1},s_{2},...,s{n}$

开始 $t$ 字符串为黑色，你的目标是将它全部染成红色

你可以执行如下操作：

挑选 $t$ 的一个子串，若此子串与 $s_{1},...,s_{n}$ 中任何一个字符串相等，那么 $t$ 对应的部分染成红色。
同时染成红色的地方将一直是红色。

### 思路

我的第一个反应是直接暴力 DP。不过介于过小的数据范围，DP 转移并且记录转移位置其实是可做的。

我的状态设计是 $(i, s)$ ~~很难见到这么简洁的状态设计的题目了~~。$i$ 表示当前为字符串第 $i$ 位，$s$ 为最小操作次数。其中 $s$ 为最优化属性。我觉得这道题的拓扑序和状态设计还是挺显然的吧。

不过我觉得这道题写扩散型 DP 会比收集型要容易一点，不过我在这里主要讲述一下收集型的方法。

对于状态 $(i, s)$ 找到一个字符串 $s_{k}$。若 $t[i - |s_{k}| + 1..i] = s_{k}$，那么意味着状态 $(i - |s_{k}| + 1, s')$ 到 $(i, s)$ 都可以由 $(i - |s_{k}|, s'')$ 转移而来。期间同时要记录状态转移。~~我尽力表述清楚了qwq~~ 

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e6;

int            dp[kMaxN];
string         a[kMaxN];
pair<int, int> pre[kMaxN];

void print(int x) {
  if (x == 0) { return; }
  print(pre[x].first);
  cout << pre[x].second << " ";
  cout << pre[x].first + 1 << endl;
}

void solve() {
  int    n, s;
  string str;
  cin >> str;
  s   = str.size();
  str = '#' + str;
  cin >> n;
  memset(dp, 0x3f, sizeof(dp));
  memset(pre, 0, sizeof(pre));
  dp[0] = 0;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  for (int i = 1; i <= s; i++) {
    for (int k = 1; k <= n; k++) {
      if (a[k].size() > i) continue;
      int l = i - a[k].size() + 1;
      if (str.substr(l, a[k].size()) == a[k]) { // 若刚好相同
        for (int j = l; j <= i; j++) {
          if (dp[l - 1] + 1 < dp[j]) {
            dp[j]  = dp[l - 1] + 1;
            pre[j] = make_pair(l - 1, k); // 记录转移
          }
        }
      }
    }
  }
  if (dp[s] == 0x3f3f3f3f) {
    cout << -1 << endl;
  } else {
    cout << dp[s] << endl;
    print(s);
  }
}

int t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) { solve(); }
  return (0 - 0);
}
```


---

## 作者：zsseg (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1714D)

### 题意：
给定一个模式串 $t$ 与 $n$ 个字符串 $s_1$、$s_2......s_n$ ，若 $s_i$ 在 $t$ 中被匹配，则在对应位置染色。求染色整个模式串时操作次数最少的染色方案。

首先，可以观察到 $t$ 、 $s$ 长度都很小，考虑枚举每一个能够染色的区间。比如对于样例 $t=\texttt{bababa},s_1=\texttt{ba},s_2=\texttt{aba}$， $s_1$ 可以染色区间 $[1,2][3,4][5,6]$ ，$s_2$ 可以染色区间 $[2,4][4,6]$。

```cpp
//暴力找染色区间
f(i,1,n){
	scanf("%s",s+1);
	ls=strlen(s+1);
	f(j,1,lt-ls+1){
		if(s[1]==t[j]){
			int f=1;
			f(k,j,j+ls-1)if(s[k-j+1]!=t[k])f=0;
			if(f)e[++cnt]=(node){j,j+ls-1,i};//找到就记录左端点、右端点、字符串编号
		}
	}
}
``` 
那么，这道题转化为下面的问题：

一个一维区间上，有若干条线段，线段 $s_i$ 两端点分别为 $l_i$，$r_i$。求覆盖全部的最小线段条数，输出方案。

这样就可以贪心了，先找到 $l_1=1$ 出发使 $r_1$ 最大的线段，再找到 $l_2\leq r_1+1$ 出发使 $r_2$ 最大的线段，以此类推，直到 $l=\left\vert t\right\vert$ 为止，开一个数组记录方案，中间找不到就输出 $-1$，最后找到就输出方案。


```cpp
//贪心找答案
sort(e+1,e+1+cnt,cmp);
int l=0;
while(l<lt){
	int maxr=l,thisid=0;
	f(i,1,cnt){
		if(e[i].l>l+1)break;//因为端点也有体积，l要+1
		if(e[i].r>maxr)maxr=e[i].r,thisid=i;
	}
	if(maxr==l){l=-1;break;}
	ans[++tot]=thisid;
	l=maxr;
}
```
### 完整代码:

```cpp
#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
#define g(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define end() putchar('\n')
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int T=read(),n,ls,lt,cnt,ans[110],tot,vis[110],res[110];
char t[110],s[11];
struct node{
	int l,r,id;
}e[1010];
bool cmp(node x,node y){
	if(x.l==y.l)return x.r>y.r;
	return x.l<y.l;
}
int main(){while(T--){
	scanf("%s",t+1);
	tot=0;
	memset(ans,0,sizeof(ans));
	memset(e,0,sizeof(e));
	lt=strlen(t+1);
	cnt=0;
	n=read();
   	//暴力求区间
	f(i,1,n){
		scanf("%s",s+1);
		ls=strlen(s+1);
		f(j,1,lt-ls+1){
			if(s[1]==t[j]){
				int f=1;
				f(k,j,j+ls-1)if(s[k-j+1]!=t[k])f=0;
				if(f)e[++cnt]=(node){j,j+ls-1,i};
			}
		}
	}
    	//按左端点排序
	sort(e+1,e+1+cnt,cmp);
        //贪心
	int l=0;
	while(l<lt){
		int maxr=l,thisid=0;
		f(i,1,cnt){
			if(e[i].l>l+1)break;
			if(e[i].r>maxr)maxr=e[i].r,thisid=i;//更新答案并记录编号
		}
		if(maxr==l){l=-1;break;}//判断无解
		ans[++tot]=thisid;//存储答案（不能直接输出，要判无解）
		l=maxr;
	}
	if(l!=-1){
		write(tot),end();
		f(i,1,tot){
			write(e[ans[i]].id),putchar(' '),write(e[ans[i]].l),end();
		}
	}else write(-1);
	end();
}
	return 0;
}

```


---

