# k-String

## 题目描述

- **题面翻译如下**

如果一个字符串可以被划分为 $k$ 个相同的子串，则称这个字符串为 $k$-string。例如，字符串“aabaabaabaab”同时是 $1$-string, $2$-string和 $4$-string，但它不是 $3$-string, $5$-string 或 $6$-string 等。显然，任何字符串都是 $1$-string。

给你一个由小写英文字母组成的字符串 $s$ 和一个正整数 $k$。你需要将字符串 $s$ 重新排列成一个 $k$-string。

## 样例 #1

### 输入

```
2
aazz
```

### 输出

```
azaz
```

## 样例 #2

### 输入

```
3
abcabcabz
```

### 输出

```
-1
```

# 题解

## 作者：Jμdge (赞：3)

emmm... 原来是水题，找 sam 题误入就 1 A 掉了


# noteskey

读入后记录每个字符出现次数然后判断能否被 k 整除

都能被 k 整除就输出 k 次每种字符除 k 后的个数...

总之很水...（毕竟 CF 题 A ）

# code


```
//by Judge
#include<cstdio>
#include<cstring>
#include<iostream>
#define fp(i,a,b) for(register int i=(a),I=(b)+1;i<I;++i)
using namespace std;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline void reads(string& s){ char c=getchar();
	for(;!isalpha(c);c=getchar()); s=" ";
	for(;isalpha(c);c=getchar()) s+=c;
} char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x,char chr='\n'){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=chr;
} int n,k,num[201]; string s;
int main(){ scanf("%d",&k);
	reads(s),n=s.length()-1;
	fp(i,1,n) ++num[s[i]];
	fp(i,'a','z') if(num[i]%k)
		return !printf("-1\n");
	fp(kkk,1,k) fp(i,'a','z')
		fp(j,1,num[i]/k) sr[++C]=i;
	return Ot(),0;
}
```


---

## 作者：Ninelife_Cat (赞：1)

$k$—字符串的定义：由某个子串重复 $k$ 次形成的字符串。

显然，$k$—字符串中的每个字符出现的次数都是 $k$ 的倍数。

在输入时统计判断该字符串是否为 $k$—字符串。

如果是，最后只要输出 $k$ 个子串就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt[101],tot[101];
//cnt数组记录字符出现次数,tot数组记录每次需要输出字符的个数
string s;
signed main()
{
	cin>>n>>s;
	for(int i=0;i<s.length();i++)
		cnt[s[i]-'a']++;//统计字符出现次数
	for(int i=0;i<=27;i++)
	{
		if(cnt[i]!=0&&cnt[i]%n!=0) {cout<<-1;return 0;}
        	//如果某个字符出现次数不是k的倍数,说明它不是k—字符串
		tot[i]=cnt[i]/n;
	}	
	while(1)
	{
		bool flag=0;//flag记录是否有输出
		for(int i=0;i<=27;i++)
			if(cnt[i]!=0) 
				for(int j=1;j<=tot[i];j++)
					cout<<char(i+'a'),cnt[i]--,flag=1;//输出子串
		if(!flag) break;//如果已经全部输出完毕,结束循环
	}
	return 0;
}

---

## 作者：lsr1409111459 (赞：0)

#### 1 题目描述

（[传送门](https://www.luogu.com.cn/problem/CF219A)）

洛谷有翻译，不做描述。点链接查看即可。

#### 2 解题思路

记录每个字母出现的次数，如果都能被 $k$ 整除，则分别除 $k$ 并组合成一个子串，输出 $k$ 次即可；否则说明不能满足要求，输出 ``-1`` 。

#### 3 解题代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;
char s[1010];
int cnt[30],k;
char ans[1010],len=0;
int main()
{
    scanf("%d%s",&k,s);
    for(int i=0;i<strlen(s);i++)cnt[s[i]-'a'+1]++;
    bool flag=true;
    for(int i=1;i<=26;i++)
    {
        if(cnt[i]%k!=0)flag=false;
        cnt[i]/=k;
        for(int j=1;j<=cnt[i];j++)
            ans[++len]='a'+i-1;
    }
    if(flag)
    {
        for(int i=1;i<=k;i++)printf("%s",ans+1);
        printf("\n");
    }
    else printf("-1\n");
    return 0;
}
```

#### 4 解题心得

签到题，思路较简单。抓住题目主要信息，注意 SPJ 。

---

## 作者：小杨小小杨 (赞：0)

## 前言
挑战本题最短代码。
## 题意
给你一个字符串，判断是否能通过将这个字符串重新排列的方式使这个字符串变为由 $k$ 个相同字串组成的字符串。能就输出这个字符串，不能就输出 ```-1```。
## 思路
使这个字符串变为由 $k$ 个相同字串组成的字符串，那么就可以看做把每一种字母都平均地分成 $k$ 份，每一份都存在于一个小子串中。那么如何判断这能不能变成由 $k$ 个相同字串组成的字符串呢？只需要判断是否从“a”到“z”每一个字符都是否能被 $k$ 整除即可。如果全能，那么就可以的，一组一组输出即可。如果有一个不能，那么输出 ```-1```。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,i,f[10001],n,j;
char t,ch,s[10001];
int main(){
	scanf("%d",&k);
	scanf("%s",s);n=strlen(s);//读入+取出长度
	for (i=0;i<n;i++) f[s[i]]++;//计数，累计每一个字符出现次数。
	for (ch='a';ch<='z';ch++)
		if (f[ch]%k!=0){printf("-1");return 0;}//判断是否能正好分成k组
	for (ch='a';ch<='z';ch++) f[ch]/=k;//求出每组每一个字符的出现次数
	for (i=1;i<=k;i++){//一组组地输出
		for (ch='a';ch<='z';ch++)//遍历查找，进行输出
			for (j=1;j<=f[ch];j++)
				printf("%c",ch);
	}
	return 0;
}

```


---

