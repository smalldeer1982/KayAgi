# [POI 1997] ADDON

## 题目背景

科学家们发现了一种新的放射性元素——`ADDON`。`ADDON` 是已知的效率最高的核燃料，因此他们决定建立一个 `ADDON` 核反应堆。

## 题目描述

根据计划，一间燃料室是一根竖直的管子。燃料棒（即装有 `ADDON` 的圆筒）将一根叠一根的被放进燃料室里，搭建成一个圆柱。燃料棒具有不同的高度。

核反应循环开始于将燃料棒放进燃料室中。接下来的步骤才是点火。麻烦的是，圆柱的高度不能是任意的——只有某些特定的高度才能保证反应的安全。这样的高度被称作稳定高度。

现在，反应堆的设计师们面临着两个任务：确定燃料室的高度以及选择一个用于制造 `ADDON` 的燃料棒的高度集合。

我们说一个高度集合是安全的（对于一个特定高度的燃料室），则有：

- 对于任意一根由高度属于这个集合的燃料棒搭建而成的，且高度不超过燃料室的高度的圆柱，它的高度一定是稳定的。


我们说一个高度集合是完备的（对于一个特定高度的燃料室），则有：

- 对于任意一根高度是稳定的,并且其高度不超过燃料室高度的圆柱，都一定能够由高度属于该集合的燃料棒搭建而成。


现在要写一个程序：
- 1. 读入一个稳定高度的集合；
- 2. 找出存在一个安全且完备的高度集合的核燃料室的最大可能值；
- 3. 对于找到的核燃料室，找出一个元素个数最少的安全且完备的高度集合；
- 4. 将结果输出。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le10000$。

## 样例 #1

### 输入

```
14
5
10
12
15
17
20
21
22
24
26
27
30
31
33```

### 输出

```
24
5
12
21```

# 题解

## 作者：_Violet_Evergarden (赞：13)

闲来无事写一发题解

# 简要题意
这道题就是说我们要找到一个序列中最大的数，然后使序列中小于这个数的数相加都凑不出小于这个数且不在这个序列中的数的数，而且序列中的数可以相互表示。然后我们要找到在最大数的前提下取最少的数量的数。

# 思路
当我们看到序列中不会有大于 $10^4$ 的数时，便很容易可以想到把所有前面选的数能表示的数全部打上标记，在遍历的时候如果在这个数前面有打上标记的数且该数并未出现在序列中就说明现在的数就是最大值，否则判断这个数是否打上标记，如果打上了那就不将它放到答案序列中。因为如果他能被前面的数表示，那么它与前面的数相加能表示的数必然已被打上标记。然后这道题就解决了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000001];
int b[1000001];
int c[1000001];
int d[1000001];
int e[1000001];
int cnt;
int flag;
int xia;
int x;
int p;
int o=100000001;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=d[i-1];j<d[i];j++){
			if(b[j]){
//				cout<<j<<"!"<<endl; 
				o=i-1;
				flag=1;
			}
		}
		if(flag){
			break;
		}
		if(b[d[i]]){
			b[d[i]]=0;
			continue;
		}
		e[++cnt]=d[i];
		for(int j=1;j<i;j++){
			b[d[i]+d[j]]=1;
		}
		for(int j=1;j<=10000;j++){
			if(!b[j]&&(j%d[i])==0){
				b[j]=1;
			}
			if(b[j]==1){
//				cout<<j<<endl;
				b[d[i]+j]=1;
			}
		}
		
		b[d[i]]=0;
	}
	cout<<d[min(o,n)]<<endl;
	for(int i=1;i<=cnt;i++){
		cout<<e[i]<<endl;
	}
	return 0;
}

```


---

## 作者：xixiyan (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P5941)

读了九九八十一分钟的题，终于看懂这道题要干什么了，于是写一发题解来帮助后人。

## 题意翻译

题目会给定一个有 $n$ 个元素的集合 $A$。

接下来你要构造一个从 $A$ 中选择一个元素 $q$，并从小于 $q$ 且属于 $A$ 的数中尽可能少的选择任意个，使得由这些数构成的集合 $S$ 具有“安全性”与“稳定性”。

安全性：任意一个能由 $S$ 内元素组成的，且不大于 $q$ 的数，一定属于集合 $A$。

稳定性：任意 $A$ 中的元素，都能够被 $S$ 内的元素表示

请你输出 $q$ 的最大值以及集合 $S$。

## 题目分析

首先，看到“稳定性”第一时间肯定想到完全背包，又因为题目保证有解，所以可以枚举 $q$。

从最低到最高依次分析，如果上一个数与他之间有可以被前面已加入 $S$ 的数表示的，说明这个 $q$ 一定不合题意，于是直接输出上一个数。

如果上一个数与他之间没有有可以被前面已加入 $S$ 的数表示的，说明这个 $q$ 可行，如果他不能被前面数表示，则将其加入 $S$ ，否则直接跳过。

最后就是大家最喜欢的~~伪~~代码环节（里面有注释）
## Code：


```cpp
#include <bits/stdc++.h>
using namespace std;
int a[10001]; //存高度
bool x[10001]; //判断能否被构成
int anns[1001]; //答案S
int main(){
	
	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	//读入
	int anss=114514;//将q设为一个很大的数,以防答案为最大数
	int tot=0;//S的元素个数
	for(int i=1;i<=n;i++){
		bool p=1;
		for(int j=a[i-1]+1;j<a[i];j++){
			if(x[j]){//存在能被构成的数
				anss=a[i-1];
				p=0;
			}
		}
		
		if(!p) break;

		if(x[a[i]]) continue;//能被构成
		
		anns[++tot]=a[i];//否则加入集合

		for(int j=1;j<i;j++){
			x[a[i]+a[j]]=1;//标记
		}
		
		for(int j=1;j<=10000;j++){
			if(x[j]&&a[i]+j<=10000) x[a[i]+j]=1;
			
			if(!x[j]&&j%a[i]==0) x[j]=1;
            //类似完全背包
		}
	}
	
	cout<<min(anss,a[n])<<'\n';//如果跑完了
	for(int i=1;i<=tot;i++){
		cout<<anns[i]<<"\n";
	}
	return 0;
}
//圆满成功
```

---

## 作者：D23lhc (赞：2)

### 分析
这道题目是一道 01 背包。我们需要找到一个安全且完备的高度集合，使得燃料室的高度最大。
首先，我们需要判断一个高度集合是否安全。对于一个高度集合，我们可以用一个布尔数组 $f$ 来表示，$f[i]$ 表示高度 $i$ 是否可以由该集合中的燃料棒搭建而成。初始时，所有的 $f[i]$ 都为 false。
然后，我们需要找到一个安全且完备的高度集合的燃料室的最大可能值。我们可以从高度 1 开始，逐个判断是否存在一个安全且完备的高度集合。

**时间复杂度分析**：假设稳定高度的个数为 $n$，遍历高度集合的时间复杂度为 $O(n)$，遍历高度集合中的每个元素的时间复杂度为 $O(n)$，因此总的时间复杂度为 $O(n^2)$。
# 代码
```
#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;
int Ans;
bool f[MAXN] = {false};
int a[MAXN];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int O[MAXN], O_size = 0;
    int tot = 1;
    f[a[n-1] + 1] = true;
    for (int i = 1; i <= a[n - 1] + 1; ++ i) 
    {
        if (f[i] && i != a[tot-1]) 
        {
            Ans = a[tot - 2];
            break;
        }
        if (i == a[tot-1]) {
            if (!f[i]) {
                O[O_size++] = i;
                f[i] = true;
            }
            ++ tot;
        }
        if (f[i]) {
            for (int j = 0; j < O_size; ++ j) {
                if (i + O[j] <= a[n-1]) {
                    f[i + O[j]] = true;
                }
            }
        }
    }
    cout << Ans << endl;
    for (int i = 0; i < O_size; ++ i) {
        cout << O[i] << endl;
    }
    return 0;
}
```

---

## 作者：yuxinrui0618 (赞：1)

# 题解：P5941 [POI1997] ADDON
#### 注：借用楼下 forever516 的题解思路
## 1. 题目大意
- 找序列中最大的符合要求的数（保证序列中小于这个数的数相加都凑不出小于这个数且不在这个序列中的数，而且序列中的数可以相互表示）；
- 取最少的数量的数。

## 2. 思路
- 遍历，能选的数字都打标记；
- 如果在这个数前面有被标记的数并且该数没有出现在序列中，记录最大值；
- 没有被标记的数放进答案数组里。

## 3. 代码
上代码！！！

``` cpp
#include<bits/stdc++.h>
using namespace std;
int h[100004],x[100004],ans[100004];
int main()
{
	int n,Max=INT_MAX,f=0,s=0;
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>h[i];
	for (int i=1;i<=n;i++)
	{
		for (int j=h[i-1];j<h[i];j++)
			if (x[j])
			{
				Max=i-1;
				f=1;
			}
		if (f)
			break;
		if (x[h[i]])
			x[h[i]]=0;
		else
		{
			ans[++s]=h[i];
			for (int j=1;j<i;j++)
				x[h[i]+h[j]]=1;
			for (int j=1;j<=10000;j++)
			{
				if (!x[j] && (j%h[i])==0)
					x[j]=1;
				if (x[j]==1)
					x[h[i]+j]=1;
			}
			x[h[i]]=0;
		}
	}
	cout<<h[min(Max,n)]<<endl;	
	for (int i=1;i<=s;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

## 4.总结
谢谢观赏！！！  
若有不完善的地方还请各位大佬指出！！！

---

## 作者：__Luna__ (赞：1)

## 题意简述

介于该题的题面晦涩难懂且部分表述模糊，此处为看不懂题目要求的人概括一下题意：

- 定义一个数 $a$ 可由一个集合集合 $\rm B$ 中的元素组成，当且仅当 $a$ 可以表示为 $\rm B$ 中有限个元素的正整数倍之和。

- 告诉你一个有 $n$ 个元素的集合 $\Omega$，求：

  1. $\Omega$ 中最大的元素 $m$，使得所有可由 $\Omega$ 中的元素组成且不大于 $m$ 数均属于 $\Omega$；

  2. $\Omega$ 中最小的子集 $\rm S$，使得 $\Omega$ 中所有不大于 $m$ 的元素均可由 $\rm S$ 中的元素组成。

注：

- 原题面中并没有要求 $m$ 是 $\Omega$ 中的元素，但是根据测试数据，本题是要求 $m$ 是 $\Omega$ 中的元素的。

## 解答思路

介于题目数据量不大，可以考虑暴力求解。流程如下：

- 准备一个数组，标记从 $1$ 至 $10000$ 的每个整数是否可由 $\Omega$ 中的元素组成。初始时均标记为否。

- 准备另一个数组，记录 $\rm S$ 中的元素。

- 从小到大依次读入 $\Omega$ 中的元素，记为 $\omega$。检查 $\omega$ 的标记：

  1. 若标记为是，则 $\omega$ 不是 $\rm S$ 中的元素；

  2. 若标记为否，则 $\omega$ 是 $\rm S$ 中的一个元素，记录之。同时，将 $\omega$ 标记为是，并检查 $1$ 至 $10000-\omega$ 的所有整数 $z$，若 $z$ 的标记为是，则将 $z+\omega$ 标记为是。
 
- 若 $\omega$ 和 $\Omega$ 中的下一个元素之间存在标记为是的数，则 $\omega$ 就是要求的 $m$。此时已记录的元素即为 $\rm S$ 中的所有元素。

## 示例代码

以下代码仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100000],c;
int t[100001];
int main()
{
	cin>>n;
	for(int i=0,j,k=0;i<n;i++,m=j)
	{
		cin>>j;
		while(k<j)
		{
			if(t[k]==1)
			{
				goto end;
			}
			k++;
		}
		k++;
		if(t[j]==0)
		{
			a[c++]=j;
			t[j]=1;
			for(int l=1;l+j<=10000;l++)
			{
				if(t[l])t[l+j]=1;
			}
		}
	}
	end:
	cout<<m<<endl;
	for(int l=0;l<c;l++)
	{
		cout<<a[l]<<endl;
	}
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 题意

找出一个最大数，使得序列中所有小于它的数相加都没有这个数小，并且不在此序列中的数。

## 思路

由于读入数据很小，只有 $10000$ 可以考虑使用桶标记每个数是否合法，如果有未出现在集合里的数被打上了标记，那么这个数就是最大的数。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep( i , l , r ) for (int i = (l) ; i <= (r) ; i++)
#define per( i , r , l ) for (int i = (r) ; i >= (l) ; i--)

int f[10010] ;
int arr[100010] ;
int n ;
bool flg = 0 ;
int tot ;
int a[100010] ;
int tmp = 0x3f3f3f3f ;
void solve (){
	cin >> n; 
	rep ( i, 1 , n ){
		cin >> a[i] ;
	}
	rep ( i , 1 , n ){
		flg = 0 ;
		rep ( j , a[i - 1] + 1 , a[i] - 1 ){
			if ( f[j] ){
				tmp = a[i - 1] ;
				flg = 1 ;
				break ;
			}
		}
		if ( flg ) break ;
		if ( f[a[i]] ){
			f[a[i]] = 0 ;
			continue ;
		}
		arr[++tot] = a[i] ;
		rep (j , 1 , i - 1){
			f[a[i] + a[j]] = 1 ;
		}
		rep ( j , 1 , 10000 ){
			if ( f[j] && a[i] + j <= 1e4 ){ f[a[i] + j] = 1 ;}
		}
		for ( int j = a[i] ; j <= 1e4 ; j += a[i] ){
			f[j] = 1 ;
		}
	}
	int tt = min ( tmp , a[n] ) ;
	cout << tt << '\n' ;
	rep ( i , 1 , tot ){
		cout << arr[i] << '\n' ;
	}
}

signed main (){
	int _ = 1 ;
	while ( _-- ){solve () ;}
	return 0 ;
}

```

---

## 作者：RockyQ012 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5941)
### 题目大意：
这道题的意思有一点复杂，大概就是找一个数，使得序列中所有小于这个数的数相加都小于这个数，且这个数不在这个序列里。在满足上述条件下取最少的数量的数。
### 题目思路：
#### 遍历加标记！
具体的说，如果在这个数前面有标记过的数并且该数并未出现在序列中，那么现在的数就是最大值。否则判断这个数是否被标记过，如果没有标记过那就将它放到答案序列中，反之就不将其加到序列里面。
### 代码：
~~借鉴了前人代码，因为我之前在这道题上被卡了几十次~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n , a[1000001] , ans[1000001] , cnt , Sum = 100000005;
bool F[1000001] , f; //定义
int main() {
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i]; //输入
    for (int i = 1 ; i <= n ; ++i) {
        for (int j = a[i - 1] ; j < a[i] ; ++j) //遍历
            if (F[j]) {
                Sum = i - 1;
                f = true;
            } // 标记
        if (f) break;
        if (F[a[i]]) {
            F[a[i]] = false;
            continue;
        }
        ans[++cnt] = a[i];
        for (int j = 1 ; j < i ; ++j) F[a[i] + a[j]] = true;
        for (int j = 1 ; j <= 10000 ; ++j) {
            if (!F[j] && (j % a[i]) == 0) F[j] = true;
            if (F[j]) F[a[i] + j] = true;
        } //判断
        F[a[i]] = false;
    }
    cout << a[min(n , Sum)] << endl;
    for (int i = 1 ; i <= cnt ; ++i) cout << ans[i] << endl; //输出
    return 0;
}
```

---

## 作者：forever516 (赞：0)

~~别人写的都有点复杂，我给大家写一个简单易懂的。~~

# 题意
找序列中最大的数，使序列中小于这个数的数相加都凑不出小于这个数且不在这个序列中的数的数。

而且序列中的数可以相互表示。然后我们要找到在最大数的前提下取最少的数量的数。

# 解法
先遍历一遍，把能选的数能表示的数全部打上标记。

在遍历的时候如果在这个数前面有打上标记的数且该数并未出现在序列中就说明现在的数就是最大值。

否则判断这个数是否打上标记，如果打上了那就不将它放到答案序列中。

由此，可得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,a[N],b[N],c[N],d[N],e[N],cnt,f,o=N;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=1;i<=n;i++){
		for(int j=d[i-1];j<d[i];j++){
			if(b[j]){
				o=i-1;
				f=1;
			}
		}
		if(f)break;
		if(b[d[i]]){
			b[d[i]]=0;
			continue;
		}
		e[++cnt]=d[i];
		for(int j=1;j<i;j++)b[d[i]+d[j]]=1;
		for(int j=1;j<=10000;j++){
			if(!b[j]&&(j%d[i])==0)b[j]=1;
			if(b[j]==1)b[d[i]+j]=1;
		}
		b[d[i]]=0;
	}
	cout<<d[min(o,n)]<<"\n";
	for(int i=1;i<=cnt;i++)cout<<e[i]<<"\n";
	return 0;
}
```

---

## 作者：Lcm_simida (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P5941)

这道题的题意有点难懂，读了 $n$ 遍……

## 大概思路

看到不超过一万的整数便想到使用标记数组来记录现在是否可行，一边遍历一边判断，如果有未出现在序列中的数同时塔在这个数前面就说明现在的数就是最大值，否则判断这个数是否打上标记，即可完成此题。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[10005],ans=0,cnt=114514,sum[10005];
bool vis[10005]; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//输入
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		bool v=1;
		for(int j=a[i-1]+1;j<a[i];j++){//判断是否可行
			if(vis[j]){
				cnt=a[i-1];
				v=0;
				break;
			}
		}
		if(v==0) break;
		if(vis[a[i]]) continue;
		sum[++ans]=a[i];//存入答案
		for(int j=1;j<i;j++){
			vis[a[i]+a[j]]=1;
		}
		for(int j=1;j<=10000;j++){//进行连接
			if(vis[j]&&a[i]+j<=10000) vis[a[i]+j]=1;
		}
		for(int j=a[i];j<=10000;j+=a[i]){//还在连接
			vis[j]=1;
		}
	}
	cout<<min(cnt,a[n])<<"\n";//输出答案，防止未更新
	for(int i=1;i<=ans;i++){
		cout<<sum[i]<<"\n";
	}
	return 0;
}
```

---

