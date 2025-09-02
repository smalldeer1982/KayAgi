# 题目信息

# Wonderful Coloring - 1

## 题目描述

This is a simplified version of the problem B2. Perhaps you should read the problem B2 before you start solving B1.

Paul and Mary have a favorite string $ s $ which consists of lowercase letters of the Latin alphabet. They want to paint it using pieces of chalk of two colors: red and green. Let's call a coloring of a string wonderful if the following conditions are met:

1. each letter of the string is either painted in exactly one color (red or green) or isn't painted;
2. each two letters which are painted in the same color are different;
3. the number of letters painted in red is equal to the number of letters painted in green;
4. the number of painted letters of this coloring is maximum among all colorings of the string which meet the first three conditions.

E. g. consider a string $ s $ equal to "kzaaa". One of the wonderful colorings of the string is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1551B1/c8856daa04b74978f65da846cae3db3aad690b80.png)The example of a wonderful coloring of the string "kzaaa".Paul and Mary want to learn by themselves how to find a wonderful coloring of the string. But they are very young, so they need a hint. Help them find $ k $ — the number of red (or green, these numbers are equal) letters in a wonderful coloring.

## 说明/提示

The first test case contains the string from the statement. One of the wonderful colorings is shown in the figure. There's no wonderful coloring containing $ 3 $ or more red letters because the total number of painted symbols will exceed the string's length.

The string from the second test case can be painted as follows. Let's paint the first occurrence of each of the letters "c", "o", "e" in red and the second ones in green. Let's paint the letters "d", "f" in red and "r", "s" in green. So every letter will be painted in red or green, hence the answer better than $ 5 $ doesn't exist.

The third test case contains the string of distinct letters, so you can paint any set of characters in red, as long as the size of this set doesn't exceed half of the size of the string and is the maximum possible.

The fourth test case contains a single letter which cannot be painted in red because there will be no letter able to be painted in green.

The fifth test case contains a string of identical letters, so there's no way to paint more than one letter in red.

## 样例 #1

### 输入

```
5
kzaaa
codeforces
archive
y
xxxxxx```

### 输出

```
2
5
3
0
1```

# AI分析结果

### 题目内容
# Wonderful Coloring - 1

## 题目描述
这是问题B2的简化版本。也许在开始解决B1之前，你应该先阅读问题B2。

保罗和玛丽有一个特别喜欢的字符串 $s$，它由拉丁字母表中的小写字母组成。他们想用两种颜色的粉笔：红色和绿色来给它上色。如果满足以下条件，我们称这种字符串的上色方式是美妙的：
1. 字符串中的每个字母要么被涂成一种颜色（红色或绿色），要么不被涂色；
2. 涂成相同颜色的任意两个字母是不同的；
3. 涂成红色的字母数量等于涂成绿色的字母数量；
4. 在所有满足前三个条件的字符串上色方式中，这种上色方式所涂字母的数量是最多的。

例如，考虑字符串 $s$ 等于 “kzaaa”。字符串的一种美妙上色方式如图所示。
![字符串“kzaaa”的美妙上色示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1551B1/c8856daa04b74978f65da846cae3db3aad690b80.png)

保罗和玛丽想自己学习如何找到字符串的美妙上色方式。但他们还很小，所以需要一个提示。帮助他们找到 $k$ —— 美妙上色中红色（或绿色，这两个数量相等）字母的数量。

## 说明/提示
第一个测试用例包含题目描述中的字符串。图中展示了一种美妙的上色方式。不存在包含3个或更多红色字母的美妙上色方式，因为涂色符号的总数将超过字符串的长度。

第二个测试用例中的字符串可以这样涂色。我们将字母“c”、“o”、“e”的第一次出现涂成红色，第二次出现涂成绿色。将字母“d”、“f”涂成红色，“r”、“s”涂成绿色。这样每个字母都会被涂成红色或绿色，因此不存在比5更好的答案。

第三个测试用例包含的字符串中字母都不同，所以你可以将任意一组字符涂成红色，只要这组字符的大小不超过字符串大小的一半且尽可能大。

第四个测试用例包含单个字母，由于没有字母可以涂成绿色，所以不能将其涂成红色。

第五个测试用例包含由相同字母组成的字符串，所以最多只能将一个字母涂成红色。

## 样例 #1
### 输入
```
5
kzaaa
codeforces
archive
y
xxxxxx
```
### 输出
```
2
5
3
0
1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，通过统计每个字母在字符串中出现的次数来确定美妙染色中红色（或绿色）字母的数量。对于出现次数大于等于2的字母，每种这样的字母可以贡献1对（一红一绿）染色；对于出现次数为1的字母，每两个这样的字母可以组成一对染色。所有题解的本质思路相同，只是在具体实现细节和代码风格上有所差异。

### 所选的题解
 - **作者：wanggk (赞：3)  星级：4星  关键亮点：思路清晰，代码简洁明了，直接阐述了根据字母出现次数分情况讨论的核心思路。**
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int T,n;
char s[55];
int cnt[26];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(cnt,0,sizeof(cnt));
		cin>>s;
		n=strlen(s);
		for(int i=0;i<n;i++) cnt[s[i]-'a']++;
		int ans=0,c=0;
		for(int i=0;i<26;i++)
		{
			if(cnt[i]>=2) ans++;
			else if(cnt[i]==1) c++;
		}
		ans+=c/2;
		printf("%d\n",ans);
	}
	return 0;
}
```
核心实现思想：用数组 `cnt` 统计每个字母出现的次数，遍历数组，对出现次数大于等于2的字母，`ans` 加1；对出现次数为1的字母，统计其数量 `c` ，最后 `ans` 加上 `c/2` 得到结果。

 - **作者：tongzhenxuan (赞：3)  星级：4星  关键亮点：对字母出现次数的分类讨论清晰，代码结构完整。**
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[10001];
int a[30],i;
void work()
{
	memset(a,0,sizeof(a));//清零计数数组 
	int l=strlen(ch);
	for(i=0;i<l;i++) a[ch[i]-'a'+1]++;//将每一个字母出现的次数累加 
	int f1=0,f2=0;//f1代表单个出现的字母，f2代表出现大于等于两次的字母 
	for(i=1;i<=26;i++)
	{
		if(a[i]>=2) f2++;
		else if(a[i]==1) f1++;
	}
	int sum=0;
	sum=f2+f1/2;//f2可以直接加入，一红一绿，单个出现则要找搭档，才能保证红色个数等于绿色个数 
	cout<<sum<<"\n";
}
int main()
{
	int T;
	cin>>T;
	while(T)
	{
		cin>>ch;
		work();
		T--;
	}
} 
```
核心实现思想：定义数组 `a` 统计字母出现次数，通过 `work` 函数分别统计出现次数为1的字母个数 `f1` 和出现次数大于等于2的字母个数 `f2`，最后计算 `f2 + f1/2` 得到结果。

 - **作者：断清秋 (赞：0)  星级：4星  关键亮点：对题意的转化清晰，代码注释详细，逻辑表述明确。**
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
string s;
ll t,n,m,a[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		ll sum=0,ans=0;
		for(ri i=97;i<=122;i++)
			a[i]=0;
		cin>>s;
		ll ls=s.size();
		for(ri i=0;i<ls;i++)
			a[(int)s[i]]++;
		for(ri i=97;i<=122;i++)
		{
			if(a[i]>=2)
				ans++;
			if(a[i]==1)
				sum++;
		}
		cout<<sum/2+ans<<endl;
	}
    back 0;
}
```
核心实现思想：用数组 `a` 统计每个字母出现次数，遍历数组，对出现次数大于等于2的字母，`ans` 加1；对出现次数为1的字母，统计其数量 `sum` ，最后计算 `sum/2 + ans` 得到结果。

### 最优关键思路或技巧
利用数组统计每个字母出现的次数，基于贪心思想，优先让出现次数大于等于2的字母各贡献一对染色，再将出现次数为1的字母两两配对染色，以达到美妙染色的要求。

### 同类型题或类似算法套路拓展
此类题目通常围绕字符串的字符统计与分配策略，类似套路是先统计字符出现频率，再依据特定规则进行分配或选择，以满足题目设定的条件。

### 推荐题目
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：同样是贪心策略，通过不断合并最小的果子堆来求最小总代价。
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则，利用贪心思想确定最优策略。
 - [P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据的分析，采用贪心策略对大臣进行排序以求解最大奖赏。 

---
处理用时：65.15秒