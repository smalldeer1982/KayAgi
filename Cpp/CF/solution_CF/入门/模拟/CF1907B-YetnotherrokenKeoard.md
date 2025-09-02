# YetnotherrokenKeoard

## 题目描述

Polycarp 遇到了一个问题——他的笔记本电脑键盘坏了。

现在，当他按下小写字母 'b' 键时，它会像一种特殊的退格键一样：删除已经输入字符串中最后（最右边）的一个小写字母。如果输入的字符串中没有小写字母，那么这个按键会被完全忽略。

类似地，当他按下大写字母 'B' 键时，它会删除已经输入字符串中最后（最右边）的一个大写字母。如果输入的字符串中没有大写字母，那么这个按键会被完全忽略。

在这两种情况下，按下 'b' 或 'B' 键时，这两个字母都不会被添加到输入字符串中。

举个例子，按键序列为 "ARaBbbitBaby"。此时，输入字符串的变化如下："" $ \xrightarrow{\texttt{A}} $ "A" $ \xrightarrow{\texttt{R}} $ "AR" $ \xrightarrow{\texttt{a}} $ "ARa" $ \xrightarrow{\texttt{B}} $ "Aa" $ \xrightarrow{\texttt{b}} $ "A" $ \xrightarrow{\texttt{b}} $ "A" $ \xrightarrow{\texttt{i}} $ "Ai" $ \xrightarrow{\texttt{t}} $ "Ait" $ \xrightarrow{\texttt{B}} $ "it" $ \xrightarrow{\texttt{a}} $ "ita" $ \xrightarrow{\texttt{b}} $ "it" $ \xrightarrow{\texttt{y}} $ "ity"。

给定一系列按键序列，请输出每个序列处理完所有按键后的最终输入字符串。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12
ARaBbbitBaby
YetAnotherBrokenKeyboard
Bubble
Improbable
abbreviable
BbBB
BusyasaBeeinaBedofBloomingBlossoms
CoDEBARbIES
codeforces
bobebobbes
b
TheBBlackbboard```

### 输出

```
ity
YetnotherrokenKeoard
le
Imprle
revile

usyasaeeinaedofloominglossoms
CDARIES
codeforces
es

helaoard```

# 题解

## 作者：HashHacker_Peas (赞：2)

## 题目描述
Polycarp的笔记本键盘坏了。

现在，当他按下 `b` 键时，它的行为类似于退格键：删除已输入字符串中最后一个小写字母。如果已输入字符串中没有小写字母，则完全忽略该按键。

类似地，当他按下 `B` 键时，它删除已输入字符串中最后一个大写字母。如果已输入字符串中没有大写字母，则完全忽略该按键。

给定一个按键序列，输出处理所有按键后的结果。
## 分析
可以用 STL 中的 deque 来分别储存字符串中**大小写字符**与其**下标**（下称U队列与L队列），当遇到字符 `b` 或 `B` 时，只要弹出相应的队列的队尾就好了。（例如，当字符 $s_i$ 为 `b` 时，弹出L队列的队尾，对于U队列也是同样的道理）

对于输出，可以判断两个队列队头下标的大小，下标小的先出队。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
string s;
int t;
int main(){
    fastio;//加快读写速度
    cin>>t;
    while(t--){
        cin>>s;
        deque<pair<char,int>>u,l;//在c++14及以后，">>"的形式不会引起歧义了；同时这里的first储存字符，second储存下标
        for(int i=0;i<s.length();i++)
            if(s[i]=='b'&&!l.empty())
                l.pop_back();
            else if(s[i]=='B'&&!u.empty())
                u.pop_back();//非空就出队
            else if(isupper(s[i])&&s[i]!='B')
                u.push_back(make_pair(s[i],i));
            else if(islower(s[i])&&s[i]!='b')
                l.push_back(make_pair(s[i],i));
        while(!u.empty()||!l.empty())
            if(u.empty())
                cout<<l.front().first,l.pop_front();
            else if(l.empty())
                cout<<u.front().first,u.pop_front();
            else if(u.front().second<l.front().second)
                cout<<u.front().first,u.pop_front();
            else cout<<l.front().first,l.pop_front();
        cout<<"\n";//多测不换行，两眼泪汪汪
    }
    return 0;//大功告成!!!
}
```
It's my [AC记录](https://www.luogu.com.cn/record/139387175).

---

## 作者：abensyl (赞：2)

原题：[CF1907B YetnotherrokenKeoard](https://www.luogu.com.cn/problem/CF1907B)。

## 思路

考虑用两个栈分别维护大写字母和小写字母，当出现 `B` 的时候，如果大写字母栈有元素，就删去栈顶，出现 `b` 的时候同理删除小写字母栈的栈顶。

最后将两个栈内还剩的元素合并一下，按照原串顺序排好输出即可。

## 代码

```
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--) {
		string s;
		cin>>s;
		int n=s.size();
		vector<int> stk1,stk2;
		s=" "+s;
		for(int i=1;i<=n;++i) {
			if(s[i]=='B') {
				if(stk1.size()) stk1.pop_back();
			} else if(s[i]=='b') {
				if(stk2.size()) stk2.pop_back();
			} else {
				if(islower(s[i])) stk2.push_back(i);
				if(isupper(s[i])) stk1.push_back(i);
			}
		}
		for(auto c:stk2) stk1.push_back(c);
		sort(stk1.begin(),stk1.end());
		for(auto c:stk1) cout<<s[c];
		cout<<'\n';
	}
	return 0;
}
```
[我的 AC 记录](https://codeforces.com/contest/1907/submission/235872880)。

---

## 作者：Withershine (赞：2)

比较简单，建议评橙。

# 思路
对于每个给定的字符串，用两个大根堆来分别记录小写字母与大写字母，注意这里记录时**不要记录**大写的 `B` 和小写的 `b`。

每当出现一个 `B` 时，从记录大写字母的大根堆中取出目前最后录入的大写字母的位置，标记，接着弹出堆顶元素，标记。小写字母同理。

以上操作在遍历一遍字符串的情况下可以实现。

最后再遍历一遍字符串，输出未打标记的字符即可。**大写的 `B` 和小写的 `b`不要输出**。

# 代码
记得多测清空！！！！！！

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
priority_queue <ll> qx;
priority_queue <ll> qd;
//priority_queue <ll , vector<ll> , greater<ll>> q;
ll T;
char s[1000006];
signed main()
{
	// freopen("in.in" , "r" , stdin);
	// freopen("out.out" , "w" , stdout);
	scanf("%lld" , &T);
	while(T--)
	{
		while(!qx.empty())
		{
			qx.pop();
		}
		while(!qd.empty())
		{
			qd.pop();
		}
		scanf("%s" , s + 1);
		ll len = strlen(s + 1);
		fr(i , 1 , len)
		{
			qx.push(-i);
			qd.push(-i);
			if(s[i] >= 'a' && s[i] <= 'z' && s[i] != 'b')
			{
				qx.push(i);
			}
			else if(s[i] >= 'A' && s[i] <= 'Z' && s[i] != 'B')
			{
				qd.push(i);
			}
			if(s[i] == 'b')
			{
				ll del = qx.top();
				qx.pop();
				if(del >= 0)
				{
					s[del] = '!';
				}
				s[i] = '!';
			}
			if(s[i] == 'B')
			{
				ll del = qd.top();
				qd.pop();
				if(del >= 0)
				{
					s[del] = '!';
				}
				s[i] = '!';
			}
		}
		fr(i , 1 , len)
		{
			if(s[i] == '!')
			{
				continue;
			}
			cout << s[i];
		}
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：xh001 (赞：2)

# 思路
用两个栈分别记录所有未被删除的小写字母位置和大写字母位置，再用一个标记数组记录是否已被删除，根据题意模拟即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
ll T,n;
ll a[1000001],ta;//记录小写字母的位置。 
ll b[1000001],tb;//记录大写字母的位置。 
char s[1000001];
bool f[1000001];//记录是否被删除。 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		for(ll i=1;i<=n;i++) f[i]=0;//多测不清空，亲人两行泪。 
		cin>>(s+1);
		n=strlen(s+1);
		ta=tb=0;
		for(ll i=1;i<=n;i++)
		{
			if(s[i]>='a' && s[i]<='z' && s[i]!='b') a[++ta]=i;
            else if(s[i]>='A' && s[i]<='Z' && s[i]!='B') b[++tb]=i;
            else if(s[i]=='b')
            {
            	f[i]=1;
            	if(ta)
            	{
            		f[a[ta]]=1;
            		ta--;
				}
			}
			else if(s[i]=='B')
			{
				f[i]=1;
				if(tb)
				{
					f[b[tb]]=1;
					tb--;
				}
			}
		}
		for(ll i=1;i<=n;i++)
		{
			if(!f[i]) cout<<s[i];
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：Dawn_cx (赞：0)

题意：一个奇怪的键盘，按小写 $b$ 是删掉目前已经打的最后一个小写字母，按大写 $B$ 是删掉目前已经打的最后一个大写字母（如果没有则不删，打 $b/B$ 不会打出来字符只会删掉字符），给出键盘按下的顺序，求最后打出的内容。

个人做法是从头开始记录目前最后一个小写、大写字母的位置，然后遇到 $b/B$ 就删除那个位置的字符，并更新目前最后一个小写、大写字母的位置，写的比较麻烦。

赛后看题解发现倒序维护 $b/B$ 的数量，遇到大小写直接删除是最快的最方便的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+10;
const ll mod = 998244353;
inline void read(int &x){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
    x=s*w;
}
int n,t,len,l[N],L[N],p,P,lst[N],LST[N];
char s[N];
void solve(){
    scanf("%s",s);
    len=strlen(s);
    p=P=0;
    lst[0]=LST[0]=-1;
    for(int i=0;i<len;i++){
        if(s[i]>='A'&&s[i]<='Z'){
            if(s[i]=='B'){
                if(P){
                    s[L[P]]=0;
                    P--;
                }
                s[i]=0;
            }
            else L[++P]=i;
        }
        else{
            if(s[i]=='b'){
                if(p){
                    s[l[p]]=0;
                    p--;
                }
                s[i]=0;
            }
            else l[++p]=i;
        }
    }
    for(int i=0;i<len;i++){
        if(s[i]!=0)putchar(s[i]);
    }
    puts("");
}
int main(){
    read(t);
    while(t--)solve();
    return 0;
}
```

---

