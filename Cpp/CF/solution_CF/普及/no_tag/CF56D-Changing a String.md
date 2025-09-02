# Changing a String

## 题目描述

这里有一个由大写字母构成的字符串 $s$，我们把他的长度表示为 $|s|$。在一次操作中，我们可以做这几种事情：

- 插入一个字符——我们可以在 $pos$ 位置上插入一个大写字母 $ch$（$1\le pos\le |s|+1$），此时字符串的 $pos$ 位置变成 $ch$ 字符，并且，其余字符将依次后移，字符串长度也要增加 $1$。
- 删除一个字符——将 $pos$ 位置上的字符删除，同样，其余字符移动，并且字符串长度减少 $1$。
- 替换一个字符——将 $pos$ 位置上的字符替换为大写字母 $ch$（$1\le pos\le |s|$），字符串长度不改变。

你的任务就是计算字符串 $s$ 通过上面的操作变到字符串 $t$ 最少花的步数，并且输出操作过程。

## 样例 #1

### 输入

```
ABA
ABBBA
```

### 输出

```
2
INSERT 3 B
INSERT 4 B
```

## 样例 #2

### 输入

```
ACCEPTED
WRONGANSWER
```

### 输出

```
10
REPLACE 1 W
REPLACE 2 R
REPLACE 3 O
REPLACE 4 N
REPLACE 5 G
REPLACE 6 A
INSERT 7 N
INSERT 8 S
INSERT 9 W
REPLACE 11 R
```

# 题解

## 作者：JOE_ZengYuQiao_0928 (赞：2)

[先看题](https://www.luogu.com.cn/problem/CF56D)
### 题意简化
有 $A$ 和 $B$ 两个字符串，不断地进行以下三种字符操作：
1. 删除一个字符。
2. 插入一个字符。
3. 将一个字符改为另一个字符。

求将字符串 $A$ 转换为字符串 $B$ 的最小操作次数。
### 题目思路
我们发现这题与 [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758?contestId=137798)基本相同，状态转移方程完全一致，只需加上输出操作过程便行，这里就不再讲解 P2758，直接开讲如何输出操作过程。
#### 考虑输出第一个插入操作。
我们知道 $ dp_{x,y}$ 的插入操作是从 $ dp_{x,{y-1}} $ 转移过来的，而我们反推如果 $ dp_{x,{y-1}}+1= dp_{x,y}$ 就说明进行了此操作，立即输出。
#### 考虑输出第二个删除操作。
我们知道 $ dp_{x,y}$ 的删除操作是从 $ dp_{{x-1},y} $ 转移过来的，而我们反推如果 $ dp_{{x-1},y}+1= dp_{x,y}$ 就说明进行了此操作，立即输出。 
#### 考虑输出第三个替换操作。
我们知道 $dp_{x,y}$ 的插入操作是从 $dp_{{x-1},{y-1}} $ 转移过来的，而我们反推如果 $ dp_{{x-1},{y-1}}+1= dp_{x,y}$ 说明进行了此操作，立即输出。
#### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
string a,b;
int n,x[N],dp[N][N];
void dfs(int x,int y){
    if(x<=0&&y<=0)return ;//边界 
    else if(y>=1&&dp[x][y]==dp[x][y-1]+1){
        dfs(x,y-1);//下一个状态 
        cout<<"INSERT "<<y<<" "<<b[y]<<"\n";//输出 
    }//插入 
    if(x>=1&&dp[x][y]==dp[x-1][y]+1){
        dfs(x-1,y);//下一个状态 
        cout<<"DELETE "<<y+1<<"\n";//输出 
    }//删除 
    else if(x>=1&&y>=1&&dp[x][y]==dp[x-1][y-1]+1){
        dfs(x-1,y-1);//下一个状态 
        cout<<"REPLACE "<<y<<" "<<b[y]<<"\n";//输出 
    }//替换 
    else dfs(x-1,y-1);//下一个状态 
}//输出过程 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(),cout.tie();
	cin>>a>>b;
    a="A"+a;
    b="C"+b;
    int n=a.size()-1;
    int m=b.size()-1; 
    for(int i=1;i<=n;i++)dp[i][0]=i;
    for(int i=1;i<=m;i++)dp[0][i]=i;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
    		if(a[i]!=b[j])dp[i][j]=min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;
    		else dp[i][j]=dp[i-1][j-1];
		}
	}
	cout<<dp[n][m]<<"\n";//从P2758复制过来的（^o^） 
	dfs(n,m);
	return 0;
}
```

---

## 作者：Stone_Xz (赞：2)

## [传送门](https://www.luogu.com.cn/problem/CF56D)

 - 本篇题解适合基础较弱的人看。
 - 小提示：本题与 [编辑距离](https://www.luogu.com.cn/problem/P2758) 这道题相似，建议先去把编辑距离做了，有助于攻克此题。

## 简要题意：

> 给定两个字符串 $a$ 和 $b$，每次可以对字符串 $a$ 做三种操作：插入一个字符（```INSERT```）、删除一个字符（```DELETE```）、将一个字符替换为另一个字符（```REPLACE```）。求将 $a$ 转换成 $b$ 的最小操作次数和最优情况下的操作过程。

## 分析：动态规划

首先，我们解决第一个问题：将 $a$ 转换成 $b$ 的最小操作次数。

 - **状态**：$dp[i][j]$ 表示字符串 $a$ 的前 $i$ 个字符转换成字符串 $b$ 的前 $j$ 个字符的最少操作次数。
 
 想出了这个状态，第一问的答案就显而易见了：
 
 设字符串 $a$ 的长度为 $n$，字符串 $b$ 的长度为 $m$。
 
 - **第一问答案**：$dp[n][m]$。
 
 接下来，我们推出状态转移方程就行了。
 
 - **状态转移方程**：至于状态转移方程，我们要根据题目分情况讨论
 
 	1. **删除**：删掉 $a[i]$ 这个位置，此时只要让 $a$ 的前 $i - 1$ 个字符变成 $b$ 的前 $j$ 个字符就行了。可得 $dp[i][j] = dp[i - 1][j] + 1$。
    
  	2. **插入**：在 $a[i]$ 后面插入一个字符 $b[j]$，此时让 $a$ 的前 $i$ 个字符变成 $b$ 的前 $j - 1$ 个字符就行了。可得 $dp[i][j] = dp[i][j - 1] + 1$。
 
 	3. **替换**：把 $a[i]$ 替换成 $b[j]$，此时让 $a$ 的前 $i - 1$ 个字符变成 $b$ 的前 $j - 1$ 个字符就行了。可得 $dp[i][j] = dp[i - 1][j - 1] + 1$。

在这三种情况中取操作次数最小的那一个，完整的就是：

```dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;```

但如果 $a[i]$ 一开始就等于 $b[j]$，让 $a$ 的前 $i - 1$ 个字符变成 $b$ 的前 $j - 1$ 个字符就行了。所以还要判断一下：

```if(a[i] == b[j])	dp[i][j] = dp[i - 1][j - 1];```

## 输出操作过程：

通过状态转移方程，我们可以判断 $dp[i][j]$ 是从哪个状态转移过来的，也就可以知道它对应的操作，用递归输出即可，注意先输出前面的操作，再输出后面的。

## AC 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;

const int N = 2e3 + 5;
int dp[N][N]; 
string a, b; 

void print(int i, int j)
{
	if(i == 0 && j == 0)
		return ;
	if(i >= 1 && dp[i][j] == dp[i - 1][j] + 1) // 删除操作 
	{
		print(i - 1, j); // 先输出前面的操作
		cout << "DELETE " << j + 1 << "\n";
	}
	else if(j >= 1 && dp[i][j] == dp[i][j - 1] + 1) // 插入操作 
	{
		print(i, j - 1);
		cout << "INSERT " << j << " " << b[j] << "\n"; 
	}
	else if(i >= 1 && j >= 1 && dp[i][j] == dp[i - 1][j - 1] + 1) // 替换操作 
	{
		print(i - 1, j - 1);
		cout << "REPLACE " << j << " " << b[j] << "\n";
	}
	else
	{
		print(i - 1, j - 1);
	}
}

int main() { 
	cin >> a >> b;
	a = '#' + a; //让下标从1开始
	b = '#' + b;
	int n = a.size() - 1;
	int m = b.size() - 1;
	for(int i = 1; i <= n; i++) 
		dp[i][0] = i;
	for(int i = 1; i <= m; i++)
		dp[0][i] = i;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			if(a[i] != b[j])
				dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
			else
				dp[i][j] = dp[i - 1][j - 1];
		}
	cout << dp[n][m] << "\n";
	print(n, m);
	return 0;
}
```

---

## 作者：yhx0322 (赞：2)

upd on $2023.12.12$：更改了描述不恰当的内容。 
## Description
有两个字符串 $A$ 和 $B$，有三种操作：

- 删除一个字符；
- 插入一个字符；
- 将一个字符改为另一个字符。

求：最少的操作次数将 $A$ 转换为 $B$，并且按照题目给定格式输出操作的方法。

## Solution
一道动态规划题目，比较经典，就比如洛谷上 [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758) 这道题，就极为相似，但是是简化版，建议先做完再来做这题。

首先，将问题做一个转化：

字符串 $A$ 插入一个字符，变成字符串 $B$；相当于**字符串 $B$ 删除一个字符，成为字符串 $A$。**

所以，问题转化为了：有两种操作。

- 删除 $A$ 或 $B$ 的某一个字符。
- 将一个字符更改为另一个字符。

设 $f_{i, j}$ 表示**字符串 $A$ 取出前 $i$ 个字符，和字符串 $B$ 取出前 $j$ 个字符**，编辑距离的结果。
### 边界设定
$i=0,f_{i,j}=j;$

$j=0,f_{i,j}=i$。
### 状态转移方程
如果当前字符删除，则操作次数的最小值为 $\min(f_{i, j - 1} + 1,f_{i-1,j} + 1)$。

如果都不要删除，在 $A_i$ 和 $B_j$ 不相同的情况下，消耗一次操作次数，进行修改。

$f_{i,j}=\min(f_{i,j}, f_{i-1,j-1}+(A_i \neq B_j))$。

### 打印
可以逆序打印，根据最终的 $dp_{n,m}$ 逆推出操作的步骤，具体的详见代码。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2010;
char a[N], b[N];
int f[N][N];

void print(int x, int y) {
	if (x <= 0 && y <= 0) return;
	if (x >= 1 && f[x][y] == f[x - 1][y] + 1) { // 删除字符串 B 中的字符
		print(x - 1, y);
		printf("DELETE %d\n", y + 1);
	} else if (y >= 1 && f[x][y] == f[x][y - 1] + 1) { // 插入一个字符
		print(x, y - 1);
		printf("INSERT %d %c\n", y, b[y]);
	} else if (x >= 1 && y >= 1 && f[x][y] == f[x - 1][y - 1] + 1) { // 替换
		print(x - 1, y - 1);
		printf("REPLACE %d %c\n", y, b[y]);
	} else print(x - 1, y - 1);
}

int main() {
	scanf("%s%s", a + 1, b + 1);
	int n = strlen(a + 1), m = strlen(b + 1);
	// DP 求解最少代价
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (!i) f[i][j] = j;
			else if (!j) f[i][j] = i;
			else {
				f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
				f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[i] != b[j]));
			}
		}
	}
	printf("%d\n", f[n][m]);
	print(n, m); // 递归打印
	return 0;
}
```

---

## 作者：2024sdhkdj (赞：2)

## 前置传送门
**[题面](https://www.luogu.com.cn/problem/CF56D)**

**[MY BLOG](https://www.luogu.com.cn/blog/hsb0507/solution-cf56d)**

**[AC CODE](https://www.luogu.com.cn/record/129620610)**
## 前置知识： 递归，线性 dp
## 题意描述
这道题的题意与 [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)近乎相同，但又有难度升级，建议先完成那道题再来切此题，效果更好。题意即给定两个字符串 $s$ 和 $t$，要你执行若干次操作，使得 $s$ 变成 $t$，且操作次数最少。最后输出**最少操作次数**与每一步的操作（即**路径**）。对于每次操作，你可以在 $s$ 中**插入**、**删除**、**替换**任意**一个**字符。
## 算法分析
此题的递推性质已经很明显了，即一个字符串会由另一个字符串**插入**、**删除**、**替换**任意**一个**字符得到。那么，我们可以考虑 dp。
### 状态
在设状态之前，先想想状态与什么东西有关？显然是两个字符串的长度。于是可以设：**$dp[i][j]$ 表示 $s$ 的前 $i$ 个字符变为 $t$ 的前 $j$ 个字符的最小操作次数。**
### 答案
根据我们设的状态：
$$ans=dp[|s|][|t|]$$
即：**$s$ 的前 $s$ 的长度个字符变成 $t$ 的前 $t$ 的长度个字符（也就是 $s$ 和 $t$ 本身）的最小操作次数。**
### 状态转移方程
在推状态转移方程之前，我们先想想，**当前状态**可以由哪几个**决策点**转移过来？显然，根据题意，有且只有三个。那我们就需要分类讨论了。

1. 当由上一个字符串**插入**一个字符得来时：$dp[i][j]=dp[i][j-1]+1$。

2. 当由上一个字符串**删除**一个字符得来时：$dp[i][j]=dp[i-1][j]+1$。

3. 当由上一个字符串**替换**一个字符得来时：

	- 当当前两个字符串的末尾字符相等时，不需要替换：$dp[i][j]=dp[i][j-1]$；
    
   - 当当前两个字符串的末尾字符不等时，需要替换：
	$dp[i][j]=dp[i][j-1]+1$。
    
那么，整合一下就是：
```cpp
dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
if(s[i]==t[j])
     dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
```
### 初始值（边界）
初始状态比较好找，即：

1. $dp[i][0]=i,i[1,|s|]$；
    
2. $dp[0][j]=j,j[1,|t|]$；

3. $dp[0][0]=0$。

好的，那么 dp 部分完成了，接下来才是本题的难点：**输出路径**。

### 路径输出
对于路径输出，我们可以记录每次当前状态是由那个状态转移过来的，然后在循环调用输出。但这样实现比较麻烦，实际上，dp 的路径可以递归输出。我们从终点（两个字符串的初始形态）开始，每次递归调用转移到当前状态的子的状态，然后再输出即可。注意！！！**一定要先递归在输出**！！！ 因为这样才能使输出是正序的，不然就会反过来输出，至于原因可以理解为递归的原理。递归的边界就是两个字符串的长度都为 $0$ 时。
## 时间复杂度分析
dp 部分与路径输出的时间复杂度都为 $O(nm)$。$n$、$m$ 分别为字符串 $s$、$t$ 的长度。
## 代码
若解释不详之处请看代码及其注释。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
string s,t;
int len1,len2;
int dp[N][N];
void dfs_print(int x,int y){//输出路径
    if(x<=0&&y<=0)//边界
        return ;
    if(x>=1&&dp[x][y]==dp[x-1][y]+1){//删除
        dfs_print(x-1,y);
        cout<<"DELETE "<<y+1<<"\n";
    }
    else if(y>=1&&dp[x][y]==dp[x][y-1]+1){//插入
        dfs_print(x,y-1);
        cout<<"INSERT "<<y<<" "<<t[y]<<"\n";
    }
    else if(x>=1&&y>=1&&dp[x][y]==dp[x-1][y-1]+1){//替换
        dfs_print(x-1,y-1);
        cout<<"REPLACE "<<y<<" "<<t[y]<<"\n";
    }
    else//啥也不干
        dfs_print(x-1,y-1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>s>>t;
    len1=s.size();
    len2=t.size();
    s=' '+s;
    t=' '+t;//使下标从 1 开始
    for(int i=1;i<=len1;i++)
        dp[i][0]=i;
    for(int i=1;i<=len2;i++)//赋初始值
        dp[0][i]=i;
    for(int i=1;i<=len1;i++)
        for(int j=1;j<=len2;j++){//状态转移
            dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
            if(s[i]==t[j])
                dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
        }
    cout<<dp[len1][len2]<<"\n";
    dfs_print(len1,len2);//从终点开始递归输出
	return 0;
}
```
## 总结
此题主要考察**思维**与**递归**，是一道比较综合的**线性 dp 类**题目，相当于是[ P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)和[ P2066 机器分配](https://www.luogu.com.cn/problem/P2066)的结合版，~~当然，也考察你的英文水平。~~
## 两个建议
- 建议此题评为**黄题或者绿题**，因为在原黄题[ P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)的基础上，此题还添加了输出路径的要求，更考验思维与代码能力。

- 建议将题意翻译改进，因为翻译中没有说明输出路径的格式，但是原文却说明了，~~这对于我这种不会英文的蒟蒻来说实在很不友好 QWQ！~~

以上建议请管理大大参考！

---

## 作者：Dehydration (赞：1)

### 前言：

建议看看[P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)，与这道题相类似。

### 思路：

~~不会做的去看 P2758 再来做这一道题。~~

我们看到 P2758 的与这道题除了需要输出步骤其他一模一样，能不能从 P2758 中找出步骤呢？

因为 P2758 是一道状态转移的 dp 题目，所以如果这个状态是从上个状态转移过来的，在这一题目里即前一个状态加一等于下一个状态，则我们可以唯一确定我们是做了什么操作。

所以，我们可以基于 P2758 写一个步骤输出函数，如果两个不同步数下的状态是从转移过来的就输出操作即可。


### 代码：

P2758 代码：

```
#include<bits/stdc++.h>
using namespace std;
string A,B;
char s1[2005],s2[2005];
int edit[2005][2005];
int dp(int i,int j){
    if(edit[i][j]!=-1) return edit[i][j];
    if(i==0) return edit[i][j]=j;
    if(j==0) return edit[i][j]=i;
    int bonus=1;
    if(s1[i]==s2[j]) bonus=0;
    return edit[i][j]=min(min(dp(i-1,j)+1,dp(i,j-1)+1),dp(i-1,j-1)+bonus);
}
int main(){
    cin>>A>>B;
    memset(edit,-1,sizeof(edit));
    int len1=A.length(),len2=B.length();
    for(int i=1;i<=len1;i++) s1[i]=A[i-1];
    for(int i=1;i<=len2;i++) s2[i]=B[i-1];
    dp(len1,len2);
    cout<<edit[len1][len2];
    return 0;
}
```

输出步骤代码：

```
void DIP(int x,char y,int op){//输出，0删除，1插入，2替换
	if(y=='!'){
		cout<<"DELETE ";
		cout<<x<<' ';
		cout<<'\n';
	}else {
		if(op==1){ 
			cout<<"INSERT ";
			cout<<x<<' ';
			cout<<y;
			cout<<'\n';
		}else {
			cout<<"REPLACE ";
			cout<<x<<' ';
			cout<<y;
			cout<<'\n';			
		}
	}
}
void step(int i,int y){
	if(i<=0&&y<=0)return;
    if(i>=1&&edit[i][y]==edit[i-1][y]+1){//符合条件删除（从删除转移过来，注意范围
        step(i-1,y);
        DIP(y+1,'!',0);
    }
    else if(y>=1&&edit[i][y]==edit[i][y-1]+1){同上
        step(i,y-1);
        DIP(y,s2[y],1);       
    }
    else if(i>=1&&y>=1&&edit[i][y]==edit[i-1][y-1]+1){
        step(i-1,y-1);
        DIP(y,s2[y],2);
    }
    else step(i-1,y-1);
}
```

先算出每个状态转移，再根据这个状态是不是前三个的哪一个转移过来继续递归即可，现在两个加起来即可，如果不会建议先去做编辑距离。

代码：

```
#include<bits/stdc++.h>
using namespace std;
string A,B;
char s1[2005],s2[2005];
int edit[2005][2005];
void DIP(int x,char y,int op){
	if(y=='!'){
		cout<<"DELETE ";
		cout<<x<<' ';
		cout<<'\n';
	}else {
		if(op==1){ 
			cout<<"INSERT ";
			cout<<x<<' ';
			cout<<y;
			cout<<'\n';
		}else {
			cout<<"REPLACE ";
			cout<<x<<' ';
			cout<<y;
			cout<<'\n';			
		}
	}
}
void step(int i,int y){
	if(i<=0&&y<=0)return;
    if(i>=1&&edit[i][y]==edit[i-1][y]+1){
        step(i-1,y);
        DIP(y+1,'!',0);
    }
    else if(y>=1&&edit[i][y]==edit[i][y-1]+1){
        step(i,y-1);
        DIP(y,s2[y],1);       
    }
    else if(i>=1&&y>=1&&edit[i][y]==edit[i-1][y-1]+1){
        step(i-1,y-1);
        DIP(y,s2[y],2);
    }
    else step(i-1,y-1);
}
int dp(int i,int j){
    if(edit[i][j]!=-1) return edit[i][j];
    if(i==0) return edit[i][j]=j;
    if(j==0) return edit[i][j]=i;
    int bonus=1;
    if(s1[i]==s2[j]) bonus=0;
    return edit[i][j]=min(min(dp(i-1,j)+1,dp(i,j-1)+1),dp(i-1,j-1)+bonus);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>A>>B;
    memset(edit,-1,sizeof(edit));
    int len1=A.length(),len2=B.length();
    for(int i=1;i<=len1;i++ ) s1[i]=A[i-1];
    for(int i=1;i<=len2;i++) s2[i]=B[i-1];
    dp(len1,len2);
    cout<<edit[len1][len2]<<'\n';
	step(len1,len2);
    return 0;
}
```

完美撒花！

---

## 作者：LOLchn0 (赞：1)

## 题意：
将一个字符串变为目标字符串，可以执行插入，置换和删除三种操作，求最少操作数。
## 思路：
设 $dp[i][j]$ 为字符串 $s$ 的前 $i$ 个字符替换成 $s1$ 的前 $j$ 个字符的最小花费。则有以下三种转移方法：

将 $s[i]$ 替换为 $s1[j]$。真实位置是 $j$。

删除 $i$ 位置的数。对应真实的 $s$ 的位置是 $j + 1$，因为这个转移相当于 $s$ 的前 $i-1$ 字符已经变成 $s1$ 的前 $j$ 个字符，所以删除的是第 $j+1$ 个位置的字符。

在 $i$ 位置后面添加一个数。真实位置是 $j$。

## 代码：
```c
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 1010;
char s[maxn], s1[maxn];
int dp[maxn][maxn];
void print(int i, int j, int remain) {
    if(!remain) return;
    if(i > 0 && j > 0 && dp[i - 1][j - 1] + (int)(s[i] != s1[j]) == dp[i][j]) {
        print(i - 1, j - 1, remain -  (int)(s[i] != s1[j]));
        if(s[i] != s1[j]) printf("REPLACE %d %c\n", j, s1[j]);
    } else if(i > 0 && dp[i - 1][j] + 1 == dp[i][j]) {
        print(i - 1, j, remain - 1);
        printf("DELETE %d\n", j + 1);
    } else if(j > 0 && dp[i][j - 1] + 1 == dp[i][j]) {
        print(i, j - 1, remain - 1);
        printf("INSERT %d %c\n", j, s1[j]);
    }
}
int main() {
    scanf("%s", s + 1);
    scanf("%s", s1 + 1);
    int n = strlen(s + 1), m = strlen(s1 + 1);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) dp[i][0] = i;
    for (int i = 1; i <= m; i++) dp[0][i] = i;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (int)(s[i] != s1[j]));
            dp[i][j] = min(dp[i][j], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
        }
    printf("%d\n", dp[n][m]);
    print(n, m, dp[n][m]);
}
```


---

## 作者：zhanglh (赞：0)

### Description

有两个字符串 $A$ 和 $B$，支持三种操作：

* 删除一个字符；
* 插入一个字符；
* 将一个字符改为另一个字符。

求：将 $A$ 转换为 $B$ 的最小操作次数，并按题目给定格式输出操作方案。

$1 \le |A|, |B| \le 1000$

### Solution

简单 dp。和 P2758 是双倍经验。

$1 \le |A|, |B| \le 1000$，定义 $f_{i, j}$ 表示考虑 $A$ 的前 $i$ 位和 $B$ 的前 $j$ 位，将 $A$ 转化为 $B$ 的最小操作次数。

如何转移？

* $A_i = B_j$，则 $f_{i,j} = f_{i-1,j-1}$。
* $A_i \not= B_j$，

1. 若删除一个字符，则 $f_{i,j} = f_{i-1,j} + 1$
2. 若插入一个字符，则 $f_{i,j} = f_{i,j-1} + 1$
3. 若将一个字符改为另一个字符，则 $f_{i,j} = f_{i-1,j-1}+1$

所有转移取 $\min$ 即可。

总结一下，状态转移方程就是

$$f_{i, j} = \min\{f_{i-1,j}+1, f_{i,j-1}+1, f_{i-1,j-1}+[A_i \not= B_j]\}$$

答案就是 $f_{n,m}$。DFS 倒推输出操作方案。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char a[1010], b[1010];
int n, m, f[1010][1010], cnt;

//f[i][j] 考虑A的前i位和B的前j位 将A转化为B的最小操作次数

void output(int i, int j) {
    if (i == 0 && j == 0) return;
    else if (i > 0 && f[i][j] == f[i - 1][j] + 1) {
        output(i - 1, j);
        cout << "DELETE " << j + 1 << "\n";
    } else if (j > 0 && f[i][j] == f[i][j - 1] + 1) {
        output(i, j - 1);
        cout << "INSERT " << j << " " << b[j] << "\n";
    } else if (i > 0 && j > 0 && f[i][j] == f[i - 1][j - 1] + 1) {
        output(i - 1, j - 1);
        cout << "REPLACE " << j << " " << b[j] << "\n";
    } else if (i > 0 && j > 0 && f[i][j] == f[i - 1][j - 1]) {
        output(i - 1, j - 1);
    }
}

int main() {
    cin >> (a + 1) >> (b + 1);
    n = strlen(a + 1);
    m = strlen(b + 1);
    memset(f, 0x3f, sizeof f);
    //f[0][0] = 0;
    for (int i = 0; i <= n; i++) f[i][0] = i;
    for (int j = 0; j <= m; j++) f[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[i] != b[j]));
            f[i][j] = min(f[i][j], min(f[i - 1][j], f[i][j - 1]) + 1);
        }
    }cout << f[n][m] << "\n";
    output(n, m);
    return 0;
}
```

Thanks for reading! ^_^

---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF56D)
# 题意
给定字符串 $s$ 和 $t$，并给出三种操作：
- 删除一个字符。
- 插入一个字符。
- 替换一个字符。
问 $s$ 转换成 $t$ 需要的最少操作次数。
# 思路
很显然，这是个动态规划题，$dp_{i,j}$ 表示 $s$ 的前 $i$ 个字符转换成 $t$ 的前 $j$ 个字符需要的操作次数。那么分类讨论状态转移方程。
- 删除：删除 $s_i$，那么只要 $s$ 的前 $i-1$ 个字符等于 $t$ 的前 $j$ 个字符即可，此时状转方程为 `dp[i][j]=dp[i-1][j]+1`。
- 插入：在 $s_i$ 后面插入 $t_j$，这时只要 $s$ 的前 $i$ 个字符等于 $t$ 的前 $j-1$ 个字符即可。方程为 `dp[i][j]=dp[i][j-1]+1`。
- 替换：把 $s_i$ 替换成 $t_j$，此时只要 $s$ 的前 $i-1$ 个字符与 $t$ 的前 $j-1$ 个字符相等即可，方程为 `dp[i][j]=dp[i-1][j-1]+1`。

那么 `dp[i][j]` 的值就是上面三个值中最小的。

注意：

如果 $s_i=t_j$，那么方程与上面的第三种情况相同，要特判一下。

代码就不放了，求关~

---

## 作者：foryou_ (赞：0)

双倍经验：P2758。

令 $dp_{i,j}$ 表示 $s$ 前 $i$ 个字符要变成 $t$ 前 $j$ 个字符所需的最少移动次数。

答案即为 $dp_{\lvert s \rvert,\lvert t \rvert}$。

显然有初始状态 $dp_{i,0}=dp_{0,i}=i$。 

因为我们只可能从添、删、替三种操作转移而来，

于是有转移方程：

- 添：

$$
dp_{i,j}=dp_{i-1,j}+1
$$

- 删：

$$
dp_{i,j}=dp_{i,j-1}+1
$$

- 替：

$$
\begin{cases}
dp_{i,j}=dp_{i-1,j-1}(s_i \neq t_i)\\
dp_{i,j}=dp_{i-1,j-1}+1(s_i = t_i)
\end{cases}
$$

三者取 $\min$ 即可。

关于输出，我们定义递归函数 $\operatorname{print}(x,y)$。

边界：$x \le 0,y \le 0$。

接着我们分别从上述三种操作中寻找路径。

但是，我们考虑到我们输出的字符一定是目标字符串 $t$ 中的字符。

因此我们考虑将对 $s$ 的添、删、替操作转化为对 $t$ 的操作。

- 添：

	若 $x,y$ 满足 $x>0,dp_{x,y}=dp_{x-1,y}+1$，
   
   则执行 $\operatorname{print}(x-1,y)$，并输出 $\texttt{DELETE} \ y+1$（$s$ 增加第 $x$ 字符与 $t$ 删去第 $y+1$ 字符等价）。
   
- 删：

	若 $x,y$ 满足 $y>0,dp_{x,y}=dp_{x,y-1}+1$，
   
   则执行 $\operatorname{print}(x,y-1)$，并输出 $\texttt{INSERT} \ y$（$s$ 删除第 $x$ 字符与 $t$ 添加第 $y$ 字符等价）。
   
- 替：

	若 $x,y$ 满足 $x>0,y>0,dp_{x,y}=dp_{x-1,y-1}+1$，
   
   则执行 $\operatorname{print}(x-1,y-1)$，并输出 $\texttt{REPLACE} \ y$（$s$ 替换第 $x$ 字符与 $t$ 替换第 $y$ 字符等价）。
   
- 否则：

	执行 $\operatorname{print}(x-1,y-1)$（即退回一个字符）。
  
然后这题就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;

string A,B;
int n,m,dp[2031][2031];

void print(int x,int y){
	if(x<=0&&y<=0) return;
	if(x>=1&&dp[x][y]==dp[x-1][y]+1) print(x-1,y),cout<<"DELETE "<<y+1<<'\n';
	else if(y>=1&&dp[x][y]==dp[x][y-1]+1) print(x,y-1),cout<<"INSERT "<<y<<' '<<B[y]<<'\n';
	else if(x>=1&&y>=1&&dp[x][y]==dp[x-1][y-1]+1) print(x-1,y-1),cout<<"REPLACE "<<y<<' '<<B[y]<<'\n';
	else print(x-1,y-1);
}

int main(){
    getline(cin,A); getline(cin,B);
    n=A.length(),m=B.length();
    A='#'+A,B='#'+B;
    
    for(int i=1;i<=n;i++) dp[i][0]=i;
    for(int i=1;i<=m;i++) dp[0][i]=i;
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[i][j]=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+(A[i]!=B[j]));
    cout<<dp[n][m]<<'\n';
    print(n,m);
    return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

考虑 DP，设计状态 $dp_{i,j}$ 表示将字符串 $s$ 的前 $i$ 个字符变为字符串 $t$ 的前 $j$ 个字符所需要的最小花费，答案即为 $dp_{n,m}$（$n,m$ 为字符串长度）。

接着考虑状态转移。首先设定边界：当 $i$ 为 $0$ 时，需要插入字符 $j$ 次，当 $j$ 为 $0$ 时，需要删除字符 $i$ 次，故 $dp_{0,j}=i,dp_{i,0}=j$。我们发现，在字符串 $s$ 中插入字符与在字符串 $t$ 中删除字符是等价的。我们可以分别从这两个状态转移过来：

$$
dp_{i,j}=\min(dp_{i-1,j}+1,dp_{i,j-1}+1)
$$

还有一种情况，就是替换字符。我们可以将前 $i-1$ 个字符和前 $j-1$ 个字符先处理好，再判断：如果 $s_i=t_j$，则无需修改，$dp_{i,j}=dp_{i-1,j-1}$。若 $s_i\ne t_j$，则需要修改 $s_i$ 和 $t_j$ 中的一个，$dp_{i,j}=dp_{i-1,j-1}+1$。我们可以把上面所说的整理成一个状态转移方程：

$$
dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-1}+[s_i\ne t_j])
$$

这样就设计完了状态转移方程。

至于输出操作，只需要递归找到前一个状态即可，具体可以参考代码。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, m, dp[N][N];
string s1, s2;

void print(int x, int y) {
    if (x <= 0 && y <= 0) return ;
    if (x >= 1 && dp[x][y] == dp[x - 1][y] + 1) {
        print(x - 1, y);
        cout << "DELETE " << y + 1 << "\n";
    }
    else if (y >= 1 && dp[x][y] == dp[x][y - 1] + 1) {
        print(x, y - 1);
        cout << "INSERT " << y << " " << s2[y] << "\n";
    } 
    else if (x >= 1 && y >= 1 && dp[x][y] == dp[x - 1][y - 1] + 1) {
        print(x - 1, y - 1);
        cout << "REPLACE " << y << " " << s2[y] << "\n";
    }
    else
        print(x - 1, y - 1);
}

int main() {
    memset(dp, 0x3f, sizeof dp);
    cin >> s1 >> s2;
    n = s1.size(), m = s2.size();
    s1 = '#' + s1, s2 = '#' + s2;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (!i) dp[i][j] = j;
            else if (!j) dp[i][j] = i;
            else { 
                dp[i][j] = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1);
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (s1[i] != s2[j]));
            }
        }
    }
    cout << dp[n][m] << "\n";
    print(n, m);
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题解

所以这道题到底为了啥啊，不就是编辑距离板子题加上输出吗？

你考虑设状态 $f_{i, j}$ 为 $a$ 的前 $i$ 位，$b$ 的前 $j$ 位要匹配最少需要的步数，那么我们的初始化显然如下：

- $f_{0, i} = i$，意思是 $a$ 的前 $0$ 位和 $b$ 的前 $i$ 位匹配，只能插入 $i$ 个字符。

- $f_{i, 0} = i$，同理，只是只能删除 $i$ 个字符。

然后我们考虑转移，显然有删除，插入，替换三种转移：

- 删除：$f_{i, j} = \min(f_{i - 1, j})$，表示将当前 $a$ 的第 $i$ 位删掉，也就是把匹配字符串的第 $j + 1$ 位给删掉。

- 插入：$f_{i, j} = \min(f_{i, j - 1})$，表示当前匹配字符串的第 $j$ 位需要插入一个字符才能使得两个字符串匹配。

- 替换，分两种情况，当 $a_i = b_j$ 时：$f_{i, j} = \min (f_{i - 1, j - 1})$，当 $a_i \ne b_j$ 时：$f_{i, j} = \min (f_{i - 1, j - 1} + 1)$，这个很好理解，如果是相同的就不需要替换，如果是不同的，那么就都替换。

然后考虑输出怎么输出，我们可以使用搜索输出，考虑输出时的位置就是上述讲的匹配字符串的操作位置。

输出的代码放上来：

```cpp
void dfs ( int i, int j ) {
	if ( !i && !j ) {
		return ;
	}
	if ( i > 0 && f[i][j] == f[i - 1][j] + 1 ) {  // 需要删除
		dfs ( i - 1, j );
		cout << "DELETE " << j + 1 << '\n';
	}
	else if ( j > 0 && f[i][j] == f[i][j - 1] + 1 ) {  // 需要插入
		dfs ( i, j - 1 );
		cout << "INSERT " << j << " " << b[j] << '\n';
	}
	else if ( f[i][j] == f[i - 1][j - 1] + 1 ) {  // 需要替换
		dfs ( i - 1, j - 1 );
		cout << "REPLACE " << j << " " << b[j] << '\n';
	}
	else {  // 不需要任何操作
		dfs ( i - 1, j - 1 );
	}
}
```

然后你 DP 完之后就直接输出就可以了，这里就不放完整代码了。

---

