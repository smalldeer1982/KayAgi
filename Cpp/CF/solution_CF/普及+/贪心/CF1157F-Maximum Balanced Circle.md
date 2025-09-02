# Maximum Balanced Circle

## 题目描述

There are $ n $ people in a row. The height of the $ i $ -th person is $ a_i $ . You can choose any subset of these people and try to arrange them into a balanced circle.

A balanced circle is such an order of people that the difference between heights of any adjacent people is no more than $ 1 $ . For example, let heights of chosen people be $ [a_{i_1}, a_{i_2}, \dots, a_{i_k}] $ , where $ k $ is the number of people you choose. Then the condition $ |a_{i_j} - a_{i_{j + 1}}| \le 1 $ should be satisfied for all $ j $ from $ 1 $ to $ k-1 $ and the condition $ |a_{i_1} - a_{i_k}| \le 1 $ should be also satisfied. $ |x| $ means the absolute value of $ x $ . It is obvious that the circle consisting of one person is balanced.

Your task is to choose the maximum number of people and construct a balanced circle consisting of all chosen people. It is obvious that the circle consisting of one person is balanced so the answer always exists.

## 样例 #1

### 输入

```
7
4 3 5 1 2 2 1
```

### 输出

```
5
2 1 1 2 3
```

## 样例 #2

### 输入

```
5
3 7 5 1 5
```

### 输出

```
2
5 5 
```

## 样例 #3

### 输入

```
3
5 1 4
```

### 输出

```
2
4 5 
```

## 样例 #4

### 输入

```
7
2 2 3 2 1 2 2
```

### 输出

```
7
1 2 2 2 2 3 2 
```

# 题解

## 作者：shenmadongdong (赞：2)

先考虑一个环的构成

显然环上的数必须是连续的，而且在最小的数向最大的数过渡的过程中，中间的每个数都会出现一遍，且最大的数向最小的数过渡的过程中中间的每个数都会再出现一遍

所以中间的每个数必定会出现至少两遍，而且这样的话构造显然

接下来我们只需将每个数的出现次数统计一下，然后再从小到大扫一遍，每次当出现的次数小于 $2$ 时即统计一次以这个数为最大值的环的长度，然后取一下 $max$ 即可

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define req(i,a,b) for(register int i=a;i>=b;--i)
using namespace std;
int n,a,num[200010],l,c,m,r,p;
int main()
{
	cin>>n;
	rep(i,1,n) scanf("%d",&a),num[a]++;//统计每个数的出现次数
	rep(i,1,200001)//需要多统计一次，否则2e5开始的区间会炸
	{
		if (l&&num[i]<2) {c+=num[i];if (c>=m) m=c,p=l,r=i;c=0,l=0;}//环的区间的结束
		else if (l&&num[i]>=2) c+=num[i];
		if (!l&&num[i]) l=i,c+=num[i];//环的区间的开始
	}
	printf("%d\n",m);//最大环长度
	rep(i,p,r) rep(j,1,num[i]-1) printf("%d ",i);
	req(i,r,p) if (num[i]) printf("%d ",i);//显而易见的构造，使其先上升再下降
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：1)

首先这个相邻差值$<=1$的环有个很好的性质，它一定能够把数在环上排列成类似这样的形式：

$a,a+1,a+2,a+3\cdots b-1,b,b-1,b-2,b-3\cdots a+1,a$

其中$a$为环上的最小值，$b$为环上的最大值，当然这其中可能有相邻相等的不过没啥关系。

那么我们就相当于是要在值域上找一段区间$[a,b]$，首先它里面所有的值都得有，而且，你观察上面的这个“凸的”序列，$[a+1,b-1]$里的数都至少得出现两次，在$b$的左右两段上都得放一个不然就构不成了。所以找一个区间里出现次数最多的$[a,b]$就行了。

那么我们就有一个思路，对于每个$a$我暴力找一个$b$使得$b$是最后一个满足$[a+1,b-1]$里面都出现至少两次的，然后我们发现，这样的话就会导致$[a+1,b]$里面的所有的$a$暴力找的结果都还是$b$，所以我们处理完这个$a$，就跳到$b$接着处理就行了，这样的复杂度是$O(\max\space a_i)$的。

另外还要注意特判$b-a<=1$的情况，这个就是$b$和$a$都出现过就可以。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	int cnt[300001], sums[300001], dp[300001];
	void ywymain() {
	    int n = get();
	    int mx = 0;
	    for (register int i = 1; i <= n; i++) {
	        int x = get();
	        cnt[x]++;
	        mx = max(mx, x);
	    }
	    for (register int i = 1; i <= mx; i++) sums[i] = sums[i - 1] + cnt[i];
	    int ans = 0;
	    for (register int i = 1; i <= mx; i++) {
	        if (!cnt[i])
	            continue;
	        if (!cnt[i + 1]) {
	            dp[i] = cnt[i];
	            ans = max(ans, dp[i]);
	            continue;
	        }
	        if (cnt[i + 1] == 1) {
	            dp[i] = cnt[i] + 1;
	            ans = max(ans, dp[i]);
	            continue;
	        }
	        int ptr = i + 1;
	        while (cnt[ptr] >= 2) ptr++;
	        if (!cnt[ptr])
	            ptr--;
	        ans = max(ans, dp[i] = sums[ptr] - sums[i - 1]);
	        i = ptr - 1;
	    }
	    cout << ans << endl;
	    for (register int i = 1; i <= mx; i++) {
	        if (dp[i] == ans) {
	            if (!cnt[i + 1]) {
	                for (register int j = 1; j <= cnt[i]; j++) printf("%d ", i);
	                return;
	            }
	            if (cnt[i + 1] == 1) {
	                for (register int j = 1; j <= cnt[i]; j++) printf("%d ", i);
	                printf("%d ", i + 1);
	                return;
	            }
	            int ptr = i + 1;
	            while (cnt[ptr] >= 2) ptr++;
	            if (!cnt[ptr])
	                ptr--;
	            for (register int j = i; j <= ptr; j++) cnt[j]--, printf("%d ", j);
	            for (register int j = ptr; j >= i; j--) {
	                while (cnt[j]) cnt[j]--, printf("%d ", j);
	            }
	            return;
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：sieve (赞：0)

# 题解：[Maximum Balanced Circle](https://www.luogu.com.cn/problem/CF1157F)

## 思路

假设我们现在拥有一组数，画出一个图来表示不同的数：

![](https://cdn.luogu.com.cn/upload/image_hosting/2sx2m52m.png)

请注意，以下内容均为假设这个序列满足题目的条件。

假设最左边的点是 $s$，最右边的点是 $t$，那么要使这个样子的集合满足条件，则必须满足的条件之一是：

$$
t = s \pm 1
$$

或

$$
t = s
$$

并且，我们要尽可能的不出现数字低于 $s$，如果有集合能满足题目的条件，一定能够满足这个条件，原因如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/fd2esw4a.png)

我们可以将途中的蓝色部分全部移到 $s$ 拼起来，红色部分可以移到 $t$ 拼起来，最终，我们一定能够构造出这样的形状：

![](https://cdn.luogu.com.cn/upload/image_hosting/x6tlx1wg.png)

类似一个山。

当然，构造出的序列中可能会出现一些相同的部分，我们依然可以把这些相同的部分移到**一起**，山就会出现这样的形状：

![](https://cdn.luogu.com.cn/upload/image_hosting/odqq1o9m.png)

注意，最后一定是一条线降下来的，不然无法构造成功。

那么，我们就可以枚举 $s$，然后看这个点能不能选，能选的条件必须有：这个数字出现的次数大于等于 $2$，并且要与上一个选的数字之差小于等于 $1$。如果不满足，但是出现了一次，就可以把这个数字选为图中的最高点。

数字要出现至少两次，因为它再中间的时候可以进行上升，但是，必须留一个做为降下去的数。

因为图中的最高点既是升高，也是下降，所以只要出现了一次就够了。

然后就是直接模拟就行了，个人感觉推导过程挺有趣的。

[Code](https://www.luogu.com.cn/paste/xgyizdrd)

---

## 作者：ttq012 (赞：0)

大力使用数据结构维护之。时间复杂度为 $O(n\log^2n)$。

首先转化为值域问题，用一个 ST 表记录任意一段区间的值的出现次数的最小值。

然后猜结论。容易发现最优秀的答案一定可以表示为 $l,l,l,\ldots,l,l+1,l+1,l+1,\ldots,l+1,l+2,\ldots,r,r,r,\ldots,r,r-1,r-2,r-3,\ldots,l+1,l$ 的形式。

所以枚举每一个有值的位置 $i$，用 ST 表求出最大的 $j$ 使得 $i\sim j$ 中所有的数都至少出现了 $2$ 次。然后：

+ 若 $i$ 出现了超过 $1$ 次，则若 $i-1$ 出现了至少一次则可以扩展到 $i-1$，$i+1$ 出现了至少一次可以扩展到 $i+1$。
+ 否则和上面基本一样，只是左右最多只能扩展一个位置。

因为我垃圾的 ST 表的查询时间复杂度为 $O(\log n)$，所以总时间复杂度为 $O(n\log^2n)$。如果用 $O(1)$ 查询的 ST 表可以将时间复杂度降低至 $O(n\log n)$。

```cp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100;
int a[N], box[N], f[20][N], s[N];
int query(int l, int r) {
    int len = r - l + 1, mi = 11451411;
    for (int i = 19; ~i; i--) {
        if (len >> i & 1) {
            mi = min(mi, f[i][l]);
            l += (1 << i);
        }
    }
    return mi;
}
signed main() {
    int n, mx = 0;
    pair<int, int> id;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        box[a[i]]++;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= 200000; i++) {
		f[0][i] = box[i];
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j + (1 << i) - 1 <= 200000; j++) {
			f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
		}
	}
    for (int i = 1; i <= 200000; i++) {
        s[i] = s[i - 1] + box[i];
    }
    for (int i = 1; i <= 200000; i++) {
        if (box[i]) {
            int l = i, r = 200000, best = i;
            while (l <= r) {
                int mid = l + r >> 1;
                if (query(i, mid) < 2) {
                    r = mid - 1;
                } else {
                    best = mid, l = mid + 1;
                }
            }
            int L = i, R = best;
            if (box[i] > 1) {
                if (box[L - 1] > 0) {
                    L--;
                }
                if (box[R + 1] > 0) {
                    R++;
                }
            } else {
                if (box[L - 1] > 0) {
                    L--;
                }
                else if (box[R + 1] > 0) {
                    R++;
                }
            }
            if (mx < s[R] - s[L - 1]) {
                mx = s[R] - s[L - 1];
                id = {L, R};
            }
        }
    }
    cout << mx << '\n';
    for (int i = id.first; i <= id.second; i++) {
        for (int j = 1; j < box[i]; j++) {
            cout << i << ' ';
        }
    }
    for (int i = id.second; i >= id.first; i--) {
        cout << i << ' ';
    }
    cout << '\n';
}
```

---

## 作者：_lgh_ (赞：0)

记子集为 $res$，最大值为 $x$，最小值为 $y$。

考虑答案的情况。看样例不难发现答案一定形如 $(x,\cdots,x),(x-1,\cdots,x-1),\cdots,(y,\cdots,y),y+1,y+2,\cdots,x-1$。

考虑这样的形状有什么限制。首先发现这一段区间是值域连续的。其次，除了 $x,y$，其他的元素出现次数必须 $\ge 2$，而且肯定能选就选。因为值域较小，因此可以直接在桶上双指针，每次尽量向右扩展找到最大的出现次数 $\ge 2$ 的位置，更新答案即可。

部分代码：
```cpp
    int n; rd(n);
    vi a(200001);
    for(int i=1,x; i<=n; i++) rd(x),a[x]++;
    int lt=0,rt=0;
    int sum=0,bg=1,ed,mxl=0;
    for(int i=1; i<=200000; i++) {
        if(a[i]==0) {
            bg=i,sum=0;
            continue;
        }
        sum+=a[i];
        if(sum>mxl) mxl=sum,lt=bg,rt=i;
        if(a[i]==1) bg=i,sum=1;
    }
```

需要注意 if 语句的判断顺序不要出错。

---

## 作者：XCH_0803 (赞：0)

# 题目大意：
给定一个长度为 $n$ 的序列，求是否能够从序列中选出一个集合，使得这个集合按照特定的顺序排成一个环后，环上相邻的点之间的权值差的绝对值不超过 $1$ 。

# 题解：
集合问题与序列顺序无关，因此可以先将序列排序。

可以发现，题目中描述的环，拆成序列之后应该满足 $a_l,a_l+1,$ $\cdots ,$ $a_r,a_r-1,$ $\cdots ,$ $a_l+1$ 的形态，即：除了 $a_l,a_r$ 之外的其他所有值应该都有至少两个。因此，开一个桶记录一下每个元素出现的次数，并对原序列进行去重。可知，对于满足 $1,2,2,$ $\cdots,$ $2,1$ 形态的序列中的任何一个 $2$ 的位置的答案都是相同的。因此，考虑使用双指针法，每次都找到 $1$ 出现的位置，统计答案并更新答案即可。

话不多说，上代码！！！

```c
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
 
int n,d[maxn],tot,cnt[maxn];
 
void read(){
    cin>>n;
    for(int i=1;i<=n;i++){
		cin>>d[i];
		++cnt[d[i]];
    }
    sort(d+1,d+n+1);
    tot=unique(d+1,d+n+1)-d-1;
}
void solve(){
    int ans=cnt[d[1]],l=1,r=1;
    for(int i=1,j;i<=tot;i=j){
        j=i+1;
        int sum=cnt[d[i]];
        while(j<=tot&&d[j]-d[j-1]==1&&cnt[d[j]]>=2){
			sum+=cnt[d[j]],++j;
        }
        int cr=j-1;
        if(j<=tot&&d[j]-d[j-1]==1){
			sum+=cnt[d[j]],cr=j;
        }
        if(sum>ans){
			ans=sum,l=i,r=cr;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=cnt[d[l]];i++){
		cout<<d[l]<<" ";
    }
    for(int i=l+1;i<r;i++){
		for(int j=1;j<cnt[d[i]];j++){
			cout<<d[i]<<" ";
		}
    }
    if(l!=r){
		for(int i=1;i<=cnt[d[r]];i++){
			cout<<d[r]<<" ";
		}
	}
    for(int i=r-1;i>=l+1;i--){
		cout<<d[i]<<" ";
    }
}
 
int main(){
    read();
    solve();
    return 0;
}
```


---

