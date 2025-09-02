# Subsequence Permutation

## 题目描述

A string $ s $ of length $ n $ , consisting of lowercase letters of the English alphabet, is given.

You must choose some number $ k $ between $ 0 $ and $ n $ . Then, you select $ k $ characters of $ s $ and permute them however you want. In this process, the positions of the other $ n-k $ characters remain unchanged. You have to perform this operation exactly once.

For example, if $ s=\texttt{"andrea"} $ , you can choose the $ k=4 $ characters $ \texttt{"a_d_ea"} $ and permute them into $ \texttt{"d_e_aa"} $ so that after the operation the string becomes $ \texttt{"dneraa"} $ .

Determine the minimum $ k $ so that it is possible to sort $ s $ alphabetically (that is, after the operation its characters appear in alphabetical order).

## 说明/提示

In the first test case, we can choose the $ k=2 $ characters $ \texttt{"_ol"} $ and rearrange them as $ \texttt{"_lo"} $ (so the resulting string is $ \texttt{"llo"} $ ). It is not possible to sort the string choosing strictly less than $ 2 $ characters.

In the second test case, one possible way to sort $ s $ is to consider the $ k=6 $ characters $ \texttt{"_o__force_"} $ and rearrange them as $ \texttt{"_c__efoor_"} $ (so the resulting string is $ \texttt{"ccdeefoors"} $ ). One can show that it is not possible to sort the string choosing strictly less than $ 6 $ characters.

In the third test case, string $ s $ is already sorted (so we can choose $ k=0 $ characters).

In the fourth test case, we can choose all $ k=4 $ characters $ \texttt{"dcba"} $ and reverse the whole string (so the resulting string is $ \texttt{"abcd"} $ ).

## 样例 #1

### 输入

```
4
3
lol
10
codeforces
5
aaaaa
4
dcba```

### 输出

```
2
6
0
4```

# 题解

## 作者：MikeC (赞：0)

## 分析

要判断将字符串进行排序需要移动几个字符，自然只需要判断排序后的字符串和原字符串的差异即可。依次扫描原字符串和排序后的字符串的每一个字符，如果不同则表示原字符串的这一个字符需要与目标字符进行对换，此时累加答案即可。

可以把字符转为数字方便判断，时间复杂度 $O(n\log n)$。

## 代码

``````cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char a[51];
int c[51],b[51];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)cin>>a[i],c[i]=a[i]-96,b[i]=c[i];
		int ans=0;
		sort(b+1,b+1+n);
		for(int i=1;i<=n;i++)if(c[i]!=b[i])ans++;
		printf("%d\n",ans);
	}
}
``````



---

## 作者：Dragonbell_exp (赞：0)

### 题目大意：
有 t 组数据，每组数据会给你一个长度为 n 的字符串 s。
你可以选择 k 个数，并把这 k 个数排序。使字符串 s 最后按照字典序排序。问 k 的最小值

### 分析：
因为只需要输出需要排序的数的最小个数，所以我们无需考虑着 k 个数都是什么。

我们的目标仅是把字符串 s 按照字典序排序。也就是说，无论我们选的这 k 个数都是什么，只要能使 s 最终成为按照字典序排序的字符串就可以了。

再想一想，如果我们所选的数排好序后有的数相较与原先的位置没有变化，那么这一个数一定是不需要选的。

因为在这道题里，我们最后一定是把字符串 s 按照字典序排好了，在结合上面说的“位置没有发生变化的数一定不需要选择”，就可以得出结论：

#### 我们要输出的 k 就是字符串 s 在排序中位置发生改变的个数。

### 实现：
经过上述的分析，实现其实已经很明了了。

在读入字符串 s 之后，先为 s 排序，然后用排好序的 s 与没有排序的做对比，如果有的位置上的字符发生了改变，答案增加一。

### 代码：
```c
#include<iostream>
#include<algorithm>
using namespace std;
char s[10000];
char e[10000];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>s[i];
			e[i]=s[i];
		}
		sort(s+1,s+n+1);
		for(int i=1;i<=n;i++){
			if(s[i]!=e[i]){
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1552A)

题意：给一个长度为 $n$ 的字符串 $s$，可以选 $k$ 个字符，使这些字符的位置变为按字母表顺序排列（其余字符位置不变），求 $k$ 的最小值。

显然把原字符串排个序，比较一下有哪些字符位置发生了改变即可，位置改变的字符数量即为答案。

时间复杂度 $O(tnlogn)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
char a[1000],b[1000];
ll t,n,m,k;
int main()
{
	cin>>t;
	while(t--)
	{
		int sum=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		cin>>n;
		for(ri i=1;i<=n;i++)
		{
			cin>>a[i];
			b[i]=a[i];
		}
		sort(b+1,b+n+1);
		for(ri i=1;i<=n;i++)
			if(a[i]!=b[i])
				sum++;
		cout<<sum<<endl;
	}
    back 0;
}
```

---

