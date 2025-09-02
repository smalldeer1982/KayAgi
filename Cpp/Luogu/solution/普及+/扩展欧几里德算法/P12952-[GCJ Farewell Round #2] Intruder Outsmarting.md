# [GCJ Farewell Round #2] Intruder Outsmarting

## 题目描述

**Amiria** 是一个谨慎的互联网用户，因此她正在为账户设置双重认证。她使用一种特殊的安全密钥作为额外防护，以智胜那些可能想要窃取它的入侵者。**Amiria** 的安全密钥需要一个激活码。要输入这个激活码，必须将其放置在带有数字的转轮上，类似于密码挂锁。

**Amiria** 的安全密钥由 $\mathbf{W}$ 个转轮组成。每个转轮上按顺序印有数字 1 到 $\mathbf{N}$。通过一次转轮旋转，用户可以将当前显示的数字移动到下一个或上一个数字。转轮上的数字是循环的，这意味着 $\mathbf{N}$ 的下一个数字是 1，而 1 的前一个数字是 $\mathbf{N}$。

这里没有隐藏密码。要激活 **Amiria** 的安全密钥，需要调整转轮，使得显示的数字序列是回文的。也就是说，数字序列从左到右和从右到左读起来是一样的。为了减慢入侵者的速度，**Amiria** 对安全密钥进行了设置，使得转轮只能以 $\mathbf{D}$ 的增量旋转。也就是说，在一次操作中，当前显示数字 $x$ 的转轮可以调整为显示 $x - \mathbf{D}$ 或 $x + \mathbf{D}$，并应用适当的循环调整。具体来说，如果 $x - \mathbf{D} < 1$，则操作后实际显示的数字是 $x - \mathbf{D} + \mathbf{N}$；如果 $x + \mathbf{D} > \mathbf{N}$，则实际显示的数字是 $x + \mathbf{D} - \mathbf{N}$。

**Amiria** 想检查这个系统会如何减慢试图使用她安全密钥的入侵者。给定转轮的数量和每个转轮当前显示的数字，找到使显示的数字序列成为回文所需的最少操作次数，或者报告这是不可能的。


## 说明/提示

**样例解释**

在样例 #1 中，可以通过 3 次操作将序列调整为 $5 \ 4 \ 5 \ 4 \ 5$，这是一个回文序列。具体操作为：对第一个和第四个转轮进行一次加法操作，对第五个转轮进行一次减法操作。无法用更少的操作使序列成为回文。

在样例 #2 中，序列已经是回文的，因此不需要任何操作。

在样例 #3 中，要使序列成为回文，两个数字必须相同。由于转轮只能以 2 的增量移动，而当前两个数字的奇偶性不同，因此无法实现。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{D} \leq \mathbf{N}-1$。
- 对所有 $i$，$1 \leq \mathbf{X}_{i} \leq \mathbf{N}$。

**测试集 1（4 分，可见判定）**
- $2 \leq \mathbf{W} \leq 5$。
- $2 \leq \mathbf{N} \leq 5$。

**测试集 2（10 分，可见判定）**
- $2 \leq \mathbf{W} \leq 1000$。
- $2 \leq \mathbf{N} \leq 10^{9}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5 5 4
1 4 5 5 4
3 4 2
3 4 3
2 4 2
1 4```

### 输出

```
Case #1: 3
Case #2: 0
Case #3: IMPOSSIBLE```

# 题解

## 作者：ziyistudy (赞：5)

不难发现我们只需考虑回文串上对应位置的两个数，即 $X_i$ 和 $X_{n-i+1}$。我们需要它们相等，则操作两数加上若干 $D$ 后模 $N$ 同余。这很**同余方程**。

先不考虑角标，我们就考虑一组 $X_1$ 和 $X_2$。下记 $k_1$ 和 $k_2$ 为操作次数。

可以列式：
$$X_1+k_1D\equiv X_2+k_2D\pmod{N}$$

移项即有：
$$(k_1-k_2)D\equiv X_2-X_1\pmod{N}$$

右边是常数，左边是未知数的若干倍，是同余方程基本形式，变形为等式即可（其中 $k_3$ 为倍数）：
$$(k_1-k_2)D+k_3N=X_2-X_1$$

无解情况显然是当这个 $X_2-X_1$ 不是 $\gcd(N,D)$ 的倍数。

这个式子丢到扩展欧几里得里面可以求出 $(k_1-k_2)$ 和 $k_3$。但是我们其实并不关心 $k_1$ 和 $k_2$ 的具体值，因为我们可以令其中一个为 $0$，所以我们只需让它们差的绝对值尽可能小。

对于一个等式方程，它的通解是可以加上对方的系数的，令我们求出的 $x_0=k_1-k_2$，则 $x=x_0+\frac{N}{\gcd(N,D)}k$，$k$ 为任意整数。

我们就把 $\frac{N}{\gcd(N,D)}$ 当一个模数做把 $x_0$ 变为一个最小正数。但注意到差其实可以使负数，所以我们需要取一个 $\max$。即：$\max(x_0,abs(x_0-\frac{N}{\gcd(N,D)}))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int N=1005;
int a[N];
void ExpGcd(int a,int b,int &x,int &y)
{
    if(!b){
        x=1;
        y=0;
    }
    else {
        ExpGcd(b,a%b,x,y);
        int tmp=x;
        x=y;
        y=tmp-a/b*y;
    }
    return ;
}
signed main() 
{
    cin.tie(nullptr);cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int T;cin>>T;
    for(int k=1;k<=T;k++)
    {
        int w,n,d;cin>>w>>n>>d;
        for(int i=1;i<=w;i++) cin>>a[i];
        int ans=0;
        bool flag=true;
        for(int i=1;i<=w/2;i++){
            int X,Y;
            int b=a[w-i+1]-a[i];
            if(b%__gcd(d,n)!=0) {flag=false;break;}
            ExpGcd(d,n,X,Y);
            int mod=n/__gcd(d,n);
            X=X*(b/__gcd(d,n));
            X=(X%mod+mod)%mod;
            ans+=min(X,abs(X-mod));
        }
        if(flag) cout<<"Case #"<<k<<": "<<ans<<endl;
        else cout<<"Case #"<<k<<": IMPOSSIBLE"<<endl;
    }
}
```

---

## 作者：jsisonx (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P12952)

# 题目分析

注意到，首先，转动转轮的过程实际上就是加 $D$ 再模 $N$ 的过程。第二，回文串的性质是 $X_i=X_{w-i+1}$。根据以上两点，该题可解。

由上面两点不难看出，题目实际上是要求下面同余方程的解：
$$X_i+Dx \equiv X_{w-i+1}+Dy \pmod N$$

其中 $i$ 取遍 $1$ 到 $\lfloor \frac{N}{2} \rfloor$。

上面的同余方程变形得

$$X_i-X_{w+i-1}+(x-y)D-kN=0$$
$$(x-y)D-kN=X_{w+i-1}-X_i$$

这是一个二元一次不定方程。根据裴蜀定理，有解的充分必要条件是 $X_{w+i-1}-X_i$ 是 $(D,N)$ 的倍数。因此，若存在 $i$ 使得 $X_{w+i-1}-X_i$ 不是 $(D,N)$ 的倍数，则无解。

若有解，则使用扩展欧几里得算法求出方程的一组解。设 $x-y=p$。

由于转动第 $i$ 个和第 $w-i+1$ 个转轮不会影响其他转轮，因此只需求出 $x+y$ 的最小值。

由于扩展欧几里得算法求出的解有正有负，因此需要分类讨论。

若 $p \ge 0$，则 $x=y+p$，此时 $x+y=2y+p$。显然最小值在 $y=0$ 且 $p$ 为不定方程最小非负整数解时取到，为 $p$。

若 $p<0$，则设 $p_0=-p$，有 $y-x=p_0$，即 $x+y=2x+p_0$，显然最小值在 $x=0$ 且 $p_0$ 为最大负整数解的相反数，即 $p$ 取到最大负整数解时取到，为 $p_0$。

因此，只需取最小非负整数解和最大负整数解的相反数中较小值即可。

对于不定方程 $Dx+Ny=C$，我们有 $x=x_0-\frac{N}{(D,N)}t$，其中 $x_0$ 为一个特解，$t$ 为任意整数。因此，若求最小非负整数解，只需找到最大的 $t$ 使得 $x$ 为正整数。易证此时 $x=x_0 \bmod n_0$，其中 $n_0=\frac{N}{(D,N)}$，所以最小非负整数解为 $x=x_0 \bmod n_0$。显然，最大负整数解为 $(x_0 \bmod n_0)-n_0$，所以最大负整数解的相反数为 $n_0-(x_0 \bmod n_0)$。

综上，对于第 $i$ 个转轮和第 $w-i+1$ 个转轮，最少需要转 $\min(x_0 \bmod n_0,n_0-(x_0 \bmod n_0))$ 次。

# 代码


```cpp
#include<bits/stdc++.h>
#define N 2001
using namespace std;
long long x,y;
long long gcd(long long a,long long b){
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
void exgcd(long long a,long long b){
	if(b==0){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b);
	long long t=x;
	x=y;
	y=t-a/b*y;
}
long long ans=0;
long long a[N];
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		ans=0;
		cout<<"Case #"<<o<<": ";
		int w,yes=1;
		long long n,d;
		cin>>w>>n>>d;
		for(int i=1;i<=w;i++){
			cin>>a[i];
		}
		long long g0=gcd(n,d);
		for(int i=1;i<=w/2;i++){
			if((a[i]-a[w-i+1])%g0!=0){
				yes=0;
				cout<<"IMPOSSIBLE"<<endl;
				break;
			}
			exgcd(d,n);
            long long n0=n/g0;
			x=x*(((a[w-i+1]-a[i])/g0)%n0)%n0;
			//cout<<x<<" "<<y<<endl;
			//int nas0=ans;
			if(x>=0){
				x%=n0;
				ans+=min(x,n0-x);
			}
			else{
				long long x0=x+n0*(ceil((double)(-x)/(double)n0));
				//cout<<x0<<endl;
				ans+=min(x0,n0-x0);
			}
			//cout<<ans-nas0<<endl;
		}
		if(yes){
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

