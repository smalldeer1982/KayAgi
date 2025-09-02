# 「OICon-02」Pick Stone

## 题目描述

小 S 有一个 $n\times m$ 的棋盘。初始每个位置都有一个棋子。每次，小 S 可以取走一个周围（四连通）被取走棋子数不超过 $1$ 的棋子。求小 S 最多能取走多少棋子，并构造一种合法的取棋子方案。

## 说明/提示

### 样例解释

对于样例 $1$，取出 $(1,1)$ 时周围有 $0$ 个已取出位置，取出 $(1,2),(2,1)$ 时周围有 $1$ 个已取出位置，故原构造符合要求。

容易证明没有更优答案。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ |
|:--:|:--:|:--:|
| $1$ | $n=1$ | $20$ |
| $2$ | $n=2$ | $30$ |
| $3$ | $n=3$ | $50$ |

对于 $100\%$ 的数据：$\bm{1\leq n\leq3}$，$1\leq m\leq10^5$。

如果你答对了第一问最多能取走的棋子数而没有正确地构造，你将获得 $70\%$ 的分值。一个子任务你的得分是所有测试点得分的最小值。注意，你仍需要按格式输出 $n\times m$ 个数表示构造方案，我们推荐你全部输出 $-1$。

保证 `checker.cpp` 在符合格式要求的输出下用时不超过 $0.5$ 秒。

## 样例 #1

### 输入

```
2 2```

### 输出

```
3
1 2
3 -1```

## 样例 #2

### 输入

```
3 5```

### 输出

```
12
2 3 4 5 6
1 -1 12 -1 7
8 9 -1 11 10```

# 题解

## 作者：Mu_shao (赞：5)

### 审题
可以得到一个明确的条件 $1 \le n \le 3$，由此可得，此题核心为**分类讨论**， $n = 1$，$n = 2$，$n = 3$。

### 题解
- $n = 1$

直接**无脑**按序列输出 $1 \sim m$。
#### code
```cpp
if (n == 1) {
	printf("%d\n", m);
	for (int i = 1; i <= m; i++) printf("%d ", i);
}
```


------------

- $n = 2$ 

第一行与 $n = 1$ 时处理方式相同，不做解释。

第二行，单数位沿着第一行继续按序输出，双数位输出 $-1$。

由此可得，总数应当减去第二行 $-1$ 的个数，公式为 $n \times m - m \div 2$

#### code
```cpp
if (n == 2) {
	printf("%d\n", n*m - m/2);
	for (int i = 1; i <= m; i++) printf("%d ", i);
	printf("\n");
   
	int a = m;
	for (int i = 1; i <= m; i++) {
		if (i % 2) printf("%d ", ++a);
		else printf("-1 ");
	}
}
   
```
------------

- $n = 3$ 

第一第二行与 $n = 2$ 时处理方式相同，不过针对特殊情况略作调整。

经过简单的模拟，可以手推出最优情况的模型。
```
1 1 1 1 1 1 1 1 1 1 1 ...
1 0 1 0 1 0 1 0 1 0 1 ...
1 1 0 1 1 1 0 1 1 1 0 ...
```
那模型出来了，空位应该**怎么填**？

观察加推理，得出：

$i ≡ 1 (\bmod 4)$ 时，若 $i \ne 1$， 先取 j，再取 $j - 1$。

$i ≡ 2 (\bmod 4)$ 时，取 j。

$i ≡ 3 (\bmod 4)$ 时，不取。

$i ≡ 0 (\bmod 4)$ 时，不操作，因 $i ≡ 1 (\bmod 4)$ 时已操作。

#### code
```cpp
if (n == 3) {
	int a[m+10][3];
	int cnt = m, t = 0; //t统计数
	for (int i = 1; i <= m; i++) {
		if (i % 2) a[i][1] = ++cnt;
		else a[i][1] = -1;
	}
	for (int i = 1; i <= m; i++) {
		if (i == m && i % 4 == 0) a[i][2] = ++cnt;
		if (i % 4 == 1) {
			a[i][2] = ++cnt;
			if (i != 1) a[i-1][2] = ++cnt;
		} else if (i % 4 == 2) a[i][2] = ++cnt;
		else if (i % 4 == 3) a[i][2] = -1, t++;
	}                             
	
	printf("%d\n", n*m - m/2 - t);
	for (int i = 1; i <= m; i++) printf("%d ", i);
	printf("\n");
	for (int j = 1; j <= 2; j++) {
		for (int i = 1; i <= m; i++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}
```



------------

最后是完整 AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	if (n == 1) {
		printf("%d\n", m);
		for (int i = 1; i <= m; i++) printf("%d ", i);
	}
	if (n == 2) {
		printf("%d\n", n*m - m/2);
		for (int i = 1; i <= m; i++) printf("%d ", i);
		printf("\n");
		int a = m;
		for (int i = 1; i <= m; i++) {
			if (i % 2) printf("%d ", ++a);
			else printf("-1 ");
		}
	}
	if (n == 3) {
		int a[m+10][3];
		int cnt = m, t = 0;
		for (int i = 1; i <= m; i++) {
			if (i % 2) a[i][1] = ++cnt;
			else a[i][1] = -1;
		}
		for (int i = 1; i <= m; i++) {
			if (i == m && i % 4 == 0) a[i][2] = ++cnt;
			if (i % 4 == 1) {
				a[i][2] = ++cnt;
				if (i != 1) a[i-1][2] = ++cnt;
			} else if (i % 4 == 2) a[i][2] = ++cnt;
			else if (i % 4 == 3) a[i][2] = -1, t++;
		}                             
		
		printf("%d\n", n*m - m/2 - t);
		for (int i = 1; i <= m; i++) printf("%d ", i);
		printf("\n");
		for (int j = 1; j <= 2; j++) {
			for (int i = 1; i <= m; i++)
				printf("%d ", a[i][j]);
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：_zSqr_Mahiro_Oyama_ (赞：4)

# P10172 Pick Stone 题解

[题目传送门](https://www.luogu.com.cn/problem/P10172)

### 分析部分：

$\text{Subtask 1}$

按顺序取走即可。取走石子数量为 $m$。

$\text{Subtask 2}$

第一行取完后，第二行从第一个石子开始取，隔一个取一个即可。取走石子数量为 $m+\displaystyle{\lceil \frac{m}{2} \rceil}$。

$\text{Subtask 3}$

构造第三行。

我们先看到第 $2$ 个样例。~~就是出了错的那个~~

输入：

```
3 5
```

我构造的输出：（稍微对齐了一点）

```
12
1  2  3  4  5
6 -1  7 -1  8
9 10 -1 12 11
```

没看懂？再来一组：

输入：

```
3 10
```

我构造的输出：
```
23
1  2  3  4  5  6  7  8  9 10
11 -1 12 -1 13 -1 14 -1 15 -1
16 17 -1 19 18 20 -1 22 21 23
```
发现了什么？

取的棋子像这样分布：（`*`为取的石子，`.`为不取的）

```
**********
*.*.*.*.*.
**.***.***
```

即，先取前两个，隔一个，取三个，隔一个，取三个……

中间的石子上边一定是第二行中的第**奇数**个取到的石子。

取的顺序也有讲究。因为按顺序取的话，取完三个中左边的石子，中间的石子它的左边和上边的石子都被取了，它就不能取了。所以要**先取中间**的石子，再取它左边和右边的石子。

还有若是中间的取不到（在范围之外），左边的能取到，就不要多标记中间的，只要标记左边的那个就可以了。

取走数量为 $2m+\displaystyle{\lceil \frac{m}{4} \rceil}$。（或者，构造完第三行后统计取走数量与第一、二行数量相加，~~如果你不信任我的话。~~）

### 代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100005];//第三行中对应石子是第几个取的，不取为0
int main(){
	cin>>n>>m;
	if(n==1){
		cout<<m<<endl;
		for(int i=1;i<=m;i++)
			cout<<i<<' ';//顺序取走
	}
	if(n==2){
		cout<<m+(m+1)/2<<endl;
		for(int i=1;i<=m;i++)
			cout<<i<<' ';
		cout<<endl;
		int cnt=m+1;
		for(int i=1;i<=m;i++)
			cout<<(i&1?cnt++:-1)<<' ';//隔一个取一个
	}
	if(n==3){
		int cnt=0;//第三行中取到了多少个棋子
		for(int i=1;i<=m+1;i++){//构造，枚举中间石子，枚举到m+1是为了确保中间取不到而左边取得到的情况不被漏掉
			if((i&1)&&(i/2)%2==0){//第三行每组中间的石子必定与第二行中第奇数个取到的石子对齐
				if(i>=1&&i<=m)a[i]=++cnt;//中间
				if(i>1)a[i-1]=++cnt;//左边
				if(i<m)a[i+1]=++cnt;//右边
			}
		}
		cout<<2*m+(m+3)/4<<endl;
		for(int i=1;i<=m;i++)
			cout<<i<<' ';
		cout<<endl;
		for(int i=1;i<=m;i++)
			cout<<(i&1?m+(i+1)/2:-1)<<' ';
		cout<<endl;
		for(int i=1;i<=m;i++){
			if(a[i])cout<<m+(m+1)/2+a[i]<<' ';//前面取了m+(m+1)/2个
			else cout<<-1<<' '; 
		}
	}
} 
```

~~蒟蒻第一篇题解，求管理通过！~~

---

## 作者：luogu10086 (赞：2)

[传送门](https://www.luogu.com.cn/problem/P10172)

整体思路：

因为 $1 \le n \le 3$，所以直接暴力模拟找规律。

$n=1$ 时，$m$ 个棋子都可以取走。

$n=2$ 时，第一行全都取走，第二行就不可以全拿。  
由样例可得，每一个 $2 \times 2$ 的棋盘里最多取 $3$ 颗棋子，很快便可以得出答案。

$n=3$ 时，看样例的样子，可以发现最后一行的顺序不同。  
为了尽可能多取棋子，最后一行取棋顺序为：$1,2,-1,4,3$。  
如果按从左到右的顺序来，那么最后一行最多拿 $3$ 颗棋子。因为在最后一个 $2 \times 2$ 的棋盘中，右下角的棋子将无法拿走。  
手动写出 $m$ 更大时的棋盘，以不同方式取棋，最终发现，第一种取棋方式取走的棋子更多。  
由此可以确定第三行取棋顺序。



------------
代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,mp[5][100010];
signed main(){
    cin>>n>>m;
    if(n==1){//情况一
        cout<<m<<endl;
        for(int i = 1;i <= m;i ++)
        cout<<i<<" ";
    }
    if(n==2){//情况二
        for(int i = 1;i <= m;i ++)
        mp[1][i]=i;
        int flag=m;
        for(int i = 1;i <= m;i += 2)
        mp[2][i]=++flag,mp[2][i+1]=-1;
        for(int i = 1;i <= 2;i ++)
        for(int j = 1;j <= m;j ++)
        if(mp[i][j]!=-1)ans++;//直接数
        cout<<ans<<endl;
        for(int i = 1;i <= 2;i ++){
            for(int j = 1;j <= m;j ++)
            cout<<mp[i][j]<<" ";
            cout<<endl;
        }
    }
    if(n==3){//情况三
        for(int i = 1;i <= m;i ++)
        mp[1][i]=i;
        int flag = m;
        for(int i = 1;i <= m;i += 2)
        mp[2][i]=++flag,mp[2][i+1]=-1;
        mp[3][1]=++flag;//先确定第一个数
        for(int i = 2;i <= m;i += 4)//以四个数为一循环
            if(i+3<=m)//判断是否超出范围
            mp[3][i]=++flag,mp[3][i+1]=-1,mp[3][i+3]=++flag,mp[3][i+2]=++flag;
            else
            mp[3][i]=++flag,mp[3][i+1]=-1,mp[3][i+2]=++flag;
        for(int i = 1;i <= 3;i ++)
        for(int j = 1;j <= m;j ++)
        if(mp[i][j]!=-1)ans++;
        cout<<ans<<endl;
        for(int i = 1;i <= 3;i ++){
            for(int j = 1;j <= m;j ++)
            cout<<mp[i][j]<<" ";
            cout<<endl;
        }
    }
}

```

---

## 作者：Brain_Huger (赞：2)

## 前言 

~~建议降橙/黄+惋惜 unr。~~

## 思路

首先这是一道构造题，可以发现 $1\le n\le3$。那么特判每一个 $n$ 时的答案。

### $n=1$

如图，仅需要按照 $1\sim m$ 或者 $m\sim 1$ 的顺序取即可，答案为 $m$。![](https://cdn.luogu.com.cn/upload/image_hosting/smvl1e8b.png)

### $n=2$

当 $m \equiv0\pmod2$ 时，答案为 $m+\frac{m}{2}$，如图所示。![](https://cdn.luogu.com.cn/upload/image_hosting/rojsg5zn.png)

当 $m \equiv1\pmod2$ 时，答案为 $m+\lceil\frac{m}{2}\rceil$，如图所示。![](https://cdn.luogu.com.cn/upload/image_hosting/lg4zzbv7.png)

### $n=3$

首先，第一行一定能全部拿走，接着，第二行每隔一个拿走一个，与 $n=2$ 时的一样。那么第三行呢？手磨 $m=7$ 的结果，发现最优解如下。
```
1	2	3	4	5	6	7
8	-1	9	-1	10	-1	11
12	13	-1	15	14	16	-1
```

再手磨 $m$ 更大的数据，会发现前三列为 $x$，$x+1$，$-1$，从第 $4$ 列开始，每 $4$ 列均为 $x+1$，$x$，$x+2$，$-1$，那么循环周期，最后判断余数即可。化简可得答案为 $2\times m+\frac{m+3}{4}$。

## 参考代码

```
#include<bits/stdc++.h>
int n,m,ans,a[5][100003],pos;
signed main(){
	scanf("%d%d",&n,&m);
	if(n==1){
		printf("%d\n",m);
		for(int i=1;i<=m;i++)printf("%d ",i);
	}
	else if(n==2){
		if(m==1){
			printf("%d\n%d\n%d",2,1,2);
		}
		else {
			if(m&1)printf("%d\n",m+m/2+1);
			else printf("%d\n",m+m/2);
			for(int i=1;i<=m;i++)printf("%d ",++pos);
			puts("");
			for(int i=1;i<=m;i++)if(i&1)printf("%d ",++pos);else printf("%d ",-1);
		}
	}
	else{
		printf("%d\n",2*m+(m+3)/4);
		for(int i=1;i<=m;i++)printf("%d ",1+pos),pos++;
		puts("");
		for(int i=1;i<=m;i++)if(i&1)printf("%d ",1+pos),pos++;else printf("%d ",-1);
		puts("");
		if(m==1)printf("%d\n",pos+1),pos++;
		else if(m==2)printf("%d %d\n",pos+1,pos+2),pos+=2;
		else if(m==3)printf("%d %d -1",pos+1,pos+2),pos+=2;
		else{
			printf("%d %d -1 ",1+pos,2+pos),pos+=2;
			for(int i=3;i+4<=m;i+=4)printf("%d %d %d -1 ",pos+2,pos+1,pos+3),pos+=3;
			if(m%4==1)printf("%d %d",pos+2,pos+1);
			else if(m%4==2)printf("%d %d %d",pos+2,pos+1,pos+3);
			else if(m%4==0)printf("%d",pos+1);
		}
	}
	return 0;
}
```

---

## 作者：lpx666666 (赞：2)

题意
------------

有一个都是棋子的矩阵，我们能从中拿出一些棋子，但四连通被取棋子不能超过一，输出能取的最多的棋子数和每个棋子取得先后位置（有多种可能）。

思路
------------
~~这是一道水绿~~

这道题我们发现 $n$ 的数据范围极小，我们再观察样例（虽然面向数据编程不是很好，但本人较菜）和自己造样例推可以得出的规律：

$1$、当 $n = 1$ 时，直接输出 $m$ 和 $1$ 到 $m$ 即可。

$2$、当 $n = 2$ 时，输出 $m + \lfloor m \div 2 \rfloor + m \bmod 2$，之后第一行和 $n = 1$ 时一样输出，第二行隔一格选一格。

$3$、当 $n = 3$ 时，输出 $n = 2$ 时的加本次的一个数，之后第一行和第二行时一样输出（不详细推导，代码中推导），第三行先选两格，之后格一格选三格。

代码
------------
来到你们最喜欢的环节了，上代码。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n==1){
		int m;
		cin>>m;
		cout<<m<<endl;
		for(int i=1;i<=m;i++){
			cout<<i<<" ";
		}
	}
	else if(n==2){
		int m;
		cin>>m;
		if(m==1) cout<<3;
		else cout<<m+m/2+m%2<<endl;
		for(int i=1;i<=m;i++){
			cout<<i<<" ";
		}
		cout<<endl;
		for(int i=1;i<=m;i++){
			if(i%2==1) cout<<m+i/2+1<<" ";
			else{
				cout<<-1<<" ";
			}
		}
	}
	else if(n==3){
		int m;
		cin>>m;
		if(m==1){
			cout<<3<<endl;//特判 
		}
		else if((m-2)%4!=0)cout<<m+int(m*1.0/2+0.5)+(m-2)/4*3+(m-2)%4+1<<endl;//四个一组，所以除以四。如果以最后的数结尾，少加一个一 
		else cout<<m+int(m*1.0/2+0.5)+(m-2)/4*3+2<<endl;//否则 +2
		for(int i=1;i<=m;i++){
			cout<<i<<" ";
		}
		cout<<endl;
		for(int i=1;i<=m;i++){
			if(i%2==1) cout<<m+i/2+1<<" ";
			else{
				cout<<-1<<" ";
			}
		}
		cout<<endl;
		int o=0;
		if(m%2==0){//判断第二行是否为-1结尾 
			if(m>=2) cout<<m+m/2+1<<" "<<m+m/2+2<<" ";
			else if(m==1) cout<<m+m/2+1<<" ";
			o=m+m/2+2;//初始次数 
		}
		else{
			if(m>=2) cout<<m+m/2+2<<" "<<m+m/2+3<<" ";
			else if(m==1) cout<<m+m/2+2<<" ";
			o=m+m/2+3;
		}
		for(int i=1;i<=m-2;i++){
			//先取中间再取两边，这样最大
			if(i%4==1){
				cout<<-1<<" ";
			}
			else if(i%4==2){
				if(i!=m-2) o+=2;//特判 
				else o++;
				cout<<o<<" ";
			}
			else if(i%4==3){
				o--;
				cout<<o<<" ";
			}
			else{
				o+=2;
				cout<<o<<" ";
			}
		}
	}
	return 0;
}

```

---

## 作者：we_are_the_chuibing (赞：2)

### 思路

注意到 $n \le 3$ ，直接从此入手。

### $n = 1$

送分。从左到右，把所有棋子取走。能取走 $m$ 颗。

```cpp
if(n==1){
	cout<<m<<endl;
	for(int i=1;i<=m;i++)cout<<i<<" ";
}
```
### $n = 2$

由于每次取走的棋子周围最多只有一颗棋子，所以我们可以推出，棋子从四联通方向上不可能有环，否则环上的最后一颗棋子取走时，必然周围有至少两颗被取走的棋子。

利用此结论，可以推断出每个边长为 $2$ 的正方形都需要保留一颗棋子。最好的策略是，将 $n = 2$，$m \equiv 0 \pmod 2$ 的棋子保留，先从左至右取完第一行，再将第二行的奇数列的棋子取完。能取走 $m + \lfloor \frac{m+1}{2} \rfloor$ 颗。

```cpp
if(n==2){
	cout<<m+(m+1)/2<<endl;
	for(int i=1;i<=m;i++)cout<<i<<" ";
	cout<<endl;
	for(int i=1;i<=m;i++){
		if(i%2)cout<<m+(i+1)/2;
		else cout<<-1;
		cout<<" ";
	}
}
```

### $n = 3$

考虑边长为 $3$ 的正方形（不含中间），从上两排的基础上，可以发现，第三排不能同时取第 $1,2,3$ 个，第 $3,4,5$ 个，第 $5,6,7$ 个，以此类推。由此推出，第三行保留棋子最少的方法需要保留 $m \equiv 3 \pmod 4$ 的棋子。

取走的方法：先按照 $n = 2$ 的方法取完前两行，再把第三行 $m \equiv 1 \pmod 4$ 的棋子取完，再把第三行 $m \equiv 0 \pmod 2$ 的棋子取完。能取走 $2m + \lfloor \frac{m+3}{4} \rfloor$ 颗。

```cpp
if(n==3){
	cout<<2*m+(m+3)/4<<endl;
	int ans=1;
	for(int i=1;i<=m;i++)cout<<ans++<<" ";
	cout<<endl;
	for(int i=1;i<=m;i++){
		if(i%2)cout<<ans++<<" ";
		else cout<<"-1 ";
	}
	cout<<endl;
	for(int i=1;i<=m;i++){
		if((i%4)==1)cout<<ans+(i/4)<<" ";
		else if((i%2)==0)cout<<ans+((m+3)/4)+(i/2)-1<<" ";
		else cout<<"-1 ";
	}
}
```

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	if(n==1){
		cout<<m<<endl;
		for(int i=1;i<=m;i++)cout<<i<<" ";
	}
	if(n==2){
		cout<<m+(m+1)/2<<endl;
		for(int i=1;i<=m;i++)cout<<i<<" ";
		cout<<endl;
		for(int i=1;i<=m;i++){
			if(i%2)cout<<m+(i+1)/2;
			else cout<<-1;
			cout<<" ";
		}
	}
	if(n==3){
		cout<<2*m+(m+3)/4<<endl;
		int ans=1;
		for(int i=1;i<=m;i++)cout<<ans++<<" ";
		cout<<endl;
		for(int i=1;i<=m;i++){
			if(i%2)cout<<ans++<<" ";
			else cout<<"-1 ";
		}
		cout<<endl;
		for(int i=1;i<=m;i++){
			if((i%4)==1)cout<<ans+(i/4)<<" ";
			else if((i%2)==0)cout<<ans+((m+3)/4)+(i/2)-1<<" ";
			else cout<<"-1 ";
		}
	}
	return 0;
}
```

---

## 作者：guer_loser_lcz (赞：2)

# 题解
## $n = 1$
这就一个个拿不就完了？代码：

```c
   cout<<m<<endl;
   for(int i=1;i<=m;i++)cout<<i<<" ";
```

## $n = 2$

先拿完一层：

```
1 2 3 ... m-2 m-1 m
o o o ...  o  o  o  <-棋子
```

可以看出，目前那第一个或最后一个最划算：拿其他的会挨上两个棋子，而它们只一个。

奇：

```
1 2 3 ... m-2 m-1 m
m+1 o m+2 ...  o  ans 
```
偶：

```
1 2 3 ... m-2 m-1 m
m+1 o m+2 ...  ans  o 
```

总和为 $\frac{3 \times m}{2}$ 向上取整。

代码：

```c
   cout<<m+(m+1)/2<<endl;
   for(int i=1;i<=m;i++)cout<<i<<" ";
   cout<<endl;
   for(int i=1;i<=m;i++){
      if(i%2==1)cout<<(i+1)/2+m<<" ";
      else cout<<-1<<" ";
   }
```


## $n = 3$

本题压轴，先按 $n = 2$ 拿：

```
1 2 3 ... m-2 m-1 m
m+1 o m+2 ... m+(m+1)/2 o 
o  o  o  ...    o  o  o
```

然后，第三行，拿法特殊：

```
x o x o x o x o x o x <-已拿
1 2 o 4 3 5 o 7 6 8 o...
```

把每一步单列出来，会清晰很多。

总和为 $\frac{9 \times m}{4}$ 向上取整。

代码：

```cpp
cout<<2*m+(m+3)/4;
cout<<endl;
for(int i=1;i<=m;i++)cout<<i<<" ";
cout<<endl;
for(int i=1;i<=m;i++){
    if(i%2==1)cout<<(i+1)/2+m<<" ";
    else cout<<-1<<" ";
}
cout<<endl;//前两行
int i=1,now=m+(m+1)/2+1;
a[i]=now++;
i++;
a[i]=now++;
i+=3;
while(i<=m+4){
    a[i]=now++;
    i--;
    a[i]=now++;
    i+=2;
    a[i]=now++;
    i+=3;
}//模拟第三行拿棋
for(int i=1;i<=m;i++){
	if(i==m-1&&(m%4==1||m%4==0)){
		if(m%4==1)cout<<a[i+1]+1<<" "<<a[i+1];
		else if(m%4==0)cout<<-1<<" "<<a[i-1]+1;
		return 0;//这两种边界会有问题，自行模拟
	}else if(a[i]==0)cout<<-1<<" ";//拿不走
	else cout<<a[i]<<" ";
}
```

---

## 作者：aaa_lvzekai (赞：2)

### 题外话

这一题加上后面骗分成功成为了 Rank44，比赛过了 $1$ 小时才来试试，还是很质量的一场比赛。

最让我兴奋的还是这张图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/6do9afky.png)

第一题骗到 $82$ 分时，成功领先紫名金钩的估值排行榜第一的魏佳泽大佬 $2$ 分。~~不过大佬还是大佬，立马被反超。~~

注：比赛时满分是 $200$ 分，这里按比赛时分数算。

## 题面

[Pick Stone](https://www.luogu.com.cn/problem/P10172)

## 做法

看到 $\bm{1\leq n\leq3}$，立马分成三种情况：

- $n = 1$

很明显，从 $1$ 取到 $m$ 就可以了。

40 分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	if(n==1)
	{
		cout<<m<<"\n";
		for(int i=1;i<=m;i++)
		{
			cout<<i<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/147368896)

- $n = 2$

我们先让第一行最优，第一行全取，可以发现第二行只能取一个空一个。

100 分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	if(n==1)
	{
		cout<<m<<"\n";
		for(int i=1;i<=m;i++)
		{
			cout<<i<<" ";
		}
		cout<<"\n";
	}
	else if(n==2)
	{
		cout<<m+(m+1)/2<<"\n";
		for(int i=1;i<=m;i++)
		{
			cout<<i<<" ";
		}
		cout<<"\n";
		for(int i=1;i<=m;i++)
		{
			if(i%2)
			{
				cout<<m+(i+1)/2<<" ";
			}
			else
			{
				cout<<-1<<" ";
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/147372953)

- $n = 3$

我们前两行按照 $n = 2$ 时去取，然后再按照题目的方案去取。

但是会发现第二个样例过不去，**考虑贪心**，如果前面位置的上面和左边都是不取棋子，就先取这个位置的棋子，再取前面位置的棋子。（有点绕，本人语文不好，不理解看代码。）

200 分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100010,M=10;
ll n,m,flag[M][N],ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	if(n==1)
	{
		cout<<m<<"\n";
		for(int i=1;i<=m;i++)
		{
			cout<<i<<" ";
		}
		cout<<"\n";
	}
	else if(n==2)
	{
		cout<<m+(m+1)/2<<"\n";
		for(int i=1;i<=m;i++)
		{
			cout<<i<<" ";
		}
		cout<<"\n";
		for(int i=1;i<=m;i++)
		{
			if(i%2)
			{
				cout<<m+(i+1)/2<<" ";
			}
			else
			{
				cout<<-1<<" ";
			}
		}
		cout<<"\n";
	}
	else
	{
		ans=m+(m+1)/2;//前两行和n=2时一样
		memset(flag,-1,sizeof(flag));//先初始化都不取
		for(int i=1;i<=m;i++)
		{
			flag[1][i]=i;
		}
		for(int i=1;i<=m;i++)
		{
			if(i%2)
			{
				flag[2][i]=m+(i+1)/2;
			}
			else
			{
				flag[2][i]=-1;
			}
		}//前两行
		for(int i=1;i<=m;i++)
		{
			if(flag[2][i]!=-1&&flag[3][i-1]!=-1)//如果这个位置的上面和左边都取
			{
				if(flag[3][i-2]==-1&&flag[2][i-1]==-1)//如果前面位置的上面和左边都是不取棋子
				{
					flag[3][i]=++ans;
					swap(flag[3][i-1],flag[3][i]);//交换
				}
				else
				{
					flag[3][i]=-1;
				}
			}
			else
			{
				flag[3][i]=++ans;
			}
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cout<<flag[i][j]<<" ";
			}
			cout<<"\n";
		}//输出
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/147367208)

---

## 作者：tzhengqing (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/P10172)

## 前言

拿到题目，读者们或许很快就会看到一个条件（事实上这极其重要）：

$\bm{1\leq n\leq3}.$

有什么用呢？**分类讨论**。
## 题意
在 $n \times m$ 大小的矩阵中取走棋子。

- 只能取走周围（四连通）被取走棋子数不超过 1 的棋子。

最大化取走棋子数，并给出方案。

若有多种合法方案，任意输出一种即可。

$\bm{1\leq n\leq3,1\leq m\leq10^5.}$

## Subtask 1 
这个子任务满足 $ n=1 $。

显然，对于 $1 \times m$ 的矩阵， 可以从前往后取。

取走棋子数 $=m$。

代码：
```cpp
if(n==1）
{
    cout<<m<<endl;
    for(int i=1;i<=m;i++)cout<<i<<' ';
}//全取
```

## Subtask 2
这个子任务满足 $ n=2 $。
 
考虑在 Subtask 1 的基础上构造解。

~~根据样例可以知道~~， 我们可以在第二排从左往右隔一个取一个。

可得最终答案为 $m+\displaystyle \lceil \frac{m}{2} \rceil$。

代码：
```cpp
if(n==2)
{
    cout<<m+m/2+m%2<<endl;
    int cnt=0;
    for(int i=1;i<=m;i++)cout<<++cnt<<' ';//第一行
    cout<<endl;
    for(int i=1;i<=m;i++)//第二行（隔一取一）
    {
        if(i&1)cout<<++cnt<<' ';
        else cout<<-1<<' ';
    }
}
```

## Subtask 3
这个子任务满足 $ n=3 $。
 
这次我们不看样例了。~~自己动手，丰衣足食。~~

考虑在 Subtask 2 的基础上构造解。

仿照子任务2的方法，先考虑从左往右取。

我们举出一个例子：

输入：

3 7

输出：（略作对齐）
```
15
  1  2  3  4  5  6  7
  8 -1  9 -1 10 -1 11
 12 13 -1 14 -1 15 -1
```
这是对的吗？

emmm... 好像不是。

看到位置 $10$ 下面那个 $-1$ 了吗？

经过观察与思考，我们可以得出新做法：

输入：

3 7

输出：（略作对齐）
```
16
  1  2  3  4  5  6  7
  8 -1  9 -1 10 -1 11
 12 13 -1 15 14 16 -1
```
至此，我们得出了正确做法：（在第三行时）

用 $j$ 表示列数，则：

若 $j \equiv 1 \pmod{4}$ 且 $j\ne1$，则先取 $j$，再取 $j-1$。

若 $j \equiv 2 \pmod{4}$，则取 $j$ 。

若 $j \equiv 3 \pmod{4}$，则不取。

若 $j \equiv 0 \pmod{4}$，则不作操作。

其余两行同 Subtask 2。

### 下附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;cin>>n>>m;
    if(n==1)
    {
        cout<<m<<endl;
        for(int i=1;i<=m;i++)cout<<i<<' ';
    }
    if(n==2)
    {
        cout<<m+m/2+m%2<<endl;
        int cnt=0;
        for(int i=1;i<=m;i++)cout<<++cnt<<' ';
        cout<<endl;
        for(int i=1;i<=m;i++)
        {
            if(i&1)cout<<++cnt<<' ';
            else cout<<-1<<' ';
        }
    }
    if(n==3)
    {
        int a[100005][3];//存答案
        int cnt=0;//计数
        for(int i=1;i<=m;i++)a[i][0]=++cnt;//第一行
        for(int i=1;i<=m;i++)//第二行
        {
            if(i&1)a[i][1]=++cnt;
            else a[i][1]=-1;
        }
        for(int i=1;i<=m;i++)//第三行（照规律模拟）
        {
            if(i==m && i%4==0)a[i][2]=++cnt;
            if(i%4==1)
            {
                if(i!=1)
                {
                    a[i][2]=++cnt;
                    a[i-1][2]=++cnt;
                }
                else a[i][2]=++cnt;
            }
            if(i%4==2)a[i][2]=++cnt;
            if(i%4==3)a[i][2]=-1;
        }
        cout<<cnt<<endl;
        for(int i=0;i<=2;i++)
        {
            for(int j=1;j<=m;j++)cout<<a[j][i]<<' ';
            cout<<endl;
        }
    }
    return 0;
}
```
~~完全违背我的马蜂~~

---

## 作者：_O_v_O_ (赞：1)

考虑分讨：

## $n=1$

很明显直接从左往右取即可。

这样最多能取 $m$ 个。

```cpp
if(n==1){
	cout<<m<<endl;
	for(int i=1;i<=m;i++){
		cout<<i<<' ';
	}
}
```
## $n=2$

在 $n=1$ 的基础上构造。

对于第二行，在第一行的基础上要每隔一个取一个才能满足要求。  
即把所有的 $\bmod\ 2=1$ 的 $i$ 给取了。

这样最多能取 $m+\lceil \frac{m}{2}\rceil$ 个。

```cpp
if(n==2){
	cout<<m+ceil(1.0*m/2)<<endl;
	for(int i=1;i<=m;i++){
		cout<<i<<' ';
	}
	cout<<endl;
	for(int i=1;i<=m;i++){
		cout<<((i%2)?(m+ceil(1.0*i/2)):(-1))<<' ';
	}
}
```

## $n=3$

在 $n=2$ 的基础上构造。

很明显，第二行是这样构造的（`o` 代表取，`x` 代表不取）：

```
o x o x o x...
```

那么第三行我们可以这样构造：

```
o x o x o x o x...
1 2 x 3 x 4 x 5...
```

但是还有更有的解法（因为刚刚的构造中出现了多个三面都没取的情况）：

```
o x o x o x o x o...
1 2 x 4 3 5 x 7 6...
```

所以最优的构造是这样的：

先输出 `1 2 -1 4`，对于接下来的每一个 $i$；

- 如果 $i\bmod4=1$，输出 $\lfloor\frac{i}{4}\rfloor\times 3$；
- 如果 $i\bmod4=2$，输出 $\lfloor\frac{i}{4}\rfloor\times 3+2$；
- 如果 $i\bmod4=3$，输出 $-1$；
- 如果 $i\bmod4=0$，输出 $\lfloor\frac{i}{4}\rfloor\times 3+1$；

这样能取 $2m+\lceil\frac{m}{4}\rceil$ 个。

注意特判。

```cpp
if(n==3){
	cout<<2*m+ceil(1.0*m/4)<<endl;
	for(int i=1;i<=m;i++){
		cout<<i<<' ';
	}
	cout<<endl;
	for(int i=1;i<=m;i++){
		cout<<((i%2)?(m+ceil(1.0*i/2)):(-1))<<' ';
	}
	cout<<endl;
	for(int i=1;i<=min(m,4);i++){
		if(i==3) cout<<-1<<' ';
		else{
			if(m==4&&i==4) cout<<m+ceil(1.0*m/2)+i-1<<' ';
			else cout<<m+ceil(1.0*m/2)+i<<' ';
		}
	}
	for(int i=5;i<=m;i++){
		switch(i%4){
			case 1:{
				cout<<m+ceil(1.0*m/2)+floor(1.0*i/4)*3<<' ';
				break;
			}
			case 2:{
				cout<<m+ceil(1.0*m/2)+floor(1.0*i/4)*3+2<<' ';
				break;
			}
			case 3:{
				cout<<-1<<' ';
				break;
			}
			default:{
				if(i==m){
					cout<<m+ceil(1.0*m/2)+floor(1.0*i/4)*3<<' ';
				}
				else{
					cout<<m+ceil(1.0*m/2)+floor(1.0*i/4)*3+1<<' ';
				}
				break;
			}
		}
	}
}
```

---

## 作者：vorDeal (赞：0)

构造题。

要观察样例之规律。

发现 $1\le n \le 3$。分类讨论。

- $n=1$
  
  顺次全部取走即可。

- $n=2$
  
  第一行同 $n=1$，第二行每隔 $1$ 个取 $1$ 个。
- $n=3$
  
  前两行同 $n=2$。

  对于第三行：

  先取 $2$ 个，再每隔 $1$ 个取 $3$ 个。特判前两个，再按余数分类讨论即可。对于每组 $3$ 个的，先取中间，后取左，再取右。

  **注意：最后一组若只有 $1$ 个要特判。**

**AC Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;

int main()
{
    cin >> n >> m;
    if (n == 1)
    {
        cout << m << endl;
        for (int i = 1; i <= m; i++)
            cout << i << ' ';
    }
    else if (n == 2)
    {
        cout << (m << 1) - (m >> 1) << endl;
        for (int i = 1; i <= m; i++)
            cout << i << ' ';
        cout << endl;
        for (int i = 1; i <= m; i++)
        {
            if (i & 1)
                cout << m + (i + 1) / 2 << ' ';
            else
                cout << "-1 ";
        }
    }
    else if (n == 3)
    {
        cout << ceil(9.0 * float(m) / 4.0) << endl;
        for (int i = 1; i <= m; i++)
            cout << i << ' ';
        cout << endl;
        for (int i = 1; i <= m; i++)
        {
            if (i & 1)
                cout << m + (i + 1) / 2 << ' ';
            else
                cout << "-1 ";
        }
        cout << endl;
        for (int i = 1; i <= m; i++)
        {
            if (i == 1 || i == 2)
                cout << (m << 1) - (m >> 1) + i << ' ';
            else if (i % 4 == 1 || (i % 4 == 0 && i == m))
                cout << (m << 1) - (m >> 1) + (i >> 2) * 3 << ' ';
            else if (i % 4 == 0)
                cout << (m << 1) - (m >> 1) + (i >> 2) * 3 + 1 << ' ';
            else if (i % 4 == 2)
                cout << (m << 1) - (m >> 1) + (i >> 2) * 3 + 2 << ' ';
            else
                cout << "-1 ";
        }
    }
    return 0;
}
```

---

## 作者：WZWZWZWY (赞：0)

比赛题、规律题。（~~今天没作业，水一篇题解~~）

[题目链接](https://www.luogu.com.cn/problem/T415749)

注意题目是放时看周围是否少于一个正整数，放后就不用管了。

所以我们可以按顺序这么放。（正整数值就是放的顺序）：



```
-1  1 -1
 3  2  4
```

```
 1 -1 2 -1  3
-1  5 4  6 -1
```

> 小规律：下面中间数的比左边小 $1$，相当于按顺序填再将它两交换。——小 `W`

------------

# 思路

### 当 $n=1$ 时，

很显然，依次输出从 $1$ 到 $m$ 即可。

**代码：**
```
cnt = 0;
for (int i = 1; i <= m; i++) ans[1][i] = ++cnt;
```


------------

### 当 $n=2$ 时，

答案也很容易想到，第一行不变，第二行第一个放正整数，每隔一个 $-1$ 放一个。

```
1  2  3  4  5
6 -1  7 -1  8
```
**代码：**

```
for (int i = 1; i <= m; i++) {
	if (i & 1) ans[2][i] = ++cnt;
	else ans[2][i] = -1;
}
```


------------

### 当 $n=3$ 时，


第一行、第二行还是一样的规律。

第三行容易想到贪心，从左往右填，能填就填，如果当前位置上面一个是 $-1$，那么肯定能填当前位置（因为是按顺序填，此时没有右边和下边的正整数）。但是，这并不是最优策略。

按我们的思路，发现如果（第三行）一个位置 $i$ 前面值是 $-1$，上面也是 $-1$，那么肯定能填，但是下一位肯定不能填，因为下一位的左边和上边都是正整数值。

#### 新的策略（省流：就是最开头的那个形状，开头的更简洁易懂哦。——来自小 `W`）：



设有一个 $3$ 行 $k$ 列的数组 $a$（第一维是行数，第二维是列数），如果 $a_{3,j}$ 填入时间比 $a_{2,j}$ 晚，比 $a_{3,j-1}$ 和 $a_{3,j+1}$ 早，它就能填。

当左边和上边都有正整数，并且 $a_{3,j-2}$ 为 $-1$ 时，在“能填就填”贪心基础上，**把 $a_{3,j}$ 与 $a_{3,j-1}$ 交换**就可以做到：比上面时间晚，比左边、右边时间早（因为按从左到右的顺序填时，比上面时间晚，比左边时间晚，比右边时间早）。

> ```
>  j -1  a -1  k
> -1  b  c  d -1
> 交换b、c变成了填入顺序合法的：
>  j -1  a -1  k
> -1  c  b  d -1
> ```

第三行基本都是这样，每四个为一组（$-1$ 加三个正整数），显然比之前的差不多每两个为一组优。再怎么填也没有更优的方案，它就是最优的！

所以这样填（这里是 $m=10$ 的结果）：

```
23
 1  2  3  4  5  6  7  8  9 10
11 -1 12 -1 13 -1 14 -1 15 -1
16 17 -1 19 18 20 -1 22 21 23
```

**代码:**
```
ans[3][1] = ++cnt;
for (int i = 2; i <= m; i++) {
	if (ans[2][i] !=-1 && ans[3][i-1] != -1) {
		if (ans[3][i-2] == -1) {
			ans[3][i] = ++cnt;
			swap(ans[3][i-1], ans[3][i]);
		} else ans[3][i] = -1;
	} else ans[3][i] = ++cnt;
}
```


------------

# 完整代码

~~其实就是拼起来，稍微压了压行~~

```
#include <iostream>
using namespace std;
int cnt, n, m, ans[4][100005];
void get1() { for (int i = 1; i <= m; i++) ans[1][i] = ++cnt; }
void get2() {
	for (int i = 1; i <= m; i++)
		if (i & 1) ans[2][i] = ++cnt;
		else ans[2][i] = -1;
}
void get3() {
	ans[3][1] = ++cnt;
	for (int i = 2; i <= m; i++)
		if (ans[2][i] !=-1 && ans[3][i-1] != -1) 
			if (ans[3][i-2] == -1) {
				ans[3][i] = ++cnt;
				swap(ans[3][i-1], ans[3][i]);
			} else ans[3][i] = -1;
		else ans[3][i] = ++cnt;
}
void print() {
	cout << cnt << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cout << ans[i][j] << " ";
		cout << "\n";
	}
}
int main() {
	cin >> n >> m;
	if (n == 1) { get1(); print(); }
	else if (n == 2) { get1(); get2(); print(); }
	else { get1(); get2(); get3(); print(); }
}
```

还有什么不懂的可以问我哦。还有什么建议的话也可以提出来哦！

---

