# [Algo Beat Contest 002 C] Counting Square Numbers

## 题目背景

| Problem | Score | Idea | Std | Data | Check | Solution |
| :----------------------------------: | :---: | :---------------------------------------------------: | :---------------------------------------------------: | :---------------------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
|     $\text{C - Counting Square Numbers}$      | $300$ | [wenqinghua1001](https://www.luogu.com.cn/user/976198) | [wenqinghua1001](https://www.luogu.com.cn/user/976198) | [joe_zxq](https://www.luogu.com.cn/user/623577) | [joe_zxq](https://www.luogu.com.cn/user/623577) |     [Link](https://www.luogu.com.cn/article/75je5m51) by [joe_zxq](https://www.luogu.com.cn/user/623577)     |

## 题目描述

wtr1 和 wqh 是一对好朋友。

wqh 给了 wtr1 一个长度为 $n$ 的数组 $A$。对于 $i=1,2,\dots,n$，需要 wtr1 给出包含了位置 $i$ 且区间和为完全平方数的子数组个数。由于最近 wtr1 很忙，请聪明的你帮帮他吧！

若一个数是一个整数的平方，则称这个数是**完全平方数**。

原数组中某段下标连续的元素按原顺序构成的数组称为**子数组**。

## 说明/提示

**【样例解释 #1】**

包含位置 $2$ 的区间和为完全平方数是 $2+3+4=9$，只有 $1$ 个。

包含位置 $4$ 的区间和为完全平方数是 $2+3+4=9$，$4+5=9$ 以及 $4$ 本身，共 $3$ 个。

**【数据范围】**

- $1 \le n \le 5 \times 10^3$。
- $0 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
1
1
1
3
1
```

# 题解

## 作者：dengrunze2608 (赞：6)

## 大意
题目需要对数组中的每一个位置 $i$，找出所有包含 $i$ 的子数组，使得这些子数组的和是一个完全平方数。最后输出满足条件的子数组的个数。
## 思路
为了方便计算每个子数组的和，我们可以先计算前缀和数组 $a$，其中 $a[i]$ 表示数组前 $i$ 个元素的和。

对于每一个位置 $i$，我们可以找到所有包含 $i$ 的子数组，即子数组的起始位置 $l$ 和结束位置 $r$ 满足 $l\le i\le r$。然后计算这些子数组的和，并检查是否为完全平方数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[5005],ans,sum,s;
int main(){
    int n;
    cin>>n;
    a[0]=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;i++){
        ans=0;
        for(int l=1;l<=i;l++){
            for(int r=i;r<=n;r++){
                sum=a[r]-a[l-1];
                s=sqrt(sum);
                if(s*s==sum){
                    ans++;
                }
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

但是，交上去会发现全部 $TLE$。
[提交记录](https://www.luogu.com.cn/record/219841841)

计算时间复杂度会发现，因为 $n\le5000$，所以最坏情况可能为 $O(n^3)$，绝对会超时。

因此我们需要优化内层循环，可以利用差分进行优化，将时间复杂度由 $O(n)$ 降到 $O(1)$。

具体来讲，可以开一个差分数组 $c$，令 `c[0]=0` 并让 `c[i]=a[i]-a[i-1]`。这样 $c$ 数组中就是相邻两数的差值了。这样，当求子数组 `a[l]` 到 `a[r]` 的和时，这个和实际上等于 `c[l]+c[l+1]+...+c[r-1]+c[r]`，我们可以发现这个结果恰好等于 `a[r]-a[l-1]`。

在本题中，我们可使用差分数组 $c$ 来记录每个位置被多少符合条件的子数组覆盖。当发现子数组 `[l,r]` 的和是完全平方数时，执行 `c[l]+=1` 以及 `c[r+1]-= 1`，这样在后续计算 $c$ 数组的前缀和时，位置 $l$ 到 $r$ 会自动加 $1$。

最后，计算差分数组 $c$ 的前缀和，就能得到每个位置被多少个符合条件的子数组覆盖，得出答案，同时大大降低了时间复杂度。

## $AC$代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[5005],n,c[5005];
long long sum,s,ans=0; 
signed main(){
    cin>>n;
    a[0]=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=a[i-1];
    }
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            sum=a[r]-a[l-1];
            s=sqrt(sum);
            if(s*s==sum){
                c[l]++;
                c[r+1]--;
            }
        }
    }
    for(int i=1;i<=n;++i){
        ans+=c[i];
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：wenqinghua1001 (赞：5)

这里是本题出题人的题解，本题考查前缀和与差分（~~当然你也可以用树状数组来解~~）。

首先输入 $A$ 数组。接着求出前缀和，$S_1=A_1$，$S_i=S_{i-1}+A_i$。对于区间 $\begin{bmatrix} l,r \end{bmatrix}$，区间所有数的和是 $S_r-S_{l-1}$。如果 $S_r-S_{l-1}$ 是平方数，那么 $C_l=C_l+1$，$C_{r+1}=C_{r+1}-1$，差分。最后对 $C$ 数组做前缀和，输出。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000001];
int s[1000001];
int c[1000001];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
		// 前缀和 
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int f=s[j]-s[i-1];
			int u=sqrt(f);
			if(u*u==f) // 平方数 
				c[i]++,c[j+1]--;
			// 差分 
		}
	}
	for(int i=1;i<=n;i++){
		c[i]=c[i-1]+c[i];
		cout<<c[i]<<endl;
		// 输出 
	}
	return 0;
}
```

---

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12716)
## 前言
没打比赛，前来水题解。
## 思路
预处理前缀和，然后差分求值。

先讲一讲如何判断完全平方数吧。

易得，若 $x$ 为完全平方数，则满足：

- $\lceil \sqrt{x} \rceil^2=x$。
- $\lfloor \sqrt{x} \rfloor^2=x$。

这是必然的。所以可以打出这样一个判断函数。
```cpp
bool pf(int x){//判断 x 是不是平方数 
	int y=sqrt(x);//强转当然也可以 
	return x==y*y; 
}
```
一定要把 $\sqrt{x}$ 存在整型变量中哦，不然会错。

然后 $sum$ 数组预处理前缀和，便于求解区间和。

为什么要用差分数组呢？因为对于区间 $[left,right]$ 来说，若满足区间和是完全平方数，那么该区间每个元素的答案都要加一，单次累加时间复杂度就有 $O(right-left+1)$，肯定超时，所以用到了**差分**数组来求，最后再对差分数组求前缀和，输出即可。

时间复杂度 $O(n^2)$，不会超时，但要注意开 long long。

**注意：单个元素也可以是子数组。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+5;
bool pf(int x){//判断 x 是不是平方数 
	int y=sqrt(x);//强转当然也可以 
	return x==y*y; 
}
int n,sum[N],b[N];
signed main(){
	scanf("%lld",&n);
	for(int i=1,x;i<=n;i++) scanf("%lld",&x),sum[i]=sum[i-1]+x;//预处理前缀和数组
	for(int left=1;left<=n;left++)
		for(int right=left;right<=n;right++){
			int he=sum[right]-sum[left-1];//求区间和
			if(pf(he)==1) b[left]++,b[right+1]--;//差分计数 
		} 
	int ans=0;
	for(int i=1;i<=n;i++) printf("%lld\n",ans+=b[i]); //差分数组求前缀和 
	return 0;
}
```
撒花。

---

## 作者：joe_zxq (赞：4)

首先考虑预处理出一个前缀和，枚举所有 $n^2$ 个区间计算区间和并判断是否为完全平方数。假设当前区间为 $[L,R]$，则需要对于区间内的每一位，其对应的答案都会增加 $1$。于是考虑维护差分数组，最终前缀和一下就是答案啦。

当然，也可以无脑地用树状数组或线段树来实现区间加，但是这是 C 题。

时间复杂度：差分做法为 $O(n^2)$，数据结构做法为 $(n^2 \log n)$。

下面展示的是差分做法。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],b[100005];
bool chk(long long x){
	long long y=sqrt(x);
	return y*y==x;
}
int main(){
	long long n;
    scanf("%lld",&n);
    for(long long i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        a[i]=a[i-1]+a[i];
    }
    for(long long i=1;i<=n;i++){
        for(long long j=i;j<=n;j++){
            long long sum=a[j]-a[i-1];
            if(chk(sum)){
                b[i]++;
                b[j+1]--;
            }
        }
    }
    for(long long i=1;i<=n;i++)
        b[i]+=b[i-1];
    for(long long i=1;i<=n;i++){
    	printf("%lld\n", b[i]);
	}
    return 0;
}
```

---

## 作者：weifengzhaomi (赞：3)

### 算法：前缀和、预处理。

## 思路：

考虑预处理好前缀和数组，方便看一段区间的和。

然后，我们暴力枚举两个端点，如果这两个端点形成的区间的和是一个**完全平方数**，那么就可以把这一段区间的答案加一，可以用**差分**。

简单来说，就是维护差分数组，在前缀和一下。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[5010],f[5010],ans[5010];
inline bool clec(int x){int y = sqrt(x);return y * y == x;}
signed main(){
	scanf("%lld",&n);
	for (int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	for (int i = 1;i <= n;i++) f[i] = f[i - 1] + a[i];
	for (int i = 1;i <= n;i++)
		for (int j = i;j <= n;j++) if (clec(f[j] - f[i - 1])) ans[i]++,ans[j + 1]--;
	for (int i = 1;i <= n;i++) ans[i] = ans[i - 1] + ans[i],printf("%d\n",ans[i]);
}
```

---

## 作者：AFO_Lzx (赞：1)

前缀和 & 差分板子结合的题。

设包含位置 $i$ 且区间和为完全平方数的区间的数量为 $d_i$。

首先区间和用前缀和解决，$O(n^2)$ 枚举符合条件的区间。

假如一个区间 $[l,r]$ 满足条件，则对于所有的 $l \le i \le r$，将 $d_i+1$。这就涉及到了区间修改。可以用树状数组或线段树等数据结构，但是码量大且时间复杂度还要多乘一个 $O(\log n)$，所以我们使用差分。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e3 + 5;
int n, c, a[N], s[N], d[N];

bool check(int x) {
	int y = sqrt(x);
	return (y * y == x);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int sum = s[j] - s[i - 1];
			if (check(sum) == 1) {
				d[i]++;
				d[j + 1]--;
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		d[i] += d[i - 1];
		cout << d[i] << '\n';
	}
	
	return 0;
}
```

---

## 作者：lilong (赞：1)

观察数据范围，考虑枚举每个区间 $[l,r]$，使用前缀和快速求出区间和并判断是否为完全平方数，若是则对 $i \in [l,r]$ 都产生 $1$ 的贡献，使用差分数组维护即可。时间复杂度 $O(n^2)$。

```cpp

#include <iostream>
#include <cstdio>
#include<cmath>
#define int long long
#define N 10010
using namespace std;
int n,a[N],s[N],d[N];
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i],s[i]=s[i-1]+a[i];
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int k=sqrt(s[j]-s[i-1]);
            if(k*k==s[j]-s[i-1]){
                d[i]++;d[j+1]--;
            }
        }
    }
    for(int i=1;i<=n;i++)
        d[i]+=d[i-1],cout<<d[i]<<endl;
    return 0;
}

```

---

## 作者：tuntunQwQ (赞：1)

因为 $n\le5000$，所以可以枚举每个区间，计算它的区间和，如果是平方数，则对于 $i\in[l,r]$，将 $i$ 的答案加 $1$。预处理前缀和的话区间和就可以 $O(1)$ 求出，将一个区间的所有元素加上同一个值可以用差分数组实现，这样时间复杂度就是 $O(n^2)$ 的，可以通过本题。注意 $5000\times 10^9$ 会爆 int，要用 long long 存储。

代码如下，可供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+10;
long long n,a[N],sum[N],ans[N];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            long long k=sqrt(sum[r]-sum[l-1]);
            if(k*k==sum[r]-sum[l-1])ans[r+1]--,ans[l]++;
        }
    }
    for(int i=1;i<=n;i++)ans[i]+=ans[i-1],cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12716)
## 题目分析
希望审核大大给过。

这是一道考验我们**差分**的题目。使用前缀和将 $A$ 数组求和，再定义 $l$ 和 $r$ 记录区间和，如果这个区间为**完全平方数**再使用差分记录进一个新的数组即可算出答案。

下面是本题代码。
## 题目[代码](https://www.luogu.com.cn/record/219845629)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
int n,a,f[5001],b[5001];
bool chk(int x){return (int)sqrt(x)==sqrt(x);}
signed main() {
	speed
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a,f[i]=f[i-1]+a;
	for(int r=1;r<=n;r++){
		for(int l=1;l<=r;l++){
			if(chk(f[r]-f[l-1])){
				b[l]++;
				b[r+1]--;
			}
		}
	}
	for(int i=1;i<=n;i++)b[i]+=b[i-1];
	for(int i=1;i<=n;i++)cout<<b[i]<<'\n';
	return 0;
}
//关注一下作者吧，一定壶关qaq
```

---

## 作者：glass_goldfish (赞：0)

水题。
### 解题思路
观察到 $n\le5\times10^3$，所以可以使用 $O(n^2)$ 的时间复杂度解决。显然，直接处理每个区间是否满足第一个条件（和为完全平方数），如果满足，则累加（记满足包含了位置 $i$ 且区间和为完全平方数的区间个数为 $f_i$），记该区间为 $[l,r]$，则 $f_l\gets f_l+1,f_{l+1}\gets f_{l+1}+1,\ldots,f_r\gets f_r+1$。看到这里，想到了什么？差分！记差分数组为 $p$，则 $p_l\gets p_l+1,p_{r+1}\gets p_{r+1}-1$。最后的 $f$ 就是 $p$ 的前缀和了。考虑到第一次用完原本数组的前缀和之后就不用了，所以第一次原本数组的前缀和数组也可以是 $f$（节省空间）。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1145141919810
using namespace std;
int n,cnt,a[12001];
int f[12001],p[12001];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],f[i]=f[i-1]+a[i];//统计原本数组的前缀和
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
		if(1LL*signed(sqrt(f[j]-f[i-1]))*signed(sqrt(f[j]-f[i-1]))==f[j]-f[i-1])//强转并判定
			p[i]++,p[j+1]--;//符合条件
	for(int i=1;i<=n;i++)
		f[i]=f[i-1]+p[i];//差分还原
	for(int i=1;i<=n;i++)
		cout<<f[i]<<"\n";//输出答案
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

考虑对于每个 $i$ 直接求答案，但是这样太过暴力，时间复杂度为 $\mathcal O(n^3)$。

于是考虑直接遍历所有区间，可以做到 $\mathcal O(n^2)$，判断和是否为完全平方数也是 $\mathcal O(1)$ 的。

然后我们发现对于满足条件的区间 $[l ,r]$，对于 $\forall i ,l \le i\le r$ 都可以有 $1$ 的贡献。

于是用差分维护，最后的答案即为差分数组的前缀和（基本性质）。

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 1e14
 
using namespace std;
 
inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}
 
constexpr int N = 2e5 + 10;
int n ,a[N] ,b[N];

signed main (){
  n = read ();
  up (i ,1 ,n) a[i] = read ();
  up (i ,1 ,n){
    int sum = 0;
    up (j ,i ,n) {
      sum += a[j];
      int sq = sqrt (sum);
      if (sq * sq == sum) b[i] ++ ,b[j + 1] --;
    }
  } int ans = 0;
  up (i ,1 ,n) {ans += b[i] ; writeln (ans);}
  return 0 ;
}
```

---

