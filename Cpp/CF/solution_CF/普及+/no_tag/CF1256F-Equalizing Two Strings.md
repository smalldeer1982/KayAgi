# Equalizing Two Strings

## 题目描述

### 题意

给你两长度都为 $n$ 的小写字符串 $S, T$。

每次操作中你可以任选一个 $L (1\le L\le n)$，同时翻转 $S$ 中的任意一个长度为 $L$ 的子串和 $T$ 中任意一个长度为 $L$ 的子串。

请回答你是否能在若干次操作后使两字符串一样？

## 样例 #1

### 输入

```
4
4
abcd
abdc
5
ababa
baaba
4
asdf
asdg
4
abcd
badc
```

### 输出

```
NO
YES
NO
YES
```

# 题解

## 作者：81179332_ (赞：4)

我们显然可以通过交换相邻两个字符来完成区间的翻转，则我们可以将原操作变为同时分别交换两个序列中两个相邻的元素

如果有字母再两个序列中出现次数不同，则显然无解

由于不需要最少步骤，所以我们可以将两个序列都搞成升序，如果有相同的字母，我们可以在 $s$ 中不停交换相同的两个，然后将另一个序列排好序即可

如果没有相同的字母，则两个序列的逆序对数的奇偶性需要相同，由于没有相同的字母，则序列程度不超过 $26$，暴力求逆序对即可

```cpp
//timeuse:20min
const int N = 200010;
int n;char s[N],t[N];
int cnt[26];
int main()
{
	freopen("random.in","r",stdin);
	freopen("sol.out","w",stdout);
	int T = read();
	while(T--)
	{
		for(int i = 0;i < 26;i++) cnt[i] = 0;
		n = read();scanf("%s %s",s + 1,t + 1);
		for(int i = 1;i <= n;i++) cnt[s[i] - 'a']++;
		bool fl = 0,p = 0;
		for(int i = 0;i < 26;i++) if(cnt[i] > 1) fl = 1;
		for(int i = 1;i <= n;i++) cnt[t[i] - 'a']--;
		for(int i = 0;i < 26;i++) if(cnt[i]) { p = 1;break; }
		if(p) { puts("NO");continue; }
		if(fl) { puts("YES");continue; }
		int ans1 = 0,ans2 = 0;
		for(int i = 1;i <= n;i++) for(int j = i + 1;j <= n;j++) if(s[i] > s[j]) ans1++;
		for(int i = 1;i <= n;i++) for(int j = i + 1;j <= n;j++) if(t[i] > t[j]) ans2++;
		if(ans1 - ans2 & 1) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：2)

显然当 $L=1$ 的时候是没有意义的，并且当 $L > 2$ 的时候可以以若干次 $L=2$ 的操作来替代，所以考虑 $L=2$ 的情况。

-  首先如果 $S$ 中每个字母出现的次数不等于 $T$ 中每个字母出现的次数，显然无解。
-  否则当 $S$ 中有任意两个重复的字母的时候显然有解，因为我们考虑每次将这两个字母互换不影响 $S$ ，而 $T$ 经过交换必然能够变成 $S$。
- 否则如果 $S,T$ 均为奇偶排列有解，反之无解。

关于第 $3$ 点的证明：

如果两个排列的逆序对奇偶性相同，则交换两个元素的时候它们逆序对的奇偶性依旧相同，如果不同的话那就一直不同，也就无解。

如果一直相同的话根据逆序对的性质知道必然有两个相邻的元素构成逆序对，交换这两个元素之后仍然具有这个性质。

考虑交换两个相邻元素，对于 $T$ 序列需要**偶数次**交换才能变换为 $S$ 序列，则对于 $S$ 序列我们一直交换任意两个元素经过偶数次之后也不会变动。

于是我们证明了这样是可行的。

对于最后一种情况由于没有两个相同的字母，所以总长度不超过 $26$ ，暴力求逆序对即可。

```cpp
#include <bits/stdc++.h>
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 2e5 + 200;
int tp, n, flg, mps[26], mpt[26];
char s[maxn], t[maxn];

int main() {
    tp = read();
    while(tp--) {
        flg = 0;
        memset(mps, 0, sizeof(mps));
        memset(mpt, 0, sizeof(mpt));
        n = read();
        scanf("%s%s", s + 1, t + 1);
        for (int i = 1; i <= n; i++) {
            mps[s[i] - 'a']++, mpt[t[i] - 'a']++;
        }
        for (int i = 0; i <= 25; i++) {
            if (mps[i] != mpt[i]) {
                flg = 1;
                puts("NO");
                break;
            }
        }
        if (flg) continue;
        for (int i = 0; i <= 25; i++) {
            if (mps[i] > 1) {
                puts("YES");
                flg = 1;
                break;
            }
        }
        if (flg) continue;
        int p1 = 0, p2 = 0;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i - 1; j++) {
                if (s[j] > s[i]) p1++;
                if (t[j] > t[i]) p2++;
            }
        }
        if (p1 % 2 == p2 % 2) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：lsr1409111459 (赞：1)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1256F)）

##### 1.1 题目大意

给你两个长度为 $n$ 的由小写字母组成的字符串 $s$ 和 $t$ 。

对于一次操作，你可以选择任意长度为 $len(1\leq len \leq n)$ 的一段并进行下述操作：

（1）在 $s$ 中选择任意一个长度为 $len$ 的子串并将其翻转。

（2）同时在 $t$ 中选择任意一个长度为 $len$ 的子串并将其翻转。

要注意对于一次操作，你只需要关注 $len$ 相同，并不需要关注具体区间。例如 $len=3$ 且 $n=5$ ，你可以翻转 $s[1...3]$ 和 $t[3...5]$ ，        $s[2...4]$ 和 $t[2...4]$ ，但是不可以是 $s[1...3]$ 和 $t[1...2]$ 。

你的任务是判断在若干次（可能为 $0$ 次）操作后， $s$ 和 $t$ 是否可能相等。

共有 $q$ 组问题。

##### 1.2 输入格式

第一行一个整数 $q(1\leq q \leq 10^4)$ 。

对于每组问题，共三行。

每组第一行为一个整数 $n(1 \leq n \leq 2·10^5)$ ，表示 $s$ 和 $t$ 的长度。

每组第二行为一个由小写字母组成的长度为 $n$ 的字符串 $s$ 。

每组第三行为一个由小写字母组成的长度为 $n$ 的字符串 $t$ 。

 $q$ 组问题的 $n$ 的和不超过 $2·10^5(\sum{n}\leq{2·10^5})$ 。

##### 1.3 输出格式

共 $q$ 行。

每行为对应问题的答案。"YES"表示 $s$ 和 $t$ 可能在若干次操作后相等，"NO"表示不能。

#### 2 解题思路

本题是一道找规律题。（这么说可能不太讲理）

对于每组数据，我们首先判断两个字符串里各个字符的个数是否相等，如果不相等，直接 $NO$ 。

接下来，我们判断是否有字符个数大于等于 $2$ ，如果有，直接 $YES$ 。因为我们可以在一个串中选两个相等的字符放在一起然后只选中它们进行翻转，相当于这个串是一直不变的。而另一个串在若干次变换后一定会和该串相等（因为所有字符数都相等，类似于冒泡排序）。

以上两条都是找规律的问题，接下来才进入正式解题的部分。

如果满足了第一条但不满足第二条，那么我们可以通过判断字符串的逆序对奇偶性是否相同来判断是否可行。我们来考察冒泡排序移动次数和逆序对的关系。例如： $4,1,3,2$ 。序列的逆序对为 $4$ ，而我们考虑向大冒，即 $4$ 先移动 $3$ 次到最末尾，然后 $3$ 再移动 $1$ 次到倒数第二个。我们发现每个序列冒泡排序的移动次数就是逆序对数。

至于为什么奇偶性，我们考虑将每个字符串都变成元素按字典序递增的形式，称为标准形式，每次 $len$ 只取 $2$ ，即冒泡排序。那么如上所说，如果逆序对数相同，说明二者可以同时变成标准形式。如果不同，则必有一个串先变成标准形式。那么如果奇偶性相同，则另一个串的剩余变换次数为偶数次，那么对于已经变好的串，我们将前两位进行偶数次变换，串仍然是标准形式，此时另一个串也达到标准形式。然而如果奇偶性不同，二者总会有两个元素相反，所以不可行。

综上，排除前两种情况后，我们只需要考虑两个字符串的逆序对数奇偶性是否相同即可。

#### 3 解题代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int q;
int n;
char s1[200010],s2[200010];
int cnt1[30],cnt2[30];//记录每个字符个数
int ans1,ans2;//记录逆序对数
int main()
{
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&n);
        memset(cnt1,0,sizeof(cnt1));
        memset(cnt2,0,sizeof(cnt2));
        ans1=0;ans2=0;
        scanf("%s%s",s1,s2);
        for(int i=0;i<n;i++)
        {
            cnt1[s1[i]-'a']++;
            cnt2[s2[i]-'a']++;
            for(int j=s1[i]-'a'+1;j<26;j++)//这里因为字符数量有限，因此我们可以通用比当前元素大的所有字符的个数来表示前面元素与当前元素构成的逆序对数
                ans1+=cnt1[j];
            for(int j=s2[i]-'a'+1;j<26;j++)
                ans2+=cnt2[j];
            ans1%=2;//我们只要逆序对的奇偶性，因此为了放置爆int，我们随时取模
            ans2%=2;    
        }
        bool flag1=true,flag2=false;//flag1=false说明有字符在两个串中的个数不等，flag2=true说明有字符个数大于等于2
        for(int i=0;i<26;i++)
        {
            if(cnt1[i]!=cnt2[i])
            {
                flag1=false;
                break;
            }
            if(cnt1[i]>=2||cnt2[i]>=2)
                flag2=true;
        }
        if(!flag1){printf("NO\n");continue;}//存在某字符在两个串中个数不等
        if(flag2||ans1==ans2){printf("YES\n");continue;}//存在某字符数量大于等于2或两串逆序对奇偶性相同
        printf("NO\n");//；两串逆序对奇偶性不同
    }
    return 0;
}
```

#### 4 解题心得

这道题拿了一血是没想到的，考场上只想到了逆序对数但是第二个样例死活过不去，手动模拟了一下才找到第二条规律。题目不算很难，但是逆序对确实是巧妙的东西。

---

## 作者：installb (赞：1)

Codeforces Round #598 (Div. 3) F  

首先无论反转多长的子串 最后的效果能够等同于进行若干次相邻两个字母交换  
把相邻交换看作后者前移  
```cpp
abcd->abdc->adbc->dabc
dabc->dacb->dcab
dcab->dcab
dcba
```

接下来分类讨论  

- 如果有字母在S和T中出现次数不同  

显然 $\sf{NO}$ 这还需要解释吗

- 如果S和T中存在一个字母出现不止一次  

把 S 中这两个字母想办法变成相邻 这一定能做到  
然后每次操作交换 S 的这两个相邻字母 T就可以任意交换  
S 不变 T 一定可以变成 S  

因为可以看作每一个字符任意右移 每次把需要移动的移过去就行了

- 其它情况

我们可以先想办法把 S 变成升序 同时对T任意选择两个相邻字母每次交换这两个 这一步的次数取决于 S 中逆序对的个数 假设这个数为$x$  
这样之后再把 T 变成升序 假设 T 中逆序对个数为$y$ 这一步需要的步数等于$y+1$或$y-1$($x$为奇数) 或 $y$($x$为偶数)  

如果$x$为奇数 在"任意选择两个相邻字母每次交换这两个"操作中 S排序完后T的逆序对显然会增加或减少一个 而如果$x$为偶数 这个数不会改变

同时也要在S上进行这些操作(任意选择两个相邻字母每次交换这两个)  

可以看出$x+y$为偶数是能做到上面一步 否则如果一个为升序 另一个逆序对必会为1  

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

LL T,n;
string s,t;
LL cnt[2][28] = {0};

LL tr[35] = {0};
LL lowbit(LL x){ return (x & (-x)); }
void modify(LL x){ for(;x <= 26;x += lowbit(x)) tr[x] ++; }
LL query(LL x){ LL ret = 0; for(;x;x -= lowbit(x)) ret += tr[x]; return ret; }
// 树状数组求逆序对
// 好像没必要啊

int main(){
	cin >> T;
	while(T --){
		memset(cnt,0,sizeof(cnt));
		cin >> n; cin >> s >> t;
		for(LL i = 0;i < n;i ++){
			cnt[0][s[i] - 'a' + 1] ++;
			cnt[1][t[i] - 'a' + 1] ++;
		}
		
		LL dif = 0; for(LL i = 1;i <= 26;i ++) if(cnt[0][i] != cnt[1][i]) dif = 1;
		if(dif){ cout << "NO" << endl; continue; }
		    // 情况1
      LL sam = 0; for(LL i = 1;i <= 26;i ++) if(cnt[0][i] >= 2) sam = 1;
		if(sam){ cout << "YES" << endl; continue; }
        // 情况2
		
		LL ans = 0,ant = 0;
		memset(tr,0,sizeof(tr));
		for(LL i = 0;i < n;i ++){ ans += query(s[i] - 'a' + 1); modify(s[i] - 'a' + 1); }
		memset(tr,0,sizeof(tr));
		for(LL i = 0;i < n;i ++){ ant += query(t[i] - 'a' + 1); modify(t[i] - 'a' + 1); }
		
		cout << ((ans & 1) == (ant & 1) ? "YES" : "NO") << endl;
	}
	return 0;
}
```

---

## 作者：Mr_Wu (赞：1)

考虑一次对某区间的翻转，就是若干次对相邻两字符的翻转。

这里给出大小为 3 的证明：

1. $\text{abc}$ 变为 $\text{acb}$
2. $\text{acb}$ 变为 $\text{cab}$
3. $\text{cab}$ 变为 $\text{cba}$

因此我们不如将题目转化为：是否能通过若干次**同时地**交换相邻字符使得两字符串一样。

首先我们必然要判断两个字符串中每个字符的出现次数是否相等。

其次，考虑两个情况：

- $S$ 中有两相同字符，此时将 $S$ 移动成升序，并在移动 $T$ 的同时交换 $S$ 的相同字符，这一定能让两字符串一样。
- $S$ 中有两不同字符，此时我们不得不判断两串转成升序排列的次数是否同奇偶，也即判断逆序对数是否同奇偶即可。

一个数据点的复杂度是 $O(nc)$，其中 $c$ 是字符集大小，当然也可以写 $O(n\log c)$ 的，不过 $c=26$ 已经可以用暴力跑过去了。

代码：

```cpp
#include <cstdio>
 
typedef long long ll;
ll read()
{
	ll ret = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
	return ret;
}
const int MAXN = 200005;
 
int Q, N, cnt[26], ans1, ans2;
char S[MAXN], T[MAXN];
int main()
{
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d%s%s", &N, S + 1, T + 1); int i, j;
		for (i = 0; i < 26; ++i) cnt[i] = 0;
		bool flag = 0;
		for (i = 1; i <= N; ++i)
		{
			++cnt[S[i] - 'a'];
			if (cnt[S[i] - 'a'] > 1) flag = 1;
		}
		for (i = 1; i <= N; ++i) --cnt[T[i] - 'a'];
		for (i = 0; i < 26; ++i) if (cnt[i]) { puts("NO"); break; }
		if (i < 26) continue;
		if (flag) puts("YES");
		else
		{
			ans1 = ans2 = 0;
			for (i = 0; i < 26; ++i) cnt[i] = 0;
			for (i = 1; i <= N; ++i)
			{
				for (j = S[i] - 'a' + 1; j < 26; ++j) ans1 += cnt[j];
				++cnt[S[i] - 'a'];
			}
			for (i = 0; i < 26; ++i) cnt[i] = 0;
			for (i = 1; i <= N; ++i)
			{
				for (j = T[i] - 'a' + 1; j < 26; ++j) ans2 += cnt[j];
				++cnt[T[i] - 'a'];
			}
			puts((ans1 - ans2) % 2 ? "NO" : "YES");
		}
	}
	return 0;
}
```





---

