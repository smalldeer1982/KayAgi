# Hongcow's Game

## 题目描述

This is an interactive problem. In the interaction section below you will see the information about flushing the output.

In this problem, you will be playing a game with Hongcow. How lucky of you!

Hongcow has a hidden $ n $ by $ n $ matrix $ M $ . Let $ M_{i,j} $ denote the entry $ i $ -th row and $ j $ -th column of the matrix. The rows and columns are labeled from $ 1 $ to $ n $ .

The matrix entries are between $ 0 $ and $ 10^{9} $ . In addition, $ M_{i,i}=0 $ for all valid $ i $ . Your task is to find the minimum value along each row, excluding diagonal elements. Formally, for each $ i $ , you must find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744B/60abf7e287a9efbab7664bfef9cac9ebdb2e6b1f.png).

To do this, you can ask Hongcow some questions.

A question consists of giving Hongcow a subset of distinct indices $ {w_{1},w_{2},...,w_{k}} $ , with $ 1<=k<=n $ . Hongcow will respond with $ n $ integers. The $ i $ -th integer will contain the minimum value of $ min_{1<=j<=k}M_{i,wj} $ .

You may only ask Hongcow at most $ 20 $ questions — he thinks you only need that many questions answered.

When you are ready to answer, print out a single integer $ -1 $ on its own line, then $ n $ integers on the next line. The $ i $ -th integer should be the minimum value in the $ i $ -th row of the matrix, excluding the $ i $ -th element. Do not forget to flush the final answer as well. Printing the answer does not count as asking a question.

You will get Wrong Answer verdict if

- Your question or answers are not in the format described in this statement.
- You ask strictly more than $ 20 $ questions.
- Your question contains duplicate indices.
- The value of $ k $ in your question does not lie in the range from $ 1 $ to $ n $ , inclusive.
- Your final answer is not correct.

 You will get Idleness Limit Exceeded if you don't print anything or if you forget to flush the output, including for the final answer (more info about flushing output below).

## 说明/提示

In the first sample, Hongcow has the hidden matrix

`<br></br>[<br></br> [0, 3, 2],<br></br> [5, 0, 7],<br></br> [4, 8 ,0],<br></br>]<br></br>`Here is a more readable version demonstrating the interaction. The column on the left represents Hongcow, while the column on the right represents the contestant.

`<br></br>3<br></br>              3<br></br>              1 2 3<br></br>0 0 0<br></br>              1<br></br>              3<br></br>2 7 0<br></br>              2<br></br>              1 2<br></br>0 0 4<br></br>              1<br></br>              2<br></br>3 0 8<br></br>              1<br></br>              1<br></br>0 5 4<br></br>              -1<br></br>              2 5 4<br></br>`For the second sample, it is possible for off-diagonal elements of the matrix to be zero.

## 样例 #1

### 输入

```
3
0 0 0
2 7 0
0 0 4
3 0 8
0 5 4```

### 输出

```
3
1 2 3
1
3
2
1 2
1
2
1
1
-1
2 5 4
```

## 样例 #2

### 输入

```
2
0 0
0 0```

### 输出

```
1
2
1
1
-1
0 0```

# 题解

## 作者：suxxsfe (赞：5)

因为对角线上都是 $0$，所以如果询问时包含了对角线，那结果必然是 $0$，会对判断造成干扰  
因此我们处理询问的结果时，如果当前这一行的处于对角线上的那一位，在询问时给出的 $k$ 个数中，则应该忽略这一行结果（因为它是 $0$）  

所以，就要想办法让每一位不在对角线上的数，都在至少一次询问中，不和它那一行的对角线上的数同时出现  
用二进制的想法考虑，因为任意一位不在对角线上的数，和那一行在对角线上的数的列号，都至少有一个二进制为相同  
所以就枚举每一个二进制位，分别询问所有的在这个二进制位上是 $0$ 或 $1$ 的列号  
那么对于每个数，就都会在它和它那一行对角线的列号，的不同的那个二进制位被枚举时，产生有效的询问  

话说这种思路好像还挺常见的，之前在 bzoj 某图论题（具体哪个忘了），好像就是用类似于 XX 和 XX 至少一个二进制位不同，来用二进制的思路优化的建边  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN puts("")
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int a[1005];
int main(){
	int n=read();
	std::memset(a,0x3f,sizeof a);
	for(reg int cnt,i=0;i<10;i++){
		cnt=0;
		for(reg int j=1;j<=n;j++)if(j&(1<<i)) cnt++;
		if(!cnt) goto NEXT;
		printf("%d\n",cnt);
		for(reg int j=1;j<=n;j++)if(j&(1<<i)) printf("%d ",j);EN;
		std::fflush(stdout);
		for(reg int j=1;j<=n;j++){
			cnt=read();
			if(j&(1<<i)) continue;
			a[j]=std::min(a[j],cnt);
		}
		NEXT:;
		cnt=0;
		for(reg int j=1;j<=n;j++)if(!(j&(1<<i))) cnt++;
		if(!cnt) continue;
		printf("%d\n",cnt);
		for(reg int j=1;j<=n;j++)if(!(j&(1<<i))) printf("%d ",j);EN;
		std::fflush(stdout);
		for(reg int j=1;j<=n;j++){
			cnt=read();
			if(!(j&(1<<i))) continue;
			a[j]=std::min(a[j],cnt);
		}
	}
	puts("-1");
	for(reg int i=1;i<=n;i++) printf("%d ",a[i]);
	std::fflush(stdout);
	return 0;
}
```

---

## 作者：封禁用户 (赞：4)

## 题解：CF744B Hongcow's Game

### 题意简述

一个 $n \times n$ 的矩阵，对角线上都是 $0$，请你找对角线外每行的最小值。你每次可以任选一个 $k(1 \le k \le n)$，询问每行这 $k$ 列的最小值，最多问 $20$ 次。

### 解题思路

二进制拆分，因为 $20$ 个二进制位足以覆盖每个列号。此时可以保证对于每行都有至少一次（其实是询问次数 $- 1$ 次）不包含对角线，输入的时候只要找每行最小非 $0$ 的即可（因为如果出现 $0$，则代表这次询问在对角线上，直接排除）。对于每次询问，更新每行答案，最后输出即可。

**提示：输出时要输 `-1`。**

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , a[1005] , cnt;
int ds(int q)
{
	int tmp = 0;
	while(q)
	{
		q /= 2;
		tmp++;
	}
	return tmp;
}
int main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		a[i] = 1000000007;
	}
	for(int i = 0 ; i < ds(n) ; i++)
	{
		cnt = 0;
		for(int j = 1 ; j <= n ; j++)
		{
			if(j & (1 << i))
			{
				cnt++;
			}
		}
		if(cnt)
		{
			cout << cnt << endl;
			for(int j = 1 ; j <= n ; j++)
			{
				if(j & (1 << i))
				{
					cout << j << ' ';
				}
				cout << endl;
			}
			for(int j = 1 ; j <= n ; j++)
			{
				cin >> cnt;
				if(j & (1 << i))
				{
					continue;
				}
				a[j] = min(a[j] , cnt);
			}	
		}
		cnt = 0;
		for(int j = 1 ; j <= n ; j++)
		{
			if(!(j & (1 << i)))
			{
				cnt++;
			}
		}
		if(!cnt)
		{
			continue;
		}
		cout << cnt << endl;
		for(int j = 1 ; j <= n ; j++)
		{
			if(!(j & (1 << i)))
			{
				cout << j << ' '; 
			}
			cout << endl;
		}
		for(int j = 1 ; j <= n ; j++)
		{
			cin >> cnt;
			if(!(j & (1 << i)))
			{
				continue;
			}
			a[j] = std::min(a[j] , cnt);
		}
	}
	cout << "-1" << endl;
	for(int i = 1 ; i <= n ; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	return 0;
}
```

---

## 作者：hongshixiaobai (赞：1)

# CF744B Hongcow's Game题解
## 题解

二进制拆分，枚举二进制每一位的 $0$ 和 $1$，分别询问，对每个回答，如果问的是当前位为 $0$，则对当前位为 $1$ 的行更新答案，因为这样一定不会更新成对角线上的值（有至少一个二进制位不同），反之亦然。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long i,j,ans[100005],qry[100005],vis[100005],cnt,tmp,n;
int main()
{
	memset(ans,0x3f,sizeof(ans));
	cin>>n;
	for(i = 0;i<=19;i++)
	{
		cnt = 0;
		for(j = 1;j<=n;j++)
			if(j&(1<<i))
				qry[++cnt] = j;
		if(!cnt)continue;
		cout<<cnt<<endl;
		for(j = 1;j<=cnt;j++)
			cout<<qry[j]<<' ';
		cout<<endl;
		for(j = 1;j<=n;j++)
		{
			cin>>tmp;
			if(j&(1<<i))continue;
			ans[j] = min(ans[j],tmp);
		}
		cnt = 0;
		for(j = 1;j<=n;j++)
			if(!(j&(1<<i)))
				qry[++cnt] = j;
		if(!cnt)continue;
		cout<<cnt<<endl;
		for(j = 1;j<=cnt;j++)
			cout<<qry[j]<<' ';
		cout<<endl;
		for(j = 1;j<=n;j++)
		{
			cin>>tmp;
			if(!(j&(1<<i)))continue;
			ans[j] = min(ans[j],tmp);
		}
	}
	cout<<-1<<endl;
	for(i = 1;i<=n;i++)cout<<ans[i]<<' ';
	cout<<endl;
}
```

---

