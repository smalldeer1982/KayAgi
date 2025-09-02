# Evolution of Weasels

## 题目描述

A wild basilisk just appeared at your doorstep. You are not entirely sure what a basilisk is and you wonder whether it evolved from your favorite animal, the weasel.

How can you find out whether basilisks evolved from weasels? Certainly, a good first step is to sequence both of their DNAs. Then you can try to check whether there is a sequence of possible mutations from the DNA of the weasel to the DNA of the basilisk.

Your friend Ron is a talented alchemist and has studied DNA sequences in many of his experiments. He has found out that DNA strings consist of the letters A, B and C and that single mutations can only remove or add substrings at any position in the string (a substring is a contiguous sequence of characters). The substrings that can be removed or added by a mutation are AA, BB, CC, ABAB or BCBC. During a sequence of mutations a DNA string may even become empty.

Ron has agreed to sequence the DNA of the weasel and the basilisk for you, but finding out whether there is a sequence of possible mutations that leads from one to the other is too difficult for him, so you have to do it on your own.

## 样例 #1

### 输入

```
8
A
B
B
C
C
A
AA
BB
BB
CC
CC
AA
ABAB
BCBC
ABC
CBA```

### 输出

```
NO
NO
NO
YES
YES
YES
YES
NO```

# 题解

## 作者：enucai (赞：4)

## Analysis

以下用 $\rightarrow$ 表示通过转化得到，不难发现所有的 $\rightarrow$ 都是 $\leftrightarrow$。称题目中的 $u$ 为 $S$，$v$ 为 $T$。

---

**引理 A**：$\texttt{AB}\leftrightarrow\texttt{BA}$，$\texttt{BC}\leftrightarrow\texttt{CB}$。

**证明**：$\texttt{AB}\leftrightarrow\texttt{AABABB}\leftrightarrow\texttt{BA}$，$\texttt{BC}\leftrightarrow\texttt{BBCBCC}\leftrightarrow\texttt{CB}$。

---

**引理 B**：若 $S$ 与 $T$ 通过变换后相等，则 $S$ 一定能通过若干变换变为 $T$。

**证明**：由于变换操作是可逆的，结论显然。

因此问题变为：判断 $S$ 与 $T$ 能否通过变换而相等。

---

### Step 1.

由 **引理 A**：$\texttt{B}$ 字符在串中的位置是可以任意改变的，且改变后所有 $\texttt{A}$ 与 $\texttt{C}$ 的相对位置关系不变。

所以不妨将所有的 $\texttt{B}$ 转移到串的最后，并将存在的 $\texttt{BB}$ 删除，得到的串**最多**只会在串末出现出现一个 $\texttt{B}$。

若 $S$ 与 $T$ 中 $\texttt{B}$ 的数量**奇偶性**不同，则答案为 `NO`，否则可将所有 $\texttt{B}$ 删除，得到只由 $\texttt{A,C}$ 构成的串 **或** 两个串末尾都有且仅有 $1$ 个 $\texttt{B}$，除最后一位外得到只由 $\texttt{A,C}$ 构成的串。

### Step 2.

由于 $\texttt{A}$ 与 $\texttt{C}$ 之间没有直接的变换，所以两个字符是相对独立的。接下来我们**贪心**删除最大数量的 $\texttt{AA}$ 与 $\texttt{CC}$。

贪心可以用**栈**来实现，类似于括号匹配思路 $^{[1]}$。若字符串 $\texttt{P}$ 能被删空，则 $\texttt{AAP,APA,PAA,CCP,CPC,PCC}$ 都可以被删空。用一个**栈**维护当前待匹配字符。枚举到一个字符 $u$，若与栈顶字符相同，则弹出栈顶字符；若不相同，则将该字符压入栈中。

$^{[1]}$ 括号匹配中，若括号串 $\texttt{P}$ 合法，则 $\texttt{()P,(P),P()}$ 都合法。用栈实现的方法略。

最后未能被匹配的字符构成的串即为 ⌈ **最简化简串** ⌋。只需判断两个串的 ⌈ **最简化简串** ⌋ 是否相等即可。

## Code

[Codeforces Status](https://codeforces.com/contest/1662/submission/154919176)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
int n,m,top;
char s[210],t[210],stk[210];
void work(){
	cin>>(s+1)>>(t+1);
	n=strlen(s+1),m=strlen(t+1);
	int cnt1=0,cnt2=0;
	For(i,1,n) if(s[i]=='B') cnt1++;
	For(i,1,m) if(t[i]=='B') cnt2++;
	if(cnt1%2!=cnt2%2) {cout<<"NO\n";return;}
	string S="",T="";
	top=0;
	For(i,1,n) if(s[i]!='B'){
		if(top&&stk[top]==s[i]) top--;
		else stk[++top]=s[i];
	}
	while(top) S+=stk[top--];
	top=0;
	For(i,1,m) if(t[i]!='B'){
		if(top&&stk[top]==t[i]) top--;
		else stk[++top]=t[i];
	}
	while(top) T+=stk[top--];
	if(S==T) cout<<"YES\n";
	else cout<<"NO\n";
}
signed main(){
	int T;cin>>T;
	while(T--) work();
}
```

---

## 作者：hgcnxn (赞：0)

## CF1662D Evolution of Weasels题解

### 思路

题目等价于两个字符串能不能变换到同一种状态。

考虑以下几种变换：

`BA`$\rightarrow$`BBABAA`$\rightarrow$`AB`

`BC`$\rightarrow$`BBCBCC`$\rightarrow$`CB`

**所以我们可以把所有的 `B` 移到字符串的最后面。**

由于我们可以删除两个相邻的 `B`，所以如果两个字符串中 `B` 的个数的奇偶性不同，一定无解。

接下去观察剩下的由 `A` 和 `C` 构成的前缀。在把所有 `AA` 及 `CC` 删除后，如果它们的前缀不一样，那么一定无解，否则它们都能转变为当前字符串，有解。其中删除的过程可以用栈实现。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,f,la,lb,suma,sumb;
string a,b;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a>>b;
		suma=sumb=f=0;
		la=a.length(),lb=b.length();
		stack<char>sta,stb;
		for(int i=0;i<la;i++){
			if(a[i]=='B')suma++;
			else{
				if(!sta.empty()&&sta.top()==a[i])sta.pop();
				else sta.push(a[i]);
			}
		}
		for(int i=0;i<lb;i++){
			if(b[i]=='B')sumb++;
			else{
				if(!stb.empty()&&stb.top()==b[i])stb.pop();
				else stb.push(b[i]);
			}
		}
		if((suma+sumb)%2==1){
			cout<<"NO\n";
			continue;
		}
		while(!sta.empty()&&!stb.empty()){
			if(sta.top()!=stb.top()){
				f=1;
				break;
			}
			sta.pop();
			stb.pop();
		}
		if(!sta.empty()||!stb.empty()||f==1)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}

```

---

## 作者：Wings_of_liberty (赞：0)

# 分析
对于这道题，我们很容易能找到以下性质：  
1.对于 $\texttt{AB}$ 我们可以在中间插入一个 $\texttt{ABAB}$ 变成 $\texttt{AABABB}$ ，消去前面的 $\texttt{AA}$ 和后面的 $\texttt{BB}$  我们发现 $\texttt{AB}$ 变成了 $\texttt{BA}$ ，同时，在 $\texttt{BA}$ 后插入 $\texttt{ABAB}$ 变成 $\texttt{BAABAB}$ ，消去一个 $\texttt{AA}$ 再消去一个 $\texttt{BB}$ ， $\texttt{BA}$ 就会变成 $\texttt{AB}$ 。  

2.同理， $\texttt{BC}$ 和 $\texttt{CB}$ 也可以进行转化，换句话说，我们可以讲所有的 $\texttt{B}$ 移动到整个序列的后面，然后直接看奇偶就可以判断 $\texttt{B}$ 。  

3.接着，由于 $\texttt{ACAC}$ 不存在，所以说 $\texttt{A}$ 与 $\texttt{C}$ 的位置是不能变的，所以我们只需用一个栈来判断，也可以用字符串，效果一样
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout) 
string s1,s2;
int l1,l2;
int b1,b2;
string st1,st2;
char tmp;
inline void init(){
	cin>>s1>>s2;
	l1=s1.length();
	l2=s2.length();
	b1=0,b2=0;
	st1.clear();
	st2.clear();
}
bool check(){
	b1=b1&1;
	b2=b2&1;
	return b1==b2;
}
inline void work(){
	for(int i=0;i<l1;i++){
		if(s1[i]=='B'){
			b1++;
			continue;
		}
		if(!st1.empty()){
			tmp=st1.back();
			if(tmp==s1[i]){
				st1.pop_back();
				continue;
			}
		}
		st1.push_back(s1[i]);
	}
	for(int i=0;i<l2;i++){
		if(s2[i]=='B'){
			b2++;
			continue;
		}
		if(!st2.empty()){
			tmp=st2.back();
			if(tmp==s2[i]){
				st2.pop_back();
				continue;
			}
		}
		
		st2.push_back(s2[i]);
	}
	if(st1==st2&&check()){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
}
int main(){
//	op("abc");
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		init();
		work();
	}
//	cl();
	return 0;
}
```


---

## 作者：wheneveright (赞：0)

## 题意

每组数据给出两个由 `ABC` 组成的字符串，问是否可以通过移除或添加子串 `AA`、`BB`、`CC`、`ABAB` 或 `BCBC` 使第一个字符串变为第二个字符串。

## 分析

首先我们知道，将第一个字符串变为第二个字符串等价于把两个字符串变成相同的一个字符串。

考虑字符串 `BABA` 可以通过以下的改变：`BABA` $\to$ `AABABA` $\to$ `AA`。

所以 `BABA` 也是可以移除或添加的子串，同理 `CBCB` 也是。

然后我们可以发现对于任意的 `BXB` 类型的字符串（`X` 代表任意一种字符），可以通过如下改变：`BXB` $\to$ `XXBXB` $\to$ `X`。

再发现对于任意的 `BXXXXB` 类型的字符串，可以通过以下的改变：`BXXXXB` $\to$ `BXBBXBBXBBXB` $\to$ `XXXX`。

根据这个结论，我们可以在字符串中任意添加或减少偶数数量的 `B`，因为我们的目标是让两个字符串相同，那么队友有偶数个 `B` 的字符串可以将 `B` 全部移除，有奇数个就考虑将最后一个 `B` 留下到最后一位。

这样处理之后只要贪心得将剩余字符串中的 `AA` 和 `CC` 子串全部去除，用栈模拟即可，最后只要判断两个字符串做下来是否相同。

[代码不做解释](https://codeforces.com/contest/1662/submission/155021245)。

---

