# [USACO20DEC] Do You Know Your ABCs? B

## 题目描述

Farmer John 的奶牛正在 "mooZ" 视频会议平台上举行每日集会。她们发明了一个简单的数字游戏，为会议增添一些乐趣。

Elsie 有三个正整数 $A$、$B$ 和 $C$（$A\le B\le C$）。这些数字是保密的，她不会直接透露给她的姐妹 Bessie。她告诉 Bessie 七个范围在 $1\ldots 10^9$ 之间的整数（不一定各不相同），并宣称这是 $A$、$B$、$C$、$A+B$、$B+C$、$C+A$ 和 $A+B+C$ 的某种排列。

给定这七个整数，请帮助 Bessie 求出 $A$、$B$ 和 $C$。可以证明，答案是唯一的。 

## 说明/提示

### 测试点性质

- 测试点 $2-3$ 满足 $C\le 50$。
- 测试点 $4-10$ 没有额外限制。

## 样例 #1

### 输入

```
2 2 11 4 9 7 9```

### 输出

```
2 2 7```

# 题解

## 作者：zhanghaosong (赞：5)

# P9955 [USACO20DEC] Do You Know Your ABCs? B 题解

### 解析

$\because a,b,c\in \mathbb N^+$，

$\therefore a\leq b\leq \cdots \leq a+b+c$。

$a$ 和 $b$ 就是给出的 $7$ 个数中的最小值和次小值，$c$ 就是给出的最大值减去 $a+b$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>v;
int tmp;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	while(cin>>tmp){
		v.push_back(tmp);
	}
	sort(v.begin(),v.end());
	cout<<v[0]<<" "<<v[1]<<" "<<v[6]-v[0]-v[1];
return 0;
}

```

### 题外话

由于使用了 `while` 读入，在读完数之后请按 `Ctrl+Z` 强制终止读入。

---

## 作者：FurippuWRY (赞：4)

设有数组 $a$，其中元素为题目中的 7 个数。

先将这 7 个数从小到大排序，因为 $A,B,C\in[1,10^9],A\le B\le C$，所以 $a_1=A,a_2=B$。

接下来需要分讨，因为 $A\le B\le C$，所以 $C$ 只会是 $a_3,a_4$ 的其中一个（比较 7 个数的大小即可得出此结论）。如果 $A+B=a_3$，那么此时的 $a_3$ 就不一定是 $C$，输出 $a_4$，否则输出 $a_3$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll a[10];

int main() {
    
    for (ll i = 1; i <= 7; ++i) cin >> a[i];
    sort(a + 1, a + 8);
    cout << a[1] << ' ' << a[2] << ' ';
    if (a[1] + a[2] == a[3]) cout << a[4];
    else cout << a[3];

    return 0;
    
}
```

---

## 作者：continueOI (赞：2)

简单题。

由 $A \le B \le C$ 可得：

$$A \le B \le A+B \le A+C \le B+C \le A+B+C$$

根据人类智慧可知，我们将这 $7$ 个数升序排序后，第一个肯定是 $A$，第二个肯定是 $B$，最后一个肯定是 $A+B+C$，减去 $A$ 和 $B$ 后即可得 $C$。

$C$ 值不取第 $3$ 个的原因是其可能为 $A+B$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	for(int i=1;i<=7;i++)
		cin>>a[i];
	sort(a+1,a+8);
	cout<<a[1]<<' '<<a[2]<<' '<<a[7]-a[1]-a[2];
	return 0;
}
```


---

## 作者：taojinchen (赞：2)

# 思路
因为所有数是正整数，所以 $A+B+C$ 最大，并且 $A$ 和 $B$ 是最小的两个。则 $C$ 等于最大的数减去最小的两个数，即 $C=(A+B+C)-A-B$ 恒成立。因此，我们只要找出最大的数和最小的两个数即可算出三个值。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,x[10],i;
int main(){
  for(i=1;i<=7;i++){
    cin>>x[i];//输入
  }
  sort(x+1,x+8);//排序，x[1]<x[2]<x[3]<x[4]<x[5]<x[6]<x[7]
  a=x[1],b=x[2],c=x[7]-a-b;//计算
  cout<<a<<" "<<b<<" "<<c;//输出a<=b<=c
  return 0;
}
```


---

## 作者：Pink_Cut_Tree (赞：1)

# P9955 [USACO20DEC] Do You Know Your ABCs? B 题解

大水题。

### 解析

对于题中给的这 $7$ 个数，它们都是正整数。

所以 $a$ 一定是最小的，$b$ 一定是次小的，最大的是 $a+b+c$，所以 $c$ 就是最大的减最小的减次小的。

### 坑点

给定的数没有排序，需要自己排序。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	for(int i=1;i<=7;i++){
		cin>>a[i];
	}
	sort(a+1,a+8);
	cout<<a[1]<<" "<<a[2]<<" "<<a[7]-a[1]-a[2];
return 0;
}

```


---

## 作者：littleqwq (赞：0)

# P9955 [USACO20DEC] Do You Know Your ABCs? B

### 大致思路：

有一个重要的等式，它就是 $a ≤ b ≤ c$ 这个等式，那么可以得出，$A + B,B + C,C + A,A + B + C$ 这几个算式一定比 $A$ 和 $B$ 大，为什么不包括 $C$ 呢？因为有一种情况 $A + B ≤ C$，这时候也是满足条件的。那我们要怎样求出 $C$ 呢？我们刚才知道了 $A$ 和 $B$ 是最小的两个数，而众所周知 $A + B + C$ 一定是所有等式中最大的，那么根据加法与减法的结合，我们可以知道，$C = A + B + C - A - B$，所以我们可以先排序，在用最大的，减去最小的两个数，也就是 $A$ 和 $B$，即可求出 $C$。

### 代码实现：

```
#include<bits/stdc++.h>
using namespace std;
int n=7,ar[1000001];
int main(){
	for(int i=1;i<=n;i++){
		cin>>ar[i];
	}
	sort(ar+1,ar+7+1);
	cout<<ar[1]<<" "<<ar[2]<<" "<<ar[7]-ar[1]-ar[2]<<"\n";
	return 0;
}
```

这样本道题就完成啦，如有不足可在评论区发布。

---

## 作者：__O_v_O__ (赞：0)

首先我们观察到，$a$ 和 $b$ 必然是七个数中最小的两个数。

原因：因为 $a\le b\le c$，所以 $c,b+c,a+c,a+b+c$ 都比 $a,b$ 大。而 $a+b$ 显然大于 $a,b$，则 $a$ 和 $b$ 是七个数中最小的两个数。

于是将七个数排序，选出最小的两个数就是 $a$ 和 $b$。

如何求出 $c$ 呢？因为 $a,b,c$ 都是正整数，所以 $a+b+c$ 必然是七个数里最大的，知道了 $a+b+c$，减去 $a,b$ 就能求出 $c$ 了。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int a[10];//定义
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//读入优化
	afor(i,1,7,STB)cin>>a[i];//输入
	sort(a+1,a+8);//排序
	cout<<a[1]<<' '<<a[2]<<' '<<a[7]-a[1]-a[2];//输出
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

首先，我们知道 $A\le B$ 的，而 $B$ 一定 $\le$ 其它别的数，因此，将数排序后前两小的数一定是 $A$ 和 $B$。

然后，因为 $A+B+C$ 是最大的，而已知 $A,B$ 所以 $C=(A+B+C)-A-B$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int s[15];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	for(int i=1;i<=7;i++){
		cin>>s[i];
	}
	sort(s+1,s+8);
	cout<<s[1]<<' '<<s[2]<<' '<<s[7]-s[1]-s[2];
	return 0;
}
```


---

