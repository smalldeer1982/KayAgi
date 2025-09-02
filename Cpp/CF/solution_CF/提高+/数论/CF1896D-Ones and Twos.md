# Ones and Twos

## 题目描述

You are given a $ 1 $ -indexed array $ a $ of length $ n $ where each element is $ 1 $ or $ 2 $ .

Process $ q $ queries of the following two types:

- "1 s": check if there exists a subarray $ ^{\dagger} $ of $ a $ whose sum equals to $ s $ .
- "2 i v": change $ a_i $ to $ v $ .

 $ ^{\dagger} $ An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. In particular, an array is a subarray of itself.

## 说明/提示

Consider the first example:

- The answer for the first query is "YES" because $ a_1+a_2+a_3=2+1+2=5 $ .
- The answer for the second query is "YES" because $ a_1+a_2+a_3+a_4=2+1+2+1=6 $ .
- The answer for the third query is "NO" because we cannot find any subarray of $ a $ whose sum is $ 7 $ .
- After the fourth query, the array $ a $ becomes $ [2,1,2,2,2] $ .
- The answer for the fifth query is "YES" because $ a_2+a_3+a_4+a_5=1+2+2+2=7 $ .

## 样例 #1

### 输入

```
2
5 5
2 1 2 1 2
1 5
1 6
1 7
2 4 2
1 7
3 2
2 2 2
1 6
1 5```

### 输出

```
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：樱雪喵 (赞：12)

原题：[P6859 蝴蝶与花](https://www.luogu.com.cn/problem/P6859)，[[POI2011] LIZ-Lollipop ](https://www.luogu.com.cn/problem/P3514)（不带修）。

突破口肯定是序列只有 $1$ 和 $2$，在这上面找找性质。

先把明显无解的询问排除掉（比如大于 $[1,n]$ 的区间和），考虑什么情况下会无解：存在一个区间 $[l,r]$ 使得 $sum(l,r)=x-1$，且 $a_{r+1}=2$。这样区间和就会把 $x$ 恰好跳过去。  
进一步地，可以证明：如果 $x-1$ 无解，那么 $x$ 一定有解；$x$ 无解当且仅当 $x-1$ 的所有解后面紧跟着的数都是 $2$（或为序列结尾）。

考虑先二分找到一个合法的区间 $sum(1,l)=x-1$，将它向右移动，要保证每移动一次区间的开头结尾都依然是 $2$。这个限制本质上是 $[1,n-l]\cup[l+1,n]$ 里面没有 $1$。

树状数组维护一下即可。单 $\log$ 做法就是把二分的过程换成线段树二分，不过两 $\log$ 甚至能跑过上面两个 $n=2\times 10^6$ 的原题，所以摆了。

下面代码的时间复杂度是 $\mathcal{O}(n\log^2n)$。

```cpp
const int N=2e5+5;
int T,n,q,a[N];
struct BIT
{
    int tr[N];
    il void clear() {for(int i=1;i<=n;i++) tr[i]=0;}
    il void add(int x,int k) {for(;x<=n;x+=x&(-x)) tr[x]+=k;}
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res+=tr[x];return res;}
    il int ask(int l,int r) {return query(r)-query(l-1);}
}tr;
int main()
{
    T=read();
    while(T--)
    {
        n=read(),q=read(); tr.clear();
        for(int i=1;i<=n;i++) a[i]=read(),tr.add(i,a[i]);
        while(q--)
        {
            int op=read(),x=read();
            if(op==2)
            {
                int v=read();
                int now=tr.ask(x,x);
                tr.add(x,v-now);
                continue;
            }
            if(x==1)
            {
                if(tr.ask(1,n)==2*n) printf("NO\n");
                else printf("YES\n");
                continue;
            }
            int l=0,r=n;
            while(l<r)
            {
                int mid=(l+r+1)>>1;
                if(tr.ask(1,mid)<=x-1) l=mid;
                else r=mid-1;
            }
            if(l!=n&&tr.ask(1,l+1)==x) {printf("YES\n");continue;}
            if(tr.ask(1,l)!=x-1) {printf("NO\n");continue;} 
            if(tr.ask(1,n-l)!=2*(n-l)||tr.ask(l+1,n)!=2*(n-l)) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
```

---

## 作者：wxzzzz (赞：11)

### 思路

考虑一下，若存在区间 $[l,r]$，区间和为 $s$，可以得出什么结论。$(r-l+1\ge 2)$

1. $a_{l+1}=2$，则区间 $[l+1,r]$ 的和为 $s-2$。

1. $a_{r-1}=2$，则区间 $[l,r-1]$ 的和为 $s-2$。

1. $a_{l+1}=1$ 且 $a_{r-1}=1$，则区间 $[l+1,r-1]$ 的和为 $s-2$。

可以得出结论，若存在区间 $[l,r]$，区间和为 $s$，满足 $r-l+1\ge 2$，那么必有一段区间的和为 $s-2$。

因此，只要整个序列中有一段区间和 $sum$ 满足 $s\le sum$ 且 $sum$ 与 $s$ 的奇偶性相同，那么 $s$ 就是合法的。

那么只需要知道整个序列的和 $sum1$ 以及和 $sum1$ 奇偶性不同，且最大的区间和 $sum2$。

令 $pl,pr$ 表示整个区间第一次和最后一次出现 $1$ 的位置，可用 set 维护。

显然有 $sum2=\max(\displaystyle\sum_{i=pl+1}^r a_i,\displaystyle\sum_{i=1}^{pr-1}a_i)$，可用树状数组维护。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, q, a[200005], c[200005], s1[200005], s2[200005];
set<int> pos;
set<int>::iterator pl, pr;
void add(int x, int k) {
    while (x <= n) {
        c[x] += k;
        x += (x & -x);
    }
}
int query(int x) {
    int ret = 0;

    while (x) {
        ret += c[x];
        x -= (x & -x);
    }

    return ret;
}
bool check(int x) {
    int sum1 = query(n), sum2;

    if (x <= sum1 && x % 2 == sum1 % 2)
        return 1;

    pl = pos.begin(), pr = pos.end();

    if (!pos.size())
        return 0;

    sum2 = query(n) - query((*pl));
    pr--, sum2 = max(sum2, query((*pr) - 1));
    return x <= sum2 && x % 2 == sum2 % 2;
}
int main() {
    cin >> t;

    while (t--) {
        for (int i = 0; i <= n + 1; i++)
            c[i] = 0;

        cin >> n >> q;
        pos.clear();

        for (int i = 1; i <= n; i++) {
            cin >> a[i], add(i, a[i]);
            s1[i] = s1[i - 1] + a[i];
            s2[i] = s2[i + 1] + a[i];

            if (a[i] == 1)
                pos.insert(i);
        }

        while (q--) {
            int op, x, k;
            cin >> op >> x;

            if (op == 1) {
                if (check(x))
                    puts("YES");
                else
                    puts("NO");
            } else {
                cin >> k;

                if (a[x] == 1)
                    pos.erase(x);

                add(x, -a[x]), a[x] = k, add(x, a[x]);

                if (a[x] == 1)
                    pos.insert(x);
            }
        }
    }

    return 0;
}
```

---

## 作者：bluewindde (赞：5)

**结论：如果序列 $a$ 中存在一段和为 $x$，那么一定存在一段和为 $x-2$。**

证明如下：

> 如果有这样一段和为 $x$ 的区间 $[l,r]$ 的左右端点均为 $1$，那么区间 $[l+1,r-1]$ 的和就为 $x-2$；否则，左右端点至少有一个是 $2$，那么区间 $[l+1,r],[l,r-1]$ 中一定至少有一个和为 $x-2$。证毕。

对于每一个询问 $s$：

1. 如果 $s$ 和序列和 $sum$ 的奇偶性相同。
    - 若 $s\le sum$，有解；
    - 否则无解。
2. 否则，如果序列中存在一个 $1$。记序列去掉最大全为 $2$ 的**前缀**得到的新序列为 $a'$，$sum'=\sum a'$；序列去掉最大全为 $2$ 的**后缀**得到的新序列为 $a''$，$sum''=\sum a''$。
    - 如果 $s<\max\{sum',sum''\}$，有解；
    - 否则无解。

上面写的可能有些难懂，请好好理解。

实现上可以用 `set` 维护第一个 $1$ 和最后一个 $1$ 的位置，$sum'$ 和 $sum''$ 可以根据全局和，用简单的计算得出。

代码

```cpp
#include <iostream>
#include <random>
#include <set>
#include <time.h>

using namespace std;

mt19937 rnd(time(0));
const char *yes[] = {
    "Yes",
    "YES",
    "YeS",
    "YEs",
    "yEs",
    "yES",
    "yeS",
    "yes"};
static inline void printYES() {
    cout << yes[rnd() % 8] << endl;
}
const char *no[] = {
    "No",
    "NO",
    "no",
    "nO"};
static inline void printNO() {
    cout << no[rnd() % 4] << endl;
}

int T, n, q;
int a[100005];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1896D.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> q;
        set<int> ss; // set 维护每个 1 出现的位置
                     // 这是很好的思路，不要像某 bluewindde 一样乱搞线段树维护
        int sum = 0; // 全局和
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] == 1) {
                ss.insert(i);
            }
            sum += a[i];
        }
        while (q--) {
            int op;
            cin >> op;
            if (op == 1) {
                int s;
                cin >> s;
                if (sum & 1) {
                    if (s & 1) { // 奇偶性相同
                        if (s <= sum) {
                            printYES();
                        } else {
                            printNO();
                        }
                    } else { // 奇偶性不同
                        if (ss.empty()) {
                            printNO();
                        } else {
                            int x1 = sum - 2 * (*ss.begin()) + 1; // 去掉前缀
                            int x2 = sum - 2 * (n - (*ss.rbegin()) + 1) + 1; // 去掉后缀
                            if (s <= max(x1, x2)) {
                                printYES();
                            } else {
                                printNO();
                            }
                        }
                    }
                } else {
                    if (s & 1) {
                        if (ss.empty()) {
                            printNO();
                        } else {
                            int x1 = sum - 2 * (*ss.begin()) + 1;
                            int x2 = sum - 2 * (n - (*ss.rbegin()) + 1) + 1;
                            if (s <= max(x1, x2)) {
                                printYES();
                            } else {
                                printNO();
                            }
                        }
                    } else {
                        if (s <= sum) {
                            printYES();
                        } else {
                            printNO();
                        }
                    }
                }
            } else {
                int i, v;
                cin >> i >> v;
                if (a[i] == 1) {
                    ss.erase(i);
                }
                sum -= a[i];
                a[i] = v;
                sum += a[i];
                if (a[i] == 1) {
                    ss.insert(i);
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：Pengzt (赞：5)

[cnblogs](https://www.cnblogs.com/Pengzt/p/17929882.html)

[CF1896D](https://www.luogu.com.cn/problem/CF1896D)

如果只有单次询问其实可以双指针，但是这个难以进行拓展。

考虑找点性质。

发现 $a_i,v\in\{1,2\}$，从值域上下手。发现若存在和为 $S$ 的方案，则一定有和为 $S-2$ 的方案，因为可以直接 $-2$ 或 $-1-1$。

然后就变为找最大的和为奇/偶数了，因为如果最大的都不行就肯定不行了。

于是就只需要支持快速找到最左边和最右边的 $1$ 的位置，用 set 即可。记得判断一下是否存在 $1$ 防止 RE。

代码十分简洁。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum;
int a[200010];
set<int> s[3];
void solve(){
	scanf("%d%d",&n,&m);sum=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),s[a[i]].insert(i),sum+=a[i];
	for(int _=1,opt,x;_<=m;_++){
		scanf("%d%d",&opt,&x);
		if(opt==1){
			if((sum&1)==(x&1)){
				if(sum>=x)puts("YES");
				else puts("NO");
			}else{
				if(!s[1].size())puts("NO");
				else{
					int mx=max(sum-(*s[1].begin())*2+1,sum-(n-(*s[1].rbegin())+1)*2+1);
					if(mx>=x)puts("YES");
					else puts("NO");
				}
			}
		}else{
			int y;scanf("%d",&y);
			sum-=a[x];s[a[x]].erase(x);
			a[x]=y;
			sum+=a[x];s[a[x]].insert(x);
		}
	}
	s[1].clear();s[2].clear();
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：AKPC (赞：3)

考虑每个 $s$ 是否有对应的子区间和为 $s$，因为元素只有 $1$ 以及 $2$，故不难想到分奇偶讨论。

假设 $s$ 对应的区间是 $[l,r]$，讨论 $a_l$ 及 $a_r$ 的值。

- 若 $a_l=1$ 且 $a_r=1$，则 $[l+1,r-1]$ 的和即为 $s-2$。
- 反之，$a_l$ 与 $a_r$ 中必有一个 $2$，去掉这个 $2$ 之后的区间和为 $s-2$。

故对于任意的 $s$，若有符合条件的区间，其区间之和等于 $s$，则一定有符合条件的区间，其和为 $s-2$。

考虑怎么维护这个查询，假设 $sum$ 是 $a$ 中所有元素的和。

查询 $s$ 的时候，如果 $s$ 与 $sum$ 同奇偶，只要 $s\leq sum$，则一定有正整数 $k$ 满足 $s+2k=sum$，固然有解，反之无解。

如果 $s$ 与 $sum$ 不同奇偶，则可以找到一个 $a$ 的前缀或后缀 $a'$，满足 $a'$ 的长度最短且包含仅一个 $1$，可以通过找第一个以及最后一个出现的 $1$ 来求这个 $a'$，只要 $s\leq sum-\sum a'$，则固然有解，反之无解。

可以用一个 `vector` 存储所有值为 $1$ 的元素对应的下标，`vector` 的最小值即为最早出现的 $1$ 对应的下标，最大值同理（当然还是建议用 `set`，`vector` 复杂度太假了有时容易 TLE）。

修改的时候，如果要把 $1$ 改成 $2$，则从 `vector` 内删除该值对应的下标，如果将 $2$ 改成 $1$，则添加进 `vector`。

[code](/paste/t847c9ur)。

---

## 作者：Luzhuoyuan (赞：2)

### 原题链接：
[[to Luogu]](https://www.luogu.com.cn/problem/CF1896D) [[to Codeforces]](https://codeforces.com/contest/1896/problem/D)

### 题意简述：
有一个长度为 $n$ 的序列 $a$，其中所有元素都为 $1$ 或 $2$，要求进行 $q$ 次操作，每次操作为以下之一：

- `1 s`：询问是否存在一个 $a$ 的子串满足其中元素总和为 $s$；
- `2 i v`：将 $a_i$ 改为 $v(v\in \{1,2\})$。

单个测试点 $t$ 组测试用例。

$t\le 10^4;n,q,\sum n,\sum q\le 10^5;s\le 2n;a_i,v\in\{1,2\}$。

### 做法：
首先我们考虑如果只要求一次 1 操作怎么做。首先如果 $s$ 大于序列总和一定是无解的。接着我们注意到可以把问题转化为求一段前缀和和一段后缀和，使得它们不相重合且它们的和等于 $sum-s$，其中 $sum$ 为当前序列总和。以下记 $\displaystyle x=sum-s,pre_i=\sum_{j=1}^i a_j,suf_i=\sum_{j=i}^n a_j$。特别地，$pre_0=suf_{n+1}=0$

那么我们可以维护两个指针 $i,j$，表示当前选择 $pre_i+suf_j$ 这一段。初始时 $i=0,j=n+1$。我们先将 $i$ 向右挪，直到 $pre_i\ge x$。若此时 $pre_i=x$，直接输出 `YES`。否则，由于 $a_i\in \{1,2\}$，必然有 $pre_i=x+1$。我们考虑将 $i$ 和 $j$ 分别向左移动使得 $pre_i+suf_j$ 减少 $1$，那么就可能出现以下的情况：

1. $a_i=1$：此时将 $i$ 左移一位即可。
2. $a_i=2,a_{j-1}=1$：此时可以将 $i$ 与 $j$ 分别左移一位，总和也恰好减少 $1$。
3. $a_i=a_{j-1}=2$：此时需要将 $i,j$ 各左移一位，然后继续尝试调整。

我们注意到，一旦 $i,j$ 满足 1 或 2 两种情况，那么一定是有解的；否则，当 $i=1$ 时都没有满足情况 1,2，那么就是无解的。

直接这样做单次询问是 $O(n)$ 的，但是我们发现若设 $y$ 为最小的 $i$ 使得 $pre_i\ge x$，那么无解当且仅当 $pre_i\ne x$ 且 $a_1=a_2=\dots=a_y=2$，$a_n=a_{n-1}=\dots=a_{n-y+1}=2$。其中第二点可以变为 $pre_y=suf_{n-y+1}=2y$。那么我们只要用**树状数组**简单维护前缀和与后缀和即可。寻找 $y$ 可以用树状数组上二分，可以做到 $O(q \log n)$，但是赛时蒟蒻忘记怎么写了 (qwq)，于是使用了直接二分。单组测试用例时间复杂度 $O(q\log^2 n)$。

### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,q,a[N],c[2][N],x,y,sum;
//c[0]->pre,c[1]->suf
//注：此处 c[1][i] 代表 suf[n-i+1]
inline int read(){
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}//快读
inline void add(int x,int p,int v){
    for(;p<=n;p+=(p&(-p)))
        c[x][p]+=v;
}//树状数组修改
inline int getv(int x,int p){
    int s=0;
    for(;p;p&=(p-1))
        s+=c[x][p];
    return s;
}//查询
inline int find(int x){
    int l=1,r=n,mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(getv(0,mid)>=x)r=mid-1;
        else l=mid+1;
    }
    return l;
}//二分查找 y
signed main(){
    T=read();
    while(T--){
        n=read(),q=read();sum=0;
        for(int i=1;i<=n;i++)c[0][i]=c[1][i]=0;
        for(int i=1;i<=n;i++)
            a[i]=read(),add(0,i,a[i]),add(1,n-i+1,a[i]),sum+=a[i];
        while(q--){
            int op=read();
            if(op==1){
                x=read();
                int tmp=find(sum-x),t=getv(0,tmp);
                if(x>sum)printf("NO\n");
                else if(t==sum-x||x==sum)printf("YES\n");
                else printf("%s\n",(tmp<<1)==t&&t==getv(1,tmp)?"NO":"YES");
            }
            else x=read(),y=read(),add(0,x,y-a[x]),add(1,n-x+1,y-a[x]),sum+=y-a[x],a[x]=y;
        }
    }
    return 0;
}
```
你可以把 `find` 函数换成如下的树状数组上二分以得到（可能）更优的复杂度。
```cpp
inline int find(int x){
    int now=0,s=0;
    for(int i=1<<(int)log2(n);i;i>>=1)
        if((now^i)<=n&&s+c[0][now^i]<x)now^=i,s+=c[0][now];
    return now+1;
}
```
为什么是“可能”？CF 实测 $78\text{ms}\to 78\text{ms}$。(迷

---

以上是题解的全部内容。如果有任何问题，欢迎评论指出啦~(qwq

（逃

---

## 作者：DCH233 (赞：2)

注意到合法的询问大小是 $O(n)$ 级别的。一个自然的想法是把所有合法的询问存下来然后 $O(1)$ 回答。$a_i$ 只能为 $1$ 或 $2$ 的限制肯定是很关键的，考虑其能为我们带来什么性质。

考虑目前已选出一个子串 $a_l,a_{l+1},a_{l+2},...,a_r$，如果希望在此基础上得到一个新的子串，那么只能删去 $a_l$ 或者 $a_r$。经过手玩发现和奇偶性有关，对两端点的值进行分类讨论：

1. $a_l = 2$ 或 $a_r = 2$。此时删去一个 $2$ 可以使得子串和的奇偶性不变。
2. $a_l = a_r = 1$，此时同时删去两端点，子串和奇偶性不变。

故若 $v$ 合法，则 $v - 2$ 也合法。这样我们只需对奇数和偶数分别维护出最大的合法值。具体来说实时维护全局和，处理出最小的前缀或后缀使得删去后奇偶性改变。可以使用可删堆维护，时间复杂度 $O(n \log n)$。

```cpp
const int N = 1e5 + 10;
int n, q;
int a[N], sum;
multiset<int> s;

bool check(int x) {
  if(x % 2 == sum % 2) return x <= sum;
  else if(s.size()) return x <= sum - *s.begin() * 2 + 1;
  else return false;
}

void solve() {
  read(n, q);
  sum = 0, s.clear();
  for(int i = 1; i <= n; ++i) {
    read(a[i]);
    sum += a[i];
    if(a[i] == 1) s.insert(min(i, n - i + 1));
  }
  for(int i = 1; i <= q; ++i) {
    int opt, x, y;
    read(opt);
    if(opt == 1) {
      read(x);
      puts(check(x) ? "YES" : "NO");
    } else {
      read(x, y);
      if(a[x] == 1) s.erase(s.find(min(x, n - x + 1)));
      if(y == 1) s.insert(min(x, n - x + 1));
      sum = sum - a[x] + y, a[x] = y;
    }
  }
}

int main() {
  int T; read(T);
  while(T--) solve();
}
```


---

## 作者：_sunkuangzheng_ (赞：2)

线段树 /jk

树状数组 /jk

提供一种好写的，一只 $\log$ 的 set 做法。

**结论**：如果 $k(k \ge 2)$ 是合法答案，$k-2$ 也是合法答案。

**证明**：如果这个区间左右有至少一个位置是 $2$，直接将它减去；否则，同时减去两边的 $1$ 即可。

那么我们只需要分奇偶维护最大子区间和。

肯定有一种区间是选 $[1,n]$，那么我们要找到一个区间，满足其和的奇偶性与 $\sum \limits_{i=1}^n a_i$ 不同，且这个区间的和最大化。注意到只有 $1$ 会改变奇偶性，我们用一个 set 维护 $1$ 的位置，找到 set 里最大最小元素 $p,q(p \le q)$，显然最大最小元素两边都是 $2$。你希望和尽可能大，肯定希望减掉的 $2$ 尽可能少，那么 $\sum \limits_{i=1}^n a_i - 2\min(p-1,n-q)-1$ 就是答案。

时间复杂度 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int T,n,t[N],re,a[N],q,op,x,y;set<int> s;
int sol(){
    if(s.size()){
        int p = *s.begin(),q = *(--s.end());
        return min((p - 1),(n - q)) * 2 + 1;
    } return 1e9;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> T;
    while(T --){
        cin >> n >> q,s.clear();int sm = 0,ans[2] = {(int)-1e9,(int)-1e9};
        for(int i = 1;i <= n;i ++) if(cin >> a[i],sm += a[i],a[i] == 1) s.insert(i);
        ans[sm % 2] = sm,ans[!(sm & 1)] = sm - sol();
        while(q --){
            cin >> op >> x;
            if(op == 1) if(x <= ans[x % 2]) cout << "YES\n"; else cout << "NO\n";
            else if(cin >> y,a[x] != y){
                    if(a[x] == 1) s.erase(x); else s.insert(x);
                    sm += y - a[x],ans[sm % 2] = sm,ans[!(sm & 1)] = sm - sol(),a[x] = y;
                }
        }
    }
}
```

---

## 作者：WaterSun (赞：1)

# 思路

令 $s_{l,r}$ 表示 $\sum_{i = l}^{r}{a_i}$，那么考虑如下的情况：

1. $a_l = 2$，则有 $s_{l + 1,r} = s_{l,r} - 2$。

2. $a_r = 2$，则有 $s_{l,r - 1} = s_{l,r} - 2$。

3. $a_l = 1,a_r = 1$，则有 $s_{l + 1,r - 1} = s_{l,r} - 2$。

所以说，你发现如果一段区间的和为 $S$，那么在它的子区间中一定有一个和为 $S - 2$ 的区间。所以不难发现如果有一个区间的和 $sum$ 满足 $sum \equiv x \pmod 2 \wedge sum \geq x$（其中 $x$ 为询问的目标和），则这个问题是一定合法的。

如果 $s_{1,n} \equiv x \pmod 2$，则直接选取整个区间即可。

考虑维护区间中最左的 $1$ 和最右的 $1$ 的位置分别记作 $l,r$。那么 $a_{1 \sim (l - 1)}$ 和 $a_{(r + 1) \sim n}$ 都是 $2$ 不会影响和的奇偶性，又因为满足合法的条件中需满足 $sum \geq x$，所以我们还想希望 $sum$ 更大。因此我们选取 $(l,n]$ 和 $[1,r)$ 区间计算即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,q;
int arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int sum = 0;
    set<int> st;
    n = read();
    q = read();
    for (re int i = 1;i <= n;i++){
        arr[i] = read();
        sum += arr[i];
        if (arr[i] == 1) st.insert(i);
    }
    while (q--){
        int op;
        op = read();
        if (op == 1){
            int x;
            x = read();
            if ((sum & 1) == (x & 1) && sum >= x) puts("YES");
            else if (st.empty()) puts("NO");
            else{
                int l = *st.begin();
                int r = *st.rbegin();
                int sl = sum - (l - 1) * 2 - 1,sr = sum - (n - r) * 2 - 1;
                if (((sl & 1) == (x & 1) && sl >= x) || ((sr & 1) == (x & 1) && sr >= x)) puts("YES");
                else puts("NO");
            }
        }
        else{
            int x,k;
            x = read();
            k = read();
            sum = sum - arr[x] + k;
            if (arr[x] == 1) st.erase(x);
            if (k == 1) st.insert(x);
            arr[x] = k;
        }
    }
}

int main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：SunsetLake (赞：1)

来自机房大佬 [FFT](https://www.luogu.com.cn/user/806728) 的简单解法。

## 思路

首先有个结论：如果 $a$ 中存在一个子串的和为 $x$ ($x>2$)，那么也就一定存在一个子串之和为 $x-2$。怎么证明？其实和为 $x$ 的子串有 $3$ 种情况：

- $\text{1\dots 1}$ 两边都为 $1$ 时把两边删去就能得到 $x-2$。
- $\text{2\dots 1}$ 一边是 $2$ 一边是 $1$ 时删 $2$ 即可。
- $\text{2\dots 2}$ 两边都是 $2$ 随便删一个即可。

有了这个结论，我们就可以维护一个区间总和 $sum$。当 $s>sum$ 时肯定不存在，先判掉。接下来如果 $s \equiv sum\pmod 2$，也就是 $s$ 与 $sum$ 奇偶性相同时，根据上面的结论 $sum$ 一直减 $2$ 就能得到 $s$ 了。最后一种情况 $s$ 与 $sum$ 奇偶性不同时，我们就需要一些 $1$ 去改变 $sum$ 的奇偶性。找到最左边的 $1$ 的位置，记为 $l$，那么在 $l$ 前面的全部是 $2$，删去无法改变 $sum$ 奇偶，故必须再删去 $l$ 位置的一个 $1$，才能让 $sum$ 与 $s$ 奇偶相同。这时就只需判断去掉前 $l$ 个数的 $sum^{\prime}$ 是否 $\ge s$，满足条件就可以一直减 $2$ 得到 $s$ 了。对于最右边的 $1$ 做一次相同的判断即可。

维护的话选用 `set`，将每个 $1$ 的位置存入 set 中。修改就把新的 $1$ 位置加入（或者删除旧的 $1$ 位置），同时更新一下 $sum$ 就好了。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n,a[2000005],sum,q;
set<int>s;
void solve(){
	while(!s.empty())s.erase(s.begin());
	cin>>n>>q;
	sum=0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum+=a[i];
		if(a[i]==1)s.insert(i);	
	}
	while(q--){
		int sl;
		char op;
		cin>>op>>sl;
		if(op==1){
			if(sl>sum){
				cout<<"NO"<<endl;
				continue;
			}
			if(sl%2==sum%2){//奇偶性相同
				cout<<"YES"<<endl;
				continue;
			}
			if(s.empty()){//没有1，sum、s奇偶性又不一样就无解
				cout<<"NO"<<endl;
				continue;
			}
			int l=*s.begin();
			auto p=s.end();p--;
			int r=*p;//获取最左、最右的1的位置
			if(sum-(l-1)*2-1>=sl||sum-(n-r)*2-1>=sl)cout<<"YES"<<endl;//去掉前面和后面判断
			else cout<<"NO"<<endl;
		}
		else{
			int x;
			cin>>x;
			if(a[sl]==x)continue;
			if(a[sl]==1)s.erase(s.find(sl));//更新
			else s.insert(sl);
			sum+=x-a[sl];
			a[sl]=x;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：1)

Modified from [cnblog](https://www.cnblogs.com/No-play-Yes-splay/p/CodeTON-round-7-solution.html)。

# [CF1896D Ones and Twos](https://www.luogu.com.cn/problem/CF1896D)

## 题意

给出一个数组 $a_1,a_2,\ldots,a_n$，执行 $q$ 次操作：

- 单点修改；
- 给出 $s$，查询是否存在一段区间的和为 $s$。

$n,q\le10^5$，任何时刻 $a_i\in\{1,2\}$。

## 题解

设 $f_{l,r}=a_{l}+a_{l+1}+\ldots+a_r$。

先看查询操作。

考虑先搞出来是否存在一段**前缀**的和等于 $s$。

如果存在答案就是 $\texttt{YES}$ 了。那不存在前缀的时候，什么时候答案是 $\texttt{NO}$ 呢？

**下面考虑无解的情况。**

首先，如果整个数组的元素加起来还不到 $s$，那直接就无解了。

否则，设 $p$ 满足 $f_{1,p}<s,f_{1,p+1}>s$。

由于 $a_i$ 只能取 $1$ 或 $2$，所以只能 $f_{1,p}=s-1,f_{1,p+1}=s+1$。这说明 $a_{p+1}$ 一定为 $2$。

然后观察到 $f_{2,p+1}=f_{1,p+1}-a_1=s+1-a_1\ne s$，所以 $a_1$ 也为 $2$。

又由于 $f_{2,p+2}=f_{2,p+1}+a_{p+2}=s-1+a_{p+2}$，所以 $a_{p+2}=2$。

以此类推。那么是不是要求 $a$ 数组全是 $2$ 呢？

不是的。当 $a=[2,1,2],s=4$ 时是无解的。

可以发现，当右边顶到 $n$ 的时候就无法滚下去了。

再稍微推一下，可以发现它只要求 $a_1,a_2,\ldots,a_{n-p},a_{p+1},\ldots,a_n$ 都是 $2$ 就无解。

于是做完了。$1$ 的位置可以 `set` 维护，找 $p$ 的话直接二分即可。由于带单点修改，树状数组拍上去即可。

时间复杂度：$\Theta(n\log^2n)$，如果用倍增之类的可以降到 $\Theta(n\log n)$。

```cpp
const int N=100005;
int n,q;
int a[N];
set<int>s1;
int c[N];
void add(int x,int v){while(x<=n)c[x]+=v,x+=x&-x;}
int query(int x){int r=0;while(x)r+=c[x],x-=x&-x;return r;}
void Solve(int CASE)
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1)s1.insert(i);
		add(i,a[i]);
	}
	while(q--)
	{
		int op,x;
		cin>>op>>x;
		if(op==1)
		{
			int l=1,r=n;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(query(mid)>x)r=mid-1;
				else l=mid+1;
			}//r
			if(query(r)==x){puts("YES");continue;}
			else if(r==n&&query(r)<x-1){puts("NO");continue;}
			else puts(s1.empty()||*s1.begin()>n-r&&*s1.rbegin()<=r?
				"NO":"YES");
		}
		else
		{
			int v;cin>>v;
			if(a[x]==v)continue;
			a[x]=v;
			add(x,v==2?1:-1);
			if(v==2)s1.erase(x);
			else s1.insert(x);
		}
	}
}
```

---

## 作者：lyhqwq (赞：0)

# Solution

一眼题，这能蓝？

如果我们能找到一个前缀的和为 $x$，那么答案为 YES。

否则一定可以找到一个前缀 $[1,p]$ 的和为 $x+1$，此时我们只需要在 $[1,n-p+1]$ 和 $[p,n]$ 中找到一个 $1$ 即可。

用树状数组维护区间和可以做到 $O(n\log^2 n)$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int _;
int n,q;
int a[N];
namespace BIT{
    int tree[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int v){
        for(int i=x;i<=n;i+=lowbit(i)) tree[i]+=v;
    }
    int query(int x){
        int ans=0;
        for(int i=x;i;i-=lowbit(i)) ans+=tree[i];
        return ans;
    }
    int Q(int l,int r){return query(r)-query(l-1);}
}
using namespace BIT;
int main(){
    scanf("%d",&_);
    while(_--){
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++) tree[i]=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),update(i,a[i]);
        while(q--){
            int op,x,v;
            scanf("%d%d",&op,&x);
            if(op==1){
                int l=1,r=n,p=0;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(query(mid)>=x) p=mid,r=mid-1;
                    else l=mid+1;
                }
                if(!p){puts("NO");continue;}
                if(query(p)==x) puts("YES");
                else{
                    if(query(n-p+1)!=2*(n-p+1)||query(n)-query(p-1)!=2*(n-p+1)) puts("YES");
                    else puts("NO");
                }
            }
            else{
                scanf("%d",&v);
                update(x,-a[x]);
                a[x]=v;
                update(x,a[x]);
            }
        }
    }
    return 0;
}

```

---

## 作者：xixisuper (赞：0)

# CF1896D Ones and Twos 题解

一道趣味思维题。

这边提供一个思路不太一样的单 $\log$ 做法。

## 思路

由于序列中全部都是 $1$ 或 $2$ ，所以有以下性质：

**如果序列所有数的和大于 $s$，且序列中不存在和为 $s$ 的子段，那必然存在一个和为 $s+1$ 的子段。**

证明如下：

假设序列中不存在和为 $s$ 的子段。由于整个序列的和大于 $s$，我们能够找到**以第一个数为左端点，使得区间和大于 $s$ 的距离左端最近的右端点。**

如果此时该区间和为 $s+2$，则若右端点为 $2$，那一定存在区间的和为 $s$，与假设相矛盾；则此时右端点只能为 $1$，所以一定存在区间和为 $s+1$ 的区间，又与该区间的定义相矛盾。

通过数学归纳我们发现，**如果序列中不存在和为 $s$ 的子段，那以第一个数为左端点，使得区间和大于 $s$ 的距离左端最近的右端点的区间和一定为 $s+1$。**

证毕。

好，我们知道了这个性质之后怎么用呢？考虑如果单次询问，那有一个浅显易懂的双指针做法，**而如果要让和为 $s$ 的区间不存在，在转移时，该区间的左右端点必须都为 $2$。**

所以当且仅当存在一个区间和为 $s+1$，且该区间后方全部都是 $2$，等长情况下的前缀也全部都是 $2$，$s$ 才会不存在。

因此，我们可以使用 **线段树维护序列中前缀连续 $2$ 的个数，后缀连续 $2$ 的个数**，然后判断，这样单次查询为 $O(\log n)$ 级别。而线段树支持在线修改，于是我们就用单 $\log$ 顺利 $A$ 掉了这道题。

## 代码

蒟蒻代码，不喜勿喷。

```cpp
#include <iostream>
#define ll int
#define mid ((l+r)>>1)
using namespace std;
const ll N=1e5+1;
ll sum[N<<2];
ll qz[N<<2],hz[N<<2]; 
ll num[N];
ll head;
void push_up(ll l,ll r,ll x){
	sum[x]=sum[x<<1]+sum[(x<<1)|1];
	if(qz[x<<1]==mid-l+1) qz[x]=qz[x<<1]+qz[(x<<1)|1];
	else qz[x]=qz[x<<1];
	if(hz[(x<<1)|1]==r-mid) hz[x]=hz[(x<<1)|1]+hz[x<<1];
	else hz[x]=hz[(x<<1)|1];
}
void build(ll l,ll r,ll x){
	if(l==r){
		sum[x]=num[l];
		if(num[l]==2) qz[x]=hz[x]=1;
		return;
	}
	build(l,mid,(x<<1));
	build(mid+1,r,(x<<1)|1);
	push_up(l,r,x);
}
void chg(ll l,ll r,ll p,ll v,ll x){
	if(l==r&&l==p){
		sum[x]=v;
		if(v==1) qz[x]=hz[x]=0;
		else qz[x]=hz[x]=1;
		return;
	}
	if(p<=mid) chg(l,mid,p,v,x<<1);
	else chg(mid+1,r,p,v,(x<<1)|1);
	push_up(l,r,x);
}
ll query(ll L,ll R,ll l,ll r,ll x){
	if(L<=l&&r<=R) return sum[x];
	ll ret=0;
	if(L<=mid) ret+=query(L,R,l,mid,x<<1);
	if(R>mid) ret+=query(L,R,mid+1,r,(x<<1)|1);
	return ret;
}
ll n,m;
void solve(){
	cin>>n>>m;
	for(ll i=0;i<=n;i++) num[i]=0;
	for(ll i=0;i<=(n<<2);i++) sum[i]=qz[i]=hz[i]=0; 
	for(ll i=1;i<=n;i++) cin>>num[i];
	head=1;
	build(1,n,head);
	while(m--){
		ll opt,p,k;
		cin>>opt;
		if(opt==1){
			cin>>k;
			if(qz[head]==0){
				if(sum[head]>=k) cout<<"YES\n";
				else cout<<"NO\n";
			}
			else{
				ll qian=qz[head],hou=hz[head];
				ll mob=n-min(qian,hou);
				if(!mob){
					if(k%2) cout<<"NO\n";
					else{
						if(k<=sum[head]) cout<<"YES\n";
						else cout<<"NO\n";
					}
				}
				else{
					ll qu=query(1,mob,1,n,head);
					if(qu>=k||(!((k-qu)%2)&&((k-qu)/2)<=min(qian,hou))) cout<<"YES\n";
					else cout<<"NO\n";
				}
			}
		} 
		else{
			cin>>p>>k;
			chg(1,n,p,k,head);
		} 
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	ll T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：AKonjac_ (赞：0)

[CF1896D](https://codeforces.com/problemset/problem/1896/D)

提供一种 ~~巨麻烦~~ 的 bitset 做法。

对于一个串，我们写一个前缀和，用树状数组动态维护，则位置 $1\leq i < j \leq n$ 对应子串的和可以表示成 $s_j-s_{i-1}$ ，原题就是求 $s_j-s_{i-1}=s$ 是否可以满足。

受 [这道题](https://www.luogu.com.cn/problem/P3674) 的启发，这道题里我们可以用 bitset 维护这个前缀和数组，对于一个 ```bitset<N> f``` ，通过位运算判断 ```f&(f>>s)``` ，若结果不为零，则说明存在这样的子串。

对于修改，我们发现，每次修改对于 bitset 中 $s_j-1$ 位置之前的位无影响，对于 $s_j$ 之后的位置，右移或左移一位即可。

我们构造两个 bitset 串，一个串满足前 $s_j-1$ 位都为 $1$ ，另一个串为前一个串按位取反。将原串与这两个串分别与一下，后一个串左/右移一位，再或在一起，就完成了修改。

现在的问题在于，如何快速构造这样的两个串。

暴力不行，我们就用空间换时间。我们采取分块的思想，设块长为 $k$ ，构造 $\frac N k$ 个串，每个串依次增加 $k$ 个 $1$。每次根据 $s_j$ 暴力修改离他最“近”的串，就可以在 $O(k)$ 的时间内构造出我们要的串。

协调一下时间空间，取 $k=N^{\frac 13}$ ，再稍稍卡常就可以通过本题了。


```cpp
#pragma GCC optimize(2)
#include<iostream>
#include<bitset>
#include<cmath>
using namespace std;
const int N=2e5+10,K=4e3;
int T,n,q,len;
bitset<N> s[K];
bitset<N> f,tmp,ttmp,g,h;
int k[N],a[N],t[N];
int read1() {
	int x=0;
	char ch=getchar();
	while(ch>'9' || ch<'0') ch=getchar();
	while(ch<='9' && ch>='0') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
void write1(int x) {
	if(x>9) write1(x/10);
	putchar(x%10+'0');
}
int lowbit(int x){
	return x&(-x);
}
void change(int x,int d){
	while(x<=n) t[x]+=d,x+=lowbit(x);
}
 
int sum(int x){
	int ans=0;
	while(x>0) ans+=t[x],x-=lowbit(x);
	return ans;
}
void init() {
	s[0].set(0);
	len=pow(N,0.33);
	for(int i=1; i<N; ++i) k[i]=(i-1)/len+1;
	for(int i=1; i<=k[N-1]; ++i) {
		s[i]=s[i-1];
		for(int j=(i-1)*len+1; j<=min(i*len,N-1); ++j) s[i].set(j);
	}
	
}
void solve() {
	n=read1(),q=read1();
	f=s[0];
	int ssum=0;
	for(int i=1;i<=n+n;++i) t[i]=0;
	for(int i=1; i<=n; ++i) {
		a[i]=read1();
		ssum+=a[i];
		f.set(ssum);
		change(i,a[i]);
	}
	for(int i=1,op,j,v; i<=q; ++i) {
		op=read1();
		if(op==1) {
			j=read1();
			if((f&(f>>j)).any()) putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
			else putchar('N'),putchar('O'),putchar('\n');
		} else {
			j=read1(),v=read1();
			if(v==a[j]) continue;
			int sumj=sum(j);
			int tmpk=k[sumj-1];
			tmp=s[tmpk];
			for(int t=min(N-1,tmpk*len); t>=sumj; --t) tmp.reset(t);
			ttmp=tmp;
			ttmp.flip();
			g=tmp&f,h=ttmp&f;
			if(v-a[j]==1) f=(g)|(h<<1);
			else f=(g)|(h>>1);
			change(j,v-a[j]);
			a[j]=v;
		}
	}
}
int main() {
	T=read1();
	init();
	while(T--) solve();
	
	return 0;
}
```


---

## 作者：baka24 (赞：0)

#### update:添加了语法高亮
这种题一般要么是数据结构，要么是有特殊性质，此题属于后者。

我们发现当一个只有 $1$ 和  $2$ 的序列的前缀和是一串连续的数的子序列，即，当 $a_i$ 为 $2$ 时他会**跳过**某些数。但此题并非要求前缀而是子串，所以当一串由 $1$ 和 $2$ 构成的序列开头是 $1$ 时，我们可以通过控制要不要这个 $1$ 来构造出一个连续的数串。

所以，此时有一个思路：让每个 $1$ **管控**的数列尽量长。我们可以用 ```set``` 维护每个 $1$ 的位置，再用树状数组维护每个 $1$ 的前后缀。

每次查询先取出最靠前和最靠后的 $1$ 得到其前后缀的最大值，与 $x$ 进行比较，如果大于 $x$，就直接输出 ```YES```，否则就先判断 $x$ 与最大前后缀的的差是否为偶数（因为包含最靠边的 $1$ 的最大前后缀剩下的部分一定全是偶数），再判断 $x$ 是否小于 $sum$。

对于全 $2$ 的情况还要特判一下，否则会 RE。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int t,n,m,a[MAXN],c[MAXN];
set<int>st;
int lb(int x){return x&(-x);}
int query(int l,int r){
    int rt=0;
    for(int i=r;i>=1;i-=lb(i)){
        rt+=c[i];
    }
    for(int i=l-1;i>=1;i-=lb(i)){
        rt-=c[i];
    }
    return rt;
}
void update(int x,int y){
    int rx=y-query(x,x);
    for(int i=x;i<=n;i+=lb(i)){
        c[i]+=rx;
    }
}
void slv(){
    st.clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)c[i]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]==1)st.insert(i);
        update(i,a[i]);
    }
    for(int i=1;i<=m;i++){
        int opt,x,y;
        scanf("%d",&opt);
        if(opt==1){
            scanf("%d",&x);
            if(st.empty()){
                int sum=query(1,n);
                if(!(x&1)&&x<=sum){
                    printf("YES\n");
                }
                else {
                    printf("NO\n");
                }
            }
            else{
                auto l=st.begin(),r=st.end();r--;
                int tmp1=query(*l,n),tmp2=query(1,*r),sum=query(1,n);
                if(x<=sum&&(tmp1>x||tmp2>x||!((tmp1-x)&1)||!(tmp2-x)&1)){
                    printf("YES\n");
                }
                else{
                    printf("NO\n");
                }
            }
        }
        else{
            scanf("%d%d",&x,&y);
            if(y==1)st.insert(x);
            else st.erase(x);
            update(x,y);
        }
    }
}
signed main(){
    scanf("%d",&t);
    while(t--){
        slv();
    }
    return 0;
}
```


---

## 作者：Drind (赞：0)

### 题目解析

本题要求维护一个只有 1 和 2 的序列，支持单点修改和查询是否有出现和为 $k$ 的子数组。

因为这个序列比较特殊，只有两个数字，所以一定有一些什么特殊的性质。我们可以从奇偶性上考虑，于是我们发现如果存在一个长度为 $k$ 的子数组，那么一定有一个长度为 $k-2$ 的子数组，证明如下：

假设这个子数组最左端和最右端有一个 2，那么去掉这个 2 即可，否则把两端的 1 去掉即可。

然后我们就可以维护区间和和最左端最右端第一个 1 的位置，使用数据结构维护即可，我用的是线段树。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

inline int lowbit(int x){
	return x&(-x);
}

struct segtree{
	int l,r,mx,mn;
}tree[N*4];

int a[N];

void pushup(int x){
	tree[x].mx=max(tree[x*2].mx,tree[x*2+1].mx);
	tree[x].mn=min(tree[x*2].mn,tree[x*2+1].mn);
}

void build(int x,int l,int r){
	tree[x].l=l; tree[x].r=r;
	tree[x].mx=0; tree[x].mn=1e8;
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid); build(x*2+1,mid+1,r);
	pushup(x);
}

void modify(int x,int p,int val){
	if(tree[x].l==tree[x].r&&tree[x].l==p){
		if(val==0){
			tree[x].mx=0;
			tree[x].mn=1e8;
			return;
		}
		tree[x].mx=tree[x].mn=val;
		return;
	}
	if(tree[x].r<p||tree[x].l>p) return;
	modify(x*2,p,val); modify(x*2+1,p,val);
	pushup(x);
}



inline void fake_main(){
	int n,m; cin>>n>>m;
	int tot=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]; tot+=a[i];
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		if(a[i]==1) modify(1,i,i);
		else modify(1,i,0);
		
	}
	
	for(int i=1;i<=m;i++){
		int op; cin>>op;
		if(op==1){
			int s; cin>>s;
			if(s%2==tot%2){//如果查询的值和整个序列奇偶性相同，那只要小于整个序列和就可以
				if(s<=tot) cout<<"YES\n";
				else cout<<"NO\n";
				continue;
			}
			int tmp=tot;
			int l=tree[1].mn,r=tree[1].mx;
			if(l<1||l>n) l=n+1;
			if(r<1||r>n) r=0;
			if(l==n+1&&r==0){//如果没有 1，输出 NO
				cout<<"NO\n";
				continue;
			}
			
			if(l<n-r+1){//找到离边缘最近的一个 1，然后一路删除直到到那个 1 为止，改变整个序列的奇偶性
				tmp-=(l-1)*2+1;
			}else tmp-=(n-r)*2+1;
			
			if(s<=tmp) cout<<"YES\n";
			else cout<<"NO\n";
		}
		else{
			int p,val; cin>>p>>val;
			if(val==1)//线段树维护 1 的位置，所以如果是 2 就赋值成 0
				modify(1,p,p); 
			else modify(1,p,0);
			
			tot=tot-a[p]+val;
			a[p]=val;
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：Maverik (赞：0)

##### Statement

有一个长度为 $n$ 的序列 $a$，其中所有元素都为 $1$ 或 $2$，要求进行 $q$ 次操作，每次操作为以下之一：

- `1 s`：询问是否存在一个 $a$ 的子串满足其中元素总和为 $s$；
- `2 i v`：将 $a_i$ 改为 $v(v\in \{1,2\})$。

$1\le n,q\le 10^5$

##### Solution

不懂为啥要二分，上面题解是不是做麻烦了。考虑 $s$ 是偶数的时候，问题是平凡的。当 $s$ 为奇数的时候，至少需要扣掉一个 $1$ 变成偶数，相当于钦定一个 $1$ 的位置，然后左右两侧拓展，显然如果左右两边 $1$ 个数仍然相同，那必然能取到所有偶数，所以很容易想到当：$cnt1$ 与 $s$ 的奇偶性相同的时候，必然能取到所有位置，不同的时候只能取到最左边的 $1$ 右侧的所有位置，或者是最右边的 $1$ 左侧所有位置。拿个 set 存一下就好了。评蓝有点过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int n,Q,a[maxn];
struct BIT
{
    int c[maxn];
    inline int lowbit(int x){return x&(-x);}
    inline void add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
    inline int query(int x){int res=0;for(;x;x-=lowbit(x))res+=c[x];return res;}
    inline int qsum(int l,int r){if(l>r)return 0;return query(r)-query(l-1);}
}tr;
inline void modify(int x,int y){tr.add(x,y-a[x]),a[x]=y;}
set<int>s;
inline void solve()
{
    
    cin>>n>>Q;
    for(int i=1,x;i<=n;i++) cin>>x,modify(i,x);
    for(int i=1;i<=n;i++) if(a[i]==1) s.insert(i);
    for(int i=1,opt,x,y;i<=Q;i++)
    {
        cin>>opt>>x;
        if(opt==1)
        {
            int v=s.size();
            if((x^v)&1)
            {
                if(s.empty()) cout<<"NO\n";
                else
                {
                    if(x<=tr.qsum(*s.begin()+1,n)) cout<<"YES\n";
                    else if(x<=tr.qsum(1,*prev(s.end())-1)) cout<<"YES\n";
                    else cout<<"NO\n";
                }
            }
            else
            {
                if(x<=tr.qsum(1,n)) cout<<"YES\n";
                else cout<<"NO\n";
            }
        }
        else
        {
            cin>>y;
            if(y==2) s.erase(x);
            else s.insert(x);
            modify(x,y);
        }
    }
    s.clear();
    for(int i=0;i<=n;i++) a[i]=tr.c[i]=0;
}
signed main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);
    int T;cin>>T;while(T--)solve();
}

```





---

## 作者：huangrenheluogu (赞：0)

发现序列只有 $1,2$，显然这里是突破口。

考虑两个数的性质：相比 $1$ 而言，用 $2$ 更改，序列总和会变多。

因此，我们发现，两端的 $1$ 是非常重要的。

找出两端的 $1$，用线段树二分即可。

假设我们找到最左边的 $1$（记 $a_{posl}=1$），那么数列显然是这个样子：

$2,2,2,\dots2,1,?,?,?,\dots,?$。

$1$ 的左边肯定是 $2$，右边不确定。

那么，如果 $a_{posl}\sim a_n$ 的总和如果大于等于 $s$，就说明右边可以删掉一些数字，左边的 $1$ 用来“微调”。

右边同理。

特判一点，记 $a_1\sim a_n$ 为 $S$，如果 $S$ 和 $s$ 同奇偶，即使不用微调的方法，删 $2$ 也可以。

如果不能用微调（两边到端点的总和都小于 $s$），那么显然可以删掉连续的 $2$。

就以左边举例，如果 $\sum\limits_{i=posl}^na_i<s$，那么可以加上左边若干个 $2$，而如果 $s$ 和 $S$ 同奇偶，那么说明 $\sum\limits_{i=posl}^na_i$ 和 $s$ 同奇偶。同时注意 $s$ 需要小于等于 $S$。

```cpp
#include<bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 1e5 + 5;
int n, q, T, o, x, v, a[N], S, sum[N << 2], sum1[N << 2], posl, posr;
inline void push_up(int p){
	sum[p] = sum[ls] + sum[rs];
	sum1[p] = sum1[ls] + sum1[rs];
}
inline void build(int p, int l, int r){
	if(l == r){
		sum[p] = a[l];
		sum1[p] = a[l] == 1 ? 1 : 0;
		return ;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	push_up(p);
}
inline void modify(int p, int l, int r, int x, int val){
	if(l == r){
		sum[p] = val;
		sum1[p] = val == 1 ? 1 : 0;
		return ;
	}
	int mid = l + r >> 1;
	if(mid >= x) modify(ls, l, mid, x, val);
	else modify(rs, mid + 1, r, x, val);
	push_up(p);
}
inline int query(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return sum[p];
	int mid = l + r >> 1, res = 0;
	if(mid >= x) res += query(ls, l, mid, x, y);
	if(mid < y) res += query(rs, mid + 1, r, x, y);
	return res;
}
inline int queryL(int p, int l, int r){
	if(!sum1[p]) return -1;
	if(l == r) return l;
	int mid = l + r >> 1;
	if(sum1[ls]) return queryL(ls, l, mid);
	return queryL(rs, mid + 1, r);
}
inline int queryR(int p, int l, int r){
	if(!sum1[p]) return -1;
	if(l == r) return l;
	int mid = l + r >> 1;
	if(sum1[rs]) return queryR(rs, mid + 1, r);
	return queryR(ls, l, mid);
}
inline void check(){
	if(S < x){
		printf("NO\n");
		return ;
	}
	posl = queryL(1, 1, n);
	posr = queryR(1, 1, n);
	if(~posl){
		if(x <= query(1, 1, n, posl, n)){
			printf("YES\n");
			return ;
		}
		if(x <= query(1, 1, n, 1, posr)){
			printf("YES\n");
			return ;
		}
	}
	if((x - S) & 1) ;
	else{
		printf("YES\n");
		return ;
	}
	printf("NO\n");
	return ;
}
int main(){
	scanf("%d", &T);
	while(T--){
		S = 0;
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			S += a[i];
		}
		build(1, 1, n);
		while(q--){
			scanf("%d", &o);
			if(o == 1){
				scanf("%d", &x);
				check();
			}
			else{
				scanf("%d%d", &x, &v);
				modify(1, 1, n, x, v);
				S += v - a[x];
				a[x] = v;
			}
		}
	}
	return 0;
}
/*
1
5 1
2 1 2 1 2
1 7
*/
```

---

## 作者：AlicX (赞：0)

## Solution 

令 $l,r$ 能使 $\sum\limits_{i=l}^{r} a_i=S$。

考虑先令 $l=1$，那么如果存在 $\sum \limits_{i=1}^{r}=S$，即输出 `YES`。如果没有，则一定有 $\sum \limits_{i=1}^{r}=S-1$，且 $a_{r+1}=2$。

考虑对 $l,r$ 进行调整：将 $l$ 向左移，$r$ 向右移。可以发现当 $1 \sim l'$ 全部为 $2$，且 $r \sim r'$ 全部为 $2$，且 $a_{r'+1}=1$ 或 $a_{l'+1}=1,a_{r'}=2$ 时，条件成立。

于是考虑用线段数维护出区间内 $1$ 出现的次数，记为 $cnt1$，$2$ 的出现次数显然可以用区间长度减去 $cnt1$ 得到，记为 $cnt2$。然后用二分求出 $1$ 左边第一次出现的 $1$ 的位置，记为 $pos1$，以及 $r$ 左边第一次出现的 $1$，记为 $pos2$。

接下来考虑答案：如果 $pos1=-1$，显然无解；如果 $pos2=-1$，且 $pos1-1 >n-r$，说明 $r$ 后面没有足够的 $2$，无解。当 $pos1,pos2$ 都不为 $-1$ 时，显然有解。

考虑再记录区间和，方便找到初始的 $r$。显然我们可以使用二分套线段树的方法，时间复杂度为 $O(n\log^2n)$，但在线段树上二分可以优化到单 $\log$。



---

