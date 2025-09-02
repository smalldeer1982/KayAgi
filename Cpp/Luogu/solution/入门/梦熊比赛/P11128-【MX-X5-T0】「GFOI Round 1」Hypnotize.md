# 【MX-X5-T0】「GFOI Round 1」Hypnotize

## 题目背景

原题链接：<https://oier.team/problems/X5A>。

---

> [$\small\text{The absolute catastrophe of \textbf{I\&“Ī྄”} .}$](https://music.163.com/#/song?id=2610328481)

## 题目描述

Arcaea 中有 $n$ 张谱面，第 $i$ 张谱面的难度为一个正整数 $a_i$。

有一个正整数 $k$，你希望打两张难度差**恰好**为 $k$ 的谱面。

你需要判断是否存在满足条件的两张谱面。如果存在则输出 `Yes`，否则输出 `No`。

## 说明/提示

**【样例解释 #1】**

第一组样例中，取第 $1$ 张和第 $6$ 张谱面，由于 $a_6-a_1=4$，输出 `Yes`。

**【样例解释 #2】**

第二组样例中，不存在两张谱面难度差为 $11$ 的谱面，输出 `No`。

**【数据范围】**

本题数据包含 $20$ 个测试点，每个测试点分值相等。

对于所有数据，满足 $1\le n\le 100$，$1\le k,a_i\le 10^9$。

## 样例 #1

### 输入

```
10 4
1 3 2 4 3 5 4 6 5 7```

### 输出

```
Yes```

## 样例 #2

### 输入

```
10 11
1 3 2 4 3 5 4 6 5 7```

### 输出

```
No```

# 题解

## 作者：Eason_cyx (赞：7)

可以对于每个数 $a_i$，用一个 `map` 来记录他们出现过。那么只需要将所有数存进 `map` 后，对于每个数 $a_i$，查询 $a_i+k$ 是否存在即可。时间复杂度 $\Theta(n\log n)$，$\log n$ 为 `map` 常数。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
map<int,int> mp;
int main() {
	int n,k; cin >> n >> k; for(int i = 1;i <= n;i++) { cin >> a[i]; mp[a[i]]++; }
	for(int i = 1;i <= n;i++) {
		if(mp[a[i]+k]) {
			cout << "Yes"; exit(0);
		}
	}
	cout << "No\n";
	return 0;
}
```

---

## 作者：DDD_et (赞：5)

# P11128 Solution

**本题做法：暴力、哈希**

## 题意

给定一个长度为 $n$ 的序列 $a$ 和一个正整数 $k$，问 $a$ 中有没有两个元素使得它们的**差**为 $k$（不是和为 $k$！）。

## 思路

首先想暴力。

两重循环，第一重枚举被减数，第二重枚举减数，如果有差为 $k$ 的即输出 `Yes` 并退出程序，最后如果没有提前结束则输出 `No`。

**细节**：由于题目要求**差为** $k$，所以如果第二重循环是从第一重循环枚举的下一个数开始的，那么就要判**绝对值**是否为 $k$（因为绝对值才是真正的差，事实上为养成好习惯，建议求**正整数差**时**只用绝对值**）。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, k, a[N];

int main ()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i < n; i ++)
        for (int j = i + 1; j <= n; j ++)
            if (abs (a[i] - a[j]) == k) //重点abs!
            {
                cout << "Yes";
                return 0;
            }
    cout << "No";
    return 0;
}
```

### 写在最后

其实有个很常用的小优化：用桶标记每个数是否出现（数据太大可以用 `map`），然后枚举 $a$ 中的每个数，看桶里面是否有能和当前数组成差为 $k$ 的数，有就输出 `Yes`（可以用来练哈希）。

**谢谢观看！**

---

## 作者：zhaohongdi114514 (赞：3)

### 排序，双指针

虽然本题是一道非常简单的红题，但我们依然要精益求精。

显然有一个 $n^2$ 的暴力，但这样不够优秀。

我们注意到那些差大于或小于 $k$ 的点对完全无需计入答案，所以考虑如何排除掉这些点对。

可以将所有数排序后采用双指针。若 $a_l$ 与 $a_r$ 之差大于 $k$ 就将 $l$ 前移来减小差，若 $a_l$ 与 $a_r$ 之差小于 $k$ 则将 $r$ 前移来增大差，若 $a_l$ 与 $a_r$ 之差等于 $k$ 则表明找到了答案，输出答案并返回。

时间复杂度 $O(n\log n)$，可以通过 $n=10^6$ 的数据。


```c++
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,k;
int a[N];
signed main(){
    cin>>n>>k;
    for (int i=1;i<=n;i++) cin>>a[i];//输入
    sort(a+1,a+n+1);//排序以便双指针处理
    int l=1,r=1;
    while (l<=n && r<=n){
        if (a[r]-a[l]>k){//情况之一
            l++;
        }  
        else if (a[r]-a[l]<k){//情况之二
            r++;
        }
        else{//找到了答案
            cout<<"Yes";
            return 0;
        }
    }
    cout<<"No";
}
```

---

## 作者：Program_A2 (赞：2)

## 思路：
本题可以暴力模拟，每输入一个数就检测是否与前面的任何一个数的差刚好等于 $k$ ,只要存在，就说明满足。

## 代码：

```cpp
#define I return
#define AK 0
#define IOI ;
#include "bits/stdc++.h"
using namespace std;
int a[101];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int l=1;l<i;l++){
			if(abs(a[i]-a[l])==k){
				cout<<"Yes";
				I AK IOI                   //为防止TLE可以在有满足的情况时中断程序
			}
		}
	}
	cout<<"No";              //全都不符合的情况的结果
    I AK IOI
}
```

---

## 作者：I_am_feiwu (赞：0)

## 题目大意
给定一个数组 $v$，问是否有两个数差为 $k$。
## 思路分析
注意到：$1 \le n \le 100$，所以这道题可以用 $O(n^2)$  的算法暴力枚举。  
注意这里只用判断 $\operatorname{abs}({v_i - v_j})$ 是否为 $k$，因为假如 $v_i - v_j=-k$ ，则必定有 $v_j - v_i=k$。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int v[105];
int n,k;
int main(){
	int n,k,tmp;
	cin>>n>>k;
	for(int i=1;i<=n;i++)	cin>>v[i];
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			//cout<<v[i]<<" "<<v[j]<<endl;
			if(abs(v[i]-v[j])==k){
				cout<<"Yes";
				return 0;
			}
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：kind_Ygg (赞：0)

~~又来水题解啦~~
## 题目大意
给定一个长度为 $n$ 序列 $a$，并且给定正整数 $k$，求这个序列里面是否存在 $a_i-a_j=k$，有输出 `Yes`，否则输出 `No`（$1\le n \le 100$）。
## 思路
斯，$n^2$ 暴力可过（但因为是正整数，所以只要 $|a_i-a_j|=k$，时间复杂度除以 $2$）。
## Code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,k;
int a[105];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(abs(a[i]-a[j])==k)
			{
				cout<<"Yes";
				return 0;
			}
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：zky114514 (赞：0)

大家好，我是 zky114514。我来交题解了！


## 题意
Arcaea 中有 $n$ 张谱面，第 $i$ 张谱面的难度为一个正整数 $a_i$，你希望打两张难度差恰好为 $k$ 的谱面，如果存在则输出 ```Yes```，否则输出 ```No```。

## 思路
因为 $n\le100$，所以很明显，**暴力判断**。

枚举两个**不同**的 $i$，如果两个的差（注意是**绝对值**）为 $k$，就可以。

如果找不到，就不行。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n,sum = 0,k;
    cin >> n>>k;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
    	if(abs(a[j]-a[i])==k&&i!=j){
    		cout<<"Yes";
    		return 0;
		}
	}
	cout<<"No";
}
```

---

## 作者：__HappY__ (赞：0)

### 题意

就是在一堆数里面找两个差为 $k$ 的数，很简单对吧。

### 思路

根据小学数学可得，若 $a - b = c$，则 $c + b = a$。于是，我们就可以记录每一个数出现的次数，再查找 $a_{a_i + k} $ 是否出现在原数组。本人是开了一个 map 来记录每个数出现的次数，再枚举每一个 $a_i + k$ 是否出现在 map 中。开 map 是因为 $a_i \le 10^9$。

代码很简单，直接给出来吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
const int N = 117;
int a[N];
map <int, int> mp;
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]]++;
	}
	for(int i = 1; i <= n; i++) {
		if(mp[a[i] + k] >= 1) {     // 找到就停下
			cout << "Yes\n";
			return 0;
		}
	}
	cout << "No\n";
	return 0;
}

``````

---

## 作者：liuhongyang123 (赞：0)

## 简短易懂的题解一枚
# 题目大意
题目已经讲的很清楚了。
# 解法
因为数据范围很小，暴力两两比对都可以过，所以我们直接两个循环，枚举比较的两张牌，然后做差，看一下是否符合要求，就可以了。
# 代码
~~码风丑，轻喷。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int n,a[MAXN],k;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){//枚举第一个数的下标
		for(int j=i;j<=n;j++){//枚举第二个数的下标，j从1开始也可以，但会重复比较很多
			if(abs(a[i]-a[j])==k){//判断，abs()为<cmath.h>中取绝对值的函数
				cout<<"Yes";
				return 0;//已经符合要求直接结束程序
			}
		}
	}
	cout<<"No";//枚举完所有的都没有符合要求的
	return 0;
}  
```
### 完结

---

## 作者：篮网总冠军 (赞：0)

本题思路：

直接暴力枚举 $i$ 和 $j$，对于每组 $i$ 和 $j$，判断 $a_i-a_j$ 是否为 $k$，如果有，输出 ``YES``。

如果枚举了所有 $i,j$ 都不满足，输出 ``No``。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[105]; 
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	long long n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			if (a[i]-a[j]==k){
				cout<<"Yes"<<endl;
				return 0;
			}
		}
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

