# [ICPC 2022 Xi'an R] Clone Ranran

## 题目描述

然然需要准备一场有 $c$ 个问题的比赛！他可以进行两种操作：

- 在 $a$ 分钟内克隆一个自己；
- 在 $b$ 分钟内准备好一个问题。

克隆的然然也可以进行上述操作，但然然不能同时进行这两个操作。

然然希望尽快准备好比赛，但是他很懒，所以他让你求出准备比赛的最小分钟数。

共有 $T$ 组数据。

$1\leq T\leq 10 ^ 5$，$1\leq a, b, c\leq 10 ^ 9$。

## 样例 #1

### 输入

```
5
1 1 1
2 3 3
9 9 9
3 26 47
1064 822 1048576
```

### 输出

```
1
7
45
44
21860
```

# 题解

## 作者：lailai0916 (赞：6)

## 原题链接

- [洛谷 P9360 [ICPC2022 Xi'an R] Clone Ranran](https://www.luogu.com.cn/problem/P9360)

## 解题思路

1. 显然，操作一在操作二之前进行更具性价比。因此，最合理的策略是优先执行若干次操作一，然后再进行操作二。

2. 可以枚举操作一的执行次数：

- 如果执行 $n$ 次操作一，可以得到 $2^n$ 个人，所需时间为 $n\cdot a$。
- 这 $2^n$ 个人出 $c$ 道问题，所需时间为 $\left\lceil\frac{c}{2^n}\right\rceil\cdot b$。

3. 最多只会进行 $30$ 次操作一，因为 $2^{30}>10^9$ 人已经足够多。通过枚举所有可能的执行次数，计算每种情况下所需的总时间，并取最小值，即 $\min_{n=0}^{30} (n\cdot a+\left\lceil\frac{c}{2^n}\right\rceil\cdot b)$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const ll inf=0x3f3f3f3f3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		ll a,b,c;
		cin>>a>>b>>c;
		ll ans=inf;
		for(int i=0;i<=30;i++)
		{
			ans=min(ans,i*a+(c+(1ll<<i)-1)/(1ll<<i)*b);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Lovely_Elaina (赞：1)

设当前有 $x$ 个 Ranran。循环若干次，每次都自我克隆一下。

贪心，如果这次出题，不如先克隆一次再出题，那么就不出题。

通过模拟可以知道，当前为第 $i$ 次循环，那么下次出题总共花 $a\times i+b\times({(c-1)\over x}+1)$ 的时间。

实际上题目是很简单的，建议自行模拟。

```cpp
#include <iostream>
// #include <bits/stdc++.h>
// #define abs(a) (a<0?-a:a)
// #define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
// #define int __int128
#define int long long
#define endl '\n'
using namespace std;

int a,b,c;
int t,mi;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> t;
    while(t--){
        mi = (int)1e15;
        cin >> a >> b >> c;

        int x = 1;
        for(int i = 0; i <= 34; i++){
            mi = min(mi,a*i+b*((c-1)/x+1));
            x *= 2;
        }
        
        cout << mi << endl;
    }
    return 0;
}
```

---

## 作者：Smg18 (赞：0)

~~发现一般的贪心都有两个及以上的条件。~~

如果本次如果要准备题目，可以试试先克隆自己，再准备，这样可以下次补回题的同时多个人。

我们可以循环模拟自己是要克隆还是准备，所以循环最大次数就行（这里循环可以循环三十四次，数据也到不了三十五次，也可是省时间循环二的次方数）。

通过模拟，变量 $i$ 为单位时间，下次出题时间公式如下。

```
maxn=min(maxn,i*a+(c+(1<<i)-1)/(1<<i)*b);
```

注意事项在代码里。

所以代码是：

```cpp
#include<iostream>
#include<cmath>
//#include<windows.h>
//nth_element
//#define int long long
#define ll long long//一定要看数据范围，否则RE
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define C continue
using namespace std;
const int N=1e5+10,NN=1e3+10;//警钟敲烂
ll n,m,k,x,y,cnt,len,T,ans;
ll minn=0x3f3f3f,maxn=0;
ll arr[N];
signed main(){
	Test;
	cin>>T;
	
	while(T--){
		ll a,b,c;
		cin>>a>>b>>c;
		maxn=b*c;//初始有值
		for(int i = 1;1<<i-1<=c;i++){//选择省时间
			maxn=min(maxn,i*a+(c+(1<<i)-1)/(1<<i)*b);
		}
		cout<<maxn<<"\n";//记得最大值
	}
	return 0;
}
```

---

