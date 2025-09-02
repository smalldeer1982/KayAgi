# Magic Squares

## 题目描述

ABBYY 的聪明海狸喜欢谜题。他最喜爱的谜题之一是幻方。最近他想出了一个自动化解决这个谜题的方法，并决定将这个挑战作为 ABBYY Cup 的赛题。

幻方是一个大小为 $n \times n$ 的矩阵，其元素均为整数。该矩阵每行的数字之和等于某个数 $s$，每列的数字之和也等于 $s$。此外，主对角线上元素之和等于 $s$，副对角线上元素之和同样等于 $s$。下图展示了幻方的示例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178D3/df1aa6f903a3e44e4322a8498e9c3054e6afd786.png)

现给定包含 $n^{2}$ 个整数 $a_{i}$ 的集合，要求将这些数字填入一个 $n \times n$ 的方阵，使其构成幻方。注意每个数字在矩阵中出现的次数必须与其在原集合中出现的次数完全相同。

**题目保证解存在！**

## 样例 #1

### 输入

```
3
1 2 3 4 5 6 7 8 9
```

### 输出

```
15
2 7 6
9 5 1
4 3 8
```

## 样例 #2

### 输入

```
3
1 0 -1 0 2 -1 -2 0 1
```

### 输出

```
0
1 0 -1
-2 0 2
1 0 -1
```

## 样例 #3

### 输入

```
2
5 5 5 5
```

### 输出

```
10
5 5
5 5
```

# 题解

## 作者：Milthm (赞：0)



你发现这是一个搜索，但是肯定不能直接搜，会炸掉的。所以我们剪一剪枝，比较好想的剪枝有这几个：

- 明显，$s=\frac{\sum{a_i}}{n}$，因为所有元素加起来刚好是 $n$ 个 $s$。

- 如果搜到一行、一列或一个对角线的末尾，发现这一行、列或对角线上面的元素之和不等于 $s$，那么肯定错了，就不要往下搜了。这个和可以用数组来维护。

但是如果你只写了这两个剪枝，只能通过本题的第一个难度。在第二个难度就会 TLE 在第 $18$ 个点，更别说这题了，所以考虑其它更多的剪枝：

- 首先，我们加个火车头，但是评测结果没有发生太多改变，仍然 TLE 在上一题第 $18$ 个点。

- 考虑填上这个地方后，如果这一行、列或对角线还有 $x$ 个元素没有填，序列的最大值是 $p$，最小值是 $q$，这个地方要填的数是 $b$。如果 $b+xp\le s$ 或 $b+xq\ge s$，说明如果填了这个肯定是错的，去枚举下一个数即可。

这样写仍然还会 TLE 在第 $18$ 个点（有完没完了），于是我就去 CF 上看测试点是什么，发现这个测试点貌似专卡顺序搜索，于是我改成了倒着枚举元素，但是仍然 TLE 在第 $21$ 个点。

但是思路已经有了，我就再想了一下，怎么安排顺序能使得搜索最快，于是就有了这样一条剪枝：

- 因为一行里面肯定是有大的也有小的，所以我们把数组第一个放最小的，第二个放最大的，第三个放第二小的，第四个放第二大的……这样，搜索的时候排列就会有大有小，就会减少很多不必要的搜索。

然后你就可以快乐的 AC 了。


### AC code

```cpp
#include<iostream>
#include<algorithm>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("inline-functions-called-once")
#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
int n,b[105],a[15][15],vis[105],maxn=-1e9,minn=1e9,c[105]; 
long long sum,s,sum1[15],sum2[15],sum3,sum4; 
void dfs(int x,int y){
	//cout<<x<<" "<<y<<'\n';
	if(x>n){
		cout<<s<<'\n';
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				cout<<a[i][j]<<" ";
			}
			cout<<'\n';
		}
		exit(0);
	}
	for(int i=n*n;i>=1;--i){
		if(!vis[i]){
			int cnt=b[i]+sum1[y];
			if(x==n&&cnt!=s)continue; 
			if(cnt+(n-x)*maxn<s)continue;
			if(cnt+(n-x)*minn>s)continue;
			cnt=b[i]+sum2[x];
			if(y==n&&cnt!=s)continue;
			if(cnt+(n-y)*maxn<s)continue;
			if(cnt+(n-y)*minn>s)continue;
			if(x==y){
				cnt=b[i]+sum3;	
				if(x==n&&cnt!=s)continue;
				if(cnt+(n-x)*maxn<s)continue;
				if(cnt+(n-x)*minn>s)continue;
			}
			if(x+y==n+1){
				cnt=b[i]+sum4;
				//for(int j=1;j<x;++j){
				//	cnt+=a[j][n+1-j];
				//}
				if(x==n&&cnt!=s)continue;
				if(cnt+(n-x)*maxn<s)continue;
				if(cnt+(n-x)*minn>s)continue;
			}
			a[x][y]=b[i];
			vis[i]=1;
			sum1[y]+=b[i];
			sum2[x]+=b[i];
			if(x==y)sum3+=b[i];
			if(x+y==n+1)sum4+=b[i];
			if(y==n)dfs(x+1,1);
			else dfs(x,y+1);
			sum1[y]-=b[i];
			sum2[x]-=b[i];
			if(x==y)sum3-=b[i];
			if(x+y==n+1)sum4-=b[i];
			vis[i]=0;
			a[x][y]=0;
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n*n;++i)cin>>b[i],sum+=b[i],maxn=max(maxn,b[i]),minn=min(minn,b[i]);
	sort(b+1,b+n*n+1);
	for(int i=1;i<=n*n;++i){
		if(i&1)c[i]=b[(i+1)/2];
		else c[i]=b[n*n-(i-2)/2];
	}
	for(int i=1;i<=n*n;++i)b[i]=c[i];
	s=sum/n;
	dfs(1,1);
	return 0;
}

```

~~题外话：本题其实早就写过了，今天发现题解通道还开着，回来水个题解。~~


---

## 作者：_edge_ (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P1406)

本题主要考察选手乱搞能力，主题库那题较水，可以用搜索搜过去。

当然，该题正解也不是啥奇奇怪怪的东西，就是朴素的搜索。

我们来思考这样一个问题，怎么搜才能较快的搜到答案。

一种暴力的搜索是枚举 $n \times n$ 的全排列，很明显它是不能通过题目的。

一种可行的想法是，我们只需要搜到一个解就 ok 了，因此在搜的过程中我们可以把那些已经不合法的给 break 掉，这样可以省下一大把时间。

这是一个剪枝，已经可以通过那个双倍经验了。

对于这题，我们不需要保证字典序最小。

因此我们可以随机打乱一个序列，然后利用卡时间的操作来使得它正确。

类似于退火，但是不完全相同。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=21;
int n,a[INF],nn,b[INF>>1][INF>>1],sum11,l;
bool flag,vis[INF];
void print() {
	int sum=0,sum1=sum11;
	for (int i=1;i<=n;i++) sum+=b[i][n];sum=0;
	for (int i=1,j=1;i<=n;i++,j++) 
		sum+=b[i][j];
	if (sum1!=sum) return ;sum=0;
	for (int i=1,j=n;i<=n;i++,j--) 
		sum+=b[i][j];
	if (sum1!=sum) return ;
	flag=true;
	cout<<sum1<<"\n";
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++)
			cout<<b[i][j]<<" ";
		cout<<"\n";
	}
	return ;
}
void DFS(int x,int y) {
	l++;
	if (l>=3e7) return ;
	if (flag) exit(0) ;
	if (x==n && y>1) {
		int sum=0;
		for (int i=1;i<=n;i++) sum+=b[i][y-1];
		if (sum11!=sum) return ;
	}
	if (y>n) {
		int sum=0;for (int i=1;i<=n;i++) sum+=b[x][i];
		if (sum11!=sum) return ;
		x++;y=1;
	}
	if (x>n) {print();return ;}
	for (int i=1;i<=nn;i++) {
		if (vis[i]) continue;
		if (l>=3e7) return ;
		b[x][y]=a[i];
		vis[i]=true;
		DFS(x,y+1);
		vis[i]=false;
	}
	return ;
}
signed main()
{
	srand(time(0));
	scanf("%d",&n);nn=n*n;
	for (int i=1;i<=nn;i++) 
		{scanf("%d",a+i);sum11+=a[i];}
	sum11/=n;
	while (clock()<CLOCKS_PER_SEC*1.9) {
		for (int i=2;i<=nn;i++)
			swap(a[i],a[rand()%(i-1)+1]);
		l=0;
		DFS(1,1);
	}
	return 0;
}
```


---

