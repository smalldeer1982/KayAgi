# 题目信息

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

# AI分析结果

### 题目内容
# 删改编辑

## 题目描述
黛西喜欢玩文字游戏。最近，她一直在和丹尼尔玩下面描述的删改文字游戏。

游戏按以下方式进行：黛西最初选择一个单词，例如“DETERMINED”。在游戏的每个回合中，丹尼尔选择一个字母，例如“E”，接下来黛西删除该单词中出现的第一个此字母，此时她得到“DTERMINED”，该回合结束。

在后续回合中，丹尼尔依次选择“D”“I”“N”“D”，黛西依次得到“TERMINED”“TERMNED”“TERMED”“TERME”。现在，如果丹尼尔选择“E”，黛西会得到“TRME”。但如果她最初选择的单词是“DETERMINED”，黛西不可能得到“TERM”这个单词。

黛西现在好奇，给定初始单词时，她能否在0个或多个回合内通过这个游戏得到她选择的最终单词。你的任务是帮助她判断这是否可行。

## 样例 #1
### 输入
```
6
DETERMINED TRME
DETERMINED TERM
PSEUDOPSEUDOHYPOPARATHYROIDISM PEPA
DEINSTITUTIONALIZATION DONATION
CONTEST CODE
SOLUTION SOLUTION
```
### 输出
```
YES
NO
YES
NO
NO
YES
```
### 算法分类
字符串

### 题解综合分析与结论
这些题解主要围绕如何判断通过特定删除操作能否从初始字符串得到目标字符串展开。
 - **思路方面**：多数题解利用了每次删除首次出现字母，使得目标字符串中的字母应尽量取自初始字符串靠后位置这一特性。有的通过记录字符位置和出现次数判断，有的使用BFS枚举尝试所有可能删除情况。
 - **算法要点**：涉及字符串基本操作，如查找、截取等，部分运用贪心策略，确保目标字符串字符在初始字符串中取最靠后位置以满足条件。
 - **解决难点**：核心是如何准确模拟删除操作并判断最终能否得到目标串，需处理字符出现次数及位置关系，避免遗漏或错误判断。

### 所选的题解
 - **作者：yeshubo_qwq（4星）**
    - **关键亮点**：思路简洁清晰，通过记录目标字符串字符在初始字符串中的位置并判断是否升序来确定能否转换，代码实现高效，利用数组巧妙保存和处理字符位置信息。
    - **核心代码实现思想**：先记录每个字符在初始字符串中的出现位置，再根据目标字符串倒着取字符位置，判断位置是否升序。
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
		for (i=0;i<26;i++) b[i]=0;
		for (i=0;i<n;i++) a[s1[i]-'A'][++b[s1[i]-'A']]=i;
		for (i=0;i<26;i++) c[i]=b[i]+1;
		flag=1;
		for (i=m-1;i>=0;i--)
			if (--c[s2[i]-'A']>=1) d[i]=a[s2[i]-'A'][c[s2[i]-'A']];
			else flag=0;
		for (i=1;i<m;i++)
			if (d[i-1]>d[i]) flag=0;
		cout<<(flag==0?"NO\n":"YES\n");
	}
	return 0;
}
```
 - **作者：IvanZhang2009（4星）**
    - **关键亮点**：利用vector记录字符位置，思路清晰，通过检查目标字符串字符在初始字符串中的出现次数和顺序来判断，逻辑严谨。
    - **核心代码实现思想**：用vector记录每个字符在初始字符串中的位置，遍历目标字符串，检查字符出现次数并记录位置，最后判断位置顺序。
```cpp
string s,t;
void Main() {
	cin>>s>>t;
	vector<int>a[200];
	int b[200];
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
  if(b[t[i]]>=a[t[i]].size()){
      cout<<"NO\n";
      return;
  }else{
      v.pb(a[t[i]][a[t[i]].size()-b[t[i]]-1]);
      b[t[i]]++;
  }
	if(v.size()<t.size()){
		cout<<"NO\n";
		return;
	}
	REP(i,1,v.size())
	if(v[i]>v[i-1]){
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
}
```
 - **作者：an_ancient_ghoul（4星）**
    - **关键亮点**：从后往前查找字符最后一次出现位置，利用栈来检查顺序，思路独特，代码简洁高效，在处理过程中注重细节，如清栈操作对效率有影响。
    - **核心代码实现思想**：先记录目标字符串字符出现次数，从后往前遍历初始字符串，将相关字符入栈，最后通过栈检查与目标字符串是否匹配。
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
		while(!st.empty())st.pop();
		si=0;t=1;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(len,0,sizeof(len));
		scanf("%s%s",a,b);
		for(int i=maxx;i>=0;i--)
		{
			if('A'<=b[i]&&b[i]<='Z')
			{
				len[b[i]-'A']++;
				si=max(si,i);
			}
		}
		for(int i=maxx;i>=0;i--)
		{
			if('A'<=a[i]&&a[i]<='Z')
			{
				if(len[a[i]-'A'])
				{
					st.push(a[i]);
					len[a[i]-'A']--;
				}
			}
		}
		k=st.size();
		if(k!=si+1)
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
		while(!st.empty())st.pop();
		if(t) printf("YES\n");
		else	printf("NO\n");
	}
	return 0;
}
```
### 最优关键思路或技巧
利用从后往前查找字符位置的方法，结合记录字符出现次数和顺序来判断能否从初始字符串转换为目标字符串。如记录每个字符在初始字符串中的位置，通过检查目标字符串字符位置是否升序（或利用栈检查顺序），以及字符出现次数是否满足要求，高效解决问题。

### 同类型题或类似算法套路拓展
此类题目通常围绕字符串的特定操作和判断展开，关键在于理解操作对字符串结构的影响，抓住每次操作删除首次出现字母这一特性，转化为对字符位置和出现次数的分析。类似套路可应用于其他字符串变换可行性判断问题，通过记录关键信息（如位置、次数）并结合特定数据结构（数组、vector、栈等）辅助判断。

### 洛谷相似题目推荐
 - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串查找和统计，与本题对字符串特定操作和判断有相似之处。
 - [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：虽涉及数学运算，但在处理数据和判断条件方面与本题有相通思路。
 - [P2219 数的分解](https://www.luogu.com.cn/problem/P2219)：通过枚举和判断条件解决问题，与本题在逻辑判断上有类似之处。

### 个人心得摘录与总结
 - **作者an_ancient_ghoul**：清栈操作对程序效率影响较大，放在不同位置可能导致不同结果，如开始不清栈可能出现玄学问题，最后不清栈会影响运行时间和内存占用，强调了细节对程序性能的重要性。 

---
处理用时：73.36秒