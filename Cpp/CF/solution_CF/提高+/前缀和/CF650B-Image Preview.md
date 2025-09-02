# Image Preview

## 题目描述

Vasya's telephone contains $ n $ photos. Photo number 1 is currently opened on the phone. It is allowed to move left and right to the adjacent photo by swiping finger over the screen. If you swipe left from the first photo, you reach photo $ n $ . Similarly, by swiping right from the last photo you reach photo $ 1 $ . It takes $ a $ seconds to swipe from photo to adjacent.

For each photo it is known which orientation is intended for it — horizontal or vertical. Phone is in the vertical orientation and can't be rotated. It takes $ b $ second to change orientation of the photo.

Vasya has $ T $ seconds to watch photos. He want to watch as many photos as possible. If Vasya opens the photo for the first time, he spends $ 1 $ second to notice all details in it. If photo is in the wrong orientation, he spends $ b $ seconds on rotating it before watching it. If Vasya has already opened the photo, he just skips it (so he doesn't spend any time for watching it or for changing its orientation). It is not allowed to skip unseen photos.

Help Vasya find the maximum number of photos he is able to watch during $ T $ seconds.

## 说明/提示

In the first sample test you can rotate the first photo (3 seconds), watch the first photo (1 seconds), move left (2 second), rotate fourth photo (3 seconds), watch fourth photo (1 second). The whole process takes exactly 10 seconds.

Note that in the last sample test the time is not enough even to watch the first photo, also you can't skip it.

## 样例 #1

### 输入

```
4 2 3 10
wwhw
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 4 13
hhwhh
```

### 输出

```
4
```

## 样例 #3

### 输入

```
5 2 4 1000
hhwhh
```

### 输出

```
5
```

## 样例 #4

### 输入

```
3 1 100 10
whw
```

### 输出

```
0
```

# 题解

## 作者：chufuzhe (赞：5)

这道题可以用尺取法来做，因为翻开的照片是连续的，所以可以用两个变量表示左右两个端点。因为第 $1$ 张左边是第 $n$ 张，第 $n$ 张右边是第 $1$ 张， $n$ 张照片围成了一圈，所以可以把 $n$ 张复制一份，接在原来的 $n$ 张后面，这样长度就变成了 $2n$ 。

下面来说左右两个端点的调整，设左端点为 $l$ ，右端点为 $r$ 。

$l$一开始是 $1$ ， $r$ 一开始是 $n$ 。每次调整首先将 $r$ 增加 $1$ ，然后增加 $l$ ，直到 $l-r$ 区间的和 $\le$ $t$ ，还有一种特殊情况，就是 $t$ $\lt$ 翻开 $n$ 张照片的总时间，这时 $r$ $-$ $l$ $>$ $n$，显然是不成立的，也要继续增加 $l$ ，每次调整后放入长度就是 $r-l$ ，取一个最大值就可以了。
```cpp
#include <bits/stdc++.h>
using namespace std;
int q[1000005];
char c[500005];
int main(){
    int n, a, b, t, ans = 0, s = 0; //ans表示最多可以看的照片张数，s表示翻开l-r区间的时间
    cin >> n >> a >> b >> t >> c; //输入
    for(int i = 0; i < n; i++){ //q[i]表示看第i张的时间
        if(c[i] == 'w') q[i] = q[i+n] = b + 1;
        else q[i] = q[i+n] = 1;
        if(i != 0) //第一张本来就是翻开的
        	s += q[i]; //加上第i张的时间
    }
    int l = 1, r = n; //l表示左端点，r表示右端点
    while(l <= n && r < 2 * n){ //边界条件
        s += q[r]; //加上第r张的时间
        r++; //调整r
        while(r - l > n || s + (r - l - 1 + min(r - n - 1, n - l)) * a > t){ //不成立时或l-r区间的和>t时调整l
            s -= q[l]; //减去第i张的时间
            l++; //调整l
        }
        ans = max(ans, r - l); //取最大值
    }
    cout << ans << endl; //输出
    return 0;
}
```
。



---

## 作者：tzc_wk (赞：3)

题目意思：从第一张照片开始看，可以向左翻或者向右，第1张左边是第n张，第n张右边是第一张，翻一次要a时间，照片有'w'和'h'两种摆放，‘w’的照片要耗费b时间翻转，看一张照片要1个单位时间，一共有T个单位时间，问最多可以看多少张照片？

考虑什么时候看照片最多：一定是往左翻a个，再往右翻b个

那么问题就来了

怎样求出a、b，要枚举a、b，时间复杂度O(n^2)会超时

我们可以二分

枚举左端点，二分右端点，时间复杂度O(nlogn)

check函数如下：
```
bool check(int m)
{
    for(int i=1;i<=m;i++){//枚举左端点
        lint sum1=w[i]/*这里w表示前缀和*/+(w[n]-w[n-(m-i)]);//向左翻看需要的时间
        lint sum2=min((i-1)*a*2+(m-i)*a,(i-1)*a+(m-i)*a*2);//向右翻看需要的时间
        if(sum1+sum2<=t)return 1;//和小于t则返回真
    }
    return 0;
}
```

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lint;//最好开long long
const int N=5e5+5;
int n,a,b,t;
lint w[N];
char s[N];
bool check(int m)
{
    for(int i=1;i<=m;i++){
        lint sum1=w[i]+(w[n]-w[n-(m-i)]);
        lint sum2=min((i-1)*a*2+(m-i)*a,(i-1)*a+(m-i)*a*2);
        if(sum1+sum2<=t)return 1;
    }
    return 0;
}
int main()
{
    scanf("%d%d%d%d%s",&n,&a,&b,&t,s+1);
    for(int i=1;i<=n;i++)w[i]=w[i-1]+1+(s[i]=='w'?b:0);//更新前缀和
    int l=0,r=n;
    while(l<r){//二分，不用说
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    printf("%d\n",l);//输出答案
}
```

---

## 作者：panyf (赞：1)

双指针， $O(n)$ 。

分 4 种情况讨论。向左划、向右划、先向左再向右、先向右再向左。将第 1 种和第 3 种合并，就只用讨论 3 种。

第 2 种直接算就行，后两种分别用双指针扫一遍。注意细节。

详细注释代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
char s[N];
int d[N];
int main(){
	int n,a,b,t,i,j,k,w=0;
	scanf("%d%d%d%d%s",&n,&a,&b,&t,s+1),++b;
	for(i=1;i<=n;++i)d[i]=s[i]=='w'?b:1;//看每个照片所用时间
	if(d[1]>t)return puts("0"),0;//第一张都看不完，直接退出
	for(i=1,j=d[1];j<=t&&i<=n;j+=d[++i]+a);//向右划
	w=i-1;
	if(w==n)return printf("%d",w),0;//照片都能看完，直接退出
	for(i=1,j=d[1]+a+d[n];j<=t;j+=d[++i]+a+a);//先向右再向左
	for(k=n;j-=d[i--]+a+a,i;){
		while(j<=t)j+=d[--k]+a;
		j-=d[k++]+a,w=max(w,i+n-k+1);
	}
	for(i=n,j=d[1]+a+d[n]+a;j<=t;j+=d[--i]+a+a);//先向左再向右
	for(k=1;j-=d[i++]+a+a,i<=n;){
		while(j<=t)j+=d[++k]+a;
		j-=d[k--]+a,w=max(w,k+n-i+1);
	}
	printf("%d",w);
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

~~好家伙，阅读理解题。。。~~

题目翻译有一点没说，就是当前你看过修复的照片你只需要用 $a$ 个时间就可以跳过它。

我们发现这个环比较难处理，所以我们将它变成一条链。

就是把当前这个给复制一份到后面。

举个例子就是：

`wbw` 变成 `wbwwbw`。

然后我们拿右边那个开头作为开头，因为能够往右或者往左。

然后我们发现这个答案其实是具有单调性的，就是你当前可以做到比如是 $6$ 页，那么你必定能找到一个 $5$ 页，也是满足这个条件的。

所以有一个比较好的想法就是二分这个答案，然后验证是否正确。

二分完了之后想一想 `check` 怎么写，我们考虑枚举左端点，然后可以确定右端点，但是必须让开头包含在他们之中。

但是很明显会出现一个问题，就是你当前如果说一直往左走，那么显然是要回头的，往右也同理。

那么我们可以考虑先看页数少的，于是就可以很愉快的验证完成了。

这边注意要用前缀和优化。

时间复杂度 $O(n \log n)$。

但是我们发现这个其实还可以进一步优化掉。

其实枚举左端点的时候，我们可以寻找到最大的右端点，然后左端点 $+1$ 的时候，右端点显然只会变大。

这个可以用双指针来实现，于是就变成了 $O(n)$。

代码我只用了二分就过掉了，~~双指针细节稍微多了亿点，能用二分还是用二分吧。。。~~

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int INF=1e6+5;
int n,a,b,t,sum[INF];
string s1;
bool check(int xx) {
        int sum1=(xx-1)*a+xx;
        for (int i=0; i<=n+n; i++) {
                int l=i,r=i+xx-1;
                if (l<=n+1 && n+1<=r) {
                        int ll=sum[r]-sum[l-1]; ll*=b;
                        int kk=min(r-(n+1),n+1-l)*a;
                        // cout<<l<<" "<<r<<" "<<sum1<<" "<<ll<<" "<<kk<<"\n";
                        if (sum1+ll+kk<=t) return 1;
                }
        }
        return 0;
}
signed main()
{
        ios::sync_with_stdio(false);
        cin>>n>>a>>b>>t;
        cin>>s1; s1=" "+s1+s1;
        for (int i=1; i<=n+n; i++)
                sum[i]=sum[i-1]+(s1[i]=='w');
        int l=0,r=n,ans=0;
        // cout<<check(8)<<"\n";
        while (l<=r) {
                int Mid=(l+r)>>1;
                if (check(Mid)) l=(ans=Mid)+1;
                else r=Mid-1;
        }
        cout<<ans<<"\n";
        return 0;
}

```


---

