# Weather

## 题目描述

科学家们对全球变暖和地球降温的问题说了很多。事实上，这种自然现象强烈影响着我们星球上的所有生命。

我们的英雄Vasya非常关心这些问题。他决定做一个小小的实验，观察室外的温度是如何变化的。他每天早上在阳台上挂一个温度计，记录下温度。

他过去的n天都在测量温度。因此，他得到了一组数据：

$t_1$,$t_2$......$t_n$,其中，$t_i$表示第i天温度。

Vasya分析了其他城市的温度统计数据，得出结论：如果先是室外温度为负的一些非零天数，然后温度为正的一些非零天数，那么这个城市就没有环境问题。

更确切地说，必须存在一个正整数k(1<=k<=n-1),使得$t_1$<0,$t_2$<0......$t_k$<0并且其余的数据大于0。

还有一个特殊的要求：温度永远不应该是零。

如果不满足这个条件，Vesya决定他的城市有环境问题，并感到不安!!

你不想让Vesya难过。因此，您需要选择多个温度值并修改它们以满足Vasya的条件。你需要知道需要改变的最小温度值的数目。

## 说明/提示

对于第一个样例：有两种方法可以改变一个数字，使序列符合Vasya的条件。你可以用任何负数替换第一个数字1，也可以用任何正数替换数字-2。

## 样例 #1

### 输入

```
4
-1 1 -2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
0 -1 1 2 -5
```

### 输出

```
2
```

# 题解

## 作者：XXh0919 (赞：5)

这道题可以用前缀和和后缀和。我们可以用前缀和求出序列中正数的个数，用后缀和求出负数的个数，再用一个计数器 $sum$ 记录 $0$ 的个数，最后计算答案即可。

注意文件读入。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+15;

int n;
int a[N],b1[N],b2[N],sum,ans=0x3f3f3f3f;

signed main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		b1[i]=b1[i-1];
		if(a[i]>0)b1[i]++;//前缀和
		if(a[i]==0)sum++;//0 的个数
	}
	for(int i=n;i>=1;--i){
		b2[i]=b2[i+1];
		if(a[i]<0)b2[i]++;//后缀和
	}
	for(int i=1;i<n;i++){
		ans=min(ans,b1[i]+b2[i+1]+sum);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：4)

## 题意
把长度为 $n$ 的数列的数字替换，换几次能让它前面全为负，后面全为正，且不含 0。
## 思路
依次枚举以 $i$ 为负的最后一个时，前面有几个正（需要改的），后面有几个负，顺便求出有几个 0（这必须要改），最后看哪种方法最优。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int weather[N],q[N],h[N],n,ans=INT_MAX,z; //weather 为每天温度，q 为前几天的正数和，h 后几天的负数和，z 为 0 的个数 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>weather[i];
		q[i]=q[i-1]; //前 i 天（先不算第 i 天）的正数和
		if(weather[i]>0){
			q[i]++; //第 i 天是否为正 
		}
		else{
			if(!weather[i]){ //0 一定要改 
				z++;
			}
		}
	}
	for(int i=n;i>=1;i--){
		h[i]=h[i+1];
		if(weather[i]<0){
			h[i]++;
		}
		// 上面已经处理过 0 了，这就不处理了 
	}
	for(int i=1;i<n;i++){ //枚举 
		ans=min(ans,q[i]+h[i+1]+z);
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：FreedomKing (赞：3)

# 前缀和/后缀和
[注：Blog 食用更佳](https://www.luogu.com.cn/blog/zhugeminhao/SP3394)

------------
### 思路

思路十分简单，就是利用前/后缀和求出序列中非负/正数个数，所以切就完了！

**但特别注意的是要用文件读写**，本蒟蒻可被它坑惨了，望你谷加上使用文件读写的说明。 [Link 1](https://www.luogu.com.cn/record/69681633) [Link 2](https://www.luogu.com.cn/record/69681739)

------------
[CF234C Weather](https://www.luogu.com.cn/problem/CF234C)
### AC Code:
```cpp
#include<bits/stdc++.h>//不用万能头也可以，但个人觉得万能头方便
using namespace std;//必须得加，不然会报错
const int N=100005;
int n,s1[N],s2[N],a[N],k,x=0x3f3f3f3f;//0x3f3f3f3f和0x7fffffff都可以
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//切记加上文件读写
	scanf("%d",&n);
	for(int i=1;i<=n;i++){//前缀和
		scanf("%d",&a[i]);
		s1[i]=s1[i-1];
		if(a[i]>0){s1[i]++;continue;}//continue小小优化了一下
		if(a[i]==0) k++;
	}
	for(int i=n;i>=1;i--){//后缀和
		s2[i]=s2[i+1];
		if(a[i]<0) s2[i]++;
	}
	for(int i=1;i<n;i++) x=min(x,(s1[i]+s2[i+1]+k));//求出最少改变数目
	printf("%d",x);//输出
	return 0;//好习惯
}
```
~~蒟蒻的第 $3$ 篇题解，但还是求过。 $QwQ$~~

---

## 作者：do_while_true (赞：1)

前置芝士:前/后缀和

思路十分简单，我们设置一个临界点。设 $sum1_i$ 为 $i$(含) 左边大于0的数 (即若 $i$ 为临界点左边要修改的(不包括0)数的个数) ，$sum2_i$ 为 $i$ 右边的小于0的数(即若 $i$ 为临界点右边要修改的(不包括0)数的个数)，$lsum$ 为0的个数(即所有的0一定要修改成正数或负数)

答案为

$$\min\limits_{i=1}^{n-1}sum1_i+sum2_{i+1}+lsum$$

### Code:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,sum1[100002],sum2[100002],a[100002],lsum,ans=0x7fffffff;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum1[i]=sum1[i-1];
		if(a[i]>0) sum1[i]++;
		if(a[i]==0) lsum++;
	}
	for(int i=n;i>=1;i--)
	{
		sum2[i]=sum2[i+1];
		if(a[i]<0) sum2[i]++;
	}
	for(int i=1;i<n;i++)
		ans=min(ans,sum1[i]+sum2[i+1]+lsum);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Alcl000000 (赞：0)

考虑对于每一个 $k\in[1,n-1]$，需要改变的温度数目为**前面大于等于 $0$ 的数的数量**与**后面小于等于 $0$ 的数的数量**的和。所以我们可以维护前缀数组 $pre$ 和后缀数组 $suf$，分别记录前后两种数的数量，答案即为 $\min_{i=1}^{n-1} pre_i+suf_{i+1}$。

code:
```cpp
#include<bits/stdc++.h>
#define ios ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
int n,ans=100000009,pre[2000005],suf[2000005],a[2000005]; 
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//因为没加文件读入读写WA了一次，但翻译没体现要加这个！！！ 
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(a[i]>=0);
	for(int i=n;i>=1;i--) suf[i]=suf[i+1]+(a[i]<=0);
	for(int i=1;i<=n-1;i++) ans=min(ans,pre[i]+suf[i+1]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 题意

使得序列前面为负数后面为正数的最小操作次数。

### 思路

前缀和后缀和求出正数和负数的数量，统计 $0$ 的数量。接着枚举每一个分界线，求出最终答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[100009],b[100009],len;
int c[100009],h=0;
signed main()
{
    freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>len;
	for(int i=1;i<=len;i++)
		cin>>c[i];
	for(int i=1;i<=len;i++)
	{
		a[i]=a[i-1];
		if(c[i]>0) a[i]++;
		if(c[i]==0) h++;
	}
	for(int i=len;i>=1;i--)
	{
		b[i]=b[i+1];
		if(c[i]<0) b[i]++;
		
	}
	int ans=0x3f3f3f3f;
	for(int i=1;i<len;i++)
		ans=min(ans,a[i]+b[i+1]+h);//a统计前面为正整数的数量，b统计后面为负数的数量。
	cout<<ans;
	return 0;
}
```

---

## 作者：Upda (赞：0)

题目要求 $\sum\limits_{i=1}^k [a_i\ge0]+\sum\limits_{i=k+1}^n [a_i\le0]$ 的最小值。

考虑枚举中间点 $k$，我们需要求前缀中非负数的个数，和后缀非正数个数。

发现这两个东西都可以前/后缀和，所以就做完了。

**特别注意 $1\leq k \leq n-1$**，即至少一正一负。

同时这题需要**文件输入输出**！！！（你谷题面居然没写）

具体见代码。

--------

```
int n,x,Ans;
int pre[100005],suf[100005];
signed main() {
    freopen("input.txt","r",stdin);   // 
    freopen("output.txt","w",stdout);  // 加文操
	n=read(); Ans=100000000;
    for(int i=1; i<=n; ++i) {
        x=read();
        pre[i]=x>=0;
        suf[i]=x<=0;
    }
    for(int i=1; i<=n; ++i) pre[i]+=pre[i-1];
    for(int i=n; i>=1; --i) suf[i]+=suf[i+1];
    for(int k=1; k< n; ++k) Ans=min(Ans,pre[k]+suf[k+1]); // 枚举 k
    write(Ans); puts("");
	return 0;
}
```

---

