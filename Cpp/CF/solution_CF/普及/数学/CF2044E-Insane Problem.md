# Insane Problem

## 题目描述

Wave 有五个整数 $k$ 、 $l_1$ 、 $r_1$ 、 $l_2$ 和 $r_2$ ，她想要你帮她数出有多少对有序数对 $(x, y)$ 满足以下条件：

- $l_1 \leq x \leq r_1$ .
- $l_2 \leq y \leq r_2$ .
- 存在一个非负整数 $n$ ，使得 $\frac{y}{x} = k^n$ 。

## 说明/提示

对于第三组测试样例，以下有序数对是符合条件的：

- $(5,15)$
- $(5,45)$
- $(6,18)$
- $(6,54)$
- $(7,21)$
- $(7,63)$

对于第四组测试样例，唯一有效的有序数对是 $(1,1\,000\,000\,000)$

## 样例 #1

### 输入

```
5
2 2 6 2 12
2 1 1000000000 1 1000000000
3 5 7 15 63
1000000000 1 5 6 1000000000
15 17 78 2596 20914861```

### 输出

```
12
1999999987
6
1
197```

# 题解

## 作者：OIerWu_829 (赞：5)

[洛谷传送门](https://www.luogu.com.cn/problem/CF2044E) / [Codeforces 传送门](https://codeforces.com/problemset/problem/2044/E)

首先特判一下 $k=1$ 的情况，对于所有满足 $l1\le x\le r1$ 和 $l2\le y\le r2$ 的 $x$ 和 $y$，都有 $\dfrac{y}{x}=1^n=1$，所以有序对 $(x,y)$ 的数量就是 $\max(0,\min(r1,r2)-\max(l1,l2)+1)$。

否则就需要处理一下。我们用 $pos$ 表示 $k^n$ 的值，然后通过 `while` 循环（只要 $pos\le r2$ 就一直循环）先计算出 $x$ 的上下限：

+ 下限：$lb=\max(l1,(l2+pos-1)\div pos)$，这是为了找到满足 $y=x\times pos$ 且 $y\ge l2$ 的最小 $x$ 值，并与 $l1$ 取 $\max$ 确保 $x\ge l1$；
+ 上限：$ub=\min(r1,r2\div pos)$，这是为了找到满足 $y=x\times pos$ 且 $y\le r2$ 的最大 $x$ 值，并与 $r1$ 取 $\min$ 确保 $x\le r1$。

然后我们统计满足条件的 $x$ 的数量，如果 $lb\le ub$，说明在这个 $pos$（即 $k^n$）下，存在满足条件的 $x$ 值，数量为 $ub-lb+1$，并将其累加到答案中。然后更新 $pos$，检查 $pos$ 是否超过 $\dfrac{r2}{k}$，如果超过则说明继续乘以 $k$ 会使 $pos$ 超过 $r2$，跳出循环；否则将 $pos$ 更新为下一个 $k$ 的幂次，也就是把 $pos$ 乘上 $k$。最后输出答案即可。

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

int main()
{
	LL T;
	cin >> T;
	while (T--)
	{
		LL k, l1, r1, l2, r2;
		cin >> k >> l1 >> r1 >> l2 >> r2;
		if (k == 1)
		{
			cout << max(0LL, min(r1, r2) - max(l1, l2) + 1) << "\n";
			return 0;
		}
		LL ans = 0, pos = 1;
		while (pos <= r2)
		{
			LL lb = max(l1, (l2 + pos - 1) / pos);
			LL ub = min(r1, r2 / pos);
			if (lb <= ub) ans += ub - lb + 1;
			if (pos > r2 / k) break;
			pos *= k;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：yr409892525 (赞：4)

## CF2044E 题解
题目要求有多少对
$x \div y=k^n$。             
不妨变形为 $x=y\div k^n$。              
我们可以枚举 $k^n$，上限 $k^n\le r2$。               
因为 $y$ 肯定是 $k^n$ 的倍数，所以如果我们能确定 $x$ 的范围就好办了。                 
因为 $y \le r2$，所以 $x \le \min(r2\div k^n,r1)$。            
因为 $y \ge l2$，所以 $x \ge \max(l2\div k^n,l1)$，因为取不到 $l2\div k^n$，所以要向上取整。            

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,m,q;
int a[N],b[N];
struct code{
    int x,y;
};
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>q;
    while(q--){
        int k,l,r,ll,rr;
        cin>>k>>l>>r>>ll>>rr;
        int ans=1,sum=0;
        while(ans<=rr){
            int rt=min(r,rr/ans),lt=max(l,(ll+ans-1)/ans);
            sum+=max(0ll,rt-lt+1);
            ans*=k;
        }
        cout<<sum<<"\n";
    }
	return 0;
}
```

---

## 作者：ohjun (赞：2)

## 思路分析
首先我们将 $\frac{y}{x} = k^n$ 转化为 $x = \frac{y}{k^n}$ 方便后续思考。考虑枚举 $n$，我们发现对于每个 $k^n$，每个 $x$ 对应的都是一个唯一的 $y$，且 $x$ 仅在一段区间内有解。所以我们求出当前 $k^n$ 下 $x$ 的上界和下界。上界为 $y$ 可以取到的最大值 $r_2$ 除 $k^n$，注意此时算出的上界可能大于 $x$ 本身的上界，所以还要将算出来的上界与 $r_1$ 做一次 $\min$。下界与上界基本同理，把 $r$ 换成 $l$，$\min$ 改成 $\max$，留意向上取整即可。还需要注意在一些 $k^n$ 下可能解是负数，所以要对算出来的解和 $0$ 做 $\max$，防止答案的值减小。

最后写一下公式：
$$$
  ans = \sum_{n = 0}^{\lfloor \log_kr_2 \rfloor} \max(0, \min(\lfloor \frac{r_2}{k^n} \rfloor, r_1) - \max(\lceil \frac{l_2}{k^n} \rceil, l_1) + 1)
$$$
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t, k, l1, l2, r1, r2;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> k >> l1 >> r1 >> l2 >> r2;
		ll ans = 0, now = 1;
		while(now <= r2)
		{
			ans += max(min(r2 / now, r1) - max((ll)ceil(double(l2) / now), l1) + 1, 0LL);
			now *= k;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Yannik (赞：2)

## 题目大意：
已知 $𝑙1≤𝑥≤𝑟1 $ , $𝑙2≤𝑦≤𝑟2$ 。

求有多少对 $(x,y)$ 满足 $𝑦/𝑥=𝑘^𝑛$ , $n≥0$ 。

## 思路：
一道很好的思维题。 
我们不能直接枚举 $l,r$ , 但我们可以枚举 $n$ , 来找到所满足的最小的 $l$ 和 最大的 $r$ 。

然后 $ans$ 每次累加对应的 $rmax-lmin+1$ 就好啦。

剩下的注意边界处理就行了。

## 赛时代码：
```cpp
#include<iostream>
#include<algorithm>
#define int long long 
using namespace std;
const int N = 2e5 + 10;
int T;
signed main(){
    cin.tie(0)->ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        int k,l1,l2,r1,r2,ans=0,now=1;
        cin>>k>>l1>>r1>>l2>>r2;
        for(int n=1;n<=60;n++){
            if(now*l1>r2) break;
            int a=max(l2/now+(l2%now>0),l1);
            int b=min(r2/now,r1);
            ans+=max(b-a+1,0ll);
            now*=k;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：DoubleQLzn (赞：1)

我们可以求出 $k$ 的所有非负整数次幂 $x_1,x_2,\cdots,x_{log_k{10^9}}$。然后枚举所有满足要求的数，对于任意 $x_i$，如果 $a$ 满足要求，应该满足下面四个不等式：

- $x_ia\geq l2$
- $x_ia\leq r2$
- $a\geq l_1$
- $a\leq r_2$

不妨移项，$a\geq l2\div a$，$a\leq r2\div a$，前者上取整，后者下取整，就是前两个不等式的解集。

最后求两个解集的交叉部分即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,k,l1,r1,l2,r2;
int jiaocha(int l1,int r1,int l2,int r2)
{
	int s = min(r1,r2) - max(l1,l2) + 1;
	return max(0ll,s);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> k >> l1 >> r1 >> l2 >> r2;
		vector<int> g;
		int now = 1;
		while (now <= 1000000000)
		{
			g.push_back(now);
			now = now * k;
		}
		int ans = 0;
		for (auto a : g)
		{
			int down = ceil(l2 * 1.0 / a),up = r2 / a;
			ans = ans + jiaocha(down,up,l1,r1);
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：_yang_yi_bo_ (赞：1)

提供一种不同的做法。

由于 $y=x \times k^n$，我们可以枚举 $n$。

有一种思路：在 $l_1$ 到 $r_1$ 的范围内枚举 $x$，判断 $l_2\le x\times k^n \le r_2$ 是否满足条件。

容易发现单调性，可以二分两次求出 $x$ 的取值范围 $l_{ans} \le x \le r_{ans}$ 将答案加 $r_{ans}-l_{ans}+1$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,k,lx,rx,ly,ry;
signed main(){
    cin>>t;
    while(t--){
        cin>>k>>lx>>rx>>ly>>ry;
        int cnt=1,ans=0;
        while(cnt<=ry){
            int lt=lx-1,rt=rx+1,ll,rr;
            while(lt+1<rt){
                int mid=(lt+rt)>>1;
                if(mid*cnt>=ly){
                    rt=mid;
                }else{
                    lt=mid;
                }
            }ll=rt;
            lt=lx-1,rt=rx+1;
            while(lt+1<rt){
                int mid=(lt+rt)>>1;
                if(mid*cnt<=ry){
                    lt=mid;
                }else{
                    rt=mid;
                }
            }rr=lt;
            if(ll<=rr){
                ans+=(rr-ll+1);
            }cnt*=k;
        }cout<<ans<<"\n";
    }
    return 0;
} 
```

---

## 作者：wflhx2011 (赞：0)

因为是 Div.4 的 E，所以不可能太难，考虑枚举 $n$，对于单次询问时间复杂度为 $O(\log r_2)$ 。

问题在于如何 $O(1)$ 求出满足条件的 $(x,y)$。因为枚举 $n$，所以等式右边就确定了。

考虑求出使 $y$ 合法且自身合法的 $x$，分别确定它的下界和上界。

- 下界首先满足 $l_1\le x$，然后要使 $y$ 合法需要 $\frac{l_2}{k^n}\le x$，又因为是整数所以将 $ \frac{l_2}{k^n}$ 上取整。下界就是 $\max(l_1,\lceil \frac{l_2}{k^n}\rceil)$。

- 上界类似，可以求出应是 $\min(r_1, \lfloor \frac{r_2}{k^n} \rfloor)$。

求出一个范围，合法答案就是这个范围的长度。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long k,l1,l2,r1,r2,ans=0,x=1;	  
		cin>>k>>l1>>r1>>l2>>r2;
		long long l3,r3;
		while(x<=r2)
		{
			l3=max(l1,(long long)ceil(l2*1.0/x)),r3=min(r1,r2/x);
			if(l3<=r3)
				ans+=r3-l3+1;	
			x*=k;
		}
		cout<<ans<<endl;
	}
 	return 0;
}


```

---

