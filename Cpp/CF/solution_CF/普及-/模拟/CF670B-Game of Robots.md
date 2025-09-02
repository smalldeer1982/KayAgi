# Game of Robots

## 题目描述

有$n(n\leq100000)$个机器人，每个机器人都有一个唯一的整数序号，该序号在$1$到$10^9$之间。他们在做一个叫“滚雪球”的游戏，即第一个机器人说出第一个机器人的序号，第二个机器人说出第一到第二个机器人的序号，第三个机器人说出第一到第三个机器人的序号……以此类推。求第$k(k\leq min(2\cdot10^9,n\cdot(n+1)/2)$个被说出的序号。

## 样例 #1

### 输入

```
2 2
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 5
10 4 18 3
```

### 输出

```
4
```

# 题解

## 作者：LJN1117 (赞：1)

循环水题，建议评红

## 前置芝士
 前缀和

## 题意
每个人都有自己的名字

现在在玩一个游戏，叫做叫名字

每个人都会叫前面人的名字和自己的名字

现在问你第 $k$ 个叫的名字是啥

## 题解

其实每个人叫了多少，就是一个前缀和

统计一下，然后直接输出就好了

##  _code_ 

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 100000+10

using namespace std;

int n,k,a[maxn],sum;

signed main(){
    scanf("%lld %lld",&n,&k);//输入
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
        sum+=i;//前缀和
        if(sum>=k){//如果大于，做差
            sum=i-(sum-k);
            printf("%lld\n",a[sum]);//输出
            break;
        }
    }
    return 0;//好习惯要养成qwq
}
```
## END


---

## 作者：yanxingyu0910 (赞：1)

**题目链接**[https://www.luogu.com.cn/problem/CF670B](https://www.luogu.com.cn/problem/CF670B)

### 题目描述
有 $n(n\leq100000)$ 个机器人，每个机器人都有一个唯一的整数序号，该序号在 $1$ 到 $10^9$ 之间。他们在做一个叫“滚雪球”的游戏，即第一个机器人说出第一个机器人的序号，第二个机器人说出第一到第二个机器人的序号，第三个机器人说出第一到第三个机器人的序号……以此类推。求第  $k$ 个被说出的序号。

**解法**

参考CF官方题解的思路：从左到右依次暴力枚举出每个机器人说出的序号。

也就是当 $k-i>0$ 时，就还不能取所以要减掉 $i$ 继续减直到 $k-1\leq 0$ 时（用"else"就能替代）取出 $a[k]$ 即可。

**代码**

[长代码含快读快写](https://www.luogu.com.cn/paste/v5ibovm1)

**精华代码部分**

```cpp
for(i=1;i<=n;++i){
	if(k-i>0){
		k-=i;
	}
	else{
		printf("%lld",a[k]);
		return 0;
	}
}
```
记得要开 long long （逃）

---

## 作者：Maxliu (赞：1)

一道很好的循环训练题。

$n\leq10^6$,这提示我们可以枚举每一个机器人说出序号的个数（编号为$i$的机器人会说出$i$个序号），设枚举过的所有机器人说出的序号数之和为$sum$,若$sum<k$，就继续枚举，直到$sum\geq k$，此时第$k-(sum-i)$个机器人的序号就是答案。

以下为代码。
```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,k,sum;
int a[100005];
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		sum+=i;
		if(k<=sum){
			printf("%lld",a[k-sum+i]);
			break;
		}
	}
	return 0;
}
```


---

## 作者：_cpp (赞：1)

这题主要是考察循环的掌握程度。

简简单单按题目模拟即可（甚至连数组都不用开）。首先，不难看出，每次机器人报的编号数都比上一个机器人多一。所以我们可以先预处理出报的第 $k$ 个编号是哪一个，即每一次都减上一次多减一即可，直到不够减为止。我这么说大家可能不理解，我来解释一组样例：

如果 $n = 3 \ k = 5$。

三个机器人编号分别为 $1 \  2\   3$。

第一个机器人会报 $1$ 个编号。

那 $k$ 就减 $1$，下一个机器人会报 $2$ 个编号，$k$ 就减 $2$。

但到第三个机器人时，它会报 $3$ 个编号，但此时 $k$ 等于 $2$，没法减。所以就证明机器人报的第 $k$ 个编号此时就是第三个机器人口中报的第 $2$ 个，见代码片段：

```cpp
cin>>n>>k;
for(i=1;k>i;i++) k-=i;  //k每次都减比上一次多减一
```

------------



那剩下来的 $k$ 就是编号中的第 $k$ 个，见代码片段：

```cpp
for(i=1;i<=n;i++){
	cin>>x;
	if(i==k) return cout<<x,0; //如果是第k个编号，就直接输出
}
```

完整代码就不放了，想必大家如果理解我的思路的话，应该可以自己打出来的。

最后再给大家看一下我的评测记录：[传送门](https://www.luogu.com.cn/record/85803149)  。

目前应是全网最快。

---

## 作者：henrywyh (赞：0)

可以直接循环累加求解，就像楼上的一样。

不过还能减少循环次数。首先我们先要求出是哪个机器人说出的第 $k$ 个编号，相当于求最大的整数 $m$ ，使得：
①：$1+2+3+...+m<k$（第 $m$ 个机器人叫不到 $k$ ）

②：$1+2+3+...+(m+1)≥k$(第 $m+1$ 个机器人叫到 $k$ )

①式化简得： $m(m+1)<2k$

不难发现 $m<\sqrt{2k}$ ，于是我们可以从 $\sqrt{2k}$ 开始往下试：
```cpp
for(i=sqrt(2*k);;i--)
{
    if(i*(i+1)<2*k)
        break;
}
```
找到 $m$ 后用 $k$ 减去 $1$ 到 $m$ 叫号总次数 $s=k-\frac{i(i+1)}{2}$ ，就是第 $m+1$ 个机器人叫的第 $s$ 个序号是（总共的）第 $k$ 个。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int num[maxn];
signed main()
{
    int n,k,i;
    cin>>n>>k;
    for(i=1;i<=n;i++)
    {
        cin>>num[i];
    }
    for(i=sqrt(2*k);;i--)
    {
        if(i*(i+1)<2*k)
            break;
    }
    int s=k-i*(i+1)/2;
    cout<<num[s];
    return 0;
}
```


---

