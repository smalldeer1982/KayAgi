# 题目信息

# Vasya and Multisets

## 题目描述

Vasya has a multiset $ s $ consisting of $ n $ integer numbers. Vasya calls some number $ x $ nice if it appears in the multiset exactly once. For example, multiset $ \{1, 1, 2, 3, 3, 3, 4\} $ contains nice numbers $ 2 $ and $ 4 $ .

Vasya wants to split multiset $ s $ into two multisets $ a $ and $ b $ (one of which may be empty) in such a way that the quantity of nice numbers in multiset $ a $ would be the same as the quantity of nice numbers in multiset $ b $ .

## 样例 #1

### 输入

```
4
3 5 7 1
```

### 输出

```
YES
BABA
```

## 样例 #2

### 输入

```
3
3 5 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# Vasya和多重集

## 题目描述
Vasya有一个由n个整数组成的多重集s。Vasya将在多重集中恰好出现一次的数称为“好数”。例如，多重集{1, 1, 2, 3, 3, 3, 4}包含好数2和4。
Vasya想将多重集s拆分为两个多重集a和b（其中一个可以为空），使得多重集a中的好数数量与多重集b中的好数数量相同。

## 样例 #1
### 输入
```
4
3 5 7 1
```
### 输出
```
YES
BABA
```

## 样例 #2
### 输入
```
3
3 5 1
```
### 输出
```
NO
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于对数字出现次数进行分类讨论来判断是否可分及如何划分。主要要点为：将数字按出现次数分为出现1次、出现2次、出现次数≥3次这几类。出现1次的数字直接贡献一个好数；出现2次的数字无论如何分配，对两个集合好数数量差值无影响；出现次数≥3次的数字可通过合理分配来调整两个集合好数数量。难点在于准确分析各类数字对结果的影响并据此构造划分方案。各题解整体思路相近，在代码实现上各有不同，如计数方式、遍历方式以及输出方案的构造细节等。

### 所选的题解
 - **作者：傅天宇 (赞：3)  星级：4星  关键亮点：代码逻辑清晰，通过预处理统计各类数字数量，然后根据不同条件进行输出方案的构造，注释详细**
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
inline void write(int x)
{
    if(x<0) putchar('-'),write(-x);
    else{if(x>9)write(x/10);putchar('0'+x%10);}
}
inline void writeputs(int x){write(x),putchar('\n');}
inline void writeputchar(int x){write(x),putchar(' ');}
int n,a[105],tong[105],ANS,ans;
bool flag;
int main()
{
    n=read();
    FOR(i,1,n) a[i]=read(),tong[a[i]]++;
    FOR(i,1,100)
    {
        if(tong[i]==1) ANS++;
        if(tong[i]>=3) ans++;
    }
    if(ans>=1&&ANS%2==1) flag=1,puts("YES");
    else if(ANS%2==0) puts("YES");
    else 
    {
        puts("NO");
        return 0;
    }
    int num=0;
    if(ANS%2==0)
    {
        FOR(i,1,n) 
        {
            if(tong[a[i]]==1&&num<ANS/2) putchar('A'),num++;
            else putchar('B');
        }
        return 0;
    }
    if(ANS%2==1)
    {
        FOR(i,1,n)
        {
            if(tong[a[i]]==1&&num<=ANS/2-1) putchar('A'),num++;
            else if(tong[a[i]]==1&&num>=ANS/2) putchar('B');
            else if(tong[a[i]]>=3&&flag) putchar('A'),flag=0;
            else putchar('B');
        }
    }
    return 0;
}
```
核心实现思想：先读入数据并统计每个数字出现次数，遍历统计出现1次和出现次数≥3次的数字个数，根据这两个统计结果判断是否有解。有解时，根据出现1次数字个数的奇偶性构造输出方案。

 - **作者：Na2PtCl6 (赞：0)  星级：4星  关键亮点：使用vector存储不同出现次数的数字位置，代码结构清晰，逻辑连贯**
```cpp
#include<bits/stdc++.h>
using namespace std;
char dv[]={'A','B'},res[104];
int n,once,var,a[104],cnt[104];
vector< int > num[104];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		++cnt[a[i]];
	}
	for(int i=1;i<=n;i++)
		num[cnt[a[i]]].push_back(i);
	for(int i=1;i<=100;i++){
		if(cnt[i]==1)
			++once;
		if(cnt[i]>=3)
			++var;
		
	}
	once%=2;
	if(once==0){
		puts("YES");
		int sw=0;
		for(int i:num[1]){
			res[i]=dv[sw];
			sw^=1;
		}
		for(int i=2;i<=n;i++)
			for(int j:num[i])
				res[j]='B';
		puts(res+1);	
		return 0;
	}
	if(var){
		puts("YES");
		int sw=0;
		for(int i:num[1]){
			res[i]=dv[sw];
			sw^=1;
		}
		vector< int > tmp;
		for(int i=2;i<=n;i++)
			for(int j:num[i])
				tmp.push_back(j);
		res[tmp.back()]='B';
		tmp.pop_back();
		for(int i:tmp)
			res[i]='A';
		puts(res+1);
	}
	else
		puts("NO");
	return 0;
}
```
核心实现思想：读入数据并统计每个数字出现次数，将不同出现次数的数字位置存入对应的vector中。根据出现1次数字个数的奇偶性及是否有出现次数≥3次的数字判断并构造输出方案。

 - **作者：Light_Star_RPmax_AFO (赞：0)  星级：4星  关键亮点：代码简洁明了，通过简洁的分类讨论和模拟输出方案，逻辑清晰**
```cpp
#include <bits/stdc++.h>
#define rint register int
using namespace std;

inline int read(){
  int f = 1,x = 0;
  char ch = getchar();
  while(!isdigit(ch)){
	if(ch == '-')f = -1;
  	ch = getchar();
  }
  while(isdigit(ch)){
  	x = (x << 1) + (x << 3) + (ch ^ 48);
  	ch = getchar();
  }
  return x * f;
}
inline void print(int x){
	if(x > 9)print(x / 10);
  putchar(x % 10 + '0');
}

int a[101], g[101];

signed main(){
	int n = read();
	for(rint i = 1; i <= n; ++i)
		a[g[i] = read()]++;
	rint sum = 0, cnt = 0;
	for(rint i = 1; i <= 100; ++i)
		if(a[i] == 1)sum++;
		else if(a[i] >= 3)cnt++;
	bool ok = 0;
	if(sum & 1)
	{
		if(cnt >= 1)
		{
			puts("YES");
			ok = 1;
			rint num = 0;
			for(rint i = 1; i <= n; ++i)
			{
				if(a[g[i]] == 1 && num <= (sum >> 1))
				{
					putchar('A'), ++num;
				}else
				{
					if(a[g[i]] == 1 && num > (sum >> 1))
					{
						putchar('B'); 
					}else
					{
						if(a[g[i]] >= 3 && ok)
						{
							putchar('B');
							ok = 0;
						}else{
							putchar('A');
						}
					}
				}
			}
		}else
		{
			puts("NO");
			return 0;	
		}
	}else
	{
		puts("YES");
		rint num = 0;
		for(rint i = 1; i <= n; ++i){
			if(a[g[i]] == 1 && num < (sum >> 1))
				putchar('A'), ++num;
			else putchar('B');
		}
	}
  return 0;
}
```
核心实现思想：读入数据并通过数组统计每个数字出现次数，遍历统计出现1次和出现次数≥3次的数字个数，根据这两个统计结果判断是否有解并构造输出方案。

### 最优关键思路或技巧
对数字出现次数进行分类讨论，利用出现1次、出现2次、出现次数≥3次的数字对两个集合好数数量影响的不同特性来判断和构造划分方案。这种思维方式简化了问题处理过程，将复杂的划分问题转化为简单的计数和条件判断问题。

### 可拓展之处
同类型题常围绕集合元素的特性及划分条件展开，类似算法套路为对元素按某种特性分类，分析各类元素对目标条件的影响，进而判断和构造解决方案。例如给定集合元素及特定性质，要求划分集合使两集合某性质的元素数量满足特定关系。

### 推荐洛谷题目
 - [P1131 海战](https://www.luogu.com.cn/problem/P1131)：涉及对二维数组元素的统计和判断，与本题对数字出现次数统计判断有相似之处。
 - [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：通过对数字组合的判断来满足特定条件，和本题对不同类型数字组合判断是否满足划分条件思路类似。
 - [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：对区域内元素特性进行分析，和本题分析集合内元素特性有相似思维方式。

### 个人心得
无。 

---
处理用时：64.88秒