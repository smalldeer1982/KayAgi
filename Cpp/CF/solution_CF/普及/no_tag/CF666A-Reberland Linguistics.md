# Reberland Linguistics

## 题目描述

First-rate specialists graduate from Berland State Institute of Peace and Friendship. You are one of the most talented students in this university. The education is not easy because you need to have fundamental knowledge in different areas, which sometimes are not related to each other.

For example, you should know linguistics very well. You learn a structure of Reberland language as foreign language. In this language words are constructed according to the following rules. First you need to choose the "root" of the word — some string which has more than $ 4 $ letters. Then several strings with the length $ 2 $ or $ 3 $ symbols are appended to this word. The only restriction —  it is not allowed to append the same string twice in a row. All these strings are considered to be suffixes of the word (this time we use word "suffix" to describe a morpheme but not the few last characters of the string as you may used to).

Here is one exercise that you have found in your task list. You are given the word $ s $ . Find all distinct strings with the length $ 2 $ or $ 3 $ , which can be suffixes of this word according to the word constructing rules in Reberland language.

Two strings are considered distinct if they have different length or there is a position in which corresponding characters do not match.

Let's look at the example: the word $ abacabaca $ is given. This word can be obtained in the following ways: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666A/db0a6930c8ac7df2b263a19be9a4e03f20d4a6b4.png), where the root of the word is overlined, and suffixes are marked by "corners". Thus, the set of possible suffixes for this word is $ {aca,ba,ca} $ .

## 说明/提示

The first test was analysed in the problem statement.

In the second example the length of the string equals $ 5 $ . The length of the root equals 5, so no string can be used as a suffix.

## 样例 #1

### 输入

```
abacabaca
```

### 输出

```
3
aca
ba
ca
```

## 样例 #2

### 输入

```
abaca
```

### 输出

```
0
```

# 题解

## 作者：Froggy (赞：3)

### 一道~~很裸~~的DP

* 状态：dp[i][0/1]表示以i位置开始的2/3子串能否作为合法“后缀”

* 转移：

1. 当i+2/3==n时，显然，dp[i][0/1]=1;

2. 当dp[i+2][1]==1时，说明可以接成一段3一段2，**相邻两个永远不会相同**，此时dp[i][0]=1;同理当dp[i+3][0]==1时，dp[i][1]=1;

3. 当dp[i+2][0]==1时，说明要结成一段2和一段2，此时**要判断两子串是否相同**来判断dp[i][0]；当dp[i+3][1]==1时，同理

* 统计：可以开个set去重

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
using namespace std;
#define N 100010
set<string> frogs;//一些“青蛙”，可以去重
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
string s,tmp; 
int dp[N][2];
int main(){
	freopen("suffix.in","r",stdin);
	freopen("suffix.out","w",stdout);
	cin>>s;
	int len=s.length();
	for(int i=len-1;i>=5;i--){
		if(i+2==len)dp[i][0]=1;
		if(i+3==len)dp[i][1]=1;
		if(i+2<len){
			if(dp[i+2][1])dp[i][0]=1;
			if(dp[i+2][0]&&(s[i+1]!=s[i+3]||s[i]!=s[i+2]))dp[i][0]=1;
		}
		if(i+3<len){
			if(dp[i+3][0])dp[i][1]=1;
			if(dp[i+3][1]&&(s[i+1]!=s[i+4]||s[i+2]!=s[i+5]||s[i]!=s[i+3]))dp[i][1]=1;
		}
	}
	for(int i=len-1;i>=5;i--){
		if(dp[i][0])frogs.insert(s.substr(i,2));
		if(dp[i][1])frogs.insert(s.substr(i,3));
	}
	cout<<frogs.size()<<endl;
	for(set<string>::iterator it=frogs.begin();it!=frogs.end();++it){
		cout<<(*it)<<endl;
	}
	return 0;
}

```



---

## 作者：sto__Liyhzh__orz (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF666A)

~~题目编号666，6。~~

### 一道~~很裸~~的DP

状态转移方程：

1. 当 $i+2 = n$ 时，$dp[i][0] \gets 1$。

   当 $i+3= n$ 时，$dp[i][1] \gets 1$。
   
   自证不难。
   
2. 当 $dp[i+2][1]=1$，可以截成一节 $2$，一节 $3$，永远不会相同，所以 $dp[i][0]\gets1$。
   
   同理，$dp[i+3][0]\gets 1$，$dp[i][1]\gets1$。
   
3. 当 $dp[i+2][0]=1$，要截成两节 $2$，现在对于$dp[i][0]$，需要判断两子串是否相同。

可以用个 `set` 去重。

---

