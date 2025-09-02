# [CCC 2015 S2] Jerseys

## 题目描述

有编号为 $1 \sim n$ 的队服要分给 $m$ 个队员，队服从小到大分别有 S、M、L 三种大小，每个队员对于队服有一定的要求，具体的：第 $i$ 个队员希望得到的队服尺码**不小于** $a_{i}$，编号为 $b_{i}$。

求最多能满足多少人的要求。


## 说明/提示

**【数据范围】：**

对于 $50\%$ 的数据，$1 \leq n,m \leq 10^{3}$；

对于 $100\%$ 的数据，$1 \leq n,m \leq 10^{6}$。



## 样例 #1

### 输入

```
4
3
M
S
S
L
L 3
S 3
L 1```

### 输出

```
1```

# 题解

## 作者：linyukun (赞：4)

## 1. 前言
本文的分析会比较通俗，自己要多去思考，麻烦一定 _仔细全部看完_，有异议、不懂或认为可以优化请私信反馈呢。  

## 2. 题目解析：
+ 对于每次询问，查看他要的标号的尺码是否合适。
+ 合适的话就计数。同时因为一件衣服一个人穿，所以尺码要小于最小码，没人穿得上，就不会重复搜索了。

## 3. 提示要点：
* 使用过的衣服大小设为 $-1$，就不会再有第二次使用了。

## 4. 代码写作：
理论存在，实践开始。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,n,m,num[1000006],b,aa;
char a,c;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='S'){
			num[i]=1;
		}
		if(c=='M'){
			num[i]=2;
		}
		if(c=='L'){
			num[i]=3;
		}
	}
	while(m--){
		cin>>a>>b;
		if(a=='S')aa=1;
		if(a=='M')aa=2;
		if(a=='L')aa=3;
		if(num[b]>=aa){
			cnt++;
			num[b]=-1;
		}
	}
	cout<<cnt;
	return 0;
}
```

## 5. 总结鸣谢：
**另：还有感谢管理大大的的审核。**

---

## 作者：UniGravity (赞：1)

## Solution P9811 [CCC 2015 S2] Jerseys

~~（为什么这题能评黄啊？）~~

### 思路分析
发现一件衣服选了就不能再选，且对答案的贡献都是 $1$，所以可以直接**贪心**的选。

具体来说，若满足第 $i$ 位队员的要求，就可以直接选走衣服，此时将衣服大小标记为 $0$ 即可。

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;

int sz[1000005];

int main() {
    cin >> n >> m; 
    char ch;
    for (int i = 1; i <= n; i++) {
        cin >> ch;
        if (ch == 'S') sz[i] = 1;
        else if (ch == 'M') sz[i] = 2;
        else sz[i] = 3;
    }
    int a, b;
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        cin >> ch >> b;
        if (ch == 'S') a = 1;
        else if (ch == 'M') a = 2;
        else a = 3;
        if (a <= sz[b]) {
            ans++;
            sz[b] = 0;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Vct14 (赞：0)

本题的思路是贪心。

因为每一件队服的贡献至多为 $1$，所以如果某一个人想穿编号为 $i$ 的队服，且这件队服刚好是他想要的尺码，那么就直接将这件队服分给他。

为了比较尺码更加方便，在读入的时候，我们可以将尺码转化为数字，例如 $0,1,2$。这样直接比较数值的大小即可。在某一件队服已经分给某人后，这件队服的尺码可以转为 $-1$，即比任何人希望的尺码都小。

```c++
#include<bits/stdc++.h>
using namespace std;
#define SizetoNum(w) if(size=='S'){w=0;}if(size=='M'){w=1;}if(size=='L'){w=2;}
int a[1000002];

int main(){
	int n,m;
	cin>>n>>m;
	char size;
	for(int i=1; i<=n; i++){
		cin>>size;
		SizetoNum(a[i]);
	}
	int num,d,sum=0;
	while(m--){
		cin>>size>>d;
		SizetoNum(num);
		if(a[d]>=num) sum++,a[d]=-1;
	}
	cout<<sum;
	return 0;
}
```

---

