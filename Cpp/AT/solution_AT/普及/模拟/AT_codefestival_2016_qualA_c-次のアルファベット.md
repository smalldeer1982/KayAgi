# 次のアルファベット

## 题目描述

# 题意翻译
高桥君有一个仅由小写字母组成的字符串s。高桥君对s执行以下操作正好是k次。在所需位置从字符串s中选择一个字母并将该字母更改为下一个字母。但是,z后面的字母是a。例如，如果选择字符串aaz的第2个字符并执行操作aaz → abz。 然后，如果选择abz的 第3个字符并执行操作，则它变为aba。高桥君 希望在k操作后，按字典顺序使字符串s尽可能小。仅在k次操作后，按字典顺序输出最小的字符串s。

## 说明/提示

设字符串s的长度为n  
+ 1≤n≤100000
+ 1≤k≤1000000000

## 样例 #1

### 输入

```
xyz
4```

### 输出

```
aya```

## 样例 #2

### 输入

```
a
25```

### 输出

```
z```

## 样例 #3

### 输入

```
codefestival
100```

### 输出

```
aaaafeaaivap```

# 题解

## 作者：tuzhewen (赞：2)

### 题目大意:
从$s$中任意选择一个字母，然后将该字母换成下一个字母。特殊的，设$z$的下一个字母是$a$。

例如，选择$aaz$的第$2$个字符进行操作的话，$aaz→abz$。接着，选择$abz$的第3个字进行操作的话，$abz$→$aba$。

现在把操作正好进行了$k$次之后的$s$，按照字典序尽可能地减小。请在正好进行了$k$次操作后的$s$中，输出字典序最小的一个。

### 思路:
显然，要字典序最小，那么只要使得越在前面的越是`a`最好，如果把前面的都变成了`a`但还是能继续变，我们就在最后一个上一直变化，不会影响字典序的大小
```
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
const int INF=0x3f3f3f3f,N=1e5+5;
using namespace std;
char s1[N];
int cnt;
int main() {
	scanf("%s%d",s1+1,&cnt);
	int len=strlen(s1+1);
	F(i,1,len) {
		if(s1[i]=='a') continue;
		else if('a'-s1[i]+26<=cnt) cnt-=('a'-s1[i]+26),s1[i]='a';
	}
	if(cnt) s1[len]=char((int)s1[len]+cnt%26);
	printf("%s\n",s1+1);
	return 0;
}
```

---

