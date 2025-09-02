# 题目信息

# Array Reodering

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Let's call a pair of indices $ i $ , $ j $ good if $ 1 \le i < j \le n $ and $ \gcd(a_i, 2a_j) > 1 $ (where $ \gcd(x, y) $ is the greatest common divisor of $ x $ and $ y $ ).

Find the maximum number of good index pairs if you can reorder the array $ a $ in an arbitrary way.

## 说明/提示

In the first example, the array elements can be rearranged as follows: $ [6, 3, 5, 3] $ .

In the third example, the array elements can be rearranged as follows: $ [4, 4, 2, 1, 1] $ .

## 样例 #1

### 输入

```
3
4
3 6 5 3
2
1 7
5
1 4 2 4 1```

### 输出

```
4
0
9```

# AI分析结果

### 题目内容翻译
给定一个由 $n$ 个整数组成的数组 $a$。

定义一对下标 $i, j$ 为“好对”，如果 $1 \le i < j \le n$ 且 $\gcd(a_i, 2a_j) > 1$（其中 $\gcd(x, y)$ 是 $x$ 和 $y$ 的最大公约数）。

求在可以任意重排数组 $a$ 的情况下，最大可能的“好对”数量。

### 算法分类
贪心

### 题解分析与结论
所有题解的核心思路都是通过贪心策略，将偶数放在数组的前面，奇数放在后面，从而最大化“好对”的数量。具体来说，偶数与任何数（无论是偶数还是奇数）相乘后都会变成偶数，因此偶数与任何数的 $\gcd$ 都会大于 1。而奇数与奇数的 $\gcd$ 不一定大于 1，因此将奇数放在后面可以减少不必要的计算。

### 所选高星题解
#### 题解1：作者：住在隔壁小莘 (赞：8)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，直接通过输入时判断奇偶性并分别处理，最后通过双重循环计算“好对”数量。
- **个人心得**：作者提到“偶数都排在奇数的前面”这一策略，并通过代码实现了这一思路，逻辑清晰。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[10010],ans,b[10010],num,num2;
int gcd(int a,int b)
{
    int n=a%b;
    while(n!=0)
    {
        a=b;
        b=n;
        n=a%b;
    }
        return b; 
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		num=0,num2=0,ans=0;
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>a[j];
			if(a[j]%2==0){
				num2++;
				ans+=n-num2;
			}else{
				num++;
				b[num]=a[j];
			}
		}
		sort(b+1,b+num+1);
		for(int j=1;j<=num;j++){
			for(int k=j+1;k<=num;k++){
				if(gcd(b[j],b[k])>1){
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
}
```

#### 题解2：作者：HerikoDeltana (赞：3)
- **星级**：4星
- **关键亮点**：通过将偶数和奇数分别放入不同的数组，最后合并并计算“好对”数量，代码结构清晰。
- **个人心得**：作者提到“数据太水了，这完全瞎搞的做法能过”，表明虽然方法简单，但在实际应用中有效。

```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define Romano 1
#define S signed
#define U unsigned
#define LL long long
#define R register
#define I inline
#define D double
#define LD long double
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f = 1;
    char c = getchar();
    x = 0;
    while (c < '0' || c > '9') 
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') 
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x *= f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
LL gcd(LL x,LL y)
{
    Heriko ! y ? x : gcd(y,x%y);
}
LL t;
S main()
{
    fr(t);
    while(t--)
    {
        LL n,a[2001],b[2001],hd=0,tl,ans=0;
        fr(n);
        tl=n+1;
        for(R LL i=1;i<=n;++i) fr(a[i]);
        for(R LL i=1;i<=n;++i)
        {
            if(a[i]&1) b[--tl]=a[i];
            else b[++hd]=a[i];
        }
        for(R LL i=1;i<=n;++i)
            for(R LL j=i+1;j<=n;j++)
                if(gcd(b[i],b[j]*2)!=1) ans++;
        fw(ans);
    }
    Heriko Deltana;
}
```

#### 题解3：作者：StayAlone (赞：3)
- **星级**：4星
- **关键亮点**：通过将偶数和奇数分别放入不同的数组，最后合并并计算“好对”数量，代码结构清晰。
- **个人心得**：作者提到“时间复杂度 $O(n^2 \log a_i)$”，表明虽然方法简单，但在实际应用中有效。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[2010], b[2010], idx, cnt;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n); idx = 1, cnt = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i)
			if (a[i] % 2 == 0) b[idx++] = a[i];
		for (int i = 1; i <= n; ++i)
			if (a[i] % 2) b[idx++] = a[i];
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (gcd(b[i], 2 * b[j]) > 1) cnt++;
		printf("%d\n", cnt);
	}
	return 0;
}
```

### 最优关键思路
将偶数放在数组的前面，奇数放在后面，从而最大化“好对”的数量。这种方法利用了偶数的性质，即偶数与任何数的 $\gcd$ 都会大于 1，从而减少了不必要的计算。

### 可拓展之处
类似的问题可以通过分析数的性质（如奇偶性、质数等）来优化算法。例如，在处理与 $\gcd$ 相关的问题时，可以考虑数的奇偶性、质因数分解等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：56.03秒