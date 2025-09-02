# Wilbur and Array

## 题目描述

小猪威尔伯又在试图修复数组了。他有一个数组 a[1],a[2],...,a[n] 最初由 n 个0组成。第一步，他可以选择任何一个下标 i 并让其下标之后的所有元素 a[i],a[i+1],...,a[n] 加1，或者减1。他的目标是得到数组 b[1],b[2],...,b[n]。
当然，威尔伯希望使用最少的步数挑战这个目标，并要求你计算这个值。

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
5```

## 样例 #2

### 输入

```
4
1 2 2 1
```

### 输出

```
3```

# 题解

## 作者：wanggk (赞：4)

[CF596B](https://www.luogu.com.cn/problem/CF596B)

### 题意

给定长度均为 $n$ 的初始数组 $a$ 和目标数组 $b$，其中 $a_1,a_2,...,a_n$ 初始均为 $0$。每一次操作，选择一个下标 $i$，并让 $a_i,...,a_n$ 均加上或减去 $1$。求最少的操作次数。

$1\leq n \leq 2\times10^5$，$-10^9 \leq b_i \leq 10^9$。

### 分析

我们观察到每次选择的是 $a$ 数组的**后缀**加上或减去 $1$，也就是说每次操作并不会影响前面的数值。

所以想要总的操作次数最少，就**从前往后满足 $b[i]$ 的条件**。 也就是说先将 $a[1]$ 达到 $b[1]$ 的值，再依次往后满足。这样可以保证每一次操作都不浪费（这个地方需要感性理解一下）。

-----

没懂的话举个例子（可以跳过不看）：

假设输入的 $b$ 数组为 $1,4,2,8,5,7$。下面来改变 $a$ 数组的值：

$0,0,0,0,0,0$ ——已操作次数： $0$  //操作前均为 $0$ 

$1,1,1,1,1,1$ ——已操作次数： $1$ //选择下标 $1$ ，进行加一操作 $1$ 次，满足 $b[1]$ 的要求

$1,4,4,4,4,4$ ——已操作次数： $4$  //选择下标 $2$ ，进行加一操作 $3$ 次，满足 $b[2]$ 的要求

$1,4,2,2,2,2$ ——已操作次数： $6$  //选择下标 $3$ ，进行减一操作 $2$ 次，满足 $b[3]$ 的要求

$1,4,2,8,8,8$ ——已操作次数： $12$ //选择下标 $4$ ，进行加一操作 $6$ 次，满足 $b[4]$ 的要求

$1,4,2,8,5,5$ ——已操作次数： $15$ //选择下标 $5$ ，进行减一操作 $3$ 次，满足 $b[5]$ 的要求

$1,4,2,8,5,7$ ——已操作次数： $17$ //选择下标 $6$ ，进行加一操作 $2$ 次，满足 $b[6]$ 的要求

总操作次数：$17$ 

---

### 简洁的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans=0;
long long a[200005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) ans+=abs(a[i]-a[i-1]);
	printf("%lld",ans); 
	return 0;
}
```

---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF596B)
# 题意
有长度为 $n$ 的个数组 $a$ 和 $b$，最开始整个 $a$ 数组的值都是 $0$，给定数组 $b$。每次操作可以将 $a_i,a_{i+1},...,a_n$ 都加 $1$ 或减 $1$。求最少操作次数。
# 思路
我们可以使用贪心来解决。

因为每次操作都只影响 $a_i,a_{i+1},...,a_n$ 的值，所以对前面的数值都没有影响。那么就可以从头开始依次进行操作满足 $a_i=b_i$。对于每一个 $b_i$ 操作的次数为 $\lvert b_i-b_{i-1}\lvert$。所以答案为所有 $\lvert b_i-b_{i-1}\lvert$ 的和。
# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
int b[200005];
signed main()
{
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) scanf("%lld",b+i);
	for (int i=1;i<=n;i++) ans+=abs(b[i]-b[i-1]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：mc_xiexie (赞：2)

## CF596B Wilbur and Array
### 大意
一个数组 $a$ 最初由 $n$ 个 $0$ 组成。第一步，他可以选择任何一个下标 $i$ 并让其下标之后的所有元素加 $1$，或者减 $1$。他的目标是使数组 $a$ 变成数组 $b$。 使用最少的步数挑战这个目标，并要求你计算这个值。

### 思路
1. 直接大模拟
```
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
long long ans=0;
int main(){
    int n;int b;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b;
        if(a[i]>b){
            ans+=a[i]-b;
            for(int j=n;j>=i;j--){
                a[j]-=(a[i]-b);
            }
        }
        else if(a[i]<b){
            ans+=b-a[i];
            for(int j=n;j>=i;j--){
                a[j]+=b-a[i];
            }
        }
    }
    cout<<ans;
}
```
$O(n^2)$ 的复杂度，#11 TLE。

2. 压复杂度

我们可以发现，从左往右完成操作，右边的数等于左边的数。

例如：

```
1 2 3 4 5

```
运算过程：
```
0 0 0 0 0
1 1 1 1 1
1 2 2 2 2
1 2 3 3 3
1 2 3 4 4
1 2 3 4 5
```
就可以发现，运算第 $i$ 个中，$a_i$ 右边的值会等于 $a_i$。

可以写出 $O(n)$ 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
long long ans=0;
int main(){
    int n;int b;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b;
        ans+=abs(a[i]-b);
        if(a[i]>b){
        	a[i]-=a[i]-b;
		}
		else if(a[i]<b){
			a[i]+=b-a[i];
		}
        a[i+1]=a[i];
    }
    cout<<ans;
}
```
3. 不用数组

我们又可以发现，给 $a_i$ 变成 $b_i$ 不如直接用 $b_i$。这样可以少一个赋值。
```
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
long long ans=0;
int main(){
    int n;int b;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b;
        ans+=abs(a[i]-b);
        a[i+1]=b;
    }
    cout<<ans;
}
```
又可以发现，我们给 $a_{i+1}$ 赋值，不如用一个变量存 $b_i$。这时我们就可以发现，不需要数组了。
```

#include<bits/stdc++.h>
using namespace std;
long long a;
long long ans=0;
int main(){
    int n;int b;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b;
        ans+=abs(a-b);
        a=b;
    }
    cout<<ans;
}
```

---

## 作者：Tjl0427 (赞：1)

# 题解：CF596B Wilbur and Array
[题目链接。](https://www.luogu.com.cn/problem/CF596B)
### 题意：
给两个长度为 $n$ 的初始化和 目标数组 $b$ 。其中：$a$ 数组中的每个元素初始值都为 $0$，$b$ 数组中的数字要输入。  
对数组 $a$ 的一次操作为从下标为 $i$ 的 $a$ 数组中往后每个元素加 $1$ 或减 $1$。  
求：最少操作次数使得数组 $a$ 等于数组 $b$。
### 思路：
推理可得：最少操作次数是数组 $a$ 的当前位与后面一位的差的绝对值。  
#### 证明：
设这两个数组分别为 $a$ 和 $b$，长度均为 $n$，$b$ 中的每个元素分别为 $b_1,b_2,...,b_n$，从 $a$ 到 $b$ 的最少次数要看 $a_i$ 到 $b_i$ 要多少步，因为每次操作不影响第 $i$ 位之前的数字，所以最少步骤取从前往后的操作方法。  
从 $a_i$ 到 $b_i$ 要操作 $| a_i - b_i |$ 次，因为不能保证 $a_i$ 和 $b_i$ 的大小，所以要加绝对值。

例如：
```c
1 5 3 6
```
运算过程：
```c
0 0 0 0
1 1 1 1 //1
1 2 2 2 //2
1 3 3 3 //3
1 4 4 4 //4
1 5 5 5 //5
1 5 4 4 //6
1 5 3 3 //7
1 5 3 4 //8
1 5 3 5 //9
1 5 3 6 //10
```
结果：$10$。
### 代码：
```c
//当然可以不用数组做了。
#include<bits/stdc++.h>
using namespace std;
long long a,ans=0,n,b;
int main()
{
    scanf("%lld",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&b);
        ans+=abs(a-b);
        a=b;
    }
    cout<<ans<<endl;
    return 0;
}
```
完美结束！

---

## 作者：Fleeing_loser (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF596B)

简单贪心。
## 题意

求一个起始全为 $0$ 的数列 $a_1,a_2 \cdots a_n$ 每次可以选择一个数 $i$ 使 $a_i \cdots a_n$ 都加上或减去 $1$，求修改成给定的序列 $b_1,b_2 \cdots b_n$ 所需要的最小修改次数是多少。

## 思路
不难发现，直接从左向右贪心修改，到第 $i$ 个数的时候，前 $i-1$ 个数已经是最优状态了，这样修改之后的结果就是最小修改次数，即 $\left\vert b_i-a_i\right\vert$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lc k<<1
#define rc k<<1|1
#define re register
const int N=2e5+10,mod=998244353;
int read() 
{
	int x;
	scanf("%d",&x);
	return x; 
}
void prt(ll x,int op)
{
	if(op==1) cout<<x<<" ";
	if(op==2) cout<<x<<"\n"; 
}
int a[N],b[N],n;
ll ans;
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		b[i]=read();
	}
	int t=0;
	for(int i=1;i<=n;++i)
	{
		if(t!=b[i])
		{
			int x=b[i]-t;
			ans+=abs(b[i]-t);
			t+=x;
		}
	}
	prt(ans,2);
	return 0;
}
```


---

