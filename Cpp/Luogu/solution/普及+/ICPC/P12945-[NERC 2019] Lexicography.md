# [NERC 2019] Lexicography

## 题目描述

Lucy 喜欢字母。她在学校学习了字典序的定义，并经常用它来做游戏。

起初，她尝试用给定的字母构造字典序最小的单词。这很简单！然后她尝试构造多个单词，并最小化其中某一个单词的字典序。这就难多了！

具体来说，Lucy 希望用给定的 $n \cdot l$ 个字母构造 $n$ 个长度为 $l$ 的单词，使得这些单词按字典序排列时，第 $k$ 个单词的字典序尽可能小。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3 2 2
abcdef```

### 输出

```
af
bc
ed```

## 样例 #2

### 输入

```
2 3 1
abcabc```

### 输出

```
aab
bcc```

# 题解

## 作者：_Weslie_ (赞：0)

一眼题。

## Solution P12945

### Idea

显然要对原字符数组排序。

考虑贪心：

1. 先填完前 $k$ 个字符串。按照原先的字符数组里的顺序，一个一个加。
2. 显然原先字符数组可能会有相同的字符。所以写一个 dfs，考虑只要出现构造出的 $ans_{i,j}=ans_{k,j}$，就对 $i$ 往后的再填一个字符。这样总会有 $ans_{k-1,j}<ans_{k,j}$ 的情况（或者两者填完了还相同，这就无所谓了）。
3. 对 $ans_k$ 最小字典序的优先：剩下的没填上去的字符直接扔进去。
4. 对 $ans_{k-1}$ 及之前的答案，把字符集里剩下的字符扔进去。
5. 对 $ans_{k+1}$ 及之后的答案，按照排序把字符集扔进去即可。

这个贪心很显然是正确的。我们要 $ans_k$ 最小，很显然就是要 $ans_k$ 前面用掉的字符数量最少，这样 $ans_k$ 就能享用更小的字符。这样的贪心可以保证 $ans_k$ 前面用掉的字符数量最少，没有一个字符被浪费。

### Code

```
#include<bits/stdc++.h>
using namespace std;
int n,l,k;
const int N=1005;
char ch[N*N];
char ans[N][N];
int pos=1;
void dfs(int lst,int w){
	if(w==l+1)return;
	for(int i=lst;i<=k;i++){
		ans[i][w]=ch[pos];//往答案里扔
		pos++;
	}
	int nw=0;
	for(int i=lst;i<=k;i++){
		if(ans[i][w]==ans[k][w]){
			nw=i;//出现第 w 位相同
			break;
		}
	}
	if(nw==k)return;
	dfs(nw,w+1);
} 
int main(){
	cin>>n>>l>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=l;j++)ans[i][j]=' ';
	}
	for(int i=1;i<=n*l;i++){
		cin>>ch[i];
	}
	sort(ch+1,ch+n*l+1);
	dfs(1,1);
	for(int j=1;j<=l;j++){
		if(ans[k][j]==' '){
			ans[k][j]=ch[pos];//保证 ansk 字典序最小
			pos++;
		}
	}
	for(int i=1;i<k;i++){
		for(int j=1;j<=l;j++){
			if(ans[i][j]==' '){
				ans[i][j]=ch[pos];//k 前面的按顺序扔
				pos++;
			}
		}
	}
	for(int i=k+1;i<=n;i++){
		for(int j=1;j<=l;j++){
			ans[i][j]=ch[pos];//k 后面的按顺序扔
			pos++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=l;j++)cout<<ans[i][j];
		cout<<'\n';
	}
}
```

---

