# String Mark

## 题目描述

At the Byteland State University marks are strings of the same length. Mark $ x $ is considered better than $ y $ if string $ y $ is lexicographically smaller than $ x $ .

Recently at the BSU was an important test work on which Vasya recived the mark $ a $ . It is very hard for the teacher to remember the exact mark of every student, but he knows the mark $ b $ , such that every student recieved mark strictly smaller than $ b $ .

Vasya isn't satisfied with his mark so he decided to improve it. He can swap characters in the string corresponding to his mark as many times as he like. Now he want to know only the number of different ways to improve his mark so that his teacher didn't notice something suspicious.

More formally: you are given two strings $ a $ , $ b $ of the same length and you need to figure out the number of different strings $ c $ such that:

1\) $ c $ can be obtained from $ a $ by swapping some characters, in other words $ c $ is a permutation of $ a $ .

2\) String $ a $ is lexicographically smaller than $ c $ .

3\) String $ c $ is lexicographically smaller than $ b $ .

For two strings $ x $ and $ y $ of the same length it is true that $ x $ is lexicographically smaller than $ y $ if there exists such $ i $ , that $ x_{1}=y_{1},x_{2}=y_{2},...,x_{i-1}=y_{i-1},x_{i}<y_{i} $ .

Since the answer can be very large, you need to find answer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample from string $ abc $ can be obtained strings $ acb,bac,bca,cab,cba $ , all of them are larger than $ abc $ , but smaller than $ ddd $ . So the answer is $ 5 $ .

In second sample any string obtained from $ abcdef $ is larger than $ abcdeg $ . So the answer is $ 0 $ .

## 样例 #1

### 输入

```
abc
ddd
```

### 输出

```
5
```

## 样例 #2

### 输入

```
abcdef
abcdeg
```

### 输出

```
0
```

## 样例 #3

### 输入

```
abacaba
ubuduba
```

### 输出

```
64
```

# 题解

## 作者：fisheep (赞：1)

## 想法：
首先吐槽一下翻译，虽然基本翻译的没啥问题，但是你不把$mod$告诉我们就很棒。~~(怀疑你是一个专门搞翻译的)~~。

言归正传，题中给你串$a$串$b$，问用$a$的排列生成新串$c$满足字典序$a<c<b$的串$c$种类数

问题转化成问$f(s)$,$f(s)$表示用已有字符构建的字符串字典序上小于$s$，答案就是$f(b)-f(a)-1$

这样一转化就不用枚举两个字典序变化点了。。

然后$i$枚举字典序变化点，$j$枚举字符集

由于字典序变化点越靠后贡献越小，所以维护一个$cur$表示当前可用字符生成的不同字符串个数，

每当决定一个字符，$cur$就要除掉剩下字符的个数，再乘上这个要用的字符的剩余个数。

## Code:
```cpp
#include<cstdio>
#include<algorithm>  
#include<queue>  
#include<cstring>  
#include<iostream>    
#include<set>  
#include<map>  
#include<vector>    
using namespace std;  
#define ll long long  
const int inf=0x3f3f3f3f;
const int maxn=1e6+5;
const int mod=1e9+7;

int n;
char a[maxn],b[maxn];
int cnt[26],c[26];
int f[maxn],rf[maxn],sr[maxn];

int f1(char *s){
	memcpy(c,cnt,sizeof c);
	int cur=f[n];
	for(int i=0;i<26;i++){
		if(c[i])
			cur=1ll*cur*rf[c[i]]%mod;
	}
	//cur是剩下字符可构成字符串种数
	int ans=0;
	for(int i=1;i<=n;i++){	//枚举不同位置
		for(int x=0;x<s[i]-'a';x++){
			if(c[x]){		//枚举比他小的字符
				int now=cur;
				now=1ll*now*sr[n-i+1]%mod;	//选定一种字符
				now=1ll*now*c[x]%mod;				//选哪一个
				ans=(ans+now)%mod;
			}
		}
		if(c[s[i]-'a']){
			cur=(ll)cur*sr[n-i+1]%mod;
			cur=(ll)cur*c[s[i]-'a']%mod;
			c[s[i]-'a']--;
		}else{
			break;
		}
	}
	return ans;
}

int rev(int a){//逆元 
	int ret=1;
	for(int b=mod-2;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ret=(ll)ret*a%mod;
	return ret;
}

int main(){
	f[0]=rf[0]=1;
	for(int i=1;i<maxn;i++){
		f[i]=(ll)i*f[i-1]%mod;
		sr[i]=rev(i);
		rf[i]=(ll)sr[i]*rf[i-1]%mod;
	}
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);
	for(int i=1;i<=n;i++){
	cnt[a[i]-'a']++;
	}
	printf("%d\n",(f1(b)-f1(a)-1+mod)%mod);
}
```

---

