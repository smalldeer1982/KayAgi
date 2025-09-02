# [GCJ 2021 #3] Build-A-Pair

## 题目描述

你需要构造一对正整数。为此，你会获得一个十进制数字列表作为可用数字。你必须**恰好使用列表中的每个数字一次**，但可以自由选择哪些数字用于第一个整数，哪些数字用于第二个整数。同时，你可以自由决定每个整数内部数字的排列顺序，但**不允许在任何整数的最高位（最左侧）放置零**。请注意，你也不能选择仅包含一个零的整数，因为它不是正整数。

例如，给定数字列表 $[1, 0, 2, 0, 4, 3]$。你可以构造的有效数字对包括 $(200, 143)$ 和 $(3, 12400)$。而以下数字对则是**无效的**：

* $(0102, 34)$：存在前导零。
* $(0, 12340)$：包含非正整数。
* $(10, 243)$ 和 $(12300, 47)$：这些数字对中使用的数字列表与给定列表不完全一致。

给定数字列表，如何构造一对数字，使得它们的绝对差最小？

## 说明/提示

**样例解释**

最优构造的数字对为：
- 样例 #1：$31$ 和 $24$；
- 样例 #2：$10$ 和 $10$；
- 样例 #3：$700$ 和 $80$；
- 样例 #4：$89$ 和 $90$。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $\mathbf{D}$ 的每个字符均为十进制数字。
- $\mathbf{D}$ 中至少有两个字符不为 $\emptyset$。

**测试集 1（3 分，可见判定）**

- $2 \leq \mathbf{D}$ 的长度 $\leq 8$。

**测试集 2（12 分，可见判定）**

- $2 \leq \mathbf{D}$ 的长度 $\leq 36$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1234
0011
07080
0899```

### 输出

```
Case #1: 7
Case #2: 0
Case #3: 620
Case #4: 1```

# 题解

## 作者：_•́へ•́╬_ (赞：0)

## 思路

如果初始给了奇数个数码，那么安排完了肯定两个数字相差一位。显然，长的那个用较小的数码，且将小的数码放在较高位；短的那个反之。

如果初始给了偶数个数码，那么安排完了肯定两个数一样长。一个朴素的想法是，某个数码给两个，就给两个数各放一个，放在高位，（除非出现前导 $0$）。接下来要安排剩下的单个的数码，枚举两个数（除去以上已经确定过的）最高位分别是啥，然后贪心确定剩下来的。

然而，反例就在样例中，对于类似 $89,90$ 这样的，枚举拆散一对相同数码，然后照做。

## implementation

```cpp
#include<stdio.h>
#include<string>
#include<algorithm>
#define int long long
using namespace std;
int t,a[10],m,ans;char n[99];string u,v;
inline void bf(int l)
{
	u="";m=0;
	for(int i=9;i>=0;--i)
	{
		if(!i)if(!u.size()){for(int j=a[i];j--;n[m++]=48);break;}
		for(int j=a[i];j>(i==l?3:1);j-=2,u+=i^48);
		if(a[i]&1)n[m++]=i^48;
		if(i==l)n[m++]=i^48,n[m++]=i^48;
	}
	n[m]=0;reverse(n,n+m);
	if(!m){ans=0;return;}
	for(int i=0;i<m;++i)for(int j=i+1;j<m;++j)if(n[i]^n[j])
	{
		string w=u,x=u;int y,z;
		w+=n[i];x+=n[j];
		for(int k=0,l=m-2>>1;l;++k)if(k^i)if(k^j)x+=n[k],--l;
		for(int k=m-1,l=m-2>>1;l;--k)if(k^i)if(k^j)w+=n[k],--l;
		if(w[0]==48||x[0]==48)continue;
		sscanf(w.c_str(),"%lld",&y);sscanf(x.c_str(),"%lld",&z);
		ans=min(ans,z-y);
	}
}
main()
{
	scanf("%d",&t);
	for(int i=1,cnt;i<=t;++i)
	{
		scanf("%s",n);for(int i=0;i<10;a[i++]=0);u=v="";
		for(cnt=0;n[cnt];++a[n[cnt++]^48]);
		if(cnt&1)
		{
			for(int i=1;;++i)if(a[i]){--a[i];u+=i^48;break;}
			for(int i=9;;--i)if(a[i]){--a[i];v+=i^48;break;}
			for(int i=0;u.size()<cnt+1>>1;++i)
				for(;a[i]&&u.size()<cnt+1>>1;--a[i],u+=i^48);
			for(int i=9;v.size()<cnt>>1;--i)
				for(;a[i]&&v.size()<cnt>>1;--a[i],v+=i^48);
			int x,y;sscanf(u.c_str(),"%lld",&x);sscanf(v.c_str(),"%lld",&y);
			printf("Case #%lld: %lld\n",i,x-y);
		}
		else
		{
			ans=1ll<<60;
			bf(-1);for(int i=0;i<10;++i)if(a[i]>1)bf(i);
			printf("Case #%lld: %lld\n",i,ans);
		}
	}
}
```

---

