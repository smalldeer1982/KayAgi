# Tokitsukaze and Good 01-String (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1' ( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good? Meanwhile, she also wants to know the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively, the number of subsegments of it is $ 2 $ . There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100", the number of subsegments of them are $ 2 $ , $ 4 $ , $ 4 $ respectively. It's easy to find that the minimum number of subsegments among all solutions with the minimum number of operations is $ 2 $ .

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110```

### 输出

```
3 2
0 3
0 1
0 1
3 1```

# 题解

## 作者：jasonliujiahua (赞：4)

# CF1678B2 Tokitsukaze and Good 01-String 


## 题意简述：

给定一个 $01$ 串，问其最少修改几次可以合法。合法的定义为：

如果将该串按最长的连续的 $0/1$ 分段，每段的长为偶数，那么该串合法。如 $11001111$ 就是一个合法的 $0/1$ 串，可以分为 $11$，$00$，$1111$ 这三段。每段的长度均为偶数。

在最少操作次数的前提下，还要输出修改使其合法后的最少的段数。

## 题目分析：
### 第一问：

可以发现如果每一段的长度都是偶数，那么该 $0/1$ 串可以收缩为长度为 $\frac{n}{2}$、每段长为原来 $\frac{1}{2}$ 的一个串。也就是说：相邻的 $s_{2k}$ 和 $s_{2k+1}$ 可以合为一个。

由此可以发现：如果 $s_{2k} \not = s_{2k+1}$，我们就需要一次操作去更改 $s_{2k}$ 或 $s_{2k+1}$ 使得其相等，并让 $ans$ 加一。

### 第二问：

在第一问的前提下可以看出：$s_{2k}$ 和 $s_{2k+1}$ 有两种情况：

- 情况一：$s_{2k} = s_{2k+1}$。

  这对数就不应浪费操作次数去修改，从而数值不变。

- 情况二：$s_{2k} \not = s_{2k+1}$。

  这对数对 $ans$ 有贡献，数值却是不定的，从而 $s_{2k}$ 和 $s_{2k+1}$ 也就可以依附于左边或右边像第一种情况那样的“对”，因此第二种情况可以忽略不看。

所以我们只需统计第一种情况 $0/1/0/1 \cdots$ 变换了多少次（在忽略第二种情况后，如果相邻两（多）**对** 颜色相同，应只算一次），作为第二问的答案。

要注意的是：如果所有的“对”都是第二种情况，就没有第一种情况的“对”让其依附，这时按照上述方法第二问答案为 $0$，这时就要特判第二问答案为 $1$。


## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int t,n,ans,a[maxn],la;
string s;
void init()
{
    cin>>n>>s;
}
void work()
{
    for(int i=0;i+1<n;i+=2)
    {
        if(s[i]!=s[i+1]) ans++;//第一问
    }
    for(int i=0;i+1<n;i+=2)
    {
        if(s[i]==s[i+1])//第二问 第一种情况
        {
            if(la==0 || a[la]!=s[i]-'0') //颜色一样只算一次
                a[++la]=s[i]-'0';
        }
    }
}
int main()
{
    cin>>t;
    while(t--)
    {
        la=ans=0;
        init();
        work();
        cout<<ans<<" "<<max(la,1)<<endl;//第二问特判
    }
    return 0;
}
```



---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1678B2)

这里给出两种做法，一种贪心，一种 $\verb!DP!$。
## 思路
贪心：我们两个两个考虑，如果 $s_i$ 与 $s_{i-1}$ 相等，我们显然不能去改它，再记录一个 $\verb!la!$ 变量表示上次是 $\verb!00!$ 串还是 $\verb!11!$ 串，如果不一样则增加块数。而如果 $s_i$ 与 $s_{i-1}$ 不相等，显然不管改成 $\verb!00!$ 还是 $\verb!11!$ 都没关系，所以我们不妨改成 $\verb!la!$ 代表的那种串。

$\verb!DP!$：我们设 $f_{i,0/1}$ 表示 $i$ 这一位是 $0/1$ 的最小段数，显然最小修改次数是固定的，所以我们只需记录段数。如果 $s_i$ 与 $s_{i-1}$ 相等，那么我们显然只能接上 $s_i$ 所代表的那种串，此时另一种只能赋值为 $\inf$。如果不相等，我们取上次 $f_{i,0/1}$ 的 $\min$。

写成状态转移方程就是：
   1. $s_i$ 与 $s_{i-1}$ 都为 $0$，$f_{i,0}=\min(f_{i-2,0},f_{i-2,1}+1),f_{i,1}=\inf$。
   2. $s_i$ 与 $s_{i-1}$ 都为 $1$，$f_{i,1}=\min(f_{i-2,1},f_{i-2,0}+1),f_{i,0}=\inf$。
   3. $s_i$ 与 $s_{i-1}$ 不相等，$f_{i,1}=\min(f_{i-2,1},f_{i-2,0}+1),f_{i,0}=\min(f_{i-2,0},f_{i-2,1}+1)$。
   
## 代码
下面给出贪心的代码：
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int T;cin>>T;
    while (T--){
        int n,la=-1,ans=0,sum=0;
        cin>>n;
        string s;cin>>s;s=" "+s;
        for (int i=1;i<=n;i+=2)
            if (s[i]==s[i+1]){
                if (la!=(s[i]-'0')) ++ans,la=(s[i]-'0');
            }else{
                s[i]=char(la+'0'),
                s[i+1]=s[i],++sum;
            }
        if (!ans) ans=1;
        cout<<sum<<' '<<ans<<'\n';
    }
    return 0;
}

```


---

## 作者：ttq012 (赞：3)

**Solution**

参考了CodeForces官方题解的做法。

贪心，枚举序列中所有的二元组，如果当前二元组的两个数的值不相同，那么操作数 $+1$，否则操作数不变。

如果当前二元组的两个数不同，那么块的数量不变。否则，如果当前二元组是第一个两个数相同的二元组或者当前二元组和上一个两个数相同的二元组是不相同的，那么块数自增 $1$。否则，块数不变。

由于答案可能类似于 `010110`，这种情况下 $y$ 的值不会更新，所以应该特判这种情况，此时 $y = 1$。

**AC Code(Python)**

```python
T = int(input())
for _ in range(0, T):
	n = int(input())
	s = input()
	x1 = -1
	x = 0
	y = 0
	f = 0
	for i in range(0, n // 2):
		j1 = i * 2
		j2 = i * 2 + 1
		if (s[j1] == s[j2] and x1 != int(s[j1])):
			y += 1
			x1 = int(s[j1])
		elif (s[j1] != s[j2]):
			x += 1
			f = 1
	if (y == 0):
		y = 1
	print (x, y, end = '\n')

```



---

## 作者：zcxnb (赞：1)

因为最后对于一个合法的串，要求连续段长度为偶数，所以，我们只关心一个偶数位二元组 $(1,2),(3,4) \dots$ 两个对应的数是否相等。

若不相等，我们只能把这个数对全改为 $0/1$，但是我们并不知道怎么改更优。

若相等，这个对就是不能改变的，因为把两个数都改变一定不优。

所以对于第一问的答案，我们观察有多少个不相等的对即可。

对于第二问的答案，我们会把中间不相等的段都改成其左或其右一段相等的段的数值，所以对于两个相邻的相等的二元组，若相同则对答案没有贡献，若相等则有 $1$ 的贡献。

特殊的，对于第一个相等的二元组也对答案有 $1$ 的贡献，若所有二元组都不相等则整个串必须变为一个相等的 $0/1$，所以答案为 $1$。

代码。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int t,n;
int a[N];
char s[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",s+1);
		for(int i=1;i<=n;i++){
			a[i]=s[i]-'0';
		}
		int lst=a[1],num=1,ans=0;
		for(int i=2;i<=n;i++){
			// printf("%d\n",lst);
			if(a[i]!=lst){
				if(num&1){
					num++;
					ans++;
				}
				else{
					num=1;
					lst=a[i];
				}
			}
			else{
				num++;
				lst=a[i];
			}
		}
		int l=0,ans2=0;
		for(int i=1;i<n;i+=2){
			if(a[i]==a[i+1]&&(!ans2||l!=a[i])){
				ans2++;
				l=a[i];
			}
		}
		if(ans2==0)  ans2++;
		printf("%d %d\n",ans,ans2);
	}
}
```

---

## 作者：qW__Wp (赞：0)

下文中的“字符串”表示 `01` 字符串；$s$ 表示给定的字符串，$t$ 表示可能的答案字符串。

---

为了方便叙述，我们作如下定义：

+ **单元**：如果一个字符串 $a$ 被分为若干个长度为 $2$ 的子串，称这些子串为 $a$ 的**单元**。
+ **完美单元**：对于一个单元 $b$，若 $b_1=b_2$，则称 $b$ 为一个**完美单元**
+ **非完美单元**：一个不是完美单元的单元称为一个**非完美单元**。
+ **完美字符串**：一个由若干个**完美单元**拼接而成的字符串称为**完美字符串**。

---

对于第一问：根据题意，$t$ 可以被分为若干个完美字符串，因此 $t$ 也是一个完美字符串。因此最优策略就是对 $s$ 的所有非完美单元中的任一字符进行一次操作使其变为完美单元，答案即为 $s$ 中的非完美单元的数量。

---

对于第二问，考虑 dp。设答案字符串为 $t$，$dp_{i,0/1}$ 表示当 $t_i=t_{i-1}=0/1$ 时，前 $i$ 位的最小划分段数，其中 $i$ 为偶数。分情况讨论：

+ 若 $s_i = s_{i-1}$，则 $t_i$、$t_{i-1}$ 只能取 $s_{i}$。
  + 若 $t_{i-2}$ 取 $s_i$，则 $dp_{i,s_i}=dp_{i-2,s_i}$。
  + 若 $t_{i-2}$ 取 $1-s_i$，则 $dp_{i,s_i}=dp_{i-2,1-s_i}+1$。
  + 综上，$dp_{i,s_i}=\min(dp_{i - 2,s_i},dp_{i-2,1-s_i}+1)$。
+ 否则，可以令 $t_i=t_{i-1}=0/1$。
  + 若 $t_i=t_{i-1}=0$，则 $dp_{i,0}=\min(dp_{i-2,0},dp_{i-2,1}+1)$。
  + 若 $t_i=t_{i-1}=1$，则 $dp_{i,1}=\min(dp_{i-2,1},dp_{i-2,0}+1)$。

答案即为 $\min(dp_{n,0},dp_{n,1})$。

初始边界：$dp_{0,0}=dp_{0,1}=1$；对于 $2 \le i \le n$ 的偶数 $i$，$dp_{i,0}=dp_{i,1}=\infty$。

时间复杂度 $O(\sum n)$。

Code:

```cpp
#include <bits/stdc++.h>
//#define int long long
#define INF 0x3fffffff
#define INFF 1e18

using namespace std;

const int N = 2e5 + 5;

int dp[N][2];

signed main() {
	int T; cin >> T;
	while (T --) {
		int n; cin >> n;
		for (int i = 1; i <= n; i ++) dp[i][0] = dp[i][1] = INF;
		string s; cin >> s;
		s = " " + s;
		int ans1 = 0;
		dp[0][0] = dp[0][1] = 1;
		for (int i = 2; i <= n; i += 2) {
			if (s[i] != s[i - 1]) {
				ans1 ++;
				if (i > 2) {
					dp[i][0] = min(dp[i - 2][0], dp[i - 2][1] + 1);
					dp[i][1] = min(dp[i - 2][1], dp[i - 2][0] + 1);
				} else dp[i][0] = dp[i][1] = 1;
			} else {
				int num = s[i] - '0';
				dp[i][num] = min(dp[i - 2][num], dp[i - 2][1 - num] + 1);
			}
		}
		cout << ans1 << ' ' << min(dp[n][0], dp[n][1]) << endl;
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

提供一种线段树做法。

设 $f_{i,0/1}$ 表示前 $i$ 个数，当前这一段的值为 $0/1$。

对于 $f_{i, j}$ 那么转移就是枚举 $k$，然后加上 $(k,i]$ 这一段中与 $j$ 不同的数的个数，记为 $w(j, k, i)$。

而我们发现将 $i$ 往后移动的过程中，所有 $j$ 相同的 $w(j, k, i)$，要么都增加 $1$，要么不变。

那么无脑维护线段树即可，就是维护区间 $\min$，以及区间 $+$，统计段数就在维护区间 $\min$ 时直接将段数作为第二关键字即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
int n;
char s[200010];
struct Node {
    int maxn, d;
    int add;
};

struct SGT {
    Node tr[800010];

    void pushup(int u) {
        tr[u].maxn = min(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
        if (tr[u << 1].maxn < tr[u << 1 | 1].maxn) tr[u].d = tr[u << 1].d;
        else if (tr[u << 1].maxn > tr[u << 1 | 1].maxn) tr[u].d = tr[u << 1 | 1].d;
        else tr[u].d = min(tr[u << 1].d, tr[u << 1 | 1].d);
    }

    void pushdown(int u) {
        tr[u << 1].maxn += tr[u].add;
        tr[u << 1 | 1].maxn += tr[u].add;

        tr[u << 1].add += tr[u].add;
        tr[u << 1 | 1].add += tr[u].add;
    }

    void modify(int u, int l, int r, int x, Node d) {
        if (l == r) {
            tr[u] = d;
            return;
        }

        pushdown(u);

        int mid = (l + r) >> 1;

        if (x <= mid) modify(u << 1, l, mid, x, d);
        else modify(u << 1 | 1, mid + 1, r, x, d);

        pushup(u);
    }

    void modify(int u, int l, int r, int ql, int qr, int d) {
        if (l >= ql && r <= qr) {
            tr[u].add += d;
            tr[u].maxn += d;

            return;
        }

        pushdown(u);
        int mid = (l + r) >> 1;

        if (ql <= mid) modify(u << 1, l, mid, ql, qr, d);
        if (qr > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, d);

        pushup(u);
    }

    Node query(int u, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) return tr[u];

        pushdown(u);
        int mid = (l + r) >> 1;
        Node res = {0, 0, 0};
        bool is_l = false;

        if (ql <= mid) res = query(u << 1, l, mid, ql, qr), is_l = true;
        if (qr > mid) {
            if (!is_l) res = query(u << 1 | 1, mid + 1, r, ql, qr);
            else {
                auto t = query(u << 1 | 1, mid + 1, r, ql, qr);
                if (t.maxn == res.maxn) res.d = min(res.d, t.d);
                if (t.maxn < res.maxn) res = t;
            }
        }

        return res;
    }
} Tr[2];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", s + 1);

        Node res = {0, 1000000000};
        for (int i = 1; i <= n; ++i) {
            if (s[i] == '0') Tr[1].modify(1, 0, (n + 1) / 2, 0, (i + 1) / 2 - 1, 1);
            else Tr[0].modify(1, 0, (n + 1) / 2, 0, (i + 1) / 2 - 1, 1);

            if (!(i & 1)) {
                auto a1 = Tr[1].query(1, 0, (n + 1) / 2, 0, i / 2 - 1), a2 = Tr[0].query(1, 0, (n + 1) / 2, 0, i / 2 - 1);
                a1.d++, a2.d++;
                a1.add = a2.add = 0;

                // cout << a1.maxn << ' ' << a1.d << ' ' << a2.maxn << ' ' << a2.d << endl;
                
                if (i == n) {
                    res.maxn = min(a1.maxn, a2.maxn);
                    if (a1.maxn == res.maxn) res.d = a1.d;
                    if (a2.maxn == res.maxn) res.d = min(res.d, a2.d);
                }

                Tr[1].modify(1, 0, (n + 1) / 2, i / 2, a2);
                Tr[0].modify(1, 0, (n + 1) / 2, i / 2, a1);
            }
        }

        printf("%d %d\n", res.maxn, res.d);

        for (int i = 0; i <= n * 3 + 10; ++i) Tr[0].tr[i] = Tr[1].tr[i] = {0, 0, 0};
    }
    return 0;
}
```

---

## 作者：tallnut (赞：0)

# 思路
题目有两问。

- 第一问：求最小操作次数。

  容易发现只有当 $i(1\le i<n)$ 为偶，而且 $s_i\ne s_{i+1}$ 时，答案才需要更新。
  
  因为他要求所有子串长度均为偶，只要 $2$ 个 $2$ 个操作即可。
  
- 第二问：求最少子串个数。

  如果一个长度为 $2$ 的子串中既有 $0$ 又有 $1$，那么通过一次操作，既可以把两个字符都变为 $1$，又可以把两个字符都变为 $0$。可以根据实际需要选择变成 $0$ 还是 $1$（与和它相邻的长度为 $2$ 子串相同即可）。
  
  也就是说，对答案有影响的只是 $a_i=a_{i+1}$ 的子串。
  
  我们使用一个 `vector`，把两个字符相同的子串加入到 `vector`，然后去重。（我的代码没有直接用 `unique`，但效果和 `unique` 是一样的）
# 代码
[AC 记录](https://www.luogu.com.cn/record/143155504)。
```
#include <iostream>
#include <vector>
using namespace std;
int t,n,ans1,ans2;
string s;
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> s;
		ans1 = 0;
		vector<int> v;
		for (int i = 0;i < s.size();i += 2)
			if (s[i] != s[i + 1]) ans1++;
			else v.push_back(s[i] - '0');
		cout << ans1 << ' ';
		//最开始的一个元素
		ans2 = 1;
		for (int i = 1;i < v.size();i++)
			if (v[i] != v[i - 1]) ans2++;
		cout << ans2 << '\n';
	}
}
```

---

## 作者：Masna_Kimoyo (赞：0)

由于字符串的长度是偶数，且最后形成的字符串一定是由一个个偶数长度的串构成的，我们可以把整个原始字符串分为一个个长度为 $2$ 的子串。

分类讨论一下：

- 如果两个字符本身就一样，还把他们都换成不一样的，肯定就不是最优解了。

若连续一段子串都是一样的颜色，那么就会对第二个答案的贡献加一。因为是两两一统计，所以会出现很多重复的情况，用一个 `unique` 将数组去重即可。最后剩下的数组长度就是第二个答案。

- 如果不一样，考虑两种情况：

一个前提条件：旁边的串都已处理完毕。（即为两个相等的字符）

1. 如果两边的子串都是一样的，那为了保证最后不同串数量最少，肯定换成和它们俩相同的颜色。此时不同颜色的串不会增加。

2. 如果两边子串不一样，那就只能二选一。但无论选哪个，最后也就是融入和选的那个子串相同颜色的那一段子串里，对第二个答案无法造成贡献。

综上，无论什么情况，都无法对第二个答案造成影响，所以不需要加入第二个答案的统计过程。

**最后，因为它们本身不同，所以至少修改一个，对第一个答案的贡献加一。**

所以代码如下：

```cpp
#include<bits/stdc++.h>
#define printlf(x) print(x),putchar('\n')
#define printsp(x) print(x),putchar(' ')
using namespace std;
inline int read(){
    int x=0;
    bool w=0;
    char c=getchar();
    while(!isdigit(c))  w|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void print(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar('0'+x%10);
}
inline pair<int,int> Solve(){
    string s;vector<int> v;
    int ans1=0,ans2=0,n=read();
    cin>>s;
    for(register int i=1;i<n;i+=2)
        if(s[i-1]!=s[i])    ++ans1;
        else    v.push_back(s[i]);
    ans2=unique(v.begin(),v.end())-v.begin();
    return {ans1,max(ans2,1)};
}
signed main(){
    int T=read();
    while(T--){
        pair<int,int> ans=Solve();
        printsp(ans.first),printlf(ans.second);
    }
    return 0;
}

```

---

