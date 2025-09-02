# Vacation

## 题目描述

暑假有 $N$ 天。对于每一天 $i$（$1 \leq i \leq N$），太郎君可以选择以下活动之一：

- A：在海里游泳，获得幸福度 $a _ i$。
- B：在山上抓虫，获得幸福度 $b _ i$。
- C：在家做作业，获得幸福度 $c _ i$。

由于太郎君容易厌倦，他不能连续两天及以上做同样的活动。

请计算太郎君可以获得的最大总幸福度。

## 样例 #1

### 输入

```
3
10 40 70
20 50 80
30 60 90```

### 输出

```
210```

## 样例 #2

### 输入

```
1
100 10 1```

### 输出

```
100```

## 样例 #3

### 输入

```
7
6 7 8
8 8 3
2 5 2
7 8 6
4 6 8
2 3 4
7 5 1```

### 输出

```
46```

# 题解

## 作者：zjyqwq (赞：27)

### AT4524 题解

本蒟蒻第一次发题解。Pas题解来一发。

------------
#### 题目解析

 题目意思很明了，我们可以用 DP 方法来解。
 
 我们先开三个数组 $a1[]$、 $a2[]$、 $a3[]$ 分别保存游泳、捉虫、写作业 ~~（什么鬼）~~ 每天增加的幸福值。
 
 然后，再写DP方程。
 
 我们再开三个数组，为 $f1[]$、 $f2[]$、 $f3[]$ 。
 
 $f1[x]$ 为第 $x$ 天为游泳时的最大辛福值。其他同理。
  
  那么如果他第 $x$ 天是游泳，那么他 $1$~$x$ 的所有幸福值最大为
 ```pascal
 a1[x]+max(f2[x-1]+f3[x-1]);

``` 
 因为如果他第 $x$ 天游泳，那么他 $1$~$x$ 天幸福总值肯定要加上他第 $x$ 天游泳获取的幸福值，因为两天不能做同样的事，那么他因选择着加上
 
 ```pascal max(f2[x-1]+f3[x-1])```
 
 那么其他两项也一样了。


------------
#### 代码区
```pascal
uses math;//使用math库，可以使用max函数。
var
n,i:longint;
a1,a2,a3,f1,f2,f3:array[0..100005]of longint;//六个数组。
 begin
  readln(n);
  for i:=1 to n do
   readln(a1[i],a2[i],a3[i]);//输入部分
  for i:=1 to n do
   begin
    f1[i]:=max(f2[i-1],f3[i-1])+a1[i];
    f2[i]:=max(f1[i-1],f3[i-1])+a2[i];
    f3[i]:=max(f2[i-1],f1[i-1])+a3[i];//DP部分
   end;
  write(max(max(f1[n],f2[n]),f3[n]));//输出第n天的所有情况中最大的
 end.
```


------------
结束啦！QwQ

疯狂暗示……



---

## 作者：Haphyxlos (赞：11)

# AT4524 Vacation

[题目传送门](https://www.luogu.com.cn/problem/AT4524)
### 题目翻译
太郎的暑假有$n$天，第$i$天他可以选择做以下三种事情：

1. 游泳，获得$a_i$点幸福值。 
2. 捉虫，获得$b_i$点幸福值。 
3. 写作业，获得$c_i$点幸福值。

但他不能连续两天进行同一种活动，请求出最多可以获得多少幸福值。

对于本题，我们可以开一个a[maxn][3]来存储可获得的幸福值，f[maxn][3]来存储当前的幸福值。

由题意，$f[i][cur]$只可能从另外两个状态中的最大值转移过来，然后再加上当前可获得的幸福值$a[i][cur]$即可。

故本题的dp方程如下：

$$f[i][0]=max(f[i-1][1],f[i-1][2])+a[i][0]$$
$$f[i][1]=max(f[i-1][0],f[i-1][2])+a[i][1]$$
$$f[i][2]=max(f[i-1][0],f[i-1][1])+a[i][2]$$

本题的ACcode：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
int n,a[maxn][3],f[maxn][3];
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i][0]>>a[i][1]>>a[i][2];
	for(int i=1;i<=n;++i){
		f[i][0]=max(f[i-1][1],f[i-1][2])+a[i][0],
		f[i][1]=max(f[i-1][0],f[i-1][2])+a[i][1],
		f[i][2]=max(f[i-1][0],f[i-1][1])+a[i][2];
	}
	cout<<max(max(f[n][0],f[n][1]),f[n][2]); 
	return 0;
}
```
耗时：$299ms$

当然，本题也有另一个写法：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
int n,a[maxn][3],f[maxn][3];
int main(int argc,char const *argv[]){
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i][0]>>a[i][1]>>a[i][2];
    for(int i=0;i<3;++i)f[1][i]=a[1][i];
    for(int i=2;i<=n;++i){
    //i是第i天
    	for(int j=0;j<3;++j){
    	//j是当前的活动
    		for(int k=0;k<3;++k){
         	//k是上次选择的活动
    			if(j!=k){
    				f[i][j]=max(f[i][j],f[i-1][k]+a[i][j]);
				}
			}
		}
	}
    cout<<max(max(f[n][0],f[n][1]),f[n][2]); 
    return 0;
}
```
耗时：$323ms$

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4524) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_c)

>Taro要度假$n$天。每天他进行仅有的$3$种活动中的恰好$1$个。他第$i$天进行第$1,2,3$种活动分别会获得$a_i,b_i,c_i$快乐值。连续$2$天不能进行同种活动。求$n$天的最大总快乐值。

>$n\in\left[1,10^5\right]$。

设$dp1_i,dp2_i,dp3_i$表示考虑到第$i$天，第$i$天分别进行第$1,2,3$种活动时获得的最大总快乐值。边界是$dp1_0=dp2_0=dp3_0=0$，目标是$\max(dp1_n,dp2_n,dp3_n)$，状态转移方程是

$$\begin{cases}dp1_i=\max(dp2_{i-1},dp3_{i-1})+a_i\\dp2_i=\max(dp1_{i-1},dp3_{i-1})+b_i\\dp3_i=\max(dp1_{i-1},dp2_{i-1})+c_i\end{cases}$$

时间复杂度$\mathrm O(n)$，乘上一个比较大的常数。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100000;
int a[N+1],b[N+1],c[N+1];
int dp1[N+1],dp2[N+1],dp3[N+1];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
	for(int i=1;i<=n;i++)//转移 
		dp1[i]=max(dp2[i-1],dp3[i-1])+a[i],
		dp2[i]=max(dp1[i-1],dp3[i-1])+b[i],
		dp3[i]=max(dp1[i-1],dp2[i-1])+c[i];
	cout<<max(max(dp1[n],dp2[n]),dp3[n]);//目标 
	return 0;
}
```

---

