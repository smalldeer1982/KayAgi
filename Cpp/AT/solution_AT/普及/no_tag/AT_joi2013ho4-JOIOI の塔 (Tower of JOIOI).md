# JOIOI の塔 (Tower of JOIOI)

## 题目描述

JOIOI 塔是一种单人游戏。

这个游戏要用到一些写有 `J`, `O`, `I` 中任一文字的圆盘。这些圆盘的直径互不相同。游戏开始时，这些圆盘按照直径大的在下面的规则堆叠。你需要用这些圆盘做尽量多的迷你 JOIOI 塔。迷你 JOIOI 塔由 $3$ 个圆盘构成，从直径较小的圆盘开始分别为 `J`, `O`, `I` 或分别为 `I`, `O`, `I` 。不过，每个圆盘最多只能使用一次。

给出长为 $N$ 的字符串 $S$ ，表示直径从小到大的圆盘上的文字。请编写程序求出使用这些圆盘能够做出的迷你 JOIOI 塔个数的最大值。

## 说明/提示

对于所有数据，$1\leq N \leq 10^6$。

| 子任务 |     分值      |   $N\le$    |
| :----: | :-----------: | :---------: |
|  $1$   |     $10$      | $N \leq 15$ |
|  $2$   |     $20$      | $N \leq 50$ |
|  $3$   | $N \leq 3000$ | $N\leq3000$ |
|  $4$   |     $50$      | $N\leq10^6$ |

## 样例 #1

### 输入

```
6
JOIIOI```

### 输出

```
2```

## 样例 #2

### 输入

```
5
JOIOI```

### 输出

```
1```

## 样例 #3

### 输入

```
6
JOIOII```

### 输出

```
2```

## 样例 #4

### 输入

```
15
JJOIIOOJOJIOIIO```

### 输出

```
4```

# 题解

## 作者：Yizhixiaoyun (赞：2)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/16856084.html)

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2013ho4)

洛谷上竟然还没有题解...

## 题目分析

简单贪心题。

考虑倒过来寻找。显然，如果一个 ```J``` 想要配成一座塔，那么必须要找一个 ```OI```。```O``` 更简单，就是直接找到一个 ```I``` 放上去就行。

最难的是 ```I```，它既可以选择单开一座塔，也可以选择放在原来的塔上面组成 ```IOI```。然后贪心思考，发现如果塔底的数量少于需求的数量，那么单开一座塔更优，否则放原来的塔更优。

然后就是二分答案，二分所需的塔底数量，跑一遍模拟。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=1e6+5;
int n;
int ans;
int l,r;
string s;
inline void init(){
	cin>>n;cin>>s;s=" "+s;
	l=1;r=n;
}
bool check(int x){
	int res=0,cnt1=0,cnt2=0;
	for(register int i=n;i>=1;--i){
		if(res==x) return true;
		if(s[i]=='J'){
			if(cnt1!=0){
				cnt1--;res++;
			}
		}
		else if(s[i]=='O'){
			if(cnt2!=0){
				cnt2--;cnt1++;
			}
		}
		else{
			if(cnt1+cnt2+res>=x&&cnt1!=0){
				cnt1--;res++;
			}
			else cnt2++;
		}
	}
	if(res==x) return true;
	return false;
}
signed main(){
	init();
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)==true){
			l=mid+1;ans=mid;
		}
		else r=mid-1;
	}
	cout<<ans<<endl;
}
```

---

## 作者：喵仔牛奶 (赞：2)

# Description

给定一个由 `J`、`O`、`I` 组成的字符串，求最多能拆分成多少 `JOI` 或 `IOI`。

对于所有数据，$1\leq \vert S\vert\leq 10^6$。

# Solution

先处理出 $\text{pre}_i$ 为前缀 `J` 和 `I` 的数量，即能组成多少个头部。

然后倒着做，维护当前拼出的 `I`、`OI` 和最终成品的数量。遇到 `J`、`O` 就模拟拼接，遇到 `I` 判断当前的 $\text{pre}_i$ 是否小于等于  `I`、`OI` 的总数量，若成立就拼成 `IOI`，否则作为 `I`。

判断这个是因为 `I` 可以作为最后的 `I` 也可以作为开头的 `I`。若大于等于前缀 `J`、`I` 数量则作为最后的 `I` 数量够用，无需继续拼接了。

时间复杂度 $\mathcal{O}(n)$。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Milkcat {
    const int N = 2e7 + 5;
    int n, ow, w, tot, pre[N]; char s[N];
	int main() {
		cin >> n >> (s + 1);
		for (int i = 1; i <= n; i ++)
			pre[i] = pre[i - 1] + (s[i] == 'J' || s[i] == 'I');
		for (int i = n; i >= 1; i --) {
    		if (s[i] == 'J' && ow) ow --, tot ++;
    		if (s[i] == 'O' && w) w --, ow ++;
			if (s[i] == 'I') {
				if (ow + w >= pre[i] && ow) ow --, tot ++;
				else w ++;
			} 
		}
		cout << tot << '\n';
        return 0;
    }
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}

/*
15
NNOWWOONONWOWWO
*/
```

---

