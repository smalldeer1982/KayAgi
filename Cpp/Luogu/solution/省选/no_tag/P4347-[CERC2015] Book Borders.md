# [CERC2015] Book Borders

## 题目描述

现有一本书,用固定宽度的字体和简单的贪婪算法来填充每行文字。书的内容是一个单词序列，每个单词包含一个或多个字符。

排版前，我们选择一个最大的行长度，并用m表示这个值。每行最多可以有m个字符，包括单词之间的空格字符。请使用排版算法简单地逐个处理单词，并在同一行上的两个连续单词之间打印每个单词，每个单词只有一个空格字符。而且如果在当前行上打印该字超过最大行长度m，则开始新行。
![](https://cdn.luogu.org/upload/pic/16228.png)
现在你得到了一个要排版的文本，并且正在试验最大行长度m的不同值。对于固定m，前导句是一个句子(由一个空格字符分隔的一系列单词)，由行的第一个单词从上到下组成。在上例中，当样本文本以最大行长度14进行排版时，前导句是“对你来说是n”（its to you n）
给定一个文本和两个整数a和b，找出a和b之间每个候选最大行长度的前导句长度。句子的长度是它包含的字符总数，包括空格字符

## 样例 #1

### 输入

```
its a long way to the top if you wanna rock n roll
13 16```

### 输出

```
22
12
12
15```

# 题解

## 作者：2018ljw (赞：3)

此题最大难度在于看出暴力复杂度是调和级数。

首先给所有单词长度和行长度均加一，简化掉对单词间空格和行末空格的处理。然后就可以贪心分段了。

可以直接前缀和二分解决，不过考虑到行长变长，行数减小，并且分段右移，所以直接对每个被分开的位置用一堆指针去维护，暴力移动、统计答案即可，如果某个指针移出界那么后面的指针就直接舍弃。

复杂度分析：不难发现复杂度与所有询问分行总数有关。假设所有单词长度均为 $l$，询问从 $l$ 到 $n$。则总数为 $l\times\frac nl+l\times\frac n{2l}+\ldots=n+\frac n2+\ldots\le n\ln n$，$l=1$ 时取等。

所以复杂度大概只有 $O(n\ln n)$ 不到。
```cpp
#include<cstdio>
#include<cstring>
char s[500001];
int n,d[500001],a,b;
int sum[500001];
int p[500001],top;
int main(){
	int i,j;
	while(1){
		scanf("%s",s+1);
		if(s[1]<='9')break;
		d[++n]=strlen(s+1)+1;
	}
	int l=strlen(s+1);
	for(i=1;i<=l;i++)a=a*10+s[i]-'0';
	scanf("%d",&b);
	a++;b++;
	for(i=1;i<=n;i++)sum[i]=sum[i-1]+d[i];
	for(i=1;i<=n;i++)if(sum[i]-sum[p[top]]>a)p[++top]=i-1;
	for(i=a;i<=b;i++){
		for(j=1;j<=top;j++){
			if(p[j]<p[j-1])p[j]=p[j-1]+1;
			while(p[j]<=n&&sum[p[j]]-sum[p[j-1]]<=i)p[j]++;
			if(p[j]>n)top=j-1;p[j]--;
		}
		int res=0;
		for(j=0;j<=top;j++)res+=d[p[j]+1];
		printf("%d\n",res-1);
	}
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

暴力好题。

先想想最原始的解法。我们每次向后跳 $m$ 格，然后如果发现再单词中间，再往回走到这个单词的开头，再计算长度。但是，这样肯定是会超时，所以，我们想一想能不能优化。

很容易发现，我们直接预处理每一个单词开头的位置和单词的长度，这样每次会跳的时间复杂度与计算的复杂度就是 $O(1)$ 的，可以极大的优化时间复杂度，长度不断递增，就按最坏算（从 $1$ 开始），那复杂度最坏就是 $O(n(\frac11+\frac12+\dots+\frac1n)) \approx O(n \log n)$，可以通过本题。

```
#include<bits/stdc++.h>

using namespace std;

#define up(i, l, r) for (int i = l; i <= r; i++)
#define dw(i, l, r) for (int i = l; i >= r; i--)

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	getline(cin, s);
	int n = s.size(), a, b;
	cin >> a >> b;
	vector<int> st(n + b + 1, 0), len(n + 5, 0);
	fill(begin(st) + n, end(st), n); // 防止死循环
	for (int i = 0, p = 0; i < n; i++) {
		if (s[i] == ' ') p = i + 1;
		st[i] = p;
		if (i >= p) len[p]++;
	} // 记录开头位置
	up(m, a, b) {
		int res = 0;
		for (int p = 0; p < n; p = st[p + m])
			res += len[p] + 1;
		cout << res - 1 << '\n';
    // 这里的答案实际上就是单词长度和期间的空格的长度之和
    // 我计算的时候算的是每一个单词跟一个空格，所以会多算一个空格
	}
	return 0;
}

```

所以，这道紫就这么水灵灵的写完了？

---

## 作者：ZJMZJM (赞：1)

~~I'm so vegetable.~~

这道题一看，是道灰题，但看了题目就发现也没那么难啊。

不就是暴力模拟嘛。

只需记录每个单词的长度和离当前位置最近的上一个结束位置。

所以是道大水题啦...

code
```
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define For(k,i,j) for(int k=i;k<=j;k++)//for循环的简写
#pragma GCC optimize(4)//O4
#define ll long long
#define MAXN 1000005
using namespace std;
char str[MAXN];//字符串
int pre[MAXN];
int len[MAXN];
int main()
{
    int n;
    while(gets(str)!=NULL)//读入
    {
        int sz=strlen(str); 
		str[sz]=' ';
        int flag=0,last=0,cnt=0;
        memset(pre,0,sizeof(pre));
        For(i,0,sz)//每个单词的长度和离当前位置最近的上一个结束位置
		{
            if(str[i+1]==' ') 
				pre[i]=i;
            else pre[i]=i==0?0:pre[i-1];
            if(!flag&&str[i]!=' ') 
			{
                flag=1;
                last=i;
                cnt=0;
            }
            if(flag&&str[i]==' ') 
			{
                flag=0;
                len[last]=cnt;
            }
            cnt++;
        }
        int a,b; 
		scanf("%d%d\n",&a,&b);
        For(i,a,b)//计算总长度，即答案
		{
            int cur=0,ans=0;
            while(cur<sz) 
			{
                ans+=len[cur]+1;
                cur=pre[min(cur+i-1,sz-1)]+2;
            }
            printf("%d\n",ans-1);//输出
        }
    }
    return 0;
}
```
关于时间复杂度：

在暴力枚举过程中，行宽越大，枚举的次数越少。

那么整体时间复杂度为 n(1/1 + 1/2 + 1/3 + ... + 1/n) = nlnn 不会超出时限.

---

