# Mister B and Angle in Polygon

## 题目描述

在一个边为 $n$ 的正凸多边形上，有一个角 $a$。

  现在要找到三个不同的顶点 $v1$ , $v2$ , $v3$ 使得 $∠ v1 v2 v3$ （其中 $v2$ 是角度的顶点，并且 $v1$ 和 $v3$ 位于其两侧）尽可能接近 $a$（换句话说，该值应该尽可能小）。

 如果有多个最优解，可以输出**任意一个**。

## 样例 #1

### 输入

```
3 15
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
4 67
```

### 输出

```
2 1 3
```

## 样例 #3

### 输入

```
4 68
```

### 输出

```
4 1 2
```

# 题解

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/CF820B)

## 题意

给定一个正 $n$ 边形和一个角度 $a$。在正 $n$ 边形正选三个不同的点 $v_1,v_2,v_3$，使 $\angle v_1v_2v_3$ 最小，求这三个点。点的序号按顺时针排列。

## 思路

根据小学知识，我们知道：$n$ 边形的内角和为 $(n-2) \times 180\degree$，其中一个角的度数为 $\frac{(n-2)\times 180\degree}{n}$，将其中一个点向其它所有点连边，把这个角分成 $(n-2)$ 个相等的部分，每一个部分的度数均为 $\frac{180\degree}{n}$。

由于这是一个正多边形，将点的编号顺时针旋转过后答案不变，那么不妨设 $v_1=1,v_2=2$，然后在 $[3,n]$ 中找到 $v_3$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/xzegqhof.png)

如图，如果 $a\le\frac{180\degree}{n}$，那么直接输出 `1 2 n`。

![](https://cdn.luogu.com.cn/upload/image_hosting/31ndv4sn.png)

如图，如果 $a\ge\frac{(n-2)\times 180\degree}{n}$，那么直接输出 `1 2 3`。

除去这两种情况，容易得到一个不等式 $\angle12n < \angle12(n-1) < \angle12(n-2)< \dots < \angle12i \le a \le \angle12(i-1) < \dots < \angle123$。

那么答案一定是 `1 2 i` 和 `1 2 (i - 1)` 中的一个。

我们可以从 $n$ 到 $3$ 倒序遍历，求出当前最小的 $\lvert \angle12i-a \rvert$，当当前的 $\lvert \angle12i-a \rvert$ 大于当前最小的 $\lvert \angle12k-a \rvert$，就进入了上面不等式的 $(i-1)$ 到 $3$ 那一段，可以直接输出结果 $k$。

但是由于上面不等式 $[n,i]$ 段和 $[i-1,3]$ 段的关于 $\lvert \angle12i-a \rvert$ 值的单调性，当满足输出答案的条件时 $k$ 必定等于 $i+1$，所以我们不用记录 $k$，直接输出 `1 2 (i + 1)` 即可。

具体实现见代码，~~自认为写的很清晰~~。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;

double n, a, m, k, maxa = 1e9;

int main() {
  cin >> n >> a;
  m = (n - 2) * 180.0 / n, k = 180.0 / n;
  if (a <= k) {
    cout << "1 2 " << n << '\n';
  } else if (a >= m) {
    cout << "1 2 3\n";
  } else {
    for (int i = n, j = 1; i >= 3; i--, j++) {
      double d = k * j;
      if (abs(d - a) < maxa) {
        maxa = abs(d - a);
      } else {
        cout << "1 2 " << i + 1 << '\n';
        return 0;
      }
    }
    cout << "1 2 3\n";
  }
  return 0;
}
```

---

## 作者：xzggzh1 (赞：1)

题意：

有一个正 $n$ 边形，问哪 $3$ 个点形成的角度最接近 $a$ 。

---

这里可以做一个正 $n$ 边形的外接圆，然后根据同弧所对的角相等这一个初中数学的知识，可以知道：这个角的大小只和他所对的弧长有关。又由于是正 $n$ 边形，所以最多只有 $n$ 个不同大小的角。

然后枚举就好了。

```cpp
int main()
{
    int n,a;
    while(cin>>n>>a)
    {
        double deg=180.0*(n-2)/n;
        int ans=3;
        double ang=(180-deg)/2;
        double tmp;
        for(int i=4;i<=n;i++)
        {
            tmp=(180.0-deg)*(i-2)/2;
            if(abs(ang-a)>abs(tmp-a))
            {
                ang=tmp;
                ans=i;
            }
        }
        cout<<"2 1 "<<ans<<endl;
    }
}
```

---

## 作者：nydzsf_qwq (赞：0)

这题和我昨天做的 CF1096C 非常像。

和那题一样，我们可以得到一个大小为 $\dfrac{(n-2)\times180^\circ}{n}$ 的内角被等分成了 $n-2$ 份，每份 $\dfrac{180^\circ}{n}$。

对 $\alpha$ 分类，分成比 $\dfrac{(n-2)\times180^\circ}{n}$ 大，比 $\dfrac{180^\circ}{n}$ 小和在这两者之间。

第一类必须是一整个内角，输出 $1\ 2\ 3$ 即可。

第二类必须是只有一份，输出 $1\ 2\ n$ 即可。

第三类只要算出离 $\alpha$ 最接近的份数，记为 $t$，输出 $1\ 2\ n-t+1$ ，这个只要判断是比 $\alpha$ 大的里最小的还是比 $\alpha$ 小的里最大的，用取整就可以算了。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,alpha;
int main() {
	cin>>n>>alpha;
	double tmp1=180.0/n,tmp2=(n-2)*180.0/n;
	if(alpha>=tmp2) printf("1 2 3");
	else if(alpha<tmp1) printf("1 2 %d",n);
	else {
		int tmp3=alpha/tmp1;
		double tmp4=alpha-tmp3*tmp1,tmp5=(tmp3+1)*tmp1-alpha;
		if(tmp4<tmp5) printf("1 2 %d",n-tmp3+1);
		else printf("1 2 %d",n-tmp3);
	}
	return 0;
}
```

---

