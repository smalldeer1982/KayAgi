# Password Cracking

## 题目描述

迪马什得知曼苏尔向朋友泄露了一些关于他的不愉快言论，于是他决心揭开曼苏尔的密码，看看具体内容是什么。

曼苏尔对自己的密码充满信心，他表示自己的密码是一个长度为 $ n $ 的二进制字符串。同时，他愿意回答迪马什的问题：

迪马什可以给出一个二进制字符串 $ t $ ，曼苏尔则回答 $ t $ 是否是他的密码的一个子串（即一段连续的字符序列）。

请帮助迪马什在不超过 $ 2n $ 次询问内猜出密码；否则，曼苏尔将识破伎俩并停止与他交流。

## 样例 #1

### 输入

```
4
3

0

0

1

4

4

2```

### 输出

```
? 00

? 000

? 010

! 010

! 1100

! 0110

! 10```

# 题解

## 作者：hema5177 (赞：4)

### 题意

交互题。用程序猜测 01 字符串。

有 t 组测试数据，每组数据中输入一个正整数 n 表示字符串的长度。程序可输出 `? s` 以判断 s 字符串是否为所需要猜测的字符串的子串。回复 1 表示 s 字符串为需猜测的字符串的子串，回复 0 则不是。程序可输出 `! s` 以确认猜测完的字符串。对于每个需猜测的字符串只能询问 2n 次。

记得在输出后加一个 `fflush(stdout);` 清空缓存。

### 思路

样例明显不是真正的思路。

想要稳稳地得到正确的字符串，只能猜。从长度为 1 开始，每一次在正确的子串前或后添加 0 或 1，直到得到正确的字符串。于是我写了第一个代码。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<deque>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		int n,sum=1,sum1=1;
		cin>>n;
		string s1="";
		deque<char> q;
		q.push_back('0');
		while(1)
		{
			bool a;
			cout<<"? ";
			deque<char> q1;
			while(!q.empty())
			{
				cout<<q.front();
				q1.push_back(q.front());
				q.pop_front();
			}
			cout<<endl;
			fflush(stdout);
			cin>>a;
			if(a&&q1.size()==n)
			{
				cout<<"! ";
				while(!q1.empty())
				{
					cout<<q1.front();
					q1.pop_front();
				}
				cout<<endl;
				sum=1;
				fflush(stdout);
				break;
			}
			else if(a)
			{
				s1="";
				while(!q1.empty())
				{
					q.push_back(q1.front());
					s1+=q1.front();
					q1.pop_front();
				}
				if(sum==1) q.push_back('0'),sum++;
				else if(sum==2) q.push_back('1'),sum++;
				else if(sum==3) q.push_front('0'),sum++;
				else q.push_front('1');
			}
			else if(!a)
			{
				for(int i=0;i<s1.size();i++) q.push_back(s1[i]);
				if(sum==2) q.push_back('1'),sum++;
				else if(sum==3) q.push_front('0'),sum++;
				else if(sum==4) q.push_front('1'),sum=1;
				else q.push_back('0'),sum++;
			}
		}
	}
}
```
然而效率太低，需要猜测很多次，很多都超过了 2n。

这样先在前面猜，又在后面猜，未免太过于混乱。那如果先全部猜测后面的，再全部猜测前面的呢？

这样似乎不会混乱，猜测次数也少了许多。

次数少应该是因为在猜测完后面的之后，再猜测前面的次数就会很固定且轻松了。也不用前后反复横跳添加 0 或 1。

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<deque>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		string s1="";//正确的子串
		while(s1.size()<n)
		{
			bool a;
			cout<<"? "<<s1+'1'<<endl;
			fflush(stdout);
			cin>>a;
			if(a)
			{
				s1+='1';
				continue;
			}
			cout<<"? "<<s1+'0'<<endl;
			fflush(stdout);
			cin>>a;
			if(a) s1+='0';
			else break;
		}
		while(s1.size()<n)
		{
			bool a;
			cout<<"? "<<'1'+s1<<endl;
			fflush(stdout);
			cin>>a;
			if(a)
			{
				s1='1'+s1;
				continue;
			}
			s1='0'+s1;//在猜测前面只有两种可能了，所以这里不用问。
		}
		cout<<"! "<<s1<<endl;
		fflush(stdout);
	}
}
```
还有[AC记录](https://codeforces.com/contest/2013/submission/284716301)。

---

## 作者：Wind_love (赞：0)

## 思路
交互题，用贪心猜测字符串。   
每次有四种可能的情况，即在前面加 0，在前面加 1，在后面加 0，在后面加 1。   
我们注意到题目要求在 $2n$ 次询问内完成猜测，所以不能每次枚举以上四种情况。   
通过思考，我们可以发现，如果在后面加 0 或 1 都不可以，那么该字符串一定不可以再次向后拓展，向前同理。   
根据这个思路，我们得到一个思路，先向后拓展，直到无法拓展，再向前拓展，最终完成猜测。询问次数在 $2n$ 次以内，符合题目条件。   
记得刷新缓冲区。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		string s="";
		int temp,f=1;
		while(1){
			if(f){
				cout<<"? "<<string(s+"0")<<endl;//endl自动刷新缓冲区 这也是它慢的原因 
				cin>>temp;
				if(temp)s+="0";
				else{
					cout<<"? "<<string(s+"1")<<endl;
					cin>>temp;
					if(temp)s+="1";
					else f=0;
				}
			}
			if(!f){
				cout<<"? "<<string("0"+s)<<endl;
				cin>>temp;
				if(temp)s="0"+s;
				else s="1"+s;
			}
			if(s.size()==n){
				cout<<"! "<<s<<endl;
				break;
			}
		}
	}
	return 0;
}

---

## 作者：Defy_HeavenS (赞：0)

~~交换题，每次输出完都要刷新缓冲区……关键我还总是忘，好烦。~~

### 思路

设当前猜准的字符串为 $s$。

首先向后去找。每次询问 $s+0$ 和 $s+1$ 是不是子串。直到这两个都不是子串为止，这就说明我们找到了这个密码的后缀。

再向前去找。每次询问 $0+s$ 和 $1+s$ 是不是子串。直到这两个都不是子串为止或长度够了，这就说明我们找到了这个密码。

~~交互题真麻烦。~~

### 代码

```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define pb push_back

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;

int n,q;
map<string,bool>mp;

bool query(string s){
	if(mp.count(s)){
		return mp[s];
	}else{
		cout<<"? "<<s<<"\n";
		cout.flush();
		cin>>q;
		mp[s]=q;
		return q;
	}
}
void solve(){
	mp.clear();
	string s;
	cin>>n;
	cout<<"? 0\n";
	cout.flush();
	cin>>q;
	if(q){
		s="0";
	}else{
		s="1";
	}
	while(s.size()<n){
		q=query(s+"0");
		if(q){
			s+="0";
			continue;
		}
		q=query(s+"1");
		if(q){
			s+='1';
			continue;
		}else{
			break;
		}
	}
	while(s.size()<n){
		q=query("0"+s);
		if(q){
			s="0"+s;
			continue;
		}
		s="1"+s;
	}
	cout<<"! "<<s<<"\n";
	cout.flush();
}

int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

### 拓展

这个题是 `01` 字符串，其实是可以延申到小写或大写字母上的，只不过这个的询问次数是 $\le 2n$ 次，而那个是 $\le k\times n$ 的，其中 $k$ 是可能的字符数量。

---

