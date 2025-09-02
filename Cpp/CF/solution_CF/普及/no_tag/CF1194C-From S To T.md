# From S To T

## 题目描述

你将会得到三个由小写拉丁字符组成的字符串 $s, t, p$

每一次操作中，你可以在 $p$ 中任意选出一个字符删去并插入在 $s$ 中的任意一个位置

例如当 $p$ 为 $\text{aba}$，$s$ 为 $\text{de}$，则以下操作都是合法的

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{ade}$

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{dae}$

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{dea}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{bde}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{dbe}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{deb}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{ade}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{dae}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{dea}$

你的任务是检验是否能经过若干次操作（可能零次），将 $s$ 变为 $t$

## 样例 #1

### 输入

```
4
ab
acxb
cax
a
aaaa
aaabbcc
a
aaaa
aabbcc
ab
baaa
aaaaa
```

### 输出

```
YES
YES
NO
NO
```

# 题解

## 作者：wen_chang (赞：3)

先解释一下题意：给出s，t，p三个字符串，你可以从p中删除任意多（可以为0）的字符，并把这些字符插入到s的任意位置，要判断是否可以让s变成t


这道题稍微思考一下就会发现并没有这么难，只是几个分开的判断而已

下面进入正题：

### 只要给出的s、t、p三个字符串不满足以下的条件，直接输出NO就可以了：

#### 1、s的长度小于等于t的长度

这个很好理解吧，因为你把p的字符移动到s中，只会让s更长，却不能让s变短。所以如果s的长度比t的长度还长，那么无论如何都不可能让s变成t。直接输出NO就好了。
#### 2、对于每个小写字母，它在s、p中出现次数之和必须大于等于它在t中出现的次数
如果一个字母在s中出现的次数，小于它在t中出现的次数，那么我们就要把p中的该字母移到s中。但是！如果把p中所有的该字母都移动了过去还不够，那么就不可能拼出t。

举个例子，假如s="abc"，t="abbbc",p="bc"，对于这个例子，我们发现，s中的字母"b"不够，所以就把p中的"b"移到s中，于是乎，我们惊奇地发现，"b"在s、p中共出现了2次，但是在t中出现了3次。所以不管怎样，s都不可能出现3个"b"，更不可能变成t。
#### 3、s必须为t的子序列（可以不连续）
换言之，你必须从t中选出一些可以不连续的字符，将它们按原本在t中的顺序拼起来，要得到s。

证明：假设s不是t的子序列，令我们在s中加入了一些p的字母后，得到新的字符串为c，因为原本s中字母的内部顺序没有改变，所以s是c的子序列，但由于s不是t的子序列，所以无论怎么操作，c都不等于t。

只要满足以上三个条件，就可以在原本的s的基础上插入p的某些字符，使得s变成t。


最后贴上代码，不要抄袭呀~

```cpp
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int q,i,zm1[26],zm2[26],faq,flag;
string s[101],t[101],p[101];
int main()
{
	cin>>q;
	while(q--)
	{
		memset(zm1,0,sizeof(zm1));
		memset(zm2,0,sizeof(zm2));
		faq=0;
		flag=0;
		cin>>s[q]>>t[q]>>p[q];
		if(s[q].size()>t[q].size())//判断条件1
		{
			cout<<"NO"<<endl;
			continue;
		}
		for(i=0;i<s[q].size();i++)zm1[s[q][i]-97]++;
		for(i=0;i<p[q].size();i++)zm1[p[q][i]-97]++;
		for(i=0;i<t[q].size();i++)zm2[t[q][i]-97]++;//记录每个字母出现次数
		for(i=0;i<=25;i++)
			if(zm1[i]<zm2[i])
			{
				cout<<"NO"<<endl;
				flag=1;
				break; 
			}//判断条件2
		if(flag)continue;
		for(i=0;i<t[q].size();i++)
		{
			if(t[q][i]==s[q][faq])faq++;
			if(faq==s[q].size())
			{
				cout<<"YES"<<endl;
				break;
			}//判断条件3
		}
		if(faq<s[q].size())cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：yanghanyv (赞：1)

### 题意
从 $p$ 中选出若干字母插入 $s$，使其变成 $t$。

### 解法
本题思路很明显，是一个贪心。  
首先 $s$ 一定会包含在 $t$ 中，且字母的相对顺序不变，所以我们先将一个 $s$ 从 $t$ 中删除，这一步需要用两个指针（下标）扫一遍判断。  
然后判断剩下的 $t$ 能否用 $p$ 中的若干字母表示出来，这一步只需统计两个字符串中各个字母的数量。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int q,pos,cnt[30];
string s,t,p;
bool flag,vis[N];
int main(){
	scanf("%d",&q);
	while(q--){
		cin>>s>>t>>p;
		pos=0;
		flag=1;
		memset(cnt,0,sizeof(cnt));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<t.size();i++){
			if(s[pos]==t[i]){
				vis[i]=1;
				if(++pos==s.size()){
					break;
				}
			}
		}//从t中删除s
		if(pos==s.size()){
			for(int i=0;i<p.size();i++){
				cnt[p[i]-'a']++;
			}//统计p中字母
			for(int i=0;i<t.size();i++){
				if(!vis[i]){
					if(--cnt[t[i]-'a']<0){
						flag=0;
						break;
					}
				}
			}//判断能否用p中字母组合出t剩下部分
		}else{
			flag=0;
		}
		if(flag){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}
```


---

## 作者：逃课小姐MS (赞：1)

### 一道需要一点点点思考的模拟题。

题目意思简单说一下：

希望在s字符串插入几个从p中掰出来的字符，使得s==t。

可以输出yes（大小写随意），反之输出no（同上）

其实很简单：

首先，我们把p拆开来，放在一个数组里面。

定义一个cnt代表的是s的指针。

然后，我们一位一位的遍历t数组，如果说t的这一位可以跟s当前指针位置上的哪一位对牢，那么就把指针向前移动一位。

如果不可以对的上，那么就在p拆开来的那个数组里找是否有当前t上的那一位，如果有，这个数组里的这一位减一。

如果有一位在p拆开来的数组里面是0但是t里面有这一位，就是不行的。如果我的cnt不等于s的长度，那也是不行的。

具体操作还是详见代码，我就不给注释了，因为不是很难。

```
#include<bits/stdc++.h>
using namespace std;
int c[27];
int main(){
    string s,t,p;
    int T;
    cin>>T;
    while(T--){
        memset(c,0,sizeof(c));
        int cnt=0;
        cin>>s>>t>>p;
        int lenp=p.length(),lens=s.length(),lent=t.length();
        for(int i=0;i<lenp;i++){
            c[(int)(p[i]-'a'+1)]++;
        }
        bool flag=1;
        for(int i=0;i<lent;i++){
            if(t[i]==s[cnt]) cnt++;
            else if(c[(int)(t[i]-'a'+1)]!=0) c[(int)(t[i]-'a'+1)]--;
            else flag=0;
        }
        if(cnt!=lens) flag=0;
        if(flag==1) cout<<"yes"<<endl;
        else cout<<"no"<<endl; 
    }
    return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1194C)

一道模拟题。

首先判断 $s$ 是否是 $t$ 的子序列，如果不是就直接输出 `NO`。证明一下，$s$ 一定是 $s$ 插入 $p$ 后得到的字符串的子序列，但如果 $s$ 不是 $t$ 的子序列，则插入后的字符串一定不等于 $t$。

如果 $s$ 是 $t$ 的子序列，我们统计一下 $t$ 中的其他字符共有多少个，如果 $p$ 中的数量足够就输出 `YES`，否则输出 `NO`。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int q, numt[30], nump[30];
signed main() {
    ios :: sync_with_stdio(0);
    cin >> q;
    while (q--) {
        memset(numt, 0, sizeof(numt));
        memset(nump, 0, sizeof(nump));
        int cnt = 0;
        string s, t, p;
        cin >> s >> t >> p;
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == s[cnt]) cnt++;
        }
        if (cnt != s.size()) cout << "NO\n";
        else {
            bool flag = 1;
            cnt = 0;
            for (int i = 0; i < t.size(); i++) {
                if (t[i] == s[cnt]) {
                    cnt++;
                    continue;
                }
                numt[t[i] - 'a' + 1]++;
            }
            for (int i = 0; i < p.size(); i++) nump[p[i] - 'a' + 1]++;
            for (int i = 1; i <= 26; i++) {
                if (nump[i] < numt[i]) flag = 0;
            }
            if (flag) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
```


---

## 作者：vandijk (赞：0)

题意：

你将会得到三个由小写拉丁字符组成的字符串 s, t, p
每一次操作中，你可以在 p 中任意选出一个字符删去并插入在 s 中的任意一个位置

例如当 p 为 aba，s 为 de，则以下操作都是合法的


你的任务是检验是否能经过若干次操作（可能零次），将 s 变为 t。

我们可以想到，用三个计数器分别计算s,t,p里a~z的数量，再一一比较大小就行。

```
#include <bits/stdc++.h>
using namespace std;

int T;
string s,t,p;
map<char,int> mp,mp2,mp3;

bool can()//判断插入无限字符行不行
{
	int j=0;
	for(int i=0;i<s.size();i++)
	{
		while(s[i]!=t[j]&&j<t.size())j++;
		if(j>=t.size())return 0;
		j++;
	}
	return 1;
}

int main()
{
	cin>>T;
	while(T--)
	{
		mp.clear();
		mp2.clear();
		mp3.clear();
		cin>>s>>t>>p;
		if(!can())
		{
			cout<<"NO"<<endl;
			continue;
		}
		for(int i=0;i<s.size();i++)
		{
			mp[s[i]]++;
		}
		for(int i=0;i<t.size();i++)
		{
			mp2[t[i]]++;
		}
		for(int i=0;i<p.size();i++)
		{
			mp3[p[i]]++;
		}
		bool flag=0;
		for(char c='a';c<='z';c++)
		{
			if(mp[c]+mp3[c]<mp2[c])//判断
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			cout<<"NO"<<endl;
		}
		else cout<<"YES"<<endl;
	}
	return 0;
}
```


---

## 作者：唐一文 (赞：0)

~~这题可能没蓝题的难度?~~

------------

### 读题
把题意简化一下：  
给出$s,t,p$三个字符串，从$p$取出一些字符插入$s$中，能否变成$t$

------------

### 思路及部分$\mathrm{Code}$
题看懂，思路就很明显了
1. 判断$s$是否为$t$的子序列$($不一定为连续$)$，再把这个子序列删除  
一遍$\mathrm{for}$循环可以解决
```cpp
register int j=0;
for(register int i=0;i^t.size();++i){//相当于i!=t.size()
	if(!(s[j]^t[i])){//相当于s[j]==t[i]
		++j;//找下一位
		t.erase(i,1);//删除
		--i;//删除后t[i]变成t[i+1],不减就会跳过t[i+1]
	}
	if(!(j^s.size())){//s已经在t中找到了,相当于j==s.size()
		break;
	}
}
if(j^s.size()){//s不是t的子序列,相当于j!=s.size()
	printf("NO\n");
	continue;
}
```
2. 判断$t$的每个字符是否在$p$中出现  
一位一位地找是否在$p$中出现过，如果出现过就在$p$中删除  
双重循环即可解决
```cpp
j=0;
register bool flag=true;//用来判断这一位有没有找到
while(j^t.size() && flag){//相当于j<t.size()
	flag=false;
	for(register int i=0;i^p.size();++i){//相当于i<p.size()
		if(!(t[j]^p[i])){//相当于t[j]==p[i]
			++j;
			flag=true;
			p.erase(i,1);//删除
			break;//找到了,跳出循环,找下一位
		}
	}
}
if(j^t.size()){//t有字符没在p中出现过，相当于j!=t.size()
	printf("NO\n");
	continue;
}
printf("YES\n");
```

------------

### 完整无注释$\mathrm{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t,p;
int main(){
	register int T;
	scanf("%d",&T);
	for(register int _=0;_^T;++_){
		cin>>s>>t>>p;
		register int j=0;
		for(register int i=0;i^t.size();++i){
			if(!(s[j]^t[i])){
				++j;
				t.erase(i,1);
				--i;
			}
			if(!(j^s.size())){
				break;
			}
		}
		if(j^s.size()){
			printf("NO\n");
			continue;
		}
		j=0;
		register bool flag=true;
		while(j^t.size() && flag){
			flag=false;
			for(register int i=0;i^p.size();++i){
				if(!(t[j]^p[i])){
					++j;
					flag=true;
					p.erase(i,1);
					break;
				}
			}
		}
		if(j^t.size()){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
	}
	return 0;
}
```

---

