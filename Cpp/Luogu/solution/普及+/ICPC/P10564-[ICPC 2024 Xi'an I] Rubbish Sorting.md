# [ICPC 2024 Xi'an I] Rubbish Sorting

## 题目描述

Bob 有很多垃圾。有一天，他想要对它们进行分类。

对于每一件垃圾，其类型用一个正整数表示。

他有 $q$ 个操作。对于每个操作，可能是以下两种操作之一。

- `1 s x` 他告诉你，名为 $s$ 的垃圾类型为 $x$。
- `2 s` 他想询问你垃圾 $s$ 的类型。

但他的记忆并不总是准确的。

对于每个操作 $2$，$s$ 可能没有在之前的操作 $1$ 中出现过。

我们定义两个字符串 $s_1$ 和 $s_2$ 的相似度为 $\sum_{i=1}^{\min\{|s_1|,|s_2|\}} [s_{1,i}=s_{2,i}]$。

这里所有字符串的索引从 $1$ 开始。

对于一个字符串 $s$，其类型是与 $s$ 相似度最大的字符串的类型，在所有之前操作 $1$ 中出现过的字符串中。如果有多个字符串与 $s$ 的相似度都最大，那么 $s$ 的类型是这些字符串类型中的最小值。

现在，他希望你解决这个问题。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4
1 aaa 1
2 aa
1 ab 2
2 bb```

### 输出

```
1
2```

## 样例 #2

### 输入

```
```

### 输出

```
```

# 题解

## 作者：M1saka16I72 (赞：2)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-p10564.html)

## 思路

观察到 $|s|$ 只有 $5$，于是考虑状态压缩。

可以枚举一个位数为当前字符串长度的二进制数 $st$，每一位代表这一位是否进行匹配。然后我们就可以根据 $st$ 再进行一次状压，把字符串压成一个 $27$ 进制的数，每一位 $\geq 1$ 时代表字母，是 $0$ 则代表这一位没有被匹配。这个数的最大大小为 $\sum^{4}_{i=0}26^i<1.5\times 10^6$，可以直接开数组统计。

插入时，我们把字符串对应的所有状态曾经对应过的 $x$ 取 $\min$，查找时按匹配度从大到小查询，如果当前答案不为 inf 就直接输出，这题就做完了，复杂度 $\mathcal{O}(2^{|s|}|s|\times q)。$

## 代码

```cpp
constexpr int N = 15e6;

int m[N];
vector<int> S[6];

inline int id(int st,string s){
	for(int i=s.length();i<5;i++){
		if(st>>i&1)	return -1;
	}
	int res = 0,b = 1;
	for(int i=0;i<s.length();i++){
		if(st>>i&1)	res+=b*(s[i]-'a'+1);
		b*=27;
	}
	return res;
}

void solve(){
	for(int i=0;i<(1<<5);i++)	S[__builtin_popcount(i)].pb_(i);
	int q;cin>>q;
	while(q--){
		int op;string s;cin>>op>>s;
		if(op==1){
			int x;cin>>x;
			for(int l=0;l<=s.length();l++){
				for(int st:S[l]){
					int now = id(st,s);
					if(now==-1)	continue;
					if(!m[now] || m[now]>x)	m[now] = x;
				}
			}
		}
		else{
			for(int l=s.length();l>=0;l--){
				int res = inf;
				for(int st:S[l]){
					int now = id(st,s);
					if(now==-1)	continue;
					if(m[now]){res = min(res,m[now]);}
				}
				if(res<inf){cout<<res<<"\n";break;}
			}
		}
	}
}
```

---

## 作者：yywlp (赞：2)

~~差点没过的卡常做法~~

观察到 $1\le |s|\le 5$。

也就是说一个字符串的子序列个数最多有这么多种：

$$\binom{5}{0}+\binom{5}{1}+\binom{5}{2}+\binom{5}{3}+\binom{5}{4}+\binom{5}{5}=32$$

有什么用呢？我们看看题目中对相似度的描述：

$$\sum_{i=1}^{\min\{|s_1|,|s_2|\}} [s_{1,i}=s_{2,i}]$$

用人话说就是**对应位置字符相同的个数**。

不难想到既然只有 $32$ 种那不妨开个 `unordered_map` 把字符的每个子序列都存一下，这样找的时候也就可以通过从大到小枚举子序列的大小保证相似度最高了。

同时，为了保证**位置对应**我们把空出来的地方随便填一个特殊符号即可，`*?#&` 随便什么都行。

最后的复杂度为 $\Theta(q)$，有一个 $32$ 的常数，还有一点 `unordered_map` 的常数，蒟蒻稍微卡常才过（哭）。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
int q;
unordered_map<string,int>p;
int f[6];
string s;
int len,x;
int ans;
int res;
inline void dfs(int u,int m,int last,int pd){
	if(u==m+1){
		string nn="";
		for(re int i=1;i<=m;i++){
			for(re int j=f[i-1]+1;j<f[i];j++)nn+='*';
			nn+=s[f[i]-1];
		}
		int nlen=nn.size();
		for(re int i=1;i<=5-nlen;i++)nn+='*';
		if(pd==1){
			if(!p[nn])p[nn]=x;
			else p[nn]=min(p[nn],x);
		}else{
			if(p[nn])ans=min(ans,p[nn]);
		}
		return;
	}
	for(re int i=last;i<=len;i++){
		if(len-i<m-u)break;
		f[u]=i;
		dfs(u+1,m,i+1,pd);
		
	}
}
void write(int x) {
	static int sta[35];
	int top = 0;
	do {
		sta[top++] = x % 10, x /= 10;
	} while (x);
	while (top) putchar(sta[--top] + 48); 
}
signed main(){
//	freopen("temp.in","r",stdin);
//	freopen("temp.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>q;
	while(q--){
		int op;
		cin>>op>>s;
		len=s.size();
		if(op==1){
			cin>>x;
			for(re int i=0;i<=len;i++)dfs(1,i,1,1);
		}else{
			ans=1e9+1;
			for(re int i=len;i>=0;i--){
				dfs(1,i,1,0);
				if(ans!=1e9+1)break;
			}
			write(ans);
			putchar('\n');
		}
	}
	return 0;
}
```

---

