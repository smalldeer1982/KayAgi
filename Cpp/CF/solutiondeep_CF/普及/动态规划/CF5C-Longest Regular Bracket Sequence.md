# 题目信息

# Longest Regular Bracket Sequence

## 题目描述

This is yet another problem dealing with regular bracket sequences.

We should remind you that a bracket sequence is called regular, if by inserting «+» and «1» into it we can get a correct mathematical expression. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

You are given a string of «(» and «)» characters. You are to find its longest substring that is a regular bracket sequence. You are to find the number of such substrings as well.

## 样例 #1

### 输入

```
)((())))(()())
```

### 输出

```
6 2
```

## 样例 #2

### 输入

```
))(
```

### 输出

```
0 1
```

# AI分析结果

### 题目内容重写

#### 题目描述

这是一个关于正则括号序列的问题。

我们提醒你，一个括号序列被称为正则的，如果通过插入“+”和“1”可以得到一个正确的数学表达式。例如，序列“(())()”、“()”和“(()(()))”是正则的，而“)(”、“(()”和“(()))(”不是。

给你一个由“（”和“）”组成的字符串。你需要找到其中最长的正则括号子串，并统计这样的子串的数量。

#### 样例 #1

##### 输入

```
)((())))(()())
```

##### 输出

```
6 2
```

#### 样例 #2

##### 输入

```
))(
```

##### 输出

```
0 1
```

### 题解分析与结论

#### 综合分析

1. **栈的应用**：大多数题解都使用了栈来匹配括号，这是解决括号匹配问题的经典方法。
2. **动态规划**：部分题解引入了动态规划的思想，通过记录以每个位置结尾的最长合法子串长度，进一步优化了算法。
3. **标记数组**：一些题解使用了标记数组来记录哪些位置的括号是匹配的，然后通过查找最长连续匹配的括号序列来得到结果。
4. **时间复杂度**：所有题解的时间复杂度都是O(n)，能够处理最大长度为10^6的字符串。

#### 最优关键思路

1. **栈+动态规划**：结合栈和动态规划的思想，可以在一次遍历中同时完成括号匹配和最长合法子串长度的计算。
2. **标记数组**：通过标记数组记录匹配的括号，然后查找最长连续匹配的括号序列，这种方法简单直观，易于实现。

#### 扩展思路

1. **类似问题**：可以扩展到其他类型的括号匹配问题，如包含多种括号（{}、[]等）的匹配。
2. **优化空间**：可以通过优化空间复杂度，减少额外数组的使用，进一步提高算法效率。

#### 推荐题目

1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)

### 所选高星题解

#### 题解1：LuckyCloud (赞：44)

##### 星级：★★★★★

##### 关键亮点

- **思路清晰**：通过栈匹配括号，并使用标记数组记录匹配的括号，最后查找最长连续匹配的括号序列。
- **代码简洁**：代码结构清晰，易于理解。

##### 核心代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int sum,tot,l,r,len,w,ans,stack[1001003],top;
bool a[1001003];
char s[1000103];
int main()
{
  scanf("%s",s);
  len=strlen(s);
  for (int i=0;i<len;i++)
  {
   if (s[i]=='(') stack[++top]=i;
   else {if (top){a[stack[top]]=true;a[i]=true;top--;}}
  }
  for (int i=0;i<=len;i++)
   if (a[i]) w++;
   else {ans=max(w,ans);w=0;}
 for (int i=0;i<=len;i++)
   if (a[i]) w++;
   else {if (w==ans)tot++;w=0;}
 if (ans)
  printf("%d %d\n",ans,tot);
 else puts("0 1\n");
  return 0;
}
```

#### 题解2：linyinuo2008 (赞：9)

##### 星级：★★★★

##### 关键亮点

- **详细分析**：对题目进行了详细的分析，并提供了清晰的算法步骤。
- **代码优化**：使用了bool数组节省空间，代码效率高。

##### 核心代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e6+1;
char c[maxn];
int len,st[maxn];
bool a[maxn];
int maximum(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	int i,j,p=0,ans=0,sum=0,num=0;
	scanf("%s",c);
	len=strlen(c);
	for(i=0;i<len;i++)
	{
		if(c[i]=='(')
		{
			p++;
			st[p]=i;
		}
		else
		{
			if(p!=0)
			{
				a[st[p]]=1;
				a[i]=1;
				p--;
			}
		}
	}
	for(i=0;i<=len;i++)
	{
		if(a[i])
		{
			sum++;
		}
		else
		{
			ans=maximum(ans,sum);
			sum=0;
		}
	}
	for(i=0;i<=len;i++)
	{
		if(a[i])
		{
			sum++;
		}
		else
		{
			if(sum==ans)
			{
				num++;
			}
			sum=0;
		}
	}
	if(ans==0)
	{
		cout<<"0 1";
	}
	else
	{
		cout<<ans<<' '<<num;
	}
	return 0;
}
```

#### 题解3：Loner_Knowledge (赞：4)

##### 星级：★★★★

##### 关键亮点

- **动态规划**：引入了动态规划的思想，通过记录以每个位置结尾的最长合法子串长度，进一步优化了算法。
- **代码简洁**：代码结构清晰，易于理解。

##### 核心代码

```cpp
#include<cstdio>
#include<cstring>
int sta[1000001],head,ans[1000001];
char s[1000001];
int main() {
    int ans1=0,ans2=1;
    scanf("%s",s);
    for(int i=0;s[i];++i) {
        if(s[i]==')') {
            if(!head)
                continue;
            head--;
            ans[i]=i-sta[head]+1+ans[sta[head]-1];
            if(ans1==ans[i])
                ans2++;
            else if(ans1<ans[i]) {
                ans1=ans[i];
                ans2=1;
            }
        }
        else
            sta[head++]=i;
    }
    printf("%d %d",ans1,ans2);
    return 0;
}
```

### 个人心得总结

- **调试经历**：在实现过程中，需要注意栈的边界条件，特别是在处理右括号时，需要确保栈不为空。
- **顿悟感想**：通过引入动态规划的思想，可以进一步优化算法，减少不必要的遍历，提高代码效率。

### 通用建议与扩展思路

- **通用建议**：在处理括号匹配问题时，栈是最常用的数据结构，结合动态规划可以进一步优化算法。
- **扩展思路**：可以扩展到其他类型的括号匹配问题，如包含多种括号（{}、[]等）的匹配，或者处理更复杂的表达式匹配问题。

---
处理用时：52.79秒