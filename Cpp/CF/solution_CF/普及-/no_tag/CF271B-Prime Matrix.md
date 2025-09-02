# Prime Matrix

## 题目描述

You've got an $ n×m $ matrix. The matrix consists of integers. In one move, you can apply a single transformation to the matrix: choose an arbitrary element of the matrix and increase it by $ 1 $ . Each element can be increased an arbitrary number of times.

You are really curious about prime numbers. Let us remind you that a prime number is a positive integer that has exactly two distinct positive integer divisors: itself and number one. For example, numbers 2, 3, 5 are prime and numbers 1, 4, 6 are not.

A matrix is prime if at least one of the two following conditions fulfills:

- the matrix has a row with prime numbers only;
- the matrix has a column with prime numbers only;

Your task is to count the minimum number of moves needed to get a prime matrix from the one you've got.

## 说明/提示

In the first sample you need to increase number 1 in cell (1, 1). Thus, the first row will consist of prime numbers: 2, 2, 3.

In the second sample you need to increase number 8 in cell (1, 2) three times. Thus, the second column will consist of prime numbers: 11, 2.

In the third sample you don't have to do anything as the second column already consists of prime numbers: 3, 2.

## 样例 #1

### 输入

```
3 3
1 2 3
5 6 1
4 4 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
4 8 8
9 2 9
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2 2
1 3
4 2
```

### 输出

```
0
```

# 题解

## 作者：agicy (赞：2)

享受最佳阅读体验请进入[传送门](https://lu-anlai.github.io/2019/02/03/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91%E3%80%90Codeforces-271B%E3%80%91-Prime-Matrix/)。

## 原题

题面请查看[Codeforces 271B Prime Matrix](http://codeforces.com/problemset/problem/271/B)。

也可在洛谷上查看：[传送门](https://www.luogu.org/problemnew/show/CF271B)。

## 题解

埃氏筛

### 思路

1. 用埃氏筛求出$1$~$10^{5}+3$以内的所有素数；

2. 求出矩阵内每个元素变为素数的操作次数；

3. 为最后统计方便，记`a[i][0]`为第$i$行的操作总数，`a[0][j]`为第$j$列的操作总数；

4. 统计答案。

#### 细节

$10^5$经过操作后的素数是$100003$，所以埃氏筛要筛到$100003$。

### 代码

```cpp
#include <cstdio>
#define INF 0X3F3F3F3F3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))
//头文件，正无穷，函数min()

bool isNotPrime[100004];//埃氏筛的标记数组
int n, m, a[501][501];

int main(void)
{
    register int i, j;
    register long long now, temp, ans = INF;
    scanf("%d%d", &n, &m);//读入n,m

    /*----埃氏筛----*/
    isNotPrime[1] = true;
    for (i = 2; i <= 100003; ++i) {
        if (!isNotPrime[i])
            for (j = (i << 1); j <= 100003; j += i)
                isNotPrime[j] = true;
    }

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);//先读入
            now = temp = a[i][j];
            while (isNotPrime[now])
                ++now;
            //寻找最近的素数now
            a[i][j] = now - temp;//求操作次数
            a[i][0] += a[i][j];
            a[0][j] += a[i][j];
            //为方便统计，记a[i][0]为第i行的操作总数，a[0][j]为第j列的操作总数
        }
    for (i = 1; i <= n; ++i)
        ans = min(ans, a[i][0]);
    for (j = 1; j <= m; ++j)
        ans = min(ans, a[0][j]);//统计
    printf("%lld\n", ans);//输出并换行
    return 0;
}
```

### 我的评测记录

- [Codeforces](http://codeforces.com/contest/271/submission/49398471)；

- [洛谷](https://www.luogu.org/recordnew/show/16053322)。


---

## 作者：LYqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF271B)

# 题目大意

给定一个 $n \times m$ 的由整数构成的矩阵，每次操作可以将一个数 $+1$，求将任意一行或一列的数全变为质数的最小操作次数。

$1 \le n,m \le 500,1 \le a_{i,j} \le 10^5$ 。

# 思路

首先使用欧拉筛把质数都筛出来，为了保险，直接筛 $1 \sim 2 \times 10^5$。

对于 $a_{i,j}(1 \le i \le n,1 \le j \le m)$，暴力计算出操作多少次可以变为质数。

最后跑两次二维循环计算行、列操作总和，取 $\min$ 即可。

# 代码

```cpp
#include <iostream>
using namespace std;
template<typename T=int>
inline T read(){
    T X=0; bool flag=1; char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+(ch^48),ch=getchar();
    if(flag) return X;
    return ~(X-1);
}

const int N=5e2+5,M=2e5+5;
int n,m,sum,ans=0x3f3f3f3f;
int a[N][N],f[N][N];
int prime[M],isprime[M];

// 欧拉筛
template<typename T=int>
int getprime(T n){
    int cnt=0;
    for(int i=1; i<=n; i++) isprime[i]=1;
    isprime[1]=0;
    for(int i=2; i<=n; i++){
        if(isprime[i]) prime[++cnt]=i;
        for(int j=1; j<=cnt && prime[j]*i<=n; j++){
            isprime[i*prime[j]]=0;
            if(i%prime[j]==0) break;
        }
    }
    return cnt;
}

int main(){
    n=read(),m=read();
    getprime(2e5);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            for(a[i][j]=read(); !isprime[a[i][j]+f[i][j]]; f[i][j]++);
            /* 这一句相当于：
            a[i][j]=read();
            while(!isprime[a[i][j]])
                a[i][j]++,f[i][j]++;
            */
    // 每列
    for(int i=1; i<=n; i++,ans=min(ans,sum),sum=0) // 直接把取 min 和重置写到循环里
        for(int j=1; j<=m; j++)
            sum+=f[i][j];
    // 每行
    for(int i=1; i<=m; i++,ans=min(ans,sum),sum=0)
        for(int j=1; j<=n; j++)
            sum+=f[j][i]; // 注意这里 j 和 i 要反过来，i 是行数
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Dream_weavers (赞：0)

## 思路

用欧拉筛筛出 $1$ 至 $2\times10^5$ 的素数（实际是到 $10^5$，保险筛到 $2\times10^5$），然后暴力矩阵内每个数的操作次数，就是找到距离这个数最近的素数再做差。用 $h_i$ 记录第 $i$ 行操作次数和，$l_j$ 记录 第 $j$ 列的操作次数和。最后找 $n$ 行、$m$ 列中最小的操作次数和。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+100;
const int INF=2e9;
int book[N],prime[N],mp[N],ind;
int h[N],l[N]; 
int n,m,a,ans=INF;

void shai(){//欧拉筛
    book[1]=1;
    for(int i=2;i<=N-50;i++){
        if(!book[i]) prime[++ind]=i;
        for(int j=1;j<=ind&&i*prime[j]<=N-50;j++){
            book[i*prime[j]]=1;
            if(!i%prime[j]) break;
        }
    }
    for(int i=1;i<=ind;i++) mp[prime[i]]=1;
}

signed main(){
	shai();
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&a);
			int tot=a;
			while(!mp[tot])tot++;//找最近的素数
			h[i]+=tot-a;//记录操作次数和
			l[j]+=tot-a;
		}
	}
	for(int i=1;i<=n;i++)ans=min(ans,h[i]);//找最小值
	for(int i=1;i<=m;i++)ans=min(ans,l[i]);
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：WangBng (赞：0)

前置芝士：线性筛

$10^5$ 经过操作后是 $100003$ ，用线性筛筛出 $1\sim100003$ 范围内的质数。

线性筛中会有一个数组 $a$ ， $a_i=1$ 表示 $i$ 是合数，反之亦然。

对于一个数 $x$ ，设 $tos=x$ ， $tos$ 一直往上加，直到 $a_{tos}=0$ 为止，操作次数即为 $tos-x$ 。

接下来统计答案即可。

Code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100008],b[60005],r,num[505][505],tos[505][505];
void shai(int n){
	a[0]=a[1]=1;
	for(int i=2;i<=n;i++){
		if(!a[i]){
			b[++r]=i;
		}
		for(int j=1;j<=r&&i*b[j]<=n;j++){
			a[i*b[j]]=1;
			if(i%b[j]==0){
				break;
			}
		}
	}
}
int main(){
	shai(100003);
	int n,m,x,ans=1e9,tot=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>num[i][j];
			x=num[i][j];
			while(a[x]){
				x++;
			}
			tos[i][j]=x-num[i][j];
		} 
	}
	for(int i=1;i<=n;i++){
		tot=0;
		for(int j=1;j<=m;j++){
			tot+=tos[i][j];
		}
		ans=min(ans,tot);
	}
	for(int i=1;i<=m;i++){
		tot=0;
		for(int j=1;j<=n;j++){
			tot+=tos[j][i];
		}
		ans=min(ans,tot);
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：q_sum (赞：0)

蒟蒻又来水CF的题了。

这道题可以用素数筛+暴力枚举解决。

前面一个素数筛，判断一个数是否为素数。

中间一个循环，判断对于一个整数$i$，大于且最接近于$i$的素数，将每个这样的素数记录到$b$数组中。

后面依次枚举每行和每列，对于每个数，无需再去重复计算大于且最接近于这个数的素数，直接调用$b[i]$即可。

下面，放代码吧，小编在做此题的时候也犯了一些低级错误，我会在代码里指出来：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[101001];
int b[101001],c[501][501],tmp,s,mn=INT_MAX;
int main()
{
	for (int i=2;i<=sqrt(101000);++i)
	   for (int j=i;j<=101000/i;++j)
	      a[i*j]=true;//素数筛部分，这里小编犯了第一处错误，应该开到101000，否则统计99991以上素数的时候就会变成0
	b[0]=b[1]=2;//小编犯了第二处错误，0和1以上最小的素数是2
	for (int i=101000;i>=2;--i)//小编犯了第三处错误，应该倒着循环，否则找的是小于i且最大的素数
	{
		if(!a[i])
		  tmp=i;//如果这个数是素数，那么先把tmp替换成这个数，以便赋值给下面的数
		b[i]=tmp;
	}
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=n;++i)
	   for (int j=1;j<=m;++j)
	      cin>>c[i][j];
	for (int i=1;i<=n;++i)
	{
		s=0;//累加器赋值为0
	   for (int j=1;j<=m;++j)
	      s+=b[c[i][j]]-c[i][j];//无需往上计算，这样最坏情况的时间复杂度就从O(n*n*100000)到了O(n*n),大大减少了时间消耗
	    if(s<mn)
	      mn=s;//如果这一行（一列)全部变成素数的步数小于现有的最小值，那么就替换
    }
    for (int i=1;i<=m;++i)
	{
		s=0;
	   for (int j=1;j<=n;++j)
	      s+=b[c[j][i]]-c[j][i];//同理，注意这里要先j再i，前面i循环做到m，j循环做到n
	    if(s<mn)
	      mn=s;
    }
    cout<<mn;//输出答案
	return 0;
}
```
附带：不要抄代码

---

