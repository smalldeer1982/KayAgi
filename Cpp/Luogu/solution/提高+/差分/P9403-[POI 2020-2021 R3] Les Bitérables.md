# [POI 2020/2021 R3] Les Bitérables

## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Les Bitérables](https://szkopul.edu.pl/problemset/problem/Lpz563_ATiESIrNZxiT5bwIx/statement/)。

d1t2。

## 题目描述

有 $t$ 个时刻，第 $i$ 个时刻给出了局面 $p_1,p_2,\dots,p_{s_i}$，表示在数轴的 $(0,d)$ 范围内，有且仅有 $p_1,p_2,\dots,p_{s_i}$ 这些位置上有物品。

在 $0$ 位置和 $d$ 位置有无穷多个物品。

你可以花费一个代价，将一个物品向左移动一个位置或向右移动一个位置。

问你在相邻两个时刻之间，把前一个局面转化为后一个局面，最少需要多少代价。

## 说明/提示

对于所有数据，$2\leq n\leq 500000$，$2\leq d\leq 10^{12}$，$\sum s_i\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $s_i\leq 1$ | 5 |
| 2 | $s_i\leq 3$ | 10 |
| 3 | $d\leq 7$ | 12 |
| 4 | $\sum s_i\leq 5000$ | 27 |
| 5 | 如果 $s_i>0$，那么 $p_{s_i}=p_1+s_i-1$ | 11 |
| 6 |  | 35 |


## 样例 #1

### 输入

```
3 10
2 4 7
3 3 6 8
1 5
```

### 输出

```
4
6```

## 样例 #2

### 输入

```
见附件```

### 输出

```
6252500
6252500
```

## 样例 #3

### 输入

```
见附件```

### 输出

```
999990000
999990000
999990000
999990000
```

## 样例 #4

### 输入

```
生成器：/paste/3igmip11```

### 输出

```
生成器：/paste/fusadpm0```

# 题解

## 作者：Semsue (赞：2)

标签线段树是一脸疑惑啊？感觉很难想到不是线性的做法。

不妨设 $s_{i}\le s_{i-1}$，一开始我们在 $i-1$ 的序列左边添加 $s_i$ 个 $0$，右边添加 $s_{i}$ 个 $d$。这样我们就可以把问题抽象成：选择 $j$ 个位置全部跑到 $0$，$s_{i-1}-s_{i}-j$ 个位置全部跑到 $d$，剩下的部分和第 $i$ 天一一对应。

有一个显然的贪心是小配小，大配大，那么要求的就是一个带绝对值的和式。OIer 非常擅长分类讨论！所以直接拆绝对值。对于一个第 $i$ 天的位置 $j$，假设一开始和它配对的位置 $k$ 是比它小的，那么它对答案的贡献是正的。找到第一个比它大的位置 $k'$，这时它的贡献会取一个反，并且以后都是负数。对于第 $i-1$ 天的位置 $j$，找到最后一个比它小的位置 $k$，显然随着滑动窗口的移动，和 $j$ 匹配的位置只能比 $k$ 小，这样 $j$ 的正负性也不会变了。

所有这些位置修改都是 $O(1)$ 的，由于两个序列都是有序的所以可以直接双指针。复杂度是 $O(n+\sum s_{i})$。

代码很短。

更新了一下代码，不要使用大量 STL 容器。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
template <typename T>
void read(T &x)
{
    T sgn = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') sgn = -1;
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    x *= sgn;
}
int n, s[maxn];
ll d, sum1[maxn], sum2[maxn];
vector<ll> p, q;
ll vec1[maxn], vec2[maxn];
int main()
{
    read(n); read(d); read(s[1]); p.resize(s[1] + 1);
    for (int i = 1; i <= s[1]; i++) read(p[i]);
    for (int i = 2; i <= n; i++)
    {
        read(s[i]);
        q.resize(s[i] + 1);
        for (int j = 1; j <= s[i]; j++) read(q[j]);
        bool flg = 0;
        if (s[i] > s[i - 1])
        {
            flg = 1;
            swap(s[i], s[i - 1]);
            swap(p, q);
        }
        vector<ll> tmp = p, temp(0);
        for (int j = 1; j <= s[i]; j++) temp.emplace_back(0);
        for (ll j : p) temp.emplace_back(j);
        for (int j = 1; j <= s[i]; j++) temp.emplace_back(d);
        s[i - 1] += 2 * s[i];
        sum2[s[i - 1] + 1] = 0;
        for (int j = 1; j <= s[i - 1]; j++) sum1[j] = temp[j] + sum1[j - 1];
        for (int j = s[i - 1]; j; j--) sum2[j] = d - temp[j] + sum2[j + 1];
        ll fans = 1e18, nans = 0;
        for (int j = 1, k = 1; j <= s[i]; j++)
        {
            nans += q[j];
            while (k <= s[i - 1] && temp[k] <= q[j]) k++;
            if (k <= s[i - 1]) vec1[max(k - j + 1, 1)] += q[j];
        }
        for (int j = s[i - 1], k = s[i]; j; j--)
        {
            if (j < s[i]) nans -= temp[j];
            while (k && q[k] >= temp[j]) k--;
            if (k) vec2[max(j - k + 1, 1)] += temp[j];
        }
        for (int j = 0; j <= s[i - 1] - s[i]; j++)
        {
            int k = s[i - 1] - s[i] - j;
            if (s[i])
            {
                nans -= temp[j + s[i]];
                if (j)
                {
                    if (temp[j] <= q[1]) nans += temp[j];
                    else nans -= temp[j];
                }
                nans += 2 * (vec2[j + 1] - vec1[j + 1]);
            } 
            fans = min(fans, nans + sum1[j] + sum2[s[i - 1] - k + 1]);
        }
        for (int j = 1; j <= s[i - 1]; j++) vec1[j] = vec2[j] = 0;
        s[i - 1] -= s[i] * 2;
        if (flg)
        {
            swap(s[i], s[i - 1]);
            swap(p, q);
        }
    	printf("%lld\n", fans);
    	swap(p, q);
    }
    return 0;
}
```

---

## 作者：NahX_ (赞：0)

题意简明，不再阐述。

首先可以对当前两行(假设为第 $i$，$i+1$ 行)的情况分类。

1. $s_i\leq s_{i+1}$。

此时可以分为三种情况。

一种是从 0 处调 $x$ 件物品（$0\leq x\leq s_{i+1}$），这 $x$ 件物品显然对应第 $i+1$ 行 $p_1,p_2,...,p_x$，然后第 $i$ 行的后 $s_i+x-s_{i+1}$ 个物品去到 $d$。

另一种是从 $d$ 处调 $x$ 件物品（$0\leq x \leq s_{i+1}$），这 $x$ 件物品显然对应第 $i+1$ 行 $p_{s_{i+1}-x+1},p_{s_{i+1}-x+2},...,p_{s_{i+1}}$，然后第 $i$ 行的前 $s_i+x-s_{i+1}$ 个物品去到 0。

还有一种是从 0 处调 $x$ 件物品，从 $d$ 处调 $y$ 件物品（$0\leq x,0\leq y,x+y+s_i=s_{i+1}$），分别对应 $i+1$ 行 $p_1,p_2,...,p_x$ 和 $p_{s_{i+1}-y+1},p_{s_{i+1}-y+2},p_{s_{i+1}}$，第 $i$ 行的物品则对应第 $i+1$ 行的 $p_{x+1},p_{x+2},...,p_{s_{i+1}-y}$。

发现最小代价无论在哪种情况中取到其代价随 $x$ 变化所形成的图像都是单谷的（第三种情况看作 $y=s_{i+1}-s_{i}-x$），于是可以三分，对于每一种情况都三分 $x$ 找到最小代价最后三种情况取最小即可。

2. $s_i>s_{i+1}$。

此时也是分三种情况，前两种情况与 $s_i\leq s_{i+1}$ 时的前两种情况相同，第三种情况变为调前 $x$ 个元素到 0，调后 $y$ 个元素到 $d$ （$0<x,0<y,s_i-x-y=s_{i+1}$）。

最小代价无论在哪种情况中取到其代价随 $x$ 变化所形成的图像也是单谷的，同上三分求最小代价即可。

时间复杂度 $O(n\log_3n)$。

```
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define int long long
#define db double
#define endl '\n'
#define lowbit(x) x&-x
#define intz(x,a) memset(x,a,sizeof(x))
const int N=5e5+5; 
int s[N];vector<int>p[N];
signed main(){int n,d;cin>>n>>d;
	for(int i=1;i<=n;i++){cin>>s[i];p[i].resize(s[i]+5);
		for(int j=1;j<=s[i];j++)cin>>p[i][j];
	}
	for(int i=1;i<n;i++){
		if(s[i]<=s[i+1]){int l=0,r=s[i+1],ans=(1ll<<63)-1;
			while(l<=r){int mid0=l+(r-l)/3,mid1=r-(r-l)/3,sum0=0,sum1=0;
				for(int j=1;j<=s[i+1];j++)
					if(j<=mid0)sum0+=p[i+1][j];
					else if(j<=mid0+s[i])sum0+=abs(p[i+1][j]-p[i][j-mid0]);
					else sum0+=d-p[i+1][j];
				for(int j=s[i+1]-mid0+1;j<=s[i];j++)sum0+=min(p[i][j],d-p[i][j]);
				for(int j=1;j<=s[i+1];j++)
					if(j<=mid1)sum1+=p[i+1][j];
					else if(j<=mid1+s[i])sum1+=abs(p[i+1][j]-p[i][j-mid1]);
					else sum1+=d-p[i+1][j];
				for(int j=s[i+1]-mid1+1;j<=s[i];j++)sum1+=min(p[i][j],d-p[i][j]);
				if(sum0>=sum1)l=mid0+1,ans=min(ans,sum1);else r=mid1-1,ans=min(ans,sum0);
			}l=0,r=s[i+1];
			while(l<=r){int mid0=l+(r-l)/3,mid1=r-(r-l)/3,sum0=0,sum1=0;
				for(int j=s[i+1];j;j--)
					if(j>=s[i+1]-mid0+1)sum0+=d-p[i+1][j];
					else if(j>=s[i+1]-mid0-s[i]+1)sum0+=abs(p[i+1][j]-p[i][j-s[i+1]+mid0+s[i]]);
					else sum0+=p[i+1][j];
				for(int j=1;j<=-s[i+1]+mid0+s[i];j++)sum0+=min(p[i][j],d-p[i][j]);
				for(int j=s[i+1];j;j--)
					if(j>=s[i+1]-mid1+1)sum1+=d-p[i+1][j];
					else if(j>=s[i+1]-mid1-s[i]+1)sum1+=abs(p[i+1][j]-p[i][j-s[i+1]+mid1+s[i]]);
					else sum1+=p[i+1][j];
				for(int j=1;j<=-s[i+1]+mid1+s[i];j++)sum1+=min(p[i][j],d-p[i][j]); 
				if(sum0>=sum1)l=mid0+1,ans=min(ans,sum1);else r=mid1-1,ans=min(ans,sum0);
			}cout<<ans<<endl;
		}else{int l=0,r=s[i],ans=(1ll<<63)-1;
			while(l<=r){int mid0=l+(r-l)/3,mid1=r-(r-l)/3,sum0=0,sum1=0;
				for(int j=1;j<=s[i];j++)
					if(j<=mid0)sum0+=p[i][j];
					else if(j<=mid0+s[i+1])sum0+=abs(p[i][j]-p[i+1][j-mid0]);
					else sum0+=d-p[i][j];
				for(int j=s[i]-mid0+1;j<=s[i+1];j++)sum0+=min(p[i+1][j],d-p[i+1][j]);
				for(int j=1;j<=s[i];j++)
					if(j<=mid1)sum1+=p[i][j];
					else if(j<=mid1+s[i+1])sum1+=abs(p[i][j]-p[i+1][j-mid1]);
					else sum1+=d-p[i][j];
				for(int j=s[i]-mid1+1;j<=s[i+1];j++)sum1+=min(p[i+1][j],d-p[i+1][j]);
				if(sum0>=sum1)l=mid0+1,ans=min(ans,sum1);else r=mid1-1,ans=min(ans,sum0);
			}l=0,r=s[i];
			while(l<=r){int mid0=l+(r-l)/3,mid1=r-(r-l)/3,sum0=0,sum1=0;
				for(int j=s[i];j;j--)
					if(j>=s[i]-mid0+1)sum0+=d-p[i][j];
					else if(j>=s[i]-mid0-s[i+1]+1)sum0+=abs(p[i][j]-p[i+1][j-s[i]+mid0+s[i+1]]);
					else sum0+=d-p[i][j];
				for(int j=1;j<=-s[i]+mid0+s[i+1];j++)sum0+=min(p[i+1][j],d-p[i+1][j]);
				for(int j=s[i];j;j--)
					if(j>=s[i]-mid1+1)sum1+=d-p[i][j];
					else if(j>=s[i]-mid1-s[i+1]+1)sum1+=abs(p[i][j]-p[i+1][j-s[i]+mid1+s[i+1]]);
					else sum1+=d-p[i][j];
				for(int j=1;j<=-s[i]+mid1+s[i+1];j++)sum1+=min(p[i+1][j],d-p[i+1][j]);
				if(sum0>=sum1)l=mid0+1,ans=min(ans,sum1);else r=mid1-1,ans=min(ans,sum0);
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

