# Yet Another Coin Problem

## 题目描述

You have $ 5 $ different types of coins, each with a value equal to one of the first $ 5 $ triangular numbers: $ 1 $ , $ 3 $ , $ 6 $ , $ 10 $ , and $ 15 $ . These coin types are available in abundance. Your goal is to find the minimum number of these coins required such that their total value sums up to exactly $ n $ .

We can show that the answer always exists.

## 说明/提示

In the first test case, for $ n = 1 $ , the answer is $ 1 $ since only one $ 1 $ value coin is sufficient. $ 1 = 1 \cdot 1 $ .

In the fourth test case, for $ n = 5 $ , the answer is $ 3 $ , which can be achieved using two $ 1 $ value coins and one $ 3 $ value coin. $ 5 = 2 \cdot 1 + 1 \cdot 3 $ .

In the seventh test case, for $ n = 12 $ , the answer is $ 2 $ , which can be achieved using two $ 6 $ value coins.

In the ninth test case, for $ n = 16 $ , the answer is $ 2 $ , which can be achieved using one $ 1 $ value coin and one $ 15 $ value coin or using one $ 10 $ value coin and one $ 6 $ value coin. $ 16 = 1 \cdot 1 + 1 \cdot 15 = 1 \cdot 6 + 1 \cdot 10 $ .

## 样例 #1

### 输入

```
14
1
2
3
5
7
11
12
14
16
17
18
20
98
402931328```

### 输出

```
1
2
1
3
2
2
2
3
2
3
2
2
8
26862090```

# 题解

## 作者：__Dist__ (赞：3)

~~用文章区写的第一篇题解。~~

### 题目描述

你有 $5$ 种不同面值的硬币，分别为：$1$ 元、$3$ 元、$6$ 元、$10$ 元和 $15$ 元。这些硬币种类有无穷多。你的目标是用最少的硬币付正好 $n$ 元钱。

### 思路讲解

考虑 $1$ 元、$3$ 元、$6$ 元、$10$ 元的硬币最多会用多少个。

首先，$1$ 元的肯定不会超过 $2$ 个。因为如果使用 $p$ 个 $1$ 元硬币（$p > 2$），我们显然可以用 $1$ 个 $3$ 元硬币和 $p-3$ 个 $1$ 元硬币代替。这样显然是更优的。

同理，$3$ 元的肯定不会超过 $1$ 个，$6$ 元的肯定不会超过 $4$ 个，$10$ 元的肯定不会超过 $2$ 个。

剩下的交给 $15$ 元硬币就好了。

由于前 $4$ 种硬币可选择的范围较少，直接枚举，统计答案即可。

### 代码环节

[$\texttt{Link}$](https://codeforces.com/contest/1934/submission/249318698)

---

## 作者：hgckythgcfhk (赞：3)

由于本题没有目前形式化题意和题解，先给出形式化题意。

求用 $1,3,6,10,15$ 这 $5$ 个数凑出 $n$ 最少用多少个数，每个数可以无限用。

一眼，这是个完全背包，但物品数很少且固定，容量很大.

观察样例发现，如果 $n$ 很大肯定是先尽量多选 $15$ 更优，我们可以贪心的先选很多个 $15$，具体多少看你预处理多少，预处理只要别开太小就行，我开到了 $10^6$，其实不用这么大，然后加上剩下的预处理出来的完全背包。

本题思维难度很低，实现上几乎都是套模板，算法只考查了背包和贪心，由于背包和贪心都有红题，所以建议本题评红或橙。

[记录](https://codeforces.com/problemset/status?my=on)

```cpp
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define ll long long
#define void inline void
using namespace std;constexpr unsigned N=1000001;
unsigned dp[N];
signed main(){open;memset(dp,0x3f,sizeof dp);dp[1]=dp[3]=dp[6]=dp[10]=dp[15]=1;dp[0]=0;
	for(int i=2 ;i<N;++i)dp[i]=min(dp[i-1 ]+1,dp[i]);
	for(int i=4 ;i<N;++i)dp[i]=min(dp[i-3 ]+1,dp[i]);
	for(int i=7 ;i<N;++i)dp[i]=min(dp[i-6 ]+1,dp[i]);
	for(int i=11;i<N;++i)dp[i]=min(dp[i-10]+1,dp[i]);
	for(int i=16;i<N;++i)dp[i]=min(dp[i-15]+1,dp[i]);
	int t;cin>>t;while(t--){int n;cin>>n;if(n<N){cout<<dp[n]<<'\n';continue;}
		int ans=(n-N+1)/15+1;n-=ans*15;cout<<ans+dp[n]<<'\n';}
}

```

---

## 作者：2022_37_yzyUUU (赞：2)

# CF1934B 题解

## 题意简述
你有五种金币，价值分别为：$1$，$3$，$6$，$10$，$15$。

每种金币可以用无限次，给你一个整数 $n$（$1 \le n \le 10^9$），你需要用上述的五种金币凑出 $n$（每个金币的价值总和正好是 $n$），问你凑出 $n$ 所需金币数量的最小值。

## 思路

### 暴力枚举
每次暴力枚举每个金币的数目即可。

面值为 $1$ 的金币最多只能有两个，因为如果更多就可以用面值为 $3$ 的金币代替了。

同理面值为 $2$ 的金币最多能有 $1$ 个，面值为 $6$ 的最多只能有 $4$ 个，面值为 $10$ 的最多有 $2$ 个，剩下的就是 $15$ 元的。

注意枚举硬币数目时从 $0$ 开始。

## 代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t;
		int ans=INT_MAX;
		for(int a=0;a<=2;a++)
			for(int b=0;b<=1;b++)
				for(int c=0;c<=4;c++)
					for(int d=0;d<=2;d++){
						int e=t-a-3*b-6*c-10*d; //15元金币凑成的钱数（可能会凑出负数）
						if(e%15==0&&e>=0)
							ans=min(ans,a+b+c+d+e/15);//取最优
					}
		cout<<ans<<"\n";
	}
   return 0;//好习惯
}
```
## End

---

## 作者：All_Unluck_Beginning (赞：2)

# CF1934B Yet Another Coin Problem 题解

## 题意
目前有 $5$ 种硬币，面值分别为 $1,3,6,10,15$。给你一个数字 $n$，求出可以凑出 $n$ 的最少的硬币的数量。

## 思路
这道题，大多数的人大概会想到动态规划的方法。

**但是，我们应该有敢于创新的精神。于是我就想到了一个简单的数学方法。**

首先我们先不讨论面值等于 $15$ 元的硬币。

考虑硬币的面值为 $1$ 元、$3$ 元、$6$ 元、$10$ 元、$15$ 元的情况。

#### 1：面值为 $1$ 元的硬币的数量范围小于 $3$。
当使用大于等于 $3$ 个 $1$ 元硬币。

则可以用面值为 $3$ 的硬币代替。

#### 2：面值为 $3$ 元的硬币的数量范围小于 $2$。
当使用大于等于 $2$ 个 $3$ 元硬币。

则可以用面值为 $6$ 的硬币代替。

#### 3：面值为 $6$ 元的硬币的数量范围小于 $4$。
当使用大于等于 $4$ 个 $6$ 元硬币。

则可以用 $2$ 个面值为 $10$ 加 $1$ 个面值为 $3$ 加 $1$ 个面值为 $1$ 的硬币代替。

#### 4：面值为 $10$ 元的硬币的数量范围小于 $2$。
当使用大于等于 $3$ 个 $10$ 元硬币。

则可以用 $2$ 个面值为 $15$ 的硬币代替。

#### 5：面值为 $15$ 的硬币。

剩下的数目都有面值为 $15$ 的硬币承担就好了。

### 时间复杂度

因为前面的数值都很少，所以时间复杂度也十分小。

## 代码
```
#include <bits/stdc++.h>
using namespace std;
int n,t,ans;
int main() {
	cin>>t;
	while(t--){
		cin>>n;
		ans=1000000000;
		for(int i=0;i<3;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<5;k++)
					for(int m=0;m<3;m++){
						int y=i*1+j*3+k*6+m*10;
						if(y>n)continue;
						if((n-y)%15==0){
							ans=min(ans,i+j+k+m+(n-y)/15);
						}
					}
		cout<<ans<<endl;
	}
}
```

---

## 作者：RyanLeander (赞：1)

## 读懂题目

[我是原题](https://www.luogu.com.cn/problem/CF1934B)

你有五种金币，价值为 $1$，$3$，$6$，$10$，$15$，每个金币可以重复取无限次，问你用这些金币凑出 $n$ 所需金币数量的最小值。
## 思考
dp 是一个好思路，设 $f[i]$ 为凑出 $i$ 所需要的金币数量的最小值，则 $f[i]=\max(f[i-1],f[i-3],f[i-6],f[i-10],f[i-15])$。

但考虑到 $n \le 10^9$ 这个数据范围，单纯的 dp 显然不行。

可不可以贪心呢？也不行，$98$ 这种情况就是贪心的反例，贪心的结果为 $9$，而答案其实是 $8$。

那可不可以两个一起用呢？**当然可以。**

我们可以用 dp 预处理一下比较小的情况的答案，当输入的 $n$ 在预处理过的范围内，直接从 dp 表中读取结果，若在范围外，尽可能取价值为 $15$ 的金币（贪心），然后就有两种情况。

* 把所有能取的 $15$ 取走，剩下的不能被 $15$ 取走的数用最优策略分，总需金币量最小。

* 少取一个 $15$，将剩下的数按最优策略分，总需金币量最小。

这样子，我们只用预处理 $1$ ~ $30$ 里的数至少需要多少个金币分，就可以以 $O(1)$ 的时间处理询问了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//开到100是为了防数组越界
const int N=110;
ll f[N],n;
int main(){
    //预处理dp表
    for(int i=0;i<40;i++) f[i]=0x3f3f3f3f3f3f3f;
    f[1]=1,f[0]=0;
    for(int i=0;i<40;i++){
        //建议这样写
        f[i+1]=min(f[i+1],f[i]+1);
        f[i+3]=min(f[i+3],f[i]+1);
        f[i+6]=min(f[i+6],f[i]+1);
        f[i+10]=min(f[i+10],f[i]+1);
        f[i+15]=min(f[i+15],f[i]+1);
    }
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%lld",&n);
        if(n<40) printf("%lld\n",f[n]); //在表里就直接输出
        else printf("%lld\n",min(
        f[n%15]+(int)(n/15), //情况一
        f[n%15+15]+(int)(n/15-1) //情况二
        ));
    }
    return 0;
}
```

[AC 记录 （代码无注释版）](https://codeforces.com/contest/1934/submission/249142695)

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：CF1934B Yet Another Coin Problem
### 分析
暴力。

若想要最优解，则面值为 $1$ 的硬币最多 $2$ 枚，因为如果每满 $3$ 枚就可以拿一枚面值为 $3$ 的硬币替代。

面值为 $3$ 的硬币最多 $1$ 枚，因为如果每满 $2$ 枚就可以拿一枚面值为 $6$ 的硬币替代。

面值为 $6$ 的硬币最多 $4$ 枚，因为如果每满 $4$ 枚就可以拿面值为 $10$ 的硬币两枚、面值为 $1$ 的硬币一枚以及面值为 $3$ 的硬币一枚替代。

面值为 $10$ 的硬币最多 $2$ 枚，因为如果每满 $3$ 枚就可以拿面值为 $15$ 的硬币两枚替代。

剩下的则是面值为 $15$ 的硬币要凑成的金额。 

循环枚举每个面值的硬币的数量，再统计最小值即可。

### 代码
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
        int ans=1e18;
        for(int i=0;i<=2;i++)
        {
            for(int j=0;j<=1;j++)
            {
                for(int k=0;k<=4;k++)
                {
                    for(int m=0;m<=2;m++)
                    {
                        int tmp=i+j*3+k*6+m*10;
                        if(n-tmp>=0&&(n-tmp)%15==0)
                        {
                            ans=min(ans,i+j+k+m+(n-tmp)/15);
                        }
                    }
                }
            }
        }
        cout<<ans<<"\n";
    }
}
```

---

## 作者：BinSky (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF1934B)

## 题目概述
你有 $5$ 美元不同类型的硬币，每个硬币的价值等于前 $5$ 美元三角形数字之一：$1$ 美元、$3$ 美元、$6$ 美元、$10$ 美元和 $15$ 美元。这些硬币种类繁多。您的目标是找到所需的这些硬币的最小数量，使它们的总价值正好达到 $n$（保证答案存在）。

## 思路分析
这道题可以用**暴力枚举+贪心**的方式解决，但是直接枚举肯定超时，所以我们要减少枚举范围。例如为了让硬币数量最小，一元最多只能拿 $2$ 个，因为拿 $3$ 个可以用 $1$ 个三元来代替；六元最多只能拿 $4$ 个，因为拿 $5$ 个可以用 $2$ 个十五元来代替，以此类推。

## 代码
```cpp
#include <bits/stdc++.h> 
using namespace std;
int main()
{
    int t,n;
    cin>>t;
    while(t--) 
    {
		int ans=0x3f3f3f3f;
		cin>>n;
     //枚举：
		for(int i1=0;i1<=2;i1++)
		{
		    for(int i2=0;i2<=1;i2++)
			{
		        for(int i3=0;i3<=4;i3++)
				{
		            for(int i4=0;i4<=2;i4++)
					{
						int s=n-i1-i2*3-i3*6-i4*10;
		                if(s>=0&&s%15==0)//满足条件剩下能用15元补充
		                {
		                	ans = min(ans,i1+i2+i3+i4+(s/15));
						}
		            }
		        }
		    }
		}
		cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

如果考虑如果能用 $15$ 面值的硬币就用，容易发现是错误的，例如 $20$，需要用 $15,3,1,1$ 的硬币，然而还有更简便的 $10,10$。

那么考虑打表 $1 \sim 30$ 的答案记为序列 $a$，有两种情况：

- 全部用 $15$ 面值的硬币，数量为 $\lfloor \frac{n}{15} \rfloor+a_{n \bmod 15}$。

- 考虑少用一个 $15$ 面值的硬币，数量为  $(\lfloor \frac{n}{15} \rfloor -1)+a_{(n \bmod 15)+ 15}$。

两种情况取一个最大值即可。

时间复杂度为 $O(T)$。

### 完整代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,ans;
ll a[]={0,1,2,1,2,3,1,2,3,2,1,2,2,2,3,1,2,3,2,3,2,2,3,3,3,2,3,3,3,4,2};
void solve(){
	ans=0;
	n=read();
	if(n>=15){
		ans+=n/15;
		n%=15;
		ans=min(ans+a[n],ans-1+a[n+15]);	
	}
	else
	  ans=a[n];
	write(ans);
	putchar('\n');
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 题意
你有 $5$ 种硬币，面值分别为 $1,3,6,10,15$。每次给你一个数字 $n$，要求求出可以凑出 $n$ 的最少的硬币的数量。
## 思路
这里通过一个暴力的思路。因为我不想构造出最有解法，并且如果直接 dp 也是不可以的。所以我们只需要 dp 求出面值在 $1\sim k$（$k$ 是一个较小的数，这里取 $60$ 就可以）之间的最优解法，然后不断使用 $15$ 元，知道剩余面额小于 $60$，此时直接调用dp处理出来的即可。
## CODE
```c++

#include <bits/stdc++.h>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
// #define mpy make_pair
#define int long long
#define pii pair<int, int>
#define ps b
#define pf a

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))

#define rd read()
int read() {
  int xx = 0, ff = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
}
void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

const int N=1e5+5;
const int INF=1e18;


int n;
int f[N];
int a[N];

void solve(){
    n=rd;
    if(n<=60){
      cout<<f[n]<<endl;
      return ;
    }
    int sum=0;
    sum+=n/15;
    n%=15;
    sum-=2;
    n+=30;
    sum+=f[n];

    cout<<sum<<endl;
    
    
}

void init(){
  for(int i=1;i<=60;i++){
    f[i]=INF;
    if(i>=1)f[i]=min(f[i-1]+1,f[i]);
    if(i>=3)f[i]=min(f[i-3]+1,f[i]);
    if(i>=6)f[i]=min(f[i-6]+1,f[i]);
    if(i>=10)f[i]=min(f[i-10]+1,f[i]);
    if(i>=15)f[i]=min(f[i-15]+1,f[i]);

  }
}

signed main(){
    int T=rd;
    init();
    while(T--){ 
        solve();
    }
}

```

---

