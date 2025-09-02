# Garbage Disposal

## 题目描述

Enough is enough. Too many times it happened that Vasya forgot to dispose of garbage and his apartment stank afterwards. Now he wants to create a garbage disposal plan and stick to it.

For each of next $ n $ days Vasya knows $ a_i $ — number of units of garbage he will produce on the $ i $ -th day. Each unit of garbage must be disposed of either on the day it was produced or on the next day. Vasya disposes of garbage by putting it inside a bag and dropping the bag into a garbage container. Each bag can contain up to $ k $ units of garbage. It is allowed to compose and drop multiple bags into a garbage container in a single day.

Being economical, Vasya wants to use as few bags as possible. You are to compute the minimum number of bags Vasya needs to dispose of all of his garbage for the given $ n $ days. No garbage should be left after the $ n $ -th day.

## 样例 #1

### 输入

```
3 2
3 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 1
1000000000 1000000000 1000000000 1000000000 1000000000
```

### 输出

```
5000000000
```

## 样例 #3

### 输入

```
3 2
1 0 1
```

### 输出

```
2
```

## 样例 #4

### 输入

```
4 4
2 8 4 1
```

### 输出

```
4
```

# 题解

## 作者：wky32768 (赞：3)

思路就是对于每一天，先加上前面的值，如果小于K且有残留就~~必须~~装掉，不然就装n/k个袋子(可证残留<k)。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[230000],ans;
signed main() {
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        a[i]+=a[i-1];
        if(a[i]<k && a[i-1]!=0) {
            ans++;
            a[i]=0;
        } else {
            ans+=a[i]/k;
            a[i]%=k;
        }
    }
    if(a[n]) ans++;
    cout<<ans;
    return 0;
}
```

---

## 作者：Zq_water (赞：2)

## 贪心题

[题目描述](https://www.luogu.com.cn/problem/CF1070D)

#### 题目思路

贪心的策略就是要让每个垃圾袋尽可能装满。

每一次将上一天剩余的垃圾加上今天产生的垃圾为新的垃圾总量，再装新的垃圾总量除以 $k$ 个垃圾袋，剩余的留给下一天。

此外，若最后一天的垃圾没有装完，还要将答案加 $1$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,x,ans,p;
int main(){
    cin>>n>>k;
    for(long long i=1;i<=n;i++){
        cin>>x;
        x+=p;
        if(x<k&&p!=0){
            ans++;
            p=0;
        }
		else{
            ans+=x/k;
            p=x%k;
        }
    }
    if(p!=0) ans++;
    cout<<ans;
    return 0;
}
```

---

## 作者：MYFJWHR (赞：0)

### CF1070D

#### Part 1 思路

**贪心**，每个垃圾口袋尽可能多的装垃圾，算出昨天剩下的垃圾加上今天产生的垃圾的总和，再用总和去除以垃圾袋的容量，这个就是今天所用的垃圾袋的数量，再把装不下的垃圾留到明天再处理。最后统计每天所用的垃圾袋总量就行了。

#### Part2 代码

```c++
#include<bits/stdc++.h>
using namespace std;
long long  n,k,a,sum,ans;//注意开long long
inline long long read(){
	char ch=getchar();
	long long x=0;
	bool t=0;
	while(ch<'0'||ch>'9')   t|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return t?-x:x;
}//快读

inline void write(long long x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}//快写

int main(){
	n=read();
	k=read();
	while(n--){
		cin>>a;
		sum+=a;//昨天剩的加今天产生的垃圾
		if(sum<k&&(sum-a)!=0){ans++;sum=0;}//注意，（sum-a)!=0表示昨天没有剩下的垃圾
		else{ans+=sum/k;sum%=k;}	
	}
	if(sum) ans++;//如果最后一天还有垃圾，另外一个垃圾袋
	write(ans);
	return 0;
}
```



---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现这是一道贪心题。在用垃圾袋时要保证尽量少的浪费，所以我们可以每次都把上一天的垃圾留到这一天，这样的浪费肯定是最小的。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,k,a[200005],ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
		if(a[i]<k&&a[i-1]!=0){
			ans++;
			a[i]=0;
		}
		else{
			ans+=a[i]/k;
			a[i]%=k;
		}
	}
	if(a[n]!=0){
		ans++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Leaves_xw (赞：0)

**题目描述：**

Vasya 已经很多次忘记将垃圾从公寓里扔出去。现在他想制定一个计划并遵守它。 对于接下来的 $n$ 天 Vasya 知道他每天会制造 $a_i$ 的垃圾。 Vasya  会将垃圾放在垃圾袋中并扔掉垃圾袋每个袋子能装 $k$ 的垃圾，一天可以扔掉或使用多个垃圾袋。 Vasya 想要使用最少的垃圾袋，你需要输出最少的垃圾袋数量。

当天生产的垃圾是可以留到第二天的，但最多留到第二天。

**思路：**

贪心题。

每一次加上今天的垃圾，如果昨天还有垃圾没扔，则将昨天的垃圾跟今天的一起扔掉，否则就将昨天没丢的和今天的除以 $k$，剩下的留到明天丢。


$a_i \le 10^9$，不开`long long` 肯定没分。


**AC代码：**

```
#include<bits/stdc++.h>
using namespace std;
long long now[200005];
int main()
{
	long long n,k,cnt=0,x;//开long long
	cin>>n>>k;
	for(long long i=1;i<=n;i++)
	{
		cin>>x;
		now[i]+=x;//今天需要丢的垃圾数累加
		if(now[i]%k==0)//如果能够整除
		{
			cnt+=now[i]/k;//计数器直接加上now[i]/k
			now[i]=0;//记得清零
		}
		else if(now[i]<k&&now[i-1]!=0)//如果昨天没有剩的直接跳过
		{
			cnt++;//只丢一个垃圾袋
			now[i]=0;//清零
		}
		else
		{
			cnt+=now[i]/k;//计数器累加
			now[i+1]+=now[i]%k;//剩下的垃圾明天仍
		}
	}
	if(now[n+1]>0)cnt++;//特殊判断
	cout<<cnt<<endl;//输出，别忘了换行
	return 0;
}
```

---

## 作者：ruruo (赞：0)

# 分析

- 一道很好想的贪心。贪心策略就是尽量让每个垃圾袋装更多的垃圾。

- 具体地，对于每一天，如果上一天剩下的垃圾和这一天产生的垃圾加起来都装不满一个垃圾袋，那直接用一个垃圾袋全部丢掉即可。

- 否则，**装满**尽可能多的垃圾袋，剩下的留到下一天处理。

- 最后需要一个特判：如果最后一天还剩下了垃圾，那还需要一个垃圾袋丢掉。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k, x, ans = 0, now = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> x;
        x += now;
        if(x < k && now != 0){
            ans++;
            now = 0;
        }else{
            ans += x / k;
            now = x % k;
        }
    }
    if(now != 0) ans++;
    cout << ans << endl;
    return 0;
}
```


---

## 作者：j1ANGFeng (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1070D)

### 思路
根据贪心，今天的能不丢就不丢，并尽可能让每个垃圾袋多装垃圾。

如果昨天有残留就必须加上今天的丢掉，否则将昨天的垃圾加上今天的垃圾除以 $k$，剩下的丢到明天去。

其余见代码注释。
## 注意

如果今天是最后一天，并且今天有垃圾，必须将答案加 $1$。
### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define int long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}
signed main(){
	int n=rd()+1,k=rd(),w,la=0,ans=0;
	while(--n){
		w=rd();
		w+=la;
		if(w<k&&la){  //昨天的有残留
			++ans;
			w=0;
		}else{
			ans+=w/k;
			w%=k;
		}
		la=w;
	}
	if(la)      //最后一天的垃圾没丢完.
	  ++ans;
	wt(ans);
	return 0;
}
```

---

## 作者：杨xyz (赞：0)

## 思路

尽可能让每个垃圾袋多装垃圾。

处理当天的垃圾时，加上昨天所剩余的，若昨天有剩余且总共不满 $k$ 个垃圾，用一个袋子装（因为只能留到第二天），否则，使用 $a_i/k$ 个袋子。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iomanip>
using namespace std;
int a[200001];
int main()
{
	long long n,k,ans=0,x;//a[i]<=1e9,必须用long long。
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[i]+=x;
		if(a[i]%k==0){//当然，这里用两个if也可以。
			ans+=a[i]/k;
			a[i]=0;
		}
		else if(a[i]<k&&a[i-1]!=0){
			ans++;
			a[i]=0;
		}
		else{
			ans+=a[i]/k;
			a[i+1]+=a[i]%k;
		}
	}
	if(a[n+1]>0)ans++;
	cout<<ans;
	return 0;
}

```

---

