# Lightsabers (medium)

## 题目描述

There is unrest in the Galactic Senate. Several thousand solar systems have declared their intentions to leave the Republic. Master Heidi needs to select the Jedi Knights who will go on peacekeeping missions throughout the galaxy. It is well-known that the success of any peacekeeping mission depends on the colors of the lightsabers of the Jedi who will go on that mission.

Heidi has $ n $ Jedi Knights standing in front of her, each one with a lightsaber of one of $ m $ possible colors. She knows that for the mission to be the most effective, she needs to select some contiguous interval of knights such that there are exactly $ k_{1} $ knights with lightsabers of the first color, $ k_{2} $ knights with lightsabers of the second color, $ ... $ , $ k_{m} $ knights with lightsabers of the $ m $ -th color.

However, since the last time, she has learned that it is not always possible to select such an interval. Therefore, she decided to ask some Jedi Knights to go on an indefinite unpaid vacation leave near certain pits on Tatooine, if you know what I mean. Help Heidi decide what is the minimum number of Jedi Knights that need to be let go before she is able to select the desired interval from the subsequence of remaining knights.

## 样例 #1

### 输入

```
8 3
3 3 1 2 2 1 1 3
3 1 1
```

### 输出

```
1
```

# 题解

## 作者：XCH_0803 (赞：0)

# 题意

先输入两个数 $n$ 和 $m$，再给你一个长为 $n$ 的序列和一个长为 $m$ 的序列，问最少要删除多少元素，才能使第一个序列中的某个连续子串中恰好满足第二个序列对每个数字的要求

# 题解

运用尺取法，设 $l$ 为左界，$r$ 为右界，若 $c[a[r]]=b[a[r]]$ 则说明对 $b$ 中第 $a[r]$ 个数字的个数要求达到满足，则 $sum+1$。如果 $sum=m$，则说明该子串满足条件，那么我们就要将左界前进（为了使删除的数字更少，最后 $r-l+1$ 肯定是最小的），此处注意要使 $c[a[l]]$ 减 $1$，如果它在减之前的个数等于 $b[a[l]]$ 则说明删减后，满足条件的个数减 $1$，即 $sum-1$。

话不多说，上代码！

```c
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
const int INF=0x3f3f3f3f;
int a[N];
int b[N];
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int sum=0;
    int pp=0;
    for(int i=1;i<=m;i++){
        cin>>b[i];
        if(b[i]==0){
        	sum++;
        }
        pp+=b[i];
    }
    int c[N];
    int l=1,r=1;
    int MIN=INF;
    for(int i=1;;i++){
        while(r<=n&&sum<m){
            c[a[r]]++;
            if(c[a[r]]==b[a[r]]){
				sum++;
            }
            r++;
        }
        if(sum<m){
			break;
        }
        MIN=min(MIN,r-l-pp);
        if(c[a[l]]==b[a[l]]){
			sum--;
        }
        c[a[l]]--;
        l++;
    }
    if(MIN!=INF){
    	cout<<MIN;
    }
    else{
		cout<<"-1";
    }
    return 0;
}
```




---

## 作者：SunnyYuan (赞：0)

## 思路

设总共有 $n$ 个数字，值域为 $m$，$c_x$ 表示数字 $x$ 在某一段的个数，$a$ 表示原数组，$b_x$ 表示要数字 $x$ 要达到的个数目标。

首先我们先圈出一段使得所有数字 $c_x \ge b_x$，那么对于圈出来的这一段我们可以使用 $\sum\limits_{i = 1}^{m} c_i - b_i$ 的次数删除多余的数字。

我们可以使用双指针完成上述过程，设当前 $(l, r)$ 已经使 $cnt$ 个数字 $c_i \ge b_i$，要删除 $ans$ 个数据才能达到目标，那么固定一个左端点 $l$，然后只要还没有凑够（$cnt < m$），就让 $r$ 加 $1$，并且让 $c_{a_r}$ 加 $1$，如果 $c_{a_r} = b_{a_r}$ 就让 $cnt$ 加 $1$，如果 $c_{a_r} > b_{a_r}$，那么说明又多来了一个根本不应该来的家伙，要把它删去，即 $ans \leftarrow ans + 1$，最后在所有 $ans$ 中取 $\min$。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Lightsabers (medium)
| OJ:      Luogu
| URL:     https://www.luogu.com.cn/problem/CF958F2
| When:    2023-11-01 15:20:39
| 
| Memory:  250 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int a[N], b[N], c[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], c[a[i]]++;
    int cnt = 0;
    for (int i = 1; i <= m; i++) cin >> b[i], cnt += (b[i] == 0);
    memset(c, 0, sizeof(c));
    int ans = 0x3f3f3f3f, sum = 0;
    for (int l = 1, r = 0; l <= n; l++) {
        while (r < n && cnt < m) {
            c[a[++r]]++;
            if (c[a[r]] == b[a[r]]) cnt++;
            if (c[a[r]] > b[a[r]]) sum++;
        }
        if (cnt == m) ans = min(ans, sum);
        else break;
        if (c[a[l]] > b[a[l]]) sum--;
        c[a[l]]--;
        if (c[a[l]] < b[a[l]]) cnt--;
    }
    if (ans == 0x3f3f3f3f) cout << "-1\n";
    else cout << ans << '\n';
    return 0;
}

```

---

