# [JOI 2020 Final] JJOOII 2

## 题目描述

定义有连续 $K$ 个 $\tt J$ 和连续 $K$ 个 $\tt O$ 和连续 $K$ 个 $\tt I$ 组成的字符串为 $K$ 阶 JOI 串。

比如，$\tt JJOOII$ 为 $2$ 阶 JOI 串，**但是，注意要有顺序**，比如 $\tt OOJJII$ 就不是 $2$ 阶 JOI 串。

现在，给定一个长度为 $N$ 的字符串 $S$，可以对他进行 $3$ 种操作：

- 操作 $1$：删除 $S$ 开头的字符
- 操作 $2$：删除 $S$ 结尾的字符
- 操作 $3$：删除 $S$ 除了开头和结尾之外的一个字符

我们要通过这些操作让 $S$ 变为 $K$ 阶 JOI 串。

但是，我们想让操作 $3$ 尽量的少。

所以我们想知道，变为 $K$ 阶 JOI 串操作 $3$ 最少需要进行多少次？

如果不能变为 $K$ 阶 JOI 串，那么输出 $-1$。

## 说明/提示

#### 样例 1 解释

1. 进行一次操作 $1$，变为 $\tt JIJOIOIIJ$。
2. 进行一次操作 $2$，变为 $\tt JIJOIOII$。
3. 进行一次操作 $3$，删掉字符 $2$，变为 $\tt JJOIOII$。
4. 进行一次操作 $3$，删掉字符 $4$，变为 $\tt JJOOII$。

#### 样例 2 解释

$\tt JJJOOOIII$ 已经是 $3$ 阶 JOI 串了，所以不需要进行操作。

#### 样例 3 解释

$\tt IIIOOOJJJ$ 无法变为 $1$ 阶 JOI 串，无解。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（1 pts）：$N \le 21$。
- Subtask 2（12 pts）：$N \le 3000$。
- Subtask 3（87 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $3 \le N \le 2 \times 10^5$。
- $1 \le K \le \dfrac{N}{3}$。
- $S$ 只包含 $\tt J$，$\tt O$，$\tt I$ 且长度为 $N$。

#### 说明

翻译自 [第19回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [B JJOOII 2](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t2.pdf)。

## 样例 #1

### 输入

```
10 2
OJIJOIOIIJ```

### 输出

```
2```

## 样例 #2

### 输入

```
9 3
JJJOOOIII
```

### 输出

```
0```

## 样例 #3

### 输入

```
9 1
IIIOOOJJJ
```

### 输出

```
-1```

# 题解

## 作者：NewJeanss (赞：12)

截至2020年10月29日，蒟蒻暂时获得了**最优解**（靠运气）。

其实这道题不用想的很复杂，蒟蒻原以为是要动态规划或者搜索剪枝什么的。实际上只要 $\mathcal{O}(n)$ 即可解决。

首先，题目要求的是**有顺序的**的 $k$ 个 JOI 串。既然是有顺序，我们可以定位**每一个** J ，从当前位置（ $x$ ）往后找**最近的** $k$ 个 J ，这必然是包含 $x$ 位置时的最优解。以此类推，找到 O 和 I 即可。最终最优的串一定存在于我们所找的这些串中。

那么找最近的 $k$ 个 J ,蒟蒻一开始也傻傻的暴力往后遍历，会浪费很多时间。实际上，我们可以**保存**每一个 J 的位置（同理 O，I），然后直接使用 `+k-1` 来求后 $k$ 个 J 的那个位置。

良心不卡常不炫技代码：


```cpp
#include <bits/stdc++.h>
#define N 200005
#define inf 0x3f3f3f3f
using namespace std;
int cntj[N],cnto[N],cnti[N],n,k,cj,co,ci,lo,li,end,ans;
string s;
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	while(cin>>n>>k>>s){
		s=" "+s; cj=co=ci=0;
		for(int i=1;i<=n;i++){//记录位置
			if(s[i]=='J') cntj[++cj]=i;
			if(s[i]=='O') cnto[++co]=i;
			if(s[i]=='I') cnti[++ci]=i;
		}
		lo=li=1; ans=inf;
		for(int i=1;i<=cj;i++){//遍历每一个J
			if(i+k-1>cj) break;//如果后面不足k个，跳出循环。后同理。
        		//注意lo和li不用每次从1开始，位置是单调递增的。
			end=cntj[i+k-1];
			while(cnto[lo]<=end&&lo<=co) lo++;
			if(lo+k-1>co) break;
			end=cnto[lo+k-1];
			while(cnti[li]<=end&&li<=ci) li++;
			if(li+k-1>ci) break;
			ans=min(ans,cnti[li+k-1]-cntj[i]+1-3*k);//总区间减去不用删除的长度即3*k
		}
		if(ans!=inf) cout<<ans<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```

------------

为什么会想到找 J 呢？因为整个所谓JOI串，实际上就是找 k 个 J，随后便可以**确定**这个串。抓住要害，简化问题。


---

## 作者：一只书虫仔 (赞：5)

#### Description

定义有连续 $K$ 个 $\tt J$ 和连续 $K$ 个 $\tt O$ 和连续 $K$ 个 $\tt I$ 组成的字符串为 $K$ 阶 JOI 串。

比如，$\tt JJOOII$ 为 $2$ 阶 JOI 串，**但是，注意要有顺序**，比如 $\tt OOJJII$ 就不是 $2$ 阶 JOI 串。

现在，给定一个长度为 $N$ 的字符串 $S$，可以对他进行 $3$ 种操作：

- 操作 $1$：删除 $S$ 开头的字符
- 操作 $2$：删除 $S$ 结尾的字符
- 操作 $3$：删除 $S$ 除了开头和结尾之外的一个字符

我们要通过这些操作让 $S$ 变为 $K$ 阶 JOI 串。

但是，我们想让操作 $3$ 尽量的少。

所以我们想知道，变为 $K$ 阶 JOI 串操作 $3$ 最少需要进行多少次？

如果不能变为 $K$ 阶 JOI 串，那么输出 $-1$。

#### Subtask 1

暴力枚举。

#### Subtask 2

我们消除的过程其实可以模拟成这样：

- 将左边一些无用字符删除一直到字符 $\tt J$。
- 将右边一些无用字符删除一直到字符 $\tt I$。
- 将中间一些字符删除使字符串变为 JOI 串。

因为，我们可以一个类似“指针”的过程来进行一个扫描：

- 从一个 $\tt J$ 开始往后扫描所有 $\tt J$。
- 从一个 $\tt O$ 开始往后扫描所有 $\tt O$。
- 从一个 $\tt I$ 开始往后扫描所有 $\tt I$。

然后 Subtask 2 就可以过了。

#### Subtask 3

重新观察 JOI 串的定义，如果要选择 $K$ 阶 JOI 串的 $\tt J$ 部分，最优的情况一定是选择连续 $3$ 个 $\tt J$。

因此我们不需要扫描所有 $\tt J$，只需要扫描到一个 $\tt J$ 然后得到与他最近的 $K-1$ 个 $\tt J$ 位置即可。

所以我们只需要扫一遍字符串然后求最小 JOI 串长度即可。

---

## 作者：zsyzsy_2012 (赞：2)

二分+前缀和简单题。

先计算三个字母的前缀和，再考虑第一个 `J` 的位置，设为 $i$。然后二分得出第 $k$ 个 `J` 最靠前的位置，接着求出第 $k$ 个 `O` 最靠前的位置，最后求出第 $k$ 个 `I` 最靠前的位置，与 $i$ 做差得到当前长度，所有长度中取最小即是答案。

下面是此题的 AC 代码：

```
#include <bits/stdc++.h>
#define N 200010
using namespace std ;
const int inf = (int)1e9 ;
char s[N] ;
int sum[3][N] ;
int main() {
    int n , k , ans = inf ;
    scanf("%d%d\n" , &n , &k) ;
    for(int i = 1 ; i <= n ; i++) scanf("%c" , &s[i]) ;
    scanf("\n") ;
    for(int i = 1 ; i <= n ; i++) {
        for(int j = 0 ; j < 3 ; j++) sum[j][i] = sum[j][i - 1] ;
        if(s[i] == 'J') sum[0][i]++ ;
        if(s[i] == 'O') sum[1][i]++ ;
        if(s[i] == 'I') sum[2][i]++ ;
    }
    for(int i = 1 ; i <= n ; i++) {
        if(s[i] != 'J') continue ;
        int l = i , r = n , best = -1 ;
        while(l <= r) {
            int mid = (l + r) / 2 ;
            if(sum[0][mid] - sum[0][i - 1] >= k) {
                best = mid ;
                r = mid - 1 ;
            }
            else {
                l = mid + 1 ;
            }
        }
        if(best == -1) continue ;
        int ll = best + 1 , rr = n , bbest = -1 ;
        while(ll <= rr) {
            int mid = (ll + rr) / 2 ;
            if(sum[1][mid] - sum[1][best] >= k) {
                bbest = mid ;
                rr = mid - 1 ;
            }
            else {
                ll = mid + 1 ;
            }
        }
        if(bbest == -1) continue ;
        int lll = bbest + 1 , rrr = n , bbbest = -1 ;
        while(lll <= rrr) {
            int mid = (lll + rrr) / 2 ;
            if(sum[2][mid] - sum[2][bbest] >= k) {
                bbbest = mid ;
                rrr = mid - 1 ;
            }
            else {
                lll = mid + 1 ;
            }
        }
        if(bbbest == -1) continue ;
        ans = min(ans , bbbest - i + 1 - 3 * k) ;
    }
    if(ans == inf) printf("-1") ;
    else printf("%d" , ans) ;
    return 0 ;
}
```


---

## 作者：Obvicat_awa (赞：2)

## 一.题意简述

给你一个由 `JOI` 三个字母组成的字符串，你可以从前，后和中间删去若干个，让其变成 $k$ 个 `J` ，$k$ 个 `O`，$k$ 个 `I`。

## 二.解题思路

听了许多 $O(n\log n)$ 甚至是 $O(n)$ 的做法后，我觉得自己太菜了，所以就来水一发无脑的 $O(n\log^2n)$ 做法。

考虑直接去二分至多需要多少次 $3$ 操作才能得到目标的字符串，然后考虑怎么写 `check`

在 `check(int x)` 里，我们要找到一个子串，删掉 $x$ 个字符后还剩下目标字符串的 $3k$ 个字符。那就相当于是我暴力枚举左端点为 $i$，右端点就是 $r=i+3k+x-1$。

于是我们就得到了这个子串，考虑怎么判断它有没有可能被操作成目标字符串。

那么我的做法是找到从 $i$ 开始第一个满足 $i$ 到它之间有 $k$ 个 `J` 的位置 $p_1$，然后找到从右往左第一个满足它们之间有 $k$ 个 `I` 的位置 $p_2$，判断 $p_1$ 和 $p_2$ 之间有没有 $k$ 个 `O`，如果有就是，没有就不是。

那么我们就可以通过二分答案找到 $p_1$ 和 $p_2$，注意提前处理三个前缀和统计区间字母的个数。

这样二分套二分就是 $n\log^2n$ 的，我知道这个方法很蠢，不过 $10^5$ 还是足够的，于是~~赢得最拉解~~。不过我觉得还是蛮好想的喵！

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int n,k,cntj[N],cnto[N],cnti[N];
string s;
inline bool enghj(int s,int t){
	return cntj[t] - cntj[s-1] >= k;
}
inline bool enghi(int s,int t){
	return cnti[t] - cnti[s-1] >= k;
}
inline bool check(int x){
//	cout << x << endl;
	int len = 3*k + x;
	for(int i = 1;i+len-1 <= n;i ++){
		if(cntj[i+len-1]-cntj[i-1] < k || cnti[i+len-1]-cnti[i-1] < k)continue;
		int ll,rr;
		int l = i,r = i+len-1;
		while(l < r){
			int mid = (l + r) >> 1;
			if(enghj(i,mid))r = mid;
			else l = mid + 1;
		}
		ll = l;
		l = i,r = i+len-1;
		while(l < r){
			int mid = (l + r + 1) >> 1;
			if(enghi(mid,i+len-1))l = mid;
			else r = mid - 1;
		}
		rr = r;
		if(cnto[rr] - cnto[ll-1] >= k)return 1;
	}
	return 0;
}
int main(){
//	freopen("joi.in","r",stdin);
//	freopen("joi.out","w",stdout);
	cin.tie(0),cout.tie(0);
	cin >> n >> k >> s;s = ' ' + s;
	for(int i = 1;i <= n;i ++)cntj[i] = cntj[i-1] + (s[i]=='J'),cnto[i] = cnto[i-1] + (s[i]=='O'),cnti[i] = cnti[i-1] + (s[i] == 'I');
	int l = 0,r = n-k*3+1;
	while(l < r){
		int mid = (l + r) >> 1;
		if(check(mid))r = mid;
		else l = mid + 1;
	}
	if(l == n-k*3+1){puts("-1");return 0;}
	cout << l << endl;
	return 0;
}
```

---

## 作者：Aoharu_shiroko (赞：2)

# 题目描述
构造一个长度为 $3K$，且 `J` `O` `I` 的长度分别为 $K$ 的字符串，顺序为先 `J` 在 `O` 最后是 `I`。

但是这里有个字符串 $S$ 由`J` `O` `I` 组成（可能有序也可能无序）。

又给出三种操作：
+	操作 $1$：删除 $S$ 开头的字符。
+	操作 $2$：删除 $S$ 结尾的字符。
+	操作 $3$：删除 $S$ 除了开头和结尾之外的一个字符。

我们要通过这些操作让 $S$ 变为 $K$ 阶 `JOI` 串。

但是，我们要操作 $3$ 使用的个数最少。

求使用多少次操作 $3$ 可以让 $S$ 变成 $K$ 阶 `JOI` 串。如果不能就输出 $-1$。


# 思路点拨
首先，我们要找到像样例一样的 $K$ 阶字串。

怎么找最高效？

我们可以运用前缀和和二分进行查找，二分不用说为了让时间复杂度更高效。

用前缀和是为什么呢？

因为它可以允许我们更高效的统计字符出现了多少次。

现在正式开始解题！

枚举每个字串的起始位置，用二分和前缀和依次找到 $K$ 阶的 `J` `O` `I` 的右端点。

遍历完整个字符串的同时，求出 $ans$ 的最小值就是答案。

Ps：这里的二分采用 [lower_bound](https://blog.csdn.net/qq_37529913/article/details/125139815) 来求位置。

# AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k;
string s;
int J[1000005],O[1000005],I[1000005];


int main()
{
	scanf("%d%d",&n,&k);
	cin >> s;
	for (int i=1;i<=n;i++)
	{
		J[i]=J[i-1];
		O[i]=O[i-1];
		I[i]=I[i-1];
		if (s[i-1]=='J') ++J[i];
		if (s[i-1]=='O') ++O[i];
		if (s[i-1]=='I') ++I[i];
	}
	int ans=0x3f3f3f3f;
	for (int i=1;i<=n;i++)
	{
		if(s[i-1]!='J') continue;
        	//好好想想为什么左端点要减一，在通过前缀和+lower_bound去取右端点
		int x=lower_bound(J+1,J+1+n,J[i-1]+k)-J;
		int y=lower_bound(O+1,O+1+n,O[x-1]+k)-O;
		int z=lower_bound(I+1,I+1+n,I[y-1]+k)-I;
		if (x>n||y>n||z>n)
		{
			break;
		}
		ans=min(ans,z-i+1);
	}
	if (ans==0x3f3f3f3f)
	{
		cout << -1 << endl;
	}
	else{
		cout << ans-k*3 << endl;
	}
	return 0;
}
```

---

## 作者：Kano_zyc (赞：1)

## 题目分析

这个问题要求我们找到一个字符串 $S$ 的最短子串，这个子串能够被转换为一个 $K$ 阶 `JOI` 字符串，仅通过删除非首尾的字符。 

$K$ 阶 `JOI` 字符串是一个由 $K$ 个 `J`，接着是 $K$ 个  `O`，最后是 $K$ 个 `I` 组成的字符串。我们的目标是最小化这种转换所需的删除操作次数。

## 解题思路

为了解决这个问题，我们首先需要找到一个子串，它包含至少 $K$ 个 `J`、$K$ 个 `O` 和 $K$ 个 `I`，并且这些字符按照 `J`、`O`、`I`的顺序排列。

一旦找到了这样的子串，我们就可以通过删除其中多余的字符来得到一个 $K$ 阶 `JOI` 字符串。

这个问题的关键在于如何高效地找到这样的子串。

我们采用的策略是使用前缀和和二分搜索。首先，我们为每个字符计算其前缀和。

这允许我们快速地计算出任何子串中每个字符的数量。

对于每个可能的子串起始位置，我们使用二分搜索来找到最少包含 $K$ 个 `J` 的位置，然后以这个位置为起点，再次使用二分搜索找到最少包含 $K$ 个 `O` 的位置，最后找到最少包含 $K$ 个 `I` 的位置。这样，我们就找到了一个包含至少 $K$ 个 `J`、$K$ 个 `O` 和 $K$ 个 `I` 的子串。我们重复这个过程，直到覆盖整个字符串。

最后，我们比较所有找到的子串的长度，并选择长度最短的一个。

这个长度最短的子串需要的删除操作次数就是我们的答案。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int J[N], O[N], I[N];

// 二分搜索找到最小的r，使得区间[l, r]包含至少k个目标字符
int findMinIndex(int l, int k, int n, int prefixSum[]) {
    int left = l, right = n, ans = n + 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (prefixSum[mid] - prefixSum[l - 1] >= k) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    // 计算前缀和
    for (int i = 1; i <= n; ++i) {
        J[i] = J[i - 1] + (s[i - 1] == 'J');
        O[i] = O[i - 1] + (s[i - 1] == 'O');
        I[i] = I[i - 1] + (s[i - 1] == 'I');
    }

    int ans = INT_MAX;
    for (int l = 1; l <= n; ++l) {
        int endJ = findMinIndex(l, k, n, J);
        if (endJ > n) break;
        int endO = findMinIndex(endJ, k, n, O);
        if (endO > n) break;
        int endI = findMinIndex(endO, k, n, I);
        if (endI > n) break;

        // 更新答案
        ans = min(ans, endI - l + 1 - 3 * k);
    }

    if (ans == INT_MAX) {
        cout << "-1\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}

```

---

## 作者：rainygame (赞：1)

老师讲过的题目，感觉是黄左右。

我们发现我们可以通过求出一个子串 $S[l,r]$，使得 $S[l,r]$ 只需要通过操作 $3$ 就可以化为 $K$ 阶字符串。显然答案即为 $(r-l+1)-3k$。

考虑把 `J`、`O`、`I` 的坐标分别存进三个 `vector` 里面，然后枚举第一个 `J` 的位置（即 $l$），然后求出最后一个 `J` 的位置；在往后找到 $k$ 个 `O`，求出最后一个 `O` 的位置；再通过最后一个 `O` 的位置求出第一个 `I` 的位置……

这样就可以求出最后一个 `I` 的位置（即 $r$），然后算更新答案即可。

注意若找不到 $k$ 个 `O` 或 `I` 就需要结束查找。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, k, ans(INT_MAX);
vector<int> cntj, cnto, cnti;
vector<int>::iterator itj, ito, iti;
string str;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> str;
    for (int i(0); i<str.size(); ++i){
        if (str[i] == 'J') cntj.push_back(i);
        else if (str[i] == 'O') cnto.push_back(i);
        else cnti.push_back(i);
    }
    ito = cnto.begin();
    iti = cnti.begin();

    for (auto it(cntj.begin()); it+k-1!=cntj.end(); ++it){
        auto itj(it+k-1);
        while (*itj > *ito && ito != cnto.end()) ++ito;
        if (cnto.end()-ito < k) break;
        ito += k-1;
        while (*ito > *iti && iti != cnti.end()) ++iti;
        if (cnti.end()-iti < k) break;
        ito -= k-1;
        ans = min(ans, *(iti+k-1)-*it+1-3*k);
    }
    if (ans == INT_MAX) cout << -1;
    else cout << ans;

    return 0;
}

```


---

## 作者：Daniel_7216 (赞：1)

提供一种比较无脑但速度快的方法。

其实稍微思考一下可以发现，这道题就是让你求一个长度最小的子串，使得这个子串可以**依次**取出 $K$ 个 $J$，$K$ 个 $O$，$K$ 个 $I$。这就意味着这个子串可以切割成三个部分，分别含有 $K$ 个需要的字母。

我们希望这三个部分都尽可能短，不难想到用而分处理。设我们需要找到的含 $k$ 个目标字母的最小整数下标为 $r$，则 $r$ 满足 $sum_r-sum_{l-1}\ge k$，也就是 $sum_r\ge sum_{l-1}+k$，其中 $l$ 是我们枚举的左端点，$sum$ 是一个记录字母出现次数的前缀和，不难想到用二分解决。

推广一下就可以得出解法：我们从 $1$ 开始枚举左端点，找到最小的下标使区间内有 $K$ 个 $J$，把这个下标作为左端点，再如法炮制找出 $K$ 个 $O$ 和 $K$ 个 $I$ 的右端点。

这个做法是我在模拟赛最后十五分钟想出来的，代码没什么细节，思维难度很低，最重要的是，代码少还跑得飞快。

考场代码，仅供参考。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm> 
using namespace std;
const int maxn = 2e5 + 1;
int sumn[maxn], sumo[maxn], sumi[maxn], ans = 1000000;
char s[200001];
int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++){
		sumn[i] = sumn[i - 1];
		if (s[i] == 'J') sumn[i]++;
		sumo[i] = sumo[i - 1];
		if (s[i] == 'O') sumo[i]++;
		sumi[i] = sumi[i - 1];
		if (s[i] == 'I') sumi[i]++;
	}
	for (int i = 1; i <= n; i++){
		//printf("%d %d %d\n", sumn[i], sumo[i], sumi[i]);
		if (s[i] != 'J') continue;
		int a = lower_bound(sumn + i, sumn + 1 + n, k + sumn[i - 1]) - sumn;
		if (a > n) break;
		int b = lower_bound(sumo + a, sumo + 1 + n, k + sumo[a - 1]) - sumo;
		if (b > n) break;
		int c = lower_bound(sumi + b, sumi + 1 + n, k + sumi[b - 1]) - sumi;
		if (c > n) break; 
		ans = min(ans, c - i + 1);
	}
	if (ans == 1000000) printf("-1");
	else printf("%d", ans - 3 * k);
	return 0;
}
```

---

## 作者：__Watcher (赞：1)

关于思路，其他题解讲得很清楚了。这篇题解提供另一个实现思路。

---

看到有一篇题解使用的尺取法（two pointers），其实可以再维护一个数组，为对于 $\rm{P,O,I}$ 三个字母，记录他们在前缀出现的次数，就可以 $O(1)$ 查询出下一个某个字母出现的位置。

这样的实现方法的好处是实现比较对称，能够体现代码的优美感。

---

提供代码，仅供参考：
```cpp
#include<bits/stdc++.h>
using namespace std;
int mpj[500005], mpo[500005], mpi[500005], sj[500005], so[500005], si[500005], n, k;
int allj, allo, alli, ans=1e9;
char ch[500005];
int main() {
	cin>>n>>k;
	scanf("%s", ch+1);
	for(int i=1;i<=n;i++) {
		mpj[i]+=mpj[i-1], mpo[i]+=mpo[i-1], mpi[i]+=mpi[i-1];
		if(ch[i]=='J') mpj[i]++, sj[++allj]=i;
		if(ch[i]=='O') mpo[i]++, so[++allo]=i;
		if(ch[i]=='I') mpi[i]++, si[++alli]=i;
	}
	for(int i=1;i<=n;i++) {
		int now=sj[mpj[i-1]+1];
		if(!now||!sj[mpj[now]+k-1]) continue;
		now=so[mpo[sj[mpj[now]+k-1]-1]+1];
		if(!now||!so[mpo[now]+k-1]) continue;
		now=si[mpi[so[mpo[now]+k-1]-1]+1];
		if(!now||!si[mpi[now]+k-1]) continue;
		now=si[mpi[now]+k-1];
		ans=min(ans, n-k*3-(i-1)-(n-now));
	}
	cout<<(ans<1e9?ans:-1);
}

```


---

## 作者：djh0314 (赞：0)

好久没写题解，水一篇。

## 题意

题意显然。

## 分析

看到这道题，我们就应该进行一个小贪心，对于最左边某一字符，直到最右边的这一字符，我们不会在中间删除同样的字符，不然则可以保留这一字符，将两边往内缩。

也就是说，我们确定了最左边的 J 后，那么留下最后一个 J 必然是当前这个 J 的后面的第 $K-1$ 个 J，对于 O 和 I 同理，找到从当前节点开始，包括当前结点的，向后共有 $K$ 个某字符的最左端点。

这个处理，我们可以使用一个栈从右向左来维护相同字符即可。

最后的答案，我们通过枚举最左边的 J，进一步确定最右的 J，确定最右的 O，最右的 I，这两个之间的价值就是 $R-L+1-3\times K$。



---

## 作者：makerlife (赞：0)

[更好的阅读体验](https://blog.makerlife.top/post/solution-P6878) | [Problem Link](https://www.luogu.com.cn/problem/P6878)

## Explanation

给定一个只包含 $\tt J$、$\tt O$、$\tt I$ 三种字符、长度为 $N$ 的字符串 $S$ 和一个正整数 $K$。定义 $K$ 阶 $\tt JOI$ 串为由恰好 $K$ 个 $\tt J$ 、$K$ 个 $\tt O$ 、$K$ 个 $\tt I$ 依次拼接而成的字串。如 $2$ 阶 $\tt JOI$ 串为 $\tt JJOOII$ 。你可以对 $S$ 进行任意次以下操作以将 $S$ 变为 $K$ 阶 $\tt JOI$ 串：

1. 删除 $S$ 的第一个字符
2. 删除 $S$ 的最后一个字符
3. 删除 $S$ 的任意一个字符

要求最小化并输出第三种操作的次数。如果不能将 $S$ 变为 $K$ 阶 $\tt JOI$ 串，输出 `-1` 。

## Solution

可以发现只要定位到了最前端的 $\tt J$ 的位置，那么就可以确定一个最短的 $\tt JOI$ 串。

即我们可以暴力从前向后扫 $\tt J$ 的位置，然后依次找到 $K$ 个 $\tt O$ 和 $\tt I$ 即可。

可以对上面的算法进行优化，我们记录每个 $\tt J$、$\tt O$、$\tt I$ 的位置为 `cj`、`co`、`ci`，那么一段 $\tt J$ 的开始位置即为 $cj_j$，结束位置为 $cj_{j+k-1}$，$\tt O$，$\tt I$ 同理。

## Core Code

```cpp
int n,k;
char s[N];
int cj[N],co[N],ci[N];
int totj,toto,toti;
int ans=INF;
int main()
{
	n=read();k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='J') cj[++totj]=i;
        if(s[i]=='O') co[++toto]=i;
        if(s[i]=='I') ci[++toti]=i;
	}
    for(int i=1;i<=totj;i++)
    {
        if(i+k-1>totj) break;//后面不足 k 个 j，下面 o,i 同理
        int ed=cj[i+k-1];//一段 j 的结束，下面 o,i 同理
        int pos=1;
        while(co[pos]<=ed && pos<=toto) pos++;//o 的起始位置，下面 i 同理
        if(pos+k-1>toto) break;
        ed=co[pos+k-1];
        pos=1;
        while(ci[pos]<=ed && pos<=toti) pos++;
        if(pos+k-1>toti) break;
        ed=ci[pos+k-1];
        ans=min(ans,ed-cj[i]+1-3*k);//答案为枚举的区间长度与 3*k 的差
    }
    printf("%d\n",(ans==INF)?-1:ans);
	return 0;
}
```



---

