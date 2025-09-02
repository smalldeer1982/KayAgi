# ALICESIE - Alice Sieve

## 题目描述

Alice 最近学会了使用 Eratosthenes 筛法，这是一种古老的算法，用于找出小于某个上界的所有素数。正如预期的那样，她对这个算法的简洁和优雅感到非常印象深刻。

现在，她决定设计自己的筛法：Alice 筛法；在给定了某个上界 $N$ 的情况下的 Alice 筛法被形式化地定义为以下过程：

1. 创建一个从 $N$ 到 $2$ 的连续整数列表 $(N, N - 1, N - 2, \cdots, 3, 2)$。所有这 $N - 1$ 个数字最初都是未标记的。
2. 最初，让 $P$ 等于 $N$，并保持这个数字未标记。
3. 标记 $P$ 的所有正约数（即 $P$ 保持未标记）。
4. 从 $2$ 到 $P - 1$ 中找到最大的未标记数字，然后让 $P$ 等于这个数字。
5. 如果列表中不再有未标记的数字，则停止。否则，从第 $3$ 步开始重复。

不幸的是，Alice 还没有找到她的筛法的应用。但她仍然想知道，对于给定的上界 $N$，有多少整数会是未标记的。

## 样例 #1

### 输入

```
3
2
3
5```

### 输出

```
1
2
3```

# 题解

## 作者：Scrutiny (赞：3)


首先打表可知若输入为$n$（这里不再赘述打表过程），则答案是 $\left\lceil\dfrac{n}{2}\right\rceil$ 

下面是证明过程：

我们记 $a=\left\lceil\dfrac{n}{2}\right\rceil$ 

首先，显然$(p,p-1)=1$，故$p-1$到$2$中所有数中最大的还没有被标记的数$q=p-1$。

而筛法会在$p=2$时终止，故共筛$n-2$次。

而对于任意一个数$i$,它最大因子（不包括它自己）一定$\leq\frac{i}{2}$

因此，区间$(a,n]$中的整数是不可能被标记的。

另一方面，对于任意正整数$i∈[1,a)$，$2i$一定$∈[2,n]$，因此$i$一定被标记过。

若$n$为偶数，则$a$被标记过，此时答案为$n-a$，即$\frac{n}{2}$，也就是$a$。

否则答案为$n-a+1$，即$\frac{n+1}{2}$，也还是$a$。

综上我们知道答案为$a$。

### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long double n,t;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		cout<<ceil(n/2)<<endl;
	}
	return 0;
}
```

说明：

1.本题数据范围较小，无需用快读、快输。

~~2.要抄窝的题解请仔细看过证明过程后再抄。~~

---

## 作者：suzy0921 (赞：2)

题意很明显是算 $\lfloor\frac{n+1}{2}\rfloor$，而 $\frac{n+1}{2}$ 直接去掉余数，所以输出 ```(n+1)/2```。

上代码：
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long t,n;
    scanf("%lld",&t);
    while(t--){
        scanf("%lld",&n);
        printf("%lld\n",(n+1)/2);
    }
    return 0;
}
```

完结撒花。

---

## 作者：Yousa_Ling (赞：1)

观察样例，大胆猜测答案为 $\lfloor \frac{n+1}{2} \rfloor$。

证：

设被标记的数为 $a$，没被标记的数为 $b$。

$\because$ 一个非零自然数 $x$ 的真因子 $n \leq \frac{x}{2}$，

$\therefore 1 \leq a \leq \frac{x}{2}$。

又 $\because \frac{b}{2} \leq \frac{x}{2}$，

$\therefore \frac{b}{2}$ 一定被标记，

又 $\because$ C++除法自动向下取整，

$\therefore$ 答案为 $\lfloor \frac{n+1}{2} \rfloor$。


代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long T;
	cin>>T;
	for(long long i=0;i<T;i++){
		int n;
		cin>>n;
		cout<<(n+1)/2<<endl;
	}
	return 0;
}
```


---

## 作者：HsKr (赞：1)

找规律。

自己手玩几组试试。

```
n=2:

p=2
标记1
结束
////////
n=3:

p=3
标记1
p=2
标记1
结束
////////
n=4:

p=4
标记1,2
p=3
标记1
p=2
标记1
结束
////////
n=12:

p=12
标记1,2,3,4,6
p=11
标记1
p=10
标记1,2,5
p=9
标记1,3
p=8
标记1,2,4
p=7
标记1
结束
结束
```

可以发现，$x\in\left[1, \left\lfloor \frac{n}{2}\right\rfloor\right]$一定被标记过了，且一定它会在$p=2\times n$时会被标记（不保证只标记1次），然而$x\in\left[ \left\lfloor \frac{n}{2}+1\right\rfloor,n\right]$则因为没有它的倍数不会被标记，所以最终未标记的个数即为$\left\lceil \frac{n}{2}\right\rceil$。

代码象征性贴一下吧（其实不贴也能做出来了）：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int main(){
	int n,k;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>k;
		cout<<(k+1)/2<<endl;
	} 
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

由于一个数的真因子 $\ge 2$，所以一个数的真因子 $\le n/2$，所以一个数的真因子个数 $\le n/2$。由此得到被标记的数 $\in [1, n / 2]$，又因为没被标记的数 $\le n$，所以没被标记的数的一半都被标记了。所以答案为 $\lfloor (n + 1) / 2 \rfloor$。

---

## 作者：HUTEHE (赞：0)

### 方法1：模拟 Alice 筛法（TLE）

根据题意模拟即可（注意：真因数指不包括 $n$ 的所有 $n$​ 的因数）。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void solve() 
{
	int n;
	cin>>n;
    vector<bool>vis(n+1,false);//真因数
    int p=n;
    while(p>1) 
    {
        for(int i=1;i*i<=p;i++) //标记真因数
        {
            if(p%i==0) 
            {
                vis[i]=true;
                if(i!=1&&i!=p/i) 
                    vis[p/i]=true;
            }
        }
        int q=-1;
        for(int i=p-1;i>=2;i--) 
            if(!vis[i]) 
        	{
                q=i;//有被标记的数
                break;
            }
        if(q==-1)break; 
        p=q;//没有被标记的数
    }
    int count=0;//统计数量
    for(int i=2;i<=n;i++) 
    {
        if(!vis[i]) 
            count++;
    }
    cout<<count<<endl;
}
signed main() 
{
    int T;
    cin>>T;
    while(T--) 
        solve();
    return 0;
}

```

但是提交后发现 TLE 了，说明有一定的规律可循。

### 方法2：找规律（AC）

#### 题目要求：

1.  **创建序列**：从 $n$ 到 $2$ 的严格下降序列。
2.  **初始化**：令  $P=n$。
3.  **标记真因数**：标记 $P$ 的所有真因数（不包括 $P$ 本身）。
4.  **寻找下一个 P**：找到从 $P-1$ 到 $2$ 中最大的未被标记的数 $q$，令 $P = q$。
5.  **重复**：如果 $q$ 存在，重复步骤 $3$ 和 $4$，否则停止。

#### 关键：

1.  **标记真因数**：每次标记 $P$ 的真因数时 $P$ 本身不会被标记。
2.  **寻找下一个 P**：每次找到的 $P$ 都是当前未被标记的数中最大的一个。

#### 结果：

* $n$ 为偶数时：最后一次选 $P$ 时，$P$​ 正好处于 $\frac{n-2}{2}$。
* $n$ 为奇数时：最后一次选 $P$ 时，$P$ 正好处于 $\frac{n-2}{2}-1$。

#### 所以：

未被标记的数（即答案）则为 $\lfloor \frac{n+1}{2} \rfloor$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		cout<<floor((n+1)/2)<<endl;
	}
	return 0;
}
```

---

## 作者：Brute_Force (赞：0)

### 题意
分析：
- 输入数为 $2$，结果为 $1$，即 $\lfloor\frac {2+1}{2}\rfloor$。
- 输入数为 $3$，结果为 $2$，即 $\lfloor\frac {3+1}{2}\rfloor$。
- 输入数为 $5$，结果为 $3$，即 $\lfloor\frac {5+1}{2}\rfloor$。

接下来证明 `ans=(n+1)/2`：

假设被标记的数为 $m$，未被标记的数为 $n$。

因为正整数 $y$ 的真因子 $n \le \frac {1}{2} y$，

所以 $1 \le m \le \frac{1}{2}y$。

又因 $\frac{1}{2}n \le \frac{1}{2}y$，

所以 $\frac{1}{2}n \le \frac{1}{2}y$。

综上所述，可得答案就是将 $\lfloor\frac {n+1}{2}\rfloor$ 输出。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n,k;
    cin>>n;
    while(n--)
    {
        cin>>k;
        cout<<(k+1)/2<<'\n';
    }
}
```
### 感谢
@[zfw100](/user/797464)，提供了我论证思路。

---

## 作者：hanshengyuan2024 (赞：0)

### 分析：
将 $n$ 至 $2$ 之间所有 $n$ 的公因数标记，随后将 $n$ 的值 $-1$。重复执行若干次后，输出未被标记的数字的个数。
### 思路：
暴力枚举即可。
### Code：
现在给出代码。（别想着抄了，时间复杂度很高的）  
```cpp
#include <iostream>
using namespace std;
bool vis[数组范围];
int a[数组范围];
int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for (int i = n; i >= 2; ++i) {
			a[i] = i;
		} // 初始化
		for (int i = n; i >= 2; ++i) {
			for (int j = 2; j <= n; ++j) {
				if (n % j == 0) vis[j] = true; 
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i]) ans++;
		}
		cout << ans << endl;
	}
}
```

---

## 作者：zfw100 (赞：0)

# SP10565 ALICESIE - Alice Sieve 题解

## 题目分析

先观察样例：

- 输入 $2$，输出是 $1$，$1=\left\lfloor\dfrac{2+1}{2}\right\rfloor$。

- 输入 $3$，输出是 $2$，$2=\left\lfloor\dfrac{3+1}{2}\right\rfloor$。

- 输入 $5$，输出是 $3$，$3=\left\lfloor\dfrac{5+1}{2}\right\rfloor$。

大胆猜测：$ans = \left\lfloor\dfrac{n+1}{2}\right\rfloor$。

为了进一步确定这个公式是正确的，我们可以打表，此处过程省略，经打表发现此公式正确，在程序中使用 `cout<<(n+1)/2<<endl;` 即可，因为 c++ 具有自动向下取整功能。


### 证明
假设被标记的数为 $m$，未被标记的数为 $n$。

因为正整数 $x$ 的真因子 $n \le 0.5x$，

所以 $1\le m\le0.5x$。

又 $0.5n \le 0.5x$，

所以 $0.5n\le 0.5x$。

所以 $ans = \left\lfloor\dfrac{n+1}{2}\right\rfloor$。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	std::ios::sync_with_stdio(0);
	ll t,n;
	cin>>t;
	for(ll i=1;i<=t;i++){
		cin>>n;
		cout<<(n+1)/2<<endl;
	}
}

```


---

## 作者：zhangzihang (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/SP10565)

这道题乍一看没啥思路，先按照题意模拟，由于题目没给 $n$ 的范围，我用 map 容器处理。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> mp;
int cnt;
void f(int n){
	for(int i=2;i*i<=n;i++)
		if(n%i==0)
			cnt-=(mp[i]!=1),mp[i]=1;
}
int main(){
	int T;cin>>T;
	while(T--){
		int n;cin>>n;
		cnt=n-1;
		while(!mp[n]&&n>=2){
			f(n);
			n--;
		}
		cout<<cnt<<"\n";
		mp.clear();
	}
	return 0;
}
```

不出意外的 T 飞了。

然后随便扔几个数进去试一下，不难发现答案总是 $\left\lceil\dfrac{n}{2}\right\rceil$，输出 $\left\lceil\dfrac{n}{2}\right\rceil$ AC 了。

下面证明为什么答案总是 $\left\lceil\dfrac{n}{2}\right\rceil$。

方便起见，令 $t$ 为 $\left\lceil\dfrac{n}{2}\right\rceil$。

显而易见 $(p,p-1)=1$，所以 $q=p-1$，筛法一直到 $2$ 停止。

对于任意正整数 $n$ 它的最大真因子不超过 $t$。

所以从 $t+1$ 到 $n$ 的数是一定不会被标记的。

$t$ 是否被标记取决于 $n$ 的奇偶性，但是 $2(t-1)$ 严格小于 $n$ 所以不超过 $t-1$ 的数必然会被标记，所以筛法实际上到 $t$ 或者 $t-1$就停止了。

当 $n$ 为一个奇数时，$t$ 不会被标记，答案为 $n-t+1$ 就是 $t$，

当 $n$ 是一个偶数时，$t$ 会被标记，答案为 $n-t$ 也是 $t$。

故，最终答案必然为 $t$。

有任何问题欢迎私信提问。

---

## 作者：COsm0s (赞：0)

打表找规律，发现答案是 $\lfloor \dfrac{(n+1)}{2} \rfloor$。

但是，为什么是这个答案呢？


------------

证：

对于任何一个非零自然数 $x$，它的真因子 $\leq \frac{x}{2}$。

所以被标记的数 $y$ 一定满足 $1 \leq y \leq \frac{x}{2}$。

而对于没标记的数 $z$ 一定满足 $\frac{z}{2}$ 被标记，因为 $\frac{z}{2} \leq \frac{x}{2}$。

根据 c++ 自动向下取整的特性，则可以推出 $\lfloor \dfrac{(n+1)}{2} \rfloor$ 这个答案。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,t;//注意long long
	cin>>t;
	while(t--){
		cin>>n;
		cout<<(n+1)/2<<endl;//自动向下取整
	}
	return 0;
}
```


---

## 作者：Carolina (赞：0)

翻译：

Alice最近学习了[埃拉托色尼筛选法](https://baike.baidu.com/item/埃拉托色尼筛选法/4524938?fr=aladdin)，一个用于在任何给定范围内寻找素数的筛选算法。如同我们期望的那样，她被这个算法简洁优雅的气质深深地震惊了。

现在，Alice决定要自己设计一个算法模型，Alice筛法，正式定义其方法如下

1）确定要在n以内的数的限制中使用ALICE筛法（给出范围），创建一个包含了从n到2的所有整数的严格下降序列

2）在开始的时候，令p=n

3）在序列中标记p的所有真因数（不包括p，即不含n）

4）找到p-1到2中所有数中最大的还没有被标记的数q，令p=q

5）若q不存在，停止，否则从第3步开始继续重复。

Alice想要知道，对于每一个给定的N，筛法结束后序列中还有多少没有被标记的数。

输入格式：第一行是一个整数T，表示有T组数据。后面每一行都有一个给定的N。

输出：T行。每行是对于每一个N，没有被标记的数的数量。

分析：
我们可以先来推一个东西：对于每一个n，只有1~n/2（下取整）会被删（显然）
然后加入1，构成集合，删掉前面的数就可以。



```pascal
var
  n,i,m:longint;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(m);
    writeln(m-m shr 1);
  end;
end.
```

---

