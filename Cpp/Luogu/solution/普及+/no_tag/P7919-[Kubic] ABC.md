# [Kubic] ABC

## 题目背景

建议先看 D 题题目背景。

## 题目描述

给定一个长度为 $n$ 的只包含 $\texttt{A,B,C}$ 的字符串 $S$，你可以进行若干次操作，每次操作为：

- 先选择一个区间 $[l,r]$，你需要保证 $1\le l\le r\le n$。

- 再选择三个字符 $pA,pB,pC\in\{\texttt{A,B,C}\}$，并将 $S_{l\dots r}$ 中所有 $\texttt{A}$ 变为 $pA$，所有 $\texttt{B}$ 变为 $pB$，所有 $\texttt{C}$ 变为 $pC$，**$pA,pB,pC$ 可以相等**。

求出**最少**需要进行多少次操作才能使得 $S$ 中**任意相邻两个字符不同**，并**输出构造方案**。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 5\times 10^3,S_i\in\{\texttt{A,B,C}\}$。

||分值|$n$|特殊性质|
|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$1$|无特殊限制|$\forall i\in[1,n),S_i\neq S_{i+1}$|
|$\operatorname{Subtask}2$|$19$|$\le 10$|无|
|$\operatorname{Subtask}3$|$10$|无特殊限制|$S_i=\texttt{A}$|
|$\operatorname{Subtask}4$|$20$|无特殊限制|$S_i\in\{\texttt{A,B}\}$|
|$\operatorname{Subtask}5$|$20$|$\le 100$|无|
|$\operatorname{Subtask}6$|$30$|无特殊限制|无|

### 评分方法

以下情况将会使你在该测试点获得 $0$ 分：

- 输出格式不满足要求。

- 输出多余信息（包括空格和换行符）

- 构造的方案操作次数与标准答案不同。

- 构造的方案不符合题目要求。

- 时间超限。

如果没有上述情况，你在该测试点获得满分。

**保证 SPJ 占用不超过 $100\operatorname{ms},10\operatorname{MB}$**。

### 样例解释 1

一种操作过程如下：

`ABBAA`

`ABABA`

可以证明没有更优的方案。

### 样例解释 2

初始序列已经符合题目要求，直接输出一行 $0$ 即可。

## 样例 #1

### 输入

```
5
ABBAA```

### 输出

```
1
3 4 BAC```

## 样例 #2

### 输入

```
5
ABCBA```

### 输出

```
0```

# 题解

## 作者：VinstaG173 (赞：16)

简单结论+构造题。

显然若 $x+1<l$，$l \le x<r$ 或 $x \ge r$，则有 $x,x+1$ 位置上的字母相同性在对 $[l,r]$ 任意操作后不变，即原来相同操作后也相同，原来不同操作后也不同。故一次操作 $[l,r]$ 最多只可能让相邻不同对数增加 $2$。故设最初相邻相同对数为 $x$，至少要 $\left\lceil\dfrac{x}{2}\right\rceil$ 次操作才能使得相邻均不相同。

以下给出构造。由以上分析得每次操作 $[l,r]$ 必然在 $l-1,l$ 与 $r,r+1$ 两个相邻位置均由相同变为不同。特别的，若 $x$ 是奇数，则有一次操作只需要对 $[l,n]$ 将 $l-1,l$ 变为不同。这样我们只要找出相邻相同组再任意分组即可。事实上直接取头尾很容易实现。时间复杂度 $O(n)$。

感觉开这个数据范围是 checker 的缘故。

Code:
```cpp
#include<cstdio>
int n,x,y,t;
char s[5003];
int l[5003],r[5003];
int main()
{
	scanf(" %d %s",&n,s+1);x=1,y=n;
	while(x<y)
	{
		while(x<y&&s[x]!=s[x+1])++x;
		while(y>x&&s[y]!=s[y-1])--y;
		if(x==y)break;
		l[++t]=++x,r[t]=--y;
	}
	printf("%d\n",t);
	if(l[t]>r[t])r[t]=n;
	for(int i=1;i<=t;++i)printf("%d %d BCA\n",l[i],r[i]);
	return 0;
}
```

---

## 作者：kkio (赞：4)

### 题面 ###
给一串字符串，每次可以选一个区间，一种改变方式，求最少的步骤，使没有一个相邻字符相同。

### 思路 ###
选定区间 $[l,r]$ ，在 $[l,r]$ 中，不会改变相邻字符的相同情况，只会改变 $S_{l-1},S_l$ 与 $S_r,S_{r+1}$ 的相同情况，这是显而易见的 。

于是只需枚举每个出现相同字符的地方，左右配对即可。
对于可能剩下一个配不上的，单独改其中一个。

对于怎么改，每个不与原来相同即可，$CAB,BCA$ 均可。
### 代码 ###
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char s[5005]; 
vector<pair<int,int> > ans;
int main()
{
	cin>>n;
	int l=1,r=n;
	cin>>s+1;
	while(1)
	{for(;l<r&&s[l]!=s[l+1];l++);for(;l<r&&s[r]!=s[r-1];r--);
		if(l>=r)break;
		int cl=++l,cr=((--r)<l?n:r); 
		ans.push_back(make_pair(cl,cr));
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d %d CAB\n",ans[i].first,ans[i].second); 
}
```


---

## 作者：int08 (赞：3)

# 前言
月赛时没想，现在才发现这题其实不难。

没错，这又是一道让人误以为是动态规划的贪心绿题。

这次题解不是很好讲，如果没看懂，可以先看看代码。
# Solution
### 1、关于 $pA$、$pB$、$pC$
题目中说它们可以相等，然而，我们发现：

如果 $pA$、$pB$、$pC$ 有相等，不仅无法使任何一组相邻的两个字母变得不同，反而可能让本来不同的相邻字母变得相同。

**所以我们就让 $pA$、$pB$、$pC$ 都互不相同。**

### 2、最短操作次数
即使 $pA$、$pB$、$pC$ 都互不相同，对 $[l,r]$ 区间的相邻字母，相同与否情况也不会有任何改变。只能改变 $(l-1,l)$ 和 $(r,r+1)$。

**所以每次能减少两个相邻相同对。**
### 3、解决方法
根据前文的推导，我们的每次改变都可以设为 $pA=\text{B}$、$pB=\text{C}$、$pC=\text{A}$。

再说 $l$ 和 $r$：

先整体循环，在每次循环中用两个 $\text{for}$ 或者 $\text{while}$ 来寻找相邻相同对，一前一后。$l$ 和 $r$ 就设在这两个地方。

如果 $l$ 到达结尾，就可以退出大循环输出答案了。

# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j=-1,ans,a[2][5006];char s[5003];
int main()
{
	cin>>n;
	scanf("%s",s);
	for(;;)
	{
		i=j+1;
		while(s[i]!=s[i+1]&&i<n-1) {i++;} //寻找l的位置
		if(i>=n-1) break; //到底了,退出循环
		j=i+1;
		while(s[j]!=s[j+1]&&j<n-1) {j++;} //寻找r的位置                         
		ans++;a[0][ans]=i+2;a[1][ans]=j+1;
	}
	cout<<ans<<endl;
	for(i=1;i<=ans;i++) cout<<a[0][i]<<" "<<a[1][i]<<" BCA\n";
	return 0;
} 
```
# 后记
输入时千万不要连用 $\text{getchar()}$，最好也不要用字符串 $\text{cin}$。

---

## 作者：Coinred001 (赞：2)

题意：对于一个长度为 $n$ 的字符串 $S \in \{\texttt{A,B,C}\}$，给定一个操作，对于三个字符 $pA,pB,pC\in\{\texttt{A,B,C}\}$，使得 $S$ 中属于区间 $[l,r]$ 的字符中所有 $\texttt{A}\to pA$，所有 $\texttt{B}\to pB$，所有 $\texttt{C}\to pC$。求使得 $S$ 中任意两个相邻字符不同的最小操作次数及其中一个构造方案。  

显然，要通过区间长度大于一的操作使得 $S$ 中任意两个相邻字符不同，必然有 $pA \not= pB \not= pC$，否则可能会导致该区间内的的相邻相等字符变多。

我们容易知道，对于这样的一次操作，**区间内部除了两端的字符，其他位置的相邻字符是否相等的状况是不会发生改变的**。所以我们得出结论：一次操作只能让一个或两个原本相邻相同的字符变得不再相同。

根据上面这个结论，若设字符串中满足 $S_i=S_{i+1}$ 的位置个数为 $t$，则最小操作次数为 $\left \lceil \dfrac{t}{2} \right \rceil$ 次（因为如果剩下一个必须要多用一次操作）。

接下来考虑如何构造方案。根据上面的结论，设配对的满足 $S_i=S_{i+1}$ 位置分别为 $l$ 和 $r$，则为了将两端相同的相邻字符变得不同，我们需要对区间 $[l+1,r]$ 进行一次操作，将 $S_{l+1}$ 和 $S_r$ 变得与 $S_{l}$ 和 $S_{r+1}$ 不同。再接着讨论 $pA,pB,pC$ 的取值，若 $S_l \not= S_r$，我们只要将这两个字符互相变成对方即可（如 $\texttt{A}\to\texttt{B},\texttt{B}\to\texttt{A}$，输出操作 `BAC`，理由显然）；若 $S_l = S_r$，则考虑轮换（即 $\texttt{A}\to\texttt{B},\texttt{B}\to\texttt{C},\texttt{C}\to\texttt{A}$，输出操作 `BCA`），以避免 $S_{l+2}$与 $S_{r-1}$ 可能对答案造成的影响。

对于当 $t$ 为奇数时剩下的最后一组，考虑特殊处理。设最后一组为 $S_k=S_{k+1}$，同理的，我们只需要改变 $S_{k+1}$ 即可。通过讨论 $S_{k+1}$ 与 $S_{k+2}$ 的关系及字符情况即可得到具体变换方式，只要最后变换后的 $S_{k+1}$ 与 $S_{k+2}$ 不相等即可。

（当然，根据官方题解，每一次操作都采取轮换 `BCA` 即能满足所有条件，而剩下的最后一组只要将区间延长到 $[k+1,n]$ 即可规避讨论。终归是想麻烦了（悲））

```cpp
int n;
char s[N],op2[5]="BCA";
int p[N],cnt;

inline void Solve()
{
	scanf("%d%s",&n,s+1);
	if(n==1){printf("0\n");return;}
	for(int i=1;i<n;i++) if(s[i]==s[i+1]) p[++cnt]=i;
	printf("%d\n",(cnt+1)/2);
	int i;
	for(i=1;i<=cnt-1;i+=2)
	{
		char op[5]="ABC";
		int l=p[i],r=p[i+1];
		if(s[l+1]!=s[r])
		{
			swap(op[s[l+1]-'A'],op[s[r]-'A']);
			printf("%d %d %s\n",l+1,r,op);
		}
		else
		{
			printf("%d %d %s\n",l+1,r,op2);
		}
	}
	if(cnt&1)
	{
		int l=p[cnt];
		char op[5]="ABC";
		if(l==n-1 || s[l+1]==s[l+2])
		{
			printf("%d %d %s\n",l+1,l+1,op2);
		}
		else
		{
			if(s[l+1]=='A'&&s[l+2]=='B') strcpy(op,"CAB");
			if(s[l+1]=='B'&&s[l+2]=='A') strcpy(op,"ACB");
			if(s[l+1]=='A'&&s[l+2]=='C') strcpy(op,"BAC");
			if(s[l+1]=='C'&&s[l+2]=='A') strcpy(op,"ACB");
			if(s[l+1]=='B'&&s[l+2]=='C') strcpy(op,"BAC");
			if(s[l+1]=='C'&&s[l+2]=='B') strcpy(op,"BCA");
			printf("%d %d %s\n",l+1,l+1,op);
		}
	}
	return ;
}
/*
官方题解思路实现
inline void Solve()
{
	scanf("%d%s",&n,s+1);
	if(n==1){printf("0\n");return;}
	for(int i=1;i<n;i++) if(s[i]==s[i+1]) p[++cnt]=i;
	if(cnt&1) p[++cnt]=n;
	printf("%d\n",cnt/2);
	for(int i=1;i<=cnt;i+=2)
	{
		int l=p[i],r=p[i+1];
		printf("%d %d %s\n",l+1,r,op);
	}
	return ;
}
*/
```



---

## 作者：BINYU (赞：2)

#### 思路
由于题上要求每相邻的两个字符不相等，我们就先把相邻的字符隔开(用 $\parallel$ 表示)

比如

$A \parallel AB \parallel BCBABCBA\parallel A\parallel ABCACBABC$

这时$\parallel $的两旁的字符一定不一样

那么隔 ~~亿~~（yi）组轮换一下就行了

**注意：从第二组开始可能更省步数**


#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt = 1,l[5005],r[5005];
char a[5005],s[3];
int main()
{
    scanf("%d",&n);
    scanf("%s",a + 1); 
    l[1] = 1;
    for(int i = 1;i < n;i++)
        if(a[i] == a[i + 1])r[cnt] = i,l[++cnt] = i + 1;//收尾记录，统计组数 
    r[cnt] = n;
    cout<<cnt / 2<<endl; 
    for(int i = 2;i <= cnt;i += 2)//从第二组开始 
        printf("%d %d BCA\n",l[i],r[i]);
   return 0;
}
```



---

## 作者：Iam1789 (赞：1)

简单构造题。

首先看一个结论，若 $s_i=s_{i+1}$，如果将他们一起改变颜色，则它们还是相等的，对目标没有贡献。只有改变其中的一个才可以对目标产生贡献。所以对于每次操作，有用的仅仅是左端点和右端点。

于是我们可以维护双指针，当 $s_l=s_{l-1}$ 并且 $s_r=s_{r+1}$ 时进行一次操作 $l,r$，让 $s_l,s_r$ 分别与左边和右边不同。为了防止 $l,r$ 之间某些本不相同的数经过改变后相同了，所以操作串每个字符必须互不相同。

最后注意边界和细节就可以了，比如 $r=l+1,s_l=s_r$ 等，然后我们就可以通过这个题了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char s[5007];
struct cj{
	int l,r;
	bool sp;
}q[5007];
int js;
char s2[4]="BCA";
char s3[4]="CAB";
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*f;
}
void write(int x)
{
	if(x/10)
	write(x/10);
	putchar(x%10+'0');
}
int main()
{
	n=read();
	scanf("%s",s+1);
	int l=2,r=n-1;
	while(l<=r)
	{
		while(s[l]!=s[l-1]&&l<=r)
		++l;
		while(s[r]!=s[r+1]&&l<=r)
		--r;
		if((l==r+1&&s[l]!=s[r])||l>r+1)
		break;
		if(l==r+1&&s[l]==s[r])
		{
			++js;
			q[js].l=l;
			q[js].r=l;
			if(s2[s[l]-'A']==s[l+1])
			q[js].sp=1;
			break;
		}
		++js;
		q[js].l=l;
		q[js].r=r;
		for(int i=l;i<=r;++i)
		s[i]=s2[s[i]-'A']; 
		++l;
		--r;
		if((l==r+1&&s[l]!=s[r])||l>r+1)
		break;
		if(l==r+1&&s[l]==s[r])
		{
			++js;
			q[js].l=l;
			q[js].r=l;
			if(s2[s[l]-'A']==s[l+1])
			q[js].sp=1;
			break;
		}
		continue;
	}
	printf("%d\n",js);
	for(int i=1;i<=js;++i)
	{
		write(q[i].l);
		putchar(' ');
		write(q[i].r);
		putchar(' ');
		if(!q[i].sp)
		printf("%s\n",s2);
		else
		printf("%s\n",s3);
	}
	return 0;
}
```


---

## 作者：闲人 (赞：0)

## Step_1 题目简述
对于一个有 $ABC$ 组成的序列 $S$ 可执行如下操作：  
1. 选择一个区间 $\left[l, r \right]$ 。

1. 对于选择的区间而言可以将其中所有 $A$ 变为 $A, B, C$ 中的任意一个。 $B$ 和 $C$ 同理。  

我们需要通过以上两个操作是的序列 $S$ 相邻两个字符不相等， 求最小步骤和方案。  

[题目传送门](https://www.luogu.com.cn/problem/P7919)

## Step_2 题目分析

不难发现， 此题是一道标准的构造体。  
根据题目描述，可以发现序列 $S$ 的如下性质。
1. 假设我将一个区间中的所有 $A$ 变成 $B$ ， 所有 $B$ 变成 $C$ ， 所有 $C$ 变成 $A$ ，那么区间内（除两端）原本与相邻字符不同的依然不同， 原本相同的依然相同，也就是说区间（除两端）的本质不变。  

2. 我们一次性最多只能使两个原本与相邻字符相同的字符变的与相邻字符不同。

对于第二点而言， 需要同学们好好领悟一下（也许不用）。  

## Step_3 正解思路  
通过 Step_2 的两点性质，我们不难想出如下方法：  

1. 我们指定两个指针 $l, r$ ， 一个指向 $1$ 一个指向 $n$ 。

2. 当当前指针所指与两侧的字符不相等， 那么指针向中间靠拢，否则我将指针所指区间内（不包括两端）的所有字符 $A$ 变成 $B$ ， $B$ 变成 $C$ ， $C$ 变成 $A$ 。

注意，在移动指针时不要其中一个找到目标字符就马上变换区间，因为我们要使步数最小， 所以每次尽量两个一起变。  
 (PS. 特别注意指针最后一刻的状态， 极为容易出错）

## AC Code
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5e3 + 5;

char s[N];
bool map[N];

int tot;
int p1[N], p2[N];
char pr[N][4];

int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		char ch;
		cin >> ch;
		s[i] = ch;
		if (s[i] == s[i - 1] && i != 1) {
			map[i - 1] = 1;
			map[i] = 1;
		}
	}
	int l = 1, r = n;
	while(l < r)
	{
		if (s[l] != s[l + 1]) 
		{
			l++;
			continue;
		}
		if (s[r] != s[r - 1]){
			r--;
			continue;
		} 
		if (l == r - 1){
			if (s[l] != 'A' && s[r + 1] != 'A')
			{
				p1[++tot] = r;
				p2[tot] = r;
				pr[tot][0] = 'A';
				pr[tot][1] = 'A';
				pr[tot][2] = 'A';
				break;
			}
			if (s[l] != 'B' && s[r + 1] != 'B')
			{
				p1[++tot] = r;
				p2[tot] = r;
				pr[tot][0] = 'B';
				pr[tot][1] = 'B';
				pr[tot][2] = 'B';
				break;
			}
			if (s[l] != 'C' && s[r + 1] != 'C')
			{
				p1[++tot] = r;
				p2[tot] = r;
				pr[tot][0] = 'C';
				pr[tot][1] = 'C';
				pr[tot][2] = 'C';
				break;
			}
		}
		
		p1[++tot] = l + 1;
		p2[tot] = r - 1;
		pr[tot]['A' - 65] = 'B';
		pr[tot]['B' - 65] = 'C';
		pr[tot]['C' - 65] = 'A';
		for (int i = l + 1; i <= r - 1; i++) s[i] = pr[tot][s[i] - 65];
	}
	printf("%d\n", tot);
	for (int i = 1; i <= tot; i++)
	{
		printf("%d %d ", p1[i], p2[i]);
		for (int j = 0; j < 3; j++) printf("%c", pr[i][j]);
		puts("");
	}
	return 0;
}
```

## 后记
月赛唯一一道作对的题

---

## 作者：ricky0916 (赞：0)

题意：略

解析：每一次操作，我们把一个序列分成 $ 3 $ 个部分，假设这三个部分为 $abc$ （$a$ 和 $c$ 可能为空），其中 $ b $ 是要修改的子串。

我们会发现一件事：修改前后，$ abc $ 内部的相邻两个字符的相同和不同的情况不会发生改变。

考虑贪心。从前往后扫一遍，遇到两对相邻且相同的字符，就将从较前面那对的后一个字符到较后面那段的前一个字符这一段修改。

这里有个小技巧：可以一直令修改为"BCA"，这样能保证把相同的改成不同的。

若最后还有一对，可以将这对后面的一个字符到结尾这段修改。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
static char buf[1000000],*pa=buf,*pd=buf;
static char buf2[1000000],*pp=buf2;
#define getchar() pa==pd&&(pd=(pa=buf)+fread(buf,1,1000000,stdin),pa==pd)?EOF:*pa++
inline void pc(char ch){
	if(pp-buf2==1000000) fwrite(buf2,1,1000000,stdout),pp=buf2;
	*pp++=ch;
}
inline void pcc(){
	fwrite(buf2,1,pp-buf2,stdout);
	pp=buf2;
}
inline int read(){
	int x=0;
	bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f^=1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	if(f) return -x;
	return x;
}
void write(long long x){
	static int sta[20];
	int top=0;
	if(x<0) pc('-'),x=-x;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) pc(sta[--top]+48);
}
inline int mx(int x,int y){
	return x>y?x:y;
}
inline char gc(){
	char ch=getchar();
	while(ch<'A'||ch>'C') ch=getchar();
	return ch;
}
int n,idx,ans,l[114514],r[114514];
char s[100010];
map<double,int>mp;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		s[i]=gc();
	}
	for(int i=1;i<n;i++){
		if(s[i]==s[i+1]){
			if(!idx) idx=i;
			else{
				l[++ans]=idx+1;
				r[ans]=i;
				idx=0;
			}
		}
	}
	if(idx) l[++ans]=idx+1,r[ans]=n;
	write(ans);
	pc('\n');
	for(int i=1;i<=ans;i++){
		write(l[i]);
		pc(' ');
		write(r[i]);
		pc(' ');
		pc('B');
		pc('C');
		pc('A');
		pc('\n');
	}
	pcc();
	return 0;
}
```


---

