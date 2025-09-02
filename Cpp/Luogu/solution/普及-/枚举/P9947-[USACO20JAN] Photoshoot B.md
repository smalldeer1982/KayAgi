# [USACO20JAN] Photoshoot B

## 题目描述

Farmer John 在给他编号为 $1\ldots N$ 的 $N$ 头奶牛排队拍照（$2\le N\le 10^3$）。FJ 一开始计划从左向右数第 $i$ 个位置排编号为 $a_i$ 的奶牛，他在一张纸上写下了排列 $a_1,a_2,\ldots,a_N$。不幸的是，这张纸刚刚被 Farmer Nhoj 偷走了！

幸好 FJ 仍然有机会恢复他之前写下的排列。在这张纸被偷走之前，Bessie 记录了序列 $b_1,b_2,\ldots,b_{N−1}$，对于每一个 $1\le i<N$ 满足 $b_i=a_i+a_{i+1}$。

基于 Bessie 的信息，帮助 FJ 恢复可以产生序列 $b$
的“字典序最小”的排列 $a$。排列 $x$ 字典序小于排列 $y$，如果对于某个 $j$，对于所有 $i<j$ 均有 $x_i=y_i$，且有 $x_j<y_j$（换句话说，这两个排列到某个位置之前都相同，在这个位置上 $x$ 小于 $y$）。保证存在至少一个满足条件的 $a$。 

## 说明/提示

### 样例解释 1

$a$ 能够产生 $b$，因为 $3+1=4$，$1+5=6$，$5+2=7$，$2+4=6$。

### 测试点性质

 - 测试点 $2-4$ 满足 $N\le 8$。
 - 测试点 $5-10$ 没有额外限制。

## 样例 #1

### 输入

```
5
4 6 7 6```

### 输出

```
3 1 5 2 4```

# 题解

## 作者：Luogu_916767 (赞：4)

[In Luogu](https://www.luogu.com.cn/problem/P9947)

### 题目大意

给出一个 $n-1$ 位的序列 $b_{1},b_{1},b_{1},\dots,b_{n-1}$。求一个序列 $a$，使 $a_{i} + a_{i+1} = b_{i}$。

### 思路分析

观察题目数据范围，可以发现其实 $n$ 并不是特别大。不难发现，只要我们知道这个序列中任何一位，就可以推出整个序列。所以，我们可以枚举第一位，并验证是否符合题目要求，最后只要找到一个符合要求的，直接输出答案就好（保证存在至少一个满足条件的 $a$）。

### 具体实现

除了判断是否合法之外就没什么难的了吧？

#### 判断是否合法

```cpp
bool flag = 1;
for(int j = 1; j <= n; j ++ ){
	if(!mp[j]){
		flag = 0;
		break;
	}
}
if(flag){
	for(int j = 1; j <= n; j ++ ){
		cout<<ans[j]<<" ";
	}
	return 0;
}
```

#### 提示

不要忘记每次检查完之后要把 $mp$ 全部清空。

综上。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
int a[1001];
int ans[1001];
map<int,bool> mp;

int main(){
	cin>>n;
	for(int i = 1; i < n; i ++ ){
		cin>>a[i];
	}
	for(int i = 1; i < a[1]; i ++ ){
		ans[1] = i;
		mp[i] = 1;
		for(int j = 2; j <= n; j ++ ){
			ans[j] = a[j-1] - ans[j-1];
			mp[ans[j]] = 1;
		}
		bool flag = 1;
		for(int j = 1; j <= n; j ++ ){
			if(!mp[j]){
				flag = 0;
				break;
			}
		}
		if(flag){
			for(int j = 1; j <= n; j ++ ){
				cout<<ans[j]<<" ";
			}
			return 0;
		}
		for(int j = 1; j <= n; j ++ ){
			mp[j] = 0;
		}
	}
}
```

---

## 作者：DFs_YYDS (赞：2)

# 题目大意
给定一个长度为 $n$ 的数列 $a$ 的相邻两个数字两两相加的结果数组 $b$，让你求出字典序最小的 $a$，并且 $a$ 包含 $1\sim n$ 所有的数（也就是说每个数都只出现一次）。
# 具体思路
首先我们发现，如果确定了 $a$ 的第一个数字，那后面的数字就都能确定下来了，然后又因为由于题目要求是字典序最小，所以从最小的 $1$ 开始枚举第一个数字。

根据第一个数字来通过 $b$ 数组推出整个数组，如果这个数组符合要求，就输出它，不然就继续循环。
# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005]/*原数组*/,b[1005]/*原数组相邻两个数两两相加的和*/,n/*原数组长度*/;
bool check(int i){//检查函数。 
	bool vis[1005];//vis[i]表示i在构造的数组中是否出现。 
	memset(vis,false,sizeof(vis));//初始化，一开始都没出现。 
	a[1]=i;//第一个数是i。 
	for(int i=2;i<=n;i++){//根据第一个数和b构造整个a数组。 
		a[i]=b[i-1]-a[i-1];//最重要的一行，这行看不懂这题就不会。 
		if(vis[a[i]]/*这个数之前已经出现过了*/ || a[i]>n/*这个数比n大*/ || a[i]<1/*这个数比1小 （虽然数据中应该不会出现，但还是写了保险）*/)return false;//无法构造，返回false。 
		vis[a[i]]=true;//将这个数标记为出现过了。 
	}
	return true;//构造成功，返回true。 
}
int main(){
	cin>>n;//输入n。 
	for(int i=1;i<n;i++)cin>>b[i];//输入b数组，注意是i<n而不是i<=n。 
	for(int i=1;i<=n;i++){//循环第一个数。 
		if(check(i)/*检查*/)break;//如果能构造，跳出循环。 
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";//输出a数组。 
	return 0;//好习惯
}
```

---

## 作者：Officer (赞：2)

[题目穿送门](https://www.luogu.com.cn/problem/P9947)

模拟水题，有手就行。

先模拟 $a_1$，然后，根据 $b_j$ 推出 $a_j$，为了方便，我们可以用一个桶，来帮助判断。

要求字典序最小，一旦发现了合理的序列，就直接输出，此时的字典序一定是最小的。

方法详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[1005],a[1005];
bool vis[1005];//桶 
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(i+i==n||i>n)
		{
			continue;
		}
		memset(vis,0,sizeof(vis));
		a[1]=i;
		vis[i]=1;
		bool flag=0;
		for(int j=1;j<=n-1;j++)
		{
			a[j+1]=b[j]-a[j];//推序列 
			if(a[j+1]<1)//a[j+1]<1,不合法 
			{
				flag=1;
				break;
			}
			if(a[j+1]>n)//a[j+1]>n,不合法 
			{
				flag=1;
				break;
			}
			if(vis[a[j+1]])//用过,不合法 
			{
				flag=1;
				break;
			}
			vis[a[j+1]]=1;
		}
		if(!flag)//输出 
		{
			for(int i=1;i<=n;i++)
			{
				cout<<a[i]<<" ";
			}
			return 0;
		}
	}
    return 0;
}
/*
*/

```

---

## 作者：lbh666 (赞：1)

题意比较好理解，这里就不多说了。

## 思路

既然 $b_i$ 可以表示为 $a_i$ 和 $a_{i+1}$ 之和，那么我们只需枚举 $a_1$ 的值，就能反推出 $a$ 数组的所有值。

- 举个例子，我们有 $b_1 = a_1 + a_2$，其中，$b_1$ 与 $a_1$ 已知，$a_2$ 就能被求出来。同理，我们由 $b_2 = a_2 + a_3$ 可以求得 $a_3$ 的值，以此类推。实际上就是一个递推的过程。

- 判定是否合法直接用桶记录即可。

- 注意，$a_1$ 的值要从 $1$ 枚举到 $b_1 - 1$，因为要给 $a_2$ 预留至少 $1$。另外在计算 $a_i$ 时，如果算出了负数，就不能加进桶里，桶的下标不能为负数。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;

const int N=1e4+5;
int n;
int a[N],b[N];
bool vis[N];//桶 

bool check(){//判定是否合法 
	int tot=0;
	for(int i=1;i<=n;++i){
		if(!vis[i])return 0;
	}
	return 1;
}

signed main(){
	cin>>n;
	for(int i=1;i<n;++i)cin>>b[i]; 
	for(int i=1;i<b[1];++i){//枚举a[1]的值 
		memset(vis,0,sizeof(vis)); //清空桶 
		a[1]=i;
		vis[a[1]]=1;
		for(int j=2;j<=n;++j){//递推求解a[i] 
			a[j]=b[j-1]-a[j-1];
			if(a[j]>0)vis[a[j]]=1;//是否是正整数的特判 
		}
		if(check()){//找到解，输出 
			for(int i=1;i<=n;++i)cout<<a[i]<<" ";
			break;
		}
	}
	return 0;
}

```

---

## 作者：longlinyu7 (赞：1)

# 题目分析

易知，只要我们知道了 $a$ 序列中的任意一个值，我们就可以通过 $b$ 序列来求出 $a$ 序列的所有值。

假设我们知道了 $a_1$ 那么就可以顺利推出整个序列的值。如何求出 $a_1$ 呢，可以顺次枚举，范围是 $1 \le a_1 \le b_i-1$。

此外我们还需要验证这个序列是否是正确的，因为 $a$ 序列是一个关于 $N$ 的排列，那么从 $1$ 到 $N$ 的所有数都只能出现一次，可以用一个桶记录一下。

至于要求字典序最小，可以从 $1$ 开始枚举，一旦发现了合理的序列，就直接输出，此时的字典序也是最小的。

# 代码
```
#include<bits/stdc++.h>
using namespace std;
#define ll  long long
const int N=4e3+5;
int a[N],n,b[N],ton[2*N];
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>b[i];
	}
	for(int i=1;i<b[1];i++){
		if(i+i==b[1]||i>n)continue;
		memset(ton,0,sizeof(ton));
		ton[i]++; // 记录第一个数
		int x=i;
		bool flag=0;
		for(int j=1;j<n;j++){
			if(b[j]-x<=0){
				flag=1;break;
			}
			ton[b[j]-x]++;
			if(b[j]-x<=0||ton[b[j]-x]!=1){
				flag=1;
				break;
			}
			else{
				x=b[j]-x;
				if(x<=0||x>n){
					flag=1;
					break;
				}
			}
		}

		if(!flag){
			x=i;
			for(int j=1;j<=n;j++){
				cout<<x<<" ";
				if(j!=n)x=b[j]-x;	
			}
		}

	}


    return 0;
}

```

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9947)

思路来源于官方题解。

## 思路

对于每一个 $1\sim N$ 的 $i$，我们可以先尝试使 $a_1=i$，对于其他的 $2\le i\le N$，我们可以使 $a_i=b_{i-1}-a_{i-1}$，如果 $a$ 数组中的所有元素没有重复，那么这就是答案，时间复杂度 $O(n^2)$。

```cpp
#include <iostream>
using namespace std;
int b[1000010], d[1000010], ans[1000010];
bool used[1000010];
int main()
{
    int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) cin >> b[i];
	for (int i = 2; i < n; i++) d[i] = b[i-1] - b[i-2];
	for (int a = 1; a <= n; a++) {
		ans[0] = a, ans[1] = b[0] - a;
		for (int i = 2; i < n; i++) ans[i] = ans[i-2] + d[i];
		for (int i = 1; i <= n; i++) used[i] = false;
		bool bad = false;
		for (int i = 0; i < n; i++) {
			if (used[ans[i]] || ans[i] <= 0 || ans[i] > n) {
				bad = true;
				break;
			}
			used[ans[i]] = true;
		}
		if (!bad) {
			for (int i = 0; i < n; i++)
				cout << ans[i] << " ";
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：Kle1N (赞：1)

首先，根据题目条件容易得出，只要知道了任何一个 $a_i$，就可以通过序列 $b$，推出所有 $a_i$。

根据这个性质，我们可以通过枚举一个 $a_i$ 从而得到整个序列 $a$，再判断其是否满足题意即可。

那么我们该枚举哪个 $a_i$ 呢？

由于题目要求答案应满足字典序最小，所以我们可以从小到大枚举 $a_1$。因为 $a_1$ 确定，序列 $a$ 也相应地唯一确定，所以若构造出的序列满足题意，则此时的 $a_i$ 就是最小的，序列的字典序自然也就最小了。

那么枚举的范围是？

依题意得，序列 $a$ 是 $N$ 的一个排列，那么 $a_i$ 就都是 $1$ 到 $N$ 的正整数，由此易得 $a_1$ 的范围为 $1 \le a_1 \le b_1-1$。

除此之外，还要判断生成的序列 $a$ 是否满足题意。字典序的问题前面已经解决了，还有一个问题就是这个序列 $a$ 是否满足是 $N$ 的排列。既然是 $N$ 的排列，那就应满足在序列 $a$ 中，$1$ 到 $N$ 每一个数都出现且仅出现一次。所以建一个桶，把所有 $a_i$ 全部扔进桶里再判断一下是否有重复或漏掉即可。

具体看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,b[1005],a[1005];
bool v[1005],f;
bool check(){
	for(int i=1;i<=n;i++){
		if(!v[i]){
			return false;
		}
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>b[i];
	}
	for(int i=1;i<b[1];i++){
		memset(v,0,sizeof(v));
		v[i]=1;
		a[1]=i;
		f=1;
		for(int j=2;j<=n;j++){
			if(b[j-1]-a[j-1]<=0){
				f=0;
				break;
			}
			a[j]=b[j-1]-a[j-1];
			if(v[a[j]]){
				f=0;
				break;
			}
			v[a[j]]=1;
		}
		if(f && check()){
			break;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：Rubedo_N (赞：0)

# 题解：P9947 [USACO20JAN] Photoshoot B
## 思路
构造题。  

先确定 $a$ 的第一个数字，则后面的数字就都能由其前一位确定。因此枚举 $a$ 的第一个数字（从 $1$ 开始）。

根据数组 $a$ 第一个数字和 $b$ 数组推出整个 $a$ 数组。如果这个数组符合要求，就输出数组 $a$。否则继续枚举 $a$ 的第一个数字。
## AC Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int b[1010],a[1010];
map<int,bool> mp;
signed main(){
	cin>>n;
	for(int i=1;i<n;i++)cin>>b[i];
	for(int i=1;i<b[1];i++){//枚举第一位 
		a[1]=i;//赋值数组第一位 
		mp[i]=true;//答案中有i 
		for(int j=2;j<=n;j++){
			a[j]=b[j-1]-a[j-1];//根据前一位确定后一位 
			mp[a[j]]=true;//答案中有a[j] 
		}
		bool flag=true;
		for(int j=1;j<=n;j++){
			if(!mp[j]){//答案中没有j 
				flag=false;//不符合要求 
				break;
			}
		}
		if(!flag)mp.clear();//不符合要求 
		else {//符合要求 
			for(int j=1;j<=n;j++)cout<<a[j]<<" ";//输出 
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：red_moon (赞：0)

## 题目分析
就是一道简单的模拟题，$a$ 和 $b$ 两个数组+一个桶即可轻松解决。可以用二分答案，这里用纯模拟解决。

## 具体思路
当 $a$ 数组的第一个值求出以后，$b$ 的各项即可求出。应为是模拟，所以我们不需要用判断函数，直接用桶代替就行啦。**要注意 $a$ 数组和 $b$ 数组之间求值时的递推表达式**，详细见代码。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],b[1005],t[1005];
int main() {
	int n;
	cin >> n;
	for(int i=1;i<n;i++)
		cin >> b[i];
	for(int i=1;i<b[1];i++)
	{
		a[1]=i;
		for(int j=1;j<n;j++)
			a[j+1]=b[j]-a[j]; //注意了
		int flag=0;
		memset(t,0,4020); //及时清空是好习惯
		for(int k=1;k<=n;k++)
		{
			if(a[k]<=0||a[k]>n)
			{
				flag=1; //标记状态
				break; //要记得退出哟
			}
			t[a[k]]++;
		}
		for(int m=1;m<=n;m++)
		{
			if(t[m]>1)
				flag=1;
		}
		if(flag)
			continue;
		else
			break;
	}
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	return 0;
}
``````

 _完结撒花_

---

## 作者：qlqaq (赞：0)

### P9947 [USACO20JAN] Photoshoot B题解
纯模拟！

在 $a _ {1}$ 算出来之后，我们就可以通过 $b$ 数组可以求出以后 $a$ 数组的所有元素。

要判断是否为排列，我们可以使用一个 $vis$ 做桶，为了保证字典序最小，我们可以从 $1$ 开始枚举，每次枚举前要清空一下 $vis$ 数组，最后使用 check 函数判断一下是否为排列。

一旦找到正解，立马输出。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,b[1005],a[1005];
bool vis[1005],f;
bool check(){
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			return false;
		}
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>b[i];
	}
	for(int i=1;i<b[1];i++){
		memset(vis,0,sizeof(vis));
		vis[i]=1;
		a[1]=i;
		f=1;
		for(int j=2;j<=n;j++){
			if(b[j-1]-a[j-1]<=0){
				f=0;
				break;
			}
			a[j]=b[j-1]-a[j-1];
			if(vis[a[j]]){
				f=0;
				break;
			}
			vis[a[j]]=1;
		}
		if(f&&check()){
			break;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

# 题意

给定 $b_1$ 至 $b_{n-1}$，求出字典序最小的   $a_1$ 
至 $a_n$，使得任意的 $b_i=a_i+a_{i-1}$。

# 思路

我们可以发现，只要确定 $a_1$ 的大小，便可以推出后边的 $n - 1$ 项，例如 $a_2 = b_1 - a_1 $ ， $ a_3 = b_2 - a_2 $ 等。



------------
## 注意：
1. a 数组中不能有重复的元素。

#### 解决办法：将每个元素放进桶里判定一下有没有重复即可。
 
2. 数组 a 中的所有元素必须为正整数，因为放进桶里判定时，会出现负数下标，导致越界。



------------


数据很小，$O(n^2)$ 可以通过。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std ;
int main (){
    int n , arr[10100] = {} , maxn = -1234567;
    cin >> n ;
    for ( int i = 1 ; i < n ; i++ ){
        cin >> arr[i] ;
        maxn = max ( maxn , arr[i] ) ;
    }
    int a[10100] = {} ;
    for ( int k = 1 ;; k++ ){
         bool flag = 0 , c = 0 ;
         int br[10100] = {} ;
         int cnt = 0 ;
         a[1] = k ;
         for ( int l = 2 ; l <= n ; l++ ){
             a[l] = arr[l - 1] - a[l - 1] ;
         }
         for ( int j = 1 ; j <= n ; j++ ){
             br[a[j]]++ ;
             if ( arr[j] == a[j] + a[j + 1] ) cnt++ ;
             if ( a[j] < 1 ) cnt-- ;// 其中a[j]非正整数，该方案过滤掉。
         }
        for ( int j = 1 ; j <= maxn ; j++ ){
            if ( br[j] > 1 ) c = 1 ;// 有重复的元素。
        }
        if ( c ) continue ;
        if ( cnt == n - 1 ) break ;// 找到了字典序最小的解。
    }
    for ( int i = 1 ; i <= n ; i++ ){
        cout << a[i] << " " ;
    }
    return 0 ;
}
```

---

## 作者：JOKER_chu (赞：0)

### 题意

你要构造一个长度为 $n$ 的 $1 \dots n$ 排列，并使每个 $1 \leq i < n$ 都有 $b_i = a_i + a_{i+1}$。并使得其字典序最小。

### 部分分思路

我们发现，这个序列唯一不好解的就是 $b_i$ 它代表了两个数。

特别的：对于测试点 $2,3,4$，我们可以用 `next_permutation` 来枚举全排列，由于康托展开的字典序顺序，所以我们可以将每一个排列 $O(n)$ 检查一遍，输出第一个合法的即可。

### 解法

我们发现，我们只要知道了 $a_1$，那么通过 $b_1 = a_1 + a_2$，也就可以知道 $a_2$，同理，可以一直这样推到 $a_n$，我们又知道这个数列的最大项不超过 $n$，因为其是一个 $1 \dots n$ 的排列。所以 `for` 循环枚举 $a_1$，然后递推出整个数列，随后检查即可。时间复杂度 $O(n^2)$。对于 $n \leq 10^3$ 可以通过。

### 代码

```cpp
#include <iostream>

#include <cmath>

#include <algorithm>

#include <climits>

#define endl '\n'

using namespace std;

const int hutao = 1e3 + 5;

int n, a[hutao], ans[hutao];
bool v[hutao];

bool function1(int x){
	int b[hutao];
	for(int first = 1; first < n; ++first){
		b[first] = a[first];
	}
	fill(v + 1, v + n + 1, 0);
	fill(ans + 1, ans + n + 1, 0);
	b[1] -= x;
	ans[1] = x;
	v[ans[1]] = 1;
	for(int first = 2; first < n; ++first){
		ans[first] = b[first - 1];
		b[first] -= b[first - 1];
		if(b[first] < 0 || v[ans[first]] == 1 || ans[first] == 0){
			return 0;
		}
		v[ans[first]] = 1;
	}
	ans[n] = b[n - 1];
	if(v[ans[n]] == 1 || ans[n] == 0){
		return 0;
	}
	return 1;
}

int main(){
	cin >> n;
	for(int first = 1; first < n; ++first){
		cin >> a[first];
	}
	for(int first = 1; first <= n; ++first){
		if(function1(first) == 1){
			for(int second = 1; second <= n; ++second){
				cout << ans[second] << " ";
			}
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：卷王 (赞：0)

我们发现如果我们确定了 $a_1$，那么后面就可以依次推出。那么直接枚举 $a_1$ ，并用 $vis$ 数组判断即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int a[1000007];
bool flag = 0;
bool vis[100007];
int b[100007];

signed main() {
	n = read();
	up(i, 1, n - 1) {
		a[i] = read();
	}
	for (int i = 1; i <= a[1] - 1; i++) {
		memset(vis, 0, sizeof(vis));
		b[1] = i;
		vis[i] = 1;
		bool ok = 1;
		for (int j = 1; j <= n - 1; j++) {
			b[j + 1] = a[j] - b[j];
			if(b[j + 1] <= 0) {
				ok = 0;
				break;
			}
			if (!vis[b[j + 1]]) vis[b[j + 1]] = 1;
			else {
				ok = 0;
				break;
			}
		}
		if (!ok) continue;
		for (int j = 1; j <= n; j++)
			if (vis[j] == 0) ok = 0;
		if (ok == 1) {
			for (int j = 1; j <= n; j++)
				printf("%lld ", b[j]);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

### $Part.1$ 题目大意

给定 $n$ 和 $b_1$，$b_2$，$\ldots$，$b_{n-2}$，$b_{n-1}$，请求出**字典序最小**的序列 $a_1$，$a_2$，$\ldots$，$a_n$，对于每一个 $1\le i<n$ 都必须满足 $b_i = a_i + a_{i+1}$，且序列 $a$ 是 $1\ldots n$ 的**排列**。

### $Part.2$ 解题方案

这里提供一种 $O(n^2)$ 的方法。

因为序列 $a$ 是 $1\ldots n$ 的排列，所以最大的数字是 $n$。

用第一重循环枚举**第一个数**。

题目给定：$a_i + a_{i+1} = b_i,1\le i\le n$。我们不难发现 $a_{i+1} = b_i - a_i,1\le i\le n$。

所以可以用第二重循环算出剩下 $a_i$（$2\le i\le n$）的值。

用一个 $vis$ 数组存储数字是否重复。

- 如果发现有重复，哨兵变 $0$，结束循环。

- 否则将这个数标记为 $1$（标记出现过）。

最后如果哨兵为 $1$，那么**直接输出方案**，结束程序。


------------

为什么不用比字典序？

因为这时 $a_1$ 已经**达到最小**，后面的数字是根据 $a_1$ 来推算，所以知道了 $a_1$，就能知道后面的数。因此不用比较。



------------

代码（其中 $b_i$ 变成了 $a_i$，$a_i$ 变成了 $num_i$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,x,y) for(ll i=x;i<=y;i++)
const ll N=1005;
bool flag;
ll n,a[N],num[N],vis[N];
int main(){
	cin>>n;
	FOR(i,1,n-1) cin>>a[i];
	FOR(i,1,n){
		memset(vis,0,sizeof(vis));//时时清零。
		num[1]=i;vis[i]=1;//标记。
		flag=1;//不要忘了。
		FOR(j,1,n-1){
			num[j+1]=a[j]-num[j];//推算 num[j]。
			if(vis[num[j+1]]){//如果已经存在。
				flag=0;break;//不符合条件。
			}
			vis[num[j+1]]=1;//标记。
		}
		if(flag){//满足条件。
			FOR(i,1,n)
				cout<<num[i]<<" ";
			exit(0);
		}
	}
    return 0;
}
```

然而正当你开心地提交了代码，却：

![](https://cdn.luogu.com.cn/upload/image_hosting/nu9xcy5p.png)

~~五彩斑斓的错误。~~

这是为什么？

那是因为可能减出来的 $a_j$ 会有**小于等于 $0$** 或者**超过 $n$** 的情况。

因此要特判。

AC code
------------

跟上面的代码多了一点，其余的都一样。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,x,y) for(ll i=x;i<=y;i++)
const ll N=1005;
bool flag;
ll n,a[N],num[N],vis[N];
int main(){
	cin>>n;
	FOR(i,1,n-1) cin>>a[i];
	FOR(i,1,n){
		memset(vis,0,sizeof(vis));
		num[1]=i;vis[i]=1;
		flag=true;
		FOR(j,1,n-1){
			num[j+1]=a[j]-num[j];
			if(num[j+1]<1||num[j+1]>n){//发现有不符合题意的数，需要特判。
				flag=false;break;
			}
			if(vis[num[j+1]]){
				flag=false;break;
			}
			vis[num[j+1]]=1;
		}
		if(flag){
			FOR(i,1,n)
				cout<<num[i]<<" ";
			exit(0);
		}
	}
    return 0;
}
```


---

## 作者：Arson1st (赞：0)

## [P9947 [USACO20JAN] Photoshoot B](https://www.luogu.com.cn/problem/P9947) 题解

### 差分+枚举

题目给出了排列中每相邻两数的和（即为 $b$ 数组），现需反推出原数组 $a$。通过关系 $b_i=a_i+a_{i+1}$，我们可以有如下结论：一旦确定 $a_1$ 的值（譬如设为 $x$），那么有 $a_2=b_1-x,a_3=b_2-(b_1-x),\cdots$ 这样循环嵌套的式子。将括号展开并合并常数项，记每一项化简后的常数项为 $c_i$，那么 $a$ 数组可以表示成 $a_i=c_i+(-1)^{i+1}x$ 的形式。我们可以先通过类似差分的方法 $O(n)$ 预处理出 $c$ 数组。譬如 $b=[4,6,7,6]$（下标从 $2$ 开始），那么 $c=[0,4,2,5,1]$（下标从 $1$ 开始）。

不难发现 $1\sim n$ 项中 $x$ 的系数是 $+1,-1,+1,-1,\cdots$ 这样分布的。接下来有一个小分讨：

- 如果 $n$ 是奇数，那么 $a_2$ 与 $a_3$，$a_{2i}$ 与 $a_{2i+1}$ 项两两相加就能抵消它们的 $x$，只剩下 $a_1$ 带有一个 $x$。注意到 $a$ 数组是 $1\sim n$ 的一个排列，于是有 $\displaystyle \sum_{i=1}^na_i=x+\displaystyle\sum_{j=2}^nc_j=\displaystyle\sum_{k=1}^nk=\frac{n\times (n+1)} 2$。这意味着我们在预处理时只需记录下 $c$ 数组的和即可做差得到定值 $x$。最后由 $a_i=c_i+x$ 依次输出即可。
- 如果 $n$ 是偶数，此时 $x$ 不再是一个定值，因为两两相消后只能得到 $\displaystyle \sum_{i=1}^na_i=\displaystyle\sum_{j=2}^nc_j$。是不是一筹莫展了？但是数据范围贴心的给到了 $10^3$，那还犹豫什么？暴力枚举啊！每次花费 $O(n)$ 代价验证是否合法（有无重复项或 $1\sim n$ 范围外的项）即可。当然可以加上一个小优化，即在预处理 $c$ 数组时通过 $c_{2i+1}+x\le n,c_{2i+1}+x\ge1$ 得到 $x\le n-c_{2i+1},x\ge 1-c_{2i+1}$，通过 $c_{2i}-x\le n,c_{2i}-x\ge 1$ 得到 $x\ge c_{2i}-n,x\le c_{2i}-1$。由此缩小枚举范围的同时保证生成的 $a$ 数组范围上合法，验证时仅判断是否有重复项即可。注意这时涉及字典序最小的问题，所以要求我们从小到大枚举。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+10;

int n, b[N], a[N], sum, mx = 1e9, mn;
bool exi[N];

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i ++)
		scanf("%d", &b[i]);
	for (int i = 2; i <= n; i ++) {//预处理
		a[i] = b[i] - a[i-1]; sum += a[i];
		if (i & 1) {//小优化
			mx = min(mx, n-a[i]);
			mn = max(mn, 1-a[i]);
		}
		else {
			mx = min(mx, a[i]-1);
			mn = max(mn, a[i]-n);
		}
	}
	if (n & 1) {//奇数情况
		sum = n * (n+1) / 2 - sum;//得到 x
		for (int i = 1; i <= n; i ++)
			printf("%d ", (i&1) ? sum + a[i] : a[i] - sum);
	}
	else {//偶数情况
		for (int x = mn, i; x <= mx; x ++) {
			memset(exi, 0, sizeof exi); exi[x] = 1;
			for (i = 2; i <= n; i ++) {
				int tmp = (i&1) ? x + a[i] : a[i] - x;
				if (exi[tmp]) break; exi[tmp] = 1;
			}
			if (i <= n) continue;
			for (int i = 1; i <= n; i ++)
				printf("%d ", (i&1) ? x + a[i] : a[i] - x);
			return 0;
		}
	}
}
```



---

## 作者：__O_v_O__ (赞：0)

此题的主要思想是枚举第一只奶牛，再用桶判断序列合法。

### 具体做法：

因为题目要求字典序最小，所以从小到大枚举第一只奶牛，范围是 $[1,b[1]-1]$。

确定第一只奶牛，显然可以推出 $a$ 序列，此时开始判断 $a$ 序列是否合法。

不合法条件：

1. 序列中有小于零或大于 $n$ 的数。

2. 序列中有重复出现的数。

对于条件一，枚举一遍即可；对于条件二，使用一个桶记录当前数是否出现过。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int n,b[1001],a[1001],m[1001];//定义
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//读入优化
	cin>>n;//输入
	afor(i,1,n-1,STB)cin>>b[i];//输入
	afor(i,1,b[1]-1,STB){
		memset(a,0,sizeof a),memset(m,0,sizeof m);//清空
		a[1]=i;//设置a[1]
		afor(j,2,n,STB)a[j]=b[j-1]-a[j-1];//产生a序列
		bool fl=true;
		afor(j,1,n,STB){
			if(m[a[j]]||a[j]<=0){fl=false;break;}//不合法则跳出
			m[a[j]]++;//桶自增
		}
		if(fl){//判断合法
			afor(j,1,n,STB)cout<<a[j]<<' ';//输出
			return 0;
		}
	}
	return 0;
}
```

---

