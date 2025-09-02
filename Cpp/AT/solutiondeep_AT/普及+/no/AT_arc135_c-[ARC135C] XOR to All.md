# 题目信息

# [ARC135C] XOR to All

## 题目描述

给定 $n$ 个非负整数 $a_1,a_2,\dots,a_n$，你可以执行以下操作任意（可以为零）次：

- 选择一个数 $x\in \{a_1,a_2,\dots,a_n\}$。

- 对于所有 $a\leq i\leq n$，将 $a_i$ 修改为 $a_i\oplus x$，其中 $\oplus$ 表示按位异或操作。

请你最大化操作后 $\sum_{i=1}^na_i$ 的值。

## 说明/提示

- $1\leq n \leq 3\times 10^5$
- $0\leq a_i<2^{30}$

## 样例 #1

### 输入

```
5

1 2 3 4 5```

### 输出

```
19```

## 样例 #2

### 输入

```
5

10 10 10 10 10```

### 输出

```
50```

## 样例 #3

### 输入

```
5

3 1 4 1 5```

### 输出

```
18```

# AI分析结果

### 题目内容重写

给定 $n$ 个非负整数 $a_1,a_2,\dots,a_n$，你可以执行以下操作任意（可以为零）次：

- 选择一个数 $x\in \{a_1,a_2,\dots,a_n\}$。

- 对于所有 $1\leq i\leq n$，将 $a_i$ 修改为 $a_i\oplus x$，其中 $\oplus$ 表示按位异或操作。

请你最大化操作后 $\sum_{i=1}^na_i$ 的值。

### 算法分类
位运算

### 综合分析与结论

本题的核心在于通过异或操作最大化数组的和。通过分析可以发现，多次操作的效果会被最后一次操作抵消，因此最多只需要操作一次即可。具体思路是统计每个二进制位为1的个数，然后计算每个数作为操作数时对总和的贡献，最终取最大值。

### 所选题解

#### 题解1：作者：ran_qwq (赞：9)
- **星级**：5星
- **关键亮点**：清晰解释了多次操作的效果被抵消的原因，提供了详细的二进制位统计方法，代码简洁高效。
- **个人心得**：通过二进制位的统计和贡献计算，避免了复杂的操作，直接得出最优解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,ans,sum,a[N],b[N][32],c[32];
void solve()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),ans+=a[i],sum+=a[i];
		for(int j=0;j<30;j++)
			if(a[i]&(1<<j)) b[i][j]=1,c[j]++;
	}
	for(int i=1;i<=n;i++)
	{
		int tot=sum;
		for(int j=0;j<30;j++) tot+=b[i][j]*(n-c[j]*2)*(1<<j);
		ans=max(ans,tot);
	}
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}
```

#### 题解2：作者：Pretharp (赞：2)
- **星级**：4星
- **关键亮点**：通过模拟操作过程，验证了多次操作的效果被抵消，代码实现清晰。
- **个人心得**：通过模拟操作过程，直观地理解了问题的本质，代码实现简洁。

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define int long long
const int N=3e5+5,K=35;
int n,a[N],b[K][2],ans;
signed main()
{
	cin.tie(0),cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];
		for(int j=0;j<K-2;j++){
			b[j][1&(a[i]>>j)]++;
		}
	}
	for(int i=1,cnt;i<=n;i++){
		cnt=0;
		for(int j=0;j<K-2;j++){
			cnt+=(b[j][!(1&(a[i]>>j))]<<j);
		}
		ans=max(ans,cnt);
	}
	return cout<<ans<<endl,0;
}
```

#### 题解3：作者：cppcppcpp3 (赞：1)
- **星级**：4星
- **关键亮点**：通过数学推导验证了多次操作的效果被抵消，代码实现简洁。
- **个人心得**：通过数学推导，简化了问题的复杂度，代码实现高效。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=3e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,a[N],c[31],ans,p,q;
int b[N][31];

main(){
	n=wrd();
	for(int i=1;i<=n;++i) ans+=(a[i]=wrd());
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) for(int j=0;j<31;++j) if((a[i]>>j)&1) b[i][j]=1;
	
	for(int i=0;i<31;++i){
		for(int j=1;j<=n;++j) c[i]+=b[j][i];
	} 
	
	for(int i=1;i<=n;++i){
		int tot=0;
		for(int j=0;j<31;++j){
			if(b[i][j]) tot+=((n-c[j])*(1<<j));
			else tot+=(c[j]*(1<<j));
		} 
		ans=max(ans,tot);
	}
	
	return printf("%lld",ans),0;
}
```

### 最优关键思路或技巧
通过统计每个二进制位为1的个数，计算每个数作为操作数时对总和的贡献，最终取最大值。这种方法避免了复杂的操作，直接得出最优解。

### 可拓展之处
类似的问题可以通过二进制位的统计和贡献计算来解决，例如最大化或最小化某些位运算的结果。

### 推荐题目
1. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)
2. [P3865 【模板】ST表](https://www.luogu.com.cn/problem/P3865)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：44.06秒