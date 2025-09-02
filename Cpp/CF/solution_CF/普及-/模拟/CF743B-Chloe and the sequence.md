# Chloe and the sequence

## 题目描述

Chloe, the same as Vladik, is a competitive programmer. She didn't have any problems to get to the olympiad like Vladik, but she was confused by the task proposed on the olympiad.

Let's consider the following algorithm of generating a sequence of integers. Initially we have a sequence consisting of a single element equal to $ 1 $ . Then we perform $ (n-1) $ steps. On each step we take the sequence we've got on the previous step, append it to the end of itself and insert in the middle the minimum positive integer we haven't used before. For example, we get the sequence $ [1,2,1] $ after the first step, the sequence $ [1,2,1,3,1,2,1] $ after the second step.

The task is to find the value of the element with index $ k $ (the elements are numbered from $ 1 $ ) in the obtained sequence, i. e. after $ (n-1) $ steps.

Please help Chloe to solve the problem!

## 说明/提示

In the first sample the obtained sequence is $ [1,2,1,3,1,2,1] $ . The number on the second position is $ 2 $ .

In the second sample the obtained sequence is $ [1,2,1,3,1,2,1,4,1,2,1,3,1,2,1] $ . The number on the eighth position is $ 4 $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 8
```

### 输出

```
4```

# 题解

## 作者：清小秋ovo (赞：10)

# CF743B
这题并不难，也不需要什么复杂的算法。

个人认为更考验的是数感和对于规律的分析吧。

吃饭的时候找了找规律，发现我这个做法思路清奇，目前题解里没有看到跟我一样的，所以就特意来一发题解讲讲我的思路。

## 题目理解
题意简介明了，就是根据给出的 $n$ 生成一个特定的序列。

值得注意的是，这个序列的每一项的数值本来就是固定的，而 $n$ 只是限定了这个数列的长度，跟数列本身关系并不大。

所以我们需要做的，就是根据题目给出的位置，找出数列中该位置的数字是什么数字。

## 找规律

下面进入激动人心~~枯燥乏味~~的找规律环节！

下面会列举出 $n$ 的值，并且写出 $n$ 的值对应的数列的样子：
$$n=1$$
$$1$$
$$n=2$$
$$121$$
$$n=3$$
$$1213121$$
$$n=4$$
$$121312141213121$$
$$n=5$$
$$1213121412131215121312141213121$$
$$n=6$$
$$121312141213121512131214121312161213121412131215121312141213121$$

乍一看可能看不出来啥东西，只是觉得这是一个很对称的数列。

那如果我们把一些数字出现的信息整合成一个表格呢？


| 统计数字 |出现位置  |规律  |
| :----------- | :----------- | :----------- |
|  $1$|$1,3,5,7,9,...... $ | 对 $2$ 取余结果为 $1$|
|  $2$|$2,6,10,14,......$  | 对 $4$ 取余结果为 $2$|
|  $3$|$4,12,20,28,36......$  | 对 $8$ 取余结果为 $4$ |
|  $4$|$8,24,40,56,72,……$  | 对 $16$ 取余结果为 $8$  |

这样的话是不是就逐渐看出了规律！！

在表格的规律一栏里出现了两个数字，为了提取出一条有用的式子，不妨将这两个数字设为 $x,y$，当前的统计数字为 $i$。

通过观察可以看出，$x$ 永远是 $y$ 的 $2$ 倍，同时，$x$ 的值永远为 $2^i$。

根据这个规律我们就可以写出如下的判断式：

```cpp
k%ll(pow(2,i))==ll(pow(2,i))/2 //判断是否对x取余时结果为y
```

此时我们只需要用一个循环从 $1$ 开始来看是哪个数字符合判断条件。

因为题目给出 $n$ 不会超过 $50$，所以这样的做法是完全可行的。

已经推到这一步了，这题已经可以说是迎刃而解了。

唯一需要注意的点就在于变量一定要开对，这题的数据已经爆整型了。

不多废话，上代码。

## 完整代码

简洁版

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k;
int main()
{
    cin>>n>>k;
    for (int i=1;i<=n;i++) if (k%ll(pow(2,i))==ll(pow(2,i))/2) cout<<i<<endl;
}
```

方便阅读版

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k;
int main()
{
    cin >> n >> k; 
    for (int i = 1; i <= n; i++)
        if (k % ll(pow(2, i)) == ll(pow(2, i)) / 2)//注意一定要开long long
            cout << i << endl;
}
```

完结撒花！

码字不易，欢迎各位与大佬在评论区交流。






---

## 作者：wpy233 (赞：3)

。。。果然是CF一道愚人节的题目。。。

还好本人没恶评，评了个普及-（谁敢恶评偶去找TA）

好吧其实这题完全可以转化为另一个问题：
```
给你一个n层的汉诺塔，问把它复原的第k步移动的是哪个圆片？
```
不需要递归，什么都不需要，你只要会一点点汉诺塔就可以AC。

如果你不知道，你可以去玩一玩。

玩越久你就会会发现一个规律：
```
举例：当n=4；
移动圆片1（最小）的次数：8；
移动圆片2的次数：4；
移动圆片3的次数：2；
移动圆片4的次数：1；
```
而且你还会发现：
```
第1、3、5、7、9、11、13、15次移动的是圆片1；
第2、6、10、14次移动的是圆片2；
第4、12次移动的是圆片3；
第8次移动的是圆片4；
```
相信大家看到这里，应该知道怎么做了。

贴代码：
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n,m;//注意2^50-1已经爆int
    cin>>n>>m;
    int s=1;
    for(int i=1;i<=n;i++)
    	if(m%2==0)
    		m/=2,s++;//这规律不难找吧。。。
    cout<<s<<endl;
    return 0;
}
```
CF的愚人节题还是很水的。。。。。

---

## 作者：LucasXu80 (赞：2)

带大家找找规律，然后康康Python的代码~

首先我们把$n=1,2,3,4$的数列都打出来找找规律：

$n=1$

$1$

$n=2$ 

$1,2,1$

$n=3$

$1,2,1,3,1,2,1$

$n=4$

$1,2,1,3,1,2,1,4,1,2,1,3,1,2,1$

首先是一个很显然但也是很重要的规律：

**这几个数列的每一项其实都是固定的，只是随着**$n$**不同，数列的长度不同罢了。**

换言之，这道题跟$n$**没有任何关系**。

接下来我们来看看每一项的值。以$n=3$为例。

这里我们定义$f(n)$为满足$2^k$整除$n$的最大$k$值，则有：

|项序号$m$|项的值|$f(m)$|
| :----------: | :----------: | :----------: |
|$1$|$1$|$0$|
|$2$|$2$|$1$|
|$3$|$1$|$0$|
|$4$|$3$|$2$|
|$5$|$1$|$0$|
|$6$|$2$|$1$|
|$7$|$1$|$0$|

发现了什么？

项的值$=f(m)+1$。

好了，现在我们就把思路解决了。

要求出$f(m)$的值也不难，当$m$为偶数的时候不断$/2$即可。

上代码！

```python
n,m=map(int, input().split()) #输入n，m（其实n没用）
ans=1 #这个1就是那个f(m)+1后面的+1，后面输出时就不用加了
while m%2==0: #还有因子2可提
    m/=2 #提出一个2
    ans+=1 #f(m)加1，也就是答案的值+1
print(ans) #最后输出答案
```
80B代码就能[AC](https://www.luogu.com.cn/record/33707522)，岂不妙哉？

最后，求过求赞！

---

## 作者：添哥 (赞：1)

## $O(log N)$做法

虽然本题不卡常，~~但为了让窝们显得高大上一点~~，本蒻决定发一篇代码为 $O(log $ $N)$ 级别的题解。

首先楼上的大佬们已经说过了，本题与 $N$ **无关**，这个序列永远是固定的：

`1 2 1 3 1 2 1 4 1 2 1 3 1 2 1……`

本蒻看到这个序列，立马想到了树状数组的数列：

`1 2 1 4 1 2 1 8 1 2 1 4 1 2 1……`

树状数组的序列很好求，用一个 $lowbit$ 就珂以了，但是怎么把树状数组的数列转换为题目要求的序列呢？原来，窝们只需要求出 $log_2$ $n+1$ 就珂以了。众所周知，求一个数的 $log$ 的复杂度为 $O(log$ $N)$ 。

### 所以最后的柿子是：

$$log_2(lowbit(n))$$

## 既然柿子推出来了，代码也很简单了：
```cpp
#include<iostream>
using namespace std;
int main()
{
    long long k,ans=0;
    cin>>k>>k;		//因为题目与N无关，所以窝们读两遍K，把N读掉
    k=k&-k;		//因为只用一次，所以我懒得写lowbit了
    while(k)
    {
        k/=2;
        ans++;
    }		//求K的log
    cout<<ans;
    return 0;
}
```

---

## 作者：Paris_Bentley (赞：0)

用一个类似二分的方法解决。

第一次把最大的数字放在中间位置，初始区间设定为1到16(左闭右开），之后每次把数字n--，同事重新更新左右边界，逐渐找到k的位置，这样的logN的复杂度一定不会超时。

不过千万要记得开long long。

上代码~
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,pos,l,r,ans;
int main()
{
	cin>>n>>k;
	ans=n;
	l=1;
	r=pow(2,n);
	pos=pow(2,n-1);//最大数字放在中心位置 也可以pos=(l+r)/2 
	while (pos!=k)
	{
		ans--;
		if (k<pos) r= pos;
		else l = pos;
		pos=(l+r)/2; 
	}
	cout<<ans<<endl;
}
```


---

## 作者：yxy666 (赞：0)

这道题虽然很简单，但是需要注意的地方还是蛮多的。（我调了半小时）。。。

切入正题：这道题是分 $n$ 的奇偶来看的。先看下列的分析图像：

下列图中 $a$ 数组表示输入数据，最上面的数字是答案下标。

当 $n$ 为奇数时（对照样例一）：

![](https://cdn.luogu.com.cn/upload/image_hosting/lprqomx7.png)

当 $n$ 为偶数时：（对照样例三）:

![](https://cdn.luogu.com.cn/upload/image_hosting/sylfdctp.png)

那我们就有了一个想法：如果 $n$ 为奇数时，我提前将 $a[1]$ 给答案，也就是最中间的值，然后接下来给值都是有规律的，一左一右，一左一右，那么就解决了呀。
```
	if(R%2!=0){//R表示字符串的长度
		ans[mid]=a[1];L=mid-1;R=mid+1;//L表示如果下次放左边，那我就放L这儿
		for(int i=2;i<=n;i++){//R表示如果下次放右边，那我就放R这儿
			if(L==0)ans[R++]=a[i];//如果左边放不下了，就放右边
			else if(R==strlen(a+1))ans[L--]=a[i];//如果右边放不下，就放右边
			else if(i%2==0)ans[L--]=a[i];//否则就按规律对应的放
			else ans[R++]=a[i]; 
		}
	}
```
如果 $n$ 为偶数，那么我提前将中间 $2$ 个的值赋掉，然后就很好办了啊（本人较懒，就不解释了，相信聪明的你能看懂）。

```
		ans[mid]=a[1];ans[mid+1]=a[2];
		L=mid-1,R=mid+2;
		for(int i=3;i<=n;i++){
			if(L==0)ans[R++]=a[i];
			else if(R==strlen(a+1))ans[L--]=a[i];
			else if(i%2==1)ans[L--]=a[i];
			else ans[R++]=a[i]; 
		}
```

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[2005],ans[2005];
int n;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read();
	scanf("%s",a+1);int L=1,R=strlen(a+1);
	int mid=(L+R)/2;
	if(R==2){
		puts(a+1);return 0;
	} 
	if(R%2!=0){
		ans[mid]=a[1];L=mid-1;R=mid+1;
		for(int i=2;i<=n;i++){
			if(L==0)ans[R++]=a[i];
			else if(R==strlen(a+1))ans[L--]=a[i];
			else if(i%2==0)ans[L--]=a[i];
			else ans[R++]=a[i]; 
		}
	}
	else{
		ans[mid]=a[1];ans[mid+1]=a[2];
		L=mid-1,R=mid+2;
		for(int i=3;i<=n;i++){
			if(L==0)ans[R++]=a[i];
			else if(R==strlen(a+1))ans[L--]=a[i];
			else if(i%2==1)ans[L--]=a[i];
			else ans[R++]=a[i]; 
		}
		
	}

	for(int i=1;i<=n;i++)printf("%c",ans[i]);
	return 0; 
}
```



---

