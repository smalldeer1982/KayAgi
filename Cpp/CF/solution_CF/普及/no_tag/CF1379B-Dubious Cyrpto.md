# Dubious Cyrpto

## 题目描述

Pasha loves to send strictly positive integers to his friends. Pasha cares about security, therefore when he wants to send an integer $ n $ , he encrypts it in the following way: he picks three integers $ a $ , $ b $ and $ c $ such that $ l \leq       a,b,c \leq r $ , and then he computes the encrypted value $ m = n       \cdot a + b - c $ .

Unfortunately, an adversary intercepted the values $ l $ , $ r $ and $ m $ . Is it possible to recover the original values of $ a $ , $ b $ and $ c $ from this information? More formally, you are asked to find any values of $ a $ , $ b $ and $ c $ such that

- $ a $ , $ b $ and $ c $ are integers,
- $ l \leq a, b, c \leq r $ ,
- there exists a strictly positive integer $ n $ , such that $ n \cdot a + b - c = m $ .

## 说明/提示

In the first example $ n = 3 $ is possible, then $ n \cdot 4 +       6 - 5 = 13 = m $ . Other possible solutions include: $ a = 4 $ , $ b = 5 $ , $ c = 4 $ (when $ n = 3 $ ); $ a = 5 $ , $ b =       4 $ , $ c = 6 $ (when $ n = 3 $ ); $ a = 6 $ , $ b = 6 $ , $ c = 5 $ (when $ n = 2 $ ); $ a = 6 $ , $ b = 5 $ , $ c =       4 $ (when $ n = 2 $ ).

In the second example the only possible case is $ n = 1 $ : in this case $ n \cdot 2 + 2 - 3 = 1 = m $ . Note that, $ n = 0 $ is not possible, since in that case $ n $ is not a strictly positive integer.

## 样例 #1

### 输入

```
2
4 6 13
2 3 1```

### 输出

```
4 6 5
2 2 3```

# 题解

## 作者：wmy_goes_to_thu (赞：7)

这道题也很简单，可以用 $\mathcal O(t \times (r-l))$ 的复杂度解决。

枚举 $a$，显然 $c-b=m~\%~a$，那么有两种情况，也就是 $b=l$ 和 $c=r$ 的情况，判断即可。注意这里的一个小问题：

设 $p=m~\%~a$，那么 $l$ 和 $l+p$ 是一种方案，但是还有一种是 $l+m-p$ 和 $l$，别忘了呀！

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int l,r;
		long long m;
		cin>>l>>r>>m;
		for(int i=l;i<=r;i++)
		{
			int p=i-m%i;
			if(l+p<=r)
			{
				cout<<i<<" "<<l<<" "<<l+p<<endl;
				break;
			}
			if(r-p>=l)
			{
				cout<<i<<" "<<r-p<<" "<<r<<endl;
				break;
			}
			p=i-p;
			if(l+p<=r)
			{
				cout<<i<<" "<<l+p<<" "<<l<<endl;
				break;
			}
			if(r-p>=l)
			{
				cout<<i<<" "<<r<<r-p<<endl;
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Create_Random (赞：1)

发个不一样的思路：

可将原式化为 $na-m=c-b$.

因为 $b$, $c$ 均在 $l$ 到 $r$ 之间。

所以 $\left|na-m\right| \le r-l$.

因为 $m$ 是固定值，

所以我们可以将 $na-m$ 看为一个一次函数。

显然因为 $n>0$,

所以我们可以在枚举 $a$ 的基础上对 $n$ 进行二分，

当 $\left|na-m\right| \le r-l$ 时即为答案。

时间复杂度 $O((r-l)\log mt)$.

注意：

当 $na-m<0$ 时 $b<c$ ,可使 $b=l$, $c=l+na-m$.

当 $na-m>0$ 时 $b>c$ ,可使 $b=r$, $c=r+na-m$.

(也可以是其他数字，只是这样边界处理最为保险）

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long l,r;
long long m;
bool flag;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		flag=0;
		scanf("%lld%lld%lld",&l,&r,&m);
		for(int i=l;i<=r;i++)
		{
			long long left=1,right=m;
			while(left<=right)
			{
				long long mid=(left+right)/2;
				if(abs(mid*i-m)<=r-l)
				{
					if(mid*i-m>=0)
					{
						printf("%d %lld %lld\n",i,l,l+mid*i-m);
					}
					else
					{
						printf("%d %lld %lld\n",i,r,r+mid*i-m);
					}
					flag=1;
					break;
				}
				else if(mid*i-m<=l-r)
				{
					left=mid+1;
				}
				else
				{
					right=mid-1;
				}
			}
			if(flag)
			{
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：bigclever (赞：1)

## 思路：
先将原式化为：
$$n \cdot a-m=c-b$$
发现题目的数据范围允许我们从 $l$ 到 $r$ 枚举一次，那么我们就枚举 $a$ 的值。接下来分为两种情况：

1. $n=\lfloor \frac{m}{a} \rfloor$，此时 $n \cdot a \le m$，即 $b-c=m-n \cdot a$。那么**最有可能合法**的情况就是让 $c=l$，$b=l+m-n \cdot a$ $(b \ge c)$。如果此时 $n \gt 0$ 且 $b \le r$，那么 $(a,b,c)$ 即为原方程的一组合法解。

1. $n=\lceil \frac{m}{a} \rceil$，此时 $n \cdot a \ge m$，即 $c-b=n \cdot a-m$。那么**最有可能合法**的情况就是让 $b=l$，$c=l+n \cdot a-m \bmod a$ $(c \ge b)$。如果此时 $n \gt 0$ 且 $c \le r$，那么 $(a,b,c)$ 即为原方程的一组合法解。

------------
代码按思路模拟即可，过于简单，不放了。

---

## 作者：ka_da_Duck (赞：1)

题目传送门：[CF1379B](https://www.luogu.com.cn/problem/CF1379B)。

思路：由于 $a,b,c$ 都是小于 $5\times10^5$ 的, 所以我们考虑枚 $a$。那么此时 $b-c$ 就等于 $m\bmod a$，$n$ 的值为 $m÷a$ 或 $m÷a+1$。考虑将 $c$ 赋值为 $l$，此时 $b$ 的值就为 $l+m-n_1\cdot a$。或是将 $b$ 赋值为 $l$, 这样的话 $c$ 的值就为 $l+n_2\cdot a-m$ 只需要检查前一个的 $b$ 或是后一个的 $c$ 是否小于 $r$ 即可。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, l, r, m;

void solve() {
	scanf("%lld%lld%lld", &l, &r, &m);
	for (int a = l; a <= r; ++a) { // 枚举 a 
		int n1 = m / a, n2 = m / a + 1;
		if (n1 > 0 && (l + m - n1 * a) <= r) {
			//　判读　n 是否是正整数 
			printf("%lld %lld %lld\n", a, l + m - n1 * a, l);
			break;
		} 
		if (n2 > 0 && (l + n2 * a - m) <= r) {
			printf("%lld %lld %lld\n", a, l, l + n2 * a - m);
			break;
		}
	}
}

signed main() {
	scanf("%d", &t);
	while (t--) solve();
}
```


---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1379B)

因为 $1 \le l \le r \le 5 \times 10 ^5$，所以考虑枚举 $a$。

让枚举后得出的 $b - c$ 的绝对值越小则越优。

对于每一个枚举的 $a$：

1.$b \ge c$ 时，$n = \lfloor \frac{m}{a} \rfloor$ 时最优，此时 $b - c = m \bmod a$。当 $b = r$ 时，如果 $c = r - (m \bmod a) \ge l$，就输出答案。如果 $b - c = 0$，就不要进行下一步，直接 `continue`。

2.$b < c$ 时，$n = \lceil \frac{m}{a} \rceil$ 时最优，此时 $c - b = m - (m \bmod a)$。当 $b = l$ 时，如果 $c = l + m - (m \bmod a) \le r$，就输出答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, l, r, m, n, b_c;//不开long long见祖宗
int main(){
	scanf("%lld", &t);
	while (t--){
		scanf("%lld%lld%lld", &l, &r, &m);
		for (int i = l; i <= r; i++){//枚举a
			n = m / i, b_c = m % i;
			if (b_c <= r - l && n > 0){printf("%lld %lld %lld\n", i, r, r - b_c); break;}//情况1
			if (!b_c) continue;
			n = m / i + 1, b_c = i - m % i;
			if (b_c <= r - l && n > 0){printf("%lld %lld %lld\n", i, l, l + b_c); break;}//情况2
		}
	}
	return 0;
}
```

---

