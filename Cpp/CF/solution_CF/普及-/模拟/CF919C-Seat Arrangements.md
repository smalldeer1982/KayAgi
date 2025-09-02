# Seat Arrangements

## 题目描述

教室有n排座位，每排有m个座位，将教室表示为$n*m$  的矩阵。字符'.'代表一个空座位，而'*'意味着座位被占用。你需要在同一行或同一列中找到k个连续的空席位，并为你和你的朋友安排这些座位。你的任务是找出安排座位的方式。如果学生所占据的地方不同，两种方式被认为是不同的。

## 样例 #1

### 输入

```
2 3 2
**.
...
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 2 2
..
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 3 4
.*.
*.*
.*.
```

### 输出

```
0
```

# 题解

## 作者：Randyhoads (赞：2)

## solution
这道题就是找连续k个空位。就横着竖着就扫一遍就行了
每次去找连续空位且长度大于K，这是就有这段空位的长度-k+1中
站的方法。。。
当k=1时要除以2。。。
### ！！！
这道题貌似是ltt出的洛谷P3654 First Step 的 加强版
做那道题的时候，我好像O(n^3)就过了。。。（我还是太菜了）

---

## 作者：Cloud_Umbrella (赞：1)

## 题意

给定一个 $n \times m$ 的矩阵，要求同一行或同一列里连续的且长度等于 $k$ 的 `.` 的数量。

## 分析

其实我是抱着暴力去试试，没想到就成功了~~（数据比较水）~~。因为题目问最多有多少个，我们用变量 $len$ 记录长度（行和列都记录，记得清零），假设 $len$ 为 $4$，$k$ 为 $3$，那么在这一行（或列）中的答案显然是 $2$，所以我们的判断条件就是 $len \ge k$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int ans,len;//分别记录答案和长度 
char s[2005][2005];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>s[i][j];//读入 
			
	for(int i=1;i<=n;i++){
		len=0;//每轮都要清零 
		for(int j=1;j<=m;j++){
			s[i][j]=='.' ? len++:len=0;//如果目前的s[i][j]是'.'，那么长度加一。否则变为零。 
			if(len>=k) ans++;
		}
	}
	for(int i=1;i<=m;i++){//与上面大同小异 
		len=0;
		for(int j=1;j<=n;j++){
			s[j][i]=='.' ? len++ : len=0;
			if(len>=k) ans++;
		}
	}
	cout<<(k!=1 ? ans : ans/2);//特判k=1，ans要除以二 
	return 0;//每天好习惯伴终生 
}

```

---

## 作者：_farawaystar_ (赞：1)

#### 题意简述

求每行每列连续 $k$ 个' . '的情况和。

#### 题目分析

1. 遍历每行：一行中遇到连续 $sum$ 个' . '，则可知，在答案中加上 $\max((sum-k+1),0)$ 个情况。

2. 遍历每列：方法同上。

3. 若 $k$ 为 $1$ ,则可知：遍历每行每列时，重复计算了两遍，所以只有答案的一半。

代码：

```
#include<iostream>
#include<cstdio> 
using namespace std;
int n,m,k,ans;
char c[4005][4005];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		getchar();
		int sum=0;
		for(int j=1;j<=m;j++){
			c[i][j]=getchar();
			if(c[i][j]=='.')sum++;
			else{
				ans+=max((sum-k+1),0);
				sum=0;
			}
		}
		ans+=max((sum-k+1),0);
	}
	for(int j=1;j<=m;j++){
		int sum=0;
		for(int i=1;i<=n;i++)
			if(c[i][j]=='.')sum++;
			else{
				ans+=max((sum-k+1),0);
				sum=0;
			}
		ans+=max((sum-k+1),0);
	}
	k==1?cout<<ans/2:cout<<ans;
	return 0;
}
```

谢谢大家！

---

## 作者：杨xyz (赞：1)

不要爆搜！！！

蒟蒻用搜索后觉得是常数问题，卡了半天常数才知道爆搜不可能过。

正解也非常简单，开两个二重循环，数每行每列连续的空格就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans;
int a[2001][2001];
int main()
{
	char a1;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		a1=getchar();
		for(int j=1;j<=m;j++){
		    a1=getchar();
		    if(a1=='.')a[i][j]=1;
		}   
	} 
	for(int i=1;i<=n;i++){//数每一行连着的空格
		int l=0;
		for(int j=1;j<=m;j++){
			if(a[i][j]==1)l++;
			if(!a[i][j]||j==m){
				if(l>=k)ans+=l-k+1;
				l=0;	
			}
		}
	}
	for(int i=1;i<=m;i++){//数每一列连着的空格
		int l=0;
		for(int j=1;j<=n;j++){
			if(a[j][i]==1)l++;
			if(!a[j][i]||j==n){
				if(l>=k)ans+=l-k+1;	
				l=0;
			}
		}
	}
	if(k==1)ans/=2;//当k=1时，分别向下向右了两遍，需要除以二。
        printf("%d",ans);
	return 0;
}

```


---

## 作者：Last_kiss_Snow_Dog6 (赞：1)

这题目翻译属实是给我整不会了，然后就按排列组合做的，发现答案好像有亿点大，不太对劲，于是就重新理解一遍题目。

题目：有 $ n\times m $ 个座位，你要选连续的 $ k $ 个座位，当然这点座位可以是横向的连续，也可以是竖向的连续，不过必须连在一起。大致上这么理解一下就可以做题了。
## Part1
正常存入，看数据范围：$ 1\le n,m,k\le 2000 $ 所以32位整型完全够，不过要存字符，所以开一个字符数组，大小开到 $ 2000\times 2000 $ 也不会爆内存，所以就开到最大即可。要有三个变量，一个存当前的长度，一个存答案，一个存空座位个数。
```cpp
char a[2005][2005];
int n,m,k;
cin>>n>>m>>k;
for(int i=0;i<n;i++)
{
	for(int j=0;j<m;j++)
	{
		cin>>a[i][j];
	}
}
int len=0,ans=0,ans2=0;
```
## Part2
判断个数的话，可以分开判断，先判断横向的，再判断竖向的。每次判断遇到空座，就把长度加一，当长度足够时就开始增加答案的个数，当遇到有人的座位时，将长度变量清空。到下一行（判断横向是否连续时）或到下一列（判断竖向是否连续时）记得清空当前长度。
```cpp
//先判断横向是否连续 
for(int i=0;i<n;i++)//行 
{
	len=0;//每次换行清空长度变量 
	for(int j=0;j<m;j++)//列 
	{
		if(a[i][j]=='.') 
		{
			len++;//当遇到空座位时，长度变量加一 
			ans2++;//记录空座位的个数 
		}
		else len=0;//当遇到有人的座位时，长度变量清空 	
		if(len>=k)//当长度达到要求后开始增加答案个数 
		{
			ans++;
		}
	}
}
len=0; //记得清空长度变量
//再判断竖向是否相等 
for(int j=0;j<m;j++)//列 
{
	len=0;//每次换列清空长度数组 
	for(int i=0;i<n;i++)//行 
	{
		if(a[i][j]=='.')
		{
			len++;//当遇到空座位时，长度变量加一
			ans2++;//记录空座位的个数 
		} 
		else len=0;//当遇到有人的座位时，长度变量清空 
		if(len>=k)//当长度达到要求后开始增加答案个数 
		{
			ans++;
		}
	}
}
```
## Part3
要动脑子的部分已经结束了（~~可以把脑子扔了~~）。接下来就剩输出了：如果 $ k=1 $ 那么说明每个空座都可以坐，否则就输出计算好的答案。
```cpp
if(k==1) cout<<ans2;
else cout<<ans;
```
## Last
最后献上完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[2005][2005];
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>a[i][j];
		}
	}
	int len=0,ans=0,ans2=0;
	//先判断横向是否连续 
	for(int i=0;i<n;i++)//行 
	{
		len=0;//每次换行清空长度变量 
		
		for(int j=0;j<m;j++)//列 
		{
			if(a[i][j]=='.') 
			{
				len++;//当遇到空座位时，长度变量加一 
				ans2++;//记录空座位的个数 
			}
			else len=0;//当遇到有人的座位时，长度变量清空 
			
			if(len>=k)//当长度达到要求后开始增加答案个数 
			{
				ans++;
			}
		}
	}
	len=0; //记得清空长度变量
	//再判断竖向是否相等 
	for(int j=0;j<m;j++)//列 
	{
		len=0;//每次换列清空长度数组 
		
		for(int i=0;i<n;i++)//行 
		{
			if(a[i][j]=='.')
			{
				len++;//当遇到空座位时，长度变量加一
				ans2++;//记录空座位的个数 
			} 
			else len=0;//当遇到有人的座位时，长度变量清空 
			
			if(len>=k)//当长度达到要求后开始增加答案个数 
			{
				ans++;
			}
		}
	}
	if(k==1) cout<<ans2;
	else cout<<ans;
	return 0; 
}
```


---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF919C)

我们先看一下，只要先输入矩阵，然后判断行和列是否能放下 $k$ 个人就行了。

不过这题好像很容易被判断成深搜，但是其实一个 $n^2$ 级别的暴力就可以过了。（$1 \le n,m,k \le2000$）

然后我们需要一个变量 ``tot`` 来记录这一行或这一列的空位置个数（然后每次判断一下是否能放下所有人就可以了）。

然后还有一点，很多题解都提到了。就是关于 $k=1$ 这类问题，我们是需要将所求到答案除以 $2$ 就行了（行和列计算时，同一个格子被计算了两次）。

然后还有一小点，如果你使用了 ``scanf`` 优化读入，那么你需要在写 ``%c`` 前加上一个空格。原因可能是输入的时候需要将每次的换行卡掉（具体自己查吧）。如果你直接写，那么是会在第七个点错误的。

然后就是循环的时候 ``i`` 和 ``j`` 的位置问题（具体位置看一下代码）。

---

# AC代码
```
#include<bits/stdc++.h>//头文件
using namespace std;
bool maap[2005][2005];
int n,m,k,tot,ans;
char x;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf(" %c",&x);
			if(x=='*')maap[i][j]=1;//平平无奇的输入
		}
	}
	for(int i=1;i<=n;i++){//判断行数 
		for(int j=1;j<=m;j++){
			if(!maap[i][j])tot++;
			if(maap[i][j]||j==m){
				if(tot>=k)ans+=tot-k+1;
				tot=0;
			}
		}
	}
	for(int i=1;i<=m;i++){//判断列数 
		for(int j=1;j<=n;j++){
			if(!maap[j][i])tot++;//判断是否是空位置，注意一下这里i,j的位置
			if(maap[j][i]||j==n){
				if(tot>=k)ans+=tot-k+1;
				tot=0;
			}
		}
	}
	if(k==1)ans/=2;//特判 
	printf("%d",ans);
	return 0;
} 
```


---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，行和列的方法数可以分开计算。设置变量 $e$ 存储方案数。观察数据范围发现，直接搜索肯定 TLE。

首先计算行的方法数。遍历每一行的每一个字符，如果一个 `*` 前有连续的 $h$ 个 `.`，就 $e\gets e+\max(h-c+1,0)$。注意这个过程在每一行可能进行多次，每次结束都要把 $h$ 重置为 $0$。列的方法数的计算方法与此相似。

另外，当人数为 $1$ 时，$e$ 应该除以 $2$，因为每种方法都被计算了两遍。

~~如果有人抄我的代码用 Python 过不了，我绝对不会告诉你去百度搜索 PyPy。~~
## 代码
```python
a,b,c = map(int,input().split())
d,e = [list(input()) for e in range(a)],0
for f in range(a):
    h = 0
    for i in range(b):
        if d[f][i] == '.':
            h += 1
        elif h > 0:
            e += max(h-c+1,0)
            h = 0
    e += max(h-c+1,0)
for g in range(b):
    h = 0
    for i in range(a):
        if d[i][g] == '.':
            h += 1
        elif h > 0:
            e += max(h-c+1,0)
            h = 0
    e += max(h-c+1,0)
if c == 1:
    print(e//2)
else:
    print(e)
```

---

## 作者：__Dist__ (赞：0)

### 题目描述

[详见原题](https://www.luogu.com.cn/problem/CF919C)

### 思路讲解

一开始以为是深搜，却发现并不需要，既然要判断连续的空座，我们只要分别以横排和竖排为单位扫两遍数组，找到每个符合条件的连续的空座，每找到一个就增加结果 $ ans $ 的数量。

还有一个细节，就是如果 $ k=1 $，那么数组横着、竖着会重复扫到一个点，从而造成重复。因此需要将 $ ans $ 除以 $ 2 $。

具体操作见代码。

### 代码环节

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int n, m, k;
int ans;//结果
int cnt;//计数
char s[2005][2005];
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> s[i][j];
	for (int i = 1; i <= n; i++) {//先看横排符合要求的
		cnt = 0;
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '.') ++cnt;
			else cnt = 0;
			if (cnt >= k) ++ans;//符合要求就增加结果数量
		}
	}
	for (int i = 1; i <= m; i++) {//再看竖列符合要求的
		cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (s[j][i] == '.') ++cnt;
			else cnt = 0;
			if (cnt >= k) ++ans;//符合要求就增加结果数量
		}
	}
	cout << (k != 1 ? ans : ans / 2);//特判输出
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

# CF919C题解
## 原题链接
[**CF919C**](https://www.luogu.com.cn/problem/CF919C)

## 思路分析
既然题目中说了“在同一行或同一列中找到 $k$ 个连续的空席位”，那么我们就分别从行和列下手。枚举的每列或每行的某个点如果是 `.`，那么计数 $cnt$ 加一，否则就将其清零。如果等于了 $k$ 的值就终止本次循环，并让记录答案的 $ans$ 加一。


并没有结束，我们来看这样一组数据：
```cpp
1 1 1
.
```
很明显这个题的答案是 $1$，但我们用代码运行却发现答案是 $2$，因为这个 `.` 会在横着和竖着的时候都被计算一遍，所以需要除以 $2$，怎么解决呢？很简单，加个特判就行了。

注意一点：这里只要 $k=1$ 答案就要除以 $2$，并不需要 $n$ 和 $m$ 也等于 $1$。

## Code：
```cpp
#include<bits/stdc++.h> 
using namespace std;
char s[2005][2005];
int n,m,k,cnt,ans;//ans记录答案，cnt记录每次.的数量 
int main(){ 
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>s[i][j];
	for(int i=1;i<=n;i++){//每行每行判断 
		cnt=0;//计数器清空 
		for(int j=1;j<=m;j++){
			if(s[i][j]=='.') cnt++; 
			else cnt=0;//如果不为.则清空计数器 
			if(cnt>=k) ans++;//只要满足题意答案数量就可以+1 
		}
	}
	for(int j=1;j<=m;j++){//每列每列判断，具体思路同每行判断 
		cnt =0;
		for(int i=1;i<=n;i++){
			if(s[i][j]=='.') cnt++;
			else cnt=0;
			if(cnt>=k) ans++;
		}
	}
	if(k==1)//特判 
		cout<<ans/2<<endl;
	else cout<<ans<<endl;
	return 0;
}
```

**无注释版的我放到了[这里](https://www.luogu.com.cn/paste/6dqefhhy)**

## [AC 记录](https://www.luogu.com.cn/record/110679765)

**THE END.**

**THANK YOU.**

---

## 作者：OoXiao_QioO (赞：0)

# 前言

这道题十分的有趣味，也很坑，但只要缕清思路，肯定就会 $\verb!AC!$。

# 思路

我一开始的思路是，遍历每个点 $(i,j)$，先从这个点扫到 $(i,j+k)$，再从 $(i,j)$ 扫到 $(i+k,j)$，写一个函数来判断是否满足朋友和自己全部入座，可以的话累加器 $+1$，最后输出一下累加器就行了。

给出代码：[代码](https://www.luogu.com.cn/paste/z6fpkkhe)

但这种做法能 $\verb!AC!$ 吗？当然不行了。如果 $n = 2000,m = 2000,k = 2000$，我们判断的次数就是 $2000$ $\times$ $2000$ $\times$ $(1000+2000)$ $\times$ $2000$，不用算都知道是一个巨大无比的数，肯定会超时，我们必须要考虑优化。

怎么优化呢？根据题面所说的同一行或同一列中找到 $k$ 个连续的空席位，我们能想到什么？那就是判断连续出现的字符！我们只需要判断每一行连续出现的字符是否 $\ge k$，如果 $\ge k$，那么统计的方案数 $s$ 就 $+1$，当然的，判断完行后，我们还需要判断每一列，最后输出一下答案就行啦！

# 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
//把大数组定义在函数外面，节省空间。 
char a[2001][2001];
int main()
{
	//定义
	 
	int n,m,i,j,k,s,cnt;//本人习惯用 i 和 n 表示循环行的变量与行数，用 j 和 m 表示循环列的变量与列数。 
	
	//输入 
	cin>>n>>m>>k;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>a[i][j];
	
	//变量赋值
	 
	s = 0;
	
	//操作
	 
	for(i=1;i<=n;i++)//先扫完每一列 
	{
		cnt = 0;//在统计连续出现的字符前，统计变量 cnt 先要清空。 
		for(j=1;j<=m;j++)
		{
			if(a[i][j]=='.')//如果满足了连续座位都空的情况 
				cnt++;//cnt++，连续出现的字符数量 +1。 
			else
				cnt = 0;//否则就是出现了有人的座位，没有必要统计下去了，cnt直接清空。 
			if(cnt>=k)//只要 cnt >= k，说明满足条件了，总方案变量 s++。
				s++;
		}
	}
	
	for(j=1;j<=m;j++)//与行相似，这里实现列。注意变量 j 的终止条件。 
	{
		cnt = 0;
		for(i=1;i<=n;i++)
		{
			if(a[i][j]=='.')
				cnt++;
			else
				cnt = 0;
			if(cnt>=k)
				s++;
		}
	}
	cout<<s/(k==1?2:1)<<endl;//这里用了一个小妙招，就是处理 k = 1 的情况。
	/*
	比如输入 
	1 1 1
	.
	
	这时我们发现，如果直接输出 s 就会输出 2，而不是正确答案 1，这是因为我们算行和列的时候算重复了，也就是行和列重合了
	所以我们需要 s / 2，把多余的消掉，这样就不用担心重复的问题了。 
	*/
	return 0;
}
```


---

## 作者：zhengenzhe (赞：0)

## 【题目大意】
给出 $n \times m$ 的一个矩阵，问有几个连续的且个数大于 $k$ 的 $\Huge{\color{red} . } $
## 【分析】
~~由于本题数据过水~~，所以直接暴力即可。先将横排的遍历一遍如果有连续的 $\Huge{\color{red} . } $ 且个数超过 $k$ 就将 $ans=ans+1$ 如果是 $\Large{\color{red} * } $ 则将 $len$ 重新赋值为 $0$。
## Code：
```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=2e3+1;
ll n,m,k,ans,length,temp;
char a[MAXN][MAXN];
void work1(){//横向遍历
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='.'){//即上文讲到的
				length++;
			}else{//有人坐了这个座位
				length=0;
			}
			if(length>=k){
				ans++;
			}
		}
		length=0;
	}
}
void work2(){//纵向遍历
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(a[j][i]=='.'){
				length++;
			}else{
				length=0;
			}
			if(length>=k){
				ans++;
			}
		}
		length=0;
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//优化
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='.'){
				temp++;
			}
		}
	}
	if(k==1){//特判k==1
		printf("%lld\n",temp);
		return 0;
	}
	work1();
	work2();
	printf("%lld\n",ans);
	return 0;
}
```

---

