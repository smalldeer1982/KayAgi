# Polycarp Writes a String from Memory

## 题目描述

Polycarp has a poor memory. Each day he can remember no more than $ 3 $ of different letters.

Polycarp wants to write a non-empty string of $ s $ consisting of lowercase Latin letters, taking minimum number of days. In how many days will he be able to do it?

Polycarp initially has an empty string and can only add characters to the end of that string.

For example, if Polycarp wants to write the string lollipops, he will do it in $ 2 $ days:

- on the first day Polycarp will memorize the letters l, o, i and write lolli;
- On the second day Polycarp will remember the letters p, o, s, add pops to the resulting line and get the line lollipops.

If Polycarp wants to write the string stringology, he will do it in $ 4 $ days:

- in the first day will be written part str;
- on day two will be written part ing;
- on the third day, part of olog will be written;
- on the fourth day, part of y will be written.

For a given string $ s $ , print the minimum number of days it will take Polycarp to write it.

## 样例 #1

### 输入

```
6
lollipops
stringology
abracadabra
codeforces
test
f```

### 输出

```
2
4
3
4
1
1```

# 题解

## 作者：Jeremiahy (赞：6)

## 题意

给定一个字符串 $s$，每天可以写下三个不同的字母，从头开始写，至少需要几天写完？

# 分析

直接模拟即可：如果第一个字母还没用就用上，一直到第三个用完，开启新的一天。在这一天中，遇见今天已经写了的字母跳过，不用浪费机会，一直到需要写第四个不同的字母为止。

在具体实现中，可建立一个指针 $l$ 及三个记录字母的字符 $a$,$b$,$c$，每天一开始 $l$ 指向第一个需要写的字母，然后按照如上步骤进行即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, ans, l;//数据组数， 天数， 指针
char a, b, c;//每天三个不同的字母
string s;//需要写的字符串
signed main() {
	cin >> t;
	while (t--) {
		cin >> s;
		ans = l = 0;//初始化
		while (l < s.length()) {
			a = b = c = '0';
			ans++;//新的一天~
			for (; ; l++) {
				if (a == '0')//还没用 a
					a = s[l];
				else if (s[l] == a)//发现已经写下
					continue;
				else if (b == '0')
					b = s[l];
				else if (s[l] == b)
					continue;
				else if (c == '0')
					c = s[l];
				else if (c == s[l])
					continue;
				else
					break;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

完。


---

## 作者：yeshubo_qwq (赞：1)

## Description

每天你可以记住至多三个字母，并且可以按照任意顺序写出任意个这些字母，问最少几天可以写出给定单词。

## Solution

模拟写的过程。

每次从第一个未写的字母开始：

- 如果这个字母已经被记住，跳过。

- 如果没有被记住且还未记满三个字母，记住这个字母。

- 如果没有被记住且已经记满三个字母，结束，下一天继续。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char s[200005];
int f[30],n,i,res,u,j;
void solve(){
	cin>>s+1,n=strlen(s+1);
	res=0;
	for (i=1;i<=n;){
		for (j=0;j<26;j++) f[j]=0;
		u=0;
		res++;
		while (i<=n){
			if (f[s[i]-'a']==1) i++;
			else if (u<3){
					u++;
					f[s[i]-'a']=1;
					i++;
				}
			else break;
		}
	}
	cout<<res<<'\n';
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int tests=1;
	cin>>tests;
	while (tests--)
		solve();
	return 0;
}

```


---

## 作者：Hisaishi_Kanade (赞：1)

### 一、题意&翻译

每次操作只能写出三种不同的字符，问写一个字符串需要至少多少次操作。

### 二、思路&代码

思路很显然，突破口就是如何维护“只有三种”，也就是去重。

这里提供两种不同的做法，复杂度也略有不同。

1. 单次 $O(n)$ 做法

采用STL库中的`unordered_map`，虽然不建议在CF比赛中使用~~因为一定会被卡~~。

```cpp
#include <stdio.h>
#include <string.h>
#include <unordered_map>
using std::unordered_map;
unordered_map<char,bool>mp;
int t,n,i;
char s[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		auto ans(0);
		scanf("%s",s);
		auto len=(int)(strlen(s));//这里长度较大，strlen()又是O(n)的，所以开变量记下来
		for(i=0;i<len;++i){
			mp[s[i]]=true;
			if(mp.size()>3){
				++ans;
				mp.clear();
				mp[s[i]]=true;
			}
		}
		if(!mp.empty())//最后特判
			++ans;
		printf("%d\n",ans);
		mp.clear();//清空
	}
	return 0;
}
```

复杂度 __期望__ $O\left(t\cdot n\right)$，实际做不到，这就是哈希的“特性”。

模拟与此同理，只是不用容器，常数略小，不多赘述。

2. 单次 $O(n\log n)$ 做法

```cpp
#include <set>
#include <stdio.h>
#include <string.h>
using std::set;
int t,n,i;
set<char>st;
char s[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		auto ans(0);
		scanf("%s",s);
		auto len=(int)(strlen(s));
		for(i=0;i<len;++i){
			st.insert(s[i]);
			if(st.size()>3){
				++ans;
				st.clear();
				st.insert(s[i]);
			}
		}
		if(!st.empty())
			++ans;
		printf("%d\n",ans);
		st.clear();
	}
	return 0;
}
```

和上面类似，`set`自动去重，很方便。

但是内部红黑树的实现导致复杂度为 $O\left(t\cdot n\log n\right)$，理论上比哈希慢。

`map`和`set`同理，不多赘述。

### 三、总结

哈希虽然复杂度更优，但测试发现，两者时间几乎一样。

由此可见 __期望__ 复杂度不能代表一切，常数因子也会影响效率。

$O(n)$ 的记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/3guf2qvy.png)

$O(n\log n)$ 的记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/rwx4bml1.png)

吸氧时间一点没变，图不挂了。

---

## 作者：Dream_weavers (赞：1)

## 题意

给出一个字符串 $s$，从前往后每三个不同的字母分为一组，问能分多少组。

## 思路

推荐用 stl 的 set，自带去重的功能（此题中排序用不上）。

设 $q$ 是一个 set 容器。每次向 $q$ 插入一个字母。如果去重后 $q$ 的大小 $=3$，并且后一个字母与 $q$ 中的不重复，那么让答案 $+1$。

最后特判一下，如果 $q$ 不为空，就让剩下的字母分成一组，答案 $+1$。

stl 的 map 记录有没有重复也可以，但没有 set 方便（个人认为）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
set <char> q;
string s;
int t,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		cin>>s;
		q.clear(),ans=0;
		for(int i=0;i<s.size();i++){
			q.insert(s[i]);
			if(q.size()>3){
				q.clear();
				q.insert(s[i]);
				ans++;
			}
		}
		if(q.size())ans++;
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Halberd_Cease (赞：0)

## 题意简述
一个人每天可以记住 $3$ 个不同的字母，求他按顺序记住一个字符串所需要的天数。

这其实就是一个模拟，我这里采用枚举天数来判断在多少天可以全部记完。

如果现在处理的字母不在今天记住字母的列表里且今天没有记满 $3$ 个字母就将这个字母放在列表中；如果满了 $3$ 个就开启新的一天。

如果在处理列表中直接下一个字母即可。

注意：随时判断是否已经处理完所有字母，随时退出。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
main()
{
	int t;
	cin>>t;
	while(t--)
	{
		char a[200010];
		char today[5];
		int today_num;
		int total=0;
		cin>>a;
		int len=strlen(a);
		for(int i=1;;i++)
		{
			memset(today,0,sizeof(today));
			today_num=0;
			while(1)
			{
				if(a[total]!=today[1]&&a[total]!=today[2]&&a[total]!=today[3])
				{
					if(today_num==3)break;//记满3个
					else
					{
						total++;
						today[++today_num]=a[total-1];//记住
					}
				}
				else total++;
				if(total>=len)break;
			}
			if(total>=len)
			{
				cout<<i<<'\n';
				break;
			}
		}
	}
 } 
```

---

## 作者：Qerucy (赞：0)

对于这道题来说，我们可以建一个 `vis` 数组，来标记字符是否被背诵过，如果有被背诵过了，我们就跳过，如果没有，就把一天内背诵的字符数量加一，如果一天内背诵的字符数量大于 $3$ 之后，就继续下一天的背诵，直到字符全被背诵完为止。

最后再输出背诵总共需要的天数即可。

代码：

```cpp
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>

using namespace std;

string s;
int t;
bool vis[1010];
int now;
int ans;

int main(){
	scanf("%d",&t);
	while(t--){
		cin>>s;
		now=ans=0;
		memset(vis,0,sizeof(vis));
		for(int i=0;i<s.length();i++){
			if(vis[s[i]]) continue;
			
			now++;
			vis[s[i]]=1;
			
			if(now>3){
				now=1;
				ans++;
				memset(vis,0,sizeof(vis));
				vis[s[i]]=1;
			}
		}
		printf("%d\n",ans+1);
	}
	return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

模拟题。

思路：首先，考虑到用最少的天数，一天学三个字符。

然后，可以采用一个指针，每次指向一个字符，如果没有学习，就学习；如果一天的学习内容已经满了，那就再开一天。

时间复杂度 $O(n)$。

---

## 作者：Shimotsuki (赞：0)

题意：定义一次操作为将三个不同的字母加入一个字符串，如果有重复的字母，则不算多于三个字母。给定一个字符串，求在空串中构造该字符串的最小操作次数。

做法：使用一个 `map` 记录字符是否出现，使用 `cnt` 来记录字母数，使用 `ans` 统计操作次数。如果当 `cnt` 达到 $3$ 且下一个字符不是重复字符，则完成一次操作。

- 记得清空 `map`。
- 如果操作完整个字符串后，`cnt` 的值非 $0$ ，则还有一次操作。

[$Code$](https://www.luogu.com.cn/paste/a03l8quq)

---

## 作者：Scorilon (赞：0)

给定一个字符串，每天可以记忆三个字符，求书写出整个字符串的天数。

每次确定要记忆的三个字母，并向后寻找，若有非三个字母其中一个，则重新开启一天记忆三个字母。
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int t;
string s;
int main(){
	scanf("%d",&t);
	while(t--){
		cin>>s;
		char a='0',b='0',c='0';//记忆三个字母
		bool f1=false,f2=false,f3=false;//三个字母是否有值
		int ans=1;//刚开始天数为1
		for(int i=0;i<s.size();i++){
			if(f1&&f2&&f3){
				if(s[i]!=a&&s[i]!=b&&s[i]!=c){//如果是未记忆，重新开启一轮
					f1=false;
					f2=false;
					f3=false;//恢复状态
					ans++;//天数+1
					a='0';
					b='0';
					c='0';
				}
				else continue;
			}
			if(!f1&&s[i]!=b&&s[i]!=c){//寻找需记忆的三个字母
				a=s[i];
				f1=true;
				continue;
			}
			if(!f2&&s[i]!=a&&s[i]!=c){
				b=s[i];
				f2=true;
				continue;
			}
			if(!f3&&s[i]!=a&&s[i]!=b){
				c=s[i];
				f3=true;
				continue;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

