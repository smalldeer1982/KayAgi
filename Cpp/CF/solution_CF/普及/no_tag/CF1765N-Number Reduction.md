# Number Reduction

## 题目描述

You are given a positive integer $ x $ .

You can apply the following operation to the number: remove one occurrence of any digit in such a way that the resulting number does not contain any leading zeroes and is still a positive integer. For example, $ 10142 $ can be converted to $ 1142 $ , $ 1042 $ , $ 1012 $ or $ 1014 $ (note that $ 0142 $ is not a valid outcome); $ 10 $ can be converted to $ 1 $ (but not to $ 0 $ since it is not positive).

Your task is to find the minimum positive integer that you can obtain from $ x $ if you can apply the aforementioned operation exactly $ k $ times.

## 样例 #1

### 输入

```
5
10000
4
1337
0
987654321
6
66837494128
5
7808652
3```

### 输出

```
1
1337
321
344128
7052```

# 题解

## 作者：灵茶山艾府 (赞：14)

本题属于【字典序最小子序列问题】，可以用单调栈解决，时间复杂度严格 $\mathcal{O}(n)$。

先看看**允许有前导零**要怎么做：直接遍历字符串，用单调栈维护，只要当前字符小于栈顶，就弹出栈顶，同时把 $k$ 减一。最后栈底到栈顶是单调非降的，把栈顶的 $k$ 个元素弹出。

回到原题，**不允许有前导零**，我们可以在前 $k+1$ 个字符中找到第一个最小的非 $0$ 字符，设其为下标为 $j$，那么肯定要把下标小于 $j$ 的字符都删掉。然后从 $j+1$ 开始按照上面的做法跑单调栈即可。

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, k int
	var s []byte
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &s, &k)
		j := 0
		for i, b := range s[:k+1] {
			if b > '0' && b < s[j] { // 最小非 0 字符（且下标最小）
				j = i
			}
		}
		k -= j // 把 j 左边的都删掉
		st := s[j : j+1] // 保留 s[j]
		for _, b := range s[j+1:] { // j 右边的正常跑单调栈即可
			for len(st) > 1 && k > 0 && b < st[len(st)-1] {
				st = st[:len(st)-1]
				k--
			}
			st = append(st, b)
		}
		st = st[:len(st)-k] // 还剩下操作次数，就去掉后面的（因为栈顶元素大）
		Fprintf(out, "%s\n", st)
	}
}
```


---

## 作者：Patrickpanpan (赞：3)

#### 1.暴力：枚举每个位置的数，逐个比较。
#### 2.错误贪心策略：每次删去数串最大的一个数字。
#### 3.贪心策略：

部分最优解：每次枚举每一位数，每次得到的都是最小值。

全局最优解：每次找到最小值，则最终答案也为最小值。


证明（数学归纳法）：

1.当 $k=1$ ，做法与暴力相同，正确；

2.当 $k>1$ ，假设 $k=m$ 正确，对于 $k=m+1$ ，再删掉 $s$ 中的一个字符后最小的一个（贪心策略），正确。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,smin,stemp;
int n;
int main()
{
	int T;
	cin>>T;
	for(int apple=1;apple<=T;apple++)
	{
		cin>>s>>n;
		for(int i=1;i<=n;i++)
		{
			smin=s;
			stemp=s;
			for(int j=0;j<s.size();j++)
			{
				stemp=s;
				stemp.erase(j,1);
				smin=min(smin,stemp);
			}
			s=smin;
		}
		while(s[0]=='0' && s.size()>1)s.erase(0,1);
		cout<<s<<endl;
	}
	return 0;
}
/*
举个栗子：
s=781864,k=3
第一遍循环：k=1,stemp=81864,71864,78864,78164,78184,78186
选出smin=71964,用smin替换s,s=71964

第二遍循环：k=2,stemp=1964,7164,7164,7194,7196
选出smin=1964,用smin替换s,s=1964

第三遍循环：k=2,stemp=964,164,194,196
选出smin=164,答案即为164
*/
```

---

## 作者：Xuan_0608 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1765N)（洛谷）
### [题目传送门](https://codeforces.com/problemset/problem/1765/N)（CodeForces）
# 分析
本题很显然是贪心，这里有两种策略：  
- （错误）每次删掉最大的那一个数字；
- （正确）每次枚举删掉每一位数的情况，取最小值，最后答案一定也为最小值。

证明：  
设 $\operatorname{f}(k, x)$ 为 $k$ 次操作后 $x$ 的最小值，则：
- 如果 $k = 0$，那么 $\operatorname{f}(k, x) = x$，正确。
- 如果 $k > 0$，那么 $\operatorname{f}(k, x) = \operatorname{f}(k - 1, s)$（其中 $s$ 为 $x$ 删掉 $x$ 的其中一个数字之后的最小值），正确。

那么现在此题就很简单了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, k, len;
string x, mins, t;
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> x >> k;
		while(k--)
		{
			len = x.size();
			mins = x;
			for(int i = 0; i < len; i++)
			{
				t = x;
				t.erase(i, 1);
				if(t[0] != '0') mins = min(mins, t);
			}
			x = mins;
		}
		cout << x + '\n'; 
	}
	return 0;
}
```

---

## 作者：yehongxin (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1765N)
### [原题传送门](https://codeforces.com/problemset/problem/1765/N)
## 题目大意
给出一个数字串，可以删去 $k$ 个数，求删去数字后的最小数。
## 解题思路
贪心，枚举每一位，求删去每一位后的最小值，反复删去 $k$ 个数字，就是所求的答案。

比如说当 $s=54391$ 时 $k=3$ 时，第一次删去 $9$ 是最小的，剩下 $5431$，第二次删去 $5$ 是最小的，剩下 $431$，最后一次删去 $4$，所的答案为 $31$。
## 以下核心代码

```cpp
for(int i=1;i<=n;i++)
{
    smin=s;//初始化把最小变成s
    stemp=s;
    for(int j=0;j<s.size();j++)
    {
        stemp=s;
        stemp.erase(j,1);//删去这一位
        smin=min(smin,stemp);//求最小值
    }
    s=smin;//更新最小值
}
```

---

## 作者：czh___ (赞：1)

因为 $x$ 的位数比较大，所以这里我们用字符串 $s$ 来存储 $x$ 的每一位。用 $ans$ 来表示经过 $k$ 次删除后的 $x$。我们已知 $k$，所以经过 $k$ 次删除后，$ans$  的位数为 $s$ 的长度减 $k$。要让 $ans$ 尽量小，我们可以选择尽量小的数字组成 $ans$ 前面几位。比如在选择 $ans$ 第一位的时候，我们可以先尝试能不能让 $1$   成为 $ans$ 的首位，如果不能就尝试 $2$，以此类推，在选择 $ans$ 后面的位数时，则先尝试能不能让 $0$ 成为首位，如果不能再一次试试 $1$ 到 $9$。如果可以找到这个数字，那我们就对 $x$ 进行删除操作，直到删到选择数字的最小下标即可。具体可以再看看注释。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int k;
		int idx[10]={0};
		vector<int>a[10];
		string ans;
		cin>>s>>k;
		for(int i=0;i<s.size();i++)
			a[s[i] - '0'].push_back(i);//存每位数的下标
		int l=0;//l为删除的起点
		int flag=0;
		while(k){
			for(int i=0;i<=9;i++){
				if(a[i].size()>idx[i]&&(l>0||i!=0)){
					if(a[i][idx[i]]<=l+k){
						k=k-(a[i][idx[i]]-l);
						l=a[i][idx[i]]+1;
						idx[i]++;
						ans+=char(i+'0');
						for(int x=0;x<=9;x++)//更新最小下标
							if(a[x].size()>idx[x]){
								while(a[x][idx[x]]<l){								
									idx[x]++;
									if(a[x].size()==idx[x])
										break;								
								}
							}
						break;
					}
				}
			}
			if(k+l>=s.size()){//删除的起点+还可以删除的次数大于了x的位数就可以不用删除了			
				flag=1;
				break;
			}
		}
		if(flag)//ans就是答案
			cout<<ans<<"\n";
		else{//ans是答案的前几位
			cout<<ans;
			for(int i=l;i<s.size();i++)
				cout<<s[i];
			cout<<"\n";
		}
	}
	return 0;
}
```

[改编于](https://blog.csdn.net/xingrin/article/details/128889326?ops_request_misc=&request_id=&biz_id=102&utm_term=Number%20Reduction&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-128889326.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

## 作者：_X_Z_N_ (赞：1)

双倍经验：[类似题目](https://www.luogu.com.cn/problem/P1106)

注意：代码相似，但是有些细节不一样。

## [本题传送门](https://www.luogu.com.cn/problem/CF1765N)

## 贪心思路：

每次从前往后扫，保证扫过的是不下降的，直到扫到第一个下降的，记为 $j$ 此时删除 $j$。

需要注意的是，要保证如果 $j$ 是当前字符串的第一个，那 $j$ 的后面不能是 $0$，否则会出现前导 $0$。

这一点在上面提到的类似题目中是允许的，但在本题中是不允许的。（~~重点敲黑板~~）

## 贪心证明:

我们想使得到的数尽可能的小，就需要尽可能的删**既靠前数字又大的**，如果前面 $n$ 个数是**不下降的**，就没必要删去。

如果删去这 $n$ 中的任意一个数（比如第 $i$ 位的数）我们直到第 $i+1$ 位的数肯定大于等于 $i$ 位的数，所以删去后得到的新数肯定是不优的。

按照这个想法，我们就要找到第一个违背了不下降的那个数 $j$ 并删去它。

## 代码1：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;//多测是真可爱(恶心),我讨厌多测
string a;//存数的
int k;//删k个
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>a;
        cin>>k;
        for(int i=1;i<=k;i++)//删k个数
        {
            int j=0;
            for(j=0;;j++)//从前往后扫,一直扫到满足if为止
			{
				if(a[j]>a[j+1] && (a[j+1]!='0' || j!=0))//前面a[j]>a[j+1]判断是否违背了不下降,后面判断前导0,要么满足后面不是0,要么不在第一位
				{
					break;//满足条件，跳出
				}
			}
            a.erase(j,1);//也是看了dalao的才学会,可以用来删a字符串的第j个字符
        }
        cout<<a<<endl;//输出,虽然大家都懂但是我话多
    }
    return 0;
}
```
以上代码的最坏的时间复杂度是 $O(nk)$，很明显会 $TLE$，所以我们需要对它进行优化。

## 优化思路：
在我们删除了第 $j$ 个数后，下一次循环中第 $1$ 到第 $j-1$ 的数我们还是要再扫一遍，但是我们在已经知道了这 $j-1$ 个数是满足不下降的，所以我们下一次遍历可以直接从 $j-1$ 开始。（注意不是 $j$）

我们再开一个变量 $p$ 用来储存下一次遍历开始的位置，$p$ 值的更新应该在每一次删除第 $j$ 个数后更新为 $j-1$，初始化为 $0$。

## 代码2:


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;//多测是真可爱(恶心),我讨厌多测
string a;//存数的
int k;//删k个
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>a;
        cin>>k;
        int p=0;//每次从p开始遍历 
        for(int i=1;i<=k;i++)//删k个数
        {
            int j=0;
            for(j=p;;j++)//从前往后扫,一直扫到满足if为止
			{
				if(a[j]>a[j+1] && (a[j+1]!='0' || j!=0))//前面a[j]>a[j+1]判断是否违背了不下降,后面判断前导0,要么满足后面不是0,要么不在第一位
				{
					break;//满足条件,跳出
				}
			}
            a.erase(j,1);//也是看了dalao的才学会,可以用来删a字符串的第j个字符
            p=j-1;//更新p的值 
        }
        cout<<a<<endl;//输出,虽然大家都懂但是我话多
    }
    return 0;
}
```

优化后的时间复杂度是 $O(n+k)$，可以接受。

不是 $O(n)$ 因为每个 $j-1$ 都遍历了两遍。

~~管理大大给过吧求求了。~~

---

## 作者：cloud2764scallop_eve (赞：1)

## 题意
给定一个正整数 $x$，可以对其进行 $k$ 次操作，每次操作可以删去这个数的任意一个数字，需要保证没有前导零。

求经过 $k$ 次操作后可以得出的最小的数。

## 思路
鉴于数据为 $n \le 10^{500000}$，选择字符串存储。再定义一个字符串，用于存储最后的答案。

这里介绍一个函数：`min_element()`。  
> Return smallest element in range
Returns an iterator pointing to the element with the smallest value in the range .  
The comparisons are performed using either for the first version, or for the second; An element is the smallest if no other element compares less than it. If more than one element fulfills this condition, the iterator returned points to the first of such elements.
——[cpluscplus.com](https://cplusplus.com/reference/algorithm/min_element/)

简单来说，就是用于求范围内的最小元素。

我们可以用 `min_element` 求出字符串中最小的元素，再用两个指针 $l$ 和 $r$ 做枚举。对于 $l \le i \le r$ 的 $s_i$，用 $m$ 记录最小值（这里的 $m$ 不能和 `min_element` 的值相等，否则意味着 $m$ 已经是最小值，没有必要枚举）。当 $m$ 小于当前的 $s_i$ 且 $s_i$ 不是前导零时，更新 $m$ 为 $s_i$，$l$ 为 $i + 1$。

在枚举结束后，用 $ans$ 记录 $m$ 的值，同时更新 $r$ 的值（加一），直到 $k$ 次操作结束。

最后输出 $ans$ 即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
void solve() {
	string s;
	int k;
	cin >> s >> k;
	int l = 0, r = k;
	k = s.size() - k;
	string ans = "";
	char ch = *min_element(s.begin(), s.end());
	while (k--) {
		char m = '9';
		for (int i = l; i <= r && m != ch; i++) {
			if (m > s[i] && (!ans.empty() || s[i] != '0'))
				m = s[i], l = i + 1;
		}
		ans += m, r++;
	}
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
//why CE? not C++11 but C11
```

## 写在后面
最后的注释是什么意思呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/2sl7x0u4.png)


真是一个~~笑死人~~的故事。

---

## 作者：Alex_Wei (赞：1)

将 $x$ 当成字符串，从前往后贪心。设当前考虑到第 $i$ 位，剩余可以删去的位数为 $k$。当 $cur + k > n$ 时，剩下来所有位都可以删去，直接退出。否则，根据贪心原则，我们找到最小的在 $[i, i + k - 1]$ 位出现过的数码，跳到它的下一次出现位置 $p$，将位置 $i\sim p - 1$ 上的数码全部删掉。维护 $suc_{i, j}$ 表示从 $i$ 开始 $j$ 的第一次出现位置即可。注意特判第一次不能跳数码 $0$。时间复杂度 $\mathcal{O}(n)$，有 $10$ 倍常数。[代码](https://codeforces.com/contest/1765/submission/185238828)。

---

