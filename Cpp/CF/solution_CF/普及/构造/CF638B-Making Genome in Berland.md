# Making Genome in Berland

## 题目描述

Berland scientists face a very important task - given the parts of short DNA fragments, restore the dinosaur DNA! The genome of a berland dinosaur has noting in common with the genome that we've used to: it can have $ 26 $ distinct nucleotide types, a nucleotide of each type can occur at most once. If we assign distinct English letters to all nucleotides, then the genome of a Berland dinosaur will represent a non-empty string consisting of small English letters, such that each letter occurs in it at most once.

Scientists have $ n $ genome fragments that are represented as substrings (non-empty sequences of consecutive nucleotides) of the sought genome.

You face the following problem: help scientists restore the dinosaur genome. It is guaranteed that the input is not contradictory and at least one suitable line always exists. When the scientists found out that you are a strong programmer, they asked you in addition to choose the one with the minimum length. If there are multiple such strings, choose any string.

## 样例 #1

### 输入

```
3
bcd
ab
cdef
```

### 输出

```
abcdef
```

## 样例 #2

### 输入

```
4
x
y
z
w
```

### 输出

```
xyzw
```

# 题解

## 作者：jch123 (赞：8)

# 题目大意
一个只由小写字母组成的字符串，且每个小写字母最多出现一次，现在给出这个字符串的 $n$ 个子串，求出符合条件的最短的合法串。
# 思路
找到哪些字符串的第一个字母没有没有前驱，从这些字母开始暴搜，再开一个动态数组维护每个字母后面的字母，搜索时直接调用。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char ans[105];//答案 
vector<int> A[30];//记录每个字母后面的字母 
int book[105],vis[105];//book用来dfs,vis用来标记前驱 
int len=0;
void dfs(int x)
{
	book[x]=1;//标记 
	ans[++len]=char('a'+x);//加到答案里
	for(int i=0;i<A[x].size();i++)
	{
		if(book[A[x][i]]==0)//没有用过
			dfs(A[x][i]);
	}
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=1;j<s.size();j++)
		{
			vis[s[j]-'a']=1;//标记为有前驱,如果之前没有前驱，那么现在就有了 
			A[s[j-1]-'a'].push_back(s[j]-'a');//记录每个字母后面的字母 
		} 
		if(vis[s[0]-'a']==0) 
			vis[s[0]-'a']=-1;//没有前驱 
	}
	for(int i=0;i<26;i++)
		if(vis[i]==-1)
			dfs(i);//当前字母没有前驱 
	for(int i=1;i<=len;i++)
		cout<<ans[i];
	return 0;
} 
```



---

## 作者：yangzd (赞：1)

# 题目大意：

一个只由小写字母组成的字符串，且每个小写字母最多出现一次，现在给出这个字符串的 $n$ 个子串，求出符合条件的最短的合法串。

# 分析：

根据输入的子串得到每个字符串的前驱和后继，之后从到大找出现过的字符中没有前驱的开始输出即可。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long t,pre[105],nex[105],flag[105];
char s[105];

signed main()
{
	ios::sync_with_stdio(0);
	
	memset(pre,-1,sizeof(pre));
    memset(nex,-1,sizeof(nex));
    memset(flag,0,sizeof(flag));
	
	cin >> t;
	
    while(t--)
    {
        cin >> s;
        
        flag[s[0]-'a']=1;
        
        for(long long i=1; i<strlen(s); i++)
        {   
            flag[s[i]-'a']=1;
            pre[s[i]-'a']=s[i-1]-'a';
            nex[s[i-1]-'a']=s[i]-'a';
        }
    }
    
    for(long long i=0; i<26; i++)
        if(pre[i]==-1 && flag[i])
        {
            long long j=i;
            
            while(true)
            {
                flag[j]=0;
                
                cout << j+'a';
                
                j=nex[j];
                
                if(j==-1)
					break;
            }
        }
        
    return 0;
}
```

---

