# Lucky Segments

## 题目描述

Petya 喜欢幸运数字。众所周知，幸运数字是指其十进制表示中只包含幸运数字 $4$ 和 $7$ 的正整数。例如，$47$、$744$、$4$ 是幸运数字，而 $5$、$17$、$467$ 不是。

Petya 有 $n$ 个区间 $[l_{1}, r_{1}]$，$[l_{2}, r_{2}]$，……，$[l_{n}, r_{n}]$。每次操作时，Petya 可以选择任意一个区间（假设是第 $i$ 个区间），将其替换为 $[l_{i}+1, r_{i}+1]$ 或 $[l_{i}-1, r_{i}-1]$。换句话说，每次操作可以将任意一个区间整体向左或向右平移一个单位距离。

Petya 称一个数字为“全满”数字，如果它属于每一个区间。也就是说，数字 $x$ 是全满数字，当且仅当对于任意 $i$（$1 \leq i \leq n$），都有 $l_{i} \leq x \leq r_{i}$。

Petya 最多可以进行 $k$ 次操作。操作结束后，他会统计全满幸运数字的数量。请你求出他最多可以得到多少个全满幸运数字。

## 说明/提示

在第一个样例中，Petya 将第二个区间向左移动两单位（变为 $[4, 7]$），此时数字 $4$ 成为全满数字。

在第二个样例中，Petya 将第一个区间向右移动两单位（变为 $[42, 47]$），将第二个区间向左移动三单位（变为 $[44, 71]$），此时数字 $44$ 和 $47$ 成为全满数字。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 7
1 4
6 9
4 7
3 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 7
40 45
47 74
```

### 输出

```
2
```

# 题解

## 作者：wmrqwq (赞：0)

# 题目链接

[CF121D Lucky Segments *2500](https://www.luogu.com.cn/problem/CF121D)

# 解题思路

注意到幸运数字数量很少，是 $2^{18}$ 量级的。

下文设 $V$ 为 $2^{18}$。

那么我们可以先爆搜出所有幸运数字并将这些数字排序，枚举左端点，注意到右端点是否能取值是有单调性的，于是我们可以二分右端点。

注意到暴力 check 的话时间复杂度是 $O(nV \log V)$，不能通过此题。

考虑优化 check，我们先特判掉最小区间长度 $<$ 要 check 的区间的长度，这种情况是无解的。对于剩下的情况我们发现可以把左右端点拆开，然后直接分别算两边的代价。

为啥这样做是对的呢？

有一个结论，除去任意次都无解的情况，问题可以转化成只移动一个端点，因为对于一个合法的区间 $[l,r]$，设 check 的区间为 $[ql,qr]$，则一定有 $l \le ql$ 或 $r \ge qr$ 成立，否则这个区间长度**一定**小于 check 区间长度，由于另一个端点是合法的，因此我们只需要 check 这个不合法的端点。

发现左右端点拆开来做是对的，那么我们将左右端点排序，根据上述性质 check 内部写一个二分维护就可以了。

时间复杂度 $O(V \log V \log n)$。

注意要开 `__int128`。

# 参考代码

```cpp
ll n,m,k;
ll a[1<<20];
ll l[1000010],r[1000010];
__int128 prel[1000010],prer[1000010];
ll ans;
ll minn;
void Dfs(ll x)
{
    if(x>1e18)
        return ;
    a[++k]=x;
    Dfs(x*10+4);
    Dfs(x*10+7);
}
bool check(ll ql,ll qr)
{
    if(qr-ql+1>minn)
        return 0;
    __int128 A=0;
    ll L=1,R=n;
    while(L<R)
    {
        ll Mid=(L+R+1)/2;
        if(l[Mid]>=ql)
            L=Mid;
        else
            R=Mid-1;
    }
    if(l[L]>=ql)
        A+=(__int128)prel[L]-(__int128)L*ql;
    
    L=1,R=n;
    while(L<R)
    {
        ll Mid=(L+R+1)/2;
        if(r[Mid]<=qr)
            L=Mid;
        else
            R=Mid-1;
    }
    if(r[L]<=qr)
        A+=(__int128)L*qr-(__int128)prer[L];
    return A<=m;
}
void _clear(){}
void solve()
{
    minn=9e18;
    _clear();
    cin>>n>>m;
    Dfs(4);
    Dfs(7);
    // cout<<k<<endl;
    sort(a+1,a+1+k);
    forl(i,1,n)
        cin>>l[i]>>r[i],
        Min(minn,r[i]-l[i]+1);
    sort(l+1,l+1+n);
    sort(r+1,r+1+n);
    reverse(l+1,l+1+n);
    forl(i,1,n)
        prel[i]=prel[i-1]+l[i];
    forl(i,1,n)
        prer[i]=prer[i-1]+r[i];
    forl(i,1,k)
    {
        ll L=i,R=k;
        while(L<R)
        {
            ll Mid=(L+R+1)/2;
            if(check(a[i],a[Mid]))
                L=Mid;
            else
                R=Mid-1;
        }
        if(check(a[i],a[L]))
            if(Max(ans,L-i+1));
                // cout<<a[i]<<' '<<a[L]<<endl;
    }
    cout<<ans<<endl;
}
```

---

