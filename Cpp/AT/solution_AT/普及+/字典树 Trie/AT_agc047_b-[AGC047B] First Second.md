# [AGC047B] First Second

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc047/tasks/agc047_b

リマクは、文字列の先頭 $ 2 $ 文字のうち片方を取り除くことを繰り返し行えます。例えば、$ abcxyx\ \rightarrow\ acxyx\ \rightarrow\ cxyx\ \rightarrow\ cyx $ とすることができます。

$ N $ 個の相異なる文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ が与えられます。$ N\ \cdot\ (N-1)\ /\ 2 $ 個のペア $ (S_i,\ S_j) $ のうち何個において、リマクは一方からもう一方を得ることができるでしょうか。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200\,000 $
- $ S_i $ は英小文字 `a` - `z` からなる。
- $ S_i\ \neq\ S_j $
- $ 1\ \leq\ |S_i| $
- $ |S_1|\ +\ |S_2|\ +\ \ldots\ +\ |S_N|\ \leq\ 10^6 $

### Sample Explanation 1

条件を満たすペアは $ (abcxyx,\ cyx) $ のみです。

### Sample Explanation 2

条件を満たすペアは $ (b,\ abc) $, $ (a,\ abc) $, $ (abc,\ c) $, $ (b,\ ab) $, $ (a,\ ab) $ の $ 5 $ 個です。

## 样例 #1

### 输入

```
3
abcxyx
cyx
abc```

### 输出

```
1```

## 样例 #2

### 输入

```
6
b
a
abc
c
d
ab```

### 输出

```
5```

# 题解

## 作者：zymooll (赞：3)

### 题目大意

对于一组字符串 $\{S_i\}$，求所有 $\sum^{i \le n}_{i=1} S_i$ 删去任意次 $S_{i,1}$ 和 $S_{i,2}$ 后得到的串 $S' \in \{S_i\}$ 的匹配个数。

### 主要思路

可以发现，对于单个字符串删去任意次 $S_{i,1}$ 和 $S_{i,2}$ 后，该字符串会变为四部分，第一部分为被删去段，第二部分为单个字符，第三部分也为被删去段，第四部分为原字符串的后缀。

所以我们可以将 $\{S_i\}$ 按后缀建立字典树，注意在查询时要注意对于第二部分的处理，详细请参见代码。

### 参考代码

```cpp
// Author:zymooll

#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define int long long
using namespace std;
int read(){
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=s*10+c-'0';
		c=getchar();
	}
	return s*w;
}
void print(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>=10)print(x/10);
	putchar(x%10+'0');
	return;
}
const int NMax=2e5;
const int SMax=1e6;
int n;
struct Trie{
    struct Node{
        int tail,son[30];
    }t[SMax+10];
    int ncnt=1;
    void radd(string s){
        int u=1;
        for(int i=s.size()-1;i>=0;i--){
            if(!t[u].son[s[i]-'a'])t[u].son[s[i]-'a']=++ncnt;
            u=t[u].son[s[i]-'a'];
        }
        t[u].tail++;
        return;
    }
    int ask(string s){
        int tot[30];
        memset(tot,0,sizeof(tot));
        for(char i:s)tot[i-'a']++;
        int u=1,ans=0;
        for(int i=s.size()-1;i>0;i--){
            for(int j=0;j<26;j++){
                if(tot[j])ans+=t[t[u].son[j]].tail;
            }
            u=t[u].son[s[i]-'a'];
            tot[s[i]-'a']--;
        }
        return ans;
    }
}T;
vector<string>q;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
    for(int i=1;i<=n;i++){
        q.push_back("");
        cin>>q[i-1];
        T.radd(q[i-1]);
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=T.ask(q[i-1]);
    }
    print(sum);
	return 0;
}

```

### 后记

这题绿还是保守了点，蓝正正好好。

---

