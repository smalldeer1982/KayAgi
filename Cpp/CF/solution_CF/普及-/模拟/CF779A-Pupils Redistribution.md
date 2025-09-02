# Pupils Redistribution

## 题目描述

在Berland每一个高中生的成绩都很有特点 — 一个在$1$ 和$5$ 之间的整数。

在高中0xFF有两个学生小组，每个小组都有$n$ 名学生。每名学生的成绩就像所知的 — 一个在$1$ 和$5$ 之间的整数。

学校主任想要在小组间重新分配这些学生以达到在两个小组间成绩为$1$ 的学生数量相等，成绩为$2$ 的学生数量相等，以此类推。换句话说，学校主任的目的是，在改变完学生的组成后，每个成绩在两个小组都有相同的人数。

实现这个的方式是，有计划的在小组间进行一系列的学生交换。每次交换中主任都会从$A$ 班(原文就是班，实际应该是组的意思)中选一名学生，再从B班中选一名学生。然后，交换他们所属的组。

输出最少的交换数，来使得每个成绩在两个小组都有相同的人数。

## 样例 #1

### 输入

```
4
5 4 4 4
5 5 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
1 1 1 1 1 1
5 5 5 5 5 5
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1
5
3
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
9
3 2 5 5 2 3 3 3 2
4 1 4 1 1 2 4 4 1
```

### 输出

```
4
```

# 题解

## 作者：封禁用户 (赞：4)

## 题意-思路
有两个组，每个组都有 $n$ 个人，每个人都有自己的成绩，你每次可以交换两个小组的人，输出最少的交换数，使得每个成绩在两个小组都有相同的人数。\
先统计两个小组各个成绩的数量，然后进行判断，如果某一个成绩出现次数为奇数，那么无解，输出 $-1$ ，否则统计要达到题目要求最少要置换的学生数量。
```cpp
#include <bits/stdc++.h>
using namespace std;
int otf[120], ans;
int main() 
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		int ele;
		cin>>ele;
		otf[ele]++;//A组分数
	}
	for(int i=1;i<=n;i++) 
	{
		int ele;
		cin>>ele;
		otf[ele]--;//每组分数差
	}//dd
	for(int i=1;i<=5;i++) 
	{
		if(abs(otf[i])%2==1) 
		{
			cout<<-1;
			return 0;
		}
		ans+=abs(otf[i]);//绝对值
	}
	cout<<ans/4;//已证明
	return 0;
}
```



---

## 作者：guozhetao (赞：3)

## 题目大意
给你两组学生，每组学生 $n$ 人，并给出每人的分数，问能否通过调换将每个成绩在两个小组都有相同的人数。
## 思路
首先，什么样才算不能通过交换呢？我们观察样例数据，发现如果有一种分数的人数是单数，那么就是无法交换。

交换的实现难度也不大。我们想统计出小组 $A$ 每个分数的人数。再与该分数总人数的一半相减取绝对值求出需要交换的个数，最后除以二输出。
## 为什么要除以二？
我们先看这组样例
### 样例输入
```
4
5 4 4 4
5 5 4 5
```

### 样例输出
```
1
```

我们发现 $A$ 小组有 $2$ 个与总人数的一半不同，但只需要将 $A$ 小组的一个 $4$ 和 $B$ 小组的一个 $5$ 调换即可。一次调换解决两个不同的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[105],b[105]; 
int danci[6],dancia[6];//统计次数 
int main() {
	scanf("%d",&n);
    //记录总共的每种分数数量和A小组每种分数数量
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
		danci[a[i]]++;
		dancia[a[i]]++;
	}
	for(int i = 1;i <= n;i++) {
		scanf("%d",&b[i]);
		danci[b[i]]++;
	}
    //判断不能通过调换解决
	for(int i = 1;i <= 5;i++) {
		if(danci[i] % 2 == 1) {
			printf("-1\n");
			return 0;
		}
	}
    //输出最少次数
	int ans = 0;
	for(int i = 1;i <= 5;i++) {
		ans += abs(dancia[i] - danci[i] / 2);
	}
	ans /= 2;//别忘记除以二
	printf("%d\n",ans);
}

```


---

## 作者：_JF_ (赞：3)

## CF779A Pupils Redistribution

这还是一个模拟题

思路非常简单，强行枚举题意，如果其中有同一个分数段的人数是单数的话，那么就一定无法完成调整，因为要求是两边的人数都一样。

设 $sa[i]$ 表示在第一组中每个分数段出现的人次，$sq[i]$ 表示在第二组每个分数段出现的人数次数。如果 $sa[i]=0$ 且 $sq[i]=0$ 的话，就可以跳出了，因为没有人。

设 $ans$ 表示调整次数，就是 $abs(sa[i]-sq[i])/2$。

最后要记得 $ans$ 要除以 $2$。

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N],b[N];
int sa[N],sq[N];
int main()
{
	int ans=0;
	int n;
	cin>>n;
	int maxx=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sa[a[i]]++;
		maxx=max(maxx,a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		sq[b[i]]++;
		maxx=max(maxx,b[i]);
	}
		
	for(int i=1;i<=maxx;i++)
	{
		if((sa[i]+sq[i])%2==1)
		{
			cout<<"-1";
			return 0;
		}
		if(sa[i]==0&&sq[i]==0)
			continue;
		ans+=abs(sa[i]-sq[i])/2;
	}
	cout<<ans/2<<endl;
}
```


---

## 作者：Luo_gu_ykc (赞：2)

## 题目大意

有两个组，每个组都有 $n$ 个人，每个人都有自己的成绩，
你每次可以交换两个小组的人，输出最少的交换数，使得每个
成绩在两个小组都有相同的人数。

## 题目大意

本题分为有解与无解，所以分类讨论。

### 有解

用三个桶数组记录每个成绩的出现数，其中一个记录 $a$ 组，一个记录 $b$ 组，还有一个都记录，然后枚举一遍，如果 $x_i$ 或者是 $y_i$ 的成绩没有出现过，累加此成绩在本组出现次数与总数的一半的差值，最后输出即可；

### 无解

如果有一个成绩的总数为奇数，无解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, cnt[15], x[105], y[105], v[15], tmp[15], ans;
bool vis[15];
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> x[i];
		cnt[x[i]]++; // 统计
		v[x[i]]++;
	}
	for(int i = 1; i <= n; i++){
		cin >> y[i];
		cnt[y[i]]++; // 统计
		tmp[y[i]]++;
	}
	for(int i = 1; i <= n; i++){
		if(cnt[x[i]] % 2 == 1 || cnt[y[i]] % 2 == 1){
			puts("-1"); // 万一总数为奇数，无解
			return 0;
		}
		if(!vis[x[i]]){
			ans += abs(v[x[i]] - (cnt[x[i]] / 2)); // 计算差值
			vis[x[i]] = 1;
		}
		if(!vis[y[i]]){
			ans += abs(tmp[y[i]] - (cnt[y[i]] / 2)); 
			vis[y[i]] = 1; 
		}
	}
	cout << ans / 2; // 记得除以2
	return 0;
}

---

## 作者：Nephren_Sakura (赞：1)

题目传送门：[link](https://www.luogu.com.cn/problem/CF779A)

定义 $sum1_i$ 表示在第 $1$ 个序列中 $i$ 的个数，$sum2_i$ 表示在第 $2$ 个序列中 $i$ 的个数

很明显，若要求无法完成，则必定存在一个 $i$ 满足 $1 \leq i \leq 5$ 并且 $sum1_i+sum2_i$ 为 $2$ 的倍数。

若要求可以完成，定义一个 $ans$ 表示对于每一个满足 $1 \leq i \leq 5$ 的 $i$ ，$sum1_i$ 与 $sum2_i$ 的差值之和。

最后输出 $ans \div 2$ 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod=317847191;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int sum1[10],sum2[10],n=read(),ans;
signed main(){
	for(int i=1; i<=n; i++)
		sum1[read()]++;
	for(int i=1; i<=n; i++)
		sum2[read()]++;
	for(int i=1; i<=5; i++)
		if((sum1[i]+sum2[i])%2){
			cout<<-1;
			return 0;
		}
		else
			ans+=abs((sum1[i]+sum2[i])/2-sum1[i]);
	cout<<ans/2;
	return 0;
}
```


---

## 作者：shAdomOvO (赞：1)

### 闲话
这道题其实并不难，那便不多废话，直接上正文
## 正文
#### 题目大意
告诉你两个班各种成绩各有多少人，让你求出最少交换几次可以是使两个班每种成绩的人数相同，不行就输出-1。

我们可以使用一个二维数组来存储数据，即a[3][6];a[1][n]表示A班成绩为N的人又多少个。

其实很容易就能想出，如果莫种成绩的人数量是单数，那么就肯定不能平均分配。代码如下：
```cpp
for(i=1;i<=5;i++){
		if((a[1][i]+a[2][i])%2!=0){
			cout<<-1;
			return 0;
		}
	}
```
如果能进行平均分配，就表明人数为偶数，我们可以先统计要切换的人数，即A组B组莫种成绩人数差的二分之一，最后又因为一次可以切换两个数，所以把结果再除以二。
## 总代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[3][6],n,i,j,b;
double ans=0;
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>b;
		a[1][b]++;
	}
	for(i=1;i<=n;i++){
		cin>>b;
		a[2][b]++;
	}
	for(i=1;i<=5;i++){
		if((a[1][i]+a[2][i])%2!=0){
			cout<<-1;
			return 0;
		}
	}
	for(i=1;i<=5;i++){
		ans+=abs(a[1][i]-a[2][i])/2;
	} 
	cout<<int(ans/2);
	return 0;
}
```


---

## 作者：Level_Down (赞：1)

### 题意简述：

·给定两个长度为n的数组。

·交换两个数组中的数，使得两组数中值相同的数数量一样。

·问最小的交换次数。

### 方法：

·使用一个数组存储第一组数中1至5每种值的个数，用另一个数组存储两个数组中1至5每种值的个数。

·计算，针对a[ i ]与b[ i ],我们要将a[ i ]中的值调整到b[ i ]中的值的一半。

公式：
```
ans += abs(a[i] / 2 - b[i]);
```
ps：在操作前我们还要先判断a[ i ]中的值能否被2整除，不能的话直接输-1结束。

·最终我们要将ans的值除以2，因为数字的交换是相互的。

#### 不要眨眼，代码来了！！！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,a[6],b[6],ans,sum;//数组a,b同上述第一步所讲
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {cin >> x;  a[x]++; b[x]++;}
	for (int i = 1; i <= n; i++) {cin >> x;  a[x]++;}//数据读入
	for (int i = 1; i <= 5; i++)
		{
			if (a[i] % 2 != 0) {cout << -1 << endl; return 0;}//判断
			ans += abs(a[i] / 2 - b[i]);//公式
		}
	cout << ans / 2 << endl;//如步骤三	
	return 0;//AC
 } 
```


---

## 作者：tryrtj (赞：1)

数据很小，可以暴力解决，方法很简单，就是统计一下每个数字在两组中出现的次数，如果两组次数和为奇数，则不可能，和为偶数则用其中一组的次数减去两组的平均数的绝对值就是这个数字所需要移动的次数。最后不要忘记把结果除以2，因为交换一次是交换两个数，会算重复

代码如下

```
#include<iostream>
#include<cmath>
using namespace std;
int c1[7],c2[7];
int main(){
	int n;
	cin>>n;
    int q;
	for(int i=0;i<n;i++){
		cin>>q;
		c1[q]++;//存储数字在两个里面出现的次数
	}
	for(int i=0;i<n;i++){
		cin>>q;
		c2[q]++;
	}
	int zong=0;//统计次数
	for(int i=1;i<=5;i++){
		if((c1[i]+c2[i])%2==0){//判断是否可能
			zong+=abs((c1[i]+c2[i])/2-c1[i]);//累加
		}
		else {
			cout<<-1<<endl;//否则直接输出-1
			return 0;
		}
	}
	cout<<zong/2<<endl;//输出总数/2
	return 0;
}
```


---

