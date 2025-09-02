# Neko Finds Grapes

## 题目描述

On a random day, Neko found $ n $ treasure chests and $ m $ keys. The $ i $ -th chest has an integer $ a_i $ written on it and the $ j $ -th key has an integer $ b_j $ on it. Neko knows those chests contain the powerful mysterious green Grapes, thus Neko wants to open as many treasure chests as possible.

The $ j $ -th key can be used to unlock the $ i $ -th chest if and only if the sum of the key number and the chest number is an odd number. Formally, $ a_i + b_j \equiv 1 \pmod{2} $ . One key can be used to open at most one chest, and one chest can be opened at most once.

Find the maximum number of chests Neko can open.

## 说明/提示

In the first example, one possible way to unlock $ 3 $ chests is as follows:

- Use first key to unlock the fifth chest,
- Use third key to unlock the second chest,
- Use fourth key to unlock the first chest.

In the second example, you can use the only key to unlock any single chest (note that one key can't be used twice).

In the third example, no key can unlock the given chest.

## 样例 #1

### 输入

```
5 4
9 14 6 2 11
8 4 7 20
```

### 输出

```
3```

## 样例 #2

### 输入

```
5 1
2 4 6 8 10
5
```

### 输出

```
1```

## 样例 #3

### 输入

```
1 4
10
20 30 40 50
```

### 输出

```
0```

# 题解

## 作者：Dancing_Wave (赞：2)

~~这题其实很水，但由于恶评成了蓝题？~~

这道题有一个限制条件：钥匙$a_{i}$+宝箱$b_{j}$为奇数要是才能打开宝箱，那么我们分别记录一下$a$数组$b$的奇偶数个数，最后取对应钥匙和宝箱数量的最小值就可以了。

那么有请——代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){//快读（可以用来压行）
	int f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		f=(f<<1)+(f<<3)+ch-'0';
		ch=getchar();
	}
	return f;
}
int n,m;//如题意
int cnt1[2],cnt2[2];//记录奇偶数个数，cnt1记录a,cnt2记录b 
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)cnt1[read()%2]++;
	for(int i=1;i<=m;i++)cnt2[read()%2]++;//输入的时候直接统计
	cout<<min(cnt1[0],cnt2[1])+min(cnt2[0],cnt1[1])<<endl;//输出
	return 0;
}
```

---

## 作者：WKAHPM (赞：0)

题目大意：

给出两组数，求两组中的两数之和为奇数的组数（不可重复选取）

思路：

我们知道奇数+偶数=奇数

所以先统计两组中奇数出现的个数和偶数出现的个数

将第一组数中奇数出现的个数与第二组中偶数进行配对，即取$min(lenji1,lenou2)$ 

再将将第一组数中偶数出现的个数与第二组中奇数进行配对，即取$min(lenou1,lenji2)$

两个结果相加即可

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int lenji1,lenji2,lenou1,lenou2;//分别表示第一组数中奇数个数、第二组数中奇数个数、第一组数中偶数个数、第二组中偶数个数
int n,m;
int a,b;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)//统计
	{
		cin>>a;
		a%2==1?lenji1++:lenou1++;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b;
		b%2==1?lenji2++:lenou2++;
	}
	cout<<min(lenji1,lenou2)+min(lenji2,lenou1);//取min相加
	return 0;
}

```


---

## 作者：ljc20020730 (赞：0)

直接统计即可，考虑配对只可能是奇数+偶数或者偶数+奇数。

所以答案必然是

  $ \min\{ cnta_{odd} , cntb_{even}\} +\min\{ cnta_{even} , cntb_{odd}\} $
 
 ```
 # include <bits/stdc++.h>
using namespace std;
int cntA[2],cntB[2];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) {
        int t; scanf("%d",&t);
        cntA[t%2]++;
    } 
    for (int i=1;i<=m;i++) {
        int t; scanf("%d",&t);
        cntB[t%2]++;
    }
    int ans=min(cntA[1],cntB[0])+min(cntA[0],cntB[1]);
    printf("%d\n",ans);
    return 0;
}
 ```

---

## 作者：mulberror (赞：0)

# 自己写的所有题解
[【传送门】](https://www.cnblogs.com/chhokmah/p/10768012.html)  
水题一道。  
题目的大致意思就是：给你两个集合，求集合间有多少数对和是奇数。  

题解，开$4$个桶后，求一个$min$就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int v1[4], v2[4];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i ++) scanf("%d", &x), v1[x % 2] ++;
	for (int i = 1, x; i <= m; i ++) scanf("%d", &x), v2[x % 2] ++;
	cout << min(v1[0], v2[1]) + min(v1[1], v2[0]) << endl; 
	return 0;
}
```

---

