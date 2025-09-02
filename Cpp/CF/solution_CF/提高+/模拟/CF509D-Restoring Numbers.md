# Restoring Numbers

## 题目描述

给你一个n*m的矩阵v。
    v[i][j]=(a[i]+b[j])%k;
    求a,b数组及其模数k。

## 样例 #1

### 输入

```
2 3
1 2 3
2 3 4
```

### 输出

```
YES
1000000007
0 1 
1 2 3 ```

## 样例 #2

### 输入

```
2 2
1 2
2 0
```

### 输出

```
YES
3
0 1 
1 2 ```

## 样例 #3

### 输入

```
2 2
1 2
2 1
```

### 输出

```
NO
```

# 题解

## 作者：distjr_ (赞：0)

## 题目描述

给你一个 $n \times m$ 的矩阵 $v$。

$v_{i, j} = (a_i + b_j) \bmod{k}$。

求两个序列及其模数 $k$。

## 思路

注意到，如果我们将 $a$ 序列中的所有数加上一，$b$ 序列中的所有数减去一，整个矩阵不会改变。

因此我们不妨设 $a_1 = 0$，通过第一列推出 $b$ 序列的值，进而推出 $a$ 序列的值。现在我们为每个格子 $(i, j)$ 计算一个误差 $error = a_i + b_j - v_{i, j}$。

如果所有的误差均为 $0$，则已经找到了一个满足条件的矩阵。否则意味着误差一定是 $k$ 的倍数，即 $k$ 一定是所有误差的公因数。另外 $k$ 还必须大于所有 $v$ 矩阵中出现的数。如果满足这两个条件则有解，否则无解。

## 代码

```cpp
/**
 * @file CF509D.cpp
 * @author distjr_
 * @brief Solution of CF509D
 */
#include <cstdio>
#include <cstdlib>
#define MAXN 105
#define int long long
// #define DEBUG
using namespace std;

int n, m, v[MAXN][MAXN], a[MAXN], b[MAXN], error, k = 0;
bool flag = true;
int (*gcd)(int, int) = [](int a, int b)
{ return ((b == 0) ? a : gcd(b, a % b)); };


signed main()
{
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%lld", &v[i][j]);
    for (int i = 1; i <= m; ++i)
        b[i] = v[1][i];
    for (int i = 1; i <= n; ++i)
        a[i] = v[i][1] - b[1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            error = abs(a[i] + b[j] - v[i][j]), k = gcd(k, error);
    if (!k)  // k为0，故最后所有的误差值都是0，直接给k赋值为1e9+7即可
        k = 1000000007;
    for (int i = 1; i <= n && flag; ++i)
        for (int j = 1; j <= m; ++j)
            if (v[i][j] >= k)
            {
                flag = false;
                break;
            }
    if (!flag)
    {
        printf("NO\n");
        return 0;
    }
    printf("YES\n%lld\n", k);
    for (int i = 1; i <= n; ++i)
        printf("%lld ", (a[i] + k) % k);
    printf("\n");
    for (int i = 1; i <= m; ++i)
        printf("%lld ", (b[i] + k) % k);
    printf("\n");
    return 0;
}
```

以上。如有问题烦请指出，谢谢。

---

## 作者：skyskyCCC (赞：0)

## 前言。
本题的第一篇题解。

比较好玩的题为什么没有人写题解呢？显而易见，本题要求出三个变量，并且每个测试点可以有多个不同的答案，所以我们大胆猜想这是一道构造题。
## 分析。
我们观察样例，发现输出的 $a_0$ 均等于 $0$ 所以我们不妨从这里下手。注意到，如果存在解的话，那么显然 $a_i$ 和 $b_j$ 可以任意转换，因为我们所要求的无非就是 $a_i+b_j$ 那么肯定有 $\left(a_i-p\right)+\left(b_j+p\right)=a_i+b_j$ 存在，所以只要存在符合条件的值，则 $a_i$ 可以取任意值，那么我们可以设 $a_0=0$ 则根据题意我们就可以推出其它的任意一个 $a_i$ 的可能取值。相应的，我们也可以求出 $b_j$ 的取值。所以我们现在已经把 $a$ 和 $b$ 的问题解决了。

接下来考虑 $k$ 的存在性问题。根据 $w_{i,j}=\left(a_i+b_j\right)\bmod k$ 我们可以得知，如果我们设 $e_{i,j}=\lvert a_i+b_j-w_{i,j}\rvert$ 的话，那么必然有 $e_{i,j}=0$ 时，符合条件，此时可以推出 $e_{i,h}$ 一定使得 $e_{i,j}\bmod k=0$。这一步就是简单地移项，应该不需要赘述。所以我们可以求出所有的 $e_{i,j}$ 然后两两求最大公因数，这样才能保证我们求出的这个数一定能够整除所有的 $e_{i,j}$。然后我们会得到一个最大公因数。根据题目的限制，我们不难发现，这个数正好就是 $k$ 的取值。然后分类讨论：

如果求出来的这个数是 $0$ 那么意味着正好前面都能被整除，即第一个数就是 $0$。为了保证对于矩阵中的每一个数都保持原来的样子，直接找到 $w_{i,j}$ 中的最大值 然后加上 $1$ 即可。此时整个矩阵不受影响，所以此时 $k$ 存在。如果不是 $0$ 那么我们就直接去看是不是大于任意一个 $w_{i,j}$ 即可。因为如果一旦小于其中的任意一个，都会导致我们已经计算出的这个矩阵改变，此时不存在。

注意到 $k$ 的分析其实牵扯到 $a$ 中，在预处理时会有负数的情况。代码直接这么顺下来即可，不是很难写。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m;
long long sum,k,pd;
long long a[205],b[205],w[205][205],e[205][205];
long long gcd(long long x,long long y){
    if(y>0){
	    return gcd(y,x%y);
	}
	else return x;
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>w[i][j];
        }
    }
    a[0]=0;
    for(int i=0;i<m;i++){
        b[i]=w[0][i]-a[0];
    }
    for(int i=1;i<n;i++){
        a[i]=w[i][0]-b[0];
    }
    sum=a[0]+b[0]-w[0][0];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            e[i][j]=abs(a[i]+b[j]-w[i][j]);
            sum=gcd(sum,e[i][j]);
        }
    }
	if(sum!=0){
		for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
            	if(sum<=w[i][j]){
					pd=1;
               		break;
            	}
        	}
    	}
    	if(pd){
    		cout<<"NO\n";
    		return 0;
		}
		k=sum;
	}
	else{
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                k=max(k,w[i][j]+1);
            }
        }
    }
    cout<<"YES\n"<<k<<"\n";
    for(int i=0;i<n;i++){
        if(a[i]<0){
            cout<<w[i][0]-b[0]+k<<" ";
            //cout<<w[i][0]<<" "<<b[i]<<" yep\n";
        }
        else cout<<a[i]<<" ";
    }
    cout<<"\n";
    for(int i=0 ;i<m;i++){
        cout<<b[i]<<" ";
    }
    return 0;
}
```
## 后记。
可能是打入门赛的原因吧，最近在数据范围上更细心了。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：dyt_dirt (赞：0)

# CF509D Restoring Numbers

[题目传送门](https://www.luogu.com.cn/problem/CF509D)

## 题目大意

给你一个 $n \times m$ 的矩阵 $v$；

有 $v_{i,j} = (a_i + b_j) \bmod k$；

求 $a$，$b$ 数组及其模数 $k$。

## 大致思路


### 一 计算题中数组
首先令 $a_0$ 为 $0$（原理很好想，如果 $a$ 中数组所有元素都减去一个数，$b$ 中数组都加上同一个数，那么最后算出来的 $v$ 是一样的）

有了 $a_0$，我们可以继而计算出整个 $a$ 和 $b$。

### 二 模拟 $v$ 数组

得出 $a$ 和 $b$ 之后，还缺一个模数 $k$，那么 $k$ 该如何求出呢?

如果将 $a$ 和 $b$ 按照题中所给方法计算得到 $v$， 会发现其实和数据给的 $v$ 不一定相同，那么就有两种情况。

#### 第一种情况
这个 $v$ 压根没有解，这时候直接输出 ```NO``` 就可以了。

#### 第二种情况

由于模数 $k$ 的存在，我们还得考虑计算模数。

初始时，将 $k$ 设为 $0$，这样在计算可能的 $k$ 时就可以取不同的部分做差，不难发现，最终的模数 $k$ 一定是这个差的绝对值的整数倍（此处请读者自证）

由于 Special Judge 的存在，我们可以直接算出所有差值之间的最大公因数，最后得到 $k$ 的答案。

细心的读者可能会发现，此时得到的 $k$ 有可能会小于题目所给的 $v$ 数组中的最大值，这时候就需要我们进行额外判断了。

如果 $k$ 经过计算后仍然为 $0$ ，就说明计算得出的数组和题中数组是一样的，这时候将 $k$ 赋值为 $v$ 一个比数组中最大值还大的数即可。

如果 $k$ 不为 $0$ 且小于等于数组中最大的元素，就说明这个数据不可能有解，直接输出 ```NO``` 即可。

## 代码


```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int Max = -1;
int n, m;
int k;
int a[101], b[101];
int v[101][101];
int v2[101][101];

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> v[i][j];
            Max = max(Max, v[i][j]);
            if (i == 1)
                b[j] = v[i][j];
            if (j == 1)
                a[i] = v[i][j] - b[j];
          	  // 根据题目来求a和b
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            v2[i][j] = a[i] + b[j];
            if (v[i][j] != v2[i][j])
                k = __gcd(k, abs(v2[i][j] - v[i][j])); // 计算差值, 同时与现存的k取最大公因数
        }

    if (k && k <= Max) // 不存在对应的k
    {
        cout << "NO" << endl;
        return 0;
    }
    else
        cout << "YES" << endl;

    if (k == 0)
        k = Max + 1;

    cout << k << endl;

    for (int i = 1; i <= n; i++)
    {
        if (a[i] < 0)
            a[i] = a[i] + k * ((0 - a[i]) / k + 1);
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= m; i++)
    {
        if (b[i] < 0)
            b[i] = b[i] + k * ((0 - b[i]) / k + 1);
        cout << b[i] << " ";
    }
}
```

---

