# 【MX-J2-T2】Turtle and Strings

## 题目背景

原题链接：<https://oier.team/problems/J2C>。

## 题目描述

给你一个仅由小写字母组成的字符串 $s$。

一个字符串序列 $t_1, t_2, \ldots, t_k$ 是合法的当且仅当：

- $s = t_1 + t_2 + \cdots + t_k$，此处 $+$ 为字符串拼接；
- $\forall 1 \le i \le k - 1, t_i \ne t_{i + 1}$。

求合法的字符串序列的长度的最大值。

## 说明/提示

#### 【样例解释】

在第一组数据中，一个合法且长度最大的字符串序列为 $[\texttt{a}, \texttt{b}, \texttt{c}]$。

在第二组数据中，一个合法且长度最大的字符串序列为 $[\texttt{a}, \texttt{abb}, \texttt{b}]$。

在第三组数据中，一个合法且长度最大的字符串序列为 $[\texttt{a}, \texttt{aa}, \texttt{a}, \texttt{aa}]$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | 分值 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $18$ | $9$ | $10^4$ | 无 | 无 |
| $2$ | $21$ | $50$ | $10^3$ | 无 | $1$ |
| $3$ | $12$ | $10^6$ | $10^6$ | $s_1 = s_2 = \cdots = s_n$ | 无 |
| $4$ | $23$ | $10^6$ | $10^6$ | **恰好**存在一个位置 $1 \le i \le n - 1$ 使得 $s_i \ne s_{i + 1}$ | 无 |
| $5$ | $26$ | $10^6$ | $10^6$ | 无 | $1, 2, 3, 4$ |

对于所有数据，满足 $1 \le T \le 10^5$，$1 \le n, \sum n \le 10^6$，$s$ 仅由小写字母组成。

## 样例 #1

### 输入

```
4
3
abc
5
aabbb
6
aaaaaa
10
pppqqppppq
```

### 输出

```
3
3
4
7
```

# 题解

## 作者：block_in_mc (赞：9)

## 题目大意

给定字符串 $s$，若字符串序列 $t$，满足 $s=t_1+t_2+\cdot\cdot\cdot+t_n$ 且 $t_i\not=t_{i+1}$，求 $t$ 长度的最大值。

## 解题思路

考虑贪心，尽量分为长度为 $1$ 的字符串，若不行再分为长度为 $2$ 的字符串。设目前正在考虑 $s_i$，上一个选择的字符串为 $l$：

- 若 $s_i\not=l$，则选择 $s_i$ 作为新的字符串；
- 否则，选择 $s_i$ 至 $s_{i+1}$ 作为新的字符串。

显然，若 $s_i=l$，选择 $s_i$ 至 $s_{i+1}$ 作为新的字符串总是合法，因为上一个选择的字符串长度为 $1$ 而 $s_i$ 至 $s_{i+1}$ 长度为 $2$，总不相等。

但是考虑字符串 `aaaaabaa`，切分为 `a/aa/a/ab/a/?`，这里剩下来的一个字符不能单独分，需要和前面的 `a` 合并。

再考虑字符串 `aaaaaaaa`，切分为 `a/aa/a/aa/a/?`，这里剩下来的 `a` 与前一个合并后为 `aa`，与前面重复，这里还可以将 `aa` 再与 `aa` 合并，变为 `a/aa/a/aaaa`。

但是这样是错误的。不难发现，`a/aa/a/aaaa` 可以再分为 `a/aa/a/aaa/a`，而类似的都可以这样做。综合考虑两种情况，发现最终答案就是考虑最后一个字符前的答案。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> s;
        s = " " + s;
        string last;
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (s.substr(i, 1) != last) last = s.substr(i, 1), cnt++;
            else if (i < n) last = s.substr(i, 2), cnt++, i++;
            else i++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
```

---

## 作者：xinxin2022 (赞：8)

我们考虑贪心策略，为了使截取段数的数量最大化，如果先后的字符一样，那么前后字符串的长度**必然是一个为二一个为一**，因为这样可以付出最少的代价满足前后字符串不相等的条件。

因此不难想出先预设答案为 $n$，如果上一次取到的是单个字符且与当前字符相等，那么将答案减一，再记录这次取到的字符串长度为二，反之则记录当前字符。

代码（抄袭题解代码可耻）：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
string s;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        cin>>s;
        int cnt=n;
        string last="";//记录上次选的字符串
        for(int j=0;j<s.size();j++){
            if(last.size()==1&&s[j]==last[0]) cnt--,j++,last=s[j-1]+s[j];
            //判断是否与上次相等
            else last=s[j];
            //不相等则记录当前字符
        }
        cout<<cnt<<'\n';
    }
    return 0;
}
```

---

## 作者：Louis_lxy (赞：5)

贪心小水题。

一个结论，如果上一个区间长度为 $1$ 且与当前遍历到的点相同，那么这个区间长度为 $2$，即当前这个数和下一个数。否则这个区间长度为 $1$，即当前这个数。这样每个区间的长度要么是 $1$，要么是 $2$，一定最优，证明如下。

显然对于两个相同的连续的字符，只有两种结果，要么分开，要么合并。而按照上述贪心做法，即优先分开。因为如果第一次操作选择合并，那么之后还有可能通过合并使得不同区间又有可能相同。因此优先分开更优，但是如果上一个区间本来就和上上个区间相同，那么并入上个区间肯定更优，不然就会使上个区间被迫并入上上个区间或者这个区间长度至少为 $2$，无论如何都造不成正贡献。

具体实现：我们可以用个变量 $f$ 表示上一个区间是否需要添加数。假设现在遍历到了 $s_i$，如果 $f=1$，那么 $lst\gets lst+s_i$（拼接字符串），否则 $lst\gets s_i$，其中 $lst$ 表示上个区间。更新 $f$ 就在新开区间的时候判断上一个区间是否长度为 $1$ 且与 $s_i$ 相等。注意如果最后 $f=1$，那么 $cnt\gets cnt-1$。

AC 记录：https://www.luogu.com.cn/record/170487086

---

## 作者：Getaway_Car_follower (赞：2)

考虑贪心，如果当前取出的字符串能满足条件直接取出并让答案 $+1$，否则就把当前字符串加入即将取出的部分。

为什么这是对的呢？

我们注意到，按照此方法取出的字符串的长度一定为 $1$ 或 $2$ 而且任何两个 $2$ 不会在一起。

那么假设我们取完了，下一个绝对能取长度为 $1$ 的就直接取，否则当前取出的字符串长度一定为 $1$，此时只能取长度为 $2$ 的字符串。


```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int n,ans;
string s,ss,sss;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		ss.clear();ans=0;sss.clear();
		cin>>n>>s;
		for(int i=0;i<n;i++){
			ss+=s[i];
			if(ss!=sss){
				ans++;
				sss=ss;
				ss.clear();
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Weekoder (赞：2)

### 思路

DP 较难维护，可以直接简单贪心。

要想要序列长度尽量长，元素长度就要尽量短。最短的情况是单个字符为一个元素。

可是这样会有问题。如果有两个相邻的字符相等，就不满足条件。而此时，最好的解决办法就是：将后面一个字符加入进来。比如当字符串为 $\texttt{aabc}$ 时，我们将第一个 $\texttt{a}$ 分离出来，此时字符串剩下 $\texttt{abc}$。可是下一个元素也是 $\texttt{a}$，于是我们加入 $\texttt{b}$，即字符串被分割为 $\texttt{a|ab|c}$。这样，字符串元素的大小均 $\le2$，就是最优的分割方式了。

代码采用 while 循环的方式进行模拟，如下：


```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int T, n;

string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T --) {
        cin >> n >> s;
        int ans = 0, now = 1;
        s = '#' + s;
        while (now <= n) {
            now ++, ans ++;
            if (s[now] == s[now - 1]) {
                if (now == n) break;
                ans ++, now += 2;
            }
        }
        cout << ans << "\n";
    }
    return 0;
} 
```

---

## 作者：Ryan_Adam (赞：1)

## P10841 【MX-J2-T2】Turtle and Strings 题解
### 算法
贪心
### 分析
题目仅仅要求 $t_i\neq t_{i+1}$，所以很容易能想到取出来的子串只能是一位或两位，这样就可以保证分割的 $k$ 最大且相邻子串不同。可以想到一种贪心策略：把字符串 $s$ 从头到尾遍历，能取一位就取一位，如果这一位和上次取的重复了就往后多取一位，这样肯定和上次不重复。

最后输出记录子串的 `vector` 的大小即可。 

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Ryan
{
    int T;
    vector<string> v;
    signed work()
    {
        cin>>T;
        while(T--)
        {
            v.clear();
            int n;
            string s;
            cin>>n>>s;
            string ans;
            ans.clear();
            for(int i=0;i<n;i++)
            {
                ans.push_back(s[i]);
                // cout<<i<<" "<<ans<<" "<<v[v.size]<<endl;
                if((v.empty())||(ans.size()&&ans!=v[v.size()-1]))
                {
                    v.push_back(ans);
                    ans.clear();
                }
            }
            // for(auto it:v)cout<<it<<" ";
            // cout<<endl;
            cout<<v.size()<<endl;
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Ryan::work();
}
```

---

## 作者：TemplateClass (赞：1)

最好的方法肯定是每个字符都划分成一个 $t _ i$，不难看出这一定是数量最多的方法。

但是由于题目要求相邻的 $t _ i$ 不能相同，而我们又知道长度不同的字符串一定不相同，所以我们可以先一个一个字符地分割，如果遇到和之前一样的字符了，就划分成 $2$ 个字符的 $t _ i$。

由此不难写出以下代码：

```cpp
int ans = 1;
for(int i = 1; i < s.size(); ++i) {
	if(s[i] == s[i - 1]) ++i;
	++ans;
}
```

但可惜这样做是错的，因为代码只要遇到相邻的两个相同的字符，就想着这次要划分为长度为 $2$ 的 $t _ i$，而可能之前的字符已经属于长度为 $2$ 的 $t _ i$ 了，所以这次其实并不需要划分 $2$ 个字符。

由此我们再写出以下代码，变量 $lastpos$ 记录了上一次划分了 $2$ 个字符的位置。

```cpp
int ans = 1, lastpos = -1;
for(int i = 1; i < s.size(); ++i) {
	if(s[i] == s[i - 1] && lastpos != i - 1) lastpos = ++i;
	++ans;
}

std::cout << ans << '\n';
```

可惜的是这样依然是错的，因为我们如果考虑字符串 $\tt abb$，那么根据上面代码的逻辑，它会输出 $3$，这是因为有时字符串并不能像我们希望的那样能剩有 $2$ 个字符来供我们划分。

所以如果结尾的 $2$ 个字符相同，那么必然要将这 $2$ 个字符划分到一起，不然如果单独地将倒数第 $2$ 个字符划分为一个 $t _ i$，那么最后一个字符便无法划分了。

于是我们再次写出如下代码：

```cpp
int ans = 1, lastpos = -1;
for(int i = 1; i < s.size(); ++i) {
	if((s[i] == s[i - 1] && lastpos != i - 1) || (i == s.size() - 2 && s[s.size() - 1] == s[s.size() - 2])) lastpos = ++i;
	++ans;
}
```

如果你这样交上去的话仍然会 WA 几个点，原因是我们考虑字符串 $\tt aa$，按照上面代码的逻辑，它会输出 $2$，这是因为我们已经默认 $|t _ 1| = 1$，这并不总是成立的。虽然容易证明的是当 $n \ge 3$ 的时候并不会对结果产生影响。但是当 $n = 2$，且 $s$ 的 $2$ 个字符又恰好相同时，它会出错。

所以我们再增加一个特判即可。

```cpp
void solve(){
	int n; std::string s;
	std::cin >> n >> s;
	
	int ans = 1, lastpos = -1;
	for(int i = 1; i < s.size(); ++i) {
		if((s[i] == s[i - 1] && lastpos != i - 1) || (i == s.size() - 2 && s[s.size() - 1] == s[s.size() - 2])) ++i, lastpos = i;
		++ans;
	}
	
	if(n == 2 && s[0] == s[1]) ans = 1;
	std::cout << ans << '\n';
}
```

---

## 作者：Eason_cyx (赞：0)

考虑将一个字符串分成几个子字符串，每个子串中所有字母都相等。

例如：`qqqqhhhheeeeeeeejjj`，可以分成 `qqqq`，`hhhh`，`eeeeeeee`，`jjj` 四个子串，然后分开处理。

学习样例解释，如果有三个一样的字符，如 `aaa`，可以分成两段 `a` 和 `aa`，因此段数增加 $2$。

那么剩下的部分？

如果剩下一个字符，那么可以自成一段。

如果剩下两个字符，显然不能自成一段（留给读者思考，可以发在评论区），那么此时可以一个字符自成一段，另一个字符和下一个子段的第一个字符成一段，这样是最优的。**注意：如果这个子段是最后一段，那么只能将这多出来的两个字符的前面一个放入前面一小段中，此时段数 $+1$。**

时间复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		string s; cin >> s;
		int ans = 0;
		s = ' ' + s;
		int stpos = 1,edpos = 1;
		bool flag = false;
		while(stpos != n+1) {
			while(s[edpos] == s[stpos]) edpos++;
			edpos--;
			int siz = edpos - stpos + 1;
			if(flag) {
				siz--;
				flag = false;
			}
			ans += siz / 3 * 2;
			int yu = siz % 3;
			if(yu == 1) ans++;
			if(yu == 2) {
				if(edpos == n) ans++;
				else {
					ans += 2;
					flag = true;
				}
			}
			stpos = edpos+1; edpos = stpos;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：cfkk (赞：0)

思路：容易想到，要想答案尽可能大，每个字符串的长度要尽可能为一。易证当有两个相邻字符相同的时候，第二个字符串的长度一定为 $2$。

以 $\tt{pppqqppppq}$ 为例，最好的分解方式一定是 $[\tt{p},\tt{pp},\tt{q},\tt{qp},\tt{p},\tt{pp},\tt{q}]$

代码如下：

```cpp
signed main()
{
    int T=read();
    while(T--)
    {
        int n=read();
        string s;
        cin>>s;
        int cnt=0;
        string last;
        for(int i=0;i<n;i++)
        {
            string str;
            str+=s[i];
            if(str==last)last=s[i]+s[i+1],i++;
            else last=s[i];
            if(i>=n)break;
            cnt++;
        }
        print(cnt);pc(1);
    }
    return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

简单贪心。

首先题意如果没看懂的话，翻译一下：

将一个字符串 $s$ 拆成 $k$ 个字符串 $t_1,t_2,\cdots,t_k$，并且 $t_i \not= t_{i+1}$。

显然，字符串的长度最多为 $2$，考虑如下方案：

假设当前截取到了 $s_i$，如果其前面已经截取下的字符串长度为 $2$ 或者 $s_i \not=s_{i-1}$ 的话，则将 $s$ 截取下来。

否则，将 $s_i$ 和 $s_i+1$ 截取下来。

贪心简单证明：

如果该次能截取长度为 $1$ 的话：

- 如果下一次也能截取长度为 $1$ 显然该情况最优。

- 如果下一次截取长度为 $2$ 的话，那么本次截取长度为 $2$，下次截取长度为 $1$ （会对后面截取长度为 $1$ 产生限制）的显然不会更优。

至于不能截取为 $1$，显然截取长度为 $2$ 是最优解。

放代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		char lst=s[0];
		bool two=false;
		int ans=1;
		for(int i=1;i<n;i++){
			if(two){
				lst=s[i];
				two=false;
				ans++;
			}
			else if(lst==s[i]){
				two=true;
				if(i!=n-1){
					
				i++;
				ans++;
				}
			}
			else{
				lst=s[i];
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

