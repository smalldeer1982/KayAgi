# Polycarpus the Safecracker

## 题目描述

Polycarpus has $ t $ safes. The password for each safe is a square matrix consisting of decimal digits '0' ... '9' (the sizes of passwords to the safes may vary). Alas, Polycarpus has forgotten all passwords, so now he has to restore them.

Polycarpus enjoys prime numbers, so when he chose the matrix passwords, he wrote a prime number in each row of each matrix. To his surprise, he found that all the matrices turned out to be symmetrical (that is, they remain the same after transposition). Now, years later, Polycarp was irritated to find out that he remembers only the prime numbers $ p_{i} $ , written in the first lines of the password matrices.

For each safe find the number of matrices which can be passwords to it.

The number of digits in $ p_{i} $ determines the number of rows and columns of the $ i $ -th matrix. One prime number can occur in several rows of the password matrix or in several matrices. The prime numbers that are written not in the first row of the matrix may have leading zeros.

## 说明/提示

Here is a possible password matrix for the second safe:

`<br></br>239<br></br>307<br></br>977<br></br>`Here is a possible password matrix for the fourth safe:

`<br></br>9001<br></br>0002<br></br>0002<br></br>1223 <br></br>`

## 样例 #1

### 输入

```
4
11
239
401
9001
```

### 输出

```
4
28
61
2834
```

# 题解

## 作者：loser_seele (赞：1)

首先预处理素数。

因为数据范围小，所以可以考虑枚举所有的矩阵对角线以上的所有情况。因为第一个数不超过五位数，所以对角线以上只会有 $ 6 $ 个元素，枚举的次数不会超过 $ 10^6 $ 次，可以接受。

然后对于每种情况没有确定的只有对角线，把每行对角线存在的可行解先算出来，最后乘起来，然后把所有情况的答案相加即为答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool prime[100000];
int s[10];
int ten[10] = {1, 10, 100, 1000, 10000, 100000};
int res;
int tenDiv[100000];
int tenMod[100000];
int tenMul[100000];
vector<int> ending2[100000];
vector<int> ending3[100000];
void init()
{
    memset(prime, 1, sizeof prime);
    prime[0] = 0;
    prime[1] = 0;
    for(int i = 0; i < 100000; i++)
    {
        tenDiv[i] = i / 10;
        tenMod[i] = i % 10;
        tenMul[i] = i * 10;
    }
    for(int i = 2; i < 100000; i++)
    {
        if(!prime[i]) 
        continue;
        for(int j = 2 * i; j < 100000; j += i)
        prime[j] = false;
    }//预处理素数
    for(int i = 0; i < 1000; i++)
        for(int j = 0; j < 100; j++)
        {
            if(prime[i * 100 + j])
                ending3[i].push_back(j);
            if(prime[j * 1000 + i])
                ending2[j].push_back(i);
        }//预处理合法方案
}
int a[10];
void rec(int cur, int n)
{
    if(cur == n)
    {
        res++;
        return;
    }
    int nu = s[cur - 1];
    for(int i = n - 1; i >= cur; i--)
    {
        a[i] = tenMul[ a[i] ] + tenMod[nu];
        nu = tenDiv[nu];
    }
    int k = a[cur];
    int T = ten[n - cur];
    int kT = k * T;
    if(n == 5 && cur == 2)
    {
        for(int i = 0; i < ending2[k].size(); i++)
        {
            int number = ending2[k][i];
            int num = number + kT;
            if(!prime[num]) 
            continue;
            s[cur] = num;
            rec(cur + 1, n);
        }
    }
    else if(n == 5 && cur == 3)
    {
        for(int i = 0; i < ending3[k].size(); i++)
        {
            int number = ending3[k][i];
            int num = number + kT;
            if(!prime[num]) 
            continue;
            s[cur] = num;
            rec(cur + 1, n);
        }
    }
    else
    {
        for(int number = 0; number < T; number++)
        {
            int num = number + kT;
            if(!prime[num]) 
            continue;
            s[cur] = num;
            rec(cur + 1, n);
        }
    }
    for(int i = n - 1; i >= cur; i--)
        a[i] = tenDiv[ a[i] ];//暴力枚举部分
}
int getLen(int num)
{
    int res = 0;
    while(num > 0)
    {
        res++;
        num /= 10;
    }
    return res;
}
void calc()
{
    a[0] = s[0];
    int n = getLen(s[0]);
    rec(1, n);
}//计算位数
int main()
{ 
    init();
    int n;
    scanf("%d", &n);
    int M = 0;
    for(int i = 0; i < n; i++)
    {
        memset(s, 0, sizeof s);
        memset(a, 0, sizeof a);//清空
        scanf("%d", &s[0]);
        res = 0;
        calc();
        printf("%d\n", res);
    }
}
```

---

