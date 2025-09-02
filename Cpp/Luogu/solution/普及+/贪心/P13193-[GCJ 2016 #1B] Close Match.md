# [GCJ 2016 #1B] Close Match

## 题目描述

你正在观看体育史上最重要的一场比赛：Oceania Coders 队对阵 Eurasia Jammers 队，比赛场地为 Centrifugal Bumble-Puppy 世界总决赛。不幸的是，由于你因期待而彻夜难眠，比赛期间你竟然睡着了！

现在计分牌上显示着双方的得分，可能带有一个或多个前导零（因为计分牌会显示固定位数的数字）。当你熟睡时，计分牌的一些灯泡被猛烈的球击坏了，因此一方或双方的得分中有一位或多位数字没有显示出来。

你觉得比分接近的比赛最精彩，所以你希望能够想象出一个比分尽可能接近的场景。你能否用某种方式填补所有缺失的数字，使得两队分数的绝对差值最小？如果有多种方案可以达到最小绝对差值，请选择 Coders 队得分最小的方案；如果在 Coders 队得分也相同的情况下仍有多种方案，则选择 Jammers 队得分最小的方案。

## 说明/提示

**样例解释**

在样例第 4 组中，注意答案不能是 15 10；该方案虽然绝对差值最小，但 Coders 队得分不是最小的。也不能是 05 10；该方案虽然绝对差值和 Coders 队得分都最小，但 Jammers 队得分不是最小的。

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 200$。
- $\mathbf{C}$ 和 $\mathbf{J}$ 长度相同。

**小数据集（测试集 1 - 可见）**

- $1 \leqslant \mathbf{C}$ 和 $\mathbf{J}$ 的长度 $\leqslant 3$。

**大数据集（测试集 2 - 隐藏）**

- $1 \leqslant \mathbf{C}$ 和 $\mathbf{J}$ 的长度 $\leqslant 18$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
4
1? 2?
?2? ??3
? ?
?5 ?0```

### 输出

```
Case #1: 19 20
Case #2: 023 023
Case #3: 0 0
Case #4: 05 00```

# 题解

## 作者：xiexiuqi29 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13193)

下文中设 $\mathbf{C}$ 和 $\mathbf{J}$ 的长度为 $n$。

可以想到 dfs 将每个问号从 $0$ 到 $9$ 进行枚举，

时间复杂度 $O(T10^n)$，可以获得 $n\le3$ 的分数。

考虑优化，因为题目要求绝对值最小，所以在 dfs 过程中 $\mathbf{C}$ 和 $\mathbf{J}$ 大小关系确定时，在较小数 ? 位置全填 $9$，在较小数 ? 位置全填 $0$ 最优，而且在大于和小于两种情况中应该让数位尽量接近。

时间复杂度 $O(Tn^2)$。~~（我感觉这题最难的是写代码）~~

```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b;
string c,e;//最优解对应的 a 和 b 的替换
bool ad,bd;//标记 a > b 或 a < b 的状态
int t,s,n;
long long minn;//当前最小差值
void dfs(int d)
{
	if(d==n)//计算当前组合的差值，并更新最优解
	  {
	  	long long aa=0,ab=0;
	  	for(int i=0;i<n;i++)
		  aa=aa*10+a[i]-'0',ab=ab*10+b[i]-'0';
		if(abs(aa-ab)<minn)
		  minn=abs(aa-ab),c=a,e=b;
		return;
	  }
	if(ad)//根据 ad 状态直接填充最优值
	  {
	  	bool fa=0,fb=0;
	  	if(a[d]=='?')
		  a[d]='0',fa=1;
		if(b[d]=='?')
		  b[d]='9',fb=1;
		dfs(d+1);
		if(fa)
		  a[d]='?';
		if(fb)
		  b[d]='?';
	  	return;
	  }
	if(bd)//根据 bd 状态直接填充最优值
	  {
		bool fa=0,fb=0;
	  	if(a[d]=='?')
		  a[d]='9',fa=1;
		if(b[d]=='?')
		  b[d]='0',fb=1;
		dfs(d+1);
		if(fa)
		  a[d]='?';
		if(fb)
		  b[d]='?';
		return;
	  }
    // 处理问号情况
	if(a[d]=='?'&&b[d]=='?')
	  {
	  	a[d]='0';
	  	b[d]='0';
	  	dfs(d+1);
		b[d]='1';
		bd=1;
		dfs(d+1);
		bd=0;
		a[d]='1';
		b[d]='0';
		ad=1;
		dfs(d+1);
		ad=0;
		a[d]='?';
		b[d]='?';
	  }
	else
	  if(a[d]=='?')
		{
			if(b[d]!='0')
			  {
			  	a[d]=b[d]-1;
			  	bd=1;
			  	dfs(d+1);
			  	bd=0;
			  }
			a[d]=b[d];
			dfs(d+1);
			if(b[d]!='9')
			  {
				a[d]=b[d]+1;
				ad=1;
				dfs(d+1);
				ad=0;
			  }
			a[d]='?';
		}
	  else
		if(b[d]=='?')
		  {
			if(a[d]!='0')
			  {
			  	b[d]=a[d]-1;
				ad=1;
				dfs(d+1);
				ad=0;
			  }
			b[d]=a[d];
			dfs(d+1);
			if(a[d]!='9')
			  {
				b[d]=a[d]+1;
				bd=1;
				dfs(d+1);
				bd=0;
			  }
			b[d]='?';
		  }
		else
		  {
			if(a[d]>b[d])
			  ad=1;
			if(a[d]<b[d])
			  bd=1;
			dfs(d+1);
			ad=0;
			bd=0;
		  }
}
int main()
{
	scanf("%d",&t);
	while(t--)
	  {
	  	ad=bd=0;
	  	s++;
	  	minn=0x3f3f3f3f3f3f3f3f;
	  	cin>>a>>b;
		n=a.size();
		dfs(0);
		printf("Case #%lld: ",s);
		cout<<c<<" "<<e<<"\n";
	  }
	return 0;
}
```

码风较丑，不喜勿喷。

---

