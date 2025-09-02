# Subtle Substring Subtraction

## 题目描述

Alice and Bob are playing a game with strings. There will be $ t $ rounds in the game. In each round, there will be a string $ s $ consisting of lowercase English letters.

Alice moves first and both the players take alternate turns. Alice is allowed to remove any substring of even length (possibly empty) and Bob is allowed to remove any substring of odd length from $ s $ .

More formally, if there was a string $ s = s_1s_2 \ldots s_k $ the player can choose a substring $ s_ls_{l+1} \ldots s_{r-1}s_r $ with length of corresponding parity and remove it. After that the string will become $ s = s_1 \ldots s_{l-1}s_{r+1} \ldots s_k $ .

After the string becomes empty, the round ends and each player calculates his/her score for this round. The score of a player is the sum of values of all characters removed by him/her. The value of $ \texttt{a} $ is $ 1 $ , the value of $ \texttt{b} $ is $ 2 $ , the value of $ \texttt{c} $ is $ 3 $ , $ \ldots $ , and the value of $ \texttt{z} $ is $ 26 $ . The player with higher score wins the round. For each round, determine the winner and the difference between winner's and loser's scores. Assume that both players play optimally to maximize their score. It can be proved that a draw is impossible.

## 说明/提示

For the first round, $ \texttt{"aba"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{ab}}}\texttt{a"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 1+2=3 $ . Bob's total score is $ 1 $ .

For the second round, $ \texttt{"abc"}\xrightarrow{\texttt{Alice}}\texttt{"a}{\color{red}{\texttt{bc}}}\texttt{"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 2+3=5 $ . Bob's total score is $ 1 $ .

For the third round, $ \texttt{"cba"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{cb}}}\texttt{a"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 3+2=5 $ . Bob's total score is $ 1 $ .

For the fourth round, $ \texttt{"n"}\xrightarrow{\texttt{Alice}}\texttt{"n"}\xrightarrow{} \texttt{"n"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{n}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 0 $ . Bob's total score is $ 14 $ .

For the fifth round, $ \texttt{"codeforces"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{codeforces}}}\texttt{"}\xrightarrow{} \texttt{""} $ . Alice's total score is $ 3+15+4+5+6+15+18+3+5+19=93 $ . Bob's total score is $ 0 $ .

## 样例 #1

### 输入

```
5
aba
abc
cba
n
codeforces```

### 输出

```
Alice 2
Alice 4
Alice 4
Bob 14
Alice 93```

# 题解

## 作者：water_three (赞：1)

### 题目大意：
现在有一个字符串，Alice 可以先将其中连续且长度为偶数的子串取出，并得到对应分值。然后 Bob 可以取出其中长度为奇数的子串。

定义 $a$ 的分值为 $1$，$b$ 的分值为 $2$，以此类推。一个子串的分值就是组成其所有字符的分值之和。

现在有 $t$ 组数据，请你求出在最优策略下谁会赢，并输出分值之差。

### 思路：
可以发现，若字符串长度为偶数，那么 Alice 可以直接取完。如果为奇数，Bob 最后只能取字符串两端分值最小的字符。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--) {
		string s;
		cin>>s;
		if(s.size()==1){
			cout<<"Bob "<<(s[0]-'a'+1)<<endl;
		}
		else{
			if(s.size()%2==0){
				int ans=0;
				for(int i=0;i<s.size();i++){
					ans+=s[i]-'a'+1;
				}
				cout<<"Alice "<<ans<<endl;
			}
			else{
				int ans=0;
				for(int i=0;i<s.size();i++){
					ans+=s[i]-'a'+1;
				}
				if((s[0]-'a'+1)>s[s.size()-1]-'a'+1){
					ans-=s[s.size()-1]-'a'+1;
					if(ans>s[s.size()-1]-'a'+1){
						cout<<"Alice "<<ans-s[s.size()-1]+'a'-1<<endl;
					}
					else{
						cout<<"Bob "<<s[s.size()-1]-'a'+1-ans<<endl;
					}
				}
				else{
					ans-=(s[0]-'a'+1);
					if(ans>(s[0]-'a'+1)){
						cout<<"Alice "<<ans-(s[0]-'a'+1)<<endl; 
					}
					else{
						cout<<"Bob "<<(s[0]-'a'+1)-ans<<endl;
					}
				}
			}
		}
	}
}
```


---

## 作者：小木虫 (赞：0)

### Preface  
考时空间开小 FST...  
### Problem  
Alice 和 Bob ~~van you see~~ 玩游戏，取字符串，字典序越靠后的字母得分越高。  

Alice 先手，每次可以拿偶数大小的一个子串。  
Bob 后手，每次可以拿奇数大小的一个子串。  

现在如果两个人足够聪明，最后谁会赢？并输出两个人分数之差的绝对值。  

### Solution  
我们发现这个 Alice ~~很狗啊~~有很大的优势，她先手。  
那如果这整个串就是个偶数大小，她全拿了。  
否则就给 Bob 剩一个。  
按这个打出分类讨论即可。  
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;char s[200005];
void init(){
	
}
void solve(){
	cin>>s;
	int n=strlen(s);
	if(n==1)cout<<"Bob"<<" "<<(int)(s[0]-'a'+1)<<endl;
	else{
		int tot=0;int MAX=0;
		if(n%2==0){
			for(int i=0;i<n;i++){
				tot+=(int)(s[i]-'a'+1);
			}
			cout<<"Alice"<<" "<<tot<<endl;
			return;
		}
		for(int i=0;i<n-1;i++){
			tot+=(int)(s[i]-'a'+1);
		}
		MAX=tot;tot=0;
		for(int i=1;i<n;i++){
			tot+=(int)(s[i]-'a'+1);
		}
		//cout<<MAX<<" "<<tot<<endl;
		if(MAX<tot){
			if((int)(s[0]-'a'+1)>tot){
				cout<<"Bob"<<" "<<(int)(s[0]-'a'+1)-tot<<endl;
			}else{
				cout<<"Alice"<<" "<<tot-(int)(s[0]-'a'+1)<<endl;
			}
		}else{
			if((int)(s[n-1]-'a'+1)>MAX){
				cout<<"Bob"<<" "<<(int)(s[n-1]-'a'+1)-MAX<<endl;
			}else{
				cout<<"Alice"<<" "<<MAX-(int)(s[n-1]-'a'+1)<<endl;
			}
		}
	}
}
int main(){
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```


---

## 作者：Failure_Terminator (赞：0)

## Problem

有一字符串 $s$。

两人博弈，Alice 只能删除偶数个字符的子串，Bob 只能删除奇数个字符的子串，$a-z$ 被删除的得分分别是 $1-26$，问获胜的人和最终的差值。

## Solution 

由于 Alice 是先手，取的是偶数个字符的子串，当字符串大小是偶数时，他可以将整个字符串全部取走。

如果字符串的大小是奇数，就考虑左右端点的两个，取走较大的一个留一个分值最小的给 Bob。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,alice,bob;
int main()
{
    scanf("%d",&t);
    while(t--){
        string s;
        cin>>s;
        n=s.size(),alice=0,bob=0;
        for(int i=0;i<n;i++) alice+=s[i]-96;//A的ASCII码-1
        if(n&1) bob+=min(s[0],s[n-1])-96;
        alice-=bob;
        if(alice>bob) cout<<"Alice "<<alice-bob<<endl;
        else cout<<"Bob "<<bob-alice<<endl;
    }
    return 0;
}
```

By **haimo**

---

## 作者：cyrxdzj (赞：0)

### 一、思路

显然，有先手优势的 Alice 要选择尽可能长的子串。

如果输入字符串的长度为偶数，那显然 Alice 就选择整个字符串，Alice 必胜。

否则，Alice 就丢弃开头或结尾的字符（丢弃字典序最小的那个），让 Bob 选，再进行判断。

### 二、代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
char s[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s+1);
		int n=strlen(s+1),sum=0;//sum指的是整个字符串的分数和。
		for(int i=1;i<=n;i++)
		{
			sum+=s[i]-'a'+1;
		}
		if(n%2==0)//字符串长度为偶数。
		{
			printf("Alice %d\n",sum);
		}
		else
		{
			int alice,bob;//各个人获得的分数。
			if(s[1]<s[n])
			{
				alice=sum-(s[1]-'a'+1);
				bob=s[1]-'a'+1;
			}
			else
			{
				alice=sum-(s[n]-'a'+1);
				bob=s[n]-'a'+1;
			}
			if(alice>bob)
			{
				printf("Alice %d\n",alice-bob);
			}
			else
			{
				printf("Bob %d\n",bob-alice);
			}
		}
	}
	return 0;
}

```

---

## 作者：yeshubo_qwq (赞：0)

思路：

分类讨论（$i$ 为给定字符串长度）。

分三类：

+ $i$ 为偶数，Alice 直接将全部字符拿走，Alice 胜。

+ $i$ 为奇数且不为 $1$，除了头尾中较小的字符留给 Bob，其余全部由 Alice 拿走，Alice 胜。

+ $i=1$，Alice 不能拿，Bob 拿走唯一的字符，Bob 胜。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,ans,i;
char s[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--){
		cin>>s+1;ans=0;
		for (i=1;s[i]!='\0';i++)
			ans+=s[i]-'a'+1;
		i--;
		if (i%2==0) cout<<"Alice "<<ans<<'\n';
		else if (i!=1) cout<<"Alice "<<ans-min(s[1]-'a'+1,s[i]-'a'+1)*2<<'\n';
		else cout<<"Bob "<<ans<<'\n';
	}
	return 0;
}
```


---

