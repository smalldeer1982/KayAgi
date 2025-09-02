# [USACO22JAN] Herdle B

## 题目描述

奶牛们发明了一种名为 Herdle 的新型解谜游戏，在牛界引起了轰动。

每天都会有一个新谜题发布供奶牛解决。游戏采用 $3\times 3$ 方阵的形式表示农场的一块田地，田地的每个方格都由特定品种的奶牛占据。总共只有 $26$ 种可能的品种，每一种由 $\text{A}$ 到 $\text{Z}$ 中的不同大写字母标识。玩家不会被告知田地中的奶牛品种排列方式——游戏目标是通过一系列猜测确定它们。

每次猜测，奶牛们输入一个 $3\times 3$ 的大写字母方阵，表示该田地可以用奶牛填充的可能方式。猜测的某些方格可能是正确的。这些方格以绿色高亮显示，让奶牛们知道这些是正确的。猜测的另一些方格可能填入了品种正确但位置错误的奶牛。这些以黄色高亮显示。

黄色高亮显示的方格的数量可以帮助指示某个品种的奶牛数量。 例如，假设猜测方阵包含 $4$ 头品种 $\text{A}$ 的奶牛，而答案方阵包含 $2$ 只品种 $\text{A}$ 的奶牛，其中没有正确位置上的 $\text{A}$ （即，它们都不应该是绿色的）。 在这种情况下，猜测方阵中只有两个 $\text{A}$ 应以黄色高亮显示。 更准确地说，如果猜测方阵中有 $x$ 个特定品种的奶牛，并且 答案方阵中有 $y \le x$ 头该品种奶牛（不包括位置正确而得到绿色高亮显示的奶牛），那么猜测方阵的 $x$ 头奶牛中只有 $y$ 头奶牛应该以黄色高亮显示。

给定正确答案的方阵和一个表示对该答案的猜测的方阵，请计算绿色和黄色高亮显示的方格的数量。

## 说明/提示

【样例解释 1】

在这个例子中，最后一行中间的 O 是正确的，所以这个方格以绿色高亮显示。字母 W 位于错误的位置，所以它以黄色高亮显示。

【样例解释 2】

在这里，其中一个 A 位于正确的位置，所以它以绿色高亮显示。余下的 A 均不在正确位置上，由于答案方阵中有两个 A，所以有两个 A 应当以黄色高亮显示。



## 样例 #1

### 输入

```
COW
SAY
MOO
WIN
THE
IOI```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
AAA
BBB
CCC
AYY
AAA
ZZZ```

### 输出

```
1
2```

# 题解

## 作者：SunSkydp (赞：18)

[可能会有更好的阅读体验](https://www.cnblogs.com/sunskydp/p/solution-p8090.html)

首先，我们得理解题意。

给定两个 $3 \times 3$ 的矩阵，分别是正确答案矩阵和奶牛猜的矩阵。绿色高亮显示位置和品种都正确的奶牛，黄色高亮显示品种正确但位置错误的奶牛，求绿色高亮数量和黄色高亮数量。

位置和品种都正确的奶牛直接判断累计相加就行了，把正确的奶牛**排除**后，我们可以设置两个计数器数组，分别表示正确答案矩阵和奶牛猜想矩阵中每个品种奶牛的数目（排除正确的奶牛）。

对于每一品种奶牛，题目中说：

> 如果猜测方阵中有 $x$ 个特定品种的奶牛，并且 答案方阵中有 $y \le x$ 头该品种奶牛（不包括位置正确而得到绿色高亮显示的奶牛），那么猜测方阵的 $x$ 头奶牛中只有 $y$ 头奶牛应该以黄色高亮显示。

所以我们只要取正确答案矩阵和奶牛猜想矩阵中每个品种奶牛排除正确奶牛后的数目的最小值即可。

如果还有不懂得话，可以尝试从下面的代码中理解，但是要杜绝抄袭，洛谷非常重视**学术诚信**。此类行为将会导致您成为**作弊者**。 具体细则请查看[洛谷社区规则](https://www.luogu.com.cn/blog/luogu/social-rules)。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[4][4], b[4][4];
int green, yellow, rall[27], gall[27];
int main() {
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 3; j++)
			cin >> a[i][j];
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 3; j++)
			cin >> b[i][j];
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 3; j++)
			if(a[i][j] == b[i][j]) green++;
			else {
				rall[a[i][j] - 'A' + 1]++;
				gall[b[i][j] - 'A' + 1]++;
			}
	for(int i = 1; i <= 26; i++) yellow += min(rall[i], gall[i]);
	printf("%d\n%d\n", green, yellow);
	return 0;
}
```

---

## 作者：Miracle_ZX (赞：8)

### Part 0 

[原题传送门](https://www.luogu.com.cn/problem/P8090)

希望能够过申，谢谢～

### Part 1 题意

原题会给出两个 $3 \times 3$ 的方阵，第一个是奶牛猜测的，第二个是正确的方阵，要求我们输出绿色和黄色高亮显示的方格的数量。

1. 首先看到原题对绿色高亮的描述：

	> 猜测的某些方格可能是正确的，这些方格以绿色高亮显示。

	所以只需输出两个方阵中对应位置相符的数量即可。

2. 我们再看到题目对黄色高亮的描述：

	> 另一些方格可能填入了品种正确但位置错误的奶牛，这些以黄色高亮显示。

	所以黄色高亮就是这个字母在两个方阵中都出现了，但是没有做到对应位置相符的数量
    
### Part 2 解题

我的模拟思路可能较为清奇，是这样的：

$ a $ 和 $ b $ 两个数组用来记录 $ mp1 $ 和 $ mp2 $ 中 $ A $ 到 $ Z $ 字母的个数，同时用 $ c $ 数组记录绿色高亮的是什么字母，有多少个。最终按字母序扫一遍三个数组，用这个字母在两个方阵中都出现了的个数，即 ```min(a[i], b[i])``` 减去做到对应位置相符的数量，即 ```c[i]```。

话不多说，上代码。

### Part 3 代码


```cpp
/*
作者: mzx
题目: USACO, Jan., Bronze, T1 Herdle
算法: 
日期: 2022.1.29
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <fstream>
using namespace std;

int a[27], b[27], c[27];
char mp1[4][4], mp2[4][4];
int ans1, ans2;

inline int read()
{
    int s = 0, f = 0;
    char ch = ' ';
    while(!isdigit(ch))
    {
        f |= (ch == '-');
        ch = getchar();
    }
    while(isdigit(ch))
    {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        ch = getchar();
    }
    return (f) ? (-s) : (s);
}

int main()
{
    ofstream fout("Herdle.out");
    ifstream fin("Herdle.in");
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            cin >> mp1[i][j];
            a[mp1[i][j] - 'A' + 1]++;
        }
    }
    for(int i = 1; i <= 3; i ++)
    {
        for(int j = 1; j <= 3; j++)
        {
            cin >> mp2[i][j];
            b[mp2[i][j] - 'A' + 1]++;
        }
    }//以上是读入与记录部分
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            if(mp1[i][j] == mp2[i][j])
            {
                ans1++;//绿色高亮记录
                c[mp1[i][j] - 'A' + 1]++;//每一个字母分别记了多少次绿色高亮
            }
        }
    }
    for(int i = 1; i <= 26; i++)
    {
        if(a[i] != 0 && b[i] != 0)
        {
            ans2 += min(a[i], b[i]) - c[i];//字母出现的个数减去这个字母被记绿色高亮的次数
        }
    }
    cout << ans1 << endl << ans2 << endl;
    return 0;
}

```

### Part 4 结果

[O2, 40ms](https://www.luogu.com.cn/record/68586082)

---

## 作者：柳下惠 (赞：4)

[题目链接](https://www.luogu.com.cn/problem/P8090)。

### 题意概要

给你两个 $3×3$ 的字符矩阵，让你求出在给出矩阵中并且位置与目标矩阵相对应的字符数量以及出现在给出矩阵中但位置与目标矩阵不对应的字符数量。

### 思路

开两个 `map` 数组，其中一个数组计录目标矩阵中各个字符出现的次数，另一个数组作为条件来判断是否累加答案。

具体的内容在代码里给出了，放一下比赛时写的代码吧。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>ma;//计录各个字符在目标矩阵中出现的次数
map<int,int>mp;
int num=0,gre=0;
char s1[6][6],s2[6][6];
int main()
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>s1[i][j],ma[s1[i][j]-'0']++;//每个字符出现了几次
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			cin>>s2[i][j];
			if(mp[s2[i][j]-'0']<ma[s2[i][j]-'0']&&ma[s2[i][j]-'0'])
				num++,mp[s2[i][j]-'0']++;
		}
   //num是累加ma数组中有多少个字符出现在了给出矩阵中
   //如果在给出矩阵中字符的数量超过了目标矩阵中对应字符的数量显然不计进总数
   //要累加总数，该字符也必须在ma数组中出现过
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			if(s1[i][j]==s2[i][j])
				gre++;
   //循环判断两个位置上的字符是否相等
	printf("%d\n%d",gre,num-gre);
	return 0;
	
}

```

---

## 作者：Coros_Trusds (赞：3)

# 题目大意

给定两个 $3\times 3$ 的字符串矩阵，求出相同位置字符相同的位置个数和存在相同字母但是位置不对应的字母个数。

# 题目分析

第一问好办，只需要比较一下就行了。

输入第一个矩阵时，我们将这个矩阵内所有字符都放到一个桶内计算出现个数。

输入第二个矩阵时，我们将这个矩阵内所有“相同位置字符相同的位置”上的字符在桶中的出现次数减 $1$，这是为了方便后面第二小问的计算。随后对于第二个矩阵的其他位置，统计桶内的元素个数即可。

# 代码

```cpp
//2022/2/6

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>//need "memset"

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=5;

int tong[ma];

bool vis[ma][ma];

char a[ma][ma],b[ma][ma];

int G,Y;

int main(void)
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif

	for(register int i=1;i<=3;i++)
	{
		scanf("%s",a[i]+1);
	}

	for(register int i=1;i<=3;i++)
	{
		for(register int j=1;j<=3;j++)
		{
			tong[a[i][j]-'A'+1]++;
		}
	}

	for(register int i=1;i<=3;i++)
	{
		scanf("%s",b[i]+1);
	}

	for(register int i=1;i<=3;i++)
	{
		for(register int j=1;j<=3;j++)
		{
			if(a[i][j]==b[i][j])
			{
				vis[i][j]=true;

				G++;

				tong[a[i][j]-'A'+1]--;
			}
		}
	}

	for(register int i=1;i<=3;i++)
	{
		for(register int j=1;j<=3;j++)
		{
			if(tong[b[i][j]-'A'+1]>=1 && vis[i][j]==false)
			{
				Y++;

				tong[b[i][j]-'A'+1]--;
			}
		}
	}

	printf("%d\n%d\n",G,Y);

	return 0;
}
```

---

## 作者：lsj2009 (赞：3)

[更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/solution-p8090)
## 题目大意
给定两个 $3\times3$ 的有且仅有大写字母的矩阵 $A$ 与 $B$，问****有多少个 $A_{i,j}=B_{i,j}$****，又****有多少个 $A_{i,j}\neq B_{i,j}$ 但在 $B$ 矩阵出现过****。

~~第一次看见这么烦的 USACO。~~
## 思路
第一种很好计算：****直接枚举 $i,j$ 看看有多少个 $A_{i,j}=B_{i,j}$ 就行了。****

接下来考虑第二种情况:有多少个 $A_{i,j}\neq B_{i,j}$ 但在 $B$ 矩阵出现过。


****有两种方法。****

- 首先枚举枚举 $i,j$，如果 $A_{i,j}=B_{i,j}$ 就直接跳过，否则在 $B$ 中寻找是否有一个 $B_{k,l}=A_{i,j}$。注意在寻找时需要注意很多细节：首先需要判断 ****$B_{k,l}$ 是否等于 $A_{k,l}$****
,如等于，那么这个 $B_{k,l}$ 并不是贡献给第二种而是贡献给第一种 $A_{i,j}=B_{k,l}$ 的；其次，****找到就退出****，一个 $A_{i,j}$ 只能贡献一次，如果有多个 $B_{k,l}$ 我们应只选择一个，同时可以证明：如果 $B_{k,l}\neq A_{k,l}$ 那么选择每一个 $B_{k,l}$ 都是****一样的****；最后，****找到一个 $B_{k,l}$ 则该 $B_{k,l}$ 就不能再使用****，原因同上：一个 $B_{k,l}$ 只能贡献一遍。

以上就是我们需要注意的事项。code 如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[3][3],b[3][3];
int n=3,ans1,ans2; //3*3 的矩阵
int main() {
	for(int i=0;i<n;i++) //输入 A 矩阵
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	for(int i=0;i<n;i++) //输入 B 矩阵
		for(int j=0;j<n;j++)
			cin>>b[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(a[i][j]==b[i][j]) //第一种情况
				++ans1;
			else {
				bool flag=false; //如果 flag=true 说明已经找到一个 B[k][l]，需退出
				for(int k=0;k<n&&!flag;k++) //flag=true 退出循环
					for(int l=0;l<n&&!flag;l++) //flag=true 退出循环
						if(a[i][j]==b[k][l]&&a[k][l]!=b[k][l]) //找到 b[k][l]，判断 b[k][l] 是否等于 a[k][l]
							++ans2,b[k][l]=' ',flag=true; //找到 b[k][l]，flag=true,将 b[k][l] 标为空格，不能使用
			}
	printf("%d\n%d",ans1,ans2);
	return 1;
}
```
上述程序时间复杂度为 $O(n^4)$。

- 第二种方法。我们分别统计 $26$ 个大写字母在 $A_{i,j}\neq B_{i,j}$ 的情况下的在 $A$ 矩阵与 $B$ 矩阵的出现次数，分别记为 $cnt_{0,c}$ 和 $cnt_{1,c}$，则最后的答案就是 $\min(cnt_{0,c},cnt{1,c})$ 之和。

证明：如果 $cnt_{0,c}>cnt_{1,c}$ 说明奶牛并没有猜完 $A$ 矩阵的 $c$ 字符，在 $A$ 矩阵出现而位置不对的 $c$，字符即他们猜的 $c$ 字符个数；如果 $cnt_{0,c}>cnt_{1,c}$ 说明奶牛猜的 $c$ 字符数过多，在 $A$ 矩阵出现过多至多只有在 $A$ 矩阵的 $c$ 字符个数。

证毕。

code 如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[3][3],b[3][3];
int n=3,cnt[2][26],ans1,ans2;
int main() {
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>b[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(a[i][j]==b[i][j])
				++ans1;
			else
				++cnt[0][a[i][j]-'A'],++cnt[1][b[i][j]-'A'];
	for(int i=0;i<26;i++)
		ans2+=min(cnt[0][i],cnt[1][i]);
	printf("%d\n%d",ans1,ans2);
	return 1;
}
```
该算法复杂度仅为 $O(n^2)$~~，但由于 $n=3$，所以使用两个算法没什么区别。~~

---

## 作者：HYdroKomide (赞：3)

### 题意：
给你两个 $3\times3$ 的大写字母矩阵，在对应位置的相同字符显示绿色。**除了绿色字符以外**还有相同的字符显示黄色，问一共有多少绿色、多少黄色。

### 思路：
~~口胡一种考场上脑抽了想出的麻烦方法。~~

小数据范围，直接暴力枚举。

考虑到绿色字符优先，就先来计算绿色字符个数。

如果这个字符是绿色的，直接将其排除，并将绿色字符个数 $+1$。

否则，用 `map` 开一个桶，将这个字符装入桶里。

最后挨个排查剩余的字符即可。

逐个操作的解释详见注释。

### 程序如下：
```cpp
#include<cstdio>
#include<map>
using namespace std;
char a[10],b[10],ans1,ans2;
map<char,int>am,bm;//开一个桶
int main(){
	scanf("%s",a+1);
	scanf("%s",a+4);
	scanf("%s",a+7);
	scanf("%s",b+1);
	scanf("%s",b+4);
	scanf("%s",b+7);//麻烦的输入方法
	for(int i=1;i<=9;i++){
		if(a[i]==b[i])ans1++;//是绿色的情况，绿色+1
		else{//否则
			am[a[i]]++;//加入桶里
			bm[b[i]]++;
		}
	}
	for(int i=1;i<=9;i++){
		ans2+=min(am[a[i]],bm[a[i]]);//该字符在两个矩阵中出现的次数最小值就是要增加的黄色个数
		am[a[i]]=bm[a[i]]=0;//将此字符排除
	}
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}
```

### THE END

---

## 作者：CRH2C (赞：2)

[官方题解](http://usaco.org/current/data/sol_prob1_bronze_jan22.html)

## 题意

给你两个 $3 \times 3$ 的大写字母方阵分别为正确答案和猜测结果。

请你求出猜测结果和正确答案字母和位置都一样的个数 和 猜测结果和正确答案字母一样但位置不一样的个数。

## 思路

1. 分别统计两个方阵各个字母的个数。

2. 对于 猜测结果和正确答案字母和位置都一样的个数，直接比对。

3. 对于 猜测结果和正确答案字母一样但位置不一样的个数，为 猜测中该字母的个数 $-$  猜测结果和正确答案字母和位置都一样的个数 与 $\max($正确答案中该字母的个数 $-$ 猜测结果和正确答案字母和位置都一样的个数$,0)$ 的较小值。

## 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
char ac[10][10],wa[10][10];int gsac[30],gswa[30],g[30],y[30];
void input(){
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>ac[i][j];
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>wa[i][j];
}
void tj(){
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++){
			gsac[ac[i][j]-'A'+1]++;
			gswa[wa[i][j]-'A'+1]++;
		}	
}
void green(){
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			if(ac[i][j]==wa[i][j]){
				g[ac[i][j]-'A'+1]++;
				g[0]++;
			}
}
void yellow(){
	for(int i=1;i<=26;i++)
		y[0]+=min(gswa[i]-g[i],max(gsac[i]-g[i],0));
}
void print(){
	cout<<g[0]<<"\n"<<y[0];
}
int main(){
	input();//输入
	tj();//分别统计两个方阵各个字母的个数
	green();//处理 猜测结果和正确答案字母和位置都一样的个数
	yellow();//处理 猜测结果和正确答案字母一样但位置不一样的个数
	print();//输出
	return 0;
}
```

---

## 作者：RootMirzayanov (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8090)

## 题意

给定两个 $3\times 3$ 的由大写字母构成的字符方阵，第一个方阵为正确答案，第二个方阵为猜测结果。

您需要求出字母和位置都完全对应的字母个数和存在相同字母但是位置不对应的字母个数。

## 解析

我们可以在边输入边将字符数预处理。因为在正确答案的方阵中找到了满足第一问条件的字符是不会再次参与第二问的计算的，而剩余未参与第一问计算的在正确答案方阵的字符都会参与第二问的计算，所以我们在每一问的计算处理过程中都将对应的字符的非零预处理数 $-1$, 如果为 $0$ 则说明该字符在所有正确答案的位置已对应完或不存在，不应参与该问的计算。

所以按照这个思路我们可以首先遍历一遍猜测方阵得到第一问的结果。但是如果我们再遍历一遍猜测方阵去得到第二问的结果会将已参与第一问答案计算的字符再次计算一遍，所以我们可以另外创建一个 `bool` 类型二维数组用于记录同样位置的猜测字符是否已经参与第一问的处理。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[10][10], tmp[10][10];
int c[30], ans; 
bool f[10][10];
int main(){
    for(int i = 1;i <= 3;i++){
        scanf("%s", a[i] + 1);
        for(int j = 1;j <= 3;j++){
            c[a[i][j] - 'A' + 1]++;
        }
    }
    for(int i = 1;i <= 3;i++){
        scanf("%s", tmp[i] + 1);
        for(int j = 1;j <= 3;j++){
            if(tmp[i][j] == a[i][j]){
                ans++;
                c[tmp[i][j] - 'A' + 1]--;
                f[i][j] = 1;
            }
        }
    }	
    printf("%d\n", ans);
    ans = 0;
    for(int i = 1;i <= 3;i++){
        for(int j = 1;j <= 3;j++){
            if(c[tmp[i][j] - 'A' + 1] > 0 && f[i][j] == 0){
                ans++;
                c[tmp[i][j] - 'A' + 1]--;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：Jerrlee✅ (赞：1)

## 题意
给出两个 $3 \times 3$ 的正方形字母矩阵，第一行输出上下两个字母一样的个数，第二行输出第一行与之字符一样但是**错位**了的字符数量。

更详细的说，对于样例二，有一个 `A` 在正确的位置上，统计第二行输出内容时就不能包括它！
## 思路
读入时就统计好每个字符出现的次数，再开**两个**循环，第一个判断第二个矩阵与第一个矩阵的某个字符是否相等，相等就把那个字符的出现次数减一，第二个判断如果第二个矩阵与第一个矩阵的某个字符不相等，且第二个矩阵的那个字符统计出现个数的值大于一，第二个答案加一。

不理解的，具体看程序。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[5][5],s[5][5];
int ans,cnt,a[114514];//ans 为第一行答案，cnt 为第二行答案，a 用来统计字符的出现次数
int main(){
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            cin>>c[i][j];
            a[c[i][j]]++;
        }
    }
    for(int i=1;i<=3;i++){//一定要分两个循环！先把 a 数组的统计处理好再在第二个循环中看是否大于 0
        for(int j=1;j<=3;j++){
            cin>>s[i][j];
            if(s[i][j]==c[i][j]) ans++,a[s[i][j]]--;
        }
    }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            if(s[i][j]!=c[i][j]&&a[s[i][j]]>0) cnt++,a[s[i][j]]--;
        }
    }
    cout<<ans<<endl<<cnt;
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/68525996)

---

## 作者：untrigintillion (赞：1)

### 思路：

1. 显然，6 行 3 列的 18 个字符，只需要用两个字符串就可以实现。

1. 先比较涂绿的，直接扫一遍即可，但是需要把相同的改成 `'Z'+1` ，使其无法被下面涂黄的扫描到（即去除位置相同的）

1. 再比较涂黄的，建一个数组 `cnt[2][27]` 去存放剩下每种字母的出现次数，注意到 `min(cnt[0][i],cnt[1][i])` 就是这种字母的重复出现次数。

### 代码：

```cpp
//AC #1...11
#include <bits/stdc++.h>
using namespace std;
int main(){
	char a[9],b[9];
	int cnt[2][27]={0};
	int G=0,Y=0;
	for(int i=0;i<9;i++)cin>>a[i];
	for(int i=0;i<9;i++)cin>>b[i];
	for(int i=0;i<9;i++)if(a[i]==b[i])G++,a[i]=b[i]='Z'+1;
	for(int i=0;i<9;i++)cnt[0][a[i]-'A']++;
	for(int i=0;i<9;i++)cnt[1][b[i]-'A']++;
	for(int i=0;i<26;i++)Y+=min(cnt[0][i],cnt[1][i]);
	cout<<G<<endl<<Y;
	return 0;
}
```

这是本蒟蒻写的第 `3` 篇题解

---

## 作者：yeshubo_qwq (赞：1)

## 题意
给定两个 $3\times3$ 的字符矩阵，以第一个字符矩阵为标准，问：**位置和字母都相同**的字母和**位置不同、字母相同的字母**的数量。
## 思路
简单的模拟，但有几处细节。

第一步：统计第一个字符矩阵中字母的数量。

第二步：统计**位置和字母都相同**的字母的数量，并减去对应字母的数量，第二个矩阵中对应位置上的字母修改，防止第三步重复统计。

第三步：统计**位置不同、字母相同的字母**的数量，同时减去字母数量。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,ans1,ans2,m[30];
char a[6][6],b[6][6];
int main(){
	for(i=1;i<=3;i++){//第一步
		scanf("%s",a[i]+1);
		for(j=1;j<=3;j++)
			m[a[i][j]-'A']++;
	}
	for(i=1;i<=3;i++){//第二步
		scanf("%s",b[i]+1);
		for(j=1;j<=3;j++)
			if(a[i][j]==b[i][j])
			    ans1++,m[b[i][j]-'A']--,b[i][j]='#';
			                       //这里将字母修改为#
	}
	for(i=1;i<=3;i++)//第三步
		for(j=1;j<=3;j++)
		    //特判不是#
			if(b[i][j]!='#'&&m[b[i][j]-'A']-->=1)ans2++;
	return printf("%d\n%d",ans1,ans2),0;
}
```


---

## 作者：skyskyCCC (赞：1)

**前言。**

一道字符练习题与模拟题。

**分析。**

~~本题我只想出了两种方法。~~

**思路一：**

先输入 $18$ 个字符,如果字母一样且位置一样， $ans$ 就加 $1$ ，再将这两个位置标记一下，就统计出了第一个答案。

然后，再循环两个字母表，如果**未被标记，位置不同，字母一样**的情况下（见代码顺序）， $sum$ 加 $1$ ，并将两个位置标记一下，第二个答案就也新鲜出炉了。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
char a[8][8],b[8][8];
bool pda[8][8],pdb[8][8];
int ans,sum;
int main(){
    ios::sync_with_stdio(false);
    for (int i=1;i<=3;i++){
    	for (int j=1;j<=3;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            cin>>b[i][j];
            if(b[i][j]==a[i][j]){ 
                ans++;
                pda[i][j]=1;
                pdb[i][j]=1;
            }
        }
    }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            for(int k=1;k<=3;k++){
                for(int z=1;z<=3;z++){
                    if(!pda[i][j]&&!pdb[k][z]&&(i!=k||j!=z)&&(a[i][j]==b[k][z])){
                    	sum++;
                        pda[i][j]=1;
                        pdb[k][z]=1;
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    cout<<sum<<endl;
    return 0;
}//by zzy

```

提交上去，效率还是挺高的，但这样循环的太多，代码容易写错，那么，我们就来研究一下如何让代码优化一下。

**思路二：**

~~我也不知道我为什么要这么做。~~

输入第一个字符表，把它们一个个扔进桶里，再输入第二个字符表，循环两个字符表，如果字母一样且位置一样，就将 $ans$ 加 $1$ ，再将第二个字符表中被统计的字符扔出桶，**避免重复判断**。

再次循环，如果第二个字符表中的字符未被统计且位置不同， $sum$ 就加 $1$ ，再将统计的字符扔出桶。

最后，输出答案即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
char a[8][8],b[8][8];
int pd[8],pd2[8];
int ans,sum;
int main(){
    ios::sync_with_stdio(false);
    for (int i=1;i<=3;i++){
        for (int j=1;j<=3;j++){
            cin>>a[i][j];
            pd[a[i][j]]++;
        }
    }
    for (int i=1;i<=3;i++){
        for (int j=1;j<=3;j++){
            cin>>b[i][j];
        }
    }
    for (int i=1;i<=3;i++){
        for (int j=1;j<=3;j++){
            if (a[i][j]==b[i][j]){
                ans++;
                pd[b[i][j]]--;
            }
        }
    }
    for (int i=1;i<=3;i++){
        for (int j=1;j<=3;j++){
            if (pd[b[i][j]]&&b[i][j]!=a[i][j]){
                sum++;
                pd[b[i][j]]--;
            }
        }
    }
    cout<<ans<<endl;
    cout<<sum<<endl;
    return 0;
}//by zzy
```
是不是简洁了许多？只有每次两个循环。

不过，不知道为什么，两个代码运行时间相同，但是，占用内存还是思路二好一点。

**后记。**

注意判断的写法。

大家如有疑问，请在评论区提出，我会尽力解答的。

---

## 作者：3a51_ (赞：0)

### 题目大意

给定 $2$ 个 $3\times3$ 的方阵，求完全正确和字母正确位置错误的个数。

### 思路分析

首先完全正确很简单，扫一遍一一比对即可。

接下来字母正确的情况，开一个```vis```数组记录是否为完全正确或者已经算过。不难发现只要两个位置不一样并且两数的```vis```都不为 $0$ 即代表字母正确位置错误。如果这里理解起来困难可以看一下代码。

### code

```cpp
#include<iostream>
using namespace std;
char c1[4][4],c2[4][4];//c1记录正确的，c2记录猜测的
int g,y,vis1[4][4],vis2[4][4]; //vis1标记完全正确的个数，vis2标记在情况2已经被算过的。
int main()
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>c1[i][j];
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			cin>>c2[i][j];
			if(c2[i][j]==c1[i][j])
			{ 
				g++;
				vis1[i][j]=1;
				vis2[i][j]=1;
			}//直接判断是否完全正确，如果完全正确，g(green)就加一
		}
	for(int i1=1;i1<=3;i1++)
		for(int j1=1;j1<=3;j1++)
			for(int i2=1;i2<=3;i2++)
				for(int j2=1;j2<=3;j2++)
				{
					if(!vis1[i1][j1] && !vis2[i2][j2] && (i1!=i2 || j1!=j2) && (c1[i1][j1]==c2[i2][j2]))//没被标记并且位置不同
					{
						y++;//计数器y(yellow)加一
						vis1[i1][j1]=1;
						vis2[i2][j2]=1;//标记
					}
				}
	cout<<g<<endl<<y;
	return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
模拟题。$green$ 记录绿色格子有多少个，$yellow$ 记录黄色格子有多少个。

+ 首先我们统计绿色格子：将正确答案的方阵和一个表示对该答案的猜测的方阵的每个格子进行对比，如果两个方阵上那个格子都相等，那就 $green \gets green + 1$，并且做上标记，以免下次找黄色格子时找重复了。

+ 然后统计黄色格子：从猜测方阵逐个取出每一个格子并且在两个方阵上该格子不相等时，将一猜测方阵该格子去和正确方阵的每一个格子比较，如果某 $1$ 个正确方阵上的格子没被标记并且等于猜测方阵该格子那就 $yellow \gets yellow + 1$，并且做上标记，以免下次找黄色格子时找重复了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[4][4], b[4][4];
bool vis[4][4];
int green, yellow;
void check(char ch) {
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      if (!vis[i][j] && a[i][j] == ch) {  //发现位置错误。
        yellow++;
        vis[i][j] = 1;
        return;
      }
    }
  }
  return;
}
int main() {
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      cin >> b[i][j];
    }
  }

  for (int i = 1; i <= 3; i++) {  //先找绿色后找黄色就是方式先后顺序冲突或重复  。
    for (int j = 1; j <= 3; j++) {
      if (a[i][j] == b[i][j]) {  //相同，猜对了。
        green++;
        vis[i][j] = 1;
      }
    }
  }

  for (int i = 1; i <= 3; i++) {  //先找绿色后找黄色就是方式先后顺序冲突或重复  。
    for (int j = 1; j <= 3; j++) {
      if (a[i][j] != b[i][j]) {  //接着查找有没有位置错误的。
        check(b[i][j]);
      }
    }
  }
  cout << green << "\n"
       << yellow;
  return 0;
}
```

---

## 作者：pengzy___ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8090)

这是一道很水的入门模拟题。

### 题意：

给你两个 $ 3*3 $  的方阵，要求你告诉他两个方阵中有多少个大写字母是相同且位置相同的，又有多少个只是长得一样。

### 分析：

只需要用两个字符二维数组来储存两个方阵，并一一判断。

要用两个桶来记录两个方阵的二十六个大写字母分别有多少个，最后用答案循环累计较小值。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int s1[30],s2[30],ans1=0,ans2=0;//桶和答案
char a[5][5],b[5][5];//数组开大一点
int main()
{
	for(int i=1;i<=3;i++)//输入
	    for(int j=1;j<=3;j++)
	        cin>>a[i][j];
	for(int i=1;i<=3;i++)
	    for(int j=1;j<=3;j++)
	        cin>>b[i][j];
	for(int i=1;i<=3;i++)
	    for(int j=1;j<=3;j++)
	        if(a[i][j]==b[i][j])ans1++;
	        else 
			{
			    s1[(int)a[i][j]-64]++;//用ascii码转换位置
			    s2[(int)b[i][j]-64]++;
			}
	for(int i=1;i<=26;i++)
	    ans2+=min(s1[i],s2[i]);//累计较小值
	cout<<ans1<<endl<<ans2;
	return 0;
}
```


---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题主要难点在于读题。

方法：

1. 用 `ans` 和 `g` 两个数组存放两个 $3 \times 3$ 的格子。

1. 遍历两个棋盘，用 `anst` 和 `gt` 两个数组存放 `ans` 和 `g` 两个棋盘中每一个字母出现的次数。用 `st` 数组存放每种字母正确的次数。

1. 将 `st` 累加得到绿色格子。

1. 遍历 `anst` 和 `gt` 两个数组从 $1$ 到 $26$，每一次黄色加上 $\operatorname{min}(anst_{i},gt_{i})-st_{i}$ 即可。

## AC CODE:

```cpp
/*
ID:yinhy09
LANG:C++
TASK:herdle
*/
#include<bits/stdc++.h>
using namespace std;
char g[10][10],ans[10][10];
int anst[30],gt[30],st[30];
int main(){
	int green=0,yellow=0;
	memset(anst,0,sizeof(anst));
	memset(gt,0,sizeof(gt));
	memset(st,0,sizeof(st));
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++) 
		{
			cin>>ans[i][j];
			anst[ans[i][j]-64]++;
		}
	}
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++) 
		{
			cin>>g[i][j];
			gt[g[i][j]-64]++;
			if(g[i][j]==ans[i][j])
			{
				green++;
				st[ans[i][j]-64]++;
			}
		}
	}
	for(int i=1;i<=26;i++)
	{
		yellow+=min(anst[i],gt[i])-st[i];
	//	cout<<char(i+64)<<": "<<gt[i]<<" "<<anst[i]<<" "<<st[i]<<endl;
	}
	cout<<green<<endl<<yellow;
	return 0;
}
```

谢谢观看~

---

## 作者：tZEROちゃん (赞：0)

先看绿色高亮的部分。

用两个 for 循环判断相同位置是否相同即可。


```cpp
int Green = 0;
rep (i, 1, 3) rep (j, 1, 3) Green += trueAnswer[i][j] == guessAnswer[i][j];
printf("%d\n", Green);
```

再看黄色高亮部分。

开两个数组 $nt$ 和 $ng$，分别表示第一个矩阵中对应元素出现的个数，比如说对于

```plain
COW
SAY
MOO
```

那么 `nt['O'] = 3, nt['Y'] = 1`，以此类推。

$ng$ 同理。

然后从 `'A'` 到 `'Z'` 遍历 $nt,\ ng$ 数组，计数器加上 $\min(nt_i, ng_i)$。

一些细节见代码。

```cpp
int Yellow = 0;
rep (i, 1, 3) rep (j, 1, 3) numtrue[trueAnswer[i][j]]++, numguess[guessAnswer[i][j]]++;
rep (c, 'A', 'Z') Yellow += min(numguess[c], numtrue[c]);
printf("%d\n", Yellow - Green); // 这里要减去绿色的数量，原因显然
```

---

## 作者：pengzy___ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8090)

这是一道入门模拟题。

### 题意：
给你两个二维的边长为 3 的方阵，要求你告诉他两个方阵中有多少个大写字母是相同的，又有多少个长相相同且位置相同。

## 分析：
只需要用两个字符二维数组来储存两个方阵，并一一判断。

要用两个桶来记录两个方阵的二十六个大写字母分别有多少个，最后用答案循环累计较小值。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int s1[30],s2[30],ans1=0,ans2=0;//桶和答案
char a[5][5],b[5][5];//数组开大一点
int main()
{
    for(int i=1;i<=3;i++)//输入
        for(int j=1;j<=3;j++)
            cin>>a[i][j];
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            cin>>b[i][j];
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            if(a[i][j]==b[i][j])ans1++;
            else 
            {
                s1[(int)a[i][j]-64]++;//用ascii码转换位置
                s2[(int)b[i][j]-64]++;
            }
    for(int i=1;i<=26;i++)
        ans2+=min(s1[i],s2[i]);//累计较小值
    cout<<ans1<<endl<<ans2;
    return 0;
}
```


---

## 作者：mcDinic (赞：0)

大暴力一道，真的是怎么玩都行。

我是先把第一个答案求出，再用一个映射存正确答案矩阵各元素出现次数，对于第一个答案中涉及到的，再减去，剩下的话匹配第二个矩阵，累加第二个答案即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[5][5],b[5][5]; 
int ans1,ans2,c[5][5];
map<char,int>mp1;
signed main(){
	mp1.clear();
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>a[i][j],mp1[a[i][j]]++;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>b[i][j];
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			if(a[i][j]==b[i][j])c[i][j]=1,ans1++,mp1[a[i][j]]--;
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			if(mp1[b[i][j]]&&!c[i][j])ans2++,mp1[b[i][j]]--;
		}
	}
	cout<<ans1<<endl<<ans2;
	return 0;
}
```


---

## 作者：happybob (赞：0)

传送门：[P8090 [USACO22JAN] Herdle B](https://www.luogu.com.cn/problem/P8090)。

考虑模拟，记录下答案方阵中每种字符出现次数，然后按照题意模拟。注意要先判断绿色个数再判断黄色个数，绿色优先级更高。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

const int N = 5;

char guess[N][N], ans[N][N];

map<char, int> as, gs;

int main()
{
	int green = 0, yellow = 0;
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			cin >> ans[i][j];
			as[ans[i][j]]++;
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			cin >> guess[i][j];
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			if (guess[i][j] == ans[i][j])
			{
				green++; 
				as[guess[i][j]]--;
			}
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			if (as[guess[i][j]] && guess[i][j] != ans[i][j])
			{
				yellow++;
				as[guess[i][j]]--;
			}
		}
	}
	printf("%d\n%d\n", green, yellow);
	return 0;
}	
```


---

## 作者：yukimianyan (赞：0)

暴力模拟。

先确定所有绿色高亮的方块，丢掉。

对于「猜测答案」剩下的字母，开个桶记每个字母出现次数。再在「正确答案」里找，分类讨论：
- 如果桶里有这个字母：
	- 如果这个方块应被绿色高亮：不可能，绿色高亮的已经丢了；
    - 如果这个方块应被黄色高亮：一定是，记录答案，这个字母出现次数减一；
- 如果桶里没有这个字母：
	- 如果这个方块应被黄色高亮：不可能，所有与这个字母相同的都已经找到方块黄色高亮了，这个方块不需要黄色高亮；
    - 如果这个方块不应被高亮：一定是。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n=3,t[256],ans[2];
char a[10][10],b[10][10];
int main(){
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++) scanf("%s",b[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==b[i][j]) ans[0]++,b[i][j]='?';
			else t[a[i][j]]++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(t[b[i][j]]>0) t[b[i][j]]--,ans[1]++;
		}
	}
	printf("%d\n%d\n",ans[0],ans[1]);
	return 0;
}

```


---

