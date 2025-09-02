# Madhouse (Easy version)

## 题目描述

This problem is different with hard version only by constraints on total answers length

It is an interactive problem

Venya joined a tour to the madhouse, in which orderlies play with patients the following game. Orderlies pick a string $ s $ of length $ n $ , consisting only of lowercase English letters. The player can ask two types of queries:

- ? l r – ask to list all substrings of $ s[l..r] $ . Substrings will be returned in random order, and in every substring, all characters will be randomly shuffled.
- ! s – guess the string picked by the orderlies. This query can be asked exactly once, after that the game will finish. If the string is guessed correctly, the player wins, otherwise he loses.

The player can ask no more than $ 3 $ queries of the first type.

To make it easier for the orderlies, there is an additional limitation: the total number of returned substrings in all queries of the first type must not exceed $ (n+1)^2 $ .

Venya asked you to write a program, which will guess the string by interacting with the orderlies' program and acting by the game's rules.

Your program should immediately terminate after guessing the string using a query of the second type. In case your program guessed the string incorrectly, or it violated the game rules, it will receive verdict Wrong answer.

Note that in every test case the string is fixed beforehand and will not change during the game, which means that the interactor is not adaptive.

## 样例 #1

### 输入

```
4

a
aa
a

cb
b
c

c```

### 输出

```
? 1 2

? 3 4

? 4 4

! aabc```

# 题解

## 作者：Rhodoks (赞：4)

[Hard version link](https://www.luogu.com.cn/blog/Rhodoks/solution-cf1286c2)

题意：有一个字符串$s$，可以询问3次它的子串$s[l..r]$，返回这一子串的所有子串，并且子串间的顺序与子串内部字符的顺序全部打乱。至多询问三次，并且返回的字符串数不能超过$(n+1)^2$个。输出$s$。

考虑询问$s[1..n]$和$s[2..n]$，共计返回字符串数为$\frac{n*(n+1)}{2}+\frac{n*(n-1)}{2}=n^2$，询问次数为2，满足要求。

相对于$s[2..n]$，询问$s[1..n]$得到的子串额外增加了$s[1..i](1 \leq i \leq n)$,如果我们能够得到这$n$个字符串，那么可以通过长度区分出他们。$s[1..i]$比$s[1..i-1]$多出来的那一个字符，便是字符串第$i$位上的字符。

使用$\text{sort}$和$\text{multiset}$实现去重，首先将读入的每个字符串都进行一遍排序，这样两个由同样字符组成（顺序可以不同）的字符串会得到同一个结果。本题中因为子串被打乱，顺序并不重要。

将$s[1..n]$询问的结果插入$\text{multiset}$，再把$s[2..n]$询问的结果从$\text{multiset}$中删掉，那么最后剩下来的$n$个字符串就是我们需要的结果。依此可以复原出原串。

code:
```cpp
#include <bits/stdc++.h>
#define _ 0
using namespace std;
 
string s;
multiset<string> st;
string ss[110];
 
char ans[1000];
bool cmp(string s1,string s2)
{
	return s1.size()<s2.size();
}
int buc[1100];
int main()
{
	int n;
	cin>>n;
	if (n==1)
	{
		cout<<"? "<<1<<' '<<1<<'\n';
		fflush(stdout);
		char c;
		cin>>c;
		cout<<"! "<<c;
		fflush(stdout);
		return 0;
	}
	cout<<"? "<<1<<' '<<n<<'\n';
	fflush(stdout);
	for (int i=0;i<n*(n+1)/2;i++)
	{
		cin>>s;
		sort(s.begin(),s.end());
		st.insert(s);	
	} 
	cout<<"? "<<2<<' '<<n<<'\n';
	fflush(stdout);
	for (int i=0;i<n*(n-1)/2;i++)
	{
		cin>>s;
		sort(s.begin(),s.end());
		st.erase(st.find(s));	
	} 
	int cnt=0;
	for (auto p:st)
	{
		ss[cnt++]=p;
	}
	sort(ss,ss+cnt,cmp);
	ans[0]=ss[0][0];
	
	for (int i=1;i<cnt;i++)
	{
		for (auto p:ss[i-1])
			buc[p]--;
		for (auto p:ss[i])
			buc[p]++;
		for (int j=0;j<255;j++)
			if (buc[j]>0)
			{
				buc[j]=0;
				ans[i]=j;
			}
	}
	cout<<"! "<<ans;
	fflush(stdout);
	return ~~(0^_^0);
}
```


---

## 作者：Day_Tao (赞：0)

简单题。不明白为什么有 *2400。感觉最多 *2000。

题目的限制是最多询问 $3$ 次，而要想得到答案那么所有询问必须覆盖整个序列。一个比较典的 trick 是考虑确定一个位置之后去依次确定剩下的位置。

不难发现我们只需要询问 $[1,n]$ 和 $[1,n-1]$ 就能求出位置 $n$ 的字母。具体的，这两次询问给出的字符串排序后的集合之差为 $n$ 个长度分别为 $[1,n]$ 的包含 $s_n$ 的字符串，其中那个长度为 $1$ 的串就是 $s_n$。

不难发现，这样我们就能确定出剩下所有的字符了。$s_{n-1}$ 就是剩下的那个长度为 $2$ 的串去掉 $s_n$ 这个字符剩下的哪个字符。对于 $s_{n-2\cdots1}$ 同样可以这样做。总的询问子串数为 $\frac{n\times(n+1)+n\times(n-1)}{2}=n^2\le(n+1)^2$。注意特判 $n=1$ 的情况。

具体实现上考虑开一个 `multiset`，在询问 $[1,n]$ 的时候插入给出的字符串（排序后），在询问 $[1,n-1]$ 的时候删除给出的字符串（排序后），将 `string` 的重载改为优先比较长度，次优先比较字符串，这样就可以用一个迭代器去顺序访问 `multiset` 然后依次确定每一位的答案。

代码比较小清新，比题解区的代码都要简洁（吧）。

**Code：**

```cpp
struct Day_Tao{
	string s;
	inline bool operator<(const Day_Tao&dt)const{
		return SZ(s)==SZ(dt.s)?s<dt.s:SZ(s)<SZ(dt.s);
	}
};
int n;char ans[N];string s,t;multiset<Day_Tao>S;
void qu(){pc('?'),pc(' ');}void an(){pc('!'),pc(' ');}
inline void SOLVE(){
	n=rd();if(n==1){qu(),cout<<1<<' '<<1<<endl,cin>>s,an(),cout<<s<<endl;return;}
	qu(),cout<<1<<' '<<n<<endl;
	for(int i=1;i<=n*(n+1)/2;i++)
		cin>>s,sort(s.begin(),s.end()),S.insert({s});
	qu(),cout<<1<<' '<<n-1<<endl;
	for(int i=1;i<=n*(n-1)/2;i++){
		cin>>s,sort(s.begin(),s.end());
		if(SZ(s)==n-1)t=s;S.erase(S.lower_bound({s}));
	}auto it=S.begin();s=(*it).s,ans[n]=s[0];int j=n;
	while(next(it)!=S.end()){
		s=(*++it).s,t="";for(int i=j;i<=n;i++)t+=ans[i];j--;
		sort(t.begin(),t.end()),ans[j]=s[SZ(s)-1];
		for(int i=0;i<SZ(t);i++)if(s[i]!=t[i]){ans[j]=s[i];break;}
	}an(),cout<<(ans+1)<<endl;
	return ;
}
```

---

## 作者：operator_ (赞：0)

# Madhouse (Easy version)

[题目传送门](https://www.luogu.com.cn/problem/CF1286C1)

## 题解

这种水题还能有蓝？不能因为困难版是黑就把简单版难度往上强拉啊！

第一次问 $[1,n]$，第二次问 $[1,n-1]$，把读入的所有字符串先**各自**内部把字符排序（反正本来就是乱序）后存入 map，第一次询问有，第二次询问没有的字符串就是原串后缀的乱序，都找出来再从后往前推出所有字符就好了。

完全不存在时间顾虑，代码随便写，唯一要注意的就是特判 $n=1$。

代码写得很丑，不放了。

---

