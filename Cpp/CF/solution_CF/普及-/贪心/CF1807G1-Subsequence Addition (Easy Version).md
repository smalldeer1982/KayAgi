# Subsequence Addition (Easy Version)

## 题目描述

The only difference between the two versions is that in this version, the constraints are lower.

Initially, array $ a $ contains just the number $ 1 $ . You can perform several operations in order to change the array. In an operation, you can select some subsequence $ ^{\dagger} $ of $ a $ and add into $ a $ an element equal to the sum of all elements of the subsequence.

You are given a final array $ c $ . Check if $ c $ can be obtained from the initial array $ a $ by performing some number (possibly 0) of operations on the initial array.

 $ ^{\dagger} $ A sequence $ b $ is a subsequence of a sequence $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly zero, but not all) elements. In other words, select $ k $ ( $ 1 \leq k \leq |a| $ ) distinct indices $ i_1, i_2, \dots, i_k $ and insert anywhere into $ a $ a new element with the value equal to $ a_{i_1} + a_{i_2} + \dots + a_{i_k} $ .

## 说明/提示

For the first test case, the initial array $ a $ is already equal to $ [1] $ , so the answer is "YES".

For the second test case, performing any amount of operations will change $ a $ to an array of size at least two which doesn't only have the element $ 2 $ , thus obtaining the array $ [2] $ is impossible and the answer is "NO".

For the third test case, we can perform the following operations in order to obtain the final given array $ c $ :

- Initially, $ a = [1] $ .
- By choosing the subsequence $ [1] $ , and inserting $ 1 $ in the array, $ a $ changes to $ [1, 1] $ .
- By choosing the subsequence $ [1, 1] $ , and inserting $ 1+1=2 $ in the middle of the array, $ a $ changes to $ [1, 2, 1] $ .
- By choosing the subsequence $ [1, 2] $ , and inserting $ 1+2=3 $ after the first $ 1 $ of the array, $ a $ changes to $ [1, 3, 2, 1] $ .
- By choosing the subsequence $ [1, 3, 1] $ and inserting $ 1+3+1=5 $ at the beginning of the array, $ a $ changes to $ [5, 1, 3, 2, 1] $ (which is the array we needed to obtain).

## 样例 #1

### 输入

```
6
1
1
1
2
5
5 1 3 2 1
5
7 1 5 2 1
3
1 1 1
5
1 1 4 2 1```

### 输出

```
YES
NO
YES
NO
YES
YES```

# 题解

## 作者：Larryyu (赞：4)

## _Description_
数列 $a$ 最开始只有一个数 $1$，你可以进行若干次操作，每次操作你可以选取 $k$ 个数（$k$ 无限制，小于等于 $a$ 的大小即可），将这 $k$ 个数的和放入 $a$ 的任意一个位置。

给定一个长度为 $n$ 的序列 $c$，问 $a$ 能否在进行若干次操作后转为 $c$。

有 $t$ 组数据。
## _Solution_
若当前进行了一次操作，则新加入的数大于当前最小的数（$k=1$），小于当前所有数的总和（$k=n$），所以我们对目标数列从小到大排序，若当前的数小于前面所有数的总和，说明这个数是可以实现的否则就不可能实现。

注意：目标序列至少要有一个 $1$。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int a[5050];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read();
	ll sum=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n);
	if(a[1]!=1){ //如果最小的不是1，说明该序列没有1（不可能有非正数）
		cout<<"NO"<<endl;
		return;
	}
	sum=1;
	for(int i=2;i<=n;i++){
		if(a[i]>sum){ //如果大于前缀和，则不可能实现
			cout<<"NO"<<endl;
			return ;
		}
		sum+=a[i];
	}
	cout<<"YES"<<endl;
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Flanksy (赞：4)

# bitset

------------

最开始序列 $a$ 中仅有一个 $1$。

由于可以在 $a$ 中任意选择任意数量的数、拼出的数可以插入任何位置，考虑贪心，对序列 $c$ 从小到大排序，判断首位是否为 $1$，不为 $1$ 显然无法从 $a$ 获得。

初步检查之后将 ```bitset``` 下标为 $1$ 的位赋 $1$，其余置 $0$。

从小到大枚举 $c$ 中元素，判断其在 ```bitset``` 中的对应的位是否为 $1$，若不为 $1$ 则无法从 $a$ 中获得该元素，也就说明 $c$ 序列无法从 $a$ 获得。

若其值为 $1$，需要将所有能够拼出的值加上这个数，此时 ```bitset``` 中所有可以被拼出的值下标处为 $1$，不可被拼出的值下标处为 $0$。

从小到大枚举 $c$ 中元素，若当前枚举到的元素为 $c_i$，将 ```bitset``` 与其自身左移 $c_i$ 位后的值进行按位或运算即可更新所有能够被拼出的数，具体实现见代码。

由于序列长度 $n$ 与值域 $V$ 同阶，时间复杂度 $O(n^2/w)$，其中 $w=32$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,c[5005];
bitset<5004> s;
void deal(){
	cin>>n,s.reset();//清空bitset
	for(int i=1;i<=n;i++) cin>>c[i];
	s[1]=1,sort(c+1,c+n+1);
	if(c[1]!=1) return cout<<"NO\n",void();//简单判定
	for(int i=2;i<=n;i++)
		if(s[c[i]]) s|=s<<c[i];//左移后按位或 
		else return cout<<"NO\n",void();
	cout<<"YES\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	for(cin>>T;T;T--) deal();
	return 0;
}
```

---

## 作者：ダ月 (赞：1)

### 题意概要：

给定长度为 $n$ 的序列 $a_i$。现在有一个初始序列 $\{1\}$。每次操作可以选择当前序列的任意一个子序列，然后进行求和，求和后的数字可以加入任何一个位置。问初始序列是否可以经过有限次操作变成 $a_i$。

### 题目分析：

将 $a_i$ 从小到大排序。先考虑暴力，当前集合已经有 $x$ 个元素，进行搜索，看是否存在一个子序列和为 $a_{x+1}$。时间复杂度：$O(n2^n)$。显然任何一个任务都不能通过。

我们可以把题目抽象成如下：对于当前集合已经有了 $a_i$ 的前 $x$ 的数，当前集合中每个数最多使用一次，可以不使用。是否取其中一部分数字，和为 $a_{x+1}$。显然，这是一个经典的 01 背包问题。即 $f_i$ 表示当前 i 这个数字是否取得到，考虑转移 $f_{i}=\operatorname{or}f_{i-a_j}$,$1\le j\le x$ 且 $i\ge a_j$。对于每个 $x$ 都重新转移的话，时间复杂度：$O(n^3)$。($a_i$ 与 $n$ 同阶)

我们对于每个 $x$，我们只用重新对 $a_x$ 转移一遍 $f_i$ 即可，因为前面能够取到的，当前也能取得到。时间复杂度：$O(n^2)$。能通过 Easy Version。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
const int N=5e3+10;
int a[N];
bool w[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;int tem=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1)tem++;
		}
		sort(a+1,a+n+1);
		memset(w,false,sizeof(w));
		if(n==1){puts(a[1]==1?"YES":"NO");continue;}
		if(n==2){puts(tem==2?"YES":"NO");continue;}
		if(tem<2){puts("NO");continue;}
		w[1]=true;bool flag=true;
		for(int i=2;i<=n;i++){
			if(!w[a[i]]){
				flag=false;
				break;
			}
			for(int j=5000;j>=a[i];j--)
				w[j]|=w[j-a[i]];
		}puts(flag?"YES":"NO");
	}return 0;
}
```

注意到能取到的元素容易被转移很多次。这里只需要一个打表，或者有敏锐的直觉，你可以猜到一个结论：对于任意正整数 $x$，如果满足 $\sum_{i=1}^{x-1}a_i\ge a_x$，那么初始序列能够经过若干次操作变成 $a_i$。

证明先咕一下，打表结果如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/1hdzmwev.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

![](https://cdn.luogu.com.cn/upload/image_hosting/386pg0dl.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

上面是 $n=4,a=\{1,1,2,4\}$ 的情况，下面是 $n=5,a=\{1,1,2,3,7\}$ 的情况。

所以有了这个代码以后，只要求出 $a_i$ 的前缀和就行。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
typedef long long ll;
int n;
const int N=2e5+10;
ll a[N],s[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;int tem=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
		if(a[1]!=1){puts("NO");continue;}
		bool flag=true;
		for(int i=2;i<=n;i++)
			if(s[i-1]<a[i]){
				flag=false;
				break;
			}
		puts(flag?"YES":"NO");
	}return 0;
}
```

时间复杂度：$O(n)$。


---

