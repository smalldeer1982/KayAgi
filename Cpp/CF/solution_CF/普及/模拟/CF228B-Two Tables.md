# Two Tables

## 题目描述

你有两个矩阵，尺寸分别为 $n_a × m_a$ 和 $n_b × m_b$，每个元素由 $0$ 和 $1$ 构成，下标从 $1$ 开始。
请求出满足
$\sum_{\begin{subarray}{l} \\i,j \end{subarray}}
a_{i,j} \cdotp b_{i+x,j+y}$ 的 $x,y$，其中 $1 ≤ i ≤ n_a, 1 ≤ j ≤ m_a, 1 ≤ i + x ≤ n_b, 1 ≤ j + y ≤ m_b$ 。

## 样例 #1

### 输入

```
3 2
01
10
00
2 3
001
111
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
3 3
000
010
000
1 1
1
```

### 输出

```
-1 -1
```

# 题解

## 作者：Eason_cyx (赞：0)

题意中有一个小坑：在这个求和的式子里面，不一定所有的 $(i+x)$ 和 $(j+y)$ 都满足条件，只加上满足条件的即可。

枚举 $x$ 和 $y$（注意 $x$ 和 $y$ 可能是负数），然后在遍历整个数组，用变量记录最大值即可。代码也很好写。

时间复杂度为 $O(n^4)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[55][55],b[55][55];
int main() {
    int na,ma; cin >> na >> ma;
    for(int i = 1;i <= na;i++) {
        for(int j = 1;j <= ma;j++) {
            scanf("%01d",&a[i][j]);
        }
    }
    int nb,mb; cin >> nb >> mb;
    for(int i = 1;i <= nb;i++) {
        for(int j = 1;j <= mb;j++) {
            scanf("%01d",&b[i][j]);
        }
    }
    long long maxn = -0x7fffffffffff,maxx = -1,maxy = -1;
    for(int x = min(-nb,-na);x <= max(nb,na);x++) {
        for(int y = min(-mb,-ma);y <= max(mb,ma);y++) {
            bool flag = true;
            long long ans = 0;
            for(int i = 1;i <= na;i++) {
                for(int j = 1;j <= ma;j++) {
                    if((i+x) > nb || (j+y) > mb || (i+x) < 1 || (j+y) < 1) {
                        continue;
                    }
                    else ans += 1ll * a[i][j] * b[i+x][j+y];
                }
            }
            if(flag) {
                if(ans > maxn) {
                    maxn = ans;
                    maxx = x;
                    maxy = y;
                }
            }
        }
    }
    cout << maxx << ' ' << maxy << endl;
    return 0;
}
```

---

## 作者：RE_Prince (赞：0)

# CF228B Two Tables 


[link](https://www.luogu.com.cn/problem/CF228B)


## Sol



这题其实就是大模拟。


思路是枚举外层的 $x,y$，因为他要统计 $a_{i,j}\times b_{i+x,j+y}$ 的和，因此外层枚举 $x,y$ 比较方便。注意一下，数组开多大用多大，下标不能是负数，别越界了！


内层我们用一个变量来记录当 $x,y$ 分别等于多少时的和，最后取一个最大，并记录最大值出现的位置。要充分枚举外层的 $x,y$，比如从 $\min(-a,-c)$ 到 $\max(a,c)$ 是最好的选择，因为它将 $x,y$ 的所有取值都考虑到了。如果考虑不全，很容易 WA。


代码很好写了：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k,ansx,ansy;
int a,b,c,d;
int x[100][100],y[109][100];
signed main() 
{
	cin>>a>>b;
	char ch;
	for(i=1;i<=a;i++)
		for(j=1;j<=b;j++) cin>>ch,x[i][j]=(ch^48);
	cin>>c>>d;
	for(i=1;i<=c;i++)
		for(j=1;j<=d;j++) cin>>ch,y[i][j]=(ch^48);
	for(i=min(-c,-a);i<=max(c,a);i++)//充分枚举x
	{
		for(j=min(-b,-d);j<=max(b,d);j++)//充分枚举y
		{
			int sum=0;
			for(int l=1;l<=max(a,c-i);l++)//注意这里也要取max
				for(int r=1;r<=max(b,d-j);r++)//同上
					if(l>=0&&r>=0&&l+i>=0&&r+j>=0&&l<=a&&r<=b&&l+i<=c&&r+j<=d) sum+=x[l][r]*y[l+i][r+j];//重点：判断是否越界
			if(sum>=k) k=sum,ansx=i,ansy=j;//记录最大值位置
		}
	}
	cout<<ansx<<" "<<ansy;
	return 0;
}
```

---

