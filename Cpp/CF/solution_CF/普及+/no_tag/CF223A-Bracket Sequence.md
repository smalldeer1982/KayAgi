# Bracket Sequence

## 题目描述

A bracket sequence is a string, containing only characters "(", ")", "\[" and "\]".

A correct bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()\[\]", "(\[\])" are correct (the resulting expressions are: "(1)+\[1\]", "(\[1+1\]+1)"), and "\](" and "\[" are not. The empty string is a correct bracket sequence by definition.

A substring $ s[l...\ r] $ $ (1<=l<=r<=|s|) $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is the string $ s_{l}s_{l+1}...\ s_{r} $ . The empty string is a substring of any string by definition.

You are given a bracket sequence, not necessarily correct. Find its substring which is a correct bracket sequence and contains as many opening square brackets «\[» as possible.

## 样例 #1

### 输入

```
([])
```

### 输出

```
1
([])
```

## 样例 #2

### 输入

```
(((
```

### 输出

```
0

```

# 题解

## 作者：卷王 (赞：8)

[传送门](https://www.luogu.com.cn/problem/CF223A)

总体来说，这题还是挺简单的，不知道为什么洛谷上只有十个人过。

首先我们分析一下题目。

> 当且仅当能在里面加上若干个 `1` 和 `+`，使其成为一个正确的表达式（其中两种括号均可以互相嵌套）

这句话表面上绕来绕去，但是我们随便举几个例子，就可以轻易发现，它所说的合法括号序列就是我们熟知的 **一个右括号配对一个左括号** 的括号序列！

现在你或许已经会做了，解读出了这个解法就已经和 CF5C 的解法很类似了，不过就是要记录一下 $sum_i$：序列到了第 $i$ 个位置包含了多少个 `[`，然后后面正常 dp 即可。

当然，没做过 CF5C 也没关系，我在这里解释一下一些数组和变量的意思：

* $l_i$ ：若 $s_i$ 为右括号，则返回它所匹配的左括号的位置，否则返回 $-1$。

* $dp_i$：到了序列的第 $i$ 个位置的最大 `[` 的数量。

* $L,x$：分别是答案的左端点和右端点，$x$ 显然是最大 $dp$ 值的下标，接着用 $l$ 数组反推得出 $L$。

这道题就做完了。

AC 代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n,m,cnta=0,cnt=0,ans=0,num=1,lst=0;
int l[1000007];
int dp[1000007];
stack<int>st;
char s[1000007];
int sum[1000007];

int main() {
	cin>>(s+1); n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='('||s[i]=='[') {
			st.push(i);
			l[i]=-1;
			continue;
		}
		if(s[i]==')'){
			if(!st.empty()&&s[st.top()]=='('){
				l[i]=st.top(); st.pop();
			}
			else{
				l[i]=-1;
				while(!st.empty()) st.pop();
			}
		}
		else if(s[i]==']'){
			if(!st.empty()&&s[st.top()]=='['){
				l[i]=st.top(); st.pop();
			}
			else{
				l[i]=-1;
				while(!st.empty()) st.pop();
			}
		}
	}
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='[');
	int maxx=0,x=-1;
	for(int i=1;i<=n;i++){
		if(s[i]=='('||s[i]=='['||l[i]==-1) dp[i]=0;
		else dp[i]=dp[l[i]-1]+sum[i]-sum[l[i]-1];
		if(dp[i]>maxx){
			maxx=dp[i];
			x=i;
		}
	}
	if(maxx==0){
		cout<<"0\n";
		return 0;
	}
	int L=l[x];
	while(1){
		if(L==1||l[L-1]==-1) break;
		L=l[L-1];
	}
	cout<<maxx<<"\n";
	for(int i=L;i<=x;i++) cout<<s[i];
	cout<<"\n";
	return 0;
}
```

---

## 作者：_outcast_ (赞：5)

### 提意

给定一个括号序列，求一个合法的括号子串，并且使得这个子
串含有尽量多的 "[ ]" 。
### 分析
~~（这道题好像没有数据范围？）~~

不过搜索是可以过的，而且也比较好想，我的思路是 BFS。

首先我们可以先把括号序列中相邻的 "()" 或 "[]"取出来，把左右括号的下标 $L$ 和 $R$ 加入队列作为搜索的起点。

然后我们对于取出的点，记录当前序列 $l$ 和 $r$ 的下标，考虑以下几种情况

- 1.包含型：
    
    简单来说就是类似 " [ (当前序列) ] "，"( （当前序列） )" 。这种情况下我们就看一下 $l-1 $和 $r+1$ 是否可以组成一个合法括号，若是，我们就把当前的新序列入队。
    
- 2.连接型：

   简单来说就是类似 "[...]（当前序列）"，"(...)（当前序列）"。这种情况根据 $l-1$ 或 $r+1$ 的边界来更新序列并加入队列。
   
至此我们就理论切掉这道题了。
### 代码实现

详见注释
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=1e5+5;
int n,m,al,ar,ans,v[N],val[N];//v[]表示当前边界所在合法序列的另一个边界的下标 
char s[N];                    //val[]表示当前边界所在合法序列的答案 
queue<int> q;
void push(int l,int r,int c){//核心，入队操作，记录边界并更新答案 
	v[l]=r; v[r]=l;
	val[l]=val[r]=c;
	q.push(l);
	q.push(r);
}
void bfs(){
	memset(v,-1,sizeof v);
	for(n=0;s[n];n++){//取出相邻的合法括号 
		if(s[n]=='('&&s[n+1]==')'){
			push(n,n+1,0);
			continue;
		}
		if(s[n]=='['&&s[n+1]==']'){
			push(n,n+1,1);
			continue;
		}
	}
	if(!q.size()) puts("0"),exit(0);//没有相邻的合法括号，无解 
	for(ans=-1;q.size();){
		int l=q.front();q.pop();
		int r=q.front();q.pop();
		
		if(v[l]==-1||v[r]==-1) continue;//如果当前节点不是边界，跳过 
		
		if(ans<val[l]) ans=val[l],al=l,ar=r;//记录答案 
		
		if(l>0&&r<n-1){//包含型 
			if(s[l-1]=='('&&s[r+1]==')'){
				v[l]=v[r]=-1,push(l-1,r+1,val[l]);
				continue;
			}
			if(s[l-1]=='['&&s[r+1]==']'){
				v[l]=v[r]=-1,push(l-1,r+1,val[l]+1);
				continue;
			}
		}
		
		if(l>0&&v[l-1]!=-1){//连接型 
			push(v[l-1],r,val[l-1]+val[l]),v[l]=v[l-1]=-1;
			continue;
		}
		if(r<n-1&&v[r+1]!=-1){
			push(l,v[r+1],val[r]+val[r+1]),v[r]=v[r+1]=-1;
			continue;
		}
	}
	s[ar+1]=0;
	cout<<ans<<'\n'<<s+al;
}
int main(){
    cin>>s;
    bfs();
}

```



---

## 作者：Ascnbeta (赞：1)

# CF233A
## 前置练习
水绿一道，在做这道题之前，推荐先做 [CF5C](https://www.luogu.com.cn/problem/CF5C)，可以说是这道题的基础。
## 题面大意
其实重点在于理解这句话：
> 一个括号序列是合法的，当且仅当能在里面加上若干个 $1$ 和 $+$，使其成为一个正确的表达式（其中两种括号均可以互相嵌套）。

如果表达式想要合法，那么就意味着括号序列必须合法，即不能出现非法嵌套和数量不匹配的情况。同样，如果括号序列合法，那么一定存在一种方案可以使添加 $1$ 和 $+$ 后的序列合法。

因此这道题实际上就转为了 CF5C 的加强版，只是多了中括号而已。
## 思路分析
判断括号是否是合法序列很简单，利用 CF5C 的思路，我们很容易想到使用**栈**来匹配，如果右括号 `)` 或 `]` 出现时，栈顶不是对应的左括号（即 `[)` 和 `(]` 两种情况）的时候，我们直接清空整个栈，因为只要出现了左右括号不匹配的情况，意味着以前的左括号到当前的整个长序列 **（注意是从头到尾的长序列，不包括它的子序列）** 已经是非法序列。同样，如果遇到右括号但是栈里已经空了也代表当前位置是非法的序列。

此外最后题目要求输出的是 `[` 出现最多次数的子序列，那么我们在每次匹配到一堆合法括号序列的时候，就可以将这两个括号所在的位置标记为 `true`，最后判断完整个括号序列后，我们只需要遍历一遍找出所有合法序列的区间，并且比较其中出现 `[` 的次数，找到出现次数最多的区间左右端点即可，最后输出这个序列。
## 具体实现
因为我们需要在右括号匹配左括号成功时将两个括号的位置都标记为 `true`，所以本蒟蒻的栈存放的是每个左括号的下标，方便标记。其他的代码参照上文内容并且类比 CF5C 即可，这里不再赘述。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
stack<int> st;
bool m[100005];//如果当前位置在一个合法的括号序列中，那么 m[i] 为 true。
int l,r,ans,tot = 1;
struct zone{
    int l,r,cnt;//cnt 表示 "[" 出现次数。
}z[100005];
int main () {
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(' || s[i] == '[') st.push(i);
        else if (s[i] == ')') {
            if (!st.empty() && s[st.top()] == '(') { //注意判断非空一定要在调用 top 前，防止因为栈是空的而去访问顶部元素导致 RE。
                m[i] = m[st.top()] = true;
                st.pop();
            }else{
                while (!st.empty()) st.pop(); // 失配时清空栈
            }
        }else {
            if (!st.empty() && s[st.top()] == '[') {
                m[i] = m[st.top()] = true;
                st.pop();
            }else{
                while (!st.empty()) st.pop();
            }
        }
    }
    int tmp = 0;
    for (int i = 0; i < s.size(); i++) {
        if (m[i]) {
            z[tot].l = i;
            int cnt = 0;
            for (int j = i; m[j]; j++) {
                if (s[j] == '[') {
                    ++cnt;
                }
                z[tot].r = j;
            }
            i += z[tot].r - z[tot].l;
            z[tot++].cnt = cnt;
        }
    }//遍历区间，存储了所有区间的信息。
    for (int i = 1; i < tot; i++) {
        if (z[i].cnt > ans) {
            ans = z[i].cnt;
            l = z[i].l;
            r = z[i].r;
        }
    }
    cout << ans << '\n';
    if (ans == 0) {
        return 0;
    }//当 ans 为 0 时特判，防止因为此时 l,r 均为 0 而导致输出了第一个字符。
    for (int i = l; i <= r; i++) {
        cout << s[i];
    }
    return 0;
}
```

---

## 作者：Melo_DDD (赞：1)

叠甲：CF 已过。

这个人因为一个特唐氏的错误成功浪费一个上午，一会警钟长鸣。

这道题和 CF5C 在做法上没有任何区别，因为观察题目发现题目条件等价于我们找到的括号是匹配的。

我们用栈解决，对每个右括号**记录与之匹配的左括号的位置**。如果遇到一个左括号（无论是小括号还是中括号），我们直接存进栈里。

当遇到一个右括号的时候，如果栈顶能够与之匹配，那么把栈顶的位置记录下来，并且将栈顶弹出。假如不匹配，那么对于之后的任意括号来说，它之前的永远不可能再匹配上了，直接将栈清空。

建议手写栈，清空是 $\Theta(1)$ 的，而且常数没有那么大。

接下来考虑如何统计最多的包含 ``[`` 的串，考虑 dp。

首先可以用前缀和优化统计 ``[`` 的个数是显然的。

设 $dp_i$ 表示以 $i$ 结尾的合法串包含多少 ``[``，那么转移方程是 $dp_i=dp_{f_i - 1}+ sum_i-sum_{f_i - 1}$，其中 $f$ 和 $sum$ 分别记录的是与当前右括号匹配的左括号的位置和前缀和。解释一下这个方程：首先两个前缀和相减求的是 $f_i$ 到 $i$ 这段有多少个 ``[``，在加上 $dp_{f_i-1}$ 的意思是看看能不能和前面合法的串拼到一起。注意只有在有与这个括号匹配的括号时才能进行上述更新。

那么我们只需要对所有的 $dp$ 数组取最大值，记录取到最大值的位置，就能找到答案串的末尾了。

那么如何找到开头呢？我们可以进行上述过程的逆操作。我们可以从最后这个位置开始一直跳，如果有 $f_i$（有括号和它匹配），就跳到 $f_i-1$ 继续向前找，设最后找到的那个位置是 $j$，那么答案串的开头就是 $j+1$。最后输出就好了。

代码：


```cpp
cin >> ch + 1 ;
int len = strlen (ch + 1) ;
f (i ,1 ,len ,1) {
	if (ch[i] == '(' || ch[i] == '[')
		stk[++ stop] = i ;
	else if (ch[i] == ')') {
		if (stop && ch[stk[stop]] == '(') {
			inf[i] = stk[stop --] ;
		}
		else 
			stop = 0 ;
	} else {
		if (stop && ch[stk[stop]] == '[') 
			inf[i] = stk[stop --] ;
		else 
			stop = 0 ;
	}
}
f (i ,1 ,len ,1) 
	sum[i] = sum[i - 1] + (ch[i] == '[') ;
int maxx = 0 ;
f (i ,1 ,len ,1) {
	if (inf[i])
		dp[i] = dp[inf[i] - 1] + sum[i] - sum[inf[i] - 1] ;
	if (dp[maxx] <= dp[i]) 
		maxx = i ;
}
cout << dp[maxx] << '\n' ;
if (! maxx)
	return 0 ;
int loc ; 
for (loc = maxx ;inf[loc] ;loc = inf[loc] - 1) ;
f (i ,loc + 1 ,maxx ,1) 
	cout << ch[i] ;
cout << '\n' ;
```

讲个笑话，这个人刚开始把栈数组设成了字符类型一直 RE，然后在机房破防了。欢迎来虐菜。

---

## 作者：ZLCT (赞：0)

# CF223A Bracket Sequence
## 题意
给定一个只含有 `(` `)` `[` `]` 的括号序列，求包含 `[` 最多的子串使该子串可以通过填入 `1` `+` 成为一个合法表达式。
## 合法表达式？合法括号匹配！
题目虽然说需要填入 `1` 和 `+` 使构成合法表达式，但是简单一想就会发现其实是要求合法括号匹配。（只需要构成形如`1+(1+(1)+1)`的表达式即可）\
于是我们的问题就变成了找到一个包含 `[` 最多的合法括号匹配。（找`]`等价）
### 合法括号匹配
首先我们可以通过一个栈处理出每一个右括号所对应的左括号。\
具体地，我们维护一个只有左括号的栈，如果遍历到了一个右括号，就与栈顶的括号匹配，如果匹配不上就一定不合法（如`(]`或`[)`），清空栈即可。
### 最多 `[` 区间
我们考虑利用上面求的合法括号匹配去进行 $dp$。\
设 $dp_i$ 表示末尾是 $s_i$ 的最大答案。（由于`[`和`]`一定成对出现，所以可以算`]`数量）\
我们每匹配到一个合法的 `)`或`]`，就可以算一次 $f_i$。\
如何转移？\
因为我们处理出了每个右括号所对应的左括号所在位置 $l_i$，所以我们直接把答案分成 $[1,l_i)$ 和 $[l_i,i]$。而 $[1,l_i)$ 的贡献就是 $f_{l_i-1}$；$[l_i,i]$ 的贡献我们可以预处理前缀`]`的数量和，贡献就是 $sum_i-sum_{l_i-1}$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l[112345],f[112345],ansl,ansr,sum[112345];
vector<int>vec;
int vlen=0;
int maxl(int m1,int m2){
    if(f[m1]>f[m2])return m1;
    return m2;
}
signed main(){
    cin>>s;
    s=' '+s;
    l[0]=-1;
    for(int i=1;i<s.size();++i){
        l[i]=-1;
        if(s[i]=='('||s[i]=='['){
            vec.push_back(i);
            vlen++;
            continue;
        }
        if(s[i]==')'){
            if(vlen&&vec[vlen-1]&&s[vec[vlen-1]]=='('){
                l[i]=vec[vlen-1];
                vec.pop_back();
                vlen--;
            }else{
                vec.clear();
                vlen=0;
            }
        }else{
            if(vlen&&vec[vlen-1]&&s[vec[vlen-1]]=='['){
                l[i]=vec[vlen-1];
                vec.pop_back();
                vlen--;
            }else{
                vec.clear();
                vlen=0;
            }
        }
    }
    for(int i=1;i<s.size();++i){
        sum[i]=sum[i-1];
        if(s[i]==']')sum[i]++;
    }
    for(int i=1;i<s.size();++i){
        if(l[i]==-1||s[i]=='('||s[i]=='[')continue;
        f[i]=f[l[i]-1]+sum[i]-sum[l[i]-1];
        ansr=maxl(ansr,i);
    }
    ansl=ansr;
    while(ansl!=1&&l[ansl]!=-1){
        ansl=l[ansl];
        if(l[ansl-1]!=-1)ansl--;
    }
    cout<<f[ansr]<<'\n';
    if(!f[ansr])return 0;
    for(int i=ansl;i<=ansr;++i){
        cout<<s[i];
    }
    return 0;
}
```

---

