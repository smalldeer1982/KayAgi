# King of Thieves

## 题目描述

In this problem you will meet the simplified model of game King of Thieves.

In a new ZeptoLab game called "King of Thieves" your aim is to reach a chest with gold by controlling your character, avoiding traps and obstacles on your way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526A/527857f6180736c7bf1bfc93b9cfb6aa3a26550b.png)An interesting feature of the game is that you can design your own levels that will be available to other players. Let's consider the following simple design of a level.

A dungeon consists of $ n $ segments located at a same vertical level, each segment is either a platform that character can stand on, or a pit with a trap that makes player lose if he falls into it. All segments have the same length, platforms on the scheme of the level are represented as '\*' and pits are represented as '.'.

One of things that affects speedrun characteristics of the level is a possibility to perform a series of consecutive jumps of the same length. More formally, when the character is on the platform number $ i_{1} $ , he can make a sequence of jumps through the platforms $ i_{1}&lt;i_{2}&lt;...&lt;i_{k} $ , if $ i_{2}-i_{1}=i_{3}-i_{2}=...=i_{k}-i_{k-1} $ . Of course, all segments $ i_{1},i_{2},...\ i_{k} $ should be exactly the platforms, not pits.

Let's call a level to be good if you can perform a sequence of four jumps of the same length or in the other words there must be a sequence $ i_{1},i_{2},...,i_{5} $ , consisting of five platforms so that the intervals between consecutive platforms are of the same length. Given the scheme of the level, check if it is good.

## 说明/提示

In the first sample test you may perform a sequence of jumps through platforms $ 2,5,8,11,14 $ .

## 样例 #1

### 输入

```
16
.**.*..*.***.**.
```

### 输出

```
yes```

## 样例 #2

### 输入

```
11
.*.*...*.*.
```

### 输出

```
no```

# 题解

## 作者：L_zaa_L (赞：5)

## 分析

[直通题目](https://www.luogu.com.cn/problem/CF526A#submit)

最开始考虑了一下 $O(n)$,等到后来才发现 $1 \le n \le 100$，这么说，$O(n^2)$ 不会超时（连 $O(n^4)$）。
暴力就可以直接解决这道题。

我们只用枚举两个：一个是起点，也就是从哪里开始跳（起点也要是```*```），另一个就是跳的距离。然后再判断 $c_i \quad c_{i+j} \quad c_{i+j*2} \quad c_{i+j*3} \quad c_{i+j*4}$ 是不是```*```即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[105];
int n;
int main(){
	cin>>n;
	cin>>c;
	for(int i=0;i<n;i++){//开始跳跃的起点
		for(int j=1;j<=n;j++){//枚举每次跳跃的距离
			if(c[i]=='*'&&c[i+j]=='*'&&c[i+j*2]=='*'&&c[i+j*3]=='*'&&c[i+j*4]=='*'){//判断能不能进行一次完美的跳跃，也就是说，脚下也必须是*，是就输出yes，否则没有就输出no
				cout<<"yes";
				return 0; 
			}
		}
		
	}
	cout<<"no";
	return 0;
}
```


---

## 作者：CQ_Bab (赞：1)

# 思路
乍一看这道题好像很难可是，当我看到 $n\le100$ 时我仿佛又看到了暴力的曙光，于是就开始写 $O(n ^ 2)$ 做法了。其实这道题就只用去枚举起点和跳跃长度再看看从 $s_i$ （初始 $i=q$ 每次 $i$ 加上 $l$）开始有几个连续的平台就行了，如果连续个数等于 $5$ 输出是,如果枚举完了也没有输出的话就直接输出否 ,那代码不就出来了吗？
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[100100];
int main(){
	cin>>n>>s+1;
	for(int l=1;l<=n;l++) { // 枚举跳跃长度
		for(int q=1;q<=n;q++){ // 枚举起点 
			int i=q,cnt=false;
			while(i<=q+4*l){ // 去看路径上的点 
				if(s[i]=='*') cnt++;
				i+=l;
			}
			if(cnt==5) {  // 如果全部点都为平台输出Yes 
				puts("yes");
				return false;
			}
		} 
	} 
	puts("no");
	return false;
}
```


---

## 作者：Hooch (赞：1)

### 题目大意

给定一段路，其中有陷阱和平台，如果踩到陷阱就算输。在平台上可以跳跃到另一个向前的平台。如果从平台 $i$ 连续跳四次，且每次跳跃长度相等，则称为这是一次好的跳跃。

现在给定一个长度为 $n$ 的字符串 $s$，其中 `.` 表示陷阱，`*` 表示平台，输出 $s$ 有无可能出现一次好的跳跃。

### 思路

这一道题一看，如果要在 $n$ 大的时候做，必须用高级数据结构维护，可是一看 $n\le 100$。。。

那么我们可以先枚举每次跳跃的长度，在枚举起点，之后求出在起点上最多能跳几次，如果能跳四次及以上，直接输出 `yes`。时间复杂度 $O(n^3)$。

### 代码

```cpp
#include <bits/stdc++.h>
int n; char s[105];
signed main(void) {
	cin >> n >> s + 1;
	for (int i = 1; i <= n; ++i) {//枚举跳跃长度 
		for (int j = 1; j <= n; ++j) {// 枚举起点
			if (s[j] == '.') continue; //判断起点是否为平台
			int k, cnt = 0;
			for (k = j + i; k <= n; k += i) if (s[k] == '.') break; else ++cnt;
			if (cnt >= 4) return puts("yes"), 0;
		}
	}
	puts("no");
}
```

---

## 作者：CSP_Sept (赞：1)

### Description

给定一个长度为 $n(1\le n\le100)$ 的仅含 `.` 和 `*` 的字符串 $s$，求出是否存在五个数 $f_1,f_2,f_3,f_4,f_5$，满足以下条件：

- $s$ 中的第 $f_{1}\sim f_{5}$ 个字符都是 `*`（字符下标从 $1$ 开始）。
- $\{f_5\}$ 严格**递增**，且对于 $2\le i\le 5$，有 $f_i-f_{i-1}=k$（$k$ 是定值）。

### Solution

- 中文版

注意到 $n$ 最大是 $100$，很小，~~而且是 A 题~~，于是考虑暴力。

枚举 $f_1$，当发现 $f_1$ 满足条件后枚举 $k$。

注意到此时 $k$ 只要枚举到 $\frac14(n-f_1)$ 即可。

每次计算出 $f_2\sim f_5$ 再判断即可。

- [English Version 1 (Offical)](https://www.luogu.com.cn/paste/psml95xe)
- [English Version 2](https://www.luogu.com.cn/paste/clqnbdlb)
- [日本語版](https://www.luogu.com.cn/paste/5k8zsbpe)

### Code

```cpp
#include <cstdio>

using namespace std;
int n;
char s[110];
int main(){
	scanf("%d%s", &n, s);
	for(int i = 0 ; i < n ; i++){
		if(s[i] == '*'){
			int res = n - i - 1;
			for(int j = 1 ; j <= n / 4 ; j++){
				int t = i;
				bool f = 1;
				for(int k = 0 ; k < 4 ; k++){
					t += j;
					if(s[t] != '*') f = 0;
				}
				if(f){
					puts("yes");
					return 0;
				}
			}
		}
	}
	puts("no");
	return 0;
}
```

---

## 作者：szhqwq (赞：0)

## 分析

此题 $1 \le n \le 100$，可 $O(n^2)$ 求解。

第一层循环枚举起跳点，第二层循环枚举跳跃长度，如果有连续 $5$ 个（注意题目说的是跳四次）差相同的 $s_i$ 均为 `*`，那么成立，否则不成立。

## AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int n;
string s;

signed main() {
	cin >> n >> s;
	for (int i = 0; i < n; i ++ ) 
		for (int j = 1; j <= n; j ++ ) 
			if (s[i] == '*' && s[i + j] == '*' && s[i + j + j] == '*' && s[i + j + j + j] == '*' && s[i + 4 * j] == '*') {
				puts("yes");
				return 0;
			}
	puts("no");
	return 0;
}
```

---

