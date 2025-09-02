# Bridge Renovation

## 题目描述

最近，Monocarp 开始在他家附近的一个公园担任董事。公园很大，所以它有一条小河甚至将其分成几个区域。这条河上建了几座桥。其中三座桥特别古老，需要维修。

所有三座桥的长度相同，但宽度不同。它们的宽度分别为 $18$，$21$，$25$ 个单位。

在公园翻新过程中，Monocarp 必须用新木板替换用作桥梁表面的旧木板。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2038L/85af0decbad9801e010ac724aebc06474601925e.png)

木板的标准长度为 $60$ 个单位。Monocarp 已经知道他每座桥都需要 $n$ 块木板。但是由于桥梁的宽度不同，第一座桥需要 $n$ 块长度为 $18$ 的木板，第二座桥需要 $n$ 块长度为 $21$ 的木板，最后一座桥需要 $n$ 块长度为 $25$ 的木板。

负责装修的工人可以将木板切成小块，但拒绝加入木板，因为它会产生薄弱点并且看起来很丑。

Monocarp 想尽可能少地购买木板，但难以计算所需的木板数量。你能帮他吗？

## 说明/提示

在第一个例子中，可以将一块长度为 $60$ 的木板切割成三块长度为 $25$、$18$ 和 $17$ 的木板，并将另一块长度为 $60$ 的木板切割成两块长度为 $39$ 和 $21$ 的木板。这样，Monocarp 将拥有所有需要的木板。

## 样例 #1

### 输入

```
1```

### 输出

```
2```

## 样例 #2

### 输入

```
3```

### 输出

```
4```

## 样例 #3

### 输入

```
1000```

### 输出

```
1167```

# 题解

## 作者：QianXiquq (赞：5)

考虑一个 $60$ 个长度的块可以通过哪些种类来组成。

能够发现以下状况:

$$ 60\ge \left\{\begin{matrix}
18
 \\21
 \\25
 \\18+18=36
 \\21 +21=42
 \\25+25=50
 \\18+18+18=54
 \\18+18+21=57
 \\21+21+18=60

\end{matrix}\right.$$

对于一个块，我们贪心地希望将其分为更多可用的块，根据问题陈述这显然是正确的。

因此，我们发现 $21+21+18$ 浪费了最少的长度，同时可以分为最多数块。将其与 $18+18+21$ 结合在一起，我们发现我们可以使用 $2$ 个块来解决 $3$ 套的问题。我们发现在这种情况下，已经没有更好的解决方案了。

因此，我们通过这样做来解决这个问题：
首先，如果 $ n\ge3 $，我们使用前面提到的解决方案。

然后，我们将其余的套标记为 $\texttt{left}$。

如果 $ \texttt{left}=1 $，我们使用 $1$ 个块 $18+21$，已经没有更好的解决方案。

如果 $ \texttt{left}=2 $，那么我们最好使用 $2$ 个块 $21+21+21+18$ 和 $18$，留 $60-18=42>25$，以 $25$ 使用。通过这样做，要处理的 $25$ 从 $n$ 减少到 $n-1$。

最后，我们需要 $ \left \lceil n/2 \right\rceil $（如果 $\texttt{left}=2$，则 $ \left \lceil (n-1)/2 \right\rceil $) 块来处理其余的 $25$。

到目前为止我们已经解决了这个问题。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
 
using namespace std;
 
int main(){
    int n; cin >> n;
    ll cnt = 0;
    cnt += floor((double)n / 3) * 2;
    
    int left = n % 3;
    if (left == 1)
        cnt++;
    if (left == 2){
        cnt += 2;
        n--;
    }
    
    cnt += ceil((double)n / 2);
 
    cout << cnt << '\n';
    return 0;
}
```

---

## 作者：Vct14 (赞：1)

upd：修改了几处笔误。

下文将宽为 $18$ 的木板称为 A，宽为 $21$ 的木板 B，宽为 $25$ 的木板为 C，宽为 $60$ 的木板称为 D。

因为一块 D 可以做 $3$ 块 A，即 $60=18+18+18+6$，而只可以做 $2$ 块 B 或 C。所以我们优先凑 B 和 C。

一块 D 可以做 $2$ 块 B，即 $60=21+21+18$（显然我们凑 B 时要优先选这一种方案，因为这可以多做 $1$ 块 A）；也可以做 $2$ 块 C，即 $60=25+25+10$；还可以做 B 和 C 各 $1$ 块，即 $60=21+25+14$。

若 $n$ 为偶数，$n$ 块 B 和 $n$ 块 C 共需要 $\dfrac{n}{2}\times2=n$ 块 D。这时我们已经有了 $\dfrac{n}{2}$ 块 A，还需要 $\dfrac{n}{2}$ 块 A，即$\left\lceil\dfrac{\frac{n}{2}}{3}\right\rceil=\left\lceil\dfrac{n}{6}\right\rceil$ 块 D。此时答案为 $n+\left\lceil\dfrac{n}{6}\right\rceil$。

若 $n$ 为奇数，$n$ 块 B 和 $n$ 块 C 共需要 $\dfrac{n-1}{2}\times2+1=n$ 块 D。这时我们已经有了 $\dfrac{n-1}{2}$ 块 A，还需要 $\dfrac{n+1}{2}$ 块 A，即 $\left\lceil\dfrac{\frac{n+1}{2}}{3}\right\rceil=\left\lceil\dfrac{n+1}{6}\right\rceil$ 块 D。由于 $n$ 为奇数，有 $\left\lceil\dfrac{n+1}{6}\right\rceil=\left\lceil\dfrac{n}{6}\right\rceil$。因此此时答案也为 $n+\left\lceil\dfrac{n}{6}\right\rceil$。

综上，答案为 $n+\left\lceil\dfrac{n}{6}\right\rceil$。

---

## 作者：NEKO_Daze (赞：1)

[洛谷CF2038L](https://www.luogu.com.cn/problem/CF2038L) || [CodeForces 2038 L](https://codeforces.com/contest/2038/problem/L)

### 简要题意

一共有三座桥需要维修。一块木板的标准长度为 $60$ 个单位。每座桥需要 $n$ 块木板。但由于桥的宽度不同，第一座桥需要长度为 $18$ 的 $n$ 块木板，第二座桥需要长度为 $21$ 的 $n$ 块木板，最后一座桥需要长度为 $25$ 的 $n$ 块木板。可以将木板切割成若干部分，但不能将木板连接起来。

最少需要多少的木板？

### 思路

考虑贪心。

对于长度为 $25$ 的木板，一块完整的木板可以分成两块长度为 $25$ 的木板，因此需要 $\lceil\frac{n}{2}\rceil$ 块木板。

对于长度为 $21$ 的木板，可以将一块木板拆成 $21+21+18$，因此需要 $\lceil\frac{n}{2}\rceil$ 块木板，并多出 $\lceil\frac{n}{2}\rceil$ 块长度为 $18$ 的木板。

对于长度为 $18$ 的木板，还需要 $\lceil\frac{n}{2}\rceil$ 块长度为 $18$ 的木板，一块完整的木板可以拆成 $18\times 3$，因此还需要 $\lceil \frac{\lceil\frac{n}{2}\rceil}{3}\rceil=\lceil\frac{n}{6}\rceil$ 块木板。

所以答案为 $\lceil\frac{n}{2}\rceil+\lceil\frac{n}{2}\rceil+\lceil\frac{n}{6}\rceil=n+\lceil\frac{n}{6}\rceil$。

极简代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    cout << n + ceil(n / 6.0);
}
```

---

## 作者：MournInk (赞：1)

考虑如何尽量利用长度为 $60$ 的木板。

不难发现，最佳的利用方式为：

- $21 + 21 + 18 = 60$
- $18 + 18 + 18 = 54$
- $25 + 25 = 50$

其他的方案一定劣于以上三种方案。

继续思考，观察到可以通过 $7$ 根长度为 $60$ 的木板裁出长度为 $18$、$21$、$25$ 的木板各 $6$ 根，此时最优。

> 方案为：$(21 + 21 + 18) \times 3 + (25 + 25) \times 3 + (18 + 18 + 18) \times 1$

则对于**每** $6$ 组木板，我们都会使用 $7$ 根长度为 $60$ 的木板，且这一定是最优的。

那么剩下的 $0 \sim 5$ 组也不难通过模拟得到：

1. 裁出 $1$ 组需要 $2$ 根；
2. 裁出 $2$ 组需要 $3$ 根；
3. 裁出 $3$ 组需要 $4$ 根；
4. 裁出 $4$ 组需要 $5$ 根；
5. 裁出 $5$ 组需要 $6$ 根。

那么答案显而易见，为 $\lfloor \frac{n}{6} \rfloor \times 7 + a_{n \bmod 6}$，其中 $a_i$ 为模拟得到的根数。

进一步化简可以得到最终答案为：$n + \lceil \frac{n}{6} \rceil$。


> 本文来自：
> ![做干净的奥赛](https://img.picgo.net/2024/11/19/950f46f6adff54912eadac7f86ab204670735f7200db90bb.png)
>
> 另附[官方题解](https://codeforces.com/contest/2038/attachments/download/28397/presentation_eng.pdf)。

---

## 作者：AK_400 (赞：0)

首先观察一下一块木板能怎么拆：
$$
21+21+18=60\\
21+18+18=57\\
18+18+18=54\\
25+25=50\\
25+21=46\\
25+18=43\\
$$
那肯定优先拆成 $3$ 个，这样只有 $21$ 和 $18$ 能拆，于是只对 $21$ 和 $18$ 的桥 dp 就可以了，剩下的除以二上取整就行。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int dp[1005][1005];
void slv(){
    cin>>n;
    int ans=(n+n+n+1)/2;
    for(int i=1;i+i+i<=n+n;i++){
        for(int j=0;j<=n;j++){
            int k=i+i+i-j;
            dp[j][k]=2e9;
            if(j>=1&&k>=2)dp[j][k]=min(dp[j][k],dp[j-1][k-2]+1);
            if(j>=2&&k>=1)dp[j][k]=min(dp[j][k],dp[j-2][k-1]+1);
            if(j>=3)dp[j][k]=min(dp[j][k],dp[j-3][k]+1);
            ans=min(ans,dp[j][k]+(n+n+n-i-i-i+1)/2);
        }
    }
    cout<<ans<<endl;
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：liwenxi114514 (赞：0)

题意：需要多少块宽 $60$ 的木板才能切成 $n$ 块宽 $18$ 的木板、$n$ 块宽 $21$ 的木板、$n$ 块宽 $25$ 的木板。木板只能切割，不能拼接。

思路：首先贪心，想一块木板剩余最少的切法。

$18+21+21=60$

$18+18+18=54$

这两种方法可以用最少的宽 $60$ 的木板，将宽 $18$ 与 $21$ 的数量缩减到 $3$ 以内，接下来在分类讨论就行了。详见代码：

```cpp
    //c%2和c%2==0代表向上取整
    #include<bits/stdc++.h>
    using namespace std;
    int n,a,b,c,ans;
    int main(){
    	cin>>n;
    	a=b=c=n;
    	a-=b/2;
    	ans+=b/2;//a+b+b
    	b%=2;
    	ans+=a/3;//a+a+a
    	a%=3;
    	if(b==0){
    		if(a==0){
    			ans+=c/2+c%2;//c+c
    		}else if(a==1){
    			ans+=(c-1)/2+1+(c%2==0);//a+c再c+c
    		}else{
    			if(c>=2){
    				ans+=2+(c-2)/2+c%2;//a+c两次，再c+c
    			}else{//c=1时 a+c再a
    				ans+=2;
    			}
    		}
    	}else{
    		if(a==0){
    			ans+=(c-1)/2+1+(c%2==0);//b+c再c+c
    		}else if(a==1){
    			if(c==1){
    				ans=2;//a+b再c
    			}else{
    				ans+=(c-2)/2+2+c%2;//a+c再b+c再c+c
    			}
    		}else{ 
    			ans+=c/2+1+c%2;//a+a+b再c+c
    		}
    	}
    	cout<<ans;
    	return 0;
    }
```

---

