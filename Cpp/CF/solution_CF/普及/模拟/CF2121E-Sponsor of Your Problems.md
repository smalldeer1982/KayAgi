# Sponsor of Your Problems

## 题目描述

For two integers $ a $ and $ b $ , we define $ f(a, b) $ as the number of positions in the decimal representation of the numbers $ a $ and $ b $ where their digits are the same. For example, $ f(12, 21) = 0 $ , $ f(31, 37) = 1 $ , $ f(19891, 18981) = 2 $ , $ f(54321, 24361) = 3 $ .

You are given two integers $ l $ and $ r $ of the same length in decimal representation. Consider all integers $ l \leq x \leq r $ . Your task is to find the minimum value of $ f(l, x) + f(x, r) $ .

## 说明/提示

In the first test case, you can choose $ x = 1 $ . Then $ f(1, 1) + f(1, 1) = 1 + 1 = 2 $ .

In the second test case, you can choose $ x = 2 $ . Then $ f(2, 2) + f(2, 3) = 1 + 0 = 1 $ .

In the third test case, you can choose $ x = 5 $ . Then $ f(4, 5) + f(5, 6) = 0 + 0 = 0 $ .

In the fourth test case, you can choose $ x = 15 $ . Then $ f(15, 15) + f(15, 16) = 2 + 1 = 3 $ .

In the fifth test case, you can choose $ x = 18 $ . Then $ f(17, 18) + f(18, 19) = 1 + 1 = 2 $ .

In the sixth test case, you can choose $ x = 200 $ . Then $ f(199, 200) + f(200, 201) = 0 + 2 = 2 $ .

In the seventh test case, you can choose $ x = 900 $ . Then $ f(899, 900) + f(900, 999) = 0 + 1 = 1 $ .

In the eighth test case, you can choose $ x = 1992 $ . Then $ f(1990, 1992) + f(1992, 2001) = 3 + 0 = 3 $ .

## 样例 #1

### 输入

```
14
1 1
2 3
4 6
15 16
17 19
199 201
899 999
1990 2001
6309 6409
12345 12501
19987 20093
746814 747932
900990999 900991010
999999999 999999999```

### 输出

```
2
1
0
3
2
2
1
3
3
4
3
5
12
18```

# 题解

## 作者：StarLinkOvO (赞：1)

# [E. Sponsor of Your Problems](https://codeforces.com/contest/2121/problem/E)

[也许更好的阅读体验](https://www.cnblogs.com/StarLink/p/18950549)

## 题目简述

定义 $f(a, b)$ 表示这两个数的十进制下数字相同的位数，如 $f(21,12) = 0$，$f(54321, 24361) = 3$。

给两个位数相同的十进制数 $l$ 和 $r$，求 $l \leq x \leq r$ 中 $f(l, x) + f(x, r)$ 的最小值。

## 思路

分类讨论，我们从简单到难分析。

首先如果 $l = r$，答案就是数字位数乘二，直接输出。

接下来考虑一般的请况，我们假设现在 $l = 1239971$，$r = 1240056$。

我们从高位到低位看，发现它们的最高两位是相同的，那么在它们之间的数都是 $12 \dots$ 的形式，和第一种相似，直接将一样的位数乘二加到答案里（但是一定要是从最高位开始都一样）。

第三、四、五位是我们讨论的重点所以我们暂时跳过一下。

我们看倒数第二位，发现如果选 $6$ 的话就完美绕开限制了，既然题目中让我们求最小值那肯定是能绕就绕，而且这一位之后的数字肯定存在和 $l$ 与 $r$ 上对应位置的数字不同的，即后面也不会对答案有贡献。所以，**当同一位上的数字之差大于 1，就直接输出答案**。

举一个其它例子，当 $l = 369, r = 531$ 时，我们最高位取了 $4$ 之后，后面的数无论怎么选都是在 $l$ 和 $r$ 这个区间里的，就一定有 473 这样每一位都和 $l, r$ 不同的，那么这之后的答案贡献就是 0。

回看第三位，即同一位上的数字相差为 1 怎么办。

那么当前位肯定是要**在两位中选一个**了，我们先将**答案加上一**再考虑后面的。

容易发现，它的下一位是几乎没有限制的，也就是对答案的贡献为 0。\
但是如果像我们举的这个例子一样，出现了 $l$ 上这一位为 9 另一个为 0，那就等于是在 39 和 40 中选一个，**答案加一**，然后考虑下一位什么情况；\
如果很不幸下一位还是这种情况，到这里相当于 399 和 400 中选，就只能一直选下去。

不过如果某一位出现了不一样的情况，像我们举的例子一样出现了其他的数字，那就相当于后面的数字又可以随便选了，后面的答案贡献都是 0，我们直接输出答案跑路就 OK 了。

如果还有不太懂的可以自己写个数想一想，还是很好推的。

思路清晰后代码就很好写了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int x, y, len, ans, tpos;
int a[3][11];

void part(int x, int op) {
    int l = 0;
    while (x) {
        a[op][++l] = x % 10;
        x /= 10;
    }
    len = l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        tpos = ans = 0;
        cin >> x >> y;
        part(x, 1), part(y, 2);

        if (x == y) { // 特判
            cout << 2 * len << endl;
            continue;
        }

        for (int i = len; i; i--) { // 判断相等的情况
            if (a[1][i] != a[2][i]) {
                tpos = i;
                break;
            }
            ans += 2;
        }

        int f = 0; // f:是否出现数字相差 1
        for (int i = tpos; i; i--) {
            // 相差为一且前面都是相等的
            if (a[1][i] + 1 == a[2][i] && !f) {
                ans++; // 只能选一个，答案肯定加一
                f = 1;
                continue;
            }
            // 前面有相差为一的情况且第一个数当前位是9另一个是0
            else if (a[1][i] == 9 && a[2][i] == 0 && f) {
                ans++; // 同样二选一
                continue;
            }

            break; // 都不符合：一定有和两个数字都不同的情况，直接输出答案
        }

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：CommandSR (赞：1)

## 思路

设输入的两个数是 $a$ 和 $b$。

从高位到低位枚举，直到 $a_i \ne b_i$，前面每一位都加上 $2$。

若当前位 $a_i + 1 < b_i$，则只需要当前位填 $a_i+1$，后面每一位都填不一样的即可，不会增加答案。

否则 $a_i + 1 = b_i$，当前位需要在 $a_i$ 和 $b_i$ 间选择。

如果选 $a_i$，且 $a_{i+1} = 9$，则下一位必须填 $9$，会再将答案增加 $1$。如果选 $b_i$，且 $b_{i+1} = 0$，则下一位必须填 $0$，也会再将答案增加 $1$。

所以一直往后枚举每一位，一直到第一个位数 $i$ 满足 $a_i \ne 9$ 或 $b_i \ne 0$ 就跳出循环即可。


## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
using namespace std;
ll a[12], b[12], ca, cb, ans = 0, f[12];
void Solve() {
	ll aa, bb; cin >> aa >> bb;
	ca = cb = ans = 0;
	while (aa) {
		a[++ca] = aa % 10;
		aa /= 10;
	}
	while (bb) {
		b[++cb] = bb % 10;
		bb /= 10;
	}
	reverse(a + 1, a + 1 + ca);
	reverse(b + 1, b + 1 + cb);
	ll p = 1;
	while (a[p] == b[p] && p <= ca) ans += 2, ++p;
	if (p > ca) {
		cout << ans << '\n';
		return;
	}
	if ((a[p] + 1) % 10 == b[p]) {
		++ans, ++p;
		while (p <= ca) {
			bool fa = (a[p] == 9);
			bool fb = (b[p] == 0);
			if (!fa) {
				cout << ans << '\n';
				return;
			} else if (!fb) {
				cout << ans << '\n';
				return;
			}
			++p, ++ans;
		}
		cout << ans << '\n';
	} else {
		cout << ans << '\n';
		return;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	ll T; cin >> T; while (T--) Solve();
	return 0;
}
```

---

## 作者：BaiBaiShaFeng (赞：0)

## 思路

没有多想，最近数位 dp 写的多，所以直接写了一个记忆化搜索。

非常无脑，我们像数位动态规划的记搜实现一样把几个数字拆开，然后搜索时记录有没有到上界或者下界，从高位往低位填数字，填完返回。

## 代码↓


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[20][20][4][4], a[15], b[15], len;
int dfs(int pos, bool limit, bool below, int sum){
    if(!pos) return sum;
    if(dp[pos][sum][limit][below]!=-1) return dp[pos][sum][limit][below];
    int up=limit?a[pos]:9, down=below?b[pos]:0, res=0x3f3f3f3f;
    for(int i=down; i<=up; ++i){
        res=min(res,dfs(pos-1,limit&&i==up,below&&i==down,sum+(i==a[pos])+(i==b[pos])));
    }
    if(!limit&&!below) dp[pos][sum][limit][below]=res;
    return res;
}
int solve(int x, int y){
    len=0;
    while(x&&y){
        a[++len]=x%10; x/=10; 
        b[len]=y%10; y/=10;
    }
    return dfs(len,true,true,0);
}
signed main(){
    memset(dp,-1,sizeof(dp));
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin>>T; while(T--){
        int l, r; cin>>r>>l; cout<<solve(l,r)<<'\n';
    }
    return 0;
}
```

---

## 作者：nydry (赞：0)

# 题意
对于正整数 $a$ 和 $b$，定义 $f(a,b)$ 表示 $a$ 和 $b$ 在十进制表示下数字相同的有几位。题目保证调用时 $a$ 和 $b$ 的总位数相等。给出 $T$ 组询问，每次给定 $l$ 和 $r$，求 $f(l,x)+f(x,r)$ 的最小值，其中 $l\le x \le r$，保证 $l$ 和 $r$ 的总位数相等。

# 做法
从高位往低位考虑，假设当前在第 $i$ 高的位，且更高的位上 $l$ 和 $r$ 相等。分以下三种情况：

1. 这一位上 $l$ 和 $r$ 仍然相等。此时 $x$ 在这一位上只有一种选择，答案加二。

2. 这一位上 $l$ 和 $r$ 不相等，且差值至少为 $2$。此时 $x$ 可以在这一位上选择一个在中间的数，更低位可以随便选，所以不会再有答案了，结束。

3. 这一位上 $l$ 和 $r$ 不相等，且差值为 $1$。$x$ 可以选择取两个值中的一个。如果选择较小者，则在 $l$ 出现非 $9$ 的数字之前，都会有贡献。同理，选择较大者会在 $r$ 出现非 $0$ 的数字之前有贡献。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void solve(){
	string l,r;
	cin>>l>>r;
	int res=0;
	for(int i=0;i<l.length();i++){
		if(l[i]==r[i])res+=2;
		else if(l[i]+1==r[i]){
			int tmp=0x3f3f3f3f;
			int pos=i+1;
			while(pos<l.length()&&l[pos]=='9')pos++;
			tmp=min(tmp,pos-i);
			pos=i+1;
			while(pos<r.length()&&r[pos]=='0')pos++;
			tmp=min(tmp,pos-i);
			res+=tmp;
			break;
		}
		else{
			break;
		}
	}
	cout<<res<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tt;
	cin>>tt;
	while(tt--)solve();
	return 0;
}
```

---

## 作者：exCat (赞：0)

首先，因为只有两个数，所以如果一旦没有上下界的限制，就可以保证后面都不会有贡献。所以我们可以思考最早什么时候没有限制。从高到低位枚举分讨即可。

- 如果当前位 $r-l>1$，选择 $[l+1,r-1]$ 之间的任何数都可以不受限制，直接退出。
- 如果 $r=l$，没得选答案加二。
- 如果 $r=l+1$，这种情况是本题的难点。我们发现当且一定答案加一，我们可以选 $l$ 接下来保证下界或者选 $r$ 接下来保证上界，但是现在不知道选什么，所以先放着，往后看。
  - 如果接下来的位上 $r=0,l=9$ 我们发现不管上一位选什么这一位都必须压着边界，答案一定加一。但是我们还是不知道选什么，所以只能往后看。
  - 如果 $r\ne 0$ 或 $l\ne 9$，就一定可以前面顶上界当前选 $x<r$ 或前面顶下界当前选 $x>l$ 不受限制且不会对答案做贡献，直接退出。 

代码模拟上面的思路即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=20;
char l[N],r[N];
void solve()
{
	cin>>l>>r;
	int n=strlen(l),ans=0,flag=0;
	for(int i=0;i<n;i++)
	{
		int x=l[i]-'0',y=r[i]-'0';
		if(!flag)
		{
			if(y-x>1)break;
			if(x==y)ans+=2;
			else ans+=1,flag=1;
		}
		else
		{
			if(x==y)break;
			if(y!=0||x!=9)break;
			ans++;
		}
	} 
	cout<<ans<<'\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
 } 
```

---

## 作者：postpone (赞：0)

> 思路来自 [capps 老师](https://codeforces.com/profile/Capps)。

要找 $f(l, x) + f(x, r)$ 的最小值，不妨分为两部分处理。

- 首先是 $l$ 和 $r$ 的最长公共前缀，因为 $x$ 的选取要在两者之间，因此这部分不得不产生贡献。

- 然后是后面的部分，似乎 $x$ 可以乱取让后面的部分不产生任何贡献，但有一些特殊情况。

  - 例如 $l=11$，$r=12$，$x$ 的个位要么取 $1$ 要么取 $2$，都会产生 $1$ 个贡献。
 
  - 例如 $l=119999$，$r=120000$，在公共前缀之后，每一位仍然产生 $1$ 个贡献。
 
  - 但如果 $l=119934$，$r=120073$，最后两位就不会产生贡献。
 
  可以发现由于进位的原因，我们在取完最长公共前缀之后，还需要判定两个东西：最长公共前缀之后的一位，是不是只相差 $1$？如果是，紧接着有多少连续的位置满足 $l_i=9$ 和 $r_i=0$？

按照上面两步走，这道题就做出来了。

```cpp
void solve() {
    string l, r;
    cin >> l >> r;

    const int n = l.size();

    int i = 0, ans = 0;
    for (; i < n; i++) {
        if (l[i] == r[i]) {
            ans += 2;
        } else {
            break;
        }
    }

    if (i < n and r[i] - l[i] == 1) {
        ans++;
        i++;
        while (i < n and l[i] == '9' and r[i] == '0') {
            ans++;
            i++;
        }
    }
    cout << ans << "\n";
}
```

---

