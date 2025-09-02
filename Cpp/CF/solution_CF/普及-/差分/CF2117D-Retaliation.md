# Retaliation

## 题目描述

Yousef 想要使数组 $a_1, a_2,\dots, a_n$ 爆炸。当一个数组的所有元素均为 $0$ 时，它就会爆炸。

在一次操作中，Yousef 可以选择执行下列选项之一：

- 对 $a$ 中所有的下标 $i$，令 $a_i$ 自减 $i$。
- 对 $a$ 中所有的下标 $i$，令 $a_i$ 自减 $n-i+1$。

你的任务是帮助 Yousef 判断能否通过一系列操作使得数组爆炸。

## 说明/提示

对于第二个测试用例，我们可以进行如下操作：

- 进行 $1$ 次第一种操作，数组变为 $[20,16,12,8,4]$。
- 进行 $4$ 次第二种操作，数组变为 $[0,0,0,0,0]$。

对于第一、第三、第四、第六个测试用例，可以证明无法通过任何操作使得数组的元素全部变为零。

## 样例 #1

### 输入

```
6
4
3 6 6 3
5
21 18 15 12 9
10
2 6 10 2 5 5 1 2 4 10
7
10 2 16 12 8 20 4
2
52 101
2
10 2```

### 输出

```
NO
YES
NO
NO
YES
NO```

# 题解

## 作者：P2441M (赞：4)

## 题意

给定一个长度为 $n$ 的序列 $a$。你可以进行若干次操作，每次操作可以执行下面两种操作中的**恰好**一种：

1. 对于每个 $1\leq i\leq n$，令 $a_i\leftarrow a_i-i$。
2. 对于每个 $1\leq i\leq n$，令 $a_i\leftarrow a_i-(n-i+1)$。

判断是否可以通过若干次操作使得 $a$ 变为全 $0$。

多测。$1\leq T\leq 10^4$，$2\leq n\leq\sum{n}\leq 2\times 10^5$，$1\leq a_i\leq 10^9$。

## 题解

操作是全局减等差数列的形式，放到 $a$ 的差分数组 $d$ 上面考虑。那么两种操作变成：

1. 令 $d_1\leftarrow d_1-1$，然后对于每个 $2\leq i\leq n$，令 $d_i\leftarrow d_i-1$。
2. 令 $d_1\leftarrow d_1-n$，然后对于每个 $2\leq i\leq n$，令 $d_i\leftarrow d_i+1$。

显然 $d[2,n]$ 无论如何操作都只是在全局 $+1/-1$，所以要让 $a$ 能通过若干次操作变为全 $0$，首先要满足 $d_2=d_3=\cdots=d_n$。

接下来对 $d_2$ 的正负性做分类讨论：

- $d_2=0$：设我们做了操作 $1$ 和 $2$ 各 $x$ 次，则 $d_1=(n+1)x$，所以只需判断是否有 $(n+1)\mid d_1$。
- $d_2>0$：设我们做了操作 $2$ 共 $x$ 次，操作 $1$ 共 $x+d_2$ 次，则 $d_1=x+d_2+nx$，即 $d_1-d_2=(n+1)x$，所以只需判断是否有 $d_1\geq d_2\land (n+1)\mid(d_1-d_2)$。
- $d_2<0$，设我们做了操作 $1$ 共 $x$ 次，操作 $2$ 共 $x-d_2$ 次，则 $d_1=x+n(x-d_2)$，即 $d_1+nd_2=(n+1)x$，所以只需判断是否有 $d_1+nd_2\geq 0\land (n+1)\mid(d_1+nd_2)$。

时间复杂度 $\mathcal{O}(\sum{n})$。

## 代码

```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5;

int t, n;
ll a[N], d[N];

inline bool solve() {
	for (int i = 2; i < n; ++i) if (d[i] != d[i + 1]) return 0;
	if (!d[2]) return d[1] % (n + 1) == 0;
	if (d[2] > 0) return (d[1] - d[2] >= 0) && ((d[1] - d[2]) % (n + 1) == 0);
	return (d[1] + d[2] * n >= 0) && ((d[1] + d[2] * n) % (n + 1) == 0);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while (t--) {
    	cin >> n;
    	for (int i = 1; i <= n; ++i) cin >> a[i];
    	for (int i = 1; i <= n; ++i) d[i] = a[i] - a[i - 1];
    	cout << (solve() ? "YES\n" : "NO\n");
    }
    return 0;
}
```

---

## 作者：HBQS (赞：1)

这道题可以使用逆推法的思想，也就是假设现在有 n 个全为 0 的元素，通过一系列变换得到给出的数组。通过举例不难发现，进行操作一的时候：**对 $a$ 中所有的下标 $i$，令 $a_i$ 自减 $i$**。相邻元素之间的差值会逐渐加一。进行操作二的时候：**对 $a$ 中所有的下标 $i$，令 $a_i$ 自减 $n-i+1$**。相邻元素之间的差值会逐渐减一，如果这个数组是满足条件的，那么不难发现，通过这俩个操作得到的数组，相邻元素的差值必定相同。于是考虑使用差分数组。

我们发现，如果使用一次操作一再使用一次操作二，相邻元素只会增大 $n+1$ ，而相邻元素的差值不改变，于是得到这道题的思路：

如果差分数组中的元素不相同，直接输出 NO。如果相同，将原数组的每个元素减去通过操作产生的相邻元素的差值，最后检查这个数组能否被 $n+1$ 配平即可，注意判断，如果进行减法的过程中出现小于 0 的数，直接输出 NO。代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define endl '\n'
#define debug cout<<"*OK*"<<endl<<endl
#define el cout<<endl<<endl
#define forr(arr) for(auto&cand:arr)
#define inf 0x3f3f3f3f

const int N = 150;
void solve()
{
    int n;
    cin>>n;
    vector<int>arr(n),pre;
    forr(arr) cin>>cand;
    for(int i = 0;i<n-1;i++)
        pre.emplace_back(arr[i]-arr[i+1]);
    for(int i = 0;i<n-1;i++)
    {
        if(pre[i]!=pre[0])
        {
            cout<<"NO"<<endl;
            return ;
        }
    }
    int temp = pre[0];
    if(temp>=0)
    {
        for(int i = 0;i<n;i++)
        {
            arr[i]-=temp*(n-i);
            if(arr[i]%(n+1)!=0||arr[i]<0)
            {
                cout<<"NO"<<endl;
                return ;
            }
        }
        cout<<"YES"<<endl;
        return ;
    }
    else
    {
        for(int i = 0;i<n;i++)
        {
            arr[i]+=temp*(i+1);
            if(arr[i]%(n+1)!=0||arr[i]<0) 
            {
                cout<<"NO"<<endl;
                return ;
            }
        }
        cout<<"YES"<<endl;
        return ;
    }

}   

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while(T--)
        solve();
    return 0;
}    
/*Written By HBQS!*/
```
如有更好的解法，希望犇犇不吝赐教！

---

## 作者：copper_ingot (赞：1)

[洛谷](https://www.luogu.com.cn/problem/CF2117D)

[Codeforces](https://codeforces.com/problemset/problem/2117/D)

设进行了 $x$ 次操作一，$y$ 次操作二，$x$ 和 $y$ 均为自然数。

则可以根据题意列出二元一次方程：

$$\begin{cases}x+ny=a_1 \\ nx+y=a_n\end{cases}$$

得到 $x-y=\frac{a_n-a_1}{n-1}$。因为 $x$ 和 $y$ 均为自然数，所以 $x-y$ 是整数。令 $x-y=\frac{a_n-a_1}{n-1}=tmp$，若 $tmp$ 不是整数则无解。

则可以解得：

$$\begin{cases}y=\frac{a_1-tmp}{n+1} \\ x=\frac{a_1-tmp}{n+1}+tmp\end{cases}$$

两者中如果有任意一个不是自然数就无解。

然后将 $x$ 和 $y$ 代入每一个 $a_i$ 计算，如果 $a_i \neq ix+(n-i+1)y$ 就无解。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
int t, n, a[200001];
signed main(){
	scanf("%lld", &t);
	while (t--){
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		if ((a[n] - a[1]) % (n - 1)){puts("NO"); continue;}//判断tmp是否为整数
		int tmp = (a[n] - a[1]) / (n - 1);
		if ((a[1] - tmp) % (n + 1)){puts("NO"); continue;}//判断y是否为整数
		int y = (a[1] - tmp) / (n + 1), x = y + tmp, flag = 1;
		if (x < 0 || y < 0){puts("NO"); continue;}//判断x、y是否为非负数
		for (int i = 1; i <= n; i++)
			if (i * x + (n - i + 1) * y != a[i]){flag = 0; break;}//对每个a[i]检验
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
```

---

