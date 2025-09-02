# Palindrome Shuffle

## 题目描述

给定一个由小写拉丁字母组成的字符串 $s$。

你可以对字符串 $s$ 执行以下操作：选择一个连续的（可能为空的）子串，并对其进行洗牌（即重新排列子串中的字符顺序）。

注意：回文是指正向和反向读取相同的字符串。例如，字符串 a、bab、acca、bcabcbacb 是回文，而 ab、abbbaa、cccb 则不是。

你的任务是确定为了将给定字符串 $s$ 转换为回文，必须进行操作的最小子串长度。

## 说明/提示

第一个示例中，可以按如下方式操作：baba → baab。

第二个示例中，字符串已经是回文，因此可以选择空子串进行操作。

第三个示例中，可以按如下方式操作：ddaa → adda。

第四个示例中，可以按如下方式操作：acbacddacbca → acbcaddacbca。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
baba
cc
ddaa
acbacddacbca```

### 输出

```
2
0
3
2```

# 题解

## 作者：Engulf (赞：4)

参考官解。

不要理解错题意，**操作最多一次**。

首先，对于 $s$ 前后两端一开始就相同的字母，完全可以把它们都去掉，如 $s = \tt{abcdeaba}$，去掉首尾的两个变为 $s' = \tt{cdea}$。

令 $s$ 变为进行上述操作后的 $s'$，设 $n = |s|$，即字符串 $s$ 的长度。

现在 $s_1 \neq s_n$，注意到我们操作的区间一定是一段 **前缀** 或 **后缀**。发现翻转 $s$ 没有任何影响，所以现在仅考虑前缀（若选取后缀，翻转 $s$ 就变成了前缀）。

> 由于 $s_1 \neq s_n$，$s_1$ 必须在操作的区间内，这就固定了区间左端点为 $1$。又因为操作最多一次，所以操作的区间就是 $s$ 的前缀。

注意到若前缀 $[1, p]$ 是合法的，$[1, p + 1]$ 也一定是合法的，因为是任意重排，完全可以不动 $s_{p+1}$，所以答案有单调性，考虑二分 $p$。

考虑如何判断 $[1, p]$ 经过重排能够使 $s$ 变为回文串。对于每个 $i\in[1, p]$：
- 若 $s_i = s_{n - i + 1}$，管它干嘛；
- 若 $s_i \neq s_{n - i + 1}$，如果 $n - i + 1 > p$，说明 $s_{n - i + 1}$ 不能被重排，所以 $i$ 这个位置得放一个 $s_{n - i + 1}$。

对每个字符 $c$ 开一个桶，记录 $[1, p]$ 内需要移动去匹配的 $c$ 的总数 $v_c$，$[1, p]$ 放的每一个 $c$ 都是在匹配另一侧的 $c$，所以一共需要有 $2v_c$ 个字符 $c$。

只需统计每个字符在 $s$ 中的出现次数 $t_c$，若 $\forall c, t_c \ge 2v_c$，说明这个操作区间 $[1, p]$ 是合法的，反之就是非法的。

$\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        string s;
        cin >> s;

        while (s.size() && *s.begin() == *--s.end()) {
            s.pop_back(), s.erase(s.begin());
        }

        int n = s.size();

        int ans = n;
        for (int tm = 0; tm < 2; tm++) {
            // debug("current s: %s\n", s.c_str());
            int l = 0, r = n - 1, res = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if ([=]() {
                    for (int i = mid + 1; i < n; i++)
                        if (n - 1 - i > mid && s[i] != s[n - 1 - i])
                            return false;

                    vector<int> cnt(26);
                    for (int i = 0; i < 26; i++)
                        cnt[i] = count(s.begin(), s.end(), 'a' + i) / 2;

                    vector<int> vec(26);
                    for (int i = 0; i <= mid; i++) {
                        if (n - 1 - i > mid) {
                            vec[s[n - 1 - i] - 'a']++;
                        }
                    }

                    // debug("checking mid of %d\n", mid);
                    for (int i = 0; i < 26; i++) {
                        // debug("vec[%c] = %d, cnt[%c] = %d\n", 'a' + i, vec[i], 'a' + i, cnt[i]);
                        if (vec[i] > cnt[i])
                            return false;
                    }

                    return true;
                }()) res = mid, r = mid - 1;
                else l = mid + 1;
            }
            ans = min(ans, res + 1);
            reverse(s.begin(), s.end());
        }

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：chenxi2009 (赞：3)

## 思路
首尾对应相同的部分已经回文，绝对不需要重排，可以提前剔除，剩下的部分令其为 $S$，$n\leftarrow\vert S\vert$。

由于相同部分已剔除，$S_1\ne S_n$，这两者至少要有一个被重排，因此剩下最长的可以**不**重排的部分只会是 $S_{1\cdots x}$ 或者 $S_{x\cdots n}$。两者可以类比所以只讨论前者。

令 $S$ 中字符 $c$ 的出现次数为 $a_c$，被选中不重排的 $c$ 个数不能超过 $\frac{a_c}{2}$。\
上面这句是**假命题**。第四组样例可以说明这一点，被选中的部分可以事先就是回文的。

综合上述两点就可以得出正确的结论了：\
$S_{1\cdots x}$ 可以被选中不重排当且仅当：\
若 $x\le\frac{n}{2}$，任意字符 $c$ 被选中的个数 $\le\frac{a_c}{2}$；\
若 $x>\frac{n}{2}$，在 $S_{1\cdots\frac{n}{2}}$ 中任意字符 $c$ 的个数 $\le\frac{a_c}{2}$，$S_{\frac{n}{2}+1\cdots x}$ 和 $S$ 中左半边对应的部分已经回文。

这是容易解释的，限制字符 $c$ 的个数是因为我们需要足够多的 $c$ 被重排以和选中这部分的 $c$ 一一对应构成回文；后一半的部分要构成回文是显然的，毕竟你都要选中不改变它了。

所以你可以从 $x=1$ 开始一直尝试增加 $x$，过程中顺便统计每一个字符的选中个数，一旦增加 $x$ 变得非法就停止。

选中字符串是 $S$ 的后缀同理，时间复杂度 $O(\sum\vert s\vert)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,cnt[200],l,r,ans,tot[200],x;
char s[300000];
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%s",s + 1);
		n = strlen(s + 1);
		l = 1,r = n;
		for(int i = 'a';i <= 'z';i ++) tot[i] = cnt[i] = 0;//cnt_c 为 c 总共出现的次数，tot_c 记录 c 被选中的个数 
		while(l < r && s[l] == s[r]) l ++,r --;//两端回文部分提前排除 
		for(int i = l;i <= r;i ++) cnt[s[i]] ++;//统计字符总个数 
		x = l;//取 S 的前缀的情况 
		for(int i = l;i <= r;i ++){
			tot[s[i]] ++;
			if(i > n / 2){if(s[i] != s[n - i + 1]) break;}//选中字符过半时，要检验与前一半是否回文 
			else{if(tot[s[i]] * 2 > cnt[s[i]]) break;}//未过半时需要检查选中的字符个数是否超过一半 
			x = i + 1;
		}
		ans = r - x + 1,x = r;//取 S 的后缀同理 
		for(int i = 'a';i <= 'z';i ++) tot[i] = 0;
		for(int i = r;i >= l;i --){
			tot[s[i]] ++;
			if(i <= n / 2){if(s[i] != s[n - i + 1]) break;}
			else{if(tot[s[i]] * 2 > cnt[s[i]]) break;}
			x = i - 1;
		}
		ans = min(ans,x - l + 1);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：3)

[更不好的阅读体验](https://wmrqwq.github.io/2025/02/19/CF2069Dsol/)

# 题目链接

[CF2069D(*1900) Palindrome Shuffle(luogu)](https://www.luogu.com.cn/problem/CF2069D)

[CF2069D(*1900) Palindrome Shuffle(codeforces)](https://codeforces.com/contest/2069/problem/D)

# 解题思路

本文 $V$ 代表 $26$，即字符集大小。

这题是史，大家一起吃。

首先根据题中定义这题显然长度为 $i(i < n)$ 合法，则长度为 $i + 1$ 合法，因为你可以任意交换，不影响。

因此此题可以二分答案。

那么容易得出 check 一个长度 $len$ 是否合法只需要判断是否有**至少**一个长度为 $len$ 的区间合法即可，那么我们考虑如何进行 check 一个任意交换区间 $[l,r]$ 是否合法，首先通过提前预处理判断掉不能任意交换且字母本应该相同的位置是否合法，处理完这个之后此时我们可以考虑分讨以下几种情况：

- $r \le \displaystyle \frac{n}{2}$，此时整个可交换的区间都在左边，只需要前缀和即可 $O(V)$ 判断一个区间是否合法。

- $l > \displaystyle \frac{n}{2}$，此时整个可交换的区间都在右边，只需要前缀和即可 $O(V)$ 判断一个区间是否合法。

- $l \le \displaystyle \frac{n}{2} < r$，则此时可交换区间包含左右两边，此时我们继续分讨：

  - $\displaystyle\frac{n}{2} - l < r - \displaystyle\frac{n}{2}$，此时我们只需要判断左边是否能暴力匹配右边的字母即可。
    
  - $\displaystyle\frac{n}{2} - l \ge r - \displaystyle\frac{n}{2}$，此时我们只需要判断右边是否能暴力匹配左边的字母即可。

那么 check 就做完了，那么整题也就做完了，最后是一个二分板子，不赘述。

时间复杂度 $O(nV \log n)$，可以通过本题。

# 参考代码

```cpp
string s;
ll n;
ll pre[200010];
ll sum[200010][30];
ll now[30];
bool PRE(ll len){
    return pre[len]==len;
}
bool ck(ll l,ll r)
{
    if(l==1 && r==n)
        return 1;
    ll l1,l2,r1,r2;
    l1=1,r1=l-1;
    l2=r+1,r2=n;
    ll len=min(r1,n-l2+1);
    if(!PRE(len))
        return 0;
    if(l+r==n+1)
        return 1;
    forl(i,0,25)
        now[i]=sum[r][i]-sum[l-1][i];
    if(l<=n/2 && r<=n/2)
    {
        if(r!=n/2 && pre[n/2]-pre[r]!=n/2-r)
            return 0;
        forl(i,0,25)
            if(now[i]!=sum[n+1-l][i]-sum[n+1-r-1][i])
                return 0;
        return 1;
    }
    else if(l>n/2 && r>n/2)
    {
        if(l!=n/2+1 && pre[n/2]-pre[n+1-l]!=n/2-(n+1-l))
            return 0;
        forl(i,0,25)
            if(now[i]!=sum[n+1-l][i]-sum[n+1-r-1][i])
                return 0;
        return 1;
    }
    else
    {
        if(n/2-l<r-n/2)
        {
       //   bug2;
            forl(i,0,25)
            {
                now[i]-=sum[n+1-(n+1-l)-1][i]-sum[n+1-r-1][i];
                if(now[i]<0)
                    return 0;
            }
            /*
            r,r-1,n-l
            */
            ///////
            // while(l+r>n+1)
            // {
            //     //r--;
            //  //   cout<<s[n+1-r]<<endl;
            //     if(!now[s[n+1-r]-'a']--)
            //         return 0;
            //     r--;
            // }
        //    bug3;
            forl(i,0,25)
                if(now[i]&1)
                    return 0;
            return 1;
        }
        else
        {
            forl(i,0,25)
            {
                now[i]-=sum[n+1-l][i]-sum[n+1-(n+1-r)][i];
                if(now[i]<0)
                    return 0;
            }
       //  bug1;
            // while(l+r<n+1)
            // {
            //     //l++;
            //     if(!now[s[n+1-l]-'a']--)
            //         return 0;
            //     l++;
            // }
         // bug4;
            forl(i,0,25)
                if(now[i]&1)
                    return 0;
            return 1;
        }
    }
}
bool check(ll Mid)
{
    forl(i,1,n-Mid+1)
        if(ck(i,i+Mid-1))   
            return 1;
    return 0;
}
ll L,R;
/*
ababa babababab
ababa babb ababa
*/
void _clear(){}
void solve()
{
    _clear();
    cin>>s;
    n=s.size();
    s=' '+s;
    forl(i,1,n)
    {
        forl(j,0,25)
            sum[i][j]=sum[i-1][j];
        sum[i][s[i]-'a']++;
    }
    forl(i,1,n)
        pre[i]=0;
    forl(i,1,n/2)
        pre[i]=(s[i]==s[n-i+1]);
    forl(i,1,n/2)
        pre[i]+=pre[i-1];
    if(pre[n/2]==n/2)
    {
        cout<<0<<endl;
        return ;
    }
   // cout<<ck(5,10)<<endl;
   // return ;
    L=1,R=n;
    while(L<R)
    {
        ll Mid=(L+R)/2;
        if(check(Mid))
            R=Mid;
        else
            L=Mid+1;
    }
    cout<<L<<endl;
}
```

---

## 作者：zyb_txdy (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF2069D)

### 题意

给定一个长度为 $n$ 的字符串 $s$。定义一次操作为，选择一个区间 $[l, r]$ 并花费区间长度的代价，将 $s_l, ..., s_r$ 重排。

现在你可以进行一次操作，求花费的最小代价，使得操作完成后 $s$ 是一个回文串。

数据范围：$n \le 2 \times 10^5$，保证 $n$ 为偶数且 $s$ 必定可以变成回文串。

## 分析

> 怎么有人读错题了然后虚空调试一整场啊，怎么会是呢？/ll

定义字符串 $s$ 的外侧为远离 $s$ 的中心的部分，内侧反之。

首先从外向内考虑，若当前的 $s_i$ 能和 $s_{n - i + 1}$ 匹配上，那么我们显然不用考虑 $s_i$ 和 $s_{n - i + 1}$，将其舍弃掉即可。

那么现在，我们就得到了新的字符串 $s$ 和它的长度 $n$，且它满足 $s_1 \ne s_n$。由于我们只能进行一次操作，故操作的区间必定至少包含 $s_1$ 和 $s_n$ 中的一个。接下来，我们将讨论包含 $s_1$ 的情况。包含 $s_n$ 的情况只需要将 $s$ 翻转并再做一遍即可。

首先注意到，若区间必须包含 $s_1$，则其长度显然满足单调性，故考虑二分答案，而 $\text{check}$ 操作是简单的，于是就做完了。

同时，这题也有复杂度为 $O(n)$ 的做法：考虑将字符串分为左右两部分，每部分的长度都为 $\frac{n}{2}$。显然只有当存在一个字符 $c$，满足 $c$ 在两边的出现次数不同时，选择的区间才会跨过这两部分。于是，找到无法匹配 / 出现次数不同的边界即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mid (l + r >> 1)
#define lowbit(x) (x & -x)

const int N = 2e5 + 5, M = 26;

int T, n;
int cnt[M], tot[M];
char s[N];

int get() {
	memset(tot, 0, sizeof(tot));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; ++i) ++tot[s[i] - 'a'];
	for (int i = n; i > n / 2; --i) {
		++cnt[s[i] - 'a'];
		if (cnt[s[i] - 'a'] > tot[s[i] - 'a'] / 2) return i;
	}
	for (int i = n / 2; i > 0; --i) if (s[i] != s[n - i + 1]) return i;
}

void Solve() {
	cin >> s + 1; n = strlen(s + 1);
	int L = 1, t = 2, ans = 1e9;
	while (L <= n / 2 && s[L] == s[n - L + 1]) ++L;
	for (int i = L; i <= n - L + 1; ++i) s[i - L + 1] = s[i];
	n = n - 2 * L + 2;
	if (n <= 0) { cout << "0" << endl; return; }
	while (t--) {
		ans = min(ans, get());
		reverse(s + 1, s + n + 1);
	}
	cout << ans << endl;
}

signed main() {
	cin >> T;
	while (T--) Solve();
	return 0;
}
```

---

## 作者：Otue (赞：1)

## [CF2069D Palindrome Shuffle](https://www.luogu.com.cn/problem/CF2069D)

### 题目大意

您将得到字符串 $s$。您可以对字符串 $s$ 执行以下操作：选择一个连续的子字符串。并根据需要对子字符串中的字符重新排序。将字符串 $s$ 转换为回文。求出进行操作的子字符串的最小可能长度。

### 题目思路

首先删除两端的无用的回文串。即找到 $i$ 满足对于每一个 $1\leq j\leq i$ 使得 $s_j=s_{n-j+1}$ 的最大 $i$，并且将 $[1,i]$ 和 $[n-i+1,n]$ 都删除。

分两种情况讨论：

* 操作的子串没有越过了字符串中点。也就是在 $[1,mid]$ 和 $[mid+1,n]$ 内进行操作。**这需要满足前提条件两端的字符串集合相等**。然后再把中间的回文串删掉，也就是满足 $s_{mid-j+1}=s_{mid+j}$ 的最大 $j$。删完后剩下的就是必须要操作的最短长度了。
* 操作的子串跨越了字符串中点。我们从 $1$ 开始遍历，如果当前遍历到字符 $c$，则必须要有一个对应的 $c$ 在右侧使得其匹配。也就是如果当前遍历存在字符 $c$ 使得出现次数超过总次数的一半，就找不到匹配的字符了。当然，还要从 $n$ 再倒着遍历一遍，比如字符串 `ffabcabc`。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)

const int N = 2e5 + 5;
int T, n, vv[28], vv2[28], vv3[28], vv4[28];
char a[N];

signed main() {
	cin >> T;
	while (T--) {
		cin >> (a + 1); n = strlen(a + 1);
		int len = 0;
		while (len + 1 <= n / 2 && a[len + 1] == a[n - (len + 1) + 1]) len++;
		memset(vv, 0, sizeof vv);
		memset(vv2, 0, sizeof vv2);
		memset(vv3, 0, sizeof vv3);
		memset(vv4, 0, sizeof vv4);
		_for(i, len + 1, n / 2) vv[a[i] - 'a']++;
		_for(i, n / 2 + 1, n - len) vv2[a[i] - 'a']++;
		int flg = 0;
		_for(i, 0, 26) {
			if (vv[i] != vv2[i]) flg = 1;
		}
		int res = 2e9;
		if (!flg) {
			int len2 = 0;
			while (len2 + 1 <= n / 2 - (len + 1) + 1 && a[n / 2 - (len2 + 1) + 1] == a[n / 2 + 1 + (len2 + 1) - 1]) len2++;
			res = min(res, n / 2 - len - len2);
		}
		_for(i, len + 1, n - len) vv3[a[i] - 'a']++;
		int maxn = 0;
		_for(i, len + 1, n / 2) {
			vv4[a[i] - 'a']++;
			if (vv4[a[i] - 'a'] > vv3[a[i] - 'a'] / 2) break;
			maxn = max(maxn, i - (len + 1) + 1);
		}
		res = min(res, n - 2 * len - maxn);
		memset(vv4, 0, sizeof vv4);
		maxn = 0;
		_pfor(i, n - len, n / 2 + 1) {
			vv4[a[i] - 'a']++;
			if (vv4[a[i] - 'a'] > vv3[a[i] - 'a'] / 2) break;
			maxn = max(maxn, n - len - i + 1);
		}
		res = min(res, n - 2 * len - maxn);
		cout << res << endl;
	}
}
```

---

## 作者：zhouyuxuan3501 (赞：0)

**注意：题意是说只能进行一次操作！**

对于 $S=c_1c_2c_3\cdots c_kAc_k\cdots c_3c_2c_1$，即 $S$ 的一个前缀已经和后缀回文，那操作的子串与前缀或后缀交叉一定更劣，于是我们可以先去掉前缀和后缀，只对中间没有回文的 $A$ 进行操作。

现在的操作等价于选取 $A$ 的一个前缀或后缀进行重排。发现枚举改变的部分不太好做——因为根本不知道剩下不动的部分满不满足回文要求。故考虑枚举不动的部分。

那不动的部分是否合法呢？考虑回文串的性质：

- 每个字母 $c$ 在对称中心左右两边的数量相等，都是 $\displaystyle \frac{1}{2}cnt(c)$。
- 回文对称(很基本的废话)。

于是不动的部分 $B$ 中每个字母 $c$ 出现次数不超过 $\displaystyle \frac{1}{2}cnt(c)$，同时若 $2|B|>|A|$，即 $B$ 经过回文中心，还要检查 $B$ 是否满足对称。预处理 $cnt$，$O(n)$ 正着扫一遍，再反着扫一遍就好了。

---

## 作者：yvbf (赞：0)

![](bilibili:BV1DkAzetEX9?t=1166)

---

## 作者：lrx___ (赞：0)

## 线性做法

特判掉原串是回文串，答案是 $0$。

先删掉首尾相等的字符，因为一定不会操作到这里。此时假设字符串的长度为 $L$。

现在这个字符串首尾不相等，则选择的区间一定包含首或包含尾（不然首尾仍然不相等，不能回文），因此选择的区间**一定是当前字符串的前缀或后缀**。

然后我们先找到中间最长的回文串。比如字符串是 `abcababac`，我们会找到 `abc[aba]bac`。此时如果两侧每个字符的出现次数都相等，那么我们只需重排其中一侧即可。上面我们只需重排左侧的 `abc` 或右边的 `bac` 即可。

如果出现次数不相等，比如 `aa[bb]cc`，我们直接枚举前缀和后缀的长度即可。这个长度一定超过 $\lfloor \frac{L}{2} \rfloor$，比如上面，我们只选 `aab` 是不可行的。

我们现在枚举了一个后缀 $S$，剩下的前缀为 $P$，如何判断它是不是合法的？

比较简便的方法就是：如果每个字符在 $P$ 中的出现次数不超过在 $S$ 中的出现次数，则合法，否则不合法。

简单证明一下。因为题目保证有解，所以**至多有一个字符出现了奇数次**。

如果没有字符出现了奇数次，则我们在 $S$ 中选出一个与 $P$ 相同的子集 $P^\prime$，翻转过来并放到后缀。此时每个字符在 $P$ 和 $P^\prime$ 个出现一次，都出现了偶数次，因此也剩下了偶数次，在中间对半分即可。

如果有一个字符出现了奇数次，设出现了 $x$ 次，则左边选了小于等于 $\lfloor \frac{x}{2} \rfloor$ 就合法，大于等于 $\lceil \frac{x}{2} \rceil$ 个就不合法。这满足“在 $P$ 中的出现次数不超过在 $S$ 中的出现次数则合法，否则不合法”。对于出现偶数次的，和前面“没有字符出现了奇数次”的情况相同。

所以这个判断方法是正确的。我们用两个桶记录，枚举时维护前缀和后缀每个字符的出现个数，到最后一个合法的位置即可。

## 代码

~~C++ 20 大法好。~~

```cpp
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#ifndef ONLINE_JUDGE
#include <format>
#define debug(...) std::cerr << std::format(__VA_ARGS__)
#else
#define debug(...)
#endif
template<typename T>
void ckmax(T& a, T b) {
	if (a < b) a = b;
}
template<typename T>
void ckmin(T& a, T b) {
	if (b < a) a = b;
}

#include <algorithm>
#include <string>
#include <ranges>
#include <vector>
void solve() {
	std::string s;
	std::cin >> s;
	std::ranges::for_each(s, [&](char& c) {c -= 'a';});
	int n = static_cast<int>(s.size());
	if (std::ranges::equal(s, s | std::views::reverse)) { // 特判回文串
		std::cout << "0\n";
		return;
	}

	// 将首尾相同的部分删掉
	int len = *std::ranges::find_if_not(std::views::iota(0, n), [&](int i) {return s[i] == s[n - i - 1];}); // 找到第一个不满足的下标
	s.erase(s.begin(), s.begin() + len);
	s.erase(s.end() - len, s.end());
	n -= len << 1;
	
	// 找出中间回文的长度
	int midl = (n - 1) >> 1, midr = n >> 1;
	len = *std::ranges::find_if_not(std::views::iota(0, n), [&](int i) {return s[midl - i] == s[midr + i];}); // 找到第一个不满足中间回文的长度
	midl -= len;
	midr += len;
	// [midl + 1, midr - 1] 这一段是回文的

	// 判断 [0, midl] 和 [midr, n) 每个字符的出现次数是否相同
	std::string lef = s.substr(0, midl + 1), rig = s.substr(midr);
	std::vector<int> b1(26, 0), b2(26, 0);
	std::ranges::for_each(lef, [&](char c) {++b1[c];});
	std::ranges::for_each(rig, [&](char c) {++b2[c];});
	if (b1 == b2) { // 相同，则只需重排一侧即可
		std::cout << lef.size() << "\n";
		return;
	}

	// 此时一定选一个前缀或一个后缀，并且要跨过中间的回文区
	std::vector<int> buc(26, 0), chosen(26, 0);
	std::ranges::for_each(s, [&](char c) {++buc[c];});
	int ans = n;
	// 选后缀，保留左边，枚举保留几位，找到第一个不满足的
	int i = *std::ranges::find_if(std::views::iota(0, (n + 1) / 2), [&](int i) {
		--buc[s[i]];
		++chosen[s[i]];
		return buc[s[i]] < chosen[s[i]]; // 代表不满足
	}) - 1;
	ckmin(ans, n - i - 1);
	std::ranges::fill(buc, 0);
	std::ranges::fill(chosen, 0);
	std::ranges::for_each(s, [&](char c) {++buc[c];});
	// 保留右边
	i = *std::ranges::find_if(std::views::iota(0, (n + 1) / 2), [&](int i) {
		--buc[s[n - i - 1]];
		++chosen[s[n - i - 1]];
		return buc[s[n - i - 1]] < chosen[s[n - i - 1]];
	}) - 1;
	ckmin(ans, n - i - 1);
	std::cout << ans << "\n";
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

---

