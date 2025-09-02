# 共通要素 (Common Elements)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2021yo1a/tasks/joi2021_yo1a_c

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ と長さ $ M $ の整数列 $ B\ =\ (B_1,\ B_2,\ \ldots,\ B_M) $ が与えられる．$ A $ と $ B $ の両方に出現する整数をすべて，$ 1 $ 個ずつ昇順で出力せよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100 $．
- $ 1\ \leqq\ M\ \leqq\ 100 $．
- $ 1\ \leqq\ A_i\ \leqq\ 100 $ ($ 1\ \leqq\ i\ \leqq\ N $)．
- $ 1\ \leqq\ B_j\ \leqq\ 100 $ ($ 1\ \leqq\ j\ \leqq\ M $)．

### Sample Explanation 1

$ 6 $ は $ A $ の $ 3 $ 番目，$ B $ の $ 4 $ 番目に出現する．また，$ 12 $ は $ A $ の $ 6 $ 番目，$ B $ の $ 2 $ 番目に出現する．$ 6 $ と $ 12 $ 以外に $ A,\ B $ の両方に出現する整数は存在しない．したがって，$ 6,\ 12 $ を昇順に改行区切りで出力する．

### Sample Explanation 2

$ 100 $ は $ A,\ B $ の両方に出現する．$ 100 $ 以外に $ A,\ B $ に出現する整数は存在しない．したがって，$ 100 $ を出力する．

### Sample Explanation 3

$ A,\ B $ の両方に出現する整数は存在しない．したがって，何も出力しない．

## 样例 #1

### 输入

```
6 5
2 4 6 8 10 12
15 12 9 6 3```

### 输出

```
6
12```

## 样例 #2

### 输入

```
3 5
100 100 100
100 100 100 100 100```

### 输出

```
100```

## 样例 #3

### 输入

```
1 1
2
5```

### 输出

```
```

## 样例 #4

### 输入

```
10 10
76 91 98 7 98 7 98 10 63 91
70 71 10 10 91 70 65 10 63 76```

### 输出

```
10
63
76
91```

# 题解

## 作者：Moon_Traveller (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_joi2021_yo1a_c)

# 题意简述：

给定一个长度为 $n$ 的数组 $a$，和一个长度为 $m$ 的数组 $b$。

从小到大输出 $a$ 和 $b$ 共有的元素。

# 思路：

定义两个数组：$visa$ 和 $visb$，把 $a,b$ 两个数组中每个数出现的次数存起来。

然后遍历 $1\sim 100$ 的每个数，把 $visa$ 和 $visb$ 中的次数都 $\ge 1$ 的数输出即可。

# 代码：

```cpp
#include <iostream>
using namespace std;

int n, m;
int a[105], b[105];
int visa[105];
int visb[105];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i]; // 这里其实不需要输入在数组里，一个变量即可
        visa[a[i]]++;
    }
    for(int i = 1; i <= m; i++)
    {
        cin >> b[i]; // 同上
        visb[b[i]]++;
    }
    for(int i = 1; i <= 100; i++)
    {
        if(visa[i] >= 1 && visb[i] >= 1)
        {
            cout << i << endl;
        }
    }
    return 0;
}
```

---

## 作者：wdgm4 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_joi2021_yo1a_c)

------------

提供三种解法。

## 1.桶

由于 $A_i$ 和 $B_i$ 的范围超级小，可以用两个桶分别存 $A$ 和 $B$ 的数字是否出现，然后输出即可。

```cpp
#include <bits/stdc++.h>
#define XD 114514

using namespace std;
int n,m,a[110],b[110];
int c[110],d[110];//桶数组 
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c[a[i]]++;
	} 
	for(int i=1;i<=m;i++){
		cin>>b[i];
		d[b[i]]++;
	} 
	for(int i=1;i<=100;i++){
		if(c[i] and d[i]) cout<<i<<endl;
	}
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/101440128)

## 2.暴力

将 $A$ 和 $B$ 数组排个序，然后直接用 $n^2$ 级别的暴力找一遍，中间用一个数组去重即可。

```cpp
#include <bits/stdc++.h>
#define XD 114514

using namespace std;
int n,m,a[110],b[110];
bool vis[110];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(int i=1;i<=m;i++){
		cin>>b[i];
	} 
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j] and vis[a[i]]==0){
				cout<<a[i]<<endl;
				vis[a[i]]=1;
			}
		}
	}
	return 0;
}

```

记得排序时 $a$ 对应的是 $n$，$b$ 对应的是 $m$。

[AC 记录](https://www.luogu.com.cn/record/101441594)

## 双指针

先将 $a$ 和 $b$ 排好序，用双指针刚开始一个指向 $a_1$，一个指向 $b_1$，之后如果 $a_i$ 等于 $b_j$ 让指向 $a$ 和 $b$ 数组的指针都往右移，否则如果 $a_i > b_j$，让指向 $b$ 数组的指针往右移，否则让指向 $a$ 数组的指针往右移。

我们可以这样想，假如 $b_j$ 是第一个与 $a_i$ 相等的，那么 $b_1$ 到 $b_{j-1}$ 一定都比 $a_i$ 到 $a_n$ 小，所以就不用再遍历 $b_1$ 到 $b_{j-1}$ 了。

```cpp
#include <bits/stdc++.h>
#define XD 114514

using namespace std;
int n,m,a[110],b[110];
bool vis[110];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(int i=1;i<=m;i++){
		cin>>b[i];
	} 
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	int i=1,j=1;
	while(i<=n and j<=m){
		if(a[i]==b[j]){
			if(!vis[a[i]]){
				cout<<a[i]<<endl;
				vis[a[i]]=1;
			}
			i++;j++;
		}else if(a[i]>b[j]) j++;
		else i++;
	}
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/101444893)

---

## 作者：幻想繁星 (赞：0)

# 题意
给定两个数组 $a$ 和 $b$，将 $a$ 和 $b$ 按从小到大的顺序排序，并输出数组 $a$ 和 $b$ 共有的元素。
# 思路
由于 $a$ 和 $b$ 的元素并不多所以可以先使用朴素的暴力找出 $a$ 和 $b$ 的共有元素。

但是由于题目要求将 $a$、$b$ 按从小到大的顺序排序，所以我们应该将找出的 $a$、$b$ 共有元素按从小到大的顺序排序并去重，即可完成此题。

时间复杂度：$\Omega(nm)$
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,t=0,a[10002],b[10002],c[10002];
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	cin>>a[i];
    for(int i=1;i<=m;i++)
    	cin>>b[i];
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    	{
    		if(a[i]==b[j])
    			c[t++]=a[i];
    	}
    sort(c,c+t);
    for(int i=0;i<t;i++)
    	if(c[i+1]!=c[i])
    		cout<<c[i]<<"\n";
}
```


---

## 作者：tianbiandeshenghuo (赞：0)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo/solution-at-joi2021-yo1a-c)

[题目传送门](/problem/AT_joi2021_yo1a_c)

给定有 $n$ 个数的数组 $a$ 和有 $m$ 个数的数组 $b$。

从小到大输出 $a$ 与 $b$ 中共有的数字，每个数占一行。

# 分析
我们对数组 $a$ 中的每个数进行记录，然后对数组 $b$ 排序。从小到大判断 $b_i$ 在 $a$ 中是否出现过即可。

但是因为不能重复输出，所以在输出过一个后重新将此数表为未记录。

时间复杂度：读入 $O(n+m)$，排序 $O(m\log m)$。

空间复杂度：$O(n+m)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int n, m, a, b[105];
bool v[105];
int main(){
  cin >> n >> m;
  while (n--){
    cin >> a;
    v[a] = 1;//标记。
  }
  for (int i = 1; i <= m; i++){
    cin >> b[i];
  }
  sort(b + 1, b + m + 1);
  for (int i = 1; i <= m; i++){
    if (v[b[i]]){//判断是否存在。
      cout << b[i] << '\n';
      v[b[i]] = 0;//归零。
    }
  }
  return 0;
}
```

---

## 作者：NaOHqwq (赞：0)

## 思路

题意给的很清楚，输入两个数组 $a$ 和 $b$ 并对其进行升序排序，然后找出两个数组共有的元素输出即可。由于数据范围不大所以可以进行暴力查找共有元素。

题中唯一要注意的地方就是如果有重复的元素，只输出一次即可，所以还需要一个数组 $s$ 存储每个元素是否出现过。

注：因为要判断各个元素是否出现过，数组 $s$ 定义成 `bool` 类型和 `int` 类型均可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 101;
int a[maxn], b[maxn];
bool s[maxn];
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for(int i = 1;i <= m;i++){
		cin >> b[i];
	}
	sort(a+1, a+n+1);
	sort(b+1, b+m+1); //排序
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(a[i]==b[j] && !s[a[i]]){
				cout << a[i] << endl;
				s[a[i]] = true;
			} //查找，判断
		}
	}
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

~~话说我应该是最复杂的写法了吧~~

## 思路：

首先在每个 $b$ 数组的元素中寻找在 $a$ 数组中是否也出现过了这么一个数字，如果出现过，再在 $c$ 数组中进行一次查重，如果 $c$ 数组中尚未出现过这个数，就把它添加到 $c$ 数组中，最后将 $c$ 数组排序，并输出。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
//暴力写法怕超时所以加了个快读快写，但事实证明没啥用
inline int read(){
	register int x = 0, f = 1;
	char c = getchar();
	while(c > '9' || c < '0'){
		if(c == '-'){
			f = -1;
		}
		c = getchar();
	}
	while(c <= '9' && c >= '0'){
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	return x * f;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9){
		write(x / 10);
	}
	putchar((x % 10) + '0');
}
int a[10086], b[10086],c[10086];
main(){
	int n, m, lenc = 0;//lenc表示c数组的长度
	n = read();
	m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= m; i++) {
		b[i] = read();
		for(int j = 1; j <= n; j++){
			if(a[j] == b[i]){//判断a数组中是否出现过与b数组一样的元素
				bool flag = 1;//flag表示c数组中是否没有出现过这个数
				for(int k = 1; k <= lenc; k++){
					if(c[k] == b[i]){//如果出现了
						flag = 0;
						break;
					}
				}
				if(flag){//如果c数组中尚未出现这个数
					c[++lenc] = b[i];//添加至c数组
				}
				break;
			}
		}
	}
	sort(c + 1, c + lenc + 1);//排序很关键
	for(int i = 1; i <= lenc; i++){
		write(c[i]);//输出
		puts("");
	}
	return 0;
}
```

---

## 作者：NOI_AK_dreeeam (赞：0)

这题先把 $a$ 数组和 $b$ 数组，排个序，然后直接暴力找出哪些元素同时在两个数组中。

不过这题有一个注意的地方：如果有多个重复的，只输出一个元素。所以还要定义一个 $c$ 数组来存每个元素是否出现过。

**_AC code_**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],b[105],c[105];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]&&!c[a[i]]){
				cout<<a[i]<<"\n";
				c[a[i]]=1;
			}
		}
	}
    return 0;
}
```


---

