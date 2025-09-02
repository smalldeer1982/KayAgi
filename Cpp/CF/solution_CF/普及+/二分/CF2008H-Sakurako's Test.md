# Sakurako's Test

## 题目描述

Sakurako 即将参加一场考试，这场考试可用一个整数数组 $n$ 和一个相关任务来描述：

对于给定的整数 $x$，Sakurako 可以多次执行以下操作：

- 选择一个整数 $i$，其中 $1 \le i \le n$，且满足 $a_i \ge x$；
- 将 $a_i$ 的值减少 $x$，即改为 $a_i - x$。

通过这样的操作，她需要找到数组 $a$ 的最小可能中位数 $^{\text{∗}}$。

Sakurako 已知数组的内容，但不清楚整数 $x$ 的值。不过，有人透露在接下来的考试中，$x$ 的值会是给定的 $q$ 个值之一，因此她希望你能帮忙找出每一个可能的 $x$ 所对应的最小中位数。

$^{\text{∗}}$ 对于一个长度为 $n$ 的数组，若 $n$ 是偶数，则中位数是排序后数组中第 $\frac{n+2}{2}$ 个位置的元素；若 $n$ 是奇数，则为第 $\frac{n+1}{2}$ 个位置的元素。

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
2
3
4
5
6 3
1 2 6 4 1 3
2
1
5```

### 输出

```
0 1 1 1 2 
1 0 2```

# 题解

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

给定一个长度为 $n$ 的序列 $a$，你可以每次选择一个 $i$ 满足 $a_i\geq x$ 并且执行 $a_i\gets a_i-x$。

现在给出 $q$ 个询问，每次给出一个 $x$，查询操作之后序列的最小中位数是多少。

$1\leq n,q,\sum n,\sum q\leq 10^5$，$1\leq a_i,x\leq n$。

# 题目思路

把每一个 $a_i$ 都减到 $\lt x$ 的部分肯定不劣。

还是套路性的二分中位数，统计 $\leq mid$ 的个数共有多少即可。

又联想到 $a_i\bmod x=a_i-\lfloor\dfrac{a_i}{x}\rfloor\times x$，按 $\lfloor\dfrac{a_i}{x}\rfloor$ 分类即可。这至多有 $\lfloor\dfrac{n}{x}\rfloor$ 段。

先对 $a_i$ 做前缀和，$sum_i$ 表示 $\leq i$ 有多少数。这样可以 $\mathcal O(1)$ 求出区间内的数的个数。

之后维护两个数 $l,r$，初始 $l\gets 0,r\gets x-1$，之后跳 $l\gets l+x,r\gets r+x$，做一个前缀和就可以算出 $[l,l+mid]$ 内的数的个数。注意前缀和边界问题。

又由于 $\sum\limits_{i=1}^n \frac{n}{i} = n\log n$，所以对于 $x$ 记忆化之后就是本质不同的 $x$，$l\gets l+x,r\gets r+x$ 这个跳的过程至多 $\mathcal O(n\log n)$ 段。加上二分的 $\log$ 复杂度就是 $\mathcal O(n\log^2n)$ 的。

# 完整代码

[CF submission 279211847](https://codeforces.com/contest/2008/submission/279211847)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
void solve()
{
    int n, q;
    read(n, q);
    int a[n + 1] = {};
    for (int i = 1; i <= n; i++)
        read(a[i]);
    sort(a + 1, a + n + 1);
    int sum[n + 1] = {};
    for (int i = 1; i <= n; i++)
        sum[a[i]]++;
    for (int i = 1; i <= n; i++)
        sum[i] += sum[i - 1];
    int vis[n + 1];
    memset(vis, -1, sizeof(vis));
    while (q--)
    {
        int x;
        read(x);
        if (~vis[x])
        {
            write(vis[x], ' ');
            continue;
        }
        auto check = [&](int mid)
        {
            int cnt = 0;
            for (int l = 0, r = x - 1; l <= n; l += x, r += x)
                cnt += (sum[min({l + mid, r, n})]) - (sum[max(0, l - 1)]);
            return cnt >= (n + 2) / 2;
        };
        int L = 0, R = n + 20, ans = n + 20;
        while (L <= R)
        {
            int mid = L + R >> 1;
            if (check(mid))
                R = (ans = mid) - 1;
            else
                L = mid + 1;
        }
        vis[x] = ans;
        write(vis[x], ' ');
    }
    putchar('\n');
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

要求中位数，先考虑二分答案。假设当前答案是 $m$，那么就是找 $a_i\bmod x\le m$ 的个数，推出满足条件的 $a_i$ 一定在 $[kx,kx+m],k\in\mathbf{N}$ 中，如果个数大于 $\dfrac{n}{2}$，说明 $m$ 合法，右边界左调，否则左边界右调。至于 $k$ 直接暴力枚举就行，因为单次询问复杂度是 $O\left(\log x\cdot\dfrac{n}{x}\right)$，总复杂度也才 $O(n\log^2 n)$，能过。

两种写法：对 $x$ 记忆化或对于每个 $x$ 预处理答案。

# Code

```cpp
#include<bits/stdc++.h>
int ans[100005];
int a[100005];
int T,n,m,l,r;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		memset(a+1,0,n<<2);
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),++a[x];
		for(int i=1;i<=n;++i)
			a[i]+=a[i-1],ans[i]=-1;
		for(int x;m--;){
			scanf("%d",&x);
			if(~ans[x]){
				printf("%d ",ans[x]);
				continue;
			}
			l=0;r=x-1;
			while(l<=r){
				int mid=l+r>>1,res=0;
				for(int i=0,j=x-1;i<=n;i+=x,j+=x)
					res+=a[std::min(i+mid,n)]-a[std::max(0,i-1)];
				if(res>(n>>1))ans[x]=mid,r=mid-1;
				else l=mid+1;
			}
			printf("%d ",ans[x]);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

## [Sakurako's Test](https://codeforces.com/contest/2008/problem/H)

要使得中位数最小，必然令所有 $a_i\gets a_i\bmod x$，然而快速修改 $a$ 是困难的。看到中位数往二分想，$mid$ 可能是中位数当且仅当 $cnt>n/2$，其中
$$
cnt=\sum_{i=1}^n [a_i\bmod x\le mid]
$$
式子有 $\bmod$ 不好处理，考虑拆掉 $\bmod$，有
$$
cnt=\sum_{i=1}^n [a_i\le \lfloor a_i/x\rfloor x+mid]
$$
$\lfloor a_i/x\rfloor x\le a_i$ 是显然的，加进式子，有
$$
cnt=\sum_{i=1}^n [\lfloor a_i/x\rfloor x\le a_i\le \lfloor a_i/x\rfloor x+mid]
$$
注意到不等式形似 $kx\le a_i\le kx+mid$，于是 $a_i$ 有贡献当且仅当存在 $k$ 使得 $a_i\in [kx,kx+mid]$。

至此做法已经清晰，对于每一个 $x$，二分中位数 $mid$，枚举 $k$ 求若干个区间内数的总个数以判断是否合法。注意到值域是 $O(n)$ 的，于是 $k\le \lfloor n/x \rfloor$，那么时间复杂度即为 $O(\sum_{x=1}^n \lfloor n/x \rfloor \log n)=O(n\log^2 n)$。

```cpp
for(int x=1;x<=n;x++){
    auto chk=[&](int mid){
        int cnt=0;
        for(int k=0;k*x<=n;k++)
            cnt+=b[min({k*x+mid,(k+1)*x-1,n})]-b[max(k*x-1,0)];
        return cnt>(n>>1);
    };
    int l=0,r=n,&res=ans[x];
    while(l<=r){
        int mid=(l+r)>>1;
        if(chk(mid))res=mid,r=mid-1;else l=mid+1;
    }
}
```

---

