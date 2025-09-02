# [ABC031D] 語呂合わせ

## 题目描述

日本有一种将数字与短字符串对应的记忆文化。

对此产生兴趣的高桥君，决定推断出仅由 $1$ 以上 $K$ 以下的数字组成的正整数 $v_1,v_2,\cdots,v_n$ 以及对应的字符串 $w_1,w_2,\cdots,w_n$ 的组合 $(v_1,w_1),(v_2,w_2),\cdots,(v_n,w_n)$ 中，哪个数字对应哪个字符串。

也就是说，想要找出满足以下条件的 $K$ 个字符串 $s_1,s_2,\cdots,s_K$。

- 对于满足 $1 \leqq i \leqq K$ 的任意整数 $i$，必须满足 $1 \leqq |s_i| \leqq 3$。
- 对于满足 $1 \leqq i \leqq N$ 的任意整数 $i$，当将整数 $v_i$ 按位分解时，得到的数字从上到下依次为 $d_1,d_2,\cdots,d_l$，则将字符串 $s_{d_1},s_{d_2},\cdots,s_{d_l}$ 按此顺序连接的字符串等于 $w_i$。

请编写程序输出 $K$ 个字符串 $s_1,s_2,\cdots,s_k$。

## 样例 #1

### 输入

```
6 4
356 migoro
461 yoroi
2 ni
12 ini```

### 输出

```
i
ni
mi
yo
go
ro```

## 样例 #2

### 输入

```
3 4
21 aaa
12 aaa
123 aaaaaa
13 aaaa```

### 输出

```
a
aa
aaa```

## 样例 #3

### 输入

```
2 3
12211 abcaaaaabcabc
2121 aaabcaaabc
222221 aaaaaaaaaaabc```

### 输出

```
abc
aa```

## 样例 #4

### 输入

```
2 1
12 abcab```

### 输出

```
ab
cab```

# 题解

## 作者：Nazale_ (赞：1)

大致题意：有 $K$ 个数字，每个数字代表一个字符串。给出一些数字顺次写出而组合成的字符串。求可能的一种数字对应方案。

考虑暴搜。注意到每个数字对应的字符串长度不超过3，所以直接枚举每个数字的长度，最后一起判断是否合法。首先要满足每个组合内的情况，即数字长度加和正好是 $v_i$ 的长度。然后从串中分离出每个数字对应的串，暴力地去看合不合法就好了。找到情况就输出。

复杂度是 $O(3^{k}nc)$ 的，其中 $c$ 是 $\sum{v_i}$ 级别的。

参考代码如下：


```
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define INF 1e10
#define eb emplace_back
#define pb push_back
#define ls (u<<1)
#define rs ((u<<1)|1)
#define lowbit(x) (x&(-x))
#define pii pair<int,int> 
#define fi first
#define se second
using namespace std;
const int maxn=55;
const int maxm=10;
const int mod=1e9+7;
int k,n,ans,len[maxm];
bool f;
string v[maxn],w[maxn],s[maxm];
void dfs(int pos){
	if(pos>k){
		for (int i=1;i<=k;i++) s[i]="";
		for (int i=1;i<=n;i++){
			int sum=0;
			for (int j=0;j<v[i].length();j++){
				sum+=len[v[i][j]-'0']; 
			}
			if(sum!=w[i].length()) return;
			int st=0;
			for (int j=0;j<v[i].length();j++){
				string str=w[i].substr(st,len[v[i][j]-'0']);
				if(s[v[i][j]-'0']=="") s[v[i][j]-'0']=str;
				else if(s[v[i][j]-'0']!=str) return;
				st+=len[v[i][j]-'0'];
			}
		}
		if(!f){
			for (int i=1;i<=k;i++){
				cout<<s[i]<<"\n";
			}
			exit(0);
		}
	}
	for (int i=1;i<=3;i++){
		len[pos]=i;
		dfs(pos+1);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>k>>n;
	for (int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
	}
	dfs(1);
	
	
	return 0;
}
```

---

