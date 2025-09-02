# Polycarpus' Dice

## 题目描述

Polycarp has $ n $ dice $ d_{1},d_{2},...,d_{n} $ . The $ i $ -th dice shows numbers from $ 1 $ to $ d_{i} $ . Polycarp rolled all the dice and the sum of numbers they showed is $ A $ . Agrippina didn't see which dice showed what number, she knows only the sum $ A $ and the values $ d_{1},d_{2},...,d_{n} $ . However, she finds it enough to make a series of statements of the following type: dice $ i $ couldn't show number $ r $ . For example, if Polycarp had two six-faced dice and the total sum is $ A=11 $ , then Agrippina can state that each of the two dice couldn't show a value less than five (otherwise, the remaining dice must have a value of at least seven, which is impossible).

For each dice find the number of values for which it can be guaranteed that the dice couldn't show these values if the sum of the shown values is $ A $ .

## 说明/提示

In the first sample from the statement $ A $ equal to 8 could be obtained in the only case when both the first and the second dice show 4. Correspondingly, both dice couldn't show values 1, 2 or 3.

In the second sample from the statement $ A $ equal to 3 could be obtained when the single dice shows 3. Correspondingly, it couldn't show 1, 2, 4 or 5.

In the third sample from the statement $ A $ equal to 3 could be obtained when one dice shows 1 and the other dice shows 2. That's why the first dice doesn't have any values it couldn't show and the second dice couldn't show 3.

## 样例 #1

### 输入

```
2 8
4 4
```

### 输出

```
3 3 ```

## 样例 #2

### 输入

```
1 3
5
```

### 输出

```
4 ```

## 样例 #3

### 输入

```
2 3
2 3
```

### 输出

```
0 1 ```

# 题解

## 作者：Error_Eric (赞：3)

### 前言

自动识别语言把 Python 识别为 Pascal 差评。

翻译有误差评。

### 正文

>有 $n$ 个骰子，第 $i$ 个骰子朝上的面的可能值在 $1$ 到  $d_i$ 之间，扔了一遍这些骰子之后发现朝上的面的值之和为 $A$。现在需要你对于每一个骰子计算出其抛出多少种值一定凑不成 $A$。$1\le n\le 2\times10^5$,$n\le A\le \sum d_i$,$1\le d_i\le 10^6$

我们记 $\sum d_i=sum$，这个骰子投出的是 $c_i$。

不难发现，除去 $d_i$，剩下的骰子可以投出所有满足 $n-1\le x\le sum-d_i$ 的整数。

如果 $c_i>A-(n-1)$ 那么是一定凑不成 $A$ 的。显然这样的 $c_i$ 有 $\max(0,d_i+n-a-1)$ 个。

如果 $c_i<A-(sum-d_i)$ 那么也是凑不成 $A$ 的。显然这样的 $c_i$ 有 $\max(0,A-sum+d_i-1)$ 个。

那么得出:

$$v_i=\max(0,d_i+n-a-1)+\max(0,A-sum+d_i-1)$$

此时这种简单题用 C++ 显得笨拙，冗长且没有必要。我们采用 Python 求解。

### Code

```python
s=input().split()
n=int(s[0]);a=int(s[1]);d=[];sum=0
s=input().split()
for i in range(n):
    d.append(int(s[i]));sum=sum+d[i]
for i in range(n):
    print(max(0,d[i]+n-a-1)+max(0,a-sum+d[i]-1),end=" ")
```

~~好像有种说法非 C++ 的题解更容易通过？~~

---

## 作者：lihanyang (赞：3)

```cpp
看看我写的代码吧：
#include<bits/stdc++.h>
using namespace std;
long long d[200007];//开大点，别TLE
int main()
{
	long long n,a;
	long long zuidanengbiaoshi=0;//最大能表示的数（也可以说是总和）（我才不告诉你我都这样命名变量呢）
	cin>>n>>a;
	for(int i=1;i<=n;i++)
	{
		cin>>d[i];
		zuidanengbiaoshi+=d[i];
	}//读入
	for(int i=1;i<=n;i++)
	{
		long long ans=0;
		if(a-n+1<d[i]) ans+=(d[i]+n-a-1);//d[i]太大了
		if(d[i]+a-zuidanengbiaoshi-1>=0) ans+=(a-zuidanengbiaoshi+d[i]-1);//d[i]太小了
		cout<<ans<<" ";//输出，别忘了是long long
	}
}
```

---

## 作者：_Felix (赞：2)

```cpp
看代码：
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main() 
{
	long long n,d[200005],a,ans=0;//定义，记得开long long
    
	cin>>n>>a;
	for(long long i=1;i<=n;i++)
	{
		cin>>d[i];
		ans+=d[i];//算和
	}//读入
    
	for(long long i=1;i<=n;i++)
	{
		long long hhh=min(a-n+1,d[i]);//最大的
		long long zzz=0;
		if(a+d[i]-ans-1>0)
			zzz=a+d[i]-ans-1;//最小的
        //abs(zzz-hhh)就是可行的情况
		cout<<d[i]-abs(zzz-hhh)<<" ";//输出
	}
	cout<<endl;//输出换行
    return 0;//完美结束
}
//最后感谢我们的hello_world2005给我们的参考

```
**By 你们最可爱的czy**

---

## 作者：sto__Liyhzh__orz (赞：2)

### [传送门](https://www.luogu.com.cn/problem/CF534C)

最值问题。

将点数记为 $sum$，将各个骰子能投出来的最大的值之和，再减去本个骰子最大值记为 $s$。

无非就是两种情况：

1. 太小了。后面全投最大值都不行。所以 $sum + s - a_i < k$，即 $sum < k + a_i - s$。

2. 太大了。后面全投 $1$ 都不行。所以 $sum + n - 1 > k$，即 $sum > k - n + 1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const int MAXN=200000+5;
LL a[MAXN],n,m;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    LL sum=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cout<<max(0ll,m-(sum-a[i])-1)+max(0ll,a[i]-(m-n+1))<<" ";
    }
    return 0;
}
```

---

## 作者：lgx57 (赞：1)

# CF534C Polycarpus' Dice 题解
一道简单的贪心。
## 1.题意
有 $n$ 个骰子，每一个的点数在 $1$ 到 $d_{i}$ 之间。再给出一个整数 $A$，求对于每一个骰子其抛出多少种所有骰子的点数总和一定凑不成 $A$。
## 2.分析
只需要知道每一个骰子的点数的最大值与最小值即可。
1. 最小值：
如果不考虑题目要求的话，点数显然最小是 $1$。
但考虑题目要求，如果当其他骰子的点数都取最大值时，加上它也无法满足要求，那么这个点数对于这个骰子来说肯定是不行的。  
所以我们考虑用 $sum$ 来表示所有骰子的点数最大值，那么，对于这个骰子，它投出的点数最小值应该为 $\min(1,A-(sum-d_{i}))$。

2. 最大值
同样的，如果不考虑题目要求的话，点数显然最大是 $d_{i}$。
但考虑题目要求，如果当其他骰子的点数都取最小值时，加上它也要超过 $A$，那么这个点数对于这个骰子来说肯定是不行的。
所以，对于这个骰子，它投出的点数最大值应该为 $\max(d_{i},A-d_{i})$。
3. 结合
只需要在 $1$ 到 $A$ 之间，把最小值到最大值之间的部分去掉即可。

## 3.参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void fio(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
const int N=2e5+5;
int a[N]; 
signed main(){
	int n,A,sum=0;
	cin>>n>>A;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for (int i=1;i<=n;i++){
		int mi=max(1ll,A-(sum-a[i]));//最小值
		int ma=min(a[i],A-(n-1));//最大值
		cout<<a[i]-(ma-mi+1)<<' ';//把它们去掉
	}
	return 0;
}

```
## 4.注记
# 十年 OI 一场空，不开 long long 见祖宗！

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF534C Polycarpus' Dice
## 翻译
有 $n$ 个骰子，第 $i$ 个骰子朝上的面的可能值在 $1$ 到  $d_i$ 之间，扔了一遍这些骰子之后发现朝上的面的值之和为 $A$。现在需要你对于每一个骰子计算出其抛出多少种值一定凑不成 $A$。$1\le n\le 2\times10^5$,$n\le A\le \sum d_i$,$1\le d_i\le 10^6$。
## 思路：
这道题正常就直接输出就行了，但有两种情况，就是前面投的太小了，后面都投最大也没达到，一种是前面投的太大了，后面全投 $1$ 都没法达到，那么只需要将 $sum$ 对这两种情况进行加减操作就行了。
## 数据范围！

---

## 作者：xinruian (赞：0)

### **题意**

有 $n$ 个骰子，第 $i$ 个骰子朝上的面的可能值在 $1$ 到 $d_i$ 之间，扔了一遍这些骰子之后发现朝上的面的值之和为 $A$。对于每个骰子，求出其**不可能**抛出的值有多少个。

### **思路**

对于每个骰子，当其他骰子朝上的面都为 $1$ 时，该骰子朝上的值为该骰子可能出现的值的最大值，即 $A-(n-1)$（若该值超过骰子自身的最大值，则该骰子可能出现的值的最大值就是自身的最大值）。

反之，对于骰子 $k$，当其他骰子朝上的面都为各自本身的最大值时，该骰子朝上的值为该骰子可能出现的值的最小值，即 $A-\sum_{i!=k}{d_i}$（若该值小于 $1$，则该骰子可能出现的值的最小值就是 $1$）。

令骰子 $k$ 可能出现的值的最大值为 $mx$，最小值为 $mn$。则对于每个骰子，可能抛出的值的种类数为：$d_k-(mx-mn+1)$。

### **代码如下**

```cpp
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <algorithm>

const int N = 2e5 + 10;

using namespace std;

int w[N];

int main() {
	int n;
	long long a, sum = 0;
	cin >> n >> a;
	for (int i = 1; i <= n; i ++) {
		cin >> w[i];
		sum += w[i];
	}
	for (int i = 1; i <= n; i ++) {
		int mx = min((long long)w[i], a - (n - 1));
		int mn = max((long long)1, a - (sum - w[i]));
		int res = w[i] - (mx - mn + 1);
		cout << res << ' '<<" \n"[i == n];
	}	
	return 0; 
}
```



---

## 作者：wuyixiang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF534C)

题目大意：$n$ 个骰子，第 $i$ 个骰子能投出 $1$ 至 $d_i$ 点，问对于每个骰子有多少个情况即使剩下的骰子怎么投都凑不出 $k$ 点。

算法分析：无非就两种情况：一种太大，一种太小。如果一个骰子投出来 $114$ 点，那么剩下即使全投 $1$ 都要超过 $k$ 了；而如果它只投了 $1$ 点，即使最后的 $n - 1$ 个骰子效果拔群全投出最大值都达不到 $k$。所以就看有多少个方案 $+\space n - 1 > k$ 或者 $+ \space s - a_i < k$ 就行了。通过转移，可以得到骰子点数必须 $> k - n + 1$ 或者 $< k - s + a_i$。注意方案数非负，所以需要对 $0$ 取 $\operatorname{max}$。最后直接输出即可。

附代码：

```cpp
#include <iostream>
using namespace std;
long long sum,a[200005],n,k;
int main()
{
    cin >> n >> k;
    for(int i = 1;i <= n;i ++)cin >> a[i],sum += a[i];//计算总和
    for(int i = 1;i <= n;i ++)
        cout << max(k - (sum - a[i]) - 1,0LL) + max(a[i] - (k - n + 1),0LL) << " ";//计算太小或过大的情况
    return 0;
}
```

---

## 作者：桃雨凪丝 (赞：0)

## 题目分析
不成立一共有两种情况。

1. 这次取得太大了，别的骰子都取 1，也超过了 A。
2. 这次取得太小了，别的骰子都取 max，也达不到 A。


------------


代码很简单，贴贴：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define re register
#define inf 1e9+10
#define lim 200010
#define mod 998244353
#define rarr(n,a) for(int i=1;i<=n;i++)cin>>a[i];
//rarr读入数组//快读 
inline int rd(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
ll n,A,d[lim],sum=0;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>n>>A; 
	for(int i=1;i<=n;i++)cin>>d[i];//好像没用rarr
	for(int i=1;i<=n;i++)sum+=d[i];
	for(int i=1;i<=n;i++){
		ll ans=0;
		ans+=max(0LL,d[i]+n-A-1);//太小了
		ans+=max(0LL,A-sum+d[i]-1); //太大了
		cout<<ans<<" ";
	}
	
	return 0;
}


```



---

## 作者：Scapegoat_Tree (赞：0)

## 更正题意

- 要求输出的是每个色子不能达到要求点数的个数。

## 思路

- 对于一个色子，我们先求出其他色子可以掷出的范围，那么我们就能得到这个色子所可能掷出的范围，这样将这个范围减去就可以求出答案了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
namespace SGT
{
	char getc(){return getchar();}
	void putc(char ch){putchar(ch);}
	int read(){int mk=1,x=0;char ch=getc();while(ch!='-'&&(ch<'0'||ch>'9'))ch=getc();if(ch=='-')mk=-1,ch=getc();while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getc();return x*mk;}
	void write(int x,std::string ch){char cc[100000];int t=0;if(x==0)putc('0');if(x<0) putc('-'),x=-x;while(x){cc[++t]=char(x%10+48);x/=10;}for(int i=t;i>=1;i--)putc(cc[i]);if(ch.size()>0)putc(ch[0]);}
	void write(char str[],std::string ch){for(int i=0;i<strlen(str);i++)putc(str[i]);if(ch.size()>0)putc(ch[0]);}
	void write(char wr,std::string ch){putc(wr);if(ch.size()>0)putc(ch[0]);}
	int max(int a,int b){return (a>b?a:b);}
	int min(int a,int b){return (a<b?a:b);}
	int gcd(int a,int b){int r;while(b>0){r=a%b;a=b;b=r;}return a;}
}
using namespace SGT;
int n,k,a[200010],sum;
signed main()
{
	n=read();
	k=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		int minn=n-1;
		int maxx=sum-a[i];//其他色子的范围
		if(k-maxx>0) ans+=k-maxx-1;
		if(k-minn<=a[i]) ans+=a[i]-k+minn;
		write(ans," ");
	}
	return 0;
}


```

---

## 作者：开始新的记忆 (赞：0)

~~比较简单，应该没有紫题的难度~~

先把总和算出来，然后O（n）把每个骰子扫一遍，然后看总和减掉这个骰子的di后与A的差即可


```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
long long mx(int a,long long b)
{
    if(a>b) return a;
    else return b;
}
int main()
{
    long long a,b,c,k=0,d[200001],e,f,j=1,z=1;
    cin>>a>>b;
    for(long long i=1;i<=a;i++)
    {
        cin>>d[i];
        k+=d[i];
    }
    for(long long j=1;j<=a;j++)
    {
        e=min(d[j],b-a+1);
        f=max(z,b-(k-d[j]));
        cout<<(d[j]-(e-f+1))<<" ";
    }
    return 0;
}
```


---

