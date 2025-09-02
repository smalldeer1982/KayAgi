# Saraga

## 题目描述

在印尼语中，"sarana olahraga" 是体育设施的意思，缩写为 "saraga"。这个缩写可以通过两种不同的方式组合而成：一种是取 "sarana" 的前缀 "sara" 和 "olahraga" 的后缀 "ga"；另一种是取 "sarana" 的前缀 "sa" 和 "olahraga" 的后缀 "raga"。

如果一个字符串 $S$ 和 $T$ 的缩写有至少两种不同的分割方法，且这些分割能得到一个字符串，使得第一个部分是 $S$ 的前缀，第二个部分是 $T$ 的后缀，我们就称这个缩写是有趣的。

现在，给定两个字符串 $S$ 和 $T$，你需要找出一个最短的有趣缩写，或者判断是否无法构造这样的缩写。

## 说明/提示

样例 1 的解释：

字符串 "saga" 可以分割为 "s" 和 "aga"，或者 "sa" 和 "ga"。因此，"saraga" 和 "saga" 都是有趣的缩写，但 "saga" 更短。

样例 2 的解释：

缩写 "belhijau" 也是一个最短的有趣缩写，所以这个解也是有效的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
sarana
olahraga```

### 输出

```
saga```

## 样例 #2

### 输入

```
berhiber
wortelhijau```

### 输出

```
berhijau```

## 样例 #3

### 输入

```
icpc
icpc```

### 输出

```
icpc```

## 样例 #4

### 输入

```
icpc
jakarta```

### 输出

```
-1```

# 题解

## 作者：siiii (赞：3)

## 题目分析
仔细观察样例，不难发现有趣字符串只需要满足该字符串前缀的最后一个字母与后缀第一个字母所在原位置的前一个字母相同即可。这样一来问题就变成了有趣字符串到底存不存在，以及如何找到最短的有趣字符串。
#### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

int st[300];//存取S字符串中各字符最早出现的位置 
char s[200100],t[200100];
int main(){
	int m=0;//判断存不存在有趣字符串 
	
	cin>>s>>t;
	
	int s1=strlen(s),t1=strlen(t);

	for(int i=1;i<s1;i++){
		if(st[s[i]]==0)//用来记录最早出现的位置 
		st[s[i]]=i;
	}

	char q;
	int Min=500010,ans=0;
	for(int i=t1-2;i>=0;i--){
		if(st[t[i]]&&st[t[i]]+t1-i<Min){
//st[t[i]]+t1-i为该有趣字符串的长度st[t[i]]为该字符串在s中最早出现的位置

/*按理来说字符t[i-1]（至于为什么是i-1是因为两个相同的字符，前缀后缀中取一个即可。这里我们去后缀中相同的字符）
在S中所对应的前缀长为st[t[i]]+1,同理 t[i]在t中所对应的后缀长为
t1-(i+1),+1，-1相互抵消，故有了原式 
*/
 
			Min=st[t[i]]+t1-i;
			ans=i;
			m=1;
			q=t[i];
		}
	}
	if(m){
		for(int i=0;i<st[q];i++)cout<<s[i];
		for(int i=ans;i<t1;i++)cout<<t[i];	
	}else cout<<-1;
}
```

---

## 作者：lfxxx (赞：1)

不妨答案串等于 $S[1,i] + T[j,n]$ 与 $S[1,i+\Delta] + T[j+\Delta,n]$。

你发现其之所以能构成答案是因为 $S[i+1,i+\Delta] = T[j+1,j+\Delta]$。你发现次数答案串的长度为 $i+n-j+1$，和 $\Delta$ 居然无关！

于是尽可能的让判定变松是不劣的，取 $\Delta = 1$，枚举 $S[i+1,i+1] = T[j+1,j+1] = ch$，记录下 $S$ 中以字符 $ch$ 结尾的最短前缀与 $T$ 中以字符 $ch$ 开头的最短后缀拼起来即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[26],suf[26];
string S,T;
int ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(pre,0x3f3f3f3f,sizeof(pre));
    memset(suf,0x3f3f3f3f,sizeof(suf));
    cin>>S>>T;
    for(int i=2;i<=S.size();i++){
        if(pre[S[i-1]-'a']==0x3f3f3f3f) pre[S[i-1]-'a']=i;
    }
    for(int i=T.size()-1;i>=1;i--){
        if(suf[T[i-1]-'a']==0x3f3f3f3f) suf[T[i-1]-'a']=T.size()-i+1;
    }
    ans=0x3f3f3f3f;
    for(int i=0;i<26;i++){
        ans=min(ans,pre[i]+suf[i]);
    }
    if(ans>=0x3f3f3f3f){
        cout<<"-1\n";
    }else{
        for(int i=0;i<26;i++){
            if(pre[i]+suf[i]==ans){
                for(int j=1;j<=pre[i];j++) cout<<S[j-1];
                for(int j=T.size()-suf[i]+2;j<=T.size();j++) cout<<T[j-1];
                return 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

如果没有任何一个字母两个字符串都有就是无解。

然后枚举 $S[i + 1, i + 1] = T[j + 1, j + 1] = c$，记录下 $S$ 中以字符 $c$ 结尾的最短前缀与 $T$ 中以字符 $c$ 开头的最短后缀拼起来即可。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 26 + 10, INF = 0x3f3f3f3f;
int a[MAXN], b[MAXN], ans = INF;
string S, T;
int main () {
    memset (a, INF,sizeof(a)); memset (b, INF,sizeof(b));
    cin >> S >> T;
    for (int i = 2; i <= S.size (); i ++) 
        if (a[S[i - 1] - 'a'] == INF) a[S[i - 1] - 'a'] = i;
    for (int i = T.size () - 1; i >= 1; i --)
        if (b[T[i - 1] - 'a'] == INF) b[T[i - 1] - 'a'] = T.size () - i + 1;
    for (int i = 0; i < 26; i ++) ans = min (ans, a[i] + b[i]);
    if (ans >= INF) cout << -1 << endl;
    else {
        for (int i = 0; i < 26; i ++) {
            if (a[i] + b[i] == ans) {
                for (int j = 1; j <= a[i]; j ++) cout << S[j - 1];
                for (int j = T.size () - b[i] + 2; j <= T.size (); j ++) cout << T[j - 1];
                cout << endl;
                return 0;
            }
        }
    }
    return 0;
}
```

---

