# Misha and Palindrome Degree

## 题目描述

Misha has an array of $ n $ integers indexed by integers from $ 1 $ to $ n $ . Let's define palindrome degree of array $ a $ as the number of such index pairs $ (l,r)(1<=l<=r<=n) $ , that the elements from the $ l $ -th to the $ r $ -th one inclusive can be rearranged in such a way that the whole array will be a palindrome. In other words, pair $ (l,r) $ should meet the condition that after some rearranging of numbers on positions from $ l $ to $ r $ , inclusive (it is allowed not to rearrange the numbers at all), for any $ 1<=i<=n $ following condition holds: $ a[i]=a[n-i+1] $ .

Your task is to find the palindrome degree of Misha's array.

## 说明/提示

In the first sample test any possible pair $ (l,r) $ meets the condition.

In the third sample test following pairs $ (1,3),(1,4),(1,5),(2,5) $ meet the condition.

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6
3 6 5 3 3 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
5 5 2 5 2
```

### 输出

```
4
```

# 题解

## 作者：sunkuangzheng (赞：5)

挺好的题啊，为什么做的人这么少 /kel

首先有两个很显然的性质：

- 性质 $1$：若重排 $[l_1,r_1]$ 可以使原序列回文，则对于任意 $l_2 \in [1,l_1],r_2 \in [r_1,n]$，重排 $[l_2,r_2]$ 都可以使原序列回文。

- 性质 $2$：设去除掉首尾极长回文段后的区间是 $[l,r](r = n-l+1)$（形式化的，$\forall i \in [1,l),a_i = a_{n-i+1}$ 且 $a_l \ne a_r$），则任意合法区间都至少包含 $l,r$ 中的一个。

性质 $2$ 决定了我们选择的区间一定包含 $[l,r]$ 的**前缀或后缀**，而性质 $1$ 决定了确定这个前后缀的长度可以**二分**。假设我们可以 $\mathcal O(n)$ 判定一个区间是否合法，考虑怎么计算答案。

首先去除掉首尾的极长回文段，得到区间 $[l,r]$。我们二分两次，第一次二分出一个 $p$ 表示 $[l,p]$ 是最短的以 $l$ 为左端点的合法区间，第二次二分出一个 $q$ 表示 $[q,r]$ 是最短的以 $r$ 为右端点的合法区间。显然，一个合法区间 $[x,y]$ 需要满足以下条件中的**至少**一个：

- $x \le l,y \ge p$。满足该条条件的区间数量是 $l(n-p+1)$。

- $x \le q,y \ge r$。满足该条条件的区间数量是 $q(n-r+1)$。

当然，我们需要减去算重复的，即同时满足两个条件的区间，也即 $x \le l,y \ge r$ 的区间，共 $l(n-r+1)$ 个。那么，最终的答案就是 $l(n-p+1)+q(n-r+1)-l(n-r+1)$。

要注意一下，有无论如何重排都不合法和无论如何重排都合法的情况，记得特判掉，防止出现意外错误。

---

接下来需要考虑这样一个问题：给定区间 $[l,r]$，问重排 $[l,r]$ 内元素可否使原序列回文。

考虑回文的限制很严格，很多位置的值其实是可以根据已经填好的位置直接确定的。关于序列对称的两个位置都不确定的，一定是中间的一段区间。此时，分 $n$ 的奇偶性讨论：

- $n$ 是偶数。所有未填的元素均要出现偶数次。

- $n$ 是奇数。需要有**恰好一个**元素出现奇数次，其余元素出现偶数次。

体现在程序上，首先计算出 $[l,r]$ 里元素的出现次数，然后我们按照 $1 \sim \lceil\dfrac{n}{2}\rceil$ 的顺序枚举 $i$，分情况讨论：

- 如果 $a_i$ 和 $a_{n-i+1}$ 都已经确定，直接判断是否相等。如果不等，说明区间不合法。

- 如果 $a_i$ 和 $a_{n-i+1}$ 恰好有一个不确定，显然不确定的位置只可以填另一个位置的值，让这个值出现次数 $-1$。

- 如果 $a_i$ 和 $a_{n-i+1}$ 都不确定，证明已经到了中间段。直接根据上面的判断条件判断即可。

这部分的时间复杂度 $\mathcal O(n)$，因此总的时间复杂度是 $\mathcal O(n \log n)$。




```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+5;
int t,n,a[N],l = 1,r,ct[N],b[N],cnt,len,ql,qr,rl,rr;
bool ck(int l,int r){
    memset(ct,0,sizeof(ct));
    for(int i = 1;i <= n;i ++) if(l <= i && i <= r) ct[a[i]] ++,b[i] = 0; else b[i] = 1;
    for(int i = rl;i <= min(rr,(n+1)/2);i ++){
        if(!b[i] && !b[n-i+1]){
            int sb = 0,fg = 0;
            for(int j = 1;j <= n;j ++) sb += ct[j] / 2,fg |= (ct[j] & 1);
            return ((sb == (n - 2 * i + 2) / 2) && (n % 2 == 0 || fg));
        }else if(!b[i]) if(ct[a[n-i+1]]) ct[a[n-i+1]] --,b[i] = 1; else return 0;
        else if(!b[n-i+1]) if(ct[a[i]]) ct[a[i]] --,b[n-i+1] = 1; else return 0;
        else if(a[i] != a[n-i+1]) return 0;
    }return 1;
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n,r = n;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    while(a[l] == a[r]) l ++,r --;
    for(int i = 1;i <= n;i ++) ct[a[i]] ++;
    for(int i = 1;i <= n;i ++) cnt += (ct[i] & 1);
    if(cnt > (n & 1)) return cout << 0,0;
    if(l > r) return cout << (n + 1) * n / 2,0;
    rl = l,rr = r;
    int tl = l,tr = r;
    while(tl <= tr){
        int mid = (tl + tr) / 2;
        if(ck(l,mid)) tr = mid - 1; else tl = mid + 1;
    }ql = tr + 1,tl = l,tr = r;
    while(tl <= tr){
        int mid = (tl + tr) / 2;
        if(ck(mid,r)) tl = mid + 1; else tr = mid - 1;
    }qr = tl - 1;
    cout << l * (n - ql + 1) + (n - r + 1) * qr - l * (n - r + 1); 
}
```

---

## 作者：Ryo_Yamada (赞：5)

> Misha 有一个数组，下标从 $1$ 到 $n$。

> 定义一个数组 $a$ 的回文度数为数对 $[l,r]$ 的个数（$1 \le l \le r \le n$），当且仅当重排 $[l,r]$ 中的数可以使 $a$ 变成一个回文序列。

> 换句话说，重排 $[l,r]$ 中的数可以使每个 $i \in [1,n],\,a_i=a_{n-i+1}$。

> 给出数组 $a$，请你求出 $a$ 的回文度数。

好玩+细节题。

首先，我们可以先尽量去掉长的首尾回文部分，剩下的记为数组 $b$，长度为 $m$。

即若 $a=\{1,4,6,3,4,1\}$，则 $b=\{6,3\}$。

此时在 $b$ **中间**取一段区间一定是不合法的，所以我们只能取 $b$ 的一个前缀或后缀。观察到取的区间长度具有单调性，可以尝试二分求出这个最短的前缀和后缀，进而求出答案。

若 $b=a[l,\dots,r]$，最短前缀**在 $a$ 数组中**位置为 $pre$，最短后缀为 $suf$，则答案为 $l \times (n - pre + 1) + suf \times (n - r + 1) - l \times (n - r - 1)$。

因为选择区间若包含另一合法区间，这个区间一定也是合法的。即选择区间覆盖 $[l,pre]$ 或覆盖 $[suf,r]$ 再减去重复的。

注意二分的 check 中的细节很多。可以分开考虑选择区间长度是否 $\le \dfrac{m}2$。若是，只需要检查元素够不够用即可。这部分注意判断，当 $m$ 为奇数时，不能计算最中间的元素，否则会 Wrong Answer on test 41。

否则，先判断没能覆盖到的地方是否本来就是回文，然后判断元素是否够用即可。

细节很多。（至少我写的是这样 QAQ，不知道有没有容易写点的做法）

$\text{Code}$：

```cpp
#define mid (l + r >> 1)
#define rep(i, b, s) for(int i = (b); i <= (s); ++i)
#define per(i, b, s) for(int i = (b); i >= (s); --i)
  
def(N, int, 1e5 + 5)

int n;
int a[N];
int cnt[N];

bool chk_pre(int s, int t, int x) {
	int len = (s + t >> 1) - s + ((s + t) & 1);
	if(x >= s + len - 1) {
		memset(cnt, 0, sizeof cnt);
		rep(i, s, x) ++cnt[a[i]];
		rep(i, x + 1 + ((s + t) % 2 == 0 && x == s + len - 1), t) if(--cnt[a[i]] < 0) return 0;
		return 1;
	}
	rep(i, x + 1, s + len - 1) if(a[i] != a[t - i + s]) return 0;
	memset(cnt, 0, sizeof cnt);
	rep(i, s, x) ++cnt[a[i]];
	rep(i, t - (x - s), t) if(--cnt[a[i]] < 0) return 0;
	return 1;
}

bool chk_suf(int s, int t, int x) {
	int len = (s + t >> 1) - s + ((s + t) & 1);
	if(x <= t - len + 1) {
		memset(cnt, 0, sizeof cnt);
		rep(i, x, t) ++cnt[a[i]];
		rep(i, s, x - 1 - ((s + t) % 2 == 0 && x == t - len + 1)) if(--cnt[a[i]] < 0) return 0;
		return 1;
	}
	rep(i, s + len, x - 1) if(a[i] != a[t - i + s]) return 0;
	memset(cnt, 0, sizeof cnt);
	rep(i, x, t) ++cnt[a[i]];
	rep(i, s, s + (t - x)) if(--cnt[a[i]] < 0) return 0;
	return 1;
}

int bs_pre(int s, int t) {
	int l = s, r = t, ans = t;
	while(l <= r) {
		if(chk_pre(s, t, mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}

int bs_suf(int s, int t) {
	int l = s, r = t, ans = s;
	while(l <= r) {
		if(chk_suf(s, t, mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}

int main() {
	qread(n);
	rep(i, 1, n) qread(a[i]), ++cnt[a[i]];
	int c = 0;
	rep(i, 1, n) c += (cnt[i] & 1);
	if(c > (n & 1)) {
		puts("0");
		return 0;
	}
	int l = 1, r = n;
	while(l < r) {
		if(a[l] != a[r]) break;
		++l, --r;
	}
	if(l >= r) {
		cout << 1ll * n * (n + 1) / 2 << endl;
		return 0;
	}
	int pre = bs_pre(l, r), suf = bs_suf(l, r);
	ll ans = 1ll * l * (n - pre + 1) + 1ll * suf * (n - r + 1) - 1ll * l * (n - r + 1);
	cout << ans << endl;
	return 0;
}
```


---

## 作者：skyskyCCC (赞：1)

## 前言。
较大型分类讨论，已经很少见到细节这么多的大讨论了。
## 分析。
首先我们判断没有方案数的情况，显然我们可以先统计一下每个数字出现的次数，用桶统计一下，有两种情况：
- 序列长度为偶数且其中有某个数出现了奇数次。
- 序列长度为奇数且统计的个数中有超过一个为奇数。

此时不可能形成回文，简而言之就是我们桶中存的数的奇偶性决定了是否无解。综合上面的两种情况，显然实际上只要有大于一个奇数存在于桶中就无解。

有一个经典的思路就是从序列的两端开始往中间找，类似于一个指针的思路，寻找已经构成回文的最长长度，然后分别考虑两个指针还可以往中间走多远。这个就可以在本题得到运用。我们设左边的指针还可以往中间走 $len_1$ 元素，并且右边还可以往中间走 $len_2$ 个元素。我们同时认为面前的已经构成回文的最长长度为 $maxx$。

我们移动指针的过程可以这么模拟：以左指针的移动为例，从我们目前的 $maxx$ 的右边开始移动，我们要构造一个回文字串则只需统计已经使用的元素的个数，为了避免上面的无解情况，只要其不超过当前指针所指的元素的个数的一半就可以继续向前走。这种情况没有限制条件。

那么我们单独考虑当前已使用的元素的个数，已经超过了当前元素在整个序列中个数的一半，则有：
- 如果当前元素所处的位置在回文中心的左侧，则当前位置无解，停止运动。
- 如果当前元素所处的位置在回文中心，考虑前面的无解情况，如果正好当前元素在整个序列中出现奇数次，则当前位置可以构成一个解。否则，当前位置无解，停止运动。
- 如果当前元素所处的位置在回文中心的右侧，但是其与回文中心的对称的位置的元素与当前的元素相等，则当前位置显然构成了一个回文，为解。否则，当前位置无解，停止运动。

右指针的运动反过来即可。

显然左指针对应的从 $1$ 到 $maxx+len_1+1$ 与右指针对应的 $maxx+1$ 均可以一一对应，形成一对可变区间。这是固定左边而考虑右边的情况。那么我们反过来，固定左指针为 $maxx+1$ 与右指针对应的从  $n-maxx-len_2$ 到 $n$ 也可以一一对应，形成一组可变区间。同时我们还有去重，我们显然重复计算了左指针对应 $maxx+1$ 与右指针对应 $maxx+1$ 的区间，所以最终答案就是

$$\left(maxx+len_1+1\right)\times\left(maxx+1\right)+\left(maxx+1\right)\times len_2$$
将上式提取公因式即可以得到 $\left(maxx+1\right)\times\left(maxx+1+len_1+len_2\right)$ 的样子。显然每个变量都可以求出来。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,a[100005];
int sum,tot=-1,l,t[100005];
int cou[100005],cou2[100005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        t[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        sum+=(t[i]&1);
    }
    if(sum>1){
    	cout<<"0\n";
        return 0;
    }//首先判断能不能形成回文。
	//如果不能形成回文我们就可以不讨论了。 
    for(int i=1;i<=n;i++){
        if(a[i]!=a[n-i+1]){
            tot=i-1;
            break;
        }
        else t[a[i]]-=2;
    }//找到左右回文的最大长度。
    if(tot==-1){
    	cout<<1ll*n*(n+1)/2<<"\n";
        return 0;
    }//本身就是个回文的情况需要特判。 
    for(int i=tot+1;i<=n;i++){
        cou[a[i]]++;
        if(cou[a[i]]*2>t[a[i]]){
            if(i<n-i+1){
            	break;
			}
			if(i==n-i+1&&t[a[i]]%2==0){
				break;
			}
			if(a[i]!=a[n-i+1]){
			    break;
			}
		}
        l++;
    }
    for(int i=n-tot;i>=1;i--){
        cou2[a[i]]++;
        if(cou2[a[i]]*2>t[a[i]]){
            if(i>n-i+1){
            	break;
			}
			if(i==n-i+1&&t[a[i]]%2==0){
				break;
			}
			if(a[i]!=a[n-i+1]){
			    break;
			}
		}
        l++;
    }
    cout<<1ll*(tot+1)*(tot+1+l)<<"\n";
    return 0;
}
```
## 后记。
注意因为 $n$ 的范围较大，所以答案需要强制转换一下。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

