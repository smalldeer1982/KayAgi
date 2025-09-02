# Robin Hood and the Major Oak

## 题目描述

在 Sherwood（原文地名）里，树木是我们的庇护所，我们都是森林的孩子。

Sherwood 中的 Major Oak（原文物品名称）以它宏伟的树叶而闻名，这些树叶为 Robin Hood（原文人名）和他的快乐男男女女们提供了庇护。

Major Oak 在 $i$ 年长出 $i^i$ 片新叶子。它从第一年开始就有 $1$ 片叶子。

树叶在树上最多能持续 $k$ 年。换句话说，第 $i$ 年长出的树叶可以持续到第 $i$ 年到第 $i+k-1$ 年。

这段文本的意思是：Robin 认为偶数是幸运的。请帮助 Robin 确定 Major Oak 在第 $n$ 年是否有偶数片叶子。

## 说明/提示

在第一个测试用例中，只有 $ 1 $ 片叶子。

在第二个测试用例中，$ k=1 $ ，所以第 $ 2 $ 年会有 $ 2^2=4 $ 片叶子。

在第三个测试用例中，$ k=2 $ ，所以第 $ 2 $ 年会有 $ 1+2^2=5 $ 片叶子。

在第四个测试用例中，$ k=2 $ ，所以第 $ 3 $ 年会有 $ 2^2 + 3^3 = 4 + 27 = 31 $ 片叶子。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
5
1 1
2 1
2 2
3 2
4 4```

### 输出

```
NO
YES
NO
NO
YES```

# 题解

## 作者：hema5177 (赞：2)

### 思路

易证对一个数进行幂运算其奇偶性不变。

计算第 n-k 到 n 有多少个奇数即可。

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		long long n,k;
		cin>>n>>k;
		if(n%2==0)
		{
			k/=2;
			if(k%2==0) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
		else
		{
			if(k%2!=0) k=k/2+1;//如果n是奇数且k是奇数，则奇数的个数必然比偶数大一
			else k/=2;
			if(k%2==0) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
}
```

---

## 作者：Program_A2 (赞：1)

## 思路：
可以证明，奇数的幂运算结果一定为奇数，偶数的幂运算结果一定为偶数，所以本题不要管幂运算内容。所以本题本质上是 $n-k+1$ 到 $n$ 的等差数列。

---
## 代码

```
#define I return
#define AK 0
#define IOI ;
#include "bits/stdc++.h"
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n,k;
		cin>>n>>k;
		if((((n-k+1)+n)*k)/2%2){      //见上文
			cout<<"No\n";
		}else{
			cout<<"Yes\n";
		}
	}
    I AK IOI
}
```

---

## 作者：cly312 (赞：1)

容易观察到：如果 $i$ 为奇数，那么 $i^i$ 也为奇数。如果 $i$ 为偶数，那么 $i^i$ 也为偶数。我们只需要统计从 $n-k+1$ 到 $n$ 中奇数的个数即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool check(int n, int k) {
    long long cnt=0;
    int i=n-k+1;
    if(i%2==0) i++;
    if(n%2==0) n--;
    cnt=(n-i)/2+1;
    return cnt%2==0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (check(n, k)) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
```

---

## 作者：OIer6666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2014B)

## 解题思路：
从 $n-k+1$ 枚举至 $n$ 可以吗？
 
不可以，如果直接算幂，会爆 `long long`！

那就换一个思路。

若 $i\bmod 2=0$，那么 $i^i\bmod 2=0$；若 $i\bmod 2=1$，那么 $i^i\bmod 2=1$。

题目要求判断奇偶性，所以可以变成一个 $n-k+1$ 至 $n-k$ 的等差数列，利用求和公式，就能判断是奇数还是偶数了。

## 代码：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define int long long
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		cout<<((n-k+1+n)*k/2%2?"nO\n":"yES\n");
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

简单题。

[题目传送门](https://www.luogu.com.cn/problem/CF2014B)

### 思路

容易发现，只有 $n - k$ 到 $n$ 对答案有影响，由于奇数的平方还是奇数，偶数的平方也还是偶数，所以可证明 $i^i$ 与 $i$ 的奇偶性相同，那么就是说可把 $i^i$ 转换为 $i$，那么也就是说求 $n - k$ 到 $n$ 的和是否为偶数，那么由于奇数加偶数等于奇数，所以可以先求出有多少个奇数与有多少个偶数，再分下列条件判断：

- 一、如果刚好奇偶数量相等，说明刚好组完，由于偶数个奇数的和为偶数，看奇数个数的奇偶性即可。

- 二、如果奇偶数量不相等，此时如果奇数多于偶数，那么多出来的那个就又组成了一个奇数，看奇数数量加一的奇偶性即可；反之，如果奇数少于偶数，那么如果奇数数量为奇数，那么奇数乘奇数加偶数为奇数，不行，如果奇数数量为偶数，那么奇数乘偶数加偶数为偶数，可以。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,sj,so;
int main(){
	cin >> t;
    while (t --)
    {
    	cin >> n >> k;
		if (n % 2 == 1)
		{
			if(k % 2 == 1)
			{
				sj = k / 2 + 1;//当n，k为奇数时，有k/2+1个奇数
				so = k + 1 - sj;//用总数减奇数个数 
			}
			else
			{
				sj = k / 2;//当n为奇数，k为偶数时，有k/2个奇数
		        so = k + 1 - sj;//用总数减奇数个数 
			}      	
        }
        else
		{
			if(k % 2 == 1)
			{
				sj = k / 2;//当n为偶数，k为奇数时，有k/2个奇数
				so = k + 1 - sj;//用总数减奇数个数 
			}
			else
			{
				sj = k / 2;//当n，k为偶数时，有k/2个奇数
		        so = k + 1 - sj;//用总数减奇数个数 
			}
		} 
		if (sj == so)//条件1 
		{
			if (sj % 2 == 0)  cout << "YES\n";
			else  cout << "NO\n"; 
		}
		else//条件2 
		{
			if (sj > so)  
			{
				if ((sj + 1) % 2 == 0)  cout << "YES\n";
			    else  cout << "NO\n";
			}
			else
			{
				if (sj % 2 == 0)  cout << "YES\n";
			    else  cout << "NO\n"; 
			}
		}
    }
	return 0;
}
```

---

## 作者：_colin1112_ (赞：0)

## 思路

容易证明对任意一个数进行幂运算后，这个数的奇偶性不变。

所以这道题的题意就变为了计算 $n - k + 1$ 到 $n$ 的奇数个数。

奇数计算公式：$\left\lfloor \frac{b + 1}{2} \right\rfloor - \left\lfloor \frac{a}{2} \right\rfloor$。


## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--){
        ll n, k;
        cin >> n >> k;
        ll a = n - k + 1;
        if (a < 1)
            a = 1;
        ll b = n;
        ll cnt = ((b + 1) >> 1) - (a >> 1);
        if(cnt % 2 == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：jubaoyi2011 (赞：0)

## 思路

在做这题时，我们只考虑幂的结果的奇偶即可，我们已知 $n^n$ 的奇偶由 $i$ 本身的奇偶决定，若 $i$ 为奇数，则 $i^i$ 为奇数，反之亦然。有些不懂这个结论的小朋友就只能推导了：

首先我们可以知道： $i^i = i$ 个 $i$ 的乘积，而奇数个奇数相乘则必然得到奇数，偶数与任何数相乘则必然得到偶数，所以就可以得到上面的结论。

所以最终我们只需要统计从 $n - k + 1$ 到 $n$ 中所有奇数的个数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        long long sum=0;
        int i=n-k+1;
        if(i%2==0) i++;
        if(n%2==0) n--;
        sum=(n-i)/2+1;
        if (sum%2==0) {
            puts("YES");
        } 
        else {
            puts("NO");
        }
    }
}
```

---

## 作者：chatoudp (赞：0)

简化版题意：给定 $n$ 和 $k$，问 $n^n+{(n-1)}^{n-1}+\dots+{(n-k+2)}^{n-k+2}+{(n-k+1)}^{n-k+1}$ 是否为偶数。

因为 $i^i$ 的奇偶性与 $i$ 的奇偶性相同，因此问题可转变为：$n+(n-1)+\dots+(n-k+2)+(n-k+1)$ 的奇偶性。也就相当于问 $n-k+1$ 到 $n$ 之间的奇数个数是否是偶数个。

这就简单了。

若 $n$ 为奇数，则奇数个数为 $\lceil\frac{k}{2}\rceil$，否则奇数个数为 $\lfloor\frac{k}{2}\rfloor$。

看懂文字叙述的请自行完成代码。

AC 代码：

```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define itn int
#define Please int
#define AC main(){
#define pritnf printf
using namespace std;
typedef long long ll;
bool f;
int n,k;
Please AC//'_' T_T ^_^
	itn T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		if(n%2==1){
			if((int)ceil(k/2.0)%2==1) printf("nO\n");
			else printf("yEs\n");
		}else{
			if((k/2)%2==1) printf("No\n");
			else printf("yES\n");
		}
	}
	I AK IOI
}

```

---

## 作者：sea_bird (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2014B)。

# 题目分析

这道题太简单了，直接模拟就可以了，但是还是要说明一下思路，由于每个树叶都有时限所以循环的时候从未到时间的树叶那开始也就是 $n-k$，之后便算出和，减去多加的第一天后，判断输出即可。

## Code

```cpp
#include<bits/stdc++.h>

using namespace std;
long long t,n,k;
long long ans=0;
int main(){
	ios::sync_with_stdio(0);//在C++中关闭输入输出流的同步,提高程序的执行效率
	cin>>t;
	for(int i=1;i<=t;i++){	
		cin>>n>>k;
		for(int j=n-k+1;j<=n;j++){
			ans+=pow(j,j);
		}
		if(ans%2==0){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
		ans=0;
	}
	return 0;
}
```

但是如果看看数据量就会发现，这会爆 `long long`，所以不能才取这个方法，但我们可以找规律发现偶数个偶数相乘还是偶数，奇数个奇数相乘还是奇数，那么这道题可以被简化为**判断范围内有多少个奇数**就行了，上文提到忽略超时的树叶，所以可以用一个变量来存开始时间，接着用**求等差数列位数的公式**算出总共有多少个奇数，由于奇数加奇数等于偶数，所以如果奇数个数是奇数的话就不满足，否则满足。

```cpp
#include<bits/stdc++.h>

using namespace std;
long long t,n,k,x;
long long ans=0;
int main(){
	ios::sync_with_stdio(0);//在C++中关闭输入输出流的同步,提高程序的执行效率
	cin>>t;
	for(int i=1;i<=t;i++){	
		cin>>n>>k;
		x=n-k+1;
		cout<<x<<endl;
		if(x%2==0){
			x-=1;//从奇数开始 
			ans=(n-x)/2+1-1;//减去多算的奇数 
		}
		else{
			ans=(n-x)/2+1;
		}
		if(ans%2==0){ 
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
		
	}
	return 0;
}
```

关于这段代码我要说几句：
- 由于 [Codeforces RemoteJudge 暂不可用](https://www.luogu.com.cn/discuss/598533)。所以我暂时不能提交。
- 一定要开 `long long`。

---

## 作者：Super_Cube (赞：0)

# Solution

题意：$\displaystyle\sum_{i=n-k+1}^ni^i$ 的奇偶性。

注意到奇数的奇数次方为奇数，偶数的偶数次方为偶数，那么实际是 $\displaystyle\sum_{i=n-k+1}^ni$ 的奇偶性。而奇偶性只与奇数个数相关，且统计范围是一段连续整数，那么肯定是奇偶数交替出现，所以奇数个数为 $\left\lfloor\dfrac{k+(n\bmod 2)}{2}\right\rfloor$。

# Code

```cpp
#include<stdio.h>
int T,n,m;
int main(){
	scanf("%d",&T);
	while(T--)
		scanf("%d%d",&n,&m),
		puts((m+(n&1)>>1)&1?"NO":"YES");
	return 0;
}
```

---

## 作者：jiangyunuo (赞：0)

### 题意：
有一棵大树，这棵大树第 $i$ 年长出 $i^i$ 片叶子，每片叶子只能存在 $k$ 年（包括长出来的一年和凋谢的那一年）。  
问：$n$ 年后这棵树会不会有偶数片叶子。  
### 思路：
又是考验奇偶性的一道题。  
显然：奇数乘奇数得奇数，偶数乘偶数得偶数。因此当 $i$ 为奇数时，$i^i$ 为奇数，反之为偶数。  
实际上，求 $n$ 年后这棵树会不会有偶数片叶子与第 $n-k+1$ 年到第 $n$ 年的叶子数量有关，更具体来说，是与这 $k$ 年中奇数年的数量有关。  
不过还没完，我与大家的做法有一点不同，我不直接统计奇数年的数量，而是给这 $k$ 年分组。  
我们将这 $k$ 年分成 $4$ 年一组，接下来，我们取最后一组，前面的组必然是两奇两偶（指两个是奇数年两个是偶数年），对于答案没有影响，最后一组中奇数的数量可就有影响了，如果最后一组中奇数的数量是奇数，那么答案是 `NO` 反之答案是 `YES`。  
注意，当 $n$ 为奇数时，最后一组就有可能是：奇，奇偶，奇偶奇，奇偶奇偶。那么最后一组有三或四个数时，奇数就有偶数个。当 $n$ 为偶数时，最后一组就有可能是：偶，偶奇，偶奇偶，偶奇偶奇。那么最后一组有一或四个数时，奇数就有偶数个。
### 代码：

```cpp
#include<bits/stdc++.h>  
using namespace std;  
int main(){
    int t;
    cin>>t;  
    int n,k;
    for(int i=1;i<=t;i++){
        cin>>n>>k;
        if(n%2){
            if((n-(n-k+1)+1)%4==0||(n-(n-k+1)+1)%4==3)cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        else{
            if((n-(n-k+1)+1)%4==0||(n-(n-k+1)+1)%4==1)cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;  
}
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[原题](https://codeforces.com/problemset/problem/2014/B)

[洛谷](https://www.luogu.com.cn/problem/CF2014B)

### 题意简述
一颗树在第 $i$ 年长出 $i^i$ 新叶。它从 $1$ 年的 $1$ 叶开始，第 $i$ 年生长的叶子持续 $i$ 年至 $i+k-1$ 年（含第 $i+k-1$ 年）。你需要确定在第 $n$ 年的树（长完叶子后）会不会有偶数片叶子。

### 思路
首先考虑对于第 $p$ 年，长出的叶子为奇数还是偶数。

因此首先考虑 $p$ 为奇数的情况。$p^p$ 等于 $p$ 个 $p$ 相乘，因此只需验证奇数个奇数相乘的情况。不难发现奇数乘奇数一定是奇数。因为任何奇数的因子里没有 $2$，乘起来也绝不会出现因子为 $2$ 的数。所以 $p^p$ 为奇数，当 $p$ 为奇数时。

再考虑 $p$ 为偶数的情况。不难发现任何一个数 $x$ 在乘 $2$ 后一定是偶数，也就是说 $p$ 乘带有 $2$ 的因子的数一定为偶数。所以 $p^p$ 为偶数，当 $p$ 为偶数时。

考虑叶子从第 $i$ 年长出来到 $i+k-1$ 年消失，原题中说明包含第 $i+k-1$ 年，所以叶子会存在 $k$ 年。

那么现在只需求出以 $n$ 结尾的 $k$ 个连续整数和的奇偶性即可。

### 代码
```cpp
#include <iostream>
#define ll long long
using namespace std;

ll t;

ll n, k;

ll tmp;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        cin >> n >> k;

        tmp = n - k + 1;

        tmp += 1 - (tmp % 2),
            n -= 1 - (n % 2);

        if (((n - tmp) / 2 + 1) % 2 == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---

