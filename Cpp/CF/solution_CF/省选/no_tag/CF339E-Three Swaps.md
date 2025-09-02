# Three Swaps

## 题目描述

Xenia the horse breeder has $ n $ $ (n>1) $ horses that stand in a row. Each horse has its own unique number. Initially, the $ i $ -th left horse has number $ i $ . That is, the sequence of numbers of horses in a row looks as follows (from left to right): 1, 2, 3, $ ... $ , $ n $ .

Xenia trains horses before the performance. During the practice sessions, she consistently gives them commands. Each command is a pair of numbers $ l,r $ $ (1<=l<r<=n) $ . The command $ l,r $ means that the horses that are on the $ l $ -th, $ (l+1) $ -th, $ (l+2) $ -th, $ ... $ , $ r $ -th places from the left must be rearranged. The horses that initially stand on the $ l $ -th and $ r $ -th places will swap. The horses on the $ (l+1) $ -th and $ (r-1) $ -th places will swap. The horses on the $ (l+2) $ -th and $ (r-2) $ -th places will swap and so on. In other words, the horses that were on the segment $ [l,r] $ change their order to the reverse one.

For example, if Xenia commanded $ l=2,r=5 $ , and the sequence of numbers of horses before the command looked as (2, 1, 3, 4, 5, 6), then after the command the sequence will be (2, 5, 4, 3, 1, 6).

We know that during the practice Xenia gave at most three commands of the described form. You have got the final sequence of numbers of horses by the end of the practice. Find what commands Xenia gave during the practice. Note that you do not need to minimize the number of commands in the solution, find any valid sequence of at most three commands.

## 样例 #1

### 输入

```
5
1 4 3 2 5
```

### 输出

```
1
2 4
```

## 样例 #2

### 输入

```
6
2 1 4 3 6 5
```

### 输出

```
3
1 2
3 4
5 6
```

# 题解

## 作者：syzf2222 (赞：7)

讲一种巧妙的思路。

我们考虑从后往前将其还原。

每次还原考虑枚举反转的左右端点。

这不是$\Theta(n^2)$的吗？

不，这是$\Theta(1)$的（没想到吧）。

考虑每次翻转后两个端点和前后必不连续，我们枚举所有这样的点。

如样例$1$中我们认为位置$1,2,4,5$都有可能是端点。

由于一次翻转只会产生$4$个可疑端点，所以最终可疑端点极少。

那么这题就可以用（上万常数的）$\Theta(n)$算法过掉了。

代码如下，仅供参考：

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=1e3+10;
const int mod=1e9+7;
int n,a[maxn];
int k,ansl[5],ansr[5];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
inline void solve(int st){
	int flag=1;
	for(int i=1;i<=n&&flag;i++)
		flag&=(i==a[i]);
	if(flag){
		printf("%d\n",st-1);
		for(int i=st-1;i>=1;i--)
			printf("%d %d\n",ansl[i],ansr[i]);
		exit(0);
	}
	if(st<=3){
		int m=0,w[1000];
		for(int i=1;i<=n;i++)
			if(abs(a[i]-a[i-1])>1||abs(a[i]-a[i+1])>1)
				w[++m]=i;
		for(int i=1;i<m;i++)
			for(int j=i+1;j<=m;j++){
				reverse(a+w[i],a+w[j]+1);
				ansl[st]=w[i],ansr[st]=w[j];
				solve(st+1);
				reverse(a+w[i],a+w[j]+1);
			}
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	a[0]=0,a[n+1]=n+1;
	solve(1);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：cjZYZtcl (赞：0)

提供一种 $O(n^3)$ 的做法。

### Solution

考虑倒着做，把输入序列还原成升序序列。

我们暴力枚举第一次翻转的左右端点，记为 $(l, r)$。

不难发现，如果该操作是可行的操作，那么剩下的序列只有极少的情况，可以分类讨论后 $O(n)$ 处理。

总时间复杂度 $O(n^3)$。

但是由于 $n \le 1000$，所以如果跑满肯定会 TLE。

那么考虑把不可能作为翻转区间的区间排除，且如果遇到一种可行情况就退出。

但这样依然可以被卡到跑满 $O(n^3)$，所以考虑先把所有可能作为第一次翻转的区间找出来，复杂度 $O(n^2)$，然后随机打乱一下，这样期望遇到可行翻转所需枚举的区间数并不多，即可通过本题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pr pair<int, int>
#define pb push_back
#define mid (l + r) / 2
#define ls num << 1
#define rs num << 1 | 1

mt19937 rnd(chrono :: system_clock().now().time_since_epoch().count());

stack<pr> ans;
vector<pr> v;

int n, l, r, a[1005];

inline int read() {
    int x = 0, m = 1;
    char ch = getchar();

    while (!isdigit(ch)) {
        if (ch == '-') m = -1;
        ch = getchar();
    }

    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }

    return x * m;
}

inline void write(int x) {
    if (x < 0) {
        putchar('-');
        write(-x);
        return;
    }

    if (x >= 10) write(x / 10);
    putchar(x % 10 + 48);
}

int check() {
    int lst = l, p = 1;

    for (int i = l; i <= r; i++) {
        if (a[i] != i) {
            lst = i;
            p = 0;
            break;
        }
    }

    if (p) return 1;

    int L = lst, R, cnt = 0;

    for (int i = lst + 1; i <= r; i++) {
        if (a[i] != i) {
            if (abs(a[i] - a[lst]) != 1 && abs(a[i] - a[i - 1]) != 1) cnt++;
            lst = i;
        }
    }

    R = lst;
    cnt++;

    if (cnt > 3) return 0;

    if (cnt == 1) {
        ans.push({L, R});

        reverse(a + L, a + R + 1);

        return 1;
    }
    else if (cnt == 2) {
        int rr = L, ll = R;

        while (abs(a[rr + 1] - a[rr]) == 1) rr++;
        while (abs(a[ll - 1] - a[ll]) == 1) ll--;

        if (rr == ll - 1) {
            if (a[L] == rr && a[R] == ll) {
                ans.push({ll, R});
                ans.push({L, rr});
                return 1;
            }
            if (a[rr] == R && a[R] == L) {
                ans.push({L, rr});
                ans.push({L, R});
                return 1;
            }
            if (a[ll] == L && a[L] == R) {
                ans.push({ll, R});
                ans.push({L, R});
                return 1;
            }
            return 0;
        }
        else {
            if (a[L] == R && a[R] == L && rr - L == R - ll) {
                ans.push({rr + 1, ll - 1});
                ans.push({L, R});
                return 1;
            }
            if (a[L] == rr && a[rr] == L && a[R] == ll && a[ll] == R) {
                ans.push({ll, R});
                ans.push({L, rr});
                return 1;
            }
            return 0;
        }
    }
    else {
        int rr = L, ll = R;

        while (abs(a[rr + 1] - a[rr]) == 1) rr++;
        while (abs(a[ll - 1] - a[ll]) == 1) ll--;

        for (int i = rr + 2; i < ll; i++) {
            if (abs(a[i] - a[i - 1]) != 1) {
                return 0;
            }
        }

        int len = ll - 1 - rr;

        if (a[rr] == R && a[ll - 1] == L && a[rr + 1] == L + len - 1 && a[R] <= a[ll]) {
            ans.push({L, ll - 1});
            ans.push({L + len, R});
            return 1;
        }
        if (a[ll] == L && a[rr + 1] == R && a[ll - 1] == R - len + 1 && a[L] >= a[rr]) {
            ans.push({rr + 1, R});
            ans.push({L, R - len});
            return 1;
        }
        if (a[L] == R && a[R] == L && a[rr + 1] <= a[ll - 1]) {
            ans.push({rr + 1, ll - 1});
            ans.push({L, R});
            return 1;
        }
        return 0;
    }
}

signed main() {
    n = read(), l = 0, r = 0;

    for (int i = 1; i <= n; i++) {
        a[i] = read();
        if (!l && i != a[i]) l = i;
        if (i != a[i]) r = i;
    }

    if (!l && !r) {
        puts("0");
        return 0;
    }

    for (int i = l; i < r; i++) {
        for (int j = i + 1; j <= r; j++) v.pb({i, j});
    }

    shuffle(v.begin(), v.end(), rnd);

    for (auto [i, j] : v) {
        reverse(a + i, a + j + 1);

        ans.push({i, j});

        if (check()) {
            break;
        }

        ans.pop();

        reverse(a + i, a + j + 1);
    }

    write(ans.size());
    putchar('\n');
    while (!ans.empty()) {
        write(ans.top().first);
        putchar(' ');
        write(ans.top().second);
        putchar('\n');
        ans.pop();
    }
}
```

---

