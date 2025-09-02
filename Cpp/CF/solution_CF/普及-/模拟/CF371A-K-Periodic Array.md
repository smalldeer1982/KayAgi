# K-Periodic Array

## 题目描述

This task will exclusively concentrate only on the arrays where all elements equal 1 and/or 2.

Array $ a $ is $ k $ -period if its length is divisible by $ k $ and there is such array $ b $ of length $ k $ , that $ a $ is represented by array $ b $ written exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371A/53488bbee46df1b241cbadadd932aea80891152b.png) times consecutively. In other words, array $ a $ is $ k $ -periodic, if it has period of length $ k $ .

For example, any array is $ n $ -periodic, where $ n $ is the array length. Array $ [2,1,2,1,2,1] $ is at the same time 2-periodic and 6-periodic and array $ [1,2,1,1,2,1,1,2,1] $ is at the same time 3-periodic and 9-periodic.

For the given array $ a $ , consisting only of numbers one and two, find the minimum number of elements to change to make the array $ k $ -periodic. If the array already is $ k $ -periodic, then the required value equals $ 0 $ .

## 说明/提示

In the first sample it is enough to change the fourth element from 2 to 1, then the array changes to $ [2,1,2,1,2,1] $ .

In the second sample, the given array already is 4-periodic.

In the third sample it is enough to replace each occurrence of number two by number one. In this case the array will look as $ [1,1,1,1,1,1,1,1,1] $ — this array is simultaneously 1-, 3- and 9-periodic.

## 样例 #1

### 输入

```
6 2
2 1 2 2 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8 4
1 1 2 1 1 1 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
9 3
2 1 1 1 2 1 1 1 2
```

### 输出

```
3
```

# 题解

## 作者：Light_Star_RPmax_AFO (赞：3)

# 大水题
题目中已经给出了 $a$ 数组只由 $1$ 或 $2$ 组成。

我们其实从题目中变可以得出一个规律。

某个位置上哪个数出现次数少我们就改他，这样我们便可以得到最小次数，如：
```cpp
样例1
周期第一个位置：2出现3次。
不用改
周期第二个位置：2 出现 1 次，1 出现 2 次。
所以我们需要改 2。

样例3
周期第一个位置：2 出现 1 次，1 出现 2 次。
所以我们需要改 2。
第二个位置：2 出现 1 次，1 出现 2 次。
所以我们需要改 2。
第三个位置：2 出现 1 次，1 出现 2 次。
所以我们需要改 2。
```
接下来上代码。
```cpp
#include<bits/stdc++.h>
#define mi(a,b) a<b?a:b
int n,k,b[110],a[10010],c[110],ans;// b记录 1 出现次数，c记录 2 出现次数。
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);//无脑输入。
    for(int i=1;i<=n;i++)if(a[i]==1)b[i%k]++;else c[i%k]++;//如果是 1 这个位置的1出现次数加 1。
    for(int i=0;i<k;i++)ans+=mi(b[i],c[i]);//得出的结论，哪个少加哪个。
    printf("%d\n",ans);//printf 与scanf 比 cin 与 cout快
    return 0;//好习惯。
}
```
 QWQ



---

## 作者：DLDZD (赞：1)

## 思路：
从样例中我们不难发现：只有一与二！

所以只需在每个 $\frac{n}{k} $ 区间分别中累加 $1$ 与 $2$ 的个数，之后加上最小的个数，循环 $k$ 次，即可实现。

## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1001];
int ans;
int n,k;
int min(int a,int b){
	return (a<b? a:b);
}//最小值函数，这样更快。
int init(int n,int k){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
}//输入
int qiuzhi(int x){
	while(x--){//写 for(int j=1;i<=k;j++) 也行，但是后面的 for 中的 k-x 要变成 j 。
		int a1=0,a2=0;
		for(int i=k-x;i<=n;i+=k){
			if(a[i]==2) a2++;//累加
			if(a[i]==1) a1++;//累加
		}
		ans+=min(a1,a2);//加上最小的。
	}
}//求值
signed main(){//因为“#define int long long”，所以main的int改为signed
	init(n,k);//初始化
	int x=k;//保存k的值
	qiuzhi(x);//求值
	cout<<ans;//输出
	return 0;
}
```

---

## 作者：Noby_Glds (赞：0)

数据还可以再大一点。
### 思路：
拿样例搞一下：
```latex
2 1
2 2
2 1
```
可以发现，第二列中，$1$ 的数目为 $2$，$2$ 的数目为 $1$，$1$ 的数目比 $2$ 多。

因此，把第二列全改为 $1$ 的花费更少。

由此推出，对于各个段的对应位置，记录 $1$ 和 $2$ 的个数，哪个少全改成哪个。
### 代码
```cpp
#include<bits/stdc++.h>
#define N 110
using namespace std;
int n,k,a[N],s[N],ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],s[i%k]+=(a[i]==1);
	for(int i=0;i<k;i++) ans+=min(s[i],n/k-s[i]);
	cout<<ans;
	return 0;
}//最短代码
```


---

