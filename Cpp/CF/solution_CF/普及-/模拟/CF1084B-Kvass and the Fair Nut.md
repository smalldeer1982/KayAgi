# Kvass and the Fair Nut

## 题目描述

The Fair Nut likes kvass very much. On his birthday parents presented him $ n $ kegs of kvass. There are $ v_i $ liters of kvass in the $ i $ -th keg. Each keg has a lever. You can pour your glass by exactly $ 1 $ liter pulling this lever. The Fair Nut likes this drink very much, so he wants to pour his glass by $ s $ liters of kvass. But he wants to do it, so kvass level in the least keg is as much as possible.

Help him find out how much kvass can be in the least keg or define it's not possible to pour his glass by $ s $ liters of kvass.

## 说明/提示

In the first example, the answer is $ 3 $ , the Fair Nut can take $ 1 $ liter from the first keg and $ 2 $ liters from the third keg. There are $ 3 $ liters of kvass in each keg.

In the second example, the answer is $ 2 $ , the Fair Nut can take $ 3 $ liters from the first keg and $ 1 $ liter from the second keg.

In the third example, the Fair Nut can't pour his cup by $ 7 $ liters, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
3 3
4 3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4
5 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 7
1 2 3
```

### 输出

```
-1
```

# 题解

## 作者：SH___int (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF1084B)
## 一、题意理解
这道题的大致意思就是给你 $n$ 桶饮料，用这 $n$ 桶饮料填满一个大小为 $s$ 的杯子，让这 $n$ 个桶剩余饮料中的最小值最大，输出这个最小值。
## 二、题目分析
 首先来说特殊情况：如果所有饮料加起来还没有杯子的容积大，那肯定不能把杯子填满，直接输出 $-1$ 就行了。
 
 其次，饮料的升数是参差不齐的，要尽量让所有饮料中最小值最大，所以要先消耗拥有饮料较多的桶，当所有桶中剩余饮料都相同（即无论改变哪个桶，都会使最小值改变时），统一减少所有桶的饮料。
## 三、代码实现
```
#include<bits/stdc++.h>
using namespace std;
long long d[1001],amin=1000000001;
long long n,s,sum;  
//十年OI一场空 不开long long见祖宗啊 
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		cin>>d[i];
		amin=min(amin,d[i]);//找出所有饮料中最小的一桶饮料的升数 
		sum+=d[i];//求出所有饮料的总和，后面特判用 
	}
	if(sum<s)//所有饮料加起来少于杯子大小 
	{
		cout<<"-1";//无解，直接输出-1 
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		s-=d[i]-amin;//把所有饮料变成最小值 
	}
	while(s>0)//杯子还没装满，就继续判断 
	{
		s-=n;//每次操作把每桶饮料都减少一升 
		amin--;//最小值相应的也减少1 
	}
	cout<<amin;//完美输出 
	return 0;
}
```


---

## 作者：chufuzhe (赞：3)

### 题意：
给出 $n$ 个装满液体的罐子和一个杯子的容积。问把杯子倒满后剩余液体最少的杯子中液体的体积的最大值。

### 思路：
根据 **保证剩余液体最少的杯子的液体体积要尽可能大** 这句，可以知道是要求平均值，如果剩余液体最少的杯子中液体体积小于平均值，那么答案就是剩余液体最少的杯子里的液体体积，如果等于答案就是所有杯子中液体体积的平均值。

**注意**， $1$ $\leq$ $s$ $\leq$ $10^{12}$，要用 $long$ $long$ 。

### 扩展：
 [三目运算符](https://baike.baidu.com/item/%E4%B8%89%E7%9B%AE%E8%BF%90%E7%AE%97%E7%AC%A6/6434591?fr=aladdin) ：对于条件表达式 $b$ $?$ $x$ $:$ $y$，当条件b成立时，运算结果为 $x$ 的值，反之运算结果为 $y$ 的值。
 
要注意，三目运算符优先级比较低，不要忘记加括号。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int n, minv = INT_MAX;
	long long s, sum = 0;
	//定义，sum表示总体积，后面求平均值是要用到，minv是最小的体积
	cin >> n >> s;  //输入
	for(int i = 1; i <= n; i++) {
		int v;
		cin >> v;
		minv = min(minv, v); //取最小值
		sum += v; //加进总变量
	}
	cout << (sum < s ? -1 : min((sum - s) / n, minv)) << endl;
	//当剩余液体最少的杯子中液体体积小于平均值时，答案就是剩余液体最少的杯子里的液体体积，反之就是平均值。
	return 0;
}
```


---

## 作者：zsh_haha (赞：0)

~~更新了题解规范，都有点不敢交题解了。~~

### 题意理解

有 $n$ 小杯饮料，要用这些饮料装满容量为 $s$ 升的大杯（小 FN 能喝下去吗），问是否能装满，若可以，要求装满后小杯饮料中的饮料量最小的那一杯的饮料量尽量大（有点拗口）。

### 思路讲解

首先求出 $n$ 杯饮料的总升数，若小杯的总升数还不到大杯的升数，那一定装不满，直接输出 $-1$。

若能装满，进行如下操作，设第 $i$ 个小杯的饮料量为 $a_i$：

- 找到小杯最小饮料量，设最小饮料量的小杯编号为 $min$。
- 遍历每个杯子，使每个小杯倒出 $a_i-a_{min}$，也就是使每个小杯的饮料量变成 $a_{min}$（不用管大杯有没有倒满，反正最小饮料量不会变）。
- 遍历完后有两种情况，第一种是大杯已经倒满了，这时小杯的最小饮料量为 $a_{min}$，直接输出 $-1$；大杯若没有倒满，就是第二种情况，继续进行下面的操作。
- 你需要进行多次操作，每次操作就是使每个小杯倒出 $1$ 升到大杯里，若当前操作后大杯装满了，那么最小饮料量就是 $a_{min}-d$，这里设 $d$ 为操作次数，**注意：如果 $a_{min}-d<0$，那么也要输出 $-1$**。当然你可以用一道算式来表示操作次数，设大杯还未装的升数为 $L$：$d=\lceil\frac{L}{n}\rceil$，因为每次操作都是 $n$ 个小杯倒 $1$ 升，也就是每次操作倒 $1\times n=n$ 升。

### ~~你们最爱的~~ AC 代码 

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int main(){
	long long s;
	int minn=1000000001;
	int n;
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		minn=min(minn,a[i]);
	}
	for(int i=1;i<=n;i++){
		s-=(a[i]-minn);
	}
	if(s<=0){
		cout<<minn;
		return 0;
	}
	s=ceil(s*1.0/n);
	if(s>minn){
		cout<<-1;
	}else{
		cout<<minn-s;
	}
    return 0;
}
```

---

## 作者：Dreamerly (赞：0)

## 题目：[CF1084B](https://www.luogu.com.cn/problem/CF1084B)
## 思路：
第一步：需要先比较桶中总体积 $sum$ 与 $s$ ，若 $sum$ $<$ $s$ ，说明无论如何都无法装满，那么直接输出 $-1$ 。


------------

第二步：再根据题意，让我们找最小的最大值。因此最优情况肯定是所有桶剩余的一样,尽可能使所有桶平衡，考虑枚举。同时不难发现有单调性，并且暴力枚举肯定过不了，因此考虑二分。

## 代码：
```
#include<bits/stdc++.h>
#define int long long)
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
} 
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int a[1001];
int n,s,ans=-1;
int sum,minn=0x3f3f3f3f;
bool check(int x){
	int leave=n*x; //剩余的量 
	if(sum-leave>=s) return 1;//若倒出的量大于s,说明此方案可行 
	else             return 0;//反之,说明此方案不行 
}
signed main(){ 
	n=read(),s=read();
	for(int i=1;i<=n;i++) sum+=(a[i]=read());
	if(sum<s) return write(-1),0; 
    
	for(int i=1;i<=n;i++) minn=min(minn,a[i]); 
	int l=0,r=minn;
	while(l<=r){ //二分答案
		int mid=(l+r)>>1;
		if(check(mid)){
			l=mid+1;
			ans=max(ans,mid);
		}  
		else r=mid-1;
	}
	write(ans);
	return 0;
} 
```


---

## 作者：wjk2020 (赞：0)

题意大概是给你一个数组，让你求一个最小的最大 sz , 使得

$(a[1]-sz)+(a[2]-sz)+......+(a[n]-sz) = s$

这题我的初始想法是从 $a[1],a[2],...,a[n]$ 中找一个最小值，

从它开始向下枚举，直到找到一个 $ans$ ，让 

$(a[1]-sz)+(a[2]-sz)+......+(a[n]-sz) - s \le s+n$

## $code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int sum, sz;
int main()
{
    int n, s;cin >> n >> s;
    for(int i = 1;i <= n;i++)
        cin >> a[i], sz = min(sz, a[i]);
    while(1)
    {
        int sum = 0;
        for(int i = 1;i <= n;i++)
            sum += a[i] - sz;
        if(sum == s){cout << sz;break;}
        else if(sum - s <= n){cout << sz-1;break;}
    }
    return 0;
}
```
TLE了。

不难想出原因：$1 \le a[i] \le 10^9$ , 肯定会炸。

这里，我把最后的部分作了优化，效果显著。

```cpp
#include<bits/stdc++.h>
#define FOR(i, m, n) for(int i = m;i <= n;i++)
using namespace std;
const int NR = 1e9;
long long n, s, a[1001];
long long ans = NR, sum;
int main()
{
    cin >> n >> s;
    FOR(i, 1, n)cin >> a[i];
	FOR(i, 1, n)sum += a[i];
	FOR(i, 1, n)ans = max(ans, a[i]);
    if(sum < s)   cout << "-1";    
    else if(sum - ans * n >= s) 
		cout << ans;          
    else
	{
        s -= (sum - ans * n);
        if(s % n == 0)ans -= s / n;
        else ans -= s / n + 1;
		cout << ans;     
    }
    return 0;
}
```


---

## 作者：lhjy666 (赞：0)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;
ll a[100005];
ll n,m,zong=0,minn=9999999999;
bool check(ll k)
{
	ll z=0;
	for (ll i=1;i<=n;i++)
	{
		z+=a[i]-k;
		if(k>a[i]) return 0;
	}
	if(z>=m) return 1;
	else return 0;
}
ll erfen()
{
	ll l=0,r=minn,mid,t=0;
	while(l<=r)
	{
		t++;
		mid=l+(r-l)/2;
		if(r-l<=3)
		{
			for (ll i=l;i<=r;i++)
			{
				if(check(i)) continue;
				else return i-1;
			}
			return r;
		}
		if(check(mid))
		{
			l=mid;
		}
		else
		{
			r=mid-1;
		}
	}
	return mid;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for (ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		zong+=a[i];
		if(a[i]<minn) minn=a[i];
	}
	if(zong<m) 
	{
		printf("-1");
		return 0;
	}
	ll ans=erfen();
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,a[1001],s,ans=99999999999999,sum;//ans存最大值,但要是在各个瓶中的最小值
int main(){
    cin>>n>>s;
    for(i=1;i<=n;i++) cin>>a[i],ans=ans>a[i]?a[i]:ans,sum+=a[i];//最小中的最大
    if(sum<s) cout<<"-1";//不可能倒出这么多
    else if(sum-ans*n>=s) cout<<ans;//足够多
    else{
        s-=(sum-ans*n);
        if(s%n==0) ans-=s/n;
        else ans-=s/n+1;
        //每桶依次-1
        cout<<ans;//答案
    }
    return 0;
}
```

---

## 作者：shenmadongdong (赞：0)

```
var n,s,m,g,mi,b:int64;
    i:longint;
begin
  read(n,s);
  for i:=1 to n do begin read(m); g:=g+m; if (m<mi)or(mi=0) then mi:=m; end;
  if s<g-mi*n then writeln(mi)
  else begin
  g:=g-s;
  if g>=0 then writeln(g div n) else writeln('-1');
  end;
end.
```

---

