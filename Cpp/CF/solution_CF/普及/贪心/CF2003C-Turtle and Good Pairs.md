# Turtle and Good Pairs

## 题目描述

海龟给你一个由小写字母组成的字符串 $s$。

他认为，如果一对整数 $(i, j)$（其中 $1 \le i < j \le n$）满足以下条件，则称其为「愉快对」：

1. 存在一个整数 $k$，满足 $i \le k < j$，而且：
   - $s_k \ne s_{k + 1}$；
   - $s_k \ne s_i$ 或 $s_{k + 1} \ne s_j$。

同时，如果一对整数 $(i, j)$（其中 $1 \le i < j \le n$）是「愉快对」或者 $s_i = s_j$，那么它就是「好对」。

海龟想重新排列字符串 $s$，以使「好对」的数量最大化。请帮他实现这一目标。

## 样例 #1

### 输入

```
5
3
abc
5
edddf
6
turtle
8
pppppppp
10
codeforces```

### 输出

```
acb
ddedf
urtlet
pppppppp
codeforces```

# 题解

## 作者：zhangxiaohan007 (赞：3)

这道题一看觉得非常的难，但实际上码量却非常的小。先直接给出结论：只需开个桶，每一次在所有字母中遍历一遍，只要这个字母没用完就输出。注意是每次遍历输出一次字母，而不是一口气输出完。

说了结论，那这道题为什么怎么做呢？看到题目，一个令人愉快的数对 $(i,j)$ 要么 $s_{i}$ 与 $s_{j}$ 相等，要么在 $s_{i}$ 和 $s_{j}$ 之间有着至少一个既不等于 $s_{i}$，又不等于 $s_{j}$ 的字母，而题目要求我们重排字符串，使这样的序列尽可能多。

这样一来，我们就可以考虑一个问题：是把重复的都放一坨，还是让每个挨着的字母都尽量不同？这时候，我们可以考虑一组数据：

```ABCABC```

这个样例看着简单，实际上却能巧妙地给上面的问题一个答案。我们经过分析，可以将上面的问题抽象成两个答案：

```AABBCC``` 以及 ```ABCABC``` 这两个答案。我们可以手推一遍，第一个答案有 $(1,2),(1,5),(1,6),(2,5),(2,6),(3,4),(3,5),(3,6),(5,6)$，共九种。而第二个答案则有 $(1,3),(1,4),(1,5),(1,6),(2,4),(2,5),(2,6),(3,5),(3,6),(4,5)$，共十种。因此我们得出，要让不一样的字母靠在一起，于是就有了开头有的结论，利用桶达到这一效果。

下面给出参考代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
using namespace std;
int n,a[114514],ans,str[30],vis[30];
void solve()
{
	string s;
	cin>>n>>s;
	s=' '+s;
	for(int i=0;i<26;i++)
	{
		str[i]=0;
	}
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		str[s[i]-'a']++;
		ss++;
	}
	vector<char>anss;
	while(ss)
	{
		for(int i=0;i<26;i++)
		{
			if(str[i]>0)
			{
				anss.push_back(i+'a');
				str[i]--;
				ss--;
			}
		}
	}
	for(auto u:anss)
	{
		cout<<u;
	}
	printf("\n");
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：Defy_HeavenS (赞：3)

# 题意

给定一个字符串 $s$。好数对的定义：对于一个数对 $(i,j)$（保证 $1\le i<j\le n$）是好数对当且仅当存在一个 $k$（保证 $i\le k<j$）满足一下两点：

- $s_k\ne s_{k+1}$。
- $s_k\ne s_i$ **或** $s_{k+1}\ne s_j$。
  则称 $(i,j)$ 是一对好数对。

现在需要对给定的这个字符串重排，使得好数对数量最多。

# 思路

对好数对 $(i,j)$ 重新理解一下。

- 对于第一个要求 $s_k\ne s_{k+1}$，其实就是要求 $s_{[i,i+1,\dots,j]}$ 中不全是相同的元素（这样就可以使 $k$ 为那两个相邻且不相同元素中的第一个）。
- 对于第二个要求 $s_k\ne s_i$ **或** $s_{k+1}\ne s_j$，注意这里的**或**，其实就是在满足上一个要求的前提下需要满足 $i+1\ne j$，也就是 $j-i+1>2$。

那这样其实就是想让我们使 $s$ 尽可能乱，尽可能让 $s$ 相邻的两个不相同。

当怎么使 $s$ 乱呢？可以用 `map` 记录字符出现次数，然后尽可能放出现次数多（因为如果乱发可能出现后面只能放一个数量最多的了，因为其他的都在前面放完了）的且不能与上一个字符相同即可。

# 代码

赛时代码。

```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define pb push_back

using namespace std;
typedef long long LL;
typedef pair<int,char> PII;

const int N=2e5+5;
int n;
string s;
void solve(){
	cin>>n>>s;
	map<char,int>mp;
	vector<PII>hav;
	for(int i=0;i<n;i++){
		if(!mp[s[i]]){
			hav.pb({1,s[i]});    //记录都有那些元素
		}
		mp[s[i]]++;    //记录数量
	}
	for(auto val:hav){
		char ch=val.second;
		val={-mp[ch],ch};    //使出现次数尽可能多的放前面
	}
	sort(hav.begin(),hav.end());
	char la='!';
	for(int i=1;i<=n;i++){
		bool flag=1;
		for(auto val:hav){    //排序后数量多的在前
			char ch=val.second;
			if(mp[ch]&&la!=ch){    //还能放且与上一个不同
				cout<<ch;
				mp[ch]--;
				la=ch;
				flag=0;
				break;
			}
		}
		if(flag){    //都放完了，只能放和上一个一样的了
			cout<<la;
			mp[la]--;
		}
	}
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

---

