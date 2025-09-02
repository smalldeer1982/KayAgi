# Field of Wonders

## 题目描述

Polycarpus参加了一个电视节目，节目的参与者的任务是尽快猜出一个完全未知的单词。

节目中，每位参与者会轮流说出一个字母，主持人会回答这个词中是否有这样的字母。如果有，那么主持人就会透露单词中所有与它相同的字母。例如，如果未知的单词是 $"abacaba"$，参与者说出了字母 $a$，主持人就会展示单词中所有字母 $a$ 的下标 $:1,3,5,7$（下标从$1$开始，从左至右）。

Polycarpus知道 $m$ 个单词，这 $m$ 个单词的长度与未知单词的长度相同。他也知道，这个未知的单词，是这些 $m$ 个单词中的一个。

节目已经进行了若干轮，未知单词的一些字母（可能没有）已经知道了，且Polycarpus能够准确地说出目前已知的字母。

现在该Polycarpus说字母了。他想说出一个字母，使得主持人一定会透露至少一个字母。但是，Polycarpus无法分辨这些已经知道的字母。你的任务是帮助Polycarpus，找出他能说的字母，使得节目主持人一定会透露至少一个未知的字母。

## 样例 #1

### 输入

```
4
a**d
2
abcd
acbd
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
lo*er
2
lover
loser
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
a*a
2
aaa
aba
```

### 输出

```
1
```

# 题解

## 作者：lixianyuan (赞：0)

# 题意
题目链接：
[洛谷](https://www.luogu.com.cn/problem/CF883E) 
[Codeforces](https://codeforces.com/problemset/problem/883/E)\
主持人给你一个完全未知的单词，当你每说出一个字母，你就会知道字符串 $s$ 中所有与它相同的字母的下标。现在已经进行了若干轮，未知单词的一些字母（可能没有）你已经知道了，你也知道这个未知的单词，是 $m$ 个单词 $t_i$ 中的一个。你想说出一个字母，使得主持人至少会透露一个字母。问可以说多少字母。
# 思路
模拟即可。如果未知字母以外的字母不对应或 $t_i$ 的字母在已知 $s$ 里已经出现过则不计算答案。否则每输入一个 $t_i$ 就将答案之外的字母排除，最后计算还剩多少个字母。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int tmp,n,m,ans;
map<char,int>st,t1,num;
void work(){
	string t;cin>>t;
	bool b=1;
	for(int i=0;i<n;i++){	//判断是否符合计算条件 
		if(s[i]!='*'&&t[i]!=s[i]){
			b=0;
			break;
		}
		else if(s[i]=='*'&&st[t[i]]==-1){
			b=0;
			break;
		}
	}
	if(b){	//计算 
		tmp++;
		t1.clear();
		for(int i=0;i<n;i++){
			if(s[i]=='*'){
				t1[t[i]]=1;
			}
		}
		for(char i='a';i<='z';i++){
			if(t1[i]!=1){
				num[i]=0;
			}
		}
	}
} 
int main(){
	cin>>n>>s>>m;
	for(int i=0;i<n;i++){	//标记已知字母 
		if(s[i]!='*'){
			st[s[i]]=-1;
		}
	}
	for(char i='a';i<='z';i++){
		num[i]=1;
	}
	while(m--){
		work();
	}
	for(char i='a';i<='z';i++){		//计算答案 
		ans+=num[i];
	}
	cout<<ans;
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/h0jf1c4o.png)

---

## 作者：rq_kyz (赞：0)

# 【题解】 Field of Wonders

### 传送门

[Field of Wonders](https://www.luogu.com.cn/problem/CF883E)

---

### 题意

现有一个长度为 $n$ 的由小写字母组成的未知字符串，你要进行猜测。每次你可以询问一个字母出现的位置，主持人会把这个字母出现的所有位置都告诉你（没有出现就不告诉）。你现在已经猜出一些字母，然后你的心中还有一些备选字符串，你确定正确答案就在这些备选字符串中（备选字符串是完整的）。请问你下一步有多少种询问的可能，使得不管正确答案是哪个，主持人至少回答你一个位置。

---

### 分析

通过样例，我们可以得出条件：

1. 已经猜出来的那些位必须一模一样，不然这个备选串直接排除。

2. 如样例三，当你从什么都不知道到询问成 `a*a` 时，必定要询问 $a$ 这个字符，所以备选的 `aaa` 一定不可能，否则我就已经知道中间是什么字符了。

3. 若我询问字符 $c$，则 $c$ 需要在每个**合法**备选串中（满足以上两个条件），不然万一正确答案就是那个没有出现字符 $c$ 的串，则主持人什么都不会回答我。

这三个条件就是本题的关键，关于实现，详见下面↓↓↓。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
char s[51],s1[51];
ll cd=0;
ll t[26];//存储每个字符出现的次数
int main(){
	ll n,m;
	scanf("%lld\n%s\n%lld",&n,s,&m);
	for(ll i=0;i<n;i++)
		if(s[i]!='*')
			t[s[i]-'a']=-1;//已经猜出的字符一定不可能再次询问
	for(ll i=1;i<=m;i++){
		scanf("\n%s",s1);
		bool b=1;
		for(ll j=0;j<n && b;j++){
			if(s[j]!='*' && s1[j]!=s[j])//第一个条件
				b=0;
			else if(s[j]=='*' && t[s1[j]-'a']==-1)//第二个条件
				b=0;
		}
		if(b){
			cd++;
			bool t1[26]={};
			for(ll j=0;j<n;j++)
				if(s[j]=='*')
					t1[s1[j]-'a']=1;//不能直接加，因为一个字符可能会出现多次
			for(ll j=0;j<26;j++)
				t[j]+=t1[j];//记录
		}
	}
	ll ans=0;
	for(ll i=0;i<26;i++)
		if(t[i]==cd)//第三个条件
			ans++;//统计答案
	printf("%lld",ans);
	return 0;
}
```

---

