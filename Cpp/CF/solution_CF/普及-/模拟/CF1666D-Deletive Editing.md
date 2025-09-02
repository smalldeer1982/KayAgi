# Deletive Editing

## 题目描述

Daisy 喜欢玩有关文字的游戏。最近，她一直在和 Daniel 玩下面描述的删除与编辑的文字游戏。

这个游戏按以下描述的方式进行：Daisy 最初选择一个词，例如 `DETERMINED`。在游戏的每个回合里，Daniel 选择一个字母，例如 `E`，接下来 Daisy 删除掉在这个词中出现的第一个这个字母，这时她得到 `DTERMINED`，这个回合结束。

在下面的回合中，Daniel 依次选择 `D`、`I`、`N`、`D`，而 Daisy 依次得到 `TERMINED`、`TERMNED`、`TERMED`、`TERME`。现在，如果 Daniel 选择 `E`，Daisy 会得到 `TRME`。但如果她最开始选择的词为 `DETERMINED`，Daisy 将不可能得到 `TERM` 这个词。

Daisy 现在好奇在给定初始的词时，她能否在 $0$ 个或多个回合内通过这个游戏得到她选择的最终词。你的任务是帮助她判断这是否可行。

## 样例 #1

### 输入

```
6
DETERMINED TRME
DETERMINED TERM
PSEUDOPSEUDOHYPOPARATHYROIDISM PEPA
DEINSTITUTIONALIZATION DONATION
CONTEST CODE
SOLUTION SOLUTION```

### 输出

```
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：Night_sea_64 (赞：4)

大家好，本蒟蒻又来写题解了。这道题~~比较简单~~。

[题目传送门](https://www.luogu.com.cn/problem/CF1666D)

这道题要用到的知识点有：字符串基本操作和贪心。

因为每次只能删去最前面的，所以后面的字母更容易被保留。想到这一点，贪心策略就出来了。就是在 $s$ 中找最靠后并且等于 $t$ 的子序列。

怎么保证它一定是最靠后的子序列呢？只要我们保证 $t$ 的最后一个字符靠后，$t$ 的倒数第二个字符也能更靠后……以此类推。

如果已经是最靠后的子序列了，还会有其中的一些字符被删去，这样就不可能满足要求了。

我们可以用 $cnts$ 记录当前字符在 $s$ 中出现的次数，用 $cntt$ 记录在 $t$ 中出现的次数。这样用 $cnts-cntt$ 就是这个字符要删的个数。再用一个 $pos$ 记录当前字符在 $s$ 中是相同字符中的第几个。

因为删的肯定是第 $1\sim cnts-cntt$ 个。所以如果 $pos≤cnts-cntt$，那么说明这个字符会被删去。

还有一种情况，就是有些字符出现在 $t$ 中但是没有出现在 $s$ 中，或者 $cnts<cntt$，也不可能。

AC 代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        string s,t;
        bool flag=1;
        cin>>s>>t;
        int cur=t.size()-1;
        for(int i=s.size()-1;i>=0;i--)
            if(s[i]==t[cur])
            {
                cur--;
                int cnts=0,cntt=0,pos=0;
                //cnts 表示当前字符在 s 中出现的次数。
                //cntt 表示当前字符在 t 中出现的次数。
                //pos 表示当前字符在 s 中是相同字符中的第几个。
                for(int j=0;j<t.size();j++)
                    cntt+=t[j]==s[i];
                for(int j=0;j<s.size();j++)
                {
                    cnts+=s[j]==s[i];
                    if(j==i)pos=cnts;
                }
                if(cnts<cntt||pos<=cnts-cntt)//不可能出现的情况。
                {
                    flag=0;
                    break;
                }
            }
        if(flag&&cur<0)cout<<"YES"<<endl;
        //cur<0 说明有一个字符在 s 中压根就没找到。
        else cout<<"NO"<<endl;
    }
    return 0;
}
```

这个时间复杂度有点高。应该可以优化。

---

## 作者：_Starlit__Sky_ (赞：3)

# 洛谷 CF1666D 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1666D)
## 题目算法

BFS 枚举

## 题目思路

使用 BFS 遍历 尝试删除存在于字符串中每一个第一次出现过的字母

## 代码

```python
n = int(input())
for _ in range(n):
    bfs,end = input().split(' ')
    bfs = [bfs]
    find = False
    while bfs:
        # 队头出队
        head = bfs.copy()
        bfs = []
        for i in head: # 遍历
            if i == end: # 找到目标字符串
                find = True
                break
            if not i or len(i) < len(end): continue # 判断合法性
            for j in range(65,91): # 尝试删除存在于字符串中每一个第一次出现过的字母
                index = i.find(chr(j))
                if index > -1: bfs.append(i[:i.find(chr(j))] + i[i.find(chr(j)) + 1:])
    if find: print('YES')
    else: print('NO')
```


---

## 作者：yeshubo_qwq (赞：1)

思路：

因为每次删掉的字母都是第一个出现的，因此，最后目标字符串剩下的字符都是初始字符串的最后的字符，将它们在初始字符串的位置保存下来，判断是否升序即可。

个人感觉倒着做比较方便。

详细注释见代码。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,i,a[30][35],b[30],c[30],d[35],flag;
string s1,s2;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--){
		cin>>s1>>s2;n=s1.size();m=s2.size();
		for (i=0;i<26;i++) b[i]=0;//每个字符出现次数清零 
		for (i=0;i<n;i++) a[s1[i]-'A'][++b[s1[i]-'A']]=i;//保存每个字符的出现位置 
		for (i=0;i<26;i++) c[i]=b[i]+1;//每次先减一，因此要总数+1 
		flag=1;//默认可以 
		for (i=m-1;i>=0;i--)//倒着取 
			if (--c[s2[i]-'A']>=1) d[i]=a[s2[i]-'A'][c[s2[i]-'A']];//保存在初始字符串的位置 
			else flag=0;//个数不足则不行 
		for (i=1;i<m;i++)
			if (d[i-1]>d[i]) flag=0;//必须升序，否则不行 
		cout<<(flag==0?"NO\n":"YES\n");
	}
	return 0;
}
```


---

## 作者：IvanZhang2009 (赞：1)

## 题意
有一个单词，每次删除任意一个字母第一次出现的地方，问最后是否可能得到另一个单词。

## 解法
因为每次删字母都删第一次出现的那个，那么最后剩下的只能是这个字母最后出现的若干次。

考虑记录每个字母出现的位置，记录在 ``vector`` 里。然后跑一遍 $t$，找到每个 $t$ 中的字母在 $s$ 中的出现位置。注意同时记录在 $t$ 中这个字母出现过几次，如果出现次数大于 $s$ 中出现的次数，输出 $\texttt{NO}$。

最后判断一下出现顺序是否有序。如果是有序的，输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

详见代码。

## 代码

```cpp
string s,t;
void Main() {
	cin>>s>>t;
	vector<int>a[200];  //记录每个字母出现的位置
	int b[200];         //记录在t中这个字母出现过几次
	memset(b,0,sizeof(b));
  REP(i,0,s.size())
  a[s[i]].pb(i);
  REP(i,0,t.size())
  if(!(a[t[i]].size())){
    cout<<"NO\n";
    return;
  }
  vector<int>v;
  for(int i=t.size()-1;i>=0;i--)
  if(b[t[i]]>=a[t[i]].size()){   //s没有足够多的字母
      cout<<"NO\n";
      return;
  }else{
      v.pb(a[t[i]][a[t[i]].size()-b[t[i]]-1]);  //记录t的每个字母在s中出现的顺序
      b[t[i]]++;
  }
	if(v.size()<t.size()){
		cout<<"NO\n";
		return;
	}
	REP(i,1,v.size())   //判断出现顺序是否有序
	if(v[i]>v[i-1]){
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
}
```

---

## 作者：an_ancient_ghoul (赞：1)

# CF1666D 题解
[原题传送](https://codeforces.com/problemset/problem/1666/D)  
## 大意：  
给定两个字符串通过删除**单个字符**（并不改变顺序）使 $s$ 最终变为 $t$ 。若可以输出"YES",反之输出"NO"。
## Input:
第一行一个整数 $n(1 \leq n \leq 10,000)$  
接下来 $n$ 行，每行两个字符串 $s$ 和 $t$ 。
## Output:
$n$ 行，每行一个字符串"YES"或"NO"
## Solution:
(本人现以75ms/8.00KB最优解第一）此时可知，其实我们只需要从后往前找就可以了。在 $s$ 中查找这些字符最后一次出现的位置，并将其记录。最后再检查是否符合 $t$ 的顺序。  
注意，因为是从后往前读，比较是反着比，所以我用了栈。
## code:  
```cpp
#include<bits/stdc++.h>
#define maxx 31
using namespace std;
char a[39],b[39],c[39];
int n,si,sc,t,k;
stack<char> st;
int len[30];
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		while(!st.empty())st.pop();//防玄学清栈，
      //最开始不知为何放在后面莫名清不干净栈
		si=0;t=1;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(len,0,sizeof(len));//原因见下：
		scanf("%s%s",a,b);
		for(int i=maxx;i>=0;i--)
		{
			if('A'<=b[i]&&b[i]<='Z')
			{
				len[b[i]-'A']++;//用一个数组记下t中字符的出现次数
				si=max(si,i);//记下t的长度
			}				
		}
		for(int i=maxx;i>=0;i--)
		{
			if('A'<=a[i]&&a[i]<='Z')
			{
				if(len[a[i]-'A'])
				{
					st.push(a[i]);//每找到一个就入栈
					len[a[i]-'A']--;//注意！如果中断会清不干净
				}
			}
		}
		k=st.size();
		if(k!=si+1)//长度不相等则直接无视
		{
			printf("NO\n");
			continue;
		}
		sc=0;
		
		while(!st.empty())
		{
			if(b[sc++]!=st.top())
			{
				t=0;
				break;
			}
			st.pop();
		}
		while(!st.empty())st.pop();//清栈，原因同上
     //不加这个121ms/12KB，加了75ms/8KB？？？Why
     //只有这个还WA了，望各位神犇解答。
		if(t) printf("YES\n");
		else	printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Dedaka (赞：1)

## 题意简述

------------
- 给定 $n$ 组数据，每组数据包括两个字符串，原串 $s$ 和目标串 $t$。

- 每次操作可指定原串中任意一个字母，将原串中第一次出现的该字母删去。

- 询问是否可以将原串转化为目标串。

- $1 \leq n \leq 10^4$，$1 \leq \left| t \right| \leq \left| s \right| \leq 30$。

## 题目分析

------------
本题考查知识点：**字符串** 以及 **贪心**。

### 思路

------------
我一开始没发现字母 **可重**，结果写假了，后来我想出了一个易懂但是跑得挺慢的做法。

首先用一个数组倒序记录目标串中每个字母 **从后往前** 是第几次出现的，再用一个数组，以相同的方式处理原串中与目标串有关字母。接着，用一个指针标记当前指向的目标串的字母（从下标 $0$ 开始）。遍历一遍原串，如果当前原串字母是指向的目标串的字母，且两者出现次序相同，说明发现了可能的情况，指向变量后移。

最后，如果指针将目标串的每个字母都指过了，说明 **完全匹配** ，可以做到转化。

该写法的贪心之处在于匹配过程之中，必须两者出现次序相同才能成功匹配这一个字母。如果出现次序不同，说明后面还有需要消除的该字母。而每次操作是删去最前面的该字母，会破坏这一状态，不合法。

### 细节

------------
注意清空数组，同时我的程序跑得慢大概就是清空的这一部分。

## 代码

------------
```cpp
#include<bits/stdc++.h>
#define mx 30
using namespace std;
int n,a[mx],b[mx],f1[mx],f2[mx];
string s1,s2;
int main(){
	cin>>n;
	while(n--){
		cin>>s1>>s2;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));//清空 awa 
		int l1=s1.length(),l2=s2.length();
		for(int i=l2-1;i>=0;i--){
			int tmp=s2[i]-'A';
			a[i]=++f1[tmp];
		}
		for(int i=l1-1;i>=0;i--){
			int tmp=s1[i]-'A';
			if(f1[tmp]){
				b[i]=++f2[tmp];
			}
		}//倒序预处理 
		int cnt=0;//指向 
		for(int i=0;i<l1;i++){
			if(b[i]==a[cnt]&&s1[i]==s2[cnt]){
				cnt++;//当前原串字母是指向的目标串字母
			}//且两者出现次序相同
		}
		if(cnt==l2){//全部匹配 
			puts("YES");
		}else{
			puts("NO");
		}
	}
	return 0;
}
```

### 其他的话
------------
有神犇能优化本蒟蒻这种做法的欢迎在评论区指出，谢谢 awa

---

