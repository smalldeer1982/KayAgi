# Everything Everywhere All But One

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . After you watched the amazing film "Everything Everywhere All At Once", you came up with the following operation.

In one operation, you choose $ n-1 $ elements of the array and replace each of them with their arithmetic mean (which doesn't have to be an integer). For example, from the array $ [1, 2, 3, 1] $ we can get the array $ [2, 2, 2, 1] $ , if we choose the first three elements, or we can get the array $ [\frac{4}{3}, \frac{4}{3}, 3, \frac{4}{3}] $ , if we choose all elements except the third.

Is it possible to make all elements of the array equal by performing a finite number of such operations?

## 说明/提示

In the first test case, all elements are already equal.

In the second test case, you can choose all elements except the third, their average is $ \frac{1 + 2 + 4 + 5}{4} = 3 $ , so the array will become $ [3, 3, 3, 3, 3] $ .

It's possible to show that it's impossible to make all elements equal in the third and fourth test cases.

## 样例 #1

### 输入

```
4
3
42 42 42
5
1 2 3 4 5
4
4 3 2 1
3
24 2 22```

### 输出

```
YES
YES
NO
NO```

# 题解

## 作者：Qerucy (赞：2)

题目大意：

定义一次操作：在 $a$ 数组里面选择 $n-1$ 个元素，把这 $n-1$ 个元素改成它们的平均值，问是否有可能使数组的所有元素通过执行有限数量的这样的操作相等。

一道贪心题

枚举每个元素，判断除这个元素之外的其它元素的平均值是否等于这个元素，如果有一个元素满足这种要求，则输出 `YES` ，然后继续下一组测试样例。

如果在枚举了所有元素之后还找不到满足条件的数之后就输出 `NO` ，因为如果没有这样的元素，一直分下去所有元素只会无限接近，而达不到相等的要求。

```cpp
#include<cstdio>

using namespace std;

int t,n;
double a[210];
double sum;

int main(){
	scanf("%d",&t);
	
	while(t--){
		
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++){
			scanf("%lf",&a[i]);
		}
		
		bool fg=0;
		
		for(int i=1;i<=n;i++){
			sum=0;
			for(int j=1;j<=n;j++){
				if(i==j) continue;
				sum+=a[j];
			}
			if(sum/(n-1)==a[i]){
				fg=1;
				break;
			}
		}
		
		puts(fg?"YES":"NO");
		
	}
	return 0;
}
```

有一种优化的方法，在算平均数的时候，我们可以把 $a$ 序列的总和算出来，在枚举到 $a_i$ 时就判断 总和 $-$ $a_i$ 再除以 $(n-1)$ 是否等于 $a_i$ 即可。

```cpp
#include<cstdio>

using namespace std;

int t,n;
double a[210];
double sum;

int main(){
	scanf("%d",&t);
	
	while(t--){
		
		sum=0;
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++){
			scanf("%lf",&a[i]);
			sum+=a[i];
		}
		
		bool fg=0;
		
		for(int i=1;i<=n;i++){
			if((sum-a[i])/(n-1)==a[i]){
				fg=1;
				break;
			}
		}
		
		puts(fg?"YES":"NO");
		
	}
	return 0;
}
```

~~好像代码跑得更慢了~~

---

## 作者：ningago (赞：1)

## 题意

给定 $n$ 个数，每次操作可以选择除一个数外的 $n-1$ 个数，使它们变成它们的平均数。

问若干次操作后能否让 $n$ 个数相等。

## 题解

令数列的元素为 $a_i(i \in [1,n])$，总和为 $\text{sum}$。

#### 性质1

操作后数列的和不变。

#### 证明（易证）

设操作了除 $a_x$ 外的 $n-1$ 个数，则操作后的和为：

$$\dfrac{\text{sum}-a_x}{n-1}\times(n-1)+a_x=\text{sum}$$

#### 性质2

对同一个数进行 $x\geq 1$ 次操作和 $y\geq 1$ 次操作没有区别。

#### 证明（易证）

由定义可得，操作后改变为的平均数是相同且确定的，所以做任意 $\geq2$ 次操作都和做 $1$ 次没有本质区别。

#### 性质3

如果答案为 ``YES``，那么至多只需要一次本质不同的操作。

#### 证明

由「性质1」可得，令最终答案序列中的所有数为平均数 $k=\dfrac{\text{sum}}{n}$，即序列为 $\{k,k,k\cdots k\}$ 。

假设这个序列是由对下标 $x$ 进行操作得到的，那么上一次操作的序列为 $b_1,b_2 \cdots b_x\cdots b_n$，其中 $b_x=k$ ，$\sum b_i = \text{sum} - k$ 。

如果现在这个序列是由另一个下标 $y$ 操作得到的，那么当 $y\ne x$ 时，根据操作的定义有 $b_i(i\ne y)=b_x=k$，$b_y = \text{sum} - (n - 1) \times k = k$，回到了最初全为 $k$ 的序列。

当 $y=x$ 时，根据定义 $b_i(i\ne x(y))$ 都相等，为 $\dfrac{\text{sum}-k}{n-1}=k$。还是回到了全为 $k$ 的序列。

由此可以证明，如果一个序列需要 $p\geq2$ 次操作完成，那么它是在对同一个数进行操作，根据「性质2」，得证。

#### 求解

现在我们知道要是能成功那么只需一次操作。

根据定义，在对 $a_x$ 操作后 $a_x$ 是不变的，并且因为操作后就全相同了，那么必须满足 $a_x=k$。

由此，只需判断序列中有没有任意的元素 $=k$ 即可。

## Code：

```cpp
#include <cstdio>

int T,n;
int a[100];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int sum = 0;
		for(int i = 1;i <= n;i++)
		{
			scanf("%d",&a[i]);
			sum += a[i];
		}
		if(sum % n)
		{
			printf("NO\n");
			continue;
		}
		bool flag = 0;
		for(int i = 1;i <= n;i++)
		{
			if(sum / n == a[i])
				flag = 1;
		}
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：1)

这道题是一道思维+结论题。

如果有一个数 $a[i]$ 乘上数字个数等于这些数字的总和，那么其余 $n-1$ 个数相加就等于 $n-a[i]$，平均数值就是 $a[i]$。经过操作，就可以让所有数字等于 $a[i]$，满足要求。反之则不行。

### 所以，如果有一个数 $a[i]$ 乘上数字个数等于这些数字的总和，即可输出YES，否则输出NO。

还有，本题是多测，输出要求换行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[55],sum;
bool flag;
int main(){
    scanf("%d",&t);
    while(t--){
        sum=0;
        flag=false;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        for(int i=1;i<=n;i++){
            if(sum==a[i]*n){
                printf("YES\n");
                flag=true;
                break;//注意！只能输出一次YES。
            }
        }
        if(flag==false){
            printf("NO\n");
        }
    }
}
```


---

## 作者：云裳 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1686A)

**思路**

对于这道题，我们要抓住不变量，也就是**序列值之和**。

知道序列值之和后，就可以求出要将这个序列变成全一样的数字。

但是，这个数字有两个局限：


- 这个数字必须存在于序列中。

无论怎样变换，这个序列最终会变成 $ a,b,b,b,b,\cdots $ 的形式。

如果 $ b $ 是等于 $ a $ ,也就是平均值存在于序列中，就可以完成变换，不然怎样变换都会变成 $ a,b,b,b,b,\cdots $ 的形式。

- 这个数字必须为整数

题目中虽然说了，变换的平均值不一定要是整数，但是仔细想想，这个序列中的数全是整数，如果平均值不是整数，也就无法完成存在于序列中的规定了。


------------

有了以上思路，代码就变得很容易了！

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define INF 0x7fffffff
typedef long long ll;
using namespace std;
ll read() {//快读
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
void write(ll x) {//快写
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void write_kong(ll x) {//空格快写
	write(x);
	cout<<" ";
}
void write_endl(ll x) {//换行快写
	write(x);
	cout<<"\n";
}
int main() {
	ll t=read();//t组数据 
	while(t--) {
		ll n=read(),sum=0,a[maxn];
		bool flag=0;//先假设 
		for(ll i=1; i<=n; i++) a[i]=read(),sum+=a[i];//边读入边求出总和 
		if(sum%n==0) {//总和是n的倍数，也就相同于判断平均值是否为整数 
			for(ll i=1; i<=n; i++) {//循环判断平均值是否存在于序列中 
				if(a[i]==(sum/n)) {//如果存在 
					flag=1;//标记为存在 
					puts("YES");//直接输出成功 
					break;//退出循环 
				}
			}
		}
		if(!flag) puts("no");//如果不存在，输出不存在 
	}
	return 0;
}
```

---

## 作者：sgl654321 (赞：0)

### 题目大意
- 有一个由 $n$ 个正整数构成的数组。
- 你可以从中选择任何 $n-1$ 个数求平均值（并不保证平均值为整数），并覆盖原数组。
- 请问是否可以通过有限数量个操作，使得数组中的所有元素都相等？
### 解题思路
首先容易得到，若干次操作，其实就相当于一次操作。

然后，我们对求平均值这个操作进行数学语言转化：对 $n-1$ 个数进行求平均值，就是一个数保持不变，其他数求平均值。

令不变的这个数为 $a_k$，则一次操作就是 $a_i\gets \dfrac{\sum a_i-a_k}{n-1}$。只需要让这个数等于 $a_k$，所有元素就都相等了。

~~小学数学老师告诉我们，~~ 一定要尽量避免除法运算，因为会有可怕的精度误差。所以我们把除法改成乘法：若 $\sum a_i-a_k=a_k\times (n-1)$，即 $a_k\times n=\sum a_i$，则所有元素都相等。

于是解法就呼之欲出了：先预处理 $\sum a_i$，然后遍历数组，套入刚刚的~~公式~~，如果相等直接输出 ```YES``` 并结束程序。如果最后仍然没有输出 ```YES```，则输出 ```NO```。

### 参考代码
本题有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[100],sum;
bool flag;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		sum=0;
		flag=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];sum+=a[i];
		}
		for(int i=1;i<=n;i++)
			if(sum-a[i]==a[i]*(n-1)){
				cout<<"YES"<<endl;flag=1;break;
			}
		if(!flag)cout<<"NO"<<endl;
		
	}
	return 0;
} 
```
[AC 记录](https://www.luogu.com.cn/record/76686130)

[原题传送门](https://www.luogu.com.cn/problem/CF1686A)

---

## 作者：windflower (赞：0)

简要题意：
>给定一个序列 $a_n$，记一次操作为任取其中 $n-1$ 个数将其变成它们的平均值，是否能通过有限次操作使序列中所有数相等。

首先，进行一次操作后，序列必定是 $a,b,b,b,b,\cdots$ 的形式，若是有 $a\neq b$ 此时若对 a 进行操作则序列不变，若对 b 进行操作则序列变为 $b,\frac{(n-2)b+a}{n-1},\frac{(n-2)b+a}{n-1},\frac{(n-2)b+a}{n-1},\cdots$ 显然 $b\neq\frac{(n-2)b+a}{n-1}$ 则又变回了之前的形式。因此，若要满足题意，则只能是第一次操作后有 $a=b$，即初始序列中存在一个数是其它数的平均数。  
思路理清后代码实现就很容易辣

附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[233],sum=0,flag;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		sum=flag=0;
		for(int i=0;i<n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		for(int i=0;i<n;i++)
			if(a[i]*n==sum)flag=1;
		if(flag)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV19Y411u7Gy)

### 2 思路

首先我们可以发现，无论怎么操作，数组的总和都是不变的，那么最终变到的数肯定就是平均数。

然后，我们发现，当完成一次操作后，数组必定有 $n-1$ 位完全一致；而剩下一位如果和这一致，可以输出 `YES`；如果不一致，那么不可能再操作了，因为无论怎么操作都会变成 $n-1$ 个数一致但和剩下一个不一样的情况。

那么，剩下的那一个数必须是这个数组的平均数。

也就是说，有解当且仅当数组中存在一个数是这个数组的平均数。

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
int a[52];
int s;
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1686A_1.in","r",stdin);
	freopen("CF1686A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		s=0;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			s+=a[i];
		}
		ans=false;
		for(int i=1;i<=n;++i){
			if(a[i]*n==s){
				ans=true;
				break;
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76577534)

By **dengziyue**

---

## 作者：Kevin0007 (赞：0)

分析：

如果经过一次操作还不能让所有元素相等，那么无论经过多少次操作都不会让所有元素相等。

为什么呢？

如果经过一次操作还不能让所有元素都相等，那么就会出现 $n-1$ 个 $a$ 和 $1$ 个 $b(a\neq b)$。然后无论怎么操作，这 $n$ 个元素都可以表示为 $n-1$ 个相同的数字和 $1$ 个不同的数字，永远不能让它们相等。

那么，如何判定一次操作后可以让所有元素都相等呢？

遍历，只有中间有一个数是所有 $n$ 个数的平均数，那么将另外的 $n-1$ 个数进行一次操作即可。反之，如果没有任何一个数是所有 $n$ 个数的平均数，那么经过一次操作不能让所有元素相等，那么无论经过多少次操作都不会让所有元素相等。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[55],sum;
bool flag;
int main(){
  cin>>T;
  while(T--){
    sum=0;flag=1;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
    for(int i=1;i<=n;i++)
      if(sum==n*a[i]){
        cout<<"YES"<<endl;
        flag=0;
        break;
      }
      if(flag) cout<<"NO"<<endl;
  }
  return 0;
}
```


---

## 作者：zyl1543130456 (赞：0)

## 题目大意

有  $ t $ 组数据，每组数据有 $ n $ 个数，你需要选择 $ n - 1 $ 个数将这几个数都变为变成它们的平均数（不必是整数），能否使得这 $ n $ 个数在经过操作后相等。

## 解题思路

显然，在操作的前后数据的和是不变的。因此要使得操作后的每个数都相等，那一定是将所有数都变为和的平均数。由于只能将 $ n - 1 $ 个数变为对方的平均值，所以如果最后全部数都相等，那么剩下的那个数( $ n - 1  $ 之外的数)一定是总和的平均值，那么只需要判断一下该值是否出现过即可。

## 代码

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;
const int N=110;
bool v[N];
int t,n,sum,a;
int main(){
	scanf("%d",&t);
	while(t--){
		sum=0;
		memset(v,0,sizeof v);
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a);
			sum+=a;
			v[a]=1;
		}
		if(sum%n) printf("NO\n");
		else{
			if(v[sum/n]) printf("YES\n");
			else printf("NO\n");
		}
	}
}
```

---

## 作者：fast_photon (赞：0)

**0. 前言**  
挺好的一道[思维题](https://www.luogu.com.cn/problem/solution/CF1686A)，想清楚了没啥实现难度。  

**1. 题意**  
给定一个具有 $n$ 个元素的数组 $a$，每次可以选定 $n-1$ 个数改为原来的平均值，执行有限此操作后是否能使这 $n$ 个数两两相同。  
平均值的定义是 $\frac{\sum_{i=1}^n a_i}{n}$。  

**2. 分析**  
这题乍一看挺吓人的。但是我们细想会发现，一次操作之后有 $n-1$ 个数都一样了。假设一样的 $n-1$ 个是 $x$，不一样的一个是 $y$。那么这 $n$ 个数的平均数一定是 $\frac{x(n-1)+y}{n}$，而 $y=\frac{(n-1)y+y}{n},x=\frac{(n-1)x+x}{n}$，所以平均数既不是 $x$ 也不是 $y$ ，就不能让所有元素都一样。  
那这有什么用呢？  
无论这次操作选择哪 $n-1$ 个，都会回到这个情况自身。  
所以如果有一个数等于整体的平均数，那么就可以。  
反之，操作一次 $x$ 一定不等于 $y$，不可以，输出 `NO`。  

**3. 代码**  
这题除了思维难度以外的部分非常适合练习萌新基础语法。知道怎么写了就不要往下看了。  
```cpp
#include<cstdio>
#define maxn 55

using namespace std;

int t, n, a[maxn];

int main() {
    scanf("%d", &t);
    while(t--) {
        int sum = 0, flag = 0; //这里如果写全局变量记得每次清零
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        for(int i = 0; i < n; i++) {
            if(sum == a[i] * n) {
                printf("YES\n");
                flag = 1;
                break;//很重要，因为可以只输出一次YES
            }
        }
        if(!flag) printf("NO\n");
    }
}
```

---

