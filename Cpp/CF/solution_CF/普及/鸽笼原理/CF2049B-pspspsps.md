# pspspsps

## 题目描述

# pspspsps


猫会被 $ pspspsps $ 所吸引，但 $ Evirir $ 作为一条有尊严的龙，只被具有奇怪特定要求的 $ pspspsps $ 所吸引......

给定一个长度为 $ n $ 的字符串 $ s = s_1s_2 \dots s_n $  ，由字符 $ p、s $ 和 $.$（点）组成，确定长度为 $ n $ 的排列 $ ^{∗} $ $ p $ 是否存在，使得对于所有整数 $ i $ （ $ 1 \le i \le n $ ）：

- 如果 $ s_i $ 是 $ p $，那么 $ [p_1， p_2， \dots， p_i] $ 形成一个排列（长度为 $ i $ ）;
- 如果 $ s_i $ 是 $ s $，那么 $ [p_i， p_{i+1}， \dots， p_{n}] $ 形成一个排列（长度为 $ n-i+1 $ ）;
- 如果 $ s_i $ 为 $ . $（点），则没有其他限制。

$ ^{∗} $ 长度为 $ n $ 的排列是一个数组，由 $ n $ 个从 $ 1 $ 到 $ n $ 的任意顺序的不同的整数组成。例如，$ [2,3,1,5,4] $ 是排列，但 $ [1,2,2] $ 不是排列（ $ 2 $ 在数组中出现两次），$ [1,3,4] $ 也不是排列（ $ n=3 $ 但数组中有 $ 4 $）。

## 说明/提示

对于第一个测试用例，一个有效的排列是 $ p = [3， 4， 1， 2] $ 。要求如下：

- $ s_1 = s $： $ [p_1， p_2， p_3， p_4] = [3， 4， 1， 2] $ 形成排列。
- $ s_2 = . $（点）：无其它要求。
- $ s_3 = s $： $ [p_3， p_4] = [1， 2] $ 形成排列。
- $ s_4 = p $： $ [p_1， p_2， p_3， p_4] = [3， 4， 1， 2] $ 形成排列。

对于第二个测试用例，可以证明没有满足所有要求的排列。

对于第三个测试用例，满足要求的一个排列是 $ p = [1， 2， 3， 4， 5] $ 。

## 样例 #1

### 输入

```
9
4
s.sp
6
pss..s
5
ppppp
2
sp
4
.sp.
8
psss....
1
.
8
pspspsps
20
....................```

### 输出

```
YES
NO
YES
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：jzy_CSPJ_AK (赞：3)

# 题解-CF2049B pspspsps #

# 题目 #

[link](https://www.luogu.com.cn/problem/CF2049B)

# 算法 #

无。此题是简单结论题。

# 思路 #

本题就是构造数组，使其满足题意。

（由题可知，如果 $u$ 点在 $0$ 或 $n - 1$ 上，那 $u$ 与 `.` 等价。）

设有 $x, y$ 二点，$x$ 上的字符为 `p`，$y$ 上的字符为 `s`，需要构造出的数组为 $f$。

那么设 $f_x  = a, f_y = b$。

$0 \sim x , y \sim n - 1$ 可以看做两个区间。

- 两区间不相交，怎么构造，$1 \sim a$ 与 $1 \sim b$ 总会有交集。
- 两区间相交，除开相交区间外，其余部分同上，一定会有相同的数。

又因为题目描述中，每个数字只能出现一次，所以区间不可以相交，就是在 $1 \sim n - 2$ 中间不可以有 `s` 和 `p` 同时存在。

暴力枚举即可。

# 代码 #

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int n, T;

void solve(){
    cin >> n >> s;
    bool flag = 0;
    for(int i = 0 ; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(s[i] == 's' && s[j] == 'p' && i != 0 && j != (n - 1)){
                flag = 1;
                break;
            }
        }
        if(flag)break;
    }
    if(flag)cout << "NO" << endl;
    else cout << "YES" << endl;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> T;
    while(T --){
        solve();
    }
    return 0;
}
```

---

## 作者：zhangzirui66 (赞：2)

简单结论题。

容易发现由于 `p` 会占有前方的 $1 \sim i$，若有 `s` 在前面而又不在最前面，会得到这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/n06bszxk.png)

其中红色区域是一个公用的排列，长度为 $len$，但两边都需要一个 $len + 1$ 的数字，不可行。`s` 在最前面就不受影响，因为左边没有不重叠部分。

反之亦然，其实也可以不判断，因为上面判断过了，赛时保险起见我判断了。

上面没有懂可以看这里：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
string s;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> s;
        bool flag = 0;
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++){
                if(s[i] == 'p' && s[j] == 's'){
                    if(!(i == n - 1 || j == 0)) flag = 1;
                }
                /*
                if(s[i] == 's' && s[j] == 'p'){
                    if(!(j == n - 1 || i == 0)) flag = 1;
                }这里可以不判断
                */
            }
        if(flag) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}
```

---

## 作者：_zhaosihan_qwq_ (赞：1)

# 题解：CF2049B pspspsps
## 思路：
得出结论非常简单。
- 我们将字符串 $s$ 中每个字符依次循环判断。
- 如果字母是 `p`，需要检查当前构建的排列前缀是否是一个长度为对应位置的合法排列。
- 根据简单的抽屉原理，如果中间字符串既含有 `s`，又含有 `p`，那么这个字符串一定不符合条件。
- 使用 dfs 模拟即可。

因代码部分过于简单，所以代码不给了。

---

## 作者：Sakura_Emilia (赞：1)

# Solution

结论题。经过简单的推理分析，可以得出只有某一类特定的字符串才满足条件。

由于字符 `s` 是从当前位置到最右端，而字符 `p` 是从当前位置到最左端。同样是排列，这注定了字符 `s` 和 `p` 不能发生交叉。当两种字符同时出现的时候，必然有其中某一种字符出现在原字符串的一端，并且这两种字符中，一定某一种只能出现过一次，就是在端点上的那一次。

最后再分类讨论一下即可。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define Ciallo main
#define int long long
#define el else
#define wl while
#define rt return
#define il inline
using namespace std;
const int N = 1e6 + 8;

int T, n, pCnt, sCnt;
string s;

il void solve() {
    cin >> n >> s;
    pCnt = sCnt = 0;
    for(char ch: s) {
        if(ch == 's')
            sCnt++;
        if(ch == 'p')
            pCnt++;
    }

    if(pCnt == 0 or sCnt == 0)
        yes
    el {
        if(pCnt != 1 and sCnt != 1)
            no
        el {
            if(pCnt == sCnt) {
                if(s[n - 1] != 'p' and s[0] != 's')
                    no
                el
                    yes
            } el {
                if(pCnt == 1) {
                    if(s[n - 1] != 'p')
                        no
                    el
                        yes
                } el {
                    if(s[0] != 's')
                        no
                    el
                        yes
                }
            };
        }
    }
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    wl(T--)
        solve();

    rt 0;
}
```

---

## 作者：GeYang (赞：1)

# 思路

依题意得，当首位为 `s` 或末位为 `p` 时，该字母是没有特殊性质的。

当中间（除去首尾两位）既有 `p` 又有 `s` 时，这些数需要小于两个排列长度中的更小者，所以这些数必须在两个排列的公共部分。

根据抽屉原理，至少有一个数不在两个排列的公共部分。

所以，中间部分既有 `p` 又有 `s` 时，一定无法构造符合要求的序列。

直接模拟即可。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
void solve()
{
	ll n;
	string s;
	bool ans=true;
	cin>>n>>s;
	for(int i=0;i<s.size();i++) if(s[i]=='p') for(int j=0;j<s.size();j++) if(s[j]=='s') if(i!=s.size()||j!=0) ans=false;
	if(ans) cout<<"YES\n";
	else cout<<"NO\n";
} 
int main()
{
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Aveiro7 (赞：0)

## 思路

这题是一个结论题。

首先我们设这个点为 $O$，那么当 $O$ 在 $0$ 或是 $n-1$ 显然没有其他限制，可以把它当成点来看待。

我们再来看除去头尾两端的时候：当中间 ``p`` 和 ``s`` 都有时，这些数就会小于两个排列的长度的较小者，所以这些数必须在两个排列的重叠部分。有由抽屉原理，必定会有数被挤出公共部分，所以无法构造。

代码就很简单了，只需判断除去头尾两端，中间 ``p`` 和 ``s`` 是否都有即可。

---

## 作者：All_Wrong_Answer (赞：0)

[原题传送门](chttps://codeforces.com/problemset/problem/2049/B)

## 结论题：

设 $n$ 为字符串 $s$ 的长度，$s$ 的下标从 $1$ 开始，当对于任何一个 $i$ 和 $j$ 有 $s_i=$ ```p```，$s_j=$ ```s``` 且 $1<i,j<n$ 时，即一个 ```p``` 和一个 ```s``` 所覆盖的区间重叠时且没有点在字符串的第一个或最后一个字符上时，无解，判断这些条件暴力枚举即可。

## 证明：

当满足上述无解条件时，图大概如下所示，根据抽屉原理，一定会有大于等于 $1$ 个数不在绿色区域，也就是重叠部分，这样很显然是不可取的。
![](https://cdn.luogu.com.cn/upload/image_hosting/jn51ph0p.png)

但是有一个点在字符串最后或第一个字符就是可以的，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/50v6wjvr.png)
很明显可以轻松构造出一组合法的方案。


## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int x;
char m[100005]; 
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>x;
		for(int j=1;j<=x;j++) cin>>m[j];
		int flag=0;
		for(int j=1;j<=x;j++){
			for(int k=1;k<=x;k++){
				if(m[j]=='p'&&m[k]=='s'&&j!=x&&k!=1) flag=1;
				if(m[j]=='s'&&m[k]=='p'&&j!=1&&k!=x) flag=1;
				//出现重叠，无解 
				if(flag==1){
				    break;
				} 
			}
			if(flag==1) break;
		}//暴力枚举 
		if(flag==1) cout<<"NO\n";
		else cout<<"YES\n";
		flag=0;
	}
	return 0;
}

```

[CF 上可过](https://codeforces.com/contest/2049/submission/299213015)

---

## 作者：WaterM (赞：0)

一道诈骗题。  
首先发现如果有存在 `p` 在 `s` 左边，那么一定无解。  
接下来就以淳朴的思路模拟。  
发现两个 `p` 中间夹的数是可以确定的。设两个 `p` 下标分别为 $x_1,x_2$，那么中间夹的数就是 $[x_1+1,x_2]$。于是将他们标记为【已确定位置】。  
同时再做一遍 `s`。此时如果发现某两个 `s` 中间夹的数被标记为【已确定位置】了，那么直接无解。  
其他情况输出有解即可。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 502;
	
	int n;
	char s[N];
	
	vector<int> x;
	int confirmed[N];
	
	void main() {
		scanf("%d%s", &n, s+1);
		//p在s左边，直接no
		for(int i = 1; i <= n; ++i) 
			for(int j = i+1; j <= n; ++j)
				if(s[i] == 'p' && s[j] == 's') {
					puts("NO");
					return;
				}
		
		s[1] = 's', s[n] = 'p';
		
		x.clear();
		memset(confirmed, 0, sizeof(confirmed));
		for(int i = 1; i <= n; ++i)
			if(s[i] == 'p') x.push_back(i);
		for(int i = 1; i < (int)x.size(); ++i) 
			for(int j = x[i-1] + 1; j <= x[i]; ++j)
				confirmed[j] = 1;
		
		x.clear();
		for(int i = n; i >= 1; --i)
			if(s[i] == 's') x.push_back(n-i+1);
		for(int i = 1; i < (int)x.size(); ++i)
			for(int j = x[i-1] + 1; j <= x[i]; ++j)
				if(confirmed[j]) {
					puts("NO");
					return;
				}
		puts("YES");
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	scanf("%d", &_);
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF2049B)

## 思路

显然首位为 `s` 或最后一位为 `p`，可以把它们看作 `.` 来处理。

对于中间的情况，如果 `p` 和 `s` 均出现了，则一定无法构造出合法方案。因为一个小于两个排列中长度更小的长度的一个数，它必须出现在两个排列当中，即两个排列的重叠部分。但由于两个排列重叠部分有限，一定至少有一个数会被挤到重叠部分以外。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 5e2 + 5;

int t, n, a[kMaxN], ans = 1;
string s;

void pr(bool pr) { cout << (pr ? "YES" : "NO") << '\n'; }

int main() {
  for (cin >> t; t; t--, ans = 1) {
    cin >> n >> s, s = ' ' + s;
    for (int i = 1; i <= n; i++) {
      if (s[i] == 'p') {
        for (int j = 1; j <= n; j++) {
          if (s[j] == 's') {
            ans &= (i == n || j == 1);
          }
        }
      }
    }
    pr(ans);
  }
  return 0;
}
```

---

