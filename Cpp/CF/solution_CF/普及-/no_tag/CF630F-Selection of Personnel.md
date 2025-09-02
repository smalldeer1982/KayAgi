# Selection of Personnel

## 题目描述

One company of IT City decided to create a group of innovative developments consisting from $ 5 $ to $ 7 $ people and hire new employees for it. After placing an advertisment the company received $ n $ resumes. Now the HR department has to evaluate each possible group composition and select one of them. Your task is to count the number of variants of group composition to evaluate.

## 样例 #1

### 输入

```
7
```

### 输出

```
29```

# 题解

## 作者：封禁用户 (赞：3)

题目传送>>[CF630F](https://www.luogu.com.cn/problem/CF630F)  
### 题意简述：  
- $5$ - $7$ 人可组一个团队，现有 $n$ 人待招，求组团队方案数。  
- $7 \le n \le 777$。  
  
### 题目分析：  
$5$ - $7$ 人可组一个团队，即团队成员数可为 $5$ 或 $6$ 或 $7$，故我们把从 $n$ 人中分别挑 $5$、$6$、$7$ 人的方案数加起来即总方案数。而关于挑人，这明显是组合，我们利用组合数公式计算即可。  
### 问题解决：  
#### 组合数公式：  
求从 $n$ 个不同元素中取出 $m$ 个元素的排列数，可看做由以下两个步骤得到的：  
第一步，从这 $n$ 个不同元素中取出 $m$ 个元素，共有 $C_n^m$ 种不同的取法；  
第二步，将取出的 $m$ 个元素做全排列，共有 $A_m^m$ 种不同的排法。  
根据分步乘法计数原理，有  
$$A_n^m=C_n^m·A_m^m$$  
因此  
$$C_n^m= \frac{A_n^m}{A_m^m}= \frac{n(n-1)(n-2) \cdots(n-m+1)}{m!}$$  
这里 $n$，$m \in \mathbb{N}^{*}$，并且 $m \le n$。这个公式叫做**组合数公式**。  
#### 额外注意:可边乘边约以防数据较大时爆。
### Code:  
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;   //类型定义long long为ll，防止频繁使用long long时累手
ll n;   //定义人数
ll Combination(ll n, ll m);   //声明求组合数函数
ll Combination(ll n, ll m)   //求组合数函数
{
	if (n == m)   //n=m时直接为1
	{
		return 1;
	}
	else
	{
		ll s = 1;
		for (ll i = n - m + 1; i <= n; i++)   //从小乘到大
		{
			s = s * i / (i - n + m);   //边乘边约，防爆(-n+m为消n和m，达到分母阶乘约)
		}
		return s;
	}
}
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	cin >> n;
	cout << Combination(n, 5) + Combination(n, 6) + Combination(n, 7);
	return 0;   //结束整个程序
}
```
### 结果(未吸氧):  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/fvied4hx.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：_巴扎黑_ (赞：2)

# 第一道深蓝题
首先，让我们普及一个~~小学~~数学知识——排列组合

这道题可用组合来解决

比如说将5个苹果取2个，方法数即为C（2，5）=（5*4）/（2*1）

没错，就是这么so easy！

下面就能写代码啦

鸭鸭鸭

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int main()
{
	long long n,ans1=1,ans2=1,ans3=1;
	cin>>n;
	for(int i=n-4;i<=n;i++) ans1=ans1*i/(i-n+5);
	for(int i=n-5;i<=n;i++) ans2=ans2*i/(i-n+6);
	for(int i=n-6;i<=n;i++) ans3=ans3*i/(i-n+7);
	cout<<(long long)(ans1+ans2+ans3)<<endl;//这是唯一要注意的地方：数据范围较大. 
	return 0;//养成好习惯 
}
```


---

## 作者：　　　吾皇 (赞：2)

### 总方案数不就是n人中选5,6,7人的方案数的总和吧，用组合数即可
#### 但是，如果你是这么写的
```cpp
ll c(ll a,ll b){
	ll ans=1;
	F(a-b+1,a) ans=ans*i;
    F(1,b) ans=ans/i;
	return ans;
}
```
#### 你就有可能会爆，因为如果a，b过大，ans在乘的过程中会炸掉，所以要这样
```cpp
ll c(ll a,ll b){
	ll ans=1;
	F(a-b+1,a) ans=ans*i/(i-a+b);
	return ans;
}
```
#### 优化在于一边乘一边除
#

### 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define F(a,b) for(ll i=a;i<=b;i++)
ll n;
ll c(ll a,ll b){
	ll ans=1;
	F(a-b+1,a) ans=ans*i/(i-a+b);
	return ans;
}
int main(){
	cin>>n;
	cout<<(ll)(c(n,5)+c(n,6)+c(n,7));
    return 0;
}
```


---

## 作者：BlackPanda (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF630F)

------------
### 题意：
求在 $n$ 个人中选出 $5-7$ 人的方案数，$7≤n≤777$。

------------
### 思路：
在 $n$ 个人中选出 $5-7$ 个人的方案数，就是求 $C^5_n$ $+$ $C^6_n$ $+$ $C^7_n$。

组合数的公式为：$C^m_n$ $=$ $\frac{n!}{m!(n-m)!}$

------------
### code:
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long C(long long m,long long n){
	long long sum=1;
	for(long long i=n-m+1;i<=n;i++){
		sum=sum*i/(i-n+m);
	}
	return sum;
}
int main(){
	cin>>n;
	cout<<C(5,n)+C(6,n)+C(7,n);
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
给定 $n$ 个人，求从这 $n$ 个人中选出 $5\sim 7$ 个人组成团队的方案数。

**数据范围：$7\leqslant n\leqslant 777$。**
## Solution
根据组合数的定义不难想到，答案即为 $\dbinom n5+\dbinom n6+\dbinom n7$。

由于担心答案可能过大，所以我写了个 Python 的代码。众所周知，$\dbinom nk=\dfrac {n!}{k!\cdot (n-k)!}$，因此，我们可以预处理出阶乘数组，然后直接按照上面的公式求出每个组合数，最后加起来即可。
## Code
```python
n = int(input());
fac = [0 for i in range(0, n + 7)];
fac[0] = 1;
for i in range (1, n + 1):
	fac[i] = fac[i - 1] * i;
print(fac[n] // fac[5] // fac[n - 5] + fac[n] // fac[6] // fac[n - 6] + fac[n] // fac[7] // fac[n - 7]);
```

---

## 作者：wpy233 (赞：1)

#震惊！CF的题目居然考小学奥数！#

这题运用了排列组合的知识。
```
所谓排列组合。。。
就是“C 几 几”。
用这个东东，就能很快算出有多少种解。
计算公式是这样的：
例如：C 7 5；
就等于（7*6*5*4*3）/（5*4*3*2*1）=21.
```
其实题目的意思，就是输入一个n，输出C n 5+C n 6+C n 7的值。

排列组合的代码，还是挺好理解的吧。。。
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
long long n,ans1=1,ans2=1,ans3=1;//注意要开long long，三个值的初始值都要标记成1
int main()
{
    cin>>n;//输入
    long long t=1;
    for(int i=n-4;i<=n;i++)
    	ans1*=i,ans1/=t,t++;//第一项
    t=1;
    for(int i=n-5;i<=n;i++)
    	ans2*=i,ans2/=t,t++;//第二项
    t=1;
    for(int i=n-6;i<=n;i++)
    	ans3*=i,ans3/=t,t++;//第三项
    cout<<ans1+ans2+ans3<<endl;//输出
    return 0;
}
```
~~真香~~

---

## 作者：int32 (赞：0)

~~会不会有点短。~~

答案即为从 $n$ 个人选 $5$ 或 $6$ 或 $7$ 人的情况。

容易想到是组合数，写成算式是 $\begin{pmatrix}n\\5\end{pmatrix}+\begin{pmatrix}n\\6\end{pmatrix}+\begin{pmatrix}n\\7\end{pmatrix}$。

计算即可。（记得边乘边除防爆）

---

## 作者：Keep_RAD (赞：0)

这一题需要一点数学基础（组合数），[不懂跳转](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0/2153250)。

如果你知道了组合数是什么，那么这一题就很简单：从 $n$ 个数里分别选 $5$、$6$、$7$ 个数（就是 $C_{n}^{5}+C_{n}^{6}+C_{n}^{7}$），并把这些方案加起来，就是答案。

鉴于楼下的前车之鉴，我们发现直接乘再取模有可能爆（当然你可用 Python），那怎么解决？很简单，边乘边除！

代码：

```cpp
#include<bits/stdc++.h>
#define int long long //防着点溢出
using namespace std;
inline int read()//快读
{
    register int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=(x<<3)+(x<<1)+(c^48); 
        c=getchar();
    }
    return x*f;
}
int c(int n,int m)
{
	int ans=1;//不能为0
  	for(int i=n-m+1;i<=n;i++) ans=ans*i/(i-n+m);
	return ans;
}
signed main()
{
	int n=read();
	cout<<c(n,5)+c(n,6)+c(n,7)<<endl;
	return 0;
}
```
完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：猜一猜我是谁 (赞：0)

# 题意简述
- 即求 n 个数中分别选 5 个、6 个、7 个数的方案总数。

# 思路
根据题意，可以看出答案为 $C^5_n+C^6_n+C^7_n$。

众所周知，组合数公式为

$$C^m_n=\frac{(n-m+1)\times(n-m+2)\times...\times(n-1)n}{m!}$$

而为了防止爆 long long，我们可以边乘边除。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long C(long long n,long long m){//计算组合数
    long long ans=1;
    for(long long i=n-m+1;i<=n;i++) ans=ans*i/(i-(n-m));//边乘边除，以防爆 long long
    return ans;
}
int main(){
    long long n;
    cin>>n;
    cout<<C(n,5)+C(n,6)+C(n,7);
}
```

---

## 作者：清清老大 (赞：0)

## 思路

本题是一道求组合数题。要在 $n$ 个人中选 $5,6$ 或 $7$ 个人，因为选的人不用考虑谁先谁后，所以是求组合。

到底怎么求组合数呢？假设要选 $5$ 个人，一开始，有 $n$ 个人可以选，所以 $5$ 个人中选一个有 $n$ 种方案。选过一个后，只剩下 $n-1$ 个选择了，此时，第一个人有 $n$ 个选择，第二个人有 $n-1$ 个选择，乘起来是 $n(n-1)$ 个选择，但是因为先选A，再选B和先选B，再选A是一样的，所以总数除以重复的 $2$ 组，有 $\frac{n(n-1)}{2 \times 1}$ 个方案。以此类推，选五个人时，有 $5 \times 4 \times 3 \times 2$ 种重复方案，出去后得 $\frac{n(n-1)(n-2)(n-3)(n-4)}{5 \times 4 \times 3 \times 2 \times 1}$ 种方案。当选 $6$ 或 $7$ 种时，分别是 $\frac{n(n-1)(n-2)(n-3)(n-4)(n-5)}{6 \times 5 \times 4 \times 3 \times 2 \times 1}$ 和 $\frac{n(n-1)(n-2)(n-3)(n-4)(n-5)(n-6)}{7 \times 6 \times 5 \times 4 \times 3 \times 2 \times 1}$ 种方案。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    long long 
    Cn5 = n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4 * (n - 4) / 5,
    Cn6 = n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4 * (n - 4) / 5 * (n - 5) / 6,
    Cn7 = n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4 * (n - 4) / 5 * (n - 5) / 6 * (n - 6) / 7;
    cout << Cn5 + Cn6 + Cn7;
}
```


---

## 作者：Daidly (赞：0)

这道题就是在$n$个人中选择$5,6,7$个人的选择种数。
也就是求$C^5_n+C^6_n+C^7_n$。
代码如下：
```
#include<bits/stdc++.h>
//样例就是求（7*6*5*4*3）/（5*4*3*2*1）+（7*6*5*4*3*2）/（6*5*4*3*2*1）+（7*6*5*4*3*2*1）/（7*6*5*4*3*2*1）=21+7+1=29 
using namespace std;
int n;
long long ans1=1,ans11=1,ans111=1;
void five(int n){//分别算出各个组合数
    for(int i=n-4;i<=n;i++){
    	ans1=ans1*i/(i-n+5);
	}
}
void six(int n){
    for(int i=n-5;i<=n;i++){
    	ans11=ans11*i/(i-n+6);
	}
}
void seven(int n){
    for(int i=n-6;i<=n;i++){
    	ans111=ans111*i/(i-n+7);
	}
}
int main(){
    cin>>n;
    five(n);
    six(n);
    seven(n);
    cout<<ans1+ans11+ans111<<endl; //把所有加起来
    return 0;
}
```


---

## 作者：AdzearDisjudge (赞：0)

显然我们求的是$\sum_{i=5}^7 C_n^i$。

~~由于数据范围问题（我不知道n=777用C++需不需要高精度啥的）~~为了简便我们用Python写。

求三个组合数即可。

```

def c(n,m):
    ans=1
    for i in range(n-m+1,n+1):
        ans*=i
    for i in range(1,m+1):
        ans//=i
    return ans
n=int(input())
print(c(n,5)+c(n,6)+c(n,7))

```

---

