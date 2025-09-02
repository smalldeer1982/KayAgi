# Find Marble

## 题目描述

Petya and Vasya are playing a game. Petya's got $ n $ non-transparent glasses, standing in a row. The glasses' positions are indexed with integers from $ 1 $ to $ n $ from left to right. Note that the positions are indexed but the glasses are not.

First Petya puts a marble under the glass in position $ s $ . Then he performs some (possibly zero) shuffling operations. One shuffling operation means moving the glass from the first position to position $ p_{1} $ , the glass from the second position to position $ p_{2} $ and so on. That is, a glass goes from position $ i $ to position $ p_{i} $ . Consider all glasses are moving simultaneously during one shuffling operation. When the glasses are shuffled, the marble doesn't travel from one glass to another: it moves together with the glass it was initially been put in.

After all shuffling operations Petya shows Vasya that the ball has moved to position $ t $ . Vasya's task is to say what minimum number of shuffling operations Petya has performed or determine that Petya has made a mistake and the marble could not have got from position $ s $ to position $ t $ .

## 样例 #1

### 输入

```
4 2 1
2 3 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 3 3
4 1 3 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3 4
1 2 3 4
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 1 3
2 1 3
```

### 输出

```
-1
```

# 题解

## 作者：Dws_t7760 (赞：7)

一道简单的模拟题，可以直接用一个一重循环解决。

思路：将 $s$ 不断更新为 $p_s$，并将变量 $ans$ 加一，如果 $s$ 的值回到了起点，也就是 $s$ 的值会形成死循环，就输出 `-1`，如果 $s$ 和 $t$ 的值相等，就输出操作次数，即输出 $ans$。

代码：

```cpp
#include<iostream>
using namespace std;
int n,a[100100],s,t,ans;
bool v[100100];
int fcin() {
	int sto=0;
	char orz=getchar();
	while(orz<'0'||orz>'9') orz=getchar();
	while(orz>='0'&&orz<='9') sto=sto*10+orz-'0',orz=getchar();
	return sto;
}
int main() {
	n=fcin(),s=fcin(),t=fcin();
	for(int i=1;i<=n;i++) a[i]=fcin();
	while(!v[s]&&s!=t&&ans<=n) v[s]=1,s=a[s],ans++;
	cout<<(s==t?ans:-1);
	return 0;
}
```


---

## 作者：zzx114514 (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/CF285B)
# 题目大意

给出一个长度为 $n$ 的排列 $p$ 以及两个在 $[1,n]$ 中的整数 $s$、$t$。

定义对 $x$ 的一次操作为使 $x$ 变为 $p_x$。

求将 $s$ 变为 $t$ 最少需要几次操作？

# 解题思路
一道简单的模拟题，按照题意模拟即可，如果修改次数大于 $n$ 则说明无解，具体请见代码注释。
# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s,t,p[100005],cnt;
int main()
{
	cin>>n>>s>>t;
	if (s==t)//如果s等于t则不用修改，直接输出0 
	{
		cout<<0;
		return 0; 
	}
	for (int i=1;i<=n;i++) cin>>p[i];
	while(cnt<n)//如果修改的次数大于n，说明陷入死循环，s不可能变成t 
	{
		if (s==t) break;//如果修改成功则跳出循环 
		s=p[s];//修改 
		cnt++;//次数+1 
	}
	cout<<(cnt>=n? -1:cnt);//如果cnt>=n说明无解，为-1，否则为cnt 
	return 0;//华丽的结尾 
}

```

# [AC!](https://www.luogu.com.cn/record/119437012)

---

## 作者：残阳如血 (赞：3)

不可多得的小清新**模拟**题！
# 思路分析
题目中已经暗示地很明显了，只能对 $x$ 进行操作使得 $x$ 变成 $p_x$。

而我们现在可以操作的值唯独 $s$，所以我们的思路就呼之欲出了。

我们重复将 $s$ 迭代为 $p_s$。如果 $s=t$，那么我们就找到了答案。如果 $s$ 回到了原来的值，那么就说明进入了死循环，不可能找到答案，输出 $-1$。
# 程序实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s, t, cnt, ps;
// ps记录s的初值，cnt记录所需要的操作次数
int main() {
	cin >> n >> s >> t, ps = s;
	vector<int> p(n + 1); // 建立一个长度为n+1的数组
	for (int i = 1; i <= n; i++) cin >> p[i];
	if (s == t) { // 一定要进行特判
		cout << 0;
		return 0;
	}
	while (true) { // 反复迭代
		s = p[s], cnt++;
		if (s == t) {
			cout << cnt;
			return 0;
		}
		if (s == ps) {
			cout << -1;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Shadow_T (赞：2)

### 题目大意

给定 $n,s,t$ 和一个长度为 $n$ 的序列 $p$。每次操作可以将 $x$ 变为 $p_x$，求最少要几次操作。

### 解题思路

就是按题意模拟，首先 $pos=s$，然后每次将 $pos$ 变为 $p_{pos}$。每次变化的时候再判断 $pos$ 是否为 $t$，如果是输出现在的次数。

对于无解的情况可以用一个桶记录所有的 $pos$，如果出现了已经出现过的 $pos$，那么必定无解；当然也可以判断操作次数大于 $n$ 了，那么也必定无解。

### 实现代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int p[100001];
bool st[100001];
int main()
{
	int n,s,t,ans=0;
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
	cin>>p[i];
	while(true)
	{
		if(s==t) break;
		if(st[s])
		{
			puts("-1");
			return 0;
		}
		st[s]=true;
		s=p[s];
		ans++;
	}
	cout<<ans;
}
```

---

## 作者：zsfzhjf (赞：2)

根据题意可知，本题就是模拟，求 $p[p[\cdots[p[s]]\cdots]]=t$ 中嵌套的个数。其中在以 $s$ 为索引查找 $t$ 的时候，可能会出现找到之前找过的数，但这时还没找到 $t$,那么就找不到 $t$ 了，则输出 $-1$。
```c
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int n,s,t;
int p[MAXN];
int main(){
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
		cin>>p[i];
	if(s==t){//特判，当s=t时，不用找
		cout<<0;
		return 0;
	}
	int pos=p[s],ans=1;
	while(1){
		if(pos==t){
			cout<<ans;
			break;
		}else if(pos==s){//形成了一个环，找不到了t了。
			cout<<-1;
			break;
		}else{
			pos=p[pos];
			ans++;
		}		
	}
}
```


---

## 作者：XH1111 (赞：2)

## 题目大意
给出三个数值：$n$，$s$，$t$。$n$ 规定了下一行 $p$ 数组的长度和大小，然后通过操作（将 $x$ 变为 $p_x$）将 $s$ 变成 $t$。若不可能，则输出 ``-1``；

## 过程介绍

我们首先定义一个变量 $sum$ 用于记录操作的次数，每轮循环将 $s$ 更新为 $p_s$，并将 $sum$ 加上 $1$，如果 $s$ 和 $t$ 的值相等，就输出 $sum$ 的值并跳出循环，如果 $s$ 的值回到了起点，如果继续运行会进入死循环，此时应该跳出循环并输出 `-1`，否则继续下一轮循环。

## 具体操作
将 $s$ 转换的过程如下：
```cpp
while(sum>=0){
    if(s==t){
        cout<<sum;
        return 0;
    }
    s=p[s];
    sum++;
}
```
而在这里面，有需要另加一个特判，防止死循环，如下：
```cpp
if(sum>=n){
    cout<<-1;
    return 0;
}
```
将这两段代码结合起来就是这道题的答案，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,s,t,p[100005],sum=0;
    cin>>n>>s>>t;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    while(sum>=0){
        if(s==t){
            cout<<sum;
            return 0;
        }
        s=p[s];
        sum++;
        if(sum>=n){
            cout<<-1;
            return 0;
        }
    }
    return 0;
} 
```

---

## 作者：andyli (赞：1)

模拟 $x = p_x$ 这个过程直到走到 $t$。如果在这个过程中走回到了起点 $s$，说明无解。

```rust
input! {
    n: usize,
    s: usize,
    t: usize,
    p: [usize; n]
}

let mut x = s;
let mut ans = 0;
println!(
    "{}",
    loop {
        if x == t {
            break ans;
        }
        x = p[x - 1];
        ans += 1;
        if x == s {
            break -1;
        }
    }
);
```

---

## 作者：very_easy (赞：0)

# 思路
这题其实很简单，不需要太难的 DFS，只需要模拟就可以了。

我们不妨使每个元素拥有两个属性：是否被访问和当前下标中的数值。

如果当前访问是数字已经被访问过了，就说明产生了循环，直接输出 $-1$ 就可以了，所以代码也就有了。

# AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct node{
	int val;
	bool flag;
}p[N];//val表示值,flag表示是否访问
int main(){
	int n,s,t;
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++){
		cin>>p[i].val;
		p[i].flag=0;//初始化
	}
	int cnt=0;//计数
	while(1){
		if(p[s].flag){//发现循环
			cout<<-1;
			exit(0);//终止
		}
		if(s==t){//找到目标
			cout<<cnt<<endl;
			exit(0);//终止
		}
		p[s].flag=1;//将当前数设置为访问过了
		s=p[s].val;//更新
		cnt++;//计数
	}
	return 0;
}

```
最后感谢管理员@AK_Dream提供的建议和帮助。

---

## 作者：zhang_Jimmy (赞：0)

一道比较简单的模拟。

首先将 $s$ 每次变成 $p_s$，并且操作次数加一，如果此时 $s$ 的值和输入时的 $s$ 的值一样，那么无论怎么变都无法变为 $t$，直接输出 `-1`；如果此时 $s = t$，直接输出操作次数即可。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,t,a[100010],ans;
int main()
{
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	if(s==t)//特判
	{
		cout<<0;
		return 0;
	}
	int tmp=s;//记录输入时s的值
	s=a[s],ans++;
	while(s!=tmp&&s!=t)
	{
		s=a[s];
		ans++;
	}
	if(s==t) cout<<ans;
	else cout<<-1;
}
```


---

## 作者：01Dragon (赞：0)

### 题意
给定 $s$、$t$、$n$ 以及长度为 $n$ 的序列 $p$，让你进行操作，每次操作能让数 $x$ 变成数 $p_x$，问需要几次操作才能让 $s$ 变成 $t$。
### 思路
直接按照题意模拟，每次操作把 $s$ 替换成 $p_s$ ，同时开一个变量 $cishu$ 记录操作次数，循环直到：

- $s=t$。这时直接输出 $cishu$。
- $cishu \ge n$。这时说明无解，需要输出 $-1$。
### 代码
```cpp
#include<iostream> 
#include<cstdio> 
#include<algorithm> 
#include<cmath> 
#include<deque> 
#include<vector> 
#include<queue> 
#include<string> 
#include<cstring> 
#include<map> 
#include<stack> 
#include<set> 
using namespace std;
int n,s,t,p[100005],cishu;
int main()
{
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
	}
	while(cishu<n)
	{
		if(s==t)//如果得到答案就跳出循环 
		{
			break;
		}
		s=p[s];//替换 
		cishu++;//记录次数 
	}
	if(cishu>=n)//如果无解 
	{
		cout<<-1;
	}
	else
	{
		cout<<cishu;
	}
	return 0;
}
```



---

