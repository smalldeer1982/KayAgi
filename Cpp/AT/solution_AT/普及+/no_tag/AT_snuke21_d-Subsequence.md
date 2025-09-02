# Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_d



# 题解

## 作者：xuan_gong_dong (赞：1)

## 题面

[Subsequence](https://www.luogu.com.cn/problem/AT_snuke21_d)
## 分析

很难不看出这是一道组合数学的题。

考虑在 $S$ 序列中先将其子序列 $T$ 看成一个整体，再计算剩下的 $0$ 和 $1$ 所能组成的序列个数。

再考虑 $T$ 序列，显然 $T$ 有 $C_{c+d+1}^{c}$ 种，隔板法直接得到该式子。

因为 $0\leq a,b,c,d\leq 2*10^3$。组合数可以直接递推得到就行了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int C[4030][4030];//
int ans=0;
int cc(int x,int y)
{
	if(x<1)return 1;
	if(x<y)return 0;
	return C[x][y];
}
void solve(int step,int a,int b,int c,int d,int ii)
{
//	int sum=0;
//	sum=C[c+d+1][c+1];
////	printf("step1=%lld  ",sum);
//	sum=sum*C[a-c+b-d+1][a-c+1];
////	printf("step2=%lld  ",sum);	
//	sum=sum%mod;
//	sum=sum*(a-c+b-d+1)%mod;
////	printf("step3=%lld\n",sum);	
//	sum=sum%mod;
//	ans+=(sum*step)%mod;
//	ans=ans%mod;
//	step=-step;
//	a-=c;
//	b-=d;
//	if(a>=c&&b>=d)
//	{
//		solve(step,a,b,c,d,ii++);
//	}
//	else
//	{
//		int sum2=0;
//		sum2=C[a+c+1][c+1];
//		sum2*=C[a+c+2][1];
//		sum2=sum2%mod;
//		sum2*=C[c+d+1][c+1];
//		sum2=sum2%mod;
//		ans-=sum2;
//		ans=(ans+mod)%mod;
//	}
	for(int i=0;i<=a-c;i++)
	{
		for(int j=0;j<=b-d;j++)
		{
			ans+=(((cc(i+d,d)*cc(j+c,c))%mod)*cc(a+b-c-d-i-j+1,a-c-i+1))%mod;
			ans=ans%mod;
		}
	}
	if(ans==0)ans=1;
	ans=ans*cc(c+d+1,c+1);
	ans=ans%mod;
}
void init()
{
	C[1][1]=1;
	for(int i=2;i<=4020;i++)
	{
		for(int j=1;j<=i;j++)
		{
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			C[i][j]=C[i][j]%mod;
		}
	}
}
signed main()
{
	init();
	int a,b,c,d;	
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	solve(1,a,b,c,d,1);
	printf("%lld",ans);
	return 0;
}
```

---

